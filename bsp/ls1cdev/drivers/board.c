/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-06-25     Bernard      first version
 * 2011-08-08     lgnq            modified for Loongson LS1B
 * 2015-07-06     chinesebear  modified for Loongson LS1C
 * 2019-12-04     Jiaxun Yang  Adapt new generic MIPS code
 */

#include <rtthread.h>
#include <rthw.h>
#include <mips.h>

#include "board.h"
#include "drv_uart.h"
#include "ls1c.h"

extern unsigned char __bss_end;

#define RT_HW_HEAP_END    (0x80000000 + MEM_SIZE)


/**
 * This function will initial sam7s64 board.
 */
void rt_hw_board_init(void)
{
    /* init hardware interrupt */
    rt_hw_exception_init();
    
    /* init hardware interrupt */
    rt_hw_interrupt_init();
    
#ifdef RT_USING_HEAP
    rt_system_heap_init((void*)&__bss_end, (void*)RT_HW_HEAP_END);
#endif

#ifdef RT_USING_SERIAL
    /* init hardware UART device */
    rt_hw_uart_init();
#endif

#ifdef RT_USING_CONSOLE
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    /* init operating system timer */
    rt_hw_timer_init();

#ifdef RT_USING_FPU
    /* init hardware fpu */
    rt_hw_fpu_init();
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

    rt_kprintf("current sr: 0x%08x\n", read_c0_status());
}

/*@}*/
