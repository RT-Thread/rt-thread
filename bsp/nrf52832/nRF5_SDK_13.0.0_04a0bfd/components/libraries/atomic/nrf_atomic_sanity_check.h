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
#ifndef NRF_ATOMIC_SANITY_CHECK_H__
#define NRF_ATOMIC_SANITY_CHECK_H__

#include "nrf_atomic.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Quick sanity check of nrf_atomic API
 * */
static inline void nrf_atomic_sanity_check(void)
{
#if defined(DEBUG_NRF) || defined(DEBUG_NRF_USER)
    nrf_atomic_u32_t val;
    nrf_atomic_u32_t flag;

    /*Fetch version tests*/
    val = 0;
    ASSERT(nrf_atomic_u32_store_fetch(&val, 10) == 0);
    ASSERT(nrf_atomic_u32_store_fetch(&val, 0) == 10);

    val = 0;
    ASSERT(nrf_atomic_u32_or_fetch(&val, 1 << 16) == 0);
    ASSERT(nrf_atomic_u32_or_fetch(&val, 1 << 5) == ((1 << 16)));
    ASSERT(nrf_atomic_u32_or_fetch(&val, 1 << 5) == ((1 << 16) | (1 << 5)));
    ASSERT(nrf_atomic_u32_or_fetch(&val, 0) == ((1 << 16) | (1 << 5)));
    ASSERT(nrf_atomic_u32_or_fetch(&val, 0xFFFFFFFF) == ((1 << 16) | (1 << 5)));
    ASSERT(nrf_atomic_u32_or_fetch(&val, 0xFFFFFFFF) == (0xFFFFFFFF));

    val = 0xFFFFFFFF;
    ASSERT(nrf_atomic_u32_and_fetch(&val, ~(1 << 16)) == 0xFFFFFFFF);
    ASSERT(nrf_atomic_u32_and_fetch(&val, ~(1 << 5)) == (0xFFFFFFFF & ~((1 << 16))));
    ASSERT(nrf_atomic_u32_and_fetch(&val, 0) == (0xFFFFFFFF & ~(((1 << 16) | (1 << 5)))));
    ASSERT(nrf_atomic_u32_and_fetch(&val, 0xFFFFFFFF) == (0));

    val = 0;
    ASSERT(nrf_atomic_u32_xor_fetch(&val, (1 << 16)) == 0);
    ASSERT(nrf_atomic_u32_xor_fetch(&val, (1 << 5)) == ((1 << 16)));
    ASSERT(nrf_atomic_u32_xor_fetch(&val, 0) == ((1 << 16) | (1 << 5)));
    ASSERT(nrf_atomic_u32_xor_fetch(&val, (1 << 16) | (1 << 5)) == ((1 << 16) | (1 << 5)));
    ASSERT(nrf_atomic_u32_xor_fetch(&val, 0) == (0));

    val = 0;
    ASSERT(nrf_atomic_u32_add_fetch(&val, 100) == 0);
    ASSERT(nrf_atomic_u32_add_fetch(&val, 100) == 100);
    ASSERT(nrf_atomic_u32_add_fetch(&val, 1 << 24) == 200);
    ASSERT(nrf_atomic_u32_add_fetch(&val, 0) == (200 + (1 << 24)));
    ASSERT(nrf_atomic_u32_add_fetch(&val, 0xFFFFFFFF) == (200 + (1 << 24)));
    ASSERT(nrf_atomic_u32_add_fetch(&val, 0) == (200 - 1 + (1 << 24)));

    val = 1000;
    ASSERT(nrf_atomic_u32_sub_fetch(&val, 100) == 1000);
    ASSERT(nrf_atomic_u32_sub_fetch(&val, 100) == 900);
    ASSERT(nrf_atomic_u32_sub_fetch(&val, 0) == 800);
    ASSERT(nrf_atomic_u32_sub_fetch(&val, 0xFFFFFFFF) == 800);
    ASSERT(nrf_atomic_u32_sub_fetch(&val, 0) == 801);

    flag = 0;
    ASSERT(nrf_atomic_flag_set_fetch(&flag) == 0);
    ASSERT(nrf_atomic_flag_set_fetch(&flag) == 1);
    ASSERT(nrf_atomic_flag_clear_fetch(&flag) == 1);
    ASSERT(nrf_atomic_flag_clear_fetch(&flag) == 0);

    /*No fetch version tests*/
    val = 0;
    ASSERT(nrf_atomic_u32_store(&val, 10) == 10);
    ASSERT(nrf_atomic_u32_store(&val, 0) == 0);

    val = 0;
    ASSERT(nrf_atomic_u32_or(&val, 1 << 16) == 1 << 16);
    ASSERT(nrf_atomic_u32_or(&val, 1 << 5) == ((1 << 16) | (1 << 5)));
    ASSERT(nrf_atomic_u32_or(&val, 1 << 5) == ((1 << 16) | (1 << 5)));
    ASSERT(nrf_atomic_u32_or(&val, 0) == ((1 << 16) | (1 << 5)));
    ASSERT(nrf_atomic_u32_or(&val, 0xFFFFFFFF) == 0xFFFFFFFF);

    val = 0xFFFFFFFF;
    ASSERT(nrf_atomic_u32_and(&val, ~(1 << 16)) == (0xFFFFFFFF & ~((1 << 16))));
    ASSERT(nrf_atomic_u32_and(&val, ~(1 << 5)) == (0xFFFFFFFF & ~(((1 << 16) | (1 << 5)))));
    ASSERT(nrf_atomic_u32_and(&val, 0) == 0);

    val = 0;
    ASSERT(nrf_atomic_u32_xor(&val, (1 << 16)) == ((1 << 16)));
    ASSERT(nrf_atomic_u32_xor(&val, (1 << 5)) == ((1 << 16) | (1 << 5)));
    ASSERT(nrf_atomic_u32_xor(&val, 0) == ((1 << 16) | (1 << 5)));
    ASSERT(nrf_atomic_u32_xor(&val, (1 << 16) | (1 << 5)) == 0);

    val = 0;
    ASSERT(nrf_atomic_u32_add(&val, 100) == 100);
    ASSERT(nrf_atomic_u32_add(&val, 100) == 200);
    ASSERT(nrf_atomic_u32_add(&val, 1 << 24) == (200 + (1 << 24)));
    ASSERT(nrf_atomic_u32_add(&val, 0) == (200 + (1 << 24)));
    ASSERT(nrf_atomic_u32_add(&val, 0xFFFFFFFF) == (200 - 1 + (1 << 24)));

    val = 1000;
    ASSERT(nrf_atomic_u32_sub(&val, 100) == 900);
    ASSERT(nrf_atomic_u32_sub(&val, 100) == 800);
    ASSERT(nrf_atomic_u32_sub(&val, 0) == 800);
    ASSERT(nrf_atomic_u32_sub(&val, 0xFFFFFFFF) == 801);

    flag = 0;
    ASSERT(nrf_atomic_flag_set(&flag) == 1);
    ASSERT(nrf_atomic_flag_set(&flag) == 1);
    ASSERT(nrf_atomic_flag_clear(&flag) == 0);
    ASSERT(nrf_atomic_flag_clear(&flag) == 0);
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* NRF_ATOMIC_SANITY_CHECK_H__ */
