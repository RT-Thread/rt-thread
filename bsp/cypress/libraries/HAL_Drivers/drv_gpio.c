/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-1      Rbb666            first version
 */

#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define PIN_GET(pin)        ((uint8_t)(((uint8_t)pin) & 0x07U))
#define PORT_GET(pin)       ((uint8_t)(((uint8_t)pin) >> 3U))

#define __IFX_PORT_MAX      15u

#define PIN_IFXPORT_MAX     __IFX_PORT_MAX

static const struct pin_irq_map pin_irq_map[] =
{
    {CYHAL_PORT_0,  ioss_interrupts_gpio_0_IRQn},
    {CYHAL_PORT_1,  ioss_interrupts_gpio_1_IRQn},
    {CYHAL_PORT_2,  ioss_interrupts_gpio_2_IRQn},
    {CYHAL_PORT_3,  ioss_interrupts_gpio_3_IRQn},
    {CYHAL_PORT_4,  ioss_interrupts_gpio_4_IRQn},
    {CYHAL_PORT_5,  ioss_interrupts_gpio_5_IRQn},
    {CYHAL_PORT_6,  ioss_interrupts_gpio_6_IRQn},
    {CYHAL_PORT_7,  ioss_interrupts_gpio_7_IRQn},
    {CYHAL_PORT_8,  ioss_interrupts_gpio_8_IRQn},
    {CYHAL_PORT_9,  ioss_interrupts_gpio_9_IRQn},
    {CYHAL_PORT_10,  ioss_interrupts_gpio_10_IRQn},
    {CYHAL_PORT_11,  ioss_interrupts_gpio_11_IRQn},
    {CYHAL_PORT_12,  ioss_interrupts_gpio_12_IRQn},
    {CYHAL_PORT_13,  ioss_interrupts_gpio_13_IRQn},
    {CYHAL_PORT_14,  ioss_interrupts_gpio_14_IRQn},
};

static struct rt_pin_irq_hdr pin_irq_handler_tab[] =
{
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
};

rt_inline void pin_irq_handler(int irqno)
{
    if (pin_irq_handler_tab[irqno].hdr)
    {
        pin_irq_handler_tab[irqno].hdr(pin_irq_handler_tab[irqno].args);
    }
}

void gpio_exint_handler(uint16_t GPIO_Pin)
{
    pin_irq_handler(GPIO_Pin);
}

static void irq0_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_0);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq1_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_1);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq2_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_2);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq3_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_3);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq4_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_4);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq5_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_5);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq6_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_6);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq7_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_7);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq8_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_8);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq9_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_9);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq10_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_10);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq11_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_11);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq12_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_12);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq13_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_13);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void irq14_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(CYHAL_PORT_14);

    /* leave interrupt */
    rt_interrupt_leave();
}

/* interrupt0 callback definition*/
cyhal_gpio_callback_data_t irq0_cb_data =
{
    .callback     = irq0_callback,
    .callback_arg = (void *)NULL
};

static void ifx_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    rt_uint16_t gpio_pin;

    if (PORT_GET(pin) < PIN_IFXPORT_MAX)
    {
        gpio_pin = pin;
    }
    else
    {
        return;
    }

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        cyhal_gpio_configure(gpio_pin, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG);
        break;
    case PIN_MODE_INPUT:
        cyhal_gpio_configure(gpio_pin, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE);
        break;
    case PIN_MODE_INPUT_PULLUP:
        cyhal_gpio_configure(gpio_pin, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_PULL_NONE);
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        cyhal_gpio_configure(gpio_pin, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_PULL_NONE);
        break;
    case PIN_MODE_OUTPUT_OD:
        cyhal_gpio_configure(gpio_pin, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_OPENDRAINDRIVESHIGH);
        break;
    }
}

static void ifx_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    rt_uint16_t gpio_pin;

    if (PORT_GET(pin) < PIN_IFXPORT_MAX)
    {
        gpio_pin = pin;
    }
    else
    {
        return;
    }

    cyhal_gpio_write_internal(gpio_pin, value);
}

static int ifx_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value = PIN_LOW;
    rt_uint16_t gpio_pin;

    if (PORT_GET(pin) < PIN_IFXPORT_MAX)
    {
        gpio_pin = pin;
    }
    else
    {
        return -RT_ERROR;
    }

    return cyhal_gpio_read_internal(pin);
}

static rt_err_t ifx_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                   rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    rt_uint16_t gpio_port;
    rt_uint16_t gpio_pin;
    rt_base_t level;
    rt_uint8_t pin_irq_mode;

    if (PORT_GET(pin) < PIN_IFXPORT_MAX)
    {
        gpio_port = PORT_GET(pin);
        gpio_pin = pin;
    }
    else
    {
        return -RT_ERROR;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_handler_tab[gpio_port].pin == pin &&
            pin_irq_handler_tab[gpio_port].hdr == hdr &&
            pin_irq_handler_tab[gpio_port].mode == mode &&
            pin_irq_handler_tab[gpio_port].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (pin_irq_handler_tab[gpio_port].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EBUSY;
    }
    pin_irq_handler_tab[gpio_port].pin = pin;
    pin_irq_handler_tab[gpio_port].hdr = hdr;
    pin_irq_handler_tab[gpio_port].mode = mode;
    pin_irq_handler_tab[gpio_port].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t ifx_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    rt_uint16_t gpio_port;
    rt_uint16_t gpio_pin;
    rt_base_t level;
    rt_uint8_t pin_irq_mode;

    if (PORT_GET(pin) < PIN_IFXPORT_MAX)
    {
        gpio_port = PORT_GET(pin);
        gpio_pin = pin;
    }
    else
    {
        return -RT_ERROR;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_handler_tab[gpio_port].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }

    pin_irq_handler_tab[gpio_port].pin = -1;
    pin_irq_handler_tab[gpio_port].hdr = RT_NULL;
    pin_irq_handler_tab[gpio_port].mode = 0;
    pin_irq_handler_tab[gpio_port].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t ifx_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                   rt_uint32_t enabled)
{
    rt_uint16_t gpio_port;
    rt_uint16_t gpio_pin;
    rt_base_t level;
    rt_uint8_t pin_irq_mode;

    const struct pin_irq_map *irqmap;

    if (PORT_GET(pin) < PIN_IFXPORT_MAX)
    {
        gpio_port = PORT_GET(pin);
        gpio_pin = pin;
    }
    else
    {
        return -RT_ERROR;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        level = rt_hw_interrupt_disable();

        if (pin_irq_handler_tab[gpio_port].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_EINVAL;
        }

        irqmap = &pin_irq_map[gpio_port];

        cyhal_gpio_register_callback(gpio_pin, &irq0_cb_data);

        Cy_GPIO_ClearInterrupt(CYHAL_GET_PORTADDR(gpio_pin), CYHAL_GET_PIN(gpio_pin));

        switch (pin_irq_handler_tab[gpio_port].mode)
        {
        case PIN_IRQ_MODE_RISING:
            pin_irq_mode = CYHAL_GPIO_IRQ_RISE;
            break;
        case PIN_IRQ_MODE_FALLING:
            pin_irq_mode = CYHAL_GPIO_IRQ_FALL;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            pin_irq_mode = CYHAL_GPIO_IRQ_BOTH;
            break;
        default:
            break;
        }
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
        Cy_GPIO_SetInterruptEdge(CYHAL_GET_PORTADDR(gpio_pin), CYHAL_GET_PIN(gpio_pin), (uint32_t)pin_irq_mode);
        Cy_GPIO_SetInterruptMask(CYHAL_GET_PORTADDR(gpio_pin), CYHAL_GET_PIN(gpio_pin), (uint32_t)RT_TRUE);
#endif
#if !defined(COMPONENT_CAT1C)
        IRQn_Type irqn = (IRQn_Type)(irqmap->irqno + PORT_GET(irqmap->pin));
#endif
        if (false == NVIC_GetEnableIRQ(irqn))
        {
            _cyhal_irq_register(irqn, GPIO_INTERRUPT_PRIORITY, _cyhal_gpio_irq_handler);
            _cyhal_irq_enable(irqn);
        }
        else
        {
            _cyhal_irq_set_priority(irqn, GPIO_INTERRUPT_PRIORITY);
        }

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        level = rt_hw_interrupt_disable();

        Cy_GPIO_Port_Deinit(CYHAL_GET_PORTADDR(gpio_pin));

#if !defined(COMPONENT_CAT1C)
        IRQn_Type irqn = (IRQn_Type)(irqmap->irqno + PORT_GET(irqmap->pin));
#endif
        _cyhal_irq_disable(irqn);

        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

const static struct rt_pin_ops _ifx_pin_ops =
{
    ifx_pin_mode,
    ifx_pin_write,
    ifx_pin_read,
    ifx_pin_attach_irq,
    ifx_pin_dettach_irq,
    ifx_pin_irq_enable,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
    return rt_device_pin_register("pin", &_ifx_pin_ops, RT_NULL);
}

#endif /* RT_USING_PIN */
