/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __THERMAL_H__
#define __THERMAL_H__

#include <rtdef.h>
#include <dt-bindings/thermal/thermal.h>

/* No upper/lower limit requirement */
#define RT_THERMAL_NO_LIMIT         ((rt_uint32_t)THERMAL_NO_LIMIT)
#define RT_THERMAL_TEMP_INVALID     (-274000)

struct rt_thermal_zone_ops;
struct rt_thermal_cooling_device;
struct rt_thermal_cooling_device_ops;
struct rt_thermal_cooling_governor;

enum rt_thermal_trip_type
{
    RT_THERMAL_TRIP_ACTIVE = 0,
    RT_THERMAL_TRIP_PASSIVE,
    RT_THERMAL_TRIP_HOT,
    RT_THERMAL_TRIP_CRITICAL,

    RT_THERMAL_TRIP_TYPE_MAX,
};

struct rt_thermal_trip
{
    /* Temperature value in millidegree celsius */
    int temperature;
    /* Relative hysteresis in millidegree celsius */
    int hysteresis;
    enum rt_thermal_trip_type type;

    void *priv;
};

struct rt_thermal_zone_params
{
    /* Sustainable power (heat) that this thermal zone can dissipate in mW */
    int sustainable_power;
    /* Slope of a linear temperature adjustment curve */
    int slope;
    /* Offset of a linear temperature adjustment curve */
    int offset;
};

struct rt_thermal_cooling_cell
{
    struct rt_thermal_cooling_device *cooling_devices;

    rt_uint32_t level_range[2];
};

struct rt_thermal_cooling_map
{
    rt_uint32_t contribution;

    rt_size_t cells_nr;
    struct rt_thermal_cooling_cell *cells;
    struct rt_thermal_trip *trips;
};

struct rt_thermal_zone_device
{
    struct rt_device parent;

    int zone_id;
    const struct rt_thermal_zone_ops *ops;

    rt_bool_t trips_free;
    rt_size_t trips_nr;
    struct rt_thermal_trip *trips;
    struct rt_thermal_zone_params params;

    rt_bool_t enabled;
    rt_bool_t cooling;
    int temperature;
    int last_temperature;
    int prev_low_trip;
    int prev_high_trip;

    rt_list_t notifier_nodes;
    struct rt_spinlock nodes_lock;

    rt_size_t cooling_maps_nr;
    struct rt_thermal_cooling_map *cooling_maps;

    rt_tick_t passive_delay, polling_delay;
    struct rt_work poller;

    struct rt_mutex mutex;

    void *priv;
};

struct rt_thermal_zone_ops
{
    rt_err_t (*get_temp)(struct rt_thermal_zone_device *zdev, int *out_temp);
    rt_err_t (*set_trips)(struct rt_thermal_zone_device *zdev, int low_temp, int high_temp);
    rt_err_t (*set_trip_temp)(struct rt_thermal_zone_device *zdev, int trip_id, int temp);
    rt_err_t (*set_trip_hyst)(struct rt_thermal_zone_device *zdev, int trip_id, int hyst);
    void (*hot)(struct rt_thermal_zone_device *zdev);
    void (*critical)(struct rt_thermal_zone_device *zdev);
};

/*
 * We don't want to make a temperature control system
 * that is finer than an air conditioner's temperature control,
 * just ensure get a reliable heat dissipation under high-load task
 * or when the SoC temperature is too high.
 */
struct rt_thermal_cooling_device
{
    struct rt_device parent;

    const struct rt_thermal_cooling_device_ops *ops;

    /* The cooling capacity indicator */
    rt_ubase_t max_level;
    rt_list_t governor_node;
    struct rt_thermal_cooling_governor *gov;

    void *priv;
};

struct rt_thermal_cooling_device_ops
{
    rt_err_t (*bind)(struct rt_thermal_cooling_device *cdev, struct rt_thermal_zone_device *zdev);
    rt_err_t (*unbind)(struct rt_thermal_cooling_device *cdev, struct rt_thermal_zone_device *zdev);
    rt_err_t (*get_max_level)(struct rt_thermal_cooling_device *cdev, rt_ubase_t *out_level);
    rt_err_t (*get_cur_level)(struct rt_thermal_cooling_device *cdev, rt_ubase_t *out_level);
    rt_err_t (*set_cur_level)(struct rt_thermal_cooling_device *cdev, rt_ubase_t level);
};

struct rt_thermal_cooling_governor
{
    rt_list_t list;

    const char *name;
    rt_list_t cdev_nodes;

    void (*tuning)(struct rt_thermal_zone_device *zdev,
            int map_idx, int cell_idx, rt_ubase_t *level);
};

struct rt_thermal_notifier;

#define RT_THERMAL_MSG_EVENT_UNSPECIFIED                RT_BIT(0) /* Unspecified event */
#define RT_THERMAL_MSG_EVENT_TEMP_SAMPLE                RT_BIT(1) /* New Temperature sample */
#define RT_THERMAL_MSG_TRIP_VIOLATED                    RT_BIT(2) /* TRIP Point violation */
#define RT_THERMAL_MSG_TRIP_CHANGED                     RT_BIT(3) /* TRIP Point temperature changed */
#define RT_THERMAL_MSG_DEVICE_DOWN                      RT_BIT(4) /* Thermal device is down */
#define RT_THERMAL_MSG_DEVICE_UP                        RT_BIT(5) /* Thermal device is up after a down event */
#define RT_THERMAL_MSG_DEVICE_POWER_CAPABILITY_CHANGED  RT_BIT(6) /* Power capability changed */
#define RT_THERMAL_MSG_TABLE_CHANGED                    RT_BIT(7) /* Thermal table(s) changed */
#define RT_THERMAL_MSG_EVENT_KEEP_ALIVE                 RT_BIT(8) /* Request for user space handler to respond */

typedef rt_err_t (*rt_thermal_notifier_callback)(struct rt_thermal_notifier *notifier,
        rt_ubase_t msg);

struct rt_thermal_notifier
{
    rt_list_t list;

    struct rt_thermal_zone_device *zdev;
    rt_thermal_notifier_callback callback;
    void *priv;
};

rt_err_t rt_thermal_zone_device_register(struct rt_thermal_zone_device *zdev);
rt_err_t rt_thermal_zone_device_unregister(struct rt_thermal_zone_device *zdev);

rt_err_t rt_thermal_cooling_device_register(struct rt_thermal_cooling_device *cdev);
rt_err_t rt_thermal_cooling_device_unregister(struct rt_thermal_cooling_device *cdev);

rt_err_t rt_thermal_cooling_governor_register(struct rt_thermal_cooling_governor *gov);
rt_err_t rt_thermal_cooling_governor_unregister(struct rt_thermal_cooling_governor *gov);

rt_err_t rt_thermal_cooling_device_change_governor(struct rt_thermal_cooling_device *cdev,
        const char *name);

rt_err_t rt_thermal_zone_notifier_register(struct rt_thermal_zone_device *zdev,
        struct rt_thermal_notifier *notifier);
rt_err_t rt_thermal_zone_notifier_unregister(struct rt_thermal_zone_device *zdev,
        struct rt_thermal_notifier *notifier);

void rt_thermal_zone_device_update(struct rt_thermal_zone_device *zdev, rt_ubase_t msg);
void rt_thermal_cooling_device_kick(struct rt_thermal_zone_device *zdev);

rt_err_t rt_thermal_zone_set_trip(struct rt_thermal_zone_device *zdev, int trip_id,
        const struct rt_thermal_trip *trip);
rt_err_t rt_thermal_zone_get_trip(struct rt_thermal_zone_device *zdev, int trip_id,
        struct rt_thermal_trip *out_trip);

#endif /* __THERMAL_H__ */
