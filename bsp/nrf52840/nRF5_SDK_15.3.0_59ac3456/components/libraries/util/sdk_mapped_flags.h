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
#ifndef SDK_MAPPED_FLAGS_H__
#define SDK_MAPPED_FLAGS_H__

#include <stdint.h>
#include <stdbool.h>
#include "app_util.h"
#include "compiler_abstraction.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * @defgroup sdk_mapped_flags Mapped flags
 * @ingroup app_common
 * @{
 * @brief Module for writing and reading flags that are associated
 *        with keys.
 *
 * @details The flags are represented as bits in a bitmap called a <i>flag collection</i>. The keys
 *          are uint16_t. Each flag collection contains all flags of the same type, one flag for
 *          each key.
 *
 *          The mapped flags module does not keep the flag states, nor the list of keys. These are
 *          provided in the API calls. A key's index in the key list determines which bit in the
 *          flag collection is associated with it. This module does not ever edit the key list, and
 *          does not edit flags except in function calls that take the flag collection as a pointer.
 *
 */

#define SDK_MAPPED_FLAGS_N_KEYS          32      /**< The number of keys to keep flags for. This is also the number of flags in a flag collection. If changing this value, you might also need change the width of the sdk_mapped_flags_t type. */
#define SDK_MAPPED_FLAGS_N_KEYS_PER_BYTE 8       /**< The number of flags that fit in one byte. */
#define SDK_MAPPED_FLAGS_INVALID_INDEX   0xFFFF  /**< A flag index guaranteed to be invalid. */

typedef uint32_t sdk_mapped_flags_t; /**< The bitmap to hold flags. Each flag is one bit, and each bit represents the flag state associated with one key. */


/**@brief Type used to present a subset of the registered keys.
 */
typedef struct
{
    uint32_t len;                                 /**< The length of the list. */
    uint16_t flag_keys[SDK_MAPPED_FLAGS_N_KEYS];  /**< The list of keys. */
} sdk_mapped_flags_key_list_t;


/**@brief Function for getting the first index at which the flag is true in the provided
 *        collection.
 *
 * @param[in]  flags   The flag collection to search for a flag set to true.
 *
 * @return  The first index that has its flag set to true. If none were found, the
 *          function returns @ref SDK_MAPPED_FLAGS_INVALID_INDEX.
 */
uint16_t sdk_mapped_flags_first_key_index_get(sdk_mapped_flags_t flags);


/**@brief Function for updating the state of a flag.
 *
 * @param[in]  p_keys   The list of associated keys (assumed to have a length of
 *                      @ref SDK_MAPPED_FLAGS_N_KEYS).
 * @param[out] p_flags  The flag collection to modify.
 * @param[in]  key      The key to modify the flag of.
 * @param[in]  value    The state to set the flag to.
 */
void sdk_mapped_flags_update_by_key(uint16_t           * p_keys,
                                    sdk_mapped_flags_t * p_flags,
                                    uint16_t             key,
                                    bool                 value);


/**@brief Function for updating the state of the same flag in multiple flag collections.
 *
 * @details The key and value are the same for all flag collections in the p_flags array.
 *
 * @param[in]  p_keys              The list of associated keys (assumed to have a length of
 *                                 @ref SDK_MAPPED_FLAGS_N_KEYS).
 * @param[out] p_flags             The flag collections to modify.
 * @param[out] n_flag_collections  The number of flag collections in p_flags.
 * @param[in]  key                 The key to modify the flag of.
 * @param[in]  value               The state to set the flag to.
 */
void sdk_mapped_flags_bulk_update_by_key(uint16_t           * p_keys,
                                         sdk_mapped_flags_t * p_flags,
                                         uint32_t             n_flag_collections,
                                         uint16_t             key,
                                         bool                 value);


/**@brief Function for getting the state of a specific flag.
 *
 * @param[in]  p_keys  The list of associated keys (assumed to have a length of
 *                     @ref SDK_MAPPED_FLAGS_N_KEYS).
 * @param[in]  flags   The flag collection to read from.
 * @param[in]  key     The key to get the flag for.
 *
 * @return  The state of the flag.
 */
bool sdk_mapped_flags_get_by_key(uint16_t * p_keys, sdk_mapped_flags_t flags, uint16_t key);


/**@brief Function for getting the state of a specific flag.
 *
 * @param[in]  p_keys   The list of associated keys (assumed to have a length of
 *                      @ref SDK_MAPPED_FLAGS_N_KEYS).
 * @param[in]  flags    The flag collection from which to read.
 * @param[in]  key      The key for which to get the flag.
 * @param[out] p_index  If not NULL, the index of the key.
 *
 * @return  The state of the flag.
 */
bool sdk_mapped_flags_get_by_key_w_idx(uint16_t         * p_keys,
                                       sdk_mapped_flags_t flags,
                                       uint16_t           key,
                                       uint8_t          * p_index);


/**@brief Function for getting a list of all keys that have a specific flag set to true.
 *
 * @param[in]  p_keys  The list of associated keys (assumed to have a length of
 *                     @ref SDK_MAPPED_FLAGS_N_KEYS).
 * @param[in]  flags   The flag collection to search.
 *
 * @return  The list of keys.
 */
sdk_mapped_flags_key_list_t sdk_mapped_flags_key_list_get(uint16_t           * p_keys,
                                                          sdk_mapped_flags_t   flags);


/**@brief Function for getting the number of keys that have a specific flag set to true.
 *
 * @param[in]  flags  The flag collection to search.
 *
 * @return  The number of keys.
 */
uint32_t sdk_mapped_flags_n_flags_set(sdk_mapped_flags_t flags);


/**@brief Function for querying whether any flags in the collection are set.
 *
 * @param[in]  flags  The flag collection to query.
 *
 * @retval  true If one or more flags are set to true.
 * @retval  false Otherwise.
 */
static __INLINE bool sdk_mapped_flags_any_set(sdk_mapped_flags_t flags)
{
    return (flags != 0);
}


/** @} */


#ifdef __cplusplus
}
#endif

#endif /* SDK_MAPPED_FLAGS_H__ */
