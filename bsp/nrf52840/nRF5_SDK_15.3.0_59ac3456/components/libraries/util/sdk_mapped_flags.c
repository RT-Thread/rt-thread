/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#include "sdk_mapped_flags.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "compiler_abstraction.h"


// Test whether the flag collection type is large enough to hold all the flags. If this fails,
// reduce SDK_MAPPED_FLAGS_N_KEYS or increase the size of sdk_mapped_flags_t.
STATIC_ASSERT((sizeof(sdk_mapped_flags_t) * SDK_MAPPED_FLAGS_N_KEYS_PER_BYTE) >= SDK_MAPPED_FLAGS_N_KEYS);


/**@brief Function for setting the state of a flag to true.
 *
 * @note This function does not check whether the index is valid.
 *
 * @param[in]  p_flags  The collection of flags to modify.
 * @param[in]  index    The index of the flag to modify.
 */
static __INLINE void sdk_mapped_flags_set_by_index(sdk_mapped_flags_t * p_flags, uint16_t index)
{
    *p_flags |= (1U << index);
}


/**@brief Function for setting the state of a flag to false.
 *
 * @note This function does not check whether the index is valid.
 *
 * @param[in]  p_flags  The collection of flags to modify.
 * @param[in]  index    The index of the flag to modify.
 */
static __INLINE void sdk_mapped_flags_clear_by_index(sdk_mapped_flags_t * p_flags, uint16_t index)
{
    *p_flags &= ~(1U << index);
}


/**@brief Function for getting the state of a flag.
 *
 * @note This function does not check whether the index is valid.
 *
 * @param[in]  p_flags  The collection of flags to read.
 * @param[in]  index    The index of the flag to get.
 */
static __INLINE bool sdk_mapped_flags_get_by_index(sdk_mapped_flags_t flags, uint16_t index)
{
    return ((flags & (1 << index)) != 0);
}



uint16_t sdk_mapped_flags_first_key_index_get(sdk_mapped_flags_t flags)
{
    for (uint16_t i = 0; i < SDK_MAPPED_FLAGS_N_KEYS; i++)
    {
        if (sdk_mapped_flags_get_by_index(flags, i))
        {
            return i;
        }
    }
    return SDK_MAPPED_FLAGS_INVALID_INDEX;
}


void sdk_mapped_flags_update_by_key(uint16_t           * p_keys,
                                    sdk_mapped_flags_t * p_flags,
                                    uint16_t             key,
                                    bool                 value)
{
    sdk_mapped_flags_bulk_update_by_key(p_keys, p_flags, 1, key, value);
}


void sdk_mapped_flags_bulk_update_by_key(uint16_t           * p_keys,
                                         sdk_mapped_flags_t * p_flags,
                                         uint32_t             n_flag_collections,
                                         uint16_t             key,
                                         bool                 value)
{
    if ((p_keys != NULL) && (p_flags != NULL) && (n_flag_collections > 0))
    {
        for (uint32_t i = 0; i < SDK_MAPPED_FLAGS_N_KEYS; i++)
        {
            if (p_keys[i] == key)
            {
                for (uint32_t j = 0; j < n_flag_collections; j++)
                {
                    if (value)
                    {
                        sdk_mapped_flags_set_by_index(&p_flags[j], i);
                    }
                    else
                    {
                        sdk_mapped_flags_clear_by_index(&p_flags[j], i);
                    }
                }
                return;
            }
        }
    }
}


bool sdk_mapped_flags_get_by_key_w_idx(uint16_t         * p_keys,
                                       sdk_mapped_flags_t flags,
                                       uint16_t           key,
                                       uint8_t          * p_index)
{
    if (p_keys != NULL)
    {
        for (uint32_t i = 0; i < SDK_MAPPED_FLAGS_N_KEYS; i++)
        {
            if (p_keys[i] == key)
            {
                if (p_index != NULL)
                {
                    *p_index = i;
                }
                return sdk_mapped_flags_get_by_index(flags, i);
            }
        }
    }
    if (p_index != NULL)
    {
        *p_index = SDK_MAPPED_FLAGS_N_KEYS;
    }
    return false;
}


bool sdk_mapped_flags_get_by_key(uint16_t * p_keys, sdk_mapped_flags_t flags, uint16_t key)
{
    if (p_keys != NULL)
    {
        for (uint32_t i = 0; i < SDK_MAPPED_FLAGS_N_KEYS; i++)
        {
            if (p_keys[i] == key)
            {
                return sdk_mapped_flags_get_by_index(flags, i);
            }
        }
    }
    return false;
}


sdk_mapped_flags_key_list_t sdk_mapped_flags_key_list_get(uint16_t           * p_keys,
                                                          sdk_mapped_flags_t   flags)
{
    sdk_mapped_flags_key_list_t key_list;
    key_list.len = 0;

    if (p_keys != NULL)
    {
        for (uint32_t i = 0; i < SDK_MAPPED_FLAGS_N_KEYS; i++)
        {
            if (sdk_mapped_flags_get_by_index(flags, i))
            {
                key_list.flag_keys[key_list.len++] = p_keys[i];
            }
        }
    }

    return key_list;
}


uint32_t sdk_mapped_flags_n_flags_set(sdk_mapped_flags_t flags)
{
    uint32_t n_flags_set = 0;

    for (uint32_t i = 0; i < SDK_MAPPED_FLAGS_N_KEYS; i++)
    {
        if (sdk_mapped_flags_get_by_index(flags, i))
        {
            n_flags_set += 1;
        }
    }
    return n_flags_set;
}
