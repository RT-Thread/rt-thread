/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
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
#include "nrf_bootloader_dfu_timers.h"

#include <stdint.h>
#include <stdbool.h>
#include <nrfx.h>
#include "nrf_clock.h"
#include "nrf_rtc.h"
#include "nrf_delay.h"
#include "nrf_log.h"


#define RTC_PRESCALER       (0)              //!< The value provided to the RTC as the prescaler. 0 corresponds to one tick per clock cycle of the LFCLK (32768 ticks/s).
#define RTC_WRAP_TICKS      ((1 << 24) - 1)  //!< The largest possible value in the RTC counter register.
#define MAX_TIMEOUT_TICKS   (RTC_WRAP_TICKS) //!< The longest fire timeout allowed. Longer timeouts are handled by multiple firings.

typedef struct
{
    nrf_bootloader_dfu_timeout_callback_t callback;         //!< Callback that is called when this timer times out.
    uint32_t                              timeout;          //!< The number of ticks from the next firing until the actual timeout. This value will be different from 0 if the original timeout was longer than MAX_TIMEOUT_TICKS, so multiple firings were needed.
    uint32_t                              repeated_timeout; //!< If different from 0, this timer will be reactivated with this value after timing out.
    uint8_t                               cc_channel;       //!< Which CC register this timer uses.
} dfu_timer_t;


dfu_timer_t   m_timers[2] = {{.cc_channel = 0}, {.cc_channel = 1}}; //!< The timers used by this module.
dfu_timer_t * mp_inactivity = &m_timers[0];                         //!< Direct pointer to the inactivity timer, for convenience and readability.
dfu_timer_t * mp_wdt_feed   = &m_timers[1];                         //!< Direct pointer to the wdt feed timer, for convenience and readability.
uint32_t      m_counter_loops = 0;                                  //!< The number of times the RTC counter register has overflowed (wrapped around) since the RTC was started.

#if RTC_COUNT > 2
#define RTC_INSTANCE   2
#define RTC_STRUCT     NRF_RTC2
#define RTC_IRQHandler RTC2_IRQHandler
#define RTC_IRQn       RTC2_IRQn
#define RTC_CC_COUNT   NRF_RTC_CC_CHANNEL_COUNT(2))
#elif RTC_COUNT > 1
#define RTC_INSTANCE   1
#define RTC_STRUCT     NRF_RTC1
#define RTC_IRQHandler RTC1_IRQHandler
#define RTC_IRQn       RTC1_IRQn
#define RTC_CC_COUNT   NRF_RTC_CC_CHANNEL_COUNT(1))
#else
#error Not enough RTC instances.
#endif

/**@brief Function for initializing the timer if it is not already initialized.
 */
static void timer_init(void)
{
    static bool m_timer_initialized;

    if (!m_timer_initialized)
    {
        if (!nrf_clock_lf_is_running())
        {
            nrf_clock_task_trigger(NRF_CLOCK_TASK_LFCLKSTART);
        }

        nrf_rtc_event_clear(RTC_STRUCT, NRF_RTC_EVENT_TICK);
        nrf_rtc_event_clear(RTC_STRUCT, NRF_RTC_EVENT_COMPARE_0);
        nrf_rtc_event_clear(RTC_STRUCT, NRF_RTC_EVENT_COMPARE_1);
        NRFX_IRQ_PRIORITY_SET(RTC_IRQn, 5);
        NRFX_IRQ_ENABLE(RTC_IRQn);
        nrf_rtc_prescaler_set(RTC_STRUCT, RTC_PRESCALER);
        nrf_rtc_task_trigger(RTC_STRUCT, NRF_RTC_TASK_CLEAR);
        nrf_rtc_task_trigger(RTC_STRUCT, NRF_RTC_TASK_START);
        nrf_rtc_int_enable(RTC_STRUCT, RTC_INTENSET_OVRFLW_Msk);

        m_timer_initialized = true;
    }
}

/**@brief Function for scheduling an RTC compare event.
 *
 * @param[in] cc_channel  Which of the RTC compare registers to use.
 * @param[in] cc_value    The ticks value at which to receive the event.
 */
static void rtc_update(uint32_t cc_channel, uint32_t cc_value)
{
    ASSERT(cc_channel < NRF_RTC_CC_CHANNEL_COUNT(RTC_INSTANCE));

    nrf_rtc_cc_set(RTC_STRUCT, cc_channel, cc_value);
    nrf_delay_us(31);
    nrf_rtc_event_clear(RTC_STRUCT, RTC_CHANNEL_EVENT_ADDR(cc_channel));
    nrf_rtc_int_enable(RTC_STRUCT, RTC_CHANNEL_INT_MASK(cc_channel));
}


/**@brief Function for activating a timer, so that it will be fired.
 *
 * This can happen multiple times before the actual timeout happens if the timeout is longer than
 * @ref MAX_TIMEOUT_TICKS.
 *
 * @param[in] p_timer        The timer to activate.
 * @param[in] timeout_ticks  The number of ticks until the timeout.
 *
 * @retval true   If the timer was activated.
 * @retval false  If the timer is already active.
 */
static void timer_activate(dfu_timer_t * p_timer, uint32_t timeout_ticks)
{
    NRF_LOG_DEBUG("timer_activate (0x%x)", p_timer);

    ASSERT(timeout_ticks <= MAX_TIMEOUT_TICKS);
    ASSERT(timeout_ticks >= NRF_BOOTLOADER_MIN_TIMEOUT_TICKS);
    uint32_t next_timeout_ticks = MIN(timeout_ticks, MAX_TIMEOUT_TICKS);
    uint32_t cc_value = RTC_WRAP(next_timeout_ticks + nrf_rtc_counter_get(RTC_STRUCT));
    p_timer->timeout  = timeout_ticks - next_timeout_ticks;

    if ((p_timer->timeout > 0) && (p_timer->timeout < NRF_BOOTLOADER_MIN_TIMEOUT_TICKS))
    {
        p_timer->timeout += NRF_BOOTLOADER_MIN_TIMEOUT_TICKS;
        cc_value         -= NRF_BOOTLOADER_MIN_TIMEOUT_TICKS;
    }

    rtc_update(p_timer->cc_channel, cc_value);
}


/**@brief Function for deactivating a timer, so that it will not fire.
 *
 * @param[in] p_timer  The timer to deactivate.
 *
 * @retval true   If the timer was deactivated.
 * @retval false  If the timer is already inactive.
 */
static void timer_stop(dfu_timer_t * p_timer)
{
    NRF_LOG_DEBUG("timer_stop (0x%x)", p_timer);
    nrf_rtc_int_disable(RTC_STRUCT, RTC_CHANNEL_INT_MASK(p_timer->cc_channel));
}


/**@brief Function for firing a timer.
 *
 * This can happen multiple times before the actual timeout happens if the timeout is longer than
 * @ref MAX_TIMEOUT_TICKS.
 * This function reactivates the timer if the timer is repeating, or if the timer has not yet
 * timed out. It then calls the callback if the timer (repeating or not) has timed out.
 *
 * @param[in] p_timer  The timer to fire.
 */
static void timer_fire(dfu_timer_t * p_timer)
{
    NRF_LOG_DEBUG("timer_fire (0x%x)", p_timer);

    if (p_timer->timeout != 0)
    {
        // The timer has not yet timed out.
        timer_activate(p_timer, p_timer->timeout);
        return;
    }

    if (p_timer->repeated_timeout != 0)
    {
        timer_activate(p_timer, p_timer->repeated_timeout);
    }

    if (p_timer->callback != NULL)
    {
        p_timer->callback();
    }
}


/**@brief Function for requesting a timeout.
 *
 * The timer will time out @p timeout_ticks ticks from now. When it times out, @p callback
 * will be called, and if @p p_timer->repeated_timeout is not 0, a new timeout will be scheduled.
 *
 * @param[in] p_timer        The timer to start.
 * @param[in] timeout_ticks  The number of ticks until the timeout.
 * @param[in] callback       The callback to call when the timer times out.
 */
static void timer_start(dfu_timer_t *                         p_timer,
                        uint32_t                              timeout_ticks,
                        nrf_bootloader_dfu_timeout_callback_t callback)
{
    timer_init(); // Initialize if needed.
    p_timer->callback = callback;
    timer_activate(p_timer, timeout_ticks);
}


/**@brief Interrupt handler for the RTC (Real Time Clock) used for the DFU timers.
 */
void RTC_IRQHandler(void)
{
    if (nrf_rtc_event_pending(RTC_STRUCT, NRF_RTC_EVENT_OVERFLOW))
    {
        m_counter_loops++;
        nrf_rtc_event_clear(RTC_STRUCT, NRF_RTC_EVENT_OVERFLOW);
    }

    for (uint32_t channel = 0; channel < 2; channel++)
    {
        if (nrf_rtc_event_pending(RTC_STRUCT, RTC_CHANNEL_EVENT_ADDR(channel)))
        {
            nrf_rtc_event_clear(RTC_STRUCT, RTC_CHANNEL_EVENT_ADDR(channel));
            timer_stop(&m_timers[channel]);
            timer_fire(&m_timers[channel]);
        }
    }
}


void nrf_bootloader_dfu_inactivity_timer_restart(uint32_t                              timeout_ticks,
                                                 nrf_bootloader_dfu_timeout_callback_t callback)
{
    timer_stop(mp_inactivity);
    if (timeout_ticks != 0)
    {
        timer_start(mp_inactivity, timeout_ticks, callback);
    }
}


void nrf_bootloader_wdt_feed_timer_start(uint32_t                              timeout_ticks,
                                         nrf_bootloader_dfu_timeout_callback_t callback)
{
    mp_wdt_feed->repeated_timeout = timeout_ticks;
    timer_start(mp_wdt_feed, timeout_ticks, callback);
}


uint32_t nrf_bootloader_dfu_timer_counter_get(void)
{
    return nrf_rtc_counter_get(RTC_STRUCT) + (m_counter_loops << 24);
}
