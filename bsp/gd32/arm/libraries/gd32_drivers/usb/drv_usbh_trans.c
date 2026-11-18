/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#include "drv_usbh_transc.h"

#if defined(BSP_USING_USB) && defined(RT_USING_USB_HOST)

#define USB_SETUP_PACKET_LEN 8U

/*!
    \brief      prepare a pipe and start a transfer
    \param[in]  pudev: pointer to usb core instance
    \param[in]  pp_num: pipe number
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_request_submit(usb_core_driver *pudev, uint8_t pp_num)
{
    pudev->host.pipe[pp_num].urb_state = URB_IDLE;
    pudev->host.pipe[pp_num].xfer_count = 0U;

    return usb_pipe_xfer(pudev, pp_num);
}

/*!
    \brief      send the setup packet to the USB device
    \param[in]  pudev: pointer to usb core instance
    \param[in]  buf: data buffer which will be sent to USB device
    \param[in]  pp_num: pipe number
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_ctlsetup_send(usb_core_driver *pudev, uint8_t *buf, uint8_t pp_num)
{
    usb_pipe *pp = &pudev->host.pipe[pp_num];

    pp->DPID = PIPE_DPID_SETUP;
    pp->xfer_buf = buf;
    pp->xfer_len = USB_SETUP_PACKET_LEN;

    return (usbh_status)usbh_request_submit(pudev, pp_num);
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
usbh_status usbh_data_send(usb_core_driver *pudev, uint8_t *buf, uint8_t pp_num, uint16_t len)
{
    usb_pipe *pp = &pudev->host.pipe[pp_num];

    pp->xfer_buf = buf;
    pp->xfer_len = len;

    switch (pp->ep.type)
    {
    case USB_EPTYPE_CTRL:
        if (0U == len)
        {
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

    usbh_request_submit(pudev, pp_num);

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
usbh_status usbh_data_recev(usb_core_driver *pudev, uint8_t *buf, uint8_t pp_num, uint16_t len)
{
    usb_pipe *pp = &pudev->host.pipe[pp_num];

    pp->xfer_buf = buf;
    pp->xfer_len = len;

    switch (pp->ep.type)
    {
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

    usbh_request_submit(pudev, pp_num);

    return USBH_OK;
}

#endif /* BSP_USING_USB && RT_USING_USB_HOST */
