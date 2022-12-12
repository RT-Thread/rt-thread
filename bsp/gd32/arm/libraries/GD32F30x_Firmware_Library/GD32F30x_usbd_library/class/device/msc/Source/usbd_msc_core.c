/*!
    \file    usbd_msc_core.c
    \brief   USB MSC device class core functions

    \version 2020-08-01, V3.0.0, firmware for GD32F30x
    \version 2021-02-20, V3.0.1, firmware for GD32F30x
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

#include "usbd_enum.h"
#include "usbd_msc_bbb.h"
#include "usbd_msc_core.h"
#include "usbd_transc.h"
#include <string.h>

#define USBD_VID                    0x28E9U
#define USBD_PID                    0x128FU

/* local function prototypes ('static') */
static uint8_t msc_core_init   (usb_dev *udev, uint8_t config_index);
static uint8_t msc_core_deinit (usb_dev *udev, uint8_t config_index);
static uint8_t msc_core_req    (usb_dev *udev, usb_req *req);
static void msc_core_in     (usb_dev *udev, uint8_t ep_num);
static void msc_core_out    (usb_dev *udev, uint8_t ep_num);

usb_class msc_class =
{
    .init     = msc_core_init,
    .deinit   = msc_core_deinit,

    .req_process = msc_core_req,

    .data_in  = msc_core_in,
    .data_out = msc_core_out
};

/* note: it should use the C99 standard when compiling the below codes */
/* USB standard device descriptor */
const usb_desc_dev msc_dev_desc =
{
    .header = {
        .bLength           = USB_DEV_DESC_LEN,
        .bDescriptorType   = USB_DESCTYPE_DEV
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
    .bNumberConfigurations = USBD_CFG_MAX_NUM
};

/* USB device configuration descriptor */
const usb_desc_config_set msc_config_desc =
{
    .config =
    {
        .header = {
            .bLength         = sizeof(usb_desc_config),
            .bDescriptorType = USB_DESCTYPE_CONFIG
        },
        .wTotalLength        = USB_MSC_CONFIG_DESC_SIZE,
        .bNumInterfaces      = 0x01U,
        .bConfigurationValue = 0x01U,
        .iConfiguration      = 0x00U,
        .bmAttributes        = 0xC0U,
        .bMaxPower           = 0x32U
    },

    .msc_itf =
    {
        .header = {
            .bLength         = sizeof(usb_desc_itf),
            .bDescriptorType = USB_DESCTYPE_ITF
        },
        .bInterfaceNumber    = 0x00U,
        .bAlternateSetting   = 0x00U,
        .bNumEndpoints       = 0x02U,
        .bInterfaceClass     = USB_CLASS_MSC,
        .bInterfaceSubClass  = USB_MSC_SUBCLASS_SCSI,
        .bInterfaceProtocol  = USB_MSC_PROTOCOL_BBB,
        .iInterface          = 0x00U
    },

    .msc_epin =
    {
        .header = {
            .bLength         = sizeof(usb_desc_ep),
            .bDescriptorType = USB_DESCTYPE_EP
        },
        .bEndpointAddress    = MSC_IN_EP,
        .bmAttributes        = USB_EP_ATTR_BULK,
        .wMaxPacketSize      = MSC_EPIN_SIZE,
        .bInterval           = 0x00U
    },

    .msc_epout =
    {
        .header = {
            .bLength         = sizeof(usb_desc_ep),
            .bDescriptorType = USB_DESCTYPE_EP
        },
        .bEndpointAddress    = MSC_OUT_EP,
        .bmAttributes        = USB_EP_ATTR_BULK,
        .wMaxPacketSize      = MSC_EPOUT_SIZE,
        .bInterval           = 0x00U
    }
};

/* USB language ID descriptor */
const usb_desc_LANGID usbd_language_id_desc =
{
    .header =
     {
         .bLength            = sizeof(usb_desc_LANGID),
         .bDescriptorType    = USB_DESCTYPE_STR
     },
    .wLANGID                 = ENG_LANGID
};

/* USB manufacture string */
static const usb_desc_str manufacturer_string =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(10U),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
    .unicode_string = {'G', 'i', 'g', 'a', 'D', 'e', 'v', 'i', 'c', 'e'}
};

/* USB product string */
static const usb_desc_str product_string =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(12U),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
    .unicode_string = {'G', 'D', '3', '2', '-', 'U', 'S', 'B', '_', 'M', 'S', 'C'}
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
uint8_t* usbd_msc_strings[] =
{
    [STR_IDX_LANGID]  = (uint8_t *)&usbd_language_id_desc,
    [STR_IDX_MFC]     = (uint8_t *)&manufacturer_string,
    [STR_IDX_PRODUCT] = (uint8_t *)&product_string,
    [STR_IDX_SERIAL]  = (uint8_t *)&serial_string
};

usb_desc msc_desc = {
    .dev_desc    = (uint8_t *)&msc_dev_desc,
    .config_desc = (uint8_t *)&msc_config_desc,
    .strings     = usbd_msc_strings
};

static uint8_t usbd_msc_maxlun = 0U;

/*!
    \brief      initialize the MSC device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t msc_core_init (usb_dev *udev, uint8_t config_index)
{
    static usbd_msc_handler msc_handler;

    memset((void *)&msc_handler, 0U, sizeof(usbd_msc_handler));

    udev->class_data[USBD_MSC_INTERFACE] = (void *)&msc_handler;

    /* initialize Tx endpoint */
    usbd_ep_init(udev, EP_BUF_SNG, BULK_TX_ADDR, &(msc_config_desc.msc_epin));

    /* initialize Rx endpoint */
    usbd_ep_init(udev, EP_BUF_SNG, BULK_RX_ADDR, &(msc_config_desc.msc_epout));

    udev->ep_transc[EP_ID(MSC_IN_EP)][TRANSC_IN] = msc_class.data_in;
    udev->ep_transc[MSC_OUT_EP][TRANSC_OUT] = msc_class.data_out;

    /* initialize the BBB layer */
    msc_bbb_init(udev);

    return USBD_OK;
}

/*!
    \brief      deinitialize the MSC device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t msc_core_deinit (usb_dev *udev, uint8_t config_index)
{
    /* clear MSC endpoints */
    usbd_ep_deinit (udev, MSC_IN_EP);
    usbd_ep_deinit (udev, MSC_OUT_EP);

    /* deinitialize the BBB layer */
    msc_bbb_deinit(udev);

    return USBD_OK;
}

/*!
    \brief      handle the MSC class-specific and standard requests
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: device class-specific request
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t msc_core_req (usb_dev *udev, usb_req *req)
{
    switch (req->bRequest) {
    case BBB_GET_MAX_LUN :
        if((0U == req->wValue) &&
            (1U == req->wLength) &&
            (0x80U == (req->bmRequestType & 0x80U))) {
            usbd_msc_maxlun = (uint8_t)usbd_mem_fops->mem_maxlun();

            usb_transc_config(&udev->transc_in[0], &usbd_msc_maxlun, 1U, 0U);
        } else {
            return USBD_FAIL;
        }
        break;

    case BBB_RESET :
        if((0U == req->wValue) &&
            (0U == req->wLength) &&
             (0x80U != (req->bmRequestType & 0x80U))) {
            msc_bbb_reset(udev);
        } else {
            return USBD_FAIL;
        }
        break;

    case USB_CLEAR_FEATURE:
        msc_bbb_clrfeature (udev, (uint8_t)req->wIndex);
        break;

    default:
        return USBD_FAIL;
    }

    return USBD_OK;
}

/*!
    \brief      handle data in stage
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: the endpoint number
    \param[out] none
    \retval     none
*/
static void msc_core_in (usb_dev *udev, uint8_t ep_num)
{
    msc_bbb_data_in(udev, ep_num);
}

/*!
    \brief      handle data out stage
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: the endpoint number
    \param[out] none
    \retval     none
*/
static void msc_core_out (usb_dev *udev, uint8_t ep_num)
{
    msc_bbb_data_out (udev, ep_num);
}
