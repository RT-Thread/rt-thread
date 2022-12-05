/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2021-12-15     JasonHu         first version
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtthread.h>

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name);

#endif /* __DRV_SPI_H__ */
