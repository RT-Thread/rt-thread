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
rt_uint64_t rt_ofw_reverse_address(struct rt_ofw_node *np, const char *range_type, rt_uint64_t address);

rt_inline rt_uint64_t rt_ofw_translate_dma2cpu(struct rt_ofw_node *np, rt_uint64_t address)
{
    rt_uint64_t bus_addr, cpu_addr;

    bus_addr = rt_ofw_reverse_address(np, "dma-ranges", address);
    cpu_addr = rt_ofw_translate_address(np, "ranges", bus_addr);

    return cpu_addr != ~0ULL ? cpu_addr : address;
}

rt_inline rt_uint64_t rt_ofw_translate_cpu2dma(struct rt_ofw_node *np, rt_uint64_t address)
{
    rt_uint64_t bus_addr, dma_addr;

    bus_addr = rt_ofw_reverse_address(np, "ranges", address);
    dma_addr = rt_ofw_translate_address(np, "dma-ranges", bus_addr);

    return dma_addr != ~0ULL ? dma_addr : address;
}

void *rt_ofw_iomap(struct rt_ofw_node *np, int index);
void *rt_ofw_iomap_by_name(struct rt_ofw_node *np, const char *name);

#endif /* __OFW_IO_H__ */
