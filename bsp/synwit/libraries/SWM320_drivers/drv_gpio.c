/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 * 2018-12-10     Zohar_Lee    fix bug
 * 2020-07-10     lik          rewrite
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
#define GPIO0 ((GPIO_TypeDef *)(0))
#define GPIO0_IRQn (GPIOA0_IRQn)

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

        __SWM_PIN(13, B, 0),
        __SWM_PIN(14, B, 1),
        __SWM_PIN(15, B, 2),
        __SWM_PIN(16, B, 3),
        __SWM_PIN(17, B, 4),
        __SWM_PIN(18, B, 5),
        __SWM_PIN(19, B, 6),
        __SWM_PIN(20, B, 7),
        __SWM_PIN(21, B, 8),
        __SWM_PIN(22, B, 9),
        __SWM_PIN(23, B, 10),
        __SWM_PIN(24, B, 11),
        __SWM_PIN(25, B, 12),

        __SWM_PIN(26, C, 0),
        __SWM_PIN(27, C, 1),
        __SWM_PIN(28, C, 2),
        __SWM_PIN(29, C, 3),
        __SWM_PIN(30, C, 4),
        __SWM_PIN(31, C, 5),
        __SWM_PIN(32, C, 6),
        __SWM_PIN(33, C, 7),

        __SWM_PIN(34, M, 0),
        __SWM_PIN(35, M, 1),
        __SWM_PIN(36, M, 2),
        __SWM_PIN(37, M, 3),
        __SWM_PIN(38, M, 4),
        __SWM_PIN(39, M, 5),
        __SWM_PIN(40, M, 6),
        __SWM_PIN(41, M, 7),
        __SWM_PIN(42, M, 8),
        __SWM_PIN(43, M, 9),
        __SWM_PIN(44, M, 10),
        __SWM_PIN(45, M, 11),
        __SWM_PIN(46, M, 12),
        __SWM_PIN(47, M, 13),
        __SWM_PIN(48, M, 14),
        __SWM_PIN(49, M, 15),
        __SWM_PIN(50, M, 16),
        __SWM_PIN(51, M, 17),
        __SWM_PIN(52, M, 18),
        __SWM_PIN(53, M, 19),
        __SWM_PIN(54, M, 20),
        __SWM_PIN(55, M, 21),

        __SWM_PIN(56, N, 0),
        __SWM_PIN(57, N, 1),
        __SWM_PIN(58, N, 2),
        __SWM_PIN(59, N, 3),
        __SWM_PIN(60, N, 4),
        __SWM_PIN(61, N, 5),
        __SWM_PIN(62, N, 6),
        __SWM_PIN(63, N, 7),
        __SWM_PIN(64, N, 8),
        __SWM_PIN(65, N, 9),
        __SWM_PIN(66, N, 10),
        __SWM_PIN(67, N, 11),
        __SWM_PIN(68, N, 12),
        __SWM_PIN(69, N, 13),
        __SWM_PIN(70, N, 14),
        __SWM_PIN(71, N, 15),
        __SWM_PIN(72, N, 16),
        __SWM_PIN(73, N, 17),
        __SWM_PIN(74, N, 18),
        __SWM_PIN(75, N, 19),

        __SWM_PIN(76, P, 0),
        __SWM_PIN(77, P, 1),
        __SWM_PIN(78, P, 2),
        __SWM_PIN(79, P, 3),
        __SWM_PIN(80, P, 4),
        __SWM_PIN(81, P, 5),
        __SWM_PIN(82, P, 6),
        __SWM_PIN(83, P, 7),
        __SWM_PIN(84, P, 8),
        __SWM_PIN(85, P, 9),
        __SWM_PIN(86, P, 10),
        __SWM_PIN(87, P, 11),
        __SWM_PIN(88, P, 12),
        __SWM_PIN(89, P, 13),
        __SWM_PIN(90, P, 14),
        __SWM_PIN(91, P, 15),
        __SWM_PIN(92, P, 16),
        __SWM_PIN(93, P, 17),
        __SWM_PIN(94, P, 18),
        __SWM_PIN(95, P, 19),
        __SWM_PIN(96, P, 20),
        __SWM_PIN(97, P, 21),
        __SWM_PIN(98, P, 22),
        __SWM_PIN(99, P, 23)};

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
        {99, 0, RT_NULL, RT_NULL}};

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
        pull_up = 1;
        break;
    }

    GPIO_Init(gpio_obj->gpio, gpio_obj->pin, dir, pull_up, pull_down);
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
            GPIO_Init(gpio_obj->gpio, gpio_obj->pin, 0, 0, 1);
            EXTI_Init(gpio_obj->gpio, gpio_obj->pin, EXTI_RISE_EDGE);
            break;
        case PIN_IRQ_MODE_FALLING:
            GPIO_Init(gpio_obj->gpio, gpio_obj->pin, 0, 1, 0);
            EXTI_Init(gpio_obj->gpio, gpio_obj->pin, EXTI_FALL_EDGE);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            GPIO_Init(gpio_obj->gpio, gpio_obj->pin, 0, 1, 1);
            EXTI_Init(gpio_obj->gpio, gpio_obj->pin, EXTI_BOTH_EDGE);
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            GPIO_Init(gpio_obj->gpio, gpio_obj->pin, 0, 0, 1);
            EXTI_Init(gpio_obj->gpio, gpio_obj->pin, EXTI_HIGH_LEVEL);
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            GPIO_Init(gpio_obj->gpio, gpio_obj->pin, 0, 1, 0);
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
            pin = 13;
        break;
        case 'C':
            pin = 26;
        break;
        case 'M':
            pin = 34;
        break;
        case 'N':
            pin = 56;
        break;
        case 'P':
            pin = 76;
        break;
        default:
            goto out;
    }

    for (i = 3; i < name_len; i++)
    {
        pin_num *= 10;
        pin_num += name[i] - '0';
    }
    if(pin_num < 24)
    {
        pin += pin_num;
    }
    else
    {
        goto out;
    }

    return pin;
out:
    rt_kprintf("PA0~PA12, PB0~PB12, PC0~PC7, PM0~PM21, PN0~PN19, PP0~PP23\n");
    return -RT_EINVAL;
}

const static struct rt_pin_ops swm_pin_ops =
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
    static int gpio[24];
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
                RT_ASSERT(index <= 24)
            }
        }
    }
    for (index = 0; index < 24; index++)
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

void GPIOP_Handler(void)
{
    rt_interrupt_enter();
    swm_pin_isr(GPIOP);
    rt_interrupt_leave();
}

int swm_pin_init(void)
{
    return rt_device_pin_register("pin", &swm_pin_ops, RT_NULL);
}

#endif /* BSP_USING_GPIO */
#endif /* RT_USING_PIN */
