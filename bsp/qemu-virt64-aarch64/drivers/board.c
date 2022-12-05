/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-20     Bernard    the first version
 * 2018-11-22     Jesven     add rt_hw_spin_lock
 *                           add rt_hw_spin_unlock
 *                           add smp ipi init
 */

#include <rthw.h>
#include <rtthread.h>
#include <mmu.h>
#ifdef RT_USING_USERSPACE
#include <page.h>
#include <lwp_arch.h>
#endif
#include "board.h"

#ifdef RT_USING_FDT
#include "interrupt.h"
#include "dtb_node.h"
#include <psci_api.h>
#include <cpu.h>
#endif

#ifdef RT_USING_USERSPACE
struct mem_desc platform_mem_desc[] = {
    {KERNEL_VADDR_START, KERNEL_VADDR_START + 0x0fffffff, KERNEL_VADDR_START + PV_OFFSET, NORMAL_MEM}
};
#else
struct mem_desc platform_mem_desc[] = {
    {0x10000000, 0x50000000, 0x10000000, DEVICE_MEM},
    {0x40000000, 0x50000000, 0x40000000, NORMAL_MEM}
};
#endif

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc)/sizeof(platform_mem_desc[0]);

void idle_wfi(void)
{
    asm volatile ("wfi");
}

/**
 * This function will initialize board
 */

rt_mmu_info mmu_info;

extern size_t MMUTable[];

#ifdef RT_USING_USERSPACE
rt_region_t init_page_region = {
    PAGE_START,
    PAGE_END,
};
#endif

void rt_hw_board_init(void)
{
#ifdef RT_USING_USERSPACE
    rt_page_init(init_page_region);

    rt_hw_mmu_setup(platform_mem_desc, platform_mem_desc_size);

    rt_hw_mmu_map_init(&mmu_info, (void*)0xfffffffff0000000, 0x10000000, MMUTable, PV_OFFSET);

    arch_kuser_init(&mmu_info, (void*)0xffffffffffff0000);
#else
    rt_hw_mmu_map_init(&mmu_info, (void*)0x80000000, 0x10000000, MMUTable, 0);
    rt_hw_mmu_ioremap_init(&mmu_info, (void*)0x80000000, 0x10000000);
#endif

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize system heap */
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);

    /* support debug feature before components init */
    rt_hw_uart_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

#ifdef RT_USING_FDT
    // TODO 0x44000000 should be replace by a variable
    void * fdt_start = (void *)0x44000000 - PV_OFFSET;
    device_tree_setup(fdt_start);

#ifdef RT_USING_SMP
    rt_hw_cpu_init();
#else
    psci_init();
#endif /* RT_USING_SMP */
#endif

    rt_components_board_init();

    rt_thread_idle_sethook(idle_wfi);

#ifdef RT_USING_SMP
    /* install IPI handle */
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
#endif
}
