/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-10     luobeihai    first version
 */

#include <rtthread.h>
#include "spi_flash.h"
#include "spi_flash_sfud.h"
#include "drv_spi.h"

#if defined(BSP_USING_SPI_FLASH)
static int rt_hw_spi_flash_init(void)
{
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOF);
    rt_hw_spi_device_attach("spi1", "spi10", GPIOF, GPIO_PIN_5);

    if (RT_NULL == rt_sfud_flash_probe("W25Q16", "spi10"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);
#endif

