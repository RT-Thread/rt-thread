/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __SYSCON_H__
#define __SYSCON_H__

#include <drivers/ofw.h>

struct rt_syscon
{
    rt_list_t list;

    struct rt_ofw_node *np;

    void *iomem_base;
    rt_size_t iomem_size;
    struct rt_spinlock rw_lock;
};

rt_err_t rt_syscon_read(struct rt_syscon *syscon, rt_off_t offset, rt_uint32_t *out_val);
rt_err_t rt_syscon_write(struct rt_syscon *syscon, rt_off_t offset, rt_uint32_t val);
rt_err_t rt_syscon_update_bits(struct rt_syscon *syscon, rt_off_t offset, rt_uint32_t mask, rt_uint32_t val);

struct rt_syscon *rt_syscon_find_by_ofw_node(struct rt_ofw_node *np);
struct rt_syscon *rt_syscon_find_by_ofw_compatible(const char *compatible);
struct rt_syscon *rt_syscon_find_by_ofw_phandle(struct rt_ofw_node *np, const char *propname);

#endif /* __SYSCON_H__ */
