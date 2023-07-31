/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-07-30     sp-cai        first version
 */

#include <rtdevice.h>

#ifdef RT_USING_SOFT_I2C
#if defined(RT_USING_SOFT_I2C5) || defined(RT_USING_SOFT_I2C6)||\
defined(RT_USING_SOFT_I2C7) ||defined(RT_USING_SOFT_I2C8)

#define DBG_ENABLE
#define DBG_TAG                         "I2C_S"
#ifdef RT_USING_SOFT_I2C_DEBUG
    #define DBG_LEVEL                   DBG_LOG
    #define I2C_DEBUG_LOG(log, ...)     log(##__VA_ARGS__)
#else
    #define I2C_DEBUG_LOG(...)
#endif
#include <rtdbg.h>

struct soft_i2c_config
{
    rt_base_t       scl_pin;
    rt_base_t       sda_pin;
    const char      *bus_name;
    rt_uint16_t     timing_delay;   /* scl and sda line delay */
    rt_uint16_t     timing_timeout; /* in tick */
};

const struct soft_i2c_config i2c_cfg[] =
{
    #ifdef RT_USING_SOFT_I2C5
    {
        .scl_pin        = RT_SOFT_I2C5_SCL_PIN,
        .sda_pin        = RT_SOFT_I2C5_SDA_PIN,
        .bus_name       = RT_SOFT_I2C5_BUS_NAME,
        .timing_delay   = RT_SOFT_I2C5_TIMING_DELAY,
        .timing_timeout = RT_SOFT_I2C5_TIMING_TIMEOUT,
    },
    #endif  //RT_USING_SOFT_I2C5
    #ifdef RT_USING_SOFT_I2C6
    {
        .scl_pin        = RT_SOFT_I2C6_SCL_PIN,
        .sda_pin        = RT_SOFT_I2C6_SDA_PIN,
        .bus_name       = RT_SOFT_I2C6_BUS_NAME,
        .timing_delay   = RT_SOFT_I2C6_TIMING_DELAY,
        .timing_timeout = RT_SOFT_I2C6_TIMING_TIMEOUT,
    },
    #endif  //RT_USING_SOFT_I2C6
    #ifdef RT_USING_SOFT_I2C7
    {
        .scl_pin        = RT_SOFT_I2C7_SCL_PIN,
        .sda_pin        = RT_SOFT_I2C7_SDA_PIN,
        .bus_name       = RT_SOFT_I2C7_BUS_NAME,
        .timing_delay   = RT_SOFT_I2C7_TIMING_DELAY,
        .timing_timeout = RT_SOFT_I2C7_TIMING_TIMEOUT,
    },
    #endif  //RT_USING_SOFT_I2C7
    #ifdef RT_USING_SOFT_I2C8
    {
        .scl_pin        = RT_SOFT_I2C8_SCL_PIN,
        .sda_pin        = RT_SOFT_I2C8_SDA_PIN,
        .bus_name       = RT_SOFT_I2C8_BUS_NAME,
        .timing_delay   = RT_SOFT_I2C8_TIMING_DELAY,
        .timing_timeout = RT_SOFT_I2C8_TIMING_TIMEOUT,
    },
    #endif  //RT_USING_SOFT_I2C8
};


static struct rt_soft_i2c i2c_bus_obj[sizeof(i2c_cfg) / sizeof(i2c_cfg[0])] =
{ 0 };

/**
* This function initializes the i2c pin.
*/
static void pin_init(const struct soft_i2c_config *cfg)
{
    rt_pin_mode(cfg->scl_pin, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda_pin, PIN_MODE_OUTPUT_OD);
    rt_pin_write(cfg->scl_pin, PIN_HIGH);
    rt_pin_write(cfg->sda_pin, PIN_HIGH);
}


/**
* This function sets the sda pin.
*/
static void set_sda(const void *cfg, rt_uint8_t value)
{
    rt_pin_write(((const struct soft_i2c_config*)cfg)->sda_pin, value);
}

/**
* This function sets the scl pin.
*/
static void set_scl(const void *cfg, rt_uint8_t value)
{
    rt_pin_write(((const struct soft_i2c_config*)cfg)->scl_pin, value);
}

/**
* This function gets the sda pin state.
*/
static rt_int8_t get_sda(const void *cfg)
{
    return rt_pin_read(((const struct soft_i2c_config*)cfg)->sda_pin);
}

/**
* This function gets the scl pin state.
*/
static rt_int8_t get_scl(const void *cfg)
{
    return rt_pin_read(((const struct soft_i2c_config*)cfg)->scl_pin);
}


static rt_err_t soft_i2c_control(struct rt_i2c_bus_device   *bus,
                                 int                        cmd,
                                 void                       *args)
{
    rt_err_t ret = -RT_ENOSYS;
    struct rt_soft_i2c *obj = (struct rt_soft_i2c *)bus;
    RT_UNUSED(obj);
    RT_ASSERT(bus != RT_NULL);

    I2C_DEBUG_LOG(LOG_D, "%s CMD start: 0x%04X", rt_i2c_bus_name(bus), cmd);
    switch(cmd)
    {
        default:
            LOG_W("%s invalid CMD: 0x%04X", rt_i2c_bus_name(bus), cmd);
            break;
    }
    I2C_DEBUG_LOG(LOG_D, "%s CMD end: 0x%04X", rt_i2c_bus_name(bus), cmd);

    return ret;
}

static const struct rt_soft_i2c_ops soft_i2c_ops =
{
    .set_sda = set_sda,
    .set_scl = set_scl,
    .get_sda = get_sda,
    .get_scl = get_scl,
    .delay = rt_hw_us_delay,
    .control = soft_i2c_control,
};

/* I2C initialization function */
int rt_soft_i2c_init(void)
{
    int err = RT_EOK;
    struct rt_soft_i2c *obj;

    for(int i = 0; i < sizeof(i2c_bus_obj) / sizeof(i2c_bus_obj[0]); i++)
    {
        const struct soft_i2c_config *cfg = &i2c_cfg[i];
        obj = &i2c_bus_obj[i];
        obj->cfg = cfg;

        pin_init(cfg);

        obj->ops = &soft_i2c_ops;
        obj->timing_delay = cfg->timing_delay;
        obj->timing_timeout = cfg->timing_timeout;
        if(rt_soft_i2c_bus_device_register(&obj->i2c_bus, cfg->bus_name) == RT_EOK)
        {
            I2C_DEBUG_LOG(LOG_D, "Software simulation %s init done"
                          ", SCL pin: 0x%02X, SDA pin: 0x%02X"
                          , cfg->bus_name
                          , cfg->scl_pin
                          , cfg->sda_pin
                         );
        }
        else
        {
            err++;
            LOG_E("Software simulation %s init fail"
                  ", SCL pin: 0x%02X, SDA pin: 0x%02X"
                  , cfg->bus_name
                  , cfg->scl_pin
                  , cfg->sda_pin
                 );
        }
    }

    return err;
}
INIT_PREV_EXPORT(rt_soft_i2c_init);

#endif  //RT_USING_SOFT_I2Cx
#endif // RT_USING_SOFT_I2C
