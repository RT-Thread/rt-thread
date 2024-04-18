/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-08     QT-one       first version
 */

#include <rtdbg.h>
#include "drv_common.h"
#ifdef RT_USING_SERIAL
    #include "drv_usart.h"
#endif

#ifdef RT_USING_FINSH
#include <finsh.h>
static void reboot(uint8_t argc, char **argv)
{
    rt_hw_cpu_reset();
}
MSH_CMD_EXPORT(reboot, Reboot System);
#endif /* RT_USING_FINSH */

/* SysTick configuration */
void rt_hw_systick_init(void)
{
    SYSTICK_ClockSourceConfig(SYSTICK_SRC_STCLK);
    SYSTICK_SetReloadValue(SystemCoreClock / 8 / RT_TICK_PER_SECOND);
    SYSTICK_IntConfig(ENABLE);
    SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
    SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);
}

/* This is the timer interrupt service routine */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/* This function is executed in case of error occurrence */
void _Error_Handler(char *s, int num)
{
    /* User can add his own implementation to report the error return state */
    LOG_E("Error_Handler at file:%s num:%d", s, num);
    while (1)
    {
    }
}

/* This function will initial HT32 board */
void rt_hw_board_init(void)
{
    /* Configure the System clock */
    rt_hw_board_clock_init();

    /* Configure the SysTick */
    rt_hw_systick_init();

    /* heap initialization */
#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    /* board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

    /* set the shell console output device */
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

}
