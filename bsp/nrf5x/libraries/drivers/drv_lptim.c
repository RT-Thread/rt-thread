/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2022-08-09     forest-rain    first version
 */
#include <drv_lptim.h>
#include <nrf_rtc.h>

#include <nrf_gpio.h>

/* nrf5xx lptim use RTC(real timer counter) periph */
#define LPTIM_CC_CHANNEL             NRFX_RTC_INT_COMPARE0
#define RTC_TICK_FREQUENCE_HZ        (RT_TICK_PER_SECOND)     //  RTC tick frequence, in HZ
#define SYSTICK_CLOCK_HZ             (32768UL)
#define RTC_PRESCALER                ((uint32_t) (NRFX_ROUNDED_DIV(SYSTICK_CLOCK_HZ, RTC_TICK_FREQUENCE_HZ) - 1))

/**< Declaring an instance of nrf_drv_rtc for RTCx.
  Instance 0 is reserved for SoftDevice \ nimble.
*/
#ifndef RTC_INSTANCE_ID
#define RTC_INSTANCE_ID (2)
#endif

const nrfx_rtc_t rtc = NRFX_RTC_INSTANCE(RTC_INSTANCE_ID);

#define DBG_COMPARE_EVENT_OUTPUT  15//P0.15
#define DBG_TICK_EVENT_OUTPUT     16//P0.16

/** @brief: Function for handling the RTC0 interrupts.
 * Triggered on TICK and COMPARE0 match.
 */
static void nrfx_lptim_handler(nrfx_rtc_int_type_t int_type)
{
    if (int_type == NRFX_RTC_INT_COMPARE0)
    {
        nrf_gpio_pin_toggle(DBG_COMPARE_EVENT_OUTPUT);
    }
    else if (int_type == NRFX_RTC_INT_TICK)
    {
        //nrf_gpio_pin_toggle(DBG_TICK_EVENT_OUTPUT);

        /* enter interrupt */
        rt_interrupt_enter();

        rt_tick_increase();

        /* leave interrupt */
        rt_interrupt_leave();
    }
}

/**
 * This function get current count value of LPTIM
 *
 * @return the count vlaue
 */
rt_uint32_t nrfx_lptim_get_current_tick(void)
{
    return nrf_rtc_counter_get(rtc.p_reg);
}

/**
 * This function get the max value that RTC can count
 *
 * @return the max count
 */
rt_uint32_t nrfx_lptim_get_tick_max(void)
{
    return (nrfx_rtc_max_ticks_get(&rtc));
}

/**
 * This function start LPTIM with reload value
 *
 * @param reload The value that LPTIM count down from
 *
 * @return RT_EOK
 */
rt_err_t nrfx_lptim_start(rt_uint32_t delay_rtc_tick)
{
    nrfx_rtc_tick_disable(&rtc);

    // Set compare channel to trigger interrupt after delay_rtc_tick
    nrfx_rtc_cc_set(&rtc, LPTIM_CC_CHANNEL, (nrf_rtc_counter_get(rtc.p_reg) + delay_rtc_tick) & RTC_COUNTER_COUNTER_Msk, true);
    
    return (RT_EOK);
}

/**
 * This function stop RTC COMPARE0 Channel
 */
void nrfx_lptim_stop(void)
{
    nrfx_rtc_cc_disable(&rtc, LPTIM_CC_CHANNEL);
    // restart rtc tick for rt_tick_increase
    nrfx_rtc_tick_enable(&rtc, true);
}

/**
 * This function get the count clock of RTC
 *
 * @return the count clock frequency in Hz
 */
rt_uint32_t nrfx_lptim_get_countfreq(void)
{
    return RTC_TICK_FREQUENCE_HZ;
}

rt_tick_t pm_timer_next_timeout_tick(rt_uint8_t mode)
{
    switch (mode)
    {
        case PM_SLEEP_MODE_LIGHT:
        case PM_SLEEP_MODE_DEEP:
        //case PM_SLEEP_MODE_STANDBY:
            return rt_timer_next_timeout_tick();
    }

    return RT_TICK_MAX;
}

/**
 * This function initialize the rtc periph for lptim
 */
int nrfx_lptim_init(void)
{
    const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(RTC_INSTANCE_ID);
    nrf_clock_lf_src_set(NRF_CLOCK, (nrf_clock_lfclk_t)NRFX_CLOCK_CONFIG_LF_SRC);
    nrfx_clock_lfclk_start();

    // Initialize RTC instance
    nrfx_rtc_config_t config = NRFX_RTC_DEFAULT_CONFIG;
    config.prescaler = RTC_PRESCALER;

    nrfx_rtc_init(&rtc_instance, &config, nrfx_lptim_handler);
    nrfx_rtc_tick_enable(&rtc_instance, true);

    //Power on RTC instance
    nrfx_rtc_enable(&rtc);

    return RT_EOK;
}

INIT_DEVICE_EXPORT(nrfx_lptim_init);
