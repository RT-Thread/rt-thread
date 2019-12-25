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
#ifndef APP_USBD_NRF_DFU_TRIGGER_H__
#define APP_USBD_NRF_DFU_TRIGGER_H__

#include <stdint.h>
#include <stdbool.h>

#include "nrf_drv_usbd.h"
#include "nrf_block_dev.h"
#include "app_usbd_class_base.h"
#include "app_usbd.h"
#include "app_usbd_core.h"
#include "app_usbd_descriptor.h"

#include "app_usbd_nrf_dfu_trigger_types.h"
#include "app_usbd_nrf_dfu_trigger_internal.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_nrf_dfu_trigger USB Nordic DFU Trigger class
 * @ingroup app_usbd
 *
 * @brief @tagAPI52840 Module with types, definitions,
 *                     and API used by the USB Nordic DFU Trigger class.
 *
 * @{
 */

#ifdef DOXYGEN
/**
 * @brief Nordic DFU Trigger class instance type.
 *
 * @ref APP_USBD_CLASS_TYPEDEF
 */
typedef struct { } app_usbd_nrf_dfu_trigger_t;
#else
/*lint -save -e10 -e26 -e123 -e505 */
APP_USBD_CLASS_NO_EP_TYPEDEF(app_usbd_nrf_dfu_trigger,                                             \
                             APP_USBD_NRF_DFU_TRIGGER_CONFIG(0),                                   \
                             APP_USBD_NRF_DFU_TRIGGER_INSTANCE_SPECIFIC_DEC,                       \
                             APP_USBD_NRF_DFU_TRIGGER_DATA_SPECIFIC_DEC                            \
);
#endif

/*lint -restore*/


/*lint -save -e407 */

/**
 * @brief Events passed to user event handler.
 *
 * @note Example prototype of user event handler:
 *
 * void dfu_user_ev_handler(app_usbd_class_inst_t const *         p_inst,
 *                          app_usbd_nrf_dfu_trigger_user_event_t event);
 */
typedef enum app_usbd_nrf_dfu_trigger_user_event_e {
    APP_USBD_NRF_DFU_TRIGGER_USER_EVT_DETACH,
} app_usbd_nrf_dfu_trigger_user_event_t;

/*lint -restore*/

/**
 * @brief Global definition of app_usbd_nrf_dfu_trigger_t class.
 *
 * @param instance_name         Name of global instance.
 * @param interface_number      Unique interface number.
 * @param p_nordic_dfu          Pointer to @ref app_usbd_nrf_dfu_trigger_nordic_info_t structure.
 * @param sem_ver_str           Semantic version string.
 * @param user_ev_handler       User event handler (optional).
 *
 * @note This macro is just simplified version of @ref APP_USBD_NRF_DFU_TRIGGER_GLOBAL_DEF_INTERNAL
 *
 */
/*lint -save -emacro(26 64 123 505 651, APP_USBD_NRF_DFU_TRIGGER_GLOBAL_DEF)*/
#define APP_USBD_NRF_DFU_TRIGGER_GLOBAL_DEF(instance_name,                                         \
                                            interface_number,                                      \
                                            p_nordic_dfu,                                          \
                                            sem_ver_str,                                           \
                                            user_ev_handler)                                       \
        APP_USBD_NRF_DFU_TRIGGER_GLOBAL_DEF_INTERNAL(instance_name,                                \
                                                     interface_number,                             \
                                                     0,                                            \
                                                     0,                                            \
                                                     p_nordic_dfu,                                 \
                                                     sem_ver_str,                                  \
                                                     user_ev_handler)
/*lint -restore*/

/**
 * @brief Helper function to get class instance from Nordic DFU Trigger.
 *
 * @param[in] p_dfu Nordic DFU Trigger instance
 *                  (declared by @ref APP_USBD_NRF_DFU_TRIGGER_GLOBAL_DEF)
 *
 * @return Base class instance
 */
static inline app_usbd_class_inst_t const *
app_usbd_nrf_dfu_trigger_class_inst_get(app_usbd_nrf_dfu_trigger_t const * p_dfu)
{
    return &p_dfu->base;
}

/**
 * @brief Helper function to get DFU from base class instance.
 *
 * @param[in] p_inst Base class instance.
 *
 * @return DFU class handle.
 */
static inline app_usbd_nrf_dfu_trigger_t const *
app_usbd_nrf_dfu_trigger_class_get( app_usbd_class_inst_t const * p_inst)
{
    return (app_usbd_nrf_dfu_trigger_t const *)p_inst;
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_NRF_DFU_TRIGGER_H__ */
