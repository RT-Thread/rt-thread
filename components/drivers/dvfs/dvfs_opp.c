/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "dvfs.opp"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct rt_dvfs_opp *dvfs_opp_find_freq(struct rt_dvfs_opp_table *opp_table, rt_ubase_t freq, int dir)
{
    struct rt_dvfs_opp *opp, *opp_next, *best = RT_NULL;

    if (!opp_table)
    {
        return RT_NULL;
    }

    rt_list_for_each_entry_safe(opp, opp_next, &opp_table->opp_nodes, list)
    {
        if (dir == 0)
        {
            if (opp->freq == freq)
            {
                return opp;
            }
        }
        else if (dir > 0)
        {
            if (opp->freq >= freq && (!best || opp->freq < best->freq))
            {
                best = opp;
            }
        }
        else
        {
            if (opp->freq <= freq)
            {
                best = opp;
            }
        }
    }

    return best;
}

struct rt_dvfs_opp *rt_dvfs_scaling_add_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq, rt_ubase_t uvolt)
{
    struct rt_dvfs_opp_table *opp_table;
    struct rt_dvfs_opp *opp, *opp_next;

    if (!dvfs)
    {
        return RT_NULL;
    }

    if (!dvfs->opp_table)
    {
        if (!(dvfs->opp_table = rt_calloc(1, sizeof(*dvfs->opp_table))))
        {
            return RT_NULL;
        }

        rt_list_init(&dvfs->opp_table->opp_nodes);
    }

    opp = rt_dvfs_scaling_find_opp(dvfs, freq);

    if (opp)
    {
        if (opp->uvolt == uvolt)
        {
            return opp;
        }

        LOG_W("%s: OPP { %lu Hz, %lu uV } is exists { %lu Hz, %lu uV }",
                rt_dm_dev_get_name(dvfs->dev), freq, uvolt, opp->freq, opp->uvolt);

        return RT_NULL;
    }

    opp = rt_calloc(1, sizeof(*opp));

    if (!opp)
    {
        LOG_E("%s: No memory to create OPP { %lu Hz, %lu uV }",
                rt_dm_dev_get_name(dvfs->dev), freq, uvolt);
        return RT_NULL;
    }

    opp->freq = freq;
    opp->uvolt = uvolt;
    opp->available = RT_TRUE;
    rt_list_init(&opp->list);

    rt_dvfs_scaling_enter(dvfs);

    opp_table = dvfs->opp_table;

    if (rt_list_isempty(&opp_table->opp_nodes))
    {
        dvfs->min_freq = opp->freq;
        dvfs->max_freq = opp->freq;
        rt_list_insert_after(&opp_table->opp_nodes, &opp->list);
    }
    else
    {
        rt_list_for_each_entry(opp_next, &opp_table->opp_nodes, list)
        {
            if (opp->freq < opp_next->freq)
            {
                rt_list_insert_before(&opp_next->list, &opp->list);
                break;
            }
        }

        if (rt_list_isempty(&opp->list))
        {
            rt_list_insert_before(&opp_table->opp_nodes, &opp->list);
            dvfs->max_freq = opp->freq;
        }
        else if (opp->freq < dvfs->min_freq)
        {
            dvfs->min_freq = opp->freq;
        }
        else if (opp->freq > dvfs->max_freq)
        {
            dvfs->max_freq = opp->freq;
        }
    }

    rt_dvfs_scaling_leave(dvfs);

    return opp;
}

rt_err_t rt_dvfs_scaling_remove_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq)
{
    struct rt_dvfs_opp_table *opp_table;
    struct rt_dvfs_opp *opp = rt_dvfs_scaling_find_opp(dvfs, freq);

    if (!opp)
    {
        return -RT_EINVAL;
    }

    opp_table = dvfs->opp_table;

    if (opp_table->current_opp == opp)
    {
        return -RT_EBUSY;
    }

    rt_dvfs_scaling_enter(dvfs);

    rt_list_remove(&opp->list);

    if (!rt_list_isempty(&opp_table->opp_nodes))
    {
        if (dvfs->min_freq == opp->freq)
        {
            opp = rt_list_entry(opp_table->opp_nodes.next, struct rt_dvfs_opp, list);

            dvfs->min_freq = opp->freq;
        }
        else if (dvfs->max_freq == opp->freq)
        {
            opp = rt_list_entry(opp_table->opp_nodes.prev, struct rt_dvfs_opp, list);

            dvfs->max_freq = opp->freq;
        }
    }
    else
    {
        LOG_W("%s: OPP is empty", rt_dm_dev_get_name(dvfs->dev));

        dvfs->min_freq = 0;
        dvfs->max_freq = 0;
    }

    rt_dvfs_scaling_leave(dvfs);

    rt_free(opp);

    return RT_EOK;
}

rt_err_t rt_dvfs_scaling_remove_opp_all(struct rt_dvfs_scaling *dvfs)
{
    struct rt_dvfs_opp *opp, *opp_next;
    struct rt_dvfs_opp_table *opp_table;

    if (!dvfs)
    {
        return -RT_EINVAL;
    }

    rt_dvfs_scaling_enter(dvfs);

    /* User will free, so free ignore current */
    dvfs->min_freq = 0;
    dvfs->max_freq = 0;

    opp_table = dvfs->opp_table;
    opp_table->current_opp = RT_NULL;

    rt_list_for_each_entry_safe(opp, opp_next, &opp_table->opp_nodes, list)
    {
        rt_list_remove(&opp->list);

        rt_dvfs_scaling_leave(dvfs);

        rt_free(opp);

        rt_dvfs_scaling_enter(dvfs);
    }

    rt_dvfs_scaling_leave(dvfs);

    return RT_EOK;
}

rt_err_t rt_dvfs_scaling_enable_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq)
{
    struct rt_dvfs_opp *opp = rt_dvfs_scaling_find_opp(dvfs, freq);

    if (!opp)
    {
        return -RT_EINVAL;
    }

    rt_dvfs_scaling_enter(dvfs);
    opp->available = RT_TRUE;
    rt_dvfs_scaling_leave(dvfs);

    return RT_EOK;
}

rt_err_t rt_dvfs_scaling_disable_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq)
{
    rt_err_t err;
    struct rt_dvfs_opp *opp = rt_dvfs_scaling_find_opp(dvfs, freq);

    if (!opp)
    {
        return -RT_EINVAL;
    }

    rt_dvfs_scaling_enter(dvfs);

    if (dvfs->opp_table->current_opp != opp)
    {
        opp->available = RT_FALSE;
        err = RT_EOK;
    }
    else
    {
        err = -RT_EBUSY;
    }

    rt_dvfs_scaling_leave(dvfs);

    return err;
}

struct rt_dvfs_opp *rt_dvfs_scaling_find_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq)
{
    struct rt_dvfs_opp *opp = RT_NULL;

    if (!dvfs || !dvfs->opp_table)
    {
        return RT_NULL;
    }

    rt_dvfs_scaling_enter(dvfs);

    if (freq >= dvfs->min_freq && freq <= dvfs->max_freq)
    {
        opp = dvfs_opp_find_freq(dvfs->opp_table, freq, 0);
    }

    rt_dvfs_scaling_leave(dvfs);

    return opp;
}

struct rt_dvfs_opp *rt_dvfs_scaling_find_ceil_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq)
{
    struct rt_dvfs_opp *opp = RT_NULL;

    if (!dvfs || !dvfs->opp_table)
    {
        return RT_NULL;
    }

    rt_dvfs_scaling_enter(dvfs);

    if (freq <= dvfs->max_freq)
    {
        opp = dvfs_opp_find_freq(dvfs->opp_table, freq, 1);
    }

    rt_dvfs_scaling_leave(dvfs);

    return opp;
}

struct rt_dvfs_opp *rt_dvfs_scaling_find_floor_opp(struct rt_dvfs_scaling *dvfs, rt_ubase_t freq)
{
    struct rt_dvfs_opp *opp = RT_NULL;

    if (!dvfs || !dvfs->opp_table)
    {
        return RT_NULL;
    }

    rt_dvfs_scaling_enter(dvfs);

    if (freq >= dvfs->min_freq)
    {
        opp = dvfs_opp_find_freq(dvfs->opp_table, freq, -1);
    }

    rt_dvfs_scaling_leave(dvfs);

    return opp;
}
