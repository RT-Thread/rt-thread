/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(APP_PWM)
#include "app_pwm.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_gpiote.h"
#include "nrf_gpiote.h"
#include "nrf_gpio.h"
#include "app_util_platform.h"
#include "nrf_assert.h"

#define APP_PWM_CHANNEL_INITIALIZED                1
#define APP_PWM_CHANNEL_UNINITIALIZED              0

#define APP_PWM_CHANNEL_ENABLED                    1
#define APP_PWM_CHANNEL_DISABLED                   0

#define TIMER_PRESCALER_MAX                        9
#define TIMER_MAX_PULSEWIDTH_US_ON_16M             4095

#ifndef GPIOTE_SET_CLEAR_TASKS
#define APP_PWM_REQUIRED_PPI_CHANNELS_PER_INSTANCE 2
#endif
#define APP_PWM_REQUIRED_PPI_CHANNELS_PER_CHANNEL  2

#define UNALLOCATED                                0xFFFFFFFFUL
#define BUSY_STATE_CHANGING                        0xFE
#define BUSY_STATE_IDLE                            0xFF

#define PWM_MAIN_CC_CHANNEL                        2
#define PWM_SECONDARY_CC_CHANNEL                   3

#ifdef GPIOTE_SET_CLEAR_TASKS
static bool m_use_ppi_delay_workaround;
#endif


/**
 * @brief PWM busy status
 *
 * Stores the number of a channel being currently updated.
 *
 */
static volatile uint8_t  m_pwm_busy[TIMER_COUNT];


/**
 * @brief New duty cycle value
 *
 * When the channel duty cycle reaches this value, the update process is complete.
 */
static volatile uint32_t m_pwm_target_value[TIMER_COUNT];


/**
 * @brief PWM ready counter
 *
 * The value in this counter is decremented in every PWM cycle after initiating the update.
 * If an event handler function was specified by the user, it is being called
 * after two cycle events (at least one full PWM cycle).
 */
volatile uint8_t m_pwm_ready_counter[TIMER_COUNT][APP_PWM_CHANNELS_PER_INSTANCE];

/**
 * @brief Pointers to instances
 *
 * This array connects any active timer instance number with the pointer to the PWM instance.
 * It is used by the interrupt runtime.
 */
static const app_pwm_t * m_instances[TIMER_COUNT];

// Macros for getting the polarity of given instance/channel.
#define POLARITY_ACTIVE(INST,CH)   (( ((INST)->p_cb)->channels_cb[(CH)].polarity == \
                 APP_PWM_POLARITY_ACTIVE_LOW)?(0):(1))
#define POLARITY_INACTIVE(INST,CH) (( ((INST)->p_cb)->channels_cb[(CH)].polarity == \
                 APP_PWM_POLARITY_ACTIVE_LOW)?(1):(0))

//lint -save -e534


/**
 * @brief Workaround for PAN-73.
 *
 * @param[in] timer     Timer.
 * @param[in] enable    Enable or disable.
 */
static void pan73_workaround(NRF_TIMER_Type * p_timer, bool enable)
{
#ifndef GPIOTE_SET_CLEAR_TASKS
    if (p_timer == NRF_TIMER0)
    {
        *(uint32_t *)0x40008C0C = (enable ? 1 : 0);
    }
    else if (p_timer == NRF_TIMER1)
    {
        *(uint32_t *)0x40009C0C = (enable ? 1 : 0);
    }
    else if (p_timer == NRF_TIMER2)
    {
        *(uint32_t *)0x4000AC0C = (enable ? 1 : 0);
    }
#else
    UNUSED_PARAMETER(p_timer);
    UNUSED_PARAMETER(enable);
#endif
}

bool app_pwm_busy_check(app_pwm_t const * const p_instance)
{
    uint8_t busy_state = (m_pwm_busy[p_instance->p_timer->instance_id]);
    bool busy = true;
    if (busy_state != BUSY_STATE_IDLE)
    {
        if (busy_state != BUSY_STATE_CHANGING)
        {
            if (nrf_drv_timer_capture_get(p_instance->p_timer, (nrf_timer_cc_channel_t) busy_state)
                == m_pwm_target_value[p_instance->p_timer->instance_id])
            {
                m_pwm_busy[p_instance->p_timer->instance_id] = BUSY_STATE_IDLE;
                busy = false;
            }
        }
    }
    else
    {
        busy = false;
    }
    return busy;
}


/**
 * @brief Function for enabling the IRQ for a given PWM instance.
 *
 * @param[in] p_instance  PWM instance.
 */
__STATIC_INLINE void pwm_irq_enable(app_pwm_t const * const p_instance)
{
    nrf_drv_timer_compare_int_enable(p_instance->p_timer, PWM_MAIN_CC_CHANNEL);
}


/**
 * @brief Function for disabling the IRQ for a given PWM instance.
 *
 * @param[in] p_instance  PWM instance.
 */
__STATIC_INLINE void pwm_irq_disable(app_pwm_t const * const p_instance)
{
    nrf_drv_timer_compare_int_disable(p_instance->p_timer, PWM_MAIN_CC_CHANNEL);
}

#ifndef GPIOTE_SET_CLEAR_TASKS
/**
 * @brief Function for disabling PWM channel PPI.
 *
 * @param[in] p_instance  PWM instance.
 */
__STATIC_INLINE void pwm_channel_ppi_disable(app_pwm_t const * const p_instance, uint8_t channel)
{
    app_pwm_cb_t * p_cb = p_instance->p_cb;

    nrf_drv_ppi_channel_disable(p_cb->channels_cb[channel].ppi_channels[0]);
    nrf_drv_ppi_channel_disable(p_cb->channels_cb[channel].ppi_channels[1]);
}


/**
 * @brief Function for disabling PWM PPI.
 *
 * @param[in] p_instance  PWM instance.
 */
__STATIC_INLINE void pwm_ppi_disable(app_pwm_t const * const p_instance)
{
    app_pwm_cb_t * p_cb = p_instance->p_cb;

    nrf_drv_ppi_channel_disable(p_cb->ppi_channels[0]);
    nrf_drv_ppi_channel_disable(p_cb->ppi_channels[1]);
}
#endif

/**
 * @brief This function is called on interrupt after duty set.
 *
 * @param[in] timer                 Timer used by PWM.
 * @param[in] timer_instance_id     Timer index.
 */
void pwm_ready_tick(nrf_timer_event_t event_type, void * p_context)
{
    uint32_t timer_instance_id = (uint32_t)p_context;
    uint8_t disable = 1;

    for (uint8_t channel = 0; channel < APP_PWM_CHANNELS_PER_INSTANCE; ++channel)
    {
        if (m_pwm_ready_counter[timer_instance_id][channel])
        {
            --m_pwm_ready_counter[timer_instance_id][channel];
            if (!m_pwm_ready_counter[timer_instance_id][channel])
            {
                app_pwm_cb_t * p_cb = m_instances[timer_instance_id]->p_cb;
                p_cb->p_ready_callback(timer_instance_id);
            }
            else
            {
                disable = 0;
            }
        }
    }

    if (disable)
    {
        pwm_irq_disable(m_instances[timer_instance_id]);
    }
}


/**
 * @brief Function for resource de-allocation.
 *
 * @param[in] p_instance       PWM instance.
 */
//lint -e{650}
static void pwm_dealloc(app_pwm_t const * const p_instance)
{
    app_pwm_cb_t * p_cb = p_instance->p_cb;

#ifdef GPIOTE_SET_CLEAR_TASKS
    nrf_drv_ppi_channel_free(p_cb->ppi_channel);
#else
    for (uint8_t i = 0; i < APP_PWM_REQUIRED_PPI_CHANNELS_PER_INSTANCE; ++i)
    {
        if (p_cb->ppi_channels[i] != (nrf_ppi_channel_t)(uint8_t)(UNALLOCATED))
        {
            nrf_drv_ppi_channel_free(p_cb->ppi_channels[i]);
        }
    }
    if (p_cb->ppi_group != (nrf_ppi_channel_group_t)UNALLOCATED)
    {
        nrf_drv_ppi_group_free(p_cb->ppi_group);
    }
#endif //GPIOTE_SET_CLEAR_TASKS
    for (uint8_t ch = 0; ch < APP_PWM_CHANNELS_PER_INSTANCE; ++ch)
    {
        for (uint8_t i = 0; i < APP_PWM_REQUIRED_PPI_CHANNELS_PER_CHANNEL; ++i)
        {
            if (p_cb->channels_cb[ch].ppi_channels[i] != (nrf_ppi_channel_t)UNALLOCATED)
            {
                nrf_drv_ppi_channel_free(p_cb->channels_cb[ch].ppi_channels[i]);
                p_cb->channels_cb[ch].ppi_channels[i] = (nrf_ppi_channel_t)UNALLOCATED;
            }
        }
        if (p_cb->channels_cb[ch].gpio_pin != UNALLOCATED)
        {
            nrf_drv_gpiote_out_uninit(p_cb->channels_cb[ch].gpio_pin);
            p_cb->channels_cb[ch].gpio_pin = UNALLOCATED;
        }
        p_cb->channels_cb[ch].initialized = APP_PWM_CHANNEL_UNINITIALIZED;
    }
    nrf_drv_timer_uninit(p_instance->p_timer);
    return;
}

#ifndef GPIOTE_SET_CLEAR_TASKS
/**
 * @brief PWM state transition from (0%, 100%) to 0% or 100%.
 *
 * @param[in] p_instance       PWM instance.
 * @param[in] channel          PWM channel number.
 * @param[in] ticks            Number of clock ticks.
 */
static void pwm_transition_n_to_0or100(app_pwm_t const * const p_instance,
                                       uint8_t channel, uint16_t ticks)
{
    app_pwm_cb_t            * p_cb     = p_instance->p_cb;
    app_pwm_channel_cb_t    * p_ch_cb  = &p_cb->channels_cb[channel];
    nrf_ppi_channel_group_t   p_ppigrp = p_cb->ppi_group;

    pwm_ppi_disable(p_instance);
    nrf_drv_ppi_group_clear(p_ppigrp);
    nrf_drv_ppi_channels_include_in_group(
            nrf_drv_ppi_channel_to_mask(p_ch_cb->ppi_channels[0]) |
            nrf_drv_ppi_channel_to_mask(p_ch_cb->ppi_channels[1]),
            p_ppigrp);

    if (!ticks)
    {
        nrf_drv_ppi_channel_assign(p_cb->ppi_channels[0],
                    nrf_drv_timer_compare_event_address_get(p_instance->p_timer, channel),
                    nrf_drv_ppi_task_addr_group_disable_get(p_ppigrp));
        nrf_drv_timer_compare(p_instance->p_timer, (nrf_timer_cc_channel_t) PWM_SECONDARY_CC_CHANNEL, 0, false);
        m_pwm_target_value[p_instance->p_timer->instance_id] =
            nrf_drv_timer_capture_get(p_instance->p_timer, (nrf_timer_cc_channel_t) channel);
        nrf_drv_ppi_channel_assign(p_cb->ppi_channels[1],
                    nrf_drv_timer_compare_event_address_get(p_instance->p_timer, channel),
                    nrf_drv_timer_capture_task_address_get(p_instance->p_timer, PWM_SECONDARY_CC_CHANNEL));
    }
    else
    {
        ticks = p_cb->period;
        nrf_drv_ppi_channel_assign(p_cb->ppi_channels[0],
                    nrf_drv_timer_compare_event_address_get(p_instance->p_timer, PWM_MAIN_CC_CHANNEL),
                    nrf_drv_ppi_task_addr_group_disable_get(p_ppigrp));
        // Set secondary CC channel to non-zero value:
        nrf_drv_timer_compare(p_instance->p_timer, (nrf_timer_cc_channel_t) PWM_SECONDARY_CC_CHANNEL, 1, false);
        m_pwm_target_value[p_instance->p_timer->instance_id] = 0;
        // The captured value will be equal to 0, because timer clear on main PWM CC channel compare is enabled.
        nrf_drv_ppi_channel_assign(p_cb->ppi_channels[1],
                    nrf_drv_timer_compare_event_address_get(p_instance->p_timer, PWM_MAIN_CC_CHANNEL),
                    nrf_drv_timer_capture_task_address_get(p_instance->p_timer, PWM_SECONDARY_CC_CHANNEL));
    }

    nrf_drv_ppi_channel_enable(p_cb->ppi_channels[0]);
    nrf_drv_ppi_channel_enable(p_cb->ppi_channels[1]);

    p_ch_cb->pulsewidth = ticks;
    m_pwm_busy[p_instance->p_timer->instance_id] = PWM_SECONDARY_CC_CHANNEL;
}


/**
 * @brief PWM state transition from (0%, 100%) to (0%, 100%).
 *
 * @param[in] p_instance       PWM instance.
 * @param[in] channel          PWM channel number.
 * @param[in] ticks            Number of clock ticks.
 */
static void pwm_transition_n_to_m(app_pwm_t const * const p_instance,
                                  uint8_t channel, uint16_t ticks)
{
    app_pwm_cb_t            * p_cb     = p_instance->p_cb;
    app_pwm_channel_cb_t    * p_ch_cb  = &p_cb->channels_cb[channel];
    nrf_ppi_channel_group_t   p_ppigrp = p_cb->ppi_group;

    pwm_ppi_disable(p_instance);
    nrf_drv_ppi_group_clear(p_ppigrp);
    nrf_drv_ppi_channels_include_in_group(
        nrf_drv_ppi_channel_to_mask(p_cb->ppi_channels[0]) |
        nrf_drv_ppi_channel_to_mask(p_cb->ppi_channels[1]),
        p_ppigrp);

    nrf_drv_ppi_channel_assign(p_cb->ppi_channels[0],
                nrf_drv_timer_compare_event_address_get(p_instance->p_timer, PWM_SECONDARY_CC_CHANNEL),
                nrf_drv_timer_capture_task_address_get(p_instance->p_timer, channel));


    if (ticks + ((nrf_timer_frequency_get(p_instance->p_timer->p_reg) == NRF_TIMER_FREQ_16MHz) ? 1 : 0)
        < p_ch_cb->pulsewidth)
    {
        // For lower value, we need one more transition. Timer task delay is included.
        // If prescaler is disabled, one tick must be added because of 1 PCLK16M clock cycle delay.
        nrf_drv_ppi_channel_assign(p_cb->ppi_channels[1],
                nrf_drv_timer_compare_event_address_get(p_instance->p_timer, PWM_SECONDARY_CC_CHANNEL),
                nrf_drv_gpiote_out_task_addr_get(p_ch_cb->gpio_pin));
    }
    else
    {
        nrf_drv_ppi_channel_remove_from_group(p_cb->ppi_channels[1], p_ppigrp);
    }
    p_ch_cb->pulsewidth = ticks;
    nrf_drv_timer_compare(p_instance->p_timer, (nrf_timer_cc_channel_t) PWM_SECONDARY_CC_CHANNEL, ticks, false);
    nrf_drv_ppi_group_enable(p_ppigrp);

    m_pwm_target_value[p_instance->p_timer->instance_id] = ticks;
    m_pwm_busy[p_instance->p_timer->instance_id] = channel;
}


/**
 * @brief PWM state transition from 0% or 100% to (0%, 100%).
 *
 * @param[in] p_instance       PWM instance.
 * @param[in] channel          PWM channel number.
 * @param[in] ticks            Number of clock ticks.
 */
static void pwm_transition_0or100_to_n(app_pwm_t const * const p_instance,
                                       uint8_t channel, uint16_t ticks)
{
    app_pwm_cb_t            * p_cb      = p_instance->p_cb;
    app_pwm_channel_cb_t    * p_ch_cb   = &p_cb->channels_cb[channel];
    nrf_ppi_channel_group_t   p_ppigrp  = p_cb->ppi_group;
    nrf_timer_cc_channel_t    pwm_ch_cc = (nrf_timer_cc_channel_t)(channel);

    pwm_ppi_disable(p_instance);
    pwm_channel_ppi_disable(p_instance, channel);

    nrf_drv_timer_compare(p_instance->p_timer, pwm_ch_cc, ticks, false);
    nrf_drv_ppi_group_clear(p_ppigrp);
    nrf_drv_ppi_channels_include_in_group(
        nrf_drv_ppi_channel_to_mask(p_ch_cb->ppi_channels[0])|
        nrf_drv_ppi_channel_to_mask(p_ch_cb->ppi_channels[1]),
        p_ppigrp);

    if (!p_ch_cb->pulsewidth)
    {
        // Channel is at 0%.
        nrf_drv_ppi_channel_assign(p_cb->ppi_channels[0],
                    nrf_drv_timer_compare_event_address_get(p_instance->p_timer, channel),
                    nrf_drv_ppi_task_addr_group_enable_get(p_ppigrp));
        nrf_drv_timer_compare(p_instance->p_timer, (nrf_timer_cc_channel_t) PWM_SECONDARY_CC_CHANNEL, 0, false);
        m_pwm_target_value[p_instance->p_timer->instance_id] =
            nrf_drv_timer_capture_get(p_instance->p_timer, (nrf_timer_cc_channel_t) channel);
        nrf_drv_ppi_channel_assign(p_cb->ppi_channels[1],
                    nrf_drv_timer_compare_event_address_get(p_instance->p_timer, channel),
                    nrf_drv_timer_capture_task_address_get(p_instance->p_timer, PWM_SECONDARY_CC_CHANNEL));

    }
    else
    {
        // Channel is at 100%.
        nrf_drv_ppi_channel_assign(p_cb->ppi_channels[0],
                    nrf_drv_timer_compare_event_address_get(p_instance->p_timer, PWM_MAIN_CC_CHANNEL),
                    nrf_drv_ppi_task_addr_group_enable_get(p_ppigrp));
        // Set secondary CC channel to non-zero value:
        nrf_drv_timer_compare(p_instance->p_timer, (nrf_timer_cc_channel_t) PWM_SECONDARY_CC_CHANNEL, 1, false);
        m_pwm_target_value[p_instance->p_timer->instance_id] = 0;
        // The captured value will be equal to 0, because timer clear on main PWM CC channel compare is enabled.
        nrf_drv_ppi_channel_assign(p_cb->ppi_channels[1],
                    nrf_drv_timer_compare_event_address_get(p_instance->p_timer, PWM_MAIN_CC_CHANNEL),
                    nrf_drv_timer_capture_task_address_get(p_instance->p_timer, PWM_SECONDARY_CC_CHANNEL));
    }
    nrf_drv_ppi_channel_enable(p_cb->ppi_channels[0]);
    nrf_drv_ppi_channel_enable(p_cb->ppi_channels[1]);

    p_ch_cb->pulsewidth = ticks;
    m_pwm_busy[p_instance->p_timer->instance_id] = PWM_SECONDARY_CC_CHANNEL;
}


/**
 * @brief PWM state transition from 0% or 100% to 0% or 100%.
 *
 * @param[in] p_instance       PWM instance.
 * @param[in] channel          PWM channel number.
 * @param[in] ticks            Number of clock ticks.
 */
static void pwm_transition_0or100_to_0or100(app_pwm_t const * const p_instance,
                                            uint8_t channel, uint16_t ticks)
{
    app_pwm_cb_t         * p_cb      = p_instance->p_cb;
    app_pwm_channel_cb_t * p_ch_cb   = &p_cb->channels_cb[channel];
    nrf_timer_cc_channel_t pwm_ch_cc = (nrf_timer_cc_channel_t)(channel);

    pwm_ppi_disable(p_instance);
    pwm_channel_ppi_disable(p_instance, channel);
    if (!ticks)
    {
        // Set to 0%.
        nrf_drv_gpiote_out_task_force(p_ch_cb->gpio_pin, POLARITY_INACTIVE(p_instance, channel));
    }
    else if (ticks >= p_cb->period)
    {
        // Set to 100%.
        ticks = p_cb->period;
        nrf_drv_gpiote_out_task_force(p_ch_cb->gpio_pin, POLARITY_ACTIVE(p_instance, channel));
    }
    nrf_drv_timer_compare(p_instance->p_timer, pwm_ch_cc, ticks, false);
    p_ch_cb->pulsewidth = ticks;

    m_pwm_busy[p_instance->p_timer->instance_id] = BUSY_STATE_IDLE;
    return;
}

static void pwm_transition(app_pwm_t const * const p_instance,
                                       uint8_t channel, uint16_t ticks)
{
    app_pwm_cb_t         * p_cb      = p_instance->p_cb;
    app_pwm_channel_cb_t * p_ch_cb = &p_instance->p_cb->channels_cb[channel];

    // Pulse width change sequence:
    if (!p_ch_cb->pulsewidth || p_ch_cb->pulsewidth >= p_cb->period)
    {
        // Channel is disabled (0%) or at 100%.
        if (!ticks || ticks >= p_cb->period)
        {
            // Set to 0 or 100%.
            pwm_transition_0or100_to_0or100(p_instance, channel, ticks);
        }
        else
        {
            // Other value.
            pwm_transition_0or100_to_n(p_instance, channel, ticks);
        }
    }
    else
    {
        // Channel is at other value.
        if (!ticks || ticks >= p_cb->period)
        {
            // Disable channel (set to 0%) or set to 100%.
            pwm_transition_n_to_0or100(p_instance, channel, ticks);
        }
        else
        {
            // Set to any other value.
            pwm_transition_n_to_m(p_instance, channel, ticks);
        }
    }
}
#else //GPIOTE_SET_CLEAR_TASKS
/**
 * @brief PWM state transition.
 *
 * @param[in] p_instance       PWM instance.
 * @param[in] channel          PWM channel number.
 * @param[in] ticks            Number of clock ticks.
 */
static void pwm_transition(app_pwm_t const * const p_instance,
                                  uint8_t channel, uint16_t ticks)
{
    app_pwm_cb_t            * p_cb     = p_instance->p_cb;
    app_pwm_channel_cb_t    * p_ch_cb  = &p_cb->channels_cb[channel];
    nrf_timer_cc_channel_t    pwm_ch_cc = (nrf_timer_cc_channel_t)(channel);

    nrf_drv_ppi_channel_disable(p_cb->ppi_channel);

    if (!ticks)
    {
        nrf_drv_ppi_channel_disable(p_ch_cb->ppi_channels[1]);
        nrf_drv_ppi_channel_enable(p_ch_cb->ppi_channels[0]);
        m_pwm_busy[p_instance->p_timer->instance_id] = BUSY_STATE_IDLE;
    }
    else if (ticks >= p_cb->period)
    {
        ticks = p_cb->period;
        nrf_drv_ppi_channel_disable(p_ch_cb->ppi_channels[0]);
        nrf_drv_ppi_channel_enable(p_ch_cb->ppi_channels[1]);
        m_pwm_busy[p_instance->p_timer->instance_id] = BUSY_STATE_IDLE;
    }
    else
    {
        // Set to any other value.
        if ((p_ch_cb->pulsewidth != p_cb->period) && (p_ch_cb->pulsewidth != 0) && (ticks < p_ch_cb->pulsewidth))
        {
            nrf_drv_timer_compare(p_instance->p_timer, (nrf_timer_cc_channel_t)PWM_SECONDARY_CC_CHANNEL, p_ch_cb->pulsewidth, false);
            nrf_drv_ppi_channel_assign(p_cb->ppi_channel,
                                       nrf_drv_timer_compare_event_address_get(p_instance->p_timer, (nrf_timer_cc_channel_t)PWM_SECONDARY_CC_CHANNEL),
                                       p_ch_cb->polarity ? nrf_drv_gpiote_clr_task_addr_get(p_ch_cb->gpio_pin) : nrf_drv_gpiote_set_task_addr_get(p_ch_cb->gpio_pin));
            nrf_drv_ppi_channel_enable(p_cb->ppi_channel);
            m_pwm_busy[p_instance->p_timer->instance_id] = channel;
            m_pwm_target_value[p_instance->p_timer->instance_id] = ticks;
        }
        else
        {
            m_pwm_busy[p_instance->p_timer->instance_id] = BUSY_STATE_IDLE;
        }

        nrf_drv_timer_compare(p_instance->p_timer, pwm_ch_cc, ticks, false);

        nrf_drv_ppi_channel_enable(p_ch_cb->ppi_channels[0]);
        nrf_drv_ppi_channel_enable(p_ch_cb->ppi_channels[1]);
    }
    p_ch_cb->pulsewidth = ticks;
    return;
}
#endif //GPIOTE_SET_CLEAR_TASKS

ret_code_t app_pwm_channel_duty_ticks_set(app_pwm_t const * const p_instance,
                                          uint8_t           channel,
                                          uint16_t          ticks)
{
    app_pwm_cb_t         * p_cb    = p_instance->p_cb;
    app_pwm_channel_cb_t * p_ch_cb = &p_cb->channels_cb[channel];

    ASSERT(channel < APP_PWM_CHANNELS_PER_INSTANCE);
    ASSERT(p_ch_cb->initialized == APP_PWM_CHANNEL_INITIALIZED);

    if (p_cb->state != NRFX_DRV_STATE_POWERED_ON)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    if (ticks == p_ch_cb->pulsewidth)
    {
        if (p_cb->p_ready_callback)
        {
            p_cb->p_ready_callback(p_instance->p_timer->instance_id);
        }
        return NRF_SUCCESS;     // No action required.
    }
    if (app_pwm_busy_check(p_instance))
    {
        return NRF_ERROR_BUSY;  // PPI channels for synchronization are still in use.
    }

    m_pwm_busy[p_instance->p_timer->instance_id] = BUSY_STATE_CHANGING;

    // Set new value.

    pwm_transition(p_instance, channel, ticks);

    if (p_instance->p_cb->p_ready_callback)
    {
        //PWM ready interrupt handler will be called after one full period.
        m_pwm_ready_counter[p_instance->p_timer->instance_id][channel] = 2;
        pwm_irq_enable(p_instance);
    }
    return NRF_SUCCESS;
}

uint16_t app_pwm_channel_duty_ticks_get(app_pwm_t const * const p_instance, uint8_t channel)
{
    app_pwm_cb_t         * p_cb      = p_instance->p_cb;
    app_pwm_channel_cb_t * p_ch_cb   = &p_cb->channels_cb[channel];

    return p_ch_cb->pulsewidth;
}

uint16_t app_pwm_cycle_ticks_get(app_pwm_t const * const p_instance)
{
    app_pwm_cb_t * p_cb = p_instance->p_cb;

    return (uint16_t)p_cb->period;
}

ret_code_t app_pwm_channel_duty_set(app_pwm_t const * const p_instance,
                                  uint8_t channel, app_pwm_duty_t duty)
{
    uint32_t ticks = ((uint32_t)app_pwm_cycle_ticks_get(p_instance) * (uint32_t)duty) / 100UL;
    return app_pwm_channel_duty_ticks_set(p_instance, channel, ticks);
}


app_pwm_duty_t app_pwm_channel_duty_get(app_pwm_t const * const p_instance, uint8_t channel)
{
    uint32_t value = ((uint32_t)app_pwm_channel_duty_ticks_get(p_instance, channel) * 100UL) \
                     / (uint32_t)app_pwm_cycle_ticks_get(p_instance);

    return (app_pwm_duty_t)value;
}


/**
 * @brief Function for initializing the PWM channel.
 *
 * @param[in] p_instance       PWM instance.
 * @param[in] channel          Channel number.
 * @param[in] pin              GPIO pin number.
 *
 * @retval    NRF_SUCCESS If initialization was successful.
 * @retval    NRF_ERROR_NO_MEM If there were not enough free resources.
 * @retval    NRF_ERROR_INVALID_STATE If the timer is already in use or initialization failed.
 */
static ret_code_t app_pwm_channel_init(app_pwm_t const * const p_instance, uint8_t channel,
                                     uint32_t pin, app_pwm_polarity_t polarity)
{
    ASSERT(channel < APP_PWM_CHANNELS_PER_INSTANCE);
    app_pwm_cb_t * p_cb = p_instance->p_cb;
    app_pwm_channel_cb_t * p_channel_cb = &p_cb->channels_cb[channel];

    if (p_cb->state != NRFX_DRV_STATE_UNINITIALIZED)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    p_channel_cb->pulsewidth = 0;
    p_channel_cb->polarity   = polarity;
    ret_code_t err_code;

    /* GPIOTE setup: */
    nrf_drv_gpiote_out_config_t out_cfg = GPIOTE_CONFIG_OUT_TASK_TOGGLE( POLARITY_INACTIVE(p_instance, channel) );
    err_code = nrf_drv_gpiote_out_init((nrf_drv_gpiote_pin_t)pin,&out_cfg);
    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_NO_MEM;
    }
    p_cb->channels_cb[channel].gpio_pin = pin;

    // Set output to inactive state.
    if (polarity)
    {
        nrf_gpio_pin_clear(pin);
    }
    else
    {
        nrf_gpio_pin_set(pin);
    }

    /* PPI setup: */
    for (uint8_t i = 0; i < APP_PWM_REQUIRED_PPI_CHANNELS_PER_CHANNEL; ++i)
    {
        if (nrf_drv_ppi_channel_alloc(&p_channel_cb->ppi_channels[i]) != NRF_SUCCESS)
        {
            return NRF_ERROR_NO_MEM; // Resource de-allocation is done by callee.
        }
    }

    nrf_drv_ppi_channel_disable(p_channel_cb->ppi_channels[0]);
    nrf_drv_ppi_channel_disable(p_channel_cb->ppi_channels[1]);

#ifdef GPIOTE_SET_CLEAR_TASKS
    uint32_t deactivate_task_addr   = polarity ? nrf_drv_gpiote_clr_task_addr_get(p_channel_cb->gpio_pin) : nrf_drv_gpiote_set_task_addr_get(p_channel_cb->gpio_pin);
    uint32_t activate_task_addr     = polarity ? nrf_drv_gpiote_set_task_addr_get(p_channel_cb->gpio_pin) : nrf_drv_gpiote_clr_task_addr_get(p_channel_cb->gpio_pin);

    nrf_drv_ppi_channel_assign(p_channel_cb->ppi_channels[0],
                               nrf_drv_timer_compare_event_address_get(p_instance->p_timer, channel),
                               deactivate_task_addr);
    nrf_drv_ppi_channel_assign(p_channel_cb->ppi_channels[1],
                               nrf_drv_timer_compare_event_address_get(p_instance->p_timer, PWM_MAIN_CC_CHANNEL),
                               activate_task_addr);
#else //GPIOTE_SET_CLEAR_TASKS
    nrf_drv_ppi_channel_assign(p_channel_cb->ppi_channels[0],
                               nrf_drv_timer_compare_event_address_get(p_instance->p_timer, channel),
                               nrf_drv_gpiote_out_task_addr_get(p_channel_cb->gpio_pin));
    nrf_drv_ppi_channel_assign(p_channel_cb->ppi_channels[1],
                               nrf_drv_timer_compare_event_address_get(p_instance->p_timer, PWM_MAIN_CC_CHANNEL),
                               nrf_drv_gpiote_out_task_addr_get(p_channel_cb->gpio_pin));
#endif //GPIOTE_SET_CLEAR_TASKS
    p_channel_cb->initialized = APP_PWM_CHANNEL_INITIALIZED;
    m_pwm_ready_counter[p_instance->p_timer->instance_id][channel] = 0;

    return NRF_SUCCESS;
}


/**
 * @brief Function for calculating target timer frequency, which will allow to set given period length.
 *
 * @param[in] period_us       Desired period in microseconds.
 *
 * @retval    Timer frequency.
 */
__STATIC_INLINE nrf_timer_frequency_t pwm_calculate_timer_frequency(uint32_t period_us)
{
    uint32_t f   = (uint32_t) NRF_TIMER_FREQ_16MHz;
    uint32_t min = (uint32_t) NRF_TIMER_FREQ_31250Hz;

    while ((period_us > TIMER_MAX_PULSEWIDTH_US_ON_16M) && (f < min))
    {
        period_us >>= 1;
        ++f;
    }

#ifdef GPIOTE_SET_CLEAR_TASKS
    if ((m_use_ppi_delay_workaround) && (f == (uint32_t) NRF_TIMER_FREQ_16MHz))
    {
        f = (uint32_t) NRF_TIMER_FREQ_8MHz;
    }
#endif // GPIOTE_SET_CLEAR_TASKS

    return (nrf_timer_frequency_t) f;
}


ret_code_t app_pwm_init(app_pwm_t const * const p_instance, app_pwm_config_t const * const p_config,
                        app_pwm_callback_t p_ready_callback)
{
    ASSERT(p_instance);

    if (!p_config)
    {
        return NRF_ERROR_INVALID_DATA;
    }

    app_pwm_cb_t * p_cb = p_instance->p_cb;

    if (p_cb->state != NRFX_DRV_STATE_UNINITIALIZED)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    uint32_t err_code = nrf_drv_ppi_init();
    if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_MODULE_ALREADY_INITIALIZED))
    {
        return NRF_ERROR_NO_MEM;
    }


    if (!nrf_drv_gpiote_is_init())
    {
        err_code = nrf_drv_gpiote_init();
        if (err_code != NRF_SUCCESS)
        {
            return NRF_ERROR_INTERNAL;
        }
    }

#ifdef GPIOTE_SET_CLEAR_TASKS
    if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x30)
    {
        m_use_ppi_delay_workaround = false;
    }
    else
    {
        m_use_ppi_delay_workaround = true;
    }
#endif

    // Innitialize resource status:
#ifdef GPIOTE_SET_CLEAR_TASKS
    p_cb->ppi_channel = (nrf_ppi_channel_t)UNALLOCATED;
#else
    p_cb->ppi_channels[0] = (nrf_ppi_channel_t)UNALLOCATED;
    p_cb->ppi_channels[1] = (nrf_ppi_channel_t)UNALLOCATED;
    p_cb->ppi_group       = (nrf_ppi_channel_group_t)UNALLOCATED;
#endif //GPIOTE_SET_CLEAR_TASKS

    for (uint8_t i = 0; i < APP_PWM_CHANNELS_PER_INSTANCE; ++i)
    {
        p_cb->channels_cb[i].initialized     = APP_PWM_CHANNEL_UNINITIALIZED;
        p_cb->channels_cb[i].ppi_channels[0] = (nrf_ppi_channel_t)UNALLOCATED;
        p_cb->channels_cb[i].ppi_channels[1] = (nrf_ppi_channel_t)UNALLOCATED;
        p_cb->channels_cb[i].gpio_pin        = UNALLOCATED;
    }

    // Allocate PPI channels and groups:

#ifdef GPIOTE_SET_CLEAR_TASKS
    if (nrf_drv_ppi_channel_alloc(&p_cb->ppi_channel) != NRF_SUCCESS)
    {
        pwm_dealloc(p_instance);
        return NRF_ERROR_NO_MEM;
    }
#else //GPIOTE_SET_CLEAR_TASKS
    if (nrf_drv_ppi_group_alloc(&p_cb->ppi_group) != NRF_SUCCESS)
    {
        pwm_dealloc(p_instance);
        return NRF_ERROR_NO_MEM;
    }

    for (uint8_t i = 0; i < APP_PWM_REQUIRED_PPI_CHANNELS_PER_INSTANCE; ++i)
    {
        if (nrf_drv_ppi_channel_alloc(&p_cb->ppi_channels[i]) != NRF_SUCCESS)
        {
            pwm_dealloc(p_instance);
            return NRF_ERROR_NO_MEM;
        }
    }
#endif //GPIOTE_SET_CLEAR_TASKS
    // Initialize channels:
    for (uint8_t i = 0; i < APP_PWM_CHANNELS_PER_INSTANCE; ++i)
    {
        if (p_config->pins[i] != APP_PWM_NOPIN)
        {
            err_code = app_pwm_channel_init(p_instance, i, p_config->pins[i], p_config->pin_polarity[i]);
            if (err_code != NRF_SUCCESS)
            {
                pwm_dealloc(p_instance);
                return err_code;
            }
            app_pwm_channel_duty_ticks_set(p_instance, i, 0);
        }
    }

    // Initialize timer:
    nrf_timer_frequency_t  timer_freq = pwm_calculate_timer_frequency(p_config->period_us);
    nrf_drv_timer_config_t timer_cfg  = {
        .frequency          = timer_freq,
        .mode               = NRF_TIMER_MODE_TIMER,
        .bit_width          = NRF_TIMER_BIT_WIDTH_16,
        .interrupt_priority = APP_IRQ_PRIORITY_LOWEST,
        .p_context          = (void *) (uint32_t) p_instance->p_timer->instance_id
    };
    err_code = nrf_drv_timer_init(p_instance->p_timer, &timer_cfg,
                                  pwm_ready_tick);
    if (err_code != NRF_SUCCESS)
    {
        pwm_dealloc(p_instance);
        return err_code;
    }

    uint32_t ticks = nrf_drv_timer_us_to_ticks(p_instance->p_timer, p_config->period_us);
    p_cb->period = ticks;
    nrf_drv_timer_clear(p_instance->p_timer);
    nrf_drv_timer_extended_compare(p_instance->p_timer, (nrf_timer_cc_channel_t) PWM_MAIN_CC_CHANNEL,
                                    ticks, NRF_TIMER_SHORT_COMPARE2_CLEAR_MASK, true);
    nrf_drv_timer_compare_int_disable(p_instance->p_timer, PWM_MAIN_CC_CHANNEL);

    p_cb->p_ready_callback = p_ready_callback;
    m_instances[p_instance->p_timer->instance_id] = p_instance;
    m_pwm_busy[p_instance->p_timer->instance_id] = BUSY_STATE_IDLE;
    p_cb->state = NRFX_DRV_STATE_INITIALIZED;

    return NRF_SUCCESS;
}


void app_pwm_enable(app_pwm_t const * const p_instance)
{
    app_pwm_cb_t * p_cb = p_instance->p_cb;

    ASSERT(p_cb->state != NRFX_DRV_STATE_UNINITIALIZED);

    for (uint32_t channel = 0; channel < APP_PWM_CHANNELS_PER_INSTANCE; ++channel)
    {
        app_pwm_channel_cb_t * p_ch_cb = &p_cb->channels_cb[channel];
        m_pwm_ready_counter[p_instance->p_timer->instance_id][channel] = 0;
        if (p_ch_cb->initialized)
        {
            nrf_drv_gpiote_out_task_force(p_ch_cb->gpio_pin, POLARITY_INACTIVE(p_instance, channel));
            nrf_drv_gpiote_out_task_enable(p_ch_cb->gpio_pin);
            p_ch_cb->pulsewidth = 0;
        }
    }
    m_pwm_busy[p_instance->p_timer->instance_id] = BUSY_STATE_IDLE;

    pan73_workaround(p_instance->p_timer->p_reg, true);

    nrf_drv_timer_clear(p_instance->p_timer);
    nrf_drv_timer_enable(p_instance->p_timer);

    p_cb->state = NRFX_DRV_STATE_POWERED_ON;
    return;
}


void app_pwm_disable(app_pwm_t const * const p_instance)
{
    app_pwm_cb_t * p_cb = p_instance->p_cb;

    ASSERT(p_cb->state != NRFX_DRV_STATE_UNINITIALIZED);

    nrf_drv_timer_disable(p_instance->p_timer);
    pwm_irq_disable(p_instance);

#ifdef GPIOTE_SET_CLEAR_TASKS
    nrf_drv_ppi_channel_disable(p_cb->ppi_channel);
#else
    for (uint8_t ppi_channel = 0; ppi_channel < APP_PWM_REQUIRED_PPI_CHANNELS_PER_INSTANCE; ++ppi_channel)
    {
        nrf_drv_ppi_channel_disable(p_cb->ppi_channels[ppi_channel]);
    }
#endif //GPIOTE_SET_CLEAR_TASKS

    for (uint8_t channel = 0; channel < APP_PWM_CHANNELS_PER_INSTANCE; ++channel)
    {
        app_pwm_channel_cb_t * p_ch_cb = &p_cb->channels_cb[channel];
        if (p_ch_cb->initialized)
        {
            uint8_t polarity = POLARITY_INACTIVE(p_instance, channel);
            if (polarity)
            {
                nrf_gpio_pin_set(p_ch_cb->gpio_pin);
            }
            else
            {
                nrf_gpio_pin_clear(p_ch_cb->gpio_pin);
            }
            nrf_drv_gpiote_out_task_disable(p_ch_cb->gpio_pin);
            nrf_drv_ppi_channel_disable(p_ch_cb->ppi_channels[0]);
            nrf_drv_ppi_channel_disable(p_ch_cb->ppi_channels[1]);
        }
    }

    pan73_workaround(p_instance->p_timer->p_reg, false);

    p_cb->state = NRFX_DRV_STATE_INITIALIZED;
    return;
}


ret_code_t app_pwm_uninit(app_pwm_t const * const p_instance)
{
    app_pwm_cb_t * p_cb = p_instance->p_cb;

    if (p_cb->state == NRFX_DRV_STATE_POWERED_ON)
    {
        app_pwm_disable(p_instance);
    }
    else if (p_cb->state == NRFX_DRV_STATE_UNINITIALIZED)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    pwm_dealloc(p_instance);

    p_cb->state = NRFX_DRV_STATE_UNINITIALIZED;
    return NRF_SUCCESS;
}


//lint -restore
#endif //NRF_MODULE_ENABLED(APP_PWM)
