/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2018-08-17     whj          add to new rt_console_set_device
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "usart.h"

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
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x20000000 */
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
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
 * This function will initial STM32 board.
 */
void rt_hw_board_init(void)
{
    /* NVIC Configuration */
    NVIC_Configuration();

    /* Configure the SysTick */
    SysTick_Config( SystemCoreClock / RT_TICK_PER_SECOND );

#ifdef RT_USING_HEAP
    rt_system_heap_init((void*)STM32_SRAM_BEGIN, (void*)STM32_SRAM_END);
#endif

    rt_components_board_init();

    rt_hw_usart_init();

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

}

/*@}*/
