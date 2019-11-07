/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-07-11     wangyq        the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "drv_uart.h"
#include "drv_gpio.h"
#include <lib_scu.h>
#include <lib_gpio.h>

/**
 * @addtogroup es8p
 */

/*@{*/

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
}

/*******************************************************************************
 * Function Name  : SystemClock_Configuration
 * Description    : Configures the System Clock.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void  SystemClock_Config(void)
{
    /* system clock 48MHz */
    PLLClock_Config(ENABLE, SCU_PLL_HRC, SCU_PLL_48M, ENABLE);
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
    /* ticks = SYS_CLK / RT_TICK_PER_SECOND */
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void systick_irq_cbk(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/*@}*/
/**
 * This function will initial es8p board.
 */
void rt_hw_board_init(void)
{
    /* NVIC Configuration */
    NVIC_Configuration();

    /*System Clock Configuration */
    SystemClock_Config();

    /* Configure the SysTick */
    SysTick_Configuration();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

/**
 * This function will delay for some us.
 *
 * @param us the delay time of us
 */
void rt_hw_us_delay(rt_uint32_t us)
{
    unsigned int start, now, delta, reload, us_tick;
    start = SysTick->VAL;
    reload = SysTick->LOAD;
    us_tick = SystemCoreClock / 1000000UL;
    do
    {
        now = SysTick->VAL;
        delta = start > now ? start - now : reload + start - now;
    }
    while (delta <  us_tick * us);
}
