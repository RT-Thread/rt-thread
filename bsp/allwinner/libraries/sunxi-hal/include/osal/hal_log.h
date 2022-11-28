#ifndef SUNXI_HAL_LOG_H
#define SUNXI_HAL_LOG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

//#define CONFIG_KERNEL_FREERTOS
//#define CONFIG_RTTKERNEL
#ifdef CONFIG_KERNEL_FREERTOS

#include <awlog.h>

#define hal_log_err(fmt, ...)           pr_err(fmt"\n", ##__VA_ARGS__)
#define hal_log_warn(fmt, ...)          pr_warn(fmt"\n", ##__VA_ARGS__)
#define hal_log_info(fmt, ...)          pr_info(fmt"\n", ##__VA_ARGS__)
#define hal_log_debug(fmt, ...)         pr_debug(fmt"\n", ##__VA_ARGS__)

#elif defined CONFIG_RTTKERNEL

#include <log.h>

#define hal_log_err(fmt, ...)           pr_err(fmt"\n", ##__VA_ARGS__)
#define hal_log_warn(fmt, ...)          pr_warn(fmt"\n", ##__VA_ARGS__)
#define hal_log_info(fmt, ...)          pr_info(fmt"\n", ##__VA_ARGS__)
#define hal_log_debug(fmt, ...)         pr_debug(fmt"\n", ##__VA_ARGS__)

#else
int printk(const char *fmt, ...);

#define HAL_XPOSTO(x)   "\033[" #x "D\033[" #x "C"

#define HAL_LOG_LAYOUT      "%s%s%s: [%s:%04u]: %s%s"
#define HAL_LOG_BACKEND_CALL(log_lv, log_color, log_format, color_off, ...) \
    printk(HAL_LOG_LAYOUT log_format "%s""\n\r",                            \
           log_color, log_lv, color_off, __func__, __LINE__, HAL_XPOSTO(30),\
           log_color, ##__VA_ARGS__, color_off)

#define HAL_LOG_COLOR(log_lv, log_color, log_format, ...)                   \
    HAL_LOG_BACKEND_CALL(log_lv, log_color, log_format,                     \
                     HAL_LOG_COLOR_OFF, ##__VA_ARGS__)


#define HAL_LOG_COLOR_OFF                 "\033[0m"
#define HAL_LOG_COLOR_RED                 "\033[1;40;31m"
#define HAL_LOG_COLOR_YELLOW              "\033[1;40;33m"
#define HAL_LOG_COLOR_BLUE                "\033[1;40;34m"
#define HAL_LOG_COLOR_PURPLE              "\033[1;40;35m"

#define HAL_LOG_ERROR_PREFIX            "[ERR]"
#define HAL_LOG_WARNING_PREFIX          "[WRN]"
#define HAL_LOG_INFO_PREFIX             "[INF]"
#define HAL_LOG_DEBUG_PREFIX            "[DBG]"

#define hal_log_err(...) \
    do { HAL_LOG_COLOR(HAL_LOG_ERROR_PREFIX, HAL_LOG_COLOR_OFF, ##__VA_ARGS__); } while(0)
#define hal_log_warn(...) \
    do { HAL_LOG_COLOR(HAL_LOG_WARNING_PREFIX, HAL_LOG_COLOR_OFF, ##__VA_ARGS__); } while(0)
#define hal_log_info(...) \
    do { HAL_LOG_COLOR(HAL_LOG_INFO_PREFIX, HAL_LOG_COLOR_OFF, ##__VA_ARGS__); } while(0)
#define hal_log_debug(...) \
    do { HAL_LOG_COLOR(HAL_LOG_DEBUG_PREFIX, HAL_LOG_COLOR_OFF, ##__VA_ARGS__); } while(0)
#endif

#ifdef __cplusplus
}
#endif

#endif
