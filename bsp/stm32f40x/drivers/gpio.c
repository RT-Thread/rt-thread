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
 * 2015-01-05     Bernard      the first version
 */

#include <rthw.h>
#include <rtdevice.h>
#include <board.h>

#ifdef RT_USING_PIN

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
    { 0, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_7},
    { 1, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_6},
    { 2, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_8},
    { 3, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_11},
    { 4, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_14},
    { 5, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_13},
    { 6, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_11},
    { 7, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_9},

    { 8, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_12},
    { 9, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_13},
    {10, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_14},
    {11, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_15},
    {12, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_6},
    {13, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_5},

    {14, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_8},
    {15, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_9},
    {16, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_5},
    {17, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_6},
    {18, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_6},
    {19, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_7},
    {20, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_9},
    {21, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_8},

    {22, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_12},
    {23, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_2},
    {24, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_1},
    {25, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_0},
    {26, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_9},
    {27, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_13},
    {28, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_15},
    {29, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_12},
    {30, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_10},
    {31, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_8},
    {32, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_7},
    {33, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_4},
    {34, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_3},
    {35, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_2},
    {36, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_1},
    {37, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_0},
    {38, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_11},
    {39, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_10},
    {40, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_7},
    {41, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_3},
    {42, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_4},
    {43, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_8},
    {44, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_15},
    {45, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_14},
    {46, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_11},
    {47, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_5},
    {48, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_10},
    {49, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_15},
    {50, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_4},
    {51, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_7},
    {52, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_3},
    {53, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_4},
};

#define ITEM_NUM(items) sizeof(items)/sizeof(items[0])
const struct pin_index *get_pin(uint8_t pin)
{
    const struct pin_index *index;

    if (pin < ITEM_NUM(pins))
    {
        index = &pins[pin];
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
    GPIO_InitStructure.GPIO_Pin     = index->pin;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_100MHz;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
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
    else
    {
        /* input setting:default. */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
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
    rt_device_pin_register("pin", &_stm32_pin_ops, RT_NULL);
    return 0;
}
INIT_BOARD_EXPORT(stm32_hw_pin_init);

#endif
