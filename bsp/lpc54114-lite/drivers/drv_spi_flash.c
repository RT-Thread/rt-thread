/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "drv_spi.h"
#include "drv_spi_flash.h"

#include "rtthread.h"
#include "rtdevice.h"
#include "spi_flash.h"
#include "spi_flash_sfud.h"

#define RT_SPI_FLASH_CS_PIN (2)

int rt_hw_flash_init(void)
{
    rt_err_t result;

    result = lpc_spi_bus_attach_device("spi2", "spi20", RT_SPI_FLASH_CS_PIN);
    if(result != RT_EOK)
    {
        return result;
    }

    if(rt_sfud_flash_probe("flash0", "spi20") == RT_NULL)
    {
        return RT_ERROR;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_flash_init);
