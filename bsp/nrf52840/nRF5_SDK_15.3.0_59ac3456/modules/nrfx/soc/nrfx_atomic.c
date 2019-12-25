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
#include "nrfx_atomic.h"

#ifndef NRFX_ATOMIC_USE_BUILT_IN
    #define NRFX_ATOMIC_USE_BUILT_IN 0
#endif // NRFX_ATOMIC_USE_BUILT_IN

#if ((__CORTEX_M >= 0x03U) || (__CORTEX_SC >= 300U))
#define NRFX_ATOMIC_STREX_LDREX_PRESENT
#endif

#if (NRFX_ATOMIC_USE_BUILT_IN == 0) && defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
#include "nrfx_atomic_internal.h"
#endif

uint32_t nrfx_atomic_u32_fetch_store(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    return __atomic_exchange_n(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(mov, old_val, new_val, p_data, value);
    (void) new_val;
    return old_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    uint32_t old_val = *p_data;
    *p_data = value;
    NRFX_CRITICAL_SECTION_EXIT();
    return old_val;
#endif // NRFX_ATOMIC_USE_BUILT_IN
}

uint32_t nrfx_atomic_u32_store(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    __atomic_store_n(p_data, value, __ATOMIC_SEQ_CST);
    return value;
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(mov, old_val, new_val, p_data, value);
    (void) old_val;
    return new_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    *p_data = value;
    NRFX_CRITICAL_SECTION_EXIT();
    return value;
#endif //NRFX_ATOMIC_USE_BUILT_IN
}

uint32_t nrfx_atomic_u32_fetch_or(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    return __atomic_fetch_or(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(orr, old_val, new_val, p_data, value);
    (void) new_val;
    return old_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    uint32_t old_val = *p_data;
    *p_data |= value;
    NRFX_CRITICAL_SECTION_EXIT();
    return old_val;
#endif //NRFX_ATOMIC_USE_BUILT_IN
}

uint32_t nrfx_atomic_u32_or(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    return __atomic_or_fetch(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(orr, old_val, new_val, p_data, value);
    (void) old_val;
    return new_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    *p_data |= value;
    uint32_t new_value = *p_data;
    NRFX_CRITICAL_SECTION_EXIT();
    return new_value;
#endif //NRFX_ATOMIC_USE_BUILT_IN
}

uint32_t nrfx_atomic_u32_fetch_and(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    return __atomic_fetch_and(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(and, old_val, new_val, p_data, value);
    (void) new_val;
    return old_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    uint32_t old_val = *p_data;
    *p_data &= value;
    NRFX_CRITICAL_SECTION_EXIT();
    return old_val;
#endif //NRFX_ATOMIC_USE_BUILT_IN
}

uint32_t nrfx_atomic_u32_and(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    return __atomic_and_fetch(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(and, old_val, new_val, p_data, value);
    (void) old_val;
    return new_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    *p_data &= value;
    uint32_t new_value = *p_data;
    NRFX_CRITICAL_SECTION_EXIT();
    return new_value;
#endif //NRFX_ATOMIC_USE_BUILT_IN
}

uint32_t nrfx_atomic_u32_fetch_xor(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    return __atomic_fetch_xor(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(eor, old_val, new_val, p_data, value);
    (void) new_val;
    return old_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    uint32_t old_val = *p_data;
    *p_data ^= value;
    NRFX_CRITICAL_SECTION_EXIT();
    return old_val;
#endif //NRFX_ATOMIC_USE_BUILT_IN
}

uint32_t nrfx_atomic_u32_xor(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    return __atomic_xor_fetch(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(eor, old_val, new_val, p_data, value);
    (void) old_val;
    return new_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    *p_data ^= value;
    uint32_t new_value = *p_data;
    NRFX_CRITICAL_SECTION_EXIT();
    return new_value;
#endif //NRFX_ATOMIC_USE_BUILT_IN
}

uint32_t nrfx_atomic_u32_fetch_add(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    return __atomic_fetch_add(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(add, old_val, new_val, p_data, value);
    (void) new_val;
    return old_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    uint32_t old_val = *p_data;
    *p_data += value;
    NRFX_CRITICAL_SECTION_EXIT();
    return old_val;
#endif //NRFX_ATOMIC_USE_BUILT_IN
}

uint32_t nrfx_atomic_u32_add(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    return __atomic_add_fetch(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(add, old_val, new_val, p_data, value);
    (void) old_val;
    return new_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    *p_data += value;
    uint32_t new_value = *p_data;
    NRFX_CRITICAL_SECTION_EXIT();
    return new_value;
#endif //NRFX_ATOMIC_USE_BUILT_IN
}

uint32_t nrfx_atomic_u32_fetch_sub(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    return __atomic_fetch_sub(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(sub, old_val, new_val, p_data, value);
    (void) new_val;
    return old_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    uint32_t old_val = *p_data;
    *p_data -= value;
    NRFX_CRITICAL_SECTION_EXIT();
    return old_val;
#endif //NRFX_ATOMIC_USE_BUILT_IN
}

uint32_t nrfx_atomic_u32_sub(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    return __atomic_sub_fetch(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(sub, old_val, new_val, p_data, value);
    (void) old_val;
    return new_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    *p_data -= value;
    uint32_t new_value = *p_data;
    NRFX_CRITICAL_SECTION_EXIT();
    return new_value;
#endif //NRFX_ATOMIC_USE_BUILT_IN
}

bool nrfx_atomic_u32_cmp_exch(nrfx_atomic_u32_t * p_data,
                              uint32_t *          p_expected,
                              uint32_t            desired)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    return __atomic_compare_exchange(p_data,
                                     p_expected,
                                     &desired,
                                     1,
                                     __ATOMIC_SEQ_CST,
                                     __ATOMIC_SEQ_CST);
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    return nrfx_atomic_internal_cmp_exch(p_data, p_expected, desired);
#else
    bool result;
    NRFX_CRITICAL_SECTION_ENTER();
    if (*p_data == *p_expected)
    {
        *p_data = desired;
        result = true;
    }
    else
    {
        *p_expected = *p_data;
        result = false;
    }
    NRFX_CRITICAL_SECTION_EXIT();
    return result;
#endif
}

uint32_t nrfx_atomic_u32_fetch_sub_hs(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    uint32_t expected = *p_data;
    uint32_t new_val;
    do {
        if (expected >= value)
        {
            new_val = expected - value;
        }
        else
        {
            new_val = expected;
        }
    } while (!__atomic_compare_exchange(p_data, &expected, &new_val,
                                        1, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
    return expected;
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(sub_hs, old_val, new_val, p_data, value);
    (void) new_val;
    return old_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    uint32_t old_val = *p_data;
    *p_data -= value;
    NRFX_CRITICAL_SECTION_EXIT();
    return old_val;
#endif //NRFX_ATOMIC_USE_BUILT_IN
}

uint32_t nrfx_atomic_u32_sub_hs(nrfx_atomic_u32_t * p_data, uint32_t value)
{
#if NRFX_ATOMIC_USE_BUILT_IN
    uint32_t expected = *p_data;
    uint32_t new_val;
    do {
        if (expected >= value)
        {
            new_val = expected - value;
        }
        else
        {
            new_val = expected;
        }
    } while (!__atomic_compare_exchange(p_data, &expected, &new_val,
                                        1, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
    return new_val;
#elif defined(NRFX_ATOMIC_STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRFX_ATOMIC_OP(sub_hs, old_val, new_val, p_data, value);
    (void) old_val;
    return new_val;
#else
    NRFX_CRITICAL_SECTION_ENTER();
    *p_data -= value;
    uint32_t new_value = *p_data;
    NRFX_CRITICAL_SECTION_EXIT();
    return new_value;
#endif //NRFX_ATOMIC_USE_BUILT_IN
}

uint32_t nrfx_atomic_flag_set_fetch(nrfx_atomic_flag_t * p_data)
{
    return nrfx_atomic_u32_fetch_or(p_data, 1);
}

uint32_t nrfx_atomic_flag_set(nrfx_atomic_flag_t * p_data)
{
    return nrfx_atomic_u32_or(p_data, 1);
}

uint32_t nrfx_atomic_flag_clear_fetch(nrfx_atomic_flag_t * p_data)
{
    return nrfx_atomic_u32_fetch_and(p_data, 0);
}

uint32_t nrfx_atomic_flag_clear(nrfx_atomic_flag_t * p_data)
{
    return nrfx_atomic_u32_and(p_data, 0);
}
