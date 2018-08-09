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
#include "nrf_atomic.h"

#ifndef NRF_ATOMIC_USE_BUILD_IN
#if (defined(__GNUC__) && defined(WIN32))
    #define NRF_ATOMIC_USE_BUILD_IN 1
#else
    #define NRF_ATOMIC_USE_BUILD_IN 0
#endif
#endif // NRF_ATOMIC_USE_BUILD_IN

#if ((__CORTEX_M >= 0x03U) || (__CORTEX_SC >= 300U))
#define STREX_LDREX_PRESENT
#else
#include "app_util_platform.h"
#endif


#if (NRF_ATOMIC_USE_BUILD_IN == 0) && defined(STREX_LDREX_PRESENT)
#include "nrf_atomic_internal.h"
#endif

uint32_t nrf_atomic_u32_fetch_store(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    return __atomic_exchange_n(p_data, value, __ATOMIC_SEQ_CST);

#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;
    NRF_ATOMIC_OP(mov, old_val, new_val, p_data, value);

    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return old_val;
#else
    CRITICAL_REGION_ENTER();
    uint32_t old_val = *p_data;
    *p_data = value;
    CRITICAL_REGION_EXIT();
    return old_val;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

uint32_t nrf_atomic_u32_store(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    __atomic_store_n(p_data, value, __ATOMIC_SEQ_CST);
    return value;
#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;

    NRF_ATOMIC_OP(mov, old_val, new_val, p_data, value);

    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return new_val;
#else
    CRITICAL_REGION_ENTER();
    *p_data = value;
    CRITICAL_REGION_EXIT();
    return value;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

uint32_t nrf_atomic_u32_fetch_or(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    return __atomic_fetch_or(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;

    NRF_ATOMIC_OP(orr, old_val, new_val, p_data, value);
    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return old_val;
#else
    CRITICAL_REGION_ENTER();
    uint32_t old_val = *p_data;
    *p_data |= value;
    CRITICAL_REGION_EXIT();
    return old_val;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

uint32_t nrf_atomic_u32_or(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    return __atomic_or_fetch(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;

    NRF_ATOMIC_OP(orr, old_val, new_val, p_data, value);
    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return new_val;
#else
    CRITICAL_REGION_ENTER();
    *p_data |= value;
    uint32_t new_value = *p_data;
    CRITICAL_REGION_EXIT();
    return new_value;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

uint32_t nrf_atomic_u32_fetch_and(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    return __atomic_fetch_and(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;

    NRF_ATOMIC_OP(and, old_val, new_val, p_data, value);
    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return old_val;
#else
    CRITICAL_REGION_ENTER();
    uint32_t old_val = *p_data;
    *p_data &= value;
    CRITICAL_REGION_EXIT();
    return old_val;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

uint32_t nrf_atomic_u32_and(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    return __atomic_and_fetch(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;

    NRF_ATOMIC_OP(and, old_val, new_val, p_data, value);
    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return new_val;
#else
    CRITICAL_REGION_ENTER();
    *p_data &= value;
    uint32_t new_value = *p_data;
    CRITICAL_REGION_EXIT();
    return new_value;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

uint32_t nrf_atomic_u32_fetch_xor(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    return __atomic_fetch_xor(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;

    NRF_ATOMIC_OP(eor, old_val, new_val, p_data, value);
    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return old_val;
#else
    CRITICAL_REGION_ENTER();
    uint32_t old_val = *p_data;
    *p_data ^= value;
    CRITICAL_REGION_EXIT();
    return old_val;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

uint32_t nrf_atomic_u32_xor(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    return __atomic_xor_fetch(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;

    NRF_ATOMIC_OP(eor, old_val, new_val, p_data, value);
    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return new_val;
#else
    CRITICAL_REGION_ENTER();
    *p_data ^= value;
    uint32_t new_value = *p_data;
    CRITICAL_REGION_EXIT();
    return new_value;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

uint32_t nrf_atomic_u32_fetch_add(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    return __atomic_fetch_add(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;

    NRF_ATOMIC_OP(add, old_val, new_val, p_data, value);
    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return old_val;
#else
    CRITICAL_REGION_ENTER();
    uint32_t old_val = *p_data;
    *p_data += value;
    CRITICAL_REGION_EXIT();
    return old_val;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

uint32_t nrf_atomic_u32_add(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    return __atomic_add_fetch(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;

    NRF_ATOMIC_OP(add, old_val, new_val, p_data, value);
    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return new_val;
#else
    CRITICAL_REGION_ENTER();
    *p_data += value;
    uint32_t new_value = *p_data;
    CRITICAL_REGION_EXIT();
    return new_value;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

uint32_t nrf_atomic_u32_fetch_sub(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    return __atomic_fetch_sub(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;

    NRF_ATOMIC_OP(sub, old_val, new_val, p_data, value);
    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return old_val;
#else
    CRITICAL_REGION_ENTER();
    uint32_t old_val = *p_data;
    *p_data -= value;
    CRITICAL_REGION_EXIT();
    return old_val;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

uint32_t nrf_atomic_u32_sub(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    return __atomic_sub_fetch(p_data, value, __ATOMIC_SEQ_CST);
#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;

    NRF_ATOMIC_OP(sub, old_val, new_val, p_data, value);
    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return new_val;
#else
    CRITICAL_REGION_ENTER();
    *p_data -= value;
    uint32_t new_value = *p_data;
    CRITICAL_REGION_EXIT();
    return new_value;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

bool nrf_atomic_u32_cmp_exch(nrf_atomic_u32_t * p_data,
                                           uint32_t *         p_expected,
                                           uint32_t           desired)
{
#if NRF_ATOMIC_USE_BUILD_IN
    return __atomic_compare_exchange(p_data,
                                     p_expected,
                                     &desired,
                                     1,
                                     __ATOMIC_SEQ_CST,
                                     __ATOMIC_SEQ_CST);
#elif defined(STREX_LDREX_PRESENT)
    return nrf_atomic_internal_cmp_exch(p_data, p_expected, desired);
#else
    CRITICAL_REGION_ENTER();
    if(*p_data == *p_expected)
    {
        *p_data = desired;
        return true;
    }
    else
    {
        *p_expected = *p_data;
        return false;
    }
    CRITICAL_REGION_EXIT();
#endif
}

uint32_t nrf_atomic_u32_fetch_sub_hs(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    uint32_t expected = *p_data;
    uint32_t new_val;
    bool     success;

    do
    {
        if (expected >= value)
        {
            new_val = expected - value;
        }
        else
        {
            new_val = expected;
        }
        success = __atomic_compare_exchange(p_data,
                                            &expected,
                                            &new_val,
                                            1,
                                            __ATOMIC_SEQ_CST,
                                            __ATOMIC_SEQ_CST);
    } while(!success);
    return expected;
#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;

    NRF_ATOMIC_OP(sub_hs, old_val, new_val, p_data, value);
    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return old_val;
#else
    CRITICAL_REGION_ENTER();
    uint32_t old_val = *p_data;
    *p_data -= value;
    CRITICAL_REGION_EXIT();
    return old_val;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

uint32_t nrf_atomic_u32_sub_hs(nrf_atomic_u32_t * p_data, uint32_t value)
{
#if NRF_ATOMIC_USE_BUILD_IN
    uint32_t expected = *p_data;
    uint32_t new_val;
    bool     success;

    do
    {
        if (expected >= value)
        {
            new_val = expected - value;
        }
        else
        {
            new_val = expected;
        }
        success = __atomic_compare_exchange(p_data,
                                            &expected,
                                            &new_val,
                                            1,
                                            __ATOMIC_SEQ_CST,
                                            __ATOMIC_SEQ_CST);
    } while(!success);
    return new_val;
#elif defined(STREX_LDREX_PRESENT)
    uint32_t old_val;
    uint32_t new_val;

    NRF_ATOMIC_OP(sub_hs, old_val, new_val, p_data, value);
    UNUSED_PARAMETER(old_val);
    UNUSED_PARAMETER(new_val);
    return new_val;
#else
    CRITICAL_REGION_ENTER();
    *p_data -= value;
    uint32_t new_value = *p_data;
    CRITICAL_REGION_EXIT();
    return new_value;
#endif //NRF_ATOMIC_USE_BUILD_IN
}

uint32_t nrf_atomic_flag_set_fetch(nrf_atomic_flag_t * p_data)
{
    return nrf_atomic_u32_fetch_or(p_data, 1);
}

uint32_t nrf_atomic_flag_set(nrf_atomic_flag_t * p_data)
{
    return nrf_atomic_u32_or(p_data, 1);
}

uint32_t nrf_atomic_flag_clear_fetch(nrf_atomic_flag_t * p_data)
{
    return nrf_atomic_u32_fetch_and(p_data, 0);
}

uint32_t nrf_atomic_flag_clear(nrf_atomic_flag_t * p_data)
{
    return nrf_atomic_u32_and(p_data, 0);
}

