/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#include <board.h>
#include "drv_gpio.h"

#ifdef BSP_USING_GPIO

#define PIN_NUM(port, no) (((((port) & 0xFu) << 4) | ((no) & 0xFu)))
#define PIN_PORT(pin) ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin) ((uint8_t)((pin) & 0xFu))

#define PIN_AIRPORT(pin) ((GPIO_TypeDef *)(GPIOA_BASE + (0x400u * PIN_PORT(pin))))

#define PIN_AIRPIN(pin) ((uint16_t)(1u << PIN_NO(pin)))

#if defined(GPIOZ)
#define __AIR32_PORT_MAX 12u
#elif defined(GPIOK)
#define __AIR32_PORT_MAX 11u
#elif defined(GPIOJ)
#define __AIR32_PORT_MAX 10u
#elif defined(GPIOI)
#define __AIR32_PORT_MAX 9u
#elif defined(GPIOH)
#define __AIR32_PORT_MAX 8u
#elif defined(GPIOG)
#define __AIR32_PORT_MAX 7u
#elif defined(GPIOF)
#define __AIR32_PORT_MAX 6u
#elif defined(GPIOE)
#define __AIR32_PORT_MAX 5u
#elif defined(GPIOD)
#define __AIR32_PORT_MAX 4u
#elif defined(GPIOC)
#define __AIR32_PORT_MAX 3u
#elif defined(GPIOB)
#define __AIR32_PORT_MAX 2u
#elif defined(GPIOA)
#define __AIR32_PORT_MAX 1u
#else
#define __AIR32_PORT_MAX 0u
#error Unsupported AIR32 GPIO peripheral.
#endif

#define PIN_AIRPORT_MAX __AIR32_PORT_MAX


struct pin_irq_map
{
    rt_uint16_t pinbit;
    rt_uint32_t irqbit;
    IRQn_Type irqno;
};

static const struct pin_irq_map pin_irq_map[] =
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

#define ITEM_NUM(items) (sizeof(items) / sizeof((items)[0]))

/* e.g. PE.7 */
static rt_base_t air32_pin_get(const char *name)
{
    rt_base_t pin = 0;
    int hw_port_num, hw_pin_num = 0;
    int i, name_len;

    name_len = rt_strlen(name);

    if ((name_len < 4) || (name_len >= 6))
    {
        return -RT_EINVAL;
    }
    if ((name[0] != 'P') || (name[2] != '.'))
    {
        return -RT_EINVAL;
    }

    if ((name[1] >= 'A') && (name[1] <= 'Z'))
    {
        hw_port_num = (int)(name[1] - 'A');
    }
    else
    {
        return -RT_EINVAL;
    }

    for (i = 3; i < name_len; i++)
    {
        hw_pin_num *= 10;
        hw_pin_num += name[i] - '0';
    }

    pin = PIN_NUM(hw_port_num, hw_pin_num);

    return pin;
}

static void air32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;

    if (PIN_PORT(pin) < PIN_AIRPORT_MAX)
    {
        gpio_port = PIN_AIRPORT(pin);
        gpio_pin = PIN_AIRPIN(pin);

        GPIO_WriteBit(gpio_port, gpio_pin, (BitAction)value);
    }
}

static rt_int8_t air32_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    int value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_AIRPORT_MAX)
    {
        gpio_port = PIN_AIRPORT(pin);
        gpio_pin = PIN_AIRPIN(pin);
        value = GPIO_ReadInputDataBit(gpio_port, gpio_pin);
    }

    return value;
}

static void air32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    if (PIN_PORT(pin) >= PIN_AIRPORT_MAX)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.GPIO_Pin = PIN_AIRPIN(pin);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: pull up. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* output setting: od. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    }

    GPIO_Init(PIN_AIRPORT(pin), &GPIO_InitStruct);
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

rt_inline const struct pin_irq_map *get_pin_irq_map(uint32_t pinbit)
{
    rt_int32_t mapindex = bit2bitno(pinbit);
    if (mapindex < 0 || mapindex >= (rt_int32_t)ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
};

static rt_err_t air32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_AIRPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_AIRPIN(pin));
    if (irqindex < 0 || irqindex >= (rt_int32_t)ITEM_NUM(pin_irq_map))
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

static rt_err_t air32_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_AIRPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_AIRPIN(pin));
    if (irqindex < 0 || irqindex >= (rt_int32_t)ITEM_NUM(pin_irq_map))
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

static rt_err_t air32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t enabled)
{
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    rt_uint8_t gpio_port_souce=0;
    GPIO_InitTypeDef GPIO_InitStruct={0};
    NVIC_InitTypeDef  NVIC_InitStructure={0};
    EXTI_InitTypeDef EXTI_InitStructure={0};

    if (PIN_PORT(pin) >= PIN_AIRPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(PIN_AIRPIN(pin));
        if (irqindex < 0 || irqindex >= (rt_int32_t)ITEM_NUM(pin_irq_map))
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
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);

        /* Configure GPIO_InitStructure */
        GPIO_InitStruct.GPIO_Pin = PIN_AIRPIN(pin);
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
            break;
        case PIN_IRQ_MODE_FALLING:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
            break;
        }
        GPIO_Init(PIN_AIRPORT(pin), &GPIO_InitStruct);

        NVIC_InitStructure.NVIC_IRQChannel = irqmap->irqno;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        GPIO_EXTILineConfig(gpio_port_souce,(rt_uint8_t)irqindex);
        EXTI_InitStructure.EXTI_Line = irqmap->irqbit;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;

        gpio_port_souce=PIN_PORT(pin);

        EXTI_Init(&EXTI_InitStructure);

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(PIN_AIRPIN(pin));
        if (irqmap == RT_NULL)
        {
            return -RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        irqmap = &pin_irq_map[irqindex];

        EXTI_InitStructure.EXTI_Line = irqmap->irqbit;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
        EXTI_InitStructure.EXTI_LineCmd = DISABLE;
        EXTI_Init(&EXTI_InitStructure);

        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}
static const struct rt_pin_ops _air32_pin_ops =
{
    .pin_mode =         air32_pin_mode,
    .pin_write =        air32_pin_write,
    .pin_read =         air32_pin_read,
    .pin_attach_irq =   air32_pin_attach_irq,
    .pin_detach_irq =   air32_pin_dettach_irq,
    .pin_irq_enable =   air32_pin_irq_enable,
    .pin_get =          air32_pin_get,
};


rt_inline void exti_irq_handler(rt_uint16_t seq)
{
    if (EXTI_GetITStatus(pin_irq_map[seq].irqbit) == SET)
    {
        EXTI_ClearITPendingBit(pin_irq_map[seq].irqbit);

        if (pin_irq_hdr_tab[seq].hdr)
        {
            pin_irq_hdr_tab[seq].hdr(pin_irq_hdr_tab[seq].args);
        }
    }
}

void EXTI0_IRQHandler(void)
{
    rt_interrupt_enter();

    exti_irq_handler(0);

    rt_interrupt_leave();
}

void EXTI1_IRQHandler(void)
{
    rt_interrupt_enter();

    exti_irq_handler(1);

    rt_interrupt_leave();
}

void EXTI2_IRQHandler(void)
{
    rt_interrupt_enter();

    exti_irq_handler(2);

    rt_interrupt_leave();
}

void EXTI3_IRQHandler(void)
{
    rt_interrupt_enter();

    exti_irq_handler(3);

    rt_interrupt_leave();
}

void EXTI4_IRQHandler(void)
{
    rt_interrupt_enter();

    exti_irq_handler(4);

    rt_interrupt_leave();
}

void EXTI9_5_IRQHandler(void)
{
    rt_interrupt_enter();

    exti_irq_handler(5);

    exti_irq_handler(6);

    exti_irq_handler(7);

    exti_irq_handler(8);

    exti_irq_handler(9);

    rt_interrupt_leave();
}

void EXTI15_10_IRQHandler(void)
{
    rt_interrupt_enter();

    exti_irq_handler(10);

    exti_irq_handler(11);

    exti_irq_handler(12);

    exti_irq_handler(13);

    exti_irq_handler(14);

    exti_irq_handler(15);

    rt_interrupt_leave();
}

int rt_hw_pin_init(void)
{
#ifdef GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
#endif
#ifdef GPIOB
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
#endif
#ifdef GPIOC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
#endif
#ifdef GPIOD
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
#endif
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    return rt_device_pin_register("pin", &_air32_pin_ops, RT_NULL);
}

#endif /* BSP_USING_GPIO */
