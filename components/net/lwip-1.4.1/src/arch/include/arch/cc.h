/*
 * Copyright (c) 2001, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: cc.h,v 1.1.1.1 2004/12/16 14:17:13 bear Exp $
 */
#ifndef __ARCH_CC_H__
#define __ARCH_CC_H__

#include <rthw.h>
#include <rtthread.h>
#include <string.h>
#include <stdint.h>

#ifndef BYTE_ORDER
#ifdef RT_USING_BIG_ENDIAN
#define BYTE_ORDER BIG_ENDIAN
#else
#define BYTE_ORDER LITTLE_ENDIAN
#endif /* RT_USING_BIG_ENDIAN */
#endif /* BYTE_ORDER */

typedef uint8_t   u8_t;
typedef int8_t    s8_t;
typedef uint16_t  u16_t;
typedef int16_t   s16_t;
typedef uint32_t  u32_t;
typedef int32_t   s32_t;
typedef uintptr_t mem_ptr_t;

#define U16_F "hu"
#define S16_F "hd"
#define X16_F "hx"
#define U32_F "lu"
#define S32_F "ld"
#define X32_F "lx"

#include <sys/errno.h>
/* some errno not defined in newlib */
#ifndef ENSRNOTFOUND
#define ENSRNOTFOUND 163  /* Domain name not found */
/* WARNING: ESHUTDOWN also not defined in newlib. We chose
            180 here because the number "108" which is used
            in arch.h has been assigned to another error code. */
#endif

/* LWIP_TIMEVAL_PRIVATE: provided by <sys/time.h> */
#include <sys/time.h>
#define LWIP_TIMEVAL_PRIVATE       0

#if defined(__CC_ARM)   /* ARMCC compiler */
#define PACK_STRUCT_FIELD(x) x
#define PACK_STRUCT_STRUCT __attribute__ ((__packed__))
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /*Arm Compiler 6*/
#define PACK_STRUCT_FIELD(x) x
#define PACK_STRUCT_STRUCT __attribute__((packed))
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END
#elif defined(__IAR_SYSTEMS_ICC__)   /* IAR Compiler */
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_STRUCT
#define PACK_STRUCT_END
#define PACK_STRUCT_FIELD(x) x
#define PACK_STRUCT_USE_INCLUDES
#elif defined(__GNUC__)     /* GNU GCC Compiler */
#define PACK_STRUCT_FIELD(x) x
#define PACK_STRUCT_STRUCT __attribute__((packed))
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END
#elif defined(_MSC_VER)
#define PACK_STRUCT_FIELD(x) x
#define PACK_STRUCT_STRUCT
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END
#endif

void sys_arch_assert(const char* file, int line);
#define LWIP_PLATFORM_DIAG(x)   do {rt_kprintf x;} while(0)
#define LWIP_PLATFORM_ASSERT(x) do {rt_kprintf(x); sys_arch_assert(__FILE__, __LINE__);}while(0)

#define SYS_ARCH_DECL_PROTECT(level)    register rt_base_t level
#define SYS_ARCH_PROTECT(level)         do {level = rt_hw_interrupt_disable();} while(0)
#define SYS_ARCH_UNPROTECT(level)       do {rt_hw_interrupt_enable(level);} while(0)

#endif /* __ARCH_CC_H__ */
