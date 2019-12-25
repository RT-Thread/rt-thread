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
#ifndef APP_USBD_AUDIO_H__
#define APP_USBD_AUDIO_H__

#include <stdint.h>
#include <stdbool.h>

#include "nrf_drv_usbd.h"
#include "app_usbd.h"
#include "app_usbd_core.h"
#include "app_usbd_class_base.h"
#include "app_usbd_descriptor.h"

#include "app_usbd_audio_types.h"
#include "app_usbd_audio_desc.h"
#include "app_usbd_audio_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_audio USB AUDIO class
 * @ingroup app_usbd
 *
 * @brief @tagAPI52840 Module with types, definitions, and API used by USB Audio class.
 *
 * @details Reference specifications:
 * - "Universal Serial Bus Device Class Definition for Audio Devices"
 *      Release 1.0,  March 18, 1998.
 * - "Universal Serial Bus Device Class Definition for Audio Data Formats"
 *      Release 1.0, March 18, 1998.
 * - "Universal Serial Bus Device Class Definition for Terminal Types"
 *      Release 1.0, March 18, 1998.
 *
 * @{
 */


#ifdef DOXYGEN
/**
 * @brief Audio class instance type
 *
 * @ref APP_USBD_CLASS_TYPEDEF
 */
typedef struct { } app_usbd_audio_t;
#else
/*lint -save -e10 -e26 -e123 -e505 */
APP_USBD_CLASS_TYPEDEF(app_usbd_audio,    \
    APP_USBD_AUDIO_CONFIG(0, 1),          \
    APP_USBD_AUDIO_INSTANCE_SPECIFIC_DEC, \
    APP_USBD_AUDIO_DATA_SPECIFIC_DEC      \
);
/*lint -restore*/
#endif


/*lint -save -e407 */

/**
 * @brief Events passed to user event handler
 *
 * @note Example prototype of user event handler:
 *
 * @code
   void audio_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                              app_usbd_audio_user_event_t   event);
 * @endcode
 */
typedef enum app_usbd_audio_user_event_e {
    APP_USBD_AUDIO_USER_EVT_CLASS_REQ,   /**< User event CLASS_REQ */
    APP_USBD_AUDIO_USER_EVT_RX_DONE,     /**< User event RX_DONE   */
    APP_USBD_AUDIO_USER_EVT_TX_DONE,     /**< User event TX_DONE   */
} app_usbd_audio_user_event_t;

/*lint -restore*/

/**
 * @brief Global definition of app_usbd_audio_t class instance.
 *
 * @param instance_name             Name of global instance.
 * @param interfaces_configs        Interfaces configurations.
 * @param user_ev_handler           User event handler.
 * @param format_descriptor         Audio class Format descriptor.
 * @param input_descriptor          Audio class Input Terminal descriptor.
 * @param output_descriptor         Audio class Output Terminal descriptor.
 * @param feature_descriptor        Audio class Feature Unit descriptor.
 * @param delay                     Streaming delay.
 * @param format                    FormatTag (@ref app_usbd_audio_as_iface_format_tag_t).
 * @param ep_size                   Endpoint size.
 * @param type_str                  Streaming type MIDISTREAMING/AUDIOSTREAMING.
 *
 * @note This macro is just simplified version of @ref APP_USBD_AUDIO_GLOBAL_DEF_INTERNAL
 *
 */
#define APP_USBD_AUDIO_GLOBAL_DEF(instance_name,            \
                                  interfaces_configs,       \
                                  user_ev_handler,          \
                                  format_descriptor,        \
                                  input_descriptor,         \
                                  output_descriptor,        \
                                  feature_descriptor,       \
                                  delay,                    \
                                  format,                   \
                                  ep_size,                  \
                                  type_str)                 \
    APP_USBD_AUDIO_GLOBAL_DEF_INTERNAL(instance_name,       \
                                       interfaces_configs,  \
                                       user_ev_handler,     \
                                       format_descriptor,   \
                                       input_descriptor,    \
                                       output_descriptor,   \
                                       feature_descriptor,  \
                                       delay,               \
                                       format,              \
                                       ep_size,             \
                                       type_str)


/**
 * @brief Initializer of Audio Format descriptor.
 *
 * @param name  Format descriptor name.
 * @param ...   Format descriptor data.
*/

#define APP_USBD_AUDIO_FORMAT_DESCRIPTOR(name, ...)             \
    static uint8_t const CONCAT_2(name,  _data)[] =             \
    {                                                           \
        __VA_ARGS__                                             \
    };                                                          \
    static const app_usbd_audio_subclass_desc_t name =          \
    {                                                           \
        sizeof(CONCAT_2(name, _data)),                          \
        APP_USBD_AUDIO_AS_IFACE_SUBTYPE_FORMAT_TYPE,            \
        CONCAT_2(name,_data)                                    \
    }

/**
 * @brief Initializer of Audio Input descriptor.
 *
 * @param name  Input descriptor name.
 * @param ...   Input descriptor data.
*/

#define APP_USBD_AUDIO_INPUT_DESCRIPTOR(name, ...)              \
    static uint8_t const CONCAT_2(name,  _data)[] =             \
    {                                                           \
        __VA_ARGS__                                             \
    };                                                          \
    static const app_usbd_audio_subclass_desc_t name =          \
    {                                                           \
        sizeof(CONCAT_2(name, _data)),                          \
        APP_USBD_AUDIO_AC_IFACE_SUBTYPE_INPUT_TERMINAL,         \
        CONCAT_2(name,_data)                                    \
    }

/**
 * @brief Initializer of Audio Output descriptor.
 *
 * @param name  Output descriptor name.
 * @param ...   Output descriptor data.
*/

#define APP_USBD_AUDIO_OUTPUT_DESCRIPTOR(name, ...)             \
    static uint8_t const CONCAT_2(name,  _data)[] =             \
    {                                                           \
        __VA_ARGS__                                             \
    };                                                          \
    static const app_usbd_audio_subclass_desc_t name =          \
    {                                                           \
        sizeof(CONCAT_2(name, _data)),                          \
        APP_USBD_AUDIO_AC_IFACE_SUBTYPE_OUTPUT_TERNINAL,        \
        CONCAT_2(name,_data)                                    \
    }

/**
 * @brief Initializer of Feture Output descriptor.
 *
 * @param name  Feture descriptor name.
 * @param ...   Feture descriptor data.
*/

#define APP_USBD_AUDIO_FEATURE_DESCRIPTOR(name, ...)            \
    static uint8_t const CONCAT_2(name,  _data)[] =             \
    {                                                           \
        __VA_ARGS__                                             \
    };                                                          \
    static const app_usbd_audio_subclass_desc_t name =          \
    {                                                           \
        sizeof(CONCAT_2(name, _data)),                          \
        APP_USBD_AUDIO_AC_IFACE_SUBTYPE_FEATURE_UNIT,           \
        CONCAT_2(name,_data)                                    \
    }

/**
 * @@brief Helper function to get class instance from Audio class.
 *
 * @param[in] p_audio Audio class instance (declared by @ref APP_USBD_AUDIO_GLOBAL_DEF).
 * @return Base class instance.
 */
static inline app_usbd_class_inst_t const *
app_usbd_audio_class_inst_get(app_usbd_audio_t const * p_audio)
{
    return &p_audio->base;
}

/**
 * @brief Helper function to get audio specific request from audio class.
 *
 * @param[in] p_audio Audio class instance (declared by @ref APP_USBD_AUDIO_GLOBAL_DEF).
 * @return Audio class specific request.
 */
static inline app_usbd_audio_req_t *
app_usbd_audio_class_request_get(app_usbd_audio_t const * p_audio)
{
    return &p_audio->specific.p_data->ctx.request;
}

/**
 * @brief Helper function to get audio from base class instance.
 *
 * @param[in] p_inst Base class instance.
 * @return Audio class handle.
 */
static inline app_usbd_audio_t const *
app_usbd_audio_class_get(app_usbd_class_inst_t const * p_inst)
{
    return (app_usbd_audio_t const *)p_inst;
}

/**
 * @brief Get the size of last received transfer.
 *
 * @note Call this function in reaction to a SOF event to check if there is any data to process.
 *
 * @param p_inst Base class instance.
 *
 * @return Number of bytes received in the last transmission.
 */
size_t app_usbd_audio_class_rx_size_get(app_usbd_class_inst_t const * p_inst);

/**
 * @brief Start audio data copying from the endpoint buffer.
 *
 * Function to be used to copy data from an audio OUT endpoint to a given buffer.
 * When it finishes, an @ref APP_USBD_AUDIO_USER_EVT_RX_DONE event is generated.
 *
 * @param p_inst Base class instance.
 * @param p_buff Target buffer.
 * @param size   Size of the requested data.
 *
 * @return Result of the endpoint transmission start.
 *
 * @sa app_usbd_audio_class_rx_size_get
 *
 * @note This function should be called in reaction to a SOF event.
 *       Isochronous endpoints are double buffered and they are automatically switched at every SOF.
 */
ret_code_t app_usbd_audio_class_rx_start(
    app_usbd_class_inst_t const * p_inst,
    void * p_buff,
    size_t size);

/**
 * @brief Start copying audio data to the endpoint buffer.
 *
 * Function to be used to copy data to an audio IN endpoint from a given buffer.
 * When it finishes, an @ref APP_USBD_AUDIO_USER_EVT_TX_DONE event is generated.
 *
 * @param p_inst Base class instance.
 * @param p_buff Source buffer.
 * @param size   Size of the data to be sent.
 *
 * @return Result of the endpoint transsmision start.
 *
 * @note This function should be called in reaction to a SOF event.
 *       Isochronous endpoints are double buffered and they are automatically switched at every SOF.
 */
ret_code_t app_usbd_audio_class_tx_start(
    app_usbd_class_inst_t const * p_inst,
    const void * p_buff,
    size_t size);

/**
 * @brief Register audio instance as the one that requires SOF events in interrupt.
 *
 * This function should be called before appending the instance.
 *
 * @param p_inst  Audio instance that requires SOF event.
 * @param handler Handler to SOF event
 *
 * @retval NRF_SUCCESS Instance linked into SOF processing list.
 *
 * @sa app_usbd_class_sof_interrupt_register
 */
ret_code_t app_usbd_audio_sof_interrupt_register(app_usbd_class_inst_t const * p_inst,
                                                 app_usbd_sof_interrupt_handler_t handler);
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_AUDIO_H__ */
