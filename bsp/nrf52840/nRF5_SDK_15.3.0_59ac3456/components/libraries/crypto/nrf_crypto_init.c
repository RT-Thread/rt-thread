/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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

#include "nrf_crypto_init.h"
#include "nrf_section.h"


// Create a named section for crypto backend data
NRF_SECTION_DEF(crypto_data, const nrf_crypto_backend_info_t);


#define NRF_CRYPTO_BACKEND_SECTION_ITEM_GET(i)      NRF_SECTION_ITEM_GET(crypto_data, nrf_crypto_backend_info_t, (i))
#define NRF_CRYPTO_BACKEND_SECTION_ITEM_COUNT       NRF_SECTION_ITEM_COUNT(crypto_data, nrf_crypto_backend_info_t)

typedef enum
{
    UNINITIALIZED,
    INITIALIZING,
    INITIALIZED,
} nrf_crypto_state_t;

static volatile nrf_crypto_state_t m_state = UNINITIALIZED;


ret_code_t nrf_crypto_init(void)
{
    ret_code_t      ret_val;
    size_t const    num_backends = NRF_CRYPTO_BACKEND_SECTION_ITEM_COUNT;

    m_state = INITIALIZING;

    // Iterate through each backends to call the init function
    for (size_t i = 0; i < num_backends; i++)
    {
        nrf_crypto_backend_info_t const * p_backend = NRF_CRYPTO_BACKEND_SECTION_ITEM_GET(i);
        ret_val = p_backend->init_fn();
        if (ret_val != NRF_SUCCESS)
        {
            return ret_val;
        }
    }

    // Set nrf_crypto to initialized
    m_state = INITIALIZED;
    return NRF_SUCCESS;
}


ret_code_t nrf_crypto_uninit(void)
{
    ret_code_t      ret_val;
    size_t const    num_backends = NRF_CRYPTO_BACKEND_SECTION_ITEM_COUNT;

    // Iterate through each backends to call the uninit function
    for (size_t i = 0; i < num_backends; i++)
    {
        nrf_crypto_backend_info_t const * p_backend = NRF_CRYPTO_BACKEND_SECTION_ITEM_GET(i);
        ret_val = p_backend->uninit_fn();
        if (ret_val != NRF_SUCCESS)
        {
            return ret_val;
        }
    }

    // Set nrf_crypto to uninitialized
    m_state = UNINITIALIZED;
    return NRF_SUCCESS;
}


bool nrf_crypto_is_initialized(void)
{
    return (m_state == INITIALIZED);
}


bool nrf_crypto_is_initializing(void)
{
    return ((m_state == INITIALIZED) || m_state == INITIALIZING);
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)
