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
void sm_ble_evt_handler(ble_evt_t const * ble_evt);


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
 */
ret_code_t sm_sec_params_set(ble_gap_sec_params_t * p_sec_params);


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
void sm_conn_sec_config_reply(uint16_t conn_handle, pm_conn_sec_config_t * p_conn_sec_config);


/**@brief Function for providing security parameters for a link.
 *
 * @details This function is optional, and must be called in reply to a @ref
 *          PM_EVT_CONN_SEC_PARAMS_REQ event, before the Security Manager event handler returns. If
 *          it is not called in time, the parameters given in @ref sm_sec_params_set are used. See
 *          @ref pm_conn_sec_config_t for the value of the default.
 *
 * @param[in]  conn_handle   The connection to set the parameters for.
 * @param[in]  p_sec_params  The parameters. If NULL, the security procedure is rejected.
 * @param[in]  p_context     The context found in the request event that this function replies to.
 *
 * @retval NRF_SUCCESS              Successful reply.
 * @retval NRF_ERROR_NULL           p_context was null.
 * @retval NRF_ERROR_INVALID_PARAM  Value of p_sec_params was invalid.
 * @retval NRF_ERROR_INVALID_STATE  This module is not initialized.
 */
ret_code_t sm_sec_params_reply(uint16_t               conn_handle,
                               ble_gap_sec_params_t * p_sec_params,
                               void           const * p_context);


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
 * @retval NRF_ERROR_INVALID_STATE        This module is not initialized.
 */
ret_code_t sm_lesc_public_key_set(ble_gap_lesc_p256_pk_t * p_public_key);



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
 * @retval NRF_ERROR_INVALID_DATA         Peer is bonded, but no LTK was found, and repairing was
 *                                        not requested.
 * @retval NRF_ERROR_NOT_FOUND            Security parameters have not been set.
 * @retval NRF_ERROR_INVALID_STATE        A security procedure is already in progress on the link,
 *                                        or the link is disconnecting.
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
