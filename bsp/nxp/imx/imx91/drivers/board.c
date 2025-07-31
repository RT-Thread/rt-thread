/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-10     Siwei Xu     Add i.MX91 SDK
 * 2025-09-15     Siwei Xu     Fix LPUART driver
 * 2025-10-08     Siwei Xu     Fix MMU Enable issues
 */
#include "board.h"

#include "serial.h"
#include "MIMX9131.h"

#include <gtimer.h>
#include <mm_aspace.h>
#include <mm_page.h>
#include <ioremap.h>
#include <mmu.h>

#include <limits.h>

#define DRAM_MAP_START KERNEL_BOOT_ADDR
#define DRAM_MAP_SIZE (64 * 1024 * 1024) // part of DRAM

#define MEM_DESC(vaddr_start, size, paddr_start, attr) \
    vaddr_start, (vaddr_start + size - 1uL), paddr_start, attr

static volatile unsigned long MMUTable[512*4] __attribute__((aligned(4 * 1024)));

struct mem_desc platform_mem_desc[] = {
    {MEM_DESC(DRAM_MAP_START, DRAM_MAP_SIZE, DRAM_MAP_START, NORMAL_MEM)},
    // {MEM_DESC(LPUART1_BASE, LPUART1_SIZE, LPUART1_BASE, DEVICE_MEM)}, // 0x4438_0000
    // {MEM_DESC(CCM_CTRL_BASE, CCM_CTRL_SIZE, CCM_CTRL_BASE, DEVICE_MEM)}, // 0x4445_8000
    // {MEM_DESC(GIC_DISTRIBUTOR_BASE, GIC_DISTRIBUTOR_SIZE, GIC_DISTRIBUTOR_BASE, DEVICE_MEM)}, // 0x4800_0000 
    // {MEM_DESC(GIC_REDISTRIBUTOR_BASE, GIC_REDISTRIBUTOR_SIZE, GIC_REDISTRIBUTOR_BASE, DEVICE_MEM)}, // 0x4804_0000
};

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc)/sizeof(platform_mem_desc[0]);

rt_region_t init_page_region = {
    (rt_size_t)PAGE_START,
    (rt_size_t)PAGE_END,
};

static rt_base_t get_sctlr_el1()
{
    rt_base_t sctlr = 0;
    __asm__ volatile ("mrs %0, sctlr_el1" : "=r"(sctlr));
    return sctlr;
}

/**
 * This function will initialize hardware board
 */
void rt_hw_board_init(void)
{
    rt_hw_mmu_map_init(&rt_kernel_space, (void*)0x080000000000, 0x10000000, (size_t *) MMUTable, 0);
    rt_page_init(init_page_region);
    rt_hw_mmu_setup(&rt_kernel_space, platform_mem_desc, platform_mem_desc_size);

#ifdef RT_USING_HEAP    
    /* initialize system heap */
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    /* map LPUART1/CCM_CTRL/GIC_DISTRIBUTOR/GIC_REDISTRIBUTOR virtual address to equals physical address */
    rt_ioremap_early((void*)LPUART1_BASE, GIC_REDISTRIBUTOR_BASE + GIC_REDISTRIBUTOR_SIZE - LPUART1_BASE);

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize uart */
    rt_hw_uart_init();

    /* initialize timer for os tick */
    rt_hw_gtimer_init();

    rt_components_board_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
    rt_kprintf("[rt_hw_board_init] rt_kprintf works!\n");
}

/*@}*/
