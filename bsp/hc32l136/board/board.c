 /*
 * Copyright (C) 2021, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-19     pjq          first version
 */



#include <rthw.h>
#include <rtthread.h>

#include "board.h"

/**
 * @addtogroup HC32
 */

/*@{*/

/**
 * @brief  BSP clock initialize.
 *         Set board system clock 24Mhz
 * @param  None
 * @retval None
 */
void rt_hw_board_clock_init(void)
{
    Sysctrl_SetRCHTrim(SysctrlRchFreq24MHz);
    Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);
}

/*******************************************************************************
 * Function Name  : SysTick_Configuration
 * Description    : Configures the SysTick for OS tick.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void  SysTick_Configuration(void)
{
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/RT_TICK_PER_SECOND);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initialize HC32 board.
 */
void rt_hw_board_init()
{
    /* Configure the System clock */
    rt_hw_board_clock_init();

    /* Configure the SysTick */
    SysTick_Configuration();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

void rt_hw_us_delay(rt_uint32_t us)
{
    uint32_t start, now, delta, reload, us_tick;
    start = SysTick->VAL;
    reload = SysTick->LOAD;
    us_tick = SystemCoreClock / 1000000UL;

    do{
        now = SysTick->VAL;
        delta = start > now ?  start - now : reload + start - now;
    }
    while(delta < us_tick * us);
}
/*@}*/
