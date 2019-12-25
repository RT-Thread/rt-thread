/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup ble_lls Link Loss Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Link Loss Service module.
 *
 * @details This module implements the Link Loss Service with the Alert Level characteristic.
 *          During initialization it adds the Link Loss Service and Alert Level characteristic
 *          to the BLE stack database.
 *
 *          The application must supply an event handler for receiving Link Loss Service
 *          events. Using this handler, the service will notify the application when the
 *          link has been lost, and which Alert Level has been set.
 *
 *          The service also provides a function for letting the application poll the current
 *          value of the Alert Level characteristic.
 *
 * @note    The application must register this module as BLE event observer using the
 *          NRF_SDH_BLE_OBSERVER macro. Example:
 *          @code
 *              ble_lls_t instance;
 *              NRF_SDH_BLE_OBSERVER(anything, BLE_LLS_BLE_OBSERVER_PRIO,
 *                                   ble_lls_on_ble_evt, &instance);
 *          @endcode
 *
 * @note Attention!
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile
 *  qualification listings, this section of source code must not be modified.
*/

#ifndef BLE_LLS_H__
#define BLE_LLS_H__

#include <stdint.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_lls instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_LLS_DEF(_name)                                                                          \
static ble_lls_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_LLS_BLE_OBSERVER_PRIO,                                                     \
                     ble_lls_on_ble_evt, &_name)


/**@brief Link Loss Service event type. */
typedef enum
{
    BLE_LLS_EVT_LINK_LOSS_ALERT                         /**< Alert Level Updated event. */
} ble_lls_evt_type_t;

/**@brief Link Loss Service event. */
typedef struct
{
    ble_lls_evt_type_t evt_type;                        /**< Type of event. */
    union
    {
        uint8_t alert_level;                            /**< New Alert Level value. */
    } params;
} ble_lls_evt_t;

// Forward declaration of the ble_lls_t type.
typedef struct ble_lls_s ble_lls_t;

/**@brief Link Loss Service event handler type. */
typedef void (*ble_lls_evt_handler_t) (ble_lls_t * p_lls, ble_lls_evt_t * p_evt);

/**@brief Link Loss Service init structure. This contains all options and data needed for initialization of the service. */
typedef struct
{
    ble_lls_evt_handler_t     evt_handler;              /**< Event handler to be called for handling events in the Link Loss Service. */
    ble_srv_error_handler_t   error_handler;            /**< Function to be called in case of an error. */
    uint8_t                   initial_alert_level;      /**< Initial value of the Alert Level characteristic. */
    security_req_t            alert_level_rd_sec;       /**< Security requirement for reading Alert Level characteristic. */
    security_req_t            alert_level_wr_sec;       /**< Security requirement for writing Alert Level characteristic. */
} ble_lls_init_t;

/**@brief Link Loss Service structure. This contains various status information for the service. */
struct ble_lls_s
{
    ble_lls_evt_handler_t     evt_handler;              /**< Event handler to be called for handling events in the Link Loss Service. */
    ble_srv_error_handler_t   error_handler;            /**< Function to be called in case of an error. */
    uint16_t                  service_handle;           /**< Handle of Link Loss Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t  alert_level_handles;      /**< Handles related to the Alert Level characteristic. */
    uint16_t                  conn_handle;              /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
};


/**@brief Function for initializing the Link Loss Service.
 *
 * @param[out]  p_lls       Link Loss Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_lls_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_lls_init(ble_lls_t * p_lls, const ble_lls_init_t * p_lls_init);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Link Loss Service.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   Link Loss Service structure.
 */
void ble_lls_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for getting current value of the Alert Level characteristic.
 *
 * @param[in]   p_lls          Link Loss Service structure.
 * @param[out]  p_alert_level  Current Alert Level value.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_lls_alert_level_get(ble_lls_t * p_lls, uint8_t * p_alert_level);


#ifdef __cplusplus
}
#endif

#endif // BLE_LLS_H__

/** @} */
