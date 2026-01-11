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

#define DBG_TAG "pinctrl.spacemit-pmic"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define __SPACEMIT_PINCTRL_INTERNAL
#include <mfd/spacemit-pmic.h>

struct spacemit_pmic_pinctrl
{
    struct rt_device_pin parent;

    rt_uint32_t npins;

    struct spacemit_pmic *pmic;
    const struct spacemit_pmic_pin_data *data;
};

#define raw_to_spacemit_pmic_pinctrl(raw) rt_container_of(raw, struct spacemit_pmic_pinctrl, parent)

static rt_err_t spacemit_pmic_pinctrl_set_mux(struct spacemit_pmic_pinctrl *pmic_pinctrl,
        rt_uint32_t function, rt_base_t pin)
{
    int i;
    rt_err_t err;
    const char *funcname;
    struct spacemit_pmic *pmic = pmic_pinctrl->pmic;
    const struct spacemit_pmic_pin_data *data = pmic_pinctrl->data;
    const struct spacemit_pmic_pin_func_desc *pinfunc_desc = data->pinfunc_desc;

    funcname = data->pinmux_funcs[function];

    for (i = 0; i < data->pin_mux_nr; ++i)
    {
        if (!rt_strcmp(funcname, pinfunc_desc[i].name) && pin == pinfunc_desc[i].pin_id)
        {
            /* Set the first */
            err = spacemit_pmic_update_bits(pmic,
                    pinfunc_desc[i].func_reg,
                    pinfunc_desc[i].func_mask,
                    pinfunc_desc[i].en_val << (__rt_ffs(pinfunc_desc[i].func_mask) - 1));
            if (err)
            {
                LOG_E("Set PIN%d, function:%s, failed", pin, funcname);
                return err;
            }

            /* Set the next if it have */
            if (pinfunc_desc[i].ha_sub)
            {
                err = spacemit_pmic_update_bits(pmic,
                        pinfunc_desc[i].sub_reg,
                        pinfunc_desc[i].sub_mask,
                        pinfunc_desc[i].sube_val << (__rt_ffs(pinfunc_desc[i].sub_mask) - 1));
                if (err)
                {
                    LOG_E("Set PIN%d, function:%s, failed", pin, funcname);
                    return err;
                }
            }

            break;
        }
    }

    if (i >= data->pin_mux_nr)
    {
        LOG_E("Unsupported PIN%d, function:%s", pin, funcname);
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static void spacemit_pmic_pinctrl_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    struct spacemit_pmic_pinctrl *pmic_pinctrl = raw_to_spacemit_pmic_pinctrl(device);

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        spacemit_pmic_pinctrl_set_mux(pmic_pinctrl, 1, pin);
        break;

    case PIN_MODE_INPUT:
        spacemit_pmic_pinctrl_set_mux(pmic_pinctrl, 0, pin);
        break;

    default:
        break;
    }
}

static void spacemit_pmic_pinctrl_write(struct rt_device *device, rt_base_t pin,
        rt_uint8_t value)
{
    rt_err_t err;
    const struct spacemit_pmic_pin_config_desc *pinconf_desc;
    struct spacemit_pmic_pinctrl *pmic_pinctrl = raw_to_spacemit_pmic_pinctrl(device);

    pinconf_desc = pmic_pinctrl->data->pinconf_desc;

    err = spacemit_pmic_update_bits(pmic_pinctrl->pmic,
            pinconf_desc[pin].output.reg,
            pinconf_desc[pin].output.msk,
            value ? pinconf_desc[pin].output.msk : 0);

    if (err)
    {
        LOG_E("Set PIN%d, val:%d, failed", pin, value);
    }
}

static rt_ssize_t spacemit_pmic_pinctrl_read(struct rt_device *device, rt_base_t pin)
{
    rt_ssize_t val;
    const struct spacemit_pmic_pin_config_desc *pinconf_desc;
    struct spacemit_pmic_pinctrl *pmic_pinctrl = raw_to_spacemit_pmic_pinctrl(device);

    pinconf_desc = pmic_pinctrl->data->pinconf_desc;

    if ((val = spacemit_pmic_read(pmic_pinctrl->pmic, pinconf_desc[pin].input.reg)) < 0)
    {
        LOG_E("Get PIN%d, direction failed", pin);
        return val;
    }

    val = val & pinconf_desc[pin].input.msk;
    val >>= __rt_ffs(pinconf_desc[pin].input.msk) - 1;

    return val;
}

static rt_ssize_t spacemit_pmic_pin_parse(struct rt_device *device,
        struct rt_ofw_cell_args *args, rt_uint32_t *flags)
{
    if (flags)
    {
        *flags = args->args[1];
    }

    return args->args[0];
}

static const struct rt_pin_ctrl_conf_params spacemit_pmic_pinctrl_params[] =
{
    { "bias-disable", PIN_CONFIG_BIAS_DISABLE },
    { "bias-pull-down", PIN_CONFIG_BIAS_PULL_DOWN },
    { "bias-pull-up", PIN_CONFIG_BIAS_PULL_UP },
    { "drive-open-drain", PIN_CONFIG_DRIVE_OPEN_DRAIN },
    { "drive-push-pull", PIN_CONFIG_DRIVE_PUSH_PULL },
    { "drive-open-source", PIN_CONFIG_DRIVE_OPEN_SOURCE },
    { "input-debounce", PIN_CONFIG_INPUT_DEBOUNCE },
    { "input-schmitt-disable", PIN_CONFIG_INPUT_SCHMITT_ENABLE },
    { "input-schmitt-enable", PIN_CONFIG_INPUT_SCHMITT_ENABLE },
    { "output-high", PIN_CONFIG_OUTPUT },
    { "output-low", PIN_CONFIG_OUTPUT },
};

static rt_bool_t spacemit_pmic_pinctrl_param_parse(const char *name, rt_uint32_t *out_param)
{
    for (int i = 0; i < RT_ARRAY_SIZE(spacemit_pmic_pinctrl_params); ++i)
    {
        if (!rt_strcmp(spacemit_pmic_pinctrl_params[i].propname, "name"))
        {
            *out_param = spacemit_pmic_pinctrl_params[i].param;
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static rt_err_t spacemit_pmic_pinctrl_confs_apply(struct rt_device *device, void *fw_conf_np)
{
    rt_err_t err;
    rt_ubase_t pin;
    rt_uint32_t function, param;
    const char *string;
    struct rt_ofw_prop *pins_prop, *prop;
    struct spacemit_pmic_pinctrl *pmic_pinctrl = raw_to_spacemit_pmic_pinctrl(device);
    const struct spacemit_pmic_pin_data *data = pmic_pinctrl->data;
    const struct spacemit_pmic_pin_config_desc *pinconf_desc = data->pinconf_desc;
    struct spacemit_pmic *pmic = pmic_pinctrl->pmic;

    /**
     *  led_pins: led-pins {
     *      pins = "PIN3";
     *      function = "sleep";
     *      bias-disable = <0>;
     *      drive-open-drain = <0x1>;
     *  };
     */

    if ((err = rt_ofw_prop_read_string(fw_conf_np, "function", &string)))
    {
        return err;
    }

    function = data->pin_mux_nr;

    for (int i = 0; i < data->pin_mux_nr; ++i)
    {
        if (!rt_strcmp(data->pinmux_funcs[i], string))
        {
            function = i;
        }
    }

    if (function >= data->pin_mux_nr)
    {
        return -RT_EINVAL;
    }

    rt_ofw_foreach_prop_string(fw_conf_np, "pins", pins_prop, string)
    {
        pin = 0;
        string += sizeof("PIN") - 1;

        while (*string)
        {
            pin *= 10;
            pin += *string - '0';

            ++string;
        }

        if (spacemit_pmic_pinctrl_set_mux(pmic_pinctrl, function, pin))
        {
            return err;
        }

        rt_ofw_foreach_prop(((struct rt_ofw_node *)fw_conf_np), prop)
        {
            rt_uint32_t reg, msk;

            if (!rt_strcmp(prop->name, "pins") || !rt_strcmp(prop->name, "function"))
            {
                continue;
            }

            if (!spacemit_pmic_pinctrl_param_parse(prop->name, &param))
            {
                return -RT_ENOSYS;
            }

            switch (param)
            {
            case PIN_CONFIG_BIAS_DISABLE:
            case PIN_CONFIG_BIAS_PULL_DOWN:
            case PIN_CONFIG_BIAS_PULL_UP:
                reg = pinconf_desc[pin].pup.reg;
                msk = pinconf_desc[pin].pup.msk;
                break;
            case PIN_CONFIG_DRIVE_OPEN_DRAIN:
            case PIN_CONFIG_DRIVE_PUSH_PULL:
            case PIN_CONFIG_DRIVE_OPEN_SOURCE:
                reg = pinconf_desc[pin].od.reg;
                msk = pinconf_desc[pin].od.msk;
                break;
            case PIN_CONFIG_INPUT_DEBOUNCE:
                reg = pinconf_desc[pin].deb.reg;
                msk = pinconf_desc[pin].deb.timemsk;
                break;
            case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
                reg = pinconf_desc[pin].deb.reg;
                msk = pinconf_desc[pin].deb.en.msk;
                break;
            case PIN_CONFIG_OUTPUT:
                reg = pinconf_desc[pin].output.reg;
                msk = pinconf_desc[pin].output.msk;
                break;
            default:
                LOG_E("To fixed your code");
                RT_ASSERT(0);
                break;
            }

            err = spacemit_pmic_update_bits(pmic, reg, msk,
                    fdt32_to_cpu(*(fdt32_t *)prop->value) << (__rt_ffs(msk) - 1));
            if (err)
            {
                LOG_E("Set reg:%x, msk:%x failed", reg, msk);
                return -RT_EINVAL;
            }
        }
    }

    return RT_EOK;
}

static const struct rt_pin_ops spacemit_pmic_pinctrl_ops =
{
    .pin_mode = spacemit_pmic_pinctrl_mode,
    .pin_write = spacemit_pmic_pinctrl_write,
    .pin_read = spacemit_pmic_pinctrl_read,
    .pin_parse = spacemit_pmic_pin_parse,
    .pin_ctrl_confs_apply = spacemit_pmic_pinctrl_confs_apply,
};

static rt_err_t spacemit_pmic_pinctrl_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_pmic *pmic = pdev->priv;
    struct spacemit_pmic_pinctrl *pmic_pinctrl = rt_calloc(1, sizeof(*pmic_pinctrl));

    if (!pmic_pinctrl)
    {
        return -RT_ENOMEM;
    }

    pmic_pinctrl->pmic = pmic;
    pmic_pinctrl->data = pdev->id->data;

    if ((err = rt_dm_dev_prop_read_u32(dev, "spacemit,npins", &pmic_pinctrl->npins)))
    {
        goto _fail;
    }

    pmic_pinctrl->parent.ops = &spacemit_pmic_pinctrl_ops;
    rt_ofw_data(dev->ofw_node) = &pmic_pinctrl->parent;

    return RT_EOK;

_fail:
    rt_free(pmic_pinctrl);

    return err;
}

static const struct rt_ofw_node_id spacemit_pmic_pinctrl_ofw_ids[] =
{
    { .compatible = "pmic,pinctrl,spm8821", .data = &spm8821_pinctrl_data },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_pmic_pinctrl_driver =
{
    .name = "spacemit-pmic-pinctrl",
    .ids = spacemit_pmic_pinctrl_ofw_ids,

    .probe = spacemit_pmic_pinctrl_probe,
};

static int spacemit_pmic_pinctrl_register(void)
{
    rt_platform_driver_register(&spacemit_pmic_pinctrl_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(spacemit_pmic_pinctrl_register);
