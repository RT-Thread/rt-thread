/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-29     luobeihai    first version
 */

#include <rtthread.h>
#include "dev_spi_flash.h"
#include "dev_spi_flash_sfud.h"
#include "drv_spi.h"

#if defined(BSP_USING_SPI_FLASH)
static int rt_hw_spi_flash_init(void)
{
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA);
    rt_hw_spi_device_attach("spi3", "spi30", GPIOA, GPIO_PIN_15);

    if (RT_NULL == rt_sfud_flash_probe("W25Q16", "spi30"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);
#endif
