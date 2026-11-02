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
#include <rtdevice.h>
#include "dev_spi_flash.h"
#include "dev_spi_flash_sfud.h"
#include "drv_spi.h"

#ifdef BSP_USING_SOFT_SPI_FLASH

static struct rt_spi_device soft_spi_flash_device;

static int rt_soft_spi_flash_init(void)
{
    rt_spi_bus_attach_device_cspin(&soft_spi_flash_device, "swspi20", "swspi2",
                                   GET_PIN(B, 14), RT_NULL);

    if (RT_NULL == rt_sfud_flash_probe("W25Q128", "swspi20"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_soft_spi_flash_init);
#endif /* BSP_USING_SOFT_SPI_FLASH */
