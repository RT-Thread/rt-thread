/*

Copyright (c) 2010 - 2021, Nordic Semiconductor ASA All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. Neither the name of Nordic Semiconductor ASA nor the names of its
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef _COMPILER_ABSTRACTION_H
#define _COMPILER_ABSTRACTION_H

/*lint ++flb "Enter library region" */

#ifndef NRF_STRING_CONCATENATE_IMPL
    #define NRF_STRING_CONCATENATE_IMPL(lhs, rhs) lhs ## rhs
#endif
#ifndef NRF_STRING_CONCATENATE
    #define NRF_STRING_CONCATENATE(lhs, rhs) NRF_STRING_CONCATENATE_IMPL(lhs, rhs)
#endif

#if defined ( __CC_ARM )

    #ifndef __ASM
        #define __ASM               __asm
    #endif

    #ifndef __INLINE
        #define __INLINE            __inline
    #endif

    #ifndef __WEAK
        #define __WEAK              __weak
    #endif

    #ifndef __ALIGN
        #define __ALIGN(n)          __align(n)
    #endif

    #ifndef __PACKED
        #define __PACKED            __packed
    #endif

    #ifndef __UNUSED
        #define __UNUSED            __attribute__((unused))
    #endif

    #define GET_SP()                __current_sp()

    #ifndef NRF_STATIC_ASSERT
        #define NRF_STATIC_ASSERT(cond, msg) \
            ;enum { NRF_STRING_CONCATENATE(static_assert_on_line_, __LINE__) = 1 / (!!(cond)) }
    #endif
    
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)

    #ifndef __ASM
        #define __ASM               __asm
    #endif

    #ifndef __INLINE
        #define __INLINE            __inline
    #endif

    #ifndef __WEAK
        #define __WEAK              __attribute__((weak))
    #endif

    #ifndef __ALIGN
        #define __ALIGN(n)          __attribute__((aligned(n)))
    #endif

    #ifndef __PACKED
        #define __PACKED            __attribute__((packed, aligned(1)))
    #endif

    #ifndef __UNUSED
        #define __UNUSED            __attribute__((unused))
    #endif

    #define GET_SP()                __current_sp()

    #ifndef NRF_STATIC_ASSERT
        #ifdef __cplusplus
            #ifndef _Static_assert
                #define _Static_assert static_assert
            #endif
        #endif
        #define NRF_STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
    #endif

#elif defined ( __ICCARM__ )

    #ifndef __ASM
        #define __ASM               __asm
    #endif

    #ifndef __INLINE
        #define __INLINE            inline
    #endif

    #ifndef __WEAK
        #define __WEAK              __weak
    #endif

    #if (__VER__ >= 8000000)
        #ifndef __ALIGN
            #define __ALIGN(n) __attribute__((aligned(x)))
        #endif

        #ifndef   __PACKED
            #define __PACKED __attribute__((packed, aligned(1)))
        #endif
    #else
        #ifndef __ALIGN
            #define STRING_PRAGMA(x) _Pragma(#x)
            #define __ALIGN(n) STRING_PRAGMA(data_alignment = n)
        #endif

        #ifndef   __PACKED
            #define __PACKED __packed
        #endif
    #endif

    #ifndef __UNUSED
        #define __UNUSED
    #endif
    
    #define GET_SP()                __get_SP()

    #ifndef NRF_STATIC_ASSERT
        #define NRF_STATIC_ASSERT(cond, msg) static_assert(cond, msg)
    #endif

#elif defined   ( __GNUC__ ) ||  defined   ( __clang__ )

    #ifndef __ASM
        #define __ASM               __asm
    #endif

    #ifndef __INLINE
        #define __INLINE            inline
    #endif

    #ifndef __WEAK
        #define __WEAK              __attribute__((weak))
    #endif

    #ifndef __ALIGN
        #define __ALIGN(n)          __attribute__((aligned(n)))
    #endif

    #ifndef __PACKED
        #define __PACKED           __attribute__((packed)) 
    #endif

    #ifndef __UNUSED
        #define __UNUSED            __attribute__((unused))
    #endif

    #define GET_SP()                gcc_current_sp()

    static inline unsigned int gcc_current_sp(void)
    {
        unsigned int stack_pointer = 0;
        __asm__ __volatile__ ("mov %0, sp" : "=r"(stack_pointer));
        return stack_pointer;
    }

    #ifndef NRF_STATIC_ASSERT
        #ifdef __cplusplus
            #ifndef _Static_assert
                #define _Static_assert static_assert
            #endif
        #endif
        #define NRF_STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
    #endif

#elif defined   ( __TASKING__ )

    #ifndef __ASM
        #define __ASM               __asm
    #endif

    #ifndef __INLINE
        #define __INLINE            inline
    #endif

    #ifndef __WEAK
        #define __WEAK              __attribute__((weak))
    #endif

    #ifndef __ALIGN
        #define __ALIGN(n)          __align(n)
    #endif
    
    /* Not defined for TASKING. */
    #ifndef __PACKED
        #define __PACKED
    #endif

    #ifndef __UNUSED
        #define __UNUSED            __attribute__((unused))
    #endif

    #define GET_SP()                __get_MSP()

    #ifndef NRF_STATIC_ASSERT
        #define NRF_STATIC_ASSERT(cond, msg) static_assert(cond, msg)
    #endif

#endif

#define NRF_MDK_VERSION_ASSERT_AT_LEAST(major, minor, micro) \
    NRF_STATIC_ASSERT( \
        ( \
            (major < MDK_MAJOR_VERSION) || \
            (major == MDK_MAJOR_VERSION && minor < MDK_MINOR_VERSION) || \
            (major == MDK_MAJOR_VERSION && minor == MDK_MINOR_VERSION && micro < MDK_MICRO_VERSION) \
        ), "MDK version mismatch.")

#define NRF_MDK_VERSION_ASSERT_EXACT(major, minor, micro) \
    NRF_STATIC_ASSERT( \
        ( \
            (major != MDK_MAJOR_VERSION) || \
            (major != MDK_MAJOR_VERSION) || \
            (major != MDK_MAJOR_VERSION) \
        ), "MDK version mismatch.")

/*lint --flb "Leave library region" */

#endif
