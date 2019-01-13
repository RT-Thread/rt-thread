/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-10-20     ZYH            the first version
 */

#include <rthw.h>
#include <rtdevice.h>
#include <board.h>

#ifdef RT_USING_PIN

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
#if (STM32F7xx_PIN_NUMBERS > 48)

    static void GPIOD_CLK_ENABLE(void)
    {
    #ifdef __HAL_RCC_GPIOD_CLK_ENABLE
        __HAL_RCC_GPIOD_CLK_ENABLE();
    #endif
    }
    #if (STM32F7xx_PIN_NUMBERS > 64)
        static void GPIOE_CLK_ENABLE(void)
        {
        #ifdef __HAL_RCC_GPIOE_CLK_ENABLE
            __HAL_RCC_GPIOE_CLK_ENABLE();
        #endif
        }
        #if (STM32F7xx_PIN_NUMBERS > 100)
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
            #if (STM32F7xx_PIN_NUMBERS > 144)
                static void GPIOH_CLK_ENABLE(void)
                {
                #ifdef __HAL_RCC_GPIOH_CLK_ENABLE
                    __HAL_RCC_GPIOH_CLK_ENABLE();
                #endif
                }
                static void GPIOI_CLK_ENABLE(void)
                {
                #ifdef __HAL_RCC_GPIOI_CLK_ENABLE
                    __HAL_RCC_GPIOI_CLK_ENABLE();
                #endif
                }
                #if (STM32F7xx_PIN_NUMBERS > 176)
                    static void GPIOJ_CLK_ENABLE(void)
                    {
                    #ifdef __HAL_RCC_GPIOJ_CLK_ENABLE
                        __HAL_RCC_GPIOJ_CLK_ENABLE();
                    #endif
                    }
                    static void GPIOK_CLK_ENABLE(void)
                    {
                    #ifdef __HAL_RCC_GPIOK_CLK_ENABLE
                        __HAL_RCC_GPIOK_CLK_ENABLE();
                    #endif
                    }
                #endif
            #endif
        #endif
    #endif
#endif
/* STM32 GPIO driver */
struct pin_index
{
    int index;
    void (*rcc)(void);
    GPIO_TypeDef *gpio;
    uint32_t pin;
};

static const struct pin_index pins[] =
{
#if (STM32F7xx_PIN_NUMBERS == 36)
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(2, A, 15),
    __STM32_PIN(3, B, 5),
    __STM32_PIN(4, B, 8),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(8, A, 14),
    __STM32_PIN(9, B, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(13, C, 14),
    __STM32_PIN(13, A, 13),
    __STM32_PIN(14, B, 3),
    __STM32_PIN(15, B, 7),
    __STM32_PIN(16, C, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(18, C, 15),
    __STM32_PIN(19, A, 8),
    __STM32_PIN(20, A, 12),
    __STM32_PIN(21, B, 4),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(25, B, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(27, B, 10),
    __STM32_PIN(28, A, 2),
    __STM32_PIN(29, A, 0),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(33, B, 2),
    __STM32_PIN(34, B, 5),
    __STM32_PIN(35, A, 3),
    __STM32_PIN_DEFAULT,
#endif
#if (STM32F7xx_PIN_NUMBERS == 48)
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(2, C, 13),
    __STM32_PIN(3, C, 14),
    __STM32_PIN(4, C, 15),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(10, A, 0),
    __STM32_PIN(11, A, 1),
    __STM32_PIN(12, A, 2),
    __STM32_PIN(13, A, 3),
    __STM32_PIN(14, A, 4),
    __STM32_PIN(15, A, 5),
    __STM32_PIN(16, A, 6),
    __STM32_PIN(17, A, 7),
    __STM32_PIN(18, B, 0),
    __STM32_PIN(19, B, 1),
    __STM32_PIN(20, B, 2),
    __STM32_PIN(21, B, 10),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(25, B, 12),
    __STM32_PIN(26, B, 13),
    __STM32_PIN(27, B, 14),
    __STM32_PIN(28, B, 15),
    __STM32_PIN(29, A, 8),
    __STM32_PIN(30, A, 9),
    __STM32_PIN(31, A, 10),
    __STM32_PIN(32, A, 11),
    __STM32_PIN(33, A, 12),
    __STM32_PIN(34, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(37, A, 14),
    __STM32_PIN(38, A, 15),
    __STM32_PIN(39, B, 3),
    __STM32_PIN(40, B, 4),
    __STM32_PIN(41, B, 5),
    __STM32_PIN(42, B, 6),
    __STM32_PIN(43, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(45, B, 8),
    __STM32_PIN(46, B, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
#endif
#if (STM32F7xx_PIN_NUMBERS == 64)
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(2, C, 13),
    __STM32_PIN(3, C, 14),
    __STM32_PIN(4, C, 15),
    __STM32_PIN(5, D, 0),
    __STM32_PIN(6, D, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(8, C, 0),
    __STM32_PIN(9, C, 1),
    __STM32_PIN(10, C, 2),
    __STM32_PIN(11, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(14, A, 0),
    __STM32_PIN(15, A, 1),
    __STM32_PIN(16, A, 2),
    __STM32_PIN(17, A, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(20, A, 4),
    __STM32_PIN(21, A, 5),
    __STM32_PIN(22, A, 6),
    __STM32_PIN(23, A, 7),
    __STM32_PIN(24, C, 4),
    __STM32_PIN(25, C, 5),
    __STM32_PIN(26, B, 0),
    __STM32_PIN(27, B, 1),
    __STM32_PIN(28, B, 2),
    __STM32_PIN(29, B, 10),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(33, B, 12),
    __STM32_PIN(34, B, 13),
    __STM32_PIN(35, B, 14),
    __STM32_PIN(36, B, 15),
    __STM32_PIN(37, C, 6),
    __STM32_PIN(38, C, 7),
    __STM32_PIN(39, C, 8),
    __STM32_PIN(40, C, 9),
    __STM32_PIN(41, A, 8),
    __STM32_PIN(42, A, 9),
    __STM32_PIN(43, A, 10),
    __STM32_PIN(44, A, 11),
    __STM32_PIN(45, A, 12),
    __STM32_PIN(46, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(49, A, 14),
    __STM32_PIN(50, A, 15),
    __STM32_PIN(51, C, 10),
    __STM32_PIN(52, C, 11),
    __STM32_PIN(53, C, 12),
    __STM32_PIN(54, D, 2),
    __STM32_PIN(55, B, 3),
    __STM32_PIN(56, B, 4),
    __STM32_PIN(57, B, 5),
    __STM32_PIN(58, B, 6),
    __STM32_PIN(59, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(61, B, 8),
    __STM32_PIN(62, B, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
#endif
#if (STM32F7xx_PIN_NUMBERS == 81)
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(2, C, 10),
    __STM32_PIN(3, A, 15),
    __STM32_PIN(4, D, 0),
    __STM32_PIN(5, B, 3),
    __STM32_PIN(6, B, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(11, A, 14),
    __STM32_PIN(12, A, 12),
    __STM32_PIN(13, C, 12),
    __STM32_PIN(14, B, 4),
    __STM32_PIN(15, B, 6),
    __STM32_PIN(16, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(20, A, 13),
    __STM32_PIN(21, A, 11),
    __STM32_PIN(22, C, 11),
    __STM32_PIN(23, D, 2),
    __STM32_PIN(24, B, 8),
    __STM32_PIN(25, C, 1),
    __STM32_PIN(26, C, 13),
    __STM32_PIN(27, C, 14),
    __STM32_PIN(28, A, 10),
    __STM32_PIN(29, A, 9),
    __STM32_PIN(30, A, 8),
    __STM32_PIN(31, C, 7),
    __STM32_PIN(32, C, 6),
    __STM32_PIN(33, B, 9),
    __STM32_PIN(34, C, 2),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(36, C, 15),
    __STM32_PIN(37, C, 8),
    __STM32_PIN(38, C, 9),
    __STM32_PIN(39, B, 14),
    __STM32_PIN(40, B, 0),
    __STM32_PIN(41, A, 4),
    __STM32_PIN(42, A, 3),
    __STM32_PIN(43, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(47, D, 9),
    __STM32_PIN(48, B, 12),
    __STM32_PIN(49, E, 13),
    __STM32_PIN(50, A, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(53, C, 0),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(55, D, 10),
    __STM32_PIN(56, B, 13),
    __STM32_PIN(57, E, 14),
    __STM32_PIN(58, E, 10),
    __STM32_PIN(59, B, 1),
    __STM32_PIN(59, A, 5),
    __STM32_PIN(61, A, 0),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(64, B, 15),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(66, B, 10),
    __STM32_PIN(67, E, 11),
    __STM32_PIN(68, B, 2),
    __STM32_PIN(69, C, 4),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(71, A, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(75, E, 15),
    __STM32_PIN(76, E, 12),
    __STM32_PIN(77, E, 9),
    __STM32_PIN(78, C, 5),
    __STM32_PIN(80, A, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(81, A, 2),
#endif
#if (STM32F7xx_PIN_NUMBERS == 100 && !defined(STM32F469xx) && !defined(STM32F479xx))
    __STM32_PIN_DEFAULT,
    __STM32_PIN(1, E, 2),
    __STM32_PIN(2, E, 3),
    __STM32_PIN(3, E, 4),
    __STM32_PIN(4, E, 5),
    __STM32_PIN(5, E, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(7, C, 13),
    __STM32_PIN(8, C, 14),
    __STM32_PIN(9, C, 15),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(15, C, 0),
    __STM32_PIN(16, C, 1),
    __STM32_PIN(17, C, 2),
    __STM32_PIN(18, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(23, A, 0),
    __STM32_PIN(24, A, 1),
    __STM32_PIN(25, A, 2),
    __STM32_PIN(26, A, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(29, A, 4),
    __STM32_PIN(30, A, 5),
    __STM32_PIN(31, A, 6),
    __STM32_PIN(32, A, 7),
    __STM32_PIN(33, C, 4),
    __STM32_PIN(34, C, 5),
    __STM32_PIN(35, B, 0),
    __STM32_PIN(36, B, 1),
    __STM32_PIN(37, B, 2),
    __STM32_PIN(38, E, 7),
    __STM32_PIN(39, E, 8),
    __STM32_PIN(40, E, 9),
    __STM32_PIN(41, E, 10),
    __STM32_PIN(42, E, 11),
    __STM32_PIN(43, E, 12),
    __STM32_PIN(44, E, 13),
    __STM32_PIN(45, E, 14),
    __STM32_PIN(46, E, 15),
    __STM32_PIN(47, B, 10),
    #if defined(STM32F405xx)||defined(STM32F415xx)||defined(STM32F407xx)||defined(STM32F417xx)||defined(STM32F427xx)||defined(STM32F437xx)||defined(STM32F429xx)
        __STM32_PIN(48, B, 11),
    #else
        __STM32_PIN_DEFAULT,
    #endif
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(51, B, 12),
    __STM32_PIN(52, B, 13),
    __STM32_PIN(53, B, 14),
    __STM32_PIN(54, B, 15),
    __STM32_PIN(55, D, 8),
    __STM32_PIN(56, D, 9),
    __STM32_PIN(57, D, 10),
    __STM32_PIN(58, D, 11),
    __STM32_PIN(59, D, 12),
    __STM32_PIN(60, D, 13),
    __STM32_PIN(61, D, 14),
    __STM32_PIN(62, D, 15),
    __STM32_PIN(63, C, 6),
    __STM32_PIN(64, C, 7),
    __STM32_PIN(65, C, 8),
    __STM32_PIN(66, C, 9),
    __STM32_PIN(67, A, 8),
    __STM32_PIN(68, A, 9),
    __STM32_PIN(69, A, 10),
    __STM32_PIN(70, A, 11),
    __STM32_PIN(71, A, 12),
    __STM32_PIN(72, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(76, A, 14),
    __STM32_PIN(77, A, 15),
    __STM32_PIN(78, C, 10),
    __STM32_PIN(79, C, 11),
    __STM32_PIN(80, C, 12),
    __STM32_PIN(81, D, 0),
    __STM32_PIN(82, D, 1),
    __STM32_PIN(83, D, 2),
    __STM32_PIN(84, D, 3),
    __STM32_PIN(85, D, 4),
    __STM32_PIN(86, D, 5),
    __STM32_PIN(87, D, 6),
    __STM32_PIN(88, D, 7),
    __STM32_PIN(89, B, 3),
    __STM32_PIN(90, B, 4),
    __STM32_PIN(91, B, 5),
    __STM32_PIN(92, B, 6),
    __STM32_PIN(93, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(95, B, 8),
    __STM32_PIN(96, B, 9),
    __STM32_PIN(97, E, 0),
    __STM32_PIN(98, E, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
#endif
#if (STM32F7xx_PIN_NUMBERS == 100 && (defined(STM32F469xx) || defined(STM32F479xx)))
    __STM32_PIN_DEFAULT,
    __STM32_PIN(1, E, 2),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(4, C, 13),
    __STM32_PIN(5, C, 14),
    __STM32_PIN(6, C, 15),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(12, C, 0),
    __STM32_PIN(13, C, 1),
    __STM32_PIN(14, C, 2),
    __STM32_PIN(15, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(19, A, 0),
    __STM32_PIN(20, A, 1),
    __STM32_PIN(21, A, 2),
    __STM32_PIN(22, A, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(25, A, 4),
    __STM32_PIN(26, A, 5),
    __STM32_PIN(27, A, 6),
    __STM32_PIN(28, A, 7),
    __STM32_PIN(29, B, 0),
    __STM32_PIN(30, B, 1),
    __STM32_PIN(31, B, 2),
    __STM32_PIN(32, E, 7),
    __STM32_PIN(33, E, 8),
    __STM32_PIN(34, E, 9),
    __STM32_PIN(35, E, 10),
    __STM32_PIN(36, E, 11),
    __STM32_PIN(37, E, 12),
    __STM32_PIN(38, E, 13),
    __STM32_PIN(39, E, 14),
    __STM32_PIN(40, E, 15),
    __STM32_PIN(41, B, 10),
    __STM32_PIN(42, B, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(46, B, 12),
    __STM32_PIN(47, B, 13),
    __STM32_PIN(48, B, 14),
    __STM32_PIN(49, B, 15),
    __STM32_PIN(50, D, 8),
    __STM32_PIN(51, D, 9),
    __STM32_PIN(52, D, 10),
    __STM32_PIN(53, D, 14),
    __STM32_PIN(54, D, 15),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(66, C, 6),
    __STM32_PIN(67, C, 7),
    __STM32_PIN(68, C, 8),
    __STM32_PIN(69, C, 9),
    __STM32_PIN(70, A, 8),
    __STM32_PIN(71, A, 9),
    __STM32_PIN(72, A, 10),
    __STM32_PIN(73, A, 11),
    __STM32_PIN(74, A, 12),
    __STM32_PIN(75, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(79, A, 14),
    __STM32_PIN(80, A, 15),
    __STM32_PIN(81, C, 10),
    __STM32_PIN(82, C, 11),
    __STM32_PIN(83, C, 12),
    __STM32_PIN(84, D, 0),
    __STM32_PIN(85, D, 1),
    __STM32_PIN(86, D, 2),
    __STM32_PIN(87, D, 3),
    __STM32_PIN(88, D, 4),
    __STM32_PIN(89, D, 5),
    __STM32_PIN(90, D, 6),
    __STM32_PIN(91, D, 7),
    __STM32_PIN(92, B, 3),
    __STM32_PIN(93, B, 4),
    __STM32_PIN(94, B, 5),
    __STM32_PIN(95, B, 6),
    __STM32_PIN(96, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(98, B, 8),
    __STM32_PIN(99, B, 9),
    __STM32_PIN_DEFAULT,
#endif
#if (STM32F7xx_PIN_NUMBERS == 144)
    __STM32_PIN_DEFAULT,
    __STM32_PIN(1, E, 2),
    __STM32_PIN(2, E, 3),
    __STM32_PIN(3, E, 4),
    __STM32_PIN(4, E, 5),
    __STM32_PIN(5, E, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(7, C, 13),
    __STM32_PIN(8, C, 14),
    __STM32_PIN(9, C, 15),
    __STM32_PIN(10, F, 0),
    __STM32_PIN(11, F, 1),
    __STM32_PIN(12, F, 2),
    __STM32_PIN(13, F, 3),
    __STM32_PIN(14, F, 4),
    __STM32_PIN(15, F, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(18, F, 6),
    __STM32_PIN(19, F, 7),
    __STM32_PIN(20, F, 8),
    __STM32_PIN(21, F, 9),
    __STM32_PIN(22, F, 10),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(26, C, 0),
    __STM32_PIN(27, C, 1),
    __STM32_PIN(28, C, 2),
    __STM32_PIN(29, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(34, A, 0),
    __STM32_PIN(35, A, 1),
    __STM32_PIN(36, A, 2),
    __STM32_PIN(37, A, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(40, A, 4),
    __STM32_PIN(41, A, 5),
    __STM32_PIN(42, A, 6),
    __STM32_PIN(43, A, 7),
    __STM32_PIN(44, C, 4),
    __STM32_PIN(45, C, 5),
    __STM32_PIN(46, B, 0),
    __STM32_PIN(47, B, 1),
    __STM32_PIN(48, B, 2),
    __STM32_PIN(49, F, 11),
    __STM32_PIN(50, F, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(53, F, 13),
    __STM32_PIN(54, F, 14),
    __STM32_PIN(55, F, 15),
    __STM32_PIN(56, G, 0),
    __STM32_PIN(57, G, 1),
    __STM32_PIN(58, E, 7),
    __STM32_PIN(59, E, 8),
    __STM32_PIN(60, E, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(63, E, 10),
    __STM32_PIN(64, E, 11),
    __STM32_PIN(65, E, 12),
    __STM32_PIN(66, E, 13),
    __STM32_PIN(67, E, 14),
    __STM32_PIN(68, E, 15),
    __STM32_PIN(69, B, 10),
    __STM32_PIN(70, B, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(73, B, 12),
    __STM32_PIN(74, B, 13),
    __STM32_PIN(75, B, 14),
    __STM32_PIN(76, B, 15),
    __STM32_PIN(77, D, 8),
    __STM32_PIN(78, D, 9),
    __STM32_PIN(79, D, 10),
    __STM32_PIN(80, D, 11),
    __STM32_PIN(81, D, 12),
    __STM32_PIN(82, D, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(85, D, 14),
    __STM32_PIN(86, D, 15),
    __STM32_PIN(87, G, 2),
    __STM32_PIN(88, G, 3),
    __STM32_PIN(89, G, 4),
    __STM32_PIN(90, G, 5),
    __STM32_PIN(91, G, 6),
    __STM32_PIN(92, G, 7),
    __STM32_PIN(93, G, 8),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(96, C, 6),
    __STM32_PIN(97, C, 7),
    __STM32_PIN(98, C, 8),
    __STM32_PIN(99, C, 9),
    __STM32_PIN(100, A, 8),
    __STM32_PIN(101, A, 9),
    __STM32_PIN(102, A, 10),
    __STM32_PIN(103, A, 11),
    __STM32_PIN(104, A, 12),
    __STM32_PIN(105, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(109, A, 14),
    __STM32_PIN(110, A, 15),
    __STM32_PIN(111, C, 10),
    __STM32_PIN(112, C, 11),
    __STM32_PIN(113, C, 12),
    __STM32_PIN(114, D, 0),
    __STM32_PIN(115, D, 1),
    __STM32_PIN(116, D, 2),
    __STM32_PIN(117, D, 3),
    __STM32_PIN(118, D, 4),
    __STM32_PIN(119, D, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(122, D, 6),
    __STM32_PIN(123, D, 7),
    __STM32_PIN(124, G, 9),
    __STM32_PIN(125, G, 10),
    __STM32_PIN(126, G, 11),
    __STM32_PIN(127, G, 12),
    __STM32_PIN(128, G, 13),
    __STM32_PIN(129, G, 14),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(132, G, 15),
    __STM32_PIN(133, B, 3),
    __STM32_PIN(134, B, 4),
    __STM32_PIN(135, B, 5),
    __STM32_PIN(136, B, 6),
    __STM32_PIN(137, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(139, B, 8),
    __STM32_PIN(140, B, 9),
    __STM32_PIN(141, E, 0),
    __STM32_PIN(142, E, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
#endif
#if (STM32F7xx_PIN_NUMBERS == 169)
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(2, I, 6),
    __STM32_PIN(3, I, 5),
    __STM32_PIN(4, E, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(6, B, 4),
    __STM32_PIN(7, G, 12),
    __STM32_PIN(8, D, 7),
    __STM32_PIN(9, D, 3),
    __STM32_PIN(10, C, 12),
    __STM32_PIN(11, A, 14),
    __STM32_PIN(12, I, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(14, I, 7),
    __STM32_PIN(15, E, 2),
    __STM32_PIN(16, I, 4),
    __STM32_PIN(17, E, 0),
    __STM32_PIN(18, B, 7),
    __STM32_PIN(19, B, 3),
    __STM32_PIN(20, G, 11),
    __STM32_PIN(21, D, 6),
    __STM32_PIN(22, D, 2),
    __STM32_PIN(23, C, 11),
    __STM32_PIN(24, A, 15),
    __STM32_PIN(25, I, 2),
    __STM32_PIN(26, I, 0),
    __STM32_PIN(27, E, 3),
    __STM32_PIN(28, E, 4),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(30, B, 9),
    __STM32_PIN(31, B, 6),
    __STM32_PIN(32, G, 15),
    __STM32_PIN(33, G, 10),
    __STM32_PIN(34, D, 5),
    __STM32_PIN(35, D, 1),
    __STM32_PIN(36, C, 10),
    __STM32_PIN(37, I, 1),
    __STM32_PIN(38, H, 15),
    __STM32_PIN(39, H, 14),
    __STM32_PIN(40, E, 5),
    __STM32_PIN(41, E, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(43, B, 8),
    __STM32_PIN(44, B, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(47, D, 4),
    __STM32_PIN(48, D, 0),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(52, H, 13),
    __STM32_PIN(53, C, 14),
    __STM32_PIN(54, I, 9),
    __STM32_PIN(55, I, 10),
    __STM32_PIN(56, C, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(60, A, 9),
    __STM32_PIN(61, A, 10),
    __STM32_PIN(62, A, 11),
    __STM32_PIN(63, A, 12),
    __STM32_PIN(64, A, 13),
    __STM32_PIN(65, A, 8),
    __STM32_PIN(66, C, 15),
    __STM32_PIN(67, F, 0),
    __STM32_PIN(68, F, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(74, C, 6),
    __STM32_PIN(75, C, 7),
    __STM32_PIN(76, C, 8),
    __STM32_PIN(77, C, 9),
    __STM32_PIN(78, G, 8),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(81, F, 4),
    __STM32_PIN(82, F, 3),
    __STM32_PIN(83, F, 2),
    __STM32_PIN(84, C, 0),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(89, G, 6),
    __STM32_PIN(90, G, 7),
    __STM32_PIN(91, G, 5),
    __STM32_PIN(92, F, 10),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(94, F, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(96, C, 1),
    __STM32_PIN(97, C, 2),
    __STM32_PIN(98, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(100, E, 13),
    __STM32_PIN(101, D, 11),
    __STM32_PIN(102, D, 14),
    __STM32_PIN(103, G, 4),
    __STM32_PIN(104, G, 2),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(109, A, 0),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(112, E, 8),
    __STM32_PIN(113, E, 14),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(116, D, 15),
    __STM32_PIN(117, D, 12),
    __STM32_PIN(118, A, 1),
    __STM32_PIN(119, A, 2),
    __STM32_PIN(120, A, 3),
    __STM32_PIN(121, A, 7),
    __STM32_PIN(122, B, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(124, F, 14),
    __STM32_PIN(125, E, 9),
    __STM32_PIN(126, E, 15),
    __STM32_PIN(127, H, 9),
    __STM32_PIN(128, D, 10),
    __STM32_PIN(129, D, 13),
    __STM32_PIN(130, D, 9),
    __STM32_PIN(131, H, 3),
    __STM32_PIN(132, H, 2),
    __STM32_PIN(133, H, 5),
    __STM32_PIN(134, C, 4),
    __STM32_PIN(135, B, 2),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(137, F, 15),
    __STM32_PIN(138, E, 10),
    __STM32_PIN(139, B, 10),
    __STM32_PIN(140, H, 8),
    __STM32_PIN(141, H, 12),
    __STM32_PIN(142, D, 8),
    __STM32_PIN(143, B, 15),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(145, H, 4),
    __STM32_PIN(146, A, 5),
    __STM32_PIN(147, C, 5),
    __STM32_PIN(148, F, 11),
    __STM32_PIN(149, F, 13),
    __STM32_PIN(150, G, 1),
    __STM32_PIN(151, E, 11),
    __STM32_PIN(152, B, 11),
    __STM32_PIN(153, H, 7),
    __STM32_PIN(154, H, 11),
    __STM32_PIN(155, B, 13),
    __STM32_PIN(156, B, 14),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(158, A, 4),
    __STM32_PIN(159, A, 6),
    __STM32_PIN(160, B, 0),
    __STM32_PIN(161, F, 12),
    __STM32_PIN(162, G, 0),
    __STM32_PIN(163, E, 7),
    __STM32_PIN(164, E, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(166, E, 12),
    __STM32_PIN(167, H, 10),
    __STM32_PIN(168, B, 12),
    __STM32_PIN_DEFAULT,
#endif
#if (STM32F7xx_PIN_NUMBERS == 176)
    __STM32_PIN_DEFAULT,
    __STM32_PIN(1, E, 2),
    __STM32_PIN(2, E, 3),
    __STM32_PIN(3, E, 4),
    __STM32_PIN(4, E, 5),
    __STM32_PIN(5, E, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(7, I, 8),
    __STM32_PIN(8, C, 13),
    __STM32_PIN(9, C, 14),
    __STM32_PIN(10, C, 15),
    __STM32_PIN(11, I, 9),
    __STM32_PIN(12, I, 10),
    __STM32_PIN(13, I, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(16, F, 0),
    __STM32_PIN(17, F, 1),
    __STM32_PIN(18, F, 2),
    __STM32_PIN(19, F, 3),
    __STM32_PIN(20, F, 4),
    __STM32_PIN(21, F, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(24, F, 6),
    __STM32_PIN(25, F, 7),
    __STM32_PIN(26, F, 8),
    __STM32_PIN(27, F, 9),
    __STM32_PIN(28, F, 10),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(32, C, 0),
    __STM32_PIN(33, C, 1),
    __STM32_PIN(34, C, 2),
    __STM32_PIN(35, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(40, A, 0),
    __STM32_PIN(41, A, 1),
    __STM32_PIN(42, A, 2),
    __STM32_PIN(43, H, 2),
    __STM32_PIN(44, H, 3),
    __STM32_PIN(45, H, 4),
    __STM32_PIN(46, H, 5),
    __STM32_PIN(47, A, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(50, A, 4),
    __STM32_PIN(51, A, 5),
    __STM32_PIN(52, A, 6),
    __STM32_PIN(53, A, 7),
    __STM32_PIN(54, C, 4),
    __STM32_PIN(55, C, 5),
    __STM32_PIN(56, B, 0),
    __STM32_PIN(57, B, 1),
    __STM32_PIN(58, B, 2),
    __STM32_PIN(59, F, 11),
    __STM32_PIN(60, F, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(63, F, 13),
    __STM32_PIN(64, F, 14),
    __STM32_PIN(65, F, 15),
    __STM32_PIN(66, G, 0),
    __STM32_PIN(67, G, 1),
    __STM32_PIN(68, E, 7),
    __STM32_PIN(69, E, 8),
    __STM32_PIN(70, E, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(73, E, 10),
    __STM32_PIN(74, E, 11),
    __STM32_PIN(75, E, 12),
    __STM32_PIN(76, E, 13),
    __STM32_PIN(77, E, 14),
    __STM32_PIN(78, E, 15),
    __STM32_PIN(79, B, 10),
    __STM32_PIN(80, B, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(83, H, 6),
    __STM32_PIN(84, H, 7),
    __STM32_PIN(85, H, 8),
    __STM32_PIN(86, H, 9),
    __STM32_PIN(87, H, 10),
    __STM32_PIN(88, H, 11),
    __STM32_PIN(89, H, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(92, B, 12),
    __STM32_PIN(93, B, 13),
    __STM32_PIN(94, B, 14),
    __STM32_PIN(95, B, 15),
    __STM32_PIN(96, D, 8),
    __STM32_PIN(97, D, 9),
    __STM32_PIN(98, D, 10),
    __STM32_PIN(99, D, 11),
    __STM32_PIN(100, D, 12),
    __STM32_PIN(101, D, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(104, D, 14),
    __STM32_PIN(105, D, 15),
    __STM32_PIN(106, G, 2),
    __STM32_PIN(107, G, 3),
    __STM32_PIN(108, G, 4),
    __STM32_PIN(109, G, 5),
    __STM32_PIN(110, G, 6),
    __STM32_PIN(111, G, 7),
    __STM32_PIN(112, G, 8),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(115, C, 6),
    __STM32_PIN(116, C, 7),
    __STM32_PIN(117, C, 8),
    __STM32_PIN(118, C, 9),
    __STM32_PIN(119, A, 8),
    __STM32_PIN(120, A, 9),
    __STM32_PIN(121, A, 10),
    __STM32_PIN(122, A, 11),
    __STM32_PIN(123, A, 12),
    __STM32_PIN(124, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(128, H, 13),
    __STM32_PIN(129, H, 14),
    __STM32_PIN(130, H, 15),
    __STM32_PIN(131, I, 0),
    __STM32_PIN(132, I, 1),
    __STM32_PIN(133, I, 2),
    __STM32_PIN(134, I, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(137, A, 14),
    __STM32_PIN(138, A, 15),
    __STM32_PIN(139, C, 10),
    __STM32_PIN(140, C, 11),
    __STM32_PIN(141, C, 12),
    __STM32_PIN(142, D, 0),
    __STM32_PIN(143, D, 1),
    __STM32_PIN(144, D, 2),
    __STM32_PIN(145, D, 3),
    __STM32_PIN(146, D, 4),
    __STM32_PIN(147, D, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(150, D, 6),
    __STM32_PIN(151, D, 7),
    __STM32_PIN(152, G, 9),
    __STM32_PIN(153, G, 10),
    __STM32_PIN(154, G, 11),
    __STM32_PIN(155, G, 12),
    __STM32_PIN(156, G, 13),
    __STM32_PIN(157, G, 14),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(160, G, 15),
    __STM32_PIN(161, B, 3),
    __STM32_PIN(162, B, 4),
    __STM32_PIN(163, B, 5),
    __STM32_PIN(164, B, 6),
    __STM32_PIN(165, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(167, B, 8),
    __STM32_PIN(168, B, 9),
    __STM32_PIN(169, E, 0),
    __STM32_PIN(170, E, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(173, I, 4),
    __STM32_PIN(174, I, 5),
    __STM32_PIN(175, I, 6),
    __STM32_PIN(176, I, 7),
#endif
#if (STM32F7xx_PIN_NUMBERS == 208)
    __STM32_PIN_DEFAULT,
    __STM32_PIN(1, E, 2),
    __STM32_PIN(2, E, 3),
    __STM32_PIN(3, E, 4),
    __STM32_PIN(4, E, 5),
    __STM32_PIN(5, E, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(7, I, 8),
    __STM32_PIN(8, C, 13),
    __STM32_PIN(9, C, 14),
    __STM32_PIN(10, C, 15),
    __STM32_PIN(11, I, 9),
    __STM32_PIN(12, I, 10),
    __STM32_PIN(13, I, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(16, F, 0),
    __STM32_PIN(17, F, 1),
    __STM32_PIN(18, F, 2),
    __STM32_PIN(19, I, 12),
    __STM32_PIN(20, I, 13),
    __STM32_PIN(21, I, 14),
    __STM32_PIN(22, F, 3),
    __STM32_PIN(23, F, 4),
    __STM32_PIN(24, F, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(27, F, 6),
    __STM32_PIN(28, F, 7),
    __STM32_PIN(29, F, 8),
    __STM32_PIN(30, F, 9),
    __STM32_PIN(31, F, 10),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(35, C, 0),
    __STM32_PIN(36, C, 1),
    __STM32_PIN(37, C, 2),
    __STM32_PIN(38, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(43, A, 0),
    __STM32_PIN(44, A, 1),
    __STM32_PIN(45, A, 2),
    __STM32_PIN(46, H, 2),
    __STM32_PIN(47, H, 3),
    __STM32_PIN(48, H, 4),
    __STM32_PIN(49, H, 5),
    __STM32_PIN(50, A, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(53, A, 4),
    __STM32_PIN(54, A, 5),
    __STM32_PIN(55, A, 6),
    __STM32_PIN(56, A, 7),
    __STM32_PIN(57, C, 4),
    __STM32_PIN(58, C, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(61, B, 0),
    __STM32_PIN(62, B, 1),
    __STM32_PIN(63, B, 2),
    __STM32_PIN(64, I, 15),
    __STM32_PIN(65, J, 0),
    __STM32_PIN(66, J, 1),
    __STM32_PIN(67, J, 2),
    __STM32_PIN(68, J, 3),
    __STM32_PIN(69, J, 4),
    __STM32_PIN(70, F, 11),
    __STM32_PIN(71, F, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(74, F, 13),
    __STM32_PIN(75, F, 14),
    __STM32_PIN(76, F, 15),
    __STM32_PIN(77, G, 0),
    __STM32_PIN(78, G, 1),
    __STM32_PIN(79, E, 7),
    __STM32_PIN(80, E, 8),
    __STM32_PIN(81, E, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(84, E, 10),
    __STM32_PIN(85, E, 11),
    __STM32_PIN(86, E, 12),
    __STM32_PIN(87, E, 13),
    __STM32_PIN(88, E, 14),
    __STM32_PIN(89, E, 15),
    __STM32_PIN(90, B, 10),
    __STM32_PIN(91, B, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(95, J, 5),
    __STM32_PIN(96, H, 6),
    __STM32_PIN(97, H, 7),
    __STM32_PIN(98, H, 8),
    __STM32_PIN(99, H, 9),
    __STM32_PIN(100, H, 10),
    __STM32_PIN(101, H, 11),
    __STM32_PIN(102, H, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(104, B, 12),
    __STM32_PIN(105, B, 13),
    __STM32_PIN(106, B, 14),
    __STM32_PIN(107, B, 15),
    __STM32_PIN(108, D, 8),
    __STM32_PIN(109, D, 9),
    __STM32_PIN(110, D, 10),
    __STM32_PIN(111, D, 11),
    __STM32_PIN(112, D, 12),
    __STM32_PIN(113, D, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(104, D, 14),
    __STM32_PIN(105, D, 15),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(129, G, 2),
    __STM32_PIN(130, G, 3),
    __STM32_PIN(131, G, 4),
    __STM32_PIN(132, G, 5),
    __STM32_PIN(133, G, 6),
    __STM32_PIN(134, G, 7),
    __STM32_PIN(135, G, 8),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(138, C, 6),
    __STM32_PIN(139, C, 7),
    __STM32_PIN(140, C, 8),
    __STM32_PIN(141, C, 9),
    __STM32_PIN(142, A, 8),
    __STM32_PIN(143, A, 9),
    __STM32_PIN(144, A, 10),
    __STM32_PIN(145, A, 11),
    __STM32_PIN(146, A, 12),
    __STM32_PIN(147, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(151, H, 13),
    __STM32_PIN(152, H, 14),
    __STM32_PIN(153, H, 15),
    __STM32_PIN(154, I, 0),
    __STM32_PIN(155, I, 1),
    __STM32_PIN(156, I, 2),
    __STM32_PIN(157, I, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(159, A, 14),
    __STM32_PIN(160, A, 15),
    __STM32_PIN(161, C, 10),
    __STM32_PIN(162, C, 11),
    __STM32_PIN(163, C, 12),
    __STM32_PIN(164, D, 0),
    __STM32_PIN(165, D, 1),
    __STM32_PIN(166, D, 2),
    __STM32_PIN(167, D, 3),
    __STM32_PIN(168, D, 4),
    __STM32_PIN(169, D, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(172, D, 6),
    __STM32_PIN(173, D, 7),
    __STM32_PIN(174, J, 12),
    __STM32_PIN(175, J, 13),
    __STM32_PIN(176, J, 14),
    __STM32_PIN(177, J, 15),
    __STM32_PIN(178, G, 9),
    __STM32_PIN(179, G, 10),
    __STM32_PIN(180, G, 11),
    __STM32_PIN(181, G, 12),
    __STM32_PIN(182, G, 13),
    __STM32_PIN(183, G, 14),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(186, K, 3),
    __STM32_PIN(187, K, 4),
    __STM32_PIN(188, K, 5),
    __STM32_PIN(189, K, 6),
    __STM32_PIN(190, K, 7),
    __STM32_PIN(191, G, 15),
    __STM32_PIN(192, B, 3),
    __STM32_PIN(193, B, 4),
    __STM32_PIN(194, B, 5),
    __STM32_PIN(195, B, 6),
    __STM32_PIN(196, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(198, B, 8),
    __STM32_PIN(199, B, 9),
    __STM32_PIN(200, E, 0),
    __STM32_PIN(201, E, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(205, I, 4),
    __STM32_PIN(206, I, 5),
    __STM32_PIN(207, I, 6),
    __STM32_PIN(208, I, 7),
#endif
#if (STM32F7xx_PIN_NUMBERS == 216)
    __STM32_PIN_DEFAULT,
    __STM32_PIN(1, E, 2),
    __STM32_PIN(2, E, 3),
    __STM32_PIN(3, E, 4),
    __STM32_PIN(4, E, 5),
    __STM32_PIN(5, E, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(9, I, 8),
    __STM32_PIN(10, C, 13),
    __STM32_PIN(11, C, 14),
    __STM32_PIN(12, C, 15),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(14, I, 9),
    __STM32_PIN(15, I, 10),
    __STM32_PIN(16, I, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(19, F, 0),
    __STM32_PIN(20, F, 1),
    __STM32_PIN(21, F, 2),
    __STM32_PIN(22, I, 12),
    __STM32_PIN(23, I, 13),
    __STM32_PIN(24, I, 14),
    __STM32_PIN(25, F, 3),
    __STM32_PIN(26, F, 4),
    __STM32_PIN(27, F, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(30, F, 6),
    __STM32_PIN(31, F, 7),
    __STM32_PIN(32, F, 8),
    __STM32_PIN(33, F, 9),
    __STM32_PIN(34, F, 10),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(38, C, 0),
    __STM32_PIN(39, C, 1),
    __STM32_PIN(40, C, 2),
    __STM32_PIN(41, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(48, A, 0),
    __STM32_PIN(49, A, 1),
    __STM32_PIN(50, A, 2),
    __STM32_PIN(51, H, 2),
    __STM32_PIN(52, H, 3),
    __STM32_PIN(53, H, 4),
    __STM32_PIN(54, H, 5),
    __STM32_PIN(55, A, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(59, A, 4),
    __STM32_PIN(60, A, 5),
    __STM32_PIN(61, A, 6),
    __STM32_PIN(62, A, 7),
    __STM32_PIN(63, C, 4),
    __STM32_PIN(64, C, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(67, B, 0),
    __STM32_PIN(68, B, 1),
    __STM32_PIN(69, B, 2),
    __STM32_PIN(70, I, 15),
    __STM32_PIN(71, J, 0),
    __STM32_PIN(72, J, 1),
    __STM32_PIN(73, J, 2),
    __STM32_PIN(74, J, 3),
    __STM32_PIN(75, J, 4),
    __STM32_PIN(76, F, 11),
    __STM32_PIN(77, F, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(80, F, 13),
    __STM32_PIN(81, F, 14),
    __STM32_PIN(82, F, 15),
    __STM32_PIN(83, G, 0),
    __STM32_PIN(84, G, 1),
    __STM32_PIN(85, E, 7),
    __STM32_PIN(86, E, 8),
    __STM32_PIN(87, E, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(90, E, 10),
    __STM32_PIN(91, E, 11),
    __STM32_PIN(92, E, 12),
    __STM32_PIN(93, E, 13),
    __STM32_PIN(94, E, 14),
    __STM32_PIN(95, E, 15),
    __STM32_PIN(96, B, 10),
    __STM32_PIN(97, B, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(101, J, 5),
    __STM32_PIN(102, H, 6),
    __STM32_PIN(103, H, 7),
    __STM32_PIN(104, H, 8),
    __STM32_PIN(105, H, 9),
    __STM32_PIN(106, H, 10),
    __STM32_PIN(107, H, 11),
    __STM32_PIN(108, H, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(111, B, 12),
    __STM32_PIN(112, B, 13),
    __STM32_PIN(113, B, 14),
    __STM32_PIN(114, B, 15),
    __STM32_PIN(115, D, 8),
    __STM32_PIN(116, D, 9),
    __STM32_PIN(117, D, 10),
    __STM32_PIN(118, D, 11),
    __STM32_PIN(119, D, 12),
    __STM32_PIN(120, D, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(123, D, 14),
    __STM32_PIN(124, D, 15),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(136, G, 2),
    __STM32_PIN(137, G, 3),
    __STM32_PIN(138, G, 4),
    __STM32_PIN(139, G, 5),
    __STM32_PIN(140, G, 6),
    __STM32_PIN(141, G, 7),
    __STM32_PIN(142, G, 8),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(145, C, 6),
    __STM32_PIN(146, C, 7),
    __STM32_PIN(147, C, 8),
    __STM32_PIN(148, C, 9),
    __STM32_PIN(149, A, 8),
    __STM32_PIN(150, A, 9),
    __STM32_PIN(151, A, 10),
    __STM32_PIN(152, A, 11),
    __STM32_PIN(153, A, 12),
    __STM32_PIN(154, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(158, H, 13),
    __STM32_PIN(159, H, 14),
    __STM32_PIN(160, H, 15),
    __STM32_PIN(161, I, 0),
    __STM32_PIN(162, I, 1),
    __STM32_PIN(163, I, 2),
    __STM32_PIN(164, I, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(167, A, 14),
    __STM32_PIN(168, A, 15),
    __STM32_PIN(169, C, 10),
    __STM32_PIN(170, C, 11),
    __STM32_PIN(171, C, 12),
    __STM32_PIN(172, D, 0),
    __STM32_PIN(173, D, 1),
    __STM32_PIN(174, D, 2),
    __STM32_PIN(175, D, 3),
    __STM32_PIN(176, D, 4),
    __STM32_PIN(177, D, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(180, D, 6),
    __STM32_PIN(181, D, 7),
    __STM32_PIN(182, J, 12),
    __STM32_PIN(183, J, 13),
    __STM32_PIN(184, J, 14),
    __STM32_PIN(185, J, 15),
    __STM32_PIN(186, G, 9),
    __STM32_PIN(187, G, 10),
    __STM32_PIN(188, G, 11),
    __STM32_PIN(189, G, 12),
    __STM32_PIN(190, G, 13),
    __STM32_PIN(191, G, 14),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(194, K, 3),
    __STM32_PIN(195, K, 4),
    __STM32_PIN(196, K, 5),
    __STM32_PIN(197, K, 6),
    __STM32_PIN(198, K, 7),
    __STM32_PIN(199, G, 15),
    __STM32_PIN(200, B, 3),
    __STM32_PIN(201, B, 4),
    __STM32_PIN(202, B, 5),
    __STM32_PIN(203, B, 6),
    __STM32_PIN(204, B, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(206, B, 8),
    __STM32_PIN(207, B, 9),
    __STM32_PIN(208, E, 0),
    __STM32_PIN(209, E, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(213, I, 4),
    __STM32_PIN(214, I, 5),
    __STM32_PIN(215, I, 6),
    __STM32_PIN(216, I, 7),
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

void stm32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    HAL_GPIO_WritePin(index->gpio, index->pin, (GPIO_PinState)value);
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

    value = HAL_GPIO_ReadPin(index->gpio, index->pin);

    return value;
}

void stm32_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
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
rt_err_t stm32_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
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
rt_err_t stm32_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
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
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
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
        stm32_pin_detach_irq,
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
