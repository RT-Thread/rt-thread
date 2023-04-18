 /**********************************************************************
 * Copyright (C) 2014-2015 Cadence Design Systems, Inc.- http://www.cadence.com
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
 ***********************************************************************
 * log.h
 * System wide debug log messaging framework
 ***********************************************************************/

#ifndef _HAVE_DBG_LOG_

#define _HAVE_DBG_LOG_ 1

#include <stdio.h>
#include <assert.h>

#ifdef DEBUG
 #define CFP_DBG_MSG 1
#endif

/**
 * Modules definitions
 */
#define CLIENT_MSG         0x01000000

#define DBG_GEN_MSG        0xFFFFFFFF

/**
 * Log level:
 * DBG_CRIT - critical
 * DBG_WARN - warning
 * DBG_FYI - fyi
 * DBG_HIVERB - highly verbose
 * DBG_INFLOOP - infinite loop debug
 */
#define DBG_CRIT 0
#define DBG_WARN 5
#define DBG_FYI 10
#define DBG_HIVERB 100
#define DBG_INFLOOP 200

/* module mask: */
#ifdef _HAVE_DBG_LOG_INT_
unsigned int g_dbg_enable_log  = 0;
#else
extern unsigned int g_dbg_enable_log;
#endif

/* level, counter, state: */
#ifdef _HAVE_DBG_LOG_INT_
unsigned int g_dbg_log_lvl = DBG_CRIT;
unsigned int g_dbg_log_cnt = 0;
unsigned int g_dbg_state = 0;
#else
extern unsigned int g_dbg_log_lvl;
extern unsigned int g_dbg_log_cnt;
extern unsigned int g_dbg_state;
#endif

#define cDbgMsg( _t, _x, ...) ( ((_x)==  0) || \
                                (((_t) & g_dbg_enable_log) && ((_x) <= g_dbg_log_lvl)) ? \
                                printf( __VA_ARGS__): 0 )


#ifdef CFP_DBG_MSG
#define DbgMsg( t, x, ...)  cDbgMsg( t, x, __VA_ARGS__ )
#else
#define DbgMsg( t, x, ...)
#endif
#ifdef CFP_VDBG_MSG
#define vDbgMsg( l, m, n, ...) DbgMsg( l, m, "[%-20.20s %4d %4d]-" n, __func__,\
                                                   __LINE__, g_dbg_log_cnt++, __VA_ARGS__)
#else
#define vDbgMsg( t, x, n, ...)
#endif
#ifdef CFP_CVDBG_MSG
#define cvDbgMsg( l, m, n, ...) cDbgMsg( l, m, "[%-20.20s %4d %4d]-" n, __func__,\
                                                   __LINE__, g_dbg_log_cnt++, __VA_ARGS__)
#else
#define cvDbgMsg( l, m, n, ...)
#endif
#ifdef CFP_EVDBG_MSG
#define evDbgMsg( l, m, n, ...) { cDbgMsg( l, m, "[%-20.20s %4d %4d]-" n, __func__,         \
                                                   __LINE__, g_dbg_log_cnt++, __VA_ARGS__); \
                                  assert(0); }
#else
#define evDbgMsg( l, m, n, ...)
#endif

#define DbgMsgSetLvl( x ) (g_dbg_log_lvl = x)
#define DbgMsgEnableModule( x ) (g_dbg_enable_log |= (x) )
#define DbgMsgDisableModule( x ) (g_dbg_enable_log &= ~( (unsigned int) (x) ))
#define DbgMsgClearAll( _x ) ( g_dbg_enable_log = _x )

#define SetDbgState( _x ) (g_dbg_state = _x )
#define GetDbgState       (g_dbg_state)

#endif
