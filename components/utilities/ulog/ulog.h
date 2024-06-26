/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-25     armink       the first version
 */

#ifndef _ULOG_H_
#define _ULOG_H_

#include <rtthread.h>
#include "ulog_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ulog init and deint
 */
int ulog_init(void);
int ulog_async_init(void);
void ulog_output_lock_enabled(rt_bool_t enabled);
void ulog_deinit(void);

/*
 * output different level log by LOG_X API
 *
 * NOTE: The `LOG_TAG` and `LOG_LVL` must be defined before including the <ulog.h> when you want to use LOG_X API.
 *
 * #define LOG_TAG              "example"
 * #define LOG_LVL              LOG_LVL_DBG
 * #include <ulog.h>
 *
 * Then you can using LOG_X API to output log
 *
 * LOG_D("this is a debug log!");
 * LOG_E("this is a error log!");
 */
#define LOG_E(...)                      ulog_e(LOG_TAG, __VA_ARGS__)
#define LOG_W(...)                      ulog_w(LOG_TAG, __VA_ARGS__)
#define LOG_I(...)                      ulog_i(LOG_TAG, __VA_ARGS__)
#define LOG_D(...)                      ulog_d(LOG_TAG, __VA_ARGS__)
#define LOG_RAW(...)                    ulog_raw(__VA_ARGS__)
#define LOG_HEX(name, width, buf, size) ulog_hex(name, width, buf, size)

/*
 * backend register and unregister
 */
rt_err_t ulog_backend_register(ulog_backend_t backend, const char *name, rt_bool_t support_color);
rt_err_t ulog_backend_unregister(ulog_backend_t backend);
rt_err_t ulog_backend_set_filter(ulog_backend_t backend, ulog_backend_filter_t filter);
ulog_backend_t ulog_backend_find(const char *name);

#ifdef ULOG_USING_FILTER
/*
 * log filter setting
 */
int ulog_tag_lvl_filter_set(const char *tag, rt_uint32_t level);
rt_uint32_t ulog_tag_lvl_filter_get(const char *tag);
rt_slist_t *ulog_tag_lvl_list_get(void);
void ulog_global_filter_lvl_set(rt_uint32_t level);
rt_uint32_t ulog_global_filter_lvl_get(void);
void ulog_global_filter_tag_set(const char *tag);
const char *ulog_global_filter_tag_get(void);
void ulog_global_filter_kw_set(const char *keyword);
const char *ulog_global_filter_kw_get(void);
#endif /* ULOG_USING_FILTER */

/*
 * flush all backends's log
 */
void ulog_flush(void);

#ifdef ULOG_USING_ASYNC_OUTPUT
/*
 * asynchronous output API
 */
void ulog_async_output(void);
void ulog_async_output_enabled(rt_bool_t enabled);
rt_err_t ulog_async_waiting_log(rt_int32_t time);
#endif

/*
 * dump the hex format data to log
 */
void ulog_hexdump(const char *tag, rt_size_t width, const rt_uint8_t *buf, rt_size_t size, ...);

/*
 * Another log output API. This API is more difficult to use than LOG_X API.
 */
void ulog_voutput(rt_uint32_t level, const char *tag, rt_bool_t newline, const rt_uint8_t *hex_buf,
     rt_size_t hex_size, rt_size_t hex_width, rt_base_t hex_addr, const char *format, va_list args);
void ulog_output(rt_uint32_t level, const char *tag, rt_bool_t newline, const char *format, ...);
void ulog_raw(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* _ULOG_H_ */
