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
/* RT_USING_COMPONENTS_INIT */
#ifdef  RT_USING_COMPONENTS_INIT
#include <components.h>
#endif
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

static void rt_hw_system_init(void)
{

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
	SysTick_Config(BUS_CLK_HZ / RT_TICK_PER_SECOND);

	/* Initial usart deriver, and set console device */
	rt_hw_usart_init();
#ifdef RT_USING_CONSOLE
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

	/* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

/*@}*/
