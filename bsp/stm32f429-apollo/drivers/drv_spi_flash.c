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
#include "drv_spi.h"
#include "spi_flash.h"
#include "spi_flash_sfud.h"

#include <rthw.h>
#include <finsh.h>


static int rt_hw_spi5_init(void)
{
    /* register spi bus */
    {
        GPIO_InitTypeDef GPIO_InitStructure;
		rt_err_t result;

		__HAL_RCC_GPIOF_CLK_ENABLE();

        GPIO_InitStructure.Alternate  = GPIO_AF5_SPI5;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStructure.Pull  = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
        GPIO_InitStructure.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);

		result = stm32_spi_bus_register(SPI5, "spi5");
        if (result != RT_EOK)
		{
			return result;
		}
    }

    /* attach cs */
    {
        static struct rt_spi_device spi_device;
        static struct stm32_spi_cs  spi_cs;
		rt_err_t result;

        GPIO_InitTypeDef GPIO_InitStructure;

        GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructure.Pull  = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FAST;

        spi_cs.GPIOx = GPIOF;
        spi_cs.GPIO_Pin = GPIO_PIN_6;
        //__HAL_RCC_GPIOF_CLK_ENABLE();

        GPIO_InitStructure.Pin = spi_cs.GPIO_Pin;
        HAL_GPIO_WritePin(spi_cs.GPIOx, spi_cs.GPIO_Pin, GPIO_PIN_SET);
        HAL_GPIO_Init(spi_cs.GPIOx, &GPIO_InitStructure);

        result = rt_spi_bus_attach_device(&spi_device, "spi50", "spi5", (void*)&spi_cs);
		if (result != RT_EOK)
		{
			return result;
		}
    }

	return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spi5_init);

static int rt_hw_spi_flash_with_sfud_init(void)
{
    if (RT_NULL == rt_sfud_flash_probe("W25Q256", "spi50"))
    {
        return RT_ERROR;
    };

	return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_with_sfud_init)
