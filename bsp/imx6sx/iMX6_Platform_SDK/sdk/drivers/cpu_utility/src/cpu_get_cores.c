/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "sdk.h"
#include "registers/regsocotp.h"
#include "cpu_utility/cpu_utility.h"


//////////////////////////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////////////////////////

//! @name Core number available OTP register constants 
//!{
#define CORE_NUM_MASK (0x0300000) //!< Number of cores available bit mask.
#define CORE_NUM_SHIFT (20)       //!< Number of cores available bit shift.
//@}

//! @name Number of cores constants in OTP register
//!
//! The same OTP bits are used for both MX6DQ and MX6SDL to determine the number
//! of available cores. But the default value of 0 has a different meaning for
//! the two chips.
//!{
#if defined(CHIP_MX6DQ)
#define FOUR_CORES (0)            //!< Four cores available register value.
#define TWO_CORES (2)             //!< Two cores available register value.
#elif defined(CHIP_MX6SDL)
#define TWO_CORES (0)             //!< Two cores available register value.
#define ONE_CORE (1)             //!< One cores available register value.
#endif
//@}

//////////////////////////////////////////////////////////////////////////////////////////
// Code
//////////////////////////////////////////////////////////////////////////////////////////

int cpu_get_cores(void)
{
    int core_count = GET_CORES_ERROR;             

#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
    // Mask and shift the contents of the control register so bit 21 and 20, which
    // are responsible for tracking cpu accessbility, are isolated.
    uint32_t raw_data = (HW_OCOTP_CFG2_RD() & CORE_NUM_MASK) >> CORE_NUM_SHIFT;
    
    // Determine whether there are 2 or 4 cores active and set the return
    // value accordingly. If no core is active, return error.
    switch(raw_data)
    {
// 4 cores only available on mx6dq
#if defined(CHIP_MX6DQ)
        case FOUR_CORES:
            core_count = FOUR_CORES_ACTIVE;
            break;
#endif // defined(CHIP_MX6DQ)
        case TWO_CORES:
            core_count = TWO_CORES_ACTIVE;
            break;
// 1 core only available on mx6sdl
#if defined(CHIP_MX6SDL)
        case ONE_CORE:
            core_count = ONE_CORE_ACTIVE;
            break;
#endif // defined(CHIP_MX6SDL)
        default:
            core_count = GET_CORES_ERROR;
    }
#elif defined(CHIP_MX6SL)
    // mx6sl only has one core
    core_count = ONE_CORE_ACTIVE;
#else
    #error Unknown cpu!
#endif

    return core_count;
}

//////////////////////////////////////////////////////////////////////////////////////////
// EOF
//////////////////////////////////////////////////////////////////////////////////////////
