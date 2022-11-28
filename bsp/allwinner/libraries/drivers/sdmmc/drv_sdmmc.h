/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     JasonHu      first version
 */

#ifndef DRV_SDMMC_H__
#define DRV_SDMMC_H__

#include <rtdef.h>

#define SDMMC_CARD_NR 2

#define SDMMC_DEV_NAME_DEF "sdmmc0"

struct dev_sdmmc
{
    int host_id;                            /* host id for each card device */
    struct rt_device_blk_geometry geometry; /* block geometry */
};

void sd_mmc1_init(void);
void sd_mmc1_deinit(void);

#endif
