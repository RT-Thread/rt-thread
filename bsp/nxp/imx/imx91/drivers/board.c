/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-12     BruceOu    the first version
 */
#include "board.h"

#include "serial.h"

#include <gtimer.h>
#include <mm_aspace.h>
#include <mm_page.h>

#include <rtconfig.h>
#include <rtdevice.h>

#include <mmu.h>

#include <limits.h>

#define DRAM_MAP_START 0x80100000
#define DRAM_MAP_SIZE (64 * 1024 * 1024) // part of DRAM

#define PERIPH_MAP_START 0x44000000
#define PERIPH_MAP_SIZE (0x10000000)

#define PERIPH_VADDR_START 0xD4000000

#define MEM_DESC(vaddr_start, size, paddr_start, attr) \
    vaddr_start, (vaddr_start + size - 1uL), paddr_start, attr

struct mem_desc platform_mem_desc[] = {
    {MEM_DESC(KERNEL_VADDR_START, DRAM_MAP_SIZE, DRAM_MAP_START, NORMAL_MEM)},
    {MEM_DESC(PERIPH_VADDR_START, PERIPH_MAP_SIZE, PERIPH_MAP_START, DEVICE_MEM)},
};

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc)/sizeof(platform_mem_desc[0]);

rt_region_t init_page_region = {
    (rt_size_t)PAGE_START,
    (rt_size_t)PAGE_END,
};

extern unsigned long MMUTable[];

/**
 * This function will initialize hardware board
 */
void rt_hw_board_init(void)
{
    // disable_strict_align_check();
    rt_hw_earlycon_ioremap();

    rt_hw_earlycon_puts("rt_hw_board_init!\n");
    rt_hw_mmu_map_init(&rt_kernel_space, (void*)0x080000000000, 0x10000000, MMUTable, 0);
    rt_hw_earlycon_puts("[rt_hw_board_init] rt_hw_mmu_map_init done!\n");

    rt_hw_earlycon_print_hex("[rt_hw_board_init] rt_kernel_space.start: ", (rt_base_t) rt_kernel_space.start);
    rt_hw_earlycon_print_hex("[rt_hw_board_init] rt_kernel_space.size:  ", (rt_base_t) rt_kernel_space.size);

    rt_hw_earlycon_print_hex("[rt_hw_board_init] PAGE_START: ", (rt_base_t) PAGE_START);
    rt_hw_earlycon_print_hex("[rt_hw_board_init] PAGE_END:   ", (rt_base_t) PAGE_END);
    rt_page_init(init_page_region);

    rt_hw_earlycon_puts("[rt_hw_board_init] rt_hw_mmu_setup!\n");
    rt_hw_mmu_setup(&rt_kernel_space, platform_mem_desc, platform_mem_desc_size);

#ifdef RT_USING_HEAP
    /* initialize system heap */
    rt_hw_earlycon_puts("[rt_hw_board_init] rt_system_heap_init!\n");
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    /* initialize hardware interrupt */
    rt_hw_earlycon_puts("[rt_hw_board_init] rt_hw_interrupt_init!\n");
    rt_hw_interrupt_init();

    /* initialize uart */
    rt_hw_earlycon_puts("[rt_hw_board_init] rt_hw_uart_init!\n");
    rt_hw_uart_init();
    rt_hw_console_output("[rt_hw_board_init] rt_hw_uart_init done!\n");

    /* initialize timer for os tick */
    rt_hw_gtimer_init();

    rt_components_board_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
    rt_hw_console_output("[rt_hw_board_init] rt_console_set_device done!\n");

    rt_kprintf("[rt_hw_board_init] rt_kprintf works!\n");
}

/*@}*/
