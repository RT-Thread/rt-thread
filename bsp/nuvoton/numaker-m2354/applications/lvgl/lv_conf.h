/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-2-17      Wayne         First version
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include "rtconfig.h"

#define LV_COLOR_DEPTH                  BSP_LCD_BPP
#define LV_HOR_RES_MAX                  BSP_LCD_WIDTH
#define LV_VER_RES_MAX                  BSP_LCD_HEIGHT

#define LV_FONT_MONTSERRAT_12           1
#define LV_FONT_MONTSERRAT_16           1
#define LV_USE_PERF_MONITOR             1
//#define CONFIG_LV_LOG_LEVEL LV_LOG_LEVEL_TRACE

//#define LV_USE_DEMO_RTT_MUSIC         1
#if LV_USE_DEMO_RTT_MUSIC
    #define LV_COLOR_SCREEN_TRANSP        1
    #define LV_DEMO_RTT_MUSIC_AUTO_PLAY   1

    #define LV_USE_DEMO_MUSIC             1
    #define LV_DEMO_MUSIC_AUTO_PLAY       1
#endif

/* Please comment LV_USE_DEMO_RTT_MUSIC declaration before un-comment below */
#define LV_USE_DEMO_WIDGETS         1
//#define LV_USE_DEMO_BENCHMARK       1

#endif
