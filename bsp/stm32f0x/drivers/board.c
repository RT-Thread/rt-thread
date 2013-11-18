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
 * 2009-01-05     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

/**
 * @addtogroup STM32
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
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
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

/*******************************************************************************
* Function Name  : SysTick_Configuration
* Description    : The RCC feeds the Cortex System Timer (SysTick) external
*                  clock with the AHB clock (HCLK) divided by 8. The SysTick
*                  can work either with this clock or directly with the Cortex
*                  clock(HCLK), configurable in the SysTick Control and Status
*                  Register.
*
*                  if SysTick Clock Source is SysTick_CLKSource_HCLK:
*                      SysTick clock = HCLK
*                  if SysTick Clock Source is SysTick_CLKSource_HCLK_Div8:
*                      SysTick clock = HCLK / 8
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void SysTick_Configuration(void)
{
    RCC_ClocksTypeDef RCC_Clocks;

    RCC_GetClocksFreq(&RCC_Clocks);// get RCC clock
    /* set SysTick tick value */
    if (SysTick->CTRL & SysTick_CTRL_CLKSOURCE_Msk == SysTick_CLKSource_HCLK)
    {
        /* SysTick Timer Clock is RCC_Clocks.HCLK_Frequency */
        SysTick_Config(RCC_Clocks.HCLK_Frequency / RT_TICK_PER_SECOND);

    }
    else
    {
        /* SysTick Timer Clock is RCC_Clocks.HCLK_Frequency / 8 */
        SysTick_Config((RCC_Clocks.HCLK_Frequency >> 3) / RT_TICK_PER_SECOND);
    }
}

/**
 * This function will initial STM32 board.
 */
void rt_hw_board_init()
{
	/* NVIC Configuration */
	NVIC_Configuration();

	/* Configure the SysTick */
	SysTick_Configuration();

	//rt_hw_usart_init();
#ifdef RT_USING_CONSOLE
	rt_console_set_device(CONSOLE_DEVICE);
#endif
}

/*@}*/
