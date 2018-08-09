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

#include <stdbool.h>
#include <stdint.h>

#include "nordic_common.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_ecc.h"
#include "app_util.h"
#include "sdk_macros.h"


#if NRF_CRYPTO_ECC_ENABLED


#if NRF_CRYPTO_ECC_IMPLEMENTED_CURVES_COUNT > 1


static const nrf_crypto_backend_ecc_key_pair_generate_fn_t key_pair_generate_impl[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    nrf_crypto_backend_secp160r1_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    nrf_crypto_backend_secp160r2_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    nrf_crypto_backend_secp192r1_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    nrf_crypto_backend_secp224r1_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    nrf_crypto_backend_secp256r1_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    nrf_crypto_backend_secp384r1_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    nrf_crypto_backend_secp521r1_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    nrf_crypto_backend_secp160k1_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    nrf_crypto_backend_secp192k1_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    nrf_crypto_backend_secp224k1_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    nrf_crypto_backend_secp256k1_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    nrf_crypto_backend_bp256r1_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    nrf_crypto_backend_bp384r1_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    nrf_crypto_backend_bp512r1_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    nrf_crypto_backend_curve25519_key_pair_generate,
#endif
#if NRF_CRYPTO_ECC_ED25519_ENABLED
    nrf_crypto_backend_ed25519_key_pair_generate,
#endif
};


static const uint16_t key_pair_generate_context_size[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP160R1_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    NRF_CRYPTO_BACKEND_SECP160R2_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP192R1_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP224R1_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP256R1_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP384R1_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP521R1_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP160K1_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP192K1_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP224K1_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP256K1_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    NRF_CRYPTO_BACKEND_BP256R1_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    NRF_CRYPTO_BACKEND_BP384R1_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    NRF_CRYPTO_BACKEND_BP512R1_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    NRF_CRYPTO_BACKEND_CURVE25519_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_ED25519_ENABLED
    NRF_CRYPTO_BACKEND_ED25519_KEY_PAIR_GENERATE_CONTEXT_SIZE,
#endif
};


static const nrf_crypto_backend_ecc_public_key_calculate_fn_t public_key_calculate_impl[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    nrf_crypto_backend_secp160r1_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    nrf_crypto_backend_secp160r2_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    nrf_crypto_backend_secp192r1_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    nrf_crypto_backend_secp224r1_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    nrf_crypto_backend_secp256r1_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    nrf_crypto_backend_secp384r1_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    nrf_crypto_backend_secp521r1_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    nrf_crypto_backend_secp160k1_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    nrf_crypto_backend_secp192k1_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    nrf_crypto_backend_secp224k1_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    nrf_crypto_backend_secp256k1_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    nrf_crypto_backend_bp256r1_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    nrf_crypto_backend_bp384r1_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    nrf_crypto_backend_bp512r1_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    nrf_crypto_backend_curve25519_public_key_calculate,
#endif
#if NRF_CRYPTO_ECC_ED25519_ENABLED
    nrf_crypto_backend_ed25519_public_key_calculate,
#endif
};


static const uint16_t public_key_calculate_context_size[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP160R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    NRF_CRYPTO_BACKEND_SECP160R2_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP192R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP224R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP256R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP384R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    NRF_CRYPTO_BACKEND_SECP521R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP160K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP192K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP224K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    NRF_CRYPTO_BACKEND_SECP256K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    NRF_CRYPTO_BACKEND_BP256R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    NRF_CRYPTO_BACKEND_BP384R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    NRF_CRYPTO_BACKEND_BP512R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    NRF_CRYPTO_BACKEND_CURVE25519_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
#if NRF_CRYPTO_ECC_ED25519_ENABLED
    NRF_CRYPTO_BACKEND_ED25519_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE,
#endif
};


static const nrf_crypto_backend_ecc_private_key_from_raw_fn_t private_key_from_raw_impl[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    nrf_crypto_backend_secp160r1_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    nrf_crypto_backend_secp160r2_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    nrf_crypto_backend_secp192r1_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    nrf_crypto_backend_secp224r1_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    nrf_crypto_backend_secp256r1_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    nrf_crypto_backend_secp384r1_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    nrf_crypto_backend_secp521r1_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    nrf_crypto_backend_secp160k1_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    nrf_crypto_backend_secp192k1_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    nrf_crypto_backend_secp224k1_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    nrf_crypto_backend_secp256k1_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    nrf_crypto_backend_bp256r1_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    nrf_crypto_backend_bp384r1_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    nrf_crypto_backend_bp512r1_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    nrf_crypto_backend_curve25519_private_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_ED25519_ENABLED
    nrf_crypto_backend_ed25519_private_key_from_raw,
#endif
};


static const nrf_crypto_backend_ecc_private_key_to_raw_fn_t private_key_to_raw_impl[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    nrf_crypto_backend_secp160r1_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    nrf_crypto_backend_secp160r2_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    nrf_crypto_backend_secp192r1_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    nrf_crypto_backend_secp224r1_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    nrf_crypto_backend_secp256r1_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    nrf_crypto_backend_secp384r1_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    nrf_crypto_backend_secp521r1_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    nrf_crypto_backend_secp160k1_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    nrf_crypto_backend_secp192k1_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    nrf_crypto_backend_secp224k1_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    nrf_crypto_backend_secp256k1_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    nrf_crypto_backend_bp256r1_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    nrf_crypto_backend_bp384r1_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    nrf_crypto_backend_bp512r1_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    nrf_crypto_backend_curve25519_private_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_ED25519_ENABLED
    nrf_crypto_backend_ed25519_private_key_to_raw,
#endif
};


static const nrf_crypto_backend_ecc_public_key_from_raw_fn_t public_key_from_raw_impl[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    nrf_crypto_backend_secp160r1_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    nrf_crypto_backend_secp160r2_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    nrf_crypto_backend_secp192r1_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    nrf_crypto_backend_secp224r1_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    nrf_crypto_backend_secp256r1_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    nrf_crypto_backend_secp384r1_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    nrf_crypto_backend_secp521r1_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    nrf_crypto_backend_secp160k1_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    nrf_crypto_backend_secp192k1_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    nrf_crypto_backend_secp224k1_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    nrf_crypto_backend_secp256k1_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    nrf_crypto_backend_bp256r1_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    nrf_crypto_backend_bp384r1_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    nrf_crypto_backend_bp512r1_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    nrf_crypto_backend_curve25519_public_key_from_raw,
#endif
#if NRF_CRYPTO_ECC_ED25519_ENABLED
    nrf_crypto_backend_ed25519_public_key_from_raw,
#endif
};


static const nrf_crypto_backend_ecc_public_key_to_raw_fn_t public_key_to_raw_impl[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    nrf_crypto_backend_secp160r1_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    nrf_crypto_backend_secp160r2_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    nrf_crypto_backend_secp192r1_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    nrf_crypto_backend_secp224r1_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    nrf_crypto_backend_secp256r1_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    nrf_crypto_backend_secp384r1_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    nrf_crypto_backend_secp521r1_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    nrf_crypto_backend_secp160k1_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    nrf_crypto_backend_secp192k1_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    nrf_crypto_backend_secp224k1_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    nrf_crypto_backend_secp256k1_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    nrf_crypto_backend_bp256r1_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    nrf_crypto_backend_bp384r1_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    nrf_crypto_backend_bp512r1_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    nrf_crypto_backend_curve25519_public_key_to_raw,
#endif
#if NRF_CRYPTO_ECC_ED25519_ENABLED
    nrf_crypto_backend_ed25519_public_key_to_raw,
#endif
};


static const nrf_crypto_backend_ecc_key_free_fn_t private_key_free_impl[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    nrf_crypto_backend_secp160r1_private_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    nrf_crypto_backend_secp160r2_private_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    nrf_crypto_backend_secp192r1_private_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    nrf_crypto_backend_secp224r1_private_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    nrf_crypto_backend_secp256r1_private_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    nrf_crypto_backend_secp384r1_private_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    nrf_crypto_backend_secp521r1_private_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    nrf_crypto_backend_secp160k1_private_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    nrf_crypto_backend_secp192k1_private_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    nrf_crypto_backend_secp224k1_private_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    nrf_crypto_backend_secp256k1_private_key_free,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    nrf_crypto_backend_bp256r1_private_key_free,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    nrf_crypto_backend_bp384r1_private_key_free,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    nrf_crypto_backend_bp512r1_private_key_free,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    nrf_crypto_backend_curve25519_private_key_free,
#endif
#if NRF_CRYPTO_ECC_ED25519_ENABLED
    nrf_crypto_backend_ed25519_private_key_free,
#endif
};


static const nrf_crypto_backend_ecc_key_free_fn_t public_key_free_impl[] =
{
#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
    nrf_crypto_backend_secp160r1_public_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP160R2_ENABLED
    nrf_crypto_backend_secp160r2_public_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP192R1_ENABLED
    nrf_crypto_backend_secp192r1_public_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP224R1_ENABLED
    nrf_crypto_backend_secp224r1_public_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP256R1_ENABLED
    nrf_crypto_backend_secp256r1_public_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP384R1_ENABLED
    nrf_crypto_backend_secp384r1_public_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP521R1_ENABLED
    nrf_crypto_backend_secp521r1_public_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP160K1_ENABLED
    nrf_crypto_backend_secp160k1_public_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP192K1_ENABLED
    nrf_crypto_backend_secp192k1_public_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP224K1_ENABLED
    nrf_crypto_backend_secp224k1_public_key_free,
#endif
#if NRF_CRYPTO_ECC_SECP256K1_ENABLED
    nrf_crypto_backend_secp256k1_public_key_free,
#endif
#if NRF_CRYPTO_ECC_BP256R1_ENABLED
    nrf_crypto_backend_bp256r1_public_key_free,
#endif
#if NRF_CRYPTO_ECC_BP384R1_ENABLED
    nrf_crypto_backend_bp384r1_public_key_free,
#endif
#if NRF_CRYPTO_ECC_BP512R1_ENABLED
    nrf_crypto_backend_bp512r1_public_key_free,
#endif
#if NRF_CRYPTO_ECC_CURVE25519_ENABLED
    nrf_crypto_backend_curve25519_public_key_free,
#endif
#if NRF_CRYPTO_ECC_ED25519_ENABLED
    nrf_crypto_backend_ed25519_public_key_free,
#endif
};


#define BACKEND_IMPL_GET(table, curve_type) (table)[(uint32_t)(curve_type)]


#else


#if NRF_CRYPTO_ECC_SECP160R1_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_secp160r1_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_secp160r1_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_secp160r1_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_secp160r1_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_secp160r1_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_secp160r1_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_secp160r1_private_key_free
#define public_key_free_impl      nrf_crypto_backend_secp160r1_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_SECP160R1_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_SECP160R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP160R2_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_secp160r2_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_secp160r2_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_secp160r2_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_secp160r2_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_secp160r2_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_secp160r2_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_secp160r2_private_key_free
#define public_key_free_impl      nrf_crypto_backend_secp160r2_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_SECP160R2_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_SECP160R2_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP192R1_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_secp192r1_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_secp192r1_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_secp192r1_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_secp192r1_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_secp192r1_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_secp192r1_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_secp192r1_private_key_free
#define public_key_free_impl      nrf_crypto_backend_secp192r1_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_SECP192R1_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_SECP192R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP224R1_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_secp224r1_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_secp224r1_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_secp224r1_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_secp224r1_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_secp224r1_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_secp224r1_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_secp224r1_private_key_free
#define public_key_free_impl      nrf_crypto_backend_secp224r1_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_SECP224R1_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_SECP224R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP256R1_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_secp256r1_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_secp256r1_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_secp256r1_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_secp256r1_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_secp256r1_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_secp256r1_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_secp256r1_private_key_free
#define public_key_free_impl      nrf_crypto_backend_secp256r1_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_SECP256R1_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_SECP256R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP384R1_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_secp384r1_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_secp384r1_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_secp384r1_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_secp384r1_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_secp384r1_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_secp384r1_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_secp384r1_private_key_free
#define public_key_free_impl      nrf_crypto_backend_secp384r1_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_SECP384R1_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_SECP384R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP521R1_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_secp521r1_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_secp521r1_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_secp521r1_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_secp521r1_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_secp521r1_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_secp521r1_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_secp521r1_private_key_free
#define public_key_free_impl      nrf_crypto_backend_secp521r1_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_SECP521R1_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_SECP521R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP160K1_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_secp160k1_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_secp160k1_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_secp160k1_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_secp160k1_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_secp160k1_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_secp160k1_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_secp160k1_private_key_free
#define public_key_free_impl      nrf_crypto_backend_secp160k1_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_SECP160K1_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_SECP160K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP192K1_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_secp192k1_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_secp192k1_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_secp192k1_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_secp192k1_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_secp192k1_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_secp192k1_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_secp192k1_private_key_free
#define public_key_free_impl      nrf_crypto_backend_secp192k1_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_SECP192K1_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_SECP192K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP224K1_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_secp224k1_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_secp224k1_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_secp224k1_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_secp224k1_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_secp224k1_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_secp224k1_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_secp224k1_private_key_free
#define public_key_free_impl      nrf_crypto_backend_secp224k1_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_SECP224K1_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_SECP224K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_SECP256K1_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_secp256k1_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_secp256k1_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_secp256k1_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_secp256k1_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_secp256k1_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_secp256k1_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_secp256k1_private_key_free
#define public_key_free_impl      nrf_crypto_backend_secp256k1_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_SECP256K1_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_SECP256K1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_BP256R1_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_bp256r1_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_bp256r1_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_bp256r1_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_bp256r1_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_bp256r1_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_bp256r1_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_bp256r1_private_key_free
#define public_key_free_impl      nrf_crypto_backend_bp256r1_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_BP256R1_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_BP256R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_BP384R1_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_bp384r1_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_bp384r1_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_bp384r1_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_bp384r1_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_bp384r1_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_bp384r1_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_bp384r1_private_key_free
#define public_key_free_impl      nrf_crypto_backend_bp384r1_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_BP384R1_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_BP384R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_BP512R1_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_bp512r1_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_bp512r1_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_bp512r1_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_bp512r1_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_bp512r1_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_bp512r1_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_bp512r1_private_key_free
#define public_key_free_impl      nrf_crypto_backend_bp512r1_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_BP512R1_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_BP512R1_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_CURVE25519_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_curve25519_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_curve25519_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_curve25519_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_curve25519_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_curve25519_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_curve25519_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_curve25519_private_key_free
#define public_key_free_impl      nrf_crypto_backend_curve25519_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_CURVE25519_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_CURVE25519_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#elif NRF_CRYPTO_ECC_ED25519_ENABLED
#define key_pair_generate_impl    nrf_crypto_backend_ed25519_key_pair_generate
#define public_key_calculate_impl nrf_crypto_backend_ed25519_public_key_calculate
#define private_key_from_raw_impl nrf_crypto_backend_ed25519_private_key_from_raw
#define private_key_to_raw_impl   nrf_crypto_backend_ed25519_private_key_to_raw
#define public_key_from_raw_impl  nrf_crypto_backend_ed25519_public_key_from_raw
#define public_key_to_raw_impl    nrf_crypto_backend_ed25519_public_key_to_raw
#define private_key_free_impl     nrf_crypto_backend_ed25519_private_key_free
#define public_key_free_impl      nrf_crypto_backend_ed25519_public_key_free
#define key_pair_generate_context_size \
    NRF_CRYPTO_BACKEND_ED25519_KEY_PAIR_GENERATE_CONTEXT_SIZE
#define public_key_calculate_context_size \
    NRF_CRYPTO_BACKEND_ED25519_PUBLIC_KEY_CALCULATE_CONTEXT_SIZE
#else
#define key_pair_generate_impl            NULL
#define public_key_calculate_impl         NULL
#define private_key_from_raw_impl         NULL
#define private_key_to_raw_impl           NULL
#define public_key_from_raw_impl          NULL
#define public_key_to_raw_impl            NULL
#define private_key_free_impl             NULL
#define public_key_free_impl              NULL
#define key_pair_generate_context_size    0
#define public_key_calculate_context_size 0
#endif


#define BACKEND_IMPL_GET(function, curve_type) (function)


#endif


ret_code_t nrf_crypto_internal_ecc_key_output_prepare(
    nrf_crypto_ecc_curve_info_t          const * p_curve_info,
    nrf_crypto_internal_ecc_key_header_t       * p_key_header)
{
    // Check NULL pointers
    VERIFY_TRUE(p_curve_info != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    VERIFY_TRUE(p_key_header != NULL, NRF_ERROR_CRYPTO_OUTPUT_NULL);

    // Clear init value to indicate that this key is not valid yet.
    p_key_header->init_value = 0;
    // Save curve info inside the header
    p_key_header->p_info = p_curve_info;

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_internal_ecc_key_input_check(
    nrf_crypto_internal_ecc_key_header_t const * p_key_header,
    uint32_t                                     init_value)
{
    // Check NULL pointer
    VERIFY_TRUE(p_key_header != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    // Check init value
    VERIFY_TRUE(p_key_header->init_value == init_value, NRF_ERROR_CRYPTO_ECC_KEY_NOT_INITIALIZED);

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_internal_ecc_raw_output_prepare(
    uint8_t    * p_raw_data,
    size_t     * p_raw_data_size,
    size_t       expected_size)
{
    // Check NULL pointer
    VERIFY_TRUE(p_raw_data != NULL, NRF_ERROR_CRYPTO_OUTPUT_NULL);

    if (p_raw_data_size != NULL) // User can provide NULL as p_raw_data_size to skip size checking
    {
        // Check if data fits into buffer
        VERIFY_TRUE(*p_raw_data_size >= expected_size, NRF_ERROR_CRYPTO_OUTPUT_LENGTH);
        // Provide actual data size
        *p_raw_data_size = expected_size;
    }

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_internal_ecc_raw_input_check(
    uint8_t const * p_raw_data,
    size_t          raw_data_size,
    size_t          expected_size)
{
    VERIFY_TRUE(p_raw_data != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    VERIFY_TRUE(raw_data_size == expected_size, NRF_ERROR_CRYPTO_INPUT_LENGTH);

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_ecc_key_pair_generate(
    nrf_crypto_ecc_key_pair_generate_context_t       * p_context,
    nrf_crypto_ecc_curve_info_t                const * p_curve_info,
    nrf_crypto_ecc_private_key_t                     * p_private_key,
    nrf_crypto_ecc_public_key_t                      * p_public_key)
{
    ret_code_t                                     result;
    void                                         * p_allocated_context = NULL;
    nrf_crypto_backend_ecc_key_pair_generate_fn_t  backend_implementation;
    size_t                                         context_size;

    // Get pointer to header for each key
    nrf_crypto_internal_ecc_key_header_t * p_private_key_header =
        (nrf_crypto_internal_ecc_key_header_t *)p_private_key;
    nrf_crypto_internal_ecc_key_header_t * p_public_key_header =
        (nrf_crypto_internal_ecc_key_header_t *)p_public_key;

    // Check and prepare parameters
    result = nrf_crypto_internal_ecc_key_output_prepare(p_curve_info, p_private_key_header);
    VERIFY_SUCCESS(result);
    result = nrf_crypto_internal_ecc_key_output_prepare(p_curve_info, p_public_key_header);
    VERIFY_SUCCESS(result);

    // Get backend specific information
    backend_implementation = BACKEND_IMPL_GET(key_pair_generate_impl, p_curve_info->curve_type);
    context_size = BACKEND_IMPL_GET(key_pair_generate_context_size, p_curve_info->curve_type);
    VERIFY_TRUE(backend_implementation != NULL, NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE);

    // Allocate context if not provided
    if (p_context == NULL && context_size > 0)
    {
        p_allocated_context = NRF_CRYPTO_ALLOC(context_size);
        VERIFY_TRUE(p_allocated_context != NULL, NRF_ERROR_CRYPTO_ALLOC_FAILED);
        p_context = p_allocated_context;
    }

    // Execute backend implementation
    result = backend_implementation(p_context, p_private_key, p_public_key);

    // Set init values to indicate valid key
    if (result == NRF_SUCCESS)
    {
        p_private_key_header->init_value = NRF_CRYPTO_INTERNAL_ECC_PRIVATE_KEY_INIT_VALUE;
        p_public_key_header->init_value = NRF_CRYPTO_INTERNAL_ECC_PUBLIC_KEY_INIT_VALUE;
    }

    // Deallocate context if allocated
    if (p_allocated_context != NULL)
    {
        NRF_CRYPTO_FREE(p_allocated_context);
    }

    return result;
}


ret_code_t nrf_crypto_ecc_public_key_calculate(
    nrf_crypto_ecc_public_key_calculate_context_t       * p_context,
    nrf_crypto_ecc_private_key_t                  const * p_private_key,
    nrf_crypto_ecc_public_key_t                         * p_public_key)
{
    ret_code_t                                        result;
    void                                            * p_allocated_context = NULL;
    nrf_crypto_backend_ecc_public_key_calculate_fn_t  backend_implementation;
    size_t                                            context_size;
    nrf_crypto_ecc_curve_info_t               const * p_info;

    // Get pointer to header for each key
    nrf_crypto_internal_ecc_key_header_t const * p_private_key_header =
        (nrf_crypto_internal_ecc_key_header_t const *)p_private_key;
    nrf_crypto_internal_ecc_key_header_t       * p_public_key_header =
        (nrf_crypto_internal_ecc_key_header_t *)p_public_key;

    // Check and prepare parameters
    result = nrf_crypto_internal_ecc_key_input_check(
        p_private_key_header,
        NRF_CRYPTO_INTERNAL_ECC_PRIVATE_KEY_INIT_VALUE);
    VERIFY_SUCCESS(result);
    p_info = p_private_key_header->p_info;
    result  = nrf_crypto_internal_ecc_key_output_prepare(p_info, p_public_key_header);
    VERIFY_SUCCESS(result);

    // Get backend specific information
    backend_implementation = BACKEND_IMPL_GET(public_key_calculate_impl, p_info->curve_type);
    context_size = BACKEND_IMPL_GET(public_key_calculate_context_size, p_info->curve_type);
    VERIFY_TRUE(backend_implementation != NULL, NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE);

    // Allocate context if not provided
    if (p_context == NULL && context_size > 0)
    {
        p_allocated_context = NRF_CRYPTO_ALLOC(context_size);
        VERIFY_TRUE(p_allocated_context != NULL, NRF_ERROR_CRYPTO_ALLOC_FAILED);
        p_context = p_allocated_context;
    }

    // Execute backend implementation
    result = backend_implementation(p_context, p_private_key, p_public_key);

    // Set init values to indicate valid key
    if (result == NRF_SUCCESS)
    {
        p_public_key_header->init_value = NRF_CRYPTO_INTERNAL_ECC_PUBLIC_KEY_INIT_VALUE;
    }

    // Deallocate context if allocated
    if (p_allocated_context != NULL)
    {
        NRF_CRYPTO_FREE(p_allocated_context);
    }

    return result;
}


ret_code_t nrf_crypto_ecc_private_key_from_raw(
    nrf_crypto_ecc_curve_info_t  const * p_curve_info,
    nrf_crypto_ecc_private_key_t       * p_private_key,
    uint8_t                      const * p_raw_data,
    size_t                               raw_data_size)
{
    ret_code_t                                       result;
    nrf_crypto_backend_ecc_private_key_from_raw_fn_t backend_implementation;

    // Get pointer to header
    nrf_crypto_internal_ecc_key_header_t * p_private_key_header =
        (nrf_crypto_internal_ecc_key_header_t *)p_private_key;

    // Check and prepare parameters
    result = nrf_crypto_internal_ecc_key_output_prepare(p_curve_info,
                                                        p_private_key_header);
    VERIFY_SUCCESS(result);
    result = nrf_crypto_internal_ecc_raw_input_check(p_raw_data,
                                                     raw_data_size,
                                                     p_curve_info->raw_private_key_size);
    VERIFY_SUCCESS(result);

    // Get backend specific information
    backend_implementation = BACKEND_IMPL_GET(private_key_from_raw_impl, p_curve_info->curve_type);
    VERIFY_TRUE(backend_implementation != NULL, NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE);

    // Execute backend implementation
    result = backend_implementation(p_private_key, p_raw_data);

    // Set init value to indicate valid key
    if (result == NRF_SUCCESS)
    {
        p_private_key_header->init_value = NRF_CRYPTO_INTERNAL_ECC_PRIVATE_KEY_INIT_VALUE;
    }

    return result;
}


ret_code_t nrf_crypto_ecc_private_key_to_raw(
    nrf_crypto_ecc_private_key_t const * p_private_key,
    uint8_t                            * p_raw_data,
    size_t                             * p_raw_data_size)
{
    ret_code_t                                             result;
    nrf_crypto_ecc_curve_info_t                    const * p_info;
    nrf_crypto_backend_ecc_private_key_to_raw_fn_t         backend_implementation;

    // Get pointer to header
    nrf_crypto_internal_ecc_key_header_t const * p_private_key_header =
        (nrf_crypto_internal_ecc_key_header_t const *)p_private_key;

    // Check and prepare parameters
    result = nrf_crypto_internal_ecc_key_input_check(
        p_private_key_header,
        NRF_CRYPTO_INTERNAL_ECC_PRIVATE_KEY_INIT_VALUE);
    VERIFY_SUCCESS(result);
    p_info = p_private_key_header->p_info;
    result = nrf_crypto_internal_ecc_raw_output_prepare(p_raw_data,
                                                        p_raw_data_size,
                                                        p_info->raw_private_key_size);
    VERIFY_SUCCESS(result);

    // Get backend specific information
    backend_implementation = BACKEND_IMPL_GET(private_key_to_raw_impl, p_info->curve_type);
    VERIFY_TRUE(backend_implementation != NULL, NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE);

    // Execute backend implementation
    result = backend_implementation(p_private_key, p_raw_data);

    return result;
}


ret_code_t nrf_crypto_ecc_public_key_from_raw(
    nrf_crypto_ecc_curve_info_t const * p_curve_info,
    nrf_crypto_ecc_public_key_t       * p_public_key,
    uint8_t                     const * p_raw_data,
    size_t                              raw_data_size)
{
    ret_code_t                                       result;
    nrf_crypto_backend_ecc_private_key_from_raw_fn_t backend_implementation;

    // Get pointer to header
    nrf_crypto_internal_ecc_key_header_t * p_public_key_header =
        (nrf_crypto_internal_ecc_key_header_t *)p_public_key;

    // Check and prepare parameters
    result = nrf_crypto_internal_ecc_key_output_prepare(p_curve_info,
                                                        p_public_key_header);
    VERIFY_SUCCESS(result);
    result = nrf_crypto_internal_ecc_raw_input_check(p_raw_data,
                                                     raw_data_size,
                                                     p_curve_info->raw_public_key_size);
    VERIFY_SUCCESS(result);

    // Get backend specific information
    backend_implementation = BACKEND_IMPL_GET(public_key_from_raw_impl, p_curve_info->curve_type);
    VERIFY_TRUE(backend_implementation != NULL, NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE);

    // Execute backend implementation
    result = backend_implementation(p_public_key, p_raw_data);

    // Set init value to indicate valid key
    if (result == NRF_SUCCESS)
    {
        p_public_key_header->init_value = NRF_CRYPTO_INTERNAL_ECC_PUBLIC_KEY_INIT_VALUE;
    }

    return result;
}


ret_code_t nrf_crypto_ecc_public_key_to_raw(
    nrf_crypto_ecc_public_key_t const * p_public_key,
    uint8_t                           * p_raw_data,
    size_t                            * p_raw_data_size)
{
    ret_code_t                                            result;
    nrf_crypto_ecc_curve_info_t                   const * p_info;
    nrf_crypto_backend_ecc_public_key_to_raw_fn_t         backend_implementation;

    // Get pointer to header
    nrf_crypto_internal_ecc_key_header_t const * p_public_key_header =
        (nrf_crypto_internal_ecc_key_header_t const *)p_public_key;

    // Check and prepare parameters
    result = nrf_crypto_internal_ecc_key_input_check(
        p_public_key_header,
        NRF_CRYPTO_INTERNAL_ECC_PUBLIC_KEY_INIT_VALUE);
    VERIFY_SUCCESS(result);
    p_info = p_public_key_header->p_info;
    result = nrf_crypto_internal_ecc_raw_output_prepare(p_raw_data,
                                                        p_raw_data_size,
                                                        p_info->raw_public_key_size);
    VERIFY_SUCCESS(result);

    // Get backend specific information
    backend_implementation = BACKEND_IMPL_GET(public_key_to_raw_impl, p_info->curve_type);
    VERIFY_TRUE(backend_implementation != NULL, NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE);

    // Execute backend implementation
    result = backend_implementation(p_public_key, p_raw_data);

    return result;
}


ret_code_t nrf_crypto_ecc_private_key_free(
    nrf_crypto_ecc_private_key_t * p_private_key)
{
    ret_code_t                                   result;
    nrf_crypto_ecc_curve_info_t          const * p_info;
    nrf_crypto_backend_ecc_key_free_fn_t         backend_implementation;

    // Get pointer to header
    nrf_crypto_internal_ecc_key_header_t * p_private_key_header =
        (nrf_crypto_internal_ecc_key_header_t *)p_private_key;

    // Check and prepare parameters
    result = nrf_crypto_internal_ecc_key_input_check(
        p_private_key_header,
        NRF_CRYPTO_INTERNAL_ECC_PRIVATE_KEY_INIT_VALUE);
    VERIFY_SUCCESS(result);
    p_info = p_private_key_header->p_info;

    UNUSED_PARAMETER(p_info); // Is some situations BACKEND_IMPL_GET() macro may not use second parameter

    // Get backend specific information
    backend_implementation = BACKEND_IMPL_GET(private_key_free_impl, p_info->curve_type);

    if (backend_implementation != NULL)
    {
        // Execute backend implementation
        result = backend_implementation(p_private_key);
    }
    else
    {
        // Free is not implemented by the backend, so nothing have to deallocated.
        result = NRF_SUCCESS;
    }

    // Clear init value to indicate invalid key
    p_private_key_header->init_value = 0;

    return result;
}


ret_code_t nrf_crypto_ecc_public_key_free(
    nrf_crypto_ecc_public_key_t * p_public_key)
{
    ret_code_t                                   result;
    nrf_crypto_ecc_curve_info_t          const * p_info;
    nrf_crypto_backend_ecc_key_free_fn_t         backend_implementation;

    // Get pointer to header
    nrf_crypto_internal_ecc_key_header_t * p_public_key_header =
        (nrf_crypto_internal_ecc_key_header_t *)p_public_key;

    // Check and prepare parameters
    result = nrf_crypto_internal_ecc_key_input_check(
        p_public_key_header,
        NRF_CRYPTO_INTERNAL_ECC_PUBLIC_KEY_INIT_VALUE);
    VERIFY_SUCCESS(result);
    p_info = p_public_key_header->p_info;

    UNUSED_PARAMETER(p_info); // Is some situations BACKEND_IMPL_GET() macro may not use second parameter

    // Get backend specific information
    backend_implementation = BACKEND_IMPL_GET(public_key_free_impl, p_info->curve_type);

    if (backend_implementation != NULL)
    {
        // Execute backend implementation
        result = backend_implementation(p_public_key);
    }
    else
    {
        // Free is not implemented by the backend, so nothing have to deallocated.
        result = NRF_SUCCESS;
    }

    // Clear init value to indicate invalid key
    p_public_key_header->init_value = 0;

    return result;
}


ret_code_t nrf_crypto_ecc_curve_info_get(
    void                         const * p_key,
    nrf_crypto_ecc_curve_info_t const ** pp_curve_info)
{
    ret_code_t result;

    // Get pointer to header
    nrf_crypto_internal_ecc_key_header_t const * p_key_header =
        (nrf_crypto_internal_ecc_key_header_t const *)p_key;

    // Check and prepare parameters
    VERIFY_TRUE(pp_curve_info != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    result = nrf_crypto_internal_ecc_key_input_check(
        p_key_header,
        NRF_CRYPTO_INTERNAL_ECC_PRIVATE_KEY_INIT_VALUE);
    if (result != NRF_SUCCESS)
    {
        // p_key can be private or public key, so check second case here
        result = nrf_crypto_internal_ecc_key_input_check(
            p_key_header,
            NRF_CRYPTO_INTERNAL_ECC_PUBLIC_KEY_INIT_VALUE);
    }
    VERIFY_SUCCESS(result);

    // Write output parameter
    *pp_curve_info = p_key_header->p_info;

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_ecc_byte_order_invert(
    nrf_crypto_ecc_curve_info_t const * p_curve_info,
    uint8_t                     const * p_raw_input,
    uint8_t                           * p_raw_output,
    size_t                              raw_data_size)
{
    uint8_t temp;
    size_t  from_index;
    size_t  to_index;
    size_t  integer_size;

    if (p_curve_info == NULL)
    {
        integer_size = raw_data_size;
    }
    else
    {
        integer_size = p_curve_info->raw_private_key_size;
    }

    VERIFY_TRUE(p_raw_input != NULL, NRF_ERROR_CRYPTO_INPUT_NULL);
    VERIFY_TRUE(p_raw_output != NULL, NRF_ERROR_CRYPTO_OUTPUT_NULL);

    // Loop over each big integer of the input
    while (raw_data_size >= integer_size)
    {
        // Swap byte by byte in current integer
        from_index = 0;
        to_index = integer_size - 1;
        while (from_index <= to_index)
        {
            // Swap bytes from source to destination, this may be the same buffer, so use temporary variable
            temp = p_raw_input[from_index];
            p_raw_output[from_index] = p_raw_input[to_index];
            p_raw_output[to_index] = temp;
            // Go to next pair of bytes
            from_index++;
            to_index--;
        }
        // Go to next integer
        raw_data_size -= integer_size;
        p_raw_input += integer_size;
        p_raw_output += integer_size;
    }

    if (raw_data_size != 0)
    {
        // Input size is not a multiple of big integer size, so it is invalid
        return NRF_ERROR_CRYPTO_INPUT_LENGTH;
    }

    return NRF_SUCCESS;
}


#endif // NRF_CRYPTO_ECC_ENABLED
