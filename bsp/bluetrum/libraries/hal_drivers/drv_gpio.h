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

int rt_hw_pin_init(void);

#endif // DRV_GPIO_H__
