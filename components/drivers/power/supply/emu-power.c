/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/misc.h>

#define POLL_INTERVAL_MS        3000
#define CHARGE_STEP_FAST        4
#define CHARGE_STEP_NORMAL      2
#define CHARGE_STEP_TRICKLE     1
#define DISCHARGE_BASE_RATE     1
#define TEMP_SENSITIVITY        30

struct emu_power
{
    struct rt_device parent;

    struct rt_power_supply battery;
    struct rt_power_supply charger;

    struct rt_timer poller;

    rt_uint32_t status;
    rt_uint32_t health;
    rt_uint32_t present;
    rt_uint32_t capacity;
    rt_uint32_t voltage;
    rt_uint32_t temp;
    rt_uint32_t charge_counter;
    rt_uint32_t current_now;
    rt_uint32_t current_avg;
    rt_uint32_t charge_full_uah;
    rt_uint32_t cycle_count;
    rt_uint32_t ac_online;
    rt_uint32_t voltage_max;
    rt_uint32_t current_max;

    rt_tick_t last_poll_tick;

    rt_uint8_t load_index;
    rt_ubase_t cpu_load;
    rt_ubase_t load_history[5];
    rt_ubase_t last_idle;
    rt_ubase_t last_total;
};
static struct emu_power _emu_power;

static enum rt_power_supply_property emu_battery_properties[] =
{
    RT_POWER_SUPPLY_PROP_STATUS,
    RT_POWER_SUPPLY_PROP_HEALTH,
    RT_POWER_SUPPLY_PROP_PRESENT,
    RT_POWER_SUPPLY_PROP_TECHNOLOGY,
    RT_POWER_SUPPLY_PROP_CAPACITY,
    RT_POWER_SUPPLY_PROP_VOLTAGE_NOW,
    RT_POWER_SUPPLY_PROP_TEMP,
    RT_POWER_SUPPLY_PROP_CHARGE_COUNTER,
    RT_POWER_SUPPLY_PROP_CURRENT_NOW,
    RT_POWER_SUPPLY_PROP_CURRENT_AVG,
    RT_POWER_SUPPLY_PROP_CHARGE_FULL,
    RT_POWER_SUPPLY_PROP_CYCLE_COUNT,
    RT_POWER_SUPPLY_PROP_SCOPE,
};

static struct rt_power_supply_battery_info emu_battery_info =
{
    .technology = RT_POWER_SUPPLY_TECHNOLOGY_LION,
    .energy_full_design_uwh = 3000000000,       /* 3000mWh */
    .charge_full_design_uah = 3000000,          /* 3000mAh */
    .voltage_min_design_uv = 3000000,           /* 3.0V */
    .voltage_max_design_uv = 4200000,           /* 4.2V */
    .precharge_current_ua = 500000,             /* 500mA */
    .charge_term_current_ua = 1000000,          /* 1000mA */
    .charge_restart_voltage_uv = 3500000,       /* 3.5V */
    .constant_charge_current_max_ua = 2000000,  /* 2000mA */
    .constant_charge_voltage_max_uv = 4200000,  /* 4.2V */
    .temp_ambient_alert_min = -10000,           /* -10C */
    .temp_ambient_alert_max = 40000,            /* 40C */
    .temp_alert_min = 20000,                    /* 20C */
    .temp_alert_max = 25000,                    /* 25C */
    .temp_min = 0,                              /* 0C */
    .temp_max = 35000,                          /* 35C */
};

static rt_err_t emu_battery_get_property(struct rt_power_supply *psy,
        enum rt_power_supply_property prop, union rt_power_supply_property_val *val)
{
    struct emu_power *ep = rt_container_of(psy, struct emu_power, battery);

    switch (prop)
    {
    case RT_POWER_SUPPLY_PROP_STATUS:
        val->intval = ep->status;
        break;

    case RT_POWER_SUPPLY_PROP_HEALTH:
        val->intval = ep->health;
        break;

    case RT_POWER_SUPPLY_PROP_PRESENT:
        val->intval = ep->present;
        break;

    case RT_POWER_SUPPLY_PROP_TECHNOLOGY:
        val->intval = RT_POWER_SUPPLY_TECHNOLOGY_LION;
        break;

    case RT_POWER_SUPPLY_PROP_CAPACITY:
        val->intval = ep->capacity;
        break;

    case RT_POWER_SUPPLY_PROP_VOLTAGE_NOW:
        val->intval = ep->voltage;
        break;

    case RT_POWER_SUPPLY_PROP_TEMP:
        val->intval = ep->temp;
        break;

    case RT_POWER_SUPPLY_PROP_CHARGE_COUNTER:
        val->intval = ep->charge_counter;
        break;

    case RT_POWER_SUPPLY_PROP_CURRENT_NOW:
        val->intval = ep->current_now;
        break;

    case RT_POWER_SUPPLY_PROP_CURRENT_AVG:
        val->intval = ep->current_avg;
        break;

    case RT_POWER_SUPPLY_PROP_CHARGE_FULL:
        val->intval = ep->charge_full_uah;
        break;

    case RT_POWER_SUPPLY_PROP_CYCLE_COUNT:
        val->intval = ep->cycle_count;
        break;

    case RT_POWER_SUPPLY_PROP_SCOPE:
        val->intval = RT_POWER_SUPPLY_SCOPE_SYSTEM;
        break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static const struct rt_power_supply_ops emu_battery_ops =
{
    .get_property = emu_battery_get_property,
};

static enum rt_power_supply_property emu_charger_properties[] =
{
    RT_POWER_SUPPLY_PROP_ONLINE,
    RT_POWER_SUPPLY_PROP_VOLTAGE_MAX,
    RT_POWER_SUPPLY_PROP_CURRENT_MAX,
};

static rt_err_t emu_charger_get_property(struct rt_power_supply *psy,
        enum rt_power_supply_property prop, union rt_power_supply_property_val *val)
{
    struct emu_power *ep = rt_container_of(psy, struct emu_power, charger);

    switch (prop)
    {
    case RT_POWER_SUPPLY_PROP_ONLINE:
        val->intval = ep->ac_online;
        break;

    case RT_POWER_SUPPLY_PROP_VOLTAGE_MAX:
        val->intval = ep->voltage_max;
        break;

    case RT_POWER_SUPPLY_PROP_CURRENT_MAX:
        val->intval = ep->current_max;
        break;

    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static const struct rt_power_supply_ops emu_charger_ops =
{
    .get_property = emu_charger_get_property,
};

static void emu_power_poll(void *param)
{
    rt_tick_t current_tick;
    rt_uint32_t elapsed_ms, avg_load = 0;
    rt_ubase_t current_idle, current_total, idle_diff, total_diff;
    struct rt_cpu_usage_stats *stats = &rt_cpu_self()->cpu_stat;
    struct emu_power *ep = param;

    current_tick = rt_tick_get();
    elapsed_ms = (current_tick - ep->last_poll_tick) * (1000 / RT_TICK_PER_SECOND);
    ep->last_poll_tick = current_tick;

    current_idle = stats->idle;
    current_total = stats->user + stats->system + stats->irq + current_idle;

    idle_diff = current_idle - ep->last_idle;
    total_diff = current_total - ep->last_total;

    ep->last_idle = current_idle;
    ep->last_total = current_total;

    if (total_diff > 0)
    {
        ep->cpu_load = 100 - (idle_diff * 100) / total_diff;
    }
    else
    {
        ep->cpu_load = 0;
    }
    ep->cpu_load = rt_clamp((rt_ubase_t)ep->cpu_load, 0UL, 100UL);

    ep->load_history[ep->load_index++ % RT_ARRAY_SIZE(ep->load_history)] = ep->cpu_load;

    for (int i = 0; i < RT_ARRAY_SIZE(ep->load_history); i++)
    {
        avg_load += ep->load_history[i];
    }
    avg_load /= RT_ARRAY_SIZE(ep->load_history);

    if (ep->ac_online)
    {
        int step;

        if (ep->capacity < 80)
        {
            step = CHARGE_STEP_FAST;
            ep->current_now = 2000000;
        }
        else if (ep->capacity < 95)
        {
            step = CHARGE_STEP_NORMAL;
            ep->current_now = 1000000;
        }
        else
        {
            step = CHARGE_STEP_TRICKLE;
            ep->current_now = 500000;
        }

        ep->capacity = rt_min_t(rt_uint32_t,
                ep->capacity + (step * elapsed_ms) / POLL_INTERVAL_MS, 100);

        ep->voltage = emu_battery_info.voltage_max_design_uv - (100 - ep->capacity) * 30;

        if (ep->capacity >= 100)
        {
            ep->status = RT_POWER_SUPPLY_STATUS_FULL;
        }
        else
        {
            ep->status = RT_POWER_SUPPLY_STATUS_CHARGING;
        }
    }
    else
    {
        int drain = (avg_load * DISCHARGE_BASE_RATE * elapsed_ms) / 1000;

        ep->capacity = rt_max_t(rt_uint32_t, ep->capacity - drain, 0);
        ep->current_now = -(500000 + (avg_load * 5000));
        ep->voltage = emu_battery_info.voltage_min_design_uv + ep->capacity * 1200;

        ep->status = (ep->capacity > 0) ?
                RT_POWER_SUPPLY_STATUS_DISCHARGING : RT_POWER_SUPPLY_STATUS_NOT_CHARGING;
    }

    ep->temp = 25000 + (ep->current_now / 1000) * TEMP_SENSITIVITY;
    ep->temp = rt_clamp((rt_uint32_t)ep->temp,
            (rt_uint32_t)emu_battery_info.temp_min, (rt_uint32_t)emu_battery_info.temp_max);

    rt_power_supply_changed(&ep->charger);
    rt_power_supply_changed(&ep->battery);
}

static int emu_power_init(void)
{
    struct rt_cpu_usage_stats *stats = &rt_cpu_self()->cpu_stat;
    struct emu_power *ep = &_emu_power;

    rt_memset(ep, 0, sizeof(*ep));

    rt_dm_dev_set_name(&ep->parent, "emu-power");

    ep->battery.dev = &ep->parent,
    ep->battery.type = RT_POWER_SUPPLY_TYPE_BATTERY,
    ep->battery.properties_nr = RT_ARRAY_SIZE(emu_battery_properties),
    ep->battery.properties = emu_battery_properties,
    ep->battery.battery_info = &emu_battery_info,
    ep->battery.ops = &emu_battery_ops,

    ep->charger.dev = &ep->parent,
    ep->charger.type = RT_POWER_SUPPLY_TYPE_USB_SDP,
    ep->charger.properties_nr = RT_ARRAY_SIZE(emu_charger_properties),
    ep->charger.properties = emu_charger_properties,
    ep->charger.ops = &emu_charger_ops,

    ep->status = RT_POWER_SUPPLY_STATUS_DISCHARGING;
    ep->health = RT_POWER_SUPPLY_HEALTH_GOOD;
    ep->present = 1;
    ep->capacity = 100;
    ep->voltage = 3800000;
    ep->voltage_max = emu_battery_info.voltage_max_design_uv;
    ep->current_max = emu_battery_info.constant_charge_current_max_ua;
    ep->temp = 25000;
    ep->last_poll_tick = rt_tick_get();
    ep->last_idle = stats->idle;
    ep->last_total = stats->user + stats->system + stats->irq + stats->idle;

    rt_power_supply_register(&ep->battery);
    rt_power_supply_register(&ep->charger);

    rt_timer_init(&ep->poller, ep->parent.parent.name, &emu_power_poll, ep,
            rt_tick_from_millisecond(POLL_INTERVAL_MS), RT_TIMER_FLAG_PERIODIC);
    rt_timer_start(&ep->poller);

    return 0;
}
INIT_DEVICE_EXPORT(emu_power_init);

static int emu_charger(int argc, char**argv)
{
    rt_base_t level;
    struct emu_power *ep = &_emu_power;

    if (argc != 2)
    {
        goto _help;
    }

    level = rt_hw_interrupt_disable();

    if (!rt_strcmp(argv[1], "on"))
    {
        ep->status = RT_POWER_SUPPLY_STATUS_CHARGING;
        ep->ac_online = 1;
        ep->current_max = emu_battery_info.constant_charge_current_max_ua;
    }
    else if (!rt_strcmp(argv[1], "off"))
    {
        ep->status = RT_POWER_SUPPLY_STATUS_DISCHARGING;
        ep->ac_online = 0;
        ep->current_max = 0;
    }
    else
    {
        rt_hw_interrupt_enable(level);
        goto _help;
    }

    rt_hw_interrupt_enable(level);

    return 0;

_help:
    rt_kprintf("Usage: %s [on|off]\n", __func__);

    return -1;
}
MSH_CMD_EXPORT(emu_charger, emu charger switch);
