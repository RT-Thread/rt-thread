/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2023/12/01     Raman Gopalan    First version
 */
#include "drv_soft_i2c.h"

#ifdef BSP_USING_SOFT_I2C
#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.I2C"

static const struct avr32_soft_i2c_config soft_i2c_config[] =
{
#ifdef BSP_USING_SOFT_I2C1
    I2C1_BUS_CONFIG,
#endif
};

static struct avr32_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/**
 * This function initializes the I2C pin.
 *
 * @param AVR32 I2C driver class.
 */
static void avr32_i2c_gpio_init(struct avr32_i2c *i2c)
{
    struct avr32_soft_i2c_config* cfg = (struct avr32_soft_i2c_config*)i2c->ops.data;

    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    gpio_set_gpio_open_drain_pin(cfg->scl);

    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);
    gpio_set_gpio_open_drain_pin(cfg->sda);
}

static void avr32_i2c_pin_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct avr32_i2c);

    for(rt_size_t i = 0; i < obj_num; i++)
    {
        avr32_i2c_gpio_init(&i2c_obj[i]);
    }
}

/**
 * This function sets the SDA pin.
 *
 * @param AVR32 config class.
 * @param The SDA pin state.
 */
static void avr32_set_sda(void *data, rt_int32_t state)
{
    struct avr32_soft_i2c_config* cfg = (struct avr32_soft_i2c_config*)data;
    if (state)
    {
    gpio_set_gpio_open_drain_pin(cfg->sda);
    }
    else
    {
    gpio_clr_gpio_open_drain_pin(cfg->sda);
    }
}

/**
 * This function sets the SCL pin.
 *
 * @param AVR32 config class.
 * @param The SCL pin state.
 */
static void avr32_set_scl(void *data, rt_int32_t state)
{
    struct avr32_soft_i2c_config* cfg = (struct avr32_soft_i2c_config*)data;
    if (state)
    {
    gpio_set_gpio_open_drain_pin(cfg->scl);
    }
    else
    {
    gpio_clr_gpio_open_drain_pin(cfg->scl);
    }
}

/**
 * This function gets the SDA pin state.
 *
 * @param The SDA pin state.
 */
static rt_int32_t avr32_get_sda(void *data)
{
    struct avr32_soft_i2c_config* cfg = (struct avr32_soft_i2c_config*)data;
    return gpio_get_gpio_open_drain_pin_output_value(cfg->sda);
}

/**
 * This function gets the SCL pin state.
 *
 * @param The SCL pin state.
 */
static rt_int32_t avr32_get_scl(void *data)
{
    struct avr32_soft_i2c_config* cfg = (struct avr32_soft_i2c_config*)data;
    return gpio_get_gpio_open_drain_pin_output_value(cfg->scl);
}

static const struct rt_i2c_bit_ops avr32_bit_ops_default =
{
    .data     = RT_NULL,
    .pin_init = avr32_i2c_pin_init,
    .set_sda  = avr32_set_sda,
    .set_scl  = avr32_set_scl,
    .get_sda  = avr32_get_sda,
    .get_scl  = avr32_get_scl,
    .udelay   = rt_hw_us_delay,
    .delay_us = 1,
    .timeout  = 100,
    .i2c_pin_init_flag = RT_FALSE
};

/**
 * If I2C is locked, this function will unlock it.
 *
 * @param AVR32 config class
 *
 * @return RT_EOK indicates successful unlock.
 */
static rt_err_t avr32_i2c_bus_unlock(const struct avr32_soft_i2c_config *cfg)
{
    rt_int32_t i = 0;

    if (PIN_LOW == gpio_get_gpio_open_drain_pin_output_value(cfg->sda))
    {
        while (i++ < 9)
        {
        gpio_set_gpio_open_drain_pin(cfg->scl);
        rt_hw_us_delay(100);
        gpio_clr_gpio_open_drain_pin(cfg->scl);
        rt_hw_us_delay(100);
        }
    }
    if (PIN_LOW == gpio_get_gpio_open_drain_pin_output_value(cfg->sda))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/* I2C initialization function */
int rt_sw_i2c_init(void)
{
    rt_err_t result;
    rt_size_t i;

    for (i = 0; i < sizeof(i2c_obj) / sizeof(struct avr32_i2c); i++)
    {
        i2c_obj[i].ops = avr32_bit_ops_default;
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c_bus.priv = &i2c_obj[i].ops;

        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c_bus, soft_i2c_config[i].bus_name);
        RT_ASSERT(result == RT_EOK);
        avr32_i2c_bus_unlock(&soft_i2c_config[i]);

        LOG_D("Software simulation %s init done, pin SCL: %d, pin SDA %d",
        soft_i2c_config[i].bus_name,
        soft_i2c_config[i].scl,
        soft_i2c_config[i].sda);
    }

    return RT_EOK;
}

#endif /* BSP_USING_SOFT_I2C */
