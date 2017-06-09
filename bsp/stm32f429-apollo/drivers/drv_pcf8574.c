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
 * 2017-06-09     tanek        first implementation.
 */
#include "drv_pcf8574.h"
#include <board.h>
#include <rthw.h>
#include <finsh.h>

//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(...)   rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)   
#endif

#define I2C_BUS_NAME	"i2c0"
#define PCF8574_ADDR 	0x20

static uint8_t rt_pcf8574_read_onebyte(void);
static void rt_pcf8574_write_onebyte(rt_uint8_t value);

static struct rt_i2c_bus_device * i2c_bus;

rt_err_t rt_pcf8574_init(void)
{
	rt_uint8_t buffer[] = { 0xFF };
	rt_off_t pos = PCF8574_ADDR;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();

	i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(I2C_BUS_NAME);
	if (i2c_bus == RT_NULL)
	{
		DEBUG_PRINTF("\ni2c_bus %s for PCF8574 not found!\n", I2C_BUS_NAME);
		return -RT_ENOSYS;
	}

	if (rt_device_open(&i2c_bus->parent, RT_NULL) != RT_EOK)
	{
		DEBUG_PRINTF("\ni2c_bus %s for cs43l22 opened failed!\n", I2C_BUS_NAME);
		return -RT_EEMPTY;
	}

	rt_device_write(&i2c_bus->parent, pos, &buffer, 1);

	return RT_EOK;
}

static uint8_t rt_pcf8574_read_onebyte(void)
{
	rt_uint8_t value;

	rt_device_read(&i2c_bus->parent, PCF8574_ADDR, &value, 1);

	return value;
}


static void rt_pcf8574_write_onebyte(rt_uint8_t value)
{
	rt_device_write(&i2c_bus->parent, PCF8574_ADDR, &value, 1);
}


void rt_pcf8574_write_bit(rt_uint8_t bit, rt_uint8_t state)
{
	rt_uint8_t data;
	data = rt_pcf8574_read_onebyte();

	if (state == 0)
		data &= ~(1 << bit);
	else 
		data |= 1 << bit;

	rt_pcf8574_write_onebyte(data);
}


rt_uint8_t rt_pcf8574_read_bit(rt_uint8_t bit)
{
	rt_uint8_t data;
	data = rt_pcf8574_read_onebyte();

	if (data&(1 << bit))
		return 1;
	else
		return 0;
}

