/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
#define DEBUG_PRINTF(...)   rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)   
#endif

static void stm32f4_i2c_gpio_init()
{
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
    
	GPIO_Initure.Pin = GPIO_PIN_8;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_Initure.Pull = GPIO_PULLUP;
	GPIO_Initure.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOA, &GPIO_Initure);
	
	GPIO_Initure.Pin = GPIO_PIN_9;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_Initure.Pull = GPIO_PULLUP;
	GPIO_Initure.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOC, &GPIO_Initure);
    
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
}

static void stm32f4_set_sda(void *data, rt_int32_t state)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, (GPIO_PinState)state);
}

static void stm32f4_set_scl(void *data, rt_int32_t state)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, (GPIO_PinState)state);
}

static rt_int32_t  stm32f4_get_sda(void *data)
{
	return (rt_int32_t)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9);
}

static rt_int32_t  stm32f4_get_scl(void *data)
{
	return (rt_int32_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);
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

	5,
	100
};

int stm32f4_i2c_init(void)
{
	struct rt_i2c_bus_device *bus;

	bus = rt_malloc(sizeof(struct rt_i2c_bus_device));
	if (bus == RT_NULL)
	{
		rt_kprintf("rt_malloc failed\n");
		return -RT_ENOMEM;
	}

	rt_memset((void *)bus, 0, sizeof(struct rt_i2c_bus_device));

	bus->priv = (void *)&bit_ops;

	stm32f4_i2c_gpio_init();

	rt_i2c_bit_add_bus(bus, "i2c3");

	return RT_EOK;
}
INIT_DEVICE_EXPORT(stm32f4_i2c_init);
