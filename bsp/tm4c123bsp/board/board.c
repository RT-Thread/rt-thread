/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-24     Tanek        the first version
 * 2018-11-12     Ernest Chen  modify copyright
 * 2020-06-27     AHTYDHD      modify to adapt in TM4C123
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "board.h"

uint32_t SystemCoreClock;

/* this function set the system clock */
void SystemCoreClockUpdate(void)
{
    FPULazyStackingEnable();
    /* Set the clocking to run directly from the crystal. 50MHz*/
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                   SYSCTL_OSC_MAIN);
    SystemCoreClock = SysCtlClockGet();
}

/* this funtion set the Systick and enable systick int */
void SysTickConfig()
{
    SysTickDisable();
    SysTickPeriodSet(SystemCoreClock / RT_TICK_PER_SECOND);
    SysTickIntEnable();
    SysTickEnable();
}

/**
 * This function will initial your board.
 */
void rt_hw_board_init()
{
    /* System Clock Update */
    SystemCoreClockUpdate();
    /* System Tick Configuration */
    SysTickConfig();

#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif
#ifdef RT_USING_PIN
    rt_hw_pin_init();
#endif
#ifdef RT_USING_PWM
    rt_hw_pwm_init();
#endif
#ifdef RT_USING_I2C
    rt_hw_i2c_init();
#endif
    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
    /* set the console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

}

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_tick_increase();
    /* leave interrupt */
    rt_interrupt_leave();
}
