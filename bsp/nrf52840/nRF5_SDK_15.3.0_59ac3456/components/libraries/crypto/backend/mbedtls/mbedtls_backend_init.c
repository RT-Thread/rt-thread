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

#include "sdk_common.h"
#include "sdk_config.h"

#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)

#include <string.h>
#include <stdint.h>
#include "nrf_crypto_init.h"
#include "nrf_crypto_mem.h"
/*lint -save -e????*/
#include "mbedtls/platform.h"
/*lint -restore*/


#if NRF_CRYPTO_ALLOC_ON_STACK
#error "MBED TLS backend does not support memory allocation on stack. Use different allocator."
#endif


/** @internal @brief Function to use NRF_CRYPTO_ALLOC for MBED TLS memory allocation.
 */
static void * mbedtls_backend_calloc(size_t count, size_t size)
{
    size_t total_size = count * size;
    void * p_data = NRF_CRYPTO_ALLOC(total_size);
    if (p_data != NULL)
    {
        memset(p_data, 0, total_size);
    }
    return p_data;
}


/** @internal @brief Function to use NRF_CRYPTO_FREE for MBED TLS memory deallocation.
 */
static void mbedtls_backend_free(void * p_data)
{
    NRF_CRYPTO_FREE(p_data);
}


/** @internal @brief Function to initialize MBED TLS backend - setup memory management for.
 */
static ret_code_t mbedtls_backend_init(void)
{
    (void)mbedtls_platform_set_calloc_free(mbedtls_backend_calloc, mbedtls_backend_free);
    return NRF_SUCCESS;
}


/** @internal @brief Function to uninitialize MBED TLS backend - currently no implementation is required.
 */
static ret_code_t mbedtls_backend_uninit(void)
{
    // Empty implementation
    return NRF_SUCCESS;
}


CRYPTO_BACKEND_REGISTER(nrf_crypto_backend_info_t const mbedtls_backend) =
{
    .init_fn    = mbedtls_backend_init,
    .uninit_fn  = mbedtls_backend_uninit,
};

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_MBEDTLS)
