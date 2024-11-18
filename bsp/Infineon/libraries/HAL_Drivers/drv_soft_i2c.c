/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-20     Rbb666       first version
 */

#include <board.h>
#include "drv_soft_i2c.h"

#ifdef RT_USING_I2C

/*#define DRV_DEBUG*/
#define LOG_TAG              "drv.i2c"
#include <drv_log.h>

#if !defined(BSP_USING_I2C1)
    #error "Please define at least one BSP_USING_I2Cx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

static const struct ifx_soft_i2c_config soft_i2c_config[] =
{
    #ifdef BSP_USING_I2C1
    I2C1_BUS_CONFIG,
    #endif
};

static struct ifx_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/**
 * This function initializes the i2c pin.
 *
 * @param ifx i2c dirver class.
 */
static void ifx_i2c_gpio_init(struct ifx_i2c *i2c)
{
    struct ifx_soft_i2c_config *cfg = (struct ifx_soft_i2c_config *)i2c->ops.data;

    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}

static void ifx_i2c_pin_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct ifx_i2c);

    for(rt_size_t i = 0; i < obj_num; i++)
    {
        ifx_i2c_gpio_init(&i2c_obj[i]);
    }
}

/**
 * This function sets the sda pin.
 *
 * @param ifx config class.
 * @param The sda pin state.
 */
static void ifx_set_sda(void *data, rt_int32_t state)
{
    struct ifx_soft_i2c_config *cfg = (struct ifx_soft_i2c_config *)data;

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
 * @param ifx config class.
 * @param The scl pin state.
 */
static void ifx_set_scl(void *data, rt_int32_t state)
{
    struct ifx_soft_i2c_config *cfg = (struct ifx_soft_i2c_config *)data;

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
 * @param The sda pin state.
 */
static rt_int32_t ifx_get_sda(void *data)
{
    struct ifx_soft_i2c_config *cfg = (struct ifx_soft_i2c_config *)data;
    return rt_pin_read(cfg->sda);
}

/**
 * This function gets the scl pin state.
 *
 * @param The scl pin state.
 */
static rt_int32_t ifx_get_scl(void *data)
{
    struct ifx_soft_i2c_config *cfg = (struct ifx_soft_i2c_config *)data;
    return rt_pin_read(cfg->scl);
}

static const struct rt_i2c_bit_ops ifx_bit_ops_default =
{
    .data     = RT_NULL,
    .pin_init = ifx_i2c_pin_init,
    .set_sda  = ifx_set_sda,
    .set_scl  = ifx_set_scl,
    .get_sda  = ifx_get_sda,
    .get_scl  = ifx_get_scl,
    .udelay   = rt_hw_us_delay,
    .delay_us = 1,
    .timeout  = 100,
    .i2c_pin_init_flag = RT_FALSE
};

/**
 * if i2c is locked, this function will unlock it
 *
 * @param ifx config class
 *
 * @return RT_EOK indicates successful unlock.
 */
static rt_err_t ifx_i2c_bus_unlock(const struct ifx_soft_i2c_config *cfg)
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
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct ifx_i2c);
    rt_err_t result;

    for (int i = 0; i < obj_num; i++)
    {
        i2c_obj[i].ops = ifx_bit_ops_default;
        i2c_obj[i].ops.data = (void *)&soft_i2c_config[i];
        i2c_obj[i].i2c_bus.priv = &i2c_obj[i].ops;

        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c_bus, soft_i2c_config[i].bus_name);
        RT_ASSERT(result == RT_EOK);
        ifx_i2c_bus_unlock(&soft_i2c_config[i]);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
              soft_i2c_config[i].bus_name,
              soft_i2c_config[i].scl,
              soft_i2c_config[i].sda);
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */
