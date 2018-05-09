/*
 * File      : drv_iic.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-06-05     tanek        first implementation.
 */
 
#include "drv_i2c.h"

#include <board.h>
#include <finsh.h>
#include <rtdevice.h>
#include <rthw.h>

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(...)           rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)   
#endif

#define I2C_SCL_PIN                 GPIO_PIN_6
#define I2C_SCL_PORT                GPIOB
#define I2C_SCL_PORT_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C_SDA_PIN                 GPIO_PIN_9
#define I2C_SDA_PORT                GPIOB
#define I2C_SDL_PORT_CLK_ENABLE()   

static struct rt_i2c_bus_device i2c_bus;


static void stm32f4_i2c_gpio_init()
{
	GPIO_InitTypeDef GPIO_Initure;

	I2C_SCL_PORT_CLK_ENABLE();
    I2C_SDL_PORT_CLK_ENABLE();
    
	GPIO_Initure.Pin = I2C_SCL_PIN | I2C_SDA_PIN;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_Initure.Pull = GPIO_NOPULL;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(I2C_SDA_PORT, &GPIO_Initure);
    
    HAL_GPIO_WritePin(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_PIN_SET);
}

static void stm32f4_set_sda(void *data, rt_int32_t state)
{
	HAL_GPIO_WritePin(I2C_SDA_PORT, I2C_SDA_PIN, (GPIO_PinState)state);
}

static void stm32f4_set_scl(void *data, rt_int32_t state)
{
	HAL_GPIO_WritePin(I2C_SCL_PORT, I2C_SCL_PIN, (GPIO_PinState)state);
}

static rt_int32_t  stm32f4_get_sda(void *data)
{
	return (rt_int32_t)HAL_GPIO_ReadPin(I2C_SDA_PORT, I2C_SDA_PIN);
}

static rt_int32_t  stm32f4_get_scl(void *data)
{
	return (rt_int32_t)HAL_GPIO_ReadPin(I2C_SCL_PORT, I2C_SCL_PIN);
}

static void stm32f4_udelay(rt_uint32_t us)
{
	rt_int32_t i;
	for (; us > 0; us--)
	{
		i = 50;
		while (i > 0)
		{
			i--;
		}
	}
}

static const struct rt_i2c_bit_ops bit_ops = {
	RT_NULL,
	stm32f4_set_sda,
	stm32f4_set_scl,
	stm32f4_get_sda,
	stm32f4_get_scl,

	stm32f4_udelay,

	50,
	100
};

int stm32f4_i2c_init(void)
{
	i2c_bus.priv = (void *)&bit_ops;

	stm32f4_i2c_gpio_init();

	rt_i2c_bit_add_bus(&i2c_bus, "i2c0");

	return RT_EOK;
}
INIT_DEVICE_EXPORT(stm32f4_i2c_init);
