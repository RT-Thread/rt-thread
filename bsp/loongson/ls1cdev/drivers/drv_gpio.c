/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-24     勤为本          first version
 * 2018-05-11     zhuangwei    add gpio interrupt ops
 */

#include <rtthread.h>
#include <drivers/dev_pin.h>
#include "ls1c_gpio.h"
#include "ls1c.h"
#include <rthw.h>

#ifdef RT_USING_PIN

void ls1c_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    unsigned int gpio = pin;

    if (PIN_MODE_OUTPUT == mode)
    {
        gpio_init(gpio, gpio_mode_output);
    }
    else
    {
        gpio_init(gpio, gpio_mode_input);
    }

    return ;
}


void ls1c_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    unsigned int gpio = pin;

    if (PIN_LOW == value)
    {
        gpio_set(gpio, gpio_level_low);
    }
    else
    {
        gpio_set(gpio, gpio_level_high);
    }

    return ;
}


rt_ssize_t ls1c_pin_read(struct rt_device *device, rt_base_t pin)
{
    unsigned int gpio = pin;
    rt_ssize_t value = PIN_LOW;

    if (0 == gpio_get(gpio))
    {
        value = PIN_LOW;
    }
    else
    {
        value = PIN_HIGH;
    }

    return value;
}

rt_err_t ls1c_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                             rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    unsigned int gpio = pin;
    char irq_name[10];
    rt_uint32_t type;
    switch (mode)
    {
      case PIN_IRQ_MODE_RISING:
      type=IRQ_TYPE_EDGE_RISING;
      break;
      case PIN_IRQ_MODE_FALLING:
      type=IRQ_TYPE_EDGE_FALLING;
      break;
      case PIN_IRQ_MODE_HIGH_LEVEL:
      type=IRQ_TYPE_LEVEL_HIGH;
      break;
      case PIN_IRQ_MODE_LOW_LEVEL:
      type=IRQ_TYPE_LEVEL_LOW;
      break;
    }
    gpio_set_irq_type(gpio, type);

    rt_sprintf(irq_name, "PIN_%d", gpio);
    rt_hw_interrupt_install(LS1C_GPIO_TO_IRQ(gpio), (rt_isr_handler_t)hdr, args, irq_name);

    return RT_EOK;
}

rt_err_t ls1c_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    return RT_EOK;
}

rt_err_t ls1c_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    unsigned int gpio = pin;

    if (enabled)
        rt_hw_interrupt_umask(LS1C_GPIO_TO_IRQ(gpio));
    else
        rt_hw_interrupt_mask(LS1C_GPIO_TO_IRQ(gpio));
    return RT_EOK;
}


const static struct rt_pin_ops _ls1c_pin_ops =
{
    ls1c_pin_mode,
    ls1c_pin_write,
    ls1c_pin_read,
    ls1c_pin_attach_irq,
    ls1c_pin_detach_irq,
    ls1c_pin_irq_enable,
    RT_NULL,
};


int hw_pin_init(void)
{
    int ret = RT_EOK;

    ret = rt_device_pin_register("pin", &_ls1c_pin_ops, RT_NULL);

    return ret;
}
INIT_BOARD_EXPORT(hw_pin_init);

#endif /*RT_USING_PIN */


