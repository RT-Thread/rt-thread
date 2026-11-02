/*
 * Copyright (c) 2026 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "drv_soft_spi.h"
#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include "rtt_board.h"

#ifdef BSP_USING_SOFT_SPI
#include <dev_spi_bit_ops.h>

#define DBG_TAG    "drv.soft_spi"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

/* 
 * SPI device structure initialization macro
 * This macro initializes a soft SPI configuration structure with pin names and bus name
 * Usage: SPI_INIT_STRUCT(n) where n is the SPI number (0-2)
 */
#define SPI_INIT_STRUCT(n) \
    { \
        .sck_pin_name = BSP_SOFT_SPI##n##_SCK_PIN, \
        .mosi_pin_name = BSP_SOFT_SPI##n##_MOSI_PIN, \
        .miso_pin_name = BSP_SOFT_SPI##n##_MISO_PIN, \
        .bus_name = "soft_spi"#n, \
    }

/* 
 * Dynamically build configuration array using weak symbol.
 * Users define SPI configuration macros in board.h or rtconfig.h:
    #define SPI1_BUS_CONFIG                                  \
    {                                                    \
        .sck = "PD20",                         \
        .mosi = "PD21",                        \
        .miso = "PD22",                        \
        .bus_name = "spi1",                              \
    }
 */

ATTR_WEAK struct hpm_soft_spi_config soft_spi_configs[] = {
#if defined(BSP_USING_SOFT_SPI0)
    SPI_INIT_STRUCT(0),
#endif

#if defined(BSP_USING_SOFT_SPI1)
    SPI_INIT_STRUCT(1),
#endif

#if defined(BSP_USING_SOFT_SPI2)
    SPI_INIT_STRUCT(2),
#endif
};

/* Number of soft SPI devices configured */
#define SOFT_SPI_PTRS_NUM (sizeof(soft_spi_configs) / sizeof(soft_spi_configs[0]))

static struct hpm_soft_spi spi_obj[SOFT_SPI_PTRS_NUM];

/**
 * This function initializes the spi pin.
 *
 * @param hpm spi driver class.
 */
static void hpm_spi_gpio_init(struct hpm_soft_spi *spi)
{
    /* use cfg pointer stored in our hpm_soft_spi instance */
    struct hpm_soft_spi_config* cfg = (struct hpm_soft_spi_config*)spi->cfg;
    rt_base_t sck_pin = rt_pin_get(cfg->sck_pin_name);
    rt_base_t mosi_pin = rt_pin_get(cfg->mosi_pin_name);
    rt_base_t miso_pin = rt_pin_get(cfg->miso_pin_name);
    if (sck_pin < 0 || mosi_pin < 0 || miso_pin < 0)
    {
        LOG_E("spi bus %s pin init error!", cfg->bus_name);
        return;
    }

    rt_pin_mode(sck_pin, PIN_MODE_OUTPUT);
    rt_pin_mode(mosi_pin, PIN_MODE_OUTPUT);
    rt_pin_mode(miso_pin, PIN_MODE_INPUT);

    rt_pin_write(sck_pin, PIN_HIGH);
    rt_pin_write(mosi_pin, PIN_HIGH);
}

static void hpm_spi_pin_init(void)
{
    rt_size_t obj_num = sizeof(spi_obj) / sizeof(struct hpm_soft_spi);

    for(rt_size_t i = 0; i < obj_num; i++)
    {
        hpm_spi_gpio_init(&spi_obj[i]);
    }
}

/**
 * This function toggle the sck pin.
 *
 * @param hpm config class.
 */
static void hpm_tog_sck(void *data)
{
    struct hpm_soft_spi_config* cfg = (struct hpm_soft_spi_config*)data;
    rt_base_t sck_pin = rt_pin_get(cfg->sck_pin_name);
    if(rt_pin_read(sck_pin) == PIN_HIGH)
    {
        rt_pin_write(sck_pin, PIN_LOW);
    }
    else
    {
        rt_pin_write(sck_pin, PIN_HIGH);
    }
}

/**
 * This function sets the sck pin.
 *
 * @param hpm config class.
 * @param The sck pin state.
 */
static void hpm_set_sck(void *data, rt_int32_t state)
{
    struct hpm_soft_spi_config* cfg = (struct hpm_soft_spi_config*)data;
    rt_base_t sck_pin = rt_pin_get(cfg->sck_pin_name);
    if (state)
    {
        rt_pin_write(sck_pin, PIN_HIGH);
    }
    else
    {
        rt_pin_write(sck_pin, PIN_LOW);
    }
}

/**
 * This function sets the mosi pin.
 *
 * @param hpm config class.
 * @param The mosi pin state.
 */
static void hpm_set_mosi(void *data, rt_int32_t state)
{
    struct hpm_soft_spi_config* cfg = (struct hpm_soft_spi_config*)data;
    rt_base_t mosi_pin = rt_pin_get(cfg->mosi_pin_name);
    if (state)
    {
        rt_pin_write(mosi_pin, PIN_HIGH);
    }
    else
    {
        rt_pin_write(mosi_pin, PIN_LOW);
    }
}

/**
 * This function sets the miso pin.
 *
 * @param hpm config class.
 * @param The miso pin state.
 */
static void hpm_set_miso(void *data, rt_int32_t state)
{
    struct hpm_soft_spi_config* cfg = (struct hpm_soft_spi_config*)data;
    rt_base_t miso_pin = rt_pin_get(cfg->miso_pin_name);
    if (state)
    {
        rt_pin_write(miso_pin, PIN_HIGH);
    }
    else
    {
        rt_pin_write(miso_pin, PIN_LOW);
    }
}

/**
 * This function gets the sck pin state.
 *
 * @param The sck pin state.
 */
static rt_int32_t hpm_get_sck(void *data)
{
    struct hpm_soft_spi_config* cfg = (struct hpm_soft_spi_config*)data;
    rt_base_t sck_pin = rt_pin_get(cfg->sck_pin_name);
    return rt_pin_read(sck_pin);
}

/**
 * This function gets the mosi pin state.
 *
 * @param The mosi pin state.
 */
static rt_int32_t hpm_get_mosi(void *data)
{
    struct hpm_soft_spi_config* cfg = (struct hpm_soft_spi_config*)data;
    rt_base_t mosi_pin = rt_pin_get(cfg->mosi_pin_name);
    return rt_pin_read(mosi_pin);
}

/**
 * This function gets the miso pin state.
 *
 * @param The miso pin state.
 */
static rt_int32_t hpm_get_miso(void *data)
{
    struct hpm_soft_spi_config* cfg = (struct hpm_soft_spi_config*)data;
    rt_base_t miso_pin = rt_pin_get(cfg->miso_pin_name);
    return rt_pin_read(miso_pin);
}

/**
 * This function sets the mosi pin direction (input/output).
 *
 * @param hpm config class.
 * @param state: 1 for input, 0 for output.
 */
static void hpm_dir_mosi(void *data, rt_int32_t state)
{
    struct hpm_soft_spi_config* cfg = (struct hpm_soft_spi_config*)data;
    rt_base_t mosi_pin = rt_pin_get(cfg->mosi_pin_name);
    if (state)
    {
        rt_pin_mode(mosi_pin, PIN_MODE_INPUT);
    }
    else
    {
        rt_pin_mode(mosi_pin, PIN_MODE_OUTPUT);
    }
}

/**
 * This function sets the miso pin direction (input/output).
 *
 * @param hpm config class.
 * @param state: 1 for input, 0 for output.
 */
static void hpm_dir_miso(void *data, rt_int32_t state)
{
    struct hpm_soft_spi_config* cfg = (struct hpm_soft_spi_config*)data;
    rt_base_t miso_pin = rt_pin_get(cfg->miso_pin_name);
    if (state)
    {
        rt_pin_mode(miso_pin, PIN_MODE_INPUT);
    }
    else
    {
        rt_pin_mode(miso_pin, PIN_MODE_OUTPUT);
    }
}

/**
 * This function provides microsecond delay.
 *
 * @param us: microseconds to delay.
 */
static void hpm_spi_udelay(rt_uint32_t us)
{
    rt_hw_us_delay(us);
}

static const struct rt_spi_bit_ops hpm_bit_ops_default =
{
    .data        = RT_NULL,
    .pin_init    = hpm_spi_pin_init,
    .tog_sclk    = hpm_tog_sck,
    .set_sclk    = hpm_set_sck,
    .set_mosi    = hpm_set_mosi,
    .set_miso    = hpm_set_miso,
    .get_sclk    = hpm_get_sck,
    .get_mosi    = hpm_get_mosi,
    .get_miso    = hpm_get_miso,
    .dir_mosi    = hpm_dir_mosi,
    .dir_miso    = hpm_dir_miso,
    .udelay      = hpm_spi_udelay,
    .delay_us    = BSP_USING_SOFT_SPI_TIMING_DELAY_US,
};

/**
 * Attach the spi device to soft SPI bus, this function must be used after initialization.
 *
 * @param bus_name: soft spi bus name.
 * @param device_name: spi device name.
 * @param pin_name: chip select pin name.
 *
 * @return RT_EOK indicates successful attachment.
 */
rt_err_t rt_hw_soft_spi_device_attach(const char *bus_name, const char *device_name, const char *pin_name)
{
    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* initialize the cs pin && select the slave */
    rt_base_t cs_pin = rt_pin_get(pin_name);
    rt_pin_mode(cs_pin, PIN_MODE_OUTPUT);
    rt_pin_write(cs_pin, PIN_HIGH);

    /* attach the device to soft spi bus */
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);
    
    if (result == RT_EOK)
    {
        LOG_D("soft spi device %s attach to %s success (cs_pin: %s)",
              device_name, bus_name, pin_name);
    }
    else
    {
        LOG_E("soft spi device %s attach to %s failed", device_name, bus_name);
    }

    return result;
}

/* SPI initialization function */
int rt_software_spi_init(void)
{
    rt_err_t result = RT_EOK;

    for (rt_size_t i = 0; i < SOFT_SPI_PTRS_NUM; i++)
    {
        if ((soft_spi_configs[i].sck_pin_name == RT_NULL) 
            || (soft_spi_configs[i].mosi_pin_name == RT_NULL) || (soft_spi_configs[i].miso_pin_name == RT_NULL))
        {
            LOG_E("soft spi%d pin config error!", i);
            result = -RT_ERROR;
            continue;
        }
        if ((rt_strcmp(soft_spi_configs[i].sck_pin_name, "None") == 0)
            || (rt_strcmp(soft_spi_configs[i].mosi_pin_name, "None") == 0)
            || (rt_strcmp(soft_spi_configs[i].miso_pin_name, "None") == 0))
        {
            LOG_E("soft spi%d pin name is None, please check!", i);
            result = -RT_ERROR;
            continue;
        }
    /* copy default ops into instance, set private data, and register bit-banged bus */
    rt_memcpy(&spi_obj[i].ops, &hpm_bit_ops_default, sizeof(struct rt_spi_bit_ops));
    spi_obj[i].ops.data = (void*)&soft_spi_configs[i];
    /* point bus.ops to our instance ops */
    spi_obj[i].spi.ops = &spi_obj[i].ops;
    spi_obj[i].cfg = (void *)&soft_spi_configs[i];
    /* initialize gpio for this instance */
    hpm_spi_gpio_init(&spi_obj[i]);
    result = rt_spi_bit_add_bus(&spi_obj[i].spi, soft_spi_configs[i].bus_name, &spi_obj[i].ops);
        RT_ASSERT(result == RT_EOK);

        LOG_D("software simulation %s init done, pin sck: %s, pin mosi: %s, pin miso: %s",
              soft_spi_configs[i].bus_name,
              soft_spi_configs[i].sck_pin_name,
              soft_spi_configs[i].mosi_pin_name,
              soft_spi_configs[i].miso_pin_name);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_software_spi_init);

#endif /* BSP_USING_SOFT_SPI */
