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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_CRYPTO)

#if defined(NRF_CRYPTO_BACKEND_MICRO_ECC) && (NRF_CRYPTO_BACKEND_MICRO_ECC == 1)

#include "micro_ecc_lib_shared.h"
#include "nrf_crypto_types.h"
#include "uECC.h"

bool micro_ecc_curve_domain_get(nrf_ecc_curve_type_t curve_type, struct uECC_Curve_t const ** p_curve)
{
    switch(curve_type)
    {
#if defined(uECC_SUPPORTS_secp160r1) && uECC_SUPPORTS_secp160r1 == 1
        case NRF_CRYPTO_CURVE_SECP160R1:
            *p_curve = uECC_secp160r1();
            break;
#endif

#if defined(uECC_SUPPORTS_secp192r1) && uECC_SUPPORTS_secp192r1 == 1
        case NRF_CRYPTO_CURVE_SECP192R1:
            *p_curve = uECC_secp192r1();
            break;
#endif

#if defined(uECC_SUPPORTS_secp224r1) && uECC_SUPPORTS_secp224r1 == 1
        case NRF_CRYPTO_CURVE_SECP224R1:
            *p_curve = uECC_secp224r1();
            break;

#endif

        case NRF_CRYPTO_CURVE_SECP256R1:
            *p_curve = uECC_secp256r1();
            break;

#if defined(uECC_SUPPORTS_secp256k1) && defined(NRF_CRYPTO_CURVE_SECP256R1)
#if NRF_CRYPTO_CURVE_SECP256R1 == 1
        case NRF_CRYPTO_CURVE_SECP256K1:
            *p_curve = uECC_secp256k1();
            break;
#endif
#endif

        default:
            return false;

    }

    return true;
}


#endif // NRF_CRYPTO_BACKEND_MICRO_ECC

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
