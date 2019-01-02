/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-06-05     tanek        first implementation.
 * 2018-03-08     ZYH          Porting for stm32f4xx
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_i2c.h"
#include <board.h>
/*user can change this*/
#define I2C_BUS_NAME  "i2c2"
/*user should change this to adapt specific board*/
#define I2C_SCL_PIN                 GPIO_PIN_6
#define I2C_SCL_PORT                GPIOB
#define I2C_SCL_PORT_CLK_ENABLE     __HAL_RCC_GPIOB_CLK_ENABLE
#define I2C_SDA_PIN                 GPIO_PIN_7
#define I2C_SDA_PORT                GPIOB
#define I2C_SDA_PORT_CLK_ENABLE     __HAL_RCC_GPIOB_CLK_ENABLE

static void drv_i2c_gpio_init()
{
    GPIO_InitTypeDef GPIO_Initure;
    I2C_SCL_PORT_CLK_ENABLE();
    I2C_SDA_PORT_CLK_ENABLE();
    GPIO_Initure.Pin = I2C_SCL_PIN;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(I2C_SCL_PORT, &GPIO_Initure);
    GPIO_Initure.Pin = I2C_SDA_PIN;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(I2C_SDA_PORT, &GPIO_Initure);
    HAL_GPIO_WritePin(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_PIN_SET);
}

static void drv_set_sda(void *data, rt_int32_t state)
{
    HAL_GPIO_WritePin(I2C_SDA_PORT, I2C_SDA_PIN, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static void drv_set_scl(void *data, rt_int32_t state)
{
    HAL_GPIO_WritePin(I2C_SCL_PORT, I2C_SCL_PIN, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static rt_int32_t  drv_get_sda(void *data)
{
    return HAL_GPIO_ReadPin(I2C_SDA_PORT, I2C_SDA_PIN) ? 1 : 0;
}

static rt_int32_t  drv_get_scl(void *data)
{
    return HAL_GPIO_ReadPin(I2C_SCL_PORT, I2C_SCL_PIN) ? 1 : 0;
}

static void drv_udelay(rt_uint32_t us)
{
    __IO uint32_t Delay = us * (SystemCoreClock / 8U / 1000000U);
    do 
    {
        __NOP();
    } 
    while (Delay --);
}

static const struct rt_i2c_bit_ops drv_bit_ops =
{
    RT_NULL,
    drv_set_sda,
    drv_set_scl,
    drv_get_sda,
    drv_get_scl,
    drv_udelay,
    1,
    100
};

int drv_i2c_init(void)
{
    static struct rt_i2c_bus_device i2c2_bus;
    drv_i2c_gpio_init();
    rt_memset((void *)&i2c2_bus, 0, sizeof(struct rt_i2c_bus_device));
    i2c2_bus.priv = (void *)&drv_bit_ops;
    rt_i2c_bit_add_bus(&i2c2_bus, I2C_BUS_NAME);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(drv_i2c_init);
/* end of i2c driver */
