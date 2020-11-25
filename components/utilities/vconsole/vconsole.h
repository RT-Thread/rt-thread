/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-20     tyx          first implementation
 */

#ifndef __VCONSOLE_H__
#define __VCONSOLE_H__

#include <rtthread.h>
#include <ipc/ringbuffer.h>

#ifndef VCONSOLE_CACHE_SIZE
#define VCONSOLE_CACHE_SIZE (256)
#endif
#ifndef VCONSOLE_POOL_SIZE
#define VCONSOLE_POOL_SIZE (256)
#endif

#define VCONSOLE_MAGIC_NUM (0x11223344)
// #define VCONSOLE_USING_MUTEX

struct vconsole;
typedef struct vconsole * vconsole_t;
typedef rt_size_t (*vc_output_t)(rt_device_t device, rt_uint8_t *buff, rt_size_t size);

struct vconsole
{
    struct rt_device parent;
    rt_uint32_t magic;
    vc_output_t output;
#ifdef VCONSOLE_USING_MUTEX
    struct rt_mutex mutex;
#endif
    struct rt_ringbuffer ring_buff;
    int old_flag;
    rt_size_t ring_size;
    rt_size_t cache_size;
    rt_uint8_t ring_pool[VCONSOLE_POOL_SIZE];
    rt_uint8_t cache[VCONSOLE_CACHE_SIZE];
};

rt_device_t vconsole_create(const char *name, vc_output_t out);
rt_device_t vconsole_switch(rt_device_t device);
rt_err_t vconsole_delete(rt_device_t device);
rt_size_t vconsole_input(rt_device_t device, const rt_uint8_t *buff,
                         rt_size_t size);
#endif
