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
**         CMSIS Peripheral Access Layer for CSI
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
 * @file PERI_CSI.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for CSI
 *
 * CMSIS Peripheral Access Layer for CSI
 */

#if !defined(PERI_CSI_H_)
#define PERI_CSI_H_                              /**< Symbol preventing repeated inclusion */

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
   -- CSI Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CSI_Peripheral_Access_Layer CSI Peripheral Access Layer
 * @{
 */

/** CSI - Size of Registers Arrays */
#define CSI_CR_COUNT                              256u

/** CSI - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR1;                               /**< CSI Control Register 1, offset: 0x0 */
  __IO uint32_t CR2;                               /**< CSI Control Register 2, offset: 0x4 */
  __IO uint32_t CR3;                               /**< CSI Control Register 3, offset: 0x8 */
  __I  uint32_t STATFIFO;                          /**< CSI Statistic FIFO Register, offset: 0xC */
  __I  uint32_t RFIFO;                             /**< CSI RX FIFO Register, offset: 0x10 */
  __IO uint32_t RXCNT;                             /**< CSI RX Count Register, offset: 0x14 */
  __IO uint32_t SR;                                /**< CSI Status Register, offset: 0x18 */
       uint8_t RESERVED_0[4];
  __IO uint32_t DMASA_STATFIFO;                    /**< CSI DMA Start Address Register - for STATFIFO, offset: 0x20 */
  __IO uint32_t DMATS_STATFIFO;                    /**< CSI DMA Transfer Size Register - for STATFIFO, offset: 0x24 */
  __IO uint32_t DMASA_FB1;                         /**< CSI DMA Start Address Register - for Frame Buffer1, offset: 0x28 */
  __IO uint32_t DMASA_FB2;                         /**< CSI DMA Transfer Size Register - for Frame Buffer2, offset: 0x2C */
  __IO uint32_t FBUF_PARA;                         /**< CSI Frame Buffer Parameter Register, offset: 0x30 */
  __IO uint32_t IMAG_PARA;                         /**< CSI Image Parameter Register, offset: 0x34 */
       uint8_t RESERVED_1[16];
  __IO uint32_t CR18;                              /**< CSI Control Register 18, offset: 0x48 */
  __IO uint32_t CR19;                              /**< CSI Control Register 19, offset: 0x4C */
  __IO uint32_t CR20;                              /**< CSI Control Register 20, offset: 0x50 */
  __IO uint32_t CR[CSI_CR_COUNT];                  /**< CSI Control Register, array offset: 0x54, array step: 0x4 */
} CSI_Type;

/* ----------------------------------------------------------------------------
   -- CSI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CSI_Register_Masks CSI Register Masks
 * @{
 */

/*! @name CR1 - CSI Control Register 1 */
/*! @{ */

#define CSI_CR1_PIXEL_BIT_MASK                   (0x1U)
#define CSI_CR1_PIXEL_BIT_SHIFT                  (0U)
/*! PIXEL_BIT
 *  0b0..8-bit data for each pixel
 *  0b1..10-bit data for each pixel
 */
#define CSI_CR1_PIXEL_BIT(x)                     (((uint32_t)(((uint32_t)(x)) << CSI_CR1_PIXEL_BIT_SHIFT)) & CSI_CR1_PIXEL_BIT_MASK)

#define CSI_CR1_REDGE_MASK                       (0x2U)
#define CSI_CR1_REDGE_SHIFT                      (1U)
/*! REDGE
 *  0b0..Pixel data is latched at the falling edge of CSI_PIXCLK
 *  0b1..Pixel data is latched at the rising edge of CSI_PIXCLK
 */
#define CSI_CR1_REDGE(x)                         (((uint32_t)(((uint32_t)(x)) << CSI_CR1_REDGE_SHIFT)) & CSI_CR1_REDGE_MASK)

#define CSI_CR1_INV_PCLK_MASK                    (0x4U)
#define CSI_CR1_INV_PCLK_SHIFT                   (2U)
/*! INV_PCLK
 *  0b0..CSI_PIXCLK is directly applied to internal circuitry
 *  0b1..CSI_PIXCLK is inverted before applied to internal circuitry
 */
#define CSI_CR1_INV_PCLK(x)                      (((uint32_t)(((uint32_t)(x)) << CSI_CR1_INV_PCLK_SHIFT)) & CSI_CR1_INV_PCLK_MASK)

#define CSI_CR1_INV_DATA_MASK                    (0x8U)
#define CSI_CR1_INV_DATA_SHIFT                   (3U)
/*! INV_DATA
 *  0b0..CSI_D[7:0] data lines are directly applied to internal circuitry
 *  0b1..CSI_D[7:0] data lines are inverted before applied to internal circuitry
 */
#define CSI_CR1_INV_DATA(x)                      (((uint32_t)(((uint32_t)(x)) << CSI_CR1_INV_DATA_SHIFT)) & CSI_CR1_INV_DATA_MASK)

#define CSI_CR1_GCLK_MODE_MASK                   (0x10U)
#define CSI_CR1_GCLK_MODE_SHIFT                  (4U)
/*! GCLK_MODE
 *  0b0..Non-gated clock mode. All incoming pixel clocks are valid. HSYNC is ignored.
 *  0b1..Gated clock mode. Pixel clock signal is valid only when HSYNC is active.
 */
#define CSI_CR1_GCLK_MODE(x)                     (((uint32_t)(((uint32_t)(x)) << CSI_CR1_GCLK_MODE_SHIFT)) & CSI_CR1_GCLK_MODE_MASK)

#define CSI_CR1_CLR_RXFIFO_MASK                  (0x20U)
#define CSI_CR1_CLR_RXFIFO_SHIFT                 (5U)
#define CSI_CR1_CLR_RXFIFO(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CR1_CLR_RXFIFO_SHIFT)) & CSI_CR1_CLR_RXFIFO_MASK)

#define CSI_CR1_CLR_STATFIFO_MASK                (0x40U)
#define CSI_CR1_CLR_STATFIFO_SHIFT               (6U)
#define CSI_CR1_CLR_STATFIFO(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CR1_CLR_STATFIFO_SHIFT)) & CSI_CR1_CLR_STATFIFO_MASK)

#define CSI_CR1_PACK_DIR_MASK                    (0x80U)
#define CSI_CR1_PACK_DIR_SHIFT                   (7U)
/*! PACK_DIR
 *  0b0..Pack from LSB first. For image data, 0x11, 0x22, 0x33, 0x44, it will appear as 0x44332211 in RX FIFO. For
 *       stat data, 0xAAAA, 0xBBBB, it will appear as 0xBBBBAAAA in STAT FIFO.
 *  0b1..Pack from MSB first. For image data, 0x11, 0x22, 0x33, 0x44, it will appear as 0x11223344 in RX FIFO. For
 *       stat data, 0xAAAA, 0xBBBB, it will appear as 0xAAAABBBB in STAT FIFO.
 */
#define CSI_CR1_PACK_DIR(x)                      (((uint32_t)(((uint32_t)(x)) << CSI_CR1_PACK_DIR_SHIFT)) & CSI_CR1_PACK_DIR_MASK)

#define CSI_CR1_FCC_MASK                         (0x100U)
#define CSI_CR1_FCC_SHIFT                        (8U)
/*! FCC
 *  0b0..Asynchronous FIFO clear is selected.
 *  0b1..Synchronous FIFO clear is selected.
 */
#define CSI_CR1_FCC(x)                           (((uint32_t)(((uint32_t)(x)) << CSI_CR1_FCC_SHIFT)) & CSI_CR1_FCC_MASK)

#define CSI_CR1_CCIR_EN_MASK                     (0x400U)
#define CSI_CR1_CCIR_EN_SHIFT                    (10U)
/*! CCIR_EN
 *  0b0..Traditional interface is selected.
 *  0b1..BT.656 interface is selected.
 */
#define CSI_CR1_CCIR_EN(x)                       (((uint32_t)(((uint32_t)(x)) << CSI_CR1_CCIR_EN_SHIFT)) & CSI_CR1_CCIR_EN_MASK)

#define CSI_CR1_HSYNC_POL_MASK                   (0x800U)
#define CSI_CR1_HSYNC_POL_SHIFT                  (11U)
/*! HSYNC_POL
 *  0b0..HSYNC is active low
 *  0b1..HSYNC is active high
 */
#define CSI_CR1_HSYNC_POL(x)                     (((uint32_t)(((uint32_t)(x)) << CSI_CR1_HSYNC_POL_SHIFT)) & CSI_CR1_HSYNC_POL_MASK)

#define CSI_CR1_HISTOGRAM_CALC_DONE_IE_MASK      (0x1000U)
#define CSI_CR1_HISTOGRAM_CALC_DONE_IE_SHIFT     (12U)
/*! HISTOGRAM_CALC_DONE_IE
 *  0b0..Histogram done interrupt disable
 *  0b1..Histogram done interrupt enable
 */
#define CSI_CR1_HISTOGRAM_CALC_DONE_IE(x)        (((uint32_t)(((uint32_t)(x)) << CSI_CR1_HISTOGRAM_CALC_DONE_IE_SHIFT)) & CSI_CR1_HISTOGRAM_CALC_DONE_IE_MASK)

#define CSI_CR1_SOF_INTEN_MASK                   (0x10000U)
#define CSI_CR1_SOF_INTEN_SHIFT                  (16U)
/*! SOF_INTEN
 *  0b0..SOF interrupt disable
 *  0b1..SOF interrupt enable
 */
#define CSI_CR1_SOF_INTEN(x)                     (((uint32_t)(((uint32_t)(x)) << CSI_CR1_SOF_INTEN_SHIFT)) & CSI_CR1_SOF_INTEN_MASK)

#define CSI_CR1_SOF_POL_MASK                     (0x20000U)
#define CSI_CR1_SOF_POL_SHIFT                    (17U)
/*! SOF_POL
 *  0b0..SOF interrupt is generated on SOF falling edge
 *  0b1..SOF interrupt is generated on SOF rising edge
 */
#define CSI_CR1_SOF_POL(x)                       (((uint32_t)(((uint32_t)(x)) << CSI_CR1_SOF_POL_SHIFT)) & CSI_CR1_SOF_POL_MASK)

#define CSI_CR1_RXFF_INTEN_MASK                  (0x40000U)
#define CSI_CR1_RXFF_INTEN_SHIFT                 (18U)
/*! RXFF_INTEN
 *  0b0..RxFIFO full interrupt disable
 *  0b1..RxFIFO full interrupt enable
 */
#define CSI_CR1_RXFF_INTEN(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CR1_RXFF_INTEN_SHIFT)) & CSI_CR1_RXFF_INTEN_MASK)

#define CSI_CR1_FB1_DMA_DONE_INTEN_MASK          (0x80000U)
#define CSI_CR1_FB1_DMA_DONE_INTEN_SHIFT         (19U)
/*! FB1_DMA_DONE_INTEN
 *  0b0..Frame Buffer1 DMA Transfer Done interrupt disable
 *  0b1..Frame Buffer1 DMA Transfer Done interrupt enable
 */
#define CSI_CR1_FB1_DMA_DONE_INTEN(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CR1_FB1_DMA_DONE_INTEN_SHIFT)) & CSI_CR1_FB1_DMA_DONE_INTEN_MASK)

#define CSI_CR1_FB2_DMA_DONE_INTEN_MASK          (0x100000U)
#define CSI_CR1_FB2_DMA_DONE_INTEN_SHIFT         (20U)
/*! FB2_DMA_DONE_INTEN
 *  0b0..Frame Buffer2 DMA Transfer Done interrupt disable
 *  0b1..Frame Buffer2 DMA Transfer Done interrupt enable
 */
#define CSI_CR1_FB2_DMA_DONE_INTEN(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CR1_FB2_DMA_DONE_INTEN_SHIFT)) & CSI_CR1_FB2_DMA_DONE_INTEN_MASK)

#define CSI_CR1_STATFF_INTEN_MASK                (0x200000U)
#define CSI_CR1_STATFF_INTEN_SHIFT               (21U)
/*! STATFF_INTEN
 *  0b0..STATFIFO full interrupt disable
 *  0b1..STATFIFO full interrupt enable
 */
#define CSI_CR1_STATFF_INTEN(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CR1_STATFF_INTEN_SHIFT)) & CSI_CR1_STATFF_INTEN_MASK)

#define CSI_CR1_SFF_DMA_DONE_INTEN_MASK          (0x400000U)
#define CSI_CR1_SFF_DMA_DONE_INTEN_SHIFT         (22U)
/*! SFF_DMA_DONE_INTEN
 *  0b0..STATFIFO DMA Transfer Done interrupt disable
 *  0b1..STATFIFO DMA Transfer Done interrupt enable
 */
#define CSI_CR1_SFF_DMA_DONE_INTEN(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CR1_SFF_DMA_DONE_INTEN_SHIFT)) & CSI_CR1_SFF_DMA_DONE_INTEN_MASK)

#define CSI_CR1_RF_OR_INTEN_MASK                 (0x1000000U)
#define CSI_CR1_RF_OR_INTEN_SHIFT                (24U)
/*! RF_OR_INTEN
 *  0b0..RxFIFO overrun interrupt is disabled
 *  0b1..RxFIFO overrun interrupt is enabled
 */
#define CSI_CR1_RF_OR_INTEN(x)                   (((uint32_t)(((uint32_t)(x)) << CSI_CR1_RF_OR_INTEN_SHIFT)) & CSI_CR1_RF_OR_INTEN_MASK)

#define CSI_CR1_SF_OR_INTEN_MASK                 (0x2000000U)
#define CSI_CR1_SF_OR_INTEN_SHIFT                (25U)
/*! SF_OR_INTEN
 *  0b0..STATFIFO overrun interrupt is disabled
 *  0b1..STATFIFO overrun interrupt is enabled
 */
#define CSI_CR1_SF_OR_INTEN(x)                   (((uint32_t)(((uint32_t)(x)) << CSI_CR1_SF_OR_INTEN_SHIFT)) & CSI_CR1_SF_OR_INTEN_MASK)

#define CSI_CR1_COF_INT_EN_MASK                  (0x4000000U)
#define CSI_CR1_COF_INT_EN_SHIFT                 (26U)
/*! COF_INT_EN
 *  0b0..COF interrupt is disabled
 *  0b1..COF interrupt is enabled
 */
#define CSI_CR1_COF_INT_EN(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CR1_COF_INT_EN_SHIFT)) & CSI_CR1_COF_INT_EN_MASK)

#define CSI_CR1_VIDEO_MODE_MASK                  (0x8000000U)
#define CSI_CR1_VIDEO_MODE_SHIFT                 (27U)
/*! VIDEO_MODE
 *  0b0..Progressive mode is selected
 *  0b1..Interlace mode is selected
 */
#define CSI_CR1_VIDEO_MODE(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CR1_VIDEO_MODE_SHIFT)) & CSI_CR1_VIDEO_MODE_MASK)

#define CSI_CR1_EOF_INT_EN_MASK                  (0x20000000U)
#define CSI_CR1_EOF_INT_EN_SHIFT                 (29U)
/*! EOF_INT_EN
 *  0b0..EOF interrupt is disabled.
 *  0b1..EOF interrupt is generated when RX count value is reached.
 */
#define CSI_CR1_EOF_INT_EN(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CR1_EOF_INT_EN_SHIFT)) & CSI_CR1_EOF_INT_EN_MASK)

#define CSI_CR1_EXT_VSYNC_MASK                   (0x40000000U)
#define CSI_CR1_EXT_VSYNC_SHIFT                  (30U)
/*! EXT_VSYNC
 *  0b0..Internal VSYNC mode
 *  0b1..External VSYNC mode
 */
#define CSI_CR1_EXT_VSYNC(x)                     (((uint32_t)(((uint32_t)(x)) << CSI_CR1_EXT_VSYNC_SHIFT)) & CSI_CR1_EXT_VSYNC_MASK)

#define CSI_CR1_SWAP16_EN_MASK                   (0x80000000U)
#define CSI_CR1_SWAP16_EN_SHIFT                  (31U)
/*! SWAP16_EN
 *  0b0..Disable swapping
 *  0b1..Enable swapping
 */
#define CSI_CR1_SWAP16_EN(x)                     (((uint32_t)(((uint32_t)(x)) << CSI_CR1_SWAP16_EN_SHIFT)) & CSI_CR1_SWAP16_EN_MASK)
/*! @} */

/*! @name CR2 - CSI Control Register 2 */
/*! @{ */

#define CSI_CR2_HSC_MASK                         (0xFFU)
#define CSI_CR2_HSC_SHIFT                        (0U)
/*! HSC
 *  0b00000000-0b11111111..Number of pixels to skip minus 1
 */
#define CSI_CR2_HSC(x)                           (((uint32_t)(((uint32_t)(x)) << CSI_CR2_HSC_SHIFT)) & CSI_CR2_HSC_MASK)

#define CSI_CR2_VSC_MASK                         (0xFF00U)
#define CSI_CR2_VSC_SHIFT                        (8U)
/*! VSC
 *  0b00000000-0b11111111..Number of rows to skip minus 1
 */
#define CSI_CR2_VSC(x)                           (((uint32_t)(((uint32_t)(x)) << CSI_CR2_VSC_SHIFT)) & CSI_CR2_VSC_MASK)

#define CSI_CR2_LVRM_MASK                        (0x70000U)
#define CSI_CR2_LVRM_SHIFT                       (16U)
/*! LVRM
 *  0b000..512 x 384
 *  0b001..448 x 336
 *  0b010..384 x 288
 *  0b011..384 x 256
 *  0b100..320 x 240
 *  0b101..288 x 216
 *  0b110..400 x 300
 */
#define CSI_CR2_LVRM(x)                          (((uint32_t)(((uint32_t)(x)) << CSI_CR2_LVRM_SHIFT)) & CSI_CR2_LVRM_MASK)

#define CSI_CR2_BTS_MASK                         (0x180000U)
#define CSI_CR2_BTS_SHIFT                        (19U)
/*! BTS
 *  0b00..GR
 *  0b01..RG
 *  0b10..BG
 *  0b11..GB
 */
#define CSI_CR2_BTS(x)                           (((uint32_t)(((uint32_t)(x)) << CSI_CR2_BTS_SHIFT)) & CSI_CR2_BTS_MASK)

#define CSI_CR2_SCE_MASK                         (0x800000U)
#define CSI_CR2_SCE_SHIFT                        (23U)
/*! SCE
 *  0b0..Skip count disable
 *  0b1..Skip count enable
 */
#define CSI_CR2_SCE(x)                           (((uint32_t)(((uint32_t)(x)) << CSI_CR2_SCE_SHIFT)) & CSI_CR2_SCE_MASK)

#define CSI_CR2_AFS_MASK                         (0x3000000U)
#define CSI_CR2_AFS_SHIFT                        (24U)
/*! AFS
 *  0b00..Abs Diff on consecutive green pixels
 *  0b01..Abs Diff on every third green pixels
 *  0b1x..Abs Diff on every four green pixels
 */
#define CSI_CR2_AFS(x)                           (((uint32_t)(((uint32_t)(x)) << CSI_CR2_AFS_SHIFT)) & CSI_CR2_AFS_MASK)

#define CSI_CR2_DRM_MASK                         (0x4000000U)
#define CSI_CR2_DRM_SHIFT                        (26U)
/*! DRM
 *  0b0..Stats grid of 8 x 6
 *  0b1..Stats grid of 8 x 12
 */
#define CSI_CR2_DRM(x)                           (((uint32_t)(((uint32_t)(x)) << CSI_CR2_DRM_SHIFT)) & CSI_CR2_DRM_MASK)

#define CSI_CR2_DMA_BURST_TYPE_SFF_MASK          (0x30000000U)
#define CSI_CR2_DMA_BURST_TYPE_SFF_SHIFT         (28U)
/*! DMA_BURST_TYPE_SFF
 *  0b01..INCR4
 *  0b11..INCR16
 *  0bx0..INCR8
 */
#define CSI_CR2_DMA_BURST_TYPE_SFF(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CR2_DMA_BURST_TYPE_SFF_SHIFT)) & CSI_CR2_DMA_BURST_TYPE_SFF_MASK)

#define CSI_CR2_DMA_BURST_TYPE_RFF_MASK          (0xC0000000U)
#define CSI_CR2_DMA_BURST_TYPE_RFF_SHIFT         (30U)
/*! DMA_BURST_TYPE_RFF
 *  0b01..INCR4
 *  0b11..INCR16
 *  0bx0..INCR8
 */
#define CSI_CR2_DMA_BURST_TYPE_RFF(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CR2_DMA_BURST_TYPE_RFF_SHIFT)) & CSI_CR2_DMA_BURST_TYPE_RFF_MASK)
/*! @} */

/*! @name CR3 - CSI Control Register 3 */
/*! @{ */

#define CSI_CR3_ECC_AUTO_EN_MASK                 (0x1U)
#define CSI_CR3_ECC_AUTO_EN_SHIFT                (0U)
/*! ECC_AUTO_EN
 *  0b0..Auto Error correction is disabled.
 *  0b1..Auto Error correction is enabled.
 */
#define CSI_CR3_ECC_AUTO_EN(x)                   (((uint32_t)(((uint32_t)(x)) << CSI_CR3_ECC_AUTO_EN_SHIFT)) & CSI_CR3_ECC_AUTO_EN_MASK)

#define CSI_CR3_ECC_INT_EN_MASK                  (0x2U)
#define CSI_CR3_ECC_INT_EN_SHIFT                 (1U)
/*! ECC_INT_EN
 *  0b0..No interrupt is generated when error is detected. Only the status bit ECC_INT is set.
 *  0b1..Interrupt is generated when error is detected.
 */
#define CSI_CR3_ECC_INT_EN(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CR3_ECC_INT_EN_SHIFT)) & CSI_CR3_ECC_INT_EN_MASK)

#define CSI_CR3_ZERO_PACK_EN_MASK                (0x4U)
#define CSI_CR3_ZERO_PACK_EN_SHIFT               (2U)
/*! ZERO_PACK_EN
 *  0b0..Zero packing disabled
 *  0b1..Zero packing enabled
 */
#define CSI_CR3_ZERO_PACK_EN(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CR3_ZERO_PACK_EN_SHIFT)) & CSI_CR3_ZERO_PACK_EN_MASK)

#define CSI_CR3_SENSOR_16BITS_MASK               (0x8U)
#define CSI_CR3_SENSOR_16BITS_SHIFT              (3U)
/*! SENSOR_16BITS
 *  0b0..Only one 8-bit sensor is connected.
 *  0b1..One 16-bit sensor is connected.
 */
#define CSI_CR3_SENSOR_16BITS(x)                 (((uint32_t)(((uint32_t)(x)) << CSI_CR3_SENSOR_16BITS_SHIFT)) & CSI_CR3_SENSOR_16BITS_MASK)

#define CSI_CR3_RxFF_LEVEL_MASK                  (0x70U)
#define CSI_CR3_RxFF_LEVEL_SHIFT                 (4U)
/*! RxFF_LEVEL
 *  0b000..4 Double words
 *  0b001..8 Double words
 *  0b010..16 Double words
 *  0b011..24 Double words
 *  0b100..32 Double words
 *  0b101..48 Double words
 *  0b110..64 Double words
 *  0b111..96 Double words
 */
#define CSI_CR3_RxFF_LEVEL(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CR3_RxFF_LEVEL_SHIFT)) & CSI_CR3_RxFF_LEVEL_MASK)

#define CSI_CR3_HRESP_ERR_EN_MASK                (0x80U)
#define CSI_CR3_HRESP_ERR_EN_SHIFT               (7U)
/*! HRESP_ERR_EN
 *  0b0..Disable hresponse error interrupt
 *  0b1..Enable hresponse error interrupt
 */
#define CSI_CR3_HRESP_ERR_EN(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CR3_HRESP_ERR_EN_SHIFT)) & CSI_CR3_HRESP_ERR_EN_MASK)

#define CSI_CR3_STATFF_LEVEL_MASK                (0x700U)
#define CSI_CR3_STATFF_LEVEL_SHIFT               (8U)
/*! STATFF_LEVEL
 *  0b000..4 Double words
 *  0b001..8 Double words
 *  0b010..12 Double words
 *  0b011..16 Double words
 *  0b100..24 Double words
 *  0b101..32 Double words
 *  0b110..48 Double words
 *  0b111..64 Double words
 */
#define CSI_CR3_STATFF_LEVEL(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CR3_STATFF_LEVEL_SHIFT)) & CSI_CR3_STATFF_LEVEL_MASK)

#define CSI_CR3_DMA_REQ_EN_SFF_MASK              (0x800U)
#define CSI_CR3_DMA_REQ_EN_SFF_SHIFT             (11U)
/*! DMA_REQ_EN_SFF
 *  0b0..Disable the dma request
 *  0b1..Enable the dma request
 */
#define CSI_CR3_DMA_REQ_EN_SFF(x)                (((uint32_t)(((uint32_t)(x)) << CSI_CR3_DMA_REQ_EN_SFF_SHIFT)) & CSI_CR3_DMA_REQ_EN_SFF_MASK)

#define CSI_CR3_DMA_REQ_EN_RFF_MASK              (0x1000U)
#define CSI_CR3_DMA_REQ_EN_RFF_SHIFT             (12U)
/*! DMA_REQ_EN_RFF
 *  0b0..Disable the dma request
 *  0b1..Enable the dma request
 */
#define CSI_CR3_DMA_REQ_EN_RFF(x)                (((uint32_t)(((uint32_t)(x)) << CSI_CR3_DMA_REQ_EN_RFF_SHIFT)) & CSI_CR3_DMA_REQ_EN_RFF_MASK)

#define CSI_CR3_DMA_REFLASH_SFF_MASK             (0x2000U)
#define CSI_CR3_DMA_REFLASH_SFF_SHIFT            (13U)
/*! DMA_REFLASH_SFF
 *  0b0..No reflashing
 *  0b1..Reflash the embedded DMA controller
 */
#define CSI_CR3_DMA_REFLASH_SFF(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CR3_DMA_REFLASH_SFF_SHIFT)) & CSI_CR3_DMA_REFLASH_SFF_MASK)

#define CSI_CR3_DMA_REFLASH_RFF_MASK             (0x4000U)
#define CSI_CR3_DMA_REFLASH_RFF_SHIFT            (14U)
/*! DMA_REFLASH_RFF
 *  0b0..No reflashing
 *  0b1..Reflash the embedded DMA controller
 */
#define CSI_CR3_DMA_REFLASH_RFF(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CR3_DMA_REFLASH_RFF_SHIFT)) & CSI_CR3_DMA_REFLASH_RFF_MASK)

#define CSI_CR3_FRMCNT_RST_MASK                  (0x8000U)
#define CSI_CR3_FRMCNT_RST_SHIFT                 (15U)
/*! FRMCNT_RST
 *  0b0..Do not reset
 *  0b1..Reset frame counter immediately
 */
#define CSI_CR3_FRMCNT_RST(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CR3_FRMCNT_RST_SHIFT)) & CSI_CR3_FRMCNT_RST_MASK)

#define CSI_CR3_FRMCNT_MASK                      (0xFFFF0000U)
#define CSI_CR3_FRMCNT_SHIFT                     (16U)
#define CSI_CR3_FRMCNT(x)                        (((uint32_t)(((uint32_t)(x)) << CSI_CR3_FRMCNT_SHIFT)) & CSI_CR3_FRMCNT_MASK)
/*! @} */

/*! @name STATFIFO - CSI Statistic FIFO Register */
/*! @{ */

#define CSI_STATFIFO_STAT_MASK                   (0xFFFFFFFFU)
#define CSI_STATFIFO_STAT_SHIFT                  (0U)
#define CSI_STATFIFO_STAT(x)                     (((uint32_t)(((uint32_t)(x)) << CSI_STATFIFO_STAT_SHIFT)) & CSI_STATFIFO_STAT_MASK)
/*! @} */

/*! @name RFIFO - CSI RX FIFO Register */
/*! @{ */

#define CSI_RFIFO_IMAGE_MASK                     (0xFFFFFFFFU)
#define CSI_RFIFO_IMAGE_SHIFT                    (0U)
#define CSI_RFIFO_IMAGE(x)                       (((uint32_t)(((uint32_t)(x)) << CSI_RFIFO_IMAGE_SHIFT)) & CSI_RFIFO_IMAGE_MASK)
/*! @} */

/*! @name RXCNT - CSI RX Count Register */
/*! @{ */

#define CSI_RXCNT_RXCNT_MASK                     (0x3FFFFFU)
#define CSI_RXCNT_RXCNT_SHIFT                    (0U)
#define CSI_RXCNT_RXCNT(x)                       (((uint32_t)(((uint32_t)(x)) << CSI_RXCNT_RXCNT_SHIFT)) & CSI_RXCNT_RXCNT_MASK)
/*! @} */

/*! @name SR - CSI Status Register */
/*! @{ */

#define CSI_SR_DRDY_MASK                         (0x1U)
#define CSI_SR_DRDY_SHIFT                        (0U)
/*! DRDY
 *  0b0..No data (word) is ready
 *  0b1..At least 1 datum (word) is ready in RXFIFO.
 */
#define CSI_SR_DRDY(x)                           (((uint32_t)(((uint32_t)(x)) << CSI_SR_DRDY_SHIFT)) & CSI_SR_DRDY_MASK)

#define CSI_SR_ECC_INT_MASK                      (0x2U)
#define CSI_SR_ECC_INT_SHIFT                     (1U)
/*! ECC_INT
 *  0b0..No error detected
 *  0b1..Error is detected in BT.656 coding
 */
#define CSI_SR_ECC_INT(x)                        (((uint32_t)(((uint32_t)(x)) << CSI_SR_ECC_INT_SHIFT)) & CSI_SR_ECC_INT_MASK)

#define CSI_SR_HISTOGRAM_CALC_DONE_INT_MASK      (0x4U)
#define CSI_SR_HISTOGRAM_CALC_DONE_INT_SHIFT     (2U)
/*! HISTOGRAM_CALC_DONE_INT
 *  0b0..Histogram calculation is not finished
 *  0b1..Histogram calculation is done and driver can access the PIXEL_COUNTERS(CSI_CSICR21~CSI_CSICR276) to get the gray level
 */
#define CSI_SR_HISTOGRAM_CALC_DONE_INT(x)        (((uint32_t)(((uint32_t)(x)) << CSI_SR_HISTOGRAM_CALC_DONE_INT_SHIFT)) & CSI_SR_HISTOGRAM_CALC_DONE_INT_MASK)

#define CSI_SR_HRESP_ERR_INT_MASK                (0x80U)
#define CSI_SR_HRESP_ERR_INT_SHIFT               (7U)
/*! HRESP_ERR_INT
 *  0b0..No hresponse error.
 *  0b1..Hresponse error is detected.
 */
#define CSI_SR_HRESP_ERR_INT(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_SR_HRESP_ERR_INT_SHIFT)) & CSI_SR_HRESP_ERR_INT_MASK)

#define CSI_SR_COF_INT_MASK                      (0x2000U)
#define CSI_SR_COF_INT_SHIFT                     (13U)
/*! COF_INT
 *  0b0..Video field has no change.
 *  0b1..Change of video field is detected.
 */
#define CSI_SR_COF_INT(x)                        (((uint32_t)(((uint32_t)(x)) << CSI_SR_COF_INT_SHIFT)) & CSI_SR_COF_INT_MASK)

#define CSI_SR_F1_INT_MASK                       (0x4000U)
#define CSI_SR_F1_INT_SHIFT                      (14U)
/*! F1_INT
 *  0b0..Field 1 of video is not detected.
 *  0b1..Field 1 of video is about to start.
 */
#define CSI_SR_F1_INT(x)                         (((uint32_t)(((uint32_t)(x)) << CSI_SR_F1_INT_SHIFT)) & CSI_SR_F1_INT_MASK)

#define CSI_SR_F2_INT_MASK                       (0x8000U)
#define CSI_SR_F2_INT_SHIFT                      (15U)
/*! F2_INT
 *  0b0..Field 2 of video is not detected
 *  0b1..Field 2 of video is about to start
 */
#define CSI_SR_F2_INT(x)                         (((uint32_t)(((uint32_t)(x)) << CSI_SR_F2_INT_SHIFT)) & CSI_SR_F2_INT_MASK)

#define CSI_SR_SOF_INT_MASK                      (0x10000U)
#define CSI_SR_SOF_INT_SHIFT                     (16U)
/*! SOF_INT
 *  0b0..SOF is not detected.
 *  0b1..SOF is detected.
 */
#define CSI_SR_SOF_INT(x)                        (((uint32_t)(((uint32_t)(x)) << CSI_SR_SOF_INT_SHIFT)) & CSI_SR_SOF_INT_MASK)

#define CSI_SR_EOF_INT_MASK                      (0x20000U)
#define CSI_SR_EOF_INT_SHIFT                     (17U)
/*! EOF_INT
 *  0b0..EOF is not detected.
 *  0b1..EOF is detected.
 */
#define CSI_SR_EOF_INT(x)                        (((uint32_t)(((uint32_t)(x)) << CSI_SR_EOF_INT_SHIFT)) & CSI_SR_EOF_INT_MASK)

#define CSI_SR_RxFF_INT_MASK                     (0x40000U)
#define CSI_SR_RxFF_INT_SHIFT                    (18U)
/*! RxFF_INT
 *  0b0..RxFIFO is not full.
 *  0b1..RxFIFO is full.
 */
#define CSI_SR_RxFF_INT(x)                       (((uint32_t)(((uint32_t)(x)) << CSI_SR_RxFF_INT_SHIFT)) & CSI_SR_RxFF_INT_MASK)

#define CSI_SR_DMA_TSF_DONE_FB1_MASK             (0x80000U)
#define CSI_SR_DMA_TSF_DONE_FB1_SHIFT            (19U)
/*! DMA_TSF_DONE_FB1
 *  0b0..DMA transfer is not completed.
 *  0b1..DMA transfer is completed.
 */
#define CSI_SR_DMA_TSF_DONE_FB1(x)               (((uint32_t)(((uint32_t)(x)) << CSI_SR_DMA_TSF_DONE_FB1_SHIFT)) & CSI_SR_DMA_TSF_DONE_FB1_MASK)

#define CSI_SR_DMA_TSF_DONE_FB2_MASK             (0x100000U)
#define CSI_SR_DMA_TSF_DONE_FB2_SHIFT            (20U)
/*! DMA_TSF_DONE_FB2
 *  0b0..DMA transfer is not completed.
 *  0b1..DMA transfer is completed.
 */
#define CSI_SR_DMA_TSF_DONE_FB2(x)               (((uint32_t)(((uint32_t)(x)) << CSI_SR_DMA_TSF_DONE_FB2_SHIFT)) & CSI_SR_DMA_TSF_DONE_FB2_MASK)

#define CSI_SR_STATFF_INT_MASK                   (0x200000U)
#define CSI_SR_STATFF_INT_SHIFT                  (21U)
/*! STATFF_INT
 *  0b0..STATFIFO is not full.
 *  0b1..STATFIFO is full.
 */
#define CSI_SR_STATFF_INT(x)                     (((uint32_t)(((uint32_t)(x)) << CSI_SR_STATFF_INT_SHIFT)) & CSI_SR_STATFF_INT_MASK)

#define CSI_SR_DMA_TSF_DONE_SFF_MASK             (0x400000U)
#define CSI_SR_DMA_TSF_DONE_SFF_SHIFT            (22U)
/*! DMA_TSF_DONE_SFF
 *  0b0..DMA transfer is not completed.
 *  0b1..DMA transfer is completed.
 */
#define CSI_SR_DMA_TSF_DONE_SFF(x)               (((uint32_t)(((uint32_t)(x)) << CSI_SR_DMA_TSF_DONE_SFF_SHIFT)) & CSI_SR_DMA_TSF_DONE_SFF_MASK)

#define CSI_SR_RF_OR_INT_MASK                    (0x1000000U)
#define CSI_SR_RF_OR_INT_SHIFT                   (24U)
/*! RF_OR_INT
 *  0b0..RXFIFO has not overflowed.
 *  0b1..RXFIFO has overflowed.
 */
#define CSI_SR_RF_OR_INT(x)                      (((uint32_t)(((uint32_t)(x)) << CSI_SR_RF_OR_INT_SHIFT)) & CSI_SR_RF_OR_INT_MASK)

#define CSI_SR_SF_OR_INT_MASK                    (0x2000000U)
#define CSI_SR_SF_OR_INT_SHIFT                   (25U)
/*! SF_OR_INT
 *  0b0..STATFIFO has not overflowed.
 *  0b1..STATFIFO has overflowed.
 */
#define CSI_SR_SF_OR_INT(x)                      (((uint32_t)(((uint32_t)(x)) << CSI_SR_SF_OR_INT_SHIFT)) & CSI_SR_SF_OR_INT_MASK)

#define CSI_SR_DMA_FIELD1_DONE_MASK              (0x4000000U)
#define CSI_SR_DMA_FIELD1_DONE_SHIFT             (26U)
#define CSI_SR_DMA_FIELD1_DONE(x)                (((uint32_t)(((uint32_t)(x)) << CSI_SR_DMA_FIELD1_DONE_SHIFT)) & CSI_SR_DMA_FIELD1_DONE_MASK)

#define CSI_SR_DMA_FIELD0_DONE_MASK              (0x8000000U)
#define CSI_SR_DMA_FIELD0_DONE_SHIFT             (27U)
#define CSI_SR_DMA_FIELD0_DONE(x)                (((uint32_t)(((uint32_t)(x)) << CSI_SR_DMA_FIELD0_DONE_SHIFT)) & CSI_SR_DMA_FIELD0_DONE_MASK)

#define CSI_SR_BASEADDR_CHHANGE_ERROR_MASK       (0x10000000U)
#define CSI_SR_BASEADDR_CHHANGE_ERROR_SHIFT      (28U)
#define CSI_SR_BASEADDR_CHHANGE_ERROR(x)         (((uint32_t)(((uint32_t)(x)) << CSI_SR_BASEADDR_CHHANGE_ERROR_SHIFT)) & CSI_SR_BASEADDR_CHHANGE_ERROR_MASK)
/*! @} */

/*! @name DMASA_STATFIFO - CSI DMA Start Address Register - for STATFIFO */
/*! @{ */

#define CSI_DMASA_STATFIFO_DMA_START_ADDR_SFF_MASK (0xFFFFFFFCU)
#define CSI_DMASA_STATFIFO_DMA_START_ADDR_SFF_SHIFT (2U)
#define CSI_DMASA_STATFIFO_DMA_START_ADDR_SFF(x) (((uint32_t)(((uint32_t)(x)) << CSI_DMASA_STATFIFO_DMA_START_ADDR_SFF_SHIFT)) & CSI_DMASA_STATFIFO_DMA_START_ADDR_SFF_MASK)
/*! @} */

/*! @name DMATS_STATFIFO - CSI DMA Transfer Size Register - for STATFIFO */
/*! @{ */

#define CSI_DMATS_STATFIFO_DMA_TSF_SIZE_SFF_MASK (0xFFFFFFFFU)
#define CSI_DMATS_STATFIFO_DMA_TSF_SIZE_SFF_SHIFT (0U)
#define CSI_DMATS_STATFIFO_DMA_TSF_SIZE_SFF(x)   (((uint32_t)(((uint32_t)(x)) << CSI_DMATS_STATFIFO_DMA_TSF_SIZE_SFF_SHIFT)) & CSI_DMATS_STATFIFO_DMA_TSF_SIZE_SFF_MASK)
/*! @} */

/*! @name DMASA_FB1 - CSI DMA Start Address Register - for Frame Buffer1 */
/*! @{ */

#define CSI_DMASA_FB1_DMA_START_ADDR_FB1_MASK    (0xFFFFFFFCU)
#define CSI_DMASA_FB1_DMA_START_ADDR_FB1_SHIFT   (2U)
#define CSI_DMASA_FB1_DMA_START_ADDR_FB1(x)      (((uint32_t)(((uint32_t)(x)) << CSI_DMASA_FB1_DMA_START_ADDR_FB1_SHIFT)) & CSI_DMASA_FB1_DMA_START_ADDR_FB1_MASK)
/*! @} */

/*! @name DMASA_FB2 - CSI DMA Transfer Size Register - for Frame Buffer2 */
/*! @{ */

#define CSI_DMASA_FB2_DMA_START_ADDR_FB2_MASK    (0xFFFFFFFCU)
#define CSI_DMASA_FB2_DMA_START_ADDR_FB2_SHIFT   (2U)
#define CSI_DMASA_FB2_DMA_START_ADDR_FB2(x)      (((uint32_t)(((uint32_t)(x)) << CSI_DMASA_FB2_DMA_START_ADDR_FB2_SHIFT)) & CSI_DMASA_FB2_DMA_START_ADDR_FB2_MASK)
/*! @} */

/*! @name FBUF_PARA - CSI Frame Buffer Parameter Register */
/*! @{ */

#define CSI_FBUF_PARA_FBUF_STRIDE_MASK           (0xFFFFU)
#define CSI_FBUF_PARA_FBUF_STRIDE_SHIFT          (0U)
#define CSI_FBUF_PARA_FBUF_STRIDE(x)             (((uint32_t)(((uint32_t)(x)) << CSI_FBUF_PARA_FBUF_STRIDE_SHIFT)) & CSI_FBUF_PARA_FBUF_STRIDE_MASK)

#define CSI_FBUF_PARA_DEINTERLACE_STRIDE_MASK    (0xFFFF0000U)
#define CSI_FBUF_PARA_DEINTERLACE_STRIDE_SHIFT   (16U)
#define CSI_FBUF_PARA_DEINTERLACE_STRIDE(x)      (((uint32_t)(((uint32_t)(x)) << CSI_FBUF_PARA_DEINTERLACE_STRIDE_SHIFT)) & CSI_FBUF_PARA_DEINTERLACE_STRIDE_MASK)
/*! @} */

/*! @name IMAG_PARA - CSI Image Parameter Register */
/*! @{ */

#define CSI_IMAG_PARA_IMAGE_HEIGHT_MASK          (0xFFFFU)
#define CSI_IMAG_PARA_IMAGE_HEIGHT_SHIFT         (0U)
#define CSI_IMAG_PARA_IMAGE_HEIGHT(x)            (((uint32_t)(((uint32_t)(x)) << CSI_IMAG_PARA_IMAGE_HEIGHT_SHIFT)) & CSI_IMAG_PARA_IMAGE_HEIGHT_MASK)

#define CSI_IMAG_PARA_IMAGE_WIDTH_MASK           (0xFFFF0000U)
#define CSI_IMAG_PARA_IMAGE_WIDTH_SHIFT          (16U)
#define CSI_IMAG_PARA_IMAGE_WIDTH(x)             (((uint32_t)(((uint32_t)(x)) << CSI_IMAG_PARA_IMAGE_WIDTH_SHIFT)) & CSI_IMAG_PARA_IMAGE_WIDTH_MASK)
/*! @} */

/*! @name CR18 - CSI Control Register 18 */
/*! @{ */

#define CSI_CR18_NTSC_EN_MASK                    (0x1U)
#define CSI_CR18_NTSC_EN_SHIFT                   (0U)
/*! NTSC_EN
 *  0b0..PAL
 *  0b1..NTSC
 */
#define CSI_CR18_NTSC_EN(x)                      (((uint32_t)(((uint32_t)(x)) << CSI_CR18_NTSC_EN_SHIFT)) & CSI_CR18_NTSC_EN_MASK)

#define CSI_CR18_TVDECODER_IN_EN_MASK            (0x2U)
#define CSI_CR18_TVDECODER_IN_EN_SHIFT           (1U)
#define CSI_CR18_TVDECODER_IN_EN(x)              (((uint32_t)(((uint32_t)(x)) << CSI_CR18_TVDECODER_IN_EN_SHIFT)) & CSI_CR18_TVDECODER_IN_EN_MASK)

#define CSI_CR18_DEINTERLACE_EN_MASK             (0x4U)
#define CSI_CR18_DEINTERLACE_EN_SHIFT            (2U)
/*! DEINTERLACE_EN
 *  0b0..Deinterlace disabled
 *  0b1..Deinterlace enabled
 */
#define CSI_CR18_DEINTERLACE_EN(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CR18_DEINTERLACE_EN_SHIFT)) & CSI_CR18_DEINTERLACE_EN_MASK)

#define CSI_CR18_PARALLEL24_EN_MASK              (0x8U)
#define CSI_CR18_PARALLEL24_EN_SHIFT             (3U)
/*! PARALLEL24_EN
 *  0b0..Input is disabled
 *  0b1..Input is enabled
 */
#define CSI_CR18_PARALLEL24_EN(x)                (((uint32_t)(((uint32_t)(x)) << CSI_CR18_PARALLEL24_EN_SHIFT)) & CSI_CR18_PARALLEL24_EN_MASK)

#define CSI_CR18_BASEADDR_SWITCH_EN_MASK         (0x10U)
#define CSI_CR18_BASEADDR_SWITCH_EN_SHIFT        (4U)
#define CSI_CR18_BASEADDR_SWITCH_EN(x)           (((uint32_t)(((uint32_t)(x)) << CSI_CR18_BASEADDR_SWITCH_EN_SHIFT)) & CSI_CR18_BASEADDR_SWITCH_EN_MASK)

#define CSI_CR18_BASEADDR_SWITCH_SEL_MASK        (0x20U)
#define CSI_CR18_BASEADDR_SWITCH_SEL_SHIFT       (5U)
/*! BASEADDR_SWITCH_SEL
 *  0b0..Switching base address at the edge of the vsync
 *  0b1..Switching base address at the edge of the first data of each frame
 */
#define CSI_CR18_BASEADDR_SWITCH_SEL(x)          (((uint32_t)(((uint32_t)(x)) << CSI_CR18_BASEADDR_SWITCH_SEL_SHIFT)) & CSI_CR18_BASEADDR_SWITCH_SEL_MASK)

#define CSI_CR18_FIELD0_DONE_IE_MASK             (0x40U)
#define CSI_CR18_FIELD0_DONE_IE_SHIFT            (6U)
/*! FIELD0_DONE_IE
 *  0b0..Interrupt disabled
 *  0b1..Interrupt enabled
 */
#define CSI_CR18_FIELD0_DONE_IE(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CR18_FIELD0_DONE_IE_SHIFT)) & CSI_CR18_FIELD0_DONE_IE_MASK)

#define CSI_CR18_DMA_FIELD1_DONE_IE_MASK         (0x80U)
#define CSI_CR18_DMA_FIELD1_DONE_IE_SHIFT        (7U)
/*! DMA_FIELD1_DONE_IE
 *  0b0..Interrupt disabled
 *  0b1..Interrupt enabled
 */
#define CSI_CR18_DMA_FIELD1_DONE_IE(x)           (((uint32_t)(((uint32_t)(x)) << CSI_CR18_DMA_FIELD1_DONE_IE_SHIFT)) & CSI_CR18_DMA_FIELD1_DONE_IE_MASK)

#define CSI_CR18_LAST_DMA_REQ_SEL_MASK           (0x100U)
#define CSI_CR18_LAST_DMA_REQ_SEL_SHIFT          (8U)
/*! LAST_DMA_REQ_SEL
 *  0b0..fifo_full_level
 *  0b1..hburst_length
 */
#define CSI_CR18_LAST_DMA_REQ_SEL(x)             (((uint32_t)(((uint32_t)(x)) << CSI_CR18_LAST_DMA_REQ_SEL_SHIFT)) & CSI_CR18_LAST_DMA_REQ_SEL_MASK)

#define CSI_CR18_BASEADDR_CHANGE_ERROR_IE_MASK   (0x200U)
#define CSI_CR18_BASEADDR_CHANGE_ERROR_IE_SHIFT  (9U)
/*! BASEADDR_CHANGE_ERROR_IE
 *  0b0..Interrupt disabled
 *  0b1..Interrupt enabled
 */
#define CSI_CR18_BASEADDR_CHANGE_ERROR_IE(x)     (((uint32_t)(((uint32_t)(x)) << CSI_CR18_BASEADDR_CHANGE_ERROR_IE_SHIFT)) & CSI_CR18_BASEADDR_CHANGE_ERROR_IE_MASK)

#define CSI_CR18_RGB888A_FORMAT_SEL_MASK         (0x400U)
#define CSI_CR18_RGB888A_FORMAT_SEL_SHIFT        (10U)
/*! RGB888A_FORMAT_SEL
 *  0b0..{8'h0, data[23:0]}
 *  0b1..{data[23:0], 8'h0}
 */
#define CSI_CR18_RGB888A_FORMAT_SEL(x)           (((uint32_t)(((uint32_t)(x)) << CSI_CR18_RGB888A_FORMAT_SEL_SHIFT)) & CSI_CR18_RGB888A_FORMAT_SEL_MASK)

#define CSI_CR18_AHB_HPROT_MASK                  (0xF000U)
#define CSI_CR18_AHB_HPROT_SHIFT                 (12U)
#define CSI_CR18_AHB_HPROT(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CR18_AHB_HPROT_SHIFT)) & CSI_CR18_AHB_HPROT_MASK)

#define CSI_CR18_MASK_OPTION_MASK                (0xC0000U)
#define CSI_CR18_MASK_OPTION_SHIFT               (18U)
/*! MASK_OPTION
 *  0b00..Writing to memory (OCRAM or external DDR) from first completely frame, when using this option, the CSI_ENABLE should be 1.
 *  0b01..Writing to memory when CSI_ENABLE is 1.
 *  0b10..Writing to memory from second completely frame, when using this option, the CSI_ENABLE should be 1.
 *  0b11..Writing to memory when data comes in, not matter the CSI_ENABLE is 1 or 0.
 */
#define CSI_CR18_MASK_OPTION(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CR18_MASK_OPTION_SHIFT)) & CSI_CR18_MASK_OPTION_MASK)

#define CSI_CR18_MIPI_DOUBLE_CMPNT_MASK          (0x100000U)
#define CSI_CR18_MIPI_DOUBLE_CMPNT_SHIFT         (20U)
/*! MIPI_DOUBLE_CMPNT
 *  0b0..Single component per clock cycle (half pixel per clock cycle)
 *  0b1..Double component per clock cycle (a pixel per clock cycle)
 */
#define CSI_CR18_MIPI_DOUBLE_CMPNT(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CR18_MIPI_DOUBLE_CMPNT_SHIFT)) & CSI_CR18_MIPI_DOUBLE_CMPNT_MASK)

#define CSI_CR18_MIPI_YU_SWAP_MASK               (0x200000U)
#define CSI_CR18_MIPI_YU_SWAP_SHIFT              (21U)
/*! MIPI_YU_SWAP - It only works in MIPI CSI YUV422 double component mode. */
#define CSI_CR18_MIPI_YU_SWAP(x)                 (((uint32_t)(((uint32_t)(x)) << CSI_CR18_MIPI_YU_SWAP_SHIFT)) & CSI_CR18_MIPI_YU_SWAP_MASK)

#define CSI_CR18_DATA_FROM_MIPI_MASK             (0x400000U)
#define CSI_CR18_DATA_FROM_MIPI_SHIFT            (22U)
/*! DATA_FROM_MIPI
 *  0b0..Data from parallel sensor
 *  0b1..Data from MIPI
 */
#define CSI_CR18_DATA_FROM_MIPI(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CR18_DATA_FROM_MIPI_SHIFT)) & CSI_CR18_DATA_FROM_MIPI_MASK)

#define CSI_CR18_LINE_STRIDE_EN_MASK             (0x1000000U)
#define CSI_CR18_LINE_STRIDE_EN_SHIFT            (24U)
#define CSI_CR18_LINE_STRIDE_EN(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CR18_LINE_STRIDE_EN_SHIFT)) & CSI_CR18_LINE_STRIDE_EN_MASK)

#define CSI_CR18_MIPI_DATA_FORMAT_MASK           (0x7E000000U)
#define CSI_CR18_MIPI_DATA_FORMAT_SHIFT          (25U)
/*! MIPI_DATA_FORMAT - Image Data Format */
#define CSI_CR18_MIPI_DATA_FORMAT(x)             (((uint32_t)(((uint32_t)(x)) << CSI_CR18_MIPI_DATA_FORMAT_SHIFT)) & CSI_CR18_MIPI_DATA_FORMAT_MASK)

#define CSI_CR18_CSI_ENABLE_MASK                 (0x80000000U)
#define CSI_CR18_CSI_ENABLE_SHIFT                (31U)
#define CSI_CR18_CSI_ENABLE(x)                   (((uint32_t)(((uint32_t)(x)) << CSI_CR18_CSI_ENABLE_SHIFT)) & CSI_CR18_CSI_ENABLE_MASK)
/*! @} */

/*! @name CR19 - CSI Control Register 19 */
/*! @{ */

#define CSI_CR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL_MASK (0xFFU)
#define CSI_CR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL_SHIFT (0U)
#define CSI_CR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL(x) (((uint32_t)(((uint32_t)(x)) << CSI_CR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL_SHIFT)) & CSI_CR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL_MASK)
/*! @} */

/*! @name CR20 - CSI Control Register 20 */
/*! @{ */

#define CSI_CR20_THRESHOLD_MASK                  (0xFFU)
#define CSI_CR20_THRESHOLD_SHIFT                 (0U)
#define CSI_CR20_THRESHOLD(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CR20_THRESHOLD_SHIFT)) & CSI_CR20_THRESHOLD_MASK)

#define CSI_CR20_BINARY_EN_MASK                  (0x100U)
#define CSI_CR20_BINARY_EN_SHIFT                 (8U)
/*! BINARY_EN
 *  0b0..Output is Y8 format(8 bits each pixel)
 *  0b1..Output is Y1 format(1 bit each pixel)
 */
#define CSI_CR20_BINARY_EN(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CR20_BINARY_EN_SHIFT)) & CSI_CR20_BINARY_EN_MASK)

#define CSI_CR20_QR_DATA_FORMAT_MASK             (0xE00U)
#define CSI_CR20_QR_DATA_FORMAT_SHIFT            (9U)
/*! QR_DATA_FORMAT
 *  0b000..YU YV one cycle per 1 pixel input
 *  0b001..UY VY one cycle per1 pixel input
 *  0b010..Y U Y V two cycles per 1 pixel input
 *  0b011..U Y V Y two cycles per 1 pixel input
 *  0b100..YUV one cycle per 1 pixel input
 *  0b101..Y U V three cycles per 1 pixel input
 */
#define CSI_CR20_QR_DATA_FORMAT(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CR20_QR_DATA_FORMAT_SHIFT)) & CSI_CR20_QR_DATA_FORMAT_MASK)

#define CSI_CR20_BIG_END_MASK                    (0x1000U)
#define CSI_CR20_BIG_END_SHIFT                   (12U)
/*! BIG_END
 *  0b0..The newest (most recent) data will be assigned the lowest position when store to memory.
 *  0b1..The newest (most recent) data will be assigned the highest position when store to memory.
 */
#define CSI_CR20_BIG_END(x)                      (((uint32_t)(((uint32_t)(x)) << CSI_CR20_BIG_END_SHIFT)) & CSI_CR20_BIG_END_MASK)

#define CSI_CR20_10BIT_NEW_EN_MASK               (0x20000000U)
#define CSI_CR20_10BIT_NEW_EN_SHIFT              (29U)
/*! 10BIT_NEW_EN
 *  0b0..When input 8bits data, it will use the data[9:2]
 *  0b1..If input is 10bits data, it will use the data[7:0] (optional)
 */
#define CSI_CR20_10BIT_NEW_EN(x)                 (((uint32_t)(((uint32_t)(x)) << CSI_CR20_10BIT_NEW_EN_SHIFT)) & CSI_CR20_10BIT_NEW_EN_MASK)

#define CSI_CR20_HISTOGRAM_EN_MASK               (0x40000000U)
#define CSI_CR20_HISTOGRAM_EN_SHIFT              (30U)
/*! HISTOGRAM_EN
 *  0b0..Histogram disable
 *  0b1..Histogram enable
 */
#define CSI_CR20_HISTOGRAM_EN(x)                 (((uint32_t)(((uint32_t)(x)) << CSI_CR20_HISTOGRAM_EN_SHIFT)) & CSI_CR20_HISTOGRAM_EN_MASK)

#define CSI_CR20_QRCODE_EN_MASK                  (0x80000000U)
#define CSI_CR20_QRCODE_EN_SHIFT                 (31U)
/*! QRCODE_EN
 *  0b0..Normal mode
 *  0b1..Gray scale mode
 */
#define CSI_CR20_QRCODE_EN(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CR20_QRCODE_EN_SHIFT)) & CSI_CR20_QRCODE_EN_MASK)
/*! @} */

/*! @name CR - CSI Control Register */
/*! @{ */

#define CSI_CR_PIXEL_COUNTERS_MASK               (0xFFFFFFU)
#define CSI_CR_PIXEL_COUNTERS_SHIFT              (0U)
#define CSI_CR_PIXEL_COUNTERS(x)                 (((uint32_t)(((uint32_t)(x)) << CSI_CR_PIXEL_COUNTERS_SHIFT)) & CSI_CR_PIXEL_COUNTERS_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group CSI_Register_Masks */

/* Backward compatibility */
#define CSI_CSICR1_PIXEL_BIT_MASK     CSI_CR1_PIXEL_BIT_MASK
#define CSI_CSICR1_PIXEL_BIT_SHIFT     CSI_CR1_PIXEL_BIT_SHIFT
#define CSI_CSICR1_PIXEL_BIT(x)     CSI_CR1_PIXEL_BIT(x)
#define CSI_CSICR1_REDGE_MASK     CSI_CR1_REDGE_MASK
#define CSI_CSICR1_REDGE_SHIFT     CSI_CR1_REDGE_SHIFT
#define CSI_CSICR1_REDGE(x)     CSI_CR1_REDGE(x)
#define CSI_CSICR1_INV_PCLK_MASK     CSI_CR1_INV_PCLK_MASK
#define CSI_CSICR1_INV_PCLK_SHIFT     CSI_CR1_INV_PCLK_SHIFT
#define CSI_CSICR1_INV_PCLK(x)     CSI_CR1_INV_PCLK(x)
#define CSI_CSICR1_INV_DATA_MASK     CSI_CR1_INV_DATA_MASK
#define CSI_CSICR1_INV_DATA_SHIFT     CSI_CR1_INV_DATA_SHIFT
#define CSI_CSICR1_INV_DATA(x)     CSI_CR1_INV_DATA(x)
#define CSI_CSICR1_GCLK_MODE_MASK     CSI_CR1_GCLK_MODE_MASK
#define CSI_CSICR1_GCLK_MODE_SHIFT     CSI_CR1_GCLK_MODE_SHIFT
#define CSI_CSICR1_GCLK_MODE(x)     CSI_CR1_GCLK_MODE(x)
#define CSI_CSICR1_CLR_RXFIFO_MASK     CSI_CR1_CLR_RXFIFO_MASK
#define CSI_CSICR1_CLR_RXFIFO_SHIFT     CSI_CR1_CLR_RXFIFO_SHIFT
#define CSI_CSICR1_CLR_RXFIFO(x)     CSI_CR1_CLR_RXFIFO(x)
#define CSI_CSICR1_CLR_STATFIFO_MASK     CSI_CR1_CLR_STATFIFO_MASK
#define CSI_CSICR1_CLR_STATFIFO_SHIFT     CSI_CR1_CLR_STATFIFO_SHIFT
#define CSI_CSICR1_CLR_STATFIFO(x)     CSI_CR1_CLR_STATFIFO(x)
#define CSI_CSICR1_PACK_DIR_MASK     CSI_CR1_PACK_DIR_MASK
#define CSI_CSICR1_PACK_DIR_SHIFT     CSI_CR1_PACK_DIR_SHIFT
#define CSI_CSICR1_PACK_DIR(x)     CSI_CR1_PACK_DIR(x)
#define CSI_CSICR1_FCC_MASK     CSI_CR1_FCC_MASK
#define CSI_CSICR1_FCC_SHIFT     CSI_CR1_FCC_SHIFT
#define CSI_CSICR1_FCC(x)     CSI_CR1_FCC(x)
#define CSI_CSICR1_CCIR_EN_MASK     CSI_CR1_CCIR_EN_MASK
#define CSI_CSICR1_CCIR_EN_SHIFT     CSI_CR1_CCIR_EN_SHIFT
#define CSI_CSICR1_CCIR_EN(x)     CSI_CR1_CCIR_EN(x)
#define CSI_CSICR1_HSYNC_POL_MASK     CSI_CR1_HSYNC_POL_MASK
#define CSI_CSICR1_HSYNC_POL_SHIFT     CSI_CR1_HSYNC_POL_SHIFT
#define CSI_CSICR1_HSYNC_POL(x)     CSI_CR1_HSYNC_POL(x)
#define CSI_CSICR1_HISTOGRAM_CALC_DONE_IE_MASK     CSI_CR1_HISTOGRAM_CALC_DONE_IE_MASK
#define CSI_CSICR1_HISTOGRAM_CALC_DONE_IE_SHIFT     CSI_CR1_HISTOGRAM_CALC_DONE_IE_SHIFT
#define CSI_CSICR1_HISTOGRAM_CALC_DONE_IE(x)     CSI_CR1_HISTOGRAM_CALC_DONE_IE(x)
#define CSI_CSICR1_SOF_INTEN_MASK     CSI_CR1_SOF_INTEN_MASK
#define CSI_CSICR1_SOF_INTEN_SHIFT     CSI_CR1_SOF_INTEN_SHIFT
#define CSI_CSICR1_SOF_INTEN(x)     CSI_CR1_SOF_INTEN(x)
#define CSI_CSICR1_SOF_POL_MASK     CSI_CR1_SOF_POL_MASK
#define CSI_CSICR1_SOF_POL_SHIFT     CSI_CR1_SOF_POL_SHIFT
#define CSI_CSICR1_SOF_POL(x)     CSI_CR1_SOF_POL(x)
#define CSI_CSICR1_RXFF_INTEN_MASK     CSI_CR1_RXFF_INTEN_MASK
#define CSI_CSICR1_RXFF_INTEN_SHIFT     CSI_CR1_RXFF_INTEN_SHIFT
#define CSI_CSICR1_RXFF_INTEN(x)     CSI_CR1_RXFF_INTEN(x)
#define CSI_CSICR1_FB1_DMA_DONE_INTEN_MASK     CSI_CR1_FB1_DMA_DONE_INTEN_MASK
#define CSI_CSICR1_FB1_DMA_DONE_INTEN_SHIFT     CSI_CR1_FB1_DMA_DONE_INTEN_SHIFT
#define CSI_CSICR1_FB1_DMA_DONE_INTEN(x)     CSI_CR1_FB1_DMA_DONE_INTEN(x)
#define CSI_CSICR1_FB2_DMA_DONE_INTEN_MASK     CSI_CR1_FB2_DMA_DONE_INTEN_MASK
#define CSI_CSICR1_FB2_DMA_DONE_INTEN_SHIFT     CSI_CR1_FB2_DMA_DONE_INTEN_SHIFT
#define CSI_CSICR1_FB2_DMA_DONE_INTEN(x)     CSI_CR1_FB2_DMA_DONE_INTEN(x)
#define CSI_CSICR1_STATFF_INTEN_MASK     CSI_CR1_STATFF_INTEN_MASK
#define CSI_CSICR1_STATFF_INTEN_SHIFT     CSI_CR1_STATFF_INTEN_SHIFT
#define CSI_CSICR1_STATFF_INTEN(x)     CSI_CR1_STATFF_INTEN(x)
#define CSI_CSICR1_SFF_DMA_DONE_INTEN_MASK     CSI_CR1_SFF_DMA_DONE_INTEN_MASK
#define CSI_CSICR1_SFF_DMA_DONE_INTEN_SHIFT     CSI_CR1_SFF_DMA_DONE_INTEN_SHIFT
#define CSI_CSICR1_SFF_DMA_DONE_INTEN(x)     CSI_CR1_SFF_DMA_DONE_INTEN(x)
#define CSI_CSICR1_RF_OR_INTEN_MASK     CSI_CR1_RF_OR_INTEN_MASK
#define CSI_CSICR1_RF_OR_INTEN_SHIFT     CSI_CR1_RF_OR_INTEN_SHIFT
#define CSI_CSICR1_RF_OR_INTEN(x)     CSI_CR1_RF_OR_INTEN(x)
#define CSI_CSICR1_SF_OR_INTEN_MASK     CSI_CR1_SF_OR_INTEN_MASK
#define CSI_CSICR1_SF_OR_INTEN_SHIFT     CSI_CR1_SF_OR_INTEN_SHIFT
#define CSI_CSICR1_SF_OR_INTEN(x)     CSI_CR1_SF_OR_INTEN(x)
#define CSI_CSICR1_COF_INT_EN_MASK     CSI_CR1_COF_INT_EN_MASK
#define CSI_CSICR1_COF_INT_EN_SHIFT     CSI_CR1_COF_INT_EN_SHIFT
#define CSI_CSICR1_COF_INT_EN(x)     CSI_CR1_COF_INT_EN(x)
#define CSI_CSICR1_VIDEO_MODE_MASK     CSI_CR1_VIDEO_MODE_MASK
#define CSI_CSICR1_VIDEO_MODE_SHIFT     CSI_CR1_VIDEO_MODE_SHIFT
#define CSI_CSICR1_VIDEO_MODE(x)     CSI_CR1_VIDEO_MODE(x)
#define CSI_CSICR1_EOF_INT_EN_MASK     CSI_CR1_EOF_INT_EN_MASK
#define CSI_CSICR1_EOF_INT_EN_SHIFT     CSI_CR1_EOF_INT_EN_SHIFT
#define CSI_CSICR1_EOF_INT_EN(x)     CSI_CR1_EOF_INT_EN(x)
#define CSI_CSICR1_EXT_VSYNC_MASK     CSI_CR1_EXT_VSYNC_MASK
#define CSI_CSICR1_EXT_VSYNC_SHIFT     CSI_CR1_EXT_VSYNC_SHIFT
#define CSI_CSICR1_EXT_VSYNC(x)     CSI_CR1_EXT_VSYNC(x)
#define CSI_CSICR1_SWAP16_EN_MASK     CSI_CR1_SWAP16_EN_MASK
#define CSI_CSICR1_SWAP16_EN_SHIFT     CSI_CR1_SWAP16_EN_SHIFT
#define CSI_CSICR1_SWAP16_EN(x)     CSI_CR1_SWAP16_EN(x)
#define CSI_CSICR2_HSC_MASK     CSI_CR2_HSC_MASK
#define CSI_CSICR2_HSC_SHIFT     CSI_CR2_HSC_SHIFT
#define CSI_CSICR2_HSC(x)     CSI_CR2_HSC(x)
#define CSI_CSICR2_VSC_MASK     CSI_CR2_VSC_MASK
#define CSI_CSICR2_VSC_SHIFT     CSI_CR2_VSC_SHIFT
#define CSI_CSICR2_VSC(x)     CSI_CR2_VSC(x)
#define CSI_CSICR2_LVRM_MASK     CSI_CR2_LVRM_MASK
#define CSI_CSICR2_LVRM_SHIFT     CSI_CR2_LVRM_SHIFT
#define CSI_CSICR2_LVRM(x)     CSI_CR2_LVRM(x)
#define CSI_CSICR2_BTS_MASK     CSI_CR2_BTS_MASK
#define CSI_CSICR2_BTS_SHIFT     CSI_CR2_BTS_SHIFT
#define CSI_CSICR2_BTS(x)     CSI_CR2_BTS(x)
#define CSI_CSICR2_SCE_MASK     CSI_CR2_SCE_MASK
#define CSI_CSICR2_SCE_SHIFT     CSI_CR2_SCE_SHIFT
#define CSI_CSICR2_SCE(x)     CSI_CR2_SCE(x)
#define CSI_CSICR2_AFS_MASK     CSI_CR2_AFS_MASK
#define CSI_CSICR2_AFS_SHIFT     CSI_CR2_AFS_SHIFT
#define CSI_CSICR2_AFS(x)     CSI_CR2_AFS(x)
#define CSI_CSICR2_DRM_MASK     CSI_CR2_DRM_MASK
#define CSI_CSICR2_DRM_SHIFT     CSI_CR2_DRM_SHIFT
#define CSI_CSICR2_DRM(x)     CSI_CR2_DRM(x)
#define CSI_CSICR2_DMA_BURST_TYPE_SFF_MASK     CSI_CR2_DMA_BURST_TYPE_SFF_MASK
#define CSI_CSICR2_DMA_BURST_TYPE_SFF_SHIFT     CSI_CR2_DMA_BURST_TYPE_SFF_SHIFT
#define CSI_CSICR2_DMA_BURST_TYPE_SFF(x)     CSI_CR2_DMA_BURST_TYPE_SFF(x)
#define CSI_CSICR2_DMA_BURST_TYPE_RFF_MASK     CSI_CR2_DMA_BURST_TYPE_RFF_MASK
#define CSI_CSICR2_DMA_BURST_TYPE_RFF_SHIFT     CSI_CR2_DMA_BURST_TYPE_RFF_SHIFT
#define CSI_CSICR2_DMA_BURST_TYPE_RFF(x)     CSI_CR2_DMA_BURST_TYPE_RFF(x)
#define CSI_CSICR3_ECC_AUTO_EN_MASK     CSI_CR3_ECC_AUTO_EN_MASK
#define CSI_CSICR3_ECC_AUTO_EN_SHIFT     CSI_CR3_ECC_AUTO_EN_SHIFT
#define CSI_CSICR3_ECC_AUTO_EN(x)     CSI_CR3_ECC_AUTO_EN(x)
#define CSI_CSICR3_ECC_INT_EN_MASK     CSI_CR3_ECC_INT_EN_MASK
#define CSI_CSICR3_ECC_INT_EN_SHIFT     CSI_CR3_ECC_INT_EN_SHIFT
#define CSI_CSICR3_ECC_INT_EN(x)     CSI_CR3_ECC_INT_EN(x)
#define CSI_CSICR3_ZERO_PACK_EN_MASK     CSI_CR3_ZERO_PACK_EN_MASK
#define CSI_CSICR3_ZERO_PACK_EN_SHIFT     CSI_CR3_ZERO_PACK_EN_SHIFT
#define CSI_CSICR3_ZERO_PACK_EN(x)     CSI_CR3_ZERO_PACK_EN(x)
#define CSI_CSICR3_SENSOR_16BITS_MASK     CSI_CR3_SENSOR_16BITS_MASK
#define CSI_CSICR3_SENSOR_16BITS_SHIFT     CSI_CR3_SENSOR_16BITS_SHIFT
#define CSI_CSICR3_SENSOR_16BITS(x)     CSI_CR3_SENSOR_16BITS(x)
#define CSI_CSICR3_RxFF_LEVEL_MASK     CSI_CR3_RxFF_LEVEL_MASK
#define CSI_CSICR3_RxFF_LEVEL_SHIFT     CSI_CR3_RxFF_LEVEL_SHIFT
#define CSI_CSICR3_RxFF_LEVEL(x)     CSI_CR3_RxFF_LEVEL(x)
#define CSI_CSICR3_HRESP_ERR_EN_MASK     CSI_CR3_HRESP_ERR_EN_MASK
#define CSI_CSICR3_HRESP_ERR_EN_SHIFT     CSI_CR3_HRESP_ERR_EN_SHIFT
#define CSI_CSICR3_HRESP_ERR_EN(x)     CSI_CR3_HRESP_ERR_EN(x)
#define CSI_CSICR3_STATFF_LEVEL_MASK     CSI_CR3_STATFF_LEVEL_MASK
#define CSI_CSICR3_STATFF_LEVEL_SHIFT     CSI_CR3_STATFF_LEVEL_SHIFT
#define CSI_CSICR3_STATFF_LEVEL(x)     CSI_CR3_STATFF_LEVEL(x)
#define CSI_CSICR3_DMA_REQ_EN_SFF_MASK     CSI_CR3_DMA_REQ_EN_SFF_MASK
#define CSI_CSICR3_DMA_REQ_EN_SFF_SHIFT     CSI_CR3_DMA_REQ_EN_SFF_SHIFT
#define CSI_CSICR3_DMA_REQ_EN_SFF(x)     CSI_CR3_DMA_REQ_EN_SFF(x)
#define CSI_CSICR3_DMA_REQ_EN_RFF_MASK     CSI_CR3_DMA_REQ_EN_RFF_MASK
#define CSI_CSICR3_DMA_REQ_EN_RFF_SHIFT     CSI_CR3_DMA_REQ_EN_RFF_SHIFT
#define CSI_CSICR3_DMA_REQ_EN_RFF(x)     CSI_CR3_DMA_REQ_EN_RFF(x)
#define CSI_CSICR3_DMA_REFLASH_SFF_MASK     CSI_CR3_DMA_REFLASH_SFF_MASK
#define CSI_CSICR3_DMA_REFLASH_SFF_SHIFT     CSI_CR3_DMA_REFLASH_SFF_SHIFT
#define CSI_CSICR3_DMA_REFLASH_SFF(x)     CSI_CR3_DMA_REFLASH_SFF(x)
#define CSI_CSICR3_DMA_REFLASH_RFF_MASK     CSI_CR3_DMA_REFLASH_RFF_MASK
#define CSI_CSICR3_DMA_REFLASH_RFF_SHIFT     CSI_CR3_DMA_REFLASH_RFF_SHIFT
#define CSI_CSICR3_DMA_REFLASH_RFF(x)     CSI_CR3_DMA_REFLASH_RFF(x)
#define CSI_CSICR3_FRMCNT_RST_MASK     CSI_CR3_FRMCNT_RST_MASK
#define CSI_CSICR3_FRMCNT_RST_SHIFT     CSI_CR3_FRMCNT_RST_SHIFT
#define CSI_CSICR3_FRMCNT_RST(x)     CSI_CR3_FRMCNT_RST(x)
#define CSI_CSICR3_FRMCNT_MASK     CSI_CR3_FRMCNT_MASK
#define CSI_CSICR3_FRMCNT_SHIFT     CSI_CR3_FRMCNT_SHIFT
#define CSI_CSICR3_FRMCNT(x)     CSI_CR3_FRMCNT(x)
#define CSI_CSISTATFIFO_STAT_MASK     CSI_STATFIFO_STAT_MASK
#define CSI_CSISTATFIFO_STAT_SHIFT     CSI_STATFIFO_STAT_SHIFT
#define CSI_CSISTATFIFO_STAT(x)     CSI_STATFIFO_STAT(x)
#define CSI_CSIRFIFO_IMAGE_MASK     CSI_RFIFO_IMAGE_MASK
#define CSI_CSIRFIFO_IMAGE_SHIFT     CSI_RFIFO_IMAGE_SHIFT
#define CSI_CSIRFIFO_IMAGE(x)     CSI_RFIFO_IMAGE(x)
#define CSI_CSIRXCNT_RXCNT_MASK     CSI_RXCNT_RXCNT_MASK
#define CSI_CSIRXCNT_RXCNT_SHIFT     CSI_RXCNT_RXCNT_SHIFT
#define CSI_CSIRXCNT_RXCNT(x)     CSI_RXCNT_RXCNT(x)
#define CSI_CSISR_DRDY_MASK     CSI_SR_DRDY_MASK
#define CSI_CSISR_DRDY_SHIFT     CSI_SR_DRDY_SHIFT
#define CSI_CSISR_DRDY(x)     CSI_SR_DRDY(x)
#define CSI_CSISR_ECC_INT_MASK     CSI_SR_ECC_INT_MASK
#define CSI_CSISR_ECC_INT_SHIFT     CSI_SR_ECC_INT_SHIFT
#define CSI_CSISR_ECC_INT(x)     CSI_SR_ECC_INT(x)
#define CSI_CSISR_HISTOGRAM_CALC_DONE_INT_MASK     CSI_SR_HISTOGRAM_CALC_DONE_INT_MASK
#define CSI_CSISR_HISTOGRAM_CALC_DONE_INT_SHIFT     CSI_SR_HISTOGRAM_CALC_DONE_INT_SHIFT
#define CSI_CSISR_HISTOGRAM_CALC_DONE_INT(x)     CSI_SR_HISTOGRAM_CALC_DONE_INT(x)
#define CSI_CSISR_HRESP_ERR_INT_MASK     CSI_SR_HRESP_ERR_INT_MASK
#define CSI_CSISR_HRESP_ERR_INT_SHIFT     CSI_SR_HRESP_ERR_INT_SHIFT
#define CSI_CSISR_HRESP_ERR_INT(x)     CSI_SR_HRESP_ERR_INT(x)
#define CSI_CSISR_COF_INT_MASK     CSI_SR_COF_INT_MASK
#define CSI_CSISR_COF_INT_SHIFT     CSI_SR_COF_INT_SHIFT
#define CSI_CSISR_COF_INT(x)     CSI_SR_COF_INT(x)
#define CSI_CSISR_F1_INT_MASK     CSI_SR_F1_INT_MASK
#define CSI_CSISR_F1_INT_SHIFT     CSI_SR_F1_INT_SHIFT
#define CSI_CSISR_F1_INT(x)     CSI_SR_F1_INT(x)
#define CSI_CSISR_F2_INT_MASK     CSI_SR_F2_INT_MASK
#define CSI_CSISR_F2_INT_SHIFT     CSI_SR_F2_INT_SHIFT
#define CSI_CSISR_F2_INT(x)     CSI_SR_F2_INT(x)
#define CSI_CSISR_SOF_INT_MASK     CSI_SR_SOF_INT_MASK
#define CSI_CSISR_SOF_INT_SHIFT     CSI_SR_SOF_INT_SHIFT
#define CSI_CSISR_SOF_INT(x)     CSI_SR_SOF_INT(x)
#define CSI_CSISR_EOF_INT_MASK     CSI_SR_EOF_INT_MASK
#define CSI_CSISR_EOF_INT_SHIFT     CSI_SR_EOF_INT_SHIFT
#define CSI_CSISR_EOF_INT(x)     CSI_SR_EOF_INT(x)
#define CSI_CSISR_RxFF_INT_MASK     CSI_SR_RxFF_INT_MASK
#define CSI_CSISR_RxFF_INT_SHIFT     CSI_SR_RxFF_INT_SHIFT
#define CSI_CSISR_RxFF_INT(x)     CSI_SR_RxFF_INT(x)
#define CSI_CSISR_DMA_TSF_DONE_FB1_MASK     CSI_SR_DMA_TSF_DONE_FB1_MASK
#define CSI_CSISR_DMA_TSF_DONE_FB1_SHIFT     CSI_SR_DMA_TSF_DONE_FB1_SHIFT
#define CSI_CSISR_DMA_TSF_DONE_FB1(x)     CSI_SR_DMA_TSF_DONE_FB1(x)
#define CSI_CSISR_DMA_TSF_DONE_FB2_MASK     CSI_SR_DMA_TSF_DONE_FB2_MASK
#define CSI_CSISR_DMA_TSF_DONE_FB2_SHIFT     CSI_SR_DMA_TSF_DONE_FB2_SHIFT
#define CSI_CSISR_DMA_TSF_DONE_FB2(x)     CSI_SR_DMA_TSF_DONE_FB2(x)
#define CSI_CSISR_STATFF_INT_MASK     CSI_SR_STATFF_INT_MASK
#define CSI_CSISR_STATFF_INT_SHIFT     CSI_SR_STATFF_INT_SHIFT
#define CSI_CSISR_STATFF_INT(x)     CSI_SR_STATFF_INT(x)
#define CSI_CSISR_DMA_TSF_DONE_SFF_MASK     CSI_SR_DMA_TSF_DONE_SFF_MASK
#define CSI_CSISR_DMA_TSF_DONE_SFF_SHIFT     CSI_SR_DMA_TSF_DONE_SFF_SHIFT
#define CSI_CSISR_DMA_TSF_DONE_SFF(x)     CSI_SR_DMA_TSF_DONE_SFF(x)
#define CSI_CSISR_RF_OR_INT_MASK     CSI_SR_RF_OR_INT_MASK
#define CSI_CSISR_RF_OR_INT_SHIFT     CSI_SR_RF_OR_INT_SHIFT
#define CSI_CSISR_RF_OR_INT(x)     CSI_SR_RF_OR_INT(x)
#define CSI_CSISR_SF_OR_INT_MASK     CSI_SR_SF_OR_INT_MASK
#define CSI_CSISR_SF_OR_INT_SHIFT     CSI_SR_SF_OR_INT_SHIFT
#define CSI_CSISR_SF_OR_INT(x)     CSI_SR_SF_OR_INT(x)
#define CSI_CSISR_DMA_FIELD1_DONE_MASK     CSI_SR_DMA_FIELD1_DONE_MASK
#define CSI_CSISR_DMA_FIELD1_DONE_SHIFT     CSI_SR_DMA_FIELD1_DONE_SHIFT
#define CSI_CSISR_DMA_FIELD1_DONE(x)     CSI_SR_DMA_FIELD1_DONE(x)
#define CSI_CSISR_DMA_FIELD0_DONE_MASK     CSI_SR_DMA_FIELD0_DONE_MASK
#define CSI_CSISR_DMA_FIELD0_DONE_SHIFT     CSI_SR_DMA_FIELD0_DONE_SHIFT
#define CSI_CSISR_DMA_FIELD0_DONE(x)     CSI_SR_DMA_FIELD0_DONE(x)
#define CSI_CSISR_BASEADDR_CHHANGE_ERROR_MASK     CSI_SR_BASEADDR_CHHANGE_ERROR_MASK
#define CSI_CSISR_BASEADDR_CHHANGE_ERROR_SHIFT     CSI_SR_BASEADDR_CHHANGE_ERROR_SHIFT
#define CSI_CSISR_BASEADDR_CHHANGE_ERROR(x)     CSI_SR_BASEADDR_CHHANGE_ERROR(x)
#define CSI_CSIDMASA_STATFIFO_DMA_START_ADDR_SFF_MASK     CSI_DMASA_STATFIFO_DMA_START_ADDR_SFF_MASK
#define CSI_CSIDMASA_STATFIFO_DMA_START_ADDR_SFF_SHIFT     CSI_DMASA_STATFIFO_DMA_START_ADDR_SFF_SHIFT
#define CSI_CSIDMASA_STATFIFO_DMA_START_ADDR_SFF(x)     CSI_DMASA_STATFIFO_DMA_START_ADDR_SFF(x)
#define CSI_CSIDMATS_STATFIFO_DMA_TSF_SIZE_SFF_MASK     CSI_DMATS_STATFIFO_DMA_TSF_SIZE_SFF_MASK
#define CSI_CSIDMATS_STATFIFO_DMA_TSF_SIZE_SFF_SHIFT     CSI_DMATS_STATFIFO_DMA_TSF_SIZE_SFF_SHIFT
#define CSI_CSIDMATS_STATFIFO_DMA_TSF_SIZE_SFF(x)     CSI_DMATS_STATFIFO_DMA_TSF_SIZE_SFF(x)
#define CSI_CSIDMASA_FB1_DMA_START_ADDR_FB1_MASK     CSI_DMASA_FB1_DMA_START_ADDR_FB1_MASK
#define CSI_CSIDMASA_FB1_DMA_START_ADDR_FB1_SHIFT     CSI_DMASA_FB1_DMA_START_ADDR_FB1_SHIFT
#define CSI_CSIDMASA_FB1_DMA_START_ADDR_FB1(x)     CSI_DMASA_FB1_DMA_START_ADDR_FB1(x)
#define CSI_CSIDMASA_FB2_DMA_START_ADDR_FB2_MASK     CSI_DMASA_FB2_DMA_START_ADDR_FB2_MASK
#define CSI_CSIDMASA_FB2_DMA_START_ADDR_FB2_SHIFT     CSI_DMASA_FB2_DMA_START_ADDR_FB2_SHIFT
#define CSI_CSIDMASA_FB2_DMA_START_ADDR_FB2(x)     CSI_DMASA_FB2_DMA_START_ADDR_FB2(x)
#define CSI_CSIFBUF_PARA_FBUF_STRIDE_MASK     CSI_FBUF_PARA_FBUF_STRIDE_MASK
#define CSI_CSIFBUF_PARA_FBUF_STRIDE_SHIFT     CSI_FBUF_PARA_FBUF_STRIDE_SHIFT
#define CSI_CSIFBUF_PARA_FBUF_STRIDE(x)     CSI_FBUF_PARA_FBUF_STRIDE(x)
#define CSI_CSIFBUF_PARA_DEINTERLACE_STRIDE_MASK     CSI_FBUF_PARA_DEINTERLACE_STRIDE_MASK
#define CSI_CSIFBUF_PARA_DEINTERLACE_STRIDE_SHIFT     CSI_FBUF_PARA_DEINTERLACE_STRIDE_SHIFT
#define CSI_CSIFBUF_PARA_DEINTERLACE_STRIDE(x)     CSI_FBUF_PARA_DEINTERLACE_STRIDE(x)
#define CSI_CSIIMAG_PARA_IMAGE_HEIGHT_MASK     CSI_IMAG_PARA_IMAGE_HEIGHT_MASK
#define CSI_CSIIMAG_PARA_IMAGE_HEIGHT_SHIFT     CSI_IMAG_PARA_IMAGE_HEIGHT_SHIFT
#define CSI_CSIIMAG_PARA_IMAGE_HEIGHT(x)     CSI_IMAG_PARA_IMAGE_HEIGHT(x)
#define CSI_CSIIMAG_PARA_IMAGE_WIDTH_MASK     CSI_IMAG_PARA_IMAGE_WIDTH_MASK
#define CSI_CSIIMAG_PARA_IMAGE_WIDTH_SHIFT     CSI_IMAG_PARA_IMAGE_WIDTH_SHIFT
#define CSI_CSIIMAG_PARA_IMAGE_WIDTH(x)     CSI_IMAG_PARA_IMAGE_WIDTH(x)
#define CSI_CSICR18_NTSC_EN_MASK     CSI_CR18_NTSC_EN_MASK
#define CSI_CSICR18_NTSC_EN_SHIFT     CSI_CR18_NTSC_EN_SHIFT
#define CSI_CSICR18_NTSC_EN(x)     CSI_CR18_NTSC_EN(x)
#define CSI_CSICR18_TVDECODER_IN_EN_MASK     CSI_CR18_TVDECODER_IN_EN_MASK
#define CSI_CSICR18_TVDECODER_IN_EN_SHIFT     CSI_CR18_TVDECODER_IN_EN_SHIFT
#define CSI_CSICR18_TVDECODER_IN_EN(x)     CSI_CR18_TVDECODER_IN_EN(x)
#define CSI_CSICR18_DEINTERLACE_EN_MASK     CSI_CR18_DEINTERLACE_EN_MASK
#define CSI_CSICR18_DEINTERLACE_EN_SHIFT     CSI_CR18_DEINTERLACE_EN_SHIFT
#define CSI_CSICR18_DEINTERLACE_EN(x)     CSI_CR18_DEINTERLACE_EN(x)
#define CSI_CSICR18_PARALLEL24_EN_MASK     CSI_CR18_PARALLEL24_EN_MASK
#define CSI_CSICR18_PARALLEL24_EN_SHIFT     CSI_CR18_PARALLEL24_EN_SHIFT
#define CSI_CSICR18_PARALLEL24_EN(x)     CSI_CR18_PARALLEL24_EN(x)
#define CSI_CSICR18_BASEADDR_SWITCH_EN_MASK     CSI_CR18_BASEADDR_SWITCH_EN_MASK
#define CSI_CSICR18_BASEADDR_SWITCH_EN_SHIFT     CSI_CR18_BASEADDR_SWITCH_EN_SHIFT
#define CSI_CSICR18_BASEADDR_SWITCH_EN(x)     CSI_CR18_BASEADDR_SWITCH_EN(x)
#define CSI_CSICR18_BASEADDR_SWITCH_SEL_MASK     CSI_CR18_BASEADDR_SWITCH_SEL_MASK
#define CSI_CSICR18_BASEADDR_SWITCH_SEL_SHIFT     CSI_CR18_BASEADDR_SWITCH_SEL_SHIFT
#define CSI_CSICR18_BASEADDR_SWITCH_SEL(x)     CSI_CR18_BASEADDR_SWITCH_SEL(x)
#define CSI_CSICR18_FIELD0_DONE_IE_MASK     CSI_CR18_FIELD0_DONE_IE_MASK
#define CSI_CSICR18_FIELD0_DONE_IE_SHIFT     CSI_CR18_FIELD0_DONE_IE_SHIFT
#define CSI_CSICR18_FIELD0_DONE_IE(x)     CSI_CR18_FIELD0_DONE_IE(x)
#define CSI_CSICR18_DMA_FIELD1_DONE_IE_MASK     CSI_CR18_DMA_FIELD1_DONE_IE_MASK
#define CSI_CSICR18_DMA_FIELD1_DONE_IE_SHIFT     CSI_CR18_DMA_FIELD1_DONE_IE_SHIFT
#define CSI_CSICR18_DMA_FIELD1_DONE_IE(x)     CSI_CR18_DMA_FIELD1_DONE_IE(x)
#define CSI_CSICR18_LAST_DMA_REQ_SEL_MASK     CSI_CR18_LAST_DMA_REQ_SEL_MASK
#define CSI_CSICR18_LAST_DMA_REQ_SEL_SHIFT     CSI_CR18_LAST_DMA_REQ_SEL_SHIFT
#define CSI_CSICR18_LAST_DMA_REQ_SEL(x)     CSI_CR18_LAST_DMA_REQ_SEL(x)
#define CSI_CSICR18_BASEADDR_CHANGE_ERROR_IE_MASK     CSI_CR18_BASEADDR_CHANGE_ERROR_IE_MASK
#define CSI_CSICR18_BASEADDR_CHANGE_ERROR_IE_SHIFT     CSI_CR18_BASEADDR_CHANGE_ERROR_IE_SHIFT
#define CSI_CSICR18_BASEADDR_CHANGE_ERROR_IE(x)     CSI_CR18_BASEADDR_CHANGE_ERROR_IE(x)
#define CSI_CSICR18_RGB888A_FORMAT_SEL_MASK     CSI_CR18_RGB888A_FORMAT_SEL_MASK
#define CSI_CSICR18_RGB888A_FORMAT_SEL_SHIFT     CSI_CR18_RGB888A_FORMAT_SEL_SHIFT
#define CSI_CSICR18_RGB888A_FORMAT_SEL(x)     CSI_CR18_RGB888A_FORMAT_SEL(x)
#define CSI_CSICR18_AHB_HPROT_MASK     CSI_CR18_AHB_HPROT_MASK
#define CSI_CSICR18_AHB_HPROT_SHIFT     CSI_CR18_AHB_HPROT_SHIFT
#define CSI_CSICR18_AHB_HPROT(x)     CSI_CR18_AHB_HPROT(x)
#define CSI_CSICR18_MASK_OPTION_MASK     CSI_CR18_MASK_OPTION_MASK
#define CSI_CSICR18_MASK_OPTION_SHIFT     CSI_CR18_MASK_OPTION_SHIFT
#define CSI_CSICR18_MASK_OPTION(x)     CSI_CR18_MASK_OPTION(x)
#define CSI_CSICR18_MIPI_DOUBLE_CMPNT_MASK     CSI_CR18_MIPI_DOUBLE_CMPNT_MASK
#define CSI_CSICR18_MIPI_DOUBLE_CMPNT_SHIFT     CSI_CR18_MIPI_DOUBLE_CMPNT_SHIFT
#define CSI_CSICR18_MIPI_DOUBLE_CMPNT(x)     CSI_CR18_MIPI_DOUBLE_CMPNT(x)
#define CSI_CSICR18_MIPI_YU_SWAP_MASK     CSI_CR18_MIPI_YU_SWAP_MASK
#define CSI_CSICR18_MIPI_YU_SWAP_SHIFT     CSI_CR18_MIPI_YU_SWAP_SHIFT
#define CSI_CSICR18_MIPI_YU_SWAP(x)     CSI_CR18_MIPI_YU_SWAP(x)
#define CSI_CSICR18_DATA_FROM_MIPI_MASK     CSI_CR18_DATA_FROM_MIPI_MASK
#define CSI_CSICR18_DATA_FROM_MIPI_SHIFT     CSI_CR18_DATA_FROM_MIPI_SHIFT
#define CSI_CSICR18_DATA_FROM_MIPI(x)     CSI_CR18_DATA_FROM_MIPI(x)
#define CSI_CSICR18_LINE_STRIDE_EN_MASK     CSI_CR18_LINE_STRIDE_EN_MASK
#define CSI_CSICR18_LINE_STRIDE_EN_SHIFT     CSI_CR18_LINE_STRIDE_EN_SHIFT
#define CSI_CSICR18_LINE_STRIDE_EN(x)     CSI_CR18_LINE_STRIDE_EN(x)
#define CSI_CSICR18_MIPI_DATA_FORMAT_MASK     CSI_CR18_MIPI_DATA_FORMAT_MASK
#define CSI_CSICR18_MIPI_DATA_FORMAT_SHIFT     CSI_CR18_MIPI_DATA_FORMAT_SHIFT
#define CSI_CSICR18_MIPI_DATA_FORMAT(x)     CSI_CR18_MIPI_DATA_FORMAT(x)
#define CSI_CSICR18_CSI_ENABLE_MASK     CSI_CR18_CSI_ENABLE_MASK
#define CSI_CSICR18_CSI_ENABLE_SHIFT     CSI_CR18_CSI_ENABLE_SHIFT
#define CSI_CSICR18_CSI_ENABLE(x)     CSI_CR18_CSI_ENABLE(x)
#define CSI_CSICR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL_MASK     CSI_CR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL_MASK
#define CSI_CSICR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL_SHIFT     CSI_CR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL_SHIFT
#define CSI_CSICR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL(x)     CSI_CR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL(x)
#define CSI_CSICR20_THRESHOLD_MASK     CSI_CR20_THRESHOLD_MASK
#define CSI_CSICR20_THRESHOLD_SHIFT     CSI_CR20_THRESHOLD_SHIFT
#define CSI_CSICR20_THRESHOLD(x)     CSI_CR20_THRESHOLD(x)
#define CSI_CSICR20_BINARY_EN_MASK     CSI_CR20_BINARY_EN_MASK
#define CSI_CSICR20_BINARY_EN_SHIFT     CSI_CR20_BINARY_EN_SHIFT
#define CSI_CSICR20_BINARY_EN(x)     CSI_CR20_BINARY_EN(x)
#define CSI_CSICR20_QR_DATA_FORMAT_MASK     CSI_CR20_QR_DATA_FORMAT_MASK
#define CSI_CSICR20_QR_DATA_FORMAT_SHIFT     CSI_CR20_QR_DATA_FORMAT_SHIFT
#define CSI_CSICR20_QR_DATA_FORMAT(x)     CSI_CR20_QR_DATA_FORMAT(x)
#define CSI_CSICR20_BIG_END_MASK     CSI_CR20_BIG_END_MASK
#define CSI_CSICR20_BIG_END_SHIFT     CSI_CR20_BIG_END_SHIFT
#define CSI_CSICR20_BIG_END(x)     CSI_CR20_BIG_END(x)
#define CSI_CSICR20_10BIT_NEW_EN_MASK     CSI_CR20_10BIT_NEW_EN_MASK
#define CSI_CSICR20_10BIT_NEW_EN_SHIFT     CSI_CR20_10BIT_NEW_EN_SHIFT
#define CSI_CSICR20_10BIT_NEW_EN(x)     CSI_CR20_10BIT_NEW_EN(x)
#define CSI_CSICR20_HISTOGRAM_EN_MASK     CSI_CR20_HISTOGRAM_EN_MASK
#define CSI_CSICR20_HISTOGRAM_EN_SHIFT     CSI_CR20_HISTOGRAM_EN_SHIFT
#define CSI_CSICR20_HISTOGRAM_EN(x)     CSI_CR20_HISTOGRAM_EN(x)
#define CSI_CSICR20_QRCODE_EN_MASK     CSI_CR20_QRCODE_EN_MASK
#define CSI_CSICR20_QRCODE_EN_SHIFT     CSI_CR20_QRCODE_EN_SHIFT
#define CSI_CSICR20_QRCODE_EN(x)     CSI_CR20_QRCODE_EN(x)
#define CSI_CSICR21_PIXEL_COUNTERS_MASK     CSI_CR21_PIXEL_COUNTERS_MASK
#define CSI_CSICR21_PIXEL_COUNTERS_SHIFT     CSI_CR21_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR21_PIXEL_COUNTERS(x)     CSI_CR21_PIXEL_COUNTERS(x)
#define CSI_CSICR22_PIXEL_COUNTERS_MASK     CSI_CR22_PIXEL_COUNTERS_MASK
#define CSI_CSICR22_PIXEL_COUNTERS_SHIFT     CSI_CR22_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR22_PIXEL_COUNTERS(x)     CSI_CR22_PIXEL_COUNTERS(x)
#define CSI_CSICR23_PIXEL_COUNTERS_MASK     CSI_CR23_PIXEL_COUNTERS_MASK
#define CSI_CSICR23_PIXEL_COUNTERS_SHIFT     CSI_CR23_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR23_PIXEL_COUNTERS(x)     CSI_CR23_PIXEL_COUNTERS(x)
#define CSI_CSICR24_PIXEL_COUNTERS_MASK     CSI_CR24_PIXEL_COUNTERS_MASK
#define CSI_CSICR24_PIXEL_COUNTERS_SHIFT     CSI_CR24_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR24_PIXEL_COUNTERS(x)     CSI_CR24_PIXEL_COUNTERS(x)
#define CSI_CSICR25_PIXEL_COUNTERS_MASK     CSI_CR25_PIXEL_COUNTERS_MASK
#define CSI_CSICR25_PIXEL_COUNTERS_SHIFT     CSI_CR25_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR25_PIXEL_COUNTERS(x)     CSI_CR25_PIXEL_COUNTERS(x)
#define CSI_CSICR26_PIXEL_COUNTERS_MASK     CSI_CR26_PIXEL_COUNTERS_MASK
#define CSI_CSICR26_PIXEL_COUNTERS_SHIFT     CSI_CR26_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR26_PIXEL_COUNTERS(x)     CSI_CR26_PIXEL_COUNTERS(x)
#define CSI_CSICR27_PIXEL_COUNTERS_MASK     CSI_CR27_PIXEL_COUNTERS_MASK
#define CSI_CSICR27_PIXEL_COUNTERS_SHIFT     CSI_CR27_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR27_PIXEL_COUNTERS(x)     CSI_CR27_PIXEL_COUNTERS(x)
#define CSI_CSICR28_PIXEL_COUNTERS_MASK     CSI_CR28_PIXEL_COUNTERS_MASK
#define CSI_CSICR28_PIXEL_COUNTERS_SHIFT     CSI_CR28_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR28_PIXEL_COUNTERS(x)     CSI_CR28_PIXEL_COUNTERS(x)
#define CSI_CSICR29_PIXEL_COUNTERS_MASK     CSI_CR29_PIXEL_COUNTERS_MASK
#define CSI_CSICR29_PIXEL_COUNTERS_SHIFT     CSI_CR29_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR29_PIXEL_COUNTERS(x)     CSI_CR29_PIXEL_COUNTERS(x)
#define CSI_CSICR30_PIXEL_COUNTERS_MASK     CSI_CR30_PIXEL_COUNTERS_MASK
#define CSI_CSICR30_PIXEL_COUNTERS_SHIFT     CSI_CR30_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR30_PIXEL_COUNTERS(x)     CSI_CR30_PIXEL_COUNTERS(x)
#define CSI_CSICR31_PIXEL_COUNTERS_MASK     CSI_CR31_PIXEL_COUNTERS_MASK
#define CSI_CSICR31_PIXEL_COUNTERS_SHIFT     CSI_CR31_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR31_PIXEL_COUNTERS(x)     CSI_CR31_PIXEL_COUNTERS(x)
#define CSI_CSICR32_PIXEL_COUNTERS_MASK     CSI_CR32_PIXEL_COUNTERS_MASK
#define CSI_CSICR32_PIXEL_COUNTERS_SHIFT     CSI_CR32_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR32_PIXEL_COUNTERS(x)     CSI_CR32_PIXEL_COUNTERS(x)
#define CSI_CSICR33_PIXEL_COUNTERS_MASK     CSI_CR33_PIXEL_COUNTERS_MASK
#define CSI_CSICR33_PIXEL_COUNTERS_SHIFT     CSI_CR33_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR33_PIXEL_COUNTERS(x)     CSI_CR33_PIXEL_COUNTERS(x)
#define CSI_CSICR34_PIXEL_COUNTERS_MASK     CSI_CR34_PIXEL_COUNTERS_MASK
#define CSI_CSICR34_PIXEL_COUNTERS_SHIFT     CSI_CR34_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR34_PIXEL_COUNTERS(x)     CSI_CR34_PIXEL_COUNTERS(x)
#define CSI_CSICR35_PIXEL_COUNTERS_MASK     CSI_CR35_PIXEL_COUNTERS_MASK
#define CSI_CSICR35_PIXEL_COUNTERS_SHIFT     CSI_CR35_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR35_PIXEL_COUNTERS(x)     CSI_CR35_PIXEL_COUNTERS(x)
#define CSI_CSICR36_PIXEL_COUNTERS_MASK     CSI_CR36_PIXEL_COUNTERS_MASK
#define CSI_CSICR36_PIXEL_COUNTERS_SHIFT     CSI_CR36_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR36_PIXEL_COUNTERS(x)     CSI_CR36_PIXEL_COUNTERS(x)
#define CSI_CSICR37_PIXEL_COUNTERS_MASK     CSI_CR37_PIXEL_COUNTERS_MASK
#define CSI_CSICR37_PIXEL_COUNTERS_SHIFT     CSI_CR37_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR37_PIXEL_COUNTERS(x)     CSI_CR37_PIXEL_COUNTERS(x)
#define CSI_CSICR38_PIXEL_COUNTERS_MASK     CSI_CR38_PIXEL_COUNTERS_MASK
#define CSI_CSICR38_PIXEL_COUNTERS_SHIFT     CSI_CR38_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR38_PIXEL_COUNTERS(x)     CSI_CR38_PIXEL_COUNTERS(x)
#define CSI_CSICR39_PIXEL_COUNTERS_MASK     CSI_CR39_PIXEL_COUNTERS_MASK
#define CSI_CSICR39_PIXEL_COUNTERS_SHIFT     CSI_CR39_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR39_PIXEL_COUNTERS(x)     CSI_CR39_PIXEL_COUNTERS(x)
#define CSI_CSICR40_PIXEL_COUNTERS_MASK     CSI_CR40_PIXEL_COUNTERS_MASK
#define CSI_CSICR40_PIXEL_COUNTERS_SHIFT     CSI_CR40_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR40_PIXEL_COUNTERS(x)     CSI_CR40_PIXEL_COUNTERS(x)
#define CSI_CSICR41_PIXEL_COUNTERS_MASK     CSI_CR41_PIXEL_COUNTERS_MASK
#define CSI_CSICR41_PIXEL_COUNTERS_SHIFT     CSI_CR41_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR41_PIXEL_COUNTERS(x)     CSI_CR41_PIXEL_COUNTERS(x)
#define CSI_CSICR42_PIXEL_COUNTERS_MASK     CSI_CR42_PIXEL_COUNTERS_MASK
#define CSI_CSICR42_PIXEL_COUNTERS_SHIFT     CSI_CR42_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR42_PIXEL_COUNTERS(x)     CSI_CR42_PIXEL_COUNTERS(x)
#define CSI_CSICR43_PIXEL_COUNTERS_MASK     CSI_CR43_PIXEL_COUNTERS_MASK
#define CSI_CSICR43_PIXEL_COUNTERS_SHIFT     CSI_CR43_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR43_PIXEL_COUNTERS(x)     CSI_CR43_PIXEL_COUNTERS(x)
#define CSI_CSICR44_PIXEL_COUNTERS_MASK     CSI_CR44_PIXEL_COUNTERS_MASK
#define CSI_CSICR44_PIXEL_COUNTERS_SHIFT     CSI_CR44_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR44_PIXEL_COUNTERS(x)     CSI_CR44_PIXEL_COUNTERS(x)
#define CSI_CSICR45_PIXEL_COUNTERS_MASK     CSI_CR45_PIXEL_COUNTERS_MASK
#define CSI_CSICR45_PIXEL_COUNTERS_SHIFT     CSI_CR45_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR45_PIXEL_COUNTERS(x)     CSI_CR45_PIXEL_COUNTERS(x)
#define CSI_CSICR46_PIXEL_COUNTERS_MASK     CSI_CR46_PIXEL_COUNTERS_MASK
#define CSI_CSICR46_PIXEL_COUNTERS_SHIFT     CSI_CR46_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR46_PIXEL_COUNTERS(x)     CSI_CR46_PIXEL_COUNTERS(x)
#define CSI_CSICR47_PIXEL_COUNTERS_MASK     CSI_CR47_PIXEL_COUNTERS_MASK
#define CSI_CSICR47_PIXEL_COUNTERS_SHIFT     CSI_CR47_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR47_PIXEL_COUNTERS(x)     CSI_CR47_PIXEL_COUNTERS(x)
#define CSI_CSICR48_PIXEL_COUNTERS_MASK     CSI_CR48_PIXEL_COUNTERS_MASK
#define CSI_CSICR48_PIXEL_COUNTERS_SHIFT     CSI_CR48_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR48_PIXEL_COUNTERS(x)     CSI_CR48_PIXEL_COUNTERS(x)
#define CSI_CSICR49_PIXEL_COUNTERS_MASK     CSI_CR49_PIXEL_COUNTERS_MASK
#define CSI_CSICR49_PIXEL_COUNTERS_SHIFT     CSI_CR49_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR49_PIXEL_COUNTERS(x)     CSI_CR49_PIXEL_COUNTERS(x)
#define CSI_CSICR50_PIXEL_COUNTERS_MASK     CSI_CR50_PIXEL_COUNTERS_MASK
#define CSI_CSICR50_PIXEL_COUNTERS_SHIFT     CSI_CR50_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR50_PIXEL_COUNTERS(x)     CSI_CR50_PIXEL_COUNTERS(x)
#define CSI_CSICR51_PIXEL_COUNTERS_MASK     CSI_CR51_PIXEL_COUNTERS_MASK
#define CSI_CSICR51_PIXEL_COUNTERS_SHIFT     CSI_CR51_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR51_PIXEL_COUNTERS(x)     CSI_CR51_PIXEL_COUNTERS(x)
#define CSI_CSICR52_PIXEL_COUNTERS_MASK     CSI_CR52_PIXEL_COUNTERS_MASK
#define CSI_CSICR52_PIXEL_COUNTERS_SHIFT     CSI_CR52_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR52_PIXEL_COUNTERS(x)     CSI_CR52_PIXEL_COUNTERS(x)
#define CSI_CSICR53_PIXEL_COUNTERS_MASK     CSI_CR53_PIXEL_COUNTERS_MASK
#define CSI_CSICR53_PIXEL_COUNTERS_SHIFT     CSI_CR53_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR53_PIXEL_COUNTERS(x)     CSI_CR53_PIXEL_COUNTERS(x)
#define CSI_CSICR54_PIXEL_COUNTERS_MASK     CSI_CR54_PIXEL_COUNTERS_MASK
#define CSI_CSICR54_PIXEL_COUNTERS_SHIFT     CSI_CR54_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR54_PIXEL_COUNTERS(x)     CSI_CR54_PIXEL_COUNTERS(x)
#define CSI_CSICR55_PIXEL_COUNTERS_MASK     CSI_CR55_PIXEL_COUNTERS_MASK
#define CSI_CSICR55_PIXEL_COUNTERS_SHIFT     CSI_CR55_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR55_PIXEL_COUNTERS(x)     CSI_CR55_PIXEL_COUNTERS(x)
#define CSI_CSICR56_PIXEL_COUNTERS_MASK     CSI_CR56_PIXEL_COUNTERS_MASK
#define CSI_CSICR56_PIXEL_COUNTERS_SHIFT     CSI_CR56_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR56_PIXEL_COUNTERS(x)     CSI_CR56_PIXEL_COUNTERS(x)
#define CSI_CSICR57_PIXEL_COUNTERS_MASK     CSI_CR57_PIXEL_COUNTERS_MASK
#define CSI_CSICR57_PIXEL_COUNTERS_SHIFT     CSI_CR57_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR57_PIXEL_COUNTERS(x)     CSI_CR57_PIXEL_COUNTERS(x)
#define CSI_CSICR58_PIXEL_COUNTERS_MASK     CSI_CR58_PIXEL_COUNTERS_MASK
#define CSI_CSICR58_PIXEL_COUNTERS_SHIFT     CSI_CR58_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR58_PIXEL_COUNTERS(x)     CSI_CR58_PIXEL_COUNTERS(x)
#define CSI_CSICR59_PIXEL_COUNTERS_MASK     CSI_CR59_PIXEL_COUNTERS_MASK
#define CSI_CSICR59_PIXEL_COUNTERS_SHIFT     CSI_CR59_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR59_PIXEL_COUNTERS(x)     CSI_CR59_PIXEL_COUNTERS(x)
#define CSI_CSICR60_PIXEL_COUNTERS_MASK     CSI_CR60_PIXEL_COUNTERS_MASK
#define CSI_CSICR60_PIXEL_COUNTERS_SHIFT     CSI_CR60_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR60_PIXEL_COUNTERS(x)     CSI_CR60_PIXEL_COUNTERS(x)
#define CSI_CSICR61_PIXEL_COUNTERS_MASK     CSI_CR61_PIXEL_COUNTERS_MASK
#define CSI_CSICR61_PIXEL_COUNTERS_SHIFT     CSI_CR61_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR61_PIXEL_COUNTERS(x)     CSI_CR61_PIXEL_COUNTERS(x)
#define CSI_CSICR62_PIXEL_COUNTERS_MASK     CSI_CR62_PIXEL_COUNTERS_MASK
#define CSI_CSICR62_PIXEL_COUNTERS_SHIFT     CSI_CR62_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR62_PIXEL_COUNTERS(x)     CSI_CR62_PIXEL_COUNTERS(x)
#define CSI_CSICR63_PIXEL_COUNTERS_MASK     CSI_CR63_PIXEL_COUNTERS_MASK
#define CSI_CSICR63_PIXEL_COUNTERS_SHIFT     CSI_CR63_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR63_PIXEL_COUNTERS(x)     CSI_CR63_PIXEL_COUNTERS(x)
#define CSI_CSICR64_PIXEL_COUNTERS_MASK     CSI_CR64_PIXEL_COUNTERS_MASK
#define CSI_CSICR64_PIXEL_COUNTERS_SHIFT     CSI_CR64_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR64_PIXEL_COUNTERS(x)     CSI_CR64_PIXEL_COUNTERS(x)
#define CSI_CSICR65_PIXEL_COUNTERS_MASK     CSI_CR65_PIXEL_COUNTERS_MASK
#define CSI_CSICR65_PIXEL_COUNTERS_SHIFT     CSI_CR65_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR65_PIXEL_COUNTERS(x)     CSI_CR65_PIXEL_COUNTERS(x)
#define CSI_CSICR66_PIXEL_COUNTERS_MASK     CSI_CR66_PIXEL_COUNTERS_MASK
#define CSI_CSICR66_PIXEL_COUNTERS_SHIFT     CSI_CR66_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR66_PIXEL_COUNTERS(x)     CSI_CR66_PIXEL_COUNTERS(x)
#define CSI_CSICR67_PIXEL_COUNTERS_MASK     CSI_CR67_PIXEL_COUNTERS_MASK
#define CSI_CSICR67_PIXEL_COUNTERS_SHIFT     CSI_CR67_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR67_PIXEL_COUNTERS(x)     CSI_CR67_PIXEL_COUNTERS(x)
#define CSI_CSICR68_PIXEL_COUNTERS_MASK     CSI_CR68_PIXEL_COUNTERS_MASK
#define CSI_CSICR68_PIXEL_COUNTERS_SHIFT     CSI_CR68_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR68_PIXEL_COUNTERS(x)     CSI_CR68_PIXEL_COUNTERS(x)
#define CSI_CSICR69_PIXEL_COUNTERS_MASK     CSI_CR69_PIXEL_COUNTERS_MASK
#define CSI_CSICR69_PIXEL_COUNTERS_SHIFT     CSI_CR69_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR69_PIXEL_COUNTERS(x)     CSI_CR69_PIXEL_COUNTERS(x)
#define CSI_CSICR70_PIXEL_COUNTERS_MASK     CSI_CR70_PIXEL_COUNTERS_MASK
#define CSI_CSICR70_PIXEL_COUNTERS_SHIFT     CSI_CR70_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR70_PIXEL_COUNTERS(x)     CSI_CR70_PIXEL_COUNTERS(x)
#define CSI_CSICR71_PIXEL_COUNTERS_MASK     CSI_CR71_PIXEL_COUNTERS_MASK
#define CSI_CSICR71_PIXEL_COUNTERS_SHIFT     CSI_CR71_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR71_PIXEL_COUNTERS(x)     CSI_CR71_PIXEL_COUNTERS(x)
#define CSI_CSICR72_PIXEL_COUNTERS_MASK     CSI_CR72_PIXEL_COUNTERS_MASK
#define CSI_CSICR72_PIXEL_COUNTERS_SHIFT     CSI_CR72_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR72_PIXEL_COUNTERS(x)     CSI_CR72_PIXEL_COUNTERS(x)
#define CSI_CSICR73_PIXEL_COUNTERS_MASK     CSI_CR73_PIXEL_COUNTERS_MASK
#define CSI_CSICR73_PIXEL_COUNTERS_SHIFT     CSI_CR73_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR73_PIXEL_COUNTERS(x)     CSI_CR73_PIXEL_COUNTERS(x)
#define CSI_CSICR74_PIXEL_COUNTERS_MASK     CSI_CR74_PIXEL_COUNTERS_MASK
#define CSI_CSICR74_PIXEL_COUNTERS_SHIFT     CSI_CR74_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR74_PIXEL_COUNTERS(x)     CSI_CR74_PIXEL_COUNTERS(x)
#define CSI_CSICR75_PIXEL_COUNTERS_MASK     CSI_CR75_PIXEL_COUNTERS_MASK
#define CSI_CSICR75_PIXEL_COUNTERS_SHIFT     CSI_CR75_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR75_PIXEL_COUNTERS(x)     CSI_CR75_PIXEL_COUNTERS(x)
#define CSI_CSICR76_PIXEL_COUNTERS_MASK     CSI_CR76_PIXEL_COUNTERS_MASK
#define CSI_CSICR76_PIXEL_COUNTERS_SHIFT     CSI_CR76_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR76_PIXEL_COUNTERS(x)     CSI_CR76_PIXEL_COUNTERS(x)
#define CSI_CSICR77_PIXEL_COUNTERS_MASK     CSI_CR77_PIXEL_COUNTERS_MASK
#define CSI_CSICR77_PIXEL_COUNTERS_SHIFT     CSI_CR77_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR77_PIXEL_COUNTERS(x)     CSI_CR77_PIXEL_COUNTERS(x)
#define CSI_CSICR78_PIXEL_COUNTERS_MASK     CSI_CR78_PIXEL_COUNTERS_MASK
#define CSI_CSICR78_PIXEL_COUNTERS_SHIFT     CSI_CR78_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR78_PIXEL_COUNTERS(x)     CSI_CR78_PIXEL_COUNTERS(x)
#define CSI_CSICR79_PIXEL_COUNTERS_MASK     CSI_CR79_PIXEL_COUNTERS_MASK
#define CSI_CSICR79_PIXEL_COUNTERS_SHIFT     CSI_CR79_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR79_PIXEL_COUNTERS(x)     CSI_CR79_PIXEL_COUNTERS(x)
#define CSI_CSICR80_PIXEL_COUNTERS_MASK     CSI_CR80_PIXEL_COUNTERS_MASK
#define CSI_CSICR80_PIXEL_COUNTERS_SHIFT     CSI_CR80_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR80_PIXEL_COUNTERS(x)     CSI_CR80_PIXEL_COUNTERS(x)
#define CSI_CSICR81_PIXEL_COUNTERS_MASK     CSI_CR81_PIXEL_COUNTERS_MASK
#define CSI_CSICR81_PIXEL_COUNTERS_SHIFT     CSI_CR81_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR81_PIXEL_COUNTERS(x)     CSI_CR81_PIXEL_COUNTERS(x)
#define CSI_CSICR82_PIXEL_COUNTERS_MASK     CSI_CR82_PIXEL_COUNTERS_MASK
#define CSI_CSICR82_PIXEL_COUNTERS_SHIFT     CSI_CR82_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR82_PIXEL_COUNTERS(x)     CSI_CR82_PIXEL_COUNTERS(x)
#define CSI_CSICR83_PIXEL_COUNTERS_MASK     CSI_CR83_PIXEL_COUNTERS_MASK
#define CSI_CSICR83_PIXEL_COUNTERS_SHIFT     CSI_CR83_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR83_PIXEL_COUNTERS(x)     CSI_CR83_PIXEL_COUNTERS(x)
#define CSI_CSICR84_PIXEL_COUNTERS_MASK     CSI_CR84_PIXEL_COUNTERS_MASK
#define CSI_CSICR84_PIXEL_COUNTERS_SHIFT     CSI_CR84_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR84_PIXEL_COUNTERS(x)     CSI_CR84_PIXEL_COUNTERS(x)
#define CSI_CSICR85_PIXEL_COUNTERS_MASK     CSI_CR85_PIXEL_COUNTERS_MASK
#define CSI_CSICR85_PIXEL_COUNTERS_SHIFT     CSI_CR85_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR85_PIXEL_COUNTERS(x)     CSI_CR85_PIXEL_COUNTERS(x)
#define CSI_CSICR86_PIXEL_COUNTERS_MASK     CSI_CR86_PIXEL_COUNTERS_MASK
#define CSI_CSICR86_PIXEL_COUNTERS_SHIFT     CSI_CR86_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR86_PIXEL_COUNTERS(x)     CSI_CR86_PIXEL_COUNTERS(x)
#define CSI_CSICR87_PIXEL_COUNTERS_MASK     CSI_CR87_PIXEL_COUNTERS_MASK
#define CSI_CSICR87_PIXEL_COUNTERS_SHIFT     CSI_CR87_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR87_PIXEL_COUNTERS(x)     CSI_CR87_PIXEL_COUNTERS(x)
#define CSI_CSICR88_PIXEL_COUNTERS_MASK     CSI_CR88_PIXEL_COUNTERS_MASK
#define CSI_CSICR88_PIXEL_COUNTERS_SHIFT     CSI_CR88_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR88_PIXEL_COUNTERS(x)     CSI_CR88_PIXEL_COUNTERS(x)
#define CSI_CSICR89_PIXEL_COUNTERS_MASK     CSI_CR89_PIXEL_COUNTERS_MASK
#define CSI_CSICR89_PIXEL_COUNTERS_SHIFT     CSI_CR89_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR89_PIXEL_COUNTERS(x)     CSI_CR89_PIXEL_COUNTERS(x)
#define CSI_CSICR90_PIXEL_COUNTERS_MASK     CSI_CR90_PIXEL_COUNTERS_MASK
#define CSI_CSICR90_PIXEL_COUNTERS_SHIFT     CSI_CR90_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR90_PIXEL_COUNTERS(x)     CSI_CR90_PIXEL_COUNTERS(x)
#define CSI_CSICR91_PIXEL_COUNTERS_MASK     CSI_CR91_PIXEL_COUNTERS_MASK
#define CSI_CSICR91_PIXEL_COUNTERS_SHIFT     CSI_CR91_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR91_PIXEL_COUNTERS(x)     CSI_CR91_PIXEL_COUNTERS(x)
#define CSI_CSICR92_PIXEL_COUNTERS_MASK     CSI_CR92_PIXEL_COUNTERS_MASK
#define CSI_CSICR92_PIXEL_COUNTERS_SHIFT     CSI_CR92_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR92_PIXEL_COUNTERS(x)     CSI_CR92_PIXEL_COUNTERS(x)
#define CSI_CSICR93_PIXEL_COUNTERS_MASK     CSI_CR93_PIXEL_COUNTERS_MASK
#define CSI_CSICR93_PIXEL_COUNTERS_SHIFT     CSI_CR93_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR93_PIXEL_COUNTERS(x)     CSI_CR93_PIXEL_COUNTERS(x)
#define CSI_CSICR94_PIXEL_COUNTERS_MASK     CSI_CR94_PIXEL_COUNTERS_MASK
#define CSI_CSICR94_PIXEL_COUNTERS_SHIFT     CSI_CR94_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR94_PIXEL_COUNTERS(x)     CSI_CR94_PIXEL_COUNTERS(x)
#define CSI_CSICR95_PIXEL_COUNTERS_MASK     CSI_CR95_PIXEL_COUNTERS_MASK
#define CSI_CSICR95_PIXEL_COUNTERS_SHIFT     CSI_CR95_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR95_PIXEL_COUNTERS(x)     CSI_CR95_PIXEL_COUNTERS(x)
#define CSI_CSICR96_PIXEL_COUNTERS_MASK     CSI_CR96_PIXEL_COUNTERS_MASK
#define CSI_CSICR96_PIXEL_COUNTERS_SHIFT     CSI_CR96_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR96_PIXEL_COUNTERS(x)     CSI_CR96_PIXEL_COUNTERS(x)
#define CSI_CSICR97_PIXEL_COUNTERS_MASK     CSI_CR97_PIXEL_COUNTERS_MASK
#define CSI_CSICR97_PIXEL_COUNTERS_SHIFT     CSI_CR97_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR97_PIXEL_COUNTERS(x)     CSI_CR97_PIXEL_COUNTERS(x)
#define CSI_CSICR98_PIXEL_COUNTERS_MASK     CSI_CR98_PIXEL_COUNTERS_MASK
#define CSI_CSICR98_PIXEL_COUNTERS_SHIFT     CSI_CR98_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR98_PIXEL_COUNTERS(x)     CSI_CR98_PIXEL_COUNTERS(x)
#define CSI_CSICR99_PIXEL_COUNTERS_MASK     CSI_CR99_PIXEL_COUNTERS_MASK
#define CSI_CSICR99_PIXEL_COUNTERS_SHIFT     CSI_CR99_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR99_PIXEL_COUNTERS(x)     CSI_CR99_PIXEL_COUNTERS(x)
#define CSI_CSICR100_PIXEL_COUNTERS_MASK     CSI_CR100_PIXEL_COUNTERS_MASK
#define CSI_CSICR100_PIXEL_COUNTERS_SHIFT     CSI_CR100_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR100_PIXEL_COUNTERS(x)     CSI_CR100_PIXEL_COUNTERS(x)
#define CSI_CSICR101_PIXEL_COUNTERS_MASK     CSI_CR101_PIXEL_COUNTERS_MASK
#define CSI_CSICR101_PIXEL_COUNTERS_SHIFT     CSI_CR101_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR101_PIXEL_COUNTERS(x)     CSI_CR101_PIXEL_COUNTERS(x)
#define CSI_CSICR102_PIXEL_COUNTERS_MASK     CSI_CR102_PIXEL_COUNTERS_MASK
#define CSI_CSICR102_PIXEL_COUNTERS_SHIFT     CSI_CR102_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR102_PIXEL_COUNTERS(x)     CSI_CR102_PIXEL_COUNTERS(x)
#define CSI_CSICR103_PIXEL_COUNTERS_MASK     CSI_CR103_PIXEL_COUNTERS_MASK
#define CSI_CSICR103_PIXEL_COUNTERS_SHIFT     CSI_CR103_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR103_PIXEL_COUNTERS(x)     CSI_CR103_PIXEL_COUNTERS(x)
#define CSI_CSICR104_PIXEL_COUNTERS_MASK     CSI_CR104_PIXEL_COUNTERS_MASK
#define CSI_CSICR104_PIXEL_COUNTERS_SHIFT     CSI_CR104_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR104_PIXEL_COUNTERS(x)     CSI_CR104_PIXEL_COUNTERS(x)
#define CSI_CSICR105_PIXEL_COUNTERS_MASK     CSI_CR105_PIXEL_COUNTERS_MASK
#define CSI_CSICR105_PIXEL_COUNTERS_SHIFT     CSI_CR105_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR105_PIXEL_COUNTERS(x)     CSI_CR105_PIXEL_COUNTERS(x)
#define CSI_CSICR106_PIXEL_COUNTERS_MASK     CSI_CR106_PIXEL_COUNTERS_MASK
#define CSI_CSICR106_PIXEL_COUNTERS_SHIFT     CSI_CR106_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR106_PIXEL_COUNTERS(x)     CSI_CR106_PIXEL_COUNTERS(x)
#define CSI_CSICR107_PIXEL_COUNTERS_MASK     CSI_CR107_PIXEL_COUNTERS_MASK
#define CSI_CSICR107_PIXEL_COUNTERS_SHIFT     CSI_CR107_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR107_PIXEL_COUNTERS(x)     CSI_CR107_PIXEL_COUNTERS(x)
#define CSI_CSICR108_PIXEL_COUNTERS_MASK     CSI_CR108_PIXEL_COUNTERS_MASK
#define CSI_CSICR108_PIXEL_COUNTERS_SHIFT     CSI_CR108_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR108_PIXEL_COUNTERS(x)     CSI_CR108_PIXEL_COUNTERS(x)
#define CSI_CSICR109_PIXEL_COUNTERS_MASK     CSI_CR109_PIXEL_COUNTERS_MASK
#define CSI_CSICR109_PIXEL_COUNTERS_SHIFT     CSI_CR109_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR109_PIXEL_COUNTERS(x)     CSI_CR109_PIXEL_COUNTERS(x)
#define CSI_CSICR110_PIXEL_COUNTERS_MASK     CSI_CR110_PIXEL_COUNTERS_MASK
#define CSI_CSICR110_PIXEL_COUNTERS_SHIFT     CSI_CR110_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR110_PIXEL_COUNTERS(x)     CSI_CR110_PIXEL_COUNTERS(x)
#define CSI_CSICR111_PIXEL_COUNTERS_MASK     CSI_CR111_PIXEL_COUNTERS_MASK
#define CSI_CSICR111_PIXEL_COUNTERS_SHIFT     CSI_CR111_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR111_PIXEL_COUNTERS(x)     CSI_CR111_PIXEL_COUNTERS(x)
#define CSI_CSICR112_PIXEL_COUNTERS_MASK     CSI_CR112_PIXEL_COUNTERS_MASK
#define CSI_CSICR112_PIXEL_COUNTERS_SHIFT     CSI_CR112_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR112_PIXEL_COUNTERS(x)     CSI_CR112_PIXEL_COUNTERS(x)
#define CSI_CSICR113_PIXEL_COUNTERS_MASK     CSI_CR113_PIXEL_COUNTERS_MASK
#define CSI_CSICR113_PIXEL_COUNTERS_SHIFT     CSI_CR113_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR113_PIXEL_COUNTERS(x)     CSI_CR113_PIXEL_COUNTERS(x)
#define CSI_CSICR114_PIXEL_COUNTERS_MASK     CSI_CR114_PIXEL_COUNTERS_MASK
#define CSI_CSICR114_PIXEL_COUNTERS_SHIFT     CSI_CR114_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR114_PIXEL_COUNTERS(x)     CSI_CR114_PIXEL_COUNTERS(x)
#define CSI_CSICR115_PIXEL_COUNTERS_MASK     CSI_CR115_PIXEL_COUNTERS_MASK
#define CSI_CSICR115_PIXEL_COUNTERS_SHIFT     CSI_CR115_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR115_PIXEL_COUNTERS(x)     CSI_CR115_PIXEL_COUNTERS(x)
#define CSI_CSICR116_PIXEL_COUNTERS_MASK     CSI_CR116_PIXEL_COUNTERS_MASK
#define CSI_CSICR116_PIXEL_COUNTERS_SHIFT     CSI_CR116_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR116_PIXEL_COUNTERS(x)     CSI_CR116_PIXEL_COUNTERS(x)
#define CSI_CSICR117_PIXEL_COUNTERS_MASK     CSI_CR117_PIXEL_COUNTERS_MASK
#define CSI_CSICR117_PIXEL_COUNTERS_SHIFT     CSI_CR117_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR117_PIXEL_COUNTERS(x)     CSI_CR117_PIXEL_COUNTERS(x)
#define CSI_CSICR118_PIXEL_COUNTERS_MASK     CSI_CR118_PIXEL_COUNTERS_MASK
#define CSI_CSICR118_PIXEL_COUNTERS_SHIFT     CSI_CR118_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR118_PIXEL_COUNTERS(x)     CSI_CR118_PIXEL_COUNTERS(x)
#define CSI_CSICR119_PIXEL_COUNTERS_MASK     CSI_CR119_PIXEL_COUNTERS_MASK
#define CSI_CSICR119_PIXEL_COUNTERS_SHIFT     CSI_CR119_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR119_PIXEL_COUNTERS(x)     CSI_CR119_PIXEL_COUNTERS(x)
#define CSI_CSICR120_PIXEL_COUNTERS_MASK     CSI_CR120_PIXEL_COUNTERS_MASK
#define CSI_CSICR120_PIXEL_COUNTERS_SHIFT     CSI_CR120_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR120_PIXEL_COUNTERS(x)     CSI_CR120_PIXEL_COUNTERS(x)
#define CSI_CSICR121_PIXEL_COUNTERS_MASK     CSI_CR121_PIXEL_COUNTERS_MASK
#define CSI_CSICR121_PIXEL_COUNTERS_SHIFT     CSI_CR121_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR121_PIXEL_COUNTERS(x)     CSI_CR121_PIXEL_COUNTERS(x)
#define CSI_CSICR122_PIXEL_COUNTERS_MASK     CSI_CR122_PIXEL_COUNTERS_MASK
#define CSI_CSICR122_PIXEL_COUNTERS_SHIFT     CSI_CR122_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR122_PIXEL_COUNTERS(x)     CSI_CR122_PIXEL_COUNTERS(x)
#define CSI_CSICR123_PIXEL_COUNTERS_MASK     CSI_CR123_PIXEL_COUNTERS_MASK
#define CSI_CSICR123_PIXEL_COUNTERS_SHIFT     CSI_CR123_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR123_PIXEL_COUNTERS(x)     CSI_CR123_PIXEL_COUNTERS(x)
#define CSI_CSICR124_PIXEL_COUNTERS_MASK     CSI_CR124_PIXEL_COUNTERS_MASK
#define CSI_CSICR124_PIXEL_COUNTERS_SHIFT     CSI_CR124_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR124_PIXEL_COUNTERS(x)     CSI_CR124_PIXEL_COUNTERS(x)
#define CSI_CSICR125_PIXEL_COUNTERS_MASK     CSI_CR125_PIXEL_COUNTERS_MASK
#define CSI_CSICR125_PIXEL_COUNTERS_SHIFT     CSI_CR125_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR125_PIXEL_COUNTERS(x)     CSI_CR125_PIXEL_COUNTERS(x)
#define CSI_CSICR126_PIXEL_COUNTERS_MASK     CSI_CR126_PIXEL_COUNTERS_MASK
#define CSI_CSICR126_PIXEL_COUNTERS_SHIFT     CSI_CR126_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR126_PIXEL_COUNTERS(x)     CSI_CR126_PIXEL_COUNTERS(x)
#define CSI_CSICR127_PIXEL_COUNTERS_MASK     CSI_CR127_PIXEL_COUNTERS_MASK
#define CSI_CSICR127_PIXEL_COUNTERS_SHIFT     CSI_CR127_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR127_PIXEL_COUNTERS(x)     CSI_CR127_PIXEL_COUNTERS(x)
#define CSI_CSICR128_PIXEL_COUNTERS_MASK     CSI_CR128_PIXEL_COUNTERS_MASK
#define CSI_CSICR128_PIXEL_COUNTERS_SHIFT     CSI_CR128_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR128_PIXEL_COUNTERS(x)     CSI_CR128_PIXEL_COUNTERS(x)
#define CSI_CSICR129_PIXEL_COUNTERS_MASK     CSI_CR129_PIXEL_COUNTERS_MASK
#define CSI_CSICR129_PIXEL_COUNTERS_SHIFT     CSI_CR129_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR129_PIXEL_COUNTERS(x)     CSI_CR129_PIXEL_COUNTERS(x)
#define CSI_CSICR130_PIXEL_COUNTERS_MASK     CSI_CR130_PIXEL_COUNTERS_MASK
#define CSI_CSICR130_PIXEL_COUNTERS_SHIFT     CSI_CR130_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR130_PIXEL_COUNTERS(x)     CSI_CR130_PIXEL_COUNTERS(x)
#define CSI_CSICR131_PIXEL_COUNTERS_MASK     CSI_CR131_PIXEL_COUNTERS_MASK
#define CSI_CSICR131_PIXEL_COUNTERS_SHIFT     CSI_CR131_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR131_PIXEL_COUNTERS(x)     CSI_CR131_PIXEL_COUNTERS(x)
#define CSI_CSICR132_PIXEL_COUNTERS_MASK     CSI_CR132_PIXEL_COUNTERS_MASK
#define CSI_CSICR132_PIXEL_COUNTERS_SHIFT     CSI_CR132_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR132_PIXEL_COUNTERS(x)     CSI_CR132_PIXEL_COUNTERS(x)
#define CSI_CSICR133_PIXEL_COUNTERS_MASK     CSI_CR133_PIXEL_COUNTERS_MASK
#define CSI_CSICR133_PIXEL_COUNTERS_SHIFT     CSI_CR133_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR133_PIXEL_COUNTERS(x)     CSI_CR133_PIXEL_COUNTERS(x)
#define CSI_CSICR134_PIXEL_COUNTERS_MASK     CSI_CR134_PIXEL_COUNTERS_MASK
#define CSI_CSICR134_PIXEL_COUNTERS_SHIFT     CSI_CR134_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR134_PIXEL_COUNTERS(x)     CSI_CR134_PIXEL_COUNTERS(x)
#define CSI_CSICR135_PIXEL_COUNTERS_MASK     CSI_CR135_PIXEL_COUNTERS_MASK
#define CSI_CSICR135_PIXEL_COUNTERS_SHIFT     CSI_CR135_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR135_PIXEL_COUNTERS(x)     CSI_CR135_PIXEL_COUNTERS(x)
#define CSI_CSICR136_PIXEL_COUNTERS_MASK     CSI_CR136_PIXEL_COUNTERS_MASK
#define CSI_CSICR136_PIXEL_COUNTERS_SHIFT     CSI_CR136_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR136_PIXEL_COUNTERS(x)     CSI_CR136_PIXEL_COUNTERS(x)
#define CSI_CSICR137_PIXEL_COUNTERS_MASK     CSI_CR137_PIXEL_COUNTERS_MASK
#define CSI_CSICR137_PIXEL_COUNTERS_SHIFT     CSI_CR137_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR137_PIXEL_COUNTERS(x)     CSI_CR137_PIXEL_COUNTERS(x)
#define CSI_CSICR138_PIXEL_COUNTERS_MASK     CSI_CR138_PIXEL_COUNTERS_MASK
#define CSI_CSICR138_PIXEL_COUNTERS_SHIFT     CSI_CR138_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR138_PIXEL_COUNTERS(x)     CSI_CR138_PIXEL_COUNTERS(x)
#define CSI_CSICR139_PIXEL_COUNTERS_MASK     CSI_CR139_PIXEL_COUNTERS_MASK
#define CSI_CSICR139_PIXEL_COUNTERS_SHIFT     CSI_CR139_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR139_PIXEL_COUNTERS(x)     CSI_CR139_PIXEL_COUNTERS(x)
#define CSI_CSICR140_PIXEL_COUNTERS_MASK     CSI_CR140_PIXEL_COUNTERS_MASK
#define CSI_CSICR140_PIXEL_COUNTERS_SHIFT     CSI_CR140_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR140_PIXEL_COUNTERS(x)     CSI_CR140_PIXEL_COUNTERS(x)
#define CSI_CSICR141_PIXEL_COUNTERS_MASK     CSI_CR141_PIXEL_COUNTERS_MASK
#define CSI_CSICR141_PIXEL_COUNTERS_SHIFT     CSI_CR141_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR141_PIXEL_COUNTERS(x)     CSI_CR141_PIXEL_COUNTERS(x)
#define CSI_CSICR142_PIXEL_COUNTERS_MASK     CSI_CR142_PIXEL_COUNTERS_MASK
#define CSI_CSICR142_PIXEL_COUNTERS_SHIFT     CSI_CR142_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR142_PIXEL_COUNTERS(x)     CSI_CR142_PIXEL_COUNTERS(x)
#define CSI_CSICR143_PIXEL_COUNTERS_MASK     CSI_CR143_PIXEL_COUNTERS_MASK
#define CSI_CSICR143_PIXEL_COUNTERS_SHIFT     CSI_CR143_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR143_PIXEL_COUNTERS(x)     CSI_CR143_PIXEL_COUNTERS(x)
#define CSI_CSICR144_PIXEL_COUNTERS_MASK     CSI_CR144_PIXEL_COUNTERS_MASK
#define CSI_CSICR144_PIXEL_COUNTERS_SHIFT     CSI_CR144_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR144_PIXEL_COUNTERS(x)     CSI_CR144_PIXEL_COUNTERS(x)
#define CSI_CSICR145_PIXEL_COUNTERS_MASK     CSI_CR145_PIXEL_COUNTERS_MASK
#define CSI_CSICR145_PIXEL_COUNTERS_SHIFT     CSI_CR145_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR145_PIXEL_COUNTERS(x)     CSI_CR145_PIXEL_COUNTERS(x)
#define CSI_CSICR146_PIXEL_COUNTERS_MASK     CSI_CR146_PIXEL_COUNTERS_MASK
#define CSI_CSICR146_PIXEL_COUNTERS_SHIFT     CSI_CR146_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR146_PIXEL_COUNTERS(x)     CSI_CR146_PIXEL_COUNTERS(x)
#define CSI_CSICR147_PIXEL_COUNTERS_MASK     CSI_CR147_PIXEL_COUNTERS_MASK
#define CSI_CSICR147_PIXEL_COUNTERS_SHIFT     CSI_CR147_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR147_PIXEL_COUNTERS(x)     CSI_CR147_PIXEL_COUNTERS(x)
#define CSI_CSICR148_PIXEL_COUNTERS_MASK     CSI_CR148_PIXEL_COUNTERS_MASK
#define CSI_CSICR148_PIXEL_COUNTERS_SHIFT     CSI_CR148_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR148_PIXEL_COUNTERS(x)     CSI_CR148_PIXEL_COUNTERS(x)
#define CSI_CSICR149_PIXEL_COUNTERS_MASK     CSI_CR149_PIXEL_COUNTERS_MASK
#define CSI_CSICR149_PIXEL_COUNTERS_SHIFT     CSI_CR149_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR149_PIXEL_COUNTERS(x)     CSI_CR149_PIXEL_COUNTERS(x)
#define CSI_CSICR150_PIXEL_COUNTERS_MASK     CSI_CR150_PIXEL_COUNTERS_MASK
#define CSI_CSICR150_PIXEL_COUNTERS_SHIFT     CSI_CR150_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR150_PIXEL_COUNTERS(x)     CSI_CR150_PIXEL_COUNTERS(x)
#define CSI_CSICR151_PIXEL_COUNTERS_MASK     CSI_CR151_PIXEL_COUNTERS_MASK
#define CSI_CSICR151_PIXEL_COUNTERS_SHIFT     CSI_CR151_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR151_PIXEL_COUNTERS(x)     CSI_CR151_PIXEL_COUNTERS(x)
#define CSI_CSICR152_PIXEL_COUNTERS_MASK     CSI_CR152_PIXEL_COUNTERS_MASK
#define CSI_CSICR152_PIXEL_COUNTERS_SHIFT     CSI_CR152_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR152_PIXEL_COUNTERS(x)     CSI_CR152_PIXEL_COUNTERS(x)
#define CSI_CSICR153_PIXEL_COUNTERS_MASK     CSI_CR153_PIXEL_COUNTERS_MASK
#define CSI_CSICR153_PIXEL_COUNTERS_SHIFT     CSI_CR153_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR153_PIXEL_COUNTERS(x)     CSI_CR153_PIXEL_COUNTERS(x)
#define CSI_CSICR154_PIXEL_COUNTERS_MASK     CSI_CR154_PIXEL_COUNTERS_MASK
#define CSI_CSICR154_PIXEL_COUNTERS_SHIFT     CSI_CR154_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR154_PIXEL_COUNTERS(x)     CSI_CR154_PIXEL_COUNTERS(x)
#define CSI_CSICR155_PIXEL_COUNTERS_MASK     CSI_CR155_PIXEL_COUNTERS_MASK
#define CSI_CSICR155_PIXEL_COUNTERS_SHIFT     CSI_CR155_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR155_PIXEL_COUNTERS(x)     CSI_CR155_PIXEL_COUNTERS(x)
#define CSI_CSICR156_PIXEL_COUNTERS_MASK     CSI_CR156_PIXEL_COUNTERS_MASK
#define CSI_CSICR156_PIXEL_COUNTERS_SHIFT     CSI_CR156_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR156_PIXEL_COUNTERS(x)     CSI_CR156_PIXEL_COUNTERS(x)
#define CSI_CSICR157_PIXEL_COUNTERS_MASK     CSI_CR157_PIXEL_COUNTERS_MASK
#define CSI_CSICR157_PIXEL_COUNTERS_SHIFT     CSI_CR157_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR157_PIXEL_COUNTERS(x)     CSI_CR157_PIXEL_COUNTERS(x)
#define CSI_CSICR158_PIXEL_COUNTERS_MASK     CSI_CR158_PIXEL_COUNTERS_MASK
#define CSI_CSICR158_PIXEL_COUNTERS_SHIFT     CSI_CR158_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR158_PIXEL_COUNTERS(x)     CSI_CR158_PIXEL_COUNTERS(x)
#define CSI_CSICR159_PIXEL_COUNTERS_MASK     CSI_CR159_PIXEL_COUNTERS_MASK
#define CSI_CSICR159_PIXEL_COUNTERS_SHIFT     CSI_CR159_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR159_PIXEL_COUNTERS(x)     CSI_CR159_PIXEL_COUNTERS(x)
#define CSI_CSICR160_PIXEL_COUNTERS_MASK     CSI_CR160_PIXEL_COUNTERS_MASK
#define CSI_CSICR160_PIXEL_COUNTERS_SHIFT     CSI_CR160_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR160_PIXEL_COUNTERS(x)     CSI_CR160_PIXEL_COUNTERS(x)
#define CSI_CSICR161_PIXEL_COUNTERS_MASK     CSI_CR161_PIXEL_COUNTERS_MASK
#define CSI_CSICR161_PIXEL_COUNTERS_SHIFT     CSI_CR161_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR161_PIXEL_COUNTERS(x)     CSI_CR161_PIXEL_COUNTERS(x)
#define CSI_CSICR162_PIXEL_COUNTERS_MASK     CSI_CR162_PIXEL_COUNTERS_MASK
#define CSI_CSICR162_PIXEL_COUNTERS_SHIFT     CSI_CR162_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR162_PIXEL_COUNTERS(x)     CSI_CR162_PIXEL_COUNTERS(x)
#define CSI_CSICR163_PIXEL_COUNTERS_MASK     CSI_CR163_PIXEL_COUNTERS_MASK
#define CSI_CSICR163_PIXEL_COUNTERS_SHIFT     CSI_CR163_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR163_PIXEL_COUNTERS(x)     CSI_CR163_PIXEL_COUNTERS(x)
#define CSI_CSICR164_PIXEL_COUNTERS_MASK     CSI_CR164_PIXEL_COUNTERS_MASK
#define CSI_CSICR164_PIXEL_COUNTERS_SHIFT     CSI_CR164_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR164_PIXEL_COUNTERS(x)     CSI_CR164_PIXEL_COUNTERS(x)
#define CSI_CSICR165_PIXEL_COUNTERS_MASK     CSI_CR165_PIXEL_COUNTERS_MASK
#define CSI_CSICR165_PIXEL_COUNTERS_SHIFT     CSI_CR165_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR165_PIXEL_COUNTERS(x)     CSI_CR165_PIXEL_COUNTERS(x)
#define CSI_CSICR166_PIXEL_COUNTERS_MASK     CSI_CR166_PIXEL_COUNTERS_MASK
#define CSI_CSICR166_PIXEL_COUNTERS_SHIFT     CSI_CR166_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR166_PIXEL_COUNTERS(x)     CSI_CR166_PIXEL_COUNTERS(x)
#define CSI_CSICR167_PIXEL_COUNTERS_MASK     CSI_CR167_PIXEL_COUNTERS_MASK
#define CSI_CSICR167_PIXEL_COUNTERS_SHIFT     CSI_CR167_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR167_PIXEL_COUNTERS(x)     CSI_CR167_PIXEL_COUNTERS(x)
#define CSI_CSICR168_PIXEL_COUNTERS_MASK     CSI_CR168_PIXEL_COUNTERS_MASK
#define CSI_CSICR168_PIXEL_COUNTERS_SHIFT     CSI_CR168_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR168_PIXEL_COUNTERS(x)     CSI_CR168_PIXEL_COUNTERS(x)
#define CSI_CSICR169_PIXEL_COUNTERS_MASK     CSI_CR169_PIXEL_COUNTERS_MASK
#define CSI_CSICR169_PIXEL_COUNTERS_SHIFT     CSI_CR169_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR169_PIXEL_COUNTERS(x)     CSI_CR169_PIXEL_COUNTERS(x)
#define CSI_CSICR170_PIXEL_COUNTERS_MASK     CSI_CR170_PIXEL_COUNTERS_MASK
#define CSI_CSICR170_PIXEL_COUNTERS_SHIFT     CSI_CR170_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR170_PIXEL_COUNTERS(x)     CSI_CR170_PIXEL_COUNTERS(x)
#define CSI_CSICR171_PIXEL_COUNTERS_MASK     CSI_CR171_PIXEL_COUNTERS_MASK
#define CSI_CSICR171_PIXEL_COUNTERS_SHIFT     CSI_CR171_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR171_PIXEL_COUNTERS(x)     CSI_CR171_PIXEL_COUNTERS(x)
#define CSI_CSICR172_PIXEL_COUNTERS_MASK     CSI_CR172_PIXEL_COUNTERS_MASK
#define CSI_CSICR172_PIXEL_COUNTERS_SHIFT     CSI_CR172_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR172_PIXEL_COUNTERS(x)     CSI_CR172_PIXEL_COUNTERS(x)
#define CSI_CSICR173_PIXEL_COUNTERS_MASK     CSI_CR173_PIXEL_COUNTERS_MASK
#define CSI_CSICR173_PIXEL_COUNTERS_SHIFT     CSI_CR173_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR173_PIXEL_COUNTERS(x)     CSI_CR173_PIXEL_COUNTERS(x)
#define CSI_CSICR174_PIXEL_COUNTERS_MASK     CSI_CR174_PIXEL_COUNTERS_MASK
#define CSI_CSICR174_PIXEL_COUNTERS_SHIFT     CSI_CR174_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR174_PIXEL_COUNTERS(x)     CSI_CR174_PIXEL_COUNTERS(x)
#define CSI_CSICR175_PIXEL_COUNTERS_MASK     CSI_CR175_PIXEL_COUNTERS_MASK
#define CSI_CSICR175_PIXEL_COUNTERS_SHIFT     CSI_CR175_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR175_PIXEL_COUNTERS(x)     CSI_CR175_PIXEL_COUNTERS(x)
#define CSI_CSICR176_PIXEL_COUNTERS_MASK     CSI_CR176_PIXEL_COUNTERS_MASK
#define CSI_CSICR176_PIXEL_COUNTERS_SHIFT     CSI_CR176_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR176_PIXEL_COUNTERS(x)     CSI_CR176_PIXEL_COUNTERS(x)
#define CSI_CSICR177_PIXEL_COUNTERS_MASK     CSI_CR177_PIXEL_COUNTERS_MASK
#define CSI_CSICR177_PIXEL_COUNTERS_SHIFT     CSI_CR177_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR177_PIXEL_COUNTERS(x)     CSI_CR177_PIXEL_COUNTERS(x)
#define CSI_CSICR178_PIXEL_COUNTERS_MASK     CSI_CR178_PIXEL_COUNTERS_MASK
#define CSI_CSICR178_PIXEL_COUNTERS_SHIFT     CSI_CR178_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR178_PIXEL_COUNTERS(x)     CSI_CR178_PIXEL_COUNTERS(x)
#define CSI_CSICR179_PIXEL_COUNTERS_MASK     CSI_CR179_PIXEL_COUNTERS_MASK
#define CSI_CSICR179_PIXEL_COUNTERS_SHIFT     CSI_CR179_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR179_PIXEL_COUNTERS(x)     CSI_CR179_PIXEL_COUNTERS(x)
#define CSI_CSICR180_PIXEL_COUNTERS_MASK     CSI_CR180_PIXEL_COUNTERS_MASK
#define CSI_CSICR180_PIXEL_COUNTERS_SHIFT     CSI_CR180_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR180_PIXEL_COUNTERS(x)     CSI_CR180_PIXEL_COUNTERS(x)
#define CSI_CSICR181_PIXEL_COUNTERS_MASK     CSI_CR181_PIXEL_COUNTERS_MASK
#define CSI_CSICR181_PIXEL_COUNTERS_SHIFT     CSI_CR181_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR181_PIXEL_COUNTERS(x)     CSI_CR181_PIXEL_COUNTERS(x)
#define CSI_CSICR182_PIXEL_COUNTERS_MASK     CSI_CR182_PIXEL_COUNTERS_MASK
#define CSI_CSICR182_PIXEL_COUNTERS_SHIFT     CSI_CR182_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR182_PIXEL_COUNTERS(x)     CSI_CR182_PIXEL_COUNTERS(x)
#define CSI_CSICR183_PIXEL_COUNTERS_MASK     CSI_CR183_PIXEL_COUNTERS_MASK
#define CSI_CSICR183_PIXEL_COUNTERS_SHIFT     CSI_CR183_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR183_PIXEL_COUNTERS(x)     CSI_CR183_PIXEL_COUNTERS(x)
#define CSI_CSICR184_PIXEL_COUNTERS_MASK     CSI_CR184_PIXEL_COUNTERS_MASK
#define CSI_CSICR184_PIXEL_COUNTERS_SHIFT     CSI_CR184_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR184_PIXEL_COUNTERS(x)     CSI_CR184_PIXEL_COUNTERS(x)
#define CSI_CSICR185_PIXEL_COUNTERS_MASK     CSI_CR185_PIXEL_COUNTERS_MASK
#define CSI_CSICR185_PIXEL_COUNTERS_SHIFT     CSI_CR185_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR185_PIXEL_COUNTERS(x)     CSI_CR185_PIXEL_COUNTERS(x)
#define CSI_CSICR186_PIXEL_COUNTERS_MASK     CSI_CR186_PIXEL_COUNTERS_MASK
#define CSI_CSICR186_PIXEL_COUNTERS_SHIFT     CSI_CR186_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR186_PIXEL_COUNTERS(x)     CSI_CR186_PIXEL_COUNTERS(x)
#define CSI_CSICR187_PIXEL_COUNTERS_MASK     CSI_CR187_PIXEL_COUNTERS_MASK
#define CSI_CSICR187_PIXEL_COUNTERS_SHIFT     CSI_CR187_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR187_PIXEL_COUNTERS(x)     CSI_CR187_PIXEL_COUNTERS(x)
#define CSI_CSICR188_PIXEL_COUNTERS_MASK     CSI_CR188_PIXEL_COUNTERS_MASK
#define CSI_CSICR188_PIXEL_COUNTERS_SHIFT     CSI_CR188_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR188_PIXEL_COUNTERS(x)     CSI_CR188_PIXEL_COUNTERS(x)
#define CSI_CSICR189_PIXEL_COUNTERS_MASK     CSI_CR189_PIXEL_COUNTERS_MASK
#define CSI_CSICR189_PIXEL_COUNTERS_SHIFT     CSI_CR189_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR189_PIXEL_COUNTERS(x)     CSI_CR189_PIXEL_COUNTERS(x)
#define CSI_CSICR190_PIXEL_COUNTERS_MASK     CSI_CR190_PIXEL_COUNTERS_MASK
#define CSI_CSICR190_PIXEL_COUNTERS_SHIFT     CSI_CR190_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR190_PIXEL_COUNTERS(x)     CSI_CR190_PIXEL_COUNTERS(x)
#define CSI_CSICR191_PIXEL_COUNTERS_MASK     CSI_CR191_PIXEL_COUNTERS_MASK
#define CSI_CSICR191_PIXEL_COUNTERS_SHIFT     CSI_CR191_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR191_PIXEL_COUNTERS(x)     CSI_CR191_PIXEL_COUNTERS(x)
#define CSI_CSICR192_PIXEL_COUNTERS_MASK     CSI_CR192_PIXEL_COUNTERS_MASK
#define CSI_CSICR192_PIXEL_COUNTERS_SHIFT     CSI_CR192_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR192_PIXEL_COUNTERS(x)     CSI_CR192_PIXEL_COUNTERS(x)
#define CSI_CSICR193_PIXEL_COUNTERS_MASK     CSI_CR193_PIXEL_COUNTERS_MASK
#define CSI_CSICR193_PIXEL_COUNTERS_SHIFT     CSI_CR193_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR193_PIXEL_COUNTERS(x)     CSI_CR193_PIXEL_COUNTERS(x)
#define CSI_CSICR194_PIXEL_COUNTERS_MASK     CSI_CR194_PIXEL_COUNTERS_MASK
#define CSI_CSICR194_PIXEL_COUNTERS_SHIFT     CSI_CR194_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR194_PIXEL_COUNTERS(x)     CSI_CR194_PIXEL_COUNTERS(x)
#define CSI_CSICR195_PIXEL_COUNTERS_MASK     CSI_CR195_PIXEL_COUNTERS_MASK
#define CSI_CSICR195_PIXEL_COUNTERS_SHIFT     CSI_CR195_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR195_PIXEL_COUNTERS(x)     CSI_CR195_PIXEL_COUNTERS(x)
#define CSI_CSICR196_PIXEL_COUNTERS_MASK     CSI_CR196_PIXEL_COUNTERS_MASK
#define CSI_CSICR196_PIXEL_COUNTERS_SHIFT     CSI_CR196_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR196_PIXEL_COUNTERS(x)     CSI_CR196_PIXEL_COUNTERS(x)
#define CSI_CSICR197_PIXEL_COUNTERS_MASK     CSI_CR197_PIXEL_COUNTERS_MASK
#define CSI_CSICR197_PIXEL_COUNTERS_SHIFT     CSI_CR197_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR197_PIXEL_COUNTERS(x)     CSI_CR197_PIXEL_COUNTERS(x)
#define CSI_CSICR198_PIXEL_COUNTERS_MASK     CSI_CR198_PIXEL_COUNTERS_MASK
#define CSI_CSICR198_PIXEL_COUNTERS_SHIFT     CSI_CR198_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR198_PIXEL_COUNTERS(x)     CSI_CR198_PIXEL_COUNTERS(x)
#define CSI_CSICR199_PIXEL_COUNTERS_MASK     CSI_CR199_PIXEL_COUNTERS_MASK
#define CSI_CSICR199_PIXEL_COUNTERS_SHIFT     CSI_CR199_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR199_PIXEL_COUNTERS(x)     CSI_CR199_PIXEL_COUNTERS(x)
#define CSI_CSICR200_PIXEL_COUNTERS_MASK     CSI_CR200_PIXEL_COUNTERS_MASK
#define CSI_CSICR200_PIXEL_COUNTERS_SHIFT     CSI_CR200_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR200_PIXEL_COUNTERS(x)     CSI_CR200_PIXEL_COUNTERS(x)
#define CSI_CSICR201_PIXEL_COUNTERS_MASK     CSI_CR201_PIXEL_COUNTERS_MASK
#define CSI_CSICR201_PIXEL_COUNTERS_SHIFT     CSI_CR201_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR201_PIXEL_COUNTERS(x)     CSI_CR201_PIXEL_COUNTERS(x)
#define CSI_CSICR202_PIXEL_COUNTERS_MASK     CSI_CR202_PIXEL_COUNTERS_MASK
#define CSI_CSICR202_PIXEL_COUNTERS_SHIFT     CSI_CR202_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR202_PIXEL_COUNTERS(x)     CSI_CR202_PIXEL_COUNTERS(x)
#define CSI_CSICR203_PIXEL_COUNTERS_MASK     CSI_CR203_PIXEL_COUNTERS_MASK
#define CSI_CSICR203_PIXEL_COUNTERS_SHIFT     CSI_CR203_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR203_PIXEL_COUNTERS(x)     CSI_CR203_PIXEL_COUNTERS(x)
#define CSI_CSICR204_PIXEL_COUNTERS_MASK     CSI_CR204_PIXEL_COUNTERS_MASK
#define CSI_CSICR204_PIXEL_COUNTERS_SHIFT     CSI_CR204_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR204_PIXEL_COUNTERS(x)     CSI_CR204_PIXEL_COUNTERS(x)
#define CSI_CSICR205_PIXEL_COUNTERS_MASK     CSI_CR205_PIXEL_COUNTERS_MASK
#define CSI_CSICR205_PIXEL_COUNTERS_SHIFT     CSI_CR205_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR205_PIXEL_COUNTERS(x)     CSI_CR205_PIXEL_COUNTERS(x)
#define CSI_CSICR206_PIXEL_COUNTERS_MASK     CSI_CR206_PIXEL_COUNTERS_MASK
#define CSI_CSICR206_PIXEL_COUNTERS_SHIFT     CSI_CR206_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR206_PIXEL_COUNTERS(x)     CSI_CR206_PIXEL_COUNTERS(x)
#define CSI_CSICR207_PIXEL_COUNTERS_MASK     CSI_CR207_PIXEL_COUNTERS_MASK
#define CSI_CSICR207_PIXEL_COUNTERS_SHIFT     CSI_CR207_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR207_PIXEL_COUNTERS(x)     CSI_CR207_PIXEL_COUNTERS(x)
#define CSI_CSICR208_PIXEL_COUNTERS_MASK     CSI_CR208_PIXEL_COUNTERS_MASK
#define CSI_CSICR208_PIXEL_COUNTERS_SHIFT     CSI_CR208_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR208_PIXEL_COUNTERS(x)     CSI_CR208_PIXEL_COUNTERS(x)
#define CSI_CSICR209_PIXEL_COUNTERS_MASK     CSI_CR209_PIXEL_COUNTERS_MASK
#define CSI_CSICR209_PIXEL_COUNTERS_SHIFT     CSI_CR209_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR209_PIXEL_COUNTERS(x)     CSI_CR209_PIXEL_COUNTERS(x)
#define CSI_CSICR210_PIXEL_COUNTERS_MASK     CSI_CR210_PIXEL_COUNTERS_MASK
#define CSI_CSICR210_PIXEL_COUNTERS_SHIFT     CSI_CR210_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR210_PIXEL_COUNTERS(x)     CSI_CR210_PIXEL_COUNTERS(x)
#define CSI_CSICR211_PIXEL_COUNTERS_MASK     CSI_CR211_PIXEL_COUNTERS_MASK
#define CSI_CSICR211_PIXEL_COUNTERS_SHIFT     CSI_CR211_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR211_PIXEL_COUNTERS(x)     CSI_CR211_PIXEL_COUNTERS(x)
#define CSI_CSICR212_PIXEL_COUNTERS_MASK     CSI_CR212_PIXEL_COUNTERS_MASK
#define CSI_CSICR212_PIXEL_COUNTERS_SHIFT     CSI_CR212_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR212_PIXEL_COUNTERS(x)     CSI_CR212_PIXEL_COUNTERS(x)
#define CSI_CSICR213_PIXEL_COUNTERS_MASK     CSI_CR213_PIXEL_COUNTERS_MASK
#define CSI_CSICR213_PIXEL_COUNTERS_SHIFT     CSI_CR213_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR213_PIXEL_COUNTERS(x)     CSI_CR213_PIXEL_COUNTERS(x)
#define CSI_CSICR214_PIXEL_COUNTERS_MASK     CSI_CR214_PIXEL_COUNTERS_MASK
#define CSI_CSICR214_PIXEL_COUNTERS_SHIFT     CSI_CR214_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR214_PIXEL_COUNTERS(x)     CSI_CR214_PIXEL_COUNTERS(x)
#define CSI_CSICR215_PIXEL_COUNTERS_MASK     CSI_CR215_PIXEL_COUNTERS_MASK
#define CSI_CSICR215_PIXEL_COUNTERS_SHIFT     CSI_CR215_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR215_PIXEL_COUNTERS(x)     CSI_CR215_PIXEL_COUNTERS(x)
#define CSI_CSICR216_PIXEL_COUNTERS_MASK     CSI_CR216_PIXEL_COUNTERS_MASK
#define CSI_CSICR216_PIXEL_COUNTERS_SHIFT     CSI_CR216_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR216_PIXEL_COUNTERS(x)     CSI_CR216_PIXEL_COUNTERS(x)
#define CSI_CSICR217_PIXEL_COUNTERS_MASK     CSI_CR217_PIXEL_COUNTERS_MASK
#define CSI_CSICR217_PIXEL_COUNTERS_SHIFT     CSI_CR217_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR217_PIXEL_COUNTERS(x)     CSI_CR217_PIXEL_COUNTERS(x)
#define CSI_CSICR218_PIXEL_COUNTERS_MASK     CSI_CR218_PIXEL_COUNTERS_MASK
#define CSI_CSICR218_PIXEL_COUNTERS_SHIFT     CSI_CR218_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR218_PIXEL_COUNTERS(x)     CSI_CR218_PIXEL_COUNTERS(x)
#define CSI_CSICR219_PIXEL_COUNTERS_MASK     CSI_CR219_PIXEL_COUNTERS_MASK
#define CSI_CSICR219_PIXEL_COUNTERS_SHIFT     CSI_CR219_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR219_PIXEL_COUNTERS(x)     CSI_CR219_PIXEL_COUNTERS(x)
#define CSI_CSICR220_PIXEL_COUNTERS_MASK     CSI_CR220_PIXEL_COUNTERS_MASK
#define CSI_CSICR220_PIXEL_COUNTERS_SHIFT     CSI_CR220_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR220_PIXEL_COUNTERS(x)     CSI_CR220_PIXEL_COUNTERS(x)
#define CSI_CSICR221_PIXEL_COUNTERS_MASK     CSI_CR221_PIXEL_COUNTERS_MASK
#define CSI_CSICR221_PIXEL_COUNTERS_SHIFT     CSI_CR221_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR221_PIXEL_COUNTERS(x)     CSI_CR221_PIXEL_COUNTERS(x)
#define CSI_CSICR222_PIXEL_COUNTERS_MASK     CSI_CR222_PIXEL_COUNTERS_MASK
#define CSI_CSICR222_PIXEL_COUNTERS_SHIFT     CSI_CR222_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR222_PIXEL_COUNTERS(x)     CSI_CR222_PIXEL_COUNTERS(x)
#define CSI_CSICR223_PIXEL_COUNTERS_MASK     CSI_CR223_PIXEL_COUNTERS_MASK
#define CSI_CSICR223_PIXEL_COUNTERS_SHIFT     CSI_CR223_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR223_PIXEL_COUNTERS(x)     CSI_CR223_PIXEL_COUNTERS(x)
#define CSI_CSICR224_PIXEL_COUNTERS_MASK     CSI_CR224_PIXEL_COUNTERS_MASK
#define CSI_CSICR224_PIXEL_COUNTERS_SHIFT     CSI_CR224_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR224_PIXEL_COUNTERS(x)     CSI_CR224_PIXEL_COUNTERS(x)
#define CSI_CSICR225_PIXEL_COUNTERS_MASK     CSI_CR225_PIXEL_COUNTERS_MASK
#define CSI_CSICR225_PIXEL_COUNTERS_SHIFT     CSI_CR225_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR225_PIXEL_COUNTERS(x)     CSI_CR225_PIXEL_COUNTERS(x)
#define CSI_CSICR226_PIXEL_COUNTERS_MASK     CSI_CR226_PIXEL_COUNTERS_MASK
#define CSI_CSICR226_PIXEL_COUNTERS_SHIFT     CSI_CR226_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR226_PIXEL_COUNTERS(x)     CSI_CR226_PIXEL_COUNTERS(x)
#define CSI_CSICR227_PIXEL_COUNTERS_MASK     CSI_CR227_PIXEL_COUNTERS_MASK
#define CSI_CSICR227_PIXEL_COUNTERS_SHIFT     CSI_CR227_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR227_PIXEL_COUNTERS(x)     CSI_CR227_PIXEL_COUNTERS(x)
#define CSI_CSICR228_PIXEL_COUNTERS_MASK     CSI_CR228_PIXEL_COUNTERS_MASK
#define CSI_CSICR228_PIXEL_COUNTERS_SHIFT     CSI_CR228_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR228_PIXEL_COUNTERS(x)     CSI_CR228_PIXEL_COUNTERS(x)
#define CSI_CSICR229_PIXEL_COUNTERS_MASK     CSI_CR229_PIXEL_COUNTERS_MASK
#define CSI_CSICR229_PIXEL_COUNTERS_SHIFT     CSI_CR229_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR229_PIXEL_COUNTERS(x)     CSI_CR229_PIXEL_COUNTERS(x)
#define CSI_CSICR230_PIXEL_COUNTERS_MASK     CSI_CR230_PIXEL_COUNTERS_MASK
#define CSI_CSICR230_PIXEL_COUNTERS_SHIFT     CSI_CR230_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR230_PIXEL_COUNTERS(x)     CSI_CR230_PIXEL_COUNTERS(x)
#define CSI_CSICR231_PIXEL_COUNTERS_MASK     CSI_CR231_PIXEL_COUNTERS_MASK
#define CSI_CSICR231_PIXEL_COUNTERS_SHIFT     CSI_CR231_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR231_PIXEL_COUNTERS(x)     CSI_CR231_PIXEL_COUNTERS(x)
#define CSI_CSICR232_PIXEL_COUNTERS_MASK     CSI_CR232_PIXEL_COUNTERS_MASK
#define CSI_CSICR232_PIXEL_COUNTERS_SHIFT     CSI_CR232_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR232_PIXEL_COUNTERS(x)     CSI_CR232_PIXEL_COUNTERS(x)
#define CSI_CSICR233_PIXEL_COUNTERS_MASK     CSI_CR233_PIXEL_COUNTERS_MASK
#define CSI_CSICR233_PIXEL_COUNTERS_SHIFT     CSI_CR233_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR233_PIXEL_COUNTERS(x)     CSI_CR233_PIXEL_COUNTERS(x)
#define CSI_CSICR234_PIXEL_COUNTERS_MASK     CSI_CR234_PIXEL_COUNTERS_MASK
#define CSI_CSICR234_PIXEL_COUNTERS_SHIFT     CSI_CR234_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR234_PIXEL_COUNTERS(x)     CSI_CR234_PIXEL_COUNTERS(x)
#define CSI_CSICR235_PIXEL_COUNTERS_MASK     CSI_CR235_PIXEL_COUNTERS_MASK
#define CSI_CSICR235_PIXEL_COUNTERS_SHIFT     CSI_CR235_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR235_PIXEL_COUNTERS(x)     CSI_CR235_PIXEL_COUNTERS(x)
#define CSI_CSICR236_PIXEL_COUNTERS_MASK     CSI_CR236_PIXEL_COUNTERS_MASK
#define CSI_CSICR236_PIXEL_COUNTERS_SHIFT     CSI_CR236_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR236_PIXEL_COUNTERS(x)     CSI_CR236_PIXEL_COUNTERS(x)
#define CSI_CSICR237_PIXEL_COUNTERS_MASK     CSI_CR237_PIXEL_COUNTERS_MASK
#define CSI_CSICR237_PIXEL_COUNTERS_SHIFT     CSI_CR237_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR237_PIXEL_COUNTERS(x)     CSI_CR237_PIXEL_COUNTERS(x)
#define CSI_CSICR238_PIXEL_COUNTERS_MASK     CSI_CR238_PIXEL_COUNTERS_MASK
#define CSI_CSICR238_PIXEL_COUNTERS_SHIFT     CSI_CR238_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR238_PIXEL_COUNTERS(x)     CSI_CR238_PIXEL_COUNTERS(x)
#define CSI_CSICR239_PIXEL_COUNTERS_MASK     CSI_CR239_PIXEL_COUNTERS_MASK
#define CSI_CSICR239_PIXEL_COUNTERS_SHIFT     CSI_CR239_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR239_PIXEL_COUNTERS(x)     CSI_CR239_PIXEL_COUNTERS(x)
#define CSI_CSICR240_PIXEL_COUNTERS_MASK     CSI_CR240_PIXEL_COUNTERS_MASK
#define CSI_CSICR240_PIXEL_COUNTERS_SHIFT     CSI_CR240_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR240_PIXEL_COUNTERS(x)     CSI_CR240_PIXEL_COUNTERS(x)
#define CSI_CSICR241_PIXEL_COUNTERS_MASK     CSI_CR241_PIXEL_COUNTERS_MASK
#define CSI_CSICR241_PIXEL_COUNTERS_SHIFT     CSI_CR241_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR241_PIXEL_COUNTERS(x)     CSI_CR241_PIXEL_COUNTERS(x)
#define CSI_CSICR242_PIXEL_COUNTERS_MASK     CSI_CR242_PIXEL_COUNTERS_MASK
#define CSI_CSICR242_PIXEL_COUNTERS_SHIFT     CSI_CR242_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR242_PIXEL_COUNTERS(x)     CSI_CR242_PIXEL_COUNTERS(x)
#define CSI_CSICR243_PIXEL_COUNTERS_MASK     CSI_CR243_PIXEL_COUNTERS_MASK
#define CSI_CSICR243_PIXEL_COUNTERS_SHIFT     CSI_CR243_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR243_PIXEL_COUNTERS(x)     CSI_CR243_PIXEL_COUNTERS(x)
#define CSI_CSICR244_PIXEL_COUNTERS_MASK     CSI_CR244_PIXEL_COUNTERS_MASK
#define CSI_CSICR244_PIXEL_COUNTERS_SHIFT     CSI_CR244_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR244_PIXEL_COUNTERS(x)     CSI_CR244_PIXEL_COUNTERS(x)
#define CSI_CSICR245_PIXEL_COUNTERS_MASK     CSI_CR245_PIXEL_COUNTERS_MASK
#define CSI_CSICR245_PIXEL_COUNTERS_SHIFT     CSI_CR245_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR245_PIXEL_COUNTERS(x)     CSI_CR245_PIXEL_COUNTERS(x)
#define CSI_CSICR246_PIXEL_COUNTERS_MASK     CSI_CR246_PIXEL_COUNTERS_MASK
#define CSI_CSICR246_PIXEL_COUNTERS_SHIFT     CSI_CR246_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR246_PIXEL_COUNTERS(x)     CSI_CR246_PIXEL_COUNTERS(x)
#define CSI_CSICR247_PIXEL_COUNTERS_MASK     CSI_CR247_PIXEL_COUNTERS_MASK
#define CSI_CSICR247_PIXEL_COUNTERS_SHIFT     CSI_CR247_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR247_PIXEL_COUNTERS(x)     CSI_CR247_PIXEL_COUNTERS(x)
#define CSI_CSICR248_PIXEL_COUNTERS_MASK     CSI_CR248_PIXEL_COUNTERS_MASK
#define CSI_CSICR248_PIXEL_COUNTERS_SHIFT     CSI_CR248_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR248_PIXEL_COUNTERS(x)     CSI_CR248_PIXEL_COUNTERS(x)
#define CSI_CSICR249_PIXEL_COUNTERS_MASK     CSI_CR249_PIXEL_COUNTERS_MASK
#define CSI_CSICR249_PIXEL_COUNTERS_SHIFT     CSI_CR249_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR249_PIXEL_COUNTERS(x)     CSI_CR249_PIXEL_COUNTERS(x)
#define CSI_CSICR250_PIXEL_COUNTERS_MASK     CSI_CR250_PIXEL_COUNTERS_MASK
#define CSI_CSICR250_PIXEL_COUNTERS_SHIFT     CSI_CR250_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR250_PIXEL_COUNTERS(x)     CSI_CR250_PIXEL_COUNTERS(x)
#define CSI_CSICR251_PIXEL_COUNTERS_MASK     CSI_CR251_PIXEL_COUNTERS_MASK
#define CSI_CSICR251_PIXEL_COUNTERS_SHIFT     CSI_CR251_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR251_PIXEL_COUNTERS(x)     CSI_CR251_PIXEL_COUNTERS(x)
#define CSI_CSICR252_PIXEL_COUNTERS_MASK     CSI_CR252_PIXEL_COUNTERS_MASK
#define CSI_CSICR252_PIXEL_COUNTERS_SHIFT     CSI_CR252_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR252_PIXEL_COUNTERS(x)     CSI_CR252_PIXEL_COUNTERS(x)
#define CSI_CSICR253_PIXEL_COUNTERS_MASK     CSI_CR253_PIXEL_COUNTERS_MASK
#define CSI_CSICR253_PIXEL_COUNTERS_SHIFT     CSI_CR253_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR253_PIXEL_COUNTERS(x)     CSI_CR253_PIXEL_COUNTERS(x)
#define CSI_CSICR254_PIXEL_COUNTERS_MASK     CSI_CR254_PIXEL_COUNTERS_MASK
#define CSI_CSICR254_PIXEL_COUNTERS_SHIFT     CSI_CR254_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR254_PIXEL_COUNTERS(x)     CSI_CR254_PIXEL_COUNTERS(x)
#define CSI_CSICR255_PIXEL_COUNTERS_MASK     CSI_CR255_PIXEL_COUNTERS_MASK
#define CSI_CSICR255_PIXEL_COUNTERS_SHIFT     CSI_CR255_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR255_PIXEL_COUNTERS(x)     CSI_CR255_PIXEL_COUNTERS(x)
#define CSI_CSICR256_PIXEL_COUNTERS_MASK     CSI_CR256_PIXEL_COUNTERS_MASK
#define CSI_CSICR256_PIXEL_COUNTERS_SHIFT     CSI_CR256_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR256_PIXEL_COUNTERS(x)     CSI_CR256_PIXEL_COUNTERS(x)
#define CSI_CSICR257_PIXEL_COUNTERS_MASK     CSI_CR257_PIXEL_COUNTERS_MASK
#define CSI_CSICR257_PIXEL_COUNTERS_SHIFT     CSI_CR257_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR257_PIXEL_COUNTERS(x)     CSI_CR257_PIXEL_COUNTERS(x)
#define CSI_CSICR258_PIXEL_COUNTERS_MASK     CSI_CR258_PIXEL_COUNTERS_MASK
#define CSI_CSICR258_PIXEL_COUNTERS_SHIFT     CSI_CR258_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR258_PIXEL_COUNTERS(x)     CSI_CR258_PIXEL_COUNTERS(x)
#define CSI_CSICR259_PIXEL_COUNTERS_MASK     CSI_CR259_PIXEL_COUNTERS_MASK
#define CSI_CSICR259_PIXEL_COUNTERS_SHIFT     CSI_CR259_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR259_PIXEL_COUNTERS(x)     CSI_CR259_PIXEL_COUNTERS(x)
#define CSI_CSICR260_PIXEL_COUNTERS_MASK     CSI_CR260_PIXEL_COUNTERS_MASK
#define CSI_CSICR260_PIXEL_COUNTERS_SHIFT     CSI_CR260_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR260_PIXEL_COUNTERS(x)     CSI_CR260_PIXEL_COUNTERS(x)
#define CSI_CSICR261_PIXEL_COUNTERS_MASK     CSI_CR261_PIXEL_COUNTERS_MASK
#define CSI_CSICR261_PIXEL_COUNTERS_SHIFT     CSI_CR261_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR261_PIXEL_COUNTERS(x)     CSI_CR261_PIXEL_COUNTERS(x)
#define CSI_CSICR262_PIXEL_COUNTERS_MASK     CSI_CR262_PIXEL_COUNTERS_MASK
#define CSI_CSICR262_PIXEL_COUNTERS_SHIFT     CSI_CR262_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR262_PIXEL_COUNTERS(x)     CSI_CR262_PIXEL_COUNTERS(x)
#define CSI_CSICR263_PIXEL_COUNTERS_MASK     CSI_CR263_PIXEL_COUNTERS_MASK
#define CSI_CSICR263_PIXEL_COUNTERS_SHIFT     CSI_CR263_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR263_PIXEL_COUNTERS(x)     CSI_CR263_PIXEL_COUNTERS(x)
#define CSI_CSICR264_PIXEL_COUNTERS_MASK     CSI_CR264_PIXEL_COUNTERS_MASK
#define CSI_CSICR264_PIXEL_COUNTERS_SHIFT     CSI_CR264_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR264_PIXEL_COUNTERS(x)     CSI_CR264_PIXEL_COUNTERS(x)
#define CSI_CSICR265_PIXEL_COUNTERS_MASK     CSI_CR265_PIXEL_COUNTERS_MASK
#define CSI_CSICR265_PIXEL_COUNTERS_SHIFT     CSI_CR265_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR265_PIXEL_COUNTERS(x)     CSI_CR265_PIXEL_COUNTERS(x)
#define CSI_CSICR266_PIXEL_COUNTERS_MASK     CSI_CR266_PIXEL_COUNTERS_MASK
#define CSI_CSICR266_PIXEL_COUNTERS_SHIFT     CSI_CR266_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR266_PIXEL_COUNTERS(x)     CSI_CR266_PIXEL_COUNTERS(x)
#define CSI_CSICR267_PIXEL_COUNTERS_MASK     CSI_CR267_PIXEL_COUNTERS_MASK
#define CSI_CSICR267_PIXEL_COUNTERS_SHIFT     CSI_CR267_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR267_PIXEL_COUNTERS(x)     CSI_CR267_PIXEL_COUNTERS(x)
#define CSI_CSICR268_PIXEL_COUNTERS_MASK     CSI_CR268_PIXEL_COUNTERS_MASK
#define CSI_CSICR268_PIXEL_COUNTERS_SHIFT     CSI_CR268_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR268_PIXEL_COUNTERS(x)     CSI_CR268_PIXEL_COUNTERS(x)
#define CSI_CSICR269_PIXEL_COUNTERS_MASK     CSI_CR269_PIXEL_COUNTERS_MASK
#define CSI_CSICR269_PIXEL_COUNTERS_SHIFT     CSI_CR269_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR269_PIXEL_COUNTERS(x)     CSI_CR269_PIXEL_COUNTERS(x)
#define CSI_CSICR270_PIXEL_COUNTERS_MASK     CSI_CR270_PIXEL_COUNTERS_MASK
#define CSI_CSICR270_PIXEL_COUNTERS_SHIFT     CSI_CR270_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR270_PIXEL_COUNTERS(x)     CSI_CR270_PIXEL_COUNTERS(x)
#define CSI_CSICR271_PIXEL_COUNTERS_MASK     CSI_CR271_PIXEL_COUNTERS_MASK
#define CSI_CSICR271_PIXEL_COUNTERS_SHIFT     CSI_CR271_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR271_PIXEL_COUNTERS(x)     CSI_CR271_PIXEL_COUNTERS(x)
#define CSI_CSICR272_PIXEL_COUNTERS_MASK     CSI_CR272_PIXEL_COUNTERS_MASK
#define CSI_CSICR272_PIXEL_COUNTERS_SHIFT     CSI_CR272_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR272_PIXEL_COUNTERS(x)     CSI_CR272_PIXEL_COUNTERS(x)
#define CSI_CSICR273_PIXEL_COUNTERS_MASK     CSI_CR273_PIXEL_COUNTERS_MASK
#define CSI_CSICR273_PIXEL_COUNTERS_SHIFT     CSI_CR273_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR273_PIXEL_COUNTERS(x)     CSI_CR273_PIXEL_COUNTERS(x)
#define CSI_CSICR274_PIXEL_COUNTERS_MASK     CSI_CR274_PIXEL_COUNTERS_MASK
#define CSI_CSICR274_PIXEL_COUNTERS_SHIFT     CSI_CR274_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR274_PIXEL_COUNTERS(x)     CSI_CR274_PIXEL_COUNTERS(x)
#define CSI_CSICR275_PIXEL_COUNTERS_MASK     CSI_CR275_PIXEL_COUNTERS_MASK
#define CSI_CSICR275_PIXEL_COUNTERS_SHIFT     CSI_CR275_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR275_PIXEL_COUNTERS(x)     CSI_CR275_PIXEL_COUNTERS(x)
#define CSI_CSICR276_PIXEL_COUNTERS_MASK     CSI_CR276_PIXEL_COUNTERS_MASK
#define CSI_CSICR276_PIXEL_COUNTERS_SHIFT     CSI_CR276_PIXEL_COUNTERS_SHIFT
#define CSI_CSICR276_PIXEL_COUNTERS(x)     CSI_CR276_PIXEL_COUNTERS(x)


/*!
 * @}
 */ /* end of group CSI_Peripheral_Access_Layer */


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


#endif  /* PERI_CSI_H_ */

