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

#include "sdk_common.h"

#if NRF_MODULE_ENABLED(NRF_SECTION_ITER)

#include "nrf_section_iter.h"


#if !defined(__GNUC__)
static void nrf_section_iter_item_set(nrf_section_iter_t * p_iter)
{
    ASSERT(p_iter            != NULL);
    ASSERT(p_iter->p_set     != NULL);
    ASSERT(p_iter->p_section != NULL);

    while (true)
    {
        if (p_iter->p_section == p_iter->p_set->p_last)
        {
            // End of the section set.
            p_iter->p_item = NULL;
            return;
        }

        if (p_iter->p_section->p_start != p_iter->p_section->p_end)
        {
            // Not empty section.
            p_iter->p_item = p_iter->p_section->p_start;
            return;
        }

        // Next section.
        p_iter->p_section++;
    }
}
#endif


void nrf_section_iter_init(nrf_section_iter_t * p_iter, nrf_section_set_t const * p_set)
{
    ASSERT(p_iter != NULL);
    ASSERT(p_set  != NULL);

    p_iter->p_set = p_set;

#if defined(__GNUC__)
    p_iter->p_item = p_iter->p_set->section.p_start;
    if (p_iter->p_item == p_iter->p_set->section.p_end)
    {
        p_iter->p_item = NULL;
    }
#else
    p_iter->p_section = p_set->p_first;
    nrf_section_iter_item_set(p_iter);
#endif
}

void nrf_section_iter_next(nrf_section_iter_t * p_iter)
{
    ASSERT(p_iter        != NULL);
    ASSERT(p_iter->p_set != NULL);

    if (p_iter->p_item == NULL)
    {
        return;
    }

    p_iter->p_item = (void *)((size_t)(p_iter->p_item) + p_iter->p_set->item_size);

#if defined(__GNUC__)
    if (p_iter->p_item == p_iter->p_set->section.p_end)
    {
        p_iter->p_item = NULL;
    }
#else
    ASSERT(p_iter->p_section != NULL);
    // End of current section reached?
    if (p_iter->p_item == p_iter->p_section->p_end)
    {
        p_iter->p_section++;
        nrf_section_iter_item_set(p_iter);
    }
#endif
}

#endif // NRF_MODULE_ENABLED(NRF_SECTION_ITER)
