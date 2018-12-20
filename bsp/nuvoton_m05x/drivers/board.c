/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2014 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-11-23     Bright      first implementation
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "usart.h"

/**
 * @addtogroup NUVOTON_M05X
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
* @brief  Inserts a delay time.
* @param  nCount: specifies the delay time length.
* @retval None
*/
static void delay(__IO uint32_t nCount)
{
	/* Decrement nCount value */
	while (nCount != 0)
	{
		nCount--;
	}
}

static void rt_hw_system_init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    SYS_UnlockReg();
    /* Enable Internal RC 22.1184MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_OSC22M_EN_Msk);

    /* Waiting for Internal RC clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_OSC22M_STB_Msk);

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(BOARD_PLL_CLOCK);

    /* Set SysTick clock source to HCLK source divide 2 */
    CLK_SetSysTickClockSrc(CLK_CLKSEL0_STCLK_S_HCLK_DIV2);
    
    SYS_LockReg();
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
 * This function will initial Nuvoton board.
 */
void rt_hw_board_init()
{
	/* NVIC Configuration */
	NVIC_Configuration();

    /* Configure the system clock */
    rt_hw_system_init();
	/* Configure the SysTick */
	SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

	/* Initial usart deriver, and set console device */
	rt_hw_usart_init();
#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)M05X_SRAM_BEGIN, (void *)M05X_SRAM_END);
#endif
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

/*@}*/
