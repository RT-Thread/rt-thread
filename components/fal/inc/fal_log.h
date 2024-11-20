/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-18     yekai        move fal log to fal_log.h to avoid TAG conflict
 */

#ifndef _FAL_LOG_H_
#define _FAL_LOG_H_

#include "fal_def.h"

#if FAL_DEBUG

/* debug level log */
#ifdef  log_d
#undef  log_d
#endif
#define log_d(...)                     FAL_PRINTF("[D/FAL] (%s:%d) ", __FUNCTION__, __LINE__);           FAL_PRINTF(__VA_ARGS__);FAL_PRINTF("\n")

#else

#ifdef assert
#undef assert
#endif
#define assert(EXPR)                   ((void)0);

/* debug level log */
#ifdef  log_d
#undef  log_d
#endif
#define log_d(...)
#endif /* FAL_DEBUG */

/* error level log */
#ifdef  log_e
#undef  log_e
#endif
#define log_e(...)                     FAL_PRINTF("\033[31;22m[E/FAL] (%s:%d) ", __FUNCTION__, __LINE__);FAL_PRINTF(__VA_ARGS__);FAL_PRINTF("\033[0m\n")

/* info level log */
#ifdef  log_i
#undef  log_i
#endif
#define log_i(...)                     FAL_PRINTF("\033[32;22m[I/FAL] ");                                FAL_PRINTF(__VA_ARGS__);FAL_PRINTF("\033[0m\n")

#endif