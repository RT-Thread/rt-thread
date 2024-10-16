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
 * @file S32K344_NVIC.h
 * @version 1.5
 * @date 2020-11-11
 * @brief Peripheral Access Layer for S32K344_NVIC
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
#if !defined(S32K344_NVIC_H_)  /* Check if memory map has not been already included */
#define S32K344_NVIC_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- S32_NVIC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup S32_NVIC_Peripheral_Access_Layer S32_NVIC Peripheral Access Layer
 * @{
 */

/** S32_NVIC - Size of Registers Arrays */
#define S32_NVIC_ISER_COUNT                      8u
#define S32_NVIC_ICER_COUNT                      8u
#define S32_NVIC_ISPR_COUNT                      8u
#define S32_NVIC_ICPR_COUNT                      8u
#define S32_NVIC_IABR_COUNT                      8u
#define S32_NVIC_IP_COUNT                        240u

/** S32_NVIC - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[4];
  __I  uint32_t ICTR;                              /**< Interrupt Control Type Register, offset: 0x4 */
       uint8_t RESERVED_1[248];
  __IO uint32_t ISER[S32_NVIC_ISER_COUNT];         /**< Interrupt Set Enable Register n, array offset: 0x100, array step: 0x4 */
       uint8_t RESERVED_2[96];
  __IO uint32_t ICER[S32_NVIC_ICER_COUNT];         /**< Interrupt Clear Enable Register n, array offset: 0x180, array step: 0x4 */
       uint8_t RESERVED_3[96];
  __IO uint32_t ISPR[S32_NVIC_ISPR_COUNT];         /**< Interrupt Set Pending Register n, array offset: 0x200, array step: 0x4 */
       uint8_t RESERVED_4[96];
  __IO uint32_t ICPR[S32_NVIC_ICPR_COUNT];         /**< Interrupt Clear Pending Register n, array offset: 0x280, array step: 0x4 */
       uint8_t RESERVED_5[96];
  __IO uint32_t IABR[S32_NVIC_IABR_COUNT];         /**< Interrupt Active bit Register n, array offset: 0x300, array step: 0x4 */
       uint8_t RESERVED_6[224];
  __IO uint8_t IP[S32_NVIC_IP_COUNT];              /**< Interrupt Priority Register n, array offset: 0x400, array step: 0x1 */
       uint8_t RESERVED_7[2576];
  __O  uint32_t STIR;                              /**< Software Trigger Interrupt Register, offset: 0xF00 */
} S32_NVIC_Type, *S32_NVIC_MemMapPtr;

 /** Number of instances of the S32_NVIC module. */
#define S32_NVIC_INSTANCE_COUNT                  (1u)

/* S32_NVIC - Peripheral instance base addresses */
/** Peripheral S32_NVIC base address */
#define S32_NVIC_BASE                            (0xE000E000u)
/** Peripheral S32_NVIC base pointer */
#define S32_NVIC                                 ((S32_NVIC_Type *)S32_NVIC_BASE)
/** Array initializer of S32_NVIC peripheral base addresses */
#define S32_NVIC_BASE_ADDRS                      { S32_NVIC_BASE }
/** Array initializer of S32_NVIC peripheral base pointers */
#define S32_NVIC_BASE_PTRS                       { S32_NVIC }

/* ----------------------------------------------------------------------------
   -- S32_NVIC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup S32_NVIC_Register_Masks S32_NVIC Register Masks
 * @{
 */

/* ICTR Bit Fields */
#define S32_NVIC_ICTR_ICTR_MASK                  0xFFFFFFFFu
#define S32_NVIC_ICTR_ICTR_SHIFT                 0u
#define S32_NVIC_ICTR_ICTR_WIDTH                 32u
#define S32_NVIC_ICTR_ICTR(x)                    (((uint32_t)(((uint32_t)(x))<<S32_NVIC_ICTR_ICTR_SHIFT))&S32_NVIC_ICTR_ICTR_MASK)
/* ISER Bit Fields */
#define S32_NVIC_ISER_SETENA_MASK                0xFFFFFFFFu
#define S32_NVIC_ISER_SETENA_SHIFT               0u
#define S32_NVIC_ISER_SETENA_WIDTH               32u
#define S32_NVIC_ISER_SETENA(x)                  (((uint32_t)(((uint32_t)(x))<<S32_NVIC_ISER_SETENA_SHIFT))&S32_NVIC_ISER_SETENA_MASK)
/* ICER Bit Fields */
#define S32_NVIC_ICER_CLRENA_MASK                0xFFFFFFFFu
#define S32_NVIC_ICER_CLRENA_SHIFT               0u
#define S32_NVIC_ICER_CLRENA_WIDTH               32u
#define S32_NVIC_ICER_CLRENA(x)                  (((uint32_t)(((uint32_t)(x))<<S32_NVIC_ICER_CLRENA_SHIFT))&S32_NVIC_ICER_CLRENA_MASK)
/* ISPR Bit Fields */
#define S32_NVIC_ISPR_SETPEND_MASK               0xFFFFFFFFu
#define S32_NVIC_ISPR_SETPEND_SHIFT              0u
#define S32_NVIC_ISPR_SETPEND_WIDTH              32u
#define S32_NVIC_ISPR_SETPEND(x)                 (((uint32_t)(((uint32_t)(x))<<S32_NVIC_ISPR_SETPEND_SHIFT))&S32_NVIC_ISPR_SETPEND_MASK)
/* ICPR Bit Fields */
#define S32_NVIC_ICPR_CLRPEND_MASK               0xFFFFFFFFu
#define S32_NVIC_ICPR_CLRPEND_SHIFT              0u
#define S32_NVIC_ICPR_CLRPEND_WIDTH              32u
#define S32_NVIC_ICPR_CLRPEND(x)                 (((uint32_t)(((uint32_t)(x))<<S32_NVIC_ICPR_CLRPEND_SHIFT))&S32_NVIC_ICPR_CLRPEND_MASK)
/* IABR Bit Fields */
#define S32_NVIC_IABR_ACTIVE_MASK                0xFFFFFFFFu
#define S32_NVIC_IABR_ACTIVE_SHIFT               0u
#define S32_NVIC_IABR_ACTIVE_WIDTH               32u
#define S32_NVIC_IABR_ACTIVE(x)                  (((uint32_t)(((uint32_t)(x))<<S32_NVIC_IABR_ACTIVE_SHIFT))&S32_NVIC_IABR_ACTIVE_MASK)
/* IP Bit Fields */
#define S32_NVIC_IP_PRI0_MASK                    0xFFu
#define S32_NVIC_IP_PRI0_SHIFT                   0u
#define S32_NVIC_IP_PRI0_WIDTH                   8u
#define S32_NVIC_IP_PRI0(x)                      (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI0_SHIFT))&S32_NVIC_IP_PRI0_MASK)
#define S32_NVIC_IP_PRI1_MASK                    0xFFu
#define S32_NVIC_IP_PRI1_SHIFT                   0u
#define S32_NVIC_IP_PRI1_WIDTH                   8u
#define S32_NVIC_IP_PRI1(x)                      (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI1_SHIFT))&S32_NVIC_IP_PRI1_MASK)
#define S32_NVIC_IP_PRI2_MASK                    0xFFu
#define S32_NVIC_IP_PRI2_SHIFT                   0u
#define S32_NVIC_IP_PRI2_WIDTH                   8u
#define S32_NVIC_IP_PRI2(x)                      (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI2_SHIFT))&S32_NVIC_IP_PRI2_MASK)
#define S32_NVIC_IP_PRI3_MASK                    0xFFu
#define S32_NVIC_IP_PRI3_SHIFT                   0u
#define S32_NVIC_IP_PRI3_WIDTH                   8u
#define S32_NVIC_IP_PRI3(x)                      (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI3_SHIFT))&S32_NVIC_IP_PRI3_MASK)
#define S32_NVIC_IP_PRI4_MASK                    0xFFu
#define S32_NVIC_IP_PRI4_SHIFT                   0u
#define S32_NVIC_IP_PRI4_WIDTH                   8u
#define S32_NVIC_IP_PRI4(x)                      (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI4_SHIFT))&S32_NVIC_IP_PRI4_MASK)
#define S32_NVIC_IP_PRI5_MASK                    0xFFu
#define S32_NVIC_IP_PRI5_SHIFT                   0u
#define S32_NVIC_IP_PRI5_WIDTH                   8u
#define S32_NVIC_IP_PRI5(x)                      (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI5_SHIFT))&S32_NVIC_IP_PRI5_MASK)
#define S32_NVIC_IP_PRI6_MASK                    0xFFu
#define S32_NVIC_IP_PRI6_SHIFT                   0u
#define S32_NVIC_IP_PRI6_WIDTH                   8u
#define S32_NVIC_IP_PRI6(x)                      (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI6_SHIFT))&S32_NVIC_IP_PRI6_MASK)
#define S32_NVIC_IP_PRI7_MASK                    0xFFu
#define S32_NVIC_IP_PRI7_SHIFT                   0u
#define S32_NVIC_IP_PRI7_WIDTH                   8u
#define S32_NVIC_IP_PRI7(x)                      (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI7_SHIFT))&S32_NVIC_IP_PRI7_MASK)
#define S32_NVIC_IP_PRI8_MASK                    0xFFu
#define S32_NVIC_IP_PRI8_SHIFT                   0u
#define S32_NVIC_IP_PRI8_WIDTH                   8u
#define S32_NVIC_IP_PRI8(x)                      (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI8_SHIFT))&S32_NVIC_IP_PRI8_MASK)
#define S32_NVIC_IP_PRI9_MASK                    0xFFu
#define S32_NVIC_IP_PRI9_SHIFT                   0u
#define S32_NVIC_IP_PRI9_WIDTH                   8u
#define S32_NVIC_IP_PRI9(x)                      (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI9_SHIFT))&S32_NVIC_IP_PRI9_MASK)
#define S32_NVIC_IP_PRI10_MASK                   0xFFu
#define S32_NVIC_IP_PRI10_SHIFT                  0u
#define S32_NVIC_IP_PRI10_WIDTH                  8u
#define S32_NVIC_IP_PRI10(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI10_SHIFT))&S32_NVIC_IP_PRI10_MASK)
#define S32_NVIC_IP_PRI11_MASK                   0xFFu
#define S32_NVIC_IP_PRI11_SHIFT                  0u
#define S32_NVIC_IP_PRI11_WIDTH                  8u
#define S32_NVIC_IP_PRI11(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI11_SHIFT))&S32_NVIC_IP_PRI11_MASK)
#define S32_NVIC_IP_PRI12_MASK                   0xFFu
#define S32_NVIC_IP_PRI12_SHIFT                  0u
#define S32_NVIC_IP_PRI12_WIDTH                  8u
#define S32_NVIC_IP_PRI12(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI12_SHIFT))&S32_NVIC_IP_PRI12_MASK)
#define S32_NVIC_IP_PRI13_MASK                   0xFFu
#define S32_NVIC_IP_PRI13_SHIFT                  0u
#define S32_NVIC_IP_PRI13_WIDTH                  8u
#define S32_NVIC_IP_PRI13(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI13_SHIFT))&S32_NVIC_IP_PRI13_MASK)
#define S32_NVIC_IP_PRI14_MASK                   0xFFu
#define S32_NVIC_IP_PRI14_SHIFT                  0u
#define S32_NVIC_IP_PRI14_WIDTH                  8u
#define S32_NVIC_IP_PRI14(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI14_SHIFT))&S32_NVIC_IP_PRI14_MASK)
#define S32_NVIC_IP_PRI15_MASK                   0xFFu
#define S32_NVIC_IP_PRI15_SHIFT                  0u
#define S32_NVIC_IP_PRI15_WIDTH                  8u
#define S32_NVIC_IP_PRI15(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI15_SHIFT))&S32_NVIC_IP_PRI15_MASK)
#define S32_NVIC_IP_PRI16_MASK                   0xFFu
#define S32_NVIC_IP_PRI16_SHIFT                  0u
#define S32_NVIC_IP_PRI16_WIDTH                  8u
#define S32_NVIC_IP_PRI16(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI16_SHIFT))&S32_NVIC_IP_PRI16_MASK)
#define S32_NVIC_IP_PRI17_MASK                   0xFFu
#define S32_NVIC_IP_PRI17_SHIFT                  0u
#define S32_NVIC_IP_PRI17_WIDTH                  8u
#define S32_NVIC_IP_PRI17(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI17_SHIFT))&S32_NVIC_IP_PRI17_MASK)
#define S32_NVIC_IP_PRI18_MASK                   0xFFu
#define S32_NVIC_IP_PRI18_SHIFT                  0u
#define S32_NVIC_IP_PRI18_WIDTH                  8u
#define S32_NVIC_IP_PRI18(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI18_SHIFT))&S32_NVIC_IP_PRI18_MASK)
#define S32_NVIC_IP_PRI19_MASK                   0xFFu
#define S32_NVIC_IP_PRI19_SHIFT                  0u
#define S32_NVIC_IP_PRI19_WIDTH                  8u
#define S32_NVIC_IP_PRI19(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI19_SHIFT))&S32_NVIC_IP_PRI19_MASK)
#define S32_NVIC_IP_PRI20_MASK                   0xFFu
#define S32_NVIC_IP_PRI20_SHIFT                  0u
#define S32_NVIC_IP_PRI20_WIDTH                  8u
#define S32_NVIC_IP_PRI20(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI20_SHIFT))&S32_NVIC_IP_PRI20_MASK)
#define S32_NVIC_IP_PRI21_MASK                   0xFFu
#define S32_NVIC_IP_PRI21_SHIFT                  0u
#define S32_NVIC_IP_PRI21_WIDTH                  8u
#define S32_NVIC_IP_PRI21(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI21_SHIFT))&S32_NVIC_IP_PRI21_MASK)
#define S32_NVIC_IP_PRI22_MASK                   0xFFu
#define S32_NVIC_IP_PRI22_SHIFT                  0u
#define S32_NVIC_IP_PRI22_WIDTH                  8u
#define S32_NVIC_IP_PRI22(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI22_SHIFT))&S32_NVIC_IP_PRI22_MASK)
#define S32_NVIC_IP_PRI23_MASK                   0xFFu
#define S32_NVIC_IP_PRI23_SHIFT                  0u
#define S32_NVIC_IP_PRI23_WIDTH                  8u
#define S32_NVIC_IP_PRI23(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI23_SHIFT))&S32_NVIC_IP_PRI23_MASK)
#define S32_NVIC_IP_PRI24_MASK                   0xFFu
#define S32_NVIC_IP_PRI24_SHIFT                  0u
#define S32_NVIC_IP_PRI24_WIDTH                  8u
#define S32_NVIC_IP_PRI24(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI24_SHIFT))&S32_NVIC_IP_PRI24_MASK)
#define S32_NVIC_IP_PRI25_MASK                   0xFFu
#define S32_NVIC_IP_PRI25_SHIFT                  0u
#define S32_NVIC_IP_PRI25_WIDTH                  8u
#define S32_NVIC_IP_PRI25(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI25_SHIFT))&S32_NVIC_IP_PRI25_MASK)
#define S32_NVIC_IP_PRI26_MASK                   0xFFu
#define S32_NVIC_IP_PRI26_SHIFT                  0u
#define S32_NVIC_IP_PRI26_WIDTH                  8u
#define S32_NVIC_IP_PRI26(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI26_SHIFT))&S32_NVIC_IP_PRI26_MASK)
#define S32_NVIC_IP_PRI27_MASK                   0xFFu
#define S32_NVIC_IP_PRI27_SHIFT                  0u
#define S32_NVIC_IP_PRI27_WIDTH                  8u
#define S32_NVIC_IP_PRI27(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI27_SHIFT))&S32_NVIC_IP_PRI27_MASK)
#define S32_NVIC_IP_PRI28_MASK                   0xFFu
#define S32_NVIC_IP_PRI28_SHIFT                  0u
#define S32_NVIC_IP_PRI28_WIDTH                  8u
#define S32_NVIC_IP_PRI28(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI28_SHIFT))&S32_NVIC_IP_PRI28_MASK)
#define S32_NVIC_IP_PRI29_MASK                   0xFFu
#define S32_NVIC_IP_PRI29_SHIFT                  0u
#define S32_NVIC_IP_PRI29_WIDTH                  8u
#define S32_NVIC_IP_PRI29(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI29_SHIFT))&S32_NVIC_IP_PRI29_MASK)
#define S32_NVIC_IP_PRI30_MASK                   0xFFu
#define S32_NVIC_IP_PRI30_SHIFT                  0u
#define S32_NVIC_IP_PRI30_WIDTH                  8u
#define S32_NVIC_IP_PRI30(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI30_SHIFT))&S32_NVIC_IP_PRI30_MASK)
#define S32_NVIC_IP_PRI31_MASK                   0xFFu
#define S32_NVIC_IP_PRI31_SHIFT                  0u
#define S32_NVIC_IP_PRI31_WIDTH                  8u
#define S32_NVIC_IP_PRI31(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI31_SHIFT))&S32_NVIC_IP_PRI31_MASK)
#define S32_NVIC_IP_PRI32_MASK                   0xFFu
#define S32_NVIC_IP_PRI32_SHIFT                  0u
#define S32_NVIC_IP_PRI32_WIDTH                  8u
#define S32_NVIC_IP_PRI32(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI32_SHIFT))&S32_NVIC_IP_PRI32_MASK)
#define S32_NVIC_IP_PRI33_MASK                   0xFFu
#define S32_NVIC_IP_PRI33_SHIFT                  0u
#define S32_NVIC_IP_PRI33_WIDTH                  8u
#define S32_NVIC_IP_PRI33(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI33_SHIFT))&S32_NVIC_IP_PRI33_MASK)
#define S32_NVIC_IP_PRI34_MASK                   0xFFu
#define S32_NVIC_IP_PRI34_SHIFT                  0u
#define S32_NVIC_IP_PRI34_WIDTH                  8u
#define S32_NVIC_IP_PRI34(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI34_SHIFT))&S32_NVIC_IP_PRI34_MASK)
#define S32_NVIC_IP_PRI35_MASK                   0xFFu
#define S32_NVIC_IP_PRI35_SHIFT                  0u
#define S32_NVIC_IP_PRI35_WIDTH                  8u
#define S32_NVIC_IP_PRI35(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI35_SHIFT))&S32_NVIC_IP_PRI35_MASK)
#define S32_NVIC_IP_PRI36_MASK                   0xFFu
#define S32_NVIC_IP_PRI36_SHIFT                  0u
#define S32_NVIC_IP_PRI36_WIDTH                  8u
#define S32_NVIC_IP_PRI36(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI36_SHIFT))&S32_NVIC_IP_PRI36_MASK)
#define S32_NVIC_IP_PRI37_MASK                   0xFFu
#define S32_NVIC_IP_PRI37_SHIFT                  0u
#define S32_NVIC_IP_PRI37_WIDTH                  8u
#define S32_NVIC_IP_PRI37(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI37_SHIFT))&S32_NVIC_IP_PRI37_MASK)
#define S32_NVIC_IP_PRI38_MASK                   0xFFu
#define S32_NVIC_IP_PRI38_SHIFT                  0u
#define S32_NVIC_IP_PRI38_WIDTH                  8u
#define S32_NVIC_IP_PRI38(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI38_SHIFT))&S32_NVIC_IP_PRI38_MASK)
#define S32_NVIC_IP_PRI39_MASK                   0xFFu
#define S32_NVIC_IP_PRI39_SHIFT                  0u
#define S32_NVIC_IP_PRI39_WIDTH                  8u
#define S32_NVIC_IP_PRI39(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI39_SHIFT))&S32_NVIC_IP_PRI39_MASK)
#define S32_NVIC_IP_PRI40_MASK                   0xFFu
#define S32_NVIC_IP_PRI40_SHIFT                  0u
#define S32_NVIC_IP_PRI40_WIDTH                  8u
#define S32_NVIC_IP_PRI40(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI40_SHIFT))&S32_NVIC_IP_PRI40_MASK)
#define S32_NVIC_IP_PRI41_MASK                   0xFFu
#define S32_NVIC_IP_PRI41_SHIFT                  0u
#define S32_NVIC_IP_PRI41_WIDTH                  8u
#define S32_NVIC_IP_PRI41(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI41_SHIFT))&S32_NVIC_IP_PRI41_MASK)
#define S32_NVIC_IP_PRI42_MASK                   0xFFu
#define S32_NVIC_IP_PRI42_SHIFT                  0u
#define S32_NVIC_IP_PRI42_WIDTH                  8u
#define S32_NVIC_IP_PRI42(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI42_SHIFT))&S32_NVIC_IP_PRI42_MASK)
#define S32_NVIC_IP_PRI43_MASK                   0xFFu
#define S32_NVIC_IP_PRI43_SHIFT                  0u
#define S32_NVIC_IP_PRI43_WIDTH                  8u
#define S32_NVIC_IP_PRI43(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI43_SHIFT))&S32_NVIC_IP_PRI43_MASK)
#define S32_NVIC_IP_PRI44_MASK                   0xFFu
#define S32_NVIC_IP_PRI44_SHIFT                  0u
#define S32_NVIC_IP_PRI44_WIDTH                  8u
#define S32_NVIC_IP_PRI44(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI44_SHIFT))&S32_NVIC_IP_PRI44_MASK)
#define S32_NVIC_IP_PRI45_MASK                   0xFFu
#define S32_NVIC_IP_PRI45_SHIFT                  0u
#define S32_NVIC_IP_PRI45_WIDTH                  8u
#define S32_NVIC_IP_PRI45(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI45_SHIFT))&S32_NVIC_IP_PRI45_MASK)
#define S32_NVIC_IP_PRI46_MASK                   0xFFu
#define S32_NVIC_IP_PRI46_SHIFT                  0u
#define S32_NVIC_IP_PRI46_WIDTH                  8u
#define S32_NVIC_IP_PRI46(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI46_SHIFT))&S32_NVIC_IP_PRI46_MASK)
#define S32_NVIC_IP_PRI47_MASK                   0xFFu
#define S32_NVIC_IP_PRI47_SHIFT                  0u
#define S32_NVIC_IP_PRI47_WIDTH                  8u
#define S32_NVIC_IP_PRI47(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI47_SHIFT))&S32_NVIC_IP_PRI47_MASK)
#define S32_NVIC_IP_PRI48_MASK                   0xFFu
#define S32_NVIC_IP_PRI48_SHIFT                  0u
#define S32_NVIC_IP_PRI48_WIDTH                  8u
#define S32_NVIC_IP_PRI48(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI48_SHIFT))&S32_NVIC_IP_PRI48_MASK)
#define S32_NVIC_IP_PRI49_MASK                   0xFFu
#define S32_NVIC_IP_PRI49_SHIFT                  0u
#define S32_NVIC_IP_PRI49_WIDTH                  8u
#define S32_NVIC_IP_PRI49(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI49_SHIFT))&S32_NVIC_IP_PRI49_MASK)
#define S32_NVIC_IP_PRI50_MASK                   0xFFu
#define S32_NVIC_IP_PRI50_SHIFT                  0u
#define S32_NVIC_IP_PRI50_WIDTH                  8u
#define S32_NVIC_IP_PRI50(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI50_SHIFT))&S32_NVIC_IP_PRI50_MASK)
#define S32_NVIC_IP_PRI51_MASK                   0xFFu
#define S32_NVIC_IP_PRI51_SHIFT                  0u
#define S32_NVIC_IP_PRI51_WIDTH                  8u
#define S32_NVIC_IP_PRI51(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI51_SHIFT))&S32_NVIC_IP_PRI51_MASK)
#define S32_NVIC_IP_PRI52_MASK                   0xFFu
#define S32_NVIC_IP_PRI52_SHIFT                  0u
#define S32_NVIC_IP_PRI52_WIDTH                  8u
#define S32_NVIC_IP_PRI52(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI52_SHIFT))&S32_NVIC_IP_PRI52_MASK)
#define S32_NVIC_IP_PRI53_MASK                   0xFFu
#define S32_NVIC_IP_PRI53_SHIFT                  0u
#define S32_NVIC_IP_PRI53_WIDTH                  8u
#define S32_NVIC_IP_PRI53(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI53_SHIFT))&S32_NVIC_IP_PRI53_MASK)
#define S32_NVIC_IP_PRI54_MASK                   0xFFu
#define S32_NVIC_IP_PRI54_SHIFT                  0u
#define S32_NVIC_IP_PRI54_WIDTH                  8u
#define S32_NVIC_IP_PRI54(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI54_SHIFT))&S32_NVIC_IP_PRI54_MASK)
#define S32_NVIC_IP_PRI55_MASK                   0xFFu
#define S32_NVIC_IP_PRI55_SHIFT                  0u
#define S32_NVIC_IP_PRI55_WIDTH                  8u
#define S32_NVIC_IP_PRI55(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI55_SHIFT))&S32_NVIC_IP_PRI55_MASK)
#define S32_NVIC_IP_PRI56_MASK                   0xFFu
#define S32_NVIC_IP_PRI56_SHIFT                  0u
#define S32_NVIC_IP_PRI56_WIDTH                  8u
#define S32_NVIC_IP_PRI56(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI56_SHIFT))&S32_NVIC_IP_PRI56_MASK)
#define S32_NVIC_IP_PRI57_MASK                   0xFFu
#define S32_NVIC_IP_PRI57_SHIFT                  0u
#define S32_NVIC_IP_PRI57_WIDTH                  8u
#define S32_NVIC_IP_PRI57(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI57_SHIFT))&S32_NVIC_IP_PRI57_MASK)
#define S32_NVIC_IP_PRI58_MASK                   0xFFu
#define S32_NVIC_IP_PRI58_SHIFT                  0u
#define S32_NVIC_IP_PRI58_WIDTH                  8u
#define S32_NVIC_IP_PRI58(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI58_SHIFT))&S32_NVIC_IP_PRI58_MASK)
#define S32_NVIC_IP_PRI59_MASK                   0xFFu
#define S32_NVIC_IP_PRI59_SHIFT                  0u
#define S32_NVIC_IP_PRI59_WIDTH                  8u
#define S32_NVIC_IP_PRI59(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI59_SHIFT))&S32_NVIC_IP_PRI59_MASK)
#define S32_NVIC_IP_PRI60_MASK                   0xFFu
#define S32_NVIC_IP_PRI60_SHIFT                  0u
#define S32_NVIC_IP_PRI60_WIDTH                  8u
#define S32_NVIC_IP_PRI60(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI60_SHIFT))&S32_NVIC_IP_PRI60_MASK)
#define S32_NVIC_IP_PRI61_MASK                   0xFFu
#define S32_NVIC_IP_PRI61_SHIFT                  0u
#define S32_NVIC_IP_PRI61_WIDTH                  8u
#define S32_NVIC_IP_PRI61(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI61_SHIFT))&S32_NVIC_IP_PRI61_MASK)
#define S32_NVIC_IP_PRI62_MASK                   0xFFu
#define S32_NVIC_IP_PRI62_SHIFT                  0u
#define S32_NVIC_IP_PRI62_WIDTH                  8u
#define S32_NVIC_IP_PRI62(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI62_SHIFT))&S32_NVIC_IP_PRI62_MASK)
#define S32_NVIC_IP_PRI63_MASK                   0xFFu
#define S32_NVIC_IP_PRI63_SHIFT                  0u
#define S32_NVIC_IP_PRI63_WIDTH                  8u
#define S32_NVIC_IP_PRI63(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI63_SHIFT))&S32_NVIC_IP_PRI63_MASK)
#define S32_NVIC_IP_PRI64_MASK                   0xFFu
#define S32_NVIC_IP_PRI64_SHIFT                  0u
#define S32_NVIC_IP_PRI64_WIDTH                  8u
#define S32_NVIC_IP_PRI64(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI64_SHIFT))&S32_NVIC_IP_PRI64_MASK)
#define S32_NVIC_IP_PRI65_MASK                   0xFFu
#define S32_NVIC_IP_PRI65_SHIFT                  0u
#define S32_NVIC_IP_PRI65_WIDTH                  8u
#define S32_NVIC_IP_PRI65(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI65_SHIFT))&S32_NVIC_IP_PRI65_MASK)
#define S32_NVIC_IP_PRI66_MASK                   0xFFu
#define S32_NVIC_IP_PRI66_SHIFT                  0u
#define S32_NVIC_IP_PRI66_WIDTH                  8u
#define S32_NVIC_IP_PRI66(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI66_SHIFT))&S32_NVIC_IP_PRI66_MASK)
#define S32_NVIC_IP_PRI67_MASK                   0xFFu
#define S32_NVIC_IP_PRI67_SHIFT                  0u
#define S32_NVIC_IP_PRI67_WIDTH                  8u
#define S32_NVIC_IP_PRI67(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI67_SHIFT))&S32_NVIC_IP_PRI67_MASK)
#define S32_NVIC_IP_PRI68_MASK                   0xFFu
#define S32_NVIC_IP_PRI68_SHIFT                  0u
#define S32_NVIC_IP_PRI68_WIDTH                  8u
#define S32_NVIC_IP_PRI68(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI68_SHIFT))&S32_NVIC_IP_PRI68_MASK)
#define S32_NVIC_IP_PRI69_MASK                   0xFFu
#define S32_NVIC_IP_PRI69_SHIFT                  0u
#define S32_NVIC_IP_PRI69_WIDTH                  8u
#define S32_NVIC_IP_PRI69(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI69_SHIFT))&S32_NVIC_IP_PRI69_MASK)
#define S32_NVIC_IP_PRI70_MASK                   0xFFu
#define S32_NVIC_IP_PRI70_SHIFT                  0u
#define S32_NVIC_IP_PRI70_WIDTH                  8u
#define S32_NVIC_IP_PRI70(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI70_SHIFT))&S32_NVIC_IP_PRI70_MASK)
#define S32_NVIC_IP_PRI71_MASK                   0xFFu
#define S32_NVIC_IP_PRI71_SHIFT                  0u
#define S32_NVIC_IP_PRI71_WIDTH                  8u
#define S32_NVIC_IP_PRI71(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI71_SHIFT))&S32_NVIC_IP_PRI71_MASK)
#define S32_NVIC_IP_PRI72_MASK                   0xFFu
#define S32_NVIC_IP_PRI72_SHIFT                  0u
#define S32_NVIC_IP_PRI72_WIDTH                  8u
#define S32_NVIC_IP_PRI72(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI72_SHIFT))&S32_NVIC_IP_PRI72_MASK)
#define S32_NVIC_IP_PRI73_MASK                   0xFFu
#define S32_NVIC_IP_PRI73_SHIFT                  0u
#define S32_NVIC_IP_PRI73_WIDTH                  8u
#define S32_NVIC_IP_PRI73(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI73_SHIFT))&S32_NVIC_IP_PRI73_MASK)
#define S32_NVIC_IP_PRI74_MASK                   0xFFu
#define S32_NVIC_IP_PRI74_SHIFT                  0u
#define S32_NVIC_IP_PRI74_WIDTH                  8u
#define S32_NVIC_IP_PRI74(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI74_SHIFT))&S32_NVIC_IP_PRI74_MASK)
#define S32_NVIC_IP_PRI75_MASK                   0xFFu
#define S32_NVIC_IP_PRI75_SHIFT                  0u
#define S32_NVIC_IP_PRI75_WIDTH                  8u
#define S32_NVIC_IP_PRI75(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI75_SHIFT))&S32_NVIC_IP_PRI75_MASK)
#define S32_NVIC_IP_PRI76_MASK                   0xFFu
#define S32_NVIC_IP_PRI76_SHIFT                  0u
#define S32_NVIC_IP_PRI76_WIDTH                  8u
#define S32_NVIC_IP_PRI76(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI76_SHIFT))&S32_NVIC_IP_PRI76_MASK)
#define S32_NVIC_IP_PRI77_MASK                   0xFFu
#define S32_NVIC_IP_PRI77_SHIFT                  0u
#define S32_NVIC_IP_PRI77_WIDTH                  8u
#define S32_NVIC_IP_PRI77(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI77_SHIFT))&S32_NVIC_IP_PRI77_MASK)
#define S32_NVIC_IP_PRI78_MASK                   0xFFu
#define S32_NVIC_IP_PRI78_SHIFT                  0u
#define S32_NVIC_IP_PRI78_WIDTH                  8u
#define S32_NVIC_IP_PRI78(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI78_SHIFT))&S32_NVIC_IP_PRI78_MASK)
#define S32_NVIC_IP_PRI79_MASK                   0xFFu
#define S32_NVIC_IP_PRI79_SHIFT                  0u
#define S32_NVIC_IP_PRI79_WIDTH                  8u
#define S32_NVIC_IP_PRI79(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI79_SHIFT))&S32_NVIC_IP_PRI79_MASK)
#define S32_NVIC_IP_PRI80_MASK                   0xFFu
#define S32_NVIC_IP_PRI80_SHIFT                  0u
#define S32_NVIC_IP_PRI80_WIDTH                  8u
#define S32_NVIC_IP_PRI80(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI80_SHIFT))&S32_NVIC_IP_PRI80_MASK)
#define S32_NVIC_IP_PRI81_MASK                   0xFFu
#define S32_NVIC_IP_PRI81_SHIFT                  0u
#define S32_NVIC_IP_PRI81_WIDTH                  8u
#define S32_NVIC_IP_PRI81(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI81_SHIFT))&S32_NVIC_IP_PRI81_MASK)
#define S32_NVIC_IP_PRI82_MASK                   0xFFu
#define S32_NVIC_IP_PRI82_SHIFT                  0u
#define S32_NVIC_IP_PRI82_WIDTH                  8u
#define S32_NVIC_IP_PRI82(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI82_SHIFT))&S32_NVIC_IP_PRI82_MASK)
#define S32_NVIC_IP_PRI83_MASK                   0xFFu
#define S32_NVIC_IP_PRI83_SHIFT                  0u
#define S32_NVIC_IP_PRI83_WIDTH                  8u
#define S32_NVIC_IP_PRI83(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI83_SHIFT))&S32_NVIC_IP_PRI83_MASK)
#define S32_NVIC_IP_PRI84_MASK                   0xFFu
#define S32_NVIC_IP_PRI84_SHIFT                  0u
#define S32_NVIC_IP_PRI84_WIDTH                  8u
#define S32_NVIC_IP_PRI84(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI84_SHIFT))&S32_NVIC_IP_PRI84_MASK)
#define S32_NVIC_IP_PRI85_MASK                   0xFFu
#define S32_NVIC_IP_PRI85_SHIFT                  0u
#define S32_NVIC_IP_PRI85_WIDTH                  8u
#define S32_NVIC_IP_PRI85(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI85_SHIFT))&S32_NVIC_IP_PRI85_MASK)
#define S32_NVIC_IP_PRI86_MASK                   0xFFu
#define S32_NVIC_IP_PRI86_SHIFT                  0u
#define S32_NVIC_IP_PRI86_WIDTH                  8u
#define S32_NVIC_IP_PRI86(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI86_SHIFT))&S32_NVIC_IP_PRI86_MASK)
#define S32_NVIC_IP_PRI87_MASK                   0xFFu
#define S32_NVIC_IP_PRI87_SHIFT                  0u
#define S32_NVIC_IP_PRI87_WIDTH                  8u
#define S32_NVIC_IP_PRI87(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI87_SHIFT))&S32_NVIC_IP_PRI87_MASK)
#define S32_NVIC_IP_PRI88_MASK                   0xFFu
#define S32_NVIC_IP_PRI88_SHIFT                  0u
#define S32_NVIC_IP_PRI88_WIDTH                  8u
#define S32_NVIC_IP_PRI88(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI88_SHIFT))&S32_NVIC_IP_PRI88_MASK)
#define S32_NVIC_IP_PRI89_MASK                   0xFFu
#define S32_NVIC_IP_PRI89_SHIFT                  0u
#define S32_NVIC_IP_PRI89_WIDTH                  8u
#define S32_NVIC_IP_PRI89(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI89_SHIFT))&S32_NVIC_IP_PRI89_MASK)
#define S32_NVIC_IP_PRI90_MASK                   0xFFu
#define S32_NVIC_IP_PRI90_SHIFT                  0u
#define S32_NVIC_IP_PRI90_WIDTH                  8u
#define S32_NVIC_IP_PRI90(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI90_SHIFT))&S32_NVIC_IP_PRI90_MASK)
#define S32_NVIC_IP_PRI91_MASK                   0xFFu
#define S32_NVIC_IP_PRI91_SHIFT                  0u
#define S32_NVIC_IP_PRI91_WIDTH                  8u
#define S32_NVIC_IP_PRI91(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI91_SHIFT))&S32_NVIC_IP_PRI91_MASK)
#define S32_NVIC_IP_PRI92_MASK                   0xFFu
#define S32_NVIC_IP_PRI92_SHIFT                  0u
#define S32_NVIC_IP_PRI92_WIDTH                  8u
#define S32_NVIC_IP_PRI92(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI92_SHIFT))&S32_NVIC_IP_PRI92_MASK)
#define S32_NVIC_IP_PRI93_MASK                   0xFFu
#define S32_NVIC_IP_PRI93_SHIFT                  0u
#define S32_NVIC_IP_PRI93_WIDTH                  8u
#define S32_NVIC_IP_PRI93(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI93_SHIFT))&S32_NVIC_IP_PRI93_MASK)
#define S32_NVIC_IP_PRI94_MASK                   0xFFu
#define S32_NVIC_IP_PRI94_SHIFT                  0u
#define S32_NVIC_IP_PRI94_WIDTH                  8u
#define S32_NVIC_IP_PRI94(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI94_SHIFT))&S32_NVIC_IP_PRI94_MASK)
#define S32_NVIC_IP_PRI95_MASK                   0xFFu
#define S32_NVIC_IP_PRI95_SHIFT                  0u
#define S32_NVIC_IP_PRI95_WIDTH                  8u
#define S32_NVIC_IP_PRI95(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI95_SHIFT))&S32_NVIC_IP_PRI95_MASK)
#define S32_NVIC_IP_PRI96_MASK                   0xFFu
#define S32_NVIC_IP_PRI96_SHIFT                  0u
#define S32_NVIC_IP_PRI96_WIDTH                  8u
#define S32_NVIC_IP_PRI96(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI96_SHIFT))&S32_NVIC_IP_PRI96_MASK)
#define S32_NVIC_IP_PRI97_MASK                   0xFFu
#define S32_NVIC_IP_PRI97_SHIFT                  0u
#define S32_NVIC_IP_PRI97_WIDTH                  8u
#define S32_NVIC_IP_PRI97(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI97_SHIFT))&S32_NVIC_IP_PRI97_MASK)
#define S32_NVIC_IP_PRI98_MASK                   0xFFu
#define S32_NVIC_IP_PRI98_SHIFT                  0u
#define S32_NVIC_IP_PRI98_WIDTH                  8u
#define S32_NVIC_IP_PRI98(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI98_SHIFT))&S32_NVIC_IP_PRI98_MASK)
#define S32_NVIC_IP_PRI99_MASK                   0xFFu
#define S32_NVIC_IP_PRI99_SHIFT                  0u
#define S32_NVIC_IP_PRI99_WIDTH                  8u
#define S32_NVIC_IP_PRI99(x)                     (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI99_SHIFT))&S32_NVIC_IP_PRI99_MASK)
#define S32_NVIC_IP_PRI100_MASK                  0xFFu
#define S32_NVIC_IP_PRI100_SHIFT                 0u
#define S32_NVIC_IP_PRI100_WIDTH                 8u
#define S32_NVIC_IP_PRI100(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI100_SHIFT))&S32_NVIC_IP_PRI100_MASK)
#define S32_NVIC_IP_PRI101_MASK                  0xFFu
#define S32_NVIC_IP_PRI101_SHIFT                 0u
#define S32_NVIC_IP_PRI101_WIDTH                 8u
#define S32_NVIC_IP_PRI101(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI101_SHIFT))&S32_NVIC_IP_PRI101_MASK)
#define S32_NVIC_IP_PRI102_MASK                  0xFFu
#define S32_NVIC_IP_PRI102_SHIFT                 0u
#define S32_NVIC_IP_PRI102_WIDTH                 8u
#define S32_NVIC_IP_PRI102(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI102_SHIFT))&S32_NVIC_IP_PRI102_MASK)
#define S32_NVIC_IP_PRI103_MASK                  0xFFu
#define S32_NVIC_IP_PRI103_SHIFT                 0u
#define S32_NVIC_IP_PRI103_WIDTH                 8u
#define S32_NVIC_IP_PRI103(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI103_SHIFT))&S32_NVIC_IP_PRI103_MASK)
#define S32_NVIC_IP_PRI104_MASK                  0xFFu
#define S32_NVIC_IP_PRI104_SHIFT                 0u
#define S32_NVIC_IP_PRI104_WIDTH                 8u
#define S32_NVIC_IP_PRI104(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI104_SHIFT))&S32_NVIC_IP_PRI104_MASK)
#define S32_NVIC_IP_PRI105_MASK                  0xFFu
#define S32_NVIC_IP_PRI105_SHIFT                 0u
#define S32_NVIC_IP_PRI105_WIDTH                 8u
#define S32_NVIC_IP_PRI105(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI105_SHIFT))&S32_NVIC_IP_PRI105_MASK)
#define S32_NVIC_IP_PRI106_MASK                  0xFFu
#define S32_NVIC_IP_PRI106_SHIFT                 0u
#define S32_NVIC_IP_PRI106_WIDTH                 8u
#define S32_NVIC_IP_PRI106(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI106_SHIFT))&S32_NVIC_IP_PRI106_MASK)
#define S32_NVIC_IP_PRI107_MASK                  0xFFu
#define S32_NVIC_IP_PRI107_SHIFT                 0u
#define S32_NVIC_IP_PRI107_WIDTH                 8u
#define S32_NVIC_IP_PRI107(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI107_SHIFT))&S32_NVIC_IP_PRI107_MASK)
#define S32_NVIC_IP_PRI108_MASK                  0xFFu
#define S32_NVIC_IP_PRI108_SHIFT                 0u
#define S32_NVIC_IP_PRI108_WIDTH                 8u
#define S32_NVIC_IP_PRI108(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI108_SHIFT))&S32_NVIC_IP_PRI108_MASK)
#define S32_NVIC_IP_PRI109_MASK                  0xFFu
#define S32_NVIC_IP_PRI109_SHIFT                 0u
#define S32_NVIC_IP_PRI109_WIDTH                 8u
#define S32_NVIC_IP_PRI109(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI109_SHIFT))&S32_NVIC_IP_PRI109_MASK)
#define S32_NVIC_IP_PRI110_MASK                  0xFFu
#define S32_NVIC_IP_PRI110_SHIFT                 0u
#define S32_NVIC_IP_PRI110_WIDTH                 8u
#define S32_NVIC_IP_PRI110(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI110_SHIFT))&S32_NVIC_IP_PRI110_MASK)
#define S32_NVIC_IP_PRI111_MASK                  0xFFu
#define S32_NVIC_IP_PRI111_SHIFT                 0u
#define S32_NVIC_IP_PRI111_WIDTH                 8u
#define S32_NVIC_IP_PRI111(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI111_SHIFT))&S32_NVIC_IP_PRI111_MASK)
#define S32_NVIC_IP_PRI112_MASK                  0xFFu
#define S32_NVIC_IP_PRI112_SHIFT                 0u
#define S32_NVIC_IP_PRI112_WIDTH                 8u
#define S32_NVIC_IP_PRI112(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI112_SHIFT))&S32_NVIC_IP_PRI112_MASK)
#define S32_NVIC_IP_PRI113_MASK                  0xFFu
#define S32_NVIC_IP_PRI113_SHIFT                 0u
#define S32_NVIC_IP_PRI113_WIDTH                 8u
#define S32_NVIC_IP_PRI113(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI113_SHIFT))&S32_NVIC_IP_PRI113_MASK)
#define S32_NVIC_IP_PRI114_MASK                  0xFFu
#define S32_NVIC_IP_PRI114_SHIFT                 0u
#define S32_NVIC_IP_PRI114_WIDTH                 8u
#define S32_NVIC_IP_PRI114(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI114_SHIFT))&S32_NVIC_IP_PRI114_MASK)
#define S32_NVIC_IP_PRI115_MASK                  0xFFu
#define S32_NVIC_IP_PRI115_SHIFT                 0u
#define S32_NVIC_IP_PRI115_WIDTH                 8u
#define S32_NVIC_IP_PRI115(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI115_SHIFT))&S32_NVIC_IP_PRI115_MASK)
#define S32_NVIC_IP_PRI116_MASK                  0xFFu
#define S32_NVIC_IP_PRI116_SHIFT                 0u
#define S32_NVIC_IP_PRI116_WIDTH                 8u
#define S32_NVIC_IP_PRI116(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI116_SHIFT))&S32_NVIC_IP_PRI116_MASK)
#define S32_NVIC_IP_PRI117_MASK                  0xFFu
#define S32_NVIC_IP_PRI117_SHIFT                 0u
#define S32_NVIC_IP_PRI117_WIDTH                 8u
#define S32_NVIC_IP_PRI117(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI117_SHIFT))&S32_NVIC_IP_PRI117_MASK)
#define S32_NVIC_IP_PRI118_MASK                  0xFFu
#define S32_NVIC_IP_PRI118_SHIFT                 0u
#define S32_NVIC_IP_PRI118_WIDTH                 8u
#define S32_NVIC_IP_PRI118(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI118_SHIFT))&S32_NVIC_IP_PRI118_MASK)
#define S32_NVIC_IP_PRI119_MASK                  0xFFu
#define S32_NVIC_IP_PRI119_SHIFT                 0u
#define S32_NVIC_IP_PRI119_WIDTH                 8u
#define S32_NVIC_IP_PRI119(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI119_SHIFT))&S32_NVIC_IP_PRI119_MASK)
#define S32_NVIC_IP_PRI120_MASK                  0xFFu
#define S32_NVIC_IP_PRI120_SHIFT                 0u
#define S32_NVIC_IP_PRI120_WIDTH                 8u
#define S32_NVIC_IP_PRI120(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI120_SHIFT))&S32_NVIC_IP_PRI120_MASK)
#define S32_NVIC_IP_PRI121_MASK                  0xFFu
#define S32_NVIC_IP_PRI121_SHIFT                 0u
#define S32_NVIC_IP_PRI121_WIDTH                 8u
#define S32_NVIC_IP_PRI121(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI121_SHIFT))&S32_NVIC_IP_PRI121_MASK)
#define S32_NVIC_IP_PRI122_MASK                  0xFFu
#define S32_NVIC_IP_PRI122_SHIFT                 0u
#define S32_NVIC_IP_PRI122_WIDTH                 8u
#define S32_NVIC_IP_PRI122(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI122_SHIFT))&S32_NVIC_IP_PRI122_MASK)
#define S32_NVIC_IP_PRI123_MASK                  0xFFu
#define S32_NVIC_IP_PRI123_SHIFT                 0u
#define S32_NVIC_IP_PRI123_WIDTH                 8u
#define S32_NVIC_IP_PRI123(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI123_SHIFT))&S32_NVIC_IP_PRI123_MASK)
#define S32_NVIC_IP_PRI124_MASK                  0xFFu
#define S32_NVIC_IP_PRI124_SHIFT                 0u
#define S32_NVIC_IP_PRI124_WIDTH                 8u
#define S32_NVIC_IP_PRI124(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI124_SHIFT))&S32_NVIC_IP_PRI124_MASK)
#define S32_NVIC_IP_PRI125_MASK                  0xFFu
#define S32_NVIC_IP_PRI125_SHIFT                 0u
#define S32_NVIC_IP_PRI125_WIDTH                 8u
#define S32_NVIC_IP_PRI125(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI125_SHIFT))&S32_NVIC_IP_PRI125_MASK)
#define S32_NVIC_IP_PRI126_MASK                  0xFFu
#define S32_NVIC_IP_PRI126_SHIFT                 0u
#define S32_NVIC_IP_PRI126_WIDTH                 8u
#define S32_NVIC_IP_PRI126(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI126_SHIFT))&S32_NVIC_IP_PRI126_MASK)
#define S32_NVIC_IP_PRI127_MASK                  0xFFu
#define S32_NVIC_IP_PRI127_SHIFT                 0u
#define S32_NVIC_IP_PRI127_WIDTH                 8u
#define S32_NVIC_IP_PRI127(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI127_SHIFT))&S32_NVIC_IP_PRI127_MASK)
#define S32_NVIC_IP_PRI128_MASK                  0xFFu
#define S32_NVIC_IP_PRI128_SHIFT                 0u
#define S32_NVIC_IP_PRI128_WIDTH                 8u
#define S32_NVIC_IP_PRI128(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI128_SHIFT))&S32_NVIC_IP_PRI128_MASK)
#define S32_NVIC_IP_PRI129_MASK                  0xFFu
#define S32_NVIC_IP_PRI129_SHIFT                 0u
#define S32_NVIC_IP_PRI129_WIDTH                 8u
#define S32_NVIC_IP_PRI129(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI129_SHIFT))&S32_NVIC_IP_PRI129_MASK)
#define S32_NVIC_IP_PRI130_MASK                  0xFFu
#define S32_NVIC_IP_PRI130_SHIFT                 0u
#define S32_NVIC_IP_PRI130_WIDTH                 8u
#define S32_NVIC_IP_PRI130(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI130_SHIFT))&S32_NVIC_IP_PRI130_MASK)
#define S32_NVIC_IP_PRI131_MASK                  0xFFu
#define S32_NVIC_IP_PRI131_SHIFT                 0u
#define S32_NVIC_IP_PRI131_WIDTH                 8u
#define S32_NVIC_IP_PRI131(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI131_SHIFT))&S32_NVIC_IP_PRI131_MASK)
#define S32_NVIC_IP_PRI132_MASK                  0xFFu
#define S32_NVIC_IP_PRI132_SHIFT                 0u
#define S32_NVIC_IP_PRI132_WIDTH                 8u
#define S32_NVIC_IP_PRI132(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI132_SHIFT))&S32_NVIC_IP_PRI132_MASK)
#define S32_NVIC_IP_PRI133_MASK                  0xFFu
#define S32_NVIC_IP_PRI133_SHIFT                 0u
#define S32_NVIC_IP_PRI133_WIDTH                 8u
#define S32_NVIC_IP_PRI133(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI133_SHIFT))&S32_NVIC_IP_PRI133_MASK)
#define S32_NVIC_IP_PRI134_MASK                  0xFFu
#define S32_NVIC_IP_PRI134_SHIFT                 0u
#define S32_NVIC_IP_PRI134_WIDTH                 8u
#define S32_NVIC_IP_PRI134(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI134_SHIFT))&S32_NVIC_IP_PRI134_MASK)
#define S32_NVIC_IP_PRI135_MASK                  0xFFu
#define S32_NVIC_IP_PRI135_SHIFT                 0u
#define S32_NVIC_IP_PRI135_WIDTH                 8u
#define S32_NVIC_IP_PRI135(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI135_SHIFT))&S32_NVIC_IP_PRI135_MASK)
#define S32_NVIC_IP_PRI136_MASK                  0xFFu
#define S32_NVIC_IP_PRI136_SHIFT                 0u
#define S32_NVIC_IP_PRI136_WIDTH                 8u
#define S32_NVIC_IP_PRI136(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI136_SHIFT))&S32_NVIC_IP_PRI136_MASK)
#define S32_NVIC_IP_PRI137_MASK                  0xFFu
#define S32_NVIC_IP_PRI137_SHIFT                 0u
#define S32_NVIC_IP_PRI137_WIDTH                 8u
#define S32_NVIC_IP_PRI137(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI137_SHIFT))&S32_NVIC_IP_PRI137_MASK)
#define S32_NVIC_IP_PRI138_MASK                  0xFFu
#define S32_NVIC_IP_PRI138_SHIFT                 0u
#define S32_NVIC_IP_PRI138_WIDTH                 8u
#define S32_NVIC_IP_PRI138(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI138_SHIFT))&S32_NVIC_IP_PRI138_MASK)
#define S32_NVIC_IP_PRI139_MASK                  0xFFu
#define S32_NVIC_IP_PRI139_SHIFT                 0u
#define S32_NVIC_IP_PRI139_WIDTH                 8u
#define S32_NVIC_IP_PRI139(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI139_SHIFT))&S32_NVIC_IP_PRI139_MASK)
#define S32_NVIC_IP_PRI140_MASK                  0xFFu
#define S32_NVIC_IP_PRI140_SHIFT                 0u
#define S32_NVIC_IP_PRI140_WIDTH                 8u
#define S32_NVIC_IP_PRI140(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI140_SHIFT))&S32_NVIC_IP_PRI140_MASK)
#define S32_NVIC_IP_PRI141_MASK                  0xFFu
#define S32_NVIC_IP_PRI141_SHIFT                 0u
#define S32_NVIC_IP_PRI141_WIDTH                 8u
#define S32_NVIC_IP_PRI141(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI141_SHIFT))&S32_NVIC_IP_PRI141_MASK)
#define S32_NVIC_IP_PRI142_MASK                  0xFFu
#define S32_NVIC_IP_PRI142_SHIFT                 0u
#define S32_NVIC_IP_PRI142_WIDTH                 8u
#define S32_NVIC_IP_PRI142(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI142_SHIFT))&S32_NVIC_IP_PRI142_MASK)
#define S32_NVIC_IP_PRI143_MASK                  0xFFu
#define S32_NVIC_IP_PRI143_SHIFT                 0u
#define S32_NVIC_IP_PRI143_WIDTH                 8u
#define S32_NVIC_IP_PRI143(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI143_SHIFT))&S32_NVIC_IP_PRI143_MASK)
#define S32_NVIC_IP_PRI144_MASK                  0xFFu
#define S32_NVIC_IP_PRI144_SHIFT                 0u
#define S32_NVIC_IP_PRI144_WIDTH                 8u
#define S32_NVIC_IP_PRI144(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI144_SHIFT))&S32_NVIC_IP_PRI144_MASK)
#define S32_NVIC_IP_PRI145_MASK                  0xFFu
#define S32_NVIC_IP_PRI145_SHIFT                 0u
#define S32_NVIC_IP_PRI145_WIDTH                 8u
#define S32_NVIC_IP_PRI145(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI145_SHIFT))&S32_NVIC_IP_PRI145_MASK)
#define S32_NVIC_IP_PRI146_MASK                  0xFFu
#define S32_NVIC_IP_PRI146_SHIFT                 0u
#define S32_NVIC_IP_PRI146_WIDTH                 8u
#define S32_NVIC_IP_PRI146(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI146_SHIFT))&S32_NVIC_IP_PRI146_MASK)
#define S32_NVIC_IP_PRI147_MASK                  0xFFu
#define S32_NVIC_IP_PRI147_SHIFT                 0u
#define S32_NVIC_IP_PRI147_WIDTH                 8u
#define S32_NVIC_IP_PRI147(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI147_SHIFT))&S32_NVIC_IP_PRI147_MASK)
#define S32_NVIC_IP_PRI148_MASK                  0xFFu
#define S32_NVIC_IP_PRI148_SHIFT                 0u
#define S32_NVIC_IP_PRI148_WIDTH                 8u
#define S32_NVIC_IP_PRI148(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI148_SHIFT))&S32_NVIC_IP_PRI148_MASK)
#define S32_NVIC_IP_PRI149_MASK                  0xFFu
#define S32_NVIC_IP_PRI149_SHIFT                 0u
#define S32_NVIC_IP_PRI149_WIDTH                 8u
#define S32_NVIC_IP_PRI149(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI149_SHIFT))&S32_NVIC_IP_PRI149_MASK)
#define S32_NVIC_IP_PRI150_MASK                  0xFFu
#define S32_NVIC_IP_PRI150_SHIFT                 0u
#define S32_NVIC_IP_PRI150_WIDTH                 8u
#define S32_NVIC_IP_PRI150(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI150_SHIFT))&S32_NVIC_IP_PRI150_MASK)
#define S32_NVIC_IP_PRI151_MASK                  0xFFu
#define S32_NVIC_IP_PRI151_SHIFT                 0u
#define S32_NVIC_IP_PRI151_WIDTH                 8u
#define S32_NVIC_IP_PRI151(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI151_SHIFT))&S32_NVIC_IP_PRI151_MASK)
#define S32_NVIC_IP_PRI152_MASK                  0xFFu
#define S32_NVIC_IP_PRI152_SHIFT                 0u
#define S32_NVIC_IP_PRI152_WIDTH                 8u
#define S32_NVIC_IP_PRI152(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI152_SHIFT))&S32_NVIC_IP_PRI152_MASK)
#define S32_NVIC_IP_PRI153_MASK                  0xFFu
#define S32_NVIC_IP_PRI153_SHIFT                 0u
#define S32_NVIC_IP_PRI153_WIDTH                 8u
#define S32_NVIC_IP_PRI153(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI153_SHIFT))&S32_NVIC_IP_PRI153_MASK)
#define S32_NVIC_IP_PRI154_MASK                  0xFFu
#define S32_NVIC_IP_PRI154_SHIFT                 0u
#define S32_NVIC_IP_PRI154_WIDTH                 8u
#define S32_NVIC_IP_PRI154(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI154_SHIFT))&S32_NVIC_IP_PRI154_MASK)
#define S32_NVIC_IP_PRI155_MASK                  0xFFu
#define S32_NVIC_IP_PRI155_SHIFT                 0u
#define S32_NVIC_IP_PRI155_WIDTH                 8u
#define S32_NVIC_IP_PRI155(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI155_SHIFT))&S32_NVIC_IP_PRI155_MASK)
#define S32_NVIC_IP_PRI156_MASK                  0xFFu
#define S32_NVIC_IP_PRI156_SHIFT                 0u
#define S32_NVIC_IP_PRI156_WIDTH                 8u
#define S32_NVIC_IP_PRI156(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI156_SHIFT))&S32_NVIC_IP_PRI156_MASK)
#define S32_NVIC_IP_PRI157_MASK                  0xFFu
#define S32_NVIC_IP_PRI157_SHIFT                 0u
#define S32_NVIC_IP_PRI157_WIDTH                 8u
#define S32_NVIC_IP_PRI157(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI157_SHIFT))&S32_NVIC_IP_PRI157_MASK)
#define S32_NVIC_IP_PRI158_MASK                  0xFFu
#define S32_NVIC_IP_PRI158_SHIFT                 0u
#define S32_NVIC_IP_PRI158_WIDTH                 8u
#define S32_NVIC_IP_PRI158(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI158_SHIFT))&S32_NVIC_IP_PRI158_MASK)
#define S32_NVIC_IP_PRI159_MASK                  0xFFu
#define S32_NVIC_IP_PRI159_SHIFT                 0u
#define S32_NVIC_IP_PRI159_WIDTH                 8u
#define S32_NVIC_IP_PRI159(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI159_SHIFT))&S32_NVIC_IP_PRI159_MASK)
#define S32_NVIC_IP_PRI160_MASK                  0xFFu
#define S32_NVIC_IP_PRI160_SHIFT                 0u
#define S32_NVIC_IP_PRI160_WIDTH                 8u
#define S32_NVIC_IP_PRI160(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI160_SHIFT))&S32_NVIC_IP_PRI160_MASK)
#define S32_NVIC_IP_PRI161_MASK                  0xFFu
#define S32_NVIC_IP_PRI161_SHIFT                 0u
#define S32_NVIC_IP_PRI161_WIDTH                 8u
#define S32_NVIC_IP_PRI161(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI161_SHIFT))&S32_NVIC_IP_PRI161_MASK)
#define S32_NVIC_IP_PRI162_MASK                  0xFFu
#define S32_NVIC_IP_PRI162_SHIFT                 0u
#define S32_NVIC_IP_PRI162_WIDTH                 8u
#define S32_NVIC_IP_PRI162(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI162_SHIFT))&S32_NVIC_IP_PRI162_MASK)
#define S32_NVIC_IP_PRI163_MASK                  0xFFu
#define S32_NVIC_IP_PRI163_SHIFT                 0u
#define S32_NVIC_IP_PRI163_WIDTH                 8u
#define S32_NVIC_IP_PRI163(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI163_SHIFT))&S32_NVIC_IP_PRI163_MASK)
#define S32_NVIC_IP_PRI164_MASK                  0xFFu
#define S32_NVIC_IP_PRI164_SHIFT                 0u
#define S32_NVIC_IP_PRI164_WIDTH                 8u
#define S32_NVIC_IP_PRI164(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI164_SHIFT))&S32_NVIC_IP_PRI164_MASK)
#define S32_NVIC_IP_PRI165_MASK                  0xFFu
#define S32_NVIC_IP_PRI165_SHIFT                 0u
#define S32_NVIC_IP_PRI165_WIDTH                 8u
#define S32_NVIC_IP_PRI165(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI165_SHIFT))&S32_NVIC_IP_PRI165_MASK)
#define S32_NVIC_IP_PRI166_MASK                  0xFFu
#define S32_NVIC_IP_PRI166_SHIFT                 0u
#define S32_NVIC_IP_PRI166_WIDTH                 8u
#define S32_NVIC_IP_PRI166(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI166_SHIFT))&S32_NVIC_IP_PRI166_MASK)
#define S32_NVIC_IP_PRI167_MASK                  0xFFu
#define S32_NVIC_IP_PRI167_SHIFT                 0u
#define S32_NVIC_IP_PRI167_WIDTH                 8u
#define S32_NVIC_IP_PRI167(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI167_SHIFT))&S32_NVIC_IP_PRI167_MASK)
#define S32_NVIC_IP_PRI168_MASK                  0xFFu
#define S32_NVIC_IP_PRI168_SHIFT                 0u
#define S32_NVIC_IP_PRI168_WIDTH                 8u
#define S32_NVIC_IP_PRI168(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI168_SHIFT))&S32_NVIC_IP_PRI168_MASK)
#define S32_NVIC_IP_PRI169_MASK                  0xFFu
#define S32_NVIC_IP_PRI169_SHIFT                 0u
#define S32_NVIC_IP_PRI169_WIDTH                 8u
#define S32_NVIC_IP_PRI169(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI169_SHIFT))&S32_NVIC_IP_PRI169_MASK)
#define S32_NVIC_IP_PRI170_MASK                  0xFFu
#define S32_NVIC_IP_PRI170_SHIFT                 0u
#define S32_NVIC_IP_PRI170_WIDTH                 8u
#define S32_NVIC_IP_PRI170(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI170_SHIFT))&S32_NVIC_IP_PRI170_MASK)
#define S32_NVIC_IP_PRI171_MASK                  0xFFu
#define S32_NVIC_IP_PRI171_SHIFT                 0u
#define S32_NVIC_IP_PRI171_WIDTH                 8u
#define S32_NVIC_IP_PRI171(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI171_SHIFT))&S32_NVIC_IP_PRI171_MASK)
#define S32_NVIC_IP_PRI172_MASK                  0xFFu
#define S32_NVIC_IP_PRI172_SHIFT                 0u
#define S32_NVIC_IP_PRI172_WIDTH                 8u
#define S32_NVIC_IP_PRI172(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI172_SHIFT))&S32_NVIC_IP_PRI172_MASK)
#define S32_NVIC_IP_PRI173_MASK                  0xFFu
#define S32_NVIC_IP_PRI173_SHIFT                 0u
#define S32_NVIC_IP_PRI173_WIDTH                 8u
#define S32_NVIC_IP_PRI173(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI173_SHIFT))&S32_NVIC_IP_PRI173_MASK)
#define S32_NVIC_IP_PRI174_MASK                  0xFFu
#define S32_NVIC_IP_PRI174_SHIFT                 0u
#define S32_NVIC_IP_PRI174_WIDTH                 8u
#define S32_NVIC_IP_PRI174(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI174_SHIFT))&S32_NVIC_IP_PRI174_MASK)
#define S32_NVIC_IP_PRI175_MASK                  0xFFu
#define S32_NVIC_IP_PRI175_SHIFT                 0u
#define S32_NVIC_IP_PRI175_WIDTH                 8u
#define S32_NVIC_IP_PRI175(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI175_SHIFT))&S32_NVIC_IP_PRI175_MASK)
#define S32_NVIC_IP_PRI176_MASK                  0xFFu
#define S32_NVIC_IP_PRI176_SHIFT                 0u
#define S32_NVIC_IP_PRI176_WIDTH                 8u
#define S32_NVIC_IP_PRI176(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI176_SHIFT))&S32_NVIC_IP_PRI176_MASK)
#define S32_NVIC_IP_PRI177_MASK                  0xFFu
#define S32_NVIC_IP_PRI177_SHIFT                 0u
#define S32_NVIC_IP_PRI177_WIDTH                 8u
#define S32_NVIC_IP_PRI177(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI177_SHIFT))&S32_NVIC_IP_PRI177_MASK)
#define S32_NVIC_IP_PRI178_MASK                  0xFFu
#define S32_NVIC_IP_PRI178_SHIFT                 0u
#define S32_NVIC_IP_PRI178_WIDTH                 8u
#define S32_NVIC_IP_PRI178(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI178_SHIFT))&S32_NVIC_IP_PRI178_MASK)
#define S32_NVIC_IP_PRI179_MASK                  0xFFu
#define S32_NVIC_IP_PRI179_SHIFT                 0u
#define S32_NVIC_IP_PRI179_WIDTH                 8u
#define S32_NVIC_IP_PRI179(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI179_SHIFT))&S32_NVIC_IP_PRI179_MASK)
#define S32_NVIC_IP_PRI180_MASK                  0xFFu
#define S32_NVIC_IP_PRI180_SHIFT                 0u
#define S32_NVIC_IP_PRI180_WIDTH                 8u
#define S32_NVIC_IP_PRI180(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI180_SHIFT))&S32_NVIC_IP_PRI180_MASK)
#define S32_NVIC_IP_PRI181_MASK                  0xFFu
#define S32_NVIC_IP_PRI181_SHIFT                 0u
#define S32_NVIC_IP_PRI181_WIDTH                 8u
#define S32_NVIC_IP_PRI181(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI181_SHIFT))&S32_NVIC_IP_PRI181_MASK)
#define S32_NVIC_IP_PRI182_MASK                  0xFFu
#define S32_NVIC_IP_PRI182_SHIFT                 0u
#define S32_NVIC_IP_PRI182_WIDTH                 8u
#define S32_NVIC_IP_PRI182(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI182_SHIFT))&S32_NVIC_IP_PRI182_MASK)
#define S32_NVIC_IP_PRI183_MASK                  0xFFu
#define S32_NVIC_IP_PRI183_SHIFT                 0u
#define S32_NVIC_IP_PRI183_WIDTH                 8u
#define S32_NVIC_IP_PRI183(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI183_SHIFT))&S32_NVIC_IP_PRI183_MASK)
#define S32_NVIC_IP_PRI184_MASK                  0xFFu
#define S32_NVIC_IP_PRI184_SHIFT                 0u
#define S32_NVIC_IP_PRI184_WIDTH                 8u
#define S32_NVIC_IP_PRI184(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI184_SHIFT))&S32_NVIC_IP_PRI184_MASK)
#define S32_NVIC_IP_PRI185_MASK                  0xFFu
#define S32_NVIC_IP_PRI185_SHIFT                 0u
#define S32_NVIC_IP_PRI185_WIDTH                 8u
#define S32_NVIC_IP_PRI185(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI185_SHIFT))&S32_NVIC_IP_PRI185_MASK)
#define S32_NVIC_IP_PRI186_MASK                  0xFFu
#define S32_NVIC_IP_PRI186_SHIFT                 0u
#define S32_NVIC_IP_PRI186_WIDTH                 8u
#define S32_NVIC_IP_PRI186(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI186_SHIFT))&S32_NVIC_IP_PRI186_MASK)
#define S32_NVIC_IP_PRI187_MASK                  0xFFu
#define S32_NVIC_IP_PRI187_SHIFT                 0u
#define S32_NVIC_IP_PRI187_WIDTH                 8u
#define S32_NVIC_IP_PRI187(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI187_SHIFT))&S32_NVIC_IP_PRI187_MASK)
#define S32_NVIC_IP_PRI188_MASK                  0xFFu
#define S32_NVIC_IP_PRI188_SHIFT                 0u
#define S32_NVIC_IP_PRI188_WIDTH                 8u
#define S32_NVIC_IP_PRI188(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI188_SHIFT))&S32_NVIC_IP_PRI188_MASK)
#define S32_NVIC_IP_PRI189_MASK                  0xFFu
#define S32_NVIC_IP_PRI189_SHIFT                 0u
#define S32_NVIC_IP_PRI189_WIDTH                 8u
#define S32_NVIC_IP_PRI189(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI189_SHIFT))&S32_NVIC_IP_PRI189_MASK)
#define S32_NVIC_IP_PRI190_MASK                  0xFFu
#define S32_NVIC_IP_PRI190_SHIFT                 0u
#define S32_NVIC_IP_PRI190_WIDTH                 8u
#define S32_NVIC_IP_PRI190(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI190_SHIFT))&S32_NVIC_IP_PRI190_MASK)
#define S32_NVIC_IP_PRI191_MASK                  0xFFu
#define S32_NVIC_IP_PRI191_SHIFT                 0u
#define S32_NVIC_IP_PRI191_WIDTH                 8u
#define S32_NVIC_IP_PRI191(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI191_SHIFT))&S32_NVIC_IP_PRI191_MASK)
#define S32_NVIC_IP_PRI192_MASK                  0xFFu
#define S32_NVIC_IP_PRI192_SHIFT                 0u
#define S32_NVIC_IP_PRI192_WIDTH                 8u
#define S32_NVIC_IP_PRI192(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI192_SHIFT))&S32_NVIC_IP_PRI192_MASK)
#define S32_NVIC_IP_PRI193_MASK                  0xFFu
#define S32_NVIC_IP_PRI193_SHIFT                 0u
#define S32_NVIC_IP_PRI193_WIDTH                 8u
#define S32_NVIC_IP_PRI193(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI193_SHIFT))&S32_NVIC_IP_PRI193_MASK)
#define S32_NVIC_IP_PRI194_MASK                  0xFFu
#define S32_NVIC_IP_PRI194_SHIFT                 0u
#define S32_NVIC_IP_PRI194_WIDTH                 8u
#define S32_NVIC_IP_PRI194(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI194_SHIFT))&S32_NVIC_IP_PRI194_MASK)
#define S32_NVIC_IP_PRI195_MASK                  0xFFu
#define S32_NVIC_IP_PRI195_SHIFT                 0u
#define S32_NVIC_IP_PRI195_WIDTH                 8u
#define S32_NVIC_IP_PRI195(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI195_SHIFT))&S32_NVIC_IP_PRI195_MASK)
#define S32_NVIC_IP_PRI196_MASK                  0xFFu
#define S32_NVIC_IP_PRI196_SHIFT                 0u
#define S32_NVIC_IP_PRI196_WIDTH                 8u
#define S32_NVIC_IP_PRI196(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI196_SHIFT))&S32_NVIC_IP_PRI196_MASK)
#define S32_NVIC_IP_PRI197_MASK                  0xFFu
#define S32_NVIC_IP_PRI197_SHIFT                 0u
#define S32_NVIC_IP_PRI197_WIDTH                 8u
#define S32_NVIC_IP_PRI197(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI197_SHIFT))&S32_NVIC_IP_PRI197_MASK)
#define S32_NVIC_IP_PRI198_MASK                  0xFFu
#define S32_NVIC_IP_PRI198_SHIFT                 0u
#define S32_NVIC_IP_PRI198_WIDTH                 8u
#define S32_NVIC_IP_PRI198(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI198_SHIFT))&S32_NVIC_IP_PRI198_MASK)
#define S32_NVIC_IP_PRI199_MASK                  0xFFu
#define S32_NVIC_IP_PRI199_SHIFT                 0u
#define S32_NVIC_IP_PRI199_WIDTH                 8u
#define S32_NVIC_IP_PRI199(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI199_SHIFT))&S32_NVIC_IP_PRI199_MASK)
#define S32_NVIC_IP_PRI200_MASK                  0xFFu
#define S32_NVIC_IP_PRI200_SHIFT                 0u
#define S32_NVIC_IP_PRI200_WIDTH                 8u
#define S32_NVIC_IP_PRI200(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI200_SHIFT))&S32_NVIC_IP_PRI200_MASK)
#define S32_NVIC_IP_PRI201_MASK                  0xFFu
#define S32_NVIC_IP_PRI201_SHIFT                 0u
#define S32_NVIC_IP_PRI201_WIDTH                 8u
#define S32_NVIC_IP_PRI201(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI201_SHIFT))&S32_NVIC_IP_PRI201_MASK)
#define S32_NVIC_IP_PRI202_MASK                  0xFFu
#define S32_NVIC_IP_PRI202_SHIFT                 0u
#define S32_NVIC_IP_PRI202_WIDTH                 8u
#define S32_NVIC_IP_PRI202(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI202_SHIFT))&S32_NVIC_IP_PRI202_MASK)
#define S32_NVIC_IP_PRI203_MASK                  0xFFu
#define S32_NVIC_IP_PRI203_SHIFT                 0u
#define S32_NVIC_IP_PRI203_WIDTH                 8u
#define S32_NVIC_IP_PRI203(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI203_SHIFT))&S32_NVIC_IP_PRI203_MASK)
#define S32_NVIC_IP_PRI204_MASK                  0xFFu
#define S32_NVIC_IP_PRI204_SHIFT                 0u
#define S32_NVIC_IP_PRI204_WIDTH                 8u
#define S32_NVIC_IP_PRI204(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI204_SHIFT))&S32_NVIC_IP_PRI204_MASK)
#define S32_NVIC_IP_PRI205_MASK                  0xFFu
#define S32_NVIC_IP_PRI205_SHIFT                 0u
#define S32_NVIC_IP_PRI205_WIDTH                 8u
#define S32_NVIC_IP_PRI205(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI205_SHIFT))&S32_NVIC_IP_PRI205_MASK)
#define S32_NVIC_IP_PRI206_MASK                  0xFFu
#define S32_NVIC_IP_PRI206_SHIFT                 0u
#define S32_NVIC_IP_PRI206_WIDTH                 8u
#define S32_NVIC_IP_PRI206(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI206_SHIFT))&S32_NVIC_IP_PRI206_MASK)
#define S32_NVIC_IP_PRI207_MASK                  0xFFu
#define S32_NVIC_IP_PRI207_SHIFT                 0u
#define S32_NVIC_IP_PRI207_WIDTH                 8u
#define S32_NVIC_IP_PRI207(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI207_SHIFT))&S32_NVIC_IP_PRI207_MASK)
#define S32_NVIC_IP_PRI208_MASK                  0xFFu
#define S32_NVIC_IP_PRI208_SHIFT                 0u
#define S32_NVIC_IP_PRI208_WIDTH                 8u
#define S32_NVIC_IP_PRI208(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI208_SHIFT))&S32_NVIC_IP_PRI208_MASK)
#define S32_NVIC_IP_PRI209_MASK                  0xFFu
#define S32_NVIC_IP_PRI209_SHIFT                 0u
#define S32_NVIC_IP_PRI209_WIDTH                 8u
#define S32_NVIC_IP_PRI209(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI209_SHIFT))&S32_NVIC_IP_PRI209_MASK)
#define S32_NVIC_IP_PRI210_MASK                  0xFFu
#define S32_NVIC_IP_PRI210_SHIFT                 0u
#define S32_NVIC_IP_PRI210_WIDTH                 8u
#define S32_NVIC_IP_PRI210(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI210_SHIFT))&S32_NVIC_IP_PRI210_MASK)
#define S32_NVIC_IP_PRI211_MASK                  0xFFu
#define S32_NVIC_IP_PRI211_SHIFT                 0u
#define S32_NVIC_IP_PRI211_WIDTH                 8u
#define S32_NVIC_IP_PRI211(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI211_SHIFT))&S32_NVIC_IP_PRI211_MASK)
#define S32_NVIC_IP_PRI212_MASK                  0xFFu
#define S32_NVIC_IP_PRI212_SHIFT                 0u
#define S32_NVIC_IP_PRI212_WIDTH                 8u
#define S32_NVIC_IP_PRI212(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI212_SHIFT))&S32_NVIC_IP_PRI212_MASK)
#define S32_NVIC_IP_PRI213_MASK                  0xFFu
#define S32_NVIC_IP_PRI213_SHIFT                 0u
#define S32_NVIC_IP_PRI213_WIDTH                 8u
#define S32_NVIC_IP_PRI213(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI213_SHIFT))&S32_NVIC_IP_PRI213_MASK)
#define S32_NVIC_IP_PRI214_MASK                  0xFFu
#define S32_NVIC_IP_PRI214_SHIFT                 0u
#define S32_NVIC_IP_PRI214_WIDTH                 8u
#define S32_NVIC_IP_PRI214(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI214_SHIFT))&S32_NVIC_IP_PRI214_MASK)
#define S32_NVIC_IP_PRI215_MASK                  0xFFu
#define S32_NVIC_IP_PRI215_SHIFT                 0u
#define S32_NVIC_IP_PRI215_WIDTH                 8u
#define S32_NVIC_IP_PRI215(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI215_SHIFT))&S32_NVIC_IP_PRI215_MASK)
#define S32_NVIC_IP_PRI216_MASK                  0xFFu
#define S32_NVIC_IP_PRI216_SHIFT                 0u
#define S32_NVIC_IP_PRI216_WIDTH                 8u
#define S32_NVIC_IP_PRI216(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI216_SHIFT))&S32_NVIC_IP_PRI216_MASK)
#define S32_NVIC_IP_PRI217_MASK                  0xFFu
#define S32_NVIC_IP_PRI217_SHIFT                 0u
#define S32_NVIC_IP_PRI217_WIDTH                 8u
#define S32_NVIC_IP_PRI217(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI217_SHIFT))&S32_NVIC_IP_PRI217_MASK)
#define S32_NVIC_IP_PRI218_MASK                  0xFFu
#define S32_NVIC_IP_PRI218_SHIFT                 0u
#define S32_NVIC_IP_PRI218_WIDTH                 8u
#define S32_NVIC_IP_PRI218(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI218_SHIFT))&S32_NVIC_IP_PRI218_MASK)
#define S32_NVIC_IP_PRI219_MASK                  0xFFu
#define S32_NVIC_IP_PRI219_SHIFT                 0u
#define S32_NVIC_IP_PRI219_WIDTH                 8u
#define S32_NVIC_IP_PRI219(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI219_SHIFT))&S32_NVIC_IP_PRI219_MASK)
#define S32_NVIC_IP_PRI220_MASK                  0xFFu
#define S32_NVIC_IP_PRI220_SHIFT                 0u
#define S32_NVIC_IP_PRI220_WIDTH                 8u
#define S32_NVIC_IP_PRI220(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI220_SHIFT))&S32_NVIC_IP_PRI220_MASK)
#define S32_NVIC_IP_PRI221_MASK                  0xFFu
#define S32_NVIC_IP_PRI221_SHIFT                 0u
#define S32_NVIC_IP_PRI221_WIDTH                 8u
#define S32_NVIC_IP_PRI221(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI221_SHIFT))&S32_NVIC_IP_PRI221_MASK)
#define S32_NVIC_IP_PRI222_MASK                  0xFFu
#define S32_NVIC_IP_PRI222_SHIFT                 0u
#define S32_NVIC_IP_PRI222_WIDTH                 8u
#define S32_NVIC_IP_PRI222(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI222_SHIFT))&S32_NVIC_IP_PRI222_MASK)
#define S32_NVIC_IP_PRI223_MASK                  0xFFu
#define S32_NVIC_IP_PRI223_SHIFT                 0u
#define S32_NVIC_IP_PRI223_WIDTH                 8u
#define S32_NVIC_IP_PRI223(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI223_SHIFT))&S32_NVIC_IP_PRI223_MASK)
#define S32_NVIC_IP_PRI224_MASK                  0xFFu
#define S32_NVIC_IP_PRI224_SHIFT                 0u
#define S32_NVIC_IP_PRI224_WIDTH                 8u
#define S32_NVIC_IP_PRI224(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI224_SHIFT))&S32_NVIC_IP_PRI224_MASK)
#define S32_NVIC_IP_PRI225_MASK                  0xFFu
#define S32_NVIC_IP_PRI225_SHIFT                 0u
#define S32_NVIC_IP_PRI225_WIDTH                 8u
#define S32_NVIC_IP_PRI225(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI225_SHIFT))&S32_NVIC_IP_PRI225_MASK)
#define S32_NVIC_IP_PRI226_MASK                  0xFFu
#define S32_NVIC_IP_PRI226_SHIFT                 0u
#define S32_NVIC_IP_PRI226_WIDTH                 8u
#define S32_NVIC_IP_PRI226(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI226_SHIFT))&S32_NVIC_IP_PRI226_MASK)
#define S32_NVIC_IP_PRI227_MASK                  0xFFu
#define S32_NVIC_IP_PRI227_SHIFT                 0u
#define S32_NVIC_IP_PRI227_WIDTH                 8u
#define S32_NVIC_IP_PRI227(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI227_SHIFT))&S32_NVIC_IP_PRI227_MASK)
#define S32_NVIC_IP_PRI228_MASK                  0xFFu
#define S32_NVIC_IP_PRI228_SHIFT                 0u
#define S32_NVIC_IP_PRI228_WIDTH                 8u
#define S32_NVIC_IP_PRI228(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI228_SHIFT))&S32_NVIC_IP_PRI228_MASK)
#define S32_NVIC_IP_PRI229_MASK                  0xFFu
#define S32_NVIC_IP_PRI229_SHIFT                 0u
#define S32_NVIC_IP_PRI229_WIDTH                 8u
#define S32_NVIC_IP_PRI229(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI229_SHIFT))&S32_NVIC_IP_PRI229_MASK)
#define S32_NVIC_IP_PRI230_MASK                  0xFFu
#define S32_NVIC_IP_PRI230_SHIFT                 0u
#define S32_NVIC_IP_PRI230_WIDTH                 8u
#define S32_NVIC_IP_PRI230(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI230_SHIFT))&S32_NVIC_IP_PRI230_MASK)
#define S32_NVIC_IP_PRI231_MASK                  0xFFu
#define S32_NVIC_IP_PRI231_SHIFT                 0u
#define S32_NVIC_IP_PRI231_WIDTH                 8u
#define S32_NVIC_IP_PRI231(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI231_SHIFT))&S32_NVIC_IP_PRI231_MASK)
#define S32_NVIC_IP_PRI232_MASK                  0xFFu
#define S32_NVIC_IP_PRI232_SHIFT                 0u
#define S32_NVIC_IP_PRI232_WIDTH                 8u
#define S32_NVIC_IP_PRI232(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI232_SHIFT))&S32_NVIC_IP_PRI232_MASK)
#define S32_NVIC_IP_PRI233_MASK                  0xFFu
#define S32_NVIC_IP_PRI233_SHIFT                 0u
#define S32_NVIC_IP_PRI233_WIDTH                 8u
#define S32_NVIC_IP_PRI233(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI233_SHIFT))&S32_NVIC_IP_PRI233_MASK)
#define S32_NVIC_IP_PRI234_MASK                  0xFFu
#define S32_NVIC_IP_PRI234_SHIFT                 0u
#define S32_NVIC_IP_PRI234_WIDTH                 8u
#define S32_NVIC_IP_PRI234(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI234_SHIFT))&S32_NVIC_IP_PRI234_MASK)
#define S32_NVIC_IP_PRI235_MASK                  0xFFu
#define S32_NVIC_IP_PRI235_SHIFT                 0u
#define S32_NVIC_IP_PRI235_WIDTH                 8u
#define S32_NVIC_IP_PRI235(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI235_SHIFT))&S32_NVIC_IP_PRI235_MASK)
#define S32_NVIC_IP_PRI236_MASK                  0xFFu
#define S32_NVIC_IP_PRI236_SHIFT                 0u
#define S32_NVIC_IP_PRI236_WIDTH                 8u
#define S32_NVIC_IP_PRI236(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI236_SHIFT))&S32_NVIC_IP_PRI236_MASK)
#define S32_NVIC_IP_PRI237_MASK                  0xFFu
#define S32_NVIC_IP_PRI237_SHIFT                 0u
#define S32_NVIC_IP_PRI237_WIDTH                 8u
#define S32_NVIC_IP_PRI237(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI237_SHIFT))&S32_NVIC_IP_PRI237_MASK)
#define S32_NVIC_IP_PRI238_MASK                  0xFFu
#define S32_NVIC_IP_PRI238_SHIFT                 0u
#define S32_NVIC_IP_PRI238_WIDTH                 8u
#define S32_NVIC_IP_PRI238(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI238_SHIFT))&S32_NVIC_IP_PRI238_MASK)
#define S32_NVIC_IP_PRI239_MASK                  0xFFu
#define S32_NVIC_IP_PRI239_SHIFT                 0u
#define S32_NVIC_IP_PRI239_WIDTH                 8u
#define S32_NVIC_IP_PRI239(x)                    (((uint8_t)(((uint8_t)(x))<<S32_NVIC_IP_PRI239_SHIFT))&S32_NVIC_IP_PRI239_MASK)
/* STIR Bit Fields */
#define S32_NVIC_STIR_INTID_MASK                 0x1FFu
#define S32_NVIC_STIR_INTID_SHIFT                0u
#define S32_NVIC_STIR_INTID_WIDTH                9u
#define S32_NVIC_STIR_INTID(x)                   (((uint32_t)(((uint32_t)(x))<<S32_NVIC_STIR_INTID_SHIFT))&S32_NVIC_STIR_INTID_MASK)

/*!
 * @}
 */ /* end of group S32_NVIC_Register_Masks */

/*!
 * @}
 */ /* end of group S32_NVIC_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_NVIC_H_) */
