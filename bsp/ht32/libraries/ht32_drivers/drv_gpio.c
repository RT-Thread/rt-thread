/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-08     QT-one       first version
 */

#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define __HT32_PIN(index, gpio, pin)            \
    {                                           \
        index, HT_GPIO##gpio, GPIO_PIN_##pin    \
    }

struct pin_index
{
    int index;
    HT_GPIO_TypeDef *gpio;
    uint32_t pin;
};

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};

static const struct pin_index pins[] =
{
#if defined(HT_GPIOA)
    __HT32_PIN(0,  A, 0),
    __HT32_PIN(1,  A, 1),
    __HT32_PIN(2,  A, 2),
    __HT32_PIN(3,  A, 3),
    __HT32_PIN(4,  A, 4),
    __HT32_PIN(5,  A, 5),
    __HT32_PIN(6,  A, 6),
    __HT32_PIN(7,  A, 7),
    __HT32_PIN(8,  A, 8),
    __HT32_PIN(9,  A, 9),
    __HT32_PIN(10, A, 10),
    __HT32_PIN(11, A, 11),
    __HT32_PIN(12, A, 12),
    __HT32_PIN(13, A, 13),
    __HT32_PIN(14, A, 14),
    __HT32_PIN(15, A, 15),
#if defined(HT_GPIOB)
    __HT32_PIN(16,  B, 0),
    __HT32_PIN(17,  B, 1),
    __HT32_PIN(18,  B, 2),
    __HT32_PIN(19,  B, 3),
    __HT32_PIN(20,  B, 4),
    __HT32_PIN(21,  B, 5),
    __HT32_PIN(22,  B, 6),
    __HT32_PIN(23,  B, 7),
    __HT32_PIN(24,  B, 8),
    __HT32_PIN(25,  B, 9),
    __HT32_PIN(26,  B, 10),
    __HT32_PIN(27,  B, 11),
    __HT32_PIN(28,  B, 12),
    __HT32_PIN(29,  B, 13),
    __HT32_PIN(30,  B, 14),
    __HT32_PIN(31,  B, 15),
#if defined(HT_GPIOC)
    __HT32_PIN(32,  C, 0),
    __HT32_PIN(33,  C, 1),
    __HT32_PIN(34,  C, 2),
    __HT32_PIN(35,  C, 3),
    __HT32_PIN(36,  C, 4),
    __HT32_PIN(37,  C, 5),
    __HT32_PIN(38,  C, 6),
    __HT32_PIN(39,  C, 7),
    __HT32_PIN(40,  C, 8),
    __HT32_PIN(41,  C, 9),
    __HT32_PIN(42,  C, 10),
    __HT32_PIN(43,  C, 11),
    __HT32_PIN(44,  C, 12),
    __HT32_PIN(45,  C, 13),
    __HT32_PIN(46,  C, 14),
    __HT32_PIN(47,  C, 15),
#if defined(HT_GPIOD)
    __HT32_PIN(48,  D, 0),
    __HT32_PIN(49,  D, 1),
    __HT32_PIN(50,  D, 2),
    __HT32_PIN(51,  D, 3),
    __HT32_PIN(52,  D, 4),
    __HT32_PIN(53,  D, 5),
    __HT32_PIN(54,  D, 6),
    __HT32_PIN(55,  D, 7),
    __HT32_PIN(56,  D, 8),
    __HT32_PIN(57,  D, 9),
    __HT32_PIN(58,  D, 10),
    __HT32_PIN(59,  D, 11),
    __HT32_PIN(60,  D, 12),
    __HT32_PIN(61,  D, 13),
    __HT32_PIN(62,  D, 14),
    __HT32_PIN(63,  D, 15),
#if defined(HT_GPIOE)
    __HT32_PIN(64,  E, 0),
    __HT32_PIN(65,  E, 1),
    __HT32_PIN(66,  E, 2),
    __HT32_PIN(67,  E, 3),
    __HT32_PIN(68,  E, 4),
    __HT32_PIN(69,  E, 5),
    __HT32_PIN(70,  E, 6),
    __HT32_PIN(71,  E, 7),
    __HT32_PIN(72,  E, 8),
    __HT32_PIN(73,  E, 9),
    __HT32_PIN(74,  E, 10),
    __HT32_PIN(75,  E, 11),
    __HT32_PIN(76,  E, 12),
    __HT32_PIN(77,  E, 13),
    __HT32_PIN(78,  E, 14),
    __HT32_PIN(79,  E, 15),
#if defined(HT_GPIOF)
    __HT32_PIN(80,  F, 0),
    __HT32_PIN(81,  F, 1),
    __HT32_PIN(82,  F, 2),
    __HT32_PIN(83,  F, 3),
    __HT32_PIN(84,  F, 4),
    __HT32_PIN(85,  F, 5),
    __HT32_PIN(86,  F, 6),
    __HT32_PIN(87,  F, 7),
    __HT32_PIN(88,  F, 8),
    __HT32_PIN(89,  F, 9),
    __HT32_PIN(90,  F, 10),
    __HT32_PIN(91,  F, 11),
    __HT32_PIN(92,  F, 12),
    __HT32_PIN(93,  F, 13),
    __HT32_PIN(94,  F, 14),
    __HT32_PIN(95,  F, 15),
#endif /* defined(HT_GPIOF) */
#endif /* defined(HT_GPIOE) */
#endif /* defined(HT_GPIOD) */
#endif /* defined(HT_GPIOC) */
#endif /* defined(HT_GPIOB) */
#endif /* defined(HT_GPIOA) */
};

static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_PIN_0, EXTI0_IRQn},
    {GPIO_PIN_1, EXTI1_IRQn},
    {GPIO_PIN_2, EXTI2_IRQn},
    {GPIO_PIN_3, EXTI3_IRQn},
    {GPIO_PIN_4, EXTI4_IRQn},
    {GPIO_PIN_5, EXTI5_IRQn},
    {GPIO_PIN_6, EXTI6_IRQn},
    {GPIO_PIN_7, EXTI7_IRQn},
    {GPIO_PIN_8, EXTI8_IRQn},
    {GPIO_PIN_9, EXTI9_IRQn},
    {GPIO_PIN_10, EXTI10_IRQn},
    {GPIO_PIN_11, EXTI11_IRQn},
    {GPIO_PIN_12, EXTI12_IRQn},
    {GPIO_PIN_13, EXTI13_IRQn},
    {GPIO_PIN_14, EXTI14_IRQn},
    {GPIO_PIN_15, EXTI15_IRQn},
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

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])

static const struct pin_index *get_pin(rt_uint8_t pin)
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
}

static void ht32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    const struct pin_index *index;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    if ((index->gpio) == HT_GPIOA)
        CKCUClock.Bit.PA         = 1;
    else if ((index->gpio) == HT_GPIOB)
        CKCUClock.Bit.PB         = 1;
#if defined(HT_GPIOC)
    else if ((index->gpio) == HT_GPIOC)
        CKCUClock.Bit.PC         = 1;
#endif
#if defined(HT_GPIOD)
    else if ((index->gpio) == HT_GPIOD)
        CKCUClock.Bit.PD         = 1;
#endif
#if defined(HT_GPIOE)
    else if ((index->gpio) == HT_GPIOE)
        CKCUClock.Bit.PE         = 1;
#endif
#if defined(HT_GPIOF)
    else if ((index->gpio) == HT_GPIOF)
        CKCUClock.Bit.PF         = 1;
#endif
    CKCUClock.Bit.AFIO           = 1;
    CKCUClock.Bit.BKP            = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    if ((index->gpio) == HT_GPIOA)
        AFIO_GPxConfig(GPIO_PA, index->pin, AFIO_MODE_1);
    else if ((index->gpio) == HT_GPIOB)
        AFIO_GPxConfig(GPIO_PB, index->pin, AFIO_MODE_1);
#if defined(HT_GPIOC)
    else if ((index->gpio) == HT_GPIOC)
        AFIO_GPxConfig(GPIO_PC, index->pin, AFIO_MODE_1);
#endif
#if defined(HT_GPIOD)
    else if ((index->gpio) == HT_GPIOD)
        AFIO_GPxConfig(GPIO_PD, index->pin, AFIO_MODE_1);
#endif
#if defined(HT_GPIOE)
    else if ((index->gpio) == HT_GPIOE)
        AFIO_GPxConfig(GPIO_PE, index->pin, AFIO_MODE_1);
#endif
#if defined(HT_GPIOF)
    else if ((index->gpio) == HT_GPIOF)
        AFIO_GPxConfig(GPIO_PF, index->pin, AFIO_MODE_1);
#endif

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        /* output setting */
        GPIO_DirectionConfig(index->gpio, index->pin, GPIO_DIR_OUT);
        GPIO_PullResistorConfig(index->gpio, index->pin, GPIO_PR_DISABLE);
        break;
    case PIN_MODE_OUTPUT_OD:
        /* output setting: od. */
        GPIO_DirectionConfig(index->gpio, index->pin, GPIO_DIR_OUT);
        GPIO_PullResistorConfig(index->gpio, index->pin, GPIO_PR_DISABLE);
        break;
    case PIN_MODE_INPUT:
        /* input setting: not pull. */
        GPIO_DirectionConfig(index->gpio, index->pin, GPIO_DIR_IN);
        GPIO_PullResistorConfig(index->gpio, index->pin, GPIO_PR_DISABLE);
        GPIO_InputConfig(index->gpio, index->pin, ENABLE);
        break;
    case PIN_MODE_INPUT_PULLUP:
        /* input setting: pull up. */
        GPIO_DirectionConfig(index->gpio, index->pin, GPIO_DIR_IN);
        GPIO_PullResistorConfig(index->gpio, index->pin, GPIO_PR_UP);
        GPIO_InputConfig(index->gpio, index->pin, ENABLE);
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        /* input setting: pull down. */
        GPIO_DirectionConfig(index->gpio, index->pin, GPIO_DIR_IN);
        GPIO_PullResistorConfig(index->gpio, index->pin, GPIO_PR_DOWN);
        GPIO_InputConfig(index->gpio, index->pin, ENABLE);
        break;
    default:
        break;
    }
}

static void ht32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    if (value == PIN_LOW)
    {
        GPIO_ClearOutBits(index->gpio, index->pin);
    }
    else
    {
        GPIO_SetOutBits(index->gpio, index->pin);
    }
}

static rt_ssize_t ht32_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    const struct pin_index *index;
    value = PIN_LOW;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return value;
    }
    value = GPIO_ReadInBit(index->gpio, index->pin);
    return value;
}

rt_inline rt_int32_t bit2bitno(rt_uint32_t bit)
{
    rt_uint8_t i;
    for (i = 0; i < 32; i++)
    {
        if ((0x01 << i) == bit)
        {
            return i;
        }
    }
    return -1;
}

rt_inline const struct pin_irq_map *get_pin_irq_map(rt_uint32_t pinbit)
{
    rt_int32_t mapindex = bit2bitno(pinbit);
    if (mapindex < 0 || mapindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
}

static rt_err_t ht32_pin_attach_irq(struct rt_device *device,
                                    rt_base_t pin,
                                    rt_uint8_t mode,
                                    void (*hdr)(void *args),
                                    void *args)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t hdr_index = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ERROR;
    }

    hdr_index = bit2bitno(index->pin);

    if (hdr_index < 0 || hdr_index >= ITEM_NUM(pin_irq_map))
    {
        return RT_ERROR;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[hdr_index].pin == pin &&
            pin_irq_hdr_tab[hdr_index].hdr == hdr &&
            pin_irq_hdr_tab[hdr_index].mode == mode &&
            pin_irq_hdr_tab[hdr_index].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (pin_irq_hdr_tab[hdr_index].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_ERROR;
    }
    pin_irq_hdr_tab[hdr_index].pin = pin;
    pin_irq_hdr_tab[hdr_index].hdr = hdr;
    pin_irq_hdr_tab[hdr_index].mode = mode;
    pin_irq_hdr_tab[hdr_index].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t ht32_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t hdr_index = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ERROR;
    }

    hdr_index = bit2bitno(index->pin);
    if (hdr_index < 0 || hdr_index >= ITEM_NUM(pin_irq_map))
    {
        return RT_ERROR;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[hdr_index].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[hdr_index].pin = -1;
    pin_irq_hdr_tab[hdr_index].hdr = RT_NULL;
    pin_irq_hdr_tab[hdr_index].mode = 0;
    pin_irq_hdr_tab[hdr_index].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t ht32_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    const struct pin_index *index;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t hdr_index = -1;
    EXTI_InitTypeDef EXTI_InitStruct;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ERROR;
    }
    if (enabled == PIN_IRQ_ENABLE)
    {
        hdr_index = bit2bitno(index->pin);
        if (hdr_index < 0 || hdr_index >= ITEM_NUM(pin_irq_map))
        {
            return RT_ERROR;
        }

        level = rt_hw_interrupt_disable();

        if (pin_irq_hdr_tab[hdr_index].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return RT_ERROR;
        }

        irqmap = &pin_irq_map[hdr_index];

        CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
        CKCUClock.Bit.AFIO                      = 1;
        CKCUClock.Bit.EXTI                      = 1;

        if ((index->gpio) == HT_GPIOA)
            CKCUClock.Bit.PA         = 1;
        else if ((index->gpio) == HT_GPIOB)
            CKCUClock.Bit.PB         = 1;
#if defined(HT_GPIOC)
        else if ((index->gpio) == HT_GPIOC)
            CKCUClock.Bit.PC         = 1;
#endif
#if defined(HT_GPIOD)
        else if ((index->gpio) == HT_GPIOD)
            CKCUClock.Bit.PD         = 1;
#endif
#if defined(HT_GPIOE)
        else if ((index->gpio) == HT_GPIOE)
            CKCUClock.Bit.PE         = 1;
#endif
#if defined(HT_GPIOF)
        else if ((index->gpio) == HT_GPIOF)
            CKCUClock.Bit.PF         = 1;
#endif

        CKCU_PeripClockConfig(CKCUClock, ENABLE);

        if ((index->gpio) == HT_GPIOA)
        {
            AFIO_GPxConfig(GPIO_PA, index->pin, AFIO_MODE_1);
            GPIO_InputConfig(HT_GPIOA, index->pin, ENABLE);
            AFIO_EXTISourceConfig(hdr_index, AFIO_ESS_PA);
        }
        else if ((index->gpio) == HT_GPIOB)
        {
            AFIO_GPxConfig(GPIO_PB, index->pin, AFIO_MODE_1);
            GPIO_InputConfig(HT_GPIOB, index->pin, ENABLE);
            AFIO_EXTISourceConfig(hdr_index, AFIO_ESS_PB);
        }
#if defined(HT_GPIOC)
        else if ((index->gpio) == HT_GPIOC)
        {
            AFIO_GPxConfig(GPIO_PC, index->pin, AFIO_MODE_1);
            GPIO_InputConfig(HT_GPIOC, index->pin, ENABLE);
            AFIO_EXTISourceConfig(hdr_index, AFIO_ESS_PC);
        }
#endif
#if defined(HT_GPIOD)
        else if ((index->gpio) == HT_GPIOD)
        {
            AFIO_GPxConfig(GPIO_PD, index->pin, AFIO_MODE_1);
            GPIO_InputConfig(HT_GPIOD, index->pin, ENABLE);
            AFIO_EXTISourceConfig(hdr_index, AFIO_ESS_PD);
        }
#endif
#if defined(HT_GPIOE)
        else if ((index->gpio) == HT_GPIOE)
        {
            AFIO_GPxConfig(GPIO_PE, index->pin, AFIO_MODE_1);
            GPIO_InputConfig(HT_GPIOE, index->pin, ENABLE);
            AFIO_EXTISourceConfig(hdr_index, AFIO_ESS_PE);
        }
#endif
#if defined(HT_GPIOF)
        else if ((index->gpio) == HT_GPIOF)
        {
            AFIO_GPxConfig(GPIO_PF, index->pin, AFIO_MODE_1);
            GPIO_InputConfig(HT_GPIOF, index->pin, ENABLE);
            AFIO_EXTISourceConfig(hdr_index, AFIO_ESS_PF);
        }
#endif

        switch (pin_irq_hdr_tab[hdr_index].mode)
        {
        case PIN_IRQ_MODE_RISING:
            GPIO_PullResistorConfig(index->gpio, index->pin, GPIO_PR_DOWN);
            EXTI_InitStruct.EXTI_IntType = EXTI_POSITIVE_EDGE;
            break;
        case PIN_IRQ_MODE_FALLING:
            GPIO_PullResistorConfig(index->gpio, index->pin, GPIO_PR_UP);
            EXTI_InitStruct.EXTI_IntType = EXTI_NEGATIVE_EDGE;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            GPIO_PullResistorConfig(index->gpio, index->pin, GPIO_PR_DISABLE);
            EXTI_InitStruct.EXTI_IntType = EXTI_BOTH_EDGE;
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            GPIO_PullResistorConfig(index->gpio, index->pin, GPIO_PR_DOWN);
            EXTI_InitStruct.EXTI_IntType = EXTI_HIGH_LEVEL;
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            GPIO_PullResistorConfig(index->gpio, index->pin, GPIO_PR_UP);
            EXTI_InitStruct.EXTI_IntType = EXTI_LOW_LEVEL;
            break;
        default:
            rt_hw_interrupt_enable(level);
            return RT_ERROR;
        }

        EXTI_InitStruct.EXTI_Channel = hdr_index;

        EXTI_InitStruct.EXTI_Debounce = EXTI_DEBOUNCE_DISABLE;
        EXTI_InitStruct.EXTI_DebounceCnt = 0;
        EXTI_Init(&EXTI_InitStruct);

        EXTI_IntConfig(hdr_index, ENABLE);

        NVIC_EnableIRQ((irqmap->irqno));
        rt_hw_interrupt_enable(level);
    }

    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(index->pin);
        if (irqmap == RT_NULL)
        {
            return RT_ERROR;
        }
        if ((irqmap->irqno) == EXTI0_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_0, DISABLE);
        else if ((irqmap->irqno) == EXTI1_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_1, DISABLE);
        else if ((irqmap->irqno) == EXTI2_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_2, DISABLE);
        else if ((irqmap->irqno) == EXTI3_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_3, DISABLE);
        else if ((irqmap->irqno) == EXTI4_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_4, DISABLE);
        else if ((irqmap->irqno) == EXTI5_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_5, DISABLE);
        else if ((irqmap->irqno) == EXTI6_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_6, DISABLE);
        else if ((irqmap->irqno) == EXTI7_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_7, DISABLE);
        else if ((irqmap->irqno) == EXTI8_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_8, DISABLE);
        else if ((irqmap->irqno) == EXTI9_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_9, DISABLE);
        else if ((irqmap->irqno) == EXTI10_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_10, DISABLE);
        else if ((irqmap->irqno) == EXTI11_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_11, DISABLE);
        else if ((irqmap->irqno) == EXTI12_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_12, DISABLE);
        else if ((irqmap->irqno) == EXTI13_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_13, DISABLE);
        else if ((irqmap->irqno) == EXTI14_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_14, DISABLE);
        else if ((irqmap->irqno) == EXTI15_IRQn)
            EXTI_IntConfig(EXTI_CHANNEL_15, DISABLE);
    }
    else
    {
        return RT_ERROR;
    }
    return RT_EOK;
}

const static struct rt_pin_ops _ht32_pin_ops =
{
    .pin_mode = ht32_pin_mode,
    .pin_write = ht32_pin_write,
    .pin_read = ht32_pin_read,
    .pin_attach_irq = ht32_pin_attach_irq,
    .pin_detach_irq = ht32_pin_detach_irq,
    .pin_irq_enable = ht32_pin_irq_enable,
    .pin_get = NULL,
};

int rt_hw_pin_init(void)
{
    int result;

    result = rt_device_pin_register("pin", &_ht32_pin_ops, RT_NULL);

    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}
#ifdef SOC_SERIES_HT32F5
void EXTI0_1_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_0, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_0);
        pin_irq_hdr(0);
    }
    else if (EXTI_GetEdgeStatus(EXTI_CHANNEL_1, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_1);
        pin_irq_hdr(1);
    }
    rt_interrupt_leave();
}

void EXTI2_3_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_2, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_2);
        pin_irq_hdr(2);
    }
    else if (EXTI_GetEdgeStatus(EXTI_CHANNEL_3, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_3);
        pin_irq_hdr(3);
    }
    rt_interrupt_leave();
}

void EXTI4_15_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_4, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_4);
        pin_irq_hdr(4);
    }
    else if (EXTI_GetEdgeStatus(EXTI_CHANNEL_5, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_5);
        pin_irq_hdr(5);
    }
    else if (EXTI_GetEdgeStatus(EXTI_CHANNEL_6, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_6);
        pin_irq_hdr(6);
    }
    else if (EXTI_GetEdgeStatus(EXTI_CHANNEL_7, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_7);
        pin_irq_hdr(7);
    }
    else if (EXTI_GetEdgeStatus(EXTI_CHANNEL_8, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_8);
        pin_irq_hdr(8);
    }
    else if (EXTI_GetEdgeStatus(EXTI_CHANNEL_9, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_9);
        pin_irq_hdr(9);
    }
    else if (EXTI_GetEdgeStatus(EXTI_CHANNEL_10, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_10);
        pin_irq_hdr(10);
    }
    else if (EXTI_GetEdgeStatus(EXTI_CHANNEL_11, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_11);
        pin_irq_hdr(11);
    }
    else if (EXTI_GetEdgeStatus(EXTI_CHANNEL_12, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_12);
        pin_irq_hdr(12);
    }
    else if (EXTI_GetEdgeStatus(EXTI_CHANNEL_13, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_13);
        pin_irq_hdr(13);
    }
    else if (EXTI_GetEdgeStatus(EXTI_CHANNEL_14, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_14);
        pin_irq_hdr(14);
    }
    else if (EXTI_GetEdgeStatus(EXTI_CHANNEL_15, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_15);
        pin_irq_hdr(15);
    }
    rt_interrupt_leave();
}
#endif

#ifdef SOC_SERIES_HT32F1
void EXTI0_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_0, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_0);
        pin_irq_hdr(0);
    }
    rt_interrupt_leave();
}
void EXTI1_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_1, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_1);
        pin_irq_hdr(1);
    }
    rt_interrupt_leave();
}
void EXTI2_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_2, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_2);
        pin_irq_hdr(2);
    }
    rt_interrupt_leave();
}
void EXTI3_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_3, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_3);
        pin_irq_hdr(3);
    }
    rt_interrupt_leave();
}
void EXTI4_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_4, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_4);
        pin_irq_hdr(4);
    }
    rt_interrupt_leave();
}
void EXTI5_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_5, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_5);
        pin_irq_hdr(5);
    }
    rt_interrupt_leave();
}
void EXTI6_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_6, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_6);
        pin_irq_hdr(6);
    }
    rt_interrupt_leave();
}
void EXTI7_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_7, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_7);
        pin_irq_hdr(7);
    }
    rt_interrupt_leave();
}
void EXTI8_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_8, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_8);
        pin_irq_hdr(8);
    }
    rt_interrupt_leave();
}
void EXTI9_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_9, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_9);
        pin_irq_hdr(9);
    }
    rt_interrupt_leave();
}
void EXTI10_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_10, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_10);
        pin_irq_hdr(10);
    }
    rt_interrupt_leave();
}
void EXTI11_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_11, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_11);
        pin_irq_hdr(11);
    }
    rt_interrupt_leave();
}
void EXTI12_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_12, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_12);
        pin_irq_hdr(12);
    }
    rt_interrupt_leave();
}
void EXTI13_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_13, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_13);
        pin_irq_hdr(13);
    }
    rt_interrupt_leave();
}
void EXTI14_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_14, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_14);
        pin_irq_hdr(14);
    }
    rt_interrupt_leave();
}
void EXTI15_IRQHandler(void)
{
    rt_interrupt_enter();
    if (EXTI_GetEdgeStatus(EXTI_CHANNEL_15, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(EXTI_CHANNEL_15);
        pin_irq_hdr(15);
    }
    rt_interrupt_leave();
}
#endif

#endif
