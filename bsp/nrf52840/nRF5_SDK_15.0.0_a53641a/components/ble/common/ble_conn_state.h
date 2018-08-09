/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
/**
 * @file
 *
 * @defgroup ble_conn_state Connection state
 * @ingroup ble_sdk_lib
 * @{
 * @brief Module for storing data on BLE connections.
 *
 * @details This module stores certain states for each connection, which can be queried by
 *          connection handle. The module uses BLE events to keep the states updated.
 *
 *          In addition to the preprogrammed states, this module can also keep track of a number of
 *          binary user states, or <i>user flags</i>. These are reset to 0 for new connections, but
 *          otherwise not touched by this module.
 *
 *          This module uses the @ref nrf_atomic module to make the flag operations thread-safe.
 *
 * @note A connection handle is not immediately invalidated when it is disconnected. Certain states,
 *       such as the role, can still be queried until the next time a new connection is established
 *       to any device.
 *
 */

#ifndef BLE_CONN_STATE_H__
#define BLE_CONN_STATE_H__

#include <stdbool.h>
#include <stdint.h>
#include "ble.h"
#include "ble_gap.h"
#include "nrf_atomic.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Connection handle statuses.
 */
typedef enum
{
    BLE_CONN_STATUS_INVALID,       /**< The connection handle is invalid. */
    BLE_CONN_STATUS_DISCONNECTED,  /**< The connection handle refers to a connection that has been disconnected, but not yet invalidated. */
    BLE_CONN_STATUS_CONNECTED,     /**< The connection handle refers to an active connection. */
} ble_conn_state_status_t;

#define BLE_CONN_STATE_MAX_CONNECTIONS  BLE_GAP_ROLE_COUNT_COMBINED_MAX  /**< The maximum number of connections supported. */
#define BLE_CONN_STATE_USER_FLAG_COUNT  24                               /**< The number of available user flags. */


/**@brief Type used to present a list of conn_handles.
 */
typedef struct
{
    uint32_t len;                                           /**< The length of the list. */
    uint16_t conn_handles[BLE_CONN_STATE_MAX_CONNECTIONS];  /**< The list of handles. */
} ble_conn_state_conn_handle_list_t;

/**@brief One ID for each user flag collection.
 *
 * @details These IDs are used to identify user flag collections in the API calls.
 */
typedef enum
{
    BLE_CONN_STATE_USER_FLAG0 = 0,
    BLE_CONN_STATE_USER_FLAG1,
    BLE_CONN_STATE_USER_FLAG2,
    BLE_CONN_STATE_USER_FLAG3,
    BLE_CONN_STATE_USER_FLAG4,
    BLE_CONN_STATE_USER_FLAG5,
    BLE_CONN_STATE_USER_FLAG6,
    BLE_CONN_STATE_USER_FLAG7,
    BLE_CONN_STATE_USER_FLAG8,
    BLE_CONN_STATE_USER_FLAG9,
    BLE_CONN_STATE_USER_FLAG10,
    BLE_CONN_STATE_USER_FLAG11,
    BLE_CONN_STATE_USER_FLAG12,
    BLE_CONN_STATE_USER_FLAG13,
    BLE_CONN_STATE_USER_FLAG14,
    BLE_CONN_STATE_USER_FLAG15,
    BLE_CONN_STATE_USER_FLAG16,
    BLE_CONN_STATE_USER_FLAG17,
    BLE_CONN_STATE_USER_FLAG18,
    BLE_CONN_STATE_USER_FLAG19,
    BLE_CONN_STATE_USER_FLAG20,
    BLE_CONN_STATE_USER_FLAG21,
    BLE_CONN_STATE_USER_FLAG22,
    BLE_CONN_STATE_USER_FLAG23,
    BLE_CONN_STATE_USER_FLAG_INVALID,
} ble_conn_state_user_flag_id_t;


/**@brief Function to be called when a flag ID is set. See @ref ble_conn_state_for_each_set_user_flag.
 *
 * @param[in]  conn_handle  The connection the flag is set for.
 * @param[in]  p_context    Arbitrary pointer provided by the caller of
 *                          @ref ble_conn_state_for_each_set_user_flag.
 */
typedef void (*ble_conn_state_user_function_t)(uint16_t conn_handle, void * p_context);


/**
 * @defgroup ble_conn_state_functions BLE connection state functions
 * @{
 */


/**@brief Function for initializing or resetting the module.
 *
 * @details This function sets all states to their default, removing all records of connection handles.
 */
void ble_conn_state_init(void);


/**@brief Function for querying whether a connection handle represents a valid connection.
 *
 * @details A connection might be valid and have a BLE_CONN_STATUS_DISCONNECTED status.
 *          Those connections are invalidated after a new connection occurs.
 *
 * @param[in]  conn_handle  Handle of the connection.
 *
 * @retval true   If conn_handle represents a valid connection, thus a connection for which
                  we have a record.
 * @retval false  If conn_handle is @ref BLE_GAP_ROLE_INVALID, or if it has never been recorded.
 */
bool ble_conn_state_valid(uint16_t conn_handle);


/**@brief Function for querying the role of the local device in a connection.
 *
 * @param[in]  conn_handle  Handle of the connection to get the role for.
 *
 * @return  The role of the local device in the connection (see @ref BLE_GAP_ROLES).
 *          If conn_handle is not valid, the function returns BLE_GAP_ROLE_INVALID.
 */
uint8_t ble_conn_state_role(uint16_t conn_handle);


/**@brief Function for querying the status of a connection.
 *
 * @param[in]  conn_handle  Handle of the connection.
 *
 * @return  The status of the connection.
 *          If conn_handle is not valid, the function returns BLE_CONN_STATE_INVALID.
 */
ble_conn_state_status_t ble_conn_state_status(uint16_t conn_handle);


/**@brief Function for querying whether a connection is encrypted.
 *
 * @param[in]  conn_handle  Handle of connection to get the encryption state for.
 *
 * @retval true   If the connection is encrypted.
 * @retval false  If the connection is not encrypted or conn_handle is invalid.
 */
bool ble_conn_state_encrypted(uint16_t conn_handle);


/**@brief Function for querying whether a connection encryption is protected from Man in the Middle
 *        attacks.
 *
 * @param[in]  conn_handle  Handle of connection to get the MITM state for.
 *
 * @retval true   If the connection is encrypted with MITM protection.
 * @retval false  If the connection is not encrypted, or encryption is not MITM protected, or
 *                conn_handle is invalid.
 */
bool ble_conn_state_mitm_protected(uint16_t conn_handle);


/**@brief Function for querying the total number of connections.
 *
 * @return  The total number of valid connections for which the module has a record.
 */
uint32_t ble_conn_state_conn_count(void);


/**@brief Function for querying the total number of connections in which the role of the local
 *        device is @ref BLE_GAP_ROLE_CENTRAL.
 *
 * @return  The number of connections in which the role of the local device is
 *          @ref BLE_GAP_ROLE_CENTRAL.
 */
uint32_t ble_conn_state_central_conn_count(void);


/**@brief Function for querying the total number of connections in which the role of the local
 *        device is @ref BLE_GAP_ROLE_PERIPH.
 *
 * @return  The number of connections in which the role of the local device is
 *          @ref BLE_GAP_ROLE_PERIPH.
 */
uint32_t ble_conn_state_peripheral_conn_count(void);


/**@brief Function for obtaining a list of all connection handles for which the module has a record.
 *
 * @details This function takes into account connections whose state is BLE_CONN_STATUS_DISCONNECTED.
 *
 * @return  A list of all valid connection handles for which the module has a record.
 */
ble_conn_state_conn_handle_list_t ble_conn_state_conn_handles(void);


/**@brief Function for obtaining a list of connection handles in which the role of the local
 *        device is @ref BLE_GAP_ROLE_CENTRAL.
 *
 * @details This function takes into account connections whose state is BLE_CONN_STATUS_DISCONNECTED.
 *
 * @return  A list of all valid connection handles for which the module has a record and in which
 *          the role of local device is @ref BLE_GAP_ROLE_CENTRAL.
 */
ble_conn_state_conn_handle_list_t ble_conn_state_central_handles(void);


/**@brief Function for obtaining the handle for the connection in which the role of the local device
 *        is @ref BLE_GAP_ROLE_PERIPH.
 *
 * @details This function takes into account connections whose state is BLE_CONN_STATUS_DISCONNECTED.
 *
 * @return  A list of all valid connection handles for which the module has a record and in which
 *          the role of local device is @ref BLE_GAP_ROLE_PERIPH.
 */
ble_conn_state_conn_handle_list_t ble_conn_state_periph_handles(void);


/**@brief Function for translating a connection handle to a value that can be used as an array index.
 *
 * @details Function for mapping connection handles onto the range <0 - MAX_CONNECTIONS>.
 *
 * @note The index will be the same as long as a connection is invalid. A subsequent connection with
 *       the same connection handle might have a different index.
 *
 * @param[in]  conn_handle  The connection for which to retrieve an index.
 *
 * @return  An index unique to this connection. Or @ref BLE_CONN_STATE_MAX_CONNECTIONS if
 *          @p conn_handle refers to an invalid connection.
 */
uint16_t ble_conn_state_conn_idx(uint16_t conn_handle);


/**@brief Function for obtaining exclusive access to one of the user flag collections.
 *
 * @details The acquired collection contains one flag for each connection. These flags can be set
 *          and read individually for each connection.
 *
 *          The state of user flags will not be modified by the connection state module, except to
 *          set it to 0 for a connection when that connection is invalidated.
 *
 * @return  The ID of the acquired flag, or BLE_CONN_STATE_USER_FLAG_INVALID if none are available.
 */
ble_conn_state_user_flag_id_t ble_conn_state_user_flag_acquire(void);


/**@brief Function for reading the value of a user flag.
 *
 * @param[in]  conn_handle  Handle of connection to get the flag state for.
 * @param[in]  flag_id      Which flag to get the state for.
 *
 * @return  The state of the flag. If conn_handle is invalid, the function returns false.
 */
bool ble_conn_state_user_flag_get(uint16_t conn_handle, ble_conn_state_user_flag_id_t flag_id);


/**@brief Function for setting the value of a user flag.
 *
 * @param[in]  conn_handle  Handle of connection to set the flag state for.
 * @param[in]  flag_id      Which flag to set the state for.
 * @param[in]  value        Value to set the flag state to.
 */
void ble_conn_state_user_flag_set(uint16_t                      conn_handle,
                                  ble_conn_state_user_flag_id_t flag_id,
                                  bool                          value);


/**@brief Function for running a function for each active connection.
 *
 * @param[in]  user_function  The function to run for each connection.
 * @param[in]  p_context      Arbitrary context to be passed to \p user_function.
 *
 * @return  The number of times \p user_function was run.
 */
uint32_t ble_conn_state_for_each_connected(ble_conn_state_user_function_t user_function,
                                           void                         * p_context);


/**@brief Function for running a function for each flag that is set in a user flag collection.
 *
 * @param[in]  flag_id        Which flags to check.
 * @param[in]  user_function  The function to run when a flag is set.
 * @param[in]  p_context      Arbitrary context to be passed to \p user_function.
 *
 * @return  The number of times \p user_function was run.
 */
uint32_t ble_conn_state_for_each_set_user_flag(ble_conn_state_user_flag_id_t  flag_id,
                                               ble_conn_state_user_function_t user_function,
                                               void                         * p_context);

/** @} */
/** @} */


#ifdef __cplusplus
}
#endif

#endif /* BLE_CONN_STATE_H__ */
