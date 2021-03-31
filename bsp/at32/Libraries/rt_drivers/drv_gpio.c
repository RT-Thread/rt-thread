/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-01-07     shelton           first version
 */

#include <board.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN

static const struct pin_index pins[] =
{
#if defined(GPIOA)
    __AT32_PIN(0 ,  A, 0 ),
    __AT32_PIN(1 ,  A, 1 ),
    __AT32_PIN(2 ,  A, 2 ),
    __AT32_PIN(3 ,  A, 3 ),
    __AT32_PIN(4 ,  A, 4 ),
    __AT32_PIN(5 ,  A, 5 ),
    __AT32_PIN(6 ,  A, 6 ),
    __AT32_PIN(7 ,  A, 7 ),
    __AT32_PIN(8 ,  A, 8 ),
    __AT32_PIN(9 ,  A, 9 ),
    __AT32_PIN(10,  A, 10),
    __AT32_PIN(11,  A, 11),
    __AT32_PIN(12,  A, 12),
    __AT32_PIN(13,  A, 13),
    __AT32_PIN(14,  A, 14),
    __AT32_PIN(15,  A, 15),
#if defined(GPIOB)
    __AT32_PIN(16,  B, 0),
    __AT32_PIN(17,  B, 1),
    __AT32_PIN(18,  B, 2),
    __AT32_PIN(19,  B, 3),
    __AT32_PIN(20,  B, 4),
    __AT32_PIN(21,  B, 5),
    __AT32_PIN(22,  B, 6),
    __AT32_PIN(23,  B, 7),
    __AT32_PIN(24,  B, 8),
    __AT32_PIN(25,  B, 9),
    __AT32_PIN(26,  B, 10),
    __AT32_PIN(27,  B, 11),
    __AT32_PIN(28,  B, 12),
    __AT32_PIN(29,  B, 13),
    __AT32_PIN(30,  B, 14),
    __AT32_PIN(31,  B, 15),
#if defined(GPIOC)
    __AT32_PIN(32,  C, 0),
    __AT32_PIN(33,  C, 1),
    __AT32_PIN(34,  C, 2),
    __AT32_PIN(35,  C, 3),
    __AT32_PIN(36,  C, 4),
    __AT32_PIN(37,  C, 5),
    __AT32_PIN(38,  C, 6),
    __AT32_PIN(39,  C, 7),
    __AT32_PIN(40,  C, 8),
    __AT32_PIN(41,  C, 9),
    __AT32_PIN(42,  C, 10),
    __AT32_PIN(43,  C, 11),
    __AT32_PIN(44,  C, 12),
    __AT32_PIN(45,  C, 13),
    __AT32_PIN(46,  C, 14),
    __AT32_PIN(47,  C, 15),
#if defined(GPIOD)
    __AT32_PIN(48,  D, 0),
    __AT32_PIN(49,  D, 1),
    __AT32_PIN(50,  D, 2),
    __AT32_PIN(51,  D, 3),
    __AT32_PIN(52,  D, 4),
    __AT32_PIN(53,  D, 5),
    __AT32_PIN(54,  D, 6),
    __AT32_PIN(55,  D, 7),
    __AT32_PIN(56,  D, 8),
    __AT32_PIN(57,  D, 9),
    __AT32_PIN(58,  D, 10),
    __AT32_PIN(59,  D, 11),
    __AT32_PIN(60,  D, 12),
    __AT32_PIN(61,  D, 13),
    __AT32_PIN(62,  D, 14),
    __AT32_PIN(63,  D, 15),
#if defined(GPIOE)
    __AT32_PIN(64,  E, 0),
    __AT32_PIN(65,  E, 1),
    __AT32_PIN(66,  E, 2),
    __AT32_PIN(67,  E, 3),
    __AT32_PIN(68,  E, 4),
    __AT32_PIN(69,  E, 5),
    __AT32_PIN(70,  E, 6),
    __AT32_PIN(71,  E, 7),
    __AT32_PIN(72,  E, 8),
    __AT32_PIN(73,  E, 9),
    __AT32_PIN(74,  E, 10),
    __AT32_PIN(75,  E, 11),
    __AT32_PIN(76,  E, 12),
    __AT32_PIN(77,  E, 13),
    __AT32_PIN(78,  E, 14),
    __AT32_PIN(79,  E, 15),
#if defined(GPIOF)
    __AT32_PIN(80,  F, 0),
    __AT32_PIN(81,  F, 1),
    __AT32_PIN(82,  F, 2),
    __AT32_PIN(83,  F, 3),
    __AT32_PIN(84,  F, 4),
    __AT32_PIN(85,  F, 5),
    __AT32_PIN(86,  F, 6),
    __AT32_PIN(87,  F, 7),
    __AT32_PIN(88,  F, 8),
    __AT32_PIN(89,  F, 9),
    __AT32_PIN(90,  F, 10),
    __AT32_PIN(91,  F, 11),
    __AT32_PIN(92,  F, 12),
    __AT32_PIN(93,  F, 13),
    __AT32_PIN(94,  F, 14),
    __AT32_PIN(95,  F, 15),
#if defined(GPIOG)
    __AT32_PIN(96,  G, 0),
    __AT32_PIN(97,  G, 1),
    __AT32_PIN(98,  G, 2),
    __AT32_PIN(99,  G, 3),
    __AT32_PIN(100, G, 4),
    __AT32_PIN(101, G, 5),
    __AT32_PIN(102, G, 6),
    __AT32_PIN(103, G, 7),
    __AT32_PIN(104, G, 8),
    __AT32_PIN(105, G, 9),
    __AT32_PIN(106, G, 10),
    __AT32_PIN(107, G, 11),
    __AT32_PIN(108, G, 12),
    __AT32_PIN(109, G, 13),
    __AT32_PIN(110, G, 14),
    __AT32_PIN(111, G, 15),
#endif /* defined(GPIOG) */
#endif /* defined(GPIOF) */
#endif /* defined(GPIOE) */
#endif /* defined(GPIOD) */
#endif /* defined(GPIOC) */
#endif /* defined(GPIOB) */
#endif /* defined(GPIOA) */
};

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
static uint32_t pin_irq_enable_mask=0;

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

static void at32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    GPIO_WriteBit(index->gpio, index->pin, (BitState)value);
}

static int at32_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    const struct pin_index *index;

    value = PIN_LOW;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return value;
    }

    value = GPIO_ReadInputDataBit(index->gpio, index->pin);

    return value;
}

static void at32_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    const struct pin_index *index;
    GPIO_InitType GPIO_InitStruct;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pins = index->pin;
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

    GPIO_Init(index->gpio, &GPIO_InitStruct);
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
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_ENOSYS;
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
        return RT_EBUSY;
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
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_ENOSYS;
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
    const struct pin_index *index;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(index->pin);
        if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
        {
            return RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return RT_ENOSYS;
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
        GPIO_Init(index->gpio, &GPIO_InitStruct);
        GPIO_EXTILineConfig(index->portsource, index->pinsource);
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
        irqmap = get_pin_irq_map(index->pin);
        if (irqmap == RT_NULL)
        {
            return RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        pin_irq_enable_mask &= ~irqmap->pinbit;

        NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 5;
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

        if (( irqmap->pinbit>=GPIO_Pins_5 )&&( irqmap->pinbit<=GPIO_Pins_9 ))
        {
            if(!(pin_irq_enable_mask&(GPIO_Pins_5|GPIO_Pins_6|GPIO_Pins_7|GPIO_Pins_8|GPIO_Pins_9)))
            {
                NVIC_InitStruct.NVIC_IRQChannel = irqmap->irqno;
            }
        }
        else if (( irqmap->pinbit>=GPIO_Pins_10 )&&( irqmap->pinbit<=GPIO_Pins_15 ))
        {
            if(!(pin_irq_enable_mask&(GPIO_Pins_10|GPIO_Pins_11|GPIO_Pins_12|GPIO_Pins_13|GPIO_Pins_14|GPIO_Pins_15)))
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
    if(RESET != EXTI_GetIntStatus(EXTI_Line5))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_5);
    }
    if(RESET != EXTI_GetIntStatus(EXTI_Line6))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_6);
    }
    if(RESET != EXTI_GetIntStatus(EXTI_Line7))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_7);
    }
    if(RESET != EXTI_GetIntStatus(EXTI_Line8))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_8);
    }
    if(RESET != EXTI_GetIntStatus(EXTI_Line9))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_9);
    }
    rt_interrupt_leave();
}

void EXTI15_10_IRQHandler(void)
{
    rt_interrupt_enter();
    if(RESET != EXTI_GetIntStatus(EXTI_Line10))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_10);
    }
    if(RESET != EXTI_GetIntStatus(EXTI_Line11))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_11);
    }
    if(RESET != EXTI_GetIntStatus(EXTI_Line12))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_12);
    }
    if(RESET != EXTI_GetIntStatus(EXTI_Line13))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_13);
    }
    if(RESET != EXTI_GetIntStatus(EXTI_Line14))
    {
        GPIO_EXTI_IRQHandler(GPIO_Pins_14);
    }
    if(RESET != EXTI_GetIntStatus(EXTI_Line15))
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
