/*!
    \file    usb_iap_core.c
    \brief   IAP driver

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
#include "usb_iap_core.h"
#include <string.h>

#define USBD_VID                     0x28E9U
#define USBD_PID                     0x028BU

/* Note:it should use the C99 standard when compiling the below codes */
/* USB standard device descriptor */
usb_desc_dev iap_dev_desc =
{
    .header =
     {
         .bLength          = USB_DEV_DESC_LEN,
         .bDescriptorType  = USB_DESCTYPE_DEV
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

usb_hid_desc_config_set iap_config_desc =
{
    .config =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_config),
             .bDescriptorType = USB_DESCTYPE_CONFIG
         },
        .wTotalLength         = USB_DESC_LEN_IAP_CONFIG_SET,
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
        .bInterfaceProtocol   = 0x01U,
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
        .wDescriptorLength    = USB_DESC_LEN_IAP_REPORT,
    },

    .hid_epin =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
        .bEndpointAddress     = IAP_IN_EP,
        .bmAttributes         = USB_EP_ATTR_INT,
        .wMaxPacketSize       = IAP_IN_PACKET,
        .bInterval            = 0x01U
    },

    .hid_epout =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
        .bEndpointAddress     = IAP_OUT_EP,
        .bmAttributes         = USB_EP_ATTR_INT,
        .wMaxPacketSize       = IAP_OUT_PACKET,
        .bInterval            = 0x01U
    }
};

/* USB language ID Descriptor */
usb_desc_LANGID usbd_language_id_desc =
{
    .header =
     {
         .bLength         = sizeof(usb_desc_LANGID),
         .bDescriptorType = USB_DESCTYPE_STR
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
         .bLength         = USB_STRING_LEN(12U),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
    .unicode_string = {'G', 'D', '3', '2', '-', 'U', 'S', 'B', '_', 'I', 'A', 'P'}
};

/* USBD serial string */
static usb_desc_str serial_string =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(2U),
         .bDescriptorType = USB_DESCTYPE_STR,
     }
};

uint8_t* usbd_iap_strings[] =
{
    [STR_IDX_LANGID]  = (uint8_t *)&usbd_language_id_desc,
    [STR_IDX_MFC]     = (uint8_t *)&manufacturer_string,
    [STR_IDX_PRODUCT] = (uint8_t *)&product_string,
    [STR_IDX_SERIAL]  = (uint8_t *)&serial_string
};

usb_desc iap_desc = {
    .dev_desc    = (uint8_t *)&iap_dev_desc,
    .config_desc = (uint8_t *)&iap_config_desc,
    .strings     = usbd_iap_strings
};

/* local function prototypes ('static') */
static uint8_t iap_init        (usb_dev *udev, uint8_t config_index);
static uint8_t iap_deinit      (usb_dev *udev, uint8_t config_index);
static uint8_t iap_req_handler (usb_dev *udev, usb_req *req);
static void    iap_data_out    (usb_dev *udev, uint8_t ep_num);

usb_class iap_class = {
    .init            = iap_init,
    .deinit          = iap_deinit,
    .req_process     = iap_req_handler,
    .data_out        = iap_data_out
};

/* USB custom HID device report descriptor */
const uint8_t iap_report_desc[USB_DESC_LEN_IAP_REPORT] =
{
    0x05, 0x01,     /* USAGE_PAGE (Generic Desktop) */
    0x09, 0x00,     /* USAGE (Custom Device)        */
    0xa1, 0x01,     /* COLLECTION (Application)     */

    /* IAP command and data */
    0x85, 0x01,     /* REPORT_ID (0x01)          */
    0x09, 0x01,     /* USAGE (IAP command)       */
    0x15, 0x00,     /* LOGICAL_MINIMUM (0)       */
    0x25, 0xff,     /* LOGICAL_MAXIMUM (255)     */
    0x75, 0x08,     /* REPORT_SIZE (8)           */
    0x95, 0x3f,     /* REPORT_COUNT (63)         */
    0x91, 0x82,     /* OUTPUT (Data,Var,Abs,Vol) */

    /* device status and option byte */
    0x85, 0x02,     /* REPORT_ID (0x02)               */
    0x09, 0x02,     /* USAGE (Status and option byte) */
    0x15, 0x00,     /* LOGICAL_MINIMUM (0)            */
    0x25, 0xff,     /* LOGICAL_MAXIMUM (255)          */
    0x75, 0x08,     /* REPORT_SIZE (8)                */
    0x95, 0x10,     /* REPORT_COUNT (16)              */
    0x81, 0x82,     /* INPUT (Data,Var,Abs,Vol)       */

    0xc0            /* END_COLLECTION            */
};

/* IAP requests management functions */
static void iap_req_erase     (usb_dev *udev);
static void iap_req_dnload    (usb_dev *udev);
static void iap_req_optionbyte(usb_dev *udev);
static void iap_req_leave     (usb_dev *udev);
static void iap_address_send  (usb_dev *udev);
static void iap_data_write (uint8_t *data, uint32_t addr, uint32_t len);

/*!
    \brief      initialize the HID device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t iap_init (usb_dev *udev, uint8_t config_index)
{
    static usbd_iap_handler iap_handler;

    /* initialize Tx endpoint */
    usbd_ep_init(udev, EP_BUF_SNG, INT_TX_ADDR, &(iap_config_desc.hid_epin));

    /* initialize Rx endpoint */
    usbd_ep_init(udev, EP_BUF_SNG, INT_RX_ADDR, &(iap_config_desc.hid_epout));

    /* unlock the internal flash */
    fmc_unlock();

    memset((void *)&iap_handler, 0, sizeof(usbd_iap_handler));

    /* prepare receive Data */
    usbd_ep_recev(udev, IAP_OUT_EP, iap_handler.report_buf, IAP_OUT_PACKET);

    udev->ep_transc[EP_ID(IAP_OUT_EP)][TRANSC_OUT] = iap_class.data_out;

    iap_handler.base_address = APP_LOADED_ADDR;

    udev->class_data[USBD_IAP_INTERFACE] = (void *)&iap_handler;

    return USBD_OK;
}

/*!
    \brief      de-initialize the HID device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t iap_deinit (usb_dev *udev, uint8_t config_index)
{
    /* deinitialize HID endpoints */
    usbd_ep_deinit (udev, IAP_IN_EP);
    usbd_ep_deinit (udev, IAP_OUT_EP);

    /* lock the internal flash */
    fmc_lock();

    return USBD_OK;
}

/*!
    \brief      handle the HID class-specific requests
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: device class-specific request
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t iap_req_handler (usb_dev *udev, usb_req *req)
{
    uint8_t status = REQ_NOTSUPP;

    usbd_iap_handler *iap = (usbd_iap_handler *)udev->class_data[USBD_IAP_INTERFACE];

    switch (req->bRequest) {
    case GET_REPORT:
        /* no use for this driver */
        break;

    case GET_IDLE:
        usb_transc_config(&udev->transc_in[0], (uint8_t *)&iap->idlestate, 1U, 0U);

        status = REQ_SUPP;
        break;

    case GET_PROTOCOL:
        usb_transc_config(&udev->transc_in[0], (uint8_t *)&iap->protocol, 1U, 0U);

        status = REQ_SUPP;
        break;

    case SET_REPORT:
        iap->reportID = (uint8_t)(req->wValue);

        usb_transc_config(&udev->transc_out[0], iap->report_buf, req->wLength, 0U);

        status = REQ_SUPP;
        break;

    case SET_IDLE:
        iap->idlestate = (uint8_t)(req->wValue >> 8);

        status = REQ_SUPP;
        break;

    case SET_PROTOCOL:
        iap->protocol = (uint8_t)(req->wValue);

        status = REQ_SUPP;
        break;

    case USB_GET_DESCRIPTOR:
        if (USB_DESCTYPE_REPORT == (req->wValue >> 8)) {
            usb_transc_config(&udev->transc_in[0],
                              (uint8_t *)iap_report_desc,
                              USB_MIN(USB_DESC_LEN_IAP_REPORT, req->wLength),
                              0U);

            return REQ_SUPP;
        }
        break;

    default:
        break;
    }

    return status;
}

/*!
    \brief      handle data out stage
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     none
*/
static void iap_data_out (usb_dev *udev ,uint8_t ep_num)
{
    usbd_iap_handler *iap = (usbd_iap_handler *)udev->class_data[USBD_IAP_INTERFACE];

    if (0x01U == iap->report_buf[0]) {
        switch(iap->report_buf[1]) {
        case IAP_DNLOAD:
            iap_req_dnload(udev);
            break;

        case IAP_ERASE:
            iap_req_erase(udev);
            break;

        case IAP_OPTION_BYTE:
            iap_req_optionbyte(udev);
            break;

        case IAP_LEAVE:
            iap_req_leave(udev);
            break;

        case IAP_GETBIN_ADDRESS:
            iap_address_send(udev);
            break;

        default:
            break;
        }
    }

    usbd_ep_recev(udev, IAP_OUT_EP, iap->report_buf, IAP_OUT_PACKET);
}

/*!
    \brief      send iap report
    \param[in]  udev: pointer to USB device instance
    \param[in]  report: pointer to HID report
    \param[in]  len: data length
    \param[out] none
    \retval     USB device operation status
*/
uint8_t iap_report_send (usb_dev *udev, uint8_t *report, uint16_t len)
{
    usbd_ep_send (udev, IAP_IN_EP, report, len);

    return USBD_OK;
}

/*!
    \brief      handle the IAP_DNLOAD request
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static void iap_req_dnload (usb_dev *udev)
{
    usbd_iap_handler *iap = (usbd_iap_handler *)udev->class_data[USBD_IAP_INTERFACE];

    if (0U != iap->transfer_times) {
        if (1U == iap->transfer_times) {
            if (0U == iap->lps) {
                iap_data_write(&iap->report_buf[2], iap->base_address, TRANSFER_SIZE);
            } else {
                iap_data_write(&iap->report_buf[2], iap->base_address, iap->file_length % TRANSFER_SIZE);
                iap->lps = 0U;
            }

            iap->dev_status[0] = 0x02U;
            iap->dev_status[1] = 0x02U;
            iap_report_send (udev, iap->dev_status, IAP_IN_PACKET);
        } else {
            iap_data_write(&iap->report_buf[2], iap->base_address, TRANSFER_SIZE);

            iap->base_address += TRANSFER_SIZE;
        }

        iap->transfer_times--;
    }
}

/*!
    \brief      handle the IAP_ERASE request
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static void iap_req_erase (usb_dev *udev)
{
    uint32_t i, addr = 0U;

    usbd_iap_handler *iap = (usbd_iap_handler *)udev->class_data[USBD_IAP_INTERFACE];

    /* get base address to erase */
    iap->base_address = iap->report_buf[2];
    iap->base_address |= (uint32_t)iap->report_buf[3] << 8;
    iap->base_address |= (uint32_t)iap->report_buf[4] << 16;
    iap->base_address |= (uint32_t)iap->report_buf[5] << 24;

    iap->page_count = iap->report_buf[6];

    /* get file length */
    iap->file_length = iap->report_buf[7];
    iap->file_length |= (uint32_t)iap->report_buf[8] << 8;
    iap->file_length |= (uint32_t)iap->report_buf[9] << 16;
    iap->file_length |= (uint32_t)iap->report_buf[10] << 24;

    /* compute last packet size and transfer times */
    iap->lps = iap->file_length % TRANSFER_SIZE;
    if (0U == iap->lps) {
        iap->transfer_times = (uint16_t)iap->file_length / TRANSFER_SIZE;
    } else {
        iap->transfer_times = (uint16_t)iap->file_length / TRANSFER_SIZE + 1U;
    }

    /* check if the address is in protected area */
    if (IS_PROTECTED_AREA(iap->base_address)) {
        return;
    }

    addr = iap->base_address;

    for (i = 0U; i < iap->page_count; i ++) {
        /* call the standard flash erase-page function */
        fmc_page_erase(addr);

        addr += PAGE_SIZE;
    }

    iap->dev_status[0] = 0x02U;
    iap->dev_status[1] = 0x01U;

    usbd_ep_send(udev, IAP_IN_EP, iap->dev_status, IAP_IN_PACKET);
}

/*!
    \brief      handle the IAP_OPTION_BYTE request
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static void iap_req_optionbyte (usb_dev *udev)
{
    uint8_t i = 0U;
    uint32_t address = 0x1FFFF800U;

    usbd_iap_handler *iap = (usbd_iap_handler *)udev->class_data[USBD_IAP_INTERFACE];

    iap->option_byte[0] = 0x02U;

    for (i = 1U; i < 17U; i++) {
        iap->option_byte[i] = *(uint8_t *)address;
        address++;
    }

    iap_report_send(udev, iap->option_byte, IAP_IN_PACKET);
}

/*!
    \brief      handle the IAP_LEAVE request
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static void iap_req_leave (usb_dev *udev)
{
    /* lock the internal flash */
    fmc_lock();

    /* generate system reset to allow jumping to the user code */
    NVIC_SystemReset();
}

/*!
    \brief      handle the IAP_SEND_ADDRESS request
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static void iap_address_send(usb_dev *udev)
{
    usbd_iap_handler *iap = (usbd_iap_handler *)udev->class_data[USBD_IAP_INTERFACE];

    iap->bin_addr[0] = 0x02U;

    iap->bin_addr[1] = (uint8_t)(APP_LOADED_ADDR);
    iap->bin_addr[2] = (uint8_t)(APP_LOADED_ADDR >> 8);
    iap->bin_addr[3] = (uint8_t)(APP_LOADED_ADDR >> 16);
    iap->bin_addr[4] = (uint8_t)(APP_LOADED_ADDR >> 24);

    iap_report_send (udev, iap->bin_addr, IAP_IN_PACKET);
}

/*!
    \brief      write data to sectors of memory
    \param[in]  data: data to be written
    \param[in]  addr: sector address/code
    \param[in]  len: length of data to be written (in bytes)
    \param[out] none
    \retval     MAL_OK if all operations are OK, MAL_FAIL else
*/
static void iap_data_write (uint8_t *data, uint32_t addr, uint32_t len)
{
    uint32_t index = 0U;

    /* check if the address is in protected area */
    if (IS_PROTECTED_AREA(addr)) {
        return;
    }

    if (len & 0x03U) {/* not an aligned data */
        for (index = len; index < ((len & 0xFFFCU) + 4U); index++) {
            data[index] = 0xFFU;
        }
    }

    /* data received are word multiple */
    for (index = 0U; index < len; index += 4U) {
        fmc_word_program(addr, *(uint32_t *)(data + index));
        addr += 4U;
    }
}
