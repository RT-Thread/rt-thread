/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-10-11     fullhan      copy from winbond flash
 */

#ifndef SPI_FLASH_GD_H_
#define SPI_FLASH_GD_H_

#include <rtthread.h>

extern rt_err_t gd_init(const char * flash_device_name, const char * spi_device_name);

#endif /* SPI_FLASH_GD_H_ */
