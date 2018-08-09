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

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL)

#include "nrf.h"
#include "nrf_crypto_init.h"
#include "nrf_crypto_error.h"

#include "cc310_bl_backend_shared.h"
#include "cc310_backend_mutex.h"
#include "sns_silib.h"
#include "nrf_cc310_bl_init.h"

/**@brief Mutex to ensure single access to nrf_cc310_bl resources */
nrf_mtx_t g_cc310_mutex;

static uint32_t init_result_get(uint32_t crys_error)
{
    uint32_t ret_val = NRF_ERROR_INTERNAL;
    switch (crys_error)
    {
        case SA_SILIB_RET_OK:
            ret_val = NRF_SUCCESS;
            break;

        case SA_SILIB_RET_EINVAL_HW_VERSION:
            ret_val = NRF_ERROR_CRYPTO_FEATURE_UNAVAILABLE;
            break;

        default:
            ret_val = NRF_ERROR_INTERNAL;
            break;
    }

    return ret_val;
}


static ret_code_t cc310_bl_backend_init(void)
{
    uint32_t                ret_val;
    CRYSError_t             crys_error;

    cc310_backend_mutex_init();

    // Enable the CC310 HW.
    NRF_CRYPTOCELL->ENABLE = 1;

    // Initialize the CC310_BL run-time library
    crys_error = nrf_cc310_bl_init();

    // Disable the CC310 HW after initialization.
    NRF_CRYPTOCELL->ENABLE = 0;

    ret_val = init_result_get(crys_error);

    return ret_val;
}


static ret_code_t cc310_bl_backend_uninit(void)
{
    // Disable the CC310 HW.
    NRF_CRYPTOCELL->ENABLE = 0;

    return NRF_SUCCESS;
}


CRYPTO_BACKEND_REGISTER(nrf_crypto_backend_info_t const cc310_bl_backend) =
{
    .init_fn    = cc310_bl_backend_init,
    .uninit_fn  = cc310_bl_backend_uninit
};

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL)
