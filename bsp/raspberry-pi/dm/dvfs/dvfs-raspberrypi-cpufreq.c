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

#define DBG_TAG "dvfs.raspberrypi-cpufreq"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/misc.h>
#include <drivers/byteorder.h>
#include <dvfs-raspberrypi-cpufreq.h>

#define RASPBERRYPI_FREQ_INTERVAL   100000000

static rt_err_t raspberrypi_firmware_clk_rate(struct rpi_firmware *rpi_fw,
        rt_uint32_t tag, rt_uint32_t id, rt_uint32_t *rate)
{
    struct rpi_firmware_clk_rate_request msg =
    {
        .id = rt_cpu_to_le32(id),
    };

    if (!rpi_fw || !rate)
    {
        return -RT_EINVAL;
    }

    if (rpi_firmware_property(rpi_fw, tag, &msg, sizeof(msg)))
    {
        return -RT_EIO;
    }

    *rate = rt_le32_to_cpu(msg.rate);

    return RT_EOK;
}

static rt_err_t raspberrypi_arm_clk_get_range(struct rt_clk *arm_clk,
        struct rpi_firmware *rpi_fw, rt_ubase_t *min, rt_ubase_t *max)
{
    rt_uint32_t min_hz = 0, max_hz = 0;

    if (!arm_clk || !min || !max)
    {
        return -RT_EINVAL;
    }

    if (arm_clk->min_rate && arm_clk->max_rate)
    {
        *min = arm_clk->min_rate;
        *max = arm_clk->max_rate;
        return RT_EOK;
    }

    if (!rpi_fw)
    {
        LOG_E("ARM clk range missing and no firmware handle");
        return -RT_EINVAL;
    }

    if (raspberrypi_firmware_clk_rate(rpi_fw, RPI_FIRMWARE_GET_MIN_CLOCK_RATE,
            RPI_FIRMWARE_ARM_CLK_ID, &min_hz))
    {
        LOG_E("firmware %s for ARM failed", "GET_MIN_CLOCK_RATE");
        return -RT_EIO;
    }

    if (raspberrypi_firmware_clk_rate(rpi_fw, RPI_FIRMWARE_GET_MAX_CLOCK_RATE,
            RPI_FIRMWARE_ARM_CLK_ID, &max_hz))
    {
        LOG_E("firmware %s for ARM failed", "GET_MAX_CLOCK_RATE");
        return -RT_EIO;
    }

    if (!min_hz || !max_hz || min_hz > max_hz)
    {
        LOG_E("firmware ARM range invalid: %u-%u Hz", min_hz, max_hz);
        return -RT_EINVAL;
    }

    rt_clk_set_rate_range(arm_clk, min_hz, max_hz);
    *min = min_hz;
    *max = max_hz;

    return RT_EOK;
}

static void raspberrypi_cpufreq_cleanup(struct rt_dvfs_scaling *scaling,
        struct rt_dvfs_cpufreq *cpufreq)
{
    if (scaling && scaling->opp_table)
    {
        rt_dvfs_scaling_remove_opp_all(scaling);
    }

    rt_free(cpufreq);
}

/*
 * Board-specific helper: build the OPP table and hand the cpufreq object
 * to the generic "ofw-cpufreq" platform driver (see dvfs-ofw.c).
 */
rt_err_t raspberrypi_cpufreq_register(struct rt_clk *arm_clk, struct rt_ofw_node *cpu_np,
        struct rpi_firmware *rpi_fw)
{
    rt_err_t err;
    rt_ubase_t min, max, rate;
    rt_uint32_t opp_count = 0;
    struct rt_dvfs_cpufreq *cpufreq;
    struct rt_dvfs_scaling *scaling;
    struct rt_platform_device *pdev;

    if (!arm_clk || rt_is_err_or_null(arm_clk) || !cpu_np)
    {
        return -RT_EINVAL;
    }

    if (!(cpufreq = rt_calloc(1, sizeof(*cpufreq))))
    {
        return -RT_ENOMEM;
    }

    scaling = rt_dvfs_cpufreq_to_scaling(cpufreq);
    scaling->clk = arm_clk;
    /*
     * VideoCore owns voltage/thermal mitigation; no extra settling time is
     * needed after firmware clock changes.
     */
    scaling->transition_latency = 0;
    scaling->retry_delay = 100000;
    rt_memset(cpufreq->cpus_map, 0xff, sizeof(cpufreq->cpus_map));

    if ((err = raspberrypi_arm_clk_get_range(arm_clk, rpi_fw, &min, &max)))
    {
        LOG_E("ARM clock range unavailable: %s", rt_strerror(err));
        raspberrypi_cpufreq_cleanup(scaling, cpufreq);
        return err;
    }

    min = rt_roundup(min, RASPBERRYPI_FREQ_INTERVAL);
    max = rt_roundup(max, RASPBERRYPI_FREQ_INTERVAL);

    if (!min || !max || min > max)
    {
        LOG_E("invalid ARM clock range: %lu-%lu Hz", min, max);
        raspberrypi_cpufreq_cleanup(scaling, cpufreq);
        return -RT_EINVAL;
    }

    for (rate = min; rate <= max; rate += RASPBERRYPI_FREQ_INTERVAL)
    {
        if (!rt_dvfs_scaling_add_opp(scaling, rate, 0))
        {
            LOG_E("failed to add OPP %lu Hz (added %u so far)", rate, opp_count);
            raspberrypi_cpufreq_cleanup(scaling, cpufreq);
            return -RT_ERROR;
        }

        ++opp_count;
    }

    /*
     * Keep the current boot frequency. ofw_dvfs_setup() eventually calls
     * rt_dvfs_scaling_register(), which skips dvfs_scaling_init_frequency()
     * when cur_freq is already set.
     */
    rate = rt_clk_get_rate(arm_clk);

    if (rate)
    {
        struct rt_dvfs_opp *opp = rt_dvfs_scaling_find_floor_opp(scaling, rate);

        if (!opp)
        {
            opp = rt_dvfs_scaling_find_ceil_opp(scaling, rate);
        }

        if (opp)
        {
            scaling->cur_freq = opp->freq;
        }
        else
        {
            LOG_W("no matching OPP for current rate %lu Hz", rate);
        }
    }

    if (!(pdev = rt_platform_device_alloc("ofw-cpufreq")))
    {
        LOG_E("alloc ofw-cpufreq failed");
        err = -RT_ENOMEM;
        goto _free_cpufreq;
    }

    pdev->priv = cpufreq;

    rt_dm_dev_set_name_auto(&pdev->parent, "cpufreq");

    if ((err = rt_device_register(&pdev->parent, rt_dm_dev_get_name(&pdev->parent),
            RT_DEVICE_FLAG_DEACTIVATE)))
    {
        goto _free;
    }

    if ((err = rt_platform_device_register(pdev)))
    {
        goto _unregister;
    }

    if (!pdev->parent.drv)
    {
        err = -RT_ERROR;
        goto _free_bus;
    }

    return RT_EOK;
_free_bus:
    rt_bus_remove_device(&pdev->parent);
_unregister:
    rt_device_unregister(&pdev->parent);
_free:
    rt_free(pdev);
_free_cpufreq:
    raspberrypi_cpufreq_cleanup(scaling, cpufreq);
    return err;
}

static int raspberrypi_dvfs_cpufreq_init(void)
{
    rt_err_t err;
    struct rt_clk *arm_clk;
    struct rt_ofw_node *cpu_np, *fw_np;
    struct rpi_firmware *rpi_fw = RT_NULL;

    if (!(arm_clk = raspberrypi_arm_clk_get()))
    {
        LOG_E("ARM clock not ready, skip cpufreq");
        return 0;
    }

    if (!(cpu_np = rt_ofw_get_next_cpu_node(RT_NULL)))
    {
        LOG_E("no CPU node, skip cpufreq");
        return 0;
    }

    if ((fw_np = rpi_firmware_find_node()))
    {
        rpi_fw = rpi_firmware_get(fw_np);
    }

    err = raspberrypi_cpufreq_register(arm_clk, cpu_np, rpi_fw);

    if (rpi_fw)
    {
        rpi_firmware_put(rpi_fw);
    }
    rt_ofw_node_put(cpu_np);

    if (err)
    {
        LOG_W("cpufreq init failed: %s", rt_strerror(err));
    }

    return 0;
}
INIT_ENV_EXPORT(raspberrypi_dvfs_cpufreq_init);
