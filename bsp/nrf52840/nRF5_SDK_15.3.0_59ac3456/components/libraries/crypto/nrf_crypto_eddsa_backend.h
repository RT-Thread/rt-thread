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

#ifndef NRF_CRYPTO_EDDSA_BACKEND_H__
#define NRF_CRYPTO_EDDSA_BACKEND_H__
#if !defined(__SDK_DOXYGEN__)

#include <stdint.h>
#include <stddef.h>

#include "sdk_config.h"
#include "nrf_crypto_ecdsa_shared.h"

// Include all backends
#include "cc310_backend_eddsa.h"
#include "oberon_backend_eddsa.h"


#ifdef __cplusplus
extern "C" {
#endif

#if !NRF_CRYPTO_ECC_ED25519_ENABLED

// Context sizes are zero for disabled functionality
#define NRF_CRYPTO_BACKEND_ED25519_SIGN_CONTEXT_SIZE 0
#define NRF_CRYPTO_BACKEND_ED25519_VERIFY_CONTEXT_SIZE 0

// Dummy typedefs for disabled contexts
typedef uint8_t nrf_crypto_backend_ed25519_sign_context_t;
typedef uint8_t nrf_crypto_backend_ed25519_verify_context_t;

#endif

#ifdef __cplusplus
}
#endif

#endif // !defined(__SDK_DOXYGEN__)
#endif // NRF_CRYPTO_EDDSA_BACKEND_H__
