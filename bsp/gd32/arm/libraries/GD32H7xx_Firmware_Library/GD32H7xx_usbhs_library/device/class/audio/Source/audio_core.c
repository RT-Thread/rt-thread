/*!
    \file    audio_core.c
    \brief   USB audio device class core functions

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

#include "audio_out_itf.h"
#include "audio_core.h"
#include <string.h>
#include <math.h>

#define USBD_VID                     0x28E9U
#define USBD_PID                     0x9574U

#define VOL_MIN                      0U    /* volume Minimum Value */
#define VOL_MAX                      100U  /* volume Maximum Value */
#define VOL_RES                      1U    /* volume Resolution */
#define VOL_0dB                      70U   /* 0dB is in the middle of VOL_MIN and VOL_MAX */

#ifdef USE_USB_AD_MICPHONE
extern volatile uint32_t count_data;
extern const char wavetestdata[];
#define LENGTH_DATA    (1747 * 32)
#endif /* USE_USB_AD_MICPHONE */

__ALIGN_BEGIN usbd_audio_handler audio_handler __ALIGN_END;

/* local function prototypes ('static') */
static uint8_t audio_init (usb_dev *udev, uint8_t config_index);
static uint8_t audio_deinit (usb_dev *udev, uint8_t config_index);
static uint8_t audio_req_handler (usb_dev *udev, usb_req *req);
static uint8_t audio_set_intf (usb_dev *udev, usb_req *req);
static uint8_t audio_ctlx_out (usb_dev *udev);
static uint8_t audio_data_in (usb_dev *udev, uint8_t ep_num);
static uint8_t audio_data_out (usb_dev *udev, uint8_t ep_num);
static uint8_t audio_sof (usb_dev *udev);
static uint8_t audio_iso_in_incomplete (usb_dev *udev);
static uint8_t audio_iso_out_incomplete (usb_dev *udev);
static uint32_t usbd_audio_spk_get_feedback(usb_dev *udev);
static void get_feedback_fs_rate(uint32_t rate, uint8_t *buf);

usb_class_core usbd_audio_cb = {
    .init      = audio_init,
    .deinit    = audio_deinit,
    .req_proc  = audio_req_handler,
    .set_intf  = audio_set_intf,
    .ctlx_out  = audio_ctlx_out,
    .data_in   = audio_data_in,
    .data_out  = audio_data_out,
    .SOF       = audio_sof,
    .incomplete_isoc_in = audio_iso_in_incomplete,
    .incomplete_isoc_out = audio_iso_out_incomplete
};

/* note:it should use the c99 standard when compiling the below codes */
/* USB standard device descriptor */
__ALIGN_BEGIN const usb_desc_dev audio_dev_desc __ALIGN_END =
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
    .bMaxPacketSize0       = USB_FS_EP0_MAX_LEN,
    .idVendor              = USBD_VID,
    .idProduct             = USBD_PID,
    .bcdDevice             = 0x0100U,
    .iManufacturer         = STR_IDX_MFC,
    .iProduct              = STR_IDX_PRODUCT,
    .iSerialNumber         = STR_IDX_SERIAL,
    .bNumberConfigurations = USBD_CFG_MAX_NUM
};

/* USB device configuration descriptor */
__ALIGN_BEGIN const usb_desc_config_set audio_config_set __ALIGN_END =
{
    .config =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_config),
             .bDescriptorType = USB_DESCTYPE_CONFIG
         },
        .wTotalLength         = AD_CONFIG_DESC_SET_LEN,
        .bNumInterfaces       = 0x01U + CONFIG_DESC_AS_ITF_COUNT,
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
         .bInterfaceSubClass  = AD_SUBCLASS_CONTROL,
         .bInterfaceProtocol  = AD_PROTOCOL_UNDEFINED,
         .iInterface          = 0x00U
    },

    .ac_itf =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_AC_itf),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = 0x01U,
         .bcdADC              = 0x0100U,
         .wTotalLength        = AC_ITF_TOTAL_LEN,
         .bInCollection       = CONFIG_DESC_AS_ITF_COUNT,
#ifdef USE_USB_AD_MICPHONE
         .baInterfaceNr0       = 0x01U,
#endif /* USE_USB_AD_MICPHONE */

#ifdef USE_USB_AD_SPEAKER
         .baInterfaceNr1       = 0x02U
#endif /* USE_USB_AD_SPEAKER */
    },

#ifdef USE_USB_AD_MICPHONE
    .mic_in_terminal =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_input_terminal),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = 0x02U,
         .bTerminalID         = 0x01U,
         .wTerminalType       = 0x0201U,
         .bAssocTerminal      = 0x00U,
         .bNrChannels         = 0x02U,
         .wChannelConfig      = 0x0003U,
         .iChannelNames       = 0x00U,
         .iTerminal           = 0x00U
    },

    .mic_feature_unit =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_mono_feature_unit),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_CONTROL_FEATURE_UNIT,
         .bUnitID             = AD_IN_STREAMING_CTRL,
         .bSourceID           = 0x01U,
         .bControlSize        = 0x01U,
         .bmaControls0        = AD_CONTROL_MUTE | AD_CONTROL_VOLUME,
         .bmaControls1        = 0x00U,
         .iFeature            = 0x00U
    },

    .mic_out_terminal =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_output_terminal),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_CONTROL_OUTPUT_TERMINAL,
         .bTerminalID         = 0x03U,
         .wTerminalType       = 0x0101U,
         .bAssocTerminal      = 0x00U,
         .bSourceID           = 0x02U,
         .iTerminal           = 0x00U
    },
#endif /* USE_USB_AD_MICPHONE */

#ifdef USE_USB_AD_SPEAKER
    .speak_in_terminal =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_input_terminal),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_CONTROL_INPUT_TERMINAL,
         .bTerminalID         = 0x04U,
         .wTerminalType       = 0x0101U,
         .bAssocTerminal      = 0x00U,
         .bNrChannels         = 0x02U,
         .wChannelConfig      = 0x0003U,
         .iChannelNames       = 0x00U,
         .iTerminal           = 0x00U
    },

    .speak_feature_unit =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_mono_feature_unit),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_CONTROL_FEATURE_UNIT,
         .bUnitID             = AD_OUT_STREAMING_CTRL,
         .bSourceID           = 0x04U,
         .bControlSize        = 0x01U,
         .bmaControls0        = AD_CONTROL_MUTE | AD_CONTROL_VOLUME,
         .bmaControls1        = 0x00U,
         .iFeature            = 0x00U
    },

    .speak_out_terminal =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_output_terminal),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_CONTROL_OUTPUT_TERMINAL,
         .bTerminalID         = 0x06U,
         .wTerminalType       = 0x0301U,
         .bAssocTerminal      = 0x00U,
         .bSourceID           = 0x05U,
         .iTerminal           = 0x00U
    },
#endif /* USE_USB_AD_SPEAKER */

#ifdef USE_USB_AD_MICPHONE
    .mic_std_as_itf_zeroband =
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
         .bInterfaceSubClass  = AD_SUBCLASS_AUDIOSTREAMING,
         .bInterfaceProtocol  = AD_PROTOCOL_UNDEFINED,
         .iInterface          = 0x00U
    },

    .mic_std_as_itf_opera =
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
         .bInterfaceSubClass  = AD_SUBCLASS_AUDIOSTREAMING,
         .bInterfaceProtocol  = AD_PROTOCOL_UNDEFINED,
         .iInterface          = 0x00U
    },

    .mic_as_itf =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_AS_itf),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_STREAMING_GENERAL,
         .bTerminalLink       = 0x03U,
         .bDelay              = 0x01U,
         .wFormatTag          = 0x0001U,
    },

    .mic_format_typeI =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_format_type),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_STREAMING_FORMAT_TYPE,
         .bFormatType         = AD_FORMAT_TYPE_I,
         .bNrChannels         = MIC_IN_CHANNEL_NBR,
         .bSubFrameSize       = 0x02U,
         .bBitResolution      = MIC_IN_BIT_RESOLUTION,
         .bSamFreqType        = 0x01U,
         .bSamFreq[0]         = (uint8_t)USBD_MIC_FREQ,
         .bSamFreq[1]         = USBD_MIC_FREQ >> 8U,
         .bSamFreq[2]         = USBD_MIC_FREQ >> 16U
    },

    .mic_std_endpoint =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_std_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
         .bEndpointAddress    = AD_IN_EP,
         .bmAttributes        = USB_ENDPOINT_TYPE_ISOCHRONOUS,
         .wMaxPacketSize      = MIC_IN_PACKET,
         .bInterval           = 0x01U,
         .bRefresh            = 0x00U,
         .bSynchAddress       = 0x00U
    },

    .mic_as_endpoint =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_AS_ep),
             .bDescriptorType = AD_DESCTYPE_ENDPOINT
         },
         .bDescriptorSubtype  = AD_ENDPOINT_GENERAL,
         .bmAttributes        = 0x00U,
         .bLockDelayUnits     = 0x00U,
         .wLockDelay          = 0x0000U,
    },
#endif /* USE_USB_AD_MICPHONE */

#ifdef USE_USB_AD_SPEAKER
    .speak_std_as_itf_zeroband =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_itf),
             .bDescriptorType = USB_DESCTYPE_ITF
         },
         .bInterfaceNumber    = 0x02U,
         .bAlternateSetting   = 0x00U,
         .bNumEndpoints       = 0x00U,
         .bInterfaceClass     = USB_CLASS_AUDIO,
         .bInterfaceSubClass  = AD_SUBCLASS_AUDIOSTREAMING,
         .bInterfaceProtocol  = AD_PROTOCOL_UNDEFINED,
         .iInterface          = 0x00U
    },

    .speak_std_as_itf_opera =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_itf),
             .bDescriptorType = USB_DESCTYPE_ITF
         },
         .bInterfaceNumber    = 0x02U,
         .bAlternateSetting   = 0x01U,
         .bNumEndpoints       = 0x02U,
         .bInterfaceClass     = USB_CLASS_AUDIO,
         .bInterfaceSubClass  = AD_SUBCLASS_AUDIOSTREAMING,
         .bInterfaceProtocol  = AD_PROTOCOL_UNDEFINED,
         .iInterface          = 0x00U
    },

    .speak_as_itf =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_AS_itf),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_STREAMING_GENERAL,
         .bTerminalLink       = 0x04U,
         .bDelay              = 0x01U,
         .wFormatTag          = 0x0001U,
    },

    .speak_format_typeI =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_format_type),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_STREAMING_FORMAT_TYPE,
         .bFormatType         = AD_FORMAT_TYPE_I,
         .bNrChannels         = SPEAKER_OUT_CHANNEL_NBR,
         .bSubFrameSize       = 0x02U,
         .bBitResolution      = SPEAKER_OUT_BIT_RESOLUTION,
         .bSamFreqType        = 0x01U,
         .bSamFreq[0]         = (uint8_t)USBD_SPEAKER_FREQ,
         .bSamFreq[1]         = USBD_SPEAKER_FREQ >> 8U,
         .bSamFreq[2]         = USBD_SPEAKER_FREQ >> 16U
    },

    .speak_std_endpoint =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_std_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
         .bEndpointAddress    = AD_OUT_EP,
         .bmAttributes        = USB_EP_ATTR_ISO | USB_EP_ATTR_ASYNC,
         .wMaxPacketSize      = SPEAKER_OUT_PACKET,
         .bInterval           = 0x01U,
         .bRefresh            = 0x00U,
         .bSynchAddress       = AD_FEEDBACK_IN_EP,
    },

    .speak_as_endpoint =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_AS_ep),
             .bDescriptorType = AD_DESCTYPE_ENDPOINT
         },
         .bDescriptorSubtype  = AD_ENDPOINT_GENERAL,
         .bmAttributes        = 0x00U,
         .bLockDelayUnits     = 0x00U,
         .wLockDelay          = 0x0000U,
    },

    .speak_feedback_endpoint =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_FeedBack_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
         .bEndpointAddress    = AD_FEEDBACK_IN_EP,
         .bmAttributes        = USB_EP_ATTR_ISO | USB_EP_ATTR_ASYNC | USB_EP_ATTR_FEEDBACK,
         .wMaxPacketSize      = FEEDBACK_IN_PACKET,
         .bInterval           = 0x01U,
         .Refresh             = FEEDBACK_IN_INTERVAL, /* refresh every 32(2^5) ms */
         .bSynchAddress       = 0x00U,
    },
#endif /* USE_USB_AD_SPEAKER */
};

/* USB language ID descriptor */
static __ALIGN_BEGIN const usb_desc_LANGID usbd_language_id_desc __ALIGN_END =
{
    .header =
     {
         .bLength         = sizeof(usb_desc_LANGID),
         .bDescriptorType = USB_DESCTYPE_STR
     },

    .wLANGID = ENG_LANGID
};

/* USB manufacture string */
static __ALIGN_BEGIN const usb_desc_str manufacturer_string __ALIGN_END =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(10),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
    .unicode_string = {'G', 'i', 'g', 'a', 'D', 'e', 'v', 'i', 'c', 'e'}
};

/* USB product string */
static __ALIGN_BEGIN const usb_desc_str product_string __ALIGN_END =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(14),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
    .unicode_string = {'G', 'D', '3', '2', '-', 'U', 'S', 'B', '_', 'A', 'u', 'd', 'i', 'o'}
};

/* USBD serial string */
static __ALIGN_BEGIN usb_desc_str serial_string __ALIGN_END =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(12),
         .bDescriptorType = USB_DESCTYPE_STR,
     }
};

/* USB string descriptor */
void *const usbd_audio_strings[] =
{
    [STR_IDX_LANGID]  = (uint8_t *)&usbd_language_id_desc,
    [STR_IDX_MFC]     = (uint8_t *)&manufacturer_string,
    [STR_IDX_PRODUCT] = (uint8_t *)&product_string,
    [STR_IDX_SERIAL]  = (uint8_t *)&serial_string
};

/* USB descriptor configure */
usb_desc audio_desc = {
    .dev_desc    = (uint8_t *)&audio_dev_desc,
    .config_desc = (uint8_t *)&audio_config_set,
    .strings     = usbd_audio_strings
};

/*!
    \brief      initialize the AUDIO device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_init (usb_dev *udev, uint8_t config_index)
{
    memset((void *)&audio_handler, 0, sizeof(usbd_audio_handler));

#ifdef USE_USB_AD_MICPHONE
{
    usb_desc_std_ep std_ep = audio_config_set.mic_std_endpoint;

    usb_desc_ep ep = {
        .header           = std_ep.header,
        .bEndpointAddress = std_ep.bEndpointAddress,
        .bmAttributes     = std_ep.bmAttributes,
        .wMaxPacketSize   = std_ep.wMaxPacketSize,
        .bInterval        = std_ep.bInterval
    };

    /* initialize TX endpoint */
    usbd_ep_setup (udev, &ep);
}
#endif /* USE_USB_AD_MICPHONE */

#ifdef USE_USB_AD_SPEAKER
{
    audio_handler.isoc_out_rdptr = audio_handler.isoc_out_buff;
    audio_handler.isoc_out_wrptr = audio_handler.isoc_out_buff;

    usb_desc_std_ep std_ep = audio_config_set.speak_std_endpoint;

    usb_desc_ep ep1 = {
        .header           = std_ep.header,
        .bEndpointAddress = std_ep.bEndpointAddress,
        .bmAttributes     = std_ep.bmAttributes,
        .wMaxPacketSize   = SPEAKER_OUT_MAX_PACKET,
        .bInterval        = std_ep.bInterval
    };

    /* initialize RX endpoint */
    usbd_ep_setup (udev, &ep1);

    /* prepare out endpoint to receive next audio packet */
    usbd_ep_recev (udev, AD_OUT_EP, audio_handler.usb_rx_buffer, SPEAKER_OUT_MAX_PACKET);

    /* initialize the audio output hardware layer */
    if (USBD_OK != audio_out_fops.audio_init(USBD_SPEAKER_FREQ, DEFAULT_VOLUME))
    {
        return USBD_FAIL;
    }

    usb_desc_FeedBack_ep feedback_ep = audio_config_set.speak_feedback_endpoint;

    usb_desc_ep ep2 = {
        .header           = feedback_ep.header,
        .bEndpointAddress = feedback_ep.bEndpointAddress,
        .bmAttributes     = feedback_ep.bmAttributes,
        .wMaxPacketSize   = feedback_ep.wMaxPacketSize,
        .bInterval        = feedback_ep.bInterval
    };

    /* initialize Tx endpoint */
    usbd_ep_setup (udev, &ep2);
}
#endif /* USE_USB_AD_SPEAKER */

    return USBD_OK;
}

/*!
    \brief      de-initialize the AUDIO device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_deinit (usb_dev *udev, uint8_t config_index)
{
#ifdef USE_USB_AD_MICPHONE
    /* deinitialize AUDIO endpoints */
    usbd_ep_clear(udev, AD_IN_EP);
#endif /* USE_USB_AD_MICPHONE */

#ifdef USE_USB_AD_SPEAKER
    /* deinitialize AUDIO endpoints */
    usbd_ep_clear(udev, AD_OUT_EP);

    /* deinitialize the audio output hardware layer */
    if (USBD_OK != audio_out_fops.audio_deinit())
    {
        return USBD_FAIL;
    }

    /* deinitialize AUDIO endpoints */
    usbd_ep_clear(udev, AD_FEEDBACK_IN_EP);
#endif /* USE_USB_AD_SPEAKER */

    return USBD_OK;
}

/*!
    \brief      handle the AUDIO class-specific requests
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: device class-specific request
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_req_handler (usb_dev *udev, usb_req *req)
{
    uint8_t status = REQ_NOTSUPP;

    usb_transc *transc_in = &udev->dev.transc_in[0];
    usb_transc *transc_out = &udev->dev.transc_out[0];

    switch (req->bRequest)
    {
    case AD_REQ_GET_CUR:
        transc_in->xfer_buf = audio_handler.audioctl;
        transc_in->remain_len = req->wLength;

        status = REQ_SUPP;
        break;

    case AD_REQ_SET_CUR:
        if (req->wLength)
        {
            transc_out->xfer_buf = audio_handler.audioctl;
            transc_out->remain_len = req->wLength;

            udev->dev.class_core->command = AD_REQ_SET_CUR;

            audio_handler.audioctl_len = req->wLength;
            audio_handler.audioctl_unit = BYTE_HIGH(req->wIndex);

            status = REQ_SUPP;
        }
        break;

    case AD_REQ_GET_MIN:
        *((uint16_t *)audio_handler.audioctl) = VOL_MIN;
        transc_in->xfer_buf = audio_handler.audioctl;
        transc_in->remain_len = req->wLength;
        status = REQ_SUPP;
        break;

    case AD_REQ_GET_MAX:
        *((uint16_t *)audio_handler.audioctl) = VOL_MAX;
        transc_in->xfer_buf = audio_handler.audioctl;
        transc_in->remain_len = req->wLength;
        status = REQ_SUPP;
        break;

    case AD_REQ_GET_RES:
        *((uint16_t *)audio_handler.audioctl) = VOL_RES;
        transc_in->xfer_buf = audio_handler.audioctl;
        transc_in->remain_len = req->wLength;
        status = REQ_SUPP;
        break;

    default:
        break;
    }

    return status;
}

/*!
    \brief      handle the AUDIO set interface requests
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: device class-specific request
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_set_intf(usb_dev *udev, usb_req *req)
{
    udev->dev.class_core->alter_set = req->wValue;

    if(0xFF != req->wValue)
    {
        if (req->wValue != 0)
        {
            /* deinit audio handler */
            memset((void *)&audio_handler, 0, sizeof(usbd_audio_handler));

            audio_handler.play_flag = 0;
            audio_handler.isoc_out_rdptr = audio_handler.isoc_out_buff;
            audio_handler.isoc_out_wrptr = audio_handler.isoc_out_buff;

            /* feedback calculate sample freq */
            audio_handler.actual_freq = I2S_ACTUAL_SAM_FREQ(USBD_SPEAKER_FREQ);
            get_feedback_fs_rate(audio_handler.actual_freq, audio_handler.feedback_freq);

            /* send feedback data of estimated frequence*/
            usbd_ep_send(udev, AD_FEEDBACK_IN_EP, audio_handler.feedback_freq, FEEDBACK_IN_PACKET);
        } else {
            /* stop audio output */
            audio_out_fops.audio_cmd(audio_handler.isoc_out_rdptr, SPEAKER_OUT_PACKET/2, AD_CMD_STOP);

            audio_handler.play_flag = 0;
            audio_handler.isoc_out_rdptr = audio_handler.isoc_out_buff;
            audio_handler.isoc_out_wrptr = audio_handler.isoc_out_buff;

            usbd_fifo_flush (udev, AD_IN_EP);
            usbd_fifo_flush (udev, AD_FEEDBACK_IN_EP);
            usbd_fifo_flush (udev, AD_OUT_EP);
        }
    }

    return 0;
}

/*!
    \brief      handles the control transfer OUT callback
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_ctlx_out (usb_dev *udev)
{
#ifdef USE_USB_AD_SPEAKER
    /* handles audio control requests data */
    /* check if an audio_control request has been issued */
    if (AD_REQ_SET_CUR == udev->dev.class_core->command)
    {
        /* in this driver, to simplify code, only SET_CUR request is managed */

        /* check for which addressed unit the audio_control request has been issued */
        if (AD_OUT_STREAMING_CTRL == audio_handler.audioctl_unit)
        {
            /* in this driver, to simplify code, only one unit is manage */

            /* reset the audioctl_cmd variable to prevent re-entering this function */
            udev->dev.class_core->command = 0U;

            audio_handler.audioctl_len = 0U;
        }
    }
#endif /* USE_USB_AD_SPEAKER */

    return USBD_OK;
}

/*!
    \brief      handles the audio IN data stage
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_data_in (usb_dev *udev, uint8_t ep_num)
{
#ifdef USE_USB_AD_MICPHONE
    if(ep_num == EP_ID(AD_IN_EP))
    {
        if(count_data < LENGTH_DATA)
        {
            /* Prepare next buffer to be sent: dummy data */
            usbd_ep_send(udev, AD_IN_EP,(uint8_t*)&wavetestdata[count_data],MIC_IN_PACKET);
            count_data += MIC_IN_PACKET;
        } else {
            usbd_ep_send(udev, AD_IN_EP,(uint8_t*)wavetestdata,MIC_IN_PACKET);
            count_data = MIC_IN_PACKET;
        }
    }
#endif /* USE_USB_AD_MICPHONE */

#ifdef USE_USB_AD_SPEAKER
    if(ep_num == EP_ID(AD_FEEDBACK_IN_EP))
    {
        /* calculate feedback actual freq */
        audio_handler.actual_freq = usbd_audio_spk_get_feedback(udev);
        get_feedback_fs_rate(audio_handler.actual_freq, audio_handler.feedback_freq);

        usbd_ep_send(udev, AD_FEEDBACK_IN_EP, audio_handler.feedback_freq, FEEDBACK_IN_PACKET);
    }
#endif /* USE_USB_AD_SPEAKER */

    return USBD_OK;
}

/*!
    \brief      handles the audio OUT data stage
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_data_out (usb_dev *udev, uint8_t ep_num)
{
    uint16_t usb_rx_length, tail_len;

    /* get receive length */
    usb_rx_length = ((usb_core_driver *)udev)->dev.transc_out[ep_num].xfer_count;

    if(audio_handler.isoc_out_wrptr >= audio_handler.isoc_out_rdptr)
    {
        audio_handler.buf_free_size = TOTAL_OUT_BUF_SIZE + audio_handler.isoc_out_rdptr - audio_handler.isoc_out_wrptr;
    }else{
        audio_handler.buf_free_size = audio_handler.isoc_out_rdptr - audio_handler.isoc_out_wrptr;
    }

    /* free buffer enough to save rx data */
    if(audio_handler.buf_free_size > usb_rx_length)
    {
        if(audio_handler.isoc_out_wrptr >= audio_handler.isoc_out_rdptr)
        {
            tail_len = audio_handler.isoc_out_buff + TOTAL_OUT_BUF_SIZE - audio_handler.isoc_out_wrptr;

            if(tail_len >= usb_rx_length)
            {
                memcpy(audio_handler.isoc_out_wrptr, audio_handler.usb_rx_buffer, usb_rx_length);

                /* increment the buffer pointer */
                audio_handler.isoc_out_wrptr += usb_rx_length;

                /* increment the Buffer pointer or roll it back when all buffers are full */
                if(audio_handler.isoc_out_wrptr >= (audio_handler.isoc_out_buff + TOTAL_OUT_BUF_SIZE))
                {
                    /* all buffers are full: roll back */
                    audio_handler.isoc_out_wrptr = audio_handler.isoc_out_buff;
                }
            }else{
                memcpy(audio_handler.isoc_out_wrptr, audio_handler.usb_rx_buffer, tail_len);
                /* adjust write pointer */
                audio_handler.isoc_out_wrptr = audio_handler.isoc_out_buff;

                memcpy(audio_handler.isoc_out_wrptr, &audio_handler.usb_rx_buffer[tail_len], usb_rx_length - tail_len);
                /* adjust write pointer */
                audio_handler.isoc_out_wrptr += usb_rx_length - tail_len;
            }
        }else{
            memcpy(audio_handler.isoc_out_wrptr, audio_handler.usb_rx_buffer, usb_rx_length);

            /* increment the buffer pointer */
            audio_handler.isoc_out_wrptr += usb_rx_length;
        }
    }

    /* Toggle the frame index */
    udev->dev.transc_out[ep_num].frame_num = (udev->dev.transc_out[ep_num].frame_num)? 0U:1U;

    /* prepare out endpoint to receive next audio packet */
    usbd_ep_recev (udev, AD_OUT_EP, audio_handler.usb_rx_buffer, SPEAKER_OUT_MAX_PACKET);

    if(audio_handler.isoc_out_wrptr >= audio_handler.isoc_out_rdptr)
    {
        audio_handler.buf_free_size = TOTAL_OUT_BUF_SIZE + audio_handler.isoc_out_rdptr - audio_handler.isoc_out_wrptr;
    }else{
        audio_handler.buf_free_size = audio_handler.isoc_out_rdptr - audio_handler.isoc_out_wrptr;
    }

    if ((0U == audio_handler.play_flag) && (audio_handler.buf_free_size < TOTAL_OUT_BUF_SIZE/2))
    {
        /* enable start of streaming */
        audio_handler.play_flag = 1U;

        /* initialize the audio output hardware layer */
        if (USBD_OK != audio_out_fops.audio_cmd(audio_handler.isoc_out_rdptr, SPEAKER_OUT_MAX_PACKET/2, AD_CMD_PLAY))
        {
            return USBD_FAIL;
        }

        audio_handler.dam_tx_len = SPEAKER_OUT_MAX_PACKET;
    }

    return USBD_OK;
}

/*!
    \brief      handles the SOF event (data buffer update and synchronization)
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_sof (usb_dev *udev)
{
    return USBD_OK;
}

/*!
    \brief      handles the audio ISO IN Incomplete event
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_iso_in_incomplete (usb_dev *udev)
{
    (void)usb_txfifo_flush (&udev->regs, EP_ID(AD_FEEDBACK_IN_EP));

    audio_handler.actual_freq = usbd_audio_spk_get_feedback(udev);
    get_feedback_fs_rate(audio_handler.actual_freq, audio_handler.feedback_freq);

    /* send feedback data of estimated frequence*/
    usbd_ep_send(udev, AD_FEEDBACK_IN_EP, audio_handler.feedback_freq, FEEDBACK_IN_PACKET);

    return USBD_OK;
}

/*!
    \brief      handles the audio ISO OUT Incomplete event
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t audio_iso_out_incomplete (usb_dev *udev)
{
    return USBD_OK;
}

/*!
    \brief      calculate feedback sample frequency
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     feedback frequency value
*/
static uint32_t usbd_audio_spk_get_feedback(usb_dev *udev)
{
    static uint32_t fb_freq;

    /* calculate buffer free size */
    if(audio_handler.isoc_out_wrptr >= audio_handler.isoc_out_rdptr)
    {
        audio_handler.buf_free_size = TOTAL_OUT_BUF_SIZE + audio_handler.isoc_out_rdptr - audio_handler.isoc_out_wrptr;
    }else{
        audio_handler.buf_free_size = audio_handler.isoc_out_rdptr - audio_handler.isoc_out_wrptr;
    }

    /* calculate feedback frequency */
    if(audio_handler.buf_free_size <= (TOTAL_OUT_BUF_SIZE/4))
    {
        fb_freq = I2S_ACTUAL_SAM_FREQ(USBD_SPEAKER_FREQ) - FEEDBACK_FREQ_OFFSET;
    }else if(audio_handler.buf_free_size >= (TOTAL_OUT_BUF_SIZE*3/4))
    {
        fb_freq = I2S_ACTUAL_SAM_FREQ(USBD_SPEAKER_FREQ) + FEEDBACK_FREQ_OFFSET;
    }else{
        fb_freq = I2S_ACTUAL_SAM_FREQ(USBD_SPEAKER_FREQ);
    }

    return fb_freq;
}

/*!
    \brief      get feedback value from rate in USB full speed
    \param[in]  rate: sample frequence
    \param[in]  buf: pointer to result buffer
    \param[out] none
    \retval     USB device operation status
*/
static void get_feedback_fs_rate(uint32_t rate, uint8_t *buf)
{
    rate = ((rate / 1000) << 14) | ((rate % 1000) << 4);

    buf[0] = rate;
    buf[1] = rate >> 8;
    buf[2] = rate >> 16;
}
