/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __HWCACHE_H__
#define __HWCACHE_H__

#include <rthw.h>
#include <rtthread.h>
#include <drivers/ofw.h>

struct rt_hwcache_ops
{
    const char *name;

    void (*enable)(void);
    void (*disable)(void);

    rt_base_t (*status)(void);

    void (*flush)(void *vaddr, rt_size_t size);
    void (*invalidate)(void *vaddr, rt_size_t size);
};

extern struct rt_hwcache_ops *rt_dm_cpu_dcache_ops;
extern struct rt_hwcache_ops *rt_dm_cpu_icache_ops;

#define RT_HWCACHE_OFW_DECLARE(name, ids, handler)   RT_OFW_STUB_EXPORT(name, ids, hwcache, handler)

void rt_hwcache_icache_enable(void);
void rt_hwcache_icache_disable(void);
rt_base_t rt_hwcache_icache_status(void);
void rt_hwcache_icache_ops(int ops, void *addr, int size);

void rt_hwcache_dcache_enable(void);
void rt_hwcache_dcache_disable(void);
rt_base_t rt_hwcache_dcache_status(void);
void rt_hwcache_dcache_ops(int ops, void *addr, int size);

rt_err_t rt_hwcache_init(void);

#endif /* __HWCACHE_H__ */
