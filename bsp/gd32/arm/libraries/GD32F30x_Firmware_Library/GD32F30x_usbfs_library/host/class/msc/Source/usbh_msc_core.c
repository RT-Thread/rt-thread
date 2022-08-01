/*!
    \file    usbh_core.c
    \brief   USB MSC(mass storage device) class driver

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

#include "usbh_msc_core.h"
#include "usbh_msc_scsi.h"
#include "usbh_msc_bbb.h"
#include "usbh_pipe.h"
#include "usbh_transc.h"
#include <stdlib.h>
#include <string.h>

/* local function prototypes ('static') */
static void usbh_msc_itf_deinit         (usbh_host *puhost);
static usbh_status usbh_msc_itf_init    (usbh_host *puhost);
static usbh_status usbh_msc_req         (usbh_host *puhost);
static usbh_status usbh_msc_handle      (usbh_host *puhost);
static usbh_status usbh_msc_maxlun_get  (usbh_host *puhost, uint8_t *maxlun);
static usbh_status usbh_msc_rdwr_process(usbh_host *puhost, uint8_t lun);

usbh_class usbh_msc =
{
    USB_CLASS_MSC,
    usbh_msc_itf_init,
    usbh_msc_itf_deinit,
    usbh_msc_req,
    usbh_msc_handle,
};

/*!
    \brief      interface initialization for MSC class
    \param[in]  puhost: pointer to usb host
    \param[out] none
    \retval     operation status
*/
static usbh_status usbh_msc_itf_init (usbh_host *puhost)
{
    usbh_status status = USBH_OK;

    uint8_t interface = usbh_interface_find(&puhost->dev_prop, MSC_CLASS, USB_MSC_SUBCLASS_SCSI, MSC_PROTOCOL);

    if (0xFFU == interface) {
        puhost->usr_cb->dev_not_supported();

        status = USBH_FAIL;
    } else {
        static usbh_msc_handler msc_handler;

        memset((void*)&msc_handler, 0, sizeof(usbh_msc_handler));

        puhost->active_class->class_data = (void *)&msc_handler;

        usbh_interface_select(&puhost->dev_prop, interface);

        usb_desc_ep *ep_desc = &puhost->dev_prop.cfg_desc_set.itf_desc_set[interface][0].ep_desc[0];

        if (ep_desc->bEndpointAddress & 0x80) {
            msc_handler.ep_in = ep_desc->bEndpointAddress;
            msc_handler.ep_size_in = ep_desc->wMaxPacketSize;
        } else {
            msc_handler.ep_out = ep_desc->bEndpointAddress;
            msc_handler.ep_size_out = ep_desc->wMaxPacketSize;
        }

        ep_desc = &puhost->dev_prop.cfg_desc_set.itf_desc_set[interface][0].ep_desc[1];

        if (ep_desc->bEndpointAddress & 0x80) {
            msc_handler.ep_in = ep_desc->bEndpointAddress;
            msc_handler.ep_size_in = ep_desc->wMaxPacketSize;
        } else {
            msc_handler.ep_out = ep_desc->bEndpointAddress;
            msc_handler.ep_size_out = ep_desc->wMaxPacketSize;
        }

        msc_handler.state = MSC_INIT;
        msc_handler.error = MSC_OK;
        msc_handler.req_state = MSC_REQ_IDLE;
        msc_handler.pipe_out = usbh_pipe_allocate(puhost->data, msc_handler.ep_out);
        msc_handler.pipe_in = usbh_pipe_allocate(puhost->data, msc_handler.ep_in);

        usbh_msc_bot_init(puhost);

        /* open the new channels */
        usbh_pipe_create (puhost->data,
                          &puhost->dev_prop,
                          msc_handler.pipe_out,
                          USB_EPTYPE_BULK,
                          msc_handler.ep_size_out);

        usbh_pipe_create (puhost->data,
                          &puhost->dev_prop,
                          msc_handler.pipe_in,
                          USB_EPTYPE_BULK,
                          msc_handler.ep_size_in);

        usbh_pipe_toggle_set (puhost->data, msc_handler.pipe_out, 0U);
        usbh_pipe_toggle_set (puhost->data, msc_handler.pipe_in, 0U);
    }

    return status;
}

/*!
    \brief      de-initialize interface by freeing host channels allocated to interface
    \param[in]  puhost: pointer to usb host
    \param[out] none
    \retval     operation status
*/
void usbh_msc_itf_deinit (usbh_host *puhost)
{
    usbh_msc_handler *msc = (usbh_msc_handler *)puhost->active_class->class_data;

    if (msc->pipe_out) {
        usb_pipe_halt (puhost->data, msc->pipe_out);
        usbh_pipe_free (puhost->data, msc->pipe_out);

        msc->pipe_out = 0U;
    }

    if (msc->pipe_in) {
        usb_pipe_halt (puhost->data, msc->pipe_in);
        usbh_pipe_free (puhost->data, msc->pipe_in);

        msc->pipe_in = 0U;
    }
}

/*!
    \brief      initialize the MSC state machine
    \param[in]  puhost: pointer to usb host
    \param[out] none
    \retval     operation status
*/
static usbh_status usbh_msc_req (usbh_host *puhost)
{
    usbh_status status = USBH_BUSY;
    usbh_msc_handler *msc = (usbh_msc_handler *)puhost->active_class->class_data;

    switch (msc->req_state) {
    case MSC_REQ_IDLE:
    case MSC_REQ_GET_MAX_LUN:
        /* issue Get_MaxLun request */
        status = usbh_msc_maxlun_get (puhost, (uint8_t *)&msc->max_lun);

        if (USBH_OK == status) {
            msc->max_lun = ((uint8_t)msc->max_lun > MSC_MAX_SUPPORTED_LUN) ? MSC_MAX_SUPPORTED_LUN : (uint8_t)msc->max_lun + 1U;

            for (uint8_t i = 0U; i < msc->max_lun; i++) {
                msc->unit[i].prev_ready_state = USBH_FAIL;
                msc->unit[i].state_changed = 0U;
            }
        } else {
            if (USBH_NOT_SUPPORTED == status) {
                msc->max_lun = 0U;
                status = USBH_OK;
            }
        }
        break;

    case MSC_REQ_ERROR:
        /* issue clear feature request */
        if (USBH_OK == usbh_clrfeature(puhost, 0x00U, puhost->control.pipe_out_num)) {
            msc->req_state = msc->prev_req_state;
        }
        break;

    default:
        break;
    }

    return status;
}

/*!
    \brief      MSC state machine handler
    \param[in]  puhost: pointer to usb host
    \param[out] none
    \retval     operation status
*/
static usbh_status usbh_msc_handle (usbh_host *puhost)
{
    usbh_status status = USBH_BUSY;
    uint8_t scsi_status = USBH_BUSY;
    uint8_t ready_status = USBH_BUSY;
    usbh_msc_handler *msc = (usbh_msc_handler *)puhost->active_class->class_data;


    switch (msc->state) {
    case MSC_INIT:
        if (msc->cur_lun < msc->max_lun) {
            msc->unit[msc->cur_lun].error = MSC_NOT_READY;

            switch (msc->unit[msc->cur_lun].state) {
            case MSC_INIT:
                msc->unit[msc->cur_lun].state = MSC_READ_INQUIRY;
                msc->timer = puhost->control.timer;
                break;

            case MSC_READ_INQUIRY:
                scsi_status = usbh_msc_scsi_inquiry(puhost, msc->cur_lun, &msc->unit[msc->cur_lun].inquiry);

                if (USBH_OK == scsi_status) {
                    msc->unit[msc->cur_lun].state = MSC_TEST_UNIT_READY;
                } else if (scsi_status == USBH_FAIL) {
                    msc->unit[msc->cur_lun].state = MSC_REQUEST_SENSE;
                } else {
                    if (scsi_status == USBH_UNRECOVERED_ERROR) {
                        msc->unit[msc->cur_lun].state = MSC_IDLE;
                        msc->unit[msc->cur_lun].error = MSC_ERROR;
                    }
                }
                break;

            case MSC_TEST_UNIT_READY:
                /* issue SCSI command TestUnitReady */
                ready_status = usbh_msc_test_unitready(puhost, msc->cur_lun);

                if (USBH_OK == ready_status) {
                    if (USBH_OK != msc->unit[msc->cur_lun].prev_ready_state) {
                        msc->unit[msc->cur_lun].state_changed = 1U;
                    } else {
                        msc->unit[msc->cur_lun].state_changed = 0U;
                    }

                    msc->unit[msc->cur_lun].state = MSC_READ_CAPACITY10;
                    msc->unit[msc->cur_lun].error = MSC_OK;
                    msc->unit[msc->cur_lun].prev_ready_state = USBH_OK;
                } else if (USBH_FAIL == ready_status) {
                    if (USBH_FAIL != msc->unit[msc->cur_lun].prev_ready_state) {
                        msc->unit[msc->cur_lun].state_changed = 1U;
                    } else {
                        msc->unit[msc->cur_lun].state_changed = 0U;
                    }

                    msc->unit[msc->cur_lun].state = MSC_REQUEST_SENSE;
                    msc->unit[msc->cur_lun].error = MSC_NOT_READY;
                    msc->unit[msc->cur_lun].prev_ready_state = USBH_FAIL;
                } else {
                    if (USBH_UNRECOVERED_ERROR == ready_status) {
                        msc->unit[msc->cur_lun].state = MSC_IDLE;
                        msc->unit[msc->cur_lun].error = MSC_ERROR;
                    }
                }
                break;

            case MSC_READ_CAPACITY10:
                /* issue READ_CAPACITY10 SCSI command */
                scsi_status = usbh_msc_read_capacity10(puhost, msc->cur_lun, &msc->unit[msc->cur_lun].capacity);

                if (USBH_OK == scsi_status) {
                    if (1U == msc->unit[msc->cur_lun].state_changed) {
                    }
                    msc->unit[msc->cur_lun].state = MSC_IDLE;
                    msc->unit[msc->cur_lun].error = MSC_OK;
                    msc->cur_lun ++;
                } else if (USBH_FAIL == scsi_status) {
                    msc->unit[msc->cur_lun].state = MSC_REQUEST_SENSE;
                } else {
                    if (USBH_UNRECOVERED_ERROR == scsi_status) {
                        msc->unit[msc->cur_lun].state = MSC_IDLE;
                        msc->unit[msc->cur_lun].error = MSC_ERROR;
                    }
                }
                break;

            case MSC_REQUEST_SENSE:
                /* issue RequestSense SCSI command for recovering error code */
                scsi_status = usbh_msc_request_sense (puhost, msc->cur_lun, &msc->unit[msc->cur_lun].sense);
                if (USBH_OK == scsi_status) {
                    if ((msc->unit[msc->cur_lun].sense.SenseKey == UNIT_ATTENTION) || (msc->unit[msc->cur_lun].sense.SenseKey == NOT_READY)) {
                        if (((puhost->control.timer > msc->timer) && ((puhost->control.timer - msc->timer) < 10000U)) \
                              || ((puhost->control.timer < msc->timer) && ((puhost->control.timer + 0x3FFFU - msc->timer) < 10000U))){
                            msc->unit[msc->cur_lun].state = MSC_TEST_UNIT_READY;
                            break;
                        }
                    }

                    msc->unit[msc->cur_lun].state = MSC_IDLE;
                    msc->cur_lun++;
                } else if (USBH_FAIL == scsi_status) {
                    msc->unit[msc->cur_lun].state = MSC_UNRECOVERED_ERROR;
                } else {
                    if (MSC_UNRECOVERED_ERROR == scsi_status) {
                        msc->unit[msc->cur_lun].state = MSC_IDLE;
                        msc->unit[msc->cur_lun].error = MSC_ERROR;
                    }
                }
                break;

            case MSC_UNRECOVERED_ERROR:
                msc->cur_lun ++;
                break;

            default:
                break;
            }
        } else {
            msc->cur_lun = 0U;
            msc->state = MSC_IDLE;
        }
        break;

    case MSC_IDLE:
        puhost->usr_cb->dev_user_app();
        status = USBH_OK;
        break;

    default:
        break;
    }

    return status;
}

/*!
    \brief      get max lun of the mass storage device
    \param[in]  puhost: pointer to USB host
    \param[in]  maxlun: pointer to max lun
    \param[out] none
    \retval     operation status
*/
static usbh_status usbh_msc_maxlun_get (usbh_host *puhost, uint8_t *maxlun)
{
    usbh_status status = USBH_BUSY;

    if (puhost->control.ctl_state == CTL_IDLE) {
        puhost->control.setup.req = (usb_req) {
            .bmRequestType = USB_TRX_IN | USB_REQTYPE_CLASS | USB_RECPTYPE_ITF,
            .bRequest      = BBB_GET_MAX_LUN,
            .wValue        = 0U,
            .wIndex        = 0U,
            .wLength       = 1U
        };

        usbh_ctlstate_config (puhost, maxlun, 1U);
    }

    status = usbh_ctl_handler (puhost);

    return status;
}

/*!
    \brief      get max lun of the mass storage device
    \param[in]  puhost: pointer to USB host
    \param[in]  lun: logic unit number
    \param[out] none
    \retval     operation status
*/
static usbh_status usbh_msc_rdwr_process(usbh_host *puhost, uint8_t lun)
{
    usbh_status error = USBH_BUSY;
    usbh_status scsi_status = USBH_BUSY;
    usbh_msc_handler *msc = (usbh_msc_handler *)puhost->active_class->class_data;

    /* switch msc req state machine */
    switch (msc->unit[lun].state) {
    case MSC_READ:
        scsi_status = usbh_msc_read10(puhost, lun,  NULL, 0U, 0U);

        if (USBH_OK == scsi_status) {
            msc->unit[lun].state = MSC_IDLE;
            error = USBH_OK;
        } else if (USBH_FAIL == scsi_status) {
            msc->unit[lun].state = MSC_REQUEST_SENSE;
        } else {
            if (USBH_UNRECOVERED_ERROR == scsi_status) {
                msc->unit[lun].state = MSC_UNRECOVERED_ERROR;
                error = USBH_FAIL;
            }
        }
        break;

    case MSC_WRITE:
        scsi_status = usbh_msc_write10(puhost, lun, NULL, 0U, 0U);

        if (USBH_OK == scsi_status) {
            msc->unit[lun].state = MSC_IDLE;
            error = USBH_OK;
        } else if(USBH_FAIL == scsi_status) {
            msc->unit[lun].state = MSC_REQUEST_SENSE;
        } else {
            if (USBH_UNRECOVERED_ERROR == scsi_status) {
                msc->unit[lun].state = MSC_UNRECOVERED_ERROR;
                error = USBH_FAIL;
            }
        }
        break;

    case MSC_REQUEST_SENSE:
        scsi_status = usbh_msc_request_sense (puhost, lun, &msc->unit[lun].sense);

        if (USBH_OK == scsi_status) {
            msc->unit[lun].state = MSC_IDLE;
            msc->unit[lun].error = MSC_ERROR;

            error = USBH_FAIL;
        }

        if (USBH_FAIL == scsi_status) {
        } else {
            if (USBH_UNRECOVERED_ERROR == scsi_status) {
                msc->unit[lun].state = MSC_UNRECOVERED_ERROR;
                error = USBH_FAIL;
            }
        }
        break;

    default:
        break;
    }

    return error;
}

/*!
    \brief      get lun information
    \param[in]  puhost: pointer to USB host
    \param[in]  lun: logic unit number
    \param[in]  info: pointer to lun information
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_msc_lun_info_get (usbh_host *puhost, uint8_t lun, msc_lun *info)
{
    usbh_msc_handler *msc = (usbh_msc_handler *)puhost->active_class->class_data;

    if (HOST_CLASS_HANDLER == puhost->cur_state) {
        memcpy(info, &msc->unit[lun], sizeof(msc_lun));

        return USBH_OK;
    } else {
        return USBH_FAIL;
    }
}

/*!
    \brief      handle msc read operation
    \param[in]  puhost: pointer to USB host
    \param[in]  lun: logic unit number
    \param[in]  address: data address
    \param[in]  pbuf: pointer to data buffer
    \param[in]  length: buffer length
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_msc_read (usbh_host *puhost,
                           uint8_t lun,
                           uint32_t address,
                           uint8_t *pbuf,
                           uint32_t length)
{
    uint32_t timeout = 0U;
    usbh_msc_handler *msc = (usbh_msc_handler *)puhost->active_class->class_data;
    usb_core_driver *pudev = (usb_core_driver *)puhost->data;

    if ((0U == pudev->host.connect_status) ||
        (HOST_CLASS_HANDLER != puhost->cur_state) ||
        (MSC_IDLE != msc->unit[lun].state)) {
        return USBH_FAIL;
    }

    msc->state = MSC_READ;
    msc->unit[lun].state = MSC_READ;
    msc->rw_lun = lun;

    usbh_msc_read10(puhost, lun, pbuf, address, length);

    timeout = puhost->control.timer;

    while (USBH_BUSY == usbh_msc_rdwr_process(puhost, lun)) {
        if (((puhost->control.timer > timeout) && ((puhost->control.timer - timeout) > (1000U * length))) \
              || ((puhost->control.timer < timeout) && ((puhost->control.timer + 0x3FFFU - timeout) > (1000U * length))) \
              || (0U == pudev->host.connect_status)){
            msc->state = MSC_IDLE;
            return USBH_FAIL;
        }
    }

    msc->state = MSC_IDLE;

    return USBH_OK;
}

/*!
    \brief      handle msc write operation
    \param[in]  puhost: pointer to USB host
    \param[in]  lun: logic unit number
    \param[in]  address: data address
    \param[in]  pbuf: pointer to data buffer
    \param[in]  length: buffer length
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_msc_write (usbh_host *puhost,
                            uint8_t lun,
                            uint32_t address,
                            uint8_t *pbuf,
                            uint32_t length)
{
    uint32_t timeout = 0U;
    usb_core_driver *pudev = (usb_core_driver *)puhost->data;
    usbh_msc_handler *msc = (usbh_msc_handler *)puhost->active_class->class_data;

    if ((0U == pudev->host.connect_status) ||
        (HOST_CLASS_HANDLER != puhost->cur_state) ||
        (MSC_IDLE != msc->unit[lun].state)) {
        return USBH_FAIL;
    }

    msc->state = MSC_WRITE;
    msc->unit[lun].state = MSC_WRITE;
    msc->rw_lun = lun;

    usbh_msc_write10(puhost, lun, pbuf, address, length);

    timeout = puhost->control.timer;

    while (USBH_BUSY == usbh_msc_rdwr_process(puhost, lun)) {
        if (((puhost->control.timer > timeout) && ((puhost->control.timer - timeout) > (1000U * length))) \
              || ((puhost->control.timer < timeout) && ((puhost->control.timer + 0x3FFFU - timeout) > (1000U * length))) \
              || (0U == pudev->host.connect_status)){
            msc->state = MSC_IDLE;
            return USBH_FAIL;
        }
    }

    msc->state = MSC_IDLE;

    return USBH_OK;
}
