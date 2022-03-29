/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 * 2021-07-31     GuEe-GUI       config the memory/io address map
 * 2021-09-11     GuEe-GUI       remove do-while in rt_hw_timer_isr
 * 2021-12-28     GuEe-GUI       add smp support
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include <mmu.h>
#include <gic.h>
#include <gicv3.h>
#include <psci.h>
#include <gtimer.h>
#include <cpuport.h>
#include <interrupt.h>

#include "drv_uart.h"

struct mem_desc platform_mem_desc[] =
{
    {0x40000000, 0x80000000, 0x40000000, NORMAL_MEM},
    {PL031_RTC_BASE, PL031_RTC_BASE + 0x1000, PL031_RTC_BASE, DEVICE_MEM},
    {PL011_UART0_BASE, PL011_UART0_BASE + 0x1000, PL011_UART0_BASE, DEVICE_MEM},
    {VIRTIO_MMIO_BASE, VIRTIO_MMIO_BASE + VIRTIO_MAX_NR * VIRTIO_MMIO_SIZE, VIRTIO_MMIO_BASE, DEVICE_MEM},
#ifdef BSP_USING_GICV2
    {GIC_PL390_DISTRIBUTOR_PPTR, GIC_PL390_DISTRIBUTOR_PPTR + 0x1000, GIC_PL390_DISTRIBUTOR_PPTR, DEVICE_MEM},
#endif
#ifdef BSP_USING_GICV3
    {GIC_PL500_DISTRIBUTOR_PPTR, GIC_PL500_DISTRIBUTOR_PPTR + 0x1000, GIC_PL500_DISTRIBUTOR_PPTR, DEVICE_MEM},
    {GIC_PL500_REDISTRIBUTOR_PPTR, GIC_PL500_REDISTRIBUTOR_PPTR + 0xf60000, GIC_PL500_REDISTRIBUTOR_PPTR, DEVICE_MEM},
#endif
};

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc)/sizeof(platform_mem_desc[0]);

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
    rt_hw_init_mmu_table(platform_mem_desc, platform_mem_desc_size);
    rt_hw_mmu_init();

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize uart */
    rt_hw_uart_init();
    /* initialize timer for os tick */
    rt_hw_gtimer_init();
    rt_thread_idle_sethook(idle_wfi);

    arm_psci_init(PSCI_METHOD_HVC, RT_NULL, RT_NULL);

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_kprintf("heap: [0x%08x - 0x%08x]\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_SMP
    /* install IPI handle */
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
    arm_gic_umask(0, IRQ_ARM_IPI_KICK);
#endif
}

void poweroff(void)
{
    arm_psci_system_off();
}
MSH_CMD_EXPORT(poweroff, poweroff...);

void reboot(void)
{
    arm_psci_system_reboot();
}
MSH_CMD_EXPORT(reboot, reboot...);

#ifdef RT_USING_SMP
void rt_hw_secondary_cpu_up(void)
{
    int i;
    extern void secondary_cpu_start(void);
    extern rt_uint64_t rt_cpu_mpidr_early[];

    for (i = 1; i < RT_CPUS_NR; ++i)
    {
        arm_psci_cpu_on(rt_cpu_mpidr_early[i], (uint64_t)(secondary_cpu_start));
    }
}

void secondary_cpu_c_start(void)
{
    rt_hw_mmu_init();
    rt_hw_spin_lock(&_cpus_lock);

    arm_gic_cpu_init(0, platform_get_gic_cpu_base());
#ifdef BSP_USING_GICV3
    arm_gic_redist_init(0, platform_get_gic_redist_base());
#endif
    rt_hw_vector_init();
    rt_hw_gtimer_local_enable();
    arm_gic_umask(0, IRQ_ARM_IPI_KICK);

    rt_kprintf("\rcall cpu %d on success\n", rt_hw_cpu_id());

    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    __WFE();
}
#endif
