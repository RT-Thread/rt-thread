/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _ROM_DEBUG_H_
#define _ROM_DEBUG_H_

#include <stdio.h>
#ifndef CONFIG_KERNEL_FREERTOS
#include <log.h>
#endif

#include "sys/sys_debug.h"


/* debug */
#ifndef CONFIG_KERNEL_FREERTOS
#define ROM_SYSLOG      printk
#else
#define ROM_SYSLOG      printf
#endif

#define ROM_DUMP_ON     1
#define ROM_DBG_ON      1
#define ROM_INF_ON      1
#define ROM_WRN_ON      1
#define ROM_ERR_ON      1
#define ROM_ANY_ON      1
#define ROM_ABORT_ON    0

#ifndef sys_abort
#define sys_abort()     ({volatile int i = 1; printf("%s, %d\n", __FUNCTION__, __LINE__); while(i);})
#endif

#if ROM_ABORT_ON
#define ROM_ABORT()     sys_abort()
#else
#define ROM_ABORT()
#endif

#if ROM_DUMP_ON
#define ROM_DUMP_BYTES(level, addr, len)                \
    do {                                            \
        if (level & ROM_DUMP_MASK)              \
            print_hex_dump_bytes(addr, len);\
    } while (0)
#define ROM_DUMP_WORDS(level, addr, len)                \
    do {                                            \
        if (level & ROM_DUMP_MASK)              \
            print_hex_dump_words(addr, len);\
    } while (0)
#else
#define ROM_DUMP_BYTES(level, addr, len)
#define ROM_DUMP_WORDS(level, addr, len)
#endif

#define ROM_LOG(level, mask, expand, fmt, arg...)       \
    do {                                            \
        if (level & mask)                       \
            ROM_SYSLOG(expand fmt, ##arg);  \
    } while (0)

#if ROM_DBG_ON
#define ROM_DBG(level, fmt, arg...) ROM_LOG(level, ROM_DBG_MASK, "[DBG]", fmt, ##arg)
#else
#define ROM_DBG(level, fmt, arg...)
#endif

#if ROM_INF_ON
#define ROM_INF(level, fmt, arg...) ROM_LOG(level, ROM_INF_MASK, "", fmt, ##arg)
#else
#define ROM_INF(level, fmt, arg...)
#endif

#if ROM_WRN_ON
#define ROM_WRN(level, fmt, arg...) ROM_LOG(level, ROM_WRN_MASK, "[WRN] ", fmt, ##arg)
#else
#define ROM_WRN(level, fmt, arg...)
#endif

#if ROM_ERR_ON
#define ROM_ERR(level, fmt, arg...)                     \
    do {                                            \
        if (level & ROM_ERR_MASK)               \
            ROM_SYSLOG("[ERR] "fmt, ##arg); \
        if (level & ROM_ABORT_ON) {               \
            ROM_ABORT();            \
        }                    \
    } while (0)
#else
#define ROM_ERR(level, fmt, arg...)
#endif

#if ROM_ANY_ON
#define ROM_ANY(level, fmt, arg...)                     \
    do {                                \
        if (level & ROM_ANY_MASK)               \
            ROM_SYSLOG(fmt, ##arg);         \
    } while (0)
#else
#define ROM_ANY(level, fmt, arg...)
#endif

#define ROM_ASSERT_PARAM(exp)                                           \
    do {                                                                \
        if (!(exp)) {                                                   \
            ROM_SYSLOG("Invalid param at %s:%d\n", __func__, __LINE__); \
        }                                                               \
    } while (0)

#define ROM_BUG_ON(v) do {if(v) {printf("BUG at %s:%d!\n", __func__, __LINE__); ROM_ABORT();}} while (0)
#define ROM_WARN_ON(v) do {if(v) {printf("WARN at %s:%d!\n", __func__, __LINE__);}} while (0)

#ifdef __CONFIG_ROM

#define ROM_IT_DBG      ROM_DBG
#define ROM_IT_INF      ROM_INF
#define ROM_IT_WRN      ROM_WRN
#define ROM_IT_ERR      ROM_ERR
#define ROM_IT_ANY      ROM_ANY

#ifndef __CONFIG_SECTION_ATTRIBUTE_NONXIP
#define __s_func        __func__
#endif

#else

/* debug in interrupt handler */
#ifdef __CONFIG_SECTION_ATTRIBUTE_NONXIP

#define ROM_IT_LOG(mask, fmt, arg...)                   \
    do {                                                \
        if (mask & ROM_DBG_MASK) {                      \
            __nonxip_rodata static const char __fmt[] = fmt;  \
            ROM_SYSLOG(__fmt, ##arg);                   \
        }                                               \
    } while (0)

#define ROM_IT_DBG(mask, fmt, arg...)                   \
    do {                            \
        if (mask & ROM_DBG_MASK) {             \
        __nonxip_rodata static const char __fmt[] = fmt;  \
        ROM_SYSLOG(__fmt, ##arg);           \
        }                           \
    } while (0)

#define ROM_IT_WRN(mask, fmt, arg...) \
    do {                        \
        if (mask & ROM_WRN_MASK) {             \
        __nonxip_rodata static const char __fmt[] = "[WRN] "fmt; \
        ROM_SYSLOG(__fmt, ##arg);           \
        }                           \
    } while (0)

#define ROM_IT_ERR(mask, fmt, arg...)                           \
    do {                                                    \
        if (mask & ROM_ERR_MASK) {             \
            __nonxip_rodata static const char __fmt[] = "[ERR] %s():%d, "fmt;   \
            ROM_SYSLOG(__fmt, __s_func, __LINE__, ##arg);      \
        }                                                   \
        if (mask & ROM_ABORT_MASK)                          \
            ROM_ABORT();                                \
    } while (0)

#else /* __CONFIG_SECTION_ATTRIBUTE_NONXIP */

#define __s_func        __func__
#define ROM_IT_DBG      ROM_DBG
#define ROM_IT_WRN      ROM_WRN
#define ROM_IT_ERR      ROM_ERR

#endif /* __CONFIG_SECTION_ATTRIBUTE_NONXIP */

#endif

#endif /* _ROM_DEBUG_H_ */
