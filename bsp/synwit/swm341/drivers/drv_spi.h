/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-01     lik          first version
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include "board.h"

//cannot be used before completion init
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_TypeDef *GPIOx, uint32_t n);
int swm_spi_init(void);

#endif /* __DRV_SPI_H__ */
