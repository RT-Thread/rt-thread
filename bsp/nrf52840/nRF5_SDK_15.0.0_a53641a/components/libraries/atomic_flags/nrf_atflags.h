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
/**@file
 *
 * @defgroup nrf_atflags Atomic flags (bitmaps)
 * @ingroup app_common
 * @{
 *
 * @brief @tagAPI52 This module implements atomic flags as bitmaps.
 *
 * Operations on the individual flags are atomic, meaning that you are always sure that the flag is
 * set to the desired value, and you always know what value was there before. You also know that no
 * other flags were affected by the operation.
 *
 * Operations on the entire flag collection are NOT atomic. This essentially means that you can't
 * know the order in which operations on different flags happened, and you can't know the state of
 * the entire flag collection at any instant. These limitations can be overcome by protecting
 * operations with a mutex.
 */

#ifndef NRF_ATFLAGS_H__
#define NRF_ATFLAGS_H__


/**
 * @brief Array of atomic flags.
 * */
typedef volatile uint32_t nrf_atflags_t;


/**
 * @brief Number of flags per @ref nrf_atflags_t.
 * */
#define NRF_ATFLAGS_FLAGS_PER_ELEMENT (sizeof(nrf_atflags_t) * 8)

/**@brief Macro for the length of an array of @ref nrf_atflags_t needed to keep \p flag_count flags.
 *
 * @param flag_count  Number of flags to keep in a flag array.
 *
 * @return Length of the array needed to house flag_count flags.
 */
#define NRF_ATFLAGS_ARRAY_LEN(flag_count) ((flag_count - 1) / NRF_ATFLAGS_FLAGS_PER_ELEMENT) + 1

/**@brief Macro for declaring a flag array with the right size and initial value.
 *
 * @note When using this macro, no call to @ref nrf_atflags_init is necessary for this array.
 *
 * @param _name    Name to be given to the array.
 * @param flag_count  Number of flags to be kept in the flag array.
 *
 * @return Flag array definition.
 */
#define NRF_ATFLAGS_DEF(_name, flag_count) \
    nrf_atflags_t _name[NRF_ATFLAGS_ARRAY_LEN((flag_count))] = {0}

/**@brief Macro for declaring a flag array with the right size as a member of a struct.
 *
 * @note When using this macro, make sure to set the array to 0 or use @ref nrf_atflags_init
 *
 * @param _name    Name to be given to the array.
 * @param flag_count  Number of flags to be kept in the flag array.
 *
 * @return Flag array definition.
 */
#define NRF_ATFLAGS_DEF_MEMBER(_name, flag_count) \
    nrf_atflags_t _name[NRF_ATFLAGS_ARRAY_LEN((flag_count))]


/**@brief Function for safely initializing a flag array to 0.
 *
 * @param p_flags          Flag array to initialize.
 * @param flags_array_len  Length of \p p_flags.
 * @param flag_count          Number of flags to be kept in the flag array.
 *
 * @retval  0 if the given length is not sufficient to house \p flag_count flags in the array.
 * @return  If successful: The actual length required.
 */
uint32_t nrf_atflags_init(nrf_atflags_t * p_flags, uint32_t flags_array_len, uint32_t flag_count);

/**@brief Function for atomically setting a flag to 1.
 *
 * @param[in] p_flags     Atomic flag array.
 * @param[in] flag_index  Index of the flag in the array.
 */
void nrf_atflags_set(nrf_atflags_t * p_flags, uint32_t flag_index);

/**@brief Function for atomically setting a flag to 1, returning the previous value of the flag.
 *
 * @param[in] p_flags     Atomic flag array.
 * @param[in] flag_index  Index of the flag in the array.
 *
 * @return Old flag value.
 */
bool nrf_atflags_fetch_set(nrf_atflags_t * p_flags, uint32_t flag_index);

/**@brief Function for atomically setting a flag to 0.
 *
 * @param[in] p_flags     Atomic flag array.
 * @param[in] flag_index  Index of the flag in the array.
 */
void nrf_atflags_clear(nrf_atflags_t * p_flags, uint32_t flag_index);

/**@brief Function for atomically setting a flag to 0, returning the previous value of the flag.
 *
 * @param[in] p_flags     Atomic flag array.
 * @param[in] flag_index  Index of the flag in the array.
 *
 * @return Old flag value.
 */
bool nrf_atflags_fetch_clear(nrf_atflags_t * p_flags, uint32_t flag_index);

/**@brief Function for getting the value of a flag in a flag array.
 *
 * @param[in] p_flags     Atomic flag array.
 * @param[in] flag_index  Index of the flag in the array.
 *
 * @return Flag value.
 */
bool nrf_atflags_get(nrf_atflags_t const * p_flags, uint32_t flag_index);

/**@brief Function for finding a flag with value 0, and atomically setting it to one.
 *
 * @param[in] p_flags  Atomic flag array.
 * @param[in] flag_count  Number of flags in the array.
 *
 * @return Index of the cleared flag that has been set.
 */
uint32_t nrf_atflags_find_and_set_flag(nrf_atflags_t * p_flags, uint32_t flag_count);

/**@brief Function for finding a flag with value 1, and atomically clearing it to 0.
 *
 * @param[in] p_flags  Atomic flag array.
 * @param[in] flag_count  The number of flags in the array.
 *
 * @return The index of the set flag that has been cleared.
 */
uint32_t nrf_atflags_find_and_clear_flag(nrf_atflags_t * p_flags, uint32_t flag_count);


#ifdef __cplusplus
}
#endif

#endif /* NRF_ATFLAGS_H__ */

/** @} */
