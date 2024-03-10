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

//! @addtogroup cortexa9
//! @{

/*!
 * @file  arm_cp_registers.h
 * @brief Definitions for ARM coprocessor registers.
 */

#ifndef __ARM_CP_REGISTERS_H__
#define __ARM_CP_REGISTERS_H__

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @name ACTLR
//@{
#define BM_ACTLR_SMP (1 << 6)
//@}

//! @name DFSR
//@{
#define BM_DFSR_WNR (1 << 11)   //!< Write not Read bit. 0=read, 1=write.
#define BM_DFSR_FS4 (0x400)      //!< Fault status bit 4..
#define BP_DFSR_FS4 (10)        //!< Bit position for FS[4].
#define BM_DFSR_FS (0xf)      //!< Fault status bits [3:0].
//@}

//! @name SCTLR
//@{
#define BM_SCTLR_TE (1 << 30)  //!< Thumb exception enable.
#define BM_SCTLR_AFE (1 << 29) //!< Access flag enable.
#define BM_SCTLR_TRE (1 << 28) //!< TEX remap enable.
#define BM_SCTLR_NMFI (1 << 27)    //!< Non-maskable FIQ support.
#define BM_SCTLR_EE (1 << 25)  //!< Exception endianess.
#define BM_SCTLR_VE (1 << 24)  //!< Interrupt vectors enable.
#define BM_SCTLR_FI (1 << 21)   //!< Fast interrupt configurable enable.
#define BM_SCTLR_RR (1 << 14)  //!< Round Robin
#define BM_SCTLR_V (1 << 13)   //!< Vectors
#define BM_SCTLR_I (1 << 12)   //!< Instruction cache enable
#define BM_SCTLR_Z (1 << 11)   //!< Branch prediction enable
#define BM_SCTLR_SW (1 << 10)  //!< SWP and SWPB enable
#define BM_SCTLR_CP15BEN (1 << 5)  //!< CP15 barrier enable
#define BM_SCTLR_C (1 << 2)    //!< Data cache enable
#define BM_SCTLR_A (1 << 1)    //!< Alignment check enable
#define BM_SCTLR_M (1 << 0)    //!< MMU enable
//@}

//! @}

#endif // __ARM_CP_REGISTERS_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

