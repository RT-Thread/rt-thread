/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "mm_aspace.h"
#include "tick.h"

#include "drv_uart.h"
#include "encoding.h"
#include "stack.h"
#include "sbi.h"
#include "riscv.h"
#include "plic.h"
#include "stack.h"

#ifdef RT_USING_SMP
#include "interrupt.h"
#endif /* RT_USING_SMP */

#ifdef RT_USING_OFW
#include <drivers/ofw_fdt.h>
#endif

#ifdef RT_USING_DM
#include <drivers/core/power.h>
#endif

#ifdef RT_USING_SMART
#include "riscv_mmu.h"
#include "mmu.h"
#include "page.h"
#include "lwp_arch.h"

rt_region_t init_page_region = {(rt_size_t)RT_HW_PAGE_START, (rt_size_t)RT_HW_PAGE_END};

extern size_t MMUTable[];

struct mem_desc platform_mem_desc[] = {
    {KERNEL_VADDR_START, (rt_size_t)RT_HW_PAGE_END - 1, (rt_size_t)ARCH_MAP_FAILED, NORMAL_MEM},
};

#define NUM_MEM_DESC (sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]))

#endif

#ifdef RT_USING_OFW
#define QEMU_RISCV_FDT_MAX_SIZE (256 * 1024)

extern rt_ubase_t boot_fdt_addr;

static rt_align(8) rt_uint8_t qemu_riscv_fdt[QEMU_RISCV_FDT_MAX_SIZE];
static void *qemu_riscv_fdt_ptr;

static void qemu_riscv_fdt_copy_early(void)
{
    void *fdt;
    rt_size_t fdt_size;

    if (!boot_fdt_addr)
    {
        rt_kprintf("OFW: boot FDT address is empty\n");
        return;
    }

#ifdef RT_USING_SMART
    fdt = (void *)(boot_fdt_addr - PV_OFFSET);
#else
    fdt = (void *)boot_fdt_addr;
#endif

    if (fdt_check_header(fdt))
    {
        rt_kprintf("OFW: invalid boot FDT at %p\n", (void *)boot_fdt_addr);
        return;
    }

    fdt_size = fdt_totalsize(fdt);
    if (fdt_size > sizeof(qemu_riscv_fdt))
    {
        rt_kprintf("OFW: boot FDT is too large: %u > %u\n",
                   (unsigned int)fdt_size, (unsigned int)sizeof(qemu_riscv_fdt));
        return;
    }

    rt_memcpy(qemu_riscv_fdt, fdt, fdt_size);
    qemu_riscv_fdt_ptr = qemu_riscv_fdt;
}

static void qemu_riscv_ofw_init(void)
{
    rt_err_t err;

    if (!qemu_riscv_fdt_ptr)
    {
        return;
    }

    err = rt_fdt_prefetch(qemu_riscv_fdt_ptr);
    if (err)
    {
        rt_kprintf("OFW: FDT prefetch failed: %d\n", err);
        return;
    }

    rt_fdt_scan_chosen_stdout();
    rt_fdt_scan_memory();

    err = rt_fdt_unflatten();
    if (err)
    {
        rt_kprintf("OFW: FDT unflatten failed: %d\n", err);
    }
}
#endif

static void qemu_riscv_machine_shutdown(void)
{
    sbi_shutdown();

    while (1)
        ;
}

rt_uint64_t rt_hw_get_clock_timer_freq(void)
{
    return 10000000ULL;
}

void primary_cpu_entry(void)
{
    /* disable global interrupt */
    rt_hw_interrupt_disable();

    entry();
}

#define IOREMAP_SIZE (1ul << 30)

#ifndef ARCH_REMAP_KERNEL
#define IOREMAP_VEND USER_VADDR_START
#else
#define IOREMAP_VEND 0ul
#endif /* ARCH_REMAP_KERNEL */

void rt_hw_board_init(void)
{
#ifdef RT_USING_SMART
    /* init data structure */
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)(IOREMAP_VEND - IOREMAP_SIZE), IOREMAP_SIZE, (rt_size_t *)MMUTable, PV_OFFSET);

#ifdef RT_USING_OFW
    qemu_riscv_fdt_copy_early();
#endif

    /* init page allocator */
    rt_page_init(init_page_region);

    /* setup region, and enable MMU */
    rt_hw_mmu_setup(&rt_kernel_space, platform_mem_desc, NUM_MEM_DESC);
#endif

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

#ifdef RT_USING_OFW
    qemu_riscv_ofw_init();
#endif

#ifdef RT_USING_DM
    rt_dm_machine_shutdown = qemu_riscv_machine_shutdown;
    rt_dm_machine_reset = qemu_riscv_machine_shutdown;
#endif

    plic_init();

    rt_hw_interrupt_init();

    rt_hw_uart_init();

#ifdef RT_USING_CONSOLE
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif /* RT_USING_CONSOLE */

    rt_hw_tick_init();

#ifdef RT_USING_SMP
    /* ipi init */
    rt_hw_ipi_init();
#endif /* RT_USING_SMP */

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_HEAP
    rt_kprintf("heap: [0x%08x - 0x%08x]\n", (rt_ubase_t)RT_HW_HEAP_BEGIN, (rt_ubase_t)RT_HW_HEAP_END);
#endif /* RT_USING_HEAP */
}

#ifndef RT_USING_DM
void rt_hw_cpu_reset(void)
{
    qemu_riscv_machine_shutdown();
}
MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reboot, reset machine);
#endif
