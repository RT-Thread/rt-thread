/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_type.h
 * @brief    source file for setting type
 *
 * Change Logs:
 * Date           Author      Version        Notes
 * 2020-11-05     wushengyan         V1.0.0         the first version
 */

#ifndef __TYPE_H__
#define __TYPE_H__

#if defined (__CC_ARM) || defined ( __ICCARM__ )
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned char      byte;
typedef unsigned short     word;

typedef signed char       int8_t;
typedef signed short      int16_t;
typedef signed int        int32_t;
typedef signed long long  int64_t;
#else
#include "stdio.h"
typedef unsigned char      byte;
typedef unsigned short     word;
#endif

/** 
  * @brief  __NOINLINE definition
  */ 
#if defined ( __CC_ARM   ) || defined   (  __GNUC__  )
/* ARM & GNUCompiler 
   ---------------- 
*/
#define __NOINLINE   noinline

#elif defined ( __ICCARM__ )
/* ICCARM Compiler
   ---------------
*/
#define __NOINLINE _Pragma("optimize = no_inline")

#endif

#ifndef Boolean
typedef enum {FALSE = 0, TRUE =1} Boolean;
#define IS_BOOLEAN(bool) ((bool == FALSE) || (bool == TRUE))
#endif

#ifndef FunctionalState
typedef enum {DISABLE = 0, ENABLE =1} FunctionalState;
#define IS_FUNCTIONAL_STATE(state) ((state== DISABLE) || (state == ENABLE))
#endif

#ifndef FunctionalState
typedef enum {ERROR = 0, SUCCESS = 1} ErrorStatus;
#define IS_ERROR_STATE(status) ((status== ERROR) || (status == SUCCESS))
#endif

#ifndef FlagStatus
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
#endif

#ifndef YC_NULL
#define YC_NULL                         (0)
#endif

#ifndef NULL
#define NULL							(0)
#endif

#endif /*__TYPE_H__*/

