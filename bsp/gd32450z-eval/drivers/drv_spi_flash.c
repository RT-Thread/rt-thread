/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

#include <rthw.h>
#include <finsh.h>

#define SPI_PERIPH                  SPI5
#define SPI_BUS_NAME                "spi5"
#define SPI_FLASH_DEVICE_NAME       "spi50"
#define SPI_FLASH_CHIP              "gd25q16"

static int rt_hw_spi5_init(void)
{
    /* register spi bus */
    {
        rt_err_t result;

        rcu_periph_clock_enable(RCU_GPIOG);
        rcu_periph_clock_enable(RCU_SPI5);

        /* SPI5_CLK(PG13), SPI5_MISO(PG12), SPI5_MOSI(PG14),SPI5_IO2(PG10) and SPI5_IO3(PG11) GPIO pin configuration */
        gpio_af_set(GPIOG, GPIO_AF_5, GPIO_PIN_10|GPIO_PIN_11| GPIO_PIN_12|GPIO_PIN_13| GPIO_PIN_14);
        gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10|GPIO_PIN_11| GPIO_PIN_12|GPIO_PIN_13| GPIO_PIN_14);
        gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ, GPIO_PIN_10|GPIO_PIN_11| GPIO_PIN_12|GPIO_PIN_13| GPIO_PIN_14);

        result = gd32_spi_bus_register(SPI5, SPI_BUS_NAME);
        if (result != RT_EOK)
        {
            return result;
        }
    }

    /* attach cs */
    {
        static struct rt_spi_device spi_device;
        static struct gd32_spi_cs  spi_cs;
        rt_err_t result;

        spi_cs.GPIOx = GPIOG;
        spi_cs.GPIO_Pin = GPIO_PIN_9;

        /* SPI5_CS(PG9) GPIO pin configuration */
        gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_9);
        gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

        gpio_bit_set(GPIOG,GPIO_PIN_9);

        result = rt_spi_bus_attach_device(&spi_device, SPI_FLASH_DEVICE_NAME, SPI_BUS_NAME, (void*)&spi_cs);
        if (result != RT_EOK)
        {
            return result;
        }
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spi5_init);

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
