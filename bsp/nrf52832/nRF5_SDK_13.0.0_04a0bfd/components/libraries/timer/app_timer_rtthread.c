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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(APP_TIMER)
#include "app_timer.h"
#include <stdlib.h>
#include "nrf.h"
#include "nrf_soc.h"
#include "app_error.h"
#include "app_util_platform.h"

#include <rtthread.h>

/**@brief This structure keeps information about osTimer.*/
typedef struct
{
    rt_timer_t id;
    app_timer_timeout_handler_t callback;
    void *parameter;
}app_timer_info_t;


ret_code_t app_timer_init(void)
{
    return NRF_SUCCESS;
}

static void _timeout_entry(void *paramter)
{
    app_timer_info_t * p_timer_info;

    p_timer_info = (app_timer_info_t *)paramter;

    if (p_timer_info->callback != RT_NULL)
    {
        p_timer_info->callback(p_timer_info->parameter);
    }
}

ret_code_t app_timer_create(app_timer_id_t const      * p_timer_id,
                            app_timer_mode_t            mode,
                            app_timer_timeout_handler_t timeout_handler)
{
    app_timer_info_t * p_timer_info;

    if ((timeout_handler == NULL) || (p_timer_id == NULL))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    p_timer_info = (app_timer_info_t *)*p_timer_id;
    p_timer_info->callback = timeout_handler;

    if (mode == APP_TIMER_MODE_SINGLE_SHOT)
    {
        p_timer_info->id = rt_timer_create("apptimer", _timeout_entry, p_timer_info,
                            0, RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_ONE_SHOT);
    }
    else
    {
        p_timer_info->id = rt_timer_create("apptimer", _timeout_entry, p_timer_info,
                            0, RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_PERIODIC);
    }

    if (p_timer_info->id != RT_NULL)
    {
        return NRF_SUCCESS;
    }
    else
    {
        return NRF_ERROR_INVALID_PARAM; // This error is unspecified by rtx
    }
}

ret_code_t app_timer_start(app_timer_id_t timer_id, uint32_t timeout_ticks, void * p_context)
{
    app_timer_info_t * p_timer_info = (app_timer_info_t *)timer_id;

    if ((timeout_ticks < APP_TIMER_MIN_TIMEOUT_TICKS))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    if (p_timer_info->id == RT_NULL)
        return NRF_ERROR_INVALID_PARAM;

    if (p_timer_info->id->parent.flag & RT_TIMER_FLAG_ACTIVATED)
    {
        return NRF_SUCCESS;
    }

    p_timer_info->parameter = p_context;

    rt_timer_control(p_timer_info->id, RT_TIMER_CTRL_SET_TIME, &timeout_ticks);

    switch (rt_timer_start(p_timer_info->id))
    {
        case RT_EOK:
            return NRF_SUCCESS;

        default:
            return NRF_ERROR_INVALID_PARAM;
    }
}

ret_code_t app_timer_stop(app_timer_id_t timer_id)
{
    app_timer_info_t * p_timer_info = (app_timer_info_t *)timer_id;

    if (p_timer_info != RT_NULL && p_timer_info->id != RT_NULL)
    {
        // if (p_timer_info->id->parent.flag & RT_TIMER_FLAG_ACTIVATED)
        {
            rt_timer_stop(p_timer_info->id);
            return NRF_SUCCESS;
        }
    }

    return NRF_ERROR_INVALID_PARAM;
}

uint32_t app_timer_cnt_get(void)
{
    return rt_tick_get();
}

uint32_t app_timer_cnt_diff_compute(uint32_t   ticks_to,
                                    uint32_t   ticks_from)
{
    return ((ticks_to - ticks_from) & RT_TICK_MAX);
}

#endif //NRF_MODULE_ENABLED(APP_TIMER)

