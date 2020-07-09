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
#if NRF_MODULE_ENABLED(PWM)
#define ENABLED_PWM_COUNT (PWM0_ENABLED+PWM1_ENABLED+PWM2_ENABLED)
#if ENABLED_PWM_COUNT
#include <string.h>
#include "nrf_drv_pwm.h"
#include "nrf_drv_common.h"
#include "nrf_gpio.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "PWM"

#if PWM_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       PWM_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  PWM_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR PWM_CONFIG_DEBUG_COLOR
#else //PWM_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif //PWM_CONFIG_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#if NRF_MODULE_ENABLED(PWM_NRF52_ANOMALY_109_WORKAROUND)
// The workaround uses interrupts to wake up the CPU and ensure it is active
// when PWM is about to start a DMA transfer. For initial transfer, done when
// a playback is started via PPI, a specific EGU instance is used to generate
// an interrupt. During the playback, the PWM interrupt triggered on SEQEND
// event of a preceding sequence is used to protect the transfer done for
// the next sequence to be played.
#include "nrf_egu.h"
#define USE_DMA_ISSUE_WORKAROUND
#endif
#if defined(USE_DMA_ISSUE_WORKAROUND)
#define EGU_IRQn(i)         EGU_IRQn_(i)
#define EGU_IRQn_(i)        SWI##i##_EGU##i##_IRQn
#define EGU_IRQHandler(i)   EGU_IRQHandler_(i)
#define EGU_IRQHandler_(i)  SWI##i##_EGU##i##_IRQHandler
#define DMA_ISSUE_EGU_IDX   PWM_NRF52_ANOMALY_109_EGU_INSTANCE
#define DMA_ISSUE_EGU               CONCAT_2(NRF_EGU, DMA_ISSUE_EGU_IDX)
#define DMA_ISSUE_EGU_IRQn          EGU_IRQn(DMA_ISSUE_EGU_IDX)
#define DMA_ISSUE_EGU_IRQHandler    EGU_IRQHandler(DMA_ISSUE_EGU_IDX)
#endif

// Control block - driver instance local data.
typedef struct
{
#if defined(USE_DMA_ISSUE_WORKAROUND)
    uint32_t                 starting_task_address;
#endif
    nrf_drv_pwm_handler_t    handler;
    nrf_drv_state_t volatile state;
    uint8_t                  flags;
} pwm_control_block_t;
static pwm_control_block_t m_cb[ENABLED_PWM_COUNT];

static void configure_pins(nrf_drv_pwm_t const * const p_instance,
                           nrf_drv_pwm_config_t const * p_config)
{
    uint32_t out_pins[NRF_PWM_CHANNEL_COUNT];
    uint8_t i;

    for (i = 0; i < NRF_PWM_CHANNEL_COUNT; ++i)
    {
        uint8_t output_pin = p_config->output_pins[i];
        if (output_pin != NRF_DRV_PWM_PIN_NOT_USED)
        {
            bool inverted = output_pin &  NRF_DRV_PWM_PIN_INVERTED;
            out_pins[i]   = output_pin & ~NRF_DRV_PWM_PIN_INVERTED;

            if (inverted)
            {
                nrf_gpio_pin_set(out_pins[i]);
            }
            else
            {
                nrf_gpio_pin_clear(out_pins[i]);
            }

            nrf_gpio_cfg_output(out_pins[i]);
        }
        else
        {
            out_pins[i] = NRF_PWM_PIN_NOT_CONNECTED;
        }
    }

    nrf_pwm_pins_set(p_instance->p_registers, out_pins);
}


ret_code_t nrf_drv_pwm_init(nrf_drv_pwm_t const * const p_instance,
                            nrf_drv_pwm_config_t const * p_config,
                            nrf_drv_pwm_handler_t        handler)
{
    ASSERT(p_config);

    ret_code_t err_code;

    pwm_control_block_t * p_cb  = &m_cb[p_instance->drv_inst_idx];

    if (p_cb->state != NRF_DRV_STATE_UNINITIALIZED)
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__,
            (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    p_cb->handler = handler;

    configure_pins(p_instance, p_config);

    nrf_pwm_enable(p_instance->p_registers);
    nrf_pwm_configure(p_instance->p_registers,
        p_config->base_clock, p_config->count_mode, p_config->top_value);
    nrf_pwm_decoder_set(p_instance->p_registers,
        p_config->load_mode, p_config->step_mode);

    nrf_pwm_shorts_set(p_instance->p_registers, 0);
    nrf_pwm_int_set(p_instance->p_registers, 0);
    nrf_pwm_event_clear(p_instance->p_registers, NRF_PWM_EVENT_LOOPSDONE);
    nrf_pwm_event_clear(p_instance->p_registers, NRF_PWM_EVENT_SEQEND0);
    nrf_pwm_event_clear(p_instance->p_registers, NRF_PWM_EVENT_SEQEND1);
    nrf_pwm_event_clear(p_instance->p_registers, NRF_PWM_EVENT_STOPPED);

    // The workaround for nRF52 Anomaly 109 "protects" DMA transfers by handling
    // interrupts generated on SEQEND0 and SEQEND1 events (this ensures that
    // the 64 MHz clock is ready when data for the next sequence to be played
    // is read). Therefore, the PWM interrupt must be enabled even if the event
    // handler is not used.
#if defined(USE_DMA_ISSUE_WORKAROUND)
    nrf_drv_common_irq_enable(DMA_ISSUE_EGU_IRQn, p_config->irq_priority);
#else
    if (p_cb->handler)
#endif
    {
        nrf_drv_common_irq_enable(nrf_drv_get_IRQn(p_instance->p_registers),
            p_config->irq_priority);
    }

    p_cb->state = NRF_DRV_STATE_INITIALIZED;

    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__,
        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}


void nrf_drv_pwm_uninit(nrf_drv_pwm_t const * const p_instance)
{
    pwm_control_block_t * p_cb  = &m_cb[p_instance->drv_inst_idx];
    ASSERT(p_cb->state != NRF_DRV_STATE_UNINITIALIZED);

    nrf_drv_common_irq_disable(nrf_drv_get_IRQn(p_instance->p_registers));
#if defined(USE_DMA_ISSUE_WORKAROUND)
    nrf_drv_common_irq_disable(DMA_ISSUE_EGU_IRQn);
#endif

    nrf_pwm_disable(p_instance->p_registers);

    p_cb->state = NRF_DRV_STATE_UNINITIALIZED;
}


static uint32_t start_playback(nrf_drv_pwm_t const * const p_instance,
                               pwm_control_block_t * p_cb,
                               uint8_t               flags,
                               nrf_pwm_task_t        starting_task)
{
    p_cb->state = NRF_DRV_STATE_POWERED_ON;
    p_cb->flags = flags;

    if (p_cb->handler)
    {
        // The notification about finished playback is by default enabled,
        // but this can be suppressed.
        // The notification that the peripheral has stopped is always enabled.
        uint32_t int_mask = NRF_PWM_INT_LOOPSDONE_MASK |
                            NRF_PWM_INT_STOPPED_MASK;

        // The workaround for nRF52 Anomaly 109 "protects" DMA transfers by
        // handling interrupts generated on SEQEND0 and SEQEND1 events (see
        // 'nrf_drv_pwm_init'), hence these events must be always enabled
        // to generate interrupts.
        // However, the user handler is called for them only when requested
        // (see 'irq_handler').
#if defined(USE_DMA_ISSUE_WORKAROUND)
        int_mask |= NRF_PWM_INT_SEQEND0_MASK | NRF_PWM_INT_SEQEND1_MASK;
#else
        if (flags & NRF_DRV_PWM_FLAG_SIGNAL_END_SEQ0)
        {
            int_mask |= NRF_PWM_INT_SEQEND0_MASK;
        }
        if (flags & NRF_DRV_PWM_FLAG_SIGNAL_END_SEQ1)
        {
            int_mask |= NRF_PWM_INT_SEQEND1_MASK;
        }
#endif
        if (flags & NRF_DRV_PWM_FLAG_NO_EVT_FINISHED)
        {
            int_mask &= ~NRF_PWM_INT_LOOPSDONE_MASK;
        }

        nrf_pwm_int_set(p_instance->p_registers, int_mask);
    }
#if defined(USE_DMA_ISSUE_WORKAROUND)
    else
    {
        nrf_pwm_int_set(p_instance->p_registers,
            NRF_PWM_INT_SEQEND0_MASK | NRF_PWM_INT_SEQEND1_MASK);
    }
#endif

    nrf_pwm_event_clear(p_instance->p_registers, NRF_PWM_EVENT_STOPPED);

    if (flags & NRF_DRV_PWM_FLAG_START_VIA_TASK)
    {
        uint32_t starting_task_address =
            nrf_pwm_task_address_get(p_instance->p_registers, starting_task);

#if defined(USE_DMA_ISSUE_WORKAROUND)
        // To "protect" the initial DMA transfer it is required to start
        // the PWM by triggering the proper task from EGU interrupt handler,
        // it is not safe to do it directly via PPI.
        p_cb->starting_task_address = starting_task_address;
        nrf_egu_int_enable(DMA_ISSUE_EGU,
            nrf_egu_int_get(DMA_ISSUE_EGU, p_instance->drv_inst_idx));
        return (uint32_t)nrf_egu_task_trigger_address_get(DMA_ISSUE_EGU,
            p_instance->drv_inst_idx);
#else
        return starting_task_address;
#endif
    }

    nrf_pwm_task_trigger(p_instance->p_registers, starting_task);
    return 0;
}


uint32_t nrf_drv_pwm_simple_playback(nrf_drv_pwm_t const * const p_instance,
                                     nrf_pwm_sequence_t const * p_sequence,
                                     uint16_t                   playback_count,
                                     uint32_t                   flags)
{
    pwm_control_block_t * p_cb  = &m_cb[p_instance->drv_inst_idx];
    ASSERT(p_cb->state != NRF_DRV_STATE_UNINITIALIZED);
    ASSERT(playback_count > 0);
    ASSERT(nrf_drv_is_in_RAM(p_sequence->values.p_raw));

    // To take advantage of the looping mechanism, we need to use both sequences
    // (single sequence can be played back only once).
    nrf_pwm_sequence_set(p_instance->p_registers, 0, p_sequence);
    nrf_pwm_sequence_set(p_instance->p_registers, 1, p_sequence);
    bool odd = (playback_count & 1);
    nrf_pwm_loop_set(p_instance->p_registers,
        (playback_count / 2) + (odd ? 1 : 0));

    uint32_t shorts_mask;
    if (flags & NRF_DRV_PWM_FLAG_STOP)
    {
        shorts_mask = NRF_PWM_SHORT_LOOPSDONE_STOP_MASK;
    }
    else if (flags & NRF_DRV_PWM_FLAG_LOOP)
    {
        shorts_mask = odd ? NRF_PWM_SHORT_LOOPSDONE_SEQSTART1_MASK
                          : NRF_PWM_SHORT_LOOPSDONE_SEQSTART0_MASK;
    }
    else
    {
        shorts_mask = 0;
    }
    nrf_pwm_shorts_set(p_instance->p_registers, shorts_mask);

    NRF_LOG_INFO("Function: %s, sequence length: %d.\r\n", (uint32_t)__func__,
        p_sequence->length * sizeof(p_sequence->values));
    NRF_LOG_DEBUG("Sequence data:\r\n");
    NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_sequence->values.p_raw,
        p_sequence->length * sizeof(p_sequence->values));
    return start_playback(p_instance, p_cb, flags,
        odd ? NRF_PWM_TASK_SEQSTART1 : NRF_PWM_TASK_SEQSTART0);
}


uint32_t nrf_drv_pwm_complex_playback(nrf_drv_pwm_t const * const p_instance,
                                      nrf_pwm_sequence_t const * p_sequence_0,
                                      nrf_pwm_sequence_t const * p_sequence_1,
                                      uint16_t                   playback_count,
                                      uint32_t                   flags)
{
    pwm_control_block_t * p_cb  = &m_cb[p_instance->drv_inst_idx];
    ASSERT(p_cb->state != NRF_DRV_STATE_UNINITIALIZED);
    ASSERT(playback_count > 0);
    ASSERT(nrf_drv_is_in_RAM(p_sequence_0->values.p_raw));
    ASSERT(nrf_drv_is_in_RAM(p_sequence_1->values.p_raw));

    nrf_pwm_sequence_set(p_instance->p_registers, 0, p_sequence_0);
    nrf_pwm_sequence_set(p_instance->p_registers, 1, p_sequence_1);
    nrf_pwm_loop_set(p_instance->p_registers, playback_count);

    uint32_t shorts_mask;
    if (flags & NRF_DRV_PWM_FLAG_STOP)
    {
        shorts_mask = NRF_PWM_SHORT_LOOPSDONE_STOP_MASK;
    }
    else if (flags & NRF_DRV_PWM_FLAG_LOOP)
    {
        shorts_mask = NRF_PWM_SHORT_LOOPSDONE_SEQSTART0_MASK;
    }
    else
    {
        shorts_mask = 0;
    }
    nrf_pwm_shorts_set(p_instance->p_registers, shorts_mask);

    NRF_LOG_INFO("Function: %s, sequence 0 length: %d.\r\n", (uint32_t)__func__,
        p_sequence_0->length * sizeof(p_sequence_0->values));
    NRF_LOG_INFO("Function: %s, sequence 1 length: %d.\r\n", (uint32_t)__func__,
        p_sequence_1->length * sizeof(p_sequence_1->values));
    NRF_LOG_DEBUG("Sequence 0 data:\r\n");
    NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_sequence_0->values.p_raw,
        p_sequence_0->length * sizeof(p_sequence_0->values));
    NRF_LOG_DEBUG("Sequence 1 data:\r\n");
    NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_sequence_1->values.p_raw,
        p_sequence_1->length * sizeof(p_sequence_1->values));
    return start_playback(p_instance, p_cb, flags, NRF_PWM_TASK_SEQSTART0);
}


bool nrf_drv_pwm_stop(nrf_drv_pwm_t const * const p_instance,
                      bool wait_until_stopped)
{
    ASSERT(m_cb[p_instance->drv_inst_idx].state != NRF_DRV_STATE_UNINITIALIZED);

    bool ret_val = false;

    if (nrf_drv_pwm_is_stopped(p_instance))
    {
        ret_val = true;
    }
    else
    {
        nrf_pwm_task_trigger(p_instance->p_registers, NRF_PWM_TASK_STOP);

        do {
            if (nrf_drv_pwm_is_stopped(p_instance))
            {
                ret_val = true;
                break;
            }
        } while (wait_until_stopped);
    }

    NRF_LOG_INFO("%s returned %d.\r\n", (uint32_t)__func__, ret_val);
    return ret_val;
}


bool nrf_drv_pwm_is_stopped(nrf_drv_pwm_t const * const p_instance)
{
    pwm_control_block_t * p_cb  = &m_cb[p_instance->drv_inst_idx];
    ASSERT(p_cb->state != NRF_DRV_STATE_UNINITIALIZED);

    bool ret_val = false;

    // If the event handler is used (interrupts are enabled), the state will
    // be changed in interrupt handler when the STOPPED event occurs.
    if (p_cb->state != NRF_DRV_STATE_POWERED_ON)
    {
        ret_val = true;
    }
    // If interrupts are disabled, we must check the STOPPED event here.
    if (nrf_pwm_event_check(p_instance->p_registers, NRF_PWM_EVENT_STOPPED))
    {
        p_cb->state = NRF_DRV_STATE_INITIALIZED;
        NRF_LOG_INFO("Disabled.\r\n");
        ret_val = true;
    }

    NRF_LOG_INFO("%s returned %d.\r\n", (uint32_t)__func__, ret_val);
    return ret_val;
}


static void irq_handler(NRF_PWM_Type * p_pwm, pwm_control_block_t * p_cb)
{
    // The user handler is called for SEQEND0 and SEQEND1 events only when the
    // user asks for it (by setting proper flags when starting the playback).
    if (nrf_pwm_event_check(p_pwm, NRF_PWM_EVENT_SEQEND0))
    {
        nrf_pwm_event_clear(p_pwm, NRF_PWM_EVENT_SEQEND0);
        if ((p_cb->flags & NRF_DRV_PWM_FLAG_SIGNAL_END_SEQ0) && p_cb->handler)
        {
            p_cb->handler(NRF_DRV_PWM_EVT_END_SEQ0);
        }
    }
    if (nrf_pwm_event_check(p_pwm, NRF_PWM_EVENT_SEQEND1))
    {
        nrf_pwm_event_clear(p_pwm, NRF_PWM_EVENT_SEQEND1);
        if ((p_cb->flags & NRF_DRV_PWM_FLAG_SIGNAL_END_SEQ1) && p_cb->handler)
        {
            p_cb->handler(NRF_DRV_PWM_EVT_END_SEQ1);
        }
    }
    // For LOOPSDONE the handler is called by default, but the user can disable
    // this (via flags).
    if (nrf_pwm_event_check(p_pwm, NRF_PWM_EVENT_LOOPSDONE))
    {
        nrf_pwm_event_clear(p_pwm, NRF_PWM_EVENT_LOOPSDONE);
        if (!(p_cb->flags & NRF_DRV_PWM_FLAG_NO_EVT_FINISHED) && p_cb->handler)
        {
            p_cb->handler(NRF_DRV_PWM_EVT_FINISHED);
        }
    }

    // The STOPPED event is always propagated to the user handler.
    if (nrf_pwm_event_check(p_pwm, NRF_PWM_EVENT_STOPPED))
    {
        nrf_pwm_event_clear(p_pwm, NRF_PWM_EVENT_STOPPED);

        p_cb->state = NRF_DRV_STATE_INITIALIZED;
        if (p_cb->handler)
        {
            p_cb->handler(NRF_DRV_PWM_EVT_STOPPED);
        }
    }
}


#if defined(USE_DMA_ISSUE_WORKAROUND)
// See 'start_playback' why this is needed.
void DMA_ISSUE_EGU_IRQHandler(void)
{
    int i;
    for (i = 0; i < ENABLED_PWM_COUNT; ++i)
    {
        volatile uint32_t * p_event_reg =
            nrf_egu_event_triggered_address_get(DMA_ISSUE_EGU, i);
        if (*p_event_reg)
        {
            *p_event_reg = 0;
            *(volatile uint32_t *)(m_cb[i].starting_task_address) = 1;
        }
    }
}
#endif


#if NRF_MODULE_ENABLED(PWM0)
void PWM0_IRQHandler(void)
{
    irq_handler(NRF_PWM0, &m_cb[PWM0_INSTANCE_INDEX]);
}
#endif

#if NRF_MODULE_ENABLED(PWM1)
void PWM1_IRQHandler(void)
{
    irq_handler(NRF_PWM1, &m_cb[PWM1_INSTANCE_INDEX]);
}
#endif

#if NRF_MODULE_ENABLED(PWM2)
void PWM2_IRQHandler(void)
{
    irq_handler(NRF_PWM2, &m_cb[PWM2_INSTANCE_INDEX]);
}
#endif

#if PWM3_ENABLED
void PWM3_IRQHandler(void)
{
    irq_handler(NRF_PWM3, &m_cb[PWM3_INSTANCE_INDEX]);
}
#endif
#endif //ENABLED_PWM_COUNT
#endif //NRF_MODULE_ENABLED(PWM)
