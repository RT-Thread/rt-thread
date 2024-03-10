/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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

#include <assert.h>
#include "sdk_types.h"
#include "cpu_utility/cpu_utility.h"
#include "core/cortex_a9.h"
#include "registers/regssrc.h"

//////////////////////////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////////////////////////

//! @brief Maximum number of CPU cores supported by this code.
#define MAX_CORE_COUNT (4)

//! @brief Info about the CPU startup routine.
typedef struct _core_startup_info {
    cpu_entry_point_t entry;    //!< Function to call after starting a core.
    void * arg;                 //!< Argument to pass core entry point.
} core_startup_info_t;

////////////////////////////////////////////////////////////////////////////////
// Externs
////////////////////////////////////////////////////////////////////////////////

extern void _start(void);    // entry function, startup routine, defined in startup.s

//////////////////////////////////////////////////////////////////////////////////////////
// Variables
//////////////////////////////////////////////////////////////////////////////////////////

//! @brief Startup routine information for each CPU core.
static core_startup_info_t s_core_info[MAX_CORE_COUNT] = {{0}};

//////////////////////////////////////////////////////////////////////////////////////////
// Code
//////////////////////////////////////////////////////////////////////////////////////////

static void common_cpu_entry(void)
{
    uint32_t myCoreNumber = cpu_get_current();
    core_startup_info_t * info = &s_core_info[myCoreNumber];
    
    // Call the requested entry point for this CPU number.
    if (info->entry)
    {
        info->entry(info->arg);
    }
}

void cpu_start_secondary(uint8_t coreNumber, cpu_entry_point_t entryPoint, void * arg)
{
    int actualCores = cpu_get_cores();
    
    // Exit if the requested core is not available.
    if (coreNumber == 0 || coreNumber >= actualCores)
    {
        return;
    }
    
    // Save entry point and arg.
    assert(coreNumber < MAX_CORE_COUNT);
    s_core_info[coreNumber].entry = entryPoint;
    s_core_info[coreNumber].arg = arg;
    
    // Prepare pointers for ROM code. The entry point is always _start, which does some
    // basic preparatory work and then calls the common_cpu_entry function, which itself
    // calls the entry point saved in s_core_info.
    switch (coreNumber)
    {
#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
        case 1:
            HW_SRC_GPR3_WR((uint32_t) & _start);
            HW_SRC_GPR4_WR((uint32_t) common_cpu_entry);

            HW_SRC_SCR.B.CORE1_ENABLE = 1;
            break;

#if defined(CHIP_MX6DQ)
        case 2:
            HW_SRC_GPR5_WR((uint32_t) & _start);
            HW_SRC_GPR6_WR((uint32_t) common_cpu_entry);

            HW_SRC_SCR.B.CORE2_ENABLE = 1;
            break;
    
        case 3:
            HW_SRC_GPR7_WR((uint32_t) & _start);
            HW_SRC_GPR8_WR((uint32_t) common_cpu_entry);

            HW_SRC_SCR.B.CORE3_ENABLE = 1;
            break;
#endif // defined(CHIP_MX6DQ)
#endif // defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
    }
}

void cpu_disable(uint8_t coreNumber)
{
    int actualCores = cpu_get_cores();
    
    // Exit if the requested core is not available.
    if (coreNumber == 0 || coreNumber >= actualCores)
    {
        return;
    }
    
    switch (coreNumber)
    {
#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
        case 1:
            HW_SRC_SCR.B.CORE1_ENABLE = 0;
            break;

#if defined(CHIP_MX6DQ)
        case 2:
            HW_SRC_SCR.B.CORE2_ENABLE = 0;
            break;
    
        case 3:
            HW_SRC_SCR.B.CORE3_ENABLE = 0;
            break;
#endif // defined(CHIP_MX6DQ)
#endif // defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
// EOF
//////////////////////////////////////////////////////////////////////////////////////////
