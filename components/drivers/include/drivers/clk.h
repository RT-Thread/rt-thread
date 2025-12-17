/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 * 2025-01-24     wumingzi     add doxygen comment
 * 2024-05-01     GuEe-GUI     make cell for hareware clock
 */

#ifndef __CLK_H__
#define __CLK_H__

#include <rthw.h>

#include <ref.h>
#include <drivers/ofw.h>

/**
 * @defgroup    group_driver_clock Clock
 * @brief       Clock driver API
 * @ingroup     group_device_driver
 */

/**
 * @addtogroup  group_driver_clock
 * @{
 */

#define RT_CLK_NODE_OBJ_NAME    "CLKNP"

struct rt_clk;
struct rt_clk_ops;
struct rt_clk_cell;

/**
 * @brief  Clock provider node - represents a hardware clock controller.
 *
 * A @ref rt_clk_node corresponds to one hardware clock provider in the
 * system, such as a PLL controller, a clock multiplexer, or a composite
 * clock block defined in the device tree.
 *
 * Each clock node may contain multiple hardware clock outputs, described
 * as @ref rt_clk_cell structures, which represent individual leaf clocks.
 *
 * Members:
 * - `parent` — embedded @ref rt_object header for RT-Thread object system.
 * - `dev` — back-reference to the hardware device providing this clock domain.
 * - `parents_clk` — optional array of parent clock handles.
 * - `multi_clk` — number of clock outputs exported by this provider.
 * - `cells` — list of @ref rt_clk_cell pointers representing each output.
 * - `ofw_parse` — callback used to parse clock arguments from device tree
 *   (`#clock-cells`) and select the corresponding @ref rt_clk_cell.
 * - `priv` — implementation-specific private data.
 *
 * Typical usage:
 * 1. Define a @ref rt_clk_node describing the hardware clock controller.
 * 2. Implement `ofw_parse()` to resolve device tree `phandle` arguments.
 * 3. Register the node using @ref rt_clk_register().
 */
struct rt_clk_node
{
    struct rt_object parent;

    struct rt_device *dev;
    struct rt_clk_array *parents_clk;

    rt_size_t multi_clk;

    rt_size_t cells_nr;
    struct rt_clk_cell **cells;

    struct rt_clk_cell *(*ofw_parse)(struct rt_clk_node *clk_np, struct rt_ofw_cell_args *args);

    void *priv;
};

#define RT_CLK_F_SET_RATE_GATE      RT_BIT(0)   /**< Must be gated across rate change */
#define RT_CLK_F_SET_PARENT_GATE    RT_BIT(1)   /**< Must be gated across re-parent */
#define RT_CLK_F_SET_RATE_PARENT    RT_BIT(2)   /**< Propagate rate change up one level */
#define RT_CLK_F_IGNORE_UNUSED      RT_BIT(3)   /**< Do not gate even if unused */
#define RT_CLK_F_SET_RATE_UNGATE    RT_BIT(4)   /**< Clock needs to run to set rate */
#define RT_CLK_F_IS_CRITICAL        RT_BIT(5)   /**< Do not gate, ever */
#define RT_CLK_F_GET_RATE_NOCACHE   RT_BIT(6)   /**< Do not get rate by cache */

/**
 * @brief  Clock cell - represents a single hardware clock element.
 *
 * A clk_cell is the fundamental unit of a clock tree, such as a PLL, divider,
 * mux, or gate. It maintains its relationship to parent clocks using pointers,
 * not lists, for lightweight hierarchy management.
 *
 * The 'ops' field defines hardware-specific callbacks. The framework invokes
 * these during enable, disable, and rate changes.
 */
struct rt_clk_cell
{
    struct rt_clk_node *clk_np;

    const char *name;
    const struct rt_clk_ops *ops;

    rt_uint8_t parents_nr;
    union
    {
        const char *parent_name;            /**< When parents_nr = 1 */
        const char *const *parent_names;
    };

    rt_ubase_t rate;                        /**< Cached or fixed rate (not always accurate) */
    struct rt_clk *clk;
    struct rt_clk *parent;

    int prepare_count;
    int enable_count;

    rt_uint32_t flags;

    void *priv;
};

/**
 * @brief  Fixed-rate clock descriptor.
 *
 * Used for constant-frequency clocks without configurable parents or dividers.
 */
struct rt_clk_fixed_rate
{
    struct rt_clk_cell cell;

    rt_ubase_t fixed_rate;
    rt_ubase_t fixed_accuracy;
};

/**
 * @brief  Clock handle - represents a consumer reference to a clock.
 *
 * Each consumer obtains an rt_clk instance bound to a specific clk_cell.
 * The handle stores consumer-specific constraints such as min/max rate.
 */
struct rt_clk
{
    struct rt_clk_cell *cell;

    const char *dev_id;              /**< Device identifier using this clock */
    const char *con_id;              /**< Connection identifier (name) */

    rt_ubase_t min_rate;
    rt_ubase_t max_rate;
};

/**
 * @brief  Clock array container.
 *
 * Represents a group of rt_clk handles, typically used for devices that
 * require multiple clock inputs.
 */
struct rt_clk_array
{
    rt_size_t count;
    struct rt_clk *clks[];
};

struct rt_clk_ops
{
    rt_err_t    (*prepare)(struct rt_clk_cell *cell);
    void        (*unprepare)(struct rt_clk_cell *cell);
    rt_bool_t   (*is_prepared)(struct rt_clk_cell *cell);

    rt_err_t    (*enable)(struct rt_clk_cell *cell);
    void        (*disable)(struct rt_clk_cell *cell);
    rt_bool_t   (*is_enabled)(struct rt_clk_cell *cell);

    rt_ubase_t  (*recalc_rate)(struct rt_clk_cell *cell, rt_ubase_t parent_rate);
    rt_base_t   (*round_rate)(struct rt_clk_cell *cell, rt_ubase_t drate, rt_ubase_t *prate);
    rt_err_t    (*set_rate)(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate);

    rt_err_t    (*set_parent)(struct rt_clk_cell *cell, rt_uint8_t idx);
    rt_uint8_t  (*get_parent)(struct rt_clk_cell *cell);

    rt_err_t    (*set_phase)(struct rt_clk_cell *cell, int degrees);
    rt_base_t   (*get_phase)(struct rt_clk_cell *cell);
};

struct rt_clk_notifier;

#define RT_CLK_MSG_PRE_RATE_CHANGE      RT_BIT(0)
#define RT_CLK_MSG_POST_RATE_CHANGE     RT_BIT(1)
#define RT_CLK_MSG_ABORT_RATE_CHANGE    RT_BIT(2)

typedef rt_err_t (*rt_clk_notifier_callback)(struct rt_clk_notifier *notifier,
        rt_ubase_t msg, rt_ubase_t old_rate, rt_ubase_t new_rate);

/**
 * @brief  Clock notifier descriptor.
 *
 * Used to register callbacks for clock events (rate change, abort, etc).
 * Each notifier is linked to a specific clock and triggered on rate changes.
 */
struct rt_clk_notifier
{
    rt_list_t list;

    struct rt_clk *clk;
    rt_clk_notifier_callback callback;
    void *priv;
};

rt_err_t rt_clk_register(struct rt_clk_node *clk_np);
rt_err_t rt_clk_unregister(struct rt_clk_node *clk_np);

rt_err_t rt_clk_notifier_register(struct rt_clk *clk, struct rt_clk_notifier *notifier);
rt_err_t rt_clk_notifier_unregister(struct rt_clk *clk, struct rt_clk_notifier *notifier);

rt_err_t rt_clk_prepare(struct rt_clk *clk);
void rt_clk_unprepare(struct rt_clk *clk);

rt_err_t rt_clk_enable(struct rt_clk *clk);
void rt_clk_disable(struct rt_clk *clk);

rt_err_t rt_clk_prepare_enable(struct rt_clk *clk);
void rt_clk_disable_unprepare(struct rt_clk *clk);

rt_err_t rt_clk_array_prepare(struct rt_clk_array *clk_arr);
void rt_clk_array_unprepare(struct rt_clk_array *clk_arr);

rt_err_t rt_clk_array_enable(struct rt_clk_array *clk_arr);
void rt_clk_array_disable(struct rt_clk_array *clk_arr);

rt_err_t rt_clk_array_prepare_enable(struct rt_clk_array *clk_arr);
void rt_clk_array_disable_unprepare(struct rt_clk_array *clk_arr);

rt_err_t rt_clk_set_rate_range(struct rt_clk *clk, rt_ubase_t min, rt_ubase_t max);
rt_err_t rt_clk_set_min_rate(struct rt_clk *clk, rt_ubase_t rate);
rt_err_t rt_clk_set_max_rate(struct rt_clk *clk, rt_ubase_t rate);
rt_err_t rt_clk_set_rate(struct rt_clk *clk, rt_ubase_t rate);
rt_ubase_t rt_clk_get_rate(struct rt_clk *clk);

rt_base_t rt_clk_round_rate(struct rt_clk *clk, rt_ubase_t rate);

rt_err_t rt_clk_set_parent(struct rt_clk *clk, struct rt_clk *clk_parent);
struct rt_clk *rt_clk_get_parent(struct rt_clk *clk);

rt_err_t rt_clk_set_phase(struct rt_clk *clk, int degrees);
rt_base_t rt_clk_get_phase(struct rt_clk *clk);

struct rt_clk *rt_clk_cell_get_clk(const struct rt_clk_cell *cell, const char *con_id);

rt_bool_t rt_clk_cell_is_prepared(const struct rt_clk_cell *cell);

rt_bool_t rt_clk_cell_is_enabled(const struct rt_clk_cell *cell);

rt_ubase_t rt_clk_cell_get_rate(const struct rt_clk_cell *cell);

rt_ubase_t rt_clk_cell_round_rate(struct rt_clk_cell *cell, rt_ubase_t rate);

struct rt_clk_cell *rt_clk_cell_get_parent(const struct rt_clk_cell *cell);
struct rt_clk_cell *rt_clk_cell_get_parent_by_index(const struct rt_clk_cell *cell, rt_uint8_t idx);
rt_uint8_t rt_clk_cell_get_parent_index(struct rt_clk_cell *cell);
rt_err_t rt_clk_cell_set_parent(struct rt_clk_cell *cell, struct rt_clk_cell *parent);

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
const char *rt_ofw_clk_get_parent_name(struct rt_ofw_node *np, int index);
rt_err_t rt_ofw_clk_set_defaults(struct rt_ofw_node *np);
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
rt_inline const char *rt_ofw_clk_get_parent_name(struct rt_ofw_node *np, int index)
{
    return RT_NULL;
}
rt_inline rt_err_t rt_ofw_clk_set_defaults(struct rt_ofw_node *np)
{
    return RT_EOK;
}
#endif /* RT_USING_OFW */

/*! @}*/

#endif /* __CLK_H__ */