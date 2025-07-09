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
**         CMSIS Peripheral Access Layer for DMAMUX
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
 * @file PERI_DMAMUX.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for DMAMUX
 *
 * CMSIS Peripheral Access Layer for DMAMUX
 */

#if !defined(PERI_DMAMUX_H_)
#define PERI_DMAMUX_H_                           /**< Symbol preventing repeated inclusion */

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
   -- Mapping Information
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Mapping_Information Mapping Information
 * @{
 */

/** Mapping Information */
#if !defined(DMA_REQUEST_SOURCE_T_)
#define DMA_REQUEST_SOURCE_T_
/*!
 * @addtogroup edma_request
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Structure for the DMA hardware request
 *
 * Defines the structure for the DMA hardware request collections. The user can configure the
 * hardware request into DMAMUX to trigger the DMA transfer accordingly. The index
 * of the hardware request varies according  to the to SoC.
 */
typedef enum _dma_request_source
{
    kDmaRequestMuxFlexIO1Request2Request3 = 1|0x100U, /**< FlexIO1 Request2 and Request3 */
    kDmaRequestMuxFlexIO1Request4Request5 = 2|0x100U, /**< FlexIO1 Request4 and Request5 */
    kDmaRequestMuxFlexIO1Request6Request7 = 3|0x100U, /**< FlexIO1 Request6 and Request7 */
    kDmaRequestMuxFlexIO2Request0Request1 = 4|0x100U, /**< FlexIO2 Request0 and Request1 */
    kDmaRequestMuxFlexIO2Request2Request3 = 5|0x100U, /**< FlexIO2 Request2 and Request3 */
    kDmaRequestMuxFlexIO2Request4Request5 = 6|0x100U, /**< FlexIO2 Request4 and Request5 */
    kDmaRequestMuxFlexIO2Request6Request7 = 7|0x100U, /**< FlexIO2 Request6 and Request7 */
    kDmaRequestMuxLPUART1Tx         = 8|0x100U,    /**< LPUART1 Transmit */
    kDmaRequestMuxLPUART1Rx         = 9|0x100U,    /**< LPUART1 Receive */
    kDmaRequestMuxLPUART2Tx         = 10|0x100U,   /**< LPUART2 Transmit */
    kDmaRequestMuxLPUART2Rx         = 11|0x100U,   /**< LPUART2 Receive */
    kDmaRequestMuxLPUART3Tx         = 12|0x100U,   /**< LPUART3 Transmit */
    kDmaRequestMuxLPUART3Rx         = 13|0x100U,   /**< LPUART3 Receive */
    kDmaRequestMuxLPUART4Tx         = 14|0x100U,   /**< LPUART4 Transmit */
    kDmaRequestMuxLPUART4Rx         = 15|0x100U,   /**< LPUART4 Receive */
    kDmaRequestMuxLPUART5Tx         = 16|0x100U,   /**< LPUART5 Transmit */
    kDmaRequestMuxLPUART5Rx         = 17|0x100U,   /**< LPUART5 Receive */
    kDmaRequestMuxLPUART6Tx         = 18|0x100U,   /**< LPUART6 Transmit */
    kDmaRequestMuxLPUART6Rx         = 19|0x100U,   /**< LPUART6 Receive */
    kDmaRequestMuxLPUART7Tx         = 20|0x100U,   /**< LPUART7 Transmit */
    kDmaRequestMuxLPUART7Rx         = 21|0x100U,   /**< LPUART7 Receive */
    kDmaRequestMuxLPUART8Tx         = 22|0x100U,   /**< LPUART8 Transmit */
    kDmaRequestMuxLPUART8Rx         = 23|0x100U,   /**< LPUART8 Receive */
    kDmaRequestMuxLPUART9Tx         = 24|0x100U,   /**< LPUART9 Transmit */
    kDmaRequestMuxLPUART9Rx         = 25|0x100U,   /**< LPUART9 Receive */
    kDmaRequestMuxLPUART10Tx        = 26|0x100U,   /**< LPUART10 Transmit */
    kDmaRequestMuxLPUART10Rx        = 27|0x100U,   /**< LPUART10 Receive */
    kDmaRequestMuxLPUART11Tx        = 28|0x100U,   /**< LPUART11 Transmit */
    kDmaRequestMuxLPUART11Rx        = 29|0x100U,   /**< LPUART11 Receive */
    kDmaRequestMuxLPUART12Tx        = 30|0x100U,   /**< LPUART12 Transmit */
    kDmaRequestMuxLPUART12Rx        = 31|0x100U,   /**< LPUART12 Receive */
    kDmaRequestMuxLCDIFv2           = 35|0x100U,   /**< LCDIFv2 */
    kDmaRequestMuxLPSPI1Rx          = 36|0x100U,   /**< LPSPI1 Receive */
    kDmaRequestMuxLPSPI1Tx          = 37|0x100U,   /**< LPSPI1 Transmit */
    kDmaRequestMuxLPSPI2Rx          = 38|0x100U,   /**< LPSPI2 Receive */
    kDmaRequestMuxLPSPI2Tx          = 39|0x100U,   /**< LPSPI2 Transmit */
    kDmaRequestMuxLPSPI3Rx          = 40|0x100U,   /**< LPSPI3 Receive */
    kDmaRequestMuxLPSPI3Tx          = 41|0x100U,   /**< LPSPI3 Transmit */
    kDmaRequestMuxLPSPI4Rx          = 42|0x100U,   /**< LPSPI4 Receive */
    kDmaRequestMuxLPSPI4Tx          = 43|0x100U,   /**< LPSPI4 Transmit */
    kDmaRequestMuxLPSPI5Rx          = 44|0x100U,   /**< LPSPI5 Receive */
    kDmaRequestMuxLPSPI5Tx          = 45|0x100U,   /**< LPSPI5 Transmit */
    kDmaRequestMuxLPSPI6Rx          = 46|0x100U,   /**< LPSPI6 Receive */
    kDmaRequestMuxLPSPI6Tx          = 47|0x100U,   /**< LPSPI6 Transmit */
    kDmaRequestMuxLPI2C1            = 48|0x100U,   /**< LPI2C1 */
    kDmaRequestMuxLPI2C2            = 49|0x100U,   /**< LPI2C2 */
    kDmaRequestMuxLPI2C3            = 50|0x100U,   /**< LPI2C3 */
    kDmaRequestMuxLPI2C4            = 51|0x100U,   /**< LPI2C4 */
    kDmaRequestMuxLPI2C5            = 52|0x100U,   /**< LPI2C5 */
    kDmaRequestMuxLPI2C6            = 53|0x100U,   /**< LPI2C6 */
    kDmaRequestMuxSai1Rx            = 54|0x100U,   /**< SAI1 Receive */
    kDmaRequestMuxSai1Tx            = 55|0x100U,   /**< SAI1 Transmit */
    kDmaRequestMuxSai2Rx            = 56|0x100U,   /**< SAI2 Receive */
    kDmaRequestMuxSai2Tx            = 57|0x100U,   /**< SAI2 Transmit */
    kDmaRequestMuxSai3Rx            = 58|0x100U,   /**< SAI3 Receive */
    kDmaRequestMuxSai3Tx            = 59|0x100U,   /**< SAI3 Transmit */
    kDmaRequestMuxSai4Rx            = 60|0x100U,   /**< SAI4 Receive */
    kDmaRequestMuxSai4Tx            = 61|0x100U,   /**< SAI4 Transmit */
    kDmaRequestMuxSpdifRx           = 62|0x100U,   /**< SPDIF Receive */
    kDmaRequestMuxSpdifTx           = 63|0x100U,   /**< SPDIF Transmit */
    kDmaRequestMuxADC_ETC           = 64|0x100U,   /**< ADC_ETC */
    kDmaRequestMuxFlexIO1Request0Request1 = 65|0x100U, /**< FlexIO1 Request0 and Request1 */
    kDmaRequestMuxADC1              = 66|0x100U,   /**< ADC1 */
    kDmaRequestMuxADC2              = 67|0x100U,   /**< ADC2 */
    kDmaRequestMuxACMP1             = 69|0x100U,   /**< ACMP1 */
    kDmaRequestMuxACMP2             = 70|0x100U,   /**< ACMP2 */
    kDmaRequestMuxACMP3             = 71|0x100U,   /**< ACMP3 */
    kDmaRequestMuxACMP4             = 72|0x100U,   /**< ACMP4 */
    kDmaRequestMuxFlexSPI1Rx        = 77|0x100U,   /**< FlexSPI1 Receive */
    kDmaRequestMuxFlexSPI1Tx        = 78|0x100U,   /**< FlexSPI1 Transmit */
    kDmaRequestMuxFlexSPI2Rx        = 79|0x100U,   /**< FlexSPI2 Receive */
    kDmaRequestMuxFlexSPI2Tx        = 80|0x100U,   /**< FlexSPI2 Transmit */
    kDmaRequestMuxXBAR1Request0     = 81|0x100U,   /**< XBAR1 Request 0 */
    kDmaRequestMuxXBAR1Request1     = 82|0x100U,   /**< XBAR1 Request 1 */
    kDmaRequestMuxXBAR1Request2     = 83|0x100U,   /**< XBAR1 Request 2 */
    kDmaRequestMuxXBAR1Request3     = 84|0x100U,   /**< XBAR1 Request 3 */
    kDmaRequestMuxFlexPWM1CaptureSub0 = 85|0x100U, /**< FlexPWM1 Capture sub-module0 */
    kDmaRequestMuxFlexPWM1CaptureSub1 = 86|0x100U, /**< FlexPWM1 Capture sub-module1 */
    kDmaRequestMuxFlexPWM1CaptureSub2 = 87|0x100U, /**< FlexPWM1 Capture sub-module2 */
    kDmaRequestMuxFlexPWM1CaptureSub3 = 88|0x100U, /**< FlexPWM1 Capture sub-module3 */
    kDmaRequestMuxFlexPWM1ValueSub0 = 89|0x100U,   /**< FlexPWM1 Value sub-module 0 */
    kDmaRequestMuxFlexPWM1ValueSub1 = 90|0x100U,   /**< FlexPWM1 Value sub-module 1 */
    kDmaRequestMuxFlexPWM1ValueSub2 = 91|0x100U,   /**< FlexPWM1 Value sub-module 2 */
    kDmaRequestMuxFlexPWM1ValueSub3 = 92|0x100U,   /**< FlexPWM1 Value sub-module 3 */
    kDmaRequestMuxFlexPWM2CaptureSub0 = 93|0x100U, /**< FlexPWM2 Capture sub-module0 */
    kDmaRequestMuxFlexPWM2CaptureSub1 = 94|0x100U, /**< FlexPWM2 Capture sub-module1 */
    kDmaRequestMuxFlexPWM2CaptureSub2 = 95|0x100U, /**< FlexPWM2 Capture sub-module2 */
    kDmaRequestMuxFlexPWM2CaptureSub3 = 96|0x100U, /**< FlexPWM2 Capture sub-module3 */
    kDmaRequestMuxFlexPWM2ValueSub0 = 97|0x100U,   /**< FlexPWM2 Value sub-module 0 */
    kDmaRequestMuxFlexPWM2ValueSub1 = 98|0x100U,   /**< FlexPWM2 Value sub-module 1 */
    kDmaRequestMuxFlexPWM2ValueSub2 = 99|0x100U,   /**< FlexPWM2 Value sub-module 2 */
    kDmaRequestMuxFlexPWM2ValueSub3 = 100|0x100U,  /**< FlexPWM2 Value sub-module 3 */
    kDmaRequestMuxFlexPWM3CaptureSub0 = 101|0x100U, /**< FlexPWM3 Capture sub-module0 */
    kDmaRequestMuxFlexPWM3CaptureSub1 = 102|0x100U, /**< FlexPWM3 Capture sub-module1 */
    kDmaRequestMuxFlexPWM3CaptureSub2 = 103|0x100U, /**< FlexPWM3 Capture sub-module2 */
    kDmaRequestMuxFlexPWM3CaptureSub3 = 104|0x100U, /**< FlexPWM3 Capture sub-module3 */
    kDmaRequestMuxFlexPWM3ValueSub0 = 105|0x100U,  /**< FlexPWM3 Value sub-module 0 */
    kDmaRequestMuxFlexPWM3ValueSub1 = 106|0x100U,  /**< FlexPWM3 Value sub-module 1 */
    kDmaRequestMuxFlexPWM3ValueSub2 = 107|0x100U,  /**< FlexPWM3 Value sub-module 2 */
    kDmaRequestMuxFlexPWM3ValueSub3 = 108|0x100U,  /**< FlexPWM3 Value sub-module 3 */
    kDmaRequestMuxFlexPWM4CaptureSub0 = 109|0x100U, /**< FlexPWM4 Capture sub-module0 */
    kDmaRequestMuxFlexPWM4CaptureSub1 = 110|0x100U, /**< FlexPWM4 Capture sub-module1 */
    kDmaRequestMuxFlexPWM4CaptureSub2 = 111|0x100U, /**< FlexPWM4 Capture sub-module2 */
    kDmaRequestMuxFlexPWM4CaptureSub3 = 112|0x100U, /**< FlexPWM4 Capture sub-module3 */
    kDmaRequestMuxFlexPWM4ValueSub0 = 113|0x100U,  /**< FlexPWM4 Value sub-module 0 */
    kDmaRequestMuxFlexPWM4ValueSub1 = 114|0x100U,  /**< FlexPWM4 Value sub-module 1 */
    kDmaRequestMuxFlexPWM4ValueSub2 = 115|0x100U,  /**< FlexPWM4 Value sub-module 2 */
    kDmaRequestMuxFlexPWM4ValueSub3 = 116|0x100U,  /**< FlexPWM4 Value sub-module 3 */
    kDmaRequestMuxQTIMER1CaptTimer0 = 133|0x100U,  /**< TMR1 Capture timer 0 */
    kDmaRequestMuxQTIMER1CaptTimer1 = 134|0x100U,  /**< TMR1 Capture timer 1 */
    kDmaRequestMuxQTIMER1CaptTimer2 = 135|0x100U,  /**< TMR1 Capture timer 2 */
    kDmaRequestMuxQTIMER1CaptTimer3 = 136|0x100U,  /**< TMR1 Capture timer 3 */
    kDmaRequestMuxQTIMER1Cmpld1Timer0Cmpld2Timer1 = 137|0x100U, /**< TMR1 cmpld1 in timer 0 or cmpld2 in timer 1 */
    kDmaRequestMuxQTIMER1Cmpld1Timer1Cmpld2Timer0 = 138|0x100U, /**< TMR1 cmpld1 in timer 1 or cmpld2 in timer 0 */
    kDmaRequestMuxQTIMER1Cmpld1Timer2Cmpld2Timer3 = 139|0x100U, /**< TMR1 cmpld1 in timer 2 or cmpld2 in timer 3 */
    kDmaRequestMuxQTIMER1Cmpld1Timer3Cmpld2Timer2 = 140|0x100U, /**< TMR1 cmpld1 in timer 3 or cmpld2 in timer 2 */
    kDmaRequestMuxQTIMER2CaptTimer0 = 141|0x100U,  /**< TMR2 Capture timer 0 */
    kDmaRequestMuxQTIMER2CaptTimer1 = 142|0x100U,  /**< TMR2 Capture timer 1 */
    kDmaRequestMuxQTIMER2CaptTimer2 = 143|0x100U,  /**< TMR2 Capture timer 2 */
    kDmaRequestMuxQTIMER2CaptTimer3 = 144|0x100U,  /**< TMR2 Capture timer 3 */
    kDmaRequestMuxQTIMER2Cmpld1Timer0Cmpld2Timer1 = 145|0x100U, /**< TMR2 cmpld1 in timer 0 or cmpld2 in timer 1 */
    kDmaRequestMuxQTIMER2Cmpld1Timer1Cmpld2Timer0 = 146|0x100U, /**< TMR2 cmpld1 in timer 1 or cmpld2 in timer 0 */
    kDmaRequestMuxQTIMER2Cmpld1Timer2Cmpld2Timer3 = 147|0x100U, /**< TMR2 cmpld1 in timer 2 or cmpld2 in timer 3 */
    kDmaRequestMuxQTIMER2Cmpld1Timer3Cmpld2Timer2 = 148|0x100U, /**< TMR2 cmpld1 in timer 3 or cmpld2 in timer 2 */
    kDmaRequestMuxQTIMER3CaptTimer0 = 149|0x100U,  /**< TMR3 Capture timer 0 */
    kDmaRequestMuxQTIMER3CaptTimer1 = 150|0x100U,  /**< TMR3 Capture timer 1 */
    kDmaRequestMuxQTIMER3CaptTimer2 = 151|0x100U,  /**< TMR3 Capture timer 2 */
    kDmaRequestMuxQTIMER3CaptTimer3 = 152|0x100U,  /**< TMR3 Capture timer 3 */
    kDmaRequestMuxQTIMER3Cmpld1Timer0Cmpld2Timer1 = 153|0x100U, /**< TMR3 cmpld1 in timer 0 or cmpld2 in timer 1 */
    kDmaRequestMuxQTIMER3Cmpld1Timer1Cmpld2Timer0 = 154|0x100U, /**< TMR3 cmpld1 in timer 1 or cmpld2 in timer 0 */
    kDmaRequestMuxQTIMER3Cmpld1Timer2Cmpld2Timer3 = 155|0x100U, /**< TMR3 cmpld1 in timer 2 or cmpld2 in timer 3 */
    kDmaRequestMuxQTIMER3Cmpld1Timer3Cmpld2Timer2 = 156|0x100U, /**< TMR3 cmpld1 in timer 3 or cmpld2 in timer 2 */
    kDmaRequestMuxQTIMER4CaptTimer0 = 157|0x100U,  /**< TMR4 Capture timer 0 */
    kDmaRequestMuxQTIMER4CaptTimer1 = 158|0x100U,  /**< TMR4 Capture timer 1 */
    kDmaRequestMuxQTIMER4CaptTimer2 = 159|0x100U,  /**< TMR4 Capture timer 2 */
    kDmaRequestMuxQTIMER4CaptTimer3 = 160|0x100U,  /**< TMR4 Capture timer 3 */
    kDmaRequestMuxQTIMER4Cmpld1Timer0Cmpld2Timer1 = 161|0x100U, /**< TMR4 cmpld1 in timer 0 or cmpld2 in timer 1 */
    kDmaRequestMuxQTIMER4Cmpld1Timer1Cmpld2Timer0 = 162|0x100U, /**< TMR4 cmpld1 in timer 1 or cmpld2 in timer 0 */
    kDmaRequestMuxQTIMER4Cmpld1Timer2Cmpld2Timer3 = 163|0x100U, /**< TMR4 cmpld1 in timer 2 or cmpld2 in timer 3 */
    kDmaRequestMuxQTIMER4Cmpld1Timer3Cmpld2Timer2 = 164|0x100U, /**< TMR4 cmpld1 in timer 3 or cmpld2 in timer 2 */
    kDmaRequestMuxPdm               = 181|0x100U,  /**< PDM */
    kDmaRequestMuxEnetTimer0        = 182|0x100U,  /**< ENET Timer0 */
    kDmaRequestMuxEnetTimer1        = 183|0x100U,  /**< ENET Timer1 */
    kDmaRequestMuxEnet1GTimer0      = 184|0x100U,  /**< ENET 1G Timer0 */
    kDmaRequestMuxEnet1GTimer1      = 185|0x100U,  /**< ENET 1G Timer1 */
    kDmaRequestMuxCAN1              = 186|0x100U,  /**< CAN1 */
    kDmaRequestMuxCAN2              = 187|0x100U,  /**< CAN2 */
    kDmaRequestMuxCAN3              = 188|0x100U,  /**< CAN3 */
    kDmaRequestMuxDAC               = 189|0x100U,  /**< DAC */
    kDmaRequestMuxASRCRequest1      = 191|0x100U,  /**< ASRC request 1 pair A input request */
    kDmaRequestMuxASRCRequest2      = 192|0x100U,  /**< ASRC request 2 pair B input request */
    kDmaRequestMuxASRCRequest3      = 193|0x100U,  /**< ASRC request 3 pair C input request */
    kDmaRequestMuxASRCRequest4      = 194|0x100U,  /**< ASRC request 4 pair A output request */
    kDmaRequestMuxASRCRequest5      = 195|0x100U,  /**< ASRC request 5 pair B output request */
    kDmaRequestMuxASRCRequest6      = 196|0x100U,  /**< ASRC request 6 pair C output request */
    kDmaRequestMuxEmvsim1Tx         = 197|0x100U,  /**< Emvsim1 Transmit */
    kDmaRequestMuxEmvsim1Rx         = 198|0x100U,  /**< Emvsim1 Receive */
    kDmaRequestMuxEmvsim2Tx         = 199|0x100U,  /**< Emvsim2 Transmit */
    kDmaRequestMuxEmvsim2Rx         = 200|0x100U,  /**< Emvsim2 Receive */
    kDmaRequestMuxCSI               = 32|0x100U,   /**< CSI */
    kDmaRequestMuxPxp               = 33|0x100U,   /**< PXP */
    kDmaRequestMuxeLCDIF            = 34|0x100U,   /**< eLCDIF */
    kDmaRequestMuxEnetQosTimer0     = 201|0x100U,  /**< ENET_QOS Timer0 */
    kDmaRequestMuxEnetQosTimer1     = 202|0x100U,  /**< ENET_QOS Timer1 */
} dma_request_source_t;

/* @} */
#endif /* DMA_REQUEST_SOURCE_T_ */


/*!
 * @}
 */ /* end of group Mapping_Information */


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
   -- DMAMUX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Peripheral_Access_Layer DMAMUX Peripheral Access Layer
 * @{
 */

/** DMAMUX - Size of Registers Arrays */
#define DMAMUX_CHCFG_REG_ARRAY_COUNT              32u

/** DMAMUX - Register Layout Typedef */
typedef struct {
  __IO uint32_t CHCFG[DMAMUX_CHCFG_REG_ARRAY_COUNT]; /**< Channel 0 Configuration Register..Channel 31 Configuration Register, array offset: 0x0, array step: 0x4 */
} DMAMUX_Type;

/* ----------------------------------------------------------------------------
   -- DMAMUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Register_Masks DMAMUX Register Masks
 * @{
 */

/*! @name CHCFG - Channel 0 Configuration Register..Channel 31 Configuration Register */
/*! @{ */

#define DMAMUX_CHCFG_SOURCE_MASK                 (0xFFU)
#define DMAMUX_CHCFG_SOURCE_SHIFT                (0U)
/*! SOURCE - DMA Channel Source (Slot Number) */
#define DMAMUX_CHCFG_SOURCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMAMUX_CHCFG_SOURCE_SHIFT)) & DMAMUX_CHCFG_SOURCE_MASK)

#define DMAMUX_CHCFG_A_ON_MASK                   (0x20000000U)
#define DMAMUX_CHCFG_A_ON_SHIFT                  (29U)
/*! A_ON - DMA Channel Always Enable
 *  0b0..DMA Channel Always ON function is disabled
 *  0b1..DMA Channel Always ON function is enabled
 */
#define DMAMUX_CHCFG_A_ON(x)                     (((uint32_t)(((uint32_t)(x)) << DMAMUX_CHCFG_A_ON_SHIFT)) & DMAMUX_CHCFG_A_ON_MASK)

#define DMAMUX_CHCFG_TRIG_MASK                   (0x40000000U)
#define DMAMUX_CHCFG_TRIG_SHIFT                  (30U)
/*! TRIG - DMA Channel Trigger Enable
 *  0b0..Triggering is disabled. If triggering is disabled and ENBL is set, the DMA Channel will simply route the
 *       specified source to the DMA channel. (Normal mode)
 *  0b1..Triggering is enabled. If triggering is enabled and ENBL is set, the DMA_CH_MUX is in Periodic Trigger mode.
 */
#define DMAMUX_CHCFG_TRIG(x)                     (((uint32_t)(((uint32_t)(x)) << DMAMUX_CHCFG_TRIG_SHIFT)) & DMAMUX_CHCFG_TRIG_MASK)

#define DMAMUX_CHCFG_ENBL_MASK                   (0x80000000U)
#define DMAMUX_CHCFG_ENBL_SHIFT                  (31U)
/*! ENBL - DMA Mux Channel Enable
 *  0b0..DMA Mux channel is disabled
 *  0b1..DMA Mux channel is enabled
 */
#define DMAMUX_CHCFG_ENBL(x)                     (((uint32_t)(((uint32_t)(x)) << DMAMUX_CHCFG_ENBL_SHIFT)) & DMAMUX_CHCFG_ENBL_MASK)
/*! @} */

/* The count of DMAMUX_CHCFG */
#define DMAMUX_CHCFG_COUNT                       (32U)


/*!
 * @}
 */ /* end of group DMAMUX_Register_Masks */


/*!
 * @}
 */ /* end of group DMAMUX_Peripheral_Access_Layer */


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


#endif  /* PERI_DMAMUX_H_ */

