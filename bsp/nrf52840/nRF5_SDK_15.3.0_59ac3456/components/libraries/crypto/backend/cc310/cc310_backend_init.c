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
#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)

#include "nrf.h"
#include "nrf_crypto_init.h"
#include "cc310_backend_shared.h"
#include "sns_silib.h"
#include "cc310_backend_mutex.h"
#include "nrf_crypto_rng.h"

/**@internal @brief Function to enable CC310 (in HW)
 */
void cc310_backend_enable(void);


/**@internal @brief Function to disable CC310 (in HW)
 */
void cc310_backend_disable(void);

static uint32_t init_result_get(uint32_t crys_error)
{
    uint32_t ret_val = NRF_ERROR_INTERNAL;
    switch (crys_error)
    {
        case CRYS_OK:
            ret_val = NRF_SUCCESS;
            break;

        default:
            ret_val = NRF_ERROR_INTERNAL;
            break;
    }

    return ret_val;
}

static ret_code_t cc310_backend_init(void)
{
    uint32_t    ret_val;
    CRYSError_t crys_error;

    cc310_backend_mutex_init();

    // Enable the CC310 HW.
    NRF_CRYPTOCELL->ENABLE = 1;

    // Initialize the CC310 run-time library
    crys_error = SaSi_LibInit();

    // Shut down CC310 after initialization.
    NRF_CRYPTOCELL->ENABLE = 0;

    ret_val = init_result_get(crys_error);
    VERIFY_SUCCESS(ret_val);

#if defined(NRF_CRYPTO_RNG_AUTO_INIT_ENABLED) && (NRF_CRYPTO_RNG_AUTO_INIT_ENABLED == 1)

    ret_val = nrf_crypto_rng_init(NULL, NULL);
    VERIFY_SUCCESS(ret_val);

#elif defined(NRF_CRYPTO_RNG_AUTO_INIT_ENABLED) && (NRF_CRYPTO_RNG_AUTO_INIT_ENABLED == 0)

    // Do nothing

#else

    #warning NRF_CRYPTO_RNG_AUTO_INIT_ENABLED define not found in sdk_config.h (Is the sdk_config.h valid?).

#endif // NRF_CRYPTO_RNG_AUTO_INIT_ENABLED

    return ret_val;
}


static ret_code_t cc310_backend_uninit(void)
{
#if defined(NRF_CRYPTO_RNG_AUTO_INIT_ENABLED) && (NRF_CRYPTO_RNG_AUTO_INIT_ENABLED == 1)

    uint32_t ret_val;
    ret_val = nrf_crypto_rng_init(NULL, NULL);
    VERIFY_SUCCESS(ret_val);

#elif defined(NRF_CRYPTO_RNG_AUTO_INIT_ENABLED) && (NRF_CRYPTO_RNG_AUTO_INIT_ENABLED == 0)

    // Do nothing

#else

    #warning NRF_CRYPTO_RNG_AUTO_INIT_ENABLED define not found in sdk_config.h (Is the sdk_config.h valid?).

#endif // NRF_CRYPTO_RNG_AUTO_INIT_ENABLED

    // Initialize the CC310 HW to do shutdown.
    NRF_CRYPTOCELL->ENABLE = 1;

    SaSi_LibFini();

    // Shut down CC310 after shutdown.
    NRF_CRYPTOCELL->ENABLE = 0;

    return NRF_SUCCESS;
}


CRYPTO_BACKEND_REGISTER(nrf_crypto_backend_info_t const cc310_backend) =
{
    .init_fn    = cc310_backend_init,
    .uninit_fn  = cc310_backend_uninit,
};

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310)
