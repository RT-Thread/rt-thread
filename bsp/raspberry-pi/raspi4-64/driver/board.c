/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 * 2021-12-28     GuEe-GUI       add smp support
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"

#include "mmu.h"
#include "gic.h"
#include "gtimer.h"
#include "cpuport.h"
#include "interrupt.h"
#include "mbox.h"

struct mem_desc platform_mem_desc[] =
{
    {0, 0x6400000, 0, NORMAL_MEM},
    {0xFE200000, 0xFE400000, 0xFE200000, DEVICE_MEM}, /* uart gpio */
    {0xFF800000, 0xFFA00000, 0xFF800000, DEVICE_MEM}, /* gic timer */
    {WDT_BASE, WDT_BASE + 0x1000, WDT_BASE, DEVICE_MEM}, /* wdt */
    {MBOX_ADDR, MBOX_ADDR + 0x200000, MBOX_ADDR, DEVICE_MEM}, /* mbox msg */
    {STIMER_BASE, STIMER_BASE + 0x200000, STIMER_BASE, DEVICE_MEM}, /* stimer */
    {MAC_BASE_ADDR, MAC_BASE_ADDR + 0x80000, MAC_BASE_ADDR, DEVICE_MEM}, /* mac */
    {MMC2_BASE_ADDR, MMC2_BASE_ADDR + 0x200000, MMC2_BASE_ADDR, DEVICE_MEM}, /* mmc */
    {ARM_TIMER_BASE, ARM_TIMER_BASE + 0x200000, ARM_TIMER_BASE, DEVICE_MEM}, /* arm timer */
    {SEND_DATA_NO_CACHE, SEND_DATA_NO_CACHE + 0x200000, SEND_DATA_NO_CACHE, NORMAL_MEM}, /* eth send */
    {RECV_DATA_NO_CACHE, RECV_DATA_NO_CACHE + 0x200000, RECV_DATA_NO_CACHE, NORMAL_MEM}, /* eth recv */
};

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc)/sizeof(platform_mem_desc[0]);

#if !defined(BSP_USING_CORETIMER) && !defined(RT_USING_SMP)
void rt_hw_timer_isr(int vector, void *parameter)
{
    ARM_TIMER_IRQCLR = 0;
    rt_tick_increase();
}
#endif

void rt_hw_timer_init(void)
{
#if defined(BSP_USING_CORETIMER) || defined(RT_USING_SMP)
    rt_hw_gtimer_init();
    core_timer_enable(0);
#else
    rt_uint32_t apb_clock = 0;
    rt_uint32_t timer_clock = 1000000;

    apb_clock = bcm271x_mbox_clock_get_rate(CORE_CLK_ID);
    ARM_TIMER_PREDIV = (apb_clock/timer_clock - 1);

    ARM_TIMER_RELOAD = 0;
    ARM_TIMER_LOAD   = 0;
    ARM_TIMER_IRQCLR = 1;
    ARM_TIMER_CTRL   = 0;

    ARM_TIMER_RELOAD = 1000000 / RT_TICK_PER_SECOND;
    ARM_TIMER_LOAD   = 1000000 / RT_TICK_PER_SECOND;

    /* 23-bit counter, enable interrupt, enable timer */
    ARM_TIMER_CTRL   = (1 << 1) | (1 << 5) | (1 << 7);

    rt_hw_interrupt_install(ARM_TIMER_IRQ, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(ARM_TIMER_IRQ);
#endif
}

void idle_wfi(void)
{
    asm volatile ("wfi");
}

/**
 *  Initialize the Hardware related stuffs. Called from rtthread_startup()
 *  after interrupt disabled.
 */
void rt_hw_board_init(void)
{
    extern void *MMUTable;
    rt_hw_mmu_map_init(&rt_kernel_space, (void*)0x80000000, 0x10000000, MMUTable, 0);
    rt_hw_mmu_setup(&rt_kernel_space, platform_mem_desc, platform_mem_desc_size);

    /* initialize hardware interrupt */
    rt_hw_interrupt_init(); // in libcpu/interrupt.c. Set some data structures, no operation on device

    /* initialize uart */
    rt_hw_uart_init();      // driver/drv_uart.c
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_kprintf("heap: 0x%08x - 0x%08x\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif
    /* initialize timer for os tick */
    rt_hw_timer_init();
    rt_thread_idle_sethook(idle_wfi);

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_SMP
    /* install IPI handle */
    rt_hw_ipi_handler_install(IRQ_ARM_IPI_KICK, rt_scheduler_ipi_handler);
    arm_gic_umask(0, IRQ_ARM_IPI_KICK);
#endif
}

#ifdef RT_USING_SMP
static unsigned long cpu_release_paddr[] =
{
    [0] = 0xd8,
    [1] = 0xe0,
    [2] = 0xe8,
    [3] = 0xf0,
    [4] = 0
};

void rt_hw_secondary_cpu_up(void)
{
    int i;
    extern void secondary_cpu_start(void);

    for (i = 1; i < RT_CPUS_NR && cpu_release_paddr[i]; ++i)
    {
        __asm__ volatile ("str %0, [%1]"::"rZ"((unsigned long)secondary_cpu_start), "r"(cpu_release_paddr[i]));
        rt_hw_dcache_flush_range(cpu_release_paddr[i], sizeof(cpu_release_paddr[i]));
        __DSB();
        __SEV();
    }
}

void secondary_cpu_c_start(void)
{
    int id;

    rt_hw_mmu_init();

    id = rt_hw_cpu_id();
    rt_hw_spin_lock(&_cpus_lock);

    arm_gic_cpu_init(0, platform_get_gic_cpu_base());
    rt_hw_vector_init();
    rt_hw_gtimer_local_enable();
    core_timer_enable(id);
    arm_gic_umask(0, IRQ_ARM_IPI_KICK);

    rt_kprintf("\rcall cpu %d on success\n", id);

    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    __WFE();
}
#endif

