/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-10-20     ZYH            the first version
 */

#ifndef __STM32_SPI_H_
#define __STM32_SPI_H_

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
extern int stm32_spi_register_bus(SPI_TypeDef *SPIx, const char *name);
extern rt_err_t stm32_spi_bus_attach_device(rt_uint32_t pin, const char *bus_name, const char *device_name);
extern int stm32_hw_spi_init(void);
#endif
