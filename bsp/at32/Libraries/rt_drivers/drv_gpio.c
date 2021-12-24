/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-01-07     shelton           first version
 * 2021-10-28     jonas             optimization design pin-index algorithm
 */

#include <board.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define PIN_NUM(port, no)           (((((port) & 0xFu) << 4) | ((no) & 0xFu)))
#define PIN_PORT(pin)               ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin)                 ((uint8_t)((pin) & 0xFu))

#define PIN_ATPORTSOURCE(pin)       ((uint8_t)(((pin) & 0xF0u) >> 4))
#define PIN_ATPINSOURCE(pin)        ((uint8_t)((pin) & 0xFu))
#define PIN_ATPORT(pin)             ((GPIO_Type *)(GPIOA_BASE + (0x400u * PIN_PORT(pin))))
#define PIN_ATPIN(pin)              ((uint16_t)(1u << PIN_NO(pin)))
#if defined(GPIOZ)
    #define __AT32_PORT_MAX 12u
#elif defined(GPIOK)
    #define __AT32_PORT_MAX 11u
#elif defined(GPIOJ)
    #define __AT32_PORT_MAX 10u
#elif defined(GPIOI)
    #define __AT32_PORT_MAX 9u
#elif defined(GPIOH)
    #define __AT32_PORT_MAX 8u
#elif defined(GPIOG)
    #define __AT32_PORT_MAX 7u
#elif defined(GPIOF)
    #define __AT32_PORT_MAX 6u
#elif defined(GPIOE)
    #define __AT32_PORT_MAX 5u
#elif defined(GPIOD)
    #define __AT32_PORT_MAX 4u
#elif defined(GPIOC)
    #define __AT32_PORT_MAX 3u
#elif defined(GPIOB)
    #define __AT32_PORT_MAX 2u
#elif defined(GPIOA)
    #define __AT32_PORT_MAX 1u
#else
    #define __AT32_PORT_MAX 0u
    #error Unsupported AT32 GPIO peripheral.
#endif
#define PIN_ATPORT_MAX __AT32_PORT_MAX

static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_Pins_0,  EXTI_Line0,  EXTI0_IRQn},
    {GPIO_Pins_1,  EXTI_Line1,  EXTI1_IRQn},
    {GPIO_Pins_2,  EXTI_Line2,  EXTI2_IRQn},
    {GPIO_Pins_3,  EXTI_Line3,  EXTI3_IRQn},
    {GPIO_Pins_4,  EXTI_Line4,  EXTI4_IRQn},
    {GPIO_Pins_5,  EXTI_Line5,  EXTI9_5_IRQn},
    {GPIO_Pins_6,  EXTI_Line6,  EXTI9_5_IRQn},
    {GPIO_Pins_7,  EXTI_Line7,  EXTI9_5_IRQn},
    {GPIO_Pins_8,  EXTI_Line8,  EXTI9_5_IRQn},
    {GPIO_Pins_9,  EXTI_Line9,  EXTI9_5_IRQn},
    {GPIO_Pins_10, EXTI_Line10, EXTI15_10_IRQn},
    {GPIO_Pins_11, EXTI_Line11, EXTI15_10_IRQn},
    {GPIO_Pins_12, EXTI_Line12, EXTI15_10_IRQn},
    {GPIO_Pins_13, EXTI_Line13, EXTI15_10_IRQn},
    {GPIO_Pins_14, EXTI_Line14, EXTI15_10_IRQn},
    {GPIO_Pins_15, EXTI_Line15, EXTI15_10_IRQn},
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

static void at32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    GPIO_Type *gpio_port;
    uint16_t gpio_pin;
    if (PIN_PORT(pin) < PIN_ATPORT_MAX)
    {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
    }
    else
    {
        return;
    }
    GPIO_WriteBit(gpio_port, gpio_pin, (BitState)value);
}

static int at32_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_Type *gpio_port;
    uint16_t gpio_pin;
    int value;

    value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX)
    {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
        value = GPIO_ReadInputDataBit(gpio_port, gpio_pin);
    }
    return value;
}

static void at32_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    GPIO_InitType GPIO_InitStruct;
    GPIO_Type *gpio_port;
    uint16_t gpio_pin;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX)
    {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
    }
    else
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pins = gpio_pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT_PP;
    GPIO_InitStruct.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT_PP;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_PU;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_PD;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT_OD;
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

static rt_err_t at32_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                    rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    RT_UNUSED GPIO_Type *gpio_port;
    uint16_t gpio_pin;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX)
    {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
    }
    else
    {
        return -RT_EINVAL;
    }

    irqindex = bit2bitno(gpio_pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_EINVAL;
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

static rt_err_t at32_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    RT_UNUSED GPIO_Type *gpio_port;
    uint16_t gpio_pin;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX)
    {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
    }
    else
    {
        return -RT_EINVAL;
    }
    irqindex = bit2bitno(gpio_pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_EINVAL;
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

static rt_err_t at32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                    rt_uint32_t enabled)
{
    GPIO_InitType GPIO_InitStruct;
    EXTI_InitType EXTI_InitStruct;
    NVIC_InitType NVIC_InitStruct;
    GPIO_Type *gpio_port;
    uint16_t gpio_pin;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX)
    {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
    }
    else
    {
        return -RT_EINVAL;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(gpio_pin);
        if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
        {
            return -RT_EINVAL;
        }

        level = rt_hw_interrupt_disable();

        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_EINVAL;
        }

        irqmap = &pin_irq_map[irqindex];

        /* Configure GPIO_InitStructure */
        GPIO_StructInit(&GPIO_InitStruct);
        EXTI_StructInit(&EXTI_InitStruct);
        GPIO_InitStruct.GPIO_Pins = irqmap->pinbit;
        GPIO_InitStruct.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
        EXTI_InitStruct.EXTI_Line = irqmap->pinbit;
        EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStruct.EXTI_LineEnable = ENABLE;
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
            break;
        case PIN_IRQ_MODE_FALLING:
            EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
            break;
        }
        GPIO_Init(gpio_port, &GPIO_InitStruct);

        GPIO_EXTILineConfig(PIN_ATPORTSOURCE(pin), PIN_ATPINSOURCE(pin));

        EXTI_Init(&EXTI_InitStruct);
        NVIC_InitStruct.NVIC_IRQChannel = irqmap->irqno;
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 5;
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
        NVIC_Init(&NVIC_InitStruct);
        pin_irq_enable_mask |= irqmap->pinbit;

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(gpio_pin);
        if (irqmap == RT_NULL)
        {
            return -RT_EINVAL;
        }

        level = rt_hw_interrupt_disable();

        pin_irq_enable_mask &= ~irqmap->pinbit;

        NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 5;
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

        if ((irqmap->pinbit >= GPIO_Pins_5) && (irqmap->pinbit <= GPIO_Pins_9))
        {
            if (!(pin_irq_enable_mask & (GPIO_Pins_5 | GPIO_Pins_6 | GPIO_Pins_7 | GPIO_Pins_8 | GPIO_Pins_9)))
            {
                NVIC_InitStruct.NVIC_IRQChannel = irqmap->irqno;
            }
        }
        else if ((irqmap->pinbit >= GPIO_Pins_10) && (irqmap->pinbit <= GPIO_Pins_15))
        {
            if (!(pin_irq_enable_mask & (GPIO_Pins_10 | GPIO_Pins_11 | GPIO_Pins_12 | GPIO_Pins_13 | GPIO_Pins_14 | GPIO_Pins_15)))
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
        return -RT_EINVAL;
    }

    return RT_EOK;
}

const static struct rt_pin_ops _at32_pin_ops =
{
    at32_pin_mode,
    at32_pin_write,
    at32_pin_read,
    at32_pin_attach_irq,
    at32_pin_dettach_irq,
    at32_pin_irq_enable,
    RT_NULL,
};

rt_inline void pin_irq_hdr(int irqno)
{
    EXTI_ClearIntPendingBit(pin_irq_map[irqno].lineno);
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
    pin_irq_hdr(bit2bitno(GPIO_Pin));
}

void EXTI0_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(GPIO_Pins_0);
    rt_interrupt_leave();
}

void EXTI1_IRQHandler(void)
{
    rt_interrupt_enter();
    EXTI_ClearIntPendingBit(GPIO_Pins_1);
    GPIO_EXTI_IRQHandler(GPIO_Pins_1);
    rt_interrupt_leave();
}

void EXTI2_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(GPIO_Pins_2);
    rt_interrupt_leave();
}

void EXTI3_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(GPIO_Pins_3);
    rt_interrupt_leave();
}

void EXTI4_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(GPIO_Pins_4);
    rt_interrupt_leave();
}

void EXTI9_5_IRQHandler(void)
{
    rt_interrupt_enter();
    if (RESET != EXTI_GetIntStatus(EXTI_Line5))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_5);
    }
    if (RESET != EXTI_GetIntStatus(EXTI_Line6))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_6);
    }
    if (RESET != EXTI_GetIntStatus(EXTI_Line7))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_7);
    }
    if (RESET != EXTI_GetIntStatus(EXTI_Line8))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_8);
    }
    if (RESET != EXTI_GetIntStatus(EXTI_Line9))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_9);
    }
    rt_interrupt_leave();
}

void EXTI15_10_IRQHandler(void)
{
    rt_interrupt_enter();
    if (RESET != EXTI_GetIntStatus(EXTI_Line10))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_10);
    }
    if (RESET != EXTI_GetIntStatus(EXTI_Line11))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_11);
    }
    if (RESET != EXTI_GetIntStatus(EXTI_Line12))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_12);
    }
    if (RESET != EXTI_GetIntStatus(EXTI_Line13))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_13);
    }
    if (RESET != EXTI_GetIntStatus(EXTI_Line14))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_14);
    }
    if (RESET != EXTI_GetIntStatus(EXTI_Line15))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_15);
    }
    rt_interrupt_leave();
}

int rt_hw_pin_init(void)
{

#ifdef GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA, ENABLE);
#endif
#ifdef GPIOB
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOB, ENABLE);
#endif
#ifdef GPIOC
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOC, ENABLE);
#endif
#ifdef GPIOD
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOD, ENABLE);
#endif
#ifdef GPIOE
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOE, ENABLE);
#endif
#ifdef GPIOF
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOF, ENABLE);
#endif
#ifdef GPIOG
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOG, ENABLE);
#endif

    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_AFIO, ENABLE);

    return rt_device_pin_register("pin", &_at32_pin_ops, RT_NULL);
}

INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* RT_USING_PIN */
