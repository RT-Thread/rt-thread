/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-08-20     BruceOu           the first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined SOC_SERIES_GD32F10x
#include "gd32f10x_gpio.h"
#elif defined SOC_SERIES_GD32F20x
#include "gd32f20x_gpio.h"
#elif defined SOC_SERIES_GD32F30x
#include "gd32f30x_gpio.h"
#elif defined SOC_SERIES_GD32F4xx
#include "gd32f4xx_gpio.h"
#elif defined SOC_SERIES_GD32H7xx
#include "gd32h7xx_gpio.h"
#elif defined SOC_SERIES_GD32E50x
#include "gd32e50x_gpio.h"
#endif

#define __GD32_PORT(port)  GPIO##port

#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32H7xx
#define GD32_PIN(index, port, pin) {index, RCU_GPIO##port,      \
                                    GPIO##port, GPIO_PIN_##pin, \
                                    EXTI_SOURCE_GPIO##port,     \
                                    EXTI_SOURCE_PIN##pin}
#else
#define GD32_PIN(index, port, pin) {index, RCU_GPIO##port,        \
                                    GPIO##port, GPIO_PIN_##pin,   \
                                    GPIO_PORT_SOURCE_GPIO##port,  \
                                    GPIO_PIN_SOURCE_##pin}

#endif

#define GD32_PIN_DEFAULT            {-1, (rcu_periph_enum)0, 0, 0, 0, 0}

#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__GD32_PORT(PORTx) - (rt_base_t)GPIO_BASE)/(0x0400UL) )) + PIN)

#define PIN_PORT(pin) ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin) ((uint8_t)((pin) & 0xFu))

#define PIN_GDPORT(pin) (GPIO_BASE + (0x400u * PIN_PORT(pin)))
#define PIN_GDPIN(pin) ((uint16_t)(1u << PIN_NO(pin)))

struct pin_index
{
    rt_int16_t index;
    rcu_periph_enum clk;
    rt_uint32_t gpio_periph;
    rt_uint32_t pin;
    rt_uint8_t port_src;
    rt_uint8_t pin_src;
};

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

