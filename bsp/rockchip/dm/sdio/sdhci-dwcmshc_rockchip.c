/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-30     RT-Thread    first version
 */

#include "rockchip.h"
#include "sdhci-dwcmshc-platform.h"

#include <drivers/dev_sdhci_host.h>

#define DBG_TAG "sdhci.dw.rockchip"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* Rockchip specific Registers */
#define DWCMSHC_EMMC_DLL_CTRL           0x800
#define DWCMSHC_EMMC_DLL_RXCLK          0x804
#define DWCMSHC_EMMC_DLL_TXCLK          0x808
#define DWCMSHC_EMMC_DLL_STRBIN         0x80c
#define DECMSHC_EMMC_DLL_CMDOUT         0x810
#define DECMSHC_EMMC_MISC_CON           0x81C
#define MISC_INTCLK_EN                  RT_BIT(1)
#define DWCMSHC_EMMC_DLL_STATUS0        0x840
#define DWCMSHC_EMMC_DLL_START          RT_BIT(0)
#define DWCMSHC_EMMC_DLL_LOCKED         RT_BIT(8)
#define DWCMSHC_EMMC_DLL_TIMEOUT        RT_BIT(9)
#define DWCMSHC_EMMC_DLL_RXCLK_SRCSEL   29
#define DWCMSHC_EMMC_DLL_START_POINT    16
#define DWCMSHC_EMMC_DLL_INC            8
#define DWCMSHC_EMMC_DLL_BYPASS         RT_BIT(24)
#define DWCMSHC_EMMC_DLL_DLYENA         RT_BIT(27)
#define DLL_TAP_VALUE_SEL               RT_BIT(25)
#define DLL_TAP_VALUE_OFFSET            8
#define DLL_TXCLK_TAPNUM_DEFAULT        0x10
#define DLL_TXCLK_TAPNUM_FROM_SW        RT_BIT(24)
#define DLL_STRBIN_TAPNUM_FROM_SW       RT_BIT(24)
#define DLL_STRBIN_DELAY_NUM_SEL        RT_BIT(26)
#define DLL_STRBIN_DELAY_NUM_OFFSET     16
#define DLL_RXCLK_NO_INVERTER           1
#define DLL_CMDOUT_TAPNUM_FROM_SW       RT_BIT(24)
#define DLL_RXCLK_ORI_GATE              RT_BIT(31)
#define DLL_CMDOUT_SRC_CLK_NEG          RT_BIT(28)
#define DLL_CMDOUT_BOTH_CLK_EDGE        RT_BIT(30)

#define RK35XX_MAX_CLKS                 3
#define USEC_PER_MSEC                   1000L

#define DLL_LOCK_WO_TMOUT(x)            ((((x) & DWCMSHC_EMMC_DLL_LOCKED) == DWCMSHC_EMMC_DLL_LOCKED) && (((x) & DWCMSHC_EMMC_DLL_TIMEOUT) == 0))

#define RK_DLL_CMD_OUT          RT_BIT(1)
#define RK_RXCLK_NO_INVERTER    RT_BIT(2)
#define RK_TAP_VALUE_SEL        RT_BIT(3)

enum sdhci_dwcmshc_rk_soc_type
{
    RK_SOC_TYPE_RK3568,
    RK_SOC_TYPE_RK3588,
};

struct sdhci_dwcmshc_rk_soc_data
{
    rt_uint32_t flags;
    rt_uint8_t hs200_tx_tap;
    rt_uint8_t hs400_tx_tap;
    rt_uint8_t hs400_cmd_tap;
    rt_uint8_t ddr50_strbin_delay_num;
    rt_uint8_t hs400_strbin_tap;
};

struct sdhci_dwcmshc_rk35xx
{
    struct rt_clk *clks[RK35XX_MAX_CLKS];
    struct rt_reset_control *rstc;

    enum sdhci_dwcmshc_rk_soc_type soc_type;
    rt_uint8_t txclk_tapnum;

    const struct sdhci_dwcmshc_rk_soc_data *soc_data;
};

static rt_bool_t sdhci_dwcmshc_rk_mux_is_better_rate(rt_ubase_t rate, rt_ubase_t now, rt_ubase_t best)
{
    return now <= rate && now > best;
}

static rt_err_t sdhci_dwcmshc_rk_mux_identify_rate(struct rt_device *dev, struct rt_clk *clk)
{
    struct rt_clk *clk_750k, *clk_375k;
    rt_err_t err;

    clk_750k = rt_clk_get_by_name(dev, "clk_osc0_div_750k");
    if (rt_is_err_or_null(clk_750k))
    {
        return rt_is_err(clk_750k) ? rt_ptr_err(clk_750k) : -RT_EINVAL;
    }

    err = rt_clk_prepare_enable(clk_750k);
    if (err)
    {
        return err;
    }

    err = rt_clk_set_rate(clk_750k, 750000);
    if (err)
    {
        return err;
    }

    clk_375k = rt_clk_get_by_name(dev, "clk_osc0_div_375k");
    if (rt_is_err_or_null(clk_375k))
    {
        return rt_is_err(clk_375k) ? rt_ptr_err(clk_375k) : -RT_EINVAL;
    }

    if (rt_clk_get_rate(clk_375k) == 0)
    {
        return -RT_EINVAL;
    }

    clk->cell->parent = RT_NULL;
    err = rt_clk_set_parent(clk, clk_375k);
    if (err)
    {
        return err;
    }

    return RT_EOK;
}

static rt_err_t sdhci_dwcmshc_rk_mux_set_rate(struct rt_device *dev, struct rt_clk *clk, rt_ubase_t rate)
{
    struct rt_clk_cell *cell = clk->cell;
    struct rt_clk *best_parent = RT_NULL;
    rt_ubase_t best = 0;
    rt_bool_t has_candidate = RT_FALSE;

    if (rate <= 400000)
    {
        return sdhci_dwcmshc_rk_mux_identify_rate(dev, clk);
    }

    for (rt_uint8_t i = 0; i < cell->parents_nr; ++i)
    {
        struct rt_clk_cell *parent_cell = rt_clk_cell_get_parent_by_index(cell, i);
        struct rt_clk *parent_clk;
        rt_ubase_t parent_rate;

        if (!parent_cell)
        {
            continue;
        }

        parent_clk = rt_clk_cell_get_clk(parent_cell, RT_NULL);
        if (!parent_clk)
        {
            continue;
        }

        parent_rate = rt_clk_get_rate(parent_clk);
        if (parent_rate == 0)
        {
            continue;
        }

        if (!has_candidate || sdhci_dwcmshc_rk_mux_is_better_rate(rate, parent_rate, best))
        {
            best_parent = parent_clk;
            best = parent_rate;
            has_candidate = RT_TRUE;
        }
    }

    if (!has_candidate)
    {
        return -RT_EINVAL;
    }

    return rt_clk_set_parent(clk, best_parent);
}

static rt_err_t sdhci_dwcmshc_rk_set_core_clk_rate(struct rt_device *dev, struct rt_clk *clk, rt_ubase_t rate)
{
    struct rt_clk_cell *cell;

    if (!clk)
    {
        return -RT_EINVAL;
    }

    cell = clk->cell;

    if (cell->ops && !cell->ops->set_rate && cell->parents_nr > 1 && cell->ops->set_parent)
    {
        return sdhci_dwcmshc_rk_mux_set_rate(dev, clk, rate);
    }

    return rt_clk_set_rate(clk, rate);
}

static void sdhci_dwcmshc_rk3568_set_clock(struct rt_sdhci_host *host, unsigned int clock)
{
    int err;
    rt_uint32_t extra, reg, dll_lock_value;
    rt_uint8_t txclk_tapnum = DLL_TXCLK_TAPNUM_DEFAULT;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct sdhci_dwcmshc *dwc_priv = rt_sdhci_pltfm_priv(pltfm_host);
    struct sdhci_dwcmshc_rk35xx *rk_priv = dwc_priv->vendor_priv;
    const struct sdhci_dwcmshc_rk_soc_data *soc_data = rk_priv->soc_data;

    host->mmc->actual_clock = 0;

    if (clock == 0)
    {
        rt_sdhci_set_clock(host, clock);
        return;
    }

    if (clock <= 400000)
    {
        clock = 375000;
    }

    if ((err = sdhci_dwcmshc_rk_set_core_clk_rate(rt_mmc_dev(host->mmc), pltfm_host->clk, clock)))
    {
        LOG_E("Fail to set clock %d", clock);
    }

    if (pltfm_host->clk)
    {
        rt_ubase_t core_rate = rt_clk_get_rate(pltfm_host->clk);

        if (core_rate)
        {
            host->max_clk = core_rate;
        }
    }

    rt_sdhci_set_clock(host, clock);

    reg = dwc_priv->vendor_specific_area1 + DWCMSHC_HOST_CTRL3;
    extra = rt_sdhci_readl(host, reg);
    extra &= ~RT_BIT(0);
    rt_sdhci_writel(host, extra, reg);

    rt_sdhci_writew(host, 0, RT_SDHCI_CLOCK_CONTROL);

    if (clock <= 52000000)
    {
        rt_sdhci_writel(host, 0, DWCMSHC_EMMC_DLL_CTRL);
        rt_sdhci_writel(host, DWCMSHC_EMMC_DLL_BYPASS | DWCMSHC_EMMC_DLL_START, DWCMSHC_EMMC_DLL_CTRL);
        rt_sdhci_writel(host, DLL_RXCLK_ORI_GATE, DWCMSHC_EMMC_DLL_RXCLK);
        rt_sdhci_writel(host, 0, DWCMSHC_EMMC_DLL_TXCLK);
        rt_sdhci_writel(host, 0, DECMSHC_EMMC_DLL_CMDOUT);
        extra = DWCMSHC_EMMC_DLL_DLYENA |
                DLL_STRBIN_DELAY_NUM_SEL |
                soc_data->ddr50_strbin_delay_num << DLL_STRBIN_DELAY_NUM_OFFSET;
        rt_sdhci_writel(host, extra, DWCMSHC_EMMC_DLL_STRBIN);
        goto _exit;
    }

    rt_sdhci_writel(host, RT_BIT(1), DWCMSHC_EMMC_DLL_CTRL);
    rt_hw_us_delay(1);
    rt_sdhci_writel(host, 0x0, DWCMSHC_EMMC_DLL_CTRL);

    extra = 0x5 << DWCMSHC_EMMC_DLL_START_POINT |
            0x2 << DWCMSHC_EMMC_DLL_INC |
            DWCMSHC_EMMC_DLL_START;
    rt_sdhci_writel(host, extra, DWCMSHC_EMMC_DLL_CTRL);
    err = readl_poll_timeout(host->ioaddr + DWCMSHC_EMMC_DLL_STATUS0,
                extra, DLL_LOCK_WO_TMOUT(extra), 1, 500 * USEC_PER_MSEC);
    if (err)
    {
        LOG_E("DLL lock timeout");
        goto _exit;
    }

    dll_lock_value = ((rt_sdhci_readl(host, DWCMSHC_EMMC_DLL_STATUS0) & 0xff) * 2) & 0xff;

    extra = 0x1 << 16 |
            0x3 << 17 |
            0x3 << 19;
    rt_sdhci_writel(host, extra, dwc_priv->vendor_specific_area1 + DWCMSHC_EMMC_ATCTRL);

    extra = DWCMSHC_EMMC_DLL_DLYENA | DLL_RXCLK_ORI_GATE;
    if (soc_data->flags & RK_RXCLK_NO_INVERTER)
    {
        extra |= DLL_RXCLK_NO_INVERTER << DWCMSHC_EMMC_DLL_RXCLK_SRCSEL;
    }
    if (soc_data->flags & RK_TAP_VALUE_SEL)
    {
        extra |= DLL_TAP_VALUE_SEL | dll_lock_value << DLL_TAP_VALUE_OFFSET;
    }
    rt_sdhci_writel(host, extra, DWCMSHC_EMMC_DLL_RXCLK);

    txclk_tapnum = soc_data->hs200_tx_tap;
    if (host->mmc->ios.timing == MMC_TIMING_MMC_HS400)
    {
        txclk_tapnum = soc_data->hs400_tx_tap;

        if (soc_data->flags & RK_DLL_CMD_OUT)
        {
            extra = DLL_CMDOUT_SRC_CLK_NEG |
                    DLL_CMDOUT_BOTH_CLK_EDGE |
                    DWCMSHC_EMMC_DLL_DLYENA |
                    soc_data->hs400_cmd_tap |
                    DLL_CMDOUT_TAPNUM_FROM_SW;
            if (soc_data->flags & RK_TAP_VALUE_SEL)
            {
                extra |= DLL_TAP_VALUE_SEL | dll_lock_value << DLL_TAP_VALUE_OFFSET;
            }
            rt_sdhci_writel(host, extra, DECMSHC_EMMC_DLL_CMDOUT);
        }
    }
    extra = DWCMSHC_EMMC_DLL_DLYENA |
            DLL_TXCLK_TAPNUM_FROM_SW |
            DLL_RXCLK_NO_INVERTER << DWCMSHC_EMMC_DLL_RXCLK_SRCSEL |
            txclk_tapnum;
    if (soc_data->flags & RK_TAP_VALUE_SEL)
    {
        extra |= DLL_TAP_VALUE_SEL | dll_lock_value << DLL_TAP_VALUE_OFFSET;
    }
    rt_sdhci_writel(host, extra, DWCMSHC_EMMC_DLL_TXCLK);

    extra = DWCMSHC_EMMC_DLL_DLYENA |
            soc_data->hs400_strbin_tap |
            DLL_STRBIN_TAPNUM_FROM_SW;
    if (soc_data->flags & RK_TAP_VALUE_SEL)
    {
        extra |= DLL_TAP_VALUE_SEL | dll_lock_value << DLL_TAP_VALUE_OFFSET;
    }
    rt_sdhci_writel(host, extra, DWCMSHC_EMMC_DLL_STRBIN);

_exit:
    rt_sdhci_clk_enable(host, 0);
    host->mmc->actual_clock = clock;
}

static unsigned int sdhci_dwcmshc_rk35xx_get_min_clock(struct rt_sdhci_host *host)
{
    return 375000;
}

static void sdhci_dwcmshc_rk35xx_reset(struct rt_sdhci_host *host, rt_uint8_t mask)
{
    rt_uint32_t extra;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct sdhci_dwcmshc *dwc_priv = rt_sdhci_pltfm_priv(pltfm_host);
    struct sdhci_dwcmshc_rk35xx *rk_priv = dwc_priv->vendor_priv;

    extra = rt_sdhci_readl(host, DECMSHC_EMMC_MISC_CON);

    if (mask & RT_SDHCI_RESET_ALL && rk_priv->rstc)
    {
        rt_reset_control_assert(rk_priv->rstc);
        rt_hw_us_delay(1);
        rt_reset_control_deassert(rk_priv->rstc);
    }

    rt_sdhci_reset(host, mask);

    rt_sdhci_writel(host, MISC_INTCLK_EN | extra, DECMSHC_EMMC_MISC_CON);
}

static const struct rt_sdhci_ops sdhci_dwcmshc_rk35xx_ops =
{
    .set_clock = sdhci_dwcmshc_rk3568_set_clock,
    .set_bus_width = rt_sdhci_set_bus_width,
    .set_uhs_signaling = sdhci_dwcmshc_set_uhs_signaling,
    .get_max_clock = rt_sdhci_pltfm_clk_get_max_clock,
    .get_min_clock = sdhci_dwcmshc_rk35xx_get_min_clock,
    .reset = sdhci_dwcmshc_rk35xx_reset,
};

static const struct rt_sdhci_pltfm_data sdhci_dwcmshc_rk35xx_pdata =
{
    .ops = &sdhci_dwcmshc_rk35xx_ops,
    .quirks = RT_SDHCI_QUIRK_BROKEN_TIMEOUT_VAL,
    .quirks2 = RT_SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
           RT_SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN,
};

static rt_err_t sdhci_dwcmshc_rk35xx_init(struct rt_sdhci_host *host, struct sdhci_dwcmshc *priv)
{
    int err;
    struct sdhci_dwcmshc_rk35xx *rk_priv;
    struct rt_device *dev = rt_mmc_dev(host->mmc);
    const struct sdhci_dwcmshc_drv_data *drv_data = priv->drv_data;

    rk_priv = rt_calloc(1, sizeof(*rk_priv));
    if (!rk_priv)
    {
        return -RT_ENOMEM;
    }

    rk_priv->soc_data = drv_data->vendor_priv;
    priv->vendor_priv = rk_priv;

    if (rt_ofw_node_is_compatible(dev->ofw_node, "rockchip,rk3588-dwcmshc"))
    {
        rk_priv->soc_type = RK_SOC_TYPE_RK3588;
    }
    else
    {
        rk_priv->soc_type = RK_SOC_TYPE_RK3568;
    }

    rk_priv->rstc = rt_reset_control_get_array(dev);

    if (rt_is_err(rk_priv->rstc))
    {
        err = rt_ptr_err(rk_priv->rstc);
        LOG_E("Failed to get reset control %s", rt_strerror(err));
        goto _err;
    }

    rk_priv->clks[0] = rt_clk_get_by_name(dev, "axi");
    rk_priv->clks[1] = rt_clk_get_by_name(dev, "block");
    rk_priv->clks[2] = rt_clk_get_by_name(dev, "timer");

    if (rt_is_err(rk_priv->clks[0]))
    {
        err = rt_ptr_err(rk_priv->clks[0]);
        LOG_E("Failed to get clocks %s", rt_strerror(err));
        goto _err;
    }

    if (rt_is_err(rk_priv->clks[1]))
    {
        err = rt_ptr_err(rk_priv->clks[1]);
        LOG_E("Failed to get clocks %s", rt_strerror(err));
        goto _err;
    }

    if (rt_is_err(rk_priv->clks[2]))
    {
        err = rt_ptr_err(rk_priv->clks[2]);
        LOG_E("Failed to get clocks %s", rt_strerror(err));
        goto _err;
    }

    err = rt_clk_prepare_enable(rk_priv->clks[0]);
    if (err)
    {
        LOG_E("Failed to enable %s clocks %s", "axi", rt_strerror(err));
        goto _err;
    }

    err = rt_clk_prepare_enable(rk_priv->clks[1]);
    if (err)
    {
        LOG_E("Failed to enable %s clocks %s", "block", rt_strerror(err));
        goto _err;
    }

    err = rt_clk_prepare_enable(rk_priv->clks[2]);
    if (err)
    {
        LOG_E("Failed to enable %s clocks %s", "timer", rt_strerror(err));
        goto _err;
    }

    rt_clk_set_rate(rk_priv->clks[1], 200000000);
    rt_clk_set_rate(rk_priv->clks[2], 24000000);

    if (rt_dm_dev_prop_read_u8(dev, "rockchip,txclk-tapnum", &rk_priv->txclk_tapnum))
    {
        rk_priv->txclk_tapnum = DLL_TXCLK_TAPNUM_DEFAULT;
    }

    rt_sdhci_writel(host, 0x0, priv->vendor_specific_area1 + DWCMSHC_HOST_CTRL3);
    rt_sdhci_writel(host, 0, DWCMSHC_EMMC_DLL_TXCLK);
    rt_sdhci_writel(host, 0, DWCMSHC_EMMC_DLL_STRBIN);

    return RT_EOK;

_err:
    rt_free(rk_priv);
    priv->vendor_priv = RT_NULL;

    return err;
}

static void sdhci_dwcmshc_rk35xx_postinit(struct rt_sdhci_host *host, struct sdhci_dwcmshc *priv)
{
    struct rt_mmc_host *mmc = host->mmc;

    RT_UNUSED(priv);

    if (rt_is_err_or_null(mmc->rthost.supply.vqmmc))
    {
        host->quirks2 |= RT_SDHCI_QUIRK2_NO_1_8_V;
        host->caps1 &= ~(RT_SDHCI_SUPPORT_SDR104 | RT_SDHCI_SUPPORT_SDR50 |
                RT_SDHCI_SUPPORT_DDR50);
        mmc->caps2 &= ~(MMC_CAP2_HS200 | MMC_CAP2_HS400 | MMC_CAP2_HSX00_1_8V |
                MMC_CAP2_HS400_ES);
        mmc->caps &= ~(MMC_CAP_1_8V_DDR | MMC_CAP_UHS);
    }

    if (mmc->f_max <= 52000000)
    {
        mmc->caps2 &= ~(MMC_CAP2_HS200 | MMC_CAP2_HS400);
        mmc->caps &= ~(MMC_CAP_3_3V_DDR | MMC_CAP_1_8V_DDR);
    }
}

static void sdhci_dwcmshc_rk35xx_remove(struct rt_sdhci_host *host, struct sdhci_dwcmshc *priv)
{
    struct sdhci_dwcmshc_rk35xx *rk_priv = priv->vendor_priv;

    RT_UNUSED(host);

    if (!rk_priv)
    {
        return;
    }

    rt_clk_disable_unprepare(rk_priv->clks[2]);
    rt_clk_disable_unprepare(rk_priv->clks[1]);
    rt_clk_disable_unprepare(rk_priv->clks[0]);
    rt_free(rk_priv);
    priv->vendor_priv = RT_NULL;
}

static const struct sdhci_dwcmshc_rk_soc_data sdhci_dwcmshc_rk3528_soc_data =
{
    .flags = RK_DLL_CMD_OUT | RK_TAP_VALUE_SEL,
    .hs200_tx_tap = 12,
    .hs400_tx_tap = 6,
    .hs400_cmd_tap = 6,
    .hs400_strbin_tap = 3,
    .ddr50_strbin_delay_num = 10,
};

static const struct sdhci_dwcmshc_rk_soc_data sdhci_dwcmshc_rk3562_soc_data =
{
    .flags = RK_DLL_CMD_OUT | RK_TAP_VALUE_SEL,
    .hs200_tx_tap = 12,
    .hs400_tx_tap = 6,
    .hs400_cmd_tap = 6,
    .hs400_strbin_tap = 3,
    .ddr50_strbin_delay_num = 10,
};

static const struct sdhci_dwcmshc_rk_soc_data sdhci_dwcmshc_rk3568_soc_data =
{
    .flags = RK_RXCLK_NO_INVERTER | RK_TAP_VALUE_SEL,
    .hs200_tx_tap = 16,
    .hs400_tx_tap = 8,
    .hs400_cmd_tap = 8,
    .hs400_strbin_tap = 4,
    .ddr50_strbin_delay_num = 16,
};

static const struct sdhci_dwcmshc_rk_soc_data sdhci_dwcmshc_rk3576_soc_data =
{
    .flags = RK_DLL_CMD_OUT | RK_TAP_VALUE_SEL,
    .hs200_tx_tap = 16,
    .hs400_tx_tap = 7,
    .hs400_cmd_tap = 7,
    .hs400_strbin_tap = 5,
    .ddr50_strbin_delay_num = 10,
};

static const struct sdhci_dwcmshc_rk_soc_data sdhci_dwcmshc_rk3588_soc_data =
{
    .flags = RK_DLL_CMD_OUT | RK_TAP_VALUE_SEL,
    .hs200_tx_tap = 16,
    .hs400_tx_tap = 9,
    .hs400_cmd_tap = 8,
    .hs400_strbin_tap = 4,
    .ddr50_strbin_delay_num = 16,
};

#define SDHCI_DWCMSHC_RK_DRV_DATA(_soc) \
{ \
    .pdata = &sdhci_dwcmshc_rk35xx_pdata, \
    .init = sdhci_dwcmshc_rk35xx_init, \
    .postinit = sdhci_dwcmshc_rk35xx_postinit, \
    .remove = sdhci_dwcmshc_rk35xx_remove, \
    .vendor_priv = (void *)&sdhci_dwcmshc_##_soc##_soc_data, \
}

static const struct sdhci_dwcmshc_drv_data sdhci_dwcmshc_rk3528_drv_data =
    SDHCI_DWCMSHC_RK_DRV_DATA(rk3528);
static const struct sdhci_dwcmshc_drv_data sdhci_dwcmshc_rk3562_drv_data =
    SDHCI_DWCMSHC_RK_DRV_DATA(rk3562);
static const struct sdhci_dwcmshc_drv_data sdhci_dwcmshc_rk3568_drv_data =
    SDHCI_DWCMSHC_RK_DRV_DATA(rk3568);
static const struct sdhci_dwcmshc_drv_data sdhci_dwcmshc_rk3576_drv_data =
    SDHCI_DWCMSHC_RK_DRV_DATA(rk3576);
static const struct sdhci_dwcmshc_drv_data sdhci_dwcmshc_rk3588_drv_data =
    SDHCI_DWCMSHC_RK_DRV_DATA(rk3588);

static rt_err_t sdhci_dwcmshc_rockchip_probe(struct rt_platform_device *pdev)
{
    const struct sdhci_dwcmshc_drv_data *drv_data = pdev->id->data;

    return sdhci_dwcmshc_platform_register(pdev, drv_data);
}

static rt_err_t sdhci_dwcmshc_rockchip_remove(struct rt_platform_device *pdev)
{
    return sdhci_dwcmshc_remove(pdev);
}

static const struct rt_ofw_node_id sdhci_dwcmshc_rockchip_ofw_ids[] =
{
    { .compatible = "rockchip,rk3588-dwcmshc", .data = &sdhci_dwcmshc_rk3588_drv_data, },
    { .compatible = "rockchip,rk3576-dwcmshc", .data = &sdhci_dwcmshc_rk3576_drv_data, },
    { .compatible = "rockchip,rk3568-dwcmshc", .data = &sdhci_dwcmshc_rk3568_drv_data, },
    { .compatible = "rockchip,rk3528-dwcmshc", .data = &sdhci_dwcmshc_rk3528_drv_data, },
    { .compatible = "rockchip,rk3562-dwcmshc", .data = &sdhci_dwcmshc_rk3562_drv_data, },
    { /* sentinel */ }
};

static struct rt_platform_driver sdhci_dwcmshc_rockchip_driver =
{
    .name = "sdhci-dwcmshc-rockchip",
    .ids = sdhci_dwcmshc_rockchip_ofw_ids,

    .probe = sdhci_dwcmshc_rockchip_probe,
    .remove = sdhci_dwcmshc_rockchip_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sdhci_dwcmshc_rockchip_driver);
