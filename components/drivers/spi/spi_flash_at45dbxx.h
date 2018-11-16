/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-16     aozima       the first version
 */

#ifndef SPI_FLASH_AT45DBXX_H_INCLUDED
#define SPI_FLASH_AT45DBXX_H_INCLUDED

#include <rtthread.h>
#include <drivers/spi.h>

struct spi_flash_at45dbxx
{
    struct rt_device                flash_device;
    struct rt_device_blk_geometry   geometry;
    struct rt_spi_device *          rt_spi_device;
};

extern rt_err_t at45dbxx_init(const char * flash_device_name, const char * spi_device_name);


#endif // SPI_FLASH_AT45DBXX_H_INCLUDED
