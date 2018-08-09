/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#ifndef NFC_BLE_PAIR_LIB_H__
#define NFC_BLE_PAIR_LIB_H__

#include <stdbool.h>
#include "sdk_errors.h"
#include "ble.h"
#include "ble_advertising.h"
#include "peer_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@file
 *
 * @addtogroup nfc_api
 *
 * @defgroup nfc_ble_pair_lib NFC BLE Pairing Library
 * @ingroup  nfc_api
 * @brief    @tagAPI52 High-level library for BLE Connection Handover pairing using NFC.
 * @{
 */

/**
 * @brief NFC pairing types.
 */
typedef enum
{
    NFC_PAIRING_MODE_JUST_WORKS,        /**< Legacy Just Works pairing without a security key. */
    NFC_PAIRING_MODE_OOB,               /**< Legacy OOB pairing with a Temporary Key shared through NFC tag data. */
    NFC_PAIRING_MODE_LESC_JUST_WORKS,   /**< LESC pairing without authentication data. */
    NFC_PAIRING_MODE_LESC_OOB,          /**< LESC pairing with OOB authentication data. */
    NFC_PAIRING_MODE_GENERIC_OOB,       /**< OOB pairing with fallback from LESC to Legacy mode. */
    NFC_PAIRING_MODE_CNT                /**< Number of available pairing modes. */
} nfc_pairing_mode_t;

/**
 * @brief Funtion for initializing NFC tag data and turning on tag emulation.
 *
 * @warning It is assumed that Peer Manager has already been initialized before calling this function.
 *          It is also assumed that BLE advertising has already been initialized and it is configured
 *          to run in the BLE_ADV_MODE_FAST mode.
 *
 * @param[in] mode                  Pairing mode, this is the value of the @ref nfc_pairing_mode_t enum.
 * @param[in] p_advertising         Pointer to the advertising module instance.
 *
 * @retval NRF_SUCCESS              If NFC has been initialized properly.
 * @retval NRF_ERROR_INVALID_PARAM  If pairing mode is invalid.
 * @retval NRF_ERROR_NULL           If pointer to the advertising module instance is NULL.
 * @retval Other                    Other error codes might be returned depending on used modules.
 */
ret_code_t nfc_ble_pair_init(ble_advertising_t * const p_advertising, nfc_pairing_mode_t mode);

/**
 * @brief Function for setting pairing data and BLE security mode.
 *
 * @param[in] mode                  New pairing mode, this is the value of the @ref nfc_pairing_mode_t enum.
 *
 * @retval NRF_SUCCESS              If new pairing mode has been set correctly.
 * @retval NRF_ERROR_INVALID_PARAM  If pairing mode is invalid.
 * @retval Other                    Other error codes might be returned depending on used modules.
 */
ret_code_t nfc_ble_pair_mode_set(nfc_pairing_mode_t mode);

/**
 * @brief Function for obtaining the current pairing mode.
 *
 * @return Current pairing mode.
 */
nfc_pairing_mode_t nfc_ble_pair_mode_get(void);

/**
 * @brief Function for replying to @ref PM_EVT_CONN_SEC_PARAMS_REQ.
 *
 * @details This function is used to allow dynamic changes in the Peer Manager
 *          security parameters depending on security parameters
 *          obtained from the peer. This is essential for dynamic switching
 *          between Legacy OOB and LESC OOB pairing modes when pairing
 *          library works in @ref NFC_PAIRING_MODE_GENERIC_OOB mode.
 *
 * @note This function invokes the @ref pm_conn_sec_params_reply function.
 *
 * @param[in] p_evt       Pointer to the Peer Manager event struct with
 *                        information about peer security parameters.
 *
 * @retval NRF_SUCCESS    If proper reply has been sent or library does not need to reply.
 * @retval NRF_ERROR_NULL If pointer to the Peer Manager event is NULL.
 * @retval Other          Other error codes might be returned by the @ref pm_conn_sec_params_reply function.
 */
ret_code_t nfc_ble_pair_on_pm_params_req(pm_evt_t const * p_evt);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NFC_BLE_PAIR_LIB_H__
