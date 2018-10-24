//*****************************************************************************
//
//! am_hal_sysctrl.h
//! @file
//!
//! @brief Functions for interfacing with the M4F system control registers
//!
//! @addtogroup sysctrl2 System Control (SYSCTRL)
//! @ingroup apollo2hal
//! @{
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
#ifndef AM_HAL_SYSCTRL_H
#define AM_HAL_SYSCTRL_H


//*****************************************************************************
//
// Definitions for sleep mode parameter
//
//*****************************************************************************
#define AM_HAL_SYSCTRL_SLEEP_DEEP       true
#define AM_HAL_SYSCTRL_SLEEP_NORMAL     false

//*****************************************************************************
//
// Parameters for am_hal_sysctrl_buck_ctimer_isr_init()
//
//*****************************************************************************
//
// Define the maximum valid timer number
//
#define BUCK_TIMER_MAX                  (AM_HAL_CTIMER_TIMERS_NUM - 1)

//
// Define the valid timer numbers
//
#define AM_HAL_SYSCTRL_BUCK_CTIMER_TIMER0   0
#define AM_HAL_SYSCTRL_BUCK_CTIMER_TIMER1   1
#define AM_HAL_SYSCTRL_BUCK_CTIMER_TIMER2   2
#define AM_HAL_SYSCTRL_BUCK_CTIMER_TIMER3   3

//
// The following is an invalid timer number. If used, it is the caller telling
// the HAL to use the "Hard Option", which applies a constant value to the zero
// cross. The applied value is more noise immune, if less energy efficent.
//
#define AM_HAL_SYSCTRL_BUCK_CTIMER_ZX_CONSTANT      0x01000000  // No timer, apply a constant value

#ifdef __cplusplus
extern "C"
{
#endif
//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern void     am_hal_sysctrl_sleep(bool bSleepDeep);
extern void     am_hal_sysctrl_fpu_enable(void);
extern void     am_hal_sysctrl_fpu_disable(void);
extern void     am_hal_sysctrl_fpu_stacking_enable(bool bLazy);
extern void     am_hal_sysctrl_fpu_stacking_disable(void);
extern void     am_hal_sysctrl_aircr_reset(void);

//
// Apollo2 zero-cross buck/ctimer related functions
//
extern uint32_t am_hal_sysctrl_buck_ctimer_isr_init(uint32_t ui32BuckTimerNumber);
extern bool     am_hal_sysctrl_buck_update_complete(void);

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_SYSCTRL_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************

