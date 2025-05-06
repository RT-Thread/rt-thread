/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2024-08-16     zhujiale     first version
 */
#include "sdhci-platform.h"

static const struct rt_sdhci_ops sdhci_pltfm_ops = {
    .set_clock         = rt_sdhci_set_clock,
    .set_bus_width     = rt_sdhci_set_bus_width,
    .reset             = rt_sdhci_reset,
    .set_uhs_signaling = rt_sdhci_set_uhs,
};

void rt_sdhci_get_property(struct rt_platform_device *pdev)
{
    struct rt_device        *dev        = &pdev->parent;
    struct rt_sdhci_host       *host       = pdev->priv;
    struct rt_sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
    rt_uint32_t              bus_width;

    if (rt_dm_dev_prop_read_bool(dev, "sdhci,auto-cmd12"))
        host->quirks |= RT_SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12;

    if (rt_dm_dev_prop_read_bool(dev, "sdhci,1-bit-only") || (rt_dm_dev_prop_read_u32(dev, "bus-width", &bus_width) == 0 && bus_width == 1))
        host->quirks |= RT_SDHCI_QUIRK_FORCE_1_BIT_DATA;

    if (rt_dm_dev_prop_read_bool(dev, "broken-cd"))
        host->quirks |= RT_SDHCI_QUIRK_BROKEN_CARD_DETECTION;

    if (rt_dm_dev_prop_read_bool(dev, "no-1-8-v"))
        host->quirks2 |= RT_SDHCI_QUIRK2_NO_1_8_V;

    rt_dm_dev_prop_read_u32(dev, "clock-frequency", &pltfm_host->clock);

    if (rt_dm_dev_prop_read_bool(dev, "keep-power-in-suspend"))
        host->mmc->pm_caps |= MMC_PM_KEEP_POWER;

    if (rt_dm_dev_prop_read_bool(dev, "wakeup-source") || rt_dm_dev_prop_read_bool(dev, "enable-sdio-wakeup")) /* legacy */
        host->mmc->pm_caps |= MMC_PM_WAKE_SDIO_IRQ;
}

struct rt_sdhci_host *rt_sdhci_pltfm_init(struct rt_platform_device     *pdev,
                                    const struct rt_sdhci_pltfm_data *pdata,
                                    size_t                         priv_size)
{
    struct rt_sdhci_host      *host;
    struct rt_device       *dev = &pdev->parent;
    void                   *ioaddr;
    int                     irq;

    ioaddr = rt_dm_dev_iomap(dev, 0);
    if (!ioaddr)
    {
        return RT_NULL;
    }

    irq = rt_dm_dev_get_irq(dev, 0);
    if (irq < 0)
    {
        return RT_NULL;
    }
    host = rt_sdhci_alloc_host(dev,sizeof(struct rt_sdhci_pltfm_host) + priv_size);
    if (!host)
    {
        return RT_NULL;
    }
    host->irq     = irq;
    host->ioaddr  = ioaddr;
    host->hw_name = rt_dm_dev_get_name(dev);

    if (pdata && pdata->ops)
        host->ops = pdata->ops;
    else
        host->ops = &sdhci_pltfm_ops;
    if (pdata)
    {
        host->quirks  = pdata->quirks;
        host->quirks2 = pdata->quirks2;
    }

    pdev->priv = host;

    return host;
}

int rt_sdhci_pltfm_init_and_add_host(struct rt_platform_device     *pdev,
                                  const struct rt_sdhci_pltfm_data *pdata,
                                  size_t                         priv_size)
{
    struct rt_sdhci_host *host;
    int                ret = 0;

    host = rt_sdhci_pltfm_init(pdev, pdata, priv_size);
    if (!host)
        return -RT_ERROR;

    rt_sdhci_get_property(pdev);

    ret = rt_sdhci_init_host(host);
    if (ret)
        rt_sdhci_pltfm_free(pdev);

    return ret;
}

void rt_sdhci_pltfm_free(struct rt_platform_device *pdev)
{
    struct rt_sdhci_host *host = pdev->priv;

    rt_sdhci_free_host(host);
}

void rt_sdhci_pltfm_remove(struct rt_platform_device *pdev)
{
    struct rt_sdhci_host *host = pdev->priv;
    int dead = (readl(host->ioaddr + RT_SDHCI_INT_STATUS) == 0xffffffff);

    rt_sdhci_uninit_host(host, dead);
    rt_sdhci_pltfm_free(pdev);
}
