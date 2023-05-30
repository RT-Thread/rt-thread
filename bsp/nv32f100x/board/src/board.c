/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-19     Quintin.Z    the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <finsh.h>
#include "sysinit.h"
#include "board.h"
#include "drv_uart.h"
#include "nv32.h"

#define portNVIC_SYSTICK_CTRL           ( ( volatile uint32_t *) 0xe000e010 )
#define portNVIC_SYSTICK_LOAD           ( ( volatile uint32_t *) 0xe000e014 )
#define portNVIC_INT_CTRL               ( ( volatile uint32_t *) 0xe000ed04 )
#define portNVIC_SYSPRI2                ( ( volatile uint32_t *) 0xe000ed20 )
#define portNVIC_SYSTICK_CLK            0x00000004
#define portNVIC_SYSTICK_INT            0x00000002
#define portNVIC_SYSTICK_ENABLE         0x00000001
#define portNVIC_PENDSVSET              0x10000000
#define portMIN_INTERRUPT_PRIORITY      ( 255UL )
#define portNVIC_PENDSV_PRI             ( portMIN_INTERRUPT_PRIORITY << 16UL )
#define portNVIC_SYSTICK_PRI            ( portMIN_INTERRUPT_PRIORITY << 24UL )

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define NV32_SRAM_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define NV32_SRAM_BEGIN    (__segment_end("HEAP"))
#else
extern int __bss_end;
#define NV32_SRAM_BEGIN    (&__bss_end)
#endif

/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
    rt_kprintf("\n\r Wrong parameter value detected on\r\n");
    rt_kprintf("       file  %s\r\n", file);
    rt_kprintf("       line  %d\r\n", line);

    while (1) ;
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
    *(portNVIC_SYSTICK_LOAD) = ( 40000000 / RT_TICK_PER_SECOND ) - 1UL;
    *(portNVIC_SYSTICK_CTRL) = portNVIC_SYSTICK_CLK | portNVIC_SYSTICK_INT | portNVIC_SYSTICK_ENABLE;

    rt_hw_uart_init();

    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif


#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif


#ifdef RT_USING_HEAP
    rt_system_heap_init((void*)NV32_SRAM_BEGIN, (void*)NV32_SRAM_END);
#endif




}

long cmd_reset(int argc, char** argv)
{
    NVIC_SystemReset();

    return 0;
}

FINSH_FUNCTION_EXPORT_ALIAS(cmd_reset, __cmd_reset, Reset Board.);



/*@}*/
