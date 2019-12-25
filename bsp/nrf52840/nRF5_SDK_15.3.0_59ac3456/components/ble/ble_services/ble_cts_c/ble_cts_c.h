/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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
 * @defgroup ble_cts_c Current Time Service client
 * @{
 * @ingroup ble_sdk_srv
 * @brief Current Time Service client module.
 *
 * @details This module implements the Current Time Service (CTS) client-peripheral role of
 *          the Time Profile. After security is established, the module tries to discover the
 *          Current Time Service and Characteristic on the central side. If this succeeds,
 *          the application can trigger a read of the current time from the connected server.
 *
 *          The module informs the application about a successful discovery using the
 *          @ref BLE_CTS_C_EVT_DISCOVERY_COMPLETE event. The handles for the CTS server is now
 *          available in the @ref ble_cts_c_evt_t structure. These handles must be assigned to an
 *          instance of CTS_C, using @ref ble_cts_c_handles_assign. For more information about
 *          service discovery, see the ble_discovery module documentation @ref lib_ble_db_discovery.
 *
 *          The application can then use the function @ref ble_cts_c_current_time_read to read the
 *          current time. If the read succeeds, it will trigger either a
 *          @ref BLE_CTS_C_EVT_CURRENT_TIME event or a @ref BLE_CTS_C_EVT_INVALID_TIME event
 *          (depending on if the data that was read was actually a valid time), which is then sent
 *          to the application. The current time is then available in the params field of the
 *          passed @ref ble_cts_c_evt_t structure.
 *
 * @note    The application must register this module as BLE event observer using the
 *          NRF_SDH_BLE_OBSERVER macro. Example:
 *          @code
 *              ble_cts_c_t instance;
 *              NRF_SDH_BLE_OBSERVER(anything, BLE_CTS_C_BLE_OBSERVER_PRIO,
 *                                   ble_cts_c_on_ble_evt, &instance);
 *          @endcode
 */

#ifndef BLE_CTS_C_H__
#define BLE_CTS_C_H__

#include "ble_srv_common.h"
#include "ble_gattc.h"
#include "ble.h"
#include "ble_date_time.h"
#include "ble_db_discovery.h"
#include "nrf_sdh_ble.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_bps instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_CTS_C_DEF(_name)                                                                        \
static ble_cts_c_t _name;                                                                           \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_CTS_C_BLE_OBSERVER_PRIO,                                                   \
                     ble_cts_c_on_ble_evt, &_name)

/** @brief Macro for defining multiple ble_cts_c instances.
 *
 * @param   _name   Name of the array of instances.
 * @param   _cnt    Number of instances to define.
 * @hideinitializer
 */
#define BLE_CTS_C_ARRAY_DEF(_name, _cnt)                 \
static ble_cts_c_t _name[_cnt];                          \
NRF_SDH_BLE_OBSERVERS(_name ## _obs,                     \
                      BLE_CTS_C_BLE_OBSERVER_PRIO,       \
                      ble_cts_c_on_ble_evt, &_name, _cnt)


/**@brief "Day Date Time" field of the "Exact Time 256" field of the Current Time Characteristic. */
typedef struct
{
    ble_date_time_t date_time;
    uint8_t         day_of_week;
} day_date_time_t;

/**@brief "Exact Time 256" field of the Current Time Characteristic. */
typedef struct
{
    day_date_time_t day_date_time;
    uint8_t         fractions256;
} exact_time_256_t;

/**@brief "Adjust Reason" field of the Current Time Characteristic. */
typedef struct
{
    uint8_t manual_time_update              : 1;
    uint8_t external_reference_time_update  : 1;
    uint8_t change_of_time_zone             : 1;
    uint8_t change_of_daylight_savings_time : 1;
} adjust_reason_t;

/**@brief Data structure for the Current Time Characteristic. */
typedef struct
{
    exact_time_256_t exact_time_256;
    adjust_reason_t  adjust_reason;
} current_time_char_t;

// Forward declaration of the ble_cts_c_t type.
typedef struct ble_cts_c_s ble_cts_c_t;

/**@brief Current Time Service client event type. */
typedef enum
{
    BLE_CTS_C_EVT_DISCOVERY_COMPLETE, /**< The Current Time Service was found at the peer. */
    BLE_CTS_C_EVT_DISCOVERY_FAILED,   /**< The Current Time Service was not found at the peer. */
    BLE_CTS_C_EVT_DISCONN_COMPLETE,   /**< Event indicating that the Current Time Service client module has finished processing the BLE_GAP_EVT_DISCONNECTED event. This event is raised only if a valid instance of the Current Time Service was found at the server. The event can be used by the application to do clean up related to the Current Time Service client.*/
    BLE_CTS_C_EVT_CURRENT_TIME,       /**< A new current time reading has been received. */
    BLE_CTS_C_EVT_INVALID_TIME        /**< The current time value received from the peer is invalid.*/
} ble_cts_c_evt_type_t;

/**@brief Structure containing the handles related to the Heart Rate Service found on the peer. */
typedef struct
{
    uint16_t cts_handle;       /**< Handle of the Current Time characteristic as provided by the SoftDevice. */
    uint16_t cts_cccd_handle;  /**< Handle of the CCCD of the Current Time characteristic. */
} ble_cts_c_handles_t;

/**@brief Current Time Service client event. */
typedef struct
{
    ble_cts_c_evt_type_t evt_type; /**< Type of event. */
    uint16_t             conn_handle; /**< Connection handle on which the CTS service was discovered on the peer device. This will be filled if the evt_type is @ref BLE_CTS_C_EVT_DISCOVERY_COMPLETE.*/
    union
    {
        current_time_char_t current_time; /**< Current Time Characteristic data. This will be filled when the evt_type is @ref BLE_CTS_C_EVT_CURRENT_TIME. */
        ble_cts_c_handles_t char_handles;  /**< Current Time related handles found on the peer device. This will be filled when the evt_type is @ref BLE_HRS_C_EVT_DISCOVERY_COMPLETE.*/
    } params;
} ble_cts_c_evt_t;

/**@brief Current Time Service client event handler type. */
typedef void (* ble_cts_c_evt_handler_t) (ble_cts_c_t * p_cts, ble_cts_c_evt_t * p_evt);


/**@brief Current Time Service client structure. This structure contains status information for the client. */
struct ble_cts_c_s
{
    ble_cts_c_evt_handler_t evt_handler;         /**< Event handler to be called for handling events from the Current Time Service client. */
    ble_srv_error_handler_t error_handler;       /**< Function to be called if an error occurs. */
    ble_cts_c_handles_t     char_handles;        /**< Handles of Current Time Characteristic at the peer (handles are provided by the BLE stack through the DB Discovery module). */
    uint16_t                conn_handle;         /**< Handle of the current connection. BLE_CONN_HANDLE_INVALID if not in a connection. */
};

/**@brief Current Time Service client init structure. This structure contains all options and data needed for initialization of the client.*/
typedef struct
{
    ble_cts_c_evt_handler_t evt_handler;   /**< Event handler to be called for handling events from the Current Time Service client. */
    ble_srv_error_handler_t error_handler; /**< Function to be called if an error occurs. */
} ble_cts_c_init_t;


/**@brief Function for initializing the Current Time Service client.
 *
 * @details This function must be used by the application to initialize the Current Time Service client.
 *
 * @param[out] p_cts Current Time Service client structure. This structure must
 *                   be supplied by the application. It is initialized by this
 *                   function and can later be used to identify this particular client
 *                   instance.
 * @param[in]  p_cts_init Information needed to initialize the Current Time Service client.
 *
 * @retval NRF_SUCCESS If the service was initialized successfully.
 */
uint32_t ble_cts_c_init(ble_cts_c_t * p_cts, const ble_cts_c_init_t * p_cts_init);


/**@brief Function for handling events from the database discovery module.
 *
 * @details This function will handle an event from the database discovery module, and determine
 *          if it relates to the discovery of CTS at the peer. If so, it will
 *          call the application's event handler indicating that CTS has been
 *          discovered. It also populates the event with the service related
 *          information before providing it to the application.
 *
 * @param[in] p_cts  Pointer to the CTS client structure.
 * @param[in] p_evt  Pointer to the event received from the database discovery module.
 */
 void ble_cts_c_on_db_disc_evt(ble_cts_c_t * p_cts, ble_db_discovery_evt_t * p_evt);


/**@brief Function for handling the application's BLE stack events.
 *
 * @details This function handles all events from the BLE stack that are of interest to the
 *          Current Time Service client. This is a callback function that must be dispatched
 *          from main application context.
 *
 * @param[in] p_ble_evt     Event received from the BLE stack.
 * @param[in] p_context     Current Time Service client structure.
 */
void ble_cts_c_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for checking whether the peer's Current Time Service instance and the Current Time
 *        Characteristic have been discovered.
 *
 * @param[in] p_cts  Current Time Service client structure.
 */
static __INLINE bool ble_cts_c_is_cts_discovered(const ble_cts_c_t * p_cts)
{
    return (p_cts->char_handles.cts_handle != BLE_GATT_HANDLE_INVALID);
}


/**@brief Function for reading the peer's Current Time Service Current Time Characteristic.
 *
 * @param[in] p_cts  Current Time Service client structure.
 *
 * @retval NRF_SUCCESS If the operation is successful. Otherwise, an error code is returned.
 */
uint32_t ble_cts_c_current_time_read(ble_cts_c_t const * p_cts);


/**@brief Function for assigning handles to a this instance of cts_c.
 *
 * @details Call this function when a link has been established with a peer to
 *          associate the link to this instance of the module. This makes it
 *          possible to handle several links and associate each link to a particular
 *          instance of this module. The connection handle and attribute handles will be
 *          provided from the discovery event @ref BLE_CTS_C_EVT_DISCOVERY_COMPLETE.
 *
 * @param[in] p_cts          Pointer to the CTS client structure instance to associate.
 * @param[in] conn_handle    Connection handle to associated with the given CTS instance.
 * @param[in] p_peer_handles Attribute handles for the CTS server you want this CTS client to
 *                           interact with.
 *
 * @retval NRF_SUCCESS    If the operation was successful.
 * @retval NRF_ERROR_NULL If a p_cts was a NULL pointer.
 */
uint32_t ble_cts_c_handles_assign(ble_cts_c_t               * p_cts,
                                  const uint16_t              conn_handle,
                                  const ble_cts_c_handles_t * p_peer_handles);


#ifdef __cplusplus
}
#endif

#endif // BLE_CTS_C_H__

/** @} */
