/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtdevice.h>

#define DBG_TAG "rtdm.power_supply"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifndef INT_MAX
#define INT_MAX (RT_UINT32_MAX >> 1)
#endif

#ifndef INT_MIN
#define INT_MIN (-INT_MAX - 1)
#endif

static RT_DEFINE_SPINLOCK(nodes_lock);
static rt_list_t power_supply_nodes = RT_LIST_OBJECT_INIT(power_supply_nodes);
static rt_list_t power_supply_notifier_nodes = RT_LIST_OBJECT_INIT(power_supply_notifier_nodes);

static rt_bool_t power_supply_have_property(struct rt_power_supply *psy,
        enum rt_power_supply_property prop);

#ifdef RT_USING_THERMAL
static rt_err_t power_supply_thermal_zone_get_temp(struct rt_thermal_zone_device *zdev,
        int *out_temp)
{
    rt_err_t err;
    union rt_power_supply_property_val val;
    struct rt_power_supply *psy = zdev->priv;

    if ((err = rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_TEMP, &val)))
    {
        return err;
    }

    *out_temp = val.intval;

    return RT_EOK;
}

const static struct rt_thermal_zone_ops power_supply_thermal_zone_ops =
{
    .get_temp = power_supply_thermal_zone_get_temp,
};

rt_err_t power_supply_thermal_register(struct rt_power_supply *psy)
{
    if (psy->thermal_dev)
    {
        return RT_EOK;
    }

    if (power_supply_have_property(psy, RT_POWER_SUPPLY_PROP_TEMP))
    {
        rt_err_t err;

        if (!(psy->thermal_dev = rt_calloc(1, sizeof(*psy->thermal_dev))))
        {
            return -RT_ENOMEM;
        }

        rt_dm_dev_set_name(&psy->thermal_dev->parent, rt_dm_dev_get_name(psy->dev));
        psy->thermal_dev->zone_id = 0;
        psy->thermal_dev->ops = &power_supply_thermal_zone_ops;
        psy->thermal_dev->parent.ofw_node = psy->dev->ofw_node;
        psy->thermal_dev->priv = psy;

        if ((err = rt_thermal_zone_device_register(psy->thermal_dev)))
        {
            rt_free(psy->thermal_dev);
            psy->thermal_dev = RT_NULL;

            return err;
        }
    }

    return RT_EOK;
}

rt_err_t power_supply_thermal_unregister(struct rt_power_supply *psy)
{
    rt_err_t err = RT_EOK;

    if (psy->thermal_dev)
    {
        if (!(err = rt_thermal_zone_device_unregister(psy->thermal_dev)))
        {
            rt_free(psy->thermal_dev);
            psy->thermal_dev = RT_NULL;
        }
    }

    return err;
}
#else
rt_err_t power_supply_thermal_register(struct rt_power_supply *psy)
{
    return RT_EOK;
}

rt_err_t power_supply_thermal_unregister(struct rt_power_supply *psy)
{
    return RT_EOK;
}
#endif /* RT_USING_THERMAL */

#ifdef RT_USING_LED
static void power_supply_update_battery_led(struct rt_power_supply *psy)
{
    union rt_power_supply_property_val status;

    if (rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_STATUS, &status))
    {
        return;
    }

    switch (status.intval)
    {
    case RT_POWER_SUPPLY_STATUS_FULL:
        rt_led_set_state(psy->led_dev, RT_LED_S_ON);
        rt_led_set_brightness(psy->led_dev, 255);
        break;

    case RT_POWER_SUPPLY_STATUS_CHARGING:
        rt_led_set_state(psy->led_dev, RT_LED_S_ON);
        rt_led_set_brightness(psy->led_dev, 255 >> 1);
        break;

    default:
        rt_led_set_state(psy->led_dev, RT_LED_S_OFF);
        break;
    }
}
static void power_supply_update_online_led(struct rt_power_supply *psy)
{
    union rt_power_supply_property_val online;

    if (rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_ONLINE, &online))
    {
        return;
    }

    if (online.intval)
    {
        rt_led_set_state(psy->led_dev, RT_LED_S_ON);
    }
    else
    {
        rt_led_set_state(psy->led_dev, RT_LED_S_OFF);
    }
}

static void power_supply_update_led(struct rt_power_supply *psy)
{
    if (!psy->led_dev)
    {
        return;
    }

    if (psy->type == RT_POWER_SUPPLY_TYPE_BATTERY)
    {
        power_supply_update_battery_led(psy);
    }
    else
    {
        power_supply_update_online_led(psy);
    }
}
#else
static void power_supply_update_led(struct rt_power_supply *psy)
{
}
#endif /* RT_USING_LED */

static void power_supply_changed_work(struct rt_work *work, void *work_data)
{
    struct rt_power_supply *psy = work_data;
    struct rt_power_supply_notifier *notifier, *next_notifier;

    power_supply_update_led(psy);

    rt_spin_lock(&nodes_lock);

    rt_list_for_each_entry_safe(notifier, next_notifier, &power_supply_notifier_nodes, list)
    {
        rt_spin_unlock(&nodes_lock);

        notifier->callback(notifier, psy);

        rt_spin_lock(&nodes_lock);
    }

    rt_spin_unlock(&nodes_lock);
}

rt_err_t rt_power_supply_register(struct rt_power_supply *psy)
{
    rt_err_t err;

    if (!psy || !psy->dev)
    {
        return -RT_EINVAL;
    }

    if (!psy->battery_info && (!psy->properties_nr || !psy->properties || !psy->ops))
    {
        return -RT_EINVAL;
    }

    if ((err = power_supply_thermal_register(psy)))
    {
        return err;
    }

    rt_ref_init(&psy->ref);
    rt_list_init(&psy->list);
    rt_work_init(&psy->changed_work, power_supply_changed_work, psy);

    rt_spin_lock(&nodes_lock);
    rt_list_insert_before(&power_supply_nodes, &psy->list);
    rt_spin_unlock(&nodes_lock);

    if (psy->dev->ofw_node)
    {
        rt_dm_dev_bind_fwdata(psy->dev, RT_NULL, psy);
    }

    return RT_EOK;
}

rt_err_t rt_power_supply_unregister(struct rt_power_supply *psy)
{
    rt_err_t err;

    if (!psy)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&nodes_lock);

    if (rt_ref_read(&psy->ref) > 1)
    {
        err = -RT_EBUSY;
        goto _unlock;
    }

    rt_list_remove(&psy->list);

    if (psy->dev->ofw_node)
    {
        rt_dm_dev_unbind_fwdata(psy->dev, RT_NULL);
    }

_unlock:
    rt_spin_unlock(&nodes_lock);

    if (!err)
    {
        rt_work_cancel(&psy->changed_work);

        err = power_supply_thermal_unregister(psy);
    }

    return err;
}

rt_err_t rt_power_supply_notifier_register(struct rt_power_supply_notifier *notifier)
{
    if (!notifier || !notifier->callback)
    {
        return -RT_EINVAL;
    }

    rt_list_init(&notifier->list);

    rt_spin_lock(&nodes_lock);
    rt_list_insert_before(&power_supply_notifier_nodes, &notifier->list);
    rt_spin_unlock(&nodes_lock);

    return RT_EOK;
}

rt_err_t rt_power_supply_notifier_unregister(struct rt_power_supply_notifier *notifier)
{
    if (!notifier)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&nodes_lock);
    rt_list_remove(&notifier->list);
    rt_spin_unlock(&nodes_lock);

    return RT_EOK;
}

static rt_bool_t power_supply_have_property(struct rt_power_supply *psy,
        enum rt_power_supply_property prop)
{
    if (!psy->ops->get_property)
    {
        return RT_FALSE;
    }

    for (int i = 0; i < psy->properties_nr; ++i)
    {
        if (psy->properties[i] == prop)
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static rt_bool_t power_supply_battery_info_have_property(
        struct rt_power_supply_battery_info *info, enum rt_power_supply_property prop)
{
    if (!info)
    {
        return RT_FALSE;
    }

    switch (prop)
    {
    case RT_POWER_SUPPLY_PROP_TECHNOLOGY:
        return info->technology != RT_POWER_SUPPLY_TECHNOLOGY_UNKNOWN;

    case RT_POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
        return info->energy_full_design_uwh >= 0;

    case RT_POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
        return info->charge_full_design_uah >= 0;

    case RT_POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
        return info->voltage_min_design_uv >= 0;

    case RT_POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
        return info->voltage_max_design_uv >= 0;

    case RT_POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
        return info->precharge_current_ua >= 0;

    case RT_POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
        return info->charge_term_current_ua >= 0;

    case RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
        return info->constant_charge_current_max_ua >= 0;

    case RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
        return info->constant_charge_voltage_max_uv >= 0;

    case RT_POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MIN:
        return info->temp_ambient_alert_min > INT_MIN;

    case RT_POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MAX:
        return info->temp_ambient_alert_max < INT_MAX;

    case RT_POWER_SUPPLY_PROP_TEMP_ALERT_MIN:
        return info->temp_alert_min > INT_MIN;

    case RT_POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
        return info->temp_alert_max < INT_MAX;

    case RT_POWER_SUPPLY_PROP_TEMP_MIN:
        return info->temp_min > INT_MIN;

    case RT_POWER_SUPPLY_PROP_TEMP_MAX:
        return info->temp_max < INT_MAX;

    default:
        return RT_FALSE;
    }
}

static rt_err_t power_supply_battery_info_get_property(
        struct rt_power_supply_battery_info *info, enum rt_power_supply_property prop,
        union rt_power_supply_property_val *val)
{
    switch (prop)
    {
    case RT_POWER_SUPPLY_PROP_TECHNOLOGY:
        val->intval = info->technology;
        break;

    case RT_POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
        val->intval = info->energy_full_design_uwh;
        break;

    case RT_POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
        val->intval = info->charge_full_design_uah;
        break;

    case RT_POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
        val->intval = info->voltage_min_design_uv;
        break;

    case RT_POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
        val->intval = info->voltage_max_design_uv;
        break;

    case RT_POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
        val->intval = info->precharge_current_ua;
        break;

    case RT_POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
        val->intval = info->charge_term_current_ua;
        break;

    case RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
        val->intval = info->constant_charge_current_max_ua;
        break;

    case RT_POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
        val->intval = info->constant_charge_voltage_max_uv;
        break;

    case RT_POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MIN:
        val->intval = info->temp_ambient_alert_min;
        break;

    case RT_POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MAX:
        val->intval = info->temp_ambient_alert_max;
        break;

    case RT_POWER_SUPPLY_PROP_TEMP_ALERT_MIN:
        val->intval = info->temp_alert_min;
        break;

    case RT_POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
        val->intval = info->temp_alert_max;
        break;

    case RT_POWER_SUPPLY_PROP_TEMP_MIN:
        val->intval = info->temp_min;
        break;

    case RT_POWER_SUPPLY_PROP_TEMP_MAX:
        val->intval = info->temp_max;
        break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

rt_err_t rt_power_supply_get_property(struct rt_power_supply *psy,
        enum rt_power_supply_property prop,
        union rt_power_supply_property_val *val)
{
    if (!psy || !val)
    {
        return -RT_EINVAL;
    }

    if (power_supply_have_property(psy, prop))
    {
        return psy->ops->get_property(psy, prop, val);
    }
    else if (power_supply_battery_info_have_property(psy->battery_info, prop))
    {
        return power_supply_battery_info_get_property(psy->battery_info, prop, val);
    }

    return -RT_ENOSYS;
}

rt_err_t rt_power_supply_set_property(struct rt_power_supply *psy,
        enum rt_power_supply_property prop,
        const union rt_power_supply_property_val *val)
{
    if (!psy || !val)
    {
        return -RT_EINVAL;
    }

    if (!psy->ops->set_property)
    {
        return -RT_ENOSYS;
    }

    return psy->ops->set_property(psy, prop, val);
}

void rt_power_supply_changed(struct rt_power_supply *psy)
{
    RT_ASSERT(psy != RT_NULL);

    rt_work_submit(&psy->changed_work, 0);
}

struct rt_power_supply *rt_power_supply_get(struct rt_device *dev, const char *id)
{
    struct rt_power_supply *psy = RT_NULL;

    if (!dev || !id)
    {
        return rt_err_ptr(-RT_EINVAL);
    }

#ifdef RT_USING_OFW
    if (dev->ofw_node)
    {
        struct rt_ofw_node *psy_np = rt_ofw_parse_phandle(dev->ofw_node, id, 0);

        if (!psy_np)
        {
            return psy;
        }

        psy = rt_ofw_data(psy_np);
    }
#endif /* RT_USING_OFW */

    if (!psy)
    {
        struct rt_power_supply *psy_target, *psy_next;

        rt_spin_lock(&nodes_lock);

        rt_list_for_each_entry_safe(psy_target, psy_next, &power_supply_nodes, list)
        {
            if (!rt_strcmp(psy_target->dev->parent.name, id))
            {
                psy = psy_target;
                break;
            }
        }

        rt_spin_unlock(&nodes_lock);
    }

    return psy;
}

static void power_supply_release(struct rt_ref *r)
{
    struct rt_power_supply *psy = rt_container_of(r, struct rt_power_supply, ref);

    rt_power_supply_unregister(psy);
}

void rt_power_supply_put(struct rt_power_supply *psy)
{
    if (!psy)
    {
        return;
    }

    rt_ref_put(&psy->ref, power_supply_release);
}

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

static int list_power_supply(int argc, char**argv)
{
    struct rt_power_supply *psy, *psy_next;
    union rt_power_supply_property_val propval = {};

    rt_spin_lock(&nodes_lock);

    rt_list_for_each_entry_safe(psy, psy_next, &power_supply_nodes, list)
    {
        rt_spin_unlock(&nodes_lock);

        rt_kprintf("%s %s\n", rt_dm_dev_get_name(psy->dev), type_str[psy->type]);

        rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_STATUS, &propval);
        rt_kprintf("status: %s\n", status_str[propval.intval]), propval.intval = 0;

        rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_CHARGE_TYPE, &propval);
        rt_kprintf("charge type: %s\n", charge_type_str[propval.intval]), propval.intval = 0;

        rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_HEALTH, &propval);
        rt_kprintf("health: %s\n", health_str[propval.intval]), propval.intval = 0;

        if (psy->battery_info)
        {
            struct rt_power_supply_battery_info *info = psy->battery_info;

            rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_CAPACITY, &propval);
            rt_kprintf("capacity:                       %d%%\n", propval.intval), propval.intval = 0;

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

        rt_kputs("\n");

        rt_spin_lock(&nodes_lock);
    }

    rt_spin_unlock(&nodes_lock);

    return 0;
}
MSH_CMD_EXPORT(list_power_supply, dump all of power supply information);
#endif /* RT_USING_CONSOLE && RT_USING_MSH */
