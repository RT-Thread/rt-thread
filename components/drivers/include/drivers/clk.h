/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 * 2025-01-24     wumingzi     add doxygen comment
 */

#ifndef __CLK_H__
#define __CLK_H__

#include <rthw.h>

#include <ref.h>
#include <drivers/ofw.h>

/**
 * @addtogroup  Drivers          RTTHREAD Driver
 * @defgroup    clk              clk
 * @brief       clk driver api
 * @ingroup     Drivers
 * @addtogroup  clk
 * @{
 */

#define RT_CLK_NODE_OBJ_NAME    "CLKNP"

struct rt_clk_ops;
struct rt_reset_control_node;

/**
 * @brief  Clk node, it is a pat of clk source or controller
 * @note   Defined as the array like this if the CLK have multi out clocks:
 * @code{.c}
 *       struct XYZ_single_clk
 *       {
 *           struct rt_clk_node parent;
 *           ...
 *       };
 *
 *       struct XYZ_multi_clk
 *       {
 *           struct rt_clk_node parent[N];
 *           ...
 *       };
 * @endcode
 *          We assume the 'N' is the max value of element in 'clock-indices' if OFW.
 */
struct rt_clk_node
{
    struct rt_object rt_parent;

    rt_list_t list;
    rt_list_t children_nodes;

    const char *name;
    const struct rt_clk_ops *ops;

    struct rt_clk_node *parent;
    struct rt_ref ref;

    rt_ubase_t rate;
    rt_ubase_t min_rate;
    rt_ubase_t max_rate;

    rt_size_t notifier_count;

    void *priv;

    struct rt_clk *clk;
    rt_size_t multi_clk;
};

/**
 * @brief   Constant rate clk
 */
struct rt_clk_fixed_rate
{
    struct rt_clk_node clk;

    rt_ubase_t fixed_rate;
    rt_ubase_t fixed_accuracy;
};

/**
 * @brief   Clk object, it can be clk source or controller
 */
struct rt_clk
{
    struct rt_clk_node *clk_np;

    const char *dev_id;
    const char *con_id;

    rt_ubase_t rate;
    int prepare_count;
    int enable_count;

    void *fw_node;
    void *priv;
};

/**
 * @brief   Clk array
 */
struct rt_clk_array
{
    rt_size_t count;
    struct rt_clk *clks[];
};

struct rt_clk_ops
{
    rt_err_t    (*init)(struct rt_clk *, void *fw_data);
    rt_err_t    (*finit)(struct rt_clk *);
    /* API */
    rt_err_t    (*prepare)(struct rt_clk *);
    void        (*unprepare)(struct rt_clk *);
    rt_bool_t   (*is_prepared)(struct rt_clk *);
    rt_err_t    (*enable)(struct rt_clk *);
    void        (*disable)(struct rt_clk *);
    rt_bool_t   (*is_enabled)(struct rt_clk *);
    rt_err_t    (*set_rate)(struct rt_clk *, rt_ubase_t rate, rt_ubase_t parent_rate);
    rt_err_t    (*set_parent)(struct rt_clk *, struct rt_clk *parent);
    rt_err_t    (*set_phase)(struct rt_clk *, int degrees);
    rt_base_t   (*get_phase)(struct rt_clk *);
    rt_base_t   (*round_rate)(struct rt_clk *, rt_ubase_t drate, rt_ubase_t *prate);
};

struct rt_clk_notifier;

#define RT_CLK_MSG_PRE_RATE_CHANGE      RT_BIT(0)
#define RT_CLK_MSG_POST_RATE_CHANGE     RT_BIT(1)
#define RT_CLK_MSG_ABORT_RATE_CHANGE    RT_BIT(2)

typedef rt_err_t (*rt_clk_notifier_callback)(struct rt_clk_notifier *notifier,
        rt_ubase_t msg, rt_ubase_t old_rate, rt_ubase_t new_rate);

/**
 * @brief   Clock notifier, it containers of clock list and callback function
 */
struct rt_clk_notifier
{
    rt_list_t list;

    struct rt_clk *clk;
    rt_clk_notifier_callback callback;
    void *priv;
};

rt_err_t rt_clk_register(struct rt_clk_node *clk_np, struct rt_clk_node *parent_np);
rt_err_t rt_clk_unregister(struct rt_clk_node *clk_np);

rt_err_t rt_clk_notifier_register(struct rt_clk *clk, struct rt_clk_notifier *notifier);
rt_err_t rt_clk_notifier_unregister(struct rt_clk *clk, struct rt_clk_notifier *notifier);

rt_err_t rt_clk_set_parent(struct rt_clk *clk, struct rt_clk *clk_parent);

rt_err_t rt_clk_prepare(struct rt_clk *clk);
rt_err_t rt_clk_unprepare(struct rt_clk *clk);

rt_err_t rt_clk_enable(struct rt_clk *clk);
void rt_clk_disable(struct rt_clk *clk);

rt_err_t rt_clk_prepare_enable(struct rt_clk *clk);
void rt_clk_disable_unprepare(struct rt_clk *clk);

rt_err_t rt_clk_array_prepare(struct rt_clk_array *clk_arr);
rt_err_t rt_clk_array_unprepare(struct rt_clk_array *clk_arr);

rt_err_t rt_clk_array_enable(struct rt_clk_array *clk_arr);
void rt_clk_array_disable(struct rt_clk_array *clk_arr);

rt_err_t rt_clk_array_prepare_enable(struct rt_clk_array *clk_arr);
void rt_clk_array_disable_unprepare(struct rt_clk_array *clk_arr);

rt_err_t rt_clk_set_rate_range(struct rt_clk *clk, rt_ubase_t min, rt_ubase_t max);
rt_err_t rt_clk_set_min_rate(struct rt_clk *clk, rt_ubase_t rate);
rt_err_t rt_clk_set_max_rate(struct rt_clk *clk, rt_ubase_t rate);
rt_err_t rt_clk_set_rate(struct rt_clk *clk, rt_ubase_t rate);
rt_ubase_t rt_clk_get_rate(struct rt_clk *clk);

rt_err_t rt_clk_set_phase(struct rt_clk *clk, int degrees);
rt_base_t rt_clk_get_phase(struct rt_clk *clk);

rt_base_t rt_clk_round_rate(struct rt_clk *clk, rt_ubase_t rate);

struct rt_clk *rt_clk_get_parent(struct rt_clk *clk);

struct rt_clk_array *rt_clk_get_array(struct rt_device *dev);
struct rt_clk *rt_clk_get_by_index(struct rt_device *dev, int index);
struct rt_clk *rt_clk_get_by_name(struct rt_device *dev, const char *name);
void rt_clk_array_put(struct rt_clk_array *clk_arr);
void rt_clk_put(struct rt_clk *clk);

#ifdef RT_USING_OFW
struct rt_clk_array *rt_ofw_get_clk_array(struct rt_ofw_node *np);
struct rt_clk *rt_ofw_get_clk(struct rt_ofw_node *np, int index);
struct rt_clk *rt_ofw_get_clk_by_name(struct rt_ofw_node *np, const char *name);
rt_ssize_t rt_ofw_count_of_clk(struct rt_ofw_node *clk_ofw_np);
#else
rt_inline struct rt_clk *rt_ofw_get_clk(struct rt_ofw_node *np, int index)
{
    return RT_NULL;
}
rt_inline struct rt_clk *rt_ofw_get_clk_by_name(struct rt_ofw_node *np, const char *name)
{
    return RT_NULL;
}
rt_inline rt_ssize_t rt_ofw_count_of_clk(struct rt_ofw_node *clk_ofw_np)
{
    return 0;
}
#endif /* RT_USING_OFW */

/*! @}*/

#endif /* __CLK_H__ */