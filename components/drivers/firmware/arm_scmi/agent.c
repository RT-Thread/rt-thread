/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include "agent.h"

#define DBG_TAG "scmi.agent"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

rt_err_t rt_scmi_process_msg(struct rt_scmi_device *sdev, struct rt_scmi_msg *msg)
{
    struct scmi_agent *agent;

    if (!sdev || !msg)
    {
        return -RT_EINVAL;
    }

    agent = sdev->agent;
    msg->sdev = sdev;

    return agent->ops->process_msg(agent, msg);
}

static const char * const _scmi_error_table[] =
{
    [-SCMI_SUCCESS]         = "SUCCESS",
    [-SCMI_ERR_SUPPORT]     = "SUPPORT",
    [-SCMI_ERR_PARAMS]      = "PARAMS",
    [-SCMI_ERR_ACCESS]      = "ACCESS",
    [-SCMI_ERR_ENTRY]       = "ENTRY",
    [-SCMI_ERR_RANGE]       = "RANGE",
    [-SCMI_ERR_BUSY]        = "BUSY",
    [-SCMI_ERR_COMMS]       = "COMMS",
    [-SCMI_ERR_GENERIC]     = "GENERIC",
    [-SCMI_ERR_HARDWARE]    = "HARDWARE",
    [-SCMI_ERR_PROTOCOL]    = "PROTOCOL",
};

const char *rt_scmi_strerror(rt_base_t err)
{
    const char *str;

    err = err < 0 ? -err : err;

    if (err < RT_ARRAY_SIZE(_scmi_error_table))
    {
        str = _scmi_error_table[err];
    }
    else
    {
        str = "UNKNOWN";
    }

    return str;
}

static rt_err_t scmi_channels_setup(struct scmi_agent *agent,
        struct rt_platform_device *pdev)
{
    struct rt_ofw_node *np = pdev->parent.ofw_node, *chn;

    rt_ofw_foreach_available_child_node(np, chn)
    {
        rt_uint32_t prot_id;
        struct rt_scmi_device *sdev;

        if (rt_ofw_prop_read_u32(chn, "reg", &prot_id))
        {
            continue;
        }

        sdev = rt_calloc(1, sizeof(*sdev));

        if (!sdev)
        {
            rt_ofw_node_put(chn);
            return -RT_ENOMEM;
        }

        sdev->parent.ofw_node = chn;
        sdev->protocol_id = prot_id;
        sdev->agent = agent;

        rt_scmi_device_register(sdev);
    }

    return RT_EOK;
}

static rt_err_t scmi_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_scmi_device *base_sdev;
    struct scmi_agent *agent = rt_malloc(sizeof(*agent) + sizeof(*base_sdev));
    const struct scmi_agent_ops *agent_ops;

    if (!agent)
    {
        return -RT_ENOMEM;
    }

    agent_ops = pdev->id->data;
    agent->ops = agent_ops;

    if ((err = agent_ops->setup(agent, &pdev->parent)))
    {
        LOG_E("Setup interface %s error = %s", agent_ops->name, rt_strerror(err));
        goto _fail;
    }

    if ((err = scmi_channels_setup(agent, pdev)))
    {
        goto _fail;
    }

    base_sdev = (void *)&agent[1];
    rt_memset(base_sdev, 0, sizeof(*base_sdev));

    base_sdev->protocol_id = SCMI_PROTOCOL_ID_BASE;
    base_sdev->agent = agent;

    if ((err = rt_scmi_device_register(base_sdev)))
    {
        LOG_W("Base protocol register error = %s", rt_strerror(err));
    }

    return RT_EOK;

_fail:
    rt_free(agent);

    return err;
}

extern struct rt_scmi_agent_ops scmi_agent_mailbox_ops;
extern struct rt_scmi_agent_ops scmi_agent_smc_ops;
extern struct rt_scmi_agent_ops scmi_agent_virtio_ops;

static const struct rt_ofw_node_id scmi_ofw_ids[] =
{
#ifdef RT_FIRMWARE_ARM_SCMI_TRANSPORT_MAILBOX
    { .compatible = "arm,scmi", .data = &scmi_agent_mailbox_ops },
#endif
#ifdef RT_FIRMWARE_ARM_SCMI_TRANSPORT_SMC
    { .compatible = "arm,scmi-smc", .data = &scmi_agent_smc_ops },
    { .compatible = "arm,scmi-smc-param", .data = &scmi_agent_smc_ops },
    { .compatible = "qcom,scmi-smc", .data = &scmi_agent_smc_ops},
#endif
#ifdef RT_FIRMWARE_ARM_SCMI_TRANSPORT_VIRTIO
    { .compatible = "arm,scmi-virtio", .data = &scmi_agent_virtio_ops },
#endif
    { /* sentinel */ }
};

static struct rt_platform_driver scmi_driver =
{
    .name = "arm-scmi",
    .ids = scmi_ofw_ids,

    .probe = scmi_probe,
};

static int scmi_drv_register(void)
{
    rt_platform_driver_register(&scmi_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(scmi_drv_register);
