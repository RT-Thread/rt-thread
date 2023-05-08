/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-02-22     Rbb666        First version
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <rtconfig.h>

#define LV_USE_PERF_MONITOR     1
#define LV_COLOR_DEPTH          16

#ifdef PKG_USING_ILI9341
    #define LV_HOR_RES_MAX          240
    #define LV_VER_RES_MAX          320
    #define LV_COLOR_16_SWAP        1
    #define LV_DPI_DEF              99
#endif

#ifdef PKG_USING_LV_MUSIC_DEMO
/* music player demo */
#define LV_USE_DEMO_RTT_MUSIC       1
#define LV_DEMO_RTT_MUSIC_AUTO_PLAY 1
#define LV_FONT_MONTSERRAT_12       1
#define LV_FONT_MONTSERRAT_16       1
#define LV_COLOR_SCREEN_TRANSP      0
#endif /* PKG_USING_LV_MUSIC_DEMO */

#endif
