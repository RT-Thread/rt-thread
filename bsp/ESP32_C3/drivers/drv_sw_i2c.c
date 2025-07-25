/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-07     wumingzi     first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#define LOG_TAG     "drv.i2c"
#ifdef RT_USING_I2C
#ifdef BSP_USING_SW_I2C
#include "rthw.h"
#include "rttypes.h"
#include <rtdbg.h>
#include "driver/gpio.h"
#include "drv_sw_i2c.h"

#if defined(BSP_USING_SW_I2C0)
#define SW_I2C0_BUS_CONFIG                               \
    {                                                    \
        .scl = BSP_SW_I2C0_SCL_PIN,                      \
        .sda = BSP_SW_I2C0_SDA_PIN,                      \
        .bus_name = "i2c0",                              \
    }
#endif

static const struct esp32c3_soft_i2c_config soft_i2c_config[] =
{
#if defined(BSP_USING_SW_I2C0)
    SW_I2C0_BUS_CONFIG,
#endif
};

static struct esp32c3_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/**
  * @brief  This function initializes the i2c pin.
  * @param  i2c
  * @retval None
  */
static void esp32c3_i2c_gpio_init(struct esp32c3_i2c *i2c)
{
    struct esp32c3_soft_i2c_config* cfg = (struct esp32c3_soft_i2c_config*)i2c->ops.data;
    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);

    gpio_set_pull_mode(cfg->sda, GPIO_FLOATING);
    gpio_set_pull_mode(cfg->scl, GPIO_FLOATING);

    gpio_set_level(cfg->scl, PIN_HIGH);
    gpio_set_level(cfg->sda, PIN_HIGH);
}

/**
  * @brief  This function sets the sda pin.
  * @param  data, state
  * @retval None
  */
static void esp32c3_set_sda(void *data, rt_int32_t state)
{
    struct esp32c3_soft_i2c_config* cfg = (struct esp32c3_soft_i2c_config*)data;
    /*rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);*/
    if (state)
    {
        gpio_set_level(cfg->sda, PIN_HIGH);
    }
    else
    {
        gpio_set_level(cfg->sda, PIN_LOW);
    }
}

/**
  * @brief  This function sets the scl pin.
  * @param  data, state
  * @retval None
  */
static void esp32c3_set_scl(void *data, rt_int32_t state)
{
    struct esp32c3_soft_i2c_config* cfg = (struct esp32c3_soft_i2c_config*)data;
    if (state)
    {
        gpio_set_level(cfg->scl, PIN_HIGH);
    }
    else
    {
        gpio_set_level(cfg->scl, PIN_LOW);
    }
}

/**
  * @brief  This function gets the sda pin state.
  * @param  data
  * @retval None
  */
static rt_int32_t esp32c3_get_sda(void *data)
{
    struct esp32c3_soft_i2c_config* cfg = (struct esp32c3_soft_i2c_config*)data;
    return gpio_get_level(cfg->sda);
}

/**
  * @brief  This function gets the scl pin state.
  * @param  data
  * @retval None
  */
static rt_int32_t esp32c3_get_scl(void *data)
{
    struct esp32c3_soft_i2c_config* cfg = (struct esp32c3_soft_i2c_config*)data;
    return gpio_get_level(cfg->scl);
}

/**
  * @brief  The time delay function.
  * @param  us
  * @retval None
  */
static void esp32c3_udelay(rt_uint32_t us)
{
    rt_hw_us_delay(us);
}

/*
 * if i2c is locked, this function will unlock it
 *
 * @param esp32 config class
 *
 * @return RT_EOK indicates successful unlock.
 */
/* */
static rt_err_t esp32c3_i2c_bus_unlock(const struct esp32c3_soft_i2c_config *cfg)
{
    rt_int32_t i = 0;

    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        /* 输出9个时钟 解锁IIC死锁  */
        while (i++ < 9)
        {
            gpio_set_level(cfg->scl, PIN_HIGH);
            esp32c3_udelay(100);
            gpio_set_level(cfg->scl, PIN_LOW);
            esp32c3_udelay(100);
        }
    }
    if (PIN_LOW == gpio_get_level(cfg->sda))
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}

static const struct rt_i2c_bit_ops esp32c3_bit_ops_default =
{
    .data     = RT_NULL,
    .set_sda  = esp32c3_set_sda,
    .set_scl  = esp32c3_set_scl,
    .get_sda  = esp32c3_get_sda,
    .get_scl  = esp32c3_get_scl,
    .udelay   = esp32c3_udelay,
    .delay_us = 1,
    .timeout  = 100
};

int rt_sw_i2c_init(void)
{
    /* I2C设备数量 */
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct esp32c3_i2c);
    rt_err_t result;
    /* 循环初始化 */
    for (int i = 0; i < obj_num; i++)
    {
        /* 注册方法 */
        i2c_obj[i].ops = esp32c3_bit_ops_default;
        /* 设备硬件数据 */
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        /* 保存设备方法 */
        i2c_obj[i].i2c_bus.priv = &i2c_obj[i].ops;

        esp32c3_i2c_gpio_init(&i2c_obj[i]);
        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c_bus, soft_i2c_config[i].bus_name);
        RT_ASSERT(result == RT_EOK);

        esp32c3_i2c_bus_unlock(&soft_i2c_config[i]);
        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
                                            soft_i2c_config[i].bus_name,
                                            soft_i2c_config[i].scl,
                                            soft_i2c_config[i].sda);
    }

    return RT_EOK;
}
INIT_APP_EXPORT(rt_sw_i2c_init);

#endif /* BSP_USING_SW_I2C */
#endif /* RT_USING_I2C */