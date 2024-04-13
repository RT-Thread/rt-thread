/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-6-14      solar        first version
 */
#include <board.h>
#include <string.h>
#include "drv_soft_spi.h"
#include "drv_config.h"

#if defined(RT_USING_SPI) && defined(RT_USING_SPI_BITOPS) && defined(RT_USING_PIN)

//#define DRV_DEBUG
#define LOG_TAG             "drv.soft_spi"
#include <drv_log.h>

static struct stm32_soft_spi_config soft_spi_config[] =
{
#ifdef BSP_USING_SOFT_SPI1
        SOFT_SPI1_BUS_CONFIG,
#endif
#ifdef BSP_USING_SOFT_SPI2
        SOFT_SPI2_BUS_CONFIG,
#endif
};

static struct stm32_soft_spi spi_obj[sizeof(soft_spi_config) / sizeof(soft_spi_config[0])];

/**
  * Attach the spi device to soft SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_softspi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin)
{

    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* attach the device to soft spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    result = rt_spi_bus_attach_device_cspin(spi_device, device_name, bus_name, cs_pin, RT_NULL);
    return result;
}

static void stm32_spi_gpio_init(struct stm32_soft_spi *spi)
{
    struct stm32_soft_spi_config *cfg = (struct stm32_soft_spi_config *)spi->cfg;
    rt_pin_mode(cfg->sck, PIN_MODE_OUTPUT);
    rt_pin_mode(cfg->miso, PIN_MODE_INPUT);
    rt_pin_mode(cfg->mosi, PIN_MODE_OUTPUT);

    rt_pin_write(cfg->miso, PIN_HIGH);
    rt_pin_write(cfg->sck, PIN_HIGH);
    rt_pin_write(cfg->mosi, PIN_HIGH);
}

void stm32_tog_sclk(void *data)
{
    struct stm32_soft_spi_config* cfg = (struct stm32_soft_spi_config*)data;
    if(rt_pin_read(cfg->sck) == PIN_HIGH)
    {
        rt_pin_write(cfg->sck, PIN_LOW);
    }
    else
    {
        rt_pin_write(cfg->sck, PIN_HIGH);
    }
}

void stm32_set_sclk(void *data, rt_int32_t state)
{

    struct stm32_soft_spi_config* cfg = (struct stm32_soft_spi_config*)data;
    if (state)
    {
        rt_pin_write(cfg->sck, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->sck, PIN_LOW);
    }
}

void stm32_set_mosi(void *data, rt_int32_t state)
{
    struct stm32_soft_spi_config* cfg = (struct stm32_soft_spi_config*)data;
    if (state)
    {
        rt_pin_write(cfg->mosi, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->mosi, PIN_LOW);
    }
}

void stm32_set_miso(void *data, rt_int32_t state)
{
    struct stm32_soft_spi_config* cfg = (struct stm32_soft_spi_config*)data;
    if (state)
    {
        rt_pin_write(cfg->miso, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->miso, PIN_LOW);
    }
}

rt_int32_t stm32_get_sclk(void *data)
{
    struct stm32_soft_spi_config* cfg = (struct stm32_soft_spi_config*)data;
    return rt_pin_read(cfg->sck);
}

rt_int32_t stm32_get_mosi(void *data)
{
    struct stm32_soft_spi_config* cfg = (struct stm32_soft_spi_config*)data;
    return rt_pin_read(cfg->mosi);
}

rt_int32_t stm32_get_miso(void *data)
{
    struct stm32_soft_spi_config* cfg = (struct stm32_soft_spi_config*)data;
    return rt_pin_read(cfg->miso);
}

void stm32_dir_mosi(void *data, rt_int32_t state)
{
    struct stm32_soft_spi_config* cfg = (struct stm32_soft_spi_config*)data;
    if (state)
    {
        rt_pin_mode(cfg->mosi, PIN_MODE_INPUT);
    }
    else
    {
        rt_pin_mode(cfg->mosi, PIN_MODE_OUTPUT);
    }
}

void stm32_dir_miso(void *data, rt_int32_t state)
{
    struct stm32_soft_spi_config* cfg = (struct stm32_soft_spi_config*)data;
    if (state)
    {
        rt_pin_mode(cfg->miso, PIN_MODE_INPUT);
    }
    else
    {
        rt_pin_mode(cfg->miso, PIN_MODE_OUTPUT);
    }
}

static void stm32_udelay(rt_uint32_t us)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    ticks = us * reload / (1000000UL / RT_TICK_PER_SECOND);
    told = SysTick->VAL;
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

static void stm32_pin_init(void)
{
    rt_size_t obj_num = sizeof(spi_obj) / sizeof(struct stm32_soft_spi);

    for(rt_size_t i; i < obj_num; i++)
    {
        stm32_spi_gpio_init(&spi_obj[i]);
    }
}

static struct rt_spi_bit_ops stm32_soft_spi_ops =
    {
        .data = RT_NULL,
        .pin_init = stm32_pin_init,
        .tog_sclk = stm32_tog_sclk,
        .set_sclk = stm32_set_sclk,
        .set_mosi = stm32_set_mosi,
        .set_miso = stm32_set_miso,
        .get_sclk = stm32_get_sclk,
        .get_mosi = stm32_get_mosi,
        .get_miso = stm32_get_miso,
        .dir_mosi = stm32_dir_mosi,
        .dir_miso = stm32_dir_miso,
        .udelay = stm32_udelay,
        .delay_us = 1,
};

/* Soft SPI initialization function */
int rt_hw_softspi_init(void)
{
    rt_size_t obj_num = sizeof(spi_obj) / sizeof(struct stm32_soft_spi);
    rt_err_t result;

    for (rt_size_t i = 0; i < obj_num; i++)
    {
        memcpy(&spi_obj[i].ops, &stm32_soft_spi_ops, sizeof(struct rt_spi_bit_ops));
        spi_obj[i].ops.data = (void *)&soft_spi_config[i];
        spi_obj[i].spi.ops = &stm32_soft_spi_ops;
        spi_obj[i].cfg = (void *)&soft_spi_config[i];
        result = rt_spi_bit_add_bus(&spi_obj[i].spi, soft_spi_config[i].bus_name, &spi_obj[i].ops);
        RT_ASSERT(result == RT_EOK);
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_softspi_init);

#endif /* defined(RT_USING_SPI) && defined(RT_USING_SPI_BITOPS) && defined(RT_USING_PIN) */
