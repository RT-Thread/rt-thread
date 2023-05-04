/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-27     SummerGift   add spi flash port file
 */

#include <rtthread.h>

#if defined(BSP_USING_SPI_FLASH)

#include "spi_flash.h"
#include "spi_flash_sfud.h"
#include "drv_spi.h"
#include "drv_gpio.h"

#define CS_PIN   GET_PIN(1,4)     /*  P104,GPIO_AD_B0_04 */

static int rt_hw_spi_flash_init(void)
{
    rt_hw_spi_device_attach("spi3", "spi30", CS_PIN);

    if (RT_NULL == rt_sfud_flash_probe("W25Q256", "spi30"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);
#endif

