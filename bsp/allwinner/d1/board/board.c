/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "tick.h"

#include "drv_uart.h"
#include "encoding.h"
#include "stack.h"
#include "sbi.h"
#include "riscv.h"
#include "stack.h"

#include "hal_gpio.h"
#include "hal_clk.h"
#include "hal_uart.h"
#include "hal_dma.h"

#ifdef RT_USING_SMART
    #include "riscv_mmu.h"
    #include "mmu.h"
    #include "page.h"
    #include "lwp_arch.h"

    //这个结构体描述了buddy system的页分配范围
    rt_region_t init_page_region =
    {
        (rt_size_t)RT_HW_PAGE_START,
        (rt_size_t)RT_HW_PAGE_END
    };

    //内核页表
    volatile rt_size_t MMUTable[__SIZE(VPN2_BIT)] __attribute__((aligned(4 * 1024)));
    rt_mmu_info mmu_info;

#endif

//初始化BSS节区
void init_bss(void)
{
    unsigned int *dst;

    dst = &__bss_start;
    while (dst < &__bss_end)
    {
        *dst++ = 0;
    }
}

static void __rt_assert_handler(const char *ex_string, const char *func, rt_size_t line)
{
    rt_kprintf("(%s) assertion failed at function:%s, line number:%d \n", ex_string, func, line);
    asm volatile("ebreak":::"memory");
}

//BSP的C入口
void primary_cpu_entry(void)
{
    //初始化BSS
    init_bss();
    //关中断
    rt_hw_interrupt_disable();
    rt_assert_set_hook(__rt_assert_handler);
    //启动RT-Thread Smart内核
    entry();
}


//这个初始化程序由内核主动调用，此时调度器还未启动，因此在此不能使用依赖线程上下文的函数
void rt_hw_board_init(void)
{
#ifdef RT_USING_SMART
    rt_page_init(init_page_region);
    rt_hw_mmu_map_init(&mmu_info,(void *)USER_VADDR_START, USER_VADDR_TOP - USER_VADDR_START, (rt_size_t *)MMUTable, 0);
    rt_hw_mmu_kernel_map_init(&mmu_info, 0x00000000UL, USER_VADDR_START - 1);
    //将低1GB MMIO区域设置为无Cache与Strong Order访存模式
    MMUTable[0] &= ~PTE_CACHE;
    MMUTable[0] &= ~PTE_SHARE;
    MMUTable[0] |= PTE_SO;
    rt_hw_mmu_switch((void *)MMUTable);
#endif
    /* initalize interrupt */
    rt_hw_interrupt_init();
#ifdef RT_USING_HEAP
    rt_kprintf("heap: [0x%08x - 0x%08x]\n", (rt_ubase_t) RT_HW_HEAP_BEGIN, (rt_ubase_t) RT_HW_HEAP_END);
    /* initialize memory system */
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif
    /* init hal hardware */
    hal_clock_init();
    hal_gpio_init();
    hal_uart_init(0);
    hal_dma_init();

    /* init rtthread hardware */
    rt_hw_uart_init();
    rt_hw_tick_init();

#ifdef RT_USING_CONSOLE
    /* set console device */
    rt_console_set_device("uart");
#endif /* RT_USING_CONSOLE */

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

void rt_hw_cpu_reset(void)
{
    sbi_shutdown();
    while(1);
}
MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reboot, reset machine);
