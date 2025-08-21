/**************************************************************************//**
 * @file     cmsis_gcc.h
 * @brief    CMSIS compiler specific macros, functions, instructions
 * @version  V1.0.0
 * @date     05. october 2021
 ******************************************************************************/
/*
 * Copyright (c) 2021 Arm Limited. All rights reserved.
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __CMSIS_GCC_H
#define __CMSIS_GCC_H

/* CMSIS compiler specific defines */
#ifndef   __ASM
  #define __ASM                                  __asm
#endif
#ifndef   __FORCEINLINE
  #define __FORCEINLINE                          __attribute__((always_inline))
#endif
#ifndef   __INLINE
  #define __INLINE                               inline
#endif
#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE                        static inline
#endif
#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#endif
#ifndef   __WEAK
  #define __WEAK                                 __attribute__((weak))
#endif

#ifndef __STRINGIFY
  #define __STRINGIFY(x)                         #x
#endif

#ifndef __MSR
  #define __MSR(sysreg, val) \
    __asm volatile ("msr "__STRINGIFY(sysreg)", %0\n" : : "r"((uint64_t)(val)))
#endif

#ifndef __MRS
#define __MRS(sysreg, pVal) \
  __asm volatile ("mrs  %0, "__STRINGIFY(sysreg)"\n" : "=r"((*pVal)))
#endif

#ifndef __WFI
#define __WFI() \
  __asm volatile ("wfi")
#endif


/* ###########################  Core Function Access  ########################### */
/** \ingroup  CMSIS_Core_FunctionInterface
    \defgroup CMSIS_Core_RegAccFunctions CMSIS Core Register Access Functions
  @{
 */


/**
  \brief   Get Interrupt Mask Bits
  \details Returns the current state of the interrupt mask bits from the DAIF register.
  \return  Interrupt Mask value
 */
__STATIC_FORCEINLINE uint64_t __get_DAIF(void)
{
    uint64_t result;
    __MRS(DAIF, &result);
    return result;
}


/**
  \brief   Enable IRQ Interrupts
  \details Enables IRQ interrupts by clearing the I-bit in the DAIF.
 */
__STATIC_FORCEINLINE void __enable_irq(void)
{
  __ASM volatile ("msr daifclr, #2" : : : "memory");
}


/**
  \brief   Disable IRQ Interrupts
  \details Disables IRQ interrupts by setting the I-bit in the DAIF.
 */
__STATIC_FORCEINLINE void __disable_irq(void)
{
  __ASM volatile ("msr daifset, #2" : : : "memory");
}


/*@} end of CMSIS_Core_RegAccFunctions */


/* ##########################  Core Instruction Access  ######################### */
/** \defgroup CMSIS_Core_InstructionInterface CMSIS Core Instruction Interface
  Access to dedicated instructions
  @{
*/

/**
  \brief   Hypervisor call with 2 arguments
  \details Makes an hypervisor call with two arguments stored in x0 and x1.
 */
#define HVC_2(imm, x0, x1) __asm volatile (                     \
				"mov x0, %0               \n\t" \
				"mov x1, %1               \n\t" \
				"hvc #" __STRINGIFY(imm) "\n\t" \
				 : : "r" (x0), "r" (x1) : "x0", "x1", "memory")

/**
  \brief   Multiprocessor Affinity
  \details Indicates the core number in the Cortex-Axx processor.
 */
__STATIC_FORCEINLINE uint64_t __get_MPIDR_EL1(void)
{
    uint64_t result;
    __MRS(MPIDR_EL1, &result);
    return result;
}

#define MPIDR_GetCoreID()                                                   \
        ({ uint64_t mpidr = __get_MPIDR_EL1();                              \
           (mpidr >> (8 * MPIDR_SUPPORT_MT(mpidr))) & MPIDR_AFFLVL_MASK; })

/**
  \brief   Instruction Synchronization Barrier
  \details Instruction Synchronization Barrier flushes the pipeline in the processor,
           so that all instructions following the ISB are fetched from cache or memory,
           after the instruction has been completed.
 */
#ifndef __ISB
__STATIC_FORCEINLINE void __ISB(void)
{
  __ASM volatile ("isb":::"memory");
}
#endif

/**
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
#ifndef __DSB
__STATIC_FORCEINLINE void __DSB(void)
{
  __ASM volatile ("dsb sy":::"memory");
}
#endif

/**
  \brief   Data Memory Barrier
  \details Ensures the apparent order of the explicit memory operations before
           and after the instruction, without ensuring their completion.
 */
#ifndef __DMB
__STATIC_FORCEINLINE void __DMB(void)
{
  __ASM volatile ("dmb sy":::"memory");
}
#endif

/**
  \brief   Reverse byte order (32 bit)
  \details Reverses the byte order in unsigned integer value. For example, 0x12345678 becomes 0x78563412.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__STATIC_FORCEINLINE uint32_t __REV(uint32_t value)
{
  return __builtin_bswap32(value);
}


/**
  \brief   Reverse byte order (16 bit)
  \details Reverses the byte order within each halfword of a word. For example, 0x12345678 becomes 0x34127856.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__STATIC_FORCEINLINE uint32_t __REV16(uint32_t value)
{
  return __builtin_bswap16(value);
}

/**
  \brief   Breakpoint
  \details Causes the processor to enter Debug state.
           Debug tools can use this to investigate system state when the instruction at a particular address is reached.
  \param [in]    value  is ignored by the processor.
                 If required, a debugger can use it to store additional information about the breakpoint.
 */
#define __BKPT(value)                       __ASM volatile ("brk "#value)

/**
  \brief   No Operation
  \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */

__STATIC_FORCEINLINE void __NOP(void)
{
  __ASM volatile ("nop");
}

/**
  \brief   Count leading zeros
  \details Counts the number of leading zeros of a data value.
  \param [in]  value  Value to count the leading zeros
  \return             number of leading zeros in value
 */
__STATIC_FORCEINLINE uint8_t __CLZ(uint32_t value)
{
  /* Even though __builtin_clz produces a CLZ instruction on ARM, formally
     __builtin_clz(0) is undefined behaviour, so handle this case specially.
     This guarantees ARM-compatible results if happening to compile on a non-ARM
     target, and ensures the compiler doesn't decide to activate any
     optimisations using the logic "value was passed to __builtin_clz, so it
     is non-zero".
     ARM GCC 7.3 and possibly earlier will optimise this test away, leaving a
     single CLZ instruction.
   */
  if (value == 0U)
  {
    return 32U;
  }
  return __builtin_clz(value);
}

/**
  \brief   likely/unlikely() branch prediction
  \details Gives hints to the compiler to favor either side of a jump instruction
  \param [in]  expr   Boolean expression under evaluation
  \return             The same boolean value
 */
#ifndef unlikely
__STATIC_FORCEINLINE long unlikely(long expr)
{
  return __builtin_expect(expr, 0L);
}
#endif

#ifndef likely
__STATIC_FORCEINLINE long likely(long expr)
{
  return __builtin_expect(expr, 1L);
}
#endif

/*@}*/ /* end of group CMSIS_Core_InstructionInterface */


#endif /* __CMSIS_GCC_H */
