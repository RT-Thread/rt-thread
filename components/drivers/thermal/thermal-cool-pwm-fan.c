/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "thermal.cool.pwm-fan"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define MAX_PWM 255

struct pwm_fan_cool
{
    struct rt_thermal_cooling_device parent;

    rt_uint32_t pwm_fan_level;
    rt_uint32_t pwm_fan_max_level;
    rt_uint32_t *pwm_fan_cooling_levels;

    struct rt_device_pwm *pwm_dev;
    struct rt_pwm_configuration pwm_conf;

    struct rt_regulator *supply;
    struct rt_spinlock lock;
};

#define raw_to_pwm_fan_cool(raw) rt_container_of(raw, struct pwm_fan_cool, parent)

static rt_err_t pwm_fan_power_on(struct pwm_fan_cool *pf_cool)
{
    rt_err_t err = RT_EOK;

    if ((err = rt_pwm_enable(pf_cool->pwm_dev, pf_cool->pwm_conf.channel)))
    {
        return err;
    }

    if (pf_cool->supply && (err = rt_regulator_enable(pf_cool->supply)))
    {
        rt_pwm_disable(pf_cool->pwm_dev, pf_cool->pwm_conf.channel);

        return err;
    }

    return err;
}

static rt_err_t pwm_fan_power_off(struct pwm_fan_cool *pf_cool)
{
    rt_err_t err = RT_EOK;

    if (pf_cool->supply && (err = rt_regulator_disable(pf_cool->supply)))
    {
        return err;
    }

    if ((err = rt_pwm_disable(pf_cool->pwm_dev, pf_cool->pwm_conf.channel)))
    {
        rt_regulator_enable(pf_cool->supply);

        return err;
    }

    return err;
}

static rt_err_t pwm_fan_cool_get_max_level(struct rt_thermal_cooling_device *cdev,
        rt_ubase_t *out_level)
{
    struct pwm_fan_cool *pf_cool = raw_to_pwm_fan_cool(cdev);

    *out_level = pf_cool->pwm_fan_max_level;

    return RT_EOK;
}

static rt_err_t pwm_fan_cool_get_cur_level(struct rt_thermal_cooling_device *cdev,
        rt_ubase_t *out_level)
{
    struct pwm_fan_cool *pf_cool = raw_to_pwm_fan_cool(cdev);

    *out_level = pf_cool->pwm_fan_level;

    return RT_EOK;
}

static rt_err_t pwm_fan_cool_set_cur_level(struct rt_thermal_cooling_device *cdev,
        rt_ubase_t level)
{
    rt_ubase_t pwm;
    rt_err_t err = RT_EOK;
    struct pwm_fan_cool *pf_cool = raw_to_pwm_fan_cool(cdev);

    if (pf_cool->pwm_fan_level == level)
    {
        return RT_EOK;
    }

    rt_spin_lock(&pf_cool->lock);

    if ((pwm = pf_cool->pwm_fan_cooling_levels[level]))
    {
        rt_ubase_t period;
        struct rt_pwm_configuration *pwm_conf = &pf_cool->pwm_conf;

        period = pwm_conf->period;
        pwm_conf->pulse = RT_DIV_ROUND_UP(pwm * (period - 1), MAX_PWM);

        err = rt_pwm_set(pf_cool->pwm_dev,
                pwm_conf->channel, pwm_conf->period, pwm_conf->pulse);

        if (!err && pf_cool->pwm_fan_level == 0)
        {
            err = pwm_fan_power_on(pf_cool);
        }
    }
    else if (pf_cool->pwm_fan_level > 0)
    {
        err = pwm_fan_power_off(pf_cool);
    }

    rt_spin_unlock(&pf_cool->lock);

    if (!err)
    {
        pf_cool->pwm_fan_level = level;
    }

    return RT_EOK;
}

const static struct rt_thermal_cooling_device_ops pwm_fan_cool_ops =
{
    .get_max_level = pwm_fan_cool_get_max_level,
    .get_cur_level = pwm_fan_cool_get_cur_level,
    .set_cur_level = pwm_fan_cool_set_cur_level,
};

static void pwm_fan_cool_free(struct pwm_fan_cool *pf_cool)
{
    if (!rt_is_err_or_null(pf_cool->supply))
    {
        rt_regulator_put(pf_cool->supply);
    }

    if (pf_cool->pwm_fan_cooling_levels)
    {
        rt_free(pf_cool->pwm_fan_cooling_levels);
    }

    rt_free(pf_cool);
}

static rt_err_t pwm_fan_cool_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    int levels_nr;
    struct rt_ofw_cell_args pwm_args;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *pwm_np;
    struct pwm_fan_cool *pf_cool = rt_calloc(1, sizeof(*pf_cool));

    if (!pf_cool)
    {
        return -RT_ENOMEM;
    }

    if (rt_ofw_parse_phandle_cells(np, "pwms", "#pwm-cells", 0, &pwm_args))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    pwm_np = pwm_args.data;

    if (!rt_ofw_data(pwm_np))
    {
        rt_platform_ofw_request(pwm_np);
    }

    pf_cool->pwm_dev = rt_ofw_data(pwm_np);
    rt_ofw_node_put(pwm_np);

    if (!pf_cool->pwm_dev)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    pf_cool->pwm_conf.channel = pwm_args.args[0];
    pf_cool->pwm_conf.period = pwm_args.args[1];

    pf_cool->supply = rt_regulator_get(dev, "fan");

    if (rt_is_err(pf_cool->supply))
    {
        err = rt_ptr_err(pf_cool->supply);
        goto _fail;
    }

    if ((levels_nr = rt_dm_dev_prop_count_of_u32(dev, "cooling-levels")) <= 0)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    pf_cool->pwm_fan_cooling_levels = rt_calloc(levels_nr, sizeof(rt_uint32_t));

    if (!pf_cool->pwm_fan_cooling_levels)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    if (rt_dm_dev_prop_read_u32_array_index(dev, "cooling-levels",
        0, levels_nr, pf_cool->pwm_fan_cooling_levels) <= 0)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    pf_cool->pwm_fan_level = MAX_PWM;
    pf_cool->pwm_fan_max_level = levels_nr - 1;

    rt_spin_lock_init(&pf_cool->lock);
    pwm_fan_cool_set_cur_level(&pf_cool->parent, 0);

    rt_dm_dev_set_name(&pf_cool->parent.parent, "%s", rt_dm_dev_get_name(&pdev->parent));
    pf_cool->parent.parent.ofw_node = dev->ofw_node;
    pf_cool->parent.ops = &pwm_fan_cool_ops;

    if ((err = rt_thermal_cooling_device_register(&pf_cool->parent)))
    {
        goto _fail;
    }

    dev->user_data = pf_cool;

    return RT_EOK;

_fail:
    pwm_fan_cool_free(pf_cool);

    return err;
}

static rt_err_t pwm_fan_cool_remove(struct rt_platform_device *pdev)
{
    struct pwm_fan_cool *pf_cool = pdev->parent.ofw_node;

    rt_thermal_cooling_device_unregister(&pf_cool->parent);

    pwm_fan_power_off(pf_cool);
    pwm_fan_cool_free(pf_cool);

    return RT_EOK;
}

static rt_err_t pwm_fan_cool_shutdown(struct rt_platform_device *pdev)
{
    return pwm_fan_cool_remove(pdev);
}

static const struct rt_ofw_node_id pwm_fan_cool_ofw_ids[] =
{
    { .compatible = "pwm-fan" },
    { /* sentinel */ }
};

static struct rt_platform_driver pwm_fan_cool_driver =
{
    .name = "pwm-fan-cool",
    .ids = pwm_fan_cool_ofw_ids,

    .probe = pwm_fan_cool_probe,
    .remove = pwm_fan_cool_remove,
    .shutdown = pwm_fan_cool_shutdown,
};
RT_PLATFORM_DRIVER_EXPORT(pwm_fan_cool_driver);
