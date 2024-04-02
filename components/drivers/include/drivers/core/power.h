/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-24     GuEe-GUI     the first version
 */

#ifndef __RT_DM_POWER_H__
#define __RT_DM_POWER_H__

#include <rtdef.h>

enum rt_dm_power_off_mode
{
    RT_DM_POWER_OFF_MODE_SHUTDOWN,
    RT_DM_POWER_OFF_MODE_RESET,

    RT_DM_POWER_OFF_MODE_NR,
};

enum rt_dm_power_off_priority
{
    RT_DM_POWER_OFF_PRIO_PLATFORM,
    RT_DM_POWER_OFF_PRIO_LOW,
    RT_DM_POWER_OFF_PRIO_DEFAULT,
    RT_DM_POWER_OFF_PRIO_HIGH,
    RT_DM_POWER_OFF_PRIO_FIRMWARE,

    RT_DM_POWER_OFF_PRIO_NR,
};

rt_err_t rt_dm_power_off_handler(struct rt_device *dev, int mode, int priority,
        rt_err_t (*callback)(struct rt_device *));

rt_err_t rt_dm_reboot_mode_register(struct rt_device *dev,
        rt_err_t (*callback)(struct rt_device *, char *cmd));

void rt_hw_cpu_reset_mode(char *cmd);

extern void (*rt_dm_machine_shutdown)(void);
extern void (*rt_dm_machine_reset)(void);

#endif /* __RT_DM_POWER_H__ */
