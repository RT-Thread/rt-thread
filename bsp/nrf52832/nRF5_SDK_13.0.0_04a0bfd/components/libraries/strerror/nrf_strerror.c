/**
 * Copyright (c) 2011 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NRF_STRERROR)
#include "nrf_strerror.h"

/**
 * @brief Macro for adding an entity to the description array.
 *
 * Macro that helps to create a single entity in the description array.
 */
#define NRF_STRERROR_ENTITY(mnemonic) {.code = mnemonic, .name = #mnemonic}

/**
 * @brief Array entity element that describes an error.
 */
typedef struct
{
    ret_code_t   code; /**< Error code. */
    char const * name; /**< Descriptive name (the same as the internal error mnemonic). */
}nrf_strerror_desc_t;

/**
 * @brief Unknown error code.
 *
 * The constant string used by @ref nrf_strerror_get when the error description was not found.
 */
static char const m_unknown_str[] = "Unknown error code";

/**
 * @brief Array with error codes.
 *
 * Array that describes error codes.
 *
 * @note It is required for this array to have error codes placed in ascending order.
 *       This condition is checked in automatic unit test before the release.
 */
static nrf_strerror_desc_t const nrf_strerror_array[] =
{
    NRF_STRERROR_ENTITY(NRF_SUCCESS),
    NRF_STRERROR_ENTITY(NRF_ERROR_SVC_HANDLER_MISSING),
    NRF_STRERROR_ENTITY(NRF_ERROR_SOFTDEVICE_NOT_ENABLED),
    NRF_STRERROR_ENTITY(NRF_ERROR_INTERNAL),
    NRF_STRERROR_ENTITY(NRF_ERROR_NO_MEM),
    NRF_STRERROR_ENTITY(NRF_ERROR_NOT_FOUND),
    NRF_STRERROR_ENTITY(NRF_ERROR_NOT_SUPPORTED),
    NRF_STRERROR_ENTITY(NRF_ERROR_INVALID_PARAM),
    NRF_STRERROR_ENTITY(NRF_ERROR_INVALID_STATE),
    NRF_STRERROR_ENTITY(NRF_ERROR_INVALID_LENGTH),
    NRF_STRERROR_ENTITY(NRF_ERROR_INVALID_FLAGS),
    NRF_STRERROR_ENTITY(NRF_ERROR_INVALID_DATA),
    NRF_STRERROR_ENTITY(NRF_ERROR_DATA_SIZE),
    NRF_STRERROR_ENTITY(NRF_ERROR_TIMEOUT),
    NRF_STRERROR_ENTITY(NRF_ERROR_NULL),
    NRF_STRERROR_ENTITY(NRF_ERROR_FORBIDDEN),
    NRF_STRERROR_ENTITY(NRF_ERROR_INVALID_ADDR),
    NRF_STRERROR_ENTITY(NRF_ERROR_BUSY),

    /* SDK Common errors */
    NRF_STRERROR_ENTITY(NRF_ERROR_MODULE_NOT_INITIALZED),
    NRF_STRERROR_ENTITY(NRF_ERROR_MUTEX_INIT_FAILED),
    NRF_STRERROR_ENTITY(NRF_ERROR_MUTEX_LOCK_FAILED),
    NRF_STRERROR_ENTITY(NRF_ERROR_MUTEX_UNLOCK_FAILED),
    NRF_STRERROR_ENTITY(NRF_ERROR_MUTEX_COND_INIT_FAILED),
    NRF_STRERROR_ENTITY(NRF_ERROR_MODULE_ALREADY_INITIALIZED),
    NRF_STRERROR_ENTITY(NRF_ERROR_STORAGE_FULL),
    NRF_STRERROR_ENTITY(NRF_ERROR_API_NOT_IMPLEMENTED),
    NRF_STRERROR_ENTITY(NRF_ERROR_FEATURE_NOT_ENABLED),

    /* TWI error codes */
    NRF_STRERROR_ENTITY(NRF_ERROR_DRV_TWI_ERR_OVERRUN),
    NRF_STRERROR_ENTITY(NRF_ERROR_DRV_TWI_ERR_ANACK),
    NRF_STRERROR_ENTITY(NRF_ERROR_DRV_TWI_ERR_DNACK)
};


char const * nrf_strerror_get(ret_code_t code)
{
    char const * p_ret = nrf_strerror_find(code);
    return (p_ret == NULL) ? m_unknown_str : p_ret;
}

char const * nrf_strerror_find(ret_code_t code)
{
    nrf_strerror_desc_t const * p_start;
    nrf_strerror_desc_t const * p_end;
    p_start = nrf_strerror_array;
    p_end   = nrf_strerror_array + ARRAY_SIZE(nrf_strerror_array);

    while (p_start < p_end)
    {
        nrf_strerror_desc_t const * p_mid = p_start + ((p_end - p_start) / 2);
        ret_code_t mid_c = p_mid->code;
        if (mid_c > code)
        {
            p_end = p_mid;
        }
        else if (mid_c < code)
        {
            p_start = p_mid + 1;
        }
        else
        {
            return p_mid->name;
        }
    }
    return NULL;
}

#endif /* NRF_STRERROR enabled */
