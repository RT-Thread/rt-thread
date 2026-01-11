/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <setup.h>
#include <board.h>
#include <rtdevice.h>

void rt_hw_board_init(void)
{
    rt_hw_common_setup();
}

void rt_hw_fdt_vendor_install_early(void *fdt)
{
    int node;

    node = fdt_path_offset(fdt, "/cpus");
    fdt_setprop_u32(fdt, node, "cpu-boot-delay-us", 100);
}
