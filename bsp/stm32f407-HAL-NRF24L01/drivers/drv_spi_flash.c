/*
 * File      : stm32f20x_40x_spi.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-01     aozima       first implementation.
 * 2012-07-27     aozima       fixed variable uninitialized.
 */
#include <board.h>
#include <drv_spi.h>
#include "spi_flash_sfud.h"

static int rt_hw_spi_flash_with_sfud_init(void)
{
	stm32_spi_bus_attach_device(SFUD_SPI_CS_PIN, SFUD_SPI_BUS_NAME, SFUD_SPI_DEV_NAME);
    if (RT_NULL == rt_sfud_flash_probe(SFUD_FLASH_DEV_NAME, SFUD_SPI_DEV_NAME))
    {
        return RT_ERROR;
    };

	return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spi_flash_with_sfud_init);
