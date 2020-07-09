/*
 * Copyright (c) 2008-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __SDK_TYPES_H__
#define __SDK_TYPES_H__

//! @addtogroup sdk_common
//! @{

/*!
 * @file sdk_types.h
 * @brief Basic types used throughout the SDK.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @name Alternate Boolean constants
//@{
#define TRUE        1
#define FALSE       0
//@}

//! @brief 
#define NONE_CHAR   (0xFF)

//! @brief A parameter was out of range or otherwise invalid.
#define INVALID_PARAMETER (-1)

//! @name Min/max macros
//@{
#if !defined(MIN)
    #define MIN(a, b)   ((a) < (b) ? (a) : (b))
#endif

#if !defined(MAX)
    #define MAX(a, b)   ((a) > (b) ? (a) : (b))
#endif
//@}

//! @brief Computes the number of elements in an array.
#define ARRAY_SIZE(x)	(sizeof(x) / sizeof((x)[0]))

//! @brief Debug print utility.
//!
//! This print function will only output text when the @a DEBUG macro is defined.
static inline void debug_printf(const char * format, ...)
{
#if defined(DEBUG)
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif
}

//! @name Test results
typedef enum _test_return
{
    TEST_NOT_STARTED     = -3, // present in the menu, but not run
    TEST_NOT_IMPLEMENTED = -2, // present in the menu, but not functional
    TEST_FAILED          = -1,
    TEST_PASSED          = 0,
    TEST_BYPASSED        = 2,  // user elected to exit the test before it was run
    TEST_NOT_PRESENT     = 3,  // not present in the menu.
    TEST_CONTINUE        = 4   // proceed with the test. opposite of TEST_BYPASSED
} test_return_t;

//! @name Return codes
//@{
#define SUCCESS (0)
#define FAIL (1)
#define ERROR_GENERIC (-1)
#define ERROR_OUT_OF_MEMORY (-2)
//@}

//! @brief Possible types of displays.
enum display_type {
    DISP_DEV_NULL = 0,
    DISP_DEV_TFTLCD,
    DISP_DEV_LVDS,
    DISP_DEV_VGA,
    DISP_DEV_HDMI,
    DISP_DEV_TV,
    DISP_DEV_MIPI,
};

//! @}

#endif // __SDK_TYPES_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
