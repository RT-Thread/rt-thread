/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2017/11/08     Urey			first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <mmu.h>

#include "board.h"
#include "nuc97x.h"

static struct mem_desc hw_mem_desc[] =
{
    { 0x00000000, 0xFFFFFFFF,     0x00000000, RW_NCNB },     /* None cached for 4G memory */
    { 0x00000000, 0x04000000-1,   0x00000000, RW_CB   },     /* 64M cached DDR memory */
    { 0x80000000, 0x84000000-1,   0x80000000, RW_CNB },      /* Shadow DDR Map */
    { 0x3C000000, 0x3C00E000-1,   0x3C000000, RW_NCNB },     /* 56K SRAM memory */
    { 0xBC000000, 0xBC00E000-1,   0xBC000000, RW_NCNB }      /* 56K Shadow memory */
};

extern void rt_hw_systick_init(void);
extern void rt_hw_uart_init(void);

void rt_hw_board_init(void)
{
    rt_hw_mmu_init(&hw_mem_desc[0], sizeof(hw_mem_desc) / sizeof(hw_mem_desc[0]));
    rt_hw_cpu_dcache_enable();
    rt_hw_cpu_icache_enable();

    /* Enable GPIO Clock */
    outpw(REG_CLK_HCLKEN, 0x0527);
    outpw(REG_CLK_PCLKEN0, inpw(REG_CLK_PCLKEN0) | (1<<3));    //Enable GPIO engin clock.

    rt_hw_interrupt_init();
    rt_hw_systick_init();
    rt_hw_uart_init();

    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

#ifdef RT_USING_HEAP
    /* init memory system */
    rt_system_heap_init(BOARD_HEAP_START, BOARD_HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
} /* rt_hw_board_init */
