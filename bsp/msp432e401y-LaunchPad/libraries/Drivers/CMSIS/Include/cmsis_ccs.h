//*****************************************************************************
//
// Copyright (C) 2012 - 2017 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  Redistributions of source code must retain the above copyright
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the
//  documentation and/or other materials provided with the
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// MSP432 Family CMSIS Definitions
//
//****************************************************************************

#ifndef CMSIS_CCS_H_
#define CMSIS_CCS_H_

#ifndef __TI_ARM__
    #error This file should only be compiled by TI compiler (minimum version 15.12.x)
#endif

/** CMSIS compiler control architecture macros */
#if defined ( __TI_ARM_V6M0__ )
    #define __ARM_ARCH_6M__                   1
#endif

#if defined ( __TI_ARM_V7M3__ )
    #define __ARM_ARCH_7M__                   1
#endif

#if defined ( __TI_ARM_V7M4__ )
    #define __ARM_ARCH_7EM__                  1
#endif

/* ###########################  Core Function Access  ########################### */
/** \ingroup  CMSIS_Core_FunctionInterface
 *  \defgroup CMSIS_Core_RegAccFunctions CMSIS Core Register Access Functions
 *  @{
 */

/**
 * \brief   Enable IRQ Interrupts
 * \details Enables IRQ interrupts by clearing the I-bit in the CPSR.
 *          Can only be executed in Privileged modes.
 */
#define __enable_irq                        _enable_IRQ

/**
 * \brief   Disable IRQ Interrupts
 * \details Disables IRQ interrupts by setting the I-bit in the CPSR.
 *          Can only be executed in Privileged modes.
 */
#define __disable_irq                       _disable_IRQ

/** @} */ /* end of CMSIS_Core_RegAccFunctions */

/* ##########################  Core Instruction Access  ######################### */
/** \defgroup CMSIS_Core_InstructionInterface CMSIS Core Instruction Interface
 *  Access to dedicated instructions
 *  @{
*/

/**
 * \brief   Count leading zeros
 * \details Counts the number of leading zeros of a data value.
 * \param [in]  VAL  Value to count the leading zeros
 * \return           number of leading zeros in value
 */
#define __CLZ(VAL)                          ((unsigned char)__clz(VAL))

/**
 * \brief   Signed Saturate
 * \details Saturates a signed value.
 * \param [in]  VAL      Value to be saturated
 * \param [in]  BITPOS   Bit position to saturate to (1..32)
 * \return               Saturated value
 */
#define __SSAT(VAL, BITPOS)                 _ssatl(VAL, 0, BITPOS)

/**
 * \brief   No Operation
 * \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
#define __NOP                               __nop

/**
 * \brief   Wait For Interrupt
 * \details Wait For Interrupt is a hint instruction that suspends execution until one of a number of events occurs.
 */
#define __WFI                               __wfi


/**
 * \brief   Wait For Event
 * \details Wait For Event is a hint instruction that permits the processor to enter
 *          a low-power state until one of a number of events occurs.
 */
#define __WFE                               __wfe

/**
 * \brief   Data Synchronization Barrier
 * \details Acts as a special kind of Data Memory Barrier.
 *          It completes when all explicit memory accesses before this instruction complete.
 */

#define __DSB                               _dsb
/**
 * \brief   Instruction Synchronization Barrier
 * \details Instruction Synchronization Barrier flushes the pipeline in the processor,
 *          so that all instructions following the ISB are fetched from cache or memory,
 *          after the instruction has been completed.
 */
#define __ISB                               _isb

/**
  \brief   Data Memory Barrier
  \details Ensures the apparent order of the explicit memory operations before
           and after the instruction, without ensuring their completion.
 */
#define __DMB                               _dmb
/**
 * \brief   Rotate Right in unsigned value (32 bit)
 * \details Rotate Right (immediate) provides the value of the contents of a register rotated by a variable number of bits.
 * \param [in]  VAL     Value to rotate
 * \param [in]  SHIFT   Number of Bits to rotate
 * \return              Rotated value
 */
#define __ROR(VAL, SHIFT)                   ((unsigned int)__ror(VAL, SHIFT))

/** @} */ /* end of group CMSIS_Core_InstructionInterface */

/* ###################  Compiler specific Intrinsics  ########################### */
/** \defgroup CMSIS_SIMD_intrinsics CMSIS SIMD Intrinsics
 *  Access to dedicated SIMD instructions
 *  @{
*/
#if (defined (__ARM_ARCH_7EM__) && (__ARM_ARCH_7EM__ == 1))

    #define __SADD8(VAL1, VAL2)                 ((unsigned int)_sadd8(VAL1, VAL2))
    #define __QADD8(VAL1, VAL2)                 ((unsigned int)_qadd8(VAL1, VAL2))
    #define __SHADD8(VAL1, VAL2)                ((unsigned int)_shadd8(VAL1, VAL2))
    #define __UADD8(VAL1, VAL2)                 ((unsigned int)_uadd8(VAL1, VAL2))
    #define __UQADD8(VAL1, VAL2)                ((unsigned int)_uqadd8(VAL1, VAL2))
    #define __UHADD8(VAL1, VAL2)                ((unsigned int)_uhadd8(VAL1, VAL2))
    #define __SSUB8(VAL1, VAL2)                 ((unsigned int)_ssub8(VAL1, VAL2))
    #define __QSUB8(VAL1, VAL2)                 ((unsigned int)_qsub8(VAL1, VAL2))
    #define __SHSUB8(VAL1, VAL2)                ((unsigned int)_shsub8(VAL1, VAL2))
    #define __USUB8(VAL1, VAL2)                 ((unsigned int)_usub8(VAL1, VAL2))
    #define __UQSUB8(VAL1, VAL2)                ((unsigned int)_uqsub8(VAL1, VAL2))
    #define __UHSUB8(VAL1, VAL2)                ((unsigned int)_uhsub8(VAL1, VAL2))
    #define __SADD16(VAL1, VAL2)                ((unsigned int)_sadd16(VAL1, VAL2))
    #define __QADD16(VAL1, VAL2)                ((unsigned int)_qadd16(VAL1, VAL2))
    #define __SHADD16(VAL1, VAL2)               ((unsigned int)_shadd16(VAL1, VAL2))
    #define __UADD16(VAL1, VAL2)                ((unsigned int)_uadd16(VAL1, VAL2))
    #define __UQADD16(VAL1, VAL2)               ((unsigned int)_uqadd16(VAL1, VAL2))
    #define __UHADD16(VAL1, VAL2)               ((unsigned int)_uhadd16(VAL1, VAL2))
    #define __SSUB16(VAL1, VAL2)                ((unsigned int)_ssub16(VAL1, VAL2))
    #define __QSUB16(VAL1, VAL2)                ((unsigned int)_qsub16(VAL1, VAL2))
    #define __SHSUB16(VAL1, VAL2)               ((unsigned int)_shsub16(VAL1, VAL2))
    #define __USUB16(VAL1, VAL2)                ((unsigned int)_usub16(VAL1, VAL2))
    #define __UQSUB16(VAL1, VAL2)               ((unsigned int)_uqsub16(VAL1, VAL2))
    #define __UHSUB16(VAL1, VAL2)               ((unsigned int)_uhsub16(VAL1, VAL2))
    #define __SASX(VAL1, VAL2)                  ((unsigned int)_saddsubx(VAL1, VAL2))
    #define __QASX(VAL1, VAL2)                  ((unsigned int)_qaddsubx(VAL1, VAL2))
    #define __SHASX(VAL1, VAL2)                 ((unsigned int)_shaddsubx(VAL1, VAL2))
    #define __UASX(VAL1, VAL2)                  ((unsigned int)_uaddsubx(VAL1, VAL2))
    #define __UQASX(VAL1, VAL2)                 ((unsigned int)_uqaddsubx(VAL1, VAL2))
    #define __UHASX(VAL1, VAL2)                 ((unsigned int)_uhaddsubx(VAL1, VAL2)))
    #define __SSAX(VAL1, VAL2)                  ((unsigned int)_ssubaddx(VAL1, VAL2))
    #define __QSAX(VAL1, VAL2)                  ((unsigned int)_qsubaddx(VAL1, VAL2))
    #define __SHSAX(VAL1, VAL2)                 ((unsigned int)_shsubaddx(VAL1, VAL2))
    #define __USAX(VAL1, VAL2)                  ((unsigned int)_usubaddx(VAL1, VAL2))
    #define __UQSAX(VAL1, VAL2)                 ((unsigned int)_uqsubaddx(VAL1, VAL2))
    #define __UHSAX(VAL1, VAL2)                 ((unsigned int)_uhsubaddx(VAL1, VAL2))
    #define __USAD8(VAL1, VAL2)                 ((unsigned int)_usad8(VAL1, VAL2))
    #define __USADA8(VAL1, VAL2, VAL3)          ((unsigned int)_usada8(VAL1, VAL2, VAL3))
    #define __SSAT16(VAL, BITPOS)               ((unsigned int)_ssat16(VAL, BITPOS))
    #define __USAT16(VAL, BITPOS)               ((unsigned int)_usat16(VAL, BITPOS))
    #define __UXTB16(VAL)                       ((unsigned int)_uxtb16(VAL, 0))
    #define __UXTAB16(VAL1, VAL2)               ((unsigned int)_uxtab16(VAL1, VAL2, 0))
    #define __SXTB16(VAL)                       ((unsigned int)_sxtb16(VAL, 0))
    #define __SXTAB16(VAL1, VAL2)               ((unsigned int)_sxtab16(VAL1, VAL2, 0))
    #define __SMUAD(VAL1, VAL2)                 ((unsigned int)_smuad(VAL1, VAL2))
    #define __SMUADX(VAL1, VAL2)                ((unsigned int)_smuadx(VAL1, VAL2))
    #define __SMLAD(VAL1, VAL2, ACCUMULATOR)    ((unsigned int)_smlad(VAL1, VAL2, ACCUMULATOR))
    #define __SMLADX(VAL1, VAL2, ACCUMULATOR)   ((unsigned int)_smladx(VAL1, VAL2, ACCUMULATOR))
    #define __SMLALD(VAL1, VAL2, ACCUMULATOR)   ((unsigned long long)_smlald(ACCUMULATOR, VAL1, VAL2))
    #define __SMLALDX(VAL1, VAL2, ACCUMULATOR)  ((unsigned long long)_smlaldx(ACCUMULATOR, VAL1, VAL2))
    #define __SMUSD(VAL1, VAL2)                 ((unsigned int)_smusd(VAL1, VAL2))
    #define __SMUSDX(VAL1, VAL2)                ((unsigned int)_smusdx(VAL1, VAL2))
    #define __SMLSD(VAL1, VAL2, ACCUMULATOR)    ((unsigned int)_smlsd(VAL1, VAL2, ACCUMULATOR))
    #define __SMLSDX(VAL1, VAL2, ACCUMULATOR)   ((unsigned int)_smlsdx(VAL1, VAL2, ACCUMULATOR))
    #define __SMLSLD(VAL1, VAL2, ACCUMULATOR)   ((unsigned long long)_smlsld(ACCUMULATOR, VAL1, VAL2))
    #define __SMLSLDX(VAL1, VAL2, ACCUMULATOR)  ((unsigned long long)_smlsldx(ACCUMULATOR, VAL1, VAL2))
    #define __SEL(VAL1, VAL2)                   ((unsigned int)_sel(VAL1, VAL2))
    #define __QADD                              _sadd
    #define __QSUB                              _ssub
    #define __PKHBT                             _pkhbt
    #define __PKHTB                             _pkhtb
    #define __SMMLA                             _smmla

    #define __QDADD                             _sdadd
    #define __QDSUB                             _sdsub
    #define __SMLABB                            _smlabb
    #define __SMLABT                            _smlabt
    #define __SMLALBB                           _smlalbb
    #define __SMLALBT                           _smlalbt
    #define __SMLALTB                           _smlaltb
    #define __SMLALTT                           _smlaltt
    #define __SMLATB                            _smlatb
    #define __SMLATT                            _smlatt
    #define __SMLAWB                            _smlawb
    #define __SMLAWT                            _smlawt
    #define __SMULBB                            _smulbb
    #define __SMULBT                            _smulbt
    #define __SMULTB                            _smultb
    #define __SMULTT                            _smultt
    #define __SMULWB                            _smulwb
    #define __SMULWT                            _smulwt
    #define __SMMLAR                            _smmlar
    #define __SMMLS                             _smmls
    #define __SMMLSR                            _smmlsr
    #define __SMMUL                             _smmul
    #define __SMMULR                            _smmulr
    #define __SXTAB                             _sxtab
    #define __SXTAH                             _sxtah
    #define __UMAAL                             _umaal
    #define __UXTAB                             _uxtab
    #define __UXTAH                             _uxtah
    #define __SUBC                              _subc

#endif /* (defined (__ARM_ARCH_7EM__) && (__ARM_ARCH_7EM__ == 1)) */

#if (defined (__ARM_ARCH_6M__) && (__ARM_ARCH_6M__ == 1))

    #define __SXTB                              _sxtb
    #define __SXTH                              _sxth
    #define __UXTB                              _uxtb
    #define __UXTH                              _uxth

#endif /* (defined (__ARM_ARCH_6M__) && (__ARM_ARCH_6M__ == 1)) */

/** @} */ /* end of group CMSIS_SIMD_intrinsics */

#endif /* CMSIS_CCS_H_ */
