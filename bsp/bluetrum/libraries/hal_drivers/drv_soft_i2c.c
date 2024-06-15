/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-07     greedyhao         first version
 */

#include <board.h>
#include "drv_soft_i2c.h"

#ifdef RT_USING_I2C

// #define DRV_DEBUG
#define LOG_TAG              "drv.i2c"
#include <drv_log.h>

#if !defined(BSP_USING_I2C1) && !defined(BSP_USING_I2C2) && !defined(BSP_USING_I2C3) && !defined(BSP_USING_I2C4)
#error "Please define at least one BSP_USING_I2Cx"
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

static const struct ab32_soft_i2c_config soft_i2c_config[] =
{
#ifdef BSP_USING_I2C1
    I2C1_BUS_CONFIG,
#endif
#ifdef BSP_USING_I2C2
    I2C2_BUS_CONFIG,
#endif
#ifdef BSP_USING_I2C3
    I2C3_BUS_CONFIG,
#endif
#ifdef BSP_USING_I2C4
    I2C4_BUS_CONFIG,
#endif
};

static struct ab32_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])] = {0};

/**
 * This function initializes the i2c pin.
 *
 * @param ab32 i2c dirver class.
 */
static void ab32_i2c_gpio_init(struct ab32_i2c *i2c)
{
    struct ab32_soft_i2c_config* cfg = (struct ab32_soft_i2c_config*)i2c->ops.data;

    cfg->scl_mode = PIN_MODE_OUTPUT_OD;
    cfg->sda_mode = PIN_MODE_OUTPUT_OD;
    rt_pin_mode(cfg->scl, cfg->scl_mode);
    rt_pin_mode(cfg->sda, cfg->sda_mode);

    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}

static void ab32_i2c_pin_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct ab32_i2c);

    for(rt_size_t i = 0; i < obj_num; i++)
    {
        ab32_i2c_gpio_init(&i2c_obj[i]);
    }
}

/**
 * This function sets the sda pin.
 *
 * @param data ab32 config class.
 * @param state The sda pin state.
 */
static void ab32_set_sda(void *data, rt_int32_t state)
{
    struct ab32_soft_i2c_config* cfg = (struct ab32_soft_i2c_config*)data;

    if (cfg->sda_mode == PIN_MODE_INPUT_PULLUP) {
        cfg->sda_mode = PIN_MODE_OUTPUT_OD;
        rt_pin_mode(cfg->sda, cfg->sda_mode);
    }

    if (state)
    {
        rt_pin_write(cfg->sda, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->sda, PIN_LOW);
    }
}

/**
 * This function sets the scl pin.
 *
 * @param data ab32 config class.
 * @param state The scl pin state.
 */
static void ab32_set_scl(void *data, rt_int32_t state)
{
    struct ab32_soft_i2c_config* cfg = (struct ab32_soft_i2c_config*)data;

    if (cfg->scl_mode == PIN_MODE_INPUT_PULLUP) {
        cfg->scl_mode = PIN_MODE_OUTPUT_OD;
        rt_pin_mode(cfg->scl, cfg->scl_mode);
    }

    if (state)
    {
        rt_pin_write(cfg->scl, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->scl, PIN_LOW);
    }
}

/**
 * This function gets the sda pin state.
 *
 * @param data The sda pin state.
 */
static rt_int32_t ab32_get_sda(void *data)
{
    struct ab32_soft_i2c_config* cfg = (struct ab32_soft_i2c_config*)data;

    if (cfg->sda_mode != PIN_MODE_INPUT_PULLUP) {
        cfg->sda_mode = PIN_MODE_INPUT_PULLUP;
        rt_pin_mode(cfg->sda, cfg->sda_mode);
    }

    return rt_pin_read(cfg->sda);
}

/**
 * This function gets the scl pin state.
 *
 * @param data The scl pin state.
 */
static rt_int32_t ab32_get_scl(void *data)
{
    struct ab32_soft_i2c_config* cfg = (struct ab32_soft_i2c_config*)data;

    if (cfg->scl_mode == PIN_MODE_INPUT_PULLUP) {
        cfg->scl_mode = PIN_MODE_INPUT_PULLUP;
        rt_pin_mode(cfg->scl, cfg->scl_mode);
    }

    return rt_pin_read(cfg->scl);
}

static const struct rt_i2c_bit_ops ab32_bit_ops_default =
{
    .data     = RT_NULL,
    .pin_init = ab32_i2c_pin_init,
    .set_sda  = ab32_set_sda,
    .set_scl  = ab32_set_scl,
    .get_sda  = ab32_get_sda,
    .get_scl  = ab32_get_scl,
    .udelay   = rt_hw_us_delay,
    .delay_us = 1,
    .timeout  = 100,
    .i2c_pin_init_flag = RT_FALSE
};

/**
 * if i2c is locked, this function will unlock it
 *
 * @param cfg ab32 config class
 *
 * @return RT_EOK indicates successful unlock.
 */
static rt_err_t ab32_i2c_bus_unlock(const struct ab32_soft_i2c_config *cfg)
{
    rt_int32_t i = 0;

    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        while (i++ < 9)
        {
            rt_pin_write(cfg->scl, PIN_HIGH);
            rt_hw_us_delay(100);
            rt_pin_write(cfg->scl, PIN_LOW);
            rt_hw_us_delay(100);
        }
    }
    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/* I2C initialization function */
int rt_hw_i2c_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct ab32_i2c);
    rt_err_t result;

    for (rt_size_t i = 0; i < obj_num; i++)
    {
        i2c_obj[i].ops = ab32_bit_ops_default;
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c_bus.priv = &i2c_obj[i].ops;

        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c_bus, soft_i2c_config[i].bus_name);
        RT_ASSERT(result == RT_EOK);
        ab32_i2c_bus_unlock(&soft_i2c_config[i]);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
        soft_i2c_config[i].bus_name,
        soft_i2c_config[i].scl,
        soft_i2c_config[i].sda);
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif
