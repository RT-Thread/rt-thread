/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#include <rtthread.h>
#include <board.h>
#include "dev_spi_flash.h"
#include "dev_spi_flash_sfud.h"
#include "drv_spi.h"

#if defined(BSP_USING_SPI_FLASH)
static int rt_hw_spi_flash_init(void)
{
    rt_hw_spi_device_attach("spi1", "spi10", GET_PIN(A, 4));

    if (RT_NULL == rt_sfud_flash_probe("W25Q64", "spi10"))
    {
        return -RT_ERROR;
    };

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);
#endif
