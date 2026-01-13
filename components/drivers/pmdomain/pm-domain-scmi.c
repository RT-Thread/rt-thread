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

#define DBG_TAG "pm-domain.scmi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct scmi_pm_domain_proxy;

struct scmi_pm_domain
{
    struct rt_dm_power_domain parent;

    rt_uint32_t domain;

    struct scmi_pm_domain_proxy *proxy;
};

#define raw_to_scmi_pm_domain(raw) rt_container_of(raw, struct scmi_pm_domain, parent)

struct scmi_pm_domain_proxy
{
    struct rt_dm_power_domain_proxy parent;

    struct rt_scmi_device *sdev;

    rt_uint32_t num_domains;
    struct scmi_pm_domain domains[];
};

#define raw_to_scmi_pm_domain_proxy(raw) rt_container_of(raw, struct scmi_pm_domain_proxy, parent)

static rt_err_t scmi_pm_domain_power(struct scmi_pm_domain *scmi_pd, rt_bool_t power_on)
{
    struct scmi_power_state_set_in in =
    {
        .flags = rt_cpu_to_le32(0),
        .domain = rt_cpu_to_le32(scmi_pd->domain),
        .state = rt_cpu_to_le32(power_on ? SCMI_POWER_STATE_GENERIC_ON : SCMI_POWER_STATE_GENERIC_OFF),
    };
    struct scmi_power_state_set_out out;
    struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_POWER_STATE_SET, &in, &out);

    return rt_scmi_process_msg(scmi_pd->proxy->sdev, &msg);
}

static rt_err_t scmi_pd_power_on(struct rt_dm_power_domain *domain)
{
    return scmi_pm_domain_power(raw_to_scmi_pm_domain(domain), RT_TRUE);
}

static rt_err_t scmi_pd_power_off(struct rt_dm_power_domain *domain)
{
    return scmi_pm_domain_power(raw_to_scmi_pm_domain(domain), RT_FALSE);
}

static struct rt_dm_power_domain *scmi_pm_domain_proxy_ofw_parse(
        struct rt_dm_power_domain_proxy *proxy, struct rt_ofw_cell_args *args)
{
    struct scmi_pm_domain_proxy *scmi_proxy = raw_to_scmi_pm_domain_proxy(proxy);

    return &scmi_proxy->domains[args->args[0]].parent;
}

static rt_err_t scmi_pm_domain_probe(struct rt_scmi_device *sdev)
{
    rt_err_t err;
    rt_uint32_t num_domains;
    struct scmi_pm_domain *scmi_pds;
    struct scmi_pm_domain_proxy *scmi_proxy;
    struct scmi_power_attributes attr = {};
    struct rt_scmi_msg msg = RT_SCMI_MSG_OUT(SCMI_COM_MSG_ATTRIBUTES, &attr);

    if ((err = rt_scmi_process_msg(sdev, &msg)))
    {
        return err;
    }

    num_domains = rt_le16_to_cpu(attr.num_domains);
    scmi_proxy = rt_calloc(1, sizeof(*scmi_proxy) + sizeof(*scmi_pds) * num_domains);

    if (!scmi_proxy)
    {
        return -RT_ENOMEM;
    }

    scmi_proxy->sdev = sdev;
    scmi_proxy->num_domains = num_domains;

    scmi_pds = scmi_proxy->domains;

    for (int i = 0; i < num_domains; ++i, ++scmi_pds)
    {
        struct rt_dm_power_domain *domain = &scmi_pds->parent;

        domain->power_off = scmi_pd_power_off;
        domain->power_on = scmi_pd_power_on;

        scmi_pds->domain = i;
        scmi_pds->proxy = scmi_proxy;

        rt_dm_power_domain_register(domain);
    }

    scmi_proxy->parent.ofw_parse = scmi_pm_domain_proxy_ofw_parse;
    rt_dm_power_domain_proxy_ofw_bind(&scmi_proxy->parent, sdev->parent.ofw_node);

    return RT_EOK;
}

static const struct rt_scmi_device_id scmi_pm_domain_ids[] =
{
    { SCMI_PROTOCOL_ID_POWER, "genpd" },
    { /* sentinel */ },
};

static struct rt_scmi_driver scmi_pm_domain_driver =
{
    .name = "pm-domain-scmi",
    .ids = scmi_pm_domain_ids,

    .probe = scmi_pm_domain_probe,
};
RT_SCMI_DRIVER_EXPORT(scmi_pm_domain_driver);
