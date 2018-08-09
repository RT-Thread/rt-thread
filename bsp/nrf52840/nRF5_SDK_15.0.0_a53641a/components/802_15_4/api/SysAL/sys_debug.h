/**
 * Copyright (c) 2016 - 2018 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 * 
 * All Rights Reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
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
#ifndef SYS_DEBUG_H_INCLUDED
#define SYS_DEBUG_H_INCLUDED


#include "hal_debug_interface.h"
#include "hal_trace_interface.h"
#include <stdbool.h>
#include <stdarg.h>

/*  This header file contains macros for debugging. */

#ifndef ASSERT
    #ifdef CONFIG_DEBUG
        #define ASSERT(CONDITION_STATEMENT) \
            do \
            { \
                bool LOCAL_CONDITION_CHECK = (CONDITION_STATEMENT); \
                if (LOCAL_CONDITION_CHECK != true) \
                { \
                    sys_assert_handler((#CONDITION_STATEMENT), __LINE__, __FILE__); \
                } \
            } while (0)
    #else

    #define ASSERT(CONDITION_STATEMENT)

    #endif  // CONFIG_DEBUG
#endif // ASSERT

#ifndef ASSERT_INFO
    #ifdef CONFIG_DEBUG
        #define ASSERT_INFO(CONDITION_STATEMENT, INFO_FMT, ...)    \
            do \
            { \
                bool LOCAL_CONDITION_CHECK = (CONDITION_STATEMENT); \
                if (LOCAL_CONDITION_CHECK != true) \
                { \
                    sys_assert_info_handler((#CONDITION_STATEMENT), __LINE__, __FILE__, \
                        INFO_FMT, __VA_ARGS__); \
                } \
            } while (0)

    #else

    #define ASSERT_INFO(CONDITION_STATEMENT, INFO_FMT, ...)
    
    #endif  // CONFIG_DEBUG
#endif // ASSERT_INFO

#ifndef ASSERT_STATIC
    #ifdef CONFIG_DEBUG
        #define ASSERT_STATIC(e)       do { enum {SA = 1/(e)}; } while (0)
    #else
        #define ASSERT_STATIC(e)
    #endif  // CONFIG_DEBUG
#endif // ASSERT_STATIC

/** 
 * @defgroup sys_debug Debugging macros
 * @ingroup sys_15_4
 * @{
 * @brief Functions used for debugging.
 */


/**@brief   System assertion fault handler.
 *
 * @details This macro should be used whenever an assertion fault is detected.
 *
 * @param[in]   CONDITION_STRING    Assertion condition string, which occurred to be not true.
 */
#define SYS_ASSERT_HANDLER(CONDITION_STRING) \
    do \
    { \
        sys_assert_handler(CONDITION_STRING, __LINE__, __FILE__); \
    } while (0)


#ifndef TRACE_PUTS
    #ifdef CONFIG_TRACE
        #define TRACE_PUTS(s)         HAL_TRACE_INTERFACE_PUTS(s)
    #else
        #define TRACE_PUTS(s)
    #endif  //CONFIG_TRACE
#endif //TRACE_PUTS


#ifndef TRACE
    #ifdef CONFIG_TRACE
        #define TRACE(INFO_FMT, ...)  sys_trace_handler(INFO_FMT, __VA_ARGS__)
    #else
        #define TRACE(INFO_FMT, ...)
    #endif  // CONFIG_DEBUG 
#endif // TRACE


/**@brief   System assertion fault handler function.
 *
 * @param[in]   condition   Assertion condition string, which was expected to be true.
 *
 * @param[in]   line        Line number.
 *
 * @param[in]   file        File name.
 */
extern void sys_assert_handler(
        const char * condition, const int line, const char * file);


/**@brief   System assertion fault handler function with additional assertion information.
 *
 * @param[in]   condition   Assertion condition string, which was expected to be true.
 *
 * @param[in]   line        Line number.
 *
 * @param[in]   file        File name.
 *
 * @param[in]   info_fmt    Format string for additional assert information.
 *
 * @param[in]   ...         Arguments list corresponding to the format string.
 */
extern void sys_assert_info_handler(
        const char * condition, const int line, const char * file,
        const char * info_fmt, ...);


/**@brief   System trace output handler function.
 *
 * @param[in]   fmt    Format string for trace output.
 *
 * @param[in]   ...    Arguments list corresponding to the format string.
 */
extern void sys_trace_handler(const char * fmt, ...);

/** @} */

#endif // SYS_DEBUG_H_INCLUDED
