/*
 * File      : drv_iic.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-06-05     tanek        first implementation.
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "drv_iic.h"

//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(...)   rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)   
#endif

/*user can change this*/
#define I2CBUS_NAME  "i2c2"

/*user should change this to adapt specific board*/
#define I2C_SCL_PIN                 GPIO_PIN_6
#define I2C_SCL_PORT                GPIOD
#define I2C_SCL_PORT_CLK_ENABLE()   __HAL_RCC_GPIOD_CLK_ENABLE()
#define I2C_SDA_PIN                 GPIO_PIN_7
#define I2C_SDA_PORT                GPIOD
#define I2C_SDL_PORT_CLK_ENABLE()   __HAL_RCC_GPIOD_CLK_ENABLE()


static void stm32f4_i2c_gpio_init()
{
	GPIO_InitTypeDef GPIO_Initure;

	I2C_SCL_PORT_CLK_ENABLE();
    I2C_SDL_PORT_CLK_ENABLE(); 
    
	GPIO_Initure.Pin = I2C_SCL_PIN;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_Initure.Pull = GPIO_PULLUP;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(I2C_SCL_PORT, &GPIO_Initure);
    
    GPIO_Initure.Pin = I2C_SDA_PIN;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_Initure.Pull = GPIO_PULLUP;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(I2C_SDA_PORT, &GPIO_Initure);
    
    HAL_GPIO_WritePin(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_PIN_SET);
}

static void stm32f4_set_sda(void *data, rt_int32_t state)
{
	//HAL_GPIO_WritePin(I2C_SDA_PORT, I2C_SDA_PIN, (GPIO_PinState)state);
  if(state)
  {
    I2C_SDA_PORT->BSRR = I2C_SDA_PIN;
  }
  else
  {
    I2C_SDA_PORT->BSRR = (uint32_t)I2C_SDA_PIN << 16U;
  }
}

static void stm32f4_set_scl(void *data, rt_int32_t state)
{
	//HAL_GPIO_WritePin(I2C_SCL_PORT, I2C_SCL_PIN, (GPIO_PinState)state);
  if(state)
  {
    I2C_SCL_PORT->BSRR = I2C_SCL_PIN;
  }
  else
  {
    I2C_SCL_PORT->BSRR = (uint32_t)I2C_SCL_PIN << 16U;
  }
}

static rt_int32_t  stm32f4_get_sda(void *data)
{
	//return (rt_int32_t)HAL_GPIO_ReadPin(I2C_SDA_PORT, I2C_SDA_PIN);
  if((I2C_SDA_PORT->IDR & I2C_SDA_PIN))
  {
    return 1;
  }
  else
  {
    return 0;
  }
  
}

static rt_int32_t  stm32f4_get_scl(void *data)
{
	//return (rt_int32_t)HAL_GPIO_ReadPin(I2C_SCL_PORT, I2C_SCL_PIN);
  if((I2C_SCL_PORT->IDR & I2C_SCL_PIN))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

static void stm32f4_udelay(rt_uint32_t us)
{
    rt_uint32_t delta;

    us = us * (SysTick->LOAD/(1000000/RT_TICK_PER_SECOND));
    delta = SysTick->VAL;
    while (delta - SysTick->VAL< us);
}

static const struct rt_i2c_bit_ops stm32f4_bit_ops = {
	RT_NULL,
	stm32f4_set_sda,
	stm32f4_set_scl,
	stm32f4_get_sda,
	stm32f4_get_scl,

	stm32f4_udelay,

	1,
	100
};

int hw_i2c_init(void)
{
	static struct rt_i2c_bus_device i2c2_bus;
       
	stm32f4_i2c_gpio_init();
  
	rt_memset((void *)&i2c2_bus, 0, sizeof(struct rt_i2c_bus_device));

	i2c2_bus.priv = (void *)&stm32f4_bit_ops;

	rt_i2c_bit_add_bus(&i2c2_bus, I2CBUS_NAME);

	return RT_EOK;
}
INIT_BOARD_EXPORT(hw_i2c_init);
/* end of i2c driver */