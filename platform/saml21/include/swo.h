/*
 *
 * there is a SWO uart associated with each pin set
 *
 * the active uart is selected along side the active pin set
 *
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _debug_unit_swo_h_
#define _debug_unit_swo_h_

struct swo_uart {
	uart_fifo_t *fifo;
	
	union {
		uint32_t all;
		struct {
			uint32_t enable_receive:1;
			uint32_t :3;
			uint32_t enable_transmit:1;
			uint32_t :27;
		} bit;
	} control;
	
	void (*disable) (void);
	void (*enable) (void);
};



#if defined(BOARD_iKIT_v1)

HAL_GPIO_PIN (FZ1_SWO,			A,16,  0)	// 
HAL_GPIO_PIN (FZ2_SWO,			A, 8,  0)
HAL_GPIO_PIN (FZ3_SWO,			A, 4,  0)	// 
HAL_GPIO_PIN (FZ4_SWO,			A,22,  0)

HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ1_SWO,SERCOM1,PORT_PMUX_PMUXE_C,SERCOM1_IRQn,0)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ2_SWO,SERCOM2,PORT_PMUX_PMUXE_D,SERCOM2_IRQn,0)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ3_SWO,SERCOM0,PORT_PMUX_PMUXE_D,SERCOM0_IRQn,0)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ4_SWO,SERCOM3,PORT_PMUX_PMUXE_C,SERCOM3_IRQn,0)

#define SERCOM0_SWO_PINS	FZ3_PINS
#define SERCOM1_SWO_PINS	FZ1_PINS
#define SERCOM2_SWO_PINS	FZ2_PINS
#define SERCOM3_SWO_PINS	FZ4_PINS


#elif defined(BOARD_iKIT_v2)

HAL_GPIO_PIN (FZ1_SWO,			A, 8,  0)	// S2
HAL_GPIO_PIN (FZ2_SWO,			A, 4,  0)	// S0
HAL_GPIO_PIN (FZ3_SWO,			A, 0,  0)	// S1
HAL_GPIO_PIN (FZ4_SWO,			A,16,  0)	// S3

HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ1_SWO,SERCOM2,PORT_PMUX_PMUXE_D,SERCOM2_IRQn,0)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ2_SWO,SERCOM0,PORT_PMUX_PMUXE_D,SERCOM0_IRQn,0)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ3_SWO,SERCOM1,PORT_PMUX_PMUXE_D,SERCOM1_IRQn,0)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ4_SWO,SERCOM3,PORT_PMUX_PMUXE_D,SERCOM3_IRQn,0)

#define SERCOM0_SWO_PINS	FZ2_PINS
#define SERCOM1_SWO_PINS	FZ3_PINS
#define SERCOM2_SWO_PINS	FZ1_PINS
#define SERCOM3_SWO_PINS	FZ4_PINS


#elif defined(BOARD_iFPDU_v1)

// can RX on any pad!

HAL_GPIO_PIN (FZ1_SWO,			A,19,  0)	// 1
HAL_GPIO_PIN (FZ2_SWO,			A,22,  0)	// 3
HAL_GPIO_PIN (FZ3_SWO,			A, 8,  0)	// 2
HAL_GPIO_PIN (FZ4_SWO,			A, 7,  0)	// 0

HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ1_SWO,SERCOM1,PORT_PMUX_PMUXE_C,SERCOM1_IRQn,3)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ2_SWO,SERCOM3,PORT_PMUX_PMUXE_D,SERCOM3_IRQn,0)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ3_SWO,SERCOM2,PORT_PMUX_PMUXE_D,SERCOM2_IRQn,0)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ4_SWO,SERCOM0,PORT_PMUX_PMUXE_D,SERCOM0_IRQn,3)


#define SERCOM0_SWO_PINS	FZ4_PINS
#define SERCOM1_SWO_PINS	FZ1_PINS
#define SERCOM2_SWO_PINS	FZ3_PINS
#define SERCOM3_SWO_PINS	FZ2_PINS

#elif defined(BOARD_DBU_v1)

// can RX on any pad!

HAL_GPIO_PIN (FZ1_SWO,			A,19,  0)	// 1
HAL_GPIO_PIN (FZ2_SWO,			A, 8,  0)	// 3
HAL_GPIO_PIN (FZ3_SWO,			A, 8,  0)	// 2
HAL_GPIO_PIN (FZ4_SWO,			A, 7,  0)	// 0

HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ1_SWO,SERCOM1,PORT_PMUX_PMUXE_C,SERCOM1_IRQn,3)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ2_SWO,SERCOM3,PORT_PMUX_PMUXE_D,SERCOM3_IRQn,0)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ3_SWO,SERCOM2,PORT_PMUX_PMUXE_D,SERCOM2_IRQn,0)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ4_SWO,SERCOM0,PORT_PMUX_PMUXE_D,SERCOM0_IRQn,3)


#define SERCOM0_SWO_PINS	FZ4_PINS
#define SERCOM1_SWO_PINS	FZ1_PINS
#define SERCOM2_SWO_PINS	FZ3_PINS
#define SERCOM3_SWO_PINS	FZ2_PINS

///////////////////////////////////////////////////////////////////////////////
//
#elif defined(BOARD_FIZZIT_V1)
//
///////////////////////////////////////////////////////////////////////////////

HAL_GPIO_PIN (FZ1_SWO,			A, 1,  0)	// 1
HAL_GPIO_PIN (FZ2_SWO,			A, 9,  0)	// 2
HAL_GPIO_PIN (FZ3_SWO,			A,13,  0)	// 4
HAL_GPIO_PIN (FZ4_SWO,			A,17,  0)	// 3
HAL_GPIO_PIN (FZ5_SWO,			A,23,  0)	// 5

HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ1_SWO,SERCOM1,PORT_PMUX_PMUXE_D,SERCOM1_IRQn,1)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ2_SWO,SERCOM2,PORT_PMUX_PMUXE_C,SERCOM2_IRQn,1)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ3_SWO,SERCOM4,PORT_PMUX_PMUXE_D,SERCOM4_IRQn,1)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ4_SWO,SERCOM3,PORT_PMUX_PMUXE_D,SERCOM3_IRQn,1)
HAL_SCOM_UART_INLINE_FUNCTIONS_D (FZ5_SWO,SERCOM5,PORT_PMUX_PMUXE_D,SERCOM5_IRQn,1)

#define SERCOM1_SWO_PINS	FZ1_PINS
#define SERCOM2_SWO_PINS	FZ2_PINS
#define SERCOM3_SWO_PINS	FZ4_PINS
#define SERCOM4_SWO_PINS	FZ3_PINS
#define SERCOM5_SWO_PINS	FZ5_PINS

///////////////////////////////////////////////////////////////////////////////
//
#elif defined(BOARD_FIZZIT_MDU_V1)
//
///////////////////////////////////////////////////////////////////////////////

HAL_GPIO_PIN (FZ1_SWO,			A, 1,  0)	// 1
HAL_GPIO_PIN (FZ2_SWO,			A, 9,  0)	// 2
HAL_GPIO_PIN (FZ3_SWO,			A,13,  0)	// 4
HAL_GPIO_PIN (FZ4_SWO,			A,17,  0)	// 3
HAL_GPIO_PIN (FZ5_SWO,			A,22,  0)	// 5

HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ1_SWO,SERCOM1,PORT_PMUX_PMUXE_D,SERCOM1_IRQn,1)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ2_SWO,SERCOM2,PORT_PMUX_PMUXE_C,SERCOM2_IRQn,1)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ3_SWO,SERCOM4,PORT_PMUX_PMUXE_D,SERCOM4_IRQn,1)
HAL_SCOM_UART_INLINE_FUNCTIONS_C (FZ4_SWO,SERCOM3,PORT_PMUX_PMUXE_D,SERCOM3_IRQn,1)

// workaround, SWO needs to be on pad 1
HAL_SCOM_UART_INLINE_FUNCTIONS_D (FZ5_SWO,SERCOM5,PORT_PMUX_PMUXE_D,SERCOM5_IRQn,0)
//HAL_SCOM_UART_INLINE_FUNCTIONS_D (FZ5_SWO,SERCOM5,PORT_PMUX_PMUXE_D,SERCOM5_IRQn,1)

#define SERCOM1_SWO_PINS	FZ1_PINS
#define SERCOM2_SWO_PINS	FZ2_PINS
#define SERCOM3_SWO_PINS	FZ4_PINS
#define SERCOM4_SWO_PINS	FZ3_PINS
#define SERCOM5_SWO_PINS	FZ5_PINS

#else
# error "need board define"
#endif




extern struct swo_uart *active_swo_uart;

#ifdef IMPLEMENT_FPDU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

//
// only ever one uart active, use a single buffer
//
static uart_fifo_t swo_uart_1_fifo = {0,0,{0}};
static uart_fifo_t swo_uart_2_fifo = {0,0,{0}};
static uart_fifo_t swo_uart_3_fifo = {0,0,{0}};
static uart_fifo_t swo_uart_4_fifo = {0,0,{0}};

static void
fz1_swo_disable (void) {
	HAL_UART_FZ1_SWO_disable ();
}

static void
fw1_swo_enable (void) {
	HAL_UART_FZ1_SWO_enable ();
}

static void
fw2_swo_disable (void) {
	// call this disable
	HAL_UART_FZ2_SWO_disable ();
}

static void
fw2_swo_enable (void) {
	// call this enable
	HAL_UART_FZ2_SWO_enable ();
}

static void
fw3_swo_disable (void) {
	// call this disable
	HAL_UART_FZ2_SWO_disable ();
}

static void
fw3_swo_enable (void) {
	// call this enable
	HAL_UART_FZ3_SWO_enable ();
}

static void
fw4_swo_disable (void) {
	// call this disable
	HAL_UART_FZ4_SWO_disable ();
}

static void
fw4_swo_enable (void) {
	// call this enable
	HAL_UART_FZ4_SWO_enable ();
}

#if NUMBER_OF_SWD_PORTS > 4

static uart_fifo_t swo_uart_5_fifo = {0,0,{0}};

static void
fz5_swo_disable (void) {
	// call this enable
	HAL_UART_FZ5_SWO_enable ();
}

static void
fw5_swo_disable (void) {
	// call this disable
	HAL_UART_FZ5_SWO_disable ();
}

#endif

struct swo_uart swo_uarts [] = {
	/* fz1 */ 
	{
		.fifo = &swo_uart_1_fifo,
		.enable = fw1_swo_enable,
		.disable = fz1_swo_disable,
		.control.all = 0,
	},
	/* fz2 */ 
	{
		.fifo = &swo_uart_2_fifo,
		.enable = fw2_swo_enable,
		.disable = fw2_swo_disable,
		.control.all = 0,
	},
	/* fz3*/ 
	{
		.fifo = &swo_uart_3_fifo,
		.enable = fw3_swo_enable,
		.disable = fw3_swo_disable,
		.control.all = 0,
	},
	/* fz4 */ 
	{
		.fifo = &swo_uart_4_fifo,
		.enable = fw4_swo_enable,
		.disable = fw4_swo_disable,
		.control.all = 0,
	},
	#if NUMBER_OF_SWD_PORTS > 4
	/* fz5 */ 
	{
		.fifo = &swo_uart_5_fifo,
		.enable = fz5_swo_disable,
		.disable = fw5_swo_disable,
		.control.all = 0,
	},
	#endif
};

struct swo_uart *active_swo_uart = NULL;

io_ticket_t swo_data_available;

bool swo_sending = false;

uint32_t byte_count_u = 0;
uint32_t byte_count_s = 0;

void
swo_send_callback (void) {
	swo_sending = false;

	/*
	want this but causes character loss
	*/
	io_enqueue_event (
		get_device_io (),&swo_data_available
	);
}

union PACK {
	uint8_t u8[64];
	uint32_t u32[16];
} swo_send_buffer = {
	.u8 = {
		ID_CMSI_DAP_UART_TRANSFER,0,0,0,0,0
	},
};

void
swo_data_available_event (io_ticket_t *ev) {
	if (!swo_sending) {	
		int limit = MIN (64 - 6,fifo_count (active_swo_uart->fifo));
		if (limit > 0) {
			
			uint8_t *cursor = swo_send_buffer.u8 + 6;
			uint8_t *end = cursor + limit;
			do {
				fifo_read (active_swo_uart->fifo,cursor);
				cursor++;
			} while (cursor < end);
			
			swo_send_buffer.u8[4] = limit;
			
			byte_count_s += limit;
			
			usb_send (
				APP_EP_SEND,swo_send_buffer.u8,DUBUG_UNIT_PACKET_SIZE,swo_send_callback
			);
			
			swo_sending = true;
		}
	}
}

void
initialise_swo (void) {

	initialise_io_event_ticket (
		&swo_data_available,swo_data_available_event,NULL
	);

	HAL_GPIO_FZ4_SWO_in ();
		
	HAL_UART_FZ1_SWO_initialise ();
	HAL_UART_FZ2_SWO_initialise ();
	HAL_UART_FZ3_SWO_initialise ();
	HAL_UART_FZ4_SWO_initialise ();

	#if NUMBER_OF_SWD_PORTS > 4
	HAL_UART_FZ5_SWO_initialise ();
	#endif
	
	//
	// select default uart
	//
	
	active_swo_uart = swo_uarts + FZ1_PINS;
}

int
DUBUG_UNIT_SELECT_SWO_UART (int index) {
	if (
			(index >= 0)
		&&	(index < MAX_PIN_SETS)
	) {
		active_swo_uart = swo_uarts + index;
		return 0;
	} else {
		return -1;
	}
}

int
DUBUG_UNIT_SELECTED_SWO_UART (void) {
	return (active_swo_uart - swo_uarts);
}

void
DUBUG_UNIT_ENABLE_SWO_UART (void) {
	swo_sending = false;
	initialise_uart_fifo (active_swo_uart->fifo);
	active_swo_uart->enable ();
}

void
DUBUG_UNIT_DISABLE_SWO_UART (void) {
	io_dequeue_event (get_device_io (),&swo_data_available);
	active_swo_uart->disable ();
}

void
DUBUG_UNIT_FLUSH_SWO_UART (void) {
	initialise_uart_fifo (active_swo_uart->fifo);
}

void
DUBUG_UNIT_CONFIGURE_SWO_UART (uint8_t settings,uint32_t *bit_rate) {
	*bit_rate = SWO_UART_BIT_RATE;
}

uint32_t
DUBUG_UNIT_SWO_UART_RECEIVE_FIFO_COUNT (void) {
	return fifo_count (active_swo_uart->fifo);
}

uint32_t
DUBUG_UNIT_SWO_RECEIVE_FIFO_COUNT (uint32_t index) {
	if (index < MAX_PIN_SETS) {
		return fifo_count (swo_uarts[index].fifo);
	} else {
		return 0;
	}
}

bool
DUBUG_UNIT_SWO_UART_READ_BYTE (uint8_t *byte) {
	if (fifo_read (active_swo_uart->fifo,byte)) {
		return true;
	} else {
		return false;
	}
}

void
report_uart_receive_error (struct swo_uart *swo,uint32_t status) {
	// report somehow...
	if (status & (
				SERCOM_USART_STATUS_BUFOVF
			|	SERCOM_USART_STATUS_FERR
			|	SERCOM_USART_STATUS_PERR
		)
	) {
		
	}
}

//
// we just keep writing to the uart fifos
//

DUBUG_UNIT_PERFORMANCE_ATTR void
swo_irq_handler (Sercom *scom,struct swo_uart *uart) {
	uint32_t flags = scom->USART.INTFLAG.reg;
	uint32_t status = scom->USART.STATUS.reg;

	scom->USART.STATUS.reg = status;
	
	if (flags & SERCOM_USART_INTFLAG_ERROR) {
		scom->USART.INTFLAG.reg = SERCOM_USART_INTFLAG_ERROR;
		report_uart_receive_error (uart,status);
	}
	
	if (flags & SERCOM_USART_INTFLAG_RXC) {
		// need a 16bit read
		volatile uint16_t byte = scom->USART.DATA.reg;
		
		if ((byte & 0xff) != 0) {
			fifo_write (uart->fifo,byte);
			
			//
			// only if read enabled (not for transfer)
			//
			
			//io_enqueue_event (
			//	get_device_io (),&swo_data_available
			//);
			byte_count_u ++;
		} else {
			byte_count_s ++;
			fifo_write (uart->fifo,'?');
			if ((byte_count_s & 0xf) == 0) {
				fifo_write (uart->fifo,'\n');
			}
		}
	}
}

#ifdef SERCOM0_SWO_PINS
DUBUG_UNIT_PERFORMANCE_ATTR void
irq_handler_sercom0 (void) {
	swo_irq_handler (SERCOM0,swo_uarts + SERCOM0_SWO_PINS);
}
#endif

DUBUG_UNIT_PERFORMANCE_ATTR void
irq_handler_sercom1 (void) {
	swo_irq_handler (SERCOM1,swo_uarts + SERCOM1_SWO_PINS);
}

DUBUG_UNIT_PERFORMANCE_ATTR void
irq_handler_sercom2 (void) {
	swo_irq_handler (SERCOM2,swo_uarts + SERCOM2_SWO_PINS);
}

DUBUG_UNIT_PERFORMANCE_ATTR void
irq_handler_sercom3 (void) {
	swo_irq_handler (SERCOM3,swo_uarts + SERCOM3_SWO_PINS);
}

#ifdef SERCOM4_SWO_PINS
DUBUG_UNIT_PERFORMANCE_ATTR void
irq_handler_sercom4 (void) {
	swo_irq_handler (SERCOM4,swo_uarts + SERCOM4_SWO_PINS);
}
#endif

#ifdef SERCOM5_SWO_PINS
DUBUG_UNIT_PERFORMANCE_ATTR void
irq_handler_sercom5 (void) {
	swo_irq_handler (SERCOM5,swo_uarts + SERCOM5_SWO_PINS);
}
#endif


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





