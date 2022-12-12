/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
#include "uart.h"

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define AM_SRAM_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define AM_SRAM_BEGIN    (__segment_end("HEAP"))
#else
extern int __bss_end;
#define AM_SRAM_BEGIN    (&__bss_end)
#endif

#define TICK_RATE_HZ  RT_TICK_PER_SECOND
#define SYSTICK_CLOCK_HZ  ( 32768UL )
#define WAKE_INTERVAL ( (uint32_t) ((SYSTICK_CLOCK_HZ / TICK_RATE_HZ)))

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
    /* Enable compare A interrupt in STIMER */
    am_hal_stimer_int_enable(AM_HAL_STIMER_INT_COMPAREA);

    /* Enable the timer interrupt in the NVIC, making sure to use the appropriate priority level */
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_STIMER_CMPR0);

    /* Configure the STIMER and run */
    am_hal_stimer_config(AM_HAL_STIMER_CFG_CLEAR | AM_HAL_STIMER_CFG_FREEZE);
    am_hal_stimer_compare_delta_set(0, WAKE_INTERVAL);
    am_hal_stimer_config(AM_HAL_STIMER_XTAL_32KHZ |
                         AM_HAL_STIMER_CFG_COMPARE_A_ENABLE);
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

    #ifndef RT_USING_RTC
    /* Run the RTC off the LFRC */
    am_hal_rtc_osc_select(AM_HAL_RTC_OSC_LFRC);

    /* Stop the XT and LFRC */
    am_hal_clkgen_osc_stop(AM_HAL_CLKGEN_OSC_XT);
    //am_hal_clkgen_osc_stop(AM_HAL_CLKGEN_OSC_LFRC);

    /* Disable the RTC */
    am_hal_rtc_osc_disable();
    #endif
}

/**
 * This is the deep power save.
 *
 */
void deep_power_save(void)
{
    am_hal_interrupt_master_disable();

    am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);

    am_hal_interrupt_master_enable();
}

/**
 * This function will initial APOLLO2 board.
 */
void rt_hw_board_init(void)
{
    /* Set the system clock to maximum frequency */
    am_hal_clkgen_sysclk_select(AM_HAL_CLKGEN_SYSCLK_MAX);

    /* Set the default cache configuration */
    am_hal_cachectrl_enable(&am_hal_cachectrl_defaults);

    /* Configure the board for low power operation */
    am_low_power_init();

    /* Config SysTick */
    SysTick_Configuration();

#ifdef RT_USING_IDLE_HOOK
    /* Set sleep deep mode */
    rt_thread_idle_sethook(deep_power_save);

#ifndef NO_FPU
    /* Enable the floating point module, and configure the core for lazy stacking */
    am_hal_sysctrl_fpu_enable();
    am_hal_sysctrl_fpu_stacking_enable(true);
#else
    am_hal_sysctrl_fpu_disable();
#endif

    /* Turn off unused Flash & SRAM */
    am_hal_pwrctrl_memory_enable(AM_HAL_PWRCTRL_MEMEN_FLASH512K);
    //am_hal_pwrctrl_memory_enable(AM_HAL_PWRCTRL_MEMEN_SRAM32K);

#endif

#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_HEAP
    rt_system_heap_init((void*)AM_SRAM_BEGIN, (void*)AM_SRAM_END);
#endif
}

/*@}*/
