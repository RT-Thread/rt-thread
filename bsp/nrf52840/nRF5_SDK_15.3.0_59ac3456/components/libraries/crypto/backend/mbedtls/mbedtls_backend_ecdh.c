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

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)

#include <string.h>

#include "nrf_crypto_ecc_shared.h"
#include "nrf_crypto_ecdh_shared.h"
#include "nrf_crypto_shared.h"
#include "nrf_crypto_ecdh.h"

/*lint -save -e????*/
#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif
#include "mbedtls/ecp.h"
#include "mbedtls/ecdh.h"
/*lint -restore*/


ret_code_t nrf_crypto_backend_mbedtls_ecdh_compute(
    void       * p_context,
    void const * p_private_key,
    void const * p_public_key,
    uint8_t    * p_shared_secret)
{
    int               result;
    mbedtls_mpi       shared_secret_mpi;
    mbedtls_ecp_group group;

    nrf_crypto_backend_mbedtls_ecc_private_key_t const * p_prv =
            (nrf_crypto_backend_mbedtls_ecc_private_key_t const *)p_private_key;

    nrf_crypto_backend_mbedtls_ecc_public_key_t  const * p_pub =
            (nrf_crypto_backend_mbedtls_ecc_public_key_t const *)p_public_key;

    nrf_crypto_ecc_curve_info_t const * p_info = p_prv->header.p_info;

    if (!nrf_crypto_backend_mbedtls_ecc_group_load(&group, p_info))
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    mbedtls_mpi_init(&shared_secret_mpi);
    result = mbedtls_ecdh_compute_shared(&group,
                                         &shared_secret_mpi,
                                         &p_pub->key,
                                         &p_prv->key,
                                         nrf_crypto_backend_mbedtls_ecc_mbedtls_rng,
                                         NULL);

    if (result == 0)
    {
        result = mbedtls_mpi_write_binary(&shared_secret_mpi,
                                          p_shared_secret,
                                          p_info->raw_private_key_size);
    }

#if NRF_CRYPTO_ECC_CURVE25519_ENABLED && !NRF_MODULE_ENABLED(NRF_CRYPTO_CURVE25519_BIG_ENDIAN)

    if (p_info == &g_nrf_crypto_ecc_curve25519_curve_info)
    {
        nrf_crypto_internal_swap_endian_in_place(p_shared_secret,
                                                 NRF_CRYPTO_ECDH_CURVE25519_SHARED_SECRET_SIZE);
    }

#endif

    mbedtls_mpi_free(&shared_secret_mpi);
    mbedtls_ecp_group_free(&group);

    if (result != 0)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    return NRF_SUCCESS;
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)

