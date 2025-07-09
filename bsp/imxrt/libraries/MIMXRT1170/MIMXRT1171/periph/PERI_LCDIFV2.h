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
**         CMSIS Peripheral Access Layer for LCDIFV2
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
 * @file PERI_LCDIFV2.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for LCDIFV2
 *
 * CMSIS Peripheral Access Layer for LCDIFV2
 */

#if !defined(PERI_LCDIFV2_H_)
#define PERI_LCDIFV2_H_                          /**< Symbol preventing repeated inclusion */

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
   -- LCDIFV2 Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LCDIFV2_Peripheral_Access_Layer LCDIFV2 Peripheral Access Layer
 * @{
 */

/** LCDIFV2 - Size of Registers Arrays */
#define LCDIFV2_INT_COUNT                         2u
#define LCDIFV2_LAYER_COUNT                       8u

/** LCDIFV2 - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< LCDIFv2 display control Register, offset: 0x0 */
  __IO uint32_t CTRL_SET;                          /**< LCDIFv2 display control Register, offset: 0x4 */
  __IO uint32_t CTRL_CLR;                          /**< LCDIFv2 display control Register, offset: 0x8 */
  __IO uint32_t CTRL_TOG;                          /**< LCDIFv2 display control Register, offset: 0xC */
  __IO uint32_t DISP_PARA;                         /**< Display Parameter Register, offset: 0x10 */
  __IO uint32_t DISP_SIZE;                         /**< Display Size Register, offset: 0x14 */
  __IO uint32_t HSYN_PARA;                         /**< Horizontal Sync Parameter Register, offset: 0x18 */
  __IO uint32_t VSYN_PARA;                         /**< Vertical Sync Parameter Register, offset: 0x1C */
  struct {                                         /* offset: 0x20, array step: 0x10 */
    __IO uint32_t INT_STATUS;                        /**< Interrupt Status Register for domain 0..Interrupt Status Register for domain 1, array offset: 0x20, array step: 0x10 */
    __IO uint32_t INT_ENABLE;                        /**< Interrupt Enable Register for domain 0..Interrupt Enable Register for domain 1, array offset: 0x24, array step: 0x10 */
         uint8_t RESERVED_0[8];
  } INT[LCDIFV2_INT_COUNT];
       uint32_t PDI_PARA;                          /**< Reserved, offset: 0x40 */
       uint8_t RESERVED_0[444];
  struct {                                         /* offset: 0x200, array step: 0x40 */
    __IO uint32_t CTRLDESCL1;                        /**< Control Descriptor Layer 1 Register, array offset: 0x200, array step: 0x40 */
    __IO uint32_t CTRLDESCL2;                        /**< Control Descriptor Layer 2 Register, array offset: 0x204, array step: 0x40 */
    __IO uint32_t CTRLDESCL3;                        /**< Control Descriptor Layer 3 Register, array offset: 0x208, array step: 0x40 */
    __IO uint32_t CTRLDESCL4;                        /**< Control Descriptor Layer 4 Register, array offset: 0x20C, array step: 0x40 */
    __IO uint32_t CTRLDESCL5;                        /**< Control Descriptor Layer 5 Register, array offset: 0x210, array step: 0x40 */
    __IO uint32_t CTRLDESCL6;                        /**< Control Descriptor Layer 6 Register, array offset: 0x214, array step: 0x40 */
    __IO uint32_t CSC_COEF0;                         /**< Color Space Conversion Coefficient Register 0, array offset: 0x218, array step: 0x40, valid indices: [0-1] */
    __IO uint32_t CSC_COEF1;                         /**< Color Space Conversion Coefficient Register 1, array offset: 0x21C, array step: 0x40, valid indices: [0-1] */
    __IO uint32_t CSC_COEF2;                         /**< Color Space Conversion Coefficient Register 2, array offset: 0x220, array step: 0x40, valid indices: [0-1] */
         uint8_t RESERVED_0[28];
  } LAYER[LCDIFV2_LAYER_COUNT];
  __IO uint32_t CLUT_LOAD;                         /**< LCDIFv2 CLUT load Register, offset: 0x400 */
} LCDIFV2_Type;

/* ----------------------------------------------------------------------------
   -- LCDIFV2 Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LCDIFV2_Register_Masks LCDIFV2 Register Masks
 * @{
 */

/*! @name CTRL - LCDIFv2 display control Register */
/*! @{ */

#define LCDIFV2_CTRL_INV_HS_MASK                 (0x1U)
#define LCDIFV2_CTRL_INV_HS_SHIFT                (0U)
/*! INV_HS - Invert Horizontal synchronization signal
 *  0b0..HSYNC signal not inverted (active HIGH)
 *  0b1..Invert HSYNC signal (active LOW)
 */
#define LCDIFV2_CTRL_INV_HS(x)                   (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_INV_HS_SHIFT)) & LCDIFV2_CTRL_INV_HS_MASK)

#define LCDIFV2_CTRL_INV_VS_MASK                 (0x2U)
#define LCDIFV2_CTRL_INV_VS_SHIFT                (1U)
/*! INV_VS - Invert Vertical synchronization signal
 *  0b0..VSYNC signal not inverted (active HIGH)
 *  0b1..Invert VSYNC signal (active LOW)
 */
#define LCDIFV2_CTRL_INV_VS(x)                   (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_INV_VS_SHIFT)) & LCDIFV2_CTRL_INV_VS_MASK)

#define LCDIFV2_CTRL_INV_DE_MASK                 (0x4U)
#define LCDIFV2_CTRL_INV_DE_SHIFT                (2U)
/*! INV_DE - Invert Data Enable polarity
 *  0b0..Data enable is active high
 *  0b1..Data enable is active low
 */
#define LCDIFV2_CTRL_INV_DE(x)                   (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_INV_DE_SHIFT)) & LCDIFV2_CTRL_INV_DE_MASK)

#define LCDIFV2_CTRL_INV_PXCK_MASK               (0x8U)
#define LCDIFV2_CTRL_INV_PXCK_SHIFT              (3U)
/*! INV_PXCK - Polarity change of Pixel Clock
 *  0b0..Display samples data on the falling edge
 *  0b1..Display samples data on the rising edge
 */
#define LCDIFV2_CTRL_INV_PXCK(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_INV_PXCK_SHIFT)) & LCDIFV2_CTRL_INV_PXCK_MASK)

#define LCDIFV2_CTRL_NEG_MASK                    (0x10U)
#define LCDIFV2_CTRL_NEG_SHIFT                   (4U)
/*! NEG - Indicates if value at the output (pixel data output) needs to be negated
 *  0b0..Output is to remain same
 *  0b1..Output to be negated
 */
#define LCDIFV2_CTRL_NEG(x)                      (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_NEG_SHIFT)) & LCDIFV2_CTRL_NEG_MASK)

#define LCDIFV2_CTRL_SW_RESET_MASK               (0x80000000U)
#define LCDIFV2_CTRL_SW_RESET_SHIFT              (31U)
/*! SW_RESET - Software Reset
 *  0b0..No action
 *  0b1..All LCDIFv2 internal registers are forced into their reset state. User registers are not affected
 */
#define LCDIFV2_CTRL_SW_RESET(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_SW_RESET_SHIFT)) & LCDIFV2_CTRL_SW_RESET_MASK)
/*! @} */

/*! @name CTRL_SET - LCDIFv2 display control Register */
/*! @{ */

#define LCDIFV2_CTRL_SET_INV_HS_MASK             (0x1U)
#define LCDIFV2_CTRL_SET_INV_HS_SHIFT            (0U)
/*! INV_HS - Invert Horizontal synchronization signal */
#define LCDIFV2_CTRL_SET_INV_HS(x)               (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_SET_INV_HS_SHIFT)) & LCDIFV2_CTRL_SET_INV_HS_MASK)

#define LCDIFV2_CTRL_SET_INV_VS_MASK             (0x2U)
#define LCDIFV2_CTRL_SET_INV_VS_SHIFT            (1U)
/*! INV_VS - Invert Vertical synchronization signal */
#define LCDIFV2_CTRL_SET_INV_VS(x)               (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_SET_INV_VS_SHIFT)) & LCDIFV2_CTRL_SET_INV_VS_MASK)

#define LCDIFV2_CTRL_SET_INV_DE_MASK             (0x4U)
#define LCDIFV2_CTRL_SET_INV_DE_SHIFT            (2U)
/*! INV_DE - Invert Data Enable polarity */
#define LCDIFV2_CTRL_SET_INV_DE(x)               (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_SET_INV_DE_SHIFT)) & LCDIFV2_CTRL_SET_INV_DE_MASK)

#define LCDIFV2_CTRL_SET_INV_PXCK_MASK           (0x8U)
#define LCDIFV2_CTRL_SET_INV_PXCK_SHIFT          (3U)
/*! INV_PXCK - Polarity change of Pixel Clock */
#define LCDIFV2_CTRL_SET_INV_PXCK(x)             (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_SET_INV_PXCK_SHIFT)) & LCDIFV2_CTRL_SET_INV_PXCK_MASK)

#define LCDIFV2_CTRL_SET_NEG_MASK                (0x10U)
#define LCDIFV2_CTRL_SET_NEG_SHIFT               (4U)
/*! NEG - Indicates if value at the output (pixel data output) needs to be negated */
#define LCDIFV2_CTRL_SET_NEG(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_SET_NEG_SHIFT)) & LCDIFV2_CTRL_SET_NEG_MASK)

#define LCDIFV2_CTRL_SET_SW_RESET_MASK           (0x80000000U)
#define LCDIFV2_CTRL_SET_SW_RESET_SHIFT          (31U)
/*! SW_RESET - Software Reset */
#define LCDIFV2_CTRL_SET_SW_RESET(x)             (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_SET_SW_RESET_SHIFT)) & LCDIFV2_CTRL_SET_SW_RESET_MASK)
/*! @} */

/*! @name CTRL_CLR - LCDIFv2 display control Register */
/*! @{ */

#define LCDIFV2_CTRL_CLR_INV_HS_MASK             (0x1U)
#define LCDIFV2_CTRL_CLR_INV_HS_SHIFT            (0U)
/*! INV_HS - Invert Horizontal synchronization signal */
#define LCDIFV2_CTRL_CLR_INV_HS(x)               (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_CLR_INV_HS_SHIFT)) & LCDIFV2_CTRL_CLR_INV_HS_MASK)

#define LCDIFV2_CTRL_CLR_INV_VS_MASK             (0x2U)
#define LCDIFV2_CTRL_CLR_INV_VS_SHIFT            (1U)
/*! INV_VS - Invert Vertical synchronization signal */
#define LCDIFV2_CTRL_CLR_INV_VS(x)               (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_CLR_INV_VS_SHIFT)) & LCDIFV2_CTRL_CLR_INV_VS_MASK)

#define LCDIFV2_CTRL_CLR_INV_DE_MASK             (0x4U)
#define LCDIFV2_CTRL_CLR_INV_DE_SHIFT            (2U)
/*! INV_DE - Invert Data Enable polarity */
#define LCDIFV2_CTRL_CLR_INV_DE(x)               (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_CLR_INV_DE_SHIFT)) & LCDIFV2_CTRL_CLR_INV_DE_MASK)

#define LCDIFV2_CTRL_CLR_INV_PXCK_MASK           (0x8U)
#define LCDIFV2_CTRL_CLR_INV_PXCK_SHIFT          (3U)
/*! INV_PXCK - Polarity change of Pixel Clock */
#define LCDIFV2_CTRL_CLR_INV_PXCK(x)             (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_CLR_INV_PXCK_SHIFT)) & LCDIFV2_CTRL_CLR_INV_PXCK_MASK)

#define LCDIFV2_CTRL_CLR_NEG_MASK                (0x10U)
#define LCDIFV2_CTRL_CLR_NEG_SHIFT               (4U)
/*! NEG - Indicates if value at the output (pixel data output) needs to be negated */
#define LCDIFV2_CTRL_CLR_NEG(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_CLR_NEG_SHIFT)) & LCDIFV2_CTRL_CLR_NEG_MASK)

#define LCDIFV2_CTRL_CLR_SW_RESET_MASK           (0x80000000U)
#define LCDIFV2_CTRL_CLR_SW_RESET_SHIFT          (31U)
/*! SW_RESET - Software Reset */
#define LCDIFV2_CTRL_CLR_SW_RESET(x)             (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_CLR_SW_RESET_SHIFT)) & LCDIFV2_CTRL_CLR_SW_RESET_MASK)
/*! @} */

/*! @name CTRL_TOG - LCDIFv2 display control Register */
/*! @{ */

#define LCDIFV2_CTRL_TOG_INV_HS_MASK             (0x1U)
#define LCDIFV2_CTRL_TOG_INV_HS_SHIFT            (0U)
/*! INV_HS - Invert Horizontal synchronization signal */
#define LCDIFV2_CTRL_TOG_INV_HS(x)               (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_TOG_INV_HS_SHIFT)) & LCDIFV2_CTRL_TOG_INV_HS_MASK)

#define LCDIFV2_CTRL_TOG_INV_VS_MASK             (0x2U)
#define LCDIFV2_CTRL_TOG_INV_VS_SHIFT            (1U)
/*! INV_VS - Invert Vertical synchronization signal */
#define LCDIFV2_CTRL_TOG_INV_VS(x)               (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_TOG_INV_VS_SHIFT)) & LCDIFV2_CTRL_TOG_INV_VS_MASK)

#define LCDIFV2_CTRL_TOG_INV_DE_MASK             (0x4U)
#define LCDIFV2_CTRL_TOG_INV_DE_SHIFT            (2U)
/*! INV_DE - Invert Data Enable polarity */
#define LCDIFV2_CTRL_TOG_INV_DE(x)               (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_TOG_INV_DE_SHIFT)) & LCDIFV2_CTRL_TOG_INV_DE_MASK)

#define LCDIFV2_CTRL_TOG_INV_PXCK_MASK           (0x8U)
#define LCDIFV2_CTRL_TOG_INV_PXCK_SHIFT          (3U)
/*! INV_PXCK - Polarity change of Pixel Clock */
#define LCDIFV2_CTRL_TOG_INV_PXCK(x)             (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_TOG_INV_PXCK_SHIFT)) & LCDIFV2_CTRL_TOG_INV_PXCK_MASK)

#define LCDIFV2_CTRL_TOG_NEG_MASK                (0x10U)
#define LCDIFV2_CTRL_TOG_NEG_SHIFT               (4U)
/*! NEG - Indicates if value at the output (pixel data output) needs to be negated */
#define LCDIFV2_CTRL_TOG_NEG(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_TOG_NEG_SHIFT)) & LCDIFV2_CTRL_TOG_NEG_MASK)

#define LCDIFV2_CTRL_TOG_SW_RESET_MASK           (0x80000000U)
#define LCDIFV2_CTRL_TOG_SW_RESET_SHIFT          (31U)
/*! SW_RESET - Software Reset */
#define LCDIFV2_CTRL_TOG_SW_RESET(x)             (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRL_TOG_SW_RESET_SHIFT)) & LCDIFV2_CTRL_TOG_SW_RESET_MASK)
/*! @} */

/*! @name DISP_PARA - Display Parameter Register */
/*! @{ */

#define LCDIFV2_DISP_PARA_BGND_B_MASK            (0xFFU)
#define LCDIFV2_DISP_PARA_BGND_B_SHIFT           (0U)
/*! BGND_B - Blue component of the default color displayed in Test Mode 1. */
#define LCDIFV2_DISP_PARA_BGND_B(x)              (((uint32_t)(((uint32_t)(x)) << LCDIFV2_DISP_PARA_BGND_B_SHIFT)) & LCDIFV2_DISP_PARA_BGND_B_MASK)

#define LCDIFV2_DISP_PARA_BGND_G_MASK            (0xFF00U)
#define LCDIFV2_DISP_PARA_BGND_G_SHIFT           (8U)
/*! BGND_G - Green component of the default color displayed in Test Mode 1. */
#define LCDIFV2_DISP_PARA_BGND_G(x)              (((uint32_t)(((uint32_t)(x)) << LCDIFV2_DISP_PARA_BGND_G_SHIFT)) & LCDIFV2_DISP_PARA_BGND_G_MASK)

#define LCDIFV2_DISP_PARA_BGND_R_MASK            (0xFF0000U)
#define LCDIFV2_DISP_PARA_BGND_R_SHIFT           (16U)
/*! BGND_R - Red component of the default color displayed in Test Mode 1. */
#define LCDIFV2_DISP_PARA_BGND_R(x)              (((uint32_t)(((uint32_t)(x)) << LCDIFV2_DISP_PARA_BGND_R_SHIFT)) & LCDIFV2_DISP_PARA_BGND_R_MASK)

#define LCDIFV2_DISP_PARA_DISP_MODE_MASK         (0x3000000U)
#define LCDIFV2_DISP_PARA_DISP_MODE_SHIFT        (24U)
/*! DISP_MODE - LCDIFv2 operating mode
 *  0b00..Normal mode. Panel content controlled by layer configuration
 *  0b01..Test Mode1(BGND Color Display)
 *  0b10..Test Mode2(Column Color Bar)
 *  0b11..Test Mode3(Row Color Bar)
 */
#define LCDIFV2_DISP_PARA_DISP_MODE(x)           (((uint32_t)(((uint32_t)(x)) << LCDIFV2_DISP_PARA_DISP_MODE_SHIFT)) & LCDIFV2_DISP_PARA_DISP_MODE_MASK)

#define LCDIFV2_DISP_PARA_LINE_PATTERN_MASK      (0x1C000000U)
#define LCDIFV2_DISP_PARA_LINE_PATTERN_SHIFT     (26U)
/*! LINE_PATTERN - LCDIFv2 line output order
 *  0b000..RGB
 *  0b001..RBG
 *  0b010..GBR
 *  0b011..GRB
 *  0b100..BRG
 *  0b101..BGR
 */
#define LCDIFV2_DISP_PARA_LINE_PATTERN(x)        (((uint32_t)(((uint32_t)(x)) << LCDIFV2_DISP_PARA_LINE_PATTERN_SHIFT)) & LCDIFV2_DISP_PARA_LINE_PATTERN_MASK)

#define LCDIFV2_DISP_PARA_DISP_ON_MASK           (0x80000000U)
#define LCDIFV2_DISP_PARA_DISP_ON_SHIFT          (31U)
/*! DISP_ON - Display panel On/Off mode
 *  0b0..Display Off
 *  0b1..Display On
 */
#define LCDIFV2_DISP_PARA_DISP_ON(x)             (((uint32_t)(((uint32_t)(x)) << LCDIFV2_DISP_PARA_DISP_ON_SHIFT)) & LCDIFV2_DISP_PARA_DISP_ON_MASK)
/*! @} */

/*! @name DISP_SIZE - Display Size Register */
/*! @{ */

#define LCDIFV2_DISP_SIZE_DELTA_X_MASK           (0xFFFU)
#define LCDIFV2_DISP_SIZE_DELTA_X_SHIFT          (0U)
/*! DELTA_X - Sets the display size horizontal resolution in pixels */
#define LCDIFV2_DISP_SIZE_DELTA_X(x)             (((uint32_t)(((uint32_t)(x)) << LCDIFV2_DISP_SIZE_DELTA_X_SHIFT)) & LCDIFV2_DISP_SIZE_DELTA_X_MASK)

#define LCDIFV2_DISP_SIZE_DELTA_Y_MASK           (0xFFF0000U)
#define LCDIFV2_DISP_SIZE_DELTA_Y_SHIFT          (16U)
/*! DELTA_Y - Sets the display size vertical resolution in pixels */
#define LCDIFV2_DISP_SIZE_DELTA_Y(x)             (((uint32_t)(((uint32_t)(x)) << LCDIFV2_DISP_SIZE_DELTA_Y_SHIFT)) & LCDIFV2_DISP_SIZE_DELTA_Y_MASK)
/*! @} */

/*! @name HSYN_PARA - Horizontal Sync Parameter Register */
/*! @{ */

#define LCDIFV2_HSYN_PARA_FP_H_MASK              (0x1FFU)
#define LCDIFV2_HSYN_PARA_FP_H_SHIFT             (0U)
/*! FP_H - HSYNC front-porch pulse width (in pixel clock cycles). Pulse width has a minimum value of 1 */
#define LCDIFV2_HSYN_PARA_FP_H(x)                (((uint32_t)(((uint32_t)(x)) << LCDIFV2_HSYN_PARA_FP_H_SHIFT)) & LCDIFV2_HSYN_PARA_FP_H_MASK)

#define LCDIFV2_HSYN_PARA_PW_H_MASK              (0xFF800U)
#define LCDIFV2_HSYN_PARA_PW_H_SHIFT             (11U)
/*! PW_H - HSYNC active pulse width (in pixel clock cycles). Pulse width has a minimum value of 1 */
#define LCDIFV2_HSYN_PARA_PW_H(x)                (((uint32_t)(((uint32_t)(x)) << LCDIFV2_HSYN_PARA_PW_H_SHIFT)) & LCDIFV2_HSYN_PARA_PW_H_MASK)

#define LCDIFV2_HSYN_PARA_BP_H_MASK              (0x7FC00000U)
#define LCDIFV2_HSYN_PARA_BP_H_SHIFT             (22U)
/*! BP_H - HSYNC back-porch pulse width (in pixel clock cycles). Pulse width has a minimum value of 1 */
#define LCDIFV2_HSYN_PARA_BP_H(x)                (((uint32_t)(((uint32_t)(x)) << LCDIFV2_HSYN_PARA_BP_H_SHIFT)) & LCDIFV2_HSYN_PARA_BP_H_MASK)
/*! @} */

/*! @name VSYN_PARA - Vertical Sync Parameter Register */
/*! @{ */

#define LCDIFV2_VSYN_PARA_FP_V_MASK              (0x1FFU)
#define LCDIFV2_VSYN_PARA_FP_V_SHIFT             (0U)
/*! FP_V - VSYNC front-porch pulse width (in horizontal line cycles). Pulse width has a minimum value of 1 */
#define LCDIFV2_VSYN_PARA_FP_V(x)                (((uint32_t)(((uint32_t)(x)) << LCDIFV2_VSYN_PARA_FP_V_SHIFT)) & LCDIFV2_VSYN_PARA_FP_V_MASK)

#define LCDIFV2_VSYN_PARA_PW_V_MASK              (0xFF800U)
#define LCDIFV2_VSYN_PARA_PW_V_SHIFT             (11U)
/*! PW_V - VSYNC active pulse width (in horizontal line cycles). Pulse width has a minimum value of 1 */
#define LCDIFV2_VSYN_PARA_PW_V(x)                (((uint32_t)(((uint32_t)(x)) << LCDIFV2_VSYN_PARA_PW_V_SHIFT)) & LCDIFV2_VSYN_PARA_PW_V_MASK)

#define LCDIFV2_VSYN_PARA_BP_V_MASK              (0x7FC00000U)
#define LCDIFV2_VSYN_PARA_BP_V_SHIFT             (22U)
/*! BP_V - VSYNC back-porch pulse width (in horizontal line cycles). Pulse width has a minimum value of 1 */
#define LCDIFV2_VSYN_PARA_BP_V(x)                (((uint32_t)(((uint32_t)(x)) << LCDIFV2_VSYN_PARA_BP_V_SHIFT)) & LCDIFV2_VSYN_PARA_BP_V_MASK)
/*! @} */

/*! @name INT_STATUS - Interrupt Status Register for domain 0..Interrupt Status Register for domain 1 */
/*! @{ */

#define LCDIFV2_INT_STATUS_VSYNC_MASK            (0x1U)
#define LCDIFV2_INT_STATUS_VSYNC_SHIFT           (0U)
/*! VSYNC - Interrupt flag to indicate that the vertical synchronization phase(The beginning of a frame)
 *  0b0..VSYNC has not started
 *  0b1..VSYNC has started
 */
#define LCDIFV2_INT_STATUS_VSYNC(x)              (((uint32_t)(((uint32_t)(x)) << LCDIFV2_INT_STATUS_VSYNC_SHIFT)) & LCDIFV2_INT_STATUS_VSYNC_MASK)

#define LCDIFV2_INT_STATUS_UNDERRUN_MASK         (0x2U)
#define LCDIFV2_INT_STATUS_UNDERRUN_SHIFT        (1U)
/*! UNDERRUN - Interrupt flag to indicate the output buffer underrun condition
 *  0b0..Output buffer not underrun
 *  0b1..Output buffer underrun
 */
#define LCDIFV2_INT_STATUS_UNDERRUN(x)           (((uint32_t)(((uint32_t)(x)) << LCDIFV2_INT_STATUS_UNDERRUN_SHIFT)) & LCDIFV2_INT_STATUS_UNDERRUN_MASK)

#define LCDIFV2_INT_STATUS_VS_BLANK_MASK         (0x4U)
#define LCDIFV2_INT_STATUS_VS_BLANK_SHIFT        (2U)
/*! VS_BLANK - Interrupt flag to indicate vertical blanking period
 *  0b0..Vertical blanking period has not started
 *  0b1..Vertical blanking period has started
 */
#define LCDIFV2_INT_STATUS_VS_BLANK(x)           (((uint32_t)(((uint32_t)(x)) << LCDIFV2_INT_STATUS_VS_BLANK_SHIFT)) & LCDIFV2_INT_STATUS_VS_BLANK_MASK)

#define LCDIFV2_INT_STATUS_DMA_ERR_MASK          (0xFF00U)
#define LCDIFV2_INT_STATUS_DMA_ERR_SHIFT         (8U)
/*! DMA_ERR - Interrupt flag to indicate that which PLANE has Read Error on the AXI interface */
#define LCDIFV2_INT_STATUS_DMA_ERR(x)            (((uint32_t)(((uint32_t)(x)) << LCDIFV2_INT_STATUS_DMA_ERR_SHIFT)) & LCDIFV2_INT_STATUS_DMA_ERR_MASK)

#define LCDIFV2_INT_STATUS_DMA_DONE_MASK         (0xFF0000U)
#define LCDIFV2_INT_STATUS_DMA_DONE_SHIFT        (16U)
/*! DMA_DONE - Interrupt flag to indicate that which PLANE has fetched the last pixel from memory */
#define LCDIFV2_INT_STATUS_DMA_DONE(x)           (((uint32_t)(((uint32_t)(x)) << LCDIFV2_INT_STATUS_DMA_DONE_SHIFT)) & LCDIFV2_INT_STATUS_DMA_DONE_MASK)

#define LCDIFV2_INT_STATUS_FIFO_EMPTY_MASK       (0xFF000000U)
#define LCDIFV2_INT_STATUS_FIFO_EMPTY_SHIFT      (24U)
/*! FIFO_EMPTY - Interrupt flag to indicate that which FIFO in the pixel blending underflowed */
#define LCDIFV2_INT_STATUS_FIFO_EMPTY(x)         (((uint32_t)(((uint32_t)(x)) << LCDIFV2_INT_STATUS_FIFO_EMPTY_SHIFT)) & LCDIFV2_INT_STATUS_FIFO_EMPTY_MASK)
/*! @} */

/* The count of LCDIFV2_INT_STATUS */
#define LCDIFV2_INT_STATUS_COUNT                 (2U)

/*! @name INT_ENABLE - Interrupt Enable Register for domain 0..Interrupt Enable Register for domain 1 */
/*! @{ */

#define LCDIFV2_INT_ENABLE_VSYNC_EN_MASK         (0x1U)
#define LCDIFV2_INT_ENABLE_VSYNC_EN_SHIFT        (0U)
/*! VSYNC_EN - Enable Interrupt flag to indicate that the vertical synchronization phase(The beginning of a frame)
 *  0b0..VSYNC interrupt disable
 *  0b1..VSYNC interrupt enable
 */
#define LCDIFV2_INT_ENABLE_VSYNC_EN(x)           (((uint32_t)(((uint32_t)(x)) << LCDIFV2_INT_ENABLE_VSYNC_EN_SHIFT)) & LCDIFV2_INT_ENABLE_VSYNC_EN_MASK)

#define LCDIFV2_INT_ENABLE_UNDERRUN_EN_MASK      (0x2U)
#define LCDIFV2_INT_ENABLE_UNDERRUN_EN_SHIFT     (1U)
/*! UNDERRUN_EN - Enable Interrupt flag to indicate the output buffer underrun condition
 *  0b0..Output buffer underrun disable
 *  0b1..Output buffer underrun enable
 */
#define LCDIFV2_INT_ENABLE_UNDERRUN_EN(x)        (((uint32_t)(((uint32_t)(x)) << LCDIFV2_INT_ENABLE_UNDERRUN_EN_SHIFT)) & LCDIFV2_INT_ENABLE_UNDERRUN_EN_MASK)

#define LCDIFV2_INT_ENABLE_VS_BLANK_EN_MASK      (0x4U)
#define LCDIFV2_INT_ENABLE_VS_BLANK_EN_SHIFT     (2U)
/*! VS_BLANK_EN - Enable Interrupt flag to indicate vertical blanking period
 *  0b0..Vertical blanking start interrupt disable
 *  0b1..Vertical blanking start interrupt enable
 */
#define LCDIFV2_INT_ENABLE_VS_BLANK_EN(x)        (((uint32_t)(((uint32_t)(x)) << LCDIFV2_INT_ENABLE_VS_BLANK_EN_SHIFT)) & LCDIFV2_INT_ENABLE_VS_BLANK_EN_MASK)

#define LCDIFV2_INT_ENABLE_DMA_ERR_EN_MASK       (0xFF00U)
#define LCDIFV2_INT_ENABLE_DMA_ERR_EN_SHIFT      (8U)
/*! DMA_ERR_EN - Enable Interrupt flag to indicate that which PLANE has Read Error on the AXI interface */
#define LCDIFV2_INT_ENABLE_DMA_ERR_EN(x)         (((uint32_t)(((uint32_t)(x)) << LCDIFV2_INT_ENABLE_DMA_ERR_EN_SHIFT)) & LCDIFV2_INT_ENABLE_DMA_ERR_EN_MASK)

#define LCDIFV2_INT_ENABLE_DMA_DONE_EN_MASK      (0xFF0000U)
#define LCDIFV2_INT_ENABLE_DMA_DONE_EN_SHIFT     (16U)
/*! DMA_DONE_EN - Enable Interrupt flag to indicate that which PLANE has fetched the last pixel from memory */
#define LCDIFV2_INT_ENABLE_DMA_DONE_EN(x)        (((uint32_t)(((uint32_t)(x)) << LCDIFV2_INT_ENABLE_DMA_DONE_EN_SHIFT)) & LCDIFV2_INT_ENABLE_DMA_DONE_EN_MASK)

#define LCDIFV2_INT_ENABLE_FIFO_EMPTY_EN_MASK    (0xFF000000U)
#define LCDIFV2_INT_ENABLE_FIFO_EMPTY_EN_SHIFT   (24U)
/*! FIFO_EMPTY_EN - Enable Interrupt flag to indicate that which FIFO in the pixel blending underflowed */
#define LCDIFV2_INT_ENABLE_FIFO_EMPTY_EN(x)      (((uint32_t)(((uint32_t)(x)) << LCDIFV2_INT_ENABLE_FIFO_EMPTY_EN_SHIFT)) & LCDIFV2_INT_ENABLE_FIFO_EMPTY_EN_MASK)
/*! @} */

/* The count of LCDIFV2_INT_ENABLE */
#define LCDIFV2_INT_ENABLE_COUNT                 (2U)

/*! @name CTRLDESCL1 - Control Descriptor Layer 1 Register */
/*! @{ */

#define LCDIFV2_CTRLDESCL1_WIDTH_MASK            (0xFFFU)
#define LCDIFV2_CTRLDESCL1_WIDTH_SHIFT           (0U)
/*! WIDTH - Width of the layer in pixels */
#define LCDIFV2_CTRLDESCL1_WIDTH(x)              (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL1_WIDTH_SHIFT)) & LCDIFV2_CTRLDESCL1_WIDTH_MASK)

#define LCDIFV2_CTRLDESCL1_HEIGHT_MASK           (0xFFF0000U)
#define LCDIFV2_CTRLDESCL1_HEIGHT_SHIFT          (16U)
/*! HEIGHT - Height of the layer in pixels */
#define LCDIFV2_CTRLDESCL1_HEIGHT(x)             (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL1_HEIGHT_SHIFT)) & LCDIFV2_CTRLDESCL1_HEIGHT_MASK)
/*! @} */

/* The count of LCDIFV2_CTRLDESCL1 */
#define LCDIFV2_CTRLDESCL1_COUNT                 (8U)

/*! @name CTRLDESCL2 - Control Descriptor Layer 2 Register */
/*! @{ */

#define LCDIFV2_CTRLDESCL2_POSX_MASK             (0xFFFU)
#define LCDIFV2_CTRLDESCL2_POSX_SHIFT            (0U)
/*! POSX - POS X */
#define LCDIFV2_CTRLDESCL2_POSX(x)               (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL2_POSX_SHIFT)) & LCDIFV2_CTRLDESCL2_POSX_MASK)

#define LCDIFV2_CTRLDESCL2_POSY_MASK             (0xFFF0000U)
#define LCDIFV2_CTRLDESCL2_POSY_SHIFT            (16U)
/*! POSY - The vertical position of top row of the layer, where 0 is the top row of the panel, only
 *    positive values are below the top row of the panel
 */
#define LCDIFV2_CTRLDESCL2_POSY(x)               (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL2_POSY_SHIFT)) & LCDIFV2_CTRLDESCL2_POSY_MASK)
/*! @} */

/* The count of LCDIFV2_CTRLDESCL2 */
#define LCDIFV2_CTRLDESCL2_COUNT                 (8U)

/*! @name CTRLDESCL3 - Control Descriptor Layer 3 Register */
/*! @{ */

#define LCDIFV2_CTRLDESCL3_PITCH_MASK            (0xFFFFU)
#define LCDIFV2_CTRLDESCL3_PITCH_SHIFT           (0U)
/*! PITCH - Number of bytes between 2 vertically adjacent pixels in system memory. Byte granularity
 *    is supported, but SW should align to 64B boundry
 */
#define LCDIFV2_CTRLDESCL3_PITCH(x)              (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL3_PITCH_SHIFT)) & LCDIFV2_CTRLDESCL3_PITCH_MASK)
/*! @} */

/* The count of LCDIFV2_CTRLDESCL3 */
#define LCDIFV2_CTRLDESCL3_COUNT                 (8U)

/*! @name CTRLDESCL4 - Control Descriptor Layer 4 Register */
/*! @{ */

#define LCDIFV2_CTRLDESCL4_ADDR_MASK             (0xFFFFFFFFU)
#define LCDIFV2_CTRLDESCL4_ADDR_SHIFT            (0U)
/*! ADDR - Address of layer data in the memory. The address programmed should be 64-bit aligned */
#define LCDIFV2_CTRLDESCL4_ADDR(x)               (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL4_ADDR_SHIFT)) & LCDIFV2_CTRLDESCL4_ADDR_MASK)
/*! @} */

/* The count of LCDIFV2_CTRLDESCL4 */
#define LCDIFV2_CTRLDESCL4_COUNT                 (8U)

/*! @name CTRLDESCL5 - Control Descriptor Layer 5 Register */
/*! @{ */

#define LCDIFV2_CTRLDESCL5_AB_MODE_MASK          (0x3U)
#define LCDIFV2_CTRLDESCL5_AB_MODE_SHIFT         (0U)
/*! AB_MODE - Alpha Blending Mode
 *  0b00..No alpha Blending (The SAFETY_EN bit need set to 1)
 *  0b01..Blend with global ALPHA
 *  0b10..Blend with embedded ALPHA
 *  0b11..Blend with Porter Duff enable
 */
#define LCDIFV2_CTRLDESCL5_AB_MODE(x)            (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL5_AB_MODE_SHIFT)) & LCDIFV2_CTRLDESCL5_AB_MODE_MASK)

#define LCDIFV2_CTRLDESCL5_PD_FACTOR_MODE_MASK   (0x30U)
#define LCDIFV2_CTRLDESCL5_PD_FACTOR_MODE_SHIFT  (4U)
/*! PD_FACTOR_MODE - Porter Duff factor mode
 *  0b00..Using 1
 *  0b01..Using 0
 *  0b10..Using straight alpha
 *  0b11..Using inverse alpha
 */
#define LCDIFV2_CTRLDESCL5_PD_FACTOR_MODE(x)     (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL5_PD_FACTOR_MODE_SHIFT)) & LCDIFV2_CTRLDESCL5_PD_FACTOR_MODE_MASK)

#define LCDIFV2_CTRLDESCL5_PD_GLOBAL_ALPHA_MODE_MASK (0xC0U)
#define LCDIFV2_CTRLDESCL5_PD_GLOBAL_ALPHA_MODE_SHIFT (6U)
/*! PD_GLOBAL_ALPHA_MODE - Porter Duff global alpha mode
 *  0b00..Using global alpha
 *  0b01..Using local alpha
 *  0b10..Using scaled alpha
 *  0b11..Using scaled alpha
 */
#define LCDIFV2_CTRLDESCL5_PD_GLOBAL_ALPHA_MODE(x) (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL5_PD_GLOBAL_ALPHA_MODE_SHIFT)) & LCDIFV2_CTRLDESCL5_PD_GLOBAL_ALPHA_MODE_MASK)

#define LCDIFV2_CTRLDESCL5_PD_ALPHA_MODE_MASK    (0x100U)
#define LCDIFV2_CTRLDESCL5_PD_ALPHA_MODE_SHIFT   (8U)
/*! PD_ALPHA_MODE - Porter Duff alpha mode
 *  0b0..Straight mode for Porter Duff alpha
 *  0b1..Inversed mode for Porter Duff alpha
 */
#define LCDIFV2_CTRLDESCL5_PD_ALPHA_MODE(x)      (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL5_PD_ALPHA_MODE_SHIFT)) & LCDIFV2_CTRLDESCL5_PD_ALPHA_MODE_MASK)

#define LCDIFV2_CTRLDESCL5_PD_COLOR_MODE_MASK    (0x200U)
#define LCDIFV2_CTRLDESCL5_PD_COLOR_MODE_SHIFT   (9U)
/*! PD_COLOR_MODE - Porter Duff alpha mode
 *  0b0..Straight mode for Porter Duff color
 *  0b1..Inversed mode for Porter Duff color
 */
#define LCDIFV2_CTRLDESCL5_PD_COLOR_MODE(x)      (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL5_PD_COLOR_MODE_SHIFT)) & LCDIFV2_CTRLDESCL5_PD_COLOR_MODE_MASK)

#define LCDIFV2_CTRLDESCL5_YUV_FORMAT_MASK       (0xC000U)
#define LCDIFV2_CTRLDESCL5_YUV_FORMAT_SHIFT      (14U)
/*! YUV_FORMAT - The YUV422 input format selection
 *  0b00..The YVYU422 8bit sequence is U1,Y1,V1,Y2
 *  0b01..The YVYU422 8bit sequence is V1,Y1,U1,Y2
 *  0b10..The YVYU422 8bit sequence is Y1,U1,Y2,V1
 *  0b11..The YVYU422 8bit sequence is Y1,V1,Y2,U1
 */
#define LCDIFV2_CTRLDESCL5_YUV_FORMAT(x)         (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL5_YUV_FORMAT_SHIFT)) & LCDIFV2_CTRLDESCL5_YUV_FORMAT_MASK)

#define LCDIFV2_CTRLDESCL5_GLOBAL_ALPHA_MASK     (0xFF0000U)
#define LCDIFV2_CTRLDESCL5_GLOBAL_ALPHA_SHIFT    (16U)
/*! GLOBAL_ALPHA - Global Alpha */
#define LCDIFV2_CTRLDESCL5_GLOBAL_ALPHA(x)       (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL5_GLOBAL_ALPHA_SHIFT)) & LCDIFV2_CTRLDESCL5_GLOBAL_ALPHA_MASK)

#define LCDIFV2_CTRLDESCL5_BPP_MASK              (0xF000000U)
#define LCDIFV2_CTRLDESCL5_BPP_SHIFT             (24U)
/*! BPP - Layer encoding format (bit per pixel)
 *  0b0000..1 bpp
 *  0b0001..2 bpp
 *  0b0010..4 bpp
 *  0b0011..8 bpp
 *  0b0100..16 bpp (RGB565)
 *  0b0101..16 bpp (ARGB1555)
 *  0b0110..16 bpp (ARGB4444)
 *  0b0111..YCbCr422 (Only layer 0/1 can support this format)
 *  0b1000..24 bpp (RGB888)
 *  0b1001..32 bpp (ARGB8888)
 *  0b1010..32 bpp (ABGR8888)
 */
#define LCDIFV2_CTRLDESCL5_BPP(x)                (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL5_BPP_SHIFT)) & LCDIFV2_CTRLDESCL5_BPP_MASK)

#define LCDIFV2_CTRLDESCL5_SAFETY_EN_MASK        (0x10000000U)
#define LCDIFV2_CTRLDESCL5_SAFETY_EN_SHIFT       (28U)
/*! SAFETY_EN - Safety Mode Enable Bit
 *  0b0..Safety Mode is disabled
 *  0b1..Safety Mode is enabled for this layer
 */
#define LCDIFV2_CTRLDESCL5_SAFETY_EN(x)          (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL5_SAFETY_EN_SHIFT)) & LCDIFV2_CTRLDESCL5_SAFETY_EN_MASK)

#define LCDIFV2_CTRLDESCL5_SHADOW_LOAD_EN_MASK   (0x40000000U)
#define LCDIFV2_CTRLDESCL5_SHADOW_LOAD_EN_SHIFT  (30U)
/*! SHADOW_LOAD_EN - Shadow Load Enable */
#define LCDIFV2_CTRLDESCL5_SHADOW_LOAD_EN(x)     (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL5_SHADOW_LOAD_EN_SHIFT)) & LCDIFV2_CTRLDESCL5_SHADOW_LOAD_EN_MASK)

#define LCDIFV2_CTRLDESCL5_EN_MASK               (0x80000000U)
#define LCDIFV2_CTRLDESCL5_EN_SHIFT              (31U)
/*! EN - Enable the layer for DMA
 *  0b0..OFF
 *  0b1..ON
 */
#define LCDIFV2_CTRLDESCL5_EN(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL5_EN_SHIFT)) & LCDIFV2_CTRLDESCL5_EN_MASK)
/*! @} */

/* The count of LCDIFV2_CTRLDESCL5 */
#define LCDIFV2_CTRLDESCL5_COUNT                 (8U)

/*! @name CTRLDESCL6 - Control Descriptor Layer 6 Register */
/*! @{ */

#define LCDIFV2_CTRLDESCL6_BCLR_B_MASK           (0xFFU)
#define LCDIFV2_CTRLDESCL6_BCLR_B_SHIFT          (0U)
/*! BCLR_B - Background B component value */
#define LCDIFV2_CTRLDESCL6_BCLR_B(x)             (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL6_BCLR_B_SHIFT)) & LCDIFV2_CTRLDESCL6_BCLR_B_MASK)

#define LCDIFV2_CTRLDESCL6_BCLR_G_MASK           (0xFF00U)
#define LCDIFV2_CTRLDESCL6_BCLR_G_SHIFT          (8U)
/*! BCLR_G - Background G component value */
#define LCDIFV2_CTRLDESCL6_BCLR_G(x)             (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL6_BCLR_G_SHIFT)) & LCDIFV2_CTRLDESCL6_BCLR_G_MASK)

#define LCDIFV2_CTRLDESCL6_BCLR_R_MASK           (0xFF0000U)
#define LCDIFV2_CTRLDESCL6_BCLR_R_SHIFT          (16U)
/*! BCLR_R - Background R component value */
#define LCDIFV2_CTRLDESCL6_BCLR_R(x)             (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CTRLDESCL6_BCLR_R_SHIFT)) & LCDIFV2_CTRLDESCL6_BCLR_R_MASK)
/*! @} */

/* The count of LCDIFV2_CTRLDESCL6 */
#define LCDIFV2_CTRLDESCL6_COUNT                 (8U)

/*! @name CSC_COEF0 - Color Space Conversion Coefficient Register 0 */
/*! @{ */

#define LCDIFV2_CSC_COEF0_Y_OFFSET_MASK          (0x1FFU)
#define LCDIFV2_CSC_COEF0_Y_OFFSET_SHIFT         (0U)
/*! Y_OFFSET - Y OFFSET */
#define LCDIFV2_CSC_COEF0_Y_OFFSET(x)            (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CSC_COEF0_Y_OFFSET_SHIFT)) & LCDIFV2_CSC_COEF0_Y_OFFSET_MASK)

#define LCDIFV2_CSC_COEF0_UV_OFFSET_MASK         (0x3FE00U)
#define LCDIFV2_CSC_COEF0_UV_OFFSET_SHIFT        (9U)
/*! UV_OFFSET - UV OFFSET */
#define LCDIFV2_CSC_COEF0_UV_OFFSET(x)           (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CSC_COEF0_UV_OFFSET_SHIFT)) & LCDIFV2_CSC_COEF0_UV_OFFSET_MASK)

#define LCDIFV2_CSC_COEF0_C0_MASK                (0x1FFC0000U)
#define LCDIFV2_CSC_COEF0_C0_SHIFT               (18U)
/*! C0 - Two's compliment Y multiplier coefficient. YUV=0x100 (1.000) YCbCr=0x12A (1.164) */
#define LCDIFV2_CSC_COEF0_C0(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CSC_COEF0_C0_SHIFT)) & LCDIFV2_CSC_COEF0_C0_MASK)

#define LCDIFV2_CSC_COEF0_ENABLE_MASK            (0x40000000U)
#define LCDIFV2_CSC_COEF0_ENABLE_SHIFT           (30U)
/*! ENABLE - Enable the CSC unit in the LCDIFv2 plane data path
 *  0b0..The CSC is bypassed and the input pixels are RGB data already
 *  0b1..The CSC is enabled and the pixels will be converted to RGB data
 */
#define LCDIFV2_CSC_COEF0_ENABLE(x)              (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CSC_COEF0_ENABLE_SHIFT)) & LCDIFV2_CSC_COEF0_ENABLE_MASK)

#define LCDIFV2_CSC_COEF0_YCBCR_MODE_MASK        (0x80000000U)
#define LCDIFV2_CSC_COEF0_YCBCR_MODE_SHIFT       (31U)
/*! YCBCR_MODE - This bit changes the behavior when performing U/V converting
 *  0b0..Converting YUV to RGB data
 *  0b1..Converting YCbCr to RGB data
 */
#define LCDIFV2_CSC_COEF0_YCBCR_MODE(x)          (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CSC_COEF0_YCBCR_MODE_SHIFT)) & LCDIFV2_CSC_COEF0_YCBCR_MODE_MASK)
/*! @} */

/* The count of LCDIFV2_CSC_COEF0 */
#define LCDIFV2_CSC_COEF0_COUNT                  (8U)

/*! @name CSC_COEF1 - Color Space Conversion Coefficient Register 1 */
/*! @{ */

#define LCDIFV2_CSC_COEF1_C4_MASK                (0x7FFU)
#define LCDIFV2_CSC_COEF1_C4_SHIFT               (0U)
/*! C4 - Two's compliment Blue U/Cb multiplier coefficient. YUV=0x208 (2.032) YCbCr=0x204 (2.017) */
#define LCDIFV2_CSC_COEF1_C4(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CSC_COEF1_C4_SHIFT)) & LCDIFV2_CSC_COEF1_C4_MASK)

#define LCDIFV2_CSC_COEF1_C1_MASK                (0x7FF0000U)
#define LCDIFV2_CSC_COEF1_C1_SHIFT               (16U)
/*! C1 - Two's compliment Red V/Cr multiplier coefficient. YUV=0x123 (1.140) YCbCr=0x198 (1.596) */
#define LCDIFV2_CSC_COEF1_C1(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CSC_COEF1_C1_SHIFT)) & LCDIFV2_CSC_COEF1_C1_MASK)
/*! @} */

/* The count of LCDIFV2_CSC_COEF1 */
#define LCDIFV2_CSC_COEF1_COUNT                  (8U)

/*! @name CSC_COEF2 - Color Space Conversion Coefficient Register 2 */
/*! @{ */

#define LCDIFV2_CSC_COEF2_C3_MASK                (0x7FFU)
#define LCDIFV2_CSC_COEF2_C3_SHIFT               (0U)
/*! C3 - Two's compliment Green U/Cb multiplier coefficient. YUV=0x79C (-0.394) YCbCr=0x79C (-0.392) */
#define LCDIFV2_CSC_COEF2_C3(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CSC_COEF2_C3_SHIFT)) & LCDIFV2_CSC_COEF2_C3_MASK)

#define LCDIFV2_CSC_COEF2_C2_MASK                (0x7FF0000U)
#define LCDIFV2_CSC_COEF2_C2_SHIFT               (16U)
/*! C2 - Two's compliment Green V/Cr multiplier coefficient. YUV=0x76B (-0.581) YCbCr=0x730 (-0.813) */
#define LCDIFV2_CSC_COEF2_C2(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CSC_COEF2_C2_SHIFT)) & LCDIFV2_CSC_COEF2_C2_MASK)
/*! @} */

/* The count of LCDIFV2_CSC_COEF2 */
#define LCDIFV2_CSC_COEF2_COUNT                  (8U)

/*! @name CLUT_LOAD - LCDIFv2 CLUT load Register */
/*! @{ */

#define LCDIFV2_CLUT_LOAD_CLUT_UPDATE_EN_MASK    (0x1U)
#define LCDIFV2_CLUT_LOAD_CLUT_UPDATE_EN_SHIFT   (0U)
/*! CLUT_UPDATE_EN - CLUT Update Enable */
#define LCDIFV2_CLUT_LOAD_CLUT_UPDATE_EN(x)      (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CLUT_LOAD_CLUT_UPDATE_EN_SHIFT)) & LCDIFV2_CLUT_LOAD_CLUT_UPDATE_EN_MASK)

#define LCDIFV2_CLUT_LOAD_SEL_CLUT_NUM_MASK      (0x70U)
#define LCDIFV2_CLUT_LOAD_SEL_CLUT_NUM_SHIFT     (4U)
/*! SEL_CLUT_NUM - Selected CLUT Number */
#define LCDIFV2_CLUT_LOAD_SEL_CLUT_NUM(x)        (((uint32_t)(((uint32_t)(x)) << LCDIFV2_CLUT_LOAD_SEL_CLUT_NUM_SHIFT)) & LCDIFV2_CLUT_LOAD_SEL_CLUT_NUM_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group LCDIFV2_Register_Masks */


/*!
 * @}
 */ /* end of group LCDIFV2_Peripheral_Access_Layer */


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


#endif  /* PERI_LCDIFV2_H_ */

