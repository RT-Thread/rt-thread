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
#if NRF_MODULE_ENABLED(APP_USBD_CDC_ACM)

#include "app_usbd_cdc_acm.h"
#include <inttypes.h>

/**
 * @defgroup app_usbd_cdc_acm_internal CDC ACM internals
 * @{
 * @ingroup app_usbd_cdc
 * @internal
 */


#define NRF_LOG_MODULE_NAME cdc_acm

#if APP_USBD_CDC_ACM_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       APP_USBD_CDC_ACM_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  APP_USBD_CDC_ACM_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR APP_USBD_CDC_ACM_CONFIG_DEBUG_COLOR
#else //APP_USBD_CDC_ACM_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif //APP_USBD_CDC_ACM_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define APP_USBD_CDC_ACM_COMM_IFACE_IDX 0    /**< CDC ACM class comm interface index. */
#define APP_USBD_CDC_ACM_DATA_IFACE_IDX 1    /**< CDC ACM class data interface index. */

#define APP_USBD_CDC_ACM_COMM_EPIN_IDX  0    /**< CDC ACM comm class endpoint IN index. */
#define APP_USBD_CDC_ACM_DATA_EPIN_IDX  0    /**< CDC ACM data class endpoint IN index. */
#define APP_USBD_CDC_ACM_DATA_EPOUT_IDX 1    /**< CDC ACM data class endpoint OUT index. */

/**
 * @brief Auxiliary function to access cdc_acm class instance data.
 *
 * @param[in] p_inst Class instance data.
 *
 * @return CDC ACM class instance.
 */
static inline app_usbd_cdc_acm_t const * cdc_acm_get(app_usbd_class_inst_t const * p_inst)
{
    ASSERT(p_inst != NULL);
    return (app_usbd_cdc_acm_t const *)p_inst;
}

/**
 * @brief Auxiliary function to access cdc_acm class context data.
 *
 * @param[in] p_cdc_acm    CDC ACM class instance data.
 *
 * @return CDC ACM class instance context.
 */
static inline app_usbd_cdc_acm_ctx_t * cdc_acm_ctx_get(app_usbd_cdc_acm_t const * p_cdc_acm)
{
    ASSERT(p_cdc_acm != NULL);
    ASSERT(p_cdc_acm->specific.p_data != NULL);
    return &p_cdc_acm->specific.p_data->ctx;
}

/**
 * @brief User event handler.
 *
 * @param[in] p_inst        Class instance.
 * @param[in] event user    Event type.
 */
static inline void user_event_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_cdc_acm_user_event_t event)
{
    app_usbd_cdc_acm_t const * p_cdc_acm = cdc_acm_get(p_inst);
    if (p_cdc_acm->specific.inst.user_ev_handler != NULL)
    {
        p_cdc_acm->specific.inst.user_ev_handler(p_inst, event);
    }
}

/**
 * @brief Auxiliary function to access CDC ACM COMM IN endpoint address.
 *
 * @param[in] p_inst Class instance data.
 *
 * @return IN endpoint address.
 */
static inline nrf_drv_usbd_ep_t comm_ep_in_addr_get(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_class_iface_conf_t const * class_iface;
    class_iface = app_usbd_class_iface_get(p_inst, APP_USBD_CDC_ACM_COMM_IFACE_IDX);

    app_usbd_class_ep_conf_t const * ep_cfg;
    ep_cfg = app_usbd_class_iface_ep_get(class_iface, APP_USBD_CDC_ACM_COMM_EPIN_IDX);

    return app_usbd_class_ep_address_get(ep_cfg);
}

/**
 * @brief Auxiliary function to access CDC ACM DATA IN endpoint address.
 *
 * @param[in] p_inst Class instance data.
 *
 * @return IN endpoint address.
 */
static inline nrf_drv_usbd_ep_t data_ep_in_addr_get(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_class_iface_conf_t const * class_iface;
    class_iface = app_usbd_class_iface_get(p_inst, APP_USBD_CDC_ACM_DATA_IFACE_IDX);

    app_usbd_class_ep_conf_t const * ep_cfg;
    ep_cfg = app_usbd_class_iface_ep_get(class_iface, APP_USBD_CDC_ACM_DATA_EPIN_IDX);

    return app_usbd_class_ep_address_get(ep_cfg);
}

/**
 * @brief Auxiliary function to access CDC ACM DATA OUT endpoint address.
 *
 * @param[in] p_inst Class instance data.
 *
 * @return OUT endpoint address.
 */
static inline nrf_drv_usbd_ep_t data_ep_out_addr_get(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_class_iface_conf_t const * class_iface;
    class_iface = app_usbd_class_iface_get(p_inst, APP_USBD_CDC_ACM_DATA_IFACE_IDX);

    app_usbd_class_ep_conf_t const * ep_cfg;
    ep_cfg = app_usbd_class_iface_ep_get(class_iface, APP_USBD_CDC_ACM_DATA_EPOUT_IDX);

    return app_usbd_class_ep_address_get(ep_cfg);
}

/**
 * @brief Internal SETUP standard IN request handler.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 */
static ret_code_t setup_req_std_in(app_usbd_class_inst_t const * p_inst,
                                   app_usbd_setup_evt_t const *  p_setup_ev)
{
    /* Only Get Descriptor standard IN request is supported by CDC class */
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
 */
static ret_code_t setup_req_std_out(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_setup_evt_t const *  p_setup_ev)
{

    switch (p_setup_ev->setup.bRequest)
    {
        default:
            break;
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
 */
static ret_code_t setup_req_class_in(app_usbd_class_inst_t const * p_inst,
                                     app_usbd_setup_evt_t const *  p_setup_ev)
{
    app_usbd_cdc_acm_t const * p_cdc_acm = cdc_acm_get(p_inst);
    app_usbd_cdc_acm_ctx_t *   p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);

    switch (p_setup_ev->setup.bRequest)
    {
        case APP_USBD_CDC_REQ_GET_LINE_CODING:
        {
            if (p_setup_ev->setup.wLength.w != sizeof(app_usbd_cdc_line_coding_t))
            {
                return NRF_ERROR_NOT_SUPPORTED;
            }

            return app_usbd_core_setup_rsp(&p_setup_ev->setup,
                                           &p_cdc_acm_ctx->line_coding,
                                           sizeof(app_usbd_cdc_line_coding_t));
        }
        default:
            break;
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Class specific OUT request data callback.
 *
 * @param status    Endpoint status.
 * @param p_context Context of transfer (set by @ref app_usbd_core_setup_data_handler_set).
 *
 * @return Standard error code.
 */
static ret_code_t cdc_acm_req_out_data_cb(nrf_drv_usbd_ep_status_t status, void * p_context)
{
    if (status != NRF_USBD_EP_OK)
    {
        return NRF_ERROR_INTERNAL;
    }

    app_usbd_cdc_acm_t const * p_cdc_acm = p_context;
    app_usbd_cdc_acm_ctx_t *   p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);

    switch (p_cdc_acm_ctx->request.type)
    {
        case APP_USBD_CDC_REQ_SET_LINE_CODING:
        {
            memcpy(&p_cdc_acm_ctx->line_coding,
                   &p_cdc_acm_ctx->request.payload.line_coding,
                   sizeof(app_usbd_cdc_line_coding_t));

            NRF_LOG_INFO("REQ_SET_LINE_CODING: baudrate: %"PRIu32", databits: %u, "
                    "format: %u, parity: %u",
                    uint32_decode(p_cdc_acm_ctx->line_coding.dwDTERate),
                    p_cdc_acm_ctx->line_coding.bDataBits,
                    p_cdc_acm_ctx->line_coding.bCharFormat,
                    p_cdc_acm_ctx->line_coding.bParityType);
            break;
        }
        default:
            return NRF_ERROR_NOT_SUPPORTED;
    }

    return NRF_SUCCESS;
}


/**
 * @brief Class specific request data stage setup.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 */
static ret_code_t cdc_acm_req_out_datastage(app_usbd_class_inst_t const * p_inst,
                                            app_usbd_setup_evt_t const *  p_setup_ev)
{
    app_usbd_cdc_acm_t const * p_cdc_acm = cdc_acm_get(p_inst);
    app_usbd_cdc_acm_ctx_t *   p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);

    p_cdc_acm_ctx->request.type = p_setup_ev->setup.bRequest;
    p_cdc_acm_ctx->request.len = p_setup_ev->setup.wLength.w;

    /*Request setup data*/
    NRF_DRV_USBD_TRANSFER_OUT(transfer,
                              &p_cdc_acm_ctx->request.payload,
                              p_cdc_acm_ctx->request.len);
    ret_code_t ret;
    CRITICAL_REGION_ENTER();
    ret = app_usbd_ep_transfer(NRF_DRV_USBD_EPOUT0, &transfer);
    if (ret == NRF_SUCCESS)
    {
        const app_usbd_core_setup_data_handler_desc_t desc = {
                .handler = cdc_acm_req_out_data_cb,
                .p_context = (void*)p_cdc_acm
        };

        ret = app_usbd_core_setup_data_handler_set(NRF_DRV_USBD_EPOUT0, &desc);
    }
    CRITICAL_REGION_EXIT();

    return ret;
}

/**
 * @brief Reset port to default state.
 *
 * @param p_inst Generic class instance.
 */
static void cdc_acm_reset_port(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_cdc_acm_t const * p_cdc_acm = cdc_acm_get(p_inst);
    app_usbd_cdc_acm_ctx_t *   p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);

    p_cdc_acm_ctx->line_state = 0;

    // Set rx transfers configuration to default state.
    p_cdc_acm_ctx->rx_transfer[0].p_buf = NULL;
    p_cdc_acm_ctx->rx_transfer[1].p_buf = NULL;
    p_cdc_acm_ctx->bytes_left = 0;
    p_cdc_acm_ctx->bytes_read = 0;
    p_cdc_acm_ctx->last_read  = 0;
    p_cdc_acm_ctx->cur_read   = 0;
    p_cdc_acm_ctx->p_copy_pos = p_cdc_acm_ctx->internal_rx_buf;
}

/**
 * @brief Internal SETUP class OUT request handler.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 */
static ret_code_t setup_req_class_out(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_setup_evt_t const *  p_setup_ev)
{
    app_usbd_cdc_acm_t const * p_cdc_acm = cdc_acm_get(p_inst);
    app_usbd_cdc_acm_ctx_t *   p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);

    switch (p_setup_ev->setup.bRequest)
    {
        case APP_USBD_CDC_REQ_SET_LINE_CODING:
        {
            if (p_setup_ev->setup.wLength.w != sizeof(app_usbd_cdc_line_coding_t))
            {
                return NRF_ERROR_NOT_SUPPORTED;
            }

            return cdc_acm_req_out_datastage(p_inst, p_setup_ev);
        }
        case APP_USBD_CDC_REQ_SET_CONTROL_LINE_STATE:
        {
            if (p_setup_ev->setup.wLength.w != 0)
            {
                return NRF_ERROR_NOT_SUPPORTED;
            }

            NRF_LOG_INFO("REQ_SET_CONTROL_LINE_STATE: 0x%x", p_setup_ev->setup.wValue.w);

            bool old_dtr = (p_cdc_acm_ctx->line_state & APP_USBD_CDC_ACM_LINE_STATE_DTR) ?
                            true : false;
            p_cdc_acm_ctx->line_state = p_setup_ev->setup.wValue.w;

            bool new_dtr = (p_cdc_acm_ctx->line_state & APP_USBD_CDC_ACM_LINE_STATE_DTR) ?
                            true : false;

            if (old_dtr == new_dtr)
            {
                return NRF_SUCCESS;
            }

            const app_usbd_cdc_acm_user_event_t ev = new_dtr ?
                  APP_USBD_CDC_ACM_USER_EVT_PORT_OPEN : APP_USBD_CDC_ACM_USER_EVT_PORT_CLOSE;

            user_event_handler(p_inst, ev);

            if (!new_dtr)
            {
                /*Abort DATA endpoints on port close */
                nrf_drv_usbd_ep_t ep;
                ep = data_ep_in_addr_get(p_inst);
                nrf_drv_usbd_ep_abort(ep);
                ep = data_ep_out_addr_get(p_inst);
                nrf_drv_usbd_ep_abort(ep);

                // Set rx transfers configuration to default state.
                p_cdc_acm_ctx->rx_transfer[0].p_buf = NULL;
                p_cdc_acm_ctx->rx_transfer[1].p_buf = NULL;
                p_cdc_acm_ctx->bytes_left = 0;
                p_cdc_acm_ctx->bytes_read = 0;
                p_cdc_acm_ctx->last_read  = 0;
                p_cdc_acm_ctx->cur_read   = 0;
                p_cdc_acm_ctx->p_copy_pos = p_cdc_acm_ctx->internal_rx_buf;
            }

            return NRF_SUCCESS;
        }
        default:
            break;
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Control endpoint handler.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 */
static ret_code_t setup_event_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_setup_evt_t const *  p_setup_ev)
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
 * @brief CDC ACM consumer.
 *
 * @note See @ref nrf_drv_usbd_consumer_t
 */
static bool cdc_acm_consumer(nrf_drv_usbd_ep_transfer_t * p_next,
                             void *                       p_context,
                             size_t                       ep_size,
                             size_t                       data_size)
{
    app_usbd_cdc_acm_ctx_t * p_cdc_acm_ctx = (app_usbd_cdc_acm_ctx_t *) p_context;
    p_next->size = data_size;

    if (data_size <= p_cdc_acm_ctx->rx_transfer[0].read_left)
    {
        p_next->p_data.rx = p_cdc_acm_ctx->rx_transfer[0].p_buf;

        p_cdc_acm_ctx->rx_transfer[0].p_buf     += data_size;
        p_cdc_acm_ctx->bytes_read               += data_size;
        p_cdc_acm_ctx->rx_transfer[0].read_left -= data_size;
        NRF_LOG_DEBUG("Received %d bytes. Space left in user buffer: %d bytes.",
                      data_size,
                      p_cdc_acm_ctx->rx_transfer[0].read_left);
        return (p_cdc_acm_ctx->rx_transfer[0].read_left) != 0;
    }
    else
    {
        p_next->p_data.rx = p_cdc_acm_ctx->internal_rx_buf;

        p_cdc_acm_ctx->cur_read = data_size;
        NRF_LOG_DEBUG("Received %d bytes. Stored in internal buffer.", data_size);
        return false;
    }
}

/**
 * @brief CDC ACM single transfer consumer.
 *
 * This function finalizes transfer after any received block.
 *
 * @note See @ref nrf_drv_usbd_consumer_t
 */
static bool cdc_acm_single_shoot_consumer(nrf_drv_usbd_ep_transfer_t * p_next,
                                          void *                       p_context,
                                          size_t                       ep_size,
                                          size_t                       data_size)
{
    app_usbd_cdc_acm_ctx_t * p_cdc_acm_ctx = (app_usbd_cdc_acm_ctx_t *) p_context;
    p_next->size = data_size;

    if (data_size <= p_cdc_acm_ctx->rx_transfer[0].read_left)
    {
        p_next->p_data.rx = p_cdc_acm_ctx->rx_transfer[0].p_buf;

        p_cdc_acm_ctx->bytes_read               = data_size;
        p_cdc_acm_ctx->rx_transfer[0].read_left = data_size;
        NRF_LOG_DEBUG("Received %d bytes. Space left in user buffer: %d bytes.",
                      data_size,
                      p_cdc_acm_ctx->rx_transfer[0].read_left);
    }
    else
    {
        p_next->p_data.rx = p_cdc_acm_ctx->internal_rx_buf;
        p_cdc_acm_ctx->cur_read = data_size;
        NRF_LOG_DEBUG("Received %d bytes. Stored in internal buffer.", data_size);
    }

    return false;
}

/**
 * @brief Manage switching between user buffers and copying data from internal buffer.
 *
 * @param p_inst  Generic USB class instance.
 *
 * @return Standard error code.
 */
static ret_code_t cdc_acm_rx_block_finished(app_usbd_class_inst_t const *  p_inst)
{
    app_usbd_cdc_acm_t const * p_cdc_acm     = cdc_acm_get(p_inst);
    app_usbd_cdc_acm_ctx_t *   p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);
    nrf_drv_usbd_ep_t          ep            = data_ep_out_addr_get(p_inst);

    nrf_drv_usbd_handler_desc_t handler_desc = {
        .handler.consumer = cdc_acm_consumer,
        .p_context        = p_cdc_acm_ctx
    };

    if (p_cdc_acm_ctx->rx_transfer[0].read_left == 0) // Buffer completely filled by consumer
    {
        p_cdc_acm_ctx->last_read  = p_cdc_acm_ctx->bytes_read;
        p_cdc_acm_ctx->bytes_read = 0;
        p_cdc_acm_ctx->bytes_left = 0;

        if (p_cdc_acm_ctx->rx_transfer[1].p_buf != NULL)
        {
            p_cdc_acm_ctx->rx_transfer[0]       = p_cdc_acm_ctx->rx_transfer[1];
            p_cdc_acm_ctx->rx_transfer[1].p_buf = NULL;
            return app_usbd_ep_handled_transfer(ep, &handler_desc);
        }
        else
        {
            p_cdc_acm_ctx->rx_transfer[0].p_buf = NULL;
            return NRF_SUCCESS;
        }
    }

    size_t bytes_read   = p_cdc_acm_ctx->cur_read;
    size_t bytes_to_cpy = bytes_read;

    if (bytes_read > p_cdc_acm_ctx->rx_transfer[0].read_left)
    {
        bytes_to_cpy = p_cdc_acm_ctx->rx_transfer[0].read_left;
    }
    memcpy(p_cdc_acm_ctx->rx_transfer[0].p_buf,
           p_cdc_acm_ctx->internal_rx_buf,
           bytes_to_cpy);

    // First buffer is full
    p_cdc_acm_ctx->last_read  = p_cdc_acm_ctx->bytes_read + bytes_to_cpy;
    p_cdc_acm_ctx->bytes_read = 0;
    p_cdc_acm_ctx->bytes_left = bytes_read - bytes_to_cpy;
    p_cdc_acm_ctx->p_copy_pos = p_cdc_acm_ctx->internal_rx_buf + bytes_to_cpy;

    if (p_cdc_acm_ctx->rx_transfer[1].p_buf != NULL)
    {
        // If there is second transfer, copy it to first
        p_cdc_acm_ctx->rx_transfer[0]       = p_cdc_acm_ctx->rx_transfer[1];
        p_cdc_acm_ctx->rx_transfer[1].p_buf = NULL;

        while (p_cdc_acm_ctx->bytes_left > 0)
        {

            if (p_cdc_acm_ctx->bytes_left >= p_cdc_acm_ctx->rx_transfer[0].read_left)
            {
                // If there are enough bytes left in internal buffer to completely fill next transfer,
                // we call user event handler to obtain next buffer and continue double buffering.
                memcpy(p_cdc_acm_ctx->rx_transfer[0].p_buf,
                       p_cdc_acm_ctx->p_copy_pos,
                       p_cdc_acm_ctx->rx_transfer[0].read_left);

                p_cdc_acm_ctx->bytes_left -= p_cdc_acm_ctx->rx_transfer[0].read_left;
                p_cdc_acm_ctx->p_copy_pos += p_cdc_acm_ctx->rx_transfer[0].read_left;
                p_cdc_acm_ctx->last_read = p_cdc_acm_ctx->rx_transfer[0].read_left;
                user_event_handler(p_inst, APP_USBD_CDC_ACM_USER_EVT_RX_DONE);

                if (p_cdc_acm_ctx->rx_transfer[1].p_buf != NULL)
                {
                    p_cdc_acm_ctx->rx_transfer[0]       = p_cdc_acm_ctx->rx_transfer[1];
                    p_cdc_acm_ctx->rx_transfer[1].p_buf = NULL;
                }
                else
                {
                    // If user does not specify a second buffer, all data transfers are done
                    // and data left in internal buffer is lost.
                    p_cdc_acm_ctx->rx_transfer[0].p_buf = NULL;
                    break;
                }
            }
            else
            {
                memcpy(p_cdc_acm_ctx->rx_transfer[0].p_buf,
                       p_cdc_acm_ctx->p_copy_pos,
                       p_cdc_acm_ctx->bytes_left);
                p_cdc_acm_ctx->bytes_read = p_cdc_acm_ctx->bytes_left;

                p_cdc_acm_ctx->rx_transfer[0].read_left -= p_cdc_acm_ctx->bytes_left;
                p_cdc_acm_ctx->rx_transfer[0].p_buf     += p_cdc_acm_ctx->bytes_left;
                break;
            }
        }


    }
    else
    {
        p_cdc_acm_ctx->rx_transfer[0].p_buf = NULL;
    }

    if (p_cdc_acm_ctx->rx_transfer[0].p_buf != NULL)
    {
        return app_usbd_ep_handled_transfer(ep, &handler_desc);
    }
    return NRF_SUCCESS;
}

/**
 * @brief Class specific endpoint transfer handler.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 */
static ret_code_t cdc_acm_endpoint_ev(app_usbd_class_inst_t const *  p_inst,
                                      app_usbd_complex_evt_t const * p_event)
{
    if (comm_ep_in_addr_get(p_inst) == p_event->drv_evt.data.eptransfer.ep)
    {
        NRF_LOG_INFO("EPIN_COMM: notify");
        return NRF_SUCCESS;
    }
    ret_code_t ret;
    if (NRF_USBD_EPIN_CHECK(p_event->drv_evt.data.eptransfer.ep))
    {
        switch (p_event->drv_evt.data.eptransfer.status)
        {
            case NRF_USBD_EP_OK:
                NRF_LOG_INFO("EPIN_DATA: %02x done", p_event->drv_evt.data.eptransfer.ep);
                user_event_handler(p_inst, APP_USBD_CDC_ACM_USER_EVT_TX_DONE);
                return NRF_SUCCESS;
            case NRF_USBD_EP_ABORTED:
                return NRF_SUCCESS;
            default:
                return NRF_ERROR_INTERNAL;
        }
    }

    if (NRF_USBD_EPOUT_CHECK(p_event->drv_evt.data.eptransfer.ep))
    {
        switch (p_event->drv_evt.data.eptransfer.status)
        {
            case NRF_USBD_EP_OK:
                ret = cdc_acm_rx_block_finished(p_inst);
                NRF_LOG_INFO("EPOUT_DATA: %02x done", p_event->drv_evt.data.eptransfer.ep);
                user_event_handler(p_inst, APP_USBD_CDC_ACM_USER_EVT_RX_DONE);
                return ret;
            case NRF_USBD_EP_WAITING:
            case NRF_USBD_EP_ABORTED:
                return NRF_SUCCESS;
            default:
                return NRF_ERROR_INTERNAL;
        }
    }

    return NRF_ERROR_NOT_SUPPORTED;
}


/**
 * @brief @ref app_usbd_class_methods_t::event_handler
 */
static ret_code_t cdc_acm_event_handler(app_usbd_class_inst_t const *  p_inst,
                                        app_usbd_complex_evt_t const * p_event)
{
    ASSERT(p_inst != NULL);
    ASSERT(p_event != NULL);

    ret_code_t ret = NRF_SUCCESS;
    switch (p_event->app_evt.type)
    {
        case APP_USBD_EVT_DRV_SOF:
            break;
        case APP_USBD_EVT_DRV_RESET:
            cdc_acm_reset_port(p_inst);
            break;
        case APP_USBD_EVT_DRV_SETUP:
            ret  = setup_event_handler(p_inst, (app_usbd_setup_evt_t const *)p_event);
            break;
        case APP_USBD_EVT_DRV_EPTRANSFER:
            ret = cdc_acm_endpoint_ev(p_inst, p_event);
            break;
        case APP_USBD_EVT_DRV_SUSPEND:
            break;
        case APP_USBD_EVT_DRV_RESUME:
            break;
        case APP_USBD_EVT_INST_APPEND:
            break;
        case APP_USBD_EVT_INST_REMOVE:
            break;
        case APP_USBD_EVT_STARTED:
            break;
        case APP_USBD_EVT_STOPPED:
            break;
        case APP_USBD_EVT_POWER_REMOVED:
            cdc_acm_reset_port(p_inst);
            break;
        default:
            ret = NRF_ERROR_NOT_SUPPORTED;
            break;
    }

    return ret;
}


static bool cdc_acm_feed_descriptors(app_usbd_class_descriptor_ctx_t * p_ctx,
                                     app_usbd_class_inst_t const     * p_inst,
                                     uint8_t                         * p_buff,
                                     size_t                            max_size)
{
    static uint8_t ifaces    = 0;
    ifaces = app_usbd_class_iface_count_get(p_inst);
    app_usbd_cdc_acm_t const * p_cdc_acm = cdc_acm_get(p_inst);

    APP_USBD_CLASS_DESCRIPTOR_BEGIN(p_ctx, p_buff, max_size);

    /* INTERFACE ASSOCIATION DESCRIPTOR */
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x08); // bLength
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_INTERFACE_ASSOCIATION); // bDescriptorType = Interface Association
    APP_USBD_CLASS_DESCRIPTOR_WRITE(p_cdc_acm->specific.inst.comm_interface); // bFirstInterface
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x02); // bInterfaceCount
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_CDC_COMM_CLASS); // bFunctionClass
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_CDC_SUBCLASS_ACM); // bFunctionSubClass
    APP_USBD_CLASS_DESCRIPTOR_WRITE(p_cdc_acm->specific.inst.protocol); // bFunctionProtocol
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // iFunction

    static uint8_t i = 0;

    for (i = 0; i < ifaces; i++)
    {
        /* INTERFACE DESCRIPTOR */
        APP_USBD_CLASS_DESCRIPTOR_WRITE(0x09); // bLength
        APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_INTERFACE); // bDescriptorType = Interface

        static app_usbd_class_iface_conf_t const * p_cur_iface = NULL;
        p_cur_iface = app_usbd_class_iface_get(p_inst, i);

        APP_USBD_CLASS_DESCRIPTOR_WRITE(app_usbd_class_iface_number_get(p_cur_iface)); // bInterfaceNumber
        APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bAlternateSetting
        APP_USBD_CLASS_DESCRIPTOR_WRITE(app_usbd_class_iface_ep_count_get(p_cur_iface)); // bNumEndpoints

        if (p_cdc_acm->specific.inst.comm_interface == app_usbd_class_iface_number_get(p_cur_iface))
        {
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_CDC_COMM_CLASS); // bInterfaceClass = CDC COMM
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_CDC_SUBCLASS_ACM); // bInterfaceSubclass
            APP_USBD_CLASS_DESCRIPTOR_WRITE(p_cdc_acm->specific.inst.protocol); // bInterfaceProtocol
        }
        else if (p_cdc_acm->specific.inst.data_interface ==
                 app_usbd_class_iface_number_get(p_cur_iface))
        {
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_CDC_DATA_CLASS); // bInterfaceClass = CDC DATA
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bInterfaceSubclass
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bInterfaceProtocol
        }
        else
        {
            ASSERT(0);
        }

        APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // iInterface

        if (p_cdc_acm->specific.inst.comm_interface == app_usbd_class_iface_number_get(p_cur_iface))
        {
            /* HEADER DESCRIPTOR */
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x05); // bLength
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_CDC_CS_INTERFACE); // bDescriptorType = Class Specific Interface
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_CDC_SCS_HEADER); // bDescriptorSubtype = Header Functional Descriptor
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x10); // bcdCDC LSB
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x01); // bcdCDC MSB

            /* CALL MANAGEMENT DESCRIPTOR */
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x05); // bLength
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_CDC_CS_INTERFACE); // bDescriptorType = Class Specific Interface
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_CDC_SCS_CALL_MGMT); // bDescriptorSubtype = Call Management Functional Descriptor
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x03); // bmCapabilities
            APP_USBD_CLASS_DESCRIPTOR_WRITE(p_cdc_acm->specific.inst.data_interface); // bDataInterface

            /* ABSTRACT CONTROL MANAGEMENT DESCRIPTOR */
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x04); // bLength
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_CDC_CS_INTERFACE); // bDescriptorType = Class Specific Interface
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_CDC_SCS_ACM); // bDescriptorSubtype = Abstract Control Management Functional Descriptor
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x02); // bmCapabilities

            /* UNION DESCRIPTOR */
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x05);
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_CDC_CS_INTERFACE); // bDescriptorType = Class Specific Interface
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_CDC_SCS_UNION); // bDescriptorSubtype = Union Functional Descriptor
            APP_USBD_CLASS_DESCRIPTOR_WRITE(p_cdc_acm->specific.inst.comm_interface); // bControlInterface
            APP_USBD_CLASS_DESCRIPTOR_WRITE(p_cdc_acm->specific.inst.data_interface); // bSubordinateInterface
        }
        else if (p_cdc_acm->specific.inst.data_interface ==
                 app_usbd_class_iface_number_get(p_cur_iface))
        {
            ;
        }
        else
        {
            ASSERT(0);
        }

        /* ENDPOINT DESCRIPTORS */
        static uint8_t endpoints = 0;
        endpoints = app_usbd_class_iface_ep_count_get(p_cur_iface);

        static uint8_t j = 0;

        for (j = 0; j < endpoints; j++)
        {
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x07);                         // bLength
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_ENDPOINT); // bDescriptorType = Endpoint

            static app_usbd_class_ep_conf_t const * p_cur_ep = NULL;
            p_cur_ep = app_usbd_class_iface_ep_get(p_cur_iface, j);
            APP_USBD_CLASS_DESCRIPTOR_WRITE(app_usbd_class_ep_address_get(p_cur_ep)); // bEndpointAddress

            if (p_cdc_acm->specific.inst.comm_interface ==
                app_usbd_class_iface_number_get(p_cur_iface))
            {
                APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_EP_ATTR_TYPE_INTERRUPT); // bmAttributes
            }
            else if (p_cdc_acm->specific.inst.data_interface ==
                     app_usbd_class_iface_number_get(p_cur_iface))
            {
                APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_EP_ATTR_TYPE_BULK); // bmAttributes
            }
            else
            {
                ASSERT(0);
            }

            APP_USBD_CLASS_DESCRIPTOR_WRITE(LSB_16(NRF_DRV_USBD_EPSIZE)); // wMaxPacketSize LSB
            APP_USBD_CLASS_DESCRIPTOR_WRITE(MSB_16(NRF_DRV_USBD_EPSIZE)); // wMaxPacketSize MSB

            if (p_cdc_acm->specific.inst.comm_interface ==
                app_usbd_class_iface_number_get(p_cur_iface))
            {
                APP_USBD_CLASS_DESCRIPTOR_WRITE(p_cdc_acm->specific.inst.p_ep_interval[0]); // bInterval
            }
            else if (p_cdc_acm->specific.inst.data_interface ==
                     app_usbd_class_iface_number_get(p_cur_iface))
            {
                APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bInterval
            }
            else
            {
                ASSERT(0);
            }

        }

    }

    APP_USBD_CLASS_DESCRIPTOR_END();
}

/**
 * @brief Public cdc_acm class interface.
 *
 */
const app_usbd_class_methods_t app_usbd_cdc_acm_class_methods = {
        .event_handler = cdc_acm_event_handler,
        .feed_descriptors = cdc_acm_feed_descriptors,
};

/** @} */

ret_code_t app_usbd_cdc_acm_write(app_usbd_cdc_acm_t const * p_cdc_acm,
                                  const void *               p_buf,
                                  size_t                     length)
{
    app_usbd_class_inst_t const * p_inst = app_usbd_cdc_acm_class_inst_get(p_cdc_acm);
    app_usbd_cdc_acm_ctx_t * p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);

    bool dtr_state = (p_cdc_acm_ctx->line_state & APP_USBD_CDC_ACM_LINE_STATE_DTR) ?
                      true : false;
    if (!dtr_state)
    {
        /*Port is not opened*/
        return NRF_ERROR_INVALID_STATE;
    }
    
    nrf_drv_usbd_ep_t ep = data_ep_in_addr_get(p_inst);
    
    if (APP_USBD_CDC_ACM_ZLP_ON_EPSIZE_WRITE && ((length % NRF_DRV_USBD_EPSIZE) == 0))
    {
        NRF_DRV_USBD_TRANSFER_IN_ZLP(transfer, p_buf, length);
        return app_usbd_ep_transfer(ep, &transfer);
    }
    else
    {
        NRF_DRV_USBD_TRANSFER_IN(transfer, p_buf, length);
        return app_usbd_ep_transfer(ep, &transfer);
    }
}

size_t app_usbd_cdc_acm_rx_size(app_usbd_cdc_acm_t const * p_cdc_acm)
{
    app_usbd_cdc_acm_ctx_t * p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);

    return p_cdc_acm_ctx->last_read;
}

size_t app_usbd_cdc_acm_bytes_stored(app_usbd_cdc_acm_t const * p_cdc_acm)
{
    app_usbd_cdc_acm_ctx_t * p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);

    return p_cdc_acm_ctx->bytes_left;
}

ret_code_t app_usbd_cdc_acm_read(app_usbd_cdc_acm_t const * p_cdc_acm,
                                 void *                     p_buf,
                                 size_t                     length)
{
    ASSERT(p_buf != NULL);
    ret_code_t ret;
    app_usbd_cdc_acm_ctx_t * p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);

    if (0U == (p_cdc_acm_ctx->line_state & APP_USBD_CDC_ACM_LINE_STATE_DTR))
    {
        /*Port is not opened*/
        return NRF_ERROR_INVALID_STATE;
    }

#if (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE == 0)
    CRITICAL_REGION_ENTER();
#endif // (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE == 0)

    if (p_cdc_acm_ctx->rx_transfer[0].p_buf == NULL)
    {
        if (p_cdc_acm_ctx->bytes_left >= length)
        {
            memcpy(p_buf, p_cdc_acm_ctx->p_copy_pos, length);
            p_cdc_acm_ctx->bytes_left -= length;
            p_cdc_acm_ctx->p_copy_pos += length;
            p_cdc_acm_ctx->last_read   = length;
            ret = NRF_SUCCESS;
        }
        else
        {
            p_cdc_acm_ctx->rx_transfer[0].p_buf     = p_buf;
            p_cdc_acm_ctx->rx_transfer[0].read_left = length;
            nrf_drv_usbd_ep_t ep = data_ep_out_addr_get(app_usbd_cdc_acm_class_inst_get(p_cdc_acm));
            nrf_drv_usbd_handler_desc_t const handler_desc = {
                .handler.consumer = cdc_acm_consumer,
                .p_context        = p_cdc_acm_ctx
            };

            if (p_cdc_acm_ctx->bytes_left > 0)
            {
                memcpy(p_cdc_acm_ctx->rx_transfer[0].p_buf,
                       p_cdc_acm_ctx->p_copy_pos,
                       p_cdc_acm_ctx->bytes_left);
                p_cdc_acm_ctx->rx_transfer[0].read_left -= p_cdc_acm_ctx->bytes_left;
                p_cdc_acm_ctx->rx_transfer[0].p_buf     += p_cdc_acm_ctx->bytes_left;
                p_cdc_acm_ctx->bytes_read = p_cdc_acm_ctx->bytes_left;
                p_cdc_acm_ctx->bytes_left = 0;

            }
            ret = app_usbd_ep_handled_transfer(ep, &handler_desc);
            if (ret == NRF_SUCCESS)
            {
                ret = NRF_ERROR_IO_PENDING;
            }
        }
    }
    else if (p_cdc_acm_ctx->rx_transfer[1].p_buf == NULL)
    {
        p_cdc_acm_ctx->rx_transfer[1].p_buf     = p_buf;
        p_cdc_acm_ctx->rx_transfer[1].read_left = length;
        ret = NRF_ERROR_IO_PENDING;
    }
    else
    {
        ret = NRF_ERROR_BUSY;
    }
#if (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE == 0)
    CRITICAL_REGION_EXIT();
#endif // (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE == 0)

    return ret;
}

ret_code_t app_usbd_cdc_acm_read_any(app_usbd_cdc_acm_t const * p_cdc_acm,
                                     void *                     p_buf,
                                     size_t                     length)
{
    ASSERT(p_buf != NULL);
    ret_code_t ret;
    app_usbd_cdc_acm_ctx_t * p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);

    if (0U == (p_cdc_acm_ctx->line_state & APP_USBD_CDC_ACM_LINE_STATE_DTR))
    {
        /*Port is not opened*/
        return NRF_ERROR_INVALID_STATE;
    }

#if (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE == 0)
    CRITICAL_REGION_ENTER();
#endif // (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE == 0)
    if (p_cdc_acm_ctx->bytes_left > 0)
    {
        size_t to_copy = MIN(length, p_cdc_acm_ctx->bytes_left);
        memcpy(p_buf, p_cdc_acm_ctx->p_copy_pos, to_copy);
        p_cdc_acm_ctx->bytes_left -= to_copy;
        p_cdc_acm_ctx->p_copy_pos += to_copy;
        p_cdc_acm_ctx->last_read   = to_copy;
        ret = NRF_SUCCESS;
    }
    else
    {
        if (p_cdc_acm_ctx->rx_transfer[0].p_buf == NULL)
        {
            p_cdc_acm_ctx->rx_transfer[0].p_buf     = p_buf;
            p_cdc_acm_ctx->rx_transfer[0].read_left = length;
            nrf_drv_usbd_ep_t ep = data_ep_out_addr_get(app_usbd_cdc_acm_class_inst_get(p_cdc_acm));
            nrf_drv_usbd_handler_desc_t const handler_desc = {
               .handler.consumer = cdc_acm_single_shoot_consumer,
               .p_context        = p_cdc_acm_ctx
            };

            ret = app_usbd_ep_handled_transfer(ep, &handler_desc);
            if (ret == NRF_SUCCESS)
            {
                ret = NRF_ERROR_IO_PENDING;
            }
        }
        else
        {
            ret = NRF_ERROR_BUSY;
        }
    }

#if (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE == 0)
    CRITICAL_REGION_EXIT();
#endif // (APP_USBD_CONFIG_EVENT_QUEUE_ENABLE == 0)

    return ret;
}

static ret_code_t cdc_acm_serial_state_notify(app_usbd_cdc_acm_t const * p_cdc_acm)
{
    app_usbd_class_inst_t const * p_inst = app_usbd_cdc_acm_class_inst_get(p_cdc_acm);
    app_usbd_cdc_acm_ctx_t *      p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);

    nrf_drv_usbd_ep_t ep = comm_ep_in_addr_get(p_inst);

    NRF_DRV_USBD_TRANSFER_OUT(transfer,
                              &p_cdc_acm_ctx->request.payload,
                              sizeof(app_usbd_cdc_acm_notify_t));
    return app_usbd_ep_transfer(ep, &transfer);
}

ret_code_t app_usbd_cdc_acm_serial_state_notify(app_usbd_cdc_acm_t const *      p_cdc_acm,
                                                app_usbd_cdc_acm_serial_state_t serial_state,
                                                bool                            value)
{
    app_usbd_cdc_acm_ctx_t * p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);

    ret_code_t ret;
    CRITICAL_REGION_ENTER();
    ret = NRF_SUCCESS;
    switch (serial_state)
    {
        case APP_USBD_CDC_ACM_SERIAL_STATE_DCD:
        case APP_USBD_CDC_ACM_SERIAL_STATE_DSR:
        case APP_USBD_CDC_ACM_SERIAL_STATE_BREAK:
        case APP_USBD_CDC_ACM_SERIAL_STATE_RING:
        case APP_USBD_CDC_ACM_SERIAL_STATE_FRAMING:
        case APP_USBD_CDC_ACM_SERIAL_STATE_PARITY:
        case APP_USBD_CDC_ACM_SERIAL_STATE_OVERRUN:

            if (value)
            {
                p_cdc_acm_ctx->serial_state |= serial_state;
            }
            else
            {
                p_cdc_acm_ctx->serial_state &= ~serial_state;
            }

            break;
        default:
            ret = NRF_ERROR_NOT_SUPPORTED;
            break;
    }

    if (ret == NRF_SUCCESS)
    {
        app_usbd_cdc_acm_notify_t * notify = &p_cdc_acm_ctx->request.payload.notify;
        notify->cdc_notify.bmRequestType = app_usbd_setup_req_val(APP_USBD_SETUP_REQREC_INTERFACE,
                                                                  APP_USBD_SETUP_REQTYPE_CLASS,
                                                                  APP_USBD_SETUP_REQDIR_IN);
        notify->cdc_notify.bRequest = APP_USBD_CDC_NOTIF_SERIAL_STATE;
        notify->cdc_notify.wValue = 0;
        notify->cdc_notify.wIndex = 0;
        notify->cdc_notify.wLength = sizeof(notify->serial_state);

        notify->serial_state = p_cdc_acm_ctx->serial_state;

        ret = cdc_acm_serial_state_notify(p_cdc_acm);
    }
    CRITICAL_REGION_EXIT();

    return ret;
}

ret_code_t app_usbd_cdc_acm_line_state_get(app_usbd_cdc_acm_t const *    p_cdc_acm,
                                           app_usbd_cdc_acm_line_state_t line_state,
                                           uint32_t *                    value)
{
    app_usbd_cdc_acm_ctx_t * p_cdc_acm_ctx = cdc_acm_ctx_get(p_cdc_acm);

    ret_code_t ret;
    CRITICAL_REGION_ENTER();
    ret = NRF_SUCCESS;
    switch (line_state)
    {
        case APP_USBD_CDC_ACM_LINE_STATE_DTR:
        case APP_USBD_CDC_ACM_LINE_STATE_RTS:
            *value = (p_cdc_acm_ctx->line_state & line_state) != 0;
            break;
        default:
            ret = NRF_ERROR_NOT_SUPPORTED;
            break;
    }
    CRITICAL_REGION_EXIT();

    return ret;
}

#endif //NRF_MODULE_ENABLED(APP_USBD_CDC_ACM)
