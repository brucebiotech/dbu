/*
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _dbu_cmsis_dap_extensions_H_
#define _dbu_cmsis_dap_extensions_H_


void fpdu_vendor_extension_select_swj_pins (void);
void fpdu_vendor_extension_selected_swj_pins (void);

void fpdu_vendor_extension_select_swo (void);
void fpdu_vendor_extension_selected_swo (void);


#ifdef IMPLEMENT_DBU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

void
fpdu_vendor_extension_select_swj_pins (void) {
	int index = dap_req_get_byte ();
	if (0 == DUBUG_UNIT_SELECT_SWJ_PINS (index)) {
		dap_resp_add_byte (DAP_OK);
	} else {
		dap_resp_add_byte (DAP_ERROR);
	}
}

void
fpdu_vendor_extension_selected_swj_pins (void) {
	dap_resp_add_byte (1);
	dap_resp_add_byte (DUBUG_UNIT_SELECTED_SWJ_PINS ()); 
}

void
fpdu_vendor_extension_select_swo (void) {
	int index = dap_req_get_byte ();

	if (0 == DUBUG_UNIT_SELECT_SWO_UART (index)) {
		dap_resp_add_byte (DAP_OK);
	} else {
		dap_resp_add_byte (DAP_ERROR);
	}
}

void
fpdu_vendor_extension_get_port_count (void) {
	dap_resp_add_byte (NUMBER_OF_SWD_PORTS);
	dap_resp_add_byte (DAP_OK);
}

void
fpdu_vendor_extension_set_swclk_state (void) {
	int state = dap_req_get_byte ();
	uint8_t result = DAP_OK;
	
	switch (state) {
		case 0:
			// force SWCLK low
			DUBUG_UNIT_SWCLK_TCK_out ();
			DUBUG_UNIT_SWCLK_TCK_clr ();
		break;
		
		case 1:
			// release SWCLK
			DUBUG_UNIT_SWCLK_TCK_in ();
		break;
		
		default:
			result = DAP_ERROR;
		break;
	}
	
	dap_resp_add_byte (result);
}

void
fpdu_vendor_extension_selected_swo (void) {
	dap_resp_add_byte (DUBUG_UNIT_SELECTED_SWO_UART ()); 
	dap_resp_add_byte (DAP_OK);
}

void
write_state (int active) {
    if (active ^ HAL_GPIO_FW1_nRESET_active_state)
      PORT->Group[HAL_GPIO_PORTA].OUTCLR.reg = (1 << 17);
    else	
      PORT->Group[HAL_GPIO_PORTA].OUTSET.reg = (1 << 17);
 }
  
void
fpdu_vendor_extension_reset_action (void) {
	uint8_t action = dap_req_get_byte ();
	
	DUBUG_UNIT_nRESET_active (action);

	dap_resp_add_byte (DAP_OK);
}

void
fpdu_vendor_extension_target_power_action (void) {
	uint8_t action = dap_req_get_byte ();
	UNUSED(action);
	#ifdef BOARD_HAS_TARGET_POWER
	switch (action) {
		case HAL_GPIO_PIN_INACTIVE:
			HAL_GPIO_FW_POWER_ENABLE_write_state(HAL_GPIO_PIN_INACTIVE);
			DUBUG_UNIT_DISCONNECT_SWJ_PINS ();
			dap_resp_add_byte (DAP_OK);
		break;
		
		case HAL_GPIO_PIN_ACTIVE:
			HAL_GPIO_FW_POWER_ENABLE_write_state(HAL_GPIO_PIN_ACTIVE);
			dap_resp_add_byte (DAP_OK);
		break;
		
		default:
			dap_resp_add_byte (DAP_ERROR);
		break;
	}
	#endif
}

void
fpdu_vendor_extension_reset_pin_state (void) {
	dap_resp_add_byte (DUBUG_UNIT_nRESET_read ());
}

void
fpdu_vendor_extension_target_power_state (void) {
	dap_resp_add_byte (DUBUG_UNIT_TARGET_POWER_PIN_active ());
}

#ifdef HAS_FLASH_PROGRAMMER_PORT

#define FPGA_OK	0x70

void
dbu_vendor_extension_flash_programmer_connect (void) {
	uint8_t buffer[4];
	byte_buffer_t id = def_byte_buffer (buffer,sizeof(buffer));

	HAL_GPIO_FPGA_CRESET_out ();
	HAL_GPIO_FPGA_CRESET_write_state (HAL_GPIO_PIN_ACTIVE);

	HAL_GPIO_FPGA_SS_write_state (HAL_GPIO_PIN_INACTIVE);
	HAL_GPIO_FPGA_SS_out ();

	HAL_SPI_FPGA_enable ();
	flash_wakeup ();
	flash_get_chip_id (id);
	dap_resp_add_byte (FPGA_OK);
}

void
dbu_vendor_extension_flash_programmer_disconnect (void) {
	HAL_SPI_FPGA_disable ();
	HAL_GPIO_FPGA_SS_in ();
	HAL_GPIO_FPGA_CRESET_in ();
	dap_resp_add_byte (FPGA_OK);
}

//
// chip id
//
void
dbu_vendor_extension_flash_programmer_get_memory_info (void) {
	uint8_t buffer[4];
	byte_buffer_t id = def_byte_buffer (buffer,sizeof(buffer));

	if (flash_get_chip_id (id) == 4) {
		dap_resp_add_byte (FPGA_OK);
		dap_resp_add_byte (buffer[0]);
		dap_resp_add_byte (buffer[1]);
		dap_resp_add_byte (buffer[2]);
		dap_resp_add_byte (buffer[3]);
	} else {
		dap_resp_add_byte (DAP_ERROR);
	}
}

//
//	begin block to end block
//
//
void
dbu_vendor_extension_flash_programmer_partial_erase (void) {
	uint16_t first_block = dap_req_get_uint16 ();
	uint16_t last_block = dap_req_get_uint16 ();
	
	uint16_t count = flash_partial_erase (first_block,last_block);
	
	dap_resp_add_byte (FPGA_OK);
	dap_resp_add_uint16 (count);
}

void
dbu_vendor_extension_flash_programmer_begin_write (void) {
	uint32_t begin = dap_req_get_uint32 ();
	if (flash_begin_write (begin)) {
		dap_resp_add_byte (FPGA_OK);
		dap_resp_add_word (begin);
	} else {
		dap_resp_add_byte (DAP_ERROR);
		dap_resp_add_word (0);
	}
}

void
dbu_vendor_extension_flash_programmer_write_chunk (void) {
	uint8_t size = dap_req_get_byte ();
	uint8_t const *data = dap_req_get_bytes (size);
	if (data != NULL) {
		uint8_t status = flash_write_chunk (data,size);
		if (status == 0) {
			dap_resp_add_byte (FPGA_OK);
			dap_resp_add_byte (0);
		} else {
			dap_resp_add_byte (DAP_ERROR);
			dap_resp_add_byte (status);
		}
	} else {
		dap_resp_add_byte (DAP_ERROR);
		dap_resp_add_byte (data[0]);
	}
}

void
dbu_vendor_extension_flash_programmer_end_write (void) {
	dap_resp_add_byte (FPGA_OK);
	dap_resp_add_word (flash_end_write ());
}

void
dbu_vendor_extension_flash_programmer_read (void) {
	uint32_t address = dap_req_get_uint32 ();
	uint8_t size = dap_req_get_byte ();

	if (size < (DUBUG_UNIT_PACKET_SIZE - 1)) {
		uint8_t data[DUBUG_UNIT_PACKET_SIZE] = {0};
		flash_read_content (address,def_byte_buffer (data,size));
		dap_resp_add_byte (FPGA_OK);
		dap_resp_add_byte (size);
		dap_resp_add_bytes (data,size);
	} else {
		dap_resp_add_byte (DAP_ERROR);
		dap_resp_add_byte (size);
	}
}
#endif /* HAS_FLASH_PROGRAMMER_PORT */

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




