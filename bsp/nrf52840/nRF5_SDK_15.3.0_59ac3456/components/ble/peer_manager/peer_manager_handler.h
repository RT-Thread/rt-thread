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
/**
 * @file peer_manager_handler.h
 *
 * @defgroup pm_handler Peer Manager Standard Event Handlers
 * @ingroup peer_manager
 * @{
 * @brief Standard event handlers implementing some best practices for BLE security.
 */


#ifndef PEER_MANAGER_HANDLER_H__
#define PEER_MANAGER_HANDLER_H__

#include "ble.h"
#include "peer_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Standard function for making Peer Manager calls based on Peer Manager events.
 *
 * This function does the following:
 *  - Logs all PM events using @ref nrf_log, at different severity levels.
 *  - Starts encryption if connected to an already bonded peer. This is affected by @ref
 *    PM_HANDLER_SEC_DELAY_MS.
 *  - Calls @ref app_error on fatal errors.
 *
 * @note In normal circumstances, this function should be called for every Peer Manager event.
 *
 * @param[in]  p_pm_evt  Peer Manager event to handle.
 */
void pm_handler_on_pm_evt(pm_evt_t const * p_pm_evt);

/**@brief Auxiliary standard function for logging Peer Manager events.
 *
 * This function logs all PM events using @ref nrf_log, at different severity levels. The
 * @ref PM_LOG_ENABLED and other @c PM_LOG_* configs control these log messages.
 *
 * @note This function is called internally by @ref pm_handler_on_pm_evt.
 *
 * @param[in]  p_pm_evt  Peer Manager event to log.
 */
void pm_handler_pm_evt_log(pm_evt_t const * p_pm_evt);

/**@brief Auxiliary standard function for maintaining room in flash based on Peer Manager events.
 *
 * This function does the following:
 *  - Ranks peers by when they last connected.
 *  - Garbage collects the flash when needed.
 *  - Deletes the lowest ranked peer(s) when garbage collection is insufficient.
 *
 * @note See also @ref pm_handler_flash_clean_on_return.
 * @note In normal circumstances, this function should be called for every Peer Manager event.
 * @note This function is a supplement to, not a replacement for @ref pm_handler_on_pm_evt.
 *
 * @param[in]  p_pm_evt  Peer Manager event to handle.
 */
void pm_handler_flash_clean(pm_evt_t const * p_pm_evt);

/**@brief Function to call when a Peer Manager function returns @ref NRF_ERROR_STORAGE_FULL.
 *
 * @note This should only be used if @ref pm_handler_flash_clean is also used.
 */
void pm_handler_flash_clean_on_return(void);

/**@brief Auxiliary standard function for disconnecting when the connection could not be secured.
 *
 * This function disconnects whenever connection security fails, i.e. whenever it receives a
 * @ref PM_EVT_CONN_SEC_FAILED.
 *
 * @note In normal circumstances, this function should be called for every Peer Manager event.
 * @note This function is a supplement to, not a replacement for @ref pm_handler_on_pm_evt.
 *
 * @param[in]  p_pm_evt  Peer Manager event to handle.
 */
void pm_handler_disconnect_on_sec_failure(pm_evt_t const * p_pm_evt);

/**@brief Function for securing a connection when it is established.
 *
 * This function starts security when receiving a @ref BLE_GAP_EVT_CONNECTED event. This is
 * affected by @ref PM_HANDLER_SEC_DELAY_MS.
 *
 * @note In normal circumstances, this function should be called for every BLE event.
 *
 * @param[in]  p_ble_evt  BLE event to handle.
 */
void pm_handler_secure_on_connection(ble_evt_t const * p_ble_evt);

/**@brief Function for securing a connection if a GATT read or write operation lacks security.
 *
 * This function starts pairing if a GATTC procedure fails with insufficient encryption
 * or insufficient authentication. This is meant to delay performing pairing/bonding until
 * it is actually needed to access resources. This is affected by @ref PM_HANDLER_SEC_DELAY_MS.
 *
 * @note When using this handler, the failed GATTC operation must be retried by the user.
 * @note This does not work when using Write Without Response (@ref BLE_GATT_OP_WRITE_CMD) because
 *       the server does not send any response, even on error. Instead, the write will be
 *       silently dropped by the server.
 * @note In normal circumstances, this function should be called for every BLE event.
 *
 * @param[in]  p_ble_evt  BLE event to handle.
 */
void pm_handler_secure_on_error(ble_evt_t const * p_ble_evt);

#ifdef __cplusplus
}
#endif

/** @}*/

#endif // PEER_MANAGER_HANDLER_H__
