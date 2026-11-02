/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-28     zhujiale     The first version
 * 2025-01-01     GuEe-GUI     Move to DM
 */

#include "dev_sdio_dm.h"
#include "dev_sdhci_dm.h"

struct sdhci_iproc_data
{
    const struct rt_sdhci_pltfm_data *pdata;
    rt_uint32_t caps;
    rt_uint32_t caps1;
    rt_uint32_t mmc_caps;
    rt_bool_t missing_caps;
};

struct sdhci_iproc_host
{
    const struct sdhci_iproc_data *data;
    rt_uint32_t shadow_cmd;
    rt_uint32_t shadow_blk;
    rt_bool_t is_cmd_shadowed;
    rt_bool_t is_blk_shadowed;
};

#define REG_OFFSET_IN_BITS(reg) ((reg) << 3 & 0x18)

rt_inline rt_uint32_t sdhci_iproc_readl(struct rt_sdhci_host *host, int reg)
{
    return HWREG32(host->ioaddr + reg);
}

static rt_uint16_t sdhci_iproc_readw(struct rt_sdhci_host *host, int reg)
{
    rt_uint16_t word;
    rt_uint32_t val;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct sdhci_iproc_host *iproc_host = rt_sdhci_pltfm_priv(pltfm_host);

    if ((reg == RT_SDHCI_TRANSFER_MODE) && iproc_host->is_cmd_shadowed)
    {
        /* Get the saved transfer mode */
        val = iproc_host->shadow_cmd;
    }
    else if ((reg == RT_SDHCI_BLOCK_SIZE || reg == RT_SDHCI_BLOCK_COUNT) &&
            iproc_host->is_blk_shadowed)
    {
        /* Get the saved block info */
        val = iproc_host->shadow_blk;
    }
    else
    {
        val = sdhci_iproc_readl(host, (reg & ~3));
    }

    word = val >> REG_OFFSET_IN_BITS(reg) & 0xffff;

    return word;
}

static rt_uint8_t sdhci_iproc_readb(struct rt_sdhci_host *host, int reg)
{
    rt_uint32_t val = sdhci_iproc_readl(host, (reg & ~3));
    rt_uint8_t byte = val >> REG_OFFSET_IN_BITS(reg) & 0xff;

    return byte;
}

rt_inline void sdhci_iproc_writel(struct rt_sdhci_host *host, rt_uint32_t val, int reg)
{
    HWREG32(host->ioaddr + reg) = val;

    if (host->clock <= 400000)
    {
        /* Round up to micro-second four SD clock delay */
        if (host->clock)
        {
            rt_hw_us_delay((4 * 1000000 + host->clock - 1) / host->clock);
        }
        else
        {
            rt_hw_us_delay(10);
        }
    }
}

static void sdhci_iproc_writew(struct rt_sdhci_host *host, rt_uint16_t val, int reg)
{
    rt_uint32_t oldval, newval;
    rt_uint32_t word_shift = REG_OFFSET_IN_BITS(reg);
    rt_uint32_t mask = 0xffff << word_shift;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct sdhci_iproc_host *iproc_host = rt_sdhci_pltfm_priv(pltfm_host);

    if (reg == RT_SDHCI_COMMAND)
    {
        /* Write the block now as we are issuing a command */
        if (iproc_host->is_blk_shadowed)
        {
            sdhci_iproc_writel(host, iproc_host->shadow_blk, RT_SDHCI_BLOCK_SIZE);
            iproc_host->is_blk_shadowed = false;
        }
        oldval = iproc_host->shadow_cmd;
        iproc_host->is_cmd_shadowed = false;
    }
    else if ((reg == RT_SDHCI_BLOCK_SIZE || reg == RT_SDHCI_BLOCK_COUNT) &&
            iproc_host->is_blk_shadowed)
    {
        /* Block size and count are stored in shadow reg */
        oldval = iproc_host->shadow_blk;
    }
    else
    {
        /* Read reg, all other registers are not shadowed */
        oldval = sdhci_iproc_readl(host, (reg & ~3));
    }
    newval = (oldval & ~mask) | (val << word_shift);

    if (reg == RT_SDHCI_TRANSFER_MODE)
    {
        /* Save the transfer mode until the command is issued */
        iproc_host->shadow_cmd = newval;
        iproc_host->is_cmd_shadowed = RT_TRUE;
    }
    else if (reg == RT_SDHCI_BLOCK_SIZE || reg == RT_SDHCI_BLOCK_COUNT)
    {
        /* Save the block info until the command is issued */
        iproc_host->shadow_blk = newval;
        iproc_host->is_blk_shadowed = RT_TRUE;
    }
    else
    {
        /* Command or other regular 32-bit write */
        sdhci_iproc_writel(host, newval, reg & ~3);
    }
}

static void sdhci_iproc_writeb(struct rt_sdhci_host *host, rt_uint8_t val, int reg)
{
    rt_uint32_t oldval = sdhci_iproc_readl(host, (reg & ~3));
    rt_uint32_t byte_shift = REG_OFFSET_IN_BITS(reg);
    rt_uint32_t mask = 0xff << byte_shift;
    rt_uint32_t newval = (oldval & ~mask) | (val << byte_shift);

    sdhci_iproc_writel(host, newval, reg & ~3);
}

static unsigned int sdhci_iproc_get_max_clock(struct rt_sdhci_host *host)
{
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);

    if (pltfm_host->clk)
    {
        return rt_sdhci_pltfm_clk_get_max_clock(host);
    }
    else
    {
        return pltfm_host->clock;
    }
}

static unsigned int sdhci_iproc_bcm2711_get_min_clock(struct rt_sdhci_host *host)
{
    return 200000;
}

static const struct rt_sdhci_ops sdhci_iproc_ops =
{
    .set_clock = rt_sdhci_set_clock,
    .get_max_clock = sdhci_iproc_get_max_clock,
    .set_bus_width = rt_sdhci_set_bus_width,
    .reset = rt_sdhci_reset,
    .set_uhs_signaling = rt_sdhci_set_uhs,
};

static const struct rt_sdhci_ops sdhci_iproc_32only_ops =
{
    .read_l = sdhci_iproc_readl,
    .read_w = sdhci_iproc_readw,
    .read_b = sdhci_iproc_readb,
    .write_l = sdhci_iproc_writel,
    .write_w = sdhci_iproc_writew,
    .write_b = sdhci_iproc_writeb,
    .set_clock = rt_sdhci_set_clock,
    .get_max_clock = sdhci_iproc_get_max_clock,
    .set_power = rt_sdhci_set_power_and_bus_voltage,
    .set_bus_width = rt_sdhci_set_bus_width,
    .reset = rt_sdhci_reset,
    .set_uhs_signaling = rt_sdhci_set_uhs,
};

static const struct rt_sdhci_pltfm_data sdhci_iproc_cygnus_pltfm_data =
{
    .quirks = RT_SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK | RT_SDHCI_QUIRK_NO_HISPD_BIT,
    .quirks2 = RT_SDHCI_QUIRK2_ACMD23_BROKEN | RT_SDHCI_QUIRK2_HOST_OFF_CARD_ON,
    .ops = &sdhci_iproc_32only_ops,
};

static const struct sdhci_iproc_data iproc_cygnus_data =
{
    .pdata = &sdhci_iproc_cygnus_pltfm_data,
    .caps = ((0x1 << RT_SDHCI_MAX_BLOCK_SHIFT) & RT_SDHCI_MAX_BLOCK_MASK) |
            RT_SDHCI_CAN_VDD_330 | RT_SDHCI_CAN_VDD_180 | RT_SDHCI_CAN_DO_SUSPEND |
            RT_SDHCI_CAN_DO_HISPD | RT_SDHCI_CAN_DO_ADMA2 | RT_SDHCI_CAN_DO_SDMA,
    .caps1 = RT_SDHCI_DRIVER_TYPE_C | RT_SDHCI_DRIVER_TYPE_D | RT_SDHCI_SUPPORT_DDR50,
    .mmc_caps = MMC_CAP_1_8V_DDR,
};

static const struct rt_sdhci_pltfm_data sdhci_iproc_pltfm_data =
{
    .quirks = RT_SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK |
              RT_SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12 |
              RT_SDHCI_QUIRK_NO_HISPD_BIT,
    .quirks2 = RT_SDHCI_QUIRK2_ACMD23_BROKEN,
    .ops = &sdhci_iproc_ops,
};

static const struct sdhci_iproc_data iproc_data =
{
    .pdata = &sdhci_iproc_pltfm_data,
    .caps = ((0x1 << RT_SDHCI_MAX_BLOCK_SHIFT) & RT_SDHCI_MAX_BLOCK_MASK) |
            RT_SDHCI_CAN_VDD_330 |
            RT_SDHCI_CAN_VDD_180 |
            RT_SDHCI_CAN_DO_SUSPEND |
            RT_SDHCI_CAN_DO_HISPD |
            RT_SDHCI_CAN_DO_ADMA2 |
            RT_SDHCI_CAN_DO_SDMA,
    .caps1 = RT_SDHCI_DRIVER_TYPE_C | RT_SDHCI_DRIVER_TYPE_D | RT_SDHCI_SUPPORT_DDR50,
};

static const struct rt_sdhci_pltfm_data sdhci_bcm2835_pltfm_data =
{
    .quirks = RT_SDHCI_QUIRK_BROKEN_CARD_DETECTION |
              RT_SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK |
              RT_SDHCI_QUIRK_NO_HISPD_BIT,
    .quirks2 = RT_SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
    .ops = &sdhci_iproc_32only_ops,
};

static const struct sdhci_iproc_data bcm2835_data =
{
    .pdata = &sdhci_bcm2835_pltfm_data,
    .caps = ((0x1 << RT_SDHCI_MAX_BLOCK_SHIFT) & RT_SDHCI_MAX_BLOCK_MASK) |
            RT_SDHCI_CAN_VDD_330 | RT_SDHCI_CAN_DO_HISPD,
    .caps1 = RT_SDHCI_DRIVER_TYPE_A | RT_SDHCI_DRIVER_TYPE_C,
    .mmc_caps = 0x00000000,
    .missing_caps = RT_TRUE,
};

static const struct rt_sdhci_ops sdhci_iproc_bcm2711_ops =
{
    .read_l = sdhci_iproc_readl,
    .read_w = sdhci_iproc_readw,
    .read_b = sdhci_iproc_readb,
    .write_l = sdhci_iproc_writel,
    .write_w = sdhci_iproc_writew,
    .write_b = sdhci_iproc_writeb,
    .set_clock = rt_sdhci_set_clock,
    .set_power = rt_sdhci_set_power_and_bus_voltage,
    .get_max_clock = sdhci_iproc_get_max_clock,
    .get_min_clock = sdhci_iproc_bcm2711_get_min_clock,
    .set_bus_width = rt_sdhci_set_bus_width,
    .reset = rt_sdhci_reset,
    .set_uhs_signaling = rt_sdhci_set_uhs,
};

static const struct rt_sdhci_pltfm_data sdhci_bcm2711_pltfm_data =
{
    .quirks = RT_SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12,
    .ops = &sdhci_iproc_bcm2711_ops,
};

static const struct sdhci_iproc_data bcm2711_data =
{
    .pdata = &sdhci_bcm2711_pltfm_data,
    .mmc_caps = MMC_CAP_3_3V_DDR,
};

static const struct rt_sdhci_pltfm_data sdhci_bcm7211a0_pltfm_data =
{
    .quirks = RT_SDHCI_QUIRK_BROKEN_TIMEOUT_VAL |
              RT_SDHCI_QUIRK_BROKEN_DMA |
              RT_SDHCI_QUIRK_BROKEN_ADMA,
    .ops = &sdhci_iproc_ops,
};

#define BCM7211A0_BASE_CLK_MHZ 100
static const struct sdhci_iproc_data bcm7211a0_data =
{
    .pdata = &sdhci_bcm7211a0_pltfm_data,
    .caps = ((BCM7211A0_BASE_CLK_MHZ / 2) << RT_SDHCI_TIMEOUT_CLK_SHIFT) |
             (BCM7211A0_BASE_CLK_MHZ << RT_SDHCI_CLOCK_BASE_SHIFT) |
             ((0x2 << RT_SDHCI_MAX_BLOCK_SHIFT) & RT_SDHCI_MAX_BLOCK_MASK) |
             RT_SDHCI_CAN_VDD_330 |
             RT_SDHCI_CAN_VDD_180 |
             RT_SDHCI_CAN_DO_SUSPEND |
             RT_SDHCI_CAN_DO_HISPD,
    .caps1 = RT_SDHCI_DRIVER_TYPE_C | RT_SDHCI_DRIVER_TYPE_D,
    .missing_caps = RT_TRUE,
};

static rt_err_t sdhci_iproc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_sdhci_host *host;
    struct sdhci_iproc_host *iproc_host;
    struct rt_sdhci_pltfm_host *pltfm_host;
    struct rt_device *dev = &pdev->parent;
    const struct sdhci_iproc_data *iproc_data = RT_NULL;

    iproc_data = pdev->id->data;
    if (!iproc_data)
    {
        return -RT_EINVAL;
    }

    host = rt_sdhci_pltfm_init(pdev, iproc_data->pdata, sizeof(*iproc_host));
    if (!host)
    {
        return -RT_ERROR;
    }

    pltfm_host = rt_sdhci_priv(host);
    iproc_host = rt_sdhci_pltfm_priv(pltfm_host);

    iproc_host->data = iproc_data;

    err = rt_mmc_of_parse(host->mmc);
    if (err)
    {
        goto _err;
    }

    rt_sdhci_get_property(pdev);

    host->mmc->caps |= iproc_host->data->mmc_caps;

    if (dev->ofw_node)
    {
        pltfm_host->clk = rt_clk_get_by_index(dev, 0);
        if (rt_is_err(pltfm_host->clk))
        {
            err = rt_ptr_err(pltfm_host->clk);
            goto _err;
        }

        err = rt_clk_prepare_enable(pltfm_host->clk);
        if (err)
        {
            goto _err;
        }
    }

    /*
     * Controllers such as bcm2835 SDIO report unreliable/zero voltage bits in
     * CAPABILITIES; rt_sdhci_setup_host() would otherwise overwrite software
     * caps when calling rt_sdhci_read_caps(..., NULL, NULL). Seed caps once
     * here so the read_caps "already done" guard keeps platform values.
     */
    if (iproc_host->data->missing_caps)
    {
        rt_sdhci_read_caps(host, RT_NULL, &iproc_host->data->caps, &iproc_host->data->caps1);
    }

    err = rt_sdhci_set_and_add_host(host);
    if (err)
    {
        goto _err_clk;
    }

    return RT_EOK;

_err_clk:
    if (dev->ofw_node)
    {
        rt_clk_disable_unprepare(pltfm_host->clk);
    }

_err:
    rt_sdhci_pltfm_free(pdev);

    return err;
}

static const struct rt_ofw_node_id sdhci_iproc_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-sdhci", .data = &bcm2835_data },
    { .compatible = "brcm,bcm2711-emmc2", .data = &bcm2711_data },
    { .compatible = "brcm,sdhci-iproc-cygnus", .data = &iproc_cygnus_data},
    { .compatible = "brcm,sdhci-iproc", .data = &iproc_data },
    { .compatible = "brcm,bcm7211a0-sdhci", .data = &bcm7211a0_data },
    { /* sentinel */ }
};

static struct rt_platform_driver sdhci_iproc_driver =
{
    .name = "sdhci-iproc",
    .ids = sdhci_iproc_ofw_ids,

    .probe = sdhci_iproc_probe,
    .remove = rt_sdhci_pltfm_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sdhci_iproc_driver);
