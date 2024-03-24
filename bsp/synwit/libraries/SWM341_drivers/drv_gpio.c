/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-01     lik          first version
 */

#include "drv_gpio.h"

#ifdef RT_USING_PIN
#ifdef BSP_USING_GPIO

//#define DRV_DEBUG
#define LOG_TAG "drv.gpio"
#include <drv_log.h>

#define __SWM_PIN(index, gpio, pin_index)                    \
    {                                                        \
        index, GPIO##gpio, PIN##pin_index, GPIO##gpio##_IRQn \
    }

struct swm_pin_device
{
    uint32_t index;
    GPIO_TypeDef *gpio;
    uint32_t pin;
    IRQn_Type irq;
};

static const struct swm_pin_device pin_obj[] =
    {
        __SWM_PIN(0, A, 0),
        __SWM_PIN(1, A, 1),
        __SWM_PIN(2, A, 2),
        __SWM_PIN(3, A, 3),
        __SWM_PIN(4, A, 4),
        __SWM_PIN(5, A, 5),
        __SWM_PIN(6, A, 6),
        __SWM_PIN(7, A, 7),
        __SWM_PIN(8, A, 8),
        __SWM_PIN(9, A, 9),
        __SWM_PIN(10, A, 10),
        __SWM_PIN(11, A, 11),
        __SWM_PIN(12, A, 12),
        __SWM_PIN(13, A, 13),
        __SWM_PIN(14, A, 14),
        __SWM_PIN(15, A, 15),

        __SWM_PIN(16, B, 0),
        __SWM_PIN(17, B, 1),
        __SWM_PIN(18, B, 2),
        __SWM_PIN(19, B, 3),
        __SWM_PIN(20, B, 4),
        __SWM_PIN(21, B, 5),
        __SWM_PIN(22, B, 6),
        __SWM_PIN(23, B, 7),
        __SWM_PIN(24, B, 8),
        __SWM_PIN(25, B, 9),
        __SWM_PIN(26, B, 10),
        __SWM_PIN(27, B, 11),
        __SWM_PIN(28, B, 12),
        __SWM_PIN(29, B, 13),
        __SWM_PIN(30, B, 14),
        __SWM_PIN(31, B, 15),

        __SWM_PIN(32, C, 0),
        __SWM_PIN(33, C, 1),
        __SWM_PIN(34, C, 2),
        __SWM_PIN(35, C, 3),
        __SWM_PIN(36, C, 4),
        __SWM_PIN(37, C, 5),
        __SWM_PIN(38, C, 6),
        __SWM_PIN(39, C, 7),
        __SWM_PIN(40, C, 8),
        __SWM_PIN(41, C, 9),
        __SWM_PIN(42, C, 10),
        __SWM_PIN(43, C, 11),
        __SWM_PIN(44, C, 12),
        __SWM_PIN(45, C, 13),
        __SWM_PIN(46, C, 14),
        __SWM_PIN(47, C, 15),

        __SWM_PIN(48, D, 0),
        __SWM_PIN(49, D, 1),
        __SWM_PIN(50, D, 2),
        __SWM_PIN(51, D, 3),
        __SWM_PIN(52, D, 4),
        __SWM_PIN(53, D, 5),
        __SWM_PIN(54, D, 6),
        __SWM_PIN(55, D, 7),
        __SWM_PIN(56, D, 8),
        __SWM_PIN(57, D, 9),
        __SWM_PIN(58, D, 10),
        __SWM_PIN(59, D, 11),
        __SWM_PIN(60, D, 12),
        __SWM_PIN(61, D, 13),
        __SWM_PIN(62, D, 14),
        __SWM_PIN(63, D, 15),

        __SWM_PIN(64, E, 0),
        __SWM_PIN(65, E, 1),
        __SWM_PIN(66, E, 2),
        __SWM_PIN(67, E, 3),
        __SWM_PIN(68, E, 4),
        __SWM_PIN(69, E, 5),
        __SWM_PIN(70, E, 6),
        __SWM_PIN(71, E, 7),
        __SWM_PIN(72, E, 8),
        __SWM_PIN(73, E, 9),
        __SWM_PIN(74, E, 10),
        __SWM_PIN(75, E, 11),
        __SWM_PIN(76, E, 12),
        __SWM_PIN(77, E, 13),
        __SWM_PIN(78, E, 14),
        __SWM_PIN(79, E, 15),

        __SWM_PIN(80, M, 0),
        __SWM_PIN(81, M, 1),
        __SWM_PIN(82, M, 2),
        __SWM_PIN(83, M, 3),
        __SWM_PIN(84, M, 4),
        __SWM_PIN(85, M, 5),
        __SWM_PIN(86, M, 6),
        __SWM_PIN(87, M, 7),
        __SWM_PIN(88, M, 8),
        __SWM_PIN(89, M, 9),
        __SWM_PIN(90, M, 10),
        __SWM_PIN(91, M, 11),
        __SWM_PIN(92, M, 12),
        __SWM_PIN(93, M, 13),
        __SWM_PIN(94, M, 14),
        __SWM_PIN(95, M, 15),

        __SWM_PIN(96, N, 0),
        __SWM_PIN(97, N, 1),
        __SWM_PIN(98, N, 2),
        __SWM_PIN(99, N, 3),
        __SWM_PIN(100, N, 4),
        __SWM_PIN(101, N, 5),
        __SWM_PIN(102, N, 6),
        __SWM_PIN(103, N, 7),
        __SWM_PIN(104, N, 8),
        __SWM_PIN(105, N, 9),
        __SWM_PIN(106, N, 10),
        __SWM_PIN(107, N, 11),
        __SWM_PIN(108, N, 12),
        __SWM_PIN(109, N, 13),
        __SWM_PIN(110, N, 14),
        __SWM_PIN(111, N, 15)};

static struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
    {
        {0, 0, RT_NULL, RT_NULL},
        {1, 0, RT_NULL, RT_NULL},
        {2, 0, RT_NULL, RT_NULL},
        {3, 0, RT_NULL, RT_NULL},
        {4, 0, RT_NULL, RT_NULL},
        {5, 0, RT_NULL, RT_NULL},
        {6, 0, RT_NULL, RT_NULL},
        {7, 0, RT_NULL, RT_NULL},
        {8, 0, RT_NULL, RT_NULL},
        {9, 0, RT_NULL, RT_NULL},
        {10, 0, RT_NULL, RT_NULL},
        {11, 0, RT_NULL, RT_NULL},
        {12, 0, RT_NULL, RT_NULL},
        {13, 0, RT_NULL, RT_NULL},
        {14, 0, RT_NULL, RT_NULL},
        {15, 0, RT_NULL, RT_NULL},
        {16, 0, RT_NULL, RT_NULL},
        {17, 0, RT_NULL, RT_NULL},
        {18, 0, RT_NULL, RT_NULL},
        {19, 0, RT_NULL, RT_NULL},
        {20, 0, RT_NULL, RT_NULL},
        {21, 0, RT_NULL, RT_NULL},
        {22, 0, RT_NULL, RT_NULL},
        {23, 0, RT_NULL, RT_NULL},
        {24, 0, RT_NULL, RT_NULL},
        {25, 0, RT_NULL, RT_NULL},
        {26, 0, RT_NULL, RT_NULL},
        {27, 0, RT_NULL, RT_NULL},
        {28, 0, RT_NULL, RT_NULL},
        {29, 0, RT_NULL, RT_NULL},
        {30, 0, RT_NULL, RT_NULL},
        {31, 0, RT_NULL, RT_NULL},
        {32, 0, RT_NULL, RT_NULL},
        {33, 0, RT_NULL, RT_NULL},
        {34, 0, RT_NULL, RT_NULL},
        {35, 0, RT_NULL, RT_NULL},
        {36, 0, RT_NULL, RT_NULL},
        {37, 0, RT_NULL, RT_NULL},
        {38, 0, RT_NULL, RT_NULL},
        {39, 0, RT_NULL, RT_NULL},
        {40, 0, RT_NULL, RT_NULL},
        {41, 0, RT_NULL, RT_NULL},
        {42, 0, RT_NULL, RT_NULL},
        {43, 0, RT_NULL, RT_NULL},
        {44, 0, RT_NULL, RT_NULL},
        {45, 0, RT_NULL, RT_NULL},
        {46, 0, RT_NULL, RT_NULL},
        {47, 0, RT_NULL, RT_NULL},
        {48, 0, RT_NULL, RT_NULL},
        {49, 0, RT_NULL, RT_NULL},
        {50, 0, RT_NULL, RT_NULL},
        {51, 0, RT_NULL, RT_NULL},
        {52, 0, RT_NULL, RT_NULL},
        {53, 0, RT_NULL, RT_NULL},
        {54, 0, RT_NULL, RT_NULL},
        {55, 0, RT_NULL, RT_NULL},
        {56, 0, RT_NULL, RT_NULL},
        {57, 0, RT_NULL, RT_NULL},
        {58, 0, RT_NULL, RT_NULL},
        {59, 0, RT_NULL, RT_NULL},
        {60, 0, RT_NULL, RT_NULL},
        {61, 0, RT_NULL, RT_NULL},
        {62, 0, RT_NULL, RT_NULL},
        {63, 0, RT_NULL, RT_NULL},
        {64, 0, RT_NULL, RT_NULL},
        {65, 0, RT_NULL, RT_NULL},
        {66, 0, RT_NULL, RT_NULL},
        {67, 0, RT_NULL, RT_NULL},
        {68, 0, RT_NULL, RT_NULL},
        {69, 0, RT_NULL, RT_NULL},
        {70, 0, RT_NULL, RT_NULL},
        {71, 0, RT_NULL, RT_NULL},
        {72, 0, RT_NULL, RT_NULL},
        {73, 0, RT_NULL, RT_NULL},
        {74, 0, RT_NULL, RT_NULL},
        {75, 0, RT_NULL, RT_NULL},
        {76, 0, RT_NULL, RT_NULL},
        {77, 0, RT_NULL, RT_NULL},
        {78, 0, RT_NULL, RT_NULL},
        {79, 0, RT_NULL, RT_NULL},
        {80, 0, RT_NULL, RT_NULL},
        {81, 0, RT_NULL, RT_NULL},
        {82, 0, RT_NULL, RT_NULL},
        {83, 0, RT_NULL, RT_NULL},
        {84, 0, RT_NULL, RT_NULL},
        {85, 0, RT_NULL, RT_NULL},
        {86, 0, RT_NULL, RT_NULL},
        {87, 0, RT_NULL, RT_NULL},
        {88, 0, RT_NULL, RT_NULL},
        {89, 0, RT_NULL, RT_NULL},
        {90, 0, RT_NULL, RT_NULL},
        {91, 0, RT_NULL, RT_NULL},
        {92, 0, RT_NULL, RT_NULL},
        {93, 0, RT_NULL, RT_NULL},
        {94, 0, RT_NULL, RT_NULL},
        {95, 0, RT_NULL, RT_NULL},
        {96, 0, RT_NULL, RT_NULL},
        {97, 0, RT_NULL, RT_NULL},
        {98, 0, RT_NULL, RT_NULL},
        {99, 0, RT_NULL, RT_NULL},
        {100, 0, RT_NULL, RT_NULL},
        {101, 0, RT_NULL, RT_NULL},
        {102, 0, RT_NULL, RT_NULL},
        {103, 0, RT_NULL, RT_NULL},
        {104, 0, RT_NULL, RT_NULL},
        {105, 0, RT_NULL, RT_NULL},
        {106, 0, RT_NULL, RT_NULL},
        {107, 0, RT_NULL, RT_NULL},
        {108, 0, RT_NULL, RT_NULL},
        {109, 0, RT_NULL, RT_NULL},
        {110, 0, RT_NULL, RT_NULL},
        {111, 0, RT_NULL, RT_NULL}};

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])

static const struct swm_pin_device *_pin2struct(uint8_t pin)
{
    const struct swm_pin_device *gpio_obj;

    if (pin < ITEM_NUM(pin_obj))
    {
        gpio_obj = &pin_obj[pin];
    }
    else
    {
        gpio_obj = RT_NULL;
    }

    return gpio_obj;
}

static void swm_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    const struct swm_pin_device *gpio_obj;
    int dir = 0;
    int pull_up = 0;
    int pull_down = 0;
    int open_drain = 0;

    gpio_obj = _pin2struct(pin);
    if (gpio_obj == RT_NULL)
    {
        return;
    }
    /* Configure GPIO_InitStructure */
    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        /* output setting */
        dir = 1;
        break;
    case PIN_MODE_INPUT:
        /* input setting: not pull. */
        dir = 0;
        break;
    case PIN_MODE_INPUT_PULLUP:
        /* input setting: pull up. */
        dir = 0;
        pull_up = 1;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        /* input setting: pull down. */
        dir = 0;
        pull_down = 1;
        break;
    case PIN_MODE_OUTPUT_OD:
        /* output setting: od. */
        dir = 1;
        open_drain = 1;
        break;
    }

    GPIO_Init(gpio_obj->gpio, gpio_obj->pin, dir, pull_up, pull_down, open_drain);
}

static void swm_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    const struct swm_pin_device *gpio_obj;

    gpio_obj = _pin2struct(pin);
    if (gpio_obj == RT_NULL)
    {
        return;
    }
    if (value)
    {
        GPIO_AtomicSetBit(gpio_obj->gpio, gpio_obj->pin);
    }
    else
    {
        GPIO_AtomicClrBit(gpio_obj->gpio, gpio_obj->pin);
    }
}

static rt_ssize_t swm_pin_read(rt_device_t dev, rt_base_t pin)
{
    const struct swm_pin_device *gpio_obj;

    gpio_obj = _pin2struct(pin);
    if (gpio_obj == RT_NULL)
    {
        return -RT_EINVAL;
    }
    return (rt_ssize_t)GPIO_GetBit(gpio_obj->gpio, gpio_obj->pin);
}

static rt_err_t swm_pin_attach_irq(struct rt_device *device,
                                   rt_base_t pin,
                                   rt_uint8_t mode,
                                   void (*hdr)(void *args),
                                   void *args)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[pin].pin == pin &&
        pin_irq_hdr_tab[pin].mode == mode &&
        pin_irq_hdr_tab[pin].hdr == hdr &&
        pin_irq_hdr_tab[pin].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[pin].pin = pin;
    pin_irq_hdr_tab[pin].mode = mode;
    pin_irq_hdr_tab[pin].hdr = hdr;
    pin_irq_hdr_tab[pin].args = args;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t swm_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    pin_irq_hdr_tab[pin].mode = 0;
    pin_irq_hdr_tab[pin].hdr = RT_NULL;
    pin_irq_hdr_tab[pin].args = RT_NULL;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t swm_pin_irq_enable(struct rt_device *device,
                                   rt_base_t pin,
                                   rt_uint8_t enabled)
{
    const struct swm_pin_device *gpio_obj;
    rt_base_t level = 0;

    gpio_obj = _pin2struct(pin);
    if (gpio_obj == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        switch (pin_irq_hdr_tab[pin].mode)
        {
        case PIN_IRQ_MODE_RISING:
            GPIO_Init(gpio_obj->gpio, gpio_obj->pin, 0, 0, 1, 0);
            EXTI_Init(gpio_obj->gpio, gpio_obj->pin, EXTI_RISE_EDGE);
            break;
        case PIN_IRQ_MODE_FALLING:
            GPIO_Init(gpio_obj->gpio, gpio_obj->pin, 0, 1, 0, 0);
            EXTI_Init(gpio_obj->gpio, gpio_obj->pin, EXTI_FALL_EDGE);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            GPIO_Init(gpio_obj->gpio, gpio_obj->pin, 0, 1, 1, 0);
            EXTI_Init(gpio_obj->gpio, gpio_obj->pin, EXTI_BOTH_EDGE);
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            GPIO_Init(gpio_obj->gpio, gpio_obj->pin, 0, 0, 1, 0);
            EXTI_Init(gpio_obj->gpio, gpio_obj->pin, EXTI_HIGH_LEVEL);
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            GPIO_Init(gpio_obj->gpio, gpio_obj->pin, 0, 1, 0, 0);
            EXTI_Init(gpio_obj->gpio, gpio_obj->pin, EXTI_LOW_LEVEL);
            break;
        default:
            return -RT_EINVAL;
        }

        level = rt_hw_interrupt_disable();
        NVIC_EnableIRQ(gpio_obj->irq);
        EXTI_Open(gpio_obj->gpio, gpio_obj->pin);
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        level = rt_hw_interrupt_disable();
        // NVIC_DisableIRQ(gpio_obj->irq);
        EXTI_Close(gpio_obj->gpio, gpio_obj->pin);
        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }
    return RT_EOK;
}

static rt_base_t swm_pin_get(const char *name)
{
    rt_base_t pin = 0;
    int pin_num = 0;
    int i, name_len;

    name_len = rt_strlen(name);

    if ((name_len < 4) || (name_len >= 6))
    {
        goto out;
    }
    if ((name[0] != 'P') || (name[2] != '.'))
    {
        goto out;
    }

    switch(name[1])
    {
        case 'A':
            pin = 0;
        break;
        case 'B':
            pin = 16;
        break;
        case 'C':
            pin = 32;
        break;
        case 'D':
            pin = 48;
        break;
        case 'E':
            pin = 64;
        break;
        case 'M':
            pin = 80;
        break;
        case 'N':
            pin = 96;
        break;
        default:
            goto out;
    }

    for (i = 3; i < name_len; i++)
    {
        pin_num *= 10;
        pin_num += name[i] - '0';
    }
    if(pin_num < 16)
    {
        pin += pin_num;
    }
    else
    {
        goto out;
    }

    return pin;
out:
    rt_kprintf("Px.y  x:A/B/C/D/E/M/N  y:0~15, e.g. PA.0\n");
    return -RT_EINVAL;
}

static const struct rt_pin_ops swm_pin_ops =
{
    .pin_mode = swm_pin_mode,
    .pin_write = swm_pin_write,
    .pin_read = swm_pin_read,
    .pin_attach_irq = swm_pin_attach_irq,
    .pin_detach_irq = swm_pin_detach_irq,
    .pin_irq_enable = swm_pin_irq_enable,
    .pin_get = swm_pin_get
};

static void swm_pin_isr(GPIO_TypeDef *GPIOx)
{
    static int gpio[16];
    int index = 0;
    static int init = 0;
    const struct swm_pin_device *gpio_obj;

    if (init == 0)
    {
        init = 1;
        for (gpio_obj = &pin_obj[0];
             gpio_obj->index < ITEM_NUM(pin_obj);
             gpio_obj++)
        {
            if (gpio_obj->gpio == GPIOx)
            {
                gpio[index] = gpio_obj->index;
                index++;
                RT_ASSERT(index <= 16)
            }
        }
    }
    for (index = 0; index < 16; index++)
    {
        gpio_obj = _pin2struct(gpio[index]);
        if (EXTI_State(gpio_obj->gpio, gpio_obj->pin))
        {
            EXTI_Clear(gpio_obj->gpio, gpio_obj->pin);
            if (pin_irq_hdr_tab[gpio_obj->index].hdr)
            {
                pin_irq_hdr_tab[gpio_obj->index].hdr(pin_irq_hdr_tab[gpio_obj->index].args);
            }
        }
    }
}

void GPIOA_Handler(void)
{
    rt_interrupt_enter();
    swm_pin_isr(GPIOA);
    rt_interrupt_leave();
}

void GPIOB_Handler(void)
{
    rt_interrupt_enter();
    swm_pin_isr(GPIOB);
    rt_interrupt_leave();
}

void GPIOC_Handler(void)
{
    rt_interrupt_enter();
    swm_pin_isr(GPIOC);
    rt_interrupt_leave();
}

void GPIOD_Handler(void)
{
    rt_interrupt_enter();
    swm_pin_isr(GPIOD);
    rt_interrupt_leave();
}

void GPIOE_Handler(void)
{
    rt_interrupt_enter();
    swm_pin_isr(GPIOE);
    rt_interrupt_leave();
}

void GPIOM_Handler(void)
{
    rt_interrupt_enter();
    swm_pin_isr(GPIOM);
    rt_interrupt_leave();
}

void GPION_Handler(void)
{
    rt_interrupt_enter();
    swm_pin_isr(GPION);
    rt_interrupt_leave();
}

int swm_pin_init(void)
{
    return rt_device_pin_register("pin", &swm_pin_ops, RT_NULL);
}

#endif /* BSP_USING_GPIO */
#endif /* RT_USING_PIN */
