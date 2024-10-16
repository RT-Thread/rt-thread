/*
** ###################################################################
**     Processor:           S32K344_M7
**     Reference manual:    S32K3xx RM Rev.2. Draft B
**     Version:             rev. 1.6, 2020-03-02
**     Build:               b210302
**
**     Abstract:
**         Peripheral Access Layer for S32K344_M7
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2021 NXP
**
**     NXP Confidential. This software is owned or controlled by NXP and may only be
**     used strictly in accordance with the applicable license terms. By expressly
**     accepting such terms or by downloading, installing, activating and/or otherwise
**     using the software, you are agreeing that you have read, and that you agree to
**     comply with and are bound by, such license terms. If you do not agree to be
**     bound by the applicable license terms, then you may not retain, install,
**     activate or otherwise use the software. The production use license in
**     Section 2.3 is expressly granted for this software.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
** ###################################################################
*/

/*!
 * @file S32K344_MPU.h
 * @version 1.5
 * @date 2020-11-11
 * @brief Peripheral Access Layer for S32K344_MPU
 *
 * This file contains register definitions and macros for easy access to their
 * bit fields.
 *
 * This file assumes LITTLE endian system.
 */

/**
* @page misra_violations MISRA-C:2012 violations
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.3, local typedef not referenced
* The SoC header defines typedef for all modules.
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.5, local macro not referenced
* The SoC header defines macros for all modules and registers.
*
* @section [global]
* Violates MISRA 2012 Advisory Directive 4.9, Function-like macro
* These are generated macros used for accessing the bit-fields from registers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.1, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.2, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.4, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.5, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 21.1, defined macro '__I' is reserved to the compiler
* This type qualifier is needed to ensure correct I/O access and addressing.
*/

/* Prevention from multiple including the same memory map */
#if !defined(S32K344_MPU_H_)  /* Check if memory map has not been already included */
#define S32K344_MPU_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- S32_MPU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup S32_MPU_Peripheral_Access_Layer S32_MPU Peripheral Access Layer
 */
/** S32_MPU - Size of Registers Arrays */
#define S32_MPU_A_COUNT                          3u

/** S32_MPU - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[3472];
  __I  uint32_t TYPE;                              /**< MPU Type Register, offset: 0xD90 */
  __IO uint32_t CTRL;                              /**< MPU Control Register, offset: 0xD94 */
  __IO uint32_t RNR;                               /**< MPU Region Number Register, offset: 0xD98 */
  __IO uint32_t RBAR;                              /**< MPU Region Base Address Register, offset: 0xD9C */
  __IO uint32_t RASR;                              /**< MPU Region Attribute and Size Register, offset: 0xDA0 */
  struct {                                         /* offset: 0xDA4, array step: 0x8 */
    __IO uint32_t RBAR;                              /**< Alias of RBAR0..Alias of RBAR2, array offset: 0xDA4, array step: 0x8 */
    __IO uint32_t RASR;                              /**< Alias of RASR0..Alias of RASR2, array offset: 0xDA8, array step: 0x8 */
  } A[S32_MPU_A_COUNT];
} S32_MPU_Type, *S32_MPU_MemMapPtr;

 /** Number of instances of the S32_MPU module. */
#define S32_MPU_INSTANCE_COUNT                   (1u)

/* S32_MPU - Peripheral instance base addresses */
/** Peripheral S32_MPU base address */
#define S32_MPU_BASE                             (0xE000E000u)
/** Peripheral S32_MPU base pointer */
#define S32_MPU                                  ((S32_MPU_Type *)S32_MPU_BASE)
/** Array initializer of S32_MPU peripheral base addresses */
#define S32_MPU_BASE_ADDRS                       { S32_MPU_BASE }
/** Array initializer of S32_MPU peripheral base pointers */
#define S32_MPU_BASE_PTRS                        { S32_MPU }

/* ----------------------------------------------------------------------------
   -- S32_MPU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup S32_MPU_Register_Masks S32_MPU Register Masks
 * @{
 */

/* TYPE Bit Fields */
#define S32_MPU_TYPE_SEPARATE_MASK               0x1u
#define S32_MPU_TYPE_SEPARATE_SHIFT              0u
#define S32_MPU_TYPE_SEPARATE_WIDTH              1u
#define S32_MPU_TYPE_SEPARATE(x)                 (((uint32_t)(((uint32_t)(x))<<S32_MPU_TYPE_SEPARATE_SHIFT))&S32_MPU_TYPE_SEPARATE_MASK)
#define S32_MPU_TYPE_DREGION_MASK                0xFF00u
#define S32_MPU_TYPE_DREGION_SHIFT               8u
#define S32_MPU_TYPE_DREGION_WIDTH               8u
#define S32_MPU_TYPE_DREGION(x)                  (((uint32_t)(((uint32_t)(x))<<S32_MPU_TYPE_DREGION_SHIFT))&S32_MPU_TYPE_DREGION_MASK)
#define S32_MPU_TYPE_IREGION_MASK                0xFF0000u
#define S32_MPU_TYPE_IREGION_SHIFT               16u
#define S32_MPU_TYPE_IREGION_WIDTH               8u
#define S32_MPU_TYPE_IREGION(x)                  (((uint32_t)(((uint32_t)(x))<<S32_MPU_TYPE_IREGION_SHIFT))&S32_MPU_TYPE_IREGION_MASK)
/* CTRL Bit Fields */
#define S32_MPU_CTRL_ENABLE_MASK                 0x1u
#define S32_MPU_CTRL_ENABLE_SHIFT                0u
#define S32_MPU_CTRL_ENABLE_WIDTH                1u
#define S32_MPU_CTRL_ENABLE(x)                   (((uint32_t)(((uint32_t)(x))<<S32_MPU_CTRL_ENABLE_SHIFT))&S32_MPU_CTRL_ENABLE_MASK)
#define S32_MPU_CTRL_HFNMIENA_MASK               0x2u
#define S32_MPU_CTRL_HFNMIENA_SHIFT              1u
#define S32_MPU_CTRL_HFNMIENA_WIDTH              1u
#define S32_MPU_CTRL_HFNMIENA(x)                 (((uint32_t)(((uint32_t)(x))<<S32_MPU_CTRL_HFNMIENA_SHIFT))&S32_MPU_CTRL_HFNMIENA_MASK)
#define S32_MPU_CTRL_PRIVDEFENA_MASK             0x4u
#define S32_MPU_CTRL_PRIVDEFENA_SHIFT            2u
#define S32_MPU_CTRL_PRIVDEFENA_WIDTH            1u
#define S32_MPU_CTRL_PRIVDEFENA(x)               (((uint32_t)(((uint32_t)(x))<<S32_MPU_CTRL_PRIVDEFENA_SHIFT))&S32_MPU_CTRL_PRIVDEFENA_MASK)
/* RNR Bit Fields */
#define S32_MPU_RNR_REGION_MASK                  0xFFu
#define S32_MPU_RNR_REGION_SHIFT                 0u
#define S32_MPU_RNR_REGION_WIDTH                 8u
#define S32_MPU_RNR_REGION(x)                    (((uint32_t)(((uint32_t)(x))<<S32_MPU_RNR_REGION_SHIFT))&S32_MPU_RNR_REGION_MASK)
/* RBAR Bit Fields */
#define S32_MPU_RBAR_REGION_MASK                 0xFu
#define S32_MPU_RBAR_REGION_SHIFT                0u
#define S32_MPU_RBAR_REGION_WIDTH                4u
#define S32_MPU_RBAR_REGION(x)                   (((uint32_t)(((uint32_t)(x))<<S32_MPU_RBAR_REGION_SHIFT))&S32_MPU_RBAR_REGION_MASK)
#define S32_MPU_RBAR_VALID_MASK                  0x10u
#define S32_MPU_RBAR_VALID_SHIFT                 4u
#define S32_MPU_RBAR_VALID_WIDTH                 1u
#define S32_MPU_RBAR_VALID(x)                    (((uint32_t)(((uint32_t)(x))<<S32_MPU_RBAR_VALID_SHIFT))&S32_MPU_RBAR_VALID_MASK)
#define S32_MPU_RBAR_ADDR_MASK                   0xFFFFFFE0u
#define S32_MPU_RBAR_ADDR_SHIFT                  5u
#define S32_MPU_RBAR_ADDR_WIDTH                  27u
#define S32_MPU_RBAR_ADDR(x)                     (((uint32_t)(((uint32_t)(x))<<S32_MPU_RBAR_ADDR_SHIFT))&S32_MPU_RBAR_ADDR_MASK)
/* RASR Bit Fields */
#define S32_MPU_RASR_ENABLE_MASK                 0x1u
#define S32_MPU_RASR_ENABLE_SHIFT                0u
#define S32_MPU_RASR_ENABLE_WIDTH                1u
#define S32_MPU_RASR_ENABLE(x)                   (((uint32_t)(((uint32_t)(x))<<S32_MPU_RASR_ENABLE_SHIFT))&S32_MPU_RASR_ENABLE_MASK)
#define S32_MPU_RASR_SIZE_MASK                   0x3Eu
#define S32_MPU_RASR_SIZE_SHIFT                  1u
#define S32_MPU_RASR_SIZE_WIDTH                  5u
#define S32_MPU_RASR_SIZE(x)                     (((uint32_t)(((uint32_t)(x))<<S32_MPU_RASR_SIZE_SHIFT))&S32_MPU_RASR_SIZE_MASK)
#define S32_MPU_RASR_SRD_MASK                    0xFF00u
#define S32_MPU_RASR_SRD_SHIFT                   8u
#define S32_MPU_RASR_SRD_WIDTH                   8u
#define S32_MPU_RASR_SRD(x)                      (((uint32_t)(((uint32_t)(x))<<S32_MPU_RASR_SRD_SHIFT))&S32_MPU_RASR_SRD_MASK)
#define S32_MPU_RASR_B_MASK                      0x10000u
#define S32_MPU_RASR_B_SHIFT                     16u
#define S32_MPU_RASR_B_WIDTH                     1u
#define S32_MPU_RASR_B(x)                        (((uint32_t)(((uint32_t)(x))<<S32_MPU_RASR_B_SHIFT))&S32_MPU_RASR_B_MASK)
#define S32_MPU_RASR_C_MASK                      0x20000u
#define S32_MPU_RASR_C_SHIFT                     17u
#define S32_MPU_RASR_C_WIDTH                     1u
#define S32_MPU_RASR_C(x)                        (((uint32_t)(((uint32_t)(x))<<S32_MPU_RASR_C_SHIFT))&S32_MPU_RASR_C_MASK)
#define S32_MPU_RASR_S_MASK                      0x40000u
#define S32_MPU_RASR_S_SHIFT                     18u
#define S32_MPU_RASR_S_WIDTH                     1u
#define S32_MPU_RASR_S(x)                        (((uint32_t)(((uint32_t)(x))<<S32_MPU_RASR_S_SHIFT))&S32_MPU_RASR_S_MASK)
#define S32_MPU_RASR_TEX_MASK                    0x380000u
#define S32_MPU_RASR_TEX_SHIFT                   19u
#define S32_MPU_RASR_TEX_WIDTH                   3u
#define S32_MPU_RASR_TEX(x)                      (((uint32_t)(((uint32_t)(x))<<S32_MPU_RASR_TEX_SHIFT))&S32_MPU_RASR_TEX_MASK)
#define S32_MPU_RASR_AP_MASK                     0x7000000u
#define S32_MPU_RASR_AP_SHIFT                    24u
#define S32_MPU_RASR_AP_WIDTH                    3u
#define S32_MPU_RASR_AP(x)                       (((uint32_t)(((uint32_t)(x))<<S32_MPU_RASR_AP_SHIFT))&S32_MPU_RASR_AP_MASK)
#define S32_MPU_RASR_XN_MASK                     0x10000000u
#define S32_MPU_RASR_XN_SHIFT                    28u
#define S32_MPU_RASR_XN_WIDTH                    1u
#define S32_MPU_RASR_XN(x)                       (((uint32_t)(((uint32_t)(x))<<S32_MPU_RASR_XN_SHIFT))&S32_MPU_RASR_XN_MASK)
/* A_RBAR Bit Fields */
#define S32_MPU_A_RBAR_REGION_MASK               0xFu
#define S32_MPU_A_RBAR_REGION_SHIFT              0u
#define S32_MPU_A_RBAR_REGION_WIDTH              4u
#define S32_MPU_A_RBAR_REGION(x)                 (((uint32_t)(((uint32_t)(x))<<S32_MPU_A_RBAR_REGION_SHIFT))&S32_MPU_A_RBAR_REGION_MASK)
#define S32_MPU_A_RBAR_VALID_MASK                0x10u
#define S32_MPU_A_RBAR_VALID_SHIFT               4u
#define S32_MPU_A_RBAR_VALID_WIDTH               1u
#define S32_MPU_A_RBAR_VALID(x)                  (((uint32_t)(((uint32_t)(x))<<S32_MPU_A_RBAR_VALID_SHIFT))&S32_MPU_A_RBAR_VALID_MASK)
#define S32_MPU_A_RBAR_ADDR_MASK                 0xFFFFFFE0u
#define S32_MPU_A_RBAR_ADDR_SHIFT                5u
#define S32_MPU_A_RBAR_ADDR_WIDTH                27u
#define S32_MPU_A_RBAR_ADDR(x)                   (((uint32_t)(((uint32_t)(x))<<S32_MPU_A_RBAR_ADDR_SHIFT))&S32_MPU_A_RBAR_ADDR_MASK)
/* A_RASR Bit Fields */
#define S32_MPU_A_RASR_ENABLE_MASK               0x1u
#define S32_MPU_A_RASR_ENABLE_SHIFT              0u
#define S32_MPU_A_RASR_ENABLE_WIDTH              1u
#define S32_MPU_A_RASR_ENABLE(x)                 (((uint32_t)(((uint32_t)(x))<<S32_MPU_A_RASR_ENABLE_SHIFT))&S32_MPU_A_RASR_ENABLE_MASK)
#define S32_MPU_A_RASR_SIZE_MASK                 0x3Eu
#define S32_MPU_A_RASR_SIZE_SHIFT                1u
#define S32_MPU_A_RASR_SIZE_WIDTH                5u
#define S32_MPU_A_RASR_SIZE(x)                   (((uint32_t)(((uint32_t)(x))<<S32_MPU_A_RASR_SIZE_SHIFT))&S32_MPU_A_RASR_SIZE_MASK)
#define S32_MPU_A_RASR_SRD_MASK                  0xFF00u
#define S32_MPU_A_RASR_SRD_SHIFT                 8u
#define S32_MPU_A_RASR_SRD_WIDTH                 8u
#define S32_MPU_A_RASR_SRD(x)                    (((uint32_t)(((uint32_t)(x))<<S32_MPU_A_RASR_SRD_SHIFT))&S32_MPU_A_RASR_SRD_MASK)
#define S32_MPU_A_RASR_B_MASK                    0x10000u
#define S32_MPU_A_RASR_B_SHIFT                   16u
#define S32_MPU_A_RASR_B_WIDTH                   1u
#define S32_MPU_A_RASR_B(x)                      (((uint32_t)(((uint32_t)(x))<<S32_MPU_A_RASR_B_SHIFT))&S32_MPU_A_RASR_B_MASK)
#define S32_MPU_A_RASR_C_MASK                    0x20000u
#define S32_MPU_A_RASR_C_SHIFT                   17u
#define S32_MPU_A_RASR_C_WIDTH                   1u
#define S32_MPU_A_RASR_C(x)                      (((uint32_t)(((uint32_t)(x))<<S32_MPU_A_RASR_C_SHIFT))&S32_MPU_A_RASR_C_MASK)
#define S32_MPU_A_RASR_S_MASK                    0x40000u
#define S32_MPU_A_RASR_S_SHIFT                   18u
#define S32_MPU_A_RASR_S_WIDTH                   1u
#define S32_MPU_A_RASR_S(x)                      (((uint32_t)(((uint32_t)(x))<<S32_MPU_A_RASR_S_SHIFT))&S32_MPU_A_RASR_S_MASK)
#define S32_MPU_A_RASR_TEX_MASK                  0x380000u
#define S32_MPU_A_RASR_TEX_SHIFT                 19u
#define S32_MPU_A_RASR_TEX_WIDTH                 3u
#define S32_MPU_A_RASR_TEX(x)                    (((uint32_t)(((uint32_t)(x))<<S32_MPU_A_RASR_TEX_SHIFT))&S32_MPU_A_RASR_TEX_MASK)
#define S32_MPU_A_RASR_AP_MASK                   0x7000000u
#define S32_MPU_A_RASR_AP_SHIFT                  24u
#define S32_MPU_A_RASR_AP_WIDTH                  3u
#define S32_MPU_A_RASR_AP(x)                     (((uint32_t)(((uint32_t)(x))<<S32_MPU_A_RASR_AP_SHIFT))&S32_MPU_A_RASR_AP_MASK)
#define S32_MPU_A_RASR_XN_MASK                   0x10000000u
#define S32_MPU_A_RASR_XN_SHIFT                  28u
#define S32_MPU_A_RASR_XN_WIDTH                  1u
#define S32_MPU_A_RASR_XN(x)                     (((uint32_t)(((uint32_t)(x))<<S32_MPU_A_RASR_XN_SHIFT))&S32_MPU_A_RASR_XN_MASK)

/*!
 * @}
 */ /* end of group S32_MPU_Register_Masks */

/*!
 * @}
 */ /* end of group S32_MPU_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_MPU_H_) */
