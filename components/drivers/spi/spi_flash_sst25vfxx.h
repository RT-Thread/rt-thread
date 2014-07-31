/*
 * File      : rtdef.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-16     aozima      the first version
 */

#ifndef SPI_FLASH_SST25VFXX_H_INCLUDED
#define SPI_FLASH_SST25VFXX_H_INCLUDED

#include <rtthread.h>
#include <drivers/spi.h>

struct spi_flash_sst25vfxx
{
    struct rt_device                flash_device;
    struct rt_device_blk_geometry   geometry;
    struct rt_spi_device *          rt_spi_device;
    struct rt_mutex                 lock;
};

extern rt_err_t sst25vfxx_init(const char * flash_device_name, const char * spi_device_name);


#endif // SPI_FLASH_SST25VFXX_H_INCLUDED
