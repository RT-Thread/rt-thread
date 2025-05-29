 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     syslog.h
 * @brief    Defines syslog APIs and usage
 * @version  V1.1
 * @date     14. February 2019
 * @usage    Add 3 lines codes below at head of source code file
 *           // 0: Err; 1: Err&Warn; 2: Err&Warn&Info; 3: Err&Warn&Info&Debug
 *           #define LOG_LEVEL 3
 *           #include <syslog.h>
 ******************************************************************************/
#include <stdio.h>

#ifndef _SYSLOG_H_
#define _SYSLOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LOG_LEVEL
#if (LOG_LEVEL >= 3) && \
    (defined CONFIG_SYSLOG_LEVEL_DEBUG)
#define LOG_ENABLE_D
#endif

#if (LOG_LEVEL >= 2) && \
    (defined CONFIG_SYSLOG_LEVEL_DEBUG || \
     defined CONFIG_SYSLOG_LEVEL_INFO)
#define LOG_ENABLE_I
#endif

#if (LOG_LEVEL >= 1) && \
    (defined CONFIG_SYSLOG_LEVEL_DEBUG || \
     defined CONFIG_SYSLOG_LEVEL_INFO  || \
     defined CONFIG_SYSLOG_LEVEL_WARN)
#define LOG_ENABLE_W
#endif

#if (LOG_LEVEL >= 0) && \
    (defined CONFIG_SYSLOG_LEVEL_DEBUG || \
     defined CONFIG_SYSLOG_LEVEL_INFO  || \
     defined CONFIG_SYSLOG_LEVEL_WARN  || \
     defined CONFIG_SYSLOG_LEVEL_ERROR)
#define LOG_ENABLE_E
#endif
#endif  /* #ifdef LOG_LEVEL */

/* [LogLevel:FileName:Function:Line] */
extern const char *PFORMAT_D;
extern const char *PFORMAT_I;
extern const char *PFORMAT_W;
extern const char *PFORMAT_E;

#define LOG_E_BASE_ARGS __FUNCTION__, __LINE__
#define LOG_W_BASE_ARGS __FUNCTION__, __LINE__
#define LOG_I_BASE_ARGS __FUNCTION__, __LINE__
#define LOG_D_BASE_ARGS __FUNCTION__, __LINE__

/* Log in freely format without prefix */
#define LOG_F(fmt, args...) printf(fmt,##args)

/* Log debug */
#ifdef LOG_ENABLE_D
#define LOG_D(fmt, args...) \
    do {printf(PFORMAT_D,LOG_D_BASE_ARGS); printf(fmt,##args);} while(0)
#else
#define LOG_D(fmt, args...)
#endif

/* Log information */
#ifdef LOG_ENABLE_I
#define LOG_I(fmt, args...) \
    do {printf(PFORMAT_I ,LOG_I_BASE_ARGS); printf(fmt,##args);} while(0)
#else
#define LOG_I(fmt, args...)
#endif

/* Log warning */
#ifdef LOG_ENABLE_W
#define LOG_W(fmt, args...) \
    do {printf(PFORMAT_W,LOG_W_BASE_ARGS); printf(fmt,##args);} while(0)
#else
#define LOG_W(fmt, args...)
#endif

/* Log error */
#ifdef LOG_ENABLE_E
#define LOG_E(fmt, args...) \
    do {printf(PFORMAT_E,LOG_E_BASE_ARGS); printf(fmt,##args);} while(0)
#else
#define LOG_E(fmt, args...)
#endif

#define ENTER()         LOG_D("Enter\n")
#define EXIT_VOID()     do { LOG_D("Exit\n"); return;} while(0)
#define EXIT_INT(val)   do { LOG_D("Exit, return val=%d\n", (int)val); return val;} while(0)
#define EXIT_PTR(ptr)   do { LOG_D("Exit, return ptr=%p\n", (void*)ptr); return ptr;} while(0)

#ifdef __cplusplus
}
#endif

#endif /* _SYSLOG_H_ */
