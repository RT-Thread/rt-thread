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

#ifdef RT_USING_SFUD
#include "spi_flash_sfud.h"
#endif

#ifdef RT_USING_W25QXX
#include "spi_flash_w25qxx.h"
#endif

#include <rthw.h>
#include <finsh.h>

#if defined(RT_USING_SFUD) && defined(RT_USING_W25QXX)
#error "RT_USING_SFUD and RT_USING_W25QXX only need one"
#endif

#define SPI_BUS_NAME                "spi1"
#define SPI_FLASH_DEVICE_NAME       "spi10"
#define SPI_FLASH_CHIP              "W25Q64"

static int rt_hw_spi1_init(void)
{
    /* register spi bus */
    {
        GPIO_InitTypeDef GPIO_InitStructure;
		rt_err_t result;

		__HAL_RCC_GPIOB_CLK_ENABLE();

        GPIO_InitStructure.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStructure.Pull = GPIO_NOPULL;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStructure.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

		result = stm32_spi_bus_register(SPI1, SPI_BUS_NAME);
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
        __HAL_RCC_GPIOD_CLK_ENABLE();
        
        spi_cs.GPIOx = GPIOD;
        spi_cs.GPIO_Pin = GPIO_PIN_13;
        
        GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructure.Pull  = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
        GPIO_InitStructure.Pin = spi_cs.GPIO_Pin;
        HAL_GPIO_Init(spi_cs.GPIOx, &GPIO_InitStructure);
        HAL_GPIO_WritePin(spi_cs.GPIOx, spi_cs.GPIO_Pin, GPIO_PIN_SET);

        result = rt_spi_bus_attach_device(&spi_device, SPI_FLASH_DEVICE_NAME, SPI_BUS_NAME, (void*)&spi_cs);
		if (result != RT_EOK)
		{
			return result;
		}
    }

	return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spi1_init);

#ifdef RT_USING_SFUD
static int rt_hw_spi_flash_with_sfud_init(void)
{
    if (RT_NULL == rt_sfud_flash_probe(SPI_FLASH_CHIP, SPI_FLASH_DEVICE_NAME))
    {
        return RT_ERROR;
    };

	return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_with_sfud_init)
#endif

#ifdef RT_USING_W25QXX
static int rt_hw_spi_flash_init(void)
{
    return w25qxx_init(SPI_FLASH_CHIP, SPI_FLASH_DEVICE_NAME);
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init)
#endif
