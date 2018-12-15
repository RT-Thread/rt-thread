//*****************************************************************************
//
//  am_hal_otp.c
//! @file
//!
//! @brief Functions for handling the OTP interface.
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
#include "am_mcu_apollo.h"
#include "am_hal_flash.h"

//*****************************************************************************
//
//! THIS FUNCTION IS DEPRECATED!
//! Use the respective HAL flash function instead.
//!
// @brief Check if debugger is currently locked out.
//
// @param None.
//
// Determine if the debugger is already locked out.
//
// @return non-zero if debugger is currently locked out.
//     Specifically:
//     0 = debugger is not locked out.
//     1 = debugger is locked out.
//
//*****************************************************************************
int
am_hal_otp_is_debugger_lockedout(void)
{
    return am_hal_flash_debugger_disable_check();
}

//*****************************************************************************
//
//! THIS FUNCTION IS DEPRECATED!
//! Use the respective HAL flash function instead.
//!
// @brief Lock out debugger access.
//
// @param None.
//
// This function locks out access by a debugger.
//
// @return 0 if lockout was successful or if lockout was already enabled.
//
//*****************************************************************************
int
am_hal_otp_debugger_lockout(void)
{
    return am_hal_flash_debugger_disable();
}

//*****************************************************************************
//
//! THIS FUNCTION IS DEPRECATED!
//! Use the respective HAL flash function instead.
//!
// @brief Lock out SRAM access.
//
// @param None.
//
// This function locks out access by a debugger to SRAM.
//
// @return 0 if lockout was successful or if lockout was already enabled.
//         Low byte=0xff, byte 1 contains current value of lockout.
//         Else, return value from HAL programming function.
//
//*****************************************************************************
int
am_hal_otp_sram_lockout(void)
{
    return am_hal_flash_wipe_sram_enable();
}

//*****************************************************************************
//
//! THIS FUNCTION IS DEPRECATED!
//! Use the respective HAL flash function instead.
//!
// @brief Set copy (read) protection.
//
// @param @u32BegAddr The beginning address to be copy protected.
//        @u32EndAddr The ending address to be copy protected.
//
// @note For Apollo, the u32BegAddr parameter should be on a 16KB boundary, and
//       the u32EndAddr parameter should be on a (16KB-1) boundary. Otherwise
//       both parameters will be truncated/expanded to do so.
//       For example, if u32BegAddr=0x1000 and u32EndAddr=0xC200, the actual
//       range that protected is: 0x0 - 0xFFFF.
//
// This function enables copy protection on a given flash address range.
//
// @return 0 if copy protection was successfully enabled.
//
//*****************************************************************************
int
am_hal_otp_set_copy_protection(uint32_t u32BegAddr, uint32_t u32EndAddr)
{
    return am_hal_flash_copy_protect_set((uint32_t*)u32BegAddr,
                                         (uint32_t*)u32EndAddr);
}

//*****************************************************************************
//
//! THIS FUNCTION IS DEPRECATED!
//! Use the respective HAL flash function instead.
//!
// @brief Set write protection.
//
// @param @u32BegAddr The beginning address to be write protected.
//        @u32EndAddr The ending address to be write protected.
//
// @note For Apollo, the u32BegAddr parameter should be on a 16KB boundary, and
//       the u32EndAddr parameter should be on a (16KB-1) boundary. Otherwise
//       both parameters will be truncated/expanded to do so.
//       For example, if u32BegAddr=0x1000 and u32EndAddr=0xC200, the actual
//       range that protected is: 0x0 - 0xFFFF.
//
// This function enables write protection on a given flash address range.
//
// @return 0 if write protection was successfully enabled.
//
//*****************************************************************************
int
am_hal_otp_set_write_protection(uint32_t u32BegAddr, uint32_t u32EndAddr)
{
    return am_hal_flash_write_protect_set((uint32_t*)u32BegAddr,
                                          (uint32_t*)u32EndAddr);
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
