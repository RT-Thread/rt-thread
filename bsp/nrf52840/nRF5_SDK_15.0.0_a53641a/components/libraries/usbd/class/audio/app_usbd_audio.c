/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(APP_USBD_AUDIO)

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

#define APP_USBD_AUDIO_CONTROL_IFACE_IDX    0 /**< Audio class control interface index */
#define APP_USBD_AUDIO_STREAMING_IFACE_IDX  1 /**< Audio class streaming interface index */

#define APP_USBD_CDC_AUDIO_STREAMING_EP_IDX 0 /**< Audio streaming isochronous endpoint index */

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
 */
static inline void user_event_handler(
    app_usbd_class_inst_t const * p_inst,
    app_usbd_audio_user_event_t   event)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);

    if (p_audio->specific.inst.user_ev_handler != NULL)
    {
        p_audio->specific.inst.user_ev_handler(p_inst, event);
    }
}


/**
 * @brief Select interface
 *
 * @param[in,out] p_inst    Instance of the class
 * @param[in]     iface_idx Index of the interface inside class structure
 * @param[in]     alternate Alternate setting that should be selected
 */
static ret_code_t iface_select(
    app_usbd_class_inst_t const * const p_inst,
    uint8_t                             iface_idx,
    uint8_t                             alternate)
{
    app_usbd_class_iface_conf_t const * p_iface = app_usbd_class_iface_get(p_inst, iface_idx);
    /* Simple check if this is data interface */
    uint8_t const ep_count = app_usbd_class_iface_ep_count_get(p_iface);

    if (ep_count > 0)
    {
        if (alternate > 1)
        {
            return NRF_ERROR_INVALID_PARAM;
        }
        app_usbd_audio_t const * p_audio     = audio_get(p_inst);
        app_usbd_audio_ctx_t   * p_audio_ctx = audio_ctx_get(p_audio);
        p_audio_ctx->streaming = (alternate != 0);

        uint8_t i;

        for (i = 0; i < ep_count; ++i)
        {
            nrf_drv_usbd_ep_t ep_addr =
                app_usbd_class_ep_address_get(app_usbd_class_iface_ep_get(p_iface, i));
            if (alternate)
            {
                app_usbd_ep_enable(ep_addr);
            }
            else
            {
                app_usbd_ep_disable(ep_addr);
            }
        }
        return NRF_SUCCESS;
    }
    return NRF_ERROR_NOT_SUPPORTED;
}


static void iface_deselect(
    app_usbd_class_inst_t const * const p_inst,
    uint8_t                             iface_idx)
{
    app_usbd_class_iface_conf_t const * p_iface = app_usbd_class_iface_get(p_inst, iface_idx);

    /* Simple check if this is data interface */
    if (p_iface->ep_cnt > 0)
    {
        app_usbd_audio_t const * p_audio     = audio_get(p_inst);
        app_usbd_audio_ctx_t   * p_audio_ctx = audio_ctx_get(p_audio);
        p_audio_ctx->streaming = false;
    }
    /* Note that all the interface endpoints would be disabled automatically after this function */
}


static uint8_t iface_selection_get(
    app_usbd_class_inst_t const * const p_inst,
    uint8_t                             iface_idx)
{
    app_usbd_class_iface_conf_t const * p_iface = app_usbd_class_iface_get(p_inst, iface_idx);
    /* Simple check if this is data interface */
    uint8_t const ep_count = app_usbd_class_iface_ep_count_get(p_iface);

    if (ep_count > 0)
    {
        app_usbd_audio_t const * p_audio     = audio_get(p_inst);
        app_usbd_audio_ctx_t   * p_audio_ctx = audio_ctx_get(p_audio);
        return (p_audio_ctx->streaming) ? 1 : 0;
    }
    return 0;
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
                                   app_usbd_setup_evt_t const  * p_setup_ev)
{
    /* Only Get Descriptor standard IN request is supported by Audio class */
    if ((app_usbd_setup_req_rec(p_setup_ev->setup.bmRequestType) == APP_USBD_SETUP_REQREC_INTERFACE)
        &&
        (p_setup_ev->setup.bmRequest == APP_USBD_SETUP_STDREQ_GET_DESCRIPTOR))
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
 * @brief Internal SETUP class IN request handler
 *
 * @param[in] p_inst        Generic class instance
 * @param[in] p_setup_ev    Setup event
 *
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t setup_req_class_in(
    app_usbd_class_inst_t const * p_inst,
    app_usbd_setup_evt_t const  * p_setup_ev)
{
    switch (p_setup_ev->setup.bmRequest)
    {
        case APP_USBD_AUDIO_REQ_GET_CUR:
        case APP_USBD_AUDIO_REQ_GET_MIN:
        case APP_USBD_AUDIO_REQ_GET_MAX:
        case APP_USBD_AUDIO_REQ_SET_RES:
        case APP_USBD_AUDIO_REQ_GET_MEM:
        {
            app_usbd_audio_t const * p_audio     = audio_get(p_inst);
            app_usbd_audio_ctx_t   * p_audio_ctx = audio_ctx_get(p_audio);


            p_audio_ctx->request.req_type  = (app_usbd_audio_req_type_t)p_setup_ev->setup.bmRequest;
            p_audio_ctx->request.control   = p_setup_ev->setup.wValue.hb;
            p_audio_ctx->request.channel   = p_setup_ev->setup.wValue.lb;
            p_audio_ctx->request.interface = p_setup_ev->setup.wIndex.hb;
            p_audio_ctx->request.entity    = p_setup_ev->setup.wIndex.lb;

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
    if (status == NRF_USBD_EP_OK)
    {
        app_usbd_audio_t const * p_audio = p_context;

        user_event_handler((app_usbd_class_inst_t const *)p_audio,
                           APP_USBD_AUDIO_USER_EVT_CLASS_REQ);
    }

    return NRF_SUCCESS;
}


static ret_code_t audio_req_out(
    app_usbd_class_inst_t const * p_inst,
    app_usbd_setup_evt_t const  * p_setup_ev)
{
    app_usbd_audio_t const * p_audio     = audio_get(p_inst);
    app_usbd_audio_ctx_t   * p_audio_ctx = audio_ctx_get(p_audio);


    p_audio_ctx->request.req_type  = (app_usbd_audio_req_type_t)p_setup_ev->setup.bmRequest;
    p_audio_ctx->request.control   = p_setup_ev->setup.wValue.hb;
    p_audio_ctx->request.channel   = p_setup_ev->setup.wValue.lb;
    p_audio_ctx->request.interface = p_setup_ev->setup.wIndex.hb;
    p_audio_ctx->request.entity    = p_setup_ev->setup.wIndex.lb;

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
    ret = app_usbd_ep_transfer(NRF_DRV_USBD_EPOUT0, &transfer);
    if (ret == NRF_SUCCESS)
    {
        app_usbd_core_setup_data_handler_desc_t desc = {
            .handler   = audio_req_out_data_cb,
            .p_context = (void *)p_audio
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
static ret_code_t setup_req_class_out(
    app_usbd_class_inst_t const * p_inst,
    app_usbd_setup_evt_t const  * p_setup_ev)
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
static ret_code_t setup_event_handler(
    app_usbd_class_inst_t const * p_inst,
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
    else /*APP_USBD_SETUP_REQDIR_OUT*/
    {
        switch (app_usbd_setup_req_typ(p_setup_ev->setup.bmRequestType))
        {
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


/**
 * @brief @ref app_usbd_class_methods_t::event_handler
 */
static ret_code_t audio_event_handler(
    app_usbd_class_inst_t const  * p_inst,
    app_usbd_complex_evt_t const * p_event)
{
    ASSERT(p_inst != NULL);
    ASSERT(p_event != NULL);

    ret_code_t ret = NRF_SUCCESS;

    switch (p_event->app_evt.type)
    {
        case APP_USBD_EVT_DRV_RESET:
            break;

        case APP_USBD_EVT_DRV_SETUP:
            ret = setup_event_handler(p_inst, (app_usbd_setup_evt_t const *)p_event);
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


static size_t audio_get_format_descriptor_size(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);

    return p_audio->specific.inst.p_format_dsc->size;
}


static size_t audio_get_format_descriptor_data(app_usbd_class_inst_t const * p_inst,
                                               uint32_t                      cur_byte)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);

    return p_audio->specific.inst.p_format_dsc->p_data[cur_byte];
}


static size_t audio_get_input_descriptor_size(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);

    return p_audio->specific.inst.p_input_dsc->size;
}


static size_t audio_get_input_descriptor_data(app_usbd_class_inst_t const * p_inst,
                                              uint32_t                      cur_byte)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);

    return p_audio->specific.inst.p_input_dsc->p_data[cur_byte];
}


static size_t audio_get_output_descriptor_size(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);

    return p_audio->specific.inst.p_output_dsc->size;
}


static size_t audio_get_output_descriptor_data(app_usbd_class_inst_t const * p_inst,
                                               uint32_t                      cur_byte)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);

    return p_audio->specific.inst.p_output_dsc->p_data[cur_byte];
}


static size_t audio_get_feature_descriptor_size(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);

    return p_audio->specific.inst.p_feature_dsc->size;
}


static size_t audio_get_feature_descriptor_data(app_usbd_class_inst_t const * p_inst,
                                                uint32_t                      cur_byte)
{
    app_usbd_audio_t const * p_audio = audio_get(p_inst);

    return p_audio->specific.inst.p_feature_dsc->p_data[cur_byte];
}


static uint8_t audio_get_control_interface_number(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_class_iface_conf_t const * ifce = 0;

    ifce = app_usbd_class_iface_get(p_inst, 0);
    return app_usbd_class_iface_number_get(ifce);
}


/**
 * @brief @ref app_usbd_class_methods_t::feed_descriptors
 */

static bool audio_feed_descriptors(app_usbd_class_descriptor_ctx_t * p_ctx,
                                   app_usbd_class_inst_t const     * p_inst,
                                   uint8_t                         * p_buff,
                                   size_t                            max_size)
{
    static uint8_t ifaces   = 0;
    ifaces = app_usbd_class_iface_count_get(p_inst);
    ASSERT(ifaces == 2);
    app_usbd_audio_t const * p_audio = audio_get(p_inst);

    APP_USBD_CLASS_DESCRIPTOR_BEGIN(p_ctx, p_buff, max_size);

    /* CONTROL INTERFACE DESCRIPTOR */
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x09); // bLength
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_INTERFACE); // bDescriptorType = Interface

    static app_usbd_class_iface_conf_t const * p_cur_iface = NULL;
    p_cur_iface = app_usbd_class_iface_get(p_inst, 0);

    APP_USBD_CLASS_DESCRIPTOR_WRITE(app_usbd_class_iface_number_get(p_cur_iface)); // bInterfaceNumber
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bAlternateSetting
    APP_USBD_CLASS_DESCRIPTOR_WRITE(app_usbd_class_iface_ep_count_get(p_cur_iface)); // bNumEndpoints
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_AUDIO_CLASS); // bInterfaceClass = Audio
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_AUDIO_SUBCLASS_AUDIOCONTROL); // bInterfaceSubclass (Audio Control)
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_AUDIO_CLASS_PROTOCOL_UNDEFINED); // bInterfaceProtocol
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // iInterface

    /* HEADER INTERFACE */
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x09); // bLength
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_AUDIO_DESCRIPTOR_INTERFACE); // bDescriptorType = Audio Interfaces
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_AUDIO_AC_IFACE_SUBTYPE_HEADER); // bDescriptorSubtype = Header
    APP_USBD_CLASS_DESCRIPTOR_WRITE(LSB_16(0x0100)); // bcdADC LSB
    APP_USBD_CLASS_DESCRIPTOR_WRITE(MSB_16(0x0100)); // bcdADC MSB

    static uint16_t header_desc_len = 0;
    header_desc_len = 9 + audio_get_feature_descriptor_size(p_inst) +
                      audio_get_input_descriptor_size(p_inst) + audio_get_output_descriptor_size(
        p_inst);
    APP_USBD_CLASS_DESCRIPTOR_WRITE(LSB_16(header_desc_len)); // wTotalLength LSB
    APP_USBD_CLASS_DESCRIPTOR_WRITE(MSB_16(header_desc_len)); // wTotalLength MSB
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x01);                    // bInCollection
    APP_USBD_CLASS_DESCRIPTOR_WRITE(audio_get_control_interface_number(p_inst) + 1); // baInterfaceNr(1)

    /* INPUT TERMINAL DESCRIPTOR */
    static uint32_t cur_byte        = 0;
    static size_t   input_desc_size = 0;
    input_desc_size = audio_get_input_descriptor_size(p_inst);

    for (cur_byte = 0; cur_byte < input_desc_size; cur_byte++)
    {
        APP_USBD_CLASS_DESCRIPTOR_WRITE(audio_get_input_descriptor_data(p_inst, cur_byte));
    }

    /* FEATURE UNIT DESCRIPTOR */
    static size_t feature_desc_size = 0;
    feature_desc_size = audio_get_feature_descriptor_size(p_inst);

    for (cur_byte = 0; cur_byte < feature_desc_size; cur_byte++)
    {
        APP_USBD_CLASS_DESCRIPTOR_WRITE(audio_get_feature_descriptor_data(p_inst, cur_byte));
    }

    /* OUTPUT TERMINAL DESCRIPTOR */
    static size_t output_desc_size = 0;
    output_desc_size = audio_get_output_descriptor_size(p_inst);

    for (cur_byte = 0; cur_byte < output_desc_size; cur_byte++)
    {
        APP_USBD_CLASS_DESCRIPTOR_WRITE(audio_get_output_descriptor_data(p_inst, cur_byte));
    }

    p_cur_iface++;

    /* STREAM INTERFACE DESCRIPTOR ALT 0 */
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x09); // bLength
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_INTERFACE); // bDescriptorType = Interface
    APP_USBD_CLASS_DESCRIPTOR_WRITE(audio_get_control_interface_number(p_inst) + 1); // bInterfaceNumber
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bAlternateSetting
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bNumEndpoints
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_AUDIO_CLASS); // bInterfaceClass = Audio
    APP_USBD_CLASS_DESCRIPTOR_WRITE(p_audio->specific.inst.type_streaming); // bInterfaceSubclass (Audio Control)
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_AUDIO_CLASS_PROTOCOL_UNDEFINED); // bInterfaceProtocol
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // iInterface

    /* STREAM INTERFACE DESCRIPTOR ALT 1 */
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x09); // bLength
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_INTERFACE); // bDescriptorType = Interface
    APP_USBD_CLASS_DESCRIPTOR_WRITE(audio_get_control_interface_number(p_inst) + 1); // bInterfaceNumber
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x01); // bAlternateSetting
    APP_USBD_CLASS_DESCRIPTOR_WRITE(app_usbd_class_iface_ep_count_get(p_cur_iface)); // bNumEndpoints
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_AUDIO_CLASS); // bInterfaceClass = Audio
    APP_USBD_CLASS_DESCRIPTOR_WRITE(p_audio->specific.inst.type_streaming); // bInterfaceSubclass (Audio Control)
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_AUDIO_CLASS_PROTOCOL_UNDEFINED); // bInterfaceProtocol
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // iInterface

    /* AudioStreaming GENERAL DESCRIPTOR */
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x07); // bLength
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_AUDIO_DESCRIPTOR_INTERFACE); // bDescriptorType = Audio Interface
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_AUDIO_AS_IFACE_SUBTYPE_GENERAL); // bDescriptorSubtype = General
    APP_USBD_CLASS_DESCRIPTOR_WRITE(audio_get_control_interface_number(p_inst) + 1); // bTerminalLink
    APP_USBD_CLASS_DESCRIPTOR_WRITE(p_audio->specific.inst.delay); // bDelay
    APP_USBD_CLASS_DESCRIPTOR_WRITE(LSB_16(p_audio->specific.inst.format)); // wFormatTag LSB
    APP_USBD_CLASS_DESCRIPTOR_WRITE(MSB_16(p_audio->specific.inst.format)); // wFormatTag MSB

    /* FORMAT DESCRIPTOR */
    static size_t format_desc_size = 0;
    format_desc_size = audio_get_format_descriptor_size(p_inst);

    for (cur_byte = 0; cur_byte < format_desc_size; cur_byte++)
    {
        APP_USBD_CLASS_DESCRIPTOR_WRITE(audio_get_format_descriptor_data(p_inst, cur_byte));
    }

    /* ENDPOINT GENERAL DESCRIPTOR */
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x07); // bLength
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_AUDIO_DESCRIPTOR_ENDPOINT); // bDescriptorType = Audio Descriptor
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_AUDIO_EP_SUBTYPE_GENERAL);  // bDescriptorSubtype = EP General
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bmAttributes
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bLockDelayUnits
    APP_USBD_CLASS_DESCRIPTOR_WRITE(LSB_16(0x0000)); // wLockDelay LSB
    APP_USBD_CLASS_DESCRIPTOR_WRITE(MSB_16(0x0000)); // wLockDelay MSB

    /* ENDPOINT ISO DESCRIPTOR */
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x09); // bLength
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_ENDPOINT); // bDescriptorType = Endpoint

    static app_usbd_class_ep_conf_t const * p_cur_ep = NULL;
    p_cur_ep = app_usbd_class_iface_ep_get(p_cur_iface, 0);
    APP_USBD_CLASS_DESCRIPTOR_WRITE(app_usbd_class_ep_address_get(p_cur_ep)); // bEndpointAddress
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_EP_ATTR_TYPE_ISOCHRONOUS); // bmAttributes
    APP_USBD_CLASS_DESCRIPTOR_WRITE(LSB_16(p_audio->specific.inst.ep_size)); // wMaxPacketSize LSB
    APP_USBD_CLASS_DESCRIPTOR_WRITE(MSB_16(p_audio->specific.inst.ep_size)); // wMaxPacketSize MSB
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x01); // bInterval
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bRefresh
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bSynchAddress

    APP_USBD_CLASS_DESCRIPTOR_END();
}

/** @} */

const app_usbd_class_methods_t app_usbd_audio_class_methods = {
    .event_handler       = audio_event_handler,
    .feed_descriptors    = audio_feed_descriptors,
    .iface_select        = iface_select,
    .iface_deselect      = iface_deselect,
    .iface_selection_get = iface_selection_get,
};


size_t app_usbd_audio_class_rx_size_get(app_usbd_class_inst_t const * p_inst)
{
    nrf_drv_usbd_ep_t ep_addr;

    ep_addr = ep_iso_addr_get(p_inst);
    ASSERT(NRF_USBD_EPISO_CHECK(ep_addr));

    return (size_t)nrf_drv_usbd_epout_size_get(ep_addr);
}


ret_code_t app_usbd_audio_class_rx_start(
    app_usbd_class_inst_t const * p_inst,
    void                        * p_buff,
    size_t                        size)
{
    nrf_drv_usbd_ep_t ep_addr;

    ep_addr = ep_iso_addr_get(p_inst);
    ASSERT(NRF_USBD_EPISO_CHECK(ep_addr));

    NRF_DRV_USBD_TRANSFER_OUT(transfer, p_buff, size);
    return app_usbd_ep_transfer(ep_addr, &transfer);
}


ret_code_t app_usbd_audio_class_tx_start(
    app_usbd_class_inst_t const * p_inst,
    const void                  * p_buff,
    size_t                        size)
{
    nrf_drv_usbd_ep_t ep_addr;

    ep_addr = ep_iso_addr_get(p_inst);
    ASSERT(NRF_USBD_EPISO_CHECK(ep_addr));

    NRF_DRV_USBD_TRANSFER_IN(transfer, p_buff, size);
    return app_usbd_ep_transfer(ep_addr, &transfer);
}


#endif //NRF_MODULE_ENABLED(APP_USBD_AUDIO)
