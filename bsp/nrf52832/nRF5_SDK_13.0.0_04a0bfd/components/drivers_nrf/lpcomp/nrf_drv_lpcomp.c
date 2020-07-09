/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(LPCOMP)
#include "nrf_drv_lpcomp.h"
#include "nrf_assert.h"
#include "nrf_error.h"
#include "nrf_soc.h"
#include "nrf_drv_common.h"
#include "app_util_platform.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define NRF_LOG_MODULE_NAME "LPCOMP"

#if LPCOMP_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       LPCOMP_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  LPCOMP_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR LPCOMP_CONFIG_DEBUG_COLOR
#define EVT_TO_STR(event)   (event == NRF_LPCOMP_EVENT_READY ? "NRF_LPCOMP_EVENT_READY" :                \
                            (event == NRF_LPCOMP_EVENT_DOWN ? "NRF_LPCOMP_EVENT_DOWN" :                  \
                            (event == NRF_LPCOMP_EVENT_UP ? "NRF_LPCOMP_EVENT_UP" :                      \
                            (event == NRF_LPCOMP_EVENT_CROSS ? "NRF_LPCOMP_EVENT_CROSS" : "UNKNOWN EVENT"))))
#else //LPCOMP_CONFIG_LOG_ENABLED
#define EVT_TO_STR(event)   ""
#define NRF_LOG_LEVEL       0
#endif //LPCOMP_CONFIG_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"


static lpcomp_events_handler_t m_lpcomp_events_handler = NULL;
static nrf_drv_state_t         m_state = NRF_DRV_STATE_UNINITIALIZED;

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    #define IRQ_HANDLER_NAME     irq_handler_for_lpcomp
    #define IRQ_HANDLER          static void IRQ_HANDLER_NAME(void)

    IRQ_HANDLER;
#else
    #define IRQ_HANDLER void LPCOMP_IRQHandler(void)
#endif // NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)

static void lpcomp_execute_handler(nrf_lpcomp_event_t event, uint32_t event_mask)
{
    if ( nrf_lpcomp_event_check(event) && nrf_lpcomp_int_enable_check(event_mask) )
    {
        nrf_lpcomp_event_clear(event);
        NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(event));

        m_lpcomp_events_handler(event);
    }
}


IRQ_HANDLER
{
    lpcomp_execute_handler(NRF_LPCOMP_EVENT_READY, LPCOMP_INTENSET_READY_Msk);
    lpcomp_execute_handler(NRF_LPCOMP_EVENT_DOWN, LPCOMP_INTENSET_DOWN_Msk);
    lpcomp_execute_handler(NRF_LPCOMP_EVENT_UP, LPCOMP_INTENSET_UP_Msk);
    lpcomp_execute_handler(NRF_LPCOMP_EVENT_CROSS, LPCOMP_INTENSET_CROSS_Msk);
}


ret_code_t nrf_drv_lpcomp_init(const nrf_drv_lpcomp_config_t * p_config,
                               lpcomp_events_handler_t   events_handler)
{
    ASSERT(p_config);
    ret_code_t err_code;

    if (m_state != NRF_DRV_STATE_UNINITIALIZED)
    { // LPCOMP driver is already initialized
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    if (nrf_drv_common_per_res_acquire(NRF_LPCOMP, IRQ_HANDLER_NAME) != NRF_SUCCESS)
    {
        err_code = NRF_ERROR_BUSY;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
#endif

    nrf_lpcomp_configure(&(p_config->hal) );

    if (events_handler)
    {
        m_lpcomp_events_handler = events_handler;
    }
    else
    {
        err_code = NRF_ERROR_INVALID_PARAM;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    nrf_lpcomp_input_select(p_config->input);

    switch (p_config->hal.detection)
    {
        case NRF_LPCOMP_DETECT_UP:
            nrf_lpcomp_int_enable(LPCOMP_INTENSET_UP_Msk);
            break;

        case NRF_LPCOMP_DETECT_DOWN:
            nrf_lpcomp_int_enable(LPCOMP_INTENSET_DOWN_Msk);
            break;

        case NRF_LPCOMP_DETECT_CROSS:
            nrf_lpcomp_int_enable(LPCOMP_INTENSET_CROSS_Msk);
            break;

        default:
            break;
    }
    nrf_lpcomp_shorts_enable(NRF_LPCOMP_SHORT_READY_SAMPLE_MASK);

    nrf_drv_common_irq_enable(LPCOMP_IRQn, p_config->interrupt_priority);

    m_state = NRF_DRV_STATE_INITIALIZED;

    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}


void nrf_drv_lpcomp_uninit(void)
{
    ASSERT(m_state != NRF_DRV_STATE_UNINITIALIZED);
    nrf_drv_common_irq_disable(LPCOMP_IRQn);
    nrf_drv_lpcomp_disable();
#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    nrf_drv_common_per_res_release(NRF_LPCOMP);
#endif
    m_state = NRF_DRV_STATE_UNINITIALIZED;
    m_lpcomp_events_handler = NULL;
    NRF_LOG_INFO("Uninitialized.\r\n");
}

void nrf_drv_lpcomp_enable(void)
{
    ASSERT(m_state == NRF_DRV_STATE_INITIALIZED);
    nrf_lpcomp_enable();
    nrf_lpcomp_task_trigger(NRF_LPCOMP_TASK_START);
    m_state = NRF_DRV_STATE_POWERED_ON;
    NRF_LOG_INFO("Enabled.\r\n");
}

void nrf_drv_lpcomp_disable(void)
{
    ASSERT(m_state == NRF_DRV_STATE_POWERED_ON);
    nrf_lpcomp_disable();
    nrf_lpcomp_task_trigger(NRF_LPCOMP_TASK_STOP);
    m_state = NRF_DRV_STATE_INITIALIZED;
    NRF_LOG_INFO("Disabled.\r\n");
}

void nrf_drv_lpcomp_event_handler_register(lpcomp_events_handler_t lpcomp_events_handler)
{
    m_lpcomp_events_handler = lpcomp_events_handler;
}

#endif //NRF_MODULE_ENABLED(LPCOMP)
