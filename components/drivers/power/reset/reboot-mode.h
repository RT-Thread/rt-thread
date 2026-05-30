/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __RESET_REBOOT_MODE_H__
#define __RESET_REBOOT_MODE_H__

#include <rtthread.h>
#include <rtdevice.h>

struct reboot_mode
{
    rt_slist_t mode_nodes;

    struct rt_device *dev;
    rt_err_t (*write)(struct reboot_mode *reboot, rt_uint32_t magic);
};

rt_err_t reboot_mode_register(struct reboot_mode *reboot);

#endif /* __RESET_REBOOT_MODE_H__ */
