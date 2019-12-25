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
#if NRF_MODULE_ENABLED(APP_USBD_HID)

#include "app_usbd.h"
#include "app_usbd_core.h"
#include "app_usbd_hid.h"

#include "nrf_log.h"

/**
 * @ingroup app_usbd_hid_internals USBD HID internals
 * @{
 * @ingroup app_usbd_hid
 * @internal
 */

#define APP_USBD_HID_SOF_NOT_REQ_FLAG 0xFFFF

/**
 * @brief Test whether SOF HID transfer is required.
 *
 * This function handles idle period IN transfer.
 *
 * @param[in,out] p_hid_ctx     Internal HID context.
 * @param[in]     framecnt      SOF event frame counter.
 *
 * @retval report_id                        If transfer with ID required
 * @retval APP_USBD_HID_SOF_NOT_REQ_FLAG    If no transfer required
 */
static uint16_t hid_sof_required(app_usbd_hid_ctx_t * p_hid_ctx, uint16_t framecnt)
{
    if (!p_hid_ctx->idle_on)
    {
        /* Infinite idle rate */
        return APP_USBD_HID_SOF_NOT_REQ_FLAG;
    }

    uint8_t i = 0;
    uint16_t rate_ms[APP_USBD_HID_REPORT_IDLE_TABLE_SIZE] = {0};
    
    for(i = 0; i < APP_USBD_HID_REPORT_IDLE_TABLE_SIZE; i++)
    {
        rate_ms[i] = p_hid_ctx->idle_rate[i] * 4;
    
        if((framecnt == APP_USBD_SOF_MAX) && (p_hid_ctx->first_idle[i] != (APP_USBD_SOF_MAX + 1)))
        {
            /* SOF has only 2047 frame count maximum - adjust m_first_idle */
            p_hid_ctx->first_idle[i] = ((p_hid_ctx->first_idle[i] + APP_USBD_SOF_MAX) % rate_ms[i]) + 1;
        }
        
        if (p_hid_ctx->access_lock)
        {
            /* Access to internal data locked. Buffer is BUSY.
             * Don't send anything. Clear transfer flag. Next transfer will be triggered
             * from API context.*/
            app_usbd_hid_state_flag_clr(p_hid_ctx, APP_USBD_HID_STATE_FLAG_TRANS_IN_PROGRESS);
            return APP_USBD_HID_SOF_NOT_REQ_FLAG;
        }

        /* Idle transfer required if SOF is correct with an accuracy of +/-10% + 2ms*/
        if (((framecnt + p_hid_ctx->first_idle[i]) % rate_ms[i]) < (2 + (rate_ms[i] / 10)))
        {
            return i;
        }
        
        /* Only 0 id has set idle rate. No need to check whole table. */
        if(!p_hid_ctx->idle_id_report)
        {
            return APP_USBD_HID_SOF_NOT_REQ_FLAG;
        }
    }

    return APP_USBD_HID_SOF_NOT_REQ_FLAG;
}

static bool hid_idle_on(app_usbd_class_inst_t const * p_inst, app_usbd_hid_ctx_t * p_hid_ctx)
{
    return p_hid_ctx->idle_on;
}

/**
 * @brief User event handler.
 *
 * @param[in] p_inst        Class instance.
 * @param[in] p_hinst       HID class instance.
 * @param[in] event user    Event type.
 */
static inline void user_event_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_hid_inst_t const * p_hinst,
                                      app_usbd_hid_user_event_t event)
{
    if (p_hinst->user_event_handler != NULL)
    {
        p_hinst->user_event_handler(p_inst, event);
    }
}

/**
 * @brief Internal SETUP standard IN request handler.
 *
 * @param[in]       p_inst        Generic class instance.
 * @param[in]       p_hinst       HID class instance.
 * @param[in,out]   p_hid_ctx     HID context.
 * @param[in]       p_setup_ev    Setup event.
 *
 * @return Standard error code.
 */
static ret_code_t setup_req_std_in(app_usbd_class_inst_t const * p_inst,
                                   app_usbd_hid_inst_t const * p_hinst,
                                   app_usbd_hid_ctx_t * p_hid_ctx,
                                   app_usbd_setup_evt_t const * p_setup_ev)
{
    /* Only Get Descriptor standard IN request is supported by HID class */
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

        /* HID specific descriptors*/
        uint32_t report_size = 
            p_hinst->p_hid_methods->subclass_length(p_inst, p_setup_ev->setup.wValue.lb);
        const uint8_t * p_first_byte = 
            p_hinst->p_hid_methods->subclass_data(p_inst, p_setup_ev->setup.wValue.lb, 0);

        return app_usbd_core_setup_rsp(
            &p_setup_ev->setup,
            p_first_byte,
            report_size);
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Internal SETUP standard OUT request handler.
 *
 * @param[in]       p_inst        Generic class instance.
 * @param[in]       p_hinst       HID class instance.
 * @param[in,out]   p_hid_ctx     HID context.
 * @param[in]       p_setup_ev    Setup event.
 *
 * @return Standard error code.
 */
static ret_code_t setup_req_std_out(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_hid_inst_t const * p_hinst,
                                    app_usbd_hid_ctx_t * p_hid_ctx,
                                    app_usbd_setup_evt_t const * p_setup_ev)
{
    /*Only Set Descriptor standard OUT request is supported by HID class. However, it is optional
     * and useless in HID cases.*/
    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Internal SETUP class IN request handler.
 *
 * @param[in]       p_inst        Generic class instance.
 * @param[in]       p_hinst       HID class instance.
 * @param[in,out]   p_hid_ctx     HID context.
 * @param[in]       p_setup_ev    Setup event.
 *
 * @return Standard error code.
 */
static ret_code_t setup_req_class_in(app_usbd_class_inst_t const * p_inst,
                                     app_usbd_hid_inst_t const * p_hinst,
                                     app_usbd_hid_ctx_t * p_hid_ctx,
                                     app_usbd_setup_evt_t const * p_setup_ev)
{
    switch (p_setup_ev->setup.bRequest)
    {
        case APP_USBD_HID_REQ_GET_REPORT:
        {
            if ((p_setup_ev->setup.wValue.hb == APP_USBD_HID_REPORT_TYPE_INPUT) ||
                (p_setup_ev->setup.wValue.hb == APP_USBD_HID_REPORT_TYPE_OUTPUT))
            {
                return p_hinst->p_hid_methods->on_get_report(p_inst, p_setup_ev);
            }
            else
            {
                break;
            }
        }
        case APP_USBD_HID_REQ_GET_IDLE:
        {
            return app_usbd_core_setup_rsp(&p_setup_ev->setup,
                                           &p_hid_ctx->idle_rate[p_setup_ev->setup.wValue.lb],
                                           sizeof(p_hid_ctx->idle_rate[p_setup_ev->setup.wValue.lb]));
        }
        case APP_USBD_HID_REQ_GET_PROTOCOL:
        {
            return app_usbd_core_setup_rsp(&p_setup_ev->setup,
                                           &p_hid_ctx->selected_protocol,
                                           sizeof(p_hid_ctx->selected_protocol));
        }
        default:
            break;

    }

    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Internal SETUP class OUT request handler.
 *
 * @param[in]       p_inst        Generic class instance.
 * @param[in]       p_hinst       HID class instance.
 * @param[in,out]   p_hid_ctx     HID context.
 * @param[in]       p_setup_ev    Setup event.
 *
 * @return Standard error code.
 */
static ret_code_t setup_req_class_out(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_hid_inst_t const * p_hinst,
                                      app_usbd_hid_ctx_t * p_hid_ctx,
                                      app_usbd_setup_evt_t const * p_setup_ev)
{
    switch (p_setup_ev->setup.bRequest)
    {
        case APP_USBD_HID_REQ_SET_REPORT:
            if (p_setup_ev->setup.wValue.hb != APP_USBD_HID_REPORT_TYPE_OUTPUT)
            {
                break;
            }

            if (p_hinst->p_hid_methods->on_set_report == NULL)
            {
                break;
            }

            return p_hinst->p_hid_methods->on_set_report(p_inst, p_setup_ev);
        case APP_USBD_HID_REQ_SET_IDLE:
            {
                p_hid_ctx->idle_rate[p_setup_ev->setup.wValue.lb] = p_setup_ev->setup.wValue.hb;
                p_hid_ctx->first_idle[p_setup_ev->setup.wValue.lb] = APP_USBD_SOF_MAX + 1;

                /* Clear idle */
                if(p_setup_ev->setup.wValue.hb == 0) 
                {
                    /* If only idle rate with id 0 is non 0 set idle_id_report to false */
                    bool clear = true;
                    uint8_t i = 0;
                    for(i=1; i < APP_USBD_HID_REPORT_IDLE_TABLE_SIZE; i++)
                    {
                        if(p_hid_ctx->idle_rate[i] != 0)
                        {
                            clear = false;
                            break;
                        }
                    }
                    
                    if(clear)
                    {
                        p_hid_ctx->idle_id_report = false;
                        
                        if(p_hid_ctx->idle_rate[0] == 0)
                        {
                            /* If all are 0 set m_idle_on to false */
                            p_hid_ctx->idle_on = false;
                        }
                    }
                }
                /* Set idle */
                else
                {
                    /* If any idle rate is not 0 set m_idle_on to true */
                    p_hid_ctx->idle_on = true;
                    
                    /* If any idle rate with id != 0 is non 0 set idle_id_report to true */
                    if(p_setup_ev->setup.wValue.lb != 0)
                    {
                        p_hid_ctx->idle_id_report = true;
                    }
                }

                return NRF_SUCCESS;
            }
        case APP_USBD_HID_REQ_SET_PROTOCOL:
            {
                app_usbd_hid_user_event_t ev = (p_setup_ev->setup.wValue.w == APP_USBD_HID_PROTO_BOOT) ?
                    APP_USBD_HID_USER_EVT_SET_BOOT_PROTO :
                    APP_USBD_HID_USER_EVT_SET_REPORT_PROTO;

                if (ev == APP_USBD_HID_USER_EVT_SET_BOOT_PROTO)
                {
                    p_hid_ctx->selected_protocol = APP_USBD_HID_PROTO_BOOT;
                }
                else if (ev == APP_USBD_HID_USER_EVT_SET_REPORT_PROTO)
                {
                    p_hid_ctx->selected_protocol = APP_USBD_HID_PROTO_REPORT;
                }
                else
                {
                    return NRF_ERROR_INVALID_PARAM;
                }

                user_event_handler(p_inst, p_hinst, ev);
            }
            return NRF_SUCCESS;
        default:
            break;
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Internal SETUP event handler.
 *
 * @param[in]       p_inst        Generic class instance.
 * @param[in]       p_hinst       HID class instance.
 * @param[in,out]   p_hid_ctx     HID context.
 * @param[in]       p_setup_ev    Setup event.
 *
 * @return Standard error code.
 */
static ret_code_t setup_event_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_hid_inst_t const * p_hinst,
                                      app_usbd_hid_ctx_t * p_hid_ctx,
                                      app_usbd_setup_evt_t const * p_setup_ev)
{
    ASSERT(p_hinst != NULL);
    ASSERT(p_hid_ctx != NULL);
    ASSERT(p_setup_ev != NULL);

    if (app_usbd_setup_req_dir(p_setup_ev->setup.bmRequestType) == APP_USBD_SETUP_REQDIR_IN)
    {
        switch (app_usbd_setup_req_typ(p_setup_ev->setup.bmRequestType))
        {
            case APP_USBD_SETUP_REQTYPE_STD:
                return setup_req_std_in(p_inst, p_hinst, p_hid_ctx, p_setup_ev);
            case APP_USBD_SETUP_REQTYPE_CLASS:
                return setup_req_class_in(p_inst, p_hinst, p_hid_ctx, p_setup_ev);
            default:
                break;
        }
    }
    else /*APP_USBD_SETUP_REQDIR_OUT*/
    {
        switch (app_usbd_setup_req_typ(p_setup_ev->setup.bmRequestType))
        {
            case APP_USBD_SETUP_REQTYPE_STD:
                return setup_req_std_out(p_inst, p_hinst, p_hid_ctx, p_setup_ev);
            case APP_USBD_SETUP_REQTYPE_CLASS:
                return setup_req_class_out(p_inst, p_hinst, p_hid_ctx, p_setup_ev);
            default:
                break;
        }
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Endpoint IN event handler.
 *
 * @param[in]       p_inst        Generic class instance.
 * @param[in]       p_hinst       HID class instance.
 * @param[in,out]   p_hid_ctx     HID context.
 * @param[in]       p_setup_ev    Setup event.
 *
 * @return Standard error code.
 */
static ret_code_t endpoint_in_event_handler(app_usbd_class_inst_t const * p_inst,
                                            app_usbd_hid_inst_t const * p_hinst,
                                            app_usbd_hid_ctx_t * p_hid_ctx,
                                            app_usbd_complex_evt_t const * p_event)
{

    if (p_event->drv_evt.data.eptransfer.status == NRF_USBD_EP_OK)
    {
        /* Notify user about last successful transfer. */
        user_event_handler(p_inst, p_hinst, APP_USBD_HID_USER_EVT_IN_REPORT_DONE);
    }

    if (app_usbd_hid_access_lock_test(p_hid_ctx))
    {
        /* Access to internal data locked. Buffer is BUSY.
         * Don't send anything. Clear transfer flag. Next transfer will be triggered
         * from main loop context. */
        app_usbd_hid_state_flag_clr(p_hid_ctx, APP_USBD_HID_STATE_FLAG_TRANS_IN_PROGRESS);
        return NRF_SUCCESS;
    }

    if (!hid_idle_on(p_inst, p_hid_ctx))
    {
        return p_hinst->p_hid_methods->ep_transfer_in(p_inst);
    }
    else
    {
        uint8_t i = 0;
        for(i=0; i < APP_USBD_HID_REPORT_IDLE_TABLE_SIZE; i++)
        {
            if (p_hid_ctx->first_idle[i] == (APP_USBD_SOF_MAX + 1))
            {
                p_hid_ctx->lock_idle[i] = true;
            }
            
            /* Only 0 id has set idle rate. No need to check whole table. */
            if(!p_hid_ctx->idle_id_report)
            {
                break;
            }
        }
        return NRF_SUCCESS;
    }
}

/**
 * @brief Endpoint OUT event handler.
 *
 * @param[in]       p_inst        Generic class instance.
 * @param[in]       p_hinst       HID class instance.
 * @param[in,out]   p_hid_ctx     HID context.
 * @param[in]       p_setup_ev    Setup event.
 *
 * @return Standard error code.
 */
static ret_code_t endpoint_out_event_handler(app_usbd_class_inst_t const * p_inst,
                                             app_usbd_hid_inst_t const * p_hinst,
                                             app_usbd_hid_ctx_t * p_hid_ctx,
                                             app_usbd_complex_evt_t const * p_event)
{
    if (p_hinst->p_hid_methods->ep_transfer_out == NULL)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if (p_event->drv_evt.data.eptransfer.status == NRF_USBD_EP_OK)
    {
        /* Notify user about last successful transfer. */
        user_event_handler(p_inst, p_hinst, APP_USBD_HID_USER_EVT_OUT_REPORT_READY);
    }

    ASSERT(p_hinst->p_rep_buffer_out->size <= NRF_DRV_USBD_EPSIZE);
    return p_hinst->p_hid_methods->ep_transfer_out(p_inst);
}


static void app_usbd_clear_idle_ctx(app_usbd_hid_ctx_t * p_hid_ctx)
{
    uint8_t i = 0;
    for(i=0; i < APP_USBD_HID_REPORT_IDLE_TABLE_SIZE; i++)
    {
        p_hid_ctx->idle_rate[i] = APP_USBD_HID_DEFAULT_IDLE_RATE;
        p_hid_ctx->first_idle[i] = APP_USBD_SOF_MAX + 1;
    }
    p_hid_ctx->idle_id_report = false;
    p_hid_ctx->idle_on = false;
}

/** @} */


ret_code_t app_usbd_hid_event_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_hid_inst_t const * p_hinst,
                                      app_usbd_hid_ctx_t * p_hid_ctx,
                                      app_usbd_complex_evt_t const * p_event)
{
    ret_code_t ret = NRF_SUCCESS;
    switch (p_event->app_evt.type)
    {
        case APP_USBD_EVT_DRV_SOF:
        {
            uint16_t sof_req = hid_sof_required(p_hid_ctx, p_event->drv_evt.data.sof.framecnt);
            if (sof_req != APP_USBD_HID_SOF_NOT_REQ_FLAG)
            {
                uint8_t i = 0;
                for(i=0; i < APP_USBD_HID_REPORT_IDLE_TABLE_SIZE; i++)
                {
                    if(p_hid_ctx->lock_idle[i])
                    {
                        p_hid_ctx->first_idle[i] = p_event->drv_evt.data.sof.framecnt;
                        p_hid_ctx->lock_idle[i] = false;
                    }
                    /* Only 0 id has set idle rate. No need to check whole table. */
                    if(!p_hid_ctx->idle_id_report)
                    {
                        break;
                    }
                }
                ret = p_hinst->p_hid_methods->on_idle(p_inst, sof_req);
            }
            break;
        }
        case APP_USBD_EVT_DRV_RESET:
        {
            app_usbd_hid_state_flag_clr(p_hid_ctx, APP_USBD_HID_STATE_FLAG_TRANS_IN_PROGRESS);
            p_hid_ctx->selected_protocol = APP_USBD_HID_PROTO_REPORT;
            app_usbd_clear_idle_ctx(p_hid_ctx);
            break;
        }
        case APP_USBD_EVT_DRV_SETUP:
            ret  = setup_event_handler(p_inst, p_hinst, p_hid_ctx, &p_event->setup_evt);
            break;
        case APP_USBD_EVT_DRV_EPTRANSFER:
            if (NRF_USBD_EPIN_CHECK(p_event->drv_evt.data.eptransfer.ep))
            {
                ret = endpoint_in_event_handler(p_inst, p_hinst, p_hid_ctx, p_event);
            }
            else
            {
                ret = endpoint_out_event_handler(p_inst, p_hinst, p_hid_ctx, p_event);
            }
            break;
        case APP_USBD_EVT_DRV_SUSPEND:
            app_usbd_hid_state_flag_set(p_hid_ctx, APP_USBD_HID_STATE_FLAG_SUSPENDED);
            break;
        case APP_USBD_EVT_DRV_RESUME:
            app_usbd_hid_state_flag_clr(p_hid_ctx, APP_USBD_HID_STATE_FLAG_SUSPENDED);

            /* Always try to trigger transfer on resume event*/
            ret = p_hinst->p_hid_methods->ep_transfer_in(p_inst);
            break;
        case APP_USBD_EVT_INST_APPEND:
            /*SOF register: GetIdle/SetIdle support*/
            ret = app_usbd_class_sof_register(p_inst);
            if (ret != NRF_SUCCESS)
            {
                break;
            }
            ret = app_usbd_class_rwu_register(p_inst);
            if (ret != NRF_SUCCESS)
            {
                break;
            }
            app_usbd_clear_idle_ctx(p_hid_ctx);
            app_usbd_hid_state_flag_set(p_hid_ctx, APP_USBD_HID_STATE_FLAG_APPENDED);
            break;
        case APP_USBD_EVT_INST_REMOVE:
            /*SOF unregister: GetIdle/SetIdle support*/
            ret = app_usbd_class_sof_unregister(p_inst);
            if (ret != NRF_SUCCESS)
            {
                break;
            }
            ret = app_usbd_class_rwu_unregister(p_inst);
            if (ret != NRF_SUCCESS)
            {
                break;
            }
            app_usbd_hid_state_flag_clr(p_hid_ctx, APP_USBD_HID_STATE_FLAG_APPENDED);
            break;
        case APP_USBD_EVT_STARTED:
            app_usbd_hid_state_flag_set(p_hid_ctx, APP_USBD_HID_STATE_FLAG_STARTED);
            break;
        case APP_USBD_EVT_STOPPED:
            app_usbd_hid_state_flag_clr(p_hid_ctx, APP_USBD_HID_STATE_FLAG_STARTED);
            break;
        default:
            ret = NRF_ERROR_NOT_SUPPORTED;
            break;
    }

    return ret;
}

app_usbd_hid_report_buffer_t * app_usbd_hid_rep_buff_in_get(app_usbd_hid_inst_t const * p_hinst)
{
    ASSERT(p_hinst);
    return p_hinst->p_rep_buffer_in;
}

#endif //NRF_MODULE_ENABLED(APP_USBD_HID)
