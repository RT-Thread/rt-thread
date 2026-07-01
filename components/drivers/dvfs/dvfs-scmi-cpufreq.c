/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/scmi.h>

#define DBG_TAG "dvfs.scmi.cpufreq"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct scmi_cpufreq
{
    struct rt_scmi_device *sdev;
    int domain_id;
    struct rt_dvfs_cpufreq cpufreq;
};

static rt_err_t scmi_perf_level_set(struct scmi_cpufreq *scmi_cpufreq, rt_uint64_t level)
{
    struct scmi_perf_level_set_in in =
    {
        .flags = rt_cpu_to_le32(0),
        .domain = rt_cpu_to_le32(scmi_cpufreq->domain_id),
        .level_lsb = rt_cpu_to_le32((rt_uint32_t)level),
        .level_msb = rt_cpu_to_le32((rt_uint32_t)(level >> 32)),
    };
    struct scmi_perf_level_set_out out;
    struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_PERF_LEVEL_SET, &in, &out);

    return rt_scmi_process_msg(scmi_cpufreq->sdev, &msg);
}

static rt_err_t scmi_cpufreq_set_opp(struct rt_dvfs_scaling *scaling, struct rt_dvfs_opp *opp)
{
    struct rt_dvfs_devfreq *devfreq = rt_container_of(scaling, struct rt_dvfs_devfreq, parent);
    struct scmi_cpufreq *scmi_cpufreq = rt_container_of(devfreq, struct scmi_cpufreq, cpufreq.parent);

    if (!opp)
    {
        return -RT_EINVAL;
    }

    return scmi_perf_level_set(scmi_cpufreq, opp->freq);
}

static rt_err_t scmi_cpufreq_add_opps(struct scmi_cpufreq *scmi_cpufreq)
{
    struct rt_dvfs_scaling *dvfs = rt_dvfs_cpufreq_to_scaling(&scmi_cpufreq->cpufreq);
    struct scmi_perf_describe_levels_in in =
    {
        .domain = rt_cpu_to_le32(scmi_cpufreq->domain_id),
        .level_index = rt_cpu_to_le32(0),
    };
    struct scmi_perf_describe_levels_out *out;
    rt_size_t out_size = sizeof(*out) + sizeof(struct scmi_perf_level) * SCMI_MAX_NUM_RATES;
    rt_err_t err;
    rt_uint32_t i, num_levels;

    out = rt_calloc(1, out_size);
    if (!out)
    {
        return -RT_ENOMEM;
    }

    do
    {
        struct rt_scmi_msg msg = RT_SCMI_MSG_RAW(SCMI_PERF_DESCRIBE_LEVELS,
                &in, sizeof(in), out, out_size);

        err = rt_scmi_process_msg(scmi_cpufreq->sdev, &msg);
        if (err)
        {
            break;
        }

        num_levels = rt_le32_to_cpu(out->num_levels) & 0xfff;

        for (i = 0; i < num_levels; ++i)
        {
            rt_uint64_t hz = SCMI_PERF_LEVEL_TO_U64(out->level[i]);
            struct rt_dvfs_opp *opp;

            if (!hz)
            {
                continue;
            }

            opp = rt_dvfs_scaling_add_opp(dvfs, (rt_ubase_t)hz, 0);
            if (opp)
            {
                opp->available = RT_TRUE;
                opp->power = rt_le32_to_cpu(out->level[i].power) / 1000;
            }
        }

        in.level_index = rt_cpu_to_le32(rt_le32_to_cpu(in.level_index) + num_levels);
    } while ((rt_le32_to_cpu(out->num_levels) >> 16) > 0);

    rt_free(out);

    return err;
}

static struct rt_dvfs_scaling_ops scmi_cpufreq_ops =
{
    .set_opp = scmi_cpufreq_set_opp,
};

static rt_err_t scmi_cpufreq_probe(struct rt_scmi_device *sdev)
{
    struct scmi_cpufreq *scmi_cpufreq;
    struct scmi_perf_attributes attr;
    struct rt_scmi_msg msg = RT_SCMI_MSG_OUT(SCMI_COM_MSG_ATTRIBUTES, &attr);
    rt_err_t err;
    int domain;

    if ((err = rt_scmi_process_msg(sdev, &msg)))
    {
        LOG_E("Get SCMI perf attributes failed: %s", rt_strerror(err));
        return err;
    }

    if (!(scmi_cpufreq = rt_calloc(1, sizeof(*scmi_cpufreq))))
    {
        return -RT_ENOMEM;
    }

    scmi_cpufreq->sdev = sdev;

    for (domain = 0; domain < rt_le16_to_cpu(attr.num_domains); ++domain)
    {
        struct scmi_perf_domain_attr_in domain_in =
        {
            .domain = rt_cpu_to_le32(domain),
        };
        struct scmi_perf_domain_attr_out domain_out;
        struct rt_scmi_msg domain_msg = RT_SCMI_MSG_IN_OUT(SCMI_PERF_DOMAIN_ATTRIBUTES,
                &domain_in, &domain_out);

        rt_memset(&scmi_cpufreq->cpufreq, 0, sizeof(scmi_cpufreq->cpufreq));

        if ((err = rt_scmi_process_msg(sdev, &domain_msg)))
        {
            continue;
        }

        scmi_cpufreq->domain_id = domain;
        rt_dvfs_cpufreq_to_scaling(&scmi_cpufreq->cpufreq)->ops = &scmi_cpufreq_ops;
        rt_dvfs_cpufreq_to_scaling(&scmi_cpufreq->cpufreq)->dev = &sdev->parent;
        scmi_cpufreq->cpufreq.master_cpu = 0;

        if ((err = scmi_cpufreq_add_opps(scmi_cpufreq)))
        {
            LOG_W("Domain %d: add OPPs failed: %s", domain, rt_strerror(err));
            rt_dvfs_scaling_remove_opp_all(rt_dvfs_cpufreq_to_scaling(&scmi_cpufreq->cpufreq));
            continue;
        }

        if ((err = rt_dvfs_cpufreq_register(&scmi_cpufreq->cpufreq)))
        {
            LOG_E("Domain %d: register cpufreq failed: %s", domain, rt_strerror(err));
            rt_dvfs_scaling_remove_opp_all(rt_dvfs_cpufreq_to_scaling(&scmi_cpufreq->cpufreq));
            continue;
        }

        err = rt_dvfs_scaling_set_governor(rt_dvfs_cpufreq_to_scaling(&scmi_cpufreq->cpufreq),
                RT_DVFS_GOVERNOR_TYPE_ONDEMAND);
        if (err)
        {
            rt_dvfs_scaling_set_governor(rt_dvfs_cpufreq_to_scaling(&scmi_cpufreq->cpufreq),
                    RT_DVFS_GOVERNOR_TYPE_PERFORMANCE);
        }

        LOG_D("SCMI cpufreq domain %d registered, freq range: %lu-%lu Hz",
              domain,
              rt_dvfs_cpufreq_to_scaling(&scmi_cpufreq->cpufreq)->min_freq,
              rt_dvfs_cpufreq_to_scaling(&scmi_cpufreq->cpufreq)->max_freq);

        sdev->parent.user_data = scmi_cpufreq;
        return RT_EOK;
    }

    rt_free(scmi_cpufreq);

    return -RT_ENOSYS;
}

static rt_err_t scmi_cpufreq_remove(struct rt_scmi_device *sdev)
{
    struct scmi_cpufreq *scmi_cpufreq = sdev->parent.user_data;

    if (scmi_cpufreq)
    {
        rt_dvfs_cpufreq_unregister(&scmi_cpufreq->cpufreq);
        rt_dvfs_scaling_remove_opp_all(rt_dvfs_cpufreq_to_scaling(&scmi_cpufreq->cpufreq));
        rt_free(scmi_cpufreq);
        sdev->parent.user_data = RT_NULL;
    }

    return RT_EOK;
}

static const struct rt_scmi_device_id scmi_cpufreq_ids[] =
{
    { SCMI_PROTOCOL_ID_PERF, "cpufreq" },
    { 0, RT_NULL },
};

static struct rt_scmi_driver scmi_cpufreq_driver =
{
    .name = "scmi-cpufreq",
    .ids = scmi_cpufreq_ids,
    .probe = scmi_cpufreq_probe,
    .remove = scmi_cpufreq_remove,
};

static int scmi_cpufreq_init(void)
{
    rt_scmi_driver_register(&scmi_cpufreq_driver);

    return 0;
}
INIT_DEVICE_EXPORT(scmi_cpufreq_init);
