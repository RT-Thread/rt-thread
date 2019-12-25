/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(APP_USBD_NRF_DFU_TRIGGER)

#include <string.h>
#include <ctype.h>
#include "app_usbd.h"
#include "app_usbd_nrf_dfu_trigger.h"
#include "app_usbd_string_desc.h"
#include "nrf_gpio.h"

/**
 * @defgroup app_usbd_nrf_dfu_trigger_internal USBD Nordic DFU Trigger internals
 * @{
 * @ingroup app_usbd_nrf_dfu_trigger
 * @internal
 */

#define NRF_LOG_MODULE_NAME usbd_nrf_dfu_trigger

#if APP_USBD_NRF_DFU_TRIGGER_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       APP_USBD_NRF_DFU_TRIGGER_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  APP_USBD_NRF_DFU_TRIGGER_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR APP_USBD_NRF_DFU_TRIGGER_CONFIG_DEBUG_COLOR
#else //APP_USBD_NRF_DFU_TRIGGER_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif //APP_USBD_NRF_DFU_TRIGGER_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**
 * @brief Auxiliary function to access DFU Trigger instance data.
 *
 * @param[in] p_inst Class instance data.
 *
 * @return DFU Trigger instance data @ref app_usbd_nrf_dfu_trigger_t
 */
static inline app_usbd_nrf_dfu_trigger_t const * nrf_dfu_trigger_get(app_usbd_class_inst_t const * p_inst)
{
    ASSERT(p_inst != NULL);
    return (app_usbd_nrf_dfu_trigger_t const *)p_inst;
}

/**
 * @brief Auxiliary function to access DFU Trigger context data.
 *
 * @param[in] p_dfu    DFU Trigger instance data.
 *
 * @return DFU Trigger context data @ref app_usbd_nrf_dfu_trigger_ctx_t
 */
static inline app_usbd_nrf_dfu_trigger_ctx_t * nrf_dfu_trigger_ctx_get(
        app_usbd_nrf_dfu_trigger_t const * p_dfu)
{
    ASSERT(p_dfu != NULL);
    ASSERT(p_dfu->specific.p_data != NULL);
    return &p_dfu->specific.p_data->ctx;
}

/**
 * @brief Internal SETUP standard IN request handler.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 * @retval NRF_SUCCESS if request handled correctly.
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported.
 */
static ret_code_t setup_req_std_in(app_usbd_class_inst_t const * p_inst,
                                   app_usbd_setup_evt_t const *  p_setup_ev)
{
    /* Only Get Descriptor standard IN request is supported by DFU class */
    if ((app_usbd_setup_req_rec(p_setup_ev->setup.bmRequestType) == APP_USBD_SETUP_REQREC_INTERFACE)
        &&
        (p_setup_ev->setup.bRequest == APP_USBD_SETUP_STDREQ_GET_DESCRIPTOR))
    {
        size_t dsc_len = 0;
        size_t max_size;

        uint8_t * p_trans_buff = app_usbd_core_setup_transfer_buff_get(&max_size);
        /* Try to find descriptor in class internals*/
        ret_code_t ret = app_usbd_class_descriptor_find(p_inst,
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
 * @retval NRF_SUCCESS if request handled correctly.
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported.
 * @retval NRF_ERROR_FORBIDDEN if endpoint stall cannot be cleared because of internal state.
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
 * @brief User event handler.
 *
 * @param[in] p_inst        Class instance.
 * @param[in] event user    Event type.
 */
static inline void user_event_handler(app_usbd_class_inst_t const *         p_inst,
                                      app_usbd_nrf_dfu_trigger_user_event_t event)
{
    app_usbd_nrf_dfu_trigger_t const * p_dfu = nrf_dfu_trigger_get(p_inst);
    if (p_dfu->specific.inst.user_ev_handler != NULL)
    {
        p_dfu->specific.inst.user_ev_handler(p_inst, event);
    }
}

/**
 * @brief Internal SETUP class IN request handler.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_setup_ev    Setup event.
 *
 * @return Standard error code.
 * @retval NRF_SUCCESS if request handled correctly.
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported.
 */
static ret_code_t setup_req_class_in(app_usbd_class_inst_t const * p_inst,
                                     app_usbd_setup_evt_t const *  p_setup_ev)
{
    app_usbd_nrf_dfu_trigger_t const * p_dfu = nrf_dfu_trigger_get(p_inst);

    switch (p_setup_ev->setup.bRequest)
    {
        case APP_USBD_NRF_DFU_TRIGGER_REQ_NORDIC_INFO:
            if (p_setup_ev->setup.wLength.w != sizeof(app_usbd_nrf_dfu_trigger_nordic_info_t))
            {
                return NRF_ERROR_NOT_SUPPORTED;
            }
            return app_usbd_core_setup_rsp(&p_setup_ev->setup,
                                           p_dfu->specific.inst.p_dfu_info,
                                           sizeof(app_usbd_nrf_dfu_trigger_nordic_info_t));

        case APP_USBD_NRF_DFU_TRIGGER_REQ_SEM_VER:
            return app_usbd_core_setup_rsp(&p_setup_ev->setup,
                                           p_dfu->specific.inst.p_sem_ver,
                                           p_dfu->specific.inst.sem_ver_size);

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
 * @retval NRF_SUCCESS if request handled correctly.
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported.
 */
static ret_code_t setup_req_class_out(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_setup_evt_t const *  p_setup_ev)
{
    app_usbd_nrf_dfu_trigger_t const * p_dfu     = nrf_dfu_trigger_get(p_inst);
    app_usbd_nrf_dfu_trigger_ctx_t *   p_dfu_ctx = nrf_dfu_trigger_ctx_get(p_dfu);

    switch (p_setup_ev->setup.bRequest)
    {
        case APP_USBD_NRF_DFU_TRIGGER_REQ_DETACH:
        {
            NRF_LOG_DEBUG("Entering DFU Mode");
            p_dfu_ctx->state = APP_USBD_NRF_DFU_TRIGGER_STATE_DETACH;
            user_event_handler(p_inst, APP_USBD_NRF_DFU_TRIGGER_USER_EVT_DETACH);
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
 * @retval NRF_SUCCESS if request handled correctly.
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported.
 */
static ret_code_t setup_event_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_setup_evt_t const *  p_setup_ev)
{
    ASSERT(p_inst     != NULL);
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
 * @brief @ref app_usbd_class_methods_t::event_handler
 */
static ret_code_t nrf_dfu_trigger_event_handler(app_usbd_class_inst_t const *  p_inst,
                                                app_usbd_complex_evt_t const * p_event)
{
    ASSERT(p_inst  != NULL);
    ASSERT(p_event != NULL);

    ret_code_t ret = NRF_SUCCESS;
    switch (p_event->app_evt.type)
    {
        case APP_USBD_EVT_DRV_SOF:
            break;
        case APP_USBD_EVT_DRV_RESET:
            break;
        case APP_USBD_EVT_DRV_SETUP:
            ret  = setup_event_handler(p_inst, (app_usbd_setup_evt_t const *) p_event);
            break;
        case APP_USBD_EVT_DRV_EPTRANSFER:
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
        default:
            ret = NRF_ERROR_NOT_SUPPORTED;
            break;
    }

    return ret;
}

/**
 * @brief @ref app_usbd_class_methods_t::feed_descriptors
 */
static bool nrf_dfu_trigger_feed_descriptors(app_usbd_class_descriptor_ctx_t * p_ctx,
                                             app_usbd_class_inst_t const     * p_inst,
                                             uint8_t                         * p_buff,
                                             size_t                            max_size)
{
    static app_usbd_class_iface_conf_t const * p_cur_iface = NULL;
    p_cur_iface = app_usbd_class_iface_get(p_inst, 0);
    app_usbd_nrf_dfu_trigger_t const * p_dfu = nrf_dfu_trigger_get(p_inst);

    APP_USBD_CLASS_DESCRIPTOR_BEGIN(p_ctx, p_buff, max_size)

    /* INTERFACE DESCRIPTOR */
    APP_USBD_CLASS_DESCRIPTOR_WRITE(sizeof(app_usbd_descriptor_iface_t)); // bLength
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_INTERFACE); // bDescriptorType
    APP_USBD_CLASS_DESCRIPTOR_WRITE(app_usbd_class_iface_number_get(p_cur_iface)); // bInterfaceNumber
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bAlternateSetting
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0); // bNumEndpoints
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_NRF_DFU_TRIGGER_CLASS); // bInterfaceClass
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_NRF_DFU_TRIGGER_SUBCLASS); // bInterfaceSubClass
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_NRF_DFU_TRIGGER_PROTOCOL_RUNTIME); // bInterfaceProtocol
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // iInterface

    /* FUNCTIONAL DESCRIPTOR */
    APP_USBD_CLASS_DESCRIPTOR_WRITE(sizeof(app_usbd_nrf_dfu_trigger_desc_func_t)); // bFunctionLength
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_NRF_DFU_TRIGGER_CS_FUNCTIONAL); // bDescriptorType
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_NRF_DFU_TRIGGER_BIT_CAN_DNLOAD |
                                    APP_USBD_NRF_DFU_TRIGGER_BIT_WILL_DETACH); // bmAttribute
    APP_USBD_CLASS_DESCRIPTOR_WRITE(LSB_16(p_dfu->specific.inst.detach_timeout)); // wDetachTimeOut LSB
    APP_USBD_CLASS_DESCRIPTOR_WRITE(MSB_16(p_dfu->specific.inst.detach_timeout)); // wDetachTimeOut MSB
    APP_USBD_CLASS_DESCRIPTOR_WRITE(LSB_16(p_dfu->specific.inst.transfer_size)); // wTransferSize LSB
    APP_USBD_CLASS_DESCRIPTOR_WRITE(MSB_16(p_dfu->specific.inst.transfer_size)); // wTransferSize MSB
    APP_USBD_CLASS_DESCRIPTOR_WRITE(LSB_16(p_dfu->specific.inst.bcd_dfu)); // bcdDFUVersion LSB
    APP_USBD_CLASS_DESCRIPTOR_WRITE(MSB_16(p_dfu->specific.inst.bcd_dfu)); // bcdDFUVersion MSB

    APP_USBD_CLASS_DESCRIPTOR_END();
}

const app_usbd_class_methods_t app_usbd_nrf_dfu_trigger_class_methods = {
        .event_handler    = nrf_dfu_trigger_event_handler,
        .feed_descriptors = nrf_dfu_trigger_feed_descriptors,
};


#endif //NRF_MODULE_ENABLED(APP_USBD_NRF_DFU_TRIGGER)
