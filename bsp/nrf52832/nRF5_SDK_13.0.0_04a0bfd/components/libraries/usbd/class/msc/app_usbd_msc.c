/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#include "sdk_config.h"
#if APP_USBD_CLASS_MSC_ENABLED
#include <string.h>
#include <ctype.h>

#include "app_usbd.h"
#include "sdk_common.h"
#include "app_usbd_msc.h"
#include "app_usbd_string_desc.h"

/**
 * @defgroup app_usbd_msc_internal USBD MSC internals
 * @{
 * @ingroup app_usbd_msc
 * @internal
 */

STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_requestsense_t) == 6);
STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_requestsense_resp_t) == 18);
STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_inquiry_t) == 6);
STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_inquiry_resp_t) == 36);
STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_read6_t) == 6);
STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_write6_t) == 6);
STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_modesense6_t) == 6);
STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_modesense6_resp_t) == 4);
STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_readcapacity10_t) == 10);
STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_readcapacity10_resp_t) == 8);
STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_read10_t) == 10);
STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_write10_t) == 10);
STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_modesense10_t) == 10);
STATIC_ASSERT(sizeof(app_usbd_scsi_cmd_modesense10_resp_t) == 8);

STATIC_ASSERT(sizeof(app_usbd_msc_cbw_t) == 31);
STATIC_ASSERT(sizeof(app_usbd_msc_csw_t) == 13);

#define NRF_LOG_MODULE_NAME "USBD MSC"
#if APP_USBD_MSC_CLASS_LOG_ENABLED
#else //APP_USBD_MSC_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif //APP_USBD_MSC_CONFIG_LOG_ENABLED
#include "nrf_log.h"

#define APP_USBD_MSC_IFACE_IDX 0    /**< Mass storage class interface index */
#define APP_USBD_MSC_EPIN_IDX  0    /**< Mass storage class endpoint IN index */
#define APP_USBD_MSC_EPOUT_IDX 1    /**< Mass storage class endpoint OUT index */

/**
 * @brief Set request buffer busy flag
 *
 * @param[in] val   Bitmask to set
 * @param[in] id    Buffer id
 * */
#define APP_USBD_MSC_REQ_BUSY_SET(val, id) SET_BIT(val, id)

/**
 * @brief Clear request buffer busy flag
 *
 * @param[in] val   Bitmask to set
 * @param[in] id    Buffer id
 * */
#define APP_USBD_MSC_REQ_BUSY_CLR(val, id) CLR_BIT(val, id)

#define APP_USBD_MSC_REQ_BUSY_FULL_MASK (0x03)  /**< Request busy mask */

static void msc_blockdev_ev_handler(nrf_block_dev_t const * p_blk_dev,
                                    nrf_block_dev_event_t const * p_event);

/**
 * @brief Auxiliary function to access MSC instance data
 *
 * @param[in] p_inst Class instance data
 *
 * @return MSC instance data @ref app_usbd_msc_t
 */
static inline app_usbd_msc_t const * msc_get(app_usbd_class_inst_t const * p_inst)
{
    ASSERT(p_inst != NULL);
    return (app_usbd_msc_t const *)p_inst;
}

/**
 * @brief Auxiliary function to access MSC context data
 *
 * @param[in] p_msc    MSC instance data
 * @return MSC context data @ref app_usbd_msc_ctx_t
 */
static inline app_usbd_msc_ctx_t * msc_ctx_get(app_usbd_msc_t const * p_msc)
{
    ASSERT(p_msc != NULL);
    ASSERT(p_msc->specific.p_data != NULL);
    return &p_msc->specific.p_data->ctx;
}

/**
 * @brief Auxiliary function to access MSC IN endpoint address
 *
 * @param[in] p_inst Class instance data
 *
 * @return IN endpoint address
 */
static inline nrf_drv_usbd_ep_t ep_in_addr_get(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_class_iface_conf_t const * class_iface;
    class_iface = app_usbd_class_iface_get(p_inst, APP_USBD_MSC_IFACE_IDX);

    app_usbd_class_ep_conf_t const * ep_cfg;
    ep_cfg = app_usbd_class_iface_ep_get(class_iface, APP_USBD_MSC_EPIN_IDX);

    return app_usbd_class_ep_address_get(ep_cfg);
}

/**
 * @brief Auxiliary function to access MSC OUT endpoint address
 *
 * @param[in] p_inst Class instance data
 *
 * @return OUT endpoint address
 */
static inline nrf_drv_usbd_ep_t ep_out_addr_get(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_class_iface_conf_t const * class_iface;
    class_iface = app_usbd_class_iface_get(p_inst, APP_USBD_MSC_IFACE_IDX);

    app_usbd_class_ep_conf_t const * ep_cfg;
    ep_cfg = app_usbd_class_iface_ep_get(class_iface, APP_USBD_MSC_EPOUT_IDX);

    return app_usbd_class_ep_address_get(ep_cfg);
}

/**
 * @brief Command Block Wrapper trigger
 *
 * @param[in] p_inst    Generic class instance
 * @param[in] state     Next state transition
 *
 * @return Standard error code
 * */
static ret_code_t cbw_wait_start(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_msc_t const * p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *   p_msc_ctx = msc_ctx_get(p_msc);

    nrf_drv_usbd_ep_t ep_addr_out = ep_out_addr_get(p_inst);

    NRF_LOG_DEBUG("cbw_wait_start\r\n");
    memset(&p_msc_ctx->cbw, 0, sizeof(app_usbd_msc_cbw_t));
    NRF_DRV_USBD_TRANSFER_OUT(cbw, &p_msc_ctx->cbw, sizeof(app_usbd_msc_cbw_t));
    ret_code_t ret = app_usbd_core_ep_transfer(ep_addr_out, &cbw);
    if (ret == NRF_SUCCESS)
    {
        p_msc_ctx->state = APP_USBD_MSC_STATE_CBW;
    }

    return ret;
}

/**
 * @brief Command Status Wrapper trigger
 *
 * @param[in] p_inst    Generic class instance
 * @param[in] state     Next state transition
 *
 * @return Standard error code
 * */
static ret_code_t csw_wait_start(app_usbd_class_inst_t const * p_inst, uint8_t status)
{
    app_usbd_msc_t const * p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *   p_msc_ctx = msc_ctx_get(p_msc);

    nrf_drv_usbd_ep_t ep_addr_in = ep_in_addr_get(p_inst);

    memset(&p_msc_ctx->csw, 0, sizeof(app_usbd_msc_csw_t));
    memcpy(p_msc_ctx->csw.signature, APP_USBD_MSC_CSW_SIGNATURE, sizeof(p_msc_ctx->csw.signature));
    memcpy(p_msc_ctx->csw.tag, p_msc_ctx->cbw.tag, sizeof(p_msc_ctx->csw.tag));
    memcpy(p_msc_ctx->csw.residue, &p_msc_ctx->current.residue, sizeof(uint32_t));
    p_msc_ctx->csw.status = status;

    NRF_DRV_USBD_TRANSFER_IN(csw, &p_msc_ctx->csw, sizeof(app_usbd_msc_csw_t));
    ret_code_t ret = app_usbd_core_ep_transfer(ep_addr_in, &csw);
    if (ret == NRF_SUCCESS)
    {
        p_msc_ctx->state = APP_USBD_MSC_STATE_CSW;
    }

    return ret;
}

/**
 * @brief IN transfer trigger
 *
 * @param[in] p_inst    Generic class instance
 * @param[in] p_buff    IN transfer data buffer
 * @param[in] size      IN transfer size
 * @param[in] state     Next state transition
 *
 * @return Standard error code
 * */
static ret_code_t transfer_in_start(app_usbd_class_inst_t const * p_inst,
                                    void const *                  p_buff,
                                    size_t                        size,
                                    app_usbd_msc_state_t          state)
{
    app_usbd_msc_t const * p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *   p_msc_ctx = msc_ctx_get(p_msc);

    NRF_LOG_DEBUG("transfer_in_start: p_buff: %p, size: %u\r\n", (uint32_t)p_buff, size);

    nrf_drv_usbd_ep_t ep_addr_in = ep_in_addr_get(p_inst);

    NRF_DRV_USBD_TRANSFER_IN(resp, p_buff, size);
    ret_code_t ret = app_usbd_core_ep_transfer(ep_addr_in, &resp);
    if (ret == NRF_SUCCESS)
    {
        p_msc_ctx->state = state;
    }
    return ret;
}

/**
 * @brief MSC reset request handler @ref  APP_USBD_MSC_REQ_BULK_RESET
 *
 * @param[in] p_inst    Generic class instance
 *
 * */
static void bulk_ep_reset(app_usbd_class_inst_t const * p_inst)
{
    nrf_drv_usbd_ep_t ep_addr_in  = ep_in_addr_get(p_inst);
    nrf_drv_usbd_ep_t ep_addr_out = ep_out_addr_get(p_inst);

    usbd_drv_ep_abort(ep_addr_in);
    usbd_drv_ep_abort(ep_addr_out);
}


/**
 * @brief OUT transfer trigger
 *
 * @param[in] p_inst    Generic class instance
 * @param[in] p_buff    OUT transfer data buffer
 * @param[in] size      OUT transfer size
 * @param[in] state     Next state transition
 *
 * @return Standard error code
 * */
static ret_code_t transfer_out_start(app_usbd_class_inst_t const * p_inst,
                                     void *                        p_buff,
                                     size_t                        size,
                                     app_usbd_msc_state_t          state)
{
    app_usbd_msc_t const * p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *   p_msc_ctx = msc_ctx_get(p_msc);

    NRF_LOG_DEBUG("transfer_out_start: p_buff: %p, size: %u\r\n", (uint32_t)p_buff, size);
    nrf_drv_usbd_ep_t ep_addr_out = ep_out_addr_get(p_inst);

    NRF_DRV_USBD_TRANSFER_OUT(resp, p_buff, size);
    ret_code_t ret = app_usbd_core_ep_transfer(ep_addr_out, &resp);
    if (ret == NRF_SUCCESS)
    {
        p_msc_ctx->state = state;
    }
    return ret;
}

/**
 * @brief Start status stage of unsupported SCSI command
 *
 * @param[in] p_inst    Generic class instance
 *
 * @return Standard error code
 * */
static ret_code_t unsupported_start(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_msc_t const * p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *   p_msc_ctx = msc_ctx_get(p_msc);

    if (p_msc_ctx->cbw.flags & APP_USBD_MSC_CBW_DIRECTION_IN)
    {
        return transfer_in_start(p_inst, NULL, 0, APP_USBD_MSC_STATE_UNSUPPORTED);
    }

    p_msc_ctx->state = APP_USBD_MSC_STATE_UNSUPPORTED;
    return NRF_ERROR_NOT_SUPPORTED;
}



/**
 * @brief Internal SETUP standard IN request handler
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_setup_ev    Setup event
 *
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t setup_req_std_in(app_usbd_class_inst_t const * p_inst,
                                   app_usbd_setup_evt_t const *  p_setup_ev)
{
    /*Only Get Descriptor standard IN request is supported by MSC class*/
    if (p_setup_ev->setup.bmRequest != APP_USBD_SETUP_STDREQ_GET_DESCRIPTOR)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    size_t dsc_len = 0;

    /* Try to find descriptor in class internals*/
    void const * p_dsc = app_usbd_class_descriptor_find(p_inst,
                                                        p_setup_ev->setup.wValue.hb,
                                                        p_setup_ev->setup.wValue.lb,
                                                        &dsc_len);
    if (p_dsc != NULL)
    {
        return app_usbd_core_setup_rsp(&(p_setup_ev->setup), p_dsc, dsc_len);
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Internal SETUP standard OUT request handler
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_setup_ev    Setup event
 *
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t setup_req_std_out(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_setup_evt_t const *  p_setup_ev)
{
    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Internal SETUP class IN request handler
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_setup_ev    Setup event
 *
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t setup_req_class_in(app_usbd_class_inst_t const * p_inst,
                                     app_usbd_setup_evt_t const *  p_setup_ev)
{
    app_usbd_msc_t const * p_msc = msc_get(p_inst);

    switch (p_setup_ev->setup.bmRequest)
    {
        case APP_USBD_MSC_REQ_GET_MAX_LUN:
        {

            if (p_setup_ev->setup.wValue.w != 0)
            {
                break;
            }

            if (p_setup_ev->setup.wLength.w != 1)
            {
                break;
            }

            size_t tx_size;
            uint16_t * p_tx_buff = app_usbd_core_setup_transfer_buff_get(&tx_size);
            ASSERT(p_msc->specific.inst.block_devs_count != 0);
            p_tx_buff[0] = p_msc->specific.inst.block_devs_count - 1;

            ret_code_t ret = cbw_wait_start(p_inst);
            UNUSED_VARIABLE(ret);
            return app_usbd_core_setup_rsp(&(p_setup_ev->setup), p_tx_buff, sizeof(uint8_t));
        }
        default:
            break;

    }

    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Internal SETUP class OUT request handler
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_setup_ev    Setup event
 *
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t setup_req_class_out(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_setup_evt_t const *  p_setup_ev)
{
    app_usbd_msc_t const * p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *   p_msc_ctx = msc_ctx_get(p_msc);

    switch (p_setup_ev->setup.bmRequest)
    {
        case APP_USBD_MSC_REQ_BULK_RESET:
        {
            if (p_setup_ev->setup.wValue.w != 0)
            {
                break;
            }

            if (p_setup_ev->setup.wLength.w != 0)
            {
                break;
            }

            /*
             * Reset internal state to be ready for next CBW
             */
            NRF_LOG_DEBUG("bulk ep reset\r\n");
            bulk_ep_reset(p_inst);

            if (p_msc_ctx->state == APP_USBD_MSC_STATE_DISABLED)
            {
                ret_code_t ret = cbw_wait_start(p_inst);
                UNUSED_VARIABLE(ret);
            }

            return NRF_SUCCESS;
        }
        default:
            break;
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Control endpoint handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_setup_ev    Setup event
 *
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t setup_event_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_setup_evt_t const *  p_setup_ev)
{
    ASSERT(p_inst != NULL);
    ASSERT(p_setup_ev != NULL);
    app_usbd_msc_t const * p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *   p_msc_ctx = msc_ctx_get(p_msc);

    app_usbd_setup_reqrec_t  req_rec = app_usbd_setup_req_rec(p_setup_ev->setup.bmRequestType);
    app_usbd_setup_reqtype_t req_type = app_usbd_setup_req_typ(p_setup_ev->setup.bmRequestType);
    if (req_rec == APP_USBD_SETUP_REQREC_ENDPOINT &&
        req_type == APP_USBD_SETUP_REQTYPE_STD)
    {

        ret_code_t ret = app_usbd_endpoint_std_req_handle(p_setup_ev);
        if (ret != NRF_SUCCESS)
        {
            return ret;
        }

        if ((p_setup_ev->setup.bmRequest == APP_USBD_SETUP_STDREQ_CLEAR_FEATURE) &&
            (p_msc_ctx->state == APP_USBD_MSC_STATE_UNSUPPORTED))
        {
            /*Unsupported command handle: status stage*/
            ret = csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_FAIL);
        }

        return ret;
    }

    if (app_usbd_setup_req_dir(p_setup_ev->setup.bmRequestType) == APP_USBD_SETUP_REQDIR_IN)
    {
        switch (app_usbd_setup_req_typ(p_setup_ev->setup.bmRequestType))
        {
            case APP_USBD_SETUP_REQTYPE_STD:
                return setup_req_std_in(p_inst, p_setup_ev);
            case APP_USBD_SETUP_REQTYPE_CLASS:
                return setup_req_class_in(p_inst, p_setup_ev);
            default:
                break;
        }
    }
    else /*APP_USBD_SETUP_REQDIR_OUT*/
    {
        switch (app_usbd_setup_req_typ(p_setup_ev->setup.bmRequestType))
        {
            case APP_USBD_SETUP_REQTYPE_STD:
                return setup_req_std_out(p_inst, p_setup_ev);
            case APP_USBD_SETUP_REQTYPE_CLASS:
                return setup_req_class_out(p_inst, p_setup_ev);
            default:
                break;
        }
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Handle read6/read10 command data stage
 *
 * @param[in] p_inst        Generic class instance
 *
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t state_data_in_handle(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_msc_t const * p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *   p_msc_ctx = msc_ctx_get(p_msc);

    ret_code_t ret = NRF_SUCCESS;

    p_msc_ctx->current.trans_in_progress = false;
    APP_USBD_MSC_REQ_BUSY_CLR(p_msc_ctx->current.req_busy_mask, p_msc_ctx->current.trans_req_id);

    if (p_msc_ctx->current.blk_datasize == 0 && p_msc_ctx->current.req_busy_mask == 0)
    {
        p_msc_ctx->current.blk_idx = p_msc_ctx->current.blk_size = 0;
        ret = csw_wait_start(p_inst, p_msc_ctx->current.csw_status);
        return ret;
    }

    ASSERT(p_msc_ctx->current.blk_size != 0);

    if (p_msc_ctx->current.req_busy_mask == 0)
    {
        nrf_block_dev_t const * p_blkd =
                                p_msc->specific.inst.pp_block_devs[p_msc_ctx->current.lun];

        /*Trigger new block read request*/
        p_msc_ctx->current.workbuff_pos ^= p_msc->specific.inst.block_buff_size;
        uint32_t req_pos = p_msc_ctx->current.workbuff_pos != 0 ? 1 : 0;
        APP_USBD_MSC_REQ_BUSY_SET(p_msc_ctx->current.req_busy_mask, req_pos);

        NRF_BLOCK_DEV_REQUEST(req,
                              p_msc_ctx->current.blk_idx,
                              p_msc_ctx->current.blk_count,
                              ((uint8_t *)p_msc->specific.inst.p_block_buff +
                              p_msc_ctx->current.workbuff_pos));

        NRF_LOG_DEBUG("nrf_blk_dev_read_req 3: id: %u, count: %u, left: %u, ptr: %p\r\n",
                      req.blk_id,
                      req.blk_count,
                      p_msc_ctx->current.blk_datasize,
                      (uint32_t)req.p_buff);

        ret = nrf_blk_dev_read_req(p_blkd, &req);
        NRF_LOG_DEBUG("nrf_blk_dev_read_req 3: ret: %u\r\n", ret);
        return ret;
    }

    uint32_t blk_size = p_msc_ctx->current.blk_size;
    p_msc_ctx->current.trans_req_id ^= 1;

    nrf_block_req_t * p_req = &p_msc_ctx->current.req;
    if (p_req->p_buff == NULL)
    {
        p_msc_ctx->current.trans_req_id ^= 1;
        return NRF_SUCCESS;
    }

    ret = transfer_in_start(p_inst,
                            p_req->p_buff,
                            p_req->blk_count * blk_size,
                            APP_USBD_MSC_STATE_DATA_IN);

    if (ret == NRF_SUCCESS)
    {
        /*Clear processed block request.*/
        memset(p_req, 0, sizeof(nrf_block_req_t));
        p_msc_ctx->current.trans_in_progress = true;
    }

    return ret;
}

/**
 * @brief Endpoint IN event handler
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_setup_ev    Setup event
 *
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t endpoint_in_event_handler(app_usbd_class_inst_t const *  p_inst,
                                            app_usbd_complex_evt_t const * p_event)
{
    app_usbd_msc_t const * p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *   p_msc_ctx = msc_ctx_get(p_msc);

    NRF_LOG_DEBUG("state: %d, ep in event, status: %d\r\n",
                  p_msc_ctx->state,
                  p_event->drv_evt.data.eptransfer.status);

    if (p_event->drv_evt.data.eptransfer.status != NRF_USBD_EP_OK)
    {
        return NRF_SUCCESS;
    }

    ret_code_t ret = NRF_SUCCESS;
    switch (p_msc_ctx->state) {
        case APP_USBD_MSC_STATE_CMD_IN:
        {
            ret = csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
            break;
        }
        case APP_USBD_MSC_STATE_DATA_IN:
        {
            CRITICAL_REGION_ENTER();
            ret = state_data_in_handle(p_inst);
            CRITICAL_REGION_EXIT();

            break;
        }
        case APP_USBD_MSC_STATE_CSW:
        {
            break;
        }
        case APP_USBD_MSC_STATE_DATA_OUT:
        {
            break;
        }
        case APP_USBD_MSC_STATE_UNSUPPORTED:
        {
            ret = NRF_ERROR_NOT_SUPPORTED;
            break;
        }
        default:
        {
            ret = NRF_ERROR_INTERNAL;
            break;
        }
    }

    return ret;
}


/**
 * @brief Helper function to calculate next block transfer block count
 *
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 *
 * @return Blocks to transfer
 * */
static uint32_t next_transfer_blkcnt_calc(app_usbd_msc_t const * p_msc,
                                          app_usbd_msc_ctx_t *   p_msc_ctx)
{
    uint32_t blkcnt = p_msc->specific.inst.block_buff_size / p_msc_ctx->current.blk_size;
    if (blkcnt > (p_msc_ctx->current.blk_datasize / p_msc_ctx->current.blk_size))
    {
        blkcnt = p_msc_ctx->current.blk_datasize / p_msc_ctx->current.blk_size;
    }

    return blkcnt;
}

/**
 * @brief Helper function to calculate next transfer size
 *
 * @param[in] p_msc_ctx     MSC context
 *
 * @return Blocks to transfer
 * */
static uint32_t next_transfer_size_calc(app_usbd_msc_ctx_t * p_msc_ctx)
{
    uint32_t blk_cnt = p_msc_ctx->current.blk_count;
    uint32_t blk_size = p_msc_ctx->current.blk_size;

    return p_msc_ctx->current.blk_datasize > blk_size * blk_cnt ?
           blk_size * blk_cnt : p_msc_ctx->current.blk_datasize;
}

/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_TESTUNITREADY handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_testunitready(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_msc_t const *        p_msc,
                                    app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: TESTUNITREADY\r\n");
    if (uint32_decode(p_msc_ctx->cbw.datlen) != 0)
    {
        return unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.cdb_length != APP_USBD_SCSI_CMD_TESTUNITREADY_LEN)
    {
        return unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.lun >= p_msc->specific.inst.block_devs_count)
    {
        return unsupported_start(p_inst);
    }

    return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
}

/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_REQUESTSENSE handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_requestsense(app_usbd_class_inst_t const * p_inst,
                                   app_usbd_msc_t const *        p_msc,
                                   app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: REQUESTSENSE\r\n");
    app_usbd_scsi_cmd_requestsense_t const * p_reqs =  (const void *)p_msc_ctx->cbw.cdb;
    UNUSED_VARIABLE(p_reqs);

    if ((p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_requestsense_t)))
    {
        return unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.lun >= p_msc->specific.inst.block_devs_count)
    {
        return unsupported_start(p_inst);
    }

    p_msc_ctx->resp_len = uint32_decode(p_msc_ctx->cbw.datlen);
    p_msc_ctx->resp_len = MIN(p_msc_ctx->resp_len,
                              sizeof(app_usbd_scsi_cmd_requestsense_resp_t));

    if (p_msc_ctx->resp_len == 0)
    {
        return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
    }

    memset(&p_msc_ctx->scsi_resp, 0, sizeof(app_usbd_scsi_cmd_requestsense_resp_t));
    p_msc_ctx->scsi_resp.requestsense.code = APP_USBD_SCSI_CMD_REQSENSE_CODE_VALID |
                                             APP_USBD_SCSI_CMD_REQSENSE_CODE_CURRENT;

    p_msc_ctx->scsi_resp.requestsense.len = sizeof(app_usbd_scsi_cmd_requestsense_resp_t) -
                                            offsetof(app_usbd_scsi_cmd_requestsense_resp_t, len);

    return transfer_in_start(p_inst,
                             &p_msc_ctx->scsi_resp,
                             p_msc_ctx->resp_len,
                             APP_USBD_MSC_STATE_CMD_IN);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_FORMAT_UNIT handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_formatunit(app_usbd_class_inst_t const * p_inst,
                                 app_usbd_msc_t const *        p_msc,
                                 app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: FORMAT_UNIT\r\n");
    return unsupported_start(p_inst);
}

static ret_code_t cmd_read_start(app_usbd_class_inst_t const * p_inst,
                                 app_usbd_msc_t const *        p_msc,
                                 app_usbd_msc_ctx_t *          p_msc_ctx)
{
    nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];

    p_msc_ctx->current.trans_in_progress = false;
    p_msc_ctx->current.req_busy_mask = 0;
    p_msc_ctx->current.workbuff_pos = 0;

    APP_USBD_MSC_REQ_BUSY_SET(p_msc_ctx->current.req_busy_mask, 0);
    NRF_BLOCK_DEV_REQUEST(req,
                          p_msc_ctx->current.blk_idx,
                          p_msc_ctx->current.blk_count,
                          ((uint8_t *)p_msc->specific.inst.p_block_buff +
                          p_msc_ctx->current.workbuff_pos));

    NRF_LOG_DEBUG("cmd_read_start\r\n");
    NRF_LOG_DEBUG("nrf_blk_dev_read_req 1: id: %u, count: %u, left: %u, ptr: %p\r\n",
                  req.blk_id,
                  req.blk_count,
                  p_msc_ctx->current.blk_datasize,
                  (uint32_t)req.p_buff);

    ret_code_t ret = nrf_blk_dev_read_req(p_blkd, &req);
    NRF_LOG_DEBUG("nrf_blk_dev_read_req 1: ret: %u\r\n", ret);

    return ret;
}

/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_READ6 handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_read6(app_usbd_class_inst_t const * p_inst,
                            app_usbd_msc_t const *        p_msc,
                            app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: READ6\r\n");
    app_usbd_scsi_cmd_read6_t const * p_read6 = (const void *)p_msc_ctx->cbw.cdb;
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_read6_t))
    {
        return unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.lun >= p_msc->specific.inst.block_devs_count)
    {
        return unsupported_start(p_inst);
    }

    nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];

    p_msc_ctx->current.lun = p_msc_ctx->cbw.lun;
    p_msc_ctx->current.blk_idx = ((p_read6->mslba & 0x1F) << 16) |
                                   uint16_big_decode(p_read6->lslba);
    p_msc_ctx->current.blk_datasize = uint32_decode(p_msc_ctx->cbw.datlen);
    p_msc_ctx->current.blk_size = nrf_blk_dev_geometry(p_blkd)->blk_size;
    p_msc_ctx->current.blk_count = next_transfer_blkcnt_calc(p_msc, p_msc_ctx);

    if (p_msc_ctx->current.blk_datasize > p_msc_ctx->current.blk_size * p_read6->xfrlen)
    {
        p_msc_ctx->current.residue = p_msc_ctx->current.blk_datasize -
                                     p_msc_ctx->current.blk_size * p_read6->xfrlen;
    }

    return cmd_read_start(p_inst, p_msc, p_msc_ctx);
}

static ret_code_t cmd_write_start(app_usbd_class_inst_t const * p_inst,
                                  app_usbd_msc_t const *        p_msc,
                                  app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("cmd_write_start\r\n");
    ret_code_t ret = transfer_out_start(p_inst,
                                        ((uint8_t *)p_msc->specific.inst.p_block_buff +
                                        p_msc_ctx->current.workbuff_pos),
                                        next_transfer_size_calc(p_msc_ctx),
                                        APP_USBD_MSC_STATE_DATA_OUT);

    if (ret == NRF_SUCCESS)
    {
        p_msc_ctx->current.trans_req_id = 0;
        APP_USBD_MSC_REQ_BUSY_SET(p_msc_ctx->current.req_busy_mask,
                                  p_msc_ctx->current.trans_req_id);
        p_msc_ctx->current.workbuff_pos ^= p_msc->specific.inst.block_buff_size;
        p_msc_ctx->current.trans_in_progress = true;
    }

    return ret;
}

/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_WRITE6 handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_write6(app_usbd_class_inst_t const * p_inst,
                             app_usbd_msc_t const *        p_msc,
                             app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: WRITE6\r\n");
    app_usbd_scsi_cmd_write6_t const * p_write6 = (const void *)p_msc_ctx->cbw.cdb;
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_write6_t))
    {
        return unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.lun >= p_msc->specific.inst.block_devs_count)
    {
        return unsupported_start(p_inst);
    }

    nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];

    p_msc_ctx->current.lun = p_msc_ctx->cbw.lun;
    p_msc_ctx->current.blk_idx = (p_write6->mslba & 0x1F << 16) |
                                  uint16_big_decode(p_write6->lslba);
    p_msc_ctx->current.blk_datasize = uint32_decode(p_msc_ctx->cbw.datlen);
    p_msc_ctx->current.blk_size = nrf_blk_dev_geometry(p_blkd)->blk_size;
    p_msc_ctx->current.blk_count = next_transfer_blkcnt_calc(p_msc, p_msc_ctx);

    if (p_msc_ctx->current.blk_datasize > p_msc_ctx->current.blk_size * p_write6->xfrlen)
    {
        p_msc_ctx->current.residue = p_msc_ctx->current.blk_datasize -
                                     p_msc_ctx->current.blk_size * p_write6->xfrlen;
    }

    return cmd_write_start(p_inst, p_msc, p_msc_ctx);
}

/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_INQUIRY handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_inquiry(app_usbd_class_inst_t const * p_inst,
                              app_usbd_msc_t const *        p_msc,
                              app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: INQUIRY\r\n");
    app_usbd_scsi_cmd_inquiry_t const * p_inq =  (const void *)p_msc_ctx->cbw.cdb;
    if (p_inq->pagecode != 0)
    {
        return unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.lun >= p_msc->specific.inst.block_devs_count)
    {
        return unsupported_start(p_inst);
    }

    p_msc_ctx->resp_len = uint32_decode(p_msc_ctx->cbw.datlen);
    p_msc_ctx->resp_len = MIN(p_msc_ctx->resp_len,
                              sizeof(app_usbd_scsi_cmd_inquiry_resp_t));

    if (p_msc_ctx->resp_len == 0)
    {
        return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
    }


    p_msc_ctx->scsi_resp.inquiry.qualtype = APP_USBD_MSC_SCSI_INQ_QUAL_CONNECTED |
                                            APP_USBD_MSC_SCSI_INQ_TYPE_DIR_ACCESS;
    p_msc_ctx->scsi_resp.inquiry.flags1   = APP_USBD_MSC_SCSI_INQ_FLAG1_RMB;
    p_msc_ctx->scsi_resp.inquiry.version  = APP_USBD_SCSI_INQ_VER_SPC4;
    p_msc_ctx->scsi_resp.inquiry.flags2   = APP_USBD_MSC_SCSI_INQ_FLAG2_RSP_SPC2 |
                                            APP_USBD_MSC_SCSI_INQ_FLAG2_HISUP;
    p_msc_ctx->scsi_resp.inquiry.len      = sizeof(app_usbd_scsi_cmd_inquiry_resp_t) -
                                            offsetof(app_usbd_scsi_cmd_inquiry_resp_t, len);

    nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];
    nrf_block_dev_info_strings_t * p_strings = NULL;
    UNUSED_RETURN_VALUE(nrf_blk_dev_ioctl(p_blkd,
                        NRF_BLOCK_DEV_IOCTL_REQ_INFO_STRINGS,
                        &p_strings));

    if (p_strings)
    {
        UNUSED_RETURN_VALUE(strncpy((char *)p_msc_ctx->scsi_resp.inquiry.vendorid,
                            p_strings->p_vendor,
                            sizeof(p_msc_ctx->scsi_resp.inquiry.vendorid)));

        UNUSED_RETURN_VALUE(strncpy((char *)p_msc_ctx->scsi_resp.inquiry.productid,
                            p_strings->p_product,
                            sizeof(p_msc_ctx->scsi_resp.inquiry.productid)));

        UNUSED_RETURN_VALUE(strncpy((char *)p_msc_ctx->scsi_resp.inquiry.revision,
                            p_strings->p_revision,
                            sizeof(p_msc_ctx->scsi_resp.inquiry.revision)));
    }
    else {
        memset(p_msc_ctx->scsi_resp.inquiry.vendorid,
               0,
               sizeof(p_msc_ctx->scsi_resp.inquiry.vendorid));
        memset(p_msc_ctx->scsi_resp.inquiry.productid,
               0,
               sizeof(p_msc_ctx->scsi_resp.inquiry.productid));
        memset(p_msc_ctx->scsi_resp.inquiry.revision,
               0,
               sizeof(p_msc_ctx->scsi_resp.inquiry.revision));
    }

    return transfer_in_start(p_inst,
                             &p_msc_ctx->scsi_resp,
                             p_msc_ctx->resp_len,
                             APP_USBD_MSC_STATE_CMD_IN);
}

/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_MODESELECT6 handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_modeselect6(app_usbd_class_inst_t const * p_inst,
                                  app_usbd_msc_t const *        p_msc,
                                  app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: MODESELECT6\r\n");
    return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_MODESENSE6 handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_modesense6(app_usbd_class_inst_t const * p_inst,
                                 app_usbd_msc_t const *        p_msc,
                                 app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: MODESENSE6\r\n");
    app_usbd_scsi_cmd_modesense6_t const * p_sense6 = (const void *)p_msc_ctx->cbw.cdb;
    UNUSED_VARIABLE(p_sense6);
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_modesense6_t))
    {
        return unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.lun >= p_msc->specific.inst.block_devs_count)
    {
        return unsupported_start(p_inst);
    }

    p_msc_ctx->resp_len = uint32_decode(p_msc_ctx->cbw.datlen);
    p_msc_ctx->resp_len = MIN(p_msc_ctx->resp_len,
                              sizeof(app_usbd_scsi_cmd_modesense6_resp_t));

    app_usbd_scsi_cmd_modesense6_resp_t * p_resp = &p_msc_ctx->scsi_resp.modesense6;
    p_resp->mdlen = sizeof(app_usbd_scsi_cmd_modesense6_resp_t) - 1;
    p_resp->type = 0;
    p_resp->param = 0;
    p_resp->bdlen = 0;

    return transfer_in_start(p_inst,
                             &p_msc_ctx->scsi_resp,
                             p_msc_ctx->resp_len,
                             APP_USBD_MSC_STATE_CMD_IN);
}

/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_STARTSTOPUNIT handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_startstopunit(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_msc_t const *        p_msc,
                                    app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: STARTSTOPUNIT\r\n");
    return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_SENDDIAGNOSTIC handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_senddiagnostic(app_usbd_class_inst_t const * p_inst,
                                     app_usbd_msc_t const *        p_msc,
                                     app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: SENDDIAGNOSTIC\r\n");
    return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
}

/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_PREVENTMEDIAREMOVAL handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_preventremoval(app_usbd_class_inst_t const * p_inst,
                                     app_usbd_msc_t const *        p_msc,
                                     app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: PREVENTMEDIAREMOVAL\r\n");
    return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
}

/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_READCAPACITY10 handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_readcapacity10(app_usbd_class_inst_t const * p_inst,
                                     app_usbd_msc_t const *        p_msc,
                                     app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: READCAPACITY10\r\n");

    app_usbd_scsi_cmd_readcapacity10_t const * p_cap10 = (const void *)p_msc_ctx->cbw.cdb;
    UNUSED_VARIABLE(p_cap10);
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_readcapacity10_t))
    {
        return unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.lun >= p_msc->specific.inst.block_devs_count)
    {
        return unsupported_start(p_inst);
    }

    p_msc_ctx->resp_len = uint32_decode(p_msc_ctx->cbw.datlen);
    p_msc_ctx->resp_len = MIN(p_msc_ctx->resp_len,
                              sizeof(app_usbd_scsi_cmd_readcapacity10_resp_t));

    if (p_msc_ctx->resp_len == 0)
    {
        return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
    }

    nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];
    nrf_block_dev_geometry_t const * p_geometry = nrf_blk_dev_geometry(p_blkd);

    (void)uint32_big_encode(p_geometry->blk_count - 1, p_msc_ctx->scsi_resp.readcapacity10.lba);
    (void)uint32_big_encode(p_geometry->blk_size, p_msc_ctx->scsi_resp.readcapacity10.blklen);

    return transfer_in_start(p_inst,
                             &p_msc_ctx->scsi_resp,
                             p_msc_ctx->resp_len,
                             APP_USBD_MSC_STATE_CMD_IN);
}

/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_READ10 handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_read10(app_usbd_class_inst_t const * p_inst,
                             app_usbd_msc_t const *        p_msc,
                             app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: READ10\r\n");
    app_usbd_scsi_cmd_read10_t const * p_read10 = (const void *)p_msc_ctx->cbw.cdb;
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_read10_t))
    {
        return unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.lun >= p_msc->specific.inst.block_devs_count)
    {
        return unsupported_start(p_inst);
    }

    if (uint32_decode(p_msc_ctx->cbw.datlen) == 0)
    {
        return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_FAIL);
    }

    if ((p_msc_ctx->cbw.flags & APP_USBD_MSC_CBW_DIRECTION_IN) == 0)
    {
        return unsupported_start(p_inst);
    }

    nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];

    p_msc_ctx->current.lun = p_msc_ctx->cbw.lun;
    p_msc_ctx->current.blk_idx = uint32_big_decode(p_read10->lba);
    p_msc_ctx->current.blk_datasize = uint32_decode(p_msc_ctx->cbw.datlen);
    p_msc_ctx->current.blk_size = nrf_blk_dev_geometry(p_blkd)->blk_size;
    p_msc_ctx->current.blk_count = next_transfer_blkcnt_calc(p_msc, p_msc_ctx);

    uint16_t blocks = uint16_big_decode(p_read10->xfrlen);
    p_msc_ctx->current.csw_status =
            uint32_decode(p_msc_ctx->cbw.datlen) < p_msc_ctx->current.blk_size * blocks ?
            APP_USBD_MSC_CSW_STATUS_FAIL : APP_USBD_MSC_CSW_STATUS_PASS;

    if (p_msc_ctx->current.blk_datasize > p_msc_ctx->current.blk_size * blocks)
    {
        p_msc_ctx->current.residue = p_msc_ctx->current.blk_datasize -
                                     p_msc_ctx->current.blk_size * blocks;
    }

    return cmd_read_start(p_inst, p_msc, p_msc_ctx);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_WRITE10 handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_write10(app_usbd_class_inst_t const * p_inst,
                              app_usbd_msc_t const *        p_msc,
                              app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: WRITE10\r\n");
    app_usbd_scsi_cmd_write10_t const * p_write10 = (const void *)p_msc_ctx->cbw.cdb;
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_write10_t))
    {
        return unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.lun >= p_msc->specific.inst.block_devs_count)
    {
        return unsupported_start(p_inst);
    }

    if (uint32_decode(p_msc_ctx->cbw.datlen) == 0)
    {
        return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_FAIL);
    }


    if ((p_msc_ctx->cbw.flags & APP_USBD_MSC_CBW_DIRECTION_IN) != 0)
    {
        return unsupported_start(p_inst);
    }

    nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];

    p_msc_ctx->current.lun = p_msc_ctx->cbw.lun;
    p_msc_ctx->current.blk_idx = uint32_big_decode(p_write10->lba);
    p_msc_ctx->current.blk_datasize = uint32_decode(p_msc_ctx->cbw.datlen);
    p_msc_ctx->current.blk_size = nrf_blk_dev_geometry(p_blkd)->blk_size;
    p_msc_ctx->current.blk_count = next_transfer_blkcnt_calc(p_msc, p_msc_ctx);

    uint16_t blocks = uint16_big_decode(p_write10->xfrlen);
    p_msc_ctx->current.csw_status =
            uint32_decode(p_msc_ctx->cbw.datlen) < p_msc_ctx->current.blk_size * blocks ?
            APP_USBD_MSC_CSW_STATUS_FAIL : APP_USBD_MSC_CSW_STATUS_PASS;

    if (p_msc_ctx->current.blk_datasize > p_msc_ctx->current.blk_size * blocks)
    {
        p_msc_ctx->current.residue = p_msc_ctx->current.blk_datasize -
                                     p_msc_ctx->current.blk_size * blocks;
    }

    return cmd_write_start(p_inst, p_msc, p_msc_ctx);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_MODESELECT10 handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_modeselect10(app_usbd_class_inst_t const * p_inst,
                                   app_usbd_msc_t const *        p_msc,
                                   app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: MODESELECT10\r\n");
    return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
}

/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_MODESENSE10 handle
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_msc         MSC instance
 * @param[in] p_msc_ctx     MSC context
 * @return Standard error code
 * */
static ret_code_t cmd_modesense10(app_usbd_class_inst_t const * p_inst,
                                  app_usbd_msc_t const *        p_msc,
                                  app_usbd_msc_ctx_t *          p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: MODESENSE10\r\n");
    app_usbd_scsi_cmd_modesense10_t const * p_sense10 = (const void *)p_msc_ctx->cbw.cdb;
    UNUSED_VARIABLE(p_sense10);
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_modesense10_t))
    {
        return unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.lun >= p_msc->specific.inst.block_devs_count)
    {
        return unsupported_start(p_inst);
    }

    p_msc_ctx->resp_len = uint32_decode(p_msc_ctx->cbw.datlen);
    p_msc_ctx->resp_len = MIN(p_msc_ctx->resp_len,
                              sizeof(app_usbd_scsi_cmd_modesense6_resp_t));

    app_usbd_scsi_cmd_modesense10_resp_t * p_resp = &p_msc_ctx->scsi_resp.modesense10;

    memset(p_resp, 0, sizeof(app_usbd_scsi_cmd_modesense10_resp_t));
    uint16_t len = sizeof(app_usbd_scsi_cmd_modesense10_resp_t) - sizeof(p_resp->mdlen);
    p_resp->mdlen[1] = len & 0xff;
    p_resp->mdlen[0] = (len >> 8) & 0xff;

    return transfer_in_start(p_inst,
                             &p_msc_ctx->scsi_resp,
                             p_msc_ctx->resp_len,
                             APP_USBD_MSC_STATE_CMD_IN);
}


/**
 * @brief SCSI Command Block Wrapper handler
 *
 * @param[in] p_inst    Generic class instance
 * @return Standard error code
 * */
static ret_code_t state_cbw(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_msc_t const * p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *   p_msc_ctx = msc_ctx_get(p_msc);

    memset(&p_msc_ctx->current, 0, sizeof(p_msc_ctx->current));

    /*Verify CBW signature*/
    if (memcmp(p_msc_ctx->cbw.signature,
               APP_USBD_MSC_CBW_SIGNATURE,
               sizeof(p_msc_ctx->cbw.signature)) != 0)
    {
        NRF_LOG_DEBUG("CMD: header error: 0x%02x%02x%02x%02x\r\n",
                                p_msc_ctx->cbw.signature[0], p_msc_ctx->cbw.signature[1],
                                p_msc_ctx->cbw.signature[2], p_msc_ctx->cbw.signature[3]);

        return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
    }

    ret_code_t ret = NRF_SUCCESS;
    switch (p_msc_ctx->cbw.cdb[0])
    {
        case APP_USBD_SCSI_CMD_TESTUNITREADY:
            ret = cmd_testunitready(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_REQUESTSENSE:
            ret = cmd_requestsense(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_FORMAT_UNIT:
            ret = cmd_formatunit(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_READ6:
            ret = cmd_read6(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_WRITE6:
            ret = cmd_write6(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_INQUIRY:
            ret = cmd_inquiry(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_MODESELECT6:
            ret = cmd_modeselect6(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_MODESENSE6:
            ret = cmd_modesense6(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_STARTSTOPUNIT:
            ret = cmd_startstopunit(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_SENDDIAGNOSTIC:
            ret = cmd_senddiagnostic(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_PREVENTMEDIAREMOVAL:
            ret = cmd_preventremoval(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_READCAPACITY10:
            ret = cmd_readcapacity10(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_READ10:
            ret = cmd_read10(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_WRITE10:
            ret = cmd_write10(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_MODESELECT10:
            ret = cmd_modeselect10(p_inst, p_msc, p_msc_ctx);
            break;
        case APP_USBD_SCSI_CMD_MODESENSE10:
            ret = cmd_modesense10(p_inst, p_msc, p_msc_ctx);
            break;
        default:
            NRF_LOG_DEBUG("CMD: UNSUPPORTED\r\n");
            if (uint32_decode(p_msc_ctx->cbw.datlen) != 0)
            {
                ret = unsupported_start(p_inst);
            }
            else
            {
                ret = csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_FAIL);
            }
            break;
    }

    return ret;
}


/**
 * @brief Handle write6/write10 command data stage
 *
 * @param[in] p_inst        Generic class instance
 *
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t state_data_out_handle(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_msc_t const * p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *   p_msc_ctx = msc_ctx_get(p_msc);

    ret_code_t ret = NRF_SUCCESS;
    uint32_t   blk_size = p_msc_ctx->current.blk_size;

    NRF_LOG_DEBUG("APP_USBD_MSC_STATE_DATA_OUT\r\n");

    p_msc_ctx->current.trans_in_progress = false;
    if ((p_msc_ctx->current.req_busy_mask != APP_USBD_MSC_REQ_BUSY_FULL_MASK) &&
        (p_msc_ctx->current.blk_datasize > p_msc_ctx->current.blk_count * blk_size))
    {
        size_t size = p_msc_ctx->current.blk_datasize - p_msc_ctx->current.blk_count * blk_size;
        if (size > p_msc_ctx->current.blk_count * blk_size)
        {
            size = p_msc_ctx->current.blk_count * blk_size;
        }

        if (size)
        {
            ret = transfer_out_start(p_inst,
                                     ((uint8_t *)p_msc->specific.inst.p_block_buff +
                                     p_msc_ctx->current.workbuff_pos),
                                     size,
                                     APP_USBD_MSC_STATE_DATA_OUT);
            if (ret == NRF_SUCCESS)
            {
                p_msc_ctx->current.trans_req_id ^= 1;
                APP_USBD_MSC_REQ_BUSY_SET(p_msc_ctx->current.req_busy_mask,
                                          p_msc_ctx->current.trans_req_id);
                p_msc_ctx->current.workbuff_pos ^= p_msc->specific.inst.block_buff_size;
                p_msc_ctx->current.trans_in_progress = true;
            }
        }
    }

    if (!p_msc_ctx->current.block_req_in_progress)
    {
        nrf_block_dev_t const * p_blkd =
                                p_msc->specific.inst.pp_block_devs[p_msc_ctx->current.lun];

        size_t pos = p_msc_ctx->current.workbuff_pos;
        if (p_msc_ctx->current.req_busy_mask != APP_USBD_MSC_REQ_BUSY_FULL_MASK)
        {
            pos ^= p_msc->specific.inst.block_buff_size;
        }

        NRF_BLOCK_DEV_REQUEST(req,
                              p_msc_ctx->current.blk_idx,
                              p_msc_ctx->current.blk_count,
                              ((uint8_t *)p_msc->specific.inst.p_block_buff + pos));

        NRF_LOG_DEBUG("nrf_blk_dev_write_req 1: id: %u, count: %u, left: %u, ptr: %p\r\n",
                      req.blk_id,
                      req.blk_count,
                      p_msc_ctx->current.blk_datasize,
                      (uint32_t)req.p_buff);

        p_msc_ctx->current.block_req_in_progress = true;
        ret = nrf_blk_dev_write_req(p_blkd, &req);
        NRF_LOG_DEBUG("nrf_blk_dev_write_req 1: ret: %u\r\n", ret);
    }

    return ret;
}

/**
 * @brief Endpoint OUT event handler
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_setup_ev    Setup event
 *
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t endpoint_out_event_handler(app_usbd_class_inst_t const *  p_inst,
                                             app_usbd_complex_evt_t const * p_event)
{
    app_usbd_msc_t const * p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *   p_msc_ctx = msc_ctx_get(p_msc);

    NRF_LOG_DEBUG("state: %d, ep out event, status: %d\r\n",
                  p_msc_ctx->state,
                  p_event->drv_evt.data.eptransfer.status);

    ret_code_t ret = NRF_SUCCESS;
    if (p_event->drv_evt.data.eptransfer.status == NRF_USBD_EP_WAITING)
    {
        if (p_msc_ctx->state == APP_USBD_MSC_STATE_DATA_OUT)
        {
            NRF_LOG_DEBUG("NRF_USBD_EP_WAITING\r\n");
        }
        else if (p_msc_ctx->state == APP_USBD_MSC_STATE_CSW ||
                 p_msc_ctx->state == APP_USBD_MSC_STATE_IDLE)
        {
            ret = cbw_wait_start(p_inst);
        }

        return ret;
    }
    else if (p_event->drv_evt.data.eptransfer.status == NRF_USBD_EP_ABORTED)
    {
        p_msc_ctx->state = APP_USBD_MSC_STATE_IDLE;
        return NRF_SUCCESS;
    }
    else if (p_event->drv_evt.data.eptransfer.status == NRF_USBD_EP_OVERLOAD)
    {
        nrf_drv_usbd_transfer_out_drop(p_event->drv_evt.data.eptransfer.ep);
        return NRF_SUCCESS;
    }
    else   /*NRF_USBD_EP_OK*/
    {
        switch (p_msc_ctx->state)
        {
            case APP_USBD_MSC_STATE_CBW:
            {
                ret = state_cbw(p_inst);
                break;
            }
            case APP_USBD_MSC_STATE_CMD_OUT:
            {
                ret = csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
                break;
            }
            case APP_USBD_MSC_STATE_DATA_OUT:
            {
                CRITICAL_REGION_ENTER();
                ret = state_data_out_handle(p_inst);
                CRITICAL_REGION_EXIT();
                break;
            }
            case APP_USBD_MSC_STATE_UNSUPPORTED:
            {
                ret = NRF_ERROR_NOT_SUPPORTED;
                break;
            }
            case APP_USBD_MSC_STATE_CSW:
                break;
            default:
            {
                ASSERT(0);
                break;
            }
        }
    }

    return ret;
}


/**
 * @brief @ref app_usbd_class_methods_t::event_handler
 */
static ret_code_t msc_event_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_complex_evt_t const * p_event)
{
    ASSERT(p_inst != NULL);
    ASSERT(p_event != NULL);

    app_usbd_msc_t const * p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *   p_msc_ctx = msc_ctx_get(p_msc);

    UNUSED_VARIABLE(p_msc);
    UNUSED_VARIABLE(p_msc_ctx);

    ret_code_t ret = NRF_SUCCESS;
    switch (p_event->app_evt.type)
    {
        case APP_USBD_EVT_DRV_SOF:
            break;
        case APP_USBD_EVT_DRV_RESET:
            break;
        case APP_USBD_EVT_DRV_SETUP:
            ret  = setup_event_handler(p_inst, (app_usbd_setup_evt_t const *)p_event);
            break;
        case APP_USBD_EVT_DRV_EPTRANSFER:
            if (NRF_USBD_EPIN_CHECK(p_event->drv_evt.data.eptransfer.ep))
            {
                ret = endpoint_in_event_handler(p_inst, p_event);
            }
            else
            {
                ret = endpoint_out_event_handler(p_inst, p_event);
            }
            break;
        case APP_USBD_EVT_DRV_SUSPEND:
        {
            /*Flush all block devices cache on suspend*/

            for (size_t i = 0; i < p_msc->specific.inst.block_devs_count; ++i)
            {
                nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[i];
                (void)nrf_blk_dev_ioctl(p_blkd, NRF_BLOCK_DEV_IOCTL_REQ_CACHE_FLUSH, NULL);
            }

            break;
        }
        case APP_USBD_EVT_DRV_RESUME:
            break;
        case APP_USBD_EVT_INST_APPEND:
        {
            /*Verify serial number string*/
            uint16_t const * p_serial_str = app_usbd_string_desc_get(APP_USBD_STRING_ID_SERIAL, 0);
            if (p_serial_str == NULL)
            {
                return NRF_ERROR_NOT_SUPPORTED;
            }

            size_t len = app_usbd_string_desc_length(p_serial_str) / sizeof(uint16_t);
            if (len < APP_USBD_MSC_MINIMAL_SERIAL_STRING_SIZE)
            {
                return NRF_ERROR_NOT_SUPPORTED;
            }

            for (size_t i = 1; i < len; ++i)
            {
                if (isxdigit(p_serial_str[i]) == 0)
                {
                    return NRF_ERROR_NOT_SUPPORTED;
                }
            }

            ret = app_usbd_class_sof_register(p_inst);
            if (ret != NRF_SUCCESS)
            {
                break;
            }

            break;
        }
        case APP_USBD_EVT_INST_REMOVE:
        {
            ret = app_usbd_class_sof_unregister(p_inst);
            break;
        }
        case APP_USBD_EVT_START:
        {
            /*Initialize all block devices*/
            ASSERT(p_msc->specific.inst.block_devs_count <= 16);
            for (size_t i = 0; i < p_msc->specific.inst.block_devs_count; ++i)
            {
                nrf_block_dev_t const * p_blk_dev = p_msc->specific.inst.pp_block_devs[i];
                ret = nrf_blk_dev_init(p_blk_dev, msc_blockdev_ev_handler, p_msc);
                if (ret != NRF_SUCCESS)
                {
                    continue;
                }

                p_msc_ctx->blk_dev_init_mask |= 1u << i;
                ASSERT(nrf_blk_dev_geometry(p_blk_dev)->blk_size <=
                       p_msc->specific.inst.block_buff_size);
            }

            break;
        }
        case APP_USBD_EVT_STOP:
        {
            /*Un-initialize all block devices*/
            ASSERT(p_msc->specific.inst.block_devs_count <= 16);
            size_t i;
            for (i = 0; i < p_msc->specific.inst.block_devs_count; ++i)
            {
                nrf_block_dev_t const * p_blk_dev = p_msc->specific.inst.pp_block_devs[i];
                ret = nrf_blk_dev_uninit(p_blk_dev);
                if (ret != NRF_SUCCESS)
                {
                    continue;
                }

                p_msc_ctx->blk_dev_init_mask &= ~(1u << i);
            }

            break;
        }
        default:
            ret = NRF_ERROR_NOT_SUPPORTED;
            break;
    }

    return ret;
}

/**
 * @brief @ref app_usbd_class_methods_t::get_descriptors
 */
static const void * msc_get_descriptors(app_usbd_class_inst_t const * p_inst, size_t * p_size)
{
    ASSERT(p_size != NULL);
    app_usbd_msc_t const *  p_msc = msc_get(p_inst);

    *p_size = p_msc->specific.inst.raw_desc_size;
    return p_msc->specific.inst.p_raw_desc;
}

const app_usbd_class_methods_t app_usbd_msc_class_methods = {
        .event_handler = msc_event_handler,
        .get_descriptors = msc_get_descriptors,
};


/**
 * @brief Block device read done event handler.
 *
 * @ref NRF_BLOCK_DEV_EVT_BLK_READ_DONE
 *
 * @param p_blk_dev     Block device handle
 * @param p_event       Block device event
 *
 * */
static void msc_blockdev_read_done_handler(nrf_block_dev_t const * p_blk_dev,
                                           nrf_block_dev_event_t const * p_event)
{
    ret_code_t ret;

    app_usbd_class_inst_t const * p_inst = p_event->p_context;
    app_usbd_msc_t const *        p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *          p_msc_ctx = msc_ctx_get(p_msc);

    uint32_t blk_cnt = p_msc_ctx->current.blk_count;
    uint32_t blk_size = p_msc_ctx->current.blk_size;

    /*Save actual request*/
    size_t req_pos = (p_msc_ctx->current.workbuff_pos != 0) ? 1 : 0;
    p_msc_ctx->current.req = *p_event->p_blk_req;

    p_msc_ctx->current.block_req_in_progress = false;

    /*Decrement transfer counter*/
    p_msc_ctx->current.blk_idx += blk_cnt;
    if (p_msc_ctx->current.blk_datasize > blk_size * blk_cnt)
    {
        p_msc_ctx->current.blk_datasize -= blk_size * blk_cnt;
    }
    else
    {
        p_msc_ctx->current.blk_datasize = 0;
    }

    NRF_LOG_DEBUG("read_done_handler: p_buff: %p, size: %u data size: %u req_pos: %u\r\n",
                  (uint32_t)p_event->p_blk_req->p_buff,
                  p_event->p_blk_req->blk_count,
                  p_msc_ctx->current.blk_datasize,
                  req_pos);

    /*Calculate next block request size*/
    p_msc_ctx->current.blk_count = next_transfer_blkcnt_calc(p_msc, p_msc_ctx);

    if (!p_msc_ctx->current.trans_in_progress)
    {
        /*Trigger new transfer.*/
        p_msc_ctx->current.trans_req_id = req_pos;
        nrf_block_req_t * p_req = &p_msc_ctx->current.req;

        ret = transfer_in_start(p_inst,
                                p_req->p_buff,
                                p_req->blk_count * blk_size,
                                APP_USBD_MSC_STATE_DATA_IN);
        if (ret != NRF_SUCCESS)
        {
            UNUSED_RETURN_VALUE(unsupported_start(p_inst));
        }
        else
        {
            /*Clear processed block request.*/
            memset(p_req, 0, sizeof(nrf_block_req_t));
            p_msc_ctx->current.trans_in_progress = true;
        }

    }

    if (p_msc_ctx->current.req_busy_mask == APP_USBD_MSC_REQ_BUSY_FULL_MASK)
    {
        /* No need to perform next block read request. USB transfers need to catch-up
         * block device readings */
        return;
    }

    if (p_msc_ctx->current.blk_count == 0)
    {
        /*All data has been read. No need to trigger new block request.*/
        return;
    }

    /*Trigger new block read request*/
    p_msc_ctx->current.workbuff_pos ^= p_msc->specific.inst.block_buff_size;
    req_pos = p_msc_ctx->current.workbuff_pos != 0 ? 1 : 0;

    APP_USBD_MSC_REQ_BUSY_SET(p_msc_ctx->current.req_busy_mask, req_pos);

    NRF_BLOCK_DEV_REQUEST(req,
                          p_msc_ctx->current.blk_idx,
                          p_msc_ctx->current.blk_count,
                          ((uint8_t *)p_msc->specific.inst.p_block_buff +
                          p_msc_ctx->current.workbuff_pos));


    NRF_LOG_DEBUG("nrf_blk_dev_read_req 2: id: %u, count: %u, left: %u, ptr: %p\r\n",
                  req.blk_id,
                  req.blk_count,
                  p_msc_ctx->current.blk_datasize,
                  (uint32_t)req.p_buff);

    ret = nrf_blk_dev_read_req(p_blk_dev, &req);
    NRF_LOG_DEBUG("nrf_blk_dev_read_req 2: ret: %u\r\n", ret);

    if (ret != NRF_SUCCESS)
    {
        UNUSED_RETURN_VALUE(unsupported_start(p_inst));
    }
}

/**
 * @brief Block device write done event handler.
 *
 * @ref NRF_BLOCK_DEV_EVT_BLK_WRITE_DONE
 *
 * @param p_blk_dev     Block device handle
 * @param p_event       Block device event
 *
 * */
static void msc_blockdev_write_done_handler(nrf_block_dev_t const * p_blk_dev,
                                            nrf_block_dev_event_t const * p_event)
{
    app_usbd_class_inst_t const * p_inst = p_event->p_context;
    app_usbd_msc_t const *        p_msc = msc_get(p_inst);
    app_usbd_msc_ctx_t *          p_msc_ctx = msc_ctx_get(p_msc);

    uint32_t blk_cnt = p_msc_ctx->current.blk_count;
    uint32_t blk_size = p_msc_ctx->current.blk_size;

    /*Save actual request*/
    size_t req_pos = (p_event->p_blk_req->p_buff == p_msc->specific.inst.p_block_buff) ? 0 : 1;
    p_msc_ctx->current.req = *p_event->p_blk_req;

    APP_USBD_MSC_REQ_BUSY_CLR(p_msc_ctx->current.req_busy_mask, req_pos);
    p_msc_ctx->current.block_req_in_progress = false;

    p_msc_ctx->current.blk_idx += blk_cnt;

    if (p_msc_ctx->current.blk_datasize > blk_size * blk_cnt)
    {
        p_msc_ctx->current.blk_datasize -= blk_size * blk_cnt;
    }
    else
    {
        p_msc_ctx->current.blk_datasize = 0;
    }

    NRF_LOG_DEBUG("write_done_handler: p_buff: %p, size: %u data size: %u req_pos: %u\r\n",
                  (uint32_t)p_event->p_blk_req->p_buff,
                  p_event->p_blk_req->blk_count,
                  p_msc_ctx->current.blk_datasize,
                  req_pos);

    if (p_msc_ctx->current.blk_datasize == 0)
    {
        p_msc_ctx ->current.blk_idx = p_msc_ctx ->current.blk_size = 0;
        UNUSED_RETURN_VALUE(csw_wait_start(p_inst, p_msc_ctx->current.csw_status));
        return;
    }

    if (p_msc_ctx->current.blk_datasize <= p_msc_ctx->current.blk_count * blk_size)
    {
        size_t pos = p_msc_ctx->current.workbuff_pos;
        if (p_msc_ctx->current.req_busy_mask != APP_USBD_MSC_REQ_BUSY_FULL_MASK)
        {
            pos ^= p_msc->specific.inst.block_buff_size;
        }

        NRF_BLOCK_DEV_REQUEST(req,
                              p_msc_ctx->current.blk_idx,
                              p_msc_ctx->current.blk_count,
                              ((uint8_t *)p_msc->specific.inst.p_block_buff + pos));

        NRF_LOG_DEBUG("nrf_blk_dev_write_req 2: id: %u, count: %u, left: %u, ptr: %p\r\n",
                      req.blk_id,
                      req.blk_count,
                      p_msc_ctx->current.blk_datasize,
                      (uint32_t)req.p_buff);

        p_msc_ctx->current.block_req_in_progress = true;
        ret_code_t ret = nrf_blk_dev_write_req(p_blk_dev, &req);
        NRF_LOG_DEBUG("nrf_blk_dev_write_req 2: ret: %u\r\n", ret);

        if (ret != NRF_SUCCESS)
        {
            UNUSED_RETURN_VALUE(unsupported_start(p_inst));
        }

        return;
    }

    if (!p_msc_ctx->current.trans_in_progress &&
        (p_msc_ctx->current.blk_datasize  > p_msc_ctx->current.blk_count * blk_size))
    {
        size_t size = p_msc_ctx->current.blk_datasize - p_msc_ctx->current.blk_count * blk_size;
        if (size > p_msc_ctx->current.blk_count * blk_size)
        {
            size = p_msc_ctx->current.blk_count * blk_size;
        }

        if (size > 0)
        {
            /*Trigger new transfer.*/
            p_msc_ctx->current.blk_count = next_transfer_blkcnt_calc(p_msc, p_msc_ctx);
            ret_code_t ret = transfer_out_start(p_inst,
                                                ((uint8_t *)p_msc->specific.inst.p_block_buff +
                                                p_msc_ctx->current.workbuff_pos),
                                                size,
                                                APP_USBD_MSC_STATE_DATA_OUT);
            if (ret == NRF_SUCCESS)
            {
                p_msc_ctx->current.trans_req_id ^= 1;
                APP_USBD_MSC_REQ_BUSY_SET(p_msc_ctx->current.req_busy_mask,
                                          p_msc_ctx->current.trans_req_id);
                p_msc_ctx->current.workbuff_pos ^= p_msc->specific.inst.block_buff_size;
                p_msc_ctx->current.trans_in_progress = true;
            }
            else
            {
                UNUSED_RETURN_VALUE(unsupported_start(p_inst));
            }
        }
    }
}


/**
 * @brief Block device event handler.
 *
 * Mass storage block device event handler. Need to be pined to all block devices
 * from initializer list.
 *
 * @param p_blk_dev     Block device handle
 * @param p_event       Block device event
 *
 * */
static void msc_blockdev_ev_handler(nrf_block_dev_t const * p_blk_dev,
                                    nrf_block_dev_event_t const * p_event)
{
    switch (p_event->ev_type) {
        case NRF_BLOCK_DEV_EVT_INIT:
            break;
        case NRF_BLOCK_DEV_EVT_UNINIT:
            break;
        case NRF_BLOCK_DEV_EVT_BLK_READ_DONE:
            CRITICAL_REGION_ENTER();
            msc_blockdev_read_done_handler(p_blk_dev, p_event);
            CRITICAL_REGION_EXIT();
            break;
        case NRF_BLOCK_DEV_EVT_BLK_WRITE_DONE:
            CRITICAL_REGION_ENTER();
            msc_blockdev_write_done_handler(p_blk_dev, p_event);
            CRITICAL_REGION_EXIT();
            break;
        default:
            break;
    }
}


bool app_usbd_msc_sync(app_usbd_msc_t const * p_msc)
{
    bool rc = true;
    ret_code_t ret = NRF_SUCCESS;

    for (size_t i = 0; i < p_msc->specific.inst.block_devs_count; ++i)
    {
        nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[i];
        bool flush_in_progress = true;

        ret = nrf_blk_dev_ioctl(p_blkd,
                                NRF_BLOCK_DEV_IOCTL_REQ_CACHE_FLUSH,
                                &flush_in_progress);

        if ((ret != NRF_SUCCESS) || flush_in_progress)
        {
            rc = false;
        }
    }

    return rc;
}

/** @} */

#endif // APP_USBD_CLASS_MSC_ENABLED
