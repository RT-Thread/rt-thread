/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2024-08-16     zhujiale     first version
 */

#ifndef __DEV_SDHCI_DM_H__
#define __DEV_SDHCI_DM_H__

#include <rtthread.h>
#include <rtdevice.h>

struct rt_sdhci_pltfm_data
{
    const struct rt_sdhci_ops *ops;
    rt_uint32_t quirks;
    rt_uint32_t quirks2;
};

struct rt_sdhci_pltfm_host
{
    struct rt_clk *clk;
    rt_uint32_t clock;
    rt_uint16_t xfer_mode_shadow;

    rt_ubase_t private[];
};

void rt_sdhci_get_property(struct rt_platform_device *pdev);

rt_inline void rt_sdhci_get_of_property(struct rt_platform_device *pdev)
{
    return rt_sdhci_get_property(pdev);
}

extern struct rt_sdhci_host *rt_sdhci_pltfm_init(struct rt_platform_device *pdev,
                                                 const struct rt_sdhci_pltfm_data *pdata,
                                                 rt_size_t priv_size);
extern void rt_sdhci_pltfm_free(struct rt_platform_device *pdev);

extern rt_err_t rt_sdhci_pltfm_init_and_add_host(struct rt_platform_device *pdev,
                                                 const struct rt_sdhci_pltfm_data *pdata,
                                                 rt_size_t priv_size);

extern rt_err_t rt_sdhci_pltfm_remove(struct rt_platform_device *pdev);

extern rt_uint32_t rt_sdhci_pltfm_clk_get_max_clock(struct rt_sdhci_host *host);

rt_inline void *rt_sdhci_pltfm_priv(struct rt_sdhci_pltfm_host *host)
{
    return host->private;
}

rt_inline rt_err_t rt_sdhci_pltfm_suspend(struct rt_device *dev)
{
    return RT_EOK;
}

rt_inline rt_err_t rt_sdhci_pltfm_resume(struct rt_device *dev)
{
    return RT_EOK;
}

#endif /* __DEV_SDHCI_DM_H__ */
