/* SPDX-License-Identifier: Apache-2.0 */
/* Copyright (c) 2006-2018, RT-Thread Development Team
 * Copyright (c) 2020, duhuanpeng<548708880@qq.com>
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-20     Bernard      the first version
 * 2017-10-20      ZYH          add mode open drain and input pull down
 * 2020-06-01     Du Huanpeng   GPIO driver based on <components/drivers/include/drivers/pin.h>
 */


#include <rtthread.h>
#include <drivers/pin.h>
#include <rthw.h>
#include <ls2k1000.h>

struct loongson_gpio {
    rt_uint64_t GPIO0_OEN;
    rt_uint64_t GPIO1_OEN;    /* Reserved */
    rt_uint64_t GPIO0_O;
    rt_uint64_t GPIO1_O;      /* Reserved */
    rt_uint64_t GPIO0_I;
    rt_uint64_t GPIO1_I;      /* Reserved */
    rt_uint64_t GPIO0_INTEN;
    rt_uint64_t GPIO1_INTEN;  /* Reserved */
};

#ifdef RT_USING_PIN

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

    m  = gpio->GPIO1_I;
    m &= (rt_uint64_t)1 << pin;

    rc = !!m;

    return rc;
}

    /* TODO: add GPIO interrupt */
static rt_err_t loongson_pin_attach_irq(struct rt_device *device, rt_int32_t pin, rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    struct loongson_gpio *gpio;

    gpio = (void *)device->user_data;

    return RT_EOK;
}
static rt_err_t loongson_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    struct loongson_gpio *gpio;

    gpio = (void *)device->user_data;

    return RT_EOK;
}
static rt_err_t loongson_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
    struct loongson_gpio *gpio;

    gpio = (void *)device->user_data;

    return RT_EOK;
}


static struct rt_pin_ops loongson_pin_ops = {
    .pin_mode  = loongson_pin_mode,
    .pin_write = loongson_pin_write,
    .pin_read  = loongson_pin_read,

    /* TODO: add GPIO interrupt */
    .pin_attach_irq = loongson_pin_attach_irq,
    .pin_detach_irq = loongson_pin_detach_irq,
    .pin_irq_enable = loongson_pin_irq_enable,
};


int loongson_pin_init(void)
{
    int rc;
    static struct loongson_gpio *loongson_gpio_priv;

    loongson_gpio_priv = (void *)GPIO_BASE;
    rc = rt_device_pin_register("pin", &loongson_pin_ops, loongson_gpio_priv);

    return rc;
}
INIT_BOARD_EXPORT(loongson_pin_init);

#endif /*RT_USING_PIN */
