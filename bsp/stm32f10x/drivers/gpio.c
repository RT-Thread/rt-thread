/*
 * File      : gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-03-24     Bright      the first version
 */

#include <rthw.h>
#include <rtdevice.h>
#include <board.h>
#include <gpio.h>

#ifdef RT_USING_PIN

#define STM32F10X_PIN_NUMBERS 100 //[ 64, 100, 144 ]

#define __STM32_PIN(index, rcc, gpio, gpio_index) { 0, RCC_##rcc##Periph_GPIO##gpio, GPIO##gpio, GPIO_Pin_##gpio_index}
#define __STM32_PIN_DEFAULT {-1, 0, 0, 0}

/* STM32 GPIO driver */
struct pin_index
{
    int index;
    uint32_t rcc;
    GPIO_TypeDef *gpio;
    uint32_t pin;
};

static const struct pin_index pins[] =
{
#if (STM32F10X_PIN_NUMBERS == 64)
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(2, APB2, C, 13),
    __STM32_PIN(3, APB2, C, 14),
    __STM32_PIN(4, APB2, C, 15),
    __STM32_PIN(5, APB2, D, 0),
    __STM32_PIN(6, APB2, D, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(8, APB2, C, 0),
    __STM32_PIN(9, APB2, C, 1),
    __STM32_PIN(10, APB2, C, 2),
    __STM32_PIN(11, APB2, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(14, APB2, A, 0),
    __STM32_PIN(15, APB2, A, 1),
    __STM32_PIN(16, APB2, A, 2),
    __STM32_PIN(17, APB2, A, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(20, APB2, A, 4),
    __STM32_PIN(21, APB2, A, 5),
    __STM32_PIN(22, APB2, A, 6),
    __STM32_PIN(23, APB2, A, 7),
    __STM32_PIN(24, APB2, C, 4),
    __STM32_PIN(25, APB2, C, 5),
    __STM32_PIN(26, APB2, B, 0),
    __STM32_PIN(27, APB2, B, 1),
    __STM32_PIN(28, APB2, B, 2),
    __STM32_PIN(29, APB2, B, 10),
    __STM32_PIN(30, APB2, B, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(33, APB2, B, 12),
    __STM32_PIN(34, APB2, B, 13),
    __STM32_PIN(35, APB2, B, 14),
    __STM32_PIN(36, APB2, B, 15),
    __STM32_PIN(37, APB2, C, 6),
    __STM32_PIN(38, APB2, C, 7),
    __STM32_PIN(39, APB2, C, 8),
    __STM32_PIN(40, APB2, C, 9),
    __STM32_PIN(41, APB2, A, 8),
    __STM32_PIN(42, APB2, A, 9),
    __STM32_PIN(43, APB2, A, 10),
    __STM32_PIN(44, APB2, A, 11),
    __STM32_PIN(45, APB2, A, 12),
    __STM32_PIN(46, APB2, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(49, APB2, A, 14),
    __STM32_PIN(50, APB2, A, 15),
    __STM32_PIN(51, APB2, C, 10),
    __STM32_PIN(52, APB2, C, 11),
    __STM32_PIN(53, APB2, C, 12),
    __STM32_PIN(54, APB2, D, 2),
    __STM32_PIN(55, APB2, B, 3),
    __STM32_PIN(56, APB2, B, 4),
    __STM32_PIN(57, APB2, B, 5),
    __STM32_PIN(58, APB2, B, 6),
    __STM32_PIN(59, APB2, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(61, APB2, B, 8),
    __STM32_PIN(62, APB2, B, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
#endif
#if (STM32F10X_PIN_NUMBERS == 100)
    __STM32_PIN_DEFAULT,
    __STM32_PIN(1, APB2, E, 2),
    __STM32_PIN(2, APB2, E, 3),
    __STM32_PIN(3, APB2, E, 4),
    __STM32_PIN(4, APB2, E, 5),
    __STM32_PIN(5, APB2, E, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(7, APB2, C, 13),
    __STM32_PIN(8, APB2, C, 14),
    __STM32_PIN(9, APB2, C, 15),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(15, APB2, C, 0),
    __STM32_PIN(16, APB2, C, 1),
    __STM32_PIN(17, APB2, C, 2),
    __STM32_PIN(18, APB2, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(23, APB2, A, 0),
    __STM32_PIN(24, APB2, A, 1),
    __STM32_PIN(25, APB2, A, 2),
    __STM32_PIN(26, APB2, A, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(29, APB2, A, 4),
    __STM32_PIN(30, APB2, A, 5),
    __STM32_PIN(31, APB2, A, 6),
    __STM32_PIN(32, APB2, A, 7),
    __STM32_PIN(33, APB2, C, 4),
    __STM32_PIN(34, APB2, C, 5),
    __STM32_PIN(35, APB2, B, 0),
    __STM32_PIN(36, APB2, B, 1),
    __STM32_PIN(37, APB2, B, 2),
    __STM32_PIN(38, APB2, E, 7),
    __STM32_PIN(39, APB2, E, 8),
    __STM32_PIN(40, APB2, E, 9),
    __STM32_PIN(41, APB2, E, 10),
    __STM32_PIN(42, APB2, E, 11),
    __STM32_PIN(43, APB2, E, 12),
    __STM32_PIN(44, APB2, E, 13),
    __STM32_PIN(45, APB2, E, 14),
    __STM32_PIN(46, APB2, E, 15),
    __STM32_PIN(47, APB2, B, 10),
    __STM32_PIN(48, APB2, B, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(51, APB2, B, 12),
    __STM32_PIN(52, APB2, B, 13),
    __STM32_PIN(53, APB2, B, 14),
    __STM32_PIN(54, APB2, B, 15),
    __STM32_PIN(55, APB2, D, 8),
    __STM32_PIN(56, APB2, D, 9),
    __STM32_PIN(57, APB2, D, 10),
    __STM32_PIN(58, APB2, D, 11),
    __STM32_PIN(59, APB2, D, 12),
    __STM32_PIN(60, APB2, D, 13),
    __STM32_PIN(61, APB2, D, 14),
    __STM32_PIN(62, APB2, D, 15),
    __STM32_PIN(63, APB2, C, 6),
    __STM32_PIN(64, APB2, C, 7),
    __STM32_PIN(65, APB2, C, 8),
    __STM32_PIN(66, APB2, C, 9),
    __STM32_PIN(67, APB2, A, 8),
    __STM32_PIN(68, APB2, A, 9),
    __STM32_PIN(69, APB2, A, 10),
    __STM32_PIN(70, APB2, A, 11),
    __STM32_PIN(71, APB2, A, 12),
    __STM32_PIN(72, APB2, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(76, APB2, A, 14),
    __STM32_PIN(77, APB2, A, 15),
    __STM32_PIN(78, APB2, C, 10),
    __STM32_PIN(79, APB2, C, 11),
    __STM32_PIN(80, APB2, C, 12),
    __STM32_PIN(81, APB2, D, 0),
    __STM32_PIN(82, APB2, D, 1),
    __STM32_PIN(83, APB2, D, 2),
    __STM32_PIN(84, APB2, D, 3),
    __STM32_PIN(85, APB2, D, 4),
    __STM32_PIN(86, APB2, D, 5),
    __STM32_PIN(87, APB2, D, 6),
    __STM32_PIN(88, APB2, D, 7),
    __STM32_PIN(89, APB2, B, 3),
    __STM32_PIN(90, APB2, B, 4),
    __STM32_PIN(91, APB2, B, 5),
    __STM32_PIN(92, APB2, B, 6),
    __STM32_PIN(93, APB2, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(95, APB2, B, 8),
    __STM32_PIN(96, APB2, B, 9),
    __STM32_PIN(97, APB2, E, 0),
    __STM32_PIN(98, APB2, E, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
#endif
#if (STM32F10X_PIN_NUMBERS == 144)
    __STM32_PIN_DEFAULT,
    __STM32_PIN(1, APB2, E, 2),
    __STM32_PIN(2, APB2, E, 3),
    __STM32_PIN(3, APB2, E, 4),
    __STM32_PIN(4, APB2, E, 5),
    __STM32_PIN(5, APB2, E, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(7, APB2, C, 13),
    __STM32_PIN(8, APB2, C, 14),
    __STM32_PIN(9, APB2, C, 15),
    
    __STM32_PIN(10, APB2, F, 0),
    __STM32_PIN(11, APB2, F, 1),
    __STM32_PIN(12, APB2, F, 2),
    __STM32_PIN(13, APB2, F, 3),
    __STM32_PIN(14, APB2, F, 4),
    __STM32_PIN(15, APB2, F, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(18, APB2, F, 6),
    __STM32_PIN(19, APB2, F, 7),
    __STM32_PIN(20, APB2, F, 8),
    __STM32_PIN(21, APB2, F, 9),
    __STM32_PIN(22, APB2, F, 10),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(26, APB2, C, 0),
    __STM32_PIN(27, APB2, C, 1),
    __STM32_PIN(28, APB2, C, 2),
    __STM32_PIN(29, APB2, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(34, APB2, A, 0),
    __STM32_PIN(35, APB2, A, 1),
    __STM32_PIN(36, APB2, A, 2),
    __STM32_PIN(37, APB2, A, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(40, APB2, A, 4),
    __STM32_PIN(41, APB2, A, 5),
    __STM32_PIN(42, APB2, A, 6),
    __STM32_PIN(43, APB2, A, 7),
    __STM32_PIN(44, APB2, C, 4),
    __STM32_PIN(45, APB2, C, 5),
    __STM32_PIN(46, APB2, B, 0),
    __STM32_PIN(47, APB2, B, 1),
    __STM32_PIN(48, APB2, B, 2),
    __STM32_PIN(49, APB2, F, 11),
    __STM32_PIN(50, APB2, F, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(53, APB2, F, 13),
    __STM32_PIN(54, APB2, F, 14),
    __STM32_PIN(55, APB2, F, 15),
    __STM32_PIN(56, APB2, G, 0),
    __STM32_PIN(57, APB2, G, 1),
    __STM32_PIN(58, APB2, E, 7),
    __STM32_PIN(59, APB2, E, 8),
    __STM32_PIN(60, APB2, E, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(63, APB2, E, 10),
    __STM32_PIN(64, APB2, E, 11),
    __STM32_PIN(65, APB2, E, 12),
    __STM32_PIN(66, APB2, E, 13),
    __STM32_PIN(67, APB2, E, 14),
    __STM32_PIN(68, APB2, E, 15),
    __STM32_PIN(69, APB2, B, 10),
    __STM32_PIN(70, APB2, B, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(73, APB2, B, 12),
    __STM32_PIN(74, APB2, B, 13),
    __STM32_PIN(75, APB2, B, 14),
    __STM32_PIN(76, APB2, B, 15),
    __STM32_PIN(77, APB2, D, 8),
    __STM32_PIN(78, APB2, D, 9),
    __STM32_PIN(79, APB2, D, 10),
    __STM32_PIN(80, APB2, D, 11),
    __STM32_PIN(81, APB2, D, 12),
    __STM32_PIN(82, APB2, D, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(85, APB2, D, 14),
    __STM32_PIN(86, APB2, D, 15),
    __STM32_PIN(87, APB2, G, 2),
    __STM32_PIN(88, APB2, G, 3),
    __STM32_PIN(89, APB2, G, 4),
    __STM32_PIN(90, APB2, G, 5),
    __STM32_PIN(91, APB2, G, 6),
    __STM32_PIN(92, APB2, G, 7),
    __STM32_PIN(93, APB2, G, 8),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(96, APB2, C, 6),
    __STM32_PIN(97, APB2, C, 7),
    __STM32_PIN(98, APB2, C, 8),
    __STM32_PIN(99, APB2, C, 9),
    __STM32_PIN(100, APB2, A, 8),
    __STM32_PIN(101, APB2, A, 9),
    __STM32_PIN(102, APB2, A, 10),
    __STM32_PIN(103, APB2, A, 11),
    __STM32_PIN(104, APB2, A, 12),
    __STM32_PIN(105, APB2, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(109, APB2, A, 14),
    __STM32_PIN(110, APB2, A, 15),
    __STM32_PIN(111, APB2, C, 10),
    __STM32_PIN(112, APB2, C, 11),
    __STM32_PIN(113, APB2, C, 12),
    __STM32_PIN(114, APB2, D, 0),
    __STM32_PIN(115, APB2, D, 1),
    __STM32_PIN(116, APB2, D, 2),
    __STM32_PIN(117, APB2, D, 3),
    __STM32_PIN(118, APB2, D, 4),
    __STM32_PIN(119, APB2, D, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(122, APB2, D, 6),
    __STM32_PIN(123, APB2, D, 7),
    __STM32_PIN(124, APB2, G, 9),
    __STM32_PIN(125, APB2, G, 10),
    __STM32_PIN(126, APB2, G, 11),
    __STM32_PIN(127, APB2, G, 12),
    __STM32_PIN(128, APB2, G, 13),
    __STM32_PIN(129, APB2, G, 14),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(132, APB2, G, 15),
    __STM32_PIN(133, APB2, B, 3),
    __STM32_PIN(134, APB2, B, 4),
    __STM32_PIN(135, APB2, B, 5),
    __STM32_PIN(136, APB2, B, 6),
    __STM32_PIN(137, APB2, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(139, APB2, B, 8),
    __STM32_PIN(140, APB2, B, 9),
    __STM32_PIN(141, APB2, E, 0),
    __STM32_PIN(142, APB2, E, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
#endif
};


#define ITEM_NUM(items) sizeof(items)/sizeof(items[0])
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

void stm32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
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

int stm32_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    const struct pin_index *index;

    value = PIN_LOW;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return value;
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

void stm32_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
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
    GPIO_Init(index->gpio, &GPIO_InitStructure);
}

const static struct rt_pin_ops _stm32_pin_ops =
{
    stm32_pin_mode,
    stm32_pin_write,
    stm32_pin_read,
};

int stm32_hw_pin_init(void)
{
    int result;
    
    result = rt_device_pin_register("pin", &_stm32_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(stm32_hw_pin_init);

#endif
