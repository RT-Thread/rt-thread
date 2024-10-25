/*!
    \file    audio_core.c
    \brief   USB audio device class core functions

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#define VOL_MIN                      0U    /* volume minimum value */
#define VOL_MAX                      100U  /* volume maximum value */
#define VOL_RES                      1U    /* volume resolution */
#define VOL_0dB                      70U   /* 0dB is in the middle of VOL_MIN and VOL_MAX */

/* local function prototypes ('static') */
static uint8_t audio_sof         (usb_dev *udev);
static uint8_t audio_init        (usb_dev *udev, uint8_t config_index);
static uint8_t audio_deinit      (usb_dev *udev, uint8_t config_index);
static uint8_t audio_req_handler (usb_dev *udev, usb_req *req);
static uint8_t audio_ctlx_out    (usb_dev *udev);
static void    audio_data_out    (usb_dev *udev, uint8_t ep_num);

static void    audio_set_itf     (usb_dev *udev, usb_req *req);

usb_class audio_class =
{
    .init        = audio_init,
    .deinit      = audio_deinit,
    .req_process = audio_req_handler,
    .ctlx_out    = audio_ctlx_out,
    .data_out    = audio_data_out
};

usbd_int_cb_struct usb_inthandler =
{
    audio_sof,
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
         .baInterfaceNr       = 0x01U
    },

    .in_terminal =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_input_terminal),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_CONTROL_INPUT_TERMINAL,
         .bTerminalID         = 0x01U,
         .wTerminalType       = 0x0101U,
         .bAssocTerminal      = 0x00U,
         .bNrChannels         = 0x02U,
         .wChannelConfig      = 0x0000U,
         .iChannelNames       = 0x00U,
         .iTerminal           = 0x00U
    },

    .feature_unit =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_mono_feature_unit),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_CONTROL_FEATURE_UNIT,
         .bUnitID             = AD_OUT_STREAMING_CTRL,
         .bSourceID           = 0x01U,
         .bControlSize        = 0x01U,
         .bmaControls0        = AD_CONTROL_MUTE | AD_CONTROL_VOLUME,
         .bmaControls1        = 0x00U,
         .iFeature            = 0x00U
    },

    .out_terminal =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_output_terminal),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_CONTROL_OUTPUT_TERMINAL,
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
         .bInterfaceSubClass  = AD_SUBCLASS_AUDIOSTREAMING,
         .bInterfaceProtocol  = AD_PROTOCOL_UNDEFINED,
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
         .bInterfaceSubClass  = AD_SUBCLASS_AUDIOSTREAMING,
         .bInterfaceProtocol  = AD_PROTOCOL_UNDEFINED,
         .iInterface          = 0x00U
    },

    .as_itf =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_AS_itf),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_STREAMING_GENERAL,
         .bTerminalLink       = 0x01U,
         .bDelay              = 0x01U,
         .wFormatTag          = 0x0001U,
    },

    .format_typeI =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_format_type),
             .bDescriptorType = AD_DESCTYPE_INTERFACE
         },
         .bDescriptorSubtype  = AD_STREAMING_FORMAT_TYPE,
         .bFormatType         = AD_FORMAT_TYPE_III,
         .bNrChannels         = SPEAKER_OUT_CHANNEL_NBR,
         .bSubFrameSize       = 0x02U,
         .bBitResolution      = SPEAKER_OUT_BIT_RESOLUTION,
         .bSamFreqType        = 0x01U,
         .bSamFreq[0]         = (uint8_t)USBD_SPEAKER_FREQ,
         .bSamFreq[1]         = USBD_SPEAKER_FREQ >> 8,
         .bSamFreq[2]         = USBD_SPEAKER_FREQ >> 16
    },

    .std_endpoint =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_std_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
         .bEndpointAddress    = AD_OUT_EP,
         .bmAttributes        = USB_ENDPOINT_TYPE_ISOCHRONOUS,
         .wMaxPacketSize      = SPEAKER_OUT_PACKET,
         .bInterval           = 0x01U,
         .bRefresh            = 0x00U,
         .bSynchAddress       = 0x00U
    },

    .as_endpoint =
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
    usbd_ep_init(udev, EP_BUF_DBL, AD_BUF_ADDR, &ep);

    usbd_int_fops = &usb_inthandler;

    audio_handler.isoc_out_rdptr = audio_handler.isoc_out_buff;
    audio_handler.isoc_out_wrptr = audio_handler.isoc_out_buff;

    /* initialize the audio output hardware layer */
    if (USBD_OK != audio_out_fops.audio_init(USBD_SPEAKER_FREQ, DEFAULT_VOLUME))
    {
        return USBD_FAIL;
    }

    udev->ep_transc[AD_OUT_EP][TRANSC_OUT] = audio_class.data_out;

    /* prepare out endpoint to receive audio data */
    usbd_ep_recev (udev, AD_OUT_EP, (uint8_t*)audio_handler.usb_rx_buffer, SPEAKER_OUT_MAX_PACKET);

    udev->class_data[USBD_AD_INTERFACE] = (void *)&audio_handler;

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
    usbd_ep_deinit(udev, AD_OUT_EP);

    /* deinitialize the audio output hardware layer */
    if (USBD_OK != audio_out_fops.audio_deinit(0U))
    {
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

    usbd_audio_handler *audio = (usbd_audio_handler *)udev->class_data[USBD_AD_INTERFACE];

    switch (req->bRequest)
    {
    case USB_SET_INTERFACE:
        audio_set_itf(udev, req);
        break;

    case AD_REQ_GET_CUR:
        usb_transc_config(&udev->transc_in[0], audio->audioctl, req->wLength, 0U);

        status = REQ_SUPP;
        break;

    case AD_REQ_SET_CUR:
        if (req->wLength)
        {
            usb_transc_config(&udev->transc_out[0], audio->audioctl, req->wLength, 0U);

            udev->class_core->req_cmd = AD_REQ_SET_CUR;

            audio->audioctl_len = req->wLength;
            audio->audioctl_unit = BYTE_HIGH(req->wIndex);

            status = REQ_SUPP;
        }
        break;

    case AD_REQ_GET_MIN:
        audio->audioctl[0] = VOL_MIN;
        usb_transc_config(&udev->transc_in[0], audio->audioctl, req->wLength, 0U);

        status = REQ_SUPP;
        break;

    case AD_REQ_GET_MAX:
        audio->audioctl[0] = VOL_MAX;
        usb_transc_config(&udev->transc_in[0], audio->audioctl, req->wLength, 0U);

        status = REQ_SUPP;
        break;

    case AD_REQ_GET_RES:
        audio->audioctl[0] = VOL_RES;
        usb_transc_config(&udev->transc_in[0], audio->audioctl, req->wLength, 0U);

        status = REQ_SUPP;
        break;

    default:
        break;
    }

    return status;
}

/*!
    \brief      handle the audio set interface requests
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: device class-specific request
    \param[out] none
    \retval     USB device operation status
*/
static void audio_set_itf(usb_dev *udev, usb_req *req)
{
    usbd_audio_handler *audio = (usbd_audio_handler *)udev->class_data[USBD_AD_INTERFACE];

    if (0xFF != req->wValue)
    {
        if (0 != req->wValue)
        {
            /* deinit audio handler */
            memset((void *)audio, 0, sizeof(usbd_audio_handler));

            audio->play_flag = 0;
            audio->isoc_out_rdptr = audio->isoc_out_buff;
            audio->isoc_out_wrptr = audio->isoc_out_buff;
        } else {
            /* stop audio output */
            audio_out_fops.audio_cmd(audio->isoc_out_rdptr, SPEAKER_OUT_PACKET / 2, AD_CMD_STOP);

            audio->play_flag = 0;
            audio->isoc_out_rdptr = audio->isoc_out_buff;
            audio->isoc_out_wrptr = audio->isoc_out_buff;
        }
    }
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
    usbd_audio_handler *audio = (usbd_audio_handler *)udev->class_data[USBD_AD_INTERFACE];

    if (AD_OUT_EP == ep_num)
    {
        uint16_t usb_rx_length, tail_len;

        /* get receive length */
        usb_rx_length = udev->transc_out[ep_num].xfer_count;

        if (audio->isoc_out_wrptr >= audio->isoc_out_rdptr)
        {
            audio->buf_free_size = TOTAL_OUT_BUF_SIZE + audio->isoc_out_rdptr - audio->isoc_out_wrptr;
        } else {
            audio->buf_free_size = audio->isoc_out_rdptr - audio->isoc_out_wrptr;
        }

        /* free buffer enough to save rx data */
        if (audio->buf_free_size > usb_rx_length)
        {
            if (audio->isoc_out_wrptr >= audio->isoc_out_rdptr)
            {
                tail_len = audio->isoc_out_buff + TOTAL_OUT_BUF_SIZE - audio->isoc_out_wrptr;

                if(tail_len >= usb_rx_length)
                {
                    memcpy(audio->isoc_out_wrptr, audio->usb_rx_buffer, usb_rx_length);

                    /* increment the buffer pointer */
                    audio->isoc_out_wrptr += usb_rx_length;

                    /* increment the Buffer pointer or roll it back when all buffers are full */
                    if (audio->isoc_out_wrptr >= (audio->isoc_out_buff + TOTAL_OUT_BUF_SIZE))
                    {
                        /* all buffers are full: roll back */
                        audio->isoc_out_wrptr = audio->isoc_out_buff;
                    }
                } else {
                    memcpy(audio->isoc_out_wrptr, audio->usb_rx_buffer, tail_len);

                    /* adjust write pointer */
                    audio->isoc_out_wrptr = audio->isoc_out_buff;

                    memcpy(audio->isoc_out_wrptr, &audio->usb_rx_buffer[tail_len], usb_rx_length - tail_len);

                    /* adjust write pointer */
                    audio->isoc_out_wrptr += usb_rx_length - tail_len;
                }
            } else {
                memcpy(audio->isoc_out_wrptr, audio->usb_rx_buffer, usb_rx_length);

                /* increment the buffer pointer */
                audio->isoc_out_wrptr += usb_rx_length;
            }
        }

        /* prepare out endpoint to receive next audio packet */
        usbd_ep_recev (udev, AD_OUT_EP, audio->usb_rx_buffer, SPEAKER_OUT_MAX_PACKET);

        if (audio->isoc_out_wrptr >= audio->isoc_out_rdptr)
        {
            audio->buf_free_size = TOTAL_OUT_BUF_SIZE + audio->isoc_out_rdptr - audio->isoc_out_wrptr;
        } else {
            audio->buf_free_size = audio->isoc_out_rdptr - audio->isoc_out_wrptr;
        }

        if ((0U == audio->play_flag) && (audio->buf_free_size < TOTAL_OUT_BUF_SIZE / 2))
        {
            /* enable start of streaming */
            audio->play_flag = 1U;

            /* initialize the audio output hardware layer */
            if (USBD_OK != audio_out_fops.audio_cmd(audio->isoc_out_rdptr, SPEAKER_OUT_MAX_PACKET / 2, AD_CMD_PLAY))
            {
                return;
            }

            audio->dam_tx_len = SPEAKER_OUT_MAX_PACKET;
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
    usbd_audio_handler *audio = (usbd_audio_handler *)udev->class_data[USBD_AD_INTERFACE];

    /* check if an audio_control request has been issued */
    if (AD_REQ_SET_CUR == udev->class_core->req_cmd)
    {
        /* in this driver, to simplify code, only SET_CUR request is managed */

        /* check for which addressed unit the audio_control request has been issued */
        if (AD_OUT_STREAMING_CTRL == audio->audioctl_unit)
        {
            /* in this driver, to simplify code, only one unit is manage */

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
static uint8_t audio_sof (usb_dev *udev)
{
    return USBD_OK;
}
