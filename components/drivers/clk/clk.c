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

#include <rtthread.h>
#include <rtservice.h>
#include <rtdevice.h>

/**
 * @addtogroup  Drivers          RTTHREAD Driver
 * @defgroup    clk              clk
 * @brief       clk driver api
 * @ingroup     Drivers
 * @addtogroup  clk
 * @{
 */

#define DBG_TAG "rtdm.clk"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct rt_spinlock _clk_lock = { 0 };
static rt_list_t _clk_nodes = RT_LIST_OBJECT_INIT(_clk_nodes);
static rt_list_t _clk_notifier_nodes = RT_LIST_OBJECT_INIT(_clk_notifier_nodes);

/**
 * @brief   Release clock node
 *
 * @param   r               point to reference count of clock node
 * @warning The function only can print log and MORE DETAILS SHOULD BE IMPLEMENTED.
 */
static void clk_release(struct rt_ref *r)
{
    struct rt_clk_node *clk_np = rt_container_of(r, struct rt_clk_node, ref);

    LOG_E("%s is release", clk_np->name);
    (void)clk_np;

    RT_ASSERT(0);
}

/**
 * @brief   Increase reference count for clock node
 *
 * @param   clk_np                  point to clock node
 *
 * @return  struct rt_clk_node *    point to clock node whose reference count has increased
 */
rt_inline struct rt_clk_node *clk_get(struct rt_clk_node *clk_np)
{
    rt_ref_get(&clk_np->ref);

    return clk_np;
}

/**
 * @brief   Decrease reference count for clock node
 *
 * @param   clk_np                  point to clock node
 *
 */
rt_inline void clk_put(struct rt_clk_node *clk_np)
{
    rt_ref_put(&clk_np->ref, &clk_release);
}

/**
 * @brief   Allocate memory space for struct clock and return it
 *
 * @param   clk_np          point to clock node
 * @param   dev_id          device identifier for the clock
 * @param   con_id          connection identifier for the clock
 * @param   fw_node         point to the firmware node associated with the clock
 *
 * @return  struct rt_clk*  point to clock
 */
static struct rt_clk *clk_alloc(struct rt_clk_node *clk_np, const char *dev_id,
        const char *con_id, void *fw_node)
{
    struct rt_clk *clk = rt_calloc(1, sizeof(*clk));

    if (clk)
    {
        clk->clk_np = clk_np;
        clk->dev_id = dev_id;
        clk->con_id = con_id;

        clk->fw_node = fw_node;
    }
    else
    {
        clk = rt_err_ptr(-RT_ENOMEM);
    }

    return clk;
}

/**
 * @brief   Free memory space of clock object
 *
 * @param   clk             point to clock
 *
 */
static void clk_free(struct rt_clk *clk)
{
    struct rt_clk_node *clk_np = clk->clk_np;

    if (clk_np && clk_np->ops->finit)
    {
        clk_np->ops->finit(clk);
    }

    rt_free(clk);
}

/**
 * @brief   Allocate memory space and creat clock object
 *
 * @param   clk_np          point to clock node
 * @param   dev_id          device identifier for the clock
 * @param   con_id          connection identifier for the clock
 * @param   fw_data         point to the firmware data associated with the clock
 * @param   fw_node         point to the firmware node associated with the clock
 *
 * @return  struct rt_clk*  point to clock
 */
static struct rt_clk *clk_create(struct rt_clk_node *clk_np, const char *dev_id,
        const char *con_id, void *fw_data, void *fw_node)
{
    struct rt_clk *clk = clk_alloc(clk_np, dev_id, con_id, fw_node);

    if (!rt_is_err(clk))
    {
        clk_get(clk_np);

        if (clk_np->ops->init && clk_np->ops->init(clk, fw_data))
        {
            LOG_E("Dev[%s] Con[%s] init fail", dev_id, con_id);

            clk_free(clk);
            clk = RT_NULL;
        }
    }

    return clk;
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
static rt_err_t clk_notify(struct rt_clk_node *clk_np, rt_ubase_t msg, rt_ubase_t old_rate, rt_ubase_t new_rate)
{
    rt_err_t err = RT_EOK;
    struct rt_clk_notifier *notifier;

    rt_list_for_each_entry(notifier, &_clk_notifier_nodes, list)
    {
        if (notifier->clk->clk_np == clk_np)
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

/**
 * @brief   Set parent clock
 *
 * @param   clk_np          point to clock node
 * @param   parent_np       point to parent rt_clk
 *
 */
static void clk_set_parent(struct rt_clk_node *clk_np, struct rt_clk_node *parent_np)
{
    rt_hw_spin_lock(&_clk_lock.lock);

    clk_np->parent = parent_np;

    rt_list_insert_after(&parent_np->children_nodes, &clk_np->list);

    rt_hw_spin_unlock(&_clk_lock.lock);
}

static const struct rt_clk_ops unused_clk_ops =
{
};

/**
 * @brief   Register clock node into clock list
 *
 * @param   clk_np          point to child node that will be registered node.
 * @param   parent_np       point to parent rt_clk. If it is RT_NULL, clock node will be linked to init node.
 *
 * @retval  RT_EOK
 * @retval  -RT_ENOMEM
 */
rt_err_t rt_clk_register(struct rt_clk_node *clk_np, struct rt_clk_node *parent_np)
{
    rt_err_t err = RT_EOK;
    struct rt_clk *clk = RT_NULL;

    if (clk_np)
    {
        clk_np->clk = clk;

        if (!clk_np->ops)
        {
            clk_np->ops = &unused_clk_ops;
        }

    #if RT_NAME_MAX > 0
        rt_strncpy(clk_np->rt_parent.name, RT_CLK_NODE_OBJ_NAME, RT_NAME_MAX);
    #else
        clk_np->rt_parent.name = RT_CLK_NODE_OBJ_NAME;
    #endif

        rt_ref_init(&clk_np->ref);
        rt_list_init(&clk_np->list);
        rt_list_init(&clk_np->children_nodes);
        clk_np->multi_clk = 0;

        if (parent_np)
        {
            clk_np->clk = clk_alloc(clk_np, RT_NULL, RT_NULL, RT_NULL);

            if (clk_np->clk)
            {
                clk_set_parent(clk_np, parent_np);
            }
            else
            {
                err = -RT_ENOMEM;
            }
        }
        else
        {
            clk_np->parent = RT_NULL;

            rt_hw_spin_lock(&_clk_lock.lock);

            rt_list_insert_after(&_clk_nodes, &clk_np->list);

            rt_hw_spin_unlock(&_clk_lock.lock);
        }
    }
    else
    {
        err = -RT_ENOMEM;
    }

    return err;
}

/**
 * @brief   Unregister clock node from clock list
 *
 * @param   clk_np          point to child node that will be Unregistered node.
 *
 * @retval  RT_EOK
 * @retval  -RT_EBUSY
 * @retval  -RT_EINVAL
 */
rt_err_t rt_clk_unregister(struct rt_clk_node *clk_np)
{
    rt_err_t err = RT_EOK;

    if (clk_np)
    {
        err = -RT_EBUSY;

        rt_hw_spin_lock(&_clk_lock.lock);

        if (rt_list_isempty(&clk_np->children_nodes))
        {
            if (rt_ref_read(&clk_np->ref) <= 1)
            {
                rt_list_remove(&clk_np->list);
                clk_free(clk_np->clk);

                err = RT_EOK;
            }
        }

        rt_hw_spin_unlock(&_clk_lock.lock);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
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
    if (!clk || !clk->clk_np || !notifier)
    {
        return -RT_EINVAL;
    }

    rt_hw_spin_lock(&_clk_lock.lock);

    ++clk->clk_np->notifier_count;
    rt_list_init(&notifier->list);
    rt_list_insert_after(&_clk_notifier_nodes, &notifier->list);

    rt_hw_spin_unlock(&_clk_lock.lock);

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

    rt_hw_spin_lock(&_clk_lock.lock);

    rt_list_for_each_entry(notifier_find, &_clk_notifier_nodes, list)
    {
        if (notifier_find->clk->clk_np == notifier->clk->clk_np)
        {
            --clk->clk_np->notifier_count;
            rt_list_remove(&notifier->list);

            break;
        }
    }

    rt_hw_spin_unlock(&_clk_lock.lock);

    return RT_EOK;
}

/**
 * @brief   Recursively prepare clock
 *
 * @param   clk             Ponit to clock that will be prepared
 * @param   clk_np          Ponit to clock node that will be prepared
 *
 * @return  rt_err_t        RT_EOK on prepare clock sucessfully, and other value is failed.
 */
static rt_err_t clk_prepare(struct rt_clk *clk, struct rt_clk_node *clk_np)
{
    rt_err_t err = RT_EOK;

    if (clk_np->parent)
    {
        clk_prepare(clk_np->clk, clk_np->parent);
    }

    if (clk->prepare_count == 0 && clk_np->ops->prepare)
    {
        err = clk_np->ops->prepare(clk);
    }

    if (!err)
    {
        ++clk->prepare_count;
    }

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
    rt_err_t err = RT_EOK;

    RT_DEBUG_NOT_IN_INTERRUPT;

    if (clk && clk->clk_np)
    {
        rt_hw_spin_lock(&_clk_lock.lock);

        err = clk_prepare(clk, clk->clk_np);

        rt_hw_spin_unlock(&_clk_lock.lock);
    }

    return err;
}

/**
 * @brief   Recursively unprepare clock
 *
 * @param   clk             Ponit to clock that will be unprepared
 * @param   clk_np          Ponit to clock node that will be unprepared
 *
 */
static void clk_unprepare(struct rt_clk *clk, struct rt_clk_node *clk_np)
{
    if (clk_np->parent)
    {
        clk_unprepare(clk_np->clk, clk_np->parent);
    }

    if (clk->prepare_count == 1 && clk_np->ops->unprepare)
    {
        clk_np->ops->unprepare(clk);
    }
    if (clk->prepare_count)
    {
        --clk->prepare_count;
    }
}

rt_err_t rt_clk_unprepare(struct rt_clk *clk)
{
    rt_err_t err = RT_EOK;

    RT_DEBUG_NOT_IN_INTERRUPT;

    if (clk && clk->clk_np)
    {
        rt_hw_spin_lock(&_clk_lock.lock);

        clk_unprepare(clk, clk->clk_np);

        rt_hw_spin_unlock(&_clk_lock.lock);
    }

    return err;
}

/**
 * @brief   Enable clock
 *
 * @param   clk             point to clock
 *
 * @return  rt_err_t        RT_EOK on enable clock FOREVER.
 */
static rt_err_t clk_enable(struct rt_clk *clk, struct rt_clk_node *clk_np)
{
    rt_err_t err = RT_EOK;

    if (clk_np->parent)
    {
        clk_enable(clk_np->clk, clk_np->parent);
    }

    if (clk->enable_count == 0 && clk_np->ops->enable)
    {
        err = clk_np->ops->enable(clk);
    }

    if (!err)
    {
        ++clk->enable_count;
    }

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
    rt_err_t err = RT_EOK;

    if (clk && clk->clk_np)
    {
        rt_hw_spin_lock(&_clk_lock.lock);

        err = clk_enable(clk, clk->clk_np);

        rt_hw_spin_unlock(&_clk_lock.lock);
    }

    return err;
}

/**
 * @brief   Recursively disable clock
 *
 * @param   clk             Ponit to clock that will be disabled
 * @param   clk_np          Ponit to clock node that will be disabled
 *
 */
static void clk_disable(struct rt_clk *clk, struct rt_clk_node *clk_np)
{
    if (clk_np->parent)
    {
        clk_disable(clk_np->clk, clk_np->parent);
    }

    if (clk->enable_count == 1 && clk_np->ops->disable)
    {
        clk_np->ops->disable(clk);
    }
    if (clk->enable_count)
    {
        --clk->enable_count;
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
    if (clk && clk->clk_np)
    {
        rt_hw_spin_lock(&_clk_lock.lock);

        clk_disable(clk, clk->clk_np);

        rt_hw_spin_unlock(&_clk_lock.lock);
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
    rt_err_t err = RT_EOK;

    RT_DEBUG_NOT_IN_INTERRUPT;

    if (clk)
    {
        err = rt_clk_prepare(clk);

        if (!err)
        {
            err = rt_clk_enable(clk);

            if (err)
            {
                rt_clk_unprepare(clk);
            }
        }
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
        rt_clk_disable(clk);
        rt_clk_unprepare(clk);
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
    rt_err_t err = RT_EOK;

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

    return err;
}

rt_err_t rt_clk_array_unprepare(struct rt_clk_array *clk_arr)
{
    rt_err_t err = RT_EOK;

    if (clk_arr)
    {
        for (int i = 0; i < clk_arr->count; ++i)
        {
            if ((err = rt_clk_unprepare(clk_arr->clks[i])))
            {
                LOG_E("CLK Array[%d] %s failed error = %s", i,
                        "unprepare", rt_strerror(err));

                break;
            }
        }
    }

    return err;
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
    rt_err_t err = RT_EOK;

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
    rt_err_t err = RT_EOK;

    if (clk && clk->clk_np)
    {
        struct rt_clk_node *clk_np = clk->clk_np;

        rt_hw_spin_lock(&_clk_lock.lock);

        if (clk_np->ops->set_rate)
        {
            rt_ubase_t rate = clk_np->rate;
            rt_ubase_t old_min = clk_np->min_rate;
            rt_ubase_t old_max = clk_np->max_rate;

            clk_np->min_rate = min;
            clk_np->max_rate = max;

            rate = rt_clamp(rate, min, max);
            err = clk_np->ops->set_rate(clk, rate,
                rt_clk_get_rate(clk_np->parent ? clk_np->parent->clk : RT_NULL));

            if (err)
            {
                clk_np->min_rate = old_min;
                clk_np->max_rate = old_max;
            }
        }
        else
        {
            err = -RT_ENOSYS;
        }

        rt_hw_spin_unlock(&_clk_lock.lock);
    }

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
    rt_err_t err = RT_EOK;

    if (clk && clk->clk_np)
    {
        struct rt_clk_node *clk_np = clk->clk_np;

        err = rt_clk_set_rate_range(clk, rate, clk_np->max_rate);
    }

    return err;
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
    rt_err_t err = RT_EOK;

    if (clk && clk->clk_np)
    {
        struct rt_clk_node *clk_np = clk->clk_np;

        err = rt_clk_set_rate_range(clk, clk_np->min_rate, rate);
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
    rt_err_t err = RT_EOK;

    rate = rt_clk_round_rate(clk, rate);

    if (clk && clk->clk_np && rate > 0)
    {
        struct rt_clk_node *clk_np = clk->clk_np;

        rt_hw_spin_lock(&_clk_lock.lock);

        if (clk_np->min_rate && rate < clk_np->min_rate)
        {
            err = -RT_EINVAL;
        }

        if (clk_np->max_rate && rate > clk_np->max_rate)
        {
            err = -RT_EINVAL;
        }

        if (!err)
        {
            if (clk_np->ops->set_rate)
            {
                rt_ubase_t old_rate = clk_np->rate;

                err = clk_np->ops->set_rate(clk, rate,
                    rt_clk_get_rate(clk_np->parent ? clk_np->parent->clk : RT_NULL));

                if (clk_np->rate != old_rate)
                {
                    clk_notify(clk_np, RT_CLK_MSG_PRE_RATE_CHANGE, old_rate, clk_np->rate);
                }
            }
            else
            {
                err = -RT_ENOSYS;
            }
        }

        rt_hw_spin_unlock(&_clk_lock.lock);
    }

    return err;
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
    rt_ubase_t rate = 0;

    if (clk)
    {
        if (clk->rate)
        {
            rate = clk->rate;
        }
        else if (clk->clk_np)
        {
            rate = clk->clk_np->rate;
        }
    }

    return rate;
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
    rt_err_t err = RT_EOK;

    if (clk && clk->clk_np && clk->clk_np->ops->set_phase)
    {
        rt_hw_spin_lock(&_clk_lock.lock);

        err = clk->clk_np->ops->set_phase(clk, degrees);

        rt_hw_spin_unlock(&_clk_lock.lock);
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
    rt_base_t res = RT_EOK;

    if (clk && clk->clk_np && clk->clk_np->ops->get_phase)
    {
        rt_hw_spin_lock(&_clk_lock.lock);

        res = clk->clk_np->ops->get_phase(clk);

        rt_hw_spin_unlock(&_clk_lock.lock);
    }

    return res;
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
    rt_base_t res = -RT_EINVAL;

    if (clk && clk->clk_np)
    {
        struct rt_clk_node *clk_np = clk->clk_np;

        if (clk_np->ops->round_rate)
        {
            rt_ubase_t best_parent_rate;

            rt_hw_spin_lock(&_clk_lock.lock);

            if (clk_np->min_rate && clk_np->max_rate)
            {
                rate = rt_clamp(rate, clk_np->min_rate, clk_np->max_rate);
            }

            res = clk_np->ops->round_rate(clk, rate, &best_parent_rate);
            (void)best_parent_rate;

            rt_hw_spin_unlock(&_clk_lock.lock);
        }
        else
        {
            if (rate < clk_np->min_rate)
            {
                res = clk_np->min_rate;
            }
            else if (rate > clk_np->max_rate)
            {
                res = clk_np->max_rate;
            }
            else
            {
                res = rate;
            }
        }
    }

    return res;
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
    rt_err_t err = RT_EOK;

    if (clk && clk->clk_np && clk->clk_np->ops->set_parent)
    {
        rt_hw_spin_lock(&_clk_lock.lock);

        err = clk->clk_np->ops->set_parent(clk, clk_parent);

        rt_hw_spin_unlock(&_clk_lock.lock);
    }

    return err;
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
    struct rt_clk *parent = RT_NULL;

    if (clk)
    {
        struct rt_clk_node *clk_np = clk->clk_np;

        rt_hw_spin_lock(&_clk_lock.lock);

        parent = clk_np->parent ? clk_np->parent->clk : RT_NULL;

        rt_hw_spin_unlock(&_clk_lock.lock);
    }

    return parent;
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
            if (clk_arr->clks[i])
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
    if (clk)
    {
        clk_put(clk->clk_np);
        clk_free(clk);
    }
}

#ifdef RT_USING_OFW
/**
 * @brief   Get a clock object from a device tree node without acquiring a lock
 *
 * @param   np              point to ofw node
 * @param   index           index of clock in ofw
 * @param   name            connection identifier for the clock
 * @param   locked          lock flag for indicating whether the caller holds the lock
 *
 * @return  struct rt_clk*  point to the newly created clock object, or an error pointer
 */
static struct rt_clk *ofw_get_clk_no_lock(struct rt_ofw_node *np, int index, const char *name, rt_bool_t locked)
{
    struct rt_clk *clk = RT_NULL;
    struct rt_ofw_cell_args clk_args;

    if (!rt_ofw_parse_phandle_cells(np, "clocks", "#clock-cells", index, &clk_args))
    {
        int count;
        struct rt_object *obj;
        struct rt_clk_node *clk_np = RT_NULL;
        struct rt_ofw_node *clk_ofw_np = clk_args.data;

        if (!rt_ofw_data(clk_ofw_np))
        {
            if (locked)
            {
                rt_hw_spin_unlock(&_clk_lock.lock);
            }

            rt_platform_ofw_request(clk_ofw_np);

            if (locked)
            {
                rt_hw_spin_lock(&_clk_lock.lock);
            }
        }

        if (rt_ofw_data(clk_ofw_np) && (obj = rt_ofw_parse_object(clk_ofw_np,
                    RT_CLK_NODE_OBJ_NAME, "#clock-cells")))
        {
            clk_np = rt_container_of(obj, struct rt_clk_node, rt_parent);

            count = rt_ofw_count_of_clk(clk_ofw_np);
        }

        rt_ofw_node_put(clk_ofw_np);

        if (clk_np)
        {
            if (count > 1)
            {
                /* args[0] must be the index of CLK */
                clk_np = &clk_np[clk_args.args[0]];
            }

            clk = clk_create(clk_np, np->full_name, name, &clk_args, np);
        }
        else
        {
            clk = rt_err_ptr(-RT_ERROR);
        }
    }

    return clk;
}

/**
 * @brief   Get clock from ofw with acquiring a spin lock
 *
 * @param   np              point to ofw node
 * @param   index           index of clock in ofw
 * @param   name            connection identifier for the clock
 *
 * @return  struct rt_clk*  point to the newly created clock object, or an error pointer
 */
static struct rt_clk *ofw_get_clk(struct rt_ofw_node *np, int index, const char *name)
{
    struct rt_clk *clk;

    rt_hw_spin_lock(&_clk_lock.lock);

    clk = ofw_get_clk_no_lock(np, index, name, RT_TRUE);

    rt_hw_spin_unlock(&_clk_lock.lock);

    return clk;
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
    int count;
    struct rt_clk_array *clk_arr = RT_NULL;

    if (!np)
    {
        return rt_err_ptr(-RT_EINVAL);
    }

    if ((count = rt_ofw_count_phandle_cells(np, "clocks", "#clock-cells")) > 0)
    {
        clk_arr = rt_calloc(1, sizeof(*clk_arr) + sizeof(clk_arr->clks[0]) * count);

        if (clk_arr)
        {
            int i;
            rt_err_t err = RT_EOK;
            rt_bool_t has_name = rt_ofw_prop_read_bool(np, "clock-names");

            clk_arr->count = count;

            rt_hw_spin_lock(&_clk_lock.lock);

            for (i = 0; i < count; ++i)
            {
                const char *name = RT_NULL;

                if (has_name)
                {
                    rt_ofw_prop_read_string_index(np, "clock-names", i, &name);
                }

                clk_arr->clks[i] = ofw_get_clk_no_lock(np, i, name, RT_FALSE);

                if (rt_is_err(clk_arr->clks[i]))
                {
                    err = rt_ptr_err(clk_arr->clks[i]);

                    --i;
                    break;
                }
            }

            rt_hw_spin_unlock(&_clk_lock.lock);

            if (i > 0 && i < count)
            {
                rt_clk_array_put(clk_arr);
                clk_arr = rt_err_ptr(err);
            }
        }
    }

    return clk_arr;
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
        clk = ofw_get_clk(np, index, RT_NULL);
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
            clk = ofw_get_clk(np, index, name);
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

#endif /* RT_USING_OFW */

/**@}*/