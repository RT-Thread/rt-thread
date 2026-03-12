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

#define DBG_TAG "reset.scmi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct scmi_reset
{
    struct rt_reset_controller parent;

    struct rt_scmi_device *sdev;
};

#define raw_to_scmi_reset(raw) rt_container_of(raw, struct scmi_reset, parent)

static rt_err_t scmi_reset_do(struct scmi_reset *srst, int domain,
        rt_uint32_t flags, rt_uint32_t state)
{
    struct scmi_reset_in in =
    {
        .domain_id = rt_cpu_to_le32(domain),
        .flags = rt_cpu_to_le32(flags),
        .reset_state = rt_cpu_to_le32(state),
    };
    struct scmi_reset_out out;
    struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_RESET_RESET, &in, &out);

    return rt_scmi_process_msg(srst->sdev, &msg);
}

static rt_err_t scmi_reset_reset(struct rt_reset_control *rstc)
{
    struct scmi_reset *srst = raw_to_scmi_reset(rstc);

    return scmi_reset_do(srst, rstc->id, SCMI_RESET_FLAG_RESET, SCMI_ARCH_COLD_RESET);
}

static rt_err_t scmi_reset_assert(struct rt_reset_control *rstc)
{
    struct scmi_reset *srst = raw_to_scmi_reset(rstc);

    return scmi_reset_do(srst, rstc->id, SCMI_RESET_FLAG_ASSERT, SCMI_ARCH_COLD_RESET);
}

static rt_err_t scmi_reset_deassert(struct rt_reset_control *rstc)
{
    struct scmi_reset *srst = raw_to_scmi_reset(rstc);

    return scmi_reset_do(srst, rstc->id, 0, SCMI_ARCH_COLD_RESET);
}

static rt_err_t scmi_reset_ofw_parse(struct rt_reset_control *rstc,
        struct rt_ofw_cell_args *args)
{
    rt_err_t err;
    struct scmi_reset *srst = raw_to_scmi_reset(rstc);
    struct scmi_reset_attr_in in =
    {
        .domain_id = rt_cpu_to_le32(rstc->id),
    };
    struct scmi_reset_attr_out out;
    struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_RESET_DOMAIN_ATTRIBUTES, &in, &out);

    if ((err = rt_scmi_process_msg(srst->sdev, &msg)))
    {
        return err;
    }

    return rt_le32_to_cpu(out.status) == 0 ? RT_EOK : -RT_ERROR;
}

static const struct rt_reset_control_ops scmi_reset_ops =
{
    .ofw_parse = scmi_reset_ofw_parse,
    .reset = scmi_reset_reset,
    .assert = scmi_reset_assert,
    .deassert = scmi_reset_deassert,
};

static rt_err_t scmi_reset_probe(struct rt_scmi_device *sdev)
{
    rt_err_t err;
    struct rt_reset_controller *rstcer;
    struct scmi_reset *srst = rt_calloc(1, sizeof(*srst));

    if (!srst)
    {
        return -RT_ENOMEM;
    }

    rstcer = &srst->parent;

    rstcer->priv = srst;
    rstcer->ofw_node = sdev->parent.ofw_node;
    rstcer->ops = &scmi_reset_ops;

    if ((err = rt_reset_controller_register(&srst->parent)))
    {
        rt_free(srst);
    }

    return err;
}

static const struct rt_scmi_device_id scmi_reset_ids[] =
{
    { SCMI_PROTOCOL_ID_RESET, "reset" },
    { /* sentinel */ },
};

static struct rt_scmi_driver scmi_reset_driver =
{
    .name = "reset-scmi",
    .ids = scmi_reset_ids,

    .probe = scmi_reset_probe,
};
RT_SCMI_DRIVER_EXPORT(scmi_reset_driver);
