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
**         CMSIS Peripheral Access Layer for MIPI_CSI2RX
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
 * @file PERI_MIPI_CSI2RX.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for MIPI_CSI2RX
 *
 * CMSIS Peripheral Access Layer for MIPI_CSI2RX
 */

#if !defined(PERI_MIPI_CSI2RX_H_)
#define PERI_MIPI_CSI2RX_H_                      /**< Symbol preventing repeated inclusion */

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
   -- MIPI_CSI2RX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MIPI_CSI2RX_Peripheral_Access_Layer MIPI_CSI2RX Peripheral Access Layer
 * @{
 */

/** MIPI_CSI2RX - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[256];
  __IO uint32_t CFG_NUM_LANES;                     /**< Lane Configuration Register, offset: 0x100 */
  __IO uint32_t CFG_DISABLE_DATA_LANES;            /**< Disable Data Lane Register, offset: 0x104 */
  __I  uint32_t BIT_ERR;                           /**< ECC and CRC Error Status Register, offset: 0x108 */
  __I  uint32_t IRQ_STATUS;                        /**< IRQ Status Register, offset: 0x10C */
  __IO uint32_t IRQ_MASK;                          /**< IRQ Mask Setting Register, offset: 0x110 */
  __I  uint32_t ULPS_STATUS;                       /**< Ultra Low Power State (ULPS) Status Register, offset: 0x114 */
  __I  uint32_t PPI_ERRSOT_HS;                     /**< ERRSotHS Status Register, offset: 0x118 */
  __I  uint32_t PPI_ERRSOTSYNC_HS;                 /**< ErrSotSync HS Status Register, offset: 0x11C */
  __I  uint32_t PPI_ERRESC;                        /**< ErrEsc Status Register, offset: 0x120 */
  __I  uint32_t PPI_ERRSYNCESC;                    /**< ErrSyncEsc Status Register, offset: 0x124 */
  __I  uint32_t PPI_ERRCONTROL;                    /**< ErrControl Status Register, offset: 0x128 */
  __IO uint32_t CFG_DISABLE_PAYLOAD_0;             /**< Disable Payload 0 Register, offset: 0x12C */
  __IO uint32_t CFG_DISABLE_PAYLOAD_1;             /**< Disable Payload 1 Register, offset: 0x130 */
} MIPI_CSI2RX_Type;

/* ----------------------------------------------------------------------------
   -- MIPI_CSI2RX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MIPI_CSI2RX_Register_Masks MIPI_CSI2RX Register Masks
 * @{
 */

/*! @name CFG_NUM_LANES - Lane Configuration Register */
/*! @{ */

#define MIPI_CSI2RX_CFG_NUM_LANES_CFG_NUM_LANES_MASK (0x3U)
#define MIPI_CSI2RX_CFG_NUM_LANES_CFG_NUM_LANES_SHIFT (0U)
/*! CFG_NUM_LANES - This field is used to set the number of active lanes for receiving data.
 *  0b00..1 Lane
 *  0b01..2 Lane
 *  0b10-0b11..
 */
#define MIPI_CSI2RX_CFG_NUM_LANES_CFG_NUM_LANES(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_NUM_LANES_CFG_NUM_LANES_SHIFT)) & MIPI_CSI2RX_CFG_NUM_LANES_CFG_NUM_LANES_MASK)
/*! @} */

/*! @name CFG_DISABLE_DATA_LANES - Disable Data Lane Register */
/*! @{ */

#define MIPI_CSI2RX_CFG_DISABLE_DATA_LANES_CFG_DISABLE_DATA_LANES_MASK (0xFU)
#define MIPI_CSI2RX_CFG_DISABLE_DATA_LANES_CFG_DISABLE_DATA_LANES_SHIFT (0U)
/*! CFG_DISABLE_DATA_LANES - Used to disable data lanes. */
#define MIPI_CSI2RX_CFG_DISABLE_DATA_LANES_CFG_DISABLE_DATA_LANES(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_DATA_LANES_CFG_DISABLE_DATA_LANES_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_DATA_LANES_CFG_DISABLE_DATA_LANES_MASK)
/*! @} */

/*! @name BIT_ERR - ECC and CRC Error Status Register */
/*! @{ */

#define MIPI_CSI2RX_BIT_ERR_BIT_ERR_MASK         (0x3FFU)
#define MIPI_CSI2RX_BIT_ERR_BIT_ERR_SHIFT        (0U)
/*! BIT_ERR - This field shows the error status of ECC and CRC */
#define MIPI_CSI2RX_BIT_ERR_BIT_ERR(x)           (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_BIT_ERR_BIT_ERR_SHIFT)) & MIPI_CSI2RX_BIT_ERR_BIT_ERR_MASK)
/*! @} */

/*! @name IRQ_STATUS - IRQ Status Register */
/*! @{ */

#define MIPI_CSI2RX_IRQ_STATUS_IRQ_STATUS_MASK   (0x1FFU)
#define MIPI_CSI2RX_IRQ_STATUS_IRQ_STATUS_SHIFT  (0U)
/*! IRQ_STATUS - This field shows the IRQ status */
#define MIPI_CSI2RX_IRQ_STATUS_IRQ_STATUS(x)     (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_IRQ_STATUS_IRQ_STATUS_SHIFT)) & MIPI_CSI2RX_IRQ_STATUS_IRQ_STATUS_MASK)
/*! @} */

/*! @name IRQ_MASK - IRQ Mask Setting Register */
/*! @{ */

#define MIPI_CSI2RX_IRQ_MASK_IRQ_MASK_MASK       (0x1FFU)
#define MIPI_CSI2RX_IRQ_MASK_IRQ_MASK_SHIFT      (0U)
/*! IRQ_MASK - This field shows the IRQ Mask setting */
#define MIPI_CSI2RX_IRQ_MASK_IRQ_MASK(x)         (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_IRQ_MASK_IRQ_MASK_SHIFT)) & MIPI_CSI2RX_IRQ_MASK_IRQ_MASK_MASK)
/*! @} */

/*! @name ULPS_STATUS - Ultra Low Power State (ULPS) Status Register */
/*! @{ */

#define MIPI_CSI2RX_ULPS_STATUS_STATUS_MASK      (0x3FFU)
#define MIPI_CSI2RX_ULPS_STATUS_STATUS_SHIFT     (0U)
/*! STATUS - This field shows the status of Rx D-PHY ULPS state */
#define MIPI_CSI2RX_ULPS_STATUS_STATUS(x)        (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_ULPS_STATUS_STATUS_SHIFT)) & MIPI_CSI2RX_ULPS_STATUS_STATUS_MASK)
/*! @} */

/*! @name PPI_ERRSOT_HS - ERRSotHS Status Register */
/*! @{ */

#define MIPI_CSI2RX_PPI_ERRSOT_HS_STATUS_MASK    (0xFU)
#define MIPI_CSI2RX_PPI_ERRSOT_HS_STATUS_SHIFT   (0U)
/*! STATUS - This field indicates PPI ErrSotHS captured status from D-PHY */
#define MIPI_CSI2RX_PPI_ERRSOT_HS_STATUS(x)      (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_PPI_ERRSOT_HS_STATUS_SHIFT)) & MIPI_CSI2RX_PPI_ERRSOT_HS_STATUS_MASK)
/*! @} */

/*! @name PPI_ERRSOTSYNC_HS - ErrSotSync HS Status Register */
/*! @{ */

#define MIPI_CSI2RX_PPI_ERRSOTSYNC_HS_STATUS_MASK (0xFU)
#define MIPI_CSI2RX_PPI_ERRSOTSYNC_HS_STATUS_SHIFT (0U)
/*! STATUS - This field indicates PPI ErrSotSync_HS captured status from D-PHY */
#define MIPI_CSI2RX_PPI_ERRSOTSYNC_HS_STATUS(x)  (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_PPI_ERRSOTSYNC_HS_STATUS_SHIFT)) & MIPI_CSI2RX_PPI_ERRSOTSYNC_HS_STATUS_MASK)
/*! @} */

/*! @name PPI_ERRESC - ErrEsc Status Register */
/*! @{ */

#define MIPI_CSI2RX_PPI_ERRESC_STATUS_MASK       (0xFU)
#define MIPI_CSI2RX_PPI_ERRESC_STATUS_SHIFT      (0U)
/*! STATUS - This field indicates PPI ErrEsc captured status from D-PHY */
#define MIPI_CSI2RX_PPI_ERRESC_STATUS(x)         (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_PPI_ERRESC_STATUS_SHIFT)) & MIPI_CSI2RX_PPI_ERRESC_STATUS_MASK)
/*! @} */

/*! @name PPI_ERRSYNCESC - ErrSyncEsc Status Register */
/*! @{ */

#define MIPI_CSI2RX_PPI_ERRSYNCESC_STATUS_MASK   (0xFU)
#define MIPI_CSI2RX_PPI_ERRSYNCESC_STATUS_SHIFT  (0U)
/*! STATUS - This field indicates PPI ErrSyncEsc captured status from D-PHY */
#define MIPI_CSI2RX_PPI_ERRSYNCESC_STATUS(x)     (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_PPI_ERRSYNCESC_STATUS_SHIFT)) & MIPI_CSI2RX_PPI_ERRSYNCESC_STATUS_MASK)
/*! @} */

/*! @name PPI_ERRCONTROL - ErrControl Status Register */
/*! @{ */

#define MIPI_CSI2RX_PPI_ERRCONTROL_STATUS_MASK   (0xFU)
#define MIPI_CSI2RX_PPI_ERRCONTROL_STATUS_SHIFT  (0U)
/*! STATUS - This field indicates PPI ErrControl captured status from D-PHY */
#define MIPI_CSI2RX_PPI_ERRCONTROL_STATUS(x)     (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_PPI_ERRCONTROL_STATUS_SHIFT)) & MIPI_CSI2RX_PPI_ERRCONTROL_STATUS_MASK)
/*! @} */

/*! @name CFG_DISABLE_PAYLOAD_0 - Disable Payload 0 Register */
/*! @{ */

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_NULL_MASK (0x1U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_NULL_SHIFT (0U)
/*! DIS_PAYLOAD_NULL - Null */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_NULL(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_NULL_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_NULL_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_BLANK_MASK (0x2U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_BLANK_SHIFT (1U)
/*! DIS_PAYLOAD_BLANK - Blank */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_BLANK(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_BLANK_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_BLANK_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_EMBEDDED_MASK (0x4U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_EMBEDDED_SHIFT (2U)
/*! DIS_PAYLOAD_EMBEDDED - Embedded */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_EMBEDDED(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_EMBEDDED_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_EMBEDDED_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_YUV420_MASK (0x400U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_YUV420_SHIFT (10U)
/*! DIS_PAYLOAD_YUV420 - Legacy YUV 420 8 bit */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_YUV420(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_YUV420_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_YUV420_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_YUV422_8BIT_MASK (0x4000U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_YUV422_8BIT_SHIFT (14U)
/*! DIS_PAYLOAD_YUV422_8BIT - YUV422 8 bit */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_YUV422_8BIT(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_YUV422_8BIT_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_YUV422_8BIT_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB444_MASK (0x10000U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB444_SHIFT (16U)
/*! DIS_PAYLOAD_RGB444 - RGB444 */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB444(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB444_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB444_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB555_MASK (0x20000U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB555_SHIFT (17U)
/*! DIS_PAYLOAD_RGB555 - RGB555 */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB555(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB555_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB555_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB565_MASK (0x40000U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB565_SHIFT (18U)
/*! DIS_PAYLOAD_RGB565 - RGB565 */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB565(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB565_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB565_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB666_MASK (0x80000U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB666_SHIFT (19U)
/*! DIS_PAYLOAD_RGB666 - RGB666 */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB666(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB666_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB666_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB888_MASK (0x100000U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB888_SHIFT (20U)
/*! DIS_PAYLOAD_RGB888 - RGB888 */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB888(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB888_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_0_DIS_PAYLOAD_RGB888_MASK)
/*! @} */

/*! @name CFG_DISABLE_PAYLOAD_1 - Disable Payload 1 Register */
/*! @{ */

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_30_MASK (0x1U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_30_SHIFT (0U)
/*! DIS_PAYLOAD_UDEF_30 - User defined type 0x31 */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_30(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_30_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_30_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_31_MASK (0x2U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_31_SHIFT (1U)
/*! DIS_PAYLOAD_UDEF_31 - User defined type 0x32 */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_31(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_31_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_31_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_32_MASK (0x4U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_32_SHIFT (2U)
/*! DIS_PAYLOAD_UDEF_32 - User defined type 0x33 */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_32(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_32_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_32_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_33_MASK (0x8U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_33_SHIFT (3U)
/*! DIS_PAYLOAD_UDEF_33 - User defined type 0x34 */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_33(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_33_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_33_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_34_MASK (0x10U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_34_SHIFT (4U)
/*! DIS_PAYLOAD_UDEF_34 - User defined type 0x35 */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_34(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_34_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_34_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_35_MASK (0x20U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_35_SHIFT (5U)
/*! DIS_PAYLOAD_UDEF_35 - User defined type 0x35 */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_35(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_35_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_35_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_36_MASK (0x40U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_36_SHIFT (6U)
/*! DIS_PAYLOAD_UDEF_36 - User defined type 0x36 */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_36(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_36_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_36_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_37_MASK (0x80U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_37_SHIFT (7U)
/*! DIS_PAYLOAD_UDEF_37 - User defined type 0x37 */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_37(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_37_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UDEF_37_MASK)

#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UNSUPPORTED_MASK (0x10000U)
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UNSUPPORTED_SHIFT (16U)
/*! DIS_PAYLOAD_UNSUPPORTED - Unsupported Data Types */
#define MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UNSUPPORTED(x) (((uint32_t)(((uint32_t)(x)) << MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UNSUPPORTED_SHIFT)) & MIPI_CSI2RX_CFG_DISABLE_PAYLOAD_1_DIS_PAYLOAD_UNSUPPORTED_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group MIPI_CSI2RX_Register_Masks */


/*!
 * @}
 */ /* end of group MIPI_CSI2RX_Peripheral_Access_Layer */


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


#endif  /* PERI_MIPI_CSI2RX_H_ */

