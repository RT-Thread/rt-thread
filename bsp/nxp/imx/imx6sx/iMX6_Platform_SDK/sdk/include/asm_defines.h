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

/*!
 * @file asm_defines.h
 * @brief defines for startup assembly code
 *
 * @ingroup diag_util
 */

#ifndef _ASM_DEFINES_H_
#define _ASM_DEFINES_H_

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @name CPSR fields
//@{
#define CPSR_N (1 << 31)    //!< Negative
#define CPSR_Z (1 << 30)    //!< Zero
#define CPSR_C (1 << 29)    //!< Carry
#define CPSR_V (1 << 28)    //!< Overflow
#define CPSR_Q (1 << 27)    //!< Saturation
#define CPSR_E (1 << 9)     //!< Endianness
#define CPSR_A (1 << 8)     //!< Async abort mask
#define CPSR_I (1 << 7)     //!< IRQ mask
#define CPSR_F (1 << 6)     //!< FIQ mask
#define CPSR_T (1 << 5)     //!< Thumb mode
#define CPSR_MODE   (0x1f)  //!< Current processor mode
//@}

//! @name Mode bits in CPSR
//@{
#define MODE_USR     0x10   //!< User mode
#define MODE_FIQ     0x11   //!< FIQ mode
#define MODE_IRQ     0x12   //!< IRQ mode
#define MODE_SVC     0x13   //!< Supervisor mode
#define MODE_ABT     0x17   //!< Abort exception mode
#define MODE_UND     0x1B   //!< Undefined instruction exception mode
#define MODE_SYS     0x1F   //!< System mode
//@}

//! @name Interrupt enable bits in CPSR
//@{
#define I_BIT        0x80    //!< When I bit is set, IRQ is disabled
#define F_BIT        0x40    //!< When F bit is set, FIQ is disabled
//@}

//! @name Stack sizes
//@{

//! @brief Size of stacks for exceptions.
#define EXCEPTION_STACK_SIZE 2048

//! @brief Supervisor mode stack size.
//!
//! This stack is much larger because most application code runs in
//! Supervisor mode.
#define SVC_STACK_SIZE 8192

//@}

#endif /*_ASM_DEFINES_H_ */
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
