/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-27        Chushicheng    the first version
 */

#ifndef DRV_SPI_H
#define DRV_SPI_H

#include <rtdevice.h>

#ifdef BSP_USING_SPI
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);
#endif /* BSP_USING_SPI */
#endif  /* DRV_SPI_H */
