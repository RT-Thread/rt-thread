/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-08-13     ChuShicheng   first version
 */

#include <rtdevice.h>

#define DBG_TAG               "I2C"
#ifdef RT_I2C_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif
#include <rtdbg.h>

static const struct soft_i2c_config soft_i2c_config[] =
{
#ifdef BSP_USING_SOFT_I2C1
    {                                                    \
        .scl = BSP_SOFT_I2C1_SCL_PIN,                    \
        .sda = BSP_SOFT_I2C1_SDA_PIN,                    \
        .bus_name = "si2c1",                             \
    },
#endif
#ifdef BSP_USING_SOFT_I2C2
    {                                                    \
        .scl = BSP_SOFT_I2C2_SCL_PIN,                    \
        .sda = BSP_SOFT_I2C2_SDA_PIN,                    \
        .bus_name = "si2c2",                             \
    },
#endif
#ifdef BSP_USING_SOFT_I2C3
    {                                                    \
        .scl = BSP_SOFT_I2C3_SCL_PIN,                    \
        .sda = BSP_SOFT_I2C3_SDA_PIN,                    \
        .bus_name = "si2c3",                             \
    },
#endif
#ifdef BSP_USING_SOFT_I2C4
    {                                                    \
        .scl = BSP_SOFT_I2C4_SCL_PIN,                    \
        .sda = BSP_SOFT_I2C4_SDA_PIN,                    \
        .bus_name = "si2c4",                             \
    },
#endif
};

static struct soft_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/**
 * This function initializes the i2c pin.
 *
 * @param soft i2c dirver class.
 */
static void soft_i2c_gpio_init(struct soft_i2c *i2c)
{
    struct soft_i2c_config* cfg = (struct soft_i2c_config*)i2c->ops.data;

    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}

/**
 * This function sets the sda pin.
 *
 * @param soft config class.
 * @param The sda pin state.
 */
static void set_sda(void *data, rt_int32_t state)
{
    struct soft_i2c_config* cfg = (struct soft_i2c_config*)data;
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
 * @param soft config class.
 * @param The scl pin state.
 */
static void set_scl(void *data, rt_int32_t state)
{
    struct soft_i2c_config* cfg = (struct soft_i2c_config*)data;
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
static rt_int32_t get_sda(void *data)
{
    struct soft_i2c_config* cfg = (struct soft_i2c_config*)data;
    return rt_pin_read(cfg->sda);
}

/**
 * This function gets the scl pin state.
 *
 * @param The scl pin state.
 */
static rt_int32_t get_scl(void *data)
{
    struct soft_i2c_config* cfg = (struct soft_i2c_config*)data;
    return rt_pin_read(cfg->scl);
}

static const struct rt_i2c_bit_ops bit_ops_default =
{
    .data     = RT_NULL,
    .set_sda  = set_sda,
    .set_scl  = set_scl,
    .get_sda  = get_sda,
    .get_scl  = get_scl,
    .udelay   = rt_hw_us_delay,
    .delay_us = 1,
    .timeout  = 100
};

/**
 * if i2c is locked, this function will unlock it
 *
 * @param soft config class
 *
 * @return RT_EOK indicates successful unlock.
 */
static rt_err_t soft_i2c_bus_unlock(const struct soft_i2c_config *cfg)
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
int rt_soft_i2c_init(void)
{
    rt_err_t result;

    for (rt_size_t i = 0; i < sizeof(i2c_obj) / sizeof(struct soft_i2c); i++)
    {
        i2c_obj[i].ops = bit_ops_default;
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c_bus.priv = &i2c_obj[i].ops;
        soft_i2c_gpio_init(&i2c_obj[i]);
        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c_bus, soft_i2c_config[i].bus_name);
        RT_ASSERT(result == RT_EOK);
        soft_i2c_bus_unlock(&soft_i2c_config[i]);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
        soft_i2c_config[i].bus_name,
        soft_i2c_config[i].scl,
        soft_i2c_config[i].sda);

        LOG_W("pin scl: %d, pin sda %d",BSP_SOFT_I2C1_SCL_PIN,BSP_SOFT_I2C1_SDA_PIN);
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_soft_i2c_init);
