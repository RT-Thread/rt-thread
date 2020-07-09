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

#if defined(NRF_CRYPTO_BACKEND_CC310_LIB) && (NRF_CRYPTO_BACKEND_CC310_LIB == 1)

#include "nrf_crypto.h"
#include "cc310_lib_shared.h"
#include "crys_ecpki_domain.h"

bool cc310_curve_domain_get(nrf_ecc_curve_type_t curve_type, CRYS_ECPKI_Domain_t ** p_domain)
{
    CRYS_ECPKI_DomainID_t domain_id;
    switch(curve_type)
    {
        case NRF_CRYPTO_CURVE_SECP160R1:
            domain_id = CRYS_ECPKI_DomainID_secp160r1;
            break;

        case NRF_CRYPTO_CURVE_SECP192R1:
            domain_id = CRYS_ECPKI_DomainID_secp192r1;
            break;

        case NRF_CRYPTO_CURVE_SECP224R1:
            domain_id = CRYS_ECPKI_DomainID_secp224r1;
            break;

        case NRF_CRYPTO_CURVE_SECP256R1:
            domain_id = CRYS_ECPKI_DomainID_secp256r1;
            break;

        case NRF_CRYPTO_CURVE_SECP384R1:
            domain_id = CRYS_ECPKI_DomainID_secp384r1;
            break;

        case NRF_CRYPTO_CURVE_SECP521R1:
            domain_id = CRYS_ECPKI_DomainID_secp521r1;
            break;

        case NRF_CRYPTO_CURVE_SECP192K1:
            domain_id = CRYS_ECPKI_DomainID_secp160k1;
            break;

        case NRF_CRYPTO_CURVE_SECP224K1:
            domain_id = CRYS_ECPKI_DomainID_secp224k1;
            break;

        case NRF_CRYPTO_CURVE_SECP256K1:
            domain_id = CRYS_ECPKI_DomainID_secp256k1;
            break;

        default:
            return false;
    }

    (*p_domain) = (CRYS_ECPKI_Domain_t*)CRYS_ECPKI_GetEcDomain(domain_id);
    return true;
}

#endif // NRF_CRYPTO_BACKEND_CC310_LIB

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
