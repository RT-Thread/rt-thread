/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-14     Haley        first implementation
 */
#include "board.h"

#include <rtthread.h>
#include <rthw.h>

#include "am_mcu_apollo.h"
#include "hal/am_hal_clkgen.h"
#include "hal/am_hal_cachectrl.h"
#include "hw_uart.h"

#define TICK_RATE_HZ  RT_TICK_PER_SECOND
#define SYSTICK_CLOCK_HZ  ( 32768UL )
#define WAKE_INTERVAL ( (uint32_t) ((SYSTICK_CLOCK_HZ / TICK_RATE_HZ)) )

/**
 * This is the timer interrupt service routine.
 *
 */
void am_stimer_cmpr0_isr(void)
{
    /* Check the timer interrupt status */
    am_hal_stimer_int_clear(AM_HAL_STIMER_INT_COMPAREA);
    am_hal_stimer_compare_delta_set(0, WAKE_INTERVAL);
	
    if (rt_thread_self() != RT_NULL)
    {
    	/* enter interrupt */
    	rt_interrupt_enter();

    	rt_tick_increase();

    	/* leave interrupt */
    	rt_interrupt_leave();
    }
}

/**
 * This is the SysTick Configure.
 *
 */
void SysTick_Configuration(void)
{
		/* Set the main clk */
    am_hal_clkgen_sysclk_select(AM_HAL_CLKGEN_SYSCLK_MAX);
	
    /* Enable compare A interrupt in STIMER */
    am_hal_stimer_int_enable(AM_HAL_STIMER_INT_COMPAREA);

    /* Enable the timer interrupt in the NVIC */
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_STIMER_CMPR0);

    /* Configure the STIMER and run */
    am_hal_stimer_config(AM_HAL_STIMER_CFG_CLEAR | AM_HAL_STIMER_CFG_FREEZE);
    am_hal_stimer_compare_delta_set(0, WAKE_INTERVAL);
    am_hal_stimer_config(AM_HAL_STIMER_XTAL_32KHZ |
                         AM_HAL_STIMER_CFG_COMPARE_A_ENABLE);
}

/**
 * This is the CacheCtrl Enable.
 *
 */
void CacheCtrl_Enable(void)
{
    am_hal_cachectrl_enable(&am_hal_cachectrl_defaults);
}

/**
 * This is the low power operation.
 * This function enables several power-saving features of the MCU, and
 * disables some of the less-frequently used peripherals. It also sets the
 * system clock to 24 MHz.
 */
void am_low_power_init(void)
{
    /* Enable internal buck converters */
    am_hal_pwrctrl_bucks_init();

    /* Initialize for low power in the power control block */
    am_hal_pwrctrl_low_power_init();

    /* Turn off the voltage comparator as this is enabled on reset */
    am_hal_vcomp_disable();

    /* Run the RTC off the LFRC */
    am_hal_rtc_osc_select(AM_HAL_RTC_OSC_LFRC);

    /* Stop the XT and LFRC */
    am_hal_clkgen_osc_stop(AM_HAL_CLKGEN_OSC_XT);
    // am_hal_clkgen_osc_stop(AM_HAL_CLKGEN_OSC_LFRC);

    /* Disable the RTC */
    am_hal_rtc_osc_disable();
}

/**
 * This is the deep power save.
 *
 */
void deep_power_save(void)
{
		am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);
}

/**
 * This function will initial APOLLO2 board.
 */
void rt_hw_board_init(void)
{
		/* Set the clock frequency */
    SysTick_Configuration();
	
		/* Set the default cache configuration */
		CacheCtrl_Enable();

    /* Configure the board for low power operation */
    //am_low_power_init();
	
#ifdef RT_USING_IDLE_HOOK	
    rt_thread_idle_sethook(deep_power_save);  
#endif
	
#ifdef RT_USING_CONSOLE
		rt_hw_uart_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

/*@}*/
