/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-09-18     AisinoChip        first version
 */

#include <rthw.h>
#include <rtdevice.h>
#include "board.h"

#ifdef RT_USING_PIN

#define __ACM32_PIN(index, gpio, gpio_index)                                \
    {                                                                       \
        index, GPIO##gpio, GPIO_PIN_##gpio_index                            \
    }

#define __ACM32_PIN_RESERVE                                                 \
    {                                                                       \
        -1, 0, 0                                                            \
    }

/* ACM32 GPIO driver */
struct pin_index
{
    int             index;
    enum_GPIOx_t    gpio;
    uint32_t        pin;
};

struct pin_irq_map
{
    rt_uint16_t         line;
    EXTI_HandleTypeDef  handle;
};

static const struct pin_index pins[] =
{
#if defined(BSP_USING_GPIO1)
    __ACM32_PIN(0,   A, 0),
    __ACM32_PIN(1,   A, 1),
    __ACM32_PIN(2,   A, 2),
    __ACM32_PIN(3,   A, 3),
    __ACM32_PIN(4,   A, 4),
    __ACM32_PIN(5,   A, 5),
    __ACM32_PIN(6,   A, 6),
    __ACM32_PIN(7,   A, 7),
    __ACM32_PIN(8,   A, 8),
    __ACM32_PIN(9,   A, 9),
    __ACM32_PIN(10,  A, 10),
    __ACM32_PIN(11,  A, 11),
    __ACM32_PIN(12,  A, 12),
    __ACM32_PIN(13,  A, 13),
    __ACM32_PIN(14,  A, 14),
    __ACM32_PIN(15,  A, 15),
    __ACM32_PIN(16,  B, 0),
    __ACM32_PIN(17,  B, 1),
    __ACM32_PIN(18,  B, 2),
    __ACM32_PIN(19,  B, 3),
    __ACM32_PIN(20,  B, 4),
    __ACM32_PIN(21,  B, 5),
    __ACM32_PIN(22,  B, 6),
    __ACM32_PIN(23,  B, 7),
    __ACM32_PIN(24,  B, 8),
    __ACM32_PIN(25,  B, 9),
    __ACM32_PIN(26,  B, 10),
    __ACM32_PIN(27,  B, 11),
    __ACM32_PIN(28,  B, 12),
    __ACM32_PIN(29,  B, 13),
    __ACM32_PIN(30,  B, 14),
    __ACM32_PIN(31,  B, 15),
#if defined(BSP_USING_GPIO2)
    __ACM32_PIN(32,  C, 0),
    __ACM32_PIN(33,  C, 1),
    __ACM32_PIN(34,  C, 2),
    __ACM32_PIN(35,  C, 3),
    __ACM32_PIN(36,  C, 4),
    __ACM32_PIN(37,  C, 5),
    __ACM32_PIN(38,  C, 6),
    __ACM32_PIN(39,  C, 7),
    __ACM32_PIN(40,  C, 8),
    __ACM32_PIN(41,  C, 9),
    __ACM32_PIN(42,  C, 10),
    __ACM32_PIN(43,  C, 11),
    __ACM32_PIN(44,  C, 12),
    __ACM32_PIN(45,  C, 13),
    __ACM32_PIN(46,  C, 14),
    __ACM32_PIN(47,  C, 15),
    __ACM32_PIN(48,  D, 0),
    __ACM32_PIN(49,  D, 1),
    __ACM32_PIN(50,  D, 2),
    __ACM32_PIN(51,  D, 3),
    __ACM32_PIN(52,  D, 4),
    __ACM32_PIN(53,  D, 5),
    __ACM32_PIN(54,  D, 6),
    __ACM32_PIN(55,  D, 7),
    __ACM32_PIN(56,  D, 8),
    __ACM32_PIN(57,  D, 9),
    __ACM32_PIN(58,  D, 10),
    __ACM32_PIN(59,  D, 11),
    __ACM32_PIN(60,  D, 12),
    __ACM32_PIN(61,  D, 13),
    __ACM32_PIN(62,  D, 14),
    __ACM32_PIN(63,  D, 15),
#if defined(BSP_USING_GPIO3)
    __ACM32_PIN(64,  E, 0),
    __ACM32_PIN(65,  E, 1),
    __ACM32_PIN(66,  E, 2),
    __ACM32_PIN(67,  E, 3),
    __ACM32_PIN(68,  E, 4),
    __ACM32_PIN(69,  E, 5),
    __ACM32_PIN(70,  E, 6),
    __ACM32_PIN(71,  E, 7),
    __ACM32_PIN(72,  E, 8),
    __ACM32_PIN(73,  E, 9),
    __ACM32_PIN(74,  E, 10),
    __ACM32_PIN(75,  E, 11),
    __ACM32_PIN(76,  E, 12),
    __ACM32_PIN(77,  E, 13),
    __ACM32_PIN(78,  E, 14),
    __ACM32_PIN(79,  E, 15),
    __ACM32_PIN(80,  F, 0),
    __ACM32_PIN(81,  F, 1),
    __ACM32_PIN(82,  F, 2),
    __ACM32_PIN(83,  F, 3),
    __ACM32_PIN(84,  F, 4),
#endif /* defined(BSP_USING_GPIO3) */
#endif /* defined(BSP_USING_GPIO2) */
#endif /* defined(BSP_USING_GPIO1) */
};

static struct pin_irq_map pin_irq_map[] =
{
    {EXTI_LINE_0,  {0}},
    {EXTI_LINE_1,  {0}},
    {EXTI_LINE_2,  {0}},
    {EXTI_LINE_3,  {0}},
    {EXTI_LINE_4,  {0}},
    {EXTI_LINE_5,  {0}},
    {EXTI_LINE_6,  {0}},
    {EXTI_LINE_7,  {0}},
    {EXTI_LINE_8,  {0}},
    {EXTI_LINE_9,  {0}},
    {EXTI_LINE_10, {0}},
    {EXTI_LINE_11, {0}},
    {EXTI_LINE_12, {0}},
    {EXTI_LINE_13, {0}},
    {EXTI_LINE_14, {0}},
    {EXTI_LINE_15, {0}},
};

static struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
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
static uint32_t pin_irq_enable_mask = 0;

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
static const struct pin_index *get_pin(uint8_t pin)
{
    const struct pin_index *index;

    if (pin < ITEM_NUM(pins))
    {
        index = &pins[pin];
        if (index->index == -1)
            index = RT_NULL;
    }
    else
    {
        index = RT_NULL;
    }

    return index;
};

static void _pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    HAL_GPIO_WritePin(index->gpio, index->pin, (enum_PinState_t)value);
}

static rt_ssize_t _pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    const struct pin_index *index;

    value = PIN_LOW;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_EINVAL;
    }

    value = HAL_GPIO_ReadPin(index->gpio, index->pin);

    return value;
}

static void _pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    const struct pin_index *index;
    GPIO_InitTypeDef GPIO_InitStruct;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.Pin = index->pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Alternate = GPIO_FUNCTION_0;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }

    /* special PIN process */
    __HAL_RTC_PC13_DIGIT();

    HAL_GPIO_Init(index->gpio, &GPIO_InitStruct);
}

#define     PIN2INDEX(pin)      ((pin) % 16)

static rt_err_t _pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    irqindex = PIN2INDEX(pin);

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == pin &&
            pin_irq_hdr_tab[irqindex].hdr == hdr &&
            pin_irq_hdr_tab[irqindex].mode == mode &&
            pin_irq_hdr_tab[irqindex].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }

    if (pin_irq_hdr_tab[irqindex].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }

    pin_irq_hdr_tab[irqindex].pin = pin;
    pin_irq_hdr_tab[irqindex].hdr = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t _pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    irqindex = PIN2INDEX(pin);

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[irqindex].pin = -1;
    pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
    pin_irq_hdr_tab[irqindex].mode = 0;
    pin_irq_hdr_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t _pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t enabled)
{
    const struct pin_index *index;
    struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    GPIO_InitTypeDef GPIO_InitStruct;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    irqindex = PIN2INDEX(pin);
    irqmap = &pin_irq_map[irqindex];

    if (enabled == PIN_IRQ_ENABLE)
    {
        level = rt_hw_interrupt_disable();

        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }

        /* Configure GPIO_InitStructure */
        GPIO_InitStruct.Pin = index->pin;
        GPIO_InitStruct.Alternate = GPIO_FUNCTION_0;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;

        irqmap->handle.u32_Line = irqmap->line;
        irqmap->handle.u32_Mode = EXTI_MODE_INTERRUPT;

        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            GPIO_InitStruct.Pull = GPIO_PULLDOWN;
            irqmap->handle.u32_Trigger = EXTI_TRIGGER_RISING;
            break;
        case PIN_IRQ_MODE_FALLING:
            GPIO_InitStruct.Pull = GPIO_PULLUP;
            irqmap->handle.u32_Trigger = EXTI_TRIGGER_FALLING;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            irqmap->handle.u32_Trigger = EXTI_TRIGGER_RISING_FALLING;
            break;
        }
        HAL_GPIO_Init(index->gpio, &GPIO_InitStruct);

        irqmap->handle.u32_GPIOSel = pin / 16;

        HAL_EXTI_SetConfigLine(&irqmap->handle);

        pin_irq_enable_mask |= 1 << irqindex;

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        if ((pin_irq_enable_mask & (1 << irqindex)) == 0)
        {
            return -RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        EXTI->IENR &= ~irqmap->line;
        EXTI->EENR &= ~irqmap->line;

        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

const static struct rt_pin_ops _acm32_pin_ops =
{
    _pin_mode,
    _pin_write,
    _pin_read,
    _pin_attach_irq,
    _pin_dettach_irq,
    _pin_irq_enable,
};

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

int rt_hw_pin_init(void)
{
    return rt_device_pin_register("pin", &_acm32_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

void EXTI_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    for (int i = 0; i < 16; i++)
    {
        if (EXTI->PDR & pin_irq_map[i].line)
        {
            EXTI->PDR = pin_irq_map[i].line;
            pin_irq_hdr(i);
            break;
        }
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* RT_USING_PIN */

