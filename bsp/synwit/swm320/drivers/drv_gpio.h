/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
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

#define GET_PIN(GPIOx,PIN) (rt_uint8_t)__SWM_GET_PIN_##GPIOx(PIN)

#define __SWM_GET_PIN_A(PIN)  (PIN)
#define __SWM_GET_PIN_B(PIN)  (13 + PIN)
#define __SWM_GET_PIN_C(PIN)  (26 + PIN)
#define __SWM_GET_PIN_M(PIN)  (34 + PIN)
#define __SWM_GET_PIN_N(PIN)  (56 + PIN)
#define __SWM_GET_PIN_P(PIN)  (76 + PIN)

int swm_pin_init(void);

#endif /* __DRV_GPIO_H__ */
