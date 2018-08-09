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
#ifndef APP_USBD_HID_KBD_INTERNAL_H__
#define APP_USBD_HID_KBD_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup app_usbd_hid_kbd_internal USB HID keyboard internals
 * @ingroup app_usbd_hid_kbd
 *
 * @brief @tagAPI52840 Module with types, definitions, and API used by the HID keyboard class.
 * @{
 */

/**
 * @brief Forward declaration of HID keyboard class type.
 *
 */
APP_USBD_CLASS_FORWARD(app_usbd_hid_kbd);


/**
 * @brief HID keyboard part of class instance data.
 *
 */
typedef struct {
    app_usbd_hid_inst_t hid_inst;  //!< HID instance data.
} app_usbd_hid_kbd_inst_t;

/**
 * @brief HID keyboard context
 *
 */
typedef struct {
    app_usbd_hid_ctx_t hid_ctx; //!< HID class context.

    struct app_usbd_hid_kbd_ctx_internal_s {
        uint8_t modifier;       //!< Keyboard modifier state @ref app_usbd_hid_kbd_modifier_t.
        uint8_t reserved;       //!< Reserved value.
        uint8_t key_table[6];   //!< Keyboard keys table @ref app_usbd_hid_kbd_codes_t.
    } rep;

    uint8_t report_buff[8];     //!< Raw report buffer.
    uint8_t leds_state;         //!< Output report LEDs state.
    uint8_t set_report;         //!< Set report flag.
} app_usbd_hid_kbd_ctx_t;

/**
 * @brief HID keyboard configuration macro.
 *
 * Used by @ref APP_USBD_HID_KBD_GLOBAL_DEF.
 *
 *
 */
#define APP_USBD_HID_KBD_CONFIG(iface, ep) ((iface, ep))


/**
 * @brief Specific class constant data for HID keyboard class.
 */
#define APP_USBD_HID_KBD_INSTANCE_SPECIFIC_DEC app_usbd_hid_kbd_inst_t inst;

/**
 * @brief Specific class data for HID keyboard class.
 */
#define APP_USBD_HID_KBD_DATA_SPECIFIC_DEC app_usbd_hid_kbd_ctx_t ctx;


/**
 * @brief Configure internal part of HID keyboard instance.
 *
 * @param report_buff_in    Input report buffers array.
 * @param report_buff_out   Output report buffer.
 * @param user_ev_handler   User event handler.
 * @param subclass_boot     Subclass boot. (@ref app_usbd_hid_subclass_t)
 */
#define APP_USBD_HID_KBD_INST_CONFIG(report_buff_in,                            \
                                     report_buff_out,                           \
                                     user_ev_handler,                           \
                                     subclass_boot)                             \
    .inst = {                                                                   \
         .hid_inst = APP_USBD_HID_INST_CONFIG(keyboard_descs,                   \
                                              subclass_boot,                    \
                                              APP_USBD_HID_PROTO_KEYBOARD,      \
                                              report_buff_in,                   \
                                              report_buff_out,                  \
                                              user_ev_handler,                  \
                                              &app_usbd_hid_kbd_methods),       \
}


/**
 * @brief Public HID keyboard interface.
 */
extern const app_usbd_hid_methods_t app_usbd_hid_kbd_methods;

/**
 * @brief Public HID keyboard class interface.
 */
extern const app_usbd_class_methods_t app_usbd_hid_kbd_class_methods;

/**
 * @brief Global definition of @ref app_usbd_hid_kbd_t class.
 *
 * @ref  APP_USBD_HID_KBD_GLOBAL_DEF
 */
#define APP_USBD_HID_KBD_GLOBAL_DEF_INTERNAL(instance_name,                        \
                                             interface_number,                     \
                                             endpoint,                             \
                                             user_ev_handler,                      \
                                             subclass_boot)                        \
    static app_usbd_hid_report_buffer_t CONCAT_2(instance_name, _in)[1];           \
    APP_USBD_HID_GENERIC_GLOBAL_OUT_REP_DEF(CONCAT_2(instance_name, _out), 1 + 1); \
    APP_USBD_CLASS_INST_GLOBAL_DEF(                                                \
        instance_name,                                                             \
        app_usbd_hid_kbd,                                                          \
        &app_usbd_hid_kbd_class_methods,                                           \
        APP_USBD_HID_KBD_CONFIG(interface_number, endpoint),                       \
        (APP_USBD_HID_KBD_INST_CONFIG(CONCAT_2(instance_name, _in),                \
                                      &CONCAT_2(instance_name, _out),              \
                                      user_ev_handler,                             \
                                      subclass_boot))                              \
    )


/** @} */


#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_HID_KBD_INTERNAL_H__ */
