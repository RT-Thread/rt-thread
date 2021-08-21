/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
 * 2021-01-18     CDT          modify i2c gpio init
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "drv_soft_i2c.h"
#include "board.h"

#if defined RT_USING_I2C

#if !defined(BSP_USING_I2C1) && !defined(BSP_USING_I2C2) && \
    !defined(BSP_USING_I2C3) && !defined(BSP_USING_I2C4) && \
    !defined(BSP_USING_I2C5) && !defined(BSP_USING_I2C6)
#error "Please define at least one BSP_USING_I2Cx"
#endif

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

static const struct hc32_soft_i2c_config soft_i2c_config[] =
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
#ifdef BSP_USING_I2C4
    I2C4_BUS_CONFIG,
#endif
#ifdef BSP_USING_I2C5
    I2C5_BUS_CONFIG,
#endif
#ifdef BSP_USING_I2C6
    I2C6_BUS_CONFIG,
#endif
};

static struct hc32_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * This function initializes the i2c pin.
 *
 * @param Hc32 i2c dirver class.
 */
static void hc32_i2c_gpio_init(struct hc32_i2c *i2c)
{
    struct hc32_soft_i2c_config* cfg = (struct hc32_soft_i2c_config*)i2c->ops.data;

    rt_pin_mode(cfg->scl_pin, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda_pin, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl_pin, PIN_HIGH);
    rt_pin_write(cfg->sda_pin, PIN_HIGH);
}

/**
 * This function sets the sda pin.
 *
 * @param Hc32 config class.
 * @param The sda pin state.
 */
static void hc32_set_sda(void *data, rt_int32_t state)
{
    struct hc32_soft_i2c_config* cfg = (struct hc32_soft_i2c_config*)data;

    if (state)
        rt_pin_write(cfg->sda_pin, PIN_HIGH);
    else
        rt_pin_write(cfg->sda_pin, PIN_LOW);
}

/**
 * This function sets the scl pin.
 *
 * @param Hc32 config class.
 * @param The scl pin state.
 */
static void hc32_set_scl(void *data, rt_int32_t state)
{
    struct hc32_soft_i2c_config* cfg = (struct hc32_soft_i2c_config*)data;

    if (state)
        rt_pin_write(cfg->scl_pin, PIN_HIGH);
    else
        rt_pin_write(cfg->scl_pin, PIN_LOW);
}

/**
 * This function gets the sda pin state.
 *
 * @param The sda pin state.
 */
static rt_int32_t hc32_get_sda(void *data)
{
    struct hc32_soft_i2c_config* cfg = (struct hc32_soft_i2c_config*)data;

    return rt_pin_read(cfg->sda_pin);
}

/**
 * This function gets the scl pin state.
 *
 * @param The scl pin state.
 */
static rt_int32_t hc32_get_scl(void *data)
{
    struct hc32_soft_i2c_config* cfg = (struct hc32_soft_i2c_config*)data;

    return rt_pin_read(cfg->scl_pin);
}

static void hc32_udelay(rt_uint32_t us)
{
    rt_hw_us_delay(us);
}

static const struct rt_i2c_bit_ops hc32_bit_ops =
{
    .data     = RT_NULL,
    .set_sda  = hc32_set_sda,
    .set_scl  = hc32_set_scl,
    .get_sda  = hc32_get_sda,
    .get_scl  = hc32_get_scl,
    .udelay   = hc32_udelay,
    .delay_us = 1,
    .timeout  = 100
};

static rt_err_t hc32_i2c_bus_unlock(const struct hc32_soft_i2c_config *cfg)
{
    rt_uint32_t i = 0;

    if (PIN_LOW == rt_pin_read(cfg->sda_pin))
    {
        while (i++ < 9)
        {
            rt_pin_write(cfg->scl_pin, PIN_HIGH);
            //HC32_udelay(100);
            rt_pin_write(cfg->scl_pin, PIN_LOW);
            //hc32_udelay(100);
        }
    }
    if(PIN_LOW == rt_pin_read(cfg->sda_pin))
        return RT_ERROR;

    return RT_EOK;
}

/* I2C initialization function */
int hc32_hw_i2c_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct hc32_i2c);
    rt_err_t result;

    for (int i = 0; i < obj_num; i++)
    {
        i2c_obj[i].ops = hc32_bit_ops;
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c1_bus.priv = &i2c_obj[i].ops;
        hc32_i2c_gpio_init(&i2c_obj[i]);
        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c1_bus, soft_i2c_config[i].bus_name);
        RT_ASSERT(result == RT_EOK);
        hc32_i2c_bus_unlock(&soft_i2c_config[i]);
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(hc32_hw_i2c_init);

#endif /* RT_USING_I2C */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
