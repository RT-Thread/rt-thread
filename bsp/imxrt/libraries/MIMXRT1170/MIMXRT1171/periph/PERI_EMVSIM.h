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
**         CMSIS Peripheral Access Layer for EMVSIM
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
 * @file PERI_EMVSIM.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for EMVSIM
 *
 * CMSIS Peripheral Access Layer for EMVSIM
 */

#if !defined(PERI_EMVSIM_H_)
#define PERI_EMVSIM_H_                           /**< Symbol preventing repeated inclusion */

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
   -- EMVSIM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EMVSIM_Peripheral_Access_Layer EMVSIM Peripheral Access Layer
 * @{
 */

/** EMVSIM - Register Layout Typedef */
typedef struct {
  __I  uint32_t VER_ID;                            /**< Version ID Register, offset: 0x0 */
  __I  uint32_t PARAM;                             /**< Parameter Register, offset: 0x4 */
  __IO uint32_t CLKCFG;                            /**< Clock Configuration Register, offset: 0x8 */
  __IO uint32_t DIVISOR;                           /**< Baud Rate Divisor Register, offset: 0xC */
  __IO uint32_t CTRL;                              /**< Control Register, offset: 0x10 */
  __IO uint32_t INT_MASK;                          /**< Interrupt Mask Register, offset: 0x14 */
  __IO uint32_t RX_THD;                            /**< Receiver Threshold Register, offset: 0x18 */
  __IO uint32_t TX_THD;                            /**< Transmitter Threshold Register, offset: 0x1C */
  __IO uint32_t RX_STATUS;                         /**< Receive Status Register, offset: 0x20 */
  __IO uint32_t TX_STATUS;                         /**< Transmitter Status Register, offset: 0x24 */
  __IO uint32_t PCSR;                              /**< Port Control and Status Register, offset: 0x28 */
  __I  uint32_t RX_BUF;                            /**< Receive Data Read Buffer, offset: 0x2C */
  __IO uint32_t TX_BUF;                            /**< Transmit Data Buffer, offset: 0x30 */
  __IO uint32_t TX_GETU;                           /**< Transmitter Guard ETU Value Register, offset: 0x34 */
  __IO uint32_t CWT_VAL;                           /**< Character Wait Time Value Register, offset: 0x38 */
  __IO uint32_t BWT_VAL;                           /**< Block Wait Time Value Register, offset: 0x3C */
  __IO uint32_t BGT_VAL;                           /**< Block Guard Time Value Register, offset: 0x40 */
  __IO uint32_t GPCNT0_VAL;                        /**< General Purpose Counter 0 Timeout Value Register, offset: 0x44 */
  __IO uint32_t GPCNT1_VAL;                        /**< General Purpose Counter 1 Timeout Value, offset: 0x48 */
} EMVSIM_Type;

/* ----------------------------------------------------------------------------
   -- EMVSIM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EMVSIM_Register_Masks EMVSIM Register Masks
 * @{
 */

/*! @name VER_ID - Version ID Register */
/*! @{ */

#define EMVSIM_VER_ID_VER_MASK                   (0xFFFFFFFFU)
#define EMVSIM_VER_ID_VER_SHIFT                  (0U)
/*! VER - Version ID of the module */
#define EMVSIM_VER_ID_VER(x)                     (((uint32_t)(((uint32_t)(x)) << EMVSIM_VER_ID_VER_SHIFT)) & EMVSIM_VER_ID_VER_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */

#define EMVSIM_PARAM_RX_FIFO_DEPTH_MASK          (0xFFU)
#define EMVSIM_PARAM_RX_FIFO_DEPTH_SHIFT         (0U)
/*! RX_FIFO_DEPTH - Receive FIFO Depth */
#define EMVSIM_PARAM_RX_FIFO_DEPTH(x)            (((uint32_t)(((uint32_t)(x)) << EMVSIM_PARAM_RX_FIFO_DEPTH_SHIFT)) & EMVSIM_PARAM_RX_FIFO_DEPTH_MASK)

#define EMVSIM_PARAM_TX_FIFO_DEPTH_MASK          (0xFF00U)
#define EMVSIM_PARAM_TX_FIFO_DEPTH_SHIFT         (8U)
/*! TX_FIFO_DEPTH - Transmit FIFO Depth */
#define EMVSIM_PARAM_TX_FIFO_DEPTH(x)            (((uint32_t)(((uint32_t)(x)) << EMVSIM_PARAM_TX_FIFO_DEPTH_SHIFT)) & EMVSIM_PARAM_TX_FIFO_DEPTH_MASK)
/*! @} */

/*! @name CLKCFG - Clock Configuration Register */
/*! @{ */

#define EMVSIM_CLKCFG_CLK_PRSC_MASK              (0xFFU)
#define EMVSIM_CLKCFG_CLK_PRSC_SHIFT             (0U)
/*! CLK_PRSC - Clock Prescaler Value */
#define EMVSIM_CLKCFG_CLK_PRSC(x)                (((uint32_t)(((uint32_t)(x)) << EMVSIM_CLKCFG_CLK_PRSC_SHIFT)) & EMVSIM_CLKCFG_CLK_PRSC_MASK)

#define EMVSIM_CLKCFG_GPCNT1_CLK_SEL_MASK        (0x300U)
#define EMVSIM_CLKCFG_GPCNT1_CLK_SEL_SHIFT       (8U)
/*! GPCNT1_CLK_SEL - General Purpose Counter 1 Clock Select
 *  0b00..Disabled / Reset
 *  0b01..Card Clock
 *  0b10..Receive Clock
 *  0b11..ETU Clock (transmit clock)
 */
#define EMVSIM_CLKCFG_GPCNT1_CLK_SEL(x)          (((uint32_t)(((uint32_t)(x)) << EMVSIM_CLKCFG_GPCNT1_CLK_SEL_SHIFT)) & EMVSIM_CLKCFG_GPCNT1_CLK_SEL_MASK)

#define EMVSIM_CLKCFG_GPCNT0_CLK_SEL_MASK        (0xC00U)
#define EMVSIM_CLKCFG_GPCNT0_CLK_SEL_SHIFT       (10U)
/*! GPCNT0_CLK_SEL - General Purpose Counter 0 Clock Select
 *  0b00..Disabled / Reset
 *  0b01..Card Clock
 *  0b10..Receive Clock
 *  0b11..ETU Clock (transmit clock)
 */
#define EMVSIM_CLKCFG_GPCNT0_CLK_SEL(x)          (((uint32_t)(((uint32_t)(x)) << EMVSIM_CLKCFG_GPCNT0_CLK_SEL_SHIFT)) & EMVSIM_CLKCFG_GPCNT0_CLK_SEL_MASK)
/*! @} */

/*! @name DIVISOR - Baud Rate Divisor Register */
/*! @{ */

#define EMVSIM_DIVISOR_DIVISOR_VALUE_MASK        (0x1FFU)
#define EMVSIM_DIVISOR_DIVISOR_VALUE_SHIFT       (0U)
/*! DIVISOR_VALUE - Divisor (F/D) Value
 *  0b000000000-0b000000100..Invalid. As per ISO 7816 specification, minimum value of F/D is 5
 *  0b000000101-0b011111111..Divisor value F/D
 */
#define EMVSIM_DIVISOR_DIVISOR_VALUE(x)          (((uint32_t)(((uint32_t)(x)) << EMVSIM_DIVISOR_DIVISOR_VALUE_SHIFT)) & EMVSIM_DIVISOR_DIVISOR_VALUE_MASK)
/*! @} */

/*! @name CTRL - Control Register */
/*! @{ */

#define EMVSIM_CTRL_IC_MASK                      (0x1U)
#define EMVSIM_CTRL_IC_SHIFT                     (0U)
/*! IC - Inverse Convention
 *  0b0..Direction convention transfers enabled
 *  0b1..Inverse convention transfers enabled
 */
#define EMVSIM_CTRL_IC(x)                        (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_IC_SHIFT)) & EMVSIM_CTRL_IC_MASK)

#define EMVSIM_CTRL_ICM_MASK                     (0x2U)
#define EMVSIM_CTRL_ICM_SHIFT                    (1U)
/*! ICM - Initial Character Mode
 *  0b0..Initial Character Mode disabled
 *  0b1..Initial Character Mode enabled
 */
#define EMVSIM_CTRL_ICM(x)                       (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_ICM_SHIFT)) & EMVSIM_CTRL_ICM_MASK)

#define EMVSIM_CTRL_ANACK_MASK                   (0x4U)
#define EMVSIM_CTRL_ANACK_SHIFT                  (2U)
/*! ANACK - Auto NACK Enable
 *  0b0..NACK generation on errors disabled
 *  0b1..NACK generation on errors enabled
 */
#define EMVSIM_CTRL_ANACK(x)                     (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_ANACK_SHIFT)) & EMVSIM_CTRL_ANACK_MASK)

#define EMVSIM_CTRL_ONACK_MASK                   (0x8U)
#define EMVSIM_CTRL_ONACK_SHIFT                  (3U)
/*! ONACK - Overrun NACK Enable
 *  0b0..NACK generation on overrun is disabled
 *  0b1..NACK generation on overrun is enabled
 */
#define EMVSIM_CTRL_ONACK(x)                     (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_ONACK_SHIFT)) & EMVSIM_CTRL_ONACK_MASK)

#define EMVSIM_CTRL_FLSH_RX_MASK                 (0x100U)
#define EMVSIM_CTRL_FLSH_RX_SHIFT                (8U)
/*! FLSH_RX - Flush Receiver Bit
 *  0b0..EMVSIM Receiver normal operation
 *  0b1..EMVSIM Receiver held in Reset
 */
#define EMVSIM_CTRL_FLSH_RX(x)                   (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_FLSH_RX_SHIFT)) & EMVSIM_CTRL_FLSH_RX_MASK)

#define EMVSIM_CTRL_FLSH_TX_MASK                 (0x200U)
#define EMVSIM_CTRL_FLSH_TX_SHIFT                (9U)
/*! FLSH_TX - Flush Transmitter Bit
 *  0b0..EMVSIM Transmitter normal operation
 *  0b1..EMVSIM Transmitter held in Reset
 */
#define EMVSIM_CTRL_FLSH_TX(x)                   (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_FLSH_TX_SHIFT)) & EMVSIM_CTRL_FLSH_TX_MASK)

#define EMVSIM_CTRL_SW_RST_MASK                  (0x400U)
#define EMVSIM_CTRL_SW_RST_SHIFT                 (10U)
/*! SW_RST - Software Reset Bit
 *  0b0..EMVSIM Normal operation
 *  0b1..EMVSIM held in Reset
 */
#define EMVSIM_CTRL_SW_RST(x)                    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_SW_RST_SHIFT)) & EMVSIM_CTRL_SW_RST_MASK)

#define EMVSIM_CTRL_KILL_CLOCKS_MASK             (0x800U)
#define EMVSIM_CTRL_KILL_CLOCKS_SHIFT            (11U)
/*! KILL_CLOCKS - Kill all internal clocks
 *  0b0..EMVSIM input clock enabled
 *  0b1..EMVSIM input clock is disabled
 */
#define EMVSIM_CTRL_KILL_CLOCKS(x)               (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_KILL_CLOCKS_SHIFT)) & EMVSIM_CTRL_KILL_CLOCKS_MASK)

#define EMVSIM_CTRL_DOZE_EN_MASK                 (0x1000U)
#define EMVSIM_CTRL_DOZE_EN_SHIFT                (12U)
/*! DOZE_EN - Doze Enable
 *  0b0..DOZE instruction gates all internal EMVSIM clocks as well as the Smart Card clock when the transmit FIFO is empty
 *  0b1..DOZE instruction has no effect on EMVSIM module
 */
#define EMVSIM_CTRL_DOZE_EN(x)                   (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_DOZE_EN_SHIFT)) & EMVSIM_CTRL_DOZE_EN_MASK)

#define EMVSIM_CTRL_STOP_EN_MASK                 (0x2000U)
#define EMVSIM_CTRL_STOP_EN_SHIFT                (13U)
/*! STOP_EN - STOP Enable
 *  0b0..STOP instruction shuts down all EMVSIM clocks
 *  0b1..STOP instruction shuts down all clocks except for the Smart Card Clock (SCK) (clock provided to Smart Card)
 */
#define EMVSIM_CTRL_STOP_EN(x)                   (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_STOP_EN_SHIFT)) & EMVSIM_CTRL_STOP_EN_MASK)

#define EMVSIM_CTRL_RCV_EN_MASK                  (0x10000U)
#define EMVSIM_CTRL_RCV_EN_SHIFT                 (16U)
/*! RCV_EN - Receiver Enable
 *  0b0..EMVSIM Receiver disabled
 *  0b1..EMVSIM Receiver enabled
 */
#define EMVSIM_CTRL_RCV_EN(x)                    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_RCV_EN_SHIFT)) & EMVSIM_CTRL_RCV_EN_MASK)

#define EMVSIM_CTRL_XMT_EN_MASK                  (0x20000U)
#define EMVSIM_CTRL_XMT_EN_SHIFT                 (17U)
/*! XMT_EN - Transmitter Enable
 *  0b0..EMVSIM Transmitter disabled
 *  0b1..EMVSIM Transmitter enabled
 */
#define EMVSIM_CTRL_XMT_EN(x)                    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_XMT_EN_SHIFT)) & EMVSIM_CTRL_XMT_EN_MASK)

#define EMVSIM_CTRL_RCVR_11_MASK                 (0x40000U)
#define EMVSIM_CTRL_RCVR_11_SHIFT                (18U)
/*! RCVR_11 - Receiver 11 ETU Mode Enable
 *  0b0..Receiver configured for 12 ETU operation mode
 *  0b1..Receiver configured for 11 ETU operation mode
 */
#define EMVSIM_CTRL_RCVR_11(x)                   (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_RCVR_11_SHIFT)) & EMVSIM_CTRL_RCVR_11_MASK)

#define EMVSIM_CTRL_RX_DMA_EN_MASK               (0x80000U)
#define EMVSIM_CTRL_RX_DMA_EN_SHIFT              (19U)
/*! RX_DMA_EN - Receive DMA Enable
 *  0b0..No DMA Read Request asserted for Receiver
 *  0b1..DMA Read Request asserted for Receiver
 */
#define EMVSIM_CTRL_RX_DMA_EN(x)                 (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_RX_DMA_EN_SHIFT)) & EMVSIM_CTRL_RX_DMA_EN_MASK)

#define EMVSIM_CTRL_TX_DMA_EN_MASK               (0x100000U)
#define EMVSIM_CTRL_TX_DMA_EN_SHIFT              (20U)
/*! TX_DMA_EN - Transmit DMA Enable
 *  0b0..No DMA Write Request asserted for Transmitter
 *  0b1..DMA Write Request asserted for Transmitter
 */
#define EMVSIM_CTRL_TX_DMA_EN(x)                 (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_TX_DMA_EN_SHIFT)) & EMVSIM_CTRL_TX_DMA_EN_MASK)

#define EMVSIM_CTRL_INV_CRC_VAL_MASK             (0x1000000U)
#define EMVSIM_CTRL_INV_CRC_VAL_SHIFT            (24U)
/*! INV_CRC_VAL - Invert bits in the CRC Output Value
 *  0b0..Bits in CRC Output value are not inverted.
 *  0b1..Bits in CRC Output value are inverted.
 */
#define EMVSIM_CTRL_INV_CRC_VAL(x)               (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_INV_CRC_VAL_SHIFT)) & EMVSIM_CTRL_INV_CRC_VAL_MASK)

#define EMVSIM_CTRL_CRC_OUT_FLIP_MASK            (0x2000000U)
#define EMVSIM_CTRL_CRC_OUT_FLIP_SHIFT           (25U)
/*! CRC_OUT_FLIP - CRC Output Value Bit Reversal or Flip
 *  0b0..Bits within the CRC output bytes are not reversed i.e. 15:0 remains 15:0
 *  0b1..Bits within the CRC output bytes are reversed i.e. 15:0 becomes {8:15,0:7}
 */
#define EMVSIM_CTRL_CRC_OUT_FLIP(x)              (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_CRC_OUT_FLIP_SHIFT)) & EMVSIM_CTRL_CRC_OUT_FLIP_MASK)

#define EMVSIM_CTRL_CRC_IN_FLIP_MASK             (0x4000000U)
#define EMVSIM_CTRL_CRC_IN_FLIP_SHIFT            (26U)
/*! CRC_IN_FLIP - CRC Input Byte's Bit Reversal or Flip Control
 *  0b0..Bits in the input byte are not reversed (i.e. 7:0 remain 7:0) before the CRC calculation
 *  0b1..Bits in the input byte are reversed (i.e. 7:0 becomes 0:7) before CRC calculation
 */
#define EMVSIM_CTRL_CRC_IN_FLIP(x)               (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_CRC_IN_FLIP_SHIFT)) & EMVSIM_CTRL_CRC_IN_FLIP_MASK)

#define EMVSIM_CTRL_CWT_EN_MASK                  (0x8000000U)
#define EMVSIM_CTRL_CWT_EN_SHIFT                 (27U)
/*! CWT_EN - Character Wait Time Counter Enable
 *  0b0..Character Wait time Counter is disabled
 *  0b1..Character Wait time counter is enabled
 */
#define EMVSIM_CTRL_CWT_EN(x)                    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_CWT_EN_SHIFT)) & EMVSIM_CTRL_CWT_EN_MASK)

#define EMVSIM_CTRL_LRC_EN_MASK                  (0x10000000U)
#define EMVSIM_CTRL_LRC_EN_SHIFT                 (28U)
/*! LRC_EN - LRC Enable
 *  0b0..8-bit Linear Redundancy Checking disabled
 *  0b1..8-bit Linear Redundancy Checking enabled
 */
#define EMVSIM_CTRL_LRC_EN(x)                    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_LRC_EN_SHIFT)) & EMVSIM_CTRL_LRC_EN_MASK)

#define EMVSIM_CTRL_CRC_EN_MASK                  (0x20000000U)
#define EMVSIM_CTRL_CRC_EN_SHIFT                 (29U)
/*! CRC_EN - CRC Enable
 *  0b0..16-bit Cyclic Redundancy Checking disabled
 *  0b1..16-bit Cyclic Redundancy Checking enabled
 */
#define EMVSIM_CTRL_CRC_EN(x)                    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_CRC_EN_SHIFT)) & EMVSIM_CTRL_CRC_EN_MASK)

#define EMVSIM_CTRL_XMT_CRC_LRC_MASK             (0x40000000U)
#define EMVSIM_CTRL_XMT_CRC_LRC_SHIFT            (30U)
/*! XMT_CRC_LRC - Transmit CRC or LRC Enable
 *  0b0..No CRC or LRC value is transmitted
 *  0b1..Transmit LRC or CRC info when FIFO empties (whichever is enabled)
 */
#define EMVSIM_CTRL_XMT_CRC_LRC(x)               (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_XMT_CRC_LRC_SHIFT)) & EMVSIM_CTRL_XMT_CRC_LRC_MASK)

#define EMVSIM_CTRL_BWT_EN_MASK                  (0x80000000U)
#define EMVSIM_CTRL_BWT_EN_SHIFT                 (31U)
/*! BWT_EN - Block Wait Time Counter Enable
 *  0b0..Disable BWT, BGT Counters
 *  0b1..Enable BWT, BGT Counters
 */
#define EMVSIM_CTRL_BWT_EN(x)                    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_BWT_EN_SHIFT)) & EMVSIM_CTRL_BWT_EN_MASK)
/*! @} */

/*! @name INT_MASK - Interrupt Mask Register */
/*! @{ */

#define EMVSIM_INT_MASK_RDT_IM_MASK              (0x1U)
#define EMVSIM_INT_MASK_RDT_IM_SHIFT             (0U)
/*! RDT_IM - Receive Data Threshold Interrupt Mask
 *  0b0..RDTF interrupt enabled
 *  0b1..RDTF interrupt masked
 */
#define EMVSIM_INT_MASK_RDT_IM(x)                (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_RDT_IM_SHIFT)) & EMVSIM_INT_MASK_RDT_IM_MASK)

#define EMVSIM_INT_MASK_TC_IM_MASK               (0x2U)
#define EMVSIM_INT_MASK_TC_IM_SHIFT              (1U)
/*! TC_IM - Transmit Complete Interrupt Mask
 *  0b0..TCF interrupt enabled
 *  0b1..TCF interrupt masked
 */
#define EMVSIM_INT_MASK_TC_IM(x)                 (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_TC_IM_SHIFT)) & EMVSIM_INT_MASK_TC_IM_MASK)

#define EMVSIM_INT_MASK_RFO_IM_MASK              (0x4U)
#define EMVSIM_INT_MASK_RFO_IM_SHIFT             (2U)
/*! RFO_IM - Receive FIFO Overflow Interrupt Mask
 *  0b0..RFO interrupt enabled
 *  0b1..RFO interrupt masked
 */
#define EMVSIM_INT_MASK_RFO_IM(x)                (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_RFO_IM_SHIFT)) & EMVSIM_INT_MASK_RFO_IM_MASK)

#define EMVSIM_INT_MASK_ETC_IM_MASK              (0x8U)
#define EMVSIM_INT_MASK_ETC_IM_SHIFT             (3U)
/*! ETC_IM - Early Transmit Complete Interrupt Mask
 *  0b0..ETC interrupt enabled
 *  0b1..ETC interrupt masked
 */
#define EMVSIM_INT_MASK_ETC_IM(x)                (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_ETC_IM_SHIFT)) & EMVSIM_INT_MASK_ETC_IM_MASK)

#define EMVSIM_INT_MASK_TFE_IM_MASK              (0x10U)
#define EMVSIM_INT_MASK_TFE_IM_SHIFT             (4U)
/*! TFE_IM - Transmit FIFO Empty Interrupt Mask
 *  0b0..TFE interrupt enabled
 *  0b1..TFE interrupt masked
 */
#define EMVSIM_INT_MASK_TFE_IM(x)                (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_TFE_IM_SHIFT)) & EMVSIM_INT_MASK_TFE_IM_MASK)

#define EMVSIM_INT_MASK_TNACK_IM_MASK            (0x20U)
#define EMVSIM_INT_MASK_TNACK_IM_SHIFT           (5U)
/*! TNACK_IM - Transmit NACK Threshold Interrupt Mask
 *  0b0..TNTE interrupt enabled
 *  0b1..TNTE interrupt masked
 */
#define EMVSIM_INT_MASK_TNACK_IM(x)              (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_TNACK_IM_SHIFT)) & EMVSIM_INT_MASK_TNACK_IM_MASK)

#define EMVSIM_INT_MASK_TFF_IM_MASK              (0x40U)
#define EMVSIM_INT_MASK_TFF_IM_SHIFT             (6U)
/*! TFF_IM - Transmit FIFO Full Interrupt Mask
 *  0b0..TFF interrupt enabled
 *  0b1..TFF interrupt masked
 */
#define EMVSIM_INT_MASK_TFF_IM(x)                (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_TFF_IM_SHIFT)) & EMVSIM_INT_MASK_TFF_IM_MASK)

#define EMVSIM_INT_MASK_TDT_IM_MASK              (0x80U)
#define EMVSIM_INT_MASK_TDT_IM_SHIFT             (7U)
/*! TDT_IM - Transmit Data Threshold Interrupt Mask
 *  0b0..TDTF interrupt enabled
 *  0b1..TDTF interrupt masked
 */
#define EMVSIM_INT_MASK_TDT_IM(x)                (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_TDT_IM_SHIFT)) & EMVSIM_INT_MASK_TDT_IM_MASK)

#define EMVSIM_INT_MASK_GPCNT0_IM_MASK           (0x100U)
#define EMVSIM_INT_MASK_GPCNT0_IM_SHIFT          (8U)
/*! GPCNT0_IM - General Purpose Timer 0 Timeout Interrupt Mask
 *  0b0..GPCNT0_TO interrupt enabled
 *  0b1..GPCNT0_TO interrupt masked
 */
#define EMVSIM_INT_MASK_GPCNT0_IM(x)             (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_GPCNT0_IM_SHIFT)) & EMVSIM_INT_MASK_GPCNT0_IM_MASK)

#define EMVSIM_INT_MASK_CWT_ERR_IM_MASK          (0x200U)
#define EMVSIM_INT_MASK_CWT_ERR_IM_SHIFT         (9U)
/*! CWT_ERR_IM - Character Wait Time Error Interrupt Mask
 *  0b0..CWT_ERR interrupt enabled
 *  0b1..CWT_ERR interrupt masked
 */
#define EMVSIM_INT_MASK_CWT_ERR_IM(x)            (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_CWT_ERR_IM_SHIFT)) & EMVSIM_INT_MASK_CWT_ERR_IM_MASK)

#define EMVSIM_INT_MASK_RNACK_IM_MASK            (0x400U)
#define EMVSIM_INT_MASK_RNACK_IM_SHIFT           (10U)
/*! RNACK_IM - Receiver NACK Threshold Interrupt Mask
 *  0b0..RTE interrupt enabled
 *  0b1..RTE interrupt masked
 */
#define EMVSIM_INT_MASK_RNACK_IM(x)              (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_RNACK_IM_SHIFT)) & EMVSIM_INT_MASK_RNACK_IM_MASK)

#define EMVSIM_INT_MASK_BWT_ERR_IM_MASK          (0x800U)
#define EMVSIM_INT_MASK_BWT_ERR_IM_SHIFT         (11U)
/*! BWT_ERR_IM - Block Wait Time Error Interrupt Mask
 *  0b0..BWT_ERR interrupt enabled
 *  0b1..BWT_ERR interrupt masked
 */
#define EMVSIM_INT_MASK_BWT_ERR_IM(x)            (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_BWT_ERR_IM_SHIFT)) & EMVSIM_INT_MASK_BWT_ERR_IM_MASK)

#define EMVSIM_INT_MASK_BGT_ERR_IM_MASK          (0x1000U)
#define EMVSIM_INT_MASK_BGT_ERR_IM_SHIFT         (12U)
/*! BGT_ERR_IM - Block Guard Time Error Interrupt
 *  0b0..BGT_ERR interrupt enabled
 *  0b1..BGT_ERR interrupt masked
 */
#define EMVSIM_INT_MASK_BGT_ERR_IM(x)            (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_BGT_ERR_IM_SHIFT)) & EMVSIM_INT_MASK_BGT_ERR_IM_MASK)

#define EMVSIM_INT_MASK_GPCNT1_IM_MASK           (0x2000U)
#define EMVSIM_INT_MASK_GPCNT1_IM_SHIFT          (13U)
/*! GPCNT1_IM - General Purpose Counter 1 Timeout Interrupt Mask
 *  0b0..GPCNT1_TO interrupt enabled
 *  0b1..GPCNT1_TO interrupt masked
 */
#define EMVSIM_INT_MASK_GPCNT1_IM(x)             (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_GPCNT1_IM_SHIFT)) & EMVSIM_INT_MASK_GPCNT1_IM_MASK)

#define EMVSIM_INT_MASK_RX_DATA_IM_MASK          (0x4000U)
#define EMVSIM_INT_MASK_RX_DATA_IM_SHIFT         (14U)
/*! RX_DATA_IM - Receive Data Interrupt Mask
 *  0b0..RX_DATA interrupt enabled
 *  0b1..RX_DATA interrupt masked
 */
#define EMVSIM_INT_MASK_RX_DATA_IM(x)            (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_RX_DATA_IM_SHIFT)) & EMVSIM_INT_MASK_RX_DATA_IM_MASK)

#define EMVSIM_INT_MASK_PEF_IM_MASK              (0x8000U)
#define EMVSIM_INT_MASK_PEF_IM_SHIFT             (15U)
/*! PEF_IM - Parity Error Interrupt Mask
 *  0b0..PEF interrupt enabled
 *  0b1..PEF interrupt masked
 */
#define EMVSIM_INT_MASK_PEF_IM(x)                (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_PEF_IM_SHIFT)) & EMVSIM_INT_MASK_PEF_IM_MASK)
/*! @} */

/*! @name RX_THD - Receiver Threshold Register */
/*! @{ */

#define EMVSIM_RX_THD_RDT_MASK                   (0xFU)
#define EMVSIM_RX_THD_RDT_SHIFT                  (0U)
/*! RDT - Receiver Data Threshold Value */
#define EMVSIM_RX_THD_RDT(x)                     (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_THD_RDT_SHIFT)) & EMVSIM_RX_THD_RDT_MASK)

#define EMVSIM_RX_THD_RNCK_THD_MASK              (0xF00U)
#define EMVSIM_RX_THD_RNCK_THD_SHIFT             (8U)
/*! RNCK_THD - Receiver NACK Threshold Value */
#define EMVSIM_RX_THD_RNCK_THD(x)                (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_THD_RNCK_THD_SHIFT)) & EMVSIM_RX_THD_RNCK_THD_MASK)
/*! @} */

/*! @name TX_THD - Transmitter Threshold Register */
/*! @{ */

#define EMVSIM_TX_THD_TDT_MASK                   (0xFU)
#define EMVSIM_TX_THD_TDT_SHIFT                  (0U)
/*! TDT - Transmitter Data Threshold Value */
#define EMVSIM_TX_THD_TDT(x)                     (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_THD_TDT_SHIFT)) & EMVSIM_TX_THD_TDT_MASK)

#define EMVSIM_TX_THD_TNCK_THD_MASK              (0xF00U)
#define EMVSIM_TX_THD_TNCK_THD_SHIFT             (8U)
/*! TNCK_THD - Transmitter NACK Threshold Value */
#define EMVSIM_TX_THD_TNCK_THD(x)                (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_THD_TNCK_THD_SHIFT)) & EMVSIM_TX_THD_TNCK_THD_MASK)
/*! @} */

/*! @name RX_STATUS - Receive Status Register */
/*! @{ */

#define EMVSIM_RX_STATUS_RFO_MASK                (0x1U)
#define EMVSIM_RX_STATUS_RFO_SHIFT               (0U)
/*! RFO - Receive FIFO Overflow Flag
 *  0b0..No overrun error has occurred
 *  0b1..A byte was received when the received FIFO was already full
 */
#define EMVSIM_RX_STATUS_RFO(x)                  (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_RFO_SHIFT)) & EMVSIM_RX_STATUS_RFO_MASK)

#define EMVSIM_RX_STATUS_RX_DATA_MASK            (0x10U)
#define EMVSIM_RX_STATUS_RX_DATA_SHIFT           (4U)
/*! RX_DATA - Receive Data Interrupt Flag
 *  0b0..No new byte is received
 *  0b1..New byte is received ans stored in Receive FIFO
 */
#define EMVSIM_RX_STATUS_RX_DATA(x)              (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_RX_DATA_SHIFT)) & EMVSIM_RX_STATUS_RX_DATA_MASK)

#define EMVSIM_RX_STATUS_RDTF_MASK               (0x20U)
#define EMVSIM_RX_STATUS_RDTF_SHIFT              (5U)
/*! RDTF - Receive Data Threshold Interrupt Flag
 *  0b0..Number of unread bytes in receive FIFO less than the value set by RDT
 *  0b1..Number of unread bytes in receive FIFO greater or than equal to value set by RDT.
 */
#define EMVSIM_RX_STATUS_RDTF(x)                 (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_RDTF_SHIFT)) & EMVSIM_RX_STATUS_RDTF_MASK)

#define EMVSIM_RX_STATUS_LRC_OK_MASK             (0x40U)
#define EMVSIM_RX_STATUS_LRC_OK_SHIFT            (6U)
/*! LRC_OK - LRC Check OK Flag
 *  0b0..Current LRC value does not match remainder.
 *  0b1..Current calculated LRC value matches the expected result (i.e. zero).
 */
#define EMVSIM_RX_STATUS_LRC_OK(x)               (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_LRC_OK_SHIFT)) & EMVSIM_RX_STATUS_LRC_OK_MASK)

#define EMVSIM_RX_STATUS_CRC_OK_MASK             (0x80U)
#define EMVSIM_RX_STATUS_CRC_OK_SHIFT            (7U)
/*! CRC_OK - CRC Check OK Flag
 *  0b0..Current CRC value does not match remainder.
 *  0b1..Current calculated CRC value matches the expected result.
 */
#define EMVSIM_RX_STATUS_CRC_OK(x)               (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_CRC_OK_SHIFT)) & EMVSIM_RX_STATUS_CRC_OK_MASK)

#define EMVSIM_RX_STATUS_CWT_ERR_MASK            (0x100U)
#define EMVSIM_RX_STATUS_CWT_ERR_SHIFT           (8U)
/*! CWT_ERR - Character Wait Time Error Flag
 *  0b0..No CWT violation has occurred
 *  0b1..Time between two consecutive characters has exceeded the value in CWT_VAL.
 */
#define EMVSIM_RX_STATUS_CWT_ERR(x)              (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_CWT_ERR_SHIFT)) & EMVSIM_RX_STATUS_CWT_ERR_MASK)

#define EMVSIM_RX_STATUS_RTE_MASK                (0x200U)
#define EMVSIM_RX_STATUS_RTE_SHIFT               (9U)
/*! RTE - Received NACK Threshold Error Flag
 *  0b0..Number of NACKs generated by the receiver is less than the value programmed in RNCK_THD
 *  0b1..Number of NACKs generated by the receiver is equal to the value programmed in RNCK_THD
 */
#define EMVSIM_RX_STATUS_RTE(x)                  (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_RTE_SHIFT)) & EMVSIM_RX_STATUS_RTE_MASK)

#define EMVSIM_RX_STATUS_BWT_ERR_MASK            (0x400U)
#define EMVSIM_RX_STATUS_BWT_ERR_SHIFT           (10U)
/*! BWT_ERR - Block Wait Time Error Flag
 *  0b0..Block wait time not exceeded
 *  0b1..Block wait time was exceeded
 */
#define EMVSIM_RX_STATUS_BWT_ERR(x)              (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_BWT_ERR_SHIFT)) & EMVSIM_RX_STATUS_BWT_ERR_MASK)

#define EMVSIM_RX_STATUS_BGT_ERR_MASK            (0x800U)
#define EMVSIM_RX_STATUS_BGT_ERR_SHIFT           (11U)
/*! BGT_ERR - Block Guard Time Error Flag
 *  0b0..Block guard time was sufficient
 *  0b1..Block guard time was too small
 */
#define EMVSIM_RX_STATUS_BGT_ERR(x)              (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_BGT_ERR_SHIFT)) & EMVSIM_RX_STATUS_BGT_ERR_MASK)

#define EMVSIM_RX_STATUS_PEF_MASK                (0x1000U)
#define EMVSIM_RX_STATUS_PEF_SHIFT               (12U)
/*! PEF - Parity Error Flag
 *  0b0..No parity error detected
 *  0b1..Parity error detected
 */
#define EMVSIM_RX_STATUS_PEF(x)                  (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_PEF_SHIFT)) & EMVSIM_RX_STATUS_PEF_MASK)

#define EMVSIM_RX_STATUS_FEF_MASK                (0x2000U)
#define EMVSIM_RX_STATUS_FEF_SHIFT               (13U)
/*! FEF - Frame Error Flag
 *  0b0..No frame error detected
 *  0b1..Frame error detected
 */
#define EMVSIM_RX_STATUS_FEF(x)                  (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_FEF_SHIFT)) & EMVSIM_RX_STATUS_FEF_MASK)

#define EMVSIM_RX_STATUS_RX_WPTR_MASK            (0xF0000U)
#define EMVSIM_RX_STATUS_RX_WPTR_SHIFT           (16U)
/*! RX_WPTR - Receive FIFO Write Pointer Value */
#define EMVSIM_RX_STATUS_RX_WPTR(x)              (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_RX_WPTR_SHIFT)) & EMVSIM_RX_STATUS_RX_WPTR_MASK)

#define EMVSIM_RX_STATUS_RX_CNT_MASK             (0xF000000U)
#define EMVSIM_RX_STATUS_RX_CNT_SHIFT            (24U)
/*! RX_CNT - Receive FIFO Byte Count
 *  0b0000..FIFO is emtpy
 */
#define EMVSIM_RX_STATUS_RX_CNT(x)               (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_RX_CNT_SHIFT)) & EMVSIM_RX_STATUS_RX_CNT_MASK)
/*! @} */

/*! @name TX_STATUS - Transmitter Status Register */
/*! @{ */

#define EMVSIM_TX_STATUS_TNTE_MASK               (0x1U)
#define EMVSIM_TX_STATUS_TNTE_SHIFT              (0U)
/*! TNTE - Transmit NACK Threshold Error Flag
 *  0b0..Transmit NACK threshold has not been reached
 *  0b1..Transmit NACK threshold reached; transmitter frozen
 */
#define EMVSIM_TX_STATUS_TNTE(x)                 (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TNTE_SHIFT)) & EMVSIM_TX_STATUS_TNTE_MASK)

#define EMVSIM_TX_STATUS_TFE_MASK                (0x8U)
#define EMVSIM_TX_STATUS_TFE_SHIFT               (3U)
/*! TFE - Transmit FIFO Empty Flag
 *  0b0..Transmit FIFO is not empty
 *  0b1..Transmit FIFO is empty
 */
#define EMVSIM_TX_STATUS_TFE(x)                  (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TFE_SHIFT)) & EMVSIM_TX_STATUS_TFE_MASK)

#define EMVSIM_TX_STATUS_ETCF_MASK               (0x10U)
#define EMVSIM_TX_STATUS_ETCF_SHIFT              (4U)
/*! ETCF - Early Transmit Complete Flag
 *  0b0..Transmit pending or in progress
 *  0b1..Transmit complete
 */
#define EMVSIM_TX_STATUS_ETCF(x)                 (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_ETCF_SHIFT)) & EMVSIM_TX_STATUS_ETCF_MASK)

#define EMVSIM_TX_STATUS_TCF_MASK                (0x20U)
#define EMVSIM_TX_STATUS_TCF_SHIFT               (5U)
/*! TCF - Transmit Complete Flag
 *  0b0..Transmit pending or in progress
 *  0b1..Transmit complete
 */
#define EMVSIM_TX_STATUS_TCF(x)                  (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TCF_SHIFT)) & EMVSIM_TX_STATUS_TCF_MASK)

#define EMVSIM_TX_STATUS_TFF_MASK                (0x40U)
#define EMVSIM_TX_STATUS_TFF_SHIFT               (6U)
/*! TFF - Transmit FIFO Full Flag
 *  0b0..Transmit FIFO Full condition has not occurred
 *  0b1..A Transmit FIFO Full condition has occurred
 */
#define EMVSIM_TX_STATUS_TFF(x)                  (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TFF_SHIFT)) & EMVSIM_TX_STATUS_TFF_MASK)

#define EMVSIM_TX_STATUS_TDTF_MASK               (0x80U)
#define EMVSIM_TX_STATUS_TDTF_SHIFT              (7U)
/*! TDTF - Transmit Data Threshold Flag
 *  0b0..Number of bytes in FIFO is greater than TDT, or bit has been cleared
 *  0b1..Number of bytes in FIFO is less than or equal to TDT
 */
#define EMVSIM_TX_STATUS_TDTF(x)                 (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TDTF_SHIFT)) & EMVSIM_TX_STATUS_TDTF_MASK)

#define EMVSIM_TX_STATUS_GPCNT0_TO_MASK          (0x100U)
#define EMVSIM_TX_STATUS_GPCNT0_TO_SHIFT         (8U)
/*! GPCNT0_TO - General Purpose Counter 0 Timeout Flag
 *  0b0..GPCNT0 time not reached, or bit has been cleared.
 *  0b1..General Purpose counter has reached the GPCNT0 value
 */
#define EMVSIM_TX_STATUS_GPCNT0_TO(x)            (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_GPCNT0_TO_SHIFT)) & EMVSIM_TX_STATUS_GPCNT0_TO_MASK)

#define EMVSIM_TX_STATUS_GPCNT1_TO_MASK          (0x200U)
#define EMVSIM_TX_STATUS_GPCNT1_TO_SHIFT         (9U)
/*! GPCNT1_TO - General Purpose Counter 1 Timeout Flag
 *  0b0..GPCNT1 time not reached, or bit has been cleared.
 *  0b1..General Purpose counter has reached the GPCNT1 value
 */
#define EMVSIM_TX_STATUS_GPCNT1_TO(x)            (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_GPCNT1_TO_SHIFT)) & EMVSIM_TX_STATUS_GPCNT1_TO_MASK)

#define EMVSIM_TX_STATUS_TX_RPTR_MASK            (0xF0000U)
#define EMVSIM_TX_STATUS_TX_RPTR_SHIFT           (16U)
/*! TX_RPTR - Transmit FIFO Read Pointer */
#define EMVSIM_TX_STATUS_TX_RPTR(x)              (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TX_RPTR_SHIFT)) & EMVSIM_TX_STATUS_TX_RPTR_MASK)

#define EMVSIM_TX_STATUS_TX_CNT_MASK             (0xF000000U)
#define EMVSIM_TX_STATUS_TX_CNT_SHIFT            (24U)
/*! TX_CNT - Transmit FIFO Byte Count
 *  0b0000..FIFO is emtpy
 */
#define EMVSIM_TX_STATUS_TX_CNT(x)               (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TX_CNT_SHIFT)) & EMVSIM_TX_STATUS_TX_CNT_MASK)
/*! @} */

/*! @name PCSR - Port Control and Status Register */
/*! @{ */

#define EMVSIM_PCSR_SAPD_MASK                    (0x1U)
#define EMVSIM_PCSR_SAPD_SHIFT                   (0U)
/*! SAPD - Auto Power Down Enable
 *  0b0..Auto power down disabled
 *  0b1..Auto power down enabled
 */
#define EMVSIM_PCSR_SAPD(x)                      (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SAPD_SHIFT)) & EMVSIM_PCSR_SAPD_MASK)

#define EMVSIM_PCSR_SVCC_EN_MASK                 (0x2U)
#define EMVSIM_PCSR_SVCC_EN_SHIFT                (1U)
/*! SVCC_EN - Vcc Enable for Smart Card
 *  0b0..Smart Card Voltage disabled
 *  0b1..Smart Card Voltage enabled
 */
#define EMVSIM_PCSR_SVCC_EN(x)                   (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SVCC_EN_SHIFT)) & EMVSIM_PCSR_SVCC_EN_MASK)

#define EMVSIM_PCSR_VCCENP_MASK                  (0x4U)
#define EMVSIM_PCSR_VCCENP_SHIFT                 (2U)
/*! VCCENP - VCC Enable Polarity Control
 *  0b0..SVCC_EN is active high. Polarity of SVCC_EN is unchanged.
 *  0b1..SVCC_EN is active low. Polarity of SVCC_EN is inverted.
 */
#define EMVSIM_PCSR_VCCENP(x)                    (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_VCCENP_SHIFT)) & EMVSIM_PCSR_VCCENP_MASK)

#define EMVSIM_PCSR_SRST_MASK                    (0x8U)
#define EMVSIM_PCSR_SRST_SHIFT                   (3U)
/*! SRST - Reset to Smart Card
 *  0b0..Smart Card Reset is asserted
 *  0b1..Smart Card Reset is de-asserted
 */
#define EMVSIM_PCSR_SRST(x)                      (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SRST_SHIFT)) & EMVSIM_PCSR_SRST_MASK)

#define EMVSIM_PCSR_SCEN_MASK                    (0x10U)
#define EMVSIM_PCSR_SCEN_SHIFT                   (4U)
/*! SCEN - Clock Enable for Smart Card
 *  0b0..Smart Card Clock Disabled
 *  0b1..Smart Card Clock Enabled
 */
#define EMVSIM_PCSR_SCEN(x)                      (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SCEN_SHIFT)) & EMVSIM_PCSR_SCEN_MASK)

#define EMVSIM_PCSR_SCSP_MASK                    (0x20U)
#define EMVSIM_PCSR_SCSP_SHIFT                   (5U)
/*! SCSP - Smart Card Clock Stop Polarity
 *  0b0..Clock is logic 0 when stopped by SCEN
 *  0b1..Clock is logic 1 when stopped by SCEN
 */
#define EMVSIM_PCSR_SCSP(x)                      (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SCSP_SHIFT)) & EMVSIM_PCSR_SCSP_MASK)

#define EMVSIM_PCSR_SPD_MASK                     (0x80U)
#define EMVSIM_PCSR_SPD_SHIFT                    (7U)
/*! SPD - Auto Power Down Control
 *  0b0..No effect
 *  0b1..Start Auto Powerdown or Power Down is in progress
 */
#define EMVSIM_PCSR_SPD(x)                       (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SPD_SHIFT)) & EMVSIM_PCSR_SPD_MASK)

#define EMVSIM_PCSR_SPDIM_MASK                   (0x1000000U)
#define EMVSIM_PCSR_SPDIM_SHIFT                  (24U)
/*! SPDIM - Smart Card Presence Detect Interrupt Mask
 *  0b0..SIM presence detect interrupt is enabled
 *  0b1..SIM presence detect interrupt is masked
 */
#define EMVSIM_PCSR_SPDIM(x)                     (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SPDIM_SHIFT)) & EMVSIM_PCSR_SPDIM_MASK)

#define EMVSIM_PCSR_SPDIF_MASK                   (0x2000000U)
#define EMVSIM_PCSR_SPDIF_SHIFT                  (25U)
/*! SPDIF - Smart Card Presence Detect Interrupt Flag
 *  0b0..No insertion or removal of Smart Card detected on Port
 *  0b1..Insertion or removal of Smart Card detected on Port
 */
#define EMVSIM_PCSR_SPDIF(x)                     (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SPDIF_SHIFT)) & EMVSIM_PCSR_SPDIF_MASK)

#define EMVSIM_PCSR_SPDP_MASK                    (0x4000000U)
#define EMVSIM_PCSR_SPDP_SHIFT                   (26U)
/*! SPDP - Smart Card Presence Detect Pin Status
 *  0b0..SIM Presence Detect pin is logic low
 *  0b1..SIM Presence Detectpin is logic high
 */
#define EMVSIM_PCSR_SPDP(x)                      (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SPDP_SHIFT)) & EMVSIM_PCSR_SPDP_MASK)

#define EMVSIM_PCSR_SPDES_MASK                   (0x8000000U)
#define EMVSIM_PCSR_SPDES_SHIFT                  (27U)
/*! SPDES - SIM Presence Detect Edge Select
 *  0b0..Falling edge on the pin
 *  0b1..Rising edge on the pin
 */
#define EMVSIM_PCSR_SPDES(x)                     (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SPDES_SHIFT)) & EMVSIM_PCSR_SPDES_MASK)
/*! @} */

/*! @name RX_BUF - Receive Data Read Buffer */
/*! @{ */

#define EMVSIM_RX_BUF_RX_BYTE_MASK               (0xFFU)
#define EMVSIM_RX_BUF_RX_BYTE_SHIFT              (0U)
/*! RX_BYTE - Receive Data Byte Read */
#define EMVSIM_RX_BUF_RX_BYTE(x)                 (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_BUF_RX_BYTE_SHIFT)) & EMVSIM_RX_BUF_RX_BYTE_MASK)
/*! @} */

/*! @name TX_BUF - Transmit Data Buffer */
/*! @{ */

#define EMVSIM_TX_BUF_TX_BYTE_MASK               (0xFFU)
#define EMVSIM_TX_BUF_TX_BYTE_SHIFT              (0U)
/*! TX_BYTE - Transmit Data Byte */
#define EMVSIM_TX_BUF_TX_BYTE(x)                 (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_BUF_TX_BYTE_SHIFT)) & EMVSIM_TX_BUF_TX_BYTE_MASK)
/*! @} */

/*! @name TX_GETU - Transmitter Guard ETU Value Register */
/*! @{ */

#define EMVSIM_TX_GETU_GETU_MASK                 (0xFFU)
#define EMVSIM_TX_GETU_GETU_SHIFT                (0U)
/*! GETU - Transmitter Guard Time Value in ETU */
#define EMVSIM_TX_GETU_GETU(x)                   (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_GETU_GETU_SHIFT)) & EMVSIM_TX_GETU_GETU_MASK)
/*! @} */

/*! @name CWT_VAL - Character Wait Time Value Register */
/*! @{ */

#define EMVSIM_CWT_VAL_CWT_MASK                  (0xFFFFU)
#define EMVSIM_CWT_VAL_CWT_SHIFT                 (0U)
/*! CWT - Character Wait Time Value */
#define EMVSIM_CWT_VAL_CWT(x)                    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CWT_VAL_CWT_SHIFT)) & EMVSIM_CWT_VAL_CWT_MASK)
/*! @} */

/*! @name BWT_VAL - Block Wait Time Value Register */
/*! @{ */

#define EMVSIM_BWT_VAL_BWT_MASK                  (0xFFFFFFFFU)
#define EMVSIM_BWT_VAL_BWT_SHIFT                 (0U)
/*! BWT - Block Wait Time Value */
#define EMVSIM_BWT_VAL_BWT(x)                    (((uint32_t)(((uint32_t)(x)) << EMVSIM_BWT_VAL_BWT_SHIFT)) & EMVSIM_BWT_VAL_BWT_MASK)
/*! @} */

/*! @name BGT_VAL - Block Guard Time Value Register */
/*! @{ */

#define EMVSIM_BGT_VAL_BGT_MASK                  (0xFFFFU)
#define EMVSIM_BGT_VAL_BGT_SHIFT                 (0U)
/*! BGT - Block Guard Time Value */
#define EMVSIM_BGT_VAL_BGT(x)                    (((uint32_t)(((uint32_t)(x)) << EMVSIM_BGT_VAL_BGT_SHIFT)) & EMVSIM_BGT_VAL_BGT_MASK)
/*! @} */

/*! @name GPCNT0_VAL - General Purpose Counter 0 Timeout Value Register */
/*! @{ */

#define EMVSIM_GPCNT0_VAL_GPCNT0_MASK            (0xFFFFU)
#define EMVSIM_GPCNT0_VAL_GPCNT0_SHIFT           (0U)
/*! GPCNT0 - General Purpose Counter 0 Timeout Value */
#define EMVSIM_GPCNT0_VAL_GPCNT0(x)              (((uint32_t)(((uint32_t)(x)) << EMVSIM_GPCNT0_VAL_GPCNT0_SHIFT)) & EMVSIM_GPCNT0_VAL_GPCNT0_MASK)
/*! @} */

/*! @name GPCNT1_VAL - General Purpose Counter 1 Timeout Value */
/*! @{ */

#define EMVSIM_GPCNT1_VAL_GPCNT1_MASK            (0xFFFFU)
#define EMVSIM_GPCNT1_VAL_GPCNT1_SHIFT           (0U)
/*! GPCNT1 - General Purpose Counter 1 Timeout Value */
#define EMVSIM_GPCNT1_VAL_GPCNT1(x)              (((uint32_t)(((uint32_t)(x)) << EMVSIM_GPCNT1_VAL_GPCNT1_SHIFT)) & EMVSIM_GPCNT1_VAL_GPCNT1_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group EMVSIM_Register_Masks */


/*!
 * @}
 */ /* end of group EMVSIM_Peripheral_Access_Layer */


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


#endif  /* PERI_EMVSIM_H_ */

