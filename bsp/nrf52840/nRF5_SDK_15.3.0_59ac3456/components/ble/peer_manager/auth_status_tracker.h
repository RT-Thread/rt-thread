/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
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
#ifndef AUTH_STATUS_TRACKER_H__
#define AUTH_STATUS_TRACKER_H__

#include <stdint.h>
#include "sdk_errors.h"
#include "ble_gap.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @cond NO_DOXYGEN
 * @defgroup auth_status_tracker Authorization Status Tracker
 * @ingroup peer_manager
 * @{
 * @brief An internal module of @ref peer_manager. A module for tracking peers with failed
 *        authorization attempts. It uses tracking policy, which is described in Bluetooth
 *        Core Specification v5.0, Vol 3, Part H, Section 2.3.6.
 */


/**@brief Function for initializing the Authorization Status Tracker module.
 *
 * @retval NRF_SUCCESS Initialization was successful.
 * @retval Other       Other error codes might be returned by the @ref app_timer_create function.
 */
ret_code_t ast_init(void);


/**@brief Function for notifying about failed authorization attempts.
 *
 * @param[in]  conn_handle  Connection handle on which authorization attempt has failed.
 */
void ast_auth_error_notify(uint16_t conn_handle);


/**@brief Function for checking if pairing request must be rejected.
 *
 * @param[in]  conn_handle  Connection handle on which this check must be performed.
 *
 * @retval  true   If the connected peer is blacklisted.
 * @retval  false  If the connected peer is not blacklisted.
 */
bool ast_peer_blacklisted(uint16_t conn_handle);


/** @}
 * @endcond
 */


#ifdef __cplusplus
}
#endif

#endif /* AUTH_STATUS_TRACKER_H__ */
