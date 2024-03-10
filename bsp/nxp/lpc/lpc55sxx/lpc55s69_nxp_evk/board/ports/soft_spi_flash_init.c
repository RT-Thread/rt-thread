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
#include "spi_flash.h"
#include "spi_flash_sfud.h"
#include "drv_soft_spi.h"
#include "drv_pin.h"

#define cs_pin  GET_PINS(1,5)

static int rt_soft_spi_flash_init(void)
{
    int result = -1;

    result = rt_hw_softspi_device_attach("sspi1", "sspi10", cs_pin);
    rt_kprintf("value is %d\n",result);

    if(result == RT_EOK)
    {
        rt_kprintf("rt_hw_softspi_device_attach successful!\n");
    }

    if (RT_NULL == rt_sfud_flash_probe("W25Q128", "sspi10"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_soft_spi_flash_init);
