/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_LOG_H
#define USB_LOG_H

#include <stdio.h>

/* DEBUG level */
#define USB_DBG_ERROR   0
#define USB_DBG_WARNING 1
#define USB_DBG_INFO    2
#define USB_DBG_LOG     3

#ifndef USB_DBG_TAG
#define USB_DBG_TAG "USB"
#endif
/*
 * The color for terminal (foreground)
 * BLACK    30
 * RED      31
 * GREEN    32
 * YELLOW   33
 * BLUE     34
 * PURPLE   35
 * CYAN     36
 * WHITE    37
 */

#ifdef  CONFIG_USB_PRINTF_COLOR_ENABLE
#define _USB_DBG_COLOR(n) CONFIG_USB_PRINTF("\033[" #n "m")
#define _USB_DBG_LOG_HDR(lvl_name, color_n) \
    CONFIG_USB_PRINTF("\033[" #color_n "m[" lvl_name "/" USB_DBG_TAG "] ")
#define _USB_DBG_LOG_X_END \
    CONFIG_USB_PRINTF("\033[0m")
#else
#define _USB_DBG_COLOR(n)
#define _USB_DBG_LOG_HDR(lvl_name, color_n) \
    CONFIG_USB_PRINTF("[" lvl_name "/" USB_DBG_TAG "] ")
#define _USB_DBG_LOG_X_END
#endif

#define usb_dbg_log_line(lvl, color_n, fmt, ...) \
    do {                                         \
        _USB_DBG_LOG_HDR(lvl, color_n);          \
        CONFIG_USB_PRINTF(fmt, ##__VA_ARGS__);              \
        _USB_DBG_LOG_X_END;                      \
    } while (0)

#if (CONFIG_USB_DBG_LEVEL >= USB_DBG_LOG)
#define USB_LOG_DBG(fmt, ...) usb_dbg_log_line("D", 0, fmt, ##__VA_ARGS__)
#else
#define USB_LOG_DBG(...)  {}
#endif

#if (CONFIG_USB_DBG_LEVEL >= USB_DBG_INFO)
#define USB_LOG_INFO(fmt, ...) usb_dbg_log_line("I", 32, fmt, ##__VA_ARGS__)
#else
#define USB_LOG_INFO(...) {}
#endif

#if (CONFIG_USB_DBG_LEVEL >= USB_DBG_WARNING)
#define USB_LOG_WRN(fmt, ...) usb_dbg_log_line("W", 33, fmt, ##__VA_ARGS__)
#else
#define USB_LOG_WRN(...) {}
#endif

#if (CONFIG_USB_DBG_LEVEL >= USB_DBG_ERROR)
#define USB_LOG_ERR(fmt, ...) usb_dbg_log_line("E", 31, fmt, ##__VA_ARGS__)
#else
#define USB_LOG_ERR(...) {}
#endif

#define USB_LOG_RAW(...) CONFIG_USB_PRINTF(__VA_ARGS__)

void usb_assert(const char *filename, int linenum);
#define USB_ASSERT(f)                       \
    do {                                    \
        if (!(f))                           \
            usb_assert(__FILE__, __LINE__); \
    } while (0)

#endif /* USB_LOG_H */
