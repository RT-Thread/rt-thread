/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-01     lik          first version
 */

#include "drv_soft_i2c.h"

#ifdef RT_USING_I2C
#ifdef BSP_USING_I2C

//#define DRV_DEBUG
#define LOG_TAG "drv.i2c"
#include <drv_log.h>

#if !defined(BSP_USING_I2C0) && !defined(BSP_USING_I2C1)
#error "Please define at least one BSP_USING_I2Cx"
/* this driver can be disabled at menuconfig ? RT-Thread Components ? Device Drivers */
#endif

#ifdef BSP_USING_I2C0
#define I2C0_BUS_CFG             \
    {                            \
        .scl = BSP_I2C0_SCL_PIN, \
        .sda = BSP_I2C0_SDA_PIN, \
        .name = "i2c0",          \
    }
#endif

#ifdef BSP_USING_I2C1
#define I2C1_BUS_CFG             \
    {                            \
        .scl = BSP_I2C1_SCL_PIN, \
        .sda = BSP_I2C1_SDA_PIN, \
        .name = "i2c1",          \
    }
#endif

/* swm config class */
struct swm_soft_i2c_cfg
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *name;
};
/* swm i2c dirver class */
struct swm_soft_i2c_device
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c_bus;
};

static const struct swm_soft_i2c_cfg swm_soft_i2c_cfg[] =
    {
#ifdef BSP_USING_I2C0
        I2C0_BUS_CFG,
#endif
#ifdef BSP_USING_I2C1
        I2C1_BUS_CFG,
#endif
};

static struct swm_soft_i2c_device i2c_obj[sizeof(swm_soft_i2c_cfg) / sizeof(swm_soft_i2c_cfg[0])];

/**
 * This function initializes the i2c pin.
 *
 * @param swm i2c dirver class.
 */
static void swm_i2c_gpio_init(struct swm_soft_i2c_device *i2c)
{
    struct swm_soft_i2c_cfg *soft_i2c_cfg = (struct swm_soft_i2c_cfg *)i2c->ops.data;

    rt_pin_mode(soft_i2c_cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(soft_i2c_cfg->sda, PIN_MODE_OUTPUT_OD);

    rt_pin_write(soft_i2c_cfg->scl, PIN_HIGH);
    rt_pin_write(soft_i2c_cfg->sda, PIN_HIGH);
}

/**
 * This function sets the sda pin.
 *
 * @param swm config class.
 * @param The sda pin state.
 */
static void swm_i2c_set_sda(void *data, rt_int32_t state)
{
    struct swm_soft_i2c_cfg *soft_i2c_cfg = (struct swm_soft_i2c_cfg *)data;
    rt_pin_mode(soft_i2c_cfg->sda, PIN_MODE_OUTPUT_OD);
    if (state)
    {
        rt_pin_write(soft_i2c_cfg->sda, PIN_HIGH);
    }
    else
    {
        rt_pin_write(soft_i2c_cfg->sda, PIN_LOW);
    }
}

/**
 * This function sets the scl pin.
 *
 * @param swm config class.
 * @param The scl pin state.
 */
static void swm_i2c_set_scl(void *data, rt_int32_t state)
{
    struct swm_soft_i2c_cfg *soft_i2c_cfg = (struct swm_soft_i2c_cfg *)data;
    rt_pin_mode(soft_i2c_cfg->scl, PIN_MODE_OUTPUT_OD);
    if (state)
    {
        rt_pin_write(soft_i2c_cfg->scl, PIN_HIGH);
    }
    else
    {
        rt_pin_write(soft_i2c_cfg->scl, PIN_LOW);
    }
}

/**
 * This function gets the sda pin state.
 *
 * @param The sda pin state.
 */
static rt_int32_t swm_i2c_get_sda(void *data)
{
    struct swm_soft_i2c_cfg *soft_i2c_cfg = (struct swm_soft_i2c_cfg *)data;
    rt_pin_mode(soft_i2c_cfg->sda, PIN_MODE_INPUT_PULLDOWN);
    return rt_pin_read(soft_i2c_cfg->sda);
}

/**
 * This function gets the scl pin state.
 *
 * @param The scl pin state.
 */
static rt_int32_t swm_i2c_get_scl(void *data)
{
    struct swm_soft_i2c_cfg *soft_i2c_cfg = (struct swm_soft_i2c_cfg *)data;
    rt_pin_mode(soft_i2c_cfg->scl, PIN_MODE_INPUT_PULLDOWN);
    return rt_pin_read(soft_i2c_cfg->scl);
}

/**
 * The time delay function.
 *
 * @param microseconds.
 */
static void swm_i2c_udelay(rt_uint32_t us)
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

static const struct rt_i2c_bit_ops swm_i2c_bit_ops =
    {
        .data = RT_NULL,
        .set_sda = swm_i2c_set_sda,
        .set_scl = swm_i2c_set_scl,
        .get_sda = swm_i2c_get_sda,
        .get_scl = swm_i2c_get_scl,
        .udelay = swm_i2c_udelay,
        .delay_us = 1,
        .timeout = 100};

/* I2C initialization function */
int swm_i2c_init(void)
{
    rt_err_t result;

    for (int i = 0; i < sizeof(i2c_obj) / sizeof(struct swm_soft_i2c_device); i++)
    {
        i2c_obj[i].ops = swm_i2c_bit_ops;
        i2c_obj[i].ops.data = (void *)&swm_soft_i2c_cfg[i];
        i2c_obj[i].i2c_bus.priv = &i2c_obj[i].ops;
        swm_i2c_gpio_init(&i2c_obj[i]);
        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c_bus, swm_soft_i2c_cfg[i].name);
        RT_ASSERT(result == RT_EOK);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
              swm_soft_i2c_cfg[i].name,
              swm_soft_i2c_cfg[i].scl,
              swm_soft_i2c_cfg[i].sda);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(swm_i2c_init);
#endif /* BSP_USING_I2C */
#endif /* RT_USING_I2C */
