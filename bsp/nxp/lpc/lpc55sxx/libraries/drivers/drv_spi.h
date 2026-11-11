/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-18     Chushicheng      The first version for LPC55S6x
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtdevice.h>

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);

#endif /*__DRV_SPI_H__ */
