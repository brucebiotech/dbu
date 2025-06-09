/*
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _debug_unit_swj_pins_h_
#define _debug_unit_swj_pins_h_

#include "pins/hal_gpio.h"

enum {
	FZ1_PINS	= 0,
	FZ2_PINS,
	FZ3_PINS,
	FZ4_PINS,
	FZ5_PINS,
	
//	MAX_PIN_SETS,
};

#define MAX_PIN_SETS NUMBER_OF_SWD_PORTS


typedef struct dap_connect_pin {
	void (*set) (void);
	void (*clear) (void);
	void (*in) (void);
	void (*out) (void);
	void (*write) (int);
	void (*active) (int);
	int (*read) (void);
} dap_connect_pin_t;

typedef struct dap_connect_pins {
	dap_connect_pin_t swd_sck;
	dap_connect_pin_t swd_dio;
	dap_connect_pin_t reset;
} dap_pins_t;


#if defined(BOARD_iKIT_v1)
#define BOARD_HAS_TARGET_POWER
HAL_GPIO_PIN (FW_POWER_ENABLE, A, 3,  1)

HAL_GPIO_PIN (FW1_SWCLK_TCK,	A,15,  0)
HAL_GPIO_PIN (FW1_SWDIO_TMS,	A,14,  0)
HAL_GPIO_PIN (FW1_nRESET,		A,17,  0)
HAL_GPIO_PIN (FW1_LED,			A, 1,  0)

HAL_GPIO_PIN (FW2_SWCLK_TCK,	A,10,  0)
HAL_GPIO_PIN (FW2_SWDIO_TMS,	A,11,  0)
HAL_GPIO_PIN (FW2_nRESET,		A, 9,  0)
HAL_GPIO_PIN (FW2_LED,			A, 0,  0)

HAL_GPIO_PIN (FW3_SWCLK_TCK,	A, 6,  0)
HAL_GPIO_PIN (FW3_SWDIO_TMS,	A, 5,  0)
HAL_GPIO_PIN (FW3_nRESET,		A, 7,  0)
HAL_GPIO_PIN (FW3_LED,			A, 2,  0)

HAL_GPIO_PIN (FW4_SWCLK_TCK,	A,19,  0)
HAL_GPIO_PIN (FW4_SWDIO_TMS,	A,23,  0)
HAL_GPIO_PIN (FW4_nRESET,		A,18,  0)
HAL_GPIO_PIN (FW4_LED,			A,27,  0)

#define NUMBER_OF_SWD_PORTS	4

#elif defined(BOARD_iKIT_v2)

// no power enable

HAL_GPIO_PIN (FW1_SWCLK_TCK,	A,14,  0)
HAL_GPIO_PIN (FW1_SWDIO_TMS,	B,11,  0)
HAL_GPIO_PIN (FW1_nRESET,		A,27,  0)
HAL_GPIO_PIN (FW1_LED,			B,10,  0)

HAL_GPIO_PIN (FW2_SWCLK_TCK,	B, 3,  0)
HAL_GPIO_PIN (FW2_SWDIO_TMS,	A, 7,  0)
HAL_GPIO_PIN (FW2_nRESET,		B, 2,  0)
HAL_GPIO_PIN (FW2_LED,			A,11,  0)

HAL_GPIO_PIN (FW3_SWCLK_TCK,	B, 9,  0)
HAL_GPIO_PIN (FW3_SWDIO_TMS,	B, 8,  0)
HAL_GPIO_PIN (FW3_nRESET,		A, 6,  0)
HAL_GPIO_PIN (FW3_LED,			A,10,  0)

HAL_GPIO_PIN (FW4_SWCLK_TCK,	A,20,  0)
HAL_GPIO_PIN (FW4_SWDIO_TMS,	A,21,  0)
HAL_GPIO_PIN (FW4_nRESET,		A,19,  0)
HAL_GPIO_PIN (FW4_LED,			A,18,  0)

#define NUMBER_OF_SWD_PORTS	4

#elif defined(BOARD_iFPDU_v1)
#define BOARD_HAS_TARGET_POWER
HAL_GPIO_PIN (FW_POWER_ENABLE, A, 23,  1)


HAL_GPIO_PIN (FW1_SWCLK_TCK,	A,15,  0)
HAL_GPIO_PIN (FW1_SWDIO_TMS,	A,11,  0)
HAL_GPIO_PIN (FW1_nRESET,		A,17,  0)
HAL_GPIO_PIN (FW1_LED,			A, 9,  0)

HAL_GPIO_PIN (FW2_SWCLK_TCK,	A,16,  0)
HAL_GPIO_PIN (FW2_SWDIO_TMS,	A,14,  0)
HAL_GPIO_PIN (FW2_nRESET,		A,18,  0)
HAL_GPIO_PIN (FW2_LED,			A,10,  0)

HAL_GPIO_PIN (FW3_SWCLK_TCK,	A, 4,  0)
HAL_GPIO_PIN (FW3_SWDIO_TMS,	A, 2,  0)
HAL_GPIO_PIN (FW3_nRESET,		A, 6,  0)
HAL_GPIO_PIN (FW3_LED,			A,27,  0)

HAL_GPIO_PIN (FW4_SWCLK_TCK,	A, 3,  0)
HAL_GPIO_PIN (FW4_SWDIO_TMS,	A, 1,  0)
HAL_GPIO_PIN (FW4_nRESET,		A, 5,  0)
HAL_GPIO_PIN (FW4_LED,			A, 0,  0)

#define NUMBER_OF_SWD_PORTS	4

#elif defined(BOARD_DBU_v1)
#define BOARD_HAS_TARGET_POWER
HAL_GPIO_PIN (FW_POWER_ENABLE, A, 23,  1)

HAL_GPIO_PIN (FW1_SWCLK_TCK,	A,15,  0)
HAL_GPIO_PIN (FW1_SWDIO_TMS,	A,11,  0)
HAL_GPIO_PIN (FW1_nRESET,		A,17,  0)
HAL_GPIO_PIN (FW1_LED,			A, 9,  0)

HAL_GPIO_PIN (FW2_SWCLK_TCK,	A, 3,  0)
HAL_GPIO_PIN (FW2_SWDIO_TMS,	A, 4,  0)
HAL_GPIO_PIN (FW2_nRESET,		A, 5,  0)
HAL_GPIO_PIN (FW2_LED,			A, 6,  0)

HAL_GPIO_PIN (FW3_SWCLK_TCK,	A, 3,  0)
HAL_GPIO_PIN (FW3_SWDIO_TMS,	A, 4,  0)
HAL_GPIO_PIN (FW3_nRESET,		A, 5,  0)
HAL_GPIO_PIN (FW3_LED,			A, 6,  0)

HAL_GPIO_PIN (FW4_SWCLK_TCK,	A, 3,  0)
HAL_GPIO_PIN (FW4_SWDIO_TMS,	A, 4,  0)
HAL_GPIO_PIN (FW4_nRESET,		A, 5,  0)
HAL_GPIO_PIN (FW4_LED,			A, 6,  0)

#define NUMBER_OF_SWD_PORTS	1


#elif defined(BOARD_FIZZIT_V1)

HAL_GPIO_PIN (FW1_SWCLK_TCK,	B, 2,  0)
HAL_GPIO_PIN (FW1_SWDIO_TMS,	B, 3,  0)
HAL_GPIO_PIN (FW1_nRESET,		A, 2,  0)

HAL_GPIO_PIN (FW2_SWCLK_TCK,	A,10,  0)
HAL_GPIO_PIN (FW2_SWDIO_TMS,	B,10,  0)
HAL_GPIO_PIN (FW2_nRESET,		A,11,  0)

HAL_GPIO_PIN (FW3_SWCLK_TCK,	A,15,  0)
HAL_GPIO_PIN (FW3_SWDIO_TMS,	A,14,  0)
HAL_GPIO_PIN (FW3_nRESET,		B,11,  0)

HAL_GPIO_PIN (FW4_SWCLK_TCK,	A,19,  0)
HAL_GPIO_PIN (FW4_SWDIO_TMS,	A,18,  0)
HAL_GPIO_PIN (FW4_nRESET,		A,20,  0)

HAL_GPIO_PIN (FZ5_SWCLK_TCK,	B,22,  0)
HAL_GPIO_PIN (FZ5_SWDIO_TMS,	B,23,  0)
HAL_GPIO_PIN (FZ5_nRESET,		A,27,  0)

#define NUMBER_OF_SWD_PORTS	5

HAL_GPIO_PIN (FPGA_MOSI,			A, 4,  0)
HAL_GPIO_PIN (FPGA_SCK,				A, 5,  0)
HAL_GPIO_PIN (FPGA_SS,				A, 6,  1)
HAL_GPIO_PIN (FPGA_MISO,			A, 7,  0)

// HAL_SCOM_SPI_INLINE_FUNCTIONS_C (FPGA_MOSI,SERCOM0,PORT_PMUX_PMUXE_D,SERCOM0_IRQn)

#elif defined(BOARD_FIZZIT_MDU_V1)

HAL_GPIO_PIN (FW1_SWCLK_TCK,	B, 2,  0)
HAL_GPIO_PIN (FW1_SWDIO_TMS,	B, 3,  0)
HAL_GPIO_PIN (FW1_nRESET,		A, 2,  0)

HAL_GPIO_PIN (FW2_SWCLK_TCK,	A,10,  0)
HAL_GPIO_PIN (FW2_SWDIO_TMS,	B,10,  0)
HAL_GPIO_PIN (FW2_nRESET,		A,11,  0)

HAL_GPIO_PIN (FW3_SWCLK_TCK,	A,15,  0)
HAL_GPIO_PIN (FW3_SWDIO_TMS,	A,14,  0)
HAL_GPIO_PIN (FW3_nRESET,		B,11,  0)

HAL_GPIO_PIN (FW4_SWCLK_TCK,	A,19,  0)
HAL_GPIO_PIN (FW4_SWDIO_TMS,	A,18,  0)
HAL_GPIO_PIN (FW4_nRESET,		A,20,  0)

HAL_GPIO_PIN (FZ5_SWCLK_TCK,	A,27,  0)
HAL_GPIO_PIN (FZ5_SWDIO_TMS,	B,23,  0)
HAL_GPIO_PIN (FZ5_nRESET,		A,21,  0)


#define NUMBER_OF_SWD_PORTS	5

HAL_GPIO_PIN (FPGA_MOSI,			A, 4,  0)
HAL_GPIO_PIN (FPGA_SCK,				A, 5,  0)
HAL_GPIO_PIN (FPGA_SS,				A, 6,  1)
HAL_GPIO_PIN (FPGA_MISO,			A, 7,  0)

#else
# error "need BOARD defined"
#endif

extern dap_pins_t* active_pins;
extern dap_pins_t dap_pins[];

int DUBUG_UNIT_TARGET_POWER_PIN_active ();


//
// swd sck
//	
static inline void 
DUBUG_UNIT_SWCLK_TCK_write (int value) {
	active_pins->swd_sck.write (value);
}

static inline int 
DUBUG_UNIT_SWCLK_TCK_read(void) {
	return active_pins->swd_sck.read ();
}

static inline void
DUBUG_UNIT_SWCLK_TCK_set (void) {
	active_pins->swd_sck.set ();
}

static inline void
DUBUG_UNIT_SWCLK_TCK_clr (void) {
	active_pins->swd_sck.clear ();
}

static inline void
DUBUG_UNIT_SWCLK_TCK_in (void) {
	active_pins->swd_sck.in ();
}

static inline void
DUBUG_UNIT_SWCLK_TCK_out (void) {
	active_pins->swd_sck.out ();
}

//
// swd dio
//
static inline void
DUBUG_UNIT_SWDIO_TMS_set (void) {
	active_pins->swd_dio.set ();
}

static inline void
DUBUG_UNIT_SWDIO_TMS_clr (void) {
	active_pins->swd_dio.clear ();
}

static inline void
DUBUG_UNIT_SWDIO_TMS_write (int value) {
	active_pins->swd_dio.write (value);
}

static inline int
DUBUG_UNIT_SWDIO_TMS_read (void) {
	return active_pins->swd_dio.read ();
}

static inline void
DUBUG_UNIT_SWDIO_TMS_in (void) {
	active_pins->swd_dio.in ();
}

static inline void
DUBUG_UNIT_SWDIO_TMS_out (void) {
	active_pins->swd_dio.out ();
}

//
// reset
//	
static inline void
DUBUG_UNIT_nRESET_set (void) {
	active_pins->reset.set ();
}

static inline void
DUBUG_UNIT_nRESET_clr (void) {
	active_pins->reset.clear ();
}

static inline void
DUBUG_UNIT_nRESET_write (int value) {
	active_pins->reset.write (value);
}

static inline void
DUBUG_UNIT_nRESET_active (int value) {
	active_pins->reset.active (value);
}

static inline int
DUBUG_UNIT_nRESET_read (void) {
	return active_pins->reset.read ();
}

static inline void
DUBUG_UNIT_nRESET_in (void) {
	active_pins->reset.in ();
}

static inline void
DUBUG_UNIT_nRESET_out (void) {
	active_pins->reset.out ();
}

static inline void
DUBUG_UNIT_LED (int index, int state) {
}

//-----------------------------------------------------------------------------
//
// pin ops
//	
//-----------------------------------------------------------------------------

static inline void
DUBUG_UNIT_DISCONNECT_SWJ_PINS (void) {
	DUBUG_UNIT_SWCLK_TCK_in ();
	DUBUG_UNIT_SWDIO_TMS_in ();
}

static inline void
DUBUG_UNIT_CONNECT_SWJ_PINS (void) {
	DUBUG_UNIT_SWDIO_TMS_out ();
	DUBUG_UNIT_SWDIO_TMS_set ();

	DUBUG_UNIT_SWCLK_TCK_out ();
	DUBUG_UNIT_SWCLK_TCK_set ();
}

#ifdef IMPLEMENT_FPDU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

#include "pins/fz1_pins.h"
#include "pins/fz2_pins.h"
#include "pins/fz3_pins.h"
#include "pins/fz4_pins.h"
#if NUMBER_OF_SWD_PORTS > 4
# include "pins/fz5_pins.h"
#endif

int
DUBUG_UNIT_TARGET_POWER_PIN_active () {
	#ifdef BOARD_HAS_TARGET_POWER
	return HAL_GPIO_FW_POWER_ENABLE_active();
	#else
	return false;
	#endif
}

dap_pins_t dap_pins[] = {
	/* fw1 */ 
	{
		.swd_sck = {
			.set = fw1_swclk_tck_set,
			.clear = fw1_swclk_tck_clear,
			.write = fw1_swclk_tck_write,
			.active = fw1_swclk_tck_write,
			.read = fw1_swclk_tck_read,
			.in = fw1_swclk_tck_in,
			.out = fw1_swclk_tck_out,
		},
		.swd_dio = {
			.set = fw1_swdio_set,
			.clear = fw1_swdio_clear,
			.write = fw1_swdio_write,
			.active = fw1_swdio_write,
			.read = fw1_swdio_read,
			.in = fw1_swdio_in,
			.out = fw1_swdio_out,
		},
		.reset = {
			.set = fw1_reset_set,
			.clear = fw1_reset_clear,
			.write = fw1_reset_write,
			.active = fw1_reset_active,
			.read = fw1_reset_read,
			.in = fw1_reset_in,
			.out = fw1_reset_out,
		},
	},
	/* fw2 */ 
	{
		.swd_sck = {
			.set = fw2_swclk_tck_set,
			.clear = fw2_swclk_tck_clear,
			.write = fw2_swclk_tck_write,
			.active = fw2_swclk_tck_write,
			.read = fw2_swclk_tck_read,
			.in = fw2_swclk_tck_in,
			.out = fw2_swclk_tck_out,
		},
		.swd_dio = {
			.set = fw2_swdio_set,
			.clear = fw2_swdio_clear,
			.write = fw2_swdio_write,
			.active = fw2_swdio_write,
			.read = fw2_swdio_read,
			.in = fw2_swdio_in,
			.out = fw2_swdio_out,
		},
		.reset = {
			.set = fw2_reset_set,
			.clear = fw2_reset_clear,
			.write = fw2_reset_write,
			.active = fw2_reset_active,
			.read = fw2_reset_read,
			.in = fw2_reset_in,
			.out = fw2_reset_out,
		},
	},
	/* fw3 */ 
	{
		.swd_sck = {
			.set = fw3_swclk_tck_set,
			.clear = fw3_swclk_tck_clear,
			.write = fw3_swclk_tck_write,
			.active = fw3_swclk_tck_write,
			.read = fw3_swclk_tck_read,
			.in = fw3_swclk_tck_in,
			.out = fw3_swclk_tck_out,
		},
		.swd_dio = {
			.set = fw3_swdio_set,
			.clear = fw3_swdio_clear,
			.write = fw3_swdio_write,
			.active = fw3_swdio_write,
			.read = fw3_swdio_read,
			.in = fw3_swdio_in,
			.out = fw3_swdio_out,
		},
		.reset = {
			.set = fw3_reset_set,
			.clear = fw3_reset_clear,
			.write = fw3_reset_write,
			.active = fw3_reset_active,
			.read = fw3_reset_read,
			.in = fw3_reset_in,
			.out = fw3_reset_out,
		},
	},
	/* fw4 */ 
	{
		.swd_sck = {
			.set = fw4_swclk_tck_set,
			.clear = fw4_swclk_tck_clear,
			.write = fw4_swclk_tck_write,
			.active = fw4_swclk_tck_write,
			.read = fw4_swclk_tck_read,
			.in = fw4_swclk_tck_in,
			.out = fw4_swclk_tck_out,
		},
		.swd_dio = {
			.set = fw4_swdio_set,
			.clear = fw4_swdio_clear,
			.write = fw4_swdio_write,
			.active = fw4_swdio_write,
			.read = fw4_swdio_read,
			.in = fw4_swdio_in,
			.out = fw4_swdio_out,
		},
		.reset = {
			.set = fw4_reset_set,
			.clear = fw4_reset_clear,
			.write = fw4_reset_write,
			.active = fw4_reset_active,
			.read = fw4_reset_read,
			.in = fw4_reset_in,
			.out = fw4_reset_out,
		},
	},
#if NUMBER_OF_SWD_PORTS > 4
	/* fz5 */ 
	{
		.swd_sck = {
			.set = fz5_swclk_tck_set,
			.clear = fz5_swclk_tck_clear,
			.write = fz5_swclk_tck_write,
			.active = fz5_swclk_tck_write,
			.read = fz5_swclk_tck_read,
			.in = fz5_swclk_tck_in,
			.out = fz5_swclk_tck_out,
		},
		.swd_dio = {
			.set = fz5_swdio_set,
			.clear = fz5_swdio_clear,
			.write = fz5_swdio_write,
			.active = fz5_swdio_write,
			.read = fz5_swdio_read,
			.in = fz5_swdio_in,
			.out = fz5_swdio_out,
		},
		.reset = {
			.set = fz5_reset_set,
			.clear = fz5_reset_clear,
			.write = fz5_reset_write,
			.active = fz5_reset_active,
			.read = fz5_reset_read,
			.in = fz5_reset_in,
			.out = fz5_reset_out,
		},
	},
#endif
};


dap_pins_t* active_pins = NULL;

int
DUBUG_UNIT_SELECT_SWJ_PINS (int index) {
	if (active_pins != (dap_pins + index)) {
		if (
				(index >= 0)
			&&	(index < MAX_PIN_SETS)
		) {
			DUBUG_UNIT_DISCONNECT_SWJ_PINS ();
			active_pins = dap_pins + index;
			DUBUG_UNIT_DISCONNECT_SWJ_PINS ();
			return 0;
		} else {
			return -1;
		}
	} else {
		return 0;
	}
}

int
DUBUG_UNIT_SELECTED_SWJ_PINS (void) {
	return (active_pins - dap_pins);
}

//
// called from initialise_cmsis_dap
//
void
DUBUG_UNIT_SETUP_SWJ_PINS (void) {
	active_pins = dap_pins + FZ1_PINS;
	DUBUG_UNIT_DISCONNECT_SWJ_PINS ();

	HAL_GPIO_FW1_nRESET_set ();
	HAL_GPIO_FW1_nRESET_out ();

	HAL_GPIO_FW2_nRESET_set ();
	HAL_GPIO_FW2_nRESET_out ();

	HAL_GPIO_FW3_nRESET_set ();
	HAL_GPIO_FW3_nRESET_out ();

	HAL_GPIO_FW4_nRESET_set ();
	HAL_GPIO_FW4_nRESET_out ();
}

void
DUBUG_UNIT_RESET_TARGET_FN (void) {

	if (DUBUG_UNIT_nRESET_read ()) {
		//
		// not being held in reset
		//
		DUBUG_UNIT_nRESET_set();
		DUBUG_UNIT_nRESET_out();
		DUBUG_UNIT_nRESET_clr();
		DUBUG_UNIT_DELAY (200);
		DUBUG_UNIT_nRESET_set();
		DUBUG_UNIT_nRESET_in();
	}
}

#endif /* IMPLEMENT_FPDU */
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





