/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup sdk_nrf_svci Supervisor instructions with indirect number
 * @{
 * @ingroup app_common
 *
 * @brief Macros to create Supervisor instructions using indirect number.
 */

#ifndef NRF_SVCI_H__
#define NRF_SVCI_H__

#include "stdint.h"
#include "compiler_abstraction.h"
#include "app_util.h"




#ifdef __cplusplus
extern "C" {
#endif

#define NRF_SVCI_SVC_NUM 0                      /**< SVC number used for all SVCI functions. */
#define NRF_SVCI_SVC_NUM_INVALID (0xFFFFFFFF)   /**< Invalid SVCI number. */

#ifdef __cplusplus
    #define GCC_CAST_CPP (uint16_t)
#else
    #define GCC_CAST_CPP
#endif

#if (__LINT__ != 1)    

#if   defined (__CC_ARM)

    #define SVCI_DECL(svci_num, return_type, function_name, ...)        \
        return_type __svc_indirect(NRF_SVCI_SVC_NUM)                    \
        svci_ ## function_name(uint32_t _svci_num, ##__VA_ARGS__);
     
    #define SVCI_DECL_0(svci_num, return_type, function_name)           \
        return_type __svc_indirect(NRF_SVCI_SVC_NUM)                    \
        svci_ ## function_name(uint32_t _svci_num);    
    
    #define SVCI_0(svci_num, return_type, function_name)                \
        SVCI_DECL_0(svci_num, return_type, function_name)               \
        static __INLINE return_type function_name(void)                 \
        {                                                               \
            return svci_ ## function_name(svci_num);  \
        }

    #define SVCI_1(svci_num, return_type, function_name, p0t, p0n)              \
        SVCI_DECL(svci_num, return_type, function_name, p0t p0n)                \
        static __INLINE return_type function_name(p0t p0n)                      \
        {                                                                       \
            return svci_ ## function_name(svci_num, p0n);                       \
        }

    #define SVCI_2(svci_num, return_type, function_name, p0t, p0n, p1t, p1n)        \
        SVCI_DECL(svci_num, return_type, function_name, p0t p0n, p1t p1n)           \
        static __INLINE return_type function_name(p0t p0n, p1t p1n)                 \
        {                                                                           \
            return svci_ ## function_name(svci_num, p0n, p1n);                      \
        }

    #define SVCI_3(svci_num, return_type, function_name, p0t, p0n, p1t, p1n, p2t, p2n)      \
        SVCI_DECL(svci_num, return_type, function_name, p0t p0n, p1t p1n, p2t p2n)          \
        static __INLINE return_type function_name(p0t p0n, p1t p1n, p2t p2n)                \
        {                                                                                   \
            return svci_ ## function_name(svci_num, p0n, p1n, p2n);                         \
        }

    #define SVCI_4(svci_num, return_type, function_name, p0t, p0n, p1t, p1n, p2t, p2n, p3t, p3n)    \
        SVCI_DECL(svci_num, return_type, function_name, p0t p0n, p1t p1n, p2t p2n, p3t p3n)         \
        static __INLINE return_type function_name(p0t p0n, p1t p1n, p2t p2n, p3t p3n)               \
        {                                                                                           \
            return svci_ ## function_name(svci_num, p0n, p1n, p2n, p3n);                            \
        }
        
#else
        
#if defined (__GNUC__)

    #define SVCI_DECL_0(svci_num, return_type, function_name)           \
        _Pragma("GCC diagnostic push")                                  \
        _Pragma("GCC diagnostic ignored \"-Wreturn-type\"")             \
        __attribute__((naked, unused))                                  \
        static return_type svci_ ## function_name(void)                 \
        {                                                               \
            /* Do the SuperVisor call by using svc instruction with     \
               R12 containing the SVCI number */                        \
            __ASM __volatile                                            \
            (                                                           \
                "  ldr r12, =%0       \n"                               \
                "  svc %1             \n"                               \
                "  bx lr              \n"                               \
                "  .ltorg"                                              \
                : /* output */                                          \
                : /* input */                                           \
                    "X"(svci_num),                                      \
                    "I"(GCC_CAST_CPP NRF_SVCI_SVC_NUM)                  \
                : /* clobbers */                                        \
                    "r12"                                               \
            );                                                          \
        }                                                               \
        _Pragma("GCC diagnostic pop")    
    
    #define SVCI_DECL(svci_num, return_type, function_name, ...)        \
        _Pragma("GCC diagnostic push")                                  \
        _Pragma("GCC diagnostic ignored \"-Wreturn-type\"")             \
        __attribute__((naked, unused))                                  \
        static return_type svci_ ## function_name(__VA_ARGS__)          \
        {                                                               \
            /* Do the SuperVisor call by using svc instruction with     \
               R12 containing the SVCI number */                        \
            __ASM __volatile                                            \
            (                                                           \
                "  ldr.w r12, =%0     \n"                               \
                "  svc %1             \n"                               \
                "  bx lr              \n"                               \
                "  .ltorg"                                              \
                : /* output */                                          \
                : /* input */                                           \
                    "X"(svci_num),                                      \
                    "I"(GCC_CAST_CPP NRF_SVCI_SVC_NUM)                  \
                : /* clobbers */                                        \
                    "r12"                                               \
            );                                                          \
        }                                                               \
        _Pragma("GCC diagnostic pop")

#elif defined (__ICCARM__)

    #define SVCI_DECL_0(svci_num, return_type, function_name)           \
        /* Suppress return value warning. */                            \
        _Pragma("diag_suppress=Pe940")                                  \
        static __root return_type svci_ ## function_name(void)          \
        {                                                               \
            /* Do the SuperVisor call by using svc instruction with     \
               R12 containing the SVCI number */                        \
            __ASM volatile                                              \
            (                                                           \
                "  mov r12, %0      \n"                                 \
                "  svc %1           \n"                                 \
                : /*no output*/                                         \
                : "r" (svci_num), "I" (NRF_SVCI_SVC_NUM)                \
                :                                                       \
            );                                                          \
        }

    #define SVCI_DECL(svci_num, return_type, function_name, ...)        \
        /* Suppress return value warning. */                            \
        _Pragma("diag_suppress=Pe940")                                  \
        static __root return_type svci_ ## function_name(__VA_ARGS__)   \
        {                                                               \
            /* We stack r0-r3 as r0 is used to set high register (r12)  \
               This CODE MUST BE IN ITS OWN __ASM BLOCK! */             \
            __ASM volatile ( "push {r0, r1, r2, r3}\n\t" );             \
            /* Set R12 to the svc_number, this will use r0 as indirect  \
             * storage. Pop r0-r3 to reset value before SVCI. */        \
            __ASM volatile                                              \
            (                                                           \
                "  mov r12, %0          \n"                             \
                "  pop {r0, r1, r2, r3} \n"                             \
                : /*no output */                                        \
                : "r" (svci_num)                                        \
                :                                                       \
            );                                                          \
            /* Do the SuperVisor call by using svc instruction with     \
               R12 containing the SVCI number */                        \
            __ASM volatile                                              \
            (                                                           \
                "  svc %0               \n"                             \
                "  bx lr                \n"                             \
                : /*no output*/                                         \
                : "I" (NRF_SVCI_SVC_NUM)                                \
                :                                                       \
            );                                                          \
        }        
#else // Not defined (__ICCARM__) or  defined (__GNUC__)

    #error Unsupported compiler for SVCI interface

#endif // Not defined (__ICCARM__) or  defined (__GNUC__)
    
        #define SVCI_0(svci_num, return_type, function_name)            \
        SVCI_DECL_0(svci_num, return_type, function_name)               \
        static __INLINE return_type function_name(void)                 \
        {                                                               \
            return svci_ ## function_name();                            \
        }

    #define SVCI_1(svci_num, return_type, function_name, p0t, p0n)              \
        SVCI_DECL(svci_num, return_type, function_name, p0t p0n)                \
        static __INLINE return_type function_name(p0t p0n)                      \
        {                                                                       \
            return svci_ ## function_name(p0n);                                 \
        }

    #define SVCI_2(svci_num, return_type, function_name, p0t, p0n, p1t, p1n)        \
        SVCI_DECL(svci_num, return_type, function_name, p0t p0n, p1t p1n)           \
        static __INLINE return_type function_name(p0t p0n, p1t p1n)                 \
        {                                                                           \
            return svci_ ## function_name(p0n, p1n);                                \
        }

    #define SVCI_3(svci_num, return_type, function_name, p0t, p0n, p1t, p1n, p2t, p2n)      \
        SVCI_DECL(svci_num, return_type, function_name, p0t p0n, p1t p1n, p2t p2n)          \
        static __INLINE return_type function_name(p0t p0n, p1t p1n, p2t p2n)                \
        {                                                                                   \
            return svci_ ## function_name(p0n, p1n, p2n);       \
        }

    #define SVCI_4(svci_num, return_type, function_name, p0t, p0n, p1t, p1n, p2t, p2n, p3t, p3n)    \
        SVCI_DECL(svci_num, return_type, function_name, p0t p0n, p1t p1n, p2t p2n, p3t p3n)         \
        static __INLINE return_type function_name(p0t p0n, p1t p1n, p2t p2n, p3t p3n)               \
        {                                                                                           \
            return svci_ ## function_name(p0n, p1n, p2n, p3n);                                      \
        }
        
#endif // Not __CC_ARM

#define VA_NARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(__VA_ARGS__, 4, 4, 3, 3, 2, 2, 1, 1, 0)

#ifdef SVCALL_INDIRECT_AS_NORMAL_FUNCTION

#define SVCI(svci_num, return_type, function_name, ...)                     \
    return_type function_name(##__VA_ARGS__)

#else
    
    
#define SVCI_IMPLI(count, svci_num, return_type, function_name, ...)        \
    SVCI##_##count (svci_num, return_type, function_name, ##__VA_ARGS__)

#define SVCI_IMPL(count, svci_num, return_type, function_name, ...)         \
    SVCI_IMPLI(count, svci_num, return_type, function_name, ##__VA_ARGS__)

#define SVCI(svci_num, return_type, function_name, ...)                     \
    SVCI_IMPL(VA_NARGS(__VA_ARGS__), svci_num, return_type, function_name, ##__VA_ARGS__)

    
#endif  // SVCALL_INDIRECT_AS_NORMAL_FUNCTION

#else // (__LINT__ == 1)
    #define SVCI(svci_num, return_type, function_name, ...)
#endif 

#ifdef __cplusplus
}
#endif



#endif  // NRF_SVCI_H__




/** @} */
