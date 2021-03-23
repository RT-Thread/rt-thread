/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */
#include "raspi.h"
#include "drv_gpio.h"


#ifdef BSP_USING_PIN
/*
 * gpio_int[0] for BANK0 (pins 0-27)
 * gpio_int[1] for BANK1 (pins 28-45)
 * gpio_int[2] for BANK2 (pins 46-53)
 */
static struct gpio_irq_def _g_gpio_irq_tbl[GPIO_IRQ_NUM];

void gpio_set_pud(rt_uint8_t pin, rt_uint8_t pud)
{
    rt_uint8_t num = pin / 32;
    rt_uint8_t shift = pin % 32;
    BCM283X_GPIO_GPPUD = pud;
    DELAY_MICROS(10);
    BCM283X_GPIO_GPPUDCLK(num) = 1 << shift;
    DELAY_MICROS(10);
    BCM283X_GPIO_GPPUD = BCM283X_GPIO_PUD_OFF;
    BCM283X_GPIO_GPPUDCLK(num) = 0 << shift;
}

static void gpio_ack_irq(int irq, bcm_gpio_pin pin)
{
    rt_uint32_t data;
    data = IRQ_PEND2;
    data &= (0x0 << (irq - 32));
    IRQ_PEND2 = data;

    data = IRQ_DISABLE2;
    data |= (0x1 << (irq - 32));
    IRQ_DISABLE2 = data;
}

void gpio_irq_disable(rt_uint8_t index, bcm_gpio_pin pin)
{
    int irq = 0;
    rt_uint32_t  reg_value;
    rt_uint8_t irq_type;
    irq = IRQ_GPIO0 + index;

    gpio_ack_irq(irq, pin);

    irq_type = _g_gpio_irq_tbl[index].irq_type[pin];
    rt_uint8_t shift = pin % 32;
    rt_uint32_t mask = 1 << shift;

    switch (irq_type)
    {
    case PIN_IRQ_MODE_RISING:
        reg_value = BCM283X_GPIO_GPREN(pin /32);
        BCM283X_GPIO_GPREN(pin /32) = (reg_value & ~ mask) | (PIN_LOW & mask);
        break;
    case PIN_IRQ_MODE_FALLING:
        reg_value = BCM283X_GPIO_GPFEN(pin /32);
        BCM283X_GPIO_GPFEN(pin /32) = (reg_value & ~ mask) | (PIN_LOW & mask);
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        reg_value = BCM283X_GPIO_GPAREN(pin /32);
        BCM283X_GPIO_GPAREN(pin /32) = (reg_value & ~ mask) | (PIN_LOW & mask);
        reg_value = BCM283X_GPIO_GPAFEN(pin /32);
        BCM283X_GPIO_GPAFEN(pin /32) = (reg_value & ~ mask) | (PIN_LOW & mask);
        break;
    case PIN_IRQ_MODE_HIGH_LEVEL:
        reg_value = BCM283X_GPIO_GPHEN(pin /32);
        BCM283X_GPIO_GPHEN(pin /32) = (reg_value & ~ mask) | (PIN_LOW & mask);
        break;
    case PIN_IRQ_MODE_LOW_LEVEL:
        reg_value = BCM283X_GPIO_GPLEN(pin /32);
        BCM283X_GPIO_GPLEN(pin /32) = (reg_value & ~ mask) | (PIN_LOW & mask);
        break;
    }
}

void gpio_irq_enable(rt_uint8_t index, bcm_gpio_pin pin)
{
    rt_uint32_t offset;
    rt_uint32_t data;

    offset = pin;
    if (index == 0)
        offset = IRQ_GPIO0 - 32;
    else if (index == 1)
        offset = IRQ_GPIO1 - 32;
    else
        offset = IRQ_GPIO2 - 32;

    data = IRQ_ENABLE2;
    data |= 0x1 << offset;
    IRQ_ENABLE2 = data;

}

static void raspi_pin_mode(struct rt_device *dev, rt_base_t pin, rt_base_t mode)
{
    RT_ASSERT((BCM_GPIO_PIN_0 <= pin) && (pin < BCM_GPIO_PIN_NULL));
    RT_ASSERT(!(mode & 0x8));

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        GPIO_FSEL(pin, BCM283X_GPIO_FSEL_OUTP);
        break;
    case PIN_MODE_INPUT:
        GPIO_FSEL(pin, BCM283X_GPIO_FSEL_INPT);
        break;
    case PIN_MODE_INPUT_PULLUP:
        gpio_set_pud(pin, BCM283X_GPIO_PUD_UP);
        GPIO_FSEL(pin, BCM283X_GPIO_FSEL_INPT);
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        gpio_set_pud(pin, BCM283X_GPIO_PUD_DOWN);
        GPIO_FSEL(pin, BCM283X_GPIO_FSEL_INPT);
        break;
    case PIN_MODE_OUTPUT_OD:
        gpio_set_pud(pin, BCM283X_GPIO_PUD_OFF);
        GPIO_FSEL(pin, BCM283X_GPIO_FSEL_OUTP);
        break;
    }
}

static void raspi_pin_write(struct rt_device *dev, rt_base_t pin, rt_base_t value)
{
    RT_ASSERT((BCM_GPIO_PIN_0 <= pin) && (pin < BCM_GPIO_PIN_NULL));
    RT_ASSERT(!(value & 0xE));

    if (value)
        BCM283X_GPIO_GPSET(pin / 32) |= (1 << (pin %32));
    else
        BCM283X_GPIO_GPCLR(pin / 32) |= (0 << (pin %32));

}

static int raspi_pin_read(struct rt_device *device, rt_base_t pin)
{
    RT_ASSERT((BCM_GPIO_PIN_0 <= pin) && (pin < BCM_GPIO_PIN_NULL));
    return (BCM2835_GPIO_GPLEV(pin / 32) & (1 << (pin % 32)))? PIN_HIGH : PIN_LOW;
}

static rt_err_t raspi_pin_attach_irq(struct rt_device *device, rt_int32_t pin, rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    RT_ASSERT((BCM_GPIO_PIN_0 <= pin) && (pin < BCM_GPIO_PIN_NULL));

    rt_uint8_t index;
    rt_uint32_t  reg_value;
    if (pin <= 27)
        index = 0;
    else if (pin <= 45)
        index = 1;
    else
        index = 2;
    _g_gpio_irq_tbl[index].irq_cb[pin]    = hdr;
    _g_gpio_irq_tbl[index].irq_arg[pin]   = args;
    _g_gpio_irq_tbl[index].irq_type[pin]  = mode;

    rt_uint8_t shift = pin % 32;
    rt_uint32_t mask = 1 << shift;

    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        reg_value = BCM283X_GPIO_GPREN(pin /32);
        BCM283X_GPIO_GPREN(pin /32) = (reg_value & ~ mask) | (PIN_HIGH & mask);
        break;
    case PIN_IRQ_MODE_FALLING:
        reg_value = BCM283X_GPIO_GPFEN(pin /32);
        BCM283X_GPIO_GPFEN(pin /32) = (reg_value & ~ mask) | (PIN_HIGH & mask);
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        reg_value = BCM283X_GPIO_GPAREN(pin /32);
        BCM283X_GPIO_GPAREN(pin /32) = (reg_value & ~ mask) | (PIN_HIGH & mask);
        reg_value = BCM283X_GPIO_GPAFEN(pin /32);
        BCM283X_GPIO_GPAFEN(pin /32) = (reg_value & ~ mask) | (PIN_HIGH & mask);
        break;
    case PIN_IRQ_MODE_HIGH_LEVEL:
        reg_value = BCM283X_GPIO_GPHEN(pin /32);
        BCM283X_GPIO_GPHEN(pin /32) = (reg_value & ~ mask) | (PIN_HIGH & mask);
        break;
    case PIN_IRQ_MODE_LOW_LEVEL:
        reg_value = BCM283X_GPIO_GPLEN(pin /32);
        BCM283X_GPIO_GPLEN(pin /32) = (reg_value & ~ mask) | (PIN_HIGH & mask);
        break;
    }
    return RT_EOK;
}

static rt_err_t raspi_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    RT_ASSERT((BCM_GPIO_PIN_0 <= pin) && (pin < BCM_GPIO_PIN_NULL));

    rt_uint8_t index;
    if (pin <= 27)
        index = 0;
    else if (pin <= 45)
        index = 1;
    else
        index = 2;

    gpio_irq_disable(index, pin);

    _g_gpio_irq_tbl[index].irq_cb[pin]    = RT_NULL;
    _g_gpio_irq_tbl[index].irq_arg[pin]   = RT_NULL;
    _g_gpio_irq_tbl[index].irq_type[pin]  = RT_NULL;

    return RT_EOK;
}

rt_err_t raspi_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
    RT_ASSERT((BCM_GPIO_PIN_0 <= pin) && (pin < BCM_GPIO_PIN_NULL));

    rt_uint8_t index;
    if (pin <= 27)
        index = 0;
    else if (pin <= 45)
        index = 1;
    else
        index = 2;

    if (enabled)
        gpio_irq_enable(index, pin);
    else
        gpio_irq_disable(index, pin);

    return RT_EOK;
}

static void gpio_irq_handler(int irq, void *param)
{
    struct gpio_irq_def *irq_def = (struct gpio_irq_def *)param;
    rt_uint32_t pin;
    rt_uint32_t value;
    rt_uint32_t tmpvalue;

    if (irq == IRQ_GPIO0)
    {
        /* 0~27 */

        value = BCM283X_GPIO_GPEDS(0);
        value &= 0x0fffffff;
        pin = 0;
        BCM283X_GPIO_GPEDS(0) = 0;
    }
    else if (irq == IRQ_GPIO1)
    {
        /* 28-45 */
        tmpvalue = BCM283X_GPIO_GPEDS(0);
        tmpvalue &= (~0x0fffffff);

        value = BCM283X_GPIO_GPEDS(1);
        value &= 0x3fff;
        value = (value<<4) | tmpvalue;
        pin = 28;
        BCM283X_GPIO_GPEDS(0) = 0;
        BCM283X_GPIO_GPEDS(1) = 0;
    }
    else if (irq == IRQ_GPIO2)
    {
        /* 46-53 */
        value = BCM283X_GPIO_GPEDS(1);
        value &= (~0x3fff);
        value &= 0xff600000;
        pin = 46;
        BCM283X_GPIO_GPEDS(1) = 0;
    }

    while (value)
    {
        if ((value & 0x1) && (irq_def->irq_cb[pin] != RT_NULL))
        {
            irq_def->irq_cb[pin](irq_def->irq_arg[pin]);
            gpio_ack_irq(irq,pin);
        }
        pin++;
        value = value >> 1;
    }
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

    /* install ISR */
    rt_hw_interrupt_install(IRQ_GPIO0, gpio_irq_handler, &_g_gpio_irq_tbl[0], "gpio0_irq");
    rt_hw_interrupt_umask(IRQ_GPIO0);

    rt_hw_interrupt_install(IRQ_GPIO1, gpio_irq_handler, &_g_gpio_irq_tbl[1], "gpio1_irq");
    rt_hw_interrupt_umask(IRQ_GPIO1);

    rt_hw_interrupt_install(IRQ_GPIO2, gpio_irq_handler, &_g_gpio_irq_tbl[2], "gpio2_irq");
    rt_hw_interrupt_umask(IRQ_GPIO2);
#endif

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_gpio_init);
