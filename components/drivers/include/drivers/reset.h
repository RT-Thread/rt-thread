/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __RESET_H__
#define __RESET_H__

#include <rthw.h>
#include <rtthread.h>
#include <drivers/ofw.h>

#define RT_RESET_CONTROLLER_OBJ_NAME    "RSTC"

struct rt_reset_control_ops;

struct rt_reset_controller
{
    struct rt_object parent;

    rt_list_t rstc_nodes;

    const char *name;
    const struct rt_reset_control_ops *ops;

    struct rt_ofw_node *ofw_node;
    void *priv;

    struct rt_spinlock spinlock;
};

struct rt_reset_control
{
    rt_list_t list;

    struct rt_reset_controller *rstcer;

    int id;
    const char *con_id;
    rt_bool_t is_array;

    void *priv;
};

struct rt_reset_control_ops
{
    /*
     * rt_ofw_cell_args return:
     *  args[0] = rstc.id
     */
    rt_err_t    (*ofw_parse)(struct rt_reset_control *rstc, struct rt_ofw_cell_args *args);
    /* API */
    rt_err_t    (*reset)(struct rt_reset_control *rstc);
    rt_err_t    (*assert)(struct rt_reset_control *rstc);
    rt_err_t    (*deassert)(struct rt_reset_control *rstc);
    int         (*status)(struct rt_reset_control *rstc);
};

rt_err_t rt_reset_controller_register(struct rt_reset_controller *rstcer);
rt_err_t rt_reset_controller_unregister(struct rt_reset_controller *rstcer);

rt_err_t rt_reset_control_reset(struct rt_reset_control *rstc);
rt_err_t rt_reset_control_assert(struct rt_reset_control *rstc);
rt_err_t rt_reset_control_deassert(struct rt_reset_control *rstc);
int rt_reset_control_status(struct rt_reset_control *rstc);

rt_ssize_t rt_reset_control_get_count(struct rt_device *dev);
struct rt_reset_control *rt_reset_control_get_array(struct rt_device *dev);
struct rt_reset_control *rt_reset_control_get_by_index(struct rt_device *dev, int index);
struct rt_reset_control *rt_reset_control_get_by_name(struct rt_device *dev, const char *name);
void rt_reset_control_put(struct rt_reset_control *rstc);

struct rt_reset_control *rt_ofw_get_reset_control_array(struct rt_ofw_node *np);
struct rt_reset_control *rt_ofw_get_reset_control_by_index(struct rt_ofw_node *np, int index);
struct rt_reset_control *rt_ofw_get_reset_control_by_name(struct rt_ofw_node *np, const char *name);

#endif /* __RESET_H__ */
