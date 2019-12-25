/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#ifndef SECURITY_DISPATCHER_H__
#define SECURITY_DISPATCHER_H__

#include <stdint.h>
#include "sdk_errors.h"
#include "ble.h"
#include "ble_gap.h"
#include "peer_manager_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @cond NO_DOXYGEN
 * @defgroup security_dispatcher Security Dispatcher
 * @ingroup peer_manager
 * @{
 * @brief An internal module of @ref peer_manager. A module for streamlining pairing, bonding, and
 *        encryption, including flash storage of shared data.
 *
 */


/**@brief Function for initializing the Security Dispatcher module.
 *
 * @retval NRF_SUCCESS         Initialization was successful.
 * @retval NRF_ERROR_INTERNAL  An unexpected fatal error occurred.
 */
ret_code_t smd_init(void);


/**@brief Function for dispatching SoftDevice events to the Security Dispatcher module.
 *
 * @param[in]  ble_evt    The SoftDevice event.
 */
void smd_ble_evt_handler(ble_evt_t const * ble_evt);


/**@brief Function for providing security configuration for a link.
 *
 * @details This function is optional, and must be called in reply to a @ref
 *          PM_EVT_CONN_SEC_CONFIG_REQ event, before the Peer Manager event handler returns. If it
 *          is not called in time, a default configuration is used. See @ref pm_conn_sec_config_t
 *          for the value of the default.
 *
 * @param[in]  conn_handle        The connection to set the configuration for.
 * @param[in]  p_conn_sec_config  The configuration.
 */
void smd_conn_sec_config_reply(uint16_t conn_handle, pm_conn_sec_config_t * p_conn_sec_config);


/**@brief Function for providing pairing and bonding parameters to use for the current pairing
 *        procedure on a connection.
 *
 * @note If this function returns an @ref NRF_ERROR_NULL, @ref NRF_ERROR_INVALID_PARAM, @ref
 *       BLE_ERROR_INVALID_CONN_HANDLE, or @ref NRF_ERROR_STORAGE_FULL, this function can be called
 *       again after corrective action.
 *
 * @note To reject a request, call this function with NULL p_sec_params.
 *
 * @param[in]  conn_handle   The connection handle of the connection the pairing is happening on.
 * @param[in]  p_sec_params  The security parameters to use for this link.
 * @param[in]  p_public_key  A pointer to the public key to use if using LESC, or NULL.
 *
 * @retval NRF_SUCCESS                    Success.
 * @retval NRF_ERROR_INVALID_STATE        No parameters have been requested on that conn_handle, or
 *                                        the link is disconnecting.
 * @retval NRF_ERROR_INVALID_PARAM        Invalid combination of parameters (not including conn_handle).
 * @retval NRF_ERROR_TIMEOUT              There has been an SMP timeout, so no more SMP operations
 *                                        can be performed on this link.
 * @retval BLE_ERROR_INVALID_CONN_HANDLE  Invalid connection handle.
 * @retval NRF_ERROR_BUSY                 No write buffer. Reattempt later.
 * @retval NRF_ERROR_INTERNAL             A fatal error occurred.
 */
ret_code_t smd_params_reply(uint16_t                 conn_handle,
                            ble_gap_sec_params_t   * p_sec_params,
                            ble_gap_lesc_p256_pk_t * p_public_key);


/**@brief Function for initiating security on the link, with the specified parameters.
 *
 * @note If the connection is a peripheral connection, this will send a security request to the
 *       master, but the master is not obligated to initiate pairing or encryption in response.
 * @note If the connection is a central connection and a key is available, the parameters will be
 *       used to determine whether to re-pair or to encrypt using the existing key. If no key is
 *       available, pairing will be started.
 *
 * @param[in]  conn_handle      Handle of the connection to initiate pairing on.
 * @param[in]  p_sec_params     The security parameters to use for this link. As a central, this can
 *                              be NULL to reject a slave security request.
 * @param[in]  force_repairing  Whether to force a pairing procedure to happen regardless of whether
 *                              an encryption key already exists. This argument is only relevant for
 *                              the central role. Recommended value: false
 *
 * @retval NRF_SUCCESS                    Success.
 * @retval NRF_ERROR_NULL                 p_sec_params was NULL (peripheral only).
 * @retval NRF_ERROR_INVALID_STATE        A security procedure is already in progress on the link,
 *                                        or the link is disconnecting.
 * @retval NRF_ERROR_INVALID_PARAM        Invalid combination of parameters (not including conn_handle).
 * @retval NRF_ERROR_INVALID_DATA         Peer is bonded, but no LTK was found, and repairing was
 *                                        not requested.
 * @retval NRF_ERROR_BUSY                 Unable to initiate procedure at this time.
 * @retval NRF_ERROR_TIMEOUT              There has been an SMP timeout, so no more SMP operations
 *                                        can be performed on this link.
 * @retval BLE_ERROR_INVALID_CONN_HANDLE  Invalid connection handle.
 * @retval NRF_ERROR_INTERNAL             No more available peer IDs.
 */
ret_code_t smd_link_secure(uint16_t               conn_handle,
                           ble_gap_sec_params_t * p_sec_params,
                           bool                   force_repairing);

/** @}
 * @endcond
 */


#ifdef __cplusplus
}
#endif

#endif /* SECURITY_DISPATCHER_H__ */
