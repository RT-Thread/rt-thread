/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-12     fanwenl      1st version
 */

#include <rtthread.h>
#include <rtdevice.h>

#ifdef BSP_USING_FLASH
#include "drv_spi.h"
#include "string.h"
#include "spi_flash.h"
#include "spi_flash_sfud.h"

int wm_nor_flash_init(void)
{
    rt_spi_flash_device_t spi_device;

    wm_spi_bus_attach_device(SPI_Flash_BUS_NAME, "norspi", SPI_Flash_CS_PIN);
    spi_device = rt_sfud_flash_probe("flash0", "norspi");
    if (spi_device == RT_NULL)
    {
        return -RT_ERROR;
    }
    return 0;
}
INIT_DEVICE_EXPORT(wm_nor_flash_init);
#endif
