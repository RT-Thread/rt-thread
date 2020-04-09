/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-03-19     wangyq        the first version
 * 2019-11-01     wangyq        update libraries
 */

#include <rtthread.h>
#include "spi_flash.h"
#include "drv_spiflash.h"
#include "spi_flash_sfud.h"
#include "drv_spi.h"

#if defined(BSP_USING_SPI_FLASH)
int rt_hw_spi_flash_init(void)
{
    es32f0_spi_device_attach(50, "spi0", "spi00");

    if (RT_NULL == rt_sfud_flash_probe("W25Q64", "spi00"))
    {
        return -RT_ERROR;
    };

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);

#endif
