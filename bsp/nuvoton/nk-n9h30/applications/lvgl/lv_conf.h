/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-18     Meco Man      First version
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include "rtconfig.h"

#define LV_VERSION_EQUAL(x,y,z) (x == LVGL_VERSION_MAJOR && y==LVGL_VERSION_MINOR  && z==LVGL_VERSION_PATCH )

//#define LV_USE_GPU_N9H30_GE2D   1

#define LV_COLOR_DEPTH                  BSP_LCD_BPP
#define LV_HOR_RES_MAX                  BSP_LCD_WIDTH
#define LV_VER_RES_MAX                  BSP_LCD_HEIGHT

#define LV_FONT_MONTSERRAT_12           1
#define LV_FONT_MONTSERRAT_16           1
#define LV_USE_PERF_MONITOR             1

#if LV_VERSION_EQUAL(8, 1, 0)
#define LV_USE_DEMO_RTT_MUSIC           1
#define LV_DEMO_RTT_MUSIC_AUTO_PLAY     1
#else
#define LV_USE_DEMO_MUSIC           1
#define LV_DEMO_MUSIC_AUTO_PLAY     1
#endif

//#define LV_DISP_DEF_REFR_PERIOD         16

//#define CONFIG_LV_LOG_LEVEL LV_LOG_LEVEL_TRACE
#endif
