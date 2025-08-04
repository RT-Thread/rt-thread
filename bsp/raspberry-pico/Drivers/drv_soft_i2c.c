/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/06/01     chushicheng  first version
 */
#include "drv_soft_i2c.h"

#ifdef BSP_USING_SOFT_I2C
#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.I2C"

static const struct pico_soft_i2c_config soft_i2c_config[] =
{
#ifdef BSP_USING_SOFT_I2C1
    I2C1_BUS_CONFIG,
#endif
};

static struct pico_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/**
 * This function initializes the i2c pin.
 *
 * @param pico i2c dirver class.
 */
static void pico_i2c_gpio_init(struct pico_i2c *i2c)
{
    struct pico_soft_i2c_config* cfg = (struct pico_soft_i2c_config*)i2c->ops.data;

    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);
    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}

static void pico_i2c_pin_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct pico_i2c);

    for(rt_size_t i = 0; i < obj_num; i++)
    {
        pico_i2c_gpio_init(&i2c_obj[i]);
    }
}

/**
 * This function sets the sda pin.
 *
 * @param pico config class.
 * @param The sda pin state.
 */
static void pico_set_sda(void *data, rt_int32_t state)
{
    struct pico_soft_i2c_config* cfg = (struct pico_soft_i2c_config*)data;
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
 * @param pico config class.
 * @param The scl pin state.
 */
static void pico_set_scl(void *data, rt_int32_t state)
{
    struct pico_soft_i2c_config* cfg = (struct pico_soft_i2c_config*)data;
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
static rt_int32_t pico_get_sda(void *data)
{
    struct pico_soft_i2c_config* cfg = (struct pico_soft_i2c_config*)data;
    return rt_pin_read(cfg->sda);
}

/**
 * This function gets the scl pin state.
 *
 * @param The scl pin state.
 */
static rt_int32_t pico_get_scl(void *data)
{
    struct pico_soft_i2c_config* cfg = (struct pico_soft_i2c_config*)data;
    return rt_pin_read(cfg->scl);
}

/**
 * The time delay function.
 *
 * @param microseconds.
 */
static void pico_udelay(rt_uint32_t us)
{
    busy_wait_us_32(us);
}

static const struct rt_i2c_bit_ops pico_bit_ops_default =
{
    .data     = RT_NULL,
    .pin_init = pico_i2c_pin_init,
    .set_sda  = pico_set_sda,
    .set_scl  = pico_set_scl,
    .get_sda  = pico_get_sda,
    .get_scl  = pico_get_scl,
    .udelay   = pico_udelay,
    .delay_us = 1,
    .timeout  = 100,
    .i2c_pin_init_flag = RT_FALSE
};

/**
 * if i2c is locked, this function will unlock it
 *
 * @param pico config class
 *
 * @return RT_EOK indicates successful unlock.
 */
static rt_err_t pico_i2c_bus_unlock(const struct pico_soft_i2c_config *cfg)
{
    rt_int32_t i = 0;

    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        while (i++ < 9)
        {
            rt_pin_write(cfg->scl, PIN_HIGH);
            pico_udelay(100);
            rt_pin_write(cfg->scl, PIN_LOW);
            pico_udelay(100);
        }
    }
    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/* I2C initialization function */
int rt_soft_i2c_init(void)
{
    rt_err_t result;

    for (rt_size_t i = 0; i < sizeof(i2c_obj) / sizeof(struct pico_i2c); i++)
    {
        i2c_obj[i].ops = pico_bit_ops_default;
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c_bus.priv = &i2c_obj[i].ops;

        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c_bus, soft_i2c_config[i].bus_name);
        RT_ASSERT(result == RT_EOK);
        pico_i2c_bus_unlock(&soft_i2c_config[i]);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
        soft_i2c_config[i].bus_name,
        soft_i2c_config[i].scl,
        soft_i2c_config[i].sda);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_soft_i2c_init);

#endif /* BSP_USING_SOFT_I2C */
