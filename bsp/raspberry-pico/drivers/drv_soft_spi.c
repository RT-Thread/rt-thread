/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-02     Chushicheng  the first version
 */
#include "drv_soft_spi.h"
#include "board.h"

#if defined BSP_USING_SOFT_SPI
#define LOG_TAG             "drv.soft_spi"
#include <rtdbg.h>

static struct pico_soft_spi_config soft_spi_config[] =
{
#ifdef BSP_USING_SOFT_SPI0
    SOFT_SPI0_BUS_CONFIG,
#endif
#ifdef BSP_USING_SOFT_SPI1
    SOFT_SPI1_BUS_CONFIG,
#endif
};

static struct pico_soft_spi spi_obj[sizeof(soft_spi_config) / sizeof(soft_spi_config[0])];

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

static void pico_spi_gpio_init(struct pico_soft_spi *spi)
{
    struct pico_soft_spi_config *cfg = (struct pico_soft_spi_config *)spi->cfg;
    rt_pin_mode(cfg->sck, PIN_MODE_OUTPUT);
    rt_pin_mode(cfg->miso, PIN_MODE_INPUT);
    rt_pin_mode(cfg->mosi, PIN_MODE_OUTPUT);

    rt_pin_write(cfg->miso, PIN_HIGH);
    rt_pin_write(cfg->sck, PIN_HIGH);
    rt_pin_write(cfg->mosi, PIN_HIGH);
}

static void pico_tog_sclk(void *data)
{
    struct pico_soft_spi_config* cfg = (struct pico_soft_spi_config*)data;
    if(rt_pin_read(cfg->sck) == PIN_HIGH)
    {
        rt_pin_write(cfg->sck, PIN_LOW);
    }
    else
    {
        rt_pin_write(cfg->sck, PIN_HIGH);
    }
}

static void pico_set_sclk(void *data, rt_int32_t state)
{
    struct pico_soft_spi_config* cfg = (struct pico_soft_spi_config*)data;
    if (state)
    {
        rt_pin_write(cfg->sck, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->sck, PIN_LOW);
    }
}

static void pico_set_mosi(void *data, rt_int32_t state)
{
    struct pico_soft_spi_config* cfg = (struct pico_soft_spi_config*)data;
    if (state)
    {
        rt_pin_write(cfg->mosi, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->mosi, PIN_LOW);
    }
}

static void pico_set_miso(void *data, rt_int32_t state)
{
    struct pico_soft_spi_config* cfg = (struct pico_soft_spi_config*)data;
    if (state)
    {
        rt_pin_write(cfg->miso, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->miso, PIN_LOW);
    }
}

static rt_int32_t pico_get_sclk(void *data)
{
    struct pico_soft_spi_config* cfg = (struct pico_soft_spi_config*)data;
    return rt_pin_read(cfg->sck);
}

static rt_int32_t pico_get_mosi(void *data)
{
    struct pico_soft_spi_config* cfg = (struct pico_soft_spi_config*)data;
    return rt_pin_read(cfg->mosi);
}

static rt_int32_t pico_get_miso(void *data)
{
    struct pico_soft_spi_config* cfg = (struct pico_soft_spi_config*)data;
    return rt_pin_read(cfg->miso);
}

static void pico_dir_mosi(void *data, rt_int32_t state)
{
    struct pico_soft_spi_config* cfg = (struct pico_soft_spi_config*)data;
    if (state)
    {
        rt_pin_mode(cfg->mosi, PIN_MODE_INPUT);
    }
    else
    {
        rt_pin_mode(cfg->mosi, PIN_MODE_OUTPUT);
    }
}

static void pico_dir_miso(void *data, rt_int32_t state)
{
    struct pico_soft_spi_config* cfg = (struct pico_soft_spi_config*)data;
    if (state)
    {
        rt_pin_mode(cfg->miso, PIN_MODE_INPUT);
    }
    else
    {
        rt_pin_mode(cfg->miso, PIN_MODE_OUTPUT);
    }
}

static void pico_udelay(rt_uint32_t us)
{
    busy_wait_us_32(us);
}

static void pico_pin_init(void)
{
    rt_size_t obj_num = sizeof(spi_obj) / sizeof(struct pico_soft_spi);

    for(rt_size_t i = 0; i < obj_num; i++)
    {
        pico_spi_gpio_init(&spi_obj[i]);
    }
}

static struct rt_spi_bit_ops pico_soft_spi_ops =
{
    .data = RT_NULL,
    .pin_init = pico_pin_init,
    .tog_sclk = pico_tog_sclk,
    .set_sclk = pico_set_sclk,
    .set_mosi = pico_set_mosi,
    .set_miso = pico_set_miso,
    .get_sclk = pico_get_sclk,
    .get_mosi = pico_get_mosi,
    .get_miso = pico_get_miso,
    .dir_mosi = pico_dir_mosi,
    .dir_miso = pico_dir_miso,
    .udelay = pico_udelay,
    .delay_us = 1,
};

/* Soft SPI initialization function */
int rt_hw_softspi_init(void)
{
    rt_size_t obj_num = sizeof(spi_obj) / sizeof(struct pico_soft_spi);
    rt_err_t result;

    for (rt_size_t i = 0; i < obj_num; i++)
    {
        pico_soft_spi_ops.data = (void *)&soft_spi_config[i];
        spi_obj[i].spi.ops = &pico_soft_spi_ops;
        spi_obj[i].cfg = (void *)&soft_spi_config[i];

        result = rt_spi_bit_add_bus(&spi_obj[i].spi, soft_spi_config[i].bus_name, &pico_soft_spi_ops);
        RT_ASSERT(result == RT_EOK);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_softspi_init);

#endif /* BSP_USING_SOFT_SPI */
