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
 * @file S32K344_SCB.h
 * @version 1.5
 * @date 2020-11-11
 * @brief Peripheral Access Layer for S32K344_SCB
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
#if !defined(S32K344_SCB_H_)  /* Check if memory map has not been already included */
#define S32K344_SCB_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- S32_SCB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup S32_SCB_Peripheral_Access_Layer S32_SCB Peripheral Access Layer
 * @{
 */

/** S32_SCB - Size of Registers Arrays */
#define S32_SCB_ID_MMFR_COUNT                    4u
#define S32_SCB_ID_ISAR_COUNT                    5u
#define S32_SCB_PID_COUNT                        8u
#define S32_SCB_CID_COUNT                        4u

/** S32_SCB - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[8];
  __IO uint32_t ACTLR;                             /**< Auxiliary Control Register, offset: 0x8 */
       uint8_t RESERVED_1[3316];
  __I  uint32_t CPUID;                             /**< CPUID Base Register, offset: 0xD00 */
  __IO uint32_t ICSR;                              /**< Interrupt Control and State Register, offset: 0xD04 */
  __IO uint32_t VTOR;                              /**< Vector Table Offset Register, offset: 0xD08 */
  __IO uint32_t AIRCR;                             /**< Application Interrupt and Reset Control Register, offset: 0xD0C */
  __IO uint32_t SCR;                               /**< System Control Register, offset: 0xD10 */
  __IO uint32_t CCR;                               /**< Configuration and Control Register, offset: 0xD14 */
  __IO uint32_t SHPR1;                             /**< System Handler Priority Register 1, offset: 0xD18 */
  __IO uint32_t SHPR2;                             /**< System Handler Priority Register 2, offset: 0xD1C */
  __IO uint32_t SHPR3;                             /**< System Handler Priority Register 3, offset: 0xD20 */
  __IO uint32_t SHCSR;                             /**< System Handler Control and State Register, offset: 0xD24 */
  __IO uint32_t CFSR;                              /**< Configurable Fault Status Registers, offset: 0xD28 */
  __IO uint32_t HFSR;                              /**< HardFault Status Register, offset: 0xD2C */
  __IO uint32_t DFSR;                              /**< Debug Fault Status Register, offset: 0xD30 */
  __IO uint32_t MMFAR;                             /**< Memanage Fault Address Register, offset: 0xD34 */
  __IO uint32_t BFAR;                              /**< BusFault Address Registerd, offset: 0xD38 */
  __IO uint32_t AFSR;                              /**< Auxiliary Fault Status Register, offset: 0xD3C */
  __I  uint32_t ID_PFR0;                           /**< Processor Feature Register 0, offset: 0xD40 */
  __I  uint32_t ID_PFR1;                           /**< Processor Feature Register 1, offset: 0xD44 */
  __I  uint32_t ID_DFR0;                           /**< Debug Feature Register 0, offset: 0xD48 */
  __I  uint32_t ID_AFR0;                           /**< Auxiliary Feature Register 0, offset: 0xD4C */
  __I  uint32_t ID_MMFR[S32_SCB_ID_MMFR_COUNT];    /**< Memory Model Feature Register 0..Memory Model Feature Register 3, array offset: 0xD50, array step: 0x4 */
  __I  uint32_t ID_ISAR[S32_SCB_ID_ISAR_COUNT];    /**< Instruction Set Attributes Register 0..Instruction Set Attributes Register 4, array offset: 0xD60, array step: 0x4 */
       uint8_t RESERVED_2[4];
  __I  uint32_t CLIDR;                             /**< Cache Level ID Register, offset: 0xD78 */
  __I  uint32_t CTR;                               /**< Cache Type Register, offset: 0xD7C */
  __I  uint32_t CCSIDR;                            /**< Cache Size ID Register, offset: 0xD80 */
  __IO uint32_t CSSELR;                            /**< Cache Size Selection Register, offset: 0xD84 */
  __IO uint32_t CPACR;                             /**< Coprocessor Access Control Register, offset: 0xD88 */
       uint8_t RESERVED_3[372];
  __O  uint32_t STIR;                              /**< Software Triggered Interrupt Register, offset: 0xF00 */
       uint8_t RESERVED_4[48];
  __IO uint32_t FPCCR;                             /**< Floating-point Context Control Register, offset: 0xF34 */
  __IO uint32_t FPCAR;                             /**< Floating-point Context Address Register, offset: 0xF38 */
  __IO uint32_t FPDSCR;                            /**< Floating-point Default Status Control Register, offset: 0xF3C */
       uint8_t RESERVED_5[16];
  __O  uint32_t ICIALLU;                           /**< Instruction cache invalidate all to Point of Unification (PoU), offset: 0xF50 */
       uint8_t RESERVED_6[4];
  __O  uint32_t ICIMVAU;                           /**< Instruction cache invalidate by address to PoU, offset: 0xF58 */
  __O  uint32_t DCIMVAC;                           /**< Data cache invalidate by address to Point of Coherency (PoC), offset: 0xF5C */
  __O  uint32_t DCISW;                             /**< Data cache invalidate by set/way, offset: 0xF60 */
  __O  uint32_t DCCMVAU;                           /**< Data cache by address to PoU, offset: 0xF64 */
  __O  uint32_t DCCMVAC;                           /**< Data cache clean by address to PoC, offset: 0xF68 */
  __O  uint32_t DCCSW;                             /**< Data cache clean by set/way, offset: 0xF6C */
  __O  uint32_t DCCIMVAC;                          /**< Data cache clean and invalidate by address to PoC, offset: 0xF70 */
  __O  uint32_t DCCISW;                            /**< Data cache clean and invalidate by set/way, offset: 0xF74 */
  __I  uint32_t BPIALL;                            /**< Not implemented - RAZ/WI, offset: 0xF78 */
       uint8_t RESERVED_7[20];
  __IO uint32_t ITCMCR;                            /**< Instruction Tightly-Coupled Memory Control Register, offset: 0xF90 */
  __IO uint32_t DTCMCR;                            /**< Data Tightly-Coupled Memory Control Register, offset: 0xF94 */
  __IO uint32_t AHBPCR;                            /**< AHBP control register, offset: 0xF98 */
  __IO uint32_t CACR;                              /**< L1 Cache Control Register, offset: 0xF9C */
  __IO uint32_t AHBSCR;                            /**< AHB Slave Control Register, offset: 0xFA0 */
       uint8_t RESERVED_8[4];
  __IO uint32_t ABFSR;                             /**< Asynchronous Bus Fault Status Register, offset: 0xFA8 */
       uint8_t RESERVED_9[4];
  __IO uint32_t IEBR0;                             /**< Instruction Error bank Register 0, offset: 0xFB0 */
  __IO uint32_t IEBR1h;                            /**< Instruction Error bank Register 1, offset: 0xFB4 */
  __IO uint32_t DEBR0h;                            /**< Data Error bank Register 0, offset: 0xFB8 */
  __IO uint32_t DEBR1h;                            /**< Data Error bank Register 1, offset: 0xFBC */
       uint8_t RESERVED_10[16];
  __I  uint32_t PID[S32_SCB_PID_COUNT];            /**< Peripheral identification register 0..Peripheral identification register 7, array offset: 0xFD0, array step: 0x4 */
  __I  uint32_t CID[S32_SCB_CID_COUNT];            /**< Component identification register 0..Component identification register 3, array offset: 0xFF0, array step: 0x4 */
} S32_SCB_Type, *S32_SCB_MemMapPtr;

 /** Number of instances of the S32_SCB module. */
#define S32_SCB_INSTANCE_COUNT                   (1u)

/* S32_SCB - Peripheral instance base addresses */
/** Peripheral S32_SCB base address */
#define S32_SCB_BASE                             (0xE000E000u)
/** Peripheral S32_SCB base pointer */
#define S32_SCB                                  ((S32_SCB_Type *)S32_SCB_BASE)
/** Array initializer of S32_SCB peripheral base addresses */
#define S32_SCB_BASE_ADDRS                       { S32_SCB_BASE }
/** Array initializer of S32_SCB peripheral base pointers */
#define S32_SCB_BASE_PTRS                        { S32_SCB }

/* ----------------------------------------------------------------------------
   -- S32_SCB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup S32_SCB_Register_Masks S32_SCB Register Masks
 * @{
 */

/* ACTLR Bit Fields */
#define S32_SCB_ACTLR_ACTLR_MASK                 0xFFFFFFFFu
#define S32_SCB_ACTLR_ACTLR_SHIFT                0u
#define S32_SCB_ACTLR_ACTLR_WIDTH                32u
#define S32_SCB_ACTLR_ACTLR(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_ACTLR_ACTLR_SHIFT))&S32_SCB_ACTLR_ACTLR_MASK)
/* CPUID Bit Fields */
#define S32_SCB_CPUID_REVISION_MASK              0xFu
#define S32_SCB_CPUID_REVISION_SHIFT             0u
#define S32_SCB_CPUID_REVISION_WIDTH             4u
#define S32_SCB_CPUID_REVISION(x)                (((uint32_t)(((uint32_t)(x))<<S32_SCB_CPUID_REVISION_SHIFT))&S32_SCB_CPUID_REVISION_MASK)
#define S32_SCB_CPUID_PARTNO_MASK                0xFFF0u
#define S32_SCB_CPUID_PARTNO_SHIFT               4u
#define S32_SCB_CPUID_PARTNO_WIDTH               12u
#define S32_SCB_CPUID_PARTNO(x)                  (((uint32_t)(((uint32_t)(x))<<S32_SCB_CPUID_PARTNO_SHIFT))&S32_SCB_CPUID_PARTNO_MASK)
#define S32_SCB_CPUID_VARIANT_MASK               0xF00000u
#define S32_SCB_CPUID_VARIANT_SHIFT              20u
#define S32_SCB_CPUID_VARIANT_WIDTH              4u
#define S32_SCB_CPUID_VARIANT(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_CPUID_VARIANT_SHIFT))&S32_SCB_CPUID_VARIANT_MASK)
#define S32_SCB_CPUID_IMPLEMENTER_MASK           0xFF000000u
#define S32_SCB_CPUID_IMPLEMENTER_SHIFT          24u
#define S32_SCB_CPUID_IMPLEMENTER_WIDTH          8u
#define S32_SCB_CPUID_IMPLEMENTER(x)             (((uint32_t)(((uint32_t)(x))<<S32_SCB_CPUID_IMPLEMENTER_SHIFT))&S32_SCB_CPUID_IMPLEMENTER_MASK)
/* ICSR Bit Fields */
#define S32_SCB_ICSR_VECTACTIVE_MASK             0x1FFu
#define S32_SCB_ICSR_VECTACTIVE_SHIFT            0u
#define S32_SCB_ICSR_VECTACTIVE_WIDTH            9u
#define S32_SCB_ICSR_VECTACTIVE(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_ICSR_VECTACTIVE_SHIFT))&S32_SCB_ICSR_VECTACTIVE_MASK)
#define S32_SCB_ICSR_RETTOBASE_MASK              0x800u
#define S32_SCB_ICSR_RETTOBASE_SHIFT             11u
#define S32_SCB_ICSR_RETTOBASE_WIDTH             1u
#define S32_SCB_ICSR_RETTOBASE(x)                (((uint32_t)(((uint32_t)(x))<<S32_SCB_ICSR_RETTOBASE_SHIFT))&S32_SCB_ICSR_RETTOBASE_MASK)
#define S32_SCB_ICSR_VECTPENDING_MASK            0x3F000u
#define S32_SCB_ICSR_VECTPENDING_SHIFT           12u
#define S32_SCB_ICSR_VECTPENDING_WIDTH           6u
#define S32_SCB_ICSR_VECTPENDING(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_ICSR_VECTPENDING_SHIFT))&S32_SCB_ICSR_VECTPENDING_MASK)
#define S32_SCB_ICSR_ISRPENDING_MASK             0x400000u
#define S32_SCB_ICSR_ISRPENDING_SHIFT            22u
#define S32_SCB_ICSR_ISRPENDING_WIDTH            1u
#define S32_SCB_ICSR_ISRPENDING(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_ICSR_ISRPENDING_SHIFT))&S32_SCB_ICSR_ISRPENDING_MASK)
#define S32_SCB_ICSR_ISRPREEMPT_MASK             0x800000u
#define S32_SCB_ICSR_ISRPREEMPT_SHIFT            23u
#define S32_SCB_ICSR_ISRPREEMPT_WIDTH            1u
#define S32_SCB_ICSR_ISRPREEMPT(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_ICSR_ISRPREEMPT_SHIFT))&S32_SCB_ICSR_ISRPREEMPT_MASK)
#define S32_SCB_ICSR_PENDSTCLR_MASK              0x2000000u
#define S32_SCB_ICSR_PENDSTCLR_SHIFT             25u
#define S32_SCB_ICSR_PENDSTCLR_WIDTH             1u
#define S32_SCB_ICSR_PENDSTCLR(x)                (((uint32_t)(((uint32_t)(x))<<S32_SCB_ICSR_PENDSTCLR_SHIFT))&S32_SCB_ICSR_PENDSTCLR_MASK)
#define S32_SCB_ICSR_PENDSTSET_MASK              0x4000000u
#define S32_SCB_ICSR_PENDSTSET_SHIFT             26u
#define S32_SCB_ICSR_PENDSTSET_WIDTH             1u
#define S32_SCB_ICSR_PENDSTSET(x)                (((uint32_t)(((uint32_t)(x))<<S32_SCB_ICSR_PENDSTSET_SHIFT))&S32_SCB_ICSR_PENDSTSET_MASK)
#define S32_SCB_ICSR_PENDSVCLR_MASK              0x8000000u
#define S32_SCB_ICSR_PENDSVCLR_SHIFT             27u
#define S32_SCB_ICSR_PENDSVCLR_WIDTH             1u
#define S32_SCB_ICSR_PENDSVCLR(x)                (((uint32_t)(((uint32_t)(x))<<S32_SCB_ICSR_PENDSVCLR_SHIFT))&S32_SCB_ICSR_PENDSVCLR_MASK)
#define S32_SCB_ICSR_PENDSVSET_MASK              0x10000000u
#define S32_SCB_ICSR_PENDSVSET_SHIFT             28u
#define S32_SCB_ICSR_PENDSVSET_WIDTH             1u
#define S32_SCB_ICSR_PENDSVSET(x)                (((uint32_t)(((uint32_t)(x))<<S32_SCB_ICSR_PENDSVSET_SHIFT))&S32_SCB_ICSR_PENDSVSET_MASK)
#define S32_SCB_ICSR_NMIPENDSET_MASK             0x80000000u
#define S32_SCB_ICSR_NMIPENDSET_SHIFT            31u
#define S32_SCB_ICSR_NMIPENDSET_WIDTH            1u
#define S32_SCB_ICSR_NMIPENDSET(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_ICSR_NMIPENDSET_SHIFT))&S32_SCB_ICSR_NMIPENDSET_MASK)
/* VTOR Bit Fields */
#define S32_SCB_VTOR_TBLOFF_MASK                 0xFFFFFF80u
#define S32_SCB_VTOR_TBLOFF_SHIFT                7u
#define S32_SCB_VTOR_TBLOFF_WIDTH                25u
#define S32_SCB_VTOR_TBLOFF(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_VTOR_TBLOFF_SHIFT))&S32_SCB_VTOR_TBLOFF_MASK)
/* AIRCR Bit Fields */
#define S32_SCB_AIRCR_AIRCR_MASK                 0xFFFFFFFFu
#define S32_SCB_AIRCR_AIRCR_SHIFT                0u
#define S32_SCB_AIRCR_AIRCR_WIDTH                32u
#define S32_SCB_AIRCR_AIRCR(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_AIRCR_AIRCR_SHIFT))&S32_SCB_AIRCR_AIRCR_MASK)
/* SCR Bit Fields */
#define S32_SCB_SCR_SLEEPONEXIT_MASK             0x2u
#define S32_SCB_SCR_SLEEPONEXIT_SHIFT            1u
#define S32_SCB_SCR_SLEEPONEXIT_WIDTH            1u
#define S32_SCB_SCR_SLEEPONEXIT(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_SCR_SLEEPONEXIT_SHIFT))&S32_SCB_SCR_SLEEPONEXIT_MASK)
#define S32_SCB_SCR_SLEEPDEEP_MASK               0x4u
#define S32_SCB_SCR_SLEEPDEEP_SHIFT              2u
#define S32_SCB_SCR_SLEEPDEEP_WIDTH              1u
#define S32_SCB_SCR_SLEEPDEEP(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_SCR_SLEEPDEEP_SHIFT))&S32_SCB_SCR_SLEEPDEEP_MASK)
#define S32_SCB_SCR_SEVONPEND_MASK               0x10u
#define S32_SCB_SCR_SEVONPEND_SHIFT              4u
#define S32_SCB_SCR_SEVONPEND_WIDTH              1u
#define S32_SCB_SCR_SEVONPEND(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_SCR_SEVONPEND_SHIFT))&S32_SCB_SCR_SEVONPEND_MASK)
/* CCR Bit Fields */
#define S32_SCB_CCR_CCR_MASK                     0xFFFFFFFFu
#define S32_SCB_CCR_CCR_SHIFT                    0u
#define S32_SCB_CCR_CCR_WIDTH                    32u
#define S32_SCB_CCR_CCR(x)                       (((uint32_t)(((uint32_t)(x))<<S32_SCB_CCR_CCR_SHIFT))&S32_SCB_CCR_CCR_MASK)
/* SHPR1 Bit Fields */
#define S32_SCB_SHPR1_SHPR1_MASK                 0xFFFFFFFFu
#define S32_SCB_SHPR1_SHPR1_SHIFT                0u
#define S32_SCB_SHPR1_SHPR1_WIDTH                32u
#define S32_SCB_SHPR1_SHPR1(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHPR1_SHPR1_SHIFT))&S32_SCB_SHPR1_SHPR1_MASK)
/* SHPR2 Bit Fields */
#define S32_SCB_SHPR2_SHPR2_MASK                 0xFFFFFFFFu
#define S32_SCB_SHPR2_SHPR2_SHIFT                0u
#define S32_SCB_SHPR2_SHPR2_WIDTH                32u
#define S32_SCB_SHPR2_SHPR2(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHPR2_SHPR2_SHIFT))&S32_SCB_SHPR2_SHPR2_MASK)
/* SHPR3 Bit Fields */
#define S32_SCB_SHPR3_SHPR3_MASK                 0xFFFFFFFFu
#define S32_SCB_SHPR3_SHPR3_SHIFT                0u
#define S32_SCB_SHPR3_SHPR3_WIDTH                32u
#define S32_SCB_SHPR3_SHPR3(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHPR3_SHPR3_SHIFT))&S32_SCB_SHPR3_SHPR3_MASK)
/* SHCSR Bit Fields */
#define S32_SCB_SHCSR_MEMFAULTACT_MASK           0x1u
#define S32_SCB_SHCSR_MEMFAULTACT_SHIFT          0u
#define S32_SCB_SHCSR_MEMFAULTACT_WIDTH          1u
#define S32_SCB_SHCSR_MEMFAULTACT(x)             (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_MEMFAULTACT_SHIFT))&S32_SCB_SHCSR_MEMFAULTACT_MASK)
#define S32_SCB_SHCSR_BUSFAULTACT_MASK           0x2u
#define S32_SCB_SHCSR_BUSFAULTACT_SHIFT          1u
#define S32_SCB_SHCSR_BUSFAULTACT_WIDTH          1u
#define S32_SCB_SHCSR_BUSFAULTACT(x)             (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_BUSFAULTACT_SHIFT))&S32_SCB_SHCSR_BUSFAULTACT_MASK)
#define S32_SCB_SHCSR_USGFAULTACT_MASK           0x8u
#define S32_SCB_SHCSR_USGFAULTACT_SHIFT          3u
#define S32_SCB_SHCSR_USGFAULTACT_WIDTH          1u
#define S32_SCB_SHCSR_USGFAULTACT(x)             (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_USGFAULTACT_SHIFT))&S32_SCB_SHCSR_USGFAULTACT_MASK)
#define S32_SCB_SHCSR_SVCALLACT_MASK             0x80u
#define S32_SCB_SHCSR_SVCALLACT_SHIFT            7u
#define S32_SCB_SHCSR_SVCALLACT_WIDTH            1u
#define S32_SCB_SHCSR_SVCALLACT(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_SVCALLACT_SHIFT))&S32_SCB_SHCSR_SVCALLACT_MASK)
#define S32_SCB_SHCSR_MONITORACT_MASK            0x100u
#define S32_SCB_SHCSR_MONITORACT_SHIFT           8u
#define S32_SCB_SHCSR_MONITORACT_WIDTH           1u
#define S32_SCB_SHCSR_MONITORACT(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_MONITORACT_SHIFT))&S32_SCB_SHCSR_MONITORACT_MASK)
#define S32_SCB_SHCSR_PENDSVACT_MASK             0x400u
#define S32_SCB_SHCSR_PENDSVACT_SHIFT            10u
#define S32_SCB_SHCSR_PENDSVACT_WIDTH            1u
#define S32_SCB_SHCSR_PENDSVACT(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_PENDSVACT_SHIFT))&S32_SCB_SHCSR_PENDSVACT_MASK)
#define S32_SCB_SHCSR_SYSTICKACT_MASK            0x800u
#define S32_SCB_SHCSR_SYSTICKACT_SHIFT           11u
#define S32_SCB_SHCSR_SYSTICKACT_WIDTH           1u
#define S32_SCB_SHCSR_SYSTICKACT(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_SYSTICKACT_SHIFT))&S32_SCB_SHCSR_SYSTICKACT_MASK)
#define S32_SCB_SHCSR_USGFAULTPENDED_MASK        0x1000u
#define S32_SCB_SHCSR_USGFAULTPENDED_SHIFT       12u
#define S32_SCB_SHCSR_USGFAULTPENDED_WIDTH       1u
#define S32_SCB_SHCSR_USGFAULTPENDED(x)          (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_USGFAULTPENDED_SHIFT))&S32_SCB_SHCSR_USGFAULTPENDED_MASK)
#define S32_SCB_SHCSR_MEMFAULTPENDED_MASK        0x2000u
#define S32_SCB_SHCSR_MEMFAULTPENDED_SHIFT       13u
#define S32_SCB_SHCSR_MEMFAULTPENDED_WIDTH       1u
#define S32_SCB_SHCSR_MEMFAULTPENDED(x)          (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_MEMFAULTPENDED_SHIFT))&S32_SCB_SHCSR_MEMFAULTPENDED_MASK)
#define S32_SCB_SHCSR_BUSFAULTPENDED_MASK        0x4000u
#define S32_SCB_SHCSR_BUSFAULTPENDED_SHIFT       14u
#define S32_SCB_SHCSR_BUSFAULTPENDED_WIDTH       1u
#define S32_SCB_SHCSR_BUSFAULTPENDED(x)          (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_BUSFAULTPENDED_SHIFT))&S32_SCB_SHCSR_BUSFAULTPENDED_MASK)
#define S32_SCB_SHCSR_SVCALLPENDED_MASK          0x8000u
#define S32_SCB_SHCSR_SVCALLPENDED_SHIFT         15u
#define S32_SCB_SHCSR_SVCALLPENDED_WIDTH         1u
#define S32_SCB_SHCSR_SVCALLPENDED(x)            (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_SVCALLPENDED_SHIFT))&S32_SCB_SHCSR_SVCALLPENDED_MASK)
#define S32_SCB_SHCSR_MEMFAULTENA_MASK           0x10000u
#define S32_SCB_SHCSR_MEMFAULTENA_SHIFT          16u
#define S32_SCB_SHCSR_MEMFAULTENA_WIDTH          1u
#define S32_SCB_SHCSR_MEMFAULTENA(x)             (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_MEMFAULTENA_SHIFT))&S32_SCB_SHCSR_MEMFAULTENA_MASK)
#define S32_SCB_SHCSR_BUSFAULTENA_MASK           0x20000u
#define S32_SCB_SHCSR_BUSFAULTENA_SHIFT          17u
#define S32_SCB_SHCSR_BUSFAULTENA_WIDTH          1u
#define S32_SCB_SHCSR_BUSFAULTENA(x)             (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_BUSFAULTENA_SHIFT))&S32_SCB_SHCSR_BUSFAULTENA_MASK)
#define S32_SCB_SHCSR_USGFAULTENA_MASK           0x40000u
#define S32_SCB_SHCSR_USGFAULTENA_SHIFT          18u
#define S32_SCB_SHCSR_USGFAULTENA_WIDTH          1u
#define S32_SCB_SHCSR_USGFAULTENA(x)             (((uint32_t)(((uint32_t)(x))<<S32_SCB_SHCSR_USGFAULTENA_SHIFT))&S32_SCB_SHCSR_USGFAULTENA_MASK)
/* CFSR Bit Fields */
#define S32_SCB_CFSR_MMFSR_IACCVIOL_MASK         0x1u
#define S32_SCB_CFSR_MMFSR_IACCVIOL_SHIFT        0u
#define S32_SCB_CFSR_MMFSR_IACCVIOL_WIDTH        1u
#define S32_SCB_CFSR_MMFSR_IACCVIOL(x)           (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_MMFSR_IACCVIOL_SHIFT))&S32_SCB_CFSR_MMFSR_IACCVIOL_MASK)
#define S32_SCB_CFSR_MMFSR_DACCVIOL_MASK         0x2u
#define S32_SCB_CFSR_MMFSR_DACCVIOL_SHIFT        1u
#define S32_SCB_CFSR_MMFSR_DACCVIOL_WIDTH        1u
#define S32_SCB_CFSR_MMFSR_DACCVIOL(x)           (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_MMFSR_DACCVIOL_SHIFT))&S32_SCB_CFSR_MMFSR_DACCVIOL_MASK)
#define S32_SCB_CFSR_MMFSR_MUNSTKERR_MASK        0x8u
#define S32_SCB_CFSR_MMFSR_MUNSTKERR_SHIFT       3u
#define S32_SCB_CFSR_MMFSR_MUNSTKERR_WIDTH       1u
#define S32_SCB_CFSR_MMFSR_MUNSTKERR(x)          (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_MMFSR_MUNSTKERR_SHIFT))&S32_SCB_CFSR_MMFSR_MUNSTKERR_MASK)
#define S32_SCB_CFSR_MMFSR_MSTKERR_MASK          0x10u
#define S32_SCB_CFSR_MMFSR_MSTKERR_SHIFT         4u
#define S32_SCB_CFSR_MMFSR_MSTKERR_WIDTH         1u
#define S32_SCB_CFSR_MMFSR_MSTKERR(x)            (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_MMFSR_MSTKERR_SHIFT))&S32_SCB_CFSR_MMFSR_MSTKERR_MASK)
#define S32_SCB_CFSR_MMFSR_MLSPERR_MASK          0x20u
#define S32_SCB_CFSR_MMFSR_MLSPERR_SHIFT         5u
#define S32_SCB_CFSR_MMFSR_MLSPERR_WIDTH         1u
#define S32_SCB_CFSR_MMFSR_MLSPERR(x)            (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_MMFSR_MLSPERR_SHIFT))&S32_SCB_CFSR_MMFSR_MLSPERR_MASK)
#define S32_SCB_CFSR_MMFSR_MMARVALID_MASK        0x80u
#define S32_SCB_CFSR_MMFSR_MMARVALID_SHIFT       7u
#define S32_SCB_CFSR_MMFSR_MMARVALID_WIDTH       1u
#define S32_SCB_CFSR_MMFSR_MMARVALID(x)          (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_MMFSR_MMARVALID_SHIFT))&S32_SCB_CFSR_MMFSR_MMARVALID_MASK)
#define S32_SCB_CFSR_BFSR_IBUSERR_MASK           0x100u
#define S32_SCB_CFSR_BFSR_IBUSERR_SHIFT          8u
#define S32_SCB_CFSR_BFSR_IBUSERR_WIDTH          1u
#define S32_SCB_CFSR_BFSR_IBUSERR(x)             (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_BFSR_IBUSERR_SHIFT))&S32_SCB_CFSR_BFSR_IBUSERR_MASK)
#define S32_SCB_CFSR_BFSR_PRECISERR_MASK         0x200u
#define S32_SCB_CFSR_BFSR_PRECISERR_SHIFT        9u
#define S32_SCB_CFSR_BFSR_PRECISERR_WIDTH        1u
#define S32_SCB_CFSR_BFSR_PRECISERR(x)           (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_BFSR_PRECISERR_SHIFT))&S32_SCB_CFSR_BFSR_PRECISERR_MASK)
#define S32_SCB_CFSR_BFSR_IMPRECISERR_MASK       0x400u
#define S32_SCB_CFSR_BFSR_IMPRECISERR_SHIFT      10u
#define S32_SCB_CFSR_BFSR_IMPRECISERR_WIDTH      1u
#define S32_SCB_CFSR_BFSR_IMPRECISERR(x)         (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_BFSR_IMPRECISERR_SHIFT))&S32_SCB_CFSR_BFSR_IMPRECISERR_MASK)
#define S32_SCB_CFSR_BFSR_UNSTKERR_MASK          0x800u
#define S32_SCB_CFSR_BFSR_UNSTKERR_SHIFT         11u
#define S32_SCB_CFSR_BFSR_UNSTKERR_WIDTH         1u
#define S32_SCB_CFSR_BFSR_UNSTKERR(x)            (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_BFSR_UNSTKERR_SHIFT))&S32_SCB_CFSR_BFSR_UNSTKERR_MASK)
#define S32_SCB_CFSR_BFSR_STKERR_MASK            0x1000u
#define S32_SCB_CFSR_BFSR_STKERR_SHIFT           12u
#define S32_SCB_CFSR_BFSR_STKERR_WIDTH           1u
#define S32_SCB_CFSR_BFSR_STKERR(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_BFSR_STKERR_SHIFT))&S32_SCB_CFSR_BFSR_STKERR_MASK)
#define S32_SCB_CFSR_BFSR_LSPERR_MASK            0x2000u
#define S32_SCB_CFSR_BFSR_LSPERR_SHIFT           13u
#define S32_SCB_CFSR_BFSR_LSPERR_WIDTH           1u
#define S32_SCB_CFSR_BFSR_LSPERR(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_BFSR_LSPERR_SHIFT))&S32_SCB_CFSR_BFSR_LSPERR_MASK)
#define S32_SCB_CFSR_BFSR_BFARVALID_MASK         0x8000u
#define S32_SCB_CFSR_BFSR_BFARVALID_SHIFT        15u
#define S32_SCB_CFSR_BFSR_BFARVALID_WIDTH        1u
#define S32_SCB_CFSR_BFSR_BFARVALID(x)           (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_BFSR_BFARVALID_SHIFT))&S32_SCB_CFSR_BFSR_BFARVALID_MASK)
#define S32_SCB_CFSR_UFSR_UNDEFINSTR_MASK        0x10000u
#define S32_SCB_CFSR_UFSR_UNDEFINSTR_SHIFT       16u
#define S32_SCB_CFSR_UFSR_UNDEFINSTR_WIDTH       1u
#define S32_SCB_CFSR_UFSR_UNDEFINSTR(x)          (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_UFSR_UNDEFINSTR_SHIFT))&S32_SCB_CFSR_UFSR_UNDEFINSTR_MASK)
#define S32_SCB_CFSR_UFSR_INVSTATE_MASK          0x20000u
#define S32_SCB_CFSR_UFSR_INVSTATE_SHIFT         17u
#define S32_SCB_CFSR_UFSR_INVSTATE_WIDTH         1u
#define S32_SCB_CFSR_UFSR_INVSTATE(x)            (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_UFSR_INVSTATE_SHIFT))&S32_SCB_CFSR_UFSR_INVSTATE_MASK)
#define S32_SCB_CFSR_UFSR_INVPC_MASK             0x40000u
#define S32_SCB_CFSR_UFSR_INVPC_SHIFT            18u
#define S32_SCB_CFSR_UFSR_INVPC_WIDTH            1u
#define S32_SCB_CFSR_UFSR_INVPC(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_UFSR_INVPC_SHIFT))&S32_SCB_CFSR_UFSR_INVPC_MASK)
#define S32_SCB_CFSR_UFSR_NOCP_MASK              0x80000u
#define S32_SCB_CFSR_UFSR_NOCP_SHIFT             19u
#define S32_SCB_CFSR_UFSR_NOCP_WIDTH             1u
#define S32_SCB_CFSR_UFSR_NOCP(x)                (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_UFSR_NOCP_SHIFT))&S32_SCB_CFSR_UFSR_NOCP_MASK)
#define S32_SCB_CFSR_UFSR_UNALIGNED_MASK         0x1000000u
#define S32_SCB_CFSR_UFSR_UNALIGNED_SHIFT        24u
#define S32_SCB_CFSR_UFSR_UNALIGNED_WIDTH        1u
#define S32_SCB_CFSR_UFSR_UNALIGNED(x)           (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_UFSR_UNALIGNED_SHIFT))&S32_SCB_CFSR_UFSR_UNALIGNED_MASK)
#define S32_SCB_CFSR_UFSR_DIVBYZERO_MASK         0x2000000u
#define S32_SCB_CFSR_UFSR_DIVBYZERO_SHIFT        25u
#define S32_SCB_CFSR_UFSR_DIVBYZERO_WIDTH        1u
#define S32_SCB_CFSR_UFSR_DIVBYZERO(x)           (((uint32_t)(((uint32_t)(x))<<S32_SCB_CFSR_UFSR_DIVBYZERO_SHIFT))&S32_SCB_CFSR_UFSR_DIVBYZERO_MASK)
/* HFSR Bit Fields */
#define S32_SCB_HFSR_HFSR_MASK                   0xFFFFFFFFu
#define S32_SCB_HFSR_HFSR_SHIFT                  0u
#define S32_SCB_HFSR_HFSR_WIDTH                  32u
#define S32_SCB_HFSR_HFSR(x)                     (((uint32_t)(((uint32_t)(x))<<S32_SCB_HFSR_HFSR_SHIFT))&S32_SCB_HFSR_HFSR_MASK)
/* DFSR Bit Fields */
#define S32_SCB_DFSR_DFSR_MASK                   0xFFFFFFFFu
#define S32_SCB_DFSR_DFSR_SHIFT                  0u
#define S32_SCB_DFSR_DFSR_WIDTH                  32u
#define S32_SCB_DFSR_DFSR(x)                     (((uint32_t)(((uint32_t)(x))<<S32_SCB_DFSR_DFSR_SHIFT))&S32_SCB_DFSR_DFSR_MASK)
/* MMFAR Bit Fields */
#define S32_SCB_MMFAR_MMFAR_MASK                 0xFFFFFFFFu
#define S32_SCB_MMFAR_MMFAR_SHIFT                0u
#define S32_SCB_MMFAR_MMFAR_WIDTH                32u
#define S32_SCB_MMFAR_MMFAR(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_MMFAR_MMFAR_SHIFT))&S32_SCB_MMFAR_MMFAR_MASK)
/* BFAR Bit Fields */
#define S32_SCB_BFAR_BFAR_MASK                   0xFFFFFFFFu
#define S32_SCB_BFAR_BFAR_SHIFT                  0u
#define S32_SCB_BFAR_BFAR_WIDTH                  32u
#define S32_SCB_BFAR_BFAR(x)                     (((uint32_t)(((uint32_t)(x))<<S32_SCB_BFAR_BFAR_SHIFT))&S32_SCB_BFAR_BFAR_MASK)
/* AFSR Bit Fields */
#define S32_SCB_AFSR_AFSR_MASK                   0xFFFFFFFFu
#define S32_SCB_AFSR_AFSR_SHIFT                  0u
#define S32_SCB_AFSR_AFSR_WIDTH                  32u
#define S32_SCB_AFSR_AFSR(x)                     (((uint32_t)(((uint32_t)(x))<<S32_SCB_AFSR_AFSR_SHIFT))&S32_SCB_AFSR_AFSR_MASK)
/* ID_PFR0 Bit Fields */
#define S32_SCB_ID_PFR0_ID_PFR0_MASK             0xFFFFFFFFu
#define S32_SCB_ID_PFR0_ID_PFR0_SHIFT            0u
#define S32_SCB_ID_PFR0_ID_PFR0_WIDTH            32u
#define S32_SCB_ID_PFR0_ID_PFR0(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_ID_PFR0_ID_PFR0_SHIFT))&S32_SCB_ID_PFR0_ID_PFR0_MASK)
/* ID_PFR1 Bit Fields */
#define S32_SCB_ID_PFR1_ID_PFR1_MASK             0xFFFFFFFFu
#define S32_SCB_ID_PFR1_ID_PFR1_SHIFT            0u
#define S32_SCB_ID_PFR1_ID_PFR1_WIDTH            32u
#define S32_SCB_ID_PFR1_ID_PFR1(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_ID_PFR1_ID_PFR1_SHIFT))&S32_SCB_ID_PFR1_ID_PFR1_MASK)
/* ID_DFR0 Bit Fields */
#define S32_SCB_ID_DFR0_ID_DFR0_MASK             0xFFFFFFFFu
#define S32_SCB_ID_DFR0_ID_DFR0_SHIFT            0u
#define S32_SCB_ID_DFR0_ID_DFR0_WIDTH            32u
#define S32_SCB_ID_DFR0_ID_DFR0(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_ID_DFR0_ID_DFR0_SHIFT))&S32_SCB_ID_DFR0_ID_DFR0_MASK)
/* ID_AFR0 Bit Fields */
#define S32_SCB_ID_AFR0_ID_AFR0_MASK             0xFFFFFFFFu
#define S32_SCB_ID_AFR0_ID_AFR0_SHIFT            0u
#define S32_SCB_ID_AFR0_ID_AFR0_WIDTH            32u
#define S32_SCB_ID_AFR0_ID_AFR0(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_ID_AFR0_ID_AFR0_SHIFT))&S32_SCB_ID_AFR0_ID_AFR0_MASK)
/* ID_MMFR Bit Fields */
#define S32_SCB_ID_MMFR_ID_MMFR0_MASK            0xFFFFFFFFu
#define S32_SCB_ID_MMFR_ID_MMFR0_SHIFT           0u
#define S32_SCB_ID_MMFR_ID_MMFR0_WIDTH           32u
#define S32_SCB_ID_MMFR_ID_MMFR0(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_ID_MMFR_ID_MMFR0_SHIFT))&S32_SCB_ID_MMFR_ID_MMFR0_MASK)
#define S32_SCB_ID_MMFR_ID_MMFR1_MASK            0xFFFFFFFFu
#define S32_SCB_ID_MMFR_ID_MMFR1_SHIFT           0u
#define S32_SCB_ID_MMFR_ID_MMFR1_WIDTH           32u
#define S32_SCB_ID_MMFR_ID_MMFR1(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_ID_MMFR_ID_MMFR1_SHIFT))&S32_SCB_ID_MMFR_ID_MMFR1_MASK)
#define S32_SCB_ID_MMFR_ID_MMFR2_MASK            0xFFFFFFFFu
#define S32_SCB_ID_MMFR_ID_MMFR2_SHIFT           0u
#define S32_SCB_ID_MMFR_ID_MMFR2_WIDTH           32u
#define S32_SCB_ID_MMFR_ID_MMFR2(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_ID_MMFR_ID_MMFR2_SHIFT))&S32_SCB_ID_MMFR_ID_MMFR2_MASK)
#define S32_SCB_ID_MMFR_ID_MMFR3_MASK            0xFFFFFFFFu
#define S32_SCB_ID_MMFR_ID_MMFR3_SHIFT           0u
#define S32_SCB_ID_MMFR_ID_MMFR3_WIDTH           32u
#define S32_SCB_ID_MMFR_ID_MMFR3(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_ID_MMFR_ID_MMFR3_SHIFT))&S32_SCB_ID_MMFR_ID_MMFR3_MASK)
/* ID_ISAR Bit Fields */
#define S32_SCB_ID_ISAR_ID_ISAR0_MASK            0xFFFFFFFFu
#define S32_SCB_ID_ISAR_ID_ISAR0_SHIFT           0u
#define S32_SCB_ID_ISAR_ID_ISAR0_WIDTH           32u
#define S32_SCB_ID_ISAR_ID_ISAR0(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_ID_ISAR_ID_ISAR0_SHIFT))&S32_SCB_ID_ISAR_ID_ISAR0_MASK)
#define S32_SCB_ID_ISAR_ID_ISAR1_MASK            0xFFFFFFFFu
#define S32_SCB_ID_ISAR_ID_ISAR1_SHIFT           0u
#define S32_SCB_ID_ISAR_ID_ISAR1_WIDTH           32u
#define S32_SCB_ID_ISAR_ID_ISAR1(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_ID_ISAR_ID_ISAR1_SHIFT))&S32_SCB_ID_ISAR_ID_ISAR1_MASK)
#define S32_SCB_ID_ISAR_ID_ISAR2_MASK            0xFFFFFFFFu
#define S32_SCB_ID_ISAR_ID_ISAR2_SHIFT           0u
#define S32_SCB_ID_ISAR_ID_ISAR2_WIDTH           32u
#define S32_SCB_ID_ISAR_ID_ISAR2(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_ID_ISAR_ID_ISAR2_SHIFT))&S32_SCB_ID_ISAR_ID_ISAR2_MASK)
#define S32_SCB_ID_ISAR_ID_ISAR3_MASK            0xFFFFFFFFu
#define S32_SCB_ID_ISAR_ID_ISAR3_SHIFT           0u
#define S32_SCB_ID_ISAR_ID_ISAR3_WIDTH           32u
#define S32_SCB_ID_ISAR_ID_ISAR3(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_ID_ISAR_ID_ISAR3_SHIFT))&S32_SCB_ID_ISAR_ID_ISAR3_MASK)
#define S32_SCB_ID_ISAR_ID_ISAR4_MASK            0xFFFFFFFFu
#define S32_SCB_ID_ISAR_ID_ISAR4_SHIFT           0u
#define S32_SCB_ID_ISAR_ID_ISAR4_WIDTH           32u
#define S32_SCB_ID_ISAR_ID_ISAR4(x)              (((uint32_t)(((uint32_t)(x))<<S32_SCB_ID_ISAR_ID_ISAR4_SHIFT))&S32_SCB_ID_ISAR_ID_ISAR4_MASK)
/* CLIDR Bit Fields */
#define S32_SCB_CLIDR_CLIDR_MASK                 0xFFFFFFFFu
#define S32_SCB_CLIDR_CLIDR_SHIFT                0u
#define S32_SCB_CLIDR_CLIDR_WIDTH                32u
#define S32_SCB_CLIDR_CLIDR(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_CLIDR_CLIDR_SHIFT))&S32_SCB_CLIDR_CLIDR_MASK)
/* CTR Bit Fields */
#define S32_SCB_CTR_CTR_MASK                     0xFFFFFFFFu
#define S32_SCB_CTR_CTR_SHIFT                    0u
#define S32_SCB_CTR_CTR_WIDTH                    32u
#define S32_SCB_CTR_CTR(x)                       (((uint32_t)(((uint32_t)(x))<<S32_SCB_CTR_CTR_SHIFT))&S32_SCB_CTR_CTR_MASK)
/* CCSIDR Bit Fields */
#define S32_SCB_CCSIDR_CCSIDR_MASK               0xFFFFFFFFu
#define S32_SCB_CCSIDR_CCSIDR_SHIFT              0u
#define S32_SCB_CCSIDR_CCSIDR_WIDTH              32u
#define S32_SCB_CCSIDR_CCSIDR(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_CCSIDR_CCSIDR_SHIFT))&S32_SCB_CCSIDR_CCSIDR_MASK)
/* CSSELR Bit Fields */
#define S32_SCB_CSSELR_CSSELR_MASK               0xFFFFFFFFu
#define S32_SCB_CSSELR_CSSELR_SHIFT              0u
#define S32_SCB_CSSELR_CSSELR_WIDTH              32u
#define S32_SCB_CSSELR_CSSELR(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_CSSELR_CSSELR_SHIFT))&S32_SCB_CSSELR_CSSELR_MASK)
/* STIR Bit Fields */
#define S32_SCB_STIR_STIR_MASK                   0xFFFFFFFFu
#define S32_SCB_STIR_STIR_SHIFT                  0u
#define S32_SCB_STIR_STIR_WIDTH                  32u
#define S32_SCB_STIR_STIR(x)                     (((uint32_t)(((uint32_t)(x))<<S32_SCB_STIR_STIR_SHIFT))&S32_SCB_STIR_STIR_MASK)
/* FPCCR Bit Fields */
#define S32_SCB_FPCCR_FPCCR_MASK                 0xFFFFFFFFu
#define S32_SCB_FPCCR_FPCCR_SHIFT                0u
#define S32_SCB_FPCCR_FPCCR_WIDTH                32u
#define S32_SCB_FPCCR_FPCCR(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_FPCCR_FPCCR_SHIFT))&S32_SCB_FPCCR_FPCCR_MASK)
/* FPCAR Bit Fields */
#define S32_SCB_FPCAR_FPCAR_MASK                 0xFFFFFFFFu
#define S32_SCB_FPCAR_FPCAR_SHIFT                0u
#define S32_SCB_FPCAR_FPCAR_WIDTH                32u
#define S32_SCB_FPCAR_FPCAR(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_FPCAR_FPCAR_SHIFT))&S32_SCB_FPCAR_FPCAR_MASK)
/* FPDSCR Bit Fields */
#define S32_SCB_FPDSCR_FPDSCR_MASK               0xFFFFFFFFu
#define S32_SCB_FPDSCR_FPDSCR_SHIFT              0u
#define S32_SCB_FPDSCR_FPDSCR_WIDTH              32u
#define S32_SCB_FPDSCR_FPDSCR(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_FPDSCR_FPDSCR_SHIFT))&S32_SCB_FPDSCR_FPDSCR_MASK)
/* ICIALLU Bit Fields */
#define S32_SCB_ICIALLU_ICIALLU_MASK             0xFFFFFFFFu
#define S32_SCB_ICIALLU_ICIALLU_SHIFT            0u
#define S32_SCB_ICIALLU_ICIALLU_WIDTH            32u
#define S32_SCB_ICIALLU_ICIALLU(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_ICIALLU_ICIALLU_SHIFT))&S32_SCB_ICIALLU_ICIALLU_MASK)
/* ICIMVAU Bit Fields */
#define S32_SCB_ICIMVAU_ICIMVAU_MASK             0xFFFFFFFFu
#define S32_SCB_ICIMVAU_ICIMVAU_SHIFT            0u
#define S32_SCB_ICIMVAU_ICIMVAU_WIDTH            32u
#define S32_SCB_ICIMVAU_ICIMVAU(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_ICIMVAU_ICIMVAU_SHIFT))&S32_SCB_ICIMVAU_ICIMVAU_MASK)
/* DCIMVAC Bit Fields */
#define S32_SCB_DCIMVAC_DCIMVAC_MASK             0xFFFFFFFFu
#define S32_SCB_DCIMVAC_DCIMVAC_SHIFT            0u
#define S32_SCB_DCIMVAC_DCIMVAC_WIDTH            32u
#define S32_SCB_DCIMVAC_DCIMVAC(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_DCIMVAC_DCIMVAC_SHIFT))&S32_SCB_DCIMVAC_DCIMVAC_MASK)
/* DCISW Bit Fields */
#define S32_SCB_DCISW_DCISW_MASK                 0xFFFFFFFFu
#define S32_SCB_DCISW_DCISW_SHIFT                0u
#define S32_SCB_DCISW_DCISW_WIDTH                32u
#define S32_SCB_DCISW_DCISW(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_DCISW_DCISW_SHIFT))&S32_SCB_DCISW_DCISW_MASK)
/* DCCMVAU Bit Fields */
#define S32_SCB_DCCMVAU_DCCMVAU_MASK             0xFFFFFFFFu
#define S32_SCB_DCCMVAU_DCCMVAU_SHIFT            0u
#define S32_SCB_DCCMVAU_DCCMVAU_WIDTH            32u
#define S32_SCB_DCCMVAU_DCCMVAU(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_DCCMVAU_DCCMVAU_SHIFT))&S32_SCB_DCCMVAU_DCCMVAU_MASK)
/* DCCMVAC Bit Fields */
#define S32_SCB_DCCMVAC_DCCMVAC_MASK             0xFFFFFFFFu
#define S32_SCB_DCCMVAC_DCCMVAC_SHIFT            0u
#define S32_SCB_DCCMVAC_DCCMVAC_WIDTH            32u
#define S32_SCB_DCCMVAC_DCCMVAC(x)               (((uint32_t)(((uint32_t)(x))<<S32_SCB_DCCMVAC_DCCMVAC_SHIFT))&S32_SCB_DCCMVAC_DCCMVAC_MASK)
/* DCCSW Bit Fields */
#define S32_SCB_DCCSW_DCCSW_MASK                 0xFFFFFFFFu
#define S32_SCB_DCCSW_DCCSW_SHIFT                0u
#define S32_SCB_DCCSW_DCCSW_WIDTH                32u
#define S32_SCB_DCCSW_DCCSW(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_DCCSW_DCCSW_SHIFT))&S32_SCB_DCCSW_DCCSW_MASK)
/* DCCIMVAC Bit Fields */
#define S32_SCB_DCCIMVAC_DCCIMVAC_MASK           0xFFFFFFFFu
#define S32_SCB_DCCIMVAC_DCCIMVAC_SHIFT          0u
#define S32_SCB_DCCIMVAC_DCCIMVAC_WIDTH          32u
#define S32_SCB_DCCIMVAC_DCCIMVAC(x)             (((uint32_t)(((uint32_t)(x))<<S32_SCB_DCCIMVAC_DCCIMVAC_SHIFT))&S32_SCB_DCCIMVAC_DCCIMVAC_MASK)
/* DCCISW Bit Fields */
#define S32_SCB_DCCISW_DCCISW_MASK               0xFFFFFFFFu
#define S32_SCB_DCCISW_DCCISW_SHIFT              0u
#define S32_SCB_DCCISW_DCCISW_WIDTH              32u
#define S32_SCB_DCCISW_DCCISW(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_DCCISW_DCCISW_SHIFT))&S32_SCB_DCCISW_DCCISW_MASK)
/* BPIALL Bit Fields */
#define S32_SCB_BPIALL_BPIALL_MASK               0xFFFFFFFFu
#define S32_SCB_BPIALL_BPIALL_SHIFT              0u
#define S32_SCB_BPIALL_BPIALL_WIDTH              32u
#define S32_SCB_BPIALL_BPIALL(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_BPIALL_BPIALL_SHIFT))&S32_SCB_BPIALL_BPIALL_MASK)
/* ITCMCR Bit Fields */
#define S32_SCB_ITCMCR_ITCMCR_MASK               0xFFFFFFFFu
#define S32_SCB_ITCMCR_ITCMCR_SHIFT              0u
#define S32_SCB_ITCMCR_ITCMCR_WIDTH              32u
#define S32_SCB_ITCMCR_ITCMCR(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_ITCMCR_ITCMCR_SHIFT))&S32_SCB_ITCMCR_ITCMCR_MASK)
/* DTCMCR Bit Fields */
#define S32_SCB_DTCMCR_DTCMCR_MASK               0xFFFFFFFFu
#define S32_SCB_DTCMCR_DTCMCR_SHIFT              0u
#define S32_SCB_DTCMCR_DTCMCR_WIDTH              32u
#define S32_SCB_DTCMCR_DTCMCR(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_DTCMCR_DTCMCR_SHIFT))&S32_SCB_DTCMCR_DTCMCR_MASK)
/* AHBPCR Bit Fields */
#define S32_SCB_AHBPCR_AHBPCR_MASK               0xFFFFFFFFu
#define S32_SCB_AHBPCR_AHBPCR_SHIFT              0u
#define S32_SCB_AHBPCR_AHBPCR_WIDTH              32u
#define S32_SCB_AHBPCR_AHBPCR(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_AHBPCR_AHBPCR_SHIFT))&S32_SCB_AHBPCR_AHBPCR_MASK)
/* CACR Bit Fields */
#define S32_SCB_CACR_CACR_MASK                   0xFFFFFFFFu
#define S32_SCB_CACR_CACR_SHIFT                  0u
#define S32_SCB_CACR_CACR_WIDTH                  32u
#define S32_SCB_CACR_CACR(x)                     (((uint32_t)(((uint32_t)(x))<<S32_SCB_CACR_CACR_SHIFT))&S32_SCB_CACR_CACR_MASK)
/* AHBSCR Bit Fields */
#define S32_SCB_AHBSCR_AHBSCR_MASK               0xFFFFFFFFu
#define S32_SCB_AHBSCR_AHBSCR_SHIFT              0u
#define S32_SCB_AHBSCR_AHBSCR_WIDTH              32u
#define S32_SCB_AHBSCR_AHBSCR(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_AHBSCR_AHBSCR_SHIFT))&S32_SCB_AHBSCR_AHBSCR_MASK)
/* ABFSR Bit Fields */
#define S32_SCB_ABFSR_ABFSR_MASK                 0xFFFFFFFFu
#define S32_SCB_ABFSR_ABFSR_SHIFT                0u
#define S32_SCB_ABFSR_ABFSR_WIDTH                32u
#define S32_SCB_ABFSR_ABFSR(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_ABFSR_ABFSR_SHIFT))&S32_SCB_ABFSR_ABFSR_MASK)
/* IEBR0 Bit Fields */
#define S32_SCB_IEBR0_IEBR0_MASK                 0xFFFFFFFFu
#define S32_SCB_IEBR0_IEBR0_SHIFT                0u
#define S32_SCB_IEBR0_IEBR0_WIDTH                32u
#define S32_SCB_IEBR0_IEBR0(x)                   (((uint32_t)(((uint32_t)(x))<<S32_SCB_IEBR0_IEBR0_SHIFT))&S32_SCB_IEBR0_IEBR0_MASK)
/* IEBR1h Bit Fields */
#define S32_SCB_IEBR1h_IEBR1h_MASK               0xFFFFFFFFu
#define S32_SCB_IEBR1h_IEBR1h_SHIFT              0u
#define S32_SCB_IEBR1h_IEBR1h_WIDTH              32u
#define S32_SCB_IEBR1h_IEBR1h(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_IEBR1h_IEBR1h_SHIFT))&S32_SCB_IEBR1h_IEBR1h_MASK)
/* DEBR0h Bit Fields */
#define S32_SCB_DEBR0h_DEBR0h_MASK               0xFFFFFFFFu
#define S32_SCB_DEBR0h_DEBR0h_SHIFT              0u
#define S32_SCB_DEBR0h_DEBR0h_WIDTH              32u
#define S32_SCB_DEBR0h_DEBR0h(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_DEBR0h_DEBR0h_SHIFT))&S32_SCB_DEBR0h_DEBR0h_MASK)
/* DEBR1h Bit Fields */
#define S32_SCB_DEBR1h_DEBR1h_MASK               0xFFFFFFFFu
#define S32_SCB_DEBR1h_DEBR1h_SHIFT              0u
#define S32_SCB_DEBR1h_DEBR1h_WIDTH              32u
#define S32_SCB_DEBR1h_DEBR1h(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_DEBR1h_DEBR1h_SHIFT))&S32_SCB_DEBR1h_DEBR1h_MASK)
/* PID Bit Fields */
#define S32_SCB_PID_PID0_MASK                    0xFFFFFFFFu
#define S32_SCB_PID_PID0_SHIFT                   0u
#define S32_SCB_PID_PID0_WIDTH                   32u
#define S32_SCB_PID_PID0(x)                      (((uint32_t)(((uint32_t)(x))<<S32_SCB_PID_PID0_SHIFT))&S32_SCB_PID_PID0_MASK)
#define S32_SCB_PID_PID1_MASK                    0xFFFFFFFFu
#define S32_SCB_PID_PID1_SHIFT                   0u
#define S32_SCB_PID_PID1_WIDTH                   32u
#define S32_SCB_PID_PID1(x)                      (((uint32_t)(((uint32_t)(x))<<S32_SCB_PID_PID1_SHIFT))&S32_SCB_PID_PID1_MASK)
#define S32_SCB_PID_PID2_MASK                    0xFFFFFFFFu
#define S32_SCB_PID_PID2_SHIFT                   0u
#define S32_SCB_PID_PID2_WIDTH                   32u
#define S32_SCB_PID_PID2(x)                      (((uint32_t)(((uint32_t)(x))<<S32_SCB_PID_PID2_SHIFT))&S32_SCB_PID_PID2_MASK)
#define S32_SCB_PID_PID3_MASK                    0xFFFFFFFFu
#define S32_SCB_PID_PID3_SHIFT                   0u
#define S32_SCB_PID_PID3_WIDTH                   32u
#define S32_SCB_PID_PID3(x)                      (((uint32_t)(((uint32_t)(x))<<S32_SCB_PID_PID3_SHIFT))&S32_SCB_PID_PID3_MASK)
#define S32_SCB_PID_PID4_MASK                    0xFFFFFFFFu
#define S32_SCB_PID_PID4_SHIFT                   0u
#define S32_SCB_PID_PID4_WIDTH                   32u
#define S32_SCB_PID_PID4(x)                      (((uint32_t)(((uint32_t)(x))<<S32_SCB_PID_PID4_SHIFT))&S32_SCB_PID_PID4_MASK)
#define S32_SCB_PID_PID5_MASK                    0xFFFFFFFFu
#define S32_SCB_PID_PID5_SHIFT                   0u
#define S32_SCB_PID_PID5_WIDTH                   32u
#define S32_SCB_PID_PID5(x)                      (((uint32_t)(((uint32_t)(x))<<S32_SCB_PID_PID5_SHIFT))&S32_SCB_PID_PID5_MASK)
#define S32_SCB_PID_PID6_MASK                    0xFFFFFFFFu
#define S32_SCB_PID_PID6_SHIFT                   0u
#define S32_SCB_PID_PID6_WIDTH                   32u
#define S32_SCB_PID_PID6(x)                      (((uint32_t)(((uint32_t)(x))<<S32_SCB_PID_PID6_SHIFT))&S32_SCB_PID_PID6_MASK)
#define S32_SCB_PID_PID7_MASK                    0xFFFFFFFFu
#define S32_SCB_PID_PID7_SHIFT                   0u
#define S32_SCB_PID_PID7_WIDTH                   32u
#define S32_SCB_PID_PID7(x)                      (((uint32_t)(((uint32_t)(x))<<S32_SCB_PID_PID7_SHIFT))&S32_SCB_PID_PID7_MASK)
/* CID Bit Fields */
#define S32_SCB_CID_CID0_MASK                    0xFFFFFFFFu
#define S32_SCB_CID_CID0_SHIFT                   0u
#define S32_SCB_CID_CID0_WIDTH                   32u
#define S32_SCB_CID_CID0(x)                      (((uint32_t)(((uint32_t)(x))<<S32_SCB_CID_CID0_SHIFT))&S32_SCB_CID_CID0_MASK)
#define S32_SCB_CID_CID1_MASK                    0xFFFFFFFFu
#define S32_SCB_CID_CID1_SHIFT                   0u
#define S32_SCB_CID_CID1_WIDTH                   32u
#define S32_SCB_CID_CID1(x)                      (((uint32_t)(((uint32_t)(x))<<S32_SCB_CID_CID1_SHIFT))&S32_SCB_CID_CID1_MASK)
#define S32_SCB_CID_CID2_MASK                    0xFFFFFFFFu
#define S32_SCB_CID_CID2_SHIFT                   0u
#define S32_SCB_CID_CID2_WIDTH                   32u
#define S32_SCB_CID_CID2(x)                      (((uint32_t)(((uint32_t)(x))<<S32_SCB_CID_CID2_SHIFT))&S32_SCB_CID_CID2_MASK)
#define S32_SCB_CID_CID3_MASK                    0xFFFFFFFFu
#define S32_SCB_CID_CID3_SHIFT                   0u
#define S32_SCB_CID_CID3_WIDTH                   32u
#define S32_SCB_CID_CID3(x)                      (((uint32_t)(((uint32_t)(x))<<S32_SCB_CID_CID3_SHIFT))&S32_SCB_CID_CID3_MASK)

/*!
 * @}
 */ /* end of group S32_SCB_Register_Masks */

/*!
 * @}
 */ /* end of group S32_SCB_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_SCB_H_) */
