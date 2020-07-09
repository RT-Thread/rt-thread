/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#ifndef SECURITY_MANAGER_H__
#define SECURITY_MANAGER_H__

#include <stdint.h>
#include "sdk_errors.h"
#include "ble.h"
#include "ble_gap.h"
#include "peer_manager_types.h"
#include "security_dispatcher.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @cond NO_DOXYGEN
 * @defgroup security_manager Security Manager
 * @ingroup peer_manager
 * @{
 * @brief An internal module of @ref peer_manager. A module for streamlining pairing, bonding, and
 *        encryption, including flash storage of shared data.
 */


/**@brief Events that can come from the Security Manager module.
 */
typedef enum
{
    // SM_EVT_PARAMS_REQ             = SMD_EVT_PARAMS_REQ,             /**< Parameters are required for a pairing procedure on the specified connection. The user must provide them using @ref sm_sec_params_set or @ref sm_sec_params_reply (only this procedure, currently unimplemented). */
    SM_EVT_SLAVE_SECURITY_REQ     = SMD_EVT_SLAVE_SECURITY_REQ,     /**< The peer (peripheral) has requested link encryption, which has been enabled. */
    SM_EVT_SEC_PROCEDURE_START    = SMD_EVT_SEC_PROCEDURE_START,    /**< A security procedure has started. */
    SM_EVT_PAIRING_SUCCESS        = SMD_EVT_PAIRING_SUCCESS,        /**< A pairing procedure (and bonding if applicable) has completed with success. */
    SM_EVT_PAIRING_FAIL           = SMD_EVT_PAIRING_FAIL,           /**< A pairing procedure has failed which means no encryption and no bond could be established. */
    SM_EVT_LINK_ENCRYPTION_UPDATE = SMD_EVT_LINK_ENCRYPTION_UPDATE, /**< The security level of the link has been updated. The link is encrypted. */
    SM_EVT_LINK_ENCRYPTION_FAILED = SMD_EVT_LINK_ENCRYPTION_FAILED, /**< An attempt to start encryption on an unencrypted link failed because the peripheral did not have the correct keys. If the peer is the peripheral, the force_repairing flag should be set when reattempting @ref sm_link_secure. */
    SM_EVT_BONDING_INFO_STORED    = SMD_EVT_BONDING_INFO_STORED,    /**< Information exchanged during bonding with a peer has been stored persistently. */
    SM_EVT_ERROR_BONDING_INFO     = SMD_EVT_ERROR_BONDING_INFO,     /**< Information exchanged during bonding with a peer could not be stored persistently, because of an unexpected error. */
    SM_EVT_ERROR_UNEXPECTED       = SMD_EVT_ERROR_UNEXPECTED,       /**< An operation failed with an unexpected error. The error is provided. This is possibly a fatal error. */
    SM_EVT_ERROR_NO_MEM           /*= SMD_EVT_ERROR_NO_MEM*/,       /**< An operation failed because there was no available storage room in persistent storage. Please free up room and the operation will automatically continue after the next compression. */
    SM_EVT_ERROR_SMP_TIMEOUT,                                       /**< An operation failed because there has been an SMP timeout on the link, which entails that no more security operations can be performed on it. */
    SM_EVT_CONN_SEC_CONFIG_REQ,                                     /**< The peer (central) has requested pairing, but a bond already exists with that peer. Reply by calling @ref sm_conn_sec_config_reply before the event handler returns. If no reply is sent, a default is used. */
} sm_evt_id_t;


typedef struct
{
    sm_evt_id_t      evt_id;
    uint16_t         conn_handle;
    smd_evt_params_t params;
} sm_evt_t;


/**@brief Event handler for events from the Security Manager module.
 *
 * @param[in]  event        The event that has happened.
 * @param[in]  conn_handle  The connection handle the event pertains to.
 */
typedef void (*sm_evt_handler_t)(sm_evt_t const * p_event);


/**@brief Function for initializing the Security Manager module.
 *
 * @retval NRF_SUCCESS        If initialization was successful.
 * @retval NRF_ERROR_INTERNAL If an unexpected error occurred.
 */
ret_code_t sm_init(void);


/**@brief Function for dispatching SoftDevice events to the Security Manager module.
 *
 * @param[in]  ble_evt    The SoftDevice event.
 */
void sm_ble_evt_handler(ble_evt_t * ble_evt);


/**@brief Function for providing pairing and bonding parameters to use for pairing procedures.
 *
 * @details Until this is called, all bonding procedures initiated by the peer will be rejected.
 *          This function can be called multiple times, even with NULL p_sec_params, in which case
 *          it will go back to rejecting all procedures.
 *
 * @param[in]  p_sec_params  The security parameters to use for this link. Can be NULL to reject
 *                           all pairing procedures.
 *
 * @retval NRF_SUCCESS                    Success.
 * @retval NRF_ERROR_INVALID_PARAM        Invalid combination of parameters.
 * @retval NRF_ERROR_INVALID_STATE        Module is not initialized.
 */
ret_code_t sm_sec_params_set(ble_gap_sec_params_t * p_sec_params);


/**@brief Function for providing security configuration for a link.
 *
 * @details This function is optional, and must be called in reply to a @ref
 *          SM_EVT_CONN_SEC_CONFIG_REQ event, before the Peer Manager event handler returns. If it
 *          is not called in time, a default configuration is used. See @ref pm_conn_sec_config_t
 *          for the value of the default.
 *
 * @param[in]  conn_handle        The connection to set the configuration for.
 * @param[in]  p_conn_sec_config  The configuration.
 */
void sm_conn_sec_config_reply(uint16_t conn_handle, pm_conn_sec_config_t * p_conn_sec_config);


/**@brief Experimental function for specifying the public key to use for LESC operations.
 *
 * @details This function can be called multiple times. The specified public key will be used for
 *          all subsequent LESC (LE Secure Connections) operations until the next time this function
 *          is called.
 *
 * @note The key must continue to reside in application memory as it is not copied by Peer Manager.
 *
 * @param[in]  p_public_key  The public key to use for all subsequent LESC operations.
 *
 * @retval NRF_SUCCESS                    Pairing initiated successfully.
 * @retval NRF_ERROR_INVALID_STATE        Peer Manager is not initialized.
 */
ret_code_t sm_lesc_public_key_set(ble_gap_lesc_p256_pk_t * p_public_key);


/**@brief Function for providing pairing and bonding parameters to use for the current pairing
 *        procedure on a connection.
 *
 * @warning This function is not yet implemented.
 *
 * @note If this function returns an @ref NRF_ERROR_NULL, @ref NRF_ERROR_INVALID_PARAM, @ref
 *       BLE_ERROR_INVALID_CONN_HANDLE, or @ref NRF_ERROR_STORAGE_FULL, this function can be called
 *       again after corrective action.
 *
 * @note To reject a request, call this function with NULL p_sec_params.
 *
 * @param[in]  conn_handle   The connection handle of the connection the pairing is happening on.
 * @param[in]  p_sec_params  The security parameters to use for this link.
 *
 * @retval NRF_SUCCESS                    Success.
 * @retval NRF_ERROR_INVALID_STATE        Module is not initialized, or no parameters have been
 *                                        requested on that conn_handle, or this error originates
 *                                        from the SoftDevice.
 * @retval NRF_ERROR_INVALID_PARAM        Invalid combination of parameters (not including conn_handle).
 * @retval NRF_ERROR_TIMEOUT              There has been an SMP timeout, so no more SMP operations
 *                                        can be performed on this link.
 * @retval BLE_ERROR_INVALID_CONN_HANDLE  Invalid connection handle.
 * @retval NRF_ERROR_STORAGE_FULL         No more room in flash. Fix and reattempt later.
 * @retval NRF_ERROR_BUSY                 No write buffer. Reattempt later.
 */
ret_code_t sm_sec_params_reply(uint16_t conn_handle, ble_gap_sec_params_t * p_sec_params);


/**@brief Function for initiating security on the link, with the specified parameters.
 *
 * @note If the connection is a peripheral connection, this will send a security request to the
 *       master, but the master is not obligated to initiate pairing or encryption in response.
 * @note If the connection is a central connection and a key is available, the parameters will be
 *       used to determine whether to re-pair or to encrypt using the existing key. If no key is
 *       available, pairing will be started.
 *
 * @param[in]  conn_handle      Handle of the connection to initiate pairing on.
 * @param[in]  force_repairing  Whether to force a pairing procedure to happen regardless of whether
 *                              an encryption key already exists. This argument is only relevant for
 *                              the central role. Recommended value: false
 *
 * @retval NRF_SUCCESS                    Success.
 * @retval NRF_ERROR_TIMEOUT              There has been an SMP timeout, so no more SMP operations
 *                                        can be performed on this link.
 * @retval BLE_ERROR_INVALID_CONN_HANDLE  Invalid connection handle.
 * @retval NRF_ERROR_NOT_FOUND            Security parameters have not been set.
 * @retval NRF_ERROR_INVALID_STATE        Module is not initialized.
 * @retval NRF_ERROR_INTERNAL             An unexpected error occurred.
 */
ret_code_t sm_link_secure(uint16_t conn_handle, bool force_repairing);

/** @}
 * @endcond
 */


#ifdef __cplusplus
}
#endif

#endif /* SECURITY_MANAGER_H__ */
