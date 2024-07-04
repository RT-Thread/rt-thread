/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-10-26  huanghe      first commit
 * 2022-10-26  zhugengyu    support aarch64
 * 2023-04-13  zhugengyu    support RT-Smart
 * 2023-07-27  zhugengyu    update aarch32 gtimer usage
 *
 */

#include "rtconfig.h"
#include <rthw.h>
#include <rtthread.h>
#include <phytium_cpu.h>

#include <mmu.h>
#include <mm_aspace.h> /* TODO: why need application space when RT_SMART off */
#include <mm_page.h>
#include "phytium_interrupt.h"

#ifdef RT_USING_SMART
    #include <page.h>
    #include <lwp_arch.h>
#endif

#include <gicv3.h>
#if defined(TARGET_ARMV8_AARCH64)
    #include <psci.h>
    #include <gtimer.h>
    #include <cpuport.h>
#else
    #include <gtimer.h>
#endif
#include <interrupt.h>
#include <board.h>

#include "fearly_uart.h"
#include "fcpu_info.h"
#include "fiopad.h"

#ifdef RT_USING_SMP
    #include "fpsci.h"
#endif

extern FIOPadCtrl iopad_ctrl;
/* mmu config */
extern struct mem_desc platform_mem_desc[];
extern const rt_uint32_t platform_mem_desc_size;

void idle_wfi(void)
{
    asm volatile("wfi");
}

/**
 * This function will initialize board
 */
extern size_t MMUTable[];

rt_region_t init_page_region =
{
    PAGE_START,
    PAGE_END
};

void FIOMuxInit(void)
{
    FIOPadCfgInitialize(&iopad_ctrl, FIOPadLookupConfig(FIOPAD0_ID));
#ifdef RT_USING_SMART
    iopad_ctrl.config.base_address = (uintptr)rt_ioremap((void *)iopad_ctrl.config.base_address, 0x2000);
#endif

    return;
}

#if defined(TARGET_ARMV8_AARCH64) /* AARCH64 */

/* aarch64 use kernel gtimer */

#else /* AARCH32 */

/* aarch32 implment gtimer by bsp */
static rt_uint32_t timer_step;

#define CNTP_CTL_ENABLE     (1U << 0)    /* Enables the timer */
#define CNTP_CTL_IMASK      (1U << 1)    /* Timer interrupt mask bit */
#define CNTP_CTL_ISTATUS    (1U << 2)    /* The status of the timer */
void GenericTimerInterruptEnable(u32 id)
{
    u64 ctrl = gtimer_get_control();
    if (ctrl & CNTP_CTL_IMASK)
    {
        ctrl &= ~CNTP_CTL_IMASK;
        gtimer_set_control(ctrl);
    }
}

void GenericTimerStart(u32 id)
{
    u32 ctrl = gtimer_get_control(); /* get CNTP_CTL */

    if (!(ctrl & CNTP_CTL_ENABLE))
    {
        ctrl |= CNTP_CTL_ENABLE; /* enable gtimer if off */
        gtimer_set_control(ctrl); /* set CNTP_CTL */
    }
}

void rt_hw_timer_isr(int vector, void *parameter)
{
    gtimer_set_load_value(timer_step);
    rt_tick_increase();
}

int rt_hw_timer_init(void)
{
    rt_hw_interrupt_install(GENERIC_TIMER_NS_IRQ_NUM, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(GENERIC_TIMER_NS_IRQ_NUM);
    timer_step = gtimer_get_counter_frequency();
    FASSERT_MSG((timer_step > 1000000), "invalid freqency %ud", timer_step);
    timer_step /= RT_TICK_PER_SECOND;

    gtimer_set_load_value(timer_step);
    GenericTimerInterruptEnable(GENERIC_TIMER_ID0);
    GenericTimerStart(GENERIC_TIMER_ID0);
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

#endif

#ifdef RT_USING_SMP
    void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler);
#endif


#if defined(TARGET_ARMV8_AARCH64)
void rt_hw_board_aarch64_init(void)
{
    /* AARCH64 */
#if defined(RT_USING_SMART)
    /* 1. init rt_kernel_space table  (aspace.start = KERNEL_VADDR_START ,  aspace.size = ), 2. init io map range (rt_ioremap_start \ rt_ioremap_size) 3.   */
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)0xfffffffff0000000, 0x10000000, MMUTable, PV_OFFSET);
#else
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)0xffffd0000000, 0x10000000, MMUTable, 0);
#endif
    rt_page_init(init_page_region);

    rt_hw_mmu_setup(&rt_kernel_space, platform_mem_desc, platform_mem_desc_size);

    /* init memory pool */
#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    phytium_interrupt_init();

    rt_hw_gtimer_init();

    FEarlyUartProbe();

    FIOMuxInit();

    /* compoent init */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

    /* shell init */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    rt_thread_idle_sethook(idle_wfi);

#ifdef RT_USING_SMP
    FPsciInit();
    /* install IPI handle */
    rt_hw_interrupt_set_priority(RT_SCHEDULE_IPI, 16);
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);
#endif

}
#else

#if defined(TARGET_E2000D)
#define FT_GIC_REDISTRUBUTIOR_OFFSET 2
#endif

void rt_hw_board_aarch32_init(void)
{

#if defined(RT_USING_SMART)
    rt_uint32_t mmutable_p = 0;
    /* set io map range is 0xf0000000 ~ 0x10000000  , Memory Protection start address is 0xf0000000  - rt_mpr_size */
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)0xf0000000, 0x10000000, MMUTable, PV_OFFSET);
    rt_hw_init_mmu_table(platform_mem_desc,platform_mem_desc_size) ;
    mmutable_p = (rt_uint32_t)MMUTable + (rt_uint32_t)PV_OFFSET ;
    rt_hw_mmu_switch((void*)mmutable_p) ;
    rt_page_init(init_page_region);
    /* rt_kernel_space 在start_gcc.S 中被初始化，此函数将iomap 空间放置在kernel space 上 */
    rt_hw_mmu_ioremap_init(&rt_kernel_space, (void *)0xf0000000, 0x10000000);
    arch_kuser_init(&rt_kernel_space, (void *)0xffff0000);
#else

    rt_hw_mmu_map_init(&rt_kernel_space, (void *)0x80000000, 0x10000000, MMUTable, 0);
    rt_hw_init_mmu_table(platform_mem_desc,platform_mem_desc_size) ;
    rt_hw_mmu_init();
    rt_hw_mmu_ioremap_init(&rt_kernel_space, (void *)0x80000000, 0x10000000);
#endif

    /* init memory pool */
#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    extern int rt_hw_cpu_id(void);

    u32 cpu_id, cpu_offset = 0;
    GetCpuId(&cpu_id);

#if defined(FT_GIC_REDISTRUBUTIOR_OFFSET)
    cpu_offset = FT_GIC_REDISTRUBUTIOR_OFFSET ;
#endif
    FEarlyUartProbe();

    FIOMuxInit();

    arm_gic_redist_address_set(0, platform_get_gic_redist_base(), rt_hw_cpu_id());
    rt_hw_interrupt_init();

    /* compoent init */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

    /* shell init */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    rt_thread_idle_sethook(idle_wfi);

#ifdef RT_USING_SMP
    FPsciInit();
    /* install IPI handle */
    rt_hw_interrupt_set_priority(RT_SCHEDULE_IPI, 16);
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);
#endif

}
#endif

/**
 * This function will initialize hardware board
 */
void rt_hw_board_init(void)
{

#if defined(TARGET_ARMV8_AARCH64)
    rt_hw_board_aarch64_init();
#else
    rt_hw_board_aarch32_init();
#endif
}

