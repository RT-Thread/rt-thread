/**
 * Copyright (c) 2012 - 2017, Nordic Semiconductor ASA
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
 * @defgroup ble_ias_c Immediate Alert Service Client
 * @{
 * @ingroup ble_sdk_srv
 * @brief Immediate Alert Service Client module
 *
 * @details This module implements the Immediate Alert Service client - locator role of the Find Me
 *          profile. On @ref BLE_GAP_EVT_CONNECTED event, this module starts discovery of the
 *          Immediate Alert Service with Alert Level characteristic at the peer. This module will
 *          indicate the application about a successful service & characteristic discovery using
 *          @ref BLE_IAS_C_EVT_DISCOVERY_COMPLETE event. The application can use @ref
 *          ble_ias_c_send_alert_level function to signal alerts to the peer.
 *
 * @note The application must propagate BLE stack events to this module by calling
 *       ble_ias_c_on_ble_evt() from the @ref softdevice_handler callback function.
 */

#ifndef BLE_IAS_C_H__
#define BLE_IAS_C_H__

#include <stdint.h>
#include "ble_srv_common.h"
#include "ble_gattc.h"
#include "ble.h"
#include "ble_db_discovery.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declaration of the ble_ias_c_t type.
typedef struct ble_ias_c_s ble_ias_c_t;

/**@brief Immediate Alert Service client event type. */
typedef enum
{
    BLE_IAS_C_EVT_DISCOVERY_COMPLETE,             /**< Event indicating that the Immediate Alert Service is found at the peer. */
    BLE_IAS_C_EVT_DISCOVERY_FAILED,               /**< Event indicating that the Immediate Alert Service is not found at the peer. */
    BLE_IAS_C_EVT_DISCONN_COMPLETE                /**< Event indicating that the Immediate Alert Service client module has completed the processing of BLE_GAP_EVT_DISCONNECTED event. This event is raised only if a valid instance of IAS was found at the peer during the discovery phase. This event can be used the application to do clean up related to the IAS Client.*/
} ble_ias_c_evt_type_t;

/**@brief Immediate Alert Service client event. */
typedef struct
{
    ble_ias_c_evt_type_t evt_type;                /**< Type of event. */
    uint16_t             conn_handle;             /**< Connection handle on which the IAS service was discovered on the peer device. This will be filled if the evt_type is @ref BLE_IAS_C_EVT_DISCOVERY_COMPLETE.*/
    ble_gattc_char_t     alert_level;             /**< Info on the discovered Alert Level characteristic discovered. This will be filled if the evt_type is @ref BLE_IAS_C_EVT_DISCOVERY_COMPLETE.*/
} ble_ias_c_evt_t;

/**@brief Immediate Alert Service client event handler type. */
typedef void (*ble_ias_c_evt_handler_t) (ble_ias_c_t * p_ias_c, ble_ias_c_evt_t * p_evt);

/**@brief IAS Client structure. This contains various status information for the client. */
struct ble_ias_c_s
{
    ble_ias_c_evt_handler_t   evt_handler;        /**< Event handler to be called for handling events in the Immediate Alert Service client. */
    ble_srv_error_handler_t   error_handler;      /**< Function to be called in case of an error. */
    uint16_t                  conn_handle;        /**< Handle of the current connection. Set with @ref ble_ias_c_handles_assign when connected. */
    ble_uuid_t                service_uuid;       /**< The GATT Service holding the discovered Immediate Service. */
    ble_gattc_char_t          alert_level_char;   /**< IAS Alert Level Characteristic. Stores data about the alert characteristic found on the peer. */
};

/**@brief IAS Client init structure. This contains all options and data needed for initialization of
 *        the client.*/
typedef struct
{
    ble_ias_c_evt_handler_t   evt_handler;        /**< Event handler to be called for handling events from the Immediate Alert Service client. */
    ble_srv_error_handler_t   error_handler;      /**< Function to be called in case of an error. */
} ble_ias_c_init_t;

/**@brief Function for initializing the Immediate Alert Service client.
 *
 * @details This call allows the application to initialize the Immediate Alert Service client.
 *
 * @param[out]  p_ias_c      Immediate Alert Service client structure. This structure will have to
 *                           be supplied by the application. It will be initialized by this
 *                           function, and will later be used to identify this particular client
 *                           instance.
 * @param[in]   p_ias_c_init Information needed to initialize the Immediate Alert Service client.
 *
 * @return      NRF_SUCCESS on successful initialization of service.
 */
uint32_t ble_ias_c_init(ble_ias_c_t * p_ias_c, const ble_ias_c_init_t * p_ias_c_init);

/**@brief Function for sending alert level to the peer.
 *
 * @details This function allows the application to send an alert to the peer.
 *
 * @param[in]   p_ias_c      Immediate Alert Service client structure.
 * @param[in]   alert_level  Required alert level to be sent to the peer.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_ias_c_send_alert_level(const ble_ias_c_t * p_ias_c, uint8_t alert_level);

/**@brief Function for handling the Application's BLE Stack events for Immediate Alert Service client.
 *
 * @details Handles all events from the BLE stack of interest to the Immediate Alert Service client.
 *
 * @param[in]   p_ias_c      Immediate Alert Service client structure.
 * @param[in]   p_ble_evt    Event received from the BLE stack.
 */
void ble_ias_c_on_ble_evt(ble_ias_c_t * p_ias_c, const ble_evt_t * p_ble_evt);

/**@brief Function for checking whether the peer's Immediate Alert Service instance and the alert level
 *        characteristic have been discovered.
 *
 * @param[in]  p_ias_c      Immediate Alert Service client structure.
 *
 * @return TRUE if a handle has been assigned to alert_level_handle, meaning it must have been
 *         discovered. FALSE if the handle is invalid.
 */
static __INLINE bool ble_ias_c_is_discovered(const ble_ias_c_t * p_ias_c)
{
    return (p_ias_c->alert_level_char.handle_value != BLE_GATT_HANDLE_INVALID);
}


/**@brief     Function for handling events from the database discovery module.
 *
 * @details   Call this function when getting a callback event from the DB discovery modue.
 *            This function will handle an event from the database discovery module, and determine
 *            if it relates to the discovery of heart rate service at the peer. If so, it will
 *            call the application's event handler indicating that the heart rate service has been
 *            discovered at the peer. It also populates the event with the service related
 *            information before providing it to the application.
 *
 * @param[in] p_ias_c Pointer to the immediate alert client structure instance that will handle
 *                    the discovery.
 * @param[in] p_evt   Pointer to the event received from the database discovery module.
 *
 */
void ble_ias_c_on_db_disc_evt(ble_ias_c_t * p_ias_c, const ble_db_discovery_evt_t * p_evt);


/**@brief Function for assigning handles to an instance of ias_c.
 *
 * @details Call this function when a link has been established with a peer to
 *          associate this link to this instance of the module. This makes it
 *          possible to handle several links and associate each link to a particular
 *          instance of this module. The connection handle and attribute handles will be
 *          provided from the discovery event @ref BLE_IAS_C_EVT_DISCOVERY_COMPLETE.
 *
 * @param[in] p_ias_c            Pointer to the IAS client structure instance to associate.
 * @param[in] conn_handle        Connection handle to associated with the given IAS Instance.
 * @param[in] alert_level_handle Attribute handle on the IAS server that you want this IAS_C client to
 *                               interact with.
 *
 * @retval NRF_SUCCESS    If the operation was successful.
 * @retval NRF_ERROR_NULL If a p_ias_c was a NULL pointer.
 */
uint32_t ble_ias_c_handles_assign(ble_ias_c_t * p_ias_c,
                                  uint16_t      conn_handle,
                                  uint16_t      alert_level_handle);



#ifdef __cplusplus
}
#endif

#endif // BLE_IAS_C_H__

/** @} */
