/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __UTILS_LOG_H__
#define __UTILS_LOG_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// #include <FreeRTOS.h>
// #include <task.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __utils_printf              bl_printk

/* cc */
/* define compiler specific symbols */
#if defined (__ICCARM__)
#define BL_PACK_STRUCT_BEGIN
#define BL_PACK_STRUCT_STRUCT
#define BL_PACK_STRUCT_END
#define BL_PACK_STRUCT_FIELD(x) x
#define BL_PACK_STRUCT_USE_INCLUDES
#elif defined (__CC_ARM)
#define BL_PACK_STRUCT_BEGIN __packed
#define BL_PACK_STRUCT_STRUCT
#define BL_PACK_STRUCT_END
#define BL_PACK_STRUCT_FIELD(x) x
#elif defined (__GNUC__)
#define BL_PACK_STRUCT_BEGIN    //#pragma pack(push, 1)
#define BL_PACK_STRUCT_STRUCT //__attribute__ ((__packed__))
#define BL_PACK_STRUCT_END      //#pragma pack(pop)
#define BL_PACK_STRUCT_FIELD(x)
#elif defined (__TASKING__)
#define BL_PACK_STRUCT_BEGIN
#define BL_PACK_STRUCT_STRUCT
#define BL_PACK_STRUCT_END
#define BL_PACK_STRUCT_FIELD(x) x
#endif

#if 0
#define BL_ASSERT(condition)    \
    do { \
        if (!(condition)) { \
            log_assert("ASSERT: %s:%d\r\n", __FILENAME__, __LINE__); \
            while (1) { \
                /*deap loop now*/ \
            } \
        } \
    } while (0)
#endif
#define BL_ASSERT(condition)

#define LOG_USE_COLOR  (0)
typedef enum LOG_BUF_OUT_DATA_TYPE {
    LOG_BUF_OUT_DATA_TYPE_HEX,
    LOG_BUF_OUT_DATA_TYPE_INT8,
    LOG_BUF_OUT_DATA_TYPE_UNT8,
} LOG_BUF_OUT_DATA_TYPE_T;
//#define LOG_USE_LINE_FEED
#define LOG_LOCK_LOCK    /* reserved, must diffrent with buf lock */
#define LOG_LOCK_UNLOCK  /* reserved, must diffrent with buf lock */
//#define SHORT_FILE __FILENAME__
#define SHORT_FILE __FILE__

#ifdef LOG_USE_LINE_FEED
#define custom_log(N, M, ...) do {  LOG_LOCK_LOCK;\
                                    __utils_printf("[%10u][%s: %s:%4d] " M "\r\n",\
                                    (xPortIsInsideInterrupt())?(xTaskGetTickCountFromISR()):(xTaskGetTickCount()),\
                                    N, SHORT_FILE, __LINE__,\
                                    ##__VA_ARGS__);\
                                    LOG_LOCK_UNLOCK;\
                                    } while(0==1)
#define custom_buf_pri(file, line, N, M, ...) do {  LOG_LOCK_LOCK;\
                                    __utils_printf("[%10u][%s: %s:%4d] " M, "\r\n",\
                                    (xPortIsInsideInterrupt())?(xTaskGetTickCountFromISR()):(xTaskGetTickCount()),\
                                    N, file, line,\
                                    ##__VA_ARGS__);\
                                    LOG_LOCK_UNLOCK;\
                                    } while(0==1)
#else
#define custom_log(N, M, ...) do {  LOG_LOCK_LOCK;\
                                    __utils_printf("[%10u][%s: %s:%4d] " M,\
                                    (xPortIsInsideInterrupt())?(xTaskGetTickCountFromISR()):(xTaskGetTickCount()),\
                                    N, SHORT_FILE, __LINE__,\
                                    ##__VA_ARGS__);\
                                    LOG_LOCK_UNLOCK;\
                                    } while(0==1)
#define custom_buf_pri(file, line, N, M, ...) do {  LOG_LOCK_LOCK;\
                                    __utils_printf("[%10u][%s: %s:%4d] " M,\
                                    (xPortIsInsideInterrupt())?(xTaskGetTickCountFromISR()):(xTaskGetTickCount()),\
                                    N, file, line,\
                                    ##__VA_ARGS__);\
                                    LOG_LOCK_UNLOCK;\
                                    } while(0==1)
#endif

#if LOG_USE_COLOR
#define log_buf_pri(file, line, M, ...)   custom_buf_pri(file, line, "\x1b[36mBUF\x1b[0m", M, ##__VA_ARGS__)
#else
#define log_buf_pri(file, line, M, ...)   custom_buf_pri(file, line, "BUF", M, ##__VA_ARGS__)
#endif

#if LOG_USE_COLOR
#define log_trace(M, ...)   custom_log("\x1b[94mTRACE \x1b[0m", M, ##__VA_ARGS__)
#define log_debug(M, ...)   custom_log("\x1b[36mDEBUG \x1b[0m", M, ##__VA_ARGS__)
#define log_info(M, ...)    custom_log("\x1b[32mINFO  \x1b[0m", M, ##__VA_ARGS__)
#define log_warn(M, ...)    custom_log("\x1b[33mWARN  \x1b[0m", M, ##__VA_ARGS__)
#define log_error(M, ...)   custom_log("\x1b[31mERROR \x1b[0m", M, ##__VA_ARGS__)
#define log_assert(M, ...)  custom_log("\x1b[35mASSERT\x1b[0m", M, ##__VA_ARGS__)
#else
#define log_trace(M, ...)   custom_log("TRACE ", M, ##__VA_ARGS__)
#define log_debug(M, ...)   custom_log("DEBUG ", M, ##__VA_ARGS__)
#define log_info(M, ...)    custom_log("INFO  ", M, ##__VA_ARGS__)
#define log_warn(M, ...)    custom_log("WARN  ", M, ##__VA_ARGS__)
#define log_error(M, ...)   custom_log("ERROR ", M, ##__VA_ARGS__)
#define log_assert(M, ...)  custom_log("ASSERT", M, ##__VA_ARGS__)
#endif
#define log_buf(pbuf, len)  log_buf_out(SHORT_FILE, __LINE__, pbuf, len, LOG_BUF_OUT_DATA_TYPE_HEX)
#define log_buf_int8(pbuf, len)  log_buf_out(SHORT_FILE, __LINE__, pbuf, len, LOG_BUF_OUT_DATA_TYPE_INT8)
#define log_buf_unt8(pbuf, len)  log_buf_out(SHORT_FILE, __LINE__, pbuf, len, LOG_BUF_OUT_DATA_TYPE_UNT8)
#define log_compile_time()  do {\
                            log_info("compile date = %s\r\n", __DATE__);\
                            log_info("compile time = %s\r\n", __TIME__);\
                            } while (0 == 1);

int log_buf_out(const char *file, int line, const void *inbuf, int len, LOG_BUF_OUT_DATA_TYPE_T type);

void bl_printk(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif

