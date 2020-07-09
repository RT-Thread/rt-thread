/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#ifndef NRF_CRYPTO_H__
#define NRF_CRYPTO_H__

#include <stdint.h>
#include "nrf_crypto_init.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_keys.h"
#include "nrf_crypto_hash.h"
#include "nrf_crypto_ecdsa.h"
#include "nrf_crypto_ecdh.h"
#include "nrf_crypto_rng.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_crypto Cryptography library
 * @ingroup app_common
 * @{
 *
 * @brief   Cryptography library (nrf_crypto).
 *
 * @details The cryptography library provides functions to compute keys, shared secrets, and hashes,
 *          and to sign and verify data using digital signatures.
 * @}
 *
 * @defgroup nrf_crypto_backends Backends
 * @ingroup nrf_crypto
 * @{
 *
 * @brief   Backends for the cryptography library.
 *
 * @details The cryptography library can be used with several backends that provide different functionality.
 * @}
 *
 * @defgroup nrf_crypto_backend_cryptocell Hardware-accelerated backend (CryptoCell)
 * @ingroup nrf_crypto_backends
 * @{
 *
 * @brief @tagAPI52840  Hardware-accelerated backend for the cryptography library based on CryptoCell (CC310).
 *
 * @details The CryptoCell backend is available on the nRF52840 SoC only, because it requires cryptography hardware. It uses the @ref cryptocell_api.
 * @}
 *
 * @defgroup nrf_crypto_backend_microecc Software backend (micro-ecc)
 * @ingroup nrf_crypto_backends
 * @{
 *
 * @brief Software backend for the cryptography library based on micro-ecc.
 *
 * @details The Software backend uses the external micro-ecc library. Make sure to install the library if you use this backend. See @ref lib_crypto_installing for details.
 *
 * @ref nrf_crypto_sw_hash "Hashing" and @ref nrf_crypto_sw_rng "random number generation" must be enabled separately.
 * @}
 *
 */


#ifdef __cplusplus
}
#endif

#endif // NRF_CRYPTO_H__

