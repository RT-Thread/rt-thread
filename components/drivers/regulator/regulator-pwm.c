/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#define DBG_TAG "regulator.pwm"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "regulator_dm.h"

struct pwm_continuous_reg_data
{
    rt_uint32_t min_uvolt_dutycycle;
    rt_uint32_t max_uvolt_dutycycle;
    rt_uint32_t dutycycle_unit;
};

struct pwm_voltages
{
    rt_uint32_t uvolt;
    rt_uint32_t dutycycle;
};

struct pwm_regulator
{
    struct rt_regulator_node  parent;
    struct rt_regulator_param param;

    rt_bool_t                      enabled;
    rt_uint8_t                     enable_active_value;
    struct rt_device_pwm          *pwm_dev;
    struct rt_pwm_configuration    pwm_conf;
    struct pwm_voltages           *duty_cycle_table;
    struct pwm_continuous_reg_data continuous;

    int         init_uvolt;
    int         selector;
    rt_uint32_t n_voltages;

    rt_base_t enable_pin;
};

#define raw_to_pwm_regulator(raw) rt_container_of(raw, struct pwm_regulator, parent)

static rt_uint8_t pwm_regulator_enable_pin_value(struct pwm_regulator *pr, rt_bool_t enable)
{
    return enable ? pr->enable_active_value : !pr->enable_active_value;
}

static rt_err_t pwm_regulator_get_config(struct pwm_regulator        *pr,
                                         struct rt_pwm_configuration *pwm_conf)
{
    rt_memset(pwm_conf, 0, sizeof(*pwm_conf));
    pwm_conf->channel = pr->pwm_conf.channel;

    return rt_pwm_get(pr->pwm_dev, pwm_conf);
}

static rt_err_t pwm_regulator_apply_config(struct pwm_regulator        *pr,
                                           struct rt_pwm_configuration *pwm_conf)
{
    rt_err_t err;

    if (!pwm_conf->period || pwm_conf->pulse > pwm_conf->period)
    {
        return -RT_EINVAL;
    }

    pwm_conf->channel = pr->pwm_conf.channel;

    /*
     * rt_pwm_set() only passes period and pulse, so use the complete
     * configuration to retain the polarity from the PWM DT specifier.
     */
    err = rt_device_control(&pr->pwm_dev->parent, PWM_CMD_SET, pwm_conf);

    if (!err)
    {
        pr->pwm_conf = *pwm_conf;
    }

    return err;
}

static rt_err_t pwm_regulator_adjust_config(struct pwm_regulator *pr)
{
    rt_err_t                    err;
    struct rt_pwm_configuration current;
    struct rt_pwm_configuration adjusted = pr->pwm_conf;

    if ((err = pwm_regulator_get_config(pr, &current)))
    {
        return err;
    }

    if (!current.period)
    {
        adjusted.pulse = 0;
    }
    else
    {
        if (current.pulse > current.period)
        {
            current.pulse = current.period;
        }

        adjusted.pulse = RT_DIV_ROUND_CLOSEST_ULL(
            (rt_uint64_t)current.pulse * adjusted.period,
            current.period);

        if (current.complementary != adjusted.complementary)
        {
            adjusted.pulse = adjusted.period - adjusted.pulse;
        }
    }

    return pwm_regulator_apply_config(pr, &adjusted);
}

static rt_err_t pwm_regulator_init_state(struct pwm_regulator *pr)
{
    rt_err_t                    err;
    rt_uint32_t                 dutycycle;
    struct rt_pwm_configuration pwm_conf;

    if ((err = pwm_regulator_get_config(pr, &pwm_conf)))
    {
        return err;
    }

    dutycycle = pwm_conf.period ? RT_DIV_ROUND_CLOSEST_ULL(
                                      (rt_uint64_t)pwm_conf.pulse * 100, pwm_conf.period)
                                : 0;

    for (int i = 0; i < pr->n_voltages; ++i)
    {
        if (dutycycle == pr->duty_cycle_table[i].dutycycle)
        {
            pr->selector = i;
            return RT_EOK;
        }
    }

    return -RT_EINVAL;
}

static rt_err_t pwm_regulator_enable(struct rt_regulator_node *reg_np)
{
    rt_err_t              err;
    struct pwm_regulator *pr = raw_to_pwm_regulator(reg_np);

    if (pr->init_uvolt)
    {
        struct rt_pwm_configuration pwm_conf;

        if ((err = pwm_regulator_get_config(pr, &pwm_conf)))
        {
            return err;
        }

        if (!pwm_conf.pulse &&
            (err = reg_np->ops->set_voltage(reg_np,
                                            pr->init_uvolt, pr->init_uvolt)))
        {
            return err;
        }
    }

    if (pr->enable_pin >= 0)
    {
        rt_pin_mode(pr->enable_pin, PIN_MODE_OUTPUT);
        rt_pin_write(pr->enable_pin, pwm_regulator_enable_pin_value(pr, RT_TRUE));
    }

    if (!(err = rt_pwm_enable(pr->pwm_dev, pr->pwm_conf.channel)))
    {
        pr->enabled = RT_TRUE;
    }
    else if (pr->enable_pin >= 0)
    {
        rt_pin_write(pr->enable_pin, pwm_regulator_enable_pin_value(pr, RT_FALSE));
    }

    return err;
}

static rt_err_t pwm_regulator_disable(struct rt_regulator_node *reg_np)
{
    rt_err_t              err;
    struct pwm_regulator *pr = raw_to_pwm_regulator(reg_np);

    if ((err = rt_pwm_disable(pr->pwm_dev, pr->pwm_conf.channel)))
    {
        return err;
    }

    pr->enabled = RT_FALSE;

    if (pr->enable_pin >= 0)
    {
        rt_pin_mode(pr->enable_pin, PIN_MODE_OUTPUT);
        rt_pin_write(pr->enable_pin, pwm_regulator_enable_pin_value(pr, RT_FALSE));
    }

    return RT_EOK;
}

static rt_bool_t pwm_regulator_is_enabled(struct rt_regulator_node *reg_np)
{
    struct pwm_regulator *pr = raw_to_pwm_regulator(reg_np);

    if (pr->enable_pin >= 0)
    {
        if (rt_pin_read(pr->enable_pin) != pr->enable_active_value)
        {
            return RT_FALSE;
        }
    }

    return pr->enabled;
}

static rt_err_t pwm_regulator_table_set_voltage(struct rt_regulator_node *reg_np,
                                                int min_uvolt, int max_uvolt)
{
    rt_err_t                    err;
    int                         selector = -1;
    rt_uint32_t                 duty_cycle;
    struct rt_pwm_configuration pwm_conf = {};
    struct pwm_regulator       *pr       = raw_to_pwm_regulator(reg_np);

    for (int i = 0; i < pr->n_voltages; ++i)
    {
        int uvolt = pr->duty_cycle_table[i].uvolt;

        if (uvolt >= min_uvolt && uvolt <= max_uvolt &&
            (selector < 0 || uvolt < pr->duty_cycle_table[selector].uvolt))
        {
            selector = i;
        }
    }

    if (selector < 0)
    {
        return -RT_EINVAL;
    }

    pwm_conf = pr->pwm_conf;

    duty_cycle = pr->duty_cycle_table[selector].dutycycle;
    duty_cycle = RT_DIV_ROUND_CLOSEST_ULL((rt_uint64_t)duty_cycle * pwm_conf.period, 100);

    pwm_conf.pulse = duty_cycle;

    if ((err = pwm_regulator_apply_config(pr, &pwm_conf)))
    {
        return err;
    }

    pr->selector = selector;

    return RT_EOK;
}

static int pwm_regulator_table_get_voltage(struct rt_regulator_node *reg_np)
{
    struct pwm_regulator *pr = raw_to_pwm_regulator(reg_np);

    if (pr->selector < 0)
    {
        if (pwm_regulator_init_state(pr))
        {
            return RT_REGULATOR_UVOLT_INVALID;
        }
    }

    return pr->duty_cycle_table[pr->selector].uvolt;
}

static rt_err_t pwm_regulator_continuous_set_voltage(struct rt_regulator_node *reg_np,
                                                     int min_uvolt, int max_uvolt)
{
    rt_err_t                    err;
    int                         target_uvolt;
    struct pwm_regulator       *pr             = raw_to_pwm_regulator(reg_np);
    struct rt_pwm_configuration pwm_conf       = pr->pwm_conf;
    rt_uint32_t                 min_uvolt_duty = pr->continuous.min_uvolt_dutycycle;
    rt_uint32_t                 max_uvolt_duty = pr->continuous.max_uvolt_dutycycle;
    rt_uint32_t                 duty_unit      = pr->continuous.dutycycle_unit, diff_duty, dutycycle;
    int                         fix_min_uvolt  = reg_np->param->min_uvolt;
    int                         fix_max_uvolt  = reg_np->param->max_uvolt;
    int                         diff_uvolt     = fix_max_uvolt - fix_min_uvolt;

    target_uvolt = min_uvolt < fix_min_uvolt ? fix_min_uvolt : min_uvolt;

    if (min_uvolt > max_uvolt || target_uvolt > max_uvolt ||
        target_uvolt > fix_max_uvolt || diff_uvolt <= 0)
    {
        return -RT_EINVAL;
    }

    if (max_uvolt_duty < min_uvolt_duty)
    {
        diff_duty = min_uvolt_duty - max_uvolt_duty;
    }
    else
    {
        diff_duty = max_uvolt_duty - min_uvolt_duty;
    }

    dutycycle = RT_DIV_ROUND_CLOSEST_ULL(
        (rt_uint64_t)(target_uvolt - fix_min_uvolt) * diff_duty, diff_uvolt);

    if (max_uvolt_duty < min_uvolt_duty)
    {
        dutycycle = min_uvolt_duty - dutycycle;
    }
    else
    {
        dutycycle = min_uvolt_duty + dutycycle;
    }

    pwm_conf.pulse = RT_DIV_ROUND_CLOSEST_ULL(
        (rt_uint64_t)dutycycle * pwm_conf.period, duty_unit);

    err = pwm_regulator_apply_config(pr, &pwm_conf);

    return err;
}

static int pwm_regulator_continuous_get_voltage(struct rt_regulator_node *reg_np)
{
    rt_err_t                    err;
    struct pwm_regulator       *pr = raw_to_pwm_regulator(reg_np);
    struct rt_pwm_configuration pwm_conf;
    rt_uint32_t                 min_uvolt_duty = pr->continuous.min_uvolt_dutycycle;
    rt_uint32_t                 max_uvolt_duty = pr->continuous.max_uvolt_dutycycle;
    rt_uint32_t                 duty_unit      = pr->continuous.dutycycle_unit, diff_duty;
    rt_uint32_t                 min_duty, max_duty;
    int                         min_uvolt = reg_np->param->min_uvolt;
    int                         max_uvolt = reg_np->param->max_uvolt;
    int                         uvolt, diff_uvolt = max_uvolt - min_uvolt;

    if ((err = pwm_regulator_get_config(pr, &pwm_conf)))
    {
        return err;
    }

    uvolt = pwm_conf.period ? RT_DIV_ROUND_CLOSEST_ULL(
                                  (rt_uint64_t)pwm_conf.pulse * duty_unit,
                                  pwm_conf.period)
                            : 0;

    min_duty = min_uvolt_duty < max_uvolt_duty ? min_uvolt_duty : max_uvolt_duty;
    max_duty = min_uvolt_duty > max_uvolt_duty ? min_uvolt_duty : max_uvolt_duty;

    if (uvolt < min_duty || uvolt > max_duty)
    {
        return RT_REGULATOR_UVOLT_INVALID;
    }

    if (max_uvolt_duty < min_uvolt_duty)
    {
        uvolt     = min_uvolt_duty - uvolt;
        diff_duty = min_uvolt_duty - max_uvolt_duty;
    }
    else
    {
        uvolt     = uvolt - min_uvolt_duty;
        diff_duty = max_uvolt_duty - min_uvolt_duty;
    }

    uvolt = RT_DIV_ROUND_CLOSEST_ULL((rt_uint64_t)uvolt * diff_uvolt, diff_duty);

    return uvolt + min_uvolt;
}

static const struct rt_regulator_ops pwm_regulator_voltage_table_ops = {
    .enable      = pwm_regulator_enable,
    .disable     = pwm_regulator_disable,
    .is_enabled  = pwm_regulator_is_enabled,
    .set_voltage = pwm_regulator_table_set_voltage,
    .get_voltage = pwm_regulator_table_get_voltage,
};

static const struct rt_regulator_ops pwm_regulator_voltage_continuous_ops = {
    .enable      = pwm_regulator_enable,
    .disable     = pwm_regulator_disable,
    .is_enabled  = pwm_regulator_is_enabled,
    .set_voltage = pwm_regulator_continuous_set_voltage,
    .get_voltage = pwm_regulator_continuous_get_voltage,
};

static rt_err_t pwm_regulator_init_table(struct rt_ofw_node   *np,
                                         struct pwm_regulator *pr)
{
    rt_err_t             err;
    rt_ssize_t           length = 0;
    struct pwm_voltages *duty_cycle_table;

    rt_ofw_prop_read_raw(np, "voltage-table", &length);

    if ((length < sizeof(*duty_cycle_table)) ||
        (length % sizeof(*duty_cycle_table)))
    {
        LOG_E("`voltage-table` length = %d is invalid", length);

        return -RT_EINVAL;
    }

    duty_cycle_table = rt_calloc(1, length);

    if (!duty_cycle_table)
    {
        return -RT_ENOMEM;
    }

    err = rt_ofw_prop_read_u32_array_index(np, "voltage-table",
                                           0, length / sizeof(rt_uint32_t), (rt_uint32_t *)duty_cycle_table);

    if (err < 0)
    {
        rt_free(duty_cycle_table);

        return err;
    }

    for (int i = 0; i < length / sizeof(*duty_cycle_table); ++i)
    {
        if (duty_cycle_table[i].dutycycle > 100)
        {
            rt_free(duty_cycle_table);

            return -RT_EINVAL;
        }
    }

    pr->duty_cycle_table = duty_cycle_table;
    pr->selector         = -1;
    pr->n_voltages       = length / sizeof(*duty_cycle_table);
    pr->parent.ops       = &pwm_regulator_voltage_table_ops;

    return RT_EOK;
}

static rt_err_t pwm_regulator_init_continuous(struct rt_ofw_node   *np,
                                              struct pwm_regulator *pr)
{
    rt_uint32_t dutycycle_unit = 100, dutycycle_range[2] = { 0, 100 };

    rt_ofw_prop_read_u32_array_index(np, "pwm-dutycycle-range", 0, 2,
                                     dutycycle_range);
    rt_ofw_prop_read_u32(np, "pwm-dutycycle-unit", &dutycycle_unit);

    if (!dutycycle_unit ||
        dutycycle_range[0] > dutycycle_unit ||
        dutycycle_range[1] > dutycycle_unit ||
        dutycycle_range[0] == dutycycle_range[1] ||
        pr->param.min_uvolt >= pr->param.max_uvolt)
    {
        return -RT_EINVAL;
    }

    pr->continuous.dutycycle_unit      = dutycycle_unit;
    pr->continuous.min_uvolt_dutycycle = dutycycle_range[0];
    pr->continuous.max_uvolt_dutycycle = dutycycle_range[1];

    pr->parent.ops = &pwm_regulator_voltage_continuous_ops;

    return RT_EOK;
}

static rt_err_t pwm_regulator_probe(struct rt_platform_device *pdev)
{
    rt_err_t                  err;
    struct rt_ofw_cell_args   pwm_args;
    struct rt_ofw_node       *np = pdev->parent.ofw_node, *pwm_np;
    struct pwm_regulator     *pr = rt_calloc(1, sizeof(*pr));
    struct rt_regulator_node *rgp;

    if (!pr)
    {
        return -RT_ENOMEM;
    }

    if ((err = regulator_ofw_parse(np, &pr->param)))
    {
        goto _fail;
    }

    if (rt_ofw_parse_phandle_cells(np, "pwms", "#pwm-cells", 0, &pwm_args))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if (pwm_args.args_count < 2 || !pwm_args.args[1])
    {
        rt_ofw_node_put(pwm_args.data);
        err = -RT_EINVAL;
        goto _fail;
    }

    pwm_np = pwm_args.data;

    if (!rt_ofw_data(pwm_np))
    {
        rt_platform_ofw_request(pwm_np);
    }

    pr->pwm_dev = rt_ofw_data(pwm_np);
    rt_ofw_node_put(pwm_np);

    if (!pr->pwm_dev)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    pr->pwm_conf.channel = pwm_args.args[0];
    pr->pwm_conf.period  = pwm_args.args[1];
    pr->pwm_conf.complementary =
        pwm_args.args_count >= 3 && (pwm_args.args[2] & RT_BIT(0));

    pr->enable_active_value = PIN_HIGH;
    pr->enable_pin          = rt_ofw_get_named_pin(np, "enable", 0,
                                                   RT_NULL, &pr->enable_active_value);

    if (pr->enable_pin < 0 && pr->enable_pin != PIN_NONE)
    {
        err = pr->enable_pin;
        goto _fail;
    }

    if (pr->enable_pin >= 0)
    {
        rt_bool_t on = pr->param.boot_on || pr->param.always_on;

        rt_pin_mode(pr->enable_pin, PIN_MODE_OUTPUT);
        rt_pin_write(pr->enable_pin, pwm_regulator_enable_pin_value(pr, on));
    }

    rgp              = &pr->parent;
    rgp->supply_name = pr->param.name;
    rgp->param       = &pr->param;
    rgp->dev         = &pdev->parent;

    if (rt_ofw_prop_read_bool(np, "voltage-table"))
    {
        err = pwm_regulator_init_table(np, pr);
    }
    else
    {
        err = pwm_regulator_init_continuous(np, pr);
    }

    if (err)
    {
        goto _fail;
    }

    {
        rt_uint32_t init_uvolt;

        if (!rt_ofw_prop_read_u32(np, "regulator-init-microvolt", &init_uvolt))
        {
            if (init_uvolt < pr->param.min_uvolt ||
                init_uvolt > pr->param.max_uvolt)
            {
                err = -RT_EINVAL;
                goto _fail;
            }

            pr->init_uvolt = init_uvolt;
        }
    }

    if ((err = pwm_regulator_adjust_config(pr)))
    {
        goto _fail;
    }

    if ((err = rt_regulator_register(rgp)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (pr)
    {
        rt_free(pr->duty_cycle_table);
        rt_free(pr);
    }

    return err;
}

static const struct rt_ofw_node_id pwm_regulator_ofw_ids[] = {
    { .compatible = "pwm-regulator" },
    { /* sentinel */ }
};

static struct rt_platform_driver pwm_regulator_driver = {
    .name = "pwm-regulator",
    .ids  = pwm_regulator_ofw_ids,

    .probe = pwm_regulator_probe,
};
RT_PLATFORM_DRIVER_EXPORT(pwm_regulator_driver);
