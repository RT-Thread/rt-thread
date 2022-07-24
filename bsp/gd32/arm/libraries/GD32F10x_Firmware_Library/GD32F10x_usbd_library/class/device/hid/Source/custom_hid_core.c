/*!
    \file    custom_hid_core.c
    \brief   custom HID class driver

    \version 2020-07-17, V3.0.0, firmware for GD32F10x
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
#include "custom_hid_core.h"
#include <string.h>

#define USBD_VID                     0x28E9U
#define USBD_PID                     0x128AU

/* Note:it should use the C99 standard when compiling the below codes */
/* USB standard device descriptor */
usb_desc_dev custom_hid_dev_desc =
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

/* USB device configure descriptor */
usb_hid_desc_config_set custom_hid_config_desc =
{
    .config =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_config),
             .bDescriptorType = USB_DESCTYPE_CONFIG
         },
        .wTotalLength         = DESC_LEN_CONFIG,
        .bNumInterfaces       = 0x01U,
        .bConfigurationValue  = 0x01U,
        .iConfiguration       = 0x00U,
        .bmAttributes         = 0x80U,
        .bMaxPower            = 0x32U
    },

    .hid_itf =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_itf),
             .bDescriptorType = USB_DESCTYPE_ITF
         },
        .bInterfaceNumber     = 0x00U,
        .bAlternateSetting    = 0x00U,
        .bNumEndpoints        = 0x02U,
        .bInterfaceClass      = USB_HID_CLASS,
        .bInterfaceSubClass   = 0x00U,
        .bInterfaceProtocol   = 0x00U,
        .iInterface           = 0x00U
    },

    .hid_vendor =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_hid),
             .bDescriptorType = USB_DESCTYPE_HID
         },
        .bcdHID               = 0x0111U,
        .bCountryCode         = 0x00U,
        .bNumDescriptors      = 0x01U,
        .bDescriptorType      = USB_DESCTYPE_REPORT,
        .wDescriptorLength    = DESC_LEN_REPORT,
    },

    .hid_epin =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
        .bEndpointAddress     = CUSTOMHID_IN_EP,
        .bmAttributes         = USB_EP_ATTR_INT,
        .wMaxPacketSize       = CUSTOMHID_IN_PACKET,
        .bInterval            = 0x20U
    },

    .hid_epout =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
        .bEndpointAddress     = CUSTOMHID_OUT_EP,
        .bmAttributes         = USB_EP_ATTR_INT,
        .wMaxPacketSize       = CUSTOMHID_OUT_PACKET,
        .bInterval            = 0x20U
    }
};

/* USB language ID descriptor */
static usb_desc_LANGID usbd_language_id_desc =
{
    .header =
     {
         .bLength = sizeof(usb_desc_LANGID),
         .bDescriptorType = USB_DESCTYPE_STR
     },
    .wLANGID = ENG_LANGID
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
         .bLength         = USB_STRING_LEN(14U),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
    .unicode_string = {'G', 'D', '3', '2', '-', 'C', 'u', 's', 't', 'o', 'm', 'H', 'I', 'D'}
};

/* USB serial string */
static usb_desc_str serial_string =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(12U),
         .bDescriptorType = USB_DESCTYPE_STR,
     }
};

/* USB string descriptor set */
static uint8_t* usbd_hid_strings[] =
{
    [STR_IDX_LANGID]  = (uint8_t *)&usbd_language_id_desc,
    [STR_IDX_MFC]     = (uint8_t *)&manufacturer_string,
    [STR_IDX_PRODUCT] = (uint8_t *)&product_string,
    [STR_IDX_SERIAL]  = (uint8_t *)&serial_string
};

usb_desc custom_hid_desc = {
    .dev_desc    = (uint8_t *)&custom_hid_dev_desc,
    .config_desc = (uint8_t *)&custom_hid_config_desc,
    .strings     = usbd_hid_strings
};

/* local function prototypes ('static') */
static uint8_t custom_hid_init         (usb_dev *udev, uint8_t config_index);
static uint8_t custom_hid_deinit       (usb_dev *udev, uint8_t config_index);
static uint8_t custom_hid_req_handler  (usb_dev *udev, usb_req *req);
static void custom_hid_data_in         (usb_dev *udev, uint8_t ep_num);
static void custom_hid_data_out        (usb_dev *udev, uint8_t ep_num);

usb_class custom_hid_class = {
    .req_cmd       = 0xFFU,

    .init          = custom_hid_init,
    .deinit        = custom_hid_deinit,
    .req_process   = custom_hid_req_handler,
    .data_in       = custom_hid_data_in,
    .data_out      = custom_hid_data_out
};

const uint8_t customhid_report_descriptor[DESC_LEN_REPORT] =
{
    0x06, 0x00, 0xFF,  /* USAGE_PAGE (Vendor Defined: 0xFF00) */
    0x09, 0x00,        /* USAGE (Custom Device)               */
    0xa1, 0x01,        /* COLLECTION (Application)            */

    /* led 1 */
    0x85, 0x11,     /* REPORT_ID (0x11)          */
    0x09, 0x01,     /* USAGE (LED 1)             */
    0x15, 0x00,     /* LOGICAL_MINIMUM (0)       */
    0x25, 0x01,     /* LOGICAL_MAXIMUM (1)       */
    0x75, 0x08,     /* REPORT_SIZE (8)           */
    0x95, 0x01,     /* REPORT_COUNT (1)          */
    0x91, 0x82,     /* OUTPUT (Data,Var,Abs,Vol) */

    /* led 2 */
    0x85, 0x12,     /* REPORT_ID (0x12)          */
    0x09, 0x02,     /* USAGE (LED 2)             */
    0x15, 0x00,     /* LOGICAL_MINIMUM (0)       */
    0x25, 0x01,     /* LOGICAL_MAXIMUM (1)       */
    0x75, 0x08,     /* REPORT_SIZE (8)           */
    0x95, 0x01,     /* REPORT_COUNT (1)          */
    0x91, 0x82,     /* OUTPUT (Data,Var,Abs,Vol) */

    /* led 3 */
    0x85, 0x13,     /* REPORT_ID (0x13)          */
    0x09, 0x03,     /* USAGE (LED 3)             */
    0x15, 0x00,     /* LOGICAL_MINIMUM (0)       */
    0x25, 0x01,     /* LOGICAL_MAXIMUM (1)       */
    0x75, 0x08,     /* REPORT_SIZE (8)           */
    0x95, 0x01,     /* REPORT_COUNT (1)          */
    0x91, 0x82,     /* OUTPUT (Data,Var,Abs,Vol) */

    /* led 4 */
    0x85, 0x14,     /* REPORT_ID (0x14)          */
    0x09, 0x04,     /* USAGE (LED 4)             */
    0x15, 0x00,     /* LOGICAL_MINIMUM (0)       */
    0x25, 0x01,     /* LOGICAL_MAXIMUM (1)       */
    0x75, 0x08,     /* REPORT_SIZE (8)           */
    0x95, 0x01,     /* REPORT_COUNT (1)          */
    0x91, 0x82,     /* OUTPUT (Data,Var,Abs,Vol) */

    /* wakeup key */
    0x85, 0x15,     /* REPORT_ID (0x15)          */
    0x09, 0x05,     /* USAGE (Push Button)       */
    0x15, 0x00,     /* LOGICAL_MINIMUM (0)       */
    0x25, 0x01,     /* LOGICAL_MAXIMUM (1)       */
    0x75, 0x01,     /* REPORT_SIZE (1)           */
    0x81, 0x02,     /* INPUT (Data,Var,Abs,Vol)  */

    0x75, 0x07,     /* REPORT_SIZE (7)           */
    0x81, 0x03,     /* INPUT (Cnst,Var,Abs,Vol)  */

    /* tamper key */
    0x85, 0x16,     /* REPORT_ID (0x16)          */
    0x09, 0x06,     /* USAGE (Push Button)       */
    0x15, 0x00,     /* LOGICAL_MINIMUM (0)       */
    0x25, 0x01,     /* LOGICAL_MAXIMUM (1)       */
    0x75, 0x01,     /* REPORT_SIZE (1)           */
    0x81, 0x02,     /* INPUT (Data,Var,Abs,Vol)  */

    0x75, 0x07,     /* REPORT_SIZE (7)           */
    0x81, 0x03,     /* INPUT (Cnst,Var,Abs,Vol)  */

    0xc0            /* END_COLLECTION            */
};

/*!
    \brief      register HID interface operation functions
    \param[in]  udev: pointer to USB device instance
    \param[in]  hid_fop: HID operation functions structure
    \param[out] none
    \retval     USB device operation status
*/
uint8_t custom_hid_itfop_register (usb_dev *udev, hid_fop_handler *hid_fop)
{
    if (NULL != hid_fop) {
        udev->user_data = hid_fop;

        return USBD_OK;
    }

    return USBD_FAIL;
}

/*!
    \brief      send custom HID report
    \param[in]  udev: pointer to USB device instance
    \param[in]  report: pointer to HID report
    \param[in]  len: data length
    \param[out] none
    \retval     USB device operation status
*/
uint8_t custom_hid_report_send (usb_dev *udev, uint8_t *report, uint16_t len)
{
    usbd_ep_send (udev, CUSTOMHID_IN_EP, report, len);

    return USBD_OK;
}

/*!
    \brief      initialize the HID device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t custom_hid_init (usb_dev *udev, uint8_t config_index)
{
    static custom_hid_handler hid_handler;

    memset((void *)&hid_handler, 0, sizeof(custom_hid_handler));

    /* initialize the data endpoints */
    usbd_ep_init(udev, EP_BUF_SNG, HID_TX_ADDR, &(custom_hid_config_desc.hid_epin));
    usbd_ep_init(udev, EP_BUF_SNG, HID_RX_ADDR, &(custom_hid_config_desc.hid_epout));

    usbd_ep_recev (udev, CUSTOMHID_OUT_EP, hid_handler.data, 2U);

    udev->ep_transc[EP_ID(CUSTOMHID_IN_EP)][TRANSC_IN] = custom_hid_class.data_in;
    udev->ep_transc[EP_ID(CUSTOMHID_OUT_EP)][TRANSC_OUT] = custom_hid_class.data_out;

    udev->class_data[CUSTOM_HID_INTERFACE] = (void *)&hid_handler;

    if (udev->user_data != NULL) {
        for (uint8_t i = 0U; i < MAX_PERIPH_NUM; i++) {
            if (((hid_fop_handler *)udev->user_data)->periph_config[i] != NULL) {
                ((hid_fop_handler *)udev->user_data)->periph_config[i]();
            }
        }
    }

    return USBD_OK;
}

/*!
    \brief      de-initialize the HID device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t custom_hid_deinit (usb_dev *udev, uint8_t config_index)
{
    /* deinitialize HID endpoints */
    usbd_ep_deinit(udev, CUSTOMHID_IN_EP);
    usbd_ep_deinit(udev, CUSTOMHID_OUT_EP);

    return USBD_OK;
}

/*!
    \brief      handle the HID class-specific requests
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: device class-specific request
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t custom_hid_req_handler (usb_dev *udev, usb_req *req)
{
    uint8_t status = REQ_NOTSUPP;

    custom_hid_handler *hid = (custom_hid_handler *)udev->class_data[CUSTOM_HID_INTERFACE];

    switch (req->bRequest) {
    case USB_GET_DESCRIPTOR:
        if (USB_DESCTYPE_REPORT == (req->wValue >> 8)) {
            usb_transc_config(&udev->transc_in[0],
                              (uint8_t *)customhid_report_descriptor,
                              USB_MIN(DESC_LEN_REPORT, req->wLength),
                              0U);

            status = REQ_SUPP;
        }
        break;

    case GET_REPORT:
        if (2U == req->wLength) {
            usb_transc_config(&udev->transc_in[0], hid->data, 2U, 0U);

            status = REQ_SUPP;
        }
        break;

    case GET_IDLE:
        usb_transc_config(&udev->transc_in[0], (uint8_t *)&hid->idlestate, 1U, 0U);

        status = REQ_SUPP;
        break;

    case GET_PROTOCOL:
        usb_transc_config(&udev->transc_in[0], (uint8_t *)&hid->protocol, 1U, 0U);

        status = REQ_SUPP;
        break;

    case SET_REPORT:
        hid->reportID = (uint8_t)(req->wValue);

        usb_transc_config(&udev->transc_out[0], hid->data, req->wLength, 0U);

        status = REQ_SUPP;
        break;

    case SET_IDLE:
        hid->idlestate = (uint8_t)(req->wValue >> 8);

        status = REQ_SUPP;
        break;

    case SET_PROTOCOL:
        hid->protocol = (uint8_t)(req->wValue);

        status = REQ_SUPP;
        break;

    default:
        break;
    }

    return status;
}

/*!
    \brief      handle custom HID data in transaction
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     none
*/
static void custom_hid_data_in (usb_dev *udev, uint8_t ep_num)
{
    return;
}

/*!
    \brief      handle custom HID data out transaction
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     none
*/
static void custom_hid_data_out (usb_dev *udev, uint8_t ep_num)
{
    custom_hid_handler *hid = (custom_hid_handler *)udev->class_data[CUSTOM_HID_INTERFACE];

    if (CUSTOMHID_OUT_EP == ep_num){
        switch (hid->data[0]){
        case 0x11:
            if (RESET != hid->data[1]) {
                /* turn on led5  */
                gd_eval_led_on(LED5);
            } else {
                gd_eval_led_off(LED5);
            }
            break;
        case 0x12:
            if (RESET != hid->data[1]) {
                gd_eval_led_on(LED2);
            } else {
                gd_eval_led_off(LED2);
            }
            break;
        case 0x13:
            if (RESET != hid->data[1]) {
                gd_eval_led_on(LED3);
            } else {
                gd_eval_led_off(LED3);
            }
            break;
        case 0x14:
            if (RESET != hid->data[1]) {
                gd_eval_led_on(LED4);
            } else {
                gd_eval_led_off(LED4);
            }
            break;
        default:
            /* turn off all leds */
            gd_eval_led_off(LED2);
            gd_eval_led_off(LED3);
            gd_eval_led_off(LED4);
            gd_eval_led_off(LED5);
            break;
        }

        usbd_ep_recev(udev, CUSTOMHID_IN_EP, hid->data, 2U);
    }
}
