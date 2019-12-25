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
/** @file
 *
 * @defgroup nrf_ble_lesc LESC module
 * @{
 * @ingroup peer_manager
 * @brief Module for handling LESC related events.
 */

#ifndef NRF_BLE_LESC_H__
#define NRF_BLE_LESC_H__

#include <stdint.h>
#include <string.h>
#include "ble.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Peer OOB Data handler prototype. */
typedef ble_gap_lesc_oob_data_t * (* nrf_ble_lesc_peer_oob_data_handler)(uint16_t conn_handle);

/**@brief   Function for initializing the LESC module.
 *
 * @details This function initializes the nrf_crypto for ECC and ECDH calculations, which are
 *          required to handle LESC authentication procedures.
 *
 * @retval NRF_SUCCESS   If the operation was successful.
 * @retval Other         Other error codes might be returned by the @ref nrf_crypto_init or
 *                       @ref nrf_ble_lesc_keypair_generate functions.
 */
ret_code_t nrf_ble_lesc_init(void);


/**@brief   Function for generating ECC keypair used for the LESC procedure.
 *
 * @details This function generates an ECC key pair, which consists of a private and public key. Keys are
 *          generated using ECC and are used to create LESC DH key during authentication procedures.
 *
 * @retval NRF_SUCCESS    If the operation was successful.
 * @retval NRF_ERROR_BUSY If any pending request needs to be processed by @ref nrf_ble_lesc_request_handler.
 * @retval Other          Other error codes might be returned by the @ref nrf_crypto_ecc_key_pair_generate,
 *                        @ref nrf_crypto_ecc_public_key_to_raw and @ref nrf_crypto_ecc_byte_order_invert
 *                        functions.
 */
ret_code_t nrf_ble_lesc_keypair_generate(void);


/**@brief   Function for generating LESC OOB data.
 *
 * @details This function generates LESC OOB data, which can be transmitted Out-Of-Band to the peer
 *          device and used during LESC procedure. It is required to generate ECC keypair with @ref
 *          nrf_ble_lesc_keypair_generate before calling this function.
 *
 * @retval NRF_SUCCESS               If the operation was successful.
 * @retval NRF_ERROR_INVALID_STATE   If the ECC keypair hasn't been generated or is currently
 *                                   being generated.
 */
ret_code_t nrf_ble_lesc_own_oob_data_generate(void);


/**@brief   Function for accessing the ECC public key used for LESC DH key generation.
 *
 * @details This function can be used to access the ECC public key, which is required to generate a LESC DH key
 *          at the peer side.
 *
 * @return Pointer to the generated public key or NULL if the key has not been generated yet.
 */
ble_gap_lesc_p256_pk_t * nrf_ble_lesc_public_key_get(void);


/**@brief   Function for accessing LESC OOB data.
 *
 * @details This function can be used to access LESC OOB data that is associated with this device.
 *          It is required to regenerate LESC OOB data with @ref nrf_ble_lesc_own_oob_data_generate,
 *          after each change of ECC keypair with @ref nrf_ble_lesc_keypair_generate.
 *
 * @return Pointer to the LESC OOB data or NULL if the data has not been generated yet or is no
 *         no longer valid.
 */
ble_gap_lesc_oob_data_t * nrf_ble_lesc_own_oob_data_get(void);


/**@brief   Function for setting the handler used to retrieve peer OOB data.
 *
 * @param[in]   handler   Function to retrieve peer OOB data.
 */
void nrf_ble_lesc_peer_oob_data_handler_set(nrf_ble_lesc_peer_oob_data_handler handler);


/**@brief   Function for responding to a DH key requests.
 *
 * @details This function calculates DH keys and supplies them to the SoftDevice if there are any
 *          pending requests for keys.
 *
 * @note This function should be called systematically (e.g. in the main application loop) to handle
 *       any pending DH key requests.
 *
 * @retval NRF_SUCCESS        If the operation was successful.
 * @retval NRF_ERROR_INTERNAL If the LESC module encountered an internal error. The only way to recover from
 *                            this type of error is to reset the application.
 * @retval Other              Other error codes might be returned by the @ref nrf_crypto_ecdh_compute,
 *                            @ref nrf_crypto_ecc_byte_order_invert, and @ref sd_ble_gap_lesc_dhkey_reply
 *                            functions.
 */
ret_code_t nrf_ble_lesc_request_handler(void);


/**@brief   Function for handling BLE stack events.
 *
 * @details This function handles events from the BLE stack that are of interest to the module.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
void nrf_ble_lesc_on_ble_evt(ble_evt_t const * p_ble_evt);


#ifdef __cplusplus
}
#endif

#endif // NRF_BLE_LESC_H__

/** @} */
