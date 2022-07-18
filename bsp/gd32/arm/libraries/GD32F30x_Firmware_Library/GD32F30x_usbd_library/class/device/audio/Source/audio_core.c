/*!
    \file    audio_core.c
    \brief   USB audio device class core functions

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
#include "audio_out_itf.h"
#include "audio_core.h"
#include <string.h>

#define USBD_VID                     0x28E9U
#define USBD_PID                     0x9574U

/* local function prototypes ('static') */
static uint8_t usbd_audio_sof    (usb_dev *udev);
static uint8_t audio_init        (usb_dev *udev, uint8_t config_index);
static uint8_t audio_deinit      (usb_dev *udev, uint8_t config_index);
static uint8_t audio_req_handler (usb_dev *udev, usb_req *req);
static uint8_t audio_ctlx_out    (usb_dev *udev);
static void    audio_data_out    (usb_dev *udev, uint8_t ep_num);

usb_class audio_class = {
    .init        = audio_init,
    .deinit      = audio_deinit,
    .req_process = audio_req_handler,
    .ctlx_out    = audio_ctlx_out,
    .data_out    = audio_data_out
};

usbd_int_cb_struct usb_inthandler =
{
    usbd_audio_sof,
};

/* note:it should use the c99 standard when compiling the below codes */
/* USB standard device descriptor */
usb_desc_dev audio_dev_desc =
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

/* USB device configuration descriptor */
usb_desc_config_set audio_config_set =
{
    .config =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_config),
             .bDescriptorType = USB_DESCTYPE_CONFIG
         },
        .wTotalLength         = AUDIO_CONFIG_DESC_SET_LEN,
        .bNumInterfaces       = 0x02U,
        .bConfigurationValue  = 0x01U,
        .iConfiguration       = 0x00U,
        .bmAttributes         = 0xC0U,
        .bMaxPower            = 0x32U
    },

    .std_itf =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_itf),
             .bDescriptorType = USB_DESCTYPE_ITF
         },
         .bInterfaceNumber    = 0x00U,
         .bAlternateSetting   = 0x00U,
         .bNumEndpoints       = 0x00U,
         .bInterfaceClass     = USB_CLASS_AUDIO,
         .bInterfaceSubClass  = AUDIO_SUBCLASS_CONTROL,
         .bInterfaceProtocol  = AUDIO_PROTOCOL_UNDEFINED,
         .iInterface          = 0x00U
    },

    .ac_itf =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_AC_itf),
             .bDescriptorType = AUDIO_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = 0x01U,
         .bcdADC              = 0x0100U,
         .wTotalLength        = 0x0027U,
         .bInCollection       = 0x01U,
         .baInterfaceNr       = 0x01U
    },

    .in_terminal =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_input_terminal),
             .bDescriptorType = AUDIO_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = 0x02U,
         .bTerminalID         = 0x01U,
         .wTerminalType       = 0x0101U,
         .bAssocTerminal      = 0x00U,
         .bNrChannels         = 0x01U,
         .wChannelConfig      = 0x0000U,
         .iChannelNames       = 0x00U,
         .iTerminal           = 0x00U
    },

    .feature_unit =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_mono_feature_unit),
             .bDescriptorType = AUDIO_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AUDIO_CONTROL_FEATURE_UNIT,
         .bUnitID             = AUDIO_OUT_STREAMING_CTRL,
         .bSourceID           = 0x01U,
         .bControlSize        = 0x01U,
         .bmaControls0        = AUDIO_CONTROL_MUTE,
         .bmaControls1        = 0x00U,
         .iFeature            = 0x00U
    },

    .out_terminal =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_output_terminal),
             .bDescriptorType = AUDIO_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AUDIO_CONTROL_OUTPUT_TERMINAL,
         .bTerminalID         = 0x03U,
         .wTerminalType       = 0x0301U,
         .bAssocTerminal      = 0x00U,
         .bSourceID           = 0x02U,
         .iTerminal           = 0x00U
    },

    .std_as_itf_zeroband =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_itf),
             .bDescriptorType = USB_DESCTYPE_ITF
         },
         .bInterfaceNumber    = 0x01U,
         .bAlternateSetting   = 0x00U,
         .bNumEndpoints       = 0x00U,
         .bInterfaceClass     = USB_CLASS_AUDIO,
         .bInterfaceSubClass  = AUDIO_SUBCLASS_AUDIOSTREAMING,
         .bInterfaceProtocol  = AUDIO_PROTOCOL_UNDEFINED,
         .iInterface          = 0x00U
    },

    .std_as_itf_opera =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_itf),
             .bDescriptorType = USB_DESCTYPE_ITF
         },
         .bInterfaceNumber    = 0x01U,
         .bAlternateSetting   = 0x01U,
         .bNumEndpoints       = 0x01U,
         .bInterfaceClass     = USB_CLASS_AUDIO,
         .bInterfaceSubClass  = AUDIO_SUBCLASS_AUDIOSTREAMING,
         .bInterfaceProtocol  = AUDIO_PROTOCOL_UNDEFINED,
         .iInterface          = 0x00U
    },

    .as_itf =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_AS_itf),
             .bDescriptorType = AUDIO_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AUDIO_STREAMING_GENERAL,
         .bTerminalLink       = 0x01U,
         .bDelay              = 0x01U,
         .wFormatTag          = 0x0001U,
    },

    .format_typeI =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_format_type),
             .bDescriptorType = AUDIO_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AUDIO_STREAMING_FORMAT_TYPE,
         .bFormatType         = AUDIO_FORMAT_TYPE_III,
         .bNrChannels         = 0x02U,
         .bSubFrameSize       = 0x02U,
         .bBitResolution      = 0x10U,
         .bSamFreqType        = 0x01U,
         .bSamFreq[0]         = (uint8_t)USBD_AUDIO_FREQ_16K,
         .bSamFreq[1]         = USBD_AUDIO_FREQ_16K >> 8,
         .bSamFreq[2]         = USBD_AUDIO_FREQ_16K >> 16
    },

    .std_endpoint =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_std_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
         .bEndpointAddress    = AUDIO_OUT_EP,
         .bmAttributes        = USB_ENDPOINT_TYPE_ISOCHRONOUS,
         .wMaxPacketSize      = PACKET_SIZE(USBD_AUDIO_FREQ_16K),
         .bInterval           = 0x01U,
         .bRefresh            = 0x00U,
         .bSynchAddress       = 0x00U
    },

    .as_endpoint =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_AS_ep),
             .bDescriptorType = AUDIO_DESCTYPE_ENDPOINT
         },
         .bDescriptorSubtype  = AUDIO_ENDPOINT_GENERAL,
         .bmAttributes        = 0x00U,
         .bLockDelayUnits     = 0x00U,
         .wLockDelay          = 0x0000U,
    }
};

/* USB language ID descriptor */
static usb_desc_LANGID usbd_language_id_desc =
{
    .header =
     {
         .bLength         = sizeof(usb_desc_LANGID),
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
    .unicode_string = {'G', 'D', '3', '2', '-', 'U', 'S', 'B', '_', 'A', 'u', 'd', 'i', 'o'}
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
static uint8_t* usbd_audio_strings[] =
{
    [STR_IDX_LANGID]  = (uint8_t *)&usbd_language_id_desc,
    [STR_IDX_MFC]     = (uint8_t *)&manufacturer_string,
    [STR_IDX_PRODUCT] = (uint8_t *)&product_string,
    [STR_IDX_SERIAL]  = (uint8_t *)&serial_string
};

usb_desc audio_desc = {
    .dev_desc    = (uint8_t *)&audio_dev_desc,
    .config_desc = (uint8_t *)&audio_config_set,
    .strings     = usbd_audio_strings
};


/*!
    \brief      initialize the audio device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_init (usb_dev *udev, uint8_t config_index)
{
    usb_desc_std_ep std_ep = audio_config_set.std_endpoint;

    static usbd_audio_handler audio_handler;

    memset((void *)&audio_handler, 0, sizeof(usbd_audio_handler));

    usb_desc_ep ep = {
        .header           = std_ep.header,
        .bEndpointAddress = std_ep.bEndpointAddress,
        .bmAttributes     = std_ep.bmAttributes,
        .wMaxPacketSize   = std_ep.wMaxPacketSize,
        .bInterval        = std_ep.bInterval
    };

    /* initialize RX endpoint */
    usbd_ep_init(udev, EP_BUF_DBL, AUDIO_BUF_ADDR, &ep);

    usbd_int_fops = &usb_inthandler;

    audio_handler.isoc_out_rdptr = audio_handler.isoc_out_buff;
    audio_handler.isoc_out_wrptr = audio_handler.isoc_out_buff;

    /* initialize the audio output hardware layer */
    if (USBD_OK != audio_out_fops.audio_init(USBD_AUDIO_FREQ_16K, DEFAULT_VOLUME, 0U)) {
        return USBD_FAIL;
    }

    udev->ep_transc[AUDIO_OUT_EP][TRANSC_OUT] = audio_class.data_out;

    /* prepare out endpoint to receive audio data */
    usbd_ep_recev (udev, AUDIO_OUT_EP, (uint8_t*)audio_handler.isoc_out_buff, (uint16_t)AUDIO_OUT_PACKET);

    udev->class_data[USBD_AUDIO_INTERFACE] = (void *)&audio_handler;

    return USBD_OK;
}

/*!
    \brief      de-initialize the audio device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_deinit (usb_dev *udev, uint8_t config_index)
{
    /* deinitialize audio endpoints */
    usbd_ep_deinit(udev, AUDIO_OUT_EP);

    /* deinitialize the audio output hardware layer */
    if (USBD_OK != audio_out_fops.audio_deinit(0U)) {
        return USBD_FAIL;
    }

    return USBD_OK;
}

/*!
    \brief      handle the audio class-specific requests
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: device class-specific request
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_req_handler (usb_dev *udev, usb_req *req)
{
    uint8_t status = REQ_NOTSUPP;

    usbd_audio_handler *audio = (usbd_audio_handler *)udev->class_data[USBD_AUDIO_INTERFACE];

    switch (req->bRequest) {
    case AUDIO_REQ_GET_CUR:
        usb_transc_config(&udev->transc_in[0], audio->audioctl, req->wLength, 0U);

        status = REQ_SUPP;
        break;

    case AUDIO_REQ_SET_CUR:
        if (req->wLength) {
            usb_transc_config(&udev->transc_out[0], audio->audioctl, req->wLength, 0U);

            udev->class_core->req_cmd = AUDIO_REQ_SET_CUR;

            audio->audioctl_len = req->wLength;
            audio->audioctl_unit = BYTE_HIGH(req->wIndex);

            status = REQ_SUPP;
        }
        break;

    default:
        break;
    }

    return status;
}

/*!
    \brief      handles the audio out data stage
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     USB device operation status
*/
static void audio_data_out (usb_dev *udev, uint8_t ep_num)
{
    usbd_audio_handler *audio = (usbd_audio_handler *)udev->class_data[USBD_AUDIO_INTERFACE];

    if (AUDIO_OUT_EP == ep_num) {
        /* increment the Buffer pointer or roll it back when all buffers are full */
        if (audio->isoc_out_wrptr >= (audio->isoc_out_buff + (AUDIO_OUT_PACKET * OUT_PACKET_NUM))) {
            /* all buffers are full: roll back */
            audio->isoc_out_wrptr = audio->isoc_out_buff;
        } else {
            /* increment the buffer pointer */
            audio->isoc_out_wrptr += AUDIO_OUT_PACKET;
        }

        /* prepare out endpoint to receive next audio packet */
        usbd_ep_recev (udev, AUDIO_OUT_EP, (uint8_t*)(audio->isoc_out_wrptr), (uint16_t)AUDIO_OUT_PACKET);

        /* trigger the start of streaming only when half buffer is full */
        if ((0U == audio->play_flag) && (audio->isoc_out_wrptr >= (audio->isoc_out_buff + ((AUDIO_OUT_PACKET * OUT_PACKET_NUM) / 2U)))) {
            /* enable start of streaming */
            audio->play_flag = 1U;
        }
    }
}

/*!
    \brief      handles audio control request data
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_ctlx_out (usb_dev *udev)
{
    usbd_audio_handler *audio = (usbd_audio_handler *)udev->class_data[USBD_AUDIO_INTERFACE];

    /* check if an audio_control request has been issued */
    if (AUDIO_REQ_SET_CUR == udev->class_core->req_cmd) {
        /* in this driver, to simplify code, only SET_CUR request is managed */

        /* check for which addressed unit the audio_control request has been issued */
        if (AUDIO_OUT_STREAMING_CTRL == audio->audioctl_unit) {
            /* in this driver, to simplify code, only one unit is manage */

            /* call the audio interface mute function */
            audio_out_fops.audio_mute_ctl(audio->audioctl[0]);

            /* reset the audioctl_cmd variable to prevent re-entering this function */
            udev->class_core->req_cmd = 0U;

            audio->audioctl_len = 0U;
        }
    }

    return USBD_OK;
}

/*!
    \brief      handles the SOF event (data buffer update and synchronization)
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t usbd_audio_sof (usb_dev *udev)
{
    usbd_audio_handler *audio = (usbd_audio_handler *)udev->class_data[USBD_AUDIO_INTERFACE];

    /* check if there are available data in stream buffer.
       in this function, a single variable (play_flag) is used to avoid software delays.
       the play operation must be executed as soon as possible after the SOF detection. */
    if (audio->play_flag) {
        /* start playing received packet */
        audio_out_fops.audio_cmd((uint8_t*)(audio->isoc_out_rdptr),  /* samples buffer pointer */
                                 AUDIO_OUT_PACKET,                   /* number of samples in Bytes */
                                 AUDIO_CMD_PLAY);                    /* command to be processed */

        /* increment the Buffer pointer or roll it back when all buffers all full */
        if (audio->isoc_out_rdptr >= (audio->isoc_out_buff + (AUDIO_OUT_PACKET * OUT_PACKET_NUM))) {
            /* roll back to the start of buffer */
            audio->isoc_out_rdptr = audio->isoc_out_buff;
        } else {
            /* increment to the next sub-buffer */
            audio->isoc_out_rdptr += AUDIO_OUT_PACKET;
        }

        /* if all available buffers have been consumed, stop playing */
        if (audio->isoc_out_rdptr == audio->isoc_out_wrptr) {
            /* pause the audio stream */
            audio_out_fops.audio_cmd((uint8_t*)(audio->isoc_out_buff),   /* samples buffer pointer */
                                     AUDIO_OUT_PACKET,                   /* number of samples in Bytes */
                                     AUDIO_CMD_PAUSE);                   /* command to be processed */

            /* stop entering play loop */
            audio->play_flag = 0U;

            /* reset buffer pointers */
            audio->isoc_out_rdptr = audio->isoc_out_buff;
            audio->isoc_out_wrptr = audio->isoc_out_buff;
        }
    }

    return USBD_OK;
}
