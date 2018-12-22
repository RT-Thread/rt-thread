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
#if NRF_MODULE_ENABLED(TIMER)
#define ENABLED_TIMER_COUNT (TIMER0_ENABLED+TIMER1_ENABLED+TIMER2_ENABLED+TIMER3_ENABLED+TIMER4_ENABLED)
#if ENABLED_TIMER_COUNT
#include "nrf_drv_timer.h"
#include "nrf_drv_common.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "TIMER"

#if TIMER_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       TIMER_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  TIMER_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR TIMER_CONFIG_DEBUG_COLOR
#else //TIMER_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif //TIMER_CONFIG_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

/**@brief Timer control block. */
typedef struct
{
    nrf_timer_event_handler_t handler;
    void *                    context;
    nrf_drv_state_t           state;
} timer_control_block_t;

static timer_control_block_t m_cb[ENABLED_TIMER_COUNT];

ret_code_t nrf_drv_timer_init(nrf_drv_timer_t const * const p_instance,
                              nrf_drv_timer_config_t const * p_config,
                              nrf_timer_event_handler_t timer_event_handler)
{
    timer_control_block_t * p_cb = &m_cb[p_instance->instance_id];
    ASSERT(((p_instance->p_reg == NRF_TIMER0) && TIMER0_ENABLED) || (p_instance->p_reg != NRF_TIMER0));
    ASSERT(((p_instance->p_reg == NRF_TIMER1) && TIMER1_ENABLED) || (p_instance->p_reg != NRF_TIMER1));
    ASSERT(((p_instance->p_reg == NRF_TIMER2) && TIMER2_ENABLED) || (p_instance->p_reg != NRF_TIMER2));
#if TIMER_COUNT == 5
    ASSERT(((p_instance->p_reg == NRF_TIMER3) && TIMER3_ENABLED) || (p_instance->p_reg != NRF_TIMER3));
    ASSERT(((p_instance->p_reg == NRF_TIMER4) && TIMER4_ENABLED) || (p_instance->p_reg != NRF_TIMER4));
#endif //TIMER_COUNT
#ifdef SOFTDEVICE_PRESENT
    ASSERT(p_instance->p_reg != NRF_TIMER0);
#endif
    ASSERT(p_config);

    ret_code_t err_code;

    if (p_cb->state != NRF_DRV_STATE_UNINITIALIZED)
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    if (timer_event_handler == NULL)
    {
        err_code = NRF_ERROR_INVALID_PARAM;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    /* Warning 685: Relational operator '<=' always evaluates to 'true'"
     * Warning in NRF_TIMER_IS_BIT_WIDTH_VALID macro. Macro validate timers resolution.
     * Not necessary in nRF52 based systems. Obligatory in nRF51 based systems.
     */

    /*lint -save -e685 */

    ASSERT(NRF_TIMER_IS_BIT_WIDTH_VALID(p_instance->p_reg, p_config->bit_width));

    //lint -restore

    p_cb->handler = timer_event_handler;
    p_cb->context = p_config->p_context;

    uint8_t i;
    for (i = 0; i < p_instance->cc_channel_count; ++i)
    {
        nrf_timer_event_clear(p_instance->p_reg,
            nrf_timer_compare_event_get(i));
    }

    nrf_drv_common_irq_enable(nrf_drv_get_IRQn(p_instance->p_reg),
        p_config->interrupt_priority);

    nrf_timer_mode_set(p_instance->p_reg, p_config->mode);
    nrf_timer_bit_width_set(p_instance->p_reg, p_config->bit_width);
    nrf_timer_frequency_set(p_instance->p_reg, p_config->frequency);

    p_cb->state = NRF_DRV_STATE_INITIALIZED;

    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}

void nrf_drv_timer_uninit(nrf_drv_timer_t const * const p_instance)
{
    nrf_drv_common_irq_disable(nrf_drv_get_IRQn(p_instance->p_reg));

    #define DISABLE_ALL UINT32_MAX
    nrf_timer_shorts_disable(p_instance->p_reg, DISABLE_ALL);
    nrf_timer_int_disable(p_instance->p_reg, DISABLE_ALL);
    #undef DISABLE_ALL

    if (m_cb[p_instance->instance_id].state == NRF_DRV_STATE_POWERED_ON)
    {
        nrf_drv_timer_disable(p_instance);
    }

    m_cb[p_instance->instance_id].state = NRF_DRV_STATE_UNINITIALIZED;
    NRF_LOG_INFO("Uninitialized instance: %d.\r\n", p_instance->instance_id);
}

void nrf_drv_timer_enable(nrf_drv_timer_t const * const p_instance)
{
    ASSERT(m_cb[p_instance->instance_id].state == NRF_DRV_STATE_INITIALIZED);
    nrf_timer_task_trigger(p_instance->p_reg, NRF_TIMER_TASK_START);
    m_cb[p_instance->instance_id].state = NRF_DRV_STATE_POWERED_ON;
    NRF_LOG_INFO("Enabled instance: %d.\r\n", p_instance->instance_id);
}

void nrf_drv_timer_disable(nrf_drv_timer_t const * const p_instance)
{
    ASSERT(m_cb[p_instance->instance_id].state == NRF_DRV_STATE_POWERED_ON);
    nrf_timer_task_trigger(p_instance->p_reg, NRF_TIMER_TASK_SHUTDOWN);
    m_cb[p_instance->instance_id].state = NRF_DRV_STATE_INITIALIZED;
    NRF_LOG_INFO("Disabled instance: %d.\r\n", p_instance->instance_id);
}

void nrf_drv_timer_resume(nrf_drv_timer_t const * const p_instance)
{
    ASSERT(m_cb[p_instance->instance_id].state == NRF_DRV_STATE_POWERED_ON);
    nrf_timer_task_trigger(p_instance->p_reg, NRF_TIMER_TASK_START);
    NRF_LOG_INFO("Resumed instance: %d.\r\n", p_instance->instance_id);
}

void nrf_drv_timer_pause(nrf_drv_timer_t const * const p_instance)
{
    ASSERT(m_cb[p_instance->instance_id].state == NRF_DRV_STATE_POWERED_ON);
    nrf_timer_task_trigger(p_instance->p_reg, NRF_TIMER_TASK_STOP);
    NRF_LOG_INFO("Paused instance: %d.\r\n", p_instance->instance_id);
}

void nrf_drv_timer_clear(nrf_drv_timer_t const * const p_instance)
{
    ASSERT(m_cb[p_instance->instance_id].state != NRF_DRV_STATE_UNINITIALIZED);
    nrf_timer_task_trigger(p_instance->p_reg, NRF_TIMER_TASK_CLEAR);
}

void nrf_drv_timer_increment(nrf_drv_timer_t const * const p_instance)
{
    ASSERT(m_cb[p_instance->instance_id].state == NRF_DRV_STATE_POWERED_ON);
    ASSERT(nrf_timer_mode_get(p_instance->p_reg) != NRF_TIMER_MODE_TIMER);

    nrf_timer_task_trigger(p_instance->p_reg, NRF_TIMER_TASK_COUNT);
}

uint32_t nrf_drv_timer_capture(nrf_drv_timer_t const * const p_instance,
                               nrf_timer_cc_channel_t cc_channel)
{
    ASSERT(m_cb[p_instance->instance_id].state == NRF_DRV_STATE_POWERED_ON);
    ASSERT(cc_channel < p_instance->cc_channel_count);

    nrf_timer_task_trigger(p_instance->p_reg,
        nrf_timer_capture_task_get(cc_channel));
    return nrf_timer_cc_read(p_instance->p_reg, cc_channel);
}

void nrf_drv_timer_compare(nrf_drv_timer_t const * const p_instance,
                           nrf_timer_cc_channel_t cc_channel,
                           uint32_t               cc_value,
                           bool                   enable_int)
{
    nrf_timer_int_mask_t timer_int = nrf_timer_compare_int_get(cc_channel);

    if (enable_int)
    {
        nrf_timer_int_enable(p_instance->p_reg, timer_int);
    }
    else
    {
        nrf_timer_int_disable(p_instance->p_reg, timer_int);
    }

    nrf_timer_cc_write(p_instance->p_reg, cc_channel, cc_value);
    NRF_LOG_INFO("Timer id: %d, capture value set: %d, channel: %d.\r\n", p_instance->instance_id, cc_value, cc_channel);
}

void nrf_drv_timer_extended_compare(nrf_drv_timer_t const * const p_instance,
                                    nrf_timer_cc_channel_t cc_channel,
                                    uint32_t               cc_value,
                                    nrf_timer_short_mask_t timer_short_mask,
                                    bool                   enable_int)
{
    nrf_timer_shorts_disable(p_instance->p_reg,
        (TIMER_SHORTS_COMPARE0_STOP_Msk  << cc_channel) |
        (TIMER_SHORTS_COMPARE0_CLEAR_Msk << cc_channel));

    nrf_timer_shorts_enable(p_instance->p_reg, timer_short_mask);

    (void)nrf_drv_timer_compare(p_instance,
                                cc_channel,
                                cc_value,
                                enable_int);
    NRF_LOG_INFO("Timer id: %d, capture value set: %d, channel: %d.\r\n", p_instance->instance_id, cc_value, cc_channel);
}

void nrf_drv_timer_compare_int_enable(nrf_drv_timer_t const * const p_instance,
                                      uint32_t channel)
{
    ASSERT(m_cb[p_instance->instance_id].state != NRF_DRV_STATE_UNINITIALIZED);
    ASSERT(channel < p_instance->cc_channel_count);

    nrf_timer_event_clear(p_instance->p_reg,
        nrf_timer_compare_event_get(channel));
    nrf_timer_int_enable(p_instance->p_reg,
        nrf_timer_compare_int_get(channel));
}

void nrf_drv_timer_compare_int_disable(nrf_drv_timer_t const * const p_instance,
                                       uint32_t channel)
{
    ASSERT(m_cb[p_instance->instance_id].state != NRF_DRV_STATE_UNINITIALIZED);
    ASSERT(channel < p_instance->cc_channel_count);

    nrf_timer_int_disable(p_instance->p_reg,
        nrf_timer_compare_int_get(channel));
}

static void irq_handler(NRF_TIMER_Type * p_reg,
                        timer_control_block_t * p_cb,
                        uint8_t channel_count)
{
    uint8_t i;
    for (i = 0; i < channel_count; ++i)
    {
        nrf_timer_event_t event = nrf_timer_compare_event_get(i);
        nrf_timer_int_mask_t int_mask = nrf_timer_compare_int_get(i);

        if (nrf_timer_event_check(p_reg, event) &&
            nrf_timer_int_enable_check(p_reg, int_mask))
        {
            nrf_timer_event_clear(p_reg, event);
            NRF_LOG_DEBUG("Compare event, channel: %d.\r\n", i);
            p_cb->handler(event, p_cb->context);
        }
    }
}

#if NRF_MODULE_ENABLED(TIMER0)
void TIMER0_IRQHandler(void)
{
    irq_handler(NRF_TIMER0, &m_cb[TIMER0_INSTANCE_INDEX],
        NRF_TIMER_CC_CHANNEL_COUNT(0));
}
#endif

#if NRF_MODULE_ENABLED(TIMER1)
void TIMER1_IRQHandler(void)
{
    irq_handler(NRF_TIMER1, &m_cb[TIMER1_INSTANCE_INDEX],
        NRF_TIMER_CC_CHANNEL_COUNT(1));
}
#endif

#if NRF_MODULE_ENABLED(TIMER2)
void TIMER2_IRQHandler(void)
{
    irq_handler(NRF_TIMER2, &m_cb[TIMER2_INSTANCE_INDEX],
        NRF_TIMER_CC_CHANNEL_COUNT(2));
}
#endif

#if NRF_MODULE_ENABLED(TIMER3)
void TIMER3_IRQHandler(void)
{
    irq_handler(NRF_TIMER3, &m_cb[TIMER3_INSTANCE_INDEX],
        NRF_TIMER_CC_CHANNEL_COUNT(3));
}
#endif

#if NRF_MODULE_ENABLED(TIMER4)
void TIMER4_IRQHandler(void)
{
    irq_handler(NRF_TIMER4, &m_cb[TIMER4_INSTANCE_INDEX],
        NRF_TIMER_CC_CHANNEL_COUNT(4));
}
#endif
#endif // ENABLED_TIMER_COUNT
#endif // NRF_MODULE_ENABLED(TIMER)
