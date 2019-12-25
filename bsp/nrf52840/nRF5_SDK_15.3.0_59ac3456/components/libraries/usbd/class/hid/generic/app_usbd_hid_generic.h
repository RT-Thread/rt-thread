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
#ifndef APP_USBD_HID_GENERIC_H__
#define APP_USBD_HID_GENERIC_H__



#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "nrf_drv_usbd.h"
#include "app_usbd_class_base.h"
#include "app_usbd_hid_types.h"
#include "app_usbd_hid.h"
#include "app_usbd.h"
#include "app_usbd_core.h"
#include "app_usbd_descriptor.h"
#include "app_usbd_hid_generic_desc.h"
#include "app_usbd_hid_generic_internal.h"

/**
 * @defgroup app_usbd_hid_generic USB HID generic
 * @ingroup app_usbd_hid
 *
 * @brief @tagAPI52840 Module with types, definitions, and API used by the HID generic class.
 * @{
 */


#ifdef DOXYGEN
/**
 * @brief HID generic class instance type.
 *
 * @ref APP_USBD_CLASS_TYPEDEF
 */
typedef struct { } app_usbd_hid_generic_t;
#else
/*lint -save -e10 -e26 -e123 -e505 */
APP_USBD_CLASS_TYPEDEF(app_usbd_hid_generic,                                           \
            APP_USBD_HID_GENERIC_CONFIG(0, (NRF_DRV_USBD_EPIN1, NRF_DRV_USBD_EPOUT1)), \
            APP_USBD_HID_GENERIC_INSTANCE_SPECIFIC_DEC,                                \
            APP_USBD_HID_GENERIC_DATA_SPECIFIC_DEC                                     \
);
/*lint -restore*/
#endif

/**
 * @brief Global definition of app_usbd_hid_generic_t class.
 *
 * @param instance_name             Name of global instance.
 * @param interface_number          Unique interface index.
 * @param user_ev_handler           User event handler (optional).
 * @param endpoint_list             Input endpoint list (@ref nrf_drv_usbd_ep_t).
 * @param subclass_descriptors      HID subclass descriptors.
 * @param report_in_queue_size      IN report queue size.
 * @param report_out_maxsize        Maximum output report size.
 * @param subclass_boot             Subclass boot (@ref app_usbd_hid_subclass_t).
 * @param protocol                  HID protocol (@ref app_usbd_hid_protocol_t).
 *
 * @note This macro is just simplified version of @ref APP_USBD_HID_GENERIC_GLOBAL_DEF_INTERNAL.
 *
 * Example class definition:
 * @code

       APP_USBD_HID_GENERIC_SUBCLASS_REPORT_DESC(mouse_desc,APP_USBD_HID_MOUSE_REPORT_DSC_BUTTON(2));

       static const app_usbd_hid_subclass_desc_t * reps[] = {&mouse_desc};

       #define ENDPOINT_LIST                                        \
       (                                                            \
               NRF_DRV_USBD_EPIN1                                   \
       )

       #define REPORT_COUNT        1
       #define REPORT_OUT_MAXSIZE  0

       APP_USBD_HID_GENERIC_GLOBAL_DEF(m_app_hid_generic,
                                       0,
                                       hid_user_ev_handler,
                                       ENDPOINT_LIST(),
                                       reps,
                                       REPORT_IN_QUEUE_SIZE,
                                       REPORT_OUT_MAXSIZE,
                                       APP_USBD_HID_SUBCLASS_BOOT,
                                       APP_USBD_HID_PROTO_MOUSE);
  @endcode
 *
 */
/*lint -emacro( (40), APP_USBD_HID_GENERIC_GLOBAL_DEF) */
#define APP_USBD_HID_GENERIC_GLOBAL_DEF(instance_name,              \
                                        interface_number,           \
                                        user_ev_handler,            \
                                        endpoint_list,              \
                                        subclass_descriptors,       \
                                        report_in_queue_size,       \
                                        report_out_maxsize,         \
                                        subclass_boot,              \
                                        protocol)                   \
    APP_USBD_HID_GENERIC_GLOBAL_DEF_INTERNAL(instance_name,         \
                                             interface_number,      \
                                             user_ev_handler,       \
                                             endpoint_list,         \
                                             subclass_descriptors,  \
                                             report_in_queue_size,  \
                                             report_out_maxsize,    \
                                             subclass_boot,         \
                                             protocol)

/**
 * @brief Helper function to get class instance from HID generic class.
 *
 * @param[in] p_generic HID generic class instance.
 *
 * @return Base class instance.
 */
static inline app_usbd_class_inst_t const *
app_usbd_hid_generic_class_inst_get(app_usbd_hid_generic_t const * p_generic)
{
    return &p_generic->base;
}

/**
 * @brief Helper function to get HID generic from base class instance.
 *
 * @param[in] p_inst Base class instance.
 *
 * @return HID generic class handle.
 */
static inline app_usbd_hid_generic_t const *
app_usbd_hid_generic_class_get(app_usbd_class_inst_t const * p_inst)
{
    return (app_usbd_hid_generic_t const *)p_inst;
}

/**
 * @brief Changes default HID idle report.
 *
 *
 * @param[in] p_generic HID generic class instance.
 * @param[in] p_buff    Report buffer.
 * @param[in] size      Report size.
 *
 * @return Standard error code.
 */
ret_code_t hid_generic_idle_set(app_usbd_hid_generic_t const * p_generic,
                                const void * p_buff,
                                size_t size);

/**
 * @brief New IN report trigger.
 *
 *
 * @param[in] p_generic HID generic class instance.
 * @param[in] p_buff    Report buffer.
 * @param[in] size      Report size.
 *
 * @return Standard error code.
 */
ret_code_t app_usbd_hid_generic_in_report_set(app_usbd_hid_generic_t const * p_generic,
                                              const void * p_buff,
                                              size_t size);

/**
 * @brief Returns last successful transfered IN report.
 *
 * @note Use this call only on @ref APP_USBD_HID_USER_EVT_IN_REPORT_DONE event.
 *
 * @param[in] p_generic HID generic class instance.
 * @param[out] p_size   Last transfered IN report size.
 *
 * @return Last transfered report ID.
 */
const void * app_usbd_hid_generic_in_report_get(app_usbd_hid_generic_t const * p_generic,
                                                size_t * p_size);

/**
 * @brief Returns last successful transfered OUT report.
 *
 * @warning Use this call only on @ref APP_USBD_HID_USER_EVT_OUT_REPORT_READY event.
 *
 * @param[in] p_generic HID generic class instance.
 * @param[out] p_size   Last transfered OUT report size.
 *
 * @return Last transfered OUT report.
 */
const void * app_usbd_hid_generic_out_report_get(app_usbd_hid_generic_t const * p_generic,
                                                 size_t * p_size);

/**
 * @brief Function handling SET_PROTOCOL command.
 *
 *
 * @param[in] p_generic     HID generic class instance.
 * @param[in] ev            User event.
 *
 * @return Standard error code.
 */
ret_code_t hid_generic_on_set_protocol(app_usbd_hid_generic_t const * p_generic,
                                       app_usbd_hid_user_event_t ev);

/**
 * @brief Function that clears HID generic buffers and sends an empty report.
 *
 * @param[in] p_inst Base class instance.
 *
 * @return Standard error code.
 */
ret_code_t hid_generic_clear_buffer(app_usbd_class_inst_t const * p_inst);

/**
 * @brief Sets handler for idle reports.
 *
 * @param[in] p_inst    Base class instance.
 * @param[in] handler   Handler.
 *
 * @return Standard error code.
 */
ret_code_t hid_generic_idle_handler_set(app_usbd_class_inst_t const * p_inst,
                                        app_usbd_hid_idle_handler_t handler);

/**
 * @brief Sends idle reoprt.
 *
 * @param[in] p_generic     HID generic class instance.
 * @param[in] p_buff        Report buffer.
 * @param[in] size          Size of report.
 *
 * @return Standard error code.
 */
ret_code_t app_usbd_hid_generic_idle_report_set(app_usbd_hid_generic_t const * p_generic,
                                                const void                   * p_buff,
                                                size_t                         size);
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_HID_GENERIC_H__ */
