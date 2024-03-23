/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author              Notes
 * 2023-10-25     Raman Gopalan       Initial version
 * 2023-11-06     Raman Gopalan       Abstraction for GPIO driver boilerplate
 * 2023-12-01     Raman Gopalan       Use Microchip's updated drivers for abstraction
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
    uint32_t gpio_flag = GPIO_DIR_INPUT;

    gpio_enable_gpio_pin(pin);
    /* Decide based on required mode */
    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        gpio_flag = GPIO_DIR_OUTPUT;
        break;
    case PIN_MODE_INPUT:
        gpio_flag = GPIO_DIR_INPUT;
        break;
    case PIN_MODE_INPUT_PULLUP:
        gpio_flag = GPIO_PULL_UP;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        gpio_flag = GPIO_PULL_DOWN;
        break;
    case PIN_MODE_OUTPUT_OD:
        gpio_flag = GPIO_OPEN_DRAIN;
        break;
    }
    gpio_configure_pin(pin, gpio_flag);
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

static rt_ssize_t at32uc3_pin_read(struct rt_device *device, rt_base_t pin)
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
