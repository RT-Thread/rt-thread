/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-01     GuEe-GUI     The first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "sdhci.brcmstb"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "dev_sdio_dm.h"
#include "dev_sdhci_dm.h"

#define SDHCI_VENDOR                            0x78
#define  SDHCI_VENDOR_ENHANCED_STRB             0x1
#define  SDHCI_VENDOR_GATE_SDCLK_EN             0x2

#define BRCMSTB_MATCH_FLAGS_NO_64BIT            RT_BIT(0)
#define BRCMSTB_MATCH_FLAGS_BROKEN_TIMEOUT      RT_BIT(1)
#define BRCMSTB_MATCH_FLAGS_HAS_CLOCK_GATE      RT_BIT(2)
#define BRCMSTB_MATCH_FLAGS_USE_CARD_BUSY       RT_BIT(3)

#define BRCMSTB_PRIV_FLAGS_HAS_CQE              RT_BIT(0)
#define BRCMSTB_PRIV_FLAGS_GATE_CLOCK           RT_BIT(1)
#define BRCMSTB_PRIV_FLAGS_HAS_SD_EXPRESS       RT_BIT(2)

#define SDHCI_ARASAN_CQE_BASE_ADDR              0x200

#define SDIO_CFG_CTRL                           0x0
#define  SDIO_CFG_CTRL_SDCD_N_TEST_EN           RT_BIT(31)
#define  SDIO_CFG_CTRL_SDCD_N_TEST_LEV          RT_BIT(30)

#define SDIO_CFG_SD_PIN_SEL                     0x44
#define  SDIO_CFG_SD_PIN_SEL_MASK               0x3
#define  SDIO_CFG_SD_PIN_SEL_MMC                RT_BIT(0)
#define  SDIO_CFG_SD_PIN_SEL_SD                 RT_BIT(1)

#define SDIO_CFG_CQ_CAPABILITY                  0x4c
#define  SDIO_CFG_CQ_CAPABILITY_FMUL_SHIFT       12

#define SDIO_CFG_MAX_50MHZ_MODE                 0x1ac
#define  SDIO_CFG_MAX_50MHZ_MODE_STRAP_OVERRIDE RT_BIT(31)
#define  SDIO_CFG_MAX_50MHZ_MODE_ENABLE         RT_BIT(0)

struct sdhci_brcmstb_priv
{
    void *cfg_regs;

    struct rt_clk *base_clk;

    rt_uint32_t flags;
    rt_uint32_t base_freq_hz;
};

struct brcmstb_match_priv
{
    void (*hs400es)(struct rt_mmc_host *mmc, struct rt_mmcsd_io_cfg *ios);
    void (*cfginit)(struct rt_sdhci_host *host);
    struct rt_sdhci_ops *ops;
    const rt_uint32_t flags;
};

rt_inline void enable_clock_gating(struct rt_sdhci_host *host)
{
    rt_uint32_t reg;

    reg = rt_sdhci_readl(host, SDHCI_VENDOR);
    reg |= SDHCI_VENDOR_GATE_SDCLK_EN;
    rt_sdhci_writel(host, reg, SDHCI_VENDOR);
}

static void brcmstb_reset(struct rt_sdhci_host *host, rt_uint8_t mask)
{
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct sdhci_brcmstb_priv *priv = rt_sdhci_pltfm_priv(pltfm_host);

    /* Reset cqhci first if CQE supported */
    rt_sdhci_reset(host, mask);

    /* Reset will clear this, so re-enable it */
    if (priv->flags & BRCMSTB_PRIV_FLAGS_GATE_CLOCK)
    {
        enable_clock_gating(host);
    }
}

static void sdhci_brcmstb_hs400es(struct rt_mmc_host *mmc, struct rt_mmcsd_io_cfg *ios)
{
    rt_uint32_t reg;
    struct rt_sdhci_host *host = rt_mmc_priv(mmc);

    reg = HWREG32(host->ioaddr + SDHCI_VENDOR);

    if (ios->enhanced_strobe)
    {
        reg |= SDHCI_VENDOR_ENHANCED_STRB;
    }
    else
    {
        reg &= ~SDHCI_VENDOR_ENHANCED_STRB;
    }

    HWREG32(host->ioaddr + SDHCI_VENDOR) = reg;
}

static void sdhci_brcmstb_set_clock(struct rt_sdhci_host *host, unsigned int clock)
{
    rt_uint16_t clk;

    host->mmc->actual_clock = 0;

    clk = rt_sdhci_clk_set(host, clock, &host->mmc->actual_clock);
    rt_sdhci_writew(host, clk, RT_SDHCI_CLOCK_CONTROL);

    if (clock == 0)
    {
        return;
    }

    rt_sdhci_clk_enable(host, clk);
}

static void sdhci_brcmstb_set_power(struct rt_sdhci_host *host, unsigned char mode,
                                    unsigned short vdd)
{
    if (!rt_is_err_or_null(host->mmc->rthost.supply.vmmc))
    {
        sdio_regulator_set_ocr(&host->mmc->rthost, host->mmc->rthost.supply.vmmc, vdd);
    }

    rt_sdhci_set_power_with_noreg(host, mode, vdd);
}

static void sdhci_bcm2712_set_clock(struct rt_sdhci_host *host, unsigned int clock)
{
    rt_uint16_t clk;
    rt_uint32_t reg;
    rt_bool_t is_emmc_rate = RT_FALSE;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct sdhci_brcmstb_priv *priv = rt_sdhci_pltfm_priv(pltfm_host);

    host->mmc->actual_clock = 0;

    rt_sdhci_writew(host, 0, RT_SDHCI_CLOCK_CONTROL);

    switch (host->mmc->ios.timing)
    {
    case MMC_TIMING_MMC_HS400:
    case MMC_TIMING_MMC_HS200:
    case MMC_TIMING_MMC_DDR52:
    case MMC_TIMING_MMC_HS:
        is_emmc_rate = RT_TRUE;
        break;
    default:
        break;
    }

    reg = HWREG32(priv->cfg_regs + SDIO_CFG_SD_PIN_SEL);
    reg &= ~SDIO_CFG_SD_PIN_SEL_MASK;
    if (is_emmc_rate)
    {
        reg |= SDIO_CFG_SD_PIN_SEL_MMC;
    }
    else
    {
        reg |= SDIO_CFG_SD_PIN_SEL_SD;
    }
    HWREG32(priv->cfg_regs + SDIO_CFG_SD_PIN_SEL) = reg;

    if (clock == 0)
    {
        return;
    }

    clk = rt_sdhci_clk_set(host, clock, &host->mmc->actual_clock);
    rt_sdhci_clk_enable(host, clk);
}

static void sdhci_bcm2712_hs400_downgrade(struct rt_mmc_host *mmc)
{
    struct rt_sdhci_host *host = rt_mmc_priv(mmc);

    /*
     * The eMMC PHY refuses to update if HS timings are selected while
     * the clock is above 52MHz, so lower it before mode transitions.
     */
    sdhci_bcm2712_set_clock(host, 52000000);
}

static void sdhci_brcmstb_set_uhs_signaling(struct rt_sdhci_host *host,
                                            unsigned int timing)
{
    rt_uint16_t ctrl_2;

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
    else if (timing == MMC_TIMING_SD_HS || timing == MMC_TIMING_MMC_HS ||
             timing == MMC_TIMING_UHS_SDR25)
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
        ctrl_2 |= RT_SDHCI_CTRL_HS400; /* Non-standard */
    }

    rt_sdhci_writew(host, ctrl_2, RT_SDHCI_HOST_CONTROL2);
}

static void sdhci_brcmstb_cfginit_2712(struct rt_sdhci_host *host)
{
    rt_uint32_t uhs_mask, hsemmc_mask, reg, base_clk_mhz;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct sdhci_brcmstb_priv *brcmstb_priv = rt_sdhci_pltfm_priv(pltfm_host);

    uhs_mask = (MMCSD_SUP_SDR50 | MMCSD_SUP_SDR104);
    hsemmc_mask = (MMC_CAP2_HS200_1_8V_SDR | MMC_CAP2_HS200_1_2V_SDR |
                   MMCSD_SUP_HS400_1V8 | MMCSD_SUP_HS400_1V2);

    /*
     * If we support a speed that requires tuning,
     * then select the delay line PHY as the clock source.
     */
    if ((host->mmc->caps & uhs_mask) || (host->mmc->caps2 & hsemmc_mask))
    {
        reg = HWREG32(brcmstb_priv->cfg_regs + SDIO_CFG_MAX_50MHZ_MODE);
        reg &= ~SDIO_CFG_MAX_50MHZ_MODE_ENABLE;
        reg |= SDIO_CFG_MAX_50MHZ_MODE_STRAP_OVERRIDE;
        HWREG32(brcmstb_priv->cfg_regs + SDIO_CFG_MAX_50MHZ_MODE) = reg;

        host->mmc_host_ops.hs400_downgrade = sdhci_bcm2712_hs400_downgrade;
    }

    if ((host->mmc->caps & MMC_CAP_NONREMOVABLE) ||
        (host->mmc->caps & MMC_CAP_NEEDS_POLL))
    {
        /* Force presence */
        reg = HWREG32(brcmstb_priv->cfg_regs + SDIO_CFG_CTRL);
        reg &= ~SDIO_CFG_CTRL_SDCD_N_TEST_LEV;
        reg |= SDIO_CFG_CTRL_SDCD_N_TEST_EN;
        HWREG32(brcmstb_priv->cfg_regs + SDIO_CFG_CTRL) = reg;
    }

    /* Guesstimate the timer frequency (controller base clock) */
    base_clk_mhz = rt_clk_get_rate(pltfm_host->clk) / 1000000;
    if (base_clk_mhz == 0)
    {
        base_clk_mhz = 1;
    }
    reg = (3 << SDIO_CFG_CQ_CAPABILITY_FMUL_SHIFT) | base_clk_mhz;
    HWREG32(brcmstb_priv->cfg_regs + SDIO_CFG_CQ_CAPABILITY) = reg;
}

static struct rt_sdhci_ops sdhci_brcmstb_ops =
{
    .set_clock = rt_sdhci_set_clock,
    .set_bus_width = rt_sdhci_set_bus_width,
    .reset = rt_sdhci_reset,
    .set_uhs_signaling = rt_sdhci_set_uhs,
};

static struct rt_sdhci_ops sdhci_brcmstb_ops_2712 =
{
    .set_clock = sdhci_bcm2712_set_clock,
    .set_power = sdhci_brcmstb_set_power,
    .set_bus_width = rt_sdhci_set_bus_width,
    .reset = brcmstb_reset,
    .set_uhs_signaling = sdhci_brcmstb_set_uhs_signaling,
};

static struct rt_sdhci_ops sdhci_brcmstb_ops_7216 =
{
    .set_clock = sdhci_brcmstb_set_clock,
    .set_bus_width = rt_sdhci_set_bus_width,
    .reset = brcmstb_reset,
    .set_uhs_signaling = sdhci_brcmstb_set_uhs_signaling,
};

static struct brcmstb_match_priv match_priv_7425 =
{
    .flags = BRCMSTB_MATCH_FLAGS_NO_64BIT | BRCMSTB_MATCH_FLAGS_BROKEN_TIMEOUT,
    .ops = &sdhci_brcmstb_ops,
};

static struct brcmstb_match_priv match_priv_7445 =
{
    .flags = BRCMSTB_MATCH_FLAGS_BROKEN_TIMEOUT,
    .ops = &sdhci_brcmstb_ops,
};

static const struct brcmstb_match_priv match_priv_7216 =
{
    .flags = BRCMSTB_MATCH_FLAGS_HAS_CLOCK_GATE,
    .hs400es = sdhci_brcmstb_hs400es,
    .ops = &sdhci_brcmstb_ops_7216,
};

static const struct brcmstb_match_priv match_priv_2712 =
{
    .flags = BRCMSTB_MATCH_FLAGS_USE_CARD_BUSY,
    .hs400es = sdhci_brcmstb_hs400es,
    .cfginit = sdhci_brcmstb_cfginit_2712,
    .ops = &sdhci_brcmstb_ops_2712,
};

#ifdef RT_USING_PM
static rt_err_t sdhci_brcmstb_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    struct rt_sdhci_host *host = device->user_data;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct sdhci_brcmstb_priv *priv = rt_sdhci_pltfm_priv(pltfm_host);

    rt_clk_disable_unprepare(priv->base_clk);

    return rt_sdhci_pltfm_suspend(device);
}

static void sdhci_brcmstb_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    struct rt_sdhci_host *host = device->user_data;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct sdhci_brcmstb_priv *priv = rt_sdhci_pltfm_priv(pltfm_host);

    if (!rt_sdhci_pltfm_resume(device) && priv->base_freq_hz)
    {
        if (!rt_clk_prepare_enable(priv->base_clk) &&
            rt_clk_get_rate(priv->base_clk) != priv->base_freq_hz)
        {
            rt_clk_set_rate(priv->base_clk, priv->base_freq_hz);
        }
    }
}

static const struct rt_device_pm_ops sdhci_brcmstb_pm_ops =
{
    .suspend = sdhci_brcmstb_pm_suspend,
    .resume = sdhci_brcmstb_pm_resume,
};
#endif /* RT_USING_PM */

static rt_err_t sdhci_brcmstb_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t actual_clock_mhz;
    struct rt_clk *clk, *base_clk = RT_NULL;
    struct rt_device *dev = &pdev->parent;
    struct rt_sdhci_host *host;
    struct sdhci_brcmstb_priv *priv;
    struct rt_sdhci_pltfm_host *pltfm_host;
    struct rt_sdhci_pltfm_data brcmstb_pdata;
    const struct brcmstb_match_priv *match_priv;

    match_priv = pdev->id->data;

    clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(clk))
    {
        return rt_ptr_err(clk);
    }

    if ((err = rt_clk_prepare_enable(clk)))
    {
        goto _free_clk;
    }

    rt_memset(&brcmstb_pdata, 0, sizeof(brcmstb_pdata));
    brcmstb_pdata.ops = match_priv->ops;

    host = rt_sdhci_pltfm_init(pdev, &brcmstb_pdata, sizeof(struct sdhci_brcmstb_priv));
    if (!host)
    {
        err = -RT_ERROR;
        goto _disable_free_clk;
    }

    pltfm_host = rt_sdhci_priv(host);
    priv = rt_sdhci_pltfm_priv(pltfm_host);
    pltfm_host->clk = clk;

    /* Check property "supports-cqe" and set cqhci IRQ here */

    /*
     * Read ref node "sde-pcie".
     * Init SDE regulator "sde-1v8", MMIO[1/2], pinctrl[default/sdex]
     */

    /* Map in the non-standard CFG registers */
    priv->cfg_regs = rt_dm_dev_iomap_by_name(dev, "cfg");
    if (!priv->cfg_regs)
    {
        priv->cfg_regs = rt_dm_dev_iomap(dev, 1);
    }

    if (!priv->cfg_regs)
    {
        err = -RT_EIO;
        goto _free_cfg;
    }

    rt_sdhci_get_of_property(pdev);

    if ((err = rt_mmc_of_parse(host->mmc)))
    {
        goto _free_cfg;
    }

    /*
     * Automatic clock gating does not work for SD cards that may
     * voltage switch so only enable it for non-removable devices.
     */
    if ((match_priv->flags & BRCMSTB_MATCH_FLAGS_HAS_CLOCK_GATE) &&
        (host->mmc->caps & MMC_CAP_NONREMOVABLE))
    {
        priv->flags |= BRCMSTB_PRIV_FLAGS_GATE_CLOCK;
    }

    /*
     * If the chip has enhanced strobe and it's enabled, add
     * callback
     */
    if (match_priv->hs400es && (host->mmc->caps2 & MMC_CAP2_HS400_ES))
    {
        host->mmc_host_ops.hs400_enhanced_strobe = match_priv->hs400es;
    }

    if (match_priv->cfginit)
    {
        match_priv->cfginit(host);
    }

    /*
     * Supply the existing CAPS, but clear the UHS modes. This
     * will allow these modes to be specified by device tree
     * properties through rt_mmc_of_parse().
     */
    host->caps = rt_sdhci_readl(host, RT_SDHCI_CAPABILITIES);
    if (match_priv->flags & BRCMSTB_MATCH_FLAGS_NO_64BIT)
    {
        host->caps &= ~RT_SDHCI_CAN_64BIT;
    }
    host->caps1 = rt_sdhci_readl(host, RT_SDHCI_CAPABILITIES_1);
    host->caps1 &= ~(RT_SDHCI_SUPPORT_SDR50 | RT_SDHCI_SUPPORT_SDR104 | RT_SDHCI_SUPPORT_DDR50);

    if (match_priv->flags & BRCMSTB_MATCH_FLAGS_BROKEN_TIMEOUT)
    {
        host->quirks |= RT_SDHCI_QUIRK_BROKEN_TIMEOUT_VAL;
    }

    if (!(match_priv->flags & BRCMSTB_MATCH_FLAGS_USE_CARD_BUSY))
    {
        host->mmc_host_ops.card_busy = RT_NULL;
    }

    /* Change the base clock frequency if the DT property exists */
    if (rt_dm_dev_prop_read_u32(dev, "clock-frequency", &priv->base_freq_hz))
    {
        goto _add_host;
    }

    base_clk = rt_clk_get_by_name(dev, "sdio_freq");
    if (rt_is_err_or_null(base_clk))
    {
        LOG_W("%s: Clock for \"sdio_freq\" not found", rt_dm_dev_get_name(dev));
        goto _add_host;
    }

    if ((err = rt_clk_prepare_enable(base_clk)))
    {
        goto _free_base_clk;
    }

    /* set improved clock rate */
    rt_clk_set_rate(base_clk, priv->base_freq_hz);
    actual_clock_mhz = rt_clk_get_rate(base_clk) / 1000000;

    host->caps &= ~RT_SDHCI_CLOCK_V3_BASE_MASK;
    host->caps |= (actual_clock_mhz << RT_SDHCI_CLOCK_BASE_SHIFT);
    /* Disable presets because they are now incorrect */
    host->quirks2 |= RT_SDHCI_QUIRK2_PRESET_VALUE_BROKEN;

    LOG_D("%s: Base Clock Frequency changed to %dMHz",
          rt_dm_dev_get_name(dev), actual_clock_mhz);
    priv->base_clk = base_clk;

_add_host:
    /* The CQE should be enabled before here. */
    if ((err = rt_sdhci_set_and_add_host(host)))
    {
        goto _err;
    }

#ifdef RT_USING_PM
    rt_pm_device_register(dev, &sdhci_brcmstb_pm_ops);
#endif

    return RT_EOK;

_err:
    goto _free_cfg;

_free_base_clk:
    if (base_clk && base_clk != clk)
    {
        rt_clk_disable_unprepare(base_clk);
        rt_clk_put(base_clk);
    }

_free_cfg:
    if (host)
    {
        rt_sdhci_pltfm_free(pdev);
    }

_disable_free_clk:
    rt_clk_disable_unprepare(clk);

_free_clk:
    rt_clk_put(clk);

    return err;
}

static rt_err_t sdhci_brcmstb_remove(struct rt_platform_device *pdev)
{
#ifdef RT_USING_PM
    rt_pm_device_unregister(&pdev->parent);
#endif

    return rt_sdhci_pltfm_remove(pdev);
}

static rt_err_t sdhci_brcmstb_shutdown(struct rt_platform_device *pdev)
{
    return sdhci_brcmstb_remove(pdev);
}

static const struct rt_ofw_node_id sdhci_brcm_ofw_ids[] =
{
    { .compatible = "brcm,bcm7425-sdhci", .data = &match_priv_7425 },
    { .compatible = "brcm,bcm7445-sdhci", .data = &match_priv_7445 },
    { .compatible = "brcm,bcm7216-sdhci", .data = &match_priv_7216 },
    { .compatible = "brcm,bcm2712-sdhci", .data = &match_priv_2712 },
    { /* sentinel */ }
};

static struct rt_platform_driver sdhci_brcmstb_driver =
{
    .name = "sdhci-brcmstb",
    .ids = sdhci_brcm_ofw_ids,

    .probe = sdhci_brcmstb_probe,
    .remove = sdhci_brcmstb_remove,
    .shutdown = sdhci_brcmstb_shutdown,
};
RT_PLATFORM_DRIVER_EXPORT(sdhci_brcmstb_driver);
