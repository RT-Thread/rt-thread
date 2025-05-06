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
typedef rt_err_t(*bypass_function_t)(struct rt_serial_device* serial, char buf, void* data);

#define RT_BYPASS_LEVEL_MAX 4
#define RT_BYPASS_LEVEL_1 0
#define RT_BYPASS_LEVEL_2 1
#define RT_BYPASS_LEVEL_3 2
#define RT_BYPASS_LEVEL_4 3
#define RT_BYPASS_MAX_LEVEL 4

/*The protect level can be register but can not be unregister we should use it carefully*/
#define RT_BYPASS_PROTECT_LEVEL_1 10
#define RT_BYPASS_PROTECT_LEVEL_2 11
#define RT_BYPASS_PROTECT_LEVEL_3 12
#define RT_BYPASS_PROTECT_LEVEL_4 13

struct rt_serial_bypass_func {
    /*The function pointer of the bypassed data processing*/
    bypass_function_t bypass;
    /*The smaller the array of levels, the higher the priority of execution*/
    rt_uint8_t level;
    rt_list_t node;
    char name[RT_NAME_MAX];
    void* data;
};

struct rt_serial_bypass_head
{
    rt_list_t head;
    struct rt_spinlock spinlock;
};

struct rt_serial_bypass {
    struct rt_work work;

    struct rt_spinlock spinlock;
    struct rt_workqueue* lower_workq;
    struct rt_serial_bypass_head* upper_h;
    struct rt_serial_bypass_head* lower_h;
    rt_mutex_t  mutex;
    struct rt_ringbuffer* pipe;
};

int serial_bypass_list(int argc, char** argv);

void rt_bypass_work_straight(struct rt_serial_device* serial);
void rt_bypass_putchar(struct rt_serial_device* serial, rt_uint8_t ch);
rt_size_t rt_bypass_getchar(struct rt_serial_device* serial, rt_uint8_t* ch);

rt_err_t rt_bypass_upper_unregister(struct rt_serial_device* serial, rt_uint8_t level);
rt_err_t rt_bypass_lower_unregister(struct rt_serial_device* serial, rt_uint8_t level);

rt_err_t rt_bypass_upper_register(struct rt_serial_device* serial, const char* name, rt_uint8_t level, bypass_function_t func, void* data);
rt_err_t rt_bypass_lower_register(struct rt_serial_device* serial, const char* name, rt_uint8_t level, bypass_function_t func, void* data);
#endif
