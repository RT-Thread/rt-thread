/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-1      Rbb666       first version
 */

#include "drv_common.h"

#ifdef RT_USING_SERIAL
    #include "drv_uart.h"
#endif

#define DBG_TAG "drv_common"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
static void reboot(uint8_t argc, char **argv)
{
    rt_hw_cpu_reset();
}
MSH_CMD_EXPORT(reboot, Reboot System);
#endif /* RT_USING_FINSH */

/**
 * this is the timer interrupt service routine.
 */
void SysTick_Handler_CB(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/* systick configuration */
void rt_hw_systick_init(void)
{
    Cy_SysTick_Init(CY_SYSTICK_CLOCK_SOURCE_CLK_CPU, SystemCoreClock / RT_TICK_PER_SECOND);
    Cy_SysTick_SetCallback(0, SysTick_Handler_CB);
    Cy_SysTick_EnableInterrupt();
}

/**
 * @brief  this function is executed in case of error occurrence.
 * @param  none
 * @retval none
 */
void _Error_Handler(char *s, int num)
{
    /* User can add his own implementation to report the HAL error return state */
    LOG_E("Error_Handler at file:%s num:%d", s, num);

    while (1)
    {
    }
}

/**
 * this function will delay for some us.
 *
 * @param us the delay time of us
 */
void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t start, now, delta, reload, us_tick;
    start = SysTick->VAL;
    reload = SysTick->LOAD;
    us_tick = SystemCoreClock / 1000000UL;

    do
    {
        now = SysTick->VAL;
        delta = start > now ? start - now : reload + start - now;
    }
    while(delta < us_tick * us);
}

/**
 * this function will initial ifx board.
 */
rt_weak void rt_hw_board_init()
{
    cy_bsp_all_init();

    /* systick init */
    rt_hw_systick_init();

    /* heap initialization */
    #if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
    #endif

    /* pin driver initialization is open by default */
    #ifdef RT_USING_PIN
    rt_hw_pin_init();
    #endif

    /* usart driver initialization is open by default */
    #ifdef RT_USING_SERIAL
    rt_hw_uart_init();
    #endif

    /* set the shell console output device */
    #if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
    #endif

    /* board underlying hardware initialization */
    #ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
    #endif
}
