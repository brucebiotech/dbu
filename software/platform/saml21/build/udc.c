/*
 *
 * (c) see end of file for license terms.
 *
 */
#include <stdbool.h>
#include <string.h>
#include "saml21.h"
#include "debug_unit.h"
#include "udc.h"
#include "usb.h"
#include "usb_descriptors.h"


/*- Definitions -------------------------------------------------------------*/
HAL_GPIO_PIN(USB_DM,   A, 24,0);
HAL_GPIO_PIN(USB_DP,   A, 25,0);

enum
{
  USB_DEVICE_EPCFG_EPTYPE_DISABLED    = 0,
  USB_DEVICE_EPCFG_EPTYPE_CONTROL     = 1,
  USB_DEVICE_EPCFG_EPTYPE_ISOCHRONOUS = 2,
  USB_DEVICE_EPCFG_EPTYPE_BULK        = 3,
  USB_DEVICE_EPCFG_EPTYPE_INTERRUPT   = 4,
  USB_DEVICE_EPCFG_EPTYPE_DUAL_BANK   = 5,
};

enum
{
  USB_DEVICE_PCKSIZE_SIZE_8    = 0,
  USB_DEVICE_PCKSIZE_SIZE_16   = 1,
  USB_DEVICE_PCKSIZE_SIZE_32   = 2,
  USB_DEVICE_PCKSIZE_SIZE_64   = 3,
  USB_DEVICE_PCKSIZE_SIZE_128  = 4,
  USB_DEVICE_PCKSIZE_SIZE_256  = 5,
  USB_DEVICE_PCKSIZE_SIZE_512  = 6,
  USB_DEVICE_PCKSIZE_SIZE_1023 = 7,
};

/*- Types -------------------------------------------------------------------*/
typedef union
{
  UsbDeviceDescBank    bank[2];
  struct
  {
    UsbDeviceDescBank  out;
    UsbDeviceDescBank  in;
  };
} udc_mem_t;

/*- Variables ---------------------------------------------------------------*/
static udc_mem_t udc_mem[USB_EPT_NUM];
static uint32_t udc_ctrl_in_buf[16];
static uint32_t udc_ctrl_out_buf[16];

/*- Implementations ---------------------------------------------------------*/


//-----------------------------------------------------------------------------
void udc_init(void)
{
  MCLK->APBBMASK.reg |= MCLK_APBBMASK_USB;
	 
  HAL_GPIO_USB_DM_pmuxen(PORT_PMUX_PMUXE_G);
  HAL_GPIO_USB_DP_pmuxen(PORT_PMUX_PMUXE_G);


	GCLK->PCHCTRL[USB_GCLK_ID].reg = (
			GCLK_PCHCTRL_GEN (0)
		|	GCLK_PCHCTRL_CHEN
	);
	while (GCLK->SYNCBUSY.reg & ( 1 << (0 + 2)));
	
  USB->DEVICE.CTRLA.bit.SWRST = 1;
	while (USB->DEVICE.SYNCBUSY.bit.SWRST);

  USB->DEVICE.PADCAL.bit.TRANSN = NVM_READ_CAL(NVM_USB_TRANSN);
  USB->DEVICE.PADCAL.bit.TRANSP = NVM_READ_CAL(NVM_USB_TRANSP);
  USB->DEVICE.PADCAL.bit.TRIM   = NVM_READ_CAL(NVM_USB_TRIM);
  USB->DEVICE.PADCAL.bit.TRANSN = 5;
  USB->DEVICE.PADCAL.bit.TRANSP = 29;
  USB->DEVICE.PADCAL.bit.TRIM   = 5;

	USB->DEVICE.QOSCTRL.bit.CQOS = 3;
	USB->DEVICE.QOSCTRL.bit.DQOS = 3;

  memset((uint8_t *)udc_mem, 0, sizeof(udc_mem));
  USB->DEVICE.DESCADD.reg = (uint32_t)udc_mem;

  USB->DEVICE.CTRLA.bit.MODE = USB_CTRLA_MODE_DEVICE_Val;
  USB->DEVICE.CTRLA.bit.RUNSTDBY = 1;
  USB->DEVICE.CTRLB.bit.SPDCONF = USB_DEVICE_CTRLB_SPDCONF_FS_Val;
  USB->DEVICE.CTRLB.bit.DETACH = 0;

  USB->DEVICE.INTENSET.reg = USB_DEVICE_INTENSET_EORST;
  USB->DEVICE.DeviceEndpoint[0].EPINTENSET.bit.RXSTP = 1;

  USB->DEVICE.CTRLA.reg |= USB_CTRLA_ENABLE;

  for (int i = 0; i < USB_EPT_NUM; i++)
  {
    udc_reset_endpoint(i, USB_IN_ENDPOINT);
    udc_reset_endpoint(i, USB_OUT_ENDPOINT);
  }

  NVIC_EnableIRQ(USB_IRQn);
}

//-----------------------------------------------------------------------------
void udc_attach(void)
{
  USB->DEVICE.CTRLB.bit.DETACH = 0;
}

//-----------------------------------------------------------------------------
void udc_detach(void)
{
  USB->DEVICE.CTRLB.bit.DETACH = 1;
}

//-----------------------------------------------------------------------------
void udc_reset_endpoint(int ep, int dir)
{
  if (USB_IN_ENDPOINT == dir)
    USB->DEVICE.DeviceEndpoint[ep].EPCFG.bit.EPTYPE1 = USB_DEVICE_EPCFG_EPTYPE_DISABLED;
  else
    USB->DEVICE.DeviceEndpoint[ep].EPCFG.bit.EPTYPE0 = USB_DEVICE_EPCFG_EPTYPE_DISABLED;
}

//-----------------------------------------------------------------------------
void udc_configure_endpoint(usb_endpoint_descriptor_t *desc)
{
  int ep, dir, type, size;

  ep = desc->bEndpointAddress & USB_INDEX_MASK;
  dir = desc->bEndpointAddress & USB_DIRECTION_MASK;
  type = desc->bmAttributes & 0x03;
  size = desc->wMaxPacketSize & 0x3ff;

  udc_reset_endpoint(ep, dir);

  if (size <= 8)
    size = USB_DEVICE_PCKSIZE_SIZE_8;
  else if (size <= 16)
    size = USB_DEVICE_PCKSIZE_SIZE_16;
  else if (size <= 32)
    size = USB_DEVICE_PCKSIZE_SIZE_32;
  else if (size <= 64)
    size = USB_DEVICE_PCKSIZE_SIZE_64;
  else if (size <= 128)
    size = USB_DEVICE_PCKSIZE_SIZE_128;
  else if (size <= 256)
    size = USB_DEVICE_PCKSIZE_SIZE_256;
  else if (size <= 512)
    size = USB_DEVICE_PCKSIZE_SIZE_512;
  else if (size <= 1023)
    size = USB_DEVICE_PCKSIZE_SIZE_1023;
  else
    while (1);

  if (USB_CONTROL_ENDPOINT == type)
    type = USB_DEVICE_EPCFG_EPTYPE_CONTROL;
  else if (USB_ISOCHRONOUS_ENDPOINT == type)
    type = USB_DEVICE_EPCFG_EPTYPE_ISOCHRONOUS;
  else if (USB_BULK_ENDPOINT == type)
    type = USB_DEVICE_EPCFG_EPTYPE_BULK;
  else
    type = USB_DEVICE_EPCFG_EPTYPE_INTERRUPT;

  if (USB_IN_ENDPOINT == dir)
  {
    USB->DEVICE.DeviceEndpoint[ep].EPCFG.bit.EPTYPE1 = type;
    USB->DEVICE.DeviceEndpoint[ep].EPINTENSET.bit.TRCPT1 = 1;
    USB->DEVICE.DeviceEndpoint[ep].EPSTATUSCLR.bit.DTGLIN = 1;
    USB->DEVICE.DeviceEndpoint[ep].EPSTATUSCLR.bit.BK1RDY = 1;
    udc_mem[ep].in.PCKSIZE.bit.SIZE = size;
  }
  else
  {
    USB->DEVICE.DeviceEndpoint[ep].EPCFG.bit.EPTYPE0 = type;
    USB->DEVICE.DeviceEndpoint[ep].EPINTENSET.bit.TRCPT0 = 1;
    USB->DEVICE.DeviceEndpoint[ep].EPSTATUSCLR.bit.DTGLOUT = 1;
    USB->DEVICE.DeviceEndpoint[ep].EPSTATUSSET.bit.BK0RDY = 1;
    udc_mem[ep].out.PCKSIZE.bit.SIZE = size;
  }
}

//-----------------------------------------------------------------------------
bool udc_endpoint_configured(int ep, int dir)
{
  if (USB_IN_ENDPOINT == dir)
    return (USB_DEVICE_EPCFG_EPTYPE_DISABLED != USB->DEVICE.DeviceEndpoint[ep].EPCFG.bit.EPTYPE1);
  else
    return (USB_DEVICE_EPCFG_EPTYPE_DISABLED != USB->DEVICE.DeviceEndpoint[ep].EPCFG.bit.EPTYPE0);
}

//-----------------------------------------------------------------------------
int udc_endpoint_get_status(int ep, int dir)
{
  if (USB_IN_ENDPOINT == dir)
    return USB->DEVICE.DeviceEndpoint[ep].EPSTATUS.bit.STALLRQ1;
  else
    return USB->DEVICE.DeviceEndpoint[ep].EPSTATUS.bit.STALLRQ0;
}

//-----------------------------------------------------------------------------
void udc_endpoint_set_feature(int ep, int dir)
{
  if (USB_IN_ENDPOINT == dir)
    USB->DEVICE.DeviceEndpoint[ep].EPSTATUSSET.bit.STALLRQ1 = 1;
  else
    USB->DEVICE.DeviceEndpoint[ep].EPSTATUSSET.bit.STALLRQ0 = 1;
}

//-----------------------------------------------------------------------------
void udc_endpoint_clear_feature(int ep, int dir)
{
  if (USB_IN_ENDPOINT == dir)
  {
    if (USB->DEVICE.DeviceEndpoint[ep].EPSTATUS.bit.STALLRQ1)
    {
      USB->DEVICE.DeviceEndpoint[ep].EPSTATUSCLR.bit.STALLRQ1 = 1;

      if (USB->DEVICE.DeviceEndpoint[ep].EPINTFLAG.bit.STALL1)
      {
//        USB->DEVICE.DeviceEndpoint[ep].EPINTFLAG.bit.STALL1 = 1;
        USB->DEVICE.DeviceEndpoint[ep].EPSTATUSCLR.bit.DTGLIN = 1;
        USB->DEVICE.DeviceEndpoint[ep].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_STALL1;
//        USB->DEVICE.DeviceEndpoint[ep].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_DTGLIN;
      }
    }
  }
  else
  {
    if (USB->DEVICE.DeviceEndpoint[ep].EPSTATUS.bit.STALLRQ0)
    {
      USB->DEVICE.DeviceEndpoint[ep].EPSTATUSCLR.bit.STALLRQ0 = 1;

      if (USB->DEVICE.DeviceEndpoint[ep].EPINTFLAG.bit.STALL0)
      {
//        USB->DEVICE.DeviceEndpoint[ep].EPINTFLAG.bit.STALL0 = 1;
        USB->DEVICE.DeviceEndpoint[ep].EPSTATUSCLR.bit.DTGLOUT = 1;
        USB->DEVICE.DeviceEndpoint[ep].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_STALL0;
//       USB->DEVICE.DeviceEndpoint[ep].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_DTGLOUT;
      }
    }
  }
}

//-----------------------------------------------------------------------------
void udc_set_address(int address)
{
  USB->DEVICE.DADD.reg = USB_DEVICE_DADD_ADDEN | USB_DEVICE_DADD_DADD(address);
}

//-----------------------------------------------------------------------------
void udc_send(int ep, uint8_t *data, int size)
{
  udc_mem[ep].in.ADDR.reg = (uint32_t)data;
  udc_mem[ep].in.PCKSIZE.bit.BYTE_COUNT = size;
  udc_mem[ep].in.PCKSIZE.bit.MULTI_PACKET_SIZE = 0;

  USB->DEVICE.DeviceEndpoint[ep].EPSTATUSSET.bit.BK1RDY = 1;
}

//-----------------------------------------------------------------------------
void udc_recv(int ep, uint8_t *data, int size)
{
  udc_mem[ep].out.ADDR.reg = (uint32_t)data;
  udc_mem[ep].out.PCKSIZE.bit.MULTI_PACKET_SIZE = size;
  udc_mem[ep].out.PCKSIZE.bit.BYTE_COUNT = 0;

  USB->DEVICE.DeviceEndpoint[ep].EPSTATUSCLR.bit.BK0RDY = 1;
}

//-----------------------------------------------------------------------------
void udc_control_send_zlp(void)
{
  udc_mem[0].in.PCKSIZE.bit.BYTE_COUNT = 0;
//  USB->DEVICE.DeviceEndpoint[0].EPINTFLAG.bit.TRCPT1 = 1;
  USB->DEVICE.DeviceEndpoint[0].EPSTATUSSET.bit.BK1RDY = 1;
  USB->DEVICE.DeviceEndpoint[0].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT1;
//  USB->DEVICE.DeviceEndpoint[0].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_BK1RDY;

  while (0 == USB->DEVICE.DeviceEndpoint[0].EPINTFLAG.bit.TRCPT1);
}

//-----------------------------------------------------------------------------
void udc_control_stall(void)
{
  USB->DEVICE.DeviceEndpoint[0].EPSTATUSSET.bit.STALLRQ1 = 1;
}

//-----------------------------------------------------------------------------
void udc_control_send(uint8_t *data, int size)
{
  if (size <= usb_device_descriptor.bMaxPacketSize0)
  {
    // Small payloads may be unaligned, so copy them into an aligned buffer
    memcpy(udc_ctrl_in_buf, data, size);
    udc_mem[0].in.ADDR.reg = (uint32_t)udc_ctrl_in_buf;
  }
  else
  {
    // Large payloads must be aligned
    udc_mem[0].in.ADDR.reg = (uint32_t)data;
  }

  udc_mem[0].in.PCKSIZE.bit.BYTE_COUNT = size;
  udc_mem[0].in.PCKSIZE.bit.MULTI_PACKET_SIZE = 0;

//  USB->DEVICE.DeviceEndpoint[0].EPINTFLAG.bit.TRCPT1 = 1;
  USB->DEVICE.DeviceEndpoint[0].EPSTATUSSET.bit.BK1RDY = 1;
  USB->DEVICE.DeviceEndpoint[0].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT1;
//  USB->DEVICE.DeviceEndpoint[0].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_BK1RDY;

  while (0 == USB->DEVICE.DeviceEndpoint[0].EPINTFLAG.bit.TRCPT1);
}

//-----------------------------------------------------------------------------
DUBUG_UNIT_PERFORMANCE_ATTR
void irq_handler_usb(void)
{
  int epint, flags;

  if (USB->DEVICE.INTFLAG.bit.EORST)
  {
    USB->DEVICE.INTFLAG.reg = USB_DEVICE_INTFLAG_EORST;
    USB->DEVICE.DADD.reg = USB_DEVICE_DADD_ADDEN;

    for (int i = 0; i < USB_EPT_NUM; i++)
    {
      udc_reset_endpoint(i, USB_IN_ENDPOINT);
      udc_reset_endpoint(i, USB_OUT_ENDPOINT);
    }

    USB->DEVICE.DeviceEndpoint[0].EPCFG.reg = (
         USB_DEVICE_EPCFG_EPTYPE0(USB_DEVICE_EPCFG_EPTYPE_CONTROL)
       | USB_DEVICE_EPCFG_EPTYPE1(USB_DEVICE_EPCFG_EPTYPE_CONTROL)
	 );
    USB->DEVICE.DeviceEndpoint[0].EPSTATUSSET.bit.BK0RDY = 1;
    USB->DEVICE.DeviceEndpoint[0].EPSTATUSCLR.bit.BK1RDY = 1;
//	  USB->DEVICE.DeviceEndpoint[0].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_BK0RDY;
//	  USB->DEVICE.DeviceEndpoint[0].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_BK1RDY;

    udc_mem[0].in.ADDR.reg = (uint32_t)udc_ctrl_in_buf;
    udc_mem[0].in.PCKSIZE.bit.SIZE = USB_DEVICE_PCKSIZE_SIZE_64;
    udc_mem[0].in.PCKSIZE.bit.BYTE_COUNT = 0;
    udc_mem[0].in.PCKSIZE.bit.MULTI_PACKET_SIZE = 0;

    udc_mem[0].out.ADDR.reg = (uint32_t)udc_ctrl_out_buf;
    udc_mem[0].out.PCKSIZE.bit.SIZE = USB_DEVICE_PCKSIZE_SIZE_64;
    udc_mem[0].out.PCKSIZE.bit.MULTI_PACKET_SIZE = 8;
    udc_mem[0].out.PCKSIZE.bit.BYTE_COUNT = 0;

    USB->DEVICE.DeviceEndpoint[0].EPSTATUSCLR.bit.BK0RDY = 1;
   USB->DEVICE.DeviceEndpoint[0].EPINTENSET.bit.RXSTP = 1;
  }

  if (USB->DEVICE.DeviceEndpoint[0].EPINTFLAG.bit.RXSTP)
  {
   USB->DEVICE.DeviceEndpoint[0].EPSTATUSCLR.bit.BK0RDY = 1;
  USB->DEVICE.DeviceEndpoint[0].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_RXSTP;

    usb_handle_standard_request((usb_request_t *)udc_ctrl_out_buf);
  }

  epint = USB->DEVICE.EPINTSMRY.reg;

  for (int i = 0; epint && i < USB_EPT_NUM; i++)
  {
    if (0 == (epint & (1 << i)))
      continue;

    epint &= ~(1 << i);

    flags = USB->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg;

    if (flags & USB_DEVICE_EPINTFLAG_TRCPT0)
    {
      USB->DEVICE.DeviceEndpoint[i].EPSTATUSSET.bit.BK0RDY = 1;
	  USB->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT0;
      udc_recv_callback(i);
    }

    if (flags & USB_DEVICE_EPINTFLAG_TRCPT1)
    {
      USB->DEVICE.DeviceEndpoint[i].EPSTATUSCLR.bit.BK1RDY = 1;
	  USB->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT1;
      udc_send_callback(i);
    }
  }
}
/*
 * Copyright (c) 2016, Alex Taradov <alex@taradov.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
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






