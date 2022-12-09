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
#include "tick.h"

#include "drv_uart.h"
#include "encoding.h"
#include "stack.h"
#include "sbi.h"
#include "riscv.h"
#include "plic.h"
#include "stack.h"

#ifdef RT_USING_USERSPACE
#include "riscv_mmu.h"
#include "mmu.h"
#include "page.h"
#include "lwp_arch.h"

rt_region_t init_page_region = {(rt_size_t)RT_HW_PAGE_START, (rt_size_t)RT_HW_PAGE_END};

rt_mmu_info mmu_info;

extern size_t MMUTable[];

struct mem_desc platform_mem_desc[] = {
    {KERNEL_VADDR_START, KERNEL_VADDR_START + 0x10000000 - 1, KERNEL_VADDR_START + PV_OFFSET, NORMAL_MEM},
};

#define NUM_MEM_DESC (sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]))

#endif

void init_bss(void)
{
    unsigned int *dst;

    dst = &__bss_start;
    while (dst < &__bss_end)
    {
        *dst++ = 0;
    }
}

void primary_cpu_entry(void)
{
    extern void entry(void);

    /* disable global interrupt */
    init_bss();
    rt_hw_interrupt_disable();
    entry();
}

#define IOREMAP_SIZE (1ul << 30)

void rt_hw_board_init(void)
{
#ifdef RT_USING_USERSPACE
    rt_page_init(init_page_region);
    /* init mmu_info structure */
    rt_hw_mmu_map_init(&mmu_info, (void *)(USER_VADDR_START - IOREMAP_SIZE), IOREMAP_SIZE, (rt_size_t *)MMUTable, 0);
    // this API is reserved currently since PLIC etc had not been porting completely to MMU version
    rt_hw_mmu_kernel_map_init(&mmu_info, 0x00000000UL, 0x80000000);
    /* setup region, and enable MMU */
    rt_hw_mmu_setup(&mmu_info, platform_mem_desc, NUM_MEM_DESC);

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

