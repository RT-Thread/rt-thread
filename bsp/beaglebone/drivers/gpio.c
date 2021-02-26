/*
 * File      : gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 */


#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <am33xx.h>
#include "gpio.h"

#ifdef RT_USING_PIN

#define reg(base)         *(int*)(base)

#define GPIO_PIN_LOW              (0x0)
#define GPIO_PIN_HIGH             (0x1)

#define GPIO_CLEARDATAOUT         (0x190)
#define GPIO_SETDATAOUT           (0x194)
#define GPIO_DATAIN               (0x138)
#define GPIO_OE                   (0x134)

static rt_base_t GPIO_BASE[] =
{
    AM33XX_GPIO_0_REGS,
    AM33XX_GPIO_1_REGS,
    AM33XX_GPIO_2_REGS,
    AM33XX_GPIO_3_REGS
};

static void am33xx_pin_mode(struct rt_device *device, rt_base_t pin, rt_base_t mode)
{
    RT_ASSERT(pin >= 0 && pin < 128);
    RT_ASSERT(mode != PIN_MODE_INPUT_PULLUP); /* Mode not supported */
    rt_base_t gpiox     = pin >> 5;
    rt_base_t pinNumber = pin & 0x1F;

    if(PIN_MODE_OUTPUT == mode)
    {
        reg(GPIO_BASE[gpiox] + GPIO_OE) &= ~(1 << pinNumber);
    }
    else if(PIN_MODE_INPUT == mode)
    {
        reg(GPIO_BASE[gpiox] + GPIO_OE) |= (1 << pinNumber);
    }
}

static void am33xx_pin_write(struct rt_device *device, rt_base_t pin, rt_base_t value)
{
    RT_ASSERT(pin >= 0 && pin < 128);
    rt_base_t gpiox     = pin >> 5;
    rt_base_t pinNumber = pin & 0x1F;

    if(GPIO_PIN_HIGH == value)
    {
        reg(GPIO_BASE[gpiox] + GPIO_SETDATAOUT) = (1 << pinNumber);
    }
    else /* GPIO_PIN_LOW */
    {
        reg(GPIO_BASE[gpiox] + GPIO_CLEARDATAOUT) = (1 << pinNumber);
    }
}

static int am33xx_pin_read(struct rt_device *device, rt_base_t pin)
{
    RT_ASSERT(pin >= 0 && pin < 128);
    rt_base_t gpiox     = pin >> 5;
    rt_base_t pinNumber = pin & 0x1F;

    return reg(GPIO_BASE[gpiox] + GPIO_DATAIN) & (1 << pinNumber) ? 1 : 0;
}

static struct rt_pin_ops am33xx_pin_ops =
{
    am33xx_pin_mode,
    am33xx_pin_write,
    am33xx_pin_read,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
};

int rt_hw_gpio_init(void)
{
    rt_device_pin_register("gpio", &am33xx_pin_ops , RT_NULL);
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_gpio_init);
#endif
