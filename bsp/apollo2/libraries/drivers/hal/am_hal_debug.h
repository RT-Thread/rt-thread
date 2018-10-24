//*****************************************************************************
//
//  am_hal_debug.h
//! @file
//!
//! @brief Useful macros for debugging.
//!
//! These functions and macros were created to assist with debugging. They are
//! intended to be as unintrusive as possible and designed to be removed from
//! the compilation of a project when they are no longer needed.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#ifndef AM_HAL_DEBUG_H
#define AM_HAL_DEBUG_H

//*****************************************************************************
//
// Debug assert macros.
//
//*****************************************************************************
#ifndef AM_HAL_DEBUG_NO_ASSERT

#define am_hal_debug_assert_msg(bCondition, pcMessage)                        \
    if ( !(bCondition))  am_hal_debug_error(__FILE__, __LINE__, pcMessage)

#define am_hal_debug_assert(bCondition)                                       \
    if ( !(bCondition))  am_hal_debug_error(__FILE__, __LINE__, 0)

#else

#define am_hal_debug_assert_msg(bCondition, pcMessage)
#define am_hal_debug_assert(bCondition)

#endif // AM_DEBUG_ASSERT

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// External function prototypes.
//
//*****************************************************************************
extern void am_hal_debug_error(const char *pcFile, uint32_t ui32Line,
                               const char *pcMessage);

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_DEBUG_H

