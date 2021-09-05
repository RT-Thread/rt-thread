/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-25 17:19:03
 * @Description:  This files is for debug functions
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FT_DEBUG_H
#define FT_DEBUG_H

#include "ft_printf.h"

typedef enum
{
    FT_LOG_NONE,   /*!< No log output */
    FT_LOG_ERROR,  /*!< Critical errors, software module can not recover on its own */
    FT_LOG_WARN,   /*!< Error conditions from which recovery measures have been taken */
    FT_LOG_INFO,   /*!< Information messages which describe normal flow of events */
    FT_LOG_DEBUG,  /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    FT_LOG_VERBOSE /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
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
#define LOG_COLOR_D
#define LOG_COLOR_V

#ifndef LOG_LOCAL_LEVEL
#define LOG_LOCAL_LEVEL FT_LOG_VERBOSE
#endif

#define LOG_FORMAT(letter, format) LOG_COLOR_##letter " %s: " format LOG_RESET_COLOR "\r\n"

#define PORT_KPRINTF Ft_printf

#define LOG_EARLY_IMPL(tag, format, log_level, log_tag_letter, ...)           \
    do                                                                        \
    {                                                                         \
        if (LOG_LOCAL_LEVEL < log_level)                                      \
            break;                                                            \
        PORT_KPRINTF(LOG_FORMAT(log_tag_letter, format), tag, ##__VA_ARGS__); \
    } while (0)

#define EARLY_LOGE(tag, format, ...) LOG_EARLY_IMPL(tag, format, FT_LOG_ERROR, E, ##__VA_ARGS__)
#define EARLY_LOGI(tag, format, ...) LOG_EARLY_IMPL(tag, format, FT_LOG_INFO, I, ##__VA_ARGS__)
#define EARLY_LOGD(tag, format, ...) LOG_EARLY_IMPL(tag, format, FT_LOG_DEBUG, D, ##__VA_ARGS__)
#define EARLY_LOGW(tag, format, ...) LOG_EARLY_IMPL(tag, format, FT_LOG_WARN, W, ##__VA_ARGS__)
#define EARLY_LOGV(tag, format, ...) LOG_EARLY_IMPL(tag, format, FT_LOG_VERBOSE, W, ##__VA_ARGS__)

#define FT_DEBUG_PRINT_I(TAG, format, ...) EARLY_LOGI(TAG, format, ##__VA_ARGS__)
#define FT_DEBUG_PRINT_E(TAG, format, ...) EARLY_LOGE(TAG, format, ##__VA_ARGS__)
#define FT_DEBUG_PRINT_D(TAG, format, ...) EARLY_LOGD(TAG, format, ##__VA_ARGS__)
#define FT_DEBUG_PRINT_W(TAG, format, ...) EARLY_LOGW(TAG, format, ##__VA_ARGS__)
#define FT_DEBUG_PRINT_V(TAG, format, ...) EARLY_LOGV(TAG, format, ##__VA_ARGS__)

#define FT_RAW_PRINTF(format, ...) PORT_KPRINTF(format, ##__VA_ARGS__)

void Ft_DumpHexWord(const u32 *ptr, ft_base_t buflen);
void Ft_DumpHexByte(const u8 *ptr, ft_base_t buflen);
#endif // !
