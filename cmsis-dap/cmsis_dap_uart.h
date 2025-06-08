/*
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _fpdu_cmsis_dap_uart_H_
#define _fpdu_cmsis_dap_uart_H_
#ifdef IMPLEMENT_FPDU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

static void
cmsis_dap_uart_transport (void) {
	uint8_t control = dap_req_get_byte ();
	switch (control) {
		case 0:	//default
			dap_resp_add_byte (DAP_OK);
		break;
		
		case 1:
			// USB COM not supported
			dap_resp_add_byte (DAP_ERROR);
		break;
		
		case 2:
			// uses cmsis dap uart
			dap_resp_add_byte (DAP_OK);
		break;
		
		default:
			dap_resp_add_byte (DAP_ERROR);
		break;
	}
}

static void
cmsis_dap_uart_configure (void) {
	uint8_t control = dap_req_get_byte ();
	uint32_t bit_rate = dap_req_get_uint32 ();
	
	DUBUG_UNIT_CONFIGURE_SWO_UART (control,&bit_rate);
	
	dap_resp_add_word (bit_rate);
	dap_resp_add_byte (DAP_OK);
}


static void
cmsis_dap_uart_control (void) {
	uint8_t control = dap_req_get_byte ();
	if (control & CMSIS_DAP_UART_CONTROL_RECEIVE_FLUSH) {
		DUBUG_UNIT_FLUSH_SWO_UART ();
	}
	
	if (control & CMSIS_DAP_UART_CONTROL_RECEIVE_ENABLE) {
		//
		// once swo is enabled, any command received needs to 
		// first disable swo before processing and responding 
		// to the command
		//
		// exception to this is the uart control command
		//
		DUBUG_UNIT_ENABLE_SWO_UART ();
	} else if (control & CMSIS_DAP_UART_CONTROL_RECEIVE_DISABLE) {
		DUBUG_UNIT_DISABLE_SWO_UART ();
	}
	
	dap_resp_add_byte (DAP_OK);
}

static void
cmsis_dap_uart_status (void) {

	// status
	dap_resp_add_byte (0);

	dap_resp_add_word (DUBUG_UNIT_SWO_UART_RECEIVE_FIFO_COUNT ());
	dap_resp_add_word (0);	// tx (to target) not supported, always 0
}

//
// only used for receive transfers from swo uart
//
// response 6 bytes + data
//
// <cmd> <status> <remainder> <rx count> <(rx count bytes)>
//
static void
cmsis_dap_uart_transfer (void) {
	uint16_t rx_count,count = 0;
	uint8_t status = 0; 	// status is state set by control message

	rx_count = dap_req_get_uint16 ();
	dap_req_get_uint16 ();	

	dap_resp_add_byte (status);	
	int remainder_ptr = dap_resp_add_uint16 (0);
	
	int count_ptr = dap_resp_add_uint16 (0);
	uint8_t byte;
	
	rx_count = MIN (rx_count,maximum_response_payload_size () - 6);
	
	do {
		if (DUBUG_UNIT_SWO_UART_READ_BYTE (&byte)) {
			dap_resp_add_byte (byte);
			count ++;
		} else {
			break;
		}
	} while (count < rx_count);

	dap_resp_set_uint16 (remainder_ptr,DUBUG_UNIT_SWO_UART_RECEIVE_FIFO_COUNT ());
	dap_resp_set_uint16 (count_ptr,count);
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




