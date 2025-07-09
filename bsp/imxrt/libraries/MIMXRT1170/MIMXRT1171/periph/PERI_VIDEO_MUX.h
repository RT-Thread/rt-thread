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
**         CMSIS Peripheral Access Layer for VIDEO_MUX
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
 * @file PERI_VIDEO_MUX.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for VIDEO_MUX
 *
 * CMSIS Peripheral Access Layer for VIDEO_MUX
 */

#if !defined(PERI_VIDEO_MUX_H_)
#define PERI_VIDEO_MUX_H_                        /**< Symbol preventing repeated inclusion */

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
   -- VIDEO_MUX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VIDEO_MUX_Peripheral_Access_Layer VIDEO_MUX Peripheral Access Layer
 * @{
 */

/** VIDEO_MUX - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0 */
    __IO uint32_t RW;                                /**< Video mux Control Register, offset: 0x0 */
    __IO uint32_t SET;                               /**< Video mux Control Register, offset: 0x4 */
    __IO uint32_t CLR;                               /**< Video mux Control Register, offset: 0x8 */
    __IO uint32_t TOG;                               /**< Video mux Control Register, offset: 0xC */
  } VID_MUX_CTRL;
       uint8_t RESERVED_0[16];
  struct {                                         /* offset: 0x20 */
    __IO uint32_t RW;                                /**< Pixel Link Master(PLM) Control Register, offset: 0x20 */
    __IO uint32_t SET;                               /**< Pixel Link Master(PLM) Control Register, offset: 0x24 */
    __IO uint32_t CLR;                               /**< Pixel Link Master(PLM) Control Register, offset: 0x28 */
    __IO uint32_t TOG;                               /**< Pixel Link Master(PLM) Control Register, offset: 0x2C */
  } PLM_CTRL;
  struct {                                         /* offset: 0x30 */
    __IO uint32_t RW;                                /**< YUV420 Control Register, offset: 0x30 */
    __IO uint32_t SET;                               /**< YUV420 Control Register, offset: 0x34 */
    __IO uint32_t CLR;                               /**< YUV420 Control Register, offset: 0x38 */
    __IO uint32_t TOG;                               /**< YUV420 Control Register, offset: 0x3C */
  } YUV420_CTRL;
       uint8_t RESERVED_1[16];
  struct {                                         /* offset: 0x50 */
    __IO uint32_t RW;                                /**< Data Disable Register, offset: 0x50 */
    __IO uint32_t SET;                               /**< Data Disable Register, offset: 0x54 */
    __IO uint32_t CLR;                               /**< Data Disable Register, offset: 0x58 */
    __IO uint32_t TOG;                               /**< Data Disable Register, offset: 0x5C */
  } CFG_DT_DISABLE;
       uint8_t RESERVED_2[16];
  struct {                                         /* offset: 0x70 */
    __IO uint32_t RW;                                /**< MIPI DSI Control Register, offset: 0x70 */
    __IO uint32_t SET;                               /**< MIPI DSI Control Register, offset: 0x74 */
    __IO uint32_t CLR;                               /**< MIPI DSI Control Register, offset: 0x78 */
    __IO uint32_t TOG;                               /**< MIPI DSI Control Register, offset: 0x7C */
  } MIPI_DSI_CTRL;
} VIDEO_MUX_Type;

/* ----------------------------------------------------------------------------
   -- VIDEO_MUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VIDEO_MUX_Register_Masks VIDEO_MUX Register Masks
 * @{
 */

/*! @name VID_MUX_CTRL - Video mux Control Register */
/*! @{ */

#define VIDEO_MUX_VID_MUX_CTRL_CSI_SEL_MASK      (0x1U)
#define VIDEO_MUX_VID_MUX_CTRL_CSI_SEL_SHIFT     (0U)
/*! CSI_SEL - CSI sensor data input mux selector
 *  0b0..CSI sensor data is from Parallel CSI
 *  0b1..CSI sensor data is from MIPI CSI
 */
#define VIDEO_MUX_VID_MUX_CTRL_CSI_SEL(x)        (((uint32_t)(((uint32_t)(x)) << VIDEO_MUX_VID_MUX_CTRL_CSI_SEL_SHIFT)) & VIDEO_MUX_VID_MUX_CTRL_CSI_SEL_MASK)

#define VIDEO_MUX_VID_MUX_CTRL_LCDIF2_SEL_MASK   (0x2U)
#define VIDEO_MUX_VID_MUX_CTRL_LCDIF2_SEL_SHIFT  (1U)
/*! LCDIF2_SEL - LCDIF2 sensor data input mux selector
 *  0b0..LCDIFv2 sensor data is from Parallel CSI
 *  0b1..LCDIFv2 sensor data is from MIPI CSI
 */
#define VIDEO_MUX_VID_MUX_CTRL_LCDIF2_SEL(x)     (((uint32_t)(((uint32_t)(x)) << VIDEO_MUX_VID_MUX_CTRL_LCDIF2_SEL_SHIFT)) & VIDEO_MUX_VID_MUX_CTRL_LCDIF2_SEL_MASK)

#define VIDEO_MUX_VID_MUX_CTRL_MIPI_DSI_SEL_MASK (0x4U)
#define VIDEO_MUX_VID_MUX_CTRL_MIPI_DSI_SEL_SHIFT (2U)
/*! MIPI_DSI_SEL - MIPI DSI video data input mux selector
 *  0b0..MIPI DSI video data is from eLCDIF
 *  0b1..MIPI DSI video data is from LCDIFv2
 */
#define VIDEO_MUX_VID_MUX_CTRL_MIPI_DSI_SEL(x)   (((uint32_t)(((uint32_t)(x)) << VIDEO_MUX_VID_MUX_CTRL_MIPI_DSI_SEL_SHIFT)) & VIDEO_MUX_VID_MUX_CTRL_MIPI_DSI_SEL_MASK)

#define VIDEO_MUX_VID_MUX_CTRL_PARA_LCD_SEL_MASK (0x8U)
#define VIDEO_MUX_VID_MUX_CTRL_PARA_LCD_SEL_SHIFT (3U)
/*! PARA_LCD_SEL - Parallel LCDIF video data input mux selector
 *  0b0..Parallel LCDIF video data is from eLCDIF
 *  0b1..Parallel LCDIF video data is from LCDIFv2
 */
#define VIDEO_MUX_VID_MUX_CTRL_PARA_LCD_SEL(x)   (((uint32_t)(((uint32_t)(x)) << VIDEO_MUX_VID_MUX_CTRL_PARA_LCD_SEL_SHIFT)) & VIDEO_MUX_VID_MUX_CTRL_PARA_LCD_SEL_MASK)
/*! @} */

/*! @name PLM_CTRL - Pixel Link Master(PLM) Control Register */
/*! @{ */

#define VIDEO_MUX_PLM_CTRL_ENABLE_MASK           (0x1U)
#define VIDEO_MUX_PLM_CTRL_ENABLE_SHIFT          (0U)
/*! ENABLE - Enable the output of HYSNC and VSYNC
 *  0b0..No active HSYNC and VSYNC output
 *  0b1..Active HSYNC and VSYNC output
 */
#define VIDEO_MUX_PLM_CTRL_ENABLE(x)             (((uint32_t)(((uint32_t)(x)) << VIDEO_MUX_PLM_CTRL_ENABLE_SHIFT)) & VIDEO_MUX_PLM_CTRL_ENABLE_MASK)

#define VIDEO_MUX_PLM_CTRL_VSYNC_OVERRIDE_MASK   (0x2U)
#define VIDEO_MUX_PLM_CTRL_VSYNC_OVERRIDE_SHIFT  (1U)
/*! VSYNC_OVERRIDE - VSYNC override
 *  0b0..VSYNC is not asserted
 *  0b1..VSYNC is asserted
 */
#define VIDEO_MUX_PLM_CTRL_VSYNC_OVERRIDE(x)     (((uint32_t)(((uint32_t)(x)) << VIDEO_MUX_PLM_CTRL_VSYNC_OVERRIDE_SHIFT)) & VIDEO_MUX_PLM_CTRL_VSYNC_OVERRIDE_MASK)

#define VIDEO_MUX_PLM_CTRL_HSYNC_OVERRIDE_MASK   (0x4U)
#define VIDEO_MUX_PLM_CTRL_HSYNC_OVERRIDE_SHIFT  (2U)
/*! HSYNC_OVERRIDE - HSYNC override
 *  0b0..HSYNC is not asserted
 *  0b1..HSYNC is asserted
 */
#define VIDEO_MUX_PLM_CTRL_HSYNC_OVERRIDE(x)     (((uint32_t)(((uint32_t)(x)) << VIDEO_MUX_PLM_CTRL_HSYNC_OVERRIDE_SHIFT)) & VIDEO_MUX_PLM_CTRL_HSYNC_OVERRIDE_MASK)

#define VIDEO_MUX_PLM_CTRL_VALID_OVERRIDE_MASK   (0x8U)
#define VIDEO_MUX_PLM_CTRL_VALID_OVERRIDE_SHIFT  (3U)
/*! VALID_OVERRIDE - Valid override
 *  0b0..HSYNC and VSYNC is asserted
 *  0b1..HSYNC and VSYNC is not asserted
 */
#define VIDEO_MUX_PLM_CTRL_VALID_OVERRIDE(x)     (((uint32_t)(((uint32_t)(x)) << VIDEO_MUX_PLM_CTRL_VALID_OVERRIDE_SHIFT)) & VIDEO_MUX_PLM_CTRL_VALID_OVERRIDE_MASK)

#define VIDEO_MUX_PLM_CTRL_POLARITY_MASK         (0x10U)
#define VIDEO_MUX_PLM_CTRL_POLARITY_SHIFT        (4U)
/*! POLARITY - Polarity of HYSNC/VSYNC
 *  0b0..Keep the current polarity of HSYNC and VSYNC
 *  0b1..Invert the polarity of HSYNC and VSYNC
 */
#define VIDEO_MUX_PLM_CTRL_POLARITY(x)           (((uint32_t)(((uint32_t)(x)) << VIDEO_MUX_PLM_CTRL_POLARITY_SHIFT)) & VIDEO_MUX_PLM_CTRL_POLARITY_MASK)
/*! @} */

/*! @name YUV420_CTRL - YUV420 Control Register */
/*! @{ */

#define VIDEO_MUX_YUV420_CTRL_FST_LN_DATA_TYPE_MASK (0x1U)
#define VIDEO_MUX_YUV420_CTRL_FST_LN_DATA_TYPE_SHIFT (0U)
/*! FST_LN_DATA_TYPE - Data type of First Line
 *  0b0..Odd (default)
 *  0b1..Even
 */
#define VIDEO_MUX_YUV420_CTRL_FST_LN_DATA_TYPE(x) (((uint32_t)(((uint32_t)(x)) << VIDEO_MUX_YUV420_CTRL_FST_LN_DATA_TYPE_SHIFT)) & VIDEO_MUX_YUV420_CTRL_FST_LN_DATA_TYPE_MASK)
/*! @} */

/*! @name CFG_DT_DISABLE - Data Disable Register */
/*! @{ */

#define VIDEO_MUX_CFG_DT_DISABLE_CFG_DT_DISABLE_MASK (0xFFFFFFU)
#define VIDEO_MUX_CFG_DT_DISABLE_CFG_DT_DISABLE_SHIFT (0U)
/*! CFG_DT_DISABLE - Data Type Disable */
#define VIDEO_MUX_CFG_DT_DISABLE_CFG_DT_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << VIDEO_MUX_CFG_DT_DISABLE_CFG_DT_DISABLE_SHIFT)) & VIDEO_MUX_CFG_DT_DISABLE_CFG_DT_DISABLE_MASK)
/*! @} */

/*! @name MIPI_DSI_CTRL - MIPI DSI Control Register */
/*! @{ */

#define VIDEO_MUX_MIPI_DSI_CTRL_DPI_SD_MASK      (0x1U)
#define VIDEO_MUX_MIPI_DSI_CTRL_DPI_SD_SHIFT     (0U)
/*! DPI_SD - Shut Down - Control to shutdown display (type 4 only)
 *  0b0..No effect
 *  0b1..Send shutdown command
 */
#define VIDEO_MUX_MIPI_DSI_CTRL_DPI_SD(x)        (((uint32_t)(((uint32_t)(x)) << VIDEO_MUX_MIPI_DSI_CTRL_DPI_SD_SHIFT)) & VIDEO_MUX_MIPI_DSI_CTRL_DPI_SD_MASK)

#define VIDEO_MUX_MIPI_DSI_CTRL_DPI_CM_MASK      (0x2U)
#define VIDEO_MUX_MIPI_DSI_CTRL_DPI_CM_SHIFT     (1U)
/*! DPI_CM - Color Mode control
 *  0b0..Normal Mode
 *  0b1..Low-color mode
 */
#define VIDEO_MUX_MIPI_DSI_CTRL_DPI_CM(x)        (((uint32_t)(((uint32_t)(x)) << VIDEO_MUX_MIPI_DSI_CTRL_DPI_CM_SHIFT)) & VIDEO_MUX_MIPI_DSI_CTRL_DPI_CM_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group VIDEO_MUX_Register_Masks */


/*!
 * @}
 */ /* end of group VIDEO_MUX_Peripheral_Access_Layer */


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


#endif  /* PERI_VIDEO_MUX_H_ */

