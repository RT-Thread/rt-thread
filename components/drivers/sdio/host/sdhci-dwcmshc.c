/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-30     RT-Thread    first version
 */

#include "sdhci-dwcmshc.h"

#include <drivers/dev_sdhci_host.h>

#define DBG_TAG "sdhci.dwcmshc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static unsigned int sdhci_dwcmshc_get_max_clock(struct rt_sdhci_host *host)
{
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);

    if (pltfm_host->clk)
    {
        return rt_sdhci_pltfm_clk_get_max_clock(host);
    }

    return pltfm_host->clock;
}

static void sdhci_dwcmshc_check_auto_cmd23(struct rt_mmc_host *mmc, struct rt_mmcsd_req *mrq)
{
    struct rt_sdhci_host *host = rt_mmc_priv(mmc);

    /*
     * No matter V4 is enabled or not, ARGUMENT2 register is 32-bit
     * block count register which doesn't support stuff bits of
     * CMD23 argument on dwcmshc host controller.
     */
    if (mrq->sbc && (mrq->sbc->arg & SDHCI_DWCMSHC_ARG2_STUFF))
    {
        host->flags &= ~RT_SDHCI_AUTO_CMD23;
    }
    else
    {
        host->flags |= RT_SDHCI_AUTO_CMD23;
    }
}

static void sdhci_dwcmshc_request(struct rt_mmc_host *mmc, struct rt_mmcsd_req *mrq)
{
    sdhci_dwcmshc_check_auto_cmd23(mmc, mrq);

    rt_sdhci_start_request(mmc, mrq);
}

void sdhci_dwcmshc_set_uhs_signaling(struct rt_sdhci_host *host, unsigned int timing)
{
    rt_uint16_t ctrl_2;
    rt_uint32_t ctrl;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct sdhci_dwcmshc *priv = rt_sdhci_pltfm_priv(pltfm_host);

    ctrl_2 = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);

    /* Select Bus Speed Mode for host */
    ctrl_2 &= ~RT_SDHCI_CTRL_UHS_MASK;
    if (timing == MMC_TIMING_MMC_HS200 || timing == MMC_TIMING_UHS_SDR104)
    {
        ctrl_2 |= RT_SDHCI_CTRL_UHS_SDR104;
    }
    else if (timing == MMC_TIMING_UHS_SDR12)
    {
        ctrl_2 |= RT_SDHCI_CTRL_UHS_SDR12;
    }
    else if (timing == MMC_TIMING_UHS_SDR25 || timing == MMC_TIMING_MMC_HS)
    {
        ctrl_2 |= RT_SDHCI_CTRL_UHS_SDR25;
    }
    else if (timing == MMC_TIMING_UHS_SDR50)
    {
        ctrl_2 |= RT_SDHCI_CTRL_UHS_SDR50;
    }
    else if (timing == MMC_TIMING_UHS_DDR50 || timing == MMC_TIMING_MMC_DDR52)
    {
        ctrl_2 |= RT_SDHCI_CTRL_UHS_DDR50;
    }
    else if (timing == MMC_TIMING_MMC_HS400)
    {
        /* Set CARD_IS_EMMC bit to enable Data Strobe for HS400 */
        ctrl = rt_sdhci_readl(host, priv->vendor_specific_area1 + DWCMSHC_EMMC_CONTROL);
        ctrl |= DWCMSHC_CARD_IS_EMMC;
        rt_sdhci_writel(host, ctrl, priv->vendor_specific_area1 + DWCMSHC_EMMC_CONTROL);

        ctrl_2 |= DWCMSHC_CTRL_HS400;
    }

    rt_sdhci_writew(host, ctrl_2, RT_SDHCI_HOST_CONTROL2);
}

static void sdhci_dwcmshc_hs400_enhanced_strobe(struct rt_mmc_host *mmc, struct rt_mmcsd_io_cfg *ios)
{
    int reg;
    rt_uint32_t vendor;
    struct rt_sdhci_host *host = rt_mmc_priv(mmc);
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct sdhci_dwcmshc *priv = rt_sdhci_pltfm_priv(pltfm_host);

    reg = priv->vendor_specific_area1 + DWCMSHC_EMMC_CONTROL;
    vendor = rt_sdhci_readl(host, reg);

    if (ios->enhanced_strobe)
    {
        vendor |= DWCMSHC_ENHANCED_STROBE;
    }
    else
    {
        vendor &= ~DWCMSHC_ENHANCED_STROBE;
    }

    rt_sdhci_writel(host, vendor, reg);
}

static int sdhci_dwcmshc_execute_tuning(struct rt_mmc_host *mmc, rt_uint32_t opcode)
{
    int err;
    struct rt_sdhci_host *host = rt_mmc_priv(mmc);

    if ((err = rt_sdhci_execute_tuning(mmc, opcode)))
    {
        return err;
    }

    /*
     * Tuning can leave the IP in an active state (Buffer Read Enable bit
     * set) which prevents the entry to low power states (i.e. S0i3). Data
     * reset will clear it.
     */
    rt_sdhci_reset(host, RT_SDHCI_RESET_DATA);

    return 0;
}

static void sdhci_dwcmshc_disable_card_clk(struct rt_sdhci_host *host)
{
    rt_uint16_t ctrl;

    ctrl = rt_sdhci_readw(host, RT_SDHCI_CLOCK_CONTROL);
    if (ctrl & RT_SDHCI_CLOCK_CARD_EN)
    {
        ctrl &= ~RT_SDHCI_CLOCK_CARD_EN;
        rt_sdhci_writew(host, ctrl, RT_SDHCI_CLOCK_CONTROL);
    }
}

static const struct rt_sdhci_ops sdhci_dwcmshc_ops = {
    .set_clock = rt_sdhci_set_clock,
    .set_bus_width = rt_sdhci_set_bus_width,
    .set_uhs_signaling = sdhci_dwcmshc_set_uhs_signaling,
    .get_max_clock = sdhci_dwcmshc_get_max_clock,
    .reset = rt_sdhci_reset,
};

static const struct rt_sdhci_pltfm_data sdhci_dwcmshc_pdata = {
    .ops = &sdhci_dwcmshc_ops,
    .quirks = RT_SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
    .quirks2 = RT_SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
};

const struct sdhci_dwcmshc_drv_data sdhci_dwcmshc_generic_drv_data = {
    .pdata = &sdhci_dwcmshc_pdata,
};

#ifdef RT_USING_PM
static rt_err_t sdhci_dwcmshc_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    rt_uint16_t data;
    struct rt_sdhci_host *host = device->user_data;

    data = rt_sdhci_readw(host, RT_SDHCI_CLOCK_CONTROL);
    data &= ~RT_SDHCI_CLOCK_CARD_EN;
    rt_sdhci_writew(host, data, RT_SDHCI_CLOCK_CONTROL);

    return RT_EOK;
}

static void sdhci_dwcmshc_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    rt_uint16_t data;
    struct rt_sdhci_host *host = device->user_data;

    data = rt_sdhci_readw(host, RT_SDHCI_CLOCK_CONTROL);
    data |= RT_SDHCI_CLOCK_CARD_EN;
    rt_sdhci_writew(host, data, RT_SDHCI_CLOCK_CONTROL);
}

static const struct rt_device_pm_ops sdhci_dwcmshc_pm_ops = {
    .suspend = sdhci_dwcmshc_pm_suspend,
    .resume = sdhci_dwcmshc_pm_resume,
};
#endif /* RT_USING_PM */

rt_err_t sdhci_dwcmshc_probe(struct rt_platform_device *pdev,
                             const struct sdhci_dwcmshc_drv_data *drv_data)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rt_sdhci_pltfm_host *pltfm_host;
    struct rt_sdhci_host *host;
    struct sdhci_dwcmshc *priv;

    if (!drv_data || !drv_data->pdata)
    {
        return -RT_EINVAL;
    }

    host = rt_sdhci_pltfm_init(pdev, drv_data->pdata, sizeof(struct sdhci_dwcmshc));

    if (rt_is_err(host))
    {
        return rt_ptr_err(host);
    }

    pltfm_host = rt_sdhci_priv(host);
    priv = rt_sdhci_pltfm_priv(pltfm_host);
    priv->drv_data = drv_data;

    pltfm_host->clk = rt_clk_get_by_name(dev, "core");
    if (rt_is_err(pltfm_host->clk))
    {
        err = rt_ptr_err(pltfm_host->clk);
        LOG_E("failed to get core clk %s", rt_strerror(err));
        goto _free_pltfm;
    }

    err = rt_clk_prepare_enable(pltfm_host->clk);
    if (err)
    {
        goto _err_clk;
    }

    priv->bus_clk = rt_clk_get_by_name(dev, "bus");
    if (!rt_is_err(priv->bus_clk))
    {
        err = rt_clk_prepare_enable(priv->bus_clk);
        if (err)
        {
            LOG_E("failed to enable bus clk %s", rt_strerror(err));
            goto _err_core_clk;
        }
    }

    err = rt_mmc_of_parse(host->mmc);
    if (err)
    {
        goto _err_clk;
    }

    rt_sdhci_get_of_property(pdev);

    priv->vendor_specific_area1 = rt_sdhci_readl(host, DWCMSHC_P_VENDOR_AREA1) & DWCMSHC_AREA1_MASK;

    host->mmc_host_ops.request = sdhci_dwcmshc_request;
    host->mmc_host_ops.hs400_enhanced_strobe = sdhci_dwcmshc_hs400_enhanced_strobe;
    host->mmc_host_ops.execute_tuning = sdhci_dwcmshc_execute_tuning;

    if (drv_data->init)
    {
        if ((err = drv_data->init(host, priv)))
        {
            goto _err_clk;
        }
    }

    if (rt_sdhci_readl(host, RT_SDHCI_CAPABILITIES) & RT_SDHCI_CAN_64BIT_V4)
    {
        rt_sdhci_enable_v4_mode(host);
    }

    err = rt_sdhci_setup_host(host);
    if (err)
    {
        goto _err_setup_host;
    }

    if (drv_data->postinit)
    {
        drv_data->postinit(host, priv);
    }

    err = rt_sdhci_init_host(host);
    if (err)
    {
        goto _err_setup_host;
    }

#ifdef RT_USING_PM
    dev->user_data = host;
    rt_pm_device_register(dev, &sdhci_dwcmshc_pm_ops);
#endif

    return RT_EOK;

_err_setup_host:
    rt_sdhci_cleanup_host(host);

_err_clk:
    if (drv_data->remove)
    {
        drv_data->remove(host, priv);
    }

    if (!rt_is_err(priv->bus_clk))
    {
        rt_clk_disable_unprepare(priv->bus_clk);
    }

_err_core_clk:
    if (!rt_is_err(pltfm_host->clk))
    {
        rt_clk_disable_unprepare(pltfm_host->clk);
    }

_free_pltfm:
    rt_sdhci_pltfm_free(pdev);

    return err;
}

rt_err_t sdhci_dwcmshc_remove(struct rt_platform_device *pdev)
{
    struct rt_sdhci_host *host = pdev->priv;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct sdhci_dwcmshc *priv = rt_sdhci_pltfm_priv(pltfm_host);

#ifdef RT_USING_PM
    rt_pm_device_unregister(&pdev->parent);
#endif

    rt_sdhci_uninit_host(host, 0);

    sdhci_dwcmshc_disable_card_clk(host);

    if (priv->drv_data && priv->drv_data->remove)
    {
        priv->drv_data->remove(host, priv);
    }

    rt_clk_disable_unprepare(pltfm_host->clk);

    if (!rt_is_err(priv->bus_clk))
    {
        rt_clk_disable_unprepare(priv->bus_clk);
    }

    rt_sdhci_pltfm_free(pdev);

    return RT_EOK;
}
