/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-21     Wangyuqiang  the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "dev_spi_flash.h"
#include "dev_spi_flash_sfud.h"
#include "drv_pin.h"

#define cs_pin GET_PINS(1, 5)

static struct rt_spi_device soft_spi_flash_device;

static int rt_soft_spi_flash_init(void)
{
    int result = -1;

    result = rt_spi_bus_attach_device_cspin(&soft_spi_flash_device, "swspi10", "swspi1",
                                            cs_pin, RT_NULL);
    rt_kprintf("value is %d\n", result);

    if (result == RT_EOK)
    {
        rt_kprintf("attach soft SPI device successful!\n");
    }

    if (RT_NULL == rt_sfud_flash_probe("W25Q128", "swspi10"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_soft_spi_flash_init);
