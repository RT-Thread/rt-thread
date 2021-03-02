/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-22     balanceTWK   first version
 */

#include <board.h>
#include "drv_soft_i2c.h"

#include "wm_regs.h"
#include "wm_gpio.h"
#include "pin_map.h"

#define DBG_SECTION_NAME     "soft_i2c"
#define DBG_COLOR
#define DBG_LEVEL           DBG_LOG
#include <rtdbg.h>

#ifdef BSP_USING_SOFT_I2C

#if !defined(BSP_USING_SOFT_I2C1) && !defined(BSP_USING_SOFT_I2C2) && !defined(BSP_USING_SOFT_I2C3)
#error "Please define at least one BSP_USING_SOFT_I2Cx"
#endif

static const struct w60x_soft_i2c_config soft_i2c_config[] =
{
#ifdef BSP_USING_SOFT_I2C1
    I2C1_BUS_CONFIG,
#endif
#ifdef BSP_USING_SOFT_I2C2
    I2C2_BUS_CONFIG,
#endif
#ifdef BSP_USING_SOFT_I2C3
    I2C3_BUS_CONFIG,
#endif
};

static struct w60x_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/**
 * This function initializes the i2c pin.
 *
 * @param w60x i2c dirver class.
 */
static void w60x_i2c_gpio_init(struct w60x_i2c *i2c)
{
    struct w60x_soft_i2c_config* cfg = (struct w60x_soft_i2c_config*)i2c->ops.data;
    rt_int16_t scl,sda;

    scl = wm_get_pin(cfg->scl);
    sda = wm_get_pin(cfg->sda);

    tls_gpio_cfg((enum tls_io_name)scl, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLHIGH);
    tls_gpio_cfg((enum tls_io_name)sda, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLHIGH);

    tls_gpio_write((enum tls_io_name)scl, 1);
    tls_gpio_write((enum tls_io_name)sda, 1);
}

/**
 * This function sets the sda pin.
 *
 * @param w60x config class.
 * @param The sda pin state.
 */
static void w60x_set_sda(void *data, rt_int32_t state)
{
    struct w60x_soft_i2c_config* cfg = (struct w60x_soft_i2c_config*)data;
    rt_int16_t sda;

    sda = wm_get_pin(cfg->sda);

    if (state)
    {
        tls_gpio_cfg((enum tls_io_name)sda, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_PULLHIGH);
    }
    else
    {
        tls_gpio_cfg((enum tls_io_name)sda, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_FLOATING);
        tls_gpio_write((enum tls_io_name)sda, 0);
    }
}

/**
 * This function sets the scl pin.
 *
 * @param w60x config class.
 * @param The scl pin state.
 */
static void w60x_set_scl(void *data, rt_int32_t state)
{
    struct w60x_soft_i2c_config* cfg = (struct w60x_soft_i2c_config*)data;
    rt_int16_t scl;

    scl = wm_get_pin(cfg->scl);

    if (state)
    {
        tls_gpio_cfg((enum tls_io_name)scl, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_PULLHIGH);
    }
    else
    {
        tls_gpio_cfg((enum tls_io_name)scl, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_FLOATING);
        tls_gpio_write((enum tls_io_name)scl, 0);
    }
}

/**
 * This function gets the sda pin state.
 *
 * @param The sda pin state.
 */
static rt_int32_t w60x_get_sda(void *data)
{
    struct w60x_soft_i2c_config* cfg = (struct w60x_soft_i2c_config*)data;
    rt_int16_t sda;

    sda = wm_get_pin(cfg->sda);

    return tls_gpio_read((enum tls_io_name)sda);
}

/**
 * This function gets the scl pin state.
 *
 * @param The scl pin state.
 */
static rt_int32_t w60x_get_scl(void *data)
{
    struct w60x_soft_i2c_config* cfg = (struct w60x_soft_i2c_config*)data;
    rt_int16_t scl;

    scl = wm_get_pin(cfg->scl);

    return tls_gpio_read((enum tls_io_name)scl);
}


static const struct rt_i2c_bit_ops w60x_bit_ops_default =
{
    .data     = RT_NULL,
    .set_sda  = w60x_set_sda,
    .set_scl  = w60x_set_scl,
    .get_sda  = w60x_get_sda,
    .get_scl  = w60x_get_scl,
    .udelay   = rt_hw_us_delay,
    .delay_us = 1,
    .timeout  = 100
};

/**
 * if i2c is locked, this function will unlock it
 *
 * @param w60x config class
 *
 * @return RT_EOK indicates successful unlock.
 */
static rt_err_t w60x_i2c_bus_unlock(const struct w60x_soft_i2c_config *cfg)
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
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct w60x_i2c);
    rt_err_t result;

    for (int i = 0; i < obj_num; i++)
    {
        i2c_obj[i].ops = w60x_bit_ops_default;
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c2_bus.priv = &i2c_obj[i].ops;
        w60x_i2c_gpio_init(&i2c_obj[i]);
        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c2_bus, soft_i2c_config[i].bus_name);
        RT_ASSERT(result == RT_EOK);
        w60x_i2c_bus_unlock(&soft_i2c_config[i]);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
        soft_i2c_config[i].bus_name, 
        soft_i2c_config[i].scl, 
        soft_i2c_config[i].sda);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_soft_i2c_init);

#endif /* BSP_USING_SOFT_I2C */
