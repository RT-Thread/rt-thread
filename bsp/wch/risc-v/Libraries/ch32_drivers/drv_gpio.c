/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     liYony       first version
 */

#include <board.h>
#include "drv_gpio.h"

#ifdef BSP_USING_GPIO
#define PIN_NUM(port, no) (((((port) & 0xFu) << 4) | ((no) & 0xFu)))
#define PIN_PORT(pin) ((rt_uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin) ((rt_uint8_t)((pin) & 0xFu))

#define PIN_STPORT(pin) ((GPIO_TypeDef *)(GPIOA_BASE + (0x400u * PIN_PORT(pin))))
#define PIN_STPIN(pin) ((rt_uint16_t)(1u << PIN_NO(pin)))

#if defined(GPIOZ)
#define __CH32_PORT_MAX 12u
#elif defined(GPIOK)
#define __CH32_PORT_MAX 11u
#elif defined(GPIOJ)
#define __CH32_PORT_MAX 10u
#elif defined(GPIOI)
#define __CH32_PORT_MAX 9u
#elif defined(GPIOH)
#define __CH32_PORT_MAX 8u
#elif defined(GPIOG)
#define __CH32_PORT_MAX 7u
#elif defined(GPIOF)
#define __CH32_PORT_MAX 6u
#elif defined(GPIOE)
#define __CH32_PORT_MAX 5u
#elif defined(GPIOD)
#define __CH32_PORT_MAX 4u
#elif defined(GPIOC)
#define __CH32_PORT_MAX 3u
#elif defined(GPIOB)
#define __CH32_PORT_MAX 2u
#elif defined(GPIOA)
#define __CH32_PORT_MAX 1u
#else
#define __CH32_PORT_MAX 0u
#error Unsupported CH32 GPIO peripheral.
#endif

#define PIN_STPORT_MAX __CH32_PORT_MAX

static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_Pin_0, EXTI0_IRQn},
    {GPIO_Pin_1, EXTI1_IRQn},
    {GPIO_Pin_2, EXTI2_IRQn},
    {GPIO_Pin_3, EXTI3_IRQn},
    {GPIO_Pin_4, EXTI4_IRQn},
    {GPIO_Pin_5, EXTI9_5_IRQn},
    {GPIO_Pin_6, EXTI9_5_IRQn},
    {GPIO_Pin_7, EXTI9_5_IRQn},
    {GPIO_Pin_8, EXTI9_5_IRQn},
    {GPIO_Pin_9, EXTI9_5_IRQn},
    {GPIO_Pin_10, EXTI15_10_IRQn},
    {GPIO_Pin_11, EXTI15_10_IRQn},
    {GPIO_Pin_12, EXTI15_10_IRQn},
    {GPIO_Pin_13, EXTI15_10_IRQn},
    {GPIO_Pin_14, EXTI15_10_IRQn},
    {GPIO_Pin_15, EXTI15_10_IRQn},
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
static rt_uint32_t pin_irq_enable_mask = 0;

#define ITEM_NUM(items) (sizeof(items) / sizeof((items)[0]))

static rt_base_t ch32_pin_get(const char *name)
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

static void ch32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    GPIO_TypeDef *gpio_port;
    rt_uint16_t gpio_pin;

    if (PIN_PORT(pin) < PIN_STPORT_MAX)
    {
        gpio_port = PIN_STPORT(pin);
        gpio_pin = PIN_STPIN(pin);
        GPIO_WriteBit(gpio_port, gpio_pin, (BitAction)value);
    }
}

static int ch32_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_TypeDef *gpio_port;
    rt_uint16_t gpio_pin;
    int value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_STPORT_MAX)
    {
        gpio_port = PIN_STPORT(pin);
        gpio_pin = PIN_STPIN(pin);
        value = GPIO_ReadInputDataBit(gpio_port, gpio_pin);
    }

    return value;
}

static void ch32_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.GPIO_Pin = PIN_STPIN(pin);
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

    GPIO_Init(PIN_STPORT(pin), &GPIO_InitStruct);
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

rt_inline const struct pin_irq_map *get_pin_irq_map(rt_uint32_t pinbit)
{
    rt_int32_t mapindex = bit2bitno(pinbit);
    if (mapindex < 0 || mapindex >= (rt_int32_t)ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
};

static rt_err_t ch32_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                     rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_STPIN(pin));
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

static rt_err_t ch32_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_STPIN(pin));
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

static rt_err_t ch32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint32_t enabled)
{
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    rt_uint8_t gpio_port_souce=0;
    GPIO_InitTypeDef GPIO_InitStruct={0};
    EXTI_InitTypeDef EXTI_InitStructure={0};

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(PIN_STPIN(pin));
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

        GPIO_InitStruct.GPIO_Pin = PIN_STPIN(pin);
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

        EXTI_InitStructure.EXTI_Line=PIN_STPIN(pin);
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;

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
        GPIO_Init(PIN_STPORT(pin), &GPIO_InitStruct);

        gpio_port_souce=PIN_PORT(pin);

        GPIO_EXTILineConfig(gpio_port_souce,(rt_uint8_t)irqindex);

        EXTI_Init(&EXTI_InitStructure);
        NVIC_SetPriority(irqmap->irqno,5<<4);
        NVIC_EnableIRQ( irqmap->irqno );
        pin_irq_enable_mask |= irqmap->pinbit;

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(PIN_STPIN(pin));
        if (irqmap == RT_NULL)
        {
            return -RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        pin_irq_enable_mask &= ~irqmap->pinbit;

        if (( irqmap->pinbit>=GPIO_Pin_5 )&&( irqmap->pinbit<=GPIO_Pin_9 ))
        {
            if(!(pin_irq_enable_mask&(GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9)))
            {
                NVIC_DisableIRQ(irqmap->irqno);
            }
        }
        else if (( irqmap->pinbit>=GPIO_Pin_10 )&&( irqmap->pinbit<=GPIO_Pin_15 ))
        {
            if(!(pin_irq_enable_mask&(GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)))
            {
                NVIC_DisableIRQ(irqmap->irqno);
            }
        }
        else
        {
            NVIC_DisableIRQ(irqmap->irqno);
        }

        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}
static const struct rt_pin_ops _ch32_pin_ops =
{
    ch32_pin_mode,
    ch32_pin_write,
    ch32_pin_read,
    ch32_pin_attach_irq,
    ch32_pin_dettach_irq,
    ch32_pin_irq_enable,
    ch32_pin_get,
};

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void HAL_GPIO_EXTI_Callback(rt_uint16_t GPIO_Pin)
{
    pin_irq_hdr(bit2bitno(GPIO_Pin));
}

#if defined (SOC_RISCV_SERIES_CH32V2)
void EXTI0_IRQHandler(void) __attribute__((interrupt()));
void EXTI1_IRQHandler(void) __attribute__((interrupt()));
void EXTI2_IRQHandler(void) __attribute__((interrupt()));
void EXTI3_IRQHandler(void) __attribute__((interrupt()));
void EXTI4_IRQHandler(void) __attribute__((interrupt()));
void EXTI9_5_IRQHandler(void) __attribute__((interrupt()));
#else
void EXTI0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI9_5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif

void EXTI0_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();

    if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
    {
        HAL_GPIO_EXTI_Callback(GPIO_Pin_0);
        EXTI_ClearITPendingBit(EXTI_Line0);
    }

    rt_interrupt_leave();
    FREE_INT_SP();
}

void EXTI1_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
    {
        HAL_GPIO_EXTI_Callback(GPIO_Pin_1);
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
    rt_interrupt_leave();
    FREE_INT_SP();
}

void EXTI2_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
    {
        HAL_GPIO_EXTI_Callback(GPIO_Pin_2);
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
    rt_interrupt_leave();
    FREE_INT_SP();
}

void EXTI3_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
    {
        HAL_GPIO_EXTI_Callback(GPIO_Pin_3);
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
    rt_interrupt_leave();
    FREE_INT_SP();
}

void EXTI4_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
    {
        HAL_GPIO_EXTI_Callback(GPIO_Pin_4);
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
    rt_interrupt_leave();
    FREE_INT_SP();
}

void EXTI9_5_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    if( (EXTI_GetITStatus(EXTI_Line5)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line6)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line7)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line8)!=RESET)|| \
        (EXTI_GetITStatus(EXTI_Line9)!=RESET) )
    {
    HAL_GPIO_EXTI_Callback(GPIO_Pin_5);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_6);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_7);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_8);
    HAL_GPIO_EXTI_Callback(GPIO_Pin_9);
    EXTI_ClearITPendingBit(EXTI_Line5|EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9);
    }
    rt_interrupt_leave();
    FREE_INT_SP();
}

int rt_hw_pin_init(void)
{
#if defined(RCC_APB2Periph_GPIOA)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
#if defined(RCC_APB2Periph_GPIOB)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
#if defined(RCC_APB2Periph_GPIOC)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
#if defined(RCC_APB2Periph_GPIOD)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);
#if defined(RCC_APB2Periph_GPIOE)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE , ENABLE);
#if defined(RCC_APB2Periph_GPIOF)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF , ENABLE);
#if defined(RCC_APB2Periph_GPIOG)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG , ENABLE);
#if defined(RCC_APB2Periph_GPIOH)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOH , ENABLE);
#if defined(RCC_APB2Periph_GPIOI)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOI , ENABLE);
#if defined(RCC_APB2Periph_GPIOJ)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOJ , ENABLE);
#if defined(RCC_APB2Periph_GPIOK)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOK , ENABLE);
#if defined(RCC_APB2Periph_GPIOZ)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOZ , ENABLE);
#endif /* defined(RCC_APB2Periph_GPIOZ) */
#endif /* defined(RCC_APB2Periph_GPIOK) */
#endif /* defined(RCC_APB2Periph_GPIOJ) */
#endif /* defined(RCC_APB2Periph_GPIOI) */
#endif /* defined(RCC_APB2Periph_GPIOH) */
#endif /* defined(RCC_APB2Periph_GPIOG) */
#endif /* defined(RCC_APB2Periph_GPIOF) */
#endif /* defined(RCC_APB2Periph_GPIOE) */
#endif /* defined(RCC_APB2Periph_GPIOD) */
#endif /* defined(RCC_APB2Periph_GPIOC) */
#endif /* defined(RCC_APB2Periph_GPIOB) */
#endif /* defined(RCC_APB2Periph_GPIOA) */

    return rt_device_pin_register("pin", &_ch32_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* BSP_USING_GPIO */
