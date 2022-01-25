/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 * 2018-12-10     Zohar_Lee    format file
 * 2020-07-10     lik          rewrite
 */

#include "drv_soft_i2c.h"

#ifdef RT_USING_I2C
#ifdef BSP_USING_I2C

/***************************************************************
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!NOTICE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*In order to use swm drv_soft_i2c,you need to commented out
line 114 (SDA_H(ops);) and line 167 (SDA_H(ops);) in i2c-bit-ops.c
At the same time, add one line (SDA_L(ops);)after line 154 (SCL_L(ops);)
in i2c-bit-ops.c
***************************************************************/

//#define DRV_DEBUG
#define LOG_TAG "drv.i2c"
#include <drv_log.h>

#if !defined(BSP_USING_I2C0) && !defined(BSP_USING_I2C1)
#error "Please define at least one BSP_USING_I2Cx"
/* this driver can be disabled at menuconfig ? RT-Thread Components ? Device Drivers */
#endif

static const struct swm_soft_i2c_cfg soft_i2c_cfg[] =
    {
#ifdef BSP_USING_I2C0
        I2C0_BUS_CFG,
#endif
#ifdef BSP_USING_I2C1
        I2C1_BUS_CFG,
#endif
};

static struct swm_i2c i2c_drv[sizeof(soft_i2c_cfg) / sizeof(soft_i2c_cfg[0])];

/**
 * This function initializes the i2c pin.
 *
 * @param swm i2c dirver class.
 */
static void swm_i2c_gpio_init(struct swm_i2c *i2c)
{
    struct swm_soft_i2c_cfg *cfg = (struct swm_soft_i2c_cfg *)i2c->ops.data;

    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}

/**
 * This function sets the sda pin.
 *
 * @param swm config class.
 * @param The sda pin state.
 */
static void swm_set_sda(void *data, rt_int32_t state)
{
    struct swm_soft_i2c_cfg *cfg = (struct swm_soft_i2c_cfg *)data;
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);
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
 * @param swm config class.
 * @param The scl pin state.
 */
static void swm_set_scl(void *data, rt_int32_t state)
{
    struct swm_soft_i2c_cfg *cfg = (struct swm_soft_i2c_cfg *)data;
    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
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
static rt_int32_t swm_get_sda(void *data)
{
    struct swm_soft_i2c_cfg *cfg = (struct swm_soft_i2c_cfg *)data;
    rt_pin_mode(cfg->sda, PIN_MODE_INPUT_PULLUP);
    return rt_pin_read(cfg->sda);
}

/**
 * This function gets the scl pin state.
 *
 * @param The scl pin state.
 */
static rt_int32_t swm_get_scl(void *data)
{
    struct swm_soft_i2c_cfg *cfg = (struct swm_soft_i2c_cfg *)data;
    rt_pin_mode(cfg->scl, PIN_MODE_INPUT_PULLUP);
    return rt_pin_read(cfg->scl);
}

/**
 * The time delay function.
 *
 * @param microseconds.
 */
static void swm_udelay(rt_uint32_t us)
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

static const struct rt_i2c_bit_ops swm_bit_ops =
    {
        .data = RT_NULL,
        .set_sda = swm_set_sda,
        .set_scl = swm_set_scl,
        .get_sda = swm_get_sda,
        .get_scl = swm_get_scl,
        .udelay = swm_udelay,
        .delay_us = 1,
        .timeout = 100};

/* I2C initialization function */
int rt_hw_i2c_init(void)
{
    rt_err_t result;

    for (int i = 0; i < sizeof(i2c_drv) / sizeof(struct swm_i2c); i++)
    {
        i2c_drv[i].ops = swm_bit_ops;
        i2c_drv[i].ops.data = (void *)&soft_i2c_cfg[i];
        i2c_drv[i].i2c2_bus.priv = &i2c_drv[i].ops;
        swm_i2c_gpio_init(&i2c_drv[i]);
        result = rt_i2c_bit_add_bus(&i2c_drv[i].i2c2_bus, soft_i2c_cfg[i].name);
        RT_ASSERT(result == RT_EOK);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
              soft_i2c_cfg[i].name,
              soft_i2c_cfg[i].scl,
              soft_i2c_cfg[i].sda);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);
#endif /* BSP_USING_I2C */
#endif /* RT_USING_I2C */
