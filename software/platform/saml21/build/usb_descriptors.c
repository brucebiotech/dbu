/*
 *
 * (c) see end of file for license terms.
 *
 */
#include <stdalign.h>
#include "usb_descriptors.h"
#include "debug_unit.h"

/*- Variables ---------------------------------------------------------------*/
const alignas(4) usb_device_descriptor_t usb_device_descriptor =
{
  .bLength            = sizeof(usb_device_descriptor_t),
  .bDescriptorType    = USB_DEVICE_DESCRIPTOR,
  .bcdUSB             = 0x0200,
  .bDeviceClass       = 0x00,
  .bDeviceSubClass    = 0x00,
  .bDeviceProtocol    = 0x00,
  .bMaxPacketSize0    = 64,
  .idVendor           = DUBUG_UNIT_VENDOR_ID,
  .idProduct          = DUBUG_UNIT_PRODUCT_ID,
  .bcdDevice          = 0x0100,
  .iManufacturer      = USB_STR_MANUFACTURER,
  .iProduct           = USB_STR_PRODUCT,
  .iSerialNumber      = USB_STR_SERIAL_NUMBER,
  .bNumConfigurations = 1,
};

int
maximum_response_payload_size (void) {
	return usb_device_descriptor.bMaxPacketSize0;
}

const alignas(4) usb_configuration_hierarchy_t usb_configuration_hierarchy =
{
  .configuration =
  {
    .bLength             = sizeof(usb_configuration_descriptor_t),
    .bDescriptorType     = USB_CONFIGURATION_DESCRIPTOR,
    .wTotalLength        = sizeof(usb_configuration_hierarchy_t),
    .bNumInterfaces      = 1,
    .bConfigurationValue = 1,
    .iConfiguration      = USB_STR_CONFIGURATION,
    .bmAttributes        = 0x80,
    .bMaxPower           = 200, // 400 mA
  },

  .interface =
  {
    .bLength             = sizeof(usb_interface_descriptor_t),
    .bDescriptorType     = USB_INTERFACE_DESCRIPTOR,
    .bInterfaceNumber    = 0,
    .bAlternateSetting   = 0,
    .bNumEndpoints       = 2,
    .bInterfaceClass     = 0x03,
    .bInterfaceSubClass  = 0x00,
    .bInterfaceProtocol  = 0x00,
    .iInterface          = USB_STR_INTERFACE,
  },

  .hid =
  {
    .bLength             = sizeof(usb_hid_descriptor_t),
    .bDescriptorType     = USB_HID_DESCRIPTOR,
    .bcdHID              = 0x0111,
    .bCountryCode        = 0,
    .bNumDescriptors     = 1,
    .bDescriptorType1    = USB_HID_REPORT_DESCRIPTOR,
    .wDescriptorLength   = sizeof(usb_hid_report_descriptor),
  },

  .ep_in =
  {
    .bLength             = sizeof(usb_endpoint_descriptor_t),
    .bDescriptorType     = USB_ENDPOINT_DESCRIPTOR,
    .bEndpointAddress    = USB_IN_ENDPOINT | APP_EP_SEND,
    .bmAttributes        = USB_INTERRUPT_ENDPOINT,
    .wMaxPacketSize      = 64,
    .bInterval           = 1,
  },

  .ep_out =
  {
    .bLength             = sizeof(usb_endpoint_descriptor_t),
    .bDescriptorType     = USB_ENDPOINT_DESCRIPTOR,
    .bEndpointAddress    = USB_OUT_ENDPOINT | APP_EP_RECV,
    .bmAttributes        = USB_INTERRUPT_ENDPOINT,
    .wMaxPacketSize      = 64,
    .bInterval           = 1,
  },
};

#if 0
#define USBD_CUSTOM_HID_REPORT_DESC_SIZE		29

const alignas(4) uint8_t usb_hid_report_descriptor[USBD_CUSTOM_HID_REPORT_DESC_SIZE] =
{
	/* USER CODE BEGIN 0 */
	0x06, 0x00, 0xFF,                   /* USAGE_PAGE (Vendor Defined Page 1) */
	0x09, 0x01,                         /* USAGE (Vendor Usage 1) */
	0xa1, 0x01,                         /* COLLECTION (Application) */
	0x19, 0x01,                         /*   USAGE_MINIMUM (0) */
	0x29, 0x40,                         /*   USAGE_MAXIMUM (64) */
	0x15, 0x00,                         /*   LOGICAL_MINIMUM (0) */
	0x26, 0xFF, 0x00,                   /*   LOGICAL_MAXIMUM (255) */
	0x75, 0x08,                         /*   REPORT_SIZE (8) */
	0x95, 0x40, 						      /*   REPORT_COUNT (64) */
	0x81, 0x00,                         /* */
	0x19, 0x01,                         /*   USAGE MINIMUM */
	0x29, 0x40,						         /*   USAGE_MAXIMUM */
	0x91, 0x00,                         /*   OUTPUT (Data,Var,Abs) (note: output from host)  */
	/* USER CODE END 0 */
	0xC0    /*     END_COLLECTION	             */
};

#else
#define USBD_CUSTOM_HID_REPORT_DESC_SIZE		28

const alignas(4) uint8_t usb_hid_report_descriptor[USBD_CUSTOM_HID_REPORT_DESC_SIZE] =
{
  0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
  0x09, 0x00,        // Usage (Undefined)
  0xa1, 0x01,        // Collection (Application)
  0x15, 0x00,        //   Logical Minimum (0)
  0x26, 0xff, 0x00,  //   Logical Maximum (255)
  0x75, 0x08,        //   Report Size (8)
  0x95, 0x40,        //   Report Count (64)
  0x09, 0x00,        //   Usage (Undefined)
  0x81, 0x82,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x75, 0x08,        //   Report Size (8)
  0x95, 0x40,        //   Report Count (64)
  0x09, 0x00,        //   Usage (Undefined)
  0x91, 0x82,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Volatile)
  0xc0,              // End Collection
};
#endif

const alignas(4) usb_string_descriptor_zero_t usb_string_descriptor_zero =
{
  .bLength               = sizeof(usb_string_descriptor_zero_t),
  .bDescriptorType       = USB_STRING_DESCRIPTOR,
  .wLANGID               = 0x0409, // English (United States)
};

const char *const usb_strings[] =
{
  [USB_STR_MANUFACTURER]  = DUBUG_UNIT_VENDOR_STR,
  [USB_STR_PRODUCT]       = DUBUG_UNIT_PRODUCT_STR,
  [USB_STR_SERIAL_NUMBER] = DUBUG_UNIT_SER_NUM_STR,
  [USB_STR_CONFIGURATION] = "Main Configuration",
  [USB_STR_INTERFACE]     = "Main Interface",
};
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


