/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 * 2021-12-28     GuEe-GUI       add smp support
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"
#include "drv_timer.h"

#include "gtimer.h"
#include "cpuport.h"
#include "interrupt.h"
#include "mmu.h"
#include "raspi.h"

struct mem_desc platform_mem_desc[] =
{
    {0, 0x6400000, 0, NORMAL_MEM},
    {0xc00000, 0xc01000, 0xc00000, DEVICE_MEM}, /* mbox */
    {0x3f000000, 0x3f200000, 0x3f000000, DEVICE_MEM}, /* timer */
    {0x3f200000, 0x3f216000, 0x3f200000, DEVICE_MEM}, /* uart */
    {0x40000000, 0x40200000, 0x40000000, DEVICE_MEM}, /* core timer */
    {0x3F300000, 0x3F301000, 0x3F300000, DEVICE_MEM}, /* sdio */
    {0x3f804000, 0x3f805000, 0x3f804000, DEVICE_MEM}, /* i2c0 */
    {0x3f205000, 0x3f206000, 0x3f205000, DEVICE_MEM}, /* i2c1 */
};

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc)/sizeof(platform_mem_desc[0]);

#if defined(BSP_USING_CORETIMER) || defined(RT_USING_SMP)
static volatile rt_uint64_t timer_step;
#define BSP_USING_CORETIMER
#endif

void rt_hw_timer_isr(int vector, void *parameter)
{
#ifdef BSP_USING_CORETIMER
    rt_hw_set_gtimer_val(timer_step);
#else
    ARM_TIMER_IRQCLR = 0;
#endif
    rt_tick_increase();
}

rt_uint8_t core_timer_flag;

void rt_hw_timer_init(void)
{
    rt_hw_interrupt_install(IRQ_ARM_TIMER, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(IRQ_ARM_TIMER);
#ifdef BSP_USING_CORETIMER
    rt_hw_isb();
    timer_step = rt_hw_get_gtimer_frq();
    rt_hw_dsb();
    timer_step /= RT_TICK_PER_SECOND;

    rt_hw_gtimer_enable();
    rt_hw_set_gtimer_val(timer_step);
#ifdef RT_USING_SMP
    core_timer_enable(rt_hw_cpu_id());
#else
    core_timer_enable(0);
#endif
#else
    __DSB();
    /* timer_clock = apb_clock/(pre_divider + 1) */
    ARM_TIMER_PREDIV = (250 - 1);

    ARM_TIMER_RELOAD = 0;
    ARM_TIMER_LOAD   = 0;
    ARM_TIMER_IRQCLR = 0;
    ARM_TIMER_CTRL   = 0;

    ARM_TIMER_RELOAD = 10000;
    ARM_TIMER_LOAD   = 10000;

    /* 23-bit counter, enable interrupt, enable timer */
    ARM_TIMER_CTRL   = (1 << 1) | (1 << 5) | (1 << 7);
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
    /* initialize timer for os tick */
    rt_hw_timer_init();
    rt_thread_idle_sethook(idle_wfi);

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_kprintf("heap: 0x%08x - 0x%08x\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_SMP
    /* install IPI handle */
    rt_hw_ipi_handler_install(IRQ_ARM_MAILBOX, rt_scheduler_ipi_handler);
    rt_hw_interrupt_umask(IRQ_ARM_MAILBOX);
    enable_cpu_ipi_intr(0);
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
    int id = rt_hw_cpu_id();

    rt_hw_mmu_init();
    rt_hw_spin_lock(&_cpus_lock);

    rt_hw_vector_init();
    rt_hw_timer_init();
    enable_cpu_ipi_intr(id);

    rt_kprintf("\rcall cpu %d on success\n", id);

    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    __WFE();
}

#endif
