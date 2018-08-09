/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
#ifndef APP_USBD_HID_MOUSE_INTERNAL_H__
#define APP_USBD_HID_MOUSE_INTERNAL_H__

/**
 * @defgroup app_usbd_hid_mouse_internals USB HID mouse internals
 * @ingroup app_usbd_hid_mouse
 *
 * @brief @tagAPI52840 Module with types, definitions, and API used by the HID mouse class.
 * @{
 */

/**
 * @brief Forward declaration of HID mouse class type.
 */
APP_USBD_CLASS_FORWARD(app_usbd_hid_mouse);


/**
 * @brief HID mouse part of class instance data.
 */
typedef struct {
    app_usbd_hid_inst_t hid_inst;      //!< HID instance data.
    const uint8_t       button_count;  //!< Number of buttons mouse specific.
} app_usbd_hid_mouse_inst_t;

/**
 * @brief HID mouse context.
 */
typedef struct {
    app_usbd_hid_ctx_t hid_ctx; //!< HID class context.

    int16_t acc_x_axis;         //!< Mouse specific. Accumulated x axis offset.
    int16_t acc_y_axis;         //!< Mouse specific. Accumulated y axis offset.
    int16_t acc_scroll;         //!< Mouse specific. Accumulated scroll offset.
    uint8_t button_state;       //!< Mouse specific. Actual button state. Bitfield of maximum 8 buttons states.
    uint8_t report_buff[4];
} app_usbd_hid_mouse_ctx_t;


/**
 * @brief HID mouse configuration macro.
 *
 * Used by @ref APP_USBD_HID_MOUSE_GLOBAL_DEF.
 *
 */
#define APP_USBD_HID_MOUSE_CONFIG(iface, ep) ((iface, ep))


/**
 * @brief Specific class constant data for HID mouse class.
 */
#define APP_USBD_HID_MOUSE_INSTANCE_SPECIFIC_DEC app_usbd_hid_mouse_inst_t inst;

/**
 * @brief Specific class data for HID mouse class.
 */
#define APP_USBD_HID_MOUSE_DATA_SPECIFIC_DEC app_usbd_hid_mouse_ctx_t ctx;


/**
 * @brief HID mouse descriptors config macro
 *
 * @ref app_usbd_hid_mouse_inst_t
 *
 */
#define APP_USBD_HID_MOUSE_DSC_CONFIG(interface_number, endpoint, rep_desc) {  \
        APP_USBD_HID_MOUSE_INTERFACE_DSC(interface_number)                     \
        APP_USBD_HID_MOUSE_HID_DSC(rep_desc)                                   \
        APP_USBD_HID_MOUSE_EP_DSC(endpoint)                                    \
}

/**
 * @brief Configure internal part of HID mouse instance.
 *
 * @param report_buff_in    Input report buffers array.
 * @param report_buff_out   Output report buffer.
 * @param user_ev_handler   User event handler.
 * @param bcnt              Mouse button count.
 * @param subclass_boot     Subclass boot. (@ref app_usbd_hid_subclass_t)
 */
#define APP_USBD_HID_MOUSE_INST_CONFIG(report_buff_in,                      \
                                       report_buff_out,                     \
                                       user_ev_handler,                     \
                                       bcnt,                                \
                                       subclass_boot)                       \
    .inst = {                                                               \
        .hid_inst = APP_USBD_HID_INST_CONFIG(mouse_descs,                   \
                                             subclass_boot,                 \
                                             APP_USBD_HID_PROTO_MOUSE,      \
                                             report_buff_in,                \
                                             report_buff_out,               \
                                             user_ev_handler,               \
                                             &app_usbd_hid_mouse_methods),  \
        .button_count = bcnt,                                               \
    }

/**
 * @brief Public HID mouse interface.
 */
extern const app_usbd_hid_methods_t app_usbd_hid_mouse_methods;

/**
 * @brief Public HID mouse class interface.
 */
extern const app_usbd_class_methods_t app_usbd_hid_mouse_class_methods;

/**
 * @brief Global definition of app_usbd_hid_mouse_t class.
 *
 * @ref  APP_USBD_HID_MOUSE_GLOBAL_DEF
 */
#define APP_USBD_HID_MOUSE_GLOBAL_DEF_INTERNAL(instance_name,               \
                                               interface_number,            \
                                               endpoint,                    \
                                               bcnt,                        \
                                               user_ev_handler,             \
                                               subclass_boot)               \
    static app_usbd_hid_report_buffer_t  CONCAT_2(instance_name, _in)[1];   \
    APP_USBD_CLASS_INST_GLOBAL_DEF(                                         \
        instance_name,                                                      \
        app_usbd_hid_mouse,                                                 \
        &app_usbd_hid_mouse_class_methods,                                  \
        APP_USBD_HID_MOUSE_CONFIG(interface_number, endpoint),              \
        (APP_USBD_HID_MOUSE_INST_CONFIG(CONCAT_2(instance_name, _in),       \
                                        NULL,                               \
                                        user_ev_handler,                    \
                                        bcnt,                               \
                                        subclass_boot))                     \
    )


/** @} */

#endif /* APP_USBD_HID_MOUSE_INTERNAL_H__ */
