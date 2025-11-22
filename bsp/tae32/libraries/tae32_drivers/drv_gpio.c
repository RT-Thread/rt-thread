/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-02-20     yeml           the first version
 */

#include <rtdevice.h>
#include <rthw.h>
#include <rtconfig.h>

#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define PIN_NUM_CALC(port, no) (((((port) & 0xFu) << 4) | ((no) & 0xFu)))

#define PIN_PORT_GET(pin) ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO_GET(pin) ((uint8_t)((pin) & 0xFu))

#define TAE32_PORT_GET(pin) ((GPIO_TypeDef *)(GPIOA_BASE + (0x1000u * PIN_PORT_GET(pin))))
#define TAE32_PIN_GET(pin)  ((uint16_t)(1u << PIN_NO_GET(pin)))

#if defined(GPIOZ)
    #define __TAE32_PORT_MAX 12u
#elif defined(GPIOK)
    #define __TAE32_PORT_MAX 11u
#elif defined(GPIOJ)
    #define __TAE32_PORT_MAX 10u
#elif defined(GPIOI)
    #define __TAE32_PORT_MAX 9u
#elif defined(GPIOH)
    #define __TAE32_PORT_MAX 8u
#elif defined(GPIOG)
    #define __TAE32_PORT_MAX 7u
#elif defined(GPIOF)
    #define __TAE32_PORT_MAX 6u
#elif defined(GPIOE)
    #define __TAE32_PORT_MAX 5u
#elif defined(GPIOD)
    #define __TAE32_PORT_MAX 4u
#elif defined(GPIOC)
    #define __TAE32_PORT_MAX 3u
#elif defined(GPIOB)
    #define __TAE32_PORT_MAX 2u
#elif defined(GPIOA)
    #define __TAE32_PORT_MAX 1u
#else
    #define __TAE32_PORT_MAX 0u
    #error Unsupported TAE32 GPIO peripheral.
#endif

#define PIN_TAEPORT_MAX __TAE32_PORT_MAX

struct tea32_pin_irq_hdr
{
    IRQn_Type irq_port;
    struct rt_pin_irq_hdr hdr_pin[16];
};

struct tea32_pin_irq_hdr pin_irq_hdr_tab[] =
{
    {
        GPIOA_IRQn,
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
        }
    },
    {
        GPIOB_IRQn,
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
        }
    },
    {   
        GPIOC_IRQn,
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
        }
    },
    {   
        GPIOD_IRQn,
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
        }
    },
    {   
        GPIOE_IRQn,
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
        }
    },
    {   
        GPIOF_IRQn,
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
        }
    }
};

static uint32_t irq_enable_mask[PIN_TAEPORT_MAX][16] = {0};

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])

static rt_base_t tae32_pin_get(const char *name)
{
    rt_base_t pin = 0;
    int hw_port_num, hw_pin_num = 0;
    int i, name_len;

    name_len = rt_strlen(name);

    if ((name_len < 4) || (name_len >= 6))
    {
        goto out;
    }
    if ((name[0] != 'P') || (name[2] != '.'))
    {
        goto out;
    }

    if ((name[1] >= 'A') && (name[1] <= 'Z'))
    {
        hw_port_num = (int)(name[1] - 'A');
    }
    else
    {
        goto out;
    }

    for (i = 3; i < name_len; i++)
    {
        hw_pin_num *= 10;
        hw_pin_num += name[i] - '0';
    }

    pin = PIN_NUM_CALC(hw_port_num, hw_pin_num);

    return pin;

out:
    rt_kprintf("Px.y  x:A~Z  y:0-15, e.g. PA.0\n");
    return -RT_EINVAL;
}

static void tae32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;

    if (PIN_PORT_GET(pin) < PIN_TAEPORT_MAX)
    {
        gpio_port = TAE32_PORT_GET(pin);
        gpio_pin = TAE32_PIN_GET(pin);

        LL_GPIO_WritePin(gpio_port, gpio_pin, (GPIO_PinStateETypeDef)value);
    }
}

static rt_size_t tae32_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    GPIO_PinStateETypeDef state = GPIO_PIN_RESET;

    if (PIN_PORT_GET(pin) < PIN_TAEPORT_MAX)
    {
        gpio_port = TAE32_PORT_GET(pin);
        gpio_pin = TAE32_PIN_GET(pin);
        state = LL_GPIO_ReadPin(gpio_port, gpio_pin);
    }
    else
    {
        return -RT_EINVAL;
    }

    return (state == GPIO_PIN_RESET) ? PIN_LOW : PIN_HIGH;
}

static void tae32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    if (PIN_PORT_GET(pin) >= PIN_TAEPORT_MAX)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.Pin = (uint32_t)TAE32_PIN_GET(pin);
    GPIO_InitStruct.OType = GPIO_OTYPE_PP;
    GPIO_InitStruct.Alternate = GPIO_AF1_OUTPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        /* output setting */
        GPIO_InitStruct.Alternate = GPIO_AF1_OUTPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        break;
    case PIN_MODE_INPUT:
        /* input setting: not pull. */
        GPIO_InitStruct.Alternate = GPIO_AF0_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        break;
    case PIN_MODE_INPUT_PULLUP:
        /* input setting: pull up. */
        GPIO_InitStruct.Alternate = GPIO_AF0_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        /* input setting: pull down. */
        GPIO_InitStruct.Alternate = GPIO_AF0_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        break;
    case PIN_MODE_OUTPUT_OD:
        /* output setting: od. */
        GPIO_InitStruct.OType = GPIO_OTYPE_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        break;

    default:
        break;
    }
    LL_GPIO_Init(TAE32_PORT_GET(pin), &GPIO_InitStruct);
}

rt_inline rt_int32_t bit2bitno(rt_uint32_t bit)
{
    rt_int32_t i;
    for (i = 0; i < 32; i++)
    {
        if (((rt_uint32_t)0x01 << i) == bit)
        {
            return i;
        }
    }
    return -1;
}

rt_inline rt_int32_t gpio_port_index(GPIO_TypeDef *port)
{
    rt_uint32_t gpio_port;
    gpio_port = (rt_uint32_t)port;
    switch (gpio_port)
    {
    case GPIOA_BASE:
        return 0;
    case GPIOB_BASE:
        return 1;
    case GPIOC_BASE:
        return 2;
    case GPIOD_BASE:
        return 3;
    case GPIOE_BASE:
        return 4;
    case GPIOF_BASE:
        return 5;
    }
    return -1;
}

static rt_err_t tae32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqPinIndex = -1;
    rt_int32_t irqPortIndex = -1;

    irqPinIndex = bit2bitno(TAE32_PIN_GET(pin));
    irqPortIndex = gpio_port_index(TAE32_PORT_GET(pin));

    if (irqPortIndex < 0 || irqPortIndex > PIN_TAEPORT_MAX)
    {
        return -RT_ENOSYS;
    }
    if (irqPinIndex < 0 || irqPinIndex >= (rt_int32_t)ITEM_NUM(pin_irq_hdr_tab[irqPortIndex].hdr_pin))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].pin == pin &&
            pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].hdr == hdr &&
            pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].mode == mode &&
            pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }

    if (pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }

    pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].pin = pin;
    pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].hdr = hdr;
    pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].mode = mode;
    pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t tae32_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;
    rt_int32_t irqPinIndex = -1;
    rt_int32_t irqPortIndex = -1;

    irqPinIndex = bit2bitno(TAE32_PIN_GET(pin));
    irqPortIndex = gpio_port_index(TAE32_PORT_GET(pin));

    if (irqPortIndex < 0 || irqPortIndex > PIN_TAEPORT_MAX)
    {
        return -RT_ENOSYS;
    }
    if (irqPinIndex < 0 || irqPinIndex >= (rt_int32_t)ITEM_NUM(pin_irq_hdr_tab[irqPortIndex].hdr_pin))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].pin = -1;
    pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].hdr = RT_NULL;
    pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].mode = 0;
    pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t tae32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t enabled)
{
    rt_base_t level;
    rt_uint8_t i;
    rt_int32_t irqPinIndex = -1;
    rt_int32_t irqPortIndex = -1;

    GPIO_InitTypeDef GPIO_InitStruct;

    irqPinIndex = bit2bitno(TAE32_PIN_GET(pin));
    irqPortIndex = gpio_port_index(TAE32_PORT_GET(pin));

    if (PIN_PORT_GET(pin) >= PIN_TAEPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    if (irqPortIndex < 0 || irqPortIndex > (rt_int32_t)ITEM_NUM(pin_irq_hdr_tab))
    {
        return -RT_ENOSYS;
    }
    if (irqPinIndex < 0 || irqPinIndex >= (rt_int32_t)ITEM_NUM(pin_irq_hdr_tab[irqPortIndex].hdr_pin))
    {
        return -RT_ENOSYS;
    }


    if (enabled == PIN_IRQ_ENABLE)
    {

        level = rt_hw_interrupt_disable();

        if (pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }

        GPIO_InitStruct.Pin = TAE32_PIN_GET(pin);
        GPIO_InitStruct.Alternate = GPIO_AF0_INPUT;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        switch (pin_irq_hdr_tab[irqPortIndex].hdr_pin[irqPinIndex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            GPIO_InitStruct.Pull = GPIO_PULLDOWN;
            GPIO_InitStruct.IntMode = GPIO_INT_MODE_RISING;
            break;
        case PIN_IRQ_MODE_FALLING:
            GPIO_InitStruct.Pull = GPIO_PULLUP;
            GPIO_InitStruct.IntMode = GPIO_INT_MODE_FALLING;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.IntMode = GPIO_INT_MODE_RISING_FALLING;
            break;
        }
        LL_GPIO_Init(TAE32_PORT_GET(pin), &GPIO_InitStruct);
        LL_NVIC_EnableIRQ(pin_irq_hdr_tab[irqPortIndex].irq_port);

        irq_enable_mask[irqPortIndex][irqPinIndex] = RT_TRUE;

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        level = rt_hw_interrupt_disable();
        LL_GPIO_DeInit(TAE32_PORT_GET(pin), TAE32_PIN_GET(pin));

        irq_enable_mask[irqPortIndex][irqPinIndex] = RT_FALSE;
        for (i = 0; i < 16; i++)
        {
            if (irq_enable_mask[irqPortIndex][i])
            {
                break;
            }
        }
        if (i >= 16)
        {
            LL_NVIC_DisableIRQ(pin_irq_hdr_tab[irqPortIndex].irq_port);
        }
        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static const struct rt_pin_ops tae32_pin_ops =
{
    tae32_pin_mode,
    tae32_pin_write,
    tae32_pin_read,
    tae32_pin_attach_irq,
    tae32_pin_dettach_irq,
    tae32_pin_irq_enable,
    tae32_pin_get,
};

rt_inline void pin_irq_hdr(rt_int32_t irq_port_index, rt_int32_t irq_pin_index)
{
    if (pin_irq_hdr_tab[irq_port_index].hdr_pin[irq_pin_index].hdr)
    {
        pin_irq_hdr_tab[irq_port_index].hdr_pin[irq_pin_index].hdr(pin_irq_hdr_tab[irq_port_index].hdr_pin[irq_pin_index].args);
    }
}

void LL_GPIO_ExtTrigCallback(GPIO_TypeDef *Instance, uint32_t pin)
{
    pin_irq_hdr(gpio_port_index(Instance), bit2bitno(pin));
}

void GPIOA_IRQHandler(void)
{
    rt_interrupt_enter();
    LL_GPIO_IRQHandler(GPIOA);
    rt_interrupt_leave();
}

void GPIOB_IRQHandler(void)
{
    rt_interrupt_enter();
    LL_GPIO_IRQHandler(GPIOB);
    rt_interrupt_leave();
}

void GPIOC_IRQHandler(void)
{
    rt_interrupt_enter();
    LL_GPIO_IRQHandler(GPIOC);
    rt_interrupt_leave();
}

void GPIOD_IRQHandler(void)
{
    rt_interrupt_enter();
    LL_GPIO_IRQHandler(GPIOD);
    rt_interrupt_leave();
}

void GPIOE_IRQHandler(void)
{
    rt_interrupt_enter();
    LL_GPIO_IRQHandler(GPIOE);
    rt_interrupt_leave();
}

void GPIOF_IRQHandler(void)
{
    rt_interrupt_enter();
    LL_GPIO_IRQHandler(GPIOF);
    rt_interrupt_leave();
}

int rt_hw_pin_init(void)
{
    int result;

    result = rt_device_pin_register("pin", &tae32_pin_ops, RT_NULL);

    return result;
}

INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* RT_USING_PIN */