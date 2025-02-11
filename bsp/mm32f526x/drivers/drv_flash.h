/*
 * Copyright (c) 2022-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-22     chasel   first version
 */

#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#include <rtdevice.h>

struct spi_flash_device
{
    struct rt_device                flash_device;
    struct rt_device_blk_geometry   geometry;
    struct rt_spi_device           *rt_spi_device;
    struct rt_mutex                 lock;
    void                           *user_data;
};

int flash_init(void);

#endif
