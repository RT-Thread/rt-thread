/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-15     Emuzit            first version
 */
#include <rthw.h>
#include <rtdebug.h>
#include <drivers/pin.h>
#include "ch56x_gpio.h"
#include "isr_sp.h"

struct port_info
{
    uint32_t pin_mark;
    struct gpio_px_regs *regbase;
};

static const struct port_info pin_ports[GPIO_PORTS] =
{
    {GPIO_PA_PIN_MARK, (struct gpio_px_regs *)GPIO_REG_BASE_PA},
    {GPIO_PB_PIN_MARK, (struct gpio_px_regs *)GPIO_REG_BASE_PB},
};

static struct rt_pin_irq_hdr pin_irq_hdr_table[8] =
{
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
};


#if defined(SOC_SERIES_CH569)
static int _gpio_pin_to_ibit(rt_base_t pin)
{
    /* gpio ext interrupt 7-0 : {PB15,PB12,PB11,PB4,PB3,PA4,PA3,PA2}
     * not time critical, use linear search
    */
    switch (pin)
    {
    case GET_PIN(A,  2): return 0;
    case GET_PIN(A,  3): return 1;
    case GET_PIN(A,  4): return 2;
    case GET_PIN(B,  3): return 3;
    case GET_PIN(B,  4): return 4;
    case GET_PIN(B, 11): return 5;
    case GET_PIN(B, 12): return 6;
    case GET_PIN(B, 15): return 7;
    }
    return -1;
}

#else

static int _gpio_pin_to_ibit(rt_base_t pin)
{
    /* gpio ext interrupt 7-0 : {PB10,PB4,PA12,PA11,PA10,PA6,PA4,PA3}
     * not time critical, use linear search
    */
    switch (pin)
    {
    case GET_PIN(A,  3): return 0;
    case GET_PIN(A,  4): return 1;
    case GET_PIN(A,  6): return 2;
    case GET_PIN(A, 10): return 3;
    case GET_PIN(A, 11): return 4;
    case GET_PIN(A, 12): return 5;
    case GET_PIN(B,  4): return 6;
    case GET_PIN(B, 10): return 7;
    }
    return -1;
}
#endif

static struct gpio_px_regs *_gpio_px_regbase(rt_base_t pin)
{
    /* fixed linear mapping : 32 pins per port, for ports A,B,C,D...
    */
    uint32_t port = (uint32_t)pin >> 5;
    uint32_t bitpos = 1 << (pin & 0x1f);

    if (port < GPIO_PORTS && (pin_ports[port].pin_mark & bitpos))
        return pin_ports[port].regbase;
    else
        return RT_NULL;
}

static void gpio_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    volatile struct gpio_px_regs *px;

    uint32_t port = (uint32_t)pin >> 5;
    uint32_t bitpos = 1 << (pin & 0x1f);

    if (port < GPIO_PORTS && (pin_ports[port].pin_mark & bitpos))
        px = pin_ports[port].regbase;
    else
        return;

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        BITS_CLR(px->PD,  bitpos);
        BITS_SET(px->DIR, bitpos);
        break;
    case PIN_MODE_INPUT:
        BITS_CLR(px->PU,  bitpos);
        BITS_CLR(px->PD,  bitpos);
        BITS_CLR(px->DIR, bitpos);
        break;
    case PIN_MODE_INPUT_PULLUP:
        BITS_SET(px->PU,  bitpos);
        BITS_CLR(px->PD,  bitpos);
        BITS_CLR(px->DIR, bitpos);
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        BITS_CLR(px->PU,  bitpos);
        BITS_SET(px->PD,  bitpos);
        BITS_CLR(px->DIR, bitpos);
        break;
    case PIN_MODE_OUTPUT_OD:
        BITS_SET(px->PD,  bitpos);
        BITS_SET(px->OUT, bitpos);
    }
}

static void gpio_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    volatile struct gpio_px_regs *px;

    uint32_t port = (uint32_t)pin >> 5;
    uint32_t bitpos = 1 << (pin & 0x1f);

    if (port < GPIO_PORTS && (pin_ports[port].pin_mark & bitpos))
        px = pin_ports[port].regbase;
    else
        return;

    if (value == 0)
        BITS_CLR(px->OUT, bitpos);
    else
        BITS_SET(px->OUT, bitpos);
}

static rt_int8_t gpio_pin_read(struct rt_device *device, rt_base_t pin)
{
    volatile struct gpio_px_regs *px;

    uint32_t port = (uint32_t)pin >> 5;
    uint32_t bitpos = 1 << (pin & 0x1f);

    if (port < GPIO_PORTS && (pin_ports[port].pin_mark & bitpos))
        px = pin_ports[port].regbase;
    else
        return PIN_LOW;

    return (px->PIN & bitpos) ? PIN_HIGH : PIN_LOW;
}

static rt_base_t gpio_pin_get(const char *name)
{
    int port, pin, sz, n;

    /* pin name is in the form "PX.nn" (X: A,B,C,D...;  nn: 0~31)
     * fixed linear mapping : 32 pins per port, for ports A,B,C,D...
    */
    sz = rt_strlen(name);
    if ((sz == 4 || sz == 5) && name[0] == 'P' && name[2] == '.')
    {
        port = name[1] - 'A';
        pin  = name[3] - '0';
        if (0 <= port && port < GPIO_PORTS && 0 <= pin && pin <= 9)
        {
            if (sz == 5)
            {
                n = name[4] - '0';
                pin = (0 <= n && n <= 9) ? (pin * 10 + n) : 32;
            }
            if (pin < 32 && (pin_ports[port].pin_mark & (1 << pin)))
            {
                return port * 32 + pin;
            }
        }
    }

    return -1;
}

static rt_err_t gpio_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;

    int ibit;

    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
    case PIN_IRQ_MODE_FALLING:
    case PIN_IRQ_MODE_HIGH_LEVEL:
    case PIN_IRQ_MODE_LOW_LEVEL:
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        /* hardware not supported */
    default:
        return -RT_EINVAL;
    }

    ibit = _gpio_pin_to_ibit(pin);
    if (ibit < 0)
        return -RT_EINVAL;

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_table[ibit].pin  == pin &&
        pin_irq_hdr_table[ibit].mode == mode &&
        pin_irq_hdr_table[ibit].hdr  == hdr &&
        pin_irq_hdr_table[ibit].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }

    if (pin_irq_hdr_table[ibit].pin >= 0)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EFULL;
    }

    pin_irq_hdr_table[ibit].pin  = pin;
    pin_irq_hdr_table[ibit].mode = mode;
    pin_irq_hdr_table[ibit].hdr  = hdr;
    pin_irq_hdr_table[ibit].args = args;

    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t gpio_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;

    int ibit;

    ibit = _gpio_pin_to_ibit(pin);
    if (ibit < 0)
        return -RT_EINVAL;

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_table[ibit].pin < 0)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_table[ibit].pin  = -1;
    pin_irq_hdr_table[ibit].mode =  0;
    pin_irq_hdr_table[ibit].hdr  = RT_NULL;
    pin_irq_hdr_table[ibit].args = RT_NULL;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t gpio_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                    rt_uint8_t enabled)
{
    volatile struct gpio_registers *gpio;

    rt_base_t level, int_enable;

    int ibit, bitpos;

    ibit = _gpio_pin_to_ibit(pin);
    if (ibit < 0)
        return -RT_EINVAL;
    bitpos = (1 << ibit);

    gpio = (struct gpio_registers *)GPIO_REG_BASE;

    if (enabled == PIN_IRQ_ENABLE)
    {
        level = rt_hw_interrupt_disable();
        if (pin_irq_hdr_table[ibit].pin != pin)
        {
            rt_hw_interrupt_enable(level);
            return -RT_EINVAL;
        }

        switch (pin_irq_hdr_table[ibit].mode)
        {
        case PIN_IRQ_MODE_RISING:
            BITS_SET(gpio->INT_MODE.reg,  bitpos);
            BITS_SET(gpio->INT_POLAR.reg, bitpos);
            break;
        case PIN_IRQ_MODE_FALLING:
            BITS_SET(gpio->INT_MODE.reg,  bitpos);
            BITS_CLR(gpio->INT_POLAR.reg, bitpos);
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            BITS_CLR(gpio->INT_MODE.reg,  bitpos);
            BITS_SET(gpio->INT_POLAR.reg, bitpos);
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            BITS_CLR(gpio->INT_MODE.reg,  bitpos);
            BITS_CLR(gpio->INT_POLAR.reg, bitpos);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
        default:
            rt_hw_interrupt_enable(level);
            return -RT_EINVAL;
        }

        /* clear possible pending intr, then enable pin intr */
        int_enable = gpio->INT_ENABLE.reg;
        gpio->INT_FLAG.reg = bitpos;
        gpio->INT_ENABLE.reg = int_enable | bitpos;
        /* enable GPIO_IRQn if this is the first enabled EXTIx */
        if (int_enable == 0)
        {
            rt_hw_interrupt_umask(GPIO_IRQn);
        }
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        level = rt_hw_interrupt_disable();
        int_enable = gpio->INT_ENABLE.reg;
        BITS_CLR(int_enable, bitpos);
        gpio->INT_ENABLE.reg = int_enable;
        /* disable GPIO_IRQn if no EXTIx enabled */
        if (int_enable == 0)
        {
            rt_hw_interrupt_mask(GPIO_IRQn);
        }
        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static const struct rt_pin_ops pin_ops =
{
    .pin_mode = gpio_pin_mode,
    .pin_write = gpio_pin_write,
    .pin_read = gpio_pin_read,
    .pin_attach_irq = gpio_pin_attach_irq,
    .pin_detach_irq = gpio_pin_detach_irq,
    .pin_irq_enable = gpio_pin_irq_enable,
    .pin_get = gpio_pin_get,
};

static int rt_hw_pin_init(void)
{
    return rt_device_pin_register("pin", &pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

void gpio_irq_handler(void) __attribute__((interrupt()));
void gpio_irq_handler(void)
{
    volatile struct gpio_registers *gpio;

    uint8_t iflags;

    int ibit, bitpos;

    isr_sp_enter();
    rt_interrupt_enter();

    gpio = (struct gpio_registers *)GPIO_REG_BASE;
    iflags = gpio->INT_FLAG.reg;
    /* prioritized as pb15 -> pa2 (CH569), or pb10 -> pa3 */
    for (ibit = 7; ibit >= 0; ibit--)
    {
        bitpos = (1 << ibit);
        if (iflags & bitpos)
        {
            if (pin_irq_hdr_table[ibit].hdr)
            {
                pin_irq_hdr_table[ibit].hdr(pin_irq_hdr_table[ibit].args);
            }
            /* clear interrupt */
            gpio->INT_FLAG.reg = bitpos;
        }
    }

    rt_interrupt_leave();
    isr_sp_leave();
}
