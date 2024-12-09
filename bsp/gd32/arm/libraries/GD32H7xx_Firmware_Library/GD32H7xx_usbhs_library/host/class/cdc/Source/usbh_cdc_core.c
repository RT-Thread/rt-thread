/*!
    \file    usbh_cdc_core.c
    \brief   USB host CDC class driver

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

#include "usbh_cdc_core.h"
#include <string.h>

#ifdef USB_HS_INTERNAL_DMA_ENABLED
    #if defined ( __ICCARM__ ) /*!< IAR Compiler */
        #pragma data_alignment = 4
    #endif
#endif /* USB_HS_INTERNAL_DMA_ENABLED */

__ALIGN_BEGIN uint8_t tx_buf[CDC_BUFFER_SIZE] __ALIGN_END;

#ifdef USB_HS_INTERNAL_DMA_ENABLED
    #if defined ( __ICCARM__ ) /*!< IAR Compiler */
        #pragma data_alignment = 4
    #endif
#endif /* USB_HS_INTERNAL_DMA_ENABLED */

__ALIGN_BEGIN uint8_t rx_buf[CDC_BUFFER_SIZE] __ALIGN_END;

/* local function prototypes ('static') */
static usbh_status cdc_interface_init (usbh_host *uhost);
static void cdc_interface_deinit (usbh_host *uhost);
static usbh_status cdc_class_request(usbh_host *uhost);
static usbh_status cdc_handle(usbh_host *uhost);
static void cdc_process_transmission(usbh_host *uhost);
static void cdc_process_reception(usbh_host *uhost);
static void cdc_init_txrxparam(usbh_host *uhost);
static void cdc_receive_data(usbh_host *uhost, cdc_xfer *cdc_data);

usbh_class usbh_cdc =
{
    USB_CLASS_CDC,
    cdc_interface_init,
    cdc_interface_deinit,
    cdc_class_request,
    cdc_handle
};

/*!
    \brief      send data to the device
    \param[in]  uhost: pointer to USB host
    \param[in]  data: data pointer
    \param[in]  length: data length
    \param[out] none
    \retval     none
*/
void cdc_data_send (usbh_host *uhost, uint8_t *data, uint16_t length)
{
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    if (cdc->tx_param.cdc_cur_state == CDC_IDLE)
    {
        cdc->tx_param.prxtx_buff = data;
        cdc->tx_param.data_length = length;
        cdc->tx_param.cdc_cur_state = CDC_SEND_DATA;
    }
}

/*!
    \brief      send dummy data to the device
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     none
*/
void cdc_dummydata_send (usbh_host *uhost)
{
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    static uint8_t cdc_send_buf[17] = {0x43, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x76, 0x69, 0x74, 0x79, 0x20, 0x6C, 0x69, 0x6E, 0x65};

    if (cdc->tx_param.cdc_cur_state == CDC_IDLE)
    {
        cdc->tx_param.prxtx_buff = cdc_send_buf;
        cdc->tx_param.data_length = sizeof(cdc_send_buf);
        cdc->tx_param.cdc_cur_state = CDC_SEND_DATA;
    }
}

/*!
    \brief      enable CDC receive
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     none
*/
void cdc_start_reception (usbh_host *uhost)
{
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    cdc->rx_enabled = 1U;
}

/*!
    \brief      stop CDC receive
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     none
*/
void cdc_stop_reception (usbh_host *uhost)
{
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    cdc->rx_enabled = 0U;

    usb_pipe_halt(uhost->data, cdc->data_itf.pipe_in);
    usbh_pipe_free(uhost->data, cdc->data_itf.pipe_in);
}

/*!
    \brief      get currently configured line coding
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
usbh_status cdc_get_line_coding (usbh_host *uhost)
{
    usbh_status status = USBH_BUSY;
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    if (CTL_IDLE == uhost->control.ctl_state)
    {
        usbh_control *usb_ctl = &uhost->control;

        usb_ctl->setup.req = (usb_req)
        {
            .bmRequestType = USB_TRX_IN | USB_RECPTYPE_ITF | USB_REQTYPE_CLASS,
            .bRequest      = GET_LINE_CODING,
            .wValue        = 0U,
            .wIndex        = 0U,
            .wLength       = LINE_CODING_STRUCTURE_SIZE
        };

        usbh_ctlstate_config (uhost, cdc->line_code_get.array, LINE_CODING_STRUCTURE_SIZE);
    }

    status = usbh_ctl_handler (uhost);

    return status;
}

/*!
    \brief      specify typical asynchronous line-character formatting properties
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
usbh_status cdc_set_line_coding (usbh_host *uhost)
{
    usbh_status status = USBH_BUSY;
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    if (CTL_IDLE == uhost->control.ctl_state)
    {
        usbh_control *usb_ctl = &uhost->control;

        usb_ctl->setup.req = (usb_req)
        {
            .bmRequestType = USB_TRX_OUT | USB_RECPTYPE_ITF | USB_REQTYPE_CLASS,
            .bRequest      = SET_LINE_CODING,
            .wValue        = 0U,
            .wIndex        = 0U,
            .wLength       = LINE_CODING_STRUCTURE_SIZE
        };

        usbh_ctlstate_config (uhost, cdc->line_code_set.array, LINE_CODING_STRUCTURE_SIZE);
    }

    status = usbh_ctl_handler (uhost);

    return status;
}

/*!
    \brief      this request generates RS-232/V.24 style control signals
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
usbh_status cdc_set_control_line_state (usbh_host *uhost)
{
    usbh_status status = USBH_BUSY;

    if (CTL_IDLE == uhost->control.ctl_state)
    {
        usbh_control *usb_ctl = &uhost->control;

        usb_ctl->setup.req = (usb_req)
        {
            .bmRequestType = USB_TRX_OUT | USB_RECPTYPE_ITF | USB_REQTYPE_CLASS,
            .bRequest      = SET_CONTROL_LINE_STATE,
            .wValue        = CDC_DEACTIVATE_CARRIER_SIGNAL_RTS | CDC_DEACTIVATE_SIGNAL_DTR,
            .wIndex        = 0U,
            .wLength       = 0U
        };

        usbh_ctlstate_config (uhost, NULL, 0U);
    }

    status = usbh_ctl_handler (uhost);

    return status;
}

/*!
    \brief      this function prepares the state before issuing the class specific commands
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     none
*/
void cdc_change_state_to_issue_setconfig (usbh_host *uhost)
{
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    uhost->backup_state = uhost->cur_state;
    uhost->cur_state = HOST_CLASS_ENUM;

    cdc->req_state = CDC_SET_LINE_CODING_RQUEST;
}

/*!
    \brief      this function prepares the state before issuing the class specific commands
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     none
*/
void cdc_issue_getconfig (usbh_host *uhost)
{
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    uhost->backup_state = uhost->cur_state;
    uhost->cur_state = HOST_CLASS_ENUM;

    cdc->req_state = CDC_GET_LINE_CODING_RQUEST;
}

/*!
    \brief      init the CDC class
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
static usbh_status cdc_interface_init (usbh_host *uhost)
{
    usbh_status status = USBH_OK;

    uint8_t interface = usbh_interface_find(&uhost->dev_prop, USB_CLASS_CDC, USB_CDC_SUBCLASS_ACM, USB_CDC_PROTOCOL_AT);

    if (0xFFU == interface)
    {
        uhost->usr_cb->dev_not_supported();

        status = USBH_FAIL;
    } else {
        usbh_interface_select(&uhost->dev_prop, interface);

        static usbh_cdc_handler cdc_handler;

        memset(&cdc_handler, 0U, sizeof(usbh_cdc_handler));

        uhost->active_class->class_data = (void *)&cdc_handler;

        usb_desc_ep *ep_desc = &uhost->dev_prop.cfg_desc_set.itf_desc_set[interface][0].ep_desc[0];

        /* collect the notification endpoint address and length */
        if (ep_desc->bEndpointAddress & 0x80U)
        {
            cdc_handler.cmd_itf.ep_notify = ep_desc->bEndpointAddress;
            cdc_handler.cmd_itf.ep_size_notify = ep_desc->wMaxPacketSize;
        }

        /* allocate the length for host channel number in */
        cdc_handler.cmd_itf.pipe_notify = usbh_pipe_allocate (uhost->data, cdc_handler.cmd_itf.ep_notify);

        /* open channel for in endpoint */
        usbh_pipe_create (uhost->data,
                          &uhost->dev_prop,
                          cdc_handler.cmd_itf.pipe_notify,
                          USB_EPTYPE_INTR,
                          cdc_handler.cmd_itf.ep_size_notify);

        usbh_pipe_toggle_set(uhost->data, cdc_handler.cmd_itf.pipe_notify, 0U);

        interface = usbh_interface_find(&uhost->dev_prop, USB_CLASS_DATA, USB_CDC_SUBCLASS_RESERVED, USB_CDC_PROTOCOL_NONE);

        ep_desc = &uhost->dev_prop.cfg_desc_set.itf_desc_set[interface][0].ep_desc[0];

        if (ep_desc->bEndpointAddress & 0x80U)
        {
            cdc_handler.data_itf.ep_in = ep_desc->bEndpointAddress;
            cdc_handler.data_itf.ep_size_in = ep_desc->wMaxPacketSize;
        } else {
            cdc_handler.data_itf.ep_out = ep_desc->bEndpointAddress;
            cdc_handler.data_itf.ep_size_out = ep_desc->wMaxPacketSize;
        }

        ep_desc = &uhost->dev_prop.cfg_desc_set.itf_desc_set[interface][0].ep_desc[1];

        if (ep_desc->bEndpointAddress & 0x80U)
        {
            cdc_handler.data_itf.ep_in = ep_desc->bEndpointAddress;
            cdc_handler.data_itf.ep_size_in = ep_desc->wMaxPacketSize;
        } else {
            cdc_handler.data_itf.ep_out = ep_desc->bEndpointAddress;
            cdc_handler.data_itf.ep_size_out = ep_desc->wMaxPacketSize;
        }

        /* allocate the length for host channel number out */
        cdc_handler.data_itf.pipe_out = usbh_pipe_allocate (uhost->data, cdc_handler.data_itf.ep_out);

        /* allocate the length for host channel number in */
        cdc_handler.data_itf.pipe_in = usbh_pipe_allocate (uhost->data, cdc_handler.data_itf.ep_in);

        /* open channel for OUT endpoint */
        usbh_pipe_create (uhost->data,
                          &uhost->dev_prop,
                          cdc_handler.data_itf.pipe_out,
                          USB_EPTYPE_BULK,
                          cdc_handler.data_itf.ep_size_out);

        /* open channel for IN endpoint */
        usbh_pipe_create (uhost->data,
                          &uhost->dev_prop,
                          cdc_handler.data_itf.pipe_in,
                          USB_EPTYPE_BULK,
                          cdc_handler.data_itf.ep_size_in);

        usbh_pipe_toggle_set(uhost->data, cdc_handler.data_itf.ep_out, 0U);
        usbh_pipe_toggle_set(uhost->data, cdc_handler.data_itf.pipe_in, 0U);

        cdc_handler.req_state = CDC_GET_LINE_CODING_RQUEST;

        /* initialize the TX/TX parameters */
        cdc_init_txrxparam(uhost);
    }

    return status;
}

/*!
    \brief      deinit the host channels used for the CDC class
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     none
*/
static void cdc_interface_deinit (usbh_host *uhost)
{
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    /* reset the channel as free */
    if (cdc->cmd_itf.pipe_notify)
    {
        usb_pipe_halt (uhost->data, cdc->cmd_itf.pipe_notify);
        usbh_pipe_free (uhost->data, cdc->cmd_itf.pipe_notify);

        cdc->cmd_itf.pipe_notify = 0U;
    }

    /* reset the channel as free */
    if (cdc->data_itf.pipe_out)
    {
        usb_pipe_halt (uhost->data, cdc->data_itf.pipe_out);
        usbh_pipe_free (uhost->data, cdc->data_itf.pipe_out);

        cdc->data_itf.pipe_out = 0U;
    }

    /* reset the channel as free */
    if (cdc->data_itf.pipe_in)
    {
        usb_pipe_halt (uhost->data, cdc->data_itf.pipe_in);
        usbh_pipe_free (uhost->data, cdc->data_itf.pipe_in);

        cdc->data_itf.pipe_in = 0U;
    }

}

/*!
    \brief      handler CDC class requests
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
static usbh_status cdc_class_request (usbh_host *uhost)
{
    usbh_status status = USBH_BUSY;
    usbh_status class_req_status = USBH_BUSY;
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    switch (cdc->req_state)
    {
    case CDC_GET_LINE_CODING_RQUEST:
        /* issue the get line coding request */
        class_req_status = cdc_get_line_coding(uhost);

        if (USBH_OK == class_req_status)
        {
            cdc->req_state = CDC_SET_CONTROL_LINE_STATE_REQUEST;
        }
        break;

    case CDC_SET_LINE_CODING_RQUEST:
        /* issue the set line coding request */
        class_req_status = cdc_set_line_coding(uhost);

        if (USBH_OK == class_req_status)
        {
            cdc->req_state = CDC_GET_LINE_CODING_RQUEST;
        }

        if (USBH_NOT_SUPPORTED == class_req_status)
        {
            /* a clear feature should be issued here */
            cdc->req_state = CDC_ERROR_STATE;
        }
        break;

    case CDC_SET_CONTROL_LINE_STATE_REQUEST:
        /* issue the set control line coding */
        class_req_status = cdc_set_control_line_state(uhost);

        if (USBH_OK == class_req_status)
        {
            cdc->req_state = CDC_SET_CONTROL_LINE_STATE_REQUEST;

            /* also set the state of receive CDCRxParam to IDLE */
            cdc->rx_param.cdc_cur_state = CDC_IDLE;

            status = USBH_OK; /* this return from class specific routines request*/
        }
        break;

    case CDC_ERROR_STATE:
        class_req_status = usbh_clrfeature(uhost, 0x00U, uhost->control.pipe_out_num);

        if (USBH_OK == class_req_status)
        {
            cdc->req_state = CDC_GET_LINE_CODING_RQUEST;
        }
        break;

    default:
        break;
    }

    return status;
}

/*!
    \brief      managing state machine for CDC data transfers
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
static usbh_status cdc_handle (usbh_host *uhost)
{
    usbh_status status = USBH_OK;

    /* call application process */
    uhost->usr_cb->dev_user_app();

    /* handle the transmission */
    cdc_process_transmission(uhost);

    /* always send in packet to device */
    cdc_process_reception(uhost);

    return status;
}

/*!
    \brief      the function is responsible for sending data to the device
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     none
*/
static void cdc_process_transmission(usbh_host *uhost)
{
    static uint32_t len ;
    usb_urb_state urb_status_tx = URB_IDLE;
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    urb_status_tx = usbh_urbstate_get(uhost->data, cdc->data_itf.pipe_out);

    switch (cdc->tx_param.cdc_cur_state)
    {
    case CDC_IDLE:
        break;

    case CDC_SEND_DATA:
        if ((urb_status_tx == URB_DONE) || (urb_status_tx == URB_IDLE))
        {
            /* check the data length is more then the usbh_cdc_handler.data_itf.length */
            if (cdc->tx_param.data_length > cdc->data_itf.ep_size_out)
            {
                len = cdc->data_itf.ep_size_out;

                /* send the data */
                usbh_data_send (uhost->data,
                                cdc->tx_param.prxtx_buff,
                                cdc->data_itf.pipe_out,
                                len);
            } else {
                len = cdc->tx_param.data_length;

                /* send the remaining data */
                usbh_data_send (uhost->data,
                                cdc->tx_param.prxtx_buff,
                                cdc->data_itf.pipe_out,
                                len);
            }

            cdc->tx_param.cdc_cur_state = CDC_DATA_SENT;
        }
        break;

    case CDC_DATA_SENT:
        /* check the status done for transmission */
        if (urb_status_tx == URB_DONE)
        {
            /* point to next chunk of data */
            cdc->tx_param.prxtx_buff += len;

            /* decrease the data length */
            cdc->tx_param.data_length -= len;

            if (cdc->tx_param.data_length == 0U)
            {
                cdc->tx_param.cdc_cur_state = CDC_IDLE;
            } else {
                cdc->tx_param.cdc_cur_state = CDC_SEND_DATA;
            }
        } else if (urb_status_tx == URB_NOTREADY)
        {
            /* send the same data */
            usbh_data_send (uhost->data,
                            (cdc->tx_param.prxtx_buff),
                            cdc->data_itf.pipe_out,
                            len);
        }
        break;

    default:
        break;
    }
}

/*!
    \brief      the function is responsible for reception of data from the device
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     none
*/
static void cdc_process_reception(usbh_host *uhost)
{
    usb_core_driver *udev = (usb_core_driver *)uhost->data;
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    if (cdc->rx_enabled == 1)
    {
        usb_urb_state urb_status_rx = usbh_urbstate_get(udev, cdc->data_itf.pipe_in);

        switch (cdc->rx_param.cdc_cur_state)
        {
        case CDC_IDLE:
            /* check the received length lesser then the remaining space available in the buffer */
            if (cdc->rx_param.data_length < (cdc->rx_param.buffer_len - cdc->data_itf.ep_size_in))
            {
                /* receive the data */
                usbh_data_recev(udev,
                                cdc->rx_param.pfill_buff,
                                cdc->data_itf.pipe_in,
                                cdc->data_itf.ep_size_in);

                /* change the CDC state to USBH_CDC_GET_DATA*/
                cdc->rx_param.cdc_cur_state = CDC_GET_DATA;
            }
            break;

        case CDC_GET_DATA:
            /* check the last state of the device is URB_DONE */
            if (urb_status_rx == URB_DONE)
            {
                /* move the pointer as well as data length */
                cdc->rx_param.data_length += udev->host.pipe[cdc->data_itf.pipe_in].xfer_count;
                cdc->rx_param.pfill_buff += udev->host.pipe[cdc->data_itf.pipe_in].xfer_count;

                /* Process the received data */
                cdc_receive_data(uhost, &cdc->rx_param);

                /*change the state OD the CDC state*/
                cdc->rx_param.cdc_cur_state = CDC_IDLE;
            }
            break;

        default:
            break;
        }
    }
}

/*!
    \brief      initialize the transmit and receive buffer and its parameter
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     none
*/
static void cdc_init_txrxparam(usbh_host *uhost)
{
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    /* initialize the transmit buffer and its parameter */
    cdc->tx_param.cdc_cur_state = CDC_IDLE;
    cdc->tx_param.data_length = 0U;
    cdc->tx_param.prxtx_buff = tx_buf;

    /* initialize the receive buffer and its parameter */
    cdc->rx_param.cdc_cur_state = CDC_IDLE;
    cdc->rx_param.data_length = 0U;
    cdc->rx_param.pfill_buff = rx_buf;
    cdc->rx_param.pempty_buff = rx_buf;
    cdc->rx_param.buffer_len = sizeof(rx_buf);
}

/*!
    \brief      call back function from CDC core layer to redirect the received data on the user out put system
    \param[in]  uhost: pointer to USB host
    \param[in]  cdc_data: data structure
    \param[out] none
    \retval     none
*/
static void cdc_receive_data(usbh_host *uhost, cdc_xfer *cdc_data)
{
    usbh_cdc_handler *cdc = (usbh_cdc_handler *)uhost->active_class->class_data;

    if (cdc_data->pempty_buff < cdc_data->pfill_buff)
    {
        /* redirect the received data on the user out put system */
        cdc->user_cb.receive(cdc_data->pempty_buff);

        cdc_data->pfill_buff = cdc_data->pempty_buff;

        /* reset the data length to zero */
        cdc_data->data_length = 0U;
    }
}
