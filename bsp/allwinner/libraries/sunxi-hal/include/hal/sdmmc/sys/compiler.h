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

#ifndef _COMPILER_H_
#define _COMPILER_H_

#if defined(__CC_ARM)
/* ARM Compiler */

#define inline      __inline
//#define __inline  __inline
#define __inline__  __inline

#ifndef __always_inline
#define __always_inline __forceinline
#endif

#ifndef __noinline
#define __noinline
#endif

#if defined(__GNUC__)
/* ARM Compiler support GNU */
#define __packed    __attribute__((__packed__))
#else
//#define __packed  __packed
#endif
//#define __asm     __asm
//#define __weak    __weak

#elif defined(__GNUC__)
/* GNU Compiler */

// #include <sys/cdefs.h>

//#define inline    inline
#define __inline    inline
#define __inline__  inline

#ifdef __always_inline
#undef __always_inline  /* already defined in <sys/cdefs.h> */
#define __always_inline inline __attribute__((always_inline))
#else
#define __always_inline inline __attribute__((always_inline))
#endif

#ifndef __noinline
#define __noinline  __attribute__((__noinline__))
#endif

// #define __packed __attribute__((__packed__))
#define __asm       asm
#define __weak      __attribute__((weak))

#ifdef __CONFIG_XIP_SECTION_FUNC_LEVEL
#define __xip_text      __attribute__((section (".xip_text")))
#define __xip_rodata    __attribute__((section (".xip_rodata")))
#define __nonxip_text   __attribute__((section (".nonxip_text")))
#define __nonxip_data   __attribute__((section (".nonxip_data")))
#define __nonxip_rodata __attribute__((section (".nonxip_rodata")))
#else /* __CONFIG_XIP_SECTION_FUNC_LEVEL */
#define __xip_text
#define __xip_rodata
#define __nonxip_text
#define __nonxip_data
#define __nonxip_rodata
#endif /* __CONFIG_XIP_SECTION_FUNC_LEVEL */

#else
#error "Compiler not supported."
#endif

#endif /* _COMPILER_H_ */
