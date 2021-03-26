/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 */

#include "drv_gpio.h"

#ifdef BSP_USING_PIN

static void raspi_pin_mode(struct rt_device *dev, rt_base_t pin, rt_base_t mode)
{
    uint32_t fselnum = pin / 10;
    uint32_t fselrest = pin % 10;

    uint32_t gpfsel = 0;
    gpfsel &= ~((uint32_t)(0x07 << (fselrest * 3)));
    gpfsel |= (uint32_t)(mode << (fselrest * 3));

    switch (fselnum)
    {
    case 0:
        GPIO_REG_GPFSEL0(GPIO_BASE) = gpfsel;
        break;
    case 1:
        GPIO_REG_GPFSEL1(GPIO_BASE) = gpfsel;
        break;
    case 2:
        GPIO_REG_GPFSEL2(GPIO_BASE) = gpfsel;
        break;
    case 3:
        GPIO_REG_GPFSEL3(GPIO_BASE) = gpfsel;
        break;
    case 4:
        GPIO_REG_GPFSEL4(GPIO_BASE) = gpfsel;
        break;
    case 5:
        GPIO_REG_GPFSEL5(GPIO_BASE) = gpfsel;
        break;
    default:
        break;
    }
}

static void raspi_pin_write(struct rt_device *dev, rt_base_t pin, rt_base_t value)
{
    uint32_t num = pin / 32;

    if(num == 0)
    {
        if(value == 0)
        {
            GPIO_REG_GPSET0(GPIO_BASE) = 1 << (pin % 32);
        }
        else
        {
            GPIO_REG_GPCLR0(GPIO_BASE) = 1 << (pin % 32);
        }
    }
    else
    {
        if(value == 0)
        {
            GPIO_REG_GPSET1(GPIO_BASE) = 1 << (pin % 32);
        }
        else
        {
            GPIO_REG_GPCLR1(GPIO_BASE) = 1 << (pin % 32);
        }

    }
}

static int raspi_pin_read(struct rt_device *device, rt_base_t pin)
{
    return 0;
}

static rt_err_t raspi_pin_attach_irq(struct rt_device *device, rt_int32_t pin, rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    return RT_EOK;
}

static rt_err_t raspi_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    return RT_EOK;
}

rt_err_t raspi_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
    return RT_EOK;
}

static const struct rt_pin_ops ops =
{
    raspi_pin_mode,
    raspi_pin_write,
    raspi_pin_read,
    raspi_pin_attach_irq,
    raspi_pin_detach_irq,
    raspi_pin_irq_enable,
    RT_NULL,
};
#endif

int rt_hw_gpio_init(void)
{
#ifdef BSP_USING_PIN
    rt_device_pin_register("gpio", &ops, RT_NULL);
#endif

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_gpio_init);
