/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <drivers/platform.h>

#define DBG_TAG "rtdm.thermal"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "thermal_dm.h"

#ifndef INT_MAX
#define INT_MAX (RT_UINT32_MAX >> 1)
#endif

#define device_list(dev)            (dev)->parent.parent.list
#define device_foreach(dev, nodes)  rt_list_for_each_entry(dev, nodes, parent.parent.list)

static struct rt_spinlock nodes_lock = {};
static rt_list_t thermal_zone_device_nodes = RT_LIST_OBJECT_INIT(thermal_zone_device_nodes);
static rt_list_t thermal_cooling_device_nodes = RT_LIST_OBJECT_INIT(thermal_cooling_device_nodes);
static rt_list_t thermal_cooling_governor_nodes = RT_LIST_OBJECT_INIT(thermal_cooling_governor_nodes);

#ifdef RT_USING_OFW
static void thermal_ofw_params_parse(struct rt_ofw_node *np,
        struct rt_thermal_zone_params *tz_params)
{
    rt_uint32_t coef[2], prop;

    if (!np)
    {
        return;
    }

    if (!rt_ofw_prop_read_u32(np, "sustainable-power", &prop))
    {
        tz_params->sustainable_power = prop;
    }

    /*
     * For now, the thermal framework supports only one sensor per thermal zone.
     * Thus, we are considering only the first two values as slope and offset.
     */
    if (rt_ofw_prop_read_u32_array_index(np, "coefficients", 0, 1, coef) < 0)
    {
        coef[0] = 1;
        coef[1] = 0;
    }

    tz_params->slope = coef[0];
    tz_params->offset = coef[1];
}

static void thermal_ofw_setup(struct rt_ofw_node *np, struct rt_thermal_zone_device *zdev)
{
    int i = 0;
    rt_uint32_t delay, pdelay;
    struct rt_ofw_cell_args args;
    struct rt_ofw_node *tmp_np, *tz_np, *trip_np, *cm_np, *cdev_np;

    if (!np || !zdev)
    {
        return;
    }

    tmp_np = rt_ofw_find_node_by_path("/thermal-zones");

    if (!tmp_np)
    {
        return;
    }

    rt_ofw_foreach_child_node(tmp_np, tz_np)
    {
        if (!rt_ofw_parse_phandle_cells(tz_np, "thermal-sensors", "#thermal-sensor-cells", 0, &args))
        {
            if (args.data == np && (!args.args_count || args.args[0] == zdev->zone_id))
            {
                rt_ofw_node_put(args.data);

                goto _found;
            }
            rt_ofw_node_put(args.data);
        }
    }

    return;

_found:
    rt_ofw_prop_read_u32(tz_np, "polling-delay-passive", &pdelay);
    rt_ofw_prop_read_u32(tz_np, "polling-delay", &delay);

    zdev->passive_delay = rt_tick_from_millisecond(pdelay);
    zdev->polling_delay = rt_tick_from_millisecond(delay);

    thermal_ofw_params_parse(tz_np, &zdev->params);

    if (zdev->trips_nr)
    {
        goto _scan_cooling;
    }

    tmp_np = rt_ofw_get_child_by_tag(tz_np, "trips");
    if (!tmp_np)
    {
        goto _scan_cooling;
    }

    zdev->trips_nr = rt_ofw_get_child_count(tmp_np);
    if (!zdev->trips_nr)
    {
        goto _scan_cooling;
    }
    zdev->trips = rt_calloc(zdev->trips_nr, sizeof(*zdev->trips));
    zdev->trips_free = RT_TRUE;

    if (!zdev->trips)
    {
        LOG_E("%s: No memory to create %s", rt_ofw_node_full_name(np), "trips");
        RT_ASSERT(0);
    }

    rt_ofw_foreach_child_node(tmp_np, trip_np)
    {
        const char *type;

        rt_ofw_prop_read_u32(trip_np, "temperature", (rt_uint32_t *)&zdev->trips[i].temperature);
        rt_ofw_prop_read_u32(trip_np, "hysteresis", (rt_uint32_t *)&zdev->trips[i].hysteresis);
        rt_ofw_prop_read_string(trip_np, "type", &type);
        zdev->trips[i].type = thermal_type(type);

        rt_ofw_data(trip_np) = &zdev->trips[i];

        ++i;
    }

_scan_cooling:
    i = 0;
    tmp_np = rt_ofw_get_child_by_tag(tz_np, "cooling-maps");
    if (!tmp_np)
    {
        goto _end;
    }

    zdev->cooling_maps_nr = rt_ofw_get_child_count(tmp_np);
    if (!zdev->cooling_maps_nr)
    {
        goto _end;
    }
    zdev->cooling_maps = rt_calloc(zdev->cooling_maps_nr, sizeof(*zdev->cooling_maps));

    if (!zdev->cooling_maps)
    {
        LOG_E("%s: No memory to create %s", rt_ofw_node_full_name(np), "cooling_maps");
        RT_ASSERT(0);
    }

    rt_ofw_foreach_child_node(tmp_np, cm_np)
    {
        struct rt_thermal_cooling_device *cdev;
        struct rt_thermal_cooling_map *map = &zdev->cooling_maps[i++];

        map->cells_nr = rt_ofw_count_phandle_cells(cm_np, "cooling-device", "#cooling-cells");
        map->cells = rt_calloc(sizeof(*map->cells), map->cells_nr);

        if (!map->cells)
        {
            LOG_E("%s: No memory to create %s", rt_ofw_node_full_name(np), "cells");
            RT_ASSERT(0);
        }

        trip_np = rt_ofw_parse_phandle(cm_np, "trip", 0);
        map->trips = rt_ofw_data(trip_np);
        rt_ofw_node_put(trip_np);

        if (!map->trips)
        {
            LOG_E("%s: trips(%s) not found", rt_ofw_node_full_name(np),
                    rt_ofw_node_full_name(trip_np));
            RT_ASSERT(0);
        }

        rt_ofw_prop_read_u32(cm_np, "contribution", &map->contribution);

        for (int c = 0; c < map->cells_nr; ++c)
        {
            struct rt_thermal_cooling_cell *cell = &map->cells[c];

            if (rt_ofw_parse_phandle_cells(cm_np, "cooling-device", "#cooling-cells", c, &args))
            {
                continue;
            }

            cdev_np = args.data;

            rt_spin_lock(&nodes_lock);
            device_foreach(cdev, &thermal_cooling_device_nodes)
            {
                if (cdev->parent.ofw_node == cdev_np)
                {
                    cell->cooling_devices = cdev;
                    break;
                }
            }
            rt_spin_unlock(&nodes_lock);

            cell->level_range[0] = args.args[0];
            cell->level_range[1] = args.args[1];

            if (cell->cooling_devices)
            {
                thermal_bind(cell->cooling_devices, zdev);
            }

            rt_ofw_node_put(cdev_np);
        }
    }
_end:
}
#else
rt_inline void thermal_ofw_setup(struct rt_ofw_node *np, struct rt_thermal_zone_device *zdev)
{
}
#endif /* RT_USING_OFW */

static void thermal_zone_poll(struct rt_work *work, void *work_data)
{
    struct rt_thermal_zone_device *zdev = work_data;

    rt_thermal_zone_device_update(zdev, RT_THERMAL_MSG_EVENT_UNSPECIFIED);
}

rt_err_t rt_thermal_zone_device_register(struct rt_thermal_zone_device *zdev)
{
    if (!zdev || !zdev->ops || !zdev->ops->get_temp)
    {
        return -RT_EINVAL;
    }

    zdev->ops->get_temp(zdev, &zdev->temperature);
    zdev->last_temperature = zdev->temperature;

    if (!zdev->trips)
    {
        zdev->trips_nr = 0;
    }

    rt_spin_lock_init(&zdev->nodes_lock);
    rt_list_init(&zdev->notifier_nodes);
    rt_list_init(&device_list(zdev));
    rt_mutex_init(&zdev->mutex, rt_dm_dev_get_name(&zdev->parent), RT_IPC_FLAG_PRIO);

    zdev->temperature = RT_THERMAL_TEMP_INVALID;
    zdev->prev_low_trip = -INT_MAX;
    zdev->prev_high_trip = INT_MAX;

    rt_spin_lock(&nodes_lock);
    rt_list_insert_before(&thermal_zone_device_nodes, &device_list(zdev));
    rt_spin_unlock(&nodes_lock);

    thermal_ofw_setup(zdev->parent.ofw_node, zdev);

    rt_work_init(&zdev->poller, thermal_zone_poll, zdev);
    zdev->enabled = RT_TRUE;

    /* Start to poll */
    rt_work_submit(&zdev->poller, zdev->polling_delay);

    return RT_EOK;
}

rt_err_t rt_thermal_zone_device_unregister(struct rt_thermal_zone_device *zdev)
{
    if (!zdev)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&zdev->nodes_lock);
    if (rt_list_isempty(&zdev->notifier_nodes))
    {
        LOG_E("%s: there is %u user", rt_dm_dev_get_name(&zdev->parent),
                rt_list_len(&zdev->notifier_nodes));

        rt_spin_unlock(&zdev->nodes_lock);

        return -RT_EBUSY;
    }
    rt_spin_unlock(&zdev->nodes_lock);

    rt_work_cancel(&zdev->poller);

    rt_spin_lock(&nodes_lock);
    rt_list_remove(&device_list(zdev));
    rt_spin_unlock(&nodes_lock);

    if (zdev->trips_free && zdev->trips)
    {
        rt_free(zdev->trips);
    }

    if (zdev->cooling_maps_nr && zdev->cooling_maps_nr)
    {
        for (int i = 0; i < zdev->cooling_maps_nr; ++i)
        {
            struct rt_thermal_cooling_device *cdev;
            struct rt_thermal_cooling_map *map = &zdev->cooling_maps[i];

            for (int c = 0; c < map->cells_nr; ++c)
            {
                cdev = map->cells[i].cooling_devices;

                if (cdev)
                {
                    thermal_unbind(cdev, zdev);
                }
            }

            rt_free(map->cells);
        }

        rt_free(zdev->cooling_maps);
    }

    rt_mutex_detach(&zdev->mutex);

    return RT_EOK;
}

rt_err_t rt_thermal_cooling_device_register(struct rt_thermal_cooling_device *cdev)
{
    rt_err_t err;

    if (!cdev || !cdev->ops ||
        !cdev->ops->get_max_level || !cdev->ops->get_cur_level || !cdev->ops->set_cur_level)
    {
        return -RT_EINVAL;
    }

    if ((err = cdev->ops->get_max_level(cdev, &cdev->max_level)))
    {
        return err;
    }

    rt_list_init(&device_list(cdev));
    rt_list_init(&cdev->governor_node);

    rt_spin_lock(&nodes_lock);
    rt_list_insert_before(&thermal_cooling_device_nodes, &device_list(cdev));
    rt_spin_unlock(&nodes_lock);

    err = rt_thermal_cooling_device_change_governor(cdev, RT_NULL);

    return err;
}

rt_err_t rt_thermal_cooling_device_unregister(struct rt_thermal_cooling_device *cdev)
{
    if (!cdev)
    {
        return -RT_EINVAL;
    }

    if (cdev->parent.ref_count)
    {
        LOG_E("%s: there is %u user",
                rt_dm_dev_get_name(&cdev->parent), cdev->parent.ref_count);
        return -RT_EINVAL;
    }

    rt_spin_lock(&nodes_lock);
    rt_list_remove(&device_list(cdev));
    rt_spin_unlock(&nodes_lock);

    return RT_EOK;
}

static void dumb_governor_tuning(struct rt_thermal_zone_device *zdev,
            int map_idx, int cell_idx, rt_ubase_t *level)
{
    struct rt_thermal_cooling_map *map = &zdev->cooling_maps[map_idx];

    if (zdev->cooling && zdev->temperature > map->trips->temperature)
    {
        if (zdev->temperature - zdev->last_temperature > map->trips->hysteresis)
        {
            ++*level;
        }
        else if (zdev->last_temperature - zdev->temperature > map->trips->hysteresis)
        {
            --*level;
        }
    }
    else
    {
        *level = 0;
    }
}

static struct rt_thermal_cooling_governor dumb_governor =
{
    .name = "dumb",
    .tuning = dumb_governor_tuning,
};

static int system_thermal_cooling_governor_init(void)
{
    rt_thermal_cooling_governor_register(&dumb_governor);

    return 0;
}
INIT_CORE_EXPORT(system_thermal_cooling_governor_init);

rt_err_t rt_thermal_cooling_governor_register(struct rt_thermal_cooling_governor *gov)
{
    rt_err_t err = RT_EOK;
    struct rt_thermal_cooling_governor *gov_tmp;

    if (!gov || !gov->name || !gov->tuning)
    {
        return -RT_EINVAL;
    }

    rt_list_init(&gov->list);
    rt_list_init(&gov->cdev_nodes);

    rt_spin_lock(&nodes_lock);

    rt_list_for_each_entry(gov_tmp, &thermal_cooling_governor_nodes, list)
    {
        if (!rt_strcmp(gov_tmp->name, gov->name))
        {
            err = -RT_ERROR;
            goto _out_unlock;
        }
    }

    rt_list_insert_before(&thermal_cooling_governor_nodes, &gov->list);

_out_unlock:
    rt_spin_unlock(&nodes_lock);

    return err;
}

rt_err_t rt_thermal_cooling_governor_unregister(struct rt_thermal_cooling_governor *gov)
{
    if (!gov)
    {
        return -RT_EINVAL;
    }

    if (gov == &dumb_governor)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&nodes_lock);

    if (!rt_list_isempty(&gov->cdev_nodes))
    {
        goto _out_unlock;
    }

    rt_list_remove(&gov->list);

_out_unlock:
    rt_spin_unlock(&nodes_lock);

    return RT_EOK;
}

rt_err_t rt_thermal_cooling_device_change_governor(struct rt_thermal_cooling_device *cdev,
        const char *name)
{
    rt_err_t err;
    struct rt_thermal_cooling_governor *gov;

    if (!cdev)
    {
        return -RT_EINVAL;
    }

    name = name ? : dumb_governor.name;
    err = -RT_ENOSYS;

    rt_spin_lock(&nodes_lock);

    rt_list_for_each_entry(gov, &thermal_cooling_governor_nodes, list)
    {
        if (!rt_strcmp(gov->name, name))
        {
            if (cdev->gov)
            {
                rt_list_remove(&cdev->governor_node);
            }

            cdev->gov = gov;
            rt_list_insert_before(&cdev->governor_node, &gov->cdev_nodes);

            err = RT_EOK;
            break;
        }
    }

    rt_spin_unlock(&nodes_lock);

    return err;
}

rt_err_t rt_thermal_zone_notifier_register(struct rt_thermal_zone_device *zdev,
        struct rt_thermal_notifier *notifier)
{
    if (!zdev || !notifier)
    {
        return -RT_EINVAL;
    }

    notifier->zdev = zdev;
    rt_list_init(&notifier->list);

    rt_spin_lock(&zdev->nodes_lock);
    rt_list_insert_after(&zdev->notifier_nodes, &notifier->list);
    rt_spin_unlock(&zdev->nodes_lock);

    return RT_EOK;
}

rt_err_t rt_thermal_zone_notifier_unregister(struct rt_thermal_zone_device *zdev,
        struct rt_thermal_notifier *notifier)
{
    if (!zdev || !notifier)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&zdev->nodes_lock);
    rt_list_remove(&notifier->list);
    rt_spin_unlock(&zdev->nodes_lock);

    return RT_EOK;
}

void rt_thermal_zone_device_update(struct rt_thermal_zone_device *zdev, rt_ubase_t msg)
{
    rt_err_t err;
    rt_bool_t passive = RT_FALSE, need_cool = RT_FALSE;
    struct rt_thermal_notifier *notifier, *next_notifier;

    RT_ASSERT(zdev != RT_NULL);

    if (!rt_interrupt_get_nest())
    {
        rt_mutex_take(&zdev->mutex, RT_WAITING_FOREVER);
    }

    /* Check thermal zone status */
    if (msg == RT_THERMAL_MSG_DEVICE_DOWN)
    {
        zdev->enabled = RT_FALSE;
    }
    else if (msg == RT_THERMAL_MSG_DEVICE_UP)
    {
        zdev->enabled = RT_TRUE;
    }

    /* Read temperature */
    zdev->last_temperature = zdev->temperature;
    zdev->ops->get_temp(zdev, &zdev->temperature);

    for (int i = 0; i < zdev->trips_nr; ++i)
    {
        struct rt_thermal_trip *tmp_trip = &zdev->trips[i];

        if (zdev->temperature <= tmp_trip->temperature)
        {
            continue;
        }

        switch (tmp_trip->type)
        {
        case RT_THERMAL_TRIP_PASSIVE:
            passive = RT_TRUE;
            goto cooling;

        case RT_THERMAL_TRIP_CRITICAL:
            if (zdev->ops->critical)
            {
                zdev->ops->critical(zdev);
            }
            else if (zdev->last_temperature > tmp_trip->temperature)
            {
                /* Tried to cool already, but failed */
                rt_hw_cpu_reset();
            }
            else
            {
                goto cooling;
            }
            break;

        case RT_THERMAL_TRIP_HOT:
            if (zdev->ops->hot)
            {
                zdev->ops->hot(zdev);
                break;
            }

        default:
        cooling:
            zdev->cooling = need_cool = RT_TRUE;
            rt_thermal_cooling_device_kick(zdev);
            break;
        }
    }

    if (!need_cool && zdev->cooling)
    {
        rt_thermal_cooling_device_kick(zdev);
    }

    /* Set the new trips */
    if (zdev->ops->set_trips)
    {
        rt_bool_t same_trip = RT_FALSE;
        int low = -INT_MAX, high = INT_MAX;
        struct rt_thermal_trip trip;

        for (int i = 0; i < zdev->trips_nr; ++i)
        {
            int trip_low;
            rt_bool_t low_set = RT_FALSE;

            if (i >= zdev->trips_nr)
            {
                goto _call_notifier;
            }
            rt_memcpy(&trip, &zdev->trips[i], sizeof(trip));

            trip_low = trip.temperature - trip.hysteresis;

            if (trip_low < zdev->temperature && trip_low > low)
            {
                low = trip_low;
                low_set = RT_TRUE;
                same_trip = RT_FALSE;
            }

            if (trip.temperature > zdev->temperature && trip.temperature < high)
            {
                high = trip.temperature;
                same_trip = low_set;
            }
        }

        /* No need to change trip points */
        if (zdev->prev_low_trip == low && zdev->prev_high_trip == high)
        {
            goto _call_notifier;
        }

        if (same_trip &&
            (zdev->prev_low_trip != -INT_MAX || zdev->prev_high_trip != INT_MAX))
        {
            goto _call_notifier;
        }

        zdev->prev_low_trip = low;
        zdev->prev_high_trip = high;

        if ((err = zdev->ops->set_trips(zdev, low, high)))
        {
            LOG_E("%s: Set trips error = %s", rt_dm_dev_get_name(&zdev->parent),
                    rt_strerror(err));
        }
    }

    /* Call all notifier, maybe have governor */
_call_notifier:
    rt_spin_lock(&zdev->nodes_lock);

    rt_list_for_each_entry_safe(notifier, next_notifier, &zdev->notifier_nodes, list)
    {
        rt_spin_unlock(&zdev->nodes_lock);

        notifier->callback(notifier, msg);

        rt_spin_lock(&zdev->nodes_lock);
    }

    rt_spin_unlock(&zdev->nodes_lock);

    /* Prepare for the next report */
    if (!zdev->enabled)
    {
        rt_work_cancel(&zdev->poller);
    }
    else if (passive && zdev->passive_delay)
    {
        rt_work_submit(&zdev->poller, zdev->passive_delay);
    }
    else if (zdev->polling_delay)
    {
        rt_work_submit(&zdev->poller, zdev->polling_delay);
    }

    if (!rt_interrupt_get_nest())
    {
        rt_mutex_release(&zdev->mutex);
    }
}

void rt_thermal_cooling_device_kick(struct rt_thermal_zone_device *zdev)
{
    RT_ASSERT(zdev != RT_NULL);

    for (int i = 0; i < zdev->cooling_maps_nr; ++i)
    {
        rt_ubase_t level;
        struct rt_thermal_cooling_device *cdev;
        struct rt_thermal_cooling_cell *cell;
        struct rt_thermal_cooling_map *map = &zdev->cooling_maps[i];

        for (int c = 0; c < map->cells_nr; ++c)
        {
            cell = &map->cells[c];
            cdev = cell->cooling_devices;

            if (!cdev)
            {
                continue;
            }

            /* Update status */
            if (cdev->ops->get_max_level(cdev, &cdev->max_level))
            {
                continue;
            }

            if (cdev->ops->get_cur_level(cdev, &level) || level > cdev->max_level)
            {
                continue;
            }

            /* Check if cooling is required */
            if (level >= cell->level_range[0] && level <= cell->level_range[1])
            {
                /* Is cooling, not call */
                continue;
            }

            cdev->gov->tuning(zdev, i, c, &level);
            level = rt_min_t(rt_ubase_t, level, cdev->max_level);

            cdev->ops->set_cur_level(cdev, level);
        }
    }
}

rt_err_t rt_thermal_zone_set_trip(struct rt_thermal_zone_device *zdev, int trip_id,
        const struct rt_thermal_trip *trip)
{
    rt_err_t err;
    struct rt_thermal_trip tmp_trip;

    if (!zdev || !trip)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&zdev->mutex, RT_WAITING_FOREVER);

    if (!zdev->ops->set_trip_temp && !zdev->ops->set_trip_hyst && !zdev->trips)
    {
        err = -RT_EINVAL;
        goto _out_unlock;
    }

    if (trip_id >= zdev->trips_nr)
    {
        err = -RT_EINVAL;
        goto _out_unlock;
    }

    rt_memcpy(&tmp_trip, &zdev->trips[trip_id], sizeof(tmp_trip));

    if (tmp_trip.type != trip->type)
    {
        err = -RT_EINVAL;
        goto _out_unlock;
    }

    if (tmp_trip.temperature != trip->temperature && zdev->ops->set_trip_temp)
    {
        if ((err = zdev->ops->set_trip_temp(zdev, trip_id, trip->temperature)))
        {
            goto _out_unlock;
        }
    }

    if (tmp_trip.hysteresis != trip->hysteresis && zdev->ops->set_trip_hyst)
    {
        if ((err = zdev->ops->set_trip_hyst(zdev, trip_id, trip->hysteresis)))
        {
            goto _out_unlock;
        }
    }

    if (zdev->trips &&
        (tmp_trip.temperature != trip->temperature || tmp_trip.hysteresis != trip->hysteresis))
    {
        zdev->trips[trip_id] = *trip;
    }

_out_unlock:
    rt_mutex_release(&zdev->mutex);

    if (!err)
    {
        rt_thermal_zone_device_update(zdev, RT_THERMAL_MSG_TRIP_CHANGED);
    }

    return err;
}

rt_err_t rt_thermal_zone_get_trip(struct rt_thermal_zone_device *zdev, int trip_id,
        struct rt_thermal_trip *out_trip)
{
    rt_err_t err = RT_EOK;

    if (!zdev || !out_trip)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&zdev->mutex, RT_WAITING_FOREVER);

    if (!zdev->trips_nr)
    {
        err = -RT_ENOSYS;
        goto _out_unlock;
    }

    if (trip_id >= zdev->trips_nr)
    {
        err = -RT_EINVAL;
        goto _out_unlock;
    }

    *out_trip = zdev->trips[trip_id];

_out_unlock:
    rt_mutex_release(&zdev->mutex);

    return err;
}

#if defined(RT_USING_CONSOLE) && defined(RT_USING_MSH)
static int list_thermal(int argc, char**argv)
{
    struct rt_thermal_zone_device *zdev;

    /* Thermal is an important subsystem, please do not output too much. */
    rt_spin_lock(&nodes_lock);
    device_foreach(zdev, &thermal_zone_device_nodes)
    {
        int temperature = zdev->temperature;

        rt_kprintf("%s-%d\n", rt_dm_dev_get_name(&zdev->parent), zdev->zone_id);
        rt_kprintf("temperature:\t%+d.%u C\n", temperature / 1000, rt_abs(temperature) % 1000);

        for (int i = 0, id = 0; i < zdev->cooling_maps_nr; ++i)
        {
            rt_ubase_t level;
            struct rt_thermal_trip *trips;
            struct rt_thermal_cooling_device *cdev;
            struct rt_thermal_cooling_cell *cell;
            struct rt_thermal_cooling_map *map = &zdev->cooling_maps[i];

            for (int c = 0; c < map->cells_nr; ++c, ++id)
            {
                trips = map->trips;
                cell = &map->cells[c];
                cdev = cell->cooling_devices;

                if (cdev)
                {
                    cdev->ops->get_cur_level(cdev, &level);

                    rt_kprintf("cooling%u:\t%s[%+d.%u C] %d\n", id,
                            rt_dm_dev_get_name(&cdev->parent),
                            trips->temperature / 1000, rt_abs(trips->temperature) % 1000,
                            level);
                }
                else
                {
                    rt_kprintf("cooling%u:\t%s[%+d.%u C] %d\n", id,
                            "(not supported)",
                            trips->temperature / 1000, rt_abs(trips->temperature) % 1000,
                            0);
                }
            }
        }
    }
    rt_spin_unlock(&nodes_lock);

    return 0;
}
MSH_CMD_EXPORT(list_thermal, dump all of thermal information);
#endif /* RT_USING_CONSOLE && RT_USING_MSH */
