/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#include <board.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN

static struct rt_pin_irq_hdr pin_irq_hdr_tab[GPIO_MAX];

static rt_base_t air105_pin_get(const char *name)
{
    rt_base_t pin = 0;
    int hw_port_num, hw_pin_num = 0;
    int i, name_len;

    name_len = rt_strlen(name);

    if ((name_len < 4) || (name_len >= 6))
    {
        return -RT_EINVAL;
    }
    if ((name[0] != 'P') || (name[2] != '.'))
    {
        return -RT_EINVAL;
    }

    if ((name[1] >= 'A') && (name[1] <= 'Z'))
    {
        hw_port_num = (int)(name[1] - 'A');
    }
    else
    {
        return -RT_EINVAL;
    }

    for (i = 3; i < name_len; i++)
    {
        hw_pin_num *= 10;
        hw_pin_num += name[i] - '0';
    }

    pin = (hw_port_num << 4) + hw_pin_num;

    return pin;
}

static void air105_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    if (pin < GPIO_MAX)
    {
        GPIO_Output(pin, value);
    }
}

static rt_int8_t air105_pin_read(rt_device_t dev, rt_base_t pin)
{
    if (pin < GPIO_MAX)
    {
        return GPIO_Input(pin);
    }
    else
    {
        return -1;
    }
}

static void air105_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    if (pin >= GPIO_MAX)
    {
        return;
    }
    switch(mode)
    {
    case PIN_MODE_OUTPUT:
        GPIO_PullConfig(pin, 0, 0);
        GPIO_Config(pin, 0, 0);
        break;
    case PIN_MODE_INPUT:
    case PIN_MODE_INPUT_PULLDOWN:
        GPIO_PullConfig(pin, 0, 0);
        GPIO_Config(pin, 1, 0);
        break;
    case PIN_MODE_INPUT_PULLUP:
        GPIO_PullConfig(pin, 1, 1);
        GPIO_Config(pin, 1, 0);
        break;
    case PIN_MODE_OUTPUT_OD:
        GPIO_ODConfig(pin, 0);
        break;
    }
}

static rt_err_t air105_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;


    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[pin].pin == pin &&
        pin_irq_hdr_tab[pin].hdr == hdr &&
        pin_irq_hdr_tab[pin].mode == mode &&
        pin_irq_hdr_tab[pin].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[pin].pin = pin;
    pin_irq_hdr_tab[pin].hdr = hdr;
    pin_irq_hdr_tab[pin].mode = mode;
    pin_irq_hdr_tab[pin].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t air105_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    pin_irq_hdr_tab[pin].pin = -1;
    pin_irq_hdr_tab[pin].hdr = RT_NULL;
    pin_irq_hdr_tab[pin].mode = 0;
    pin_irq_hdr_tab[pin].args = RT_NULL;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t air105_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t enabled)
{

    rt_base_t level;
    if (pin >= GPIO_MAX)
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {

        level = rt_hw_interrupt_disable();

        if (pin_irq_hdr_tab[pin].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }
        switch (pin_irq_hdr_tab[pin].mode)
        {
        case PIN_IRQ_MODE_RISING:
            GPIO_ExtiConfig(pin, 0, 1, 0);
            break;
        case PIN_IRQ_MODE_FALLING:
            GPIO_ExtiConfig(pin, 0, 0, 1);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            GPIO_ExtiConfig(pin, 0, 1, 1);
            break;
        }
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        level = rt_hw_interrupt_disable();
        GPIO_ExtiConfig(pin, 0, 0, 0);
        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}
const static struct rt_pin_ops _air105_pin_ops =
{
    air105_pin_mode,
    air105_pin_write,
    air105_pin_read,
    air105_pin_attach_irq,
    air105_pin_dettach_irq,
    air105_pin_irq_enable,
    air105_pin_get,
};

static int pin_irq_hdr(void *pData, void *pParam)
{
    rt_uint32_t irqno = (rt_uint32_t)pData;
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
    return 0;
}


int rt_hw_pin_init(void)
{
    GPIO_GlobalInit(pin_irq_hdr);
    return rt_device_pin_register("pin", &_air105_pin_ops, RT_NULL);
}

#endif /* RT_USING_PIN */
