/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-20     rcitach      first version
 */

#include <rtdevice.h>

#include "drv_gpio.h"
#include "interrupt.h"


#define S100_GPIO_PORT0_BASE             0x23480000U
#define S100_GPIO_PORT1_BASE             0x23490000U
#define S100_GPIO_PORT2_BASE             0x234A0000U

#define S100_GPIO_PORT0_IRQ              68
#define S100_GPIO_PORT1_IRQ              69
#define S100_GPIO_PORT2_IRQ              70

#define S100_GPIO_PORT_COUNT             3
#define S100_GPIO_CHANNELS_PER_PORT      32

typedef struct
{
    volatile rt_uint32_t swporta_dr;
    volatile rt_uint32_t swporta_ddr;
    volatile rt_uint32_t rsvd0;
    volatile rt_uint32_t swportb_dr;
    volatile rt_uint32_t swportb_ddr;
    volatile rt_uint32_t rsvd1[7];
    volatile rt_uint32_t inten;
    volatile rt_uint32_t intmask;
    volatile rt_uint32_t inttype_level;
    volatile rt_uint32_t int_polarity;
    volatile rt_uint32_t intstatus;
    volatile rt_uint32_t raw_intstatus;
    volatile rt_uint32_t debounce;
    volatile rt_uint32_t porta_eoi;
    volatile rt_uint32_t ext_porta;
    volatile rt_uint32_t ext_portb;
    volatile rt_uint32_t rsvd2[2];
    volatile rt_uint32_t ls_sync;
    volatile rt_uint32_t id_code;
    volatile rt_uint32_t int_bothedge;
    volatile rt_uint32_t ver_id_code;
} s100_gpio_reg_t;

static s100_gpio_reg_t *const s100_gpio_ports[S100_GPIO_PORT_COUNT] =
{
    (s100_gpio_reg_t *)S100_GPIO_PORT0_BASE,
    (s100_gpio_reg_t *)S100_GPIO_PORT1_BASE,
    (s100_gpio_reg_t *)S100_GPIO_PORT2_BASE,
};

static const int s100_gpio_port_irqs[S100_GPIO_PORT_COUNT] =
{
    S100_GPIO_PORT0_IRQ,
    S100_GPIO_PORT1_IRQ,
    S100_GPIO_PORT2_IRQ,
};

static struct rt_pin_irq_hdr s100_pin_irq_hdr[S100_GPIO_PIN_COUNT];

static rt_err_t s100_pin_to_gpio(s100_pin_t pin,
                                 rt_uint8_t *port_index,
                                 rt_uint8_t *bit_index)
{
    rt_uint8_t gpio_pin;

    if (!s100_pin_is_valid(pin))
    {
        return -RT_EINVAL;
    }

    /* The MCU GPIO numbering skips pin 79, so pins >= 80 shift by one. */
    gpio_pin = (pin >= 80U) ? (pin - 1U) : pin;
    *port_index = gpio_pin / S100_GPIO_CHANNELS_PER_PORT;
    *bit_index = gpio_pin % S100_GPIO_CHANNELS_PER_PORT;

    if (*port_index >= S100_GPIO_PORT_COUNT)
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t s100_gpio_to_pin(rt_uint8_t port_index,
                                 rt_uint8_t bit_index,
                                 s100_pin_t *pin)
{
    rt_uint8_t gpio_pin;

    if (port_index >= S100_GPIO_PORT_COUNT || bit_index >= S100_GPIO_CHANNELS_PER_PORT)
    {
        return -RT_EINVAL;
    }

    gpio_pin = (port_index * S100_GPIO_CHANNELS_PER_PORT) + bit_index;
    *pin = (gpio_pin >= 79U) ? (gpio_pin + 1U) : gpio_pin;

    if (!s100_pin_is_valid(*pin))
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t s100_gpio_config_irq(rt_base_t pin, rt_uint8_t mode)
{
    rt_uint8_t port_index;
    rt_uint8_t bit_index;
    rt_uint32_t bit;
    s100_gpio_reg_t *gpio;
    rt_err_t ret;

    ret = s100_pin_to_gpio((s100_pin_t)pin, &port_index, &bit_index);
    if (ret != RT_EOK)
    {
        return ret;
    }

    gpio = s100_gpio_ports[port_index];
    bit = 1UL << bit_index;

    gpio->inten &= ~bit;
    gpio->intmask |= bit;
    gpio->int_bothedge &= ~bit;

    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        gpio->inttype_level |= bit;
        gpio->int_polarity |= bit;
        break;
    case PIN_IRQ_MODE_FALLING:
        gpio->inttype_level |= bit;
        gpio->int_polarity &= ~bit;
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        gpio->inttype_level |= bit;
        gpio->int_bothedge |= bit;
        break;
    case PIN_IRQ_MODE_HIGH_LEVEL:
        gpio->inttype_level &= ~bit;
        gpio->int_polarity |= bit;
        break;
    case PIN_IRQ_MODE_LOW_LEVEL:
        gpio->inttype_level &= ~bit;
        gpio->int_polarity &= ~bit;
        break;
    default:
        return -RT_EINVAL;
    }

    gpio->porta_eoi = bit;
    return RT_EOK;
}

rt_err_t s100_gpio_set_direction(s100_pin_t pin, s100_pin_direction_t direction)
{
    rt_uint8_t port_index;
    rt_uint8_t bit_index;
    rt_uint32_t bit;
    rt_err_t ret;

    ret = s100_pin_to_gpio(pin, &port_index, &bit_index);
    if (ret != RT_EOK)
    {
        return -RT_EINVAL;
    }

    bit = 1UL << bit_index;
    if (direction == S100_PIN_DIR_OUT)
    {
        s100_gpio_ports[port_index]->swporta_ddr |= bit;
    }
    else
    {
        s100_gpio_ports[port_index]->swporta_ddr &= ~bit;
    }

    return RT_EOK;
}

rt_err_t s100_gpio_write_pin(s100_pin_t pin, s100_pin_level_t level)
{
    rt_uint8_t port_index;
    rt_uint8_t bit_index;
    rt_uint32_t bit;
    rt_err_t ret;

    ret = s100_pin_to_gpio(pin, &port_index, &bit_index);
    if (ret != RT_EOK)
    {
        return -RT_EINVAL;
    }

    bit = 1UL << bit_index;
    if (level == S100_PIN_LEVEL_HIGH)
    {
        s100_gpio_ports[port_index]->swporta_dr |= bit;
    }
    else
    {
        s100_gpio_ports[port_index]->swporta_dr &= ~bit;
    }

    return RT_EOK;
}

rt_err_t s100_gpio_read_pin(s100_pin_t pin, s100_pin_level_t *level)
{
    rt_uint8_t port_index;
    rt_uint8_t bit_index;
    rt_err_t ret;

    if (level == RT_NULL)
    {
        return -RT_EINVAL;
    }

    ret = s100_pin_to_gpio(pin, &port_index, &bit_index);
    if (ret != RT_EOK)
    {
        return -RT_EINVAL;
    }

    *level = (s100_gpio_ports[port_index]->ext_porta & (1UL << bit_index)) ?
        S100_PIN_LEVEL_HIGH : S100_PIN_LEVEL_LOW;

    return RT_EOK;
}

void s100_gpio_write(rt_uint8_t pin, rt_uint8_t value)
{
    (void)s100_pin_set_function(pin, S100_PIN_FUNC_GPIO);
    (void)s100_gpio_set_direction(pin, S100_PIN_DIR_OUT);
    (void)s100_gpio_write_pin(pin, value ? S100_PIN_LEVEL_HIGH : S100_PIN_LEVEL_LOW);
}

rt_uint8_t s100_gpio_read(rt_uint8_t pin)
{
    s100_pin_level_t level = S100_PIN_LEVEL_LOW;

    (void)s100_gpio_read_pin(pin, &level);
    return (level == S100_PIN_LEVEL_HIGH) ? 1U : 0U;
}

static void s100_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    RT_UNUSED(device);

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        (void)s100_pin_set_function((s100_pin_t)pin, S100_PIN_FUNC_GPIO);
        (void)s100_gpio_set_direction((s100_pin_t)pin, S100_PIN_DIR_OUT);
        break;
    case PIN_MODE_INPUT:
        (void)s100_pin_set_function((s100_pin_t)pin, S100_PIN_FUNC_GPIO);
        (void)s100_gpio_set_direction((s100_pin_t)pin, S100_PIN_DIR_IN);
        (void)s100_pin_set_pull((s100_pin_t)pin, S100_PIN_PULL_NONE);
        break;
    case PIN_MODE_INPUT_PULLUP:
        (void)s100_pin_set_function((s100_pin_t)pin, S100_PIN_FUNC_GPIO);
        (void)s100_gpio_set_direction((s100_pin_t)pin, S100_PIN_DIR_IN);
        (void)s100_pin_set_pull((s100_pin_t)pin, S100_PIN_PULL_UP);
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        (void)s100_pin_set_function((s100_pin_t)pin, S100_PIN_FUNC_GPIO);
        (void)s100_gpio_set_direction((s100_pin_t)pin, S100_PIN_DIR_IN);
        (void)s100_pin_set_pull((s100_pin_t)pin, S100_PIN_PULL_DOWN);
        break;
    case PIN_MODE_OUTPUT_OD:
        (void)s100_pin_set_function((s100_pin_t)pin, S100_PIN_FUNC_GPIO);
        (void)s100_gpio_set_direction((s100_pin_t)pin, S100_PIN_DIR_OUT);
        (void)s100_pin_set_pull((s100_pin_t)pin, S100_PIN_PULL_UP);
        break;
    default:
        break;
    }
}

static void s100_pin_write_device(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    RT_UNUSED(device);
    (void)s100_gpio_write_pin((s100_pin_t)pin,
                              value ? S100_PIN_LEVEL_HIGH : S100_PIN_LEVEL_LOW);
}

static rt_ssize_t s100_pin_read_device(struct rt_device *device, rt_base_t pin)
{
    s100_pin_level_t level = S100_PIN_LEVEL_LOW;

    RT_UNUSED(device);
    if (s100_gpio_read_pin((s100_pin_t)pin, &level) != RT_EOK)
    {
        return PIN_LOW;
    }

    return (level == S100_PIN_LEVEL_HIGH) ? PIN_HIGH : PIN_LOW;
}

static rt_err_t s100_pin_attach_irq(struct rt_device *device,
                                    rt_base_t pin,
                                    rt_uint8_t mode,
                                    void (*hdr)(void *args),
                                    void *args)
{
    rt_base_t level;

    RT_UNUSED(device);
    if (!s100_pin_is_valid((s100_pin_t)pin))
    {
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();
    s100_pin_irq_hdr[pin].pin = pin;
    s100_pin_irq_hdr[pin].mode = mode;
    s100_pin_irq_hdr[pin].hdr = hdr;
    s100_pin_irq_hdr[pin].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t s100_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;

    RT_UNUSED(device);
    if (!s100_pin_is_valid((s100_pin_t)pin))
    {
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();
    s100_pin_irq_hdr[pin].pin = -1;
    s100_pin_irq_hdr[pin].mode = 0;
    s100_pin_irq_hdr[pin].hdr = RT_NULL;
    s100_pin_irq_hdr[pin].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t s100_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    rt_uint8_t port_index;
    rt_uint8_t bit_index;
    rt_uint32_t bit;
    s100_gpio_reg_t *gpio;
    rt_err_t ret;

    RT_UNUSED(device);
    ret = s100_pin_to_gpio((s100_pin_t)pin, &port_index, &bit_index);
    if (ret != RT_EOK)
    {
        return ret;
    }

    gpio = s100_gpio_ports[port_index];
    bit = 1UL << bit_index;

    if (enabled == PIN_IRQ_ENABLE)
    {
        ret = s100_gpio_config_irq(pin, s100_pin_irq_hdr[pin].mode);
        if (ret != RT_EOK)
        {
            return ret;
        }

        gpio->intmask &= ~bit;
        gpio->inten |= bit;
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        gpio->intmask |= bit;
        gpio->inten &= ~bit;
        gpio->porta_eoi = bit;
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static const struct rt_pin_ops s100_pin_ops =
{
    s100_pin_mode,
    s100_pin_write_device,
    s100_pin_read_device,
    s100_pin_attach_irq,
    s100_pin_detach_irq,
    s100_pin_irq_enable,
    RT_NULL,
};

static void s100_gpio_irq_dispatch(rt_uint8_t port_index)
{
    rt_uint32_t status;
    rt_uint8_t bit;
    s100_gpio_reg_t *gpio;

    gpio = s100_gpio_ports[port_index];
    status = gpio->intstatus;
    gpio->porta_eoi = status;

    for (bit = 0; bit < S100_GPIO_CHANNELS_PER_PORT; bit++)
    {
        s100_pin_t pin;
        rt_uint32_t mask = 1UL << bit;

        if ((status & mask) == 0U)
        {
            continue;
        }

        if (s100_gpio_to_pin(port_index, bit, &pin) != RT_EOK)
        {
            continue;
        }

        if (s100_pin_irq_hdr[pin].hdr != RT_NULL)
        {
            s100_pin_irq_hdr[pin].hdr(s100_pin_irq_hdr[pin].args);
        }
    }
}

static void s100_gpio_irq0_isr(int vector, void *param)
{
    RT_UNUSED(vector);
    RT_UNUSED(param);
    s100_gpio_irq_dispatch(0);
}

static void s100_gpio_irq1_isr(int vector, void *param)
{
    RT_UNUSED(vector);
    RT_UNUSED(param);
    s100_gpio_irq_dispatch(1);
}

static void s100_gpio_irq2_isr(int vector, void *param)
{
    RT_UNUSED(vector);
    RT_UNUSED(param);
    s100_gpio_irq_dispatch(2);
}

int rt_hw_pin_init(void)
{
    rt_size_t i;
    rt_isr_handler_t handlers[S100_GPIO_PORT_COUNT] =
    {
        s100_gpio_irq0_isr,
        s100_gpio_irq1_isr,
        s100_gpio_irq2_isr,
    };

    for (i = 0; i < S100_GPIO_PIN_COUNT; i++)
    {
        s100_pin_irq_hdr[i].pin = -1;
        s100_pin_irq_hdr[i].mode = 0;
        s100_pin_irq_hdr[i].hdr = RT_NULL;
        s100_pin_irq_hdr[i].args = RT_NULL;
    }

    /*
     * Each GPIO block reports through one parent interrupt. The per-pin RT-
     * Thread callbacks are dispatched in s100_gpio_irq_dispatch() after the
     * block-level status register is decoded.
     */
    for (i = 0; i < S100_GPIO_PORT_COUNT; i++)
    {
        rt_hw_interrupt_install(s100_gpio_port_irqs[i], handlers[i], RT_NULL, "gpio");
        rt_hw_interrupt_set_triger_mode(s100_gpio_port_irqs[i], IRQ_MODE_TRIG_LEVEL);
        rt_hw_interrupt_umask(s100_gpio_port_irqs[i]);
    }

    return rt_device_pin_register("pin", &s100_pin_ops, RT_NULL);
}
INIT_DEVICE_EXPORT(rt_hw_pin_init);

