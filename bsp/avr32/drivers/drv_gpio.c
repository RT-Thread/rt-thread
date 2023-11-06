/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author              Notes
 * 2023-10-25     Raman Gopalan       Initial version
 * 2023-11-06     Raman Gopalan       Abstraction for GPIO driver boilerplate
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "gpio.h"
#include <rtdbg.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN

static void at32uc3_pin_mode(struct rt_device *dev, rt_base_t pin, rt_uint8_t mode)
{
    RT_ASSERT((AVR32_BSP_GPIO_PMIN <= pin) && (pin <= AVR32_BSP_GPIO_PMAX));
    /* Pointer to the register set for this GPIO port */
    volatile avr32_gpio_port_t *gpio_regs = &AVR32_GPIO.port[pin >> 5];

    /* Decide based on required mode */
    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        gpio_regs->oders = 1 << (pin & 0x1F); /* Enable output driver */
        gpio_regs->gpers = 1 << (pin & 0x1F); /* Make GPIO control this pin */
        break;
    case PIN_MODE_INPUT:
        gpio_regs->oderc = 1 << (pin & 0x1F);
        gpio_regs->gpers = 1 << (pin & 0x1F);
        break;
    case PIN_MODE_INPUT_PULLUP:
        gpio_regs->puers = 1 << (pin & 0x1F);
        break;
    case PIN_MODE_INPUT_PULLDOWN:
	LOG_W("Pull-down enable register not defined for this SOC.");
        break;
    case PIN_MODE_OUTPUT_OD:
	LOG_W("The open-drain mode is not synthesized on the current AVR32 products.");
        break;
    }
}

static void at32uc3_pin_write(struct rt_device *dev, rt_base_t pin, rt_uint8_t value)
{
    RT_ASSERT((AVR32_BSP_GPIO_PMIN <= pin) && (pin <= AVR32_BSP_GPIO_PMAX));
    if (value == PIN_HIGH)
    {
        gpio_set_gpio_pin(pin);
    }
    else
    {
        gpio_clr_gpio_pin(pin);
    }
}

static rt_int8_t at32uc3_pin_read(struct rt_device *device, rt_base_t pin)
{
    RT_ASSERT((AVR32_BSP_GPIO_PMIN <= pin) && (pin <= AVR32_BSP_GPIO_PMAX));
    return (gpio_get_pin_value(pin) ? PIN_HIGH : PIN_LOW);
}

static const struct rt_pin_ops ops =
{
    at32uc3_pin_mode,
    at32uc3_pin_write,
    at32uc3_pin_read,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
};

int rt_hw_gpio_init(void)
{
    rt_device_pin_register("gpio", &ops, RT_NULL);

    return 0;
}

#endif /* RT_USING_PIN */
