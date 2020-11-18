/*
 * File      : drv_spi_flash.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
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
 * 2018-02-08     RT-Thread    the first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#define DBG_TAG  "FLASH"
#define DBG_LVL  DBG_LOG
#include <rtdbg.h>

#define SPI_FLASH_DEVICE_NAME       "spi00"
#define SPI_FLASH_CHIP              "gd25qxx"

//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(...)   rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)
#endif

#ifdef TINA_USING_SPI_FLASH

#include "spi_flash.h"

#if defined(RT_USING_SFUD)
#include "spi_flash_sfud.h"
rt_spi_flash_device_t spi_device;
int rt_hw_spi_flash_with_sfud_init(void)
{
    DEBUG_PRINTF("%s -> %d\n", __FUNCTION__, __LINE__);
    spi_device = rt_sfud_flash_probe(SPI_FLASH_CHIP, SPI_FLASH_DEVICE_NAME);
    if (spi_device == NULL)
    {
        DEBUG_PRINTF("%s -> %d\n", __FUNCTION__, __LINE__);
        return RT_ERROR;
    };

    DEBUG_PRINTF("%s -> %d\n", __FUNCTION__, __LINE__);
    return RT_EOK;
}
INIT_PREV_EXPORT(rt_hw_spi_flash_with_sfud_init);

#endif

#endif