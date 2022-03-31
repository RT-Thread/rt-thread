/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-13     AisinoChip   first implementation.
 */

#include <board.h>

#ifdef RT_USING_I2C_BITOPS

#include <rtdevice.h>
#include <drivers/pin.h>

#define I2C_BUS_NAME  "i2cs"

/* user should change this to adapt specific board */
#define I2C_SCL_PIN          GPIO_PIN_6
#define I2C_SCL_PORT         GPIOD
#define I2C_SDA_PIN          GPIO_PIN_7
#define I2C_SDA_PORT         GPIOD

struct acm32_i2c_bit_data
{
    struct
    {
        enum_GPIOx_t port;
        rt_uint32_t  pin;
    } scl, sda;
};

static void _set_sda(void *data, rt_int32_t state)
{
    struct acm32_i2c_bit_data* bd = data;

    if (state)
    {
        HAL_GPIO_WritePin(bd->sda.port, bd->sda.pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(bd->sda.port, bd->sda.pin, GPIO_PIN_CLEAR);
    }
}

static void _set_scl(void *data, rt_int32_t state)
{
    struct acm32_i2c_bit_data* bd = data;
    if (state)
    {
        HAL_GPIO_WritePin(bd->scl.port, bd->scl.pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(bd->scl.port, bd->scl.pin, GPIO_PIN_CLEAR);
    }
}

static rt_int32_t _get_sda(void *data)
{
    struct acm32_i2c_bit_data* bd = data;

    return HAL_GPIO_ReadPin(bd->sda.port, bd->sda.pin);
}

static rt_int32_t _get_scl(void *data)
{
    struct acm32_i2c_bit_data* bd = data;

    return HAL_GPIO_ReadPin(bd->scl.port, bd->scl.pin);
}

static void acm32_udelay(rt_uint32_t us)
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

static void drv_i2c_gpio_init(const struct acm32_i2c_bit_data* bd)
{
    GPIO_InitTypeDef GPIO_Handle;

    GPIO_Handle.Pin            = bd->sda.pin;
    GPIO_Handle.Mode           = GPIO_MODE_OUTPUT_OD;
    GPIO_Handle.Pull           = GPIO_PULLUP;
    GPIO_Handle.Alternate      = GPIO_FUNCTION_0;
    HAL_GPIO_Init(bd->sda.port, &GPIO_Handle);

    GPIO_Handle.Pin            = bd->scl.pin;
    GPIO_Handle.Mode           = GPIO_MODE_OUTPUT_OD;
    GPIO_Handle.Pull           = GPIO_PULLUP;
    GPIO_Handle.Alternate      = GPIO_FUNCTION_0;
    HAL_GPIO_Init(bd->scl.port, &GPIO_Handle);

    _set_sda((void*)bd, 1);
    _set_scl((void*)bd, 1);
}

int rt_soft_i2c_init(void)
{
    static struct rt_i2c_bus_device i2c_device;
    static const struct acm32_i2c_bit_data _i2c_bdata =
    {
        /* SCL */
        { I2C_SCL_PORT, I2C_SCL_PIN},
        /* SDA */
        { I2C_SDA_PORT, I2C_SDA_PIN},
    };

    static const struct rt_i2c_bit_ops _i2c_bit_ops =
    {
        (void*)&_i2c_bdata,
        _set_sda,
        _set_scl,
        _get_sda,
        _get_scl,
        acm32_udelay,
        1,
        100
    };

    drv_i2c_gpio_init(&_i2c_bdata);

    i2c_device.priv = (void *)&_i2c_bit_ops;
    rt_i2c_bit_add_bus(&i2c_device, I2C_BUS_NAME);

    return 0;
}
INIT_DEVICE_EXPORT(rt_soft_i2c_init);

#endif /* RT_USING_I2C_BITOPS */

