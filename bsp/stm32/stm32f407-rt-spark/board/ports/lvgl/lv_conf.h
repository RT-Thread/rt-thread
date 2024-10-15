/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-18     Meco Man      First version
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <rtconfig.h>

#define LV_COLOR_DEPTH          16
#define MY_DISP_HOR_RES          240
#define MY_DISP_VER_RES          240

/* music player demo */
#ifdef PKG_USING_LV_MUSIC_DEMO
    #define LV_USE_DEMO_MUSIC           1
    #define LV_HOR_RES_MAX              MY_DISP_HOR_RES
    #define LV_VER_RES_MAX              MY_DISP_VER_RES
    #define LV_USE_DEMO_RTT_MUSIC       1
    #define LV_DEMO_RTT_MUSIC_AUTO_PLAY 1
    #define LV_FONT_MONTSERRAT_12       1
    #define LV_FONT_MONTSERRAT_16       1
    #define LV_COLOR_SCREEN_TRANSP      1
#endif

#define LV_USE_SYSMON               1
#define LV_USE_PERF_MONITOR         1
#define LV_USE_DEMO_WIDGETS         1
#define LV_FONT_MONTSERRAT_20       1
#define LV_FONT_MONTSERRAT_24       1
#define LV_FONT_MONTSERRAT_26       1
#define LV_USE_DEMO_BENCHMARK       1

#endif
