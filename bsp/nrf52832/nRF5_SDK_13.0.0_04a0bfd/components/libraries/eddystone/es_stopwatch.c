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

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "es_stopwatch.h"
#include "sdk_macros.h"
#include "app_timer.h"
#include "es_app_config.h"

static uint32_t m_ticks_last_returned[ES_STOPWATCH_MAX_USERS];
static uint32_t m_ids_ticks_wrap[ES_STOPWATCH_MAX_USERS];
static uint8_t  m_nof_ids     = 0;
static bool     m_initialized = false;

uint32_t es_stopwatch_check(es_stopwatch_id_t id)
{
    uint32_t ticks_current = app_timer_cnt_get();
    uint32_t ticks_diff;

    if (m_ids_ticks_wrap[id] == 0)
    {
        APP_ERROR_CHECK(NRF_ERROR_INVALID_STATE);
    }

    ticks_diff = app_timer_cnt_diff_compute(ticks_current, m_ticks_last_returned[id]);

    if (ticks_diff >= m_ids_ticks_wrap[id])
    {
        m_ticks_last_returned[id] = (ticks_current / m_ids_ticks_wrap[id]) * m_ids_ticks_wrap[id];

        return ticks_diff / m_ids_ticks_wrap[id];
    }

    return 0;
}

ret_code_t es_stopwatch_create(es_stopwatch_id_t * p_sw_id, uint32_t ticks_wrap)
{
    VERIFY_PARAM_NOT_NULL(p_sw_id);

    if (m_nof_ids == ES_STOPWATCH_MAX_USERS)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (!m_initialized)
    {
        return NRF_ERROR_MODULE_NOT_INITIALZED;
    }

    *p_sw_id = m_nof_ids;

    m_ids_ticks_wrap[m_nof_ids] = ticks_wrap;

    m_nof_ids++;

    return NRF_SUCCESS;
}


void es_stopwatch_init(void)
{
    m_nof_ids = 0;
    memset(m_ticks_last_returned, 0, sizeof(m_ticks_last_returned));
    memset(m_ids_ticks_wrap, 0, sizeof(m_ids_ticks_wrap));
    m_initialized = true;
}
