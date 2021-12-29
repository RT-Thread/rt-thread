/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-27     SummerGift   add spi flash port file
 */

#include <rtthread.h>
#include <spi_flash.h>
#include <spi_flash_sfud.h>
#include "drv_spi.h"

static int rt_hw_spi_flash_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
	/*往总线spi3挂载一个spi30的设备*/
    rt_hw_spi_device_attach("spi3", "spi30", GPIOA, GPIO_PIN_10);
	/*使用SFUD探测 spi30从设备，并将spi30连接的flash初始化为块设备，名称为：W25Q128*/
   if (RT_NULL == rt_sfud_flash_probe("W25Q128", "spi30"))
    {
        return -RT_ERROR;
    };  
    return RT_EOK;
}
/*导出到自动初始化*/
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);

