/*
 *
 * (c) see end of file for license terms.
 *
 */

//-----------------------------------------------------------------------------
#define IMPLEMENT_IO
#define IMPLEMENT_FPDU
#include "debug_unit.h"


alignas(4) uint8_t app_request_buffer[DUBUG_UNIT_PACKET_SIZE];
alignas(4) uint8_t app_response_buffer[DUBUG_UNIT_PACKET_SIZE];

//-----------------------------------------------------------------------------
void
usb_send_callback (void) {
}

//-----------------------------------------------------------------------------
void
usb_receive_callback (void) {
	process_cmsis_dap_request (
		app_request_buffer,sizeof(app_request_buffer),
		app_response_buffer,sizeof(app_response_buffer)
	);
	
	usb_send (
		APP_EP_SEND, 
		app_response_buffer, 
		sizeof(app_response_buffer), 
		usb_send_callback
	);
	
	usb_recv (
		APP_EP_RECV, 
		app_request_buffer, 
		sizeof(app_request_buffer), 
		usb_receive_callback
	);
}

//-----------------------------------------------------------------------------
void
usb_configuration_callback (int config) {
	usb_recv (
		APP_EP_RECV,
		app_request_buffer,sizeof(app_request_buffer),
		usb_receive_callback
	);
	
	(void)config;
}

/*
 * ----------------------------------------------------------------------
 *
 * initialise_cpu  --
 *
 * see C:\Users\gregor\projects\old\projects\ntt\3\cpu\microchip\saml21\clocks
 *
 * ----------------------------------------------------------------------
 */
static void
initialise_cpu (void) {
	uint32_t coarse, fine;

	NVMCTRL->CTRLB.bit.MANW = 1;

	OSCCTRL->INTFLAG.reg = (
		OSCCTRL_INTFLAG_DFLLRDY
	);
	
	//
	// for 48MHz
	//
	NVMCTRL->CTRLB.bit.RWS = 2;
	PM->INTFLAG.reg = PM_INTFLAG_PLRDY;
	PM->PLCFG.bit.PLSEL = 2;
	while ((PM->INTFLAG.reg & PM_INTFLAG_PLRDY) == 0);

	coarse = NVM_READ_CAL(NVM_DFLL48M_COARSE_CAL);
	fine = 8;

	OSCCTRL->DFLLCTRL.reg = OSCCTRL_DFLLCTRL_ENABLE;	// errata
	while(!OSCCTRL->STATUS.bit.DFLLRDY);

	OSCCTRL->DFLLMUL.reg = (
			OSCCTRL_DFLLMUL_MUL(48000)
		|	OSCCTRL_DFLLMUL_FSTEP(1)
		|	OSCCTRL_DFLLMUL_CSTEP(1)
	);
	OSCCTRL->DFLLVAL.reg = (
			OSCCTRL_DFLLVAL_COARSE(coarse) 
		|	OSCCTRL_DFLLVAL_FINE(fine)
	);

	while(!OSCCTRL->STATUS.bit.DFLLRDY);
	OSCCTRL->DFLLCTRL.reg |= (
			OSCCTRL_DFLLCTRL_ENABLE
		|	OSCCTRL_DFLLCTRL_MODE
		|	OSCCTRL_DFLLCTRL_USBCRM
	);
	while(!OSCCTRL->STATUS.bit.DFLLRDY);

	//
	// now switch core clock to DFLL48M
	//
	GCLK->GENCTRL[0].reg = (
			GCLK_GENCTRL_SRC_DFLL48M
		|	GCLK_GENCTRL_RUNSTDBY
		|	GCLK_GENCTRL_IDC
		|	GCLK_GENCTRL_OE
		|	GCLK_GENCTRL_GENEN
	);
	
	while (GCLK->SYNCBUSY.reg & GCLK_SYNCBUSY_MASK);
}

#define OSC32K_CALIBRATION	((*((uint32_t const*) NVMCTRL_OTP5) >> 6) & (0x0000003f))


int 
main (void) {
//	io_t *io = get_device_io ();

	initialise_cpu ();
	
	#ifdef BOARD_HAS_TARGET_POWER
	HAL_GPIO_FW_POWER_ENABLE_write (HAL_GPIO_PIN_INACTIVE);
	HAL_GPIO_FW_POWER_ENABLE_out ();
	#endif

	initialise_cmsis_dap ();
	initialise_swo ();
	initialise_usb_serial_number ();
	initialise_usb ();
	
	//PM->SLEEPCFG.bit.SLEEPMODE = 5;
	
	while (1) {
//		io_wait_for_interrupt (io);
		__WFI();
	}

	return 0;
}
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





