/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-21     fanwenl      first version
 */

#ifndef __PIN_MAP_H__
#define __PIN_MAP_H__

#include <rtthread.h>

#define WM_PIN_DEFAULT (-1)

rt_int16_t wm_get_pin(rt_base_t pin_index);

#endif
