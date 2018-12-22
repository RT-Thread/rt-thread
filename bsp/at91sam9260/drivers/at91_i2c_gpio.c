/*
 * File      : at91_i2c_gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
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
 * Date           Author		Notes
 * 2012-04-25     weety		first version
 */

#include <rtdevice.h>
#include <rthw.h>
#include <at91sam926x.h>


static void at91_i2c_gpio_init()
{
	at91_sys_write(AT91_PMC_PCER, 1 << AT91SAM9260_ID_PIOA); //enable PIOA clock
	at91_sys_write(AT91_PIOA + PIO_PUER, (1 << 23));
	at91_sys_write(AT91_PIOA + PIO_PER, (1 << 23));
	at91_sys_write(AT91_PIOA + PIO_MDER, (1 << 23));
	at91_sys_write(AT91_PIOA + PIO_PUER, (1 << 24));
	at91_sys_write(AT91_PIOA + PIO_PER, (1 << 24));
	at91_sys_write(AT91_PIOA + PIO_MDER, (1 << 24));

	at91_sys_write(AT91_PIOA + PIO_OER, (1 << 23));
	at91_sys_write(AT91_PIOA + PIO_OER, (1 << 24));

	at91_sys_write(AT91_PIOA + PIO_SODR, (1 << 23));
	at91_sys_write(AT91_PIOA + PIO_SODR, (1 << 24));
}

static void at91_set_sda(void *data, rt_int32_t state)
{
	if (state)
	{
		at91_sys_write(AT91_PIOA + PIO_SODR, (1 << 23));
	}
	else
	{
		at91_sys_write(AT91_PIOA + PIO_CODR, (1 << 23));
	}
}

static void at91_set_scl(void *data, rt_int32_t state)
{
	if (state)
	{
		at91_sys_write(AT91_PIOA + PIO_SODR, (1 << 24));
	}
	else
	{
		at91_sys_write(AT91_PIOA + PIO_CODR, (1 << 24));
	}
}

static rt_int32_t  at91_get_sda(void *data)
{
	return at91_sys_read(AT91_PIOA + PIO_PDSR) & (1 << 23);
}

static rt_int32_t  at91_get_scl(void *data)
{
	return at91_sys_read(AT91_PIOA + PIO_PDSR) & (1 << 24);
}

static void at91_udelay (rt_uint32_t us)
{
	rt_int32_t i;
	for (; us > 0; us--)
	{
		i = 50000;
		while(i > 0)
		{
			i--;
		}
	}
}

static const struct rt_i2c_bit_ops bit_ops = {
	RT_NULL,
	at91_set_sda,
	at91_set_scl,
	at91_get_sda,
	at91_get_scl,
	
	at91_udelay,

	5,
	100
};

int at91_i2c_init(void)
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

	at91_i2c_gpio_init();

	rt_i2c_bit_add_bus(bus, "i2c0");

	return 0;
}

INIT_DEVICE_EXPORT(at91_i2c_init);

