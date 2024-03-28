/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 */

#include "drv_common.h"
#include "drv_soft_i2c.h"

#ifdef RT_USING_I2C

#define LOG_TAG              "drv.i2c"
#include <drv_log.h>

#if !defined(BSP_USING_I2C1) && !defined(BSP_USING_I2C2) && \
    !defined(BSP_USING_I2C3)
#error "Please define at least one BSP_USING_I2Cx"
/* this driver can be disabled at menuconfig RT-Thread Components Device Drivers */
#endif

static const struct at32_soft_i2c_config soft_i2c_config[] =
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
};

static struct at32_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/**
 * this function initializes the i2c pin.
 *
 * @param at32 i2c dirver class.
 */
static void at32_i2c_gpio_init(struct at32_i2c *i2c)
{
    struct at32_soft_i2c_config* cfg = (struct at32_soft_i2c_config*)i2c->ops.data;

    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}

/**
 * this function sets the sda pin.
 *
 * @param at32 config class.
 * @param the sda pin state.
 */
static void at32_set_sda(void *data, rt_int32_t state)
{
    struct at32_soft_i2c_config* cfg = (struct at32_soft_i2c_config*)data;
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
 * this function sets the scl pin.
 *
 * @param at32 config class.
 * @param the scl pin state.
 */
static void at32_set_scl(void *data, rt_int32_t state)
{
    struct at32_soft_i2c_config* cfg = (struct at32_soft_i2c_config*)data;
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
 * this function gets the sda pin state.
 *
 * @param the sda pin state.
 */
static rt_int32_t at32_get_sda(void *data)
{
    struct at32_soft_i2c_config* cfg = (struct at32_soft_i2c_config*)data;
    return rt_pin_read(cfg->sda);
}

/**
 * this function gets the scl pin state.
 *
 * @param the scl pin state.
 */
static rt_int32_t at32_get_scl(void *data)
{
    struct at32_soft_i2c_config* cfg = (struct at32_soft_i2c_config*)data;
    return rt_pin_read(cfg->scl);
}

static const struct rt_i2c_bit_ops at32_bit_ops_default =
{
    .data     = RT_NULL,
    .set_sda  = at32_set_sda,
    .set_scl  = at32_set_scl,
    .get_sda  = at32_get_sda,
    .get_scl  = at32_get_scl,
    .udelay   = rt_hw_us_delay,
    .delay_us = 1,
    .timeout  = 100
};

/**
 * if i2c is locked, this function will unlock it
 *
 * @param at32 config class
 *
 * @return RT_EOK indicates successful unlock.
 */
static rt_err_t at32_i2c_bus_unlock(const struct at32_soft_i2c_config *cfg)
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

/* i2c initialization function */
int rt_hw_i2c_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct at32_i2c);
    rt_err_t result;

    for (int i = 0; i < obj_num; i++)
    {
        i2c_obj[i].ops = at32_bit_ops_default;
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c_bus.priv = &i2c_obj[i].ops;
        at32_i2c_gpio_init(&i2c_obj[i]);
        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c_bus, soft_i2c_config[i].bus_name);
        RT_ASSERT(result == RT_EOK);
        at32_i2c_bus_unlock(&soft_i2c_config[i]);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
        soft_i2c_config[i].bus_name,
        soft_i2c_config[i].scl,
        soft_i2c_config[i].sda);
    }

    return RT_EOK;
}

INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */
