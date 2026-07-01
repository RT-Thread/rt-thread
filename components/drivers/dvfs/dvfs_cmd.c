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

#define DBG_TAG "dvfs.cmd"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <stdlib.h>
#include <string.h>
#include <finsh.h>
#include <drivers/dvfs.h>

#define GOVERNOR_NAME_MAX   sizeof(((struct rt_dvfs_governor *)RT_NULL)->name)

static int list_dvfs(int argc, char**argv)
{
    rt_ubase_t level;
    struct rt_object *obj;
    struct rt_device *dev;
    struct rt_dvfs_scaling *dvfs;
    struct rt_object_information *info = rt_object_get_information(RT_Object_Class_Device);

    level = rt_hw_interrupt_disable();

    rt_kprintf("%-*.s %-*.s %-*.s Frequency (Hz)\n",
            RT_NAME_MAX, "Name",
            RT_NAME_MAX, "Device",
            GOVERNOR_NAME_MAX, "Governor");

    rt_list_for_each_entry(obj, &info->object_list, list)
    {
        dev = rt_container_of(obj, struct rt_device, parent);

        if (!(dvfs = dev->dvfs_scaling))
        {
            continue;
        }

        rt_kprintf("%-*.s %-*.s %-*.s %lu\n",
                RT_NAME_MAX, rt_dm_dev_get_name(dev),
                RT_NAME_MAX, rt_dm_dev_get_name(dvfs->dev),
                GOVERNOR_NAME_MAX, dvfs->gov ? dvfs->gov->name : "N/A",
                dvfs->cur_freq);
    }

    rt_hw_interrupt_enable(level);

    return 0;
}
MSH_CMD_EXPORT(list_dvfs, dump all of dvfs information);

enum
{
    DVFS_OPT_DUMP = 1,
    DVFS_OPT_SET_GOVERNOR,
    DVFS_OPT_SET_FREQUENCY,
};

CMD_OPTIONS_STATEMENT(dvfs)

static struct rt_dvfs_scaling *dvfs_scaling(const char *name)
{
    struct rt_device *dev = rt_device_find(name);

    if (!dev)
    {
        LOG_E("Device %s not found", name);
        return RT_NULL;
    }

    if (!dev->dvfs_scaling)
    {
        LOG_E("Device %s not supported dvfs", name);
        return RT_NULL;
    }

    return dev->dvfs_scaling;
}

static int dvfs(int argc, char**argv)
{
    struct rt_dvfs_scaling *dvfs;

    if (argc < 2)
    {
        goto _usage;
    }

    if (MSH_OPT_ID_GET(dvfs) == DVFS_OPT_DUMP)
    {
        rt_uint32_t opp_id = 0;
        struct rt_dvfs_opp *opp;

        if (argc != 3 || !(dvfs = dvfs_scaling(argv[2])))
        {
            goto _usage;
        }

        rt_dvfs_scaling_enter(dvfs);

        rt_kprintf("name:               %s\n", argv[2]);
        rt_kprintf("device:             %s\n", rt_dm_dev_get_name(dvfs->dev));
        rt_kprintf("governor:           %s\n", dvfs->gov ? dvfs->gov->name : "N/A");
        rt_kprintf("min frequency:      %lu Hz\n", dvfs->min_freq);
        rt_kprintf("max frequency:      %lu Hz\n", dvfs->max_freq);
        rt_kprintf("current frequency:  %lu Hz", dvfs->cur_freq);
        if (dvfs->opp_table && dvfs->opp_table->current_opp)
        {
            rt_kprintf(" @ %lu uV", dvfs->opp_table->current_opp->uvolt);
        }
        rt_kprintf("\n");
        rt_kprintf("suspend frequency:  %lu Hz\n", dvfs->suspend_freq);

#ifdef RT_USING_DVFS_EVENT
        if (dvfs->load_update)
        {
            struct rt_dvfs_devfreq *devfreq;
            struct rt_dvfs_event_data evd = {0};

            dvfs->load_update(dvfs);
            rt_kprintf("event load:         %u%%\n", dvfs->cpu_load.load_percentage);

            devfreq = rt_container_of(dvfs, struct rt_dvfs_devfreq, parent);
            if (devfreq->ev && rt_dvfs_event_read(devfreq->ev, &evd) == RT_EOK && evd.total_count)
            {
                rt_uint64_t load_p = evd.load_count * 100000000ULL / evd.total_count;
                rt_uint32_t load_int = (rt_uint32_t)(load_p / 1000000ULL);
                rt_uint32_t load_frac = (rt_uint32_t)(load_p % 1000000ULL);

                rt_kprintf("event counters:     %lu / %lu (%u.%06u%%)\n",
                        (unsigned long)evd.load_count,
                        (unsigned long)evd.total_count,
                        load_int, load_frac);
            }
        }
#endif

        if (dvfs->opp_table)
        {
            struct rt_dvfs_opp *current = dvfs->opp_table->current_opp;
            const char *state;

            rt_kprintf("opp table:\n");

            rt_list_for_each_entry(opp, &dvfs->opp_table->opp_nodes, list)
            {
                if (!opp->available)
                {
                    state = "disabled";
                }
                else if (opp == current)
                {
                    state = "active";
                }
                else if (opp->freq == dvfs->suspend_freq)
                {
                    state = "suspend";
                }
                else
                {
                    state = RT_NULL;
                }

                rt_kprintf("  opp[%02u]: %10lu Hz  %7lu uV  %5lu mW",
                        opp_id, opp->freq, opp->uvolt, opp->power);

                if (state)
                {
                    rt_kprintf("  (%s)", state);
                }

                rt_kprintf("\n");

                ++opp_id;
            }
        }

        rt_dvfs_scaling_leave(dvfs);

        return 0;
    }
    else if (MSH_OPT_ID_GET(dvfs) == DVFS_OPT_SET_GOVERNOR)
    {
        rt_err_t err;
        struct rt_dvfs_governor *gov;

        if (argc != 4 || !(dvfs = dvfs_scaling(argv[2])))
        {
            goto _usage;
        }

        if (!(gov = rt_dvfs_governor_get_by_name(argv[3])))
        {
            LOG_E("Governor %s is not supported", argv[3]);
            goto _usage;
        }

        err = rt_dvfs_scaling_set_governor(dvfs, gov->type);
        rt_dvfs_governor_put(gov);

        return err;
    }
    else if (MSH_OPT_ID_GET(dvfs) == DVFS_OPT_SET_FREQUENCY)
    {
        rt_err_t err;
        rt_ubase_t freq;

        if (argc != 4 || !(dvfs = dvfs_scaling(argv[2])))
        {
            goto _usage;
        }

        freq = atol(argv[3]);

        if (freq < dvfs->min_freq || freq > dvfs->max_freq)
        {
            LOG_E("Frequency %lu is not supported", freq);
            goto _usage;
        }

        if (dvfs->gov && dvfs->gov->type != RT_DVFS_GOVERNOR_TYPE_FREEDOM)
        {
            err = rt_dvfs_scaling_set_governor(dvfs, RT_DVFS_GOVERNOR_TYPE_FREEDOM);
            if (err)
            {
                LOG_E("switch governor failed: %s", rt_strerror(err));
                return err;
            }
        }

        err = rt_dvfs_scaling_set_frequency(dvfs, freq);
        if (err)
        {
            LOG_E("%s: set frequency %lu failed: %s",
                  rt_dm_dev_get_name(dvfs->dev), freq, rt_strerror(err));
        }
        else
        {
            rt_kprintf("%s: frequency set to %lu Hz\n",
                    rt_dm_dev_get_name(dvfs->dev), dvfs->cur_freq);
        }

        return err;
    }

_usage:
    rt_kprintf("Usage:\n");
    rt_kprintf("dvfs dump <name>                        - dump dvfs information\n");
    rt_kprintf("dvfs set_governor <name> <governor>     - set dvfs governor\n");
    rt_kprintf("dvfs set_frequency <name> <frequenc>    - set dvfs frequency\n");

    return (int)-RT_EINVAL;
}
CMD_OPTIONS_NODE_START(dvfs)
CMD_OPTIONS_NODE(DVFS_OPT_DUMP, dump, dump dvfs information)
CMD_OPTIONS_NODE(DVFS_OPT_SET_GOVERNOR, set_governor, set dvfs governor)
CMD_OPTIONS_NODE(DVFS_OPT_SET_FREQUENCY, set_frequency, set dvfs frequency)
CMD_OPTIONS_NODE_END
MSH_CMD_EXPORT_ALIAS(dvfs, dvfs, dvfs operation, optenable);
