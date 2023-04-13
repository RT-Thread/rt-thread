/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#ifndef __DRV_SPI__
#define __DRV_SPI__

int rt_hw_spi_init(void);

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t cs_pin);

#endif
