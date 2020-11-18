/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-01-23     wangyq        the first version
 * 2019-11-01     wangyq        update libraries
 */

#include <rthw.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_gpio.h"
#include <ald_cmu.h>
#include <ald_gpio.h>

#ifdef RT_USING_PIN

#define __ES32F0_PIN(index, gpio, gpio_index) {index, GPIO##gpio, GPIO_PIN_##gpio_index}
#define __ES32F0_PIN_DEFAULT {-1, 0, 0}

/* ES32F0 GPIO driver */
struct pin_index
{
    int index;
    GPIO_TypeDef *gpio;
    uint32_t pin;
};

static const struct pin_index pins[] =
{
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(2, C, 13),
    __ES32F0_PIN(3, C, 14),
    __ES32F0_PIN(4, C, 15),
    __ES32F0_PIN(5, H, 0),
    __ES32F0_PIN(6, H, 1),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(8, C, 0),
    __ES32F0_PIN(9, C, 1),
    __ES32F0_PIN(10, C, 2),
    __ES32F0_PIN(11, C, 3),
    __ES32F0_PIN(12, H, 3),
    __ES32F0_PIN(13, H, 4),
    __ES32F0_PIN(14, A, 0),
    __ES32F0_PIN(15, A, 1),
    __ES32F0_PIN(16, A, 2),
    __ES32F0_PIN(17, A, 3),
    __ES32F0_PIN(18, F, 0),
    __ES32F0_PIN(19, F, 1),
    __ES32F0_PIN(20, A, 4),
    __ES32F0_PIN(21, A, 5),
    __ES32F0_PIN(22, A, 6),
    __ES32F0_PIN(23, A, 7),
    __ES32F0_PIN(24, C, 4),
    __ES32F0_PIN(25, C, 5),
    __ES32F0_PIN(26, B, 0),
    __ES32F0_PIN(27, B, 1),
    __ES32F0_PIN(28, B, 2),
    __ES32F0_PIN(29, B, 10),
    __ES32F0_PIN(30, B, 11),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(33, B, 12),
    __ES32F0_PIN(34, B, 13),
    __ES32F0_PIN(35, B, 14),
    __ES32F0_PIN(36, B, 15),
    __ES32F0_PIN(37, C, 6),
    __ES32F0_PIN(38, C, 7),
    __ES32F0_PIN(39, C, 8),
    __ES32F0_PIN(40, C, 9),
    __ES32F0_PIN(41, A, 8),
    __ES32F0_PIN(42, A, 9),
    __ES32F0_PIN(43, A, 10),
    __ES32F0_PIN(44, A, 11),
    __ES32F0_PIN(45, A, 12),
    __ES32F0_PIN(46, A, 13),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(49, A, 14),
    __ES32F0_PIN(50, A, 15),
    __ES32F0_PIN(51, C, 10),
    __ES32F0_PIN(52, C, 11),
    __ES32F0_PIN(53, C, 12),
    __ES32F0_PIN(54, D, 2),
    __ES32F0_PIN(55, B, 3),
    __ES32F0_PIN(56, B, 4),
    __ES32F0_PIN(57, B, 5),
    __ES32F0_PIN(58, B, 6),
    __ES32F0_PIN(59, B, 7),
    __ES32F0_PIN(60, H, 2),
    __ES32F0_PIN(61, B, 8),
    __ES32F0_PIN(62, B, 9),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
};

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};
static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_PIN_0, EXTI0_3_IRQn},
    {GPIO_PIN_1, EXTI0_3_IRQn},
    {GPIO_PIN_2, EXTI0_3_IRQn},
    {GPIO_PIN_3, EXTI0_3_IRQn},
    {GPIO_PIN_4, EXTI4_7_IRQn},
    {GPIO_PIN_5, EXTI4_7_IRQn},
    {GPIO_PIN_6, EXTI4_7_IRQn},
    {GPIO_PIN_7, EXTI4_7_IRQn},
    {GPIO_PIN_8, EXTI8_11_IRQn},
    {GPIO_PIN_9, EXTI8_11_IRQn},
    {GPIO_PIN_10, EXTI8_11_IRQn},
    {GPIO_PIN_11, EXTI8_11_IRQn},
    {GPIO_PIN_12, EXTI12_15_IRQn},
    {GPIO_PIN_13, EXTI12_15_IRQn},
    {GPIO_PIN_14, EXTI12_15_IRQn},
    {GPIO_PIN_15, EXTI12_15_IRQn},
};

struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
{
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
};

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
const struct pin_index *get_pin(uint8_t pin)
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

void es32f0_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    const struct pin_index *index;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    ald_gpio_write_pin(index->gpio, index->pin, value);
}

int es32f0_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    const struct pin_index *index;
    value = PIN_LOW;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return value;
    }
    value = ald_gpio_read_pin(index->gpio, index->pin);
    return value;
}

void es32f0_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    const struct pin_index *index;
    gpio_init_t gpio_initstruct;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    gpio_initstruct.mode = GPIO_MODE_OUTPUT;
    gpio_initstruct.func = GPIO_FUNC_1;
    gpio_initstruct.odrv = GPIO_OUT_DRIVE_NORMAL;
    gpio_initstruct.type = GPIO_TYPE_CMOS;
    gpio_initstruct.pupd = GPIO_FLOATING;
    gpio_initstruct.odos = GPIO_PUSH_PULL;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        gpio_initstruct.mode = GPIO_MODE_OUTPUT;
        gpio_initstruct.pupd = GPIO_FLOATING;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        gpio_initstruct.mode = GPIO_MODE_INPUT;
        gpio_initstruct.pupd = GPIO_FLOATING;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        gpio_initstruct.mode = GPIO_MODE_INPUT;
        gpio_initstruct.pupd = GPIO_PUSH_UP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        gpio_initstruct.mode = GPIO_MODE_INPUT;
        gpio_initstruct.pupd = GPIO_PUSH_DOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        gpio_initstruct.mode = GPIO_MODE_OUTPUT;
        gpio_initstruct.pupd = GPIO_FLOATING;
        gpio_initstruct.odos = GPIO_OPEN_DRAIN;
    }
    ald_gpio_init(index->gpio, index->pin, &gpio_initstruct);
}

rt_inline const struct pin_irq_map *get_pin_irq_map(rt_uint16_t gpio_pin)
{
    rt_int32_t mapindex = gpio_pin & 0x00FF;
    if (mapindex < 0 || mapindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
};

rt_err_t es32f0_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                               rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    /* pin no. convert to dec no. */
    for (irqindex = 0; irqindex < 16; irqindex++)
    {
        if ((0x01 << irqindex) == index->pin)
        {
            break;
        }
    }
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

rt_err_t es32f0_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = index->pin & 0x00FF;
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

rt_err_t es32f0_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                               rt_uint32_t enabled)
{
    const struct pin_index *index;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    /* Configure GPIO_InitStructure & EXTI_InitStructure */
    gpio_init_t gpio_initstruct;
    exti_init_t exti_initstruct;
    exti_initstruct.filter = DISABLE;
    exti_initstruct.cks = EXTI_FILTER_CLOCK_10K;
    exti_initstruct.filter_time = 0x0;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    if (enabled == PIN_IRQ_ENABLE)
    {
        /* pin no. convert to dec no. */
        for (irqindex = 0; irqindex < 16; irqindex++)
        {
            if ((0x01 << irqindex) == index->pin)
            {
                break;
            }
        }
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
        ald_gpio_exti_init(index->gpio, index->pin, &exti_initstruct);
        /* Configure GPIO_InitStructure */
        gpio_initstruct.mode = GPIO_MODE_INPUT;
        gpio_initstruct.func = GPIO_FUNC_1;
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            gpio_initstruct.pupd = GPIO_PUSH_DOWN;
            ald_gpio_exti_interrupt_config(index->pin, EXTI_TRIGGER_RISING_EDGE, ENABLE);
            break;
        case PIN_IRQ_MODE_FALLING:
            gpio_initstruct.pupd = GPIO_PUSH_UP;
            ald_gpio_exti_interrupt_config(index->pin, EXTI_TRIGGER_TRAILING_EDGE, ENABLE);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            gpio_initstruct.pupd = GPIO_FLOATING;
            ald_gpio_exti_interrupt_config(index->pin, EXTI_TRIGGER_BOTH_EDGE, ENABLE);
            break;
        }
        ald_gpio_init(index->gpio, index->pin, &gpio_initstruct);
        NVIC_EnableIRQ(irqmap->irqno);
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(index->pin);
        if (irqmap == RT_NULL)
        {
            return RT_ENOSYS;
        }
        NVIC_DisableIRQ(irqmap->irqno);
    }
    else
    {
        return RT_ENOSYS;
    }
    return RT_EOK;
}

const static struct rt_pin_ops _es32f0_pin_ops =
{
    es32f0_pin_mode,
    es32f0_pin_write,
    es32f0_pin_read,
    es32f0_pin_attach_irq,
    es32f0_pin_detach_irq,
    es32f0_pin_irq_enable,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
    int result;
    ald_cmu_perh_clock_config(CMU_PERH_GPIO, ENABLE);
    result = rt_device_pin_register("pin", &_es32f0_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

rt_inline void pin_irq_hdr(uint16_t GPIO_Pin)
{
    uint16_t irqno;
    /* pin no. convert to dec no. */
    for (irqno = 0; irqno < 16; irqno++)
    {
        if ((0x01 << irqno) == GPIO_Pin)
        {
            break;
        }
    }
    if (irqno == 16)
        return;
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (ald_gpio_exti_get_flag_status(GPIO_Pin) != RESET)
    {
        ald_gpio_exti_clear_flag_status(GPIO_Pin);
        pin_irq_hdr(GPIO_Pin);
    }
}

void EXTI0_3_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_0);
    GPIO_EXTI_Callback(GPIO_PIN_1);
    GPIO_EXTI_Callback(GPIO_PIN_2);
    GPIO_EXTI_Callback(GPIO_PIN_3);
    rt_interrupt_leave();
}

void EXTI4_7_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_4);
    GPIO_EXTI_Callback(GPIO_PIN_5);
    GPIO_EXTI_Callback(GPIO_PIN_6);
    GPIO_EXTI_Callback(GPIO_PIN_7);
    rt_interrupt_leave();
}

void EXTI8_11_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_8);
    GPIO_EXTI_Callback(GPIO_PIN_9);
    GPIO_EXTI_Callback(GPIO_PIN_10);
    GPIO_EXTI_Callback(GPIO_PIN_11);
    rt_interrupt_leave();
}

void EXTI12_15_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_12);
    GPIO_EXTI_Callback(GPIO_PIN_13);
    GPIO_EXTI_Callback(GPIO_PIN_14);
    GPIO_EXTI_Callback(GPIO_PIN_15);
    rt_interrupt_leave();
}

#endif
