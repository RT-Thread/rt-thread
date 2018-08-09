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

#include "sdk_config.h"
#include "nordic_common.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)

#include <stdbool.h>
#include <string.h>

#include "nrf_crypto_ecc.h"
#include "nrf_crypto_ecdh.h"
#include "nrf_crypto_mem.h"
#include "nrf_crypto_rng.h"
#include "nrf_assert.h"
#include "mbedtls_backend_ecc.h"

/*lint -save -e????*/
#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif
#include "mbedtls/ecp.h"
#include "mbedtls/bignum.h"
/*lint -restore*/


bool nrf_crypto_backend_mbedtls_ecc_group_load(
    mbedtls_ecp_group                        * p_group,
    struct nrf_crypto_ecc_curve_info_s const * p_info)
{
    int result;

    mbedtls_ecp_group_init(p_group);
    result = mbedtls_ecp_group_load(p_group,
                                    (mbedtls_ecp_group_id)(intptr_t)p_info->p_backend_data);

    if (result != 0)
    {
        return false;
    }
    return true;
}


int nrf_crypto_backend_mbedtls_ecc_mbedtls_rng(void * p_param, unsigned char * p_data, size_t size)
{
#if NRF_MODULE_ENABLED(NRF_CRYPTO_RNG)

    ret_code_t result;

    result = nrf_crypto_rng_vector_generate(p_data, size);

    if (result != NRF_SUCCESS)
    {
        return MBEDTLS_ERR_ECP_RANDOM_FAILED;
    }
    return 0;

#else
    return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
#endif
}


ret_code_t nrf_crypto_backend_mbedtls_key_pair_generate(
    void * p_context,
    void * p_private_key,
    void * p_public_key)
{
    int result;
    mbedtls_ecp_group group;

    nrf_crypto_backend_mbedtls_ecc_private_key_t * p_prv =
            (nrf_crypto_backend_mbedtls_ecc_private_key_t *)p_private_key;

    nrf_crypto_backend_mbedtls_ecc_public_key_t  * p_pub =
            (nrf_crypto_backend_mbedtls_ecc_public_key_t *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_pub->header.p_info;

    if (!nrf_crypto_backend_mbedtls_ecc_group_load(&group, p_info))
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    mbedtls_ecp_point_init(&p_pub->key);
    mbedtls_mpi_init(&p_prv->key);
    result = mbedtls_ecp_gen_keypair(&group,
                                     &p_prv->key,
                                     &p_pub->key,
                                     nrf_crypto_backend_mbedtls_ecc_mbedtls_rng,
                                     NULL);

    mbedtls_ecp_group_free(&group);

    if (result != 0)
    {
        mbedtls_mpi_free(&p_prv->key);
        mbedtls_ecp_point_free(&p_pub->key);
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_mbedtls_public_key_calculate(
    void       * p_context,
    void const * p_private_key,
    void       * p_public_key)
{
    int result;
    mbedtls_ecp_group group;

    nrf_crypto_backend_mbedtls_ecc_private_key_t const * p_prv =
            (nrf_crypto_backend_mbedtls_ecc_private_key_t const *)p_private_key;

    nrf_crypto_backend_mbedtls_ecc_public_key_t  * p_pub =
            (nrf_crypto_backend_mbedtls_ecc_public_key_t *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_pub->header.p_info;

    if (!nrf_crypto_backend_mbedtls_ecc_group_load(&group, p_info))
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    mbedtls_ecp_point_init(&p_pub->key);
    result = mbedtls_ecp_mul(&group,
                             &p_pub->key,
                             &p_prv->key,
                             &group.G,
                             nrf_crypto_backend_mbedtls_ecc_mbedtls_rng,
                             NULL);

    mbedtls_ecp_group_free(&group);

    if (result != 0)
    {
        mbedtls_ecp_point_free(&p_pub->key);
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_mbedtls_private_key_from_raw(
    void          * p_private_key,
    uint8_t const * p_raw_data)
{
    int result;
    mbedtls_ecp_group group;

    nrf_crypto_backend_mbedtls_ecc_private_key_t * p_prv =
            (nrf_crypto_backend_mbedtls_ecc_private_key_t *)p_private_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_prv->header.p_info;

    if (!nrf_crypto_backend_mbedtls_ecc_group_load(&group, p_info))
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    mbedtls_mpi_init(&p_prv->key);
    result = mbedtls_mpi_read_binary(&p_prv->key, p_raw_data, p_info->raw_private_key_size);

    if (result == 0)
    {
#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_CURVE25519)
        // Update bits in Curve25519 private key
        if (p_prv->header.p_info->curve_type == NRF_CRYPTO_ECC_CURVE25519_CURVE_TYPE)
        {
            result = mbedtls_mpi_set_bit(&p_prv->key, 0, 0);
            ASSERT(result == 0);
            result = mbedtls_mpi_set_bit(&p_prv->key, 1, 0);
            ASSERT(result == 0);
            result = mbedtls_mpi_set_bit(&p_prv->key, 2, 0);
            ASSERT(result == 0);
            result = mbedtls_mpi_set_bit(&p_prv->key, 254, 1);
            ASSERT(result == 0);
            result = mbedtls_mpi_set_bit(&p_prv->key, 255, 0);
            ASSERT(result == 0);
        }
#endif
        if (mbedtls_ecp_check_privkey(&group, &p_prv->key) != 0)
        {
            result = MBEDTLS_ERR_ECP_INVALID_KEY;
        }
    }

    mbedtls_ecp_group_free(&group);

    if (result != 0)
    {
        mbedtls_mpi_free(&p_prv->key);
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_mbedtls_private_key_to_raw(
    void    const * p_private_key,
    uint8_t       * p_raw_data)
{
    int result;

    nrf_crypto_backend_mbedtls_ecc_private_key_t const * p_prv =
            (nrf_crypto_backend_mbedtls_ecc_private_key_t const *)p_private_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_prv->header.p_info;

    result = mbedtls_mpi_write_binary(&p_prv->key, p_raw_data, p_info->raw_private_key_size);

    if (result != 0)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_mbedtls_public_key_from_raw(
    void          * p_public_key,
    uint8_t const * p_raw_data)
{
    int result;
    mbedtls_ecp_group group;

    nrf_crypto_backend_mbedtls_ecc_public_key_t * p_pub =
        (nrf_crypto_backend_mbedtls_ecc_public_key_t *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_pub->header.p_info;

    mbedtls_ecp_point_init(&p_pub->key);

    result = mbedtls_mpi_read_binary(&p_pub->key.X,
                                     p_raw_data,
                                     p_info->raw_private_key_size);
    if (result != 0)
    {
        goto error_exit;
    }

    if (p_info->raw_public_key_size > p_info->raw_private_key_size)
    {
        result = mbedtls_mpi_read_binary(&p_pub->key.Y,
                                         &p_raw_data[p_info->raw_private_key_size],
                                         p_info->raw_private_key_size);
    }

    if (result != 0)
    {
        goto error_exit;
    }

    result = mbedtls_mpi_lset(&p_pub->key.Z, 1);

    if (result == 0)
    {
        if (!nrf_crypto_backend_mbedtls_ecc_group_load(&group, p_info))
        {
            goto error_exit;
        }
        result = mbedtls_ecp_check_pubkey(&group, &p_pub->key);
        mbedtls_ecp_group_free(&group);
    }

    if (result != 0)
    {
        goto error_exit;
    }
    return NRF_SUCCESS;

error_exit:
    mbedtls_ecp_point_free(&p_pub->key);
    return NRF_ERROR_CRYPTO_INTERNAL;
}


ret_code_t nrf_crypto_backend_mbedtls_public_key_to_raw(
    void const * p_public_key,
    uint8_t    * p_raw_data)
{
    int result;

    nrf_crypto_backend_mbedtls_ecc_public_key_t const * p_pub =
        (nrf_crypto_backend_mbedtls_ecc_public_key_t const *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_pub->header.p_info;

    result = mbedtls_mpi_write_binary(&p_pub->key.X,
                                      p_raw_data,
                                      p_info->raw_private_key_size);
    if (result != 0)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    if (p_info->raw_public_key_size > p_info->raw_private_key_size)
    {
        result = mbedtls_mpi_write_binary(&p_pub->key.Y,
                                          &p_raw_data[p_info->raw_private_key_size],
                                          p_info->raw_private_key_size);
    }

    if (result != 0)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_backend_mbedtls_private_key_free(
    void * p_private_key)
{
    nrf_crypto_backend_mbedtls_ecc_private_key_t * p_prv =
            (nrf_crypto_backend_mbedtls_ecc_private_key_t *)p_private_key;

    mbedtls_mpi_free(&p_prv->key);
    return NRF_SUCCESS;
}

ret_code_t nrf_crypto_backend_mbedtls_public_key_free(
    void * p_public_key)
{
    nrf_crypto_backend_mbedtls_ecc_public_key_t * p_pub =
            (nrf_crypto_backend_mbedtls_ecc_public_key_t *)p_public_key;

    mbedtls_ecp_point_free(&p_pub->key);
    return NRF_SUCCESS;
}


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP192R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp192r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_mbedtls_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_mbedtls_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP192R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP192R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP192R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)MBEDTLS_ECP_DP_SECP192R1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP224R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp224r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_mbedtls_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_mbedtls_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP224R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP224R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP224R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)MBEDTLS_ECP_DP_SECP224R1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP256R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp256r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_mbedtls_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_mbedtls_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP256R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP256R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)MBEDTLS_ECP_DP_SECP256R1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP384R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp384r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_mbedtls_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_mbedtls_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP384R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP384R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP384R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)MBEDTLS_ECP_DP_SECP384R1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP521R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp521r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_mbedtls_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_mbedtls_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP521R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP521R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP521R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)MBEDTLS_ECP_DP_SECP521R1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP192K1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp192k1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_mbedtls_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_mbedtls_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP192K1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP192K1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP192K1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)MBEDTLS_ECP_DP_SECP192K1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP224K1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp224k1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_mbedtls_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_mbedtls_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP224K1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP224K1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP224K1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)MBEDTLS_ECP_DP_SECP224K1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_SECP256K1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_secp256k1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_mbedtls_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_mbedtls_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_SECP256K1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_SECP256K1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_SECP256K1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)MBEDTLS_ECP_DP_SECP256K1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_BP256R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_bp256r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_mbedtls_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_mbedtls_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_BP256R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_BP256R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_BP256R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)MBEDTLS_ECP_DP_BP256R1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_BP384R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_bp384r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_mbedtls_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_mbedtls_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_BP384R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_BP384R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_BP384R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)MBEDTLS_ECP_DP_BP384R1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_BP512R1)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_bp512r1_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_mbedtls_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_mbedtls_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_BP512R1_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_BP512R1_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_BP512R1_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)MBEDTLS_ECP_DP_BP512R1,
};
#endif


#if NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS_ECC_CURVE25519)
const nrf_crypto_ecc_curve_info_t g_nrf_crypto_ecc_curve25519_curve_info =
{
    .public_key_size      = sizeof(nrf_crypto_backend_mbedtls_ecc_public_key_t),
    .private_key_size     = sizeof(nrf_crypto_backend_mbedtls_ecc_private_key_t),
    .curve_type           = NRF_CRYPTO_ECC_CURVE25519_CURVE_TYPE,
    .raw_private_key_size = NRF_CRYPTO_ECC_CURVE25519_RAW_PRIVATE_KEY_SIZE,
    .raw_public_key_size  = NRF_CRYPTO_ECC_CURVE25519_RAW_PUBLIC_KEY_SIZE,
    .p_backend_data       = (void *)MBEDTLS_ECP_DP_CURVE25519,
};
#endif


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)
