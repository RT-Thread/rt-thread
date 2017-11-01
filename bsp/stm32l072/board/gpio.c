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
 * 2016-08-29     Aubr.Cool      the first version
 */
#include <rthw.h>
#include <rtdevice.h>
#include <board.h>

#ifdef RT_USING_PIN

#include "stm32l0xx.h"

#define __RCC_GPIO_CLK_ENABLE(BIT)   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->IOPENR, BIT);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)
#define __RCC_GPIO_CLK_DISABLE(BIT)  CLEAR_BIT(RCC->IOPENR, BIT)

#define __STM32_PIN(index, gpio, gpio_index) \
    {index, RCC_IOPENR_GPIO##gpio##EN, GPIO##gpio, GPIO_PIN_##gpio_index}
#define __STM32_PIN_DEFAULT {-1, 0, 0}

/* STM32 GPIO driver */
struct pin_index
{
    int index;
    unsigned int clk;
    GPIO_TypeDef *gpio;
    uint32_t pin;
};

static const struct pin_index pins[] =
{
#ifdef UFQFPN32
     __STM32_PIN_DEFAULT,
     __STM32_PIN(1, C, 14),
     __STM32_PIN(2, C, 15),
     __STM32_PIN_DEFAULT,
     __STM32_PIN_DEFAULT,
     __STM32_PIN_DEFAULT,
     __STM32_PIN(6, A, 0),
     __STM32_PIN(7, A, 1),
     __STM32_PIN(8, A, 2),
     __STM32_PIN(9, A, 3),
     __STM32_PIN(10, A, 4),
     __STM32_PIN(11, A, 5),
     __STM32_PIN(12, A, 6),
     __STM32_PIN(13, A, 7),
     __STM32_PIN(14, B, 0),
     __STM32_PIN(15, B, 1),
     __STM32_PIN_DEFAULT,
     __STM32_PIN_DEFAULT,
     __STM32_PIN(18, A, 8),
     __STM32_PIN(19, A, 9),
     __STM32_PIN(20, A, 10),
     __STM32_PIN(21, A, 11),
     __STM32_PIN(22, A, 12),
     __STM32_PIN(23, A, 13),
     __STM32_PIN_DEFAULT,
     __STM32_PIN(25, A, 14),
     __STM32_PIN(26, B, 4),
     __STM32_PIN(27, B, 5),
     __STM32_PIN(28, B, 6),
     __STM32_PIN(29, B, 7),
     __STM32_PIN_DEFAULT,
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
inline void stm32_pin_write_early(rt_base_t pin, rt_base_t value)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    HAL_GPIO_WritePin(index->gpio, index->pin, value);
}
void stm32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    stm32_pin_write_early(pin, value);
}
inline int stm32_pin_read_early(rt_base_t pin)
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
int stm32_pin_read(rt_device_t dev, rt_base_t pin)
{
    return stm32_pin_read_early(pin);
}
void stm32_pin_mode_early(rt_base_t pin, rt_base_t mode)
{
    const struct pin_index *index;
    GPIO_InitTypeDef  GPIO_InitStructure;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.Pin   = index->pin;
    GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    __RCC_GPIO_CLK_ENABLE(index->clk);
    if (mode == GPIO_MODE_OUTPUT_PP)
    {
        /* output setting */
        GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructure.Pull = GPIO_NOPULL;
    } else if(mode == GPIO_MODE_OUTPUT_OD)
    {
        GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_OD;
        GPIO_InitStructure.Pull = GPIO_NOPULL;
    }
    else if (mode == GPIO_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStructure.Mode  = GPIO_MODE_INPUT;
        GPIO_InitStructure.Pull = GPIO_PULLUP;
    } else if(((mode & 0xFF) == GPIO_MODE_AF_PP) ||
        ((mode & 0xFF) == GPIO_MODE_AF_OD)
    ) {
        GPIO_InitStructure.Mode  = (mode & ~0xFF00);
        GPIO_InitStructure.Pull = GPIO_NOPULL;
        GPIO_InitStructure.Alternate = (mode & 0xFF00) >> 8;
    } else if(mode == GPIO_MODE_ANALOG){
        GPIO_InitStructure.Mode  = GPIO_MODE_ANALOG;
    } else {
        /* input setting:default. */
        GPIO_InitStructure.Mode  = GPIO_MODE_INPUT;
        GPIO_InitStructure.Pull = GPIO_NOPULL;
    }
    HAL_GPIO_Init(index->gpio, &GPIO_InitStructure);
}
void stm32_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    stm32_pin_mode_early(pin, mode);
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
