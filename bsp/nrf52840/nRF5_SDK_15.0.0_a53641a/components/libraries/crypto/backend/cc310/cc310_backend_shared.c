/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)

#include "nrf.h"
#include "cc310_backend_shared.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_rng.h"
#include "crys_rnd_error.h"
#include "nrf_crypto_shared.h"
#include "cc310_backend_shared.h"


static uint32_t m_use_count = 0;

void cc310_backend_enable(void)
{
    m_use_count++;

    if (m_use_count == 1)
    {
        // Enable the CryptoCell hardware
        NRF_CRYPTOCELL->ENABLE = 1;

        // Enable the CryptoCell IRQ
        NVIC_EnableIRQ(CRYPTOCELL_IRQn);
    }
}

void cc310_backend_disable(void)
{
    m_use_count--;

    // If no more users. Disable HW/IRQ
    if (m_use_count == 0)
    {
        // Disable the CryptoCell hardware
        NRF_CRYPTOCELL->ENABLE = 0;

        // Disable the CryptoCell IRQ
        NVIC_DisableIRQ(CRYPTOCELL_IRQn);
    }
}


uint32_t nrf_crypto_backend_cc310_rng(void * p_state, uint16_t size, uint8_t * p_data)
{
#if defined(NRF_CRYPTO_RNG_ENABLED) && (NRF_CRYPTO_RNG_ENABLED == 1)

    ret_code_t result = nrf_crypto_rng_vector_generate_no_mutex(p_data, (size_t)size);
    if (result == NRF_SUCCESS)
    {
        return CRYS_OK;
    }
    else if (result == NRF_ERROR_CRYPTO_CONTEXT_NOT_INITIALIZED)
    {
        return CRYS_RND_INSTANTIATION_NOT_DONE_ERROR;
    }
    else
    {
        return CRYS_RND_IS_NOT_SUPPORTED;
    }

#elif defined(NRF_CRYPTO_RNG_ENABLED) && (NRF_CRYPTO_RNG_ENABLED == 0)

    return NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;

#else

    #warning NRF_CRYPTO_RNG_ENABLED define not found in sdk_config.h (Is the sdk_config.h valid?).

#endif // NRF_CRYPTO_RNG_ENABLED
}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)
