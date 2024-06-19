/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-05-29     QT-one       first version
 */
#include <rtdbg.h>
#include "drv_soft_i2c.h"

#ifdef RT_USING_I2C
#if !defined(BSP_USING_I2C0_SW) && !defined(BSP_USING_I2C1_SW) && !defined(BSP_USING_I2C2_SW)
    #error "Please define at least one BSP_USING_I2Cx_SW"
    /* this driver can be disabled at menuconfig RT-Thread Components Device Drivers */
#endif

/* ht32 software i2c config class */
struct ht32_soft_i2c_config
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *bus_name;
};
/* ht32 software i2c dirver class */
struct ht32_soft_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c_bus;
};

static rt_uint8_t scl_rw_flag = 0;
static rt_uint8_t sda_rw_flag = 0;

static const struct ht32_soft_i2c_config soft_i2c_config[] =
{
#ifdef BSP_USING_I2C0_SW
    {
        .scl        = BSP_I2C0_SLC_PIN,
        .sda        = BSP_I2C0_SDA_PIN,
        .bus_name   = BSP_USING_I2C0_SW_NAME,
    },
#endif
#ifdef BSP_USING_I2C1_SW
    {
        .scl        = BSP_I2C1_SLC_PIN,
        .sda        = BSP_I2C1_SDA_PIN,
        .bus_name   = BSP_USING_I2C1_SW_NAME,
    },
#endif
#ifdef BSP_USING_I2C2_SW
    {
        .scl        = BSP_I2C2_SLC_PIN,
        .sda        = BSP_I2C2_SDA_PIN,
        .bus_name   = BSP_USING_I2C2_SW_NAME,
    },
#endif
};

static struct ht32_soft_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/* this function initializes the software i2c pin */
static void ht32_soft_i2c_gpio_init(struct ht32_soft_i2c *i2c)
{
    struct ht32_soft_i2c_config* cfg = (struct ht32_soft_i2c_config*)i2c->ops.data;

    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}
/* this function sets the sda pin */
void ht32_set_sda(void *data, rt_int32_t state)
{
    struct ht32_soft_i2c_config* cfg = (struct ht32_soft_i2c_config*)data;
    if(sda_rw_flag != 0)
    {
        sda_rw_flag = 0;
        rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);
    }
    if (state)
    {
        rt_pin_write(cfg->sda, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->sda, PIN_LOW);
    }
}
/* this function sets the scl pin */
void ht32_set_scl(void *data, rt_int32_t state)
{
    struct ht32_soft_i2c_config* cfg = (struct ht32_soft_i2c_config*)data;
    if(scl_rw_flag != 0)
    {
        scl_rw_flag = 0;
        rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    }
    if (state)
    {
        rt_pin_write(cfg->scl, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->scl, PIN_LOW);
    }
}
/* this function gets the sda pin state */
rt_int32_t ht32_get_sda(void *data)
{
    struct ht32_soft_i2c_config* cfg = (struct ht32_soft_i2c_config*)data;

    if(sda_rw_flag == 0)
    {
        sda_rw_flag = 1;
        rt_pin_mode(cfg->sda, PIN_MODE_INPUT);
    }
    return rt_pin_read(cfg->sda);
}
/* this function gets the scl pin state */
rt_int32_t ht32_get_scl(void *data)
{
    struct ht32_soft_i2c_config* cfg = (struct ht32_soft_i2c_config*)data;
    if(scl_rw_flag == 0)
    {
        scl_rw_flag = 1;
        rt_pin_mode(cfg->scl, PIN_MODE_INPUT);
    }
    return rt_pin_read(cfg->scl);
}

void ht32_udelay(rt_uint32_t us)
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

static const struct rt_i2c_bit_ops ht32_bit_ops_default =
{
    .data     = RT_NULL,
    .set_sda  = ht32_set_sda,
    .set_scl  = ht32_set_scl,
    .get_sda  = ht32_get_sda,
    .get_scl  = ht32_get_scl,
    .udelay   = ht32_udelay,
    .delay_us = 1,
    .timeout  = 100
};

/* if i2c is locked, this function will unlock it */
static rt_err_t ht32_soft_i2c_bus_unlock(const struct ht32_soft_i2c_config *cfg)
{
    rt_int32_t i = 0;
    rt_pin_mode(cfg->sda, PIN_MODE_INPUT_PULLUP);
    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        while (i++ < 9)
        {
            rt_pin_write(cfg->scl, PIN_HIGH);
            ht32_udelay(100);
            rt_pin_write(cfg->scl, PIN_LOW);
            ht32_udelay(100);
        }
    }
    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        return -RT_ERROR;
    }
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);
    return RT_EOK;
}

/* i2c initialization function */
int rt_sw_i2c_init(void)
{
    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct ht32_soft_i2c);
    rt_err_t result;

    for (int i = 0; i < obj_num; i++)
    {
        i2c_obj[i].ops = ht32_bit_ops_default;
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c_bus.priv = &i2c_obj[i].ops;
        ht32_soft_i2c_gpio_init(&i2c_obj[i]);

        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c_bus, soft_i2c_config[i].bus_name);

        RT_ASSERT(result == RT_EOK);
        ht32_soft_i2c_bus_unlock(&soft_i2c_config[i]);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
        soft_i2c_config[i].bus_name,
        soft_i2c_config[i].scl,
        soft_i2c_config[i].sda);
    }
    return result;
}

INIT_BOARD_EXPORT(rt_sw_i2c_init);


#endif /* RT_USING_I2C */
