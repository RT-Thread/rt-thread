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
**         CMSIS Peripheral Access Layer for OSC_RC_400M
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
 * @file PERI_OSC_RC_400M.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for OSC_RC_400M
 *
 * CMSIS Peripheral Access Layer for OSC_RC_400M
 */

#if !defined(PERI_OSC_RC_400M_H_)
#define PERI_OSC_RC_400M_H_                      /**< Symbol preventing repeated inclusion */

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
   -- OSC_RC_400M Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_RC_400M_Peripheral_Access_Layer OSC_RC_400M Peripheral Access Layer
 * @{
 */

/** OSC_RC_400M - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0 */
    __IO uint32_t RW;                                /**< Control Register 0, offset: 0x0 */
    __IO uint32_t SET;                               /**< Control Register 0, offset: 0x4 */
    __IO uint32_t CLR;                               /**< Control Register 0, offset: 0x8 */
    __IO uint32_t TOG;                               /**< Control Register 0, offset: 0xC */
  } CTRL0;
  struct {                                         /* offset: 0x10 */
    __IO uint32_t RW;                                /**< Control Register 1, offset: 0x10 */
    __IO uint32_t SET;                               /**< Control Register 1, offset: 0x14 */
    __IO uint32_t CLR;                               /**< Control Register 1, offset: 0x18 */
    __IO uint32_t TOG;                               /**< Control Register 1, offset: 0x1C */
  } CTRL1;
  struct {                                         /* offset: 0x20 */
    __IO uint32_t RW;                                /**< Control Register 2, offset: 0x20 */
    __IO uint32_t SET;                               /**< Control Register 2, offset: 0x24 */
    __IO uint32_t CLR;                               /**< Control Register 2, offset: 0x28 */
    __IO uint32_t TOG;                               /**< Control Register 2, offset: 0x2C */
  } CTRL2;
  struct {                                         /* offset: 0x30 */
    __IO uint32_t RW;                                /**< Control Register 3, offset: 0x30 */
    __IO uint32_t SET;                               /**< Control Register 3, offset: 0x34 */
    __IO uint32_t CLR;                               /**< Control Register 3, offset: 0x38 */
    __IO uint32_t TOG;                               /**< Control Register 3, offset: 0x3C */
  } CTRL3;
       uint8_t RESERVED_0[16];
  struct {                                         /* offset: 0x50 */
    __I  uint32_t RW;                                /**< Status Register 0, offset: 0x50 */
    __I  uint32_t SET;                               /**< Status Register 0, offset: 0x54 */
    __I  uint32_t CLR;                               /**< Status Register 0, offset: 0x58 */
    __I  uint32_t TOG;                               /**< Status Register 0, offset: 0x5C */
  } STAT0;
  struct {                                         /* offset: 0x60 */
    __I  uint32_t RW;                                /**< Status Register 1, offset: 0x60 */
    __I  uint32_t SET;                               /**< Status Register 1, offset: 0x64 */
    __I  uint32_t CLR;                               /**< Status Register 1, offset: 0x68 */
    __I  uint32_t TOG;                               /**< Status Register 1, offset: 0x6C */
  } STAT1;
  struct {                                         /* offset: 0x70 */
    __I  uint32_t RW;                                /**< Status Register 2, offset: 0x70 */
    __I  uint32_t SET;                               /**< Status Register 2, offset: 0x74 */
    __I  uint32_t CLR;                               /**< Status Register 2, offset: 0x78 */
    __I  uint32_t TOG;                               /**< Status Register 2, offset: 0x7C */
  } STAT2;
} OSC_RC_400M_Type;

/* ----------------------------------------------------------------------------
   -- OSC_RC_400M Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_RC_400M_Register_Masks OSC_RC_400M Register Masks
 * @{
 */

/*! @name CTRL0 - Control Register 0 */
/*! @{ */

#define OSC_RC_400M_CTRL0_REF_CLK_DIV_MASK       (0x3F000000U)
#define OSC_RC_400M_CTRL0_REF_CLK_DIV_SHIFT      (24U)
/*! REF_CLK_DIV - Divide value for ref_clk to generate slow_clk (used inside this IP) */
#define OSC_RC_400M_CTRL0_REF_CLK_DIV(x)         (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_CTRL0_REF_CLK_DIV_SHIFT)) & OSC_RC_400M_CTRL0_REF_CLK_DIV_MASK)
/*! @} */

/*! @name CTRL1 - Control Register 1 */
/*! @{ */

#define OSC_RC_400M_CTRL1_HYST_MINUS_MASK        (0xFU)
#define OSC_RC_400M_CTRL1_HYST_MINUS_SHIFT       (0U)
/*! HYST_MINUS - Negative hysteresis value for the tuned clock */
#define OSC_RC_400M_CTRL1_HYST_MINUS(x)          (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_CTRL1_HYST_MINUS_SHIFT)) & OSC_RC_400M_CTRL1_HYST_MINUS_MASK)

#define OSC_RC_400M_CTRL1_HYST_PLUS_MASK         (0xF00U)
#define OSC_RC_400M_CTRL1_HYST_PLUS_SHIFT        (8U)
/*! HYST_PLUS - Positive hysteresis value for the tuned clock */
#define OSC_RC_400M_CTRL1_HYST_PLUS(x)           (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_CTRL1_HYST_PLUS_SHIFT)) & OSC_RC_400M_CTRL1_HYST_PLUS_MASK)

#define OSC_RC_400M_CTRL1_TARGET_COUNT_MASK      (0xFFFF0000U)
#define OSC_RC_400M_CTRL1_TARGET_COUNT_SHIFT     (16U)
/*! TARGET_COUNT - Target count for the fast clock */
#define OSC_RC_400M_CTRL1_TARGET_COUNT(x)        (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_CTRL1_TARGET_COUNT_SHIFT)) & OSC_RC_400M_CTRL1_TARGET_COUNT_MASK)
/*! @} */

/*! @name CTRL2 - Control Register 2 */
/*! @{ */

#define OSC_RC_400M_CTRL2_TUNE_BYP_MASK          (0x400U)
#define OSC_RC_400M_CTRL2_TUNE_BYP_SHIFT         (10U)
/*! TUNE_BYP - Bypass the tuning logic
 *  0b0..Use the output of tuning logic to run the oscillator
 *  0b1..Bypass the tuning logic and use the programmed OSC_TUNE_VAL to run the oscillator
 */
#define OSC_RC_400M_CTRL2_TUNE_BYP(x)            (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_CTRL2_TUNE_BYP_SHIFT)) & OSC_RC_400M_CTRL2_TUNE_BYP_MASK)

#define OSC_RC_400M_CTRL2_TUNE_EN_MASK           (0x1000U)
#define OSC_RC_400M_CTRL2_TUNE_EN_SHIFT          (12U)
/*! TUNE_EN - Freeze/Unfreeze the tuning value
 *  0b0..Freezes the tuning at the current tuned value. Oscillator runs at the frozen tuning value
 *  0b1..Unfreezes and continues the tuning operation
 */
#define OSC_RC_400M_CTRL2_TUNE_EN(x)             (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_CTRL2_TUNE_EN_SHIFT)) & OSC_RC_400M_CTRL2_TUNE_EN_MASK)

#define OSC_RC_400M_CTRL2_TUNE_START_MASK        (0x4000U)
#define OSC_RC_400M_CTRL2_TUNE_START_SHIFT       (14U)
/*! TUNE_START - Start/Stop tuning
 *  0b0..Stop tuning and reset the tuning logic. Oscillator runs using programmed OSC_TUNE_VAL
 *  0b1..Start tuning
 */
#define OSC_RC_400M_CTRL2_TUNE_START(x)          (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_CTRL2_TUNE_START_SHIFT)) & OSC_RC_400M_CTRL2_TUNE_START_MASK)

#define OSC_RC_400M_CTRL2_OSC_TUNE_VAL_MASK      (0xFF000000U)
#define OSC_RC_400M_CTRL2_OSC_TUNE_VAL_SHIFT     (24U)
/*! OSC_TUNE_VAL - Program the oscillator frequency */
#define OSC_RC_400M_CTRL2_OSC_TUNE_VAL(x)        (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_CTRL2_OSC_TUNE_VAL_SHIFT)) & OSC_RC_400M_CTRL2_OSC_TUNE_VAL_MASK)
/*! @} */

/*! @name CTRL3 - Control Register 3 */
/*! @{ */

#define OSC_RC_400M_CTRL3_CLR_ERR_MASK           (0x1U)
#define OSC_RC_400M_CTRL3_CLR_ERR_SHIFT          (0U)
/*! CLR_ERR - Clear the error flag CLK1M_ERR
 *  0b0..No effect
 *  0b1..Clears the error flag CLK1M_ERR in status register STAT0
 */
#define OSC_RC_400M_CTRL3_CLR_ERR(x)             (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_CTRL3_CLR_ERR_SHIFT)) & OSC_RC_400M_CTRL3_CLR_ERR_MASK)

#define OSC_RC_400M_CTRL3_EN_1M_CLK_MASK         (0x100U)
#define OSC_RC_400M_CTRL3_EN_1M_CLK_SHIFT        (8U)
/*! EN_1M_CLK - Enable 1MHz output Clock
 *  0b0..Enable the output (clk_1m_out)
 *  0b1..Disable the output (clk_1m_out)
 */
#define OSC_RC_400M_CTRL3_EN_1M_CLK(x)           (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_CTRL3_EN_1M_CLK_SHIFT)) & OSC_RC_400M_CTRL3_EN_1M_CLK_MASK)

#define OSC_RC_400M_CTRL3_MUX_1M_CLK_MASK        (0x400U)
#define OSC_RC_400M_CTRL3_MUX_1M_CLK_SHIFT       (10U)
/*! MUX_1M_CLK - Select free/locked 1MHz output
 *  0b0..Select free-running 1MHz to be put out on clk_1m_out
 *  0b1..Select locked 1MHz to be put out on clk_1m_out
 */
#define OSC_RC_400M_CTRL3_MUX_1M_CLK(x)          (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_CTRL3_MUX_1M_CLK_SHIFT)) & OSC_RC_400M_CTRL3_MUX_1M_CLK_MASK)

#define OSC_RC_400M_CTRL3_COUNT_1M_CLK_MASK      (0xFFFF0000U)
#define OSC_RC_400M_CTRL3_COUNT_1M_CLK_SHIFT     (16U)
/*! COUNT_1M_CLK - Count for the locked clk_1m_out */
#define OSC_RC_400M_CTRL3_COUNT_1M_CLK(x)        (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_CTRL3_COUNT_1M_CLK_SHIFT)) & OSC_RC_400M_CTRL3_COUNT_1M_CLK_MASK)
/*! @} */

/*! @name STAT0 - Status Register 0 */
/*! @{ */

#define OSC_RC_400M_STAT0_CLK1M_ERR_MASK         (0x1U)
#define OSC_RC_400M_STAT0_CLK1M_ERR_SHIFT        (0U)
/*! CLK1M_ERR - Error flag for clk_1m_locked
 *  0b0..No effect
 *  0b1..The count value has been reached within one divided ref_clk period
 */
#define OSC_RC_400M_STAT0_CLK1M_ERR(x)           (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_STAT0_CLK1M_ERR_SHIFT)) & OSC_RC_400M_STAT0_CLK1M_ERR_MASK)
/*! @} */

/*! @name STAT1 - Status Register 1 */
/*! @{ */

#define OSC_RC_400M_STAT1_CURR_COUNT_VAL_MASK    (0xFFFF0000U)
#define OSC_RC_400M_STAT1_CURR_COUNT_VAL_SHIFT   (16U)
/*! CURR_COUNT_VAL - Current count for the fast clock */
#define OSC_RC_400M_STAT1_CURR_COUNT_VAL(x)      (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_STAT1_CURR_COUNT_VAL_SHIFT)) & OSC_RC_400M_STAT1_CURR_COUNT_VAL_MASK)
/*! @} */

/*! @name STAT2 - Status Register 2 */
/*! @{ */

#define OSC_RC_400M_STAT2_CURR_OSC_TUNE_VAL_MASK (0xFF000000U)
#define OSC_RC_400M_STAT2_CURR_OSC_TUNE_VAL_SHIFT (24U)
/*! CURR_OSC_TUNE_VAL - Current tuning value used by oscillator */
#define OSC_RC_400M_STAT2_CURR_OSC_TUNE_VAL(x)   (((uint32_t)(((uint32_t)(x)) << OSC_RC_400M_STAT2_CURR_OSC_TUNE_VAL_SHIFT)) & OSC_RC_400M_STAT2_CURR_OSC_TUNE_VAL_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group OSC_RC_400M_Register_Masks */


/*!
 * @}
 */ /* end of group OSC_RC_400M_Peripheral_Access_Layer */


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


#endif  /* PERI_OSC_RC_400M_H_ */

