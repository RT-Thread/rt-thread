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
**         CMSIS Peripheral Access Layer for IOMUXC_GPR
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
 * @file PERI_IOMUXC_GPR.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for IOMUXC_GPR
 *
 * CMSIS Peripheral Access Layer for IOMUXC_GPR
 */

#if !defined(PERI_IOMUXC_GPR_H_)
#define PERI_IOMUXC_GPR_H_                       /**< Symbol preventing repeated inclusion */

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
   -- IOMUXC_GPR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_GPR_Peripheral_Access_Layer IOMUXC_GPR Peripheral Access Layer
 * @{
 */

/** IOMUXC_GPR - Register Layout Typedef */
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
       uint8_t RESERVED_0[4];
  __IO uint32_t GPR20;                             /**< GPR20 General Purpose Register, offset: 0x50 */
  __IO uint32_t GPR21;                             /**< GPR21 General Purpose Register, offset: 0x54 */
  __IO uint32_t GPR22;                             /**< GPR22 General Purpose Register, offset: 0x58 */
  __IO uint32_t GPR23;                             /**< GPR23 General Purpose Register, offset: 0x5C */
  __IO uint32_t GPR24;                             /**< GPR24 General Purpose Register, offset: 0x60 */
  __IO uint32_t GPR25;                             /**< GPR25 General Purpose Register, offset: 0x64 */
  __IO uint32_t GPR26;                             /**< GPR26 General Purpose Register, offset: 0x68 */
  __IO uint32_t GPR27;                             /**< GPR27 General Purpose Register, offset: 0x6C */
  __IO uint32_t GPR28;                             /**< GPR28 General Purpose Register, offset: 0x70 */
  __IO uint32_t GPR29;                             /**< GPR29 General Purpose Register, offset: 0x74 */
  __IO uint32_t GPR30;                             /**< GPR30 General Purpose Register, offset: 0x78 */
  __IO uint32_t GPR31;                             /**< GPR31 General Purpose Register, offset: 0x7C */
  __IO uint32_t GPR32;                             /**< GPR32 General Purpose Register, offset: 0x80 */
  __IO uint32_t GPR33;                             /**< GPR33 General Purpose Register, offset: 0x84 */
  __IO uint32_t GPR34;                             /**< GPR34 General Purpose Register, offset: 0x88 */
  __IO uint32_t GPR35;                             /**< GPR35 General Purpose Register, offset: 0x8C */
  __IO uint32_t GPR36;                             /**< GPR36 General Purpose Register, offset: 0x90 */
  __IO uint32_t GPR37;                             /**< GPR37 General Purpose Register, offset: 0x94 */
  __IO uint32_t GPR38;                             /**< GPR38 General Purpose Register, offset: 0x98 */
  __IO uint32_t GPR39;                             /**< GPR39 General Purpose Register, offset: 0x9C */
  __IO uint32_t GPR40;                             /**< GPR40 General Purpose Register, offset: 0xA0 */
  __IO uint32_t GPR41;                             /**< GPR41 General Purpose Register, offset: 0xA4 */
  __IO uint32_t GPR42;                             /**< GPR42 General Purpose Register, offset: 0xA8 */
  __IO uint32_t GPR43;                             /**< GPR43 General Purpose Register, offset: 0xAC */
  __IO uint32_t GPR44;                             /**< GPR44 General Purpose Register, offset: 0xB0 */
  __IO uint32_t GPR45;                             /**< GPR45 General Purpose Register, offset: 0xB4 */
  __IO uint32_t GPR46;                             /**< GPR46 General Purpose Register, offset: 0xB8 */
  __IO uint32_t GPR47;                             /**< GPR47 General Purpose Register, offset: 0xBC */
  __IO uint32_t GPR48;                             /**< GPR48 General Purpose Register, offset: 0xC0 */
  __IO uint32_t GPR49;                             /**< GPR49 General Purpose Register, offset: 0xC4 */
  __IO uint32_t GPR50;                             /**< GPR50 General Purpose Register, offset: 0xC8 */
  __IO uint32_t GPR51;                             /**< GPR51 General Purpose Register, offset: 0xCC */
  __IO uint32_t GPR52;                             /**< GPR52 General Purpose Register, offset: 0xD0 */
  __IO uint32_t GPR53;                             /**< GPR53 General Purpose Register, offset: 0xD4 */
  __IO uint32_t GPR54;                             /**< GPR54 General Purpose Register, offset: 0xD8 */
  __IO uint32_t GPR55;                             /**< GPR55 General Purpose Register, offset: 0xDC */
       uint8_t RESERVED_1[12];
  __IO uint32_t GPR59;                             /**< GPR59 General Purpose Register, offset: 0xEC */
       uint8_t RESERVED_2[8];
  __IO uint32_t GPR62;                             /**< GPR62 General Purpose Register, offset: 0xF8 */
  __I  uint32_t GPR63;                             /**< GPR63 General Purpose Register, offset: 0xFC */
  __IO uint32_t GPR64;                             /**< GPR64 General Purpose Register, offset: 0x100 */
  __IO uint32_t GPR65;                             /**< GPR65 General Purpose Register, offset: 0x104 */
  __IO uint32_t GPR66;                             /**< GPR66 General Purpose Register, offset: 0x108 */
  __IO uint32_t GPR67;                             /**< GPR67 General Purpose Register, offset: 0x10C */
  __IO uint32_t GPR68;                             /**< GPR68 General Purpose Register, offset: 0x110 */
  __IO uint32_t GPR69;                             /**< GPR69 General Purpose Register, offset: 0x114 */
  __IO uint32_t GPR70;                             /**< GPR70 General Purpose Register, offset: 0x118 */
  __IO uint32_t GPR71;                             /**< GPR71 General Purpose Register, offset: 0x11C */
  __IO uint32_t GPR72;                             /**< GPR72 General Purpose Register, offset: 0x120 */
  __IO uint32_t GPR73;                             /**< GPR73 General Purpose Register, offset: 0x124 */
  __IO uint32_t GPR74;                             /**< GPR74 General Purpose Register, offset: 0x128 */
  __I  uint32_t GPR75;                             /**< GPR75 General Purpose Register, offset: 0x12C */
  __I  uint32_t GPR76;                             /**< GPR76 General Purpose Register, offset: 0x130 */
} IOMUXC_GPR_Type;

/* ----------------------------------------------------------------------------
   -- IOMUXC_GPR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_GPR_Register_Masks IOMUXC_GPR Register Masks
 * @{
 */

/*! @name GPR0 - GPR0 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR0_SAI1_MCLK1_SEL_MASK      (0x7U)
#define IOMUXC_GPR_GPR0_SAI1_MCLK1_SEL_SHIFT     (0U)
/*! SAI1_MCLK1_SEL - SAI1 MCLK1 source select */
#define IOMUXC_GPR_GPR0_SAI1_MCLK1_SEL(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_SAI1_MCLK1_SEL_SHIFT)) & IOMUXC_GPR_GPR0_SAI1_MCLK1_SEL_MASK)

#define IOMUXC_GPR_GPR0_SAI1_MCLK2_SEL_MASK      (0x38U)
#define IOMUXC_GPR_GPR0_SAI1_MCLK2_SEL_SHIFT     (3U)
/*! SAI1_MCLK2_SEL - SAI1 MCLK2 source select */
#define IOMUXC_GPR_GPR0_SAI1_MCLK2_SEL(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_SAI1_MCLK2_SEL_SHIFT)) & IOMUXC_GPR_GPR0_SAI1_MCLK2_SEL_MASK)

#define IOMUXC_GPR_GPR0_SAI1_MCLK3_SEL_MASK      (0xC0U)
#define IOMUXC_GPR_GPR0_SAI1_MCLK3_SEL_SHIFT     (6U)
/*! SAI1_MCLK3_SEL - SAI1 MCLK3 source select */
#define IOMUXC_GPR_GPR0_SAI1_MCLK3_SEL(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_SAI1_MCLK3_SEL_SHIFT)) & IOMUXC_GPR_GPR0_SAI1_MCLK3_SEL_MASK)

#define IOMUXC_GPR_GPR0_SAI1_MCLK_DIR_MASK       (0x100U)
#define IOMUXC_GPR_GPR0_SAI1_MCLK_DIR_SHIFT      (8U)
/*! SAI1_MCLK_DIR - SAI1_MCLK signal direction control */
#define IOMUXC_GPR_GPR0_SAI1_MCLK_DIR(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_SAI1_MCLK_DIR_SHIFT)) & IOMUXC_GPR_GPR0_SAI1_MCLK_DIR_MASK)

#define IOMUXC_GPR_GPR0_DWP_MASK                 (0x30000000U)
#define IOMUXC_GPR_GPR0_DWP_SHIFT                (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR0_DWP(x)                   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DWP_SHIFT)) & IOMUXC_GPR_GPR0_DWP_MASK)

#define IOMUXC_GPR_GPR0_DWP_LOCK_MASK            (0xC0000000U)
#define IOMUXC_GPR_GPR0_DWP_LOCK_SHIFT           (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR0_DWP_LOCK(x)              (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR0_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR0_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR1 - GPR1 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR1_SAI2_MCLK3_SEL_MASK      (0x3U)
#define IOMUXC_GPR_GPR1_SAI2_MCLK3_SEL_SHIFT     (0U)
/*! SAI2_MCLK3_SEL - SAI2 MCLK3 source select */
#define IOMUXC_GPR_GPR1_SAI2_MCLK3_SEL(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_SAI2_MCLK3_SEL_SHIFT)) & IOMUXC_GPR_GPR1_SAI2_MCLK3_SEL_MASK)

#define IOMUXC_GPR_GPR1_SAI2_MCLK_DIR_MASK       (0x100U)
#define IOMUXC_GPR_GPR1_SAI2_MCLK_DIR_SHIFT      (8U)
/*! SAI2_MCLK_DIR - SAI2_MCLK signal direction control */
#define IOMUXC_GPR_GPR1_SAI2_MCLK_DIR(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_SAI2_MCLK_DIR_SHIFT)) & IOMUXC_GPR_GPR1_SAI2_MCLK_DIR_MASK)

#define IOMUXC_GPR_GPR1_DWP_MASK                 (0x30000000U)
#define IOMUXC_GPR_GPR1_DWP_SHIFT                (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR1_DWP(x)                   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_DWP_SHIFT)) & IOMUXC_GPR_GPR1_DWP_MASK)

#define IOMUXC_GPR_GPR1_DWP_LOCK_MASK            (0xC0000000U)
#define IOMUXC_GPR_GPR1_DWP_LOCK_SHIFT           (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR1_DWP_LOCK(x)              (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR1_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR1_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR2 - GPR2 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR2_SAI3_MCLK3_SEL_MASK      (0x3U)
#define IOMUXC_GPR_GPR2_SAI3_MCLK3_SEL_SHIFT     (0U)
/*! SAI3_MCLK3_SEL - SAI3 MCLK3 source select */
#define IOMUXC_GPR_GPR2_SAI3_MCLK3_SEL(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_SAI3_MCLK3_SEL_SHIFT)) & IOMUXC_GPR_GPR2_SAI3_MCLK3_SEL_MASK)

#define IOMUXC_GPR_GPR2_SAI3_MCLK_DIR_MASK       (0x100U)
#define IOMUXC_GPR_GPR2_SAI3_MCLK_DIR_SHIFT      (8U)
/*! SAI3_MCLK_DIR - SAI3_MCLK signal direction control */
#define IOMUXC_GPR_GPR2_SAI3_MCLK_DIR(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_SAI3_MCLK_DIR_SHIFT)) & IOMUXC_GPR_GPR2_SAI3_MCLK_DIR_MASK)

#define IOMUXC_GPR_GPR2_SAI4_MCLK_DIR_MASK       (0x200U)
#define IOMUXC_GPR_GPR2_SAI4_MCLK_DIR_SHIFT      (9U)
/*! SAI4_MCLK_DIR - SAI4_MCLK signal direction control */
#define IOMUXC_GPR_GPR2_SAI4_MCLK_DIR(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_SAI4_MCLK_DIR_SHIFT)) & IOMUXC_GPR_GPR2_SAI4_MCLK_DIR_MASK)

#define IOMUXC_GPR_GPR2_DWP_MASK                 (0x30000000U)
#define IOMUXC_GPR_GPR2_DWP_SHIFT                (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR2_DWP(x)                   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_DWP_SHIFT)) & IOMUXC_GPR_GPR2_DWP_MASK)

#define IOMUXC_GPR_GPR2_DWP_LOCK_MASK            (0xC0000000U)
#define IOMUXC_GPR_GPR2_DWP_LOCK_SHIFT           (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR2_DWP_LOCK(x)              (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR2_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR2_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR3 - GPR3 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR3_MQS_CLK_DIV_MASK         (0xFFU)
#define IOMUXC_GPR_GPR3_MQS_CLK_DIV_SHIFT        (0U)
/*! MQS_CLK_DIV - Divider ratio control for mclk from hmclk. */
#define IOMUXC_GPR_GPR3_MQS_CLK_DIV(x)           (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR3_MQS_CLK_DIV_SHIFT)) & IOMUXC_GPR_GPR3_MQS_CLK_DIV_MASK)

#define IOMUXC_GPR_GPR3_MQS_SW_RST_MASK          (0x100U)
#define IOMUXC_GPR_GPR3_MQS_SW_RST_SHIFT         (8U)
/*! MQS_SW_RST - MQS software reset */
#define IOMUXC_GPR_GPR3_MQS_SW_RST(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR3_MQS_SW_RST_SHIFT)) & IOMUXC_GPR_GPR3_MQS_SW_RST_MASK)

#define IOMUXC_GPR_GPR3_MQS_EN_MASK              (0x200U)
#define IOMUXC_GPR_GPR3_MQS_EN_SHIFT             (9U)
/*! MQS_EN - MQS enable */
#define IOMUXC_GPR_GPR3_MQS_EN(x)                (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR3_MQS_EN_SHIFT)) & IOMUXC_GPR_GPR3_MQS_EN_MASK)

#define IOMUXC_GPR_GPR3_MQS_OVERSAMPLE_MASK      (0x400U)
#define IOMUXC_GPR_GPR3_MQS_OVERSAMPLE_SHIFT     (10U)
/*! MQS_OVERSAMPLE - Medium Quality Sound (MQS) Oversample */
#define IOMUXC_GPR_GPR3_MQS_OVERSAMPLE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR3_MQS_OVERSAMPLE_SHIFT)) & IOMUXC_GPR_GPR3_MQS_OVERSAMPLE_MASK)

#define IOMUXC_GPR_GPR3_DWP_MASK                 (0x30000000U)
#define IOMUXC_GPR_GPR3_DWP_SHIFT                (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR3_DWP(x)                   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR3_DWP_SHIFT)) & IOMUXC_GPR_GPR3_DWP_MASK)

#define IOMUXC_GPR_GPR3_DWP_LOCK_MASK            (0xC0000000U)
#define IOMUXC_GPR_GPR3_DWP_LOCK_SHIFT           (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR3_DWP_LOCK(x)              (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR3_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR3_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR4 - GPR4 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR4_ENET_TX_CLK_SEL_MASK     (0x1U)
#define IOMUXC_GPR_GPR4_ENET_TX_CLK_SEL_SHIFT    (0U)
/*! ENET_TX_CLK_SEL - ENET TX_CLK select */
#define IOMUXC_GPR_GPR4_ENET_TX_CLK_SEL(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_ENET_TX_CLK_SEL_SHIFT)) & IOMUXC_GPR_GPR4_ENET_TX_CLK_SEL_MASK)

#define IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR_MASK    (0x2U)
#define IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR_SHIFT   (1U)
/*! ENET_REF_CLK_DIR - ENET_REF_CLK direction control */
#define IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR_SHIFT)) & IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR_MASK)

#define IOMUXC_GPR_GPR4_ENET_TIME_SEL_MASK       (0x4U)
#define IOMUXC_GPR_GPR4_ENET_TIME_SEL_SHIFT      (2U)
/*! ENET_TIME_SEL - ENET master timer source select */
#define IOMUXC_GPR_GPR4_ENET_TIME_SEL(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_ENET_TIME_SEL_SHIFT)) & IOMUXC_GPR_GPR4_ENET_TIME_SEL_MASK)

#define IOMUXC_GPR_GPR4_ENET_EVENT0IN_SEL_MASK   (0x8U)
#define IOMUXC_GPR_GPR4_ENET_EVENT0IN_SEL_SHIFT  (3U)
/*! ENET_EVENT0IN_SEL - ENET ENET_1588_EVENT0_IN source select */
#define IOMUXC_GPR_GPR4_ENET_EVENT0IN_SEL(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_ENET_EVENT0IN_SEL_SHIFT)) & IOMUXC_GPR_GPR4_ENET_EVENT0IN_SEL_MASK)

#define IOMUXC_GPR_GPR4_DWP_MASK                 (0x30000000U)
#define IOMUXC_GPR_GPR4_DWP_SHIFT                (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR4_DWP(x)                   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_DWP_SHIFT)) & IOMUXC_GPR_GPR4_DWP_MASK)

#define IOMUXC_GPR_GPR4_DWP_LOCK_MASK            (0xC0000000U)
#define IOMUXC_GPR_GPR4_DWP_LOCK_SHIFT           (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR4_DWP_LOCK(x)              (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR4_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR4_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR5 - GPR5 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR5_ENET1G_TX_CLK_SEL_MASK   (0x1U)
#define IOMUXC_GPR_GPR5_ENET1G_TX_CLK_SEL_SHIFT  (0U)
/*! ENET1G_TX_CLK_SEL - ENET1G TX_CLK select */
#define IOMUXC_GPR_GPR5_ENET1G_TX_CLK_SEL(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_ENET1G_TX_CLK_SEL_SHIFT)) & IOMUXC_GPR_GPR5_ENET1G_TX_CLK_SEL_MASK)

#define IOMUXC_GPR_GPR5_ENET1G_REF_CLK_DIR_MASK  (0x2U)
#define IOMUXC_GPR_GPR5_ENET1G_REF_CLK_DIR_SHIFT (1U)
/*! ENET1G_REF_CLK_DIR - ENET1G_REF_CLK direction control */
#define IOMUXC_GPR_GPR5_ENET1G_REF_CLK_DIR(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_ENET1G_REF_CLK_DIR_SHIFT)) & IOMUXC_GPR_GPR5_ENET1G_REF_CLK_DIR_MASK)

#define IOMUXC_GPR_GPR5_ENET1G_RGMII_EN_MASK     (0x4U)
#define IOMUXC_GPR_GPR5_ENET1G_RGMII_EN_SHIFT    (2U)
/*! ENET1G_RGMII_EN - ENET1G RGMII TX clock output enable */
#define IOMUXC_GPR_GPR5_ENET1G_RGMII_EN(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_ENET1G_RGMII_EN_SHIFT)) & IOMUXC_GPR_GPR5_ENET1G_RGMII_EN_MASK)

#define IOMUXC_GPR_GPR5_ENET1G_TIME_SEL_MASK     (0x8U)
#define IOMUXC_GPR_GPR5_ENET1G_TIME_SEL_SHIFT    (3U)
/*! ENET1G_TIME_SEL - ENET1G master timer source select */
#define IOMUXC_GPR_GPR5_ENET1G_TIME_SEL(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_ENET1G_TIME_SEL_SHIFT)) & IOMUXC_GPR_GPR5_ENET1G_TIME_SEL_MASK)

#define IOMUXC_GPR_GPR5_ENET1G_EVENT0IN_SEL_MASK (0x10U)
#define IOMUXC_GPR_GPR5_ENET1G_EVENT0IN_SEL_SHIFT (4U)
/*! ENET1G_EVENT0IN_SEL - ENET1G ENET_1588_EVENT0_IN source select */
#define IOMUXC_GPR_GPR5_ENET1G_EVENT0IN_SEL(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_ENET1G_EVENT0IN_SEL_SHIFT)) & IOMUXC_GPR_GPR5_ENET1G_EVENT0IN_SEL_MASK)

#define IOMUXC_GPR_GPR5_DWP_MASK                 (0x30000000U)
#define IOMUXC_GPR_GPR5_DWP_SHIFT                (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR5_DWP(x)                   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_DWP_SHIFT)) & IOMUXC_GPR_GPR5_DWP_MASK)

#define IOMUXC_GPR_GPR5_DWP_LOCK_MASK            (0xC0000000U)
#define IOMUXC_GPR_GPR5_DWP_LOCK_SHIFT           (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR5_DWP_LOCK(x)              (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR5_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR5_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR6 - GPR6 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR6_ENET_QOS_REF_CLK_DIR_MASK (0x1U)
#define IOMUXC_GPR_GPR6_ENET_QOS_REF_CLK_DIR_SHIFT (0U)
/*! ENET_QOS_REF_CLK_DIR - ENET_QOS_REF_CLK direction control */
#define IOMUXC_GPR_GPR6_ENET_QOS_REF_CLK_DIR(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR6_ENET_QOS_REF_CLK_DIR_SHIFT)) & IOMUXC_GPR_GPR6_ENET_QOS_REF_CLK_DIR_MASK)

#define IOMUXC_GPR_GPR6_ENET_QOS_RGMII_EN_MASK   (0x2U)
#define IOMUXC_GPR_GPR6_ENET_QOS_RGMII_EN_SHIFT  (1U)
/*! ENET_QOS_RGMII_EN - ENET_QOS RGMII TX clock output enable */
#define IOMUXC_GPR_GPR6_ENET_QOS_RGMII_EN(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR6_ENET_QOS_RGMII_EN_SHIFT)) & IOMUXC_GPR_GPR6_ENET_QOS_RGMII_EN_MASK)

#define IOMUXC_GPR_GPR6_ENET_QOS_TIME_SEL_MASK   (0x4U)
#define IOMUXC_GPR_GPR6_ENET_QOS_TIME_SEL_SHIFT  (2U)
/*! ENET_QOS_TIME_SEL - ENET_QOS master timer source select */
#define IOMUXC_GPR_GPR6_ENET_QOS_TIME_SEL(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR6_ENET_QOS_TIME_SEL_SHIFT)) & IOMUXC_GPR_GPR6_ENET_QOS_TIME_SEL_MASK)

#define IOMUXC_GPR_GPR6_ENET_QOS_INTF_SEL_MASK   (0x38U)
#define IOMUXC_GPR_GPR6_ENET_QOS_INTF_SEL_SHIFT  (3U)
/*! ENET_QOS_INTF_SEL - ENET_QOS PHY Interface Select */
#define IOMUXC_GPR_GPR6_ENET_QOS_INTF_SEL(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR6_ENET_QOS_INTF_SEL_SHIFT)) & IOMUXC_GPR_GPR6_ENET_QOS_INTF_SEL_MASK)

#define IOMUXC_GPR_GPR6_ENET_QOS_CLKGEN_EN_MASK  (0x40U)
#define IOMUXC_GPR_GPR6_ENET_QOS_CLKGEN_EN_SHIFT (6U)
/*! ENET_QOS_CLKGEN_EN - ENET_QOS clock generator enable */
#define IOMUXC_GPR_GPR6_ENET_QOS_CLKGEN_EN(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR6_ENET_QOS_CLKGEN_EN_SHIFT)) & IOMUXC_GPR_GPR6_ENET_QOS_CLKGEN_EN_MASK)

#define IOMUXC_GPR_GPR6_ENET_QOS_EVENT0IN_SEL_MASK (0x80U)
#define IOMUXC_GPR_GPR6_ENET_QOS_EVENT0IN_SEL_SHIFT (7U)
/*! ENET_QOS_EVENT0IN_SEL - ENET_QOS ENET_1588_EVENT0_IN source select */
#define IOMUXC_GPR_GPR6_ENET_QOS_EVENT0IN_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR6_ENET_QOS_EVENT0IN_SEL_SHIFT)) & IOMUXC_GPR_GPR6_ENET_QOS_EVENT0IN_SEL_MASK)

#define IOMUXC_GPR_GPR6_DWP_MASK                 (0x30000000U)
#define IOMUXC_GPR_GPR6_DWP_SHIFT                (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR6_DWP(x)                   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR6_DWP_SHIFT)) & IOMUXC_GPR_GPR6_DWP_MASK)

#define IOMUXC_GPR_GPR6_DWP_LOCK_MASK            (0xC0000000U)
#define IOMUXC_GPR_GPR6_DWP_LOCK_SHIFT           (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR6_DWP_LOCK(x)              (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR6_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR6_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR7 - GPR7 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR7_GINT_MASK                (0x1U)
#define IOMUXC_GPR_GPR7_GINT_SHIFT               (0U)
/*! GINT - Global interrupt */
#define IOMUXC_GPR_GPR7_GINT(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR7_GINT_SHIFT)) & IOMUXC_GPR_GPR7_GINT_MASK)

#define IOMUXC_GPR_GPR7_DWP_MASK                 (0x30000000U)
#define IOMUXC_GPR_GPR7_DWP_SHIFT                (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR7_DWP(x)                   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR7_DWP_SHIFT)) & IOMUXC_GPR_GPR7_DWP_MASK)

#define IOMUXC_GPR_GPR7_DWP_LOCK_MASK            (0xC0000000U)
#define IOMUXC_GPR_GPR7_DWP_LOCK_SHIFT           (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR7_DWP_LOCK(x)              (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR7_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR7_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR8 - GPR8 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR8_WDOG1_MASK_MASK          (0x1U)
#define IOMUXC_GPR_GPR8_WDOG1_MASK_SHIFT         (0U)
/*! WDOG1_MASK - WDOG1 timeout mask for WDOG_ANY */
#define IOMUXC_GPR_GPR8_WDOG1_MASK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR8_WDOG1_MASK_SHIFT)) & IOMUXC_GPR_GPR8_WDOG1_MASK_MASK)

#define IOMUXC_GPR_GPR8_DWP_MASK                 (0x30000000U)
#define IOMUXC_GPR_GPR8_DWP_SHIFT                (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR8_DWP(x)                   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR8_DWP_SHIFT)) & IOMUXC_GPR_GPR8_DWP_MASK)

#define IOMUXC_GPR_GPR8_DWP_LOCK_MASK            (0xC0000000U)
#define IOMUXC_GPR_GPR8_DWP_LOCK_SHIFT           (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR8_DWP_LOCK(x)              (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR8_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR8_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR9 - GPR9 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR9_WDOG2_MASK_MASK          (0x1U)
#define IOMUXC_GPR_GPR9_WDOG2_MASK_SHIFT         (0U)
/*! WDOG2_MASK - WDOG2 timeout mask for WDOG_ANY */
#define IOMUXC_GPR_GPR9_WDOG2_MASK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR9_WDOG2_MASK_SHIFT)) & IOMUXC_GPR_GPR9_WDOG2_MASK_MASK)

#define IOMUXC_GPR_GPR9_DWP_MASK                 (0x30000000U)
#define IOMUXC_GPR_GPR9_DWP_SHIFT                (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR9_DWP(x)                   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR9_DWP_SHIFT)) & IOMUXC_GPR_GPR9_DWP_MASK)

#define IOMUXC_GPR_GPR9_DWP_LOCK_MASK            (0xC0000000U)
#define IOMUXC_GPR_GPR9_DWP_LOCK_SHIFT           (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR9_DWP_LOCK(x)              (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR9_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR9_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR10 - GPR10 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR10_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR10_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR10_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR10_DWP_SHIFT)) & IOMUXC_GPR_GPR10_DWP_MASK)

#define IOMUXC_GPR_GPR10_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR10_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR10_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR10_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR10_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR11 - GPR11 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR11_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR11_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR11_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR11_DWP_SHIFT)) & IOMUXC_GPR_GPR11_DWP_MASK)

#define IOMUXC_GPR_GPR11_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR11_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR11_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR11_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR11_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR12 - GPR12 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR12_QTIMER1_TMR_CNTS_FREEZE_MASK (0x1U)
#define IOMUXC_GPR_GPR12_QTIMER1_TMR_CNTS_FREEZE_SHIFT (0U)
/*! QTIMER1_TMR_CNTS_FREEZE - QTIMER1 timer counter freeze */
#define IOMUXC_GPR_GPR12_QTIMER1_TMR_CNTS_FREEZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR12_QTIMER1_TMR_CNTS_FREEZE_SHIFT)) & IOMUXC_GPR_GPR12_QTIMER1_TMR_CNTS_FREEZE_MASK)

#define IOMUXC_GPR_GPR12_QTIMER1_TRM0_INPUT_SEL_MASK (0x100U)
#define IOMUXC_GPR_GPR12_QTIMER1_TRM0_INPUT_SEL_SHIFT (8U)
/*! QTIMER1_TRM0_INPUT_SEL - QTIMER1 TMR0 input select */
#define IOMUXC_GPR_GPR12_QTIMER1_TRM0_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR12_QTIMER1_TRM0_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR12_QTIMER1_TRM0_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR12_QTIMER1_TRM1_INPUT_SEL_MASK (0x200U)
#define IOMUXC_GPR_GPR12_QTIMER1_TRM1_INPUT_SEL_SHIFT (9U)
/*! QTIMER1_TRM1_INPUT_SEL - QTIMER1 TMR1 input select */
#define IOMUXC_GPR_GPR12_QTIMER1_TRM1_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR12_QTIMER1_TRM1_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR12_QTIMER1_TRM1_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR12_QTIMER1_TRM2_INPUT_SEL_MASK (0x400U)
#define IOMUXC_GPR_GPR12_QTIMER1_TRM2_INPUT_SEL_SHIFT (10U)
/*! QTIMER1_TRM2_INPUT_SEL - QTIMER1 TMR2 input select */
#define IOMUXC_GPR_GPR12_QTIMER1_TRM2_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR12_QTIMER1_TRM2_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR12_QTIMER1_TRM2_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR12_QTIMER1_TRM3_INPUT_SEL_MASK (0x800U)
#define IOMUXC_GPR_GPR12_QTIMER1_TRM3_INPUT_SEL_SHIFT (11U)
/*! QTIMER1_TRM3_INPUT_SEL - QTIMER1 TMR3 input select */
#define IOMUXC_GPR_GPR12_QTIMER1_TRM3_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR12_QTIMER1_TRM3_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR12_QTIMER1_TRM3_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR12_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR12_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR12_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR12_DWP_SHIFT)) & IOMUXC_GPR_GPR12_DWP_MASK)

#define IOMUXC_GPR_GPR12_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR12_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR12_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR12_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR12_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR13 - GPR13 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR13_QTIMER2_TMR_CNTS_FREEZE_MASK (0x1U)
#define IOMUXC_GPR_GPR13_QTIMER2_TMR_CNTS_FREEZE_SHIFT (0U)
/*! QTIMER2_TMR_CNTS_FREEZE - QTIMER2 timer counter freeze */
#define IOMUXC_GPR_GPR13_QTIMER2_TMR_CNTS_FREEZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR13_QTIMER2_TMR_CNTS_FREEZE_SHIFT)) & IOMUXC_GPR_GPR13_QTIMER2_TMR_CNTS_FREEZE_MASK)

#define IOMUXC_GPR_GPR13_QTIMER2_TRM0_INPUT_SEL_MASK (0x100U)
#define IOMUXC_GPR_GPR13_QTIMER2_TRM0_INPUT_SEL_SHIFT (8U)
/*! QTIMER2_TRM0_INPUT_SEL - QTIMER2 TMR0 input select */
#define IOMUXC_GPR_GPR13_QTIMER2_TRM0_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR13_QTIMER2_TRM0_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR13_QTIMER2_TRM0_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR13_QTIMER2_TRM1_INPUT_SEL_MASK (0x200U)
#define IOMUXC_GPR_GPR13_QTIMER2_TRM1_INPUT_SEL_SHIFT (9U)
/*! QTIMER2_TRM1_INPUT_SEL - QTIMER2 TMR1 input select */
#define IOMUXC_GPR_GPR13_QTIMER2_TRM1_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR13_QTIMER2_TRM1_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR13_QTIMER2_TRM1_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR13_QTIMER2_TRM2_INPUT_SEL_MASK (0x400U)
#define IOMUXC_GPR_GPR13_QTIMER2_TRM2_INPUT_SEL_SHIFT (10U)
/*! QTIMER2_TRM2_INPUT_SEL - QTIMER2 TMR2 input select */
#define IOMUXC_GPR_GPR13_QTIMER2_TRM2_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR13_QTIMER2_TRM2_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR13_QTIMER2_TRM2_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR13_QTIMER2_TRM3_INPUT_SEL_MASK (0x800U)
#define IOMUXC_GPR_GPR13_QTIMER2_TRM3_INPUT_SEL_SHIFT (11U)
/*! QTIMER2_TRM3_INPUT_SEL - QTIMER2 TMR3 input select */
#define IOMUXC_GPR_GPR13_QTIMER2_TRM3_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR13_QTIMER2_TRM3_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR13_QTIMER2_TRM3_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR13_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR13_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR13_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR13_DWP_SHIFT)) & IOMUXC_GPR_GPR13_DWP_MASK)

#define IOMUXC_GPR_GPR13_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR13_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR13_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR13_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR13_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR14 - GPR14 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR14_QTIMER3_TMR_CNTS_FREEZE_MASK (0x1U)
#define IOMUXC_GPR_GPR14_QTIMER3_TMR_CNTS_FREEZE_SHIFT (0U)
/*! QTIMER3_TMR_CNTS_FREEZE - QTIMER3 timer counter freeze */
#define IOMUXC_GPR_GPR14_QTIMER3_TMR_CNTS_FREEZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR14_QTIMER3_TMR_CNTS_FREEZE_SHIFT)) & IOMUXC_GPR_GPR14_QTIMER3_TMR_CNTS_FREEZE_MASK)

#define IOMUXC_GPR_GPR14_QTIMER3_TRM0_INPUT_SEL_MASK (0x100U)
#define IOMUXC_GPR_GPR14_QTIMER3_TRM0_INPUT_SEL_SHIFT (8U)
/*! QTIMER3_TRM0_INPUT_SEL - QTIMER3 TMR0 input select */
#define IOMUXC_GPR_GPR14_QTIMER3_TRM0_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR14_QTIMER3_TRM0_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR14_QTIMER3_TRM0_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR14_QTIMER3_TRM1_INPUT_SEL_MASK (0x200U)
#define IOMUXC_GPR_GPR14_QTIMER3_TRM1_INPUT_SEL_SHIFT (9U)
/*! QTIMER3_TRM1_INPUT_SEL - QTIMER3 TMR1 input select */
#define IOMUXC_GPR_GPR14_QTIMER3_TRM1_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR14_QTIMER3_TRM1_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR14_QTIMER3_TRM1_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR14_QTIMER3_TRM2_INPUT_SEL_MASK (0x400U)
#define IOMUXC_GPR_GPR14_QTIMER3_TRM2_INPUT_SEL_SHIFT (10U)
/*! QTIMER3_TRM2_INPUT_SEL - QTIMER3 TMR2 input select */
#define IOMUXC_GPR_GPR14_QTIMER3_TRM2_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR14_QTIMER3_TRM2_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR14_QTIMER3_TRM2_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR14_QTIMER3_TRM3_INPUT_SEL_MASK (0x800U)
#define IOMUXC_GPR_GPR14_QTIMER3_TRM3_INPUT_SEL_SHIFT (11U)
/*! QTIMER3_TRM3_INPUT_SEL - QTIMER3 TMR3 input select */
#define IOMUXC_GPR_GPR14_QTIMER3_TRM3_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR14_QTIMER3_TRM3_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR14_QTIMER3_TRM3_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR14_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR14_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR14_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR14_DWP_SHIFT)) & IOMUXC_GPR_GPR14_DWP_MASK)

#define IOMUXC_GPR_GPR14_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR14_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR14_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR14_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR14_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR15 - GPR15 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR15_QTIMER4_TMR_CNTS_FREEZE_MASK (0x1U)
#define IOMUXC_GPR_GPR15_QTIMER4_TMR_CNTS_FREEZE_SHIFT (0U)
/*! QTIMER4_TMR_CNTS_FREEZE - QTIMER4 timer counter freeze */
#define IOMUXC_GPR_GPR15_QTIMER4_TMR_CNTS_FREEZE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR15_QTIMER4_TMR_CNTS_FREEZE_SHIFT)) & IOMUXC_GPR_GPR15_QTIMER4_TMR_CNTS_FREEZE_MASK)

#define IOMUXC_GPR_GPR15_QTIMER4_TRM0_INPUT_SEL_MASK (0x100U)
#define IOMUXC_GPR_GPR15_QTIMER4_TRM0_INPUT_SEL_SHIFT (8U)
/*! QTIMER4_TRM0_INPUT_SEL - QTIMER4 TMR0 input select */
#define IOMUXC_GPR_GPR15_QTIMER4_TRM0_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR15_QTIMER4_TRM0_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR15_QTIMER4_TRM0_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR15_QTIMER4_TRM1_INPUT_SEL_MASK (0x200U)
#define IOMUXC_GPR_GPR15_QTIMER4_TRM1_INPUT_SEL_SHIFT (9U)
/*! QTIMER4_TRM1_INPUT_SEL - QTIMER4 TMR1 input select */
#define IOMUXC_GPR_GPR15_QTIMER4_TRM1_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR15_QTIMER4_TRM1_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR15_QTIMER4_TRM1_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR15_QTIMER4_TRM2_INPUT_SEL_MASK (0x400U)
#define IOMUXC_GPR_GPR15_QTIMER4_TRM2_INPUT_SEL_SHIFT (10U)
/*! QTIMER4_TRM2_INPUT_SEL - QTIMER4 TMR2 input select */
#define IOMUXC_GPR_GPR15_QTIMER4_TRM2_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR15_QTIMER4_TRM2_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR15_QTIMER4_TRM2_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR15_QTIMER4_TRM3_INPUT_SEL_MASK (0x800U)
#define IOMUXC_GPR_GPR15_QTIMER4_TRM3_INPUT_SEL_SHIFT (11U)
/*! QTIMER4_TRM3_INPUT_SEL - QTIMER4 TMR3 input select */
#define IOMUXC_GPR_GPR15_QTIMER4_TRM3_INPUT_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR15_QTIMER4_TRM3_INPUT_SEL_SHIFT)) & IOMUXC_GPR_GPR15_QTIMER4_TRM3_INPUT_SEL_MASK)

#define IOMUXC_GPR_GPR15_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR15_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR15_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR15_DWP_SHIFT)) & IOMUXC_GPR_GPR15_DWP_MASK)

#define IOMUXC_GPR_GPR15_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR15_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR15_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR15_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR15_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR16 - GPR16 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR16_FLEXRAM_BANK_CFG_SEL_MASK (0x4U)
#define IOMUXC_GPR_GPR16_FLEXRAM_BANK_CFG_SEL_SHIFT (2U)
/*! FLEXRAM_BANK_CFG_SEL - FlexRAM bank config source select */
#define IOMUXC_GPR_GPR16_FLEXRAM_BANK_CFG_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR16_FLEXRAM_BANK_CFG_SEL_SHIFT)) & IOMUXC_GPR_GPR16_FLEXRAM_BANK_CFG_SEL_MASK)

#define IOMUXC_GPR_GPR16_CM7_FORCE_HCLK_EN_MASK  (0x8U)
#define IOMUXC_GPR_GPR16_CM7_FORCE_HCLK_EN_SHIFT (3U)
/*! CM7_FORCE_HCLK_EN - CM7 platform AHB clock enable */
#define IOMUXC_GPR_GPR16_CM7_FORCE_HCLK_EN(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR16_CM7_FORCE_HCLK_EN_SHIFT)) & IOMUXC_GPR_GPR16_CM7_FORCE_HCLK_EN_MASK)

#define IOMUXC_GPR_GPR16_M7_GPC_SLEEP_SEL_MASK   (0x20U)
#define IOMUXC_GPR_GPR16_M7_GPC_SLEEP_SEL_SHIFT  (5U)
/*! M7_GPC_SLEEP_SEL - CM7 sleep request selection */
#define IOMUXC_GPR_GPR16_M7_GPC_SLEEP_SEL(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR16_M7_GPC_SLEEP_SEL_SHIFT)) & IOMUXC_GPR_GPR16_M7_GPC_SLEEP_SEL_MASK)

#define IOMUXC_GPR_GPR16_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR16_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR16_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR16_DWP_SHIFT)) & IOMUXC_GPR_GPR16_DWP_MASK)

#define IOMUXC_GPR_GPR16_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR16_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR16_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR16_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR16_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR17 - GPR17 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR17_FLEXRAM_BANK_CFG_LOW_MASK (0xFFFFU)
#define IOMUXC_GPR_GPR17_FLEXRAM_BANK_CFG_LOW_SHIFT (0U)
/*! FLEXRAM_BANK_CFG_LOW - FlexRAM bank config value */
#define IOMUXC_GPR_GPR17_FLEXRAM_BANK_CFG_LOW(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR17_FLEXRAM_BANK_CFG_LOW_SHIFT)) & IOMUXC_GPR_GPR17_FLEXRAM_BANK_CFG_LOW_MASK)

#define IOMUXC_GPR_GPR17_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR17_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR17_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR17_DWP_SHIFT)) & IOMUXC_GPR_GPR17_DWP_MASK)

#define IOMUXC_GPR_GPR17_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR17_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR17_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR17_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR17_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR18 - GPR18 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR18_FLEXRAM_BANK_CFG_HIGH_MASK (0xFFFFU)
#define IOMUXC_GPR_GPR18_FLEXRAM_BANK_CFG_HIGH_SHIFT (0U)
/*! FLEXRAM_BANK_CFG_HIGH - FlexRAM bank config value */
#define IOMUXC_GPR_GPR18_FLEXRAM_BANK_CFG_HIGH(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR18_FLEXRAM_BANK_CFG_HIGH_SHIFT)) & IOMUXC_GPR_GPR18_FLEXRAM_BANK_CFG_HIGH_MASK)

#define IOMUXC_GPR_GPR18_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR18_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR18_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR18_DWP_SHIFT)) & IOMUXC_GPR_GPR18_DWP_MASK)

#define IOMUXC_GPR_GPR18_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR18_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR18_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR18_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR18_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR20 - GPR20 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_4_MASK (0x1U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_4_SHIFT (0U)
/*! IOMUXC_XBAR_DIR_SEL_4 - IOMUXC XBAR_INOUT4 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_4(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_4_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_4_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_5_MASK (0x2U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_5_SHIFT (1U)
/*! IOMUXC_XBAR_DIR_SEL_5 - IOMUXC XBAR_INOUT5 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_5(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_5_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_5_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_6_MASK (0x4U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_6_SHIFT (2U)
/*! IOMUXC_XBAR_DIR_SEL_6 - IOMUXC XBAR_INOUT6 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_6(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_6_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_6_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_7_MASK (0x8U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_7_SHIFT (3U)
/*! IOMUXC_XBAR_DIR_SEL_7 - IOMUXC XBAR_INOUT7 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_7(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_7_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_7_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_8_MASK (0x10U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_8_SHIFT (4U)
/*! IOMUXC_XBAR_DIR_SEL_8 - IOMUXC XBAR_INOUT8 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_8(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_8_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_8_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_9_MASK (0x20U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_9_SHIFT (5U)
/*! IOMUXC_XBAR_DIR_SEL_9 - IOMUXC XBAR_INOUT9 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_9(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_9_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_9_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_10_MASK (0x40U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_10_SHIFT (6U)
/*! IOMUXC_XBAR_DIR_SEL_10 - IOMUXC XBAR_INOUT10 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_10(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_10_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_10_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_11_MASK (0x80U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_11_SHIFT (7U)
/*! IOMUXC_XBAR_DIR_SEL_11 - IOMUXC XBAR_INOUT11 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_11(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_11_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_11_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_12_MASK (0x100U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_12_SHIFT (8U)
/*! IOMUXC_XBAR_DIR_SEL_12 - IOMUXC XBAR_INOUT12 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_12(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_12_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_12_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_13_MASK (0x200U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_13_SHIFT (9U)
/*! IOMUXC_XBAR_DIR_SEL_13 - IOMUXC XBAR_INOUT13 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_13(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_13_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_13_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_14_MASK (0x400U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_14_SHIFT (10U)
/*! IOMUXC_XBAR_DIR_SEL_14 - IOMUXC XBAR_INOUT14 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_14(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_14_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_14_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_15_MASK (0x800U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_15_SHIFT (11U)
/*! IOMUXC_XBAR_DIR_SEL_15 - IOMUXC XBAR_INOUT15 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_15(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_15_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_15_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_16_MASK (0x1000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_16_SHIFT (12U)
/*! IOMUXC_XBAR_DIR_SEL_16 - IOMUXC XBAR_INOUT16 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_16(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_16_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_16_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_17_MASK (0x2000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_17_SHIFT (13U)
/*! IOMUXC_XBAR_DIR_SEL_17 - IOMUXC XBAR_INOUT17 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_17(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_17_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_17_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_18_MASK (0x4000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_18_SHIFT (14U)
/*! IOMUXC_XBAR_DIR_SEL_18 - IOMUXC XBAR_INOUT18 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_18(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_18_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_18_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_19_MASK (0x8000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_19_SHIFT (15U)
/*! IOMUXC_XBAR_DIR_SEL_19 - IOMUXC XBAR_INOUT19 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_19(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_19_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_19_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_20_MASK (0x10000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_20_SHIFT (16U)
/*! IOMUXC_XBAR_DIR_SEL_20 - IOMUXC XBAR_INOUT20 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_20(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_20_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_20_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_21_MASK (0x20000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_21_SHIFT (17U)
/*! IOMUXC_XBAR_DIR_SEL_21 - IOMUXC XBAR_INOUT21 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_21(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_21_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_21_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_22_MASK (0x40000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_22_SHIFT (18U)
/*! IOMUXC_XBAR_DIR_SEL_22 - IOMUXC XBAR_INOUT22 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_22(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_22_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_22_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_23_MASK (0x80000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_23_SHIFT (19U)
/*! IOMUXC_XBAR_DIR_SEL_23 - IOMUXC XBAR_INOUT23 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_23(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_23_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_23_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_24_MASK (0x100000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_24_SHIFT (20U)
/*! IOMUXC_XBAR_DIR_SEL_24 - IOMUXC XBAR_INOUT24 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_24(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_24_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_24_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_25_MASK (0x200000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_25_SHIFT (21U)
/*! IOMUXC_XBAR_DIR_SEL_25 - IOMUXC XBAR_INOUT25 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_25(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_25_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_25_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_26_MASK (0x400000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_26_SHIFT (22U)
/*! IOMUXC_XBAR_DIR_SEL_26 - IOMUXC XBAR_INOUT26 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_26(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_26_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_26_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_27_MASK (0x800000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_27_SHIFT (23U)
/*! IOMUXC_XBAR_DIR_SEL_27 - IOMUXC XBAR_INOUT27 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_27(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_27_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_27_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_28_MASK (0x1000000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_28_SHIFT (24U)
/*! IOMUXC_XBAR_DIR_SEL_28 - IOMUXC XBAR_INOUT28 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_28(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_28_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_28_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_29_MASK (0x2000000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_29_SHIFT (25U)
/*! IOMUXC_XBAR_DIR_SEL_29 - IOMUXC XBAR_INOUT29 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_29(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_29_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_29_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_30_MASK (0x4000000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_30_SHIFT (26U)
/*! IOMUXC_XBAR_DIR_SEL_30 - IOMUXC XBAR_INOUT30 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_30(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_30_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_30_MASK)

#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_31_MASK (0x8000000U)
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_31_SHIFT (27U)
/*! IOMUXC_XBAR_DIR_SEL_31 - IOMUXC XBAR_INOUT31 function direction select */
#define IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_31(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_31_SHIFT)) & IOMUXC_GPR_GPR20_IOMUXC_XBAR_DIR_SEL_31_MASK)

#define IOMUXC_GPR_GPR20_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR20_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR20_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_DWP_SHIFT)) & IOMUXC_GPR_GPR20_DWP_MASK)

#define IOMUXC_GPR_GPR20_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR20_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR20_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR20_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR20_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR21 - GPR21 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_32_MASK (0x1U)
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_32_SHIFT (0U)
/*! IOMUXC_XBAR_DIR_SEL_32 - IOMUXC XBAR_INOUT32 function direction select */
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_32(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_32_SHIFT)) & IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_32_MASK)

#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_33_MASK (0x2U)
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_33_SHIFT (1U)
/*! IOMUXC_XBAR_DIR_SEL_33 - IOMUXC XBAR_INOUT33 function direction select */
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_33(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_33_SHIFT)) & IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_33_MASK)

#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_34_MASK (0x4U)
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_34_SHIFT (2U)
/*! IOMUXC_XBAR_DIR_SEL_34 - IOMUXC XBAR_INOUT34 function direction select */
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_34(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_34_SHIFT)) & IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_34_MASK)

#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_35_MASK (0x8U)
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_35_SHIFT (3U)
/*! IOMUXC_XBAR_DIR_SEL_35 - IOMUXC XBAR_INOUT35 function direction select */
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_35(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_35_SHIFT)) & IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_35_MASK)

#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_36_MASK (0x10U)
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_36_SHIFT (4U)
/*! IOMUXC_XBAR_DIR_SEL_36 - IOMUXC XBAR_INOUT36 function direction select */
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_36(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_36_SHIFT)) & IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_36_MASK)

#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_37_MASK (0x20U)
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_37_SHIFT (5U)
/*! IOMUXC_XBAR_DIR_SEL_37 - IOMUXC XBAR_INOUT37 function direction select */
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_37(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_37_SHIFT)) & IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_37_MASK)

#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_38_MASK (0x40U)
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_38_SHIFT (6U)
/*! IOMUXC_XBAR_DIR_SEL_38 - IOMUXC XBAR_INOUT38 function direction select */
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_38(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_38_SHIFT)) & IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_38_MASK)

#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_39_MASK (0x80U)
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_39_SHIFT (7U)
/*! IOMUXC_XBAR_DIR_SEL_39 - IOMUXC XBAR_INOUT39 function direction select */
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_39(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_39_SHIFT)) & IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_39_MASK)

#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_40_MASK (0x100U)
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_40_SHIFT (8U)
/*! IOMUXC_XBAR_DIR_SEL_40 - IOMUXC XBAR_INOUT40 function direction select */
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_40(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_40_SHIFT)) & IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_40_MASK)

#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_41_MASK (0x200U)
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_41_SHIFT (9U)
/*! IOMUXC_XBAR_DIR_SEL_41 - IOMUXC XBAR_INOUT41 function direction select */
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_41(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_41_SHIFT)) & IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_41_MASK)

#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_42_MASK (0x400U)
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_42_SHIFT (10U)
/*! IOMUXC_XBAR_DIR_SEL_42 - IOMUXC XBAR_INOUT42 function direction select */
#define IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_42(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_42_SHIFT)) & IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_42_MASK)

#define IOMUXC_GPR_GPR21_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR21_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR21_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR21_DWP_SHIFT)) & IOMUXC_GPR_GPR21_DWP_MASK)

#define IOMUXC_GPR_GPR21_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR21_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR21_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR21_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR21_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR22 - GPR22 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR22_REF_1M_CLK_GPT1_MASK    (0x1U)
#define IOMUXC_GPR_GPR22_REF_1M_CLK_GPT1_SHIFT   (0U)
/*! REF_1M_CLK_GPT1 - GPT1 1 MHz clock source select */
#define IOMUXC_GPR_GPR22_REF_1M_CLK_GPT1(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR22_REF_1M_CLK_GPT1_SHIFT)) & IOMUXC_GPR_GPR22_REF_1M_CLK_GPT1_MASK)

#define IOMUXC_GPR_GPR22_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR22_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR22_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR22_DWP_SHIFT)) & IOMUXC_GPR_GPR22_DWP_MASK)

#define IOMUXC_GPR_GPR22_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR22_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR22_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR22_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR22_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR23 - GPR23 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR23_REF_1M_CLK_GPT2_MASK    (0x1U)
#define IOMUXC_GPR_GPR23_REF_1M_CLK_GPT2_SHIFT   (0U)
/*! REF_1M_CLK_GPT2 - GPT2 1 MHz clock source select */
#define IOMUXC_GPR_GPR23_REF_1M_CLK_GPT2(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR23_REF_1M_CLK_GPT2_SHIFT)) & IOMUXC_GPR_GPR23_REF_1M_CLK_GPT2_MASK)

#define IOMUXC_GPR_GPR23_GPT2_CAPIN1_SEL_MASK    (0x2U)
#define IOMUXC_GPR_GPR23_GPT2_CAPIN1_SEL_SHIFT   (1U)
/*! GPT2_CAPIN1_SEL - GPT2 input capture channel 1 source select */
#define IOMUXC_GPR_GPR23_GPT2_CAPIN1_SEL(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR23_GPT2_CAPIN1_SEL_SHIFT)) & IOMUXC_GPR_GPR23_GPT2_CAPIN1_SEL_MASK)

#define IOMUXC_GPR_GPR23_GPT2_CAPIN2_SEL_MASK    (0x4U)
#define IOMUXC_GPR_GPR23_GPT2_CAPIN2_SEL_SHIFT   (2U)
/*! GPT2_CAPIN2_SEL - GPT2 input capture channel 2 source select */
#define IOMUXC_GPR_GPR23_GPT2_CAPIN2_SEL(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR23_GPT2_CAPIN2_SEL_SHIFT)) & IOMUXC_GPR_GPR23_GPT2_CAPIN2_SEL_MASK)

#define IOMUXC_GPR_GPR23_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR23_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR23_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR23_DWP_SHIFT)) & IOMUXC_GPR_GPR23_DWP_MASK)

#define IOMUXC_GPR_GPR23_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR23_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR23_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR23_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR23_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR24 - GPR24 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR24_REF_1M_CLK_GPT3_MASK    (0x1U)
#define IOMUXC_GPR_GPR24_REF_1M_CLK_GPT3_SHIFT   (0U)
/*! REF_1M_CLK_GPT3 - GPT3 1 MHz clock source select */
#define IOMUXC_GPR_GPR24_REF_1M_CLK_GPT3(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR24_REF_1M_CLK_GPT3_SHIFT)) & IOMUXC_GPR_GPR24_REF_1M_CLK_GPT3_MASK)

#define IOMUXC_GPR_GPR24_GPT3_CAPIN1_SEL_MASK    (0x2U)
#define IOMUXC_GPR_GPR24_GPT3_CAPIN1_SEL_SHIFT   (1U)
/*! GPT3_CAPIN1_SEL - GPT3 input capture channel 1 source select */
#define IOMUXC_GPR_GPR24_GPT3_CAPIN1_SEL(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR24_GPT3_CAPIN1_SEL_SHIFT)) & IOMUXC_GPR_GPR24_GPT3_CAPIN1_SEL_MASK)

#define IOMUXC_GPR_GPR24_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR24_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR24_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR24_DWP_SHIFT)) & IOMUXC_GPR_GPR24_DWP_MASK)

#define IOMUXC_GPR_GPR24_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR24_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR24_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR24_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR24_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR25 - GPR25 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR25_REF_1M_CLK_GPT4_MASK    (0x1U)
#define IOMUXC_GPR_GPR25_REF_1M_CLK_GPT4_SHIFT   (0U)
/*! REF_1M_CLK_GPT4 - GPT4 1 MHz clock source select */
#define IOMUXC_GPR_GPR25_REF_1M_CLK_GPT4(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR25_REF_1M_CLK_GPT4_SHIFT)) & IOMUXC_GPR_GPR25_REF_1M_CLK_GPT4_MASK)

#define IOMUXC_GPR_GPR25_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR25_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR25_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR25_DWP_SHIFT)) & IOMUXC_GPR_GPR25_DWP_MASK)

#define IOMUXC_GPR_GPR25_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR25_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR25_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR25_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR25_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR26 - GPR26 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR26_REF_1M_CLK_GPT5_MASK    (0x1U)
#define IOMUXC_GPR_GPR26_REF_1M_CLK_GPT5_SHIFT   (0U)
/*! REF_1M_CLK_GPT5 - GPT5 1 MHz clock source select */
#define IOMUXC_GPR_GPR26_REF_1M_CLK_GPT5(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR26_REF_1M_CLK_GPT5_SHIFT)) & IOMUXC_GPR_GPR26_REF_1M_CLK_GPT5_MASK)

#define IOMUXC_GPR_GPR26_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR26_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR26_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR26_DWP_SHIFT)) & IOMUXC_GPR_GPR26_DWP_MASK)

#define IOMUXC_GPR_GPR26_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR26_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR26_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR26_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR26_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR27 - GPR27 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR27_REF_1M_CLK_GPT6_MASK    (0x1U)
#define IOMUXC_GPR_GPR27_REF_1M_CLK_GPT6_SHIFT   (0U)
/*! REF_1M_CLK_GPT6 - GPT6 1 MHz clock source select */
#define IOMUXC_GPR_GPR27_REF_1M_CLK_GPT6(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR27_REF_1M_CLK_GPT6_SHIFT)) & IOMUXC_GPR_GPR27_REF_1M_CLK_GPT6_MASK)

#define IOMUXC_GPR_GPR27_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR27_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR27_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR27_DWP_SHIFT)) & IOMUXC_GPR_GPR27_DWP_MASK)

#define IOMUXC_GPR_GPR27_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR27_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR27_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR27_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR27_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR28 - GPR28 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR28_ARCACHE_USDHC_MASK      (0x1U)
#define IOMUXC_GPR_GPR28_ARCACHE_USDHC_SHIFT     (0U)
/*! ARCACHE_USDHC - uSDHC block cacheable attribute value of AXI read transactions */
#define IOMUXC_GPR_GPR28_ARCACHE_USDHC(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR28_ARCACHE_USDHC_SHIFT)) & IOMUXC_GPR_GPR28_ARCACHE_USDHC_MASK)

#define IOMUXC_GPR_GPR28_AWCACHE_USDHC_MASK      (0x2U)
#define IOMUXC_GPR_GPR28_AWCACHE_USDHC_SHIFT     (1U)
/*! AWCACHE_USDHC - uSDHC block cacheable attribute value of AXI write transactions */
#define IOMUXC_GPR_GPR28_AWCACHE_USDHC(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR28_AWCACHE_USDHC_SHIFT)) & IOMUXC_GPR_GPR28_AWCACHE_USDHC_MASK)

#define IOMUXC_GPR_GPR28_CACHE_ENET1G_MASK       (0x20U)
#define IOMUXC_GPR_GPR28_CACHE_ENET1G_SHIFT      (5U)
#define IOMUXC_GPR_GPR28_CACHE_ENET1G(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR28_CACHE_ENET1G_SHIFT)) & IOMUXC_GPR_GPR28_CACHE_ENET1G_MASK)

#define IOMUXC_GPR_GPR28_CACHE_ENET_MASK         (0x80U)
#define IOMUXC_GPR_GPR28_CACHE_ENET_SHIFT        (7U)
/*! CACHE_ENET - ENET block cacheable attribute value of AXI transactions */
#define IOMUXC_GPR_GPR28_CACHE_ENET(x)           (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR28_CACHE_ENET_SHIFT)) & IOMUXC_GPR_GPR28_CACHE_ENET_MASK)

#define IOMUXC_GPR_GPR28_CACHE_USB_MASK          (0x2000U)
#define IOMUXC_GPR_GPR28_CACHE_USB_SHIFT         (13U)
/*! CACHE_USB - USB block cacheable attribute value of AXI transactions */
#define IOMUXC_GPR_GPR28_CACHE_USB(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR28_CACHE_USB_SHIFT)) & IOMUXC_GPR_GPR28_CACHE_USB_MASK)

#define IOMUXC_GPR_GPR28_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR28_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR28_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR28_DWP_SHIFT)) & IOMUXC_GPR_GPR28_DWP_MASK)

#define IOMUXC_GPR_GPR28_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR28_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR28_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR28_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR28_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR29 - GPR29 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR29_USBPHY1_IPG_CLK_ACTIVE_MASK (0x1U)
#define IOMUXC_GPR_GPR29_USBPHY1_IPG_CLK_ACTIVE_SHIFT (0U)
/*! USBPHY1_IPG_CLK_ACTIVE - USBPHY1 register access clock enable */
#define IOMUXC_GPR_GPR29_USBPHY1_IPG_CLK_ACTIVE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR29_USBPHY1_IPG_CLK_ACTIVE_SHIFT)) & IOMUXC_GPR_GPR29_USBPHY1_IPG_CLK_ACTIVE_MASK)

#define IOMUXC_GPR_GPR29_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR29_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR29_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR29_DWP_SHIFT)) & IOMUXC_GPR_GPR29_DWP_MASK)

#define IOMUXC_GPR_GPR29_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR29_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR29_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR29_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR29_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR30 - GPR30 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR30_USBPHY2_IPG_CLK_ACTIVE_MASK (0x1U)
#define IOMUXC_GPR_GPR30_USBPHY2_IPG_CLK_ACTIVE_SHIFT (0U)
/*! USBPHY2_IPG_CLK_ACTIVE - USBPHY2 register access clock enable */
#define IOMUXC_GPR_GPR30_USBPHY2_IPG_CLK_ACTIVE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR30_USBPHY2_IPG_CLK_ACTIVE_SHIFT)) & IOMUXC_GPR_GPR30_USBPHY2_IPG_CLK_ACTIVE_MASK)

#define IOMUXC_GPR_GPR30_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR30_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR30_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR30_DWP_SHIFT)) & IOMUXC_GPR_GPR30_DWP_MASK)

#define IOMUXC_GPR_GPR30_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR30_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR30_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR30_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR30_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR31 - GPR31 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR31_RMW2_WAIT_BVALID_CPL_MASK (0x1U)
#define IOMUXC_GPR_GPR31_RMW2_WAIT_BVALID_CPL_SHIFT (0U)
/*! RMW2_WAIT_BVALID_CPL - OCRAM M7 RMW wait enable */
#define IOMUXC_GPR_GPR31_RMW2_WAIT_BVALID_CPL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR31_RMW2_WAIT_BVALID_CPL_SHIFT)) & IOMUXC_GPR_GPR31_RMW2_WAIT_BVALID_CPL_MASK)

#define IOMUXC_GPR_GPR31_OCRAM_M7_CLK_GATING_MASK (0x4U)
#define IOMUXC_GPR_GPR31_OCRAM_M7_CLK_GATING_SHIFT (2U)
/*! OCRAM_M7_CLK_GATING - OCRAM M7 clock gating enable */
#define IOMUXC_GPR_GPR31_OCRAM_M7_CLK_GATING(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR31_OCRAM_M7_CLK_GATING_SHIFT)) & IOMUXC_GPR_GPR31_OCRAM_M7_CLK_GATING_MASK)

#define IOMUXC_GPR_GPR31_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR31_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR31_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR31_DWP_SHIFT)) & IOMUXC_GPR_GPR31_DWP_MASK)

#define IOMUXC_GPR_GPR31_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR31_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR31_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR31_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR31_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR32 - GPR32 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR32_RMW1_WAIT_BVALID_CPL_MASK (0x1U)
#define IOMUXC_GPR_GPR32_RMW1_WAIT_BVALID_CPL_SHIFT (0U)
/*! RMW1_WAIT_BVALID_CPL - OCRAM1 RMW wait enable */
#define IOMUXC_GPR_GPR32_RMW1_WAIT_BVALID_CPL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR32_RMW1_WAIT_BVALID_CPL_SHIFT)) & IOMUXC_GPR_GPR32_RMW1_WAIT_BVALID_CPL_MASK)

#define IOMUXC_GPR_GPR32_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR32_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR32_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR32_DWP_SHIFT)) & IOMUXC_GPR_GPR32_DWP_MASK)

#define IOMUXC_GPR_GPR32_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR32_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR32_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR32_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR32_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR33 - GPR33 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR33_RMW2_WAIT_BVALID_CPL_MASK (0x1U)
#define IOMUXC_GPR_GPR33_RMW2_WAIT_BVALID_CPL_SHIFT (0U)
/*! RMW2_WAIT_BVALID_CPL - OCRAM2 RMW wait enable */
#define IOMUXC_GPR_GPR33_RMW2_WAIT_BVALID_CPL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR33_RMW2_WAIT_BVALID_CPL_SHIFT)) & IOMUXC_GPR_GPR33_RMW2_WAIT_BVALID_CPL_MASK)

#define IOMUXC_GPR_GPR33_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR33_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR33_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR33_DWP_SHIFT)) & IOMUXC_GPR_GPR33_DWP_MASK)

#define IOMUXC_GPR_GPR33_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR33_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR33_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR33_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR33_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR34 - GPR34 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR34_XECC_FLEXSPI1_WAIT_BVALID_CPL_MASK (0x1U)
#define IOMUXC_GPR_GPR34_XECC_FLEXSPI1_WAIT_BVALID_CPL_SHIFT (0U)
/*! XECC_FLEXSPI1_WAIT_BVALID_CPL - XECC_FLEXSPI1 RMW wait enable */
#define IOMUXC_GPR_GPR34_XECC_FLEXSPI1_WAIT_BVALID_CPL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR34_XECC_FLEXSPI1_WAIT_BVALID_CPL_SHIFT)) & IOMUXC_GPR_GPR34_XECC_FLEXSPI1_WAIT_BVALID_CPL_MASK)

#define IOMUXC_GPR_GPR34_FLEXSPI1_OTFAD_EN_MASK  (0x2U)
#define IOMUXC_GPR_GPR34_FLEXSPI1_OTFAD_EN_SHIFT (1U)
/*! FLEXSPI1_OTFAD_EN - FlexSPI1 OTFAD enable */
#define IOMUXC_GPR_GPR34_FLEXSPI1_OTFAD_EN(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR34_FLEXSPI1_OTFAD_EN_SHIFT)) & IOMUXC_GPR_GPR34_FLEXSPI1_OTFAD_EN_MASK)

#define IOMUXC_GPR_GPR34_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR34_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR34_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR34_DWP_SHIFT)) & IOMUXC_GPR_GPR34_DWP_MASK)

#define IOMUXC_GPR_GPR34_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR34_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR34_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR34_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR34_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR35 - GPR35 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR35_XECC_FLEXSPI2_WAIT_BVALID_CPL_MASK (0x1U)
#define IOMUXC_GPR_GPR35_XECC_FLEXSPI2_WAIT_BVALID_CPL_SHIFT (0U)
/*! XECC_FLEXSPI2_WAIT_BVALID_CPL - XECC_FLEXSPI2 RMW wait enable */
#define IOMUXC_GPR_GPR35_XECC_FLEXSPI2_WAIT_BVALID_CPL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR35_XECC_FLEXSPI2_WAIT_BVALID_CPL_SHIFT)) & IOMUXC_GPR_GPR35_XECC_FLEXSPI2_WAIT_BVALID_CPL_MASK)

#define IOMUXC_GPR_GPR35_FLEXSPI2_OTFAD_EN_MASK  (0x2U)
#define IOMUXC_GPR_GPR35_FLEXSPI2_OTFAD_EN_SHIFT (1U)
/*! FLEXSPI2_OTFAD_EN - FlexSPI2 OTFAD enable */
#define IOMUXC_GPR_GPR35_FLEXSPI2_OTFAD_EN(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR35_FLEXSPI2_OTFAD_EN_SHIFT)) & IOMUXC_GPR_GPR35_FLEXSPI2_OTFAD_EN_MASK)

#define IOMUXC_GPR_GPR35_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR35_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR35_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR35_DWP_SHIFT)) & IOMUXC_GPR_GPR35_DWP_MASK)

#define IOMUXC_GPR_GPR35_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR35_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR35_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR35_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR35_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR36 - GPR36 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR36_XECC_SEMC_WAIT_BVALID_CPL_MASK (0x1U)
#define IOMUXC_GPR_GPR36_XECC_SEMC_WAIT_BVALID_CPL_SHIFT (0U)
/*! XECC_SEMC_WAIT_BVALID_CPL - XECC_SEMC RMW wait enable */
#define IOMUXC_GPR_GPR36_XECC_SEMC_WAIT_BVALID_CPL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR36_XECC_SEMC_WAIT_BVALID_CPL_SHIFT)) & IOMUXC_GPR_GPR36_XECC_SEMC_WAIT_BVALID_CPL_MASK)

#define IOMUXC_GPR_GPR36_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR36_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR36_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR36_DWP_SHIFT)) & IOMUXC_GPR_GPR36_DWP_MASK)

#define IOMUXC_GPR_GPR36_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR36_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR36_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR36_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR36_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR37 - GPR37 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR37_NIDEN_MASK              (0x1U)
#define IOMUXC_GPR_GPR37_NIDEN_SHIFT             (0U)
/*! NIDEN - ARM non-secure (non-invasive) debug enable */
#define IOMUXC_GPR_GPR37_NIDEN(x)                (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR37_NIDEN_SHIFT)) & IOMUXC_GPR_GPR37_NIDEN_MASK)

#define IOMUXC_GPR_GPR37_DBG_EN_MASK             (0x2U)
#define IOMUXC_GPR_GPR37_DBG_EN_SHIFT            (1U)
/*! DBG_EN - ARM invasive debug enable */
#define IOMUXC_GPR_GPR37_DBG_EN(x)               (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR37_DBG_EN_SHIFT)) & IOMUXC_GPR_GPR37_DBG_EN_MASK)

#define IOMUXC_GPR_GPR37_EXC_MON_MASK            (0x8U)
#define IOMUXC_GPR_GPR37_EXC_MON_SHIFT           (3U)
/*! EXC_MON - Exclusive monitor response select of illegal command */
#define IOMUXC_GPR_GPR37_EXC_MON(x)              (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR37_EXC_MON_SHIFT)) & IOMUXC_GPR_GPR37_EXC_MON_MASK)

#define IOMUXC_GPR_GPR37_M7_DBG_ACK_MASK_MASK    (0x20U)
#define IOMUXC_GPR_GPR37_M7_DBG_ACK_MASK_SHIFT   (5U)
/*! M7_DBG_ACK_MASK - CM7 debug halt mask */
#define IOMUXC_GPR_GPR37_M7_DBG_ACK_MASK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR37_M7_DBG_ACK_MASK_SHIFT)) & IOMUXC_GPR_GPR37_M7_DBG_ACK_MASK_MASK)

#define IOMUXC_GPR_GPR37_M4_DBG_ACK_MASK_MASK    (0x40U)
#define IOMUXC_GPR_GPR37_M4_DBG_ACK_MASK_SHIFT   (6U)
/*! M4_DBG_ACK_MASK - CM4 debug halt mask */
#define IOMUXC_GPR_GPR37_M4_DBG_ACK_MASK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR37_M4_DBG_ACK_MASK_SHIFT)) & IOMUXC_GPR_GPR37_M4_DBG_ACK_MASK_MASK)

#define IOMUXC_GPR_GPR37_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR37_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR37_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR37_DWP_SHIFT)) & IOMUXC_GPR_GPR37_DWP_MASK)

#define IOMUXC_GPR_GPR37_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR37_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR37_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR37_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR37_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR38 - GPR38 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR38_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR38_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR38_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR38_DWP_SHIFT)) & IOMUXC_GPR_GPR38_DWP_MASK)

#define IOMUXC_GPR_GPR38_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR38_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR38_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR38_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR38_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR39 - GPR39 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR39_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR39_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR39_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR39_DWP_SHIFT)) & IOMUXC_GPR_GPR39_DWP_MASK)

#define IOMUXC_GPR_GPR39_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR39_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR39_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR39_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR39_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR40 - GPR40 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR40_GPIO_MUX2_GPIO_SEL_LOW_MASK (0xFFFFU)
#define IOMUXC_GPR_GPR40_GPIO_MUX2_GPIO_SEL_LOW_SHIFT (0U)
/*! GPIO_MUX2_GPIO_SEL_LOW - GPIO2 and CM7_GPIO2 share same IO MUX function, GPIO_MUX2 selects one GPIO function. */
#define IOMUXC_GPR_GPR40_GPIO_MUX2_GPIO_SEL_LOW(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR40_GPIO_MUX2_GPIO_SEL_LOW_SHIFT)) & IOMUXC_GPR_GPR40_GPIO_MUX2_GPIO_SEL_LOW_MASK)

#define IOMUXC_GPR_GPR40_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR40_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR40_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR40_DWP_SHIFT)) & IOMUXC_GPR_GPR40_DWP_MASK)

#define IOMUXC_GPR_GPR40_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR40_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR40_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR40_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR40_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR41 - GPR41 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR41_GPIO_MUX2_GPIO_SEL_HIGH_MASK (0xFFFFU)
#define IOMUXC_GPR_GPR41_GPIO_MUX2_GPIO_SEL_HIGH_SHIFT (0U)
/*! GPIO_MUX2_GPIO_SEL_HIGH - GPIO2 and CM7_GPIO2 share same IO MUX function, GPIO_MUX2 selects one GPIO function. */
#define IOMUXC_GPR_GPR41_GPIO_MUX2_GPIO_SEL_HIGH(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR41_GPIO_MUX2_GPIO_SEL_HIGH_SHIFT)) & IOMUXC_GPR_GPR41_GPIO_MUX2_GPIO_SEL_HIGH_MASK)

#define IOMUXC_GPR_GPR41_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR41_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR41_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR41_DWP_SHIFT)) & IOMUXC_GPR_GPR41_DWP_MASK)

#define IOMUXC_GPR_GPR41_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR41_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR41_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR41_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR41_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR42 - GPR42 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR42_GPIO_MUX3_GPIO_SEL_LOW_MASK (0xFFFFU)
#define IOMUXC_GPR_GPR42_GPIO_MUX3_GPIO_SEL_LOW_SHIFT (0U)
/*! GPIO_MUX3_GPIO_SEL_LOW - GPIO3 and CM7_GPIO3 share same IO MUX function, GPIO_MUX3 selects one GPIO function. */
#define IOMUXC_GPR_GPR42_GPIO_MUX3_GPIO_SEL_LOW(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR42_GPIO_MUX3_GPIO_SEL_LOW_SHIFT)) & IOMUXC_GPR_GPR42_GPIO_MUX3_GPIO_SEL_LOW_MASK)

#define IOMUXC_GPR_GPR42_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR42_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR42_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR42_DWP_SHIFT)) & IOMUXC_GPR_GPR42_DWP_MASK)

#define IOMUXC_GPR_GPR42_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR42_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR42_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR42_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR42_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR43 - GPR43 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR43_GPIO_MUX3_GPIO_SEL_HIGH_MASK (0xFFFFU)
#define IOMUXC_GPR_GPR43_GPIO_MUX3_GPIO_SEL_HIGH_SHIFT (0U)
/*! GPIO_MUX3_GPIO_SEL_HIGH - GPIO3 and CM7_GPIO3 share same IO MUX function, GPIO_MUX3 selects one GPIO function. */
#define IOMUXC_GPR_GPR43_GPIO_MUX3_GPIO_SEL_HIGH(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR43_GPIO_MUX3_GPIO_SEL_HIGH_SHIFT)) & IOMUXC_GPR_GPR43_GPIO_MUX3_GPIO_SEL_HIGH_MASK)

#define IOMUXC_GPR_GPR43_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR43_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR43_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR43_DWP_SHIFT)) & IOMUXC_GPR_GPR43_DWP_MASK)

#define IOMUXC_GPR_GPR43_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR43_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR43_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR43_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR43_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR44 - GPR44 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR44_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR44_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR44_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR44_DWP_SHIFT)) & IOMUXC_GPR_GPR44_DWP_MASK)

#define IOMUXC_GPR_GPR44_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR44_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR44_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR44_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR44_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR45 - GPR45 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR45_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR45_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR45_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR45_DWP_SHIFT)) & IOMUXC_GPR_GPR45_DWP_MASK)

#define IOMUXC_GPR_GPR45_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR45_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR45_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR45_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR45_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR46 - GPR46 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR46_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR46_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR46_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR46_DWP_SHIFT)) & IOMUXC_GPR_GPR46_DWP_MASK)

#define IOMUXC_GPR_GPR46_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR46_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR46_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR46_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR46_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR47 - GPR47 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR47_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR47_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR47_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR47_DWP_SHIFT)) & IOMUXC_GPR_GPR47_DWP_MASK)

#define IOMUXC_GPR_GPR47_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR47_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR47_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR47_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR47_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR48 - GPR48 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR48_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR48_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR48_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR48_DWP_SHIFT)) & IOMUXC_GPR_GPR48_DWP_MASK)

#define IOMUXC_GPR_GPR48_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR48_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR48_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR48_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR48_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR49 - GPR49 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR49_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR49_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR49_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR49_DWP_SHIFT)) & IOMUXC_GPR_GPR49_DWP_MASK)

#define IOMUXC_GPR_GPR49_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR49_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR49_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR49_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR49_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR50 - GPR50 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR50_CAAM_IPS_MGR_MASK       (0x1FU)
#define IOMUXC_GPR_GPR50_CAAM_IPS_MGR_SHIFT      (0U)
/*! CAAM_IPS_MGR - CAAM manager processor identifier */
#define IOMUXC_GPR_GPR50_CAAM_IPS_MGR(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR50_CAAM_IPS_MGR_SHIFT)) & IOMUXC_GPR_GPR50_CAAM_IPS_MGR_MASK)

#define IOMUXC_GPR_GPR50_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR50_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR50_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR50_DWP_SHIFT)) & IOMUXC_GPR_GPR50_DWP_MASK)

#define IOMUXC_GPR_GPR50_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR50_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR50_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR50_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR50_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR51 - GPR51 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR51_M7_NMI_CLEAR_MASK       (0x1U)
#define IOMUXC_GPR_GPR51_M7_NMI_CLEAR_SHIFT      (0U)
/*! M7_NMI_CLEAR - Clear CM7 NMI holding register */
#define IOMUXC_GPR_GPR51_M7_NMI_CLEAR(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR51_M7_NMI_CLEAR_SHIFT)) & IOMUXC_GPR_GPR51_M7_NMI_CLEAR_MASK)

#define IOMUXC_GPR_GPR51_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR51_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR51_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR51_DWP_SHIFT)) & IOMUXC_GPR_GPR51_DWP_MASK)

#define IOMUXC_GPR_GPR51_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR51_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR51_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR51_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR51_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR52 - GPR52 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR52_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR52_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR52_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR52_DWP_SHIFT)) & IOMUXC_GPR_GPR52_DWP_MASK)

#define IOMUXC_GPR_GPR52_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR52_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR52_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR52_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR52_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR53 - GPR53 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR53_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR53_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR53_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR53_DWP_SHIFT)) & IOMUXC_GPR_GPR53_DWP_MASK)

#define IOMUXC_GPR_GPR53_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR53_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR53_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR53_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR53_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR54 - GPR54 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR54_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR54_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR54_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR54_DWP_SHIFT)) & IOMUXC_GPR_GPR54_DWP_MASK)

#define IOMUXC_GPR_GPR54_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR54_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR54_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR54_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR54_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR55 - GPR55 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR55_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR55_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR55_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR55_DWP_SHIFT)) & IOMUXC_GPR_GPR55_DWP_MASK)

#define IOMUXC_GPR_GPR55_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR55_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR55_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR55_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR55_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR59 - GPR59 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR59_MIPI_CSI_AUTO_PD_EN_MASK (0x1U)
#define IOMUXC_GPR_GPR59_MIPI_CSI_AUTO_PD_EN_SHIFT (0U)
/*! MIPI_CSI_AUTO_PD_EN - Powers down inactive lanes reported by CSI2X_CFG_NUM_LANES. */
#define IOMUXC_GPR_GPR59_MIPI_CSI_AUTO_PD_EN(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR59_MIPI_CSI_AUTO_PD_EN_SHIFT)) & IOMUXC_GPR_GPR59_MIPI_CSI_AUTO_PD_EN_MASK)

#define IOMUXC_GPR_GPR59_MIPI_CSI_SOFT_RST_N_MASK (0x2U)
#define IOMUXC_GPR_GPR59_MIPI_CSI_SOFT_RST_N_SHIFT (1U)
/*! MIPI_CSI_SOFT_RST_N - MIPI CSI APB clock domain and User interface clock domain software reset bit
 *  0b0..Assert reset
 *  0b1..De-assert reset
 */
#define IOMUXC_GPR_GPR59_MIPI_CSI_SOFT_RST_N(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR59_MIPI_CSI_SOFT_RST_N_SHIFT)) & IOMUXC_GPR_GPR59_MIPI_CSI_SOFT_RST_N_MASK)

#define IOMUXC_GPR_GPR59_MIPI_CSI_CONT_CLK_MODE_MASK (0x4U)
#define IOMUXC_GPR_GPR59_MIPI_CSI_CONT_CLK_MODE_SHIFT (2U)
/*! MIPI_CSI_CONT_CLK_MODE - Enables the slave clock lane feature to maintain HS reception state
 *    during continuous clock mode operation, despite line glitches.
 */
#define IOMUXC_GPR_GPR59_MIPI_CSI_CONT_CLK_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR59_MIPI_CSI_CONT_CLK_MODE_SHIFT)) & IOMUXC_GPR_GPR59_MIPI_CSI_CONT_CLK_MODE_MASK)

#define IOMUXC_GPR_GPR59_MIPI_CSI_DDRCLK_EN_MASK (0x8U)
#define IOMUXC_GPR_GPR59_MIPI_CSI_DDRCLK_EN_SHIFT (3U)
/*! MIPI_CSI_DDRCLK_EN - When high, enables received DDR clock on CLK_DRXHS */
#define IOMUXC_GPR_GPR59_MIPI_CSI_DDRCLK_EN(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR59_MIPI_CSI_DDRCLK_EN_SHIFT)) & IOMUXC_GPR_GPR59_MIPI_CSI_DDRCLK_EN_MASK)

#define IOMUXC_GPR_GPR59_MIPI_CSI_PD_RX_MASK     (0x10U)
#define IOMUXC_GPR_GPR59_MIPI_CSI_PD_RX_SHIFT    (4U)
/*! MIPI_CSI_PD_RX - Power Down input for MIPI CSI PHY. */
#define IOMUXC_GPR_GPR59_MIPI_CSI_PD_RX(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR59_MIPI_CSI_PD_RX_SHIFT)) & IOMUXC_GPR_GPR59_MIPI_CSI_PD_RX_MASK)

#define IOMUXC_GPR_GPR59_MIPI_CSI_RX_ENABLE_MASK (0x20U)
#define IOMUXC_GPR_GPR59_MIPI_CSI_RX_ENABLE_SHIFT (5U)
/*! MIPI_CSI_RX_ENABLE - Assert to enable MIPI CSI Receive Enable */
#define IOMUXC_GPR_GPR59_MIPI_CSI_RX_ENABLE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR59_MIPI_CSI_RX_ENABLE_SHIFT)) & IOMUXC_GPR_GPR59_MIPI_CSI_RX_ENABLE_MASK)

#define IOMUXC_GPR_GPR59_MIPI_CSI_RX_RCAL_MASK   (0xC0U)
#define IOMUXC_GPR_GPR59_MIPI_CSI_RX_RCAL_SHIFT  (6U)
/*! MIPI_CSI_RX_RCAL - MIPI CSI PHY on-chip termination control bits */
#define IOMUXC_GPR_GPR59_MIPI_CSI_RX_RCAL(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR59_MIPI_CSI_RX_RCAL_SHIFT)) & IOMUXC_GPR_GPR59_MIPI_CSI_RX_RCAL_MASK)

#define IOMUXC_GPR_GPR59_MIPI_CSI_RXCDRP_MASK    (0x300U)
#define IOMUXC_GPR_GPR59_MIPI_CSI_RXCDRP_SHIFT   (8U)
/*! MIPI_CSI_RXCDRP - Programming bits that adjust the threshold voltage of LP-CD, default setting 2'b01
 *  0b00..344mV
 *  0b01..325mV (Default)
 *  0b10..307mV
 *  0b11..Invalid
 */
#define IOMUXC_GPR_GPR59_MIPI_CSI_RXCDRP(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR59_MIPI_CSI_RXCDRP_SHIFT)) & IOMUXC_GPR_GPR59_MIPI_CSI_RXCDRP_MASK)

#define IOMUXC_GPR_GPR59_MIPI_CSI_RXLPRP_MASK    (0xC00U)
#define IOMUXC_GPR_GPR59_MIPI_CSI_RXLPRP_SHIFT   (10U)
/*! MIPI_CSI_RXLPRP - Programming bits that adjust the threshold voltage of LP-RX, default setting 2'b01 */
#define IOMUXC_GPR_GPR59_MIPI_CSI_RXLPRP(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR59_MIPI_CSI_RXLPRP_SHIFT)) & IOMUXC_GPR_GPR59_MIPI_CSI_RXLPRP_MASK)

#define IOMUXC_GPR_GPR59_MIPI_CSI_S_PRG_RXHS_SETTLE_MASK (0x3F000U)
#define IOMUXC_GPR_GPR59_MIPI_CSI_S_PRG_RXHS_SETTLE_SHIFT (12U)
/*! MIPI_CSI_S_PRG_RXHS_SETTLE - Bits used to program T_HS_SETTLE. */
#define IOMUXC_GPR_GPR59_MIPI_CSI_S_PRG_RXHS_SETTLE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR59_MIPI_CSI_S_PRG_RXHS_SETTLE_SHIFT)) & IOMUXC_GPR_GPR59_MIPI_CSI_S_PRG_RXHS_SETTLE_MASK)

#define IOMUXC_GPR_GPR59_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR59_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR59_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR59_DWP_SHIFT)) & IOMUXC_GPR_GPR59_DWP_MASK)

#define IOMUXC_GPR_GPR59_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR59_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR59_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR59_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR59_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR62 - GPR62 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR62_MIPI_DSI_CLK_TM_MASK    (0x7U)
#define IOMUXC_GPR_GPR62_MIPI_DSI_CLK_TM_SHIFT   (0U)
/*! MIPI_DSI_CLK_TM - MIPI DSI Clock Lane triming bits */
#define IOMUXC_GPR_GPR62_MIPI_DSI_CLK_TM(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR62_MIPI_DSI_CLK_TM_SHIFT)) & IOMUXC_GPR_GPR62_MIPI_DSI_CLK_TM_MASK)

#define IOMUXC_GPR_GPR62_MIPI_DSI_D0_TM_MASK     (0x38U)
#define IOMUXC_GPR_GPR62_MIPI_DSI_D0_TM_SHIFT    (3U)
/*! MIPI_DSI_D0_TM - MIPI DSI Data Lane 0 triming bits */
#define IOMUXC_GPR_GPR62_MIPI_DSI_D0_TM(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR62_MIPI_DSI_D0_TM_SHIFT)) & IOMUXC_GPR_GPR62_MIPI_DSI_D0_TM_MASK)

#define IOMUXC_GPR_GPR62_MIPI_DSI_D1_TM_MASK     (0x1C0U)
#define IOMUXC_GPR_GPR62_MIPI_DSI_D1_TM_SHIFT    (6U)
/*! MIPI_DSI_D1_TM - MIPI DSI Data Lane 1 triming bits */
#define IOMUXC_GPR_GPR62_MIPI_DSI_D1_TM(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR62_MIPI_DSI_D1_TM_SHIFT)) & IOMUXC_GPR_GPR62_MIPI_DSI_D1_TM_MASK)

#define IOMUXC_GPR_GPR62_MIPI_DSI_TX_RCAL_MASK   (0x600U)
#define IOMUXC_GPR_GPR62_MIPI_DSI_TX_RCAL_SHIFT  (9U)
/*! MIPI_DSI_TX_RCAL - MIPI DSI PHY on-chip termination control bits */
#define IOMUXC_GPR_GPR62_MIPI_DSI_TX_RCAL(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR62_MIPI_DSI_TX_RCAL_SHIFT)) & IOMUXC_GPR_GPR62_MIPI_DSI_TX_RCAL_MASK)

#define IOMUXC_GPR_GPR62_MIPI_DSI_TX_ULPS_ENABLE_MASK (0x3800U)
#define IOMUXC_GPR_GPR62_MIPI_DSI_TX_ULPS_ENABLE_SHIFT (11U)
/*! MIPI_DSI_TX_ULPS_ENABLE - DSI transmit ULPS mode enable */
#define IOMUXC_GPR_GPR62_MIPI_DSI_TX_ULPS_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR62_MIPI_DSI_TX_ULPS_ENABLE_SHIFT)) & IOMUXC_GPR_GPR62_MIPI_DSI_TX_ULPS_ENABLE_MASK)

#define IOMUXC_GPR_GPR62_MIPI_DSI_PCLK_SOFT_RESET_N_MASK (0x10000U)
#define IOMUXC_GPR_GPR62_MIPI_DSI_PCLK_SOFT_RESET_N_SHIFT (16U)
/*! MIPI_DSI_PCLK_SOFT_RESET_N - MIPI DSI APB clock domain software reset bit
 *  0b0..Assert reset
 *  0b1..De-assert reset
 */
#define IOMUXC_GPR_GPR62_MIPI_DSI_PCLK_SOFT_RESET_N(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR62_MIPI_DSI_PCLK_SOFT_RESET_N_SHIFT)) & IOMUXC_GPR_GPR62_MIPI_DSI_PCLK_SOFT_RESET_N_MASK)

#define IOMUXC_GPR_GPR62_MIPI_DSI_BYTE_SOFT_RESET_N_MASK (0x20000U)
#define IOMUXC_GPR_GPR62_MIPI_DSI_BYTE_SOFT_RESET_N_SHIFT (17U)
/*! MIPI_DSI_BYTE_SOFT_RESET_N - MIPI DSI Byte clock domain software reset bit
 *  0b0..Assert reset
 *  0b1..De-assert reset
 */
#define IOMUXC_GPR_GPR62_MIPI_DSI_BYTE_SOFT_RESET_N(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR62_MIPI_DSI_BYTE_SOFT_RESET_N_SHIFT)) & IOMUXC_GPR_GPR62_MIPI_DSI_BYTE_SOFT_RESET_N_MASK)

#define IOMUXC_GPR_GPR62_MIPI_DSI_DPI_SOFT_RESET_N_MASK (0x40000U)
#define IOMUXC_GPR_GPR62_MIPI_DSI_DPI_SOFT_RESET_N_SHIFT (18U)
/*! MIPI_DSI_DPI_SOFT_RESET_N - MIPI DSI Pixel clock domain software reset bit
 *  0b0..Assert reset
 *  0b1..De-assert reset
 */
#define IOMUXC_GPR_GPR62_MIPI_DSI_DPI_SOFT_RESET_N(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR62_MIPI_DSI_DPI_SOFT_RESET_N_SHIFT)) & IOMUXC_GPR_GPR62_MIPI_DSI_DPI_SOFT_RESET_N_MASK)

#define IOMUXC_GPR_GPR62_MIPI_DSI_ESC_SOFT_RESET_N_MASK (0x80000U)
#define IOMUXC_GPR_GPR62_MIPI_DSI_ESC_SOFT_RESET_N_SHIFT (19U)
/*! MIPI_DSI_ESC_SOFT_RESET_N - MIPI DSI Escape clock domain software reset bit
 *  0b0..Assert reset
 *  0b1..De-assert reset
 */
#define IOMUXC_GPR_GPR62_MIPI_DSI_ESC_SOFT_RESET_N(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR62_MIPI_DSI_ESC_SOFT_RESET_N_SHIFT)) & IOMUXC_GPR_GPR62_MIPI_DSI_ESC_SOFT_RESET_N_MASK)

#define IOMUXC_GPR_GPR62_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR62_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR62_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR62_DWP_SHIFT)) & IOMUXC_GPR_GPR62_DWP_MASK)

#define IOMUXC_GPR_GPR62_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR62_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR62_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR62_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR62_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR63 - GPR63 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR63_MIPI_DSI_TX_ULPS_ACTIVE_MASK (0x7U)
#define IOMUXC_GPR_GPR63_MIPI_DSI_TX_ULPS_ACTIVE_SHIFT (0U)
/*! MIPI_DSI_TX_ULPS_ACTIVE - DSI transmit ULPS mode active flag */
#define IOMUXC_GPR_GPR63_MIPI_DSI_TX_ULPS_ACTIVE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR63_MIPI_DSI_TX_ULPS_ACTIVE_SHIFT)) & IOMUXC_GPR_GPR63_MIPI_DSI_TX_ULPS_ACTIVE_MASK)
/*! @} */

/*! @name GPR64 - GPR64 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR64_GPIO_DISP1_FREEZE_MASK  (0x1U)
#define IOMUXC_GPR_GPR64_GPIO_DISP1_FREEZE_SHIFT (0U)
/*! GPIO_DISP1_FREEZE - Compensation code freeze */
#define IOMUXC_GPR_GPR64_GPIO_DISP1_FREEZE(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR64_GPIO_DISP1_FREEZE_SHIFT)) & IOMUXC_GPR_GPR64_GPIO_DISP1_FREEZE_MASK)

#define IOMUXC_GPR_GPR64_GPIO_DISP1_COMPTQ_MASK  (0x2U)
#define IOMUXC_GPR_GPR64_GPIO_DISP1_COMPTQ_SHIFT (1U)
/*! GPIO_DISP1_COMPTQ - COMPEN and COMPTQ control the operating modes of the compensation cell */
#define IOMUXC_GPR_GPR64_GPIO_DISP1_COMPTQ(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR64_GPIO_DISP1_COMPTQ_SHIFT)) & IOMUXC_GPR_GPR64_GPIO_DISP1_COMPTQ_MASK)

#define IOMUXC_GPR_GPR64_GPIO_DISP1_COMPEN_MASK  (0x4U)
#define IOMUXC_GPR_GPR64_GPIO_DISP1_COMPEN_SHIFT (2U)
/*! GPIO_DISP1_COMPEN - COMPEN and COMPTQ control the operating modes of the compensation cell */
#define IOMUXC_GPR_GPR64_GPIO_DISP1_COMPEN(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR64_GPIO_DISP1_COMPEN_SHIFT)) & IOMUXC_GPR_GPR64_GPIO_DISP1_COMPEN_MASK)

#define IOMUXC_GPR_GPR64_GPIO_DISP1_FASTFRZ_EN_MASK (0x8U)
#define IOMUXC_GPR_GPR64_GPIO_DISP1_FASTFRZ_EN_SHIFT (3U)
/*! GPIO_DISP1_FASTFRZ_EN - Compensation code fast freeze */
#define IOMUXC_GPR_GPR64_GPIO_DISP1_FASTFRZ_EN(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR64_GPIO_DISP1_FASTFRZ_EN_SHIFT)) & IOMUXC_GPR_GPR64_GPIO_DISP1_FASTFRZ_EN_MASK)

#define IOMUXC_GPR_GPR64_GPIO_DISP1_RASRCP_MASK  (0xF0U)
#define IOMUXC_GPR_GPR64_GPIO_DISP1_RASRCP_SHIFT (4U)
/*! GPIO_DISP1_RASRCP - GPIO_DISP_B1 IO bank's 4-bit PMOS compensation codes from core */
#define IOMUXC_GPR_GPR64_GPIO_DISP1_RASRCP(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR64_GPIO_DISP1_RASRCP_SHIFT)) & IOMUXC_GPR_GPR64_GPIO_DISP1_RASRCP_MASK)

#define IOMUXC_GPR_GPR64_GPIO_DISP1_RASRCN_MASK  (0xF00U)
#define IOMUXC_GPR_GPR64_GPIO_DISP1_RASRCN_SHIFT (8U)
/*! GPIO_DISP1_RASRCN - GPIO_DISP_B1 IO bank's 4-bit NMOS compensation codes from core */
#define IOMUXC_GPR_GPR64_GPIO_DISP1_RASRCN(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR64_GPIO_DISP1_RASRCN_SHIFT)) & IOMUXC_GPR_GPR64_GPIO_DISP1_RASRCN_MASK)

#define IOMUXC_GPR_GPR64_GPIO_DISP1_SELECT_NASRC_MASK (0x1000U)
#define IOMUXC_GPR_GPR64_GPIO_DISP1_SELECT_NASRC_SHIFT (12U)
/*! GPIO_DISP1_SELECT_NASRC - GPIO_DISP1_NASRC selection */
#define IOMUXC_GPR_GPR64_GPIO_DISP1_SELECT_NASRC(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR64_GPIO_DISP1_SELECT_NASRC_SHIFT)) & IOMUXC_GPR_GPR64_GPIO_DISP1_SELECT_NASRC_MASK)

#define IOMUXC_GPR_GPR64_GPIO_DISP1_REFGEN_SLEEP_MASK (0x2000U)
#define IOMUXC_GPR_GPR64_GPIO_DISP1_REFGEN_SLEEP_SHIFT (13U)
/*! GPIO_DISP1_REFGEN_SLEEP - GPIO_DISP_B1 IO bank reference voltage generator cell sleep enable */
#define IOMUXC_GPR_GPR64_GPIO_DISP1_REFGEN_SLEEP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR64_GPIO_DISP1_REFGEN_SLEEP_SHIFT)) & IOMUXC_GPR_GPR64_GPIO_DISP1_REFGEN_SLEEP_MASK)

#define IOMUXC_GPR_GPR64_GPIO_DISP1_SUPLYDET_LATCH_MASK (0x4000U)
#define IOMUXC_GPR_GPR64_GPIO_DISP1_SUPLYDET_LATCH_SHIFT (14U)
/*! GPIO_DISP1_SUPLYDET_LATCH - GPIO_DISP_B1 IO bank power supply mode latch enable */
#define IOMUXC_GPR_GPR64_GPIO_DISP1_SUPLYDET_LATCH(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR64_GPIO_DISP1_SUPLYDET_LATCH_SHIFT)) & IOMUXC_GPR_GPR64_GPIO_DISP1_SUPLYDET_LATCH_MASK)

#define IOMUXC_GPR_GPR64_GPIO_DISP1_COMPOK_MASK  (0x100000U)
#define IOMUXC_GPR_GPR64_GPIO_DISP1_COMPOK_SHIFT (20U)
/*! GPIO_DISP1_COMPOK - GPIO_DISP_B1 IO bank compensation OK flag */
#define IOMUXC_GPR_GPR64_GPIO_DISP1_COMPOK(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR64_GPIO_DISP1_COMPOK_SHIFT)) & IOMUXC_GPR_GPR64_GPIO_DISP1_COMPOK_MASK)

#define IOMUXC_GPR_GPR64_GPIO_DISP1_NASRC_MASK   (0x1E00000U)
#define IOMUXC_GPR_GPR64_GPIO_DISP1_NASRC_SHIFT  (21U)
/*! GPIO_DISP1_NASRC - GPIO_DISP_B1 IO bank compensation codes */
#define IOMUXC_GPR_GPR64_GPIO_DISP1_NASRC(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR64_GPIO_DISP1_NASRC_SHIFT)) & IOMUXC_GPR_GPR64_GPIO_DISP1_NASRC_MASK)

#define IOMUXC_GPR_GPR64_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR64_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR64_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR64_DWP_SHIFT)) & IOMUXC_GPR_GPR64_DWP_MASK)

#define IOMUXC_GPR_GPR64_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR64_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR64_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR64_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR64_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR65 - GPR65 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR65_GPIO_EMC1_FREEZE_MASK   (0x1U)
#define IOMUXC_GPR_GPR65_GPIO_EMC1_FREEZE_SHIFT  (0U)
/*! GPIO_EMC1_FREEZE - Compensation code freeze */
#define IOMUXC_GPR_GPR65_GPIO_EMC1_FREEZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR65_GPIO_EMC1_FREEZE_SHIFT)) & IOMUXC_GPR_GPR65_GPIO_EMC1_FREEZE_MASK)

#define IOMUXC_GPR_GPR65_GPIO_EMC1_COMPTQ_MASK   (0x2U)
#define IOMUXC_GPR_GPR65_GPIO_EMC1_COMPTQ_SHIFT  (1U)
/*! GPIO_EMC1_COMPTQ - COMPEN and COMPTQ control the operating modes of the compensation cell */
#define IOMUXC_GPR_GPR65_GPIO_EMC1_COMPTQ(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR65_GPIO_EMC1_COMPTQ_SHIFT)) & IOMUXC_GPR_GPR65_GPIO_EMC1_COMPTQ_MASK)

#define IOMUXC_GPR_GPR65_GPIO_EMC1_COMPEN_MASK   (0x4U)
#define IOMUXC_GPR_GPR65_GPIO_EMC1_COMPEN_SHIFT  (2U)
/*! GPIO_EMC1_COMPEN - COMPEN and COMPTQ control the operating modes of the compensation cell */
#define IOMUXC_GPR_GPR65_GPIO_EMC1_COMPEN(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR65_GPIO_EMC1_COMPEN_SHIFT)) & IOMUXC_GPR_GPR65_GPIO_EMC1_COMPEN_MASK)

#define IOMUXC_GPR_GPR65_GPIO_EMC1_FASTFRZ_EN_MASK (0x8U)
#define IOMUXC_GPR_GPR65_GPIO_EMC1_FASTFRZ_EN_SHIFT (3U)
/*! GPIO_EMC1_FASTFRZ_EN - Compensation code fast freeze */
#define IOMUXC_GPR_GPR65_GPIO_EMC1_FASTFRZ_EN(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR65_GPIO_EMC1_FASTFRZ_EN_SHIFT)) & IOMUXC_GPR_GPR65_GPIO_EMC1_FASTFRZ_EN_MASK)

#define IOMUXC_GPR_GPR65_GPIO_EMC1_RASRCP_MASK   (0xF0U)
#define IOMUXC_GPR_GPR65_GPIO_EMC1_RASRCP_SHIFT  (4U)
/*! GPIO_EMC1_RASRCP - GPIO_EMC_B1 IO bank's 4-bit PMOS compensation codes from core */
#define IOMUXC_GPR_GPR65_GPIO_EMC1_RASRCP(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR65_GPIO_EMC1_RASRCP_SHIFT)) & IOMUXC_GPR_GPR65_GPIO_EMC1_RASRCP_MASK)

#define IOMUXC_GPR_GPR65_GPIO_EMC1_RASRCN_MASK   (0xF00U)
#define IOMUXC_GPR_GPR65_GPIO_EMC1_RASRCN_SHIFT  (8U)
/*! GPIO_EMC1_RASRCN - GPIO_EMC_B1 IO bank's 4-bit NMOS compensation codes from core */
#define IOMUXC_GPR_GPR65_GPIO_EMC1_RASRCN(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR65_GPIO_EMC1_RASRCN_SHIFT)) & IOMUXC_GPR_GPR65_GPIO_EMC1_RASRCN_MASK)

#define IOMUXC_GPR_GPR65_GPIO_EMC1_SELECT_NASRC_MASK (0x1000U)
#define IOMUXC_GPR_GPR65_GPIO_EMC1_SELECT_NASRC_SHIFT (12U)
/*! GPIO_EMC1_SELECT_NASRC - GPIO_EMC1_NASRC selection */
#define IOMUXC_GPR_GPR65_GPIO_EMC1_SELECT_NASRC(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR65_GPIO_EMC1_SELECT_NASRC_SHIFT)) & IOMUXC_GPR_GPR65_GPIO_EMC1_SELECT_NASRC_MASK)

#define IOMUXC_GPR_GPR65_GPIO_EMC1_REFGEN_SLEEP_MASK (0x2000U)
#define IOMUXC_GPR_GPR65_GPIO_EMC1_REFGEN_SLEEP_SHIFT (13U)
/*! GPIO_EMC1_REFGEN_SLEEP - GPIO_EMC_B1 IO bank reference voltage generator cell sleep enable */
#define IOMUXC_GPR_GPR65_GPIO_EMC1_REFGEN_SLEEP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR65_GPIO_EMC1_REFGEN_SLEEP_SHIFT)) & IOMUXC_GPR_GPR65_GPIO_EMC1_REFGEN_SLEEP_MASK)

#define IOMUXC_GPR_GPR65_GPIO_EMC1_SUPLYDET_LATCH_MASK (0x4000U)
#define IOMUXC_GPR_GPR65_GPIO_EMC1_SUPLYDET_LATCH_SHIFT (14U)
/*! GPIO_EMC1_SUPLYDET_LATCH - GPIO_EMC_B1 IO bank power supply mode latch enable */
#define IOMUXC_GPR_GPR65_GPIO_EMC1_SUPLYDET_LATCH(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR65_GPIO_EMC1_SUPLYDET_LATCH_SHIFT)) & IOMUXC_GPR_GPR65_GPIO_EMC1_SUPLYDET_LATCH_MASK)

#define IOMUXC_GPR_GPR65_GPIO_EMC1_COMPOK_MASK   (0x100000U)
#define IOMUXC_GPR_GPR65_GPIO_EMC1_COMPOK_SHIFT  (20U)
/*! GPIO_EMC1_COMPOK - GPIO_EMC_B1 IO bank compensation OK flag */
#define IOMUXC_GPR_GPR65_GPIO_EMC1_COMPOK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR65_GPIO_EMC1_COMPOK_SHIFT)) & IOMUXC_GPR_GPR65_GPIO_EMC1_COMPOK_MASK)

#define IOMUXC_GPR_GPR65_GPIO_EMC1_NASRC_MASK    (0x1E00000U)
#define IOMUXC_GPR_GPR65_GPIO_EMC1_NASRC_SHIFT   (21U)
/*! GPIO_EMC1_NASRC - GPIO_EMC_B1 IO bank compensation codes */
#define IOMUXC_GPR_GPR65_GPIO_EMC1_NASRC(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR65_GPIO_EMC1_NASRC_SHIFT)) & IOMUXC_GPR_GPR65_GPIO_EMC1_NASRC_MASK)

#define IOMUXC_GPR_GPR65_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR65_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR65_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR65_DWP_SHIFT)) & IOMUXC_GPR_GPR65_DWP_MASK)

#define IOMUXC_GPR_GPR65_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR65_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR65_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR65_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR65_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR66 - GPR66 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR66_GPIO_EMC2_FREEZE_MASK   (0x1U)
#define IOMUXC_GPR_GPR66_GPIO_EMC2_FREEZE_SHIFT  (0U)
/*! GPIO_EMC2_FREEZE - Compensation code freeze */
#define IOMUXC_GPR_GPR66_GPIO_EMC2_FREEZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR66_GPIO_EMC2_FREEZE_SHIFT)) & IOMUXC_GPR_GPR66_GPIO_EMC2_FREEZE_MASK)

#define IOMUXC_GPR_GPR66_GPIO_EMC2_COMPTQ_MASK   (0x2U)
#define IOMUXC_GPR_GPR66_GPIO_EMC2_COMPTQ_SHIFT  (1U)
/*! GPIO_EMC2_COMPTQ - COMPEN and COMPTQ control the operating modes of the compensation cell */
#define IOMUXC_GPR_GPR66_GPIO_EMC2_COMPTQ(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR66_GPIO_EMC2_COMPTQ_SHIFT)) & IOMUXC_GPR_GPR66_GPIO_EMC2_COMPTQ_MASK)

#define IOMUXC_GPR_GPR66_GPIO_EMC2_COMPEN_MASK   (0x4U)
#define IOMUXC_GPR_GPR66_GPIO_EMC2_COMPEN_SHIFT  (2U)
/*! GPIO_EMC2_COMPEN - COMPEN and COMPTQ control the operating modes of the compensation cell */
#define IOMUXC_GPR_GPR66_GPIO_EMC2_COMPEN(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR66_GPIO_EMC2_COMPEN_SHIFT)) & IOMUXC_GPR_GPR66_GPIO_EMC2_COMPEN_MASK)

#define IOMUXC_GPR_GPR66_GPIO_EMC2_FASTFRZ_EN_MASK (0x8U)
#define IOMUXC_GPR_GPR66_GPIO_EMC2_FASTFRZ_EN_SHIFT (3U)
/*! GPIO_EMC2_FASTFRZ_EN - Compensation code fast freeze */
#define IOMUXC_GPR_GPR66_GPIO_EMC2_FASTFRZ_EN(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR66_GPIO_EMC2_FASTFRZ_EN_SHIFT)) & IOMUXC_GPR_GPR66_GPIO_EMC2_FASTFRZ_EN_MASK)

#define IOMUXC_GPR_GPR66_GPIO_EMC2_RASRCP_MASK   (0xF0U)
#define IOMUXC_GPR_GPR66_GPIO_EMC2_RASRCP_SHIFT  (4U)
/*! GPIO_EMC2_RASRCP - GPIO_EMC_B2 IO bank's 4-bit PMOS compensation codes from core */
#define IOMUXC_GPR_GPR66_GPIO_EMC2_RASRCP(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR66_GPIO_EMC2_RASRCP_SHIFT)) & IOMUXC_GPR_GPR66_GPIO_EMC2_RASRCP_MASK)

#define IOMUXC_GPR_GPR66_GPIO_EMC2_RASRCN_MASK   (0xF00U)
#define IOMUXC_GPR_GPR66_GPIO_EMC2_RASRCN_SHIFT  (8U)
/*! GPIO_EMC2_RASRCN - GPIO_EMC_B2 IO bank's 4-bit NMOS compensation codes from core */
#define IOMUXC_GPR_GPR66_GPIO_EMC2_RASRCN(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR66_GPIO_EMC2_RASRCN_SHIFT)) & IOMUXC_GPR_GPR66_GPIO_EMC2_RASRCN_MASK)

#define IOMUXC_GPR_GPR66_GPIO_EMC2_SELECT_NASRC_MASK (0x1000U)
#define IOMUXC_GPR_GPR66_GPIO_EMC2_SELECT_NASRC_SHIFT (12U)
/*! GPIO_EMC2_SELECT_NASRC - GPIO_EMC2_NASRC selection */
#define IOMUXC_GPR_GPR66_GPIO_EMC2_SELECT_NASRC(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR66_GPIO_EMC2_SELECT_NASRC_SHIFT)) & IOMUXC_GPR_GPR66_GPIO_EMC2_SELECT_NASRC_MASK)

#define IOMUXC_GPR_GPR66_GPIO_EMC2_REFGEN_SLEEP_MASK (0x2000U)
#define IOMUXC_GPR_GPR66_GPIO_EMC2_REFGEN_SLEEP_SHIFT (13U)
/*! GPIO_EMC2_REFGEN_SLEEP - GPIO_EMC_B2 IO bank reference voltage generator cell sleep enable */
#define IOMUXC_GPR_GPR66_GPIO_EMC2_REFGEN_SLEEP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR66_GPIO_EMC2_REFGEN_SLEEP_SHIFT)) & IOMUXC_GPR_GPR66_GPIO_EMC2_REFGEN_SLEEP_MASK)

#define IOMUXC_GPR_GPR66_GPIO_EMC2_SUPLYDET_LATCH_MASK (0x4000U)
#define IOMUXC_GPR_GPR66_GPIO_EMC2_SUPLYDET_LATCH_SHIFT (14U)
/*! GPIO_EMC2_SUPLYDET_LATCH - GPIO_EMC_B2 IO bank power supply mode latch enable */
#define IOMUXC_GPR_GPR66_GPIO_EMC2_SUPLYDET_LATCH(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR66_GPIO_EMC2_SUPLYDET_LATCH_SHIFT)) & IOMUXC_GPR_GPR66_GPIO_EMC2_SUPLYDET_LATCH_MASK)

#define IOMUXC_GPR_GPR66_GPIO_EMC2_COMPOK_MASK   (0x100000U)
#define IOMUXC_GPR_GPR66_GPIO_EMC2_COMPOK_SHIFT  (20U)
/*! GPIO_EMC2_COMPOK - GPIO_EMC_B2 IO bank compensation OK flag */
#define IOMUXC_GPR_GPR66_GPIO_EMC2_COMPOK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR66_GPIO_EMC2_COMPOK_SHIFT)) & IOMUXC_GPR_GPR66_GPIO_EMC2_COMPOK_MASK)

#define IOMUXC_GPR_GPR66_GPIO_EMC2_NASRC_MASK    (0x1E00000U)
#define IOMUXC_GPR_GPR66_GPIO_EMC2_NASRC_SHIFT   (21U)
/*! GPIO_EMC2_NASRC - GPIO_EMC_B2 IO bank compensation codes */
#define IOMUXC_GPR_GPR66_GPIO_EMC2_NASRC(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR66_GPIO_EMC2_NASRC_SHIFT)) & IOMUXC_GPR_GPR66_GPIO_EMC2_NASRC_MASK)

#define IOMUXC_GPR_GPR66_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR66_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR66_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR66_DWP_SHIFT)) & IOMUXC_GPR_GPR66_DWP_MASK)

#define IOMUXC_GPR_GPR66_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR66_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR66_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR66_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR66_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR67 - GPR67 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR67_GPIO_SD1_FREEZE_MASK    (0x1U)
#define IOMUXC_GPR_GPR67_GPIO_SD1_FREEZE_SHIFT   (0U)
/*! GPIO_SD1_FREEZE - Compensation code freeze */
#define IOMUXC_GPR_GPR67_GPIO_SD1_FREEZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR67_GPIO_SD1_FREEZE_SHIFT)) & IOMUXC_GPR_GPR67_GPIO_SD1_FREEZE_MASK)

#define IOMUXC_GPR_GPR67_GPIO_SD1_COMPTQ_MASK    (0x2U)
#define IOMUXC_GPR_GPR67_GPIO_SD1_COMPTQ_SHIFT   (1U)
/*! GPIO_SD1_COMPTQ - COMPEN and COMPTQ control the operating modes of the compensation cell */
#define IOMUXC_GPR_GPR67_GPIO_SD1_COMPTQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR67_GPIO_SD1_COMPTQ_SHIFT)) & IOMUXC_GPR_GPR67_GPIO_SD1_COMPTQ_MASK)

#define IOMUXC_GPR_GPR67_GPIO_SD1_COMPEN_MASK    (0x4U)
#define IOMUXC_GPR_GPR67_GPIO_SD1_COMPEN_SHIFT   (2U)
/*! GPIO_SD1_COMPEN - COMPEN and COMPTQ control the operating modes of the compensation cell */
#define IOMUXC_GPR_GPR67_GPIO_SD1_COMPEN(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR67_GPIO_SD1_COMPEN_SHIFT)) & IOMUXC_GPR_GPR67_GPIO_SD1_COMPEN_MASK)

#define IOMUXC_GPR_GPR67_GPIO_SD1_FASTFRZ_EN_MASK (0x8U)
#define IOMUXC_GPR_GPR67_GPIO_SD1_FASTFRZ_EN_SHIFT (3U)
/*! GPIO_SD1_FASTFRZ_EN - Compensation code fast freeze */
#define IOMUXC_GPR_GPR67_GPIO_SD1_FASTFRZ_EN(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR67_GPIO_SD1_FASTFRZ_EN_SHIFT)) & IOMUXC_GPR_GPR67_GPIO_SD1_FASTFRZ_EN_MASK)

#define IOMUXC_GPR_GPR67_GPIO_SD1_RASRCP_MASK    (0xF0U)
#define IOMUXC_GPR_GPR67_GPIO_SD1_RASRCP_SHIFT   (4U)
/*! GPIO_SD1_RASRCP - GPIO_SD_B1 IO bank's 4-bit PMOS compensation codes from core */
#define IOMUXC_GPR_GPR67_GPIO_SD1_RASRCP(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR67_GPIO_SD1_RASRCP_SHIFT)) & IOMUXC_GPR_GPR67_GPIO_SD1_RASRCP_MASK)

#define IOMUXC_GPR_GPR67_GPIO_SD1_RASRCN_MASK    (0xF00U)
#define IOMUXC_GPR_GPR67_GPIO_SD1_RASRCN_SHIFT   (8U)
/*! GPIO_SD1_RASRCN - GPIO_SD_B1 IO bank's 4-bit NMOS compensation codes from core */
#define IOMUXC_GPR_GPR67_GPIO_SD1_RASRCN(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR67_GPIO_SD1_RASRCN_SHIFT)) & IOMUXC_GPR_GPR67_GPIO_SD1_RASRCN_MASK)

#define IOMUXC_GPR_GPR67_GPIO_SD1_SELECT_NASRC_MASK (0x1000U)
#define IOMUXC_GPR_GPR67_GPIO_SD1_SELECT_NASRC_SHIFT (12U)
/*! GPIO_SD1_SELECT_NASRC - GPIO_SD1_NASRC selection */
#define IOMUXC_GPR_GPR67_GPIO_SD1_SELECT_NASRC(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR67_GPIO_SD1_SELECT_NASRC_SHIFT)) & IOMUXC_GPR_GPR67_GPIO_SD1_SELECT_NASRC_MASK)

#define IOMUXC_GPR_GPR67_GPIO_SD1_REFGEN_SLEEP_MASK (0x2000U)
#define IOMUXC_GPR_GPR67_GPIO_SD1_REFGEN_SLEEP_SHIFT (13U)
/*! GPIO_SD1_REFGEN_SLEEP - GPIO_SD_B1 IO bank reference voltage generator cell sleep enable */
#define IOMUXC_GPR_GPR67_GPIO_SD1_REFGEN_SLEEP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR67_GPIO_SD1_REFGEN_SLEEP_SHIFT)) & IOMUXC_GPR_GPR67_GPIO_SD1_REFGEN_SLEEP_MASK)

#define IOMUXC_GPR_GPR67_GPIO_SD1_SUPLYDET_LATCH_MASK (0x4000U)
#define IOMUXC_GPR_GPR67_GPIO_SD1_SUPLYDET_LATCH_SHIFT (14U)
/*! GPIO_SD1_SUPLYDET_LATCH - GPIO_SD_B1 IO bank power supply mode latch enable */
#define IOMUXC_GPR_GPR67_GPIO_SD1_SUPLYDET_LATCH(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR67_GPIO_SD1_SUPLYDET_LATCH_SHIFT)) & IOMUXC_GPR_GPR67_GPIO_SD1_SUPLYDET_LATCH_MASK)

#define IOMUXC_GPR_GPR67_GPIO_SD1_COMPOK_MASK    (0x100000U)
#define IOMUXC_GPR_GPR67_GPIO_SD1_COMPOK_SHIFT   (20U)
/*! GPIO_SD1_COMPOK - GPIO_SD_B1 IO bank compensation OK flag */
#define IOMUXC_GPR_GPR67_GPIO_SD1_COMPOK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR67_GPIO_SD1_COMPOK_SHIFT)) & IOMUXC_GPR_GPR67_GPIO_SD1_COMPOK_MASK)

#define IOMUXC_GPR_GPR67_GPIO_SD1_NASRC_MASK     (0x1E00000U)
#define IOMUXC_GPR_GPR67_GPIO_SD1_NASRC_SHIFT    (21U)
/*! GPIO_SD1_NASRC - GPIO_SD_B1 IO bank compensation codes */
#define IOMUXC_GPR_GPR67_GPIO_SD1_NASRC(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR67_GPIO_SD1_NASRC_SHIFT)) & IOMUXC_GPR_GPR67_GPIO_SD1_NASRC_MASK)

#define IOMUXC_GPR_GPR67_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR67_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR67_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR67_DWP_SHIFT)) & IOMUXC_GPR_GPR67_DWP_MASK)

#define IOMUXC_GPR_GPR67_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR67_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR67_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR67_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR67_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR68 - GPR68 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR68_GPIO_SD2_FREEZE_MASK    (0x1U)
#define IOMUXC_GPR_GPR68_GPIO_SD2_FREEZE_SHIFT   (0U)
/*! GPIO_SD2_FREEZE - Compensation code freeze */
#define IOMUXC_GPR_GPR68_GPIO_SD2_FREEZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR68_GPIO_SD2_FREEZE_SHIFT)) & IOMUXC_GPR_GPR68_GPIO_SD2_FREEZE_MASK)

#define IOMUXC_GPR_GPR68_GPIO_SD2_COMPTQ_MASK    (0x2U)
#define IOMUXC_GPR_GPR68_GPIO_SD2_COMPTQ_SHIFT   (1U)
/*! GPIO_SD2_COMPTQ - COMPEN and COMPTQ control the operating modes of the compensation cell */
#define IOMUXC_GPR_GPR68_GPIO_SD2_COMPTQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR68_GPIO_SD2_COMPTQ_SHIFT)) & IOMUXC_GPR_GPR68_GPIO_SD2_COMPTQ_MASK)

#define IOMUXC_GPR_GPR68_GPIO_SD2_COMPEN_MASK    (0x4U)
#define IOMUXC_GPR_GPR68_GPIO_SD2_COMPEN_SHIFT   (2U)
/*! GPIO_SD2_COMPEN - COMPEN and COMPTQ control the operating modes of the compensation cell */
#define IOMUXC_GPR_GPR68_GPIO_SD2_COMPEN(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR68_GPIO_SD2_COMPEN_SHIFT)) & IOMUXC_GPR_GPR68_GPIO_SD2_COMPEN_MASK)

#define IOMUXC_GPR_GPR68_GPIO_SD2_FASTFRZ_EN_MASK (0x8U)
#define IOMUXC_GPR_GPR68_GPIO_SD2_FASTFRZ_EN_SHIFT (3U)
/*! GPIO_SD2_FASTFRZ_EN - Compensation code fast freeze */
#define IOMUXC_GPR_GPR68_GPIO_SD2_FASTFRZ_EN(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR68_GPIO_SD2_FASTFRZ_EN_SHIFT)) & IOMUXC_GPR_GPR68_GPIO_SD2_FASTFRZ_EN_MASK)

#define IOMUXC_GPR_GPR68_GPIO_SD2_RASRCP_MASK    (0xF0U)
#define IOMUXC_GPR_GPR68_GPIO_SD2_RASRCP_SHIFT   (4U)
/*! GPIO_SD2_RASRCP - GPIO_SD_B2 IO bank's 4-bit PMOS compensation codes from core */
#define IOMUXC_GPR_GPR68_GPIO_SD2_RASRCP(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR68_GPIO_SD2_RASRCP_SHIFT)) & IOMUXC_GPR_GPR68_GPIO_SD2_RASRCP_MASK)

#define IOMUXC_GPR_GPR68_GPIO_SD2_RASRCN_MASK    (0xF00U)
#define IOMUXC_GPR_GPR68_GPIO_SD2_RASRCN_SHIFT   (8U)
/*! GPIO_SD2_RASRCN - GPIO_SD_B2 IO bank's 4-bit NMOS compensation codes from core */
#define IOMUXC_GPR_GPR68_GPIO_SD2_RASRCN(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR68_GPIO_SD2_RASRCN_SHIFT)) & IOMUXC_GPR_GPR68_GPIO_SD2_RASRCN_MASK)

#define IOMUXC_GPR_GPR68_GPIO_SD2_SELECT_NASRC_MASK (0x1000U)
#define IOMUXC_GPR_GPR68_GPIO_SD2_SELECT_NASRC_SHIFT (12U)
/*! GPIO_SD2_SELECT_NASRC - GPIO_SD2_NASRC selection */
#define IOMUXC_GPR_GPR68_GPIO_SD2_SELECT_NASRC(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR68_GPIO_SD2_SELECT_NASRC_SHIFT)) & IOMUXC_GPR_GPR68_GPIO_SD2_SELECT_NASRC_MASK)

#define IOMUXC_GPR_GPR68_GPIO_SD2_REFGEN_SLEEP_MASK (0x2000U)
#define IOMUXC_GPR_GPR68_GPIO_SD2_REFGEN_SLEEP_SHIFT (13U)
/*! GPIO_SD2_REFGEN_SLEEP - GPIO_SD_B2 IO bank reference voltage generator cell sleep enable */
#define IOMUXC_GPR_GPR68_GPIO_SD2_REFGEN_SLEEP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR68_GPIO_SD2_REFGEN_SLEEP_SHIFT)) & IOMUXC_GPR_GPR68_GPIO_SD2_REFGEN_SLEEP_MASK)

#define IOMUXC_GPR_GPR68_GPIO_SD2_SUPLYDET_LATCH_MASK (0x4000U)
#define IOMUXC_GPR_GPR68_GPIO_SD2_SUPLYDET_LATCH_SHIFT (14U)
/*! GPIO_SD2_SUPLYDET_LATCH - GPIO_SD_B2 IO bank power supply mode latch enable */
#define IOMUXC_GPR_GPR68_GPIO_SD2_SUPLYDET_LATCH(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR68_GPIO_SD2_SUPLYDET_LATCH_SHIFT)) & IOMUXC_GPR_GPR68_GPIO_SD2_SUPLYDET_LATCH_MASK)

#define IOMUXC_GPR_GPR68_GPIO_SD2_COMPOK_MASK    (0x100000U)
#define IOMUXC_GPR_GPR68_GPIO_SD2_COMPOK_SHIFT   (20U)
/*! GPIO_SD2_COMPOK - GPIO_SD_B2 IO bank compensation OK flag */
#define IOMUXC_GPR_GPR68_GPIO_SD2_COMPOK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR68_GPIO_SD2_COMPOK_SHIFT)) & IOMUXC_GPR_GPR68_GPIO_SD2_COMPOK_MASK)

#define IOMUXC_GPR_GPR68_GPIO_SD2_NASRC_MASK     (0x1E00000U)
#define IOMUXC_GPR_GPR68_GPIO_SD2_NASRC_SHIFT    (21U)
/*! GPIO_SD2_NASRC - GPIO_SD_B2 IO bank compensation codes */
#define IOMUXC_GPR_GPR68_GPIO_SD2_NASRC(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR68_GPIO_SD2_NASRC_SHIFT)) & IOMUXC_GPR_GPR68_GPIO_SD2_NASRC_MASK)

#define IOMUXC_GPR_GPR68_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR68_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR68_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR68_DWP_SHIFT)) & IOMUXC_GPR_GPR68_DWP_MASK)

#define IOMUXC_GPR_GPR68_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR68_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR68_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR68_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR68_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR69 - GPR69 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR69_GPIO_DISP2_HIGH_RANGE_MASK (0x2U)
#define IOMUXC_GPR_GPR69_GPIO_DISP2_HIGH_RANGE_SHIFT (1U)
/*! GPIO_DISP2_HIGH_RANGE - GPIO_DISP_B2 IO bank supply voltage range selection */
#define IOMUXC_GPR_GPR69_GPIO_DISP2_HIGH_RANGE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR69_GPIO_DISP2_HIGH_RANGE_SHIFT)) & IOMUXC_GPR_GPR69_GPIO_DISP2_HIGH_RANGE_MASK)

#define IOMUXC_GPR_GPR69_GPIO_DISP2_LOW_RANGE_MASK (0x4U)
#define IOMUXC_GPR_GPR69_GPIO_DISP2_LOW_RANGE_SHIFT (2U)
/*! GPIO_DISP2_LOW_RANGE - GPIO_DISP_B2 IO bank supply voltage range selection */
#define IOMUXC_GPR_GPR69_GPIO_DISP2_LOW_RANGE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR69_GPIO_DISP2_LOW_RANGE_SHIFT)) & IOMUXC_GPR_GPR69_GPIO_DISP2_LOW_RANGE_MASK)

#define IOMUXC_GPR_GPR69_GPIO_AD0_HIGH_RANGE_MASK (0x10U)
#define IOMUXC_GPR_GPR69_GPIO_AD0_HIGH_RANGE_SHIFT (4U)
/*! GPIO_AD0_HIGH_RANGE - GPIO_AD IO bank supply voltage range selection for GPIO_AD_00 to GPIO_AD_17 */
#define IOMUXC_GPR_GPR69_GPIO_AD0_HIGH_RANGE(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR69_GPIO_AD0_HIGH_RANGE_SHIFT)) & IOMUXC_GPR_GPR69_GPIO_AD0_HIGH_RANGE_MASK)

#define IOMUXC_GPR_GPR69_GPIO_AD0_LOW_RANGE_MASK (0x20U)
#define IOMUXC_GPR_GPR69_GPIO_AD0_LOW_RANGE_SHIFT (5U)
/*! GPIO_AD0_LOW_RANGE - GPIO_AD IO bank supply voltage range selection for GPIO_AD_00 to GPIO_AD_17 */
#define IOMUXC_GPR_GPR69_GPIO_AD0_LOW_RANGE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR69_GPIO_AD0_LOW_RANGE_SHIFT)) & IOMUXC_GPR_GPR69_GPIO_AD0_LOW_RANGE_MASK)

#define IOMUXC_GPR_GPR69_GPIO_AD1_HIGH_RANGE_MASK (0x80U)
#define IOMUXC_GPR_GPR69_GPIO_AD1_HIGH_RANGE_SHIFT (7U)
/*! GPIO_AD1_HIGH_RANGE - GPIO_LPSR IO bank supply voltage range selection for GPIO_AD_18 to GPIO_AD_35 */
#define IOMUXC_GPR_GPR69_GPIO_AD1_HIGH_RANGE(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR69_GPIO_AD1_HIGH_RANGE_SHIFT)) & IOMUXC_GPR_GPR69_GPIO_AD1_HIGH_RANGE_MASK)

#define IOMUXC_GPR_GPR69_GPIO_AD1_LOW_RANGE_MASK (0x100U)
#define IOMUXC_GPR_GPR69_GPIO_AD1_LOW_RANGE_SHIFT (8U)
/*! GPIO_AD1_LOW_RANGE - GPIO_LPSR IO bank supply voltage range selection for GPIO_AD_18 to GPIO_AD_35 */
#define IOMUXC_GPR_GPR69_GPIO_AD1_LOW_RANGE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR69_GPIO_AD1_LOW_RANGE_SHIFT)) & IOMUXC_GPR_GPR69_GPIO_AD1_LOW_RANGE_MASK)

#define IOMUXC_GPR_GPR69_SUPLYDET_DISP1_SLEEP_MASK (0x200U)
#define IOMUXC_GPR_GPR69_SUPLYDET_DISP1_SLEEP_SHIFT (9U)
/*! SUPLYDET_DISP1_SLEEP - GPIO_DISP_B1 IO bank supply voltage detector sleep mode enable */
#define IOMUXC_GPR_GPR69_SUPLYDET_DISP1_SLEEP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR69_SUPLYDET_DISP1_SLEEP_SHIFT)) & IOMUXC_GPR_GPR69_SUPLYDET_DISP1_SLEEP_MASK)

#define IOMUXC_GPR_GPR69_SUPLYDET_EMC1_SLEEP_MASK (0x400U)
#define IOMUXC_GPR_GPR69_SUPLYDET_EMC1_SLEEP_SHIFT (10U)
/*! SUPLYDET_EMC1_SLEEP - GPIO_EMC_B1 IO bank supply voltage detector sleep mode enable */
#define IOMUXC_GPR_GPR69_SUPLYDET_EMC1_SLEEP(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR69_SUPLYDET_EMC1_SLEEP_SHIFT)) & IOMUXC_GPR_GPR69_SUPLYDET_EMC1_SLEEP_MASK)

#define IOMUXC_GPR_GPR69_SUPLYDET_EMC2_SLEEP_MASK (0x800U)
#define IOMUXC_GPR_GPR69_SUPLYDET_EMC2_SLEEP_SHIFT (11U)
/*! SUPLYDET_EMC2_SLEEP - GPIO_EMC_B2 IO bank supply voltage detector sleep mode enable */
#define IOMUXC_GPR_GPR69_SUPLYDET_EMC2_SLEEP(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR69_SUPLYDET_EMC2_SLEEP_SHIFT)) & IOMUXC_GPR_GPR69_SUPLYDET_EMC2_SLEEP_MASK)

#define IOMUXC_GPR_GPR69_SUPLYDET_SD1_SLEEP_MASK (0x1000U)
#define IOMUXC_GPR_GPR69_SUPLYDET_SD1_SLEEP_SHIFT (12U)
/*! SUPLYDET_SD1_SLEEP - GPIO_SD_B1 IO bank supply voltage detector sleep mode enable */
#define IOMUXC_GPR_GPR69_SUPLYDET_SD1_SLEEP(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR69_SUPLYDET_SD1_SLEEP_SHIFT)) & IOMUXC_GPR_GPR69_SUPLYDET_SD1_SLEEP_MASK)

#define IOMUXC_GPR_GPR69_SUPLYDET_SD2_SLEEP_MASK (0x2000U)
#define IOMUXC_GPR_GPR69_SUPLYDET_SD2_SLEEP_SHIFT (13U)
/*! SUPLYDET_SD2_SLEEP - GPIO_SD_B2 IO bank supply voltage detector sleep mode enable */
#define IOMUXC_GPR_GPR69_SUPLYDET_SD2_SLEEP(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR69_SUPLYDET_SD2_SLEEP_SHIFT)) & IOMUXC_GPR_GPR69_SUPLYDET_SD2_SLEEP_MASK)

#define IOMUXC_GPR_GPR69_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR69_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR69_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR69_DWP_SHIFT)) & IOMUXC_GPR_GPR69_DWP_MASK)

#define IOMUXC_GPR_GPR69_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR69_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR69_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR69_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR69_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR70 - GPR70 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR70_ADC1_IPG_DOZE_MASK      (0x1U)
#define IOMUXC_GPR_GPR70_ADC1_IPG_DOZE_SHIFT     (0U)
/*! ADC1_IPG_DOZE - ADC1 doze mode */
#define IOMUXC_GPR_GPR70_ADC1_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_ADC1_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR70_ADC1_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR70_ADC1_STOP_REQ_MASK      (0x2U)
#define IOMUXC_GPR_GPR70_ADC1_STOP_REQ_SHIFT     (1U)
/*! ADC1_STOP_REQ - ADC1 stop request */
#define IOMUXC_GPR_GPR70_ADC1_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_ADC1_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR70_ADC1_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR70_ADC1_IPG_STOP_MODE_MASK (0x4U)
#define IOMUXC_GPR_GPR70_ADC1_IPG_STOP_MODE_SHIFT (2U)
/*! ADC1_IPG_STOP_MODE - ADC1 stop mode selection, cannot change when ADC1_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR70_ADC1_IPG_STOP_MODE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_ADC1_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR70_ADC1_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR70_ADC2_IPG_DOZE_MASK      (0x8U)
#define IOMUXC_GPR_GPR70_ADC2_IPG_DOZE_SHIFT     (3U)
/*! ADC2_IPG_DOZE - ADC2 doze mode */
#define IOMUXC_GPR_GPR70_ADC2_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_ADC2_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR70_ADC2_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR70_ADC2_STOP_REQ_MASK      (0x10U)
#define IOMUXC_GPR_GPR70_ADC2_STOP_REQ_SHIFT     (4U)
/*! ADC2_STOP_REQ - ADC2 stop request */
#define IOMUXC_GPR_GPR70_ADC2_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_ADC2_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR70_ADC2_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR70_ADC2_IPG_STOP_MODE_MASK (0x20U)
#define IOMUXC_GPR_GPR70_ADC2_IPG_STOP_MODE_SHIFT (5U)
/*! ADC2_IPG_STOP_MODE - ADC2 stop mode selection, cannot change when ADC2_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR70_ADC2_IPG_STOP_MODE(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_ADC2_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR70_ADC2_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR70_CAAM_IPG_DOZE_MASK      (0x40U)
#define IOMUXC_GPR_GPR70_CAAM_IPG_DOZE_SHIFT     (6U)
/*! CAAM_IPG_DOZE - CAN3 doze mode */
#define IOMUXC_GPR_GPR70_CAAM_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_CAAM_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR70_CAAM_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR70_CAAM_STOP_REQ_MASK      (0x80U)
#define IOMUXC_GPR_GPR70_CAAM_STOP_REQ_SHIFT     (7U)
/*! CAAM_STOP_REQ - CAAM stop request */
#define IOMUXC_GPR_GPR70_CAAM_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_CAAM_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR70_CAAM_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR70_CAN1_IPG_DOZE_MASK      (0x100U)
#define IOMUXC_GPR_GPR70_CAN1_IPG_DOZE_SHIFT     (8U)
/*! CAN1_IPG_DOZE - CAN1 doze mode */
#define IOMUXC_GPR_GPR70_CAN1_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_CAN1_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR70_CAN1_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR70_CAN1_STOP_REQ_MASK      (0x200U)
#define IOMUXC_GPR_GPR70_CAN1_STOP_REQ_SHIFT     (9U)
/*! CAN1_STOP_REQ - CAN1 stop request */
#define IOMUXC_GPR_GPR70_CAN1_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_CAN1_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR70_CAN1_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR70_CAN2_IPG_DOZE_MASK      (0x400U)
#define IOMUXC_GPR_GPR70_CAN2_IPG_DOZE_SHIFT     (10U)
/*! CAN2_IPG_DOZE - CAN2 doze mode */
#define IOMUXC_GPR_GPR70_CAN2_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_CAN2_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR70_CAN2_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR70_CAN2_STOP_REQ_MASK      (0x800U)
#define IOMUXC_GPR_GPR70_CAN2_STOP_REQ_SHIFT     (11U)
/*! CAN2_STOP_REQ - CAN2 stop request */
#define IOMUXC_GPR_GPR70_CAN2_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_CAN2_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR70_CAN2_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR70_CAN3_IPG_DOZE_MASK      (0x1000U)
#define IOMUXC_GPR_GPR70_CAN3_IPG_DOZE_SHIFT     (12U)
/*! CAN3_IPG_DOZE - CAN3 doze mode */
#define IOMUXC_GPR_GPR70_CAN3_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_CAN3_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR70_CAN3_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR70_CAN3_STOP_REQ_MASK      (0x2000U)
#define IOMUXC_GPR_GPR70_CAN3_STOP_REQ_SHIFT     (13U)
/*! CAN3_STOP_REQ - CAN3 stop request */
#define IOMUXC_GPR_GPR70_CAN3_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_CAN3_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR70_CAN3_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR70_EDMA_STOP_REQ_MASK      (0x8000U)
#define IOMUXC_GPR_GPR70_EDMA_STOP_REQ_SHIFT     (15U)
/*! EDMA_STOP_REQ - EDMA stop request */
#define IOMUXC_GPR_GPR70_EDMA_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_EDMA_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR70_EDMA_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR70_EDMA_LPSR_STOP_REQ_MASK (0x10000U)
#define IOMUXC_GPR_GPR70_EDMA_LPSR_STOP_REQ_SHIFT (16U)
/*! EDMA_LPSR_STOP_REQ - EDMA_LPSR stop request */
#define IOMUXC_GPR_GPR70_EDMA_LPSR_STOP_REQ(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_EDMA_LPSR_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR70_EDMA_LPSR_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR70_ENET_IPG_DOZE_MASK      (0x20000U)
#define IOMUXC_GPR_GPR70_ENET_IPG_DOZE_SHIFT     (17U)
/*! ENET_IPG_DOZE - ENET doze mode */
#define IOMUXC_GPR_GPR70_ENET_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_ENET_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR70_ENET_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR70_ENET_STOP_REQ_MASK      (0x40000U)
#define IOMUXC_GPR_GPR70_ENET_STOP_REQ_SHIFT     (18U)
/*! ENET_STOP_REQ - ENET stop request */
#define IOMUXC_GPR_GPR70_ENET_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_ENET_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR70_ENET_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR70_ENET1G_IPG_DOZE_MASK    (0x80000U)
#define IOMUXC_GPR_GPR70_ENET1G_IPG_DOZE_SHIFT   (19U)
/*! ENET1G_IPG_DOZE - ENET1G doze mode */
#define IOMUXC_GPR_GPR70_ENET1G_IPG_DOZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_ENET1G_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR70_ENET1G_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR70_ENET1G_STOP_REQ_MASK    (0x100000U)
#define IOMUXC_GPR_GPR70_ENET1G_STOP_REQ_SHIFT   (20U)
/*! ENET1G_STOP_REQ - ENET1G stop request */
#define IOMUXC_GPR_GPR70_ENET1G_STOP_REQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_ENET1G_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR70_ENET1G_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR70_FLEXIO1_IPG_DOZE_MASK   (0x200000U)
#define IOMUXC_GPR_GPR70_FLEXIO1_IPG_DOZE_SHIFT  (21U)
/*! FLEXIO1_IPG_DOZE - FLEXIO2 doze mode */
#define IOMUXC_GPR_GPR70_FLEXIO1_IPG_DOZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_FLEXIO1_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR70_FLEXIO1_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR70_FLEXIO2_IPG_DOZE_MASK   (0x400000U)
#define IOMUXC_GPR_GPR70_FLEXIO2_IPG_DOZE_SHIFT  (22U)
/*! FLEXIO2_IPG_DOZE - FLEXIO2 doze mode */
#define IOMUXC_GPR_GPR70_FLEXIO2_IPG_DOZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_FLEXIO2_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR70_FLEXIO2_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR70_FLEXSPI1_IPG_DOZE_MASK  (0x800000U)
#define IOMUXC_GPR_GPR70_FLEXSPI1_IPG_DOZE_SHIFT (23U)
/*! FLEXSPI1_IPG_DOZE - FLEXSPI1 doze mode */
#define IOMUXC_GPR_GPR70_FLEXSPI1_IPG_DOZE(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_FLEXSPI1_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR70_FLEXSPI1_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR70_FLEXSPI1_STOP_REQ_MASK  (0x1000000U)
#define IOMUXC_GPR_GPR70_FLEXSPI1_STOP_REQ_SHIFT (24U)
/*! FLEXSPI1_STOP_REQ - FLEXSPI1 stop request */
#define IOMUXC_GPR_GPR70_FLEXSPI1_STOP_REQ(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_FLEXSPI1_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR70_FLEXSPI1_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR70_FLEXSPI2_IPG_DOZE_MASK  (0x2000000U)
#define IOMUXC_GPR_GPR70_FLEXSPI2_IPG_DOZE_SHIFT (25U)
/*! FLEXSPI2_IPG_DOZE - FLEXSPI2 doze mode */
#define IOMUXC_GPR_GPR70_FLEXSPI2_IPG_DOZE(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_FLEXSPI2_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR70_FLEXSPI2_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR70_FLEXSPI2_STOP_REQ_MASK  (0x4000000U)
#define IOMUXC_GPR_GPR70_FLEXSPI2_STOP_REQ_SHIFT (26U)
/*! FLEXSPI2_STOP_REQ - FLEXSPI2 stop request */
#define IOMUXC_GPR_GPR70_FLEXSPI2_STOP_REQ(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_FLEXSPI2_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR70_FLEXSPI2_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR70_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR70_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR70_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_DWP_SHIFT)) & IOMUXC_GPR_GPR70_DWP_MASK)

#define IOMUXC_GPR_GPR70_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR70_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR70_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR70_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR70_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR71 - GPR71 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR71_GPT1_IPG_DOZE_MASK      (0x1U)
#define IOMUXC_GPR_GPR71_GPT1_IPG_DOZE_SHIFT     (0U)
/*! GPT1_IPG_DOZE - GPT1 doze mode */
#define IOMUXC_GPR_GPR71_GPT1_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_GPT1_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR71_GPT1_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR71_GPT2_IPG_DOZE_MASK      (0x2U)
#define IOMUXC_GPR_GPR71_GPT2_IPG_DOZE_SHIFT     (1U)
/*! GPT2_IPG_DOZE - GPT2 doze mode */
#define IOMUXC_GPR_GPR71_GPT2_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_GPT2_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR71_GPT2_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR71_GPT3_IPG_DOZE_MASK      (0x4U)
#define IOMUXC_GPR_GPR71_GPT3_IPG_DOZE_SHIFT     (2U)
/*! GPT3_IPG_DOZE - GPT3 doze mode */
#define IOMUXC_GPR_GPR71_GPT3_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_GPT3_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR71_GPT3_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR71_GPT4_IPG_DOZE_MASK      (0x8U)
#define IOMUXC_GPR_GPR71_GPT4_IPG_DOZE_SHIFT     (3U)
/*! GPT4_IPG_DOZE - GPT4 doze mode */
#define IOMUXC_GPR_GPR71_GPT4_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_GPT4_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR71_GPT4_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR71_GPT5_IPG_DOZE_MASK      (0x10U)
#define IOMUXC_GPR_GPR71_GPT5_IPG_DOZE_SHIFT     (4U)
/*! GPT5_IPG_DOZE - GPT5 doze mode */
#define IOMUXC_GPR_GPR71_GPT5_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_GPT5_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR71_GPT5_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR71_GPT6_IPG_DOZE_MASK      (0x20U)
#define IOMUXC_GPR_GPR71_GPT6_IPG_DOZE_SHIFT     (5U)
/*! GPT6_IPG_DOZE - GPT6 doze mode */
#define IOMUXC_GPR_GPR71_GPT6_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_GPT6_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR71_GPT6_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR71_LPI2C1_IPG_DOZE_MASK    (0x40U)
#define IOMUXC_GPR_GPR71_LPI2C1_IPG_DOZE_SHIFT   (6U)
/*! LPI2C1_IPG_DOZE - LPI2C1 doze mode */
#define IOMUXC_GPR_GPR71_LPI2C1_IPG_DOZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C1_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C1_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR71_LPI2C1_STOP_REQ_MASK    (0x80U)
#define IOMUXC_GPR_GPR71_LPI2C1_STOP_REQ_SHIFT   (7U)
/*! LPI2C1_STOP_REQ - LPI2C1 stop request */
#define IOMUXC_GPR_GPR71_LPI2C1_STOP_REQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C1_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C1_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR71_LPI2C1_IPG_STOP_MODE_MASK (0x100U)
#define IOMUXC_GPR_GPR71_LPI2C1_IPG_STOP_MODE_SHIFT (8U)
/*! LPI2C1_IPG_STOP_MODE - LPI2C1 stop mode selection, cannot change when LPI2C1_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR71_LPI2C1_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C1_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C1_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR71_LPI2C2_IPG_DOZE_MASK    (0x200U)
#define IOMUXC_GPR_GPR71_LPI2C2_IPG_DOZE_SHIFT   (9U)
/*! LPI2C2_IPG_DOZE - LPI2C2 doze mode */
#define IOMUXC_GPR_GPR71_LPI2C2_IPG_DOZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C2_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C2_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR71_LPI2C2_STOP_REQ_MASK    (0x400U)
#define IOMUXC_GPR_GPR71_LPI2C2_STOP_REQ_SHIFT   (10U)
/*! LPI2C2_STOP_REQ - LPI2C2 stop request */
#define IOMUXC_GPR_GPR71_LPI2C2_STOP_REQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C2_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C2_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR71_LPI2C2_IPG_STOP_MODE_MASK (0x800U)
#define IOMUXC_GPR_GPR71_LPI2C2_IPG_STOP_MODE_SHIFT (11U)
/*! LPI2C2_IPG_STOP_MODE - LPI2C2 stop mode selection, cannot change when LPI2C2_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR71_LPI2C2_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C2_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C2_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR71_LPI2C3_IPG_DOZE_MASK    (0x1000U)
#define IOMUXC_GPR_GPR71_LPI2C3_IPG_DOZE_SHIFT   (12U)
/*! LPI2C3_IPG_DOZE - LPI2C3 doze mode */
#define IOMUXC_GPR_GPR71_LPI2C3_IPG_DOZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C3_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C3_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR71_LPI2C3_STOP_REQ_MASK    (0x2000U)
#define IOMUXC_GPR_GPR71_LPI2C3_STOP_REQ_SHIFT   (13U)
/*! LPI2C3_STOP_REQ - LPI2C3 stop request */
#define IOMUXC_GPR_GPR71_LPI2C3_STOP_REQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C3_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C3_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR71_LPI2C3_IPG_STOP_MODE_MASK (0x4000U)
#define IOMUXC_GPR_GPR71_LPI2C3_IPG_STOP_MODE_SHIFT (14U)
/*! LPI2C3_IPG_STOP_MODE - LPI2C3 stop mode selection, cannot change when LPI2C3_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR71_LPI2C3_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C3_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C3_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR71_LPI2C4_IPG_DOZE_MASK    (0x8000U)
#define IOMUXC_GPR_GPR71_LPI2C4_IPG_DOZE_SHIFT   (15U)
/*! LPI2C4_IPG_DOZE - LPI2C4 doze mode */
#define IOMUXC_GPR_GPR71_LPI2C4_IPG_DOZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C4_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C4_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR71_LPI2C4_STOP_REQ_MASK    (0x10000U)
#define IOMUXC_GPR_GPR71_LPI2C4_STOP_REQ_SHIFT   (16U)
/*! LPI2C4_STOP_REQ - LPI2C4 stop request */
#define IOMUXC_GPR_GPR71_LPI2C4_STOP_REQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C4_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C4_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR71_LPI2C4_IPG_STOP_MODE_MASK (0x20000U)
#define IOMUXC_GPR_GPR71_LPI2C4_IPG_STOP_MODE_SHIFT (17U)
/*! LPI2C4_IPG_STOP_MODE - LPI2C4 stop mode selection, cannot change when LPI2C4_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR71_LPI2C4_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C4_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C4_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR71_LPI2C5_IPG_DOZE_MASK    (0x40000U)
#define IOMUXC_GPR_GPR71_LPI2C5_IPG_DOZE_SHIFT   (18U)
/*! LPI2C5_IPG_DOZE - LPI2C5 doze mode */
#define IOMUXC_GPR_GPR71_LPI2C5_IPG_DOZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C5_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C5_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR71_LPI2C5_STOP_REQ_MASK    (0x80000U)
#define IOMUXC_GPR_GPR71_LPI2C5_STOP_REQ_SHIFT   (19U)
/*! LPI2C5_STOP_REQ - LPI2C5 stop request */
#define IOMUXC_GPR_GPR71_LPI2C5_STOP_REQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C5_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C5_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR71_LPI2C5_IPG_STOP_MODE_MASK (0x100000U)
#define IOMUXC_GPR_GPR71_LPI2C5_IPG_STOP_MODE_SHIFT (20U)
/*! LPI2C5_IPG_STOP_MODE - LPI2C5 stop mode selection, cannot change when LPI2C5_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR71_LPI2C5_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C5_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C5_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR71_LPI2C6_IPG_DOZE_MASK    (0x200000U)
#define IOMUXC_GPR_GPR71_LPI2C6_IPG_DOZE_SHIFT   (21U)
/*! LPI2C6_IPG_DOZE - LPI2C6 doze mode */
#define IOMUXC_GPR_GPR71_LPI2C6_IPG_DOZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C6_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C6_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR71_LPI2C6_STOP_REQ_MASK    (0x400000U)
#define IOMUXC_GPR_GPR71_LPI2C6_STOP_REQ_SHIFT   (22U)
/*! LPI2C6_STOP_REQ - LPI2C6 stop request */
#define IOMUXC_GPR_GPR71_LPI2C6_STOP_REQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C6_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C6_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR71_LPI2C6_IPG_STOP_MODE_MASK (0x800000U)
#define IOMUXC_GPR_GPR71_LPI2C6_IPG_STOP_MODE_SHIFT (23U)
/*! LPI2C6_IPG_STOP_MODE - LPI2C6 stop mode selection, cannot change when LPI2C6_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR71_LPI2C6_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPI2C6_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR71_LPI2C6_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR71_LPSPI1_IPG_DOZE_MASK    (0x1000000U)
#define IOMUXC_GPR_GPR71_LPSPI1_IPG_DOZE_SHIFT   (24U)
/*! LPSPI1_IPG_DOZE - LPSPI1 doze mode */
#define IOMUXC_GPR_GPR71_LPSPI1_IPG_DOZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPSPI1_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR71_LPSPI1_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR71_LPSPI1_STOP_REQ_MASK    (0x2000000U)
#define IOMUXC_GPR_GPR71_LPSPI1_STOP_REQ_SHIFT   (25U)
/*! LPSPI1_STOP_REQ - LPSPI1 stop request */
#define IOMUXC_GPR_GPR71_LPSPI1_STOP_REQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPSPI1_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR71_LPSPI1_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR71_LPSPI1_IPG_STOP_MODE_MASK (0x4000000U)
#define IOMUXC_GPR_GPR71_LPSPI1_IPG_STOP_MODE_SHIFT (26U)
/*! LPSPI1_IPG_STOP_MODE - LPSPI1 stop mode selection, cannot change when LPSPI1_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR71_LPSPI1_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_LPSPI1_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR71_LPSPI1_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR71_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR71_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR71_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_DWP_SHIFT)) & IOMUXC_GPR_GPR71_DWP_MASK)

#define IOMUXC_GPR_GPR71_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR71_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR71_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR71_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR71_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR72 - GPR72 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR72_LPSPI2_IPG_DOZE_MASK    (0x1U)
#define IOMUXC_GPR_GPR72_LPSPI2_IPG_DOZE_SHIFT   (0U)
/*! LPSPI2_IPG_DOZE - LPSPI2 doze mode */
#define IOMUXC_GPR_GPR72_LPSPI2_IPG_DOZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI2_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI2_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR72_LPSPI2_STOP_REQ_MASK    (0x2U)
#define IOMUXC_GPR_GPR72_LPSPI2_STOP_REQ_SHIFT   (1U)
/*! LPSPI2_STOP_REQ - LPSPI2 stop request */
#define IOMUXC_GPR_GPR72_LPSPI2_STOP_REQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI2_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI2_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR72_LPSPI2_IPG_STOP_MODE_MASK (0x4U)
#define IOMUXC_GPR_GPR72_LPSPI2_IPG_STOP_MODE_SHIFT (2U)
/*! LPSPI2_IPG_STOP_MODE - LPSPI2 stop mode selection, cannot change when LPSPI2_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR72_LPSPI2_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI2_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI2_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR72_LPSPI3_IPG_DOZE_MASK    (0x8U)
#define IOMUXC_GPR_GPR72_LPSPI3_IPG_DOZE_SHIFT   (3U)
/*! LPSPI3_IPG_DOZE - LPSPI3 doze mode */
#define IOMUXC_GPR_GPR72_LPSPI3_IPG_DOZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI3_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI3_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR72_LPSPI3_STOP_REQ_MASK    (0x10U)
#define IOMUXC_GPR_GPR72_LPSPI3_STOP_REQ_SHIFT   (4U)
/*! LPSPI3_STOP_REQ - LPSPI3 stop request */
#define IOMUXC_GPR_GPR72_LPSPI3_STOP_REQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI3_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI3_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR72_LPSPI3_IPG_STOP_MODE_MASK (0x20U)
#define IOMUXC_GPR_GPR72_LPSPI3_IPG_STOP_MODE_SHIFT (5U)
/*! LPSPI3_IPG_STOP_MODE - LPSPI3 stop mode selection, cannot change when LPSPI3_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR72_LPSPI3_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI3_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI3_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR72_LPSPI4_IPG_DOZE_MASK    (0x40U)
#define IOMUXC_GPR_GPR72_LPSPI4_IPG_DOZE_SHIFT   (6U)
/*! LPSPI4_IPG_DOZE - LPSPI4 doze mode */
#define IOMUXC_GPR_GPR72_LPSPI4_IPG_DOZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI4_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI4_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR72_LPSPI4_STOP_REQ_MASK    (0x80U)
#define IOMUXC_GPR_GPR72_LPSPI4_STOP_REQ_SHIFT   (7U)
/*! LPSPI4_STOP_REQ - LPSPI4 stop request */
#define IOMUXC_GPR_GPR72_LPSPI4_STOP_REQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI4_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI4_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR72_LPSPI4_IPG_STOP_MODE_MASK (0x100U)
#define IOMUXC_GPR_GPR72_LPSPI4_IPG_STOP_MODE_SHIFT (8U)
/*! LPSPI4_IPG_STOP_MODE - LPSPI4 stop mode selection, cannot change when LPSPI4_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR72_LPSPI4_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI4_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI4_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR72_LPSPI5_IPG_DOZE_MASK    (0x200U)
#define IOMUXC_GPR_GPR72_LPSPI5_IPG_DOZE_SHIFT   (9U)
/*! LPSPI5_IPG_DOZE - LPSPI5 doze mode */
#define IOMUXC_GPR_GPR72_LPSPI5_IPG_DOZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI5_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI5_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR72_LPSPI5_STOP_REQ_MASK    (0x400U)
#define IOMUXC_GPR_GPR72_LPSPI5_STOP_REQ_SHIFT   (10U)
/*! LPSPI5_STOP_REQ - LPSPI5 stop request */
#define IOMUXC_GPR_GPR72_LPSPI5_STOP_REQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI5_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI5_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR72_LPSPI5_IPG_STOP_MODE_MASK (0x800U)
#define IOMUXC_GPR_GPR72_LPSPI5_IPG_STOP_MODE_SHIFT (11U)
/*! LPSPI5_IPG_STOP_MODE - LPSPI5 stop mode selection, cannot change when LPSPI5_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR72_LPSPI5_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI5_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI5_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR72_LPSPI6_IPG_DOZE_MASK    (0x1000U)
#define IOMUXC_GPR_GPR72_LPSPI6_IPG_DOZE_SHIFT   (12U)
/*! LPSPI6_IPG_DOZE - LPSPI6 doze mode */
#define IOMUXC_GPR_GPR72_LPSPI6_IPG_DOZE(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI6_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI6_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR72_LPSPI6_STOP_REQ_MASK    (0x2000U)
#define IOMUXC_GPR_GPR72_LPSPI6_STOP_REQ_SHIFT   (13U)
/*! LPSPI6_STOP_REQ - LPSPI6 stop request */
#define IOMUXC_GPR_GPR72_LPSPI6_STOP_REQ(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI6_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI6_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR72_LPSPI6_IPG_STOP_MODE_MASK (0x4000U)
#define IOMUXC_GPR_GPR72_LPSPI6_IPG_STOP_MODE_SHIFT (14U)
/*! LPSPI6_IPG_STOP_MODE - LPSPI6 stop mode selection, cannot change when LPSPI6_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR72_LPSPI6_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPSPI6_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR72_LPSPI6_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR72_LPUART1_IPG_DOZE_MASK   (0x8000U)
#define IOMUXC_GPR_GPR72_LPUART1_IPG_DOZE_SHIFT  (15U)
/*! LPUART1_IPG_DOZE - LPUART1 doze mode */
#define IOMUXC_GPR_GPR72_LPUART1_IPG_DOZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPUART1_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR72_LPUART1_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR72_LPUART1_STOP_REQ_MASK   (0x10000U)
#define IOMUXC_GPR_GPR72_LPUART1_STOP_REQ_SHIFT  (16U)
/*! LPUART1_STOP_REQ - LPUART1 stop request */
#define IOMUXC_GPR_GPR72_LPUART1_STOP_REQ(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPUART1_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR72_LPUART1_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR72_LPUART1_IPG_STOP_MODE_MASK (0x20000U)
#define IOMUXC_GPR_GPR72_LPUART1_IPG_STOP_MODE_SHIFT (17U)
/*! LPUART1_IPG_STOP_MODE - LPUART1 stop mode selection, cannot change when LPUART1_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR72_LPUART1_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPUART1_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR72_LPUART1_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR72_LPUART2_IPG_DOZE_MASK   (0x40000U)
#define IOMUXC_GPR_GPR72_LPUART2_IPG_DOZE_SHIFT  (18U)
/*! LPUART2_IPG_DOZE - LPUART2 doze mode */
#define IOMUXC_GPR_GPR72_LPUART2_IPG_DOZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPUART2_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR72_LPUART2_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR72_LPUART2_STOP_REQ_MASK   (0x80000U)
#define IOMUXC_GPR_GPR72_LPUART2_STOP_REQ_SHIFT  (19U)
/*! LPUART2_STOP_REQ - LPUART2 stop request */
#define IOMUXC_GPR_GPR72_LPUART2_STOP_REQ(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPUART2_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR72_LPUART2_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR72_LPUART2_IPG_STOP_MODE_MASK (0x100000U)
#define IOMUXC_GPR_GPR72_LPUART2_IPG_STOP_MODE_SHIFT (20U)
/*! LPUART2_IPG_STOP_MODE - LPUART2 stop mode selection, cannot change when LPUART2_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR72_LPUART2_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPUART2_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR72_LPUART2_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR72_LPUART3_IPG_DOZE_MASK   (0x200000U)
#define IOMUXC_GPR_GPR72_LPUART3_IPG_DOZE_SHIFT  (21U)
/*! LPUART3_IPG_DOZE - LPUART3 doze mode */
#define IOMUXC_GPR_GPR72_LPUART3_IPG_DOZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPUART3_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR72_LPUART3_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR72_LPUART3_STOP_REQ_MASK   (0x400000U)
#define IOMUXC_GPR_GPR72_LPUART3_STOP_REQ_SHIFT  (22U)
/*! LPUART3_STOP_REQ - LPUART3 stop request */
#define IOMUXC_GPR_GPR72_LPUART3_STOP_REQ(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPUART3_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR72_LPUART3_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR72_LPUART3_IPG_STOP_MODE_MASK (0x800000U)
#define IOMUXC_GPR_GPR72_LPUART3_IPG_STOP_MODE_SHIFT (23U)
/*! LPUART3_IPG_STOP_MODE - LPUART3 stop mode selection, cannot change when LPUART3_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR72_LPUART3_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPUART3_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR72_LPUART3_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR72_LPUART4_IPG_DOZE_MASK   (0x1000000U)
#define IOMUXC_GPR_GPR72_LPUART4_IPG_DOZE_SHIFT  (24U)
/*! LPUART4_IPG_DOZE - LPUART4 doze mode */
#define IOMUXC_GPR_GPR72_LPUART4_IPG_DOZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPUART4_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR72_LPUART4_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR72_LPUART4_STOP_REQ_MASK   (0x2000000U)
#define IOMUXC_GPR_GPR72_LPUART4_STOP_REQ_SHIFT  (25U)
/*! LPUART4_STOP_REQ - LPUART4 stop request */
#define IOMUXC_GPR_GPR72_LPUART4_STOP_REQ(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPUART4_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR72_LPUART4_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR72_LPUART4_IPG_STOP_MODE_MASK (0x4000000U)
#define IOMUXC_GPR_GPR72_LPUART4_IPG_STOP_MODE_SHIFT (26U)
/*! LPUART4_IPG_STOP_MODE - LPUART4 stop mode selection, cannot change when LPUART4_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR72_LPUART4_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_LPUART4_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR72_LPUART4_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR72_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR72_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR72_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_DWP_SHIFT)) & IOMUXC_GPR_GPR72_DWP_MASK)

#define IOMUXC_GPR_GPR72_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR72_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR72_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR72_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR72_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR73 - GPR73 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR73_LPUART5_IPG_DOZE_MASK   (0x1U)
#define IOMUXC_GPR_GPR73_LPUART5_IPG_DOZE_SHIFT  (0U)
/*! LPUART5_IPG_DOZE - LPUART5 doze mode */
#define IOMUXC_GPR_GPR73_LPUART5_IPG_DOZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART5_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART5_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR73_LPUART5_STOP_REQ_MASK   (0x2U)
#define IOMUXC_GPR_GPR73_LPUART5_STOP_REQ_SHIFT  (1U)
/*! LPUART5_STOP_REQ - LPUART5 stop request */
#define IOMUXC_GPR_GPR73_LPUART5_STOP_REQ(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART5_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR73_LPUART5_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR73_LPUART5_IPG_STOP_MODE_MASK (0x4U)
#define IOMUXC_GPR_GPR73_LPUART5_IPG_STOP_MODE_SHIFT (2U)
/*! LPUART5_IPG_STOP_MODE - LPUART5 stop mode selection, cannot change when LPUART5_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR73_LPUART5_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART5_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART5_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR73_LPUART6_IPG_DOZE_MASK   (0x8U)
#define IOMUXC_GPR_GPR73_LPUART6_IPG_DOZE_SHIFT  (3U)
/*! LPUART6_IPG_DOZE - LPUART6 doze mode */
#define IOMUXC_GPR_GPR73_LPUART6_IPG_DOZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART6_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART6_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR73_LPUART6_STOP_REQ_MASK   (0x10U)
#define IOMUXC_GPR_GPR73_LPUART6_STOP_REQ_SHIFT  (4U)
/*! LPUART6_STOP_REQ - LPUART6 stop request */
#define IOMUXC_GPR_GPR73_LPUART6_STOP_REQ(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART6_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR73_LPUART6_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR73_LPUART6_IPG_STOP_MODE_MASK (0x20U)
#define IOMUXC_GPR_GPR73_LPUART6_IPG_STOP_MODE_SHIFT (5U)
/*! LPUART6_IPG_STOP_MODE - LPUART6 stop mode selection, cannot change when LPUART6_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR73_LPUART6_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART6_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART6_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR73_LPUART7_IPG_DOZE_MASK   (0x40U)
#define IOMUXC_GPR_GPR73_LPUART7_IPG_DOZE_SHIFT  (6U)
/*! LPUART7_IPG_DOZE - LPUART7 doze mode */
#define IOMUXC_GPR_GPR73_LPUART7_IPG_DOZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART7_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART7_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR73_LPUART7_STOP_REQ_MASK   (0x80U)
#define IOMUXC_GPR_GPR73_LPUART7_STOP_REQ_SHIFT  (7U)
/*! LPUART7_STOP_REQ - LPUART7 stop request */
#define IOMUXC_GPR_GPR73_LPUART7_STOP_REQ(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART7_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR73_LPUART7_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR73_LPUART7_IPG_STOP_MODE_MASK (0x100U)
#define IOMUXC_GPR_GPR73_LPUART7_IPG_STOP_MODE_SHIFT (8U)
/*! LPUART7_IPG_STOP_MODE - LPUART7 stop mode selection, cannot change when LPUART7_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR73_LPUART7_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART7_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART7_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR73_LPUART8_IPG_DOZE_MASK   (0x200U)
#define IOMUXC_GPR_GPR73_LPUART8_IPG_DOZE_SHIFT  (9U)
/*! LPUART8_IPG_DOZE - LPUART8 doze mode */
#define IOMUXC_GPR_GPR73_LPUART8_IPG_DOZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART8_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART8_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR73_LPUART8_STOP_REQ_MASK   (0x400U)
#define IOMUXC_GPR_GPR73_LPUART8_STOP_REQ_SHIFT  (10U)
/*! LPUART8_STOP_REQ - LPUART8 stop request */
#define IOMUXC_GPR_GPR73_LPUART8_STOP_REQ(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART8_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR73_LPUART8_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR73_LPUART8_IPG_STOP_MODE_MASK (0x800U)
#define IOMUXC_GPR_GPR73_LPUART8_IPG_STOP_MODE_SHIFT (11U)
/*! LPUART8_IPG_STOP_MODE - LPUART8 stop mode selection, cannot change when LPUART8_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR73_LPUART8_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART8_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART8_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR73_LPUART9_IPG_DOZE_MASK   (0x1000U)
#define IOMUXC_GPR_GPR73_LPUART9_IPG_DOZE_SHIFT  (12U)
/*! LPUART9_IPG_DOZE - LPUART9 doze mode */
#define IOMUXC_GPR_GPR73_LPUART9_IPG_DOZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART9_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART9_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR73_LPUART9_STOP_REQ_MASK   (0x2000U)
#define IOMUXC_GPR_GPR73_LPUART9_STOP_REQ_SHIFT  (13U)
/*! LPUART9_STOP_REQ - LPUART9 stop request */
#define IOMUXC_GPR_GPR73_LPUART9_STOP_REQ(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART9_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR73_LPUART9_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR73_LPUART9_IPG_STOP_MODE_MASK (0x4000U)
#define IOMUXC_GPR_GPR73_LPUART9_IPG_STOP_MODE_SHIFT (14U)
/*! LPUART9_IPG_STOP_MODE - LPUART9 stop mode selection, cannot change when LPUART9_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR73_LPUART9_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART9_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART9_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR73_LPUART10_IPG_DOZE_MASK  (0x8000U)
#define IOMUXC_GPR_GPR73_LPUART10_IPG_DOZE_SHIFT (15U)
/*! LPUART10_IPG_DOZE - LPUART10 doze mode */
#define IOMUXC_GPR_GPR73_LPUART10_IPG_DOZE(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART10_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART10_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR73_LPUART10_STOP_REQ_MASK  (0x10000U)
#define IOMUXC_GPR_GPR73_LPUART10_STOP_REQ_SHIFT (16U)
/*! LPUART10_STOP_REQ - LPUART10 stop request */
#define IOMUXC_GPR_GPR73_LPUART10_STOP_REQ(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART10_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR73_LPUART10_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR73_LPUART10_IPG_STOP_MODE_MASK (0x20000U)
#define IOMUXC_GPR_GPR73_LPUART10_IPG_STOP_MODE_SHIFT (17U)
/*! LPUART10_IPG_STOP_MODE - LPUART10 stop mode selection, cannot change when LPUART10_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR73_LPUART10_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART10_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART10_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR73_LPUART11_IPG_DOZE_MASK  (0x40000U)
#define IOMUXC_GPR_GPR73_LPUART11_IPG_DOZE_SHIFT (18U)
/*! LPUART11_IPG_DOZE - LPUART11 doze mode */
#define IOMUXC_GPR_GPR73_LPUART11_IPG_DOZE(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART11_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART11_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR73_LPUART11_STOP_REQ_MASK  (0x80000U)
#define IOMUXC_GPR_GPR73_LPUART11_STOP_REQ_SHIFT (19U)
/*! LPUART11_STOP_REQ - LPUART11 stop request */
#define IOMUXC_GPR_GPR73_LPUART11_STOP_REQ(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART11_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR73_LPUART11_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR73_LPUART11_IPG_STOP_MODE_MASK (0x100000U)
#define IOMUXC_GPR_GPR73_LPUART11_IPG_STOP_MODE_SHIFT (20U)
/*! LPUART11_IPG_STOP_MODE - LPUART11 stop mode selection, cannot change when LPUART11_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR73_LPUART11_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART11_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART11_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR73_LPUART12_IPG_DOZE_MASK  (0x200000U)
#define IOMUXC_GPR_GPR73_LPUART12_IPG_DOZE_SHIFT (21U)
/*! LPUART12_IPG_DOZE - LPUART12 doze mode */
#define IOMUXC_GPR_GPR73_LPUART12_IPG_DOZE(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART12_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART12_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR73_LPUART12_STOP_REQ_MASK  (0x400000U)
#define IOMUXC_GPR_GPR73_LPUART12_STOP_REQ_SHIFT (22U)
/*! LPUART12_STOP_REQ - LPUART12 stop request */
#define IOMUXC_GPR_GPR73_LPUART12_STOP_REQ(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART12_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR73_LPUART12_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR73_LPUART12_IPG_STOP_MODE_MASK (0x800000U)
#define IOMUXC_GPR_GPR73_LPUART12_IPG_STOP_MODE_SHIFT (23U)
/*! LPUART12_IPG_STOP_MODE - LPUART12 stop mode selection, cannot change when LPUART12_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR73_LPUART12_IPG_STOP_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_LPUART12_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR73_LPUART12_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR73_MIC_IPG_DOZE_MASK       (0x1000000U)
#define IOMUXC_GPR_GPR73_MIC_IPG_DOZE_SHIFT      (24U)
/*! MIC_IPG_DOZE - MIC doze mode */
#define IOMUXC_GPR_GPR73_MIC_IPG_DOZE(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_MIC_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR73_MIC_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR73_MIC_STOP_REQ_MASK       (0x2000000U)
#define IOMUXC_GPR_GPR73_MIC_STOP_REQ_SHIFT      (25U)
/*! MIC_STOP_REQ - MIC stop request */
#define IOMUXC_GPR_GPR73_MIC_STOP_REQ(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_MIC_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR73_MIC_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR73_MIC_IPG_STOP_MODE_MASK  (0x4000000U)
#define IOMUXC_GPR_GPR73_MIC_IPG_STOP_MODE_SHIFT (26U)
/*! MIC_IPG_STOP_MODE - MIC stop mode selection, cannot change when MIC_STOP_REQ is asserted.
 *  0b0..This module is functional in Stop Mode
 *  0b1..This module is not functional in Stop Mode and the corresponding x_STOP_REQ field is set to '1'.
 */
#define IOMUXC_GPR_GPR73_MIC_IPG_STOP_MODE(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_MIC_IPG_STOP_MODE_SHIFT)) & IOMUXC_GPR_GPR73_MIC_IPG_STOP_MODE_MASK)

#define IOMUXC_GPR_GPR73_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR73_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR73_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_DWP_SHIFT)) & IOMUXC_GPR_GPR73_DWP_MASK)

#define IOMUXC_GPR_GPR73_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR73_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR73_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR73_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR73_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR74 - GPR74 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR74_PIT1_STOP_REQ_MASK      (0x2U)
#define IOMUXC_GPR_GPR74_PIT1_STOP_REQ_SHIFT     (1U)
/*! PIT1_STOP_REQ - PIT1 stop request */
#define IOMUXC_GPR_GPR74_PIT1_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_PIT1_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR74_PIT1_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR74_PIT2_STOP_REQ_MASK      (0x4U)
#define IOMUXC_GPR_GPR74_PIT2_STOP_REQ_SHIFT     (2U)
/*! PIT2_STOP_REQ - PIT2 stop request */
#define IOMUXC_GPR_GPR74_PIT2_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_PIT2_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR74_PIT2_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR74_SEMC_STOP_REQ_MASK      (0x8U)
#define IOMUXC_GPR_GPR74_SEMC_STOP_REQ_SHIFT     (3U)
/*! SEMC_STOP_REQ - SEMC stop request */
#define IOMUXC_GPR_GPR74_SEMC_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_SEMC_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR74_SEMC_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR74_SIM1_IPG_DOZE_MASK      (0x10U)
#define IOMUXC_GPR_GPR74_SIM1_IPG_DOZE_SHIFT     (4U)
/*! SIM1_IPG_DOZE - SIM1 doze mode */
#define IOMUXC_GPR_GPR74_SIM1_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_SIM1_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR74_SIM1_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR74_SIM2_IPG_DOZE_MASK      (0x20U)
#define IOMUXC_GPR_GPR74_SIM2_IPG_DOZE_SHIFT     (5U)
/*! SIM2_IPG_DOZE - SIM2 doze mode */
#define IOMUXC_GPR_GPR74_SIM2_IPG_DOZE(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_SIM2_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR74_SIM2_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR74_SNVS_HP_IPG_DOZE_MASK   (0x40U)
#define IOMUXC_GPR_GPR74_SNVS_HP_IPG_DOZE_SHIFT  (6U)
/*! SNVS_HP_IPG_DOZE - SNVS_HP doze mode */
#define IOMUXC_GPR_GPR74_SNVS_HP_IPG_DOZE(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_SNVS_HP_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR74_SNVS_HP_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR74_SNVS_HP_STOP_REQ_MASK   (0x80U)
#define IOMUXC_GPR_GPR74_SNVS_HP_STOP_REQ_SHIFT  (7U)
/*! SNVS_HP_STOP_REQ - SNVS_HP stop request */
#define IOMUXC_GPR_GPR74_SNVS_HP_STOP_REQ(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_SNVS_HP_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR74_SNVS_HP_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR74_WDOG1_IPG_DOZE_MASK     (0x100U)
#define IOMUXC_GPR_GPR74_WDOG1_IPG_DOZE_SHIFT    (8U)
/*! WDOG1_IPG_DOZE - WDOG1 doze mode */
#define IOMUXC_GPR_GPR74_WDOG1_IPG_DOZE(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_WDOG1_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR74_WDOG1_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR74_WDOG2_IPG_DOZE_MASK     (0x200U)
#define IOMUXC_GPR_GPR74_WDOG2_IPG_DOZE_SHIFT    (9U)
/*! WDOG2_IPG_DOZE - WDOG2 doze mode */
#define IOMUXC_GPR_GPR74_WDOG2_IPG_DOZE(x)       (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_WDOG2_IPG_DOZE_SHIFT)) & IOMUXC_GPR_GPR74_WDOG2_IPG_DOZE_MASK)

#define IOMUXC_GPR_GPR74_SAI1_STOP_REQ_MASK      (0x400U)
#define IOMUXC_GPR_GPR74_SAI1_STOP_REQ_SHIFT     (10U)
/*! SAI1_STOP_REQ - SAI1 stop request */
#define IOMUXC_GPR_GPR74_SAI1_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_SAI1_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR74_SAI1_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR74_SAI2_STOP_REQ_MASK      (0x800U)
#define IOMUXC_GPR_GPR74_SAI2_STOP_REQ_SHIFT     (11U)
/*! SAI2_STOP_REQ - SAI2 stop request */
#define IOMUXC_GPR_GPR74_SAI2_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_SAI2_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR74_SAI2_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR74_SAI3_STOP_REQ_MASK      (0x1000U)
#define IOMUXC_GPR_GPR74_SAI3_STOP_REQ_SHIFT     (12U)
/*! SAI3_STOP_REQ - SAI3 stop request */
#define IOMUXC_GPR_GPR74_SAI3_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_SAI3_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR74_SAI3_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR74_SAI4_STOP_REQ_MASK      (0x2000U)
#define IOMUXC_GPR_GPR74_SAI4_STOP_REQ_SHIFT     (13U)
/*! SAI4_STOP_REQ - SAI4 stop request */
#define IOMUXC_GPR_GPR74_SAI4_STOP_REQ(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_SAI4_STOP_REQ_SHIFT)) & IOMUXC_GPR_GPR74_SAI4_STOP_REQ_MASK)

#define IOMUXC_GPR_GPR74_FLEXIO1_STOP_REQ_BUS_MASK (0x4000U)
#define IOMUXC_GPR_GPR74_FLEXIO1_STOP_REQ_BUS_SHIFT (14U)
/*! FLEXIO1_STOP_REQ_BUS - FLEXIO1 bus clock domain stop request */
#define IOMUXC_GPR_GPR74_FLEXIO1_STOP_REQ_BUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_FLEXIO1_STOP_REQ_BUS_SHIFT)) & IOMUXC_GPR_GPR74_FLEXIO1_STOP_REQ_BUS_MASK)

#define IOMUXC_GPR_GPR74_FLEXIO1_STOP_REQ_PER_MASK (0x8000U)
#define IOMUXC_GPR_GPR74_FLEXIO1_STOP_REQ_PER_SHIFT (15U)
/*! FLEXIO1_STOP_REQ_PER - FLEXIO1 peripheral clock domain stop request */
#define IOMUXC_GPR_GPR74_FLEXIO1_STOP_REQ_PER(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_FLEXIO1_STOP_REQ_PER_SHIFT)) & IOMUXC_GPR_GPR74_FLEXIO1_STOP_REQ_PER_MASK)

#define IOMUXC_GPR_GPR74_FLEXIO2_STOP_REQ_BUS_MASK (0x10000U)
#define IOMUXC_GPR_GPR74_FLEXIO2_STOP_REQ_BUS_SHIFT (16U)
/*! FLEXIO2_STOP_REQ_BUS - FLEXIO2 bus clock domain stop request */
#define IOMUXC_GPR_GPR74_FLEXIO2_STOP_REQ_BUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_FLEXIO2_STOP_REQ_BUS_SHIFT)) & IOMUXC_GPR_GPR74_FLEXIO2_STOP_REQ_BUS_MASK)

#define IOMUXC_GPR_GPR74_FLEXIO2_STOP_REQ_PER_MASK (0x20000U)
#define IOMUXC_GPR_GPR74_FLEXIO2_STOP_REQ_PER_SHIFT (17U)
/*! FLEXIO2_STOP_REQ_PER - FLEXIO2 peripheral clock domain stop request */
#define IOMUXC_GPR_GPR74_FLEXIO2_STOP_REQ_PER(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_FLEXIO2_STOP_REQ_PER_SHIFT)) & IOMUXC_GPR_GPR74_FLEXIO2_STOP_REQ_PER_MASK)

#define IOMUXC_GPR_GPR74_DWP_MASK                (0x30000000U)
#define IOMUXC_GPR_GPR74_DWP_SHIFT               (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_GPR_GPR74_DWP(x)                  (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_DWP_SHIFT)) & IOMUXC_GPR_GPR74_DWP_MASK)

#define IOMUXC_GPR_GPR74_DWP_LOCK_MASK           (0xC0000000U)
#define IOMUXC_GPR_GPR74_DWP_LOCK_SHIFT          (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_GPR_GPR74_DWP_LOCK(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR74_DWP_LOCK_SHIFT)) & IOMUXC_GPR_GPR74_DWP_LOCK_MASK)
/*! @} */

/*! @name GPR75 - GPR75 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR75_ADC1_STOP_ACK_MASK      (0x1U)
#define IOMUXC_GPR_GPR75_ADC1_STOP_ACK_SHIFT     (0U)
/*! ADC1_STOP_ACK - ADC1 stop acknowledge */
#define IOMUXC_GPR_GPR75_ADC1_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_ADC1_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_ADC1_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_ADC2_STOP_ACK_MASK      (0x2U)
#define IOMUXC_GPR_GPR75_ADC2_STOP_ACK_SHIFT     (1U)
/*! ADC2_STOP_ACK - ADC2 stop acknowledge */
#define IOMUXC_GPR_GPR75_ADC2_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_ADC2_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_ADC2_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_CAAM_STOP_ACK_MASK      (0x4U)
#define IOMUXC_GPR_GPR75_CAAM_STOP_ACK_SHIFT     (2U)
/*! CAAM_STOP_ACK - CAAM stop acknowledge */
#define IOMUXC_GPR_GPR75_CAAM_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_CAAM_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_CAAM_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_CAN1_STOP_ACK_MASK      (0x8U)
#define IOMUXC_GPR_GPR75_CAN1_STOP_ACK_SHIFT     (3U)
/*! CAN1_STOP_ACK - CAN1 stop acknowledge */
#define IOMUXC_GPR_GPR75_CAN1_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_CAN1_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_CAN1_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_CAN2_STOP_ACK_MASK      (0x10U)
#define IOMUXC_GPR_GPR75_CAN2_STOP_ACK_SHIFT     (4U)
/*! CAN2_STOP_ACK - CAN2 stop acknowledge */
#define IOMUXC_GPR_GPR75_CAN2_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_CAN2_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_CAN2_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_CAN3_STOP_ACK_MASK      (0x20U)
#define IOMUXC_GPR_GPR75_CAN3_STOP_ACK_SHIFT     (5U)
/*! CAN3_STOP_ACK - CAN3 stop acknowledge */
#define IOMUXC_GPR_GPR75_CAN3_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_CAN3_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_CAN3_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_EDMA_STOP_ACK_MASK      (0x40U)
#define IOMUXC_GPR_GPR75_EDMA_STOP_ACK_SHIFT     (6U)
/*! EDMA_STOP_ACK - EDMA stop acknowledge */
#define IOMUXC_GPR_GPR75_EDMA_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_EDMA_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_EDMA_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_EDMA_LPSR_STOP_ACK_MASK (0x80U)
#define IOMUXC_GPR_GPR75_EDMA_LPSR_STOP_ACK_SHIFT (7U)
/*! EDMA_LPSR_STOP_ACK - EDMA_LPSR stop acknowledge */
#define IOMUXC_GPR_GPR75_EDMA_LPSR_STOP_ACK(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_EDMA_LPSR_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_EDMA_LPSR_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_ENET_STOP_ACK_MASK      (0x100U)
#define IOMUXC_GPR_GPR75_ENET_STOP_ACK_SHIFT     (8U)
/*! ENET_STOP_ACK - ENET stop acknowledge */
#define IOMUXC_GPR_GPR75_ENET_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_ENET_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_ENET_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_ENET1G_STOP_ACK_MASK    (0x200U)
#define IOMUXC_GPR_GPR75_ENET1G_STOP_ACK_SHIFT   (9U)
/*! ENET1G_STOP_ACK - ENET1G stop acknowledge */
#define IOMUXC_GPR_GPR75_ENET1G_STOP_ACK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_ENET1G_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_ENET1G_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_FLEXSPI1_STOP_ACK_MASK  (0x400U)
#define IOMUXC_GPR_GPR75_FLEXSPI1_STOP_ACK_SHIFT (10U)
/*! FLEXSPI1_STOP_ACK - FLEXSPI1 stop acknowledge */
#define IOMUXC_GPR_GPR75_FLEXSPI1_STOP_ACK(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_FLEXSPI1_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_FLEXSPI1_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_FLEXSPI2_STOP_ACK_MASK  (0x800U)
#define IOMUXC_GPR_GPR75_FLEXSPI2_STOP_ACK_SHIFT (11U)
/*! FLEXSPI2_STOP_ACK - FLEXSPI2 stop acknowledge */
#define IOMUXC_GPR_GPR75_FLEXSPI2_STOP_ACK(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_FLEXSPI2_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_FLEXSPI2_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPI2C1_STOP_ACK_MASK    (0x1000U)
#define IOMUXC_GPR_GPR75_LPI2C1_STOP_ACK_SHIFT   (12U)
/*! LPI2C1_STOP_ACK - LPI2C1 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPI2C1_STOP_ACK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPI2C1_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPI2C1_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPI2C2_STOP_ACK_MASK    (0x2000U)
#define IOMUXC_GPR_GPR75_LPI2C2_STOP_ACK_SHIFT   (13U)
/*! LPI2C2_STOP_ACK - LPI2C2 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPI2C2_STOP_ACK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPI2C2_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPI2C2_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPI2C3_STOP_ACK_MASK    (0x4000U)
#define IOMUXC_GPR_GPR75_LPI2C3_STOP_ACK_SHIFT   (14U)
/*! LPI2C3_STOP_ACK - LPI2C3 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPI2C3_STOP_ACK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPI2C3_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPI2C3_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPI2C4_STOP_ACK_MASK    (0x8000U)
#define IOMUXC_GPR_GPR75_LPI2C4_STOP_ACK_SHIFT   (15U)
/*! LPI2C4_STOP_ACK - LPI2C4 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPI2C4_STOP_ACK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPI2C4_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPI2C4_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPI2C5_STOP_ACK_MASK    (0x10000U)
#define IOMUXC_GPR_GPR75_LPI2C5_STOP_ACK_SHIFT   (16U)
/*! LPI2C5_STOP_ACK - LPI2C5 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPI2C5_STOP_ACK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPI2C5_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPI2C5_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPI2C6_STOP_ACK_MASK    (0x20000U)
#define IOMUXC_GPR_GPR75_LPI2C6_STOP_ACK_SHIFT   (17U)
/*! LPI2C6_STOP_ACK - LPI2C6 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPI2C6_STOP_ACK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPI2C6_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPI2C6_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPSPI1_STOP_ACK_MASK    (0x40000U)
#define IOMUXC_GPR_GPR75_LPSPI1_STOP_ACK_SHIFT   (18U)
/*! LPSPI1_STOP_ACK - LPSPI1 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPSPI1_STOP_ACK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPSPI1_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPSPI1_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPSPI2_STOP_ACK_MASK    (0x80000U)
#define IOMUXC_GPR_GPR75_LPSPI2_STOP_ACK_SHIFT   (19U)
/*! LPSPI2_STOP_ACK - LPSPI2 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPSPI2_STOP_ACK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPSPI2_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPSPI2_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPSPI3_STOP_ACK_MASK    (0x100000U)
#define IOMUXC_GPR_GPR75_LPSPI3_STOP_ACK_SHIFT   (20U)
/*! LPSPI3_STOP_ACK - LPSPI3 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPSPI3_STOP_ACK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPSPI3_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPSPI3_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPSPI4_STOP_ACK_MASK    (0x200000U)
#define IOMUXC_GPR_GPR75_LPSPI4_STOP_ACK_SHIFT   (21U)
/*! LPSPI4_STOP_ACK - LPSPI4 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPSPI4_STOP_ACK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPSPI4_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPSPI4_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPSPI5_STOP_ACK_MASK    (0x400000U)
#define IOMUXC_GPR_GPR75_LPSPI5_STOP_ACK_SHIFT   (22U)
/*! LPSPI5_STOP_ACK - LPSPI5 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPSPI5_STOP_ACK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPSPI5_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPSPI5_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPSPI6_STOP_ACK_MASK    (0x800000U)
#define IOMUXC_GPR_GPR75_LPSPI6_STOP_ACK_SHIFT   (23U)
/*! LPSPI6_STOP_ACK - LPSPI6 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPSPI6_STOP_ACK(x)      (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPSPI6_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPSPI6_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPUART1_STOP_ACK_MASK   (0x1000000U)
#define IOMUXC_GPR_GPR75_LPUART1_STOP_ACK_SHIFT  (24U)
/*! LPUART1_STOP_ACK - LPUART1 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPUART1_STOP_ACK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPUART1_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPUART1_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPUART2_STOP_ACK_MASK   (0x2000000U)
#define IOMUXC_GPR_GPR75_LPUART2_STOP_ACK_SHIFT  (25U)
/*! LPUART2_STOP_ACK - LPUART2 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPUART2_STOP_ACK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPUART2_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPUART2_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPUART3_STOP_ACK_MASK   (0x4000000U)
#define IOMUXC_GPR_GPR75_LPUART3_STOP_ACK_SHIFT  (26U)
/*! LPUART3_STOP_ACK - LPUART3 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPUART3_STOP_ACK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPUART3_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPUART3_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPUART4_STOP_ACK_MASK   (0x8000000U)
#define IOMUXC_GPR_GPR75_LPUART4_STOP_ACK_SHIFT  (27U)
/*! LPUART4_STOP_ACK - LPUART4 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPUART4_STOP_ACK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPUART4_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPUART4_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPUART5_STOP_ACK_MASK   (0x10000000U)
#define IOMUXC_GPR_GPR75_LPUART5_STOP_ACK_SHIFT  (28U)
/*! LPUART5_STOP_ACK - LPUART5 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPUART5_STOP_ACK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPUART5_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPUART5_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPUART6_STOP_ACK_MASK   (0x20000000U)
#define IOMUXC_GPR_GPR75_LPUART6_STOP_ACK_SHIFT  (29U)
/*! LPUART6_STOP_ACK - LPUART6 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPUART6_STOP_ACK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPUART6_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPUART6_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPUART7_STOP_ACK_MASK   (0x40000000U)
#define IOMUXC_GPR_GPR75_LPUART7_STOP_ACK_SHIFT  (30U)
/*! LPUART7_STOP_ACK - LPUART7 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPUART7_STOP_ACK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPUART7_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPUART7_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR75_LPUART8_STOP_ACK_MASK   (0x80000000U)
#define IOMUXC_GPR_GPR75_LPUART8_STOP_ACK_SHIFT  (31U)
/*! LPUART8_STOP_ACK - LPUART8 stop acknowledge */
#define IOMUXC_GPR_GPR75_LPUART8_STOP_ACK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR75_LPUART8_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR75_LPUART8_STOP_ACK_MASK)
/*! @} */

/*! @name GPR76 - GPR76 General Purpose Register */
/*! @{ */

#define IOMUXC_GPR_GPR76_LPUART9_STOP_ACK_MASK   (0x1U)
#define IOMUXC_GPR_GPR76_LPUART9_STOP_ACK_SHIFT  (0U)
/*! LPUART9_STOP_ACK - LPUART9 stop acknowledge */
#define IOMUXC_GPR_GPR76_LPUART9_STOP_ACK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_LPUART9_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR76_LPUART9_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR76_LPUART10_STOP_ACK_MASK  (0x2U)
#define IOMUXC_GPR_GPR76_LPUART10_STOP_ACK_SHIFT (1U)
/*! LPUART10_STOP_ACK - LPUART10 stop acknowledge */
#define IOMUXC_GPR_GPR76_LPUART10_STOP_ACK(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_LPUART10_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR76_LPUART10_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR76_LPUART11_STOP_ACK_MASK  (0x4U)
#define IOMUXC_GPR_GPR76_LPUART11_STOP_ACK_SHIFT (2U)
/*! LPUART11_STOP_ACK - LPUART11 stop acknowledge */
#define IOMUXC_GPR_GPR76_LPUART11_STOP_ACK(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_LPUART11_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR76_LPUART11_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR76_LPUART12_STOP_ACK_MASK  (0x8U)
#define IOMUXC_GPR_GPR76_LPUART12_STOP_ACK_SHIFT (3U)
/*! LPUART12_STOP_ACK - LPUART12 stop acknowledge */
#define IOMUXC_GPR_GPR76_LPUART12_STOP_ACK(x)    (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_LPUART12_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR76_LPUART12_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR76_MIC_STOP_ACK_MASK       (0x10U)
#define IOMUXC_GPR_GPR76_MIC_STOP_ACK_SHIFT      (4U)
/*! MIC_STOP_ACK - MIC stop acknowledge */
#define IOMUXC_GPR_GPR76_MIC_STOP_ACK(x)         (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_MIC_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR76_MIC_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR76_PIT1_STOP_ACK_MASK      (0x20U)
#define IOMUXC_GPR_GPR76_PIT1_STOP_ACK_SHIFT     (5U)
/*! PIT1_STOP_ACK - PIT1 stop acknowledge */
#define IOMUXC_GPR_GPR76_PIT1_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_PIT1_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR76_PIT1_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR76_PIT2_STOP_ACK_MASK      (0x40U)
#define IOMUXC_GPR_GPR76_PIT2_STOP_ACK_SHIFT     (6U)
/*! PIT2_STOP_ACK - PIT2 stop acknowledge */
#define IOMUXC_GPR_GPR76_PIT2_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_PIT2_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR76_PIT2_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR76_SEMC_STOP_ACK_MASK      (0x80U)
#define IOMUXC_GPR_GPR76_SEMC_STOP_ACK_SHIFT     (7U)
/*! SEMC_STOP_ACK - SEMC stop acknowledge */
#define IOMUXC_GPR_GPR76_SEMC_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_SEMC_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR76_SEMC_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR76_SNVS_HP_STOP_ACK_MASK   (0x100U)
#define IOMUXC_GPR_GPR76_SNVS_HP_STOP_ACK_SHIFT  (8U)
/*! SNVS_HP_STOP_ACK - SNVS_HP stop acknowledge */
#define IOMUXC_GPR_GPR76_SNVS_HP_STOP_ACK(x)     (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_SNVS_HP_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR76_SNVS_HP_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR76_SAI1_STOP_ACK_MASK      (0x200U)
#define IOMUXC_GPR_GPR76_SAI1_STOP_ACK_SHIFT     (9U)
/*! SAI1_STOP_ACK - SAI1 stop acknowledge */
#define IOMUXC_GPR_GPR76_SAI1_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_SAI1_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR76_SAI1_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR76_SAI2_STOP_ACK_MASK      (0x400U)
#define IOMUXC_GPR_GPR76_SAI2_STOP_ACK_SHIFT     (10U)
/*! SAI2_STOP_ACK - SAI2 stop acknowledge */
#define IOMUXC_GPR_GPR76_SAI2_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_SAI2_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR76_SAI2_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR76_SAI3_STOP_ACK_MASK      (0x800U)
#define IOMUXC_GPR_GPR76_SAI3_STOP_ACK_SHIFT     (11U)
/*! SAI3_STOP_ACK - SAI3 stop acknowledge */
#define IOMUXC_GPR_GPR76_SAI3_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_SAI3_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR76_SAI3_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR76_SAI4_STOP_ACK_MASK      (0x1000U)
#define IOMUXC_GPR_GPR76_SAI4_STOP_ACK_SHIFT     (12U)
/*! SAI4_STOP_ACK - SAI4 stop acknowledge */
#define IOMUXC_GPR_GPR76_SAI4_STOP_ACK(x)        (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_SAI4_STOP_ACK_SHIFT)) & IOMUXC_GPR_GPR76_SAI4_STOP_ACK_MASK)

#define IOMUXC_GPR_GPR76_FLEXIO1_STOP_ACK_BUS_MASK (0x2000U)
#define IOMUXC_GPR_GPR76_FLEXIO1_STOP_ACK_BUS_SHIFT (13U)
/*! FLEXIO1_STOP_ACK_BUS - FLEXIO1 stop acknowledge of bus clock domain */
#define IOMUXC_GPR_GPR76_FLEXIO1_STOP_ACK_BUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_FLEXIO1_STOP_ACK_BUS_SHIFT)) & IOMUXC_GPR_GPR76_FLEXIO1_STOP_ACK_BUS_MASK)

#define IOMUXC_GPR_GPR76_FLEXIO1_STOP_ACK_PER_MASK (0x4000U)
#define IOMUXC_GPR_GPR76_FLEXIO1_STOP_ACK_PER_SHIFT (14U)
/*! FLEXIO1_STOP_ACK_PER - FLEXIO1 stop acknowledge of peripheral clock domain */
#define IOMUXC_GPR_GPR76_FLEXIO1_STOP_ACK_PER(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_FLEXIO1_STOP_ACK_PER_SHIFT)) & IOMUXC_GPR_GPR76_FLEXIO1_STOP_ACK_PER_MASK)

#define IOMUXC_GPR_GPR76_FLEXIO2_STOP_ACK_BUS_MASK (0x8000U)
#define IOMUXC_GPR_GPR76_FLEXIO2_STOP_ACK_BUS_SHIFT (15U)
/*! FLEXIO2_STOP_ACK_BUS - FLEXIO2 stop acknowledge of bus clock domain */
#define IOMUXC_GPR_GPR76_FLEXIO2_STOP_ACK_BUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_FLEXIO2_STOP_ACK_BUS_SHIFT)) & IOMUXC_GPR_GPR76_FLEXIO2_STOP_ACK_BUS_MASK)

#define IOMUXC_GPR_GPR76_FLEXIO2_STOP_ACK_PER_MASK (0x10000U)
#define IOMUXC_GPR_GPR76_FLEXIO2_STOP_ACK_PER_SHIFT (16U)
/*! FLEXIO2_STOP_ACK_PER - FLEXIO2 stop acknowledge of peripheral clock domain */
#define IOMUXC_GPR_GPR76_FLEXIO2_STOP_ACK_PER(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_GPR_GPR76_FLEXIO2_STOP_ACK_PER_SHIFT)) & IOMUXC_GPR_GPR76_FLEXIO2_STOP_ACK_PER_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group IOMUXC_GPR_Register_Masks */


/*!
 * @}
 */ /* end of group IOMUXC_GPR_Peripheral_Access_Layer */


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


#endif  /* PERI_IOMUXC_GPR_H_ */

