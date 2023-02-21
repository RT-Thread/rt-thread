/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-04-12     RT-Thread    the first version
 */

#ifndef __DRV_PIN_H__
#define __DRV_PIN_H__

#include <hal_gpio.h>

/* IO port */
enum gpio_port
{
    GPIO_PORT_RESERVED0 = 0,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_G,
    GPIO_PORT_NUM,
};

/* IO pin */
enum gpio_pin
{
    GPIO_PIN_0 = 0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15,
    GPIO_PIN_16,
    GPIO_PIN_17,
    GPIO_PIN_18,
    GPIO_PIN_19,
    GPIO_PIN_20,
    GPIO_PIN_21,
    GPIO_PIN_22,
    GPIO_PIN_NUM,
};

#define HAL_GPIO(bank,num) GPIO_P##bank##num

#define GET_GPIO_PORT(PIN)       (PIN / 32)
#define GET_GPIO_PIN(PIN)        (PIN % 32)
#define GET_PIN(PORTx, PIN)      (rt_base_t)(32 * PORTx + PIN)

#endif
