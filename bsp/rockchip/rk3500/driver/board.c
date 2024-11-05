/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */
#include <setup.h>
#include <board.h>
#include <psci.h>

void rt_hw_board_init(void)
{
#if RT_VER_NUM < 0x50200
    rt_fdt_commit_memregion_early(&(rt_region_t)
    {
        .name = "memheap",
        .start = (rt_size_t)rt_kmem_v2p(HEAP_BEGIN),
        .end = (rt_size_t)rt_kmem_v2p(HEAP_END),
    }, RT_TRUE);
#endif
    rt_hw_common_setup();
}

void reboot(void)
{
    psci_system_reboot();
}
MSH_CMD_EXPORT(reboot, reboot...);

void rt_hw_cpu_shutdown(void)
{
    psci_system_off();
}
MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_shutdown, shutdown, shutdown...);
