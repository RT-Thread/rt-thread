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
#ifndef GATT_CACHE_MANAGER_H__
#define GATT_CACHE_MANAGER_H__

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
 * @defgroup gatt_cache_manager GATT Cache Manager
 * @ingroup peer_manager
 * @{
 * @brief An internal module of @ref peer_manager. A module for managing persistent storing of GATT
 *        attributes.
 */


/**@brief Function for initializing the GATT Cache Manager module.
 *
 * @retval NRF_SUCCESS         Initialization was successful.
 * @retval NRF_ERROR_INTERNAL  If an internal error occurred.
 */
ret_code_t gcm_init(void);


/**@brief Function for dispatching SoftDevice events to the GATT Cache Manager module.
 *
 * @param[in]  p_ble_evt  The SoftDevice event.
 */
void gcm_ble_evt_handler(ble_evt_t const * p_ble_evt);


/**@brief Function for triggering local GATT database data to be stored persistently.
 *
 * @details Values are retrieved from SoftDevice and written to persistent storage.
 *
 * @note This operation happens asynchronously, so any errors are reported as events.
 *
 * @note This function is only needed when you want to override the regular functionality of the
 *       module, e.g. to immediately store to flash instead of waiting for the native logic to
 *       perform the update.
 *
 * @param[in]  conn_handle  Connection handle to perform update on.
 *
 * @retval NRF_SUCCESS                    Store operation started.
 */
ret_code_t gcm_local_db_cache_update(uint16_t conn_handle);


/**@brief Function for manually informing that the local database has changed.
 *
 * @details This causes a service changed notification to be sent to all bonded peers that
 *          subscribe to it.
 */
void gcm_local_database_has_changed(void);

/** @}
  * @endcond
 */


#ifdef __cplusplus
}
#endif

#endif /* GATT_CACHE_MANAGER_H__ */
