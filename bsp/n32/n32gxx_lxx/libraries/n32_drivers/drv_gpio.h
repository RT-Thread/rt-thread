/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __N32_PORT(port)  GPIO##port##_BASE

#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__N32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)

#define __N32_PIN(index, gpio, gpio_pin)                                \
    {                                                                   \
        index, gpio, gpio_pin                                           \
    }

#define __N32_PIN_RESERVE                                               \
    {                                                                   \
        -1, 0, 0                                                        \
    }

/* GPIO driver */
struct pin_index
{
    int index;
    GPIO_Module *gpio;
    uint32_t pin;
};

struct pin_irq_map
{
    uint16_t pinbit;
    IRQn_Type irqno;
};

int rt_hw_pin_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

