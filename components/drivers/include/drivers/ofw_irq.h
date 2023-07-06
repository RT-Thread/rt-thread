/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

#ifndef __OFW_IRQ_H__
#define __OFW_IRQ_H__

#include <drivers/ofw.h>

int rt_ofw_irq_cells(struct rt_ofw_node *np);

rt_err_t rt_ofw_parse_irq_map(struct rt_ofw_node *np, struct rt_ofw_cell_args *irq_args);
rt_err_t rt_ofw_parse_irq_cells(struct rt_ofw_node *np, int index, struct rt_ofw_cell_args *out_irq_args);

struct rt_ofw_node *rt_ofw_find_irq_parent(struct rt_ofw_node *np, int *out_interrupt_cells);
int rt_ofw_map_irq(struct rt_ofw_cell_args *irq_args);

int rt_ofw_get_irq_count(struct rt_ofw_node *np);
int rt_ofw_get_irq(struct rt_ofw_node *np, int index);
int rt_ofw_get_irq_by_name(struct rt_ofw_node *np, const char *name);

#endif /* __OFW_IRQ_H__ */
