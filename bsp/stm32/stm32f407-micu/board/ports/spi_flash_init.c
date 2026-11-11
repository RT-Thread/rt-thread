/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-12-15     DaiLingxiang   add spi flash port file
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "dev_spi_flash.h"
#include "dev_spi_flash_sfud.h"

#include <drv_spi.h>
#include <drv_gpio.h>

static int rt_hw_spi_flash_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    rt_hw_spi_device_attach("spi1", "flash0", GET_PIN(A, 4));

    if (RT_NULL == rt_sfud_flash_probe("ZD25WQ", "flash0"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);
