/* SPDX-License-Identifier: Apache-2.0 */
/* Copyright (c) 2006-2018, RT-Thread Development Team
 * Copyright (c) 2020, duhuanpeng<548708880@qq.com>
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-20     Bernard      the first version
 * 2017-10-20      ZYH         add mode open drain and input pull down
 * 2020-06-01     Du Huanpeng  GPIO driver based on <components/drivers/include/drivers/pin.h>
 */
#include <rtthread.h>
#include <drivers/pin.h>
#include <ls2k1000.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN
#define     GPIO_IRQ_NUM                    (64)
static struct gpio_irq_def _g_gpio_irq_tbl[GPIO_IRQ_NUM];

static void loongson_pin_mode(struct rt_device *device, rt_base_t pin, rt_base_t mode)
{
    struct loongson_gpio *gpio;
    rt_uint64_t m;

    gpio = (void *)device->user_data;
    m = (rt_uint64_t)1 << pin;

    switch (mode) {
    case PIN_MODE_OUTPUT:
        gpio->GPIO0_OEN &= ~m;
        break;
    case PIN_MODE_INPUT:
        gpio->GPIO0_OEN |= m;
        break;
    case PIN_MODE_INPUT_PULLUP:
        gpio->GPIO0_OEN |= m;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        gpio->GPIO0_OEN |= m;
        break;
    case PIN_MODE_OUTPUT_OD:
        gpio->GPIO0_OEN &= ~m;
        break;
    default:
        /* error */
        rt_kprintf("error\n");
    }
}

static void loongson_pin_write(struct rt_device *device, rt_base_t pin, rt_base_t value)
{
    struct loongson_gpio *gpio;
    rt_uint64_t m;

    if (pin < 0 || pin >= 60) {
        rt_kprintf("error\n");
        return;
    }

    gpio = (void *)device->user_data;
    m = (rt_uint64_t)1 << pin;

    if (value)
        gpio->GPIO0_O |= m;
    else
        gpio->GPIO0_O &= ~m;
}
static int loongson_pin_read(struct rt_device *device, rt_base_t pin)
{
    struct loongson_gpio *gpio;
    int rc;

    gpio = (void *)device->user_data;
    rt_uint64_t m;

    m  = gpio->GPIO0_I;
    m &= (rt_uint64_t)1 << pin;

    rc = !!m;

    return rc;
}

/* TODO: add GPIO interrupt */
static rt_err_t loongson_pin_attach_irq(struct rt_device *device, rt_int32_t pin, rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    rt_uint8_t index;
    rt_uint64_t m;
    struct loongson_gpio *gpio;

    gpio = (void *)device->user_data;

    if(pin < 4)
    {
        index = pin;
    }
    else if(pin < 32)
    {
        index = 5;
    }
    else
    {
        index = 6;
    }
    
    _g_gpio_irq_tbl[index].irq_cb[pin]    = hdr;
    _g_gpio_irq_tbl[index].irq_arg[pin]   = args;
    _g_gpio_irq_tbl[index].irq_type[pin]  = mode;

    liointc_set_irq_mode(index, mode);
    m = (rt_uint64_t)1 << pin;
    gpio->GPIO0_INTEN |= m;

    return RT_EOK;
}
static rt_err_t loongson_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    struct loongson_gpio *gpio;

    gpio = (void *)device->user_data;

    rt_uint8_t index;
    if(pin < 4)
    {
        index = pin;
    }
    else if(pin < 32)
    {
        index = 5;
    }
    else
    {
        index = 6;
    }
    _g_gpio_irq_tbl[index].irq_cb[pin]    = RT_NULL;
    _g_gpio_irq_tbl[index].irq_arg[pin]   = RT_NULL;
    _g_gpio_irq_tbl[index].irq_type[pin]  = RT_NULL;
    _g_gpio_irq_tbl[index].state[pin]     = RT_NULL;

    return RT_EOK;
}
static rt_err_t loongson_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
    struct loongson_gpio *gpio;

    gpio = (void *)device->user_data;

    rt_uint8_t index;
    if(pin < 4)
    {
        index = pin;
    }
    else if(pin < 32)
    {
        index = 5;
    }
    else
    {
        index = 6;
    }

    if (enabled)
        _g_gpio_irq_tbl[index].state[pin] = 1;
    else
        _g_gpio_irq_tbl[index].state[pin] = 0;
    return RT_EOK;
}

static void gpio_irq_handler(int irq, void *param)
{
    struct gpio_irq_def *irq_def = (struct gpio_irq_def *)param;
    rt_uint32_t pin;
    rt_uint32_t value;
    rt_uint32_t tmpvalue;

    if(irq == LS2K_GPIO0_INT_IRQ)
    {
        pin = 0;
    }
    else if(irq == LS2K_GPIO1_INT_IRQ)
    {
        pin = 1;
    }
    else if(irq == LS2K_GPIO2_INT_IRQ)
    {
        pin = 2;
    }
    else if(irq == LS2K_GPIO3_INT_IRQ)
    {
        pin = 3;
    }
    else if(irq == LS2K_GPIO_INTLO_IRQ)
    {
        pin = 4;
    }
    else
    {
        pin = 32;
    }
    
    while (value)
    {
        if ((value & 0x1) && (irq_def->irq_cb[pin] != RT_NULL))
        {
            if(irq_def->state[pin])
            {
                irq_def->irq_cb[pin](irq_def->irq_arg[pin]);
            }
        }
        pin++;
        value = value >> 1;
    }
}

static struct rt_pin_ops loongson_pin_ops = {
    .pin_mode  = loongson_pin_mode,
    .pin_write = loongson_pin_write,
    .pin_read  = loongson_pin_read,

    /* TODO: add GPIO interrupt */
    .pin_attach_irq = loongson_pin_attach_irq,
    .pin_detach_irq = loongson_pin_detach_irq,
    .pin_irq_enable = loongson_pin_irq_enable,
    .pin_get        = RT_NULL,
};


int loongson_pin_init(void)
{
    int rc;
    static struct loongson_gpio *loongson_gpio_priv;

    loongson_gpio_priv = (void *)GPIO_BASE;
    rc = rt_device_pin_register("pin", &loongson_pin_ops, loongson_gpio_priv);

    //gpio0
    rt_hw_interrupt_install(LS2K_GPIO0_INT_IRQ, gpio_irq_handler, &_g_gpio_irq_tbl[0], "gpio0_irq");
    rt_hw_interrupt_umask(LS2K_GPIO0_INT_IRQ);

    //gpio1
    rt_hw_interrupt_install(LS2K_GPIO1_INT_IRQ, gpio_irq_handler, &_g_gpio_irq_tbl[1], "gpio1_irq");
    rt_hw_interrupt_umask(LS2K_GPIO1_INT_IRQ);

    //gpio2
    rt_hw_interrupt_install(LS2K_GPIO2_INT_IRQ, gpio_irq_handler, &_g_gpio_irq_tbl[2], "gpio2_irq");
    rt_hw_interrupt_umask(LS2K_GPIO2_INT_IRQ);

    //gpio3
    rt_hw_interrupt_install(LS2K_GPIO3_INT_IRQ, gpio_irq_handler, &_g_gpio_irq_tbl[3], "gpio3_irq");
    rt_hw_interrupt_umask(LS2K_GPIO3_INT_IRQ);

    //gpio4~gpio31
    rt_hw_interrupt_install(LS2K_GPIO_INTLO_IRQ, gpio_irq_handler, &_g_gpio_irq_tbl[4], "gpio4_irq");
    rt_hw_interrupt_umask(LS2K_GPIO_INTLO_IRQ);

    //gpio32~gpio63
    rt_hw_interrupt_install(LS2K_GPIO_INTHI_IRQ, gpio_irq_handler, &_g_gpio_irq_tbl[5], "gpio5_irq");
    rt_hw_interrupt_umask(LS2K_GPIO_INTHI_IRQ);

    return rc;
}
INIT_BOARD_EXPORT(loongson_pin_init);

#endif /*RT_USING_PIN */
