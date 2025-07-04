/*
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _cmsis_dap_uart_fifo_h_
#define _cmsis_dap_uart_fifo_h_

typedef struct PACK {
	volatile uint16_t	wr;
	volatile uint16_t	rd;
	uint8_t data[DUBUG_UNIT_UART_BUFFER_SIZE];
} uart_fifo_t;

static inline bool
fifo_read (uart_fifo_t *fifo,uint8_t *byte) {
	bool r = false;

	if (fifo->rd != fifo->wr) {
		*byte = fifo->data[fifo->rd];
		fifo->rd = (fifo->rd + 1) % DUBUG_UNIT_UART_BUFFER_SIZE;
		r = true;
	}
	
	return r;
}

static inline void
fifo_write (uart_fifo_t *fifo,uint8_t byte) {
	uint16_t n = (fifo->wr + 1) % DUBUG_UNIT_UART_BUFFER_SIZE;
	fifo->data[fifo->wr] = byte;
	fifo->wr = n;//(fifo->wr + 1) % DUBUG_UNIT_UART_BUFFER_SIZE;
}

void initialise_uart_fifo (uart_fifo_t*);
uint32_t fifo_count (uart_fifo_t*);

#ifdef IMPLEMENT_FPDU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

uint32_t
fifo_count (uart_fifo_t *fifo) {
	return ((
			(fifo->wr + DUBUG_UNIT_UART_BUFFER_SIZE) - fifo->rd)
		%	DUBUG_UNIT_UART_BUFFER_SIZE
	);
}

void
initialise_uart_fifo (uart_fifo_t *fifo) {
	fifo->rd = 0;
	fifo->wr = 0;
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






