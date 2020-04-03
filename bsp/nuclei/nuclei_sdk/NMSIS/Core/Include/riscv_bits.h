/*
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __RISCV_BITS_H__
#define __RISCV_BITS_H__

#ifdef __cplusplus
 extern "C" {
#endif

#if __riscv_xlen == 64
# define SLL32                  sllw
# define STORE                  sd
# define LOAD                   ld
# define LWU                    lwu
# define LOG_REGBYTES           3
#else
# define SLL32                  sll
# define STORE                  sw
# define LOAD                   lw
# define LWU                    lw
# define LOG_REGBYTES           2
#endif /* __riscv_xlen */

#define REGBYTES (1 << LOG_REGBYTES)

#if __riscv_flen == 64
# define FPSTORE                fsd
# define FPLOAD                 fld
# define LOG_FPREGBYTES         3
#else
# define FPSTORE                fsw
# define FPLOAD                 flw
# define LOG_FPREGBYTES         2
#endif /* __riscv_flen */
#define FPREGBYTES              (1 << LOG_FPREGBYTES)

#define __rv_likely(x)          __builtin_expect((x), 1)
#define __rv_unlikely(x)        __builtin_expect((x), 0)

#define __RV_ROUNDUP(a, b)      ((((a)-1)/(b)+1)*(b))
#define __RV_ROUNDDOWN(a, b)    ((a)/(b)*(b))

#define __RV_MAX(a, b)          ((a) > (b) ? (a) : (b))
#define __RV_MIN(a, b)          ((a) < (b) ? (a) : (b))
#define __RV_CLAMP(a, lo, hi)   MIN(MAX(a, lo), hi)

#define __RV_EXTRACT_FIELD(val, which)                  (((val) & (which)) / ((which) & ~((which)-1)))
#define __RV_INSERT_FIELD(val, which, fieldval)         (((val) & ~(which)) | ((fieldval) * ((which) & ~((which)-1))))

#ifdef __ASSEMBLY__
#define _AC(X,Y)                X
#define _AT(T,X)                X
#else
#define __AC(X,Y)               (X##Y)
#define _AC(X,Y)                __AC(X,Y)
#define _AT(T,X)                ((T)(X))
#endif /* __ASSEMBLY__ */

#define _UL(x)                  (_AC(x, UL))
#define _ULL(x)                 (_AC(x, ULL))

#define _BITUL(x)               (_UL(1) << (x))
#define _BITULL(x)              (_ULL(1) << (x))

#define UL(x)                   (_UL(x))
#define ULL(x)                  (_ULL(x))

#define STR(x)                  XSTR(x)
#define XSTR(x)                 #x
#define __STR(s)                #s
#define STRINGIFY(s)            __STR(s)

#ifdef __cplusplus
}
#endif

#endif /** __RISCV_BITS_H__  */
