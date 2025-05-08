/**************************************************************************//**
 * @file     cmsis_cp15.h
 * @brief    CMSIS compiler specific macros, functions, instructions
 * @date     02. February 2024
 ******************************************************************************/
/*
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates. All Rights Reserved.
 *
 * This file is based on the "CMSIS\Core_A\Include\cmsis_cp15.h"
 *
 * Changes:
 * Renesas Electronics Corporation on 2021-08-31
 *    - Changed to be related to Cortex-R52 by
 * Renesas Electronics Corporation on 2024-02-02
 *    - Functions are sorted according to the Arm technical reference.
 *    - Added some functions to convert BSP into C language.
 */
/*
 * Copyright (c) 2009-2017 ARM Limited. All rights reserved.
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

#if   defined ( __ICCARM__ )
  #pragma system_include         /* treat file as system include file for MISRA check */
#elif defined (__clang__)
  #pragma clang system_header   /* treat file as system include file */
#endif

#ifndef __CMSIS_CP15_H
#define __CMSIS_CP15_H

/** \brief  Get CTR
    \return               Cache Type Register value
 */
__STATIC_FORCEINLINE uint32_t __get_CTR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 0, 0, 1);
  return result;
}

/** \brief  Get MPIDR

    This function returns the value of the Multiprocessor Affinity Register.

    \return               Multiprocessor Affinity Register value
 */
__STATIC_FORCEINLINE uint32_t __get_MPIDR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 0, 0, 5);
  return result;
}

/** \brief  Get CCSIDR
    \return CCSIDR Register value
 */
__STATIC_FORCEINLINE uint32_t __get_CCSIDR(void)
{
  uint32_t result;
  __get_CP(15, 1, result, 0, 0, 0);
  return result;
}

/** \brief  Get CLIDR
    \return CLIDR Register value
 */
__STATIC_FORCEINLINE uint32_t __get_CLIDR(void)
{
  uint32_t result;
  __get_CP(15, 1, result, 0, 0, 1);
  return result;
}

/** \brief  Get CSSELR
    \return CSSELR Register value
 */
__STATIC_FORCEINLINE uint32_t __get_CSSELR(void)
{
  uint32_t result;
  __get_CP(15, 2, result, 0, 0, 0);
  return result;
}

/** \brief  Set CSSELR
 */
__STATIC_FORCEINLINE void __set_CSSELR(uint32_t value)
{
  __set_CP(15, 2, value, 0, 0, 0);
}

/** \brief  Get SCTLR

    This function assigns the given value to the System Control Register.

    \return               System Control Register value
 */
__STATIC_FORCEINLINE uint32_t __get_SCTLR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 1, 0, 0);
  return result;
}

/** \brief  Set SCTLR
    \param [in]    value  System Control Register value to set
 */
__STATIC_FORCEINLINE void __set_SCTLR(uint32_t value)
{
  __set_CP(15, 0, value, 1, 0, 0);
}


/** \brief  Get ACTLR
    \return               Auxiliary Control register value
 */
__STATIC_FORCEINLINE uint32_t __get_ACTLR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 1, 0, 1);
  return(result);
}

/** \brief  Set ACTLR
    \param [in]    value  Auxiliary Control value to set
 */
__STATIC_FORCEINLINE void __set_ACTLR(uint32_t value)
{
  __set_CP(15, 0, value, 1, 0, 1);
}

/** \brief  Get CPACR
    \return               Coprocessor Access Control register value
 */
__STATIC_FORCEINLINE uint32_t __get_CPACR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 1, 0, 2);
  return result;
}

/** \brief  Set CPACR
    \param [in]    value  Coprocessor Access Control value to set
 */
__STATIC_FORCEINLINE void __set_CPACR(uint32_t value)
{
  __set_CP(15, 0, value, 1, 0, 2);
}

/** \brief  Get TTBR0

    This function returns the value of the Translation Table Base Register 0.

    \return               Translation Table Base Register 0 value
 */
__STATIC_FORCEINLINE uint32_t __get_TTBR0(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 2, 0, 0);
  return result;
}

/** \brief  Set TTBR0

    This function assigns the given value to the Translation Table Base Register 0.

    \param [in]    value  Translation Table Base Register 0 value to set
 */
__STATIC_FORCEINLINE void __set_TTBR0(uint32_t value)
{
  __set_CP(15, 0, value, 2, 0, 0);
}

/** \brief  Get DACR

    This function returns the value of the Domain Access Control Register.

    \return               Domain Access Control Register value
 */
__STATIC_FORCEINLINE uint32_t __get_DACR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 3, 0, 0);
  return result;
}

/** \brief  Set DACR

    This function assigns the given value to the Domain Access Control Register.

    \param [in]    value   Domain Access Control Register value to set
 */
__STATIC_FORCEINLINE void __set_DACR(uint32_t value)
{
  __set_CP(15, 0, value, 3, 0, 0);
}

/** \brief  Get ICC_PMR
 */
__STATIC_FORCEINLINE uint32_t __get_ICC_PMR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 4, 6, 0);
  return result;
}

/** \brief  Set ICC_PMR
 */
__STATIC_FORCEINLINE void __set_ICC_PMR(uint32_t value)
{
  __set_CP(15, 0, value, 4, 6, 0);
}

/** \brief  Get DFSR
    \return               Data Fault Status Register value
 */
__STATIC_FORCEINLINE uint32_t __get_DFSR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 5, 0, 0);
  return result;
}

/** \brief  Set DFSR
    \param [in]    value  Data Fault Status value to set
 */
__STATIC_FORCEINLINE void __set_DFSR(uint32_t value)
{
  __set_CP(15, 0, value, 5, 0, 0);
}

/** \brief  Get IFSR
    \return               Instruction Fault Status Register value
 */
__STATIC_FORCEINLINE uint32_t __get_IFSR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 5, 0, 1);
  return result;
}

/** \brief  Set IFSR
    \param [in]    value  Instruction Fault Status value to set
 */
__STATIC_FORCEINLINE void __set_IFSR(uint32_t value)
{
  __set_CP(15, 0, value, 5, 0, 1);
}

/** \brief  Set PRSELR

    This function assigns the given value to the Protection Region Selection Register.

    \param [in]    value  Protection Region Selection Register to set
 */
__STATIC_FORCEINLINE void __set_PRSELR(uint32_t value)
{
  __set_CP(15, 0, value, 6, 2, 1);
}

/** \brief  Get PRBAR

    This function returns the value of the Protection Region Base Address Register.

    \return               Protection Region Base Address Register
 */
__STATIC_FORCEINLINE uint32_t __get_PRBAR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 6, 3, 0);
  return result;
}

/** \brief  Set PRBAR

    This function assigns the given value to the Protection Region Base Address Register.

    \param [in]    value  Protection Region Base Address Register to set
 */
__STATIC_FORCEINLINE void __set_PRBAR(uint32_t value)
{
  __set_CP(15, 0, value, 6, 3, 0);
}

/** \brief  Get PRLAR

    This function returns the value of the Protection Region Limit Address Register.

    \return               Protection Region Limit Address Register
 */
__STATIC_FORCEINLINE uint32_t __get_PRLAR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 6, 3, 1);
  return result;
}

/** \brief  Set PRLAR

    This function assigns the given value to the Protection Region Limit Address Register.

    \param [in]    value  Protection Region Limit Address Register to set
 */
__STATIC_FORCEINLINE void __set_PRLAR(uint32_t value)
{
  __set_CP(15, 0, value, 6, 3, 1);
}

/** \brief  Set ICIALLU

  Instruction Cache Invalidate All
 */
__STATIC_FORCEINLINE void __set_ICIALLU(uint32_t value)
{
  __set_CP(15, 0, value, 7, 5, 0);
}

/** \brief  Set ICIVAU
 */
__STATIC_FORCEINLINE void __set_ICIVAU(uint32_t value)
{
  __set_CP(15, 0, value, 7, 5, 1);
}

/** \brief  Set BPIALL.

  Branch Predictor Invalidate All
 */
__STATIC_FORCEINLINE void __set_BPIALL(uint32_t value)
{
  __set_CP(15, 0, value, 7, 5, 6);
}

/** \brief  Set DCIMVAC

  Data cache invalidate
 */
__STATIC_FORCEINLINE void __set_DCIMVAC(uint32_t value)
{
  __set_CP(15, 0, value, 7, 6, 1);
}

/** \brief  Set DCIVAC
 */
__STATIC_FORCEINLINE void __set_DCIVAC(uint32_t value)
{
  __set_CP(15, 0, value, 7, 6, 1);
}

/** \brief  Set DCISW
 */
__STATIC_FORCEINLINE void __set_DCISW(uint32_t value)
{
  __set_CP(15, 0, value, 7, 6, 2);
}

/** \brief  Set DCCMVAC

  Data cache clean
 */
__STATIC_FORCEINLINE void __set_DCCMVAC(uint32_t value)
{
  __set_CP(15, 0, value, 7, 10, 1);
}

/** \brief  Set DCCVAC
 */
__STATIC_FORCEINLINE void __set_DCCVAC(uint32_t value)
{
  __set_CP(15, 0, value, 7, 10, 1);
}

/** \brief  Set DCCSW
 */
__STATIC_FORCEINLINE void __set_DCCSW(uint32_t value)
{
  __set_CP(15, 0, value, 7, 10, 2);
}

/** \brief  Set DCCIMVAC

  Data cache clean and invalidate
 */
__STATIC_FORCEINLINE void __set_DCCIMVAC(uint32_t value)
{
  __set_CP(15, 0, value, 7, 14, 1);
}

/** \brief  Set DCCIVAC
 */
__STATIC_FORCEINLINE void __set_DCCIVAC(uint32_t value)
{
  __set_CP(15, 0, value, 7, 14, 1);
}

/** \brief  Set DCCISW
 */
__STATIC_FORCEINLINE void __set_DCCISW(uint32_t value)
{
  __set_CP(15, 0, value, 7, 14, 2);
}

/** \brief  Set TLBIALL

  TLB Invalidate All
 */
__STATIC_FORCEINLINE void __set_TLBIALL(uint32_t value)
{
  __set_CP(15, 0, value, 8, 7, 0);
}

/** \brief  Set MAIR0

    This function assigns the given value to the Memory Attribute Indirection Registers 0.

    \param [in]    value  Memory Attribute Indirection Registers 0 to set
 */
__STATIC_FORCEINLINE void __set_MAIR0(uint32_t value)
{
  __set_CP(15, 0, value, 10, 2, 0);
}

/** \brief  Set MAIR1

    This function assigns the given value to the Memory Attribute Indirection Registers 1.

    \param [in]    value  Memory Attribute Indirection Registers 1 to set
 */
__STATIC_FORCEINLINE void __set_MAIR1(uint32_t value)
{
  __set_CP(15, 0, value, 10, 2, 1);
}

/** \brief  Get IMP_SLAVEPCTLR

    This function returns the value of the Slave Port Control Register.

    \return                 Slave Port Control Register
 */
__STATIC_FORCEINLINE uint32_t __get_IMP_SLAVEPCTLR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 11, 0, 0);
  return result;
}

/** \brief  Set IMP_SLAVEPCTLR

    This function assigns the given value to the Slave Port Control Register.

    \param [in]    value    Slave Port Control Register value to set
 */
__STATIC_FORCEINLINE void __set_IMP_SLAVEPCTLR(uint32_t value)
{
  __set_CP(15, 0, value, 11, 0, 0);
}

/** \brief  Get VBAR

    This function returns the value of the Vector Base Address Register.

    \return               Vector Base Address Register
 */
__STATIC_FORCEINLINE uint32_t __get_VBAR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 12, 0, 0);
  return result;
}

/** \brief  Set VBAR

    This function assigns the given value to the Vector Base Address Register.

    \param [in]    value  Vector Base Address Register value to set
 */
__STATIC_FORCEINLINE void __set_VBAR(uint32_t value)
{
  __set_CP(15, 0, value, 12, 0, 0);
}

/** \brief  Get MVBAR

    This function returns the value of the Monitor Vector Base Address Register.

    \return               Monitor Vector Base Address Register
 */
__STATIC_FORCEINLINE uint32_t __get_MVBAR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 12, 0, 1);
  return result;
}

/** \brief  Set MVBAR

    This function assigns the given value to the Monitor Vector Base Address Register.

    \param [in]    value  Monitor Vector Base Address Register value to set
 */
__STATIC_FORCEINLINE void __set_MVBAR(uint32_t value)
{
  __set_CP(15, 0, value, 12, 0, 1);
}

/** \brief  Get ISR
    \return               Interrupt Status Register value
 */
__STATIC_FORCEINLINE uint32_t __get_ISR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 12, 1, 0);
  return result;
}

/** \brief  Get ICC_RPR
 */
__STATIC_FORCEINLINE uint32_t __get_ICC_RPR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 12, 11, 3);
  return result;
}

/** \brief  Get ICC_IAR1
 */
__STATIC_FORCEINLINE uint32_t __get_ICC_IAR1(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 12, 12, 0);
  return result;
}

/** \brief  Set ICC_EOIR1
 */
__STATIC_FORCEINLINE void __set_ICC_EOIR1(uint32_t value)
{
  __set_CP(15, 0, value, 12, 12, 0);
}

/** \brief  Get ICC_HPPIR1
 */
__STATIC_FORCEINLINE uint32_t __get_ICC_HPPIR1(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 12, 12, 2);
  return result;
}

/** \brief  Get ICC_BPR1
 */
__STATIC_FORCEINLINE uint32_t __get_ICC_BPR1(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 12, 12, 3);
  return result;
}

/** \brief  Set ICC_BPR1
 */
__STATIC_FORCEINLINE void __set_ICC_BPR1(uint32_t value)
{
  __set_CP(15, 0, value, 12, 12, 3);
}

/** \brief  Get ICC_CTLR
 */
__STATIC_FORCEINLINE uint32_t __get_ICC_CTLR(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 12, 12, 4);
  return result;
}

/** \brief  Set ICC_CTLR
 */
__STATIC_FORCEINLINE void __set_ICC_CTLR(uint32_t value)
{
  __set_CP(15, 0, value, 12, 12, 4);
}

/** \brief  Set ICC_IGRPEN1
 */
__STATIC_FORCEINLINE void __set_ICC_IGRPEN1(uint32_t value)
{
  __set_CP(15, 0, value, 12, 12, 7);
}

/** \brief  Set CNTFRQ

  This function assigns the given value to PL1 Physical Timer Counter Frequency Register (CNTFRQ).

  \param [in]    value  CNTFRQ Register value to set
*/
__STATIC_FORCEINLINE void __set_CNTFRQ(uint32_t value)
{
  __set_CP(15, 0, value, 14, 0, 0);
}

/** \brief  Get CNTFRQ

    This function returns the value of the PL1 Physical Timer Counter Frequency Register (CNTFRQ).

    \return               CNTFRQ Register value
 */
__STATIC_FORCEINLINE uint32_t __get_CNTFRQ(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 14, 0, 0);
  return result;
}

/** \brief  Set CNTKCTL

  This function assigns the given value to Counter-timer Kernel Control Register (CNTKCTL).

  \param [in]    value  CNTKCTL Register value to set
*/
__STATIC_FORCEINLINE void __set_CNTKCTL(uint32_t value)
{
  __set_CP(15, 0, value, 14, 1, 0);
}

/** \brief  Get CNTKCTL

    This function returns the value of the Counter-timer kernel Control Register (CNTKCTL).

    \return               CNTFRQ Register value
 */
__STATIC_FORCEINLINE uint32_t __get_CNTKCTL(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 14, 1, 0);
  return result;
}

/** \brief  Set CNTP_TVAL

  This function assigns the given value to PL1 Physical Timer Value Register (CNTP_TVAL).

  \param [in]    value  CNTP_TVAL Register value to set
*/
__STATIC_FORCEINLINE void __set_CNTP_TVAL(uint32_t value)
{
  __set_CP(15, 0, value, 14, 2, 0);
}

/** \brief  Get CNTP_TVAL

    This function returns the value of the PL1 Physical Timer Value Register (CNTP_TVAL).

    \return               CNTP_TVAL Register value
 */
__STATIC_FORCEINLINE uint32_t __get_CNTP_TVAL(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 14, 2, 0);
  return result;
}

/** \brief  Set CNTP_CTL

  This function assigns the given value to PL1 Physical Timer Control Register (CNTP_CTL).

  \param [in]    value  CNTP_CTL Register value to set
*/
__STATIC_FORCEINLINE void __set_CNTP_CTL(uint32_t value)
{
  __set_CP(15, 0, value, 14, 2, 1);
}

/** \brief  Get CNTP_CTL register
    \return               CNTP_CTL Register value
 */
__STATIC_FORCEINLINE uint32_t __get_CNTP_CTL(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 14, 2, 1);
  return result;
}

/** \brief  Set CNTV_CTL

  This function assigns the given value to PL1 Virtual Timer Control Register (CNTV_CTL).

  \param [in]    value  CNTV_CTL Register value to set
*/
__STATIC_FORCEINLINE void __set_CNTV_CTL(uint32_t value)
{
  __set_CP(15, 0, value, 14, 3, 1);
}

/** \brief  Get CNTV_CTL register
    \return               CNTV_CTL Register value
 */
__STATIC_FORCEINLINE uint32_t __get_CNTV_CTL(void)
{
  uint32_t result;
  __get_CP(15, 0, result, 14, 3, 1);
  return result;
}

/** \brief  Get CBAR
    \return               Configuration Base Address register value
 */
__STATIC_FORCEINLINE uint32_t __get_CBAR(void)
{
  uint32_t result;
  __get_CP(15, 4, result, 15, 0, 0);
  return result;
}

/** \brief  Get CNTPCT

    This function returns the value of the 64 bits PL1 Physical Count Register (CNTPCT).

    \return               CNTPCT Register value
 */
__STATIC_FORCEINLINE uint64_t __get_CNTPCT(void)
{
  uint64_t result;
  __get_CP64(15, 0, result, 14);
  return result;
}

/** \brief  Set ICC_SGI1R
 */
__STATIC_FORCEINLINE void __set_ICC_SGI1R(uint64_t value)
{
  __set_CP64(15, 0, value, 12);
}

/** \brief  Get CNTVCT

    This function returns the value of the 64 bits PL1 Virtual Count Register (CNTVCT).

    \return               CNTVCT Register value
 */
__STATIC_FORCEINLINE uint64_t __get_CNTVCT(void)
{
  uint64_t result;
  __get_CP64(15, 1, result, 14);
  return result;
}

/** \brief  Set CNTP_CVAL

  This function assigns the given value to 64bits PL1 Physical Timer CompareValue Register (CNTP_CVAL).

  \param [in]    value  CNTP_CVAL Register value to set
*/
__STATIC_FORCEINLINE void __set_CNTP_CVAL(uint64_t value)
{
  __set_CP64(15, 2, value, 14);
}

/** \brief  Get CNTP_CVAL

    This function returns the value of the 64 bits PL1 Physical Timer CompareValue Register (CNTP_CVAL).

    \return               CNTP_CVAL Register value
 */
__STATIC_FORCEINLINE uint64_t __get_CNTP_CVAL(void)
{
  uint64_t result;
  __get_CP64(15, 2, result, 14);
  return result;
}

#endif
