/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-08     QT-one       first version
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* public function */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, HT_GPIO_TypeDef *cs_gpiox, uint16_t cs_gpio_pin);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_SPI_H__ */
