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

#include <string.h>

#include "nrf_crypto_ecc_shared.h"
#include "nrf_crypto_ecdh_shared.h"
#include "nrf_crypto_shared.h"
#include "nrf_crypto_ecdh.h"
#include "optiga_backend_ecc.h"

/*lint -save -e????*/
#include "optiga/optiga_crypt.h"
/*lint -restore*/


ret_code_t nrf_crypto_backend_optiga_ecdh_compute(
    void       * p_context,
    void const * p_private_key,
    void const * p_public_key,
    uint8_t    * p_shared_secret)
{
    optiga_lib_status_t res = OPTIGA_LIB_ERROR;

    // Prepare public key
    nrf_crypto_backend_secp256r1_public_key_t * p_pub =
            (nrf_crypto_backend_secp256r1_public_key_t *) p_public_key;
    if (p_pub->oid != NRF_CRYPTO_INFINEON_PUBKEY_HOST_OID)
    {
        // OPTIGA requires the peer' public key to be host-supplied
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    // magic OID for pubkey from host
    public_key_from_host_t pub_key = {
        .public_key = p_pub->raw_pubkey,
        .length     = 64+4,   // public key + DER BITSTRING header
        .curve      = OPTIGA_ECC_NIST_P_256
    };

    // Prepare private key
    nrf_crypto_backend_secp256r1_private_key_t * p_priv =
            (nrf_crypto_backend_secp256r1_private_key_t *) p_private_key;
    optiga_key_id_t priv_oid = p_priv->oid;
    if (priv_oid == NRF_CRYPTO_INFINEON_PRIVKEY_HOST_OID)
    {
        // OPTIGA Trust X can only compute ECDH with private key from inside OPTIGA
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    res = optiga_crypt_ecdh(
        priv_oid,          // private key OID
        &pub_key,          // peer public key details
        true,              // true: export shared secret to host
        p_shared_secret    // resulting shared secret
    );

    if (res != OPTIGA_LIB_SUCCESS)
    {
        // error in the optiga library
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    return NRF_SUCCESS;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OPTIGA)

