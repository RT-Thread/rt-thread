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
/**@file
 *
 * @defgroup nrf_atomic Atomic operations API
 * @ingroup app_common
 * @{
 *
 * @brief @tagAPI52 This module implements C11 stdatomic.h simplified API.
          At this point only Cortex-M3/M4 cores are supported (LDREX/STREX instructions).
 *        Atomic types are limited to @ref nrf_atomic_u32_t and @ref nrf_atomic_flag_t.
 */

#ifndef NRF_ATOMIC_H__
#define NRF_ATOMIC_H__

#include "sdk_common.h"

/**
 * @brief Atomic 32 bit unsigned type
 * */
typedef volatile uint32_t nrf_atomic_u32_t;

/**
 * @brief Atomic 1 bit flag type (technically 32 bit)
 * */
typedef volatile uint32_t nrf_atomic_flag_t;



#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Stores value to an atomic object
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value to store
 *
 * @return Old value stored into atomic object
 * */
uint32_t nrf_atomic_u32_fetch_store(nrf_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Stores value to an atomic object
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value to store
 *
 * @return New value stored into atomic object
 * */
uint32_t nrf_atomic_u32_store(nrf_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Logical OR operation on an atomic object
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value of second operand OR operation
 *
 * @return Old value stored into atomic object
 * */
uint32_t nrf_atomic_u32_fetch_or(nrf_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Logical OR operation on an atomic object
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value of second operand OR operation
 *
 * @return New value stored into atomic object
 * */
uint32_t nrf_atomic_u32_or(nrf_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Logical AND operation on an atomic object
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value of second operand AND operation
 *
 * @return Old value stored into atomic object
 * */
uint32_t nrf_atomic_u32_fetch_and(nrf_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Logical AND operation on an atomic object
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value of second operand AND operation
 *
 * @return New value stored into atomic object
 * */
uint32_t nrf_atomic_u32_and(nrf_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Logical XOR operation on an atomic object
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value of second operand XOR operation
 *
 * @return Old value stored into atomic object
 * */
uint32_t nrf_atomic_u32_fetch_xor(nrf_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Logical XOR operation on an atomic object
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value of second operand XOR operation
 *
 * @return New value stored into atomic object
 * */
uint32_t nrf_atomic_u32_xor(nrf_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Arithmetic ADD operation on an atomic object
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value of second operand ADD operation
 *
 * @return Old value stored into atomic object
 * */
uint32_t nrf_atomic_u32_fetch_add(nrf_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Arithmetic ADD operation on an atomic object
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value of second operand ADD operation
 *
 * @return New value stored into atomic object
 * */
uint32_t nrf_atomic_u32_add(nrf_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Arithmetic SUB operation on an atomic object
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value of second operand SUB operation
 *
 * @return Old value stored into atomic object
 * */
uint32_t nrf_atomic_u32_fetch_sub(nrf_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Arithmetic SUB operation on an atomic object
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value of second operand SUB operation
 *
 * @return New value stored into atomic object
 * */
uint32_t nrf_atomic_u32_sub(nrf_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief If value at pointer is equal to expected value, changes value at pointer to desired
 *
 * Atomically compares the value pointed to by p_data with the value pointed to by p_expected,
 * and if those are equal, replaces the former with desired. Otherwise, loads the actual value
 * pointed to by p_data into *p_expected.
 *
 * @param p_data     Atomic memory pointer to test and modify.
 * @param p_expected Pointer to test value.
 * @param desired    Value to be stored to atomic memory.
 *
 * @retval true  *p_data was equal to *p_expected
 * @retval false *p_data was not equal to *p_expected
 */
bool nrf_atomic_u32_cmp_exch(nrf_atomic_u32_t * p_data,
                             uint32_t *         p_expected,
                             uint32_t           desired);

/**
 * @brief Arithmetic SUB operation on an atomic object performed if object >= value.
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value of second operand SUB operation
 *
 * @return Old value stored into atomic object
 * */
uint32_t nrf_atomic_u32_fetch_sub_hs(nrf_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Arithmetic SUB operation on an atomic object performed if object >= value.
 *
 * @param[in] p_data    Atomic memory pointer
 * @param[in] value     Value of second operand SUB operation
 *
 * @return New value stored into atomic object
 * */
uint32_t nrf_atomic_u32_sub_hs(nrf_atomic_u32_t * p_data, uint32_t value);

/**************************************************************************************************/

/**
 * @brief Logic one bit flag set operation on an atomic object
 *
 * @param[in] p_data    Atomic flag memory pointer
 *
 * @return Old flag value
 * */
uint32_t nrf_atomic_flag_set_fetch(nrf_atomic_flag_t * p_data);

/**
 * @brief Logic one bit flag set operation on an atomic object
 *
 * @param[in] p_data    Atomic flag memory pointer
 *
 * @return New flag value
 * */
uint32_t nrf_atomic_flag_set(nrf_atomic_flag_t * p_data);

/**
 * @brief Logic one bit flag clear operation on an atomic object
 *
 * @param[in] p_data    Atomic flag memory pointer
 *
 * @return Old flag value
 * */
uint32_t nrf_atomic_flag_clear_fetch(nrf_atomic_flag_t * p_data);

/**
 * @brief Logic one bit flag clear operation on an atomic object
 *
 * @param[in] p_data    Atomic flag memory pointer
 *
 * @return New flag value
 * */
uint32_t nrf_atomic_flag_clear(nrf_atomic_flag_t * p_data);

#ifdef __cplusplus
}
#endif

#endif /* NRF_ATOMIC_H__ */

/** @} */
