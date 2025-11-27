/*
 * (c) see end of file for license terms.
 *
 */
#ifndef _debug_unit_fpga_h_
#define _debug_unit_fpga_h_
#include <string.h>

#define SPI_FLASH_READ_STATUS				0x05
#define SPI_FLASH_WRITE_ENABLE			0x06
#define SPI_FLASH_WRITE_DISABLE			0x04
#define SPI_FLASH_CE							0x60
#define SPI_FLASH_READ_ID					0x9f	// or 9e
#define SPI_FLASH_READ						0x03
#define SPI_FLASH_PAGE_WRITE				0x02
#define SPI_FLASH_4K_SECTOR_ERASE		0x20
#define SPI_FLASH_PAGE_ERASE				0x81	// or db
#define SPI_FLASH_ENTER_POWER_DOWN		0xb9
#define SPI_FLASH_RELEASE_POWER_DOWN	0xab

uint32_t flash_get_chip_id (byte_buffer_t);
void flash_wakeup (void);

#ifdef IMPLEMENT_DBU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------
#ifdef HAS_FLASH_PROGRAMMER_PORT

//
// the smalest erase size
uint32_t flash_block_size = 4096;
uint32_t flash_write_address;

void
initialise_fpga (void) {	
	HAL_SPI_FPGA_initialise ();
	HAL_SPI_FPGA_disable ();
	HAL_GPIO_FPGA_SS_in ();
	HAL_GPIO_FPGA_CDONE_in ();
	HAL_GPIO_FPGA_CDONE_pullup ();
	HAL_GPIO_FPGA_CRESET_in ();
}

uint32_t
read_le_uint32 (uint8_t const* ptr) {
	uint8_t const* ptr8 = (uint8_t const*) ptr;
	return (
			(uint32_t) ptr8[0] 
		+	((uint32_t)ptr8[1] << 8)
		+	((uint32_t)ptr8[2] << 16) 
		+	((uint32_t)ptr8[3] << 24)
	);
}

void 
delay (uint32_t delay) {
	volatile uint32_t count = delay;
	while (count--);
}

void
flash_wakeup (void) {
	uint8_t cmd[] = {
		SPI_FLASH_RELEASE_POWER_DOWN
	};
	HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_ACTIVE);
	HAL_SPI_FPGA_write_read (def_byte_slice (cmd,1),def_byte_buffer (NULL,0));
	
	delay (50);
	
	HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_INACTIVE);
}

void
flash_sleep (void) {
	uint8_t cmd[] = {
		SPI_FLASH_ENTER_POWER_DOWN
	};
	HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_ACTIVE);
	HAL_SPI_FPGA_write_read (def_byte_slice (cmd,1),def_byte_buffer (NULL,0));
	HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_INACTIVE);
}

uint32_t
flash_get_chip_id (byte_buffer_t id) {
	if (id.size == 4) {
		uint8_t cmd[5] = {
			SPI_FLASH_READ_ID,0,0,0,0
		}, data[5] = {0};

		HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_ACTIVE);

		HAL_SPI_FPGA_write_read (def_byte_slice (cmd,1),def_byte_buffer (data,5));

		HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_INACTIVE);

		memcpy (id.bytes,data + 1,4);
		return 4;
	} else {
		return 0;
	}
}

void
pulse_chip_select (void) {
	HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_INACTIVE);
	delay (3);
	HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_ACTIVE);
}

//
// expects CS to be active
//
uint8_t
fpga_flash_read_status_register (void) {
	uint8_t cmd[] = {
		SPI_FLASH_READ_STATUS,0
	}, data[2] = {0};
	
	HAL_SPI_FPGA_write_read (
		def_byte_slice (cmd,2),
		def_byte_buffer (data,2)
	);
		
	return data[1];
}

void
fpga_flash_write_enable (void) {
	uint8_t cmd[] = {
		SPI_FLASH_WRITE_ENABLE
	};
	HAL_SPI_FPGA_write_read (
		def_byte_slice (cmd,1),
		def_byte_buffer (NULL,0)
	);

	pulse_chip_select ();
}

void
fpga_flash_write_disable (void) {
	uint8_t cmd[] = {
		SPI_FLASH_WRITE_DISABLE
	};
	HAL_SPI_FPGA_write_read (
		def_byte_slice (cmd,1),
		def_byte_buffer (NULL,0)
	);
}

uint16_t
flash_partial_erase (uint16_t first_block,uint16_t last_block) {
	uint8_t status = 0;
	uint32_t begin_address = first_block * flash_block_size;
	uint32_t end_address = (last_block + 1) * flash_block_size;
	uint16_t count = 0;
	
	HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_ACTIVE);

	while (begin_address < end_address) {
		uint8_t cmd[] = {
			SPI_FLASH_4K_SECTOR_ERASE,
			begin_address >> 16,
			begin_address >> 8,
			begin_address
		};

		fpga_flash_write_enable ();
		
		HAL_SPI_FPGA_write_read (
			def_byte_slice (cmd,sizeof(cmd)),def_byte_buffer (NULL,0)
		);

		pulse_chip_select ();
		
		do {
			delay (1000);
			status = fpga_flash_read_status_register ();
		} while ((status & 0x01) != 0);
		
		begin_address += flash_block_size;
		count ++;
	}
	count --;
	
//	fpga_flash_write_disable ();
	
	HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_INACTIVE);
	
	return (count);
}

uint8_t
flash_begin_write (uint32_t address) {
	flash_write_address = address;
	return 1;
}

uint8_t
flash_write_chunk (uint8_t const *data,uint32_t size) {
	uint8_t status;

	HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_ACTIVE);

	uint8_t cmd[] = {
		SPI_FLASH_PAGE_WRITE,
		flash_write_address >> 16,
		flash_write_address >> 8,
		flash_write_address
	};

	fpga_flash_write_enable ();

	HAL_SPI_FPGA_write_read (
		def_byte_slice (cmd,sizeof(cmd)),
		def_byte_buffer (NULL,0)
	);

	HAL_SPI_FPGA_write_read (
		def_byte_slice (data,size),
		def_byte_buffer (NULL,0)
	);

	pulse_chip_select ();
	
	while (((status = fpga_flash_read_status_register ()) & 0x03) != 0) {
		// firstread get 0x03
		delay (100);
		status = fpga_flash_read_status_register ();
	}
	
	flash_write_address += size;

	HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_INACTIVE);
	
	return status;
}

uint32_t
flash_end_write (void) {
	return flash_write_address;
}

uint32_t
flash_read_content (uint32_t address,byte_buffer_t rd) {
	uint8_t cmd[] = {
		SPI_FLASH_READ,
		address >> 16,
		address >> 8,
		address
	};

	HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_ACTIVE);

	HAL_SPI_FPGA_write_read (
		def_byte_slice (cmd,sizeof(cmd)),
		def_byte_buffer (NULL,0)
	);

	HAL_SPI_FPGA_write_read (
		def_byte_slice (NULL,0),
		rd
	);

	delay (10);
	
	HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_INACTIVE);

	return 0;
}

#else
void
initialise_fpga (void) {
	// nothing to do
}
#endif
#endif /* IMPLEMENT_DBU */
#endif
/*

BSD 3-Clause License

Copyright (c) 2025, Gregor Bruce

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
