/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2025-01-23     CYFS          first version
 */
#include <rthw.h>
#include <rtdevice.h>
#include <dev_spi_bit_ops.h>

#ifdef RT_USING_SOFT_SPI
#if !defined(RT_USING_SOFT_SPI0) &&\
    !defined(RT_USING_SOFT_SPI1) && !defined(RT_USING_SOFT_SPI2) &&\
    !defined(RT_USING_SOFT_SPI3) && !defined(RT_USING_SOFT_SPI4) &&\
    !defined(RT_USING_SOFT_SPI5) && !defined(RT_USING_SOFT_SPI6)
    #error "Please define at least one RT_USING_SOFT_SPIx"
    /*
    This driver can be disabled at:
    menuconfig -> RT-Thread Components -> Device Drivers -> Using I2C device drivers
    */
#endif

#define DBG_ENABLE
#define DBG_TAG                         "SPI_S"
#ifdef RT_SPI_BITOPS_DEBUG
    #define DBG_LEVEL                   DBG_LOG
#endif
#include <rtdbg.h>

/* spi config class */
struct rt_soft_spi_config
{
    rt_base_t       sck;
    rt_base_t       miso;
    rt_base_t       mosi;
    rt_uint32_t     timing_delay;
    const char      *bus_name;
};

/* spi dirver class */
struct rt_soft_spi
{
    struct rt_spi_bit_obj spi;
    struct rt_spi_bit_ops ops;
    struct rt_soft_spi_config *cfg;
};

static struct rt_soft_spi_config soft_spi_config[] =
{
#ifdef RT_USING_SOFT_SPI0
    {
        .sck = RT_SOFT_SPI0_SCK_PIN,
        .miso = RT_SOFT_SPI0_MISO_PIN,
        .mosi = RT_SOFT_SPI0_MOSI_PIN,
        .timing_delay = RT_SOFT_SPI0_TIMING_DELAY,
        .bus_name = RT_SOFT_SPI0_BUS_NAME,
    },
#endif  /*RT_USING_SOFT_SPI0*/
#ifdef RT_USING_SOFT_SPI1
    {
        .sck = RT_SOFT_SPI1_SCK_PIN,
        .miso = RT_SOFT_SPI1_MISO_PIN,
        .mosi = RT_SOFT_SPI1_MOSI_PIN,
        .timing_delay = RT_SOFT_SPI1_TIMING_DELAY,
        .bus_name = RT_SOFT_SPI1_BUS_NAME,
    },
#endif  /*RT_USING_SOFT_SPI1*/
#ifdef RT_USING_SOFT_SPI2
    {
        .sck = RT_SOFT_SPI2_SCK_PIN,
        .miso = RT_SOFT_SPI2_MISO_PIN,
        .mosi = RT_SOFT_SPI2_MOSI_PIN,
        .timing_delay = RT_SOFT_SPI2_TIMING_DELAY,
        .bus_name = RT_SOFT_SPI2_BUS_NAME,
    },
#endif  /*RT_USING_SOFT_SPI2*/
#ifdef RT_USING_SOFT_SPI3
    {
        .sck = RT_SOFT_SPI3_SCK_PIN,
        .miso = RT_SOFT_SPI3_MISO_PIN,
        .mosi = RT_SOFT_SPI3_MOSI_PIN,
        .timing_delay = RT_SOFT_SPI3_TIMING_DELAY,
        .bus_name = RT_SOFT_SPI3_BUS_NAME,
    },
#endif  /*RT_USING_SOFT_SPI3*/
#ifdef RT_USING_SOFT_SPI4
    {
        .sck = RT_SOFT_SPI4_SCK_PIN,
        .miso = RT_SOFT_SPI4_MISO_PIN,
        .mosi = RT_SOFT_SPI4_MOSI_PIN,
        .timing_delay = RT_SOFT_SPI4_TIMING_DELAY,
        .bus_name = RT_SOFT_SPI4_BUS_NAME,
    },
#endif  /*RT_USING_SOFT_SPI4*/
#ifdef RT_USING_SOFT_SPI5
    {
        .sck = RT_SOFT_SPI5_SCK_PIN,
        .miso = RT_SOFT_SPI5_MISO_PIN,
        .mosi = RT_SOFT_SPI5_MOSI_PIN,
        .timing_delay = RT_SOFT_SPI5_TIMING_DELAY,
        .bus_name = RT_SOFT_SPI5_BUS_NAME,
    },
#endif  /*RT_USING_SOFT_SPI5*/
#ifdef RT_USING_SOFT_SPI6
    {
        .sck = RT_SOFT_SPI6_SCK_PIN,
        .miso = RT_SOFT_SPI6_MISO_PIN,
        .mosi = RT_SOFT_SPI6_MOSI_PIN,
        .timing_delay = RT_SOFT_SPI6_TIMING_DELAY,
        .bus_name = RT_SOFT_SPI6_BUS_NAME,
    },
#endif  /*RT_USING_SOFT_SPI6*/

};

static struct rt_soft_spi spi_obj[sizeof(soft_spi_config) / sizeof(soft_spi_config[0])];

static void spi_soft_pin_init(struct rt_soft_spi * soft_spi)
{
    struct rt_soft_spi_config *cfg = (struct rt_soft_spi_config *)soft_spi->cfg;
    rt_pin_mode(cfg->sck, PIN_MODE_OUTPUT);
    rt_pin_mode(cfg->miso, PIN_MODE_INPUT);
    rt_pin_mode(cfg->mosi, PIN_MODE_OUTPUT);

    rt_pin_write(cfg->miso, PIN_HIGH);
    rt_pin_write(cfg->sck, PIN_HIGH);
    rt_pin_write(cfg->mosi, PIN_HIGH);
}


static void spi_soft_tog_sclk(void *data)
{
    struct rt_soft_spi_config *cfg = (struct rt_soft_spi_config *)data;
    if(rt_pin_read(cfg->sck) == PIN_HIGH)
    {
        rt_pin_write(cfg->sck, PIN_LOW);
    }
    else
    {
        rt_pin_write(cfg->sck, PIN_HIGH);
    }
}

static void spi_soft_set_sclk(void *data, rt_int32_t state)
{
    struct rt_soft_spi_config *cfg = (struct rt_soft_spi_config *)data;
    if (state)
    {
        rt_pin_write(cfg->sck, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->sck, PIN_LOW);
    }
}

static void spi_soft_set_mosi(void *data, rt_int32_t state)
{
    struct rt_soft_spi_config *cfg = (struct rt_soft_spi_config *)data;
    if (state)
    {
        rt_pin_write(cfg->mosi, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->mosi, PIN_LOW);
    }
}

static void spi_soft_set_miso(void *data, rt_int32_t state)
{
    struct rt_soft_spi_config *cfg = (struct rt_soft_spi_config *)data;
    if (state)
    {
        rt_pin_write(cfg->miso, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->miso, PIN_LOW);
    }
}

static rt_int32_t spi_soft_get_sclk(void *data)
{
    struct rt_soft_spi_config *cfg = (struct rt_soft_spi_config *)data;
    return rt_pin_read(cfg->sck);
}

static rt_int32_t spi_soft_get_mosi(void *data)
{
    struct rt_soft_spi_config *cfg = (struct rt_soft_spi_config *)data;
    return rt_pin_read(cfg->mosi);
}

static rt_int32_t spi_soft_get_miso(void *data)
{
    struct rt_soft_spi_config *cfg = (struct rt_soft_spi_config *)data;
    return rt_pin_read(cfg->miso);
}

static void spi_soft_dir_mosi(void *data, rt_int32_t state)
{
    struct rt_soft_spi_config *cfg = (struct rt_soft_spi_config *)data;
    if (state)
    {
        rt_pin_mode(cfg->mosi, PIN_MODE_INPUT);
    }
    else
    {
        rt_pin_mode(cfg->mosi, PIN_MODE_OUTPUT);
    }
}

static void spi_soft_dir_miso(void *data, rt_int32_t state)
{
    struct rt_soft_spi_config *cfg = (struct rt_soft_spi_config *)data;
    if (state)
    {
        rt_pin_mode(cfg->miso, PIN_MODE_INPUT);
    }
    else
    {
        rt_pin_mode(cfg->miso, PIN_MODE_OUTPUT);
    }
}

static struct rt_spi_bit_ops soft_spi_ops=
{
    .data = RT_NULL,
    .pin_init = RT_NULL,
    .tog_sclk = spi_soft_tog_sclk,
    .set_sclk = spi_soft_set_sclk,
    .set_mosi = spi_soft_set_mosi,
    .set_miso = spi_soft_set_miso,
    .get_sclk = spi_soft_get_sclk,
    .get_mosi = spi_soft_get_mosi,
    .get_miso = spi_soft_get_miso,
    .dir_mosi = spi_soft_dir_mosi,
    .dir_miso = spi_soft_dir_miso,
    .udelay   = rt_hw_us_delay,
};

/* Soft SPI initialization function */
int rt_soft_spi_init(void)
{
    rt_size_t obj_num = sizeof(spi_obj) / sizeof(struct rt_soft_spi);
    rt_err_t result;

    for (rt_size_t i = 0; i < obj_num; i++)
    {
        rt_memcpy(&spi_obj[i].ops, &soft_spi_ops, sizeof(struct rt_spi_bit_ops));
        spi_obj[i].ops.data = (void *)&soft_spi_config[i];
        spi_obj[i].spi.ops = &soft_spi_ops;
        spi_obj[i].cfg = (void *)&soft_spi_config[i];
        spi_soft_pin_init(&spi_obj[i]);
        spi_obj[i].spi.ops->delay_us = soft_spi_config[i].timing_delay;
        result = rt_spi_bit_add_bus(&spi_obj[i].spi, soft_spi_config[i].bus_name, &spi_obj[i].ops);
        RT_ASSERT(result == RT_EOK);
    }

    return RT_EOK;
}
INIT_PREV_EXPORT(rt_soft_spi_init);

#endif /* RT_USING_SOFT_SPI */

