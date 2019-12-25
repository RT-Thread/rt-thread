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

#ifndef NRFX_ATOMIC_H__
#define NRFX_ATOMIC_H__

#include <nrfx.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrfx_atomic Atomic operations API
 * @ingroup nrfx
 * @{
 *
 * @brief This module implements C11 stdatomic.h simplified API.
 *
 * At this point, only Cortex-M3 and M4 cores are supported (LDREX/STREX instructions).
 * Atomic types are limited to @ref nrfx_atomic_u32_t and @ref nrfx_atomic_flag_t.
 */


/**
 * @brief Atomic 32-bit unsigned type.
 */
typedef volatile uint32_t nrfx_atomic_u32_t;

/**
 * @brief Atomic 1-bit flag type (technically 32-bit).
 */
typedef volatile uint32_t nrfx_atomic_flag_t;

/**
 * @brief Function for storing a value to an atomic object and returning its previous value.
 *
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value to store.
 *
 * @return Previous value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_fetch_store(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for storing a value to an atomic object and returning its new value.
 *
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value to store.
 *
 * @return New value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_store(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for running a logical OR operation on an atomic object
 *        and returning its previous value.
 *
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value of the second operand in the OR operation.
 *
 * @return Previous value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_fetch_or(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for running a logical OR operation on an atomic object
 *        and returning its new value.
 *
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value of the second operand in the OR operation.
 *
 * @return New value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_or(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for running a logical AND operation on an atomic object
 *        and returning its previous value.
 *
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value of the second operand in the AND operation.
 *
 * @return Previous value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_fetch_and(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for running a logical AND operation on an atomic object
 *        and returning its new value.
 *
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value of the second operand in the AND operation.
 *
 * @return New value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_and(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for running a logical XOR operation on an atomic object
 *        and returning its previous value.
 *
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value of the second operand in the XOR operation.
 *
 * @return Previous value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_fetch_xor(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for running a logical XOR operation on an atomic object
 *        and returning its new value.
 *
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value of the second operand in the XOR operation.
 *
 * @return New value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_xor(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for running an arithmetic ADD operation on an atomic object
 *        and returning its previous value.
 *
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value of the second operand in the ADD operation.
 *
 * @return Previous value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_fetch_add(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for running an arithmetic ADD operation on an atomic object
 *        and returning its new value.
 *
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value of the second operand in the ADD operation.
 *
 * @return New value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_add(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for running an arithmetic SUB operation on an atomic object
 *        and returning its previous value.
 *
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value of the second operand in the SUB operation.
 *
 * @return Old value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_fetch_sub(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for running an arithmetic SUB operation on an atomic object 
 *        and returning its new value.
 *
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value of the second operand in the SUB operation.
 *
 * @return New value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_sub(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for atomic conditional value replacement.
 *
 * Atomically compares the value pointed to by @p p_data with the value pointed to by @p p_expected.
 * If those are equal, replaces the former with desired. Otherwise, loads the actual value
 * pointed to by @p p_data into @p *p_expected.
 *
 * @param p_data     Atomic memory pointer to test and modify.
 * @param p_expected Pointer to the test value.
 * @param desired    Value to be stored to atomic memory.
 *
 * @retval true  @p *p_data was equal to @p *p_expected.
 * @retval false @p *p_data was not equal to @p *p_expected.
 */
bool nrfx_atomic_u32_cmp_exch(nrfx_atomic_u32_t * p_data,
                              uint32_t *         p_expected,
                              uint32_t           desired);

/**
 * @brief Function for running an arithmetic SUB operation on an atomic object
 *        if object >= value, and returning its previous value.
 *        
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value of the second operand in the SUB operation.
 *
 * @return Previous value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_fetch_sub_hs(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for running an arithmetic SUB operation on an atomic object 
 *        if object >= value, and returning its new value.
 *
 * @param[in] p_data    Atomic memory pointer.
 * @param[in] value     Value of the second operand in the SUB operation.
 *
 * @return New value stored in the atomic object.
 */
uint32_t nrfx_atomic_u32_sub_hs(nrfx_atomic_u32_t * p_data, uint32_t value);

/**
 * @brief Function for running a logical one bit flag set operation 
 *        on an atomic object and returning its previous value.
 *
 * @param[in] p_data    Atomic flag memory pointer.
 *
 * @return Previous flag value.
 */
uint32_t nrfx_atomic_flag_set_fetch(nrfx_atomic_flag_t * p_data);

/**
 * @brief Function for running a logical one bit flag set operation 
 *        on an atomic object and returning its new value.
 *
 * @param[in] p_data    Atomic flag memory pointer.
 *
 * @return New flag value.
 */
uint32_t nrfx_atomic_flag_set(nrfx_atomic_flag_t * p_data);

/**
 * @brief Function for running a logical one bit flag clear operation 
 *        on an atomic object and returning its previous value.
 *
 * @param[in] p_data    Atomic flag memory pointer.
 *
 * @return Previous flag value.
 */
uint32_t nrfx_atomic_flag_clear_fetch(nrfx_atomic_flag_t * p_data);

/**
 * @brief Function for running a logical one bit flag clear operation 
 *        on an atomic object and returning its new value.
 *
 * @param[in] p_data    Atomic flag memory pointer.
 *
 * @return New flag value.
 */
uint32_t nrfx_atomic_flag_clear(nrfx_atomic_flag_t * p_data);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRFX_ATOMIC_H__
