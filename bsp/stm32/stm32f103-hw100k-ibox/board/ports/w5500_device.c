/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-26     BalanceTWK   add port file
 */

#include "drv_spi.h"
#include "board.h"
#include "drv_gpio.h"
int w5500_spi_device_init()
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    return rt_hw_spi_device_attach("spi2","spi20",GPIOB,GPIO_PIN_12);
}
INIT_DEVICE_EXPORT(w5500_spi_device_init);
