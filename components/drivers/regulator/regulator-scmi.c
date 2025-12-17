/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "regulator.scmi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct scmi_regulator
{
    struct rt_regulator_node parent;
    struct rt_regulator_param param;

    struct rt_device dev;
    struct rt_scmi_device *sdev;

    rt_uint32_t domain_id;
};

#define raw_to_scmi_regulator(raw) rt_container_of(raw, struct scmi_regulator, parent)

static rt_err_t scmi_regulator_set_enable(struct scmi_regulator *sreg, rt_bool_t enable)
{
    struct scmi_voltage_config_set_in in =
    {
        .domain_id = rt_cpu_to_le32(sreg->domain_id),
        .config = rt_cpu_to_le32(enable ? SCMI_VOLTAGE_CONFIG_ON : SCMI_VOLTAGE_CONFIG_OFF),
    };
    struct scmi_voltage_config_set_out out;
    struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_VOLTAGE_DOMAIN_CONFIG_SET, &in, &out);

    return rt_scmi_process_msg(sreg->sdev, &msg) ? : (out.status ? -RT_ERROR : RT_EOK);
}

static rt_err_t scmi_regulator_enable(struct rt_regulator_node *reg_np)
{
    struct scmi_regulator *sreg = raw_to_scmi_regulator(reg_np);

    return scmi_regulator_set_enable(sreg, RT_TRUE);
}

static rt_err_t scmi_regulator_disable(struct rt_regulator_node *reg_np)
{
    struct scmi_regulator *sreg = raw_to_scmi_regulator(reg_np);

    return scmi_regulator_set_enable(sreg, RT_FALSE);
}

static rt_bool_t scmi_regulator_is_enabled(struct rt_regulator_node *reg_np)
{
    struct scmi_regulator *sreg = raw_to_scmi_regulator(reg_np);
    struct scmi_voltage_config_get_in in =
    {
        .domain_id = rt_cpu_to_le32(sreg->domain_id),
    };
    struct scmi_voltage_config_get_out out;
    struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_VOLTAGE_DOMAIN_CONFIG_GET, &in, &out);

    return rt_scmi_process_msg(sreg->sdev, &msg) ? RT_FALSE : (out.config == SCMI_VOLTAGE_CONFIG_ON);
}

static rt_err_t scmi_regulator_set_voltage(struct rt_regulator_node *reg_np,
        int min_uvolt, int max_uvolt)
{
    struct scmi_regulator *sreg = raw_to_scmi_regulator(reg_np);
    struct scmi_voltage_level_set_in in =
    {
        .domain_id = rt_cpu_to_le32(sreg->domain_id),
        .voltage_level = rt_cpu_to_le32((max_uvolt + min_uvolt) >> 1),
    };
    struct scmi_voltage_level_set_out out;
    struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_VOLTAGE_DOMAIN_LEVEL_SET, &in, &out);

    return rt_scmi_process_msg(sreg->sdev, &msg);
}

static int scmi_regulator_get_voltage(struct rt_regulator_node *reg_np)
{
    struct scmi_regulator *sreg = raw_to_scmi_regulator(reg_np);
    struct scmi_voltage_level_get_in in =
    {
        .domain_id = rt_cpu_to_le32(sreg->domain_id),
    };
    struct scmi_voltage_level_get_out out;
    struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_VOLTAGE_DOMAIN_LEVEL_GET, &in, &out);

    return rt_scmi_process_msg(sreg->sdev, &msg) ? : out.voltage_level;
}

static const struct rt_regulator_ops scmi_regulator_voltage_ops =
{
    .enable = scmi_regulator_enable,
    .disable = scmi_regulator_disable,
    .is_enabled = scmi_regulator_is_enabled,
    .set_voltage = scmi_regulator_set_voltage,
    .get_voltage = scmi_regulator_get_voltage,
};

static rt_err_t scmi_regulator_probe(struct rt_scmi_device *sdev)
{
    rt_err_t err;
    rt_uint32_t dom_nr;
    struct rt_regulator_node *rnp;
    struct rt_ofw_node *np, *child_np;
    struct scmi_regulator *sregs = RT_NULL, *sreg;

    np = rt_ofw_get_child_by_tag(sdev->parent.ofw_node, "regulators");

    if (!np)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    dom_nr = rt_ofw_get_child_count(np);

    if (!dom_nr)
    {
        err = -RT_EEMPTY;
        goto _fail;
    }

    sregs = rt_calloc(dom_nr, sizeof(*sregs));

    if (!sregs)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    sreg = &sregs[0];

    rt_ofw_foreach_child_node(np, child_np)
    {
        if ((err = rt_ofw_prop_read_u32(child_np, "reg", &sreg->domain_id)))
        {
            goto _fail;
        }

        sreg->sdev = sdev;

        rnp = &sreg->parent;
        sreg->dev.ofw_node = child_np;

        rt_ofw_prop_read_string(child_np, "regulator-name", &rnp->supply_name);
        rnp->ops = &scmi_regulator_voltage_ops;
        rnp->param = &sreg->param;
        rnp->dev = &sreg->dev;

        ++sreg;
    }
    rt_ofw_node_put(np);

    sreg = &sregs[0];

    for (int i = 0; i < dom_nr; ++i, ++sreg)
    {
        if ((err = rt_regulator_register(&sreg->parent)))
        {
            while (i --> 0)
            {
                --sreg;

                rt_regulator_unregister(&sreg->parent);
            }

            goto _fail;
        }
    }

    return RT_EOK;

_fail:
    rt_ofw_node_put(np);

    if (sregs)
    {
        rt_free(sregs);
    }

    return err;
}

static const struct rt_scmi_device_id scmi_regulator_ids[] =
{
    { SCMI_PROTOCOL_ID_VOLTAGE, "regulator" },
    { /* sentinel */ },
};

static struct rt_scmi_driver scmi_regulator_driver =
{
    .name = "scmi-regulator",
    .ids = scmi_regulator_ids,

    .probe = scmi_regulator_probe,
};
RT_SCMI_DRIVER_EXPORT(scmi_regulator_driver);
