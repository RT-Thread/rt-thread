/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fdebug.h
 * Date: 2021-04-07 09:53:07
 * LastEditTime: 2022-02-17 18:04:58
 * Description:  This file is for showing debug api.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  zhugengyu  2022/10/27   rename file name
 */

#ifndef FDEBUG_H
#define FDEBUG_H

#include <stdio.h>
#include "sdkconfig.h"
#include "ftypes.h"
#include "fprintk.h"
#ifdef CONFIG_USE_AMP
#include "fsmp.h"
#endif

#if defined(CONFIG_USE_AMP)
#include "fcpu_info.h"
#endif


#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    FT_LOG_NONE,   /* No log output */
    FT_LOG_ERROR,  /* Critical errors, software module can not recover on its own */
    FT_LOG_WARN,   /* Error conditions from which recovery measures have been taken */
    FT_LOG_INFO,   /* Information messages which describe normal flow of events */
    FT_LOG_DEBUG,  /* Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    FT_LOG_VERBOSE /* Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
} ft_log_level_t;

#define LOG_COLOR_BLACK "30"
#define LOG_COLOR_RED "31"
#define LOG_COLOR_GREEN "32"
#define LOG_COLOR_BROWN "33"
#define LOG_COLOR_BLUE "34"
#define LOG_COLOR_PURPLE "35"
#define LOG_COLOR_CYAN "36"
#define LOG_COLOR(COLOR) "\033[0;" COLOR "m"
#define LOG_BOLD(COLOR) "\033[1;" COLOR "m"
#define LOG_RESET_COLOR "\033[0m"
#define LOG_COLOR_E LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_W LOG_COLOR(LOG_COLOR_BROWN)
#define LOG_COLOR_I LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_D LOG_COLOR(LOG_COLOR_CYAN)
#define LOG_COLOR_V LOG_COLOR(LOG_COLOR_PURPLE)

/* select debug log level */
#ifdef CONFIG_LOG_VERBOS
    #define LOG_LOCAL_LEVEL FT_LOG_VERBOSE
#endif

#ifdef CONFIG_LOG_ERROR
    #define LOG_LOCAL_LEVEL FT_LOG_ERROR
#endif

#ifdef CONFIG_LOG_WARN
    #define LOG_LOCAL_LEVEL FT_LOG_WARN
#endif

#ifdef CONFIG_LOG_INFO
    #define LOG_LOCAL_LEVEL FT_LOG_INFO
#endif

#ifdef CONFIG_LOG_DEBUG
    #define LOG_LOCAL_LEVEL FT_LOG_DEBUG
#endif

#define LOG_FORMAT(letter, format) LOG_COLOR_##letter " %s: " format LOG_RESET_COLOR "\r\n"

#define PORT_KPRINTF f_printk

#if defined(CONFIG_LOG_DISPALY_CORE_NUM)    
    #define DISPALY_CORE_NUM() \
        do {u32 cpu_id;                                                           \
        GetCpuId(&cpu_id);                                                    \
        PORT_KPRINTF("cpu%d:", cpu_id);                                      } while(0)
#else
#define DISPALY_CORE_NUM()
#endif


#ifdef CONFIG_USE_AMP
#define LOG_SPIN_LOCK() SpinLock();
#define LOG_SPIN_UNLOCK() SpinUnlock() ;
#else
#define LOG_SPIN_LOCK()
#define LOG_SPIN_UNLOCK()
#endif


#ifndef CONFIG_LOG_EXTRA_INFO
#define LOG_EARLY_IMPL(tag, format, log_level, log_tag_letter, ...)           \
    do                                                                        \
    {                                                                         \
        if (LOG_LOCAL_LEVEL < log_level)                                      \
            break;                                                            \
        LOG_SPIN_LOCK();                                                      \
        DISPALY_CORE_NUM();                                                   \
        PORT_KPRINTF(LOG_FORMAT(log_tag_letter, format), tag, ##__VA_ARGS__); \
        LOG_SPIN_UNLOCK();                                                    \
    } while (0)
#else
#include <string.h>
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
/* print debug information with source file name and source code line num. */
#define LOG_EARLY_IMPL(tag, format, log_level, log_tag_letter, ...)           \
    do                                                                        \
    {                                                                         \
        if (LOG_LOCAL_LEVEL < log_level)                                      \
            break;                                                            \
        DISPALY_CORE_NUM()  \
        PORT_KPRINTF(LOG_FORMAT(log_tag_letter, format" @%s:%d"), tag, ##__VA_ARGS__, __FILENAME__, __LINE__); \
    } while (0)
#endif

#define EARLY_LOGE(tag, format, ...) LOG_EARLY_IMPL(tag, format, FT_LOG_ERROR, E, ##__VA_ARGS__)
#define EARLY_LOGI(tag, format, ...) LOG_EARLY_IMPL(tag, format, FT_LOG_INFO, I, ##__VA_ARGS__)
#define EARLY_LOGD(tag, format, ...) LOG_EARLY_IMPL(tag, format, FT_LOG_DEBUG, D, ##__VA_ARGS__)
#define EARLY_LOGW(tag, format, ...) LOG_EARLY_IMPL(tag, format, FT_LOG_WARN, W, ##__VA_ARGS__)
#define EARLY_LOGV(tag, format, ...) LOG_EARLY_IMPL(tag, format, FT_LOG_VERBOSE, W, ##__VA_ARGS__)

/* do not compile log if define CONFIG_LOG_NONE */
#ifndef CONFIG_LOG_NONE
    #define FT_DEBUG_PRINT_I(TAG, format, ...) EARLY_LOGI(TAG, format, ##__VA_ARGS__)
    #define FT_DEBUG_PRINT_E(TAG, format, ...) EARLY_LOGE(TAG, format, ##__VA_ARGS__)
    #define FT_DEBUG_PRINT_D(TAG, format, ...) EARLY_LOGD(TAG, format, ##__VA_ARGS__)
    #define FT_DEBUG_PRINT_W(TAG, format, ...) EARLY_LOGW(TAG, format, ##__VA_ARGS__)
    #define FT_DEBUG_PRINT_V(TAG, format, ...) EARLY_LOGV(TAG, format, ##__VA_ARGS__)
#else
    #define FT_DEBUG_PRINT_I(TAG, format, ...)
    #define FT_DEBUG_PRINT_E(TAG, format, ...)
    #define FT_DEBUG_PRINT_D(TAG, format, ...)
    #define FT_DEBUG_PRINT_W(TAG, format, ...)
    #define FT_DEBUG_PRINT_V(TAG, format, ...)
#endif

#define FT_RAW_PRINTF(format, ...) PORT_KPRINTF(format, ##__VA_ARGS__)

void FtDumpHexWord(const u32 *ptr, u32 buflen);
void FtDumpHexByte(const u8 *ptr, u32 buflen);

#ifdef __cplusplus
}
#endif

#endif // !
