/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-29     JasonJia     first implementation
 */


#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "clk.h"
#include "drv_usart.h"
#include "sysram.h"
#ifdef PKG_USING_EASYLOGGER
#include "elog.h"
#endif

/**
 * @addtogroup HC32
 */

/*@{*/

/*******************************************************************************
* Function Name  : Ddl_AssertHook
* Description    : Reports the name of the source file and the source line number
*                  where the assert error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void Ddl_AssertHook(uint8_t* file, uint32_t line)
{
    rt_kprintf("\n\r Wrong parameter value detected on\r\n");
    rt_kprintf("       file  %s\r\n", file);
    rt_kprintf("       line  %d\r\n", line);

    while (1) ;
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
    stc_clk_freq_t stcClkFreq;
    rt_uint32_t cnts;

    Clk_GetClockFreq(&stcClkFreq);

    cnts = (rt_uint32_t)stcClkFreq.sysclkFreq / RT_TICK_PER_SECOND;

    SysTick_Config(cnts);
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
void rt_hw_board_init()
{
    /* Configure the SysTick */
    SysTick_Configuration();

#ifdef RT_USING_CONSOLE
    /* Init console before other hardware's initialization. */
    hc32_hw_console_init(RT_CONSOLE_DEVICE_NAME);
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
    #ifdef PKG_USING_EASYLOGGER
        elog_init();
        elog_set_fmt(ELOG_LVL_ASSERT,ELOG_FMT_ALL);
        elog_set_fmt(ELOG_LVL_ERROR,ELOG_FMT_ALL);
        elog_set_fmt(ELOG_LVL_WARN,ELOG_FMT_ALL);
        elog_set_fmt(ELOG_LVL_INFO,ELOG_FMT_ALL);
        elog_set_fmt(ELOG_LVL_DEBUG,ELOG_FMT_ALL);
        elog_set_fmt(ELOG_LVL_VERBOSE,ELOG_FMT_ALL);
        elog_output_lock_enabled(RT_FALSE);
        elog_set_text_color_enabled(RT_TRUE);
        elog_start();
    #endif
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_HEAP
    #ifdef RT_USING_EXT_SRAM
        /* TBD. */
    #else
        /* Use high speed sram as high speed heap. */
        rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);

        /* Use system sram as system heap. */
        sysram_init((void *)SYS_HEAP_BEGIN, (void *)SYS_HEAP_END);
    #endif
#endif

}


/*@}*/
