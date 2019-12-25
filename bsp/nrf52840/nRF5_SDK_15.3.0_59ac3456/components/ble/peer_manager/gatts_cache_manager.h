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
#ifndef GATTS_CACHE_MANAGER_H__
#define GATTS_CACHE_MANAGER_H__

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
 * @defgroup gatts_cache_manager GATT Server Cache Manager
 * @ingroup peer_manager
 * @{
 * @brief An internal module of @ref peer_manager. A module for managing persistent storing of GATT
 *        attributes pertaining to the GATT server role of the local device.
 */


/**@brief Function for initializing the GATT Server Cache Manager module.
 *
 * @retval NRF_SUCCESS         Initialization was successful.
 * @retval NRF_ERROR_INTERNAL  If an internal error occurred.
 */
ret_code_t gscm_init(void);


/**@brief Function for triggering local GATT database data to be stored persistently. Values are
 *        retrieved from the SoftDevice and written to persistent storage.
 *
 * @param[in]  conn_handle  Connection handle to perform update on.
 *
 * @retval NRF_SUCCESS                    Store operation started.
 * @retval BLE_ERROR_INVALID_CONN_HANDLE  conn_handle does not refer to an active connection with a
 *                                        bonded peer.
 * @retval NRF_ERROR_BUSY                 Unable to perform operation at this time. Reattempt later.
 * @retval NRF_ERROR_DATA_SIZE            Write buffer not large enough. Call will never work with
 *                                        this GATT database.
 * @retval NRF_ERROR_STORAGE_FULL         No room in persistent_storage. Free up space; the
 *                                        operation will be automatically reattempted after the
 *                                        next FDS garbage collection procedure.
 */
ret_code_t gscm_local_db_cache_update(uint16_t conn_handle);


/**@brief Function for applying stored local GATT database data to the SoftDevice. Values are
 *        retrieved from persistent storage and given to the SoftDevice.
 *
 * @param[in]  conn_handle  Connection handle to apply values to.
 *
 * @retval NRF_SUCCESS                    Store operation started.
 * @retval BLE_ERROR_INVALID_CONN_HANDLE  conn_handle does not refer to an active connection with a
 *                                        bonded peer.
 * @retval NRF_ERROR_INVALID_DATA         The stored data was rejected by the SoftDevice, which
 *                                        probably means that the local database has changed. The
 *                                        system part of the sys_attributes was attempted applied,
 *                                        so service changed indications can be sent to subscribers.
 * @retval NRF_ERROR_BUSY                 Unable to perform operation at this time. Reattempt later.
 * @retval NRF_ERROR_INTERNAL             An unexpected error happened.
 */
ret_code_t gscm_local_db_cache_apply(uint16_t conn_handle);


/**@brief Function for storing the fact that the local database has changed, for all currently
 *        bonded peers.
 *
 * @note This will cause a later call to @ref gscm_service_changed_ind_needed to return true for
 *       a connection with a currently bonded peer.
 */
void gscm_local_database_has_changed(void);


/**@brief Function for checking if a service changed indication should be sent.
 *
 * @param[in]  conn_handle  The connection to check.
 *
 * @return true if a service changed indication should be sent, false if not.
 */
bool gscm_service_changed_ind_needed(uint16_t conn_handle);


/**@brief Function for sending a service changed indication to a connected peer.
 *
 * @param[in]  conn_handle  The connection to send the indication on.
 *
 * @retval NRF_SUCCESS                       Indication sent or not needed.
 * @retval BLE_ERROR_INVALID_CONN_HANDLE     conn_handle does not refer to an active connection.
 * @retval NRF_ERROR_BUSY                    Unable to send indication at this time. Reattempt later.
 * @retval BLE_ERROR_GATTS_SYS_ATTR_MISSING  Information missing. Apply local cache, then reattempt.
 * @retval NRF_ERROR_INVALID_PARAM           From @ref sd_ble_gatts_service_changed. Unexpected.
 * @retval NRF_ERROR_NOT_SUPPORTED           Service changed characteristic is not present.
 * @retval NRF_ERROR_INVALID_STATE           Service changed cannot be indicated to this peer
 *                                           because the peer has not subscribed to it.
 * @retval NRF_ERROR_INTERNAL                An unexpected error happened.
 */
ret_code_t gscm_service_changed_ind_send(uint16_t conn_handle);


/**@brief Function for specifying that a peer has been made aware of the latest local database
 *        change.
 *
 * @note After calling this, a later call to @ref gscm_service_changed_ind_needed will to return
 *       false for this peer unless @ref gscm_local_database_has_changed is called again.
 *
 * @param[in]  peer_id  The connection to send the indication on.
 */
void gscm_db_change_notification_done(pm_peer_id_t peer_id);

/** @}
 * @endcond
*/


#ifdef __cplusplus
}
#endif

#endif /* GATTS_CACHE_MANAGER_H__ */
