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
**         CMSIS Peripheral Access Layer for DSI_HOST_NXP_FDSOI28_DPHY_INTFC
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
 * @file PERI_DSI_HOST_NXP_FDSOI28_DPHY_INTFC.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for DSI_HOST_NXP_FDSOI28_DPHY_INTFC
 *
 * CMSIS Peripheral Access Layer for DSI_HOST_NXP_FDSOI28_DPHY_INTFC
 */

#if !defined(PERI_DSI_HOST_NXP_FDSOI28_DPHY_INTFC_H_)
#define PERI_DSI_HOST_NXP_FDSOI28_DPHY_INTFC_H_  /**< Symbol preventing repeated inclusion */

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
   -- DSI_HOST_NXP_FDSOI28_DPHY_INTFC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DSI_HOST_NXP_FDSOI28_DPHY_INTFC_Peripheral_Access_Layer DSI_HOST_NXP_FDSOI28_DPHY_INTFC Peripheral Access Layer
 * @{
 */

/** DSI_HOST_NXP_FDSOI28_DPHY_INTFC - Register Layout Typedef */
typedef struct {
  __IO uint32_t PD_TX;                             /**< Powerdown Transmit, offset: 0x0 */
  __IO uint32_t M_PRG_HS_PREPARE;                  /**< M Program High Speed Prepare, offset: 0x4 */
  __IO uint32_t MC_PRG_HS_PREPARE;                 /**< MC Program High Speed Prepare, offset: 0x8 */
  __IO uint32_t M_PRG_HS_ZERO;                     /**< M Program High Speed Zero, offset: 0xC */
  __IO uint32_t MC_PRG_HS_ZERO;                    /**< MC Program High Speed Zero, offset: 0x10 */
  __IO uint32_t M_PRG_HS_TRAIL;                    /**< M Program High Speed Trail, offset: 0x14 */
  __IO uint32_t MC_PRG_HS_TRAIL;                   /**< MC Program High Speed Trail, offset: 0x18 */
  __IO uint32_t PD_PLL;                            /**< Powerdown PLL, offset: 0x1C */
  __IO uint32_t TST;                               /**< Test, offset: 0x20 */
  __IO uint32_t CN;                                /**< Control N Divider, offset: 0x24 */
  __IO uint32_t CM;                                /**< Control M Divider, offset: 0x28 */
  __IO uint32_t CO;                                /**< Control Divider, offset: 0x2C */
  __I  uint32_t LOCK;                              /**< Lock, offset: 0x30 */
  __IO uint32_t LOCK_BYP;                          /**< Lock BYP, offset: 0x34 */
  __IO uint32_t TX_RCAL;                           /**< TX_RCAL, offset: 0x38 */
  __IO uint32_t AUTO_PD_EN;                        /**< AUTO_PD_EN, offset: 0x3C */
  __IO uint32_t RXLPRP;                            /**< RXLPRP, offset: 0x40 */
  __IO uint32_t RXCDRP;                            /**< RXCDRP, offset: 0x44 */
} DSI_HOST_NXP_FDSOI28_DPHY_INTFC_Type;

/* ----------------------------------------------------------------------------
   -- DSI_HOST_NXP_FDSOI28_DPHY_INTFC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DSI_HOST_NXP_FDSOI28_DPHY_INTFC_Register_Masks DSI_HOST_NXP_FDSOI28_DPHY_INTFC Register Masks
 * @{
 */

/*! @name PD_TX - Powerdown Transmit */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_PD_TX_PD_TX_MASK (0x1U)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_PD_TX_PD_TX_SHIFT (0U)
/*! PD_TX - Power Down Transmit
 *  0b0..Power Up
 *  0b1..Power Down
 */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_PD_TX_PD_TX(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_PD_TX_PD_TX_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_PD_TX_PD_TX_MASK)
/*! @} */

/*! @name M_PRG_HS_PREPARE - M Program High Speed Prepare */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_PREPARE_M_PRG_HS_PREPARE_MASK (0x3U)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_PREPARE_M_PRG_HS_PREPARE_SHIFT (0U)
/*! M_PRG_HS_PREPARE - DPHY m_PRG_HS_PREPARE input */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_PREPARE_M_PRG_HS_PREPARE(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_PREPARE_M_PRG_HS_PREPARE_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_PREPARE_M_PRG_HS_PREPARE_MASK)
/*! @} */

/*! @name MC_PRG_HS_PREPARE - MC Program High Speed Prepare */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_PREPARE_MC_PRG_HS_PREPARE_MASK (0x1U)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_PREPARE_MC_PRG_HS_PREPARE_SHIFT (0U)
/*! MC_PRG_HS_PREPARE - DPHY mc_PRG_HS_PREPARE input */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_PREPARE_MC_PRG_HS_PREPARE(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_PREPARE_MC_PRG_HS_PREPARE_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_PREPARE_MC_PRG_HS_PREPARE_MASK)
/*! @} */

/*! @name M_PRG_HS_ZERO - M Program High Speed Zero */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_ZERO_M_PRG_HS_ZERO_MASK (0x1FU)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_ZERO_M_PRG_HS_ZERO_SHIFT (0U)
/*! M_PRG_HS_ZERO - DPHY m_PRG_HS_ZERO input */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_ZERO_M_PRG_HS_ZERO(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_ZERO_M_PRG_HS_ZERO_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_ZERO_M_PRG_HS_ZERO_MASK)
/*! @} */

/*! @name MC_PRG_HS_ZERO - MC Program High Speed Zero */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_ZERO_MC_PRG_HS_ZERO_MASK (0x3FU)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_ZERO_MC_PRG_HS_ZERO_SHIFT (0U)
/*! MC_PRG_HS_ZERO - DPHY mc_PRG_HS_ZERO input */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_ZERO_MC_PRG_HS_ZERO(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_ZERO_MC_PRG_HS_ZERO_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_ZERO_MC_PRG_HS_ZERO_MASK)
/*! @} */

/*! @name M_PRG_HS_TRAIL - M Program High Speed Trail */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_TRAIL_M_PRG_HS_TRAIL_MASK (0xFU)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_TRAIL_M_PRG_HS_TRAIL_SHIFT (0U)
/*! M_PRG_HS_TRAIL - DPHY m_PRG_HS_TRAIL input */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_TRAIL_M_PRG_HS_TRAIL(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_TRAIL_M_PRG_HS_TRAIL_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_M_PRG_HS_TRAIL_M_PRG_HS_TRAIL_MASK)
/*! @} */

/*! @name MC_PRG_HS_TRAIL - MC Program High Speed Trail */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_TRAIL_MC_PRG_HS_TRAIL_MASK (0xFU)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_TRAIL_MC_PRG_HS_TRAIL_SHIFT (0U)
/*! MC_PRG_HS_TRAIL - DPHY mc_PRG_HS_TRAIL input */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_TRAIL_MC_PRG_HS_TRAIL(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_TRAIL_MC_PRG_HS_TRAIL_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_MC_PRG_HS_TRAIL_MC_PRG_HS_TRAIL_MASK)
/*! @} */

/*! @name PD_PLL - Powerdown PLL */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_PD_PLL_PD_PLL_MASK (0x1U)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_PD_PLL_PD_PLL_SHIFT (0U)
/*! PD_PLL - Powerdown signal
 *  0b0..Power up PLL
 *  0b1..Power down PLL
 */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_PD_PLL_PD_PLL(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_PD_PLL_PD_PLL_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_PD_PLL_PD_PLL_MASK)
/*! @} */

/*! @name TST - Test */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_TST_TST_MASK (0x3FU)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_TST_TST_SHIFT (0U)
/*! TST - Test */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_TST_TST(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_TST_TST_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_TST_TST_MASK)
/*! @} */

/*! @name CN - Control N Divider */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CN_CN_MASK (0x1FU)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CN_CN_SHIFT (0U)
/*! CN - Control N Divider */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CN_CN(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CN_CN_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CN_CN_MASK)
/*! @} */

/*! @name CM - Control M Divider */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CM_CM_MASK (0xFFU)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CM_CM_SHIFT (0U)
/*! CM - Control M divider */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CM_CM(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CM_CM_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CM_CM_MASK)
/*! @} */

/*! @name CO - Control Divider */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CO_CO_MASK (0x3U)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CO_CO_SHIFT (0U)
/*! CO - Control O divider
 *  0b00..Divide by 1
 *  0b01..Divide by 2
 *  0b10..Divide by 4
 *  0b11..Divide by 8
 */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CO_CO(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CO_CO_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_CO_CO_MASK)
/*! @} */

/*! @name LOCK - Lock */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_LOCK_LOCK_MASK (0x1U)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_LOCK_LOCK_SHIFT (0U)
/*! LOCK - Lock Detect Output
 *  0b0..PLL not locked
 *  0b1..PLL has achieved frequency lock
 */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_LOCK_LOCK(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_LOCK_LOCK_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_LOCK_LOCK_MASK)
/*! @} */

/*! @name LOCK_BYP - Lock BYP */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_LOCK_BYP_LOCK_BYP_MASK (0x1U)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_LOCK_BYP_LOCK_BYP_SHIFT (0U)
/*! LOCK_BYP - DPHY LOCK_BYP input
 *  0b0..PLL LOCK signal will gate TxByteClkHS clock
 *  0b1..PLL LOCK signal will not gate TxByteClkHS clock, CIL based counter will be used to gate the TxByteClkHS
 */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_LOCK_BYP_LOCK_BYP(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_LOCK_BYP_LOCK_BYP_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_LOCK_BYP_LOCK_BYP_MASK)
/*! @} */

/*! @name TX_RCAL - TX_RCAL */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_TX_RCAL_TX_RCAL_MASK (0x3U)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_TX_RCAL_TX_RCAL_SHIFT (0U)
/*! TX_RCAL - TX_RCAL
 *  0b00..20% higher than mid-range. Highest impedance setting
 *  0b01..Mid-range impedance setting (default)
 *  0b10..15% lower than mid-range
 *  0b11..25% lower than mid-range. Lowest impedance setting
 */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_TX_RCAL_TX_RCAL(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_TX_RCAL_TX_RCAL_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_TX_RCAL_TX_RCAL_MASK)
/*! @} */

/*! @name AUTO_PD_EN - AUTO_PD_EN */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_AUTO_PD_EN_AUTO_PD_EN_MASK (0x1U)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_AUTO_PD_EN_AUTO_PD_EN_SHIFT (0U)
/*! AUTO_PD_EN - DPHY AUTO_PD_EN input
 *  0b0..Inactive lanes are powered up and driving LP11
 *  0b1..inactive lanes are powered down
 */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_AUTO_PD_EN_AUTO_PD_EN(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_AUTO_PD_EN_AUTO_PD_EN_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_AUTO_PD_EN_AUTO_PD_EN_MASK)
/*! @} */

/*! @name RXLPRP - RXLPRP */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_RXLPRP_RXLPRP_MASK (0x3U)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_RXLPRP_RXLPRP_SHIFT (0U)
/*! RXLPRP - DPHY RXLPRP input */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_RXLPRP_RXLPRP(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_RXLPRP_RXLPRP_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_RXLPRP_RXLPRP_MASK)
/*! @} */

/*! @name RXCDRP - RXCDRP */
/*! @{ */

#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_RXCDRP_RXCDRP_MASK (0x3U)
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_RXCDRP_RXCDRP_SHIFT (0U)
/*! RXCDRP - DPHY RXCDRP input
 *  0b00..344mV
 *  0b01..325mV (Default)
 *  0b10..307mV
 *  0b11..Reserved, invalid
 */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_RXCDRP_RXCDRP(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_NXP_FDSOI28_DPHY_INTFC_RXCDRP_RXCDRP_SHIFT)) & DSI_HOST_NXP_FDSOI28_DPHY_INTFC_RXCDRP_RXCDRP_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group DSI_HOST_NXP_FDSOI28_DPHY_INTFC_Register_Masks */


/*!
 * @}
 */ /* end of group DSI_HOST_NXP_FDSOI28_DPHY_INTFC_Peripheral_Access_Layer */


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


#endif  /* PERI_DSI_HOST_NXP_FDSOI28_DPHY_INTFC_H_ */

