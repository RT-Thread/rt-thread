/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-02     henryhuang   the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <rthw.h>

#define MM32_PIN(index, rcc, gpio, gpio_index) { 0, RCC_##rcc##Periph_GPIO##gpio, GPIO##gpio, GPIO_Pin_##gpio_index, GPIO_PortSourceGPIO##gpio, GPIO_PinSource##gpio_index}
#define MM32_PIN_DEFAULT {-1, 0, 0, 0, 0, 0}
/* MM32 GPIO driver */
struct pin_index
{
    int index;
    uint32_t rcc;
    GPIO_TypeDef *gpio;
    uint32_t pin;
    uint8_t port_source;
    uint8_t pin_source;
};
static const struct pin_index mm32_pin_map[] =
{
    MM32_PIN_DEFAULT,
    MM32_PIN_DEFAULT,
    MM32_PIN(2, APB2, C, 13),
    MM32_PIN(3, APB2, C, 14),
    MM32_PIN(4, APB2, C, 15),
    MM32_PIN_DEFAULT,
    MM32_PIN_DEFAULT,
    MM32_PIN_DEFAULT,
    MM32_PIN_DEFAULT,
    MM32_PIN_DEFAULT,
    MM32_PIN(10, APB2, A, 0),
    MM32_PIN(11, APB2, A, 1),
    MM32_PIN(12, APB2, A, 2),
    MM32_PIN(13, APB2, A, 3),
    MM32_PIN(14, APB2, A, 4),
    MM32_PIN(15, APB2, A, 5),
    MM32_PIN(16, APB2, A, 6),
    MM32_PIN(17, APB2, A, 7),
    MM32_PIN(18, APB2, B, 0),
    MM32_PIN(19, APB2, B, 1),
    MM32_PIN(20, APB2, B, 2),
    MM32_PIN(21, APB2, B, 10),
    MM32_PIN(22, APB2, B, 11),
    MM32_PIN_DEFAULT,
    MM32_PIN_DEFAULT,
    MM32_PIN(25, APB2, B, 12),
    MM32_PIN(26, APB2, B, 13),
    MM32_PIN(27, APB2, B, 14),
    MM32_PIN(28, APB2, B, 15),
    MM32_PIN(29, APB2, A, 8),
    MM32_PIN(30, APB2, A, 9),
    MM32_PIN(31, APB2, A, 10),
    MM32_PIN(32, APB2, A, 11),
    MM32_PIN(33, APB2, A, 12),
    MM32_PIN(34, APB2, A, 13),
    MM32_PIN_DEFAULT,
    MM32_PIN_DEFAULT,
    MM32_PIN(37, APB2, A, 14),
    MM32_PIN(38, APB2, A, 15),
    MM32_PIN(39, APB2, B, 3),
    MM32_PIN(40, APB2, B, 4),
    MM32_PIN(41, APB2, B, 5),
    MM32_PIN(42, APB2, B, 6),
    MM32_PIN(43, APB2, B, 7),
    MM32_PIN_DEFAULT,
    MM32_PIN(45, APB2, B, 8),
    MM32_PIN(46, APB2, B, 9),
    MM32_PIN_DEFAULT,
    MM32_PIN_DEFAULT,
};

struct pin_irq_map
{
    rt_uint16_t            pinbit;
    rt_uint32_t            irqbit;
    enum IRQn              irqno;
};
const struct pin_irq_map mm32_pin_irq_map[] =
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
struct rt_pin_irq_hdr mm32_pin_irq_hdr_tab[] =
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

    if (pin < ITEM_NUM(mm32_pin_map))
    {
        index = &mm32_pin_map[pin];
        if (index->gpio == 0)
            index = RT_NULL;
    }
    else
    {
        index = RT_NULL;
    }

    return index;
};

void mm32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
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

rt_ssize_t mm32_pin_read(rt_device_t dev, rt_base_t pin)
{
    rt_ssize_t value;
    const struct pin_index *index;

    value = PIN_LOW;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_EINVAL;
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

void mm32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    const struct pin_index *index;
    GPIO_InitTypeDef  GPIO_InitStructure;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    /* GPIO Periph clock enable */
    RCC_APB2PeriphClockCmd(index->rcc, ENABLE);
    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.GPIO_Pin     = index->pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
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
    if (mapindex < 0 || mapindex >= ITEM_NUM(mm32_pin_irq_map))
    {
        return RT_NULL;
    }
    return &mm32_pin_irq_map[mapindex];
};
rt_err_t mm32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
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
    if (irqindex < 0 || irqindex >= ITEM_NUM(mm32_pin_irq_map))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (mm32_pin_irq_hdr_tab[irqindex].pin == pin   &&
            mm32_pin_irq_hdr_tab[irqindex].hdr == hdr   &&
            mm32_pin_irq_hdr_tab[irqindex].mode == mode &&
            mm32_pin_irq_hdr_tab[irqindex].args == args
       )
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (mm32_pin_irq_hdr_tab[irqindex].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }
    mm32_pin_irq_hdr_tab[irqindex].pin = pin;
    mm32_pin_irq_hdr_tab[irqindex].hdr = hdr;
    mm32_pin_irq_hdr_tab[irqindex].mode = mode;
    mm32_pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}
rt_err_t mm32_pin_detach_irq(struct rt_device *device, rt_base_t pin)
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
    if (irqindex < 0 || irqindex >= ITEM_NUM(mm32_pin_irq_map))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (mm32_pin_irq_hdr_tab[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    mm32_pin_irq_hdr_tab[irqindex].pin = -1;
    mm32_pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
    mm32_pin_irq_hdr_tab[irqindex].mode = 0;
    mm32_pin_irq_hdr_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}
rt_err_t mm32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
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
        if (irqindex < 0 || irqindex >= ITEM_NUM(mm32_pin_irq_map))
        {
            return -RT_ENOSYS;
        }
        level = rt_hw_interrupt_disable();
        if (mm32_pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }
        irqmap = &mm32_pin_irq_map[irqindex];
        /* GPIO Periph clock enable */
        RCC_APB2PeriphClockCmd(index->rcc, ENABLE);
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

        GPIO_EXTILineConfig(index->port_source, index->pin_source);
        EXTI_InitStructure.EXTI_Line = irqmap->irqbit;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        switch (mm32_pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
            break;
        case PIN_IRQ_MODE_FALLING:
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
            break;
        }
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_Init(&EXTI_InitStructure);
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
const static struct rt_pin_ops _mm32_pin_ops =
{
    mm32_pin_mode,
    mm32_pin_write,
    mm32_pin_read,
    mm32_pin_attach_irq,
    mm32_pin_detach_irq,
    mm32_pin_irq_enable,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
    int result;

    result = rt_device_pin_register("pin", &_mm32_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

rt_inline void pin_irq_hdr(int irqno)
{
    EXTI_ClearITPendingBit(mm32_pin_irq_map[irqno].irqbit);
    if (mm32_pin_irq_hdr_tab[irqno].hdr)
    {
        mm32_pin_irq_hdr_tab[irqno].hdr(mm32_pin_irq_hdr_tab[irqno].args);
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
