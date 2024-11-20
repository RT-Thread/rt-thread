/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-20     zhujiale     the first version
 */

#ifndef __RTT_BYPASS_H__
#define __RTT_BYPASS_H__
#include <rtthread.h>
#include <rttypes.h>
#include <rtdevice.h>
typedef rt_err_t (*bypass_function_t)(struct rt_serial_device* serial, char buf);
struct rt_serial_bypass {
    /*The function pointer of the bypassed data processing*/
    bypass_function_t bypass;

    /*The smaller the array of levels, the higher the priority of execution*/
    rt_uint8_t level;
#define RT_BYPASS_LEVEL_MAX 4
#define RT_BYPASS_LEVEL_1 0
#define RT_BYPASS_LEVEL_2 1
#define RT_BYPASS_LEVEL_3 2
#define RT_BYPASS_LEVEL_4 3
#define BYPASS_FUNC_MAX_4 4
    rt_list_t list;
    char name[RT_NAME_MAX];
};

rt_err_t rt_bypass_unregister(struct rt_serial_device* serial, rt_uint8_t level);
rt_err_t rt_bypass_register(struct rt_serial_device* serial, const char* name, rt_uint8_t level, bypass_function_t func);

#endif
