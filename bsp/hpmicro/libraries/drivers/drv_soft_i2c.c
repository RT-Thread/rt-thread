/*
 * Copyright (c) 2026 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "drv_soft_i2c.h"
#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include "rtt_board.h"

#ifdef BSP_USING_SOFT_I2C

#define DBG_TAG    "drv.soft_i2c"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

/* 
 * I2C device structure initialization macro
 * This macro initializes a soft I2C configuration structure with pin names and bus name
 * Usage: I2C_INIT_STRUCT(n) where n is the I2C number (1-8)
 */
#define I2C_INIT_STRUCT(n) \
    { \
        .scl_pin_name = BSP_SOFT_I2C##n##_SCL_PIN, \
        .sda_pin_name = BSP_SOFT_I2C##n##_SDA_PIN, \
        .bus_name = "soft_i2c"#n, \
    }

/* 
 * Dynamically build configuration array using weak symbol.
 * Users define I2C configuration macros in board.h or rtconfig.h:
    #define I2C1_BUS_CONFIG                                  \
    {                                                    \
        .scl = "PD20",                         \
        .sda = "PD21",                         \
        .bus_name = "i2c1",                              \
    }
 */

ATTR_WEAK struct hpm_soft_i2c_config soft_i2c_configs[] = {
#if defined(BSP_USING_SOFT_I2C0)
    I2C_INIT_STRUCT(0),
#endif

#if defined(BSP_USING_SOFT_I2C1)
    I2C_INIT_STRUCT(1),
#endif

#if defined(BSP_USING_SOFT_I2C2)
    I2C_INIT_STRUCT(2),
#endif

#if defined(BSP_USING_SOFT_I2C3)
    I2C_INIT_STRUCT(3),
#endif

#if defined(BSP_USING_SOFT_I2C4)
    I2C_INIT_STRUCT(4),
#endif

#if defined(BSP_USING_SOFT_I2C5)
    I2C_INIT_STRUCT(5),
#endif

#if defined(BSP_USING_SOFT_I2C6)
    I2C_INIT_STRUCT(6),
#endif

#if defined(BSP_USING_SOFT_I2C7)
    I2C_INIT_STRUCT(7),
#endif

#if defined(BSP_USING_SOFT_I2C8)
    I2C_INIT_STRUCT(8),
#endif
};

/* Number of soft I2C devices configured */
#define SOFT_I2C_PTRS_NUM (sizeof(soft_i2c_configs) / sizeof(soft_i2c_configs[0]))

static struct hpm_i2c i2c_obj[SOFT_I2C_PTRS_NUM];

/**
 * This function initializes the i2c pin.
 *
 * @param hpm i2c driver class.
 */
static void hpm_i2c_gpio_init(struct hpm_i2c *i2c)
{
    struct hpm_soft_i2c_config* cfg = (struct hpm_soft_i2c_config*)i2c->ops.data;
    rt_base_t scl_pin = rt_pin_get(cfg->scl_pin_name);
    rt_base_t sda_pin = rt_pin_get(cfg->sda_pin_name);
    if (scl_pin < 0 || sda_pin < 0)
    {
        LOG_E("i2c bus %s pin init error!", cfg->bus_name);
        return;
    }

    rt_pin_mode(scl_pin, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(sda_pin, PIN_MODE_OUTPUT_OD);

    rt_pin_write(scl_pin, PIN_HIGH);
    rt_pin_write(sda_pin, PIN_HIGH);
}

static void hpm_i2c_pin_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct hpm_i2c);

    for(rt_size_t i = 0; i < obj_num; i++)
    {
        hpm_i2c_gpio_init(&i2c_obj[i]);
    }
}

/**
 * This function sets the sda pin.
 *
 * @param hpm config class.
 * @param The sda pin state.
 */
static void hpm_set_sda(void *data, rt_int32_t state)
{
    struct hpm_soft_i2c_config* cfg = (struct hpm_soft_i2c_config*)data;
    rt_base_t sda_pin = rt_pin_get(cfg->sda_pin_name);
    if (state)
    {
        rt_pin_write(sda_pin, PIN_HIGH);
    }
    else
    {
        rt_pin_write(sda_pin, PIN_LOW);
    }
}

/**
 * This function sets the scl pin.
 *
 * @param hpm config class.
 * @param The scl pin state.
 */
static void hpm_set_scl(void *data, rt_int32_t state)
{
    struct hpm_soft_i2c_config* cfg = (struct hpm_soft_i2c_config*)data;
    rt_base_t scl_pin = rt_pin_get(cfg->scl_pin_name);
    if (state)
    {
        rt_pin_write(scl_pin, PIN_HIGH);
    }
    else
    {
        rt_pin_write(scl_pin, PIN_LOW);
    }
}

/**
 * This function gets the sda pin state.
 *
 * @param The sda pin state.
 */
static rt_int32_t hpm_get_sda(void *data)
{
    struct hpm_soft_i2c_config* cfg = (struct hpm_soft_i2c_config*)data;
    rt_base_t sda_pin = rt_pin_get(cfg->sda_pin_name);
    return rt_pin_read(sda_pin);
}

/**
 * This function gets the scl pin state.
 *
 * @param The scl pin state.
 */
static rt_int32_t hpm_get_scl(void *data)
{
    struct hpm_soft_i2c_config* cfg = (struct hpm_soft_i2c_config*)data;
    rt_base_t scl_pin = rt_pin_get(cfg->scl_pin_name);
    return rt_pin_read(scl_pin);
}

static const struct rt_i2c_bit_ops hpm_bit_ops_default =
{
    .data     = RT_NULL,
    .pin_init = hpm_i2c_pin_init,
    .set_sda  = hpm_set_sda,
    .set_scl  = hpm_set_scl,
    .get_sda  = hpm_get_sda,
    .get_scl  = hpm_get_scl,
    .udelay   = rt_hw_us_delay,
    .delay_us = BSP_USING_SOFT_I2C_TIMING_DELAY_US,
    .timeout  = BSP_USING_SOFT_I2C_TIMING_TIMEOUT,
    .i2c_pin_init_flag = RT_FALSE
};

/**
 * if i2c is locked, this function will unlock it
 *
 * @param hpm config class
 *
 * @return RT_EOK indicates successful unlock.
 */
static rt_err_t hpm_i2c_bus_unlock(const struct hpm_soft_i2c_config *cfg)
{
    rt_int32_t i = 0;
    rt_base_t sda_pin = rt_pin_get(cfg->sda_pin_name);
    rt_base_t scl_pin = rt_pin_get(cfg->scl_pin_name);
    if (PIN_LOW == rt_pin_read(sda_pin))
    {
        while (i++ < 9)
        {
            rt_pin_write(scl_pin, PIN_HIGH);
            rt_hw_us_delay(100);
            rt_pin_write(scl_pin, PIN_LOW);
            rt_hw_us_delay(100);
        }
    }
    if (PIN_LOW == rt_pin_read(sda_pin))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/* I2C initialization function */
int rt_software_i2c_init(void)
{
    rt_err_t result = RT_EOK;
    for (rt_size_t i = 0; i < SOFT_I2C_PTRS_NUM; i++)
    {
        if ((soft_i2c_configs[i].scl_pin_name == RT_NULL) 
            || (soft_i2c_configs[i].sda_pin_name == RT_NULL))
        {
            LOG_E("soft i2c%d pin config error!", i);
            result = -RT_ERROR;
            continue;
        }
        if ((rt_strcmp(soft_i2c_configs[i].scl_pin_name, "None") == 0)
            || (rt_strcmp(soft_i2c_configs[i].sda_pin_name, "None") == 0))
        {
            LOG_E("soft i2c%d pin name is None, please check!", i);
            result = -RT_ERROR;
            continue;
        }
        i2c_obj[i].ops = hpm_bit_ops_default;
        i2c_obj[i].ops.data = (void*)&soft_i2c_configs[i];
        i2c_obj[i].i2c_bus.priv = &i2c_obj[i].ops;
        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c_bus, soft_i2c_configs[i].bus_name);
        RT_ASSERT(result == RT_EOK);
        hpm_i2c_bus_unlock(&soft_i2c_configs[i]);
        LOG_D("software simulation %s init done, pin scl: %s, pin sda %s",
        soft_i2c_configs[i].bus_name,
        soft_i2c_configs[i].scl_pin_name,
        soft_i2c_configs[i].sda_pin_name);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_software_i2c_init);

#endif /* BSP_USING_SOFT_I2C */
