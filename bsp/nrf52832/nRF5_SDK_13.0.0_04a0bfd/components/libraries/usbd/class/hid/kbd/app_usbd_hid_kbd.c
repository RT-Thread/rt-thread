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
#if APP_USBD_HID_KBD_ENABLED
#include <string.h>

#include "sdk_common.h"
#include "app_usbd_hid_kbd.h"
#include "app_util_platform.h"


/**
 * @defgroup app_usbd_hid_kbd_internals USB HID keyboard internals
 * @{
 * @ingroup app_usbd_hid_kbd
 * @internal
 */

STATIC_ASSERT(sizeof(app_usbd_hid_descriptor_t) == 6);

/**
 * @brief Auxiliary function to access HID keyboard context data.
 *
 * @param[in] p_inst class instance data.
 *
 * @return HID keyboard instance data context.
 */
static inline app_usbd_hid_kbd_ctx_t * hid_kbd_ctx_get(app_usbd_hid_kbd_t const * p_kbd)
{
    ASSERT(p_kbd != NULL);
    ASSERT(p_kbd->specific.p_data != NULL);
    return &p_kbd->specific.p_data->ctx;
}

/**
 * @brief Auxiliary function to access HID keyboard instance data.
 *
 * @param[in] p_inst class instance data.
 *
 * @return HID keyboard instance data.
 */
static inline app_usbd_hid_kbd_t const * hid_kbd_get(app_usbd_class_inst_t const * p_inst)
{
    ASSERT(p_inst != NULL);
    return (app_usbd_hid_kbd_t const *)p_inst;
}

/**
 * @brief Returns keyboard report buffer handle.
 *
 * @param[in] p_kbd HID keyboard instance.
 *
 * @return HID report buffer.
 */
static inline
app_usbd_hid_report_buffer_t const * hid_kbd_rep_buffer_get(app_usbd_hid_kbd_t const * p_kbd)
{
    ASSERT(p_kbd != NULL);
    app_usbd_hid_inst_t const *    p_hinst = &p_kbd->specific.inst.hid_inst;
    app_usbd_hid_kbd_ctx_t *       p_kbd_ctx = hid_kbd_ctx_get(p_kbd);
    app_usbd_hid_report_buffer_t * p_rep_buff = app_usbd_hid_rep_buff_in_get(p_hinst);

    p_rep_buff->p_buff = p_kbd_ctx->report_buff;
    p_rep_buff->size = sizeof(p_kbd_ctx->report_buff);

    /*Keyboard has only one report input/output report buffer */
    return p_rep_buff;
}


/**
 * @brief Auxiliary function to prepare report transfer buffer to next transfer.
 *
 * @param[in] p_kbd HID keyboard instance.
 *
 * @retval true     Next transfer is required.
 * @retval false    Next transfer is not required.
 */
static inline bool hid_kbd_transfer_next(app_usbd_hid_kbd_t const * p_kbd)
{
    /*Send report only when state has changed*/
    app_usbd_hid_report_buffer_t const * p_rep_buffer = hid_kbd_rep_buffer_get(p_kbd);
    app_usbd_hid_kbd_ctx_t *             p_kbd_ctx = hid_kbd_ctx_get(p_kbd);

    if (memcmp(p_rep_buffer->p_buff, &p_kbd_ctx->rep, p_rep_buffer->size))
    {
        memcpy(p_rep_buffer->p_buff, &p_kbd_ctx->rep, p_rep_buffer->size);
        return true;
    }

    return false;
}


/**
 * @brief Triggers IN endpoint transfer.
 *
 * @param[in] p_kbd HID keyboard instance.
 *
 * @return Standard error code.
 */
static inline ret_code_t hid_kbd_transfer_set(app_usbd_hid_kbd_t const * p_kbd)
{
    app_usbd_class_inst_t const * p_inst = (app_usbd_class_inst_t const *)p_kbd;
    app_usbd_hid_kbd_ctx_t *      p_kbd_ctx = hid_kbd_ctx_get(p_kbd);

    nrf_drv_usbd_ep_t ep_addr = app_usbd_hid_epin_addr_get(p_inst);

    app_usbd_hid_state_flag_clr(&p_kbd_ctx->hid_ctx, APP_USBD_HID_STATE_FLAG_TRANS_IN_PROGRESS);

    if (!hid_kbd_transfer_next(p_kbd))
    {
        /* Transfer buffer hasn't changed since last transfer. No need to setup
         * next transfer.
         * */
        return NRF_SUCCESS;
    }

    app_usbd_hid_report_buffer_t const * p_rep_buffer = hid_kbd_rep_buffer_get(p_kbd);
    NRF_DRV_USBD_TRANSFER_IN(transfer, p_rep_buffer->p_buff, p_rep_buffer->size);

    ret_code_t ret;
    CRITICAL_REGION_ENTER();
    ret = app_usbd_core_ep_transfer(ep_addr, &transfer);
    if (ret == NRF_SUCCESS)
    {
        app_usbd_hid_state_flag_set(&p_kbd_ctx->hid_ctx, APP_USBD_HID_STATE_FLAG_TRANS_IN_PROGRESS);
    }
    CRITICAL_REGION_EXIT();

    return ret;
}

ret_code_t app_usbd_hid_kbd_modifier_state_set(app_usbd_hid_kbd_t const *  p_kbd,
                                               app_usbd_hid_kbd_modifier_t modifier,
                                               bool state)
{
    app_usbd_hid_kbd_ctx_t * p_kbd_ctx = hid_kbd_ctx_get(p_kbd);
    bool actual_state = (p_kbd_ctx->rep.modifier & modifier) != 0;

    if (actual_state == state)
    {
        /*Modifier has already the same state*/
        return NRF_SUCCESS;
    }

    app_usbd_hid_access_lock(&p_kbd_ctx->hid_ctx);

    if (state)
    {
        p_kbd_ctx->rep.modifier |= modifier;
    }
    else
    {
        p_kbd_ctx->rep.modifier &= ~modifier;
    }
    app_usbd_hid_access_unlock(&p_kbd_ctx->hid_ctx);

    if (app_usbd_hid_trans_required(&p_kbd_ctx->hid_ctx))
    {
        /*New transfer need to be triggered*/
        return hid_kbd_transfer_set(p_kbd);
    }

    return NRF_SUCCESS;
}


ret_code_t app_usbd_hid_kbd_key_control(app_usbd_hid_kbd_t const * p_kbd,
                                        app_usbd_hid_kbd_codes_t   key,
                                        bool press)
{
    app_usbd_hid_kbd_ctx_t * p_kbd_ctx = hid_kbd_ctx_get(p_kbd);
    uint8_t * destination = NULL;
    if (press)
    {
        for (size_t i = 0; i < ARRAY_SIZE(p_kbd_ctx->rep.key_table); ++i) {
            if (p_kbd_ctx->rep.key_table[i] == key)
            {
                /*Already pressed*/
                return NRF_SUCCESS;
            }

            if ((destination == NULL) && (p_kbd_ctx->rep.key_table[i] == 0))
            {
                destination = &p_kbd_ctx->rep.key_table[i];
            }
        }

        if (destination == NULL)
        {
            return NRF_ERROR_BUSY;
        }
    }
    else
    {
        /*Find if key is pressed*/
        for (size_t i = 0; i < ARRAY_SIZE(p_kbd_ctx->rep.key_table); ++i) {
            if (p_kbd_ctx->rep.key_table[i] == key)
            {
                destination = &p_kbd_ctx->rep.key_table[i];
                break;
            }
        }

        if (destination == NULL)
        {
            /*Key hasn't been pressed*/
            return NRF_SUCCESS;
        }
    }

    /*Save destination*/
    app_usbd_hid_access_lock(&p_kbd_ctx->hid_ctx);
    *destination = press ? key : 0;
    app_usbd_hid_access_unlock(&p_kbd_ctx->hid_ctx);

    if (app_usbd_hid_trans_required(&p_kbd_ctx->hid_ctx))
    {
        /*New transfer need to be triggered*/
        return hid_kbd_transfer_set(p_kbd);
    }

    return NRF_SUCCESS;
}

bool app_usbd_hid_kbd_led_state_get(app_usbd_hid_kbd_t const * p_kbd,
                                    app_usbd_hid_kbd_led_t     led)
{
        app_usbd_hid_kbd_ctx_t * p_kbd_ctx = hid_kbd_ctx_get(p_kbd);

        return (p_kbd_ctx->leds_state & led) != 0;
}

/**
 * @brief @ref app_usbd_hid_interface_t::on_get_report
 */
static ret_code_t hid_kbd_on_get_report(app_usbd_class_inst_t const * p_inst,
                                        app_usbd_setup_evt_t const *  p_setup_ev)
{
    app_usbd_hid_kbd_t const * p_kbd = hid_kbd_get(p_inst);
    app_usbd_hid_report_buffer_t const * p_rep_buffer = hid_kbd_rep_buffer_get(p_kbd);

    return app_usbd_core_setup_rsp(&(p_setup_ev->setup), p_rep_buffer->p_buff, p_rep_buffer->size);
}


static ret_code_t hid_kbd_on_set_report_data_cb(nrf_drv_usbd_ep_status_t status, void * p_context)
{
    if (status != NRF_USBD_EP_OK)
    {
        return NRF_ERROR_INTERNAL;
    }

    app_usbd_hid_kbd_t const * p_kbd = p_context;
    app_usbd_hid_report_buffer_t const * p_rep_buff;
    p_rep_buff = app_usbd_hid_rep_buff_out_get(&p_kbd->specific.inst.hid_inst);

    /*Update LEDs state*/
    app_usbd_hid_kbd_ctx_t * p_kbd_ctx = hid_kbd_ctx_get(p_kbd);
    p_kbd_ctx->leds_state = p_rep_buff->p_buff[1];

    app_usbd_hid_user_ev_handler_t handler = p_kbd->specific.inst.hid_inst.user_event_handler;
    handler((app_usbd_class_inst_t const *)(p_kbd), APP_USBD_HID_USER_EVT_OUT_REPORT_READY);
    return NRF_SUCCESS;
}

/**
 * @brief @ref app_usbd_hid_interface_t::hid_kbd_on_set_report
 */
static ret_code_t hid_kbd_on_set_report(app_usbd_class_inst_t const * p_inst,
                                        app_usbd_setup_evt_t const *  p_setup_ev)
{
    app_usbd_hid_kbd_t const * p_kbd = hid_kbd_get(p_inst);

    /*Request setup data*/
    app_usbd_hid_report_buffer_t const * p_rep_buff;
    p_rep_buff = app_usbd_hid_rep_buff_out_get(&p_kbd->specific.inst.hid_inst);

    p_rep_buff->p_buff[0] = 0;
    NRF_DRV_USBD_TRANSFER_OUT(transfer, p_rep_buff->p_buff + 1, p_rep_buff->size - 1);

    ret_code_t ret;
    CRITICAL_REGION_ENTER();
    ret = app_usbd_core_setup_data_transfer(NRF_DRV_USBD_EPOUT0, &transfer);
    if (ret == NRF_SUCCESS)
    {
        app_usbd_core_setup_data_handler_desc_t desc = {
                .handler = hid_kbd_on_set_report_data_cb,
                .p_context = (app_usbd_hid_kbd_t *)p_kbd
        };

        ret = app_usbd_core_setup_data_handler_set(NRF_DRV_USBD_EPOUT0, &desc);
    }
    CRITICAL_REGION_EXIT();

    return ret;
}

/**
 * @brief @ref app_usbd_hid_interface_t::hid_kbd_ep_transfer_in
 */
static ret_code_t hid_kbd_ep_transfer_in(app_usbd_class_inst_t const * p_inst)
{
    return hid_kbd_transfer_set((app_usbd_hid_kbd_t const *)p_inst);
}

/**
 * @brief @ref app_usbd_class_interface_t::event_handler
 */
static ret_code_t hid_kbd_event_handler(app_usbd_class_inst_t const *  p_inst,
                                        app_usbd_complex_evt_t const * p_event)
{
    ASSERT(p_inst != NULL);
    ASSERT(p_event != NULL);

    app_usbd_hid_kbd_t const *  p_kbd = hid_kbd_get(p_inst);
    app_usbd_hid_inst_t const * p_hinst = &p_kbd->specific.inst.hid_inst;

    app_usbd_hid_kbd_ctx_t * p_kbd_ctx = hid_kbd_ctx_get(p_kbd);
    app_usbd_hid_ctx_t *     p_hid_ctx = &p_kbd_ctx->hid_ctx;

    /*Try handle event by generic HID event handler*/
    return app_usbd_hid_event_handler(p_inst, p_hinst, p_hid_ctx, p_event);
}

/**
 * @brief @ref app_usbd_class_interface_t::get_descriptors
 */
static const void * hid_kbd_get_descriptors(app_usbd_class_inst_t const * p_inst,
                                            size_t * p_size)
{
    ASSERT(p_size != NULL);
    app_usbd_hid_kbd_t const *  p_kbd = hid_kbd_get(p_inst);
    app_usbd_hid_inst_t const * p_hinst = &p_kbd->specific.inst.hid_inst;

    *p_size = p_hinst->raw_desc_size;
    return p_hinst->p_raw_desc;
}

/** @} */

const app_usbd_hid_methods_t app_usbd_hid_kbd_methods = {
        .on_get_report = hid_kbd_on_get_report,
        .on_set_report = hid_kbd_on_set_report,
        .ep_transfer_in = hid_kbd_ep_transfer_in,
        .ep_transfer_out = NULL,
};

const app_usbd_class_methods_t app_usbd_hid_kbd_class_methods = {
        .event_handler = hid_kbd_event_handler,
        .get_descriptors = hid_kbd_get_descriptors,
};

#endif // APP_USBD_HID_KBD_ENABLED
