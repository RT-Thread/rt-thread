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

#define LCD_W 480
#define LCD_H 320

#define LV_COLOR_16_SWAP    0
#define LV_COLOR_DEPTH      32
#define LV_USE_PERF_MONITOR 1

#define LV_HOR_RES_MAX          LCD_W
#define LV_VER_RES_MAX          LCD_H

#define LV_USE_DEMO_RTT_MUSIC       1
#define LV_DEMO_RTT_MUSIC_AUTO_PLAY 1

#define LV_FONT_MONTSERRAT_12       1
#define LV_FONT_MONTSERRAT_16       1

#endif
