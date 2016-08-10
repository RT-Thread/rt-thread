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
 * 
 */

#include <stdio.h>
#include <rthw.h>
#include <rtthread.h>
#include "fsl_clock_manager.h"

#include "board.h"
#include "board_app.h"

extern void rt_hw_uart_init(void);

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
 * Function Name  : SysTick_Configuration
 * Description    : Configures the SysTick for OS tick.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void  SysTick_Configuration(void)
{
    //SystemCoreClockUpdate();              /* Update Core Clock Frequency        */
   int i;
  for (i = 0; i < PORT_INSTANCE_COUNT; i++)
  {
    CLOCK_SYS_EnablePortClock(i);
  }
    /* Init board clock */
    BOARD_ClockInit();
    SysTick_Config(SystemCoreClock/RT_TICK_PER_SECOND); /* Generate interrupt each 1 ms       */
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
 * This function will initial Tower board.
 */
void rt_hw_board_init()
{
    /* NVIC Configuration */
    NVIC_Configuration();

    /* Configure the SysTick */
    SysTick_Configuration();

    dbg_uart_init();
    
    rt_hw_uart_init();

#ifdef RT_USING_CONSOLE
    rt_console_set_device(CONSOLE_DEVICE);
#endif
}

//for kernel debug when console not registered
//must call after the debuginit
void rt_hw_console_output(const char *str)
{
    printf("\r%s\r\n",str);
}

/*@}*/
