//*****************************************************************************
//
//! @file am_reg_macros_asm.h
//!
//! @brief Inline assembly macros. Initially for critical section handling in
//! protecting hardware registers.
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

#ifndef AM_REG_MACROS_ASM_H
#define AM_REG_MACROS_ASM_H

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Critical section assembly macros
//
// These macros implement critical section protection using inline assembly
// for various compilers.  They are intended to be used in other register
// macros or directly in sections of code.
//
// Important usage note: These macros create a local scope and therefore MUST
// be used in pairs.
//
//*****************************************************************************

#if defined(__GNUC_STDC_INLINE__)
//
// GCC macros.
//
#define AM_CRITICAL_BEGIN_ASM                                               \
    if ( 1 )                                                                \
    {                                                                       \
        volatile uint32_t ui32Primask_04172010;                             \
        __asm("    mrs %0, PRIMASK" : "=r"(ui32Primask_04172010));          \
        __asm("    cpsid i");

#define AM_CRITICAL_END_ASM                                                 \
        __asm("    msr PRIMASK, %0" : : "r"(ui32Primask_04172010));         \
    }

#elif defined(__ARMCC_VERSION)
//
// ARM/Keil macros.
//
#define AM_CRITICAL_BEGIN_ASM                                               \
    if ( 1 )                                                                \
    {                                                                       \
        volatile uint32_t ui32Primask_04172010;                             \
        __asm                                                               \
        {                                                                   \
            mrs     ui32Primask_04172010, PRIMASK;                          \
            cpsid   i;                                                      \
        }

#define AM_CRITICAL_END_ASM                                                 \
        __asm                                                               \
        {                                                                   \
            msr     PRIMASK, ui32Primask_04172010;                          \
        }                                                                   \
    }

#elif defined(__IAR_SYSTEMS_ICC__)
//
// IAR macros.
//
#define AM_CRITICAL_BEGIN_ASM                                               \
    if ( 1 )                                                                \
    {                                                                       \
        volatile uint32_t ui32Primask_04172010;                             \
        __asm("    mrs %0, PRIMASK" : "=r"(ui32Primask_04172010));          \
        __asm("    cpsid i");

#define AM_CRITICAL_END_ASM                                                 \
        __asm("    msr PRIMASK, %0" : : "r"(ui32Primask_04172010));         \
    }
#endif


//*****************************************************************************
//
// A collection of some common inline assembly instructions / intrinsics.
//
//*****************************************************************************
//
// AM_ASM_BKPT(n)
//
#if     defined(__ARMCC_VERSION)
#define     AM_ASM_BKPT(n)  __breakpoint(n)
#elif   defined(__IAR_SYSTEMS_ICC__)
#define     AM_ASM_BKPT(n)  asm("    bkpt "#n);
#else
#define     AM_ASM_BKPT(n)  __asm("    bkpt "#n);
#endif

//
// AM_ASM_WFI
//
#if     defined(__ARMCC_VERSION)
#define     AM_ASM_WFI      __wfi();
#elif   defined(__IAR_SYSTEMS_ICC__)
#define     AM_ASM_WFI      asm("    wfi");
#else
#define     AM_ASM_WFI      __asm("    wfi");
#endif

//
// AM_ASM_NOP
//
#if     defined(__ARMCC_VERSION)
#define     AM_ASM_NOP      __nop();
#elif   defined(__IAR_SYSTEMS_ICC__)
#define     AM_ASM_NOP      asm("    nop");
#else
#define     AM_ASM_NOP      __asm("    nop");
#endif

#ifdef __cplusplus
}
#endif

#endif // AM_REG_MACROS_ASM_H

