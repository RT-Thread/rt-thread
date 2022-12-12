/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-01-28     Rudy Lo       The first version
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <rtconfig.h>
#include "rgb_lcd_port.h"

#define LV_HOR_RES LCD_WIDTH
#define LV_VER_RES LCD_HEIGHT

#define LV_COLOR_DEPTH LCD_BITS_PER_PIXEL

#define LV_COLOR_16_SWAP 0

#define LV_USE_PERF_MONITOR 1

#define LV_USE_DEMO_WIDGETS 1

#define LV_USE_DEMO_BENCHMARK 0
#endif
