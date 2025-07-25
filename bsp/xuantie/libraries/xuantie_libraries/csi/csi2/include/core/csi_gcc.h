 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     csi_gcc.h
 * @brief    CSI Header File for GCC.
 * @version  V1.0
 * @date     02. June 2020
 ******************************************************************************/

#ifndef _CSI_GCC_H_
#define _CSI_GCC_H_

#include <stdlib.h>
#include <stdint.h>

#ifndef __ASM
#define __ASM                   __asm    /*!< asm keyword for GNU Compiler */
#endif

#ifndef __INLINE
#define __INLINE                inline   /*!< inline keyword for GNU Compiler */
#endif

#ifndef __ALWAYS_STATIC_INLINE
#define __ALWAYS_STATIC_INLINE  __attribute__((always_inline)) static inline
#endif

#ifndef __STATIC_INLINE
#define __STATIC_INLINE         static inline
#endif

#ifndef __NO_RETURN
#define __NO_RETURN             __attribute__((__noreturn__))
#endif

#ifndef __USED
#define __USED                  __attribute__((used))
#endif

#ifndef __WEAK
#define __WEAK                  __attribute__((weak))
#endif

#ifndef __PACKED
#define __PACKED                __attribute__((packed, aligned(1)))
#endif

#ifndef __PACKED_STRUCT
#define __PACKED_STRUCT         struct __attribute__((packed, aligned(1)))
#endif

#ifndef __PACKED_UNION
#define __PACKED_UNION          union __attribute__((packed, aligned(1)))
#endif


/* ###########################  Core Function Access  ########################### */
/** \ingroup  CSI_Core_FunctionInterface
    \defgroup CSI_Core_RegAccFunctions CSI Core Register Access Functions
  @{
 */
/**
  \brief   Enable IRQ Interrupts
  \details Enables IRQ interrupts by setting the IE-bit in the PSR.
           Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __enable_irq(void)
{
    __ASM volatile("psrset ie");
}



/**
  \brief   Disable IRQ Interrupts
  \details Disables IRQ interrupts by clearing the IE-bit in the PSR.
  Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __disable_irq(void)
{
    __ASM volatile("psrclr ie");
}

/**
  \brief   Get PSR
  \details Returns the content of the PSR Register.
  \return               PSR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_PSR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, psr" : "=r"(result) :: "memory");
    return (result);
}

/**
  \brief   Set PSR
  \details Writes the given value to the PSR Register.
  \param [in]    psr  PSR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_PSR(uint32_t psr)
{
    __ASM volatile("mtcr %0, psr" : : "r"(psr) : "memory");
}

/**
  \brief   Get SP
  \details Returns the content of the SP Register.
  \return               SP Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_SP(void)
{
    uint32_t result;

    __ASM volatile("mov %0, sp" : "=r"(result));
    return (result);
}

/**
  \brief   Set SP
  \details Writes the given value to the SP Register.
  \param [in]    sp  SP Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SP(uint32_t sp)
{
    __ASM volatile("mov sp, %0" : : "r"(sp): "sp");
}

/**
  \brief   Get Int SP
  \details Returns the content of the Int SP Register.
  \return               Int SP Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_Int_SP(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<15, 1>" : "=r"(result));
    return (result);
}

/**
  \brief   Set Int SP
  \details Writes the given value to the Int SP Register.
  \param [in]    sp  Int SP Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_Int_SP(uint32_t sp)
{
    __ASM volatile("mtcr %0, cr<15, 1>" : : "r"(sp));
}

/**
  \brief   Get VBR Register
  \details Returns the content of the VBR Register.
  \return               VBR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_VBR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, vbr" : "=r"(result));
    return (result);
}

/**
  \brief   Set VBR
  \details Writes the given value to the VBR Register.
  \param [in]    vbr  VBR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_VBR(uint32_t vbr)
{
    __ASM volatile("mtcr %0, vbr" : : "r"(vbr));
}

/**
  \brief   Get EPC Register
  \details Returns the content of the EPC Register.
  \return               EPC Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_EPC(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, epc" : "=r"(result));
    return (result);
}

/**
  \brief   Set EPC
  \details Writes the given value to the EPC Register.
  \param [in]    epc  EPC Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_EPC(uint32_t epc)
{
    __ASM volatile("mtcr %0, epc" : : "r"(epc));
}

/**
  \brief   Get EPSR
  \details Returns the content of the EPSR Register.
  \return               EPSR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_EPSR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, epsr" : "=r"(result));
    return (result);
}

/**
  \brief   Set EPSR
  \details Writes the given value to the EPSR Register.
  \param [in]    epsr  EPSR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_EPSR(uint32_t epsr)
{
    __ASM volatile("mtcr %0, epsr" : : "r"(epsr));
}

/**
  \brief   Get CPUID Register
  \details Returns the content of the CPUID Register.
  \return               CPUID Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_CPUID(void)
{
    uint32_t result;

#ifdef __CK610
    __ASM volatile("mfcr %0, cr13" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<13, 0>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Get CCR
  \details Returns the current value of the CCR.
  \return               CCR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_CCR(void)
{
    register uint32_t result;

#ifdef __CK610
    __ASM volatile("mfcr %0, cr18\n"  : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<18, 0>\n"  : "=r"(result));
#endif
    return (result);
}


/**
  \brief   Set CCR
  \details Assigns the given value to the CCR.
  \param [in]    ccr  CCR value to set
 */
__ALWAYS_STATIC_INLINE void __set_CCR(uint32_t ccr)
{
#ifdef __CK610
    __ASM volatile("mtcr %0, cr18\n" : : "r"(ccr));
#else
    __ASM volatile("mtcr %0, cr<18, 0>\n" : : "r"(ccr));
#endif
}

/**
  \brief   Get CCR2
  \details Returns the current value of the CCR2.
  \return               CCR2 Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_CCR2(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<31, 0>\n"  : "=r"(result));
    return (result);
}

/**
  \brief   Set CCR2
  \details Assigns the given value to the CCR2.
  \param [in]    ccr2  CCR2 value to set
 */
__ALWAYS_STATIC_INLINE void __set_CCR2(uint32_t ccr2)
{
    __ASM volatile("mtcr %0, cr<31, 0>\n" : : "r"(ccr2));
}

/**
  \brief   Get DCSR
  \details Returns the content of the DCSR Register.
  \return               DCSR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_DCSR(void)
{
    uint32_t result;
#ifdef __CK610
    __ASM volatile("mfcr %0, cr14" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<14, 0>" : "=r"(result));
#endif
    return (result);
}


/**
  \brief   Set DCSR
  \details Writes the given value to the DCSR Register.
  \param [in]    dcsr  DCSR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_DCSR(uint32_t dcsr)
{
#ifdef __CK610
    __ASM volatile("mtcr %0, cr14" : : "r"(dcsr));
#else
    __ASM volatile("mtcr %0, cr<14, 0>" : : "r"(dcsr));
#endif
}


/**
  \brief   Get CFR
  \details Returns the content of the CFR Register.
  \return               CFR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_CFR(void)
{
    uint32_t result;
#ifdef __CK610
    __ASM volatile("mfcr %0, cr17" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<17, 0>" : "=r"(result));
#endif

    return (result);
}


/**
  \brief   Set CFR
  \details Writes the given value to the CFR Register.
  \param [in]    cfr  CFR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_CFR(uint32_t cfr)
{
#ifdef __CK610
    __ASM volatile("mtcr %0, cr17" : : "r"(cfr));
#else
    __ASM volatile("mtcr %0, cr<17, 0>" : : "r"(cfr));
#endif
}


/**
  \brief   Get CIR
  \details Returns the content of the CIR Register.
  \return               CIR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_CIR(void)
{
    uint32_t result;
#ifdef __CK610
    __ASM volatile("mfcr %0, cr22" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<22, 0>" : "=r"(result));
#endif
    return (result);
}


/**
  \brief   Set CIR
  \details Writes the given value to the CIR Register.
  \param [in]    cir  CIR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_CIR(uint32_t cir)
{
#ifdef __CK610
    __ASM volatile("mtcr %0, cr22" : : "r"(cir));
#else
    __ASM volatile("mtcr %0, cr<22, 0>" : : "r"(cir));
#endif
}

/**
  \brief   Get ERRLC
  \details Returns the current value of the ERRLC.
  \return               ERRLC Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_ERRLC(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<6, 1>\n"  : "=r"(result));
    return (result);
}

/**
  \brief   Set ERRLC
  \details Assigns the given value to the ERRLC.
  \param [in]    errlc  ERRLC value to set
 */
__ALWAYS_STATIC_INLINE void __set_ERRLC(uint32_t errlc)
{
    __ASM volatile("mtcr %0, cr<6, 1>\n" : : "r"(errlc));
}

/**
  \brief   Get ERRADDR
  \details Returns the current value of the ERRADDR.
  \return               ERRADDR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_ERRADDR(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<7, 1>\n"  : "=r"(result));
    return (result);
}

/**
  \brief   Set ERRADDR
  \details Assigns the given value to the ERRADDR.
  \param [in]    erraddr  ERRADDR value to set
 */
__ALWAYS_STATIC_INLINE void __set_ERRADDR(uint32_t erraddr)
{
    __ASM volatile("mtcr %0, cr<7, 1>\n" : : "r"(erraddr));
}

/**
  \brief   Get ERRSTS
  \details Returns the current value of the ERRSTS.
  \return               ERRSTS Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_ERRSTS(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<8, 1>\n"  : "=r"(result));
    return (result);
}

/**
  \brief   Set ERRSTS
  \details Assigns the given value to the ERRSTS.
  \param [in]    errsts  ERRSTS value to set
 */
__ALWAYS_STATIC_INLINE void __set_ERRSTS(uint32_t errsts)
{
    __ASM volatile("mtcr %0, cr<8, 1>\n" : : "r"(errsts));
}

/**
  \brief   Get ERRINJCR
  \details Returns the current value of the ERRINJCR.
  \return               ERRINJCR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_ERRINJCR(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<9, 1>\n"  : "=r"(result));
    return (result);
}

/**
  \brief   Set ERRINJCR
  \details Assigns the given value to the ERRINJCR.
  \param [in]    errinjcr  ERRINJCR value to set
 */
__ALWAYS_STATIC_INLINE void __set_ERRINJCR(uint32_t errinjcr)
{
    __ASM volatile("mtcr %0, cr<9, 1>\n" : : "r"(errinjcr));
}

/**
  \brief   Get ERRINJCNT
  \details Returns the current value of the ERRINJCNT.
  \return               ERRINJCNT Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_ERRINJCNT(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<10, 1>\n"  : "=r"(result));
    return (result);
}

/**
  \brief   Set ERRINJCNT
  \details Assigns the given value to the ERRINJCNT.
  \param [in]    errinjcnt  ERRINJCNT value to set
 */
__ALWAYS_STATIC_INLINE void __set_ERRINJCNT(uint32_t errinjcnt)
{
    __ASM volatile("mtcr %0, cr<10, 1>\n" : : "r"(errinjcnt));
}

/**
  \brief   Get ITCMCR
  \details Returns the content of the ITCMCR Register.
  \return               ITCMCR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_ITCMCR(void)
{
    uint32_t result;
    __ASM volatile("mfcr %0, cr<22, 1>" : "=r"(result));
    return (result);
}

/**
  \brief   Set ITCMCR
  \details Writes the given value to the ITCMCR Register.
  \param [in]    itcmcr  ITCMCR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_ITCMCR(uint32_t itcmcr)
{
    __ASM volatile("mtcr %0, cr<22, 1>" : : "r"(itcmcr));
}

/**
  \brief   Get DTCMCR
  \details Returns the content of the DTCMCR Register.
  \return               DTCMCR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_DTCMCR(void)
{
    uint32_t result;
    __ASM volatile("mfcr %0, cr<23, 1>" : "=r"(result));
    return (result);
}

/**
  \brief   Set DTCMCR
  \details Writes the given value to the DTCMCR Register.
  \param [in]    dtcmcr  DTCMCR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_DTCMCR(uint32_t dtcmcr)
{
    __ASM volatile("mtcr %0, cr<23, 1>" : : "r"(dtcmcr));
}

/**
  \brief   Get CINDEX
  \details Returns the current value of the CINDEX.
  \return               CINDEX Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_CINDEX(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<26, 1>\n"  : "=r"(result));
    return (result);
}

/**
  \brief   Set CINDEX
  \details Assigns the given value to the CINDEX.
  \param [in]    cindex  CINDEX value to set
 */
__ALWAYS_STATIC_INLINE void __set_CINDEX(uint32_t cindex)
{
    __ASM volatile("mtcr %0, cr<26, 1>\n" : : "r"(cindex));
}

/**
  \brief   Get CDATAx
  \details Returns the current value of the CDATAx.
  \return               CDATAx Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_CDATA0(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<27, 1>\n"  : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_CDATA1(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<28, 1>\n"  : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_CDATA2(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<29, 1>\n"  : "=r"(result));
    return (result);
}

/**
  \brief   Set CDATAx
  \details Assigns the given value to the CDATAx.
  \param [in]    cdata  CDATAx value to set
 */
__ALWAYS_STATIC_INLINE void __set_CDATA0(uint32_t cdata)
{
    __ASM volatile("mtcr %0, cr<27, 1>\n" : : "r"(cdata));
}

__ALWAYS_STATIC_INLINE void __set_CDATA1(uint32_t cdata)
{
    __ASM volatile("mtcr %0, cr<28, 1>\n" : : "r"(cdata));
}

__ALWAYS_STATIC_INLINE void __set_CDATA2(uint32_t cdata)
{
    __ASM volatile("mtcr %0, cr<29, 1>\n" : : "r"(cdata));
}

/**
  \brief   Get CINS
  \details Returns the current value of the CINS.
  \return               CINS Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_CINS(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<31, 1>\n"  : "=r"(result));
    return (result);
}

/**
  \brief   Set CINS
  \details Assigns the given value to the CINS.
  \param [in]    cins  CINS value to set
 */
__ALWAYS_STATIC_INLINE void __set_CINS(uint32_t cins)
{
    __ASM volatile("mtcr %0, cr<31, 1>\n" : : "r"(cins));
}

/**
  \brief   Get CAPR
  \details Returns the current value of the CAPR.
  \return               CAPR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_CAPR(void)
{
    register uint32_t result;

#ifdef __CK610
    __ASM volatile("mfcr %0, cr19\n" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<19, 0>\n" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set CAPR
  \details Assigns the given value to the CAPR.
  \param [in]    capr  CAPR value to set
 */
__ALWAYS_STATIC_INLINE void __set_CAPR(uint32_t capr)
{
#ifdef __CK610
    __ASM volatile("mtcr %0, cr19\n" : : "r"(capr));
#else
    __ASM volatile("mtcr %0, cr<19, 0>\n" : : "r"(capr));
#endif
}

/**
  \brief   Get CAPR1
  \details Returns the current value of the CAPR1.
  \return               CAPR1 Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_CAPR1(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<16, 0>\n" : "=r"(result));
    return (result);
}

/**
  \brief   Set CAPR1
  \details Assigns the given value to the CAPR1.
  \param [in]    capr1  CAPR1 value to set
 */
__ALWAYS_STATIC_INLINE void __set_CAPR1(uint32_t capr1)
{
    __ASM volatile("mtcr %0, cr<16, 0>\n" : : "r"(capr1));
}

/**
  \brief   Set PACR
  \details Assigns the given value to the PACR.

    \param [in]    pacr  PACR value to set
 */
__ALWAYS_STATIC_INLINE void __set_PACR(uint32_t pacr)
{
#ifdef __CK610
    __ASM volatile("mtcr %0, cr20\n" : : "r"(pacr));
#else
    __ASM volatile("mtcr %0, cr<20, 0>\n" : : "r"(pacr));
#endif
}


/**
  \brief   Get PACR
  \details Returns the current value of PACR.
  \return               PACR value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_PACR(void)
{
    uint32_t result;

#ifdef __CK610
    __ASM volatile("mfcr %0, cr20" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<20, 0>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set PRSR
  \details Assigns the given value to the PRSR.

    \param [in]    prsr  PRSR value to set
 */
__ALWAYS_STATIC_INLINE void __set_PRSR(uint32_t prsr)
{
#ifdef __CK610
    __ASM volatile("mtcr %0, cr21\n" : : "r"(prsr));
#else
    __ASM volatile("mtcr %0, cr<21, 0>\n" : : "r"(prsr));
#endif
}

/**
  \brief   Get PRSR
  \details Returns the current value of PRSR.
  \return               PRSR value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_PRSR(void)
{
    uint32_t result;

#ifdef __CK610
    __ASM volatile("mfcr %0, cr21" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<21, 0>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set ATTR0
  \details Assigns the given value to the ATTR0.

    \param [in]    attr0  ATTR0 value to set
 */
__ALWAYS_STATIC_INLINE void __set_ATTR0(uint32_t attr0)
{
    __ASM volatile("mtcr %0, cr<26, 0>\n" : : "r"(attr0));
}

/**
  \brief   Get ATTR0
  \details Returns the current value of ATTR0.
  \return               ATTR0 value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_ATTR0(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<26, 0>" : "=r"(result));

    return (result);
}

/**
  \brief   Set ATTR1
  \details Assigns the given value to the ATTR1.

    \param [in]    attr0  ATTR1 value to set
 */
__ALWAYS_STATIC_INLINE void __set_ATTR1(uint32_t attr1)
{
    __ASM volatile("mtcr %0, cr<27, 0>\n" : : "r"(attr1));
}

/**
  \brief   Get ATTR1
  \details Returns the current value of ATTR1.
  \return               ATTR1 value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_ATTR1(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<27, 0>" : "=r"(result));

    return (result);
}

/**
  \brief   Get user sp
  \details Returns the current value of user r14.
  \return               UR14 value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_UR14(void)
{
    uint32_t result;

#ifdef __CK610
    __ASM volatile("mov %0, sp" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<14, 1>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set UR14
  \details Assigns the given value to the UR14.
  \param [in]    ur14  UR14 value to set
 */
__ALWAYS_STATIC_INLINE void __set_UR14(uint32_t ur14)
{
#ifdef __CK610
    __ASM volatile("mov sp, %0" : "=r"(ur14));
#else
    __ASM volatile("mtcr %0, cr<14, 1>\n" : : "r"(ur14));
#endif
}

/**
  \brief   Get CHR Register
  \details Returns the content of the CHR Register.
  \return               CHR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_CHR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<31, 0>\n" :"=r"(result));
    return (result);
}

/**
  \brief   Set CHR
  \details Assigns the given value to the CHR.
  \param [in]    chr  CHR value to set
 */
__ALWAYS_STATIC_INLINE void __set_CHR(uint32_t chr)
{
    __ASM volatile("mtcr %0, cr<31, 0>\n" : : "r"(chr));
}

/**
  \brief   Get HINT
  \details Returns the content of the HINT Register.
  \return               HINT Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_HINT(void)
{
    uint32_t result;
#ifdef __CK610
    __ASM volatile("mfcr %0, cr<30, 0>" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<31, 0>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set HINT
  \details Writes the given value to the HINT Register.
  \param [in]    hint  HINT Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_HINT(uint32_t hint)
{
#ifdef __CK610
    __ASM volatile("mtcr %0, cr<30, 0>" : "=r"(hint));
#else
    __ASM volatile("mtcr %0, cr<31, 0>" : : "r"(hint));
#endif
}

/**
  \brief   Get MIR
  \details Returns the content of the MIR Register.
  \return               MIR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MIR(void)
{
    uint32_t result;
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cprcr %0, cpcr0" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<0, 15>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set MIR
  \details Writes the given value to the MIR Register.
  \param [in]    mir  MIR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MIR(uint32_t mir)
{
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cpwcr %0, cpcr0" : : "b"(mir));
#else
    __ASM volatile("mtcr %0, cr<0, 15>" : : "r"(mir));
#endif
}


/**
  \brief   Get MEL0
  \details Returns the content of the MEL0 Register.
  \return               MEL0 Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MEL0(void)
{
    uint32_t result;
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cprcr %0, cpcr2" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<2, 15>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set MEL0
  \details Writes the given value to the MEL0 Register.
  \param [in]    mel0  MEL0 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MEL0(uint32_t mel0)
{
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cpwcr %0, cpcr2" : : "b"(mel0));
#else
    __ASM volatile("mtcr %0, cr<2, 15>" : : "r"(mel0));
#endif
}


/**
  \brief   Get MEL1
  \details Returns the content of the MEL1 Register.
  \return               MEL1 Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MEL1(void)
{
    uint32_t result;
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cprcr %0, cpcr3" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<3, 15>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set MEL1
  \details Writes the given value to the MEL1 Register.
  \param [in]    mel1  MEL1 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MEL1(uint32_t mel1)
{
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cpwcr %0, cpcr3" : : "b"(mel1));
#else
    __ASM volatile("mtcr %0, cr<3, 15>" : : "r"(mel1));
#endif
}


/**
  \brief   Get MEH
  \details Returns the content of the MEH Register.
  \return               MEH Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MEH(void)
{
    uint32_t result;
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cprcr %0, cpcr4" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<4, 15>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set MEH
  \details Writes the given value to the MEH Register.
  \param [in]    meh  MEH Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MEH(uint32_t meh)
{
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cpwcr %0, cpcr4" : : "b"(meh));
#else
    __ASM volatile("mtcr %0, cr<4, 15>" : : "r"(meh));
#endif
}


/**
  \brief   Get MPR
  \details Returns the content of the MPR Register.
  \return               MPR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MPR(void)
{
    uint32_t result;
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cprcr %0, cpcr6" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<6, 15>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set MPR
  \details Writes the given value to the MPR Register.
  \param [in]    mpr  MPR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MPR(uint32_t mpr)
{
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cpwcr %0, cpcr6" : : "b"(mpr));
#else
    __ASM volatile("mtcr %0, cr<6, 15>" : : "r"(mpr));
#endif
}


/**
  \brief   Get MCIR
  \details Returns the content of the MCIR Register.
  \return               MCIR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MCIR(void)
{
    uint32_t result;
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cprcr %0, cpcr8" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<8, 15>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set MCIR
  \details Writes the given value to the MCIR Register.
  \param [in]    mcir  MCIR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MCIR(uint32_t mcir)
{
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cpwcr %0, cpcr8" : : "b"(mcir));
#else
    __ASM volatile("mtcr %0, cr<8, 15>" : : "r"(mcir));
#endif
}


/**
  \brief   Get MPGD
  \details Returns the content of the MPGD Register.
  \return               MPGD Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MPGD(void)
{
    uint32_t result;
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cprcr %0, cpcr29" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<29, 15>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set MPGD
  \details Writes the given value to the MPGD Register.
  \param [in]    mpgd  MPGD Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MPGD(uint32_t mpgd)
{
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cpwcr %0, cpcr29" : : "b"(mpgd));
#else
    __ASM volatile("mtcr %0, cr<29, 15>" : : "r"(mpgd));
#endif
}


/**
  \brief   Get MSA0
  \details Returns the content of the MSA0 Register.
  \return               MSA0 Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MSA0(void)
{
    uint32_t result;
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cprcr %0, cpcr30" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<30, 15>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set MSA0
  \details Writes the given value to the MSA0 Register.
  \param [in]    msa0  MSA0 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MSA0(uint32_t msa0)
{
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cpwcr %0, cpcr30" : : "b"(msa0));
#else
    __ASM volatile("mtcr %0, cr<30, 15>" : : "r"(msa0));
#endif
}


/**
  \brief   Get MSA1
  \details Returns the content of the MSA1 Register.
  \return               MSA1 Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MSA1(void)
{
    uint32_t result;

#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cprcr %0, cpcr31" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<31, 15>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set MSA1
  \details Writes the given value to the MSA1 Register.
  \param [in]    msa1  MSA1 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MSA1(uint32_t msa1)
{
#ifdef __CK610
    __ASM volatile("cpseti 15");
    __ASM volatile("cpwcr %0, cpcr31" : : "b"(msa1));
#else
    __ASM volatile("mtcr %0, cr<31, 15>" : : "r"(msa1));
#endif
}


/**
  \brief   Enable interrupts and exceptions
  \details Enables interrupts and exceptions by setting the IE-bit and EE-bit in the PSR.
           Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __enable_excp_irq(void)
{
    __ASM volatile("psrset ee, ie");
}


/**
  \brief   Disable interrupts and exceptions
  \details Disables interrupts and exceptions by clearing the IE-bit and EE-bit in the PSR.
           Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __disable_excp_irq(void)
{
    __ASM volatile("psrclr ee, ie");
}

/**
  \brief   Get GSR
  \details Returns the content of the GSR Register.
  \return               GSR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_GSR(void)
{
    uint32_t result;

#ifdef __CK610
    __ASM volatile("mfcr %0, cr12" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<12, 0>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Get GCR
  \details Returns the content of the GCR Register.
  \return               GCR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_GCR(void)
{
    uint32_t result;

#ifdef __CK610
    __ASM volatile("mfcr %0, cr11" : "=r"(result));
#else
    __ASM volatile("mfcr %0, cr<11, 0>" : "=r"(result));
#endif
    return (result);
}

/**
  \brief   Set GCR
  \details Writes the given value to the GCR Register.
  \param [in]    gcr  GCR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_GCR(uint32_t gcr)
{
#ifdef __CK610
    __ASM volatile("mtcr %0, cr11" : : "r"(gcr));
#else
    __ASM volatile("mtcr %0, cr<11, 0>" : : "r"(gcr));
#endif
}

/**
  \brief   Get WSSR
  \details Returns the content of the WSSR Register, must be accessed in TEE
  \return               WSSR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_WSSR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<0, 3>" : "=r"(result));
    return (result);
}

/**
  \brief   Get WRCR
  \details Returns the content of the WRCR Register, must be accessed in TEE
  \return               WRCR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_WRCR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<1, 3>" : "=r"(result));
    return (result);
}

/**
  \brief   Set WRCR
  \details Writes the given value to the WRCR Register, must be accessed in TEE
  \param [in]    wrcr  WRCR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_WRCR(uint32_t wrcr)
{
    __ASM volatile("mtcr %0, cr<1, 3>" : : "r"(wrcr));
}

/**
  \brief   Get DCR
  \details Returns the content of the DCR Register, must be accessed in TEE
  \return               DCR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_DCR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<8, 3>" : "=r"(result));
    return (result);
}

/**
  \brief   Set DCR
  \details Writes the given value to the DCR Register, must be accessed in TEE
  \param [in]    dcr  DCR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_DCR(uint32_t dcr)
{
    __ASM volatile("mtcr %0, cr<8, 3>" : : "r"(dcr));
}

/**
  \brief   Get PCR
  \details Returns the content of the PCR Register, must be accessed in TEE
  \return               PCR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_PCR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<9, 3>" : "=r"(result));
    return (result);
}

/**
  \brief   Set PCR
  \details Writes the given value to the PCR Register, must be accessed in TEE
  \param [in]    pcr  PCR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_PCR(uint32_t pcr)
{
    __ASM volatile("mtcr %0, cr<9, 3>" : : "r"(pcr));
}

/**
  \brief   Get EBR
  \details Returns the content of the EBR Register.
  \return               EBR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_EBR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<1, 1>" : "=r"(result));
    return (result);
}

/**
  \brief   Set EBR
  \details Writes the given value to the EBR Register.
  \param [in]    ebr  EBR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_EBR(uint32_t ebr)
{
    __ASM volatile("mtcr %0, cr<1, 1>" : : "r"(ebr));
}

/*@} end of CSI_Core_RegAccFunctions */

/* ##########################  Core Instruction Access  ######################### */
/** \defgroup CSI_Core_InstructionInterface CSI Core Instruction Interface
  Access to dedicated instructions
  @{
*/

#define __CSI_GCC_OUT_REG(r) "=r" (r)
#define __CSI_GCC_USE_REG(r) "r" (r)

/**
  \brief   No Operation
  \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
__ALWAYS_STATIC_INLINE void __NOP(void)
{
    __ASM volatile("nop");
}


/**
  \brief   Wait For Interrupt
  \details Wait For Interrupt is a hint instruction that suspends execution until one of a number of events occurs.
 */
__ALWAYS_STATIC_INLINE void __WFI(void)
{
    __ASM volatile("wait");
}

/**
  \brief   Wait For Interrupt
  \details Wait For Interrupt is a hint instruction that suspends execution until one interrupt occurs.
 */
__ALWAYS_STATIC_INLINE void __WAIT(void)
{
    __ASM volatile("wait");
}

/**
  \brief   Doze For Interrupt
  \details Doze For Interrupt is a hint instruction that suspends execution until one interrupt occurs.
 */
__ALWAYS_STATIC_INLINE void __DOZE(void)
{
    __ASM volatile("doze");
}

/**
  \brief   Stop For Interrupt
  \details Stop For Interrupt is a hint instruction that suspends execution until one interrupt occurs.
 */
__ALWAYS_STATIC_INLINE void __STOP(void)
{
    __ASM volatile("stop");
}

/**
  \brief   Instruction Synchronization Barrier
  \details Instruction Synchronization Barrier flushes the pipeline in the processor,
           so that all instructions following the ISB are fetched from cache or memory,
           after the instruction has been completed.
 */
__ALWAYS_STATIC_INLINE void __ISB(void)
{
    __ASM volatile("sync"::: "memory");
}


/**
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
__ALWAYS_STATIC_INLINE void __DSB(void)
{
    __ASM volatile("sync"::: "memory");
}


/**
  \brief   Data Memory Barrier
  \details Ensures the apparent order of the explicit memory operations before
           and after the instruction, without ensuring their completion.
 */
__ALWAYS_STATIC_INLINE void __DMB(void)
{
    __ASM volatile("sync"::: "memory");
}

/**
  \brief   Search from the highest bit that the very first bit which's value is 1.
  \param [in]    value  Value to  bit search.
  \return               if the highest bit' value is 1,  return 0, and if lowest bit's value is 1, return 31, otherwise return 32.
 */
#if !defined(__CK610) || !(__CK80X == 1)
__ALWAYS_STATIC_INLINE uint32_t __FF0(uint32_t value)
{
    uint32_t ret;

    __ASM volatile("ff0 %0, %1" : "=r"(ret) : "r"(value));
    return ret;
}
#endif

/**
  \brief   Search from the highest bit that the very first bit which's value is 0.
  \param [in]    value  Value to  bit search.
  \return               if the highest bit' value is 0,  return 0, and if lowest bit's value is 0, return 31, otherwise return 32.
 */
#if !(__CK80X == 1)
__ALWAYS_STATIC_INLINE uint32_t __FF1(uint32_t value)
{
    uint32_t ret;
#if !defined (__CK610)
    __ASM volatile("ff1 %0, %1" : "=r"(ret) : "r"(value));
#else
    ret = value;
    __ASM volatile("ff1 %0" : "=r"(ret):);
#endif
    return ret;
}
#endif

/**
  \brief   Reverse byte order (32 bit)
  \details Reverses the byte order in integer value.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_STATIC_INLINE uint32_t __REV(uint32_t value)
{
    return __builtin_bswap32(value);
}


/**
  \brief   Reverse byte order (16 bit)
  \details Reverses the byte order in two unsigned short values.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_STATIC_INLINE uint32_t __REV16(uint32_t value)
{
    uint32_t result;
#if (__CK80X >= 2)
    __ASM volatile("revh %0, %1" : __CSI_GCC_OUT_REG(result) : __CSI_GCC_USE_REG(value));
#else
    result = ((value & 0xFF000000) >> 8) | ((value & 0x00FF0000) << 8) |
             ((value & 0x0000FF00) >> 8) | ((value & 0x000000FF) << 8);
#endif
    return (result);
}


/**
  \brief   Reverse byte order in signed short value
  \details Reverses the byte order in a signed short value with sign extension to integer.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_STATIC_INLINE int32_t __REVSH(int32_t value)
{
    return (short)(((value & 0xFF00) >> 8) | ((value & 0x00FF) << 8));
}


/**
  \brief   Rotate Right in unsigned value (32 bit)
  \details Rotate Right (immediate) provides the value of the contents of a register rotated by a variable number of bits.
  \param [in]    op1  Value to rotate
  \param [in]    op2  Number of Bits to rotate
  \return               Rotated value
 */
__ALWAYS_STATIC_INLINE uint32_t __ROR(uint32_t op1, uint32_t op2)
{
    return (op1 >> op2) | (op1 << (32U - op2));
}


/**
  \brief   Breakpoint
  \details Causes the processor to enter Debug state
           Debug tools can use this to investigate system state when the instruction at a particular address is reached.
 */
__ALWAYS_STATIC_INLINE void __BKPT(void)
{
    __ASM volatile("bkpt");
}

/**
  \brief   Reverse bit order of value
  \details Reverses the bit order of the given value.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_STATIC_INLINE uint32_t __RBIT(uint32_t value)
{
    uint32_t result;

#if (__CK80X >= 0x03U)
    __ASM volatile("brev %0, %1" : "=r"(result) : "r"(value));
#else
    int32_t s = 4 /*sizeof(v)*/ * 8 - 1; /* extra shift needed at end */

    result = value;                      /* r will be reversed bits of v; first get LSB of v */

    for (value >>= 1U; value; value >>= 1U) {
        result <<= 1U;
        result |= value & 1U;
        s--;
    }

    result <<= s;                        /* shift when v's highest bits are zero */
#endif
    return (result);
}


/**
  \brief   Count leading zeros
  \details Counts the number of leading zeros of a data value.
  \param [in]  value  Value to count the leading zeros
  \return             number of leading zeros in value
 */
#define __CLZ             __builtin_clz
/**
  \details This function saturates a signed value.
  \param [in]    x   Value to be saturated
  \param [in]    y   Bit position to saturate to [1..32]
  \return            Saturated value.
 */
__ALWAYS_STATIC_INLINE int32_t __SSAT(int32_t x, uint32_t y)
{
    int32_t posMax, negMin;
    uint32_t i;

    posMax = 1;

    for (i = 0; i < (y - 1); i++) {
        posMax = posMax * 2;
    }

    if (x > 0) {
        posMax = (posMax - 1);

        if (x > posMax) {
            x = posMax;
        }

//    x &= (posMax * 2 + 1);
    } else {
        negMin = -posMax;

        if (x < negMin) {
            x = negMin;
        }

//    x &= (posMax * 2 - 1);
    }

    return (x);
}

/**
  \brief   Unsigned Saturate
  \details Saturates an unsigned value.
  \param [in]  value  Value to be saturated
  \param [in]    sat  Bit position to saturate to (0..31)
  \return             Saturated value
 */
__ALWAYS_STATIC_INLINE uint32_t __USAT(uint32_t value, uint32_t sat)
{
    uint32_t result;

    if ((((0xFFFFFFFF >> sat) << sat) & value) != 0) {
        result = 0xFFFFFFFF >> (32 - sat);
    } else {
        result = value;
    }

    return (result);
}

/**
  \brief   Unsigned Saturate for internal use
  \details Saturates an unsigned value, should not call directly.
  \param [in]  value  Value to be saturated
  \param [in]    sat  Bit position to saturate to (0..31)
  \return             Saturated value
 */
__ALWAYS_STATIC_INLINE uint32_t __IUSAT(uint32_t value, uint32_t sat)
{
    uint32_t result;

    if (value & 0x80000000) { /* only overflow set bit-31 */
        result = 0;
    } else if ((((0xFFFFFFFF >> sat) << sat) & value) != 0) {
        result = 0xFFFFFFFF >> (32 - sat);
    } else {
        result = value;
    }

    return (result);
}

/**
  \brief   Rotate Right with Extend
  \details This function moves each bit of a bitstring right by one bit.
           The carry input is shifted in at the left end of the bitstring.
  \note    carry input will always 0.
  \param [in]    op1  Value to rotate
  \return               Rotated value
 */
__ALWAYS_STATIC_INLINE uint32_t __RRX(uint32_t op1)
{
#if (__CK80X >= 2)
    uint32_t res = 0;
    __ASM volatile("bgeni    t0, 31\n\t"
                   "lsri     %0, 1\n\t"
                   "movt     %1, t0\n\t"
                   "or       %1, %1, %0\n\t"
               : "=r"(op1), "=r"(res): "0"(op1), "1"(res): "t0");
    return res;
#else
    uint32_t res = 0;
    __ASM volatile("movi     r7, 0\n\t"
                   "bseti    r7, 31\n\t"
                   "lsri     %0, 1\n\t"
                   "bf       1f\n\t"
                   "mov     %1, r7\n\t"
                   "1:\n\t"
                   "or       %1, %1, %0\n\t"
               : "=r"(op1), "=r"(res): "0"(op1), "1"(res): "r7");
    return res;
#endif
}

/**
  \brief   LDRT Unprivileged (8 bit)
  \details Executes a Unprivileged LDRT instruction for 8 bit value.
  \param [in]    addr  Pointer to location
  \return             value of type uint8_t at (*ptr)
 */
__ALWAYS_STATIC_INLINE uint8_t __LDRBT(volatile uint8_t *addr)
{
    uint32_t result;
//#warning "__LDRBT"
    __ASM volatile("ldb %0, (%1, 0)" : "=r"(result) : "r"(addr));
    return ((uint8_t) result);    /* Add explicit type cast here */
}


/**
  \brief   LDRT Unprivileged (16 bit)
  \details Executes a Unprivileged LDRT instruction for 16 bit values.
  \param [in]    addr  Pointer to location
  \return        value of type uint16_t at (*ptr)
 */
__ALWAYS_STATIC_INLINE uint16_t __LDRHT(volatile uint16_t *addr)
{
    uint32_t result;

//#warning "__LDRHT"
    __ASM volatile("ldh %0, (%1, 0)" : "=r"(result) : "r"(addr));
    return ((uint16_t) result);    /* Add explicit type cast here */
}


/**
  \brief   LDRT Unprivileged (32 bit)
  \details Executes a Unprivileged LDRT instruction for 32 bit values.
  \param [in]    addr  Pointer to location
  \return        value of type uint32_t at (*ptr)
 */
__ALWAYS_STATIC_INLINE uint32_t __LDRT(volatile uint32_t *addr)
{
    uint32_t result;

//#warning "__LDRT"
    __ASM volatile("ldw %0, (%1, 0)" : "=r"(result) : "r"(addr));
    return (result);
}


/**
  \brief   STRT Unprivileged (8 bit)
  \details Executes a Unprivileged STRT instruction for 8 bit values.
  \param [in]  value  Value to store
  \param [in]    addr  Pointer to location
 */
__ALWAYS_STATIC_INLINE void __STRBT(uint8_t value, volatile uint8_t *addr)
{
//#warning "__STRBT"
    __ASM volatile("stb %1, (%0, 0)" :: "r"(addr), "r"((uint32_t)value) : "memory");
}


/**
  \brief   STRT Unprivileged (16 bit)
  \details Executes a Unprivileged STRT instruction for 16 bit values.
  \param [in]  value  Value to store
  \param [in]    addr  Pointer to location
 */
__ALWAYS_STATIC_INLINE void __STRHT(uint16_t value, volatile uint16_t *addr)
{
//#warning "__STRHT"
    __ASM volatile("sth %1, (%0, 0)" :: "r"(addr), "r"((uint32_t)value) : "memory");
}


/**
  \brief   STRT Unprivileged (32 bit)
  \details Executes a Unprivileged STRT instruction for 32 bit values.
  \param [in]  value  Value to store
  \param [in]    addr  Pointer to location
 */
__ALWAYS_STATIC_INLINE void __STRT(uint32_t value, volatile uint32_t *addr)
{
//#warning "__STRT"
    __ASM volatile("stw %1, (%0, 0)" :: "r"(addr), "r"(value) : "memory");
}

/*@}*/ /* end of group CSI_Core_InstructionInterface */


/* ##########################  FPU functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_FpuFunctions FPU Functions
  \brief    Function that provides FPU type.
  @{
 */

/**
  \brief   get FPU type
  \details returns the FPU type, always 0.
  \returns
   - \b  0: No FPU
   - \b  1: Single precision FPU
   - \b  2: Double + Single precision FPU
 */
__ALWAYS_STATIC_INLINE uint32_t __get_FPUType(void)
{
//FIXME:
    return 0;
}

/*@} end of CSI_Core_FpuFunctions */

/* ###################  Compiler specific Intrinsics  ########################### */
/** \defgroup CSI_SIMD_intrinsics CSI SIMD Intrinsics
  Access to dedicated SIMD instructions \n
  Single Instruction Multiple Data (SIMD) extensions are provided to simplify development of application software. SIMD extensions increase the processing capability without materially increasing the power consumption. The SIMD extensions are completely transparent to the operating system (OS), allowing existing OS ports to be used.

  @{
*/

/**
  \brief   Halfword packing instruction. Combines bits[15:0] of val1 with bits[31:16]
           of val2 levitated with the val3.
  \details Combine a halfword from one register with a halfword from another register.
           The second argument can be left-shifted before extraction of the halfword.
  \param [in]    val1   first 16-bit operands
  \param [in]    val2   second 16-bit operands
  \param [in]    val3   value for left-shifting val2. Value range [0..31].
  \return               the combination of halfwords.
  \remark
                 res[15:0]  = val1[15:0]              \n
                 res[31:16] = val2[31:16] << val3
 */
__ALWAYS_STATIC_INLINE uint32_t __PKHBT(uint32_t val1, uint32_t val2, uint32_t val3)
{
    return ((((int32_t)(val1) << 0) & (int32_t)0x0000FFFF) | (((int32_t)(val2) << val3) & (int32_t)0xFFFF0000));
}

/**
  \brief   Halfword packing instruction. Combines bits[31:16] of val1 with bits[15:0]
           of val2 right-shifted with the val3.
  \details Combine a halfword from one register with a halfword from another register.
           The second argument can be right-shifted before extraction of the halfword.
  \param [in]    val1   first 16-bit operands
  \param [in]    val2   second 16-bit operands
  \param [in]    val3   value for right-shifting val2. Value range [1..32].
  \return               the combination of halfwords.
  \remark
                 res[15:0]  = val2[15:0] >> val3        \n
                 res[31:16] = val1[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __PKHTB(uint32_t val1, uint32_t val2, uint32_t val3)
{
    return ((((int32_t)(val1) << 0) & (int32_t)0xFFFF0000) | (((int32_t)(val2) >> val3) & (int32_t)0x0000FFFF));
}

/**
  \brief   Dual 16-bit signed saturate.
  \details This function saturates a signed value.
  \param [in]    x   two signed 16-bit values to be saturated.
  \param [in]    y   bit position for saturation, an integral constant expression in the range 1 to 16.
  \return        the sum of the absolute differences of the following bytes, added to the accumulation value:\n
                 the signed saturation of the low halfword in val1, saturated to the bit position specified in
                 val2 and returned in the low halfword of the return value.\n
                 the signed saturation of the high halfword in val1, saturated to the bit position specified in
                 val2 and returned in the high halfword of the return value.
 */
__ALWAYS_STATIC_INLINE uint32_t __SSAT16(int32_t x, const uint32_t y)
{
    int32_t r = 0, s = 0;

    r = __SSAT((((int32_t)x << 16) >> 16), y) & (int32_t)0x0000FFFF;
    s = __SSAT((((int32_t)x) >> 16), y) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturate.
  \details This function enables you to saturate two signed 16-bit values to a selected unsigned range.
  \param [in]    x   two signed 16-bit values to be saturated.
  \param [in]    y   bit position for saturation, an integral constant expression in the range 1 to 16.
  \return        the saturation of the two signed 16-bit values, as non-negative values:
                 the saturation of the low halfword in val1, saturated to the bit position specified in
                 val2 and returned in the low halfword of the return value.\n
                 the saturation of the high halfword in val1, saturated to the bit position specified in
                 val2 and returned in the high halfword of the return value.
 */
__ALWAYS_STATIC_INLINE uint32_t __USAT16(uint32_t x, const uint32_t y)
{
    int32_t r = 0, s = 0;

    r = __IUSAT(((x << 16) >> 16), y) & 0x0000FFFF;
    s = __IUSAT(((x) >> 16), y) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Quad 8-bit saturating addition.
  \details This function enables you to perform four 8-bit integer additions,
           saturating the results to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the saturated addition of the first byte of each operand in the first byte of the return value.\n
                 the saturated addition of the second byte of each operand in the second byte of the return value.\n
                 the saturated addition of the third byte of each operand in the third byte of the return value.\n
                 the saturated addition of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __QADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = __SSAT(((((int32_t)x << 24) >> 24) + (((int32_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((int32_t)x << 16) >> 24) + (((int32_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((int32_t)x <<  8) >> 24) + (((int32_t)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((int32_t)x) >> 24) + (((int32_t)y) >> 24)), 8) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned saturating addition.
  \details This function enables you to perform four unsigned 8-bit integer additions,
           saturating the results to the 8-bit unsigned integer range 0 < x < 2^8 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the saturated addition of the first byte of each operand in the first byte of the return value.\n
                 the saturated addition of the second byte of each operand in the second byte of the return value.\n
                 the saturated addition of the third byte of each operand in the third byte of the return value.\n
                 the saturated addition of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit signed integer range 0 <= x <= 2^8 - 1.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __UQADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = __IUSAT((((x << 24) >> 24) + ((y << 24) >> 24)), 8) & 0x000000FF;
    s = __IUSAT((((x << 16) >> 24) + ((y << 16) >> 24)), 8) & 0x000000FF;
    t = __IUSAT((((x <<  8) >> 24) + ((y <<  8) >> 24)), 8) & 0x000000FF;
    u = __IUSAT((((x) >> 24) + ((y) >> 24)), 8) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Quad 8-bit signed addition.
  \details This function performs four 8-bit signed integer additions.
  \param [in]    x  first four 8-bit summands.
  \param [in]    y  second four 8-bit summands.
  \return        the addition of the first bytes from each operand, in the first byte of the return value.\n
                 the addition of the second bytes of each operand, in the second byte of the return value.\n
                 the addition of the third bytes of each operand, in the third byte of the return value.\n
                 the addition of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __SADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = ((((int32_t)x << 24) >> 24) + (((int32_t)y << 24) >> 24)) & (int32_t)0x000000FF;
    s = ((((int32_t)x << 16) >> 24) + (((int32_t)y << 16) >> 24)) & (int32_t)0x000000FF;
    t = ((((int32_t)x <<  8) >> 24) + (((int32_t)y <<  8) >> 24)) & (int32_t)0x000000FF;
    u = ((((int32_t)x) >> 24) + (((int32_t)y) >> 24)) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned addition.
  \details This function performs four unsigned 8-bit integer additions.
  \param [in]    x  first four 8-bit summands.
  \param [in]    y  second four 8-bit summands.
  \return        the addition of the first bytes from each operand, in the first byte of the return value.\n
                 the addition of the second bytes of each operand, in the second byte of the return value.\n
                 the addition of the third bytes of each operand, in the third byte of the return value.\n
                 the addition of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __UADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((x << 24) >> 24) + ((y << 24) >> 24)) & 0x000000FF;
    s = (((x << 16) >> 24) + ((y << 16) >> 24)) & 0x000000FF;
    t = (((x <<  8) >> 24) + ((y <<  8) >> 24)) & 0x000000FF;
    u = (((x) >> 24) + ((y) >> 24)) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Quad 8-bit saturating subtract.
  \details This function enables you to perform four 8-bit integer subtractions,
           saturating the results to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the subtraction of the first byte of each operand in the first byte of the return value.\n
                 the subtraction of the second byte of each operand in the second byte of the return value.\n
                 the subtraction of the third byte of each operand in the third byte of the return value.\n
                 the subtraction of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __QSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = __SSAT(((((int32_t)x << 24) >> 24) - (((int32_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((int32_t)x << 16) >> 24) - (((int32_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((int32_t)x <<  8) >> 24) - (((int32_t)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((int32_t)x) >> 24) - (((int32_t)y) >> 24)), 8) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned saturating subtraction.
  \details This function enables you to perform four unsigned 8-bit integer subtractions,
           saturating the results to the 8-bit unsigned integer range 0 < x < 2^8 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the subtraction of the first byte of each operand in the first byte of the return value.\n
                 the subtraction of the second byte of each operand in the second byte of the return value.\n
                 the subtraction of the third byte of each operand in the third byte of the return value.\n
                 the subtraction of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit unsigned integer range 0 <= x <= 2^8 - 1.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __UQSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = __IUSAT((((x << 24) >> 24) - ((y << 24) >> 24)), 8) & 0x000000FF;
    s = __IUSAT((((x << 16) >> 24) - ((y << 16) >> 24)), 8) & 0x000000FF;
    t = __IUSAT((((x <<  8) >> 24) - ((y <<  8) >> 24)), 8) & 0x000000FF;
    u = __IUSAT((((x) >> 24) - ((y) >> 24)), 8) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Quad 8-bit signed subtraction.
  \details This function enables you to perform four 8-bit signed integer subtractions.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \return        the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __SSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = ((((int32_t)x << 24) >> 24) - (((int32_t)y << 24) >> 24)) & (int32_t)0x000000FF;
    s = ((((int32_t)x << 16) >> 24) - (((int32_t)y << 16) >> 24)) & (int32_t)0x000000FF;
    t = ((((int32_t)x <<  8) >> 24) - (((int32_t)y <<  8) >> 24)) & (int32_t)0x000000FF;
    u = ((((int32_t)x) >> 24) - (((int32_t)y) >> 24)) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned subtract.
  \details This function enables you to perform four 8-bit unsigned integer subtractions.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \return        the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __USUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((x << 24) >> 24) - ((y << 24) >> 24)) & 0x000000FF;
    s = (((x << 16) >> 24) - ((y << 16) >> 24)) & 0x000000FF;
    t = (((x <<  8) >> 24) - ((y <<  8) >> 24)) & 0x000000FF;
    u = (((x) >> 24) - ((y) >> 24)) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Unsigned sum of quad 8-bit unsigned absolute difference.
  \details This function enables you to perform four unsigned 8-bit subtractions, and add the absolute values
           of the differences together, returning the result as a single unsigned integer.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \return        the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.\n
                 The sum is returned as a single unsigned integer.
  \remark
                 absdiff1   = val1[7:0]   - val2[7:0]        \n
                 absdiff2   = val1[15:8]  - val2[15:8]       \n
                 absdiff3   = val1[23:16] - val2[23:16]      \n
                 absdiff4   = val1[31:24] - val2[31:24]      \n
                 res[31:0]  = absdiff1 + absdiff2 + absdiff3 + absdiff4
 */
__ALWAYS_STATIC_INLINE uint32_t __USAD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((x << 24) >> 24) - ((y << 24) >> 24)) & 0x000000FF;
    s = (((x << 16) >> 24) - ((y << 16) >> 24)) & 0x000000FF;
    t = (((x <<  8) >> 24) - ((y <<  8) >> 24)) & 0x000000FF;
    u = (((x) >> 24) - ((y) >> 24)) & 0x000000FF;

    return (u + t + s + r);
}

/**
  \brief   Unsigned sum of quad 8-bit unsigned absolute difference with 32-bit accumulate.
  \details This function enables you to perform four unsigned 8-bit subtractions, and add the absolute values
           of the differences to a 32-bit accumulate operand.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \param [in]  sum  accumulation value.
  \return        the sum of the absolute differences of the following bytes, added to the accumulation value:
                 the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 absdiff1 = val1[7:0]   - val2[7:0]        \n
                 absdiff2 = val1[15:8]  - val2[15:8]       \n
                 absdiff3 = val1[23:16] - val2[23:16]      \n
                 absdiff4 = val1[31:24] - val2[31:24]      \n
                 sum = absdiff1 + absdiff2 + absdiff3 + absdiff4 \n
                 res[31:0] = sum[31:0] + val3[31:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __USADA8(uint32_t x, uint32_t y, uint32_t sum)
{
    int32_t r, s, t, u;

#ifdef __cplusplus
    r = (abs((long long)((x << 24) >> 24) - ((y << 24) >> 24))) & 0x000000FF;
    s = (abs((long long)((x << 16) >> 24) - ((y << 16) >> 24))) & 0x000000FF;
    t = (abs((long long)((x <<  8) >> 24) - ((y <<  8) >> 24))) & 0x000000FF;
    u = (abs((long long)((x) >> 24) - ((y) >> 24))) & 0x000000FF;
#else
    r = (abs(((x << 24) >> 24) - ((y << 24) >> 24))) & 0x000000FF;
    s = (abs(((x << 16) >> 24) - ((y << 16) >> 24))) & 0x000000FF;
    t = (abs(((x <<  8) >> 24) - ((y <<  8) >> 24))) & 0x000000FF;
    u = (abs(((x) >> 24) - ((y) >> 24))) & 0x000000FF;
#endif
    return (u + t + s + r + sum);
}

/**
  \brief   Dual 16-bit saturating addition.
  \details This function enables you to perform two 16-bit integer arithmetic additions in parallel,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the saturated addition of the low halfwords, in the low halfword of the return value.\n
                 the saturated addition of the high halfwords, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __QADD16(uint32_t x, uint32_t y)
{
    int32_t r = 0, s = 0;

    r = __SSAT(((((int32_t)x << 16) >> 16) + (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) + (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating addition.
  \details This function enables you to perform two unsigned 16-bit integer additions, saturating
           the results to the 16-bit unsigned integer range 0 < x < 2^16 - 1.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the saturated addition of the low halfwords, in the low halfword of the return value.\n
                 the saturated addition of the high halfwords, in the high halfword of the return value.\n
                 The results are saturated to the 16-bit unsigned integer range 0 < x < 2^16 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __UQADD16(uint32_t x, uint32_t y)
{
    int32_t r = 0, s = 0;

    r = __IUSAT((((x << 16) >> 16) + ((y << 16) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) + ((y) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed addition.
  \details This function enables you to perform two 16-bit signed integer additions.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the addition of the low halfwords in the low halfword of the return value.\n
                 the addition of the high halfwords in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __SADD16(uint32_t x, uint32_t y)
{
    int32_t r = 0, s = 0;

    r = ((((int32_t)x << 16) >> 16) + (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) + (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition
  \details This function enables you to perform two 16-bit unsigned integer additions.
  \param [in]    x   first two 16-bit summands for each addition.
  \param [in]    y   second two 16-bit summands for each addition.
  \return        the addition of the low halfwords in the low halfword of the return value.\n
                 the addition of the high halfwords in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __UADD16(uint32_t x, uint32_t y)
{
    int32_t r = 0, s = 0;

    r = (((x << 16) >> 16) + ((y << 16) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) + ((y) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}


/**
  \brief   Dual 16-bit signed addition with halved results.
  \details This function enables you to perform two signed 16-bit integer additions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved addition of the low halfwords, in the low halfword of the return value.\n
                 the halved addition of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[31:16]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __SHADD16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) + (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) + (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition with halved results.
  \details This function enables you to perform two unsigned 16-bit integer additions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved addition of the low halfwords, in the low halfword of the return value.\n
                 the halved addition of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[31:16]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __UHADD16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) + ((y << 16) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) + ((y) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Quad 8-bit signed addition with halved results.
  \details This function enables you to perform four signed 8-bit integer additions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved addition of the first bytes from each operand, in the first byte of the return value.\n
                 the halved addition of the second bytes from each operand, in the second byte of the return value.\n
                 the halved addition of the third bytes from each operand, in the third byte of the return value.\n
                 the halved addition of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   + val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  + val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] + val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] + val2[31:24]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __SHADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((((int32_t)x << 24) >> 24) + (((int32_t)y << 24) >> 24)) >> 1) & (int32_t)0x000000FF;
    s = (((((int32_t)x << 16) >> 24) + (((int32_t)y << 16) >> 24)) >> 1) & (int32_t)0x000000FF;
    t = (((((int32_t)x <<  8) >> 24) + (((int32_t)y <<  8) >> 24)) >> 1) & (int32_t)0x000000FF;
    u = (((((int32_t)x) >> 24) + (((int32_t)y) >> 24)) >> 1) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned addition with halved results.
  \details This function enables you to perform four unsigned 8-bit integer additions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved addition of the first bytes from each operand, in the first byte of the return value.\n
                 the halved addition of the second bytes from each operand, in the second byte of the return value.\n
                 the halved addition of the third bytes from each operand, in the third byte of the return value.\n
                 the halved addition of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   + val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  + val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] + val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] + val2[31:24]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __UHADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = ((((x << 24) >> 24) + ((y << 24) >> 24)) >> 1) & 0x000000FF;
    s = ((((x << 16) >> 24) + ((y << 16) >> 24)) >> 1) & 0x000000FF;
    t = ((((x <<  8) >> 24) + ((y <<  8) >> 24)) >> 1) & 0x000000FF;
    u = ((((x) >> 24) + ((y) >> 24)) >> 1) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Dual 16-bit saturating subtract.
  \details This function enables you to perform two 16-bit integer subtractions in parallel,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the saturated subtraction of the low halfwords, in the low halfword of the return value.\n
                 the saturated subtraction of the high halfwords, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __QSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __SSAT(((((int32_t)x << 16) >> 16) - (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) - (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating subtraction.
  \details This function enables you to perform two unsigned 16-bit integer subtractions,
           saturating the results to the 16-bit unsigned integer range 0 < x < 2^16 - 1.
  \param [in]    x   first two 16-bit operands for each subtraction.
  \param [in]    y   second two 16-bit operands for each subtraction.
  \return        the saturated subtraction of the low halfwords, in the low halfword of the return value.\n
                 the saturated subtraction of the high halfwords, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __UQSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __IUSAT((((x << 16) >> 16) - ((y << 16) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) - ((y) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed subtraction.
  \details This function enables you to perform two 16-bit signed integer subtractions.
  \param [in]    x   first two 16-bit operands of each subtraction.
  \param [in]    y   second two 16-bit operands of each subtraction.
  \return        the subtraction of the low halfword in the second operand from the low
                 halfword in the first operand, in the low halfword of the return value. \n
                 the subtraction of the high halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __SSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((int32_t)x << 16) >> 16) - (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) - (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned subtract.
  \details This function enables you to perform two 16-bit unsigned integer subtractions.
  \param [in]    x   first two 16-bit operands of each subtraction.
  \param [in]    y   second two 16-bit operands of each subtraction.
  \return        the subtraction of the low halfword in the second operand from the low
                 halfword in the first operand, in the low halfword of the return value. \n
                 the subtraction of the high halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __USUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((x << 16) >> 16) - ((y << 16) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) - ((y) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed subtraction with halved results.
  \details This function enables you to perform two signed 16-bit integer subtractions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved subtraction of the low halfwords, in the low halfword of the return value.\n
                 the halved subtraction of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[31:16]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __SHSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) - (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) - (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned subtraction with halved results.
  \details This function enables you to perform two unsigned 16-bit integer subtractions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved subtraction of the low halfwords, in the low halfword of the return value.\n
                 the halved subtraction of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[31:16]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __UHSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) - ((y << 16) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) - ((y) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Quad 8-bit signed addition with halved results.
  \details This function enables you to perform four signed 8-bit integer subtractions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the halved subtraction of the second bytes from each operand, in the second byte of the return value.\n
                 the halved subtraction of the third bytes from each operand, in the third byte of the return value.\n
                 the halved subtraction of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   - val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  - val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] - val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] - val2[31:24]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __SHSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((((int32_t)x << 24) >> 24) - (((int32_t)y << 24) >> 24)) >> 1) & (int32_t)0x000000FF;
    s = (((((int32_t)x << 16) >> 24) - (((int32_t)y << 16) >> 24)) >> 1) & (int32_t)0x000000FF;
    t = (((((int32_t)x <<  8) >> 24) - (((int32_t)y <<  8) >> 24)) >> 1) & (int32_t)0x000000FF;
    u = (((((int32_t)x) >> 24) - (((int32_t)y) >> 24)) >> 1) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned subtraction with halved results.
  \details This function enables you to perform four unsigned 8-bit integer subtractions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the halved subtraction of the second bytes from each operand, in the second byte of the return value.\n
                 the halved subtraction of the third bytes from each operand, in the third byte of the return value.\n
                 the halved subtraction of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   - val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  - val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] - val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] - val2[31:24]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __UHSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = ((((x << 24) >> 24) - ((y << 24) >> 24)) >> 1) & 0x000000FF;
    s = ((((x << 16) >> 24) - ((y << 16) >> 24)) >> 1) & 0x000000FF;
    t = ((((x <<  8) >> 24) - ((y <<  8) >> 24)) >> 1) & 0x000000FF;
    u = ((((x) >> 24) - ((y) >> 24)) >> 1) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Dual 16-bit add and subtract with exchange.
  \details This function enables you to exchange the halfwords of the one operand,
           then add the high halfwords and subtract the low halfwords,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the saturated subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the saturated addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __QASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __SSAT(((((int32_t)x << 16) >> 16) - (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) + (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating addition and subtraction with exchange.
  \details This function enables you to exchange the halfwords of the second operand and
           perform one unsigned 16-bit integer addition and one unsigned 16-bit subtraction,
           saturating the results to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the saturated subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the saturated addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __UQASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __IUSAT((((x << 16) >> 16) - ((y) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) + ((y << 16) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit addition and subtraction with exchange.
  \details It enables you to exchange the halfwords of the second operand, add the high halfwords
           and subtract the low halfwords.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((int32_t)x << 16) >> 16) - (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) + (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition and subtraction with exchange.
  \details This function enables you to exchange the two halfwords of the second operand,
           add the high halfwords and subtract the low halfwords.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __UASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((x << 16) >> 16) - ((y) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) + ((y << 16) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed addition and subtraction with halved results.
  \details This function enables you to exchange the two halfwords of one operand, perform one
           signed 16-bit integer addition and one signed 16-bit subtraction, and halve the results.
  \param [in]    x   first 16-bit operands.
  \param [in]    y   second 16-bit operands.
  \return        the halved subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the halved addition of the low halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[15:0]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __SHASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) - (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) + (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition and subtraction with halved results and exchange.
  \details This function enables you to exchange the halfwords of the second operand,
           add the high halfwords and subtract the low halfwords, halving the results.
  \param [in]    x   first operand for the subtraction in the low halfword, and
                     the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword, and
                     the second operand for the addition in the low halfword.
  \return        the halved subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the halved addition of the low halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[15:0]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __UHASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) - ((y) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) + ((y << 16) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit subtract and add with exchange.
  \details This function enables you to exchange the halfwords of one operand,
           then subtract the high halfwords and add the low halfwords,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first operand for the addition in the low halfword,
                     and the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword,
                     and the second operand for the subtraction in the low halfword.
  \return        the saturated addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the saturated subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __QSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __SSAT(((((int32_t)x << 16) >> 16) + (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) - (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating subtraction and addition with exchange.
  \details This function enables you to exchange the halfwords of the second operand and perform
           one unsigned 16-bit integer subtraction and one unsigned 16-bit addition, saturating
           the results to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \param [in]    x   first operand for the addition in the low halfword,
                     and the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword,
                     and the second operand for the subtraction in the low halfword.
  \return        the saturated addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the saturated subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __UQSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __IUSAT((((x << 16) >> 16) + ((y) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) - ((y << 16) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit unsigned subtract and add with exchange.
  \details This function enables you to exchange the halfwords of the second operand,
           subtract the high halfwords and add the low halfwords.
  \param [in]    x   first operand for the addition in the low halfword,
                     and the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword,
                     and the second operand for the subtraction in the low halfword.
  \return        the addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __USAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((x << 16) >> 16) + ((y) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) - ((y << 16) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed subtraction and addition with exchange.
  \details This function enables you to exchange the two halfwords of one operand and perform one
           16-bit integer subtraction and one 16-bit addition.
  \param [in]    x   first operand for the addition in the low halfword, and the first operand
                     for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword, and the second
                     operand for the subtraction in the low halfword.
  \return        the addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((int32_t)x << 16) >> 16) + (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) - (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}


/**
  \brief   Dual 16-bit signed subtraction and addition with halved results.
  \details This function enables you to exchange the two halfwords of one operand, perform one signed
           16-bit integer subtraction and one signed 16-bit addition, and halve the results.
  \param [in]    x   first 16-bit operands.
  \param [in]    y   second 16-bit operands.
  \return        the halved addition of the low halfword in the first operand and the
                 high halfword in the second operand, in the low halfword of the return value.\n
                 the halved subtraction of the low halfword in the second operand from the
                 high halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[15:0]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __SHSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) + (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) - (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned subtraction and addition with halved results and exchange.
  \details This function enables you to exchange the halfwords of the second operand,
           subtract the high halfwords and add the low halfwords, halving the results.
  \param [in]    x   first operand for the addition in the low halfword, and
                     the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword, and
                     the second operand for the subtraction in the low halfword.
  \return        the halved addition of the low halfword in the first operand and the
                 high halfword in the second operand, in the low halfword of the return value.\n
                 the halved subtraction of the low halfword in the second operand from the
                 high halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[15:0]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __UHSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) + ((y) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) - ((y << 16) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed multiply with exchange returning difference.
  \details This function enables you to perform two 16-bit signed multiplications, subtracting
           one of the products from the other. The halfwords of the second operand are exchanged
           before performing the arithmetic. This produces top * bottom and bottom * top multiplication.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the difference of the products of the two 16-bit signed multiplications.
  \remark
                 p1 = val1[15:0]  * val2[31:16]       \n
                 p2 = val1[31:16] * val2[15:0]        \n
                 res[31:0] = p1 - p2
 */
__ALWAYS_STATIC_INLINE uint32_t __SMUSDX(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16))));
}

/**
  \brief   Sum of dual 16-bit signed multiply with exchange.
  \details This function enables you to perform two 16-bit signed multiplications with exchanged
           halfwords of the second operand, adding the products together.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the sum of the products of the two 16-bit signed multiplications with exchanged halfwords of the second operand.
  \remark
                 p1 = val1[15:0]  * val2[31:16]       \n
                 p2 = val1[31:16] * val2[15:0]        \n
                 res[31:0] = p1 + p2
 */
__ALWAYS_STATIC_INLINE uint32_t __SMUADX(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16))));
}


/**
  \brief   Saturating add.
  \details This function enables you to obtain the saturating add of two integers.
  \param [in]    x   first summand of the saturating add operation.
  \param [in]    y   second summand of the saturating add operation.
  \return        the saturating addition of val1 and val2.
  \remark
                 res[31:0] = SAT(val1 + SAT(val2))
 */
__ALWAYS_STATIC_INLINE int32_t __QADD(int32_t x, int32_t y)
{
    int32_t result;

    if (y >= 0) {
        if (x + y >= x) {
            result = x + y;
        } else {
            result = 0x7FFFFFFF;
        }
    } else {
        if (x + y < x) {
            result = x + y;
        } else {
            result = 0x80000000;
        }
    }

    return result;
}

/**
  \brief   Saturating subtract.
  \details This function enables you to obtain the saturating add of two integers.
  \param [in]    x   first summand of the saturating add operation.
  \param [in]    y   second summand of the saturating add operation.
  \return        the saturating addition of val1 and val2.
  \remark
                 res[31:0] = SAT(val1 - SAT(val2))
 */
__ALWAYS_STATIC_INLINE int32_t __QSUB(int32_t x, int32_t y)
{
    int64_t tmp;
    int32_t result;

    tmp = (int64_t)x - (int64_t)y;

    if (tmp > 0x7fffffff) {
        tmp = 0x7fffffff;
    } else if (tmp < (-2147483647 - 1)) {
        tmp = -2147483647 - 1;
    }

    result = tmp;
    return result;
}

/**
  \brief   Dual 16-bit signed multiply with single 32-bit accumulator.
  \details This function enables you to perform two signed 16-bit multiplications,
           adding both results to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication added to the accumulate value, as a 32-bit integer.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[31:0] = p1 + p2 + val3[31:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SMLAD(uint32_t x, uint32_t y, uint32_t sum)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Pre-exchanged dual 16-bit signed multiply with single 32-bit accumulator.
  \details This function enables you to perform two signed 16-bit multiplications with exchanged
           halfwords of the second operand, adding both results to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication with exchanged halfwords of the second
                 operand added to the accumulate value, as a 32-bit integer.
  \remark
                 p1 = val1[15:0]  * val2[31:16]     \n
                 p2 = val1[31:16] * val2[15:0]      \n
                 res[31:0] = p1 + p2 + val3[31:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SMLADX(uint32_t x, uint32_t y, uint32_t sum)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange subtract with 32-bit accumulate.
  \details This function enables you to perform two 16-bit signed multiplications, take the
           difference of the products, subtracting the high halfword product from the low
           halfword product, and add the difference to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[15:0]       \n
                 p2 = val1[31:16] * val2[31:16]      \n
                 res[31:0] = p1 - p2 + val3[31:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SMLSD(uint32_t x, uint32_t y, uint32_t sum)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange subtract with 32-bit accumulate.
  \details This function enables you to exchange the halfwords in the second operand, then perform two 16-bit
           signed multiplications. The difference of the products is added to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[31:16]     \n
                 p2 = val1[31:16] * val2[15:0]      \n
                 res[31:0] = p1 - p2 + val3[31:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SMLSDX(uint32_t x, uint32_t y, uint32_t sum)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with single 64-bit accumulator.
  \details This function enables you to perform two signed 16-bit multiplications, adding both results
           to a 64-bit accumulate operand. Overflow is only possible as a result of the 64-bit addition.
           This overflow is not detected if it occurs. Instead, the result wraps around modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 sum = p1 + p2 + val3[63:32][31:0]  \n
                 res[63:32] = sum[63:32]            \n
                 res[31:0]  = sum[31:0]
 */
__ALWAYS_STATIC_INLINE uint64_t __SMLALD(uint32_t x, uint32_t y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange with single 64-bit accumulator.
  \details This function enables you to exchange the halfwords of the second operand, and perform two
           signed 16-bit multiplications, adding both results to a 64-bit accumulate operand. Overflow
           is only possible as a result of the 64-bit addition. This overflow is not detected if it occurs.
           Instead, the result wraps around modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[31:16]     \n
                 p2 = val1[31:16] * val2[15:0]      \n
                 sum = p1 + p2 + val3[63:32][31:0]  \n
                 res[63:32] = sum[63:32]            \n
                 res[31:0]  = sum[31:0]
 */
__ALWAYS_STATIC_INLINE uint64_t __SMLALDX(uint32_t x, uint32_t y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   dual 16-bit signed multiply subtract with 64-bit accumulate.
  \details This function It enables you to perform two 16-bit signed multiplications, take the difference
           of the products, subtracting the high halfword product from the low halfword product, and add the
           difference to a 64-bit accumulate operand. Overflow cannot occur during the multiplications or the
           subtraction. Overflow can occur as a result of the 64-bit addition, and this overflow is not
           detected. Instead, the result wraps round to modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[63:32][31:0] = p1 - p2 + val3[63:32][31:0]
 */
__ALWAYS_STATIC_INLINE uint64_t __SMLSLD(uint32_t x, uint32_t y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange subtract with 64-bit accumulate.
  \details This function enables you to exchange the halfwords of the second operand, perform two 16-bit multiplications,
           adding the difference of the products to a 64-bit accumulate operand. Overflow cannot occur during the
           multiplications or the subtraction. Overflow can occur as a result of the 64-bit addition, and this overflow
           is not detected. Instead, the result wraps round to modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[31:16]      \n
                 p2 = val1[31:16] * val2[15:0]       \n
                 res[63:32][31:0] = p1 - p2 + val3[63:32][31:0]
 */
__ALWAYS_STATIC_INLINE uint64_t __SMLSLDX(uint32_t x, uint32_t y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   32-bit signed multiply with 32-bit truncated accumulator.
  \details This function enables you to perform a signed 32-bit multiplications, adding the most
           significant 32 bits of the 64-bit result to a 32-bit accumulate operand.
  \param [in]    x   first operand for multiplication.
  \param [in]    y   second operand for multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of multiplication (most significant 32 bits) is added to the accumulate value, as a 32-bit integer.
  \remark
                 p = val1 * val2      \n
                 res[31:0] = p[63:32] + val3[31:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SMMLA(int32_t x, int32_t y, int32_t sum)
{
    return (uint32_t)((int32_t)((int64_t)((int64_t)x * (int64_t)y) >> 32) + sum);
}

/**
  \brief   Sum of dual 16-bit signed multiply.
  \details This function enables you to perform two 16-bit signed multiplications, adding the products together.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the sum of the products of the two 16-bit signed multiplications.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[31:0] = p1 + p2
 */
__ALWAYS_STATIC_INLINE uint32_t __SMUAD(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16))));
}

/**
  \brief   Dual 16-bit signed multiply returning difference.
  \details This function enables you to perform two 16-bit signed multiplications, taking the difference
           of the products by subtracting the high halfword product from the low halfword product.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the difference of the products of the two 16-bit signed multiplications.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[31:0] = p1 - p2
 */
__ALWAYS_STATIC_INLINE uint32_t __SMUSD(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16))));
}

/**
  \brief   Dual extracted 8-bit to 16-bit signed addition.
  \details This function enables you to extract two 8-bit values from the second operand (at bit positions
           [7:0] and [23:16]), sign-extend them to 16-bits each, and add the results to the first operand.
  \param [in]    x   values added to the sign-extended to 16-bit values.
  \param [in]    y   two 8-bit values to be extracted and sign-extended.
  \return        the addition of val1 and val2, where the 8-bit values in val2[7:0] and
                 val2[23:16] have been extracted and sign-extended prior to the addition.
  \remark
                 res[15:0]  = val1[15:0] + SignExtended(val2[7:0])      \n
                 res[31:16] = val1[31:16] + SignExtended(val2[23:16])
 */
__ALWAYS_STATIC_INLINE uint32_t __SXTAB16(uint32_t x, uint32_t y)
{
    return ((uint32_t)((((((int32_t)y << 24) >> 24) + (((int32_t)x << 16) >> 16)) & (int32_t)0x0000FFFF) |
                       (((((int32_t)y <<  8) >>  8)  + (((int32_t)x >> 16) << 16)) & (int32_t)0xFFFF0000)));
}

/**
  \brief   Extracted 16-bit to 32-bit unsigned addition.
  \details This function enables you to extract two 8-bit values from one operand, zero-extend
           them to 16 bits each, and add the results to two 16-bit values from another operand.
  \param [in]    x   values added to the zero-extended to 16-bit values.
  \param [in]    y   two 8-bit values to be extracted and zero-extended.
  \return        the addition of val1 and val2, where the 8-bit values in val2[7:0] and
                 val2[23:16] have been extracted and zero-extended prior to the addition.
  \remark
                 res[15:0]  = ZeroExt(val2[7:0]   to 16 bits) + val1[15:0]      \n
                 res[31:16] = ZeroExt(val2[31:16] to 16 bits) + val1[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __UXTAB16(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((y << 24) >> 24) + ((x << 16) >> 16)) & 0x0000FFFF) |
                       ((((y <<  8) >>  8) + ((x >> 16) << 16)) & 0xFFFF0000)));
}

/**
  \brief   Dual extract 8-bits and sign extend each to 16-bits.
  \details This function enables you to extract two 8-bit values from an operand and sign-extend them to 16 bits each.
  \param [in]    x   two 8-bit values in val[7:0] and val[23:16] to be sign-extended.
  \return        the 8-bit values sign-extended to 16-bit values.\n
                 sign-extended value of val[7:0] in the low halfword of the return value.\n
                 sign-extended value of val[23:16] in the high halfword of the return value.
  \remark
                 res[15:0]  = SignExtended(val[7:0])       \n
                 res[31:16] = SignExtended(val[23:16])
 */
__ALWAYS_STATIC_INLINE uint32_t __SXTB16(uint32_t x)
{
    return ((uint32_t)(((((int32_t)x << 24) >> 24) & (int32_t)0x0000FFFF) |
                       ((((int32_t)x <<  8) >>  8) & (int32_t)0xFFFF0000)));
}

/**
  \brief   Dual extract 8-bits and zero-extend to 16-bits.
  \details This function enables you to extract two 8-bit values from an operand and zero-extend them to 16 bits each.
  \param [in]    x   two 8-bit values in val[7:0] and val[23:16] to be zero-extended.
  \return        the 8-bit values sign-extended to 16-bit values.\n
                 sign-extended value of val[7:0] in the low halfword of the return value.\n
                 sign-extended value of val[23:16] in the high halfword of the return value.
  \remark
                 res[15:0]  = SignExtended(val[7:0])       \n
                 res[31:16] = SignExtended(val[23:16])
 */
__ALWAYS_STATIC_INLINE uint32_t __UXTB16(uint32_t x)
{
    return ((uint32_t)((((x << 24) >> 24) & 0x0000FFFF) |
                       (((x <<  8) >>  8) & 0xFFFF0000)));
}

#endif /* _CSI_GCC_H_ */
