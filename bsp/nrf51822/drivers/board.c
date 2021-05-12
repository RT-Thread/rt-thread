/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <rthw.h>
#include <rtthread.h>

#include <nrf51.h>
#include <nrf51_bitfields.h>

#include "board.h"
#include "uart.h"

/**
 * @addtogroup NRF51822
 */

/*@{*/
#define LFCLK_FREQUENCY           (32768UL)                                 /**< LFCLK frequency in Hertz, constant. */
#define RTC_FREQUENCY             (800UL)                                   /**< Required RTC working clock RTC_FREQUENCY Hertz. Changable. */
#define COUNTER_PRESCALER         ((LFCLK_FREQUENCY / RTC_FREQUENCY) - 1)   /* f = LFCLK/(prescaler + 1) */


/** @brief Function starting the internal LFCLK XTAL oscillator.
 */
void lfclk_config(void)
{
    NRF_CLOCK->LFCLKSRC            = (CLOCK_LFCLKSRC_SRC_Xtal << CLOCK_LFCLKSRC_SRC_Pos);
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_LFCLKSTART    = 1;
    while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0)
    {
        //Do nothing.
    }
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
}


/** @brief Function for configuring the RTC with TICK to 100Hz.
 */
void rtc_config(void)
{
    NVIC_EnableIRQ(RTC0_IRQn);                 // Enable Interrupt for the RTC in the core.
    NRF_RTC0->PRESCALER = COUNTER_PRESCALER;   // Set prescaler to a TICK of RTC_FREQUENCY.

    // Enable TICK event and TICK interrupt:
    NRF_RTC0->EVTENSET = RTC_EVTENSET_TICK_Msk;
    NRF_RTC0->INTENSET = RTC_INTENSET_TICK_Msk;
}


/** @brief: Function for handling the RTC0 interrupts.
 * Triggered on TICK and COMPARE0 match.
 */
void RTC0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    if ((NRF_RTC0->EVENTS_TICK != 0) &&
            ((NRF_RTC0->INTENSET & RTC_INTENSET_TICK_Msk) != 0))
    {
        NRF_RTC0->EVENTS_TICK = 0;

        rt_tick_increase();  //This function will notify kernel there is one tick passed
    }
    /* leave interrupt */
    rt_interrupt_leave();
}


/**
 * This function will initial NRF51822 board.
 */
void rt_hw_board_init()
{
    //lfclk_config();
    rtc_config();
    NRF_RTC0->TASKS_START = 1;
    /* Initial usart deriver, and set console device */
    rt_hw_uart_init();

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

/*@}*/
