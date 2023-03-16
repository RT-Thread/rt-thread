/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-01-21     charlown           first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "board.h"
#include "ch32f20x_gpio.h"

#ifdef RT_USING_PIN

#ifndef ITEM_NUM
#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
#endif

struct pin_info
{
    rt_base_t pin;
    rt_uint32_t gpio_pin;
    rt_uint32_t portsource;
    rt_uint32_t pinsource;
    GPIO_TypeDef *gpio;
};

/*
 *pin: assign number, start 0
 *group: such GPIOA, use 'A'
 *gpio_pin: such GPIO_PIN_0, use '0'
 */
#define ASSIGN_PIN(pin, group, gpio_pin)                                                            \
    {                                                                                               \
        pin, GPIO_Pin_##gpio_pin, GPIO_PortSourceGPIO##group, GPIO_PinSource##gpio_pin, GPIO##group \
    }
#define NOT_USE_PIN    \
    {                  \
        -1, 0, 0, 0, 0 \
    }

static const struct pin_info pin_info_list[] = {
#if defined(GPIOA)
    ASSIGN_PIN(0, A, 0),
    ASSIGN_PIN(1, A, 1),
    ASSIGN_PIN(2, A, 2),
    ASSIGN_PIN(3, A, 3),
    ASSIGN_PIN(4, A, 4),
    ASSIGN_PIN(5, A, 5),
    ASSIGN_PIN(6, A, 6),
    ASSIGN_PIN(7, A, 7),
    ASSIGN_PIN(8, A, 8),
    ASSIGN_PIN(9, A, 9),
    ASSIGN_PIN(10, A, 10),
    ASSIGN_PIN(11, A, 11),
    ASSIGN_PIN(12, A, 12),
    ASSIGN_PIN(13, A, 13),
    ASSIGN_PIN(14, A, 14),
    ASSIGN_PIN(15, A, 15),
#endif
#if defined(GPIOB)
    ASSIGN_PIN(16, B, 0),
    ASSIGN_PIN(17, B, 1),
    ASSIGN_PIN(18, B, 2),
    ASSIGN_PIN(19, B, 3),
    ASSIGN_PIN(20, B, 4),
    ASSIGN_PIN(21, B, 5),
    ASSIGN_PIN(22, B, 6),
    ASSIGN_PIN(23, B, 7),
    ASSIGN_PIN(24, B, 8),
    ASSIGN_PIN(25, B, 9),
    ASSIGN_PIN(26, B, 10),
    ASSIGN_PIN(27, B, 11),
    ASSIGN_PIN(28, B, 12),
    ASSIGN_PIN(29, B, 13),
    ASSIGN_PIN(30, B, 14),
    ASSIGN_PIN(31, B, 15),
#endif
#if defined(GPIOC)
    ASSIGN_PIN(32, C, 0),
    ASSIGN_PIN(33, C, 1),
    ASSIGN_PIN(34, C, 2),
    ASSIGN_PIN(35, C, 3),
    ASSIGN_PIN(36, C, 4),
    ASSIGN_PIN(37, C, 5),
    ASSIGN_PIN(38, C, 6),
    ASSIGN_PIN(39, C, 7),
    ASSIGN_PIN(40, C, 8),
    ASSIGN_PIN(41, C, 9),
    ASSIGN_PIN(42, C, 10),
    ASSIGN_PIN(43, C, 11),
    ASSIGN_PIN(44, C, 12),
    ASSIGN_PIN(45, C, 13),
    ASSIGN_PIN(46, C, 14),
    ASSIGN_PIN(47, C, 15),
#endif
#if defined(GPIOD)
    ASSIGN_PIN(48, D, 0),
    ASSIGN_PIN(49, D, 1),
    ASSIGN_PIN(50, D, 2),
    ASSIGN_PIN(51, D, 3),
    ASSIGN_PIN(52, D, 4),
    ASSIGN_PIN(53, D, 5),
    ASSIGN_PIN(54, D, 6),
    ASSIGN_PIN(55, D, 7),
    ASSIGN_PIN(56, D, 8),
    ASSIGN_PIN(57, D, 9),
    ASSIGN_PIN(58, D, 10),
    ASSIGN_PIN(59, D, 11),
    ASSIGN_PIN(60, D, 12),
    ASSIGN_PIN(61, D, 13),
    ASSIGN_PIN(62, D, 14),
    ASSIGN_PIN(63, D, 15),
#endif
#if defined(GPIOE)
    ASSIGN_PIN(64, E, 0),
    ASSIGN_PIN(65, E, 1),
    ASSIGN_PIN(66, E, 2),
    ASSIGN_PIN(67, E, 3),
    ASSIGN_PIN(68, E, 4),
    ASSIGN_PIN(69, E, 5),
    ASSIGN_PIN(70, E, 6),
    ASSIGN_PIN(71, E, 7),
    ASSIGN_PIN(72, E, 8),
    ASSIGN_PIN(73, E, 9),
    ASSIGN_PIN(74, E, 10),
    ASSIGN_PIN(75, E, 11),
    ASSIGN_PIN(76, E, 12),
    ASSIGN_PIN(77, E, 13),
    ASSIGN_PIN(78, E, 14),
    ASSIGN_PIN(79, E, 15),
#endif
};

static const struct pin_info *pin_info_list_find(rt_base_t pin)
{
    const struct pin_info *item = RT_NULL;

    if ((pin != -1) && (pin < ITEM_NUM(pin_info_list)))
    {
        item = pin_info_list[pin].pin == -1 ? RT_NULL : &pin_info_list[pin];
    }

    return item;
}

static rt_base_t pin_info_list_find_pin(rt_uint16_t portsource, rt_uint16_t pinsource)
{
    rt_base_t pin = -1;
    int index;

    for (index = 0; index < ITEM_NUM(pin_info_list); index++)
    {
        if (pin_info_list[index].portsource == portsource && pin_info_list[index].pinsource == pinsource)
        {
            pin = pin_info_list[index].pin;

            break;
        }
    }

    return pin;
}

/*
 *use: 0 using the exti line, -1 do not using
 */
struct exti_line_irq
{
    rt_uint16_t nvic_priority;
    rt_uint16_t nvic_subpriority;
    rt_uint32_t exit_line;
    IRQn_Type irqn;
    int use;
    struct rt_pin_irq_hdr bind_irq_hdr;
};

static struct exti_line_irq exti_line_irq_list[] = {
    {5, 0, EXTI_Line0, EXTI0_IRQn, 0, {
                                          .pin = -1,
                                      }},
    {5, 0, EXTI_Line1, EXTI1_IRQn, 0, {
                                          .pin = -1,
                                      }},
    {5, 0, EXTI_Line2, EXTI2_IRQn, 0, {
                                          .pin = -1,
                                      }},
    {5, 0, EXTI_Line3, EXTI3_IRQn, 0, {
                                          .pin = -1,
                                      }},
    {5, 0, EXTI_Line4, EXTI4_IRQn, 0, {
                                          .pin = -1,
                                      }},
    {5, 0, EXTI_Line5, EXTI9_5_IRQn, 0, {
                                            .pin = -1,
                                        }},
    {5, 0, EXTI_Line6, EXTI9_5_IRQn, 0, {
                                            .pin = -1,
                                        }},
    {5, 0, EXTI_Line7, EXTI9_5_IRQn, 0, {
                                            .pin = -1,
                                        }},
    {5, 0, EXTI_Line8, EXTI9_5_IRQn, 0, {
                                            .pin = -1,
                                        }},
    {5, 0, EXTI_Line9, EXTI9_5_IRQn, 0, {
                                            .pin = -1,
                                        }},
    {5, 0, EXTI_Line10, EXTI15_10_IRQn, 0, {
                                               .pin = -1,
                                           }},
    {5, 0, EXTI_Line11, EXTI15_10_IRQn, 0, {
                                               .pin = -1,
                                           }},
    {5, 0, EXTI_Line12, EXTI15_10_IRQn, 0, {
                                               .pin = -1,
                                           }},
    {5, 0, EXTI_Line13, EXTI15_10_IRQn, 0, {
                                               .pin = -1,
                                           }},
    {5, 0, EXTI_Line14, EXTI15_10_IRQn, 0, {
                                               .pin = -1,
                                           }},
    {5, 0, EXTI_Line15, EXTI15_10_IRQn, 0, {
                                               .pin = -1,
                                           }},
};

static struct exti_line_irq *exti_line_irq_list_find(rt_int16_t pin)
{
    struct exti_line_irq *item = RT_NULL;
    int index;

    for (index = 0; index < ITEM_NUM(exti_line_irq_list); index++)
    {
        if (exti_line_irq_list[index].bind_irq_hdr.pin == pin)
        {
            item = &exti_line_irq_list[index];
            break;
        }
    }

    return item;
}

static rt_err_t exti_line_irq_list_bind(struct rt_pin_irq_hdr *irq_hdr)
{
    rt_err_t ret = RT_EFULL;
    rt_base_t level;
    struct exti_line_irq *item;
    int index;

    for (index = 0; index < ITEM_NUM(exti_line_irq_list); index++)
    {
        if (exti_line_irq_list[index].bind_irq_hdr.pin == -1 && exti_line_irq_list[index].use != -1)
        {
            item = &exti_line_irq_list[index];
            break;
        }
    }

    if (item != RT_NULL)
    {
        level = rt_hw_interrupt_disable();
        item->bind_irq_hdr.pin = irq_hdr->pin;
        item->bind_irq_hdr.mode = irq_hdr->mode;
        item->bind_irq_hdr.hdr = irq_hdr->hdr;
        item->bind_irq_hdr.args = irq_hdr->args;
        rt_hw_interrupt_enable(level);

        ret = RT_EOK;
    }

    return ret;
}

static rt_err_t exti_line_irq_list_unbind(rt_int16_t pin)
{
    rt_err_t ret = RT_EEMPTY;
    rt_base_t level;
    struct exti_line_irq *item;

    item = exti_line_irq_list_find(pin);

    if (item != RT_NULL)
    {
        level = rt_hw_interrupt_disable();

        item->bind_irq_hdr.pin = -1;

        rt_hw_interrupt_enable(level);

        ret = RT_EOK;
    }

    return ret;
}

void ch32f2_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    const struct pin_info *item;
    GPIO_InitTypeDef gpio_initstruct;

    item = pin_info_list_find(pin);

    if (item == RT_NULL)
    {
        return;
    }

    gpio_initstruct.GPIO_Pin = item->gpio_pin;
    gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;

    if (mode == PIN_MODE_OUTPUT)
    {
        gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        gpio_initstruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        gpio_initstruct.GPIO_Mode = GPIO_Mode_IPU;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        gpio_initstruct.GPIO_Mode = GPIO_Mode_IPD;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_OD;
    }

    GPIO_Init(item->gpio, &gpio_initstruct);
}

void ch32f2_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    const struct pin_info *item;

    item = pin_info_list_find(pin);

    if (item == RT_NULL)
    {
        return;
    }

    GPIO_WriteBit(item->gpio, item->gpio_pin, (BitAction)value);
}

rt_int8_t ch32f2_pin_read(rt_device_t dev, rt_base_t pin)
{
    const struct pin_info *item;

    item = pin_info_list_find(pin);

    if (item == RT_NULL)
    {
        return PIN_LOW;
    }

    return GPIO_ReadInputDataBit(item->gpio, item->gpio_pin);
}

rt_err_t ch32f2_pin_attach_irq(struct rt_device *device, rt_base_t pin, rt_uint8_t mode, void (*hdr)(void *args),
                               void *args)
{
    struct rt_pin_irq_hdr bind_item;

    bind_item.pin = pin;
    bind_item.mode = mode;
    bind_item.hdr = hdr;
    bind_item.args = args;

    return exti_line_irq_list_bind(&bind_item);
}

rt_err_t ch32f2_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    return exti_line_irq_list_unbind(pin);
}

rt_err_t ch32f2_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    struct exti_line_irq *find;
    const struct pin_info *item;
    rt_base_t level;

    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    find = exti_line_irq_list_find(pin);

    if (find == RT_NULL)
        return -RT_EINVAL;

    item = pin_info_list_find(pin);

    if (item == RT_NULL)
        return -RT_EINVAL;

    if (enabled == PIN_IRQ_ENABLE)
    {

        level = rt_hw_interrupt_disable();

        GPIO_EXTILineConfig(item->portsource, item->pinsource);
        EXTI_InitStructure.EXTI_Line = find->exit_line;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

        switch (find->bind_irq_hdr.mode)
        {
        case PIN_IRQ_MODE_RISING:
        {
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
            break;
        }
        case PIN_IRQ_MODE_FALLING:
        {
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
            break;
        }
        case PIN_IRQ_MODE_RISING_FALLING:
        {
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
            break;
        }
        default:
            break;
        }

        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_Init(&EXTI_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel = find->irqn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = find->nvic_priority;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = find->nvic_subpriority;

        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        rt_hw_interrupt_enable(level);
    }
    else
    {
        level = rt_hw_interrupt_disable();

        EXTI_InitStructure.EXTI_Line = find->exit_line;
        EXTI_InitStructure.EXTI_LineCmd = DISABLE;
        EXTI_Init(&EXTI_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&NVIC_InitStructure);

        rt_hw_interrupt_enable(level);
    }

    return RT_EOK;
}

/*PX.XX*/
rt_base_t ch32f2_pin_get(const char *name)
{
    rt_uint16_t portsource, pinsource;
    int sz;

    sz = rt_strlen(name);

    if (sz == 4)
    {
        portsource = name[1] - 0x41;
        pinsource = name[3] - 0x30;
        return pin_info_list_find_pin(portsource, pinsource);
    }

    if (sz == 5)
    {
        portsource = name[1];
        pinsource = (name[3] - 0x30) * 10 + (name[4] - 0x30);
        return pin_info_list_find_pin(portsource, pinsource);
    }

    return -1;
}

const static struct rt_pin_ops pin_ops = {
    .pin_mode = ch32f2_pin_mode,
    .pin_write = ch32f2_pin_write,
    .pin_read = ch32f2_pin_read,
    .pin_attach_irq = ch32f2_pin_attach_irq,
    .pin_detach_irq = ch32f2_pin_detach_irq,
    .pin_irq_enable = ch32f2_pin_irq_enable,
    .pin_get = ch32f2_pin_get,
};

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
#ifdef GPIOE
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
#endif
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    return rt_device_pin_register("pin", &pin_ops, RT_NULL);
}

rt_inline void exti_irq_handler(rt_uint16_t seq)
{
    if (EXTI_GetITStatus(exti_line_irq_list[seq].exit_line) == SET)
    {
        EXTI_ClearITPendingBit(exti_line_irq_list[seq].exit_line);

        if (exti_line_irq_list[seq].use != -1 &&
            exti_line_irq_list[seq].bind_irq_hdr.pin != -1 &&
            exti_line_irq_list[seq].bind_irq_hdr.hdr != RT_NULL)
        {
            exti_line_irq_list[seq].bind_irq_hdr.hdr(exti_line_irq_list[seq].bind_irq_hdr.args);
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

#endif /* RT_USING_PIN */
