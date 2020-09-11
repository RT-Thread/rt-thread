/*
 * File      : gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2017-09-16     Haley        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "am_mcu_apollo.h"

#ifdef RT_USING_PIN

#define APLLO2_PIN_NUMBERS    64 //[34, 64]
struct rt_pin_irq_hdr am_pin_irq_hdr_tab[64];

void am_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        am_hal_gpio_pin_config(pin, AM_HAL_GPIO_OUTPUT);
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        am_hal_gpio_pin_config(pin, AM_HAL_GPIO_INPUT);
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        am_hal_gpio_pin_config(pin, AM_HAL_GPIO_INPUT);
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        am_hal_gpio_pin_config(pin, AM_HAL_GPIO_OPENDRAIN);
    }
    else
    {
        /* input setting:default. */
        am_hal_gpio_pin_config(pin, AM_HAL_GPIO_3STATE);
    }
}

void am_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    if (value == PIN_LOW)
    {
        am_hal_gpio_out_bit_clear(pin);
    }
    else if (value == PIN_HIGH)
    {
        am_hal_gpio_out_bit_set(pin);
    }    
}

int am_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value = PIN_LOW;

    if (am_hal_gpio_pin_config_read(pin) == AM_HAL_GPIO_OUTPUT)
    {
        if (am_hal_gpio_out_bit_read(pin) == 0)
        {
            value = PIN_LOW;
        }
        else
        {
            value = PIN_HIGH;
        }
    }
    else
    {
        if (am_hal_gpio_input_bit_read(pin) == 0)
        {
            value = PIN_LOW;
        }
        else
        {
            value = PIN_HIGH;
        }
    }

    return value;
}

rt_err_t am_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    irqindex = pin;

    level = rt_hw_interrupt_disable();
    if(am_pin_irq_hdr_tab[irqindex].pin == pin   &&
       am_pin_irq_hdr_tab[irqindex].hdr == hdr   &&
       am_pin_irq_hdr_tab[irqindex].mode == mode &&
       am_pin_irq_hdr_tab[irqindex].args == args
    )
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if(am_pin_irq_hdr_tab[irqindex].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }
    am_pin_irq_hdr_tab[irqindex].pin = pin;
    am_pin_irq_hdr_tab[irqindex].hdr = hdr;
    am_pin_irq_hdr_tab[irqindex].mode = mode;
    am_pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t am_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    irqindex = pin;

    level = rt_hw_interrupt_disable();
    if(am_pin_irq_hdr_tab[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    am_pin_irq_hdr_tab[irqindex].pin = -1;
    am_pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
    am_pin_irq_hdr_tab[irqindex].mode = 0;
    am_pin_irq_hdr_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t am_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    irqindex = pin;

    if (enabled == PIN_IRQ_ENABLE)
    {
        level = rt_hw_interrupt_disable();

        /* Configure the GPIO/button interrupt polarity */
        if (am_pin_irq_hdr_tab[irqindex].mode == PIN_IRQ_MODE_RISING)
        {
            am_hal_gpio_int_polarity_bit_set(am_pin_irq_hdr_tab[irqindex].pin, AM_HAL_GPIO_RISING);
        }
        else if (am_pin_irq_hdr_tab[irqindex].mode == PIN_IRQ_MODE_FALLING)
        {
            am_hal_gpio_int_polarity_bit_set(am_pin_irq_hdr_tab[irqindex].pin, AM_HAL_GPIO_FALLING);
        }

        /* Clear the GPIO Interrupt (write to clear) */
        am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(am_pin_irq_hdr_tab[irqindex].pin));

        /* Enable the GPIO/button interrupt */
        am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(am_pin_irq_hdr_tab[irqindex].pin));

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        if (am_hal_gpio_int_enable_get() != AM_HAL_GPIO_BIT(am_pin_irq_hdr_tab[irqindex].pin))
        {
            return RT_ENOSYS;
        }

        /* Disable the GPIO/button interrupt */
        am_hal_gpio_int_disable(AM_HAL_GPIO_BIT(am_pin_irq_hdr_tab[irqindex].pin));
    }
    else
    {
        return RT_ENOSYS;
    }

    return RT_EOK;
}

const static struct rt_pin_ops am_pin_ops =
{
    am_pin_mode,
    am_pin_write,
    am_pin_read,
    am_pin_attach_irq,
    am_pin_dettach_irq,
    am_pin_irq_enable,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
    rt_device_pin_register("pin", &am_pin_ops, RT_NULL);

    //rt_device_pin_irq_register("pin", &am_pin_ops, RT_NULL);
    //rt_kprintf("pin_init!\n");

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_pin_init);
#endif

/*@}*/
