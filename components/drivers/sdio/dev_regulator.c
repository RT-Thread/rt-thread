/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#include "dev_sdio_dm.h"

#define DBG_TAG               "SDIO"
#ifdef RT_SDIO_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* RT_SDIO_DEBUG */
#include <rtdbg.h>

static rt_err_t ocrbitnum_to_vdd(int vdd_bit, int *min_uvolt, int *max_uvolt)
{
    int tmp;

    if (!vdd_bit)
    {
        return -RT_EINVAL;
    }

    tmp = vdd_bit - rt_ilog2(VDD_165_195);

    if (tmp == 0)
    {
        *min_uvolt = 1650 * 1000;
        *max_uvolt = 1950 * 1000;
    }
    else
    {
        *min_uvolt = 1900 * 1000 + tmp * 100 * 1000;
        *max_uvolt = *min_uvolt + 100 * 1000;
    }

    return 0;
}

rt_err_t sdio_regulator_set_ocr(struct rt_mmcsd_host *host,
        struct rt_regulator *supply, rt_uint16_t vdd_bit)
{
    rt_err_t err = RT_EOK;

    if (!host)
    {
        return -RT_EINVAL;
    }

    if (rt_is_err_or_null(supply))
    {
        return RT_EOK;
    }

    if (vdd_bit)
    {
        int min_uvolt, max_uvolt;

        ocrbitnum_to_vdd(vdd_bit, &min_uvolt, &max_uvolt);

        err = rt_regulator_set_voltage(supply, min_uvolt, max_uvolt);

        if (!err && host->supply.regulator_enabled)
        {
            err = rt_regulator_enable(supply);

            if (!err)
            {
                host->supply.regulator_enabled = RT_TRUE;
            }
        }
    }
    else if (host->supply.regulator_enabled)
    {
        err = rt_regulator_disable(supply);

        if (!err)
        {
            host->supply.regulator_enabled = RT_FALSE;
        }
    }

    if (err)
    {
        LOG_E("Set regulator OCR %d error = %s", vdd_bit, rt_strerror(err));
    }

    return err;
}

static int regulator_set_voltage_if_supported(struct rt_regulator *regulator,
        int min_uvolt, int target_uvolt, int max_uvolt)
{
    if (!rt_regulator_is_supported_voltage(regulator, min_uvolt, max_uvolt))
    {
        return -RT_EINVAL;
    }

    if (rt_regulator_get_voltage(regulator) == target_uvolt)
    {
        return RT_EOK;
    }

    return rt_regulator_set_voltage_triplet(regulator, min_uvolt, target_uvolt,
            max_uvolt);
}

rt_err_t sdio_regulator_set_vqmmc(struct rt_mmcsd_host *host,
        struct rt_mmcsd_io_cfg *ios)
{
    rt_err_t err;
    int uvolt, min_uvolt, max_uvolt;

    if (rt_is_err_or_null(host->supply.vqmmc))
    {
        return -RT_EINVAL;
    }

    switch (ios->signal_voltage)
    {
    case MMCSD_SIGNAL_VOLTAGE_120:
        return regulator_set_voltage_if_supported(host->supply.vqmmc,
                1100000, 1200000, 1300000);

    case MMCSD_SIGNAL_VOLTAGE_180:
        return regulator_set_voltage_if_supported(host->supply.vqmmc,
                1700000, 1800000, 1950000);

    case MMCSD_SIGNAL_VOLTAGE_330:
        err = ocrbitnum_to_vdd(host->io_cfg.vdd, &uvolt, &max_uvolt);

        if (err)
        {
            return err;
        }

        min_uvolt = rt_max(uvolt - 300000, 2700000);
        max_uvolt = rt_min(max_uvolt + 200000, 3600000);

        err = regulator_set_voltage_if_supported(host->supply.vqmmc,
                min_uvolt, uvolt, max_uvolt);
        if (err >= 0)
        {
            return err;
        }

        return regulator_set_voltage_if_supported(host->supply.vqmmc,
                2700000, uvolt, 3600000);

    default:
        return -RT_EINVAL;
    }
}

rt_err_t sdio_regulator_get_supply(struct rt_device *dev, struct rt_mmcsd_host *host)
{
    rt_err_t err;

    if (!dev || !host)
    {
        return -RT_EINVAL;
    }

    host->supply.vmmc = rt_regulator_get(dev, "vmmc");
    host->supply.vqmmc = rt_regulator_get(dev, "vqmmc");

    if (!rt_is_err(host->supply.vmmc))
    {
        if (!host->supply.vmmc)
        {
            LOG_D("No vmmc regulator found");
        }
    }
    else
    {
        err = rt_ptr_err(host->supply.vmmc);
        goto _fail;
    }

    if (!rt_is_err(host->supply.vqmmc))
    {
        if (host->supply.vqmmc)
        {
            LOG_D("No vqmmc regulator found");
        }
    }
    else
    {
        err = rt_ptr_err(host->supply.vqmmc);
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (!rt_is_err_or_null(host->supply.vmmc))
    {
        rt_regulator_put(host->supply.vmmc);
        host->supply.vmmc = RT_NULL;
    }

    if (!rt_is_err_or_null(host->supply.vqmmc))
    {
        rt_regulator_put(host->supply.vqmmc);
        host->supply.vqmmc = RT_NULL;
    }

    return err;
}

rt_err_t sdio_regulator_enable_vqmmc(struct rt_mmcsd_host *host)
{
    struct rt_mmcsd_supply *supply;

    if (!host)
    {
        return -RT_EINVAL;
    }

    supply = &host->supply;

    if (!rt_is_err_or_null(supply->vqmmc) && !supply->vqmmc_enabled)
    {
        rt_err_t err = rt_regulator_enable(supply->vqmmc);

        if (err)
        {
            LOG_E("Enabling vqmmc regulator failed error = %s", rt_strerror(err));
        }
        else
        {
            supply->vqmmc_enabled = RT_TRUE;
        }
    }

    return RT_EOK;
}

void sdio_regulator_disable_vqmmc(struct rt_mmcsd_host *host)
{
    struct rt_mmcsd_supply *supply;

    if (!host)
    {
        return;
    }

    supply = &host->supply;

    if (!rt_is_err_or_null(supply->vqmmc) && supply->vqmmc_enabled)
    {
        rt_regulator_disable(supply->vqmmc);

        supply->vqmmc_enabled = RT_FALSE;
    }
}
