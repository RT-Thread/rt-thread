/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-02     spaceman           first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <rthw.h>
#include <drv_gpio.h>

#ifdef RT_USING_PIN

#define TKM32_PIN(index, rcc, gpio, gpio_index) { index, RCC_##rcc##Periph_GPIO##gpio, GPIO##gpio, GPIO_Pin_##gpio_index, \
                                                    ((rt_base_t)__TKM32_PORT(gpio)-(rt_base_t)GPIOA_BASE)/(0x0400UL), gpio_index}
#define TKM32_PIN_DEFAULT {-1, 0, 0, 0, 0, 0}
/* TKM32 GPIO driver */
struct pin_index
{
    int index;
    uint32_t rcc;
    GPIO_TypeDef *gpio;
    uint32_t pin;
    uint8_t port_source;
    uint8_t pin_source;
};
static const struct pin_index tkm32_pin_map[] =
{
    TKM32_PIN_DEFAULT,
    TKM32_PIN(0, AHB, A, 0),
    TKM32_PIN(1, AHB, A, 1),
    TKM32_PIN(2, AHB, A, 2),
    TKM32_PIN(3, AHB, A, 3),
    TKM32_PIN(4, AHB, A, 4),
    TKM32_PIN(5, AHB, A, 5),
    TKM32_PIN(6, AHB, A, 6),
    TKM32_PIN(7, AHB, A, 7),
    TKM32_PIN(8, AHB, A, 8),
    TKM32_PIN(9, AHB, A, 9),
    TKM32_PIN(10, AHB, A, 10),
    TKM32_PIN(11, AHB, A, 11),
    TKM32_PIN(12, AHB, A, 12),
    TKM32_PIN(13, AHB, A, 13),
    TKM32_PIN(14, AHB, A, 14),
    TKM32_PIN(15, AHB, A, 15),
    TKM32_PIN(16, AHB, B, 0),
    TKM32_PIN(17, AHB, B, 1),
    TKM32_PIN(18, AHB, B, 2),
    TKM32_PIN(19, AHB, B, 3),
    TKM32_PIN(20, AHB, B, 4),
    TKM32_PIN(21, AHB, B, 5),
    TKM32_PIN(22, AHB, B, 6),
    TKM32_PIN(23, AHB, B, 7),
    TKM32_PIN(24, AHB, B, 8),
    TKM32_PIN(25, AHB, B, 9),
    TKM32_PIN(26, AHB, B, 10),
    TKM32_PIN(27, AHB, B, 11),
    TKM32_PIN(28, AHB, B, 12),
    TKM32_PIN(29, AHB, B, 13),
    TKM32_PIN(30, AHB, B, 14),
    TKM32_PIN(31, AHB, B, 15),
    TKM32_PIN(32, AHB, C, 0),
    TKM32_PIN(33, AHB, C, 1),
    TKM32_PIN(34, AHB, C, 2),
    TKM32_PIN(35, AHB, C, 3),
    TKM32_PIN(36, AHB, C, 4),
    TKM32_PIN(37, AHB, C, 5),
    TKM32_PIN(38, AHB, C, 6),
    TKM32_PIN(39, AHB, C, 7),
    TKM32_PIN(40, AHB, C, 8),
    TKM32_PIN(41, AHB, C, 9),
    TKM32_PIN(42, AHB, C, 10),
    TKM32_PIN(43, AHB, C, 11),
    TKM32_PIN(44, AHB, C, 12),
    TKM32_PIN(45, AHB, C, 13),
    TKM32_PIN(46, AHB, C, 14),
    TKM32_PIN(47, AHB, C, 15),
    TKM32_PIN(48, AHB, D, 0),
    TKM32_PIN(49, AHB, D, 1),
    TKM32_PIN(50, AHB, D, 2),
    TKM32_PIN(51, AHB, D, 3),
    TKM32_PIN(52, AHB, D, 4),
    TKM32_PIN(53, AHB, D, 5),
    TKM32_PIN(54, AHB, D, 6),
    TKM32_PIN(55, AHB, D, 7),
    TKM32_PIN(56, AHB, D, 8),
    TKM32_PIN(57, AHB, D, 9),
    TKM32_PIN(58, AHB, D, 10),
    TKM32_PIN(59, AHB, D, 11),
    TKM32_PIN(60, AHB, D, 12),
    TKM32_PIN(61, AHB, D, 13),
    TKM32_PIN(62, AHB, D, 14),
    TKM32_PIN(63, AHB, D, 15),
    TKM32_PIN(64, AHB, E, 0),
    TKM32_PIN(65, AHB, E, 1),
    TKM32_PIN(66, AHB, E, 2),
    TKM32_PIN(67, AHB, E, 3),
    TKM32_PIN(68, AHB, E, 4),
    TKM32_PIN(69, AHB, E, 5),
    TKM32_PIN(70, AHB, E, 6),
    TKM32_PIN(71, AHB, E, 7),
    TKM32_PIN(72, AHB, E, 8),
    TKM32_PIN(73, AHB, E, 9),
    TKM32_PIN(74, AHB, E, 10),
    TKM32_PIN(75, AHB, E, 11),
    TKM32_PIN(76, AHB, E, 12),
    TKM32_PIN(77, AHB, E, 13),
    TKM32_PIN(78, AHB, E, 14),
    TKM32_PIN(79, AHB, E, 15),
    TKM32_PIN(80, AHB, E, 16),
    TKM32_PIN(81, AHB, E, 17),
    TKM32_PIN(82, AHB, E, 18),
    TKM32_PIN(83, AHB, E, 19),
    TKM32_PIN(84, AHB, E, 20),
    TKM32_PIN(85, AHB, E, 21),
    TKM32_PIN(86, AHB, E, 22),
    TKM32_PIN(87, AHB, E, 23),
};

struct pin_irq_map
{
    rt_uint16_t            pinbit;
    rt_uint32_t            irqbit;
    enum IRQn              irqno;
};
const struct pin_irq_map tkm32_pin_irq_map[] =
{
    {GPIO_Pin_0,  EXTI_Line0,  EXTI0_IRQn    },
    {GPIO_Pin_1,  EXTI_Line1,  EXTI1_IRQn    },
    {GPIO_Pin_2,  EXTI_Line2,  EXTI2_IRQn    },
    {GPIO_Pin_3,  EXTI_Line3,  EXTI3_IRQn    },
    {GPIO_Pin_4,  EXTI_Line4,  EXTI4_IRQn    },
    {GPIO_Pin_5,  EXTI_Line5,  EXTI9_5_IRQn  },
    {GPIO_Pin_6,  EXTI_Line6,  EXTI9_5_IRQn  },
    {GPIO_Pin_7,  EXTI_Line7,  EXTI9_5_IRQn  },
    {GPIO_Pin_8,  EXTI_Line8,  EXTI9_5_IRQn  },
    {GPIO_Pin_9,  EXTI_Line9,  EXTI9_5_IRQn  },
    {GPIO_Pin_10, EXTI_Line10, EXTI15_10_IRQn},
    {GPIO_Pin_11, EXTI_Line11, EXTI15_10_IRQn},
    {GPIO_Pin_12, EXTI_Line12, EXTI15_10_IRQn},
    {GPIO_Pin_13, EXTI_Line13, EXTI15_10_IRQn},
    {GPIO_Pin_14, EXTI_Line14, EXTI15_10_IRQn},
    {GPIO_Pin_15, EXTI_Line15, EXTI15_10_IRQn},
};
struct rt_pin_irq_hdr tkm32_pin_irq_hdr_tab[] =
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
const struct pin_index *get_pin(uint8_t pin)
{
    const struct pin_index *index;

    if (pin+1 < ITEM_NUM(tkm32_pin_map))
    {
        index = &tkm32_pin_map[pin+1];
        if (index->gpio == 0)
            index = RT_NULL;
    }
    else
    {
        index = RT_NULL;
    }

    return index;
};

void tkm32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    if (value == PIN_LOW)
    {
        GPIO_ResetBits(index->gpio, index->pin);
    }
    else
    {
        GPIO_SetBits(index->gpio, index->pin);
    }
}

rt_int8_t tkm32_pin_read(rt_device_t dev, rt_base_t pin)
{
    rt_int8_t value;
    const struct pin_index *index;

    value = PIN_LOW;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return PIN_LOW;
    }
    if (GPIO_ReadInputDataBit(index->gpio, index->pin) == Bit_RESET)
    {
        value = PIN_LOW;
    }
    else
    {
        value = PIN_HIGH;
    }
    return value;
}

void tkm32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    const struct pin_index *index;
    GPIO_InitTypeDef  GPIO_InitStructure;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    /* GPIO Periph clock enable */
    RCC_AHBPeriphClockCmd(index->rcc, ENABLE);
    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.GPIO_Pin     = index->pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    }
    else
    {
        /* input setting:default. */
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;
    }
    GPIO_Init( index->gpio, &GPIO_InitStructure);
    GPIO_PinAFConfig(index->gpio, index->pin, GPIO_AF_GPIO);
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
    if (mapindex < 0 || mapindex >= ITEM_NUM(tkm32_pin_irq_map))
    {
        return RT_NULL;
    }
    return &tkm32_pin_irq_map[mapindex];
};
rt_err_t tkm32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
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
    irqindex = bit2bitno(index->pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(tkm32_pin_irq_map))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (tkm32_pin_irq_hdr_tab[irqindex].pin == pin   &&
            tkm32_pin_irq_hdr_tab[irqindex].hdr == hdr   &&
            tkm32_pin_irq_hdr_tab[irqindex].mode == mode &&
            tkm32_pin_irq_hdr_tab[irqindex].args == args
       )
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (tkm32_pin_irq_hdr_tab[irqindex].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }
    tkm32_pin_irq_hdr_tab[irqindex].pin = pin;
    tkm32_pin_irq_hdr_tab[irqindex].hdr = hdr;
    tkm32_pin_irq_hdr_tab[irqindex].mode = mode;
    tkm32_pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}
rt_err_t tkm32_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(tkm32_pin_irq_map))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (tkm32_pin_irq_hdr_tab[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    tkm32_pin_irq_hdr_tab[irqindex].pin = -1;
    tkm32_pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
    tkm32_pin_irq_hdr_tab[irqindex].mode = 0;
    tkm32_pin_irq_hdr_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}
rt_err_t tkm32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                             rt_uint8_t enabled)
{
    const struct pin_index *index;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }
    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(index->pin);
        if (irqindex < 0 || irqindex >= ITEM_NUM(tkm32_pin_irq_map))
        {
            return -RT_ENOSYS;
        }
        level = rt_hw_interrupt_disable();
        if (tkm32_pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }
        irqmap = &tkm32_pin_irq_map[irqindex];
        /* GPIO Periph clock enable */
        RCC_AHBPeriphClockCmd(index->rcc, ENABLE);
        /* Configure GPIO_InitStructure */
        GPIO_InitStructure.GPIO_Pin     = index->pin;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(index->gpio, &GPIO_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel = irqmap->irqno;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        // GPIO_EXTILineConfig(index->port_source, index->pin_source);
        // EXTI_InitStructure.EXTI_Line = irqmap->irqbit;
        // EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        switch (tkm32_pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            Ex_NVIC_Config(index->port_source, index->pin_source, 2);
            // EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
            break;
        case PIN_IRQ_MODE_FALLING:
            Ex_NVIC_Config(index->port_source, index->pin_source, 1);
            // EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            Ex_NVIC_Config(index->port_source, index->pin_source, 3);
            // EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
            break;
        }
        // EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        // EXTI_Init(&EXTI_InitStructure);
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(index->pin);
        if (irqmap == RT_NULL)
        {
            return -RT_ENOSYS;
        }
        EXTI_InitStructure.EXTI_Line = irqmap->irqbit;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
        EXTI_InitStructure.EXTI_LineCmd = DISABLE;
        EXTI_Init(&EXTI_InitStructure);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}
const static struct rt_pin_ops _tkm32_pin_ops =
{
    tkm32_pin_mode,
    tkm32_pin_write,
    tkm32_pin_read,
    tkm32_pin_attach_irq,
    tkm32_pin_detach_irq,
    tkm32_pin_irq_enable,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
    int result;

    result = rt_device_pin_register("pin", &_tkm32_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

rt_inline void pin_irq_hdr(int irqno)
{
    EXTI_ClearITPendingBit(tkm32_pin_irq_map[irqno].irqbit);
    if (tkm32_pin_irq_hdr_tab[irqno].hdr)
    {
        tkm32_pin_irq_hdr_tab[irqno].hdr(tkm32_pin_irq_hdr_tab[irqno].args);
    }
}
void EXTI0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    pin_irq_hdr(0);
    /* leave interrupt */
    rt_interrupt_leave();
}
void EXTI1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    pin_irq_hdr(1);
    /* leave interrupt */
    rt_interrupt_leave();
}
void EXTI2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    pin_irq_hdr(2);
    /* leave interrupt */
    rt_interrupt_leave();
}
void EXTI3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    pin_irq_hdr(3);
    /* leave interrupt */
    rt_interrupt_leave();
}
void EXTI4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    pin_irq_hdr(4);
    /* leave interrupt */
    rt_interrupt_leave();
}
void EXTI9_5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    if (EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
        pin_irq_hdr(5);
    }
    if (EXTI_GetITStatus(EXTI_Line6) != RESET)
    {
        pin_irq_hdr(6);
    }
    if (EXTI_GetITStatus(EXTI_Line7) != RESET)
    {
        pin_irq_hdr(7);
    }
    if (EXTI_GetITStatus(EXTI_Line8) != RESET)
    {
        pin_irq_hdr(8);
    }
    if (EXTI_GetITStatus(EXTI_Line9) != RESET)
    {
        pin_irq_hdr(9);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
void EXTI15_10_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    if (EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
        pin_irq_hdr(10);
    }
    if (EXTI_GetITStatus(EXTI_Line11) != RESET)
    {
        pin_irq_hdr(11);
    }
    if (EXTI_GetITStatus(EXTI_Line12) != RESET)
    {
        pin_irq_hdr(12);
    }
    if (EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
        pin_irq_hdr(13);
    }
    if (EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
        pin_irq_hdr(14);
    }
    if (EXTI_GetITStatus(EXTI_Line15) != RESET)
    {
        pin_irq_hdr(15);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* RT_USING_PIN */
