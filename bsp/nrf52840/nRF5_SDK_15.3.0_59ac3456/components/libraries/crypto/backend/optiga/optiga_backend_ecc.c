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

#include <stdbool.h>
#include <string.h>

#include "nrf_crypto_ecc.h"
#include "nrf_crypto_ecdh.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_rng.h"
#include "nrf_crypto_shared.h"
#include "nrf_assert.h"
#include "optiga_backend_ecc.h"

/*lint -save -e????*/
#include "optiga/optiga_crypt.h"
/*lint -restore*/

int nrf_crypto_backend_optiga_ecc_optiga_rng(void * p_param, unsigned char * p_data, size_t size)
{
#if NRF_MODULE_ENABLED(NRF_CRYPTO_RNG)
    return NRF_SUCCESS;

#else
    return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
#endif
}

static const uint8_t der_pub_key_header[] = {
    0x03, // ASN.1 BITSTRING
    0x42, // bytes following
    0x00, // no unused bits
    0x04  // uncompressed key, see https://tools.ietf.org/html/rfc5480#section-2.2
};

#define DER_PUB_KEY_HEADER_LEN (sizeof(der_pub_key_header)/sizeof(der_pub_key_header[0]))

// for our purposes we always have 1 byte tag + 1 byte length
#define DER_OCTET_STRING_HEADER_LEN 2

// lengths for the ASN.1 DER encoded keys imported and exported by OPTIGA
#define OPTIGA_SECP256R1_PRIV_KEY_LEN (DER_OCTET_STRING_HEADER_LEN + NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE)
#define OPTIGA_SECP256R1_PUBL_KEY_LEN (DER_PUB_KEY_HEADER_LEN + NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE)

ret_code_t nrf_crypto_backend_optiga_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key)
{
    optiga_lib_status_t res = OPTIGA_LIB_ERROR;

    nrf_crypto_backend_secp256r1_public_key_t * p_pub =
            (nrf_crypto_backend_secp256r1_public_key_t *) p_public_key;

    nrf_crypto_backend_secp256r1_private_key_t * p_priv =
            (nrf_crypto_backend_secp256r1_private_key_t *) p_private_key;

    bool export_private_key;
    if (p_priv->oid == 0)
    {
        // OID=0 was implicitly specified when initializising, mostly due to Nordic internal code calling our API
        p_priv->oid = (optiga_key_id_t)0xE100;
        export_private_key = false;
    }
    else if (p_priv->oid == NRF_CRYPTO_INFINEON_PRIVKEY_HOST_OID)
    {
        export_private_key = true;
    }
    else // any other value for OID, we assume the OID was purposefully specified by caller
    {
        export_private_key = false;
    }

    void * priv_key;
    if (export_private_key)
    {
        //lint -save -e611 -e545 (Suspicious cast, Suspicious use of &)
        priv_key = (void*) &p_priv->raw_privkey;
        //lint -restore
        p_priv->oid = (optiga_key_id_t)NRF_CRYPTO_INFINEON_PRIVKEY_HOST_OID;
    }
    else
    {
        //lint -save -e611 -e545 (Suspicious cast, Suspicious use of &)
        priv_key = (void*) &p_priv->oid;

        memset(p_priv->raw_privkey, 0, OPTIGA_SECP256R1_PRIV_KEY_LEN);
        //lint -restore
    }

    // Set all flags because the nrf_crypto API does not allow to specify key use
    const optiga_key_usage_t key_usage = (optiga_key_usage_t)(OPTIGA_KEY_USAGE_AUTHENTICATION |
                                                              OPTIGA_KEY_USAGE_SIGN |
                                                              OPTIGA_KEY_USAGE_KEY_AGREEMENT);

    uint16_t publ_key_len = OPTIGA_SECP256R1_PUBL_KEY_LEN;
    res = optiga_crypt_ecc_generate_keypair(OPTIGA_ECC_NIST_P_256,
                                            key_usage,
                                            export_private_key,
                                            priv_key,
                                            p_pub->raw_pubkey,
                                            &publ_key_len);

    if(res != OPTIGA_LIB_SUCCESS)
    {
        // error in the optiga library
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    if(publ_key_len != OPTIGA_SECP256R1_PUBL_KEY_LEN)
    {
        // unexpected length
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    // mark the public key as stored in host memory
    p_pub->oid = (optiga_key_id_t)NRF_CRYPTO_INFINEON_PUBKEY_HOST_OID;
    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_optiga_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key)
{
    return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
}


ret_code_t nrf_crypto_backend_optiga_private_key_from_raw(
    void          * p_private_key,
    uint8_t const * p_raw_data)
{
   return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
}

#define DER_TAG_OCTET_STRING 0x04

ret_code_t nrf_crypto_backend_optiga_private_key_to_raw(
    void    const * p_private_key,
    uint8_t       * p_raw_data)
{
    nrf_crypto_backend_secp256r1_private_key_t * p_priv =
            (nrf_crypto_backend_secp256r1_private_key_t *)p_private_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_priv->header.p_info;

    if(p_priv->oid != NRF_CRYPTO_INFINEON_PRIVKEY_HOST_OID)
    {
        // must use magic OID for private key exported to host
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    uint8_t* p_key = p_priv->raw_privkey;
    if(*p_key != DER_TAG_OCTET_STRING)
    {
        // private key must be encoded as DER OCTET STRING
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    p_key++;

    if(p_info == &g_nrf_crypto_ecc_secp256r1_curve_info)
    {
        if(*p_key != NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE)
        {
            // wrong length
            return NRF_ERROR_CRYPTO_INTERNAL;
        }
        p_key++;

        memcpy(p_raw_data, p_key, NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE);

        return NRF_SUCCESS;
    }

    return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
}

ret_code_t nrf_crypto_backend_optiga_public_key_from_raw(
    void          * p_public_key,
    uint8_t const * p_raw_data)
{
    nrf_crypto_backend_secp256r1_public_key_t * p_pub =
            (nrf_crypto_backend_secp256r1_public_key_t *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_pub->header.p_info;

    if (p_info == &g_nrf_crypto_ecc_secp256r1_curve_info)
    {
        // copy header
        memcpy(p_pub->raw_pubkey, der_pub_key_header, DER_PUB_KEY_HEADER_LEN);
        // copy public key data
        memcpy(p_pub->raw_pubkey + DER_PUB_KEY_HEADER_LEN, p_raw_data, NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE);
        // Set OID to magic number for host-supplied public key
        p_pub->oid = (optiga_key_id_t)NRF_CRYPTO_INFINEON_PUBKEY_HOST_OID;

        return NRF_SUCCESS;
    }

    return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
}


ret_code_t nrf_crypto_backend_optiga_public_key_to_raw(
    void const * p_public_key,
    uint8_t    * p_raw_data)
{
    nrf_crypto_backend_secp256r1_public_key_t * p_pub =
            (nrf_crypto_backend_secp256r1_public_key_t *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_pub->header.p_info;

    if(p_pub->oid != NRF_CRYPTO_INFINEON_PUBKEY_HOST_OID)
    {
        // must use magic OID for host supplied public key
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    if (p_info == &g_nrf_crypto_ecc_secp256r1_curve_info)
    {
        if(memcmp(p_pub->raw_pubkey, der_pub_key_header, DER_PUB_KEY_HEADER_LEN) != 0) {
            // public key not correctly encoded
            return NRF_ERROR_CRYPTO_INTERNAL;
        }

        memcpy(p_raw_data,
               p_pub->raw_pubkey + DER_PUB_KEY_HEADER_LEN,
               NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE);

        return NRF_SUCCESS;
    }

    return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
}


ret_code_t nrf_crypto_backend_optiga_private_key_free(
    void * p_private_key)
{
    return NRF_ERROR_CRYPTO_INTERNAL;
}

ret_code_t nrf_crypto_backend_optiga_public_key_free(
    void * p_public_key)
{
    return NRF_ERROR_CRYPTO_INTERNAL;
}

#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OPTIGA_ECC_SECP256R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp256r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_secp256r1_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_optiga_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP256R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)OPTIGA_ECC_NIST_P_256,
};
#endif

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_OPTIGA)
