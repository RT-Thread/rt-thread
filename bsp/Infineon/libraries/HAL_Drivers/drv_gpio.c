/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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

static cyhal_gpio_callback_data_t irq_cb_data[PIN_IFXPORT_MAX];

static const struct pin_irq_map pin_irq_map[] =
{
    {CYHAL_PORT_0,  ioss_interrupts_gpio_0_IRQn},
#if !defined(SOC_CY8C6245LQI_S3D72) && !defined(SOC_CY8C6244LQI_S4D92)
    {CYHAL_PORT_1,  ioss_interrupts_gpio_1_IRQn},
#endif
    {CYHAL_PORT_2,  ioss_interrupts_gpio_2_IRQn},
    {CYHAL_PORT_3,  ioss_interrupts_gpio_3_IRQn},
#if !defined(SOC_CY8C6245LQI_S3D72) && !defined(SOC_CY8C6244LQI_S4D92)
    {CYHAL_PORT_4,  ioss_interrupts_gpio_4_IRQn},
#endif
    {CYHAL_PORT_5,  ioss_interrupts_gpio_5_IRQn},
    {CYHAL_PORT_6,  ioss_interrupts_gpio_6_IRQn},
    {CYHAL_PORT_7,  ioss_interrupts_gpio_7_IRQn},
    {CYHAL_PORT_8,  ioss_interrupts_gpio_8_IRQn},
    {CYHAL_PORT_9,  ioss_interrupts_gpio_9_IRQn},
    {CYHAL_PORT_10,  ioss_interrupts_gpio_10_IRQn},
    {CYHAL_PORT_11,  ioss_interrupts_gpio_11_IRQn},
    {CYHAL_PORT_12,  ioss_interrupts_gpio_12_IRQn},
#if !defined(SOC_CY8C6245LQI_S3D72) && !defined(SOC_CY8C6244LQI_S4D92)
    {CYHAL_PORT_13,  ioss_interrupts_gpio_13_IRQn},
#endif
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
    Cy_GPIO_ClearInterrupt(CYHAL_GET_PORTADDR(irqno), CYHAL_GET_PIN(irqno));

    if (pin_irq_handler_tab[irqno].hdr)
    {
        pin_irq_handler_tab[irqno].hdr(pin_irq_handler_tab[irqno].args);
    }
}

void gpio_exint_handler(uint16_t GPIO_Port)
{
    pin_irq_handler(GPIO_Port);
}

/* interrupt callback definition*/
static void irq_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    /* To avoid compiler warnings */
    (void) callback_arg;
    (void) event;

    /* enter interrupt */
    rt_interrupt_enter();

    gpio_exint_handler(*(rt_uint16_t *)callback_arg);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void ifx_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
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
        cyhal_gpio_init(gpio_pin, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, true);
        break;

    case PIN_MODE_INPUT:
        cyhal_gpio_init(gpio_pin, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
        break;

    case PIN_MODE_INPUT_PULLUP:
        cyhal_gpio_init(gpio_pin, CYHAL_GPIO_DIR_BIDIRECTIONAL, CYHAL_GPIO_DRIVE_PULLUP, true);
        break;

    case PIN_MODE_INPUT_PULLDOWN:
        cyhal_gpio_init(gpio_pin, CYHAL_GPIO_DIR_BIDIRECTIONAL, CYHAL_GPIO_DRIVE_PULLDOWN, false);
        break;

    case PIN_MODE_OUTPUT_OD:
        cyhal_gpio_init(gpio_pin, CYHAL_GPIO_DIR_BIDIRECTIONAL, CYHAL_GPIO_DRIVE_PULLUP, true);
        break;
    }
}

static void ifx_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
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

    cyhal_gpio_write(gpio_pin, value);
}

static rt_int8_t ifx_pin_read(struct rt_device *device, rt_base_t pin)
{
    rt_uint16_t gpio_pin;

    if (PORT_GET(pin) < PIN_IFXPORT_MAX)
    {
        gpio_pin = pin;
    }
    else
    {
        return -RT_ERROR;
    }

    return cyhal_gpio_read(gpio_pin);
}

static rt_err_t ifx_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                   rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_uint16_t gpio_port;
    rt_uint16_t gpio_pin;
    rt_base_t level;

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
        return -RT_EBUSY;
    }

    pin_irq_handler_tab[gpio_port].pin = pin;
    pin_irq_handler_tab[gpio_port].hdr = hdr;
    pin_irq_handler_tab[gpio_port].mode = mode;
    pin_irq_handler_tab[gpio_port].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t ifx_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_uint16_t gpio_port;
    rt_uint16_t gpio_pin;
    rt_base_t level;

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
                                   rt_uint8_t enabled)
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

#if !defined(COMPONENT_CAT1C)
        IRQn_Type irqn = (IRQn_Type)(irqmap->irqno + PORT_GET(irqmap->port));
#endif
        irq_cb_data[irqn].callback = irq_callback;
        irq_cb_data[irqn].callback_arg = (rt_uint16_t *)&pin_irq_map[gpio_port].port;

        cyhal_gpio_register_callback(gpio_pin, &irq_cb_data[irqn]);

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

        cyhal_gpio_enable_event(gpio_pin, pin_irq_mode, GPIO_INTERRUPT_PRIORITY, RT_TRUE);

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        level = rt_hw_interrupt_disable();

        Cy_GPIO_Port_Deinit(CYHAL_GET_PORTADDR(gpio_pin));

#if !defined(COMPONENT_CAT1C)
        IRQn_Type irqn = (IRQn_Type)(irqmap->irqno + PORT_GET(irqmap->port));
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
