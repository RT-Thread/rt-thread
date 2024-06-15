/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-06-04     BruceOu           the first version
 */
#include "drv_soft_i2c.h"

#ifdef RT_USING_I2C

#define LOG_TAG              "drv.i2c"
#include <rtdbg.h>

#if !defined(BSP_USING_I2C0) && !defined(BSP_USING_I2C1) && !defined(BSP_USING_I2C2) && !defined(BSP_USING_I2C3)
#error "Please define at least one BSP_USING_I2Cx"
/* this driver can be disabled at menuconfig → RT-Thread Components → Device Drivers */
#endif

static const struct gd32_soft_i2c_config soft_i2c_config[] =
{
#ifdef BSP_USING_I2C0
    I2C0_BUS_CONFIG,
#endif
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

static struct gd32_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/**
  * @brief  This function initializes the i2c pin.
  * @param  i2c
  * @retval None
  */
static void gd32_i2c_gpio_init(struct gd32_i2c *i2c)
{
    struct gd32_soft_i2c_config* cfg = (struct gd32_soft_i2c_config*)i2c->ops.data;

    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}

static void gd32_i2c_pin_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct gd32_i2c);

    for(rt_size_t i = 0; i < obj_num; i++)
    {
        gd32_i2c_gpio_init(&i2c_obj[i]);
    }
}

/**
  * @brief  This function sets the sda pin.
  * @param  data, state
  * @retval None
  */
static void gd32_set_sda(void *data, rt_int32_t state)
{
    struct gd32_soft_i2c_config* cfg = (struct gd32_soft_i2c_config*)data;
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
  * @brief  This function sets the scl pin.
  * @param  data, state
  * @retval None
  */
static void gd32_set_scl(void *data, rt_int32_t state)
{
    struct gd32_soft_i2c_config* cfg = (struct gd32_soft_i2c_config*)data;
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
  * @brief  This function gets the sda pin state.
  * @param  data
  * @retval None
  */
static rt_int32_t gd32_get_sda(void *data)
{
    struct gd32_soft_i2c_config* cfg = (struct gd32_soft_i2c_config*)data;
    return rt_pin_read(cfg->sda);
}


/**
  * @brief  This function gets the scl pin state.
  * @param  data
  * @retval None
  */
static rt_int32_t gd32_get_scl(void *data)
{
    struct gd32_soft_i2c_config* cfg = (struct gd32_soft_i2c_config*)data;
    return rt_pin_read(cfg->scl);
}

/**
  * @brief  The time delay function.
  * @param  us
  * @retval None
  */
static void gd32_udelay(rt_uint32_t us)
{
    int i = ( rcu_clock_freq_get(CK_SYS) / 4000000 * us);
    while(i)
    {
        i--;
    }
}

static const struct rt_i2c_bit_ops gd32_bit_ops_default =
{
    .data     = RT_NULL,
    .pin_init = gd32_i2c_pin_init,
    .set_sda  = gd32_set_sda,
    .set_scl  = gd32_set_scl,
    .get_sda  = gd32_get_sda,
    .get_scl  = gd32_get_scl,
    .udelay   = gd32_udelay,
    .delay_us = 1,
    .timeout  = 100,
    .i2c_pin_init_flag = RT_FALSE
};

/**
  * @brief  if i2c is locked, this function will unlock it
  * @param  cfg
  * @retval RT_EOK indicates successful unlock.
  */
static rt_err_t gd32_i2c_bus_unlock(const struct gd32_soft_i2c_config *cfg)
{
    rt_int32_t i = 0;

    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        while (i++ < 9)
        {
            rt_pin_write(cfg->scl, PIN_HIGH);
            gd32_udelay(100);
            rt_pin_write(cfg->scl, PIN_LOW);
            gd32_udelay(100);
        }
    }
    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
  * @brief  I2C initialization function
  * @param  None
  * @retval RT_EOK indicates successful initialization.
  */
int rt_hw_i2c_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct gd32_i2c);
    rt_err_t result;

    for (rt_size_t = 0; i < obj_num; i++)
    {
        i2c_obj[i].ops = gd32_bit_ops_default;
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c_bus.priv = &i2c_obj[i].ops;

        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c_bus, soft_i2c_config[i].bus_name);

        RT_ASSERT(result == RT_EOK);

        gd32_i2c_bus_unlock(&soft_i2c_config[i]);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
        soft_i2c_config[i].bus_name,
        soft_i2c_config[i].scl,
        soft_i2c_config[i].sda);
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */
