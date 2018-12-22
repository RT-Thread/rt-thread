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
#if APP_USBD_CLASS_AUDIO_ENABLED
#include "app_usbd_audio.h"
#include "app_util_platform.h"

/**
 * @defgroup app_usbd_audio_internals USBD Audio internals
 * @{
 * @ingroup app_usbd_audio
 * @internal
 */

STATIC_ASSERT(sizeof(app_usbd_audio_ac_iface_header_desc_t) == 8);
STATIC_ASSERT(sizeof(app_usbd_audio_input_terminal_desc_t) == 12);
STATIC_ASSERT(sizeof(app_usbd_audio_output_terminal_desc_t) == 9);
STATIC_ASSERT(sizeof(app_usbd_audio_feature_unit_desc_t) == 6);
STATIC_ASSERT(sizeof(app_usbd_audio_as_iface_desc_t) == 7);
STATIC_ASSERT(sizeof(app_usbd_audio_as_format_type_one_desc_t) == 8);
STATIC_ASSERT(sizeof(app_usbd_audio_as_format_type_two_desc_t) == 9);
STATIC_ASSERT(sizeof(app_usbd_audio_as_format_type_three_desc_t) == 8);
STATIC_ASSERT(sizeof(app_usbd_audio_as_endpoint_desc_t) == 7);

#define APP_USBD_AUDIO_CONTROL_IFACE_IDX    0  /**< Audio class control interface index */
#define APP_USBD_AUDIO_STREAMING_IFACE_IDX  1  /**< Audio class streaming interface index */

#define APP_USBD_CDC_AUDIO_STREAMING_EP_IDX 0  /**< Audio streaming isochronous endpoint index */

/**
 * @brief Auxiliary function to access audio class instance data
 *
 * @param[in] p_inst Class instance data
 * @return Audio class instance data @ref app_usbd_audio_t
 */
static inline app_usbd_audio_t const * audio_get(app_usbd_class_inst_t const * p_inst)
{
    ASSERT(p_inst != NULL);
    return (app_usbd_audio_t const *)p_inst;
}

/**
 * @brief Auxiliary function to access audio class context data
 *
 * @param[in] p_audio    Audio class instance data
 * @return Audio class context data @ref app_usbd_audio_ctx_t
 */
static inline app_usbd_audio_ctx_t * audio_ctx_get(app_usbd_audio_t const * p_audio)
{
    ASSERT(p_audio != NULL);
    ASSERT(p_audio->specific.p_data != NULL);
    return &p_audio->specific.p_data->ctx;
}


/**
 * @brief User event handler
 *
 * @param[in] p_inst        Class instance
 * @param[in] event user    Event type @ref app_usbd_audio_user_event_t
 * */
static inline void user_event_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_audio_user_event_t event)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);
    if (p_audio->specific.inst.user_ev_handler != NULL)
    {
        p_audio->specific.inst.user_ev_handler(p_inst, event);
    }
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
                                   app_usbd_setup_evt_t const * p_setup_ev)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);
    app_usbd_audio_ctx_t *   p_audio_ctx = audio_ctx_get(p_audio);

    switch (p_setup_ev->setup.bmRequest)
    {
        case APP_USBD_SETUP_STDREQ_GET_DESCRIPTOR:
        {
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

            break;
        }
        case APP_USBD_SETUP_STDREQ_GET_INTERFACE:
        {

            size_t tx_maxsize;
            uint8_t * p_tx_buff = app_usbd_core_setup_transfer_buff_get(&tx_maxsize);

            p_tx_buff[0] = p_audio_ctx->streaming ? 1 : 0;

            return app_usbd_core_setup_rsp(&p_setup_ev->setup,
                                           p_tx_buff,
                                           sizeof(uint8_t));
        }
        default:
            break;
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
                                    app_usbd_setup_evt_t const * p_setup_ev)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);
    app_usbd_audio_ctx_t *   p_audio_ctx = audio_ctx_get(p_audio);

    switch (p_setup_ev->setup.bmRequest)
    {
        case APP_USBD_SETUP_STDREQ_SET_INTERFACE:
        {
            uint8_t iface_count = app_usbd_class_iface_count_get(p_inst);
            app_usbd_class_iface_conf_t const * p_iface = NULL;
            for (uint8_t j = 0; j < iface_count; ++j)
            {
                p_iface = app_usbd_class_iface_get(p_inst, j);
                if (p_iface->number == p_setup_ev->setup.wIndex.w)
                {
                    break;
                }
            }

            if (p_iface == NULL)
            {
                break;
            }

            p_audio_ctx->streaming = (p_iface->ep_cnt > 0) &&
                                     (p_setup_ev->setup.wValue.w == 1);

            return app_usbd_req_std_set_interface(p_inst, p_setup_ev);
        }
        default:
            break;
    }

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
                                     app_usbd_setup_evt_t const * p_setup_ev)
{
    switch (p_setup_ev->setup.bmRequest)
    {
        case APP_USBD_AUDIO_REQ_GET_CUR:
        case APP_USBD_AUDIO_REQ_GET_MIN:
        case APP_USBD_AUDIO_REQ_GET_MAX:
        case APP_USBD_AUDIO_REQ_SET_RES:
        case APP_USBD_AUDIO_REQ_GET_MEM:
        {
            app_usbd_audio_t const * p_audio = audio_get(p_inst);
            app_usbd_audio_ctx_t *   p_audio_ctx = audio_ctx_get(p_audio);


            p_audio_ctx->request.req_type = (app_usbd_audio_req_type_t)p_setup_ev->setup.bmRequest;
            p_audio_ctx->request.control = p_setup_ev->setup.wValue.hb;
            p_audio_ctx->request.channel = p_setup_ev->setup.wValue.lb;
            p_audio_ctx->request.interface = p_setup_ev->setup.wIndex.hb;
            p_audio_ctx->request.entity = p_setup_ev->setup.wIndex.lb;

            p_audio_ctx->request.length = p_setup_ev->setup.wLength.w;

            p_audio_ctx->request.req_target = APP_USBD_AUDIO_CLASS_REQ_IN;

            app_usbd_setup_reqrec_t rec = app_usbd_setup_req_rec(p_setup_ev->setup.bmRequestType);
            if (rec == APP_USBD_SETUP_REQREC_ENDPOINT)
            {
                p_audio_ctx->request.req_target = APP_USBD_AUDIO_EP_REQ_IN;
            }

            user_event_handler((app_usbd_class_inst_t const *)p_audio,
                                APP_USBD_AUDIO_USER_EVT_CLASS_REQ);

            return app_usbd_core_setup_rsp(&p_setup_ev->setup,
                                            p_audio_ctx->request.payload,
                                            p_audio_ctx->request.length);
        }
        default:
            break;
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

static ret_code_t audio_req_out_data_cb(nrf_drv_usbd_ep_status_t status, void * p_context)
{
    if(status == NRF_USBD_EP_OK)
    {
        app_usbd_audio_t const * p_audio = p_context;

        user_event_handler((app_usbd_class_inst_t const *)p_audio,
                            APP_USBD_AUDIO_USER_EVT_CLASS_REQ);
    }

    return NRF_SUCCESS;
}

static ret_code_t audio_req_out(app_usbd_class_inst_t const * p_inst,
                                app_usbd_setup_evt_t const * p_setup_ev)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);
    app_usbd_audio_ctx_t *   p_audio_ctx = audio_ctx_get(p_audio);


    p_audio_ctx->request.req_type = (app_usbd_audio_req_type_t)p_setup_ev->setup.bmRequest;
    p_audio_ctx->request.control = p_setup_ev->setup.wValue.hb;
    p_audio_ctx->request.channel = p_setup_ev->setup.wValue.lb;
    p_audio_ctx->request.interface = p_setup_ev->setup.wIndex.hb;
    p_audio_ctx->request.entity = p_setup_ev->setup.wIndex.lb;

    p_audio_ctx->request.length = p_setup_ev->setup.wLength.w;

    p_audio_ctx->request.req_target = APP_USBD_AUDIO_CLASS_REQ_OUT;
    if (app_usbd_setup_req_rec(p_setup_ev->setup.bmRequestType) == APP_USBD_SETUP_REQREC_ENDPOINT)
    {
        p_audio_ctx->request.req_target = APP_USBD_AUDIO_EP_REQ_OUT;
    }

    /*Request setup data*/
    NRF_DRV_USBD_TRANSFER_OUT(transfer, p_audio_ctx->request.payload, p_audio_ctx->request.length);
    ret_code_t ret;
    CRITICAL_REGION_ENTER();
    ret = app_usbd_core_setup_data_transfer(NRF_DRV_USBD_EPOUT0, &transfer);
    if (ret == NRF_SUCCESS)
    {
        app_usbd_core_setup_data_handler_desc_t desc = {
                .handler = audio_req_out_data_cb,
                .p_context = (void*)p_audio
        };

        ret = app_usbd_core_setup_data_handler_set(NRF_DRV_USBD_EPOUT0, &desc);
    }
    CRITICAL_REGION_EXIT();

    return ret;
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
                                      app_usbd_setup_evt_t const * p_setup_ev)
{
    switch (p_setup_ev->setup.bmRequest)
    {
        case APP_USBD_AUDIO_REQ_SET_CUR:
        case APP_USBD_AUDIO_REQ_SET_MIN:
        case APP_USBD_AUDIO_REQ_SET_MAX:
        case APP_USBD_AUDIO_REQ_SET_RES:
        case APP_USBD_AUDIO_REQ_SET_MEM:
            return audio_req_out(p_inst, p_setup_ev);
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
                                      app_usbd_setup_evt_t const * p_setup_ev)
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
 * @brief Endpoint IN event handler
 *
 * @param[in] p_inst        Generic class instance
 *
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t endpoint_in_event_handler(app_usbd_class_inst_t const * p_inst)
{
    user_event_handler(p_inst, APP_USBD_AUDIO_USER_EVT_TX_DONE);
    return NRF_SUCCESS;
}


/**
 * @brief Endpoint OUT event handler
 *
 * @param[in] p_inst        Generic class instance
 *
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t endpoint_out_event_handler(app_usbd_class_inst_t const * p_inst)
{
    user_event_handler(p_inst, APP_USBD_AUDIO_USER_EVT_RX_DONE);
    return NRF_SUCCESS;
}

/**
* @brief Auxiliary function to access isochronous endpoint address
*
* @param[in] p_inst Class instance data
*
* @return ISO endpoint address
*/
static inline nrf_drv_usbd_ep_t ep_iso_addr_get(app_usbd_class_inst_t const * p_inst)
{
   app_usbd_class_iface_conf_t const * class_iface;
   class_iface = app_usbd_class_iface_get(p_inst, APP_USBD_AUDIO_STREAMING_IFACE_IDX);

   app_usbd_class_ep_conf_t const * ep_cfg;
   ep_cfg = app_usbd_class_iface_ep_get(class_iface, APP_USBD_CDC_AUDIO_STREAMING_EP_IDX);

   return app_usbd_class_ep_address_get(ep_cfg);
}

static ret_code_t sof_event_handler(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);
    app_usbd_audio_ctx_t *   p_audio_ctx = audio_ctx_get(p_audio);

    nrf_drv_usbd_ep_t ep_addr = ep_iso_addr_get(p_inst);

    if (app_usbd_core_state_get() != APP_USB_STATE_BASE(APP_USBD_STATE_Configured))
    {
        return NRF_SUCCESS;
    }

    if (!p_audio_ctx->streaming)
    {
        return NRF_SUCCESS;
    }

    /*OUT transfers*/
    if (p_audio_ctx->rx_size && NRF_USBD_EPOUT_CHECK(ep_addr))
    {

        ASSERT(NRF_USBD_EPISO_CHECK(ep_addr));

        uint32_t isoout = nrf_usbd_epout_size_get(ep_addr);
        if (isoout)
        {
            ASSERT(isoout == p_audio_ctx->rx_size);
            NRF_DRV_USBD_TRANSFER_OUT(transfer, p_audio_ctx->p_rx_buff, p_audio_ctx->rx_size);
            return app_usbd_core_ep_transfer(ep_addr, &transfer);
        }
    }

    /*IN transfers*/
    if (p_audio_ctx->tx_size && NRF_USBD_EPIN_CHECK(ep_addr))
    {
        ASSERT(NRF_USBD_EPISO_CHECK(ep_addr));
        NRF_DRV_USBD_TRANSFER_IN(transfer, p_audio_ctx->p_tx_buff, p_audio_ctx->tx_size);
        return app_usbd_core_ep_transfer(ep_addr, &transfer);
    }

    return NRF_SUCCESS;
}




/**
 * @brief @ref app_usbd_class_methods_t::event_handler
 */
static ret_code_t audio_event_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_complex_evt_t const * p_event)
{
    ASSERT(p_inst != NULL);
    ASSERT(p_event != NULL);

    ret_code_t ret = NRF_SUCCESS;
    switch (p_event->app_evt.type)
    {
        case APP_USBD_EVT_DRV_SOF:
            ret = sof_event_handler(p_inst);
            break;
        case APP_USBD_EVT_DRV_RESET:
            break;
        case APP_USBD_EVT_DRV_SETUP:
            ret  = setup_event_handler(p_inst, (app_usbd_setup_evt_t const *)p_event);
            break;
        case APP_USBD_EVT_DRV_EPTRANSFER:
            if (NRF_USBD_EPIN_CHECK(p_event->drv_evt.data.eptransfer.ep))
            {
                ret = endpoint_in_event_handler(p_inst);
            }
            else
            {
                ret = endpoint_out_event_handler(p_inst);
            }
            break;
        case APP_USBD_EVT_DRV_SUSPEND:
            break;
        case APP_USBD_EVT_DRV_RESUME:
            break;
        case APP_USBD_EVT_INST_APPEND:
        {
            ret = app_usbd_class_sof_register(p_inst);
            break;
        }
        case APP_USBD_EVT_INST_REMOVE:
        {
            ret = app_usbd_class_sof_unregister(p_inst);
            break;
        }
        case APP_USBD_EVT_START:
            break;
        case APP_USBD_EVT_STOP:
            break;
        default:
            ret = NRF_ERROR_NOT_SUPPORTED;
            break;
    }

    return ret;
}

/**
 * @brief @ref app_usbd_class_methods_t::get_descriptors
 */
static const void * audio_get_descriptors(app_usbd_class_inst_t const * p_inst,
                                          size_t * p_size)
{
    ASSERT(p_size != NULL);
    app_usbd_audio_t const *  p_audio = audio_get(p_inst);

    *p_size = p_audio->specific.inst.raw_desc_size;
    return p_audio->specific.inst.p_raw_desc;
}

/** @} */

const app_usbd_class_methods_t app_usbd_audio_class_methods = {
        .event_handler = audio_event_handler,
        .get_descriptors = audio_get_descriptors,
};

void app_usbd_audio_class_tx_buf_set(app_usbd_class_inst_t const * p_inst,
                                     const void * p_buff,
                                     size_t size)
{
    ASSERT(p_inst != NULL);

    app_usbd_audio_t const * p_audio = audio_get(p_inst);
    app_usbd_audio_ctx_t *   p_audio_ctx = audio_ctx_get(p_audio);
    CRITICAL_REGION_ENTER();

    p_audio_ctx->p_tx_buff = p_buff;
    p_audio_ctx->tx_size = size;

    CRITICAL_REGION_EXIT();
}

void app_usbd_audio_class_rx_buf_set(app_usbd_class_inst_t const * p_inst,
                                     void * p_buff,
                                     size_t size)
{
    ASSERT(p_inst != NULL);

    app_usbd_audio_t const * p_audio = audio_get(p_inst);
    app_usbd_audio_ctx_t *   p_audio_ctx = audio_ctx_get(p_audio);
    CRITICAL_REGION_ENTER();

    p_audio_ctx->p_rx_buff = p_buff;
    p_audio_ctx->rx_size = size;

    CRITICAL_REGION_EXIT();
}

#endif //APP_USBD_CLASS_AUDIO_ENABLED
