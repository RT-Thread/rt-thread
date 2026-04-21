/**************************************************************************//**
 * @file     lv_conf.h
 * @brief    lvgl configuration
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef LV_CONF_H
#define LV_CONF_H

#include "rtconfig.h"

#define LV_COLOR_DEPTH                  BSP_LCD_BPP
#define LV_HOR_RES_MAX                  BSP_LCD_WIDTH
#define LV_VER_RES_MAX                  BSP_LCD_HEIGHT

#define LV_FONT_MONTSERRAT_12           1
#define LV_FONT_MONTSERRAT_16           1

#define CONFIG_LV_MEM_SIZE              (64*1024)
#define CONFIG_LV_CACHE_DEF_SIZE        (64*1024)

/* Please comment LV_USE_DEMO_MUSIC declaration before un-comment below */
//#define LV_USE_DEMO_WIDGETS             1

/* For V8 definitions */
//#define LV_USE_PERF_MONITOR             1

/* For V9 definitions */
#define LV_USE_SYSMON                   1
#define LV_USE_PERF_MONITOR             1
#define LV_USE_LOG                      0

#if 1

    //LV_CONF_MINIMAL

    #undef LV_USE_DEMO_WIDGETS
    #undef LV_USE_SYSMON
    #undef LV_USE_PERF_MONITOR
    #undef LV_USE_LOG

    #define LV_USE_THEME_DEFAULT 1
    #define LV_WIDGETS_HAS_DEFAULT_VALUE     0
    #define LV_USE_ANIMIMG                   0
    #define LV_USE_ARC                       1
    #define LV_USE_BAR                       1
    #define LV_USE_BUTTON                    1
    #define LV_USE_BUTTONMATRIX              1
    #define LV_USE_CALENDAR                  0
    #define LV_USE_CALENDAR_HEADER_ARROW     0
    #define LV_USE_CALENDAR_HEADER_DROPDOWN  0
    #define LV_USE_CALENDAR_CHINESE          0
    #define LV_USE_CANVAS                    0
    #define LV_USE_CHART                     0
    #define LV_USE_CHECKBOX                  0
    #define LV_USE_DROPDOWN                  0
    #define LV_USE_IMAGE                     1
    #define LV_USE_IMAGEBUTTON               0
    #define LV_USE_KEYBOARD                  0
    #define LV_USE_LABEL                     1
    #define LV_LABEL_TEXT_SELECTION          0
    #define LV_LABEL_LONG_TXT_HINT           0
    #define LV_LABEL_WAIT_CHAR_COUNT         0
    #define LV_USE_LED                       1
    #define LV_USE_LINE                      1
    #define LV_USE_LIST                      0
    #define LV_USE_MENU                      0
    #define LV_USE_MSGBOX                    0
    #define LV_USE_ROLLER                    0
    #define LV_USE_SCALE                     1
    #define LV_USE_SLIDER                    1
    #define LV_USE_SPAN                      0
    #define LV_USE_SPINBOX                   0
    #define LV_USE_SPINNER                   0
    #define LV_USE_SWITCH                    1
    #define LV_USE_TEXTAREA                  0
    #define LV_USE_TABLE                     0
    #define LV_USE_TABVIEW                   0
    #define LV_USE_TILEVIEW                  0
    #define LV_USE_WIN                       0
    #define LV_DRAW_SW_SUPPORT_RGB565        1
    #define LV_DRAW_SW_SUPPORT_RGB565A8      0
    #define LV_DRAW_SW_SUPPORT_RGB888          1
    #define LV_DRAW_SW_SUPPORT_XRGB8888      0
    #define LV_DRAW_SW_SUPPORT_ARGB8888      1
    #define LV_DRAW_SW_SUPPORT_L8            0
    #define LV_DRAW_SW_SUPPORT_AL88          0
    #define LV_DRAW_SW_SUPPORT_A8            0
    #define LV_DRAW_SW_SUPPORT_I1            0
    #define LV_DRAW_SW_COMPLEX               1

#endif

#if LV_USE_LOG == 1
    #define LV_LOG_LEVEL       LV_LOG_LEVEL_TRACE
    //#define LV_LOG_LEVEL     LV_LOG_LEVEL_INFO
    //#define LV_LOG_LEVEL     LV_LOG_LEVEL_WARN
    //#define LV_LOG_LEVEL     LV_LOG_LEVEL_ERROR
    //#define LV_LOG_LEVEL     LV_LOG_LEVEL_USER
    //#define LV_LOG_LEVEL     LV_LOG_LEVEL_NONE
#endif

#endif /* LV_CONF_H */
