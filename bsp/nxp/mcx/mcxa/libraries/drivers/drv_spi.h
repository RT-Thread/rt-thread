/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2024-03-22     Jisheng Zhang   The first version for mcxn
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtdevice.h>

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t pin);

int rt_hw_spi_init(void);

#endif /*__DRV_SPI_H__ */
