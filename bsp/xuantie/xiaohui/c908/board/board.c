/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-23     Wangshun     first version
 * 2026-08-13     chenguohao   add xiaohui C908 rt-smart support
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "tick.h"
#include "drv_uart.h"
#include <interrupt.h>

#ifdef RT_USING_SMART
#include <mmu.h>
#include <riscv_mmu.h>
#include <mm_aspace.h>
#include <mm_page.h>
#include <ioremap.h>
#include <lwp_arch.h>
#endif

#ifdef RT_USING_SMART

rt_region_t init_page_region = { (rt_size_t)RT_HW_PAGE_START, (rt_size_t)RT_HW_PAGE_END };

extern size_t MMUTable[];

/* map the whole rt-smart managed physical range */
struct mem_desc platform_mem_desc[] = {
    { KERNEL_VADDR_START + MEM_PHYS_BASE,
      KERNEL_VADDR_START + MEM_PHYS_BASE + MEM_RTSMART_SIZE - 1,
      (rt_size_t)ARCH_MAP_FAILED, NORMAL_MEM },
};

#define NUM_MEM_DESC (sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]))

#endif /* RT_USING_SMART */

#ifndef ARCH_REMAP_KERNEL
#define IOREMAP_VEND USER_VADDR_START
#else
#define IOREMAP_VEND 0ul
#endif

#define IOREMAP_SIZE (1ul << 30)

/* satp modes supported by hardware, probed by the M-mode boot shim */
unsigned long g_mmu_modes_supported = 0;

static volatile rt_uint32_t *stimecmp_reg = RT_NULL;

void sbi_init(void)
{
    /* no SBI firmware on this platform */
}

void sbi_print_version(void)
{
}

void sbi_set_timer(rt_uint64_t stime_value)
{
    if (stimecmp_reg)
    {
        /* CLINT supervisor timecmp (memory mapped, S-mode writable),
         * one 64-bit register per hart at STIMECMP + hartid * 8 */
        int cpu = rt_hw_cpu_id();

        stimecmp_reg[cpu * 2] = (rt_uint32_t)(stime_value & 0xFFFFFFFF);
        stimecmp_reg[cpu * 2 + 1] = (rt_uint32_t)(stime_value >> 32);
    }
}

void sbi_console_putchar(int ch)
{
    (void)ch;
}

int sbi_console_getchar(void)
{
    return -1;
}

void sbi_shutdown(void)
{
    while (1);
}

int sbi_remote_sfence_vma(const unsigned long *hart_mask,
                          const unsigned long hart_mask_base,
                          unsigned long start, unsigned long size)
{
    __asm__ volatile("sfence.vma" ::: "memory");
#ifdef RT_USING_SMP
    /* ask the other harts to flush their TLB via IPI */
    {
        unsigned int mask = ((1U << RT_CPUS_NR) - 1) & ~(1U << rt_hw_cpu_id());

        if (mask)
        {
            rt_hw_ipi_send(RT_MAX_IPI - 1, mask);
        }
    }
#endif
    return 0;
}

void sbi_send_ipi(const unsigned long *hart_mask)
{
#ifdef RT_USING_SMP
    /* IPIs are raised directly through the CLINT SSIP registers by
     * rt_hw_ipi_send(), nothing to do here. */
#endif
}

void sbi_remote_fence_i(const unsigned long *hart_mask)
{
    __asm__ volatile("fence.i" ::: "memory");
#ifdef RT_USING_SMP
    {
        unsigned int mask = ((1U << RT_CPUS_NR) - 1) & ~(1U << rt_hw_cpu_id());

        if (mask)
        {
            rt_hw_ipi_send(RT_MAX_IPI - 1, mask);
        }
    }
#endif
}

#ifdef RT_USING_SMP
/* IPI handler on the remote hart: flush local TLB and instruction stream */
static void _tlb_flush_ipi(int vector, void *param)
{
    __asm__ volatile("sfence.vma" ::: "memory");
    __asm__ volatile("fence.i" ::: "memory");
}

int sbi_hsm_hart_start(unsigned long hart, unsigned long saddr, unsigned long priv)
{
    static volatile void *sreset_base = RT_NULL;
    volatile unsigned long *release = (volatile unsigned long *)(KERNEL_VADDR_START + MEM_PHYS_BASE + MEM_BOOT_SCRATCH_OFF + 8);

    if (hart == 0 || hart >= RT_CPUS_NR)
    {
        return -1;
    }

    if (sreset_base == RT_NULL)
    {
        sreset_base = rt_ioremap((void *)0x18030000UL /* XIAOHUI_SRESET_BASE */, 0x1000);
        if (sreset_base == RT_NULL)
        {
            return -1;
        }
    }

    /* secondary entry = M-mode boot shim (Reset_Handler) at the DRAM base */
    *(volatile unsigned long *)((char *)sreset_base + 0x10 + ((hart - 1) << 3)) = MEM_PHYS_BASE;

    /* release the shim park loop */
    *release |= (1UL << hart);
    __asm__ volatile("fence rw, rw" ::: "memory");

    /* release the hart from reset (xiaohui RESET controller);
     * harmless if the hart is already spinning in the park loop */
    *(volatile unsigned int *)sreset_base = 0x7f;

    return 0;
}
#endif /* RT_USING_SMP */

rt_uint64_t rt_hw_get_clock_timer_freq(void)
{
    /* xiaohui coretim runs at 25MHz */
    return 25000000ULL;
}

void init_bss(void)
{
    unsigned int *dst;

    dst = &__bss_start;
    while ((rt_ubase_t)dst < (rt_ubase_t)&__bss_end)
    {
        *dst++ = 0;
    }
}

/* lock-free UART output for the assert path: rt_kprintf may block on the
 * console lock, which can be part of the failure being reported */
static volatile rt_uint32_t *raw_uart = RT_NULL;

static void _raw_putc(char c)
{
    if (raw_uart == RT_NULL)
    {
        return;
    }
    while ((raw_uart[5] & 0x20) == 0);
    raw_uart[0] = (rt_uint32_t)(rt_uint8_t)c;
}

static void _raw_puts(const char *s)
{
    while (*s)
    {
        if (*s == '\n')
        {
            _raw_putc('\r');
        }
        _raw_putc(*s++);
    }
}

static void _raw_putdec(rt_size_t v)
{
    char buf[24];
    int i = 0;

    do
    {
        buf[i++] = (char)('0' + v % 10);
        v /= 10;
    } while (v && i < (int)sizeof(buf));
    while (i > 0)
    {
        _raw_putc(buf[--i]);
    }
}

static void __rt_assert_handler(const char *ex_string, const char *func, rt_size_t line)
{
    _raw_puts("(");
    _raw_puts(ex_string);
    _raw_puts(") assertion failed at function:");
    _raw_puts(func);
    _raw_puts(", line number:");
    _raw_putdec(line);
    _raw_puts(" (cpu");
    _raw_putdec((rt_size_t)rt_hw_cpu_id());
    _raw_puts(")\n");
    asm volatile("ebreak" ::: "memory");
}

void primary_cpu_entry(void)
{
    /* disable global interrupt */
    rt_hw_interrupt_disable();
    rt_assert_set_hook(__rt_assert_handler);
    entry();
}

void rt_hw_board_init(void)
{
#ifdef RT_USING_SMART
    /* init data structure */
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)(IOREMAP_VEND - IOREMAP_SIZE), IOREMAP_SIZE, (rt_size_t *)MMUTable, PV_OFFSET);

    /* init page allocator */
    rt_page_init(init_page_region);

    /* setup region, and enable MMU */
    rt_hw_mmu_setup(&rt_kernel_space, platform_mem_desc, NUM_MEM_DESC);
#endif

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

    /* initialize interrupt controller */
    rt_hw_interrupt_init();

#ifdef RT_USING_SMP
    /* boot hart IPI init (maps the CLINT SSIP page); secondary harts call
     * rt_hw_ipi_init() themselves in secondary_cpu_entry() */
    rt_hw_ipi_init();
    rt_hw_ipi_handler_install(RT_MAX_IPI - 1, _tlb_flush_ipi);
#endif

#ifdef RT_USING_SMART
    /* map CLINT for the direct-hw sbi_set_timer */
    stimecmp_reg = (volatile rt_uint32_t *)rt_ioremap(
        (void *)(XIAOHUI_CLINT_PHY_ADDR + XIAOHUI_STIMECMP_OFF), 0x1000);

    /* private UART mapping for the lock-free assert output path */
    raw_uart = (volatile rt_uint32_t *)rt_ioremap((void *)XIAOHUI_UART0_PHY_ADDR, 0x1000);

    /* fetch the satp mode probe result left by the M-mode boot shim */
    g_mmu_modes_supported = *(volatile unsigned long *)(KERNEL_VADDR_START + MEM_PHYS_BASE + MEM_BOOT_SCRATCH_OFF);
#endif

    /* uart driver */
    rt_hw_uart_init();

    /* tick timer */
    rt_hw_tick_init();

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif /* RT_USING_CONSOLE */

#ifdef RT_USING_SMART
    /* report active/supported MMU translation modes */
    {
        rt_ubase_t satp;

        __asm__ volatile("csrr %0, satp" : "=r"(satp));
        rt_kprintf("MMU: active Sv%d, hw support:%s%s%s\n",
                   ((satp >> 60) & 0xF) == 8 ? 39 : ((satp >> 60) & 0xF) == 9 ? 48
                                                : ((satp >> 60) & 0xF) == 10  ? 57
                                                                              : 0,
                   (g_mmu_modes_supported >> 8) & 1 ? " Sv39" : "",
                   (g_mmu_modes_supported >> 9) & 1 ? " Sv48" : "",
                   (g_mmu_modes_supported >> 10) & 1 ? " Sv57" : "");
    }
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

void rt_hw_cpu_reset(void)
{
    while (1);
}
MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reboot, reset machine);

