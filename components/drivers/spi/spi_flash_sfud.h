/*
 * File      : spi_flash_sfud.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2016, RT-Thread Development Team
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
 * 2016-09-28     armink       first version.
 */

#ifndef _SPI_FLASH_SFUD_H_
#define _SPI_FLASH_SFUD_H_

#include <rtthread.h>
#include "./sfud/inc/sfud.h"

/**
 * SPI Flash device initialize by SFUD(Serial Flash Universal Driver) library
 *
 * @param rtt_dev the static RT-Thread's flash device object
 * @param sfud_dev the static SFUD's flash device object
 *
 * @return result
 */
extern rt_err_t rt_sfud_init(struct spi_flash_device *rtt_flash, sfud_flash *sfud_flash);

#endif /* _SPI_FLASH_SFUD_H_ */
