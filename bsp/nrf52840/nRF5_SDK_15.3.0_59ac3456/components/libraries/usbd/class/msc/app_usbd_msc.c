/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(APP_USBD_MSC)

#include <string.h>
#include <ctype.h>
#include "app_usbd.h"
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

#define NRF_LOG_MODULE_NAME usbd_msc

#if APP_USBD_MSC_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       APP_USBD_MSC_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  APP_USBD_MSC_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR APP_USBD_MSC_CONFIG_DEBUG_COLOR
#else // APP_USBD_MSC_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif  // APP_USBD_MSC_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define APP_USBD_MSC_IFACE_IDX 0 /**< Mass storage class interface index */
#define APP_USBD_MSC_EPIN_IDX  0 /**< Mass storage class endpoint IN index */
#define APP_USBD_MSC_EPOUT_IDX 1 /**< Mass storage class endpoint OUT index */

/**
 * @brief Set request buffer busy flag.
 *
 * @param[in] val   Bitmask to set.
 * @param[in] id    Buffer id.
 * */
#define APP_USBD_MSC_REQ_BUSY_SET(val, id) SET_BIT(val, id)

/**
 * @brief Clear request buffer busy flag.
 *
 * @param[in] val   Bitmask to set.
 * @param[in] id    Buffer id.
 * */
#define APP_USBD_MSC_REQ_BUSY_CLR(val, id) CLR_BIT(val, id)

#define APP_USBD_MSC_REQ_BUSY_FULL_MASK (0x03) /**< Request busy mask */

static void msc_blockdev_ev_handler(nrf_block_dev_t const       * p_blk_dev,
                                    nrf_block_dev_event_t const * p_event);

/** @brief Command Block Wrapper signature */
static const uint8_t m_cbw_signature[] = APP_USBD_MSC_CBW_SIGNATURE;

/** @brief Command Status Wrapper signature */
static const uint8_t m_csw_signature[] = APP_USBD_MSC_CSW_SIGNATURE;

STATIC_ASSERT(sizeof(m_cbw_signature) == sizeof(((app_usbd_msc_cbw_t*)0)->signature));
STATIC_ASSERT(sizeof(m_csw_signature) == sizeof(((app_usbd_msc_csw_t*)0)->signature));

/**
 * @brief Auxiliary function to access MSC instance data.
 *
 * @param[in] p_inst Class instance data.
 *
 * @return MSC instance data @ref app_usbd_msc_t
 */
static inline app_usbd_msc_t const * msc_get(app_usbd_class_inst_t const * p_inst)
{
    ASSERT(p_inst != NULL);
    return (app_usbd_msc_t const *)p_inst;
}

/**
 * @brief Auxiliary function to access MSC context data.
 *
 * @param[in] p_msc    MSC instance data.
 * @return MSC context data @ref app_usbd_msc_ctx_t
 */
static inline app_usbd_msc_ctx_t * msc_ctx_get(app_usbd_msc_t const * p_msc)
{
    ASSERT(p_msc != NULL);
    ASSERT(p_msc->specific.p_data != NULL);
    return &p_msc->specific.p_data->ctx;
}


/**
 * @brief Auxiliary function to access MSC IN endpoint address.
 *
 * @param[in] p_inst Class instance data.
 *
 * @return IN endpoint address.
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
 * @brief Auxiliary function to access MSC OUT endpoint address.
 *
 * @param[in] p_inst Class instance data.
 *
 * @return OUT endpoint address.
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
 * @brief Clear the data buffer.
 *
 * @param p_msc MSC instance data.
 */
static inline void msc_buff_clear(app_usbd_msc_t const * p_msc)
{
    app_usbd_msc_ctx_t * p_ctx = msc_ctx_get(p_msc);

    p_ctx->current.buff.rd_idx  = 0;
    p_ctx->current.buff.d_count = 0;
    p_ctx->current.buff.a_count = 0;
}

/**
 * @brief Check if there is any data block ready in the buffer.
 *
 * @param p_msc MSC instance data.
 *
 * @retval true  There is data block ready.
 * @retval false There is no data ready for processing.
 */
static inline bool msc_buff_data_check(app_usbd_msc_t const * p_msc)
{
    app_usbd_msc_ctx_t * p_ctx = msc_ctx_get(p_msc);
    return (p_ctx->current.buff.d_count > 0);
}

/**
 * @brief Check if there is any free space in the buffer.
 *
 * @param p_msc MSC instance data.
 *
 * @retval true  There is free space.
 * @retval false There is no free space.
 */
static inline bool msc_buff_space_check(app_usbd_msc_t const * p_msc)
{
    app_usbd_msc_ctx_t * p_ctx = msc_ctx_get(p_msc);
    return (p_ctx->current.buff.a_count < p_msc->specific.inst.block_buff_count);
}

/**
 * @brief Allocate buffer block.
 *
 * @param p_msc MSC instance data.
 *
 * @return Pointer to a data block or NULL if there is no free space available.
 */
static inline void * msc_buff_alloc(app_usbd_msc_t const * p_msc)
{
    app_usbd_msc_ctx_t * p_ctx = msc_ctx_get(p_msc);
    void * p_buff = NULL;
    CRITICAL_REGION_ENTER();
    if (msc_buff_space_check(p_msc))
    {
        uint8_t idx = (p_ctx->current.buff.rd_idx + p_ctx->current.buff.a_count) %
            p_msc->specific.inst.block_buff_count;
        size_t offset = idx * p_msc->specific.inst.block_buff_size;
        p_buff = ((uint8_t*)(p_msc->specific.inst.p_block_buff)) + offset;
        ++(p_ctx->current.buff.a_count);
    }
    NRF_LOG_DEBUG("buff_alloc, idx: %u, dc: %u, ac: %u",
                  p_ctx->current.buff.rd_idx,
                  p_ctx->current.buff.d_count,
                  p_ctx->current.buff.a_count);
    CRITICAL_REGION_EXIT();

    return p_buff;
}

/**
 * @brief Put the buffer block.
 *
 * Puts previously allocated buffer and marks it as ready to be processed.
 *
 * @param p_msc MSC instance data.
 *
 * @note This one may be called only if the previous call of
 *       @ref msc_buff_alloc succeed.
 */
static inline void msc_buff_put(app_usbd_msc_t const * p_msc)
{
    app_usbd_msc_ctx_t * p_ctx = msc_ctx_get(p_msc);
    CRITICAL_REGION_ENTER();
    /* Assert if there is any space - if it is not it means some coding error */
    ASSERT(p_ctx->current.buff.d_count < p_ctx->current.buff.a_count);
    ASSERT(p_ctx->current.buff.d_count < p_msc->specific.inst.block_buff_count);
    ++(p_ctx->current.buff.d_count);
    NRF_LOG_DEBUG("buff_put, idx: %u, dc: %u, ac: %u",
                  p_ctx->current.buff.rd_idx,
                  p_ctx->current.buff.d_count,
                  p_ctx->current.buff.a_count);
    CRITICAL_REGION_EXIT();
}

/**
 * @brief Get the data block filled with data.
 *
 * @param p_msc MSC instance data.
 *
 * @return Pointer to the buffer or NULL if there is no data to be processed.
 */
static inline void * msc_buff_get(app_usbd_msc_t const * p_msc)
{
    app_usbd_msc_ctx_t * p_ctx = msc_ctx_get(p_msc);
    void * p_buff = NULL;
    CRITICAL_REGION_ENTER();
    if (msc_buff_data_check(p_msc))
    {
        uint8_t idx = p_ctx->current.buff.rd_idx;
        size_t offset = idx * p_msc->specific.inst.block_buff_size;
        p_buff = ((uint8_t*)(p_msc->specific.inst.p_block_buff)) + offset;
    }
    NRF_LOG_DEBUG("buff_get, idx: %u, dc: %u, ac: %u",
                  p_ctx->current.buff.rd_idx,
                  p_ctx->current.buff.d_count,
                  p_ctx->current.buff.a_count);
    CRITICAL_REGION_EXIT();

    return p_buff;
}

/**
 * @brief Free the last used data buffer block.
 *
 * Function frees the oldest data block.
 *
 * @param p_msc MSC instance data.
 *
 * @note This one may be called only if the previous call of
 *       @ref msc_buff_get succeed.
 */
static inline void msc_buff_free(app_usbd_msc_t const * p_msc)
{
    app_usbd_msc_ctx_t * p_ctx = msc_ctx_get(p_msc);
    CRITICAL_REGION_ENTER();
    /* Assert if there is any data - in case there is none, a coding error exists */
    ASSERT(p_ctx->current.buff.d_count > 0);
    ASSERT(p_ctx->current.buff.a_count > 0);
    --(p_ctx->current.buff.d_count);
    --(p_ctx->current.buff.a_count);
    p_ctx->current.buff.rd_idx = (p_ctx->current.buff.rd_idx + 1) %
        p_msc->specific.inst.block_buff_count;
    NRF_LOG_DEBUG("buff_free, idx: %u, dc: %u, ac: %u",
              p_ctx->current.buff.rd_idx,
              p_ctx->current.buff.d_count,
              p_ctx->current.buff.a_count);
    CRITICAL_REGION_EXIT();
}

/**
 * @brief Helpful macro to sub a value with zero saturation.
 *
 * @param[in] m The minuend.
 * @param[in] s The subtrahend.
 *
 * @return The difference saturated at 0.
 */
#define SUB_SAT0(m, s) ((m) < (s)) ?  0 : ((m) - (s))

/**
 * @brief Command Block Wrapper trigger.
 *
 * @param[in] p_inst    Generic class instance.
 * @param[in] state     Next state transition.
 *
 * @return Standard error code.
 * */
static ret_code_t cbw_wait_start(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);

    nrf_drv_usbd_ep_t ep_addr_out = ep_out_addr_get(p_inst);

    NRF_LOG_DEBUG("cbw_wait_start");
    memset(&p_msc_ctx->cbw, 0, sizeof(app_usbd_msc_cbw_t));
    NRF_DRV_USBD_TRANSFER_OUT(cbw, &p_msc_ctx->cbw, sizeof(app_usbd_msc_cbw_t));
    ret_code_t ret = app_usbd_ep_transfer(ep_addr_out, &cbw);
    if (ret == NRF_SUCCESS)
    {
        p_msc_ctx->state = APP_USBD_MSC_STATE_CBW;
    }

    return ret;
}


/**
 * @brief Command Status Wrapper trigger.
 *
 * @param[in] p_inst    Generic class instance.
 * @param[in] state     Next state transition.
 *
 * @return Standard error code.
 * */
static ret_code_t csw_wait_start(app_usbd_class_inst_t const * p_inst, uint8_t status)
{
    app_usbd_msc_t const * p_msc      = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx  = msc_ctx_get(p_msc);
    nrf_drv_usbd_ep_t      ep_addr_in = ep_in_addr_get(p_inst);

    NRF_LOG_DEBUG("csw_wait_start: %u", status);

    /* The maximum of this two is already the data that was not processed */
    size_t datalen_left = MAX(
        p_msc_ctx->current.process.datalen_left,
        p_msc_ctx->current.transfer.datalen_left);

    UNUSED_RETURN_VALUE(uint32_encode(datalen_left, p_msc_ctx->csw.residue));
    p_msc_ctx->csw.status = status;

    NRF_DRV_USBD_TRANSFER_IN(csw, &p_msc_ctx->csw, sizeof(app_usbd_msc_csw_t));
    ret_code_t ret = app_usbd_ep_transfer(ep_addr_in, &csw);
    if (ret == NRF_SUCCESS)
    {
        p_msc_ctx->state = APP_USBD_MSC_STATE_CSW;
    }

    return ret;
}


/**
 * @brief IN transfer trigger.
 *
 * @param[in] p_inst    Generic class instance.
 * @param[in] p_buff    IN transfer data buffer.
 * @param[in] size      IN transfer size.
 * @param[in] state     Next state transition.
 *
 * @return Standard error code.
 * */
static ret_code_t transfer_in_start(app_usbd_class_inst_t const * p_inst,
                                    void const                  * p_buff,
                                    size_t                        size,
                                    app_usbd_msc_state_t          state)
{
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);

    NRF_LOG_DEBUG("transfer_in_start: p_buff: %p, size: %u", (uint32_t)p_buff, size);

    nrf_drv_usbd_ep_t ep_addr_in = ep_in_addr_get(p_inst);

    NRF_DRV_USBD_TRANSFER_IN(resp, p_buff, size);
    ret_code_t ret = app_usbd_ep_transfer(ep_addr_in, &resp);
    if (ret == NRF_SUCCESS)
    {
        p_msc_ctx->state = state;
    }
    return ret;
}


/**
 * @brief MSC reset request handler @ref  APP_USBD_MSC_REQ_BULK_RESET
 *
 * @param[in] p_inst    Generic class instance.
 *
 * */
static void bulk_ep_reset(app_usbd_class_inst_t const * p_inst)
{
    nrf_drv_usbd_ep_t ep_addr_in  = ep_in_addr_get(p_inst);
    nrf_drv_usbd_ep_t ep_addr_out = ep_out_addr_get(p_inst);

    nrf_drv_usbd_ep_abort(ep_addr_in);
    nrf_drv_usbd_ep_abort(ep_addr_out);
}


/**
 * @brief OUT transfer trigger.
 *
 * @param[in] p_inst    Generic class instance.
 * @param[in] p_buff    OUT transfer data buffer.
 * @param[in] size      OUT transfer size.
 * @param[in] state     Next state transition.
 *
 * @return Standard error code.
 * */
static ret_code_t transfer_out_start(app_usbd_class_inst_t const * p_inst,
                                     void                        * p_buff,
                                     size_t                        size,
                                     app_usbd_msc_state_t          state)
{
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);

    NRF_LOG_DEBUG("transfer_out_start: p_buff: %p, size: %u", (uint32_t)p_buff, size);
    nrf_drv_usbd_ep_t ep_addr_out = ep_out_addr_get(p_inst);

    NRF_DRV_USBD_TRANSFER_OUT(resp, p_buff, size);
    ret_code_t ret = app_usbd_ep_transfer(ep_addr_out, &resp);
    if (ret == NRF_SUCCESS)
    {
        p_msc_ctx->state = state;
    }
    return ret;
}


/**
 * @brief Generic function to stall communication endpoints and mark error state.
 *
 * Function used internally to stall all communication endpoints and mark current state.
 *
 * @param p_inst Generic class instance.
 * @param state  State to set.
 */
static void status_generic_error_stall(app_usbd_class_inst_t const * p_inst,
                                       app_usbd_msc_state_t          state)
{
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);

    nrf_drv_usbd_ep_t ep_in  = ep_in_addr_get(p_inst);
    nrf_drv_usbd_ep_t ep_out = ep_out_addr_get(p_inst);

    nrf_drv_usbd_ep_stall(ep_in);
    nrf_drv_usbd_ep_stall(ep_out);
    nrf_drv_usbd_ep_abort(ep_in);
    nrf_drv_usbd_ep_abort(ep_out);

    p_msc_ctx->state = state;
}


/**
 * @brief Start status stage of unsupported SCSI command.
 *
 * @param[in,out] p_inst    Generic class instance.
 *
 * @return Standard error code.
 *
 * @sa status_generic_error_stall
 */
static ret_code_t status_unsupported_start(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_msc_t const * p_msc      = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx  = msc_ctx_get(p_msc);
    bool                   data_stage = uint32_decode(p_msc_ctx->cbw.datlen) != 0;
    ret_code_t             ret        = NRF_SUCCESS;
    if (!data_stage)
    {
        /* Try to transfer the response now */
        ret = csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_FAIL);
    }
    else
    {
        /* Cannot transfer failed response in current command - stall the endpoints and postpone the answer */
        status_generic_error_stall(p_inst, APP_USBD_MSC_STATE_UNSUPPORTED);
    }
    return ret;
}


/**
 * @brief Start status stage of CBW invalid.
 *
 * @param[in,out] p_inst    Generic class instance.
 *
 * @sa status_generic_error_stall
 */
static void status_cbwinvalid_start(app_usbd_class_inst_t const * p_inst)
{
    status_generic_error_stall(p_inst, APP_USBD_MSC_STATE_CBW_INVALID);
}


/**
 * @brief Start status stage of internal device error.
 *
 * Kind of error that requires bulk reset but does not stall endpoint permanently - the correct
 * answer is possible.
 *
 * @param[in] p_inst    Generic class instance.
 *
 * @sa status_generic_error_stall
 */
static void status_deverror_start(app_usbd_class_inst_t const * p_inst)
{
    status_generic_error_stall(p_inst, APP_USBD_MSC_STATE_DEVICE_ERROR);
}


/**
 * @brief Internal SETUP standard IN request handler.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 * @retval NRF_SUCCESS              Request handled correctly.
 * @retval NRF_ERROR_NOT_SUPPORTED  Request is not supported.
 */
static ret_code_t setup_req_std_in(app_usbd_class_inst_t const * p_inst,
                                   app_usbd_setup_evt_t const  * p_setup_ev)
{
    /* Only Get Descriptor standard IN request is supported by MSC class */
    if ((app_usbd_setup_req_rec(p_setup_ev->setup.bmRequestType) == APP_USBD_SETUP_REQREC_INTERFACE)
        &&
        (p_setup_ev->setup.bRequest == APP_USBD_SETUP_STDREQ_GET_DESCRIPTOR))
    {
        size_t dsc_len = 0;
        size_t max_size;

        uint8_t * p_trans_buff = app_usbd_core_setup_transfer_buff_get(&max_size);

        /* Try to find descriptor in class internals*/
        ret_code_t ret = app_usbd_class_descriptor_find(
            p_inst,
            p_setup_ev->setup.wValue.hb,
            p_setup_ev->setup.wValue.lb,
            p_trans_buff,
            &dsc_len);

        if (ret != NRF_ERROR_NOT_FOUND)
        {
            ASSERT(dsc_len < NRF_DRV_USBD_EPSIZE);
            return app_usbd_core_setup_rsp(&(p_setup_ev->setup), p_trans_buff, dsc_len);
        }
    }
    return NRF_ERROR_NOT_SUPPORTED;
}


/**
 * @brief Internal SETUP standard OUT request handler.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 * @retval NRF_SUCCESS              Request handled correctly.
 * @retval NRF_ERROR_NOT_SUPPORTED  Request is not supported.
 * @retval NRF_ERROR_FORBIDDEN      Endpoint stall cannot be cleared because of internal state.
 */
static ret_code_t setup_req_std_out(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_setup_evt_t const  * p_setup_ev)
{
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);

    app_usbd_setup_reqrec_t req_rec = app_usbd_setup_req_rec(p_setup_ev->setup.bmRequestType);

    if ((req_rec == APP_USBD_SETUP_REQREC_ENDPOINT) &&
        (p_setup_ev->setup.bRequest == APP_USBD_SETUP_STDREQ_CLEAR_FEATURE) &&
        (p_setup_ev->setup.wValue.w == APP_USBD_SETUP_STDFEATURE_ENDPOINT_HALT))
    {
        if (p_msc_ctx->state == APP_USBD_MSC_STATE_CBW_INVALID)
        {
            return NRF_ERROR_FORBIDDEN;
        }
        ret_code_t ret = NRF_SUCCESS;
        /* Clearing endpoint here. It is done normally inside app_usbd, but we are overwritting this functionality */
        nrf_drv_usbd_ep_t ep_addr = (nrf_drv_usbd_ep_t)(p_setup_ev->setup.wIndex.lb);
        nrf_drv_usbd_ep_dtoggle_clear(ep_addr);
        nrf_drv_usbd_ep_stall_clear(ep_addr);
        if (NRF_USBD_EPIN_CHECK(ep_addr))
        {
            switch (p_msc_ctx->state)
            {
                case APP_USBD_MSC_STATE_UNSUPPORTED:
                {
                    nrf_drv_usbd_ep_stall_clear(ep_out_addr_get(p_inst));
                    /*Unsupported command handle: status stage*/
                    ret = csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_FAIL);
                    if (ret != NRF_SUCCESS)
                    {
                        NRF_LOG_ERROR("Unexpected csw_wait_start on ep clear: %d", ret);
                    }
                    break;
                }

                case APP_USBD_MSC_STATE_DEVICE_ERROR:
                {
                    nrf_drv_usbd_ep_stall_clear(ep_out_addr_get(p_inst));
                    /*Unsupported command handle: status stage*/
                    ret = csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PE);
                    if (ret != NRF_SUCCESS)
                    {
                        NRF_LOG_ERROR("Unexpected csw_wait_start on ep clear: %d", ret);
                    }
                    break;
                }

                default:
                    break;
            }
        }
        return ret;
    }
    return NRF_ERROR_NOT_SUPPORTED;
}


/**
 * @brief Internal SETUP class IN request handler.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 * @retval NRF_SUCCESS              Request handled correctly.
 * @retval NRF_ERROR_NOT_SUPPORTED  Request is not supported.
 */
static ret_code_t setup_req_class_in(app_usbd_class_inst_t const * p_inst,
                                     app_usbd_setup_evt_t const  * p_setup_ev)
{
    app_usbd_msc_t const * p_msc = msc_get(p_inst);

    switch (p_setup_ev->setup.bRequest)
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

            size_t     tx_size;
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
 * @brief Internal SETUP class OUT request handler.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 * @retval NRF_SUCCESS              Request handled correctly.
 * @retval NRF_ERROR_NOT_SUPPORTED  Request is not supported.
 */
static ret_code_t setup_req_class_out(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_setup_evt_t const  * p_setup_ev)
{
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);

    switch (p_setup_ev->setup.bRequest)
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
            NRF_LOG_DEBUG("bulk ep reset");
            bulk_ep_reset(p_inst);

            if (p_msc_ctx->state != APP_USBD_MSC_STATE_CBW)
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
 * @brief Control endpoint handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 * @retval NRF_SUCCESS              Request handled correctly.
 * @retval NRF_ERROR_NOT_SUPPORTED  Request is not supported.
 */
static ret_code_t setup_event_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_setup_evt_t const  * p_setup_ev)
{
    ASSERT(p_inst != NULL);
    ASSERT(p_setup_ev != NULL);

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
    else /* APP_USBD_SETUP_REQDIR_OUT */
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
 * @brief Get number of blocks that should be transfered into the selected LUN
 *
 * Function calculates number of blocks for the request.
 * The number of block is calculated based on the work buffer size and the size left to transfer.
 *
 * @param p_msc MSC instance.
 * @param size  The size of the transfer left.
 *
 * @return Number of blocks required for the transfer.
 */
static uint32_t current_blkcnt_calc(app_usbd_msc_t const * p_msc, size_t size)
{
    app_usbd_msc_ctx_t * p_msc_ctx = msc_ctx_get(p_msc);

    if (size > p_msc->specific.inst.block_buff_size)
    {
        size = p_msc->specific.inst.block_buff_size;
    }
    return CEIL_DIV(size, p_msc_ctx->current.process.blk_size);
}


/**
 * @brief Helper function to calculate next transfer size.
 *
 * @param[in] p_msc   MSC instance.
 * @param[in] size    Total size of the transfer left.
 *
 * @return Blocks to transfer.
 * */
static uint32_t current_size_calc(app_usbd_msc_t const * p_msc, size_t size)
{
    return MIN(size, p_msc->specific.inst.block_buff_size);
}


static ret_code_t read_transfer_processor(app_usbd_class_inst_t const * p_inst)
{
    ret_code_t ret                   = NRF_SUCCESS;
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);
    if ((!p_msc_ctx->current.transfer.pending))
    {
        NRF_LOG_DEBUG("read_transfer_processor: left: %u, state: %u",
                      p_msc_ctx->current.transfer.size_left,
                      p_msc_ctx->state);
        if (p_msc_ctx->current.transfer.abort)
        {
            NRF_LOG_ERROR("read_transfer_processor: aborted");
            ret = NRF_ERROR_NOT_SUPPORTED;
        }
        else if (p_msc_ctx->current.transfer.size_left > 0)
        {
            if (msc_buff_data_check(p_msc))
            {
                void * p_buff   = msc_buff_get(p_msc);
                size_t req_size = current_size_calc(p_msc, p_msc_ctx->current.transfer.size_left);
                ASSERT(p_buff != NULL);
                /*Trigger new transfer.*/
                p_msc_ctx->current.transfer.pending = true;
                ret = transfer_in_start(p_inst, p_buff, req_size, APP_USBD_MSC_STATE_DATA_IN);
                if (ret != NRF_SUCCESS)
                {
                    p_msc_ctx->current.transfer.pending = false;
                }
            }
        }
        else
        {
            if (p_msc_ctx->state == APP_USBD_MSC_STATE_DATA_IN)
            {
                if (p_msc_ctx->current.transfer.datalen_left == 0)
                {
                    ret = csw_wait_start(p_inst, p_msc_ctx->csw.status);
                    ASSERT(ret == NRF_SUCCESS);
                }
                else
                {
                    ret = NRF_ERROR_NOT_SUPPORTED;
                }
            }
        }
    }
    return ret;
}


static ret_code_t read_blockmem_processor(app_usbd_class_inst_t const * p_inst)
{
    ret_code_t ret                   = NRF_SUCCESS;
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);
    if (!(p_msc_ctx->current.process.pending))
    {
        NRF_LOG_DEBUG("read_blockmem_processor: left: %u", p_msc_ctx->current.process.size_left);
        if (p_msc_ctx->current.process.abort)
        {
            NRF_LOG_ERROR("read_blockmem_processor: aborted");
            ret = NRF_ERROR_NOT_SUPPORTED;
        }
        else if ((p_msc_ctx->current.process.size_left > 0) && msc_buff_space_check(p_msc))
        {
            nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];
            uint32_t blk_cnt = current_blkcnt_calc(p_msc, p_msc_ctx->current.process.size_left);
            void * p_buff    = msc_buff_alloc(p_msc);
            ASSERT(p_buff != NULL);
            NRF_BLOCK_DEV_REQUEST(
                req,
                p_msc_ctx->current.process.blk_idx,
                blk_cnt,
                p_buff);

            p_msc_ctx->current.process.pending = true;
            ret = nrf_blk_dev_read_req(p_blkd, &req);

            if (ret != NRF_SUCCESS)
            {
                /* Mark process pending and move all pionters */
                p_msc_ctx->current.process.pending = false;
                NRF_LOG_ERROR("read_blockmem_processor: block req failed: %u", ret);
            }
        }
    }
    return ret;
}


static ret_code_t write_transfer_processor(app_usbd_class_inst_t const * p_inst)
{
    ret_code_t ret                   = NRF_SUCCESS;
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);
    if (!(p_msc_ctx->current.transfer.pending))
    {
        NRF_LOG_DEBUG("write_transfer_processor: left: %u", p_msc_ctx->current.transfer.size_left);
        if ((p_msc_ctx->current.transfer.size_left > 0) && msc_buff_space_check(p_msc))
        {
            void * p_buff   = msc_buff_alloc(p_msc);
            size_t req_size = current_size_calc(p_msc, p_msc_ctx->current.transfer.size_left);
            ASSERT(p_buff != NULL);
            /*Trigger new transfer.*/
            p_msc_ctx->current.transfer.pending = true;
            ret = transfer_out_start(p_inst, p_buff, req_size, APP_USBD_MSC_STATE_DATA_OUT);
            if (ret != NRF_SUCCESS)
            {
                p_msc_ctx->current.transfer.pending = false;
            }
        }
    }
    return ret;
}

static ret_code_t write_blockmem_processor(app_usbd_class_inst_t const * p_inst)
{
    ret_code_t ret                   = NRF_SUCCESS;
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);

    if (!(p_msc_ctx->current.process.pending))
    {
        NRF_LOG_DEBUG("write_blockmem_processor: left: %u, state: %u",
                      p_msc_ctx->current.process.size_left,
                      p_msc_ctx->state);
        if (p_msc_ctx->current.process.abort)
        {
            NRF_LOG_ERROR("write_blockmem_processor: aborted");
            ret = NRF_ERROR_NOT_SUPPORTED;
        }
        else if (p_msc_ctx->current.process.size_left > 0)
        {
            if (msc_buff_data_check(p_msc))
            {
                nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];
                uint32_t blk_cnt = current_blkcnt_calc(p_msc, p_msc_ctx->current.process.size_left);
                void * p_buff    = msc_buff_get(p_msc);
                ASSERT(p_buff != NULL);
                NRF_BLOCK_DEV_REQUEST(
                    req,
                    p_msc_ctx->current.process.blk_idx,
                    blk_cnt,
                    p_buff);

                p_msc_ctx->current.process.pending = true;
                ret = nrf_blk_dev_write_req(p_blkd, &req);

                if (ret != NRF_SUCCESS)
                {
                    p_msc_ctx->current.process.pending = false;
                    NRF_LOG_ERROR("write_blockmem_processor: block req failed: %u", ret);
                }
            }
        }
        else
        {
            if (p_msc_ctx->state == APP_USBD_MSC_STATE_DATA_OUT)
            {
                if (p_msc_ctx->current.process.datalen_left == 0)
                {
                    ret = csw_wait_start(p_inst, p_msc_ctx->csw.status);
                    ASSERT(ret == NRF_SUCCESS);
                }
                else
                {
                    ret = NRF_ERROR_NOT_SUPPORTED;
                }
            }
        }
    }
    return ret;
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_TESTUNITREADY handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_testunitready(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_msc_t const        * p_msc,
                                    app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: TESTUNITREADY");
    if (uint32_decode(p_msc_ctx->cbw.datlen) != 0)
    {
        return status_unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.cdb_length != APP_USBD_SCSI_CMD_TESTUNITREADY_LEN)
    {
        return status_unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.lun >= p_msc->specific.inst.block_devs_count)
    {
        return status_unsupported_start(p_inst);
    }

    return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_REQUESTSENSE handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_requestsense(app_usbd_class_inst_t const * p_inst,
                                   app_usbd_msc_t const        * p_msc,
                                   app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: REQUESTSENSE");
    app_usbd_scsi_cmd_requestsense_t const * p_reqs = (const void *)p_msc_ctx->cbw.cdb;
    UNUSED_VARIABLE(p_reqs);

    if ((p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_requestsense_t)))
    {
        return status_unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.lun >= p_msc->specific.inst.block_devs_count)
    {
        return status_unsupported_start(p_inst);
    }

    if (uint32_decode(p_msc_ctx->cbw.datlen) > sizeof(app_usbd_scsi_cmd_requestsense_resp_t))
    {
        return status_unsupported_start(p_inst);
    }

    uint32_t resp_len = uint32_decode(p_msc_ctx->cbw.datlen);

    if (resp_len == 0)
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
                             resp_len,
                             APP_USBD_MSC_STATE_CMD_IN);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_FORMAT_UNIT handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_formatunit(app_usbd_class_inst_t const * p_inst,
                                 app_usbd_msc_t const        * p_msc,
                                 app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: FORMAT_UNIT");
    return status_unsupported_start(p_inst);
}


static ret_code_t cmd_read_start(app_usbd_class_inst_t const * p_inst,
                                 app_usbd_msc_t const        * p_msc,
                                 app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("cmd_read_start");
    ret_code_t ret;

    if (p_msc_ctx->current.process.datalen_left == 0)
    {
        NRF_LOG_WARNING("Transfer size 0 detected");
        return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_FAIL);
    }
    if (p_msc_ctx->current.process.size_left == 0)
    {
        NRF_LOG_WARNING("Read size 0 detected");
        return status_unsupported_start(p_inst);
    }
    if ((p_msc_ctx->cbw.flags & APP_USBD_MSC_CBW_DIRECTION_IN) == 0)
    {
        NRF_LOG_WARNING("Wrong transfer direction");
        return status_unsupported_start(p_inst);
    }

    msc_buff_clear(p_msc);
    if (p_msc_ctx->current.process.size_left > p_msc_ctx->current.process.datalen_left)
    {
        p_msc_ctx->current.process.size_left = p_msc_ctx->current.process.datalen_left;
        /* After transmitting required number of bytes - set error information */
        p_msc_ctx->csw.status                = APP_USBD_MSC_CSW_STATUS_PE;
    }
    p_msc_ctx->current.transfer.datalen_left = p_msc_ctx->current.process.datalen_left;
    p_msc_ctx->current.transfer.size_left    = p_msc_ctx->current.process.size_left;
    p_msc_ctx->current.transfer.pending      = false;
    p_msc_ctx->current.process. pending      = false;

    ret = read_blockmem_processor(p_inst);
    NRF_LOG_DEBUG("read_blockmem: id: %u, left: %u, datalen: %u, ret: %u",
                  p_msc_ctx->current.process.blk_idx,
                  p_msc_ctx->current.process.size_left,
                  p_msc_ctx->current.process.datalen_left,
                  ret);

    if (ret != NRF_SUCCESS)
    {
        UNUSED_RETURN_VALUE(status_unsupported_start(p_inst));
    }
    return ret;
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_READ6 handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_read6(app_usbd_class_inst_t const * p_inst,
                            app_usbd_msc_t const        * p_msc,
                            app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: READ6");
    app_usbd_scsi_cmd_read6_t const * p_read6 = (const void *)p_msc_ctx->cbw.cdb;
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_read6_t))
    {
        return status_unsupported_start(p_inst);
    }

    nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];
    uint32_t blk_size = nrf_blk_dev_geometry(p_blkd)->blk_size;
    uint8_t  blocks   = p_read6->xfrlen;

    p_msc_ctx->current.process.blk_idx   =
        ((p_read6->mslba & 0x1F) << 16) | uint16_big_decode(p_read6->lslba);
    p_msc_ctx->current.process.blk_size  = blk_size;
    p_msc_ctx->current.process.size_left = blocks * blk_size;

    return cmd_read_start(p_inst, p_msc, p_msc_ctx);
}


static ret_code_t cmd_write_start(app_usbd_class_inst_t const * p_inst,
                                  app_usbd_msc_t const        * p_msc,
                                  app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("cmd_write_start");
    ret_code_t ret;

    if (p_msc_ctx->current.process.datalen_left == 0)
    {
        NRF_LOG_WARNING("Transfer size 0 detected");
        return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_FAIL);
    }
    if (p_msc_ctx->current.process.size_left == 0)
    {
        NRF_LOG_WARNING("Write size 0 detected");
        return status_unsupported_start(p_inst);
    }
    if ((p_msc_ctx->cbw.flags & APP_USBD_MSC_CBW_DIRECTION_IN) != 0)
    {
        NRF_LOG_WARNING("Wrong transfer direction");
        return status_unsupported_start(p_inst);
    }

    msc_buff_clear(p_msc);
    if (p_msc_ctx->current.process.size_left > p_msc_ctx->current.process.datalen_left)
    {
        p_msc_ctx->current.process.size_left = p_msc_ctx->current.process.datalen_left;
        /* After transmitting required number of bytes - set error information */
        p_msc_ctx->csw.status                = APP_USBD_MSC_CSW_STATUS_PE;
    }
    p_msc_ctx->current.transfer.datalen_left = p_msc_ctx->current.process.datalen_left;
    p_msc_ctx->current.transfer.size_left    = p_msc_ctx->current.process.size_left;
    p_msc_ctx->current.transfer.pending      = false;
    p_msc_ctx->current.process. pending      = false;

    ret = write_transfer_processor(p_inst);
    NRF_LOG_DEBUG("write_blockrx: id: %u, left: %u, datalen: %u, ret: %u",
                  p_msc_ctx->current.process.blk_idx,
                  p_msc_ctx->current.process.size_left,
                  p_msc_ctx->current.process.datalen_left,
                  ret);

    if (ret != NRF_SUCCESS)
    {
        UNUSED_RETURN_VALUE(status_unsupported_start(p_inst));
    }
    return ret;
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_WRITE6 handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_write6(app_usbd_class_inst_t const * p_inst,
                             app_usbd_msc_t const        * p_msc,
                             app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: WRITE6");
    app_usbd_scsi_cmd_write6_t const * p_write6 = (const void *)p_msc_ctx->cbw.cdb;
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_write6_t))
    {
        return status_unsupported_start(p_inst);
    }

    nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];
    uint32_t blk_size = nrf_blk_dev_geometry(p_blkd)->blk_size;
    uint8_t  blocks   = p_write6->xfrlen;

    p_msc_ctx->current.process.blk_idx   =
        ((p_write6->mslba & 0x1F) << 16) | uint16_big_decode(p_write6->lslba);
    p_msc_ctx->current.process.blk_size  = blk_size;
    p_msc_ctx->current.process.size_left = blocks * blk_size;

    return cmd_write_start(p_inst, p_msc, p_msc_ctx);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_INQUIRY handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_inquiry(app_usbd_class_inst_t const * p_inst,
                              app_usbd_msc_t const        * p_msc,
                              app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: INQUIRY");
    app_usbd_scsi_cmd_inquiry_t const * p_inq = (const void *)p_msc_ctx->cbw.cdb;
    if (p_inq->pagecode != 0)
    {
        NRF_LOG_WARNING("unsupported pagecode");
        return status_unsupported_start(p_inst);
    }

    if (uint32_decode(p_msc_ctx->cbw.datlen) > sizeof(app_usbd_scsi_cmd_inquiry_resp_t))
    {
        return status_unsupported_start(p_inst);
    }

    uint32_t resp_len = uint32_decode(p_msc_ctx->cbw.datlen);

    if (resp_len == 0)
    {
        return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
    }


    p_msc_ctx->scsi_resp.inquiry.qualtype = APP_USBD_MSC_SCSI_INQ_QUAL_CONNECTED |
                                            APP_USBD_MSC_SCSI_INQ_TYPE_DIR_ACCESS;
    p_msc_ctx->scsi_resp.inquiry.flags1  = APP_USBD_MSC_SCSI_INQ_FLAG1_RMB;
    p_msc_ctx->scsi_resp.inquiry.version = APP_USBD_SCSI_INQ_VER_SPC4;
    p_msc_ctx->scsi_resp.inquiry.flags2  = APP_USBD_MSC_SCSI_INQ_FLAG2_RSP_SPC2 |
                                           APP_USBD_MSC_SCSI_INQ_FLAG2_HISUP;
    p_msc_ctx->scsi_resp.inquiry.len = sizeof(app_usbd_scsi_cmd_inquiry_resp_t) -
                                       offsetof(app_usbd_scsi_cmd_inquiry_resp_t, len);

    nrf_block_dev_t const * p_blkd =
        p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];
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
    else
    {
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
                             resp_len,
                             APP_USBD_MSC_STATE_CMD_IN);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_MODESELECT6 handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_modeselect6(app_usbd_class_inst_t const * p_inst,
                                  app_usbd_msc_t const        * p_msc,
                                  app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: MODESELECT6");
    return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_MODESENSE6 handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_modesense6(app_usbd_class_inst_t const * p_inst,
                                 app_usbd_msc_t const        * p_msc,
                                 app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: MODESENSE6");
    app_usbd_scsi_cmd_modesense6_t const * p_sense6 = (const void *)p_msc_ctx->cbw.cdb;
    UNUSED_VARIABLE(p_sense6);
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_modesense6_t))
    {
        return status_unsupported_start(p_inst);
    }

    if (uint32_decode(p_msc_ctx->cbw.datlen) > sizeof(app_usbd_scsi_cmd_modesense6_resp_t))
    {
        return status_unsupported_start(p_inst);
    }

    uint32_t resp_len = uint32_decode(p_msc_ctx->cbw.datlen);

    app_usbd_scsi_cmd_modesense6_resp_t * p_resp = &p_msc_ctx->scsi_resp.modesense6;
    p_resp->mdlen = sizeof(app_usbd_scsi_cmd_modesense6_resp_t) - 1;
    p_resp->type  = 0;
    p_resp->param = 0;
    p_resp->bdlen = 0;

    return transfer_in_start(p_inst,
                             &p_msc_ctx->scsi_resp,
                             resp_len,
                             APP_USBD_MSC_STATE_CMD_IN);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_STARTSTOPUNIT handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_startstopunit(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_msc_t const        * p_msc,
                                    app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: STARTSTOPUNIT");
    return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_SENDDIAGNOSTIC handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_senddiagnostic(app_usbd_class_inst_t const * p_inst,
                                     app_usbd_msc_t const        * p_msc,
                                     app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: SENDDIAGNOSTIC");
    return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_PREVENTMEDIAREMOVAL handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_preventremoval(app_usbd_class_inst_t const * p_inst,
                                     app_usbd_msc_t const        * p_msc,
                                     app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: PREVENTMEDIAREMOVAL");
    return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_READCAPACITY10 handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_readcapacity10(app_usbd_class_inst_t const * p_inst,
                                     app_usbd_msc_t const        * p_msc,
                                     app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: READCAPACITY10");

    app_usbd_scsi_cmd_readcapacity10_t const * p_cap10 = (const void *)p_msc_ctx->cbw.cdb;
    UNUSED_VARIABLE(p_cap10);
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_readcapacity10_t))
    {
        return status_unsupported_start(p_inst);
    }

    if (uint32_decode(p_msc_ctx->cbw.datlen) > sizeof(app_usbd_scsi_cmd_readcapacity10_resp_t))
    {
        return status_unsupported_start(p_inst);
    }

    uint32_t resp_len = uint32_decode(p_msc_ctx->cbw.datlen);

    if (resp_len == 0)
    {
        return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
    }

    nrf_block_dev_t const * p_blkd =
        p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];
    nrf_block_dev_geometry_t const * p_geometry = nrf_blk_dev_geometry(p_blkd);

    UNUSED_RETURN_VALUE(
        uint32_big_encode(p_geometry->blk_count - 1, p_msc_ctx->scsi_resp.readcapacity10.lba));
    UNUSED_RETURN_VALUE(
        uint32_big_encode(p_geometry->blk_size, p_msc_ctx->scsi_resp.readcapacity10.blklen));

    return transfer_in_start(p_inst,
                             &p_msc_ctx->scsi_resp,
                             resp_len,
                             APP_USBD_MSC_STATE_CMD_IN);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_READ10 handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_read10(app_usbd_class_inst_t const * p_inst,
                             app_usbd_msc_t const        * p_msc,
                             app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: READ10");
    app_usbd_scsi_cmd_read10_t const * p_read10 = (const void *)p_msc_ctx->cbw.cdb;
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_read10_t))
    {
        return status_unsupported_start(p_inst);
    }

    nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];
    uint32_t blk_size = nrf_blk_dev_geometry(p_blkd)->blk_size;
    uint16_t blocks   = uint16_big_decode(p_read10->xfrlen);

    p_msc_ctx->current.process.blk_idx   = uint32_big_decode(p_read10->lba);
    p_msc_ctx->current.process.blk_size  = blk_size;
    p_msc_ctx->current.process.size_left = blocks * blk_size;

    return cmd_read_start(p_inst, p_msc, p_msc_ctx);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_WRITE10 handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_write10(app_usbd_class_inst_t const * p_inst,
                              app_usbd_msc_t const        * p_msc,
                              app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: WRITE10");
    app_usbd_scsi_cmd_write10_t const * p_write10 = (const void *)p_msc_ctx->cbw.cdb;
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_write10_t))
    {
        return status_unsupported_start(p_inst);
    }

    nrf_block_dev_t const * p_blkd = p_msc->specific.inst.pp_block_devs[p_msc_ctx->cbw.lun];
    uint32_t blk_size = nrf_blk_dev_geometry(p_blkd)->blk_size;
    uint16_t blocks   = uint16_big_decode(p_write10->xfrlen);

    p_msc_ctx->current.process.blk_idx   = uint32_big_decode(p_write10->lba);
    p_msc_ctx->current.process.blk_size  = blk_size;
    p_msc_ctx->current.process.size_left = blocks * blk_size;

    return cmd_write_start(p_inst, p_msc, p_msc_ctx);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_MODESELECT10 handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_modeselect10(app_usbd_class_inst_t const * p_inst,
                                   app_usbd_msc_t const        * p_msc,
                                   app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: MODESELECT10");
    return csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
}


/**
 * @brief SCSI Command: @ref APP_USBD_SCSI_CMD_MODESENSE10 handle.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_msc         MSC instance.
 * @param[in] p_msc_ctx     MSC context.
 * @return Standard error code.
 * */
static ret_code_t cmd_modesense10(app_usbd_class_inst_t const * p_inst,
                                  app_usbd_msc_t const        * p_msc,
                                  app_usbd_msc_ctx_t          * p_msc_ctx)
{
    NRF_LOG_DEBUG("CMD: MODESENSE10");
    app_usbd_scsi_cmd_modesense10_t const * p_sense10 = (const void *)p_msc_ctx->cbw.cdb;
    UNUSED_VARIABLE(p_sense10);
    if (p_msc_ctx->cbw.cdb_length < sizeof(app_usbd_scsi_cmd_modesense10_t))
    {
        return status_unsupported_start(p_inst);
    }

    if (p_msc_ctx->cbw.lun >= p_msc->specific.inst.block_devs_count)
    {
        return status_unsupported_start(p_inst);
    }

    if (uint32_decode(p_msc_ctx->cbw.datlen) > sizeof(app_usbd_scsi_cmd_modesense6_resp_t))
    {
        return status_unsupported_start(p_inst);
    }

    uint32_t resp_len = uint32_decode(p_msc_ctx->cbw.datlen);

    app_usbd_scsi_cmd_modesense10_resp_t * p_resp = &p_msc_ctx->scsi_resp.modesense10;

    memset(p_resp, 0, sizeof(app_usbd_scsi_cmd_modesense10_resp_t));
    uint16_t len = sizeof(app_usbd_scsi_cmd_modesense10_resp_t) - sizeof(p_resp->mdlen);
    p_resp->mdlen[1] = len & 0xff;
    p_resp->mdlen[0] = (len >> 8) & 0xff;

    return transfer_in_start(p_inst,
                             &p_msc_ctx->scsi_resp,
                             resp_len,
                             APP_USBD_MSC_STATE_CMD_IN);
}


/**
 * @brief Get the size of the last OUT transfer.
 *
 * @param p_inst Generic class instance.
 *
 * @return Number of received bytes or 0 if none.
 */
static size_t get_last_out_size(app_usbd_class_inst_t const * p_inst)
{
    nrf_drv_usbd_ep_t ep = ep_out_addr_get(p_inst);
    size_t            size;
    ret_code_t        ret = nrf_drv_usbd_ep_status_get(ep, &size);

    if (ret != NRF_SUCCESS)
    {
        size = 0;
    }

    return size;
}


/**
 * @brief SCSI Command Block Wrapper handler.
 *
 * @param[in] p_inst    Generic class instance.
 * @return Standard error code.
 * */
static ret_code_t state_cbw(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);

    memset(&p_msc_ctx->current, 0, sizeof(p_msc_ctx->current));
    memset( p_msc_ctx->csw.tag, 0, sizeof(p_msc_ctx->csw.tag));

    /*Verify the transfer size*/
    if (get_last_out_size(p_inst) != sizeof(app_usbd_msc_cbw_t))
    {
        NRF_LOG_DEBUG("CMD: size error: %u", get_last_out_size(p_inst));
        status_cbwinvalid_start(p_inst);
        return NRF_SUCCESS;
    }

    /*Verify CBW signature*/
    if (memcmp(p_msc_ctx->cbw.signature,
               m_cbw_signature,
               sizeof(m_cbw_signature)) != 0)
    {
        NRF_LOG_DEBUG("CMD: header error: 0x%02x%02x%02x%02x",
                      p_msc_ctx->cbw.signature[0], p_msc_ctx->cbw.signature[1],
                      p_msc_ctx->cbw.signature[2], p_msc_ctx->cbw.signature[3]);

        status_cbwinvalid_start(p_inst);
        return NRF_SUCCESS;
    }

    /*Prepare the response*/
    memcpy(p_msc_ctx->csw.tag, p_msc_ctx->cbw.tag, sizeof(p_msc_ctx->csw.tag));
    p_msc_ctx->csw.status                   = APP_USBD_MSC_CSW_STATUS_PASS;
    p_msc_ctx->current.process.lun          = p_msc_ctx->cbw.lun;
    p_msc_ctx->current.process.datalen_left = uint32_decode(p_msc_ctx->cbw.datlen);

    if (p_msc_ctx->current.process.lun >= p_msc->specific.inst.block_devs_count)
    {
        NRF_LOG_WARNING("Unsupported LUN");
        return status_unsupported_start(p_inst);
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
            NRF_LOG_DEBUG("CMD: UNSUPPORTED");
            NRF_LOG_HEXDUMP_DEBUG(&(p_msc_ctx->cbw), sizeof(p_msc_ctx->cbw));
            if (uint32_decode(p_msc_ctx->cbw.datlen) != 0)
            {
                ret = status_unsupported_start(p_inst);
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
 * @brief Mark transfer block process.
 *
 * Common part of the @ref state_data_in_handle and @ref state_data_out_handle
 * that marks the current transfer state.
 *
 * @param p_msc_ctx  MSC context.
 * @param size       Number of bytes transfered.
 */
static void state_data_in_out_process(app_usbd_msc_ctx_t * p_msc_ctx, size_t size)
{
    p_msc_ctx->current.transfer.pending = false;
    p_msc_ctx->current.transfer.size_left =
        SUB_SAT0(p_msc_ctx->current.transfer.size_left, size);
    p_msc_ctx->current.transfer.datalen_left =
        SUB_SAT0(p_msc_ctx->current.transfer.datalen_left, size);
}

/**
 * @brief Handle read6/read10 command data stage.
 *
 * @param[in] p_inst Generic class instance.
 * @param[in] size   Number of bytes sent.
 *
 * @return Standard error code.
 */
static ret_code_t state_data_in_handle(app_usbd_class_inst_t const * p_inst, size_t size)
{
    ret_code_t ret;
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);

    NRF_LOG_DEBUG("APP_USBD_MSC_STATE_DATA_IN");
    /* For the in transfer direction, correctly transfered block have to match */
    ASSERT(current_size_calc(p_msc, p_msc_ctx->current.transfer.size_left) == size);
    /* Mark the fact the transfer block has been transfered */
    state_data_in_out_process(p_msc_ctx, size);
    msc_buff_free(p_msc);

    ret = read_transfer_processor(p_inst);
    if(ret == NRF_SUCCESS)
    {
        ret = read_blockmem_processor(p_inst);
    }
    if (ret != NRF_SUCCESS)
    {
        UNUSED_RETURN_VALUE(status_unsupported_start(p_inst));
    }
    return ret;
}


/**
 * @brief Endpoint IN event handler.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 */
static ret_code_t endpoint_in_event_handler(app_usbd_class_inst_t const  * p_inst,
                                            app_usbd_complex_evt_t const * p_event)
{
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);
    size_t                 size;

    NRF_LOG_DEBUG("state: %d, ep in event, status: %d",
                  p_msc_ctx->state,
                  p_event->drv_evt.data.eptransfer.status);

    if (NRF_SUCCESS != nrf_drv_usbd_ep_status_get(p_event->drv_evt.data.eptransfer.ep, &size))
    {
        size = 0;
    }

    if (p_event->drv_evt.data.eptransfer.status != NRF_USBD_EP_OK)
    {
        return NRF_SUCCESS;
    }

    ret_code_t ret = NRF_SUCCESS;

    switch (p_msc_ctx->state)
    {
        case APP_USBD_MSC_STATE_CMD_IN:
        {
            p_msc_ctx->current.process.datalen_left -= size;
            ret = csw_wait_start(p_inst, APP_USBD_MSC_CSW_STATUS_PASS);
            break;
        }

        case APP_USBD_MSC_STATE_DATA_IN:
        {
            ret = state_data_in_handle(p_inst, size);
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
 * @brief Handle write6/write10 command data stage.
 *
 * @param[in] p_inst Generic class instance.
 * @param[in] size   Number of bytes received.
 *
 * @return Standard error code.
 * @retval NRF_SUCCESS              Request handled correctly.
 * @retval NRF_ERROR_NOT_SUPPORTED  Request is not supported.
 */
static ret_code_t state_data_out_handle(app_usbd_class_inst_t const * p_inst, size_t size)
{
    ret_code_t ret      = NRF_SUCCESS;
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);

    NRF_LOG_DEBUG("APP_USBD_MSC_STATE_DATA_OUT");
    /* For the OUT transfer direction we may get less than we expected */
    if (current_size_calc(p_msc, p_msc_ctx->current.transfer.size_left) != size)
    {
        p_msc_ctx->current.process.abort = true;
    }
    /* Mark the fact the transfer block has been transfered */
    state_data_in_out_process(p_msc_ctx, size);
    msc_buff_put(p_msc);

    ret = write_transfer_processor(p_inst);
    if(ret == NRF_SUCCESS)
    {
        ret = write_blockmem_processor(p_inst);
    }
    if (ret != NRF_SUCCESS)
    {
        UNUSED_RETURN_VALUE(status_unsupported_start(p_inst));
    }
    return ret;
}


/**
 * @brief Endpoint OUT event handler.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 * @retval NRF_SUCCESS              Request handled correctly.
 * @retval NRF_ERROR_NOT_SUPPORTED  Request is not supported.
 */
static ret_code_t endpoint_out_event_handler(app_usbd_class_inst_t const  * p_inst,
                                             app_usbd_complex_evt_t const * p_event)
{
    ret_code_t ret = NRF_SUCCESS;
    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);
    size_t                 size;

    NRF_LOG_DEBUG("state: %d, ep out event, status: %d",
                  p_msc_ctx->state,
                  p_event->drv_evt.data.eptransfer.status);

    if (NRF_SUCCESS != nrf_drv_usbd_ep_status_get(p_event->drv_evt.data.eptransfer.ep, &size))
    {
        size = 0;
    }

    if (p_event->drv_evt.data.eptransfer.status == NRF_USBD_EP_WAITING)
    {
        if (p_msc_ctx->state == APP_USBD_MSC_STATE_DATA_OUT)
        {
            NRF_LOG_DEBUG("NRF_USBD_EP_WAITING");
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
        NRF_LOG_ERROR("Data overload");

        switch (p_msc_ctx->state)
        {
            case APP_USBD_MSC_STATE_DATA_OUT:
            {
                status_deverror_start(p_inst);
                break;
            }

            /* Default action is the same like CBW - stall totally until bulk reset */
            case APP_USBD_MSC_STATE_CBW:
            default:
            {
                status_cbwinvalid_start(p_inst);
                break;
            }
        }
        return NRF_SUCCESS;
    }
    else /*NRF_USBD_EP_OK*/
    {
        switch (p_msc_ctx->state)
        {
            case APP_USBD_MSC_STATE_CBW:
            {
                ret = state_cbw(p_inst);
                break;
            }

            case APP_USBD_MSC_STATE_DATA_OUT:
            {
                CRITICAL_REGION_ENTER();
                ret = state_data_out_handle(p_inst, size);
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
                ret = NRF_ERROR_NOT_SUPPORTED;
                break;
            }
        }
    }

    NRF_LOG_DEBUG("Ep proc status: %d", ret);
    return ret;
}


/**
 * @brief @ref app_usbd_class_methods_t::event_handler
 */
static ret_code_t msc_event_handler(app_usbd_class_inst_t const  * p_inst,
                                    app_usbd_complex_evt_t const * p_event)
{
    ASSERT(p_inst != NULL);
    ASSERT(p_event != NULL);

    app_usbd_msc_t const * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t   * p_msc_ctx = msc_ctx_get(p_msc);

    UNUSED_VARIABLE(p_msc);
    UNUSED_VARIABLE(p_msc_ctx);

    ret_code_t ret = NRF_SUCCESS;

    switch (p_event->app_evt.type)
    {
        case APP_USBD_EVT_DRV_SOF:
            break;

        case APP_USBD_EVT_DRV_RESET:
            /* Initialize */
            memset(p_msc_ctx, 0, sizeof(app_usbd_msc_csw_t));
            /* Configure the CSW signature as it should never be changed when software works */
            memcpy(p_msc_ctx->csw.signature, m_csw_signature, sizeof(m_csw_signature));
            break;

        case APP_USBD_EVT_DRV_SETUP:
            ret = setup_event_handler(p_inst, (app_usbd_setup_evt_t const *)p_event);
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

            break;
        }

        case APP_USBD_EVT_INST_REMOVE:
        {
            break;
        }

        case APP_USBD_EVT_STARTED:
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

        case APP_USBD_EVT_STOPPED:
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
 * @brief @ref app_usbd_class_methods_t::feed_descriptors
 */

static bool msc_feed_descriptors(app_usbd_class_descriptor_ctx_t * p_ctx,
                                 app_usbd_class_inst_t const     * p_inst,
                                 uint8_t                         * p_buff,
                                 size_t                            max_size)
{
    static uint8_t ifaces   = 0;
    ifaces = app_usbd_class_iface_count_get(p_inst);
    app_usbd_msc_t const * p_msc = msc_get(p_inst);

    APP_USBD_CLASS_DESCRIPTOR_BEGIN(p_ctx, p_buff, max_size);

    static uint8_t i = 0;

    for (i = 0; i < ifaces; i++)
    {
        /* INTERFACE DESCRIPTOR */
        APP_USBD_CLASS_DESCRIPTOR_WRITE(0x09);                          // bLength
        APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_INTERFACE); // bDescriptorType = Interface

        static app_usbd_class_iface_conf_t const * p_cur_iface = NULL;
        p_cur_iface = app_usbd_class_iface_get(p_inst, i);

        APP_USBD_CLASS_DESCRIPTOR_WRITE(app_usbd_class_iface_number_get(p_cur_iface)); // bInterfaceNumber
        APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bAlternateSetting
        APP_USBD_CLASS_DESCRIPTOR_WRITE(app_usbd_class_iface_ep_count_get(p_cur_iface)); // bNumEndpoints
        APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_MSC_CLASS); // bInterfaceClass = MSC
        APP_USBD_CLASS_DESCRIPTOR_WRITE(p_msc->specific.inst.subclass); // bInterfaceSubclass (Industry Standard Command Block)
        APP_USBD_CLASS_DESCRIPTOR_WRITE(p_msc->specific.inst.protocol); // bInterfaceProtocol
        APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // iInterface


        static uint8_t endpoints = 0;
        endpoints = app_usbd_class_iface_ep_count_get(p_cur_iface);

        static uint8_t j = 0;

        for (j = 0; j < endpoints; j++)
        {
            // ENDPOINT DESCRIPTOR
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x07); // bLength
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_ENDPOINT); // bDescriptorType = Endpoint

            static app_usbd_class_ep_conf_t const * p_cur_ep = NULL;
            p_cur_ep = app_usbd_class_iface_ep_get(p_cur_iface, j);
            APP_USBD_CLASS_DESCRIPTOR_WRITE(app_usbd_class_ep_address_get(p_cur_ep)); // bEndpointAddress
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_EP_ATTR_TYPE_BULK); // bmAttributes
            APP_USBD_CLASS_DESCRIPTOR_WRITE(LSB_16(NRF_DRV_USBD_EPSIZE)); // wMaxPacketSize LSB
            APP_USBD_CLASS_DESCRIPTOR_WRITE(MSB_16(NRF_DRV_USBD_EPSIZE)); // wMaxPacketSize MSB
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bInterval
        }

    }

    APP_USBD_CLASS_DESCRIPTOR_END();
}

const app_usbd_class_methods_t app_usbd_msc_class_methods = {
    .event_handler    = msc_event_handler,
    .feed_descriptors = msc_feed_descriptors,
};

/**
 * @brief Mark block device process.
 *
 * Common part of the @ref msc_blockdev_read_done_handler and @ref msc_blockdev_write_done_handler
 * that marks the current processing state.
 *
 * @param p_blk_dev     Block device handle.
 * @param p_event       Block device event.
 */
static void msc_blockdev_done_process(nrf_block_dev_t const       * p_blk_dev,
                                      nrf_block_dev_event_t const * p_event)
{
    app_usbd_class_inst_t const * p_inst    = p_event->p_context;
    app_usbd_msc_t const        * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t          * p_msc_ctx = msc_ctx_get(p_msc);

    uint32_t blk_count = p_event->p_blk_req->blk_count;
    uint32_t size      = blk_count * p_msc_ctx->current.process.blk_size;

    p_msc_ctx->current.process.blk_idx   += blk_count;
    p_msc_ctx->current.process.size_left =
        SUB_SAT0(p_msc_ctx->current.process.size_left, size);
    p_msc_ctx->current.process.datalen_left =
        SUB_SAT0(p_msc_ctx->current.process.datalen_left, size);

    p_msc_ctx->current.process.pending = false;
}

/**
 * @brief Block device read done event handler.
 *
 * @ref NRF_BLOCK_DEV_EVT_BLK_READ_DONE
 *
 * @param p_blk_dev     Block device handle.
 * @param p_event       Block device event.
 *
 * */
static void msc_blockdev_read_done_handler(nrf_block_dev_t const       * p_blk_dev,
                                           nrf_block_dev_event_t const * p_event)
{
    ret_code_t ret;
    app_usbd_class_inst_t const * p_inst    = p_event->p_context;
    app_usbd_msc_t const        * p_msc     = msc_get(p_inst);
    app_usbd_msc_ctx_t          * p_msc_ctx = msc_ctx_get(p_msc);

    NRF_LOG_DEBUG("read_done_handler: p_buff: %p, size: %u",
                  (uint32_t)p_event->p_blk_req->p_buff,
                  p_event->p_blk_req->blk_count);

    msc_buff_put(p_msc);
    if (p_event->result == NRF_BLOCK_DEV_RESULT_SUCCESS)
    {
        msc_blockdev_done_process(p_blk_dev, p_event);
    }
    else
    {
        p_msc_ctx->current.transfer.abort = true;
    }


    ret = read_transfer_processor(p_inst);
    if(ret == NRF_SUCCESS)
    {
        ret = read_blockmem_processor(p_inst);
    }
    if (ret != NRF_SUCCESS)
    {
        UNUSED_RETURN_VALUE(status_unsupported_start(p_inst));
    }
}


/**
 * @brief Block device write done event handler.
 *
 * @ref NRF_BLOCK_DEV_EVT_BLK_WRITE_DONE
 *
 * @param p_blk_dev     Block device handle.
 * @param p_event       Block device event.
 *
 * */
static void msc_blockdev_write_done_handler(nrf_block_dev_t const       * p_blk_dev,
                                            nrf_block_dev_event_t const * p_event)
{
    ret_code_t ret;
    app_usbd_class_inst_t const * p_inst    = p_event->p_context;
    app_usbd_msc_t const        * p_msc     = msc_get(p_inst);

    NRF_LOG_DEBUG("write_done_handler: p_buff: %p, size: %u",
                  (uint32_t)p_event->p_blk_req->p_buff,
                  p_event->p_blk_req->blk_count);

    msc_buff_free(p_msc);
    if (p_event->result == NRF_BLOCK_DEV_RESULT_SUCCESS)
    {
        msc_blockdev_done_process(p_blk_dev, p_event);
    }
    else
    {
        UNUSED_RETURN_VALUE(status_unsupported_start(p_inst));
    }

    ret = write_transfer_processor(p_inst);
    if(ret == NRF_SUCCESS)
    {
        ret = write_blockmem_processor(p_inst);
    }
    if (ret != NRF_SUCCESS)
    {
        UNUSED_RETURN_VALUE(status_unsupported_start(p_inst));
    }
}


/**
 * @brief Block device event handler.
 *
 * Mass storage block device event handler. Need to be pined to all block devices
 * from initializer list.
 *
 * @param p_blk_dev     Block device handle.
 * @param p_event       Block device event.
 *
 * */
static void msc_blockdev_ev_handler(nrf_block_dev_t const       * p_blk_dev,
                                    nrf_block_dev_event_t const * p_event)
{
    switch (p_event->ev_type)
    {
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

/** @} */

bool app_usbd_msc_sync(app_usbd_msc_t const * p_msc)
{
    bool       rc  = true;
    ret_code_t ret = NRF_SUCCESS;

    for (size_t i = 0; i < p_msc->specific.inst.block_devs_count; ++i)
    {
        nrf_block_dev_t const * p_blkd            = p_msc->specific.inst.pp_block_devs[i];
        bool                    flush_in_progress = true;

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


#endif //NRF_MODULE_ENABLED(APP_USBD_MSC)
