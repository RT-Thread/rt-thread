/*!
    \file  usbh_enum.c
    \brief USB host mode enumberation driver

    \version 2019-6-5, V1.0.0, firmware for GD32 USBFS&USBHS
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

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

#include "usbh_transc.h"
#include "usbh_enum.h"

static void usbh_devdesc_parse (usb_desc_dev *cfg_desc, uint8_t *buf, uint16_t len);
static void usbh_cfgset_parse  (usb_dev_prop *udev, uint8_t *buf);
static void usbh_cfgdesc_parse (usb_desc_config *cfg_desc, uint8_t *buf);
static void usbh_itfdesc_parse (usb_desc_itf *itf_desc, uint8_t *buf);
static void usbh_epdesc_parse  (usb_desc_ep *ep_desc, uint8_t *buf);
static void usbh_strdesc_parse (uint8_t *psrc, uint8_t *pdest, uint16_t len);


/*!
    \brief      configure USB control status parameters
    \param[in]  puhost: pointer to usb host
    \param[in]  buf: control transfer data buffer pointer
    \param[in]  len: length of the data buffer
    \param[out] none
    \retval     none
*/
void usbh_ctlstate_config (usbh_host *puhost, uint8_t *buf, uint16_t len)
{
    /* prepare the transactions */
    puhost->control.buf = buf;
    puhost->control.ctl_len = len;

    puhost->control.ctl_state = CTL_SETUP;
}

/*!
    \brief      get device descriptor from the USB device
    \param[in]  pudev: pointer to usb core instance
    \param[in]  puhost: pointer to usb host
    \param[in]  len: length of the descriptor
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_devdesc_get (usb_core_driver *pudev, usbh_host *puhost, uint8_t len)
{
    usbh_status status = USBH_BUSY;

    usbh_control *usb_ctl = &puhost->control;

    if (CTL_IDLE == usb_ctl->ctl_state) {
        usb_ctl->setup.req = (usb_req) {
            .bmRequestType = USB_TRX_IN | USB_RECPTYPE_DEV | USB_REQTYPE_STRD,
            .bRequest      = USB_GET_DESCRIPTOR,
            .wValue        = USBH_DESC(USB_DESCTYPE_DEV),
            .wIndex        = 0U,
            .wLength       = len
        };

        usbh_ctlstate_config (puhost, pudev->host.rx_buf, len);
    }

    status = usbh_ctl_handler (pudev, puhost);

    if (USBH_OK == status) {
        /* commands successfully sent and response received */
        usbh_devdesc_parse (&puhost->dev_prop.dev_desc, pudev->host.rx_buf, len);
    }

    return status;
}

/*!
    \brief      get configuration descriptor from the USB device
    \param[in]  pudev: pointer to usb core instance
    \param[in]  puhost: pointer to usb host
    \param[in]  len: length of the descriptor
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_cfgdesc_get (usb_core_driver *pudev, usbh_host *puhost, uint16_t len)
{
    usbh_status status = USBH_BUSY;

    usbh_control *usb_ctl = &puhost->control;

    if (CTL_IDLE == usb_ctl->ctl_state) {
        usb_ctl->setup.req = (usb_req) {
            .bmRequestType = USB_TRX_IN | USB_RECPTYPE_DEV | USB_REQTYPE_STRD,
            .bRequest      = USB_GET_DESCRIPTOR,
            .wValue        = USBH_DESC(USB_DESCTYPE_CONFIG),
            .wIndex        = 0U,
            .wLength       = len
        };

        usbh_ctlstate_config (puhost, pudev->host.rx_buf, len);
    }

    status = usbh_ctl_handler (pudev, puhost);

    if (USBH_OK == status) {
        if (len <= USB_CFG_DESC_LEN) {
            usbh_cfgdesc_parse (&puhost->dev_prop.cfg_desc, pudev->host.rx_buf);
        } else {
            usbh_cfgset_parse (&puhost->dev_prop, pudev->host.rx_buf);
        }
    }

    return status;
}

/*!
    \brief      get string descriptor from the USB device
    \param[in]  pudev: pointer to usb core instance
    \param[in]  puhost: pointer to usb host
    \param[in]  str_index: index for the string descriptor
    \param[in]  buf: buffer pointer to the string descriptor
    \param[in]  len: length of the descriptor
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_strdesc_get (usb_core_driver *pudev,
                              usbh_host *puhost,
                              uint8_t str_index, 
                              uint8_t *buf, 
                              uint16_t len)
{
    usbh_status status = USBH_BUSY;

    usbh_control *usb_ctl = &puhost->control;

    if (CTL_IDLE == usb_ctl->ctl_state) {
        usb_ctl->setup.req = (usb_req) {
            .bmRequestType = USB_TRX_IN | USB_RECPTYPE_DEV | USB_REQTYPE_STRD,
            .bRequest      = USB_GET_DESCRIPTOR,
            .wValue        = USBH_DESC(USB_DESCTYPE_STR) | str_index,
            .wIndex        = 0x0409U,
            .wLength       = len
        };

        usbh_ctlstate_config (puhost, pudev->host.rx_buf, len);
    }

    status = usbh_ctl_handler (pudev, puhost);

    if (USBH_OK == status) {
        /* commands successfully sent and response received */
        usbh_strdesc_parse (pudev->host.rx_buf, buf, len);
    }

    return status;
}

/*!
    \brief      set the address to the connected device
    \param[in]  pudev: pointer to usb core instance
    \param[in]  puhost: pointer to usb host
    \param[in]  dev_addr: device address to assign
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_setaddress (usb_core_driver *pudev, usbh_host *puhost, uint8_t dev_addr)
{
    usbh_status status = USBH_BUSY;

    usbh_control *usb_ctl = &puhost->control;

    if (CTL_IDLE == usb_ctl->ctl_state) {
        usb_ctl->setup.req = (usb_req) {
            .bmRequestType = USB_TRX_OUT | USB_RECPTYPE_DEV | USB_REQTYPE_STRD,
            .bRequest      = USB_SET_ADDRESS,
            .wValue        = (uint16_t)dev_addr,
            .wIndex        = 0U,
            .wLength       = 0U
        };

        usbh_ctlstate_config (puhost, NULL, 0U);
    }

    status = usbh_ctl_handler (pudev, puhost);

    return status;
}

/*!
    \brief      set the configuration value to the connected device
    \param[in]  pudev: pointer to usb core instance
    \param[in]  puhost: pointer to usb host
    \param[in]  config_index: configuration value
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_setcfg (usb_core_driver *pudev, usbh_host *puhost, uint16_t config_index)
{
    usbh_status status = USBH_BUSY;

    usbh_control *usb_ctl = &puhost->control;

    if (CTL_IDLE == usb_ctl->ctl_state) {
        usb_ctl->setup.req = (usb_req) {
            .bmRequestType = USB_TRX_OUT | USB_RECPTYPE_DEV | USB_REQTYPE_STRD,
            .bRequest      = USB_SET_CONFIGURATION,
            .wValue        = config_index,
            .wIndex        = 0U,
            .wLength       = 0U
        };

        usbh_ctlstate_config (puhost, NULL, 0U);
    }

    status = usbh_ctl_handler (pudev, puhost);

    return status;
}

/*!
    \brief      set the interface value to the connected device
    \param[in]  pudev: pointer to usb core instance
    \param[in]  puhost: pointer to usb host
    \param[in]  ep_num: endpoint number
    \param[in]  alter_setting: altnated setting value
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_setinterface (usb_core_driver *pudev,
                               usbh_host *puhost,
                               uint8_t ep_num,
                               uint8_t set)
{
    usbh_status status = USBH_BUSY;

    usbh_control *usb_ctl = &puhost->control;

    if (CTL_IDLE == usb_ctl->ctl_state) {
        usb_ctl->setup.req = (usb_req) {
            .bmRequestType = USB_TRX_OUT | USB_RECPTYPE_ITF | USB_REQTYPE_STRD,
            .bRequest      = USB_SET_INTERFACE,
            .wValue        = set,
            .wIndex        = ep_num,
            .wLength       = 0U
        };

        usbh_ctlstate_config (puhost, NULL, 0U);
    }

    status = usbh_ctl_handler (pudev, puhost);

    return status;
}

/*!
    \brief      clear or disable a specific feature
    \param[in]  pudev: pointer to usb core instance
    \param[in]  puhost: pointer to usb host
    \param[in]  ep_addr: endpoint address
    \param[in]  pp_num: pipe number
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_clrfeature (usb_core_driver *pudev,
                             usbh_host *puhost,
                             uint8_t ep_addr, 
                             uint8_t pp_num) 
{
    usbh_status status = USBH_BUSY;

    usbh_control *usb_ctl = &puhost->control;

    if (CTL_IDLE == usb_ctl->ctl_state) {
        usb_ctl->setup.req = (usb_req) {
            .bmRequestType = USB_TRX_OUT | USB_RECPTYPE_EP | USB_REQTYPE_STRD,
            .bRequest      = USB_CLEAR_FEATURE,
            .wValue        = FEATURE_SELECTOR_EP,
            .wIndex        = ep_addr,
            .wLength       = 0
        };

        if (EP_DIR(ep_addr)) {
            pudev->host.pipe[pp_num].data_toggle_in = 0U;
        } else {
            pudev->host.pipe[pp_num].data_toggle_out = 0U;
        }

        usbh_ctlstate_config (puhost, NULL, 0U);
    } 

    status = usbh_ctl_handler (pudev, puhost);

    return status;
}

/*!
    \brief      parse the device descriptor
    \param[in]  dev_desc: pointer to usb device descriptor buffer
    \param[in]  buf: pointer to the source descriptor buffer
    \param[in]  len: length of the descriptor
    \param[out] none
    \retval     operation status
*/
static void  usbh_devdesc_parse (usb_desc_dev *dev_desc, uint8_t *buf, uint16_t len)
{
    *dev_desc = (usb_desc_dev) {
        .header = {
            .bLength         = *(uint8_t *)(buf + 0U),
            .bDescriptorType = *(uint8_t *)(buf + 1U)
        },

        .bcdUSB              = BYTE_SWAP(buf + 2U),
        .bDeviceClass        = *(uint8_t *)(buf + 4U),
        .bDeviceSubClass     = *(uint8_t *)(buf + 5U),
        .bDeviceProtocol     = *(uint8_t *)(buf + 6U),
        .bMaxPacketSize0     = *(uint8_t *)(buf + 7U)
    };

    if (len > 8U) {
        /* for 1st time after device connection, host may issue only 8 bytes for device descriptor length  */
        dev_desc->idVendor              = BYTE_SWAP(buf + 8U);
        dev_desc->idProduct             = BYTE_SWAP(buf + 10U);
        dev_desc->bcdDevice             = BYTE_SWAP(buf + 12U);
        dev_desc->iManufacturer         = *(uint8_t *)(buf + 14U);
        dev_desc->iProduct              = *(uint8_t *)(buf + 15U);
        dev_desc->iSerialNumber         = *(uint8_t *)(buf + 16U);
        dev_desc->bNumberConfigurations = *(uint8_t *)(buf + 17U);
    }
}

/*!
    \brief      parse the configuration descriptor
    \param[in]  cfg_desc: pointer to usb configuration descriptor buffer
    \param[in]  buf: pointer to the source descriptor buffer
    \param[out] none
    \retval     operation status
*/
static void usbh_cfgdesc_parse (usb_desc_config *cfg_desc, uint8_t *buf)
{
    /* parse configuration descriptor */
    *cfg_desc = (usb_desc_config) {
        .header = {
            .bLength         = *(uint8_t *)(buf + 0U),
            .bDescriptorType = *(uint8_t *)(buf + 1U),
        },

        .wTotalLength        = BYTE_SWAP(buf + 2U),
        .bNumInterfaces      = *(uint8_t *)(buf + 4U),
        .bConfigurationValue = *(uint8_t *)(buf + 5U),
        .iConfiguration      = *(uint8_t *)(buf + 6U),
        .bmAttributes        = *(uint8_t *)(buf + 7U),
        .bMaxPower           = *(uint8_t *)(buf + 8U)
    };
}

/*!
    \brief      parse the configuration descriptor set
    \param[in]  udev: pointer to USB core instance
    \param[in]  buf: pointer to the source descriptor buffer
    \param[out] none
    \retval     operation status
*/
static void  usbh_cfgset_parse (usb_dev_prop *udev, uint8_t *buf)
{
    usb_desc_ep *ep = NULL;
    usb_desc_itf *itf = NULL, itf_value;

    usb_desc_header *pdesc = (usb_desc_header *)buf;

    int8_t itf_index = 0U, ep_index = 0U;
    uint16_t ptr;

    uint8_t prev_itf = 0U;
    uint16_t prev_ep_len = 0U;

    /* parse configuration descriptor */
    usbh_cfgdesc_parse (&udev->cfg_desc, buf);

    ptr = USB_CFG_DESC_LEN;

    if (udev->cfg_desc.bNumInterfaces > USBH_MAX_INTERFACES_NUM) {
        return;
    }

    while (ptr < udev->cfg_desc.wTotalLength) {
        pdesc = usbh_nextdesc_get ((uint8_t *)pdesc, &ptr);

        if (pdesc->bDescriptorType == USB_DESCTYPE_ITF) {
            itf_index = *(((uint8_t *)pdesc) + 2U);
            itf = &udev->itf_desc[itf_index];

            if ((*((uint8_t *)pdesc + 3U)) < 3U) {
                usbh_itfdesc_parse (&itf_value, (uint8_t *)pdesc);

                /* parse endpoint descriptors relative to the current interface */
                if (itf_value.bNumEndpoints > USBH_MAX_EP_NUM) {
                    return;
                }

                for (ep_index = 0; ep_index < itf_value.bNumEndpoints; ) {
                    pdesc = usbh_nextdesc_get ((void*)pdesc, &ptr);

                    if (pdesc->bDescriptorType == USB_DESCTYPE_EP) {
                        ep = &udev->ep_desc[itf_index][ep_index];

                        if (prev_itf != itf_index) {
                            prev_itf = itf_index;
                            usbh_itfdesc_parse (itf, (uint8_t *)&itf_value);
                        } else {
                            if (prev_ep_len > BYTE_SWAP((uint8_t *)pdesc + 4U)) {
                                break;
                            } else {
                                usbh_itfdesc_parse (itf, (uint8_t *)&itf_value);
                            }
                        }

                        usbh_epdesc_parse (ep, (uint8_t *)pdesc);
                        prev_ep_len = BYTE_SWAP((uint8_t *)pdesc + 4U);
                        ep_index++;
                    }
                }
            }
        }
    }
}

/*!
    \brief      parse the interface descriptor
    \param[in]  itf_desc: pointer to usb interface descriptor buffer
    \param[in]  buf: pointer to the source descriptor buffer
    \param[out] none
    \retval     operation status
*/
static void  usbh_itfdesc_parse (usb_desc_itf *itf_desc, uint8_t *buf)
{
    *itf_desc = (usb_desc_itf) {
        .header = {
            .bLength         = *(uint8_t *)(buf + 0U),
            .bDescriptorType = *(uint8_t *)(buf + 1U),
        },

        .bInterfaceNumber    = *(uint8_t *)(buf + 2U),
        .bAlternateSetting   = *(uint8_t *)(buf + 3U),
        .bNumEndpoints       = *(uint8_t *)(buf + 4U),
        .bInterfaceClass     = *(uint8_t *)(buf + 5U),
        .bInterfaceSubClass  = *(uint8_t *)(buf + 6U),
        .bInterfaceProtocol  = *(uint8_t *)(buf + 7U),
        .iInterface          = *(uint8_t *)(buf + 8U)
    };
}

/*!
    \brief      parse the endpoint descriptor
    \param[in]  ep_desc: pointer to usb endpoint descriptor buffer
    \param[in]  buf: pointer to the source descriptor buffer
    \param[out] none
    \retval     operation status
*/
static void  usbh_epdesc_parse (usb_desc_ep *ep_desc, uint8_t *buf)
{
    *ep_desc = (usb_desc_ep) {
        .header = {
            .bLength         = *(uint8_t *)(buf + 0U),
            .bDescriptorType = *(uint8_t *)(buf + 1U)
        },

        .bEndpointAddress    = *(uint8_t *)(buf + 2U),
        .bmAttributes        = *(uint8_t *)(buf + 3U),
        .wMaxPacketSize      = BYTE_SWAP(buf + 4U),
        .bInterval           = *(uint8_t *)(buf + 6U)
    };
}

/*!
    \brief      parse the string descriptor
    \param[in]  psrc: source pointer containing the descriptor data
    \param[in]  pdest: destination address pointer
    \param[in]  len: length of the descriptor
    \param[out] none
    \retval     operation status
*/
static void usbh_strdesc_parse (uint8_t *psrc, uint8_t *pdest, uint16_t len)
{
    uint16_t str_len = 0U, index = 0U;

    /* the unicode string descriptor is not NULL-terminated. The string length is
     * computed by substracting two from the value of the first byte of the descriptor.
     */

    /* check which is lower size, the size of string or the length of bytes read from the device */
    if (USB_DESCTYPE_STR == psrc[1]) {
        /* make sure the descriptor is string type */

        /* psrc[0] contains Size of Descriptor, subtract 2 to get the length of string */      
        str_len = USB_MIN(psrc[0] - 2U, len);

        psrc += 2U; /* adjust the offset ignoring the string len and descriptor type */

        for (index = 0U; index < str_len; index += 2U) {
            /* copy only the string and ignore the unicode id, hence add the src */
            *pdest = psrc[index];

            pdest++;
        }

        *pdest = 0U; /* mark end of string */  
    }
}

/*!
    \brief      get the next descriptor header
    \param[in]  pbuf: pointer to buffer where the configuration descriptor set is available
    \param[in]  ptr: data popinter inside the configuration descriptor set
    \param[out] none
    \retval     operation status
*/
usb_desc_header *usbh_nextdesc_get (uint8_t *pbuf, uint16_t *ptr)
{
    usb_desc_header *pnext;

    *ptr += ((usb_desc_header *)pbuf)->bLength;

    pnext = (usb_desc_header *)((uint8_t *)pbuf + ((usb_desc_header *)pbuf)->bLength);

    return (pnext);
}

