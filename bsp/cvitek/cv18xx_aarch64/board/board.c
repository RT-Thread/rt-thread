/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-15     liYony       the first version
 */

#include <mmu.h>
#include <board.h>
#include <mm_aspace.h>
#include <mm_page.h>
#include <drv_uart.h>
#include <gtimer.h>
#include <setup.h>

extern size_t MMUTable[];

#ifndef RT_USING_OFW
void idle_wfi(void)
{
    asm volatile("wfi");
}

#ifdef RT_USING_SMART
struct mem_desc platform_mem_desc[] = {
    {KERNEL_VADDR_START, KERNEL_VADDR_START + 0x0FFFFFFF, (rt_size_t)ARCH_MAP_FAILED, NORMAL_MEM},
};
#else
struct mem_desc platform_mem_desc[] =
{
    {0x80200000, 0x90200000 - 1, 0x80200000, NORMAL_MEM}, /* memory size 256M */
    {0x01000000, 0x80000000 - 1, 0x01000000, DEVICE_MEM},
};
#endif

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]);

void rt_hw_board_init(void)
{
#ifdef RT_USING_SMART
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)0xfffffffff0000000, 0x10000000, MMUTable, PV_OFFSET);
#else
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)0xffffd0000000, 0x10000000, MMUTable, 0);
#endif
    rt_region_t init_page_region;
    init_page_region.start = PAGE_START;
    init_page_region.end = PAGE_END;
    rt_page_init(init_page_region);

    rt_hw_mmu_setup(&rt_kernel_space, platform_mem_desc, platform_mem_desc_size);

#ifdef RT_USING_HEAP
    /* initialize system heap */
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
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
    rt_kprintf("heap: [0x%08x - 0x%08x]\n", HEAP_BEGIN, HEAP_END);

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
#else
void rt_hw_board_init(void)
{
    rt_hw_common_setup();
}

/*
 * FIXME: This is a temporary workaround.
 * When aarch bsp enables the device tree, the current u-boot will
 * pass in bootargs, which contains "root=/dev/mmcblk0p2 rootwait rw",
 * which means that the kernel is required to wait until the rootfs
 * in /dev/mmcblk0p2 loaded successfully. However, the current aarch64 bsp
 * default does not implement sdmmc device mounting, causing the kernel file
 * system mounting module (rootfs_mnt_init() of components/drivers/core/mnt.c)
 * to enter an infinite loop waiting.
 * Solution: At present, we do not plan to modify the startup parameters
 * of u-boot. The temporary solution adopted is to create a pseudo
 * /dev/mmcblk0p2 device during the board initialization process, and
 * then cancel the pseudo device after mnt is completed. This allows the
 * kernel boot to be completed successfully.
 */
static struct rt_device *pseudo_mmcblk;

static int pseudo_mmcblk_setup(void)
{
    pseudo_mmcblk = rt_calloc(1, sizeof(*pseudo_mmcblk));

    RT_ASSERT(pseudo_mmcblk != RT_NULL);

    pseudo_mmcblk->type = RT_Device_Class_Graphic;

    return (int)rt_device_register(pseudo_mmcblk, "/dev/mmcblk0p2", RT_DEVICE_FLAG_DEACTIVATE);
}
INIT_BOARD_EXPORT(pseudo_mmcblk_setup);

static int pseudo_mmcblk_remove(void)
{
    if (pseudo_mmcblk)
    {
        return (int)rt_device_unregister(pseudo_mmcblk);
    }

    return 0;
}
INIT_FS_EXPORT(pseudo_mmcblk_remove);
#endif /* RT_USING_OFW */

static rt_ubase_t pinmux_base = RT_NULL;

rt_ubase_t pinmux_base_ioremap(void)
{
    if (pinmux_base == RT_NULL)
    {
        pinmux_base = (rt_size_t)rt_ioremap((void*)0x03001000, 0x1000);
    }

    return pinmux_base;
}
