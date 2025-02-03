/*
 * Copyright (c) 2022-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-22     chasel   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_gpio.h"
#include <board.h>
#include <rthw.h>
#include <hal_gpio.h>
#include <hal_exti.h>
#include <hal_misc.h>
#include <hal_rcc.h>

#define PIN_NUM(port, no)               (((((port) & 0xFu) << 4) | ((no) & 0xFu)))
#define PIN_PORT(pin)                   ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin)                     ((uint8_t)((pin) & 0xFu))
#define RCC_PIN_PORT(pin)               ((uint32_t)(0x01u << (PIN_PORT(pin))))

#define PIN_ATPORTSOURCE(pin)           ((uint8_t)(((pin) & 0xF0u) >> 4))
#define PIN_ATPINSOURCE(pin)            ((uint8_t)((pin) & 0xFu))

#define PIN_ATPORT(pin)                 ((GPIO_TypeDef *)(GPIOA_BASE + (0x400u * PIN_PORT(pin))))
#define PIN_ATPIN(pin)                  ((uint16_t)(1u << PIN_NO(pin)))

/* mm32f5265 pin port */
#define __MM32_PORT_MAX 6u

#define PIN_ATPORT_MAX __MM32_PORT_MAX

struct pin_irq_map
{
    rt_uint16_t pinbit;
    rt_uint32_t irqbit;
    enum IRQn irqno;
};
const struct pin_irq_map mm32_pin_irq_map[] =
{
    {GPIO_Pin_0, EXTI_Line0, EXTI0_IRQn},
    {GPIO_Pin_1, EXTI_Line1, EXTI1_IRQn},
    {GPIO_Pin_2, EXTI_Line2, EXTI2_IRQn},
    {GPIO_Pin_3, EXTI_Line3, EXTI3_IRQn},
    {GPIO_Pin_4, EXTI_Line4, EXTI4_IRQn},
    {GPIO_Pin_5, EXTI_Line5, EXTI9_5_IRQn},
    {GPIO_Pin_6, EXTI_Line6, EXTI9_5_IRQn},
    {GPIO_Pin_7, EXTI_Line7, EXTI9_5_IRQn},
    {GPIO_Pin_8, EXTI_Line8, EXTI9_5_IRQn},
    {GPIO_Pin_9, EXTI_Line9, EXTI9_5_IRQn},
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

static rt_base_t mm32_pin_get(const char *name)
{
    rt_base_t pin = 0;
    int hw_port_num, hw_pin_num = 0;
    int i, name_len;

    name_len = rt_strlen(name);

    if ((name_len < 4) || (name_len >= 6)) {
        return -RT_EINVAL;
    }

    if ((name[0] != 'P') || (name[2] != '.')) {
        return -RT_EINVAL;
    }

    if ((name[1] >= 'A') && (name[1] <= 'Z')) {
        hw_port_num = (int)(name[1] - 'A');
    } else {
        return -RT_EINVAL;
    }

    for (i = 3; i < name_len; i++) {
        hw_pin_num *= 10;
        hw_pin_num += name[i] - '0';
    }

    pin = PIN_NUM(hw_port_num, hw_pin_num);

    return pin;
}

void mm32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    GPIO_TypeDef *gpio_port;

    uint16_t gpio_pin;
    if (PIN_PORT(pin) < PIN_ATPORT_MAX) {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
    } else {
        return;
    }

    GPIO_WriteBit(gpio_port, gpio_pin, (PIN_LOW == value) ? Bit_RESET : Bit_SET);
}

rt_ssize_t mm32_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    int value;

    value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX) {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
        value = GPIO_ReadInputDataBit(gpio_port, gpio_pin);
    } else {
        return -RT_EINVAL;
    }

    return value;
}

void mm32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    GPIO_InitTypeDef GPIO_InitStructure;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX) {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
    } else {
        return;
    }

    /* GPIO Periph clock enable */
    RCC_AHBPeriphClockCmd(RCC_PIN_PORT(pin), ENABLE);

    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.GPIO_Pin = gpio_pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_High;

    if (mode == PIN_MODE_OUTPUT) {
        /* output setting */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    } else if (mode == PIN_MODE_OUTPUT_OD) {
        /* output setting: od. */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    } else if (mode == PIN_MODE_INPUT) {
        /* input setting: not pull. */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_FLOATING;
    } else if (mode == PIN_MODE_INPUT_PULLUP) {
        /* input setting: pull up. */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    } else {
        /* input setting:default. */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    }

    GPIO_Init(gpio_port, &GPIO_InitStructure);
}

rt_inline rt_int32_t bit2bitno(rt_uint32_t bit)
{
    int i;
    for (i = 0; i < 32; i++) {
        if ((0x01 << i) == bit) {
            return i;
        }
    }

    return -1;
}

rt_inline const struct pin_irq_map *get_pin_irq_map(uint32_t pinbit)
{
    rt_int32_t mapindex = bit2bitno(pinbit);
    if (mapindex < 0 || mapindex >= ITEM_NUM(mm32_pin_irq_map)) {
        return RT_NULL;
    }
    return &mm32_pin_irq_map[mapindex];
};

rt_err_t mm32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                             rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    uint16_t gpio_pin;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX) {
        gpio_pin = PIN_ATPIN(pin);
    } else {
        return -RT_EINVAL;
    }

    irqindex = bit2bitno(gpio_pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(mm32_pin_irq_map)) {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (mm32_pin_irq_hdr_tab[irqindex].pin == pin &&
            mm32_pin_irq_hdr_tab[irqindex].hdr == hdr &&
            mm32_pin_irq_hdr_tab[irqindex].mode == mode &&
            mm32_pin_irq_hdr_tab[irqindex].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }

    if (mm32_pin_irq_hdr_tab[irqindex].pin != -1) {
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
    uint16_t gpio_pin;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX) {
        gpio_pin     =  PIN_ATPIN(pin);
    } else {
        return -RT_EINVAL;
    }

    irqindex = bit2bitno(gpio_pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(mm32_pin_irq_map)) {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (mm32_pin_irq_hdr_tab[irqindex].pin == -1) {
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
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX) {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
    } else {
        return -RT_EINVAL;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(gpio_pin);
        if (irqindex < 0 || irqindex >= ITEM_NUM(mm32_pin_irq_map)) {
            return -RT_ENOSYS;
        }
        level = rt_hw_interrupt_disable();
        if (mm32_pin_irq_hdr_tab[irqindex].pin == -1) {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }
        irqmap = &mm32_pin_irq_map[irqindex];

        /* GPIO Periph clock enable */
        RCC_AHBPeriphClockCmd(RCC_PIN_PORT(pin), ENABLE);

        /* Configure GPIO_InitStructure */
        GPIO_InitStructure.GPIO_Pin = gpio_pin;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_High;
        GPIO_Init(gpio_port, &GPIO_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel = irqmap->irqno;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        EXTI_InitStructure.EXTI_Line = irqmap->irqbit;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        switch (mm32_pin_irq_hdr_tab[irqindex].mode) {
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
    } else if (enabled == PIN_IRQ_DISABLE) {
        irqmap = get_pin_irq_map(gpio_pin);
        if (irqmap == RT_NULL) {
            return -RT_ENOSYS;
        }
        EXTI_InitStructure.EXTI_Line = irqmap->irqbit;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
        EXTI_InitStructure.EXTI_LineCmd = DISABLE;
        EXTI_Init(&EXTI_InitStructure);
    } else {
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
    mm32_pin_get,
};

int rt_hw_pin_init(void)
{
    int result;

    result = rt_device_pin_register("pin", &_mm32_pin_ops, RT_NULL);
    return result;
}

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

