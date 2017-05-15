/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef NRF_SVCI_H__
#define NRF_SVCI_H__

#include "stdint.h"
#include "compiler_abstraction.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NRF_SVCI_SVC_NUM 0 /**< SVC number used for all SVCI functions. */
#define NRF_SVCI_SVC_NUM_INVALID (0xFFFFFFFF) /**< Invalid SVCI number. */


#if   defined (__CC_ARM)

        #define SVCI_DECL(svci_num, return_type, function_name, ...)   \
                return_type __svc_indirect(NRF_SVCI_SVC_NUM) svci_##function_name(uint32_t _svci_num, ##__VA_ARGS__);

#elif defined (__GNUC__)

        #ifdef __cplusplus
                #define GCC_CAST_CPP (uint8_t)
        #else
                #define GCC_CAST_CPP
        #endif

        #define SVCI_DECL(svci_num, return_type, function_name, ...)   \
                _Pragma("GCC diagnostic push")                          \
                _Pragma("GCC diagnostic ignored \"-Wreturn-type\"")     \
                __attribute__((naked, unused))                          \
                static return_type function_name(uint32_t svci_num,  \
                                                                                 __VA_ARGS__)           \
                {                                                       \
                        __asm __volatile (                                  \
                                "mov r12, %1\n\t"                               \
                                "svc %0\n\t"                                    \
                                "bx r14\n\t"                                    \
                                : /* no output */                               \
                                : "I" (GCC_CAST_CPP NRF_SVCI_SVC_NUM), "r" (svci_num)  \
                                : "r12" /* do we need to clobber? */            \
                        );                                                  \
                }                                                       \
                _Pragma("GCC diagnostic pop")

#elif defined (__ICCARM__)

        #define SVCI_DECL(svci_num, return_type, function_name, ...)   \
                /* Suppress return value warming. */                    \
                _Pragma("diag_suppress=Pe940")                          \
                static return_type function_name(uint32_t svci_num,      \
                                                                                 __VA_ARGS__)           \
                {                                                       \
                        __asm volatile (                                    \
                                "mov r12, %1\n\t"                               \
                                "svc %0\n\t"                                    \
                                "bx r14\n\t"                                    \
                                : /* no output */                               \
                                : "I" (NRF_SVCI_SVC_NUM), "r" (svci_num)        \
                                : "r12" /* do we need to clobber? */            \
                        );                                                  \
                }

#else

        #define SVCI_DECL(svci_number, return_type, function_name, ...)

#endif

#define VA_NARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(__VA_ARGS__, 4, 4, 3, 3, 2, 2, 1, 1, 0)

#ifdef SVC_INTERFACE_CALL_AS_NORMAL_FUNCTION

#define SVCI_0(svci_num, return_type, function_name) \
                return_type function_name(void)
#define SVCI_1(svci_num, return_type, function_name, p0t, p0n) \
                return_type function_name(p0t p0n)
#define SVCI_2(svci_num, return_type, function_name, p0t, p0n, p1t, p1n) \
                return_type function_name(p0t p0n, p1t p1n)
#define SVCI_3(svci_num, return_type, function_name, p0t, p0n, p1t, p1n, p2t, p2n) \
                return_type function_name(p0t p0n, p1t p1n, p2t p2n)
#define SVCI_4(svci_num, return_type, function_name, p0t, p0n, p1t, p1n, p2t, p2n, p3t, p3n) \
                return_type function_name(p0t p0n, p1t p1n, p2t p2n, p3t p3n)

#else

#define SVCI_0(svci_num, return_type, function_name) \
        SVCI_DECL(svci_num, return_type, function_name) \
        static __INLINE return_type function_name(void) {return svci_##function_name(svci_num);}

#define SVCI_1(svci_num, return_type, function_name, p0t, p0n) \
        SVCI_DECL(svci_num, return_type, function_name, p0t p0n) \
        static __INLINE return_type function_name(p0t p0n) {return svci_##function_name(svci_num, p0n);}

#define SVCI_2(svci_num, return_type, function_name, p0t, p0n, p1t, p1n) \
        SVCI_DECL(svci_num, return_type, function_name, p0t p0n, p1t p1n) \
        static __INLINE return_type function_name(p0t p0n, p1t p1n) {return svci_##function_name(svci_num, p0n, p1n);}

#define SVCI_3(svci_num, return_type, function_name, p0t, p0n, p1t, p1n, p2t, p2n) \
        SVCI_DECL(svci_num, return_type, function_name, p0t p0n, p1t p1n, p2t p2n) \
        static __INLINE return_type function_name(p0t p0n, p1t p1n, p2t p2n) {return svci_##function_name(svci_num, p0n, p1n, p2n);}

#define SVCI_4(svci_num, return_type, function_name, p0t, p0n, p1t, p1n, p2t, p2n, p3t, p3n) \
        SVCI_DECL(svci_num, return_type, function_name, p0t p0n, p1t p1n, p2t p2n, p3t p3n) \
        static __INLINE return_type function_name(p0t p0n, p1t p1n, p2t p2n, p3t p3n) {return svci_##function_name(svci_num, p0n, p1n, p2n, p3n);}

#endif  // SVCALL_AS_NORMAL_FUNCTION

#define SVCI_IMPLI(count, svci_num, return_type, function_name, ...) SVCI##_##count (svci_num, return_type, function_name, ##__VA_ARGS__)
#define SVCI_IMPL(count, svci_num, return_type, function_name, ...) SVCI_IMPLI(count, svci_num, return_type, function_name, ##__VA_ARGS__)
#define SVCI(svci_num, return_type, function_name, ...) SVCI_IMPL(VA_NARGS(__VA_ARGS__), svci_num, return_type, function_name, ##__VA_ARGS__)



#ifdef __cplusplus
}
#endif

#endif  // NRF_SVCI_H__
