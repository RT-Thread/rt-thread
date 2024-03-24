/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-08-20     breo.com     first version
 */

#include "drv_gpio.h"
#include <rtdevice.h>
#include <rthw.h>
#include "n32g45x.h"

#ifdef RT_USING_PIN

#ifndef N32G45X_PIN_NUMBERS
    #define N32G45X_PIN_NUMBERS 64//[48, 64, 80, 100, 128 ]
#endif

#define __N32_PIN(index, rcc, gpio, gpio_index) \
{ \
0, RCC_##rcc##_PERIPH_GPIO##gpio, GPIO##gpio, GPIO_PIN_##gpio_index \
, GPIO##gpio##_PORT_SOURCE, GPIO_PIN_SOURCE##gpio_index, "P" #gpio "." #gpio_index \
}
#define __N32_PIN_DEFAULT {-1, 0, 0, 0, 0, 0, ""}

/* N32 GPIO driver */
struct pin_index
{
    int index;
    uint32_t rcc;
    GPIO_Module *gpio;
    uint32_t pin;
    uint8_t port_source;
    uint8_t pin_source;
    const char* name;
};

static const struct pin_index pins[] =
{
#if (N32G45X_PIN_NUMBERS == 48)
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(2, APB2, C, 13),
    __N32_PIN(3, APB2, C, 14),
    __N32_PIN(4, APB2, C, 15),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(10, APB2, A, 0),
    __N32_PIN(11, APB2, A, 1),
    __N32_PIN(12, APB2, A, 2),
    __N32_PIN(13, APB2, A, 3),
    __N32_PIN(14, APB2, A, 4),
    __N32_PIN(15, APB2, A, 5),
    __N32_PIN(16, APB2, A, 6),
    __N32_PIN(17, APB2, A, 7),
    __N32_PIN(18, APB2, B, 0),
    __N32_PIN(19, APB2, B, 1),
    __N32_PIN(20, APB2, B, 2),
    __N32_PIN(21, APB2, B, 10),
    __N32_PIN(22, APB2, B, 11),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(25, APB2, B, 12),
    __N32_PIN(26, APB2, B, 13),
    __N32_PIN(27, APB2, B, 14),
    __N32_PIN(28, APB2, B, 15),
    __N32_PIN(29, APB2, A, 8),
    __N32_PIN(30, APB2, A, 9),
    __N32_PIN(31, APB2, A, 10),
    __N32_PIN(32, APB2, A, 11),
    __N32_PIN(33, APB2, A, 12),
    __N32_PIN(34, APB2, A, 13),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(37, APB2, A, 14),
    __N32_PIN(38, APB2, A, 15),
    __N32_PIN(39, APB2, B, 3),
    __N32_PIN(40, APB2, B, 4),
    __N32_PIN(41, APB2, B, 5),
    __N32_PIN(42, APB2, B, 6),
    __N32_PIN(43, APB2, B, 7),
    __N32_PIN_DEFAULT,
    __N32_PIN(45, APB2, B, 8),
    __N32_PIN(46, APB2, B, 9),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    #endif
    #if (N32G45X_PIN_NUMBERS == 64)
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(2, APB2, C, 13),
    __N32_PIN(3, APB2, C, 14),
    __N32_PIN(4, APB2, C, 15),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(8, APB2, C, 0),
    __N32_PIN(9, APB2, C, 1),
    __N32_PIN(10, APB2, C, 2),
    __N32_PIN(11, APB2, C, 3),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(14, APB2, A, 0),
    __N32_PIN(15, APB2, A, 1),
    __N32_PIN(16, APB2, A, 2),
    __N32_PIN(17, APB2, A, 3),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(20, APB2, A, 4),
    __N32_PIN(21, APB2, A, 5),
    __N32_PIN(22, APB2, A, 6),
    __N32_PIN(23, APB2, A, 7),
    __N32_PIN(24, APB2, C, 4),
    __N32_PIN(25, APB2, C, 5),
    __N32_PIN(26, APB2, B, 0),
    __N32_PIN(27, APB2, B, 1),
    __N32_PIN(28, APB2, B, 2),
    __N32_PIN(29, APB2, B, 10),
    __N32_PIN(30, APB2, B, 11),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(33, APB2, B, 12),
    __N32_PIN(34, APB2, B, 13),
    __N32_PIN(35, APB2, B, 14),
    __N32_PIN(36, APB2, B, 15),
    __N32_PIN(37, APB2, C, 6),
    __N32_PIN(38, APB2, C, 7),
    __N32_PIN(39, APB2, C, 8),
    __N32_PIN(40, APB2, C, 9),
    __N32_PIN(41, APB2, A, 8),
    __N32_PIN(42, APB2, A, 9),
    __N32_PIN(43, APB2, A, 10),
    __N32_PIN(44, APB2, A, 11),
    __N32_PIN(45, APB2, A, 12),
    __N32_PIN(46, APB2, A, 13),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(49, APB2, A, 14),
    __N32_PIN(50, APB2, A, 15),
    __N32_PIN(51, APB2, C, 10),
    __N32_PIN(52, APB2, C, 11),
    __N32_PIN(53, APB2, C, 12),
    __N32_PIN(54, APB2, D, 2),
    __N32_PIN(55, APB2, B, 3),
    __N32_PIN(56, APB2, B, 4),
    __N32_PIN(57, APB2, B, 5),
    __N32_PIN(58, APB2, B, 6),
    __N32_PIN(59, APB2, B, 7),
    __N32_PIN_DEFAULT,
    __N32_PIN(61, APB2, B, 8),
    __N32_PIN(62, APB2, B, 9),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    #endif
    #if (N32G45X_PIN_NUMBERS == 80)
    __N32_PIN_DEFAULT,
    __N32_PIN(1, APB2, E, 2),
    __N32_PIN(2, APB2, E, 3),
    __N32_PIN_DEFAULT,
    __N32_PIN(4, APB2, C, 13),
    __N32_PIN(5, APB2, C, 14),
    __N32_PIN(6, APB2, C, 15),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(10, APB2, C, 0),
    __N32_PIN(11, APB2, C, 1),
    __N32_PIN(12, APB2, C, 2),
    __N32_PIN(13, APB2, C, 3),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(16, APB2, A, 0),
    __N32_PIN(17, APB2, A, 1),
    __N32_PIN(18, APB2, A, 2),
    __N32_PIN(19, APB2, A, 3),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(22, APB2, A, 4),
    __N32_PIN(23, APB2, A, 5),
    __N32_PIN(24, APB2, A, 6),
    __N32_PIN(25, APB2, A, 7),
    __N32_PIN(26, APB2, C, 4),
    __N32_PIN(27, APB2, C, 5),
    __N32_PIN(28, APB2, B, 0),
    __N32_PIN(29, APB2, B, 1),
    __N32_PIN(30, APB2, B, 2),
    __N32_PIN(31, APB2, E, 7),
    __N32_PIN(32, APB2, E, 8),
    __N32_PIN(33, APB2, E, 9),
    __N32_PIN(34, APB2, E, 10),
    __N32_PIN(35, APB2, E, 11),
    __N32_PIN(36, APB2, E, 12),
    __N32_PIN(37, APB2, E, 13),
    __N32_PIN(38, APB2, B, 10),
    __N32_PIN(39, APB2, B, 11),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(42, APB2, B, 12),
    __N32_PIN(43, APB2, B, 13),
    __N32_PIN(44, APB2, B, 14),
    __N32_PIN(45, APB2, B, 15),
    __N32_PIN(46, APB2, D, 8),
    __N32_PIN(47, APB2, D, 9),
    __N32_PIN(48, APB2, D, 10),
    __N32_PIN(49, APB2, D, 14),
    __N32_PIN(50, APB2, D, 15),
    __N32_PIN(51, APB2, C, 6),
    __N32_PIN(52, APB2, C, 7),
    __N32_PIN(53, APB2, C, 8),
    __N32_PIN(54, APB2, C, 9),
    __N32_PIN(55, APB2, A, 8),
    __N32_PIN(56, APB2, A, 9),
    __N32_PIN(57, APB2, A, 10),
    __N32_PIN(58, APB2, A, 11),
    __N32_PIN(59, APB2, A, 12),
    __N32_PIN(60, APB2, A, 13),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(63, APB2, A, 14),
    __N32_PIN(64, APB2, A, 15),
    __N32_PIN(65, APB2, C, 10),
    __N32_PIN(66, APB2, C, 11),
    __N32_PIN(67, APB2, C, 12),
    __N32_PIN(68, APB2, D, 0),
    __N32_PIN(69, APB2, D, 1),
    __N32_PIN(70, APB2, D, 2),
    __N32_PIN(71, APB2, B, 3),
    __N32_PIN(72, APB2, B, 4),
    __N32_PIN(73, APB2, B, 5),
    __N32_PIN(74, APB2, B, 6),
    __N32_PIN(75, APB2, B, 7),
    __N32_PIN_DEFAULT,
    __N32_PIN(77, APB2, B, 8),
    __N32_PIN(78, APB2, B, 9),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
#endif
#if (N32G45X_PIN_NUMBERS == 100)
    __N32_PIN_DEFAULT,
    __N32_PIN(1, APB2, E, 2),
    __N32_PIN(2, APB2, E, 3),
    __N32_PIN(3, APB2, E, 4),
    __N32_PIN(4, APB2, E, 5),
    __N32_PIN(5, APB2, E, 6),
    __N32_PIN_DEFAULT,
    __N32_PIN(7, APB2, C, 13),
    __N32_PIN(8, APB2, C, 14),
    __N32_PIN(9, APB2, C, 15),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(15, APB2, C, 0),
    __N32_PIN(16, APB2, C, 1),
    __N32_PIN(17, APB2, C, 2),
    __N32_PIN(18, APB2, C, 3),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(23, APB2, A, 0),
    __N32_PIN(24, APB2, A, 1),
    __N32_PIN(25, APB2, A, 2),
    __N32_PIN(26, APB2, A, 3),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(29, APB2, A, 4),
    __N32_PIN(30, APB2, A, 5),
    __N32_PIN(31, APB2, A, 6),
    __N32_PIN(32, APB2, A, 7),
    __N32_PIN(33, APB2, C, 4),
    __N32_PIN(34, APB2, C, 5),
    __N32_PIN(35, APB2, B, 0),
    __N32_PIN(36, APB2, B, 1),
    __N32_PIN(37, APB2, B, 2),
    __N32_PIN(38, APB2, E, 7),
    __N32_PIN(39, APB2, E, 8),
    __N32_PIN(40, APB2, E, 9),
    __N32_PIN(41, APB2, E, 10),
    __N32_PIN(42, APB2, E, 11),
    __N32_PIN(43, APB2, E, 12),
    __N32_PIN(44, APB2, E, 13),
    __N32_PIN(45, APB2, E, 14),
    __N32_PIN(46, APB2, E, 15),
    __N32_PIN(47, APB2, B, 10),
    __N32_PIN(48, APB2, B, 11),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(51, APB2, B, 12),
    __N32_PIN(52, APB2, B, 13),
    __N32_PIN(53, APB2, B, 14),
    __N32_PIN(54, APB2, B, 15),
    __N32_PIN(55, APB2, D, 8),
    __N32_PIN(56, APB2, D, 9),
    __N32_PIN(57, APB2, D, 10),
    __N32_PIN(58, APB2, D, 11),
    __N32_PIN(59, APB2, D, 12),
    __N32_PIN(60, APB2, D, 13),
    __N32_PIN(61, APB2, D, 14),
    __N32_PIN(62, APB2, D, 15),
    __N32_PIN(63, APB2, C, 6),
    __N32_PIN(64, APB2, C, 7),
    __N32_PIN(65, APB2, C, 8),
    __N32_PIN(66, APB2, C, 9),
    __N32_PIN(67, APB2, A, 8),
    __N32_PIN(68, APB2, A, 9),
    __N32_PIN(69, APB2, A, 10),
    __N32_PIN(70, APB2, A, 11),
    __N32_PIN(71, APB2, A, 12),
    __N32_PIN(72, APB2, A, 13),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(76, APB2, A, 14),
    __N32_PIN(77, APB2, A, 15),
    __N32_PIN(78, APB2, C, 10),
    __N32_PIN(79, APB2, C, 11),
    __N32_PIN(80, APB2, C, 12),
    __N32_PIN(81, APB2, D, 0),
    __N32_PIN(82, APB2, D, 1),
    __N32_PIN(83, APB2, D, 2),
    __N32_PIN(84, APB2, D, 3),
    __N32_PIN(85, APB2, D, 4),
    __N32_PIN(86, APB2, D, 5),
    __N32_PIN(87, APB2, D, 6),
    __N32_PIN(88, APB2, D, 7),
    __N32_PIN(89, APB2, B, 3),
    __N32_PIN(90, APB2, B, 4),
    __N32_PIN(91, APB2, B, 5),
    __N32_PIN(92, APB2, B, 6),
    __N32_PIN(93, APB2, B, 7),
    __N32_PIN_DEFAULT,
    __N32_PIN(95, APB2, B, 8),
    __N32_PIN(96, APB2, B, 9),
    __N32_PIN(97, APB2, E, 0),
    __N32_PIN(98, APB2, E, 1),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    #endif
    #if (N32G45X_PIN_NUMBERS == 128)
    __N32_PIN_DEFAULT,
    __N32_PIN(1, APB2, E, 2),
    __N32_PIN(2, APB2, E, 3),
    __N32_PIN(3, APB2, E, 4),
    __N32_PIN(4, APB2, E, 5),
    __N32_PIN(5, APB2, E, 6),
    __N32_PIN_DEFAULT,
    __N32_PIN(7, APB2, C, 13),
    __N32_PIN(8, APB2, C, 14),
    __N32_PIN(9, APB2, C, 15),
    __N32_PIN(10, APB2, F, 0),
    __N32_PIN(11, APB2, F, 1),
    __N32_PIN(12, APB2, F, 2),
    __N32_PIN(13, APB2, F, 3),
    __N32_PIN(14, APB2, F, 4),
    __N32_PIN(15, APB2, F, 5),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(21, APB2, C, 0),
    __N32_PIN(22, APB2, C, 1),
    __N32_PIN(23, APB2, C, 2),
    __N32_PIN(24, APB2, C, 3),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(29, APB2, A, 0),
    __N32_PIN(30, APB2, A, 1),
    __N32_PIN(31, APB2, A, 2),
    __N32_PIN(32, APB2, A, 3),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(35, APB2, A, 4),
    __N32_PIN(36, APB2, A, 5),
    __N32_PIN(37, APB2, A, 6),
    __N32_PIN(38, APB2, A, 7),
    __N32_PIN(39, APB2, C, 4),
    __N32_PIN(40, APB2, C, 5),
    __N32_PIN(41, APB2, B, 0),
    __N32_PIN(42, APB2, B, 1),
    __N32_PIN(43, APB2, B, 2),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(46, APB2, F, 12),
    __N32_PIN(47, APB2, F, 13),
    __N32_PIN(48, APB2, F, 14),
    __N32_PIN(49, APB2, F, 15),
    __N32_PIN(50, APB2, E, 7),
    __N32_PIN(51, APB2, E, 8),
    __N32_PIN(52, APB2, E, 9),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(55, APB2, E, 10),
    __N32_PIN(56, APB2, E, 11),
    __N32_PIN(57, APB2, E, 12),
    __N32_PIN(58, APB2, E, 13),
    __N32_PIN(59, APB2, E, 14),
    __N32_PIN(60, APB2, E, 15),
    __N32_PIN(61, APB2, B, 10),
    __N32_PIN(62, APB2, B, 11),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(65, APB2, B, 12),
    __N32_PIN(66, APB2, B, 13),
    __N32_PIN(67, APB2, B, 14),
    __N32_PIN(68, APB2, B, 15),
    __N32_PIN(69, APB2, D, 8),
    __N32_PIN(70, APB2, D, 9),
    __N32_PIN(71, APB2, D, 10),
    __N32_PIN(72, APB2, D, 11),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(75, APB2, D, 12),
    __N32_PIN(76, APB2, D, 13),
    __N32_PIN(77, APB2, D, 14),
    __N32_PIN(78, APB2, D, 15),
    __N32_PIN(79, APB2, G, 0),
    __N32_PIN(80, APB2, G, 1),
    __N32_PIN(81, APB2, G, 2),
    __N32_PIN(82, APB2, G, 3),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(85, APB2, C, 6),
    __N32_PIN(86, APB2, C, 7),
    __N32_PIN(87, APB2, C, 8),
    __N32_PIN(88, APB2, C, 9),
    __N32_PIN(89, APB2, A, 8),
    __N32_PIN(90, APB2, A, 9),
    __N32_PIN(91, APB2, A, 10),
    __N32_PIN(92, APB2, A, 11),
    __N32_PIN(93, APB2, A, 12),
    __N32_PIN(94, APB2, A, 13),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(97, APB2, A, 14),
    __N32_PIN(98, APB2, A, 15),
    __N32_PIN(99, APB2, C, 10),
    __N32_PIN(100, APB2, C, 11),
    __N32_PIN(101, APB2, C, 12),
    __N32_PIN(102, APB2, D, 0),
    __N32_PIN(103, APB2, D, 1),
    __N32_PIN(104, APB2, D, 2),
    __N32_PIN(105, APB2, D, 3),
    __N32_PIN(106, APB2, D, 4),
    __N32_PIN(107, APB2, D, 5),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(110, APB2, D, 6),
    __N32_PIN(111, APB2, D, 7),
    __N32_PIN(112, APB2, G, 4),
    __N32_PIN(113, APB2, G, 5),
    __N32_PIN(114, APB2, G, 9),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
    __N32_PIN(117, APB2, B, 3),
    __N32_PIN(118, APB2, B, 4),
    __N32_PIN(119, APB2, B, 5),
    __N32_PIN(120, APB2, B, 6),
    __N32_PIN(121, APB2, B, 7),
    __N32_PIN_DEFAULT,
    __N32_PIN(123, APB2, B, 8),
    __N32_PIN(124, APB2, B, 9),
    __N32_PIN(125, APB2, E, 0),
    __N32_PIN(126, APB2, E, 1),
    __N32_PIN_DEFAULT,
    __N32_PIN_DEFAULT,
#endif
};

struct pin_irq_map
{
    rt_uint16_t            pinbit;
    rt_uint32_t            irqbit;
    enum IRQn              irqno;
};
static const  struct pin_irq_map pin_irq_map[] =
{
    {GPIO_PIN_0,  EXTI_LINE0,  EXTI0_IRQn    },
    {GPIO_PIN_1,  EXTI_LINE1,  EXTI1_IRQn    },
    {GPIO_PIN_2,  EXTI_LINE2,  EXTI2_IRQn    },
    {GPIO_PIN_3,  EXTI_LINE3,  EXTI3_IRQn    },
    {GPIO_PIN_4,  EXTI_LINE4,  EXTI4_IRQn    },
    {GPIO_PIN_5,  EXTI_LINE5,  EXTI9_5_IRQn  },
    {GPIO_PIN_6,  EXTI_LINE6,  EXTI9_5_IRQn  },
    {GPIO_PIN_7,  EXTI_LINE7,  EXTI9_5_IRQn  },
    {GPIO_PIN_8,  EXTI_LINE8,  EXTI9_5_IRQn  },
    {GPIO_PIN_9,  EXTI_LINE9,  EXTI9_5_IRQn  },
    {GPIO_PIN_10, EXTI_LINE10, EXTI15_10_IRQn},
    {GPIO_PIN_11, EXTI_LINE11, EXTI15_10_IRQn},
    {GPIO_PIN_12, EXTI_LINE12, EXTI15_10_IRQn},
    {GPIO_PIN_13, EXTI_LINE13, EXTI15_10_IRQn},
    {GPIO_PIN_14, EXTI_LINE14, EXTI15_10_IRQn},
    {GPIO_PIN_15, EXTI_LINE15, EXTI15_10_IRQn},
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

rt_base_t n32_pin_get(const char *name)
{
    rt_base_t i;

    for (i = 0; i < ITEM_NUM(pins); i++)
    {
        if (rt_strcmp(pins[i].name, name) == 0)
        {
            /* in get_pin function, use pin parameter as index of pins array */
            return i;
        }
    }

    /* refers content of pins array, map to __N32_PIN_DEFAULT */
    return 0;
}

void n32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
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

rt_ssize_t n32_pin_read(rt_device_t dev, rt_base_t pin)
{
    rt_ssize_t value;
    const struct pin_index *index;

    value = PIN_LOW;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_EINVAL;
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

void n32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    const struct pin_index *index;
    GPIO_InitType  GPIO_InitStructure;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    /* GPIO Periph clock enable */
    RCC_EnableAPB2PeriphClk(index->rcc, ENABLE);

    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.Pin        = index->pin;
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
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull up. */
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* input setting: pull up. */
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;
    }
    else
    {
        /* input setting:default. */
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;
    }
    GPIO_InitPeripheral(index->gpio, &GPIO_InitStructure);
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
rt_err_t n32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                            rt_uint8_t mode, void (*hdr)(void *args), void *args)
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
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
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
    pin_irq_hdr_tab[irqindex].hdr = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}
rt_err_t n32_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
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
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
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
rt_err_t n32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                            rt_uint8_t enabled)
{
    const struct pin_index *index;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    GPIO_InitType  GPIO_InitStructure;
    NVIC_InitType  NVIC_InitStructure;
    EXTI_InitType EXTI_InitStructure;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }
    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(index->pin);
        if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
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
        /* GPIO Periph clock enable */
        RCC_EnableAPB2PeriphClk(index->rcc, ENABLE);
        /* Configure GPIO_InitStructure */
        GPIO_InitStructure.Pin        = index->pin;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitPeripheral(index->gpio, &GPIO_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel = irqmap->irqno;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        GPIO_ConfigEXTILine(index->port_source, index->pin_source);
        EXTI_InitStructure.EXTI_Line = irqmap->irqbit;
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
        EXTI_InitPeripheral(&EXTI_InitStructure);
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(index->pin);
        if (irqmap == RT_NULL)
        {
            return -RT_ENOSYS;
        }
        EXTI_InitStructure.EXTI_Line = irqmap->irqbit;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
        EXTI_InitStructure.EXTI_LineCmd = DISABLE;
        EXTI_InitPeripheral(&EXTI_InitStructure);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}
const static struct rt_pin_ops _n32_pin_ops =
{
    n32_pin_mode,
    n32_pin_write,
    n32_pin_read,
    n32_pin_attach_irq,
    n32_pin_dettach_irq,
    n32_pin_irq_enable,
    n32_pin_get
};

int n32_hw_pin_init(void)
{
    int result;

    result = rt_device_pin_register("pin", &_n32_pin_ops, RT_NULL);
    return result;
}

rt_inline void pin_irq_hdr(int irqno)
{
    EXTI_ClrITPendBit(pin_irq_map[irqno].irqbit);
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
    if (EXTI_GetITStatus(EXTI_LINE5) != RESET)
    {
        pin_irq_hdr(5);
    }
    if (EXTI_GetITStatus(EXTI_LINE6) != RESET)
    {
        pin_irq_hdr(6);
    }
    if (EXTI_GetITStatus(EXTI_LINE7) != RESET)
    {
        pin_irq_hdr(7);
    }
    if (EXTI_GetITStatus(EXTI_LINE8) != RESET)
    {
        pin_irq_hdr(8);
    }
    if (EXTI_GetITStatus(EXTI_LINE9) != RESET)
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
    if (EXTI_GetITStatus(EXTI_LINE10) != RESET)
    {
        pin_irq_hdr(10);
    }
    if (EXTI_GetITStatus(EXTI_LINE11) != RESET)
    {
        pin_irq_hdr(11);
    }
    if (EXTI_GetITStatus(EXTI_LINE12) != RESET)
    {
        pin_irq_hdr(12);
    }
    if (EXTI_GetITStatus(EXTI_LINE13) != RESET)
    {
        pin_irq_hdr(13);
    }
    if (EXTI_GetITStatus(EXTI_LINE14) != RESET)
    {
        pin_irq_hdr(14);
    }
    if (EXTI_GetITStatus(EXTI_LINE15) != RESET)
    {
        pin_irq_hdr(15);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}


#endif

