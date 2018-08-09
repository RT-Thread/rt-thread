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
#if NRF_MODULE_ENABLED(APP_USBD_HID_KBD)

#include <string.h>
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
    app_usbd_hid_inst_t const    * p_hinst    = &p_kbd->specific.inst.hid_inst;
    app_usbd_hid_kbd_ctx_t       * p_kbd_ctx  = hid_kbd_ctx_get(p_kbd);
    app_usbd_hid_report_buffer_t * p_rep_buff = app_usbd_hid_rep_buff_in_get(p_hinst);

    p_rep_buff->p_buff = p_kbd_ctx->report_buff;
    p_rep_buff->size   = sizeof(p_kbd_ctx->report_buff);

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
    app_usbd_hid_kbd_ctx_t             * p_kbd_ctx    = hid_kbd_ctx_get(p_kbd);

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
    app_usbd_class_inst_t const * p_inst    = (app_usbd_class_inst_t const *)p_kbd;
    app_usbd_hid_kbd_ctx_t      * p_kbd_ctx = hid_kbd_ctx_get(p_kbd);

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
    ret = app_usbd_ep_transfer(ep_addr, &transfer);
    if (ret == NRF_SUCCESS)
    {
        app_usbd_hid_state_flag_set(&p_kbd_ctx->hid_ctx, APP_USBD_HID_STATE_FLAG_TRANS_IN_PROGRESS);
    }
    CRITICAL_REGION_EXIT();

    return ret;
}


ret_code_t app_usbd_hid_kbd_modifier_state_set(app_usbd_hid_kbd_t const  * p_kbd,
                                               app_usbd_hid_kbd_modifier_t modifier,
                                               bool                        state)
{
    app_usbd_hid_kbd_ctx_t * p_kbd_ctx    = hid_kbd_ctx_get(p_kbd);
    bool                     actual_state = (p_kbd_ctx->rep.modifier & modifier) != 0;

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
                                        bool                       press)
{
    app_usbd_hid_kbd_ctx_t * p_kbd_ctx   = hid_kbd_ctx_get(p_kbd);
    uint8_t                * destination = NULL;

    if (press)
    {
        for (size_t i = 0; i < ARRAY_SIZE(p_kbd_ctx->rep.key_table); ++i)
        {
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
        for (size_t i = 0; i < ARRAY_SIZE(p_kbd_ctx->rep.key_table); ++i)
        {
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

const void * app_usbd_hid_kbd_in_report_get(app_usbd_hid_kbd_t const * p_kbd,
                                            size_t * p_size)
{
    app_usbd_hid_inst_t const * p_kinst = &p_kbd->specific.inst.hid_inst;
    *p_size = p_kinst->p_rep_buffer_in->size;
    return p_kinst->p_rep_buffer_in->p_buff;
}

const void * app_usbd_hid_kbd_out_report_get(app_usbd_hid_kbd_t const * p_kbd,
                                             size_t * p_size)
{
    app_usbd_hid_inst_t const * p_kinst = &p_kbd->specific.inst.hid_inst;
    *p_size = p_kinst->p_rep_buffer_out->size;
    return p_kinst->p_rep_buffer_out->p_buff;
}

/**
 * @brief @ref app_usbd_hid_interface_t::on_get_report
 */
static ret_code_t hid_kbd_on_get_report(app_usbd_class_inst_t const * p_inst,
                                        app_usbd_setup_evt_t const  * p_setup_ev)
{
    app_usbd_hid_kbd_t const * p_kinst = hid_kbd_get(p_inst);
    uint8_t const * p_rep_buffer = NULL;
    size_t buffer_size = 0;

    if (p_setup_ev->setup.wValue.hb == APP_USBD_HID_REPORT_TYPE_INPUT)
    {
        p_rep_buffer = app_usbd_hid_kbd_in_report_get(p_kinst, &buffer_size);
    }
    else if (p_setup_ev->setup.wValue.hb == APP_USBD_HID_REPORT_TYPE_OUTPUT)
    {
        p_rep_buffer = app_usbd_hid_kbd_out_report_get(p_kinst, &buffer_size);
    }
    else
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    /* Return LEDs state (only the second byte) */
    return app_usbd_core_setup_rsp(&(p_setup_ev->setup), p_rep_buffer + 1, buffer_size - 1);
}


static ret_code_t hid_kbd_on_set_report_data_cb(nrf_drv_usbd_ep_status_t status, void * p_context)
{
    if (status != NRF_USBD_EP_OK)
    {
        return NRF_ERROR_INTERNAL;
    }

    app_usbd_hid_kbd_t const           * p_kbd = p_context;
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
                                        app_usbd_setup_evt_t const  * p_setup_ev)
{
    app_usbd_hid_kbd_t const * p_kbd = hid_kbd_get(p_inst);

    /*Request setup data*/
    app_usbd_hid_report_buffer_t const * p_rep_buff;

    p_rep_buff = app_usbd_hid_rep_buff_out_get(&p_kbd->specific.inst.hid_inst);

    p_rep_buff->p_buff[0] = 0;
    NRF_DRV_USBD_TRANSFER_OUT(transfer, p_rep_buff->p_buff + 1, p_rep_buff->size - 1);

    ret_code_t ret;
    CRITICAL_REGION_ENTER();
    ret = app_usbd_ep_transfer(NRF_DRV_USBD_EPOUT0, &transfer);
    if (ret == NRF_SUCCESS)
    {
        app_usbd_core_setup_data_handler_desc_t desc = {
            .handler   = hid_kbd_on_set_report_data_cb,
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
static ret_code_t hid_kbd_event_handler(app_usbd_class_inst_t const  * p_inst,
                                        app_usbd_complex_evt_t const * p_event)
{
    ASSERT(p_inst != NULL);
    ASSERT(p_event != NULL);

    app_usbd_hid_kbd_t const  * p_kbd   = hid_kbd_get(p_inst);
    app_usbd_hid_inst_t const * p_hinst = &p_kbd->specific.inst.hid_inst;

    app_usbd_hid_kbd_ctx_t * p_kbd_ctx = hid_kbd_ctx_get(p_kbd);
    app_usbd_hid_ctx_t     * p_hid_ctx = &p_kbd_ctx->hid_ctx;

    /*Try handle event by generic HID event handler*/
    return app_usbd_hid_event_handler(p_inst, p_hinst, p_hid_ctx, p_event);
}


static uint8_t hid_kbd_get_class_descriptors_count(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_hid_kbd_t const  * p_kbd   = hid_kbd_get(p_inst);
    app_usbd_hid_inst_t const * p_hinst = &p_kbd->specific.inst.hid_inst;

    return p_hinst->subclass_desc_count;
}


static app_usbd_descriptor_t hid_kbd_get_class_descriptors_type(
    app_usbd_class_inst_t const * p_inst,
    uint8_t                       desc_num)
{
    app_usbd_hid_kbd_t const  * p_kbd   = hid_kbd_get(p_inst);
    app_usbd_hid_inst_t const * p_hinst = &p_kbd->specific.inst.hid_inst;

    return p_hinst->p_subclass_desc[desc_num]->type;
}


static size_t hid_kbd_get_class_descriptors_length(app_usbd_class_inst_t const * p_inst,
                                                   uint8_t                       desc_num)
{
    app_usbd_hid_kbd_t const  * p_kbd   = hid_kbd_get(p_inst);
    app_usbd_hid_inst_t const * p_hinst = &p_kbd->specific.inst.hid_inst;

    return p_hinst->p_subclass_desc[desc_num]->size;
}


static uint8_t hid_kbd_get_class_descriptors_data(app_usbd_class_inst_t const * p_inst,
                                                  uint8_t                       desc_num,
                                                  uint32_t                      cur_byte)
{
    app_usbd_hid_kbd_t const  * p_kbd   = hid_kbd_get(p_inst);
    app_usbd_hid_inst_t const * p_hinst = &p_kbd->specific.inst.hid_inst;

    return p_hinst->p_subclass_desc[desc_num]->p_data[cur_byte];
}


static bool hid_kbd_feed_descriptors(app_usbd_class_descriptor_ctx_t                   * p_ctx,
                                     app_usbd_class_inst_t const                       * p_inst,
                                     uint8_t                                           * p_buff,
                                     size_t                                              max_size)
{
    static uint8_t ifaces   = 0;
    ifaces = app_usbd_class_iface_count_get(p_inst);
    app_usbd_hid_kbd_t const * p_kbd = hid_kbd_get(p_inst);

    APP_USBD_CLASS_DESCRIPTOR_BEGIN(p_ctx, p_buff, max_size);

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
        APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_HID_CLASS); // bInterfaceClass = HID
        APP_USBD_CLASS_DESCRIPTOR_WRITE(p_kbd->specific.inst.hid_inst.subclass_boot); // bInterfaceSubclass (Boot Interface)
        APP_USBD_CLASS_DESCRIPTOR_WRITE(p_kbd->specific.inst.hid_inst.protocol); // bInterfaceProtocol
        APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // iInterface

        /* HID DESCRIPTOR */
        APP_USBD_CLASS_DESCRIPTOR_WRITE(0x09); // bLength
        APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_HID_DESCRIPTOR_HID);  // bDescriptorType = HID
        APP_USBD_CLASS_DESCRIPTOR_WRITE(LSB_16(APP_USBD_HID_BCD_VER)); // bcdHID LSB
        APP_USBD_CLASS_DESCRIPTOR_WRITE(MSB_16(APP_USBD_HID_BCD_VER)); // bcdHID MSB
        APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_HID_COUNTRY_NOT_SUPPORTED); // bCountryCode
        APP_USBD_CLASS_DESCRIPTOR_WRITE(hid_kbd_get_class_descriptors_count(p_inst)); // bNumDescriptors

        static uint8_t class_desc_cnt = 0;
        class_desc_cnt = hid_kbd_get_class_descriptors_count(p_inst);
        static uint8_t  j              = 0;
        static uint16_t class_desc_len = 0;

        for (j = 0; j < class_desc_cnt; j++)
        {
            APP_USBD_CLASS_DESCRIPTOR_WRITE(hid_kbd_get_class_descriptors_type(p_inst, j)); // bDescriptorType

            class_desc_len = hid_kbd_get_class_descriptors_length(p_inst, j);
            APP_USBD_CLASS_DESCRIPTOR_WRITE(LSB_16(class_desc_len)); // wDescriptorLength LSB
            APP_USBD_CLASS_DESCRIPTOR_WRITE(MSB_16(class_desc_len)); // wDescriptorLength MSB
        }

        static uint8_t endpoints = 0;
        endpoints = app_usbd_class_iface_ep_count_get(p_cur_iface);

        for (j = 0; j < endpoints; j++)
        {
            /* ENDPOINT DESCRIPTOR */
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x07); // bLengths
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_ENDPOINT); // bDescriptorType = Endpoint

            static app_usbd_class_ep_conf_t const * p_cur_ep = NULL;
            p_cur_ep = app_usbd_class_iface_ep_get(p_cur_iface, i);
            APP_USBD_CLASS_DESCRIPTOR_WRITE(app_usbd_class_ep_address_get(p_cur_ep)); // bEndpointAddress
            APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_EP_ATTR_TYPE_INTERRUPT); // bmAttributes
            APP_USBD_CLASS_DESCRIPTOR_WRITE(LSB_16(NRF_DRV_USBD_EPSIZE)); // wMaxPacketSize LSB
            APP_USBD_CLASS_DESCRIPTOR_WRITE(MSB_16(NRF_DRV_USBD_EPSIZE)); // wMaxPacketSize MSB
            APP_USBD_CLASS_DESCRIPTOR_WRITE(0x01); // bInterval
        }
    }

    APP_USBD_CLASS_DESCRIPTOR_END();
}

static bool hid_kbd_feed_subclass_descriptor(app_usbd_class_descriptor_ctx_t  * p_ctx,
                                                  app_usbd_class_inst_t const * p_inst,
                                                  uint8_t                     * p_buff,
                                                  size_t                        max_size,
                                                  uint8_t                       index)
{
    APP_USBD_CLASS_DESCRIPTOR_BEGIN(p_ctx, p_buff, max_size);

    /* PHYSICAL AND REPORT DESCRIPTORS */
    static uint32_t cur_byte      = 0;
    static size_t   sub_desc_size = 0;
    sub_desc_size = hid_kbd_get_class_descriptors_length(p_inst, index);

    for (cur_byte = 0; cur_byte <= sub_desc_size; cur_byte++)
    {
        APP_USBD_CLASS_DESCRIPTOR_WRITE(hid_kbd_get_class_descriptors_data(p_inst, index, cur_byte));
    }

    APP_USBD_CLASS_DESCRIPTOR_END();
}

/** @} */

const app_usbd_hid_methods_t app_usbd_hid_kbd_methods = {
    .on_get_report   = hid_kbd_on_get_report,
    .on_set_report   = hid_kbd_on_set_report,
    .ep_transfer_in  = hid_kbd_ep_transfer_in,
    .ep_transfer_out = NULL,
    .feed_subclass_descriptor = hid_kbd_feed_subclass_descriptor,
};

const app_usbd_class_methods_t app_usbd_hid_kbd_class_methods = {
    .event_handler            = hid_kbd_event_handler,
    .feed_descriptors         = hid_kbd_feed_descriptors,
};

#endif //NRF_MODULE_ENABLED(APP_USBD_HID_KBD)
