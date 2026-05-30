/*
 * Copyright (c) 2021-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-03     supperthomas first version
 * 2024-12-08     wumingzi     support open drain mode for soft i2c
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "driver/gpio.h"

#ifdef RT_USING_PIN

static void mcu_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    gpio_set_level(pin, value);
    /*TODO:set gpio out put mode */
}

static rt_ssize_t mcu_pin_read(rt_device_t dev, rt_base_t pin)
{
    rt_ssize_t value;
    value = gpio_get_level(pin);
    return value;
}

static void mcu_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << pin);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    switch  (mode)
    {
        case PIN_MODE_INPUT:
            gpio_set_direction(pin, GPIO_MODE_INPUT);
        case PIN_MODE_OUTPUT:
            gpio_set_direction(pin, GPIO_MODE_OUTPUT);
        case PIN_MODE_OUTPUT_OD:
            gpio_set_direction(pin, GPIO_MODE_INPUT_OUTPUT_OD);
    }
    /*TODO:set gpio out put mode */
}


static rt_err_t mcu_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                   rt_uint8_t irq_mode, void (*hdr)(void *args), void *args)
{

    /*TODO: start irq handle */
    return -RT_ENOSYS;
}

static rt_err_t mcu_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    /*TODO:disable gpio irq handle */
    return RT_EOK;
}

static rt_err_t mcu_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                   rt_uint8_t enabled)
{
    /*TODO:start irq handle */
    return RT_EOK;
}

const static struct rt_pin_ops _mcu_pin_ops =
{
    mcu_pin_mode,
    mcu_pin_write,
    mcu_pin_read,
    mcu_pin_attach_irq,
    mcu_pin_detach_irq,
    mcu_pin_irq_enable,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
    /*TODO: INIT THE GPIO CLOCK AND OTHER */
    return rt_device_pin_register("pin", &_mcu_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* RT_USING_PIN */