/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 * 2020-07-10     lik          rewrite
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include "board.h"

#define __SWM_PIN(index, gpio, pin_index)                    \
    {                                                        \
        index, GPIO##gpio, PIN##pin_index, GPIO##gpio##_IRQn \
    }
#define GPIO0 ((GPIO_TypeDef *)(0))
#define GPIO0_IRQn (GPIOA0_IRQn)

struct swm_pin_index
{
    uint32_t index;
    GPIO_TypeDef *gpio;
    uint32_t pin;
    IRQn_Type irq;
};
typedef struct swm_pin_index pin_t;

int rt_hw_pin_init(void);

#endif /* __DRV_GPIO_H__ */
