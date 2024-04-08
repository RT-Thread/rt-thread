/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-01     lik          first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include "board.h"

#define GET_PIN(GPIOx,PIN) (rt_uint8_t)__SWM_GET_PIN_##GPIOx(PIN)

#define __SWM_GET_PIN_A(PIN)  (PIN)
#define __SWM_GET_PIN_B(PIN)  (16 + PIN)
#define __SWM_GET_PIN_C(PIN)  (32 + PIN)
#define __SWM_GET_PIN_D(PIN)  (48 + PIN)
#define __SWM_GET_PIN_E(PIN)  (64 + PIN)
#define __SWM_GET_PIN_M(PIN)  (80 + PIN)
#define __SWM_GET_PIN_N(PIN)  (96 + PIN)

int swm_pin_init(void);

#endif /* __DRV_GPIO_H__ */
