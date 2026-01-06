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

#define DBG_TAG "power_supply.daemon"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_PM
static rt_bool_t low_power_mode = RT_FALSE;
static rt_uint8_t raw_pm_run_mode = PM_RUN_MODE_MAX;
static rt_uint8_t raw_pm_sleep_mode = PM_RUN_MODE_MAX;
static rt_uint8_t last_pm_sleep_mode;
#endif

static rt_err_t daemon_power_supply_notify(struct rt_power_supply_notifier *notifier,
        struct rt_power_supply *psy)
{
    union rt_power_supply_property_val propval;
    rt_uint32_t voltage_now, voltage_min, voltage_max;

    if (!rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_CAPACITY, &propval))
    {
        goto _capacity_check;
    }

    if (rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_VOLTAGE_NOW, &propval))
    {
        return -RT_ENOSYS;
    }
    voltage_now = propval.intval / 1000000;

    if (rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_VOLTAGE_MIN, &propval))
    {
        return -RT_ENOSYS;
    }
    voltage_min = propval.intval / 1000000;

    if (rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_VOLTAGE_MAX, &propval))
    {
        return -RT_ENOSYS;
    }
    voltage_max = propval.intval / 1000000;

    propval.intval = (voltage_now - voltage_min) * 100 / (voltage_max - voltage_min);

_capacity_check:
    if (propval.intval >= 80)
    {
        rt_bool_t full_power = propval.intval == 100;

        if (rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_STATUS, &propval))
        {
            return -RT_ENOSYS;
        }

        if (propval.intval == RT_POWER_SUPPLY_STATUS_CHARGING)
        {
            if (full_power)
            {
                LOG_I("%s: Power is full", rt_dm_dev_get_name(psy->dev));
            }
            else
            {
                LOG_I("%s: Power is sufficient", rt_dm_dev_get_name(psy->dev));
            }
        }
    }
    else if (propval.intval <= 20)
    {
    #ifdef RT_USING_PM
        rt_uint8_t pm_sleep_mode;
        struct rt_pm *pm = rt_pm_get_handle();

        RT_ASSERT(pm != RT_NULL);

        low_power_mode = RT_TRUE;

        if (raw_pm_run_mode == PM_RUN_MODE_MAX)
        {
            raw_pm_run_mode = pm->run_mode;
        }
        if (raw_pm_sleep_mode == PM_SLEEP_MODE_MAX)
        {
            last_pm_sleep_mode = raw_pm_sleep_mode = pm->sleep_mode;
        }
        pm_sleep_mode = pm->sleep_mode;
    #endif /* RT_USING_PM */

        if (propval.intval <= 5)
        {
            do {
            #ifdef RT_USING_PM
                if (pm_sleep_mode != PM_SLEEP_MODE_SHUTDOWN && propval.intval > 1)
                {
                    pm_sleep_mode = PM_SLEEP_MODE_SHUTDOWN;
                    break;
                }
            #endif

                if (!rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_SCOPE, &propval) &&
                    propval.intval == RT_POWER_SUPPLY_SCOPE_SYSTEM)
                {
                    LOG_E("%s: Power is critical, poweroff now", rt_dm_dev_get_name(psy->dev));
                    rt_hw_cpu_shutdown();
                }
            } while (0);

            LOG_E("%s: Power is critical", rt_dm_dev_get_name(psy->dev));
        }
        else if (propval.intval <= 10)
        {
        #ifdef RT_USING_PM
            pm_sleep_mode = PM_SLEEP_MODE_STANDBY;
            rt_pm_run_enter(PM_RUN_MODE_LOW_SPEED);
        #endif
        }
        else if (propval.intval <= 15)
        {
        #ifdef RT_USING_PM
            pm_sleep_mode = PM_SLEEP_MODE_DEEP;
            rt_pm_run_enter(PM_RUN_MODE_MEDIUM_SPEED);
        #endif
        }
        else if (propval.intval <= 20)
        {
        #ifdef RT_USING_PM
            pm_sleep_mode = PM_SLEEP_MODE_LIGHT;
            rt_pm_run_enter(PM_RUN_MODE_NORMAL_SPEED);
        #endif
            LOG_W("%s: Power is low", rt_dm_dev_get_name(psy->dev));
        }

    #ifdef RT_USING_PM
        if (pm_sleep_mode != last_pm_sleep_mode)
        {
            rt_pm_release(last_pm_sleep_mode);
            rt_pm_request(pm_sleep_mode);

            last_pm_sleep_mode = pm_sleep_mode;
        }
    #endif /* RT_USING_PM */
    }
    else
    {
    #ifdef RT_USING_PM
        if (low_power_mode)
        {
            rt_pm_release(last_pm_sleep_mode);
            rt_pm_request(raw_pm_sleep_mode);

            rt_pm_run_enter(raw_pm_run_mode);

            low_power_mode = RT_FALSE;
        }
    #endif /* RT_USING_PM */
    }

    return RT_EOK;
}

static int power_supply_daemon_init(void)
{
    static struct rt_power_supply_notifier daemon_notifier;

    daemon_notifier.callback = daemon_power_supply_notify;
    rt_power_supply_notifier_register(&daemon_notifier);

    return 0;
}
INIT_ENV_EXPORT(power_supply_daemon_init);
