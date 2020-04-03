/*!
    \file  usbh_transc.c
    \brief USB host mode transactions driver

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

#include "drv_usb_hw.h"
#include "usbh_transc.h"

/*!
    \brief      prepare a pipe and start a transfer
    \param[in]  pudev: pointer to usb core instance
    \param[in]  pp_num: pipe number
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_request_submit (usb_core_driver *pudev, uint8_t pp_num) 
{
    pudev->host.pipe[pp_num].urb_state = URB_IDLE;
    pudev->host.pipe[pp_num].xfer_count = 0U;

    return usb_pipe_xfer (pudev, pp_num);
}

/*!
    \brief      send the setup packet to the USB device
    \param[in]  pudev: pointer to usb core instance
    \param[in]  buf: data buffer which will be sent to USB device
    \param[in]  pp_num: pipe number
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_ctlsetup_send (usb_core_driver *pudev, uint8_t *buf, uint8_t pp_num)
{
    usb_pipe *pp = &pudev->host.pipe[pp_num];

    pp->DPID = PIPE_DPID_SETUP;
    pp->xfer_buf = buf;
    pp->xfer_len = USB_SETUP_PACKET_LEN;

    return (usbh_status)usbh_request_submit (pudev, pp_num);
}

/*!
    \brief      send a data packet to the USB device
    \param[in]  pudev: pointer to usb core instance
    \param[in]  buf: data buffer which will be sent to USB device
    \param[in]  pp_num: pipe number
    \param[in]  len: length of the data to be sent
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_data_send (usb_core_driver *pudev, uint8_t *buf, uint8_t pp_num, uint16_t len)
{
    usb_pipe *pp = &pudev->host.pipe[pp_num];

    pp->xfer_buf = buf;
    pp->xfer_len = len;

    switch (pp->ep.type) {
    case USB_EPTYPE_CTRL:
        if (0U == len) {
            pp->data_toggle_out = 1U;
        }

        pp->DPID = PIPE_DPID[pp->data_toggle_out];
        break;

    case USB_EPTYPE_INTR:
        pp->DPID = PIPE_DPID[pp->data_toggle_out];

        pp->data_toggle_out ^= 1U;
        break;

    case USB_EPTYPE_BULK:
        pp->DPID = PIPE_DPID[pp->data_toggle_out];
        break;

    case USB_EPTYPE_ISOC:
        pp->DPID = PIPE_DPID[0];
        break;

    default:
        break;
    }

    usbh_request_submit (pudev, pp_num);

    return USBH_OK;
}

/*!
    \brief      receive a data packet from the USB device
    \param[in]  pudev: pointer to usb core instance
    \param[in]  buf: data buffer which will be received from USB device
    \param[in]  pp_num: pipe number
    \param[in]  len: length of the data to be received
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_data_recev (usb_core_driver *pudev, uint8_t *buf, uint8_t pp_num, uint16_t len)
{
    usb_pipe *pp = &pudev->host.pipe[pp_num];

    pp->xfer_buf = buf;
    pp->xfer_len = len;

    switch (pp->ep.type) {
    case USB_EPTYPE_CTRL:
        pp->DPID = PIPE_DPID[1];
        break;

    case USB_EPTYPE_INTR:
        pp->DPID = PIPE_DPID[pp->data_toggle_in];

        /* Toggle DATA PID */
        pp->data_toggle_in ^= 1U;
        break;

    case USB_EPTYPE_BULK:
        pp->DPID = PIPE_DPID[pp->data_toggle_in];
        break;

    case USB_EPTYPE_ISOC:
        pp->DPID = PIPE_DPID[0];
        break;

    default:
        break;
    }

    usbh_request_submit (pudev, pp_num);

    return USBH_OK;
}

/*!
    \brief      wait for USB URB(USB request block) state
    \param[in]  pudev: pointer to USB core instance
    \param[in]  puhost: pointer to USB host
    \param[in]  pp_num: pipe number
    \param[in]  wait_time: wait time
    \param[out] none
    \retval     USB URB state
*/
static usb_urb_state usbh_urb_wait (usb_core_driver *pudev, usbh_host *puhost, uint8_t pp_num, uint32_t wait_time)
{
    usb_urb_state urb_status = URB_IDLE;

    while (URB_DONE != (urb_status = usbh_urbstate_get(pudev, pp_num))) {
        if (URB_NOTREADY == urb_status) {
            break;
        } else if (URB_STALL == urb_status) {
            puhost->control.ctl_state = CTL_SETUP;
            break;
        } else if (URB_ERROR == urb_status) {
            puhost->control.ctl_state = CTL_ERROR;
            break;
        } else if ((wait_time > 0U) && \
                    ((usb_curframe_get(pudev)- puhost->control.timer) > wait_time)) {
            /* timeout for in transfer */
            puhost->control.ctl_state = CTL_ERROR;
            break;
        } else {
            /* no operation, just wait */
        }
    }

    return urb_status;
}

/*!
    \brief      USB setup transaction
    \param[in]  pudev: pointer to USB core instance
    \param[in]  puhost: pointer to USB host
    \param[out] none
    \retval     none
*/
static void usbh_setup_transc (usb_core_driver *pudev, usbh_host *puhost)
{
    usb_urb_state urb_status = URB_IDLE;

    /* send a SETUP packet */
    usbh_ctlsetup_send (pudev, 
                        puhost->control.setup.data, 
                        puhost->control.pipe_out_num);

    urb_status = usbh_urb_wait (pudev, puhost, puhost->control.pipe_out_num, 0U);

    if (URB_DONE == urb_status) {
        uint8_t dir = (puhost->control.setup.req.bmRequestType & USB_TRX_MASK);

        if (puhost->control.setup.req.wLength) {
            if (USB_TRX_IN == dir) {
                puhost->control.ctl_state = CTL_DATA_IN;
            } else {
                puhost->control.ctl_state = CTL_DATA_OUT;
            }
        } else {
            if (USB_TRX_IN == dir) {
                puhost->control.ctl_state = CTL_STATUS_OUT;
            } else {
                puhost->control.ctl_state = CTL_STATUS_IN;
            }
        }

        /* set the delay timer to enable timeout for data stage completion */
        puhost->control.timer = usb_curframe_get(pudev);
    }
}

/*!
    \brief      USB data IN transaction
    \param[in]  pudev: pointer to USB core instance
    \param[in]  puhost: pointer to USB host
    \param[out] none
    \retval     none
*/
static void usbh_data_in_transc (usb_core_driver *pudev, usbh_host *puhost)
{
    usb_urb_state urb_status = URB_IDLE;

    usbh_data_recev (pudev,
                     puhost->control.buf,
                     puhost->control.pipe_in_num,
                     puhost->control.ctl_len);

    urb_status = usbh_urb_wait (pudev, puhost, puhost->control.pipe_in_num, DATA_STAGE_TIMEOUT);

    if (URB_DONE == urb_status) {
        puhost->control.ctl_state = CTL_STATUS_OUT;

        puhost->control.timer = usb_curframe_get(pudev);
    }
}

/*!
    \brief      USB data OUT transaction
    \param[in]  pudev: pointer to USB core instance
    \param[in]  puhost: pointer to USB host
    \param[out] none
    \retval     none
*/
static void usbh_data_out_transc (usb_core_driver *pudev, usbh_host *puhost)
{
    usb_urb_state urb_status = URB_IDLE;

    pudev->host.pipe[puhost->control.pipe_out_num].data_toggle_out = 1U; 

    usbh_data_send (pudev,
                    puhost->control.buf,
                    puhost->control.pipe_out_num,
                    puhost->control.ctl_len);

    urb_status = usbh_urb_wait (pudev, puhost, puhost->control.pipe_out_num, DATA_STAGE_TIMEOUT);

    if (URB_DONE == urb_status) {
        puhost->control.ctl_state = CTL_STATUS_IN;

        puhost->control.timer = usb_curframe_get(pudev);
    }
}

/*!
    \brief      USB status IN transaction
    \param[in]  pudev: pointer to USB core instance
    \param[in]  puhost: pointer to USB host
    \param[out] none
    \retval     none
*/
static void usbh_status_in_transc (usb_core_driver *pudev, usbh_host *puhost)
{
    uint8_t pp_num = puhost->control.pipe_in_num;

    usb_urb_state urb_status = URB_IDLE;

    usbh_data_recev (pudev, NULL, pp_num, 0U);

    urb_status = usbh_urb_wait (pudev, puhost, pp_num, NODATA_STAGE_TIMEOUT);

    if (URB_DONE == urb_status) {
        puhost->control.ctl_state = CTL_FINISH;
    }
}

/*!
    \brief      USB status OUT transaction
    \param[in]  pudev: pointer to USB core instance
    \param[in]  puhost: pointer to USB host
    \param[out] none
    \retval     none
*/
static void usbh_status_out_transc (usb_core_driver *pudev, usbh_host *puhost)
{
    uint8_t pp_num = puhost->control.pipe_out_num;

    usb_urb_state urb_status = URB_IDLE;

    pudev->host.pipe[pp_num].data_toggle_out ^= 1U;

    usbh_data_send (pudev, NULL, pp_num, 0U);

    urb_status = usbh_urb_wait (pudev, puhost, pp_num, NODATA_STAGE_TIMEOUT);

    if (URB_DONE == urb_status) {
        puhost->control.ctl_state = CTL_FINISH;
    }
}

/*!
    \brief      USB control transfer handler
    \param[in]  pudev: pointer to USB core instance
    \param[in]  puhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_ctl_handler (usb_core_driver *pudev, usbh_host *puhost)
{
    usbh_status status = USBH_BUSY;

    switch (puhost->control.ctl_state) {
    case CTL_SETUP:
        usbh_setup_transc (pudev, puhost);
        break;

    case CTL_DATA_IN:
        usbh_data_in_transc (pudev, puhost);
        break;

    case CTL_DATA_OUT:
        usbh_data_out_transc (pudev, puhost);
        break;

    case CTL_STATUS_IN:
        usbh_status_in_transc (pudev, puhost);
        break;

    case CTL_STATUS_OUT:
        usbh_status_out_transc (pudev, puhost);
        break;

    case CTL_FINISH:
        puhost->control.ctl_state = CTL_IDLE;

        status = USBH_OK;
        break;

    case CTL_ERROR:
        if (++puhost->control.error_count <= USBH_MAX_ERROR_COUNT) {
            /* do the transmission again, starting from SETUP packet */
            puhost->control.ctl_state = CTL_SETUP;
        } else {
            status = USBH_FAIL;
        }
        break;

    default:
        break;
    }

    return status;
}

