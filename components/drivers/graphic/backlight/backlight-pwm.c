/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "backlight.pwm"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct pwm_backlight
{
    struct rt_backlight_device parent;

    rt_uint32_t lth_brightness;
    rt_uint32_t *levels;

    rt_base_t enable_pin;
    rt_uint8_t active_val;

    rt_uint32_t scale;
    rt_uint32_t post_pwm_on_delay;
    rt_uint32_t pwm_off_delay;
    rt_uint32_t dft_brightness;
    rt_uint32_t max_brightness;

    rt_bool_t enabled;
    struct rt_device_pwm *pwm_dev;
    struct rt_pwm_configuration pwm_conf;

    struct rt_regulator *power_supply;
};

#define raw_to_pwm_backlight(raw) rt_container_of(raw, struct pwm_backlight, parent)

static void pwm_backlight_power_on(struct pwm_backlight *pbl)
{
    rt_err_t err;

    if (pbl->enabled)
    {
        return;
    }

    if (pbl->power_supply)
    {
        if ((err = rt_regulator_enable(pbl->power_supply)))
        {
            LOG_E("Enable power supply error = %s", rt_strerror(err));
        }
    }

    if (pbl->post_pwm_on_delay)
    {
        rt_thread_mdelay(pbl->post_pwm_on_delay);
    }

    if (pbl->enable_pin >= 0)
    {
        rt_pin_write(pbl->enable_pin, pbl->active_val);
    }

    pbl->enabled = RT_TRUE;
}

static void pwm_backlight_power_off(struct pwm_backlight *pbl)
{
    if (!pbl->enabled)
    {
        return;
    }

    if (pbl->enable_pin >= 0)
    {
        rt_pin_write(pbl->enable_pin, !pbl->active_val);
    }

    if (pbl->pwm_off_delay)
    {
        rt_thread_mdelay(pbl->pwm_off_delay);
    }

    if (pbl->power_supply)
    {
        rt_regulator_disable(pbl->power_supply);
    }

    pbl->enabled = RT_FALSE;
}

static int compute_duty_cycle(struct pwm_backlight *pbl, rt_uint32_t brightness,
        rt_uint32_t period)
{
    rt_uint64_t duty_cycle;
    rt_uint32_t lth = pbl->lth_brightness;

    if (pbl->levels)
    {
        duty_cycle = pbl->levels[brightness];
    }
    else
    {
        duty_cycle = brightness;
    }

    duty_cycle *= period - lth;
    rt_do_div(duty_cycle, pbl->scale);

    return duty_cycle + lth;
}

static rt_err_t pwm_backlight_update_status(struct rt_backlight_device *bl)
{
    rt_uint32_t brightness, duty_cycle;
    struct rt_pwm_configuration pwm_conf = {};
    struct pwm_backlight *pbl = raw_to_pwm_backlight(bl);

    rt_pwm_get(pbl->pwm_dev, &pwm_conf);
    brightness = rt_backlight_power_brightness(bl);

    if (brightness > 0)
    {
        duty_cycle = compute_duty_cycle(pbl, brightness, pwm_conf.period);
        pwm_conf.pulse = duty_cycle;
        rt_pwm_set(pbl->pwm_dev, pwm_conf.channel, pwm_conf.period, pwm_conf.pulse);

        rt_pwm_enable(pbl->pwm_dev, pbl->pwm_conf.channel);

        pwm_backlight_power_on(pbl);
    }
    else
    {
        pwm_backlight_power_off(pbl);

        pwm_conf.pulse = 0;
        rt_pwm_set(pbl->pwm_dev, pwm_conf.channel, pwm_conf.period, pwm_conf.pulse);

        if (pbl->power_supply || pbl->enable_pin >= 0)
        {
            rt_pwm_disable(pbl->pwm_dev, pbl->pwm_conf.channel);
        }
    }

    return RT_EOK;
}

static struct rt_backlight_ops pwm_backlight_ops =
{
    .update_status = pwm_backlight_update_status,
};

#define PWM_LUMINANCE_SHIFT 16
#define PWM_LUMINANCE_SCALE (1 << PWM_LUMINANCE_SHIFT) /* luminance scale */

rt_inline int period_fls(int period)
{
    return period ? sizeof(period) * 8 - __rt_clz(period) : 0;
}

static rt_err_t pwm_backlight_brightness_default(struct pwm_backlight *pbl,
        rt_uint32_t period)
{
    rt_uint32_t lightness;
    rt_uint64_t res, cie1931;

    pbl->max_brightness = rt_min((int)RT_DIV_ROUND_UP(period, period_fls(period)), 4096);

    pbl->levels = rt_calloc(pbl->max_brightness, sizeof(*pbl->levels));

    if (!pbl->levels)
    {
        return -RT_ENOMEM;
    }

    /* Fill the table using the cie1931 algorithm */
    for (int i = 0; i < pbl->max_brightness; ++i)
    {
        lightness = (i * PWM_LUMINANCE_SCALE) / pbl->max_brightness * 100;

        if (lightness <= (8 * PWM_LUMINANCE_SCALE))
        {
            cie1931 = RT_DIV_ROUND_CLOSEST(lightness * 10, 9033);
        }
        else
        {
            cie1931 = (lightness + (16 * PWM_LUMINANCE_SCALE)) / 116;
            cie1931 *= cie1931 * cie1931;
            cie1931 += 1ULL << (2 * PWM_LUMINANCE_SHIFT - 1);
            cie1931 >>= 2 * PWM_LUMINANCE_SHIFT;
        }

        res = cie1931 * period;
        res = RT_DIV_ROUND_CLOSEST_ULL(res, PWM_LUMINANCE_SCALE);

        if (res > RT_UINT32_MAX)
        {
            return -RT_EINVAL;
        }

        pbl->levels[i] = (rt_uint32_t)res;
    }

    pbl->dft_brightness = pbl->max_brightness / 2;
    pbl->max_brightness--;

    return 0;
}

static rt_err_t pwm_backlight_ofw_parse(struct pwm_backlight *pbl,
        struct rt_ofw_node *np)
{
    rt_err_t err;
    rt_ssize_t length;
    rt_uint32_t *table, value;
    rt_uint32_t num_levels, num_steps = 0;
    struct rt_ofw_prop *prop;

    /*
     * These values are optional and set as 0 by default, the out values
     * are modified only if a valid u32 value can be decoded.
     */
    rt_ofw_prop_read_u32(np, "post-pwm-on-delay-ms", &pbl->post_pwm_on_delay);
    rt_ofw_prop_read_u32(np, "pwm-off-delay-ms", &pbl->pwm_off_delay);

    /*
     * Determine the number of brightness levels, if this property is not
     * set a default table of brightness levels will be used.
     */
    prop = rt_ofw_get_prop(np, "brightness-levels", &length);

    if (!prop)
    {
        return RT_EOK;
    }

    num_levels = length / sizeof(rt_uint32_t);

    if (!num_levels)
    {
        return RT_EOK;
    }

    pbl->levels = rt_calloc(num_levels, sizeof(*pbl->levels));

    if (!pbl->levels)
    {
        return -RT_ENOMEM;
    }

    if ((err = rt_ofw_prop_read_u32_array_index(np, "brightness-levels",
            0, num_levels, pbl->levels)) < 0)
    {
        goto _fail;
    }

    if ((err = rt_ofw_prop_read_u32(np, "default-brightness-level", &value)))
    {
        goto _fail;
    }

    pbl->dft_brightness = value;

    /*
     * This property is optional, if is set enables linear
     * interpolation between each of the values of brightness levels
     * and creates a new pre-computed table.
     */
    rt_ofw_prop_read_u32(np, "num-interpolated-steps", &num_steps);

    /*
     * Make sure that there is at least two entries in the
     * brightness-levels table, otherwise we can't interpolate
     * between two points.
     */
    if (num_steps)
    {
        rt_int64_t dy;
        rt_uint32_t x1, x2, x, dx, y1, y2;
        rt_uint32_t num_input_levels = num_levels;

        if (num_input_levels < 2)
        {
            LOG_E("Can't interpolate");

            err = -RT_EINVAL;
            goto _fail;
        }

        num_levels = (num_input_levels - 1) * num_steps + 1;

        table = rt_calloc(num_levels, sizeof(*table));

        if (!table)
        {
            err = -RT_ENOMEM;
            goto _fail;
        }

        /*
         * Fill the interpolated table[x] = y
         * by draw lines between each (x1, y1) to (x2, y2).
         */
        dx = num_steps;

        for (int i = 0; i < num_input_levels - 1; ++i)
        {
            x1 = i * dx;
            x2 = x1 + dx;
            y1 = pbl->levels[i];
            y2 = pbl->levels[i + 1];
            dy = (rt_int64_t)y2 - y1;

            for (x = x1; x < x2; ++x)
            {
                table[x] = y1 + (rt_int64_t)(dy * (x - x1)) / (rt_int64_t)dx;
            }
        }

        /* Fill in the last point, since no line starts here. */
        table[x2] = y2;

        rt_free(pbl->levels);
        pbl->levels = table;
    }

    pbl->max_brightness = num_levels - 1;

    return RT_EOK;

_fail:
    rt_free(pbl->levels);

    return err;
}

static enum rt_backlight_power pwm_backlight_initial_power_state(
        struct pwm_backlight *pbl, struct rt_device *dev)
{
    rt_bool_t active = RT_TRUE;

    if (pbl->enable_pin >= 0 && rt_pin_read(pbl->enable_pin) != pbl->active_val)
    {
        active = RT_FALSE;
    }

    if (pbl->power_supply && !rt_regulator_is_enabled(pbl->power_supply))
    {
        active = RT_FALSE;
    }

    /* Synchronize the enable_gpio with the observed state of the hardware. */
    rt_pin_mode(pbl->enable_pin, PIN_MODE_OUTPUT);
    rt_pin_write(pbl->enable_pin, active ? pbl->active_val : !pbl->active_val);

    /* Not booted with device tree or no phandle link to the node */
    if (!dev->ofw_node || rt_dm_dev_prop_read_bool(dev, "phandle"))
    {
        return RT_BACKLIGHT_POWER_UNBLANK;
    }

    return active ? RT_BACKLIGHT_POWER_UNBLANK: RT_BACKLIGHT_POWER_POWERDOWN;
}

static rt_err_t pwm_backlight_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    enum rt_backlight_power power;
    struct rt_ofw_cell_args pwm_args;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *pwm_np;
    struct pwm_backlight *pbl = rt_calloc(1, sizeof(*pbl));

    if (!pbl)
    {
        return -RT_ENOMEM;
    }

    if ((err = pwm_backlight_ofw_parse(pbl, dev->ofw_node)))
    {
        goto _fail;
    }

    pbl->enable_pin = rt_pin_get_named_pin(dev, "enable", 0, RT_NULL, &pbl->active_val);

    if (pbl->enable_pin < 0 && pbl->enable_pin != PIN_NONE)
    {
        err = pbl->enable_pin;

        goto _fail;
    }

    pbl->power_supply = rt_regulator_get(dev, "power");

    if (rt_is_err(pbl->power_supply))
    {
        err = rt_ptr_err(pbl->power_supply);

        goto _fail;
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

    pbl->pwm_dev = rt_ofw_data(pwm_np);
    rt_ofw_node_put(pwm_np);

    if (!pbl->pwm_dev)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    pbl->pwm_conf.channel = pwm_args.args[0];
    pbl->pwm_conf.period = pwm_args.args[1];

    rt_pwm_set_period(pbl->pwm_dev, pbl->pwm_conf.channel, pbl->pwm_conf.period);

    if (pbl->levels)
    {
        for (int i = 0; i <= pbl->max_brightness; ++i)
        {
            if (pbl->levels[i] > pbl->scale)
            {
                pbl->scale = pbl->levels[i];
            }
        }
    }
    else if (!pbl->max_brightness)
    {
        struct rt_pwm_configuration pwm_conf = {};

        rt_pwm_get(pbl->pwm_dev, &pwm_conf);

        /* Make levels */
        if ((err = pwm_backlight_brightness_default(pbl, pbl->pwm_conf.period)))
        {
            LOG_E("Setup default brightness table error = %s", rt_strerror(err));

            goto _fail;
        }

        for (int i = 0; i <= pbl->max_brightness; ++i)
        {
            if (pbl->levels[i] > pbl->scale)
            {
                pbl->scale = pbl->levels[i];
            }
        }
    }
    else
    {
        pbl->scale = pbl->max_brightness;
    }

    pbl->parent.props.max_brightness = pbl->max_brightness;
    pbl->parent.ops = &pwm_backlight_ops;

    if ((err = rt_backlight_register(&pbl->parent)))
    {
        goto _fail;
    }

    power = pwm_backlight_initial_power_state(pbl, dev);
    rt_backlight_set_power(&pbl->parent, power);

    if (pbl->dft_brightness > pbl->max_brightness)
    {
        LOG_W("Invalid default brightness level: %u, using %u",
                pbl->dft_brightness, pbl->max_brightness);

        pbl->dft_brightness = pbl->max_brightness;
    }
    rt_backlight_set_brightness(&pbl->parent, pbl->dft_brightness);

    return RT_EOK;

_fail:
    if (!rt_is_err_or_null(pbl->power_supply))
    {
        rt_regulator_put(pbl->power_supply);
    }

    if (pbl->levels)
    {
        rt_free(pbl->levels);
    }

    rt_free(pbl);

    return err;
}

static rt_err_t pwm_backlight_remove(struct rt_platform_device *pdev)
{
    struct rt_pwm_configuration pwm_conf = {};
    struct pwm_backlight *pbl = pdev->parent.user_data;

    rt_backlight_unregister(&pbl->parent);

    pwm_backlight_power_off(pbl);

    rt_regulator_put(pbl->power_supply);

    rt_pwm_get(pbl->pwm_dev, &pwm_conf);
    pwm_conf.pulse = 0;

    rt_pwm_set(pbl->pwm_dev, pwm_conf.channel, pwm_conf.period, pwm_conf.pulse);
    rt_pwm_disable(pbl->pwm_dev, pbl->pwm_conf.channel);

    if (pbl->levels)
    {
        rt_free(pbl->levels);
    }

    rt_free(pbl);

    return RT_EOK;
}

static rt_err_t pwm_backlight_shutdown(struct rt_platform_device *pdev)
{
    struct rt_pwm_configuration pwm_conf = {};
    struct pwm_backlight *pbl = pdev->parent.user_data;

    pwm_backlight_power_off(pbl);

    rt_pwm_get(pbl->pwm_dev, &pwm_conf);
    pwm_conf.pulse = 0;

    rt_pwm_set(pbl->pwm_dev, pwm_conf.channel, pwm_conf.period, pwm_conf.pulse);
    rt_pwm_disable(pbl->pwm_dev, pbl->pwm_conf.channel);

    return RT_EOK;
}

static const struct rt_ofw_node_id pwm_backlight_ofw_ids[] =
{
    { .compatible = "pwm-backlight" },
    { /* sentinel */ }
};

static struct rt_platform_driver pwm_backlight_driver =
{
    .name = "pwm-backlight",
    .ids = pwm_backlight_ofw_ids,

    .probe = pwm_backlight_probe,
    .remove = pwm_backlight_remove,
    .shutdown = pwm_backlight_shutdown,
};
RT_PLATFORM_DRIVER_EXPORT(pwm_backlight_driver);
