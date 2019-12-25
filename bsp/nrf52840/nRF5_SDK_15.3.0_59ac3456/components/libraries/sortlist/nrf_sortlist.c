/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NRF_SORTLIST)
#include "nrf_sortlist.h"
#include "nrf_assert.h"

#define NRF_LOG_MODULE_NAME sortlist
#if NRF_SORTLIST_CONFIG_LOG_ENABLED
    #define NRF_LOG_LEVEL       NRF_SORTLIST_CONFIG_LOG_LEVEL
    #define NRF_LOG_INFO_COLOR  NRF_SORTLIST_CONFIG_INFO_COLOR
    #define NRF_LOG_DEBUG_COLOR NRF_SORTLIST_CONFIG_DEBUG_COLOR
#else
    #define NRF_LOG_LEVEL       0
#endif // NRF_SORTLIST_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

void nrf_sortlist_add(nrf_sortlist_t const * p_list, nrf_sortlist_item_t * p_item)
{
    ASSERT(p_list);
    ASSERT(p_item);

    nrf_sortlist_item_t ** pp_curr = &(p_list->p_cb->p_head);

    while(*pp_curr != NULL)
    {
        if(!(p_list->compare_func(*pp_curr, p_item)))
        {
            break;
        }
        pp_curr = &((*pp_curr)->p_next);
    }

    p_item->p_next = *pp_curr;
    *pp_curr = p_item;

    NRF_LOG_INFO("List:%s, adding element:%08X after:%08X, before:%08X",
                                  p_list->p_name, p_item, *pp_curr, p_item->p_next);
}

nrf_sortlist_item_t * nrf_sortlist_pop(nrf_sortlist_t const * p_list)
{
    ASSERT(p_list);
    nrf_sortlist_item_t * ret = p_list->p_cb->p_head;
    if (p_list->p_cb->p_head != NULL)
    {
        p_list->p_cb->p_head = p_list->p_cb->p_head->p_next;
    }
    NRF_LOG_INFO("List:%s, poping element:%08X", p_list->p_name, ret);
    return ret;
}

nrf_sortlist_item_t const * nrf_sortlist_peek(nrf_sortlist_t const * p_list)
{
    ASSERT(p_list);
    return p_list->p_cb->p_head;
}

nrf_sortlist_item_t const * nrf_sortlist_next(nrf_sortlist_item_t const * p_item)
{
    ASSERT(p_item);
    return p_item->p_next;
}

bool nrf_sortlist_remove(nrf_sortlist_t const * p_list, nrf_sortlist_item_t * p_item)
{
    ASSERT(p_list);
    ASSERT(p_item);
    bool ret = false;

    nrf_sortlist_item_t ** pp_curr = &(p_list->p_cb->p_head);

    while(*pp_curr != NULL)
    {
        if(*pp_curr == p_item)
        {
            *pp_curr = p_item->p_next;
            ret = true;
            break;
        }
        pp_curr = &((*pp_curr)->p_next);
    }

    NRF_LOG_INFO("List:%s, removing element:%08X %s",
                                  p_list->p_name, p_item, ret ? "succeeded" : "not found");
    return ret;
}
#endif //NRF_SORTLIST_ENABLED
