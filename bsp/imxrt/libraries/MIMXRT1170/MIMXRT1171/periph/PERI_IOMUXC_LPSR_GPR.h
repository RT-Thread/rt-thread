/*
** ###################################################################
**     Processors:          MIMXRT1171AVM8A
**                          MIMXRT1171AVM8B
**                          MIMXRT1171CVM8A
**                          MIMXRT1171CVM8B
**                          MIMXRT1171DVMAA
**                          MIMXRT1171DVMAB
**                          MIMXRT1172AVM8A
**                          MIMXRT1172AVM8B
**                          MIMXRT1172CVM8A
**                          MIMXRT1172CVM8B
**                          MIMXRT1172DVMAA
**                          MIMXRT1172DVMAB
**                          MIMXRT1173CVM8A_cm4
**                          MIMXRT1173CVM8A_cm7
**                          MIMXRT1173CVM8B_cm4
**                          MIMXRT1173CVM8B_cm7
**                          MIMXRT1175AVM8A_cm4
**                          MIMXRT1175AVM8A_cm7
**                          MIMXRT1175AVM8B_cm4
**                          MIMXRT1175AVM8B_cm7
**                          MIMXRT1175CVM8A_cm4
**                          MIMXRT1175CVM8A_cm7
**                          MIMXRT1175CVM8B_cm4
**                          MIMXRT1175CVM8B_cm7
**                          MIMXRT1175DVMAA_cm4
**                          MIMXRT1175DVMAA_cm7
**                          MIMXRT1175DVMAB_cm4
**                          MIMXRT1175DVMAB_cm7
**                          MIMXRT1176AVM8A_cm4
**                          MIMXRT1176AVM8A_cm7
**                          MIMXRT1176AVM8B_cm4
**                          MIMXRT1176AVM8B_cm7
**                          MIMXRT1176CVM8A_cm4
**                          MIMXRT1176CVM8A_cm7
**                          MIMXRT1176CVM8B_cm4
**                          MIMXRT1176CVM8B_cm7
**                          MIMXRT1176DVMAA_cm4
**                          MIMXRT1176DVMAA_cm7
**                          MIMXRT1176DVMAB_cm4
**                          MIMXRT1176DVMAB_cm7
**                          MIMXRT117HAVM8A_cm4
**                          MIMXRT117HAVM8A_cm7
**                          MIMXRT117HAVM8B_cm4
**                          MIMXRT117HAVM8B_cm7
**                          MIMXRT117HCVM8A_cm4
**                          MIMXRT117HCVM8A_cm7
**                          MIMXRT117HCVM8B_cm4
**                          MIMXRT117HCVM8B_cm7
**                          MIMXRT117HDVMAA_cm4
**                          MIMXRT117HDVMAA_cm7
**                          MIMXRT117HDVMAB_cm4
**                          MIMXRT117HDVMAB_cm7
**
**     Version:             rev. 2.0, 2024-10-29
**     Build:               b250520
**
**     Abstract:
**         CMSIS Peripheral Access Layer for IOMUXC_LPSR_GPR
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2025 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 0.1 (2018-03-05)
**         Initial version.
**     - rev. 1.0 (2020-12-29)
**         Update header files to align with IMXRT1170RM Rev.0.
**     - rev. 2.0 (2024-10-29)
**         Change the device header file from single flat file to multiple files based on peripherals,
**         each peripheral with dedicated header file located in periphN folder.
**
** ###################################################################
*/

/*!
 * @file PERI_IOMUXC_LPSR_GPR.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for IOMUXC_LPSR_GPR
 *
 * CMSIS Peripheral Access Layer for IOMUXC_LPSR_GPR
 */

#if !defined(PERI_IOMUXC_LPSR_GPR_H_)
#define PERI_IOMUXC_LPSR_GPR_H_                  /**< Symbol preventing repeated inclusion */

#if (defined(CPU_MIMXRT1171AVM8A) || defined(CPU_MIMXRT1171AVM8B) || defined(CPU_MIMXRT1171CVM8A) || defined(CPU_MIMXRT1171CVM8B) || defined(CPU_MIMXRT1171DVMAA) || defined(CPU_MIMXRT1171DVMAB))
#include "MIMXRT1171_COMMON.h"
#elif (defined(CPU_MIMXRT1172AVM8A) || defined(CPU_MIMXRT1172AVM8B) || defined(CPU_MIMXRT1172CVM8A) || defined(CPU_MIMXRT1172CVM8B) || defined(CPU_MIMXRT1172DVMAA) || defined(CPU_MIMXRT1172DVMAB))
#include "MIMXRT1172_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm4) || defined(CPU_MIMXRT1173CVM8B_cm4))
#include "MIMXRT1173_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm7) || defined(CPU_MIMXRT1173CVM8B_cm7))
#include "MIMXRT1173_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm4) || defined(CPU_MIMXRT1175AVM8B_cm4) || defined(CPU_MIMXRT1175CVM8A_cm4) || defined(CPU_MIMXRT1175CVM8B_cm4) || defined(CPU_MIMXRT1175DVMAA_cm4) || defined(CPU_MIMXRT1175DVMAB_cm4))
#include "MIMXRT1175_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm7) || defined(CPU_MIMXRT1175AVM8B_cm7) || defined(CPU_MIMXRT1175CVM8A_cm7) || defined(CPU_MIMXRT1175CVM8B_cm7) || defined(CPU_MIMXRT1175DVMAA_cm7) || defined(CPU_MIMXRT1175DVMAB_cm7))
#include "MIMXRT1175_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm4) || defined(CPU_MIMXRT1176AVM8B_cm4) || defined(CPU_MIMXRT1176CVM8A_cm4) || defined(CPU_MIMXRT1176CVM8B_cm4) || defined(CPU_MIMXRT1176DVMAA_cm4) || defined(CPU_MIMXRT1176DVMAB_cm4))
#include "MIMXRT1176_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm7) || defined(CPU_MIMXRT1176AVM8B_cm7) || defined(CPU_MIMXRT1176CVM8A_cm7) || defined(CPU_MIMXRT1176CVM8B_cm7) || defined(CPU_MIMXRT1176DVMAA_cm7) || defined(CPU_MIMXRT1176DVMAB_cm7))
#include "MIMXRT1176_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm4) || defined(CPU_MIMXRT117HAVM8B_cm4) || defined(CPU_MIMXRT117HCVM8A_cm4) || defined(CPU_MIMXRT117HCVM8B_cm4) || defined(CPU_MIMXRT117HDVMAA_cm4) || defined(CPU_MIMXRT117HDVMAB_cm4))
#include "MIMXRT117H_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm7) || defined(CPU_MIMXRT117HAVM8B_cm7) || defined(CPU_MIMXRT117HCVM8A_cm7) || defined(CPU_MIMXRT117HCVM8B_cm7) || defined(CPU_MIMXRT117HDVMAA_cm7) || defined(CPU_MIMXRT117HDVMAB_cm7))
#include "MIMXRT117H_cm7_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- IOMUXC_LPSR_GPR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_LPSR_GPR_Peripheral_Access_Layer IOMUXC_LPSR_GPR Peripheral Access Layer
 * @{
 */

/** IOMUXC_LPSR_GPR - Register Layout Typedef */
typedef struct {
  __IO uint32_t GPR0;                              /**< GPR0 General Purpose Register, offset: 0x0 */
  __IO uint32_t GPR1;                              /**< GPR1 General Purpose Register, offset: 0x4 */
  __IO uint32_t GPR2;                              /**< GPR2 General Purpose Register, offset: 0x8 */
  __IO uint32_t GPR3;                              /**< GPR3 General Purpose Register, offset: 0xC */
  __IO uint32_t GPR4;                              /**< GPR4 General Purpose Register, offset: 0x10 */
  __IO uint32_t GPR5;                              /**< GPR5 General Purpose Register, offset: 0x14 */
  __IO uint32_t GPR6;                              /**< GPR6 General Purpose Register, offset: 0x18 */
  __IO uint32_t GPR7;                              /**< GPR7 General Purpose Register, offset: 0x1C */
  __IO uint32_t GPR8;                              /**< GPR8 General Purpose Register, offset: 0x20 */
  __IO uint32_t GPR9;                              /**< GPR9 General Purpose Register, offset: 0x24 */
  __IO uint32_t GPR10;                             /**< GPR10 General Purpose Register, offset: 0x28 */
  __IO uint32_t GPR11;                             /**< GPR11 General Purpose Register, offset: 0x2C */
  __IO uint32_t GPR12;                             /**< GPR12 General Purpose Register, offset: 0x30 */
  __IO uint32_t GPR13;                             /**< GPR13 General Purpose Register, offset: 0x34 */
  __IO uint32_t GPR14;                             /**< GPR14 General Purpose Register, offset: 0x38 */
  __IO uint32_t GPR15;                             /**< GPR15 General Purpose Register, offset: 0x3C */
  __IO uint32_t GPR16;                             /**< GPR16 General Purpose Register, offset: 0x40 */
  __IO uint32_t GPR17;                             /**< GPR17 General Purpose Register, offset: 0x44 */
  __IO uint32_t GPR18;                             /**< GPR18 General Purpose Register, offset: 0x48 */
  __IO uint32_t GPR19;                             /**< GPR19 General Purpose Register, offset: 0x4C */
  __IO uint32_t GPR20;                             /**< GPR20 General Purpose Register, offset: 0x50 */
  __IO uint32_t GPR21;                             /**< GPR21 General Purpose Register, offset: 0x54 */
  __IO uint32_t GPR22;                             /**< GPR22 General Purpose Register, offset: 0x58 */
  __IO uint32_t GPR23;                             /**< GPR23 General Purpose Register, offset: 0x5C */
  __IO uint32_t GPR24;                             /**< GPR24 General Purpose Register, offset: 0x60 */
  __IO uint32_t GPR25;                             /**< GPR25 General Purpose Register, offset: 0x64 */
  __IO uint32_t GPR26;                             /**< GPR26 General Purpose Register, offset: 0x68 */
       uint8_t RESERVED_0[24];
  __IO uint32_t GPR33;                             /**< GPR33 General Purpose Register, offset: 0x84 */
  __IO uint32_t GPR34;                             /**< GPR34 General Purpose Register, offset: 0x88 */
  __IO uint32_t GPR35;                             /**< GPR35 General Purpose Register, offset: 0x8C */
  __IO uint32_t GPR36;                             /**< GPR36 General Purpose Register, offset: 0x90 */
  __IO uint32_t GPR37;                             /**< GPR37 General Purpose Register, offset: 0x94 */
  __IO uint32_t GPR38;                             /**< GPR38 General Purpose Register, offset: 0x98 */
  __IO uint32_t GPR39;                             /**< GPR39 General Purpose Register, offset: 0x9C */
  __I  uint32_t GPR40;                             /**< GPR40 General Purpose Register, offset: 0xA0 */
  __I  uint32_t GPR41;                             /**< GPR41 General Purpose Register, offset: 0xA4 */
} IOMUXC_LPSR_GPR_Type;

/* ----------------------------------------------------------------------------
   -- IOMUXC_LPSR_GPR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_LPSR_GPR_Register_Masks IOMUXC_LPSR_GPR Register Masks
 * @{
 */

/*! @name GPR0 - GPR0 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR0_CM4_INIT_VTOR_LOW_MASK (0xFFF8U)
#define IOMUXC_LPSR_GPR_GPR0_CM4_INIT_VTOR_LOW_SHIFT (3U)
/*! CM4_INIT_VTOR_LOW - CM4 Vector table offset value lower bits out of reset */
#define IOMUXC_LPSR_GPR_GPR0_CM4_INIT_VTOR_LOW(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR0_CM4_INIT_VTOR_LOW_SHIFT)) & IOMUXC_LPSR_GPR_GPR0_CM4_INIT_VTOR_LOW_MASK)

#define IOMUXC_LPSR_GPR_GPR0_DWP_MASK            (0x30000000U)
#define IOMUXC_LPSR_GPR_GPR0_DWP_SHIFT           (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_LPSR_GPR_GPR0_DWP(x)              (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR0_DWP_SHIFT)) & IOMUXC_LPSR_GPR_GPR0_DWP_MASK)

#define IOMUXC_LPSR_GPR_GPR0_DWP_LOCK_MASK       (0xC0000000U)
#define IOMUXC_LPSR_GPR_GPR0_DWP_LOCK_SHIFT      (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_LPSR_GPR_GPR0_DWP_LOCK(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR0_DWP_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR0_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR1 - GPR1 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR1_CM4_INIT_VTOR_HIGH_MASK (0xFFFFU)
#define IOMUXC_LPSR_GPR_GPR1_CM4_INIT_VTOR_HIGH_SHIFT (0U)
/*! CM4_INIT_VTOR_HIGH - CM4 Vector table offset value higher bits out of reset */
#define IOMUXC_LPSR_GPR_GPR1_CM4_INIT_VTOR_HIGH(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR1_CM4_INIT_VTOR_HIGH_SHIFT)) & IOMUXC_LPSR_GPR_GPR1_CM4_INIT_VTOR_HIGH_MASK)

#define IOMUXC_LPSR_GPR_GPR1_DWP_MASK            (0x30000000U)
#define IOMUXC_LPSR_GPR_GPR1_DWP_SHIFT           (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_LPSR_GPR_GPR1_DWP(x)              (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR1_DWP_SHIFT)) & IOMUXC_LPSR_GPR_GPR1_DWP_MASK)

#define IOMUXC_LPSR_GPR_GPR1_DWP_LOCK_MASK       (0xC0000000U)
#define IOMUXC_LPSR_GPR_GPR1_DWP_LOCK_SHIFT      (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_LPSR_GPR_GPR1_DWP_LOCK(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR1_DWP_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR1_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR2 - GPR2 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR2_LOCK_MASK           (0x1U)
#define IOMUXC_LPSR_GPR_GPR2_LOCK_SHIFT          (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR2_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR2_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR2_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR2_APC_AC_R0_BOT_MASK  (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR2_APC_AC_R0_BOT_SHIFT (3U)
/*! APC_AC_R0_BOT - APC start address of memory region-0 */
#define IOMUXC_LPSR_GPR_GPR2_APC_AC_R0_BOT(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR2_APC_AC_R0_BOT_SHIFT)) & IOMUXC_LPSR_GPR_GPR2_APC_AC_R0_BOT_MASK)
/*! @} */

/*! @name GPR3 - GPR3 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR3_LOCK_MASK           (0x1U)
#define IOMUXC_LPSR_GPR_GPR3_LOCK_SHIFT          (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR3_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR3_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR3_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR3_APC_AC_R0_TOP_MASK  (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR3_APC_AC_R0_TOP_SHIFT (3U)
/*! APC_AC_R0_TOP - APC end address of memory region-0 */
#define IOMUXC_LPSR_GPR_GPR3_APC_AC_R0_TOP(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR3_APC_AC_R0_TOP_SHIFT)) & IOMUXC_LPSR_GPR_GPR3_APC_AC_R0_TOP_MASK)
/*! @} */

/*! @name GPR4 - GPR4 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR4_LOCK_MASK           (0x1U)
#define IOMUXC_LPSR_GPR_GPR4_LOCK_SHIFT          (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR4_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR4_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR4_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR4_APC_AC_R1_BOT_MASK  (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR4_APC_AC_R1_BOT_SHIFT (3U)
/*! APC_AC_R1_BOT - APC start address of memory region-1 */
#define IOMUXC_LPSR_GPR_GPR4_APC_AC_R1_BOT(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR4_APC_AC_R1_BOT_SHIFT)) & IOMUXC_LPSR_GPR_GPR4_APC_AC_R1_BOT_MASK)
/*! @} */

/*! @name GPR5 - GPR5 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR5_LOCK_MASK           (0x1U)
#define IOMUXC_LPSR_GPR_GPR5_LOCK_SHIFT          (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR5_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR5_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR5_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR5_APC_AC_R1_TOP_MASK  (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR5_APC_AC_R1_TOP_SHIFT (3U)
/*! APC_AC_R1_TOP - APC end address of memory region-1 */
#define IOMUXC_LPSR_GPR_GPR5_APC_AC_R1_TOP(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR5_APC_AC_R1_TOP_SHIFT)) & IOMUXC_LPSR_GPR_GPR5_APC_AC_R1_TOP_MASK)
/*! @} */

/*! @name GPR6 - GPR6 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR6_LOCK_MASK           (0x1U)
#define IOMUXC_LPSR_GPR_GPR6_LOCK_SHIFT          (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR6_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR6_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR6_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR6_APC_AC_R2_BOT_MASK  (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR6_APC_AC_R2_BOT_SHIFT (3U)
/*! APC_AC_R2_BOT - APC start address of memory region-2 */
#define IOMUXC_LPSR_GPR_GPR6_APC_AC_R2_BOT(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR6_APC_AC_R2_BOT_SHIFT)) & IOMUXC_LPSR_GPR_GPR6_APC_AC_R2_BOT_MASK)
/*! @} */

/*! @name GPR7 - GPR7 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR7_LOCK_MASK           (0x1U)
#define IOMUXC_LPSR_GPR_GPR7_LOCK_SHIFT          (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR7_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR7_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR7_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR7_APC_AC_R2_TOP_MASK  (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR7_APC_AC_R2_TOP_SHIFT (3U)
/*! APC_AC_R2_TOP - APC end address of memory region-2 */
#define IOMUXC_LPSR_GPR_GPR7_APC_AC_R2_TOP(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR7_APC_AC_R2_TOP_SHIFT)) & IOMUXC_LPSR_GPR_GPR7_APC_AC_R2_TOP_MASK)
/*! @} */

/*! @name GPR8 - GPR8 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR8_LOCK_MASK           (0x1U)
#define IOMUXC_LPSR_GPR_GPR8_LOCK_SHIFT          (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR8_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR8_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR8_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR8_APC_AC_R3_BOT_MASK  (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR8_APC_AC_R3_BOT_SHIFT (3U)
/*! APC_AC_R3_BOT - APC start address of memory region-3 */
#define IOMUXC_LPSR_GPR_GPR8_APC_AC_R3_BOT(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR8_APC_AC_R3_BOT_SHIFT)) & IOMUXC_LPSR_GPR_GPR8_APC_AC_R3_BOT_MASK)
/*! @} */

/*! @name GPR9 - GPR9 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR9_LOCK_MASK           (0x1U)
#define IOMUXC_LPSR_GPR_GPR9_LOCK_SHIFT          (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR9_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR9_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR9_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR9_APC_AC_R3_TOP_MASK  (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR9_APC_AC_R3_TOP_SHIFT (3U)
/*! APC_AC_R3_TOP - APC end address of memory region-3 */
#define IOMUXC_LPSR_GPR_GPR9_APC_AC_R3_TOP(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR9_APC_AC_R3_TOP_SHIFT)) & IOMUXC_LPSR_GPR_GPR9_APC_AC_R3_TOP_MASK)
/*! @} */

/*! @name GPR10 - GPR10 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR10_LOCK_MASK          (0x1U)
#define IOMUXC_LPSR_GPR_GPR10_LOCK_SHIFT         (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR10_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR10_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR10_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR10_APC_AC_R4_BOT_MASK (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR10_APC_AC_R4_BOT_SHIFT (3U)
/*! APC_AC_R4_BOT - APC start address of memory region-4 */
#define IOMUXC_LPSR_GPR_GPR10_APC_AC_R4_BOT(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR10_APC_AC_R4_BOT_SHIFT)) & IOMUXC_LPSR_GPR_GPR10_APC_AC_R4_BOT_MASK)
/*! @} */

/*! @name GPR11 - GPR11 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR11_LOCK_MASK          (0x1U)
#define IOMUXC_LPSR_GPR_GPR11_LOCK_SHIFT         (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR11_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR11_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR11_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR11_APC_AC_R4_TOP_MASK (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR11_APC_AC_R4_TOP_SHIFT (3U)
/*! APC_AC_R4_TOP - APC end address of memory region-4 */
#define IOMUXC_LPSR_GPR_GPR11_APC_AC_R4_TOP(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR11_APC_AC_R4_TOP_SHIFT)) & IOMUXC_LPSR_GPR_GPR11_APC_AC_R4_TOP_MASK)
/*! @} */

/*! @name GPR12 - GPR12 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR12_LOCK_MASK          (0x1U)
#define IOMUXC_LPSR_GPR_GPR12_LOCK_SHIFT         (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR12_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR12_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR12_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR12_APC_AC_R5_BOT_MASK (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR12_APC_AC_R5_BOT_SHIFT (3U)
/*! APC_AC_R5_BOT - APC start address of memory region-5 */
#define IOMUXC_LPSR_GPR_GPR12_APC_AC_R5_BOT(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR12_APC_AC_R5_BOT_SHIFT)) & IOMUXC_LPSR_GPR_GPR12_APC_AC_R5_BOT_MASK)
/*! @} */

/*! @name GPR13 - GPR13 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR13_LOCK_MASK          (0x1U)
#define IOMUXC_LPSR_GPR_GPR13_LOCK_SHIFT         (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR13_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR13_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR13_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR13_APC_AC_R5_TOP_MASK (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR13_APC_AC_R5_TOP_SHIFT (3U)
/*! APC_AC_R5_TOP - APC end address of memory region-5 */
#define IOMUXC_LPSR_GPR_GPR13_APC_AC_R5_TOP(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR13_APC_AC_R5_TOP_SHIFT)) & IOMUXC_LPSR_GPR_GPR13_APC_AC_R5_TOP_MASK)
/*! @} */

/*! @name GPR14 - GPR14 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR14_LOCK_MASK          (0x1U)
#define IOMUXC_LPSR_GPR_GPR14_LOCK_SHIFT         (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR14_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR14_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR14_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR14_APC_AC_R6_BOT_MASK (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR14_APC_AC_R6_BOT_SHIFT (3U)
/*! APC_AC_R6_BOT - APC start address of memory region-6 */
#define IOMUXC_LPSR_GPR_GPR14_APC_AC_R6_BOT(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR14_APC_AC_R6_BOT_SHIFT)) & IOMUXC_LPSR_GPR_GPR14_APC_AC_R6_BOT_MASK)
/*! @} */

/*! @name GPR15 - GPR15 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR15_LOCK_MASK          (0x1U)
#define IOMUXC_LPSR_GPR_GPR15_LOCK_SHIFT         (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR15_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR15_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR15_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR15_APC_AC_R6_TOP_MASK (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR15_APC_AC_R6_TOP_SHIFT (3U)
/*! APC_AC_R6_TOP - APC end address of memory region-6 */
#define IOMUXC_LPSR_GPR_GPR15_APC_AC_R6_TOP(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR15_APC_AC_R6_TOP_SHIFT)) & IOMUXC_LPSR_GPR_GPR15_APC_AC_R6_TOP_MASK)
/*! @} */

/*! @name GPR16 - GPR16 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR16_LOCK_MASK          (0x1U)
#define IOMUXC_LPSR_GPR_GPR16_LOCK_SHIFT         (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR16_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR16_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR16_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR16_APC_AC_R7_BOT_MASK (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR16_APC_AC_R7_BOT_SHIFT (3U)
/*! APC_AC_R7_BOT - APC start address of memory region-7 */
#define IOMUXC_LPSR_GPR_GPR16_APC_AC_R7_BOT(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR16_APC_AC_R7_BOT_SHIFT)) & IOMUXC_LPSR_GPR_GPR16_APC_AC_R7_BOT_MASK)
/*! @} */

/*! @name GPR17 - GPR17 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR17_LOCK_MASK          (0x1U)
#define IOMUXC_LPSR_GPR_GPR17_LOCK_SHIFT         (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access to bit 31:1 is not blocked
 *  0b1..Write access to bit 31:1 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR17_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR17_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR17_LOCK_MASK)

#define IOMUXC_LPSR_GPR_GPR17_APC_AC_R7_TOP_MASK (0xFFFFFFF8U)
#define IOMUXC_LPSR_GPR_GPR17_APC_AC_R7_TOP_SHIFT (3U)
/*! APC_AC_R7_TOP - APC end address of memory region-7 */
#define IOMUXC_LPSR_GPR_GPR17_APC_AC_R7_TOP(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR17_APC_AC_R7_TOP_SHIFT)) & IOMUXC_LPSR_GPR_GPR17_APC_AC_R7_TOP_MASK)
/*! @} */

/*! @name GPR18 - GPR18 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR18_APC_R0_ENCRYPT_ENABLE_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR18_APC_R0_ENCRYPT_ENABLE_SHIFT (4U)
/*! APC_R0_ENCRYPT_ENABLE - APC memory region-0 encryption enable
 *  0b0..No effect
 *  0b1..Encryption enabled
 */
#define IOMUXC_LPSR_GPR_GPR18_APC_R0_ENCRYPT_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR18_APC_R0_ENCRYPT_ENABLE_SHIFT)) & IOMUXC_LPSR_GPR_GPR18_APC_R0_ENCRYPT_ENABLE_MASK)

#define IOMUXC_LPSR_GPR_GPR18_LOCK_MASK          (0xFFFF0000U)
#define IOMUXC_LPSR_GPR_GPR18_LOCK_SHIFT         (16U)
/*! LOCK - Lock the write to bit 15:0 */
#define IOMUXC_LPSR_GPR_GPR18_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR18_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR18_LOCK_MASK)
/*! @} */

/*! @name GPR19 - GPR19 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR19_APC_R1_ENCRYPT_ENABLE_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR19_APC_R1_ENCRYPT_ENABLE_SHIFT (4U)
/*! APC_R1_ENCRYPT_ENABLE - APC memory region-1 encryption enable
 *  0b0..No effect
 *  0b1..Encryption enabled
 */
#define IOMUXC_LPSR_GPR_GPR19_APC_R1_ENCRYPT_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR19_APC_R1_ENCRYPT_ENABLE_SHIFT)) & IOMUXC_LPSR_GPR_GPR19_APC_R1_ENCRYPT_ENABLE_MASK)

#define IOMUXC_LPSR_GPR_GPR19_LOCK_MASK          (0xFFFF0000U)
#define IOMUXC_LPSR_GPR_GPR19_LOCK_SHIFT         (16U)
/*! LOCK - Lock the write to bit 15:0 */
#define IOMUXC_LPSR_GPR_GPR19_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR19_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR19_LOCK_MASK)
/*! @} */

/*! @name GPR20 - GPR20 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR20_APC_R2_ENCRYPT_ENABLE_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR20_APC_R2_ENCRYPT_ENABLE_SHIFT (4U)
/*! APC_R2_ENCRYPT_ENABLE - APC memory region-2 encryption enable
 *  0b0..No effect
 *  0b1..Encryption enabled
 */
#define IOMUXC_LPSR_GPR_GPR20_APC_R2_ENCRYPT_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR20_APC_R2_ENCRYPT_ENABLE_SHIFT)) & IOMUXC_LPSR_GPR_GPR20_APC_R2_ENCRYPT_ENABLE_MASK)

#define IOMUXC_LPSR_GPR_GPR20_LOCK_MASK          (0xFFFF0000U)
#define IOMUXC_LPSR_GPR_GPR20_LOCK_SHIFT         (16U)
/*! LOCK - Lock the write to bit 15:0 */
#define IOMUXC_LPSR_GPR_GPR20_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR20_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR20_LOCK_MASK)
/*! @} */

/*! @name GPR21 - GPR21 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR21_APC_R3_ENCRYPT_ENABLE_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR21_APC_R3_ENCRYPT_ENABLE_SHIFT (4U)
/*! APC_R3_ENCRYPT_ENABLE - APC memory region-3 encryption enable
 *  0b0..No effect
 *  0b1..Encryption enabled
 */
#define IOMUXC_LPSR_GPR_GPR21_APC_R3_ENCRYPT_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR21_APC_R3_ENCRYPT_ENABLE_SHIFT)) & IOMUXC_LPSR_GPR_GPR21_APC_R3_ENCRYPT_ENABLE_MASK)

#define IOMUXC_LPSR_GPR_GPR21_LOCK_MASK          (0xFFFF0000U)
#define IOMUXC_LPSR_GPR_GPR21_LOCK_SHIFT         (16U)
/*! LOCK - Lock the write to bit 15:0 */
#define IOMUXC_LPSR_GPR_GPR21_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR21_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR21_LOCK_MASK)
/*! @} */

/*! @name GPR22 - GPR22 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR22_APC_R4_ENCRYPT_ENABLE_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR22_APC_R4_ENCRYPT_ENABLE_SHIFT (4U)
/*! APC_R4_ENCRYPT_ENABLE - APC memory region-4 encryption enable
 *  0b0..No effect
 *  0b1..Encryption enabled
 */
#define IOMUXC_LPSR_GPR_GPR22_APC_R4_ENCRYPT_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR22_APC_R4_ENCRYPT_ENABLE_SHIFT)) & IOMUXC_LPSR_GPR_GPR22_APC_R4_ENCRYPT_ENABLE_MASK)

#define IOMUXC_LPSR_GPR_GPR22_LOCK_MASK          (0xFFFF0000U)
#define IOMUXC_LPSR_GPR_GPR22_LOCK_SHIFT         (16U)
/*! LOCK - Lock the write to bit 15:0 */
#define IOMUXC_LPSR_GPR_GPR22_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR22_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR22_LOCK_MASK)
/*! @} */

/*! @name GPR23 - GPR23 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR23_APC_R5_ENCRYPT_ENABLE_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR23_APC_R5_ENCRYPT_ENABLE_SHIFT (4U)
/*! APC_R5_ENCRYPT_ENABLE - APC memory region-5 encryption enable
 *  0b0..No effect
 *  0b1..Encryption enabled
 */
#define IOMUXC_LPSR_GPR_GPR23_APC_R5_ENCRYPT_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR23_APC_R5_ENCRYPT_ENABLE_SHIFT)) & IOMUXC_LPSR_GPR_GPR23_APC_R5_ENCRYPT_ENABLE_MASK)

#define IOMUXC_LPSR_GPR_GPR23_LOCK_MASK          (0xFFFF0000U)
#define IOMUXC_LPSR_GPR_GPR23_LOCK_SHIFT         (16U)
/*! LOCK - Lock the write to bit 15:0 */
#define IOMUXC_LPSR_GPR_GPR23_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR23_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR23_LOCK_MASK)
/*! @} */

/*! @name GPR24 - GPR24 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR24_APC_R6_ENCRYPT_ENABLE_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR24_APC_R6_ENCRYPT_ENABLE_SHIFT (4U)
/*! APC_R6_ENCRYPT_ENABLE - APC memory region-6 encryption enable
 *  0b0..No effect
 *  0b1..Encryption enabled
 */
#define IOMUXC_LPSR_GPR_GPR24_APC_R6_ENCRYPT_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR24_APC_R6_ENCRYPT_ENABLE_SHIFT)) & IOMUXC_LPSR_GPR_GPR24_APC_R6_ENCRYPT_ENABLE_MASK)

#define IOMUXC_LPSR_GPR_GPR24_LOCK_MASK          (0xFFFF0000U)
#define IOMUXC_LPSR_GPR_GPR24_LOCK_SHIFT         (16U)
/*! LOCK - Lock the write to bit 15:0 */
#define IOMUXC_LPSR_GPR_GPR24_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR24_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR24_LOCK_MASK)
/*! @} */

/*! @name GPR25 - GPR25 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR25_APC_R7_ENCRYPT_ENABLE_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR25_APC_R7_ENCRYPT_ENABLE_SHIFT (4U)
/*! APC_R7_ENCRYPT_ENABLE - APC memory region-7 encryption enable
 *  0b0..No effect
 *  0b1..Encryption enabled
 */
#define IOMUXC_LPSR_GPR_GPR25_APC_R7_ENCRYPT_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR25_APC_R7_ENCRYPT_ENABLE_SHIFT)) & IOMUXC_LPSR_GPR_GPR25_APC_R7_ENCRYPT_ENABLE_MASK)

#define IOMUXC_LPSR_GPR_GPR25_APC_VALID_MASK     (0x20U)
#define IOMUXC_LPSR_GPR_GPR25_APC_VALID_SHIFT    (5U)
/*! APC_VALID - APC global enable bit
 *  0b0..No effect
 *  0b1..Enable encryption for GPRx[APC_x_ENCRYPT_ENABLE] (valid for GPR2-GPR25)
 */
#define IOMUXC_LPSR_GPR_GPR25_APC_VALID(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR25_APC_VALID_SHIFT)) & IOMUXC_LPSR_GPR_GPR25_APC_VALID_MASK)

#define IOMUXC_LPSR_GPR_GPR25_LOCK_MASK          (0xFFFF0000U)
#define IOMUXC_LPSR_GPR_GPR25_LOCK_SHIFT         (16U)
/*! LOCK - Lock the write to bit 15:0 */
#define IOMUXC_LPSR_GPR_GPR25_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR25_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR25_LOCK_MASK)
/*! @} */

/*! @name GPR26 - GPR26 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR26_CM7_INIT_VTOR_MASK (0x1FFFFFFU)
#define IOMUXC_LPSR_GPR_GPR26_CM7_INIT_VTOR_SHIFT (0U)
/*! CM7_INIT_VTOR - Vector table offset register out of reset. See the ARM v7-M Architecture
 *    Reference Manual for more information about the vector table offset register (VTOR).
 */
#define IOMUXC_LPSR_GPR_GPR26_CM7_INIT_VTOR(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR26_CM7_INIT_VTOR_SHIFT)) & IOMUXC_LPSR_GPR_GPR26_CM7_INIT_VTOR_MASK)

#define IOMUXC_LPSR_GPR_GPR26_FIELD_0_MASK       (0xE000000U)
#define IOMUXC_LPSR_GPR_GPR26_FIELD_0_SHIFT      (25U)
/*! FIELD_0 - General purpose bits */
#define IOMUXC_LPSR_GPR_GPR26_FIELD_0(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR26_FIELD_0_SHIFT)) & IOMUXC_LPSR_GPR_GPR26_FIELD_0_MASK)

#define IOMUXC_LPSR_GPR_GPR26_DWP_MASK           (0x30000000U)
#define IOMUXC_LPSR_GPR_GPR26_DWP_SHIFT          (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_LPSR_GPR_GPR26_DWP(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR26_DWP_SHIFT)) & IOMUXC_LPSR_GPR_GPR26_DWP_MASK)

#define IOMUXC_LPSR_GPR_GPR26_DWP_LOCK_MASK      (0xC0000000U)
#define IOMUXC_LPSR_GPR_GPR26_DWP_LOCK_SHIFT     (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_LPSR_GPR_GPR26_DWP_LOCK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR26_DWP_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR26_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR33 - GPR33 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR33_M4_NMI_CLEAR_MASK  (0x1U)
#define IOMUXC_LPSR_GPR_GPR33_M4_NMI_CLEAR_SHIFT (0U)
/*! M4_NMI_CLEAR - Clear CM4 NMI holding register */
#define IOMUXC_LPSR_GPR_GPR33_M4_NMI_CLEAR(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR33_M4_NMI_CLEAR_SHIFT)) & IOMUXC_LPSR_GPR_GPR33_M4_NMI_CLEAR_MASK)

#define IOMUXC_LPSR_GPR_GPR33_USBPHY1_WAKEUP_IRQ_CLEAR_MASK (0x100U)
#define IOMUXC_LPSR_GPR_GPR33_USBPHY1_WAKEUP_IRQ_CLEAR_SHIFT (8U)
/*! USBPHY1_WAKEUP_IRQ_CLEAR - Clear USBPHY1 wakeup interrupt holding register */
#define IOMUXC_LPSR_GPR_GPR33_USBPHY1_WAKEUP_IRQ_CLEAR(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR33_USBPHY1_WAKEUP_IRQ_CLEAR_SHIFT)) & IOMUXC_LPSR_GPR_GPR33_USBPHY1_WAKEUP_IRQ_CLEAR_MASK)

#define IOMUXC_LPSR_GPR_GPR33_USBPHY2_WAKEUP_IRQ_CLEAR_MASK (0x200U)
#define IOMUXC_LPSR_GPR_GPR33_USBPHY2_WAKEUP_IRQ_CLEAR_SHIFT (9U)
/*! USBPHY2_WAKEUP_IRQ_CLEAR - Clear USBPHY1 wakeup interrupt holding register */
#define IOMUXC_LPSR_GPR_GPR33_USBPHY2_WAKEUP_IRQ_CLEAR(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR33_USBPHY2_WAKEUP_IRQ_CLEAR_SHIFT)) & IOMUXC_LPSR_GPR_GPR33_USBPHY2_WAKEUP_IRQ_CLEAR_MASK)

#define IOMUXC_LPSR_GPR_GPR33_DWP_MASK           (0x30000000U)
#define IOMUXC_LPSR_GPR_GPR33_DWP_SHIFT          (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_LPSR_GPR_GPR33_DWP(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR33_DWP_SHIFT)) & IOMUXC_LPSR_GPR_GPR33_DWP_MASK)

#define IOMUXC_LPSR_GPR_GPR33_DWP_LOCK_MASK      (0xC0000000U)
#define IOMUXC_LPSR_GPR_GPR33_DWP_LOCK_SHIFT     (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_LPSR_GPR_GPR33_DWP_LOCK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR33_DWP_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR33_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR34 - GPR34 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR34_GPIO_LPSR_HIGH_RANGE_MASK (0x2U)
#define IOMUXC_LPSR_GPR_GPR34_GPIO_LPSR_HIGH_RANGE_SHIFT (1U)
/*! GPIO_LPSR_HIGH_RANGE - GPIO_LPSR IO bank supply voltage range selection */
#define IOMUXC_LPSR_GPR_GPR34_GPIO_LPSR_HIGH_RANGE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR34_GPIO_LPSR_HIGH_RANGE_SHIFT)) & IOMUXC_LPSR_GPR_GPR34_GPIO_LPSR_HIGH_RANGE_MASK)

#define IOMUXC_LPSR_GPR_GPR34_GPIO_LPSR_LOW_RANGE_MASK (0x4U)
#define IOMUXC_LPSR_GPR_GPR34_GPIO_LPSR_LOW_RANGE_SHIFT (2U)
/*! GPIO_LPSR_LOW_RANGE - GPIO_LPSR IO bank supply voltage range selection */
#define IOMUXC_LPSR_GPR_GPR34_GPIO_LPSR_LOW_RANGE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR34_GPIO_LPSR_LOW_RANGE_SHIFT)) & IOMUXC_LPSR_GPR_GPR34_GPIO_LPSR_LOW_RANGE_MASK)

#define IOMUXC_LPSR_GPR_GPR34_M7_NMI_MASK_MASK   (0x8U)
#define IOMUXC_LPSR_GPR_GPR34_M7_NMI_MASK_SHIFT  (3U)
/*! M7_NMI_MASK - Mask CM7 NMI pin input
 *  0b0..NMI input from IO to CM7 is not blocked
 *  0b1..NMI input from IO to CM7 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR34_M7_NMI_MASK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR34_M7_NMI_MASK_SHIFT)) & IOMUXC_LPSR_GPR_GPR34_M7_NMI_MASK_MASK)

#define IOMUXC_LPSR_GPR_GPR34_M4_NMI_MASK_MASK   (0x10U)
#define IOMUXC_LPSR_GPR_GPR34_M4_NMI_MASK_SHIFT  (4U)
/*! M4_NMI_MASK - Mask CM4 NMI pin input
 *  0b0..NMI input from IO to CM4 is not blocked
 *  0b1..NMI input from IO to CM4 is blocked
 */
#define IOMUXC_LPSR_GPR_GPR34_M4_NMI_MASK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR34_M4_NMI_MASK_SHIFT)) & IOMUXC_LPSR_GPR_GPR34_M4_NMI_MASK_MASK)

#define IOMUXC_LPSR_GPR_GPR34_M4_GPC_SLEEP_SEL_MASK (0x20U)
#define IOMUXC_LPSR_GPR_GPR34_M4_GPC_SLEEP_SEL_SHIFT (5U)
/*! M4_GPC_SLEEP_SEL - CM4 sleep request selection
 *  0b0..CM4 SLEEPDEEP is sent to GPC
 *  0b1..CM4 SLEEPING is sent to GPC
 */
#define IOMUXC_LPSR_GPR_GPR34_M4_GPC_SLEEP_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR34_M4_GPC_SLEEP_SEL_SHIFT)) & IOMUXC_LPSR_GPR_GPR34_M4_GPC_SLEEP_SEL_MASK)

#define IOMUXC_LPSR_GPR_GPR34_SEC_ERR_RESP_MASK  (0x800U)
#define IOMUXC_LPSR_GPR_GPR34_SEC_ERR_RESP_SHIFT (11U)
/*! SEC_ERR_RESP - Security error response enable
 *  0b0..OKEY response
 *  0b1..SLVError (default)
 */
#define IOMUXC_LPSR_GPR_GPR34_SEC_ERR_RESP(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR34_SEC_ERR_RESP_SHIFT)) & IOMUXC_LPSR_GPR_GPR34_SEC_ERR_RESP_MASK)

#define IOMUXC_LPSR_GPR_GPR34_DWP_MASK           (0x30000000U)
#define IOMUXC_LPSR_GPR_GPR34_DWP_SHIFT          (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_LPSR_GPR_GPR34_DWP(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR34_DWP_SHIFT)) & IOMUXC_LPSR_GPR_GPR34_DWP_MASK)

#define IOMUXC_LPSR_GPR_GPR34_DWP_LOCK_MASK      (0xC0000000U)
#define IOMUXC_LPSR_GPR_GPR34_DWP_LOCK_SHIFT     (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_LPSR_GPR_GPR34_DWP_LOCK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR34_DWP_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR34_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR35 - GPR35 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR35_ADC1_IPG_DOZE_MASK (0x1U)
#define IOMUXC_LPSR_GPR_GPR35_ADC1_IPG_DOZE_SHIFT (0U)
/*! ADC1_IPG_DOZE - ADC1 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR35_ADC1_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_ADC1_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_ADC1_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_ADC1_STOP_REQ_MASK (0x2U)
#define IOMUXC_LPSR_GPR_GPR35_ADC1_STOP_REQ_SHIFT (1U)
/*! ADC1_STOP_REQ - ADC1 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR35_ADC1_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_ADC1_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_ADC1_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR35_ADC1_IPG_STOP_MODE_MASK (0x4U)
#define IOMUXC_LPSR_GPR_GPR35_ADC1_IPG_STOP_MODE_SHIFT (2U)
/*! ADC1_IPG_STOP_MODE - ADC1 stop mode selection. This bitfield cannot change when ADC1_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR35_ADC1_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_ADC1_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_ADC1_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_ADC2_IPG_DOZE_MASK (0x8U)
#define IOMUXC_LPSR_GPR_GPR35_ADC2_IPG_DOZE_SHIFT (3U)
/*! ADC2_IPG_DOZE - ADC2 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR35_ADC2_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_ADC2_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_ADC2_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_ADC2_STOP_REQ_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR35_ADC2_STOP_REQ_SHIFT (4U)
/*! ADC2_STOP_REQ - ADC2 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR35_ADC2_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_ADC2_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_ADC2_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR35_ADC2_IPG_STOP_MODE_MASK (0x20U)
#define IOMUXC_LPSR_GPR_GPR35_ADC2_IPG_STOP_MODE_SHIFT (5U)
/*! ADC2_IPG_STOP_MODE - ADC2 stop mode selection. This bitfield cannot change when ADC2_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR35_ADC2_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_ADC2_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_ADC2_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_CAAM_IPG_DOZE_MASK (0x40U)
#define IOMUXC_LPSR_GPR_GPR35_CAAM_IPG_DOZE_SHIFT (6U)
/*! CAAM_IPG_DOZE - CAN3 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR35_CAAM_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_CAAM_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_CAAM_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_CAAM_STOP_REQ_MASK (0x80U)
#define IOMUXC_LPSR_GPR_GPR35_CAAM_STOP_REQ_SHIFT (7U)
/*! CAAM_STOP_REQ - CAAM stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR35_CAAM_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_CAAM_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_CAAM_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR35_CAN1_IPG_DOZE_MASK (0x100U)
#define IOMUXC_LPSR_GPR_GPR35_CAN1_IPG_DOZE_SHIFT (8U)
/*! CAN1_IPG_DOZE - CAN1 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR35_CAN1_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_CAN1_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_CAN1_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_CAN1_STOP_REQ_MASK (0x200U)
#define IOMUXC_LPSR_GPR_GPR35_CAN1_STOP_REQ_SHIFT (9U)
/*! CAN1_STOP_REQ - CAN1 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR35_CAN1_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_CAN1_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_CAN1_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR35_CAN2_IPG_DOZE_MASK (0x400U)
#define IOMUXC_LPSR_GPR_GPR35_CAN2_IPG_DOZE_SHIFT (10U)
/*! CAN2_IPG_DOZE - CAN2 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR35_CAN2_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_CAN2_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_CAN2_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_CAN2_STOP_REQ_MASK (0x800U)
#define IOMUXC_LPSR_GPR_GPR35_CAN2_STOP_REQ_SHIFT (11U)
/*! CAN2_STOP_REQ - CAN2 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR35_CAN2_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_CAN2_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_CAN2_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR35_CAN3_IPG_DOZE_MASK (0x1000U)
#define IOMUXC_LPSR_GPR_GPR35_CAN3_IPG_DOZE_SHIFT (12U)
/*! CAN3_IPG_DOZE - CAN3 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR35_CAN3_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_CAN3_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_CAN3_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_CAN3_STOP_REQ_MASK (0x2000U)
#define IOMUXC_LPSR_GPR_GPR35_CAN3_STOP_REQ_SHIFT (13U)
/*! CAN3_STOP_REQ - CAN3 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR35_CAN3_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_CAN3_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_CAN3_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR35_EDMA_STOP_REQ_MASK (0x8000U)
#define IOMUXC_LPSR_GPR_GPR35_EDMA_STOP_REQ_SHIFT (15U)
/*! EDMA_STOP_REQ - EDMA stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR35_EDMA_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_EDMA_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_EDMA_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR35_EDMA_LPSR_STOP_REQ_MASK (0x10000U)
#define IOMUXC_LPSR_GPR_GPR35_EDMA_LPSR_STOP_REQ_SHIFT (16U)
/*! EDMA_LPSR_STOP_REQ - EDMA_LPSR stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR35_EDMA_LPSR_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_EDMA_LPSR_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_EDMA_LPSR_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR35_ENET_IPG_DOZE_MASK (0x20000U)
#define IOMUXC_LPSR_GPR_GPR35_ENET_IPG_DOZE_SHIFT (17U)
/*! ENET_IPG_DOZE - ENET doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR35_ENET_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_ENET_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_ENET_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_ENET_STOP_REQ_MASK (0x40000U)
#define IOMUXC_LPSR_GPR_GPR35_ENET_STOP_REQ_SHIFT (18U)
/*! ENET_STOP_REQ - ENET stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR35_ENET_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_ENET_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_ENET_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR35_ENET1G_IPG_DOZE_MASK (0x80000U)
#define IOMUXC_LPSR_GPR_GPR35_ENET1G_IPG_DOZE_SHIFT (19U)
/*! ENET1G_IPG_DOZE - ENET1G doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR35_ENET1G_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_ENET1G_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_ENET1G_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_ENET1G_STOP_REQ_MASK (0x100000U)
#define IOMUXC_LPSR_GPR_GPR35_ENET1G_STOP_REQ_SHIFT (20U)
/*! ENET1G_STOP_REQ - ENET1G stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR35_ENET1G_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_ENET1G_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_ENET1G_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR35_FLEXIO1_IPG_DOZE_MASK (0x200000U)
#define IOMUXC_LPSR_GPR_GPR35_FLEXIO1_IPG_DOZE_SHIFT (21U)
/*! FLEXIO1_IPG_DOZE - FLEXIO2 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR35_FLEXIO1_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_FLEXIO1_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_FLEXIO1_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_FLEXIO2_IPG_DOZE_MASK (0x400000U)
#define IOMUXC_LPSR_GPR_GPR35_FLEXIO2_IPG_DOZE_SHIFT (22U)
/*! FLEXIO2_IPG_DOZE - FLEXIO2 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR35_FLEXIO2_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_FLEXIO2_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_FLEXIO2_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_FLEXSPI1_IPG_DOZE_MASK (0x800000U)
#define IOMUXC_LPSR_GPR_GPR35_FLEXSPI1_IPG_DOZE_SHIFT (23U)
/*! FLEXSPI1_IPG_DOZE - FLEXSPI1 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR35_FLEXSPI1_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_FLEXSPI1_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_FLEXSPI1_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_FLEXSPI1_STOP_REQ_MASK (0x1000000U)
#define IOMUXC_LPSR_GPR_GPR35_FLEXSPI1_STOP_REQ_SHIFT (24U)
/*! FLEXSPI1_STOP_REQ - FLEXSPI1 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR35_FLEXSPI1_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_FLEXSPI1_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_FLEXSPI1_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR35_FLEXSPI2_IPG_DOZE_MASK (0x2000000U)
#define IOMUXC_LPSR_GPR_GPR35_FLEXSPI2_IPG_DOZE_SHIFT (25U)
/*! FLEXSPI2_IPG_DOZE - FLEXSPI2 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR35_FLEXSPI2_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_FLEXSPI2_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_FLEXSPI2_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR35_FLEXSPI2_STOP_REQ_MASK (0x4000000U)
#define IOMUXC_LPSR_GPR_GPR35_FLEXSPI2_STOP_REQ_SHIFT (26U)
/*! FLEXSPI2_STOP_REQ - FLEXSPI2 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR35_FLEXSPI2_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_FLEXSPI2_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_FLEXSPI2_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR35_DWP_MASK           (0x30000000U)
#define IOMUXC_LPSR_GPR_GPR35_DWP_SHIFT          (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_LPSR_GPR_GPR35_DWP(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_DWP_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_DWP_MASK)

#define IOMUXC_LPSR_GPR_GPR35_DWP_LOCK_MASK      (0xC0000000U)
#define IOMUXC_LPSR_GPR_GPR35_DWP_LOCK_SHIFT     (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_LPSR_GPR_GPR35_DWP_LOCK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR35_DWP_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR35_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR36 - GPR36 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR36_GPT1_IPG_DOZE_MASK (0x1U)
#define IOMUXC_LPSR_GPR_GPR36_GPT1_IPG_DOZE_SHIFT (0U)
/*! GPT1_IPG_DOZE - GPT1 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR36_GPT1_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_GPT1_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_GPT1_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_GPT2_IPG_DOZE_MASK (0x2U)
#define IOMUXC_LPSR_GPR_GPR36_GPT2_IPG_DOZE_SHIFT (1U)
/*! GPT2_IPG_DOZE - GPT2 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR36_GPT2_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_GPT2_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_GPT2_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_GPT3_IPG_DOZE_MASK (0x4U)
#define IOMUXC_LPSR_GPR_GPR36_GPT3_IPG_DOZE_SHIFT (2U)
/*! GPT3_IPG_DOZE - GPT3 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR36_GPT3_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_GPT3_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_GPT3_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_GPT4_IPG_DOZE_MASK (0x8U)
#define IOMUXC_LPSR_GPR_GPR36_GPT4_IPG_DOZE_SHIFT (3U)
/*! GPT4_IPG_DOZE - GPT4 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR36_GPT4_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_GPT4_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_GPT4_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_GPT5_IPG_DOZE_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR36_GPT5_IPG_DOZE_SHIFT (4U)
/*! GPT5_IPG_DOZE - GPT5 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR36_GPT5_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_GPT5_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_GPT5_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_GPT6_IPG_DOZE_MASK (0x20U)
#define IOMUXC_LPSR_GPR_GPR36_GPT6_IPG_DOZE_SHIFT (5U)
/*! GPT6_IPG_DOZE - GPT6 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR36_GPT6_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_GPT6_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_GPT6_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C1_IPG_DOZE_MASK (0x40U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C1_IPG_DOZE_SHIFT (6U)
/*! LPI2C1_IPG_DOZE - LPI2C1 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C1_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C1_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C1_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C1_STOP_REQ_MASK (0x80U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C1_STOP_REQ_SHIFT (7U)
/*! LPI2C1_STOP_REQ - LPI2C1 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C1_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C1_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C1_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C1_IPG_STOP_MODE_MASK (0x100U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C1_IPG_STOP_MODE_SHIFT (8U)
/*! LPI2C1_IPG_STOP_MODE - LPI2C1 stop mode selection. This bitfield cannot change when LPI2C1_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C1_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C1_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C1_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C2_IPG_DOZE_MASK (0x200U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C2_IPG_DOZE_SHIFT (9U)
/*! LPI2C2_IPG_DOZE - LPI2C2 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C2_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C2_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C2_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C2_STOP_REQ_MASK (0x400U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C2_STOP_REQ_SHIFT (10U)
/*! LPI2C2_STOP_REQ - LPI2C2 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C2_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C2_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C2_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C2_IPG_STOP_MODE_MASK (0x800U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C2_IPG_STOP_MODE_SHIFT (11U)
/*! LPI2C2_IPG_STOP_MODE - LPI2C2 stop mode selection. This bitfield cannot change when LPI2C2_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C2_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C2_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C2_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C3_IPG_DOZE_MASK (0x1000U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C3_IPG_DOZE_SHIFT (12U)
/*! LPI2C3_IPG_DOZE - LPI2C3 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C3_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C3_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C3_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C3_STOP_REQ_MASK (0x2000U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C3_STOP_REQ_SHIFT (13U)
/*! LPI2C3_STOP_REQ - LPI2C3 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C3_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C3_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C3_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C3_IPG_STOP_MODE_MASK (0x4000U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C3_IPG_STOP_MODE_SHIFT (14U)
/*! LPI2C3_IPG_STOP_MODE - LPI2C3 stop mode selection. This bitfield cannot change when LPI2C3_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C3_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C3_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C3_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C4_IPG_DOZE_MASK (0x8000U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C4_IPG_DOZE_SHIFT (15U)
/*! LPI2C4_IPG_DOZE - LPI2C4 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C4_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C4_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C4_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C4_STOP_REQ_MASK (0x10000U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C4_STOP_REQ_SHIFT (16U)
/*! LPI2C4_STOP_REQ - LPI2C4 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C4_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C4_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C4_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C4_IPG_STOP_MODE_MASK (0x20000U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C4_IPG_STOP_MODE_SHIFT (17U)
/*! LPI2C4_IPG_STOP_MODE - LPI2C4 stop mode selection. This bitfield cannot change when LPI2C4_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C4_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C4_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C4_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C5_IPG_DOZE_MASK (0x40000U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C5_IPG_DOZE_SHIFT (18U)
/*! LPI2C5_IPG_DOZE - LPI2C5 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C5_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C5_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C5_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C5_STOP_REQ_MASK (0x80000U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C5_STOP_REQ_SHIFT (19U)
/*! LPI2C5_STOP_REQ - LPI2C5 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C5_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C5_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C5_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C5_IPG_STOP_MODE_MASK (0x100000U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C5_IPG_STOP_MODE_SHIFT (20U)
/*! LPI2C5_IPG_STOP_MODE - LPI2C5 stop mode selection. This bitfield cannot change when LPI2C5_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C5_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C5_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C5_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C6_IPG_DOZE_MASK (0x200000U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C6_IPG_DOZE_SHIFT (21U)
/*! LPI2C6_IPG_DOZE - LPI2C6 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C6_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C6_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C6_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C6_STOP_REQ_MASK (0x400000U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C6_STOP_REQ_SHIFT (22U)
/*! LPI2C6_STOP_REQ - LPI2C6 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C6_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C6_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C6_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPI2C6_IPG_STOP_MODE_MASK (0x800000U)
#define IOMUXC_LPSR_GPR_GPR36_LPI2C6_IPG_STOP_MODE_SHIFT (23U)
/*! LPI2C6_IPG_STOP_MODE - LPI2C6 stop mode selection. This bitfield cannot change when LPI2C6_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR36_LPI2C6_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPI2C6_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPI2C6_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPSPI1_IPG_DOZE_MASK (0x1000000U)
#define IOMUXC_LPSR_GPR_GPR36_LPSPI1_IPG_DOZE_SHIFT (24U)
/*! LPSPI1_IPG_DOZE - LPSPI1 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR36_LPSPI1_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPSPI1_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPSPI1_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPSPI1_STOP_REQ_MASK (0x2000000U)
#define IOMUXC_LPSR_GPR_GPR36_LPSPI1_STOP_REQ_SHIFT (25U)
/*! LPSPI1_STOP_REQ - LPSPI1 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR36_LPSPI1_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPSPI1_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPSPI1_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR36_LPSPI1_IPG_STOP_MODE_MASK (0x4000000U)
#define IOMUXC_LPSR_GPR_GPR36_LPSPI1_IPG_STOP_MODE_SHIFT (26U)
/*! LPSPI1_IPG_STOP_MODE - LPSPI1 stop mode selection. This bitfield cannot change when LPSPI1_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR36_LPSPI1_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_LPSPI1_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_LPSPI1_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR36_DWP_MASK           (0x30000000U)
#define IOMUXC_LPSR_GPR_GPR36_DWP_SHIFT          (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_LPSR_GPR_GPR36_DWP(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_DWP_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_DWP_MASK)

#define IOMUXC_LPSR_GPR_GPR36_DWP_LOCK_MASK      (0xC0000000U)
#define IOMUXC_LPSR_GPR_GPR36_DWP_LOCK_SHIFT     (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_LPSR_GPR_GPR36_DWP_LOCK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR36_DWP_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR36_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR37 - GPR37 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR37_LPSPI2_IPG_DOZE_MASK (0x1U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI2_IPG_DOZE_SHIFT (0U)
/*! LPSPI2_IPG_DOZE - LPSPI2 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI2_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI2_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI2_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI2_STOP_REQ_MASK (0x2U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI2_STOP_REQ_SHIFT (1U)
/*! LPSPI2_STOP_REQ - LPSPI2 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI2_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI2_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI2_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI2_IPG_STOP_MODE_MASK (0x4U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI2_IPG_STOP_MODE_SHIFT (2U)
/*! LPSPI2_IPG_STOP_MODE - LPSPI2 stop mode selection. This bitfield cannot change when LPSPI2_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI2_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI2_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI2_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI3_IPG_DOZE_MASK (0x8U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI3_IPG_DOZE_SHIFT (3U)
/*! LPSPI3_IPG_DOZE - LPSPI3 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI3_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI3_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI3_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI3_STOP_REQ_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI3_STOP_REQ_SHIFT (4U)
/*! LPSPI3_STOP_REQ - LPSPI3 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI3_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI3_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI3_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI3_IPG_STOP_MODE_MASK (0x20U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI3_IPG_STOP_MODE_SHIFT (5U)
/*! LPSPI3_IPG_STOP_MODE - LPSPI3 stop mode selection. This bitfield cannot change when LPSPI3_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI3_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI3_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI3_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI4_IPG_DOZE_MASK (0x40U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI4_IPG_DOZE_SHIFT (6U)
/*! LPSPI4_IPG_DOZE - LPSPI4 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI4_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI4_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI4_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI4_STOP_REQ_MASK (0x80U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI4_STOP_REQ_SHIFT (7U)
/*! LPSPI4_STOP_REQ - LPSPI4 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI4_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI4_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI4_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI4_IPG_STOP_MODE_MASK (0x100U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI4_IPG_STOP_MODE_SHIFT (8U)
/*! LPSPI4_IPG_STOP_MODE - LPSPI4 stop mode selection. This bitfield cannot change when LPSPI4_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI4_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI4_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI4_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI5_IPG_DOZE_MASK (0x200U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI5_IPG_DOZE_SHIFT (9U)
/*! LPSPI5_IPG_DOZE - LPSPI5 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI5_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI5_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI5_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI5_STOP_REQ_MASK (0x400U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI5_STOP_REQ_SHIFT (10U)
/*! LPSPI5_STOP_REQ - LPSPI5 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI5_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI5_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI5_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI5_IPG_STOP_MODE_MASK (0x800U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI5_IPG_STOP_MODE_SHIFT (11U)
/*! LPSPI5_IPG_STOP_MODE - LPSPI5 stop mode selection. This bitfield cannot change when LPSPI5_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI5_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI5_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI5_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI6_IPG_DOZE_MASK (0x1000U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI6_IPG_DOZE_SHIFT (12U)
/*! LPSPI6_IPG_DOZE - LPSPI6 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI6_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI6_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI6_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI6_STOP_REQ_MASK (0x2000U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI6_STOP_REQ_SHIFT (13U)
/*! LPSPI6_STOP_REQ - LPSPI6 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI6_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI6_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI6_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPSPI6_IPG_STOP_MODE_MASK (0x4000U)
#define IOMUXC_LPSR_GPR_GPR37_LPSPI6_IPG_STOP_MODE_SHIFT (14U)
/*! LPSPI6_IPG_STOP_MODE - LPSPI6 stop mode selection. This bitfield cannot change when LPSPI6_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR37_LPSPI6_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPSPI6_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPSPI6_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPUART1_IPG_DOZE_MASK (0x8000U)
#define IOMUXC_LPSR_GPR_GPR37_LPUART1_IPG_DOZE_SHIFT (15U)
/*! LPUART1_IPG_DOZE - LPUART1 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR37_LPUART1_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPUART1_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPUART1_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPUART1_STOP_REQ_MASK (0x10000U)
#define IOMUXC_LPSR_GPR_GPR37_LPUART1_STOP_REQ_SHIFT (16U)
/*! LPUART1_STOP_REQ - LPUART1 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR37_LPUART1_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPUART1_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPUART1_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPUART1_IPG_STOP_MODE_MASK (0x20000U)
#define IOMUXC_LPSR_GPR_GPR37_LPUART1_IPG_STOP_MODE_SHIFT (17U)
/*! LPUART1_IPG_STOP_MODE - LPUART1 stop mode selection. This bitfield cannot change when LPUART1_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR37_LPUART1_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPUART1_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPUART1_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPUART2_IPG_DOZE_MASK (0x40000U)
#define IOMUXC_LPSR_GPR_GPR37_LPUART2_IPG_DOZE_SHIFT (18U)
/*! LPUART2_IPG_DOZE - LPUART2 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR37_LPUART2_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPUART2_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPUART2_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPUART2_STOP_REQ_MASK (0x80000U)
#define IOMUXC_LPSR_GPR_GPR37_LPUART2_STOP_REQ_SHIFT (19U)
/*! LPUART2_STOP_REQ - LPUART2 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR37_LPUART2_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPUART2_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPUART2_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPUART2_IPG_STOP_MODE_MASK (0x100000U)
#define IOMUXC_LPSR_GPR_GPR37_LPUART2_IPG_STOP_MODE_SHIFT (20U)
/*! LPUART2_IPG_STOP_MODE - LPUART2 stop mode selection. This bitfield cannot change when LPUART2_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR37_LPUART2_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPUART2_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPUART2_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPUART3_IPG_DOZE_MASK (0x200000U)
#define IOMUXC_LPSR_GPR_GPR37_LPUART3_IPG_DOZE_SHIFT (21U)
/*! LPUART3_IPG_DOZE - LPUART3 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR37_LPUART3_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPUART3_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPUART3_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPUART3_STOP_REQ_MASK (0x400000U)
#define IOMUXC_LPSR_GPR_GPR37_LPUART3_STOP_REQ_SHIFT (22U)
/*! LPUART3_STOP_REQ - LPUART3 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR37_LPUART3_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPUART3_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPUART3_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPUART3_IPG_STOP_MODE_MASK (0x800000U)
#define IOMUXC_LPSR_GPR_GPR37_LPUART3_IPG_STOP_MODE_SHIFT (23U)
/*! LPUART3_IPG_STOP_MODE - LPUART3 stop mode selection. This bitfield cannot change when LPUART3_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR37_LPUART3_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPUART3_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPUART3_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPUART4_IPG_DOZE_MASK (0x1000000U)
#define IOMUXC_LPSR_GPR_GPR37_LPUART4_IPG_DOZE_SHIFT (24U)
/*! LPUART4_IPG_DOZE - LPUART4 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR37_LPUART4_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPUART4_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPUART4_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPUART4_STOP_REQ_MASK (0x2000000U)
#define IOMUXC_LPSR_GPR_GPR37_LPUART4_STOP_REQ_SHIFT (25U)
/*! LPUART4_STOP_REQ - LPUART4 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR37_LPUART4_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPUART4_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPUART4_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR37_LPUART4_IPG_STOP_MODE_MASK (0x4000000U)
#define IOMUXC_LPSR_GPR_GPR37_LPUART4_IPG_STOP_MODE_SHIFT (26U)
/*! LPUART4_IPG_STOP_MODE - LPUART4 stop mode selection. This bitfield cannot change when LPUART4_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR37_LPUART4_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_LPUART4_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_LPUART4_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR37_DWP_MASK           (0x30000000U)
#define IOMUXC_LPSR_GPR_GPR37_DWP_SHIFT          (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_LPSR_GPR_GPR37_DWP(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_DWP_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_DWP_MASK)

#define IOMUXC_LPSR_GPR_GPR37_DWP_LOCK_MASK      (0xC0000000U)
#define IOMUXC_LPSR_GPR_GPR37_DWP_LOCK_SHIFT     (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_LPSR_GPR_GPR37_DWP_LOCK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR37_DWP_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR37_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR38 - GPR38 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR38_LPUART5_IPG_DOZE_MASK (0x1U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART5_IPG_DOZE_SHIFT (0U)
/*! LPUART5_IPG_DOZE - LPUART5 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART5_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART5_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART5_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART5_STOP_REQ_MASK (0x2U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART5_STOP_REQ_SHIFT (1U)
/*! LPUART5_STOP_REQ - LPUART5 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART5_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART5_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART5_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART5_IPG_STOP_MODE_MASK (0x4U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART5_IPG_STOP_MODE_SHIFT (2U)
/*! LPUART5_IPG_STOP_MODE - LPUART5 stop mode selection. This bitfield cannot change when LPUART5_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART5_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART5_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART5_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART6_IPG_DOZE_MASK (0x8U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART6_IPG_DOZE_SHIFT (3U)
/*! LPUART6_IPG_DOZE - LPUART6 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART6_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART6_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART6_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART6_STOP_REQ_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART6_STOP_REQ_SHIFT (4U)
/*! LPUART6_STOP_REQ - LPUART6 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART6_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART6_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART6_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART6_IPG_STOP_MODE_MASK (0x20U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART6_IPG_STOP_MODE_SHIFT (5U)
/*! LPUART6_IPG_STOP_MODE - LPUART6 stop mode selection. This bitfield cannot change when LPUART6_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART6_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART6_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART6_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART7_IPG_DOZE_MASK (0x40U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART7_IPG_DOZE_SHIFT (6U)
/*! LPUART7_IPG_DOZE - LPUART7 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART7_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART7_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART7_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART7_STOP_REQ_MASK (0x80U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART7_STOP_REQ_SHIFT (7U)
/*! LPUART7_STOP_REQ - LPUART7 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART7_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART7_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART7_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART7_IPG_STOP_MODE_MASK (0x100U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART7_IPG_STOP_MODE_SHIFT (8U)
/*! LPUART7_IPG_STOP_MODE - LPUART7 stop mode selection. This bitfield cannot change when LPUART7_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART7_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART7_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART7_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART8_IPG_DOZE_MASK (0x200U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART8_IPG_DOZE_SHIFT (9U)
/*! LPUART8_IPG_DOZE - LPUART8 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART8_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART8_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART8_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART8_STOP_REQ_MASK (0x400U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART8_STOP_REQ_SHIFT (10U)
/*! LPUART8_STOP_REQ - LPUART8 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART8_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART8_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART8_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART8_IPG_STOP_MODE_MASK (0x800U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART8_IPG_STOP_MODE_SHIFT (11U)
/*! LPUART8_IPG_STOP_MODE - LPUART8 stop mode selection. This bitfield cannot change when LPUART8_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART8_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART8_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART8_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART9_IPG_DOZE_MASK (0x1000U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART9_IPG_DOZE_SHIFT (12U)
/*! LPUART9_IPG_DOZE - LPUART9 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART9_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART9_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART9_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART9_STOP_REQ_MASK (0x2000U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART9_STOP_REQ_SHIFT (13U)
/*! LPUART9_STOP_REQ - LPUART9 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART9_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART9_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART9_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART9_IPG_STOP_MODE_MASK (0x4000U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART9_IPG_STOP_MODE_SHIFT (14U)
/*! LPUART9_IPG_STOP_MODE - LPUART9 stop mode selection. This bitfield cannot change when LPUART9_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART9_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART9_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART9_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART10_IPG_DOZE_MASK (0x8000U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART10_IPG_DOZE_SHIFT (15U)
/*! LPUART10_IPG_DOZE - LPUART10 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART10_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART10_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART10_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART10_STOP_REQ_MASK (0x10000U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART10_STOP_REQ_SHIFT (16U)
/*! LPUART10_STOP_REQ - LPUART10 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART10_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART10_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART10_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART10_IPG_STOP_MODE_MASK (0x20000U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART10_IPG_STOP_MODE_SHIFT (17U)
/*! LPUART10_IPG_STOP_MODE - LPUART10 stop mode selection. This bitfield cannot change when LPUART10_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART10_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART10_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART10_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART11_IPG_DOZE_MASK (0x40000U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART11_IPG_DOZE_SHIFT (18U)
/*! LPUART11_IPG_DOZE - LPUART11 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART11_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART11_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART11_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART11_STOP_REQ_MASK (0x80000U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART11_STOP_REQ_SHIFT (19U)
/*! LPUART11_STOP_REQ - LPUART11 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART11_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART11_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART11_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART11_IPG_STOP_MODE_MASK (0x100000U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART11_IPG_STOP_MODE_SHIFT (20U)
/*! LPUART11_IPG_STOP_MODE - LPUART11 stop mode selection. This bitfield cannot change when LPUART11_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART11_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART11_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART11_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART12_IPG_DOZE_MASK (0x200000U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART12_IPG_DOZE_SHIFT (21U)
/*! LPUART12_IPG_DOZE - LPUART12 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART12_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART12_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART12_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART12_STOP_REQ_MASK (0x400000U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART12_STOP_REQ_SHIFT (22U)
/*! LPUART12_STOP_REQ - LPUART12 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART12_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART12_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART12_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR38_LPUART12_IPG_STOP_MODE_MASK (0x800000U)
#define IOMUXC_LPSR_GPR_GPR38_LPUART12_IPG_STOP_MODE_SHIFT (23U)
/*! LPUART12_IPG_STOP_MODE - LPUART12 stop mode selection. This bitfield cannot change when LPUART12_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR38_LPUART12_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_LPUART12_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_LPUART12_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_MIC_IPG_DOZE_MASK  (0x1000000U)
#define IOMUXC_LPSR_GPR_GPR38_MIC_IPG_DOZE_SHIFT (24U)
/*! MIC_IPG_DOZE - MIC doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR38_MIC_IPG_DOZE(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_MIC_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_MIC_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_MIC_STOP_REQ_MASK  (0x2000000U)
#define IOMUXC_LPSR_GPR_GPR38_MIC_STOP_REQ_SHIFT (25U)
/*! MIC_STOP_REQ - MIC stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR38_MIC_STOP_REQ(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_MIC_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_MIC_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR38_MIC_IPG_STOP_MODE_MASK (0x4000000U)
#define IOMUXC_LPSR_GPR_GPR38_MIC_IPG_STOP_MODE_SHIFT (26U)
/*! MIC_IPG_STOP_MODE - MIC stop mode selection. This bitfield cannot change when MIC_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_LPSR_GPR_GPR38_MIC_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_MIC_IPG_STOP_MODE_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_MIC_IPG_STOP_MODE_MASK)

#define IOMUXC_LPSR_GPR_GPR38_DWP_MASK           (0x30000000U)
#define IOMUXC_LPSR_GPR_GPR38_DWP_SHIFT          (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_LPSR_GPR_GPR38_DWP(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_DWP_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_DWP_MASK)

#define IOMUXC_LPSR_GPR_GPR38_DWP_LOCK_MASK      (0xC0000000U)
#define IOMUXC_LPSR_GPR_GPR38_DWP_LOCK_SHIFT     (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_LPSR_GPR_GPR38_DWP_LOCK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR38_DWP_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR38_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR39 - GPR39 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR39_PIT1_STOP_REQ_MASK (0x2U)
#define IOMUXC_LPSR_GPR_GPR39_PIT1_STOP_REQ_SHIFT (1U)
/*! PIT1_STOP_REQ - PIT1 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR39_PIT1_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_PIT1_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_PIT1_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR39_PIT2_STOP_REQ_MASK (0x4U)
#define IOMUXC_LPSR_GPR_GPR39_PIT2_STOP_REQ_SHIFT (2U)
/*! PIT2_STOP_REQ - PIT2 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR39_PIT2_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_PIT2_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_PIT2_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR39_SEMC_STOP_REQ_MASK (0x8U)
#define IOMUXC_LPSR_GPR_GPR39_SEMC_STOP_REQ_SHIFT (3U)
/*! SEMC_STOP_REQ - SEMC stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR39_SEMC_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_SEMC_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_SEMC_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR39_SIM1_IPG_DOZE_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR39_SIM1_IPG_DOZE_SHIFT (4U)
/*! SIM1_IPG_DOZE - SIM1 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR39_SIM1_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_SIM1_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_SIM1_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR39_SIM2_IPG_DOZE_MASK (0x20U)
#define IOMUXC_LPSR_GPR_GPR39_SIM2_IPG_DOZE_SHIFT (5U)
/*! SIM2_IPG_DOZE - SIM2 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR39_SIM2_IPG_DOZE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_SIM2_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_SIM2_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR39_SNVS_HP_IPG_DOZE_MASK (0x40U)
#define IOMUXC_LPSR_GPR_GPR39_SNVS_HP_IPG_DOZE_SHIFT (6U)
/*! SNVS_HP_IPG_DOZE - SNVS_HP doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR39_SNVS_HP_IPG_DOZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_SNVS_HP_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_SNVS_HP_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR39_SNVS_HP_STOP_REQ_MASK (0x80U)
#define IOMUXC_LPSR_GPR_GPR39_SNVS_HP_STOP_REQ_SHIFT (7U)
/*! SNVS_HP_STOP_REQ - SNVS_HP stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR39_SNVS_HP_STOP_REQ(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_SNVS_HP_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_SNVS_HP_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR39_WDOG1_IPG_DOZE_MASK (0x100U)
#define IOMUXC_LPSR_GPR_GPR39_WDOG1_IPG_DOZE_SHIFT (8U)
/*! WDOG1_IPG_DOZE - WDOG1 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR39_WDOG1_IPG_DOZE(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_WDOG1_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_WDOG1_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR39_WDOG2_IPG_DOZE_MASK (0x200U)
#define IOMUXC_LPSR_GPR_GPR39_WDOG2_IPG_DOZE_SHIFT (9U)
/*! WDOG2_IPG_DOZE - WDOG2 doze mode
 *  0b0..Not in doze mode
 *  0b1..In doze mode
 */
#define IOMUXC_LPSR_GPR_GPR39_WDOG2_IPG_DOZE(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_WDOG2_IPG_DOZE_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_WDOG2_IPG_DOZE_MASK)

#define IOMUXC_LPSR_GPR_GPR39_SAI1_STOP_REQ_MASK (0x400U)
#define IOMUXC_LPSR_GPR_GPR39_SAI1_STOP_REQ_SHIFT (10U)
/*! SAI1_STOP_REQ - SAI1 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR39_SAI1_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_SAI1_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_SAI1_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR39_SAI2_STOP_REQ_MASK (0x800U)
#define IOMUXC_LPSR_GPR_GPR39_SAI2_STOP_REQ_SHIFT (11U)
/*! SAI2_STOP_REQ - SAI2 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR39_SAI2_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_SAI2_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_SAI2_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR39_SAI3_STOP_REQ_MASK (0x1000U)
#define IOMUXC_LPSR_GPR_GPR39_SAI3_STOP_REQ_SHIFT (12U)
/*! SAI3_STOP_REQ - SAI3 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR39_SAI3_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_SAI3_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_SAI3_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR39_SAI4_STOP_REQ_MASK (0x2000U)
#define IOMUXC_LPSR_GPR_GPR39_SAI4_STOP_REQ_SHIFT (13U)
/*! SAI4_STOP_REQ - SAI4 stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR39_SAI4_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_SAI4_STOP_REQ_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_SAI4_STOP_REQ_MASK)

#define IOMUXC_LPSR_GPR_GPR39_FLEXIO1_STOP_REQ_BUS_MASK (0x4000U)
#define IOMUXC_LPSR_GPR_GPR39_FLEXIO1_STOP_REQ_BUS_SHIFT (14U)
/*! FLEXIO1_STOP_REQ_BUS - FLEXIO1 bus clock domain stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR39_FLEXIO1_STOP_REQ_BUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_FLEXIO1_STOP_REQ_BUS_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_FLEXIO1_STOP_REQ_BUS_MASK)

#define IOMUXC_LPSR_GPR_GPR39_FLEXIO1_STOP_REQ_PER_MASK (0x8000U)
#define IOMUXC_LPSR_GPR_GPR39_FLEXIO1_STOP_REQ_PER_SHIFT (15U)
/*! FLEXIO1_STOP_REQ_PER - FLEXIO1 peripheral clock domain stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR39_FLEXIO1_STOP_REQ_PER(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_FLEXIO1_STOP_REQ_PER_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_FLEXIO1_STOP_REQ_PER_MASK)

#define IOMUXC_LPSR_GPR_GPR39_FLEXIO2_STOP_REQ_BUS_MASK (0x10000U)
#define IOMUXC_LPSR_GPR_GPR39_FLEXIO2_STOP_REQ_BUS_SHIFT (16U)
/*! FLEXIO2_STOP_REQ_BUS - FLEXIO2 bus clock domain stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR39_FLEXIO2_STOP_REQ_BUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_FLEXIO2_STOP_REQ_BUS_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_FLEXIO2_STOP_REQ_BUS_MASK)

#define IOMUXC_LPSR_GPR_GPR39_FLEXIO2_STOP_REQ_PER_MASK (0x20000U)
#define IOMUXC_LPSR_GPR_GPR39_FLEXIO2_STOP_REQ_PER_SHIFT (17U)
/*! FLEXIO2_STOP_REQ_PER - FLEXIO2 peripheral clock domain stop request
 *  0b0..Stop request off
 *  0b1..Stop request on
 */
#define IOMUXC_LPSR_GPR_GPR39_FLEXIO2_STOP_REQ_PER(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_FLEXIO2_STOP_REQ_PER_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_FLEXIO2_STOP_REQ_PER_MASK)

#define IOMUXC_LPSR_GPR_GPR39_DWP_MASK           (0x30000000U)
#define IOMUXC_LPSR_GPR_GPR39_DWP_SHIFT          (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_LPSR_GPR_GPR39_DWP(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_DWP_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_DWP_MASK)

#define IOMUXC_LPSR_GPR_GPR39_DWP_LOCK_MASK      (0xC0000000U)
#define IOMUXC_LPSR_GPR_GPR39_DWP_LOCK_SHIFT     (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_LPSR_GPR_GPR39_DWP_LOCK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR39_DWP_LOCK_SHIFT)) & IOMUXC_LPSR_GPR_GPR39_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR40 - GPR40 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR40_ADC1_STOP_ACK_MASK (0x1U)
#define IOMUXC_LPSR_GPR_GPR40_ADC1_STOP_ACK_SHIFT (0U)
/*! ADC1_STOP_ACK - ADC1 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_ADC1_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_ADC1_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_ADC1_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_ADC2_STOP_ACK_MASK (0x2U)
#define IOMUXC_LPSR_GPR_GPR40_ADC2_STOP_ACK_SHIFT (1U)
/*! ADC2_STOP_ACK - ADC2 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_ADC2_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_ADC2_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_ADC2_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_CAAM_STOP_ACK_MASK (0x4U)
#define IOMUXC_LPSR_GPR_GPR40_CAAM_STOP_ACK_SHIFT (2U)
/*! CAAM_STOP_ACK - CAAM stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_CAAM_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_CAAM_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_CAAM_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_CAN1_STOP_ACK_MASK (0x8U)
#define IOMUXC_LPSR_GPR_GPR40_CAN1_STOP_ACK_SHIFT (3U)
/*! CAN1_STOP_ACK - CAN1 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_CAN1_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_CAN1_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_CAN1_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_CAN2_STOP_ACK_MASK (0x10U)
#define IOMUXC_LPSR_GPR_GPR40_CAN2_STOP_ACK_SHIFT (4U)
/*! CAN2_STOP_ACK - CAN2 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_CAN2_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_CAN2_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_CAN2_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_CAN3_STOP_ACK_MASK (0x20U)
#define IOMUXC_LPSR_GPR_GPR40_CAN3_STOP_ACK_SHIFT (5U)
/*! CAN3_STOP_ACK - CAN3 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_CAN3_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_CAN3_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_CAN3_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_EDMA_STOP_ACK_MASK (0x40U)
#define IOMUXC_LPSR_GPR_GPR40_EDMA_STOP_ACK_SHIFT (6U)
/*! EDMA_STOP_ACK - EDMA stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_EDMA_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_EDMA_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_EDMA_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_EDMA_LPSR_STOP_ACK_MASK (0x80U)
#define IOMUXC_LPSR_GPR_GPR40_EDMA_LPSR_STOP_ACK_SHIFT (7U)
/*! EDMA_LPSR_STOP_ACK - EDMA_LPSR stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_EDMA_LPSR_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_EDMA_LPSR_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_EDMA_LPSR_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_ENET_STOP_ACK_MASK (0x100U)
#define IOMUXC_LPSR_GPR_GPR40_ENET_STOP_ACK_SHIFT (8U)
/*! ENET_STOP_ACK - ENET stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_ENET_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_ENET_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_ENET_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_ENET1G_STOP_ACK_MASK (0x200U)
#define IOMUXC_LPSR_GPR_GPR40_ENET1G_STOP_ACK_SHIFT (9U)
/*! ENET1G_STOP_ACK - ENET1G stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_ENET1G_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_ENET1G_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_ENET1G_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_FLEXSPI1_STOP_ACK_MASK (0x400U)
#define IOMUXC_LPSR_GPR_GPR40_FLEXSPI1_STOP_ACK_SHIFT (10U)
/*! FLEXSPI1_STOP_ACK - FLEXSPI1 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_FLEXSPI1_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_FLEXSPI1_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_FLEXSPI1_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_FLEXSPI2_STOP_ACK_MASK (0x800U)
#define IOMUXC_LPSR_GPR_GPR40_FLEXSPI2_STOP_ACK_SHIFT (11U)
/*! FLEXSPI2_STOP_ACK - FLEXSPI2 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_FLEXSPI2_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_FLEXSPI2_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_FLEXSPI2_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPI2C1_STOP_ACK_MASK (0x1000U)
#define IOMUXC_LPSR_GPR_GPR40_LPI2C1_STOP_ACK_SHIFT (12U)
/*! LPI2C1_STOP_ACK - LPI2C1 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPI2C1_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPI2C1_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPI2C1_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPI2C2_STOP_ACK_MASK (0x2000U)
#define IOMUXC_LPSR_GPR_GPR40_LPI2C2_STOP_ACK_SHIFT (13U)
/*! LPI2C2_STOP_ACK - LPI2C2 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPI2C2_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPI2C2_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPI2C2_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPI2C3_STOP_ACK_MASK (0x4000U)
#define IOMUXC_LPSR_GPR_GPR40_LPI2C3_STOP_ACK_SHIFT (14U)
/*! LPI2C3_STOP_ACK - LPI2C3 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPI2C3_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPI2C3_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPI2C3_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPI2C4_STOP_ACK_MASK (0x8000U)
#define IOMUXC_LPSR_GPR_GPR40_LPI2C4_STOP_ACK_SHIFT (15U)
/*! LPI2C4_STOP_ACK - LPI2C4 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPI2C4_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPI2C4_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPI2C4_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPI2C5_STOP_ACK_MASK (0x10000U)
#define IOMUXC_LPSR_GPR_GPR40_LPI2C5_STOP_ACK_SHIFT (16U)
/*! LPI2C5_STOP_ACK - LPI2C5 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPI2C5_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPI2C5_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPI2C5_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPI2C6_STOP_ACK_MASK (0x20000U)
#define IOMUXC_LPSR_GPR_GPR40_LPI2C6_STOP_ACK_SHIFT (17U)
/*! LPI2C6_STOP_ACK - LPI2C6 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPI2C6_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPI2C6_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPI2C6_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPSPI1_STOP_ACK_MASK (0x40000U)
#define IOMUXC_LPSR_GPR_GPR40_LPSPI1_STOP_ACK_SHIFT (18U)
/*! LPSPI1_STOP_ACK - LPSPI1 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPSPI1_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPSPI1_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPSPI1_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPSPI2_STOP_ACK_MASK (0x80000U)
#define IOMUXC_LPSR_GPR_GPR40_LPSPI2_STOP_ACK_SHIFT (19U)
/*! LPSPI2_STOP_ACK - LPSPI2 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPSPI2_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPSPI2_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPSPI2_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPSPI3_STOP_ACK_MASK (0x100000U)
#define IOMUXC_LPSR_GPR_GPR40_LPSPI3_STOP_ACK_SHIFT (20U)
/*! LPSPI3_STOP_ACK - LPSPI3 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPSPI3_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPSPI3_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPSPI3_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPSPI4_STOP_ACK_MASK (0x200000U)
#define IOMUXC_LPSR_GPR_GPR40_LPSPI4_STOP_ACK_SHIFT (21U)
/*! LPSPI4_STOP_ACK - LPSPI4 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPSPI4_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPSPI4_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPSPI4_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPSPI5_STOP_ACK_MASK (0x400000U)
#define IOMUXC_LPSR_GPR_GPR40_LPSPI5_STOP_ACK_SHIFT (22U)
/*! LPSPI5_STOP_ACK - LPSPI5 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPSPI5_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPSPI5_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPSPI5_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPSPI6_STOP_ACK_MASK (0x800000U)
#define IOMUXC_LPSR_GPR_GPR40_LPSPI6_STOP_ACK_SHIFT (23U)
/*! LPSPI6_STOP_ACK - LPSPI6 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPSPI6_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPSPI6_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPSPI6_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPUART1_STOP_ACK_MASK (0x1000000U)
#define IOMUXC_LPSR_GPR_GPR40_LPUART1_STOP_ACK_SHIFT (24U)
/*! LPUART1_STOP_ACK - LPUART1 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPUART1_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPUART1_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPUART1_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPUART2_STOP_ACK_MASK (0x2000000U)
#define IOMUXC_LPSR_GPR_GPR40_LPUART2_STOP_ACK_SHIFT (25U)
/*! LPUART2_STOP_ACK - LPUART2 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPUART2_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPUART2_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPUART2_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPUART3_STOP_ACK_MASK (0x4000000U)
#define IOMUXC_LPSR_GPR_GPR40_LPUART3_STOP_ACK_SHIFT (26U)
/*! LPUART3_STOP_ACK - LPUART3 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPUART3_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPUART3_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPUART3_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPUART4_STOP_ACK_MASK (0x8000000U)
#define IOMUXC_LPSR_GPR_GPR40_LPUART4_STOP_ACK_SHIFT (27U)
/*! LPUART4_STOP_ACK - LPUART4 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPUART4_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPUART4_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPUART4_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPUART5_STOP_ACK_MASK (0x10000000U)
#define IOMUXC_LPSR_GPR_GPR40_LPUART5_STOP_ACK_SHIFT (28U)
/*! LPUART5_STOP_ACK - LPUART5 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPUART5_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPUART5_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPUART5_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPUART6_STOP_ACK_MASK (0x20000000U)
#define IOMUXC_LPSR_GPR_GPR40_LPUART6_STOP_ACK_SHIFT (29U)
/*! LPUART6_STOP_ACK - LPUART6 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPUART6_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPUART6_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPUART6_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPUART7_STOP_ACK_MASK (0x40000000U)
#define IOMUXC_LPSR_GPR_GPR40_LPUART7_STOP_ACK_SHIFT (30U)
/*! LPUART7_STOP_ACK - LPUART7 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPUART7_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPUART7_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPUART7_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR40_LPUART8_STOP_ACK_MASK (0x80000000U)
#define IOMUXC_LPSR_GPR_GPR40_LPUART8_STOP_ACK_SHIFT (31U)
/*! LPUART8_STOP_ACK - LPUART8 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR40_LPUART8_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR40_LPUART8_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR40_LPUART8_STOP_ACK_MASK)
/*! @} */

/*! @name GPR41 - GPR41 General Purpose Register */
/*! @{ */

#define IOMUXC_LPSR_GPR_GPR41_LPUART9_STOP_ACK_MASK (0x1U)
#define IOMUXC_LPSR_GPR_GPR41_LPUART9_STOP_ACK_SHIFT (0U)
/*! LPUART9_STOP_ACK - LPUART9 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR41_LPUART9_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_LPUART9_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_LPUART9_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR41_LPUART10_STOP_ACK_MASK (0x2U)
#define IOMUXC_LPSR_GPR_GPR41_LPUART10_STOP_ACK_SHIFT (1U)
/*! LPUART10_STOP_ACK - LPUART10 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR41_LPUART10_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_LPUART10_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_LPUART10_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR41_LPUART11_STOP_ACK_MASK (0x4U)
#define IOMUXC_LPSR_GPR_GPR41_LPUART11_STOP_ACK_SHIFT (2U)
/*! LPUART11_STOP_ACK - LPUART11 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR41_LPUART11_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_LPUART11_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_LPUART11_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR41_LPUART12_STOP_ACK_MASK (0x8U)
#define IOMUXC_LPSR_GPR_GPR41_LPUART12_STOP_ACK_SHIFT (3U)
/*! LPUART12_STOP_ACK - LPUART12 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR41_LPUART12_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_LPUART12_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_LPUART12_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR41_MIC_STOP_ACK_MASK  (0x10U)
#define IOMUXC_LPSR_GPR_GPR41_MIC_STOP_ACK_SHIFT (4U)
/*! MIC_STOP_ACK - MIC stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR41_MIC_STOP_ACK(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_MIC_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_MIC_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR41_PIT1_STOP_ACK_MASK (0x20U)
#define IOMUXC_LPSR_GPR_GPR41_PIT1_STOP_ACK_SHIFT (5U)
/*! PIT1_STOP_ACK - PIT1 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR41_PIT1_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_PIT1_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_PIT1_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR41_PIT2_STOP_ACK_MASK (0x40U)
#define IOMUXC_LPSR_GPR_GPR41_PIT2_STOP_ACK_SHIFT (6U)
/*! PIT2_STOP_ACK - PIT2 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR41_PIT2_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_PIT2_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_PIT2_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR41_SEMC_STOP_ACK_MASK (0x80U)
#define IOMUXC_LPSR_GPR_GPR41_SEMC_STOP_ACK_SHIFT (7U)
/*! SEMC_STOP_ACK - SEMC stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR41_SEMC_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_SEMC_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_SEMC_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR41_SNVS_HP_STOP_ACK_MASK (0x100U)
#define IOMUXC_LPSR_GPR_GPR41_SNVS_HP_STOP_ACK_SHIFT (8U)
/*! SNVS_HP_STOP_ACK - SNVS_HP stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR41_SNVS_HP_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_SNVS_HP_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_SNVS_HP_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR41_SAI1_STOP_ACK_MASK (0x200U)
#define IOMUXC_LPSR_GPR_GPR41_SAI1_STOP_ACK_SHIFT (9U)
/*! SAI1_STOP_ACK - SAI1 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR41_SAI1_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_SAI1_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_SAI1_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR41_SAI2_STOP_ACK_MASK (0x400U)
#define IOMUXC_LPSR_GPR_GPR41_SAI2_STOP_ACK_SHIFT (10U)
/*! SAI2_STOP_ACK - SAI2 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR41_SAI2_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_SAI2_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_SAI2_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR41_SAI3_STOP_ACK_MASK (0x800U)
#define IOMUXC_LPSR_GPR_GPR41_SAI3_STOP_ACK_SHIFT (11U)
/*! SAI3_STOP_ACK - SAI3 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR41_SAI3_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_SAI3_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_SAI3_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR41_SAI4_STOP_ACK_MASK (0x1000U)
#define IOMUXC_LPSR_GPR_GPR41_SAI4_STOP_ACK_SHIFT (12U)
/*! SAI4_STOP_ACK - SAI4 stop acknowledge */
#define IOMUXC_LPSR_GPR_GPR41_SAI4_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_SAI4_STOP_ACK_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_SAI4_STOP_ACK_MASK)

#define IOMUXC_LPSR_GPR_GPR41_FLEXIO1_STOP_ACK_BUS_MASK (0x2000U)
#define IOMUXC_LPSR_GPR_GPR41_FLEXIO1_STOP_ACK_BUS_SHIFT (13U)
/*! FLEXIO1_STOP_ACK_BUS - FLEXIO1 stop acknowledge of bus clock domain */
#define IOMUXC_LPSR_GPR_GPR41_FLEXIO1_STOP_ACK_BUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_FLEXIO1_STOP_ACK_BUS_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_FLEXIO1_STOP_ACK_BUS_MASK)

#define IOMUXC_LPSR_GPR_GPR41_FLEXIO1_STOP_ACK_PER_MASK (0x4000U)
#define IOMUXC_LPSR_GPR_GPR41_FLEXIO1_STOP_ACK_PER_SHIFT (14U)
/*! FLEXIO1_STOP_ACK_PER - FLEXIO1 stop acknowledge of peripheral clock domain */
#define IOMUXC_LPSR_GPR_GPR41_FLEXIO1_STOP_ACK_PER(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_FLEXIO1_STOP_ACK_PER_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_FLEXIO1_STOP_ACK_PER_MASK)

#define IOMUXC_LPSR_GPR_GPR41_FLEXIO2_STOP_ACK_BUS_MASK (0x8000U)
#define IOMUXC_LPSR_GPR_GPR41_FLEXIO2_STOP_ACK_BUS_SHIFT (15U)
/*! FLEXIO2_STOP_ACK_BUS - FLEXIO2 stop acknowledge of bus clock domain */
#define IOMUXC_LPSR_GPR_GPR41_FLEXIO2_STOP_ACK_BUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_FLEXIO2_STOP_ACK_BUS_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_FLEXIO2_STOP_ACK_BUS_MASK)

#define IOMUXC_LPSR_GPR_GPR41_FLEXIO2_STOP_ACK_PER_MASK (0x10000U)
#define IOMUXC_LPSR_GPR_GPR41_FLEXIO2_STOP_ACK_PER_SHIFT (16U)
/*! FLEXIO2_STOP_ACK_PER - FLEXIO2 stop acknowledge of peripheral clock domain */
#define IOMUXC_LPSR_GPR_GPR41_FLEXIO2_STOP_ACK_PER(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_FLEXIO2_STOP_ACK_PER_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_FLEXIO2_STOP_ACK_PER_MASK)

#define IOMUXC_LPSR_GPR_GPR41_ROM_READ_LOCKED_MASK (0x1000000U)
#define IOMUXC_LPSR_GPR_GPR41_ROM_READ_LOCKED_SHIFT (24U)
/*! ROM_READ_LOCKED - ROM read lock status bit */
#define IOMUXC_LPSR_GPR_GPR41_ROM_READ_LOCKED(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_LPSR_GPR_GPR41_ROM_READ_LOCKED_SHIFT)) & IOMUXC_LPSR_GPR_GPR41_ROM_READ_LOCKED_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group IOMUXC_LPSR_GPR_Register_Masks */


/*!
 * @}
 */ /* end of group IOMUXC_LPSR_GPR_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* PERI_IOMUXC_LPSR_GPR_H_ */

