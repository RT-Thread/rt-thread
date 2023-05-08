/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022/03/15     flyingcys    first version
 */

#ifndef BOARD_H__
#define BOARD_H__

#include <rtconfig.h>

#include "bflb_uart.h"
#include "bflb_gpio.h"
#include "bflb_clock.h"
#include "bflb_rtc.h"
#include "bflb_flash.h"
#include "bl616_tzc_sec.h"
#include "bl616_psram.h"
#include "bl616_glb.h"

#define     HW_MTIMER_CLOCK     1000000

extern uint8_t __HeapBase;
extern uint8_t __HeapLimit;

#define RT_HW_HEAP_BEGIN    (void*)&__HeapBase
#define RT_HW_HEAP_END      (void*)&__HeapLimit

void rt_hw_board_init(void);

#endif
