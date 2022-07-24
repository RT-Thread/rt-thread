/*!
    \file    printer_core.c
    \brief   USB printer device class core functions

    \version 2020-08-01, V3.0.0, firmware for GD32F30x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "usbd_transc.h"
#include "printer_core.h"

#define USBD_VID                     0x28E9U
#define USBD_PID                     0x028DU

/* printer port status: paper not empty/selected/no error */
static uint8_t g_port_status = 0x18U;
uint8_t g_printer_data_buf[PRINTER_OUT_PACKET];

uint8_t Printer_DEVICE_ID[DEVICE_ID_LEN] =
{
    0x00, 0x67,
    'M', 'A', 'N', 'U', 'F', 'A', 'C', 'T', 'U', 'R', 'E', 'R', ':',
    'G', 'I', 'G', 'A', ' ', 'D', 'E', 'V', 'I', 'C', 'E', '-', ';',
    'C', 'O', 'M', 'M', 'A', 'N', 'D', ' ', 'S', 'E', 'T', ':',
    'P', 'C', 'L', ',', 'M', 'P', 'L', ';',
    'M', 'O', 'D', 'E', 'L', ':',
    'L', 'a', 's', 'e', 'r', 'B', 'e', 'a', 'm', '?', ';',
    'C', 'O', 'M', 'M', 'E', 'N', 'T', ':',
    'G', 'o', 'o', 'd', ' ', '!', ';',
    'A', 'C', 'T', 'I', 'V', 'E', ' ', 'C', 'O', 'M', 'M', 'A', 'N', 'D', ' ', 'S', 'E', 'T', ':',
    'P', 'C', 'L', ';'
};

/* USB standard device descriptor */
usb_desc_dev printer_dev_desc =
{
    .header =
     {
         .bLength          = USB_DEV_DESC_LEN,
         .bDescriptorType  = USB_DESCTYPE_DEV,
     },
    .bcdUSB                = 0x0200U,
    .bDeviceClass          = 0x00U,
    .bDeviceSubClass       = 0x00U,
    .bDeviceProtocol       = 0x00U,
    .bMaxPacketSize0       = USBD_EP0_MAX_SIZE,
    .idVendor              = USBD_VID,
    .idProduct             = USBD_PID,
    .bcdDevice             = 0x0100U,
    .iManufacturer         = STR_IDX_MFC,
    .iProduct              = STR_IDX_PRODUCT,
    .iSerialNumber         = STR_IDX_SERIAL,
    .bNumberConfigurations = USBD_CFG_MAX_NUM,
};

/* USB device configuration descriptor */
usb_printer_desc_config_set printer_config_desc =
{
    .config =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_config),
             .bDescriptorType = USB_DESCTYPE_CONFIG
         },
        .wTotalLength         = USB_PRINTER_CONFIG_DESC_LEN,
        .bNumInterfaces       = 0x01U,
        .bConfigurationValue  = 0x01U,
        .iConfiguration       = 0x00U,
        .bmAttributes         = 0xA0U,
        .bMaxPower            = 0x32U
    },

    .printer_itf =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_itf),
             .bDescriptorType = USB_DESCTYPE_ITF
         },
        .bInterfaceNumber     = 0x00U,
        .bAlternateSetting    = 0x00U,
        .bNumEndpoints        = 0x02U,
        .bInterfaceClass      = USB_CLASS_PRINTER,
        .bInterfaceSubClass   = USB_SUBCLASS_PRINTER,
        .bInterfaceProtocol   = PROTOCOL_BI_DIRECTIONAL_ITF,
        .iInterface           = 0x00U
    },

    .printer_epin =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
        .bEndpointAddress     = PRINTER_IN_EP,
        .bmAttributes         = USB_EP_ATTR_BULK,
        .wMaxPacketSize       = PRINTER_IN_PACKET,
        .bInterval            = 0x00U
    },

    .printer_epout =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
        .bEndpointAddress     = PRINTER_OUT_EP,
        .bmAttributes         = USB_EP_ATTR_BULK,
        .wMaxPacketSize       = PRINTER_OUT_PACKET,
        .bInterval            = 0x00U
    },
};

/* USB language ID Descriptor */
static usb_desc_LANGID usbd_language_id_desc =
{
    .header =
     {
         .bLength         = sizeof(usb_desc_LANGID),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
    .wLANGID              = ENG_LANGID
};

/* USB manufacture string */
static usb_desc_str manufacturer_string =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(10U),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
    .unicode_string = {'G', 'i', 'g', 'a', 'D', 'e', 'v', 'i', 'c', 'e'}
};

/* USB product string */
static usb_desc_str product_string =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(16U),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
    .unicode_string = {'G', 'D', '3', '2', '-', 'U', 'S', 'B', '_', 'P', 'r', 'i', 'n', 't', 'e', 'r'}
};

/* USBD serial string */
static usb_desc_str serial_string =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(12U),
         .bDescriptorType = USB_DESCTYPE_STR,
     }
};

/* USB string descriptor */
static uint8_t* usbd_msc_strings[] =
{
    [STR_IDX_LANGID]  = (uint8_t *)&usbd_language_id_desc,
    [STR_IDX_MFC]     = (uint8_t *)&manufacturer_string,
    [STR_IDX_PRODUCT] = (uint8_t *)&product_string,
    [STR_IDX_SERIAL]  = (uint8_t *)&serial_string
};

usb_desc printer_desc = {
    .dev_desc    = (uint8_t *)&printer_dev_desc,
    .config_desc = (uint8_t *)&printer_config_desc,
    .strings     = usbd_msc_strings
};

/* local function prototypes ('static') */
static uint8_t printer_init         (usb_dev *udev, uint8_t config_index);
static uint8_t printer_deinit       (usb_dev *udev, uint8_t config_index);
static uint8_t printer_req_handler  (usb_dev *udev, usb_req *req);
static void printer_data_in         (usb_dev *udev, uint8_t ep_num);
static void printer_data_out        (usb_dev *udev, uint8_t ep_num);

usb_class printer_class = {
    .init          = printer_init,
    .deinit        = printer_deinit,
    .req_process   = printer_req_handler,
    .data_in       = printer_data_in,
    .data_out      = printer_data_out
};
/*!
    \brief      initialize the printer device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t printer_init (usb_dev *udev, uint8_t config_index)
{
    /* initialize the data Tx/Rx endpoint */
    usbd_ep_init(udev, EP_BUF_SNG, BULK_TX_ADDR, &(printer_config_desc.printer_epin));
    usbd_ep_init(udev, EP_BUF_SNG, BULK_RX_ADDR, &(printer_config_desc.printer_epout));

    udev->ep_transc[EP_ID(PRINTER_IN_EP)][TRANSC_IN] = printer_class.data_in;
    udev->ep_transc[PRINTER_OUT_EP][TRANSC_OUT] = printer_class.data_out;

    /* prepare to receive data */
    usbd_ep_recev(udev, PRINTER_OUT_EP, g_printer_data_buf, PRINTER_OUT_PACKET);

    return USBD_OK;
}

/*!
    \brief      de-initialize the printer device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t printer_deinit (usb_dev *udev, uint8_t config_index)
{
    /* deinitialize the data Tx/Rx endpoint */
    usbd_ep_deinit(udev, PRINTER_IN_EP);
    usbd_ep_deinit(udev, PRINTER_OUT_EP);

    return USBD_OK;
}

/*!
    \brief      handle the printer class-specific requests
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: device class-specific request
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t printer_req_handler (usb_dev *udev, usb_req *req)
{
    uint8_t status = REQ_NOTSUPP;

    switch (req->bRequest) {
    case GET_DEVICE_ID:
        usb_transc_config(&udev->transc_in[0], Printer_DEVICE_ID, DEVICE_ID_LEN, 0U);

        status = REQ_SUPP;
        break;

    case GET_PORT_STATUS:
        usb_transc_config(&udev->transc_in[0], (uint8_t *)&g_port_status, 1U, 0U);

        status = REQ_SUPP;
        break;

    case SOFT_RESET:
        usbd_ep_recev(udev, PRINTER_OUT_EP, g_printer_data_buf, PRINTER_OUT_PACKET);

        status = REQ_SUPP;
        break;

    default:
        break;
    }

    return status;
}

/*!
    \brief      handle printer data
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     none
*/
static void  printer_data_in (usb_dev *udev, uint8_t ep_num)
{
}

/*!
    \brief      handle printer data
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     none
*/
static void  printer_data_out (usb_dev *udev, uint8_t ep_num)
{
}
