/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-30     RT-Thread    first version
 */

#include "sdhci-dwcmshc-platform.h"

rt_err_t sdhci_dwcmshc_platform_register(struct rt_platform_device *pdev,
                                         const struct sdhci_dwcmshc_drv_data *drv_data)
{
    return sdhci_dwcmshc_probe(pdev, drv_data);
}

static rt_err_t sdhci_dwcmshc_platform_probe(struct rt_platform_device *pdev)
{
    const struct sdhci_dwcmshc_drv_data *drv_data = RT_NULL;

    if (pdev->parent.ofw_node)
    {
        drv_data = pdev->id->data;
    }

    if (!drv_data)
    {
        drv_data = &sdhci_dwcmshc_generic_drv_data;
    }

    return sdhci_dwcmshc_platform_register(pdev, drv_data);
}

static rt_err_t sdhci_dwcmshc_platform_remove(struct rt_platform_device *pdev)
{
    return sdhci_dwcmshc_remove(pdev);
}

static const struct rt_ofw_node_id sdhci_dwcmshc_platform_ofw_ids[] = {
    {
        .compatible = "snps,dwcmshc-sdhci",
        .data = &sdhci_dwcmshc_generic_drv_data,
    },
    { /* sentinel */ }
};

static struct rt_platform_driver sdhci_dwcmshc_platform_driver = {
    .name = "sdhci-dwcmshc",
    .ids = sdhci_dwcmshc_platform_ofw_ids,

    .probe = sdhci_dwcmshc_platform_probe,
    .remove = sdhci_dwcmshc_platform_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sdhci_dwcmshc_platform_driver);
