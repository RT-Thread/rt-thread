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

#include "nrf.h"
#include "nrf_atomic.h"
#include "nrf_atflags.h"
#include "sdk_common.h"



/**@brief Macro for getting the index inside the flag array where a flag can be found.
 *
 * @param flag_index  Index of the flag.
 *
 * @return Index of the @ref nrf_atflags_t the flag can be found in.
 */
#define FLAG_BASE(flag_index) ((flag_index) / NRF_ATFLAGS_FLAGS_PER_ELEMENT)

/**@brief Macro for getting the mask representing the flag within the flag array member.
 *
 * @param flag_index  ID of the flag.
 *
 * @return Mask representing the flag within a single @ref nrf_atflags_t.
 */
#define FLAG_MASK(flag_index) (1UL << ((flag_index) % NRF_ATFLAGS_FLAGS_PER_ELEMENT))


void nrf_atflags_set(nrf_atflags_t * p_flags, uint32_t flag_index)
{
    uint32_t new_value = nrf_atomic_u32_or(&p_flags[FLAG_BASE(flag_index)], FLAG_MASK(flag_index));
    UNUSED_RETURN_VALUE(new_value);
}


bool nrf_atflags_fetch_set(nrf_atflags_t * p_flags, uint32_t flag_index)
{
    return (nrf_atomic_u32_fetch_or(&p_flags[FLAG_BASE(flag_index)], FLAG_MASK(flag_index))
            & FLAG_MASK(flag_index)) != 0;
}


void nrf_atflags_clear(nrf_atflags_t * p_flags, uint32_t flag_index)
{
    uint32_t new_value = nrf_atomic_u32_and(&p_flags[FLAG_BASE(flag_index)], ~FLAG_MASK(flag_index));
    UNUSED_RETURN_VALUE(new_value);
}


bool nrf_atflags_fetch_clear(nrf_atflags_t * p_flags, uint32_t flag_index)
{
    return (nrf_atomic_u32_fetch_and(&p_flags[FLAG_BASE(flag_index)], ~FLAG_MASK(flag_index))
            & FLAG_MASK(flag_index)) != 0;
}


bool nrf_atflags_get(nrf_atflags_t const * p_flags, uint32_t flag_index)
{
    return (p_flags[FLAG_BASE(flag_index)] & FLAG_MASK(flag_index)) != 0;
}


uint32_t nrf_atflags_init(nrf_atflags_t * p_flags, uint32_t flags_array_len, uint32_t flag_count)
{
    uint32_t required_flags_array_len = NRF_ATFLAGS_ARRAY_LEN(flag_count);

    if (required_flags_array_len <= flags_array_len)
    {
        for (uint32_t i = 0; i < required_flags_array_len; i++)
        {
            p_flags[i] = 0;
        }
        return required_flags_array_len;
    }
    return 0;
}

uint32_t nrf_atflags_find_and_set_flag(nrf_atflags_t * p_flags, uint32_t flag_count)
{
    for (uint32_t i = 0; i < NRF_ATFLAGS_ARRAY_LEN(flag_count); i++)
    {
        // Using __RBIT to make the order of flags more traditional.
        uint32_t first_zero = __CLZ(__RBIT(~p_flags[i]));
        while (first_zero < 32)
        {
            uint32_t first_zero_global = first_zero + (i * 32);
            if (first_zero_global >= flag_count)
            {
                break;
            }
            if (!nrf_atflags_fetch_set(p_flags, first_zero_global))
            {
                return first_zero_global;
            }
            first_zero = __CLZ(__RBIT(~p_flags[i]));
        }
    }

    return flag_count;
}

uint32_t nrf_atflags_find_and_clear_flag(nrf_atflags_t * p_flags, uint32_t flag_count)
{
    for (uint32_t i = 0; i < NRF_ATFLAGS_ARRAY_LEN(flag_count); i++)
    {
        // Using __RBIT to make the order of flags more traditional.
        uint32_t first_one = __CLZ(__RBIT(p_flags[i]));
        while (first_one < 32)
        {
            uint32_t first_one_global = first_one + (i * 32);
            if (first_one_global >= flag_count)
            {
                break;
            }
            if (nrf_atflags_fetch_clear(p_flags, first_one_global))
            {
                return first_one_global;
            }
            first_one = __CLZ(__RBIT(p_flags[i]));
        }
    }

    return flag_count;
}
