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

#ifdef RT_USING_SMART
struct mem_desc platform_mem_desc[] =
{
    {KERNEL_VADDR_START, KERNEL_VADDR_START + 0x1fffffff, (rt_size_t) ARCH_MAP_FAILED, NORMAL_MEM}
};
#else
struct mem_desc platform_mem_desc[] =
{
    {PLATFORM_MEM_TALBE(0x208000,                    0x20000000), 0x208000,                   NORMAL_MEM},
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
#endif

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]);

void idle_wfi(void)
{
    __asm__ volatile ("wfi");
}

void rt_hw_board_init(void)
{
    extern size_t MMUTable[];
    static rt_region_t init_page_region;
#ifdef RT_USING_SMART
    rt_hw_mmu_map_init(&rt_kernel_space, (void *) 0xfffffffff0000000, 0x10000000, MMUTable, PV_OFFSET);
#else
    rt_hw_mmu_map_init(&rt_kernel_space, (void *) 0x208000, 0xE0000000, MMUTable, 0);
#endif

    init_page_region.start = RT_HW_PAGE_START;
    init_page_region.end = RT_HW_PAGE_END;
    rt_page_init(init_page_region);
    rt_hw_mmu_setup(&rt_kernel_space, platform_mem_desc, platform_mem_desc_size);

    // rt_memset(RT_HW_HEAP_BEGIN, 0, 0x8000);
    // rt_hw_cpu_dcache_clean(RT_HW_HEAP_BEGIN, 0x8000);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);

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

    rt_kprintf("heap: [0x%08x - 0x%08x]\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);

#ifdef RT_USING_FDT
    void *fdt_start = (void *) 0x0A100000 - PV_OFFSET;
    device_tree_setup(fdt_start);

#ifdef RT_USING_SMP
    rt_hw_cpu_init();
#else
    psci_init();
#endif /* RT_USING_SMP */
#endif

    // psci_init();

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
void rt_hw_cpu_shutdown()
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
