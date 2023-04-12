/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-01     zhs          the first version which add from wch
 */

#include <board.h>
#include "drv_soft_spi.h"

#ifdef BSP_USING_SOFT_SPI

#define LOG_TAG             "drv.soft_spi"
#include <drv_log.h>

static struct ch32_soft_spi_config soft_spi_config[] =
{
#ifdef BSP_USING_SOFT_SPI1
    SOFT_SPI1_BUS_CONFIG,
#endif
#ifdef BSP_USING_SOFT_SPI2
    SOFT_SPI2_BUS_CONFIG,
#endif
};

/**
  * Attach the spi device to soft SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_soft_spi_device_attach(const char *bus_name, const char *device_name, const char *pin_name)
{

    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* initialize the cs pin && select the slave*/
    rt_base_t cs_pin = rt_pin_get(pin_name);
    rt_pin_mode(cs_pin, PIN_MODE_OUTPUT);
    rt_pin_write(cs_pin, PIN_HIGH);

    /* attach the device to soft spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);
    return result;
}

static void ch32_spi_gpio_init(struct ch32_soft_spi *spi)
{
    struct ch32_soft_spi_config *cfg = (struct ch32_soft_spi_config *)spi->cfg;
    rt_pin_mode(cfg->sck, PIN_MODE_OUTPUT);
    rt_pin_mode(cfg->miso, PIN_MODE_INPUT);
    rt_pin_mode(cfg->mosi, PIN_MODE_OUTPUT);

    rt_pin_write(cfg->miso, PIN_HIGH);
    rt_pin_write(cfg->sck, PIN_HIGH);
    rt_pin_write(cfg->mosi, PIN_HIGH);
}

void ch32_tog_sclk(void *data)
{
    struct ch32_soft_spi_config* cfg = (struct ch32_soft_spi_config*)data;
    if(rt_pin_read(cfg->sck) == PIN_HIGH)
    {
        rt_pin_write(cfg->sck, PIN_LOW);
    }
    else
    {
        rt_pin_write(cfg->sck, PIN_HIGH);
    }
}

void ch32_set_sclk(void *data, rt_int32_t state)
{

    struct ch32_soft_spi_config* cfg = (struct ch32_soft_spi_config*)data;
    if (state)
    {
        rt_pin_write(cfg->sck, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->sck, PIN_LOW);
    }
}

void ch32_set_mosi(void *data, rt_int32_t state)
{
    struct ch32_soft_spi_config* cfg = (struct ch32_soft_spi_config*)data;
    if (state)
    {
        rt_pin_write(cfg->mosi, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->mosi, PIN_LOW);
    }
}

void ch32_set_miso(void *data, rt_int32_t state)
{
    struct ch32_soft_spi_config* cfg = (struct ch3_soft_spi_config*)data;
    if (state)
    {
        rt_pin_write(cfg->miso, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->miso, PIN_LOW);
    }
}

rt_int32_t ch32_get_sclk(void *data)
{
    struct ch32_soft_spi_config* cfg = (struct ch32_soft_spi_config*)data;
    return rt_pin_read(cfg->sck);
}

rt_int32_t ch32_get_mosi(void *data)
{
    struct ch32_soft_spi_config* cfg = (struct ch32_soft_spi_config*)data;
    return rt_pin_read(cfg->mosi);
}

rt_int32_t ch32_get_miso(void *data)
{
    struct ch32_soft_spi_config* cfg = (struct ch32_soft_spi_config*)data;
    return rt_pin_read(cfg->miso);
}

void ch32_dir_mosi(void *data, rt_int32_t state)
{
    struct ch32_soft_spi_config* cfg = (struct ch32_soft_spi_config*)data;
    if (state)
    {
        rt_pin_mode(cfg->mosi, PIN_MODE_INPUT);
    }
    else
    {
        rt_pin_mode(cfg->mosi, PIN_MODE_OUTPUT);
    }
}

void ch32_dir_miso(void *data, rt_int32_t state)
{
    struct ch32_soft_spi_config* cfg = (struct ch32_soft_spi_config*)data;
    if (state)
    {
        rt_pin_mode(cfg->miso, PIN_MODE_INPUT);
    }
    else
    {
        rt_pin_mode(cfg->miso, PIN_MODE_OUTPUT);
    }
}

static void ch32_udelay(rt_uint32_t us)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->CMP;

    ticks = us * reload / (1000000 / RT_TICK_PER_SECOND);
    told = SysTick->CNT;
    while (1)
    {
        tnow = SysTick->CNT;
        if (tnow != told)
        {
            if (tnow > told)
            {
                tcnt += tnow - told;
            }
            else
            {
                tcnt += reload - told + tnow;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

static struct rt_spi_bit_ops ch32_soft_spi_ops =
{
    .data = RT_NULL,
    .tog_sclk = ch32_tog_sclk,
    .set_sclk = ch32_set_sclk,
    .set_mosi = ch32_set_mosi,
    .set_miso = ch32_set_miso,
    .get_sclk = ch32_get_sclk,
    .get_mosi = ch32_get_mosi,
    .get_miso = ch32_get_miso,
    .dir_mosi = ch32_dir_mosi,
    .dir_miso = ch32_dir_miso,
    .udelay = ch32_udelay,
    .delay_us = 1,
};

static struct ch32_soft_spi spi_obj[sizeof(soft_spi_config) / sizeof(soft_spi_config[0])];

/* Soft SPI initialization function */
int rt_soft_spi_init(void)
{
    rt_size_t obj_num = sizeof(spi_obj) / sizeof(struct ch32_soft_spi);
    rt_err_t result;

    for (int i = 0; i < obj_num; i++)
    {
        ch32_soft_spi_ops.data = (void *)&soft_spi_config[i];
        spi_obj[i].spi.ops = &ch32_soft_spi_ops;
        spi_obj[i].cfg = (void *)&soft_spi_config[i];
        ch32_spi_gpio_init(&spi_obj[i]);
        result = rt_spi_bit_add_bus(&spi_obj[i].spi, soft_spi_config[i].bus_name, &ch32_soft_spi_ops);
        RT_ASSERT(result == RT_EOK);
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_soft_spi_init);

#endif /* BSP_USING_SOFT_SPI */
