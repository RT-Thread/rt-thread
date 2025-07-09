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
**         CMSIS Peripheral Access Layer for SNVS
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
 * @file PERI_SNVS.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for SNVS
 *
 * CMSIS Peripheral Access Layer for SNVS
 */

#if !defined(PERI_SNVS_H_)
#define PERI_SNVS_H_                             /**< Symbol preventing repeated inclusion */

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
   -- SNVS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SNVS_Peripheral_Access_Layer SNVS Peripheral Access Layer
 * @{
 */

/** SNVS - Size of Registers Arrays */
#define SNVS_LPZMKR_COUNT                         8u
#define SNVS_LPGPR0_LPGPR3_COUNT                  4u
#define SNVS_LPATCR_COUNT                         5u
#define SNVS_LPGPR0_LPGPR7_COUNT                  4u

/** SNVS - Register Layout Typedef */
typedef struct {
  __IO uint32_t HPLR;                              /**< SNVS_HP Lock Register, offset: 0x0 */
  __IO uint32_t HPCOMR;                            /**< SNVS_HP Command Register, offset: 0x4 */
  __IO uint32_t HPCR;                              /**< SNVS_HP Control Register, offset: 0x8 */
  __IO uint32_t HPSICR;                            /**< SNVS_HP Security Interrupt Control Register, offset: 0xC */
  __IO uint32_t HPSVCR;                            /**< SNVS_HP Security Violation Control Register, offset: 0x10 */
  __IO uint32_t HPSR;                              /**< SNVS_HP Status Register, offset: 0x14 */
  __IO uint32_t HPSVSR;                            /**< SNVS_HP Security Violation Status Register, offset: 0x18 */
  __IO uint32_t HPHACIVR;                          /**< SNVS_HP High Assurance Counter IV Register, offset: 0x1C */
  __I  uint32_t HPHACR;                            /**< SNVS_HP High Assurance Counter Register, offset: 0x20 */
  __IO uint32_t HPRTCMR;                           /**< SNVS_HP Real Time Counter MSB Register, offset: 0x24 */
  __IO uint32_t HPRTCLR;                           /**< SNVS_HP Real Time Counter LSB Register, offset: 0x28 */
  __IO uint32_t HPTAMR;                            /**< SNVS_HP Time Alarm MSB Register, offset: 0x2C */
  __IO uint32_t HPTALR;                            /**< SNVS_HP Time Alarm LSB Register, offset: 0x30 */
  __IO uint32_t LPLR;                              /**< SNVS_LP Lock Register, offset: 0x34 */
  __IO uint32_t LPCR;                              /**< SNVS_LP Control Register, offset: 0x38 */
  __IO uint32_t LPMKCR;                            /**< SNVS_LP Master Key Control Register, offset: 0x3C */
  __IO uint32_t LPSVCR;                            /**< SNVS_LP Security Violation Control Register, offset: 0x40 */
  __IO uint32_t LPTGFCR;                           /**< SNVS_LP Tamper Glitch Filters Configuration Register, offset: 0x44 */
  __IO uint32_t LPTDCR;                            /**< SNVS_LP Tamper Detect Configuration Register, offset: 0x48 */
  __IO uint32_t LPSR;                              /**< SNVS_LP Status Register, offset: 0x4C */
  __IO uint32_t LPSRTCMR;                          /**< SNVS_LP Secure Real Time Counter MSB Register, offset: 0x50 */
  __IO uint32_t LPSRTCLR;                          /**< SNVS_LP Secure Real Time Counter LSB Register, offset: 0x54 */
  __IO uint32_t LPTAR;                             /**< SNVS_LP Time Alarm Register, offset: 0x58 */
  __IO uint32_t LPSMCMR;                           /**< SNVS_LP Secure Monotonic Counter MSB Register, offset: 0x5C */
  __IO uint32_t LPSMCLR;                           /**< SNVS_LP Secure Monotonic Counter LSB Register, offset: 0x60 */
  __IO uint32_t LPLVDR;                            /**< SNVS_LP Digital Low-Voltage Detector Register, offset: 0x64 */
  __IO uint32_t LPGPR0_LEGACY_ALIAS;               /**< SNVS_LP General Purpose Register 0 (legacy alias), offset: 0x68 */
  __IO uint32_t LPZMKR[SNVS_LPZMKR_COUNT];         /**< SNVS_LP Zeroizable Master Key Register, array offset: 0x6C, array step: 0x4 */
       uint8_t RESERVED_0[4];
  __IO uint32_t LPGPR_ALIAS[SNVS_LPGPR0_LPGPR3_COUNT]; /**< SNVS_LP General Purpose Registers 0 .. 3, array offset: 0x90, array step: 0x4 */
  __IO uint32_t LPTDC2R;                           /**< SNVS_LP Tamper Detectors Config 2 Register, offset: 0xA0 */
  __IO uint32_t LPTDSR;                            /**< SNVS_LP Tamper Detectors Status Register, offset: 0xA4 */
  __IO uint32_t LPTGF1CR;                          /**< SNVS_LP Tamper Glitch Filter 1 Configuration Register, offset: 0xA8 */
  __IO uint32_t LPTGF2CR;                          /**< SNVS_LP Tamper Glitch Filter 2 Configuration Register, offset: 0xAC */
       uint8_t RESERVED_1[16];
  __O  uint32_t LPATCR[SNVS_LPATCR_COUNT];         /**< SNVS_LP Active Tamper 1 Configuration Register..SNVS_LP Active Tamper 5 Configuration Register, array offset: 0xC0, array step: 0x4 */
       uint8_t RESERVED_2[12];
  __IO uint32_t LPATCTLR;                          /**< SNVS_LP Active Tamper Control Register, offset: 0xE0 */
  __IO uint32_t LPATCLKR;                          /**< SNVS_LP Active Tamper Clock Control Register, offset: 0xE4 */
  __IO uint32_t LPATRC1R;                          /**< SNVS_LP Active Tamper Routing Control 1 Register, offset: 0xE8 */
  __IO uint32_t LPATRC2R;                          /**< SNVS_LP Active Tamper Routing Control 2 Register, offset: 0xEC */
       uint8_t RESERVED_3[16];
  __IO uint32_t LPGPR[SNVS_LPGPR0_LPGPR7_COUNT];   /**< SNVS_LP General Purpose Registers 0 .. 3, array offset: 0x100, array step: 0x4 */
       uint8_t RESERVED_4[2792];
  __I  uint32_t HPVIDR1;                           /**< SNVS_HP Version ID Register 1, offset: 0xBF8 */
  __I  uint32_t HPVIDR2;                           /**< SNVS_HP Version ID Register 2, offset: 0xBFC */
} SNVS_Type;

/* ----------------------------------------------------------------------------
   -- SNVS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SNVS_Register_Masks SNVS Register Masks
 * @{
 */

/*! @name HPLR - SNVS_HP Lock Register */
/*! @{ */

#define SNVS_HPLR_ZMK_WSL_MASK                   (0x1U)
#define SNVS_HPLR_ZMK_WSL_SHIFT                  (0U)
/*! ZMK_WSL
 *  0b0..Write access is allowed
 *  0b1..Write access is not allowed
 */
#define SNVS_HPLR_ZMK_WSL(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_ZMK_WSL_SHIFT)) & SNVS_HPLR_ZMK_WSL_MASK)

#define SNVS_HPLR_ZMK_RSL_MASK                   (0x2U)
#define SNVS_HPLR_ZMK_RSL_SHIFT                  (1U)
/*! ZMK_RSL
 *  0b0..Read access is allowed (only in software Programming mode)
 *  0b1..Read access is not allowed
 */
#define SNVS_HPLR_ZMK_RSL(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_ZMK_RSL_SHIFT)) & SNVS_HPLR_ZMK_RSL_MASK)

#define SNVS_HPLR_SRTC_SL_MASK                   (0x4U)
#define SNVS_HPLR_SRTC_SL_SHIFT                  (2U)
/*! SRTC_SL
 *  0b0..Write access is allowed
 *  0b1..Write access is not allowed
 */
#define SNVS_HPLR_SRTC_SL(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_SRTC_SL_SHIFT)) & SNVS_HPLR_SRTC_SL_MASK)

#define SNVS_HPLR_LPCALB_SL_MASK                 (0x8U)
#define SNVS_HPLR_LPCALB_SL_SHIFT                (3U)
/*! LPCALB_SL
 *  0b0..Write access is allowed
 *  0b1..Write access is not allowed
 */
#define SNVS_HPLR_LPCALB_SL(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_LPCALB_SL_SHIFT)) & SNVS_HPLR_LPCALB_SL_MASK)

#define SNVS_HPLR_MC_SL_MASK                     (0x10U)
#define SNVS_HPLR_MC_SL_SHIFT                    (4U)
/*! MC_SL
 *  0b0..Write access (increment) is allowed
 *  0b1..Write access (increment) is not allowed
 */
#define SNVS_HPLR_MC_SL(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_MC_SL_SHIFT)) & SNVS_HPLR_MC_SL_MASK)

#define SNVS_HPLR_GPR_SL_MASK                    (0x20U)
#define SNVS_HPLR_GPR_SL_SHIFT                   (5U)
/*! GPR_SL
 *  0b0..Write access is allowed
 *  0b1..Write access is not allowed
 */
#define SNVS_HPLR_GPR_SL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_GPR_SL_SHIFT)) & SNVS_HPLR_GPR_SL_MASK)

#define SNVS_HPLR_LPSVCR_SL_MASK                 (0x40U)
#define SNVS_HPLR_LPSVCR_SL_SHIFT                (6U)
/*! LPSVCR_SL
 *  0b0..Write access is allowed
 *  0b1..Write access is not allowed
 */
#define SNVS_HPLR_LPSVCR_SL(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_LPSVCR_SL_SHIFT)) & SNVS_HPLR_LPSVCR_SL_MASK)

#define SNVS_HPLR_LPTGFCR_SL_MASK                (0x80U)
#define SNVS_HPLR_LPTGFCR_SL_SHIFT               (7U)
/*! LPTGFCR_SL
 *  0b0..Write access is allowed
 *  0b1..Write access is not allowed
 */
#define SNVS_HPLR_LPTGFCR_SL(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_LPTGFCR_SL_SHIFT)) & SNVS_HPLR_LPTGFCR_SL_MASK)

#define SNVS_HPLR_LPSECR_SL_MASK                 (0x100U)
#define SNVS_HPLR_LPSECR_SL_SHIFT                (8U)
/*! LPSECR_SL
 *  0b0..Write access is allowed
 *  0b1..Write access is not allowed
 */
#define SNVS_HPLR_LPSECR_SL(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_LPSECR_SL_SHIFT)) & SNVS_HPLR_LPSECR_SL_MASK)

#define SNVS_HPLR_MKS_SL_MASK                    (0x200U)
#define SNVS_HPLR_MKS_SL_SHIFT                   (9U)
/*! MKS_SL
 *  0b0..Write access is allowed
 *  0b1..Write access is not allowed
 */
#define SNVS_HPLR_MKS_SL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_MKS_SL_SHIFT)) & SNVS_HPLR_MKS_SL_MASK)

#define SNVS_HPLR_HPSVCR_L_MASK                  (0x10000U)
#define SNVS_HPLR_HPSVCR_L_SHIFT                 (16U)
/*! HPSVCR_L
 *  0b0..Write access is allowed
 *  0b1..Write access is not allowed
 */
#define SNVS_HPLR_HPSVCR_L(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_HPSVCR_L_SHIFT)) & SNVS_HPLR_HPSVCR_L_MASK)

#define SNVS_HPLR_HPSICR_L_MASK                  (0x20000U)
#define SNVS_HPLR_HPSICR_L_SHIFT                 (17U)
/*! HPSICR_L
 *  0b0..Write access is allowed
 *  0b1..Write access is not allowed
 */
#define SNVS_HPLR_HPSICR_L(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_HPSICR_L_SHIFT)) & SNVS_HPLR_HPSICR_L_MASK)

#define SNVS_HPLR_HAC_L_MASK                     (0x40000U)
#define SNVS_HPLR_HAC_L_SHIFT                    (18U)
/*! HAC_L
 *  0b0..Write access is allowed
 *  0b1..Write access is not allowed
 */
#define SNVS_HPLR_HAC_L(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_HAC_L_SHIFT)) & SNVS_HPLR_HAC_L_MASK)

#define SNVS_HPLR_AT1_SL_MASK                    (0x1000000U)
#define SNVS_HPLR_AT1_SL_SHIFT                   (24U)
/*! AT1_SL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_HPLR_AT1_SL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_AT1_SL_SHIFT)) & SNVS_HPLR_AT1_SL_MASK)

#define SNVS_HPLR_AT2_SL_MASK                    (0x2000000U)
#define SNVS_HPLR_AT2_SL_SHIFT                   (25U)
/*! AT2_SL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_HPLR_AT2_SL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_AT2_SL_SHIFT)) & SNVS_HPLR_AT2_SL_MASK)

#define SNVS_HPLR_AT3_SL_MASK                    (0x4000000U)
#define SNVS_HPLR_AT3_SL_SHIFT                   (26U)
/*! AT3_SL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_HPLR_AT3_SL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_AT3_SL_SHIFT)) & SNVS_HPLR_AT3_SL_MASK)

#define SNVS_HPLR_AT4_SL_MASK                    (0x8000000U)
#define SNVS_HPLR_AT4_SL_SHIFT                   (27U)
/*! AT4_SL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_HPLR_AT4_SL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_AT4_SL_SHIFT)) & SNVS_HPLR_AT4_SL_MASK)

#define SNVS_HPLR_AT5_SL_MASK                    (0x10000000U)
#define SNVS_HPLR_AT5_SL_SHIFT                   (28U)
/*! AT5_SL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_HPLR_AT5_SL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_HPLR_AT5_SL_SHIFT)) & SNVS_HPLR_AT5_SL_MASK)
/*! @} */

/*! @name HPCOMR - SNVS_HP Command Register */
/*! @{ */

#define SNVS_HPCOMR_SSM_ST_MASK                  (0x1U)
#define SNVS_HPCOMR_SSM_ST_SHIFT                 (0U)
#define SNVS_HPCOMR_SSM_ST(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_SSM_ST_SHIFT)) & SNVS_HPCOMR_SSM_ST_MASK)

#define SNVS_HPCOMR_SSM_ST_DIS_MASK              (0x2U)
#define SNVS_HPCOMR_SSM_ST_DIS_SHIFT             (1U)
/*! SSM_ST_DIS
 *  0b0..Secure to Trusted State transition is enabled
 *  0b1..Secure to Trusted State transition is disabled
 */
#define SNVS_HPCOMR_SSM_ST_DIS(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_SSM_ST_DIS_SHIFT)) & SNVS_HPCOMR_SSM_ST_DIS_MASK)

#define SNVS_HPCOMR_SSM_SFNS_DIS_MASK            (0x4U)
#define SNVS_HPCOMR_SSM_SFNS_DIS_SHIFT           (2U)
/*! SSM_SFNS_DIS
 *  0b0..Soft Fail to Non-Secure State transition is enabled
 *  0b1..Soft Fail to Non-Secure State transition is disabled
 */
#define SNVS_HPCOMR_SSM_SFNS_DIS(x)              (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_SSM_SFNS_DIS_SHIFT)) & SNVS_HPCOMR_SSM_SFNS_DIS_MASK)

#define SNVS_HPCOMR_LP_SWR_MASK                  (0x10U)
#define SNVS_HPCOMR_LP_SWR_SHIFT                 (4U)
/*! LP_SWR
 *  0b0..No Action
 *  0b1..Reset LP section
 */
#define SNVS_HPCOMR_LP_SWR(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_LP_SWR_SHIFT)) & SNVS_HPCOMR_LP_SWR_MASK)

#define SNVS_HPCOMR_LP_SWR_DIS_MASK              (0x20U)
#define SNVS_HPCOMR_LP_SWR_DIS_SHIFT             (5U)
/*! LP_SWR_DIS
 *  0b0..LP software reset is enabled
 *  0b1..LP software reset is disabled
 */
#define SNVS_HPCOMR_LP_SWR_DIS(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_LP_SWR_DIS_SHIFT)) & SNVS_HPCOMR_LP_SWR_DIS_MASK)

#define SNVS_HPCOMR_SW_SV_MASK                   (0x100U)
#define SNVS_HPCOMR_SW_SV_SHIFT                  (8U)
#define SNVS_HPCOMR_SW_SV(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_SW_SV_SHIFT)) & SNVS_HPCOMR_SW_SV_MASK)

#define SNVS_HPCOMR_SW_FSV_MASK                  (0x200U)
#define SNVS_HPCOMR_SW_FSV_SHIFT                 (9U)
#define SNVS_HPCOMR_SW_FSV(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_SW_FSV_SHIFT)) & SNVS_HPCOMR_SW_FSV_MASK)

#define SNVS_HPCOMR_SW_LPSV_MASK                 (0x400U)
#define SNVS_HPCOMR_SW_LPSV_SHIFT                (10U)
#define SNVS_HPCOMR_SW_LPSV(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_SW_LPSV_SHIFT)) & SNVS_HPCOMR_SW_LPSV_MASK)

#define SNVS_HPCOMR_PROG_ZMK_MASK                (0x1000U)
#define SNVS_HPCOMR_PROG_ZMK_SHIFT               (12U)
/*! PROG_ZMK
 *  0b0..No Action
 *  0b1..Activate hardware key programming mechanism
 */
#define SNVS_HPCOMR_PROG_ZMK(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_PROG_ZMK_SHIFT)) & SNVS_HPCOMR_PROG_ZMK_MASK)

#define SNVS_HPCOMR_MKS_EN_MASK                  (0x2000U)
#define SNVS_HPCOMR_MKS_EN_SHIFT                 (13U)
/*! MKS_EN
 *  0b0..OTP master key is selected as an SNVS master key
 *  0b1..SNVS master key is selected according to the setting of the MASTER_KEY_SEL field of LPMKCR
 */
#define SNVS_HPCOMR_MKS_EN(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_MKS_EN_SHIFT)) & SNVS_HPCOMR_MKS_EN_MASK)

#define SNVS_HPCOMR_HAC_EN_MASK                  (0x10000U)
#define SNVS_HPCOMR_HAC_EN_SHIFT                 (16U)
/*! HAC_EN
 *  0b0..High Assurance Counter is disabled
 *  0b1..High Assurance Counter is enabled
 */
#define SNVS_HPCOMR_HAC_EN(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_HAC_EN_SHIFT)) & SNVS_HPCOMR_HAC_EN_MASK)

#define SNVS_HPCOMR_HAC_LOAD_MASK                (0x20000U)
#define SNVS_HPCOMR_HAC_LOAD_SHIFT               (17U)
/*! HAC_LOAD
 *  0b0..No Action
 *  0b1..Load the HAC
 */
#define SNVS_HPCOMR_HAC_LOAD(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_HAC_LOAD_SHIFT)) & SNVS_HPCOMR_HAC_LOAD_MASK)

#define SNVS_HPCOMR_HAC_CLEAR_MASK               (0x40000U)
#define SNVS_HPCOMR_HAC_CLEAR_SHIFT              (18U)
/*! HAC_CLEAR
 *  0b0..No Action
 *  0b1..Clear the HAC
 */
#define SNVS_HPCOMR_HAC_CLEAR(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_HAC_CLEAR_SHIFT)) & SNVS_HPCOMR_HAC_CLEAR_MASK)

#define SNVS_HPCOMR_HAC_STOP_MASK                (0x80000U)
#define SNVS_HPCOMR_HAC_STOP_SHIFT               (19U)
#define SNVS_HPCOMR_HAC_STOP(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_HAC_STOP_SHIFT)) & SNVS_HPCOMR_HAC_STOP_MASK)

#define SNVS_HPCOMR_NPSWA_EN_MASK                (0x80000000U)
#define SNVS_HPCOMR_NPSWA_EN_SHIFT               (31U)
#define SNVS_HPCOMR_NPSWA_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPCOMR_NPSWA_EN_SHIFT)) & SNVS_HPCOMR_NPSWA_EN_MASK)
/*! @} */

/*! @name HPCR - SNVS_HP Control Register */
/*! @{ */

#define SNVS_HPCR_RTC_EN_MASK                    (0x1U)
#define SNVS_HPCR_RTC_EN_SHIFT                   (0U)
/*! RTC_EN
 *  0b0..RTC is disabled
 *  0b1..RTC is enabled
 */
#define SNVS_HPCR_RTC_EN(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_HPCR_RTC_EN_SHIFT)) & SNVS_HPCR_RTC_EN_MASK)

#define SNVS_HPCR_HPTA_EN_MASK                   (0x2U)
#define SNVS_HPCR_HPTA_EN_SHIFT                  (1U)
/*! HPTA_EN
 *  0b0..HP Time Alarm Interrupt is disabled
 *  0b1..HP Time Alarm Interrupt is enabled
 */
#define SNVS_HPCR_HPTA_EN(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_HPCR_HPTA_EN_SHIFT)) & SNVS_HPCR_HPTA_EN_MASK)

#define SNVS_HPCR_DIS_PI_MASK                    (0x4U)
#define SNVS_HPCR_DIS_PI_SHIFT                   (2U)
/*! DIS_PI
 *  0b0..Periodic interrupt will trigger a functional interrupt
 *  0b1..Disable periodic interrupt in the function interrupt
 */
#define SNVS_HPCR_DIS_PI(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_HPCR_DIS_PI_SHIFT)) & SNVS_HPCR_DIS_PI_MASK)

#define SNVS_HPCR_PI_EN_MASK                     (0x8U)
#define SNVS_HPCR_PI_EN_SHIFT                    (3U)
/*! PI_EN
 *  0b0..HP Periodic Interrupt is disabled
 *  0b1..HP Periodic Interrupt is enabled
 */
#define SNVS_HPCR_PI_EN(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_HPCR_PI_EN_SHIFT)) & SNVS_HPCR_PI_EN_MASK)

#define SNVS_HPCR_PI_FREQ_MASK                   (0xF0U)
#define SNVS_HPCR_PI_FREQ_SHIFT                  (4U)
/*! PI_FREQ
 *  0b0000..- bit 0 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b0001..- bit 1 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b0010..- bit 2 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b0011..- bit 3 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b0100..- bit 4 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b0101..- bit 5 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b0110..- bit 6 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b0111..- bit 7 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b1000..- bit 8 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b1001..- bit 9 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b1010..- bit 10 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b1011..- bit 11 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b1100..- bit 12 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b1101..- bit 13 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b1110..- bit 14 of the HPRTCLR is selected as a source of the periodic interrupt
 *  0b1111..- bit 15 of the HPRTCLR is selected as a source of the periodic interrupt
 */
#define SNVS_HPCR_PI_FREQ(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_HPCR_PI_FREQ_SHIFT)) & SNVS_HPCR_PI_FREQ_MASK)

#define SNVS_HPCR_HPCALB_EN_MASK                 (0x100U)
#define SNVS_HPCR_HPCALB_EN_SHIFT                (8U)
/*! HPCALB_EN
 *  0b0..HP Timer calibration disabled
 *  0b1..HP Timer calibration enabled
 */
#define SNVS_HPCR_HPCALB_EN(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_HPCR_HPCALB_EN_SHIFT)) & SNVS_HPCR_HPCALB_EN_MASK)

#define SNVS_HPCR_HPCALB_VAL_MASK                (0x7C00U)
#define SNVS_HPCR_HPCALB_VAL_SHIFT               (10U)
/*! HPCALB_VAL
 *  0b00000..+0 counts per each 32768 ticks of the counter
 *  0b00001..+1 counts per each 32768 ticks of the counter
 *  0b00010..+2 counts per each 32768 ticks of the counter
 *  0b01111..+15 counts per each 32768 ticks of the counter
 *  0b10000..-16 counts per each 32768 ticks of the counter
 *  0b10001..-15 counts per each 32768 ticks of the counter
 *  0b11110..-2 counts per each 32768 ticks of the counter
 *  0b11111..-1 counts per each 32768 ticks of the counter
 */
#define SNVS_HPCR_HPCALB_VAL(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPCR_HPCALB_VAL_SHIFT)) & SNVS_HPCR_HPCALB_VAL_MASK)

#define SNVS_HPCR_HP_TS_MASK                     (0x10000U)
#define SNVS_HPCR_HP_TS_SHIFT                    (16U)
/*! HP_TS
 *  0b0..No Action
 *  0b1..Synchronize the HP Time Counter to the LP Time Counter
 */
#define SNVS_HPCR_HP_TS(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_HPCR_HP_TS_SHIFT)) & SNVS_HPCR_HP_TS_MASK)

#define SNVS_HPCR_BTN_CONFIG_MASK                (0x7000000U)
#define SNVS_HPCR_BTN_CONFIG_SHIFT               (24U)
#define SNVS_HPCR_BTN_CONFIG(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPCR_BTN_CONFIG_SHIFT)) & SNVS_HPCR_BTN_CONFIG_MASK)

#define SNVS_HPCR_BTN_MASK_MASK                  (0x8000000U)
#define SNVS_HPCR_BTN_MASK_SHIFT                 (27U)
#define SNVS_HPCR_BTN_MASK(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_HPCR_BTN_MASK_SHIFT)) & SNVS_HPCR_BTN_MASK_MASK)
/*! @} */

/*! @name HPSICR - SNVS_HP Security Interrupt Control Register */
/*! @{ */

#define SNVS_HPSICR_CAAM_EN_MASK                 (0x1U)
#define SNVS_HPSICR_CAAM_EN_SHIFT                (0U)
/*! CAAM_EN
 *  0b0..CAAM Security Violation Interrupt is Disabled
 *  0b1..CAAM Security Violation Interrupt is Enabled
 */
#define SNVS_HPSICR_CAAM_EN(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_HPSICR_CAAM_EN_SHIFT)) & SNVS_HPSICR_CAAM_EN_MASK)

#define SNVS_HPSICR_JTAGC_EN_MASK                (0x2U)
#define SNVS_HPSICR_JTAGC_EN_SHIFT               (1U)
/*! JTAGC_EN
 *  0b0..JTAG Active Interrupt is Disabled
 *  0b1..JTAG Active Interrupt is Enabled
 */
#define SNVS_HPSICR_JTAGC_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPSICR_JTAGC_EN_SHIFT)) & SNVS_HPSICR_JTAGC_EN_MASK)

#define SNVS_HPSICR_WDOG2_EN_MASK                (0x4U)
#define SNVS_HPSICR_WDOG2_EN_SHIFT               (2U)
/*! WDOG2_EN
 *  0b0..Watchdog 2 Reset Interrupt is Disabled
 *  0b1..Watchdog 2 Reset Interrupt is Enabled
 */
#define SNVS_HPSICR_WDOG2_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPSICR_WDOG2_EN_SHIFT)) & SNVS_HPSICR_WDOG2_EN_MASK)

#define SNVS_HPSICR_SRC_EN_MASK                  (0x10U)
#define SNVS_HPSICR_SRC_EN_SHIFT                 (4U)
/*! SRC_EN
 *  0b0..Internal Boot Interrupt is Disabled
 *  0b1..Internal Boot Interrupt is Enabled
 */
#define SNVS_HPSICR_SRC_EN(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_HPSICR_SRC_EN_SHIFT)) & SNVS_HPSICR_SRC_EN_MASK)

#define SNVS_HPSICR_OCOTP_EN_MASK                (0x20U)
#define SNVS_HPSICR_OCOTP_EN_SHIFT               (5U)
/*! OCOTP_EN
 *  0b0..OCOTP attack error Interrupt is Disabled
 *  0b1..OCOTP attack error Interrupt is Enabled
 */
#define SNVS_HPSICR_OCOTP_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPSICR_OCOTP_EN_SHIFT)) & SNVS_HPSICR_OCOTP_EN_MASK)

#define SNVS_HPSICR_LPSVI_EN_MASK                (0x80000000U)
#define SNVS_HPSICR_LPSVI_EN_SHIFT               (31U)
/*! LPSVI_EN
 *  0b0..LP Security Violation Interrupt is Disabled
 *  0b1..LP Security Violation Interrupt is Enabled
 */
#define SNVS_HPSICR_LPSVI_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPSICR_LPSVI_EN_SHIFT)) & SNVS_HPSICR_LPSVI_EN_MASK)
/*! @} */

/*! @name HPSVCR - SNVS_HP Security Violation Control Register */
/*! @{ */

#define SNVS_HPSVCR_CAAM_CFG_MASK                (0x1U)
#define SNVS_HPSVCR_CAAM_CFG_SHIFT               (0U)
/*! CAAM_CFG
 *  0b0..CAAM Security Violation is a non-fatal violation
 *  0b1..CAAM Security Violation is a fatal violation
 */
#define SNVS_HPSVCR_CAAM_CFG(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVCR_CAAM_CFG_SHIFT)) & SNVS_HPSVCR_CAAM_CFG_MASK)

#define SNVS_HPSVCR_JTAGC_CFG_MASK               (0x2U)
#define SNVS_HPSVCR_JTAGC_CFG_SHIFT              (1U)
/*! JTAGC_CFG
 *  0b0..JTAG Active is a non-fatal violation
 *  0b1..JTAG Active is a fatal violation
 */
#define SNVS_HPSVCR_JTAGC_CFG(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVCR_JTAGC_CFG_SHIFT)) & SNVS_HPSVCR_JTAGC_CFG_MASK)

#define SNVS_HPSVCR_WDOG2_CFG_MASK               (0x4U)
#define SNVS_HPSVCR_WDOG2_CFG_SHIFT              (2U)
/*! WDOG2_CFG
 *  0b0..Watchdog 2 Reset is a non-fatal violation
 *  0b1..Watchdog 2 Reset is a fatal violation
 */
#define SNVS_HPSVCR_WDOG2_CFG(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVCR_WDOG2_CFG_SHIFT)) & SNVS_HPSVCR_WDOG2_CFG_MASK)

#define SNVS_HPSVCR_SRC_CFG_MASK                 (0x10U)
#define SNVS_HPSVCR_SRC_CFG_SHIFT                (4U)
/*! SRC_CFG
 *  0b0..Internal Boot is a non-fatal violation
 *  0b1..Internal Boot is a fatal violation
 */
#define SNVS_HPSVCR_SRC_CFG(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVCR_SRC_CFG_SHIFT)) & SNVS_HPSVCR_SRC_CFG_MASK)

#define SNVS_HPSVCR_OCOTP_CFG_MASK               (0x60U)
#define SNVS_HPSVCR_OCOTP_CFG_SHIFT              (5U)
/*! OCOTP_CFG
 *  0b00..OCOTP attack error is disabled
 *  0b01..OCOTP attack error is a non-fatal violation
 *  0b1x..OCOTP attack error is a fatal violation
 */
#define SNVS_HPSVCR_OCOTP_CFG(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVCR_OCOTP_CFG_SHIFT)) & SNVS_HPSVCR_OCOTP_CFG_MASK)

#define SNVS_HPSVCR_LPSV_CFG_MASK                (0xC0000000U)
#define SNVS_HPSVCR_LPSV_CFG_SHIFT               (30U)
/*! LPSV_CFG
 *  0b00..LP security violation is disabled
 *  0b01..LP security violation is a non-fatal violation
 *  0b1x..LP security violation is a fatal violation
 */
#define SNVS_HPSVCR_LPSV_CFG(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVCR_LPSV_CFG_SHIFT)) & SNVS_HPSVCR_LPSV_CFG_MASK)
/*! @} */

/*! @name HPSR - SNVS_HP Status Register */
/*! @{ */

#define SNVS_HPSR_HPTA_MASK                      (0x1U)
#define SNVS_HPSR_HPTA_SHIFT                     (0U)
/*! HPTA
 *  0b0..No time alarm interrupt occurred.
 *  0b1..A time alarm interrupt occurred.
 */
#define SNVS_HPSR_HPTA(x)                        (((uint32_t)(((uint32_t)(x)) << SNVS_HPSR_HPTA_SHIFT)) & SNVS_HPSR_HPTA_MASK)

#define SNVS_HPSR_PI_MASK                        (0x2U)
#define SNVS_HPSR_PI_SHIFT                       (1U)
/*! PI
 *  0b0..No periodic interrupt occurred.
 *  0b1..A periodic interrupt occurred.
 */
#define SNVS_HPSR_PI(x)                          (((uint32_t)(((uint32_t)(x)) << SNVS_HPSR_PI_SHIFT)) & SNVS_HPSR_PI_MASK)

#define SNVS_HPSR_LPDIS_MASK                     (0x10U)
#define SNVS_HPSR_LPDIS_SHIFT                    (4U)
#define SNVS_HPSR_LPDIS(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_HPSR_LPDIS_SHIFT)) & SNVS_HPSR_LPDIS_MASK)

#define SNVS_HPSR_BTN_MASK                       (0x40U)
#define SNVS_HPSR_BTN_SHIFT                      (6U)
#define SNVS_HPSR_BTN(x)                         (((uint32_t)(((uint32_t)(x)) << SNVS_HPSR_BTN_SHIFT)) & SNVS_HPSR_BTN_MASK)

#define SNVS_HPSR_BI_MASK                        (0x80U)
#define SNVS_HPSR_BI_SHIFT                       (7U)
#define SNVS_HPSR_BI(x)                          (((uint32_t)(((uint32_t)(x)) << SNVS_HPSR_BI_SHIFT)) & SNVS_HPSR_BI_MASK)

#define SNVS_HPSR_SSM_STATE_MASK                 (0xF00U)
#define SNVS_HPSR_SSM_STATE_SHIFT                (8U)
/*! SSM_STATE
 *  0b0000..Init
 *  0b0001..Hard Fail
 *  0b0011..Soft Fail
 *  0b1000..Init Intermediate (transition state between Init and Check - SSM stays in this state only one clock cycle)
 *  0b1001..Check
 *  0b1011..Non-Secure
 *  0b1101..Trusted
 *  0b1111..Secure
 */
#define SNVS_HPSR_SSM_STATE(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_HPSR_SSM_STATE_SHIFT)) & SNVS_HPSR_SSM_STATE_MASK)

#define SNVS_HPSR_SYS_SECURITY_CFG_MASK          (0x7000U)
#define SNVS_HPSR_SYS_SECURITY_CFG_SHIFT         (12U)
/*! SYS_SECURITY_CFG
 *  0b000..Fab Configuration - the default configuration of newly fabricated chips
 *  0b001..Open Configuration - the configuration after NXP-programmable fuses have been blown
 *  0b011..Closed Configuration - the configuration after OEM-programmable fuses have been blown
 *  0b111..Field Return Configuration - the configuration of chips that are returned to NXP for analysis
 */
#define SNVS_HPSR_SYS_SECURITY_CFG(x)            (((uint32_t)(((uint32_t)(x)) << SNVS_HPSR_SYS_SECURITY_CFG_SHIFT)) & SNVS_HPSR_SYS_SECURITY_CFG_MASK)

#define SNVS_HPSR_SYS_SECURE_BOOT_MASK           (0x8000U)
#define SNVS_HPSR_SYS_SECURE_BOOT_SHIFT          (15U)
#define SNVS_HPSR_SYS_SECURE_BOOT(x)             (((uint32_t)(((uint32_t)(x)) << SNVS_HPSR_SYS_SECURE_BOOT_SHIFT)) & SNVS_HPSR_SYS_SECURE_BOOT_MASK)

#define SNVS_HPSR_OTPMK_ZERO_MASK                (0x8000000U)
#define SNVS_HPSR_OTPMK_ZERO_SHIFT               (27U)
/*! OTPMK_ZERO
 *  0b0..The OTPMK is not zero.
 *  0b1..The OTPMK is zero.
 */
#define SNVS_HPSR_OTPMK_ZERO(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPSR_OTPMK_ZERO_SHIFT)) & SNVS_HPSR_OTPMK_ZERO_MASK)

#define SNVS_HPSR_ZMK_ZERO_MASK                  (0x80000000U)
#define SNVS_HPSR_ZMK_ZERO_SHIFT                 (31U)
/*! ZMK_ZERO
 *  0b0..The ZMK is not zero.
 *  0b1..The ZMK is zero.
 */
#define SNVS_HPSR_ZMK_ZERO(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_HPSR_ZMK_ZERO_SHIFT)) & SNVS_HPSR_ZMK_ZERO_MASK)
/*! @} */

/*! @name HPSVSR - SNVS_HP Security Violation Status Register */
/*! @{ */

#define SNVS_HPSVSR_CAAM_MASK                    (0x1U)
#define SNVS_HPSVSR_CAAM_SHIFT                   (0U)
/*! CAAM
 *  0b0..No CAAM Security Violation security violation was detected.
 *  0b1..CAAM Security Violation security violation was detected.
 */
#define SNVS_HPSVSR_CAAM(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVSR_CAAM_SHIFT)) & SNVS_HPSVSR_CAAM_MASK)

#define SNVS_HPSVSR_JTAGC_MASK                   (0x2U)
#define SNVS_HPSVSR_JTAGC_SHIFT                  (1U)
/*! JTAGC
 *  0b0..No JTAG Active security violation was detected.
 *  0b1..JTAG Active security violation was detected.
 */
#define SNVS_HPSVSR_JTAGC(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVSR_JTAGC_SHIFT)) & SNVS_HPSVSR_JTAGC_MASK)

#define SNVS_HPSVSR_WDOG2_MASK                   (0x4U)
#define SNVS_HPSVSR_WDOG2_SHIFT                  (2U)
/*! WDOG2
 *  0b0..No Watchdog 2 Reset security violation was detected.
 *  0b1..Watchdog 2 Reset security violation was detected.
 */
#define SNVS_HPSVSR_WDOG2(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVSR_WDOG2_SHIFT)) & SNVS_HPSVSR_WDOG2_MASK)

#define SNVS_HPSVSR_SRC_MASK                     (0x10U)
#define SNVS_HPSVSR_SRC_SHIFT                    (4U)
/*! SRC
 *  0b0..No Internal Boot security violation was detected.
 *  0b1..Internal Boot security violation was detected.
 */
#define SNVS_HPSVSR_SRC(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVSR_SRC_SHIFT)) & SNVS_HPSVSR_SRC_MASK)

#define SNVS_HPSVSR_OCOTP_MASK                   (0x20U)
#define SNVS_HPSVSR_OCOTP_SHIFT                  (5U)
/*! OCOTP
 *  0b0..No OCOTP attack error security violation was detected.
 *  0b1..OCOTP attack error security violation was detected.
 */
#define SNVS_HPSVSR_OCOTP(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVSR_OCOTP_SHIFT)) & SNVS_HPSVSR_OCOTP_MASK)

#define SNVS_HPSVSR_SW_SV_MASK                   (0x2000U)
#define SNVS_HPSVSR_SW_SV_SHIFT                  (13U)
#define SNVS_HPSVSR_SW_SV(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVSR_SW_SV_SHIFT)) & SNVS_HPSVSR_SW_SV_MASK)

#define SNVS_HPSVSR_SW_FSV_MASK                  (0x4000U)
#define SNVS_HPSVSR_SW_FSV_SHIFT                 (14U)
#define SNVS_HPSVSR_SW_FSV(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVSR_SW_FSV_SHIFT)) & SNVS_HPSVSR_SW_FSV_MASK)

#define SNVS_HPSVSR_SW_LPSV_MASK                 (0x8000U)
#define SNVS_HPSVSR_SW_LPSV_SHIFT                (15U)
#define SNVS_HPSVSR_SW_LPSV(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVSR_SW_LPSV_SHIFT)) & SNVS_HPSVSR_SW_LPSV_MASK)

#define SNVS_HPSVSR_ZMK_SYNDROME_MASK            (0x1FF0000U)
#define SNVS_HPSVSR_ZMK_SYNDROME_SHIFT           (16U)
#define SNVS_HPSVSR_ZMK_SYNDROME(x)              (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVSR_ZMK_SYNDROME_SHIFT)) & SNVS_HPSVSR_ZMK_SYNDROME_MASK)

#define SNVS_HPSVSR_ZMK_ECC_FAIL_MASK            (0x8000000U)
#define SNVS_HPSVSR_ZMK_ECC_FAIL_SHIFT           (27U)
/*! ZMK_ECC_FAIL
 *  0b0..ZMK ECC Failure was not detected.
 *  0b1..ZMK ECC Failure was detected.
 */
#define SNVS_HPSVSR_ZMK_ECC_FAIL(x)              (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVSR_ZMK_ECC_FAIL_SHIFT)) & SNVS_HPSVSR_ZMK_ECC_FAIL_MASK)

#define SNVS_HPSVSR_LP_SEC_VIO_MASK              (0x80000000U)
#define SNVS_HPSVSR_LP_SEC_VIO_SHIFT             (31U)
#define SNVS_HPSVSR_LP_SEC_VIO(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_HPSVSR_LP_SEC_VIO_SHIFT)) & SNVS_HPSVSR_LP_SEC_VIO_MASK)
/*! @} */

/*! @name HPHACIVR - SNVS_HP High Assurance Counter IV Register */
/*! @{ */

#define SNVS_HPHACIVR_HAC_COUNTER_IV_MASK        (0xFFFFFFFFU)
#define SNVS_HPHACIVR_HAC_COUNTER_IV_SHIFT       (0U)
#define SNVS_HPHACIVR_HAC_COUNTER_IV(x)          (((uint32_t)(((uint32_t)(x)) << SNVS_HPHACIVR_HAC_COUNTER_IV_SHIFT)) & SNVS_HPHACIVR_HAC_COUNTER_IV_MASK)
/*! @} */

/*! @name HPHACR - SNVS_HP High Assurance Counter Register */
/*! @{ */

#define SNVS_HPHACR_HAC_COUNTER_MASK             (0xFFFFFFFFU)
#define SNVS_HPHACR_HAC_COUNTER_SHIFT            (0U)
#define SNVS_HPHACR_HAC_COUNTER(x)               (((uint32_t)(((uint32_t)(x)) << SNVS_HPHACR_HAC_COUNTER_SHIFT)) & SNVS_HPHACR_HAC_COUNTER_MASK)
/*! @} */

/*! @name HPRTCMR - SNVS_HP Real Time Counter MSB Register */
/*! @{ */

#define SNVS_HPRTCMR_RTC_MASK                    (0x7FFFU)
#define SNVS_HPRTCMR_RTC_SHIFT                   (0U)
#define SNVS_HPRTCMR_RTC(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_HPRTCMR_RTC_SHIFT)) & SNVS_HPRTCMR_RTC_MASK)
/*! @} */

/*! @name HPRTCLR - SNVS_HP Real Time Counter LSB Register */
/*! @{ */

#define SNVS_HPRTCLR_RTC_MASK                    (0xFFFFFFFFU)
#define SNVS_HPRTCLR_RTC_SHIFT                   (0U)
#define SNVS_HPRTCLR_RTC(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_HPRTCLR_RTC_SHIFT)) & SNVS_HPRTCLR_RTC_MASK)
/*! @} */

/*! @name HPTAMR - SNVS_HP Time Alarm MSB Register */
/*! @{ */

#define SNVS_HPTAMR_HPTA_MS_MASK                 (0x7FFFU)
#define SNVS_HPTAMR_HPTA_MS_SHIFT                (0U)
#define SNVS_HPTAMR_HPTA_MS(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_HPTAMR_HPTA_MS_SHIFT)) & SNVS_HPTAMR_HPTA_MS_MASK)
/*! @} */

/*! @name HPTALR - SNVS_HP Time Alarm LSB Register */
/*! @{ */

#define SNVS_HPTALR_HPTA_LS_MASK                 (0xFFFFFFFFU)
#define SNVS_HPTALR_HPTA_LS_SHIFT                (0U)
#define SNVS_HPTALR_HPTA_LS(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_HPTALR_HPTA_LS_SHIFT)) & SNVS_HPTALR_HPTA_LS_MASK)
/*! @} */

/*! @name LPLR - SNVS_LP Lock Register */
/*! @{ */

#define SNVS_LPLR_ZMK_WHL_MASK                   (0x1U)
#define SNVS_LPLR_ZMK_WHL_SHIFT                  (0U)
/*! ZMK_WHL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_LPLR_ZMK_WHL(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_ZMK_WHL_SHIFT)) & SNVS_LPLR_ZMK_WHL_MASK)

#define SNVS_LPLR_ZMK_RHL_MASK                   (0x2U)
#define SNVS_LPLR_ZMK_RHL_SHIFT                  (1U)
/*! ZMK_RHL
 *  0b0..Read access is allowed (only in software programming mode).
 *  0b1..Read access is not allowed.
 */
#define SNVS_LPLR_ZMK_RHL(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_ZMK_RHL_SHIFT)) & SNVS_LPLR_ZMK_RHL_MASK)

#define SNVS_LPLR_SRTC_HL_MASK                   (0x4U)
#define SNVS_LPLR_SRTC_HL_SHIFT                  (2U)
/*! SRTC_HL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_LPLR_SRTC_HL(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_SRTC_HL_SHIFT)) & SNVS_LPLR_SRTC_HL_MASK)

#define SNVS_LPLR_LPCALB_HL_MASK                 (0x8U)
#define SNVS_LPLR_LPCALB_HL_SHIFT                (3U)
/*! LPCALB_HL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_LPLR_LPCALB_HL(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_LPCALB_HL_SHIFT)) & SNVS_LPLR_LPCALB_HL_MASK)

#define SNVS_LPLR_MC_HL_MASK                     (0x10U)
#define SNVS_LPLR_MC_HL_SHIFT                    (4U)
/*! MC_HL
 *  0b0..Write access (increment) is allowed.
 *  0b1..Write access (increment) is not allowed.
 */
#define SNVS_LPLR_MC_HL(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_MC_HL_SHIFT)) & SNVS_LPLR_MC_HL_MASK)

#define SNVS_LPLR_GPR_HL_MASK                    (0x20U)
#define SNVS_LPLR_GPR_HL_SHIFT                   (5U)
/*! GPR_HL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_LPLR_GPR_HL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_GPR_HL_SHIFT)) & SNVS_LPLR_GPR_HL_MASK)

#define SNVS_LPLR_LPSVCR_HL_MASK                 (0x40U)
#define SNVS_LPLR_LPSVCR_HL_SHIFT                (6U)
/*! LPSVCR_HL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_LPLR_LPSVCR_HL(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_LPSVCR_HL_SHIFT)) & SNVS_LPLR_LPSVCR_HL_MASK)

#define SNVS_LPLR_LPTGFCR_HL_MASK                (0x80U)
#define SNVS_LPLR_LPTGFCR_HL_SHIFT               (7U)
/*! LPTGFCR_HL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_LPLR_LPTGFCR_HL(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_LPTGFCR_HL_SHIFT)) & SNVS_LPLR_LPTGFCR_HL_MASK)

#define SNVS_LPLR_LPSECR_HL_MASK                 (0x100U)
#define SNVS_LPLR_LPSECR_HL_SHIFT                (8U)
/*! LPSECR_HL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_LPLR_LPSECR_HL(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_LPSECR_HL_SHIFT)) & SNVS_LPLR_LPSECR_HL_MASK)

#define SNVS_LPLR_MKS_HL_MASK                    (0x200U)
#define SNVS_LPLR_MKS_HL_SHIFT                   (9U)
/*! MKS_HL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_LPLR_MKS_HL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_MKS_HL_SHIFT)) & SNVS_LPLR_MKS_HL_MASK)

#define SNVS_LPLR_AT1_HL_MASK                    (0x1000000U)
#define SNVS_LPLR_AT1_HL_SHIFT                   (24U)
/*! AT1_HL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_LPLR_AT1_HL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_AT1_HL_SHIFT)) & SNVS_LPLR_AT1_HL_MASK)

#define SNVS_LPLR_AT2_HL_MASK                    (0x2000000U)
#define SNVS_LPLR_AT2_HL_SHIFT                   (25U)
/*! AT2_HL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_LPLR_AT2_HL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_AT2_HL_SHIFT)) & SNVS_LPLR_AT2_HL_MASK)

#define SNVS_LPLR_AT3_HL_MASK                    (0x4000000U)
#define SNVS_LPLR_AT3_HL_SHIFT                   (26U)
/*! AT3_HL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_LPLR_AT3_HL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_AT3_HL_SHIFT)) & SNVS_LPLR_AT3_HL_MASK)

#define SNVS_LPLR_AT4_HL_MASK                    (0x8000000U)
#define SNVS_LPLR_AT4_HL_SHIFT                   (27U)
/*! AT4_HL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_LPLR_AT4_HL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_AT4_HL_SHIFT)) & SNVS_LPLR_AT4_HL_MASK)

#define SNVS_LPLR_AT5_HL_MASK                    (0x10000000U)
#define SNVS_LPLR_AT5_HL_SHIFT                   (28U)
/*! AT5_HL
 *  0b0..Write access is allowed.
 *  0b1..Write access is not allowed.
 */
#define SNVS_LPLR_AT5_HL(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPLR_AT5_HL_SHIFT)) & SNVS_LPLR_AT5_HL_MASK)
/*! @} */

/*! @name LPCR - SNVS_LP Control Register */
/*! @{ */

#define SNVS_LPCR_SRTC_ENV_MASK                  (0x1U)
#define SNVS_LPCR_SRTC_ENV_SHIFT                 (0U)
/*! SRTC_ENV
 *  0b0..SRTC is disabled or invalid.
 *  0b1..SRTC is enabled and valid.
 */
#define SNVS_LPCR_SRTC_ENV(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_SRTC_ENV_SHIFT)) & SNVS_LPCR_SRTC_ENV_MASK)

#define SNVS_LPCR_LPTA_EN_MASK                   (0x2U)
#define SNVS_LPCR_LPTA_EN_SHIFT                  (1U)
/*! LPTA_EN
 *  0b0..LP time alarm interrupt is disabled.
 *  0b1..LP time alarm interrupt is enabled.
 */
#define SNVS_LPCR_LPTA_EN(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_LPTA_EN_SHIFT)) & SNVS_LPCR_LPTA_EN_MASK)

#define SNVS_LPCR_MC_ENV_MASK                    (0x4U)
#define SNVS_LPCR_MC_ENV_SHIFT                   (2U)
/*! MC_ENV
 *  0b0..MC is disabled or invalid.
 *  0b1..MC is enabled and valid.
 */
#define SNVS_LPCR_MC_ENV(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_MC_ENV_SHIFT)) & SNVS_LPCR_MC_ENV_MASK)

#define SNVS_LPCR_LPWUI_EN_MASK                  (0x8U)
#define SNVS_LPCR_LPWUI_EN_SHIFT                 (3U)
#define SNVS_LPCR_LPWUI_EN(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_LPWUI_EN_SHIFT)) & SNVS_LPCR_LPWUI_EN_MASK)

#define SNVS_LPCR_SRTC_INV_EN_MASK               (0x10U)
#define SNVS_LPCR_SRTC_INV_EN_SHIFT              (4U)
/*! SRTC_INV_EN
 *  0b0..SRTC stays valid in the case of security violation (other than a software violation (HPSVSR[SW_LPSV] = 1 or HPCOMR[SW_LPSV] = 1)).
 *  0b1..SRTC is invalidated in the case of security violation.
 */
#define SNVS_LPCR_SRTC_INV_EN(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_SRTC_INV_EN_SHIFT)) & SNVS_LPCR_SRTC_INV_EN_MASK)

#define SNVS_LPCR_DP_EN_MASK                     (0x20U)
#define SNVS_LPCR_DP_EN_SHIFT                    (5U)
/*! DP_EN
 *  0b0..Smart PMIC enabled.
 *  0b1..Dumb PMIC enabled.
 */
#define SNVS_LPCR_DP_EN(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_DP_EN_SHIFT)) & SNVS_LPCR_DP_EN_MASK)

#define SNVS_LPCR_TOP_MASK                       (0x40U)
#define SNVS_LPCR_TOP_SHIFT                      (6U)
/*! TOP
 *  0b0..Leave system power on.
 *  0b1..Turn off system power.
 */
#define SNVS_LPCR_TOP(x)                         (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_TOP_SHIFT)) & SNVS_LPCR_TOP_MASK)

#define SNVS_LPCR_LVD_EN_MASK                    (0x80U)
#define SNVS_LPCR_LVD_EN_SHIFT                   (7U)
#define SNVS_LPCR_LVD_EN(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_LVD_EN_SHIFT)) & SNVS_LPCR_LVD_EN_MASK)

#define SNVS_LPCR_LPCALB_EN_MASK                 (0x100U)
#define SNVS_LPCR_LPCALB_EN_SHIFT                (8U)
/*! LPCALB_EN
 *  0b0..SRTC Time calibration is disabled.
 *  0b1..SRTC Time calibration is enabled.
 */
#define SNVS_LPCR_LPCALB_EN(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_LPCALB_EN_SHIFT)) & SNVS_LPCR_LPCALB_EN_MASK)

#define SNVS_LPCR_LPCALB_VAL_MASK                (0x7C00U)
#define SNVS_LPCR_LPCALB_VAL_SHIFT               (10U)
/*! LPCALB_VAL
 *  0b00000..+0 counts per each 32768 ticks of the counter clock
 *  0b00001..+1 counts per each 32768 ticks of the counter clock
 *  0b00010..+2 counts per each 32768 ticks of the counter clock
 *  0b01111..+15 counts per each 32768 ticks of the counter clock
 *  0b10000..-16 counts per each 32768 ticks of the counter clock
 *  0b10001..-15 counts per each 32768 ticks of the counter clock
 *  0b11110..-2 counts per each 32768 ticks of the counter clock
 *  0b11111..-1 counts per each 32768 ticks of the counter clock
 */
#define SNVS_LPCR_LPCALB_VAL(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_LPCALB_VAL_SHIFT)) & SNVS_LPCR_LPCALB_VAL_MASK)

#define SNVS_LPCR_BTN_PRESS_TIME_MASK            (0x30000U)
#define SNVS_LPCR_BTN_PRESS_TIME_SHIFT           (16U)
#define SNVS_LPCR_BTN_PRESS_TIME(x)              (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_BTN_PRESS_TIME_SHIFT)) & SNVS_LPCR_BTN_PRESS_TIME_MASK)

#define SNVS_LPCR_DEBOUNCE_MASK                  (0xC0000U)
#define SNVS_LPCR_DEBOUNCE_SHIFT                 (18U)
#define SNVS_LPCR_DEBOUNCE(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_DEBOUNCE_SHIFT)) & SNVS_LPCR_DEBOUNCE_MASK)

#define SNVS_LPCR_ON_TIME_MASK                   (0x300000U)
#define SNVS_LPCR_ON_TIME_SHIFT                  (20U)
#define SNVS_LPCR_ON_TIME(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_ON_TIME_SHIFT)) & SNVS_LPCR_ON_TIME_MASK)

#define SNVS_LPCR_PK_EN_MASK                     (0x400000U)
#define SNVS_LPCR_PK_EN_SHIFT                    (22U)
#define SNVS_LPCR_PK_EN(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_PK_EN_SHIFT)) & SNVS_LPCR_PK_EN_MASK)

#define SNVS_LPCR_PK_OVERRIDE_MASK               (0x800000U)
#define SNVS_LPCR_PK_OVERRIDE_SHIFT              (23U)
#define SNVS_LPCR_PK_OVERRIDE(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_PK_OVERRIDE_SHIFT)) & SNVS_LPCR_PK_OVERRIDE_MASK)

#define SNVS_LPCR_GPR_Z_DIS_MASK                 (0x1000000U)
#define SNVS_LPCR_GPR_Z_DIS_SHIFT                (24U)
#define SNVS_LPCR_GPR_Z_DIS(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPCR_GPR_Z_DIS_SHIFT)) & SNVS_LPCR_GPR_Z_DIS_MASK)
/*! @} */

/*! @name LPMKCR - SNVS_LP Master Key Control Register */
/*! @{ */

#define SNVS_LPMKCR_MASTER_KEY_SEL_MASK          (0x3U)
#define SNVS_LPMKCR_MASTER_KEY_SEL_SHIFT         (0U)
/*! MASTER_KEY_SEL
 *  0b0x..Select one time programmable master key.
 *  0b10..Select zeroizable master key when MKS_EN bit is set .
 *  0b11..Select combined master key when MKS_EN bit is set .
 */
#define SNVS_LPMKCR_MASTER_KEY_SEL(x)            (((uint32_t)(((uint32_t)(x)) << SNVS_LPMKCR_MASTER_KEY_SEL_SHIFT)) & SNVS_LPMKCR_MASTER_KEY_SEL_MASK)

#define SNVS_LPMKCR_ZMK_HWP_MASK                 (0x4U)
#define SNVS_LPMKCR_ZMK_HWP_SHIFT                (2U)
/*! ZMK_HWP
 *  0b0..ZMK is in the software programming mode.
 *  0b1..ZMK is in the hardware programming mode.
 */
#define SNVS_LPMKCR_ZMK_HWP(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPMKCR_ZMK_HWP_SHIFT)) & SNVS_LPMKCR_ZMK_HWP_MASK)

#define SNVS_LPMKCR_ZMK_VAL_MASK                 (0x8U)
#define SNVS_LPMKCR_ZMK_VAL_SHIFT                (3U)
/*! ZMK_VAL
 *  0b0..ZMK is not valid.
 *  0b1..ZMK is valid.
 */
#define SNVS_LPMKCR_ZMK_VAL(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPMKCR_ZMK_VAL_SHIFT)) & SNVS_LPMKCR_ZMK_VAL_MASK)

#define SNVS_LPMKCR_ZMK_ECC_EN_MASK              (0x10U)
#define SNVS_LPMKCR_ZMK_ECC_EN_SHIFT             (4U)
/*! ZMK_ECC_EN
 *  0b0..ZMK ECC check is disabled.
 *  0b1..ZMK ECC check is enabled.
 */
#define SNVS_LPMKCR_ZMK_ECC_EN(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_LPMKCR_ZMK_ECC_EN_SHIFT)) & SNVS_LPMKCR_ZMK_ECC_EN_MASK)

#define SNVS_LPMKCR_ZMK_ECC_VALUE_MASK           (0xFF80U)
#define SNVS_LPMKCR_ZMK_ECC_VALUE_SHIFT          (7U)
#define SNVS_LPMKCR_ZMK_ECC_VALUE(x)             (((uint32_t)(((uint32_t)(x)) << SNVS_LPMKCR_ZMK_ECC_VALUE_SHIFT)) & SNVS_LPMKCR_ZMK_ECC_VALUE_MASK)
/*! @} */

/*! @name LPSVCR - SNVS_LP Security Violation Control Register */
/*! @{ */

#define SNVS_LPSVCR_CAAM_EN_MASK                 (0x1U)
#define SNVS_LPSVCR_CAAM_EN_SHIFT                (0U)
/*! CAAM_EN
 *  0b0..CAAM Security Violation is disabled in the LP domain.
 *  0b1..CAAM Security Violation is enabled in the LP domain.
 */
#define SNVS_LPSVCR_CAAM_EN(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPSVCR_CAAM_EN_SHIFT)) & SNVS_LPSVCR_CAAM_EN_MASK)

#define SNVS_LPSVCR_JTAGC_EN_MASK                (0x2U)
#define SNVS_LPSVCR_JTAGC_EN_SHIFT               (1U)
/*! JTAGC_EN
 *  0b0..JTAG Active is disabled in the LP domain.
 *  0b1..JTAG Active is enabled in the LP domain.
 */
#define SNVS_LPSVCR_JTAGC_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPSVCR_JTAGC_EN_SHIFT)) & SNVS_LPSVCR_JTAGC_EN_MASK)

#define SNVS_LPSVCR_WDOG2_EN_MASK                (0x4U)
#define SNVS_LPSVCR_WDOG2_EN_SHIFT               (2U)
/*! WDOG2_EN
 *  0b0..Watchdog 2 Reset is disabled in the LP domain.
 *  0b1..Watchdog 2 Reset is enabled in the LP domain.
 */
#define SNVS_LPSVCR_WDOG2_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPSVCR_WDOG2_EN_SHIFT)) & SNVS_LPSVCR_WDOG2_EN_MASK)

#define SNVS_LPSVCR_SRC_EN_MASK                  (0x10U)
#define SNVS_LPSVCR_SRC_EN_SHIFT                 (4U)
/*! SRC_EN
 *  0b0..Internal Boot is disabled in the LP domain.
 *  0b1..Internal Boot is enabled in the LP domain.
 */
#define SNVS_LPSVCR_SRC_EN(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_LPSVCR_SRC_EN_SHIFT)) & SNVS_LPSVCR_SRC_EN_MASK)

#define SNVS_LPSVCR_OCOTP_EN_MASK                (0x20U)
#define SNVS_LPSVCR_OCOTP_EN_SHIFT               (5U)
/*! OCOTP_EN
 *  0b0..OCOTP attack error is disabled in the LP domain.
 *  0b1..OCOTP attack error is enabled in the LP domain.
 */
#define SNVS_LPSVCR_OCOTP_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPSVCR_OCOTP_EN_SHIFT)) & SNVS_LPSVCR_OCOTP_EN_MASK)
/*! @} */

/*! @name LPTGFCR - SNVS_LP Tamper Glitch Filters Configuration Register */
/*! @{ */

#define SNVS_LPTGFCR_WMTGF_MASK                  (0x1FU)
#define SNVS_LPTGFCR_WMTGF_SHIFT                 (0U)
#define SNVS_LPTGFCR_WMTGF(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGFCR_WMTGF_SHIFT)) & SNVS_LPTGFCR_WMTGF_MASK)

#define SNVS_LPTGFCR_WMTGF_EN_MASK               (0x80U)
#define SNVS_LPTGFCR_WMTGF_EN_SHIFT              (7U)
/*! WMTGF_EN
 *  0b0..Wire-mesh tamper glitch filter is bypassed.
 *  0b1..Wire-mesh tamper glitch filter is enabled.
 */
#define SNVS_LPTGFCR_WMTGF_EN(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGFCR_WMTGF_EN_SHIFT)) & SNVS_LPTGFCR_WMTGF_EN_MASK)

#define SNVS_LPTGFCR_ETGF1_MASK                  (0x7F0000U)
#define SNVS_LPTGFCR_ETGF1_SHIFT                 (16U)
#define SNVS_LPTGFCR_ETGF1(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGFCR_ETGF1_SHIFT)) & SNVS_LPTGFCR_ETGF1_MASK)

#define SNVS_LPTGFCR_ETGF1_EN_MASK               (0x800000U)
#define SNVS_LPTGFCR_ETGF1_EN_SHIFT              (23U)
/*! ETGF1_EN
 *  0b0..External tamper glitch filter 1 is bypassed.
 *  0b1..External tamper glitch filter 1 is enabled.
 */
#define SNVS_LPTGFCR_ETGF1_EN(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGFCR_ETGF1_EN_SHIFT)) & SNVS_LPTGFCR_ETGF1_EN_MASK)

#define SNVS_LPTGFCR_ETGF2_MASK                  (0x7F000000U)
#define SNVS_LPTGFCR_ETGF2_SHIFT                 (24U)
#define SNVS_LPTGFCR_ETGF2(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGFCR_ETGF2_SHIFT)) & SNVS_LPTGFCR_ETGF2_MASK)

#define SNVS_LPTGFCR_ETGF2_EN_MASK               (0x80000000U)
#define SNVS_LPTGFCR_ETGF2_EN_SHIFT              (31U)
/*! ETGF2_EN
 *  0b0..External tamper glitch filter 2 is bypassed.
 *  0b1..External tamper glitch filter 2 is enabled.
 */
#define SNVS_LPTGFCR_ETGF2_EN(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGFCR_ETGF2_EN_SHIFT)) & SNVS_LPTGFCR_ETGF2_EN_MASK)
/*! @} */

/*! @name LPTDCR - SNVS_LP Tamper Detect Configuration Register */
/*! @{ */

#define SNVS_LPTDCR_SRTCR_EN_MASK                (0x2U)
#define SNVS_LPTDCR_SRTCR_EN_SHIFT               (1U)
/*! SRTCR_EN
 *  0b0..SRTC rollover is disabled.
 *  0b1..SRTC rollover is enabled.
 */
#define SNVS_LPTDCR_SRTCR_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_SRTCR_EN_SHIFT)) & SNVS_LPTDCR_SRTCR_EN_MASK)

#define SNVS_LPTDCR_MCR_EN_MASK                  (0x4U)
#define SNVS_LPTDCR_MCR_EN_SHIFT                 (2U)
/*! MCR_EN
 *  0b0..MC rollover is disabled.
 *  0b1..MC rollover is enabled.
 */
#define SNVS_LPTDCR_MCR_EN(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_MCR_EN_SHIFT)) & SNVS_LPTDCR_MCR_EN_MASK)

#define SNVS_LPTDCR_CT_EN_MASK                   (0x10U)
#define SNVS_LPTDCR_CT_EN_SHIFT                  (4U)
/*! CT_EN
 *  0b0..Clock tamper is disabled.
 *  0b1..Clock tamper is enabled.
 */
#define SNVS_LPTDCR_CT_EN(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_CT_EN_SHIFT)) & SNVS_LPTDCR_CT_EN_MASK)

#define SNVS_LPTDCR_TT_EN_MASK                   (0x20U)
#define SNVS_LPTDCR_TT_EN_SHIFT                  (5U)
/*! TT_EN
 *  0b0..Temperature tamper is disabled.
 *  0b1..Temperature tamper is enabled.
 */
#define SNVS_LPTDCR_TT_EN(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_TT_EN_SHIFT)) & SNVS_LPTDCR_TT_EN_MASK)

#define SNVS_LPTDCR_VT_EN_MASK                   (0x40U)
#define SNVS_LPTDCR_VT_EN_SHIFT                  (6U)
/*! VT_EN
 *  0b0..Voltage tamper is disabled.
 *  0b1..Voltage tamper is enabled.
 */
#define SNVS_LPTDCR_VT_EN(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_VT_EN_SHIFT)) & SNVS_LPTDCR_VT_EN_MASK)

#define SNVS_LPTDCR_WMT1_EN_MASK                 (0x80U)
#define SNVS_LPTDCR_WMT1_EN_SHIFT                (7U)
/*! WMT1_EN
 *  0b0..Wire-mesh tamper 1 is disabled.
 *  0b1..Wire-mesh tamper 1 is enabled.
 */
#define SNVS_LPTDCR_WMT1_EN(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_WMT1_EN_SHIFT)) & SNVS_LPTDCR_WMT1_EN_MASK)

#define SNVS_LPTDCR_WMT2_EN_MASK                 (0x100U)
#define SNVS_LPTDCR_WMT2_EN_SHIFT                (8U)
/*! WMT2_EN
 *  0b0..Wire-mesh tamper 2 is disabled.
 *  0b1..Wire-mesh tamper 2 is enabled.
 */
#define SNVS_LPTDCR_WMT2_EN(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_WMT2_EN_SHIFT)) & SNVS_LPTDCR_WMT2_EN_MASK)

#define SNVS_LPTDCR_ET1_EN_MASK                  (0x200U)
#define SNVS_LPTDCR_ET1_EN_SHIFT                 (9U)
/*! ET1_EN
 *  0b0..External tamper 1 is disabled.
 *  0b1..External tamper 1 is enabled.
 */
#define SNVS_LPTDCR_ET1_EN(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_ET1_EN_SHIFT)) & SNVS_LPTDCR_ET1_EN_MASK)

#define SNVS_LPTDCR_ET2_EN_MASK                  (0x400U)
#define SNVS_LPTDCR_ET2_EN_SHIFT                 (10U)
/*! ET2_EN
 *  0b0..External tamper 2 is disabled.
 *  0b1..External tamper 2 is enabled.
 */
#define SNVS_LPTDCR_ET2_EN(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_ET2_EN_SHIFT)) & SNVS_LPTDCR_ET2_EN_MASK)

#define SNVS_LPTDCR_ET1P_MASK                    (0x800U)
#define SNVS_LPTDCR_ET1P_SHIFT                   (11U)
/*! ET1P
 *  0b0..External tamper 1 is active low.
 *  0b1..External tamper 1 is active high.
 */
#define SNVS_LPTDCR_ET1P(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_ET1P_SHIFT)) & SNVS_LPTDCR_ET1P_MASK)

#define SNVS_LPTDCR_ET2P_MASK                    (0x1000U)
#define SNVS_LPTDCR_ET2P_SHIFT                   (12U)
/*! ET2P
 *  0b0..External tamper 2 is active low.
 *  0b1..External tamper 2 is active high.
 */
#define SNVS_LPTDCR_ET2P(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_ET2P_SHIFT)) & SNVS_LPTDCR_ET2P_MASK)

#define SNVS_LPTDCR_PFD_OBSERV_MASK              (0x4000U)
#define SNVS_LPTDCR_PFD_OBSERV_SHIFT             (14U)
#define SNVS_LPTDCR_PFD_OBSERV(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_PFD_OBSERV_SHIFT)) & SNVS_LPTDCR_PFD_OBSERV_MASK)

#define SNVS_LPTDCR_POR_OBSERV_MASK              (0x8000U)
#define SNVS_LPTDCR_POR_OBSERV_SHIFT             (15U)
#define SNVS_LPTDCR_POR_OBSERV(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_POR_OBSERV_SHIFT)) & SNVS_LPTDCR_POR_OBSERV_MASK)

#define SNVS_LPTDCR_LTDC_MASK                    (0x70000U)
#define SNVS_LPTDCR_LTDC_SHIFT                   (16U)
#define SNVS_LPTDCR_LTDC(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_LTDC_SHIFT)) & SNVS_LPTDCR_LTDC_MASK)

#define SNVS_LPTDCR_HTDC_MASK                    (0x700000U)
#define SNVS_LPTDCR_HTDC_SHIFT                   (20U)
#define SNVS_LPTDCR_HTDC(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_HTDC_SHIFT)) & SNVS_LPTDCR_HTDC_MASK)

#define SNVS_LPTDCR_VRC_MASK                     (0x7000000U)
#define SNVS_LPTDCR_VRC_SHIFT                    (24U)
#define SNVS_LPTDCR_VRC(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_VRC_SHIFT)) & SNVS_LPTDCR_VRC_MASK)

#define SNVS_LPTDCR_OSCB_MASK                    (0x10000000U)
#define SNVS_LPTDCR_OSCB_SHIFT                   (28U)
/*! OSCB
 *  0b0..Normal SRTC clock oscillator not bypassed.
 *  0b1..Normal SRTC clock oscillator bypassed. Alternate clock can drive the SRTC clock source.
 */
#define SNVS_LPTDCR_OSCB(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDCR_OSCB_SHIFT)) & SNVS_LPTDCR_OSCB_MASK)
/*! @} */

/*! @name LPSR - SNVS_LP Status Register */
/*! @{ */

#define SNVS_LPSR_LPTA_MASK                      (0x1U)
#define SNVS_LPSR_LPTA_SHIFT                     (0U)
/*! LPTA
 *  0b0..No time alarm interrupt occurred.
 *  0b1..A time alarm interrupt occurred.
 */
#define SNVS_LPSR_LPTA(x)                        (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_LPTA_SHIFT)) & SNVS_LPSR_LPTA_MASK)

#define SNVS_LPSR_SRTCR_MASK                     (0x2U)
#define SNVS_LPSR_SRTCR_SHIFT                    (1U)
/*! SRTCR
 *  0b0..SRTC has not reached its maximum value.
 *  0b1..SRTC has reached its maximum value.
 */
#define SNVS_LPSR_SRTCR(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_SRTCR_SHIFT)) & SNVS_LPSR_SRTCR_MASK)

#define SNVS_LPSR_MCR_MASK                       (0x4U)
#define SNVS_LPSR_MCR_SHIFT                      (2U)
/*! MCR
 *  0b0..MC has not reached its maximum value.
 *  0b1..MC has reached its maximum value.
 */
#define SNVS_LPSR_MCR(x)                         (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_MCR_SHIFT)) & SNVS_LPSR_MCR_MASK)

#define SNVS_LPSR_LVD_MASK                       (0x8U)
#define SNVS_LPSR_LVD_SHIFT                      (3U)
/*! LVD
 *  0b0..No low voltage event detected.
 *  0b1..Low voltage event is detected.
 */
#define SNVS_LPSR_LVD(x)                         (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_LVD_SHIFT)) & SNVS_LPSR_LVD_MASK)

#define SNVS_LPSR_CTD_MASK                       (0x10U)
#define SNVS_LPSR_CTD_SHIFT                      (4U)
/*! CTD
 *  0b0..No clock tamper.
 *  0b1..Clock tamper is detected.
 */
#define SNVS_LPSR_CTD(x)                         (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_CTD_SHIFT)) & SNVS_LPSR_CTD_MASK)

#define SNVS_LPSR_TTD_MASK                       (0x20U)
#define SNVS_LPSR_TTD_SHIFT                      (5U)
/*! TTD
 *  0b0..No temperature tamper.
 *  0b1..Temperature tamper is detected.
 */
#define SNVS_LPSR_TTD(x)                         (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_TTD_SHIFT)) & SNVS_LPSR_TTD_MASK)

#define SNVS_LPSR_VTD_MASK                       (0x40U)
#define SNVS_LPSR_VTD_SHIFT                      (6U)
/*! VTD
 *  0b0..Voltage tampering not detected.
 *  0b1..Voltage tampering detected.
 */
#define SNVS_LPSR_VTD(x)                         (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_VTD_SHIFT)) & SNVS_LPSR_VTD_MASK)

#define SNVS_LPSR_WMT1D_MASK                     (0x80U)
#define SNVS_LPSR_WMT1D_SHIFT                    (7U)
/*! WMT1D
 *  0b0..Wire-mesh tampering 1 not detected.
 *  0b1..Wire-mesh tampering 1 detected.
 */
#define SNVS_LPSR_WMT1D(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_WMT1D_SHIFT)) & SNVS_LPSR_WMT1D_MASK)

#define SNVS_LPSR_WMT2D_MASK                     (0x100U)
#define SNVS_LPSR_WMT2D_SHIFT                    (8U)
/*! WMT2D
 *  0b0..Wire-mesh tampering 2 not detected.
 *  0b1..Wire-mesh tampering 2 detected.
 */
#define SNVS_LPSR_WMT2D(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_WMT2D_SHIFT)) & SNVS_LPSR_WMT2D_MASK)

#define SNVS_LPSR_ET1D_MASK                      (0x200U)
#define SNVS_LPSR_ET1D_SHIFT                     (9U)
/*! ET1D
 *  0b0..External tampering 1 not detected.
 *  0b1..External tampering 1 detected.
 */
#define SNVS_LPSR_ET1D(x)                        (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_ET1D_SHIFT)) & SNVS_LPSR_ET1D_MASK)

#define SNVS_LPSR_ET2D_MASK                      (0x400U)
#define SNVS_LPSR_ET2D_SHIFT                     (10U)
/*! ET2D
 *  0b0..External tampering 2 not detected.
 *  0b1..External tampering 2 detected.
 */
#define SNVS_LPSR_ET2D(x)                        (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_ET2D_SHIFT)) & SNVS_LPSR_ET2D_MASK)

#define SNVS_LPSR_ESVD_MASK                      (0x10000U)
#define SNVS_LPSR_ESVD_SHIFT                     (16U)
/*! ESVD
 *  0b0..No external security violation.
 *  0b1..External security violation is detected.
 */
#define SNVS_LPSR_ESVD(x)                        (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_ESVD_SHIFT)) & SNVS_LPSR_ESVD_MASK)

#define SNVS_LPSR_EO_MASK                        (0x20000U)
#define SNVS_LPSR_EO_SHIFT                       (17U)
/*! EO
 *  0b0..Emergency off was not detected.
 *  0b1..Emergency off was detected.
 */
#define SNVS_LPSR_EO(x)                          (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_EO_SHIFT)) & SNVS_LPSR_EO_MASK)

#define SNVS_LPSR_SPOF_MASK                      (0x40000U)
#define SNVS_LPSR_SPOF_SHIFT                     (18U)
/*! SPOF
 *  0b0..Set Power Off was not detected.
 *  0b1..Set Power Off was detected.
 */
#define SNVS_LPSR_SPOF(x)                        (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_SPOF_SHIFT)) & SNVS_LPSR_SPOF_MASK)

#define SNVS_LPSR_LPNS_MASK                      (0x40000000U)
#define SNVS_LPSR_LPNS_SHIFT                     (30U)
/*! LPNS
 *  0b0..LP section was not programmed in the non-secure state.
 *  0b1..LP section was programmed in the non-secure state.
 */
#define SNVS_LPSR_LPNS(x)                        (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_LPNS_SHIFT)) & SNVS_LPSR_LPNS_MASK)

#define SNVS_LPSR_LPS_MASK                       (0x80000000U)
#define SNVS_LPSR_LPS_SHIFT                      (31U)
/*! LPS
 *  0b0..LP section was not programmed in secure or trusted state.
 *  0b1..LP section was programmed in secure or trusted state.
 */
#define SNVS_LPSR_LPS(x)                         (((uint32_t)(((uint32_t)(x)) << SNVS_LPSR_LPS_SHIFT)) & SNVS_LPSR_LPS_MASK)
/*! @} */

/*! @name LPSRTCMR - SNVS_LP Secure Real Time Counter MSB Register */
/*! @{ */

#define SNVS_LPSRTCMR_SRTC_MASK                  (0x7FFFU)
#define SNVS_LPSRTCMR_SRTC_SHIFT                 (0U)
#define SNVS_LPSRTCMR_SRTC(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_LPSRTCMR_SRTC_SHIFT)) & SNVS_LPSRTCMR_SRTC_MASK)
/*! @} */

/*! @name LPSRTCLR - SNVS_LP Secure Real Time Counter LSB Register */
/*! @{ */

#define SNVS_LPSRTCLR_SRTC_MASK                  (0xFFFFFFFFU)
#define SNVS_LPSRTCLR_SRTC_SHIFT                 (0U)
#define SNVS_LPSRTCLR_SRTC(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_LPSRTCLR_SRTC_SHIFT)) & SNVS_LPSRTCLR_SRTC_MASK)
/*! @} */

/*! @name LPTAR - SNVS_LP Time Alarm Register */
/*! @{ */

#define SNVS_LPTAR_LPTA_MASK                     (0xFFFFFFFFU)
#define SNVS_LPTAR_LPTA_SHIFT                    (0U)
#define SNVS_LPTAR_LPTA(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_LPTAR_LPTA_SHIFT)) & SNVS_LPTAR_LPTA_MASK)
/*! @} */

/*! @name LPSMCMR - SNVS_LP Secure Monotonic Counter MSB Register */
/*! @{ */

#define SNVS_LPSMCMR_MON_COUNTER_MASK            (0xFFFFU)
#define SNVS_LPSMCMR_MON_COUNTER_SHIFT           (0U)
#define SNVS_LPSMCMR_MON_COUNTER(x)              (((uint32_t)(((uint32_t)(x)) << SNVS_LPSMCMR_MON_COUNTER_SHIFT)) & SNVS_LPSMCMR_MON_COUNTER_MASK)

#define SNVS_LPSMCMR_MC_ERA_BITS_MASK            (0xFFFF0000U)
#define SNVS_LPSMCMR_MC_ERA_BITS_SHIFT           (16U)
#define SNVS_LPSMCMR_MC_ERA_BITS(x)              (((uint32_t)(((uint32_t)(x)) << SNVS_LPSMCMR_MC_ERA_BITS_SHIFT)) & SNVS_LPSMCMR_MC_ERA_BITS_MASK)
/*! @} */

/*! @name LPSMCLR - SNVS_LP Secure Monotonic Counter LSB Register */
/*! @{ */

#define SNVS_LPSMCLR_MON_COUNTER_MASK            (0xFFFFFFFFU)
#define SNVS_LPSMCLR_MON_COUNTER_SHIFT           (0U)
#define SNVS_LPSMCLR_MON_COUNTER(x)              (((uint32_t)(((uint32_t)(x)) << SNVS_LPSMCLR_MON_COUNTER_SHIFT)) & SNVS_LPSMCLR_MON_COUNTER_MASK)
/*! @} */

/*! @name LPLVDR - SNVS_LP Digital Low-Voltage Detector Register */
/*! @{ */

#define SNVS_LPLVDR_LVD_MASK                     (0xFFFFFFFFU)
#define SNVS_LPLVDR_LVD_SHIFT                    (0U)
#define SNVS_LPLVDR_LVD(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_LPLVDR_LVD_SHIFT)) & SNVS_LPLVDR_LVD_MASK)
/*! @} */

/*! @name LPGPR0_LEGACY_ALIAS - SNVS_LP General Purpose Register 0 (legacy alias) */
/*! @{ */

#define SNVS_LPGPR0_LEGACY_ALIAS_GPR_MASK        (0xFFFFFFFFU)
#define SNVS_LPGPR0_LEGACY_ALIAS_GPR_SHIFT       (0U)
#define SNVS_LPGPR0_LEGACY_ALIAS_GPR(x)          (((uint32_t)(((uint32_t)(x)) << SNVS_LPGPR0_LEGACY_ALIAS_GPR_SHIFT)) & SNVS_LPGPR0_LEGACY_ALIAS_GPR_MASK)
/*! @} */

/*! @name LPZMKR - SNVS_LP Zeroizable Master Key Register */
/*! @{ */

#define SNVS_LPZMKR_ZMK_MASK                     (0xFFFFFFFFU)
#define SNVS_LPZMKR_ZMK_SHIFT                    (0U)
#define SNVS_LPZMKR_ZMK(x)                       (((uint32_t)(((uint32_t)(x)) << SNVS_LPZMKR_ZMK_SHIFT)) & SNVS_LPZMKR_ZMK_MASK)
/*! @} */

/*! @name LPGPR_ALIAS - SNVS_LP General Purpose Registers 0 .. 3 */
/*! @{ */

#define SNVS_LPGPR_ALIAS_GPR_MASK                (0xFFFFFFFFU)
#define SNVS_LPGPR_ALIAS_GPR_SHIFT               (0U)
#define SNVS_LPGPR_ALIAS_GPR(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPGPR_ALIAS_GPR_SHIFT)) & SNVS_LPGPR_ALIAS_GPR_MASK)
/*! @} */

/* The count of SNVS_LPGPR_ALIAS */
#define SNVS_LPGPR_ALIAS_COUNT                   (4U)

/*! @name LPTDC2R - SNVS_LP Tamper Detectors Config 2 Register */
/*! @{ */

#define SNVS_LPTDC2R_ET3_EN_MASK                 (0x1U)
#define SNVS_LPTDC2R_ET3_EN_SHIFT                (0U)
/*! ET3_EN
 *  0b0..External tamper 3 is disabled.
 *  0b1..External tamper 3 is enabled.
 */
#define SNVS_LPTDC2R_ET3_EN(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET3_EN_SHIFT)) & SNVS_LPTDC2R_ET3_EN_MASK)

#define SNVS_LPTDC2R_ET4_EN_MASK                 (0x2U)
#define SNVS_LPTDC2R_ET4_EN_SHIFT                (1U)
/*! ET4_EN
 *  0b0..External tamper 4 is disabled.
 *  0b1..External tamper 4 is enabled.
 */
#define SNVS_LPTDC2R_ET4_EN(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET4_EN_SHIFT)) & SNVS_LPTDC2R_ET4_EN_MASK)

#define SNVS_LPTDC2R_ET5_EN_MASK                 (0x4U)
#define SNVS_LPTDC2R_ET5_EN_SHIFT                (2U)
/*! ET5_EN
 *  0b0..External tamper 5 is disabled.
 *  0b1..External tamper 5 is enabled.
 */
#define SNVS_LPTDC2R_ET5_EN(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET5_EN_SHIFT)) & SNVS_LPTDC2R_ET5_EN_MASK)

#define SNVS_LPTDC2R_ET6_EN_MASK                 (0x8U)
#define SNVS_LPTDC2R_ET6_EN_SHIFT                (3U)
/*! ET6_EN
 *  0b0..External tamper 6 is disabled.
 *  0b1..External tamper 6 is enabled.
 */
#define SNVS_LPTDC2R_ET6_EN(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET6_EN_SHIFT)) & SNVS_LPTDC2R_ET6_EN_MASK)

#define SNVS_LPTDC2R_ET7_EN_MASK                 (0x10U)
#define SNVS_LPTDC2R_ET7_EN_SHIFT                (4U)
/*! ET7_EN
 *  0b0..External tamper 7 is disabled.
 *  0b1..External tamper 7 is enabled.
 */
#define SNVS_LPTDC2R_ET7_EN(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET7_EN_SHIFT)) & SNVS_LPTDC2R_ET7_EN_MASK)

#define SNVS_LPTDC2R_ET8_EN_MASK                 (0x20U)
#define SNVS_LPTDC2R_ET8_EN_SHIFT                (5U)
/*! ET8_EN
 *  0b0..External tamper 8 is disabled.
 *  0b1..External tamper 8 is enabled.
 */
#define SNVS_LPTDC2R_ET8_EN(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET8_EN_SHIFT)) & SNVS_LPTDC2R_ET8_EN_MASK)

#define SNVS_LPTDC2R_ET9_EN_MASK                 (0x40U)
#define SNVS_LPTDC2R_ET9_EN_SHIFT                (6U)
/*! ET9_EN
 *  0b0..External tamper 9 is disabled.
 *  0b1..External tamper 9 is enabled.
 */
#define SNVS_LPTDC2R_ET9_EN(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET9_EN_SHIFT)) & SNVS_LPTDC2R_ET9_EN_MASK)

#define SNVS_LPTDC2R_ET10_EN_MASK                (0x80U)
#define SNVS_LPTDC2R_ET10_EN_SHIFT               (7U)
/*! ET10_EN
 *  0b0..External tamper 10 is disabled.
 *  0b1..External tamper 10 is enabled.
 */
#define SNVS_LPTDC2R_ET10_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET10_EN_SHIFT)) & SNVS_LPTDC2R_ET10_EN_MASK)

#define SNVS_LPTDC2R_ET3P_MASK                   (0x10000U)
#define SNVS_LPTDC2R_ET3P_SHIFT                  (16U)
/*! ET3P
 *  0b0..External tamper 3 active low.
 *  0b1..External tamper 3 active high.
 */
#define SNVS_LPTDC2R_ET3P(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET3P_SHIFT)) & SNVS_LPTDC2R_ET3P_MASK)

#define SNVS_LPTDC2R_ET4P_MASK                   (0x20000U)
#define SNVS_LPTDC2R_ET4P_SHIFT                  (17U)
/*! ET4P
 *  0b0..External tamper 4 is active low.
 *  0b1..External tamper 4 is active high.
 */
#define SNVS_LPTDC2R_ET4P(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET4P_SHIFT)) & SNVS_LPTDC2R_ET4P_MASK)

#define SNVS_LPTDC2R_ET5P_MASK                   (0x40000U)
#define SNVS_LPTDC2R_ET5P_SHIFT                  (18U)
/*! ET5P
 *  0b0..External tamper 5 is active low.
 *  0b1..External tamper 5 is active high.
 */
#define SNVS_LPTDC2R_ET5P(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET5P_SHIFT)) & SNVS_LPTDC2R_ET5P_MASK)

#define SNVS_LPTDC2R_ET6P_MASK                   (0x80000U)
#define SNVS_LPTDC2R_ET6P_SHIFT                  (19U)
/*! ET6P
 *  0b0..External tamper 6 is active low.
 *  0b1..External tamper 6 is active high.
 */
#define SNVS_LPTDC2R_ET6P(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET6P_SHIFT)) & SNVS_LPTDC2R_ET6P_MASK)

#define SNVS_LPTDC2R_ET7P_MASK                   (0x100000U)
#define SNVS_LPTDC2R_ET7P_SHIFT                  (20U)
/*! ET7P
 *  0b0..External tamper 7 is active low.
 *  0b1..External tamper 7 is active high.
 */
#define SNVS_LPTDC2R_ET7P(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET7P_SHIFT)) & SNVS_LPTDC2R_ET7P_MASK)

#define SNVS_LPTDC2R_ET8P_MASK                   (0x200000U)
#define SNVS_LPTDC2R_ET8P_SHIFT                  (21U)
/*! ET8P
 *  0b0..External tamper 8 is active low.
 *  0b1..External tamper 8 is active high.
 */
#define SNVS_LPTDC2R_ET8P(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET8P_SHIFT)) & SNVS_LPTDC2R_ET8P_MASK)

#define SNVS_LPTDC2R_ET9P_MASK                   (0x400000U)
#define SNVS_LPTDC2R_ET9P_SHIFT                  (22U)
/*! ET9P
 *  0b0..External tamper 9 is active low.
 *  0b1..External tamper 9 is active high.
 */
#define SNVS_LPTDC2R_ET9P(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET9P_SHIFT)) & SNVS_LPTDC2R_ET9P_MASK)

#define SNVS_LPTDC2R_ET10P_MASK                  (0x800000U)
#define SNVS_LPTDC2R_ET10P_SHIFT                 (23U)
/*! ET10P
 *  0b0..External tamper 10 is active low.
 *  0b1..External tamper 10 is active high.
 */
#define SNVS_LPTDC2R_ET10P(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDC2R_ET10P_SHIFT)) & SNVS_LPTDC2R_ET10P_MASK)
/*! @} */

/*! @name LPTDSR - SNVS_LP Tamper Detectors Status Register */
/*! @{ */

#define SNVS_LPTDSR_ET3D_MASK                    (0x1U)
#define SNVS_LPTDSR_ET3D_SHIFT                   (0U)
/*! ET3D
 *  0b0..External tamper 3 is not detected.
 *  0b1..External tamper 3 is detected.
 */
#define SNVS_LPTDSR_ET3D(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDSR_ET3D_SHIFT)) & SNVS_LPTDSR_ET3D_MASK)

#define SNVS_LPTDSR_ET4D_MASK                    (0x2U)
#define SNVS_LPTDSR_ET4D_SHIFT                   (1U)
/*! ET4D
 *  0b0..External tamper 4 is not detected.
 *  0b1..External tamper 4 is detected.
 */
#define SNVS_LPTDSR_ET4D(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDSR_ET4D_SHIFT)) & SNVS_LPTDSR_ET4D_MASK)

#define SNVS_LPTDSR_ET5D_MASK                    (0x4U)
#define SNVS_LPTDSR_ET5D_SHIFT                   (2U)
/*! ET5D
 *  0b0..External tamper 5 is not detected.
 *  0b1..External tamper 5 is detected.
 */
#define SNVS_LPTDSR_ET5D(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDSR_ET5D_SHIFT)) & SNVS_LPTDSR_ET5D_MASK)

#define SNVS_LPTDSR_ET6D_MASK                    (0x8U)
#define SNVS_LPTDSR_ET6D_SHIFT                   (3U)
/*! ET6D
 *  0b0..External tamper 6 is not detected.
 *  0b1..External tamper 6 is detected.
 */
#define SNVS_LPTDSR_ET6D(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDSR_ET6D_SHIFT)) & SNVS_LPTDSR_ET6D_MASK)

#define SNVS_LPTDSR_ET7D_MASK                    (0x10U)
#define SNVS_LPTDSR_ET7D_SHIFT                   (4U)
/*! ET7D
 *  0b0..External tamper 7 is not detected.
 *  0b1..External tamper 7 is detected.
 */
#define SNVS_LPTDSR_ET7D(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDSR_ET7D_SHIFT)) & SNVS_LPTDSR_ET7D_MASK)

#define SNVS_LPTDSR_ET8D_MASK                    (0x20U)
#define SNVS_LPTDSR_ET8D_SHIFT                   (5U)
/*! ET8D
 *  0b0..External tamper 8 is not detected.
 *  0b1..External tamper 8 is detected.
 */
#define SNVS_LPTDSR_ET8D(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDSR_ET8D_SHIFT)) & SNVS_LPTDSR_ET8D_MASK)

#define SNVS_LPTDSR_ET9D_MASK                    (0x40U)
#define SNVS_LPTDSR_ET9D_SHIFT                   (6U)
/*! ET9D
 *  0b0..External tamper 9 is not detected.
 *  0b1..External tamper 9 is detected.
 */
#define SNVS_LPTDSR_ET9D(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDSR_ET9D_SHIFT)) & SNVS_LPTDSR_ET9D_MASK)

#define SNVS_LPTDSR_ET10D_MASK                   (0x80U)
#define SNVS_LPTDSR_ET10D_SHIFT                  (7U)
/*! ET10D
 *  0b0..External tamper 10 is not detected.
 *  0b1..External tamper 10 is detected.
 */
#define SNVS_LPTDSR_ET10D(x)                     (((uint32_t)(((uint32_t)(x)) << SNVS_LPTDSR_ET10D_SHIFT)) & SNVS_LPTDSR_ET10D_MASK)
/*! @} */

/*! @name LPTGF1CR - SNVS_LP Tamper Glitch Filter 1 Configuration Register */
/*! @{ */

#define SNVS_LPTGF1CR_ETGF3_MASK                 (0x7FU)
#define SNVS_LPTGF1CR_ETGF3_SHIFT                (0U)
#define SNVS_LPTGF1CR_ETGF3(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF1CR_ETGF3_SHIFT)) & SNVS_LPTGF1CR_ETGF3_MASK)

#define SNVS_LPTGF1CR_ETGF3_EN_MASK              (0x80U)
#define SNVS_LPTGF1CR_ETGF3_EN_SHIFT             (7U)
/*! ETGF3_EN
 *  0b0..External tamper glitch filter 3 is bypassed.
 *  0b1..External tamper glitch filter 3 is enabled.
 */
#define SNVS_LPTGF1CR_ETGF3_EN(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF1CR_ETGF3_EN_SHIFT)) & SNVS_LPTGF1CR_ETGF3_EN_MASK)

#define SNVS_LPTGF1CR_ETGF4_MASK                 (0x7F00U)
#define SNVS_LPTGF1CR_ETGF4_SHIFT                (8U)
#define SNVS_LPTGF1CR_ETGF4(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF1CR_ETGF4_SHIFT)) & SNVS_LPTGF1CR_ETGF4_MASK)

#define SNVS_LPTGF1CR_ETGF4_EN_MASK              (0x8000U)
#define SNVS_LPTGF1CR_ETGF4_EN_SHIFT             (15U)
/*! ETGF4_EN
 *  0b0..External tamper glitch filter 4 is bypassed.
 *  0b1..External tamper glitch filter 4 is enabled.
 */
#define SNVS_LPTGF1CR_ETGF4_EN(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF1CR_ETGF4_EN_SHIFT)) & SNVS_LPTGF1CR_ETGF4_EN_MASK)

#define SNVS_LPTGF1CR_ETGF5_MASK                 (0x7F0000U)
#define SNVS_LPTGF1CR_ETGF5_SHIFT                (16U)
#define SNVS_LPTGF1CR_ETGF5(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF1CR_ETGF5_SHIFT)) & SNVS_LPTGF1CR_ETGF5_MASK)

#define SNVS_LPTGF1CR_ETGF5_EN_MASK              (0x800000U)
#define SNVS_LPTGF1CR_ETGF5_EN_SHIFT             (23U)
/*! ETGF5_EN
 *  0b0..External tamper glitch filter 5 is bypassed.
 *  0b1..External tamper glitch filter 5 is enabled.
 */
#define SNVS_LPTGF1CR_ETGF5_EN(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF1CR_ETGF5_EN_SHIFT)) & SNVS_LPTGF1CR_ETGF5_EN_MASK)

#define SNVS_LPTGF1CR_ETGF6_MASK                 (0x7F000000U)
#define SNVS_LPTGF1CR_ETGF6_SHIFT                (24U)
#define SNVS_LPTGF1CR_ETGF6(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF1CR_ETGF6_SHIFT)) & SNVS_LPTGF1CR_ETGF6_MASK)

#define SNVS_LPTGF1CR_ETGF6_EN_MASK              (0x80000000U)
#define SNVS_LPTGF1CR_ETGF6_EN_SHIFT             (31U)
/*! ETGF6_EN
 *  0b0..External tamper glitch filter 6 is bypassed.
 *  0b1..External tamper glitch filter 6 is enabled.
 */
#define SNVS_LPTGF1CR_ETGF6_EN(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF1CR_ETGF6_EN_SHIFT)) & SNVS_LPTGF1CR_ETGF6_EN_MASK)
/*! @} */

/*! @name LPTGF2CR - SNVS_LP Tamper Glitch Filter 2 Configuration Register */
/*! @{ */

#define SNVS_LPTGF2CR_ETGF7_MASK                 (0x7FU)
#define SNVS_LPTGF2CR_ETGF7_SHIFT                (0U)
#define SNVS_LPTGF2CR_ETGF7(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF2CR_ETGF7_SHIFT)) & SNVS_LPTGF2CR_ETGF7_MASK)

#define SNVS_LPTGF2CR_ETGF7_EN_MASK              (0x80U)
#define SNVS_LPTGF2CR_ETGF7_EN_SHIFT             (7U)
/*! ETGF7_EN
 *  0b0..External tamper glitch filter 7 is bypassed.
 *  0b1..External tamper glitch filter 7 is enabled.
 */
#define SNVS_LPTGF2CR_ETGF7_EN(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF2CR_ETGF7_EN_SHIFT)) & SNVS_LPTGF2CR_ETGF7_EN_MASK)

#define SNVS_LPTGF2CR_ETGF8_MASK                 (0x7F00U)
#define SNVS_LPTGF2CR_ETGF8_SHIFT                (8U)
#define SNVS_LPTGF2CR_ETGF8(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF2CR_ETGF8_SHIFT)) & SNVS_LPTGF2CR_ETGF8_MASK)

#define SNVS_LPTGF2CR_ETGF8_EN_MASK              (0x8000U)
#define SNVS_LPTGF2CR_ETGF8_EN_SHIFT             (15U)
/*! ETGF8_EN
 *  0b0..External tamper glitch filter 8 is bypassed.
 *  0b1..External tamper glitch filter 8 is enabled.
 */
#define SNVS_LPTGF2CR_ETGF8_EN(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF2CR_ETGF8_EN_SHIFT)) & SNVS_LPTGF2CR_ETGF8_EN_MASK)

#define SNVS_LPTGF2CR_ETGF9_MASK                 (0x7F0000U)
#define SNVS_LPTGF2CR_ETGF9_SHIFT                (16U)
#define SNVS_LPTGF2CR_ETGF9(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF2CR_ETGF9_SHIFT)) & SNVS_LPTGF2CR_ETGF9_MASK)

#define SNVS_LPTGF2CR_ETGF9_EN_MASK              (0x800000U)
#define SNVS_LPTGF2CR_ETGF9_EN_SHIFT             (23U)
/*! ETGF9_EN
 *  0b0..External tamper glitch filter 9 is bypassed.
 *  0b1..External tamper glitch filter 9 is enabled.
 */
#define SNVS_LPTGF2CR_ETGF9_EN(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF2CR_ETGF9_EN_SHIFT)) & SNVS_LPTGF2CR_ETGF9_EN_MASK)

#define SNVS_LPTGF2CR_ETGF10_MASK                (0x7F000000U)
#define SNVS_LPTGF2CR_ETGF10_SHIFT               (24U)
#define SNVS_LPTGF2CR_ETGF10(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF2CR_ETGF10_SHIFT)) & SNVS_LPTGF2CR_ETGF10_MASK)

#define SNVS_LPTGF2CR_ETGF10_EN_MASK             (0x80000000U)
#define SNVS_LPTGF2CR_ETGF10_EN_SHIFT            (31U)
/*! ETGF10_EN
 *  0b0..External tamper glitch filter 10 is bypassed.
 *  0b1..External tamper glitch filter 10 is enabled.
 */
#define SNVS_LPTGF2CR_ETGF10_EN(x)               (((uint32_t)(((uint32_t)(x)) << SNVS_LPTGF2CR_ETGF10_EN_SHIFT)) & SNVS_LPTGF2CR_ETGF10_EN_MASK)
/*! @} */

/*! @name LPATCR - SNVS_LP Active Tamper 1 Configuration Register..SNVS_LP Active Tamper 5 Configuration Register */
/*! @{ */

#define SNVS_LPATCR_Seed_MASK                    (0xFFFFU)
#define SNVS_LPATCR_Seed_SHIFT                   (0U)
#define SNVS_LPATCR_Seed(x)                      (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCR_Seed_SHIFT)) & SNVS_LPATCR_Seed_MASK)

#define SNVS_LPATCR_Polynomial_MASK              (0xFFFF0000U)
#define SNVS_LPATCR_Polynomial_SHIFT             (16U)
#define SNVS_LPATCR_Polynomial(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCR_Polynomial_SHIFT)) & SNVS_LPATCR_Polynomial_MASK)
/*! @} */

/*! @name LPATCTLR - SNVS_LP Active Tamper Control Register */
/*! @{ */

#define SNVS_LPATCTLR_AT1_EN_MASK                (0x1U)
#define SNVS_LPATCTLR_AT1_EN_SHIFT               (0U)
/*! AT1_EN
 *  0b0..Active Tamper 1 is disabled.
 *  0b1..Active Tamper 1 is enabled.
 */
#define SNVS_LPATCTLR_AT1_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCTLR_AT1_EN_SHIFT)) & SNVS_LPATCTLR_AT1_EN_MASK)

#define SNVS_LPATCTLR_AT2_EN_MASK                (0x2U)
#define SNVS_LPATCTLR_AT2_EN_SHIFT               (1U)
/*! AT2_EN
 *  0b0..Active Tamper 2 is disabled.
 *  0b1..Active Tamper 2 is enabled.
 */
#define SNVS_LPATCTLR_AT2_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCTLR_AT2_EN_SHIFT)) & SNVS_LPATCTLR_AT2_EN_MASK)

#define SNVS_LPATCTLR_AT3_EN_MASK                (0x4U)
#define SNVS_LPATCTLR_AT3_EN_SHIFT               (2U)
/*! AT3_EN
 *  0b0..Active Tamper 3 is disabled.
 *  0b1..Active Tamper 3 is enabled.
 */
#define SNVS_LPATCTLR_AT3_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCTLR_AT3_EN_SHIFT)) & SNVS_LPATCTLR_AT3_EN_MASK)

#define SNVS_LPATCTLR_AT4_EN_MASK                (0x8U)
#define SNVS_LPATCTLR_AT4_EN_SHIFT               (3U)
/*! AT4_EN
 *  0b0..Active Tamper 4 is disabled.
 *  0b1..Active Tamper 4 is enabled.
 */
#define SNVS_LPATCTLR_AT4_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCTLR_AT4_EN_SHIFT)) & SNVS_LPATCTLR_AT4_EN_MASK)

#define SNVS_LPATCTLR_AT5_EN_MASK                (0x10U)
#define SNVS_LPATCTLR_AT5_EN_SHIFT               (4U)
/*! AT5_EN
 *  0b0..Active Tamper 5 is disabled.
 *  0b1..Active Tamper 5 is enabled.
 */
#define SNVS_LPATCTLR_AT5_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCTLR_AT5_EN_SHIFT)) & SNVS_LPATCTLR_AT5_EN_MASK)

#define SNVS_LPATCTLR_AT1_PAD_EN_MASK            (0x10000U)
#define SNVS_LPATCTLR_AT1_PAD_EN_SHIFT           (16U)
/*! AT1_PAD_EN
 *  0b0..Active Tamper 1 is disabled.
 *  0b1..Active Tamper 1 is enabled.
 */
#define SNVS_LPATCTLR_AT1_PAD_EN(x)              (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCTLR_AT1_PAD_EN_SHIFT)) & SNVS_LPATCTLR_AT1_PAD_EN_MASK)

#define SNVS_LPATCTLR_AT2_PAD_EN_MASK            (0x20000U)
#define SNVS_LPATCTLR_AT2_PAD_EN_SHIFT           (17U)
/*! AT2_PAD_EN
 *  0b0..Active Tamper 2 is disabled.
 *  0b1..Active Tamper 2 is enabled.
 */
#define SNVS_LPATCTLR_AT2_PAD_EN(x)              (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCTLR_AT2_PAD_EN_SHIFT)) & SNVS_LPATCTLR_AT2_PAD_EN_MASK)

#define SNVS_LPATCTLR_AT3_PAD_EN_MASK            (0x40000U)
#define SNVS_LPATCTLR_AT3_PAD_EN_SHIFT           (18U)
/*! AT3_PAD_EN
 *  0b0..Active Tamper 3 is disabled.
 *  0b1..Active Tamper 3 is enabled
 */
#define SNVS_LPATCTLR_AT3_PAD_EN(x)              (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCTLR_AT3_PAD_EN_SHIFT)) & SNVS_LPATCTLR_AT3_PAD_EN_MASK)

#define SNVS_LPATCTLR_AT4_PAD_EN_MASK            (0x80000U)
#define SNVS_LPATCTLR_AT4_PAD_EN_SHIFT           (19U)
/*! AT4_PAD_EN
 *  0b0..Active Tamper 4 is disabled.
 *  0b1..Active Tamper 4 is enabled.
 */
#define SNVS_LPATCTLR_AT4_PAD_EN(x)              (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCTLR_AT4_PAD_EN_SHIFT)) & SNVS_LPATCTLR_AT4_PAD_EN_MASK)

#define SNVS_LPATCTLR_AT5_PAD_EN_MASK            (0x100000U)
#define SNVS_LPATCTLR_AT5_PAD_EN_SHIFT           (20U)
/*! AT5_PAD_EN
 *  0b0..Active Tamper 5 is disabled.
 *  0b1..Active Tamper 5 is enabled.
 */
#define SNVS_LPATCTLR_AT5_PAD_EN(x)              (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCTLR_AT5_PAD_EN_SHIFT)) & SNVS_LPATCTLR_AT5_PAD_EN_MASK)
/*! @} */

/*! @name LPATCLKR - SNVS_LP Active Tamper Clock Control Register */
/*! @{ */

#define SNVS_LPATCLKR_AT1_CLK_CTL_MASK           (0x3U)
#define SNVS_LPATCLKR_AT1_CLK_CTL_SHIFT          (0U)
#define SNVS_LPATCLKR_AT1_CLK_CTL(x)             (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCLKR_AT1_CLK_CTL_SHIFT)) & SNVS_LPATCLKR_AT1_CLK_CTL_MASK)

#define SNVS_LPATCLKR_AT2_CLK_CTL_MASK           (0x30U)
#define SNVS_LPATCLKR_AT2_CLK_CTL_SHIFT          (4U)
#define SNVS_LPATCLKR_AT2_CLK_CTL(x)             (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCLKR_AT2_CLK_CTL_SHIFT)) & SNVS_LPATCLKR_AT2_CLK_CTL_MASK)

#define SNVS_LPATCLKR_AT3_CLK_CTL_MASK           (0x300U)
#define SNVS_LPATCLKR_AT3_CLK_CTL_SHIFT          (8U)
#define SNVS_LPATCLKR_AT3_CLK_CTL(x)             (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCLKR_AT3_CLK_CTL_SHIFT)) & SNVS_LPATCLKR_AT3_CLK_CTL_MASK)

#define SNVS_LPATCLKR_AT4_CLK_CTL_MASK           (0x3000U)
#define SNVS_LPATCLKR_AT4_CLK_CTL_SHIFT          (12U)
#define SNVS_LPATCLKR_AT4_CLK_CTL(x)             (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCLKR_AT4_CLK_CTL_SHIFT)) & SNVS_LPATCLKR_AT4_CLK_CTL_MASK)

#define SNVS_LPATCLKR_AT5_CLK_CTL_MASK           (0x30000U)
#define SNVS_LPATCLKR_AT5_CLK_CTL_SHIFT          (16U)
#define SNVS_LPATCLKR_AT5_CLK_CTL(x)             (((uint32_t)(((uint32_t)(x)) << SNVS_LPATCLKR_AT5_CLK_CTL_SHIFT)) & SNVS_LPATCLKR_AT5_CLK_CTL_MASK)
/*! @} */

/*! @name LPATRC1R - SNVS_LP Active Tamper Routing Control 1 Register */
/*! @{ */

#define SNVS_LPATRC1R_ET1RCTL_MASK               (0x7U)
#define SNVS_LPATRC1R_ET1RCTL_SHIFT              (0U)
#define SNVS_LPATRC1R_ET1RCTL(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPATRC1R_ET1RCTL_SHIFT)) & SNVS_LPATRC1R_ET1RCTL_MASK)

#define SNVS_LPATRC1R_ET2RCTL_MASK               (0x70U)
#define SNVS_LPATRC1R_ET2RCTL_SHIFT              (4U)
#define SNVS_LPATRC1R_ET2RCTL(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPATRC1R_ET2RCTL_SHIFT)) & SNVS_LPATRC1R_ET2RCTL_MASK)

#define SNVS_LPATRC1R_ET3RCTL_MASK               (0x700U)
#define SNVS_LPATRC1R_ET3RCTL_SHIFT              (8U)
#define SNVS_LPATRC1R_ET3RCTL(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPATRC1R_ET3RCTL_SHIFT)) & SNVS_LPATRC1R_ET3RCTL_MASK)

#define SNVS_LPATRC1R_ET4RCTL_MASK               (0x7000U)
#define SNVS_LPATRC1R_ET4RCTL_SHIFT              (12U)
#define SNVS_LPATRC1R_ET4RCTL(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPATRC1R_ET4RCTL_SHIFT)) & SNVS_LPATRC1R_ET4RCTL_MASK)

#define SNVS_LPATRC1R_ET5RCTL_MASK               (0x70000U)
#define SNVS_LPATRC1R_ET5RCTL_SHIFT              (16U)
#define SNVS_LPATRC1R_ET5RCTL(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPATRC1R_ET5RCTL_SHIFT)) & SNVS_LPATRC1R_ET5RCTL_MASK)

#define SNVS_LPATRC1R_ET6RCTL_MASK               (0x700000U)
#define SNVS_LPATRC1R_ET6RCTL_SHIFT              (20U)
#define SNVS_LPATRC1R_ET6RCTL(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPATRC1R_ET6RCTL_SHIFT)) & SNVS_LPATRC1R_ET6RCTL_MASK)

#define SNVS_LPATRC1R_ET7RCTL_MASK               (0x7000000U)
#define SNVS_LPATRC1R_ET7RCTL_SHIFT              (24U)
#define SNVS_LPATRC1R_ET7RCTL(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPATRC1R_ET7RCTL_SHIFT)) & SNVS_LPATRC1R_ET7RCTL_MASK)

#define SNVS_LPATRC1R_ET8RCTL_MASK               (0x70000000U)
#define SNVS_LPATRC1R_ET8RCTL_SHIFT              (28U)
#define SNVS_LPATRC1R_ET8RCTL(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPATRC1R_ET8RCTL_SHIFT)) & SNVS_LPATRC1R_ET8RCTL_MASK)
/*! @} */

/*! @name LPATRC2R - SNVS_LP Active Tamper Routing Control 2 Register */
/*! @{ */

#define SNVS_LPATRC2R_ET9RCTL_MASK               (0x7U)
#define SNVS_LPATRC2R_ET9RCTL_SHIFT              (0U)
#define SNVS_LPATRC2R_ET9RCTL(x)                 (((uint32_t)(((uint32_t)(x)) << SNVS_LPATRC2R_ET9RCTL_SHIFT)) & SNVS_LPATRC2R_ET9RCTL_MASK)

#define SNVS_LPATRC2R_ET10RCTL_MASK              (0x70U)
#define SNVS_LPATRC2R_ET10RCTL_SHIFT             (4U)
#define SNVS_LPATRC2R_ET10RCTL(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_LPATRC2R_ET10RCTL_SHIFT)) & SNVS_LPATRC2R_ET10RCTL_MASK)
/*! @} */

/*! @name LPGPR - SNVS_LP General Purpose Registers 0 .. 3 */
/*! @{ */

#define SNVS_LPGPR_GPR_MASK                      (0xFFFFFFFFU)
#define SNVS_LPGPR_GPR_SHIFT                     (0U)
#define SNVS_LPGPR_GPR(x)                        (((uint32_t)(((uint32_t)(x)) << SNVS_LPGPR_GPR_SHIFT)) & SNVS_LPGPR_GPR_MASK)
/*! @} */

/* The count of SNVS_LPGPR */
#define SNVS_LPGPR_COUNT                         (4U)

/*! @name HPVIDR1 - SNVS_HP Version ID Register 1 */
/*! @{ */

#define SNVS_HPVIDR1_MINOR_REV_MASK              (0xFFU)
#define SNVS_HPVIDR1_MINOR_REV_SHIFT             (0U)
#define SNVS_HPVIDR1_MINOR_REV(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_HPVIDR1_MINOR_REV_SHIFT)) & SNVS_HPVIDR1_MINOR_REV_MASK)

#define SNVS_HPVIDR1_MAJOR_REV_MASK              (0xFF00U)
#define SNVS_HPVIDR1_MAJOR_REV_SHIFT             (8U)
#define SNVS_HPVIDR1_MAJOR_REV(x)                (((uint32_t)(((uint32_t)(x)) << SNVS_HPVIDR1_MAJOR_REV_SHIFT)) & SNVS_HPVIDR1_MAJOR_REV_MASK)

#define SNVS_HPVIDR1_IP_ID_MASK                  (0xFFFF0000U)
#define SNVS_HPVIDR1_IP_ID_SHIFT                 (16U)
#define SNVS_HPVIDR1_IP_ID(x)                    (((uint32_t)(((uint32_t)(x)) << SNVS_HPVIDR1_IP_ID_SHIFT)) & SNVS_HPVIDR1_IP_ID_MASK)
/*! @} */

/*! @name HPVIDR2 - SNVS_HP Version ID Register 2 */
/*! @{ */

#define SNVS_HPVIDR2_ECO_REV_MASK                (0xFF00U)
#define SNVS_HPVIDR2_ECO_REV_SHIFT               (8U)
#define SNVS_HPVIDR2_ECO_REV(x)                  (((uint32_t)(((uint32_t)(x)) << SNVS_HPVIDR2_ECO_REV_SHIFT)) & SNVS_HPVIDR2_ECO_REV_MASK)

#define SNVS_HPVIDR2_IP_ERA_MASK                 (0xFF000000U)
#define SNVS_HPVIDR2_IP_ERA_SHIFT                (24U)
#define SNVS_HPVIDR2_IP_ERA(x)                   (((uint32_t)(((uint32_t)(x)) << SNVS_HPVIDR2_IP_ERA_SHIFT)) & SNVS_HPVIDR2_IP_ERA_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SNVS_Register_Masks */


/*!
 * @}
 */ /* end of group SNVS_Peripheral_Access_Layer */


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


#endif  /* PERI_SNVS_H_ */

