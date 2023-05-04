/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/01/5      chushicheng  first version
 *
 */

#include "drv_gpio.h"
#include <stdbool.h>

#ifdef BSP_USING_PIN

#define DBG_TAG              "drv.gpio"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

static struct bflb_device_s *gpio;

static struct rt_pin_irq_hdr pin_irq_hdr_tab[GPIO_MAX];

static void gpio_isr(int irq, void *arg)
{
    rt_base_t i;
    for(i = 0; i < GPIO_MAX; i ++)
    {
        if(pin_irq_hdr_tab[i].pin != -1)
        {
            bool intstatus = bflb_gpio_get_intstatus(gpio, i);
            if (intstatus) {
                bflb_gpio_int_clear(gpio, i);
                if(pin_irq_hdr_tab[i].hdr)
                    pin_irq_hdr_tab[i].hdr(pin_irq_hdr_tab[i].args);
            }
        }
    }

}

static void _pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    if(value)
        bflb_gpio_set(gpio, pin);
    else
        bflb_gpio_reset(gpio, pin);
}

static int _pin_read(rt_device_t dev, rt_base_t pin)
{
    return bflb_gpio_read(gpio, pin);
}

static void _pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    rt_uint32_t cfgset = 0;

    switch(mode)
    {
        case PIN_MODE_OUTPUT:
            cfgset = GPIO_OUTPUT;
            break;

        case PIN_MODE_INPUT:
            cfgset = GPIO_INPUT;
            break;

        case PIN_MODE_INPUT_PULLUP:
            cfgset = GPIO_INPUT | GPIO_PULLUP;
            break;

        case PIN_MODE_INPUT_PULLDOWN:
            cfgset =  GPIO_INPUT | GPIO_PULLDOWN;
            break;

        case PIN_MODE_OUTPUT_OD:
            cfgset = GPIO_OUTPUT | GPIO_FLOAT;
            break;

        default:
            cfgset = GPIO_OUTPUT | GPIO_FLOAT;
            break;
    }

    cfgset |= GPIO_SMT_EN | GPIO_DRV_0;
    bflb_gpio_init(gpio, pin, cfgset);
}

static rt_err_t _pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                rt_uint32_t irq_mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    if(pin_irq_hdr_tab[pin].pin == pin &&
        pin_irq_hdr_tab[pin].hdr == hdr &&
        pin_irq_hdr_tab[pin].mode == irq_mode &&
        pin_irq_hdr_tab[pin].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }

    if(pin_irq_hdr_tab[pin].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }

    pin_irq_hdr_tab[pin].pin = pin;
    pin_irq_hdr_tab[pin].mode = irq_mode;
    pin_irq_hdr_tab[pin].hdr = hdr;
    pin_irq_hdr_tab[pin].args = args;

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t _pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    if(pin_irq_hdr_tab[pin].pin == -1)
    {
        rt_hw_interrupt_enable(level);

        return RT_EOK;
    }

    pin_irq_hdr_tab[pin].pin = -1;
    pin_irq_hdr_tab[pin].mode = 0;
    pin_irq_hdr_tab[pin].hdr = RT_NULL;
    pin_irq_hdr_tab[pin].args = RT_NULL;

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t _pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                rt_uint32_t enabled)
{
    rt_base_t level;
    rt_uint8_t trig_mode = 0;

    if (enabled == PIN_IRQ_ENABLE)
    {
        level = rt_hw_interrupt_disable();

        if(pin_irq_hdr_tab[pin].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }

        switch (pin_irq_hdr_tab[pin].mode)
        {
            case PIN_IRQ_MODE_RISING:
                trig_mode = GPIO_INT_TRIG_MODE_SYNC_RISING_EDGE;
                break;

            case PIN_IRQ_MODE_FALLING:
                trig_mode = GPIO_INT_TRIG_MODE_SYNC_FALLING_EDGE;
                break;

            case PIN_IRQ_MODE_RISING_FALLING:
                trig_mode = GPIO_INT_TRIG_MODE_ASYNC_FALLING_EDGE;
                break;

            case PIN_IRQ_MODE_HIGH_LEVEL:
                trig_mode = GPIO_INT_TRIG_MODE_SYNC_HIGH_LEVEL;
                break;

            case PIN_IRQ_MODE_LOW_LEVEL:
                trig_mode = GPIO_INT_TRIG_MODE_SYNC_LOW_LEVEL;
                break;
        }

        bflb_gpio_int_init(gpio, pin, trig_mode);
        bflb_gpio_int_mask(gpio, pin, false);

        rt_hw_interrupt_enable(level);
    }
    else if(enabled == PIN_IRQ_DISABLE)
    {
        level = rt_hw_interrupt_disable();
        bflb_gpio_int_mask(gpio, pin, true);

        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }
    return RT_EOK;
}

const static struct rt_pin_ops bl_drv_pin_ops =
{
    _pin_mode,
    _pin_write,
    _pin_read,
    _pin_attach_irq,
    _pin_detach_irq,
    _pin_irq_enable,
    NULL,
};

int rt_hw_pin_init(void)
{
    rt_uint8_t i;

    for(i = 0; i < GPIO_MAX; i ++)
    {
        pin_irq_hdr_tab[i].pin = -1;
    }
    gpio = bflb_device_get_by_name("gpio");
    bflb_irq_attach(gpio->irq_num, gpio_isr, gpio);
    bflb_irq_enable(gpio->irq_num);

    return rt_device_pin_register("pin", &bl_drv_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /*BSP_USING_PIN */
