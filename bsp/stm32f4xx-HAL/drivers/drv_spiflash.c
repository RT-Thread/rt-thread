/*
 * File      : gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-11-08     ZYH            the first version
 */
#include <rtthread.h>
#ifdef RT_USING_W25QXX
#include <drv_spi.h>
#include "spi_flash_w25qxx.h"
int rt_w25qxx_init(void)
{
	stm32_spi_bus_attach_device(RT_W25QXX_CS_PIN,RT_W25QXX_SPI_BUS_NAME,"w25qxx");
	return w25qxx_init("flash0","w25qxx");
}
INIT_DEVICE_EXPORT(rt_w25qxx_init);

#endif








