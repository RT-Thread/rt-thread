/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-19     greedyhao         first version
 */

#ifndef DRV_GPIO_H__
#define DRV_GPIO_H__

#include "drv_common.h"
#include "board.h"

#define __AB32_PORT(port)   GPIO##port
#define __AB32_GET_PIN_A(PIN)  PIN
#define __AB32_GET_PIN_B(PIN)  8 + PIN
#define __AB32_GET_PIN_E(PIN)  13 + PIN
#define __AB32_GET_PIN_F(PIN)  21 + PIN

#define WAKEUP_INT_ENABLE   16
#define WAKEUP_CRICUIT_0    0  // PA7
#define WAKEUP_CRICUIT_1    1  // PB1
#define WAKEUP_CRICUIT_2    2  // PB2
#define WAKEUP_CRICUIT_3    3  // PB3
#define WAKEUP_CRICUIT_4    4  // PB4
#define WAKEUP_CRICUIT_5    5  // WKO (RTC)
#define WAKEUP_CRICUIT_6    6  // Falling edge for other GPIOs
#define WAKEUP_CRICUIT_7    7  // Rising edge for other GPIOs
#define WAKEUP_EDGE_SELECT_0 16
#define WAKEUP_EDGE_SELECT_1 17
#define WAKEUP_EDGE_SELECT_2 18
#define WAKEUP_EDGE_SELECT_3 19
#define WAKEUP_EDGE_SELECT_4 20
#define WAKEUP_EDGE_SELECT_5 21
#define WAKEUP_EDGE_SELECT_6 22
#define WAKEUP_EDGE_SELECT_7 23

/* structure to store IRQ handler and arguments per pin */
struct ab32_pin_irq
{
    void (*hdr)(void *args);
    void *args;
};

int rt_hw_pin_init(void);

#endif // DRV_GPIO_H__
