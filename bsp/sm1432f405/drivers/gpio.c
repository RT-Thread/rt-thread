/*
 * File      : gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-03-24     armink            the first version
 */

#include <rthw.h>
#include <rtdevice.h>
#include <board.h>

#ifdef RT_USING_PIN

#define STM32_PIN_NUMBERS 100 //[48, 64, 100, 144 ]

#define __STM32_PIN(index, rcc, gpio, gpio_index) { 0, RCC_##rcc##Periph_GPIO##gpio, GPIO##gpio, GPIO_Pin_##gpio_index}
#define __STM32_PIN_DEFAULT {-1, 0, 0, 0}

#define ITEM_NUM(items) sizeof(items)/sizeof(items[0])

/* STM32 GPIO driver */
struct pin_index
{
    int index;
    uint32_t rcc;
    GPIO_TypeDef *gpio;
    uint32_t pin;
};

/* STM32 GPIO irq information */
struct pin_irq
{
    /* EXTI port source gpiox, such as EXTI_PortSourceGPIOA */
    rt_uint8_t port_source;
    /* EXTI pin sources, such as EXTI_PinSource0 */
    rt_uint8_t pin_source;
    /* NVIC IRQ EXTI channel, such as EXTI0_IRQn */
    enum IRQn irq_exti_channel;
    /* EXTI line, such as EXTI_Line0 */
    rt_uint32_t exti_line;
};

static const struct pin_index pins[] =
{
#if (STM32_PIN_NUMBERS == 48)
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(2, AHB1, C, 13),
    __STM32_PIN(3, AHB1, C, 14),
    __STM32_PIN(4, AHB1, C, 15),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(10, AHB1, A, 0),
    __STM32_PIN(11, AHB1, A, 1),
    __STM32_PIN(12, AHB1, A, 2),
    __STM32_PIN(13, AHB1, A, 3),
    __STM32_PIN(14, AHB1, A, 4),
    __STM32_PIN(15, AHB1, A, 5),
    __STM32_PIN(16, AHB1, A, 6),
    __STM32_PIN(17, AHB1, A, 7),
    __STM32_PIN(18, AHB1, B, 0),
    __STM32_PIN(19, AHB1, B, 1),
    __STM32_PIN(20, AHB1, B, 2),
    __STM32_PIN(21, AHB1, B, 10),
    __STM32_PIN(22, AHB1, B, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(25, AHB1, B, 12),
    __STM32_PIN(26, AHB1, B, 13),
    __STM32_PIN(27, AHB1, B, 14),
    __STM32_PIN(28, AHB1, B, 15),
    __STM32_PIN(29, AHB1, A, 8),
    __STM32_PIN(30, AHB1, A, 9),
    __STM32_PIN(31, AHB1, A, 10),
    __STM32_PIN(32, AHB1, A, 11),
    __STM32_PIN(33, AHB1, A, 12),
    __STM32_PIN(34, AHB1, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(37, AHB1, A, 14),
    __STM32_PIN(38, AHB1, A, 15),
    __STM32_PIN(39, AHB1, B, 3),
    __STM32_PIN(40, AHB1, B, 4),
    __STM32_PIN(41, AHB1, B, 5),
    __STM32_PIN(42, AHB1, B, 6),
    __STM32_PIN(43, AHB1, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(45, AHB1, B, 8),
    __STM32_PIN(46, AHB1, B, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,

#endif
#if (STM32_PIN_NUMBERS == 64)
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(2, AHB1, C, 13),
    __STM32_PIN(3, AHB1, C, 14),
    __STM32_PIN(4, AHB1, C, 15),
    __STM32_PIN(5, AHB1, D, 0),
    __STM32_PIN(6, AHB1, D, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(8, AHB1, C, 0),
    __STM32_PIN(9, AHB1, C, 1),
    __STM32_PIN(10, AHB1, C, 2),
    __STM32_PIN(11, AHB1, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(14, AHB1, A, 0),
    __STM32_PIN(15, AHB1, A, 1),
    __STM32_PIN(16, AHB1, A, 2),
    __STM32_PIN(17, AHB1, A, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(20, AHB1, A, 4),
    __STM32_PIN(21, AHB1, A, 5),
    __STM32_PIN(22, AHB1, A, 6),
    __STM32_PIN(23, AHB1, A, 7),
    __STM32_PIN(24, AHB1, C, 4),
    __STM32_PIN(25, AHB1, C, 5),
    __STM32_PIN(26, AHB1, B, 0),
    __STM32_PIN(27, AHB1, B, 1),
    __STM32_PIN(28, AHB1, B, 2),
    __STM32_PIN(29, AHB1, B, 10),
    __STM32_PIN(30, AHB1, B, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(33, AHB1, B, 12),
    __STM32_PIN(34, AHB1, B, 13),
    __STM32_PIN(35, AHB1, B, 14),
    __STM32_PIN(36, AHB1, B, 15),
    __STM32_PIN(37, AHB1, C, 6),
    __STM32_PIN(38, AHB1, C, 7),
    __STM32_PIN(39, AHB1, C, 8),
    __STM32_PIN(40, AHB1, C, 9),
    __STM32_PIN(41, AHB1, A, 8),
    __STM32_PIN(42, AHB1, A, 9),
    __STM32_PIN(43, AHB1, A, 10),
    __STM32_PIN(44, AHB1, A, 11),
    __STM32_PIN(45, AHB1, A, 12),
    __STM32_PIN(46, AHB1, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(49, AHB1, A, 14),
    __STM32_PIN(50, AHB1, A, 15),
    __STM32_PIN(51, AHB1, C, 10),
    __STM32_PIN(52, AHB1, C, 11),
    __STM32_PIN(53, AHB1, C, 12),
    __STM32_PIN(54, AHB1, D, 2),
    __STM32_PIN(55, AHB1, B, 3),
    __STM32_PIN(56, AHB1, B, 4),
    __STM32_PIN(57, AHB1, B, 5),
    __STM32_PIN(58, AHB1, B, 6),
    __STM32_PIN(59, AHB1, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(61, AHB1, B, 8),
    __STM32_PIN(62, AHB1, B, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
#endif
#if (STM32_PIN_NUMBERS == 100)
    __STM32_PIN_DEFAULT,
    __STM32_PIN(1, AHB1, E, 2),
    __STM32_PIN(2, AHB1, E, 3),
    __STM32_PIN(3, AHB1, E, 4),
    __STM32_PIN(4, AHB1, E, 5),
    __STM32_PIN(5, AHB1, E, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(7, AHB1, C, 13),
    __STM32_PIN(8, AHB1, C, 14),
    __STM32_PIN(9, AHB1, C, 15),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(15, AHB1, C, 0),
    __STM32_PIN(16, AHB1, C, 1),
    __STM32_PIN(17, AHB1, C, 2),
    __STM32_PIN(18, AHB1, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(23, AHB1, A, 0),
    __STM32_PIN(24, AHB1, A, 1),
    __STM32_PIN(25, AHB1, A, 2),
    __STM32_PIN(26, AHB1, A, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(29, AHB1, A, 4),
    __STM32_PIN(30, AHB1, A, 5),
    __STM32_PIN(31, AHB1, A, 6),
    __STM32_PIN(32, AHB1, A, 7),
    __STM32_PIN(33, AHB1, C, 4),
    __STM32_PIN(34, AHB1, C, 5),
    __STM32_PIN(35, AHB1, B, 0),
    __STM32_PIN(36, AHB1, B, 1),
    __STM32_PIN(37, AHB1, B, 2),
    __STM32_PIN(38, AHB1, E, 7),
    __STM32_PIN(39, AHB1, E, 8),
    __STM32_PIN(40, AHB1, E, 9),
    __STM32_PIN(41, AHB1, E, 10),
    __STM32_PIN(42, AHB1, E, 11),
    __STM32_PIN(43, AHB1, E, 12),
    __STM32_PIN(44, AHB1, E, 13),
    __STM32_PIN(45, AHB1, E, 14),
    __STM32_PIN(46, AHB1, E, 15),
    __STM32_PIN(47, AHB1, B, 10),
    __STM32_PIN(48, AHB1, B, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(51, AHB1, B, 12),
    __STM32_PIN(52, AHB1, B, 13),
    __STM32_PIN(53, AHB1, B, 14),
    __STM32_PIN(54, AHB1, B, 15),
    __STM32_PIN(55, AHB1, D, 8),
    __STM32_PIN(56, AHB1, D, 9),
    __STM32_PIN(57, AHB1, D, 10),
    __STM32_PIN(58, AHB1, D, 11),
    __STM32_PIN(59, AHB1, D, 12),
    __STM32_PIN(60, AHB1, D, 13),
    __STM32_PIN(61, AHB1, D, 14),
    __STM32_PIN(62, AHB1, D, 15),
    __STM32_PIN(63, AHB1, C, 6),
    __STM32_PIN(64, AHB1, C, 7),
    __STM32_PIN(65, AHB1, C, 8),
    __STM32_PIN(66, AHB1, C, 9),
    __STM32_PIN(67, AHB1, A, 8),
    __STM32_PIN(68, AHB1, A, 9),
    __STM32_PIN(69, AHB1, A, 10),
    __STM32_PIN(70, AHB1, A, 11),
    __STM32_PIN(71, AHB1, A, 12),
    __STM32_PIN(72, AHB1, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(76, AHB1, A, 14),
    __STM32_PIN(77, AHB1, A, 15),
    __STM32_PIN(78, AHB1, C, 10),
    __STM32_PIN(79, AHB1, C, 11),
    __STM32_PIN(80, AHB1, C, 12),
    __STM32_PIN(81, AHB1, D, 0),
    __STM32_PIN(82, AHB1, D, 1),
    __STM32_PIN(83, AHB1, D, 2),
    __STM32_PIN(84, AHB1, D, 3),
    __STM32_PIN(85, AHB1, D, 4),
    __STM32_PIN(86, AHB1, D, 5),
    __STM32_PIN(87, AHB1, D, 6),
    __STM32_PIN(88, AHB1, D, 7),
    __STM32_PIN(89, AHB1, B, 3),
    __STM32_PIN(90, AHB1, B, 4),
    __STM32_PIN(91, AHB1, B, 5),
    __STM32_PIN(92, AHB1, B, 6),
    __STM32_PIN(93, AHB1, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(95, AHB1, B, 8),
    __STM32_PIN(96, AHB1, B, 9),
    __STM32_PIN(97, AHB1, E, 0),
    __STM32_PIN(98, AHB1, E, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
#endif
#if (STM32_PIN_NUMBERS == 144)
    __STM32_PIN_DEFAULT,
    __STM32_PIN(1, AHB1, E, 2),
    __STM32_PIN(2, AHB1, E, 3),
    __STM32_PIN(3, AHB1, E, 4),
    __STM32_PIN(4, AHB1, E, 5),
    __STM32_PIN(5, AHB1, E, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(7, AHB1, C, 13),
    __STM32_PIN(8, AHB1, C, 14),
    __STM32_PIN(9, AHB1, C, 15),

    __STM32_PIN(10, AHB1, F, 0),
    __STM32_PIN(11, AHB1, F, 1),
    __STM32_PIN(12, AHB1, F, 2),
    __STM32_PIN(13, AHB1, F, 3),
    __STM32_PIN(14, AHB1, F, 4),
    __STM32_PIN(15, AHB1, F, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(18, AHB1, F, 6),
    __STM32_PIN(19, AHB1, F, 7),
    __STM32_PIN(20, AHB1, F, 8),
    __STM32_PIN(21, AHB1, F, 9),
    __STM32_PIN(22, AHB1, F, 10),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(26, AHB1, C, 0),
    __STM32_PIN(27, AHB1, C, 1),
    __STM32_PIN(28, AHB1, C, 2),
    __STM32_PIN(29, AHB1, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(34, AHB1, A, 0),
    __STM32_PIN(35, AHB1, A, 1),
    __STM32_PIN(36, AHB1, A, 2),
    __STM32_PIN(37, AHB1, A, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(40, AHB1, A, 4),
    __STM32_PIN(41, AHB1, A, 5),
    __STM32_PIN(42, AHB1, A, 6),
    __STM32_PIN(43, AHB1, A, 7),
    __STM32_PIN(44, AHB1, C, 4),
    __STM32_PIN(45, AHB1, C, 5),
    __STM32_PIN(46, AHB1, B, 0),
    __STM32_PIN(47, AHB1, B, 1),
    __STM32_PIN(48, AHB1, B, 2),
    __STM32_PIN(49, AHB1, F, 11),
    __STM32_PIN(50, AHB1, F, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(53, AHB1, F, 13),
    __STM32_PIN(54, AHB1, F, 14),
    __STM32_PIN(55, AHB1, F, 15),
    __STM32_PIN(56, AHB1, G, 0),
    __STM32_PIN(57, AHB1, G, 1),
    __STM32_PIN(58, AHB1, E, 7),
    __STM32_PIN(59, AHB1, E, 8),
    __STM32_PIN(60, AHB1, E, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(63, AHB1, E, 10),
    __STM32_PIN(64, AHB1, E, 11),
    __STM32_PIN(65, AHB1, E, 12),
    __STM32_PIN(66, AHB1, E, 13),
    __STM32_PIN(67, AHB1, E, 14),
    __STM32_PIN(68, AHB1, E, 15),
    __STM32_PIN(69, AHB1, B, 10),
    __STM32_PIN(70, AHB1, B, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(73, AHB1, B, 12),
    __STM32_PIN(74, AHB1, B, 13),
    __STM32_PIN(75, AHB1, B, 14),
    __STM32_PIN(76, AHB1, B, 15),
    __STM32_PIN(77, AHB1, D, 8),
    __STM32_PIN(78, AHB1, D, 9),
    __STM32_PIN(79, AHB1, D, 10),
    __STM32_PIN(80, AHB1, D, 11),
    __STM32_PIN(81, AHB1, D, 12),
    __STM32_PIN(82, AHB1, D, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(85, AHB1, D, 14),
    __STM32_PIN(86, AHB1, D, 15),
    __STM32_PIN(87, AHB1, G, 2),
    __STM32_PIN(88, AHB1, G, 3),
    __STM32_PIN(89, AHB1, G, 4),
    __STM32_PIN(90, AHB1, G, 5),
    __STM32_PIN(91, AHB1, G, 6),
    __STM32_PIN(92, AHB1, G, 7),
    __STM32_PIN(93, AHB1, G, 8),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(96, AHB1, C, 6),
    __STM32_PIN(97, AHB1, C, 7),
    __STM32_PIN(98, AHB1, C, 8),
    __STM32_PIN(99, AHB1, C, 9),
    __STM32_PIN(100, AHB1, A, 8),
    __STM32_PIN(101, AHB1, A, 9),
    __STM32_PIN(102, AHB1, A, 10),
    __STM32_PIN(103, AHB1, A, 11),
    __STM32_PIN(104, AHB1, A, 12),
    __STM32_PIN(105, AHB1, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(109, AHB1, A, 14),
    __STM32_PIN(110, AHB1, A, 15),
    __STM32_PIN(111, AHB1, C, 10),
    __STM32_PIN(112, AHB1, C, 11),
    __STM32_PIN(113, AHB1, C, 12),
    __STM32_PIN(114, AHB1, D, 0),
    __STM32_PIN(115, AHB1, D, 1),
    __STM32_PIN(116, AHB1, D, 2),
    __STM32_PIN(117, AHB1, D, 3),
    __STM32_PIN(118, AHB1, D, 4),
    __STM32_PIN(119, AHB1, D, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(122, AHB1, D, 6),
    __STM32_PIN(123, AHB1, D, 7),
    __STM32_PIN(124, AHB1, G, 9),
    __STM32_PIN(125, AHB1, G, 10),
    __STM32_PIN(126, AHB1, G, 11),
    __STM32_PIN(127, AHB1, G, 12),
    __STM32_PIN(128, AHB1, G, 13),
    __STM32_PIN(129, AHB1, G, 14),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(132, AHB1, G, 15),
    __STM32_PIN(133, AHB1, B, 3),
    __STM32_PIN(134, AHB1, B, 4),
    __STM32_PIN(135, AHB1, B, 5),
    __STM32_PIN(136, AHB1, B, 6),
    __STM32_PIN(137, AHB1, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(139, AHB1, B, 8),
    __STM32_PIN(140, AHB1, B, 9),
    __STM32_PIN(141, AHB1, E, 0),
    __STM32_PIN(142, AHB1, E, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
#endif
};

struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
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
    RCC_AHB1PeriphClockCmd(index->rcc, ENABLE);

    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.GPIO_Pin   = index->pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: open drain */
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    }
    else
    {
        /* error mode */
        RT_ASSERT(0);
    }
    GPIO_Init(index->gpio, &GPIO_InitStructure);
}

rt_inline rt_int32_t bit2bitno(rt_uint32_t bit)
{
    int i;
    for (i = 0; i < 32; i++)
    {
        if ((1UL << i) == bit)
        {
            return i;
        }
    }
    return -1;
}

rt_inline rt_int32_t bitno2bit(rt_uint32_t bitno)
{
    if (bitno <= 32)
    {
        return 1UL << bitno;
    }
    else
    {
        return 0;
    }
}

static const struct pin_irq *get_pin_irq(uint16_t pin)
{
    static struct pin_irq irq;
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_NULL;
    }

    irq.exti_line = index->pin;
    irq.pin_source = bit2bitno(index->pin);
    irq.port_source = ((uint32_t)index->gpio - GPIOA_BASE) / (GPIOB_BASE - GPIOA_BASE);
    switch (irq.pin_source)
    {
    case 0 : irq.irq_exti_channel = EXTI0_IRQn;break;
    case 1 : irq.irq_exti_channel = EXTI1_IRQn;break;
    case 2 : irq.irq_exti_channel = EXTI2_IRQn;break;
    case 3 : irq.irq_exti_channel = EXTI3_IRQn;break;
    case 4 : irq.irq_exti_channel = EXTI4_IRQn;break;
    case 5 :
    case 6 :
    case 7 :
    case 8 :
    case 9 : irq.irq_exti_channel = EXTI9_5_IRQn;break;
    case 10 :
    case 11 :
    case 12 :
    case 13 :
    case 14 :
    case 15 : irq.irq_exti_channel = EXTI15_10_IRQn;break;
    default : return RT_NULL;
    }

    return &irq;
};

rt_err_t stm32_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                  rt_uint32_t mode, void (*hdr)(void *args), void *args)
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
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_hdr_tab))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == pin   &&
        pin_irq_hdr_tab[irqindex].hdr == hdr   &&
        pin_irq_hdr_tab[irqindex].mode == mode &&
        pin_irq_hdr_tab[irqindex].args == args
    )
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
    //TODO PA1 will overwrite PB1's hdr, using rt_list ?
    pin_irq_hdr_tab[irqindex].hdr = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);
 
    return RT_EOK;
}

rt_err_t stm32_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
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
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_hdr_tab))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[irqindex].pin  = -1;
    pin_irq_hdr_tab[irqindex].hdr  = RT_NULL;
    pin_irq_hdr_tab[irqindex].mode = 0;
    pin_irq_hdr_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);
 
    return RT_EOK;
}

rt_err_t stm32_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
    const struct pin_index *index;
    const struct pin_irq *irq;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }
    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(index->pin);
        if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_hdr_tab))
        {
            return -RT_ENOSYS;
        }
        level = rt_hw_interrupt_disable();
        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }

        irq = get_pin_irq(pin);
        if (irq == RT_NULL)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }
        /* select the input source pin for the EXTI line */
        SYSCFG_EXTILineConfig(irq->port_source, irq->pin_source);
        /* select the mode(interrupt, event) and configure the trigger selection */
        EXTI_InitStructure.EXTI_Line = irq->exti_line;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        switch (pin_irq_hdr_tab[irqindex].mode)
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
        /* configure NVIC IRQ channel mapped to the EXTI line */
        NVIC_InitStructure.NVIC_IRQChannel = irq->irq_exti_channel;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irq = get_pin_irq(index->pin);
        if (irq == RT_NULL)
        {
            return -RT_ENOSYS;
        }
        EXTI_InitStructure.EXTI_Line = irq->exti_line;
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
const static struct rt_pin_ops _stm32_pin_ops =
{
    stm32_pin_mode,
    stm32_pin_write,
    stm32_pin_read,
    stm32_pin_attach_irq,
    stm32_pin_dettach_irq,
    stm32_pin_irq_enable,
};

int stm32_hw_pin_init(void)
{
    int result;

    /* enable SYSCFG clock for EXTI */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    result = rt_device_pin_register("pin", &_stm32_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(stm32_hw_pin_init);

rt_inline void pin_irq_hdr(int irqno)
{
    EXTI_ClearITPendingBit(bitno2bit(irqno));
    if (pin_irq_hdr_tab[irqno].hdr)
    {
       pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
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

#endif
