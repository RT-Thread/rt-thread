/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-04     RTT          configure LVGL for the MIPI DSI LCD
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#define LV_COLOR_FORMAT_DEFAULT         LV_COLOR_FORMAT_RGB565
#define LV_DISABLE_ASSERT_HANDLER_INCLUDE_WARNING 1
#define LV_USE_GINO_FACTORY_PROFILE     1

#define LV_HOR_RES_MAX                  720
#define LV_VER_RES_MAX                  720

#if defined(BSP_USING_OV7670) && (defined(__GNUC__) || defined(__ARMCC_VERSION))
/* The RT-Thread port selects rt_malloc before loading this file. Its automatic
 * SDRAM fallback is unsuitable for CPU-rendered image scratch buffers. Only
 * CPU-owned LVGL allocations use DTCM; DMA/draw buffers remain in AXI SRAM. */
#undef LV_USE_STDLIB_MALLOC
#define LV_USE_STDLIB_MALLOC            LV_STDLIB_BUILTIN
#define LV_MEM_SIZE                     (256U * 1024U)
#define LV_MEM_ADR                      0
#define LV_ATTRIBUTE_LARGE_RAM_ARRAY    __attribute__((section(".bss.lvgl_heap"), aligned(8)))
#endif

#define LV_USE_SYSMON                   0
#define LV_USE_PERF_MONITOR             0
#define LV_USE_MEM_MONITOR              0

#define LV_USE_THEME_DEFAULT            1
#define LV_USE_THEME_SIMPLE             0
#define LV_USE_THEME_MONO               0

#define LV_USE_FLEX                     0
#define LV_USE_GRID                     0

#define LV_USE_DEMO_BENCHMARK           0
#define LV_USE_DEMO_SMARTWATCH          0
#define LV_USE_DEMO_MUSIC               0

#define LV_USE_FS_STDIO                 0
#define LV_USE_FS_POSIX                 0
#define LV_USE_FS_WIN32                 0
#define LV_USE_FS_FATFS                 0
#define LV_USE_FS_LITTLEFS              0
#define LV_USE_FS_ARDUINO_ESP_LITTLEFS  0
#define LV_USE_FS_ARDUINO_SD            0
#define LV_USE_FS_UEFI                  0
#define LV_USE_FS_FROGFS                0
#define LV_USE_FS_MEMFS                 0

#define LV_USE_BMP                      0
#define LV_USE_LODEPNG                  0
#define LV_USE_LIBPNG                   0
#define LV_USE_TJPGD                    0
#define LV_USE_LIBJPEG_TURBO            0
#define LV_USE_LIBWEBP                  0
#define LV_USE_SVG                      0
#define LV_USE_RLE                      0
#define LV_USE_LZ4                      0
#define LV_USE_GIF                      0
#define LV_USE_QRCODE                   0
#define LV_USE_BARCODE                  0
#define LV_USE_LOTTIE                   0

#define LV_USE_ANIMIMG                  0
#define LV_USE_ARC                      0
#define LV_USE_ARCLABEL                 0
#define LV_USE_BAR                      1
#define LV_USE_BUTTON                   1
#define LV_USE_BUTTONMATRIX             1
#define LV_USE_CALENDAR                 0
#define LV_USE_CANVAS                   0
#define LV_USE_CHART                    0
#define LV_USE_CHECKBOX                 0
#define LV_USE_DROPDOWN                 1
#define LV_USE_IMAGE                    1
#define LV_USE_IMAGEBUTTON              0
#define LV_USE_KEYBOARD                 1
#define LV_USE_LABEL                    1
#define LV_USE_LED                      0
#define LV_USE_LINE                     0
#define LV_USE_LIST                     0
#define LV_USE_MENU                     0
#define LV_USE_MSGBOX                   0
#define LV_USE_ROLLER                   0
#define LV_USE_SCALE                    0
#define LV_USE_SLIDER                   1
#define LV_USE_SPAN                     0
#define LV_USE_SPINBOX                  0
#define LV_USE_SPINNER                  0
#define LV_USE_SWITCH                   1
#define LV_USE_TABLE                    1
#define LV_USE_TABVIEW                  0
#define LV_USE_TEXTAREA                 1
#define LV_USE_TILEVIEW                 0
#define LV_USE_WIN                      0
#define LV_USE_IME_PINYIN               0

#define LV_USE_FILE_EXPLORER            0
#define LV_USE_FRAGMENT                 0
#define LV_USE_TRANSLATION              0
#define LV_USE_FREETYPE                 0
#define LV_USE_TINY_TTF                 0
#define LV_USE_FONT_MANAGER             0
#define LV_USE_IMGFONT                  0

#define LV_FONT_MONTSERRAT_12           0
#define LV_FONT_MONTSERRAT_14           0
#define LV_FONT_MONTSERRAT_16           1
#define LV_FONT_DEFAULT                 &lv_font_montserrat_16

#endif /* LV_CONF_H */
