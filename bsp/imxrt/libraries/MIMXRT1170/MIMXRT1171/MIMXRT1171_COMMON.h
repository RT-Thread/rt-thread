/*
** ###################################################################
**     Processors:          MIMXRT1171AVM8A
**                          MIMXRT1171AVM8B
**                          MIMXRT1171CVM8A
**                          MIMXRT1171CVM8B
**                          MIMXRT1171DVMAA
**                          MIMXRT1171DVMAB
**
**     Compilers:           Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    IMXRT1170RM, Rev 1, 02/2021
**     Version:             rev. 2.0, 2024-10-29
**     Build:               b250520
**
**     Abstract:
**         CMSIS Peripheral Access Layer for MIMXRT1171
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
 * @file MIMXRT1171_COMMON.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for MIMXRT1171
 *
 * CMSIS Peripheral Access Layer for MIMXRT1171
 */

#if !defined(MIMXRT1171_COMMON_H_)
#define MIMXRT1171_COMMON_H_                     /**< Symbol preventing repeated inclusion */

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0200U
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0000U


/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS 234                /**< Number of interrupts in the Vector table */

typedef enum IRQn {
  /* Auxiliary constants */
  NotAvail_IRQn                = -128,             /**< Not available device specific interrupt */

  /* Core interrupts */
  NonMaskableInt_IRQn          = -14,              /**< Non Maskable Interrupt */
  HardFault_IRQn               = -13,              /**< Cortex-M7 SV Hard Fault Interrupt */
  MemoryManagement_IRQn        = -12,              /**< Cortex-M7 Memory Management Interrupt */
  BusFault_IRQn                = -11,              /**< Cortex-M7 Bus Fault Interrupt */
  UsageFault_IRQn              = -10,              /**< Cortex-M7 Usage Fault Interrupt */
  SVCall_IRQn                  = -5,               /**< Cortex-M7 SV Call Interrupt */
  DebugMonitor_IRQn            = -4,               /**< Cortex-M7 Debug Monitor Interrupt */
  PendSV_IRQn                  = -2,               /**< Cortex-M7 Pend SV Interrupt */
  SysTick_IRQn                 = -1,               /**< Cortex-M7 System Tick Interrupt */

  /* Device specific interrupts */
  DMA0_DMA16_IRQn              = 0,                /**< DMA channel 0/16 transfer complete */
  DMA1_DMA17_IRQn              = 1,                /**< DMA channel 1/17 transfer complete */
  DMA2_DMA18_IRQn              = 2,                /**< DMA channel 2/18 transfer complete */
  DMA3_DMA19_IRQn              = 3,                /**< DMA channel 3/19 transfer complete */
  DMA4_DMA20_IRQn              = 4,                /**< DMA channel 4/20 transfer complete */
  DMA5_DMA21_IRQn              = 5,                /**< DMA channel 5/21 transfer complete */
  DMA6_DMA22_IRQn              = 6,                /**< DMA channel 6/22 transfer complete */
  DMA7_DMA23_IRQn              = 7,                /**< DMA channel 7/23 transfer complete */
  DMA8_DMA24_IRQn              = 8,                /**< DMA channel 8/24 transfer complete */
  DMA9_DMA25_IRQn              = 9,                /**< DMA channel 9/25 transfer complete */
  DMA10_DMA26_IRQn             = 10,               /**< DMA channel 10/26 transfer complete */
  DMA11_DMA27_IRQn             = 11,               /**< DMA channel 11/27 transfer complete */
  DMA12_DMA28_IRQn             = 12,               /**< DMA channel 12/28 transfer complete */
  DMA13_DMA29_IRQn             = 13,               /**< DMA channel 13/29 transfer complete */
  DMA14_DMA30_IRQn             = 14,               /**< DMA channel 14/30 transfer complete */
  DMA15_DMA31_IRQn             = 15,               /**< DMA channel 15/31 transfer complete */
  DMA_ERROR_IRQn               = 16,               /**< DMA error interrupt channels 0-15 / 16-31 */
  CTI_TRIGGER_OUT0_IRQn        = 17,               /**< CTI_TRIGGER_OUT0 */
  CTI_TRIGGER_OUT1_IRQn        = 18,               /**< CTI_TRIGGER_OUT1 */
  CORE_IRQn                    = 19,               /**< CorePlatform exception IRQ */
  LPUART1_IRQn                 = 20,               /**< LPUART1 TX interrupt and RX interrupt */
  LPUART2_IRQn                 = 21,               /**< LPUART2 TX interrupt and RX interrupt */
  LPUART3_IRQn                 = 22,               /**< LPUART3 TX interrupt and RX interrupt */
  LPUART4_IRQn                 = 23,               /**< LPUART4 TX interrupt and RX interrupt */
  LPUART5_IRQn                 = 24,               /**< LPUART5 TX interrupt and RX interrupt */
  LPUART6_IRQn                 = 25,               /**< LPUART6 TX interrupt and RX interrupt */
  LPUART7_IRQn                 = 26,               /**< LPUART7 TX interrupt and RX interrupt */
  LPUART8_IRQn                 = 27,               /**< LPUART8 TX interrupt and RX interrupt */
  LPUART9_IRQn                 = 28,               /**< LPUART9 TX interrupt and RX interrupt */
  LPUART10_IRQn                = 29,               /**< LPUART10 TX interrupt and RX interrupt */
  LPUART11_IRQn                = 30,               /**< LPUART11 TX interrupt and RX interrupt */
  LPUART12_IRQn                = 31,               /**< LPUART12 TX interrupt and RX interrupt */
  LPI2C1_IRQn                  = 32,               /**< LPI2C1 interrupt */
  LPI2C2_IRQn                  = 33,               /**< LPI2C2 interrupt */
  LPI2C3_IRQn                  = 34,               /**< LPI2C3 interrupt */
  LPI2C4_IRQn                  = 35,               /**< LPI2C4 interrupt */
  LPI2C5_IRQn                  = 36,               /**< LPI2C5 interrupt */
  LPI2C6_IRQn                  = 37,               /**< LPI2C6 interrupt */
  LPSPI1_IRQn                  = 38,               /**< LPSPI1 interrupt request line to the core */
  LPSPI2_IRQn                  = 39,               /**< LPSPI2 interrupt request line to the core */
  LPSPI3_IRQn                  = 40,               /**< LPSPI3 interrupt request line to the core */
  LPSPI4_IRQn                  = 41,               /**< LPSPI4 interrupt request line to the core */
  LPSPI5_IRQn                  = 42,               /**< LPSPI5 interrupt request line to the core */
  LPSPI6_IRQn                  = 43,               /**< LPSPI6 interrupt request line to the core */
  CAN1_IRQn                    = 44,               /**< CAN1 interrupt */
  CAN1_ERROR_IRQn              = 45,               /**< CAN1 error interrupt */
  CAN2_IRQn                    = 46,               /**< CAN2 interrupt */
  CAN2_ERROR_IRQn              = 47,               /**< CAN2 error interrupt */
  CAN3_IRQn                    = 48,               /**< CAN3 interrupt */
  CAN3_ERROR_IRQn              = 49,               /**< CAN3 error interrupt */
  FLEXRAM_IRQn                 = 50,               /**< FlexRAM address out of range Or access hit IRQ */
  KPP_IRQn                     = 51,               /**< Keypad interrupt */
  Reserved68_IRQn              = 52,               /**< Reserved interrupt */
  GPR_IRQ_IRQn                 = 53,               /**< GPR interrupt */
  Reserved70_IRQn              = 54,               /**< Reserved interrupt */
  LCDIFv2_IRQn                 = 55,               /**< LCDIFv2 interrupt */
  Reserved72_IRQn              = 56,               /**< Reserved interrupt */
  Reserved73_IRQn              = 57,               /**< Reserved interrupt */
  MIPI_CSI_IRQn                = 58,               /**< MIPI_CSI interrupt */
  MIPI_DSI_IRQn                = 59,               /**< MIPI_DSI interrupt */
  GPU2D_IRQn                   = 60,               /**< GPU2D interrupt */
  GPIO6_Combined_0_15_IRQn     = 61,               /**< Combined interrupt indication for GPIO6 signal 0 throughout 15 */
  GPIO6_Combined_16_31_IRQn    = 62,               /**< Combined interrupt indication for GPIO6 signal 16 throughout 31 */
  DAC_IRQn                     = 63,               /**< DAC interrupt */
  KEY_MANAGER_IRQn             = 64,               /**< PUF interrupt */
  WDOG2_IRQn                   = 65,               /**< WDOG2 interrupt */
  SNVS_HP_NON_TZ_IRQn          = 66,               /**< SRTC Consolidated Interrupt. Non TZ */
  SNVS_HP_TZ_IRQn              = 67,               /**< SRTC Security Interrupt. TZ */
  SNVS_PULSE_EVENT_IRQn        = 68,               /**< ON-OFF button press shorter than 5 secs (pulse event) */
  CAAM_IRQ0_IRQn               = 69,               /**< CAAM interrupt queue for JQ0 */
  CAAM_IRQ1_IRQn               = 70,               /**< CAAM interrupt queue for JQ1 */
  CAAM_IRQ2_IRQn               = 71,               /**< CAAM interrupt queue for JQ2 */
  CAAM_IRQ3_IRQn               = 72,               /**< CAAM interrupt queue for JQ3 */
  CAAM_RECORVE_ERRPR_IRQn      = 73,               /**< CAAM interrupt for recoverable error */
  CAAM_RTIC_IRQn               = 74,               /**< CAAM interrupt for RTIC */
  CDOG_IRQn                    = 75,               /**< CDOG interrupt */
  SAI1_IRQn                    = 76,               /**< SAI1 interrupt */
  SAI2_IRQn                    = 77,               /**< SAI1 interrupt */
  SAI3_RX_IRQn                 = 78,               /**< SAI3 interrupt */
  SAI3_TX_IRQn                 = 79,               /**< SAI3 interrupt */
  SAI4_RX_IRQn                 = 80,               /**< SAI4 interrupt */
  SAI4_TX_IRQn                 = 81,               /**< SAI4 interrupt */
  SPDIF_IRQn                   = 82,               /**< SPDIF interrupt */
  TMPSNS_INT_IRQn              = 83,               /**< TMPSNS interrupt */
  TMPSNS_LOW_HIGH_IRQn         = 84,               /**< TMPSNS low high interrupt */
  TMPSNS_PANIC_IRQn            = 85,               /**< TMPSNS panic interrupt */
  LPSR_LP8_BROWNOUT_IRQn       = 86,               /**< LPSR 1p8 brownout interrupt */
  LPSR_LP0_BROWNOUT_IRQn       = 87,               /**< LPSR 1p0 brownout interrupt */
  ADC1_IRQn                    = 88,               /**< ADC1 interrupt */
  ADC2_IRQn                    = 89,               /**< ADC2 interrupt */
  USBPHY1_IRQn                 = 90,               /**< USBPHY1 interrupt */
  USBPHY2_IRQn                 = 91,               /**< USBPHY2 interrupt */
  RDC_IRQn                     = 92,               /**< RDC interrupt */
  GPIO13_Combined_0_31_IRQn    = 93,               /**< Combined interrupt indication for GPIO13 signal 0 throughout 31 */
  Reserved110_IRQn             = 94,               /**< Reserved interrupt */
  DCIC1_IRQn                   = 95,               /**< DCIC1 interrupt */
  DCIC2_IRQn                   = 96,               /**< DCIC2 interrupt */
  ASRC_IRQn                    = 97,               /**< ASRC interrupt */
  FLEXRAM_ECC_IRQn             = 98,               /**< FlexRAM ECC fatal interrupt */
  CM7_GPIO2_3_IRQn             = 99,               /**< CM7_GPIO2,CM7_GPIO3 interrupt */
  GPIO1_Combined_0_15_IRQn     = 100,              /**< Combined interrupt indication for GPIO1 signal 0 throughout 15 */
  GPIO1_Combined_16_31_IRQn    = 101,              /**< Combined interrupt indication for GPIO1 signal 16 throughout 31 */
  GPIO2_Combined_0_15_IRQn     = 102,              /**< Combined interrupt indication for GPIO2 signal 0 throughout 15 */
  GPIO2_Combined_16_31_IRQn    = 103,              /**< Combined interrupt indication for GPIO2 signal 16 throughout 31 */
  GPIO3_Combined_0_15_IRQn     = 104,              /**< Combined interrupt indication for GPIO3 signal 0 throughout 15 */
  GPIO3_Combined_16_31_IRQn    = 105,              /**< Combined interrupt indication for GPIO3 signal 16 throughout 31 */
  GPIO4_Combined_0_15_IRQn     = 106,              /**< Combined interrupt indication for GPIO4 signal 0 throughout 15 */
  GPIO4_Combined_16_31_IRQn    = 107,              /**< Combined interrupt indication for GPIO4 signal 16 throughout 31 */
  GPIO5_Combined_0_15_IRQn     = 108,              /**< Combined interrupt indication for GPIO5 signal 0 throughout 15 */
  GPIO5_Combined_16_31_IRQn    = 109,              /**< Combined interrupt indication for GPIO5 signal 16 throughout 31 */
  FLEXIO1_IRQn                 = 110,              /**< FLEXIO1 interrupt */
  FLEXIO2_IRQn                 = 111,              /**< FLEXIO2 interrupt */
  WDOG1_IRQn                   = 112,              /**< WDOG1 interrupt */
  RTWDOG3_IRQn                 = 113,              /**< RTWDOG3 interrupt */
  EWM_IRQn                     = 114,              /**< EWM interrupt */
  OCOTP_READ_FUSE_ERROR_IRQn   = 115,              /**< OCOTP read fuse error interrupt */
  OCOTP_READ_DONE_ERROR_IRQn   = 116,              /**< OCOTP read fuse done interrupt */
  GPC_IRQn                     = 117,              /**< GPC interrupt */
  MUA_IRQn                     = 118,              /**< MUA interrupt */
  GPT1_IRQn                    = 119,              /**< GPT1 interrupt */
  GPT2_IRQn                    = 120,              /**< GPT2 interrupt */
  GPT3_IRQn                    = 121,              /**< GPT3 interrupt */
  GPT4_IRQn                    = 122,              /**< GPT4 interrupt */
  GPT5_IRQn                    = 123,              /**< GPT5 interrupt */
  GPT6_IRQn                    = 124,              /**< GPT6 interrupt */
  PWM1_0_IRQn                  = 125,              /**< PWM1 capture 0, compare 0, or reload 0 interrupt */
  PWM1_1_IRQn                  = 126,              /**< PWM1 capture 1, compare 1, or reload 0 interrupt */
  PWM1_2_IRQn                  = 127,              /**< PWM1 capture 2, compare 2, or reload 0 interrupt */
  PWM1_3_IRQn                  = 128,              /**< PWM1 capture 3, compare 3, or reload 0 interrupt */
  PWM1_FAULT_IRQn              = 129,              /**< PWM1 fault or reload error interrupt */
  FLEXSPI1_IRQn                = 130,              /**< FlexSPI1 interrupt */
  FLEXSPI2_IRQn                = 131,              /**< FlexSPI2 interrupt */
  SEMC_IRQn                    = 132,              /**< SEMC interrupt */
  USDHC1_IRQn                  = 133,              /**< USDHC1 interrupt */
  USDHC2_IRQn                  = 134,              /**< USDHC2 interrupt */
  USB_OTG2_IRQn                = 135,              /**< USBO2 USB OTG2 */
  USB_OTG1_IRQn                = 136,              /**< USBO2 USB OTG1 */
  ENET_IRQn                    = 137,              /**< ENET interrupt */
  ENET_1588_Timer_IRQn         = 138,              /**< ENET_1588_Timer interrupt */
  ENET_1G_MAC0_Tx_Rx_1_IRQn    = 139,              /**< ENET 1G MAC0 transmit/receive 1 */
  ENET_1G_MAC0_Tx_Rx_2_IRQn    = 140,              /**< ENET 1G MAC0 transmit/receive 2 */
  ENET_1G_IRQn                 = 141,              /**< ENET 1G interrupt */
  ENET_1G_1588_Timer_IRQn      = 142,              /**< ENET_1G_1588_Timer interrupt */
  XBAR1_IRQ_0_1_IRQn           = 143,              /**< XBARA1 output signal 0, 1 interrupt */
  XBAR1_IRQ_2_3_IRQn           = 144,              /**< XBARA1 output signal 2, 3 interrupt */
  ADC_ETC_IRQ0_IRQn            = 145,              /**< ADCETC IRQ0 interrupt */
  ADC_ETC_IRQ1_IRQn            = 146,              /**< ADCETC IRQ1 interrupt */
  ADC_ETC_IRQ2_IRQn            = 147,              /**< ADCETC IRQ2 interrupt */
  ADC_ETC_IRQ3_IRQn            = 148,              /**< ADCETC IRQ3 interrupt */
  ADC_ETC_ERROR_IRQ_IRQn       = 149,              /**< ADCETC Error IRQ interrupt */
  Reserved166_IRQn             = 150,              /**< Reserved interrupt */
  Reserved167_IRQn             = 151,              /**< Reserved interrupt */
  Reserved168_IRQn             = 152,              /**< Reserved interrupt */
  Reserved169_IRQn             = 153,              /**< Reserved interrupt */
  Reserved170_IRQn             = 154,              /**< Reserved interrupt */
  PIT1_IRQn                    = 155,              /**< PIT1 interrupt */
  PIT2_IRQn                    = 156,              /**< PIT2 interrupt */
  ACMP1_IRQn                   = 157,              /**< ACMP interrupt */
  ACMP2_IRQn                   = 158,              /**< ACMP interrupt */
  ACMP3_IRQn                   = 159,              /**< ACMP interrupt */
  ACMP4_IRQn                   = 160,              /**< ACMP interrupt */
  Reserved177_IRQn             = 161,              /**< Reserved interrupt */
  Reserved178_IRQn             = 162,              /**< Reserved interrupt */
  Reserved179_IRQn             = 163,              /**< Reserved interrupt */
  Reserved180_IRQn             = 164,              /**< Reserved interrupt */
  ENC1_IRQn                    = 165,              /**< ENC1 interrupt */
  ENC2_IRQn                    = 166,              /**< ENC2 interrupt */
  ENC3_IRQn                    = 167,              /**< ENC3 interrupt */
  ENC4_IRQn                    = 168,              /**< ENC4 interrupt */
  Reserved185_IRQn             = 169,              /**< Reserved interrupt */
  Reserved186_IRQn             = 170,              /**< Reserved interrupt */
  TMR1_IRQn                    = 171,              /**< TMR1 interrupt */
  TMR2_IRQn                    = 172,              /**< TMR2 interrupt */
  TMR3_IRQn                    = 173,              /**< TMR3 interrupt */
  TMR4_IRQn                    = 174,              /**< TMR4 interrupt */
  SEMA4_CP0_IRQn               = 175,              /**< SEMA4 CP0 interrupt */
  SEMA4_CP1_IRQn               = 176,              /**< SEMA4 CP1 interrupt */
  PWM2_0_IRQn                  = 177,              /**< PWM2 capture 0, compare 0, or reload 0 interrupt */
  PWM2_1_IRQn                  = 178,              /**< PWM2 capture 1, compare 1, or reload 0 interrupt */
  PWM2_2_IRQn                  = 179,              /**< PWM2 capture 2, compare 2, or reload 0 interrupt */
  PWM2_3_IRQn                  = 180,              /**< PWM2 capture 3, compare 3, or reload 0 interrupt */
  PWM2_FAULT_IRQn              = 181,              /**< PWM2 fault or reload error interrupt */
  PWM3_0_IRQn                  = 182,              /**< PWM3 capture 0, compare 0, or reload 0 interrupt */
  PWM3_1_IRQn                  = 183,              /**< PWM3 capture 1, compare 1, or reload 0 interrupt */
  PWM3_2_IRQn                  = 184,              /**< PWM3 capture 2, compare 2, or reload 0 interrupt */
  PWM3_3_IRQn                  = 185,              /**< PWM3 capture 3, compare 3, or reload 0 interrupt */
  PWM3_FAULT_IRQn              = 186,              /**< PWM3 fault or reload error interrupt */
  PWM4_0_IRQn                  = 187,              /**< PWM4 capture 0, compare 0, or reload 0 interrupt */
  PWM4_1_IRQn                  = 188,              /**< PWM4 capture 1, compare 1, or reload 0 interrupt */
  PWM4_2_IRQn                  = 189,              /**< PWM4 capture 2, compare 2, or reload 0 interrupt */
  PWM4_3_IRQn                  = 190,              /**< PWM4 capture 3, compare 3, or reload 0 interrupt */
  PWM4_FAULT_IRQn              = 191,              /**< PWM4 fault or reload error interrupt */
  Reserved208_IRQn             = 192,              /**< Reserved interrupt */
  Reserved209_IRQn             = 193,              /**< Reserved interrupt */
  Reserved210_IRQn             = 194,              /**< Reserved interrupt */
  Reserved211_IRQn             = 195,              /**< Reserved interrupt */
  Reserved212_IRQn             = 196,              /**< Reserved interrupt */
  Reserved213_IRQn             = 197,              /**< Reserved interrupt */
  Reserved214_IRQn             = 198,              /**< Reserved interrupt */
  Reserved215_IRQn             = 199,              /**< Reserved interrupt */
  PDM_HWVAD_EVENT_IRQn         = 200,              /**< HWVAD event interrupt */
  PDM_HWVAD_ERROR_IRQn         = 201,              /**< HWVAD error interrupt */
  PDM_EVENT_IRQn               = 202,              /**< PDM event interrupt */
  PDM_ERROR_IRQn               = 203,              /**< PDM error interrupt */
  EMVSIM1_IRQn                 = 204,              /**< EMVSIM1 interrupt */
  EMVSIM2_IRQn                 = 205,              /**< EMVSIM2 interrupt */
  MECC1_INT_IRQn               = 206,              /**< MECC1 int */
  MECC1_FATAL_INT_IRQn         = 207,              /**< MECC1 fatal int */
  MECC2_INT_IRQn               = 208,              /**< MECC2 int */
  MECC2_FATAL_INT_IRQn         = 209,              /**< MECC2 fatal int */
  XECC_FLEXSPI1_INT_IRQn       = 210,              /**< XECC int */
  XECC_FLEXSPI1_FATAL_INT_IRQn = 211,              /**< XECC fatal int */
  XECC_FLEXSPI2_INT_IRQn       = 212,              /**< XECC int */
  XECC_FLEXSPI2_FATAL_INT_IRQn = 213,              /**< XECC fatal int */
  XECC_SEMC_INT_IRQn           = 214,              /**< XECC int */
  XECC_SEMC_FATAL_INT_IRQn     = 215,              /**< XECC fatal int */
  Reserved232_IRQn             = 216,              /**< Reserved interrupt */
  Reserved233_IRQn             = 217               /**< Reserved interrupt */
} IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Cortex M7 Core Configuration
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Cortex_Core_Configuration Cortex M7 Core Configuration
 * @{
 */

#define __MPU_PRESENT                  1         /**< Defines if an MPU is present or not */
#define __ICACHE_PRESENT               1         /**< Defines if an ICACHE is present or not */
#define __DCACHE_PRESENT               1         /**< Defines if an DCACHE is present or not */
#define __DTCM_PRESENT                 1         /**< Defines if an DTCM is present or not */
#define __NVIC_PRIO_BITS               4         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig         0         /**< Vendor specific implementation of SysTickConfig is defined */
#define __FPU_PRESENT                  1         /**< Defines if an FPU is present or not */

#include "core_cm7.h"                  /* Core Peripheral Access Layer */
#include "system_MIMXRT1171.h"         /* Device specific configuration file */

/*!
 * @}
 */ /* end of group Cortex_Core_Configuration */


#ifndef MIMXRT1171_SERIES
#define MIMXRT1171_SERIES
#endif
/* CPU specific feature definitions */
#include "MIMXRT1171_features.h"

/* ADC - Peripheral instance base addresses */
/** Peripheral LPADC1 base address */
#define LPADC1_BASE                              (0x40050000u)
/** Peripheral LPADC1 base pointer */
#define LPADC1                                   ((ADC_Type *)LPADC1_BASE)
/** Peripheral LPADC2 base address */
#define LPADC2_BASE                              (0x40054000u)
/** Peripheral LPADC2 base pointer */
#define LPADC2                                   ((ADC_Type *)LPADC2_BASE)
/** Array initializer of ADC peripheral base addresses */
#define ADC_BASE_ADDRS                           { 0u, LPADC1_BASE, LPADC2_BASE }
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            { (ADC_Type *)0u, LPADC1, LPADC2 }
/** Interrupt vectors for the ADC peripheral type */
#define ADC_IRQS                                 { NotAvail_IRQn, ADC1_IRQn, ADC2_IRQn }

/* ADC_ETC - Peripheral instance base addresses */
/** Peripheral ADC_ETC base address */
#define ADC_ETC_BASE                             (0x40048000u)
/** Peripheral ADC_ETC base pointer */
#define ADC_ETC                                  ((ADC_ETC_Type *)ADC_ETC_BASE)
/** Array initializer of ADC_ETC peripheral base addresses */
#define ADC_ETC_BASE_ADDRS                       { ADC_ETC_BASE }
/** Array initializer of ADC_ETC peripheral base pointers */
#define ADC_ETC_BASE_PTRS                        { ADC_ETC }
/** Interrupt vectors for the ADC_ETC peripheral type */
#define ADC_ETC_IRQS                             { { ADC_ETC_IRQ0_IRQn, ADC_ETC_IRQ1_IRQn, ADC_ETC_IRQ2_IRQn, ADC_ETC_IRQ3_IRQn } }
#define ADC_ETC_FAULT_IRQS                       { ADC_ETC_ERROR_IRQ_IRQn }

/* ANADIG_LDO_SNVS - Peripheral instance base addresses */
/** Peripheral ANADIG_LDO_SNVS base address */
#define ANADIG_LDO_SNVS_BASE                     (0x40C84000u)
/** Peripheral ANADIG_LDO_SNVS base pointer */
#define ANADIG_LDO_SNVS                          ((ANADIG_LDO_SNVS_Type *)ANADIG_LDO_SNVS_BASE)
/** Array initializer of ANADIG_LDO_SNVS peripheral base addresses */
#define ANADIG_LDO_SNVS_BASE_ADDRS               { ANADIG_LDO_SNVS_BASE }
/** Array initializer of ANADIG_LDO_SNVS peripheral base pointers */
#define ANADIG_LDO_SNVS_BASE_PTRS                { ANADIG_LDO_SNVS }

/* ANADIG_LDO_SNVS_DIG - Peripheral instance base addresses */
/** Peripheral ANADIG_LDO_SNVS_DIG base address */
#define ANADIG_LDO_SNVS_DIG_BASE                 (0x40C84000u)
/** Peripheral ANADIG_LDO_SNVS_DIG base pointer */
#define ANADIG_LDO_SNVS_DIG                      ((ANADIG_LDO_SNVS_DIG_Type *)ANADIG_LDO_SNVS_DIG_BASE)
/** Array initializer of ANADIG_LDO_SNVS_DIG peripheral base addresses */
#define ANADIG_LDO_SNVS_DIG_BASE_ADDRS           { ANADIG_LDO_SNVS_DIG_BASE }
/** Array initializer of ANADIG_LDO_SNVS_DIG peripheral base pointers */
#define ANADIG_LDO_SNVS_DIG_BASE_PTRS            { ANADIG_LDO_SNVS_DIG }

/* ANADIG_MISC - Peripheral instance base addresses */
/** Peripheral ANADIG_MISC base address */
#define ANADIG_MISC_BASE                         (0x40C84000u)
/** Peripheral ANADIG_MISC base pointer */
#define ANADIG_MISC                              ((ANADIG_MISC_Type *)ANADIG_MISC_BASE)
/** Array initializer of ANADIG_MISC peripheral base addresses */
#define ANADIG_MISC_BASE_ADDRS                   { ANADIG_MISC_BASE }
/** Array initializer of ANADIG_MISC peripheral base pointers */
#define ANADIG_MISC_BASE_PTRS                    { ANADIG_MISC }

/* ANADIG_OSC - Peripheral instance base addresses */
/** Peripheral ANADIG_OSC base address */
#define ANADIG_OSC_BASE                          (0x40C84000u)
/** Peripheral ANADIG_OSC base pointer */
#define ANADIG_OSC                               ((ANADIG_OSC_Type *)ANADIG_OSC_BASE)
/** Array initializer of ANADIG_OSC peripheral base addresses */
#define ANADIG_OSC_BASE_ADDRS                    { ANADIG_OSC_BASE }
/** Array initializer of ANADIG_OSC peripheral base pointers */
#define ANADIG_OSC_BASE_PTRS                     { ANADIG_OSC }

/* ANADIG_PLL - Peripheral instance base addresses */
/** Peripheral ANADIG_PLL base address */
#define ANADIG_PLL_BASE                          (0x40C84000u)
/** Peripheral ANADIG_PLL base pointer */
#define ANADIG_PLL                               ((ANADIG_PLL_Type *)ANADIG_PLL_BASE)
/** Array initializer of ANADIG_PLL peripheral base addresses */
#define ANADIG_PLL_BASE_ADDRS                    { ANADIG_PLL_BASE }
/** Array initializer of ANADIG_PLL peripheral base pointers */
#define ANADIG_PLL_BASE_PTRS                     { ANADIG_PLL }

/* ANADIG_PMU - Peripheral instance base addresses */
/** Peripheral ANADIG_PMU base address */
#define ANADIG_PMU_BASE                          (0x40C84000u)
/** Peripheral ANADIG_PMU base pointer */
#define ANADIG_PMU                               ((ANADIG_PMU_Type *)ANADIG_PMU_BASE)
/** Array initializer of ANADIG_PMU peripheral base addresses */
#define ANADIG_PMU_BASE_ADDRS                    { ANADIG_PMU_BASE }
/** Array initializer of ANADIG_PMU peripheral base pointers */
#define ANADIG_PMU_BASE_PTRS                     { ANADIG_PMU }

/* ANADIG_TEMPSENSOR - Peripheral instance base addresses */
/** Peripheral ANADIG_TEMPSENSOR base address */
#define ANADIG_TEMPSENSOR_BASE                   (0x40C84000u)
/** Peripheral ANADIG_TEMPSENSOR base pointer */
#define ANADIG_TEMPSENSOR                        ((ANADIG_TEMPSENSOR_Type *)ANADIG_TEMPSENSOR_BASE)
/** Array initializer of ANADIG_TEMPSENSOR peripheral base addresses */
#define ANADIG_TEMPSENSOR_BASE_ADDRS             { ANADIG_TEMPSENSOR_BASE }
/** Array initializer of ANADIG_TEMPSENSOR peripheral base pointers */
#define ANADIG_TEMPSENSOR_BASE_PTRS              { ANADIG_TEMPSENSOR }

/* AOI - Peripheral instance base addresses */
/** Peripheral AOI1 base address */
#define AOI1_BASE                                (0x400B8000u)
/** Peripheral AOI1 base pointer */
#define AOI1                                     ((AOI_Type *)AOI1_BASE)
/** Peripheral AOI2 base address */
#define AOI2_BASE                                (0x400BC000u)
/** Peripheral AOI2 base pointer */
#define AOI2                                     ((AOI_Type *)AOI2_BASE)
/** Array initializer of AOI peripheral base addresses */
#define AOI_BASE_ADDRS                           { 0u, AOI1_BASE, AOI2_BASE }
/** Array initializer of AOI peripheral base pointers */
#define AOI_BASE_PTRS                            { (AOI_Type *)0u, AOI1, AOI2 }

/* ASRC - Peripheral instance base addresses */
/** Peripheral ASRC base address */
#define ASRC_BASE                                (0x40414000u)
/** Peripheral ASRC base pointer */
#define ASRC                                     ((ASRC_Type *)ASRC_BASE)
/** Array initializer of ASRC peripheral base addresses */
#define ASRC_BASE_ADDRS                          { ASRC_BASE }
/** Array initializer of ASRC peripheral base pointers */
#define ASRC_BASE_PTRS                           { ASRC }
/** Interrupt vectors for the ASRC peripheral type */
#define ASRC_IRQS                                { ASRC_IRQn }

/* AUDIO_PLL - Peripheral instance base addresses */
/** Peripheral AUDIO_PLL base address */
#define AUDIO_PLL_BASE                           (0u)
/** Peripheral AUDIO_PLL base pointer */
#define AUDIO_PLL                                ((AUDIO_PLL_Type *)AUDIO_PLL_BASE)
/** Array initializer of AUDIO_PLL peripheral base addresses */
#define AUDIO_PLL_BASE_ADDRS                     { AUDIO_PLL_BASE }
/** Array initializer of AUDIO_PLL peripheral base pointers */
#define AUDIO_PLL_BASE_PTRS                      { AUDIO_PLL }

/* CAAM - Peripheral instance base addresses */
/** Peripheral CAAM base address */
#define CAAM_BASE                                (0x40440000u)
/** Peripheral CAAM base pointer */
#define CAAM                                     ((CAAM_Type *)CAAM_BASE)
/** Array initializer of CAAM peripheral base addresses */
#define CAAM_BASE_ADDRS                          { CAAM_BASE }
/** Array initializer of CAAM peripheral base pointers */
#define CAAM_BASE_PTRS                           { CAAM }

/* CAN - Peripheral instance base addresses */
/** Peripheral CAN1 base address */
#define CAN1_BASE                                (0x400C4000u)
/** Peripheral CAN1 base pointer */
#define CAN1                                     ((CAN_Type *)CAN1_BASE)
/** Peripheral CAN2 base address */
#define CAN2_BASE                                (0x400C8000u)
/** Peripheral CAN2 base pointer */
#define CAN2                                     ((CAN_Type *)CAN2_BASE)
/** Peripheral CAN3 base address */
#define CAN3_BASE                                (0x40C3C000u)
/** Peripheral CAN3 base pointer */
#define CAN3                                     ((CAN_Type *)CAN3_BASE)
/** Array initializer of CAN peripheral base addresses */
#define CAN_BASE_ADDRS                           { 0u, CAN1_BASE, CAN2_BASE, CAN3_BASE }
/** Array initializer of CAN peripheral base pointers */
#define CAN_BASE_PTRS                            { (CAN_Type *)0u, CAN1, CAN2, CAN3 }
/** Interrupt vectors for the CAN peripheral type */
#define CAN_Rx_Warning_IRQS                      { NotAvail_IRQn, CAN1_IRQn, CAN2_IRQn, CAN3_IRQn }
#define CAN_Tx_Warning_IRQS                      { NotAvail_IRQn, CAN1_IRQn, CAN2_IRQn, CAN3_IRQn }
#define CAN_Wake_Up_IRQS                         { NotAvail_IRQn, CAN1_IRQn, CAN2_IRQn, CAN3_IRQn }
#define CAN_Error_IRQS                           { NotAvail_IRQn, CAN1_IRQn, CAN2_IRQn, CAN3_IRQn }
#define CAN_Bus_Off_IRQS                         { NotAvail_IRQn, CAN1_IRQn, CAN2_IRQn, CAN3_IRQn }
#define CAN_ORed_Message_buffer_IRQS             { NotAvail_IRQn, CAN1_IRQn, CAN2_IRQn, CAN3_IRQn }

/* CAN_WRAPPER - Peripheral instance base addresses */
/** Peripheral CAN1_WRAPPER base address */
#define CAN1_WRAPPER_BASE                        (0x400C4000u)
/** Peripheral CAN1_WRAPPER base pointer */
#define CAN1_WRAPPER                             ((CAN_WRAPPER_Type *)CAN1_WRAPPER_BASE)
/** Peripheral CAN2_WRAPPER base address */
#define CAN2_WRAPPER_BASE                        (0x400C8000u)
/** Peripheral CAN2_WRAPPER base pointer */
#define CAN2_WRAPPER                             ((CAN_WRAPPER_Type *)CAN2_WRAPPER_BASE)
/** Peripheral CAN3_WRAPPER base address */
#define CAN3_WRAPPER_BASE                        (0x40C3C000u)
/** Peripheral CAN3_WRAPPER base pointer */
#define CAN3_WRAPPER                             ((CAN_WRAPPER_Type *)CAN3_WRAPPER_BASE)
/** Array initializer of CAN_WRAPPER peripheral base addresses */
#define CAN_WRAPPER_BASE_ADDRS                   { 0u, CAN1_WRAPPER_BASE, CAN2_WRAPPER_BASE, CAN3_WRAPPER_BASE }
/** Array initializer of CAN_WRAPPER peripheral base pointers */
#define CAN_WRAPPER_BASE_PTRS                    { (CAN_WRAPPER_Type *)0u, CAN1_WRAPPER, CAN2_WRAPPER, CAN3_WRAPPER }

/* CCM - Peripheral instance base addresses */
/** Peripheral CCM base address */
#define CCM_BASE                                 (0x40CC0000u)
/** Peripheral CCM base pointer */
#define CCM                                      ((CCM_Type *)CCM_BASE)
/** Array initializer of CCM peripheral base addresses */
#define CCM_BASE_ADDRS                           { CCM_BASE }
/** Array initializer of CCM peripheral base pointers */
#define CCM_BASE_PTRS                            { CCM }

/* CCM_OBS - Peripheral instance base addresses */
/** Peripheral CCM_OBS base address */
#define CCM_OBS_BASE                             (0x40150000u)
/** Peripheral CCM_OBS base pointer */
#define CCM_OBS                                  ((CCM_OBS_Type *)CCM_OBS_BASE)
/** Array initializer of CCM_OBS peripheral base addresses */
#define CCM_OBS_BASE_ADDRS                       { CCM_OBS_BASE }
/** Array initializer of CCM_OBS peripheral base pointers */
#define CCM_OBS_BASE_PTRS                        { CCM_OBS }

/* CDOG - Peripheral instance base addresses */
/** Peripheral CDOG base address */
#define CDOG_BASE                                (0x41900000u)
/** Peripheral CDOG base pointer */
#define CDOG                                     ((CDOG_Type *)CDOG_BASE)
/** Array initializer of CDOG peripheral base addresses */
#define CDOG_BASE_ADDRS                          { CDOG_BASE }
/** Array initializer of CDOG peripheral base pointers */
#define CDOG_BASE_PTRS                           { CDOG }
/** Interrupt vectors for the CDOG peripheral type */
#define CDOG_IRQS                                { CDOG_IRQn }

/* CMP - Peripheral instance base addresses */
/** Peripheral CMP1 base address */
#define CMP1_BASE                                (0x401A4000u)
/** Peripheral CMP1 base pointer */
#define CMP1                                     ((CMP_Type *)CMP1_BASE)
/** Peripheral CMP2 base address */
#define CMP2_BASE                                (0x401A8000u)
/** Peripheral CMP2 base pointer */
#define CMP2                                     ((CMP_Type *)CMP2_BASE)
/** Peripheral CMP3 base address */
#define CMP3_BASE                                (0x401AC000u)
/** Peripheral CMP3 base pointer */
#define CMP3                                     ((CMP_Type *)CMP3_BASE)
/** Peripheral CMP4 base address */
#define CMP4_BASE                                (0x401B0000u)
/** Peripheral CMP4 base pointer */
#define CMP4                                     ((CMP_Type *)CMP4_BASE)
/** Array initializer of CMP peripheral base addresses */
#define CMP_BASE_ADDRS                           { 0u, CMP1_BASE, CMP2_BASE, CMP3_BASE, CMP4_BASE }
/** Array initializer of CMP peripheral base pointers */
#define CMP_BASE_PTRS                            { (CMP_Type *)0u, CMP1, CMP2, CMP3, CMP4 }
/** Interrupt vectors for the CMP peripheral type */
#define CMP_IRQS                                 { NotAvail_IRQn, ACMP1_IRQn, ACMP2_IRQn, ACMP3_IRQn, ACMP4_IRQn }

/* DAC - Peripheral instance base addresses */
/** Peripheral DAC base address */
#define DAC_BASE                                 (0x40064000u)
/** Peripheral DAC base pointer */
#define DAC                                      ((DAC_Type *)DAC_BASE)
/** Array initializer of DAC peripheral base addresses */
#define DAC_BASE_ADDRS                           { DAC_BASE }
/** Array initializer of DAC peripheral base pointers */
#define DAC_BASE_PTRS                            { DAC }
/** Interrupt vectors for the DAC peripheral type */
#define DAC_IRQS                                 { DAC_IRQn }

/* DCDC - Peripheral instance base addresses */
/** Peripheral DCDC base address */
#define DCDC_BASE                                (0x40CA8000u)
/** Peripheral DCDC base pointer */
#define DCDC                                     ((DCDC_Type *)DCDC_BASE)
/** Array initializer of DCDC peripheral base addresses */
#define DCDC_BASE_ADDRS                          { DCDC_BASE }
/** Array initializer of DCDC peripheral base pointers */
#define DCDC_BASE_PTRS                           { DCDC }

/* DCIC - Peripheral instance base addresses */
/** Peripheral DCIC1 base address */
#define DCIC1_BASE                               (0x40819000u)
/** Peripheral DCIC1 base pointer */
#define DCIC1                                    ((DCIC_Type *)DCIC1_BASE)
/** Peripheral DCIC2 base address */
#define DCIC2_BASE                               (0x4081A000u)
/** Peripheral DCIC2 base pointer */
#define DCIC2                                    ((DCIC_Type *)DCIC2_BASE)
/** Array initializer of DCIC peripheral base addresses */
#define DCIC_BASE_ADDRS                          { 0u, DCIC1_BASE, DCIC2_BASE }
/** Array initializer of DCIC peripheral base pointers */
#define DCIC_BASE_PTRS                           { (DCIC_Type *)0u, DCIC1, DCIC2 }

/* DMA - Peripheral instance base addresses */
/** Peripheral DMA0 base address */
#define DMA0_BASE                                (0x40070000u)
/** Peripheral DMA0 base pointer */
#define DMA0                                     ((DMA_Type *)DMA0_BASE)
/** Array initializer of DMA peripheral base addresses */
#define DMA_BASE_ADDRS                           { DMA0_BASE }
/** Array initializer of DMA peripheral base pointers */
#define DMA_BASE_PTRS                            { DMA0 }
/** Interrupt vectors for the DMA peripheral type */
#define DMA_CHN_IRQS                             { { DMA0_DMA16_IRQn, DMA1_DMA17_IRQn, DMA2_DMA18_IRQn, DMA3_DMA19_IRQn, DMA4_DMA20_IRQn, DMA5_DMA21_IRQn, DMA6_DMA22_IRQn, DMA7_DMA23_IRQn, DMA8_DMA24_IRQn, DMA9_DMA25_IRQn, DMA10_DMA26_IRQn, DMA11_DMA27_IRQn, DMA12_DMA28_IRQn, DMA13_DMA29_IRQn, DMA14_DMA30_IRQn, DMA15_DMA31_IRQn, DMA0_DMA16_IRQn, DMA1_DMA17_IRQn, DMA2_DMA18_IRQn, DMA3_DMA19_IRQn, DMA4_DMA20_IRQn, DMA5_DMA21_IRQn, DMA6_DMA22_IRQn, DMA7_DMA23_IRQn, DMA8_DMA24_IRQn, DMA9_DMA25_IRQn, DMA10_DMA26_IRQn, DMA11_DMA27_IRQn, DMA12_DMA28_IRQn, DMA13_DMA29_IRQn, DMA14_DMA30_IRQn, DMA15_DMA31_IRQn } }
#define DMA_ERROR_IRQS                           { DMA_ERROR_IRQn }

/* DMAMUX - Peripheral instance base addresses */
/** Peripheral DMAMUX0 base address */
#define DMAMUX0_BASE                             (0x40074000u)
/** Peripheral DMAMUX0 base pointer */
#define DMAMUX0                                  ((DMAMUX_Type *)DMAMUX0_BASE)
/** Array initializer of DMAMUX peripheral base addresses */
#define DMAMUX_BASE_ADDRS                        { DMAMUX0_BASE }
/** Array initializer of DMAMUX peripheral base pointers */
#define DMAMUX_BASE_PTRS                         { DMAMUX0 }

/* DSI_HOST - Peripheral instance base addresses */
/** Peripheral DSI_HOST base address */
#define DSI_HOST_BASE                            (0x4080C000u)
/** Peripheral DSI_HOST base pointer */
#define DSI_HOST                                 ((DSI_HOST_Type *)DSI_HOST_BASE)
/** Array initializer of DSI_HOST peripheral base addresses */
#define DSI_HOST_BASE_ADDRS                      { DSI_HOST_BASE }
/** Array initializer of DSI_HOST peripheral base pointers */
#define DSI_HOST_BASE_PTRS                       { DSI_HOST }
/** Interrupt vectors for the DSI_HOST peripheral type */
#define DSI_HOST_DSI_IRQS                        { MIPI_DSI_IRQn }

/* DSI_HOST_APB_PKT_IF - Peripheral instance base addresses */
/** Peripheral DSI_HOST_APB_PKT_IF base address */
#define DSI_HOST_APB_PKT_IF_BASE                 (0x4080C280u)
/** Peripheral DSI_HOST_APB_PKT_IF base pointer */
#define DSI_HOST_APB_PKT_IF                      ((DSI_HOST_APB_PKT_IF_Type *)DSI_HOST_APB_PKT_IF_BASE)
/** Array initializer of DSI_HOST_APB_PKT_IF peripheral base addresses */
#define DSI_HOST_APB_PKT_IF_BASE_ADDRS           { DSI_HOST_APB_PKT_IF_BASE }
/** Array initializer of DSI_HOST_APB_PKT_IF peripheral base pointers */
#define DSI_HOST_APB_PKT_IF_BASE_PTRS            { DSI_HOST_APB_PKT_IF }

/* DSI_HOST_DPI_INTFC - Peripheral instance base addresses */
/** Peripheral DSI_HOST_DPI_INTFC base address */
#define DSI_HOST_DPI_INTFC_BASE                  (0x4080C200u)
/** Peripheral DSI_HOST_DPI_INTFC base pointer */
#define DSI_HOST_DPI_INTFC                       ((DSI_HOST_DPI_INTFC_Type *)DSI_HOST_DPI_INTFC_BASE)
/** Array initializer of DSI_HOST_DPI_INTFC peripheral base addresses */
#define DSI_HOST_DPI_INTFC_BASE_ADDRS            { DSI_HOST_DPI_INTFC_BASE }
/** Array initializer of DSI_HOST_DPI_INTFC peripheral base pointers */
#define DSI_HOST_DPI_INTFC_BASE_PTRS             { DSI_HOST_DPI_INTFC }

/* DSI_HOST_NXP_FDSOI28_DPHY_INTFC - Peripheral instance base addresses */
/** Peripheral DSI_HOST_DPHY_INTFC base address */
#define DSI_HOST_DPHY_INTFC_BASE                 (0x4080C300u)
/** Peripheral DSI_HOST_DPHY_INTFC base pointer */
#define DSI_HOST_DPHY_INTFC                      ((DSI_HOST_NXP_FDSOI28_DPHY_INTFC_Type *)DSI_HOST_DPHY_INTFC_BASE)
/** Array initializer of DSI_HOST_NXP_FDSOI28_DPHY_INTFC peripheral base
 * addresses */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_BASE_ADDRS { DSI_HOST_DPHY_INTFC_BASE }
/** Array initializer of DSI_HOST_NXP_FDSOI28_DPHY_INTFC peripheral base
 * pointers */
#define DSI_HOST_NXP_FDSOI28_DPHY_INTFC_BASE_PTRS { DSI_HOST_DPHY_INTFC }

/* EMVSIM - Peripheral instance base addresses */
/** Peripheral EMVSIM1 base address */
#define EMVSIM1_BASE                             (0x40154000u)
/** Peripheral EMVSIM1 base pointer */
#define EMVSIM1                                  ((EMVSIM_Type *)EMVSIM1_BASE)
/** Peripheral EMVSIM2 base address */
#define EMVSIM2_BASE                             (0x40158000u)
/** Peripheral EMVSIM2 base pointer */
#define EMVSIM2                                  ((EMVSIM_Type *)EMVSIM2_BASE)
/** Array initializer of EMVSIM peripheral base addresses */
#define EMVSIM_BASE_ADDRS                        { 0u, EMVSIM1_BASE, EMVSIM2_BASE }
/** Array initializer of EMVSIM peripheral base pointers */
#define EMVSIM_BASE_PTRS                         { (EMVSIM_Type *)0u, EMVSIM1, EMVSIM2 }
/** Interrupt vectors for the EMVSIM peripheral type */
#define EMVSIM_IRQS                              { NotAvail_IRQn, EMVSIM1_IRQn, EMVSIM2_IRQn }

/* ENC - Peripheral instance base addresses */
/** Peripheral ENC1 base address */
#define ENC1_BASE                                (0x40174000u)
/** Peripheral ENC1 base pointer */
#define ENC1                                     ((ENC_Type *)ENC1_BASE)
/** Peripheral ENC2 base address */
#define ENC2_BASE                                (0x40178000u)
/** Peripheral ENC2 base pointer */
#define ENC2                                     ((ENC_Type *)ENC2_BASE)
/** Peripheral ENC3 base address */
#define ENC3_BASE                                (0x4017C000u)
/** Peripheral ENC3 base pointer */
#define ENC3                                     ((ENC_Type *)ENC3_BASE)
/** Peripheral ENC4 base address */
#define ENC4_BASE                                (0x40180000u)
/** Peripheral ENC4 base pointer */
#define ENC4                                     ((ENC_Type *)ENC4_BASE)
/** Array initializer of ENC peripheral base addresses */
#define ENC_BASE_ADDRS                           { 0u, ENC1_BASE, ENC2_BASE, ENC3_BASE, ENC4_BASE }
/** Array initializer of ENC peripheral base pointers */
#define ENC_BASE_PTRS                            { (ENC_Type *)0u, ENC1, ENC2, ENC3, ENC4 }
/** Interrupt vectors for the ENC peripheral type */
#define ENC_COMPARE_IRQS                         { NotAvail_IRQn, ENC1_IRQn, ENC2_IRQn, ENC3_IRQn, ENC4_IRQn }
#define ENC_HOME_IRQS                            { NotAvail_IRQn, ENC1_IRQn, ENC2_IRQn, ENC3_IRQn, ENC4_IRQn }
#define ENC_WDOG_IRQS                            { NotAvail_IRQn, ENC1_IRQn, ENC2_IRQn, ENC3_IRQn, ENC4_IRQn }
#define ENC_INDEX_IRQS                           { NotAvail_IRQn, ENC1_IRQn, ENC2_IRQn, ENC3_IRQn, ENC4_IRQn }
#define ENC_INPUT_SWITCH_IRQS                    { NotAvail_IRQn, ENC1_IRQn, ENC2_IRQn, ENC3_IRQn, ENC4_IRQn }

/* ENET - Peripheral instance base addresses */
/** Peripheral ENET base address */
#define ENET_BASE                                (0x40424000u)
/** Peripheral ENET base pointer */
#define ENET                                     ((ENET_Type *)ENET_BASE)
/** Peripheral ENET_1G base address */
#define ENET_1G_BASE                             (0x40420000u)
/** Peripheral ENET_1G base pointer */
#define ENET_1G                                  ((ENET_Type *)ENET_1G_BASE)
/** Array initializer of ENET peripheral base addresses */
#define ENET_BASE_ADDRS                          { ENET_BASE, ENET_1G_BASE }
/** Array initializer of ENET peripheral base pointers */
#define ENET_BASE_PTRS                           { ENET, ENET_1G }
/** Interrupt vectors for the ENET peripheral type */
#define ENET_Transmit_IRQS                       { ENET_IRQn, ENET_1G_IRQn }
#define ENET_Receive_IRQS                        { ENET_IRQn, ENET_1G_IRQn }
#define ENET_Error_IRQS                          { ENET_IRQn, ENET_1G_IRQn }
#define ENET_1588_Timer_IRQS                     { ENET_1588_Timer_IRQn, ENET_1G_1588_Timer_IRQn }
#define ENET_Ts_IRQS                             { ENET_IRQn, ENET_1G_IRQn }

/* ETHERNET_PLL - Peripheral instance base addresses */
/** Peripheral ETHERNET_PLL base address */
#define ETHERNET_PLL_BASE                        (0u)
/** Peripheral ETHERNET_PLL base pointer */
#define ETHERNET_PLL                             ((ETHERNET_PLL_Type *)ETHERNET_PLL_BASE)
/** Array initializer of ETHERNET_PLL peripheral base addresses */
#define ETHERNET_PLL_BASE_ADDRS                  { ETHERNET_PLL_BASE }
/** Array initializer of ETHERNET_PLL peripheral base pointers */
#define ETHERNET_PLL_BASE_PTRS                   { ETHERNET_PLL }

/* EWM - Peripheral instance base addresses */
/** Peripheral EWM base address */
#define EWM_BASE                                 (0x4002C000u)
/** Peripheral EWM base pointer */
#define EWM                                      ((EWM_Type *)EWM_BASE)
/** Array initializer of EWM peripheral base addresses */
#define EWM_BASE_ADDRS                           { EWM_BASE }
/** Array initializer of EWM peripheral base pointers */
#define EWM_BASE_PTRS                            { EWM }
/** Interrupt vectors for the EWM peripheral type */
#define EWM_IRQS                                 { EWM_IRQn }

/* FLEXIO - Peripheral instance base addresses */
/** Peripheral FLEXIO1 base address */
#define FLEXIO1_BASE                             (0x400AC000u)
/** Peripheral FLEXIO1 base pointer */
#define FLEXIO1                                  ((FLEXIO_Type *)FLEXIO1_BASE)
/** Peripheral FLEXIO2 base address */
#define FLEXIO2_BASE                             (0x400B0000u)
/** Peripheral FLEXIO2 base pointer */
#define FLEXIO2                                  ((FLEXIO_Type *)FLEXIO2_BASE)
/** Array initializer of FLEXIO peripheral base addresses */
#define FLEXIO_BASE_ADDRS                        { 0u, FLEXIO1_BASE, FLEXIO2_BASE }
/** Array initializer of FLEXIO peripheral base pointers */
#define FLEXIO_BASE_PTRS                         { (FLEXIO_Type *)0u, FLEXIO1, FLEXIO2 }
/** Interrupt vectors for the FLEXIO peripheral type */
#define FLEXIO_IRQS                              { NotAvail_IRQn, FLEXIO1_IRQn, FLEXIO2_IRQn }

/* FLEXRAM - Peripheral instance base addresses */
/** Peripheral FLEXRAM base address */
#define FLEXRAM_BASE                             (0x40028000u)
/** Peripheral FLEXRAM base pointer */
#define FLEXRAM                                  ((FLEXRAM_Type *)FLEXRAM_BASE)
/** Array initializer of FLEXRAM peripheral base addresses */
#define FLEXRAM_BASE_ADDRS                       { FLEXRAM_BASE }
/** Array initializer of FLEXRAM peripheral base pointers */
#define FLEXRAM_BASE_PTRS                        { FLEXRAM }
/** Interrupt vectors for the FLEXRAM peripheral type */
#define FLEXRAM_IRQS                             { FLEXRAM_IRQn }
#define FLEXRAM_ECC_IRQS                         { FLEXRAM_ECC_IRQn }

/* FLEXSPI - Peripheral instance base addresses */
/** Peripheral FLEXSPI1 base address */
#define FLEXSPI1_BASE                            (0x400CC000u)
/** Peripheral FLEXSPI1 base pointer */
#define FLEXSPI1                                 ((FLEXSPI_Type *)FLEXSPI1_BASE)
/** Peripheral FLEXSPI2 base address */
#define FLEXSPI2_BASE                            (0x400D0000u)
/** Peripheral FLEXSPI2 base pointer */
#define FLEXSPI2                                 ((FLEXSPI_Type *)FLEXSPI2_BASE)
/** Array initializer of FLEXSPI peripheral base addresses */
#define FLEXSPI_BASE_ADDRS                       { 0u, FLEXSPI1_BASE, FLEXSPI2_BASE }
/** Array initializer of FLEXSPI peripheral base pointers */
#define FLEXSPI_BASE_PTRS                        { (FLEXSPI_Type *)0u, FLEXSPI1, FLEXSPI2 }
/** Interrupt vectors for the FLEXSPI peripheral type */
#define FLEXSPI_IRQS                             { NotAvail_IRQn, FLEXSPI1_IRQn, FLEXSPI2_IRQn }
/** FlexSPI AMBA memory base alias count */
#define FLEXSPI_AMBA_BASE_ALIAS_COUNT     (1)
/* FlexSPI AMBA base address array. */
#define FlexSPI_AMBA_BASE_ARRAY                  { {0u}, {0x30000000u}, {0x60000000u} }
/* FlexSPI AMBA end address array. */
#define FlexSPI_AMBA_END_ARRAY                   { {0u}, {0x3FFFFFFFu}, {0x7F7FFFFFu} }
/* FlexSPI1 AMBA address. */
#define FlexSPI1_AMBA_BASE                       (0x30000000u)
/* FlexSPI1 ASFM address. */
#define FlexSPI1_ASFM_BASE                       (0x30000000u)
/* Base Address of AHB address space mapped to IP RX FIFO. */
#define FlexSPI1_ARDF_BASE                       (0x2FC00000u)
/* Base Address of AHB address space mapped to IP TX FIFO. */
#define FlexSPI1_ATDF_BASE                       (0x2F800000u)
/* FlexSPI2 AMBA address. */
#define FlexSPI2_AMBA_BASE                       (0x60000000u)
/* FlexSPI2 ASFM address. */
#define FlexSPI2_ASFM_BASE                       (0x60000000u)
/* Base Address of AHB address space mapped to IP RX FIFO. */
#define FlexSPI2_ARDF_BASE                       (0x7FC00000u)
/* Base Address of AHB address space mapped to IP TX FIFO. */
#define FlexSPI2_ATDF_BASE                       (0x7F800000u)


/* GPC_CPU_MODE_CTRL - Peripheral instance base addresses */
/** Peripheral GPC_CPU_MODE_CTRL_0 base address */
#define GPC_CPU_MODE_CTRL_0_BASE                 (0x40C00000u)
/** Peripheral GPC_CPU_MODE_CTRL_0 base pointer */
#define GPC_CPU_MODE_CTRL_0                      ((GPC_CPU_MODE_CTRL_Type *)GPC_CPU_MODE_CTRL_0_BASE)
/** Peripheral GPC_CPU_MODE_CTRL_1 base address */
#define GPC_CPU_MODE_CTRL_1_BASE                 (0x40C00800u)
/** Peripheral GPC_CPU_MODE_CTRL_1 base pointer */
#define GPC_CPU_MODE_CTRL_1                      ((GPC_CPU_MODE_CTRL_Type *)GPC_CPU_MODE_CTRL_1_BASE)
/** Array initializer of GPC_CPU_MODE_CTRL peripheral base addresses */
#define GPC_CPU_MODE_CTRL_BASE_ADDRS             { GPC_CPU_MODE_CTRL_0_BASE, GPC_CPU_MODE_CTRL_1_BASE }
/** Array initializer of GPC_CPU_MODE_CTRL peripheral base pointers */
#define GPC_CPU_MODE_CTRL_BASE_PTRS              { GPC_CPU_MODE_CTRL_0, GPC_CPU_MODE_CTRL_1 }

/* GPC_SET_POINT_CTRL - Peripheral instance base addresses */
/** Peripheral GPC_SET_POINT_CTRL base address */
#define GPC_SET_POINT_CTRL_BASE                  (0x40C02000u)
/** Peripheral GPC_SET_POINT_CTRL base pointer */
#define GPC_SET_POINT_CTRL                       ((GPC_SET_POINT_CTRL_Type *)GPC_SET_POINT_CTRL_BASE)
/** Array initializer of GPC_SET_POINT_CTRL peripheral base addresses */
#define GPC_SET_POINT_CTRL_BASE_ADDRS            { GPC_SET_POINT_CTRL_BASE }
/** Array initializer of GPC_SET_POINT_CTRL peripheral base pointers */
#define GPC_SET_POINT_CTRL_BASE_PTRS             { GPC_SET_POINT_CTRL }

/* GPC_STBY_CTRL - Peripheral instance base addresses */
/** Peripheral GPC_STBY_CTRL base address */
#define GPC_STBY_CTRL_BASE                       (0x40C02800u)
/** Peripheral GPC_STBY_CTRL base pointer */
#define GPC_STBY_CTRL                            ((GPC_STBY_CTRL_Type *)GPC_STBY_CTRL_BASE)
/** Array initializer of GPC_STBY_CTRL peripheral base addresses */
#define GPC_STBY_CTRL_BASE_ADDRS                 { GPC_STBY_CTRL_BASE }
/** Array initializer of GPC_STBY_CTRL peripheral base pointers */
#define GPC_STBY_CTRL_BASE_PTRS                  { GPC_STBY_CTRL }

/* GPIO - Peripheral instance base addresses */
/** Peripheral GPIO1 base address */
#define GPIO1_BASE                               (0x4012C000u)
/** Peripheral GPIO1 base pointer */
#define GPIO1                                    ((GPIO_Type *)GPIO1_BASE)
/** Peripheral GPIO2 base address */
#define GPIO2_BASE                               (0x40130000u)
/** Peripheral GPIO2 base pointer */
#define GPIO2                                    ((GPIO_Type *)GPIO2_BASE)
/** Peripheral GPIO3 base address */
#define GPIO3_BASE                               (0x40134000u)
/** Peripheral GPIO3 base pointer */
#define GPIO3                                    ((GPIO_Type *)GPIO3_BASE)
/** Peripheral GPIO4 base address */
#define GPIO4_BASE                               (0x40138000u)
/** Peripheral GPIO4 base pointer */
#define GPIO4                                    ((GPIO_Type *)GPIO4_BASE)
/** Peripheral GPIO5 base address */
#define GPIO5_BASE                               (0x4013C000u)
/** Peripheral GPIO5 base pointer */
#define GPIO5                                    ((GPIO_Type *)GPIO5_BASE)
/** Peripheral GPIO6 base address */
#define GPIO6_BASE                               (0x40140000u)
/** Peripheral GPIO6 base pointer */
#define GPIO6                                    ((GPIO_Type *)GPIO6_BASE)
/** Peripheral GPIO7 base address */
#define GPIO7_BASE                               (0x40C5C000u)
/** Peripheral GPIO7 base pointer */
#define GPIO7                                    ((GPIO_Type *)GPIO7_BASE)
/** Peripheral GPIO8 base address */
#define GPIO8_BASE                               (0x40C60000u)
/** Peripheral GPIO8 base pointer */
#define GPIO8                                    ((GPIO_Type *)GPIO8_BASE)
/** Peripheral GPIO9 base address */
#define GPIO9_BASE                               (0x40C64000u)
/** Peripheral GPIO9 base pointer */
#define GPIO9                                    ((GPIO_Type *)GPIO9_BASE)
/** Peripheral GPIO10 base address */
#define GPIO10_BASE                              (0x40C68000u)
/** Peripheral GPIO10 base pointer */
#define GPIO10                                   ((GPIO_Type *)GPIO10_BASE)
/** Peripheral GPIO11 base address */
#define GPIO11_BASE                              (0x40C6C000u)
/** Peripheral GPIO11 base pointer */
#define GPIO11                                   ((GPIO_Type *)GPIO11_BASE)
/** Peripheral GPIO12 base address */
#define GPIO12_BASE                              (0x40C70000u)
/** Peripheral GPIO12 base pointer */
#define GPIO12                                   ((GPIO_Type *)GPIO12_BASE)
/** Peripheral GPIO13 base address */
#define GPIO13_BASE                              (0x40CA0000u)
/** Peripheral GPIO13 base pointer */
#define GPIO13                                   ((GPIO_Type *)GPIO13_BASE)
/** Peripheral CM7_GPIO2 base address */
#define CM7_GPIO2_BASE                           (0x42008000u)
/** Peripheral CM7_GPIO2 base pointer */
#define CM7_GPIO2                                ((GPIO_Type *)CM7_GPIO2_BASE)
/** Peripheral CM7_GPIO3 base address */
#define CM7_GPIO3_BASE                           (0x4200C000u)
/** Peripheral CM7_GPIO3 base pointer */
#define CM7_GPIO3                                ((GPIO_Type *)CM7_GPIO3_BASE)
/** Array initializer of GPIO peripheral base addresses */
#define GPIO_BASE_ADDRS                          { 0u, GPIO1_BASE, GPIO2_BASE, GPIO3_BASE, GPIO4_BASE, GPIO5_BASE, GPIO6_BASE, GPIO7_BASE, GPIO8_BASE, GPIO9_BASE, GPIO10_BASE, GPIO11_BASE, GPIO12_BASE, GPIO13_BASE, CM7_GPIO2_BASE, CM7_GPIO3_BASE }
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { (GPIO_Type *)0u, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO6, GPIO7, GPIO8, GPIO9, GPIO10, GPIO11, GPIO12, GPIO13, CM7_GPIO2, CM7_GPIO3 }
/** Interrupt vectors for the GPIO peripheral type */
#define GPIO_COMBINED_LOW_IRQS                   { NotAvail_IRQn, GPIO1_Combined_0_15_IRQn, GPIO2_Combined_0_15_IRQn, GPIO3_Combined_0_15_IRQn, GPIO4_Combined_0_15_IRQn, GPIO5_Combined_0_15_IRQn, GPIO6_Combined_0_15_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, GPIO13_Combined_0_31_IRQn, CM7_GPIO2_3_IRQn, CM7_GPIO2_3_IRQn }
#define GPIO_COMBINED_HIGH_IRQS                  { NotAvail_IRQn, GPIO1_Combined_16_31_IRQn, GPIO2_Combined_16_31_IRQn, GPIO3_Combined_16_31_IRQn, GPIO4_Combined_16_31_IRQn, GPIO5_Combined_16_31_IRQn, GPIO6_Combined_16_31_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, GPIO13_Combined_0_31_IRQn, CM7_GPIO2_3_IRQn, CM7_GPIO2_3_IRQn }

/* GPT - Peripheral instance base addresses */
/** Peripheral GPT1 base address */
#define GPT1_BASE                                (0x400EC000u)
/** Peripheral GPT1 base pointer */
#define GPT1                                     ((GPT_Type *)GPT1_BASE)
/** Peripheral GPT2 base address */
#define GPT2_BASE                                (0x400F0000u)
/** Peripheral GPT2 base pointer */
#define GPT2                                     ((GPT_Type *)GPT2_BASE)
/** Peripheral GPT3 base address */
#define GPT3_BASE                                (0x400F4000u)
/** Peripheral GPT3 base pointer */
#define GPT3                                     ((GPT_Type *)GPT3_BASE)
/** Peripheral GPT4 base address */
#define GPT4_BASE                                (0x400F8000u)
/** Peripheral GPT4 base pointer */
#define GPT4                                     ((GPT_Type *)GPT4_BASE)
/** Peripheral GPT5 base address */
#define GPT5_BASE                                (0x400FC000u)
/** Peripheral GPT5 base pointer */
#define GPT5                                     ((GPT_Type *)GPT5_BASE)
/** Peripheral GPT6 base address */
#define GPT6_BASE                                (0x40100000u)
/** Peripheral GPT6 base pointer */
#define GPT6                                     ((GPT_Type *)GPT6_BASE)
/** Array initializer of GPT peripheral base addresses */
#define GPT_BASE_ADDRS                           { 0u, GPT1_BASE, GPT2_BASE, GPT3_BASE, GPT4_BASE, GPT5_BASE, GPT6_BASE }
/** Array initializer of GPT peripheral base pointers */
#define GPT_BASE_PTRS                            { (GPT_Type *)0u, GPT1, GPT2, GPT3, GPT4, GPT5, GPT6 }
/** Interrupt vectors for the GPT peripheral type */
#define GPT_IRQS                                 { NotAvail_IRQn, GPT1_IRQn, GPT2_IRQn, GPT3_IRQn, GPT4_IRQn, GPT5_IRQn, GPT6_IRQn }

/* I2S - Peripheral instance base addresses */
/** Peripheral SAI1 base address */
#define SAI1_BASE                                (0x40404000u)
/** Peripheral SAI1 base pointer */
#define SAI1                                     ((I2S_Type *)SAI1_BASE)
/** Peripheral SAI2 base address */
#define SAI2_BASE                                (0x40408000u)
/** Peripheral SAI2 base pointer */
#define SAI2                                     ((I2S_Type *)SAI2_BASE)
/** Peripheral SAI3 base address */
#define SAI3_BASE                                (0x4040C000u)
/** Peripheral SAI3 base pointer */
#define SAI3                                     ((I2S_Type *)SAI3_BASE)
/** Peripheral SAI4 base address */
#define SAI4_BASE                                (0x40C40000u)
/** Peripheral SAI4 base pointer */
#define SAI4                                     ((I2S_Type *)SAI4_BASE)
/** Array initializer of I2S peripheral base addresses */
#define I2S_BASE_ADDRS                           { 0u, SAI1_BASE, SAI2_BASE, SAI3_BASE, SAI4_BASE }
/** Array initializer of I2S peripheral base pointers */
#define I2S_BASE_PTRS                            { (I2S_Type *)0u, SAI1, SAI2, SAI3, SAI4 }
/** Interrupt vectors for the I2S peripheral type */
#define I2S_RX_IRQS                              { NotAvail_IRQn, SAI1_IRQn, SAI2_IRQn, SAI3_RX_IRQn, SAI4_RX_IRQn }
#define I2S_TX_IRQS                              { NotAvail_IRQn, SAI1_IRQn, SAI2_IRQn, SAI3_TX_IRQn, SAI4_TX_IRQn }

/* IEE - Peripheral instance base addresses */
/** Peripheral IEE__IEE_RT1170 base address */
#define IEE__IEE_RT1170_BASE                     (0x4006C000u)
/** Peripheral IEE__IEE_RT1170 base pointer */
#define IEE__IEE_RT1170                          ((IEE_Type *)IEE__IEE_RT1170_BASE)
/** Array initializer of IEE peripheral base addresses */
#define IEE_BASE_ADDRS                           { IEE__IEE_RT1170_BASE }
/** Array initializer of IEE peripheral base pointers */
#define IEE_BASE_PTRS                            { IEE__IEE_RT1170 }

/* IEE_APC - Peripheral instance base addresses */
/** Peripheral IEE_APC base address */
#define IEE_APC_BASE                             (0x40068000u)
/** Peripheral IEE_APC base pointer */
#define IEE_APC                                  ((IEE_APC_Type *)IEE_APC_BASE)
/** Array initializer of IEE_APC peripheral base addresses */
#define IEE_APC_BASE_ADDRS                       { IEE_APC_BASE }
/** Array initializer of IEE_APC peripheral base pointers */
#define IEE_APC_BASE_PTRS                        { IEE_APC }

/* IOMUXC - Peripheral instance base addresses */
/** Peripheral IOMUXC base address */
#define IOMUXC_BASE                              (0x400E8000u)
/** Peripheral IOMUXC base pointer */
#define IOMUXC                                   ((IOMUXC_Type *)IOMUXC_BASE)
/** Array initializer of IOMUXC peripheral base addresses */
#define IOMUXC_BASE_ADDRS                        { IOMUXC_BASE }
/** Array initializer of IOMUXC peripheral base pointers */
#define IOMUXC_BASE_PTRS                         { IOMUXC }

/* IOMUXC_GPR - Peripheral instance base addresses */
/** Peripheral IOMUXC_GPR base address */
#define IOMUXC_GPR_BASE                          (0x400E4000u)
/** Peripheral IOMUXC_GPR base pointer */
#define IOMUXC_GPR                               ((IOMUXC_GPR_Type *)IOMUXC_GPR_BASE)
/** Array initializer of IOMUXC_GPR peripheral base addresses */
#define IOMUXC_GPR_BASE_ADDRS                    { IOMUXC_GPR_BASE }
/** Array initializer of IOMUXC_GPR peripheral base pointers */
#define IOMUXC_GPR_BASE_PTRS                     { IOMUXC_GPR }

/* IOMUXC_LPSR - Peripheral instance base addresses */
/** Peripheral IOMUXC_LPSR base address */
#define IOMUXC_LPSR_BASE                         (0x40C08000u)
/** Peripheral IOMUXC_LPSR base pointer */
#define IOMUXC_LPSR                              ((IOMUXC_LPSR_Type *)IOMUXC_LPSR_BASE)
/** Array initializer of IOMUXC_LPSR peripheral base addresses */
#define IOMUXC_LPSR_BASE_ADDRS                   { IOMUXC_LPSR_BASE }
/** Array initializer of IOMUXC_LPSR peripheral base pointers */
#define IOMUXC_LPSR_BASE_PTRS                    { IOMUXC_LPSR }

/* IOMUXC_LPSR_GPR - Peripheral instance base addresses */
/** Peripheral IOMUXC_LPSR_GPR base address */
#define IOMUXC_LPSR_GPR_BASE                     (0x40C0C000u)
/** Peripheral IOMUXC_LPSR_GPR base pointer */
#define IOMUXC_LPSR_GPR                          ((IOMUXC_LPSR_GPR_Type *)IOMUXC_LPSR_GPR_BASE)
/** Array initializer of IOMUXC_LPSR_GPR peripheral base addresses */
#define IOMUXC_LPSR_GPR_BASE_ADDRS               { IOMUXC_LPSR_GPR_BASE }
/** Array initializer of IOMUXC_LPSR_GPR peripheral base pointers */
#define IOMUXC_LPSR_GPR_BASE_PTRS                { IOMUXC_LPSR_GPR }

/* IOMUXC_SNVS - Peripheral instance base addresses */
/** Peripheral IOMUXC_SNVS base address */
#define IOMUXC_SNVS_BASE                         (0x40C94000u)
/** Peripheral IOMUXC_SNVS base pointer */
#define IOMUXC_SNVS                              ((IOMUXC_SNVS_Type *)IOMUXC_SNVS_BASE)
/** Array initializer of IOMUXC_SNVS peripheral base addresses */
#define IOMUXC_SNVS_BASE_ADDRS                   { IOMUXC_SNVS_BASE }
/** Array initializer of IOMUXC_SNVS peripheral base pointers */
#define IOMUXC_SNVS_BASE_PTRS                    { IOMUXC_SNVS }

/* IOMUXC_SNVS_GPR - Peripheral instance base addresses */
/** Peripheral IOMUXC_SNVS_GPR base address */
#define IOMUXC_SNVS_GPR_BASE                     (0x40C98000u)
/** Peripheral IOMUXC_SNVS_GPR base pointer */
#define IOMUXC_SNVS_GPR                          ((IOMUXC_SNVS_GPR_Type *)IOMUXC_SNVS_GPR_BASE)
/** Array initializer of IOMUXC_SNVS_GPR peripheral base addresses */
#define IOMUXC_SNVS_GPR_BASE_ADDRS               { IOMUXC_SNVS_GPR_BASE }
/** Array initializer of IOMUXC_SNVS_GPR peripheral base pointers */
#define IOMUXC_SNVS_GPR_BASE_PTRS                { IOMUXC_SNVS_GPR }

/* IPS_DOMAIN - Peripheral instance base addresses */
/** Peripheral IPS_DOMAIN base address */
#define IPS_DOMAIN_BASE                          (0x40C87C00u)
/** Peripheral IPS_DOMAIN base pointer */
#define IPS_DOMAIN                               ((IPS_DOMAIN_Type *)IPS_DOMAIN_BASE)
/** Array initializer of IPS_DOMAIN peripheral base addresses */
#define IPS_DOMAIN_BASE_ADDRS                    { IPS_DOMAIN_BASE }
/** Array initializer of IPS_DOMAIN peripheral base pointers */
#define IPS_DOMAIN_BASE_PTRS                     { IPS_DOMAIN }

/* KEY_MANAGER - Peripheral instance base addresses */
/** Peripheral KEY_MANAGER base address */
#define KEY_MANAGER_BASE                         (0x40C80000u)
/** Peripheral KEY_MANAGER base pointer */
#define KEY_MANAGER                              ((KEY_MANAGER_Type *)KEY_MANAGER_BASE)
/** Array initializer of KEY_MANAGER peripheral base addresses */
#define KEY_MANAGER_BASE_ADDRS                   { KEY_MANAGER_BASE }
/** Array initializer of KEY_MANAGER peripheral base pointers */
#define KEY_MANAGER_BASE_PTRS                    { KEY_MANAGER }

/* KPP - Peripheral instance base addresses */
/** Peripheral KPP base address */
#define KPP_BASE                                 (0x400E0000u)
/** Peripheral KPP base pointer */
#define KPP                                      ((KPP_Type *)KPP_BASE)
/** Array initializer of KPP peripheral base addresses */
#define KPP_BASE_ADDRS                           { KPP_BASE }
/** Array initializer of KPP peripheral base pointers */
#define KPP_BASE_PTRS                            { KPP }
/** Interrupt vectors for the KPP peripheral type */
#define KPP_IRQS                                 { KPP_IRQn }

/* LCDIFV2 - Peripheral instance base addresses */
/** Peripheral LCDIFV2 base address */
#define LCDIFV2_BASE                             (0x40808000u)
/** Peripheral LCDIFV2 base pointer */
#define LCDIFV2                                  ((LCDIFV2_Type *)LCDIFV2_BASE)
/** Array initializer of LCDIFV2 peripheral base addresses */
#define LCDIFV2_BASE_ADDRS                       { LCDIFV2_BASE }
/** Array initializer of LCDIFV2 peripheral base pointers */
#define LCDIFV2_BASE_PTRS                        { LCDIFV2 }

/* LPI2C - Peripheral instance base addresses */
/** Peripheral LPI2C1 base address */
#define LPI2C1_BASE                              (0x40104000u)
/** Peripheral LPI2C1 base pointer */
#define LPI2C1                                   ((LPI2C_Type *)LPI2C1_BASE)
/** Peripheral LPI2C2 base address */
#define LPI2C2_BASE                              (0x40108000u)
/** Peripheral LPI2C2 base pointer */
#define LPI2C2                                   ((LPI2C_Type *)LPI2C2_BASE)
/** Peripheral LPI2C3 base address */
#define LPI2C3_BASE                              (0x4010C000u)
/** Peripheral LPI2C3 base pointer */
#define LPI2C3                                   ((LPI2C_Type *)LPI2C3_BASE)
/** Peripheral LPI2C4 base address */
#define LPI2C4_BASE                              (0x40110000u)
/** Peripheral LPI2C4 base pointer */
#define LPI2C4                                   ((LPI2C_Type *)LPI2C4_BASE)
/** Peripheral LPI2C5 base address */
#define LPI2C5_BASE                              (0x40C34000u)
/** Peripheral LPI2C5 base pointer */
#define LPI2C5                                   ((LPI2C_Type *)LPI2C5_BASE)
/** Peripheral LPI2C6 base address */
#define LPI2C6_BASE                              (0x40C38000u)
/** Peripheral LPI2C6 base pointer */
#define LPI2C6                                   ((LPI2C_Type *)LPI2C6_BASE)
/** Array initializer of LPI2C peripheral base addresses */
#define LPI2C_BASE_ADDRS                         { 0u, LPI2C1_BASE, LPI2C2_BASE, LPI2C3_BASE, LPI2C4_BASE, LPI2C5_BASE, LPI2C6_BASE }
/** Array initializer of LPI2C peripheral base pointers */
#define LPI2C_BASE_PTRS                          { (LPI2C_Type *)0u, LPI2C1, LPI2C2, LPI2C3, LPI2C4, LPI2C5, LPI2C6 }
/** Interrupt vectors for the LPI2C peripheral type */
#define LPI2C_IRQS                               { NotAvail_IRQn, LPI2C1_IRQn, LPI2C2_IRQn, LPI2C3_IRQn, LPI2C4_IRQn, LPI2C5_IRQn, LPI2C6_IRQn }

/* LPSPI - Peripheral instance base addresses */
/** Peripheral LPSPI1 base address */
#define LPSPI1_BASE                              (0x40114000u)
/** Peripheral LPSPI1 base pointer */
#define LPSPI1                                   ((LPSPI_Type *)LPSPI1_BASE)
/** Peripheral LPSPI2 base address */
#define LPSPI2_BASE                              (0x40118000u)
/** Peripheral LPSPI2 base pointer */
#define LPSPI2                                   ((LPSPI_Type *)LPSPI2_BASE)
/** Peripheral LPSPI3 base address */
#define LPSPI3_BASE                              (0x4011C000u)
/** Peripheral LPSPI3 base pointer */
#define LPSPI3                                   ((LPSPI_Type *)LPSPI3_BASE)
/** Peripheral LPSPI4 base address */
#define LPSPI4_BASE                              (0x40120000u)
/** Peripheral LPSPI4 base pointer */
#define LPSPI4                                   ((LPSPI_Type *)LPSPI4_BASE)
/** Peripheral LPSPI5 base address */
#define LPSPI5_BASE                              (0x40C2C000u)
/** Peripheral LPSPI5 base pointer */
#define LPSPI5                                   ((LPSPI_Type *)LPSPI5_BASE)
/** Peripheral LPSPI6 base address */
#define LPSPI6_BASE                              (0x40C30000u)
/** Peripheral LPSPI6 base pointer */
#define LPSPI6                                   ((LPSPI_Type *)LPSPI6_BASE)
/** Array initializer of LPSPI peripheral base addresses */
#define LPSPI_BASE_ADDRS                         { 0u, LPSPI1_BASE, LPSPI2_BASE, LPSPI3_BASE, LPSPI4_BASE, LPSPI5_BASE, LPSPI6_BASE }
/** Array initializer of LPSPI peripheral base pointers */
#define LPSPI_BASE_PTRS                          { (LPSPI_Type *)0u, LPSPI1, LPSPI2, LPSPI3, LPSPI4, LPSPI5, LPSPI6 }
/** Interrupt vectors for the LPSPI peripheral type */
#define LPSPI_IRQS                               { NotAvail_IRQn, LPSPI1_IRQn, LPSPI2_IRQn, LPSPI3_IRQn, LPSPI4_IRQn, LPSPI5_IRQn, LPSPI6_IRQn }

/* LPUART - Peripheral instance base addresses */
/** Peripheral LPUART1 base address */
#define LPUART1_BASE                             (0x4007C000u)
/** Peripheral LPUART1 base pointer */
#define LPUART1                                  ((LPUART_Type *)LPUART1_BASE)
/** Peripheral LPUART2 base address */
#define LPUART2_BASE                             (0x40080000u)
/** Peripheral LPUART2 base pointer */
#define LPUART2                                  ((LPUART_Type *)LPUART2_BASE)
/** Peripheral LPUART3 base address */
#define LPUART3_BASE                             (0x40084000u)
/** Peripheral LPUART3 base pointer */
#define LPUART3                                  ((LPUART_Type *)LPUART3_BASE)
/** Peripheral LPUART4 base address */
#define LPUART4_BASE                             (0x40088000u)
/** Peripheral LPUART4 base pointer */
#define LPUART4                                  ((LPUART_Type *)LPUART4_BASE)
/** Peripheral LPUART5 base address */
#define LPUART5_BASE                             (0x4008C000u)
/** Peripheral LPUART5 base pointer */
#define LPUART5                                  ((LPUART_Type *)LPUART5_BASE)
/** Peripheral LPUART6 base address */
#define LPUART6_BASE                             (0x40090000u)
/** Peripheral LPUART6 base pointer */
#define LPUART6                                  ((LPUART_Type *)LPUART6_BASE)
/** Peripheral LPUART7 base address */
#define LPUART7_BASE                             (0x40094000u)
/** Peripheral LPUART7 base pointer */
#define LPUART7                                  ((LPUART_Type *)LPUART7_BASE)
/** Peripheral LPUART8 base address */
#define LPUART8_BASE                             (0x40098000u)
/** Peripheral LPUART8 base pointer */
#define LPUART8                                  ((LPUART_Type *)LPUART8_BASE)
/** Peripheral LPUART9 base address */
#define LPUART9_BASE                             (0x4009C000u)
/** Peripheral LPUART9 base pointer */
#define LPUART9                                  ((LPUART_Type *)LPUART9_BASE)
/** Peripheral LPUART10 base address */
#define LPUART10_BASE                            (0x400A0000u)
/** Peripheral LPUART10 base pointer */
#define LPUART10                                 ((LPUART_Type *)LPUART10_BASE)
/** Peripheral LPUART11 base address */
#define LPUART11_BASE                            (0x40C24000u)
/** Peripheral LPUART11 base pointer */
#define LPUART11                                 ((LPUART_Type *)LPUART11_BASE)
/** Peripheral LPUART12 base address */
#define LPUART12_BASE                            (0x40C28000u)
/** Peripheral LPUART12 base pointer */
#define LPUART12                                 ((LPUART_Type *)LPUART12_BASE)
/** Array initializer of LPUART peripheral base addresses */
#define LPUART_BASE_ADDRS                        { 0u, LPUART1_BASE, LPUART2_BASE, LPUART3_BASE, LPUART4_BASE, LPUART5_BASE, LPUART6_BASE, LPUART7_BASE, LPUART8_BASE, LPUART9_BASE, LPUART10_BASE, LPUART11_BASE, LPUART12_BASE }
/** Array initializer of LPUART peripheral base pointers */
#define LPUART_BASE_PTRS                         { (LPUART_Type *)0u, LPUART1, LPUART2, LPUART3, LPUART4, LPUART5, LPUART6, LPUART7, LPUART8, LPUART9, LPUART10, LPUART11, LPUART12 }
/** Interrupt vectors for the LPUART peripheral type */
#define LPUART_RX_TX_IRQS                        { NotAvail_IRQn, LPUART1_IRQn, LPUART2_IRQn, LPUART3_IRQn, LPUART4_IRQn, LPUART5_IRQn, LPUART6_IRQn, LPUART7_IRQn, LPUART8_IRQn, LPUART9_IRQn, LPUART10_IRQn, LPUART11_IRQn, LPUART12_IRQn }

/* MCM - Peripheral instance base addresses */
/** Peripheral CM7_MCM base address */
#define CM7_MCM_BASE                             (0xE0080000u)
/** Peripheral CM7_MCM base pointer */
#define CM7_MCM                                  ((MCM_Type *)CM7_MCM_BASE)
/** Array initializer of MCM peripheral base addresses */
#define MCM_BASE_ADDRS                           { CM7_MCM_BASE }
/** Array initializer of MCM peripheral base pointers */
#define MCM_BASE_PTRS                            { CM7_MCM }

/* MECC - Peripheral instance base addresses */
/** Peripheral MECC1 base address */
#define MECC1_BASE                               (0x40014000u)
/** Peripheral MECC1 base pointer */
#define MECC1                                    ((MECC_Type *)MECC1_BASE)
/** Peripheral MECC2 base address */
#define MECC2_BASE                               (0x40018000u)
/** Peripheral MECC2 base pointer */
#define MECC2                                    ((MECC_Type *)MECC2_BASE)
/** Array initializer of MECC peripheral base addresses */
#define MECC_BASE_ADDRS                          { 0u, MECC1_BASE, MECC2_BASE }
/** Array initializer of MECC peripheral base pointers */
#define MECC_BASE_PTRS                           { (MECC_Type *)0u, MECC1, MECC2 }

/* MIPI_CSI2RX - Peripheral instance base addresses */
/** Peripheral MIPI_CSI2RX base address */
#define MIPI_CSI2RX_BASE                         (0x40810000u)
/** Peripheral MIPI_CSI2RX base pointer */
#define MIPI_CSI2RX                              ((MIPI_CSI2RX_Type *)MIPI_CSI2RX_BASE)
/** Array initializer of MIPI_CSI2RX peripheral base addresses */
#define MIPI_CSI2RX_BASE_ADDRS                   { MIPI_CSI2RX_BASE }
/** Array initializer of MIPI_CSI2RX peripheral base pointers */
#define MIPI_CSI2RX_BASE_PTRS                    { MIPI_CSI2RX }

/* MU - Peripheral instance base addresses */
/** Peripheral MUA base address */
#define MUA_BASE                                 (0x40C48000u)
/** Peripheral MUA base pointer */
#define MUA                                      ((MU_Type *)MUA_BASE)
/** Array initializer of MU peripheral base addresses */
#define MU_BASE_ADDRS                            { MUA_BASE }
/** Array initializer of MU peripheral base pointers */
#define MU_BASE_PTRS                             { MUA }
/** Interrupt vectors for the MU peripheral type */
#define MU_IRQS                                  { MUA_IRQn }

/* OCOTP - Peripheral instance base addresses */
/** Peripheral OCOTP base address */
#define OCOTP_BASE                               (0x40CAC000u)
/** Peripheral OCOTP base pointer */
#define OCOTP                                    ((OCOTP_Type *)OCOTP_BASE)
/** Array initializer of OCOTP peripheral base addresses */
#define OCOTP_BASE_ADDRS                         { OCOTP_BASE }
/** Array initializer of OCOTP peripheral base pointers */
#define OCOTP_BASE_PTRS                          { OCOTP }

/* OSC_RC_400M - Peripheral instance base addresses */
/** Peripheral OSC_RC_400M base address */
#define OSC_RC_400M_BASE                         (0u)
/** Peripheral OSC_RC_400M base pointer */
#define OSC_RC_400M                              ((OSC_RC_400M_Type *)OSC_RC_400M_BASE)
/** Array initializer of OSC_RC_400M peripheral base addresses */
#define OSC_RC_400M_BASE_ADDRS                   { OSC_RC_400M_BASE }
/** Array initializer of OSC_RC_400M peripheral base pointers */
#define OSC_RC_400M_BASE_PTRS                    { OSC_RC_400M }

/* OTFAD - Peripheral instance base addresses */
/** Peripheral OTFAD1 base address */
#define OTFAD1_BASE                              (0x400CC000u)
/** Peripheral OTFAD1 base pointer */
#define OTFAD1                                   ((OTFAD_Type *)OTFAD1_BASE)
/** Peripheral OTFAD2 base address */
#define OTFAD2_BASE                              (0x400D0000u)
/** Peripheral OTFAD2 base pointer */
#define OTFAD2                                   ((OTFAD_Type *)OTFAD2_BASE)
/** Array initializer of OTFAD peripheral base addresses */
#define OTFAD_BASE_ADDRS                         { 0u, OTFAD1_BASE, OTFAD2_BASE }
/** Array initializer of OTFAD peripheral base pointers */
#define OTFAD_BASE_PTRS                          { (OTFAD_Type *)0u, OTFAD1, OTFAD2 }

/* PDM - Peripheral instance base addresses */
/** Peripheral PDM base address */
#define PDM_BASE                                 (0x40C20000u)
/** Peripheral PDM base pointer */
#define PDM                                      ((PDM_Type *)PDM_BASE)
/** Array initializer of PDM peripheral base addresses */
#define PDM_BASE_ADDRS                           { PDM_BASE }
/** Array initializer of PDM peripheral base pointers */
#define PDM_BASE_PTRS                            { PDM }

/* PGMC_BPC - Peripheral instance base addresses */
/** Peripheral PGMC_BPC0 base address */
#define PGMC_BPC0_BASE                           (0x40C88000u)
/** Peripheral PGMC_BPC0 base pointer */
#define PGMC_BPC0                                ((PGMC_BPC_Type *)PGMC_BPC0_BASE)
/** Peripheral PGMC_BPC1 base address */
#define PGMC_BPC1_BASE                           (0x40C88200u)
/** Peripheral PGMC_BPC1 base pointer */
#define PGMC_BPC1                                ((PGMC_BPC_Type *)PGMC_BPC1_BASE)
/** Peripheral PGMC_BPC2 base address */
#define PGMC_BPC2_BASE                           (0x40C88400u)
/** Peripheral PGMC_BPC2 base pointer */
#define PGMC_BPC2                                ((PGMC_BPC_Type *)PGMC_BPC2_BASE)
/** Peripheral PGMC_BPC3 base address */
#define PGMC_BPC3_BASE                           (0x40C88600u)
/** Peripheral PGMC_BPC3 base pointer */
#define PGMC_BPC3                                ((PGMC_BPC_Type *)PGMC_BPC3_BASE)
/** Peripheral PGMC_BPC4 base address */
#define PGMC_BPC4_BASE                           (0x40C88800u)
/** Peripheral PGMC_BPC4 base pointer */
#define PGMC_BPC4                                ((PGMC_BPC_Type *)PGMC_BPC4_BASE)
/** Peripheral PGMC_BPC5 base address */
#define PGMC_BPC5_BASE                           (0x40C88A00u)
/** Peripheral PGMC_BPC5 base pointer */
#define PGMC_BPC5                                ((PGMC_BPC_Type *)PGMC_BPC5_BASE)
/** Peripheral PGMC_BPC6 base address */
#define PGMC_BPC6_BASE                           (0x40C88C00u)
/** Peripheral PGMC_BPC6 base pointer */
#define PGMC_BPC6                                ((PGMC_BPC_Type *)PGMC_BPC6_BASE)
/** Peripheral PGMC_BPC7 base address */
#define PGMC_BPC7_BASE                           (0x40C88E00u)
/** Peripheral PGMC_BPC7 base pointer */
#define PGMC_BPC7                                ((PGMC_BPC_Type *)PGMC_BPC7_BASE)
/** Array initializer of PGMC_BPC peripheral base addresses */
#define PGMC_BPC_BASE_ADDRS                      { PGMC_BPC0_BASE, PGMC_BPC1_BASE, PGMC_BPC2_BASE, PGMC_BPC3_BASE, PGMC_BPC4_BASE, PGMC_BPC5_BASE, PGMC_BPC6_BASE, PGMC_BPC7_BASE }
/** Array initializer of PGMC_BPC peripheral base pointers */
#define PGMC_BPC_BASE_PTRS                       { PGMC_BPC0, PGMC_BPC1, PGMC_BPC2, PGMC_BPC3, PGMC_BPC4, PGMC_BPC5, PGMC_BPC6, PGMC_BPC7 }

/* PGMC_CPC - Peripheral instance base addresses */
/** Peripheral PGMC_CPC0 base address */
#define PGMC_CPC0_BASE                           (0x40C89000u)
/** Peripheral PGMC_CPC0 base pointer */
#define PGMC_CPC0                                ((PGMC_CPC_Type *)PGMC_CPC0_BASE)
/** Peripheral PGMC_CPC1 base address */
#define PGMC_CPC1_BASE                           (0x40C89400u)
/** Peripheral PGMC_CPC1 base pointer */
#define PGMC_CPC1                                ((PGMC_CPC_Type *)PGMC_CPC1_BASE)
/** Array initializer of PGMC_CPC peripheral base addresses */
#define PGMC_CPC_BASE_ADDRS                      { PGMC_CPC0_BASE, PGMC_CPC1_BASE }
/** Array initializer of PGMC_CPC peripheral base pointers */
#define PGMC_CPC_BASE_PTRS                       { PGMC_CPC0, PGMC_CPC1 }

/* PGMC_MIF - Peripheral instance base addresses */
/** Peripheral PGMC_CPC0_MIF0 base address */
#define PGMC_CPC0_MIF0_BASE                      (0x40C89100u)
/** Peripheral PGMC_CPC0_MIF0 base pointer */
#define PGMC_CPC0_MIF0                           ((PGMC_MIF_Type *)PGMC_CPC0_MIF0_BASE)
/** Peripheral PGMC_CPC0_MIF1 base address */
#define PGMC_CPC0_MIF1_BASE                      (0x40C89200u)
/** Peripheral PGMC_CPC0_MIF1 base pointer */
#define PGMC_CPC0_MIF1                           ((PGMC_MIF_Type *)PGMC_CPC0_MIF1_BASE)
/** Peripheral PGMC_CPC1_MIF0 base address */
#define PGMC_CPC1_MIF0_BASE                      (0x40C89500u)
/** Peripheral PGMC_CPC1_MIF0 base pointer */
#define PGMC_CPC1_MIF0                           ((PGMC_MIF_Type *)PGMC_CPC1_MIF0_BASE)
/** Peripheral PGMC_CPC1_MIF1 base address */
#define PGMC_CPC1_MIF1_BASE                      (0x40C89600u)
/** Peripheral PGMC_CPC1_MIF1 base pointer */
#define PGMC_CPC1_MIF1                           ((PGMC_MIF_Type *)PGMC_CPC1_MIF1_BASE)
/** Array initializer of PGMC_MIF peripheral base addresses */
#define PGMC_MIF_BASE_ADDRS                      { PGMC_CPC0_MIF0_BASE, PGMC_CPC0_MIF1_BASE, PGMC_CPC1_MIF0_BASE, PGMC_CPC1_MIF1_BASE }
/** Array initializer of PGMC_MIF peripheral base pointers */
#define PGMC_MIF_BASE_PTRS                       { PGMC_CPC0_MIF0, PGMC_CPC0_MIF1, PGMC_CPC1_MIF0, PGMC_CPC1_MIF1 }

/* PGMC_PPC - Peripheral instance base addresses */
/** Peripheral PGMC_PPC0 base address */
#define PGMC_PPC0_BASE                           (0x40C8B000u)
/** Peripheral PGMC_PPC0 base pointer */
#define PGMC_PPC0                                ((PGMC_PPC_Type *)PGMC_PPC0_BASE)
/** Array initializer of PGMC_PPC peripheral base addresses */
#define PGMC_PPC_BASE_ADDRS                      { PGMC_PPC0_BASE }
/** Array initializer of PGMC_PPC peripheral base pointers */
#define PGMC_PPC_BASE_PTRS                       { PGMC_PPC0 }

/* PHY_LDO - Peripheral instance base addresses */
/** Peripheral PHY_LDO base address */
#define PHY_LDO_BASE                             (0u)
/** Peripheral PHY_LDO base pointer */
#define PHY_LDO                                  ((PHY_LDO_Type *)PHY_LDO_BASE)
/** Array initializer of PHY_LDO peripheral base addresses */
#define PHY_LDO_BASE_ADDRS                       { PHY_LDO_BASE }
/** Array initializer of PHY_LDO peripheral base pointers */
#define PHY_LDO_BASE_PTRS                        { PHY_LDO }

/* PIT - Peripheral instance base addresses */
/** Peripheral PIT1 base address */
#define PIT1_BASE                                (0x400D8000u)
/** Peripheral PIT1 base pointer */
#define PIT1                                     ((PIT_Type *)PIT1_BASE)
/** Peripheral PIT2 base address */
#define PIT2_BASE                                (0x40CB0000u)
/** Peripheral PIT2 base pointer */
#define PIT2                                     ((PIT_Type *)PIT2_BASE)
/** Array initializer of PIT peripheral base addresses */
#define PIT_BASE_ADDRS                           { 0u, PIT1_BASE, PIT2_BASE }
/** Array initializer of PIT peripheral base pointers */
#define PIT_BASE_PTRS                            { (PIT_Type *)0u, PIT1, PIT2 }
/** Interrupt vectors for the PIT peripheral type */
#define PIT_IRQS                                 { { NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn }, { PIT1_IRQn, PIT1_IRQn, PIT1_IRQn, PIT1_IRQn }, { PIT2_IRQn, PIT2_IRQn, PIT2_IRQn, PIT2_IRQn } }

/* PUF - Peripheral instance base addresses */
/** Peripheral KEY_MANAGER__PUF base address */
#define KEY_MANAGER__PUF_BASE                    (0x40C82000u)
/** Peripheral KEY_MANAGER__PUF base pointer */
#define KEY_MANAGER__PUF                         ((PUF_Type *)KEY_MANAGER__PUF_BASE)
/** Array initializer of PUF peripheral base addresses */
#define PUF_BASE_ADDRS                           { KEY_MANAGER__PUF_BASE }
/** Array initializer of PUF peripheral base pointers */
#define PUF_BASE_PTRS                            { KEY_MANAGER__PUF }

/* PWM - Peripheral instance base addresses */
/** Peripheral PWM1 base address */
#define PWM1_BASE                                (0x4018C000u)
/** Peripheral PWM1 base pointer */
#define PWM1                                     ((PWM_Type *)PWM1_BASE)
/** Peripheral PWM2 base address */
#define PWM2_BASE                                (0x40190000u)
/** Peripheral PWM2 base pointer */
#define PWM2                                     ((PWM_Type *)PWM2_BASE)
/** Peripheral PWM3 base address */
#define PWM3_BASE                                (0x40194000u)
/** Peripheral PWM3 base pointer */
#define PWM3                                     ((PWM_Type *)PWM3_BASE)
/** Peripheral PWM4 base address */
#define PWM4_BASE                                (0x40198000u)
/** Peripheral PWM4 base pointer */
#define PWM4                                     ((PWM_Type *)PWM4_BASE)
/** Array initializer of PWM peripheral base addresses */
#define PWM_BASE_ADDRS                           { 0u, PWM1_BASE, PWM2_BASE, PWM3_BASE, PWM4_BASE }
/** Array initializer of PWM peripheral base pointers */
#define PWM_BASE_PTRS                            { (PWM_Type *)0u, PWM1, PWM2, PWM3, PWM4 }
/** Interrupt vectors for the PWM peripheral type */
#define PWM_CMP_IRQS                             { { NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn }, { PWM1_0_IRQn, PWM1_1_IRQn, PWM1_2_IRQn, PWM1_3_IRQn }, { PWM2_0_IRQn, PWM2_1_IRQn, PWM2_2_IRQn, PWM2_3_IRQn }, { PWM3_0_IRQn, PWM3_1_IRQn, PWM3_2_IRQn, PWM3_3_IRQn }, { PWM4_0_IRQn, PWM4_1_IRQn, PWM4_2_IRQn, PWM4_3_IRQn } }
#define PWM_RELOAD_IRQS                          { { NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn }, { PWM1_0_IRQn, PWM1_1_IRQn, PWM1_2_IRQn, PWM1_3_IRQn }, { PWM2_0_IRQn, PWM2_1_IRQn, PWM2_2_IRQn, PWM2_3_IRQn }, { PWM3_0_IRQn, PWM3_1_IRQn, PWM3_2_IRQn, PWM3_3_IRQn }, { PWM4_0_IRQn, PWM4_1_IRQn, PWM4_2_IRQn, PWM4_3_IRQn } }
#define PWM_CAPTURE_IRQS                         { { NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn }, { PWM1_0_IRQn, PWM1_1_IRQn, PWM1_2_IRQn, PWM1_3_IRQn }, { PWM2_0_IRQn, PWM2_1_IRQn, PWM2_2_IRQn, PWM2_3_IRQn }, { PWM3_0_IRQn, PWM3_1_IRQn, PWM3_2_IRQn, PWM3_3_IRQn }, { PWM4_0_IRQn, PWM4_1_IRQn, PWM4_2_IRQn, PWM4_3_IRQn } }
#define PWM_FAULT_IRQS                           { NotAvail_IRQn, PWM1_FAULT_IRQn, PWM2_FAULT_IRQn, PWM3_FAULT_IRQn, PWM4_FAULT_IRQn }
#define PWM_RELOAD_ERROR_IRQS                    { NotAvail_IRQn, PWM1_FAULT_IRQn, PWM2_FAULT_IRQn, PWM3_FAULT_IRQn, PWM4_FAULT_IRQn }

/* RDC - Peripheral instance base addresses */
/** Peripheral RDC base address */
#define RDC_BASE                                 (0x40C78000u)
/** Peripheral RDC base pointer */
#define RDC                                      ((RDC_Type *)RDC_BASE)
/** Array initializer of RDC peripheral base addresses */
#define RDC_BASE_ADDRS                           { RDC_BASE }
/** Array initializer of RDC peripheral base pointers */
#define RDC_BASE_PTRS                            { RDC }
/** Interrupt vectors for the RDC peripheral type */
#define RDC_IRQS                                 { RDC_IRQn }

/* RDC_SEMAPHORE - Peripheral instance base addresses */
/** Peripheral RDC_SEMAPHORE1 base address */
#define RDC_SEMAPHORE1_BASE                      (0x40C44000u)
/** Peripheral RDC_SEMAPHORE1 base pointer */
#define RDC_SEMAPHORE1                           ((RDC_SEMAPHORE_Type *)RDC_SEMAPHORE1_BASE)
/** Peripheral RDC_SEMAPHORE2 base address */
#define RDC_SEMAPHORE2_BASE                      (0x40CCC000u)
/** Peripheral RDC_SEMAPHORE2 base pointer */
#define RDC_SEMAPHORE2                           ((RDC_SEMAPHORE_Type *)RDC_SEMAPHORE2_BASE)
/** Array initializer of RDC_SEMAPHORE peripheral base addresses */
#define RDC_SEMAPHORE_BASE_ADDRS                 { RDC_SEMAPHORE1_BASE, RDC_SEMAPHORE2_BASE }
/** Array initializer of RDC_SEMAPHORE peripheral base pointers */
#define RDC_SEMAPHORE_BASE_PTRS                  { RDC_SEMAPHORE1, RDC_SEMAPHORE2 }

/* RTWDOG - Peripheral instance base addresses */
/** Peripheral RTWDOG3 base address */
#define RTWDOG3_BASE                             (0x40038000u)
/** Peripheral RTWDOG3 base pointer */
#define RTWDOG3                                  ((RTWDOG_Type *)RTWDOG3_BASE)
/** Peripheral RTWDOG4 base address */
#define RTWDOG4_BASE                             (0x40C10000u)
/** Peripheral RTWDOG4 base pointer */
#define RTWDOG4                                  ((RTWDOG_Type *)RTWDOG4_BASE)
/** Array initializer of RTWDOG peripheral base addresses */
#define RTWDOG_BASE_ADDRS                        { 0u, 0u, 0u, RTWDOG3_BASE, RTWDOG4_BASE }
/** Array initializer of RTWDOG peripheral base pointers */
#define RTWDOG_BASE_PTRS                         { (RTWDOG_Type *)0u, (RTWDOG_Type *)0u, (RTWDOG_Type *)0u, RTWDOG3, RTWDOG4 }
/** Interrupt vectors for the RTWDOG peripheral type */
#define RTWDOG_IRQS                              { NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, RTWDOG3_IRQn, NotAvail_IRQn }

/* SEMA4 - Peripheral instance base addresses */
/** Peripheral SEMA4 base address */
#define SEMA4_BASE                               (0x40CC8000u)
/** Peripheral SEMA4 base pointer */
#define SEMA4                                    ((SEMA4_Type *)SEMA4_BASE)
/** Array initializer of SEMA4 peripheral base addresses */
#define SEMA4_BASE_ADDRS                         { SEMA4_BASE }
/** Array initializer of SEMA4 peripheral base pointers */
#define SEMA4_BASE_PTRS                          { SEMA4 }

/* SEMC - Peripheral instance base addresses */
/** Peripheral SEMC base address */
#define SEMC_BASE                                (0x400D4000u)
/** Peripheral SEMC base pointer */
#define SEMC                                     ((SEMC_Type *)SEMC_BASE)
/** Array initializer of SEMC peripheral base addresses */
#define SEMC_BASE_ADDRS                          { SEMC_BASE }
/** Array initializer of SEMC peripheral base pointers */
#define SEMC_BASE_PTRS                           { SEMC }
/** Interrupt vectors for the SEMC peripheral type */
#define SEMC_IRQS                                { SEMC_IRQn }

/* SNVS - Peripheral instance base addresses */
/** Peripheral SNVS base address */
#define SNVS_BASE                                (0x40C90000u)
/** Peripheral SNVS base pointer */
#define SNVS                                     ((SNVS_Type *)SNVS_BASE)
/** Array initializer of SNVS peripheral base addresses */
#define SNVS_BASE_ADDRS                          { SNVS_BASE }
/** Array initializer of SNVS peripheral base pointers */
#define SNVS_BASE_PTRS                           { SNVS }
/** Interrupt vectors for the SNVS peripheral type */
#define SNVS_IRQS                                { SNVS_PULSE_EVENT_IRQn }
#define SNVS_CONSOLIDATED_IRQS                   { SNVS_HP_NON_TZ_IRQn }
#define SNVS_SECURITY_IRQS                       { SNVS_HP_TZ_IRQn }

/* SPDIF - Peripheral instance base addresses */
/** Peripheral SPDIF base address */
#define SPDIF_BASE                               (0x40400000u)
/** Peripheral SPDIF base pointer */
#define SPDIF                                    ((SPDIF_Type *)SPDIF_BASE)
/** Array initializer of SPDIF peripheral base addresses */
#define SPDIF_BASE_ADDRS                         { SPDIF_BASE }
/** Array initializer of SPDIF peripheral base pointers */
#define SPDIF_BASE_PTRS                          { SPDIF }
/** Interrupt vectors for the SPDIF peripheral type */
#define SPDIF_IRQS                               { SPDIF_IRQn }

/* SRAM - Peripheral instance base addresses */
/** Peripheral SRAM base address */
#define SRAM_BASE                                (0x40C9C000u)
/** Peripheral SRAM base pointer */
#define SRAM                                     ((SRAM_Type *)SRAM_BASE)
/** Array initializer of SRAM peripheral base addresses */
#define SRAM_BASE_ADDRS                          { SRAM_BASE }
/** Array initializer of SRAM peripheral base pointers */
#define SRAM_BASE_PTRS                           { SRAM }

/* SRC - Peripheral instance base addresses */
/** Peripheral SRC base address */
#define SRC_BASE                                 (0x40C04000u)
/** Peripheral SRC base pointer */
#define SRC                                      ((SRC_Type *)SRC_BASE)
/** Array initializer of SRC peripheral base addresses */
#define SRC_BASE_ADDRS                           { SRC_BASE }
/** Array initializer of SRC peripheral base pointers */
#define SRC_BASE_PTRS                            { SRC }

/* SSARC_HP - Peripheral instance base addresses */
/** Peripheral SSARC_HP base address */
#define SSARC_HP_BASE                            (0x40CB4000u)
/** Peripheral SSARC_HP base pointer */
#define SSARC_HP                                 ((SSARC_HP_Type *)SSARC_HP_BASE)
/** Array initializer of SSARC_HP peripheral base addresses */
#define SSARC_HP_BASE_ADDRS                      { SSARC_HP_BASE }
/** Array initializer of SSARC_HP peripheral base pointers */
#define SSARC_HP_BASE_PTRS                       { SSARC_HP }

/* SSARC_LP - Peripheral instance base addresses */
/** Peripheral SSARC_LP base address */
#define SSARC_LP_BASE                            (0x40CB8000u)
/** Peripheral SSARC_LP base pointer */
#define SSARC_LP                                 ((SSARC_LP_Type *)SSARC_LP_BASE)
/** Array initializer of SSARC_LP peripheral base addresses */
#define SSARC_LP_BASE_ADDRS                      { SSARC_LP_BASE }
/** Array initializer of SSARC_LP peripheral base pointers */
#define SSARC_LP_BASE_PTRS                       { SSARC_LP }

/* TMPSNS - Peripheral instance base addresses */
/** Peripheral TMPSNS base address */
#define TMPSNS_BASE                              (0u)
/** Peripheral TMPSNS base pointer */
#define TMPSNS                                   ((TMPSNS_Type *)TMPSNS_BASE)
/** Array initializer of TMPSNS peripheral base addresses */
#define TMPSNS_BASE_ADDRS                        { TMPSNS_BASE }
/** Array initializer of TMPSNS peripheral base pointers */
#define TMPSNS_BASE_PTRS                         { TMPSNS }

/* TMR - Peripheral instance base addresses */
/** Peripheral TMR1 base address */
#define TMR1_BASE                                (0x4015C000u)
/** Peripheral TMR1 base pointer */
#define TMR1                                     ((TMR_Type *)TMR1_BASE)
/** Peripheral TMR2 base address */
#define TMR2_BASE                                (0x40160000u)
/** Peripheral TMR2 base pointer */
#define TMR2                                     ((TMR_Type *)TMR2_BASE)
/** Peripheral TMR3 base address */
#define TMR3_BASE                                (0x40164000u)
/** Peripheral TMR3 base pointer */
#define TMR3                                     ((TMR_Type *)TMR3_BASE)
/** Peripheral TMR4 base address */
#define TMR4_BASE                                (0x40168000u)
/** Peripheral TMR4 base pointer */
#define TMR4                                     ((TMR_Type *)TMR4_BASE)
/** Array initializer of TMR peripheral base addresses */
#define TMR_BASE_ADDRS                           { 0u, TMR1_BASE, TMR2_BASE, TMR3_BASE, TMR4_BASE }
/** Array initializer of TMR peripheral base pointers */
#define TMR_BASE_PTRS                            { (TMR_Type *)0u, TMR1, TMR2, TMR3, TMR4 }
/** Interrupt vectors for the TMR peripheral type */
#define TMR_IRQS                                 { NotAvail_IRQn, TMR1_IRQn, TMR2_IRQn, TMR3_IRQn, TMR4_IRQn }

/* USB - Peripheral instance base addresses */
/** Peripheral USB_OTG1 base address */
#define USB_OTG1_BASE                            (0x40430000u)
/** Peripheral USB_OTG1 base pointer */
#define USB_OTG1                                 ((USB_Type *)USB_OTG1_BASE)
/** Peripheral USB_OTG2 base address */
#define USB_OTG2_BASE                            (0x4042C000u)
/** Peripheral USB_OTG2 base pointer */
#define USB_OTG2                                 ((USB_Type *)USB_OTG2_BASE)
/** Array initializer of USB peripheral base addresses */
#define USB_BASE_ADDRS                           { 0u, USB_OTG1_BASE, USB_OTG2_BASE }
/** Array initializer of USB peripheral base pointers */
#define USB_BASE_PTRS                            { (USB_Type *)0u, USB_OTG1, USB_OTG2 }
/** Interrupt vectors for the USB peripheral type */
#define USB_IRQS                                 { NotAvail_IRQn, USB_OTG1_IRQn, USB_OTG2_IRQn }

/* USBHSDCD - Peripheral instance base addresses */
/** Peripheral USBHSDCD1 base address */
#define USBHSDCD1_BASE                           (0x40434800u)
/** Peripheral USBHSDCD1 base pointer */
#define USBHSDCD1                                ((USBHSDCD_Type *)USBHSDCD1_BASE)
/** Peripheral USBHSDCD2 base address */
#define USBHSDCD2_BASE                           (0x40438800u)
/** Peripheral USBHSDCD2 base pointer */
#define USBHSDCD2                                ((USBHSDCD_Type *)USBHSDCD2_BASE)
/** Array initializer of USBHSDCD peripheral base addresses */
#define USBHSDCD_BASE_ADDRS                      { 0u, USBHSDCD1_BASE, USBHSDCD2_BASE }
/** Array initializer of USBHSDCD peripheral base pointers */
#define USBHSDCD_BASE_PTRS                       { (USBHSDCD_Type *)0u, USBHSDCD1, USBHSDCD2 }
/* Backward compatibility */
#define USBHSDCD_STACK_BASE_ADDRS                { USBHSDCD1_BASE, USBHSDCD2_BASE }


/* USBNC - Peripheral instance base addresses */
/** Peripheral USBNC_OTG1 base address */
#define USBNC_OTG1_BASE                          (0x40430200u)
/** Peripheral USBNC_OTG1 base pointer */
#define USBNC_OTG1                               ((USBNC_Type *)USBNC_OTG1_BASE)
/** Peripheral USBNC_OTG2 base address */
#define USBNC_OTG2_BASE                          (0x4042C200u)
/** Peripheral USBNC_OTG2 base pointer */
#define USBNC_OTG2                               ((USBNC_Type *)USBNC_OTG2_BASE)
/** Array initializer of USBNC peripheral base addresses */
#define USBNC_BASE_ADDRS                         { 0u, USBNC_OTG1_BASE, USBNC_OTG2_BASE }
/** Array initializer of USBNC peripheral base pointers */
#define USBNC_BASE_PTRS                          { (USBNC_Type *)0u, USBNC_OTG1, USBNC_OTG2 }
/* Backward compatibility */
#define USB_OTGn_CTRL     CTRL1
#define USBNC_USB_OTGn_CTRL_OVER_CUR_DIS_MASK     USBNC_CTRL1_OVER_CUR_DIS_MASK
#define USBNC_USB_OTGn_CTRL_OVER_CUR_DIS_SHIFT     USBNC_CTRL1_OVER_CUR_DIS_SHIFT
#define USBNC_USB_OTGn_CTRL_OVER_CUR_DIS(x)     USBNC_CTRL1_OVER_CUR_DIS(x)
#define USBNC_USB_OTGn_CTRL_OVER_CUR_POL_MASK     USBNC_CTRL1_OVER_CUR_POL_MASK
#define USBNC_USB_OTGn_CTRL_OVER_CUR_POL_SHIFT     USBNC_CTRL1_OVER_CUR_POL_SHIFT
#define USBNC_USB_OTGn_CTRL_OVER_CUR_POL(x)     USBNC_CTRL1_OVER_CUR_POL(x)
#define USBNC_USB_OTGn_CTRL_PWR_POL_MASK     USBNC_CTRL1_PWR_POL_MASK
#define USBNC_USB_OTGn_CTRL_PWR_POL_SHIFT     USBNC_CTRL1_PWR_POL_SHIFT
#define USBNC_USB_OTGn_CTRL_PWR_POL(x)     USBNC_CTRL1_PWR_POL(x)
#define USBNC_USB_OTGn_CTRL_WIE_MASK     USBNC_CTRL1_WIE_MASK
#define USBNC_USB_OTGn_CTRL_WIE_SHIFT     USBNC_CTRL1_WIE_SHIFT
#define USBNC_USB_OTGn_CTRL_WIE(x)     USBNC_CTRL1_WIE(x)
#define USBNC_USB_OTGn_CTRL_WKUP_SW_EN_MASK     USBNC_CTRL1_WKUP_SW_EN_MASK
#define USBNC_USB_OTGn_CTRL_WKUP_SW_EN_SHIFT     USBNC_CTRL1_WKUP_SW_EN_SHIFT
#define USBNC_USB_OTGn_CTRL_WKUP_SW_EN(x)     USBNC_CTRL1_WKUP_SW_EN(x)
#define USBNC_USB_OTGn_CTRL_WKUP_SW_MASK     USBNC_CTRL1_WKUP_SW_MASK
#define USBNC_USB_OTGn_CTRL_WKUP_SW_SHIFT     USBNC_CTRL1_WKUP_SW_SHIFT
#define USBNC_USB_OTGn_CTRL_WKUP_SW(x)     USBNC_CTRL1_WKUP_SW(x)
#define USBNC_USB_OTGn_CTRL_WKUP_ID_EN_MASK     USBNC_CTRL1_WKUP_ID_EN_MASK
#define USBNC_USB_OTGn_CTRL_WKUP_ID_EN_SHIFT     USBNC_CTRL1_WKUP_ID_EN_SHIFT
#define USBNC_USB_OTGn_CTRL_WKUP_ID_EN(x)     USBNC_CTRL1_WKUP_ID_EN(x)
#define USBNC_USB_OTGn_CTRL_WKUP_VBUS_EN_MASK     USBNC_CTRL1_WKUP_VBUS_EN_MASK
#define USBNC_USB_OTGn_CTRL_WKUP_VBUS_EN_SHIFT     USBNC_CTRL1_WKUP_VBUS_EN_SHIFT
#define USBNC_USB_OTGn_CTRL_WKUP_VBUS_EN(x)     USBNC_CTRL1_WKUP_VBUS_EN(x)
#define USBNC_USB_OTGn_CTRL_WKUP_DPDM_EN_MASK     USBNC_CTRL1_WKUP_DPDM_EN_MASK
#define USBNC_USB_OTGn_CTRL_WKUP_DPDM_EN_SHIFT     USBNC_CTRL1_WKUP_DPDM_EN_SHIFT
#define USBNC_USB_OTGn_CTRL_WKUP_DPDM_EN(x)     USBNC_CTRL1_WKUP_DPDM_EN(x)
#define USBNC_USB_OTGn_CTRL_WIR_MASK     USBNC_CTRL1_WIR_MASK
#define USBNC_USB_OTGn_CTRL_WIR_SHIFT     USBNC_CTRL1_WIR_SHIFT
#define USBNC_USB_OTGn_CTRL_WIR(x)     USBNC_CTRL1_WIR(x)
#define USBNC_STACK_BASE_ADDRS                { USBNC_OTG1_BASE, USBNC_OTG2_BASE }


/* USBPHY - Peripheral instance base addresses */
/** Peripheral USBPHY1 base address */
#define USBPHY1_BASE                             (0x40434000u)
/** Peripheral USBPHY1 base pointer */
#define USBPHY1                                  ((USBPHY_Type *)USBPHY1_BASE)
/** Peripheral USBPHY2 base address */
#define USBPHY2_BASE                             (0x40438000u)
/** Peripheral USBPHY2 base pointer */
#define USBPHY2                                  ((USBPHY_Type *)USBPHY2_BASE)
/** Array initializer of USBPHY peripheral base addresses */
#define USBPHY_BASE_ADDRS                        { 0u, USBPHY1_BASE, USBPHY2_BASE }
/** Array initializer of USBPHY peripheral base pointers */
#define USBPHY_BASE_PTRS                         { (USBPHY_Type *)0u, USBPHY1, USBPHY2 }
/** Interrupt vectors for the USBPHY peripheral type */
#define USBPHY_IRQS                              { NotAvail_IRQn, USBPHY1_IRQn, USBPHY2_IRQn }
/* Backward compatibility */
#define USBPHY_CTRL_ENDEVPLUGINDET_MASK     USBPHY_CTRL_ENDEVPLUGINDETECT_MASK
#define USBPHY_CTRL_ENDEVPLUGINDET_SHIFT    USBPHY_CTRL_ENDEVPLUGINDETECT_SHIFT
#define USBPHY_CTRL_ENDEVPLUGINDET(x)       USBPHY_CTRL_ENDEVPLUGINDETECT(x)
#define USBPHY_TX_TXCAL45DM_MASK            USBPHY_TX_TXCAL45DN_MASK
#define USBPHY_TX_TXCAL45DM_SHIFT           USBPHY_TX_TXCAL45DN_SHIFT
#define USBPHY_TX_TXCAL45DM(x)              USBPHY_TX_TXCAL45DN(x)

#define USBPHY_STACK_BASE_ADDRS             { USBPHY1_BASE, USBPHY2_BASE }


/* USDHC - Peripheral instance base addresses */
/** Peripheral USDHC1 base address */
#define USDHC1_BASE                              (0x40418000u)
/** Peripheral USDHC1 base pointer */
#define USDHC1                                   ((USDHC_Type *)USDHC1_BASE)
/** Peripheral USDHC2 base address */
#define USDHC2_BASE                              (0x4041C000u)
/** Peripheral USDHC2 base pointer */
#define USDHC2                                   ((USDHC_Type *)USDHC2_BASE)
/** Array initializer of USDHC peripheral base addresses */
#define USDHC_BASE_ADDRS                         { 0u, USDHC1_BASE, USDHC2_BASE }
/** Array initializer of USDHC peripheral base pointers */
#define USDHC_BASE_PTRS                          { (USDHC_Type *)0u, USDHC1, USDHC2 }
/** Interrupt vectors for the USDHC peripheral type */
#define USDHC_IRQS                               { NotAvail_IRQn, USDHC1_IRQn, USDHC2_IRQn }

/* VIDEO_MUX - Peripheral instance base addresses */
/** Peripheral VIDEO_MUX base address */
#define VIDEO_MUX_BASE                           (0x40818000u)
/** Peripheral VIDEO_MUX base pointer */
#define VIDEO_MUX                                ((VIDEO_MUX_Type *)VIDEO_MUX_BASE)
/** Array initializer of VIDEO_MUX peripheral base addresses */
#define VIDEO_MUX_BASE_ADDRS                     { VIDEO_MUX_BASE }
/** Array initializer of VIDEO_MUX peripheral base pointers */
#define VIDEO_MUX_BASE_PTRS                      { VIDEO_MUX }

/* VIDEO_PLL - Peripheral instance base addresses */
/** Peripheral VIDEO_PLL base address */
#define VIDEO_PLL_BASE                           (0u)
/** Peripheral VIDEO_PLL base pointer */
#define VIDEO_PLL                                ((VIDEO_PLL_Type *)VIDEO_PLL_BASE)
/** Array initializer of VIDEO_PLL peripheral base addresses */
#define VIDEO_PLL_BASE_ADDRS                     { VIDEO_PLL_BASE }
/** Array initializer of VIDEO_PLL peripheral base pointers */
#define VIDEO_PLL_BASE_PTRS                      { VIDEO_PLL }

/* VMBANDGAP - Peripheral instance base addresses */
/** Peripheral VMBANDGAP base address */
#define VMBANDGAP_BASE                           (0u)
/** Peripheral VMBANDGAP base pointer */
#define VMBANDGAP                                ((VMBANDGAP_Type *)VMBANDGAP_BASE)
/** Array initializer of VMBANDGAP peripheral base addresses */
#define VMBANDGAP_BASE_ADDRS                     { VMBANDGAP_BASE }
/** Array initializer of VMBANDGAP peripheral base pointers */
#define VMBANDGAP_BASE_PTRS                      { VMBANDGAP }

/* WDOG - Peripheral instance base addresses */
/** Peripheral WDOG1 base address */
#define WDOG1_BASE                               (0x40030000u)
/** Peripheral WDOG1 base pointer */
#define WDOG1                                    ((WDOG_Type *)WDOG1_BASE)
/** Peripheral WDOG2 base address */
#define WDOG2_BASE                               (0x40034000u)
/** Peripheral WDOG2 base pointer */
#define WDOG2                                    ((WDOG_Type *)WDOG2_BASE)
/** Array initializer of WDOG peripheral base addresses */
#define WDOG_BASE_ADDRS                          { 0u, WDOG1_BASE, WDOG2_BASE }
/** Array initializer of WDOG peripheral base pointers */
#define WDOG_BASE_PTRS                           { (WDOG_Type *)0u, WDOG1, WDOG2 }
/** Interrupt vectors for the WDOG peripheral type */
#define WDOG_IRQS                                { NotAvail_IRQn, WDOG1_IRQn, WDOG2_IRQn }

/* XBARA - Peripheral instance base addresses */
/** Peripheral XBARA1 base address */
#define XBARA1_BASE                              (0x4003C000u)
/** Peripheral XBARA1 base pointer */
#define XBARA1                                   ((XBARA_Type *)XBARA1_BASE)
/** Array initializer of XBARA peripheral base addresses */
#define XBARA_BASE_ADDRS                         { 0u, XBARA1_BASE }
/** Array initializer of XBARA peripheral base pointers */
#define XBARA_BASE_PTRS                          { (XBARA_Type *)0u, XBARA1 }

/* XBARB - Peripheral instance base addresses */
/** Peripheral XBARB2 base address */
#define XBARB2_BASE                              (0x40040000u)
/** Peripheral XBARB2 base pointer */
#define XBARB2                                   ((XBARB_Type *)XBARB2_BASE)
/** Peripheral XBARB3 base address */
#define XBARB3_BASE                              (0x40044000u)
/** Peripheral XBARB3 base pointer */
#define XBARB3                                   ((XBARB_Type *)XBARB3_BASE)
/** Array initializer of XBARB peripheral base addresses */
#define XBARB_BASE_ADDRS                         { 0u, 0u, XBARB2_BASE, XBARB3_BASE }
/** Array initializer of XBARB peripheral base pointers */
#define XBARB_BASE_PTRS                          { (XBARB_Type *)0u, (XBARB_Type *)0u, XBARB2, XBARB3 }

/* XECC - Peripheral instance base addresses */
/** Peripheral XECC_FLEXSPI1 base address */
#define XECC_FLEXSPI1_BASE                       (0x4001C000u)
/** Peripheral XECC_FLEXSPI1 base pointer */
#define XECC_FLEXSPI1                            ((XECC_Type *)XECC_FLEXSPI1_BASE)
/** Peripheral XECC_FLEXSPI2 base address */
#define XECC_FLEXSPI2_BASE                       (0x40020000u)
/** Peripheral XECC_FLEXSPI2 base pointer */
#define XECC_FLEXSPI2                            ((XECC_Type *)XECC_FLEXSPI2_BASE)
/** Peripheral XECC_SEMC base address */
#define XECC_SEMC_BASE                           (0x40024000u)
/** Peripheral XECC_SEMC base pointer */
#define XECC_SEMC                                ((XECC_Type *)XECC_SEMC_BASE)
/** Array initializer of XECC peripheral base addresses */
#define XECC_BASE_ADDRS                          { 0u, XECC_FLEXSPI1_BASE, XECC_FLEXSPI2_BASE, XECC_SEMC_BASE }
/** Array initializer of XECC peripheral base pointers */
#define XECC_BASE_PTRS                           { (XECC_Type *)0u, XECC_FLEXSPI1, XECC_FLEXSPI2, XECC_SEMC }

/* XRDC2 - Peripheral instance base addresses */
/** Peripheral XRDC2_D0 base address */
#define XRDC2_D0_BASE                            (0x40CE0000u)
/** Peripheral XRDC2_D0 base pointer */
#define XRDC2_D0                                 ((XRDC2_Type *)XRDC2_D0_BASE)
/** Peripheral XRDC2_D1 base address */
#define XRDC2_D1_BASE                            (0x40CD0000u)
/** Peripheral XRDC2_D1 base pointer */
#define XRDC2_D1                                 ((XRDC2_Type *)XRDC2_D1_BASE)
/** Array initializer of XRDC2 peripheral base addresses */
#define XRDC2_BASE_ADDRS                         { XRDC2_D0_BASE, XRDC2_D1_BASE }
/** Array initializer of XRDC2 peripheral base pointers */
#define XRDC2_BASE_PTRS                          { XRDC2_D0, XRDC2_D1 }

/* ----------------------------------------------------------------------------
   -- Macros for use with bit field definitions (xxx_SHIFT, xxx_MASK).
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Bit_Field_Generic_Macros Macros for use with bit field definitions (xxx_SHIFT, xxx_MASK).
 * @{
 */

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang system_header
  #endif
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma system_include
#endif

/**
 * @brief Mask and left-shift a bit field value for use in a register bit range.
 * @param field Name of the register bit field.
 * @param value Value of the bit field.
 * @return Masked and shifted value.
 */
#define NXP_VAL2FLD(field, value)    (((value) << (field ## _SHIFT)) & (field ## _MASK))
/**
 * @brief Mask and right-shift a register value to extract a bit field value.
 * @param field Name of the register bit field.
 * @param value Value of the register.
 * @return Masked and shifted bit field value.
 */
#define NXP_FLD2VAL(field, value)    (((value) & (field ## _MASK)) >> (field ## _SHIFT))

/*!
 * @}
 */ /* end of group Bit_Field_Generic_Macros */


/* ----------------------------------------------------------------------------
   -- SDK Compatibility
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SDK_Compatibility_Symbols SDK Compatibility
 * @{
 */

/* No SDK compatibility issues. */

/*!
 * @}
 */ /* end of group SDK_Compatibility_Symbols */


#endif  /* MIMXRT1171_COMMON_H_ */

