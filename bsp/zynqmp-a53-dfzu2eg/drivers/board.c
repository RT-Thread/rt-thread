/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-11     liYony       the first version
 */

#include <mmu.h>
#include <board.h>
#include <mm_aspace.h>
#include <mm_page.h>
#include <drv_uart.h>
#include <gtimer.h>

extern size_t MMUTable[];

#ifdef RT_USING_SMART
struct mem_desc platform_mem_desc[] = {
    {KERNEL_VADDR_START, KERNEL_VADDR_START + 0x7FF00000 - 1, (rt_size_t)ARCH_MAP_FAILED, NORMAL_MEM}
};
#else
struct mem_desc platform_mem_desc[] =
{
    {0x00200000, 0x7FF00000 - 1, 0x00200000, NORMAL_MEM},
    {GIC400_DISTRIBUTOR_PPTR, GIC400_DISTRIBUTOR_PPTR + GIC400_SIZE - 1, GIC400_DISTRIBUTOR_PPTR, DEVICE_MEM},
    {GIC400_CONTROLLER_PPTR, GIC400_CONTROLLER_PPTR + GIC400_SIZE - 1, GIC400_CONTROLLER_PPTR, DEVICE_MEM},
};
#endif

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]);

void idle_wfi(void)
{
    asm volatile("wfi");
}

void rt_hw_board_init(void)
{
#ifdef RT_USING_SMART
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)0xfffffffff0000000, 0x10000000, MMUTable, PV_OFFSET);
#else
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)0xffffd0000000, 0x10000000, MMUTable, 0);
#endif
    rt_region_t init_page_region;
    init_page_region.start = PAGE_START;
    init_page_region.end = PAGE_END;
    rt_page_init(init_page_region);

    rt_hw_mmu_setup(&rt_kernel_space, platform_mem_desc, platform_mem_desc_size);

#ifdef RT_USING_HEAP
    /* initialize system heap */
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize uart */
    rt_hw_uart_init();

    /* initialize timer for os tick */
    rt_hw_gtimer_init();

    rt_thread_idle_sethook(idle_wfi);
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    rt_kprintf("heap: [0x%08x - 0x%08x]\n", HEAP_BEGIN, HEAP_END);

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
