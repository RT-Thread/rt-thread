/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"

#include "cp15.h"
#include "mmu.h"
#include "mbox.h"

#ifdef RT_USING_USERSPACE
#include <page.h>
#include <lwp_arch.h>
#endif

rt_mmu_info mmu_info;
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

void* mac_reg_base_addr = (void *)MAC_REG;

void* eth_send_no_cache = (void *)SEND_DATA_NO_CACHE;
void* eth_recv_no_cache = (void *)RECV_DATA_NO_CACHE;

#ifdef RT_USING_USERSPACE
struct mem_desc platform_mem_desc[] = {
    {KERNEL_VADDR_START, KERNEL_VADDR_START + 0x0fffffff, KERNEL_VADDR_START + PV_OFFSET, NORMAL_MEM}
};
#else
struct mem_desc platform_mem_desc[] = {
    {0x0, 0x6400000, 0x0, NORMAL_MEM},
    {0xFE000000, 0xFE400000, 0xFE000000, DEVICE_MEM},//uart gpio
    {0xFF800000, 0xFFA00000, 0xFF800000, DEVICE_MEM} //gic
};
#endif

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc)/sizeof(platform_mem_desc[0]);

void rt_hw_timer_isr(int vector, void *parameter)
{
    ARM_TIMER_IRQCLR = 0;
    rt_tick_increase();
}

void rt_hw_timer_init(void)
{
    rt_hw_interrupt_install(ARM_TIMER_IRQ, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(ARM_TIMER_IRQ);
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
}

void idle_wfi(void)
{
    asm volatile ("wfi");
}

#ifdef RT_USING_USERSPACE
rt_region_t init_page_region = {
    (uint32_t)(KERNEL_VADDR_START + 32 * 1024 * 1024),
    (uint32_t)(KERNEL_VADDR_START + 64 * 1024 * 1024),
};
#endif

/**
 *  Initialize the Hardware related stuffs. Called from rtthread_startup() 
 *  after interrupt disabled.
 */
void rt_hw_board_init(void)
{
    /* io device remap */
#ifdef RT_USING_USERSPACE
    rt_hw_mmu_map_init(&mmu_info, (void*)0xf0000000, 0x10000000, MMUTable, PV_OFFSET);

    rt_page_init(init_page_region);
    rt_hw_mmu_ioremap_init(&mmu_info, (void*)0xf0000000, 0x10000000);

    arch_kuser_init(&mmu_info, (void*)0xffff0000);
#else
    rt_hw_mmu_map_init(&mmu_info, (void*)GPIO_BASE_ADDR, 0x10000000, MMUTable, 0);
#endif

    //gpio
    gpio_base_addr = (size_t)rt_hw_kernel_phys_to_virt((void*)GPIO_BASE_ADDR, 0x1000);
    //uart
    //uart_base_addr = (size_t)rt_hw_kernel_phys_to_virt((void*)UART_BASE, 0x1000);
    //aux
    //aux_addr = (size_t)rt_hw_kernel_phys_to_virt((void*)AUX_BASE_ADDR, 0x1000);
    //timer
    arm_timer_base = (size_t)rt_hw_kernel_phys_to_virt((void*)ARM_TIMER_BASE, 0x1000);
    //gic
    //gic_base_addr = (size_t)rt_hw_kernel_phys_to_virt((void*)GIC_V2_BASE, 0x10000);
    //pactl
    pactl_cs_base = (size_t)rt_hw_kernel_phys_to_virt((void*)PACTL_CS_ADDR, 0x1000);

    //stimer
    stimer_base_addr = (size_t)rt_hw_kernel_phys_to_virt((void*)STIMER_BASE, 0x1000);

    //mmc2_base_addr 
    mmc2_base_addr = (size_t)rt_hw_kernel_phys_to_virt((void*)MMC2_BASE_ADDR, 0x1000);

    //mbox
    videocore_mbox = (size_t)rt_hw_kernel_phys_to_virt((void*)VIDEOCORE_MBOX, 0x1000);

    //mbox msg
    mbox_addr = (size_t)rt_hw_kernel_phys_to_virt((void*)MBOX_ADDR, 0x1000);
    mbox = (volatile unsigned int *)mbox_addr;

    //wdt
    wdt_base_addr = (size_t)rt_hw_kernel_phys_to_virt((void*)WDT_BASE, 0x1000);

    //mac
    mac_reg_base_addr = (void *)rt_hw_kernel_phys_to_virt((void*)MAC_REG, 0x80000);

    //eth data
    eth_send_no_cache = (void *)rt_hw_kernel_phys_to_virt((void*)SEND_DATA_NO_CACHE, 0x200000);
    eth_recv_no_cache = (void *)rt_hw_kernel_phys_to_virt((void*)RECV_DATA_NO_CACHE, 0x200000);

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif
    /* initialize uart */
    rt_hw_uart_init();

#ifdef RT_USING_CONSOLE
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif /* RT_USING_CONSOLE */

    /* initialize timer for os tick */
    rt_hw_timer_init();
    rt_thread_idle_sethook(idle_wfi);

    rt_kprintf("heap: 0x%08x - 0x%08x\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

}

#ifdef RT_USING_GDBSERVER

#include <dfs_posix.h>

#define GDB_CONNECT_DEVICE "/dev/uart4"

/* for gdb */
int gdb_com_open(void)
{
    return open(GDB_CONNECT_DEVICE, O_RDWR);
}

void gdb_com_close(int fd)
{
    close(fd);
}

ssize_t gdb_com_read(int fd, void *buff, size_t len)
{
    return read(fd, buff, len);
}

ssize_t gdb_com_write(int fd, void *buff, size_t len)
{
    return write(fd, buff, len);
}

#endif
