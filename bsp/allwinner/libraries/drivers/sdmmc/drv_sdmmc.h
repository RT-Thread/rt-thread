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
#include <rtdevice.h>

#define SDMMC_CARD_NR 2

#define SDMMC_DEV_NAME_DEF "sdmmc0"

struct dev_sdmmc
{
    int host_id;                            /* host id for each card device */
    struct rt_device_blk_geometry geometry; /* block geometry */
};

void sd_mmc1_init(void);
void sd_mmc1_deinit(void);

#ifdef RT_USING_DEVICE_OPS
#define rt_dev_has_control(dev)         (dev)->ops->control
#define rt_dev_control(dev, cmd, args) (dev)->ops->control(dev, cmd, args)
#define rt_dev_read(dev, pos, buffer, size) (dev)->ops->read(dev, pos, buffer, size)
#define rt_dev_write(dev, pos, buffer, size) (dev)->ops->write(dev, pos, buffer, size)

#else
#define rt_dev_has_control(dev)         (dev)->control
#define rt_dev_control(dev, cmd, args) (dev)->control(dev, cmd, args)
#define rt_dev_read(dev, pos, buffer, size) (dev)->read(dev, pos, buffer, size)
#define rt_dev_write(dev, pos, buffer, size) (dev)->write(dev, pos, buffer, size)

#endif

#endif
