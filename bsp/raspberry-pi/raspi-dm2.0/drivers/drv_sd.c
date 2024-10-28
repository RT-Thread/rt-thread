/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-28     zhujiale     The first version
 */

#include <sdhci.h>
#include <rtdevice.h>
#include "drv_sd.h"
#define DBG_TAG "SDHCI"
#ifdef DRV_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>
#define REG_OFFSET_IN_BITS(reg) ((reg) << 3 & 0x18)
struct sdhci_iproc_data {
    const struct sdhci_pltfm_data *pdata;
    rt_uint32_t caps;
    rt_uint32_t caps1;
    rt_uint32_t mmc_caps;
    rt_bool_t missing_caps;
};

struct sdhci_iproc_host {
    const struct sdhci_iproc_data *data;
    rt_uint32_t shadow_cmd;
    rt_uint32_t shadow_blk;
    rt_bool_t is_cmd_shadowed;
    rt_bool_t is_blk_shadowed;
};

static inline rt_uint32_t sdhci_iproc_readl(struct sdhci_host *host, int reg)
{
    rt_uint32_t val = readl(host->ioaddr + reg);

    return val;
}

static rt_uint16_t sdhci_iproc_readw(struct sdhci_host *host, int reg)
{
    struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
    struct sdhci_iproc_host *iproc_host = sdhci_pltfm_priv(pltfm_host);
    rt_uint32_t val;
    rt_uint16_t word;

    if ((reg == SDHCI_TRANSFER_MODE) && iproc_host->is_cmd_shadowed)
    {
        /* Get the saved transfer mode */
        val = iproc_host->shadow_cmd;
    } else if ((reg == SDHCI_BLOCK_SIZE || reg == SDHCI_BLOCK_COUNT) &&
           iproc_host->is_blk_shadowed)
           {
        /* Get the saved block info */
        val = iproc_host->shadow_blk;
    } else {
        val = sdhci_iproc_readl(host, (reg & ~3));
    }
    word = val >> REG_OFFSET_IN_BITS(reg) & 0xffff;
    return word;
}

static rt_uint8_t sdhci_iproc_readb(struct sdhci_host *host, int reg)
{
    rt_uint32_t val = sdhci_iproc_readl(host, (reg & ~3));
    rt_uint8_t byte = val >> REG_OFFSET_IN_BITS(reg) & 0xff;
    return byte;
}

static inline void sdhci_iproc_writel(struct sdhci_host *host, rt_uint32_t val, int reg)
{
    LOG_D("%s: writel [0x%02x] 0x%08x\n",
         mmc_hostname(host->mmc), reg, val);
    writel(val, host->ioaddr + reg);
    if (host->clock <= 400000)
    {
        /* Round up to micro-second four SD clock delay */
        if (host->clock)
            rt_hw_us_delay((4 * 1000000 + host->clock - 1) / host->clock);
        else
            rt_hw_us_delay(10);
    }
}

static void sdhci_iproc_writew(struct sdhci_host *host, rt_uint16_t val, int reg)
{
    struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
    struct sdhci_iproc_host *iproc_host = sdhci_pltfm_priv(pltfm_host);
    rt_uint32_t word_shift = REG_OFFSET_IN_BITS(reg);
    rt_uint32_t mask = 0xffff << word_shift;
    rt_uint32_t oldval, newval;

    if (reg == SDHCI_COMMAND)
    {
        /* Write the block now as we are issuing a command */
        if (iproc_host->is_blk_shadowed)
        {
            sdhci_iproc_writel(host, iproc_host->shadow_blk,
                SDHCI_BLOCK_SIZE);
            iproc_host->is_blk_shadowed = false;
        }
        oldval = iproc_host->shadow_cmd;
        iproc_host->is_cmd_shadowed = false;
    } else if ((reg == SDHCI_BLOCK_SIZE || reg == SDHCI_BLOCK_COUNT) &&
           iproc_host->is_blk_shadowed)
           {
        /* Block size and count are stored in shadow reg */
        oldval = iproc_host->shadow_blk;
    } else {
        /* Read reg, all other registers are not shadowed */
        oldval = sdhci_iproc_readl(host, (reg & ~3));
    }
    newval = (oldval & ~mask) | (val << word_shift);

    if (reg == SDHCI_TRANSFER_MODE)
    {
        /* Save the transfer mode until the command is issued */
        iproc_host->shadow_cmd = newval;
        iproc_host->is_cmd_shadowed = true;
    } else if (reg == SDHCI_BLOCK_SIZE || reg == SDHCI_BLOCK_COUNT)
    {
        /* Save the block info until the command is issued */
        iproc_host->shadow_blk = newval;
        iproc_host->is_blk_shadowed = true;
    } else {
        /* Command or other regular 32-bit write */
        sdhci_iproc_writel(host, newval, reg & ~3);
    }
}

static void sdhci_iproc_writeb(struct sdhci_host *host, rt_uint8_t val, int reg)
{
    rt_uint32_t oldval = sdhci_iproc_readl(host, (reg & ~3));
    rt_uint32_t byte_shift = REG_OFFSET_IN_BITS(reg);
    rt_uint32_t mask = 0xff << byte_shift;
    rt_uint32_t newval = (oldval & ~mask) | (val << byte_shift);

    sdhci_iproc_writel(host, newval, reg & ~3);
}

static const struct sdhci_ops sdhci_iproc_bcm2711_ops = {
    .read_l = sdhci_iproc_readl,
    .read_w = sdhci_iproc_readw,
    .read_b = sdhci_iproc_readb,
    .write_l = sdhci_iproc_writel,
    .write_w = sdhci_iproc_writew,
    .write_b = sdhci_iproc_writeb,
    .set_clock = sdhci_set_clock,
    .set_bus_width = sdhci_set_bus_width,
    .reset = sdhci_reset,
    .set_uhs_signaling = sdhci_set_uhs_signaling,
};

static const struct sdhci_pltfm_data sdhci_bcm2711_pltfm_data = {
    .quirks = SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12,
    .ops = &sdhci_iproc_bcm2711_ops,
};

static const struct sdhci_iproc_data bcm2711_data = {
    .pdata = &sdhci_bcm2711_pltfm_data,
    .mmc_caps = MMC_CAP_3_3V_DDR,
};

rt_err_t bcm2835_probe(struct rt_platform_device *pdev)
{
    struct sdhci_iproc_host *iproc_host;
    const struct sdhci_iproc_data *iproc_data = NULL;
    struct sdhci_host *host;
    struct sdhci_pltfm_host *pltfm_host;
    int ret;
    iproc_data = &bcm2711_data;
    host = sdhci_pltfm_init(pdev, iproc_data->pdata, sizeof(*iproc_host));
    pltfm_host = sdhci_priv(host);
    iproc_host = sdhci_pltfm_priv(pltfm_host);

    iproc_host->data = iproc_data;

    ret = mmc_of_parse(host->mmc);
    if (ret)
        goto err;

    sdhci_get_property(pdev);

    host->mmc->caps |= iproc_host->data->mmc_caps;

    ret = sdhci_add_host(host);
    if (ret)
        goto err;

    return 0;
err:
    return ret;
}

static const struct rt_ofw_node_id bcm2835_ofw_ids[] =
{
    /* { .compatible = "brcm,bcm2711-emmc2"},*/
    { .compatible = "brcm,bcm2835-mmc"},
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835_driver =
{
    .name = "bcm2835",
    .ids = bcm2835_ofw_ids,

    .probe = bcm2835_probe,
    /* .remove = pl011_remove,*/
};


RT_PLATFORM_DRIVER_EXPORT(bcm2835_driver);


