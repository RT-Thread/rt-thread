/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_SPI_MCXC162_H__
#define __DRV_SPI_MCXC162_H__

#include <rtdevice.h>

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name,
                                 rt_base_t cs_pin);
int rt_hw_spi_init(void);

#endif /* __DRV_SPI_MCXC162_H__ */
