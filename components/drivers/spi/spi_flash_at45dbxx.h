/*
 * File      : spi_flash_at45dbxx.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2011, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
