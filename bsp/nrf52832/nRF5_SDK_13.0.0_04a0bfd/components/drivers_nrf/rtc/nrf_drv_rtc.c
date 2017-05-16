/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(RTC)
#define ENABLED_RTC_COUNT (RTC0_ENABLED+RTC1_ENABLED+RTC2_ENABLED)
#if ENABLED_RTC_COUNT

#include "nrf_drv_rtc.h"
#include "nrf_rtc.h"
#include "nrf_assert.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "RTC"

#if RTC_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       RTC_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  RTC_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR RTC_CONFIG_DEBUG_COLOR
#define EVT_TO_STR(event)   (event == NRF_RTC_EVENT_TICK ? "NRF_RTC_EVENT_TICK" :               \
                            (event == NRF_RTC_EVENT_OVERFLOW ? "NRF_RTC_EVENT_OVERFLOW" :       \
                            (event == NRF_RTC_EVENT_COMPARE_0 ? "NRF_RTC_EVENT_COMPARE_0" :     \
                            (event == NRF_RTC_EVENT_COMPARE_1 ? "NRF_RTC_EVENT_COMPARE_1" :     \
                            (event == NRF_RTC_EVENT_COMPARE_2 ? "NRF_RTC_EVENT_COMPARE_2" :     \
                            (event == NRF_RTC_EVENT_COMPARE_3 ? "NRF_RTC_EVENT_COMPARE_3" : "UNKNOWN EVENT")
#else //RTC_CONFIG_LOG_ENABLED
#define EVT_TO_STR(event)   ""
#define NRF_LOG_LEVEL       0
#endif //RTC_CONFIG_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

/**@brief RTC driver instance control block structure. */
typedef struct
{
    nrf_drv_state_t state;        /**< Instance state. */
    bool            reliable;     /**< Reliable mode flag. */
    uint8_t         tick_latency; /**< Maximum length of interrupt handler in ticks (max 7.7 ms). */
} nrf_drv_rtc_cb_t;

// User callbacks local storage.
static nrf_drv_rtc_handler_t m_handlers[ENABLED_RTC_COUNT];
static nrf_drv_rtc_cb_t      m_cb[ENABLED_RTC_COUNT];

ret_code_t nrf_drv_rtc_init(nrf_drv_rtc_t const * const p_instance,
                            nrf_drv_rtc_config_t const * p_config,
                            nrf_drv_rtc_handler_t handler)
{
    ASSERT(p_config);

    ret_code_t err_code;

    if (handler)
    {
        m_handlers[p_instance->instance_id] = handler;
    }
    else
    {
        err_code = NRF_ERROR_INVALID_PARAM;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    if (m_cb[p_instance->instance_id].state != NRF_DRV_STATE_UNINITIALIZED)
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    nrf_drv_common_irq_enable(p_instance->irq, p_config->interrupt_priority);
    nrf_rtc_prescaler_set(p_instance->p_reg, p_config->prescaler);
    m_cb[p_instance->instance_id].reliable     = p_config->reliable;
    m_cb[p_instance->instance_id].tick_latency = p_config->tick_latency;
    m_cb[p_instance->instance_id].state        = NRF_DRV_STATE_INITIALIZED;

    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}

void nrf_drv_rtc_uninit(nrf_drv_rtc_t const * const p_instance)
{
    uint32_t mask = NRF_RTC_INT_TICK_MASK     |
                    NRF_RTC_INT_OVERFLOW_MASK |
                    NRF_RTC_INT_COMPARE0_MASK |
                    NRF_RTC_INT_COMPARE1_MASK |
                    NRF_RTC_INT_COMPARE2_MASK |
                    NRF_RTC_INT_COMPARE3_MASK;
    ASSERT(m_cb[p_instance->instance_id].state != NRF_DRV_STATE_UNINITIALIZED);

    nrf_drv_common_irq_disable(p_instance->irq);

    nrf_rtc_task_trigger(p_instance->p_reg, NRF_RTC_TASK_STOP);
    nrf_rtc_event_disable(p_instance->p_reg, mask);
    nrf_rtc_int_disable(p_instance->p_reg, mask);

    m_cb[p_instance->instance_id].state = NRF_DRV_STATE_UNINITIALIZED;
    NRF_LOG_INFO("Uninitialized.\r\n");
}

void nrf_drv_rtc_enable(nrf_drv_rtc_t const * const p_instance)
{
    ASSERT(m_cb[p_instance->instance_id].state == NRF_DRV_STATE_INITIALIZED);

    nrf_rtc_task_trigger(p_instance->p_reg, NRF_RTC_TASK_START);
    m_cb[p_instance->instance_id].state = NRF_DRV_STATE_POWERED_ON;
    NRF_LOG_INFO("Enabled.\r\n");
}

void nrf_drv_rtc_disable(nrf_drv_rtc_t const * const p_instance)
{
    ASSERT(m_cb[p_instance->instance_id].state != NRF_DRV_STATE_UNINITIALIZED);

    nrf_rtc_task_trigger(p_instance->p_reg, NRF_RTC_TASK_STOP);
    m_cb[p_instance->instance_id].state = NRF_DRV_STATE_INITIALIZED;
    NRF_LOG_INFO("Disabled.\r\n");
}

ret_code_t nrf_drv_rtc_cc_disable(nrf_drv_rtc_t const * const p_instance, uint32_t channel)
{
    ASSERT(m_cb[p_instance->instance_id].state != NRF_DRV_STATE_UNINITIALIZED);
    ASSERT(channel<p_instance->cc_channel_count);

    ret_code_t err_code;
    uint32_t int_mask = RTC_CHANNEL_INT_MASK(channel);
    nrf_rtc_event_t event    = RTC_CHANNEL_EVENT_ADDR(channel);

    nrf_rtc_event_disable(p_instance->p_reg,int_mask);
    if (nrf_rtc_int_is_enabled(p_instance->p_reg,int_mask))
    {
        nrf_rtc_int_disable(p_instance->p_reg,int_mask);
        if (nrf_rtc_event_pending(p_instance->p_reg,event))
        {
            nrf_rtc_event_clear(p_instance->p_reg,event);
            err_code = NRF_ERROR_TIMEOUT;
            NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
            return err_code;
        }
    }
    NRF_LOG_INFO("RTC id: %d, channel disabled: %d.\r\n", p_instance->instance_id, channel);
    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}

ret_code_t nrf_drv_rtc_cc_set(nrf_drv_rtc_t const * const p_instance,
                              uint32_t channel,
                              uint32_t val,
                              bool enable_irq)
{
    ASSERT(m_cb[p_instance->instance_id].state != NRF_DRV_STATE_UNINITIALIZED);
    ASSERT(channel<p_instance->cc_channel_count);

    ret_code_t err_code;
    uint32_t int_mask = RTC_CHANNEL_INT_MASK(channel);
    nrf_rtc_event_t event    = RTC_CHANNEL_EVENT_ADDR(channel);

    nrf_rtc_event_disable(p_instance->p_reg, int_mask);
    nrf_rtc_int_disable(p_instance->p_reg, int_mask);

    val = RTC_WRAP(val);
    if (m_cb[p_instance->instance_id].reliable)
    {
        nrf_rtc_cc_set(p_instance->p_reg,channel,val);
        uint32_t cnt = nrf_rtc_counter_get(p_instance->p_reg);
        int32_t diff = cnt - val;
        if (cnt < val)
        {
            diff += RTC_COUNTER_COUNTER_Msk;
        }
        if (diff < m_cb[p_instance->instance_id].tick_latency)
        {
            err_code = NRF_ERROR_TIMEOUT;
            NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
            return err_code;
        }
    }
    else
    {
        nrf_rtc_cc_set(p_instance->p_reg,channel,val);
    }

    if (enable_irq)
    {
        nrf_rtc_event_clear(p_instance->p_reg,event);
        nrf_rtc_int_enable(p_instance->p_reg, int_mask);
    }
    nrf_rtc_event_enable(p_instance->p_reg,int_mask);

    NRF_LOG_INFO("RTC id: %d, channel enabled: %d, compare value: %d.\r\n", p_instance->instance_id, channel, val);
    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}

void nrf_drv_rtc_tick_enable(nrf_drv_rtc_t const * const p_instance, bool enable_irq)
{
    nrf_rtc_event_t event = NRF_RTC_EVENT_TICK;
    uint32_t mask = NRF_RTC_INT_TICK_MASK;

    nrf_rtc_event_clear(p_instance->p_reg, event);
    nrf_rtc_event_enable(p_instance->p_reg, mask);
    if (enable_irq)
    {
        nrf_rtc_int_enable(p_instance->p_reg, mask);
    }
    NRF_LOG_INFO("Tick events enabled.\r\n");
}

void nrf_drv_rtc_tick_disable(nrf_drv_rtc_t const * const p_instance)
{
    uint32_t mask = NRF_RTC_INT_TICK_MASK;

    nrf_rtc_event_disable(p_instance->p_reg, mask);
    nrf_rtc_int_disable(p_instance->p_reg, mask);
    NRF_LOG_INFO("Tick events disabled.\r\n");
}

void nrf_drv_rtc_overflow_enable(nrf_drv_rtc_t const * const p_instance, bool enable_irq)
{
    nrf_rtc_event_t event = NRF_RTC_EVENT_OVERFLOW;
    uint32_t mask = NRF_RTC_INT_OVERFLOW_MASK;

    nrf_rtc_event_clear(p_instance->p_reg, event);
    nrf_rtc_event_enable(p_instance->p_reg, mask);
    if (enable_irq)
    {
        nrf_rtc_int_enable(p_instance->p_reg, mask);
    }
}
void nrf_drv_rtc_overflow_disable(nrf_drv_rtc_t const * const p_instance)
{
    uint32_t mask = NRF_RTC_INT_OVERFLOW_MASK;
    nrf_rtc_event_disable(p_instance->p_reg, mask);
    nrf_rtc_int_disable(p_instance->p_reg, mask);
}

uint32_t nrf_drv_rtc_max_ticks_get(nrf_drv_rtc_t const * const p_instance)
{
    uint32_t ticks;
    if (m_cb[p_instance->instance_id].reliable)
    {
        ticks = RTC_COUNTER_COUNTER_Msk - m_cb[p_instance->instance_id].tick_latency;
    }
    else
    {
        ticks = RTC_COUNTER_COUNTER_Msk;
    }
    return ticks;
}

/**@brief Generic function for handling RTC interrupt
 *
 * @param[in]  p_reg         Pointer to instance register structure.
 * @param[in]  instance_id   Index of instance.
 */
__STATIC_INLINE void nrf_drv_rtc_int_handler(NRF_RTC_Type * p_reg,
                                             uint32_t instance_id,
                                             uint32_t channel_count)
{
    uint32_t i;
    uint32_t int_mask = (uint32_t)NRF_RTC_INT_COMPARE0_MASK;
    nrf_rtc_event_t event = NRF_RTC_EVENT_COMPARE_0;

    for (i = 0; i < channel_count; i++)
    {
        if (nrf_rtc_int_is_enabled(p_reg,int_mask) && nrf_rtc_event_pending(p_reg,event))
        {
            nrf_rtc_event_disable(p_reg,int_mask);
            nrf_rtc_int_disable(p_reg,int_mask);
            nrf_rtc_event_clear(p_reg,event);
            NRF_LOG_DEBUG("Event: %s, instance id: %d.\r\n",
                         (uint32_t)EVT_TO_STR(event), (uint32_t)instance_id);
            m_handlers[instance_id]((nrf_drv_rtc_int_type_t)i);
        }
        int_mask <<= 1;
        event    = (nrf_rtc_event_t)((uint32_t)event + sizeof(uint32_t));
    }
    event = NRF_RTC_EVENT_TICK;
    if (nrf_rtc_int_is_enabled(p_reg,NRF_RTC_INT_TICK_MASK) &&
        nrf_rtc_event_pending(p_reg, event))
    {
        nrf_rtc_event_clear(p_reg, event);
        NRF_LOG_DEBUG("Event: %s, instance id: %d.\r\n", (uint32_t)EVT_TO_STR(event), instance_id);
        m_handlers[instance_id](NRF_DRV_RTC_INT_TICK);
    }

    event = NRF_RTC_EVENT_OVERFLOW;
    if (nrf_rtc_int_is_enabled(p_reg,NRF_RTC_INT_OVERFLOW_MASK) &&
        nrf_rtc_event_pending(p_reg, event))
    {
        nrf_rtc_event_clear(p_reg,event);
        NRF_LOG_DEBUG("Event: %s, instance id: %d.\r\n", (uint32_t)EVT_TO_STR(event), instance_id);
        m_handlers[instance_id](NRF_DRV_RTC_INT_OVERFLOW);
    }
}

#if NRF_MODULE_ENABLED(RTC0)
void RTC0_IRQHandler(void)
{
    nrf_drv_rtc_int_handler(NRF_RTC0,RTC0_INSTANCE_INDEX, NRF_RTC_CC_CHANNEL_COUNT(0));
}
#endif

#if NRF_MODULE_ENABLED(RTC1)
void RTC1_IRQHandler(void)
{
    nrf_drv_rtc_int_handler(NRF_RTC1,RTC1_INSTANCE_INDEX, NRF_RTC_CC_CHANNEL_COUNT(1));
}
#endif

#if NRF_MODULE_ENABLED(RTC2)
void RTC2_IRQHandler(void)
{
    nrf_drv_rtc_int_handler(NRF_RTC2,RTC2_INSTANCE_INDEX, NRF_RTC_CC_CHANNEL_COUNT(2));
}
#endif
#endif //ENABLED_RTC_COUNT
#endif //NRF_MODULE_ENABLED(RTC)
