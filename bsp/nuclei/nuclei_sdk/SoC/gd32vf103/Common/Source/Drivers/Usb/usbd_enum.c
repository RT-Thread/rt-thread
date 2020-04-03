/*!
    \file  usbd_enum.c
    \brief USB enumeration function

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

#include "usbd_enum.h"
#include "usb_ch9_std.h"

static usb_reqsta _usb_std_getstatus        (usb_core_driver *udev, usb_req *req);
static usb_reqsta _usb_std_setaddress       (usb_core_driver *udev, usb_req *req);
static usb_reqsta _usb_std_setconfiguration (usb_core_driver *udev, usb_req *req);
static usb_reqsta _usb_std_getconfiguration (usb_core_driver *udev, usb_req *req);
static usb_reqsta _usb_std_getdescriptor    (usb_core_driver *udev, usb_req *req);
static usb_reqsta _usb_std_setfeature       (usb_core_driver *udev, usb_req *req);
static usb_reqsta _usb_std_clearfeature     (usb_core_driver *udev, usb_req *req);
static usb_reqsta _usb_std_reserved         (usb_core_driver *udev, usb_req *req);
static usb_reqsta _usb_std_setdescriptor    (usb_core_driver *udev, usb_req *req);
static usb_reqsta _usb_std_getinterface     (usb_core_driver *udev, usb_req *req);
static usb_reqsta _usb_std_setinterface     (usb_core_driver *udev, usb_req *req);
static usb_reqsta _usb_std_synchframe       (usb_core_driver *udev, usb_req *req);

static uint8_t* _usb_dev_desc_get     (usb_core_driver *udev, uint8_t index, uint16_t *len);
static uint8_t* _usb_config_desc_get  (usb_core_driver *udev, uint8_t index, uint16_t *len);
static uint8_t* _usb_str_desc_get     (usb_core_driver *udev, uint8_t index, uint16_t *len);
static uint8_t* _usb_bos_desc_get     (usb_core_driver *udev, uint8_t index, uint16_t *len);

static usb_reqsta (*_std_dev_req[])(usb_core_driver *udev, usb_req *req) =
{
    [USB_GET_STATUS]        = _usb_std_getstatus,
    [USB_CLEAR_FEATURE]     = _usb_std_clearfeature,
    [USB_RESERVED2]         = _usb_std_reserved,
    [USB_SET_FEATURE]       = _usb_std_setfeature,
    [USB_RESERVED4]         = _usb_std_reserved,
    [USB_SET_ADDRESS]       = _usb_std_setaddress,
    [USB_GET_DESCRIPTOR]    = _usb_std_getdescriptor,
    [USB_SET_DESCRIPTOR]    = _usb_std_setdescriptor,
    [USB_GET_CONFIGURATION] = _usb_std_getconfiguration,
    [USB_SET_CONFIGURATION] = _usb_std_setconfiguration,
    [USB_GET_INTERFACE]     = _usb_std_getinterface,
    [USB_SET_INTERFACE]     = _usb_std_setinterface,
    [USB_SYNCH_FRAME]       = _usb_std_synchframe,
};

/* get standard descriptor handler */
static uint8_t* (*std_desc_get[])(usb_core_driver *udev, uint8_t index, uint16_t *len) = {
    [USB_DESCTYPE_DEV - 1]    = _usb_dev_desc_get,
    [USB_DESCTYPE_CONFIG - 1] = _usb_config_desc_get,
    [USB_DESCTYPE_STR - 1]    = _usb_str_desc_get
};

/*!
    \brief      handle USB standard device request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     USB device request status
*/
usb_reqsta  usbd_standard_request (usb_core_driver *udev, usb_req *req)
{
    return (*_std_dev_req[req->bRequest])(udev, req);
}

/*!
    \brief      handle USB device class request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB device class request
    \param[out] none
    \retval     USB device request status
*/
usb_reqsta  usbd_class_request (usb_core_driver *udev, usb_req *req)
{
    if (USBD_CONFIGURED == udev->dev.cur_status) {
        if (BYTE_LOW(req->wIndex) <= USBD_ITF_MAX_NUM) {
            /* call device class handle function */
            return (usb_reqsta)udev->dev.class_core->req_proc(udev, req);
        }
    }

    return REQ_NOTSUPP;
}

/*!
    \brief      handle USB vendor request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB vendor request
    \param[out] none
    \retval     USB device request status
*/
usb_reqsta  usbd_vendor_request (usb_core_driver *udev, usb_req *req)
{
    /* added by user... */

    return REQ_SUPP;
}

/*!
    \brief      no operation, just for reserved
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB vendor request
    \param[out] none
    \retval     USB device request status
*/
static usb_reqsta _usb_std_reserved (usb_core_driver *udev, usb_req *req)
{
    /* no operation... */

    return REQ_NOTSUPP;
}

/*!
    \brief      get the device descriptor
    \param[in]  udev: pointer to USB device instance
    \param[in]  index: no use
    \param[out] len: data length pointer
    \retval     descriptor buffer pointer
*/
static uint8_t* _usb_dev_desc_get (usb_core_driver *udev, uint8_t index, uint16_t *len)
{
    *len = udev->dev.desc.dev_desc[0];

    return udev->dev.desc.dev_desc;
}

/*!
    \brief      get the configuration descriptor
    \brief[in]  udev: pointer to USB device instance
    \brief[in]  index: no use
    \param[out] len: data length pointer
    \retval     descriptor buffer pointer
*/
static uint8_t* _usb_config_desc_get (usb_core_driver *udev, uint8_t index, uint16_t *len)
{
    *len = udev->dev.desc.config_desc[2];

    return udev->dev.desc.config_desc;
}

/*!
    \brief      get the BOS descriptor
    \brief[in]  udev: pointer to USB device instance
    \brief[in]  index: no use
    \param[out] len: data length pointer
    \retval     descriptor buffer pointer
*/
static uint8_t* _usb_bos_desc_get (usb_core_driver *udev, uint8_t index, uint16_t *len)
{
    *len = udev->dev.desc.bos_desc[2];

    return udev->dev.desc.bos_desc;
}

/*!
    \brief      get string descriptor
    \param[in]  udev: pointer to USB device instance
    \param[in]  index: string descriptor index
    \param[out] len: pointer to string length
    \retval     descriptor buffer pointer
*/
static uint8_t* _usb_str_desc_get (usb_core_driver *udev, uint8_t index, uint16_t *len)
{
    uint8_t *desc = udev->dev.desc.strings[index];

    *len = desc[0];

    return desc;
}

/*!
    \brief      handle Get_Status request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     USB device request status
*/
static usb_reqsta _usb_std_getstatus (usb_core_driver *udev, usb_req *req)
{
    uint8_t recp = BYTE_LOW(req->wIndex);

    usb_transc *transc = &udev->dev.transc_in[0];

    static uint8_t status[2] = {0};

    switch(req->bmRequestType & USB_RECPTYPE_MASK) {
        case USB_RECPTYPE_DEV:
            if ((USBD_ADDRESSED == udev->dev.cur_status) || \
                (USBD_CONFIGURED == udev->dev.cur_status)) {

                if (udev->dev.pm.power_mode) {
                    status[0] = USB_STATUS_SELF_POWERED;
                } else {
                    status[0] = 0U;
                }

                if (udev->dev.pm.dev_remote_wakeup) {
                    status[0] |= USB_STATUS_REMOTE_WAKEUP;
                } else {
                    status[0] = 0U;
                }

                transc->xfer_buf = status;
                transc->remain_len = 2U;

                return REQ_SUPP;
            }
            break;

        case USB_RECPTYPE_ITF:
            if ((USBD_CONFIGURED == udev->dev.cur_status) && (recp <= USBD_ITF_MAX_NUM)) {
                transc->xfer_buf = status;
                transc->remain_len = 2U;

                return REQ_SUPP;
            }
            break;

        case USB_RECPTYPE_EP:
            if (USBD_CONFIGURED == udev->dev.cur_status) {
                if (0x80U == (recp & 0x80U)) {
                    status[0] = udev->dev.transc_in[EP_ID(recp)].ep_stall;
                } else {
                    status[0] = udev->dev.transc_out[recp].ep_stall;
                }

                transc->xfer_buf = status;
                transc->remain_len = 2U;

                return REQ_SUPP;
            }
            break;

        default:
            break;
    }

    return REQ_NOTSUPP;
}

/*!
    \brief      handle USB Clear_Feature request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: USB device request
    \param[out] none
    \retval     USB device request status
*/
static usb_reqsta _usb_std_clearfeature (usb_core_driver *udev, usb_req *req)
{
    uint8_t ep = 0;

    switch(req->bmRequestType & USB_RECPTYPE_MASK)
    {
        case USB_RECPTYPE_DEV:
            if ((USBD_ADDRESSED == udev->dev.cur_status) || \
                (USBD_CONFIGURED == udev->dev.cur_status)) {

                /* clear device remote wakeup feature */
                if (USB_FEATURE_REMOTE_WAKEUP == req->wValue) {
                    udev->dev.pm.dev_remote_wakeup = 0U;

                    return REQ_SUPP;
                }
            }
            break;

        case USB_RECPTYPE_ITF:
            break;

        case USB_RECPTYPE_EP:
            /* get endpoint address */
            ep = BYTE_LOW(req->wIndex);

            if (USBD_CONFIGURED == udev->dev.cur_status) {
                /* clear endpoint halt feature */
                if ((USB_FEATURE_EP_HALT == req->wValue) && (!CTL_EP(ep))) {
                    usbd_ep_stall_clear (udev, ep);

                    udev->dev.class_core->req_proc (udev, req);
                }

                return REQ_SUPP;
            }
            break;

        default:
            break;
    }

    return REQ_NOTSUPP;
}

/*!
    \brief      handle USB Set_Feature request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     USB device request status
*/
static usb_reqsta _usb_std_setfeature (usb_core_driver *udev, usb_req *req)
{
    uint8_t ep = 0;

    switch(req->bmRequestType & USB_RECPTYPE_MASK)
    {
        case USB_RECPTYPE_DEV:
            if ((USBD_ADDRESSED == udev->dev.cur_status) || \
                (USBD_CONFIGURED == udev->dev.cur_status)) {
                /* set device remote wakeup feature */
                if (USB_FEATURE_REMOTE_WAKEUP == req->wValue) {
                    udev->dev.pm.dev_remote_wakeup = 1U;
                }

                return REQ_SUPP;
            }
            break;

        case USB_RECPTYPE_ITF:
            break;

        case USB_RECPTYPE_EP:
            /* get endpoint address */
            ep = BYTE_LOW(req->wIndex);

            if (USBD_CONFIGURED == udev->dev.cur_status) {
                /* set endpoint halt feature */
                if ((USB_FEATURE_EP_HALT == req->wValue) && (!CTL_EP(ep))) {
                    usbd_ep_stall (udev, ep);
                }

                return REQ_SUPP;
            }
            break;

        default:
            break;
    }

    return REQ_NOTSUPP;
}

/*!
    \brief      handle USB Set_Address request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     USB device request status
*/
static usb_reqsta _usb_std_setaddress (usb_core_driver *udev, usb_req *req)
{
    if ((0U == req->wIndex) && (0U == req->wLength)) {
        udev->dev.dev_addr = (uint8_t)(req->wValue) & 0x7FU;

        if (udev->dev.cur_status != USBD_CONFIGURED) {
            usbd_addr_set (udev, udev->dev.dev_addr);

            if (udev->dev.dev_addr) {
                udev->dev.cur_status = USBD_ADDRESSED;
            } else {
                udev->dev.cur_status = USBD_DEFAULT;
            }

            return REQ_SUPP;
        }
    }

    return REQ_NOTSUPP;
}

/*!
    \brief      handle USB Get_Descriptor request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     USB device request status
*/
static usb_reqsta _usb_std_getdescriptor (usb_core_driver *udev, usb_req *req)
{
    uint8_t desc_type = 0;
    uint8_t desc_index = 0;

    usb_transc *transc = &udev->dev.transc_in[0];

    /* get device standard descriptor */
    switch (req->bmRequestType & USB_RECPTYPE_MASK) {
    case USB_RECPTYPE_DEV:
        desc_type = BYTE_HIGH(req->wValue);
        desc_index = BYTE_LOW(req->wValue);

        switch (desc_type) {
        case USB_DESCTYPE_DEV:
            transc->xfer_buf = std_desc_get[desc_type - 1U](udev, desc_index, (uint16_t *)&(transc->remain_len));

            if (64U == req->wLength) {
                transc->remain_len = 8U;
            }
            break;

        case USB_DESCTYPE_CONFIG:
            transc->xfer_buf = std_desc_get[desc_type - 1U](udev, desc_index, (uint16_t *)&(transc->remain_len));
            break;

        case USB_DESCTYPE_STR:
            if (desc_index < STR_IDX_MAX) {
                transc->xfer_buf = std_desc_get[desc_type - 1U](udev, desc_index, (uint16_t *)&(transc->remain_len));
            }
            break;

        case USB_DESCTYPE_ITF:
        case USB_DESCTYPE_EP:
        case USB_DESCTYPE_DEV_QUALIFIER:
        case USB_DESCTYPE_OTHER_SPD_CONFIG:
        case USB_DESCTYPE_ITF_POWER:
            break;

        case USB_DESCTYPE_BOS:
            transc->xfer_buf = _usb_bos_desc_get(udev, desc_index, (uint16_t *)&(transc->remain_len));
            break;

        default:
            break;
        }
        break;

    case USB_RECPTYPE_ITF:
        /* get device class special descriptor */
        return (usb_reqsta)(udev->dev.class_core->req_proc(udev, req));

    case USB_RECPTYPE_EP:
        break;

    default:
        break;
    }

    if ((0U != transc->remain_len) && (0U != req->wLength)) {
        if (transc->remain_len < req->wLength) {
            if ((transc->remain_len >= transc->max_len) && (0U == (transc->remain_len % transc->max_len))) {
                udev->dev.control.ctl_zlp = 1;
            }
        } else {
            transc->remain_len = req->wLength;
        }

        return REQ_SUPP;
    }

    return REQ_NOTSUPP;
}

/*!
    \brief      handle USB Set_Descriptor request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     USB device request status
*/
static usb_reqsta _usb_std_setdescriptor (usb_core_driver *udev, usb_req *req)
{
    /* no handle... */
    return REQ_SUPP;
}

/*!
    \brief      handle USB Get_Configuration request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     USB device request status
*/
static usb_reqsta _usb_std_getconfiguration (usb_core_driver *udev, usb_req *req)
{
    usb_transc *transc = &udev->dev.transc_in[0];

    switch (udev->dev.cur_status) {
    case USBD_ADDRESSED:
        if (USB_DEFAULT_CONFIG == udev->dev.config) {
            transc->xfer_buf = &(udev->dev.config);
            transc->remain_len = 1U;

            return REQ_SUPP;
        }
        break;

    case USBD_CONFIGURED:
        if (udev->dev.config != USB_DEFAULT_CONFIG) {
            transc->xfer_buf = &(udev->dev.config);
            transc->remain_len = 1U;

            return REQ_SUPP;
        }
        break;

    default:
        break;
    }

    return REQ_NOTSUPP;
}

/*!
    \brief      handle USB Set_Configuration request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     USB device request status
*/
static usb_reqsta _usb_std_setconfiguration (usb_core_driver *udev, usb_req *req)
{
    static uint8_t config;

    config = (uint8_t)(req->wValue);

    if (config <= USBD_CFG_MAX_NUM) {
        switch (udev->dev.cur_status) {
        case USBD_ADDRESSED:
            if (config){
                udev->dev.class_core->init(udev, config);

                udev->dev.config = config;
                udev->dev.cur_status = USBD_CONFIGURED;
            }

            return REQ_SUPP;

        case USBD_CONFIGURED:
            if (USB_DEFAULT_CONFIG == config) {
                udev->dev.class_core->deinit(udev, config);

                udev->dev.config = config;
                udev->dev.cur_status = USBD_ADDRESSED;
            } else if (config != udev->dev.config) {
                /* clear old configuration */
                udev->dev.class_core->deinit(udev, config);

                /* set new configuration */
                udev->dev.config = config;
                udev->dev.class_core->init(udev, config);
            }

            return REQ_SUPP;

        case USBD_DEFAULT:
            break;

        default:
            break;
        }
    }

    return REQ_NOTSUPP;
}

/*!
    \brief      handle USB Get_Interface request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     USB device request status
*/
static usb_reqsta _usb_std_getinterface (usb_core_driver *udev, usb_req *req)
{
    switch (udev->dev.cur_status) {
    case USBD_DEFAULT:
        break;

    case USBD_ADDRESSED:
        break;

    case USBD_CONFIGURED:
        if (BYTE_LOW(req->wIndex) <= USBD_ITF_MAX_NUM) {
            usb_transc *transc = &udev->dev.transc_in[0];

            transc->xfer_buf = &(udev->dev.class_core->alter_set);
            transc->remain_len = 1U;

            return REQ_SUPP;
        }
        break;

    default:
        break;
    }

    return REQ_NOTSUPP;
}

/*!
    \brief      handle USB Set_Interface request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     USB device request status
*/
static usb_reqsta _usb_std_setinterface (usb_core_driver *udev, usb_req *req)
{
    switch (udev->dev.cur_status) {
    case USBD_DEFAULT:
        break;

    case USBD_ADDRESSED:
        break;

    case USBD_CONFIGURED:
        if (BYTE_LOW(req->wIndex) <= USBD_ITF_MAX_NUM) {
            udev->dev.class_core->alter_set = req->wValue;

            return REQ_SUPP;
        }
        break;

    default:
        break;
    }

    return REQ_NOTSUPP;
}

/*!
    \brief      handle USB SynchFrame request
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     USB device request status
*/
static usb_reqsta _usb_std_synchframe (usb_core_driver *udev, usb_req *req)
{
    /* no handle... */
    return REQ_SUPP;
}

/*!
    \brief      handle USB enumeration error
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
void usbd_enum_error (usb_core_driver *udev, usb_req *req)
{
    usbd_ep_stall (udev, 0x80);
    usbd_ep_stall (udev, 0x00);

    usb_ctlep_startout(udev);
}

/*!
    \brief      convert hex 32bits value into unicode char
    \param[in]  value: hex 32bits value
    \param[in]  pbuf: buffer pointer to store unicode char
    \param[in]  len: value length
    \param[out] none
    \retval     none
*/
void int_to_unicode (uint32_t value, uint8_t *pbuf, uint8_t len)
{
    uint8_t index = 0;

    for (index = 0; index < len; index++) {
        if ((value >> 28) < 0x0A) {
            pbuf[2 * index] = (value >> 28) + '0';
        } else {
            pbuf[2 * index] = (value >> 28) + 'A' - 10; 
        }

        value = value << 4;

        pbuf[2 * index + 1] = 0;
    }
}
