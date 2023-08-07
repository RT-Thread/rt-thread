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
#include <ioremap.h>
#include <psci_api.h>

#include <board.h>
#include <drv_uart.h>

#include "mm_page.h"

#define PLATFORM_MEM_TALBE(va, size) va, ((unsigned long)va + size - 1)

struct mem_desc platform_mem_desc[] =
{
    {PLATFORM_MEM_TALBE(0x20000000,                    0x10000000), 0x20000000,                   NORMAL_MEM},
    {PLATFORM_MEM_TALBE(GRF_PMU_BASE,                  0x10000),    GRF_PMU_BASE,                 DEVICE_MEM},
    {PLATFORM_MEM_TALBE(GRF_SYS_BASE,                  0x10000),    GRF_SYS_BASE,                 DEVICE_MEM},
    {PLATFORM_MEM_TALBE(CRU_BASE,                      0x10000),    CRU_BASE,                     DEVICE_MEM},
    {PLATFORM_MEM_TALBE(UART0_MMIO_BASE,               0x10000),    UART0_MMIO_BASE,              DEVICE_MEM},
    {PLATFORM_MEM_TALBE(UART1_MMIO_BASE,               0x90000),    UART1_MMIO_BASE,              DEVICE_MEM},
    {PLATFORM_MEM_TALBE(GIC_PL600_DISTRIBUTOR_PPTR,    0x10000),    GIC_PL600_DISTRIBUTOR_PPTR,   DEVICE_MEM},
    {PLATFORM_MEM_TALBE(GIC_PL600_REDISTRIBUTOR_PPTR,  0xc0000),    GIC_PL600_REDISTRIBUTOR_PPTR, DEVICE_MEM},
#ifdef PKG_USING_RT_OPENAMP
    {PLATFORM_MEM_TALBE(AMP_SHARE_MEMORY_ADDRESS, AMP_SHARE_MEMORY_SIZE), AMP_SHARE_MEMORY_ADDRESS, NORMAL_MEM},
#endif /* PKG_USING_RT_OPENAMP */
};

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]);

void idle_wfi(void)
{
    __asm__ volatile ("wfi");
}

void rt_hw_board_init(void)
{
    extern unsigned long MMUTable[512];
    rt_region_t init_page_region;

    rt_hw_mmu_map_init(&rt_kernel_space, (void *) 0x20000000, 0xE0000000 - 1, MMUTable, 0);

    init_page_region.start = RT_HW_PAGE_START;
    init_page_region.end = RT_HW_PAGE_END;
    rt_page_init(init_page_region);

    rt_hw_mmu_setup(&rt_kernel_space, platform_mem_desc, platform_mem_desc_size);

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize uart */
    rt_hw_uart_init();

    /* initialize timer for os tick */
    rt_hw_gtimer_init();

    rt_thread_idle_sethook(idle_wfi);

    // TODO porting to FDT-driven PSCI: arm_psci_init(PSCI_METHOD_SMC, RT_NULL, RT_NULL);
    psci_init();

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
    if (psci_ops.system_reset)
    {
        psci_ops.system_reset();
    }
    else
    {
        void *cur_base = rt_ioremap((void *) CRU_BASE, 0x100);
        HWREG32(cur_base + 0x00D4) = 0xfdb9;
        HWREG32(cur_base + 0x00D8) = 0xeca8;
    }
}
MSH_CMD_EXPORT(reboot, reboot...);

static void print_cpu_id(int argc, char *argv[])
{
    rt_kprintf("rt_hw_cpu_id:%d\n", rt_hw_cpu_id());
}
MSH_CMD_EXPORT_ALIAS(print_cpu_id, cpuid, print_cpu_id);

#ifdef RT_USING_AMP
void start_cpu(int argc, char *argv[])
{
    rt_uint32_t status;
    if (psci_ops.cpu_on)
    {
        status = psci_ops.cpu_on(0x3, (rt_uint64_t) 0x7A000000);
        rt_kprintf("arm_psci_cpu_on 0x%X\n", status);
    }
}
MSH_CMD_EXPORT(start_cpu, start_cpu);

#ifdef RT_AMP_SLAVE
void rt_hw_cpu_shutdown(void)
{
    if (psci_ops.cpu_off)
    {
        psci_ops.cpu_off(0);
    }
}
#endif /* RT_AMP_SLAVE */
#endif /* RT_USING_AMP */

#if defined(RT_USING_SMP) || defined(RT_USING_AMP)
rt_uint64_t rt_cpu_mpidr_early[] =
{
    [0] = 0x80000000,
    [1] = 0x80000100,
    [2] = 0x80000200,
    [3] = 0x80000300,
    [RT_CPUS_NR] = 0
};
#endif

#ifdef RT_USING_SMP
void rt_hw_secondary_cpu_up(void)
{
    int i;
    extern void secondary_cpu_start(void);

    for (i = 1; i < RT_CPUS_NR; ++i)
    {
        arm_psci_cpu_on(rt_cpu_mpidr_early[i], (rt_uint64_t) secondary_cpu_start);
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
