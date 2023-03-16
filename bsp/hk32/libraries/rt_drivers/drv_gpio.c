/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-08-15     Jonas        first version
 */

#include <board.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define PIN_NUM(port, no)           (((((port) & 0xFu) << 4) | ((no) & 0xFu)))
#define PIN_PORT(pin)               ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin)                 ((uint8_t)((pin) & 0xFu))

#define PIN_HKPORTSOURCE(pin)       ((uint8_t)(((pin) & 0xF0u) >> 4))
#define PIN_HKPINSOURCE(pin)        ((uint8_t)((pin) & 0xFu))
#define PIN_HKPORT(pin)             ((GPIO_TypeDef *)(GPIOA_BASE + (0x400u * PIN_PORT(pin))))
#define PIN_HKPIN(pin)              ((uint16_t)(1u << PIN_NO(pin)))
#if defined(GPIOZ)
    #define __HK32_PORT_MAX 12u
#elif defined(GPIOK)
    #define __HK32_PORT_MAX 11u
#elif defined(GPIOJ)
    #define __HK32_PORT_MAX 10u
#elif defined(GPIOI)
    #define __HK32_PORT_MAX 9u
#elif defined(GPIOH)
    #define __HK32_PORT_MAX 8u
#elif defined(GPIOG)
    #define __HK32_PORT_MAX 7u
#elif defined(GPIOF)
    #define __HK32_PORT_MAX 6u
#elif defined(GPIOE)
    #define __HK32_PORT_MAX 5u
#elif defined(GPIOD)
    #define __HK32_PORT_MAX 4u
#elif defined(GPIOC)
    #define __HK32_PORT_MAX 3u
#elif defined(GPIOB)
    #define __HK32_PORT_MAX 2u
#elif defined(GPIOA)
    #define __HK32_PORT_MAX 1u
#else
    #define __HK32_PORT_MAX 0u
    #error Unsupported HK32 GPIO peripheral.
#endif
#define PIN_HKPORT_MAX __HK32_PORT_MAX

static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_Pin_0,  EXTI_Line0,  EXTI0_1_IRQn},
    {GPIO_Pin_1,  EXTI_Line1,  EXTI0_1_IRQn},
    {GPIO_Pin_2,  EXTI_Line2,  EXTI2_3_IRQn},
    {GPIO_Pin_3,  EXTI_Line3,  EXTI2_3_IRQn},
    {GPIO_Pin_4,  EXTI_Line4,  EXTI4_15_IRQn},
    {GPIO_Pin_5,  EXTI_Line5,  EXTI4_15_IRQn},
    {GPIO_Pin_6,  EXTI_Line6,  EXTI4_15_IRQn},
    {GPIO_Pin_7,  EXTI_Line7,  EXTI4_15_IRQn},
    {GPIO_Pin_8,  EXTI_Line8,  EXTI4_15_IRQn},
    {GPIO_Pin_9,  EXTI_Line9,  EXTI4_15_IRQn},
    {GPIO_Pin_10, EXTI_Line10, EXTI4_15_IRQn},
    {GPIO_Pin_11, EXTI_Line11, EXTI4_15_IRQn},
    {GPIO_Pin_12, EXTI_Line12, EXTI4_15_IRQn},
    {GPIO_Pin_13, EXTI_Line13, EXTI4_15_IRQn},
    {GPIO_Pin_14, EXTI_Line14, EXTI4_15_IRQn},
    {GPIO_Pin_15, EXTI_Line15, EXTI4_15_IRQn},
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

static void hk32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    if (PIN_PORT(pin) < PIN_HKPORT_MAX)
    {
        gpio_port    =  PIN_HKPORT(pin);
        gpio_pin     =  PIN_HKPIN(pin);
        GPIO_WriteBit(gpio_port, gpio_pin, (BitAction)value);
    }
}

static int hk32_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    int value;

    value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_HKPORT_MAX)
    {
        gpio_port    =  PIN_HKPORT(pin);
        gpio_pin     =  PIN_HKPIN(pin);
        value = GPIO_ReadInputDataBit(gpio_port, gpio_pin);
    }
    return value;
}

static void hk32_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    if (PIN_PORT(pin) < PIN_HKPORT_MAX)
    {
        gpio_port    =  PIN_HKPORT(pin);
        gpio_pin     =  PIN_HKPIN(pin);
    }
    else
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = gpio_pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    }

    GPIO_Init(gpio_port, &GPIO_InitStruct);
}

rt_inline rt_int32_t bit2bitno(rt_uint32_t bit)
{
    int i;
    for (i = 0; i < 32; i++)
    {
        if ((0x01 << i) == bit)
        {
            return i;
        }
    }
    return -1;
}

rt_inline const struct pin_irq_map *get_pin_irq_map(uint32_t pinbit)
{
    rt_int32_t mapindex = bit2bitno(pinbit);
    if (mapindex < 0 || mapindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
};

static rt_err_t hk32_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                    rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    uint16_t gpio_pin;
    if (PIN_PORT(pin) < PIN_HKPORT_MAX)
    {
        gpio_pin     =  PIN_HKPIN(pin);
    }
    else
    {
        return -RT_ENOSYS;
    }
    irqindex = bit2bitno(gpio_pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_ENOSYS;
    }

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

static rt_err_t hk32_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;
    uint16_t gpio_pin;
    if (PIN_PORT(pin) < PIN_HKPORT_MAX)
    {
        gpio_pin     =  PIN_HKPIN(pin);
    }
    else
    {
        return -RT_ENOSYS;
    }
    irqindex = bit2bitno(gpio_pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_ENOSYS;
    }

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

static rt_err_t hk32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                    rt_uint32_t enabled)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    if (PIN_PORT(pin) < PIN_HKPORT_MAX)
    {
        gpio_port    =  PIN_HKPORT(pin);
        gpio_pin     =  PIN_HKPIN(pin);
    }
    else
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(gpio_pin);
        if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
        {
            return -RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }

        irqmap = &pin_irq_map[irqindex];

        /* Configure GPIO_InitStructure */
        GPIO_StructInit(&GPIO_InitStruct);
        EXTI_StructInit(&EXTI_InitStruct);
        GPIO_InitStruct.GPIO_Pin = irqmap->pinbit;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        EXTI_InitStruct.EXTI_Line = irqmap->pinbit;
        EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStruct.EXTI_LineCmd = ENABLE;
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
            EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
            break;
        case PIN_IRQ_MODE_FALLING:
            GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
            EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
            break;
        }
        GPIO_Init(gpio_port, &GPIO_InitStruct);
        SYSCFG_EXTILineConfig(PIN_HKPORTSOURCE(pin), PIN_HKPINSOURCE(pin));
        EXTI_Init(&EXTI_InitStruct);
        NVIC_InitStruct.NVIC_IRQChannel = irqmap->irqno;
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_InitStruct.NVIC_IRQChannelPriority = 3;
        NVIC_Init(&NVIC_InitStruct);
        pin_irq_enable_mask |= irqmap->pinbit;

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(gpio_pin);
        if (irqmap == RT_NULL)
        {
            return -RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        pin_irq_enable_mask &= ~irqmap->pinbit;

        NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
        NVIC_InitStruct.NVIC_IRQChannelPriority = 3;

        if ((irqmap->pinbit >= GPIO_Pin_0) && (irqmap->pinbit <= GPIO_Pin_1))
        {
            if (!(pin_irq_enable_mask & (GPIO_Pin_0 | GPIO_Pin_1)))
            {
                NVIC_InitStruct.NVIC_IRQChannel = irqmap->irqno;
            }
        }
        else if ((irqmap->pinbit >= GPIO_Pin_2) && \
                 (irqmap->pinbit <= GPIO_Pin_3))
        {
            if (!(pin_irq_enable_mask & (GPIO_Pin_2 | GPIO_Pin_3)))
            {
                NVIC_InitStruct.NVIC_IRQChannel = irqmap->irqno;
            }
        }
        else if ((irqmap->pinbit >= GPIO_Pin_4) && \
                 (irqmap->pinbit <= GPIO_Pin_15))
        {
            if (!(pin_irq_enable_mask & (GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_6  | \
                                         GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | \
                                         GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | \
                                         GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)))
            {
                NVIC_InitStruct.NVIC_IRQChannel = irqmap->irqno;
            }
        }
        else
        {
            NVIC_InitStruct.NVIC_IRQChannel = irqmap->irqno;
        }

        NVIC_Init(&NVIC_InitStruct);
        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}
const static struct rt_pin_ops _hk32_pin_ops =
{
    hk32_pin_mode,
    hk32_pin_write,
    hk32_pin_read,
    hk32_pin_attach_irq,
    hk32_pin_dettach_irq,
    hk32_pin_irq_enable,
    RT_NULL,
};

rt_inline void pin_irq_hdr(int irqno)
{
    EXTI_ClearITPendingBit(pin_irq_map[irqno].lineno);
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
    pin_irq_hdr(bit2bitno(GPIO_Pin));
}

void EXTI0_1_IRQHandler(void)
{
    rt_interrupt_enter();
    if (RESET != EXTI_GetITStatus(EXTI_Line0))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_0);
    }
    if (RESET != EXTI_GetITStatus(EXTI_Line1))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_1);
    }
    rt_interrupt_leave();
}

void EXTI2_3_IRQHandler(void)
{
    rt_interrupt_enter();
    if (RESET != EXTI_GetITStatus(EXTI_Line2))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_2);
    }
    if (RESET != EXTI_GetITStatus(EXTI_Line3))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_3);
    }
    rt_interrupt_leave();
}

void EXTI4_15_IRQHandler(void)
{
    rt_interrupt_enter();
    if (RESET != EXTI_GetITStatus(EXTI_Line4))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_4);
    }
    if (RESET != EXTI_GetITStatus(EXTI_Line5))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_5);
    }
    if (RESET != EXTI_GetITStatus(EXTI_Line6))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_6);
    }
    if (RESET != EXTI_GetITStatus(EXTI_Line7))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_7);
    }
    if (RESET != EXTI_GetITStatus(EXTI_Line8))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_8);
    }
    if (RESET != EXTI_GetITStatus(EXTI_Line9))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_9);
    }
    if (RESET != EXTI_GetITStatus(EXTI_Line10))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_10);
    }
    if (RESET != EXTI_GetITStatus(EXTI_Line11))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_11);
    }
    if (RESET != EXTI_GetITStatus(EXTI_Line12))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_12);
    }
    if (RESET != EXTI_GetITStatus(EXTI_Line13))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_13);
    }
    if (RESET != EXTI_GetITStatus(EXTI_Line14))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_14);
    }
    if (RESET != EXTI_GetITStatus(EXTI_Line15))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pin_15);
    }
    rt_interrupt_leave();
}

int rt_hw_pin_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
#ifdef GPIOA
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
#endif
#ifdef GPIOB
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
#endif
#ifdef GPIOC
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
#endif
#ifdef GPIOD
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
#endif
#ifdef GPIOE
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOE, ENABLE);
#endif
#ifdef GPIOF
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
#endif
#ifdef GPIOG
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOG, ENABLE);
#endif

    return rt_device_pin_register("pin", &_hk32_pin_ops, RT_NULL);
}

INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* RT_USING_PIN */
