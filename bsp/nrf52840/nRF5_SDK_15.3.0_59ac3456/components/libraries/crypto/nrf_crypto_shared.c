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

#include "sdk_config.h"
#include "nordic_common.h"
#include "nrf_crypto_shared.h"


#if NRF_MODULE_ENABLED(NRF_CRYPTO)


void nrf_crypto_internal_swap_endian_in_place(uint8_t * p_buffer, size_t size)
{
    ASSERT(p_buffer != NULL);

    uint8_t temp;
    uint8_t * p_first = p_buffer;
    uint8_t * p_last = p_buffer + size - 1;
    while (p_last >= p_first)
    {
        temp = *p_first;
        *p_first = *p_last;
        *p_last = temp;
        p_first++;
        p_last--;
    }
}


void nrf_crypto_internal_swap_endian(uint8_t * p_out, uint8_t const * p_in, size_t size)
{
    ASSERT(p_out != NULL);
    ASSERT(p_in != NULL);

    uint8_t const * p_first = p_in;
    uint8_t * p_last = p_out + size - 1;
    while (p_last >= p_out)
    {
        *p_last = *p_first;
        p_first++;
        p_last--;
    }
}


void nrf_crypto_internal_double_swap_endian(uint8_t * p_out, uint8_t const * p_in, size_t part_size)
{
    nrf_crypto_internal_swap_endian(p_out, p_in, part_size);
    nrf_crypto_internal_swap_endian(&p_out[part_size], &p_in[part_size], part_size);
}


void nrf_crypto_internal_double_swap_endian_in_place(uint8_t * p_buffer, size_t part_size)
{
    nrf_crypto_internal_swap_endian_in_place(p_buffer, part_size);
    nrf_crypto_internal_swap_endian_in_place(&p_buffer[part_size], part_size);
}


#endif
