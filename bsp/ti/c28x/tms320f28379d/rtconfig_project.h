/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-27     xuzhuoyi     the first version
 * 2022-08-22     guyunjie     remove data types other than 8bit for compatibility with libc
 */

#ifndef __RTCONFIG_PROJECT_H__
#define __RTCONFIG_PROJECT_H__

/* C28X does not support 8bit data type by hardward (char = 16bit) so
 * 8bit data types are not defined in its standard libs. We define them
 * here. Be careful that the 8bit is actually 16bit. */
#define UINT8_MAX      0xff         /**< Maximum number of UINT8 */
typedef signed   char  int8_t;      /**<  8bit integer type */
typedef unsigned char  uint8_t;     /**<  8bit unsigned integer type */

/* C28X automatically disable interrupt in interrupt service routine.
 * We need to enable manually to allow for interrupt nesting by calling
 * this macro at the start of preemptible interrupt service routines*/
#define ALLOW_ISR_PREEMPT() __asm(" CLRC INTM")

#define RT_USING_ZERO_LATENCY
#define ZERO_LATENCY_INT_MASK 0x0000

#endif
