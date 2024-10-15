/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-6-14      solar        first version
 */

#include <rtthread.h>
#include "dev_spi_flash.h"
#include "dev_spi_flash_sfud.h"
#include <drv_spi.h>
#include <drv_soft_spi.h>

#ifdef BSP_USING_SOFT_SPI_FLASH

static int rt_soft_spi_flash_init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    rt_hw_soft_spi_device_attach("sspi2", "sspi20", "PB.14");

    if (RT_NULL == rt_sfud_flash_probe("W25Q128", "sspi20"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_soft_spi_flash_init);
#endif /* BSP_USING_SOFT_SPI_FLASH */
