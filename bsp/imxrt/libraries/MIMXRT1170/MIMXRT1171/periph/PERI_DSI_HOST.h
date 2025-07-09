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
**         CMSIS Peripheral Access Layer for DSI_HOST
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
 * @file PERI_DSI_HOST.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for DSI_HOST
 *
 * CMSIS Peripheral Access Layer for DSI_HOST
 */

#if !defined(PERI_DSI_HOST_H_)
#define PERI_DSI_HOST_H_                         /**< Symbol preventing repeated inclusion */

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
   -- DSI_HOST Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DSI_HOST_Peripheral_Access_Layer DSI_HOST Peripheral Access Layer
 * @{
 */

/** DSI_HOST - Register Layout Typedef */
typedef struct {
  __IO uint32_t CFG_NUM_LANES;                     /**< Configure Number of Lanes, offset: 0x0 */
  __IO uint32_t CFG_NONCONTINUOUS_CLK;             /**< Configure Noncontinuous Clock, offset: 0x4 */
  __IO uint32_t CFG_T_PRE;                         /**< Configure TCLK-PRE DPHY, offset: 0x8 */
  __IO uint32_t CFG_T_POST;                        /**< Configure TCLK Wait, offset: 0xC */
  __IO uint32_t CFG_TX_GAP;                        /**< Configure Transmit Gap, offset: 0x10 */
  __IO uint32_t CFG_AUTOINSERT_EOTP;               /**< Configure Auto Insert EoTp, offset: 0x14 */
  __IO uint32_t CFG_EXTRA_CMDS_AFTER_EOTP;         /**< Configure Extra Packets after EOTP, offset: 0x18 */
  __IO uint32_t CFG_HTX_TO_COUNT;                  /**< Configure HTX Timeout Count, offset: 0x1C */
  __IO uint32_t CFG_LRX_H_TO_COUNT;                /**< Configure Low-Power Receive Timeout Count, offset: 0x20 */
  __IO uint32_t CFG_BTA_H_TO_COUNT;                /**< Configure BTA_H Timeout Count, offset: 0x24 */
  __IO uint32_t CFG_TWAKEUP;                       /**< Configure Twakeup, offset: 0x28 */
  __I  uint32_t CFG_STATUS_OUT;                    /**< Configure Status Out, offset: 0x2C */
  __I  uint32_t RX_ERROR_STATUS;                   /**< Receive Error Status, offset: 0x30 */
} DSI_HOST_Type;

/* ----------------------------------------------------------------------------
   -- DSI_HOST Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DSI_HOST_Register_Masks DSI_HOST Register Masks
 * @{
 */

/*! @name CFG_NUM_LANES - Configure Number of Lanes */
/*! @{ */

#define DSI_HOST_CFG_NUM_LANES_NUM_LANES_MASK    (0x3U)
#define DSI_HOST_CFG_NUM_LANES_NUM_LANES_SHIFT   (0U)
/*! NUM_LANES - Number of active lanes.
 *  0b00..1 lane
 *  0b01..2 lanes
 */
#define DSI_HOST_CFG_NUM_LANES_NUM_LANES(x)      (((uint32_t)(((uint32_t)(x)) << DSI_HOST_CFG_NUM_LANES_NUM_LANES_SHIFT)) & DSI_HOST_CFG_NUM_LANES_NUM_LANES_MASK)
/*! @} */

/*! @name CFG_NONCONTINUOUS_CLK - Configure Noncontinuous Clock */
/*! @{ */

#define DSI_HOST_CFG_NONCONTINUOUS_CLK_CLK_MODE_MASK (0x1U)
#define DSI_HOST_CFG_NONCONTINUOUS_CLK_CLK_MODE_SHIFT (0U)
/*! CLK_MODE - Clock Mode
 *  0b0..Continuous high speed clock
 *  0b1..Non-Continuous high speed clock
 */
#define DSI_HOST_CFG_NONCONTINUOUS_CLK_CLK_MODE(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_CFG_NONCONTINUOUS_CLK_CLK_MODE_SHIFT)) & DSI_HOST_CFG_NONCONTINUOUS_CLK_CLK_MODE_MASK)
/*! @} */

/*! @name CFG_T_PRE - Configure TCLK-PRE DPHY */
/*! @{ */

#define DSI_HOST_CFG_T_PRE_NUM_PERIODS_MASK      (0xFFU)
#define DSI_HOST_CFG_T_PRE_NUM_PERIODS_SHIFT     (0U)
/*! NUM_PERIODS - Number of Periods */
#define DSI_HOST_CFG_T_PRE_NUM_PERIODS(x)        (((uint32_t)(((uint32_t)(x)) << DSI_HOST_CFG_T_PRE_NUM_PERIODS_SHIFT)) & DSI_HOST_CFG_T_PRE_NUM_PERIODS_MASK)
/*! @} */

/*! @name CFG_T_POST - Configure TCLK Wait */
/*! @{ */

#define DSI_HOST_CFG_T_POST_NUM_PERIODS_MASK     (0xFFU)
#define DSI_HOST_CFG_T_POST_NUM_PERIODS_SHIFT    (0U)
/*! NUM_PERIODS - Number of Periods */
#define DSI_HOST_CFG_T_POST_NUM_PERIODS(x)       (((uint32_t)(((uint32_t)(x)) << DSI_HOST_CFG_T_POST_NUM_PERIODS_SHIFT)) & DSI_HOST_CFG_T_POST_NUM_PERIODS_MASK)
/*! @} */

/*! @name CFG_TX_GAP - Configure Transmit Gap */
/*! @{ */

#define DSI_HOST_CFG_TX_GAP_NUM_PERIODS_MASK     (0xFFU)
#define DSI_HOST_CFG_TX_GAP_NUM_PERIODS_SHIFT    (0U)
/*! NUM_PERIODS - Number of Periods */
#define DSI_HOST_CFG_TX_GAP_NUM_PERIODS(x)       (((uint32_t)(((uint32_t)(x)) << DSI_HOST_CFG_TX_GAP_NUM_PERIODS_SHIFT)) & DSI_HOST_CFG_TX_GAP_NUM_PERIODS_MASK)
/*! @} */

/*! @name CFG_AUTOINSERT_EOTP - Configure Auto Insert EoTp */
/*! @{ */

#define DSI_HOST_CFG_AUTOINSERT_EOTP_AUTOINSERT_MASK (0x1U)
#define DSI_HOST_CFG_AUTOINSERT_EOTP_AUTOINSERT_SHIFT (0U)
/*! AUTOINSERT - Auto Insert
 *  0b0..EoTp is not automatically inserted
 *  0b1..EoTp is automatically inserted
 */
#define DSI_HOST_CFG_AUTOINSERT_EOTP_AUTOINSERT(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_CFG_AUTOINSERT_EOTP_AUTOINSERT_SHIFT)) & DSI_HOST_CFG_AUTOINSERT_EOTP_AUTOINSERT_MASK)
/*! @} */

/*! @name CFG_EXTRA_CMDS_AFTER_EOTP - Configure Extra Packets after EOTP */
/*! @{ */

#define DSI_HOST_CFG_EXTRA_CMDS_AFTER_EOTP_EXTRA_EOTP_MASK (0xFFU)
#define DSI_HOST_CFG_EXTRA_CMDS_AFTER_EOTP_EXTRA_EOTP_SHIFT (0U)
/*! EXTRA_EOTP - Extra EOTP */
#define DSI_HOST_CFG_EXTRA_CMDS_AFTER_EOTP_EXTRA_EOTP(x) (((uint32_t)(((uint32_t)(x)) << DSI_HOST_CFG_EXTRA_CMDS_AFTER_EOTP_EXTRA_EOTP_SHIFT)) & DSI_HOST_CFG_EXTRA_CMDS_AFTER_EOTP_EXTRA_EOTP_MASK)
/*! @} */

/*! @name CFG_HTX_TO_COUNT - Configure HTX Timeout Count */
/*! @{ */

#define DSI_HOST_CFG_HTX_TO_COUNT_COUNT_MASK     (0xFFFFFFU)
#define DSI_HOST_CFG_HTX_TO_COUNT_COUNT_SHIFT    (0U)
/*! COUNT - Count */
#define DSI_HOST_CFG_HTX_TO_COUNT_COUNT(x)       (((uint32_t)(((uint32_t)(x)) << DSI_HOST_CFG_HTX_TO_COUNT_COUNT_SHIFT)) & DSI_HOST_CFG_HTX_TO_COUNT_COUNT_MASK)
/*! @} */

/*! @name CFG_LRX_H_TO_COUNT - Configure Low-Power Receive Timeout Count */
/*! @{ */

#define DSI_HOST_CFG_LRX_H_TO_COUNT_COUNT_MASK   (0xFFFFFFU)
#define DSI_HOST_CFG_LRX_H_TO_COUNT_COUNT_SHIFT  (0U)
/*! COUNT - Count */
#define DSI_HOST_CFG_LRX_H_TO_COUNT_COUNT(x)     (((uint32_t)(((uint32_t)(x)) << DSI_HOST_CFG_LRX_H_TO_COUNT_COUNT_SHIFT)) & DSI_HOST_CFG_LRX_H_TO_COUNT_COUNT_MASK)
/*! @} */

/*! @name CFG_BTA_H_TO_COUNT - Configure BTA_H Timeout Count */
/*! @{ */

#define DSI_HOST_CFG_BTA_H_TO_COUNT_COUNT_MASK   (0xFFFFFFU)
#define DSI_HOST_CFG_BTA_H_TO_COUNT_COUNT_SHIFT  (0U)
/*! COUNT - Count */
#define DSI_HOST_CFG_BTA_H_TO_COUNT_COUNT(x)     (((uint32_t)(((uint32_t)(x)) << DSI_HOST_CFG_BTA_H_TO_COUNT_COUNT_SHIFT)) & DSI_HOST_CFG_BTA_H_TO_COUNT_COUNT_MASK)
/*! @} */

/*! @name CFG_TWAKEUP - Configure Twakeup */
/*! @{ */

#define DSI_HOST_CFG_TWAKEUP_NUM_PERIODS_MASK    (0x7FFFFU)
#define DSI_HOST_CFG_TWAKEUP_NUM_PERIODS_SHIFT   (0U)
/*! NUM_PERIODS - Number of Periods */
#define DSI_HOST_CFG_TWAKEUP_NUM_PERIODS(x)      (((uint32_t)(((uint32_t)(x)) << DSI_HOST_CFG_TWAKEUP_NUM_PERIODS_SHIFT)) & DSI_HOST_CFG_TWAKEUP_NUM_PERIODS_MASK)
/*! @} */

/*! @name CFG_STATUS_OUT - Configure Status Out */
/*! @{ */

#define DSI_HOST_CFG_STATUS_OUT_STATUS_MASK      (0xFFFFFFFFU)
#define DSI_HOST_CFG_STATUS_OUT_STATUS_SHIFT     (0U)
/*! STATUS - Status */
#define DSI_HOST_CFG_STATUS_OUT_STATUS(x)        (((uint32_t)(((uint32_t)(x)) << DSI_HOST_CFG_STATUS_OUT_STATUS_SHIFT)) & DSI_HOST_CFG_STATUS_OUT_STATUS_MASK)
/*! @} */

/*! @name RX_ERROR_STATUS - Receive Error Status */
/*! @{ */

#define DSI_HOST_RX_ERROR_STATUS_STATUS_MASK     (0x7FFU)
#define DSI_HOST_RX_ERROR_STATUS_STATUS_SHIFT    (0U)
/*! STATUS - Status */
#define DSI_HOST_RX_ERROR_STATUS_STATUS(x)       (((uint32_t)(((uint32_t)(x)) << DSI_HOST_RX_ERROR_STATUS_STATUS_SHIFT)) & DSI_HOST_RX_ERROR_STATUS_STATUS_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group DSI_HOST_Register_Masks */


/*!
 * @}
 */ /* end of group DSI_HOST_Peripheral_Access_Layer */


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


#endif  /* PERI_DSI_HOST_H_ */

