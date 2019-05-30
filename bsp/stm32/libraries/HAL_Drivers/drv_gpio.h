/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-11-06     balanceTWK        first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <drv_common.h>
#include <board.h>

enum
{
#ifdef GPIOA
    GPIOA_PORT,
#endif
#ifdef GPIOB
    GPIOB_PORT,
#endif
#ifdef GPIOC
    GPIOC_PORT,
#endif
#ifdef GPIOD
    GPIOD_PORT,
#endif
#ifdef GPIOE
    GPIOE_PORT,
#endif
#ifdef GPIOF
    GPIOF_PORT,
#endif
#ifdef GPIOG
    GPIOG_PORT,
#endif
#ifdef GPIOH
    GPIOH_PORT,
#endif
#ifdef GPIOI
    GPIOI_PORT,
#endif
#ifdef GPIOJ
    GPIOJ_PORT,
#endif
#ifdef GPIOK
    GPIOK_PORT,
#endif
};

#define GET_PIN(PORTx,PIN) (rt_base_t)(GPIO##PORTx##_PORT*16 + PIN)

#define __STM32_PIN(gpio, gpio_index)                                         \
    {                                                                         \
        GET_PIN(gpio,gpio_index), GPIO##gpio, GPIO_PIN_##gpio_index           \
    }

#define __STM32_PIN_RESERVE                                                   \
    {                                                                         \
        -1, 0, 0                                                              \
    }

/* STM32 GPIO driver */
struct pin_index
{
    int index;
    GPIO_TypeDef *gpio;
    uint32_t pin;
};

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};

int rt_hw_pin_init(void);

#endif /* __DRV_GPIO_H__ */

