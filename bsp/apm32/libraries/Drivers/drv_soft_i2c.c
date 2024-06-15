/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 */

#include "board.h"
#include <sys/time.h>

#ifdef RT_USING_I2C

#define DBG_TAG              "drv.i2c"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#if !defined(BSP_USING_I2C1) && !defined(BSP_USING_I2C2) && !defined(BSP_USING_I2C3) && !defined(BSP_USING_I2C4)
    #error "Please define at least one BSP_USING_I2Cx"
#endif

/* apm32 i2c config class */
struct apm32_soft_i2c_config
{
    rt_uint8_t scl_pin;
    rt_uint8_t sda_pin;
    const char *bus_name;
};

/* apm32 i2c dirver class */
struct apm32_soft_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c_bus;
};

static const struct apm32_soft_i2c_config soft_i2c_config[] =
{
#ifdef BSP_USING_I2C1
    {
        BSP_I2C1_SCL_PIN,
        BSP_I2C1_SDA_PIN,
        "i2c1"
    },
#endif
#ifdef BSP_USING_I2C2
    {
        BSP_I2C2_SCL_PIN,
        BSP_I2C2_SDA_PIN,
        "i2c2"
    },
#endif
#ifdef BSP_USING_I2C3
    {
        BSP_I2C3_SCL_PIN,
        BSP_I2C3_SDA_PIN,
        "i2c3"
    },
#endif
#ifdef BSP_USING_I2C4
    {
        BSP_I2C4_SCL_PIN,
        BSP_I2C4_SDA_PIN,
        "i2c4"
    },
#endif
};

static struct apm32_soft_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/**
 * @brief    This function will config gpio of soft i2c.
 *
 * @param    i2c is a pointer to the object of soft i2c.
 */
static void apm32_soft_i2c_gpio_init(struct apm32_soft_i2c *i2c)
{
    struct apm32_soft_i2c_config *cfg = (struct apm32_soft_i2c_config *)i2c->ops.data;

    rt_pin_mode(cfg->scl_pin, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda_pin, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl_pin, PIN_HIGH);
    rt_pin_write(cfg->sda_pin, PIN_HIGH);
}

static void apm32_i2c_pin_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct apm32_soft_i2c);

    for(rt_size_t i = 0; i < obj_num; i++)
    {
        apm32_soft_i2c_gpio_init(&i2c_obj[i]);
    }
}

/**
 * @brief    This function sets the sda pin.
 *
 * @param    data is a pointer to the i2c config class.
 *
 * @param    state is the level of sda pin.
 */
static void apm32_soft_i2c_set_sda(void *data, rt_int32_t state)
{
    struct apm32_soft_i2c_config *cfg = (struct apm32_soft_i2c_config *)data;

    rt_pin_write(cfg->sda_pin, state ? PIN_HIGH : PIN_LOW);
}

/**
 * @brief    This function sets the scl pin.
 *
 * @param    data is a pointer to the i2c config class.
 *
 * @param    state is the level of scl pin.
 */
static void apm32_soft_i2c_set_scl(void *data, rt_int32_t state)
{
    struct apm32_soft_i2c_config *cfg = (struct apm32_soft_i2c_config *)data;

    rt_pin_write(cfg->scl_pin, state ? PIN_HIGH : PIN_LOW);
}

/**
 * @brief    This function gets the sda pin state.
 *
 * @param    data is a pointer to the i2c config class.
 */
static rt_int32_t apm32_soft_i2c_get_sda(void *data)
{
    struct apm32_soft_i2c_config *cfg = (struct apm32_soft_i2c_config *)data;
    return rt_pin_read(cfg->sda_pin);
}

/**
 * @brief    This function gets the scl pin state.
 *
 * @param    data is a pointer to the i2c config class.
 */
static rt_int32_t apm32_soft_i2c_get_scl(void *data)
{
    struct apm32_soft_i2c_config *cfg = (struct apm32_soft_i2c_config *)data;
    return rt_pin_read(cfg->scl_pin);
}

/**
 * @brief    The time delay function in microseconds.
 *
 * @param    us is the microseconds to delay.
 */
static void apm32_soft_i2c_udelay(rt_uint32_t us)
{
    rt_uint32_t count_old = SysTick->VAL;
    rt_uint32_t count_now;
    rt_uint32_t count = 0;
    rt_uint32_t reload = SysTick->LOAD;
    rt_uint32_t count_pre_us = (reload * RT_TICK_PER_SECOND) / 1000000;

    while (count_pre_us * us > count)
    {
        count_now = SysTick->VAL;
        if (count_now != count_old)
        {
            if (count_now < count_old)
            {
                count += count_old - count_now;
            }
            else
            {
                count += reload - count_now + count_old;
            }
            count_old = count_now;
        }
    }
}

/**
 * @brief    This function will unlock i2c, if it is locked.
 *
 * @param    cfg is a pointer to i2c config class.
 *
 * @return   RT_EOK indicates successful unlock, other value indicates failed.
 */
static rt_err_t apm32_i2c_bus_unlock(const struct apm32_soft_i2c_config *cfg)
{
    rt_int32_t i = 0;

    if (PIN_LOW == rt_pin_read(cfg->sda_pin))
    {
        while (i++ < 9)
        {
            rt_pin_write(cfg->scl_pin, PIN_HIGH);
            apm32_soft_i2c_udelay(100);
            rt_pin_write(cfg->scl_pin, PIN_LOW);
            apm32_soft_i2c_udelay(100);
        }
    }
    if (PIN_LOW == rt_pin_read(cfg->sda_pin))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static const struct rt_i2c_bit_ops apm32_bit_ops_default =
{
    .data     = RT_NULL,
    .pin_init = apm32_i2c_pin_init,
    .set_sda  = apm32_soft_i2c_set_sda,
    .set_scl  = apm32_soft_i2c_set_scl,
    .get_sda  = apm32_soft_i2c_get_sda,
    .get_scl  = apm32_soft_i2c_get_scl,
    .udelay   = apm32_soft_i2c_udelay,
    .delay_us = 1,
    .timeout  = 100,
    .i2c_pin_init_flag = RT_FALSE
};

/**
 * @brief    I2C initialization function.
 *
 * @return   RT_EOK indicates successful initialization, other value indicates failed;
 */
int rt_hw_i2c_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct apm32_soft_i2c);
    rt_err_t result;

    for (rt_size_t i = 0; i < obj_num; i++)
    {
        i2c_obj[i].ops = apm32_bit_ops_default;
        i2c_obj[i].ops.data = (void *)&soft_i2c_config[i];
        i2c_obj[i].i2c_bus.priv = &i2c_obj[i].ops;

        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c_bus, soft_i2c_config[i].bus_name);

        RT_ASSERT(result == RT_EOK);

        apm32_i2c_bus_unlock(&soft_i2c_config[i]);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda: %d",
              soft_i2c_config[i].bus_name,
              soft_i2c_config[i].scl_pin,
              soft_i2c_config[i].sda_pin);
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */
