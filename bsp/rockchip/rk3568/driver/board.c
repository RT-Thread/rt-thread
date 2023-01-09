/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <mmu.h>
#include <psci.h>
#include <gicv3.h>
#include <gtimer.h>
#include <cpuport.h>
#include <interrupt.h>

#include <board.h>
#include <drv_uart.h>

struct mem_desc platform_mem_desc[] =
{
    {0x200000, 0x80000000, 0x200000, NORMAL_MEM},
    {UART0_MMIO_BASE, UART0_MMIO_BASE + 0x10000, UART0_MMIO_BASE, DEVICE_MEM},
    {UART1_MMIO_BASE, UART1_MMIO_BASE + 0x90000, UART1_MMIO_BASE, DEVICE_MEM},
    {GIC_PL600_DISTRIBUTOR_PPTR, GIC_PL600_DISTRIBUTOR_PPTR + 0x10000, GIC_PL600_DISTRIBUTOR_PPTR, DEVICE_MEM},
    {GIC_PL600_REDISTRIBUTOR_PPTR, GIC_PL600_REDISTRIBUTOR_PPTR + 0xc0000, GIC_PL600_REDISTRIBUTOR_PPTR, DEVICE_MEM},
};

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]);

void idle_wfi(void)
{
    __asm__ volatile ("wfi");
}

void rt_hw_board_init(void)
{
    extern void *MMUTable;
    rt_hw_mmu_map_init(&rt_kernel_space, (void*)0x80000000, 0x10000000, MMUTable, 0);
    rt_hw_mmu_setup(&rt_kernel_space, platform_mem_desc, platform_mem_desc_size);

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();
    /* initialize uart */
    rt_hw_uart_init();
    /* initialize timer for os tick */
    rt_hw_gtimer_init();

    rt_thread_idle_sethook(idle_wfi);

    // TODO porting to FDT-driven PSCI: arm_psci_init(PSCI_METHOD_SMC, RT_NULL, RT_NULL);

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

void reboot(void)
{
    // TODO poring to FDT to use new PSCI: arm_psci_system_reboot();
}
MSH_CMD_EXPORT(reboot, reboot...);

#ifdef RT_USING_SMP
rt_uint64_t rt_cpu_mpidr_early[] =
{
    [0] = 0x81000000,
    [1] = 0x81000100,
    [2] = 0x81000200,
    [3] = 0x81000300,
};

void rt_hw_secondary_cpu_up(void)
{
    int i;
    extern void secondary_cpu_start(void);

    for (i = 1; i < RT_CPUS_NR; ++i)
    {
        arm_psci_cpu_on(rt_cpu_mpidr_early[i], (rt_uint64_t)secondary_cpu_start);
    }
}

void secondary_cpu_c_start(void)
{
    rt_hw_mmu_init();
    rt_hw_spin_lock(&_cpus_lock);

    arm_gic_cpu_init(0, platform_get_gic_cpu_base());
    arm_gic_redist_init(0, platform_get_gic_redist_base());
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
