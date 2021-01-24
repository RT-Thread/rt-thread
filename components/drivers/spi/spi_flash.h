/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016/5/20      bernard      the first version
 * 2020/1/7       redoc        add include
 */

#ifndef SPI_FLASH_H__
#define SPI_FLASH_H__

#include <rtdevice.h>

struct spi_flash_device
{
    struct rt_device                flash_device;
    struct rt_device_blk_geometry   geometry;
    struct rt_spi_device *          rt_spi_device;
    struct rt_mutex                 lock;
    void *                          user_data;
};

typedef struct spi_flash_device *rt_spi_flash_device_t;

#ifdef RT_USING_MTD_NOR
struct spi_flash_mtd
{
    struct rt_mtd_nor_device 			mtd_device;
    struct rt_spi_device *     			rt_spi_device;
    struct rt_mutex            			lock;
    void *                     			user_data;
};
#endif

#endif
