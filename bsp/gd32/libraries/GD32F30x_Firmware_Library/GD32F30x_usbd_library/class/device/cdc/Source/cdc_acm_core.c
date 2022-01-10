/*!
    \file    cdc_acm_core.c
    \brief   CDC ACM driver

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
#include "cdc_acm_core.h"

#define USBD_VID                          0x28E9U
#define USBD_PID                          0x018AU

/* note:it should use the C99 standard when compiling the below codes */
/* USB standard device descriptor */
usb_desc_dev cdc_dev_desc =
{
    .header =
     {
         .bLength          = USB_DEV_DESC_LEN,
         .bDescriptorType  = USB_DESCTYPE_DEV,
     },
    .bcdUSB                = 0x0200U,
    .bDeviceClass          = USB_CLASS_CDC,
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
usb_cdc_desc_config_set cdc_config_desc =
{
    .config =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_config),
             .bDescriptorType = USB_DESCTYPE_CONFIG,
         },
        .wTotalLength         = USB_CDC_ACM_CONFIG_DESC_SIZE,
        .bNumInterfaces       = 0x02U,
        .bConfigurationValue  = 0x01U,
        .iConfiguration       = 0x00U,
        .bmAttributes         = 0x80U,
        .bMaxPower            = 0x32U
    },

    .cmd_itf =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_itf),
             .bDescriptorType = USB_DESCTYPE_ITF
         },
        .bInterfaceNumber     = 0x00U,
        .bAlternateSetting    = 0x00U,
        .bNumEndpoints        = 0x01U,
        .bInterfaceClass      = USB_CLASS_CDC,
        .bInterfaceSubClass   = USB_CDC_SUBCLASS_ACM,
        .bInterfaceProtocol   = USB_CDC_PROTOCOL_AT,
        .iInterface           = 0x00U
    },

    .cdc_header =
    {
        .header =
         {
            .bLength         = sizeof(usb_desc_header_func),
            .bDescriptorType = USB_DESCTYPE_CS_INTERFACE
         },
        .bDescriptorSubtype  = 0x00U,
        .bcdCDC              = 0x0110U
    },

    .cdc_call_managment =
    {
        .header =
         {
            .bLength         = sizeof(usb_desc_call_managment_func),
            .bDescriptorType = USB_DESCTYPE_CS_INTERFACE
         },
        .bDescriptorSubtype  = 0x01U,
        .bmCapabilities      = 0x00U,
        .bDataInterface      = 0x01U
    },

    .cdc_acm =
    {
        .header =
         {
            .bLength         = sizeof(usb_desc_acm_func),
            .bDescriptorType = USB_DESCTYPE_CS_INTERFACE
         },
        .bDescriptorSubtype  = 0x02U,
        .bmCapabilities      = 0x02U,
    },

    .cdc_union =
    {
        .header =
         {
            .bLength         = sizeof(usb_desc_union_func),
            .bDescriptorType = USB_DESCTYPE_CS_INTERFACE
         },
        .bDescriptorSubtype  = 0x06U,
        .bMasterInterface    = 0x00U,
        .bSlaveInterface0    = 0x01U,
    },

    .cdc_cmd_endpoint =
    {
        .header =
         {
            .bLength         = sizeof(usb_desc_ep),
            .bDescriptorType = USB_DESCTYPE_EP,
         },
        .bEndpointAddress    = CDC_CMD_EP,
        .bmAttributes        = USB_EP_ATTR_INT,
        .wMaxPacketSize      = CDC_ACM_CMD_PACKET_SIZE,
        .bInterval           = 0x0AU
    },

    .cdc_data_interface =
    {
        .header =
         {
            .bLength         = sizeof(usb_desc_itf),
            .bDescriptorType = USB_DESCTYPE_ITF,
         },
        .bInterfaceNumber    = 0x01U,
        .bAlternateSetting   = 0x00U,
        .bNumEndpoints       = 0x02U,
        .bInterfaceClass     = USB_CLASS_DATA,
        .bInterfaceSubClass  = 0x00U,
        .bInterfaceProtocol  = USB_CDC_PROTOCOL_NONE,
        .iInterface          = 0x00U
    },

    .cdc_out_endpoint =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_ep),
             .bDescriptorType = USB_DESCTYPE_EP,
         },
        .bEndpointAddress     = CDC_OUT_EP,
        .bmAttributes         = USB_EP_ATTR_BULK,
        .wMaxPacketSize       = CDC_ACM_DATA_PACKET_SIZE,
        .bInterval            = 0x00U
    },

    .cdc_in_endpoint =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
        .bEndpointAddress     = CDC_IN_EP,
        .bmAttributes         = USB_EP_ATTR_BULK,
        .wMaxPacketSize       = CDC_ACM_DATA_PACKET_SIZE,
        .bInterval            = 0x00U
    }
};

/* USB language ID descriptor */
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
         .bLength         = USB_STRING_LEN(12U),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
    .unicode_string = {'G', 'D', '3', '2', '-', 'C', 'D', 'C', '_', 'A', 'C', 'M'}
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

/* USB string descriptor set */
uint8_t* usbd_cdc_strings[] =
{
    [STR_IDX_LANGID]  = (uint8_t *)&usbd_language_id_desc,
    [STR_IDX_MFC]     = (uint8_t *)&manufacturer_string,
    [STR_IDX_PRODUCT] = (uint8_t *)&product_string,
    [STR_IDX_SERIAL]  = (uint8_t *)&serial_string
};

usb_desc cdc_desc = {
    .dev_desc    = (uint8_t *)&cdc_dev_desc,
    .config_desc = (uint8_t *)&cdc_config_desc,
    .strings     = usbd_cdc_strings
};

/* local function prototypes ('static') */
static uint8_t cdc_acm_init         (usb_dev *udev, uint8_t config_index);
static uint8_t cdc_acm_deinit       (usb_dev *udev, uint8_t config_index);
static uint8_t cdc_acm_req_handler  (usb_dev *udev, usb_req *req);
static uint8_t cdc_acm_ctlx_out     (usb_dev *udev);
static void cdc_acm_data_in         (usb_dev *udev, uint8_t ep_num);
static void cdc_acm_data_out        (usb_dev *udev, uint8_t ep_num);

usb_class cdc_class = {
    .req_cmd       = NO_CMD,

    .init          = cdc_acm_init,
    .deinit        = cdc_acm_deinit,
    .req_process   = cdc_acm_req_handler,
    .ctlx_out      = cdc_acm_ctlx_out,
    .data_in       = cdc_acm_data_in,
    .data_out      = cdc_acm_data_out
};

/*!
    \brief      receive CDC ACM data
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
void cdc_acm_data_receive(usb_dev *udev)
{
    usb_cdc_handler *cdc = (usb_cdc_handler *)udev->class_data[CDC_COM_INTERFACE];

    cdc->packet_receive = 0U;
    cdc->pre_packet_send = 0U;

    usbd_ep_recev(udev, CDC_OUT_EP, (uint8_t*)(cdc->data), USB_CDC_RX_LEN);
}

/*!
    \brief      send CDC ACM data
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
void cdc_acm_data_send (usb_dev *udev)
{
    usb_cdc_handler *cdc = (usb_cdc_handler *)udev->class_data[CDC_COM_INTERFACE];
    uint32_t data_len = cdc->receive_length;

    if ((0U != data_len) && (1U == cdc->packet_sent)) {
        cdc->packet_sent = 0U;
        usbd_ep_send(udev, CDC_IN_EP, (uint8_t*)(cdc->data), (uint16_t)data_len);
        cdc->receive_length = 0U;
    }
}

/*!
    \brief      check cdc acm is ready for data transfer
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     0 if CDC is ready, 5 otherwise
*/
uint8_t cdc_acm_check_ready(usb_dev *udev)
{
    if (udev->class_data[CDC_COM_INTERFACE] != NULL) {
        usb_cdc_handler *cdc = (usb_cdc_handler *)udev->class_data[CDC_COM_INTERFACE];

        if ((1U == cdc->packet_receive) && (1U == cdc->pre_packet_send)) {
            return 0U;
        }
    }

    return 5U;
}

/*!
    \brief      initialize the CDC ACM device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t cdc_acm_init (usb_dev *udev, uint8_t config_index)
{
    static usb_cdc_handler cdc_handler;

    /* initialize the data endpoints */
    usbd_ep_init(udev, EP_BUF_SNG, BULK_TX_ADDR, &(cdc_config_desc.cdc_in_endpoint));
    usbd_ep_init(udev, EP_BUF_SNG, BULK_RX_ADDR, &(cdc_config_desc.cdc_out_endpoint));

    /* initialize the command endpoint */
    usbd_ep_init(udev, EP_BUF_SNG, INT_TX_ADDR, &(cdc_config_desc.cdc_cmd_endpoint));

    udev->ep_transc[EP_ID(CDC_IN_EP)][TRANSC_IN] = cdc_class.data_in;
    udev->ep_transc[CDC_OUT_EP][TRANSC_OUT] = cdc_class.data_out;

    /* initialize cdc handler structure */
    cdc_handler.packet_receive = 0U;
    cdc_handler.packet_sent = 1U;
    cdc_handler.pre_packet_send = 1U;
    cdc_handler.receive_length = 0U;

    cdc_handler.line_coding = (acm_line){
        .dwDTERate   = 115200U,
        .bCharFormat = 0U,
        .bParityType = 0U,
        .bDataBits   = 0x08U
    };

    udev->class_data[CDC_COM_INTERFACE] = (void *)&cdc_handler;

    return USBD_OK;
}

/*!
    \brief      de-initialize the CDC ACM device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t cdc_acm_deinit (usb_dev *udev, uint8_t config_index)
{
    /* deinitialize the data endpoints */
    usbd_ep_deinit(udev, CDC_IN_EP);
    usbd_ep_deinit(udev, CDC_OUT_EP);

    /* deinitialize the command endpoint */
    usbd_ep_deinit(udev, CDC_CMD_EP);

    return USBD_OK;
}

/*!
    \brief      command data received on control endpoint
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t cdc_acm_ctlx_out (usb_dev *udev)
{
    usb_cdc_handler *cdc = (usb_cdc_handler *)udev->class_data[CDC_COM_INTERFACE];

    if (NO_CMD != udev->class_core->req_cmd) {
        cdc->packet_receive = 1U;
        cdc->pre_packet_send = 1U;

        udev->class_core->req_cmd = NO_CMD;
    }

    return USBD_OK;
}


/*!
    \brief      handle CDC ACM data in transaction
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     USB device operation status
*/
static void cdc_acm_data_in (usb_dev *udev, uint8_t ep_num)
{
    usb_transc *transc = &udev->transc_in[ep_num];
    usb_cdc_handler *cdc = (usb_cdc_handler *)udev->class_data[CDC_COM_INTERFACE];

    if (transc->xfer_count == transc->max_len) {
        usbd_ep_send(udev, EP_ID(ep_num), NULL, 0U);
    } else {
        cdc->packet_sent = 1U;
        cdc->pre_packet_send = 1U;
    }
}

/*!
    \brief      handle CDC ACM data out transaction
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     USB device operation status
*/
static void cdc_acm_data_out (usb_dev *udev, uint8_t ep_num)
{
    usb_cdc_handler *cdc = (usb_cdc_handler *)udev->class_data[CDC_COM_INTERFACE];

    cdc->packet_receive = 1U;

    cdc->receive_length = udev->transc_out[ep_num].xfer_count;
}

/*!
    \brief      handle the CDC ACM class-specific requests
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: device class-specific request
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t cdc_acm_req_handler (usb_dev *udev, usb_req *req)
{
    uint8_t status = REQ_NOTSUPP, noti_buf[10] = {0U};
    usb_cdc_handler *cdc = (usb_cdc_handler *)udev->class_data[CDC_COM_INTERFACE];

    acm_notification *notif = (void *)noti_buf;

    switch (req->bRequest) {
    case SEND_ENCAPSULATED_COMMAND:
        break;

    case GET_ENCAPSULATED_RESPONSE:
        break;

    case SET_COMM_FEATURE:
        break;

    case GET_COMM_FEATURE:
        break;

    case CLEAR_COMM_FEATURE:
        break;

    case SET_LINE_CODING:
        /* set the value of the current command to be processed */
        udev->class_core->req_cmd = req->bRequest;

        usb_transc_config(&udev->transc_out[0U], (uint8_t *)&cdc->line_coding, req->wLength, 0U);

        status = REQ_SUPP;
        break;

    case GET_LINE_CODING:
        usb_transc_config(&udev->transc_in[0U], (uint8_t *)&cdc->line_coding, 7U, 0U);

        status = REQ_SUPP;
        break;

    case SET_CONTROL_LINE_STATE:
        notif->bmRequestType = 0xA1U;
        notif->bNotification = USB_CDC_NOTIFY_SERIAL_STATE;
        notif->wIndex = 0U;
        notif->wValue = 0U;
        notif->wLength = 2U;
        noti_buf[8] = (uint8_t)req->wValue & 3U;
        noti_buf[9] = 0U;

        status = REQ_SUPP;
        break;

    case SEND_BREAK:
        break;

    default:
        break;
    }

    return status;
}
