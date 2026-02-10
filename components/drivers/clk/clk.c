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

#include <rtthread.h>
#include <rtservice.h>
#include <rtdevice.h>

/**
 * @addtogroup group_driver_clock
 * @{
 */

#define DBG_TAG "rtdm.clk"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_bool_t clk_ignore_unused = RT_FALSE;

static struct rt_mutex _clk_lock;
static rt_list_t _clk_node_nodes = RT_LIST_OBJECT_INIT(_clk_node_nodes);
static rt_list_t _clk_notifier_nodes = RT_LIST_OBJECT_INIT(_clk_notifier_nodes);

static int clk_init(void)
{
#ifdef RT_USING_OFW
    clk_ignore_unused = !!rt_ofw_bootargs_select("clk_ignore_unused", 0);
#endif
    rt_mutex_init(&_clk_lock, "CLK", RT_IPC_FLAG_PRIO);

    return 0;
}
INIT_CORE_EXPORT(clk_init);

/**
 * @brief   Acquire global clock framework lock.
 *
 */
static void clk_lock(void)
{
    if (rt_thread_self())
    {
        rt_mutex_take(&_clk_lock, RT_WAITING_FOREVER);
    }
}

/**
 * @brief   Release global clock framework lock.
 *
 */
static void clk_unlock(void)
{
    if (rt_thread_self())
    {
        rt_mutex_release(&_clk_lock);
    }
}

/**
 * @brief   Allocate memory space for struct clock and return it
 *
 * @param   cell            point to clock cell
 * @param   dev_id          device identifier for the clock
 * @param   con_id          connection identifier for the clock
 *
 * @return  struct rt_clk*  point to clock
 */
static struct rt_clk *clk_alloc(struct rt_clk_cell *cell, const char *dev_id, const char *con_id)
{
    struct rt_clk *clk = rt_calloc(1, sizeof(*clk));

    if (!clk)
    {
        LOG_E("%s not memory to create CLK for dev_id = %s con_id = %s",
                cell->name, dev_id, con_id);
        return RT_NULL;
    }

    clk->cell = cell;

    clk->dev_id = dev_id;
    clk->con_id = con_id;

    if (cell->clk)
    {
        clk->min_rate = cell->clk->min_rate;
        clk->max_rate = cell->clk->max_rate;
    }
    else
    {
        clk->min_rate = 0;
        clk->max_rate = ~0UL;
    }

    return clk;
}

/**
 * @brief   Update clk cell hardware information
 *
 * @param   cell            point to clock cell
 * @param   clk             bind clk
 *
 */
static void clk_cell_bind(struct rt_clk_cell *cell, struct rt_clk *clk)
{
    if (!cell->clk)
    {
        cell->clk = clk;
    }
    else
    {
        if (!cell->clk->dev_id)
        {
            cell->clk->dev_id = clk->dev_id;
        }

        if (!cell->clk->con_id)
        {
            cell->clk->con_id = clk->con_id;
        }
    }
}

/**
 * @brief   Register a clock node into the global clock framework.
 *
 * This function initializes an @ref rt_clk_node structure and inserts it
 * into the global clock node list. Each node may contain multiple
 * @ref rt_clk_cell instances, which represent the individual output clocks
 * provided by the node.
 *
 * If the node is associated with a device (clk_np->dev is not NULL),
 * the framework will automatically try to obtain its parent clocks by calling
 * rt_clk_get_array(clk_np->dev). Otherwise, the node will be treated as a
 * root-level provider (e.g., fixed clock).
 *
 * The caller must ensure that all @ref rt_clk_cell entries are allocated
 * and linked to the node before calling this function.
 *
 * @param   clk_np  Pointer to the clock node to be registered.
 *
 * @retval  RT_EOK          Successfully registered.
 * @retval  -RT_EINVAL      Invalid argument or missing cell list.
 * @retval  -RT_ENOMEM      Failed to allocate parent clock array.
 */
rt_err_t rt_clk_register(struct rt_clk_node *clk_np)
{
    rt_err_t err = RT_EOK;
    struct rt_clk_cell *cell;

    if (!clk_np || !clk_np->cells_nr || !clk_np->cells)
    {
        return -RT_EINVAL;
    }

    if (clk_np->dev && !rt_is_err(clk_np->parents_clk))
    {
        clk_np->parents_clk = rt_clk_get_array(clk_np->dev);

        if (rt_is_err(clk_np->parents_clk))
        {
            return rt_ptr_err(clk_np->parents_clk);
        }
    }

#if RT_NAME_MAX > 0
    rt_strncpy(clk_np->parent.name, RT_CLK_NODE_OBJ_NAME, RT_NAME_MAX);
#else
    clk_np->parent.name = RT_CLK_NODE_OBJ_NAME;
#endif

    rt_list_init(&clk_np->parent.list);

    for (int i = 0; i < clk_np->cells_nr; ++i)
    {
        cell = clk_np->cells[i];

        if (!cell)
        {
            continue;
        }

        cell->clk_np = clk_np;

        cell->rate = 0;
        cell->prepare_count = 0;
        cell->enable_count = 0;
    }

    clk_lock();
    rt_list_insert_after(&_clk_node_nodes, &clk_np->parent.list);
    clk_unlock();

#ifdef RT_USING_OFW
    if (clk_np->dev && clk_np->dev->ofw_node)
    {
        rt_bool_t set_ofw_data = RT_FALSE;
        struct rt_ofw_node *np = clk_np->dev->ofw_node;

        if (!rt_ofw_data(np))
        {
            set_ofw_data = RT_TRUE;
            rt_ofw_data(np) = &clk_np->parent;
        }

        if ((err = rt_ofw_clk_set_defaults(np)))
        {
            if (set_ofw_data)
            {
                rt_ofw_data(np) = RT_NULL;
            }
        }
    }
#endif /* RT_USING_OFW */

    if (err)
    {
        if (!rt_is_err(clk_np->parents_clk))
        {
            rt_clk_array_put(clk_np->parents_clk);
        }
    }

    return err;
}

/**
 * @brief   Unregister a clock node from global clock list
 *
 * This API is intended for rollback use only, typically called
 * when a clock provider fails after registration but before any
 * consumer starts using its clocks.
 *
 * It removes the specified clock node from the global list and
 * releases its parent clock array if present. The function does
 * not free memory of @ref rt_clk_cell instances or the node itself.
 *
 * @param   clk_np  Pointer to the clock node to be unregistered.
 *
 * @retval  RT_EOK      Successfully unregistered.
 * @retval  -RT_EINVAL  Invalid parameter.
 * @retval  -RT_EBUSY   One or more cells are active and cannot be removed.
 */
rt_err_t rt_clk_unregister(struct rt_clk_node *clk_np)
{
    struct rt_clk_cell *cell;

    if (!clk_np)
    {
        return -RT_EINVAL;
    }

    if (clk_np->cells && clk_np->cells_nr)
    {
        for (int i = 0; i < clk_np->cells_nr; ++i)
        {
            cell = clk_np->cells[i];

            if (cell && cell->enable_count > 0)
            {
                return -RT_EBUSY;
            }
        }
    }

    clk_lock();
    rt_list_remove(&clk_np->parent.list);
    clk_unlock();

    if (!rt_is_err(clk_np->parents_clk))
    {
        rt_clk_array_put(clk_np->parents_clk);
    }

    return RT_EOK;
}

/**
 * @brief   Register clock notifier into notifier list
 *
 * @param   clk             point to clock
 * @param   notifier        point to notifier for register
 *
 * @retval  RT_EOK
 * @retval  -RT_EINVAL
 */
rt_err_t rt_clk_notifier_register(struct rt_clk *clk, struct rt_clk_notifier *notifier)
{
    if (!clk || !notifier)
    {
        return -RT_EINVAL;
    }

    notifier->clk = clk;
    rt_list_init(&notifier->list);

    clk_lock();
    rt_list_insert_after(&_clk_notifier_nodes, &notifier->list);
    clk_unlock();

    return RT_EOK;
}

/**
 * @brief   Unregister clock notifier into notifier list
 *
 * @param   clk             point to clock
 * @param   notifier        point to notifier for unregister
 *
 * @retval  RT_EOK
 * @retval  -RT_EINVAL
 */
rt_err_t rt_clk_notifier_unregister(struct rt_clk *clk, struct rt_clk_notifier *notifier)
{
    struct rt_clk_notifier *notifier_find;

    if (!clk || !notifier)
    {
        return -RT_EINVAL;
    }

    clk_lock();
    rt_list_for_each_entry(notifier_find, &_clk_notifier_nodes, list)
    {
        if (notifier_find == notifier)
        {
            rt_list_remove(&notifier->list);

            break;
        }
    }
    clk_unlock();

    return RT_EOK;
}

/**
 * @brief   Notify corresponding clock from all
 *
 * @param   clk_np          point to clock node
 * @param   msg             message identifier for the event
 * @param   old_rate        old rate of the clock before the event
 * @param   new_rate        new rate of the clock after the event
 *
 * @return  rt_err_t        RT_EOK on notify clock sucessfully, and other value is failed.
 */
static rt_err_t clk_notify(struct rt_clk_node *clk_np, rt_ubase_t msg,
        rt_ubase_t old_rate, rt_ubase_t new_rate)
{
    rt_err_t err = RT_EOK;
    struct rt_clk_notifier *notifier;

    rt_list_for_each_entry(notifier, &_clk_notifier_nodes, list)
    {
        if (notifier->clk->cell->clk_np == clk_np)
        {
            err = notifier->callback(notifier, msg, old_rate, new_rate);

            /* Only check hareware's error */
            if (err == -RT_EIO)
            {
                break;
            }
        }
    }

    return err;
}

static void clk_unprepare(struct rt_clk *clk);
static void clk_disable(struct rt_clk *clk);
static rt_ubase_t clk_round_rate(struct rt_clk *clk, rt_ubase_t rate);
static rt_err_t clk_set_rate(struct rt_clk *clk, rt_ubase_t rate);
static rt_err_t clk_set_parent(struct rt_clk *clk, struct rt_clk *parent);
static struct rt_clk *clk_get_parent(struct rt_clk *clk);
static rt_ubase_t clk_get_rate(struct rt_clk *clk);

static struct rt_clk *clk_cell_get_clk(struct rt_clk_cell *cell);

/**
 * @brief   Recursively prepare clock
 *
 * @param   clk             Ponit to clock that will be prepared
 *
 * @return  rt_err_t        RT_EOK on prepare clock sucessfully, and other value is failed.
 */
static rt_err_t clk_prepare(struct rt_clk *clk)
{
    rt_err_t err;
    struct rt_clk *parent;
    struct rt_clk_cell *cell;

    cell = clk->cell;

    /* Already prepared */
    if (cell->prepare_count++ > 0)
    {
        return RT_EOK;
    }

    parent = clk_get_parent(clk);

    if (parent)
    {
        if ((err = clk_prepare(parent)))
        {
            goto _fail;
        }
    }

    if (cell->ops->prepare)
    {
        if ((err = cell->ops->prepare(cell)))
        {
            if (parent)
            {
                clk_unprepare(parent);
            }

            goto _fail;
        }
    }

    return RT_EOK;

_fail:
    --cell->prepare_count;
    return err;
}

/**
 * @brief   Prepare clock
 *
 * @param   clk
 *
 * @return  rt_err_t        RT_EOK on prepare clock sucessfully, and other value is failed.
 */
rt_err_t rt_clk_prepare(struct rt_clk *clk)
{
    rt_err_t err;

    RT_DEBUG_NOT_IN_INTERRUPT;

    if (clk)
    {
        clk_lock();
        err = clk_prepare(clk);
        clk_unlock();
    }
    else
    {
        err = RT_EOK;
    }

    return err;
}

/**
 * @brief   Recursively unprepare clock
 *
 * @param   clk             Ponit to clock that will be unprepared
 *
 */
static void clk_unprepare(struct rt_clk *clk)
{
    struct rt_clk *parent;
    struct rt_clk_cell *cell;

    cell = clk->cell;

    /* Don't unprepare readly */
    if (cell->prepare_count-- > 1)
    {
        return;
    }

    if (cell->ops->unprepare)
    {
        cell->ops->unprepare(cell);
    }

    parent = clk_get_parent(clk);

    if (parent)
    {
        clk_unprepare(parent);
    }
}

/**
 * @brief   Unprepare clock
 *
 * @param   clk             Ponit to clock that will be unprepared
 *
 */
void rt_clk_unprepare(struct rt_clk *clk)
{
    RT_DEBUG_NOT_IN_INTERRUPT;

    if (clk)
    {
        clk_lock();
        clk_unprepare(clk);
        clk_unlock();
    }
}

/**
 * @brief   Enable clock
 *
 * @param   clk             point to clock
 *
 * @return  rt_err_t        RT_EOK on enable clock FOREVER.
 */
static rt_err_t clk_enable(struct rt_clk *clk)
{
    rt_err_t err;
    struct rt_clk *parent;
    struct rt_clk_cell *cell;

    cell = clk->cell;

    /* Already enabled */
    if (cell->enable_count++ > 0)
    {
        return RT_EOK;
    }

    parent = clk_get_parent(clk);

    if (parent)
    {
        if ((err = clk_enable(parent)))
        {
            goto _fail;
        }
    }

    if (cell->ops->enable)
    {
        if ((err = cell->ops->enable(cell)))
        {
            if (parent)
            {
                clk_disable(parent);
            }

            goto _fail;
        }
    }

    return RT_EOK;

_fail:
    --cell->enable_count;
    return err;
}

/**
 * @brief   Enable clock
 *
 * @param   clk             point to clock
 *
 * @return  rt_err_t        RT_EOK on enable clock sucessfully, and other value is failed.
 */
rt_err_t rt_clk_enable(struct rt_clk *clk)
{
    rt_err_t err;

    if (clk)
    {
        clk_lock();
        err = clk_enable(clk);
        clk_unlock();
    }
    else
    {
        err = RT_EOK;
    }

    return err;
}

/**
 * @brief   Recursively disable clock
 *
 * @param   clk             Ponit to clock that will be disabled
 *
 */
static void clk_disable(struct rt_clk *clk)
{
    struct rt_clk *parent;
    struct rt_clk_cell *cell;

    cell = clk->cell;

    if (cell->enable_count == 0)
    {
        LOG_W("%s: Disable called with count = 0", cell->name);
        return;
    }

    if (cell->enable_count-- > 1)
    {
        return;
    }

    if (cell->flags & RT_CLK_F_IS_CRITICAL)
    {
        return;
    }

    if (clk_ignore_unused && cell->flags & RT_CLK_F_IGNORE_UNUSED)
    {
        return;
    }

    if (cell->ops->disable)
    {
        cell->ops->disable(cell);
    }

    parent = clk_get_parent(clk);

    if (parent)
    {
        clk_disable(parent);
    }
}

/**
 * @brief   Disable clock
 *
 * @param   clk             point to clock
 *
 */
void rt_clk_disable(struct rt_clk *clk)
{
    if (clk)
    {
        clk_lock();
        clk_disable(clk);
        clk_unlock();
    }
}

/**
 * @brief   Prepare and enable clock
 *
 * @param   clk             point to clock
 *
 * @return  rt_err_t        RT_EOK on prepare and enable clock sucessfully, and other value is failed.
 */
rt_err_t rt_clk_prepare_enable(struct rt_clk *clk)
{
    rt_err_t err;

    RT_DEBUG_NOT_IN_INTERRUPT;

    if (clk)
    {
        clk_lock();
        if (!(err = clk_prepare(clk)))
        {
            if ((err = clk_enable(clk)))
            {
                clk_unprepare(clk);
            }
        }
        clk_unlock();
    }
    else
    {
        err = RT_EOK;
    }

    return err;
}

/**
 * @brief   Disable and unprepare clock
 *
 * @param   clk             point to clock
 *
 */
void rt_clk_disable_unprepare(struct rt_clk *clk)
{
    RT_DEBUG_NOT_IN_INTERRUPT;

    if (clk)
    {
        clk_lock();
        clk_disable(clk);
        clk_unprepare(clk);
        clk_unlock();
    }
}

/**
 * @brief   Prepare clock array for mutipule out clock
 *
 * @param   clk_arr         point to clock array
 *
 * @return  rt_err_t        RT_EOK on prepare clock array sucessfully, and other value is failed.
 */
rt_err_t rt_clk_array_prepare(struct rt_clk_array *clk_arr)
{
    rt_err_t err;

    if (clk_arr)
    {
        for (int i = 0; i < clk_arr->count; ++i)
        {
            if ((err = rt_clk_prepare(clk_arr->clks[i])))
            {
                LOG_E("CLK Array[%d] %s failed error = %s", i,
                        "prepare", rt_strerror(err));

                while (i --> 0)
                {
                    rt_clk_unprepare(clk_arr->clks[i]);
                }

                break;
            }
        }
    }
    else
    {
        err = RT_EOK;
    }

    return err;
}

/**
 * @brief   Unprepare clock array for mutipule out clock
 *
 * @param   clk_arr         point to clock array
 *
 */
void rt_clk_array_unprepare(struct rt_clk_array *clk_arr)
{
    if (clk_arr)
    {
        for (int i = 0; i < clk_arr->count; ++i)
        {
            rt_clk_unprepare(clk_arr->clks[i]);
        }
    }
}

/**
 * @brief   Enable clock array for mutipule out clock
 *
 * @param   clk_arr         point to clock array
 *
 * @return  rt_err_t        RT_EOK on Enable clock array sucessfully, and other value is failed.
 */
rt_err_t rt_clk_array_enable(struct rt_clk_array *clk_arr)
{
    rt_err_t err;

    if (clk_arr)
    {
        for (int i = 0; i < clk_arr->count; ++i)
        {
            if ((err = rt_clk_enable(clk_arr->clks[i])))
            {
                LOG_E("CLK Array[%d] %s failed error = %s", i,
                        "enable", rt_strerror(err));

                while (i --> 0)
                {
                    rt_clk_disable(clk_arr->clks[i]);
                }

                break;
            }
        }
    }
    else
    {
        err = RT_EOK;
    }

    return err;
}

/**
 * @brief   Enable clock array for mutipule out clock
 *
 * @param   clk_arr         point to clock array
 *
 */
void rt_clk_array_disable(struct rt_clk_array *clk_arr)
{
    if (clk_arr)
    {
        for (int i = 0; i < clk_arr->count; ++i)
        {
            rt_clk_disable(clk_arr->clks[i]);
        }
    }
}

/**
 * @brief   Prepare and enable clock array
 *
 * @param   clk_arr         point to clock array
 *
 * @return  rt_err_t        RT_EOK on prepare and enable clock array sucessfully, and other
                            value is failed.
 */
rt_err_t rt_clk_array_prepare_enable(struct rt_clk_array *clk_arr)
{
    rt_err_t err;

    if ((err = rt_clk_array_prepare(clk_arr)))
    {
        return err;
    }

    if ((err = rt_clk_array_enable(clk_arr)))
    {
        rt_clk_array_unprepare(clk_arr);
    }

    return err;
}

/**
 * @brief   Disable and unprepare clock array
 *
 * @param   clk_arr         point to clock array
 *
 */
void rt_clk_array_disable_unprepare(struct rt_clk_array *clk_arr)
{
    rt_clk_array_disable(clk_arr);
    rt_clk_array_unprepare(clk_arr);
}

/**
 * @brief   Set and clamp clock rate within specified range.
 *
 * @details This function updates the minimum and maximum allowed rate
 *          of a clock, clamps its current rate to the new range, and
 *          immediately applies the change via set_rate().
 *
 * @param   clk     Pointer to clock handle.
 * @param   min     Minimum allowed rate (Hz).
 * @param   max     Maximum allowed rate (Hz).
 *
 * @retval  RT_EOK          Successfully updated.
 * @retval  -RT_EINVAL      Invalid parameter or range.
 * @retval  -RT_ENOSYS      Clock driver does not support set_rate().
 * @retval  other           Hardware-specific error returned by set_rate().
 */
static rt_err_t clk_set_rate_range(struct rt_clk *clk, rt_ubase_t min, rt_ubase_t max)
{
    rt_err_t err;
    rt_ubase_t rate, old_min, old_max;
    struct rt_clk_cell *cell;

    if (min > max)
    {
        return -RT_EINVAL;
    }

    cell = clk->cell;

    old_min = clk->min_rate;
    old_max = clk->max_rate;

    clk->min_rate = min;
    clk->max_rate = max;

    if (cell->flags & RT_CLK_F_GET_RATE_NOCACHE)
    {
        rate = clk_get_rate(clk);
    }
    else
    {
        rate = cell->rate;
    }

    if ((err = clk_set_rate(clk, rt_clamp(rate, min, max))))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    clk->min_rate = old_min;
    clk->max_rate = old_max;

    return err;
}

/**
 * @brief   Set clock rate range
 *
 * @param   clk             point to clock
 * @param   min             minimum clock rate
 * @param   max             minimum clock rate
 *
 * @return  rt_err_t        RT_EOK on set clock rate range sucessfully, and other value is failed.
 */
rt_err_t rt_clk_set_rate_range(struct rt_clk *clk, rt_ubase_t min, rt_ubase_t max)
{
    rt_err_t err;

    if (!clk)
    {
        return RT_EOK;
    }

    clk_lock();
    err = clk_set_rate_range(clk, min, max);
    clk_unlock();

    return err;
}

/**
 * @brief   Set minimum clock rate
 *
 * @param   clk             point to clock
 * @param   rate            miminum clock rate
 *
 * @return  rt_err_t        RT_EOK on set minimum clock rate sucessfully, and other value is failed.
 */
rt_err_t rt_clk_set_min_rate(struct rt_clk *clk, rt_ubase_t rate)
{
    if (clk)
    {
        return rt_clk_set_rate_range(clk, rate, clk->max_rate);
    }

    return RT_EOK;
}

/**
 * @brief   Set maximum clock rate
 *
 * @param   clk             point to clock
 * @param   rate            maximum clock rate
 *
 * @return  rt_err_t        RT_EOK on set maximum clock rate sucessfully, and other value is failed.
 */
rt_err_t rt_clk_set_max_rate(struct rt_clk *clk, rt_ubase_t rate)
{
    if (clk)
    {
        return rt_clk_set_rate_range(clk, clk->min_rate, rate);
    }

    return RT_EOK;
}

/**
 * @brief   Set clock rate.
 *
 * @details This function directly sets the frequency of the given clock.
 *          If the hardware driver supports set_rate(), the new rate will
 *          be applied immediately and the cached rate will be updated.
 *
 * @param   clk     Pointer to clock handle.
 * @param   rate    Target frequency (Hz).
 *
 * @retval  RT_EOK          Successfully updated.
 * @retval  -RT_EINVAL      Invalid parameter.
 * @retval  -RT_ENOSYS      Clock driver does not support set_rate().
 * @retval  other           Hardware-specific error returned by set_rate().
 */
static rt_err_t clk_set_rate(struct rt_clk *clk, rt_ubase_t rate)
{
    rt_err_t err;
    rt_ubase_t old_rate, prate;
    rt_bool_t was_enabled = RT_FALSE;
    rt_bool_t was_disabled = RT_FALSE;
    struct rt_clk *parent = RT_NULL;
    struct rt_clk_node *clk_np;
    struct rt_clk_cell *cell;

    cell = clk->cell;

    if (!cell->ops->set_rate)
    {
        return -RT_ENOSYS;
    }

    clk_np = cell->clk_np;

    if (cell->flags & RT_CLK_F_GET_RATE_NOCACHE)
    {
        old_rate = clk_get_rate(clk);
    }
    else
    {
        old_rate = cell->rate;
    }
    rate = rt_clamp(rate, clk->min_rate, clk->max_rate);

    parent = clk_get_parent(clk);

    if (cell->parents_nr > 1)
    {
        rt_uint8_t best_idx = RT_UINT8_MAX;
        rt_ubase_t best_rounded = 0, best_diff = ~0UL;
        struct rt_clk_cell *parent_cell, *best_parent_cell = RT_NULL;

        for (rt_uint8_t idx = 0; idx < cell->parents_nr; ++idx)
        {
            rt_ubase_t rounded, diff;

            if (!(parent_cell = rt_clk_cell_get_parent_by_index(cell, idx)))
            {
                continue;
            }

            if (!parent_cell->clk && !(parent_cell->clk = clk_cell_get_clk(parent_cell)))
            {
                return RT_NULL;
            }

            prate = clk_get_rate(parent_cell->clk);
            rounded = clk_round_rate(parent_cell->clk, rate);
            rounded = (rounded > 0) ? rounded : rate;

            diff = rt_abs(rounded - rate);

            if (diff < best_diff)
            {
                best_idx = idx;
                best_diff = diff;
                best_rounded = rounded;
                best_parent_cell = parent_cell;
            }
        }

        if (best_idx != RT_UINT8_MAX && parent->cell != best_parent_cell)
        {
            parent = best_parent_cell->clk;

            if ((err = clk_set_parent(clk, parent)))
            {
                return err;
            }

            rate = best_rounded;
        }
    }

    if (parent)
    {
        if (cell->flags & RT_CLK_F_SET_RATE_PARENT)
        {
            if ((err = clk_set_rate(parent, rate)))
            {
                return err;
            }
        }

        prate = clk_get_rate(parent);
    }
    else
    {
        prate = 0;
    }

    if ((cell->flags & RT_CLK_F_SET_RATE_GATE) && cell->enable_count > 0)
    {
        was_enabled = RT_TRUE;
        clk_disable(clk);
    }
    else if ((cell->flags & RT_CLK_F_SET_RATE_UNGATE) && cell->enable_count == 0)
    {
        was_disabled = RT_TRUE;
        clk_enable(clk);
    }

    clk_notify(clk_np, RT_CLK_MSG_PRE_RATE_CHANGE, old_rate, rate);

    if ((err = cell->ops->set_rate(cell, rate, prate)))
    {
        clk_notify(clk_np, RT_CLK_MSG_ABORT_RATE_CHANGE, old_rate, rate);

        goto _end;
    }

    /* Update cached rate */
    cell->rate = rate;

    clk_notify(clk_np, RT_CLK_MSG_POST_RATE_CHANGE, old_rate, rate);

_end:
    if (was_enabled)
    {
        clk_enable(clk);
    }
    else if (was_disabled)
    {
        clk_disable(clk);
    }

    return err;
}

/**
 * @brief   Set clock rate
 *
 * @param   clk             point to clock
 * @param   rate            target rate
 *
 * @return  rt_err_t        RT_EOK on set clock rate sucessfully, and other value is failed.
 */
rt_err_t rt_clk_set_rate(struct rt_clk *clk, rt_ubase_t rate)
{
    rt_err_t err;

    if (clk)
    {
        clk_lock();
        err = clk_set_rate(clk, rate);
        clk_unlock();
    }
    else
    {
        err = RT_EOK;
    }

    return err;
}

/**
 * @brief   Internal helper to get clock rate (no locking, no validation).
 *
 * @param   clk     Pointer to clock handle.
 *
 * @return  Clock frequency in Hz, or 0 if invalid.
 */
static rt_ubase_t clk_get_rate(struct rt_clk *clk)
{
    rt_ubase_t prate;
    struct rt_clk *parent;
    struct rt_clk_cell *cell;

    cell = clk->cell;
    parent = clk_get_parent(clk);
    prate = parent ? clk_get_rate(parent) : 0;

    if (cell->ops->recalc_rate)
    {
        cell->rate = cell->ops->recalc_rate(cell, prate);
    }
    else
    {
        cell->rate = prate;
    }

    return cell->rate;
}

/**
 * @brief   Get clock rate
 *
 * @param   clk             point to clock
 *
 * @return  rt_ubase_t      clock rate or error code
 */
rt_ubase_t rt_clk_get_rate(struct rt_clk *clk)
{
    rt_ubase_t rate;

    if (clk)
    {
        clk_lock();
        rate = clk_get_rate(clk);
        clk_unlock();
    }
    else
    {
        rate = 0;
    }

    return rate;
}

/**
 * @brief   Internal helper to round clock rate (no locking).
 *
 * @param   clk     Pointer to clock handle.
 * @param   rate    Desired frequency in Hz.
 *
 * @return  Rounded frequency in Hz (may differ from requested value).
 */
static rt_ubase_t clk_round_rate(struct rt_clk *clk, rt_ubase_t rate)
{
    rt_ubase_t prate, rounded = rate;
    struct rt_clk *parent;
    struct rt_clk_cell *cell;

    cell = clk->cell;

    parent = clk_get_parent(clk);
    prate = parent ? clk_get_rate(parent) : 0;

    /* If driver provides round_rate() callback, use it */
    if (cell->ops->round_rate)
    {
        rt_base_t res = cell->ops->round_rate(cell, rate, &prate);

        if (res > 0)
        {
            rounded = res;
        }
    }
    else if ((cell->flags & RT_CLK_F_SET_RATE_PARENT) && parent)
    {
        /* Delegate rounding to parent clock if supported */
        rounded = clk_round_rate(parent, rate);
    }

    /* Clamp to valid range */
    return rt_clamp(rounded, clk->min_rate, clk->max_rate);
}

/**
 * @brief   Check if clock rate is in the minimum to maximun and get it
 *
 * @param   clk             point to clock
 * @param   rate            rate will be checked
 *
 * @return  rt_base_t       get the correct rate
 * @note    if parameter rate less than the minimum or more than maximum, the
            retrun rate will be set to minimum ormaximum value
 */
rt_base_t rt_clk_round_rate(struct rt_clk *clk, rt_ubase_t rate)
{
    rt_ubase_t rounded = 0;

    if (clk)
    {
        clk_lock();
        rounded = clk_round_rate(clk, rate);
        clk_unlock();
    }

    return rounded;
}

/**
 * @brief   Set parent clock
 *
 * @param   clk_np          point to clock node
 * @param   parent_np       point to parent rt_clk
 *
 * @return  rt_err_t        RT_EOK on set clock parent sucessfully, and other value is failed.
 */
static rt_err_t clk_set_parent(struct rt_clk *clk, struct rt_clk *parent)
{
    rt_err_t err;
    rt_uint8_t idx = RT_UINT8_MAX;
    rt_bool_t was_enabled = RT_FALSE;
    struct rt_clk_cell *cell;

    cell = clk->cell;

    /* Already same parent? */
    if (parent)
    {
        if (cell->parent == parent->cell->clk)
        {
            return RT_EOK;
        }
    }
    else if (!cell->parent)
    {
        return RT_EOK;
    }

    /* No multi-parent */
    if (cell->parents_nr <= 1)
    {
        return -RT_EINVAL;
    }

    /* Multi-parent but driver lacks support */
    if (!cell->ops->set_parent)
    {
        return -RT_EINVAL;
    }

    /* Find new parent index if provided */
    if (parent)
    {
        const char *pname = parent->cell->name;

        /* Temporarily gate if required */
        if ((cell->flags & RT_CLK_F_SET_PARENT_GATE) && cell->enable_count > 0)
        {
            was_enabled = RT_TRUE;
            clk_disable(clk);
        }

        for (int i = 0; i < cell->parents_nr; ++i)
        {
            if (!rt_strcmp(cell->parent_names[i], pname))
            {
                idx = i;
                break;
            }
        }

        if (idx == RT_UINT8_MAX)
        {
            LOG_W("%s: Invalid parent %s", cell->name, pname);
            err = -RT_EINVAL;
            goto _end;
        }

        if (cell->ops->set_parent)
        {
            if (!(err = cell->ops->set_parent(cell, idx)))
            {
                cell->parent = parent->cell->clk;
            }
        }
        else
        {
            err = -RT_ENOSYS;
        }

    _end:
        if (was_enabled)
        {
            clk_enable(clk);
        }
    }
    else
    {
        err = RT_EOK;
    }

    return err;
}

/**
 * @brief   Set clock parent object
 *
 * @param   clk             point to clock
 * @param   clk_parent      point to parent clock
 *
 * @return  rt_err_t        RT_EOK on set clock parent sucessfully, and other value is failed.
 */
rt_err_t rt_clk_set_parent(struct rt_clk *clk, struct rt_clk *clk_parent)
{
    rt_err_t err;

    if (clk)
    {
        clk_lock();
        err = clk_set_parent(clk, clk_parent);
        clk_unlock();
    }
    else
    {
        err = RT_EOK;
    }

    return err;
}

/**
 * @brief   Resolve and return the parent clock of a given clock handle.
 *
 * @details This function determines the parent clock for the provided
 *          clock handle (`clk`). It first checks for an existing cached
 *          parent, and if none exists:
 *          1. Calls the driver's `get_parent()` callback to retrieve
 *             the parent index.
 *          2. Looks up the corresponding parent clock by name from:
 *             - The controller's `parents_clk` array, or
 *             - The controller's own `cells` array.
 *          3. If a matching cell exists but no rt_clk handle yet, a new
 *             handle is allocated via `clk_alloc()`.
 *          4. The resolved parent is cached in `cell->parent`.
 *
 * @param   clk     Pointer to the clock handle.
 *
 * @return  Pointer to the parent clock handle, or NULL on failure.
 */
static struct rt_clk *clk_get_parent(struct rt_clk *clk)
{
    rt_uint8_t idx;
    struct rt_clk *parent;
    struct rt_clk_cell *cell, *parent_cell;

    cell = clk->cell;

    if (!cell->parent_names)
    {
        return RT_NULL;
    }

    if (cell->parent)
    {
        return cell->parent;
    }

    if (cell->parents_nr > 1)
    {
        if (!cell->ops->get_parent)
        {
            LOG_E("%s: Missing get_parent() while having parent_names", cell->name);
            return RT_NULL;
        }

        idx = cell->ops->get_parent(cell);

        if (idx >= cell->parents_nr)
        {
            LOG_E("%s: Get parent fail", cell->name);
            return RT_NULL;
        }
    }
    else
    {
        idx = 0;
    }

    parent_cell = rt_clk_cell_get_parent_by_index(cell, idx);

    if (!parent_cell)
    {
        return RT_NULL;
    }

    if (!parent_cell->clk && !(parent_cell->clk = clk_cell_get_clk(parent_cell)))
    {
        return RT_NULL;
    }

    parent = parent_cell->clk;
    cell->parent = parent;

    return parent;
}

/**
 * @brief   Get parent clock pointer
 *
 * @param   clk             child clock
 *
 * @return  struct rt_clk*  parent clock object pointer will be return, unless child
                            clock node havn't parent node instead return RT_NULL
 */
struct rt_clk *rt_clk_get_parent(struct rt_clk *clk)
{
    struct rt_clk *parent;

    if (clk)
    {
        clk_lock();
        parent = clk_get_parent(clk);
        clk_unlock();
    }
    else
    {
        parent = RT_NULL;
    }

    return parent;
}

/**
 * @brief   Set clock phase
 *
 * @param   clk             point to clock
 * @param   degrees         target phase and the unit of phase is degree
 *
 * @return  rt_err_t        RT_EOK on set clock phase sucessfully, and other value is failed.
 */
rt_err_t rt_clk_set_phase(struct rt_clk *clk, int degrees)
{
    rt_err_t err;

    if (clk)
    {
        struct rt_clk_cell *cell = clk->cell;

        /* Sanity check degrees */
        degrees %= 360;

        if (degrees < 0)
        {
            degrees += 360;
        }

        if (cell->ops->set_phase)
        {
            err = cell->ops->set_phase(cell, degrees);
        }
        else
        {
            err = -RT_ENOSYS;
        }
    }
    else
    {
        err = RT_EOK;
    }

    return err;
}

/**
 * @brief   Get clock phase
 *
 * @param   clk             point to clock
 *
 * @return  rt_base_t       clock phase or error code
 */
rt_base_t rt_clk_get_phase(struct rt_clk *clk)
{
    rt_base_t res;

    if (clk)
    {
        struct rt_clk_cell *cell = clk->cell;

        if (cell->ops->get_phase)
        {
            res = cell->ops->get_phase(cell);
        }
        else
        {
            res = 0;
        }
    }
    else
    {
        res = 0;
    }

    return res;
}

/**
 * @brief   Check if the clock cell is prepared
 *
 * @param   cell    Pointer to clock cell
 *
 * @return  RT_TRUE if prepared, otherwise RT_FALSE
 */
rt_bool_t rt_clk_cell_is_prepared(const struct rt_clk_cell *cell)
{
    RT_ASSERT(cell != RT_NULL);

    if (cell->ops->is_prepared)
    {
        return cell->ops->is_prepared((struct rt_clk_cell *)cell);
    }

    return RT_TRUE;
}

/**
 * @brief   Get or create clock handle for a clock cell
 *
 * @param   cell    Pointer to clock cell
 *
 * @return  Pointer to clock handle, or RT_NULL on failure
 *
 * @note    If the clock handle does not exist, it will be created automatically.
 */
static struct rt_clk *clk_cell_get_clk(struct rt_clk_cell *cell)
{
    if (cell->clk)
    {
        return cell->clk;
    }

    cell->clk = clk_alloc(cell, RT_NULL, RT_NULL);

    return cell->clk;
}

/**
 * @brief   Get or create clock handle for a clock cell
 *
 * @param   cell    Pointer to clock cell
 * @param   con_id  Connection identifier for the clock cell
 *
 * @return  Pointer to clock handle, or RT_NULL on failure
 *
 * @note    If the clock handle does not exist, it will be created automatically.
 */
struct rt_clk *rt_clk_cell_get_clk(const struct rt_clk_cell *cell, const char *con_id)
{
    struct rt_clk *clk;

    RT_ASSERT(cell != RT_NULL);

    if ((clk = clk_cell_get_clk((struct rt_clk_cell *)cell)))
    {
        if (!clk->con_id)
        {
            clk->con_id = con_id;
        }
    }

    return clk;
}

/**
 * @brief   Check if the clock cell is enabled
 *
 * @param   cell    Pointer to clock cell
 *
 * @return  RT_TRUE if enabled, otherwise RT_FALSE
 */
rt_bool_t rt_clk_cell_is_enabled(const struct rt_clk_cell *cell)
{
    RT_ASSERT(cell != RT_NULL);

    if (cell->ops->is_enabled)
    {
        return cell->ops->is_enabled((struct rt_clk_cell *)cell);
    }

    return RT_TRUE;
}

/**
 * @brief   Get current rate of the clock cell
 *
 * @param   cell    Pointer to clock cell
 *
 * @return  Current rate in Hz
 */
rt_ubase_t rt_clk_cell_get_rate(const struct rt_clk_cell *cell)
{
    struct rt_clk *clk;

    RT_ASSERT(cell != RT_NULL);

    clk = clk_cell_get_clk((struct rt_clk_cell *)cell);

    return clk_get_rate(clk);
}

/**
 * @brief   Round a desired rate to the nearest supported rate
 *
 * @param   cell    Pointer to clock cell
 * @param   rate    Desired frequency in Hz
 *
 * @return  Closest supported frequency in Hz
 */
rt_ubase_t rt_clk_cell_round_rate(struct rt_clk_cell *cell, rt_ubase_t rate)
{
    struct rt_clk *clk;

    RT_ASSERT(cell != RT_NULL);

    clk = clk_cell_get_clk((struct rt_clk_cell *)cell);

    return clk_round_rate(clk, rate);
}

/**
 * @brief   Get parent clock cell
 *
 * @param   cell    Pointer to clock cell
 *
 * @return  Pointer to parent clock cell, or RT_NULL if none
 */
struct rt_clk_cell *rt_clk_cell_get_parent(const struct rt_clk_cell *cell)
{
    struct rt_clk *clk, *parent_clk;

    RT_ASSERT(cell != RT_NULL);

    clk = clk_cell_get_clk((struct rt_clk_cell *)cell);

    if ((parent_clk = clk_get_parent(clk)))
    {
        return parent_clk->cell;
    }

    return RT_NULL;
}

/**
 * @brief   Get parent clock cell by index
 *
 * @param   cell    Pointer to clock cell
 * @param   idx     Parent index
 *
 * @return  Pointer to parent clock cell, or RT_NULL if not found
 */
struct rt_clk_cell *rt_clk_cell_get_parent_by_index(const struct rt_clk_cell *cell, rt_uint8_t idx)
{
    const char *pname;
    struct rt_clk_cell *parent_cell;
    struct rt_clk_node *clk_np, *clk_np_raw;

    RT_ASSERT(cell != RT_NULL);
    RT_ASSERT(idx != RT_UINT8_MAX);

    clk_np = cell->clk_np;

    if (cell->parents_nr > 1)
    {
        pname = cell->parent_names[idx];
    }
    else if (idx == 0)
    {
        pname = cell->parent_name;
    }
    else
    {
        pname = RT_NULL;
        goto _end;
    }

    clk_np_raw = RT_NULL;

_retry:
    if (!rt_is_err_or_null(clk_np->parents_clk))
    {
        struct rt_clk_array *parents_clk = clk_np->parents_clk;

        for (rt_uint8_t i = 0; i < parents_clk->count; ++i)
        {
            if (!rt_strcmp(pname, parents_clk->clks[i]->cell->name))
            {
                return parents_clk->clks[i]->cell;
            }
        }
    }

    for (int i = 0; i < clk_np->cells_nr; ++i)
    {
        parent_cell = clk_np->cells[i];

        if (!parent_cell)
        {
            continue;
        }

        if (!rt_strcmp(parent_cell->name, pname))
        {
            return (struct rt_clk_cell *)parent_cell;
        }
    }

    /* Find on the global list */
    if (clk_np_raw)
    {
        do {
            clk_np = rt_list_entry(clk_np->parent.list.next, rt_typeof(*clk_np), parent.list);
        } while (&clk_np->parent.list != &_clk_node_nodes && clk_np == clk_np_raw);
    }
    else
    {
        clk_np_raw = clk_np;
        clk_np = rt_list_entry(_clk_node_nodes.next, rt_typeof(*clk_np), parent.list);
    }

    if (&clk_np->parent.list != &_clk_node_nodes)
    {
        goto _retry;
    }

_end:
    LOG_E("%s: Parent[%d] '%s' not found", cell->name, idx, pname);

    return RT_NULL;
}

/**
 * @brief   Get current parent index
 *
 * @param   cell    Pointer to clock cell
 *
 * @return  Parent index on success, negative error code on failure
 */
rt_uint8_t rt_clk_cell_get_parent_index(struct rt_clk_cell *cell)
{
    RT_ASSERT(cell != RT_NULL);

    if (cell->ops->get_parent)
    {
        return cell->ops->get_parent(cell);
    }

    return RT_UINT8_MAX;
}

/**
 * @brief   Set new parent clock cell
 *
 * @param   cell    Pointer to clock cell
 * @param   parent  Pointer to new parent clock cell
 *
 * @return  RT_EOK on success, or error code on failure
 */
rt_err_t rt_clk_cell_set_parent(struct rt_clk_cell *cell, struct rt_clk_cell *parent)
{
    rt_err_t err;
    struct rt_clk *clk, *parent_clk = RT_NULL;

    RT_ASSERT(cell != RT_NULL);

    clk = clk_cell_get_clk((struct rt_clk_cell *)cell);

    if (parent)
    {
        parent_clk = clk_cell_get_clk((struct rt_clk_cell *)parent);
    }

    if ((err = clk_set_parent(clk, parent_clk)))
    {
        return err;
    }

    return RT_EOK;
}

/**
 * @brief   Get clock array pointer from ofw device node
 *
 * @param   dev                     point to dev
 *
 * @return  struct rt_clk_array*    if use ofw and under normal circumstance, it will return
                                    clock array pointer and other value is RT_NULL
 */
struct rt_clk_array *rt_clk_get_array(struct rt_device *dev)
{
    struct rt_clk_array *clk_arr = RT_NULL;

#ifdef RT_USING_OFW
    clk_arr = rt_ofw_get_clk_array(dev->ofw_node);
#endif

    return clk_arr;
}

/**
 * @brief   Get clock pointer from ofw device node by index
 *
 * @param   dev             point to dev
 * @param   index           index of clock object
 *
 * @return  struct rt_clk*  if use ofw and under normal circumstance, it will return clock
                            pointer and other value is RT_NULL
 */
struct rt_clk *rt_clk_get_by_index(struct rt_device *dev, int index)
{
    struct rt_clk *clk = RT_NULL;

#ifdef RT_USING_OFW
    clk = rt_ofw_get_clk(dev->ofw_node, index);
#endif

    return clk;
}

/**
 * @brief   Get clock pointer from ofw device node by name
 *
 * @param   dev             point to dev
 * @param   name            name of clock object
 *
 * @return  struct rt_clk*  if use ofw and under normal circumstance, it will return clock
                            pointer and other value is RT_NULL
 */
struct rt_clk *rt_clk_get_by_name(struct rt_device *dev, const char *name)
{
    struct rt_clk *clk = RT_NULL;

#ifdef RT_USING_OFW
    clk = rt_ofw_get_clk_by_name(dev->ofw_node, name);
#endif

    if (!clk && name)
    {
        struct rt_clk_node *clk_np;
        struct rt_clk_cell *cell = RT_NULL;

        clk_lock();
        rt_list_for_each_entry(clk_np, &_clk_node_nodes, parent.list)
        {
            for (int i = 0; i < clk_np->cells_nr; ++i)
            {
                cell = clk_np->cells[i];

                if (!cell)
                {
                    continue;
                }

                if (!rt_strcmp(cell->name, name))
                {
                    clk = clk_alloc(cell, rt_dm_dev_get_name(dev), RT_NULL);

                    if (clk)
                    {
                        clk_cell_bind(cell, clk);
                    }

                    goto _out_lock;
                }
            }
        }
    _out_lock:
        clk_unlock();
    }

    return clk;
}

/**
 * @brief   Put reference count of all colock in the clock array
 *
 * @param   clk_arr         point to clock array
 *
 */
void rt_clk_array_put(struct rt_clk_array *clk_arr)
{
    if (clk_arr)
    {
        for (int i = 0; i < clk_arr->count; ++i)
        {
            if (!rt_is_err_or_null(clk_arr->clks[i]))
            {
                rt_clk_put(clk_arr->clks[i]);
            }
            else
            {
                break;
            }
        }

        rt_free(clk_arr);
    }
}

/**
 * @brief   Put reference count of clock
 *
 * @param   clk             point to clock
 *
 */
void rt_clk_put(struct rt_clk *clk)
{
    if (clk && clk->cell->clk != clk)
    {
        rt_free(clk);
    }
}

#ifdef RT_USING_OFW
static struct rt_clk_array *ofw_get_clk_array(struct rt_ofw_node *np,
        const char *basename, const char *propname);
static struct rt_clk *ofw_get_clk(struct rt_ofw_node *np,
        const char *basename, int index, const char *name);

/**
 * @brief   Retrieve a clock cell from a clock node using OFW (device tree) arguments.
 *
 * @details
 * This helper function translates parsed device tree clock specifiers
 * (from `clocks = <&phandle args...>;`) into an actual `rt_clk_cell` pointer
 * belonging to the specified `clk_np` (clock node).
 *
 * Behavior:
 *  - If the clock node provides a custom parser (`clk_np->ofw_parse`),
 *    this function delegates the lookup to that callback.
 *    → This allows complex clock providers (e.g. multiplexers, dividers)
 *      to interpret multiple arguments or encoded indices.
 *  - Otherwise, it assumes the first argument (`args->args[0]`)
 *    is the cell index and directly returns `clk_np->cells[args->args[0]]`.
 *
 * This abstraction allows different clock providers to implement flexible
 * device-tree bindings without changing the core clock framework.
 *
 * @param   clk_np      Pointer to the clock node containing clock cells.
 * @param   args        Pointer to parsed OFW clock arguments (from device tree).
 *
 * @return  Pointer to the resolved `rt_clk_cell` if found, or `RT_NULL` on failure.
 *
 * @note
 *  - The default indexing behavior assumes that the clock node’s `#clock-cells`
 *    property equals 1 (only one integer index).
 *  - Complex clock providers should implement their own `.ofw_parse()` callback
 *    to handle multiple argument cases.
 *  - This function is typically used during `rt_ofw_clk_get()` to
 *    resolve device clock references.
 */
static struct rt_clk_cell *ofw_get_cell(struct rt_clk_node *clk_np, struct rt_ofw_cell_args *args)
{
    if (clk_np->ofw_parse)
    {
        return clk_np->ofw_parse(clk_np, args);
    }

    return clk_np->cells[args->args[0]];
}

/**
 * @brief   Get clock array from ofw by name
 *
 * @param   np                      point to ofw node
 * @param   basename                name of clocks base name
 * @param   propname                name of clocks prop name
 *
 * @return  struct rt_clk_array*    point to the newly created clock array, or an error pointer
 */
static struct rt_clk_array *ofw_get_clk_array(struct rt_ofw_node *np,
        const char *basename, const char *propname)
{
    int count;
    rt_bool_t has_name;
    struct rt_clk_array *clk_arr;

    if ((count = rt_ofw_count_phandle_cells(np, basename, "#clock-cells")) <= 0)
    {
        if (count)
        {
            return rt_err_ptr(count);
        }

        return RT_NULL;
    }

    clk_arr = rt_calloc(1, sizeof(*clk_arr) + sizeof(clk_arr->clks[0]) * count);

    if (!clk_arr)
    {
        return rt_err_ptr(-RT_ENOMEM);
    }

    clk_arr->count = count;
    has_name = rt_ofw_prop_read_bool(np, propname);

    clk_lock();
    for (int i = 0; i < count; ++i)
    {
        const char *name = RT_NULL;

        if (has_name)
        {
            rt_ofw_prop_read_string_index(np, "clock-names", i, &name);
        }

        clk_arr->clks[i] = ofw_get_clk(np, basename, i, name);

        if (rt_is_err(clk_arr->clks[i]))
        {
            rt_err_t err = rt_ptr_err(clk_arr->clks[i]);

            clk_unlock();

            rt_clk_array_put(clk_arr);

            return rt_err_ptr(err);
        }
    }
    clk_unlock();

    return clk_arr;
}

/**
 * @brief   Get clock array from ofw
 *
 * @param   np                      point to ofw node
 *
 * @return  struct rt_clk_array*    point to the newly created clock array, or an error pointer
 */
struct rt_clk_array *rt_ofw_get_clk_array(struct rt_ofw_node *np)
{
    if (!np)
    {
        return rt_err_ptr(-RT_EINVAL);
    }

    return ofw_get_clk_array(np, "clocks", "clock-names");
}

/**
 * @brief   Get clock from ofw
 *
 * @param   np              point to ofw node
 * @param   basename        name of clocks base name
 * @param   index           index of clock in ofw
 * @param   name            connection identifier for the clock
 *
 * @return  struct rt_clk*  point to the newly created clock object, or an error pointer
 */
static struct rt_clk *ofw_get_clk(struct rt_ofw_node *np,
        const char *basename, int index, const char *name)
{
    struct rt_object *obj;
    struct rt_clk *clk;
    struct rt_clk_cell *cell;
    struct rt_clk_node *clk_np = RT_NULL;
    struct rt_ofw_node *clk_ofw_np;
    struct rt_ofw_cell_args clk_args;

    if (rt_ofw_parse_phandle_cells(np, basename, "#clock-cells", index, &clk_args))
    {
        return RT_NULL;
    }

    clk_ofw_np = clk_args.data;

    if (!rt_ofw_data(clk_ofw_np))
    {
        if (clk_ofw_np == np)
        {
            LOG_D("%s: No registration to the system yet", rt_ofw_node_full_name(clk_ofw_np));
            return RT_NULL;
        }

        rt_platform_ofw_request(clk_ofw_np);
    }

    if (rt_ofw_data(clk_ofw_np) && (obj = rt_ofw_parse_object(clk_ofw_np,
                RT_CLK_NODE_OBJ_NAME, "#clock-cells")))
    {
        clk_np = rt_container_of(obj, struct rt_clk_node, parent);
    }

    if (!clk_np)
    {
        clk = rt_err_ptr(-RT_EINVAL);
        goto _end;
    }

    if (!clk_args.args_count)
    {
        clk_args.args[0] = 0;
    }
    index = clk_args.args[0];

    if (rt_ofw_prop_read_bool(clk_ofw_np, "clock-indices"))
    {
        const fdt32_t *val_raw;
        rt_uint32_t val, indice = 0;
        struct rt_ofw_prop *prop;

        rt_ofw_foreach_prop_u32(clk_ofw_np, "clock-indices", prop, val_raw, val)
        {
            if (index == val)
            {
                index = indice;
                goto _goon;
            }
            ++indice;
        }

        clk = rt_err_ptr(-RT_EINVAL);
        goto _end;
    }
_goon:

    rt_ofw_prop_read_string_index(clk_ofw_np, "clock-output-names", index, &name);

    if (!(cell = ofw_get_cell(clk_np, &clk_args)))
    {
        LOG_D("%s: CLK index = %d (%s) is not implemented",
                rt_ofw_node_full_name(np), index, name);
        return RT_NULL;
    }

    clk = clk_alloc(cell, rt_ofw_node_full_name(np), name);

    if (clk)
    {
        clk_cell_bind(cell, clk);
    }
    else
    {
        clk = rt_err_ptr(-RT_ENOMEM);
    }

_end:
    rt_ofw_node_put(clk_ofw_np);

    return clk;
}

/**
 * @brief   Get clock from ofw with acquiring a spin lock by index and node pointer
 *
 * @param   np              point to ofw node
 * @param   index           index of clock in ofw
 *
 * @return  struct rt_clk*  point to the newly created clock object, or an error pointer
 */
struct rt_clk *rt_ofw_get_clk(struct rt_ofw_node *np, int index)
{
    struct rt_clk *clk = RT_NULL;

    if (np && index >= 0)
    {
        clk = ofw_get_clk(np, "clocks", index, RT_NULL);
    }

    return clk;
}

/**
 * @brief   Get clock from ofw with acquiring a spin lock by name
 *
 * @param   np              point to ofw node
 * @param   name            name of clock will be returned
 *
 * @return  struct rt_clk*  point to the newly created clock object, or an error pointer
 */
struct rt_clk *rt_ofw_get_clk_by_name(struct rt_ofw_node *np, const char *name)
{
    struct rt_clk *clk = RT_NULL;

    if (np && name)
    {
        int index = rt_ofw_prop_index_of_string(np, "clock-names", name);

        if (index >= 0)
        {
            clk = ofw_get_clk(np, "clocks", index, name);
        }
    }

    return clk;
}

/**
 * @brief   Count number of clocks in ofw
 *
 * @param   clk_ofw_np      point to ofw node
 *
 * @return  rt_ssize_t      number of clocks
 */
rt_ssize_t rt_ofw_count_of_clk(struct rt_ofw_node *clk_ofw_np)
{
    if (clk_ofw_np)
    {
        struct rt_clk_node *clk_np = rt_ofw_data(clk_ofw_np);

        if (clk_np && clk_np->multi_clk)
        {
            return clk_np->multi_clk;
        }
        else
        {
            const fdt32_t *cell;
            rt_uint32_t count = 0;
            struct rt_ofw_prop *prop;

            prop = rt_ofw_get_prop(clk_ofw_np, "clock-indices", RT_NULL);

            if (prop)
            {
                rt_uint32_t max_idx = 0, idx;

                for (cell = rt_ofw_prop_next_u32(prop, RT_NULL, &idx);
                    cell;
                    cell = rt_ofw_prop_next_u32(prop, cell, &idx))
                {
                    if (idx > max_idx)
                    {
                        max_idx = idx;
                    }
                }

                count = max_idx + 1;
            }
            else
            {
                rt_ssize_t len;

                if ((prop = rt_ofw_get_prop(clk_ofw_np, "clock-output-names", &len)))
                {
                    char *value = prop->value;

                    for (int i = 0; i < len; ++i, ++value)
                    {
                        if (*value == '\0')
                        {
                            ++count;
                        }
                    }
                    if (!count)
                    {
                        count = 1;
                    }
                }
                else
                {
                    count = 1;
                }
            }

            if (clk_np)
            {
                clk_np->multi_clk = count;
            }

            return count;
        }
    }

    return -RT_EINVAL;
}

/**
 * @brief   Get parent clock name from device tree
 *
 * @param   np      Pointer to device tree node
 * @param   index   Index within "clocks" property
 *
 * @return  const char*  Name of the parent clock, or NULL if not found
 */
const char *rt_ofw_clk_get_parent_name(struct rt_ofw_node *np, int index)
{
    const char *pname = RT_NULL;
    struct rt_ofw_node *clk_ofw_np;
    struct rt_ofw_cell_args clk_args;

    if (rt_ofw_parse_phandle_cells(np, "clocks", "#clock-cells", index, &clk_args))
    {
        return RT_NULL;
    }

    clk_ofw_np = clk_args.data;

    index = clk_args.args_count ? clk_args.args[0] : 0;

    if (rt_ofw_prop_read_bool(clk_ofw_np, "clock-indices"))
    {
        const fdt32_t *val_raw;
        rt_uint32_t val, indice = 0;
        struct rt_ofw_prop *prop;

        rt_ofw_foreach_prop_u32(clk_ofw_np, "clock-indices", prop, val_raw, val)
        {
            if (index == val)
            {
                index = indice;
                goto _goon;
            }
            ++indice;
        }

        goto _end;
    }
_goon:

    if (rt_ofw_prop_read_string_index(clk_ofw_np, "clock-output-names", index, &pname))
    {
        struct rt_clk *provider_clk = rt_ofw_get_clk(np, index);

        if (rt_is_err_or_null(provider_clk))
        {
            pname = provider_clk->cell->name;

            rt_clk_put(provider_clk);
        }
    }

_end:
    rt_ofw_node_put(clk_ofw_np);

    return pname;
}

/**
 * @brief   Initialize clock from device tree (OFW) defaults.
 *
 * @details
 * This function applies the device tree–specified clock default.
 * It processes the following standard DT bindings in order:
 *
 *  - **assigned-clocks**: list of clock phandles that must be configured
 *    before the device is probed.
 *  - **assigned-clock-parents**: optional list of corresponding parent
 *    clock phandles for each entry in *assigned-clocks*.
 *  - **assigned-clock-rates**: optional list of target rates (in Hz)
 *    to set for each clock in *assigned-clocks*.
 *
 * For each assigned clock, the function will:
 *  1. Retrieve the referenced clock handle.
 *  2. Set its parent if a corresponding entry in
 *     *assigned-clock-parents* exists.
 *  3. Set its rate if a corresponding entry in
 *     *assigned-clock-rates* exists.
 *
 * This ensures that all clocks required by a device are configured
 * according to the hardware design before the device driver runs.
 *
 * @param   np          Point to ofw node
 *
 * @return
 *  - RT_EOK            : Successfully applied assigned-clocks settings.
 *  - -RT_EINVAL        : Invalid or inconsistent device tree entries.
 *  - -RT_ENOSYS        : Clock driver does not support required operation.
 *  - Other negative values : Underlying driver or hardware error.
 *
 * @note
 *  - This function should be called **after all clocks in the system
 *    have been registered**, ensuring that referenced parents exist.
 *  - Clocks not listed in *assigned-clocks* are left unchanged.
 *  - The function is typically invoked at the end of
 *    `rt_clk_node_register()`.
 */
rt_err_t rt_ofw_clk_set_defaults(struct rt_ofw_node *np)
{
    struct rt_clk *clk;
    struct rt_clk_array *clk_arr;

    if (!np)
    {
        return RT_EOK;
    }

    clk_arr = ofw_get_clk_array(np, "assigned-clocks", RT_NULL);

    if (rt_is_err(clk_arr))
    {
        return rt_ptr_err(clk_arr);
    }

    if (clk_arr)
    {
        rt_uint32_t rate;
        struct rt_clk_array *clk_parent_arr;

        clk_parent_arr = ofw_get_clk_array(np, "assigned-clock-parents", RT_NULL);

        if (rt_is_err(clk_parent_arr))
        {
            rt_clk_array_put(clk_arr);
            return rt_ptr_err(clk_parent_arr);
        }

        for (int i = 0; i < clk_arr->count; ++i)
        {
            clk = clk_arr->clks[i];

            if (clk_parent_arr && i < clk_parent_arr->count)
            {
                rt_clk_set_parent(clk, clk_parent_arr->clks[i]);
            }

            if (!rt_ofw_prop_read_u32_index(np, "assigned-clock-rates", i, &rate))
            {
                rt_clk_set_rate(clk, rate);
            }
        }

        rt_clk_array_put(clk_parent_arr);
        rt_clk_array_put(clk_arr);
    }

    return RT_EOK;
}
#endif /* RT_USING_OFW */

#if defined(RT_USING_CONSOLE) && defined(RT_USING_MSH)
static int list_clk(int argc, char**argv)
{
    struct rt_clk_node *clk_np;
    struct rt_clk_cell *cell, *parent;

    rt_kprintf("%-*.s %-*.s %-*.s %-*.s %-*.s %-*.s Parent\n",
            32, "Name",
            12, "Enable Count",
            13, "Prepare Count",
            11, "Rate",
            32, "Device ID",
            32, "Connection ID");

    clk_lock();
    rt_list_for_each_entry(clk_np, &_clk_node_nodes, parent.list)
    {
        for (int i = 0; i < clk_np->cells_nr; ++i)
        {
            rt_ubase_t rate;
            const char *dev_id = "deviceless", *con_id = "no_connection_id";

            cell = clk_np->cells[i];

            if (!cell)
            {
                continue;
            }

            rate = cell->rate ? : rt_clk_cell_get_rate(cell);

            if (cell->clk)
            {
                if (cell->clk->dev_id)
                {
                    dev_id = cell->clk->dev_id;
                }
                if (cell->clk->con_id)
                {
                    con_id = cell->clk->con_id;
                }
            }

            parent = rt_clk_cell_get_parent(cell);

            rt_kprintf("%-*.s %-12d %-13d %-11lu %-*.s %-*.s %s\n",
                    32, cell->name,
                    cell->enable_count,
                    cell->prepare_count,
                    rate,
                    32, dev_id,
                    32, con_id,
                    parent ? parent->name : RT_NULL);
        }
    }
    clk_unlock();

    return 0;
}
MSH_CMD_EXPORT(list_clk, dump all of clk information);
#endif /* RT_USING_CONSOLE && RT_USING_MSH */

/**@}*/