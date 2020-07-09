//*****************************************************************************
//
//  am_hal_otp.h
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
#ifndef AM_HAL_OTP_H
#define AM_HAL_OTP_H

//*****************************************************************************
//
// Define some OTP values and macros.
//
//*****************************************************************************
#define AM_HAL_OTP_SIG0             0x00
#define AM_HAL_OTP_SIG1             0x04
#define AM_HAL_OTP_SIG2             0x08
#define AM_HAL_OTP_SIG3             0x0C

#define AM_HAL_OTP_DBGR_O           0x10
#define AM_HAL_OTP_WRITPROT0_O      0x20
#define AM_HAL_OTP_WRITPROT1_O      0x24
#define AM_HAL_OTP_COPYPROT0_O      0x30
#define AM_HAL_OTP_COPYPROT1_O      0x34

#define AM_HAL_OTP_ADDR             0x50020000
#define AM_HAL_OTP_DBGRPROT_ADDR    (AM_HAL_OTP_ADDR + AM_HAL_OTP_DBGR_O)
#define AM_HAL_OTP_WRITPROT_ADDR    (AM_HAL_OTP_ADDR + AM_HAL_OTP_WRITPROT0_O)
#define AM_HAL_OTP_COPYPROT_ADDR    (AM_HAL_OTP_ADDR + AM_HAL_OTP_COPYPROT0_O)

#define AM_HAL_OTP_CHUNKSIZE        (16*1024)

//
// Debugger port lockout macros.
//
#define AM_OTP_DBGR_LOCKOUT_S       (0)
#define AM_OTP_DBGR_LOCKOUT_M       (0x1 << AM_OTP_DBGR_LOCKOUT_S)
#define AM_OTP_STRM_LOCKOUT_S       (1)
#define AM_OTP_STRM_LOCKOUT_M       (0x1 << AM_OTP_STRM_LOCKOUT_S)
#define AM_OTP_SRAM_LOCKOUT_S       (2)
#define AM_OTP_SRAM_LOCKOUT_M       (0x1 << AM_OTP_SRAM_LOCKOUT_S)

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Function prototypes
//
//*****************************************************************************
extern int am_hal_otp_is_debugger_lockedout(void);
extern int am_hal_otp_debugger_lockout(void);
extern int am_hal_otp_sram_lockout(void);
extern int am_hal_otp_set_copy_protection(uint32_t u32BegAddr, uint32_t u32EndAddr);
extern int am_hal_otp_set_write_protection(uint32_t u32BegAddr, uint32_t u32EndAddr);

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_OTP_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************

