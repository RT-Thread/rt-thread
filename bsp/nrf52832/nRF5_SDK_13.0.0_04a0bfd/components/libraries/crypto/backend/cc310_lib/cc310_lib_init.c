/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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

#if defined(NRF_CRYPTO_BACKEND_CC310_LIB) && (NRF_CRYPTO_BACKEND_CC310_LIB == 1)

#include "nrf_crypto_init.h"
#include "cc310_lib_init.h"
#include "cc310_lib_shared.h"
#include "crys_rnd.h"
#include "sns_silib.h"

// Temporary setting this before real handling of memory management
CRYS_RND_Context_t      g_rnd_context;

// Temporary setting this before real handling of memory management
CRYS_RND_WorkBuff_t     g_rnd_work_buffer;


/**@brief Pointer to contigious memory holding random number context data
 *
 * @note    The data pointed to must be available in the duration of the usage of Cryptocell api functions.
 */
CRYS_RND_Context_t    * gp_rnd_context          = &g_rnd_context;

/**@brief Pointer to contigious memory for the rnd initialization workspace
 *
 * @note    The Data pointed to must be available in the duration of the initialization of the Cryptocell
 *          or during reseeding of rng.
 */
CRYS_RND_WorkBuff_t * gp_rnd_work_buffer        = &g_rnd_work_buffer;

static uint32_t init_result_get(uint32_t crys_error)
{
    uint32_t ret_val = NRF_ERROR_INTERNAL;
    switch(crys_error)
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


static uint32_t uninit_result_get(uint32_t crys_error)
{
    uint32_t ret_val;

    switch(crys_error)
    {
        default:
            ret_val = NRF_ERROR_INTERNAL;
    }

    return ret_val;
}


uint32_t nrf_crypto_init(void)
{
    //nrf_crypto_init_info_h * p_init_info
    uint32_t                ret_val;
    CRYSError_t             crys_error;

    // Initialize the cryptocell by setting hardware register
    NRF_CRYPTOCELL->ENABLE = 1;

    // Initialize the CC310 run-time library
    crys_error = SaSi_LibInit(gp_rnd_context, gp_rnd_work_buffer);
    ret_val = init_result_get(crys_error);
    return ret_val;
}


uint32_t nrf_crypto_uninit(void)
{
    uint32_t        ret_val;
    CRYSError_t     crys_error;

    // Check that the library has been initialized. If not, exit.
    if (gp_rnd_context == NULL)
    {
        return NRF_SUCCESS;
    }

    crys_error = SaSi_LibFini(gp_rnd_context);

    // Set rnd context to zero to signal that the library is uninitialized
    gp_rnd_context = NULL;

    ret_val = uninit_result_get(crys_error);
    return ret_val;
}


bool nrf_crypto_is_initialized(void)
{
    return (gp_rnd_context != NULL);
}


#endif // NRF_CRYPTO_BACKEND_CC310_LIB

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)

