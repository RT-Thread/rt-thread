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
#if NRF_MODULE_ENABLED(WDT)
#include "nrf_drv_wdt.h"
#include "nrf_drv_common.h"
#include "nrf_error.h"
#include "nrf_assert.h"
#include "nrf_wdt.h"
#include "app_util_platform.h"
#include <stdbool.h>
#include <stdint.h>

#define NRF_LOG_MODULE_NAME "WDT"

#if WDT_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       WDT_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  WDT_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR WDT_CONFIG_DEBUG_COLOR
#else //WDT_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif //WDT_CONFIG_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"


/**@brief WDT event handler. */
static nrf_wdt_event_handler_t m_wdt_event_handler;

/**@brief WDT state. */
static nrf_drv_state_t m_state;

/**@brief WDT alloc table. */
static uint32_t m_alloc_index;

static const nrf_drv_wdt_config_t m_default_config = NRF_DRV_WDT_DEAFULT_CONFIG;

/**@brief WDT interrupt handler. */
void WDT_IRQHandler(void)
{
    if (nrf_wdt_int_enable_check(NRF_WDT_INT_TIMEOUT_MASK) == true)
    {
        nrf_wdt_event_clear(NRF_WDT_EVENT_TIMEOUT);
        m_wdt_event_handler();
    }
}


ret_code_t nrf_drv_wdt_init(nrf_drv_wdt_config_t const * p_config,
                            nrf_wdt_event_handler_t     wdt_event_handler)
{
    ASSERT(wdt_event_handler != NULL);
    ret_code_t err_code;
    m_wdt_event_handler = wdt_event_handler;

    if (m_state == NRF_DRV_STATE_UNINITIALIZED)
    {
        m_state = NRF_DRV_STATE_INITIALIZED;
    }
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    if (p_config == NULL)
    {
        p_config = &m_default_config;
    }

    nrf_wdt_behaviour_set(p_config->behaviour);







    nrf_wdt_reload_value_set((p_config->reload_value * 32768) / 1000);

    nrf_drv_common_irq_enable(WDT_IRQn, p_config->interrupt_priority);

    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}


void nrf_drv_wdt_enable(void)
{
    ASSERT(m_alloc_index != 0);
    ASSERT(m_state == NRF_DRV_STATE_INITIALIZED);
    nrf_wdt_int_enable(NRF_WDT_INT_TIMEOUT_MASK);
    nrf_wdt_task_trigger(NRF_WDT_TASK_START);
    m_state = NRF_DRV_STATE_POWERED_ON;
    NRF_LOG_INFO("Enabled.\r\n");
}


void nrf_drv_wdt_feed(void)
{
    ASSERT(m_state == NRF_DRV_STATE_POWERED_ON);
    for (uint32_t i = 0; i < m_alloc_index; i++)
    {
        nrf_wdt_reload_request_set((nrf_wdt_rr_register_t)(NRF_WDT_RR0 + i));
    }
}

ret_code_t nrf_drv_wdt_channel_alloc(nrf_drv_wdt_channel_id * p_channel_id)
{
    ret_code_t result;
    ASSERT(p_channel_id);
    ASSERT(m_state == NRF_DRV_STATE_INITIALIZED);

    CRITICAL_REGION_ENTER();
    if (m_alloc_index < NRF_WDT_CHANNEL_NUMBER)
    {
        *p_channel_id = (nrf_drv_wdt_channel_id)(NRF_WDT_RR0 + m_alloc_index);
        m_alloc_index++;
        nrf_wdt_reload_request_enable(*p_channel_id);
        result = NRF_SUCCESS;
    }
    else
    {
        result = NRF_ERROR_NO_MEM;
    }
    CRITICAL_REGION_EXIT();
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(result));
    return result;
}

void nrf_drv_wdt_channel_feed(nrf_drv_wdt_channel_id channel_id)
{
    ASSERT(m_state == NRF_DRV_STATE_POWERED_ON);
    nrf_wdt_reload_request_set(channel_id);
}
#endif //NRF_MODULE_ENABLED(WDT)
