//*****************************************************************************
//
//  am_hal_global.h
//! @file
//!
//! @brief Locate all HAL global variables here.
//!
//! This module contains global variables that are used throughout the HAL,
//! but not necessarily those designated as const (which typically end up in
//! flash). Consolidating globals here will make it easier to manage them.
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
#ifndef AM_HAL_GLOBAL_H
#define AM_HAL_GLOBAL_H

//*****************************************************************************
//
// Macro definitions
//
//*****************************************************************************

//******************************************************************************
//
// Macros used to access the bit fields in the flags variable.
//
//******************************************************************************
#define AM_HAL_FLAGS_BFR(flagnm)                                            \
    ((g_ui32HALflags & AM_HAL_FLAGS_##flagnm##_M) >> AM_HAL_FLAGS_##flagnm##_S)

#define AM_HAL_FLAGS_BFW(flagnm, value)                                     \
    g_ui32HALflags = ((g_ui32HALflags & (~(AM_HAL_FLAGS_##flagnm##_M)))  |    \
     ((value << AM_HAL_FLAGS_##flagnm##_S) & (AM_HAL_FLAGS_##flagnm##_M)) )

//******************************************************************************
//
// ITMSKIPENABLEDISABLE - Set when the ITM is not to be disabled.  This is
//                        typically needed by Keil debug.ini.
//
//******************************************************************************
#define AM_HAL_FLAGS_ITMSKIPENABLEDISABLE_S         0
#define AM_HAL_FLAGS_ITMSKIPENABLEDISABLE_M         (1 << AM_HAL_FLAGS_ITMSKIPENABLEDISABLE_S)
#define AM_HAL_FLAGS_ITMSKIPENABLEDISABLE(n)        (((n) << AM_HAL_FLAGS_ITMSKIPENABLEDISABLE_S) & AM_HAL_FLAGS_ITMSKIPENABLEDISABLE_M)

//******************************************************************************
//
// ITMBKPT - Breakpoint at the end of itm_enable(), which is needed by
//           Keil debug.ini.
//
//******************************************************************************
#define AM_HAL_FLAGS_ITMBKPT_S                      1
#define AM_HAL_FLAGS_ITMBKPT_M                      (1 << AM_HAL_FLAGS_ITMBKPT_S)
#define AM_HAL_FLAGS_ITMBKPT(n)                     (((n) << AM_HAL_FLAGS_ITMBKPT_S) & AM_HAL_FLAGS_ITMBKPT_M)

//******************************************************************************
//
// Next available flag or bit field.
//
//******************************************************************************
#define AM_HAL_FLAGS_NEXTBITFIELD_S                 2
#define AM_HAL_FLAGS_NEXTBITFIELD_M                 (1 << AM_HAL_FLAGS_NEXTBITFIELD_S)
#define AM_HAL_FLAGS_NEXTBITFIELD(n)                (((n) << AM_HAL_FLAGS_NEXTBITFIELD_S) & AM_HAL_FLAGS_NEXTBITFIELD_M)

//*****************************************************************************
//
// Global Variables extern declarations.
//
//*****************************************************************************
extern volatile uint32_t g_ui32HALflags;

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_GLOBAL_H
