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
#ifndef APP_USBD_HID_MOUSE_H__
#define APP_USBD_HID_MOUSE_H__

#include <stdint.h>
#include <stdbool.h>

#include "nrf_drv_usbd.h"
#include "app_usbd_class_base.h"
#include "app_usbd_hid_types.h"
#include "app_usbd_hid.h"
#include "app_usbd.h"
#include "app_usbd_core.h"
#include "app_usbd_descriptor.h"
#include "app_usbd_hid_mouse_desc.h"
#include "app_usbd_hid_mouse_internal.h"

/**
 * @defgroup app_usbd_hid_mouse USB HID mouse
 * @ingroup app_usbd_hid
 *
 * @brief @tagAPI52840 Module with types, definitions, and API used by the HID mouse class.
 * @{
 */

#ifdef DOXYGEN
/**
 * @brief HID mouse class instance type.
 *
 * @ref APP_USBD_CLASS_TYPEDEF
 */
typedef struct { } app_usbd_hid_mouse_t;
#else
/*lint -save -e10 -e26 -e123 -e505 */
APP_USBD_CLASS_TYPEDEF(app_usbd_hid_mouse,                      \
            APP_USBD_HID_MOUSE_CONFIG(0, NRF_DRV_USBD_EPIN1),   \
            APP_USBD_HID_MOUSE_INSTANCE_SPECIFIC_DEC,           \
            APP_USBD_HID_MOUSE_DATA_SPECIFIC_DEC                \
);
/*lint -restore*/
#endif

/**
 * @brief Global definition macro of app_usbd_hid_mouse_t class.
 *
 * @param instance_name     Name of global instance.
 * @param interface_number  Unique interface number.
 * @param endpoint          Input endpoint (@ref nrf_drv_usbd_ep_t).
 * @param bcnt              Mouse button count (from 1 to 8).
 * @param user_ev_handler   User event handler (optional).
 * @param subclass_boot     Subclass boot (@ref app_usbd_hid_subclass_t).
 *
 * @note This macro is just simplified version of @ref APP_USBD_HID_MOUSE_GLOBAL_DEF_INTERNAL.
 *
 * @code
   APP_USBD_HID_MOUSE_GLOBAL_DEF(my_awesome_mouse, 0, NRF_DRV_USBD_EPIN1, 3, NULL);
 * @endcode
 */
#define APP_USBD_HID_MOUSE_GLOBAL_DEF(instance_name,                                                    \
                                      interface_number,                                                 \
                                      endpoint,                                                         \
                                      bcnt,                                                             \
                                      user_ev_handler,                                                  \
                                      subclass_boot)                                                    \
    APP_USBD_HID_GENERIC_SUBCLASS_REPORT_DESC(mouse_desc, APP_USBD_HID_MOUSE_REPORT_DSC_BUTTON(bcnt));  \
    static const app_usbd_hid_subclass_desc_t * mouse_descs[] = {&mouse_desc};                          \
    APP_USBD_HID_MOUSE_GLOBAL_DEF_INTERNAL(instance_name,                                               \
                                           interface_number,                                            \
                                           endpoint,                                                    \
                                           bcnt,                                                        \
                                           user_ev_handler,                                             \
                                           subclass_boot)

/**
 * @brief Helper function to get class instance from HID mouse internals.
 *
 * @param[in] p_mouse Mouse instance (declared by @ref APP_USBD_HID_MOUSE_GLOBAL_DEF).
 *
 * @return Base class instance.
 */
static inline app_usbd_class_inst_t const *
app_usbd_hid_mouse_class_inst_get(app_usbd_hid_mouse_t const * p_mouse)
{
    return &p_mouse->base;
}

/**
 * @brief Helper function to get HID mouse from base class instance.
 *
 * @param[in] p_inst Base class instance.
 *
 * @return HID mouse class handle.
 */
static inline app_usbd_hid_mouse_t const *
app_usbd_hid_mouse_class_get(app_usbd_class_inst_t const * p_inst)
{
    return (app_usbd_hid_mouse_t const *)p_inst;
}

/**
 * @brief Move mouse X axis.
 *
 * @param[in] p_mouse Mouse instance (declared by @ref APP_USBD_HID_MOUSE_GLOBAL_DEF).
 * @param[in] offset  Relative mouse position: allowed full int8_t range.
 *
 * @return Standard error code.
 */
ret_code_t app_usbd_hid_mouse_x_move(app_usbd_hid_mouse_t const * p_mouse, int8_t offset);

/**
 * @brief Move mouse Y axis.
 *
 * @param[in] p_mouse Mouse instance (declared by @ref APP_USBD_HID_MOUSE_GLOBAL_DEF).
 * @param[in] offset  Relative mouse position: allowed full int8_t range.
 *
 * @return Standard error code.
 */
ret_code_t app_usbd_hid_mouse_y_move(app_usbd_hid_mouse_t const * p_mouse, int8_t offset);

/**
 * @brief Move mouse scroll.
 *
 * @param[in] p_mouse Mouse instance (declared by @ref APP_USBD_HID_MOUSE_GLOBAL_DEF).
 * @param[in] offset  Relative mouse position: allowed full int8_t range.
 *
 * @return Standard error code.
 */
ret_code_t app_usbd_hid_mouse_scroll_move(app_usbd_hid_mouse_t const * p_mouse, int8_t offset);

/**
 * @brief Set mouse button state.
 *
 * @param[in] p_mouse    Mouse instance (declared by @ref APP_USBD_HID_MOUSE_GLOBAL_DEF).
 * @param[in] button_id  Button number (0...7).
 * @param[in] state      Button state: true -> PRESSED, false -> RELEASED.
 *
 * @return Standard error code.
 */
ret_code_t app_usbd_hid_mouse_button_state(app_usbd_hid_mouse_t const * p_mouse,
                                           uint8_t button_id,
                                           bool state);

/**
 * @brief Function handling SET_PROTOCOL command.
 *
 *
 * @param[in] p_mouse       Mouse instance.
 * @param[in] ev            User event.
 *
 * @return Standard error code.
 */
ret_code_t hid_mouse_on_set_protocol(app_usbd_hid_mouse_t const * p_mouse,
                                     app_usbd_hid_user_event_t ev);

/**
 * @brief Function that clears HID mouse buffers and sends an empty report.
 *
 * @param[in] p_inst Base class instance.
 *
 * @return Standard error code.
 */
ret_code_t hid_mouse_clear_buffer(app_usbd_class_inst_t const * p_inst);

/** @} */

#endif /* APP_USBD_HID_MOUSE_H__ */
