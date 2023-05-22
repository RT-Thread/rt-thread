/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-11     linshire     the first version
 */

#include <board.h>
#include "drv_soft_i2c.h"

#ifdef BSP_USING_SOFT_I2C

#define LOG_TAG              "drv.soft_i2c"
#include <drv_log.h>

#if !defined(BSP_USING_SOFT_I2C1) && !defined(BSP_USING_SOFT_I2C2)
#error "Please define at least one BSP_USING_SOFT_I2Cx"
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

static const struct lpc55s69_soft_i2c_config soft_i2c_config[] =
{
#ifdef BSP_USING_SOFT_I2C1
    SOFT_I2C1_BUS_CONFIG,
#endif
#ifdef BSP_USING_SOFT_I2C2
    SOFT_I2C2_BUS_CONFIG,
#endif
};

static struct lpc55s69_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/**
 * This function initializes the i2c pin.
 *
 * @param lpc55s69 i2c dirver class.
 */
static void lpc55s69_i2c_gpio_init(struct lpc55s69_i2c *i2c)
{
    struct lpc55s69_soft_i2c_config* cfg = (struct lpc55s69_soft_i2c_config*)i2c->ops.data;

    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}

/**
 * This function sets the sda pin.
 *
 * @param lpc55s69 config class.
 * @param The sda pin state.
 */
static void lpc55s69_set_sda(void *data, rt_int32_t state)
{
    struct lpc55s69_soft_i2c_config* cfg = (struct lpc55s69_soft_i2c_config*)data;
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
 * @param lpc55s69 config class.
 * @param The scl pin state.
 */
static void lpc55s69_set_scl(void *data, rt_int32_t state)
{
    struct lpc55s69_soft_i2c_config* cfg = (struct lpc55s69_soft_i2c_config*)data;
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
static rt_int32_t lpc55s69_get_sda(void *data)
{
    struct lpc55s69_soft_i2c_config* cfg = (struct lpc55s69_soft_i2c_config*)data;
    return rt_pin_read(cfg->sda);
}

/**
 * This function gets the scl pin state.
 *
 * @param The scl pin state.
 */
static rt_int32_t lpc55s69_get_scl(void *data)
{
    struct lpc55s69_soft_i2c_config* cfg = (struct lpc55s69_soft_i2c_config*)data;
    return rt_pin_read(cfg->scl);
}
/**
 * The time delay function.
 *
 * @param microseconds.
 */
static void lpc55s69_udelay(rt_uint32_t us)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    ticks = us * reload / (1000000 / RT_TICK_PER_SECOND);
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

static const struct rt_i2c_bit_ops lpc55s69_bit_ops_default =
{
    .data     = RT_NULL,
    .set_sda  = lpc55s69_set_sda,
    .set_scl  = lpc55s69_set_scl,
    .get_sda  = lpc55s69_get_sda,
    .get_scl  = lpc55s69_get_scl,
    .udelay   = lpc55s69_udelay,
    .delay_us = 1,
    .timeout  = 100
};

/**
 * if i2c is locked, this function will unlock it
 *
 * @param lpc55s69 config class
 *
 * @return RT_EOK indicates successful unlock.
 */
static rt_err_t lpc55s69_i2c_bus_unlock(const struct lpc55s69_soft_i2c_config *cfg)
{
    rt_int32_t i = 0;

    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        while (i++ < 9)
        {
            rt_pin_write(cfg->scl, PIN_HIGH);
            lpc55s69_udelay(100);
            rt_pin_write(cfg->scl, PIN_LOW);
            lpc55s69_udelay(100);
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
    rt_err_t result;

    for (rt_size_t i = 0; i < sizeof(i2c_obj) / sizeof(struct lpc55s69_i2c); i++)
    {
        i2c_obj[i].ops = lpc55s69_bit_ops_default;
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c2_bus.priv = &i2c_obj[i].ops;
        lpc55s69_i2c_gpio_init(&i2c_obj[i]);
        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c2_bus, soft_i2c_config[i].bus_name);
        RT_ASSERT(result == RT_EOK);
        lpc55s69_i2c_bus_unlock(&soft_i2c_config[i]);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
        soft_i2c_config[i].bus_name,
        soft_i2c_config[i].scl,
        soft_i2c_config[i].sda);
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif /* BSP_USING_SOFT_I2C */
