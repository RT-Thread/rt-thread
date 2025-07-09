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
**         CMSIS Peripheral Access Layer for IOMUXC_SNVS_GPR
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
 * @file PERI_IOMUXC_SNVS_GPR.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for IOMUXC_SNVS_GPR
 *
 * CMSIS Peripheral Access Layer for IOMUXC_SNVS_GPR
 */

#if !defined(PERI_IOMUXC_SNVS_GPR_H_)
#define PERI_IOMUXC_SNVS_GPR_H_                  /**< Symbol preventing repeated inclusion */

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
   -- IOMUXC_SNVS_GPR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_SNVS_GPR_Peripheral_Access_Layer IOMUXC_SNVS_GPR Peripheral Access Layer
 * @{
 */

/** IOMUXC_SNVS_GPR - Size of Registers Arrays */
#define IOMUXC_SNVS_GPR_GPR_COUNT                 32u

/** IOMUXC_SNVS_GPR - Register Layout Typedef */
typedef struct {
  __IO uint32_t GPR[IOMUXC_SNVS_GPR_GPR_COUNT];    /**< GPR0 General Purpose Register, array offset: 0x0, array step: 0x4 */
  __IO uint32_t GPR32;                             /**< GPR32 General Purpose Register, offset: 0x80 */
  __IO uint32_t GPR33;                             /**< GPR33 General Purpose Register, offset: 0x84 */
  __IO uint32_t GPR34;                             /**< GPR34 General Purpose Register, offset: 0x88 */
  __IO uint32_t GPR35;                             /**< GPR35 General Purpose Register, offset: 0x8C */
  __IO uint32_t GPR36;                             /**< GPR36 General Purpose Register, offset: 0x90 */
  __IO uint32_t GPR37;                             /**< GPR37 General Purpose Register, offset: 0x94 */
} IOMUXC_SNVS_GPR_Type;

/* ----------------------------------------------------------------------------
   -- IOMUXC_SNVS_GPR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_SNVS_GPR_Register_Masks IOMUXC_SNVS_GPR Register Masks
 * @{
 */

/*! @name GPR - GPR0 General Purpose Register */
/*! @{ */

#define IOMUXC_SNVS_GPR_GPR_GPR_MASK             (0xFFFFFFFFU)
#define IOMUXC_SNVS_GPR_GPR_GPR_SHIFT            (0U)
/*! GPR - General purpose bits */
#define IOMUXC_SNVS_GPR_GPR_GPR(x)               (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR_GPR_SHIFT)) & IOMUXC_SNVS_GPR_GPR_GPR_MASK)
/*! @} */

/*! @name GPR32 - GPR32 General Purpose Register */
/*! @{ */

#define IOMUXC_SNVS_GPR_GPR32_GPR_MASK           (0xFFFEU)
#define IOMUXC_SNVS_GPR_GPR32_GPR_SHIFT          (1U)
/*! GPR - General purpose bits */
#define IOMUXC_SNVS_GPR_GPR32_GPR(x)             (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR32_GPR_SHIFT)) & IOMUXC_SNVS_GPR_GPR32_GPR_MASK)

#define IOMUXC_SNVS_GPR_GPR32_LOCK_MASK          (0xFFFF0000U)
#define IOMUXC_SNVS_GPR_GPR32_LOCK_SHIFT         (16U)
/*! LOCK - Lock the write to bit 15:0 */
#define IOMUXC_SNVS_GPR_GPR32_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR32_LOCK_SHIFT)) & IOMUXC_SNVS_GPR_GPR32_LOCK_MASK)
/*! @} */

/*! @name GPR33 - GPR33 General Purpose Register */
/*! @{ */

#define IOMUXC_SNVS_GPR_GPR33_DCDC_STATUS_CAPT_CLR_MASK (0x2U)
#define IOMUXC_SNVS_GPR_GPR33_DCDC_STATUS_CAPT_CLR_SHIFT (1U)
/*! DCDC_STATUS_CAPT_CLR - DCDC captured status clear
 *  0b0..No change
 *  0b1..Clear the 3 bits of DCDC captured status: DCDC_OVER_VOL, DCDC_OVER_CUR, and DCDC_IN_LOW_VOL
 */
#define IOMUXC_SNVS_GPR_GPR33_DCDC_STATUS_CAPT_CLR(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR33_DCDC_STATUS_CAPT_CLR_SHIFT)) & IOMUXC_SNVS_GPR_GPR33_DCDC_STATUS_CAPT_CLR_MASK)

#define IOMUXC_SNVS_GPR_GPR33_SNVS_BYPASS_EN_MASK (0x4U)
#define IOMUXC_SNVS_GPR_GPR33_SNVS_BYPASS_EN_SHIFT (2U)
/*! SNVS_BYPASS_EN - SNVS LDO_SNVS_ANA bypass enable
 *  0b0..Disable bypass
 *  0b1..Enable bypass
 */
#define IOMUXC_SNVS_GPR_GPR33_SNVS_BYPASS_EN(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR33_SNVS_BYPASS_EN_SHIFT)) & IOMUXC_SNVS_GPR_GPR33_SNVS_BYPASS_EN_MASK)

#define IOMUXC_SNVS_GPR_GPR33_DCDC_IN_LOW_VOL_MASK (0x10000U)
#define IOMUXC_SNVS_GPR_GPR33_DCDC_IN_LOW_VOL_SHIFT (16U)
/*! DCDC_IN_LOW_VOL - DCDC_IN low voltage detect
 *  0b0..Voltage on DCDC_IN is higher than 2.6V
 *  0b1..Voltage on DCDC_IN is lower than 2.6V
 */
#define IOMUXC_SNVS_GPR_GPR33_DCDC_IN_LOW_VOL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR33_DCDC_IN_LOW_VOL_SHIFT)) & IOMUXC_SNVS_GPR_GPR33_DCDC_IN_LOW_VOL_MASK)

#define IOMUXC_SNVS_GPR_GPR33_DCDC_OVER_CUR_MASK (0x20000U)
#define IOMUXC_SNVS_GPR_GPR33_DCDC_OVER_CUR_SHIFT (17U)
/*! DCDC_OVER_CUR - DCDC output over current alert
 *  0b0..No Overcurrent on DCDC output
 *  0b1..Overcurrent on DCDC output
 */
#define IOMUXC_SNVS_GPR_GPR33_DCDC_OVER_CUR(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR33_DCDC_OVER_CUR_SHIFT)) & IOMUXC_SNVS_GPR_GPR33_DCDC_OVER_CUR_MASK)

#define IOMUXC_SNVS_GPR_GPR33_DCDC_OVER_VOL_MASK (0x40000U)
#define IOMUXC_SNVS_GPR_GPR33_DCDC_OVER_VOL_SHIFT (18U)
/*! DCDC_OVER_VOL - DCDC output over voltage alert
 *  0b0..No Overvoltage on DCDC VDDLP0 or VDDLP8 output
 *  0b1..Overvoltage on DCDC VDDLP0 or VDDLP8 output
 */
#define IOMUXC_SNVS_GPR_GPR33_DCDC_OVER_VOL(x)   (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR33_DCDC_OVER_VOL_SHIFT)) & IOMUXC_SNVS_GPR_GPR33_DCDC_OVER_VOL_MASK)

#define IOMUXC_SNVS_GPR_GPR33_DCDC_STS_DC_OK_MASK (0x80000U)
#define IOMUXC_SNVS_GPR_GPR33_DCDC_STS_DC_OK_SHIFT (19U)
/*! DCDC_STS_DC_OK - DCDC status OK
 *  0b0..DCDC is settling
 *  0b1..DCDC already settled
 */
#define IOMUXC_SNVS_GPR_GPR33_DCDC_STS_DC_OK(x)  (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR33_DCDC_STS_DC_OK_SHIFT)) & IOMUXC_SNVS_GPR_GPR33_DCDC_STS_DC_OK_MASK)

#define IOMUXC_SNVS_GPR_GPR33_SNVS_XTAL_CLK_OK_MASK (0x100000U)
#define IOMUXC_SNVS_GPR_GPR33_SNVS_XTAL_CLK_OK_SHIFT (20U)
/*! SNVS_XTAL_CLK_OK - 32K OSC ok flag
 *  0b0..32K oscillator is NOT stable into normal operation
 *  0b1..32K oscillator is stable into normal operation
 */
#define IOMUXC_SNVS_GPR_GPR33_SNVS_XTAL_CLK_OK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR33_SNVS_XTAL_CLK_OK_SHIFT)) & IOMUXC_SNVS_GPR_GPR33_SNVS_XTAL_CLK_OK_MASK)
/*! @} */

/*! @name GPR34 - GPR34 General Purpose Register */
/*! @{ */

#define IOMUXC_SNVS_GPR_GPR34_LOCK_MASK          (0x1U)
#define IOMUXC_SNVS_GPR_GPR34_LOCK_SHIFT         (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access is not blocked
 *  0b1..Write access is blocked
 */
#define IOMUXC_SNVS_GPR_GPR34_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR34_LOCK_SHIFT)) & IOMUXC_SNVS_GPR_GPR34_LOCK_MASK)

#define IOMUXC_SNVS_GPR_GPR34_SNVS_CORE_VOLT_DET_TRIM_SEL_MASK (0x2U)
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CORE_VOLT_DET_TRIM_SEL_SHIFT (1U)
/*! SNVS_CORE_VOLT_DET_TRIM_SEL - SNVS core voltage detect trim select
 *  0b0..The trimming codes are selected from eFuse
 *  0b1..The trimming codes of core voltage detectors used to change the voltage falling trip point are selected from SNVS_CORE_VOLT_DET_TRIM
 */
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CORE_VOLT_DET_TRIM_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR34_SNVS_CORE_VOLT_DET_TRIM_SEL_SHIFT)) & IOMUXC_SNVS_GPR_GPR34_SNVS_CORE_VOLT_DET_TRIM_SEL_MASK)

#define IOMUXC_SNVS_GPR_GPR34_SNVS_CORE_VOLT_DET_TRIM_MASK (0xCU)
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CORE_VOLT_DET_TRIM_SHIFT (2U)
/*! SNVS_CORE_VOLT_DET_TRIM - SNVS core voltage detect trim */
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CORE_VOLT_DET_TRIM(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR34_SNVS_CORE_VOLT_DET_TRIM_SHIFT)) & IOMUXC_SNVS_GPR_GPR34_SNVS_CORE_VOLT_DET_TRIM_MASK)

#define IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_TRIM_SEL_MASK (0x80U)
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_TRIM_SEL_SHIFT (7U)
/*! SNVS_CLK_DET_TRIM_SEL - SNVS clock detect trim select
 *  0b0..The trimming codes are selected from eFuse
 *  0b1..The trimming codes of clock detector used to change the boundary frequencies are selected from SNVS_CLK_DET_TRIM
 */
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_TRIM_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_TRIM_SEL_SHIFT)) & IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_TRIM_SEL_MASK)

#define IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_TRIM_MASK (0xFF00U)
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_TRIM_SHIFT (8U)
/*! SNVS_CLK_DET_TRIM - SNVS clock detect trim bits */
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_TRIM(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_TRIM_SHIFT)) & IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_TRIM_MASK)

#define IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_OFFSET_HIGH_MASK (0x30000U)
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_OFFSET_HIGH_SHIFT (16U)
/*! SNVS_CLK_DET_OFFSET_HIGH - SNVS clock detect offset of high boundary frequency
 *  0b00..No change (Default)
 *  0b01..Add +5 to the Trim
 *  0b10..Add +10 to the trim
 *  0b11..Add -5 to the Trim
 */
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_OFFSET_HIGH(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_OFFSET_HIGH_SHIFT)) & IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_OFFSET_HIGH_MASK)

#define IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_OFFSET_LOW_MASK (0xC0000U)
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_OFFSET_LOW_SHIFT (18U)
/*! SNVS_CLK_DET_OFFSET_LOW - SNVS clock detect offset of low boundary frequency
 *  0b00..No change (Default)
 *  0b01..Add +5 to the Trim
 *  0b10..Add +10 to the trim
 *  0b11..Add -5 to the Trim
 */
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_OFFSET_LOW(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_OFFSET_LOW_SHIFT)) & IOMUXC_SNVS_GPR_GPR34_SNVS_CLK_DET_OFFSET_LOW_MASK)

#define IOMUXC_SNVS_GPR_GPR34_SNVS_CAP_TRIM_SEL_MASK (0x800000U)
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CAP_TRIM_SEL_SHIFT (23U)
/*! SNVS_CAP_TRIM_SEL - SNVS OSC load capacitor trim select
 *  0b0..The trimming codes are selected from eFuse
 *  0b1..The trimming codes are used from SNVS_OSC_CAP_TRIM (osc32k's load capacitor)
 */
#define IOMUXC_SNVS_GPR_GPR34_SNVS_CAP_TRIM_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR34_SNVS_CAP_TRIM_SEL_SHIFT)) & IOMUXC_SNVS_GPR_GPR34_SNVS_CAP_TRIM_SEL_MASK)

#define IOMUXC_SNVS_GPR_GPR34_SNVS_OSC_CAP_TRIM_MASK (0xF000000U)
#define IOMUXC_SNVS_GPR_GPR34_SNVS_OSC_CAP_TRIM_SHIFT (24U)
/*! SNVS_OSC_CAP_TRIM - SNVS OSC load capacitor trim */
#define IOMUXC_SNVS_GPR_GPR34_SNVS_OSC_CAP_TRIM(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR34_SNVS_OSC_CAP_TRIM_SHIFT)) & IOMUXC_SNVS_GPR_GPR34_SNVS_OSC_CAP_TRIM_MASK)
/*! @} */

/*! @name GPR35 - GPR35 General Purpose Register */
/*! @{ */

#define IOMUXC_SNVS_GPR_GPR35_LOCK_MASK          (0x1U)
#define IOMUXC_SNVS_GPR_GPR35_LOCK_SHIFT         (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access is not blocked
 *  0b1..Write access is blocked
 */
#define IOMUXC_SNVS_GPR_GPR35_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR35_LOCK_SHIFT)) & IOMUXC_SNVS_GPR_GPR35_LOCK_MASK)

#define IOMUXC_SNVS_GPR_GPR35_SNVS_VOLT_DET_TRIM_SEL_MASK (0x8U)
#define IOMUXC_SNVS_GPR_GPR35_SNVS_VOLT_DET_TRIM_SEL_SHIFT (3U)
/*! SNVS_VOLT_DET_TRIM_SEL - SNVS voltage detect trim select
 *  0b0..The trimming codes are selected from eFuse
 *  0b1..The trimming codes of voltage detectors to change the voltage boundaries in battery voltage detecting are selected from SNVS_VOLT_DET_TRIM
 */
#define IOMUXC_SNVS_GPR_GPR35_SNVS_VOLT_DET_TRIM_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR35_SNVS_VOLT_DET_TRIM_SEL_SHIFT)) & IOMUXC_SNVS_GPR_GPR35_SNVS_VOLT_DET_TRIM_SEL_MASK)

#define IOMUXC_SNVS_GPR_GPR35_SNVS_VOLT_DET_TRIM_MASK (0xFF0U)
#define IOMUXC_SNVS_GPR_GPR35_SNVS_VOLT_DET_TRIM_SHIFT (4U)
/*! SNVS_VOLT_DET_TRIM - SNVS voltage detect trim */
#define IOMUXC_SNVS_GPR_GPR35_SNVS_VOLT_DET_TRIM(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR35_SNVS_VOLT_DET_TRIM_SHIFT)) & IOMUXC_SNVS_GPR_GPR35_SNVS_VOLT_DET_TRIM_MASK)

#define IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_TRIM_SEL_MASK (0x8000U)
#define IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_TRIM_SEL_SHIFT (15U)
/*! SNVS_TEMP_DET_TRIM_SEL - SNVS temperature detect trim select
 *  0b0..The trimming codes are selected from eFuse
 *  0b1..The trimming codes to define the temperature boundaries of temperature detector are selected from SNVS_TEMP_DET_TRIM
 */
#define IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_TRIM_SEL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_TRIM_SEL_SHIFT)) & IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_TRIM_SEL_MASK)

#define IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_TRIM_MASK (0xFFF0000U)
#define IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_TRIM_SHIFT (16U)
/*! SNVS_TEMP_DET_TRIM - SNVS temperature detect trim */
#define IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_TRIM(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_TRIM_SHIFT)) & IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_TRIM_MASK)

#define IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_OFFSET_HIGH_MASK (0x30000000U)
#define IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_OFFSET_HIGH_SHIFT (28U)
/*! SNVS_TEMP_DET_OFFSET_HIGH - SNVS temperature detect offset of high temperature boundary
 *  0b00..No change (Default)
 *  0b01..Add +5 to the Trim
 *  0b10..Add +10 to the trim
 *  0b11..Add -5 to the Trim
 */
#define IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_OFFSET_HIGH(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_OFFSET_HIGH_SHIFT)) & IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_OFFSET_HIGH_MASK)

#define IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_OFFSET_LOW_MASK (0xC0000000U)
#define IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_OFFSET_LOW_SHIFT (30U)
/*! SNVS_TEMP_DET_OFFSET_LOW - SNVS temperature detect offset of low temperature boundary
 *  0b00..No change (Default)
 *  0b01..Add +5 to the Trim
 *  0b10..Add +10 to the trim
 *  0b11..Add -5 to the Trim
 */
#define IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_OFFSET_LOW(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_OFFSET_LOW_SHIFT)) & IOMUXC_SNVS_GPR_GPR35_SNVS_TEMP_DET_OFFSET_LOW_MASK)
/*! @} */

/*! @name GPR36 - GPR36 General Purpose Register */
/*! @{ */

#define IOMUXC_SNVS_GPR_GPR36_SNVSDIG_SNVS1P8_ISO_EN_MASK (0x800000U)
#define IOMUXC_SNVS_GPR_GPR36_SNVSDIG_SNVS1P8_ISO_EN_SHIFT (23U)
/*! SNVSDIG_SNVS1P8_ISO_EN - SNVS RAM isolation enable bit
 *  0b0..Enable SRAM access (It should be cleared after LDO_SNVS_DIG and SNVS SRAM peripheral power is back)
 *  0b1..Enable the isolation to avoid extra leakage power before SNVS SRAM peripheral power or LDO_SNVS_DIG is switched off
 */
#define IOMUXC_SNVS_GPR_GPR36_SNVSDIG_SNVS1P8_ISO_EN(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR36_SNVSDIG_SNVS1P8_ISO_EN_SHIFT)) & IOMUXC_SNVS_GPR_GPR36_SNVSDIG_SNVS1P8_ISO_EN_MASK)

#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_SLEEP_MASK (0x4000000U)
#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_SLEEP_SHIFT (26U)
/*! SNVS_SRAM_SLEEP - SNVS SRAM power-down enable bit
 *  0b0..Enable SRAM access (It should be cleared after LDO_SNVS_DIG is enabled)
 *  0b1..SNVS SRAM can go in Shutdown/ Periphery Off Array On/ Periphery On Array Off mode. In addition, this bit
 *       ensures power-up without stuck-at /high DC current states and hence must be held to 1 during wake-up, so
 *       this bit is default high.
 */
#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_SLEEP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_SLEEP_SHIFT)) & IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_SLEEP_MASK)

#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_STDBY_MASK (0x8000000U)
#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_STDBY_SHIFT (27U)
/*! SNVS_SRAM_STDBY - SNVS SRAM standby enable bit
 *  0b0..SNVS SRAM does not enter low leakage state
 *  0b1..SNVS SRAM enters low leakage state and large drivers are switched OFF
 */
#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_STDBY(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_STDBY_SHIFT)) & IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_STDBY_MASK)

#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWLARGEMP_FORCE_MASK (0x10000000U)
#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWLARGEMP_FORCE_SHIFT (28U)
/*! SNVS_SRAM_PSWLARGEMP_FORCE - SNVS SRAM large switch control bit for peripheral
 *  0b0..Switch on SNVS SRAM power for peripheral
 *  0b1..Switch off SNVS SRAM power for peripheral (SRAM array power is not impacted, and data can be retained)
 */
#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWLARGEMP_FORCE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWLARGEMP_FORCE_SHIFT)) & IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWLARGEMP_FORCE_MASK)

#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWLARGE_MASK (0x20000000U)
#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWLARGE_SHIFT (29U)
/*! SNVS_SRAM_PSWLARGE - SNVS SRAM large switch control bit
 *  0b0..Switch on SNVS SRAM power for peripheral and array
 *  0b1..Switch off SNVS SRAM power for peripheral and array
 */
#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWLARGE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWLARGE_SHIFT)) & IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWLARGE_MASK)

#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWSMALLMP_FORCE_MASK (0x40000000U)
#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWSMALLMP_FORCE_SHIFT (30U)
/*! SNVS_SRAM_PSWSMALLMP_FORCE - SNVS SRAM small switch control bit for peripheral
 *  0b0..Switch on SNVS SRAM power for peripheral
 *  0b1..Switch off SNVS SRAM power for peripheral (SRAM array power is not impacted, and data can be retained)
 */
#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWSMALLMP_FORCE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWSMALLMP_FORCE_SHIFT)) & IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWSMALLMP_FORCE_MASK)

#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWSMALL_MASK (0x80000000U)
#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWSMALL_SHIFT (31U)
/*! SNVS_SRAM_PSWSMALL - SNVS SRAM small switch control bit
 *  0b0..Switch on SNVS SRAM power for peripheral and array
 *  0b1..Switch off SNVS SRAM power for peripheral and array
 */
#define IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWSMALL(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWSMALL_SHIFT)) & IOMUXC_SNVS_GPR_GPR36_SNVS_SRAM_PSWSMALL_MASK)
/*! @} */

/*! @name GPR37 - GPR37 General Purpose Register */
/*! @{ */

#define IOMUXC_SNVS_GPR_GPR37_LOCK_MASK          (0x1U)
#define IOMUXC_SNVS_GPR_GPR37_LOCK_SHIFT         (0U)
/*! LOCK - Lock the write to bit 31:1
 *  0b0..Write access is not blocked
 *  0b1..Write access is blocked
 */
#define IOMUXC_SNVS_GPR_GPR37_LOCK(x)            (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR37_LOCK_SHIFT)) & IOMUXC_SNVS_GPR_GPR37_LOCK_MASK)

#define IOMUXC_SNVS_GPR_GPR37_SNVS_TAMPER_PUE_MASK (0x7FEU)
#define IOMUXC_SNVS_GPR_GPR37_SNVS_TAMPER_PUE_SHIFT (1U)
/*! SNVS_TAMPER_PUE - SNVS tamper detect pin pull enable bit */
#define IOMUXC_SNVS_GPR_GPR37_SNVS_TAMPER_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR37_SNVS_TAMPER_PUE_SHIFT)) & IOMUXC_SNVS_GPR_GPR37_SNVS_TAMPER_PUE_MASK)

#define IOMUXC_SNVS_GPR_GPR37_SNVS_TAMPER_PUS_MASK (0x1FF800U)
#define IOMUXC_SNVS_GPR_GPR37_SNVS_TAMPER_PUS_SHIFT (11U)
/*! SNVS_TAMPER_PUS - SNVS tamper detect pin pull selection bit */
#define IOMUXC_SNVS_GPR_GPR37_SNVS_TAMPER_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_GPR_GPR37_SNVS_TAMPER_PUS_SHIFT)) & IOMUXC_SNVS_GPR_GPR37_SNVS_TAMPER_PUS_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group IOMUXC_SNVS_GPR_Register_Masks */


/*!
 * @}
 */ /* end of group IOMUXC_SNVS_GPR_Peripheral_Access_Layer */


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


#endif  /* PERI_IOMUXC_SNVS_GPR_H_ */

