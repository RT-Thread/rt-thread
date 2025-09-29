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


struct mem_desc platform_mem_desc[] = {
    {0x80100000, 0x8FFFFFFF, 0x80000000, NORMAL_MEM},
    {0xD4000000, 0xDFFFFFFF, 0x44380000, DEVICE_MEM},
};

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc)/sizeof(platform_mem_desc[0]);

rt_region_t init_page_region = {
    (rt_size_t)PAGE_START,
    (rt_size_t)PAGE_END,
};

extern unsigned long MMUTable[];

static void rt_hw_timer_isr(int vector, void *param)
{
    rt_tick_increase();
    // epit_get_compare_event(HW_EPIT1);
}

int rt_hw_timer_init(void)
{
    uint32_t freq;

    // Make sure the timer is off.
    // HW_ARMGLOBALTIMER_CONTROL.B.TIMER_ENABLE = 0;

    // HW_ARMGLOBALTIMER_CONTROL.B.FCR0 =1;

    // HW_ARMGLOBALTIMER_CONTROL.B.FCR1 =0;

    // HW_ARMGLOBALTIMER_CONTROL.B.DBG_ENABLE =0;

    // // Clear counter.
    // HW_ARMGLOBALTIMER_COUNTER_HI_WR(0);
    // HW_ARMGLOBALTIMER_COUNTER_LO_WR(0);

    // // Now turn on the timer.
    // HW_ARMGLOBALTIMER_CONTROL.B.TIMER_ENABLE = 1;

    // freq = get_main_clock(IPG_CLK);

    // epit_init(HW_EPIT1, CLKSRC_IPG_CLK, freq / 1000000,
    //           SET_AND_FORGET, 10000, WAIT_MODE_EN | STOP_MODE_EN);

    // epit_counter_enable(HW_EPIT1, 10000, IRQ_MODE);

    // rt_hw_interrupt_install(IMX_INT_EPIT1, rt_hw_timer_isr, RT_NULL, "tick");
    // rt_hw_interrupt_umask(IMX_INT_EPIT1);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

/**
 * This function will initialize hardware board
 */
void rt_hw_board_init(void)
{
    // enable_neon_fpu();
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

    rt_hw_console_output("[rt_hw_board_init] rt_hw_board_init done!\n");
    rt_kprintf("[rt_hw_board_init] rt_kprintf works!\n");
    rt_hw_console_output("[rt_hw_board_init] rt_hw_board_init done!!\n");
}

/*@}*/
