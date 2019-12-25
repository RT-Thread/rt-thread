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

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)

#include <string.h>

#include "nrf_crypto_mem.h"
#include "nrf_crypto_ecc.h"
#include "cc310_backend_ecc.h"
#include "cc310_backend_shared.h"
#include "cc310_backend_mutex.h"
#include "crys_ecpki_kg.h"
#include "crys_ecpki_domain.h"
#include "crys_ecpki_build.h"
#include "crys_ecpki_error.h"
#include "crys_rnd_error.h"
#include "crys_ec_mont_api.h"
#include "crys_ec_edw_api.h"
#include "crys_ec_mont_edw_error.h"
#include "nrf_crypto_shared.h"


#define CC310_UNCOMPRESSED_PUBLIC_KEY_ID_BYTE 0x04 /**< @brief @internal Byte value used by CC310 library to prefix uncompressed public key. */


ret_code_t nrf_crypto_backend_cc310_ecc_error_convert(uint32_t crys_error)
{
    switch (crys_error)
    {
        case CRYS_OK:
            return NRF_SUCCESS;

        case CRYS_ECDSA_VERIFY_INCONSISTENT_VERIFY_ERROR:
        case CRYS_ECEDW_SIGN_VERIFY_FAILED_ERROR:
            return NRF_ERROR_CRYPTO_ECDSA_INVALID_SIGNATURE;

        case CRYS_RND_INSTANTIATION_NOT_DONE_ERROR:
            return NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED;

        default:
            return NRF_ERROR_CRYPTO_INTERNAL;
    }
}


/** @internal @brief Returns domain value from @ref CRYS_ECPKI_DomainID_t enum based on
 *  value from info structure.
 *
 * @param[in] p_info  Curve info.
 * @returns           Pointer to CC310 domain.
 */
static CRYS_ECPKI_Domain_t const * get_domain(nrf_crypto_ecc_curve_info_t const * p_info)
{
    CRYS_ECPKI_DomainID_t       domain_id = (CRYS_ECPKI_DomainID_t)(intptr_t)p_info->p_backend_data;
    const CRYS_ECPKI_Domain_t * domain    = CRYS_ECPKI_GetEcDomain(domain_id);
    return domain;
}


ret_code_t nrf_crypto_backend_cc310_ecc_public_key_convert(
    nrf_crypto_backend_cc310_ecc_public_key_t * p_pub,
    CRYS_ECPKI_BUILD_TempData_t * p_temp_data)
{
    ret_code_t                   result;
    CRYSError_t                  crys_error;
    CRYS_ECPKI_Domain_t const  * p_domain;
    uint8_t                      ucompressed_key[NRF_CRYPTO_ECC_RAW_PUBLIC_KEY_MAX_SIZE + 1];
    bool                         mutex_locked;

    nrf_crypto_ecc_curve_info_t const * p_info = p_pub->header.p_info;

    if (p_pub->key_converted)
    {
        return NRF_SUCCESS;
    }

    p_domain = get_domain(p_info);

    // Tell CC310 library that this is raw public key in uncompressed format.
    ucompressed_key[0] = CC310_UNCOMPRESSED_PUBLIC_KEY_ID_BYTE;
    memcpy(&ucompressed_key[1], p_pub->key.raw_public_key, p_info->raw_public_key_size);

    mutex_locked = cc310_backend_mutex_trylock();
    if (!mutex_locked)
    {
        return NRF_ERROR_CRYPTO_BUSY;
    }

    cc310_backend_enable();

    crys_error = CRYS_ECPKI_BuildPublKeyPartlyCheck(p_domain,
                                                    ucompressed_key,
                                                    p_info->raw_public_key_size + 1,
                                                    &p_pub->key.cc310_public_key,
                                                    p_temp_data);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);
    if (result == NRF_SUCCESS)
    {
        p_pub->key_converted = true;
    }
    else
    {
        memcpy(p_pub->key.raw_public_key, &ucompressed_key[1], p_info->raw_public_key_size);
    }

    return result;
}


ret_code_t nrf_crypto_backend_cc310_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key)
{
    ret_code_t                   result;
    CRYSError_t                  crys_error;
    CRYS_ECPKI_Domain_t  const * p_domain;
    bool                         mutex_locked;

    nrf_crypto_backend_cc310_key_pair_generate_context_t * p_ctx =
        (nrf_crypto_backend_cc310_key_pair_generate_context_t *)p_context;

    nrf_crypto_backend_cc310_ecc_private_key_t * p_prv =
        (nrf_crypto_backend_cc310_ecc_private_key_t *)p_private_key;

    nrf_crypto_backend_cc310_ecc_public_key_t  * p_pub =
        (nrf_crypto_backend_cc310_ecc_public_key_t *)p_public_key;

    p_domain = get_domain(p_prv->header.p_info);

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    crys_error = CRYS_ECPKI_GenKeyPair(p_context,
                                       nrf_crypto_backend_cc310_rng,
                                       p_domain,
                                       &p_prv->private_key,
                                       &p_pub->key.cc310_public_key,
                                       &p_ctx->temp_data,
                                       NULL);
    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    p_pub->key_converted = true;

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);
    return result;
}


ret_code_t nrf_crypto_backend_cc310_private_key_from_raw(
    void          * p_private_key,
    uint8_t const * p_raw_data)
{
    ret_code_t                  result;
    CRYSError_t                 crys_error;
    CRYS_ECPKI_Domain_t const * p_domain;
    bool                        mutex_locked;

    nrf_crypto_backend_cc310_ecc_private_key_t * p_prv =
            (nrf_crypto_backend_cc310_ecc_private_key_t *)p_private_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_prv->header.p_info;

    p_domain = get_domain(p_info);

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    crys_error = CRYS_ECPKI_BuildPrivKey(p_domain,
                                         p_raw_data,
                                         p_info->raw_private_key_size,
                                         &p_prv->private_key);

    cc310_backend_mutex_unlock();

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);
    return result;
}


ret_code_t nrf_crypto_backend_cc310_private_key_to_raw(
    void const * p_private_key,
    uint8_t    * p_raw_data)
{
    ret_code_t    result;
    CRYSError_t   crys_error;
    uint32_t      key_size;

    nrf_crypto_backend_cc310_ecc_private_key_t * p_prv =
            (nrf_crypto_backend_cc310_ecc_private_key_t *)p_private_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_prv->header.p_info;

    key_size = p_info->raw_private_key_size;

    crys_error = CRYS_ECPKI_ExportPrivKey(&p_prv->private_key,
                                          p_raw_data,
                                          &key_size);

    if (key_size != p_info->raw_private_key_size)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);

    return result;
}


ret_code_t nrf_crypto_backend_cc310_public_key_from_raw(
    void          * p_public_key,
    uint8_t const * p_raw_data)
{
    nrf_crypto_backend_cc310_ecc_public_key_t  * p_pub =
            (nrf_crypto_backend_cc310_ecc_public_key_t *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_pub->header.p_info;

    memcpy(p_pub->key.raw_public_key, p_raw_data, p_info->raw_public_key_size);
    p_pub->key_converted = false;

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_cc310_public_key_to_raw(
    void const * p_public_key,
    uint8_t    * p_raw_data)
{
    ret_code_t    result;
    CRYSError_t   crys_error;
    uint8_t       ucompressed_key[NRF_CRYPTO_ECC_RAW_PUBLIC_KEY_MAX_SIZE + 1];
    uint32_t      key_size;
    bool          mutex_locked;

    nrf_crypto_backend_cc310_ecc_public_key_t * p_pub =
            (nrf_crypto_backend_cc310_ecc_public_key_t *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_pub->header.p_info;

    if (!p_pub->key_converted)
    {
        memcpy(p_raw_data, p_pub->key.raw_public_key, p_info->raw_public_key_size);
        return NRF_SUCCESS;
    }

    mutex_locked = cc310_backend_mutex_trylock();
    if (!mutex_locked)
    {
        return NRF_ERROR_CRYPTO_BUSY;
    }

    key_size = p_info->raw_public_key_size + 1;

    crys_error = CRYS_ECPKI_ExportPublKey(&p_pub->key.cc310_public_key,
                                          CRYS_EC_PointUncompressed,
                                          ucompressed_key,
                                          &key_size);

    cc310_backend_mutex_unlock();

    if ((key_size != p_info->raw_public_key_size + 1)
        || (ucompressed_key[0] != CC310_UNCOMPRESSED_PUBLIC_KEY_ID_BYTE))
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    memcpy(p_raw_data, &ucompressed_key[1], p_info->raw_public_key_size);

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);
    return result;
}


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_CURVE25519)

ret_code_t nrf_crypto_backend_cc310_curve25519_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key)
{
    ret_code_t  result;
    CRYSError_t crys_error;
    bool        mutex_locked;

    nrf_crypto_backend_cc310_curve25519_context_t * p_ctx =
        (nrf_crypto_backend_cc310_curve25519_context_t *)p_context;

    nrf_crypto_backend_curve25519_private_key_t * p_prv =
        (nrf_crypto_backend_curve25519_private_key_t *)p_private_key;

    nrf_crypto_backend_curve25519_public_key_t  * p_pub =
        (nrf_crypto_backend_curve25519_public_key_t *)p_public_key;

    size_t  pub_key_size = sizeof(p_pub->key);
    size_t  prv_key_size = sizeof(p_prv->key);

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    crys_error = CRYS_ECMONT_KeyPair(p_pub->key,
                                     &pub_key_size,
                                     p_prv->key,
                                     &prv_key_size,
                                     p_context,
                                     nrf_crypto_backend_cc310_rng,
                                     &p_ctx->temp_data);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);
    return result;
}


ret_code_t nrf_crypto_backend_cc310_curve25519_key_from_raw(
    void          * p_key,
    uint8_t const * p_raw_data)
{
    nrf_crypto_backend_curve25519_key_t * p_internal_key =
        (nrf_crypto_backend_curve25519_key_t *)p_key;

#if NRF_MODULE_ENABLED(NRF_CRYPTO_CURVE25519_BIG_ENDIAN)
    nrf_crypto_internal_swap_endian(p_internal_key->key, p_raw_data, sizeof(p_internal_key->key));
#else
    memcpy(p_internal_key->key, p_raw_data, sizeof(p_internal_key->key));
#endif

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_cc310_curve25519_key_to_raw(
    void const * p_key,
    uint8_t    * p_raw_data)
{
    nrf_crypto_backend_curve25519_key_t * p_internal_key =
        (nrf_crypto_backend_curve25519_key_t *)p_key;

#if NRF_MODULE_ENABLED(NRF_CRYPTO_CURVE25519_BIG_ENDIAN)
    nrf_crypto_internal_swap_endian(p_raw_data, p_internal_key->key, sizeof(p_internal_key->key));
#else
    memcpy(p_raw_data, p_internal_key->key, sizeof(p_internal_key->key));
#endif

    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_CURVE25519)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_ED25519)

ret_code_t nrf_crypto_backend_cc310_ed25519_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key)
{
    ret_code_t                   result;
    CRYSError_t                  crys_error;
    bool                         mutex_locked;

    nrf_crypto_backend_cc310_ed25519_context_t * p_ctx =
        (nrf_crypto_backend_cc310_ed25519_context_t *)p_context;

    nrf_crypto_backend_ed25519_private_key_t * p_prv =
        (nrf_crypto_backend_ed25519_private_key_t *)p_private_key;

    nrf_crypto_backend_ed25519_public_key_t  * p_pub =
        (nrf_crypto_backend_ed25519_public_key_t *)p_public_key;

    size_t                       pub_key_size = sizeof(p_pub->key);
    size_t                       prv_key_size = sizeof(p_prv->key);

    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    cc310_backend_enable();

    crys_error = CRYS_ECEDW_KeyPair(p_prv->key,
                                    &prv_key_size,
                                    p_pub->key,
                                    &pub_key_size,
                                    p_context,
                                    nrf_crypto_backend_cc310_rng,
                                    &p_ctx->temp_data);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);
    return result;
}


ret_code_t nrf_crypto_backend_cc310_ed25519_private_key_from_raw(
    void          * p_key,
    uint8_t const * p_raw_data)
{
    uint8_t                 pub_key_dummy[CRYS_ECEDW_ORD_SIZE_IN_BYTES]; // Throw away buffer
    CRYSError_t             crys_error;
    bool                    mutex_locked;
    ret_code_t              result;
    CRYS_ECEDW_TempBuff_t * p_temp_data = NULL;

    nrf_crypto_backend_ed25519_private_key_t * p_internal_prv_key =
        (nrf_crypto_backend_ed25519_private_key_t *)p_key;

    size_t                  prv_key_size = sizeof(p_internal_prv_key->key);
    size_t                  pub_key_size = sizeof(pub_key_dummy);
 
    // Generate public key using CRYS_ECEDW_SeedKeyPair
    mutex_locked = cc310_backend_mutex_trylock();
    VERIFY_TRUE(mutex_locked, NRF_ERROR_CRYPTO_BUSY);

    // Use memory allocation (instead of stack) for the temporary data, as it is ~700 bytes.
    p_temp_data = NRF_CRYPTO_ALLOC(sizeof(CRYS_ECEDW_TempBuff_t));
    if (p_temp_data == NULL)
    {
        return NRF_ERROR_CRYPTO_ALLOC_FAILED;
    }

    cc310_backend_enable();

    crys_error = CRYS_ECEDW_SeedKeyPair(p_raw_data,
                                        CRYS_ECEDW_ORD_SIZE_IN_BYTES,
                                        p_internal_prv_key->key,
                                        &prv_key_size,
                                        pub_key_dummy,
                                        &pub_key_size,
                                        p_temp_data);

    cc310_backend_disable();

    cc310_backend_mutex_unlock();

    NRF_CRYPTO_FREE(p_temp_data);

    result = nrf_crypto_backend_cc310_ecc_error_convert(crys_error);
    return result;
}


ret_code_t nrf_crypto_backend_cc310_ed25519_private_key_to_raw(
    void const * p_key,
    uint8_t    * p_raw_data)
{
    nrf_crypto_backend_ed25519_private_key_t * p_internal_key =
        (nrf_crypto_backend_ed25519_private_key_t *)p_key;

    memcpy(p_raw_data, p_internal_key->key, CRYS_ECEDW_ORD_SIZE_IN_BYTES);

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_cc310_ed25519_public_key_from_raw(
    void          * p_key,
    uint8_t const * p_raw_data)
{
    nrf_crypto_backend_ed25519_public_key_t * p_internal_key =
        (nrf_crypto_backend_ed25519_public_key_t *)p_key;

    memcpy(p_internal_key->key, p_raw_data, sizeof(p_internal_key->key));

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_cc310_ed25519_public_key_to_raw(
    void const * p_key,
    uint8_t    * p_raw_data)
{
    nrf_crypto_backend_ed25519_public_key_t * p_internal_key =
        (nrf_crypto_backend_ed25519_public_key_t *)p_key;

    memcpy(p_raw_data, p_internal_key->key, sizeof(p_internal_key->key));

    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_ed25519_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key)
{
    nrf_crypto_backend_ed25519_private_key_t * p_prv =
        (nrf_crypto_backend_ed25519_private_key_t *)p_private_key;

    nrf_crypto_backend_ed25519_public_key_t * p_pub =
        (nrf_crypto_backend_ed25519_public_key_t *)p_public_key;

    memcpy(p_pub->key, p_prv->key+CRYS_ECEDW_ORD_SIZE_IN_BYTES, CRYS_ECEDW_ORD_SIZE_IN_BYTES);

    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_ED25519)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp160r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_cc310_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_cc310_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP160R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP160R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP160R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)CRYS_ECPKI_DomainID_secp160r1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160R2)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp160r2_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_cc310_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_cc310_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP160R2_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP160R2_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP160R2_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)CRYS_ECPKI_DomainID_secp160r2,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP192R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp192r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_cc310_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_cc310_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP192R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP192R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP192R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)CRYS_ECPKI_DomainID_secp192r1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP224R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp224r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_cc310_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_cc310_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP224R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP224R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)CRYS_ECPKI_DomainID_secp224r1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP256R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp256r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_cc310_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_cc310_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP256R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)CRYS_ECPKI_DomainID_secp256r1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP384R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp384r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_cc310_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_cc310_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP384R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP384R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP384R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)CRYS_ECPKI_DomainID_secp384r1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP521R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp521r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_cc310_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_cc310_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP521R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP521R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP521R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)CRYS_ECPKI_DomainID_secp521r1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP160K1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp160k1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_cc310_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_cc310_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP160K1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP160K1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP160K1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)CRYS_ECPKI_DomainID_secp160k1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP192K1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp192k1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_cc310_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_cc310_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP192K1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP192K1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP192K1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)CRYS_ECPKI_DomainID_secp192k1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP224K1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp224k1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_cc310_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_cc310_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP224K1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP224K1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP224K1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)CRYS_ECPKI_DomainID_secp224k1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_SECP256K1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp256k1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_cc310_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_cc310_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP256K1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP256K1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP256K1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)CRYS_ECPKI_DomainID_secp256k1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_CURVE25519)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_curve25519_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_curve25519_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_curve25519_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_CURVE25519_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_CURVE25519_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_CURVE25519_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)CRYS_ECMONT_DOMAIN_CURVE_25519,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_ECC_ED25519)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_ed25519_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_ed25519_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_ed25519_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_ED25519_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_ED25519_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_ED25519_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = NULL,
};
#endif


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)
