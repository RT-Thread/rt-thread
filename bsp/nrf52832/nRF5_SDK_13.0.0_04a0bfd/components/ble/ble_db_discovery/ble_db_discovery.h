/**
 * Copyright (c) 2013 - 2017, Nordic Semiconductor ASA
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
/**@file
 *
 * @defgroup ble_db_discovery Database Discovery
 * @{
 * @ingroup  ble_sdk_lib
 * @brief    Database discovery module.
 *
 * @details  This module contains the APIs and types exposed by the DB Discovery module. These APIs
 *           and types can be used by the application to perform discovery of a service and its
 *           characteristics at the peer server. This module can also be used to discover the
 *           desired services in multiple remote devices.
 *
 * @warning  The maximum number of characteristics per service that can be discovered by this module
 *           is determined by the number of characteristics in the service structure defined in
 *           db_disc_config.h. If the peer has more than the supported number of characteristics, then
 *           the first found will be discovered and any further characteristics will be ignored. Only the
 *           following descriptors will be searched for at the peer: Client Characteristic Configuration,
 *           Characteristic Extended Properties, Characteristic User Description, and Report Reference.
 *
 * @note     Presently only one instance of a Primary Service can be discovered by this module. If
 *           there are multiple instances of the service at the peer, only the first instance
 *           of it at the peer is fetched and returned to the application.
 *
 * @note     The application must propagate BLE stack events to this module by calling
 *           ble_db_discovery_on_ble_evt().
 *
 */

#ifndef BLE_DB_DISCOVERY_H__
#define BLE_DB_DISCOVERY_H__

#include <stdint.h>
#include "nrf_error.h"
#include "ble.h"
#include "ble_gattc.h"
#include "ble_srv_common.h"
#include "ble_gatt_db.h"

#ifdef __cplusplus
extern "C" {
#endif


#define BLE_DB_DISCOVERY_MAX_SRV          6  /**< Maximum number of services supported by this module. This also indicates the maximum number of users allowed to be registered to this module. (one user per service). */


/**@brief   Type of the DB Discovery event.
 */
typedef enum
{
    BLE_DB_DISCOVERY_COMPLETE,      /**< Event indicating that the GATT Database discovery is complete. */
    BLE_DB_DISCOVERY_ERROR,         /**< Event indicating that an internal error has occurred in the DB Discovery module. This could typically be because of the SoftDevice API returning an error code during the DB discover.*/
    BLE_DB_DISCOVERY_SRV_NOT_FOUND, /**< Event indicating that the service was not found at the peer.*/
    BLE_DB_DISCOVERY_AVAILABLE      /**< Event indicating that the DB discovery module is available.*/
} ble_db_discovery_evt_type_t;



/**@brief   Structure for holding the information related to the GATT database at the server.
 *
 * @details This module identifies a remote database. Use one instance of this structure per
 *          connection.
 *
 * @warning This structure must be zero-initialized.
 */
typedef struct
{
    ble_gatt_db_srv_t   services[BLE_DB_DISCOVERY_MAX_SRV];  /**< Information related to the current service being discovered. This is intended for internal use during service discovery.*/
    uint8_t             srv_count;                           /**< Number of services at the peers GATT database.*/
    uint8_t             curr_char_ind;                       /**< Index of the current characteristic being discovered. This is intended for internal use during service discovery.*/
    uint8_t             curr_srv_ind;                        /**< Index of the current service being discovered. This is intended for internal use during service discovery.*/
    bool                discovery_in_progress;               /**< Variable to indicate if there is a service discovery in progress. */
    uint8_t             discoveries_count;                   /**< Number of service discoveries made, both successful and unsuccessful. */
    uint16_t            conn_handle;                         /**< Connection handle on which the discovery is started*/
} ble_db_discovery_t;


/**@brief   Structure containing the event from the DB discovery module to the application.
 */
typedef struct
{
    ble_db_discovery_evt_type_t evt_type;     /**< Type of event. */
    uint16_t                    conn_handle;  /**< Handle of the connection for which this event has occurred. */
    union
    {
        ble_gatt_db_srv_t discovered_db;  /**< Structure containing the information about the GATT Database at the server. This will be filled when the event type is @ref BLE_DB_DISCOVERY_COMPLETE.*/
        uint32_t               err_code;       /**< nRF Error code indicating the type of error which occurred in the DB Discovery module. This will be filled when the event type is @ref BLE_DB_DISCOVERY_ERROR. */
    } params;
} ble_db_discovery_evt_t;


/**@brief   DB Discovery event handler type. */
typedef void (* ble_db_discovery_evt_handler_t)(ble_db_discovery_evt_t * p_evt);


/**@brief     Function for initializing the DB Discovery module.
 *
 * @param[in] evt_handler        Event handler to be called by the DB discovery module when any event
 *                               related to discovery of the registered service occurs.
 *
 * @retval  NRF_SUCCESS    On successful initialization.
 * @retval  NRF_ERROR_NULL If the handler was NULL.
 */
uint32_t ble_db_discovery_init(ble_db_discovery_evt_handler_t evt_handler);


/**@brief Function for closing the DB Discovery module.
 *
 * @details This function will clear up any internal variables and states maintained by the
 *          module. To re-use the module after calling this function, the function @ref
 *          ble_db_discovery_init must be called again.
 *
 * @retval  NRF_SUCCESS    Operation success.
 */
uint32_t ble_db_discovery_close(void);


/**@brief Function for registering with the DB Discovery module.
 *
 * @details   The application can use this function to inform which service it is interested in
 *            discovering at the server.
 *
 * @param[in] p_uuid             Pointer to the UUID of the service to be discovered at the server.
 *
 * @note      The total number of services that can be discovered by this module is @ref
 *            BLE_DB_DISCOVERY_MAX_SRV. This effectively means that the maximum number of
 *            registrations possible is equal to the @ref BLE_DB_DISCOVERY_MAX_SRV.
 *
 * @retval    NRF_SUCCESS               Operation success.
 * @retval    NRF_ERROR_NULL            When a NULL pointer is passed as input.
 * @retval    NRF_ERROR_INVALID_STATE   If this function is called without calling the
 *                                      @ref ble_db_discovery_init.
 * @retval    NRF_ERROR_NO_MEM          The maximum number of registrations allowed by this module
 *                                      has been reached.
 */
uint32_t ble_db_discovery_evt_register(const ble_uuid_t * const             p_uuid);


/**@brief Function for starting the discovery of the GATT database at the server.
 *
 * @warning p_db_discovery structure must be zero-initialized.
 *
 * @param[out] p_db_discovery    Pointer to the DB Discovery structure.
 * @param[in]  conn_handle       The handle of the connection for which the discovery should be
 *                               started.
 *
 * @retval    NRF_SUCCESS               Operation success.
 * @retval    NRF_ERROR_NULL            When a NULL pointer is passed as input.
 * @retval    NRF_ERROR_INVALID_STATE   If this function is called without calling the
 *                                      @ref ble_db_discovery_init, or without calling
 *                                      @ref ble_db_discovery_evt_register.
 * @retval    NRF_ERROR_BUSY            If a discovery is already in progress for the current
 *                                      connection.
 *
 * @return                              This API propagates the error code returned by the
 *                                      SoftDevice API @ref sd_ble_gattc_primary_services_discover.
 */
uint32_t ble_db_discovery_start(ble_db_discovery_t * const p_db_discovery,
                                uint16_t                   conn_handle);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @param[in,out] p_db_discovery Pointer to the DB Discovery structure.
 * @param[in]     p_ble_evt      Pointer to the BLE event received.
 */
void ble_db_discovery_on_ble_evt(ble_db_discovery_t * const p_db_discovery,
                                 const ble_evt_t * const    p_ble_evt);


#ifdef __cplusplus
}
#endif

#endif // BLE_DB_DISCOVERY_H__

/** @} */
