/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-16     GuEe-GUI     first version
 */

#ifndef __SERIAL_DM_H__
#define __SERIAL_DM_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>

int serial_dev_set_name(struct rt_serial_device *sdev);

void *serial_base_from_args(char *str);
struct serial_configure serial_cfg_from_args(char *str);

#define serial_for_each_args(arg, args)                                 \
    for (char *context = (arg = (typeof(arg))args, (void *)RT_NULL),    \
        *context_end = rt_strchrnul((char *)args, ' ');                 \
         (arg = strtok_r(arg, ",", &context)) && arg < context_end;     \
         arg = RT_NULL)

#endif /* __SERIAL_DM_H__ */
