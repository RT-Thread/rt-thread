/**
 * Copyright (c) 2018 - 2018, Nordic Semiconductor ASA
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
 * @defgroup ble_lesc BLE LESC module
 * @{
 * @ingroup ble_sdk_lib
 *
 * @brief Module for handling LESC DHKey requests.
 */
#ifndef BLE_LESC_H__
#define BLE_LESC_H__

#include "sdk_common.h"
#include "ble_gap.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Function to initialize the ble_lesc module.
 *
 * @details This function initializes the nrf_crypto for key
 *          generation and ECDH calculations.
 *
 * @retval  NRF_SUCCESS     Initalization was successful.
 * @return  Any error code reported by @ref nrf_crypto_init.
 * @return  Any error code reported by @ref nrf_crypto_rng_init.
 */
ret_code_t ble_lesc_init(void);


/**@brief Function to generate a ECC key pair to use in LESC
 *
 * @details This function initializes the crypto system by calling nrf_crypto_init
 *          and nrf_crypto_rng_init before calling the required functions to generate
 *          the ECC key pair. If the key generation was successful this function sets
 *          the LESC local public key in peer manager by calling 
 *          @ref pm_lesc_public_key_set.
 *
 * @note    Run @ref ble_lesc_init before calling this API.
 *
 * @retval  NRF_SUCCESS     Generating ECC key pair was successful.
 * @return  Any error code form @ref nrf_crypto_ecc_key_pair_generate.
 * @return  Any error code from @ref nrf_crypto_ecc_public_key_to_raw.
 * @return  Any error code from @ref nrf_crypto_ecc_byte_order_invert.
 * @return  Any error code reported by @ref pm_lesc_public_key_set.
 */
ret_code_t ble_lesc_ecc_keypair_generate_and_set(void);


/**@brief Function to get the current LESC ECC local public key
 *
 * @details This function gets the current ECC local public key used LESC pairing procedure
 *          the format of this key is in a type usable by peer manager, NFC (OOB) and SoftDevice.
 *
 * @note    Run @ref ble_lesc_ecc_keypair_generate_and_set before calling this function.
 *
 * @retval  NRF_SUCCESS                 Getting the local public key was successful.
 * @retval  NRF_ERROR_NULL              pp_lesc_public_key was NULL.
 * @retval  NRF_ERROR_INVALID_STATE     No ECC keypair was generated prior to this call
 */
ret_code_t ble_lesc_ecc_local_public_key_get(ble_gap_lesc_p256_pk_t const ** pp_lesc_public_key);


/**@brief Function to service LESC ECDH calculations
 *
 * @details This function will calculate a LESC ECDH key (also known as shared secret) as long as
 *          @ref BLE_GAP_EVT_LESC_DHKEY_REQUEST event has been received from SoftDevice.
 *
 * @note This function should be run in a low interrupt priority like an idle-loop in the main
 *       application context.
 *
 * @warning Any error code reported by this function that is not @ref NRF_SUCCESS is critical and should be 
 *          handled by aborting all ongoing BLE operations and resetting the device. 
 *          Failure to do is a security risk.
 *
 * @retval NRF_SUCCESS              Service operation was successful.
 * @return Any other error code than NRF_SUCCESS which indicates that the device is in a critical state
 *         and must be restarted.
 */
ret_code_t ble_lesc_service_request_handler(void);


#ifdef __cplusplus
}
#endif

#endif // BLE_LESC_H__

/** @} */
