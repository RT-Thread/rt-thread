/*
 * File      : stm32f7xx_gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-26     ZYH      first implementation
 */
#include "stm32f7xx_gpio.h"
#include <rthw.h>
#include <rtdevice.h>
#include <board.h>
#ifdef RT_USING_PIN

#define STM32F767_PIN_NUMBERS 144 //[144]
#define __STM32_PIN(index, gpio, gpio_index) {index, GPIO##gpio##_CLK_ENABLE, GPIO##gpio, GPIO_PIN_##gpio_index}
#define __STM32_PIN_DEFAULT {-1, 0, 0, 0}


static void GPIOA_CLK_ENABLE(void)
{
#ifdef __HAL_RCC_GPIOA_CLK_ENABLE
    __HAL_RCC_GPIOA_CLK_ENABLE();
#endif
}
static void GPIOB_CLK_ENABLE(void)
{
#ifdef __HAL_RCC_GPIOB_CLK_ENABLE
    __HAL_RCC_GPIOB_CLK_ENABLE();
#endif
}
static void GPIOC_CLK_ENABLE(void)
{
#ifdef __HAL_RCC_GPIOC_CLK_ENABLE
    __HAL_RCC_GPIOC_CLK_ENABLE();
#endif
}
static void GPIOD_CLK_ENABLE(void)
{
#ifdef __HAL_RCC_GPIOD_CLK_ENABLE
    __HAL_RCC_GPIOD_CLK_ENABLE();
#endif
}
static void GPIOE_CLK_ENABLE(void)
{
#ifdef __HAL_RCC_GPIOE_CLK_ENABLE
    __HAL_RCC_GPIOE_CLK_ENABLE();
#endif
}
static void GPIOF_CLK_ENABLE(void)
{
#ifdef __HAL_RCC_GPIOF_CLK_ENABLE
    __HAL_RCC_GPIOF_CLK_ENABLE();
#endif
}
static void GPIOG_CLK_ENABLE(void)
{
#ifdef __HAL_RCC_GPIOG_CLK_ENABLE
    __HAL_RCC_GPIOG_CLK_ENABLE();
#endif
}
static void GPIOH_CLK_ENABLE(void)
{
#ifdef __HAL_RCC_GPIOH_CLK_ENABLE
    __HAL_RCC_GPIOH_CLK_ENABLE();
#endif
}


struct pin_index
{
    int index;
    void (*rcc)(void);
    GPIO_TypeDef *gpio;
    uint32_t pin;
};


static const struct pin_index pins[] =
{
#if (STM32F767_PIN_NUMBERS == 144)
    __STM32_PIN(0,E,2),
    __STM32_PIN(1,E,3),
    __STM32_PIN(2,E,4),
    __STM32_PIN(3,E,5),
    __STM32_PIN(4,E,6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(6,C,13),
    __STM32_PIN(7,C,14),
    __STM32_PIN(8,C,15),
    __STM32_PIN(9,F,0),
    __STM32_PIN(10,F,1),
    __STM32_PIN(11,F,2),
    __STM32_PIN(12,F,3),
    __STM32_PIN(13,F,4),
    __STM32_PIN(14,F,5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(17,F,6),
    __STM32_PIN(18,F,7),
    __STM32_PIN(19,F,8),
    __STM32_PIN(20,F,9),
    __STM32_PIN(21,F,10),
    __STM32_PIN(22,H,0),
    __STM32_PIN(23,H,1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(25,C,0),
    __STM32_PIN(26,C,1),
    __STM32_PIN(27,C,2),
    __STM32_PIN(28,C,3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(33,A,0),
    __STM32_PIN(34,A,1),
    __STM32_PIN(35,A,2),
    __STM32_PIN(36,A,3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(39,A,4),
    __STM32_PIN(40,A,5),
    __STM32_PIN(41,A,6),
    __STM32_PIN(42,A,7),
    __STM32_PIN(43,C,4),
    __STM32_PIN(44,C,5),
    __STM32_PIN(45,B,0),
    __STM32_PIN(46,B,1),
    __STM32_PIN(47,B,2),
    __STM32_PIN(48,F,11),
    __STM32_PIN(49,F,12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(52,F,13),
    __STM32_PIN(53,F,14),
    __STM32_PIN(54,F,15),
    __STM32_PIN(55,G,0),
    __STM32_PIN(56,G,1),
    __STM32_PIN(57,E,7),
    __STM32_PIN(58,E,8),
    __STM32_PIN(59,E,9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(62,E,10),
    __STM32_PIN(63,E,11),
    __STM32_PIN(64,E,12),
    __STM32_PIN(65,E,13),
    __STM32_PIN(66,E,14),
    __STM32_PIN(67,E,15),
    __STM32_PIN(68,B,10),
    __STM32_PIN(69,B,11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(72,B,12),
    __STM32_PIN(73,B,13),
    __STM32_PIN(74,B,14),
    __STM32_PIN(75,B,15),
    __STM32_PIN(76,D,8),
    __STM32_PIN(77,D,9),
    __STM32_PIN(78,D,10),
    __STM32_PIN(79,D,11),
    __STM32_PIN(80,D,12),
    __STM32_PIN(81,D,13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(84,D,14),
    __STM32_PIN(85,D,15),
    __STM32_PIN(86,G,2),
    __STM32_PIN(87,G,3),
    __STM32_PIN(88,G,4),
    __STM32_PIN(89,G,5),
    __STM32_PIN(90,G,6),
    __STM32_PIN(91,G,7),
    __STM32_PIN(92,G,8),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(95,C,6),
    __STM32_PIN(96,C,7),
    __STM32_PIN(97,C,8),
    __STM32_PIN(98,C,9),
    __STM32_PIN(99,A,8),
    __STM32_PIN(100,A,9),
    __STM32_PIN(101,A,10),
    __STM32_PIN(102,A,11),
    __STM32_PIN(103,A,12),
    __STM32_PIN(104,A,13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(108,A,14),
    __STM32_PIN(109,A,15),
    __STM32_PIN(110,C,10),
    __STM32_PIN(111,C,11),
    __STM32_PIN(112,C,12),
    __STM32_PIN(113,D,0),
    __STM32_PIN(114,D,1),
    __STM32_PIN(115,D,2),
    __STM32_PIN(116,D,3),
    __STM32_PIN(117,D,4),
    __STM32_PIN(118,D,5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(121,D,6),
    __STM32_PIN(122,D,7),
    __STM32_PIN(123,G,9),
    __STM32_PIN(124,G,10),
    __STM32_PIN(125,G,11),
    __STM32_PIN(126,G,12),
    __STM32_PIN(127,G,13),
    __STM32_PIN(128,G,14),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(131,G,15),
    __STM32_PIN(132,B,3),
    __STM32_PIN(133,B,4),
    __STM32_PIN(134,B,5),
    __STM32_PIN(135,B,6),
    __STM32_PIN(136,B,7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(138,B,8),
    __STM32_PIN(139,B,9),
    __STM32_PIN(140,E,0),
    __STM32_PIN(141,E,1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
#endif
};

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};

static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_PIN_0, EXTI0_IRQn},
    {GPIO_PIN_1, EXTI1_IRQn},
    {GPIO_PIN_2, EXTI2_IRQn},
    {GPIO_PIN_3, EXTI3_IRQn},
    {GPIO_PIN_4, EXTI4_IRQn},
    {GPIO_PIN_5, EXTI9_5_IRQn},
    {GPIO_PIN_6, EXTI9_5_IRQn},
    {GPIO_PIN_7, EXTI9_5_IRQn},
    {GPIO_PIN_8, EXTI9_5_IRQn},
    {GPIO_PIN_9, EXTI9_5_IRQn},
    {GPIO_PIN_10, EXTI15_10_IRQn},
    {GPIO_PIN_11, EXTI15_10_IRQn},
    {GPIO_PIN_12, EXTI15_10_IRQn},
    {GPIO_PIN_13, EXTI15_10_IRQn},
    {GPIO_PIN_14, EXTI15_10_IRQn},
    {GPIO_PIN_15, EXTI15_10_IRQn},
};


static struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
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

static const struct pin_index *get_pin(uint8_t pin)
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

static void stm32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    HAL_GPIO_WritePin(index->gpio, index->pin, (GPIO_PinState)value);
}


static int stm32_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    const struct pin_index *index;

    value = PIN_LOW;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return value;
    }

    value = HAL_GPIO_ReadPin(index->gpio, index->pin);

    return value;
}
static void stm32_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    const struct pin_index *index;
    GPIO_InitTypeDef GPIO_InitStruct;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    /* GPIO Periph clock enable */
    index->rcc();

    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.Pin = index->pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }

    HAL_GPIO_Init(index->gpio, &GPIO_InitStruct);
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
    if (mapindex < 0 || mapindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
};

static rt_err_t stm32_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
    rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
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
static rt_err_t stm32_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
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

rt_err_t stm32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                rt_uint32_t enabled)
{
    const struct pin_index *index;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    GPIO_InitTypeDef GPIO_InitStruct;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(index->pin);
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
    /* GPIO Periph clock enable */
    index->rcc();
    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.Pin = index->pin;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    switch (pin_irq_hdr_tab[irqindex].mode)
    {
    case PIN_IRQ_MODE_RISING:
        GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
        break;
    case PIN_IRQ_MODE_FALLING:
        GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
        break;
    }
    HAL_GPIO_Init(index->gpio, &GPIO_InitStruct);
    HAL_NVIC_SetPriority(irqmap->irqno, 5, 0);
    HAL_NVIC_EnableIRQ(irqmap->irqno);
    rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(index->pin);
        if (irqmap == RT_NULL)
        {
            return RT_ENOSYS;
        }
        HAL_NVIC_DisableIRQ(irqmap->irqno);
    }
    else
    {
        return RT_ENOSYS;
    }

    return RT_EOK;
}


const static struct rt_pin_ops _stm32_pin_ops =
{
    stm32_pin_mode,
    stm32_pin_write,
    stm32_pin_read,
    stm32_pin_attach_irq,
    stm32_pin_dettach_irq,
    stm32_pin_irq_enable,
};

int rt_hw_pin_init(void)
{
    int result;

    result = rt_device_pin_register("pin", &_stm32_pin_ops, RT_NULL);
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

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    pin_irq_hdr(bit2bitno(GPIO_Pin));
}
void EXTI0_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
    rt_interrupt_leave();
}
void EXTI1_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
    rt_interrupt_leave();
}
void EXTI2_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
    rt_interrupt_leave();
}
void EXTI3_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
    rt_interrupt_leave();
}
void EXTI4_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
    rt_interrupt_leave();
}
void EXTI9_5_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
    rt_interrupt_leave();
}
void EXTI15_10_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
    rt_interrupt_leave();
}
#endif

