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
#if APP_USBD_HID_MOUSE_ENABLED
#include <string.h>

#include "sdk_common.h"
#include "app_usbd_hid_mouse.h"
#include "app_util_platform.h"


/**
 * @defgroup app_usbd_hid_mouse_internal USBD HID Mouse internals
 * @{
 * @ingroup app_usbd_hid_mouse
 * @internal
 */

/**
 * @brief Auxiliary function to access HID mouse context data.
 *
 * @param[in] p_inst class instance data.
 *
 * @return HID mouse instance data context.
 */
static inline app_usbd_hid_mouse_ctx_t * hid_mouse_ctx_get(app_usbd_hid_mouse_t const * p_mouse)
{
    ASSERT(p_mouse != NULL);
    ASSERT(p_mouse->specific.p_data != NULL);
    return &p_mouse->specific.p_data->ctx;
}

/**
 * @brief Auxiliary function to access HID mouse instance data.
 *
 * @param[in] p_inst class instance data.
 *
 * @return HID mouse instance.
 */
static inline app_usbd_hid_mouse_t const * hid_mouse_get(app_usbd_class_inst_t const * p_inst)
{
    ASSERT(p_inst != NULL);
    return (app_usbd_hid_mouse_t const *)p_inst;
}

/**
 * @brief Returns mouse report buffer handle.
 *
 * @param[in] p_kbd HID keyboard instance.
 *
 * @return HID report buffer.
 */
static inline
app_usbd_hid_report_buffer_t const * hid_mouse_rep_buffer_get(app_usbd_hid_mouse_t const * p_mouse)
{
    ASSERT(p_mouse != NULL);
    app_usbd_hid_inst_t const * p_hinst = &p_mouse->specific.inst.hid_inst;
    app_usbd_hid_mouse_ctx_t *            p_mouse_ctx = hid_mouse_ctx_get(p_mouse);
    app_usbd_hid_report_buffer_t *        p_rep_buff = app_usbd_hid_rep_buff_in_get(p_hinst);

    p_rep_buff->p_buff = p_mouse_ctx->report_buff;
    p_rep_buff->size = sizeof(p_mouse_ctx->report_buff);

    /*Mouse has only one report input report buffer */
    return app_usbd_hid_rep_buff_in_get(p_hinst);
}

/**@brief Auxiliary function to get report value from internal accumulated value.
 *
 * @param[in] acc Accumulated XY axis or scroll.
 *
 * @return Offset value that could be written directly to report buffer.
 */
static inline int8_t hid_mouse_axis_acc_get(int16_t acc)
{
    if (acc > INT8_MAX)
    {
        return INT8_MAX;
    }

    if (acc < INT8_MIN)
    {
        return INT8_MIN;
    }

    return acc;
}

/**@brief Auxiliary function to prepare report transfer buffer to next transfer.
 *
 * @param[in] p_mouse_ctx Mouse internal context.
 *
 * @retval true     Next transfer is required.
 * @retval false    Next transfer is not required.
 */
static inline bool hid_mouse_transfer_next(app_usbd_hid_mouse_t const * p_mouse)
{

    app_usbd_hid_mouse_ctx_t *            p_mouse_ctx = hid_mouse_ctx_get(p_mouse);
    app_usbd_hid_report_buffer_t const *  p_rep_buffer = hid_mouse_rep_buffer_get(p_mouse);

    uint8_t * p_buff = p_rep_buffer->p_buff;

    /*Save last buttons state*/
    uint8_t last_button_state = p_buff[0];

    /*Button state*/
    p_buff[0] = p_mouse_ctx->button_state;

    /*Axis X*/
    int8_t val_x = hid_mouse_axis_acc_get(p_mouse_ctx->acc_x_axis);
    p_mouse_ctx->acc_x_axis -= val_x;
    p_buff[1] = val_x;

    /*Axis Y*/
    int8_t val_y = hid_mouse_axis_acc_get(p_mouse_ctx->acc_y_axis);
    p_mouse_ctx->acc_y_axis -= val_y;
    p_buff[2] = val_y;

    /*Scroll*/
    int8_t val_scroll = hid_mouse_axis_acc_get(p_mouse_ctx->acc_scroll);
    p_mouse_ctx->acc_scroll -= val_scroll;
    p_buff[3] = val_scroll;

    if (val_x || val_y || val_scroll)
    {
        /*New transfer is required if any of mouse relative position is not zero*/
        return true;
    }

    if (last_button_state != p_buff[0])
    {
        /*New transfer is required if button state has changed*/
        return true;
    }

    return false;
}

/**
 * @brief Triggers IN endpoint transfer.
 *
 * @param[in] p_mouse HID mouse instance.
 *
 * @return Standard error code.
 */
static inline ret_code_t hid_mouse_transfer_set(app_usbd_hid_mouse_t const * p_mouse)
{
    app_usbd_class_inst_t const * p_inst = (app_usbd_class_inst_t const *)p_mouse;
    app_usbd_hid_mouse_ctx_t *    p_mouse_ctx = hid_mouse_ctx_get(p_mouse);

    nrf_drv_usbd_ep_t ep_addr = app_usbd_hid_epin_addr_get(p_inst);

    app_usbd_hid_state_flag_clr(&p_mouse_ctx->hid_ctx, APP_USBD_HID_STATE_FLAG_TRANS_IN_PROGRESS);
    if (!hid_mouse_transfer_next(p_mouse))
    {
        /* Transfer buffer hasn't changed since last transfer. No need to setup
         * next transfer.
         * */
        return NRF_SUCCESS;
    }

    app_usbd_hid_report_buffer_t const * p_rep_buffer = hid_mouse_rep_buffer_get(p_mouse);

    NRF_DRV_USBD_TRANSFER_IN(transfer, p_rep_buffer->p_buff, p_rep_buffer->size);

    ret_code_t ret;
    CRITICAL_REGION_ENTER();
    ret = app_usbd_core_ep_transfer(ep_addr, &transfer);
    if (ret == NRF_SUCCESS)
    {
        app_usbd_hid_state_flag_set(&p_mouse_ctx->hid_ctx,
                                    APP_USBD_HID_STATE_FLAG_TRANS_IN_PROGRESS);
    }
    CRITICAL_REGION_EXIT();

    return ret;
}

/**
 * @brief Checks if adding would cause 16 bit signed integer overflow.
 *
 * @param[in] acc   Signed 16 bit accumulator to test.
 * @param[in] value Value to add to accumulator.
 *
 * @retval true     Overflow detected.
 * @retval false    No overflow detected.
 */
static inline bool hid_mouse_acc_overflow_check(int16_t acc, int8_t val)
{
    if (((int32_t)acc + val) > INT16_MAX)
    {
        return true;
    }

    if (((int32_t)acc + val) < INT16_MIN)
    {
        return true;
    }

    return false;
}

ret_code_t app_usbd_hid_mouse_x_move(app_usbd_hid_mouse_t const * p_mouse, int8_t offset)
{
    app_usbd_hid_mouse_ctx_t * p_mouse_ctx = hid_mouse_ctx_get(p_mouse);
    if (!app_usbd_hid_state_valid(&p_mouse_ctx->hid_ctx))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (offset == 0)
    {
        /*No position change*/
        return NRF_SUCCESS;
    }

    if (hid_mouse_acc_overflow_check(p_mouse_ctx->acc_y_axis, offset))
    {
        /*Overflow detected*/
        return NRF_ERROR_BUSY;
    }

    app_usbd_hid_access_lock(&p_mouse_ctx->hid_ctx);
    p_mouse_ctx->acc_x_axis += offset;
    app_usbd_hid_access_unlock(&p_mouse_ctx->hid_ctx);

    if (app_usbd_hid_trans_required(&p_mouse_ctx->hid_ctx))
    {
        /*New transfer need to be triggered*/
        return hid_mouse_transfer_set(p_mouse);
    }

    return NRF_SUCCESS;
}

ret_code_t app_usbd_hid_mouse_y_move(app_usbd_hid_mouse_t const * p_mouse, int8_t offset)
{
    app_usbd_hid_mouse_ctx_t * p_mouse_ctx = hid_mouse_ctx_get(p_mouse);
    if (!app_usbd_hid_state_valid(&p_mouse_ctx->hid_ctx))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (offset == 0)
    {
        /*No position change*/
        return NRF_SUCCESS;
    }

    if (hid_mouse_acc_overflow_check(p_mouse_ctx->acc_y_axis, offset))
    {
        /*Overflow detected*/
        return NRF_ERROR_BUSY;
    }

    app_usbd_hid_access_lock(&p_mouse_ctx->hid_ctx);
    p_mouse_ctx->acc_y_axis += offset;
    app_usbd_hid_access_unlock(&p_mouse_ctx->hid_ctx);

    if (app_usbd_hid_trans_required(&p_mouse_ctx->hid_ctx))
    {
        /*New transfer need to be triggered*/
        return hid_mouse_transfer_set(p_mouse);
    }

    return NRF_SUCCESS;
}

ret_code_t app_usbd_hid_mouse_scroll_move(app_usbd_hid_mouse_t const * p_mouse, int8_t offset)
{
    app_usbd_hid_mouse_ctx_t * p_mouse_ctx = hid_mouse_ctx_get(p_mouse);
    if (!app_usbd_hid_state_valid(&p_mouse_ctx->hid_ctx))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (offset == 0)
    {
        /*No position change*/
        return NRF_SUCCESS;
    }

    if (hid_mouse_acc_overflow_check(p_mouse_ctx->acc_scroll, offset))
    {
        /*Overflow detected*/
        return NRF_ERROR_BUSY;
    }

    app_usbd_hid_access_lock(&p_mouse_ctx->hid_ctx);
    p_mouse_ctx->acc_scroll += offset;
    app_usbd_hid_access_unlock(&p_mouse_ctx->hid_ctx);

    if (app_usbd_hid_trans_required(&p_mouse_ctx->hid_ctx))
    {
        /*New transfer need to be triggered*/
        return hid_mouse_transfer_set(p_mouse);
    }

    return NRF_SUCCESS;
}

ret_code_t app_usbd_hid_mouse_button_state(app_usbd_hid_mouse_t const * p_mouse,
                                           uint8_t button_id,
                                           bool state)
{
    ASSERT(button_id < 8);
    app_usbd_hid_mouse_ctx_t * p_mouse_ctx = hid_mouse_ctx_get(p_mouse);

    if (button_id >= p_mouse->specific.inst.button_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    if (!app_usbd_hid_state_valid(&p_mouse_ctx->hid_ctx))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (IS_SET(p_mouse_ctx->button_state, button_id) == (state ? 1 : 0))
    {
        return NRF_SUCCESS;
    }

    app_usbd_hid_access_lock(&p_mouse_ctx->hid_ctx);
    if (state)
    {
        SET_BIT(p_mouse_ctx->button_state, button_id);
    }
    else
    {
        CLR_BIT(p_mouse_ctx->button_state, button_id);
    }
    app_usbd_hid_access_unlock(&p_mouse_ctx->hid_ctx);

    if (app_usbd_hid_trans_required(&p_mouse_ctx->hid_ctx))
    {
        /*New transfer need to be triggered*/
        return hid_mouse_transfer_set(p_mouse);
    }

    return NRF_SUCCESS;
}

/**
 * @brief @ref app_usbd_hid_interface_t::on_get_report
 */
static ret_code_t hid_mouse_on_get_report(app_usbd_class_inst_t const * p_inst,
                                        app_usbd_setup_evt_t const * p_setup_ev)
{
    app_usbd_hid_mouse_t const * p_mouse = hid_mouse_get(p_inst);
    app_usbd_hid_report_buffer_t const * p_rep_buffer = hid_mouse_rep_buffer_get(p_mouse);

    return app_usbd_core_setup_rsp(&(p_setup_ev->setup), p_rep_buffer->p_buff, p_rep_buffer->size);
}

/**
 * @brief @ref app_usbd_hid_interface_t::on_set_report
 */
static ret_code_t hid_mouse_on_set_report(app_usbd_class_inst_t const * p_inst,
                                        app_usbd_setup_evt_t const * p_setup_ev)
{
    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief @ref app_usbd_hid_interface_t::ep_transfer_set
 */
static ret_code_t hid_mouse_ep_transfer_in(app_usbd_class_inst_t const * p_inst)
{
    return hid_mouse_transfer_set((app_usbd_hid_mouse_t const *)p_inst);
}

/**
 * @brief @ref app_usbd_class_interface_t::event_handler
 */
static ret_code_t hid_mouse_event_handler(app_usbd_class_inst_t const * p_inst,
                                          app_usbd_complex_evt_t const * p_event)
{
    ASSERT(p_inst != NULL);
    ASSERT(p_event != NULL);

    app_usbd_hid_mouse_t const * p_mouse = hid_mouse_get(p_inst);
    app_usbd_hid_inst_t const * p_hinst = &p_mouse->specific.inst.hid_inst;

    app_usbd_hid_mouse_ctx_t * p_mouse_ctx = hid_mouse_ctx_get(p_mouse);
    app_usbd_hid_ctx_t * p_hid_ctx = &p_mouse_ctx->hid_ctx;


    ret_code_t ret = NRF_SUCCESS;
    switch (p_event->app_evt.type)
    {
        default:
            ret = NRF_ERROR_NOT_SUPPORTED;
            break;
    }

    if (ret != NRF_ERROR_NOT_SUPPORTED)
    {
        /* Event was processed by specific handler */
        return ret;
    }

    /*Try handle event by generic HID event handler*/
    return app_usbd_hid_event_handler(p_inst, p_hinst, p_hid_ctx, p_event);
}

/**
 * @brief @ref app_usbd_class_interface_t::get_descriptors
 */
static const void * hid_mouse_get_descriptors(app_usbd_class_inst_t const * p_inst,
                                              size_t * p_size)
{
    ASSERT(p_size != NULL);
    app_usbd_hid_mouse_t const * p_mouse = hid_mouse_get(p_inst);
    app_usbd_hid_inst_t const * p_hinst = &p_mouse->specific.inst.hid_inst;

    *p_size = p_hinst->raw_desc_size;
    return p_hinst->p_raw_desc;
}

/** @} */

const app_usbd_hid_methods_t app_usbd_hid_mouse_methods = {
        .on_get_report = hid_mouse_on_get_report,
        .on_set_report = hid_mouse_on_set_report,
        .ep_transfer_in = hid_mouse_ep_transfer_in,
        .ep_transfer_out = NULL,
};

const app_usbd_class_methods_t app_usbd_hid_mouse_class_methods = {
        .event_handler = hid_mouse_event_handler,
        .get_descriptors = hid_mouse_get_descriptors,
};

#endif // APP_USBD_HID_MOUSE_ENABLED
