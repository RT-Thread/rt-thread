/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 * 2020-06-16     bigmagic       add gpio irq
 */

#include "drv_gpio.h"

#ifdef BSP_USING_PIN

/*
 * gpio_int[0] for BANK0 (pins 0-27)
 * gpio_int[1] for BANK1 (pins 28-45)
 * gpio_int[2] for BANK2 (pins 46-53)
 */
static struct gpio_irq_def _g_gpio_irq_tbl[GPIO_IRQ_NUM];

uint32_t raspi_get_pin_state(uint32_t fselnum)
{
    uint32_t gpfsel = 0;

    switch (fselnum)
    {
    case 0:
        gpfsel = GPIO_REG_GPFSEL0(GPIO_BASE);
        break;
    case 1:
        gpfsel = GPIO_REG_GPFSEL1(GPIO_BASE);
        break;
    case 2:
        gpfsel = GPIO_REG_GPFSEL2(GPIO_BASE);
        break;
    case 3:
        gpfsel = GPIO_REG_GPFSEL3(GPIO_BASE);
        break;
    case 4:
        gpfsel = GPIO_REG_GPFSEL4(GPIO_BASE);
        break;
    case 5:
        gpfsel = GPIO_REG_GPFSEL5(GPIO_BASE);
        break;
    default:
        break;
    }
    return gpfsel;
}

void raspi_set_pin_state(uint32_t fselnum, uint32_t gpfsel)
{
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

static void gpio_set_pud(GPIO_PIN pin, GPIO_PUPD_FUNC mode)
{
    uint32_t fselnum = pin / 16;
    uint32_t fselrest = pin % 16;
    uint32_t reg_value = 0;

    switch (fselnum)
    {
    case 0:
        reg_value = GPIO_PUP_PDN_CNTRL_REG0(GPIO_BASE);
        GPIO_PUP_PDN_CNTRL_REG0(GPIO_BASE) = (reg_value | (mode << (fselrest*2)));
        break;
    case 1:
        reg_value = GPIO_PUP_PDN_CNTRL_REG1(GPIO_BASE);
        GPIO_PUP_PDN_CNTRL_REG1(GPIO_BASE) = (reg_value | (mode << (fselrest*2)));
        break;

    case 2:
        reg_value = GPIO_PUP_PDN_CNTRL_REG2(GPIO_BASE);
        GPIO_PUP_PDN_CNTRL_REG2(GPIO_BASE) = (reg_value | (mode << (fselrest*2)));
        break;

    case 3:
        reg_value = GPIO_PUP_PDN_CNTRL_REG3(GPIO_BASE);
        GPIO_PUP_PDN_CNTRL_REG3(GPIO_BASE) = (reg_value | (mode << (fselrest*2)));
        break;
    default:
        break;
    }
}

void prev_raspi_pin_mode(GPIO_PIN pin, GPIO_FUNC mode)
{
    uint32_t fselnum = pin / 10;
    uint32_t fselrest = pin % 10;
    uint32_t gpfsel = 0;

    gpfsel = raspi_get_pin_state(fselnum);
    gpfsel &= ~((uint32_t)(0x07 << (fselrest * 3)));
    gpfsel |= (uint32_t)(mode << (fselrest * 3));
    raspi_set_pin_state(fselnum, gpfsel);
}

void prev_raspi_pin_write(GPIO_PIN pin, int pin_value)
{
    uint32_t num = pin / 32;

    if(num == 0)
    {
        if(pin_value == 1)
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
        if(pin_value == 1)
        {
            GPIO_REG_GPSET1(GPIO_BASE) = 1 << (pin % 32);
        }
        else
        {
            GPIO_REG_GPCLR1(GPIO_BASE) = 1 << (pin % 32);
        }
    }
}

static void raspi_pin_mode(struct rt_device *dev, rt_base_t pin, rt_uint8_t mode)
{
    GPIO_FUNC raspi_mode = OUTPUT;

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        raspi_mode = OUTPUT;
        break;
    case PIN_MODE_INPUT:
        raspi_mode = INPUT;
        break;
    case PIN_MODE_INPUT_PULLUP:
        gpio_set_pud(pin, RASPI_PULL_UP);
        raspi_mode = INPUT;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        gpio_set_pud(pin, RASPI_PULL_DOWN);
        raspi_mode = INPUT;
        break;
    case PIN_MODE_OUTPUT_OD:
        raspi_mode = OUTPUT;
        break;
    }
    prev_raspi_pin_mode((GPIO_PIN)pin, raspi_mode);
}

static void raspi_pin_write(struct rt_device *dev, rt_base_t pin, rt_uint8_t value)
{
    prev_raspi_pin_write(pin, value);
}

static rt_ssize_t raspi_pin_read(struct rt_device *device, rt_base_t pin)
{
    uint32_t num = pin / 32;
    rt_ssize_t pin_level = 0;

    if(num == 0)
    {
        if(GPIO_REG_GPLEV0(GPIO_BASE) & (1 << pin))
        {
            pin_level = 1;
        }
        else
        {
            pin_level = 0;
        }

    }
    else
    {
        if(GPIO_REG_GPLEV1(GPIO_BASE) & (1 << pin))
        {
            pin_level = 1;
        }
        else
        {
            pin_level = 0;
        }
    }

    return pin_level;
}

static rt_err_t raspi_pin_attach_irq(struct rt_device *device, rt_base_t pin, rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
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
    rt_uint8_t pin_num = pin / 32;
    rt_uint32_t mask = 1 << shift;

    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        if(pin_num == 0)
        {
            reg_value = GPIO_REG_GPREN0(GPIO_BASE);
            GPIO_REG_GPREN0(GPIO_BASE) = (reg_value & ~ mask) | (mask);
        }
        else
        {
            reg_value = GPIO_REG_GPREN1(GPIO_BASE);
            GPIO_REG_GPREN1(GPIO_BASE) = (reg_value & ~ mask) | (mask);
        }
        break;
    case PIN_IRQ_MODE_FALLING:
        if(pin_num == 0)
        {
            reg_value = GPIO_REG_GPFEN0(GPIO_BASE);
            GPIO_REG_GPFEN0(GPIO_BASE) = (reg_value & ~ mask) | (mask);
        }
        else
        {
            reg_value = GPIO_REG_GPFEN1(GPIO_BASE);
            GPIO_REG_GPFEN1(GPIO_BASE) = (reg_value & ~ mask) | (mask);
        }
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        if(pin_num == 0)
        {
            reg_value = GPIO_REG_GPAREN0(GPIO_BASE);
            GPIO_REG_GPAREN0(GPIO_BASE) = (reg_value & ~ mask) | (mask);
            reg_value = GPIO_REG_GPFEN0(GPIO_BASE);
            GPIO_REG_GPFEN0(GPIO_BASE) = (reg_value & ~ mask) | (mask);
        }
        else
        {
            reg_value = GPIO_REG_GPAREN1(GPIO_BASE);
            GPIO_REG_GPAREN1(GPIO_BASE) = (reg_value & ~ mask) | (mask);
            reg_value = GPIO_REG_GPFEN1(GPIO_BASE);
            GPIO_REG_GPFEN1(GPIO_BASE) = (reg_value & ~ mask) | (mask);
        }
        break;
    case PIN_IRQ_MODE_HIGH_LEVEL:
        if(pin_num == 0)
        {
            reg_value = GPIO_REG_GPHEN0(GPIO_BASE);
            GPIO_REG_GPHEN0(GPIO_BASE) = (reg_value & ~ mask) | (mask);
        }
        else
        {
            reg_value = GPIO_REG_GPHEN1(GPIO_BASE);
            GPIO_REG_GPHEN1(GPIO_BASE) = (reg_value & ~ mask) | ( mask);
        }
        break;
    case PIN_IRQ_MODE_LOW_LEVEL:
        if(pin_num == 0)
        {
            reg_value = GPIO_REG_GPLEN0(GPIO_BASE);
            GPIO_REG_GPLEN0(GPIO_BASE) = (reg_value & ~ mask) | (mask);
        }
        else
        {
            reg_value = GPIO_REG_GPLEN1(GPIO_BASE);
            GPIO_REG_GPLEN1(GPIO_BASE) = (reg_value & ~ mask) | (mask);
        }
        break;
    }
    return RT_EOK;
}

static rt_err_t raspi_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_uint8_t index;
    if (pin <= 27)
        index = 0;
    else if (pin <= 45)
        index = 1;
    else
        index = 2;

    _g_gpio_irq_tbl[index].irq_cb[pin]    = RT_NULL;
    _g_gpio_irq_tbl[index].irq_arg[pin]   = RT_NULL;
    _g_gpio_irq_tbl[index].irq_type[pin]  = RT_NULL;
    _g_gpio_irq_tbl[index].state[pin]     = RT_NULL;

    return RT_EOK;
}

rt_err_t raspi_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    rt_uint8_t index;
    if (pin <= 27)
        index = 0;
    else if (pin <= 45)
        index = 1;
    else
        index = 2;

    if (enabled)
        _g_gpio_irq_tbl[index].state[pin] = 1;
    else
        _g_gpio_irq_tbl[index].state[pin] = 0;

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

static void gpio_irq_handler(int irq, void *param)
{
    struct gpio_irq_def *irq_def = (struct gpio_irq_def *)param;
    rt_uint32_t pin;
    rt_uint32_t value;
    rt_uint32_t tmpvalue;

    if(irq == IRQ_GPIO0)
    {
        /* 0~27 */
        value = GPIO_REG_GPEDS0(GPIO_BASE);
        value &= 0x0fffffff;
        pin = 0;
        GPIO_REG_GPEDS0(GPIO_BASE) = value;
    }
    else if(irq == IRQ_GPIO1)
    {
        /* 28-45 */
        tmpvalue = GPIO_REG_GPEDS0(GPIO_BASE);
        tmpvalue &= (~0x0fffffff);
        GPIO_REG_GPEDS0(GPIO_BASE) = tmpvalue;

        value = GPIO_REG_GPEDS1(GPIO_BASE);
        value &= 0x3fff;
        GPIO_REG_GPEDS1(GPIO_BASE) = value;
        value = (value) | tmpvalue;
        pin = 28;
    }
    else if (irq == IRQ_GPIO2)
    {
        /* 46-53 */
        value = GPIO_REG_GPEDS1(GPIO_BASE);
        value &= (~0x3fff);
        GPIO_REG_GPEDS1(GPIO_BASE) = value;
        pin = 46;
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
#endif

int rt_hw_gpio_init(void)
{
#ifdef BSP_USING_PIN
    rt_device_pin_register("gpio", &ops, RT_NULL);

    //disable all intr
    GPIO_REG_GPEDS0(GPIO_BASE) = 0xffffffff;
    GPIO_REG_GPEDS1(GPIO_BASE) = 0xffffffff;

    GPIO_REG_GPREN0(GPIO_BASE) = 0x0;
    GPIO_REG_GPREN1(GPIO_BASE) = 0x0;

    GPIO_REG_GPFEN0(GPIO_BASE) = 0x0;
    GPIO_REG_GPFEN1(GPIO_BASE) = 0x0;

    GPIO_REG_GPHEN0(GPIO_BASE) = 0x0;
    GPIO_REG_GPHEN1(GPIO_BASE) = 0x0;

    GPIO_REG_GPAREN0(GPIO_BASE) = 0x0;
    GPIO_REG_GPAREN1(GPIO_BASE) = 0x0;

    GPIO_REG_GPAFEN0(GPIO_BASE) = 0x0;
    GPIO_REG_GPAFEN0(GPIO_BASE) = 0x0;

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
