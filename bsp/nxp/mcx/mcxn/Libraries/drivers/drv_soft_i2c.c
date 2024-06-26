/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-25     Andeyqi      the first version
 */
#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_SW_I2C

#define LOG_TAG              "drv.i2c"
#include <rtdbg.h>

/* MCXNXXX config class */
struct mcxnxxx_soft_i2c_config
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *bus_name;
};

/* MCXNXXX i2c dirver class */
struct mcxnxxx_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c2_bus;
};

#if defined(BSP_USING_SW_I2C0)
#define SW_I2C0_BUS_CONFIG                               \
    {                                                    \
        .scl = BSP_SW_I2C0_SCL_PIN,                      \
        .sda = BSP_SW_I2C0_SDA_PIN,                      \
        .bus_name = "swi2c0",                            \
    }
#endif

static const struct mcxnxxx_soft_i2c_config soft_i2c_config[] =
{
#if defined(BSP_USING_SW_I2C0)
    SW_I2C0_BUS_CONFIG,
#endif
};

static struct mcxnxxx_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/**
  * @brief  This function initializes the i2c pin.
  * @param  i2c
  * @retval None
  */
static void mcxnxxx_i2c_gpio_init(struct mcxnxxx_i2c *i2c)
{
    struct mcxnxxx_soft_i2c_config* cfg = (struct mcxnxxx_soft_i2c_config*)i2c->ops.data;

    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}

/**
  * @brief  This function sets the sda pin.
  * @param  data, state
  * @retval None
  */
static void mcxnxxx_set_sda(void *data, rt_int32_t state)
{
    struct mcxnxxx_soft_i2c_config* cfg = (struct mcxnxxx_soft_i2c_config*)data;

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
  * @brief  This function sets the scl pin.
  * @param  data, state
  * @retval None
  */
static void mcxnxxx_set_scl(void *data, rt_int32_t state)
{
    struct mcxnxxx_soft_i2c_config* cfg = (struct mcxnxxx_soft_i2c_config*)data;

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
  * @brief  This function gets the sda pin state.
  * @param  data
  * @retval None
  */
static rt_int32_t mcxnxxx_get_sda(void *data)
{
    struct mcxnxxx_soft_i2c_config* cfg = (struct mcxnxxx_soft_i2c_config*)data;

    rt_pin_mode(cfg->sda, PIN_MODE_INPUT);

    return rt_pin_read(cfg->sda);
}


/**
  * @brief  This function gets the scl pin state.
  * @param  data
  * @retval None
  */
static rt_int32_t mcxnxxx_get_scl(void *data)
{
    struct mcxnxxx_soft_i2c_config* cfg = (struct mcxnxxx_soft_i2c_config*)data;

    rt_pin_mode(cfg->scl,PIN_MODE_INPUT);

    return rt_pin_read(cfg->scl);
}

/**
  * @brief  The time delay function.
  * @param  us
  * @retval None
  */
static void mcxnxxx_udelay(rt_uint32_t us)
{
    rt_uint32_t frequency = CLOCK_GetCoreSysClkFreq();

    int i = (frequency/ 4000000 * us);
    while(i)
    {
        i--;
    }
}

static const struct rt_i2c_bit_ops mcxnxxx_bit_ops_default =
{
    .data     = RT_NULL,
    .set_sda  = mcxnxxx_set_sda,
    .set_scl  = mcxnxxx_set_scl,
    .get_sda  = mcxnxxx_get_sda,
    .get_scl  = mcxnxxx_get_scl,
    .udelay   = mcxnxxx_udelay,
    .delay_us = 1,
    .timeout  = 100
};

/**
  * @brief  if i2c is locked, this function will unlock it
  * @param  cfg
  * @retval RT_EOK indicates successful unlock.
  */
static rt_err_t mcxnxxx_i2c_bus_unlock(const struct mcxnxxx_soft_i2c_config *cfg)
{
    rt_int32_t i = 0;

    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        while (i++ < 9)
        {
            rt_pin_write(cfg->scl, PIN_HIGH);
            mcxnxxx_udelay(100);
            rt_pin_write(cfg->scl, PIN_LOW);
            mcxnxxx_udelay(100);
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
int rt_hw_soft_i2c_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct mcxnxxx_i2c);
    rt_err_t result;

    for (int i = 0; i < obj_num; i++)
    {
        i2c_obj[i].ops = mcxnxxx_bit_ops_default;
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c2_bus.priv = &i2c_obj[i].ops;
        mcxnxxx_i2c_gpio_init(&i2c_obj[i]);

        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c2_bus, soft_i2c_config[i].bus_name);

        RT_ASSERT(result == RT_EOK);

        mcxnxxx_i2c_bus_unlock(&soft_i2c_config[i]);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
        soft_i2c_config[i].bus_name,
        soft_i2c_config[i].scl,
        soft_i2c_config[i].sda);
    }

    return RT_EOK;
}
INIT_APP_EXPORT(rt_hw_soft_i2c_init);

#endif /* RT_USING_I2C */
