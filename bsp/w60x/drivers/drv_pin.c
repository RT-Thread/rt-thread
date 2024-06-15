/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-15     flyingcys    1st version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "wm_type_def.h"
#include "wm_io.h"
#include "wm_gpio.h"
#include "pin_map.h"
#include "drv_pin.h"

#ifdef BSP_USING_PIN

static void wm_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    rt_int16_t gpio_pin;
    gpio_pin = wm_get_pin(pin);
    if (gpio_pin < 0)
    {
        return;
    }
    if (mode == PIN_MODE_INPUT)
    {
        tls_gpio_cfg((enum tls_io_name)gpio_pin, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_FLOATING);
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        tls_gpio_cfg((enum tls_io_name)gpio_pin, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_PULLHIGH);
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        tls_gpio_cfg((enum tls_io_name)gpio_pin, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_PULLLOW);
    }
    else if (mode == PIN_MODE_OUTPUT)
    {
        tls_gpio_cfg((enum tls_io_name)gpio_pin, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLHIGH);
    }
    return;
}

static void wm_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    rt_int16_t gpio_pin;
    gpio_pin = wm_get_pin(pin);
    if (gpio_pin < 0)
    {
        return;
    }
    tls_gpio_write((enum tls_io_name)gpio_pin, value);
    return;
}

static rt_ssize_t wm_pin_read(struct rt_device *device, rt_base_t pin)
{
    rt_int16_t gpio_pin;
    gpio_pin = wm_get_pin(pin);
    if (gpio_pin < 0)
    {
        return PIN_LOW;
    }
    return tls_gpio_read((enum tls_io_name)gpio_pin);
}

static rt_err_t wm_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                  rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_int16_t gpio_pin;
    rt_base_t level;

    gpio_pin = wm_get_pin(pin);
    if (gpio_pin < 0)
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    /*irq mode set*/
    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        tls_gpio_irq_cfg((enum tls_io_name)gpio_pin, WM_GPIO_IRQ_TRIG_RISING_EDGE);
        break;
    case PIN_IRQ_MODE_FALLING:
        tls_gpio_irq_cfg((enum tls_io_name)gpio_pin, WM_GPIO_IRQ_TRIG_FALLING_EDGE);
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        tls_gpio_irq_cfg((enum tls_io_name)gpio_pin, WM_GPIO_IRQ_TRIG_DOUBLE_EDGE);
        break;
    case PIN_IRQ_MODE_HIGH_LEVEL:
        tls_gpio_irq_cfg((enum tls_io_name)gpio_pin, WM_GPIO_IRQ_TRIG_HIGH_LEVEL);
        break;
    case PIN_IRQ_MODE_LOW_LEVEL:
        tls_gpio_irq_cfg((enum tls_io_name)gpio_pin, WM_GPIO_IRQ_TRIG_LOW_LEVEL);
        break;
    default:
        rt_hw_interrupt_enable(level);
        return -RT_ENOSYS;
    }

    tls_gpio_isr_register((enum tls_io_name)gpio_pin, hdr, args);
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t wm_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    return RT_EOK;
}

static rt_err_t wm_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    rt_int16_t gpio_pin;
    rt_base_t level;

    gpio_pin = wm_get_pin(pin);
    if (gpio_pin < 0)
    {
        return -RT_ENOSYS;
    }
    level = rt_hw_interrupt_disable();
    if (enabled == PIN_IRQ_ENABLE)
    {
        tls_clr_gpio_irq_status((enum tls_io_name)gpio_pin);
        tls_gpio_irq_enable((enum tls_io_name)gpio_pin);
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        tls_gpio_irq_disable((enum tls_io_name)gpio_pin);
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    else
    {
        rt_hw_interrupt_enable(level);
        return -RT_ENOSYS;
    }
}

struct rt_pin_ops _wm_pin_ops =
{
    wm_pin_mode,
    wm_pin_write,
    wm_pin_read,
    wm_pin_attach_irq,
    wm_pin_detach_irq,
    wm_pin_irq_enable,
    RT_NULL,
};

int wm_hw_pin_init(void)
{
    int ret = rt_device_pin_register("pin", &_wm_pin_ops, RT_NULL);
    return ret;
}
INIT_BOARD_EXPORT(wm_hw_pin_init);

void WM_GPIOA_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIOA_IRQHandler();
    rt_interrupt_leave();
}

void WM_GPIOB_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIOB_IRQHandler();
    rt_interrupt_leave();
}
#endif /* BSP_USING_PIN */
