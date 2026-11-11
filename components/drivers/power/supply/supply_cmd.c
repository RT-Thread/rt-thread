/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-03-27     Evlers       first version
 */

#include <rtdevice.h>

#if defined(RT_USING_CONSOLE) && defined(RT_USING_MSH)

const char * const type_str[] =
{
    [RT_POWER_SUPPLY_TYPE_UNKNOWN] = "UnKnown",
    [RT_POWER_SUPPLY_TYPE_BATTERY] = "Battery",
    [RT_POWER_SUPPLY_TYPE_UPS] = "UPS",
    [RT_POWER_SUPPLY_TYPE_MAINS] = "Mains",
    [RT_POWER_SUPPLY_TYPE_USB_SDP] = "USB SDP",
    [RT_POWER_SUPPLY_TYPE_USB_DCP] = "USB DCP",
    [RT_POWER_SUPPLY_TYPE_USB_CDP] = "USB CDP",
    [RT_POWER_SUPPLY_TYPE_USB_ACA] = "USB ACA",
    [RT_POWER_SUPPLY_TYPE_USB_TYPE_C] = "USB TypeC",
    [RT_POWER_SUPPLY_TYPE_USB_PD] = "USB PD",
    [RT_POWER_SUPPLY_TYPE_USB_PD_DRP] = "USB PD DRP",
    [RT_POWER_SUPPLY_TYPE_USB_PD_PPS] = "USB PD PPS",
    [RT_POWER_SUPPLY_TYPE_WIRELESS] = "Wireless",
};

const char * const status_str[] =
{
    [RT_POWER_SUPPLY_STATUS_UNKNOWN] = "UnKnown",
    [RT_POWER_SUPPLY_STATUS_CHARGING] = "Charging",
    [RT_POWER_SUPPLY_STATUS_DISCHARGING] = "Discharging",
    [RT_POWER_SUPPLY_STATUS_NOT_CHARGING] = "Not Charging",
    [RT_POWER_SUPPLY_STATUS_FULL] = "Full",
};

const char * const charge_type_str[] =
{
    [RT_POWER_SUPPLY_CHARGE_TYPE_UNKNOWN] = "Unknown",
    [RT_POWER_SUPPLY_CHARGE_TYPE_NONE] = "None",
    [RT_POWER_SUPPLY_CHARGE_TYPE_TRICKLE] = "Trickle",
    [RT_POWER_SUPPLY_CHARGE_TYPE_FAST] = "Fast",
    [RT_POWER_SUPPLY_CHARGE_TYPE_STANDARD] = "Standard",
    [RT_POWER_SUPPLY_CHARGE_TYPE_ADAPTIVE] = "Adaptive",
    [RT_POWER_SUPPLY_CHARGE_TYPE_CUSTOM] = "Custom",
    [RT_POWER_SUPPLY_CHARGE_TYPE_LONGLIFE] = "Longlife",
    [RT_POWER_SUPPLY_CHARGE_TYPE_BYPASS] = "Bypass",
};

const char * const health_str[] =
{
    [RT_POWER_SUPPLY_HEALTH_UNKNOWN] = "Unknown",
    [RT_POWER_SUPPLY_HEALTH_GOOD] = "Good",
    [RT_POWER_SUPPLY_HEALTH_OVERHEAT] = "Overheat",
    [RT_POWER_SUPPLY_HEALTH_DEAD] = "Dead",
    [RT_POWER_SUPPLY_HEALTH_OVERVOLTAGE] = "Overvoltage",
    [RT_POWER_SUPPLY_HEALTH_UNSPEC_FAILURE] = "Unspec Failure",
    [RT_POWER_SUPPLY_HEALTH_COLD] = "Cold",
    [RT_POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE] = "Watchdog Timer Expire",
    [RT_POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE] = "Safety Timer Expire",
    [RT_POWER_SUPPLY_HEALTH_OVERCURRENT] = "Overcurrent",
    [RT_POWER_SUPPLY_HEALTH_CALIBRATION_REQUIRED] = "Calibration Required",
    [RT_POWER_SUPPLY_HEALTH_WARM] = "Warm",
    [RT_POWER_SUPPLY_HEALTH_COOL] = "Cool",
    [RT_POWER_SUPPLY_HEALTH_HOT] = "Hot",
    [RT_POWER_SUPPLY_HEALTH_NO_BATTERY] = "No Battery",
};

const char * const tech_str[] =
{
    [RT_POWER_SUPPLY_TECHNOLOGY_UNKNOWN] = "UnKnown",
    [RT_POWER_SUPPLY_TECHNOLOGY_NiMH] = "NiMH",
    [RT_POWER_SUPPLY_TECHNOLOGY_LION] = "LION",
    [RT_POWER_SUPPLY_TECHNOLOGY_LIPO] = "LIPO",
    [RT_POWER_SUPPLY_TECHNOLOGY_LiFe] = "LiFe",
    [RT_POWER_SUPPLY_TECHNOLOGY_NiCd] = "NiCd",
    [RT_POWER_SUPPLY_TECHNOLOGY_LiMn] = "LiMn",
};

const char * const capacity_level_str[] =
{
    [RT_POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN] = "Unknown",
    [RT_POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL] = "Critical",
    [RT_POWER_SUPPLY_CAPACITY_LEVEL_LOW] = "Low",
    [RT_POWER_SUPPLY_CAPACITY_LEVEL_NORMAL] = "Normal",
    [RT_POWER_SUPPLY_CAPACITY_LEVEL_HIGH] = "High",
    [RT_POWER_SUPPLY_CAPACITY_LEVEL_FULL] = "Full",
};

const char * const scope_str[] =
{
    [RT_POWER_SUPPLY_SCOPE_UNKNOWN] = "Unknown",
    [RT_POWER_SUPPLY_SCOPE_SYSTEM] = "System",
    [RT_POWER_SUPPLY_SCOPE_DEVICE] = "Device",
};

enum power_supply_prop_dump_type
{
    POWER_SUPPLY_PROP_DUMP_INT = 0,
    POWER_SUPPLY_PROP_DUMP_ENUM,
    POWER_SUPPLY_PROP_DUMP_STR,
};

struct power_supply_prop_desc
{
    enum rt_power_supply_property prop;
    const char *name;
    const char *label;
    const char *unit;
    enum power_supply_prop_dump_type type;
    const char * const *str_tab;
    rt_size_t str_tab_size;
};

static const struct power_supply_prop_desc g_power_supply_prop_desc[] =
{
    {RT_POWER_SUPPLY_PROP_ONLINE,                      "online",                     "online:",                     RT_NULL, POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_PRESENT,                     "present",                    "present:",                    RT_NULL, POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_AUTHENTIC,                   "authentic",                  "authentic:",                  RT_NULL, POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_STATUS,                      "status",                     "status:",                     RT_NULL, POWER_SUPPLY_PROP_DUMP_ENUM, status_str, sizeof(status_str) / sizeof(status_str[0])},
    {RT_POWER_SUPPLY_PROP_CHARGE_TYPE,                 "charge_type",                "charge type:",                RT_NULL, POWER_SUPPLY_PROP_DUMP_ENUM, charge_type_str, sizeof(charge_type_str) / sizeof(charge_type_str[0])},
    {RT_POWER_SUPPLY_PROP_HEALTH,                      "health",                     "health:",                     RT_NULL, POWER_SUPPLY_PROP_DUMP_ENUM, health_str, sizeof(health_str) / sizeof(health_str[0])},
    {RT_POWER_SUPPLY_PROP_SCOPE,                       "scope",                      "scope:",                      RT_NULL, POWER_SUPPLY_PROP_DUMP_ENUM, scope_str, sizeof(scope_str) / sizeof(scope_str[0])},
    {RT_POWER_SUPPLY_PROP_CAPACITY,                    "capacity",                   "capacity:",                   "%",    POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_CAPACITY_LEVEL,              "capacity_level",             "capacity level:",             RT_NULL, POWER_SUPPLY_PROP_DUMP_ENUM, capacity_level_str, sizeof(capacity_level_str) / sizeof(capacity_level_str[0])},
    {RT_POWER_SUPPLY_PROP_VOLTAGE_NOW,                 "voltage_now",                "voltage now:",                "uV",   POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_VOLTAGE_AVG,                 "voltage_avg",                "voltage avg:",                "uV",   POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_CURRENT_NOW,                 "current_now",                "current now:",                "uA",   POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_CURRENT_AVG,                 "current_avg",                "current avg:",                "uA",   POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_POWER_NOW,                   "power_now",                  "power now:",                  "uW",   POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_POWER_AVG,                   "power_avg",                  "power avg:",                  "uW",   POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT,         "input_voltage_limit",        "input voltage limit:",        "uV",   POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,         "input_current_limit",        "input current limit:",        "uA",   POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_INPUT_POWER_LIMIT,           "input_power_limit",          "input power limit:",          "uW",   POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,     "constant_charge_voltage",    "constant charge voltage:",    "uV",   POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX, "constant_charge_voltage_max", "constant charge voltage max:", "uV",  POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,     "constant_charge_current",    "constant charge current:",    "uA",   POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX, "constant_charge_current_max", "constant charge current max:", "uA",  POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_TEMP,                        "temp",                       "temp:",                       "mC",   POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_TEMP_AMBIENT,                "temp_ambient",               "temp ambient:",               "mC",   POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,           "time_to_empty_now",          "time to empty now:",          "s",    POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,            "time_to_full_now",           "time to full now:",           "s",    POWER_SUPPLY_PROP_DUMP_INT,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_MODEL_NAME,                  "model_name",                 "model name:",                 RT_NULL, POWER_SUPPLY_PROP_DUMP_STR,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_MANUFACTURER,                "manufacturer",               "manufacturer:",               RT_NULL, POWER_SUPPLY_PROP_DUMP_STR,  RT_NULL, 0},
    {RT_POWER_SUPPLY_PROP_SERIAL_NUMBER,               "serial_number",              "serial number:",              RT_NULL, POWER_SUPPLY_PROP_DUMP_STR,  RT_NULL, 0},
};

#ifdef FINSH_USING_OPTION_COMPLETION
static struct msh_cmd_opt power_supply_msh_options[] =
{
    {0, RT_NULL, RT_NULL},
};
#endif

static const struct power_supply_prop_desc *power_supply_find_prop_desc(const char *name)
{
    rt_size_t i;

    if (!name)
    {
        return RT_NULL;
    }

    for (i = 0; i < sizeof(g_power_supply_prop_desc) / sizeof(g_power_supply_prop_desc[0]); ++i)
    {
        if (!rt_strcmp(g_power_supply_prop_desc[i].name, name))
        {
            return &g_power_supply_prop_desc[i];
        }
    }

    return RT_NULL;
}

static struct rt_power_supply *power_supply_find_by_name(const char *name)
{
    struct rt_power_supply **nodes;
    struct rt_power_supply *result = RT_NULL;
    rt_size_t count = 0;
    rt_size_t i;

    if (!name)
    {
        return RT_NULL;
    }

    nodes = rt_power_supply_snapshot(&count);
    if (!nodes)
    {
        return RT_NULL;
    }

    for (i = 0; i < count; ++i)
    {
        const char *dev_name = rt_power_supply_name(nodes[i]);

        if (!rt_strcmp(dev_name, name))
        {
            result = nodes[i];
            rt_ref_get(&result->ref);
            break;
        }
    }

    rt_power_supply_snapshot_free(nodes, count);
    return result;
}

static rt_err_t power_supply_dump_one_property(struct rt_power_supply *psy,
        const struct power_supply_prop_desc *desc,
        rt_bool_t print_unsupported)
{
    union rt_power_supply_property_val val = {};
    rt_err_t err;

    err = rt_power_supply_get_property(psy, desc->prop, &val);
    if (err != RT_EOK)
    {
        if (print_unsupported)
        {
            rt_kprintf("%-30s <unsupported>\n", desc->label);
        }
        return err;
    }

    if (desc->type == POWER_SUPPLY_PROP_DUMP_STR)
    {
        rt_kprintf("%-30s %s\n", desc->label, val.strval ? val.strval : "<null>");
        return RT_EOK;
    }

    if (desc->type == POWER_SUPPLY_PROP_DUMP_ENUM)
    {
        if ((val.intval >= 0) && ((rt_size_t)val.intval < desc->str_tab_size) && desc->str_tab[val.intval])
        {
            rt_kprintf("%-30s %s\n", desc->label, desc->str_tab[val.intval]);
        }
        else
        {
            rt_kprintf("%-30s %d\n", desc->label, val.intval);
        }
        return RT_EOK;
    }

    if (desc->unit)
    {
        rt_kprintf("%-30s %d %s\n", desc->label, val.intval, desc->unit);
    }
    else
    {
        rt_kprintf("%-30s %d\n", desc->label, val.intval);
    }

    return RT_EOK;
}

static void power_supply_dump_known_property_names(void)
{
    rt_size_t i;

    rt_kputs("Known properties:\n");

    for (i = 0; i < sizeof(g_power_supply_prop_desc) / sizeof(g_power_supply_prop_desc[0]); ++i)
    {
        rt_kprintf("  %s\n", g_power_supply_prop_desc[i].name);
    }
}

static void power_supply_dump_battery_info(struct rt_power_supply *psy)
{
    if (psy->battery_info)
    {
        struct rt_power_supply_battery_info *info = psy->battery_info;

        rt_kprintf("technology:                     %s\n", tech_str[info->technology]);
        rt_kprintf("energy full design:             %u uWh\n", info->energy_full_design_uwh);
        rt_kprintf("charge full design:             %u uAh\n", info->charge_full_design_uah);
        rt_kprintf("voltage design range:           %u~%u uV\n", info->voltage_min_design_uv, info->voltage_max_design_uv);
        rt_kprintf("precharge current:              %u uA\n", info->precharge_current_ua);
        rt_kprintf("charge term current:            %u uA\n", info->charge_term_current_ua);
        rt_kprintf("charge restart voltage:         %u uV\n", info->charge_restart_voltage_uv);
        rt_kprintf("constant charge current max:    %u uA\n", info->constant_charge_current_max_ua);
        rt_kprintf("constant charge voltage max:    %u uV\n", info->constant_charge_voltage_max_uv);
        rt_kprintf("temp ambient alert range:       %+d.%u~%+d.%u C\n",
                info->temp_ambient_alert_min / 1000, rt_abs(info->temp_ambient_alert_min) % 1000,
                info->temp_ambient_alert_max / 1000, rt_abs(info->temp_ambient_alert_max) % 1000);
        rt_kprintf("temp alert range:               %+d.%u~%+d.%u C\n",
                info->temp_alert_min / 1000, rt_abs(info->temp_alert_min) % 1000,
                info->temp_alert_max / 1000, rt_abs(info->temp_alert_max) % 1000);
        rt_kprintf("temp range:                     %+d.%u~%+d.%u C\n",
                info->temp_min / 1000, rt_abs(info->temp_min) % 1000,
                info->temp_max / 1000, rt_abs(info->temp_max) % 1000);
    }
}

static void power_supply_dump_properties(struct rt_power_supply *psy)
{
    rt_size_t i;

    for (i = 0; i < sizeof(g_power_supply_prop_desc) / sizeof(g_power_supply_prop_desc[0]); ++i)
    {
        power_supply_dump_one_property(psy, &g_power_supply_prop_desc[i], RT_FALSE);
    }
}

static int power_supply_do_list(void)
{
    struct rt_power_supply **nodes;
    rt_size_t count = 0;
    rt_size_t i;

    nodes = rt_power_supply_snapshot(&count);
    if (!nodes || !count)
    {
        return 0;
    }

    for (i = 0; i < count; ++i)
    {
        rt_kprintf("%s %s\n", rt_power_supply_name(nodes[i]), type_str[nodes[i]->type]);
        power_supply_dump_properties(nodes[i]);
        power_supply_dump_battery_info(nodes[i]);
    }

    rt_power_supply_snapshot_free(nodes, count);
    return 0;
}

static int power_supply_do_show(const char *name)
{
    struct rt_power_supply *psy = power_supply_find_by_name(name);

    if (!psy)
    {
        rt_kprintf("power_supply: device '%s' not found\n", name ? name : "<null>");
        return -RT_ERROR;
    }

    rt_kprintf("%s %s\n", rt_power_supply_name(psy), type_str[psy->type]);
    power_supply_dump_properties(psy);
    power_supply_dump_battery_info(psy);
    rt_power_supply_put(psy);
    return RT_EOK;
}

static int power_supply_do_get(const char *name, const char *prop_name)
{
    struct rt_power_supply *psy = power_supply_find_by_name(name);
    const struct power_supply_prop_desc *desc = power_supply_find_prop_desc(prop_name);
    int ret;

    if (!psy)
    {
        rt_kprintf("power_supply: device '%s' not found\n", name ? name : "<null>");
        return -RT_ERROR;
    }

    if (!desc)
    {
        rt_kprintf("power_supply: unknown property '%s'\n", prop_name ? prop_name : "<null>");
        power_supply_dump_known_property_names();
        rt_power_supply_put(psy);
        return -RT_EINVAL;
    }

    ret = power_supply_dump_one_property(psy, desc, RT_TRUE);
    rt_power_supply_put(psy);
    return ret;
}

static int power_supply(int argc, char **argv)
{
    if (argc == 2 && !rt_strcmp(argv[1], "list"))
    {
        return power_supply_do_list();
    }

    if (argc == 3 && !rt_strcmp(argv[1], "show"))
    {
        return power_supply_do_show(argv[2]);
    }

    if (argc == 4 && !rt_strcmp(argv[1], "get"))
    {
        return power_supply_do_get(argv[2], argv[3]);
    }

    rt_kputs("Usage:\n");
    rt_kputs("  power_supply list\n");
    rt_kputs("  power_supply show <name>\n");
    rt_kputs("  power_supply get <name> <property>\n");

    return RT_EOK;
}
MSH_CMD_EXPORT(power_supply, power supply helper use power_supply list);

#endif /* RT_USING_CONSOLE && RT_USING_MSH */
