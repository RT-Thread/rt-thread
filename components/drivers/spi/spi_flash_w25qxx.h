/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-16     aozima      the first version
 * 2012-08-23     aozima       add flash lock.
 */

#ifndef SPI_FLASH_W25QXX_H_INCLUDED
#define SPI_FLASH_W25QXX_H_INCLUDED

#include <rtthread.h>

extern rt_err_t w25qxx_init(const char * flash_device_name,
                            const char * spi_device_name);

#endif // SPI_FLASH_W25QXX_H_INCLUDED
