/*
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _dap_device_with_jtag_h_
#define _dap_device_with_jtag_h_

HAL_GPIO_PIN (TDI,          B, 11, 0)
HAL_GPIO_PIN (TDO,          B, 2,  0)
HAL_GPIO_PIN (nTRST,        A, 5,  0)

//-----------------------------------------------------------------------------
static inline void DUBUG_UNIT_TDI_write(int value)
{
	#ifdef DUBUG_UNIT_ENABLE_JTAG
	HAL_GPIO_TDI_write(value);
	#endif
}

//-----------------------------------------------------------------------------
static inline void DUBUG_UNIT_TDO_write(int value)
{
	HAL_GPIO_TDO_write(value);
}
//-----------------------------------------------------------------------------
static inline int DUBUG_UNIT_TDO_read(void)
{
	return HAL_GPIO_TDO_read();
}

//-----------------------------------------------------------------------------
static inline int DUBUG_UNIT_TDI_read(void)
{
	return HAL_GPIO_TDI_read();
}

//-----------------------------------------------------------------------------
static inline void DUBUG_UNIT_nTRST_write(int value)
{
  (void)value;
}

//-----------------------------------------------------------------------------
static inline int DUBUG_UNIT_nTRST_read(void)
{
  return 0;
}

//-----------------------------------------------------------------------------
static inline void DUBUG_UNIT_CONNECT_JTAG (void)
{
  HAL_GPIO_SWDIO_TMS_out();
  HAL_GPIO_SWDIO_TMS_set();

  HAL_GPIO_SWCLK_TCK_out();
  HAL_GPIO_SWCLK_TCK_set();

  HAL_GPIO_TDO_in();

  HAL_GPIO_TDI_out();
  HAL_GPIO_TDI_set();

  HAL_GPIO_nRESET_out();
  HAL_GPIO_nRESET_set();
}

#ifdef IMPLEMENT_FPDU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

void
DUBUG_UNIT_JTAG_SETUP (void) {

	HAL_GPIO_TDO_in ();
	HAL_GPIO_TDI_in ();
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





