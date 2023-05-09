/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-01-28     flybreak       first version
 */

#include "drv_gpio.h"

static void pico_pin_mode(struct rt_device *dev, rt_base_t pin, rt_uint8_t mode)
{
    RT_ASSERT((0 <= pin) && (pin < N_GPIOS));

    gpio_init(pin);
    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        gpio_set_dir(pin, GPIO_OUT);
        break;
    case PIN_MODE_INPUT:
        gpio_set_dir(pin, GPIO_IN);
        break;
    case PIN_MODE_INPUT_PULLUP:
        gpio_pull_up(pin);
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        gpio_pull_down(pin);
        break;
    case PIN_MODE_OUTPUT_OD:
        gpio_disable_pulls(pin);
        break;
    }
}

static void pico_pin_write(struct rt_device *dev, rt_base_t pin, rt_uint8_t value)
{
    RT_ASSERT((0 <= pin) && (pin < N_GPIOS));
    gpio_put(pin, value);
}

static rt_int8_t pico_pin_read(struct rt_device *device, rt_base_t pin)
{
    RT_ASSERT((0 <= pin) && (pin < N_GPIOS));
    return (gpio_get(pin)? PIN_HIGH : PIN_LOW);
}

static const struct rt_pin_ops ops =
{
    pico_pin_mode,
    pico_pin_write,
    pico_pin_read,
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
INIT_DEVICE_EXPORT(rt_hw_gpio_init);
