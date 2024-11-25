/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtservice.h>

#define DBG_TAG "rtdm.reset"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/ofw.h>
#include "reset.h"

struct reset_control_array
{
    struct rt_reset_control captain;

    rt_size_t count;
    struct rt_reset_control *rstcs[];
};

#define reset_control_to_array(rstc) rt_container_of(rstc, struct reset_control_array, captain)

static struct rt_spinlock _rstcer_lock = { 0 };
static rt_list_t _rstcer_nodes = RT_LIST_OBJECT_INIT(_rstcer_nodes);

rt_err_t rt_reset_controller_register(struct rt_reset_controller *rstcer)
{
    rt_ubase_t level;

    if (!rstcer)
    {
        return -RT_EINVAL;
    }

    rt_list_init(&rstcer->list);
    rt_list_init(&rstcer->rstc_nodes);
    rt_spin_lock_init(&rstcer->spinlock);

    level = rt_spin_lock_irqsave(&_rstcer_lock);

    rt_list_insert_after(&_rstcer_nodes, &rstcer->list);

    rt_spin_unlock_irqrestore(&_rstcer_lock, level);

    if (rstcer->ofw_node)
    {
        if (!rt_ofw_data(rstcer->ofw_node))
        {
            rt_ofw_data(rstcer->ofw_node) = rstcer;
        }
    }

    return RT_EOK;
}

rt_err_t rt_reset_controller_unregister(struct rt_reset_controller *rstcer)
{
    if (rstcer)
    {
        rt_spin_lock(&_rstcer_lock);

        rt_list_remove(&rstcer->list);

        rt_spin_unlock(&_rstcer_lock);

        return RT_EOK;
    }

    return -RT_EINVAL;
}

rt_err_t rt_reset_control_reset(struct rt_reset_control *rstc)
{
    rt_err_t err;

    if (!rstc)
    {
        return -RT_EINVAL;
    }

    if (rstc->rstcer->ops->reset)
    {
        if ((err = rstc->rstcer->ops->reset(rstc)))
        {
            return err;
        }
    }

    if (rstc->is_array)
    {
        struct reset_control_array *rstc_arr = reset_control_to_array(rstc);

        for (int i = 0; i < rstc_arr->count; ++i)
        {
            if ((err = rt_reset_control_reset(rstc_arr->rstcs[i])))
            {
                return err;
            }
        }
    }

    return RT_EOK;
}

rt_err_t rt_reset_control_assert(struct rt_reset_control *rstc)
{
    rt_err_t err;

    if (!rstc)
    {
        return -RT_EINVAL;
    }

    if (rstc->deassert && rstc->rstcer->ops->assert)
    {
        if ((err = rstc->rstcer->ops->assert(rstc)))
        {
            return err;
        }

        rstc->deassert = RT_FALSE;
    }

    if (rstc->is_array)
    {
        struct reset_control_array *rstc_arr = reset_control_to_array(rstc);

        for (int i = 0; i < rstc_arr->count; ++i)
        {
            if ((err = rt_reset_control_assert(rstc_arr->rstcs[i])))
            {
                if (rstc->rstcer->ops->deassert)
                {
                    rstc->rstcer->ops->deassert(rstc);

                    rstc->deassert = RT_TRUE;
                }

                while (i --> 0)
                {
                    rt_reset_control_deassert(rstc_arr->rstcs[i]);
                }

                return err;
            }
        }
    }

    return RT_EOK;
}

rt_err_t rt_reset_control_deassert(struct rt_reset_control *rstc)
{
    rt_err_t err;

    if (!rstc)
    {
        return -RT_EINVAL;
    }

    if (!rstc->deassert && rstc->rstcer->ops->deassert)
    {
        if ((err = rstc->rstcer->ops->deassert(rstc)))
        {
            return err;
        }

        rstc->deassert = RT_TRUE;
    }

    if (rstc->is_array)
    {
        struct reset_control_array *rstc_arr = reset_control_to_array(rstc);

        for (int i = 0; i < rstc_arr->count; ++i)
        {
            if ((err = rt_reset_control_deassert(rstc_arr->rstcs[i])))
            {
                if (rstc->rstcer->ops->assert)
                {
                    rstc->rstcer->ops->assert(rstc);

                    rstc->deassert = RT_FALSE;
                }

                while (i --> 0)
                {
                    rt_reset_control_assert(rstc_arr->rstcs[i]);
                }

                return err;
            }
        }
    }

    return RT_EOK;
}

int rt_reset_control_status(struct rt_reset_control *rstc)
{
    if (!rstc)
    {
        return -RT_EINVAL;
    }

    if (rstc->rstcer->ops->status)
    {
        return rstc->rstcer->ops->status(rstc);
    }

    return -RT_ENOSYS;
}

static void reset_free(struct rt_reset_control *rstc)
{
    if (rstc->is_array)
    {
        struct reset_control_array *rstc_arr = reset_control_to_array(rstc);

        for (int i = 0; i < rstc_arr->count; ++i)
        {
            rt_reset_control_put(rstc_arr->rstcs[i]);
        }
    }

    rt_free(rstc);
}

struct rt_reset_control *rt_reset_control_get_array(struct rt_device *dev)
{
    return rt_ofw_get_reset_control_array(dev->ofw_node);
}

struct rt_reset_control *rt_reset_control_get_by_index(struct rt_device *dev, int index)
{
    return rt_ofw_get_reset_control_by_index(dev->ofw_node, index);
}

struct rt_reset_control *rt_reset_control_get_by_name(struct rt_device *dev, const char *name)
{
    return rt_ofw_get_reset_control_by_name(dev->ofw_node, name);
}

void rt_reset_control_put(struct rt_reset_control *rstc)
{
    struct rt_reset_controller *rstcer;

    if (!rstc)
    {
        return;
    }

    rstcer = rstc->rstcer;

    rt_spin_lock(&rstcer->spinlock);

    rt_list_remove(&rstc->list);

    rt_spin_unlock(&rstcer->spinlock);

    reset_free(rstc);
}

static struct rt_reset_control *ofw_get_reset_control(struct rt_ofw_node *np, int index,
        const char *name, rt_bool_t is_array)
{
    struct rt_reset_control *rstc;
    struct rt_ofw_cell_args reset_args = {};
    struct rt_reset_controller *rstcer = RT_NULL;

    if (is_array)
    {
        rt_size_t rstc_nr;
        struct reset_control_array *rstc_arr;

        rstc_nr = rt_ofw_count_phandle_cells(np, "resets", "#reset-cells");

        if (!rstc_nr)
        {
            return RT_NULL;
        }

        rstc_arr = rt_calloc(1, sizeof(*rstc_arr) + sizeof(struct rt_reset_control *) * rstc_nr);

        if (!rstc_arr)
        {
            LOG_E("No memory to create %s[%d] reset control",
                    rt_ofw_node_full_name(np), index);

            return RT_NULL;
        }

        rstc_arr->count = rstc_nr - 1;

        for (int i = 0; i < rstc_arr->count; ++i)
        {
            rstc_arr->rstcs[i] = ofw_get_reset_control(np, i + 1, RT_NULL, RT_FALSE);

            if (!rstc_arr->rstcs[i])
            {
                while (i --> 0)
                {
                    rt_reset_control_put(rstc_arr->rstcs[i]);
                }

                rt_free(rstc_arr);
                rstc_arr = RT_NULL;

                return RT_NULL;
            }
        }

        rstc = &rstc_arr->captain;
        rstc->is_array = RT_TRUE;
    }
    else
    {
        rstc = rt_calloc(1, sizeof(*rstc));

        if (!rstc)
        {
            LOG_E("No memory to create %s[%d] reset control",
                    rt_ofw_node_full_name(np), index);

            return RT_NULL;
        }
    }

    if (!rt_ofw_parse_phandle_cells(np, "resets", "#reset-cells", index, &reset_args))
    {
        void *rt_data = rt_ofw_data(reset_args.data);

        if (rt_data)
        {
            /* check is clk */
            if (rt_ofw_prop_read_bool(reset_args.data, "#clock-cells"))
            {
                struct rt_reset_controller_clk_node *rstcer_clk = rt_data;

                rstcer = &rstcer_clk->rstcer;
            }
            else
            {
                rstcer = rt_data;
            }
        }

        rt_ofw_node_put(reset_args.data);
    }

    if (!rstcer)
    {
        goto _fail;
    }

    if (!name && rt_ofw_prop_read_bool(np, "reset-names"))
    {
        rt_ofw_prop_read_string_index(np, "reset-names", index, &name);
    }

    rstc->con_id = name;
    rstc->rstcer = rstcer;

    if (rstcer->ops->ofw_parse)
    {
        rt_err_t err = rstcer->ops->ofw_parse(rstc, &reset_args);

        if (err)
        {
            LOG_E("Parse %s reset control error = %s",
                    rt_ofw_node_full_name(np), rt_strerror(err));

            goto _fail;
        }
    }

    rstc->id = reset_args.args[0];

    rt_list_init(&rstc->list);

    rt_spin_lock(&rstcer->spinlock);

    rt_list_insert_after(&rstcer->rstc_nodes, &rstc->list);

    rt_spin_unlock(&rstcer->spinlock);

    return rstc;

_fail:
    if (rstc && !rstc->is_array)
    {
        rt_free(rstc);
    }

    return RT_NULL;
}

struct rt_reset_control *rt_ofw_get_reset_control_array(struct rt_ofw_node *np)
{
    return ofw_get_reset_control(np, 0, RT_NULL, RT_TRUE);
}

struct rt_reset_control *rt_ofw_get_reset_control_by_index(struct rt_ofw_node *np, int index)
{
    return ofw_get_reset_control(np, index, RT_NULL, RT_FALSE);
}

struct rt_reset_control *rt_ofw_get_reset_control_by_name(struct rt_ofw_node *np, const char *name)
{
    if (np)
    {
        int index = rt_ofw_prop_index_of_string(np, "reset-names", name);

        if (index >= 0)
        {
            return ofw_get_reset_control(np, index, name, RT_FALSE);
        }
    }

    return RT_NULL;
}
