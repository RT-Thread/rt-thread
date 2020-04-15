/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     csi_reg.h
 * @brief    CSI Header File for reg.
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CSI_REG_H_
#define _CSI_REG_H_

#include<csi_gcc.h>

/**
  \brief   Enable IRQ Interrupts
  \details Enables IRQ interrupts by setting the IE-bit in the PSR.
           Can only be executed in Privileged modes.
 */
__ALWAYS_INLINE void __enable_irq(void)
{
    __ASM volatile("psrset ie");
}



/**
  \brief   Disable IRQ Interrupts
  \details Disables IRQ interrupts by clearing the IE-bit in the PSR.
  Can only be executed in Privileged modes.
 */
__ALWAYS_INLINE void __disable_irq(void)
{
    __ASM volatile("psrclr ie");
}

/**
  \brief   Get PSR
  \details Returns the content of the PSR Register.
  \return               PSR Register value
 */
__ALWAYS_INLINE uint32_t __get_PSR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, psr" : "=r"(result));
    return (result);
}

/**
  \brief   Set PSR
  \details Writes the given value to the PSR Register.
  \param [in]    psr  PSR Register value to set
 */
__ALWAYS_INLINE void __set_PSR(uint32_t psr)
{
    __ASM volatile("mtcr %0, psr" : : "r"(psr));
}

/**
  \brief   Get SP
  \details Returns the content of the SP Register.
  \return               SP Register value
 */
__ALWAYS_INLINE uint32_t __get_SP(void)
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
__ALWAYS_INLINE void __set_SP(uint32_t sp)
{
    __ASM volatile("mov sp, %0" : : "r"(sp): "sp");
}


/**
  \brief   Get VBR Register
  \details Returns the content of the VBR Register.
  \return               VBR Register value
 */
__ALWAYS_INLINE uint32_t __get_VBR(void)
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
__ALWAYS_INLINE void __set_VBR(uint32_t vbr)
{
    __ASM volatile("mtcr %0, vbr" : : "r"(vbr));
}

/**
  \brief   Get EPC Register
  \details Returns the content of the EPC Register.
  \return               EPC Register value
 */
__ALWAYS_INLINE uint32_t __get_EPC(void)
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
__ALWAYS_INLINE void __set_EPC(uint32_t epc)
{
    __ASM volatile("mtcr %0, epc" : : "r"(epc));
}

/**
  \brief   Get EPSR
  \details Returns the content of the EPSR Register.
  \return               EPSR Register value
 */
__ALWAYS_INLINE uint32_t __get_EPSR(void)
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
__ALWAYS_INLINE void __set_EPSR(uint32_t epsr)
{
    __ASM volatile("mtcr %0, epsr" : : "r"(epsr));
}

/**
  \brief   Get CPUID Register
  \details Returns the content of the CPUID Register.
  \return               CPUID Register value
 */
__ALWAYS_INLINE uint32_t __get_CPUID(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<13, 0>" : "=r"(result));
    return (result);
}

#if       (__SOFTRESET_PRESENT == 1U)
/**
  \brief   Set SRCR
  \details Assigns the given value to the SRCR.
  \param [in]    srcr  SRCR value to set
 */
__ALWAYS_INLINE void __set_SRCR(uint32_t srcr)
{
    __ASM volatile("mtcr %0, cr<31, 0>\n" : : "r"(srcr));
}
#endif /* __SOFTRESET_PRESENT == 1U */

#if       (__MGU_PRESENT == 1U)
/**
  \brief   Get CCR
  \details Returns the current value of the CCR.
  \return               CCR Register value
 */
__ALWAYS_INLINE uint32_t __get_CCR(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<18, 0>\n"  : "=r"(result));
    return (result);
}


/**
  \brief   Set CCR
  \details Assigns the given value to the CCR.
  \param [in]    ccr  CCR value to set
 */
__ALWAYS_INLINE void __set_CCR(uint32_t ccr)
{
    __ASM volatile("mtcr %0, cr<18, 0>\n" : : "r"(ccr));
}


/**
  \brief   Get CAPR
  \details Returns the current value of the CAPR.
  \return               CAPR Register value
 */
__ALWAYS_INLINE uint32_t __get_CAPR(void)
{
    register uint32_t result;

    __ASM volatile("mfcr %0, cr<19, 0>\n" : "=r"(result));
    return (result);
}

/**
  \brief   Set CAPR
  \details Assigns the given value to the CAPR.
  \param [in]    capr  CAPR value to set
 */
__ALWAYS_INLINE void __set_CAPR(uint32_t capr)
{
    __ASM volatile("mtcr %0, cr<19, 0>\n" : : "r"(capr));
}


/**
  \brief   Set PACR
  \details Assigns the given value to the PACR.

    \param [in]    pacr  PACR value to set
 */
__ALWAYS_INLINE void __set_PACR(uint32_t pacr)
{
    __ASM volatile("mtcr %0, cr<20, 0>\n" : : "r"(pacr));
}


/**
  \brief   Get PACR
  \details Returns the current value of PACR.
  \return               PACR value
 */
__ALWAYS_INLINE uint32_t __get_PACR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<20, 0>" : "=r"(result));
    return (result);
}

/**
  \brief   Set PRSR
  \details Assigns the given value to the PRSR.

    \param [in]    prsr  PRSR value to set
 */
__ALWAYS_INLINE void __set_PRSR(uint32_t prsr)
{
    __ASM volatile("mtcr %0, cr<21, 0>\n" : : "r"(prsr));
}

/**
  \brief   Get PRSR
  \details Returns the current value of PRSR.
  \return               PRSR value
 */
__ALWAYS_INLINE uint32_t __get_PRSR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<21, 0>" : "=r"(result));
    return (result);
}
#endif /* __MGU_PRESENT == 1U */

/**
  \brief   Get user sp
  \details Returns the current value of user r14.
  \return               UR14 value
 */
__ALWAYS_INLINE uint32_t __get_UR14(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<14, 1>" : "=r"(result));
    return (result);
}

/**
  \brief   Enable interrupts and exceptions
  \details Enables interrupts and exceptions by setting the IE-bit and EE-bit in the PSR.
           Can only be executed in Privileged modes.
 */
__ALWAYS_INLINE void __enable_excp_irq(void)
{
    __ASM volatile("psrset ee, ie");
}


/**
  \brief   Disable interrupts and exceptions
  \details Disables interrupts and exceptions by clearing the IE-bit and EE-bit in the PSR.
           Can only be executed in Privileged modes.
 */
__ALWAYS_INLINE void __disable_excp_irq(void)
{
    __ASM volatile("psrclr ee, ie");
}

#if       (__GSR_GCR_PRESENT == 1U)
/**
  \brief   Get GSR
  \details Returns the content of the GSR Register.
  \return               GSR Register value
 */
__ALWAYS_INLINE uint32_t __get_GSR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<12, 0>" : "=r"(result));
    return (result);
}

/**
  \brief   Get GCR
  \details Returns the content of the GCR Register.
  \return               GCR Register value
 */
__ALWAYS_INLINE uint32_t __get_GCR(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<11, 0>" : "=r"(result));
    return (result);
}

/**
  \brief   Set GCR
  \details Writes the given value to the GCR Register.
  \param [in]    gcr  GCR Register value to set
 */
__ALWAYS_INLINE void __set_GCR(uint32_t gcr)
{
    __ASM volatile("mtcr %0, cr<11, 0>" : : "r"(gcr));
}

#endif /* (__GSR_GCR_PRESENT == 1U) */


#endif /* _CSI_REG_H_ */
