/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

#ifndef __OFW_IO_H__
#define __OFW_IO_H__

#include <ioremap.h>
#include <drivers/ofw.h>

int rt_ofw_bus_addr_cells(struct rt_ofw_node *np);
int rt_ofw_bus_size_cells(struct rt_ofw_node *np);
int rt_ofw_io_addr_cells(struct rt_ofw_node *np);
int rt_ofw_io_size_cells(struct rt_ofw_node *np);

int rt_ofw_get_address_count(struct rt_ofw_node *np);
rt_err_t rt_ofw_get_address(struct rt_ofw_node *np, int index, rt_uint64_t *out_address, rt_uint64_t *out_size);
rt_err_t rt_ofw_get_address_by_name(struct rt_ofw_node *np, const char *name,
        rt_uint64_t *out_address, rt_uint64_t *out_size);
int rt_ofw_get_address_array(struct rt_ofw_node *np, int nr, rt_uint64_t *out_regs);

rt_uint64_t rt_ofw_translate_address(struct rt_ofw_node *np, const char *range_type, rt_uint64_t address);

void *rt_ofw_iomap(struct rt_ofw_node *np, int index);
void *rt_ofw_iomap_by_name(struct rt_ofw_node *np, const char *name);

#endif /* __OFW_IO_H__ */
