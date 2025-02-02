/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <stm32h7xx.h>
#include "drv_common.h"
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t _heap_start[];
extern uint8_t _heap_end[];
#define HEAP_BEGIN      _heap_start
#define HEAP_END        _heap_end

void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif
