/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#ifndef __POWER_SUPPLY_H__
#define __POWER_SUPPLY_H__

#include <rtthread.h>
#include <drivers/led.h>
#include <drivers/thermal.h>

enum rt_power_supply_type
{
    RT_POWER_SUPPLY_TYPE_UNKNOWN = 0,
    RT_POWER_SUPPLY_TYPE_BATTERY,
    RT_POWER_SUPPLY_TYPE_UPS,
    RT_POWER_SUPPLY_TYPE_MAINS,
    RT_POWER_SUPPLY_TYPE_USB_SDP,           /* Standard Downstream Port */
    RT_POWER_SUPPLY_TYPE_USB_DCP,           /* Dedicated Charging Port */
    RT_POWER_SUPPLY_TYPE_USB_CDP,           /* Charging Downstream Port */
    RT_POWER_SUPPLY_TYPE_USB_ACA,           /* Accessory Charger Adapters */
    RT_POWER_SUPPLY_TYPE_USB_TYPE_C,        /* Type C Port */
    RT_POWER_SUPPLY_TYPE_USB_PD,            /* Power Delivery Port */
    RT_POWER_SUPPLY_TYPE_USB_PD_DRP,        /* PD Dual Role Port */
    RT_POWER_SUPPLY_TYPE_USB_PD_PPS,        /* PD Programmable Power Supply */
    RT_POWER_SUPPLY_TYPE_WIRELESS,          /* Wireless */
};

enum rt_power_supply_status
{
    RT_POWER_SUPPLY_STATUS_UNKNOWN = 0,
    RT_POWER_SUPPLY_STATUS_CHARGING,
    RT_POWER_SUPPLY_STATUS_DISCHARGING,
    RT_POWER_SUPPLY_STATUS_NOT_CHARGING,
    RT_POWER_SUPPLY_STATUS_FULL,
};

enum rt_power_supply_charge_type
{
    RT_POWER_SUPPLY_CHARGE_TYPE_UNKNOWN = 0,
    RT_POWER_SUPPLY_CHARGE_TYPE_NONE,
    RT_POWER_SUPPLY_CHARGE_TYPE_TRICKLE,    /* Slow speed */
    RT_POWER_SUPPLY_CHARGE_TYPE_FAST,       /* Fast speed */
    RT_POWER_SUPPLY_CHARGE_TYPE_STANDARD,   /* Normal speed */
    RT_POWER_SUPPLY_CHARGE_TYPE_ADAPTIVE,   /* Dynamically adjusted speed */
    RT_POWER_SUPPLY_CHARGE_TYPE_CUSTOM,     /* Use CHARGE_CONTROL_* props */
    RT_POWER_SUPPLY_CHARGE_TYPE_LONGLIFE,   /* Slow speed, longer life */
    RT_POWER_SUPPLY_CHARGE_TYPE_BYPASS,     /* Bypassing the charger */
};

enum rt_power_supply_health
{
    RT_POWER_SUPPLY_HEALTH_UNKNOWN = 0,
    RT_POWER_SUPPLY_HEALTH_GOOD,
    RT_POWER_SUPPLY_HEALTH_OVERHEAT,
    RT_POWER_SUPPLY_HEALTH_DEAD,
    RT_POWER_SUPPLY_HEALTH_OVERVOLTAGE,
    RT_POWER_SUPPLY_HEALTH_UNSPEC_FAILURE,
    RT_POWER_SUPPLY_HEALTH_COLD,
    RT_POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE,
    RT_POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE,
    RT_POWER_SUPPLY_HEALTH_OVERCURRENT,
    RT_POWER_SUPPLY_HEALTH_CALIBRATION_REQUIRED,
    RT_POWER_SUPPLY_HEALTH_WARM,
    RT_POWER_SUPPLY_HEALTH_COOL,
    RT_POWER_SUPPLY_HEALTH_HOT,
    RT_POWER_SUPPLY_HEALTH_NO_BATTERY,
};

enum rt_power_supply_technology
{
    RT_POWER_SUPPLY_TECHNOLOGY_UNKNOWN = 0,
    RT_POWER_SUPPLY_TECHNOLOGY_NiMH,
    RT_POWER_SUPPLY_TECHNOLOGY_LION,
    RT_POWER_SUPPLY_TECHNOLOGY_LIPO,
    RT_POWER_SUPPLY_TECHNOLOGY_LiFe,
    RT_POWER_SUPPLY_TECHNOLOGY_NiCd,
    RT_POWER_SUPPLY_TECHNOLOGY_LiMn,
};

enum rt_power_supply_capacity_level
{
    RT_POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN = 0,
    RT_POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL,
    RT_POWER_SUPPLY_CAPACITY_LEVEL_LOW,
    RT_POWER_SUPPLY_CAPACITY_LEVEL_NORMAL,
    RT_POWER_SUPPLY_CAPACITY_LEVEL_HIGH,
    RT_POWER_SUPPLY_CAPACITY_LEVEL_FULL,
};

enum rt_power_supply_scope
{
    RT_POWER_SUPPLY_SCOPE_UNKNOWN = 0,
    RT_POWER_SUPPLY_SCOPE_SYSTEM,
    RT_POWER_SUPPLY_SCOPE_DEVICE,
};

enum rt_power_supply_property
{
    /* Properties of type `int' */
    RT_POWER_SUPPLY_PROP_STATUS = 0,
    RT_POWER_SUPPLY_PROP_CHARGE_TYPE,
    RT_POWER_SUPPLY_PROP_HEALTH,
    RT_POWER_SUPPLY_PROP_PRESENT,
    RT_POWER_SUPPLY_PROP_ONLINE,
    RT_POWER_SUPPLY_PROP_AUTHENTIC,
    RT_POWER_SUPPLY_PROP_TECHNOLOGY,
    RT_POWER_SUPPLY_PROP_CYCLE_COUNT,
    RT_POWER_SUPPLY_PROP_VOLTAGE_MAX,
    RT_POWER_SUPPLY_PROP_VOLTAGE_MIN,
    RT_POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
    RT_POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
    RT_POWER_SUPPLY_PROP_VOLTAGE_NOW,
    RT_POWER_SUPPLY_PROP_VOLTAGE_AVG,
    RT_POWER_SUPPLY_PROP_VOLTAGE_OCV,
    RT_POWER_SUPPLY_PROP_VOLTAGE_BOOT,
    RT_POWER_SUPPLY_PROP_CURRENT_MAX,
    RT_POWER_SUPPLY_PROP_CURRENT_NOW,
    RT_POWER_SUPPLY_PROP_CURRENT_AVG,
    RT_POWER_SUPPLY_PROP_CURRENT_BOOT,
    RT_POWER_SUPPLY_PROP_POWER_NOW,
    RT_POWER_SUPPLY_PROP_POWER_AVG,
    RT_POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
    RT_POWER_SUPPLY_PROP_CHARGE_EMPTY_DESIGN,
    RT_POWER_SUPPLY_PROP_CHARGE_FULL,
    RT_POWER_SUPPLY_PROP_CHARGE_EMPTY,
    RT_POWER_SUPPLY_PROP_CHARGE_NOW,
    RT_POWER_SUPPLY_PROP_CHARGE_AVG,
    RT_POWER_SUPPLY_PROP_CHARGE_COUNTER,
    RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
    RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
    RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
    RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
    RT_POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT,
    RT_POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX,
    RT_POWER_SUPPLY_PROP_CHARGE_CONTROL_START_THRESHOLD,
    RT_POWER_SUPPLY_PROP_CHARGE_CONTROL_END_THRESHOLD,
    RT_POWER_SUPPLY_PROP_CHARGE_BEHAVIOUR,
    RT_POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
    RT_POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT,
    RT_POWER_SUPPLY_PROP_INPUT_POWER_LIMIT,
    RT_POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN,
    RT_POWER_SUPPLY_PROP_ENERGY_EMPTY_DESIGN,
    RT_POWER_SUPPLY_PROP_ENERGY_FULL,
    RT_POWER_SUPPLY_PROP_ENERGY_EMPTY,
    RT_POWER_SUPPLY_PROP_ENERGY_NOW,
    RT_POWER_SUPPLY_PROP_ENERGY_AVG,
    RT_POWER_SUPPLY_PROP_CAPACITY,
    RT_POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN,
    RT_POWER_SUPPLY_PROP_CAPACITY_ALERT_MAX,
    RT_POWER_SUPPLY_PROP_CAPACITY_ERROR_MARGIN,
    RT_POWER_SUPPLY_PROP_CAPACITY_LEVEL,
    RT_POWER_SUPPLY_PROP_TEMP,
    RT_POWER_SUPPLY_PROP_TEMP_MAX,
    RT_POWER_SUPPLY_PROP_TEMP_MIN,
    RT_POWER_SUPPLY_PROP_TEMP_ALERT_MIN,
    RT_POWER_SUPPLY_PROP_TEMP_ALERT_MAX,
    RT_POWER_SUPPLY_PROP_TEMP_AMBIENT,
    RT_POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MIN,
    RT_POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MAX,
    RT_POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
    RT_POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG,
    RT_POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
    RT_POWER_SUPPLY_PROP_TIME_TO_FULL_AVG,
    RT_POWER_SUPPLY_PROP_SCOPE,
    RT_POWER_SUPPLY_PROP_PRECHARGE_CURRENT,
    RT_POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT,
    RT_POWER_SUPPLY_PROP_CALIBRATE,
    RT_POWER_SUPPLY_PROP_MANUFACTURE_YEAR,
    RT_POWER_SUPPLY_PROP_MANUFACTURE_MONTH,
    RT_POWER_SUPPLY_PROP_MANUFACTURE_DAY,
    /* Properties of type `const char *' */
    RT_POWER_SUPPLY_PROP_MODEL_NAME,
    RT_POWER_SUPPLY_PROP_MANUFACTURER,
    RT_POWER_SUPPLY_PROP_SERIAL_NUMBER,
};

union rt_power_supply_property_val
{
    int intval;
    const char *strval;
};

struct rt_power_supply_battery_info
{
    enum rt_power_supply_technology technology;
    int energy_full_design_uwh;
    int charge_full_design_uah;
    int voltage_min_design_uv;
    int voltage_max_design_uv;
    int precharge_current_ua;
    int charge_term_current_ua;
    int charge_restart_voltage_uv;
    int constant_charge_current_max_ua;
    int constant_charge_voltage_max_uv;
    int temp_ambient_alert_min;
    int temp_ambient_alert_max;
    int temp_alert_min;
    int temp_alert_max;
    int temp_min;
    int temp_max;
};

struct rt_power_supply_ops;
struct rt_power_supply_notifier;

struct rt_power_supply
{
    rt_list_t list;

    struct rt_device *dev;

    enum rt_power_supply_type type;

    rt_size_t properties_nr;
    enum rt_power_supply_property *properties;
    struct rt_power_supply_battery_info *battery_info;

    const struct rt_power_supply_ops *ops;

    struct rt_ref ref;

#ifdef RT_USING_THERMAL
    struct rt_thermal_zone_device *thermal_dev;
#endif

#ifdef RT_USING_LED
    struct rt_led_device *led_dev;
#endif

    struct rt_work changed_work;
};

struct rt_power_supply_ops
{
    rt_err_t (*get_property)(struct rt_power_supply *psy,
            enum rt_power_supply_property prop, union rt_power_supply_property_val *val);
    rt_err_t (*set_property)(struct rt_power_supply *psy,
            enum rt_power_supply_property prop, const union rt_power_supply_property_val *val);
};

typedef rt_err_t (*rt_power_supply_notifier_callback)(struct rt_power_supply_notifier *notifier,
        struct rt_power_supply *psy);

struct rt_power_supply_notifier
{
    rt_list_t list;

    rt_power_supply_notifier_callback callback;
    void *priv;
};

rt_err_t rt_power_supply_register(struct rt_power_supply *psy);
rt_err_t rt_power_supply_unregister(struct rt_power_supply *psy);

rt_err_t rt_power_supply_notifier_register(struct rt_power_supply_notifier *notifier);
rt_err_t rt_power_supply_notifier_unregister(struct rt_power_supply_notifier *notifier);

rt_err_t rt_power_supply_get_property(struct rt_power_supply *psy,
        enum rt_power_supply_property prop,
        union rt_power_supply_property_val *val);
rt_err_t rt_power_supply_set_property(struct rt_power_supply *psy,
        enum rt_power_supply_property prop,
        const union rt_power_supply_property_val *val);

void rt_power_supply_changed(struct rt_power_supply *psy);

struct rt_power_supply *rt_power_supply_get(struct rt_device *dev, const char *id);
void rt_power_supply_put(struct rt_power_supply *psy);

#endif /* __POWER_SUPPLY_H__ */
