/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pinctrl.rk8xx"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rk8xx.h"

struct rk8xx_pin
{
    const char *name;
};

enum rk8xx_pin_mux
{
    RK805_PINMUX_GPIO = 0,
    RK806_PINMUX_FUN0 = 0,
    RK806_PINMUX_FUN1,
    RK806_PINMUX_FUN2,
    RK806_PINMUX_FUN3,
    RK806_PINMUX_FUN4,
    RK806_PINMUX_FUN5,
};

struct rk8xx_pin_function
{
    const char *name;
    enum rk8xx_pin_mux mux;
};

struct rk8xx_pin_conf
{
    rt_uint8_t reg;
    rt_uint8_t fun_reg;
    rt_uint8_t fun_msk;
    rt_uint8_t dir_msk;
    rt_uint8_t val_msk;
};

struct rk8xx_pinctrl
{
    struct rt_device_pin parent;

    struct rk8xx *rk8xx;

    int pins_nr;
    const struct rk8xx_pin *pins;

    int pin_func_nr;
    const struct rk8xx_pin_function *pin_funcs;

    int pin_confs_nr;
    const struct rk8xx_pin_conf *pin_confs;
};

#define raw_to_rk8xx_pinctrl(raw) rt_container_of(raw, struct rk8xx_pinctrl, parent)

static void rk8xx_pinctrl_set_direction(struct rk8xx_pinctrl *rk8xx_pl,
        rt_base_t pin, rt_bool_t input)
{
    rt_uint32_t val;
    const struct rk8xx_pin_conf *pin_conf = &rk8xx_pl->pin_confs[pin];

    if (!pin_conf->dir_msk)
    {
        /* Default output */
        return;
    }

    val = rk8xx_read(rk8xx_pl->rk8xx, pin_conf->reg);

    if ((rt_err_t)val < 0)
    {
        LOG_E("Get PIN%d direction failed", pin);
    }

    return;
}

static void rk8xx_pinctrl_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    struct rk8xx_pinctrl *rk8xx_pl = raw_to_rk8xx_pinctrl(device);

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        rk8xx_pinctrl_set_direction(rk8xx_pl, pin, RT_FALSE);
        break;

    case PIN_MODE_INPUT:
        if (rk8xx_pl->rk8xx->variant != RK805_ID)
        {
            rk8xx_pinctrl_set_direction(rk8xx_pl, pin, RT_TRUE);
        }
        break;

    default:
        break;
    }
}

static void rk8xx_pinctrl_write(struct rt_device *device, rt_base_t pin,
        rt_uint8_t value)
{
    rt_err_t err;
    struct rk8xx_pinctrl *rk8xx_pl = raw_to_rk8xx_pinctrl(device);
    const struct rk8xx_pin_conf *pin_conf = &rk8xx_pl->pin_confs[pin];

    err = rk8xx_update_bits(rk8xx_pl->rk8xx,
            pin_conf->reg, pin_conf->val_msk, value ? pin_conf->val_msk : 0);

    if (err)
    {
        LOG_E("Set PIN%d value %d failed", pin, value);
    }
}

static rt_ssize_t rk8xx_pinctrl_read(struct rt_device *device, rt_base_t pin)
{
    int val;
    struct rk8xx_pinctrl *rk8xx_pl = raw_to_rk8xx_pinctrl(device);

    val = rk8xx_read(rk8xx_pl->rk8xx, rk8xx_pl->pin_confs[pin].reg);

    if ((rt_err_t)val < 0)
    {
        LOG_E("Get PIN%d value failed", pin);

        return val;
    }

    return !!(val & rk8xx_pl->pin_confs[pin].val_msk);
}

static rt_ssize_t rk8xx_pin_parse(struct rt_device *device,
        struct rt_ofw_cell_args *args, rt_uint32_t *flags)
{
    if (flags)
    {
        *flags = args->args[1];
    }

    return args->args[0];
}

static rt_err_t rk8xx_pinctrl_confs_apply(struct rt_device *device, void *fw_conf_np)
{
    int i;
    rt_err_t err;
    rt_base_t pin = 0;
    enum rk8xx_pin_mux mux = 0;
    const char *pin_name, *function;
    const struct rk8xx_pin_conf *pin_conf;
    struct rt_ofw_node *conf_np = fw_conf_np;
    struct rk8xx_pinctrl *rk8xx_pl = raw_to_rk8xx_pinctrl(device);

    if ((err = rt_ofw_prop_read_string(conf_np, "pins", &pin_name)))
    {
        LOG_E("%s: %s not found", rt_ofw_node_full_name(conf_np), "pins");
        return err;
    }

    if ((err = rt_ofw_prop_read_string(conf_np, "function", &function)))
    {
        LOG_E("%s: %s not found", rt_ofw_node_full_name(conf_np), "function");
        return err;
    }

    for (i = 0; i < rk8xx_pl->pins_nr; ++i)
    {
        if (!rt_strcmp(rk8xx_pl->pins[i].name, pin_name))
        {
            break;
        }
        ++pin;
    }

    if (i == rk8xx_pl->pins_nr)
    {
        return -RT_EINVAL;
    }

    for (i = 0; i < rk8xx_pl->pin_func_nr; ++i)
    {
        if (!rt_strcmp(rk8xx_pl->pin_funcs[i].name, function))
        {
            mux = rk8xx_pl->pin_funcs[i].mux;
            break;
        }
    }

    if (i == rk8xx_pl->pin_func_nr)
    {
        return -RT_EINVAL;
    }

    pin_conf = &rk8xx_pl->pin_confs[pin];

    if (!pin_conf->fun_msk)
    {
        return RT_EOK;
    }

    mux <<= __rt_ffs(pin_conf->fun_msk) - 1;
    err = rk8xx_update_bits(rk8xx_pl->rk8xx,
            pin_conf->fun_reg, pin_conf->fun_msk, mux);

    if (err)
    {
        LOG_E("Set PIN%d func%d failed", pin, mux);
    }

    return err;
}

static const struct rt_pin_ops rk8xx_pinctrl_ops =
{
    .pin_mode = rk8xx_pinctrl_mode,
    .pin_write = rk8xx_pinctrl_write,
    .pin_read = rk8xx_pinctrl_read,
    .pin_parse = rk8xx_pin_parse,
    .pin_ctrl_confs_apply = rk8xx_pinctrl_confs_apply,
};

static const struct rk8xx_pin rk805_pins[] =
{
    { .name = "gpio0", },
    { .name = "gpio1", },
};

static const struct rk8xx_pin_function rk805_gpio_funcs[] =
{
    { .name = "gpio", .mux = RK805_PINMUX_GPIO },
};

#define RK805_GPIO0_VAL_MSK RT_BIT(0)
#define RK805_GPIO1_VAL_MSK RT_BIT(1)

static const struct rk8xx_pin_conf rk805_gpio_confs[] =
{
    {
        .reg = RK805_OUT_REG,
        .val_msk = RK805_GPIO0_VAL_MSK,
    },
    {
        .reg = RK805_OUT_REG,
        .val_msk = RK805_GPIO1_VAL_MSK,
    },
};

static struct rk8xx_pin rk806_pins[] =
{
    { .name = "gpio_pwrctrl1", },
    { .name = "gpio_pwrctrl2", },
    { .name = "gpio_pwrctrl3", },
};

static const struct rk8xx_pin_function rk806_gpio_funcs[] =
{
    { .name = "pin_fun0", .mux = RK806_PINMUX_FUN0 },
    { .name = "pin_fun1", .mux = RK806_PINMUX_FUN1 },
    { .name = "pin_fun2", .mux = RK806_PINMUX_FUN2 },
    { .name = "pin_fun3", .mux = RK806_PINMUX_FUN3 },
    { .name = "pin_fun4", .mux = RK806_PINMUX_FUN4 },
    { .name = "pin_fun5", .mux = RK806_PINMUX_FUN5 },
};

#define RK806_PWRCTRL1_DR   RT_BIT(0)
#define RK806_PWRCTRL2_DR   RT_BIT(1)
#define RK806_PWRCTRL3_DR   RT_BIT(2)
#define RK806_PWRCTRL1_DATA RT_BIT(4)
#define RK806_PWRCTRL2_DATA RT_BIT(5)
#define RK806_PWRCTRL3_DATA RT_BIT(6)
#define RK806_PWRCTRL1_FUN  RT_GENMASK(2, 0)
#define RK806_PWRCTRL2_FUN  RT_GENMASK(6, 4)
#define RK806_PWRCTRL3_FUN  RT_GENMASK(2, 0)

static const struct rk8xx_pin_conf rk806_gpio_confs[] =
{
    {
        .fun_reg = RK806_SLEEP_CONFIG0,
        .fun_msk = RK806_PWRCTRL1_FUN,
        .reg = RK806_SLEEP_GPIO,
        .val_msk = RK806_PWRCTRL1_DATA,
        .dir_msk = RK806_PWRCTRL1_DR,
    },
    {
        .fun_reg = RK806_SLEEP_CONFIG0,
        .fun_msk = RK806_PWRCTRL2_FUN,
        .reg = RK806_SLEEP_GPIO,
        .val_msk = RK806_PWRCTRL2_DATA,
        .dir_msk = RK806_PWRCTRL2_DR,
    },
    {
        .fun_reg = RK806_SLEEP_CONFIG1,
        .fun_msk = RK806_PWRCTRL3_FUN,
        .reg = RK806_SLEEP_GPIO,
        .val_msk = RK806_PWRCTRL3_DATA,
        .dir_msk = RK806_PWRCTRL3_DR,
    }
};

static rt_err_t rk8xx_pinctrl_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    char *compat;
    int pins_nr, pin_func_nr, pin_confs_nr;
    const struct rk8xx_pin *pins;
    const struct rk8xx_pin_function *pin_funcs;
    const struct rk8xx_pin_conf *pin_confs;
    struct rk8xx *rk8xx = pdev->priv;
    struct rt_ofw_node *np = pdev->parent.ofw_node;
    struct rk8xx_pinctrl *rk8xx_pl = rt_calloc(1, sizeof(*rk8xx_pl));

    if (!rk8xx_pl)
    {
        return -RT_ENOMEM;
    }

    rk8xx_pl->rk8xx = rk8xx;

    switch (rk8xx->variant)
    {
    case RK805_ID:
        compat = "rk805-pinctrl";
        pins_nr = RT_ARRAY_SIZE(rk805_pins);
        pins = rk805_pins;
        pin_func_nr = RT_ARRAY_SIZE(rk805_gpio_funcs);
        pin_funcs = rk805_gpio_funcs;
        pin_confs_nr = RT_ARRAY_SIZE(rk805_gpio_confs);
        pin_confs = rk805_gpio_confs;
        break;

    case RK806_ID:
        compat = "rk806-pinctrl";
        pins_nr = RT_ARRAY_SIZE(rk806_pins);
        pins = rk806_pins;
        pin_func_nr = RT_ARRAY_SIZE(rk806_gpio_funcs);
        pin_funcs = rk806_gpio_funcs;
        pin_confs_nr = RT_ARRAY_SIZE(rk806_gpio_confs);
        pin_confs = rk806_gpio_confs;
        break;

    default:
        err = -RT_EINVAL;
        goto _fail;
    }

    rk8xx_pl->parent.ops = &rk8xx_pinctrl_ops;
    rk8xx_pl->pins_nr = pins_nr;
    rk8xx_pl->pins = pins;
    rk8xx_pl->pin_func_nr = pin_func_nr;
    rk8xx_pl->pin_funcs = pin_funcs;
    rk8xx_pl->pin_confs_nr = pin_confs_nr;
    rk8xx_pl->pin_confs = pin_confs;

    if (!rt_ofw_prop_read_bool(np, "compatible"))
    {
        /* make pinctrl can find that */
        if ((err = rt_ofw_append_prop(np, "compatible", rt_strlen(compat) + 1, compat)))
        {
            goto _fail;
        }
    }

    rt_ofw_data(np) = &rk8xx_pl->parent;

    return RT_EOK;

_fail:
    rt_free(rk8xx_pl);

    return err;
}

static struct rt_platform_driver rk8xx_pinctrl_driver =
{
    .name = "rk8xx-pinctrl",
    .probe = rk8xx_pinctrl_probe,
};
RT_PLATFORM_DRIVER_EXPORT(rk8xx_pinctrl_driver);
