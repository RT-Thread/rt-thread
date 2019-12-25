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

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OPTIGA)

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "nrf_crypto_ecc.h"
#include "nrf_crypto_ecdsa.h"

#include "optiga_backend_ecdsa.h"
#include "optiga_backend_utils.h"

/*lint -save -e????*/
#include "optiga/optiga_crypt.h"
/*lint -restore*/


ret_code_t nrf_crypto_backend_optiga_sign(
    void           * p_context,
    void     const * p_private_key,
    uint8_t  const * p_data,
    size_t           data_size,
    uint8_t        * p_signature)
{
    optiga_lib_status_t res = OPTIGA_LIB_ERROR;
    nrf_crypto_backend_optiga_ecc_private_key_t * p_prv =
            (nrf_crypto_backend_optiga_ecc_private_key_t *)p_private_key;

    optiga_key_id_t oid = p_prv->oid;

    uint16_t der_sig_len = NRF_CRYPTO_ECDSA_SECP256R1_SIGNATURE_SIZE + DER_OVERHEAD;
    uint8_t der_sig[NRF_CRYPTO_ECDSA_SECP256R1_SIGNATURE_SIZE + DER_OVERHEAD] = {0};

    res = optiga_crypt_ecdsa_sign((uint8_t *)p_data, data_size, oid, der_sig, &der_sig_len);
    if(res != OPTIGA_LIB_SUCCESS) {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    size_t sig_len = NRF_CRYPTO_ECDSA_SECP256R1_SIGNATURE_SIZE;
    return asn1_to_ecdsa_rs(der_sig, der_sig_len, p_signature, &sig_len);
}

ret_code_t nrf_crypto_backend_optiga_verify(
    void           * p_context,
    void     const * p_public_key,
    uint8_t  const * p_data,
    size_t           data_size,
    uint8_t  const * p_signature)
{
    nrf_crypto_backend_secp256r1_public_key_t * p_pub =
            (nrf_crypto_backend_secp256r1_public_key_t *)p_public_key;

    optiga_key_id_t oid = p_pub->oid;

    size_t der_sig_len = NRF_CRYPTO_ECDSA_SECP256R1_SIGNATURE_SIZE + DER_OVERHEAD;
    uint8_t der_sig[NRF_CRYPTO_ECDSA_SECP256R1_SIGNATURE_SIZE + DER_OVERHEAD] = {0};

    const size_t rs_size = NRF_CRYPTO_ECDSA_SECP256R1_SIGNATURE_SIZE/2;

    optiga_lib_status_t res = OPTIGA_LIB_ERROR;

    // Convert signature to DER format needed by OPTIGA
    if (!ecdsa_rs_to_asn1(p_signature,
                          rs_size,
                          p_signature + rs_size,
                          rs_size,
                          der_sig,
                          &der_sig_len))
    {
        return  NRF_ERROR_CRYPTO_INTERNAL;
    }

    if (oid == NRF_CRYPTO_INFINEON_PUBKEY_HOST_OID)
    {
        // Create magic OID for pubkey from host
        public_key_from_host_t pub_key = {
            .public_key = p_pub->raw_pubkey,
            .length = 64+4,   // public key + DER BITSTRING header
            .curve = OPTIGA_ECC_NIST_P_256
        };

        res = optiga_crypt_ecdsa_verify((uint8_t *)p_data,
                                        data_size,
                                        der_sig,
                                        der_sig_len,
                                        OPTIGA_CRYPT_HOST_DATA,
                                        &pub_key);
    }
    else
    {
        // Public key is in OPTIGA, referenced by OID
        res = optiga_crypt_ecdsa_verify((uint8_t *)p_data,
                                        data_size,
                                        der_sig,
                                        der_sig_len,
                                        OPTIGA_CRYPT_OID_DATA,
                                        &oid);
    }

    // consider everything that is not success a signature failure
    if (res != OPTIGA_LIB_SUCCESS)
    {
        return NRF_ERROR_CRYPTO_ECDSA_INVALID_SIGNATURE;
    }

    return NRF_SUCCESS;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OPTIGA)
