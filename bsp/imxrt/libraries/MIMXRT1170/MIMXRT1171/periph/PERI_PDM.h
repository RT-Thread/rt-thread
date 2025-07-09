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
**         CMSIS Peripheral Access Layer for PDM
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
 * @file PERI_PDM.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for PDM
 *
 * CMSIS Peripheral Access Layer for PDM
 */

#if !defined(PERI_PDM_H_)
#define PERI_PDM_H_                              /**< Symbol preventing repeated inclusion */

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
   -- PDM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDM_Peripheral_Access_Layer PDM Peripheral Access Layer
 * @{
 */

/** PDM - Size of Registers Arrays */
#define PDM_DATACHN_COUNT                         8u

/** PDM - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL_1;                            /**< PDM Control register 1, offset: 0x0 */
  __IO uint32_t CTRL_2;                            /**< PDM Control register 2, offset: 0x4 */
  __IO uint32_t STAT;                              /**< PDM Status register, offset: 0x8 */
       uint8_t RESERVED_0[4];
  __IO uint32_t FIFO_CTRL;                         /**< PDM FIFO Control register, offset: 0x10 */
  __IO uint32_t FIFO_STAT;                         /**< PDM FIFO Status register, offset: 0x14 */
       uint8_t RESERVED_1[12];
  __I  uint32_t DATACH[PDM_DATACHN_COUNT];         /**< PDM Output Result Register, array offset: 0x24, array step: 0x4 */
       uint8_t RESERVED_2[32];
  __IO uint32_t DC_CTRL;                           /**< PDM DC Remover Control register, offset: 0x64 */
       uint8_t RESERVED_3[12];
  __IO uint32_t RANGE_CTRL;                        /**< PDM Range Control register, offset: 0x74 */
       uint8_t RESERVED_4[4];
  __IO uint32_t RANGE_STAT;                        /**< PDM Range Status register, offset: 0x7C */
       uint8_t RESERVED_5[16];
  __IO uint32_t VAD0_CTRL_1;                       /**< Voice Activity Detector 0 Control register, offset: 0x90 */
  __IO uint32_t VAD0_CTRL_2;                       /**< Voice Activity Detector 0 Control register, offset: 0x94 */
  __IO uint32_t VAD0_STAT;                         /**< Voice Activity Detector 0 Status register, offset: 0x98 */
  __IO uint32_t VAD0_SCONFIG;                      /**< Voice Activity Detector 0 Signal Configuration, offset: 0x9C */
  __IO uint32_t VAD0_NCONFIG;                      /**< Voice Activity Detector 0 Noise Configuration, offset: 0xA0 */
  __I  uint32_t VAD0_NDATA;                        /**< Voice Activity Detector 0 Noise Data, offset: 0xA4 */
  __IO uint32_t VAD0_ZCD;                          /**< Voice Activity Detector 0 Zero-Crossing Detector, offset: 0xA8 */
} PDM_Type;

/* ----------------------------------------------------------------------------
   -- PDM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDM_Register_Masks PDM Register Masks
 * @{
 */

/*! @name CTRL_1 - PDM Control register 1 */
/*! @{ */

#define PDM_CTRL_1_CH0EN_MASK                    (0x1U)
#define PDM_CTRL_1_CH0EN_SHIFT                   (0U)
/*! CH0EN - Channel 0 Enable */
#define PDM_CTRL_1_CH0EN(x)                      (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_CH0EN_SHIFT)) & PDM_CTRL_1_CH0EN_MASK)

#define PDM_CTRL_1_CH1EN_MASK                    (0x2U)
#define PDM_CTRL_1_CH1EN_SHIFT                   (1U)
/*! CH1EN - Channel 1 Enable */
#define PDM_CTRL_1_CH1EN(x)                      (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_CH1EN_SHIFT)) & PDM_CTRL_1_CH1EN_MASK)

#define PDM_CTRL_1_CH2EN_MASK                    (0x4U)
#define PDM_CTRL_1_CH2EN_SHIFT                   (2U)
/*! CH2EN - Channel 2 Enable */
#define PDM_CTRL_1_CH2EN(x)                      (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_CH2EN_SHIFT)) & PDM_CTRL_1_CH2EN_MASK)

#define PDM_CTRL_1_CH3EN_MASK                    (0x8U)
#define PDM_CTRL_1_CH3EN_SHIFT                   (3U)
/*! CH3EN - Channel 3 Enable */
#define PDM_CTRL_1_CH3EN(x)                      (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_CH3EN_SHIFT)) & PDM_CTRL_1_CH3EN_MASK)

#define PDM_CTRL_1_CH4EN_MASK                    (0x10U)
#define PDM_CTRL_1_CH4EN_SHIFT                   (4U)
/*! CH4EN - Channel 4 Enable */
#define PDM_CTRL_1_CH4EN(x)                      (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_CH4EN_SHIFT)) & PDM_CTRL_1_CH4EN_MASK)

#define PDM_CTRL_1_CH5EN_MASK                    (0x20U)
#define PDM_CTRL_1_CH5EN_SHIFT                   (5U)
/*! CH5EN - Channel 5 Enable */
#define PDM_CTRL_1_CH5EN(x)                      (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_CH5EN_SHIFT)) & PDM_CTRL_1_CH5EN_MASK)

#define PDM_CTRL_1_CH6EN_MASK                    (0x40U)
#define PDM_CTRL_1_CH6EN_SHIFT                   (6U)
/*! CH6EN - Channel 6 Enable */
#define PDM_CTRL_1_CH6EN(x)                      (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_CH6EN_SHIFT)) & PDM_CTRL_1_CH6EN_MASK)

#define PDM_CTRL_1_CH7EN_MASK                    (0x80U)
#define PDM_CTRL_1_CH7EN_SHIFT                   (7U)
/*! CH7EN - Channel 7 Enable */
#define PDM_CTRL_1_CH7EN(x)                      (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_CH7EN_SHIFT)) & PDM_CTRL_1_CH7EN_MASK)

#define PDM_CTRL_1_ERREN_MASK                    (0x800000U)
#define PDM_CTRL_1_ERREN_SHIFT                   (23U)
/*! ERREN - Error Interruption Enable
 *  0b0..Error Interrupts disabled
 *  0b1..Error Interrupts enabled
 */
#define PDM_CTRL_1_ERREN(x)                      (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_ERREN_SHIFT)) & PDM_CTRL_1_ERREN_MASK)

#define PDM_CTRL_1_DISEL_MASK                    (0x3000000U)
#define PDM_CTRL_1_DISEL_SHIFT                   (24U)
/*! DISEL - DMA Interrupt Selection
 *  0b00..DMA and interrupt requests disabled
 *  0b01..DMA requests enabled
 *  0b10..Interrupt requests enabled
 *  0b11..Reserved
 */
#define PDM_CTRL_1_DISEL(x)                      (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_DISEL_SHIFT)) & PDM_CTRL_1_DISEL_MASK)

#define PDM_CTRL_1_DBGE_MASK                     (0x4000000U)
#define PDM_CTRL_1_DBGE_SHIFT                    (26U)
/*! DBGE - Module Enable in Debug
 *  0b0..Disabled after completing the current frame
 *  0b1..Enabled
 */
#define PDM_CTRL_1_DBGE(x)                       (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_DBGE_SHIFT)) & PDM_CTRL_1_DBGE_MASK)

#define PDM_CTRL_1_SRES_MASK                     (0x8000000U)
#define PDM_CTRL_1_SRES_SHIFT                    (27U)
/*! SRES - Software-reset bit
 *  0b0..No action
 *  0b1..Software reset
 */
#define PDM_CTRL_1_SRES(x)                       (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_SRES_SHIFT)) & PDM_CTRL_1_SRES_MASK)

#define PDM_CTRL_1_DBG_MASK                      (0x10000000U)
#define PDM_CTRL_1_DBG_SHIFT                     (28U)
/*! DBG - Debug Mode
 *  0b0..Normal Mode
 *  0b1..Debug Mode
 */
#define PDM_CTRL_1_DBG(x)                        (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_DBG_SHIFT)) & PDM_CTRL_1_DBG_MASK)

#define PDM_CTRL_1_PDMIEN_MASK                   (0x20000000U)
#define PDM_CTRL_1_PDMIEN_SHIFT                  (29U)
/*! PDMIEN - PDM Enable
 *  0b0..PDM stopped
 *  0b1..PDM operation started
 */
#define PDM_CTRL_1_PDMIEN(x)                     (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_PDMIEN_SHIFT)) & PDM_CTRL_1_PDMIEN_MASK)

#define PDM_CTRL_1_DOZEN_MASK                    (0x40000000U)
#define PDM_CTRL_1_DOZEN_SHIFT                   (30U)
/*! DOZEN - DOZE enable */
#define PDM_CTRL_1_DOZEN(x)                      (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_DOZEN_SHIFT)) & PDM_CTRL_1_DOZEN_MASK)

#define PDM_CTRL_1_MDIS_MASK                     (0x80000000U)
#define PDM_CTRL_1_MDIS_SHIFT                    (31U)
/*! MDIS - Module Disable
 *  0b0..Normal Mode
 *  0b1..Disable/Low Leakage Mode
 */
#define PDM_CTRL_1_MDIS(x)                       (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_1_MDIS_SHIFT)) & PDM_CTRL_1_MDIS_MASK)
/*! @} */

/*! @name CTRL_2 - PDM Control register 2 */
/*! @{ */

#define PDM_CTRL_2_CLKDIV_MASK                   (0xFFU)
#define PDM_CTRL_2_CLKDIV_SHIFT                  (0U)
/*! CLKDIV - Clock Divider */
#define PDM_CTRL_2_CLKDIV(x)                     (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_2_CLKDIV_SHIFT)) & PDM_CTRL_2_CLKDIV_MASK)

#define PDM_CTRL_2_CICOSR_MASK                   (0xF0000U)
#define PDM_CTRL_2_CICOSR_SHIFT                  (16U)
/*! CICOSR - CIC Decimation Rate */
#define PDM_CTRL_2_CICOSR(x)                     (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_2_CICOSR_SHIFT)) & PDM_CTRL_2_CICOSR_MASK)

#define PDM_CTRL_2_QSEL_MASK                     (0xE000000U)
#define PDM_CTRL_2_QSEL_SHIFT                    (25U)
/*! QSEL - Quality Mode
 *  0b000..Medium quality mode
 *  0b001..High quality mode
 *  0b100..Very low quality 2 mode
 *  0b101..Very low quality 1 mode
 *  0b110..Very low quality 0 mode
 *  0b111..Low quality mode
 */
#define PDM_CTRL_2_QSEL(x)                       (((uint32_t)(((uint32_t)(x)) << PDM_CTRL_2_QSEL_SHIFT)) & PDM_CTRL_2_QSEL_MASK)
/*! @} */

/*! @name STAT - PDM Status register */
/*! @{ */

#define PDM_STAT_CH0F_MASK                       (0x1U)
#define PDM_STAT_CH0F_SHIFT                      (0U)
/*! CH0F - Channel 0 Output Data Flag
 *  0b0..Channel's FIFO did not reach the number of elements configured in watermark bit-field
 *  0b1..Channel's FIFO reached the number of elements configured in watermark bit-field
 */
#define PDM_STAT_CH0F(x)                         (((uint32_t)(((uint32_t)(x)) << PDM_STAT_CH0F_SHIFT)) & PDM_STAT_CH0F_MASK)

#define PDM_STAT_CH1F_MASK                       (0x2U)
#define PDM_STAT_CH1F_SHIFT                      (1U)
/*! CH1F - Channel 1 Output Data Flag
 *  0b0..Channel's FIFO did not reach the number of elements configured in watermark bit-field
 *  0b1..Channel's FIFO reached the number of elements configured in watermark bit-field
 */
#define PDM_STAT_CH1F(x)                         (((uint32_t)(((uint32_t)(x)) << PDM_STAT_CH1F_SHIFT)) & PDM_STAT_CH1F_MASK)

#define PDM_STAT_CH2F_MASK                       (0x4U)
#define PDM_STAT_CH2F_SHIFT                      (2U)
/*! CH2F - Channel 2 Output Data Flag
 *  0b0..Channel's FIFO did not reach the number of elements configured in watermark bit-field
 *  0b1..Channel's FIFO reached the number of elements configured in watermark bit-field
 */
#define PDM_STAT_CH2F(x)                         (((uint32_t)(((uint32_t)(x)) << PDM_STAT_CH2F_SHIFT)) & PDM_STAT_CH2F_MASK)

#define PDM_STAT_CH3F_MASK                       (0x8U)
#define PDM_STAT_CH3F_SHIFT                      (3U)
/*! CH3F - Channel 3 Output Data Flag
 *  0b0..Channel's FIFO did not reach the number of elements configured in watermark bit-field
 *  0b1..Channel's FIFO reached the number of elements configured in watermark bit-field
 */
#define PDM_STAT_CH3F(x)                         (((uint32_t)(((uint32_t)(x)) << PDM_STAT_CH3F_SHIFT)) & PDM_STAT_CH3F_MASK)

#define PDM_STAT_CH4F_MASK                       (0x10U)
#define PDM_STAT_CH4F_SHIFT                      (4U)
/*! CH4F - Channel 4 Output Data Flag
 *  0b0..Channel's FIFO did not reach the number of elements configured in watermark bit-field
 *  0b1..Channel's FIFO reached the number of elements configured in watermark bit-field
 */
#define PDM_STAT_CH4F(x)                         (((uint32_t)(((uint32_t)(x)) << PDM_STAT_CH4F_SHIFT)) & PDM_STAT_CH4F_MASK)

#define PDM_STAT_CH5F_MASK                       (0x20U)
#define PDM_STAT_CH5F_SHIFT                      (5U)
/*! CH5F - Channel 5 Output Data Flag
 *  0b0..Channel's FIFO did not reach the number of elements configured in watermark bit-field
 *  0b1..Channel's FIFO reached the number of elements configured in watermark bit-field
 */
#define PDM_STAT_CH5F(x)                         (((uint32_t)(((uint32_t)(x)) << PDM_STAT_CH5F_SHIFT)) & PDM_STAT_CH5F_MASK)

#define PDM_STAT_CH6F_MASK                       (0x40U)
#define PDM_STAT_CH6F_SHIFT                      (6U)
/*! CH6F - Channel 6 Output Data Flag
 *  0b0..Channel's FIFO did not reach the number of elements configured in watermark bit-field
 *  0b1..Channel's FIFO reached the number of elements configured in watermark bit-field
 */
#define PDM_STAT_CH6F(x)                         (((uint32_t)(((uint32_t)(x)) << PDM_STAT_CH6F_SHIFT)) & PDM_STAT_CH6F_MASK)

#define PDM_STAT_CH7F_MASK                       (0x80U)
#define PDM_STAT_CH7F_SHIFT                      (7U)
/*! CH7F - Channel 7 Output Data Flag
 *  0b0..Channel's FIFO did not reach the number of elements configured in watermark bit-field
 *  0b1..Channel's FIFO reached the number of elements configured in watermark bit-field
 */
#define PDM_STAT_CH7F(x)                         (((uint32_t)(((uint32_t)(x)) << PDM_STAT_CH7F_SHIFT)) & PDM_STAT_CH7F_MASK)

#define PDM_STAT_LOWFREQF_MASK                   (0x20000000U)
#define PDM_STAT_LOWFREQF_SHIFT                  (29U)
/*! LOWFREQF - Low Frequency Flag
 *  0b0..CLKDIV value is OK
 *  0b1..CLKDIV value is too low
 */
#define PDM_STAT_LOWFREQF(x)                     (((uint32_t)(((uint32_t)(x)) << PDM_STAT_LOWFREQF_SHIFT)) & PDM_STAT_LOWFREQF_MASK)

#define PDM_STAT_FIR_RDY_MASK                    (0x40000000U)
#define PDM_STAT_FIR_RDY_SHIFT                   (30U)
/*! FIR_RDY - Filter Data Ready
 *  0b0..Filter data is not reliable
 *  0b1..Filter data is reliable
 */
#define PDM_STAT_FIR_RDY(x)                      (((uint32_t)(((uint32_t)(x)) << PDM_STAT_FIR_RDY_SHIFT)) & PDM_STAT_FIR_RDY_MASK)

#define PDM_STAT_BSY_FIL_MASK                    (0x80000000U)
#define PDM_STAT_BSY_FIL_SHIFT                   (31U)
/*! BSY_FIL - Busy Flag
 *  0b0..PDM is stopped
 *  0b1..PDM is running
 */
#define PDM_STAT_BSY_FIL(x)                      (((uint32_t)(((uint32_t)(x)) << PDM_STAT_BSY_FIL_SHIFT)) & PDM_STAT_BSY_FIL_MASK)
/*! @} */

/*! @name FIFO_CTRL - PDM FIFO Control register */
/*! @{ */

#define PDM_FIFO_CTRL_FIFOWMK_MASK               (0x7U)
#define PDM_FIFO_CTRL_FIFOWMK_SHIFT              (0U)
/*! FIFOWMK - FIFO Watermark Control */
#define PDM_FIFO_CTRL_FIFOWMK(x)                 (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_CTRL_FIFOWMK_SHIFT)) & PDM_FIFO_CTRL_FIFOWMK_MASK)
/*! @} */

/*! @name FIFO_STAT - PDM FIFO Status register */
/*! @{ */

#define PDM_FIFO_STAT_FIFOOVF0_MASK              (0x1U)
#define PDM_FIFO_STAT_FIFOOVF0_SHIFT             (0U)
/*! FIFOOVF0 - FIFO Overflow Exception flag for Channel 0
 *  0b0..No exception by FIFO overflow
 *  0b1..Exception by FIFO overflow
 */
#define PDM_FIFO_STAT_FIFOOVF0(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOOVF0_SHIFT)) & PDM_FIFO_STAT_FIFOOVF0_MASK)

#define PDM_FIFO_STAT_FIFOOVF1_MASK              (0x2U)
#define PDM_FIFO_STAT_FIFOOVF1_SHIFT             (1U)
/*! FIFOOVF1 - FIFO Overflow Exception flag for Channel 1
 *  0b0..No exception by FIFO overflow
 *  0b1..Exception by FIFO overflow
 */
#define PDM_FIFO_STAT_FIFOOVF1(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOOVF1_SHIFT)) & PDM_FIFO_STAT_FIFOOVF1_MASK)

#define PDM_FIFO_STAT_FIFOOVF2_MASK              (0x4U)
#define PDM_FIFO_STAT_FIFOOVF2_SHIFT             (2U)
/*! FIFOOVF2 - FIFO Overflow Exception flag for Channel 2
 *  0b0..No exception by FIFO overflow
 *  0b1..Exception by FIFO overflow
 */
#define PDM_FIFO_STAT_FIFOOVF2(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOOVF2_SHIFT)) & PDM_FIFO_STAT_FIFOOVF2_MASK)

#define PDM_FIFO_STAT_FIFOOVF3_MASK              (0x8U)
#define PDM_FIFO_STAT_FIFOOVF3_SHIFT             (3U)
/*! FIFOOVF3 - FIFO Overflow Exception flag for Channel 3
 *  0b0..No exception by FIFO overflow
 *  0b1..Exception by FIFO overflow
 */
#define PDM_FIFO_STAT_FIFOOVF3(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOOVF3_SHIFT)) & PDM_FIFO_STAT_FIFOOVF3_MASK)

#define PDM_FIFO_STAT_FIFOOVF4_MASK              (0x10U)
#define PDM_FIFO_STAT_FIFOOVF4_SHIFT             (4U)
/*! FIFOOVF4 - FIFO Overflow Exception flag for Channel 4
 *  0b0..No exception by FIFO overflow
 *  0b1..Exception by FIFO overflow
 */
#define PDM_FIFO_STAT_FIFOOVF4(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOOVF4_SHIFT)) & PDM_FIFO_STAT_FIFOOVF4_MASK)

#define PDM_FIFO_STAT_FIFOOVF5_MASK              (0x20U)
#define PDM_FIFO_STAT_FIFOOVF5_SHIFT             (5U)
/*! FIFOOVF5 - FIFO Overflow Exception flag for Channel 5
 *  0b0..No exception by FIFO overflow
 *  0b1..Exception by FIFO overflow
 */
#define PDM_FIFO_STAT_FIFOOVF5(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOOVF5_SHIFT)) & PDM_FIFO_STAT_FIFOOVF5_MASK)

#define PDM_FIFO_STAT_FIFOOVF6_MASK              (0x40U)
#define PDM_FIFO_STAT_FIFOOVF6_SHIFT             (6U)
/*! FIFOOVF6 - FIFO Overflow Exception flag for Channel 6
 *  0b0..No exception by FIFO overflow
 *  0b1..Exception by FIFO overflow
 */
#define PDM_FIFO_STAT_FIFOOVF6(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOOVF6_SHIFT)) & PDM_FIFO_STAT_FIFOOVF6_MASK)

#define PDM_FIFO_STAT_FIFOOVF7_MASK              (0x80U)
#define PDM_FIFO_STAT_FIFOOVF7_SHIFT             (7U)
/*! FIFOOVF7 - FIFO Overflow Exception flag for Channel 7
 *  0b0..No exception by FIFO overflow
 *  0b1..Exception by FIFO overflow
 */
#define PDM_FIFO_STAT_FIFOOVF7(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOOVF7_SHIFT)) & PDM_FIFO_STAT_FIFOOVF7_MASK)

#define PDM_FIFO_STAT_FIFOUND0_MASK              (0x100U)
#define PDM_FIFO_STAT_FIFOUND0_SHIFT             (8U)
/*! FIFOUND0 - FIFO Underflow Exception flag for Channel 0
 *  0b0..No exception by FIFO Underflow
 *  0b1..Exception by FIFO underflow
 */
#define PDM_FIFO_STAT_FIFOUND0(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOUND0_SHIFT)) & PDM_FIFO_STAT_FIFOUND0_MASK)

#define PDM_FIFO_STAT_FIFOUND1_MASK              (0x200U)
#define PDM_FIFO_STAT_FIFOUND1_SHIFT             (9U)
/*! FIFOUND1 - FIFO Underflow Exception flag for Channel 1
 *  0b0..No exception by FIFO Underflow
 *  0b1..Exception by FIFO underflow
 */
#define PDM_FIFO_STAT_FIFOUND1(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOUND1_SHIFT)) & PDM_FIFO_STAT_FIFOUND1_MASK)

#define PDM_FIFO_STAT_FIFOUND2_MASK              (0x400U)
#define PDM_FIFO_STAT_FIFOUND2_SHIFT             (10U)
/*! FIFOUND2 - FIFO Underflow Exception flag for Channel 2
 *  0b0..No exception by FIFO Underflow
 *  0b1..Exception by FIFO underflow
 */
#define PDM_FIFO_STAT_FIFOUND2(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOUND2_SHIFT)) & PDM_FIFO_STAT_FIFOUND2_MASK)

#define PDM_FIFO_STAT_FIFOUND3_MASK              (0x800U)
#define PDM_FIFO_STAT_FIFOUND3_SHIFT             (11U)
/*! FIFOUND3 - FIFO Underflow Exception flag for Channel 3
 *  0b0..No exception by FIFO Underflow
 *  0b1..Exception by FIFO underflow
 */
#define PDM_FIFO_STAT_FIFOUND3(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOUND3_SHIFT)) & PDM_FIFO_STAT_FIFOUND3_MASK)

#define PDM_FIFO_STAT_FIFOUND4_MASK              (0x1000U)
#define PDM_FIFO_STAT_FIFOUND4_SHIFT             (12U)
/*! FIFOUND4 - FIFO Underflow Exception flag for Channel 4
 *  0b0..No exception by FIFO Underflow
 *  0b1..Exception by FIFO underflow
 */
#define PDM_FIFO_STAT_FIFOUND4(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOUND4_SHIFT)) & PDM_FIFO_STAT_FIFOUND4_MASK)

#define PDM_FIFO_STAT_FIFOUND5_MASK              (0x2000U)
#define PDM_FIFO_STAT_FIFOUND5_SHIFT             (13U)
/*! FIFOUND5 - FIFO Underflow Exception flag for Channel 5
 *  0b0..No exception by FIFO Underflow
 *  0b1..Exception by FIFO underflow
 */
#define PDM_FIFO_STAT_FIFOUND5(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOUND5_SHIFT)) & PDM_FIFO_STAT_FIFOUND5_MASK)

#define PDM_FIFO_STAT_FIFOUND6_MASK              (0x4000U)
#define PDM_FIFO_STAT_FIFOUND6_SHIFT             (14U)
/*! FIFOUND6 - FIFO Underflow Exception flag for Channel 6
 *  0b0..No exception by FIFO Underflow
 *  0b1..Exception by FIFO underflow
 */
#define PDM_FIFO_STAT_FIFOUND6(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOUND6_SHIFT)) & PDM_FIFO_STAT_FIFOUND6_MASK)

#define PDM_FIFO_STAT_FIFOUND7_MASK              (0x8000U)
#define PDM_FIFO_STAT_FIFOUND7_SHIFT             (15U)
/*! FIFOUND7 - FIFO Underflow Exception flag for Channel 7
 *  0b0..No exception by FIFO Underflow
 *  0b1..Exception by FIFO underflow
 */
#define PDM_FIFO_STAT_FIFOUND7(x)                (((uint32_t)(((uint32_t)(x)) << PDM_FIFO_STAT_FIFOUND7_SHIFT)) & PDM_FIFO_STAT_FIFOUND7_MASK)
/*! @} */

/*! @name DATACH - PDM Output Result Register */
/*! @{ */

#define PDM_DATACH_DATA_MASK                     (0xFFFFFFFFU)
#define PDM_DATACH_DATA_SHIFT                    (0U)
/*! DATA - Channel n Data */
#define PDM_DATACH_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << PDM_DATACH_DATA_SHIFT)) & PDM_DATACH_DATA_MASK)
/*! @} */

/* The count of PDM_DATACH */
#define PDM_DATACH_COUNT                         (8U)

/*! @name DC_CTRL - PDM DC Remover Control register */
/*! @{ */

#define PDM_DC_CTRL_DCCONFIG0_MASK               (0x3U)
#define PDM_DC_CTRL_DCCONFIG0_SHIFT              (0U)
/*! DCCONFIG0 - Channel 0 DC Remover Configuration
 *  0b00..DC Remover cut-off at 21Hz
 *  0b01..DC Remover cut-off at 83Hz
 *  0b10..DC Remover cut-off at 152Hz
 *  0b11..DC Remover is bypassed
 */
#define PDM_DC_CTRL_DCCONFIG0(x)                 (((uint32_t)(((uint32_t)(x)) << PDM_DC_CTRL_DCCONFIG0_SHIFT)) & PDM_DC_CTRL_DCCONFIG0_MASK)

#define PDM_DC_CTRL_DCCONFIG1_MASK               (0xCU)
#define PDM_DC_CTRL_DCCONFIG1_SHIFT              (2U)
/*! DCCONFIG1 - Channel 1 DC Remover Configuration
 *  0b00..DC Remover cut-off at 21Hz
 *  0b01..DC Remover cut-off at 83Hz
 *  0b10..DC Remover cut-off at 152Hz
 *  0b11..DC Remover is bypassed
 */
#define PDM_DC_CTRL_DCCONFIG1(x)                 (((uint32_t)(((uint32_t)(x)) << PDM_DC_CTRL_DCCONFIG1_SHIFT)) & PDM_DC_CTRL_DCCONFIG1_MASK)

#define PDM_DC_CTRL_DCCONFIG2_MASK               (0x30U)
#define PDM_DC_CTRL_DCCONFIG2_SHIFT              (4U)
/*! DCCONFIG2 - Channel 2 DC Remover Configuration
 *  0b00..DC Remover cut-off at 21Hz
 *  0b01..DC Remover cut-off at 83Hz
 *  0b10..DC Remover cut-off at 152Hz
 *  0b11..DC Remover is bypassed
 */
#define PDM_DC_CTRL_DCCONFIG2(x)                 (((uint32_t)(((uint32_t)(x)) << PDM_DC_CTRL_DCCONFIG2_SHIFT)) & PDM_DC_CTRL_DCCONFIG2_MASK)

#define PDM_DC_CTRL_DCCONFIG3_MASK               (0xC0U)
#define PDM_DC_CTRL_DCCONFIG3_SHIFT              (6U)
/*! DCCONFIG3 - Channel 3 DC Remover Configuration
 *  0b00..DC Remover cut-off at 21Hz
 *  0b01..DC Remover cut-off at 83Hz
 *  0b10..DC Remover cut-off at 152Hz
 *  0b11..DC Remover is bypassed
 */
#define PDM_DC_CTRL_DCCONFIG3(x)                 (((uint32_t)(((uint32_t)(x)) << PDM_DC_CTRL_DCCONFIG3_SHIFT)) & PDM_DC_CTRL_DCCONFIG3_MASK)

#define PDM_DC_CTRL_DCCONFIG4_MASK               (0x300U)
#define PDM_DC_CTRL_DCCONFIG4_SHIFT              (8U)
/*! DCCONFIG4 - Channel 4 DC Remover Configuration
 *  0b00..DC Remover cut-off at 21Hz
 *  0b01..DC Remover cut-off at 83Hz
 *  0b10..DC Remover cut-off at 152Hz
 *  0b11..DC Remover is bypassed
 */
#define PDM_DC_CTRL_DCCONFIG4(x)                 (((uint32_t)(((uint32_t)(x)) << PDM_DC_CTRL_DCCONFIG4_SHIFT)) & PDM_DC_CTRL_DCCONFIG4_MASK)

#define PDM_DC_CTRL_DCCONFIG5_MASK               (0xC00U)
#define PDM_DC_CTRL_DCCONFIG5_SHIFT              (10U)
/*! DCCONFIG5 - Channel 5 DC Remover Configuration
 *  0b00..DC Remover cut-off at 21Hz
 *  0b01..DC Remover cut-off at 83Hz
 *  0b10..DC Remover cut-off at 152Hz
 *  0b11..DC Remover is bypassed
 */
#define PDM_DC_CTRL_DCCONFIG5(x)                 (((uint32_t)(((uint32_t)(x)) << PDM_DC_CTRL_DCCONFIG5_SHIFT)) & PDM_DC_CTRL_DCCONFIG5_MASK)

#define PDM_DC_CTRL_DCCONFIG6_MASK               (0x3000U)
#define PDM_DC_CTRL_DCCONFIG6_SHIFT              (12U)
/*! DCCONFIG6 - Channel 6 DC Remover Configuration
 *  0b00..DC Remover cut-off at 21Hz
 *  0b01..DC Remover cut-off at 83Hz
 *  0b10..DC Remover cut-off at 152Hz
 *  0b11..DC Remover is bypassed
 */
#define PDM_DC_CTRL_DCCONFIG6(x)                 (((uint32_t)(((uint32_t)(x)) << PDM_DC_CTRL_DCCONFIG6_SHIFT)) & PDM_DC_CTRL_DCCONFIG6_MASK)

#define PDM_DC_CTRL_DCCONFIG7_MASK               (0xC000U)
#define PDM_DC_CTRL_DCCONFIG7_SHIFT              (14U)
/*! DCCONFIG7 - Channel 7 DC Remover Configuration
 *  0b00..DC Remover cut-off at 21Hz
 *  0b01..DC Remover cut-off at 83Hz
 *  0b10..DC Remover cut-off at 152Hz
 *  0b11..DC Remover is bypassed
 */
#define PDM_DC_CTRL_DCCONFIG7(x)                 (((uint32_t)(((uint32_t)(x)) << PDM_DC_CTRL_DCCONFIG7_SHIFT)) & PDM_DC_CTRL_DCCONFIG7_MASK)
/*! @} */

/*! @name RANGE_CTRL - PDM Range Control register */
/*! @{ */

#define PDM_RANGE_CTRL_RANGEADJ0_MASK            (0xFU)
#define PDM_RANGE_CTRL_RANGEADJ0_SHIFT           (0U)
/*! RANGEADJ0 - Channel 0 Range Adjustment */
#define PDM_RANGE_CTRL_RANGEADJ0(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_CTRL_RANGEADJ0_SHIFT)) & PDM_RANGE_CTRL_RANGEADJ0_MASK)

#define PDM_RANGE_CTRL_RANGEADJ1_MASK            (0xF0U)
#define PDM_RANGE_CTRL_RANGEADJ1_SHIFT           (4U)
/*! RANGEADJ1 - Channel 1 Range Adjustment */
#define PDM_RANGE_CTRL_RANGEADJ1(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_CTRL_RANGEADJ1_SHIFT)) & PDM_RANGE_CTRL_RANGEADJ1_MASK)

#define PDM_RANGE_CTRL_RANGEADJ2_MASK            (0xF00U)
#define PDM_RANGE_CTRL_RANGEADJ2_SHIFT           (8U)
/*! RANGEADJ2 - Channel 2 Range Adjustment */
#define PDM_RANGE_CTRL_RANGEADJ2(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_CTRL_RANGEADJ2_SHIFT)) & PDM_RANGE_CTRL_RANGEADJ2_MASK)

#define PDM_RANGE_CTRL_RANGEADJ3_MASK            (0xF000U)
#define PDM_RANGE_CTRL_RANGEADJ3_SHIFT           (12U)
/*! RANGEADJ3 - Channel 3 Range Adjustment */
#define PDM_RANGE_CTRL_RANGEADJ3(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_CTRL_RANGEADJ3_SHIFT)) & PDM_RANGE_CTRL_RANGEADJ3_MASK)

#define PDM_RANGE_CTRL_RANGEADJ4_MASK            (0xF0000U)
#define PDM_RANGE_CTRL_RANGEADJ4_SHIFT           (16U)
/*! RANGEADJ4 - Channel 4 Range Adjustment */
#define PDM_RANGE_CTRL_RANGEADJ4(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_CTRL_RANGEADJ4_SHIFT)) & PDM_RANGE_CTRL_RANGEADJ4_MASK)

#define PDM_RANGE_CTRL_RANGEADJ5_MASK            (0xF00000U)
#define PDM_RANGE_CTRL_RANGEADJ5_SHIFT           (20U)
/*! RANGEADJ5 - Channel 5 Range Adjustment */
#define PDM_RANGE_CTRL_RANGEADJ5(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_CTRL_RANGEADJ5_SHIFT)) & PDM_RANGE_CTRL_RANGEADJ5_MASK)

#define PDM_RANGE_CTRL_RANGEADJ6_MASK            (0xF000000U)
#define PDM_RANGE_CTRL_RANGEADJ6_SHIFT           (24U)
/*! RANGEADJ6 - Channel 6 Range Adjustment */
#define PDM_RANGE_CTRL_RANGEADJ6(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_CTRL_RANGEADJ6_SHIFT)) & PDM_RANGE_CTRL_RANGEADJ6_MASK)

#define PDM_RANGE_CTRL_RANGEADJ7_MASK            (0xF0000000U)
#define PDM_RANGE_CTRL_RANGEADJ7_SHIFT           (28U)
/*! RANGEADJ7 - Channel 7 Range Adjustment */
#define PDM_RANGE_CTRL_RANGEADJ7(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_CTRL_RANGEADJ7_SHIFT)) & PDM_RANGE_CTRL_RANGEADJ7_MASK)
/*! @} */

/*! @name RANGE_STAT - PDM Range Status register */
/*! @{ */

#define PDM_RANGE_STAT_RANGEOVF0_MASK            (0x1U)
#define PDM_RANGE_STAT_RANGEOVF0_SHIFT           (0U)
/*! RANGEOVF0 - Channel 0 Range Overflow Error Flag
 *  0b0..No exception by range overflow
 *  0b1..Exception by range overflow
 */
#define PDM_RANGE_STAT_RANGEOVF0(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEOVF0_SHIFT)) & PDM_RANGE_STAT_RANGEOVF0_MASK)

#define PDM_RANGE_STAT_RANGEOVF1_MASK            (0x2U)
#define PDM_RANGE_STAT_RANGEOVF1_SHIFT           (1U)
/*! RANGEOVF1 - Channel 1 Range Overflow Error Flag
 *  0b0..No exception by range overflow
 *  0b1..Exception by range overflow
 */
#define PDM_RANGE_STAT_RANGEOVF1(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEOVF1_SHIFT)) & PDM_RANGE_STAT_RANGEOVF1_MASK)

#define PDM_RANGE_STAT_RANGEOVF2_MASK            (0x4U)
#define PDM_RANGE_STAT_RANGEOVF2_SHIFT           (2U)
/*! RANGEOVF2 - Channel 2 Range Overflow Error Flag
 *  0b0..No exception by range overflow
 *  0b1..Exception by range overflow
 */
#define PDM_RANGE_STAT_RANGEOVF2(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEOVF2_SHIFT)) & PDM_RANGE_STAT_RANGEOVF2_MASK)

#define PDM_RANGE_STAT_RANGEOVF3_MASK            (0x8U)
#define PDM_RANGE_STAT_RANGEOVF3_SHIFT           (3U)
/*! RANGEOVF3 - Channel 3 Range Overflow Error Flag
 *  0b0..No exception by range overflow
 *  0b1..Exception by range overflow
 */
#define PDM_RANGE_STAT_RANGEOVF3(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEOVF3_SHIFT)) & PDM_RANGE_STAT_RANGEOVF3_MASK)

#define PDM_RANGE_STAT_RANGEOVF4_MASK            (0x10U)
#define PDM_RANGE_STAT_RANGEOVF4_SHIFT           (4U)
/*! RANGEOVF4 - Channel 4 Range Overflow Error Flag
 *  0b0..No exception by range overflow
 *  0b1..Exception by range overflow
 */
#define PDM_RANGE_STAT_RANGEOVF4(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEOVF4_SHIFT)) & PDM_RANGE_STAT_RANGEOVF4_MASK)

#define PDM_RANGE_STAT_RANGEOVF5_MASK            (0x20U)
#define PDM_RANGE_STAT_RANGEOVF5_SHIFT           (5U)
/*! RANGEOVF5 - Channel 5 Range Overflow Error Flag
 *  0b0..No exception by range overflow
 *  0b1..Exception by range overflow
 */
#define PDM_RANGE_STAT_RANGEOVF5(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEOVF5_SHIFT)) & PDM_RANGE_STAT_RANGEOVF5_MASK)

#define PDM_RANGE_STAT_RANGEOVF6_MASK            (0x40U)
#define PDM_RANGE_STAT_RANGEOVF6_SHIFT           (6U)
/*! RANGEOVF6 - Channel 6 Range Overflow Error Flag
 *  0b0..No exception by range overflow
 *  0b1..Exception by range overflow
 */
#define PDM_RANGE_STAT_RANGEOVF6(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEOVF6_SHIFT)) & PDM_RANGE_STAT_RANGEOVF6_MASK)

#define PDM_RANGE_STAT_RANGEOVF7_MASK            (0x80U)
#define PDM_RANGE_STAT_RANGEOVF7_SHIFT           (7U)
/*! RANGEOVF7 - Channel 7 Range Overflow Error Flag
 *  0b0..No exception by range overflow
 *  0b1..Exception by range overflow
 */
#define PDM_RANGE_STAT_RANGEOVF7(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEOVF7_SHIFT)) & PDM_RANGE_STAT_RANGEOVF7_MASK)

#define PDM_RANGE_STAT_RANGEUNF0_MASK            (0x10000U)
#define PDM_RANGE_STAT_RANGEUNF0_SHIFT           (16U)
/*! RANGEUNF0 - Channel 0 Range Underflow Error Flag
 *  0b0..No exception by range underflow
 *  0b1..Exception by range underflow
 */
#define PDM_RANGE_STAT_RANGEUNF0(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEUNF0_SHIFT)) & PDM_RANGE_STAT_RANGEUNF0_MASK)

#define PDM_RANGE_STAT_RANGEUNF1_MASK            (0x20000U)
#define PDM_RANGE_STAT_RANGEUNF1_SHIFT           (17U)
/*! RANGEUNF1 - Channel 1 Range Underflow Error Flag
 *  0b0..No exception by range underflow
 *  0b1..Exception by range underflow
 */
#define PDM_RANGE_STAT_RANGEUNF1(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEUNF1_SHIFT)) & PDM_RANGE_STAT_RANGEUNF1_MASK)

#define PDM_RANGE_STAT_RANGEUNF2_MASK            (0x40000U)
#define PDM_RANGE_STAT_RANGEUNF2_SHIFT           (18U)
/*! RANGEUNF2 - Channel 2 Range Underflow Error Flag
 *  0b0..No exception by range underflow
 *  0b1..Exception by range underflow
 */
#define PDM_RANGE_STAT_RANGEUNF2(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEUNF2_SHIFT)) & PDM_RANGE_STAT_RANGEUNF2_MASK)

#define PDM_RANGE_STAT_RANGEUNF3_MASK            (0x80000U)
#define PDM_RANGE_STAT_RANGEUNF3_SHIFT           (19U)
/*! RANGEUNF3 - Channel 3 Range Underflow Error Flag
 *  0b0..No exception by range underflow
 *  0b1..Exception by range underflow
 */
#define PDM_RANGE_STAT_RANGEUNF3(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEUNF3_SHIFT)) & PDM_RANGE_STAT_RANGEUNF3_MASK)

#define PDM_RANGE_STAT_RANGEUNF4_MASK            (0x100000U)
#define PDM_RANGE_STAT_RANGEUNF4_SHIFT           (20U)
/*! RANGEUNF4 - Channel 4 Range Underflow Error Flag
 *  0b0..No exception by range underflow
 *  0b1..Exception by range underflow
 */
#define PDM_RANGE_STAT_RANGEUNF4(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEUNF4_SHIFT)) & PDM_RANGE_STAT_RANGEUNF4_MASK)

#define PDM_RANGE_STAT_RANGEUNF5_MASK            (0x200000U)
#define PDM_RANGE_STAT_RANGEUNF5_SHIFT           (21U)
/*! RANGEUNF5 - Channel 5 Range Underflow Error Flag
 *  0b0..No exception by range underflow
 *  0b1..Exception by range underflow
 */
#define PDM_RANGE_STAT_RANGEUNF5(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEUNF5_SHIFT)) & PDM_RANGE_STAT_RANGEUNF5_MASK)

#define PDM_RANGE_STAT_RANGEUNF6_MASK            (0x400000U)
#define PDM_RANGE_STAT_RANGEUNF6_SHIFT           (22U)
/*! RANGEUNF6 - Channel 6 Range Underflow Error Flag
 *  0b0..No exception by range underflow
 *  0b1..Exception by range underflow
 */
#define PDM_RANGE_STAT_RANGEUNF6(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEUNF6_SHIFT)) & PDM_RANGE_STAT_RANGEUNF6_MASK)

#define PDM_RANGE_STAT_RANGEUNF7_MASK            (0x800000U)
#define PDM_RANGE_STAT_RANGEUNF7_SHIFT           (23U)
/*! RANGEUNF7 - Channel 7 Range Underflow Error Flag
 *  0b0..No exception by range underflow
 *  0b1..Exception by range underflow
 */
#define PDM_RANGE_STAT_RANGEUNF7(x)              (((uint32_t)(((uint32_t)(x)) << PDM_RANGE_STAT_RANGEUNF7_SHIFT)) & PDM_RANGE_STAT_RANGEUNF7_MASK)
/*! @} */

/*! @name VAD0_CTRL_1 - Voice Activity Detector 0 Control register */
/*! @{ */

#define PDM_VAD0_CTRL_1_VADEN_MASK               (0x1U)
#define PDM_VAD0_CTRL_1_VADEN_SHIFT              (0U)
/*! VADEN - Voice Activity Detector Enable
 *  0b0..The HWVAD is disabled
 *  0b1..The HWVAD is enabled
 */
#define PDM_VAD0_CTRL_1_VADEN(x)                 (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_1_VADEN_SHIFT)) & PDM_VAD0_CTRL_1_VADEN_MASK)

#define PDM_VAD0_CTRL_1_VADRST_MASK              (0x2U)
#define PDM_VAD0_CTRL_1_VADRST_SHIFT             (1U)
/*! VADRST - Voice Activity Detector Reset */
#define PDM_VAD0_CTRL_1_VADRST(x)                (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_1_VADRST_SHIFT)) & PDM_VAD0_CTRL_1_VADRST_MASK)

#define PDM_VAD0_CTRL_1_VADIE_MASK               (0x4U)
#define PDM_VAD0_CTRL_1_VADIE_SHIFT              (2U)
/*! VADIE - Voice Activity Detector Interruption Enable
 *  0b0..HWVAD Interrupts disabled
 *  0b1..HWVAD Interrupts enabled
 */
#define PDM_VAD0_CTRL_1_VADIE(x)                 (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_1_VADIE_SHIFT)) & PDM_VAD0_CTRL_1_VADIE_MASK)

#define PDM_VAD0_CTRL_1_VADERIE_MASK             (0x8U)
#define PDM_VAD0_CTRL_1_VADERIE_SHIFT            (3U)
/*! VADERIE - Voice Activity Detector Error Interruption Enable
 *  0b0..HWVAD Error Interrupts disabled
 *  0b1..HWVAD Error Interrupts enabled
 */
#define PDM_VAD0_CTRL_1_VADERIE(x)               (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_1_VADERIE_SHIFT)) & PDM_VAD0_CTRL_1_VADERIE_MASK)

#define PDM_VAD0_CTRL_1_VADST10_MASK             (0x10U)
#define PDM_VAD0_CTRL_1_VADST10_SHIFT            (4U)
/*! VADST10 - Voice Activity Detector Internal Filters Initialization
 *  0b0..Normal operation.
 *  0b1..Filters are initialized.
 */
#define PDM_VAD0_CTRL_1_VADST10(x)               (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_1_VADST10_SHIFT)) & PDM_VAD0_CTRL_1_VADST10_MASK)

#define PDM_VAD0_CTRL_1_VADINITT_MASK            (0x1F00U)
#define PDM_VAD0_CTRL_1_VADINITT_SHIFT           (8U)
/*! VADINITT - Voice Activity Detector Initialization Time */
#define PDM_VAD0_CTRL_1_VADINITT(x)              (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_1_VADINITT_SHIFT)) & PDM_VAD0_CTRL_1_VADINITT_MASK)

#define PDM_VAD0_CTRL_1_VADCICOSR_MASK           (0xF0000U)
#define PDM_VAD0_CTRL_1_VADCICOSR_SHIFT          (16U)
/*! VADCICOSR - Voice Activity Detector CIC Oversampling Rate */
#define PDM_VAD0_CTRL_1_VADCICOSR(x)             (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_1_VADCICOSR_SHIFT)) & PDM_VAD0_CTRL_1_VADCICOSR_MASK)

#define PDM_VAD0_CTRL_1_VADCHSEL_MASK            (0x7000000U)
#define PDM_VAD0_CTRL_1_VADCHSEL_SHIFT           (24U)
/*! VADCHSEL - Voice Activity Detector Channel Selector */
#define PDM_VAD0_CTRL_1_VADCHSEL(x)              (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_1_VADCHSEL_SHIFT)) & PDM_VAD0_CTRL_1_VADCHSEL_MASK)
/*! @} */

/*! @name VAD0_CTRL_2 - Voice Activity Detector 0 Control register */
/*! @{ */

#define PDM_VAD0_CTRL_2_VADHPF_MASK              (0x3U)
#define PDM_VAD0_CTRL_2_VADHPF_SHIFT             (0U)
/*! VADHPF - Voice Activity Detector High-Pass Filter
 *  0b00..Filter bypassed.
 *  0b01..Cut-off frequency at 1750Hz.
 *  0b10..Cut-off frequency at 215Hz.
 *  0b11..Cut-off frequency at 102Hz.
 */
#define PDM_VAD0_CTRL_2_VADHPF(x)                (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_2_VADHPF_SHIFT)) & PDM_VAD0_CTRL_2_VADHPF_MASK)

#define PDM_VAD0_CTRL_2_VADINPGAIN_MASK          (0xF00U)
#define PDM_VAD0_CTRL_2_VADINPGAIN_SHIFT         (8U)
/*! VADINPGAIN - Voice Activity Detector Input Gain */
#define PDM_VAD0_CTRL_2_VADINPGAIN(x)            (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_2_VADINPGAIN_SHIFT)) & PDM_VAD0_CTRL_2_VADINPGAIN_MASK)

#define PDM_VAD0_CTRL_2_VADFRAMET_MASK           (0x3F0000U)
#define PDM_VAD0_CTRL_2_VADFRAMET_SHIFT          (16U)
/*! VADFRAMET - Voice Activity Detector Frame Time */
#define PDM_VAD0_CTRL_2_VADFRAMET(x)             (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_2_VADFRAMET_SHIFT)) & PDM_VAD0_CTRL_2_VADFRAMET_MASK)

#define PDM_VAD0_CTRL_2_VADFOUTDIS_MASK          (0x10000000U)
#define PDM_VAD0_CTRL_2_VADFOUTDIS_SHIFT         (28U)
/*! VADFOUTDIS - Voice Activity Detector Force Output Disable
 *  0b0..Output is enabled.
 *  0b1..Output is disabled.
 */
#define PDM_VAD0_CTRL_2_VADFOUTDIS(x)            (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_2_VADFOUTDIS_SHIFT)) & PDM_VAD0_CTRL_2_VADFOUTDIS_MASK)

#define PDM_VAD0_CTRL_2_VADPREFEN_MASK           (0x40000000U)
#define PDM_VAD0_CTRL_2_VADPREFEN_SHIFT          (30U)
/*! VADPREFEN - Voice Activity Detector Pre Filter Enable
 *  0b0..Pre-filter is bypassed.
 *  0b1..Pre-filter is enabled.
 */
#define PDM_VAD0_CTRL_2_VADPREFEN(x)             (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_2_VADPREFEN_SHIFT)) & PDM_VAD0_CTRL_2_VADPREFEN_MASK)

#define PDM_VAD0_CTRL_2_VADFRENDIS_MASK          (0x80000000U)
#define PDM_VAD0_CTRL_2_VADFRENDIS_SHIFT         (31U)
/*! VADFRENDIS - Voice Activity Detector Frame Energy Disable
 *  0b0..Frame energy calculus enabled.
 *  0b1..Frame energy calculus disabled.
 */
#define PDM_VAD0_CTRL_2_VADFRENDIS(x)            (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_CTRL_2_VADFRENDIS_SHIFT)) & PDM_VAD0_CTRL_2_VADFRENDIS_MASK)
/*! @} */

/*! @name VAD0_STAT - Voice Activity Detector 0 Status register */
/*! @{ */

#define PDM_VAD0_STAT_VADIF_MASK                 (0x1U)
#define PDM_VAD0_STAT_VADIF_SHIFT                (0U)
/*! VADIF - Voice Activity Detector Interrupt Flag
 *  0b0..Voice activity not detected
 *  0b1..Voice activity detected
 */
#define PDM_VAD0_STAT_VADIF(x)                   (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_STAT_VADIF_SHIFT)) & PDM_VAD0_STAT_VADIF_MASK)

#define PDM_VAD0_STAT_VADEF_MASK                 (0x8000U)
#define PDM_VAD0_STAT_VADEF_SHIFT                (15U)
/*! VADEF - Voice Activity Detector Event Flag
 *  0b0..Voice activity not detected
 *  0b1..Voice activity detected
 */
#define PDM_VAD0_STAT_VADEF(x)                   (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_STAT_VADEF_SHIFT)) & PDM_VAD0_STAT_VADEF_MASK)

#define PDM_VAD0_STAT_VADINSATF_MASK             (0x10000U)
#define PDM_VAD0_STAT_VADINSATF_SHIFT            (16U)
/*! VADINSATF - Voice Activity Detector Input Saturation Flag
 *  0b0..No exception
 *  0b1..Exception
 */
#define PDM_VAD0_STAT_VADINSATF(x)               (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_STAT_VADINSATF_SHIFT)) & PDM_VAD0_STAT_VADINSATF_MASK)

#define PDM_VAD0_STAT_VADINITF_MASK              (0x80000000U)
#define PDM_VAD0_STAT_VADINITF_SHIFT             (31U)
/*! VADINITF - Voice Activity Detector Initialization Flag
 *  0b0..HWVAD is not being initialized.
 *  0b1..HWVAD is being initialized.
 */
#define PDM_VAD0_STAT_VADINITF(x)                (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_STAT_VADINITF_SHIFT)) & PDM_VAD0_STAT_VADINITF_MASK)
/*! @} */

/*! @name VAD0_SCONFIG - Voice Activity Detector 0 Signal Configuration */
/*! @{ */

#define PDM_VAD0_SCONFIG_VADSGAIN_MASK           (0xFU)
#define PDM_VAD0_SCONFIG_VADSGAIN_SHIFT          (0U)
/*! VADSGAIN - Voice Activity Detector Signal Gain */
#define PDM_VAD0_SCONFIG_VADSGAIN(x)             (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_SCONFIG_VADSGAIN_SHIFT)) & PDM_VAD0_SCONFIG_VADSGAIN_MASK)

#define PDM_VAD0_SCONFIG_VADSMAXEN_MASK          (0x40000000U)
#define PDM_VAD0_SCONFIG_VADSMAXEN_SHIFT         (30U)
/*! VADSMAXEN - Voice Activity Detector Signal Maximum Enable
 *  0b0..Maximum block is bypassed.
 *  0b1..Maximum block is enabled.
 */
#define PDM_VAD0_SCONFIG_VADSMAXEN(x)            (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_SCONFIG_VADSMAXEN_SHIFT)) & PDM_VAD0_SCONFIG_VADSMAXEN_MASK)

#define PDM_VAD0_SCONFIG_VADSFILEN_MASK          (0x80000000U)
#define PDM_VAD0_SCONFIG_VADSFILEN_SHIFT         (31U)
/*! VADSFILEN - Voice Activity Detector Signal Filter Enable
 *  0b0..Signal filter is disabled.
 *  0b1..Signal filter is enabled.
 */
#define PDM_VAD0_SCONFIG_VADSFILEN(x)            (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_SCONFIG_VADSFILEN_SHIFT)) & PDM_VAD0_SCONFIG_VADSFILEN_MASK)
/*! @} */

/*! @name VAD0_NCONFIG - Voice Activity Detector 0 Noise Configuration */
/*! @{ */

#define PDM_VAD0_NCONFIG_VADNGAIN_MASK           (0xFU)
#define PDM_VAD0_NCONFIG_VADNGAIN_SHIFT          (0U)
/*! VADNGAIN - Voice Activity Detector Noise Gain */
#define PDM_VAD0_NCONFIG_VADNGAIN(x)             (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_NCONFIG_VADNGAIN_SHIFT)) & PDM_VAD0_NCONFIG_VADNGAIN_MASK)

#define PDM_VAD0_NCONFIG_VADNFILADJ_MASK         (0x1F00U)
#define PDM_VAD0_NCONFIG_VADNFILADJ_SHIFT        (8U)
/*! VADNFILADJ - Voice Activity Detector Noise Filter Adjustment */
#define PDM_VAD0_NCONFIG_VADNFILADJ(x)           (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_NCONFIG_VADNFILADJ_SHIFT)) & PDM_VAD0_NCONFIG_VADNFILADJ_MASK)

#define PDM_VAD0_NCONFIG_VADNOREN_MASK           (0x10000000U)
#define PDM_VAD0_NCONFIG_VADNOREN_SHIFT          (28U)
/*! VADNOREN - Voice Activity Detector Noise OR Enable
 *  0b0..Noise input is not decimated.
 *  0b1..Noise input is decimated.
 */
#define PDM_VAD0_NCONFIG_VADNOREN(x)             (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_NCONFIG_VADNOREN_SHIFT)) & PDM_VAD0_NCONFIG_VADNOREN_MASK)

#define PDM_VAD0_NCONFIG_VADNDECEN_MASK          (0x20000000U)
#define PDM_VAD0_NCONFIG_VADNDECEN_SHIFT         (29U)
/*! VADNDECEN - Voice Activity Detector Noise Decimation Enable
 *  0b0..Noise input is not decimated.
 *  0b1..Noise input is decimated.
 */
#define PDM_VAD0_NCONFIG_VADNDECEN(x)            (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_NCONFIG_VADNDECEN_SHIFT)) & PDM_VAD0_NCONFIG_VADNDECEN_MASK)

#define PDM_VAD0_NCONFIG_VADNMINEN_MASK          (0x40000000U)
#define PDM_VAD0_NCONFIG_VADNMINEN_SHIFT         (30U)
/*! VADNMINEN - Voice Activity Detector Noise Minimum Enable
 *  0b0..Minimum block is bypassed.
 *  0b1..Minimum block is enabled.
 */
#define PDM_VAD0_NCONFIG_VADNMINEN(x)            (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_NCONFIG_VADNMINEN_SHIFT)) & PDM_VAD0_NCONFIG_VADNMINEN_MASK)

#define PDM_VAD0_NCONFIG_VADNFILAUTO_MASK        (0x80000000U)
#define PDM_VAD0_NCONFIG_VADNFILAUTO_SHIFT       (31U)
/*! VADNFILAUTO - Voice Activity Detector Noise Filter Auto
 *  0b0..Noise filter is always enabled.
 *  0b1..Noise filter is enabled/disabled based on voice activity information.
 */
#define PDM_VAD0_NCONFIG_VADNFILAUTO(x)          (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_NCONFIG_VADNFILAUTO_SHIFT)) & PDM_VAD0_NCONFIG_VADNFILAUTO_MASK)
/*! @} */

/*! @name VAD0_NDATA - Voice Activity Detector 0 Noise Data */
/*! @{ */

#define PDM_VAD0_NDATA_VADNDATA_MASK             (0xFFFFU)
#define PDM_VAD0_NDATA_VADNDATA_SHIFT            (0U)
/*! VADNDATA - Voice Activity Detector Noise Data */
#define PDM_VAD0_NDATA_VADNDATA(x)               (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_NDATA_VADNDATA_SHIFT)) & PDM_VAD0_NDATA_VADNDATA_MASK)
/*! @} */

/*! @name VAD0_ZCD - Voice Activity Detector 0 Zero-Crossing Detector */
/*! @{ */

#define PDM_VAD0_ZCD_VADZCDEN_MASK               (0x1U)
#define PDM_VAD0_ZCD_VADZCDEN_SHIFT              (0U)
/*! VADZCDEN - Zero-Crossing Detector Enable
 *  0b0..The ZCD is disabled
 *  0b1..The ZCD is enabled
 */
#define PDM_VAD0_ZCD_VADZCDEN(x)                 (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_ZCD_VADZCDEN_SHIFT)) & PDM_VAD0_ZCD_VADZCDEN_MASK)

#define PDM_VAD0_ZCD_VADZCDAUTO_MASK             (0x4U)
#define PDM_VAD0_ZCD_VADZCDAUTO_SHIFT            (2U)
/*! VADZCDAUTO - Zero-Crossing Detector Automatic Threshold
 *  0b0..The ZCD threshold is not estimated automatically
 *  0b1..The ZCD threshold is estimated automatically
 */
#define PDM_VAD0_ZCD_VADZCDAUTO(x)               (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_ZCD_VADZCDAUTO_SHIFT)) & PDM_VAD0_ZCD_VADZCDAUTO_MASK)

#define PDM_VAD0_ZCD_VADZCDAND_MASK              (0x10U)
#define PDM_VAD0_ZCD_VADZCDAND_SHIFT             (4U)
/*! VADZCDAND - Zero-Crossing Detector AND Behavior
 *  0b0..The ZCD result is OR'ed with the energy-based detection.
 *  0b1..The ZCD result is AND'ed with the energy-based detection.
 */
#define PDM_VAD0_ZCD_VADZCDAND(x)                (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_ZCD_VADZCDAND_SHIFT)) & PDM_VAD0_ZCD_VADZCDAND_MASK)

#define PDM_VAD0_ZCD_VADZCDADJ_MASK              (0xF00U)
#define PDM_VAD0_ZCD_VADZCDADJ_SHIFT             (8U)
/*! VADZCDADJ - Zero-Crossing Detector Adjustment */
#define PDM_VAD0_ZCD_VADZCDADJ(x)                (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_ZCD_VADZCDADJ_SHIFT)) & PDM_VAD0_ZCD_VADZCDADJ_MASK)

#define PDM_VAD0_ZCD_VADZCDTH_MASK               (0x3FF0000U)
#define PDM_VAD0_ZCD_VADZCDTH_SHIFT              (16U)
/*! VADZCDTH - Zero-Crossing Detector Threshold */
#define PDM_VAD0_ZCD_VADZCDTH(x)                 (((uint32_t)(((uint32_t)(x)) << PDM_VAD0_ZCD_VADZCDTH_SHIFT)) & PDM_VAD0_ZCD_VADZCDTH_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PDM_Register_Masks */


/*!
 * @}
 */ /* end of group PDM_Peripheral_Access_Layer */


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


#endif  /* PERI_PDM_H_ */

