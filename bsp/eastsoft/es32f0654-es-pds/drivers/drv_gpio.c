/*
 * File      : drv_gpio.c
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * Change Logs:
 * Date           Author            Notes
 * 2019-01-23     wangyq            the first version
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

//static void GPIO_CLK_ENABLE(void)
//{
//    cmu_perh_clock_config(CMU_PERH_GPIO,ENABLE);
//}

/* ES32F0 GPIO driver */
struct pin_index
{
    int index;
    GPIO_TypeDef *gpio;
    uint32_t pin;
};
static const struct pin_index pins[] =
{
#if (ES32F0XX_PIN_NUMBERS == 48)
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(2, C, 13),
    __ES32F0_PIN(3, C, 14),
    __ES32F0_PIN(4, C, 15),
    __ES32F0_PIN(5, H, 0),
    __ES32F0_PIN(6, H, 1),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(8, H, 3),
    __ES32F0_PIN(9, H, 4),
    __ES32F0_PIN(10, A, 0),
    __ES32F0_PIN(11, A, 1),
    __ES32F0_PIN(12, A, 2),
    __ES32F0_PIN(13, A, 3),
    __ES32F0_PIN(14, A, 4),
    __ES32F0_PIN(15, A, 5),
    __ES32F0_PIN(16, A, 6),
    __ES32F0_PIN(17, A, 7),
    __ES32F0_PIN(18, B, 0),
    __ES32F0_PIN(19, B, 1),
    __ES32F0_PIN(20, B, 2),
    __ES32F0_PIN(21, B, 10),
    __ES32F0_PIN(22, B, 11),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(25, B, 12),
    __ES32F0_PIN(26, B, 13),
    __ES32F0_PIN(27, B, 14),
    __ES32F0_PIN(28, B, 15),
    __ES32F0_PIN(29, A, 8),
    __ES32F0_PIN(30, A, 9),
    __ES32F0_PIN(31, A, 10),
    __ES32F0_PIN(32, A, 11),
    __ES32F0_PIN(33, A, 12),
    __ES32F0_PIN(34, A, 13),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(37, A, 14),
    __ES32F0_PIN(38, A, 15),
    __ES32F0_PIN(39, B, 3),
    __ES32F0_PIN(40, B, 4),
    __ES32F0_PIN(41, B, 5),
    __ES32F0_PIN(42, B, 6),
    __ES32F0_PIN(43, B, 7),
    __ES32F0_PIN(44, H, 2),
    __ES32F0_PIN(45, B, 8),
    __ES32F0_PIN(46, B, 9),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
#endif
#if (ES32F0XX_PIN_NUMBERS == 64)
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
    __ES32F0_PIN_DEFAULT,
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
#endif
#if (ES32F0XX_PIN_NUMBERS == 100)
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(1, E, 2),
    __ES32F0_PIN(2, E, 3),
    __ES32F0_PIN(3, E, 4),
    __ES32F0_PIN(4, E, 5),
    __ES32F0_PIN(5, E, 6),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(7, C, 13),
    __ES32F0_PIN(8, C, 14),
    __ES32F0_PIN(9, C, 15),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(11, F, 4),
    __ES32F0_PIN(12, H, 0),
    __ES32F0_PIN(13, H, 1),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(15, C, 0),
    __ES32F0_PIN(16, C, 1),
    __ES32F0_PIN(17, C, 2),
    __ES32F0_PIN(18, C, 3),
    __ES32F0_PIN(19, F, 6),
    __ES32F0_PIN(20, H, 3),
    __ES32F0_PIN(21, H, 4),
    __ES32F0_PIN(22, F, 7),
    __ES32F0_PIN(23, A, 0),
    __ES32F0_PIN(24, A, 1),
    __ES32F0_PIN(25, A, 2),
    __ES32F0_PIN(26, A, 3),
    __ES32F0_PIN(27, F, 0),
    __ES32F0_PIN(28, F, 1),
    __ES32F0_PIN(29, A, 4),
    __ES32F0_PIN(30, A, 5),
    __ES32F0_PIN(31, A, 6),
    __ES32F0_PIN(32, A, 7),
    __ES32F0_PIN(33, C, 4),
    __ES32F0_PIN(34, C, 5),
    __ES32F0_PIN(35, B, 0),
    __ES32F0_PIN(36, B, 1),
    __ES32F0_PIN(37, B, 2),
    __ES32F0_PIN(38, E, 7),
    __ES32F0_PIN(39, E, 8),
    __ES32F0_PIN(40, E, 9),
    __ES32F0_PIN(41, E, 10),
    __ES32F0_PIN(42, E, 11),
    __ES32F0_PIN(43, E, 12),
    __ES32F0_PIN(44, E, 13),
    __ES32F0_PIN(45, E, 14),
    __ES32F0_PIN(46, E, 15),
    __ES32F0_PIN(47, B, 10),
    __ES32F0_PIN(48, B, 11),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(51, B, 12),
    __ES32F0_PIN(52, B, 13),
    __ES32F0_PIN(53, B, 14),
    __ES32F0_PIN(54, B, 15),
    __ES32F0_PIN(55, D, 8),
    __ES32F0_PIN(56, D, 9),
    __ES32F0_PIN(57, D, 10),
    __ES32F0_PIN(58, D, 11),
    __ES32F0_PIN(59, D, 12),
    __ES32F0_PIN(60, D, 13),
    __ES32F0_PIN(61, D, 14),
    __ES32F0_PIN(62, D, 15),
    __ES32F0_PIN(63, C, 6),
    __ES32F0_PIN(64, C, 7),
    __ES32F0_PIN(65, C, 8),
    __ES32F0_PIN(66, C, 9),
    __ES32F0_PIN(67, A, 8),
    __ES32F0_PIN(68, A, 9),
    __ES32F0_PIN(69, A, 10),
    __ES32F0_PIN(70, A, 11),
    __ES32F0_PIN(71, A, 12),
    __ES32F0_PIN(72, A, 13),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(76, A, 14),
    __ES32F0_PIN(77, A, 15),
    __ES32F0_PIN(78, C, 10),
    __ES32F0_PIN(79, C, 11),
    __ES32F0_PIN(80, C, 12),
    __ES32F0_PIN(81, D, 0),
    __ES32F0_PIN(82, D, 1),
    __ES32F0_PIN(83, D, 2),
    __ES32F0_PIN(84, D, 3),
    __ES32F0_PIN(85, D, 4),
    __ES32F0_PIN(86, D, 5),
    __ES32F0_PIN(87, D, 6),
    __ES32F0_PIN(88, D, 7),
    __ES32F0_PIN(89, B, 3),
    __ES32F0_PIN(90, B, 4),
    __ES32F0_PIN(91, B, 5),
    __ES32F0_PIN(92, B, 6),
    __ES32F0_PIN(93, B, 7),
    __ES32F0_PIN(94, H, 2),
    __ES32F0_PIN(95, B, 8),
    __ES32F0_PIN(96, B, 9),
    __ES32F0_PIN(97, E, 0),
    __ES32F0_PIN(98, E, 1),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
#endif
};

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};

//static const struct pin_irq_map pin_irq_map[] =
//{
//    {GPIO_PIN_0, EXTI0_3_IRQn},
//    {GPIO_PIN_1, EXTI0_3_IRQn},
//    {GPIO_PIN_2, EXTI0_3_IRQn},
//    {GPIO_PIN_3, EXTI0_3_IRQn},
//    {GPIO_PIN_4, EXTI4_7_IRQn},
//    {GPIO_PIN_5, EXTI4_7_IRQn},
//    {GPIO_PIN_6, EXTI4_7_IRQn},
//    {GPIO_PIN_7, EXTI4_7_IRQn},
//    {GPIO_PIN_8, EXTI8_11_IRQn},
//    {GPIO_PIN_9, EXTI8_11_IRQn},
//    {GPIO_PIN_10, EXTI8_11_IRQn},
//    {GPIO_PIN_11, EXTI8_11_IRQn},
//    {GPIO_PIN_12, EXTI12_15_IRQn},
//    {GPIO_PIN_13, EXTI12_15_IRQn},
//    {GPIO_PIN_14, EXTI12_15_IRQn},
//    {GPIO_PIN_15, EXTI12_15_IRQn},
//};

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
    gpio_write_pin(index->gpio, index->pin, value);
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
    value = gpio_read_pin(index->gpio, index->pin);
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
    gpio_init(index->gpio, index->pin, &gpio_initstruct);
}

const static struct rt_pin_ops _es32f0_pin_ops =
{
    es32f0_pin_mode,
    es32f0_pin_write,
    es32f0_pin_read,
};

int rt_hw_pin_init(void)
{
    int result;
    cmu_perh_clock_config(CMU_PERH_GPIO, ENABLE);
    result = rt_device_pin_register("pin", &_es32f0_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif
