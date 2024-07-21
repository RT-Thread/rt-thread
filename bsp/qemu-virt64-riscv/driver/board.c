/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
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
#include "mm_aspace.h"
#include "tick.h"

#include "drv_uart.h"
#include "encoding.h"
#include "stack.h"
#include "sbi.h"
#include "riscv.h"
#include "plic.h"
#include "stack.h"

#ifdef RT_USING_SMART
#include "riscv_mmu.h"
#include "mmu.h"
#include "page.h"
#include "lwp_arch.h"

rt_region_t init_page_region = {(rt_size_t)RT_HW_PAGE_START, (rt_size_t)RT_HW_PAGE_END};

extern size_t MMUTable[];

struct mem_desc platform_mem_desc[] = {
    {KERNEL_VADDR_START, (rt_size_t)RT_HW_PAGE_END - 1, (rt_size_t)ARCH_MAP_FAILED, NORMAL_MEM},
};

#define NUM_MEM_DESC (sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]))

#endif

void primary_cpu_entry(void)
{
    /* disable global interrupt */
    rt_hw_interrupt_disable();

    entry();
}

#define IOREMAP_SIZE (1ul << 30)

#ifndef ARCH_REMAP_KERNEL
#define IOREMAP_VEND USER_VADDR_START
#else
#define IOREMAP_VEND 0ul
#endif /* ARCH_REMAP_KERNEL */

void rt_hw_board_init(void)
{
#ifdef RT_USING_SMART
    /* init data structure */
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)(IOREMAP_VEND - IOREMAP_SIZE), IOREMAP_SIZE, (rt_size_t *)MMUTable, PV_OFFSET);

    /* init page allocator */
    rt_page_init(init_page_region);

    /* setup region, and enable MMU */
    rt_hw_mmu_setup(&rt_kernel_space, platform_mem_desc, NUM_MEM_DESC);
#endif

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

    plic_init();

    rt_hw_interrupt_init();

    rt_hw_uart_init();

#ifdef RT_USING_CONSOLE
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif /* RT_USING_CONSOLE */

    rt_hw_tick_init();

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_HEAP
    rt_kprintf("heap: [0x%08x - 0x%08x]\n", (rt_ubase_t)RT_HW_HEAP_BEGIN, (rt_ubase_t)RT_HW_HEAP_END);
#endif /* RT_USING_HEAP */
}

void rt_hw_cpu_reset(void)
{
    sbi_shutdown();

    while (1)
        ;
}
MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reboot, reset machine);

