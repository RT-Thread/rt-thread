/*!
    \file    usbh_hid_core.c
    \brief   USB host HID class driver

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
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

#include <string.h>
#include "usbh_pipe.h"
#include "usbh_hid_core.h"
#include "usbh_standard_hid.h"

/* local function prototypes ('static') */
static void usbh_hiddesc_parse(usb_desc_hid *hid_desc, uint8_t *buf);
static void usbh_hid_itf_deinit(usbh_host *uhost);
static usbh_status usbh_hid_itf_init(usbh_host *uhost);
static usbh_status usbh_hid_class_req(usbh_host *uhost);
static usbh_status usbh_hid_handle(usbh_host *uhost);
static usbh_status usbh_hid_reportdesc_get(usbh_host *uhost, uint16_t len);
static usbh_status usbh_hid_sof(usbh_host *uhost);
static usbh_status usbh_hid_desc_get(usbh_host *uhost, uint16_t len);
static usbh_status usbh_set_idle(usbh_host *uhost, uint8_t duration, uint8_t report_ID);
static usbh_status usbh_set_protocol(usbh_host *uhost, uint8_t protocol);

usbh_class usbh_hid = {
    USB_HID_CLASS,
    usbh_hid_itf_init,
    usbh_hid_itf_deinit,
    usbh_hid_class_req,
    usbh_hid_handle,
    usbh_hid_sof
};

/*!
    \brief      get report
    \param[in]  uhost: pointer to USB host
    \param[in]  report_type: duration for HID set idle request
    \param[in]  report_ID: targeted report ID for HID set idle request
    \param[in]  report_len: length of data report to be send
    \param[in]  report_buf: report buffer
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_get_report(usbh_host *uhost, \
                            uint8_t  report_type, \
                            uint8_t  report_ID, \
                            uint8_t  report_len, \
                            uint8_t *report_buf)
{
    usbh_status status = USBH_BUSY;

    if(CTL_IDLE == uhost->control.ctl_state) {
        uhost->control.setup.req = (usb_req) {
            .bmRequestType = USB_TRX_IN | USB_RECPTYPE_ITF | USB_REQTYPE_CLASS,
            .bRequest      = GET_REPORT,
            .wValue        = (report_type << 8) | report_ID,
            .wIndex        = 0U,
            .wLength       = report_len
        };

        usbh_ctlstate_config(uhost, report_buf, report_len);
    }

    status = usbh_ctl_handler(uhost);

    return status;
}

/*!
    \brief      set report
    \param[in]  udev: pointer to USB core instance
    \param[in]  uhost: pointer to USB host
    \param[in]  report_type: duration for HID set idle request
    \param[in]  report_ID: targeted report ID for HID set idle request
    \param[in]  report_len: length of data report to be send
    \param[in]  report_buf: report buffer
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_set_report(usb_core_driver *udev, \
                            usbh_host *uhost, \
                            uint8_t  report_type, \
                            uint8_t  report_ID, \
                            uint8_t  report_len, \
                            uint8_t *report_buf)
{
    usbh_status status = USBH_BUSY;

    if(CTL_IDLE == uhost->control.ctl_state) {
        uhost->control.setup.req = (usb_req) {
            .bmRequestType = USB_TRX_OUT | USB_RECPTYPE_ITF | USB_REQTYPE_CLASS,
            .bRequest      = SET_REPORT,
            .wValue        = (report_type << 8) | report_ID,
            .wIndex        = 0U,
            .wLength       = report_len
        };

        usbh_ctlstate_config(uhost, report_buf, report_len);
    }

    status = usbh_ctl_handler(uhost);

    return status;
}

/*!
    \brief      deinitialize the host pipes used for the HID class
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
void usbh_hid_itf_deinit(usbh_host *uhost)
{
    usbh_hid_handler *hid = (usbh_hid_handler *)uhost->active_class->class_data;

    if(0x00U != hid->pipe_in) {
        usb_pipe_halt(uhost->data, hid->pipe_in);

        usbh_pipe_free(uhost->data, hid->pipe_in);

        /* reset the pipe as free */
        hid->pipe_in = 0U;
    }

    if(0x00U != hid->pipe_out) {
        usb_pipe_halt(uhost->data, hid->pipe_out);

        usbh_pipe_free(uhost->data, hid->pipe_out);

        /* reset the channel as free */
        hid->pipe_out = 0U;
    }
}

/*!
    \brief      return device type
    \param[in]  udev: pointer to USB core instance
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     hid_type
*/
hid_type usbh_hid_device_type_get(usb_core_driver *udev, usbh_host *uhost)
{
    hid_type type = HID_UNKNOWN;
    uint8_t interface_protocol;

    if(HOST_CLASS_HANDLER == uhost->cur_state) {
        interface_protocol = uhost->dev_prop.cfg_desc_set.itf_desc_set[uhost->dev_prop.cur_itf][0].itf_desc.bInterfaceProtocol;

        if(USB_HID_PROTOCOL_KEYBOARD == interface_protocol) {
            type = HID_KEYBOARD;
        } else {
            if(USB_HID_PROTOCOL_MOUSE == interface_protocol) {
                type = HID_MOUSE;
            }
        }
    }

    return type;
}

/*!
    \brief      return HID device poll time
    \param[in]  udev: pointer to USB core instance
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     poll time (ms)
*/
uint8_t usbh_hid_poll_interval_get(usb_core_driver *udev, usbh_host *uhost)
{
    usbh_hid_handler *hid = (usbh_hid_handler *)uhost->active_class->class_data;

    if((HOST_CLASS_ENUM == uhost->cur_state) || \
            (HOST_USER_INPUT == uhost->cur_state) || \
            (HOST_CLASS_CHECK == uhost->cur_state) || \
            (HOST_CLASS_HANDLER == uhost->cur_state)) {
        return (uint8_t)(hid->poll);
    } else {
        return 0U;
    }
}

/*!
    \brief      initialize the hid class
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
static usbh_status usbh_hid_itf_init(usbh_host *uhost)
{
    uint8_t num = 0U, ep_num = 0U, interface = 0U;
    usbh_status status = USBH_BUSY;

    interface = usbh_interface_find(&uhost->dev_prop, USB_HID_CLASS, USB_HID_SUBCLASS_BOOT_ITF, 0xFFU);

    if(0xFFU == interface) {
        uhost->usr_cb->dev_not_supported();

        status = USBH_FAIL;
    } else {
        usbh_interface_select(&uhost->dev_prop, interface);

        static usbh_hid_handler hid_handler;

        memset((void *)&hid_handler, 0U, sizeof(usbh_hid_handler));

        hid_handler.state = HID_ERROR;

        uint8_t itf_protocol = uhost->dev_prop.cfg_desc_set.itf_desc_set[uhost->dev_prop.cur_itf][0].itf_desc.bInterfaceProtocol;
        if(USB_HID_PROTOCOL_KEYBOARD == itf_protocol) {
            hid_handler.init = usbh_hid_keybrd_init;
            hid_handler.decode = usbh_hid_keybrd_decode;
        } else if(USB_HID_PROTOCOL_MOUSE == itf_protocol) {
            hid_handler.init = usbh_hid_mouse_init;
            hid_handler.decode = usbh_hid_mouse_decode;
        } else {
            status = USBH_FAIL;
        }

        hid_handler.state = HID_INIT;
        hid_handler.ctl_state = HID_REQ_INIT;
        hid_handler.ep_addr = uhost->dev_prop.cfg_desc_set.itf_desc_set[uhost->dev_prop.cur_itf][0].ep_desc[0].bEndpointAddress;
        hid_handler.len = uhost->dev_prop.cfg_desc_set.itf_desc_set[uhost->dev_prop.cur_itf][0].ep_desc[0].wMaxPacketSize;
        hid_handler.poll = uhost->dev_prop.cfg_desc_set.itf_desc_set[uhost->dev_prop.cur_itf][0].ep_desc[0].bInterval;

        if(hid_handler.poll < HID_MIN_POLL) {
            hid_handler.poll = HID_MIN_POLL;
        }

        /* check for available number of endpoints */
        /* find the number of endpoints in the interface descriptor */
        /* choose the lower number in order not to overrun the buffer allocated */
        ep_num = USB_MIN(uhost->dev_prop.cfg_desc_set.itf_desc_set[uhost->dev_prop.cur_itf][0].itf_desc.bNumEndpoints, USBH_MAX_EP_NUM);

        /* decode endpoint IN and OUT address from interface descriptor */
        for(num = 0U; num < ep_num; num++) {
            usb_desc_ep *ep_desc = &uhost->dev_prop.cfg_desc_set.itf_desc_set[uhost->dev_prop.cur_itf][0].ep_desc[num];

            uint8_t ep_addr = ep_desc->bEndpointAddress;

            if(ep_addr & 0x80U) {
                hid_handler.ep_in = ep_addr;
                hid_handler.pipe_in = usbh_pipe_allocate(uhost->data, ep_addr);

                /* open channel for IN endpoint */
                usbh_pipe_create(uhost->data, \
                                 &uhost->dev_prop, \
                                 hid_handler.pipe_in, \
                                 USB_EPTYPE_INTR, \
                                 hid_handler.len);

                usbh_pipe_toggle_set(uhost->data, hid_handler.pipe_in, 0U);
            } else {
                hid_handler.ep_out = ep_addr;
                hid_handler.pipe_out = usbh_pipe_allocate(uhost->data, ep_addr);

                /* open channel for OUT endpoint */
                usbh_pipe_create(uhost->data, \
                                 &uhost->dev_prop, \
                                 hid_handler.pipe_out, \
                                 USB_EPTYPE_INTR, \
                                 hid_handler.len);

                usbh_pipe_toggle_set(uhost->data, hid_handler.pipe_out, 0U);
            }
        }

        uhost->active_class->class_data = (void *)&hid_handler;

        status = USBH_OK;
    }

    return status;
}

/*!
    \brief      handle HID class requests for HID class
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
static usbh_status usbh_hid_class_req(usbh_host *uhost)
{
    usbh_status status = USBH_BUSY;
    usbh_status class_req_status = USBH_BUSY;

    usbh_hid_handler *hid = (usbh_hid_handler *)uhost->active_class->class_data;

    /* handle HID control state machine */
    switch(hid->ctl_state) {
    case HID_REQ_INIT:
    case HID_REQ_GET_HID_DESC:
        /* get HID descriptor */
        if(USBH_OK == usbh_hid_desc_get(uhost, USB_HID_DESC_SIZE)) {
            usbh_hiddesc_parse(&hid->hid_desc, uhost->dev_prop.data);

            hid->ctl_state = HID_REQ_GET_REPORT_DESC;
        }
        break;

    case HID_REQ_GET_REPORT_DESC:
        /* get report descriptor */
        if(USBH_OK == usbh_hid_reportdesc_get(uhost, hid->hid_desc.wDescriptorLength)) {
            hid->ctl_state = HID_REQ_SET_IDLE;
        }
        break;

    case HID_REQ_SET_IDLE:
        class_req_status = usbh_set_idle(uhost, 0U, 0U);

        /* set idle */
        if(USBH_OK == class_req_status) {
            hid->ctl_state = HID_REQ_SET_PROTOCOL;
        } else {
            if(USBH_NOT_SUPPORTED == class_req_status) {
                hid->ctl_state = HID_REQ_SET_PROTOCOL;
            }
        }
        break;

    case HID_REQ_SET_PROTOCOL:
        /* set protocol */
        if(USBH_OK == usbh_set_protocol(uhost, 0U)) {
            hid->ctl_state = HID_REQ_IDLE;

            /* all requests performed */
            status = USBH_OK;
        }
        break;

    case HID_REQ_IDLE:
    default:
        break;
    }

    return status;
}

/*!
    \brief      manage state machine for HID data transfers
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
static usbh_status usbh_hid_handle(usbh_host *uhost)
{
    usbh_status status = USBH_OK;
    usbh_hid_handler *hid = (usbh_hid_handler *)uhost->active_class->class_data;

    switch(hid->state) {
    case HID_INIT:
        hid->init(uhost->data, uhost);
        hid->state = HID_IDLE;
        break;

    case HID_IDLE:
        hid->state = HID_SYNC;
        status = USBH_OK;
        break;

    case HID_SYNC:
        /* sync with start of even frame */
        if(1U == usb_frame_even(uhost->data)) {
            hid->state = HID_GET_DATA;
        }
        break;

    case HID_GET_DATA:
        usbh_data_recev(uhost->data, hid->pdata, hid->pipe_in, hid->len);

        hid->state = HID_POLL;
        hid->timer = usb_curframe_get(uhost->data);
        hid->data_ready = 0U;
        break;

    case HID_POLL:
        if(URB_DONE == usbh_urbstate_get(uhost->data, hid->pipe_in)) {
            if(0U == hid->data_ready) {
                hid->data_ready = 1U;

                hid->decode(hid->pdata);
            }
        } else {
            /* check IN endpoint STALL status */
            if(URB_STALL == usbh_urbstate_get(uhost->data, hid->pipe_in)) {
                /* issue clear feature on interrupt IN endpoint */
                if(USBH_OK == (usbh_clrfeature(uhost, hid->ep_addr, hid->pipe_in))) {
                    /* change state to issue next IN token */
                    hid->state = HID_GET_DATA;
                }
            }
        }
        break;

    default:
        break;
    }
    return status;
}

/*!
    \brief      send get report descriptor command to the device
    \param[in]  uhost: pointer to USB host
    \param[in]  len: HID report descriptor length
    \param[out] none
    \retval     operation status
*/
static usbh_status usbh_hid_reportdesc_get(usbh_host *uhost, uint16_t len)
{
    usbh_status status = USBH_BUSY;

    if(CTL_IDLE == uhost->control.ctl_state) {
        uhost->control.setup.req = (usb_req) {
            .bmRequestType = USB_TRX_IN | USB_RECPTYPE_ITF | USB_REQTYPE_STRD,
            .bRequest      = USB_GET_DESCRIPTOR,
            .wValue        = USBH_DESC(USB_DESCTYPE_REPORT),
            .wIndex        = 0U,
            .wLength       = len
        };

        usbh_ctlstate_config(uhost, uhost->dev_prop.data, len);
    }

    status = usbh_ctl_handler(uhost);

    return status;
}

/*!
    \brief      managing the SOF process
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
static usbh_status usbh_hid_sof(usbh_host *uhost)
{
    usbh_hid_handler *hid = (usbh_hid_handler *)uhost->active_class->class_data;

    if(HID_POLL == hid->state) {
        uint32_t frame_count = usb_curframe_get(uhost->data);

        if((frame_count > hid->timer) && ((frame_count - hid->timer) >= hid->poll)) {
            hid->state = HID_GET_DATA;
        } else if((frame_count < hid->timer) && ((frame_count + 0x3FFFU - hid->timer) >= hid->poll)) {
            hid->state = HID_GET_DATA;
        } else {
            /* no operation */
        }
    }

    return USBH_OK;
}

/*!
    \brief      send the command of get HID descriptor to the device
    \param[in]  uhost: pointer to USB host
    \param[in]  len: HID descriptor length
    \param[out] none
    \retval     operation status
*/
static usbh_status usbh_hid_desc_get(usbh_host *uhost, uint16_t len)
{
    usbh_status status = USBH_BUSY;

    if(CTL_IDLE == uhost->control.ctl_state) {
        uhost->control.setup.req = (usb_req) {
            .bmRequestType = USB_TRX_IN | USB_RECPTYPE_ITF | USB_REQTYPE_STRD,
            .bRequest      = USB_GET_DESCRIPTOR,
            .wValue        = USBH_DESC(USB_DESCTYPE_HID),
            .wIndex        = 0U,
            .wLength       = len
        };

        usbh_ctlstate_config(uhost, uhost->dev_prop.data, len);
    }

    status = usbh_ctl_handler(uhost);

    return status;
}

/*!
    \brief      set idle state
    \param[in]  uhost: pointer to USB host
    \param[in]  duration: duration for HID set idle request
    \param[in]  report_ID: targeted report ID for HID set idle request
    \param[out] none
    \retval     operation status
*/
static usbh_status usbh_set_idle(usbh_host *uhost, uint8_t duration, uint8_t report_ID)
{
    usbh_status status = USBH_BUSY;

    if(CTL_IDLE == uhost->control.ctl_state) {
        uhost->control.setup.req = (usb_req) {
            .bmRequestType = USB_TRX_OUT | USB_RECPTYPE_ITF | USB_REQTYPE_CLASS,
            .bRequest      = SET_IDLE,
            .wValue        = (duration << 8) | report_ID,
            .wIndex        = 0U,
            .wLength       = 0U
        };

        usbh_ctlstate_config(uhost, NULL, 0U);
    }

    status = usbh_ctl_handler(uhost);

    return status;
}

/*!
    \brief      set protocol state
    \param[in]  uhost: pointer to USB host
    \param[in]  protocol: boot/report protocol
    \param[out] none
    \retval     operation status
*/
static usbh_status usbh_set_protocol(usbh_host *uhost, uint8_t protocol)
{
    usbh_status status = USBH_BUSY;

    if(CTL_IDLE == uhost->control.ctl_state) {
        uhost->control.setup.req = (usb_req) {
            .bmRequestType = USB_TRX_OUT | USB_RECPTYPE_ITF | USB_REQTYPE_CLASS,
            .bRequest      = SET_PROTOCOL,
            .wValue        = !protocol,
            .wIndex        = 0U,
            .wLength       = 0U
        };

        usbh_ctlstate_config(uhost, NULL, 0U);
    }

    status = usbh_ctl_handler(uhost);

    return status;
}

/*!
    \brief      parse the HID descriptor
    \param[in]  hid_desc: pointer to HID descriptor
    \param[in]  buf: pointer to buffer where the source descriptor is available
    \param[out] none
    \retval     none
*/
static void usbh_hiddesc_parse(usb_desc_hid *hid_desc, uint8_t *buf)
{
    hid_desc->header.bLength         = *(uint8_t *)(buf + 0U);
    hid_desc->header.bDescriptorType = *(uint8_t *)(buf + 1U);
    hid_desc->bcdHID                 = BYTE_SWAP(buf + 2U);
    hid_desc->bCountryCode           = *(uint8_t *)(buf + 4U);
    hid_desc->bNumDescriptors        = *(uint8_t *)(buf + 5U);
    hid_desc->bDescriptorType        = *(uint8_t *)(buf + 6U);
    hid_desc->wDescriptorLength      = BYTE_SWAP(buf + 7U);
}
