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
#ifndef CC310_LIB_KEYS_H__
#define CC310_LIB_KEYS_H__

/** @file
 *
 * @defgroup nrf_crypto_backend_cc310_lib_ecc_keys CC310 backend ECC key types.
 * @{
 * @ingroup nrf_crypto_backend_cryptocell
 *
 * @brief Provides types required for CC310 backend ECC keys.
 */

#include "nrf_crypto_ecdsa.h"
#include "crys_ecpki_types.h"

#ifdef __cplusplus
extern "C" {
#if 0
}
#endif
#endif

/**@brief   Macro to get the size of the internal represenation of a private key
 *          in the CryptoCell API.
 */
#define NRF_CRYPTO_ECC_PRIVATE_KEY_MAX_SIZE (sizeof(CRYS_ECPKI_UserPrivKey_t))

/**@brief   Macro to get the size of the internal represenation of a public key
 *          in the CryptoCell API.
 */
#define NRF_CRYPTO_ECC_PUBLIC_KEY_MAX_SIZE (sizeof(CRYS_ECPKI_UserPublKey_t))

#ifdef __cplusplus
}
#endif

/**@} */

#endif // #ifndef CC310_LIB_KEYS_H__
