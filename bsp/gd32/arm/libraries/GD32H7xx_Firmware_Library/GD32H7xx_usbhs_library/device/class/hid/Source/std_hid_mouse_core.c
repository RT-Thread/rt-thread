/*!
    \file    std_hid_mouse_core.c
    \brief   HID class driver

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

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

#include "std_hid_mouse_core.h"
#include <string.h>

#define USBD_VID                     0x28e9U
#define USBD_PID                     0x0381U

/* Note:it should use the C99 standard when compiling the below codes */
/* USB standard device descriptor */
const usb_desc_dev hid_dev_desc = {
    .header =
    {
        .bLength          = USB_DEV_DESC_LEN,
        .bDescriptorType  = USB_DESCTYPE_DEV
    },
    .bcdUSB                = 0x0200U,
    .bDeviceClass          = 0x00U,
    .bDeviceSubClass       = 0x00U,
    .bDeviceProtocol       = 0x00U,
    .bMaxPacketSize0       = USB_FS_EP0_MAX_LEN,
    .idVendor              = USBD_VID,
    .idProduct             = USBD_PID,
    .bcdDevice             = 0x0100U,
    .iManufacturer         = STR_IDX_MFC,
    .iProduct              = STR_IDX_PRODUCT,
    .iSerialNumber         = STR_IDX_SERIAL,
    .bNumberConfigurations = USBD_CFG_MAX_NUM
};

const usb_hid_desc_config_set hid_config_desc = {
    .config =
    {
        .header =
        {
            .bLength         = sizeof(usb_desc_config),
            .bDescriptorType = USB_DESCTYPE_CONFIG
        },
        .wTotalLength         = USB_HID_CONFIG_DESC_LEN,
        .bNumInterfaces       = 0x01U,
        .bConfigurationValue  = 0x01U,
        .iConfiguration       = 0x00U,
        .bmAttributes         = 0xA0U,
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
        .bNumEndpoints        = 0x01U,
        .bInterfaceClass      = USB_HID_CLASS,
        .bInterfaceSubClass   = USB_HID_SUBCLASS_BOOT_ITF,
        .bInterfaceProtocol   = USB_HID_PROTOCOL_MOUSE,
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
        .wDescriptorLength    = USB_HID_REPORT_DESC_LEN,
    },

    .hid_epin =
    {
        .header =
        {
            .bLength         = sizeof(usb_desc_ep),
            .bDescriptorType = USB_DESCTYPE_EP
        },
        .bEndpointAddress     = HID_IN_EP,
        .bmAttributes         = USB_EP_ATTR_INT,
        .wMaxPacketSize       = HID_IN_PACKET,
        .bInterval            = 0x40U
    }
};

/* USB language ID Descriptor */
const usb_desc_LANGID usbd_language_id_desc = {
    .header =
    {
        .bLength         = sizeof(usb_desc_LANGID),
        .bDescriptorType = USB_DESCTYPE_STR
    },
    .wLANGID              = ENG_LANGID
};

/* USB manufacture string */
static const usb_desc_str manufacturer_string = {
    .header =
    {
        .bLength         = USB_STRING_LEN(10),
        .bDescriptorType = USB_DESCTYPE_STR,
    },
    .unicode_string = {'G', 'i', 'g', 'a', 'D', 'e', 'v', 'i', 'c', 'e'}
};

/* USB product string */
static const usb_desc_str product_string = {
    .header =
    {
        .bLength         = USB_STRING_LEN(14),
        .bDescriptorType = USB_DESCTYPE_STR,
    },
    .unicode_string = {'G', 'D', '3', '2', '-', 'U', 'S', 'B', '_', 'M', 'o', 'u', 's', 'e'}
};

/* USB serial string */
static usb_desc_str serial_string = {
    .header =
    {
        .bLength         = USB_STRING_LEN(12),
        .bDescriptorType = USB_DESCTYPE_STR,
    }
};

static void *const usbd_hid_strings[] = {
    [STR_IDX_LANGID]  = (uint8_t *) &usbd_language_id_desc,
    [STR_IDX_MFC]     = (uint8_t *) &manufacturer_string,
    [STR_IDX_PRODUCT] = (uint8_t *) &product_string,
    [STR_IDX_SERIAL]  = (uint8_t *) &serial_string
};

usb_desc hid_mouse_desc = {
    .dev_desc    = (uint8_t *) &hid_dev_desc,
    .config_desc = (uint8_t *) &hid_config_desc,
    .strings     = usbd_hid_strings
};

const uint8_t hid_report_desc[USB_HID_REPORT_DESC_LEN] = {
    0x05, 0x01,  /* USAGE_PAGE (Generic Desktop) */
    0x09, 0x02,  /* USAGE (Mouse) */
    0xa1, 0x01,  /* COLLECTION (Application) */
    0x09, 0x01,  /* USAGE (Pointer) */

    0xa1, 0x00,  /* COLLECTION (Physical) */
    0x05, 0x09,  /* USAGE_PAGE (Button) */
    0x19, 0x01,  /* USAGE_MINIMUM (1) */
    0x29, 0x03,  /* USAGE_MAXIMUM (3) */

    0x15, 0x00,  /* LOGICAL_MINIMUM (0) */
    0x25, 0x01,  /* LOGICAL_MAXIMUM (1) */
    0x95, 0x03,  /* REPORT_COUNT (3) */
    0x75, 0x01,  /* REPORT_SIZE (1) */
    0x81, 0x02,  /* INPUT (Data,Var,Abs) */

    0x95, 0x01,  /* REPORT_COUNT (1) */
    0x75, 0x05,  /* REPORT_SIZE (5) */
    0x81, 0x01,  /* INPUT (Cnst,Var,Abs) */

    0x05, 0x01,  /* USAGE_PAGE (Generic Desktop) */
    0x09, 0x30,  /* USAGE (X) */
    0x09, 0x31,  /* USAGE (Y) */
    0x09, 0x38,  /* USAGE (Wheel) */

    0x15, 0x81,  /* LOGICAL_MINIMUM (-127) */
    0x25, 0x7F,  /* LOGICAL_MAXIMUM (127) */
    0x75, 0x08,  /* REPORT_SIZE (8) */
    0x95, 0x03,  /* REPORT_COUNT (3) */
    0x81, 0x06,  /* INPUT (Data,Var,Rel) */
    0xc0,        /* END_COLLECTION */
    0xc0         /* END_COLLECTION */
};

/* local function prototypes ('static') */
static uint8_t hid_init(usb_dev *udev, uint8_t config_index);
static uint8_t hid_deinit(usb_dev *udev, uint8_t config_index);
static uint8_t hid_req(usb_dev *udev, usb_req *req);
static uint8_t hid_data_in(usb_dev *udev, uint8_t ep_num);

usb_class_core usbd_hid_cb = {
    .command         = NO_CMD,
    .alter_set       = 0U,

    .init            = hid_init,
    .deinit          = hid_deinit,
    .req_proc        = hid_req,
    .data_in         = hid_data_in
};

/*!
    \brief      register HID interface operation functions
    \param[in]  udev: pointer to USB device instance
    \param[in]  hid_fop: HID operation functions structure
    \param[out] none
    \retval     USB device operation status
*/
uint8_t hid_itfop_register(usb_dev *udev, mice_fop_handler *hid_fop)
{
    if(NULL != hid_fop)
    {
        udev->dev.user_data = (void *)hid_fop;

        return USBD_OK;
    }

    return USBD_FAIL;
}

/*!
    \brief      send mouse report
    \param[in]  udev: pointer to USB device instance
    \param[in]  report: pointer to HID report
    \param[in]  len: data length
    \param[out] none
    \retval     USB device operation status
*/
uint8_t hid_report_send(usb_dev *udev, uint8_t *report, uint16_t len)
{
    standard_mice_handler *hid = (standard_mice_handler *)udev->dev.class_data[USBD_HID_INTERFACE];

    if(USBD_CONFIGURED == udev->dev.cur_status)
    {
        if(1 == hid->prev_transfer_complete)
        {
            hid->prev_transfer_complete = 0U;
            usbd_ep_send(udev, HID_IN_EP, report, len);
        }
    }

    return USBD_OK;
}

/*!
    \brief      initialize the HID device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t hid_init(usb_dev *udev, uint8_t config_index)
{
    static standard_mice_handler mice_handler;

    memset((void *)&mice_handler, 0U, sizeof(standard_mice_handler));

    /* initialize the data Tx endpoint */
    usbd_ep_setup(udev, &(hid_config_desc.hid_epin));

    mice_handler.prev_transfer_complete = 1U;

    udev->dev.class_data[USBD_HID_INTERFACE] = (void *)&mice_handler;

    if(NULL != udev->dev.user_data)
    {
        ((mice_fop_handler *)(udev->dev.user_data))->mice_itf_config();
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
static uint8_t hid_deinit(usb_dev *udev, uint8_t config_index)
{
    /* deinitialize HID endpoints */
    usbd_ep_clear(udev, HID_IN_EP);

    return USBD_OK;
}

/*!
    \brief      handle the HID class-specific requests
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: device class-specific request
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t hid_req(usb_dev *udev, usb_req *req)
{
    usb_transc *transc = &udev->dev.transc_in[0];

    standard_mice_handler *hid = (standard_mice_handler *)udev->dev.class_data[USBD_HID_INTERFACE];

    switch(req->bRequest)
    {
    case GET_REPORT:
        /* no use for this driver */
        break;

    case GET_IDLE:
        transc->xfer_buf = (uint8_t *)&hid->idle_state;

        transc->remain_len = 1U;
        break;

    case GET_PROTOCOL:
        transc->xfer_buf = (uint8_t *)&hid->protocol;

        transc->remain_len = 1U;
        break;

    case SET_REPORT:
        /* no use for this driver */
        break;

    case SET_IDLE:
        hid->idle_state = (uint8_t)(req->wValue >> 8U);
        break;

    case SET_PROTOCOL:
        hid->protocol = (uint8_t)(req->wValue);
        break;

    case USB_GET_DESCRIPTOR:
        if(USB_DESCTYPE_REPORT == (req->wValue >> 8U))
        {
            transc->remain_len = USB_MIN(USB_HID_REPORT_DESC_LEN, req->wLength);
            transc->xfer_buf = (uint8_t *)hid_report_desc;

            return REQ_SUPP;
        }
        break;

    default:
        break;
    }

    return USBD_OK;
}

/*!
    \brief      handle data stage
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint identifier
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t hid_data_in(usb_dev *udev, uint8_t ep_num)
{
    standard_mice_handler *hid = (standard_mice_handler *)udev->dev.class_data[USBD_HID_INTERFACE];

    if(0U == hid->data[0])
    {
        hid->prev_transfer_complete = 1U;
    } else {
        hid->data[0] = 0U;
        usbd_ep_send(udev, HID_IN_EP, hid->data, HID_IN_PACKET);
    }

    return USBD_OK;
}
