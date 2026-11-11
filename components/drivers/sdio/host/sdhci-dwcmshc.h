/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-30     RT-Thread    first version
 */

#ifndef __SDHCI_DWCMSHC_H__
#define __SDHCI_DWCMSHC_H__

#include "../dev_sdhci_dm.h"

#define SDHCI_DWCMSHC_ARG2_STUFF RT_GENMASK(31, 16)

/* DWCMSHC specific Mode Select value */
#define DWCMSHC_CTRL_HS400 0x7

/* DWC IP vendor area 1 pointer */
#define DWCMSHC_P_VENDOR_AREA1 0xe8
#define DWCMSHC_AREA1_MASK     RT_GENMASK(11, 0)
/* Offset inside the vendor area 1 */
#define DWCMSHC_HOST_CTRL3      0x8
#define DWCMSHC_EMMC_CONTROL    0x2c
#define DWCMSHC_CARD_IS_EMMC    RT_BIT(0)
#define DWCMSHC_ENHANCED_STROBE RT_BIT(8)
#define DWCMSHC_EMMC_ATCTRL     0x40

/* DWC IP vendor area 2 pointer */
#define DWCMSHC_P_VENDOR_AREA2 0xea

struct sdhci_dwcmshc;

struct sdhci_dwcmshc_drv_data
{
    const struct rt_sdhci_pltfm_data *pdata;

    rt_err_t (*init)(struct rt_sdhci_host *host, struct sdhci_dwcmshc *priv);
    void (*postinit)(struct rt_sdhci_host *host, struct sdhci_dwcmshc *priv);
    void (*remove)(struct rt_sdhci_host *host, struct sdhci_dwcmshc *priv);

    void *vendor_priv;
};

struct sdhci_dwcmshc
{
    struct rt_clk *bus_clk;
    /* P_VENDOR_SPECIFIC_AREA1/2 reg */
    int vendor_specific_area1;
    int vendor_specific_area2;

    void *vendor_priv;
    const struct sdhci_dwcmshc_drv_data *drv_data;
};

extern const struct sdhci_dwcmshc_drv_data sdhci_dwcmshc_generic_drv_data;

rt_err_t sdhci_dwcmshc_probe(struct rt_platform_device *pdev,
                             const struct sdhci_dwcmshc_drv_data *drv_data);
rt_err_t sdhci_dwcmshc_remove(struct rt_platform_device *pdev);

void sdhci_dwcmshc_set_uhs_signaling(struct rt_sdhci_host *host, unsigned int timing);

#endif /* __SDHCI_DWCMSHC_H__ */
