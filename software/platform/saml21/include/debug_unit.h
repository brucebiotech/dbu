/*
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _feather_plus_debug_unit_H_
#define _feather_plus_debug_unit_H_
#include <io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>

#include "saml21.h"
#include "cpu/nvm_data.h"


#define LOWEST_INTERRUPT_PRIORITY		((1 << __NVIC_PRIO_BITS) - 1)

#define EVENT_LOOP_INTERRUPT_PRIORITY	LOWEST_INTERRUPT_PRIORITY				// 3
#define USB_INTERRUPT_PRIORITY			(LOWEST_INTERRUPT_PRIORITY - 1)		// 2
#define UART_INTERRUPT_PRIORITY			(LOWEST_INTERRUPT_PRIORITY - 2)		// 1
#define HIGHEST_INTERRUPT_PRIORITY		(LOWEST_INTERRUPT_PRIORITY - 3)		// 0
#define NUMBER_OF_INTERRUPT_VECTORS		(PERIPH_COUNT_IRQn + 16)

#define ENABLE_INTERRUPTS	\
	do {	\
		__DMB();	\
		__enable_irq();	\
	} while (0)

#define DISABLE_INTERRUPTS	\
	do {	\
		__disable_irq();	\
		__DMB();	\
	} while (0)


#define DUBUG_UNIT_DEFAULT_PORT        DAP_PORT_SWD
#define DUBUG_UNIT_DEFAULT_CLOCK       1000000 // Hz
#define DUBUG_UNIT_PACKET_SIZE         64
#define DUBUG_UNIT_PACKET_COUNT        1
#define DUBUG_UNIT_JTAG_DEV_COUNT      8
#define DUBUG_UNIT_SER_NUM_STR			usb_serial_number
#define DUBUG_UNIT_CMSIS_DAP_VER_STR   "1.3.0"
#ifdef __SAML21E18B__
# define DUBUG_UNIT_UART_BUFFER_SIZE	4096 //8000
#else
# define DUBUG_UNIT_UART_BUFFER_SIZE	(4096 - 1200)
#endif
#define SWO_UART_BIT_RATE					115200

#define DUBUG_UNIT_VENDOR_STR          "BBT"
#define DUBUG_UNIT_PRODUCT_STR         "fizzit (CMSIS-DAP)"	// must contain "CMSIS-DAP"
#define DUBUG_UNIT_VENDOR_ID				0x1209
#define DUBUG_UNIT_PRODUCT_ID				0x7042

extern char usb_serial_number[];

#ifndef DUBUG_UNIT_PERFORMANCE_ATTR
# define DUBUG_UNIT_PERFORMANCE_ATTR    __attribute__((section(".ramfunc")))
#endif

// A value at which dap_clock_test() produces 1 kHz output on the SWCLK pin
#define DUBUG_UNIT_DELAY_CONSTANT      8000

// A threshold for switching to fast clock (no added delays)
// This is the frequency produced by dap_clock_test(1) on the SWCLK pin
#define DUBUG_UNIT_FAST_CLOCK          1200000 // Hz


#include "uart_fifo.h"
void DUBUG_UNIT_DELAY (uint32_t);


#include "pins.h"
#include "usb.h"
#include "jtag.h"
#include "cmsis_dap.h"
#include "swo.h"


//-----------------------------------------------------------------------------
__attribute__((always_inline))
static inline void DUBUG_UNIT_DELAY_LOOP (uint32_t cycles)
{
  asm volatile (
    "1: sub %[cycles], %[cycles], #1 \n"
    "   bne 1b \n"
    : [cycles] "+l"(cycles)
  );
}


#ifdef IMPLEMENT_FPDU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------
typedef struct PACK_STRUCTURE {
	IO_STRUCT_MEMBERS

} device_io_t;

void
irq_handler_pend_sv (void) {
	io_t *io = get_device_io ();
	while (io_do_next_event (io));
}

static void
samd21_signal_event_pending (io_t *io) {
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

static void
samd21_wait_for_interrupt (io_t *io) {
	__WFI ();
}

static uint32_t
samd21_enter_critical_section (io_t *io) {
	uint32_t interrupts_were_enabled = !(__get_PRIMASK() & 0x1);
	DISABLE_INTERRUPTS;
	return interrupts_were_enabled;
}

static void
samd21_exit_critical_section (io_t *io,uint32_t were_enabled) {
	if (were_enabled) {
		ENABLE_INTERRUPTS;
	}
}

device_io_t*
initialise_device_io (void) {
	static const io_implementation_t implementation = {
		SPECIALISE_IO_IMPLEMENTATION()
		.signal_event_pending = samd21_signal_event_pending,
		.wait_for_interrupt = samd21_wait_for_interrupt,
		.enter_critical_section = samd21_enter_critical_section,
		.exit_critical_section = samd21_exit_critical_section,
	};
	static device_io_t dio = {
		.implementation = &implementation,
	};

	initialise_io ((io_t*) &dio);

	NVIC_SetPriority (PendSV_IRQn,EVENT_LOOP_INTERRUPT_PRIORITY);
		
	NVIC_SetPriority (USB_IRQn,USB_INTERRUPT_PRIORITY);
	NVIC_SetPriority (SERCOM0_IRQn,UART_INTERRUPT_PRIORITY);
	NVIC_SetPriority (SERCOM1_IRQn,UART_INTERRUPT_PRIORITY);
	NVIC_SetPriority (SERCOM2_IRQn,UART_INTERRUPT_PRIORITY);
	NVIC_SetPriority (SERCOM3_IRQn,UART_INTERRUPT_PRIORITY);
	NVIC_SetPriority (SERCOM4_IRQn,UART_INTERRUPT_PRIORITY);
	NVIC_SetPriority (SERCOM5_IRQn,UART_INTERRUPT_PRIORITY);
	
	return &dio;
}

io_t*
get_device_io (void) {
	static device_io_t *dio = NULL;
	if (dio == NULL) {
		dio = initialise_device_io ();
	}
	return (io_t*) dio;
}


char usb_serial_number[33];

void
initialise_usb_serial_number (void) {
	uint32_t wuid[4];
	uint8_t *uid = (uint8_t*) wuid;

	wuid[0] = *(volatile uint32_t*)0x0080a00c;
	wuid[1] = *(volatile uint32_t*)0x0080a040;
	wuid[2] = *(volatile uint32_t*)0x0080a044;
	wuid[3] = *(volatile uint32_t*)0x0080a048;

	
	for (int i = 0, d = 0; i < 16; i++) {
		usb_serial_number[d++] = "0123456789ABCDEF"[uid[i] & 0xf];
		usb_serial_number[d++] = "0123456789ABCDEF"[uid[i] >> 4];
	}
	
	usb_serial_number[32] = 0;
}

void
_initialise_usb_serial_number (void) {

//	memcpy (usb_serial_number,"0123456789ABCDEF",16);
	
	usb_serial_number[16] = 0;
}

void
DUBUG_UNIT_DELAY (uint32_t cycles) {
	DUBUG_UNIT_DELAY_LOOP (cycles);
}


struct dap_info_strings {
	int    id;
	char   * const str;
};

static const struct dap_info_strings dap_info_strings[] = {
	#ifdef DUBUG_UNIT_VENDOR_STR
	{ DAP_INFO_VENDOR,        DUBUG_UNIT_VENDOR_STR },
	#endif
	#ifdef DUBUG_UNIT_PRODUCT_STR
	{ DAP_INFO_PRODUCT,       DUBUG_UNIT_PRODUCT_STR },
	#endif
	#ifdef DUBUG_UNIT_SER_NUM_STR
	{ DAP_INFO_SER_NUM,       DUBUG_UNIT_SER_NUM_STR },
	#endif
	#ifdef DUBUG_UNIT_CMSIS_DAP_VER_STR
	{ DAP_INFO_CMSIS_DAP_VER, DUBUG_UNIT_CMSIS_DAP_VER_STR },
	#endif
	#ifdef DUBUG_UNIT_DEVICE_VENDOR_STR
	{ DAP_INFO_DEVICE_VENDOR, DUBUG_UNIT_DEVICE_VENDOR_STR },
	#endif
	#ifdef DUBUG_UNIT_DEVICE_NAME_STR
	{ DAP_INFO_DEVICE_NAME,   DUBUG_UNIT_DEVICE_NAME_STR },
	#endif
	#ifdef DUBUG_UNIT_BOARD_VENDOR_STR
	{ DAP_INFO_BOARD_VENDOR,  DUBUG_UNIT_BOARD_VENDOR_STR },
	#endif
	#ifdef DUBUG_UNIT_BOARD_NAME_STR
	{ DAP_INFO_BOARD_NAME,    DUBUG_UNIT_BOARD_NAME_STR },
	#endif
	#ifdef DUBUG_UNIT_FW_VER_STR
	{ DAP_INFO_FW_VER,        DUBUG_UNIT_FW_VER_STR },
	#endif
};


//-----------------------------------------------------------------------------
void
cmsis_dap_debug_unit_info (void) {
	int index = dap_req_get_byte ();

	if (DAP_INFO_CAPABILITIES == index) {
		int cap = DAP_CAP_SWD;
		#ifdef DUBUG_UNIT_ENABLE_JTAG
		cap |= DAP_CAP_JTAG;
		#endif
				
		dap_resp_add_byte(1);
		dap_resp_add_byte(cap);
	} else if (DAP_INFO_PACKET_COUNT == index) {
		dap_resp_add_byte(1);
		dap_resp_add_byte(DUBUG_UNIT_PACKET_COUNT);
	} else if (DAP_INFO_PACKET_SIZE == index) {
		dap_resp_add_byte(2);
		dap_resp_add_byte(DUBUG_UNIT_PACKET_SIZE & 0xff);
		dap_resp_add_byte((DUBUG_UNIT_PACKET_SIZE >> 8) & 0xff);
	} else {
		dap_resp_add_byte(0); // Size placeholder

		for (int i = 0; i < ARRAY_SIZE(dap_info_strings); i++) {
			if (dap_info_strings[i].id == index) {
				const char *str = dap_info_strings[i].str;

				while (*str) {
					dap_resp_add_byte(*str++);
				}
				dap_resp_add_byte(0);
				dap_resp_set_byte(1, dap_resp_get_pointer () - 2);
				break;
			}
		}
	}
}


#endif /* IMPLEMENT_FPDU */
#endif // _DUBUG_UNIT_H_
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2016-2022, Alex Taradov <alex@taradov.com>. All rights reserved.
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





