/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __DVFS_RASPBERRYPI_CPUFREQ_H__
#define __DVFS_RASPBERRYPI_CPUFREQ_H__

#include <rtdevice.h>
#include <firmware-raspberrypi.h>

struct rt_clk *raspberrypi_arm_clk_get(void);
rt_err_t raspberrypi_cpufreq_register(struct rt_clk *arm_clk, struct rt_ofw_node *cpu_np,
        struct rpi_firmware *rpi_fw);

#endif /* __DVFS_RASPBERRYPI_CPUFREQ_H__ */
