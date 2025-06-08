/*
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _fpdu_cmsis_dap_jtag_H_
#define _fpdu_cmsis_dap_jtag_H_

#define ARM_JTAG_IR_LENGTH  4


#ifdef IMPLEMENT_FPDU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
static void dap_jtag_idcode(void)
{
#ifdef DUBUG_UNIT_ENABLE_JTAG
  uint32_t data;

  if (DAP_PORT_JTAG != dap_port || !dap_select_DP_protocol(dap_req_get_byte()))
  {
    dap_resp_add_byte(DAP_ERROR);
    return;
  }

  dap_jtag_write_ir(JTAG_IDCODE);

  DUBUG_UNIT_SWDIO_TMS_write(1);
  dap_swj_run(1); // -> Select-DR-Scan
  DUBUG_UNIT_SWDIO_TMS_write(0);
  dap_swj_run(2 + dap_jtag_dev_index); // -> Shift-DR

  data = dap_jtag_read(31);

  DUBUG_UNIT_SWDIO_TMS_write(1);
  data |= (dap_jtag_read(1) << 31); // -> Exit1-DR

  dap_swj_run(1); // -> Update-DR
  DUBUG_UNIT_SWDIO_TMS_write(0);
  dap_swj_run(1); // -> Idle
  DUBUG_UNIT_TDI_write(1);

  dap_resp_add_byte(DAP_OK);
  dap_resp_add_word(data);
#endif
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




