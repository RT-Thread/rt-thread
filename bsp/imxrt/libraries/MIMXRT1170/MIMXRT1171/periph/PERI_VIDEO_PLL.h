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
**         CMSIS Peripheral Access Layer for VIDEO_PLL
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
 * @file PERI_VIDEO_PLL.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for VIDEO_PLL
 *
 * CMSIS Peripheral Access Layer for VIDEO_PLL
 */

#if !defined(PERI_VIDEO_PLL_H_)
#define PERI_VIDEO_PLL_H_                        /**< Symbol preventing repeated inclusion */

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
   -- VIDEO_PLL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VIDEO_PLL_Peripheral_Access_Layer VIDEO_PLL Peripheral Access Layer
 * @{
 */

/** VIDEO_PLL - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0 */
    __IO uint32_t RW;                                /**< Fractional PLL Control Register, offset: 0x0 */
    __IO uint32_t SET;                               /**< Fractional PLL Control Register, offset: 0x4 */
    __IO uint32_t CLR;                               /**< Fractional PLL Control Register, offset: 0x8 */
    __IO uint32_t TOG;                               /**< Fractional PLL Control Register, offset: 0xC */
  } CTRL0;
  struct {                                         /* offset: 0x10 */
    __IO uint32_t RW;                                /**< Fractional PLL Spread Spectrum Control Register, offset: 0x10 */
    __IO uint32_t SET;                               /**< Fractional PLL Spread Spectrum Control Register, offset: 0x14 */
    __IO uint32_t CLR;                               /**< Fractional PLL Spread Spectrum Control Register, offset: 0x18 */
    __IO uint32_t TOG;                               /**< Fractional PLL Spread Spectrum Control Register, offset: 0x1C */
  } SPREAD_SPECTRUM;
  struct {                                         /* offset: 0x20 */
    __IO uint32_t RW;                                /**< Fractional PLL Numerator Control Register, offset: 0x20 */
    __IO uint32_t SET;                               /**< Fractional PLL Numerator Control Register, offset: 0x24 */
    __IO uint32_t CLR;                               /**< Fractional PLL Numerator Control Register, offset: 0x28 */
    __IO uint32_t TOG;                               /**< Fractional PLL Numerator Control Register, offset: 0x2C */
  } NUMERATOR;
  struct {                                         /* offset: 0x30 */
    __IO uint32_t RW;                                /**< Fractional PLL Denominator Control Register, offset: 0x30 */
    __IO uint32_t SET;                               /**< Fractional PLL Denominator Control Register, offset: 0x34 */
    __IO uint32_t CLR;                               /**< Fractional PLL Denominator Control Register, offset: 0x38 */
    __IO uint32_t TOG;                               /**< Fractional PLL Denominator Control Register, offset: 0x3C */
  } DENOMINATOR;
} VIDEO_PLL_Type;

/* ----------------------------------------------------------------------------
   -- VIDEO_PLL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VIDEO_PLL_Register_Masks VIDEO_PLL Register Masks
 * @{
 */

/*! @name CTRL0 - Fractional PLL Control Register */
/*! @{ */

#define VIDEO_PLL_CTRL0_DIV_SELECT_MASK          (0x7FU)
#define VIDEO_PLL_CTRL0_DIV_SELECT_SHIFT         (0U)
/*! DIV_SELECT - DIV_SELECT */
#define VIDEO_PLL_CTRL0_DIV_SELECT(x)            (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_CTRL0_DIV_SELECT_SHIFT)) & VIDEO_PLL_CTRL0_DIV_SELECT_MASK)

#define VIDEO_PLL_CTRL0_ENABLE_ALT_MASK          (0x100U)
#define VIDEO_PLL_CTRL0_ENABLE_ALT_SHIFT         (8U)
/*! ENABLE_ALT - ENABLE_ALT
 *  0b0..Disable the alternate clock output
 *  0b1..Enable the alternate clock output which is the output of the post_divider, and cannot be bypassed
 */
#define VIDEO_PLL_CTRL0_ENABLE_ALT(x)            (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_CTRL0_ENABLE_ALT_SHIFT)) & VIDEO_PLL_CTRL0_ENABLE_ALT_MASK)

#define VIDEO_PLL_CTRL0_HOLD_RING_OFF_MASK       (0x2000U)
#define VIDEO_PLL_CTRL0_HOLD_RING_OFF_SHIFT      (13U)
/*! HOLD_RING_OFF - PLL Start up initialization
 *  0b0..Normal operation
 *  0b1..Initialize PLL start up
 */
#define VIDEO_PLL_CTRL0_HOLD_RING_OFF(x)         (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_CTRL0_HOLD_RING_OFF_SHIFT)) & VIDEO_PLL_CTRL0_HOLD_RING_OFF_MASK)

#define VIDEO_PLL_CTRL0_POWERUP_MASK             (0x4000U)
#define VIDEO_PLL_CTRL0_POWERUP_SHIFT            (14U)
/*! POWERUP - POWERUP
 *  0b0..Power down the PLL
 *  0b1..Power Up the PLL
 */
#define VIDEO_PLL_CTRL0_POWERUP(x)               (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_CTRL0_POWERUP_SHIFT)) & VIDEO_PLL_CTRL0_POWERUP_MASK)

#define VIDEO_PLL_CTRL0_ENABLE_MASK              (0x8000U)
#define VIDEO_PLL_CTRL0_ENABLE_SHIFT             (15U)
/*! ENABLE - ENABLE
 *  0b0..Disable the clock output
 *  0b1..Enable the clock output
 */
#define VIDEO_PLL_CTRL0_ENABLE(x)                (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_CTRL0_ENABLE_SHIFT)) & VIDEO_PLL_CTRL0_ENABLE_MASK)

#define VIDEO_PLL_CTRL0_BYPASS_MASK              (0x10000U)
#define VIDEO_PLL_CTRL0_BYPASS_SHIFT             (16U)
/*! BYPASS - BYPASS
 *  0b0..No Bypass
 *  0b1..Bypass the PLL
 */
#define VIDEO_PLL_CTRL0_BYPASS(x)                (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_CTRL0_BYPASS_SHIFT)) & VIDEO_PLL_CTRL0_BYPASS_MASK)

#define VIDEO_PLL_CTRL0_DITHER_EN_MASK           (0x20000U)
#define VIDEO_PLL_CTRL0_DITHER_EN_SHIFT          (17U)
/*! DITHER_EN - DITHER_EN
 *  0b0..Disable Dither
 *  0b1..Enable Dither
 */
#define VIDEO_PLL_CTRL0_DITHER_EN(x)             (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_CTRL0_DITHER_EN_SHIFT)) & VIDEO_PLL_CTRL0_DITHER_EN_MASK)

#define VIDEO_PLL_CTRL0_BIAS_TRIM_MASK           (0x380000U)
#define VIDEO_PLL_CTRL0_BIAS_TRIM_SHIFT          (19U)
/*! BIAS_TRIM - BIAS_TRIM */
#define VIDEO_PLL_CTRL0_BIAS_TRIM(x)             (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_CTRL0_BIAS_TRIM_SHIFT)) & VIDEO_PLL_CTRL0_BIAS_TRIM_MASK)

#define VIDEO_PLL_CTRL0_PLL_REG_EN_MASK          (0x400000U)
#define VIDEO_PLL_CTRL0_PLL_REG_EN_SHIFT         (22U)
/*! PLL_REG_EN - PLL_REG_EN */
#define VIDEO_PLL_CTRL0_PLL_REG_EN(x)            (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_CTRL0_PLL_REG_EN_SHIFT)) & VIDEO_PLL_CTRL0_PLL_REG_EN_MASK)

#define VIDEO_PLL_CTRL0_POST_DIV_SEL_MASK        (0xE000000U)
#define VIDEO_PLL_CTRL0_POST_DIV_SEL_SHIFT       (25U)
/*! POST_DIV_SEL - Post Divide Select
 *  0b000..Divide by 1
 *  0b001..Divide by 2
 *  0b010..Divide by 4
 *  0b011..Divide by 8
 *  0b100..Divide by 16
 *  0b101..Divide by 32
 */
#define VIDEO_PLL_CTRL0_POST_DIV_SEL(x)          (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_CTRL0_POST_DIV_SEL_SHIFT)) & VIDEO_PLL_CTRL0_POST_DIV_SEL_MASK)

#define VIDEO_PLL_CTRL0_BIAS_SELECT_MASK         (0x20000000U)
#define VIDEO_PLL_CTRL0_BIAS_SELECT_SHIFT        (29U)
/*! BIAS_SELECT - BIAS_SELECT
 *  0b0..Used in SoCs with a bias current of 10uA
 *  0b1..Used in SoCs with a bias current of 2uA
 */
#define VIDEO_PLL_CTRL0_BIAS_SELECT(x)           (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_CTRL0_BIAS_SELECT_SHIFT)) & VIDEO_PLL_CTRL0_BIAS_SELECT_MASK)
/*! @} */

/*! @name SPREAD_SPECTRUM - Fractional PLL Spread Spectrum Control Register */
/*! @{ */

#define VIDEO_PLL_SPREAD_SPECTRUM_STEP_MASK      (0x7FFFU)
#define VIDEO_PLL_SPREAD_SPECTRUM_STEP_SHIFT     (0U)
/*! STEP - Step */
#define VIDEO_PLL_SPREAD_SPECTRUM_STEP(x)        (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_SPREAD_SPECTRUM_STEP_SHIFT)) & VIDEO_PLL_SPREAD_SPECTRUM_STEP_MASK)

#define VIDEO_PLL_SPREAD_SPECTRUM_ENABLE_MASK    (0x8000U)
#define VIDEO_PLL_SPREAD_SPECTRUM_ENABLE_SHIFT   (15U)
/*! ENABLE - Enable */
#define VIDEO_PLL_SPREAD_SPECTRUM_ENABLE(x)      (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_SPREAD_SPECTRUM_ENABLE_SHIFT)) & VIDEO_PLL_SPREAD_SPECTRUM_ENABLE_MASK)

#define VIDEO_PLL_SPREAD_SPECTRUM_STOP_MASK      (0xFFFF0000U)
#define VIDEO_PLL_SPREAD_SPECTRUM_STOP_SHIFT     (16U)
/*! STOP - Stop */
#define VIDEO_PLL_SPREAD_SPECTRUM_STOP(x)        (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_SPREAD_SPECTRUM_STOP_SHIFT)) & VIDEO_PLL_SPREAD_SPECTRUM_STOP_MASK)
/*! @} */

/*! @name NUMERATOR - Fractional PLL Numerator Control Register */
/*! @{ */

#define VIDEO_PLL_NUMERATOR_NUM_MASK             (0x3FFFFFFFU)
#define VIDEO_PLL_NUMERATOR_NUM_SHIFT            (0U)
/*! NUM - Numerator */
#define VIDEO_PLL_NUMERATOR_NUM(x)               (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_NUMERATOR_NUM_SHIFT)) & VIDEO_PLL_NUMERATOR_NUM_MASK)
/*! @} */

/*! @name DENOMINATOR - Fractional PLL Denominator Control Register */
/*! @{ */

#define VIDEO_PLL_DENOMINATOR_DENOM_MASK         (0x3FFFFFFFU)
#define VIDEO_PLL_DENOMINATOR_DENOM_SHIFT        (0U)
/*! DENOM - Denominator */
#define VIDEO_PLL_DENOMINATOR_DENOM(x)           (((uint32_t)(((uint32_t)(x)) << VIDEO_PLL_DENOMINATOR_DENOM_SHIFT)) & VIDEO_PLL_DENOMINATOR_DENOM_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group VIDEO_PLL_Register_Masks */


/*!
 * @}
 */ /* end of group VIDEO_PLL_Peripheral_Access_Layer */


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


#endif  /* PERI_VIDEO_PLL_H_ */

