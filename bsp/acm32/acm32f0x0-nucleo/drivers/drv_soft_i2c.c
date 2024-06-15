/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-13     AisinoChip   first implementation.
 * 2024-04-23     LZero        Modify the I2C framework.
 */

#ifdef BSP_USING_SOFT_I2C

#include "drv_soft_i2c.h"

#define DBG_TAG              "drv.i2c"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */

static struct acm32_soft_i2c_config soft_i2c_config[] = 
{
#ifdef BSP_USING_I2C0
    I2C0_BUS_CONFIG,
#endif
};

static struct acm32_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

static void drv_i2c_gpio_init(struct acm32_i2c* i2c)
{
    struct acm32_soft_i2c_config* cfg = (struct acm32_soft_i2c_config*)i2c->ops.data;

    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}

static void acm32_i2c_pin_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct acm32_i2c);

    for(rt_size_t i = 0; i < obj_num; i++)
    {
        drv_i2c_gpio_init(&i2c_obj[i]);
    }
}

static void _set_sda(void *data, rt_int32_t state)
{
    struct acm32_soft_i2c_config* cfg = (struct acm32_soft_i2c_config*)data;

    if (state)
    {
        rt_pin_write(cfg->sda, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->sda, PIN_LOW);
    }
}

static void _set_scl(void *data, rt_int32_t state)
{
    struct acm32_soft_i2c_config* cfg = (struct acm32_soft_i2c_config*)data;

    if (state)
    {
        rt_pin_write(cfg->scl, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->scl, PIN_LOW);
    }
}

static rt_int32_t _get_sda(void *data)
{
    struct acm32_soft_i2c_config* cfg = (struct acm32_soft_i2c_config*)data;

    return rt_pin_read(cfg->sda);
}

static rt_int32_t _get_scl(void *data)
{
    struct acm32_soft_i2c_config* cfg = (struct acm32_soft_i2c_config*)data;

    return rt_pin_read(cfg->scl);
}

static void acm32_udelay(rt_uint32_t us)
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

static const struct rt_i2c_bit_ops acm32_bit_ops_default =
{
    .data     = RT_NULL,
    .pin_init = acm32_i2c_pin_init,
    .set_sda  = _set_sda,
    .set_scl  = _set_scl,
    .get_sda  = _get_sda,
    .get_scl  = _get_scl,
    .udelay   = acm32_udelay,
    .delay_us = 1,
    .timeout  = 100,
    .i2c_pin_init_flag = RT_FALSE
};

int rt_soft_i2c_init(void)
{
    rt_err_t result;

    for (rt_size_t i = 0; i < sizeof(i2c_obj) / sizeof(struct acm32_i2c); i++)
    {
        i2c_obj[i].ops = acm32_bit_ops_default;
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c_bus.priv = &i2c_obj[i].ops;
    
        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c_bus, soft_i2c_config[i].bus_name);
        RT_ASSERT(result == RT_EOK);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda: %d",
        soft_i2c_config[i].bus_name,
        soft_i2c_config[i].scl,
        soft_i2c_config[i].sda);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_soft_i2c_init);

#endif /* RT_USING_I2C_BITOPS */

