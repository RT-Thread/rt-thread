/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 * 2021-12-28     GuEe-GUI       add smp support
 * 2023-03-28     WangXiaoyao    sync works & memory layout fixups
 *                               code formats
 */

#include <rthw.h>
#include <rtthread.h>
#include <mm_aspace.h>

#include "board.h"
#include "drv_uart.h"

#include "cp15.h"
#include "mmu.h"
#include "mbox.h"
#include <mm_page.h>

#ifdef RT_USING_SMART
#include <lwp_arch.h>
#endif

extern size_t MMUTable[];

size_t gpio_base_addr = GPIO_BASE_ADDR;

size_t uart_base_addr = UART_BASE;

size_t gic_base_addr = GIC_V2_BASE;

size_t arm_timer_base = ARM_TIMER_BASE;

size_t pactl_cs_base = PACTL_CS_ADDR;

size_t stimer_base_addr = STIMER_BASE;

size_t mmc2_base_addr   = MMC2_BASE_ADDR;

size_t videocore_mbox = VIDEOCORE_MBOX;

size_t mbox_addr = MBOX_ADDR;

size_t wdt_base_addr = WDT_BASE;

uint8_t *mac_reg_base_addr = (uint8_t *)MAC_REG;

uint8_t *eth_send_no_cache = (uint8_t *)SEND_DATA_NO_CACHE;
uint8_t *eth_recv_no_cache = (uint8_t *)RECV_DATA_NO_CACHE;

#ifdef RT_USING_SMART
struct mem_desc platform_mem_desc[] = {
    {KERNEL_VADDR_START, KERNEL_VADDR_START + 0x0fffffff, (rt_size_t)ARCH_MAP_FAILED, NORMAL_MEM}
};
#else
struct mem_desc platform_mem_desc[] = {
    {0x00200000, (128ul << 20) - 1, 0x00200000, NORMAL_MEM},
    {0xFC000000, 0x000100000000 - 1, 0xFC000000, DEVICE_MEM},
};
#endif

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc)/sizeof(platform_mem_desc[0]);

void idle_wfi(void)
{
    asm volatile ("wfi");
}

/**
 * This function will initialize board
 */

extern size_t MMUTable[];
int rt_hw_gtimer_init(void);

rt_region_t init_page_region = {
    PAGE_START,
    PAGE_END,
};

/**
 *  Initialize the Hardware related stuffs. Called from rtthread_startup()
 *  after interrupt disabled.
 */
void rt_hw_board_init(void)
{
    extern void (*system_off)(void);
    extern void reboot(void);
    system_off = reboot;

    /* io device remap */
#ifdef RT_USING_SMART
    rt_hw_mmu_map_init(&rt_kernel_space, (void*)0xfffffffff0000000, 0x10000000, MMUTable, PV_OFFSET);
#else
    rt_hw_mmu_map_init(&rt_kernel_space, (void*)0x000400000000, 0x10000000, MMUTable, 0);
#endif
    rt_page_init(init_page_region);
    rt_hw_mmu_setup(&rt_kernel_space, platform_mem_desc, platform_mem_desc_size);

    /* map peripheral address to virtual address */
#ifdef RT_USING_HEAP
    /* initialize system heap */
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    //gpio
    gpio_base_addr = (size_t)rt_ioremap((void*)GPIO_BASE_ADDR, 0x1000);

    //pactl
    pactl_cs_base = (size_t)rt_ioremap((void*)PACTL_CS_ADDR, 0x1000);

    //stimer
    stimer_base_addr = (size_t)rt_ioremap((void*)STIMER_BASE, 0x1000);

    //mmc2_base_addr
    mmc2_base_addr = (size_t)rt_ioremap((void*)MMC2_BASE_ADDR, 0x1000);

    //mbox
    videocore_mbox = (size_t)rt_ioremap((void*)VIDEOCORE_MBOX, 0x1000);

    // mbox msg
    mbox = (volatile unsigned int *)rt_pages_alloc(0);

    //wdt
    wdt_base_addr = (size_t)rt_ioremap((void*)WDT_BASE, 0x1000);

    //mac
    mac_reg_base_addr = (void *)rt_ioremap((void*)MAC_REG, 0x80000);

    // eth data
    eth_send_no_cache = (void *)rt_pages_alloc(rt_page_bits(0x200000));
    eth_recv_no_cache = (void *)rt_pages_alloc(rt_page_bits(0x200000));

    /* initialize uart */
    rt_hw_uart_init();

    /* initialize timer for os tick */
    rt_hw_gtimer_init();

#ifdef RT_USING_CONSOLE
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif /* RT_USING_CONSOLE */

    rt_kprintf("heap: 0x%08x - 0x%08x\n", HEAP_BEGIN, HEAP_END);

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
    rt_thread_idle_sethook(idle_wfi);
}

#ifdef RT_USING_SMP
#include <gic.h>

void rt_hw_mmu_ktbl_set(unsigned long tbl);
void _secondary_cpu_entry(void);

static unsigned long cpu_release_paddr[] =
{
    [0] = 0xd8,
    [1] = 0xe0,
    [2] = 0xe8,
    [3] = 0xf0,
    [4] = 0x00
};

#ifndef RT_USING_SMART
static void *_remap(void *paddr, size_t size)
{
    int ret;
    static void *va = 0;
    size_t low_off = (size_t)paddr & ARCH_PAGE_MASK;
    if (va)
        return va + low_off;

    va = rt_kernel_space.start;
    while (1)
    {
        int rt_kmem_map_phy(void *va, void *pa, rt_size_t length, rt_size_t attr);
        ret = rt_kmem_map_phy(va, 0x0, ARCH_PAGE_SIZE, MMU_MAP_K_DEVICE);
        if (ret == RT_EOK)
        {
            break;
        }
        else
        {
            va += ARCH_PAGE_SIZE;
        }
    }
    return va + low_off;
}
#endif /* RT_USING_SMART */

void rt_hw_secondary_cpu_up(void)
{
    int i;
    void *release_addr;

    for (i = 1; i < RT_CPUS_NR && cpu_release_paddr[i]; ++i)
    {
#ifdef RT_USING_SMART
        release_addr = rt_ioremap((void *)cpu_release_paddr[i], sizeof(cpu_release_paddr[0]));
#else
        release_addr = _remap((void *)cpu_release_paddr[i], sizeof(cpu_release_paddr[0]));
#endif
        __asm__ volatile ("str %0, [%1]"::"rZ"((unsigned long)_secondary_cpu_entry + PV_OFFSET), "r"(release_addr));
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, release_addr, sizeof(release_addr));
        asm volatile ("dsb sy");
        asm volatile ("sev");
    }
}

void rt_hw_secondary_cpu_bsp_start(void)
{
    rt_hw_spin_lock(&_cpus_lock);

    rt_hw_mmu_ktbl_set((unsigned long)MMUTable);

    rt_hw_vector_init();

    arm_gic_cpu_init(0, 0);

    rt_hw_gtimer_init();

    rt_kprintf("\rcpu %d boot success\n", rt_hw_cpu_id());

    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    asm volatile ("wfe":::"memory", "cc");
}

#endif
