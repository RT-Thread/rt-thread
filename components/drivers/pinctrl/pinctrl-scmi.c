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

#define DBG_TAG "pinctrl.scmi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define ATTR_SEL(x)     ((rt_uint32_t)(x) & 0x3U)
#define ATTR_NUM(n)     ((((rt_uint32_t)(n)) & 0xffU) << 2)
#define ATTR_FUNCSEL    (1u << 10)

struct scmi_pinctrl_info
{
    rt_uint32_t identifier;
    char name[64];
};

struct scmi_pinctrl
{
    struct rt_device_pin parent;

    struct rt_scmi_device *sdev;

    rt_size_t pins_nr;
    struct scmi_pinctrl_info *pins;

    rt_size_t groups_nr;
    struct scmi_pinctrl_info *groups;

    rt_size_t function_nr;
    struct scmi_pinctrl_info *function;
};

#define raw_to_scmi_pinctrl(raw) rt_container_of(raw, struct scmi_pinctrl, parent)

static const struct rt_pin_ctrl_conf_params scmi_conf_params[] =
{
    { "bias-bus-hold", PIN_CONFIG_BIAS_BUS_HOLD, 0 },
    { "bias-disable", PIN_CONFIG_BIAS_DISABLE, 0 },
    { "bias-high-impedance", PIN_CONFIG_BIAS_HIGH_IMPEDANCE, 0 },
    { "bias-pull-up", PIN_CONFIG_BIAS_PULL_UP, 1 },
    { "bias-pull-pin-default", PIN_CONFIG_BIAS_PULL_PIN_DEFAULT, 1 },
    { "bias-pull-down", PIN_CONFIG_BIAS_PULL_DOWN, 1 },
    { "drive-open-drain", PIN_CONFIG_DRIVE_OPEN_DRAIN, 0 },
    { "drive-open-source", PIN_CONFIG_DRIVE_OPEN_SOURCE, 0 },
    { "drive-push-pull", PIN_CONFIG_DRIVE_PUSH_PULL, 0 },
    { "drive-strength", PIN_CONFIG_DRIVE_STRENGTH, 0 },
    { "drive-strength-microamp", PIN_CONFIG_DRIVE_STRENGTH_UA, 0 },
    { "input-debounce", PIN_CONFIG_INPUT_DEBOUNCE, 0 },
    { "input-disable", PIN_CONFIG_INPUT_ENABLE, 0 },
    { "input-enable", PIN_CONFIG_INPUT_ENABLE, 1 },
    { "input-schmitt", PIN_CONFIG_INPUT_SCHMITT, 0 },
    { "input-schmitt-disable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, 0 },
    { "input-schmitt-enable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, 1 },
    { "low-power-disable", PIN_CONFIG_MODE_LOW_POWER, 0 },
    { "low-power-enable", PIN_CONFIG_MODE_LOW_POWER, 1 },
    { "output-disable", PIN_CONFIG_OUTPUT_ENABLE, 0 },
    { "output-enable", PIN_CONFIG_OUTPUT_ENABLE, 1 },
    { "output-high", PIN_CONFIG_OUTPUT, 1, },
    { "output-impedance-ohms", PIN_CONFIG_OUTPUT_IMPEDANCE_OHMS, 0 },
    { "output-low", PIN_CONFIG_OUTPUT, 0, },
    { "power-source", PIN_CONFIG_POWER_SOURCE, 0 },
    { "slew-rate", PIN_CONFIG_SLEW_RATE, 0 },
};

static enum scmi_pinctrl_conf_type scmi_conf_params_map[] =
{
    SCMI_PINCTRL_BIAS_BUS_HOLD,
    SCMI_PINCTRL_BIAS_DISABLE,
    SCMI_PINCTRL_BIAS_HIGH_IMPEDANCE,
    SCMI_PINCTRL_BIAS_PULL_UP,
    SCMI_PINCTRL_BIAS_PULL_DEFAULT,
    SCMI_PINCTRL_BIAS_PULL_DOWN,
    SCMI_PINCTRL_DRIVE_OPEN_DRAIN,
    SCMI_PINCTRL_DRIVE_OPEN_SOURCE,
    SCMI_PINCTRL_DRIVE_PUSH_PULL,
    SCMI_PINCTRL_DRIVE_STRENGTH,
    SCMI_PINCTRL_DRIVE_STRENGTH,
    SCMI_PINCTRL_INPUT_DEBOUNCE,
    SCMI_PINCTRL_INPUT_MODE,
    SCMI_PINCTRL_INPUT_MODE,
    SCMI_PINCTRL_INPUT_SCHMITT,
    SCMI_PINCTRL_INPUT_MODE,
    SCMI_PINCTRL_INPUT_MODE,
    SCMI_PINCTRL_LOW_POWER_MODE,
    SCMI_PINCTRL_LOW_POWER_MODE,
    SCMI_PINCTRL_OUTPUT_MODE,
    SCMI_PINCTRL_OUTPUT_MODE,
    SCMI_PINCTRL_OUTPUT_VALUE,
    SCMI_PINCTRL_OUTPUT_VALUE,
    SCMI_PINCTRL_OUTPUT_VALUE,
    SCMI_PINCTRL_POWER_SOURCE,
    SCMI_PINCTRL_SLEW_RATE,
};

static rt_bool_t scmi_pinconf_prop_name_to_param(const char *propname,
        rt_uint32_t *default_value, rt_uint32_t *out_type)
{
    const struct rt_pin_ctrl_conf_params *params = scmi_conf_params;

    for (int i = 0; i < RT_ARRAY_SIZE(scmi_conf_params); ++i, ++params)
    {
        if (!rt_strcmp(params->propname, propname))
        {
            *out_type = scmi_conf_params_map[i];
            *default_value = params->default_value;

            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static rt_bool_t scmi_lookup_id(const struct scmi_pinctrl_info *info,
        rt_size_t nr, const char *name, rt_uint32_t *out_id)
{
    for (rt_size_t i = 0; i < nr; ++i)
    {
        if (!rt_strcmp((const char *)info[i].name, name))
        {
            *out_id = info[i].identifier;
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static rt_err_t scmi_pinctrl_confs_apply(struct rt_device *device, void *fw_conf_np)
{
    rt_err_t err = RT_EOK;
    const char *string;
    rt_uint32_t function_id = 0xffffffffU;
    rt_size_t pins_nr = 0, groups_nr = 0, params_nr = 0;
    rt_uint32_t pins_id[32], groups_id[32], params_type[32], params_val[32];
    struct rt_ofw_prop *prop;
    struct rt_ofw_node *np = fw_conf_np;
    struct scmi_pinctrl *spctl = raw_to_scmi_pinctrl(device);

    LOG_D("Pinctrl apply '%s'", rt_ofw_node_full_name(np));

    rt_ofw_foreach_prop(np, prop)
    {
        if (!rt_strcmp(prop->name, "phandle"))
        {
            continue;
        }
        else if (!rt_strcmp(prop->name, "groups"))
        {
            for (string = rt_ofw_prop_next_string(prop, RT_NULL); string;
                string = rt_ofw_prop_next_string(prop, string))
            {
                if (groups_nr >= RT_ARRAY_SIZE(groups_id))
                {
                    return -RT_EFULL;
                }

                if (!scmi_lookup_id(spctl->groups, spctl->groups_nr, string, &groups_id[groups_nr]))
                {
                    return -RT_EINVAL;
                }
                ++groups_nr;
            }
        }
        else if (!rt_strcmp(prop->name, "pins"))
        {
            for (string = rt_ofw_prop_next_string(prop, RT_NULL); string;
                string = rt_ofw_prop_next_string(prop, string))
            {
                if (pins_nr >= RT_ARRAY_SIZE(pins_id))
                {
                    return -RT_EFULL;
                }

                if (!scmi_lookup_id(spctl->pins, spctl->pins_nr, string, &pins_id[pins_nr]))
                {
                    return -RT_EINVAL;
                }
                ++pins_nr;
            }
        }
        else if (!rt_strcmp(prop->name, "function"))
        {
            string = rt_ofw_prop_next_string(prop, RT_NULL);

            if (!scmi_lookup_id(spctl->function, spctl->function_nr, string, &function_id))
            {
                return -RT_EINVAL;
            }
        }
        else
        {
            if (params_nr >= RT_ARRAY_SIZE(params_type))
            {
                return -RT_EFULL;
            }

            if (!scmi_pinconf_prop_name_to_param(prop->name, &params_val[params_nr], &params_type[params_nr]))
            {
                return -RT_EINVAL;
            }

            if (prop->length >= sizeof(rt_uint32_t))
            {
                rt_ofw_prop_next_u32(prop, RT_NULL, &params_val[params_nr]);
            }

            ++params_nr;
        }
    }

    if (function_id != 0xffffffffU)
    {
        for (rt_size_t i = 0; i < groups_nr; ++i)
        {
            struct scmi_pinctrl_settings_conf_in in =
            {
                .identifier  = rt_cpu_to_le32(groups_id[i]),
                .function_id = rt_cpu_to_le32(function_id),
                .attributes  = rt_cpu_to_le32(ATTR_SEL(SCMI_PINCTRL_TYPE_GROUP) | ATTR_FUNCSEL),
            };
            struct scmi_pinctrl_settings_conf_out out = {0};
            struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_PINCTRL_SETTINGS_CONFIGURE, &in, &out);

            if ((err = rt_scmi_process_msg(spctl->sdev, &msg)))
            {
                return err;
            }

            if (rt_le32_to_cpu(out.status) != 0)
            {
                return -RT_ERROR;
            }
        }
    }

    if (params_nr)
    {
        struct
        {
            struct scmi_pinctrl_settings_conf_in hdr;
            rt_le32_t config[2 * 32];
        } in;
        struct scmi_pinctrl_settings_conf_out out = {0};
        struct rt_scmi_msg msg = {
            .sdev = spctl->sdev,
            .message_id = SCMI_PINCTRL_SETTINGS_CONFIGURE,
            .out_msg = (rt_uint8_t *)&out,
            .out_msg_size = sizeof(out),
        };

        for (rt_size_t i = 0; i < params_nr; ++i)
        {
            in.config[2 * i + 0] = rt_cpu_to_le32(params_type[i]);
            in.config[2 * i + 1] = rt_cpu_to_le32(params_val[i]);
        }

        for (rt_size_t i = 0; i < groups_nr; i++)
        {
            in.hdr.identifier  = rt_cpu_to_le32(groups_id[i]);
            in.hdr.function_id = rt_cpu_to_le32(0xffffffffU);
            in.hdr.attributes  = rt_cpu_to_le32(ATTR_SEL(SCMI_PINCTRL_TYPE_GROUP) | ATTR_NUM(params_nr));

            msg.in_msg = (rt_uint8_t *)&in;
            msg.in_msg_size = (rt_uint32_t)(sizeof(in.hdr) + params_nr * 2 * sizeof(rt_le32_t));

            if ((err = rt_scmi_process_msg(spctl->sdev, &msg)))
            {
                return err;
            }

            if (rt_le32_to_cpu(out.status) != 0)
            {
                return -RT_ERROR;
            }
        }

        for (rt_size_t i = 0; i < pins_nr; i++)
        {
            in.hdr.identifier  = rt_cpu_to_le32(pins_id[i]);
            in.hdr.function_id = rt_cpu_to_le32(0xffffffffU);
            in.hdr.attributes  = rt_cpu_to_le32(ATTR_SEL(SCMI_PINCTRL_TYPE_PIN) | ATTR_NUM(params_nr));

            msg.in_msg = (rt_uint8_t *)&in;
            msg.in_msg_size = (rt_uint32_t)(sizeof(in.hdr) + params_nr * 2 * sizeof(rt_le32_t));

            if ((err = rt_scmi_process_msg(spctl->sdev, &msg)))
            {
                return err;
            }

            if (rt_le32_to_cpu(out.status) != 0)
            {
                return -RT_ERROR;
            }
        }
    }

    return err;
}

static const struct rt_pin_ops scmi_pinctrl_ops =
{
    .pin_ctrl_confs_apply = scmi_pinctrl_confs_apply,
};

static rt_err_t scmi_pinctrl_name_parse_one(struct rt_scmi_device *sdev,
        enum scmi_pinctrl_selector_type sel, rt_size_t id, char *name)
{
    rt_err_t err;
    struct scmi_pinctrl_attributes_in attr_in =
    {
        .identifier = rt_cpu_to_le32(id),
        .flags = rt_cpu_to_le32(sel),
    };
    struct scmi_pinctrl_attributes_out attr_out = {0};
    struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_PINCTRL_ATTRIBUTES, &attr_in, &attr_out);

    name[0] = '\0';

    if ((err = rt_scmi_process_msg(sdev, &msg)))
    {
        return err;
    }

    if (rt_le32_to_cpu(attr_out.status) != 0)
    {
        return -RT_ERROR;
    }

    rt_strncpy(name, (char *)attr_out.name, sizeof(attr_out.name));

    if (SCMI_PINCTRL_EXT_NAME_FLAG(rt_le32_to_cpu(attr_out.attributes)))
    {
        struct scmi_pinctrl_name_get_in name_in =
        {
            .identifier = rt_cpu_to_le32(id),
            .flags = rt_cpu_to_le32(sel),
        };
        struct scmi_pinctrl_name_get_out name_out = {0};

        msg = RT_SCMI_MSG_IN_OUT(SCMI_PINCTRL_NAME_GET, &name_in, &name_out);

        if ((err = rt_scmi_process_msg(sdev, &msg)))
        {
            return err;
        }

        if (rt_le32_to_cpu(name_out.status) != 0)
        {
            return -RT_ERROR;
        }

        rt_strncpy(name, (char *)name_out.name, sizeof(name_out.name));
    }

    return RT_EOK;
}

static rt_err_t scmi_pinctrl_probe(struct rt_scmi_device *sdev)
{
    rt_err_t err;
    struct rt_scmi_msg msg;
    struct rt_device *dev = &sdev->parent;
    struct scmi_pinctrl_protocol_attributes protocol_attr_out;
    struct scmi_pinctrl *spctl = rt_calloc(1, sizeof(*spctl));

    if (!spctl)
    {
        return -RT_ENOMEM;
    }

    rt_memset(&protocol_attr_out, 0, sizeof(protocol_attr_out));
    msg = RT_SCMI_MSG_OUT(SCMI_COM_MSG_ATTRIBUTES, &protocol_attr_out);

    if ((err = rt_scmi_process_msg(sdev, &msg)))
    {
        goto _fail;
    }

    if (rt_le32_to_cpu(protocol_attr_out.status) != 0)
    {
        err = -RT_ERROR;
        goto _fail;
    }

    spctl->pins_nr = SCMI_PINCTRL_PINS_NR(rt_le32_to_cpu(protocol_attr_out.attributes_low));
    spctl->groups_nr = SCMI_PINCTRL_GROUPS_NR(rt_le32_to_cpu(protocol_attr_out.attributes_low));
    spctl->function_nr  = SCMI_PINCTRL_FUNCTIONS_NR(rt_le32_to_cpu(protocol_attr_out.attributes_high));

    spctl->pins = rt_malloc(sizeof(*spctl->pins) * spctl->pins_nr);
    spctl->groups = rt_malloc(sizeof(*spctl->groups) * spctl->groups_nr);
    spctl->function = rt_malloc(sizeof(*spctl->function) * spctl->function_nr);

    if (!spctl->pins || !spctl->groups || !spctl->function)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    for (rt_size_t i = 0; i < spctl->pins_nr; ++i)
    {
        if (scmi_pinctrl_name_parse_one(sdev, SCMI_PINCTRL_TYPE_PIN, i, spctl->pins[i].name))
        {
            LOG_E("%s parse identifier = %d fail", "Pin", i);
            continue;
        }

        spctl->pins[i].identifier = i;
    }

    for (rt_size_t i = 0; i < spctl->groups_nr; ++i)
    {
        if (scmi_pinctrl_name_parse_one(sdev, SCMI_PINCTRL_TYPE_GROUP, i, spctl->groups[i].name))
        {
            LOG_E("%s parse identifier = %d fail", "Group", i);
            continue;
        }

        spctl->groups[i].identifier = i;
    }

    for (rt_size_t i = 0; i < spctl->function_nr; ++i)
    {
        if (scmi_pinctrl_name_parse_one(sdev, SCMI_PINCTRL_TYPE_FUNCTION, i, spctl->function[i].name))
        {
            LOG_E("%s parse identifier = %d fail", "Function", i);
            continue;
        }

        spctl->function[i].identifier = i;
    }

    spctl->parent.ops = &scmi_pinctrl_ops;
    spctl->sdev = sdev;
    rt_ofw_data(dev->ofw_node) = &spctl->parent;

    return RT_EOK;

_fail:
    if (spctl->pins)
    {
        rt_free(spctl->pins);
    }

    if (spctl->groups)
    {
        rt_free(spctl->groups);
    }

    if (spctl->function)
    {
        rt_free(spctl->function);
    }

    rt_free(spctl);

    return err;
}

static const struct rt_scmi_device_id scmi_pinctrl_ids[] =
{
    { SCMI_PROTOCOL_ID_PINCTRL, "pinctrl" },
    { /* sentinel */ },
};

static struct rt_scmi_driver scmi_pinctrl_driver =
{
    .name = "pinctrl-scmi",
    .ids = scmi_pinctrl_ids,

    .probe = scmi_pinctrl_probe,
};
RT_SCMI_DRIVER_EXPORT(scmi_pinctrl_driver);
