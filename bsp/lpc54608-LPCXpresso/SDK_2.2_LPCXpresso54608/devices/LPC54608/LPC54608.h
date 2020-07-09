/*
** ###################################################################
**     Processors:          LPC54608J512BD208
**                          LPC54608J512ET180
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          MCUXpresso Compiler
**
**     Reference manual:    LPC54S60x/LPC5460x User manual Rev.0.9  7 Nov 2016
**     Version:             rev. 1.1, 2016-11-25
**     Build:               b170214
**
**     Abstract:
**         CMSIS Peripheral Access Layer for LPC54608
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of the copyright holder nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2016-08-12)
**         Initial version.
**     - rev. 1.1 (2016-11-25)
**         Update CANFD and Classic CAN register.
**         Add MAC TIMERSTAMP registers.
**
** ###################################################################
*/

/*!
 * @file LPC54608.h
 * @version 1.1
 * @date 2016-11-25
 * @brief CMSIS Peripheral Access Layer for LPC54608
 *
 * CMSIS Peripheral Access Layer for LPC54608
 */

#ifndef _LPC54608_H_
#define _LPC54608_H_                             /**< Symbol preventing repeated inclusion */

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0100U
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0001U


/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS 73                 /**< Number of interrupts in the Vector table */

typedef enum IRQn {
  /* Auxiliary constants */
  NotAvail_IRQn                = -128,             /**< Not available device specific interrupt */

  /* Core interrupts */
  NonMaskableInt_IRQn          = -14,              /**< Non Maskable Interrupt */
  HardFault_IRQn               = -13,              /**< Cortex-M4 SV Hard Fault Interrupt */
  MemoryManagement_IRQn        = -12,              /**< Cortex-M4 Memory Management Interrupt */
  BusFault_IRQn                = -11,              /**< Cortex-M4 Bus Fault Interrupt */
  UsageFault_IRQn              = -10,              /**< Cortex-M4 Usage Fault Interrupt */
  SVCall_IRQn                  = -5,               /**< Cortex-M4 SV Call Interrupt */
  DebugMonitor_IRQn            = -4,               /**< Cortex-M4 Debug Monitor Interrupt */
  PendSV_IRQn                  = -2,               /**< Cortex-M4 Pend SV Interrupt */
  SysTick_IRQn                 = -1,               /**< Cortex-M4 System Tick Interrupt */

  /* Device specific interrupts */
  WDT_BOD_IRQn                 = 0,                /**< Windowed watchdog timer, Brownout detect */
  DMA0_IRQn                    = 1,                /**< DMA controller */
  GINT0_IRQn                   = 2,                /**< GPIO group 0 */
  GINT1_IRQn                   = 3,                /**< GPIO group 1 */
  PIN_INT0_IRQn                = 4,                /**< Pin interrupt 0 or pattern match engine slice 0 */
  PIN_INT1_IRQn                = 5,                /**< Pin interrupt 1or pattern match engine slice 1 */
  PIN_INT2_IRQn                = 6,                /**< Pin interrupt 2 or pattern match engine slice 2 */
  PIN_INT3_IRQn                = 7,                /**< Pin interrupt 3 or pattern match engine slice 3 */
  UTICK0_IRQn                  = 8,                /**< Micro-tick Timer */
  MRT0_IRQn                    = 9,                /**< Multi-rate timer */
  CTIMER0_IRQn                 = 10,               /**< Standard counter/timer CTIMER0 */
  CTIMER1_IRQn                 = 11,               /**< Standard counter/timer CTIMER1 */
  SCT0_IRQn                    = 12,               /**< SCTimer/PWM */
  CTIMER3_IRQn                 = 13,               /**< Standard counter/timer CTIMER3 */
  FLEXCOMM0_IRQn               = 14,               /**< Flexcomm Interface 0 (USART, SPI, I2C, FLEXCOMM) */
  FLEXCOMM1_IRQn               = 15,               /**< Flexcomm Interface 1 (USART, SPI, I2C, FLEXCOMM) */
  FLEXCOMM2_IRQn               = 16,               /**< Flexcomm Interface 2 (USART, SPI, I2C, FLEXCOMM) */
  FLEXCOMM3_IRQn               = 17,               /**< Flexcomm Interface 3 (USART, SPI, I2C, FLEXCOMM) */
  FLEXCOMM4_IRQn               = 18,               /**< Flexcomm Interface 4 (USART, SPI, I2C, FLEXCOMM) */
  FLEXCOMM5_IRQn               = 19,               /**< Flexcomm Interface 5 (USART, SPI, I2C,, FLEXCOMM) */
  FLEXCOMM6_IRQn               = 20,               /**< Flexcomm Interface 6 (USART, SPI, I2C, I2S,, FLEXCOMM) */
  FLEXCOMM7_IRQn               = 21,               /**< Flexcomm Interface 7 (USART, SPI, I2C, I2S,, FLEXCOMM) */
  ADC0_SEQA_IRQn               = 22,               /**< ADC0 sequence A completion. */
  ADC0_SEQB_IRQn               = 23,               /**< ADC0 sequence B completion. */
  ADC0_THCMP_IRQn              = 24,               /**< ADC0 threshold compare and error. */
  DMIC0_IRQn                   = 25,               /**< Digital microphone and DMIC subsystem */
  HWVAD0_IRQn                  = 26,               /**< Hardware Voice Activity Detector */
  USB0_NEEDCLK_IRQn            = 27,               /**< USB Activity Wake-up Interrupt */
  USB0_IRQn                    = 28,               /**< USB device */
  RTC_IRQn                     = 29,               /**< RTC alarm and wake-up interrupts */
  Reserved46_IRQn              = 30,               /**< Reserved interrupt */
  Reserved47_IRQn              = 31,               /**< Reserved interrupt */
  PIN_INT4_IRQn                = 32,               /**< Pin interrupt 4 or pattern match engine slice 4 int */
  PIN_INT5_IRQn                = 33,               /**< Pin interrupt 5 or pattern match engine slice 5 int */
  PIN_INT6_IRQn                = 34,               /**< Pin interrupt 6 or pattern match engine slice 6 int */
  PIN_INT7_IRQn                = 35,               /**< Pin interrupt 7 or pattern match engine slice 7 int */
  CTIMER2_IRQn                 = 36,               /**< Standard counter/timer CTIMER2 */
  CTIMER4_IRQn                 = 37,               /**< Standard counter/timer CTIMER4 */
  RIT_IRQn                     = 38,               /**< Repetitive Interrupt Timer */
  SPIFI0_IRQn                  = 39,               /**< SPI flash interface */
  FLEXCOMM8_IRQn               = 40,               /**< Flexcomm Interface 8 (USART, SPI, I2C, FLEXCOMM) */
  FLEXCOMM9_IRQn               = 41,               /**< Flexcomm Interface 9 (USART, SPI, I2C, FLEXCOMM) */
  SDIO_IRQn                    = 42,               /**< SD/MMC  */
  CAN0_IRQ0_IRQn               = 43,               /**< CAN0 interrupt0 */
  CAN0_IRQ1_IRQn               = 44,               /**< CAN0 interrupt1 */
  CAN1_IRQ0_IRQn               = 45,               /**< CAN1 interrupt0 */
  CAN1_IRQ1_IRQn               = 46,               /**< CAN1 interrupt1 */
  USB1_IRQn                    = 47,               /**< USB1 interrupt */
  USB1_NEEDCLK_IRQn            = 48,               /**< USB1 activity */
  ETHERNET_IRQn                = 49,               /**< Ethernet */
  ETHERNET_PMT_IRQn            = 50,               /**< Ethernet power management interrupt */
  ETHERNET_MACLP_IRQn          = 51,               /**< Ethernet MAC interrupt */
  EEPROM_IRQn                  = 52,               /**< EEPROM interrupt */
  LCD_IRQn                     = 53,               /**< LCD interrupt */
  SHA_IRQn                     = 54,               /**< SHA interrupt */
  SMARTCARD0_IRQn              = 55,               /**< Smart card 0 interrupt */
  SMARTCARD1_IRQn              = 56                /**< Smart card 1 interrupt */
} IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Cortex M4 Core Configuration
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Cortex_Core_Configuration Cortex M4 Core Configuration
 * @{
 */

#define __MPU_PRESENT                  1         /**< Defines if an MPU is present or not */
#define __NVIC_PRIO_BITS               3         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig         0         /**< Vendor specific implementation of SysTickConfig is defined */
#define __FPU_PRESENT                  1         /**< Defines if an FPU is present or not */

#include "core_cm4.h"                  /* Core Peripheral Access Layer */
#include "system_LPC54608.h"           /* Device specific configuration file */

/*!
 * @}
 */ /* end of group Cortex_Core_Configuration */


/* ----------------------------------------------------------------------------
   -- Mapping Information
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Mapping_Information Mapping Information
 * @{
 */

/** Mapping Information */

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
  #pragma push
  #pragma anon_unions
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- ADC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Peripheral_Access_Layer ADC Peripheral Access Layer
 * @{
 */

/** ADC - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< ADC Control register. Contains the clock divide value, resolution selection, sampling time selection, and mode controls., offset: 0x0 */
  __IO uint32_t INSEL;                             /**< Input Select. Allows selection of the temperature sensor as an alternate input to ADC channel 0., offset: 0x4 */
  __IO uint32_t SEQ_CTRL[2];                       /**< ADC Conversion Sequence-n control register: Controls triggering and channel selection for conversion sequence-n. Also specifies interrupt mode for sequence-n., array offset: 0x8, array step: 0x4 */
  __I  uint32_t SEQ_GDAT[2];                       /**< ADC Sequence-n Global Data register. This register contains the result of the most recent ADC conversion performed under sequence-n., array offset: 0x10, array step: 0x4 */
       uint8_t RESERVED_0[8];
  __I  uint32_t DAT[12];                           /**< ADC Channel 0 Data register. This register contains the result of the most recent conversion completed on channel 0., array offset: 0x20, array step: 0x4 */
  __IO uint32_t THR0_LOW;                          /**< ADC Low Compare Threshold register 0: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 0., offset: 0x50 */
  __IO uint32_t THR1_LOW;                          /**< ADC Low Compare Threshold register 1: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 1., offset: 0x54 */
  __IO uint32_t THR0_HIGH;                         /**< ADC High Compare Threshold register 0: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 0., offset: 0x58 */
  __IO uint32_t THR1_HIGH;                         /**< ADC High Compare Threshold register 1: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 1., offset: 0x5C */
  __IO uint32_t CHAN_THRSEL;                       /**< ADC Channel-Threshold Select register. Specifies which set of threshold compare registers are to be used for each channel, offset: 0x60 */
  __IO uint32_t INTEN;                             /**< ADC Interrupt Enable register. This register contains enable bits that enable the sequence-A, sequence-B, threshold compare and data overrun interrupts to be generated., offset: 0x64 */
  __IO uint32_t FLAGS;                             /**< ADC Flags register. Contains the four interrupt/DMA trigger flags and the individual component overrun and threshold-compare flags. (The overrun bits replicate information stored in the result registers)., offset: 0x68 */
  __IO uint32_t STARTUP;                           /**< ADC Startup register., offset: 0x6C */
  __IO uint32_t CALIB;                             /**< ADC Calibration register., offset: 0x70 */
} ADC_Type;

/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */

/*! @name CTRL - ADC Control register. Contains the clock divide value, resolution selection, sampling time selection, and mode controls. */
#define ADC_CTRL_CLKDIV_MASK                     (0xFFU)
#define ADC_CTRL_CLKDIV_SHIFT                    (0U)
#define ADC_CTRL_CLKDIV(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_CLKDIV_SHIFT)) & ADC_CTRL_CLKDIV_MASK)
#define ADC_CTRL_ASYNMODE_MASK                   (0x100U)
#define ADC_CTRL_ASYNMODE_SHIFT                  (8U)
#define ADC_CTRL_ASYNMODE(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_ASYNMODE_SHIFT)) & ADC_CTRL_ASYNMODE_MASK)
#define ADC_CTRL_RESOL_MASK                      (0x600U)
#define ADC_CTRL_RESOL_SHIFT                     (9U)
#define ADC_CTRL_RESOL(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_RESOL_SHIFT)) & ADC_CTRL_RESOL_MASK)
#define ADC_CTRL_BYPASSCAL_MASK                  (0x800U)
#define ADC_CTRL_BYPASSCAL_SHIFT                 (11U)
#define ADC_CTRL_BYPASSCAL(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_BYPASSCAL_SHIFT)) & ADC_CTRL_BYPASSCAL_MASK)
#define ADC_CTRL_TSAMP_MASK                      (0x7000U)
#define ADC_CTRL_TSAMP_SHIFT                     (12U)
#define ADC_CTRL_TSAMP(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_TSAMP_SHIFT)) & ADC_CTRL_TSAMP_MASK)

/*! @name INSEL - Input Select. Allows selection of the temperature sensor as an alternate input to ADC channel 0. */
#define ADC_INSEL_SEL_MASK                       (0x3U)
#define ADC_INSEL_SEL_SHIFT                      (0U)
#define ADC_INSEL_SEL(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_INSEL_SEL_SHIFT)) & ADC_INSEL_SEL_MASK)

/*! @name SEQ_CTRL - ADC Conversion Sequence-n control register: Controls triggering and channel selection for conversion sequence-n. Also specifies interrupt mode for sequence-n. */
#define ADC_SEQ_CTRL_CHANNELS_MASK               (0xFFFU)
#define ADC_SEQ_CTRL_CHANNELS_SHIFT              (0U)
#define ADC_SEQ_CTRL_CHANNELS(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_CHANNELS_SHIFT)) & ADC_SEQ_CTRL_CHANNELS_MASK)
#define ADC_SEQ_CTRL_TRIGGER_MASK                (0x3F000U)
#define ADC_SEQ_CTRL_TRIGGER_SHIFT               (12U)
#define ADC_SEQ_CTRL_TRIGGER(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_TRIGGER_SHIFT)) & ADC_SEQ_CTRL_TRIGGER_MASK)
#define ADC_SEQ_CTRL_TRIGPOL_MASK                (0x40000U)
#define ADC_SEQ_CTRL_TRIGPOL_SHIFT               (18U)
#define ADC_SEQ_CTRL_TRIGPOL(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_TRIGPOL_SHIFT)) & ADC_SEQ_CTRL_TRIGPOL_MASK)
#define ADC_SEQ_CTRL_SYNCBYPASS_MASK             (0x80000U)
#define ADC_SEQ_CTRL_SYNCBYPASS_SHIFT            (19U)
#define ADC_SEQ_CTRL_SYNCBYPASS(x)               (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_SYNCBYPASS_SHIFT)) & ADC_SEQ_CTRL_SYNCBYPASS_MASK)
#define ADC_SEQ_CTRL_START_MASK                  (0x4000000U)
#define ADC_SEQ_CTRL_START_SHIFT                 (26U)
#define ADC_SEQ_CTRL_START(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_START_SHIFT)) & ADC_SEQ_CTRL_START_MASK)
#define ADC_SEQ_CTRL_BURST_MASK                  (0x8000000U)
#define ADC_SEQ_CTRL_BURST_SHIFT                 (27U)
#define ADC_SEQ_CTRL_BURST(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_BURST_SHIFT)) & ADC_SEQ_CTRL_BURST_MASK)
#define ADC_SEQ_CTRL_SINGLESTEP_MASK             (0x10000000U)
#define ADC_SEQ_CTRL_SINGLESTEP_SHIFT            (28U)
#define ADC_SEQ_CTRL_SINGLESTEP(x)               (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_SINGLESTEP_SHIFT)) & ADC_SEQ_CTRL_SINGLESTEP_MASK)
#define ADC_SEQ_CTRL_LOWPRIO_MASK                (0x20000000U)
#define ADC_SEQ_CTRL_LOWPRIO_SHIFT               (29U)
#define ADC_SEQ_CTRL_LOWPRIO(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_LOWPRIO_SHIFT)) & ADC_SEQ_CTRL_LOWPRIO_MASK)
#define ADC_SEQ_CTRL_MODE_MASK                   (0x40000000U)
#define ADC_SEQ_CTRL_MODE_SHIFT                  (30U)
#define ADC_SEQ_CTRL_MODE(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_MODE_SHIFT)) & ADC_SEQ_CTRL_MODE_MASK)
#define ADC_SEQ_CTRL_SEQ_ENA_MASK                (0x80000000U)
#define ADC_SEQ_CTRL_SEQ_ENA_SHIFT               (31U)
#define ADC_SEQ_CTRL_SEQ_ENA(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_SEQ_ENA_SHIFT)) & ADC_SEQ_CTRL_SEQ_ENA_MASK)

/* The count of ADC_SEQ_CTRL */
#define ADC_SEQ_CTRL_COUNT                       (2U)

/*! @name SEQ_GDAT - ADC Sequence-n Global Data register. This register contains the result of the most recent ADC conversion performed under sequence-n. */
#define ADC_SEQ_GDAT_RESULT_MASK                 (0xFFF0U)
#define ADC_SEQ_GDAT_RESULT_SHIFT                (4U)
#define ADC_SEQ_GDAT_RESULT(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_RESULT_SHIFT)) & ADC_SEQ_GDAT_RESULT_MASK)
#define ADC_SEQ_GDAT_THCMPRANGE_MASK             (0x30000U)
#define ADC_SEQ_GDAT_THCMPRANGE_SHIFT            (16U)
#define ADC_SEQ_GDAT_THCMPRANGE(x)               (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_THCMPRANGE_SHIFT)) & ADC_SEQ_GDAT_THCMPRANGE_MASK)
#define ADC_SEQ_GDAT_THCMPCROSS_MASK             (0xC0000U)
#define ADC_SEQ_GDAT_THCMPCROSS_SHIFT            (18U)
#define ADC_SEQ_GDAT_THCMPCROSS(x)               (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_THCMPCROSS_SHIFT)) & ADC_SEQ_GDAT_THCMPCROSS_MASK)
#define ADC_SEQ_GDAT_CHN_MASK                    (0x3C000000U)
#define ADC_SEQ_GDAT_CHN_SHIFT                   (26U)
#define ADC_SEQ_GDAT_CHN(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_CHN_SHIFT)) & ADC_SEQ_GDAT_CHN_MASK)
#define ADC_SEQ_GDAT_OVERRUN_MASK                (0x40000000U)
#define ADC_SEQ_GDAT_OVERRUN_SHIFT               (30U)
#define ADC_SEQ_GDAT_OVERRUN(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_OVERRUN_SHIFT)) & ADC_SEQ_GDAT_OVERRUN_MASK)
#define ADC_SEQ_GDAT_DATAVALID_MASK              (0x80000000U)
#define ADC_SEQ_GDAT_DATAVALID_SHIFT             (31U)
#define ADC_SEQ_GDAT_DATAVALID(x)                (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_DATAVALID_SHIFT)) & ADC_SEQ_GDAT_DATAVALID_MASK)

/* The count of ADC_SEQ_GDAT */
#define ADC_SEQ_GDAT_COUNT                       (2U)

/*! @name DAT - ADC Channel 0 Data register. This register contains the result of the most recent conversion completed on channel 0. */
#define ADC_DAT_RESULT_MASK                      (0xFFF0U)
#define ADC_DAT_RESULT_SHIFT                     (4U)
#define ADC_DAT_RESULT(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_DAT_RESULT_SHIFT)) & ADC_DAT_RESULT_MASK)
#define ADC_DAT_THCMPRANGE_MASK                  (0x30000U)
#define ADC_DAT_THCMPRANGE_SHIFT                 (16U)
#define ADC_DAT_THCMPRANGE(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_DAT_THCMPRANGE_SHIFT)) & ADC_DAT_THCMPRANGE_MASK)
#define ADC_DAT_THCMPCROSS_MASK                  (0xC0000U)
#define ADC_DAT_THCMPCROSS_SHIFT                 (18U)
#define ADC_DAT_THCMPCROSS(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_DAT_THCMPCROSS_SHIFT)) & ADC_DAT_THCMPCROSS_MASK)
#define ADC_DAT_CHANNEL_MASK                     (0x3C000000U)
#define ADC_DAT_CHANNEL_SHIFT                    (26U)
#define ADC_DAT_CHANNEL(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_DAT_CHANNEL_SHIFT)) & ADC_DAT_CHANNEL_MASK)
#define ADC_DAT_OVERRUN_MASK                     (0x40000000U)
#define ADC_DAT_OVERRUN_SHIFT                    (30U)
#define ADC_DAT_OVERRUN(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_DAT_OVERRUN_SHIFT)) & ADC_DAT_OVERRUN_MASK)
#define ADC_DAT_DATAVALID_MASK                   (0x80000000U)
#define ADC_DAT_DATAVALID_SHIFT                  (31U)
#define ADC_DAT_DATAVALID(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_DAT_DATAVALID_SHIFT)) & ADC_DAT_DATAVALID_MASK)

/* The count of ADC_DAT */
#define ADC_DAT_COUNT                            (12U)

/*! @name THR0_LOW - ADC Low Compare Threshold register 0: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 0. */
#define ADC_THR0_LOW_THRLOW_MASK                 (0xFFF0U)
#define ADC_THR0_LOW_THRLOW_SHIFT                (4U)
#define ADC_THR0_LOW_THRLOW(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_THR0_LOW_THRLOW_SHIFT)) & ADC_THR0_LOW_THRLOW_MASK)

/*! @name THR1_LOW - ADC Low Compare Threshold register 1: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 1. */
#define ADC_THR1_LOW_THRLOW_MASK                 (0xFFF0U)
#define ADC_THR1_LOW_THRLOW_SHIFT                (4U)
#define ADC_THR1_LOW_THRLOW(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_THR1_LOW_THRLOW_SHIFT)) & ADC_THR1_LOW_THRLOW_MASK)

/*! @name THR0_HIGH - ADC High Compare Threshold register 0: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 0. */
#define ADC_THR0_HIGH_THRHIGH_MASK               (0xFFF0U)
#define ADC_THR0_HIGH_THRHIGH_SHIFT              (4U)
#define ADC_THR0_HIGH_THRHIGH(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_THR0_HIGH_THRHIGH_SHIFT)) & ADC_THR0_HIGH_THRHIGH_MASK)

/*! @name THR1_HIGH - ADC High Compare Threshold register 1: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 1. */
#define ADC_THR1_HIGH_THRHIGH_MASK               (0xFFF0U)
#define ADC_THR1_HIGH_THRHIGH_SHIFT              (4U)
#define ADC_THR1_HIGH_THRHIGH(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_THR1_HIGH_THRHIGH_SHIFT)) & ADC_THR1_HIGH_THRHIGH_MASK)

/*! @name CHAN_THRSEL - ADC Channel-Threshold Select register. Specifies which set of threshold compare registers are to be used for each channel */
#define ADC_CHAN_THRSEL_CH0_THRSEL_MASK          (0x1U)
#define ADC_CHAN_THRSEL_CH0_THRSEL_SHIFT         (0U)
#define ADC_CHAN_THRSEL_CH0_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH0_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH0_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH1_THRSEL_MASK          (0x2U)
#define ADC_CHAN_THRSEL_CH1_THRSEL_SHIFT         (1U)
#define ADC_CHAN_THRSEL_CH1_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH1_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH1_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH2_THRSEL_MASK          (0x4U)
#define ADC_CHAN_THRSEL_CH2_THRSEL_SHIFT         (2U)
#define ADC_CHAN_THRSEL_CH2_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH2_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH2_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH3_THRSEL_MASK          (0x8U)
#define ADC_CHAN_THRSEL_CH3_THRSEL_SHIFT         (3U)
#define ADC_CHAN_THRSEL_CH3_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH3_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH3_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH4_THRSEL_MASK          (0x10U)
#define ADC_CHAN_THRSEL_CH4_THRSEL_SHIFT         (4U)
#define ADC_CHAN_THRSEL_CH4_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH4_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH4_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH5_THRSEL_MASK          (0x20U)
#define ADC_CHAN_THRSEL_CH5_THRSEL_SHIFT         (5U)
#define ADC_CHAN_THRSEL_CH5_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH5_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH5_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH6_THRSEL_MASK          (0x40U)
#define ADC_CHAN_THRSEL_CH6_THRSEL_SHIFT         (6U)
#define ADC_CHAN_THRSEL_CH6_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH6_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH6_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH7_THRSEL_MASK          (0x80U)
#define ADC_CHAN_THRSEL_CH7_THRSEL_SHIFT         (7U)
#define ADC_CHAN_THRSEL_CH7_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH7_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH7_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH8_THRSEL_MASK          (0x100U)
#define ADC_CHAN_THRSEL_CH8_THRSEL_SHIFT         (8U)
#define ADC_CHAN_THRSEL_CH8_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH8_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH8_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH9_THRSEL_MASK          (0x200U)
#define ADC_CHAN_THRSEL_CH9_THRSEL_SHIFT         (9U)
#define ADC_CHAN_THRSEL_CH9_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH9_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH9_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH10_THRSEL_MASK         (0x400U)
#define ADC_CHAN_THRSEL_CH10_THRSEL_SHIFT        (10U)
#define ADC_CHAN_THRSEL_CH10_THRSEL(x)           (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH10_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH10_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH11_THRSEL_MASK         (0x800U)
#define ADC_CHAN_THRSEL_CH11_THRSEL_SHIFT        (11U)
#define ADC_CHAN_THRSEL_CH11_THRSEL(x)           (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH11_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH11_THRSEL_MASK)

/*! @name INTEN - ADC Interrupt Enable register. This register contains enable bits that enable the sequence-A, sequence-B, threshold compare and data overrun interrupts to be generated. */
#define ADC_INTEN_SEQA_INTEN_MASK                (0x1U)
#define ADC_INTEN_SEQA_INTEN_SHIFT               (0U)
#define ADC_INTEN_SEQA_INTEN(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_SEQA_INTEN_SHIFT)) & ADC_INTEN_SEQA_INTEN_MASK)
#define ADC_INTEN_SEQB_INTEN_MASK                (0x2U)
#define ADC_INTEN_SEQB_INTEN_SHIFT               (1U)
#define ADC_INTEN_SEQB_INTEN(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_SEQB_INTEN_SHIFT)) & ADC_INTEN_SEQB_INTEN_MASK)
#define ADC_INTEN_OVR_INTEN_MASK                 (0x4U)
#define ADC_INTEN_OVR_INTEN_SHIFT                (2U)
#define ADC_INTEN_OVR_INTEN(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_OVR_INTEN_SHIFT)) & ADC_INTEN_OVR_INTEN_MASK)
#define ADC_INTEN_ADCMPINTEN0_MASK               (0x18U)
#define ADC_INTEN_ADCMPINTEN0_SHIFT              (3U)
#define ADC_INTEN_ADCMPINTEN0(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN0_SHIFT)) & ADC_INTEN_ADCMPINTEN0_MASK)
#define ADC_INTEN_ADCMPINTEN1_MASK               (0x60U)
#define ADC_INTEN_ADCMPINTEN1_SHIFT              (5U)
#define ADC_INTEN_ADCMPINTEN1(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN1_SHIFT)) & ADC_INTEN_ADCMPINTEN1_MASK)
#define ADC_INTEN_ADCMPINTEN2_MASK               (0x180U)
#define ADC_INTEN_ADCMPINTEN2_SHIFT              (7U)
#define ADC_INTEN_ADCMPINTEN2(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN2_SHIFT)) & ADC_INTEN_ADCMPINTEN2_MASK)
#define ADC_INTEN_ADCMPINTEN3_MASK               (0x600U)
#define ADC_INTEN_ADCMPINTEN3_SHIFT              (9U)
#define ADC_INTEN_ADCMPINTEN3(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN3_SHIFT)) & ADC_INTEN_ADCMPINTEN3_MASK)
#define ADC_INTEN_ADCMPINTEN4_MASK               (0x1800U)
#define ADC_INTEN_ADCMPINTEN4_SHIFT              (11U)
#define ADC_INTEN_ADCMPINTEN4(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN4_SHIFT)) & ADC_INTEN_ADCMPINTEN4_MASK)
#define ADC_INTEN_ADCMPINTEN5_MASK               (0x6000U)
#define ADC_INTEN_ADCMPINTEN5_SHIFT              (13U)
#define ADC_INTEN_ADCMPINTEN5(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN5_SHIFT)) & ADC_INTEN_ADCMPINTEN5_MASK)
#define ADC_INTEN_ADCMPINTEN6_MASK               (0x18000U)
#define ADC_INTEN_ADCMPINTEN6_SHIFT              (15U)
#define ADC_INTEN_ADCMPINTEN6(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN6_SHIFT)) & ADC_INTEN_ADCMPINTEN6_MASK)
#define ADC_INTEN_ADCMPINTEN7_MASK               (0x60000U)
#define ADC_INTEN_ADCMPINTEN7_SHIFT              (17U)
#define ADC_INTEN_ADCMPINTEN7(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN7_SHIFT)) & ADC_INTEN_ADCMPINTEN7_MASK)
#define ADC_INTEN_ADCMPINTEN8_MASK               (0x180000U)
#define ADC_INTEN_ADCMPINTEN8_SHIFT              (19U)
#define ADC_INTEN_ADCMPINTEN8(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN8_SHIFT)) & ADC_INTEN_ADCMPINTEN8_MASK)
#define ADC_INTEN_ADCMPINTEN9_MASK               (0x600000U)
#define ADC_INTEN_ADCMPINTEN9_SHIFT              (21U)
#define ADC_INTEN_ADCMPINTEN9(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN9_SHIFT)) & ADC_INTEN_ADCMPINTEN9_MASK)
#define ADC_INTEN_ADCMPINTEN10_MASK              (0x1800000U)
#define ADC_INTEN_ADCMPINTEN10_SHIFT             (23U)
#define ADC_INTEN_ADCMPINTEN10(x)                (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN10_SHIFT)) & ADC_INTEN_ADCMPINTEN10_MASK)
#define ADC_INTEN_ADCMPINTEN11_MASK              (0x6000000U)
#define ADC_INTEN_ADCMPINTEN11_SHIFT             (25U)
#define ADC_INTEN_ADCMPINTEN11(x)                (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN11_SHIFT)) & ADC_INTEN_ADCMPINTEN11_MASK)

/*! @name FLAGS - ADC Flags register. Contains the four interrupt/DMA trigger flags and the individual component overrun and threshold-compare flags. (The overrun bits replicate information stored in the result registers). */
#define ADC_FLAGS_THCMP0_MASK                    (0x1U)
#define ADC_FLAGS_THCMP0_SHIFT                   (0U)
#define ADC_FLAGS_THCMP0(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP0_SHIFT)) & ADC_FLAGS_THCMP0_MASK)
#define ADC_FLAGS_THCMP1_MASK                    (0x2U)
#define ADC_FLAGS_THCMP1_SHIFT                   (1U)
#define ADC_FLAGS_THCMP1(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP1_SHIFT)) & ADC_FLAGS_THCMP1_MASK)
#define ADC_FLAGS_THCMP2_MASK                    (0x4U)
#define ADC_FLAGS_THCMP2_SHIFT                   (2U)
#define ADC_FLAGS_THCMP2(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP2_SHIFT)) & ADC_FLAGS_THCMP2_MASK)
#define ADC_FLAGS_THCMP3_MASK                    (0x8U)
#define ADC_FLAGS_THCMP3_SHIFT                   (3U)
#define ADC_FLAGS_THCMP3(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP3_SHIFT)) & ADC_FLAGS_THCMP3_MASK)
#define ADC_FLAGS_THCMP4_MASK                    (0x10U)
#define ADC_FLAGS_THCMP4_SHIFT                   (4U)
#define ADC_FLAGS_THCMP4(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP4_SHIFT)) & ADC_FLAGS_THCMP4_MASK)
#define ADC_FLAGS_THCMP5_MASK                    (0x20U)
#define ADC_FLAGS_THCMP5_SHIFT                   (5U)
#define ADC_FLAGS_THCMP5(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP5_SHIFT)) & ADC_FLAGS_THCMP5_MASK)
#define ADC_FLAGS_THCMP6_MASK                    (0x40U)
#define ADC_FLAGS_THCMP6_SHIFT                   (6U)
#define ADC_FLAGS_THCMP6(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP6_SHIFT)) & ADC_FLAGS_THCMP6_MASK)
#define ADC_FLAGS_THCMP7_MASK                    (0x80U)
#define ADC_FLAGS_THCMP7_SHIFT                   (7U)
#define ADC_FLAGS_THCMP7(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP7_SHIFT)) & ADC_FLAGS_THCMP7_MASK)
#define ADC_FLAGS_THCMP8_MASK                    (0x100U)
#define ADC_FLAGS_THCMP8_SHIFT                   (8U)
#define ADC_FLAGS_THCMP8(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP8_SHIFT)) & ADC_FLAGS_THCMP8_MASK)
#define ADC_FLAGS_THCMP9_MASK                    (0x200U)
#define ADC_FLAGS_THCMP9_SHIFT                   (9U)
#define ADC_FLAGS_THCMP9(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP9_SHIFT)) & ADC_FLAGS_THCMP9_MASK)
#define ADC_FLAGS_THCMP10_MASK                   (0x400U)
#define ADC_FLAGS_THCMP10_SHIFT                  (10U)
#define ADC_FLAGS_THCMP10(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP10_SHIFT)) & ADC_FLAGS_THCMP10_MASK)
#define ADC_FLAGS_THCMP11_MASK                   (0x800U)
#define ADC_FLAGS_THCMP11_SHIFT                  (11U)
#define ADC_FLAGS_THCMP11(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP11_SHIFT)) & ADC_FLAGS_THCMP11_MASK)
#define ADC_FLAGS_OVERRUN0_MASK                  (0x1000U)
#define ADC_FLAGS_OVERRUN0_SHIFT                 (12U)
#define ADC_FLAGS_OVERRUN0(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN0_SHIFT)) & ADC_FLAGS_OVERRUN0_MASK)
#define ADC_FLAGS_OVERRUN1_MASK                  (0x2000U)
#define ADC_FLAGS_OVERRUN1_SHIFT                 (13U)
#define ADC_FLAGS_OVERRUN1(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN1_SHIFT)) & ADC_FLAGS_OVERRUN1_MASK)
#define ADC_FLAGS_OVERRUN2_MASK                  (0x4000U)
#define ADC_FLAGS_OVERRUN2_SHIFT                 (14U)
#define ADC_FLAGS_OVERRUN2(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN2_SHIFT)) & ADC_FLAGS_OVERRUN2_MASK)
#define ADC_FLAGS_OVERRUN3_MASK                  (0x8000U)
#define ADC_FLAGS_OVERRUN3_SHIFT                 (15U)
#define ADC_FLAGS_OVERRUN3(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN3_SHIFT)) & ADC_FLAGS_OVERRUN3_MASK)
#define ADC_FLAGS_OVERRUN4_MASK                  (0x10000U)
#define ADC_FLAGS_OVERRUN4_SHIFT                 (16U)
#define ADC_FLAGS_OVERRUN4(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN4_SHIFT)) & ADC_FLAGS_OVERRUN4_MASK)
#define ADC_FLAGS_OVERRUN5_MASK                  (0x20000U)
#define ADC_FLAGS_OVERRUN5_SHIFT                 (17U)
#define ADC_FLAGS_OVERRUN5(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN5_SHIFT)) & ADC_FLAGS_OVERRUN5_MASK)
#define ADC_FLAGS_OVERRUN6_MASK                  (0x40000U)
#define ADC_FLAGS_OVERRUN6_SHIFT                 (18U)
#define ADC_FLAGS_OVERRUN6(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN6_SHIFT)) & ADC_FLAGS_OVERRUN6_MASK)
#define ADC_FLAGS_OVERRUN7_MASK                  (0x80000U)
#define ADC_FLAGS_OVERRUN7_SHIFT                 (19U)
#define ADC_FLAGS_OVERRUN7(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN7_SHIFT)) & ADC_FLAGS_OVERRUN7_MASK)
#define ADC_FLAGS_OVERRUN8_MASK                  (0x100000U)
#define ADC_FLAGS_OVERRUN8_SHIFT                 (20U)
#define ADC_FLAGS_OVERRUN8(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN8_SHIFT)) & ADC_FLAGS_OVERRUN8_MASK)
#define ADC_FLAGS_OVERRUN9_MASK                  (0x200000U)
#define ADC_FLAGS_OVERRUN9_SHIFT                 (21U)
#define ADC_FLAGS_OVERRUN9(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN9_SHIFT)) & ADC_FLAGS_OVERRUN9_MASK)
#define ADC_FLAGS_OVERRUN10_MASK                 (0x400000U)
#define ADC_FLAGS_OVERRUN10_SHIFT                (22U)
#define ADC_FLAGS_OVERRUN10(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN10_SHIFT)) & ADC_FLAGS_OVERRUN10_MASK)
#define ADC_FLAGS_OVERRUN11_MASK                 (0x800000U)
#define ADC_FLAGS_OVERRUN11_SHIFT                (23U)
#define ADC_FLAGS_OVERRUN11(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN11_SHIFT)) & ADC_FLAGS_OVERRUN11_MASK)
#define ADC_FLAGS_SEQA_OVR_MASK                  (0x1000000U)
#define ADC_FLAGS_SEQA_OVR_SHIFT                 (24U)
#define ADC_FLAGS_SEQA_OVR(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_SEQA_OVR_SHIFT)) & ADC_FLAGS_SEQA_OVR_MASK)
#define ADC_FLAGS_SEQB_OVR_MASK                  (0x2000000U)
#define ADC_FLAGS_SEQB_OVR_SHIFT                 (25U)
#define ADC_FLAGS_SEQB_OVR(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_SEQB_OVR_SHIFT)) & ADC_FLAGS_SEQB_OVR_MASK)
#define ADC_FLAGS_SEQA_INT_MASK                  (0x10000000U)
#define ADC_FLAGS_SEQA_INT_SHIFT                 (28U)
#define ADC_FLAGS_SEQA_INT(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_SEQA_INT_SHIFT)) & ADC_FLAGS_SEQA_INT_MASK)
#define ADC_FLAGS_SEQB_INT_MASK                  (0x20000000U)
#define ADC_FLAGS_SEQB_INT_SHIFT                 (29U)
#define ADC_FLAGS_SEQB_INT(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_SEQB_INT_SHIFT)) & ADC_FLAGS_SEQB_INT_MASK)
#define ADC_FLAGS_THCMP_INT_MASK                 (0x40000000U)
#define ADC_FLAGS_THCMP_INT_SHIFT                (30U)
#define ADC_FLAGS_THCMP_INT(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP_INT_SHIFT)) & ADC_FLAGS_THCMP_INT_MASK)
#define ADC_FLAGS_OVR_INT_MASK                   (0x80000000U)
#define ADC_FLAGS_OVR_INT_SHIFT                  (31U)
#define ADC_FLAGS_OVR_INT(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVR_INT_SHIFT)) & ADC_FLAGS_OVR_INT_MASK)

/*! @name STARTUP - ADC Startup register. */
#define ADC_STARTUP_ADC_ENA_MASK                 (0x1U)
#define ADC_STARTUP_ADC_ENA_SHIFT                (0U)
#define ADC_STARTUP_ADC_ENA(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_STARTUP_ADC_ENA_SHIFT)) & ADC_STARTUP_ADC_ENA_MASK)
#define ADC_STARTUP_ADC_INIT_MASK                (0x2U)
#define ADC_STARTUP_ADC_INIT_SHIFT               (1U)
#define ADC_STARTUP_ADC_INIT(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_STARTUP_ADC_INIT_SHIFT)) & ADC_STARTUP_ADC_INIT_MASK)

/*! @name CALIB - ADC Calibration register. */
#define ADC_CALIB_CALIB_MASK                     (0x1U)
#define ADC_CALIB_CALIB_SHIFT                    (0U)
#define ADC_CALIB_CALIB(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CALIB_CALIB_SHIFT)) & ADC_CALIB_CALIB_MASK)
#define ADC_CALIB_CALREQD_MASK                   (0x2U)
#define ADC_CALIB_CALREQD_SHIFT                  (1U)
#define ADC_CALIB_CALREQD(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_CALIB_CALREQD_SHIFT)) & ADC_CALIB_CALREQD_MASK)
#define ADC_CALIB_CALVALUE_MASK                  (0x1FCU)
#define ADC_CALIB_CALVALUE_SHIFT                 (2U)
#define ADC_CALIB_CALVALUE(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_CALIB_CALVALUE_SHIFT)) & ADC_CALIB_CALVALUE_MASK)


/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base address */
#define ADC0_BASE                                (0x400A0000u)
/** Peripheral ADC0 base pointer */
#define ADC0                                     ((ADC_Type *)ADC0_BASE)
/** Array initializer of ADC peripheral base addresses */
#define ADC_BASE_ADDRS                           { ADC0_BASE }
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            { ADC0 }
/** Interrupt vectors for the ADC peripheral type */
#define ADC_SEQ_IRQS                             { ADC0_SEQA_IRQn, ADC0_SEQB_IRQn }
#define ADC_THCMP_IRQS                           { ADC0_THCMP_IRQn }

/*!
 * @}
 */ /* end of group ADC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- ASYNC_SYSCON Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ASYNC_SYSCON_Peripheral_Access_Layer ASYNC_SYSCON Peripheral Access Layer
 * @{
 */

/** ASYNC_SYSCON - Register Layout Typedef */
typedef struct {
  __IO uint32_t ASYNCPRESETCTRL;                   /**< Async peripheral reset control, offset: 0x0 */
  __O  uint32_t ASYNCPRESETCTRLSET;                /**< Set bits in ASYNCPRESETCTRL, offset: 0x4 */
  __O  uint32_t ASYNCPRESETCTRLCLR;                /**< Clear bits in ASYNCPRESETCTRL, offset: 0x8 */
       uint8_t RESERVED_0[4];
  __IO uint32_t ASYNCAPBCLKCTRL;                   /**< Async peripheral clock control, offset: 0x10 */
  __O  uint32_t ASYNCAPBCLKCTRLSET;                /**< Set bits in ASYNCAPBCLKCTRL, offset: 0x14 */
  __O  uint32_t ASYNCAPBCLKCTRLCLR;                /**< Clear bits in ASYNCAPBCLKCTRL, offset: 0x18 */
       uint8_t RESERVED_1[4];
  __IO uint32_t ASYNCAPBCLKSELA;                   /**< Async APB clock source select A, offset: 0x20 */
} ASYNC_SYSCON_Type;

/* ----------------------------------------------------------------------------
   -- ASYNC_SYSCON Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ASYNC_SYSCON_Register_Masks ASYNC_SYSCON Register Masks
 * @{
 */

/*! @name ASYNCPRESETCTRL - Async peripheral reset control */
#define ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER3_MASK (0x2000U)
#define ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER3_SHIFT (13U)
#define ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER3(x)  (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER3_SHIFT)) & ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER3_MASK)
#define ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER4_MASK (0x4000U)
#define ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER4_SHIFT (14U)
#define ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER4(x)  (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER4_SHIFT)) & ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER4_MASK)

/*! @name ASYNCPRESETCTRLSET - Set bits in ASYNCPRESETCTRL */
#define ASYNC_SYSCON_ASYNCPRESETCTRLSET_ARST_SET_MASK (0xFFFFFFFFU)
#define ASYNC_SYSCON_ASYNCPRESETCTRLSET_ARST_SET_SHIFT (0U)
#define ASYNC_SYSCON_ASYNCPRESETCTRLSET_ARST_SET(x) (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCPRESETCTRLSET_ARST_SET_SHIFT)) & ASYNC_SYSCON_ASYNCPRESETCTRLSET_ARST_SET_MASK)

/*! @name ASYNCPRESETCTRLCLR - Clear bits in ASYNCPRESETCTRL */
#define ASYNC_SYSCON_ASYNCPRESETCTRLCLR_ARST_CLR_MASK (0xFFFFFFFFU)
#define ASYNC_SYSCON_ASYNCPRESETCTRLCLR_ARST_CLR_SHIFT (0U)
#define ASYNC_SYSCON_ASYNCPRESETCTRLCLR_ARST_CLR(x) (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCPRESETCTRLCLR_ARST_CLR_SHIFT)) & ASYNC_SYSCON_ASYNCPRESETCTRLCLR_ARST_CLR_MASK)

/*! @name ASYNCAPBCLKCTRL - Async peripheral clock control */
#define ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER3_MASK (0x2000U)
#define ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER3_SHIFT (13U)
#define ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER3(x)  (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER3_SHIFT)) & ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER3_MASK)
#define ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER4_MASK (0x4000U)
#define ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER4_SHIFT (14U)
#define ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER4(x)  (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER4_SHIFT)) & ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER4_MASK)

/*! @name ASYNCAPBCLKCTRLSET - Set bits in ASYNCAPBCLKCTRL */
#define ASYNC_SYSCON_ASYNCAPBCLKCTRLSET_ACLK_SET_MASK (0xFFFFFFFFU)
#define ASYNC_SYSCON_ASYNCAPBCLKCTRLSET_ACLK_SET_SHIFT (0U)
#define ASYNC_SYSCON_ASYNCAPBCLKCTRLSET_ACLK_SET(x) (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCAPBCLKCTRLSET_ACLK_SET_SHIFT)) & ASYNC_SYSCON_ASYNCAPBCLKCTRLSET_ACLK_SET_MASK)

/*! @name ASYNCAPBCLKCTRLCLR - Clear bits in ASYNCAPBCLKCTRL */
#define ASYNC_SYSCON_ASYNCAPBCLKCTRLCLR_ACLK_CLR_MASK (0xFFFFFFFFU)
#define ASYNC_SYSCON_ASYNCAPBCLKCTRLCLR_ACLK_CLR_SHIFT (0U)
#define ASYNC_SYSCON_ASYNCAPBCLKCTRLCLR_ACLK_CLR(x) (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCAPBCLKCTRLCLR_ACLK_CLR_SHIFT)) & ASYNC_SYSCON_ASYNCAPBCLKCTRLCLR_ACLK_CLR_MASK)

/*! @name ASYNCAPBCLKSELA - Async APB clock source select A */
#define ASYNC_SYSCON_ASYNCAPBCLKSELA_SEL_MASK    (0x3U)
#define ASYNC_SYSCON_ASYNCAPBCLKSELA_SEL_SHIFT   (0U)
#define ASYNC_SYSCON_ASYNCAPBCLKSELA_SEL(x)      (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCAPBCLKSELA_SEL_SHIFT)) & ASYNC_SYSCON_ASYNCAPBCLKSELA_SEL_MASK)


/*!
 * @}
 */ /* end of group ASYNC_SYSCON_Register_Masks */


/* ASYNC_SYSCON - Peripheral instance base addresses */
/** Peripheral ASYNC_SYSCON base address */
#define ASYNC_SYSCON_BASE                        (0x40040000u)
/** Peripheral ASYNC_SYSCON base pointer */
#define ASYNC_SYSCON                             ((ASYNC_SYSCON_Type *)ASYNC_SYSCON_BASE)
/** Array initializer of ASYNC_SYSCON peripheral base addresses */
#define ASYNC_SYSCON_BASE_ADDRS                  { ASYNC_SYSCON_BASE }
/** Array initializer of ASYNC_SYSCON peripheral base pointers */
#define ASYNC_SYSCON_BASE_PTRS                   { ASYNC_SYSCON }

/*!
 * @}
 */ /* end of group ASYNC_SYSCON_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CAN Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAN_Peripheral_Access_Layer CAN Peripheral Access Layer
 * @{
 */

/** CAN - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[16];
  __IO uint32_t TEST;                              /**< Test Register, offset: 0x10 */
       uint8_t RESERVED_1[4];
  __IO uint32_t CCCR;                              /**< CC Control Register, offset: 0x18 */
  __IO uint32_t NBTP;                              /**< Nominal Bit Timing and Prescaler Register, offset: 0x1C */
  __IO uint32_t TSCC;                              /**< Timestamp Counter Configuration, offset: 0x20 */
  __IO uint32_t TSCV;                              /**< Timestamp Counter Value, offset: 0x24 */
  __IO uint32_t TOCC;                              /**< Timeout Counter Configuration, offset: 0x28 */
  __I  uint32_t TOCV;                              /**< Timeout Counter Value, offset: 0x2C */
       uint8_t RESERVED_2[16];
  __I  uint32_t ECR;                               /**< Error Counter Register, offset: 0x40 */
  __I  uint32_t PSR;                               /**< Protocol Status Register, offset: 0x44 */
  __IO uint32_t TDCR;                              /**< Transmitter Delay Compensator Register, offset: 0x48 */
       uint8_t RESERVED_3[4];
  __IO uint32_t IR;                                /**< Interrupt Register, offset: 0x50 */
  __IO uint32_t IE;                                /**< Interrupt Enable, offset: 0x54 */
  __IO uint32_t ILS;                               /**< Interrupt Line Select, offset: 0x58 */
  __IO uint32_t ILE;                               /**< Interrupt Line Enable, offset: 0x5C */
       uint8_t RESERVED_4[32];
  __IO uint32_t GFC;                               /**< Global Filter Configuration, offset: 0x80 */
  __IO uint32_t SIDFC;                             /**< Standard ID Filter Configuration, offset: 0x84 */
  __IO uint32_t XIDFC;                             /**< Extended ID Filter Configuration, offset: 0x88 */
       uint8_t RESERVED_5[4];
  __IO uint32_t XIDAM;                             /**< Extended ID AND Mask, offset: 0x90 */
  __I  uint32_t HPMS;                              /**< High Priority Message Status, offset: 0x94 */
  __IO uint32_t NDAT1;                             /**< New Data 1, offset: 0x98 */
  __IO uint32_t NDAT2;                             /**< New Data 2, offset: 0x9C */
  __IO uint32_t RXF0C;                             /**< Rx FIFO 0 Configuration, offset: 0xA0 */
  __IO uint32_t RXF0S;                             /**< Rx FIFO 0 Status, offset: 0xA4 */
  __IO uint32_t RXF0A;                             /**< Rx FIFO 0 Acknowledge, offset: 0xA8 */
  __IO uint32_t RXBC;                              /**< Rx Buffer Configuration, offset: 0xAC */
  __IO uint32_t RXF1C;                             /**< Rx FIFO 1 Configuration, offset: 0xB0 */
  __I  uint32_t RXF1S;                             /**< Rx FIFO 1 Status, offset: 0xB4 */
  __IO uint32_t RXF1A;                             /**< Rx FIFO 1 Acknowledge, offset: 0xB8 */
  __IO uint32_t RXESC;                             /**< Rx Buffer and FIFO Element Size Configuration, offset: 0xBC */
  __IO uint32_t TXBC;                              /**< Tx Buffer Configuration, offset: 0xC0 */
  __IO uint32_t TXFQS;                             /**< Tx FIFO/Queue Status, offset: 0xC4 */
  __IO uint32_t TXESC;                             /**< Tx Buffer Element Size Configuration, offset: 0xC8 */
  __IO uint32_t TXBRP;                             /**< Tx Buffer Request Pending, offset: 0xCC */
  __IO uint32_t TXBAR;                             /**< Tx Buffer Add Request, offset: 0xD0 */
  __IO uint32_t TXBCR;                             /**< Tx Buffer Cancellation Request, offset: 0xD4 */
  __IO uint32_t TXBTO;                             /**< Tx Buffer Transmission Occurred, offset: 0xD8 */
  __IO uint32_t TXBCF;                             /**< Tx Buffer Cancellation Finished, offset: 0xDC */
  __IO uint32_t TXBTIE;                            /**< Tx Buffer Transmission Interrupt Enable, offset: 0xE0 */
  __IO uint32_t TXBCIE;                            /**< Tx Buffer Cancellation Finished Interrupt Enable, offset: 0xE4 */
       uint8_t RESERVED_6[8];
  __IO uint32_t TXEFC;                             /**< Tx Event FIFO Configuration, offset: 0xF0 */
  __I  uint32_t TXEFS;                             /**< Tx Event FIFO Status, offset: 0xF4 */
  __IO uint32_t TXEFA;                             /**< Tx Event FIFO Acknowledge, offset: 0xF8 */
       uint8_t RESERVED_7[260];
  __IO uint32_t MRBA;                              /**< CAN Message RAM Base Address, offset: 0x200 */
       uint8_t RESERVED_8[508];
  __IO uint32_t ETSCC;                             /**< External Timestamp Counter Configuration, offset: 0x400 */
       uint8_t RESERVED_9[508];
  __IO uint32_t ETSCV;                             /**< External Timestamp Counter Value, offset: 0x600 */
} CAN_Type;

/* ----------------------------------------------------------------------------
   -- CAN Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAN_Register_Masks CAN Register Masks
 * @{
 */

/*! @name TEST - Test Register */
#define CAN_TEST_LBCK_MASK                       (0x10U)
#define CAN_TEST_LBCK_SHIFT                      (4U)
#define CAN_TEST_LBCK(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TEST_LBCK_SHIFT)) & CAN_TEST_LBCK_MASK)
#define CAN_TEST_TX_MASK                         (0x60U)
#define CAN_TEST_TX_SHIFT                        (5U)
#define CAN_TEST_TX(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_TEST_TX_SHIFT)) & CAN_TEST_TX_MASK)
#define CAN_TEST_RX_MASK                         (0x80U)
#define CAN_TEST_RX_SHIFT                        (7U)
#define CAN_TEST_RX(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_TEST_RX_SHIFT)) & CAN_TEST_RX_MASK)

/*! @name CCCR - CC Control Register */
#define CAN_CCCR_INIT_MASK                       (0x1U)
#define CAN_CCCR_INIT_SHIFT                      (0U)
#define CAN_CCCR_INIT(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_INIT_SHIFT)) & CAN_CCCR_INIT_MASK)
#define CAN_CCCR_CCE_MASK                        (0x2U)
#define CAN_CCCR_CCE_SHIFT                       (1U)
#define CAN_CCCR_CCE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_CCE_SHIFT)) & CAN_CCCR_CCE_MASK)
#define CAN_CCCR_ASM_MASK                        (0x4U)
#define CAN_CCCR_ASM_SHIFT                       (2U)
#define CAN_CCCR_ASM(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_ASM_SHIFT)) & CAN_CCCR_ASM_MASK)
#define CAN_CCCR_CSA_MASK                        (0x8U)
#define CAN_CCCR_CSA_SHIFT                       (3U)
#define CAN_CCCR_CSA(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_CSA_SHIFT)) & CAN_CCCR_CSA_MASK)
#define CAN_CCCR_CSR_MASK                        (0x10U)
#define CAN_CCCR_CSR_SHIFT                       (4U)
#define CAN_CCCR_CSR(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_CSR_SHIFT)) & CAN_CCCR_CSR_MASK)
#define CAN_CCCR_MON_MASK                        (0x20U)
#define CAN_CCCR_MON_SHIFT                       (5U)
#define CAN_CCCR_MON(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_MON_SHIFT)) & CAN_CCCR_MON_MASK)
#define CAN_CCCR_DAR_MASK                        (0x40U)
#define CAN_CCCR_DAR_SHIFT                       (6U)
#define CAN_CCCR_DAR(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_DAR_SHIFT)) & CAN_CCCR_DAR_MASK)
#define CAN_CCCR_TEST_MASK                       (0x80U)
#define CAN_CCCR_TEST_SHIFT                      (7U)
#define CAN_CCCR_TEST(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_TEST_SHIFT)) & CAN_CCCR_TEST_MASK)
#define CAN_CCCR_PXHD_MASK                       (0x1000U)
#define CAN_CCCR_PXHD_SHIFT                      (12U)
#define CAN_CCCR_PXHD(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_PXHD_SHIFT)) & CAN_CCCR_PXHD_MASK)
#define CAN_CCCR_EFBI_MASK                       (0x2000U)
#define CAN_CCCR_EFBI_SHIFT                      (13U)
#define CAN_CCCR_EFBI(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_EFBI_SHIFT)) & CAN_CCCR_EFBI_MASK)
#define CAN_CCCR_TXP_MASK                        (0x4000U)
#define CAN_CCCR_TXP_SHIFT                       (14U)
#define CAN_CCCR_TXP(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CCCR_TXP_SHIFT)) & CAN_CCCR_TXP_MASK)

/*! @name NBTP - Nominal Bit Timing and Prescaler Register */
#define CAN_NBTP_NTSEG2_MASK                     (0x7FU)
#define CAN_NBTP_NTSEG2_SHIFT                    (0U)
#define CAN_NBTP_NTSEG2(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_NBTP_NTSEG2_SHIFT)) & CAN_NBTP_NTSEG2_MASK)
#define CAN_NBTP_NTSEG1_MASK                     (0xFF00U)
#define CAN_NBTP_NTSEG1_SHIFT                    (8U)
#define CAN_NBTP_NTSEG1(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_NBTP_NTSEG1_SHIFT)) & CAN_NBTP_NTSEG1_MASK)
#define CAN_NBTP_NBRP_MASK                       (0x1FF0000U)
#define CAN_NBTP_NBRP_SHIFT                      (16U)
#define CAN_NBTP_NBRP(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_NBTP_NBRP_SHIFT)) & CAN_NBTP_NBRP_MASK)
#define CAN_NBTP_NSJW_MASK                       (0xFE000000U)
#define CAN_NBTP_NSJW_SHIFT                      (25U)
#define CAN_NBTP_NSJW(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_NBTP_NSJW_SHIFT)) & CAN_NBTP_NSJW_MASK)

/*! @name TSCC - Timestamp Counter Configuration */
#define CAN_TSCC_TSS_MASK                        (0x3U)
#define CAN_TSCC_TSS_SHIFT                       (0U)
#define CAN_TSCC_TSS(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TSCC_TSS_SHIFT)) & CAN_TSCC_TSS_MASK)
#define CAN_TSCC_TCP_MASK                        (0xF0000U)
#define CAN_TSCC_TCP_SHIFT                       (16U)
#define CAN_TSCC_TCP(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TSCC_TCP_SHIFT)) & CAN_TSCC_TCP_MASK)

/*! @name TSCV - Timestamp Counter Value */
#define CAN_TSCV_TSC_MASK                        (0xFFFFU)
#define CAN_TSCV_TSC_SHIFT                       (0U)
#define CAN_TSCV_TSC(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TSCV_TSC_SHIFT)) & CAN_TSCV_TSC_MASK)

/*! @name TOCC - Timeout Counter Configuration */
#define CAN_TOCC_ETOC_MASK                       (0x1U)
#define CAN_TOCC_ETOC_SHIFT                      (0U)
#define CAN_TOCC_ETOC(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TOCC_ETOC_SHIFT)) & CAN_TOCC_ETOC_MASK)
#define CAN_TOCC_TOS_MASK                        (0x6U)
#define CAN_TOCC_TOS_SHIFT                       (1U)
#define CAN_TOCC_TOS(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TOCC_TOS_SHIFT)) & CAN_TOCC_TOS_MASK)
#define CAN_TOCC_TOP_MASK                        (0xFFFF0000U)
#define CAN_TOCC_TOP_SHIFT                       (16U)
#define CAN_TOCC_TOP(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TOCC_TOP_SHIFT)) & CAN_TOCC_TOP_MASK)

/*! @name TOCV - Timeout Counter Value */
#define CAN_TOCV_TOC_MASK                        (0xFFFFU)
#define CAN_TOCV_TOC_SHIFT                       (0U)
#define CAN_TOCV_TOC(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TOCV_TOC_SHIFT)) & CAN_TOCV_TOC_MASK)

/*! @name ECR - Error Counter Register */
#define CAN_ECR_TEC_MASK                         (0xFFU)
#define CAN_ECR_TEC_SHIFT                        (0U)
#define CAN_ECR_TEC(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ECR_TEC_SHIFT)) & CAN_ECR_TEC_MASK)
#define CAN_ECR_REC_MASK                         (0x7F00U)
#define CAN_ECR_REC_SHIFT                        (8U)
#define CAN_ECR_REC(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ECR_REC_SHIFT)) & CAN_ECR_REC_MASK)
#define CAN_ECR_RP_MASK                          (0x8000U)
#define CAN_ECR_RP_SHIFT                         (15U)
#define CAN_ECR_RP(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_ECR_RP_SHIFT)) & CAN_ECR_RP_MASK)
#define CAN_ECR_CEL_MASK                         (0xFF0000U)
#define CAN_ECR_CEL_SHIFT                        (16U)
#define CAN_ECR_CEL(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ECR_CEL_SHIFT)) & CAN_ECR_CEL_MASK)

/*! @name PSR - Protocol Status Register */
#define CAN_PSR_LEC_MASK                         (0x7U)
#define CAN_PSR_LEC_SHIFT                        (0U)
#define CAN_PSR_LEC(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_PSR_LEC_SHIFT)) & CAN_PSR_LEC_MASK)
#define CAN_PSR_ACT_MASK                         (0x18U)
#define CAN_PSR_ACT_SHIFT                        (3U)
#define CAN_PSR_ACT(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_PSR_ACT_SHIFT)) & CAN_PSR_ACT_MASK)
#define CAN_PSR_EP_MASK                          (0x20U)
#define CAN_PSR_EP_SHIFT                         (5U)
#define CAN_PSR_EP(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_PSR_EP_SHIFT)) & CAN_PSR_EP_MASK)
#define CAN_PSR_EW_MASK                          (0x40U)
#define CAN_PSR_EW_SHIFT                         (6U)
#define CAN_PSR_EW(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_PSR_EW_SHIFT)) & CAN_PSR_EW_MASK)
#define CAN_PSR_BO_MASK                          (0x80U)
#define CAN_PSR_BO_SHIFT                         (7U)
#define CAN_PSR_BO(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_PSR_BO_SHIFT)) & CAN_PSR_BO_MASK)
#define CAN_PSR_PXE_MASK                         (0x4000U)
#define CAN_PSR_PXE_SHIFT                        (14U)
#define CAN_PSR_PXE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_PSR_PXE_SHIFT)) & CAN_PSR_PXE_MASK)
#define CAN_PSR_TDCV_MASK                        (0x7F0000U)
#define CAN_PSR_TDCV_SHIFT                       (16U)
#define CAN_PSR_TDCV(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PSR_TDCV_SHIFT)) & CAN_PSR_TDCV_MASK)

/*! @name TDCR - Transmitter Delay Compensator Register */
#define CAN_TDCR_TDCF_MASK                       (0x7FU)
#define CAN_TDCR_TDCF_SHIFT                      (0U)
#define CAN_TDCR_TDCF(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TDCR_TDCF_SHIFT)) & CAN_TDCR_TDCF_MASK)
#define CAN_TDCR_TDCO_MASK                       (0x7F00U)
#define CAN_TDCR_TDCO_SHIFT                      (8U)
#define CAN_TDCR_TDCO(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TDCR_TDCO_SHIFT)) & CAN_TDCR_TDCO_MASK)

/*! @name IR - Interrupt Register */
#define CAN_IR_RF0N_MASK                         (0x1U)
#define CAN_IR_RF0N_SHIFT                        (0U)
#define CAN_IR_RF0N(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF0N_SHIFT)) & CAN_IR_RF0N_MASK)
#define CAN_IR_RF0W_MASK                         (0x2U)
#define CAN_IR_RF0W_SHIFT                        (1U)
#define CAN_IR_RF0W(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF0W_SHIFT)) & CAN_IR_RF0W_MASK)
#define CAN_IR_RF0F_MASK                         (0x4U)
#define CAN_IR_RF0F_SHIFT                        (2U)
#define CAN_IR_RF0F(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF0F_SHIFT)) & CAN_IR_RF0F_MASK)
#define CAN_IR_RF0L_MASK                         (0x8U)
#define CAN_IR_RF0L_SHIFT                        (3U)
#define CAN_IR_RF0L(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF0L_SHIFT)) & CAN_IR_RF0L_MASK)
#define CAN_IR_RF1N_MASK                         (0x10U)
#define CAN_IR_RF1N_SHIFT                        (4U)
#define CAN_IR_RF1N(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF1N_SHIFT)) & CAN_IR_RF1N_MASK)
#define CAN_IR_RF1W_MASK                         (0x20U)
#define CAN_IR_RF1W_SHIFT                        (5U)
#define CAN_IR_RF1W(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF1W_SHIFT)) & CAN_IR_RF1W_MASK)
#define CAN_IR_RF1F_MASK                         (0x40U)
#define CAN_IR_RF1F_SHIFT                        (6U)
#define CAN_IR_RF1F(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF1F_SHIFT)) & CAN_IR_RF1F_MASK)
#define CAN_IR_RF1L_MASK                         (0x80U)
#define CAN_IR_RF1L_SHIFT                        (7U)
#define CAN_IR_RF1L(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_RF1L_SHIFT)) & CAN_IR_RF1L_MASK)
#define CAN_IR_HPM_MASK                          (0x100U)
#define CAN_IR_HPM_SHIFT                         (8U)
#define CAN_IR_HPM(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_HPM_SHIFT)) & CAN_IR_HPM_MASK)
#define CAN_IR_TC_MASK                           (0x200U)
#define CAN_IR_TC_SHIFT                          (9U)
#define CAN_IR_TC(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_IR_TC_SHIFT)) & CAN_IR_TC_MASK)
#define CAN_IR_TCF_MASK                          (0x400U)
#define CAN_IR_TCF_SHIFT                         (10U)
#define CAN_IR_TCF(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_TCF_SHIFT)) & CAN_IR_TCF_MASK)
#define CAN_IR_TFE_MASK                          (0x800U)
#define CAN_IR_TFE_SHIFT                         (11U)
#define CAN_IR_TFE(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_TFE_SHIFT)) & CAN_IR_TFE_MASK)
#define CAN_IR_TEFN_MASK                         (0x1000U)
#define CAN_IR_TEFN_SHIFT                        (12U)
#define CAN_IR_TEFN(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_TEFN_SHIFT)) & CAN_IR_TEFN_MASK)
#define CAN_IR_TEFW_MASK                         (0x2000U)
#define CAN_IR_TEFW_SHIFT                        (13U)
#define CAN_IR_TEFW(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_TEFW_SHIFT)) & CAN_IR_TEFW_MASK)
#define CAN_IR_TEFF_MASK                         (0x4000U)
#define CAN_IR_TEFF_SHIFT                        (14U)
#define CAN_IR_TEFF(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_TEFF_SHIFT)) & CAN_IR_TEFF_MASK)
#define CAN_IR_TEFL_MASK                         (0x8000U)
#define CAN_IR_TEFL_SHIFT                        (15U)
#define CAN_IR_TEFL(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_TEFL_SHIFT)) & CAN_IR_TEFL_MASK)
#define CAN_IR_TSW_MASK                          (0x10000U)
#define CAN_IR_TSW_SHIFT                         (16U)
#define CAN_IR_TSW(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_TSW_SHIFT)) & CAN_IR_TSW_MASK)
#define CAN_IR_MRAF_MASK                         (0x20000U)
#define CAN_IR_MRAF_SHIFT                        (17U)
#define CAN_IR_MRAF(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_MRAF_SHIFT)) & CAN_IR_MRAF_MASK)
#define CAN_IR_TOO_MASK                          (0x40000U)
#define CAN_IR_TOO_SHIFT                         (18U)
#define CAN_IR_TOO(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_TOO_SHIFT)) & CAN_IR_TOO_MASK)
#define CAN_IR_DRX_MASK                          (0x80000U)
#define CAN_IR_DRX_SHIFT                         (19U)
#define CAN_IR_DRX(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_DRX_SHIFT)) & CAN_IR_DRX_MASK)
#define CAN_IR_BEC_MASK                          (0x100000U)
#define CAN_IR_BEC_SHIFT                         (20U)
#define CAN_IR_BEC(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_BEC_SHIFT)) & CAN_IR_BEC_MASK)
#define CAN_IR_BEU_MASK                          (0x200000U)
#define CAN_IR_BEU_SHIFT                         (21U)
#define CAN_IR_BEU(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_BEU_SHIFT)) & CAN_IR_BEU_MASK)
#define CAN_IR_ELO_MASK                          (0x400000U)
#define CAN_IR_ELO_SHIFT                         (22U)
#define CAN_IR_ELO(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_ELO_SHIFT)) & CAN_IR_ELO_MASK)
#define CAN_IR_EP_MASK                           (0x800000U)
#define CAN_IR_EP_SHIFT                          (23U)
#define CAN_IR_EP(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_IR_EP_SHIFT)) & CAN_IR_EP_MASK)
#define CAN_IR_EW_MASK                           (0x1000000U)
#define CAN_IR_EW_SHIFT                          (24U)
#define CAN_IR_EW(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_IR_EW_SHIFT)) & CAN_IR_EW_MASK)
#define CAN_IR_BO_MASK                           (0x2000000U)
#define CAN_IR_BO_SHIFT                          (25U)
#define CAN_IR_BO(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_IR_BO_SHIFT)) & CAN_IR_BO_MASK)
#define CAN_IR_WDI_MASK                          (0x4000000U)
#define CAN_IR_WDI_SHIFT                         (26U)
#define CAN_IR_WDI(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_WDI_SHIFT)) & CAN_IR_WDI_MASK)
#define CAN_IR_PEA_MASK                          (0x8000000U)
#define CAN_IR_PEA_SHIFT                         (27U)
#define CAN_IR_PEA(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_PEA_SHIFT)) & CAN_IR_PEA_MASK)
#define CAN_IR_PED_MASK                          (0x10000000U)
#define CAN_IR_PED_SHIFT                         (28U)
#define CAN_IR_PED(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_PED_SHIFT)) & CAN_IR_PED_MASK)
#define CAN_IR_ARA_MASK                          (0x20000000U)
#define CAN_IR_ARA_SHIFT                         (29U)
#define CAN_IR_ARA(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_ARA_SHIFT)) & CAN_IR_ARA_MASK)

/*! @name IE - Interrupt Enable */
#define CAN_IE_RF0NE_MASK                        (0x1U)
#define CAN_IE_RF0NE_SHIFT                       (0U)
#define CAN_IE_RF0NE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF0NE_SHIFT)) & CAN_IE_RF0NE_MASK)
#define CAN_IE_RF0WE_MASK                        (0x2U)
#define CAN_IE_RF0WE_SHIFT                       (1U)
#define CAN_IE_RF0WE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF0WE_SHIFT)) & CAN_IE_RF0WE_MASK)
#define CAN_IE_RF0FE_MASK                        (0x4U)
#define CAN_IE_RF0FE_SHIFT                       (2U)
#define CAN_IE_RF0FE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF0FE_SHIFT)) & CAN_IE_RF0FE_MASK)
#define CAN_IE_RF0LE_MASK                        (0x8U)
#define CAN_IE_RF0LE_SHIFT                       (3U)
#define CAN_IE_RF0LE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF0LE_SHIFT)) & CAN_IE_RF0LE_MASK)
#define CAN_IE_RF1NE_MASK                        (0x10U)
#define CAN_IE_RF1NE_SHIFT                       (4U)
#define CAN_IE_RF1NE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF1NE_SHIFT)) & CAN_IE_RF1NE_MASK)
#define CAN_IE_RF1WE_MASK                        (0x20U)
#define CAN_IE_RF1WE_SHIFT                       (5U)
#define CAN_IE_RF1WE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF1WE_SHIFT)) & CAN_IE_RF1WE_MASK)
#define CAN_IE_RF1FE_MASK                        (0x40U)
#define CAN_IE_RF1FE_SHIFT                       (6U)
#define CAN_IE_RF1FE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF1FE_SHIFT)) & CAN_IE_RF1FE_MASK)
#define CAN_IE_RF1LE_MASK                        (0x80U)
#define CAN_IE_RF1LE_SHIFT                       (7U)
#define CAN_IE_RF1LE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_RF1LE_SHIFT)) & CAN_IE_RF1LE_MASK)
#define CAN_IE_HPME_MASK                         (0x100U)
#define CAN_IE_HPME_SHIFT                        (8U)
#define CAN_IE_HPME(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_HPME_SHIFT)) & CAN_IE_HPME_MASK)
#define CAN_IE_TCE_MASK                          (0x200U)
#define CAN_IE_TCE_SHIFT                         (9U)
#define CAN_IE_TCE(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IE_TCE_SHIFT)) & CAN_IE_TCE_MASK)
#define CAN_IE_TCFE_MASK                         (0x400U)
#define CAN_IE_TCFE_SHIFT                        (10U)
#define CAN_IE_TCFE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_TCFE_SHIFT)) & CAN_IE_TCFE_MASK)
#define CAN_IE_TFEE_MASK                         (0x800U)
#define CAN_IE_TFEE_SHIFT                        (11U)
#define CAN_IE_TFEE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_TFEE_SHIFT)) & CAN_IE_TFEE_MASK)
#define CAN_IE_TEFNE_MASK                        (0x1000U)
#define CAN_IE_TEFNE_SHIFT                       (12U)
#define CAN_IE_TEFNE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_TEFNE_SHIFT)) & CAN_IE_TEFNE_MASK)
#define CAN_IE_TEFWE_MASK                        (0x2000U)
#define CAN_IE_TEFWE_SHIFT                       (13U)
#define CAN_IE_TEFWE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_TEFWE_SHIFT)) & CAN_IE_TEFWE_MASK)
#define CAN_IE_TEFFE_MASK                        (0x4000U)
#define CAN_IE_TEFFE_SHIFT                       (14U)
#define CAN_IE_TEFFE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_TEFFE_SHIFT)) & CAN_IE_TEFFE_MASK)
#define CAN_IE_TEFLE_MASK                        (0x8000U)
#define CAN_IE_TEFLE_SHIFT                       (15U)
#define CAN_IE_TEFLE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_TEFLE_SHIFT)) & CAN_IE_TEFLE_MASK)
#define CAN_IE_TSWE_MASK                         (0x10000U)
#define CAN_IE_TSWE_SHIFT                        (16U)
#define CAN_IE_TSWE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_TSWE_SHIFT)) & CAN_IE_TSWE_MASK)
#define CAN_IE_MRAFE_MASK                        (0x20000U)
#define CAN_IE_MRAFE_SHIFT                       (17U)
#define CAN_IE_MRAFE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IE_MRAFE_SHIFT)) & CAN_IE_MRAFE_MASK)
#define CAN_IE_TOOE_MASK                         (0x40000U)
#define CAN_IE_TOOE_SHIFT                        (18U)
#define CAN_IE_TOOE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_TOOE_SHIFT)) & CAN_IE_TOOE_MASK)
#define CAN_IE_DRXE_MASK                         (0x80000U)
#define CAN_IE_DRXE_SHIFT                        (19U)
#define CAN_IE_DRXE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_DRXE_SHIFT)) & CAN_IE_DRXE_MASK)
#define CAN_IE_BECE_MASK                         (0x100000U)
#define CAN_IE_BECE_SHIFT                        (20U)
#define CAN_IE_BECE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_BECE_SHIFT)) & CAN_IE_BECE_MASK)
#define CAN_IE_BEUE_MASK                         (0x200000U)
#define CAN_IE_BEUE_SHIFT                        (21U)
#define CAN_IE_BEUE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_BEUE_SHIFT)) & CAN_IE_BEUE_MASK)
#define CAN_IE_ELOE_MASK                         (0x400000U)
#define CAN_IE_ELOE_SHIFT                        (22U)
#define CAN_IE_ELOE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_ELOE_SHIFT)) & CAN_IE_ELOE_MASK)
#define CAN_IE_EPE_MASK                          (0x800000U)
#define CAN_IE_EPE_SHIFT                         (23U)
#define CAN_IE_EPE(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IE_EPE_SHIFT)) & CAN_IE_EPE_MASK)
#define CAN_IE_EWE_MASK                          (0x1000000U)
#define CAN_IE_EWE_SHIFT                         (24U)
#define CAN_IE_EWE(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IE_EWE_SHIFT)) & CAN_IE_EWE_MASK)
#define CAN_IE_BOE_MASK                          (0x2000000U)
#define CAN_IE_BOE_SHIFT                         (25U)
#define CAN_IE_BOE(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IE_BOE_SHIFT)) & CAN_IE_BOE_MASK)
#define CAN_IE_WDIE_MASK                         (0x4000000U)
#define CAN_IE_WDIE_SHIFT                        (26U)
#define CAN_IE_WDIE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_WDIE_SHIFT)) & CAN_IE_WDIE_MASK)
#define CAN_IE_PEAE_MASK                         (0x8000000U)
#define CAN_IE_PEAE_SHIFT                        (27U)
#define CAN_IE_PEAE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_PEAE_SHIFT)) & CAN_IE_PEAE_MASK)
#define CAN_IE_PEDE_MASK                         (0x10000000U)
#define CAN_IE_PEDE_SHIFT                        (28U)
#define CAN_IE_PEDE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_PEDE_SHIFT)) & CAN_IE_PEDE_MASK)
#define CAN_IE_ARAE_MASK                         (0x20000000U)
#define CAN_IE_ARAE_SHIFT                        (29U)
#define CAN_IE_ARAE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IE_ARAE_SHIFT)) & CAN_IE_ARAE_MASK)

/*! @name ILS - Interrupt Line Select */
#define CAN_ILS_RF0NL_MASK                       (0x1U)
#define CAN_ILS_RF0NL_SHIFT                      (0U)
#define CAN_ILS_RF0NL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF0NL_SHIFT)) & CAN_ILS_RF0NL_MASK)
#define CAN_ILS_RF0WL_MASK                       (0x2U)
#define CAN_ILS_RF0WL_SHIFT                      (1U)
#define CAN_ILS_RF0WL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF0WL_SHIFT)) & CAN_ILS_RF0WL_MASK)
#define CAN_ILS_RF0FL_MASK                       (0x4U)
#define CAN_ILS_RF0FL_SHIFT                      (2U)
#define CAN_ILS_RF0FL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF0FL_SHIFT)) & CAN_ILS_RF0FL_MASK)
#define CAN_ILS_RF0LL_MASK                       (0x8U)
#define CAN_ILS_RF0LL_SHIFT                      (3U)
#define CAN_ILS_RF0LL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF0LL_SHIFT)) & CAN_ILS_RF0LL_MASK)
#define CAN_ILS_RF1NL_MASK                       (0x10U)
#define CAN_ILS_RF1NL_SHIFT                      (4U)
#define CAN_ILS_RF1NL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF1NL_SHIFT)) & CAN_ILS_RF1NL_MASK)
#define CAN_ILS_RF1WL_MASK                       (0x20U)
#define CAN_ILS_RF1WL_SHIFT                      (5U)
#define CAN_ILS_RF1WL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF1WL_SHIFT)) & CAN_ILS_RF1WL_MASK)
#define CAN_ILS_RF1FL_MASK                       (0x40U)
#define CAN_ILS_RF1FL_SHIFT                      (6U)
#define CAN_ILS_RF1FL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF1FL_SHIFT)) & CAN_ILS_RF1FL_MASK)
#define CAN_ILS_RF1LL_MASK                       (0x80U)
#define CAN_ILS_RF1LL_SHIFT                      (7U)
#define CAN_ILS_RF1LL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_RF1LL_SHIFT)) & CAN_ILS_RF1LL_MASK)
#define CAN_ILS_HPML_MASK                        (0x100U)
#define CAN_ILS_HPML_SHIFT                       (8U)
#define CAN_ILS_HPML(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_HPML_SHIFT)) & CAN_ILS_HPML_MASK)
#define CAN_ILS_TCL_MASK                         (0x200U)
#define CAN_ILS_TCL_SHIFT                        (9U)
#define CAN_ILS_TCL(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TCL_SHIFT)) & CAN_ILS_TCL_MASK)
#define CAN_ILS_TCFL_MASK                        (0x400U)
#define CAN_ILS_TCFL_SHIFT                       (10U)
#define CAN_ILS_TCFL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TCFL_SHIFT)) & CAN_ILS_TCFL_MASK)
#define CAN_ILS_TFEL_MASK                        (0x800U)
#define CAN_ILS_TFEL_SHIFT                       (11U)
#define CAN_ILS_TFEL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TFEL_SHIFT)) & CAN_ILS_TFEL_MASK)
#define CAN_ILS_TEFNL_MASK                       (0x1000U)
#define CAN_ILS_TEFNL_SHIFT                      (12U)
#define CAN_ILS_TEFNL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TEFNL_SHIFT)) & CAN_ILS_TEFNL_MASK)
#define CAN_ILS_TEFWL_MASK                       (0x2000U)
#define CAN_ILS_TEFWL_SHIFT                      (13U)
#define CAN_ILS_TEFWL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TEFWL_SHIFT)) & CAN_ILS_TEFWL_MASK)
#define CAN_ILS_TEFFL_MASK                       (0x4000U)
#define CAN_ILS_TEFFL_SHIFT                      (14U)
#define CAN_ILS_TEFFL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TEFFL_SHIFT)) & CAN_ILS_TEFFL_MASK)
#define CAN_ILS_TEFLL_MASK                       (0x8000U)
#define CAN_ILS_TEFLL_SHIFT                      (15U)
#define CAN_ILS_TEFLL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TEFLL_SHIFT)) & CAN_ILS_TEFLL_MASK)
#define CAN_ILS_TSWL_MASK                        (0x10000U)
#define CAN_ILS_TSWL_SHIFT                       (16U)
#define CAN_ILS_TSWL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TSWL_SHIFT)) & CAN_ILS_TSWL_MASK)
#define CAN_ILS_MRAFL_MASK                       (0x20000U)
#define CAN_ILS_MRAFL_SHIFT                      (17U)
#define CAN_ILS_MRAFL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILS_MRAFL_SHIFT)) & CAN_ILS_MRAFL_MASK)
#define CAN_ILS_TOOL_MASK                        (0x40000U)
#define CAN_ILS_TOOL_SHIFT                       (18U)
#define CAN_ILS_TOOL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_TOOL_SHIFT)) & CAN_ILS_TOOL_MASK)
#define CAN_ILS_DRXL_MASK                        (0x80000U)
#define CAN_ILS_DRXL_SHIFT                       (19U)
#define CAN_ILS_DRXL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_DRXL_SHIFT)) & CAN_ILS_DRXL_MASK)
#define CAN_ILS_BECL_MASK                        (0x100000U)
#define CAN_ILS_BECL_SHIFT                       (20U)
#define CAN_ILS_BECL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_BECL_SHIFT)) & CAN_ILS_BECL_MASK)
#define CAN_ILS_BEUL_MASK                        (0x200000U)
#define CAN_ILS_BEUL_SHIFT                       (21U)
#define CAN_ILS_BEUL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_BEUL_SHIFT)) & CAN_ILS_BEUL_MASK)
#define CAN_ILS_ELOL_MASK                        (0x400000U)
#define CAN_ILS_ELOL_SHIFT                       (22U)
#define CAN_ILS_ELOL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_ELOL_SHIFT)) & CAN_ILS_ELOL_MASK)
#define CAN_ILS_EPL_MASK                         (0x800000U)
#define CAN_ILS_EPL_SHIFT                        (23U)
#define CAN_ILS_EPL(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ILS_EPL_SHIFT)) & CAN_ILS_EPL_MASK)
#define CAN_ILS_EWL_MASK                         (0x1000000U)
#define CAN_ILS_EWL_SHIFT                        (24U)
#define CAN_ILS_EWL(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ILS_EWL_SHIFT)) & CAN_ILS_EWL_MASK)
#define CAN_ILS_BOL_MASK                         (0x2000000U)
#define CAN_ILS_BOL_SHIFT                        (25U)
#define CAN_ILS_BOL(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ILS_BOL_SHIFT)) & CAN_ILS_BOL_MASK)
#define CAN_ILS_WDIL_MASK                        (0x4000000U)
#define CAN_ILS_WDIL_SHIFT                       (26U)
#define CAN_ILS_WDIL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_WDIL_SHIFT)) & CAN_ILS_WDIL_MASK)
#define CAN_ILS_PEAL_MASK                        (0x8000000U)
#define CAN_ILS_PEAL_SHIFT                       (27U)
#define CAN_ILS_PEAL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_PEAL_SHIFT)) & CAN_ILS_PEAL_MASK)
#define CAN_ILS_PEDL_MASK                        (0x10000000U)
#define CAN_ILS_PEDL_SHIFT                       (28U)
#define CAN_ILS_PEDL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_PEDL_SHIFT)) & CAN_ILS_PEDL_MASK)
#define CAN_ILS_ARAL_MASK                        (0x20000000U)
#define CAN_ILS_ARAL_SHIFT                       (29U)
#define CAN_ILS_ARAL(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ILS_ARAL_SHIFT)) & CAN_ILS_ARAL_MASK)

/*! @name ILE - Interrupt Line Enable */
#define CAN_ILE_EINT0_MASK                       (0x1U)
#define CAN_ILE_EINT0_SHIFT                      (0U)
#define CAN_ILE_EINT0(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILE_EINT0_SHIFT)) & CAN_ILE_EINT0_MASK)
#define CAN_ILE_EINT1_MASK                       (0x2U)
#define CAN_ILE_EINT1_SHIFT                      (1U)
#define CAN_ILE_EINT1(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ILE_EINT1_SHIFT)) & CAN_ILE_EINT1_MASK)

/*! @name GFC - Global Filter Configuration */
#define CAN_GFC_RRFE_MASK                        (0x1U)
#define CAN_GFC_RRFE_SHIFT                       (0U)
#define CAN_GFC_RRFE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_GFC_RRFE_SHIFT)) & CAN_GFC_RRFE_MASK)
#define CAN_GFC_RRFS_MASK                        (0x2U)
#define CAN_GFC_RRFS_SHIFT                       (1U)
#define CAN_GFC_RRFS(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_GFC_RRFS_SHIFT)) & CAN_GFC_RRFS_MASK)
#define CAN_GFC_ANFE_MASK                        (0xCU)
#define CAN_GFC_ANFE_SHIFT                       (2U)
#define CAN_GFC_ANFE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_GFC_ANFE_SHIFT)) & CAN_GFC_ANFE_MASK)
#define CAN_GFC_ANFS_MASK                        (0x30U)
#define CAN_GFC_ANFS_SHIFT                       (4U)
#define CAN_GFC_ANFS(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_GFC_ANFS_SHIFT)) & CAN_GFC_ANFS_MASK)

/*! @name SIDFC - Standard ID Filter Configuration */
#define CAN_SIDFC_FLSSA_MASK                     (0xFFFCU)
#define CAN_SIDFC_FLSSA_SHIFT                    (2U)
#define CAN_SIDFC_FLSSA(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_SIDFC_FLSSA_SHIFT)) & CAN_SIDFC_FLSSA_MASK)
#define CAN_SIDFC_LSS_MASK                       (0xFF0000U)
#define CAN_SIDFC_LSS_SHIFT                      (16U)
#define CAN_SIDFC_LSS(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_SIDFC_LSS_SHIFT)) & CAN_SIDFC_LSS_MASK)

/*! @name XIDFC - Extended ID Filter Configuration */
#define CAN_XIDFC_FLESA_MASK                     (0xFFFCU)
#define CAN_XIDFC_FLESA_SHIFT                    (2U)
#define CAN_XIDFC_FLESA(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_XIDFC_FLESA_SHIFT)) & CAN_XIDFC_FLESA_MASK)
#define CAN_XIDFC_LSE_MASK                       (0xFF0000U)
#define CAN_XIDFC_LSE_SHIFT                      (16U)
#define CAN_XIDFC_LSE(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_XIDFC_LSE_SHIFT)) & CAN_XIDFC_LSE_MASK)

/*! @name XIDAM - Extended ID AND Mask */
#define CAN_XIDAM_EIDM_MASK                      (0x1FFFFFFFU)
#define CAN_XIDAM_EIDM_SHIFT                     (0U)
#define CAN_XIDAM_EIDM(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_XIDAM_EIDM_SHIFT)) & CAN_XIDAM_EIDM_MASK)

/*! @name HPMS - High Priority Message Status */
#define CAN_HPMS_BIDX_MASK                       (0x3FU)
#define CAN_HPMS_BIDX_SHIFT                      (0U)
#define CAN_HPMS_BIDX(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_HPMS_BIDX_SHIFT)) & CAN_HPMS_BIDX_MASK)
#define CAN_HPMS_MSI_MASK                        (0xC0U)
#define CAN_HPMS_MSI_SHIFT                       (6U)
#define CAN_HPMS_MSI(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_HPMS_MSI_SHIFT)) & CAN_HPMS_MSI_MASK)
#define CAN_HPMS_FIDX_MASK                       (0x7F00U)
#define CAN_HPMS_FIDX_SHIFT                      (8U)
#define CAN_HPMS_FIDX(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_HPMS_FIDX_SHIFT)) & CAN_HPMS_FIDX_MASK)
#define CAN_HPMS_FLST_MASK                       (0x8000U)
#define CAN_HPMS_FLST_SHIFT                      (15U)
#define CAN_HPMS_FLST(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_HPMS_FLST_SHIFT)) & CAN_HPMS_FLST_MASK)

/*! @name NDAT1 - New Data 1 */
#define CAN_NDAT1_ND_MASK                        (0xFFFFFFFFU)
#define CAN_NDAT1_ND_SHIFT                       (0U)
#define CAN_NDAT1_ND(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_NDAT1_ND_SHIFT)) & CAN_NDAT1_ND_MASK)

/*! @name NDAT2 - New Data 2 */
#define CAN_NDAT2_ND_MASK                        (0xFFFFFFFFU)
#define CAN_NDAT2_ND_SHIFT                       (0U)
#define CAN_NDAT2_ND(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_NDAT2_ND_SHIFT)) & CAN_NDAT2_ND_MASK)

/*! @name RXF0C - Rx FIFO 0 Configuration */
#define CAN_RXF0C_F0SA_MASK                      (0xFFFCU)
#define CAN_RXF0C_F0SA_SHIFT                     (2U)
#define CAN_RXF0C_F0SA(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0C_F0SA_SHIFT)) & CAN_RXF0C_F0SA_MASK)
#define CAN_RXF0C_F0S_MASK                       (0x7F0000U)
#define CAN_RXF0C_F0S_SHIFT                      (16U)
#define CAN_RXF0C_F0S(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_RXF0C_F0S_SHIFT)) & CAN_RXF0C_F0S_MASK)
#define CAN_RXF0C_F0WM_MASK                      (0x7F000000U)
#define CAN_RXF0C_F0WM_SHIFT                     (24U)
#define CAN_RXF0C_F0WM(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0C_F0WM_SHIFT)) & CAN_RXF0C_F0WM_MASK)
#define CAN_RXF0C_F0OM_MASK                      (0x80000000U)
#define CAN_RXF0C_F0OM_SHIFT                     (31U)
#define CAN_RXF0C_F0OM(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0C_F0OM_SHIFT)) & CAN_RXF0C_F0OM_MASK)

/*! @name RXF0S - Rx FIFO 0 Status */
#define CAN_RXF0S_F0FL_MASK                      (0x7FU)
#define CAN_RXF0S_F0FL_SHIFT                     (0U)
#define CAN_RXF0S_F0FL(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0S_F0FL_SHIFT)) & CAN_RXF0S_F0FL_MASK)
#define CAN_RXF0S_F0GI_MASK                      (0x3F00U)
#define CAN_RXF0S_F0GI_SHIFT                     (8U)
#define CAN_RXF0S_F0GI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0S_F0GI_SHIFT)) & CAN_RXF0S_F0GI_MASK)
#define CAN_RXF0S_F0PI_MASK                      (0x3F0000U)
#define CAN_RXF0S_F0PI_SHIFT                     (16U)
#define CAN_RXF0S_F0PI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0S_F0PI_SHIFT)) & CAN_RXF0S_F0PI_MASK)
#define CAN_RXF0S_F0F_MASK                       (0x1000000U)
#define CAN_RXF0S_F0F_SHIFT                      (24U)
#define CAN_RXF0S_F0F(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_RXF0S_F0F_SHIFT)) & CAN_RXF0S_F0F_MASK)
#define CAN_RXF0S_RF0L_MASK                      (0x2000000U)
#define CAN_RXF0S_RF0L_SHIFT                     (25U)
#define CAN_RXF0S_RF0L(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0S_RF0L_SHIFT)) & CAN_RXF0S_RF0L_MASK)

/*! @name RXF0A - Rx FIFO 0 Acknowledge */
#define CAN_RXF0A_F0AI_MASK                      (0x3FU)
#define CAN_RXF0A_F0AI_SHIFT                     (0U)
#define CAN_RXF0A_F0AI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF0A_F0AI_SHIFT)) & CAN_RXF0A_F0AI_MASK)

/*! @name RXBC - Rx Buffer Configuration */
#define CAN_RXBC_RBSA_MASK                       (0xFFFCU)
#define CAN_RXBC_RBSA_SHIFT                      (2U)
#define CAN_RXBC_RBSA(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_RXBC_RBSA_SHIFT)) & CAN_RXBC_RBSA_MASK)

/*! @name RXF1C - Rx FIFO 1 Configuration */
#define CAN_RXF1C_F1SA_MASK                      (0xFFFCU)
#define CAN_RXF1C_F1SA_SHIFT                     (2U)
#define CAN_RXF1C_F1SA(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1C_F1SA_SHIFT)) & CAN_RXF1C_F1SA_MASK)
#define CAN_RXF1C_F1S_MASK                       (0x7F0000U)
#define CAN_RXF1C_F1S_SHIFT                      (16U)
#define CAN_RXF1C_F1S(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_RXF1C_F1S_SHIFT)) & CAN_RXF1C_F1S_MASK)
#define CAN_RXF1C_F1WM_MASK                      (0x7F000000U)
#define CAN_RXF1C_F1WM_SHIFT                     (24U)
#define CAN_RXF1C_F1WM(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1C_F1WM_SHIFT)) & CAN_RXF1C_F1WM_MASK)
#define CAN_RXF1C_F1OM_MASK                      (0x80000000U)
#define CAN_RXF1C_F1OM_SHIFT                     (31U)
#define CAN_RXF1C_F1OM(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1C_F1OM_SHIFT)) & CAN_RXF1C_F1OM_MASK)

/*! @name RXF1S - Rx FIFO 1 Status */
#define CAN_RXF1S_F1FL_MASK                      (0x7FU)
#define CAN_RXF1S_F1FL_SHIFT                     (0U)
#define CAN_RXF1S_F1FL(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1S_F1FL_SHIFT)) & CAN_RXF1S_F1FL_MASK)
#define CAN_RXF1S_F1GI_MASK                      (0x3F00U)
#define CAN_RXF1S_F1GI_SHIFT                     (8U)
#define CAN_RXF1S_F1GI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1S_F1GI_SHIFT)) & CAN_RXF1S_F1GI_MASK)
#define CAN_RXF1S_F1PI_MASK                      (0x3F0000U)
#define CAN_RXF1S_F1PI_SHIFT                     (16U)
#define CAN_RXF1S_F1PI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1S_F1PI_SHIFT)) & CAN_RXF1S_F1PI_MASK)
#define CAN_RXF1S_F1F_MASK                       (0x1000000U)
#define CAN_RXF1S_F1F_SHIFT                      (24U)
#define CAN_RXF1S_F1F(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_RXF1S_F1F_SHIFT)) & CAN_RXF1S_F1F_MASK)
#define CAN_RXF1S_RF1L_MASK                      (0x2000000U)
#define CAN_RXF1S_RF1L_SHIFT                     (25U)
#define CAN_RXF1S_RF1L(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1S_RF1L_SHIFT)) & CAN_RXF1S_RF1L_MASK)

/*! @name RXF1A - Rx FIFO 1 Acknowledge */
#define CAN_RXF1A_F1AI_MASK                      (0x3FU)
#define CAN_RXF1A_F1AI_SHIFT                     (0U)
#define CAN_RXF1A_F1AI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXF1A_F1AI_SHIFT)) & CAN_RXF1A_F1AI_MASK)

/*! @name RXESC - Rx Buffer and FIFO Element Size Configuration */
#define CAN_RXESC_F0DS_MASK                      (0x7U)
#define CAN_RXESC_F0DS_SHIFT                     (0U)
#define CAN_RXESC_F0DS(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXESC_F0DS_SHIFT)) & CAN_RXESC_F0DS_MASK)
#define CAN_RXESC_F1DS_MASK                      (0x70U)
#define CAN_RXESC_F1DS_SHIFT                     (4U)
#define CAN_RXESC_F1DS(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXESC_F1DS_SHIFT)) & CAN_RXESC_F1DS_MASK)
#define CAN_RXESC_RBDS_MASK                      (0x700U)
#define CAN_RXESC_RBDS_SHIFT                     (8U)
#define CAN_RXESC_RBDS(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_RXESC_RBDS_SHIFT)) & CAN_RXESC_RBDS_MASK)

/*! @name TXBC - Tx Buffer Configuration */
#define CAN_TXBC_TBSA_MASK                       (0xFFFCU)
#define CAN_TXBC_TBSA_SHIFT                      (2U)
#define CAN_TXBC_TBSA(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXBC_TBSA_SHIFT)) & CAN_TXBC_TBSA_MASK)
#define CAN_TXBC_NDTB_MASK                       (0x3F0000U)
#define CAN_TXBC_NDTB_SHIFT                      (16U)
#define CAN_TXBC_NDTB(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXBC_NDTB_SHIFT)) & CAN_TXBC_NDTB_MASK)
#define CAN_TXBC_TFQS_MASK                       (0x3F000000U)
#define CAN_TXBC_TFQS_SHIFT                      (24U)
#define CAN_TXBC_TFQS(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXBC_TFQS_SHIFT)) & CAN_TXBC_TFQS_MASK)
#define CAN_TXBC_TFQM_MASK                       (0x40000000U)
#define CAN_TXBC_TFQM_SHIFT                      (30U)
#define CAN_TXBC_TFQM(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXBC_TFQM_SHIFT)) & CAN_TXBC_TFQM_MASK)

/*! @name TXFQS - Tx FIFO/Queue Status */
#define CAN_TXFQS_TFGI_MASK                      (0x1F00U)
#define CAN_TXFQS_TFGI_SHIFT                     (8U)
#define CAN_TXFQS_TFGI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXFQS_TFGI_SHIFT)) & CAN_TXFQS_TFGI_MASK)
#define CAN_TXFQS_TFQPI_MASK                     (0x1F0000U)
#define CAN_TXFQS_TFQPI_SHIFT                    (16U)
#define CAN_TXFQS_TFQPI(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_TXFQS_TFQPI_SHIFT)) & CAN_TXFQS_TFQPI_MASK)
#define CAN_TXFQS_TFQF_MASK                      (0x200000U)
#define CAN_TXFQS_TFQF_SHIFT                     (21U)
#define CAN_TXFQS_TFQF(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXFQS_TFQF_SHIFT)) & CAN_TXFQS_TFQF_MASK)

/*! @name TXESC - Tx Buffer Element Size Configuration */
#define CAN_TXESC_TBDS_MASK                      (0x7U)
#define CAN_TXESC_TBDS_SHIFT                     (0U)
#define CAN_TXESC_TBDS(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXESC_TBDS_SHIFT)) & CAN_TXESC_TBDS_MASK)

/*! @name TXBRP - Tx Buffer Request Pending */
#define CAN_TXBRP_TRP_MASK                       (0xFFFFFFFFU)
#define CAN_TXBRP_TRP_SHIFT                      (0U)
#define CAN_TXBRP_TRP(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXBRP_TRP_SHIFT)) & CAN_TXBRP_TRP_MASK)

/*! @name TXBAR - Tx Buffer Add Request */
#define CAN_TXBAR_AR_MASK                        (0xFFFFFFFFU)
#define CAN_TXBAR_AR_SHIFT                       (0U)
#define CAN_TXBAR_AR(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TXBAR_AR_SHIFT)) & CAN_TXBAR_AR_MASK)

/*! @name TXBCR - Tx Buffer Cancellation Request */
#define CAN_TXBCR_CR_MASK                        (0xFFFFFFFFU)
#define CAN_TXBCR_CR_SHIFT                       (0U)
#define CAN_TXBCR_CR(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TXBCR_CR_SHIFT)) & CAN_TXBCR_CR_MASK)

/*! @name TXBTO - Tx Buffer Transmission Occurred */
#define CAN_TXBTO_TO_MASK                        (0xFFFFFFFFU)
#define CAN_TXBTO_TO_SHIFT                       (0U)
#define CAN_TXBTO_TO(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TXBTO_TO_SHIFT)) & CAN_TXBTO_TO_MASK)

/*! @name TXBCF - Tx Buffer Cancellation Finished */
#define CAN_TXBCF_TO_MASK                        (0xFFFFFFFFU)
#define CAN_TXBCF_TO_SHIFT                       (0U)
#define CAN_TXBCF_TO(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_TXBCF_TO_SHIFT)) & CAN_TXBCF_TO_MASK)

/*! @name TXBTIE - Tx Buffer Transmission Interrupt Enable */
#define CAN_TXBTIE_TIE_MASK                      (0xFFFFFFFFU)
#define CAN_TXBTIE_TIE_SHIFT                     (0U)
#define CAN_TXBTIE_TIE(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXBTIE_TIE_SHIFT)) & CAN_TXBTIE_TIE_MASK)

/*! @name TXBCIE - Tx Buffer Cancellation Finished Interrupt Enable */
#define CAN_TXBCIE_CFIE_MASK                     (0xFFFFFFFFU)
#define CAN_TXBCIE_CFIE_SHIFT                    (0U)
#define CAN_TXBCIE_CFIE(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_TXBCIE_CFIE_SHIFT)) & CAN_TXBCIE_CFIE_MASK)

/*! @name TXEFC - Tx Event FIFO Configuration */
#define CAN_TXEFC_EFSA_MASK                      (0xFFFCU)
#define CAN_TXEFC_EFSA_SHIFT                     (2U)
#define CAN_TXEFC_EFSA(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFC_EFSA_SHIFT)) & CAN_TXEFC_EFSA_MASK)
#define CAN_TXEFC_EFS_MASK                       (0x3F0000U)
#define CAN_TXEFC_EFS_SHIFT                      (16U)
#define CAN_TXEFC_EFS(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXEFC_EFS_SHIFT)) & CAN_TXEFC_EFS_MASK)
#define CAN_TXEFC_EFWM_MASK                      (0x3F000000U)
#define CAN_TXEFC_EFWM_SHIFT                     (24U)
#define CAN_TXEFC_EFWM(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFC_EFWM_SHIFT)) & CAN_TXEFC_EFWM_MASK)

/*! @name TXEFS - Tx Event FIFO Status */
#define CAN_TXEFS_EFFL_MASK                      (0x3FU)
#define CAN_TXEFS_EFFL_SHIFT                     (0U)
#define CAN_TXEFS_EFFL(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFS_EFFL_SHIFT)) & CAN_TXEFS_EFFL_MASK)
#define CAN_TXEFS_EFGI_MASK                      (0x1F00U)
#define CAN_TXEFS_EFGI_SHIFT                     (8U)
#define CAN_TXEFS_EFGI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFS_EFGI_SHIFT)) & CAN_TXEFS_EFGI_MASK)
#define CAN_TXEFS_EFPI_MASK                      (0x3F0000U)
#define CAN_TXEFS_EFPI_SHIFT                     (16U)
#define CAN_TXEFS_EFPI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFS_EFPI_SHIFT)) & CAN_TXEFS_EFPI_MASK)
#define CAN_TXEFS_EFF_MASK                       (0x1000000U)
#define CAN_TXEFS_EFF_SHIFT                      (24U)
#define CAN_TXEFS_EFF(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_TXEFS_EFF_SHIFT)) & CAN_TXEFS_EFF_MASK)
#define CAN_TXEFS_TEFL_MASK                      (0x2000000U)
#define CAN_TXEFS_TEFL_SHIFT                     (25U)
#define CAN_TXEFS_TEFL(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFS_TEFL_SHIFT)) & CAN_TXEFS_TEFL_MASK)

/*! @name TXEFA - Tx Event FIFO Acknowledge */
#define CAN_TXEFA_EFAI_MASK                      (0x1FU)
#define CAN_TXEFA_EFAI_SHIFT                     (0U)
#define CAN_TXEFA_EFAI(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXEFA_EFAI_SHIFT)) & CAN_TXEFA_EFAI_MASK)

/*! @name MRBA - CAN Message RAM Base Address */
#define CAN_MRBA_BA_MASK                         (0xFFFFFFFFU)
#define CAN_MRBA_BA_SHIFT                        (0U)
#define CAN_MRBA_BA(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_MRBA_BA_SHIFT)) & CAN_MRBA_BA_MASK)

/*! @name ETSCC - External Timestamp Counter Configuration */
#define CAN_ETSCC_ETCP_MASK                      (0x7FFU)
#define CAN_ETSCC_ETCP_SHIFT                     (0U)
#define CAN_ETSCC_ETCP(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_ETSCC_ETCP_SHIFT)) & CAN_ETSCC_ETCP_MASK)
#define CAN_ETSCC_ETCE_MASK                      (0x80000000U)
#define CAN_ETSCC_ETCE_SHIFT                     (31U)
#define CAN_ETSCC_ETCE(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_ETSCC_ETCE_SHIFT)) & CAN_ETSCC_ETCE_MASK)

/*! @name ETSCV - External Timestamp Counter Value */
#define CAN_ETSCV_ETSC_MASK                      (0xFFFFU)
#define CAN_ETSCV_ETSC_SHIFT                     (0U)
#define CAN_ETSCV_ETSC(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_ETSCV_ETSC_SHIFT)) & CAN_ETSCV_ETSC_MASK)


/*!
 * @}
 */ /* end of group CAN_Register_Masks */


/* CAN - Peripheral instance base addresses */
/** Peripheral CAN0 base address */
#define CAN0_BASE                                (0x4009D000u)
/** Peripheral CAN0 base pointer */
#define CAN0                                     ((CAN_Type *)CAN0_BASE)
/** Peripheral CAN1 base address */
#define CAN1_BASE                                (0x4009E000u)
/** Peripheral CAN1 base pointer */
#define CAN1                                     ((CAN_Type *)CAN1_BASE)
/** Array initializer of CAN peripheral base addresses */
#define CAN_BASE_ADDRS                           { CAN0_BASE, CAN1_BASE }
/** Array initializer of CAN peripheral base pointers */
#define CAN_BASE_PTRS                            { CAN0, CAN1 }
/** Interrupt vectors for the CAN peripheral type */
#define CAN_IRQS                                 { { CAN0_IRQ0_IRQn, CAN0_IRQ1_IRQn }, { CAN1_IRQ0_IRQn, CAN1_IRQ1_IRQn } }

/*!
 * @}
 */ /* end of group CAN_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CRC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Peripheral_Access_Layer CRC Peripheral Access Layer
 * @{
 */

/** CRC - Register Layout Typedef */
typedef struct {
  __IO uint32_t MODE;                              /**< CRC mode register, offset: 0x0 */
  __IO uint32_t SEED;                              /**< CRC seed register, offset: 0x4 */
  union {                                          /* offset: 0x8 */
    __I  uint32_t SUM;                               /**< CRC checksum register, offset: 0x8 */
    __O  uint32_t WR_DATA;                           /**< CRC data register, offset: 0x8 */
  };
} CRC_Type;

/* ----------------------------------------------------------------------------
   -- CRC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Masks CRC Register Masks
 * @{
 */

/*! @name MODE - CRC mode register */
#define CRC_MODE_CRC_POLY_MASK                   (0x3U)
#define CRC_MODE_CRC_POLY_SHIFT                  (0U)
#define CRC_MODE_CRC_POLY(x)                     (((uint32_t)(((uint32_t)(x)) << CRC_MODE_CRC_POLY_SHIFT)) & CRC_MODE_CRC_POLY_MASK)
#define CRC_MODE_BIT_RVS_WR_MASK                 (0x4U)
#define CRC_MODE_BIT_RVS_WR_SHIFT                (2U)
#define CRC_MODE_BIT_RVS_WR(x)                   (((uint32_t)(((uint32_t)(x)) << CRC_MODE_BIT_RVS_WR_SHIFT)) & CRC_MODE_BIT_RVS_WR_MASK)
#define CRC_MODE_CMPL_WR_MASK                    (0x8U)
#define CRC_MODE_CMPL_WR_SHIFT                   (3U)
#define CRC_MODE_CMPL_WR(x)                      (((uint32_t)(((uint32_t)(x)) << CRC_MODE_CMPL_WR_SHIFT)) & CRC_MODE_CMPL_WR_MASK)
#define CRC_MODE_BIT_RVS_SUM_MASK                (0x10U)
#define CRC_MODE_BIT_RVS_SUM_SHIFT               (4U)
#define CRC_MODE_BIT_RVS_SUM(x)                  (((uint32_t)(((uint32_t)(x)) << CRC_MODE_BIT_RVS_SUM_SHIFT)) & CRC_MODE_BIT_RVS_SUM_MASK)
#define CRC_MODE_CMPL_SUM_MASK                   (0x20U)
#define CRC_MODE_CMPL_SUM_SHIFT                  (5U)
#define CRC_MODE_CMPL_SUM(x)                     (((uint32_t)(((uint32_t)(x)) << CRC_MODE_CMPL_SUM_SHIFT)) & CRC_MODE_CMPL_SUM_MASK)

/*! @name SEED - CRC seed register */
#define CRC_SEED_CRC_SEED_MASK                   (0xFFFFFFFFU)
#define CRC_SEED_CRC_SEED_SHIFT                  (0U)
#define CRC_SEED_CRC_SEED(x)                     (((uint32_t)(((uint32_t)(x)) << CRC_SEED_CRC_SEED_SHIFT)) & CRC_SEED_CRC_SEED_MASK)

/*! @name SUM - CRC checksum register */
#define CRC_SUM_CRC_SUM_MASK                     (0xFFFFFFFFU)
#define CRC_SUM_CRC_SUM_SHIFT                    (0U)
#define CRC_SUM_CRC_SUM(x)                       (((uint32_t)(((uint32_t)(x)) << CRC_SUM_CRC_SUM_SHIFT)) & CRC_SUM_CRC_SUM_MASK)

/*! @name WR_DATA - CRC data register */
#define CRC_WR_DATA_CRC_WR_DATA_MASK             (0xFFFFFFFFU)
#define CRC_WR_DATA_CRC_WR_DATA_SHIFT            (0U)
#define CRC_WR_DATA_CRC_WR_DATA(x)               (((uint32_t)(((uint32_t)(x)) << CRC_WR_DATA_CRC_WR_DATA_SHIFT)) & CRC_WR_DATA_CRC_WR_DATA_MASK)


/*!
 * @}
 */ /* end of group CRC_Register_Masks */


/* CRC - Peripheral instance base addresses */
/** Peripheral CRC_ENGINE base address */
#define CRC_ENGINE_BASE                          (0x40095000u)
/** Peripheral CRC_ENGINE base pointer */
#define CRC_ENGINE                               ((CRC_Type *)CRC_ENGINE_BASE)
/** Array initializer of CRC peripheral base addresses */
#define CRC_BASE_ADDRS                           { CRC_ENGINE_BASE }
/** Array initializer of CRC peripheral base pointers */
#define CRC_BASE_PTRS                            { CRC_ENGINE }

/*!
 * @}
 */ /* end of group CRC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CTIMER Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CTIMER_Peripheral_Access_Layer CTIMER Peripheral Access Layer
 * @{
 */

/** CTIMER - Register Layout Typedef */
typedef struct {
  __IO uint32_t IR;                                /**< Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending., offset: 0x0 */
  __IO uint32_t TCR;                               /**< Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR., offset: 0x4 */
  __IO uint32_t TC;                                /**< Timer Counter, offset: 0x8 */
  __IO uint32_t PR;                                /**< Prescale Register, offset: 0xC */
  __IO uint32_t PC;                                /**< Prescale Counter, offset: 0x10 */
  __IO uint32_t MCR;                               /**< Match Control Register, offset: 0x14 */
  __IO uint32_t MR[4];                             /**< Match Register . MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC., array offset: 0x18, array step: 0x4 */
  __IO uint32_t CCR;                               /**< Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place., offset: 0x28 */
  __I  uint32_t CR[4];                             /**< Capture Register . CR is loaded with the value of TC when there is an event on the CAPn. input., array offset: 0x2C, array step: 0x4 */
  __IO uint32_t EMR;                               /**< External Match Register. The EMR controls the match function and the external match pins., offset: 0x3C */
       uint8_t RESERVED_0[48];
  __IO uint32_t CTCR;                              /**< Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting., offset: 0x70 */
  __IO uint32_t PWMC;                              /**< PWM Control Register. The PWMCON enables PWM mode for the external match pins., offset: 0x74 */
  __IO uint32_t MSR[4];                            /**< Match Shadow Register, array offset: 0x78, array step: 0x4 */
} CTIMER_Type;

/* ----------------------------------------------------------------------------
   -- CTIMER Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CTIMER_Register_Masks CTIMER Register Masks
 * @{
 */

/*! @name IR - Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending. */
#define CTIMER_IR_MR0INT_MASK                    (0x1U)
#define CTIMER_IR_MR0INT_SHIFT                   (0U)
#define CTIMER_IR_MR0INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_MR0INT_SHIFT)) & CTIMER_IR_MR0INT_MASK)
#define CTIMER_IR_MR1INT_MASK                    (0x2U)
#define CTIMER_IR_MR1INT_SHIFT                   (1U)
#define CTIMER_IR_MR1INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_MR1INT_SHIFT)) & CTIMER_IR_MR1INT_MASK)
#define CTIMER_IR_MR2INT_MASK                    (0x4U)
#define CTIMER_IR_MR2INT_SHIFT                   (2U)
#define CTIMER_IR_MR2INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_MR2INT_SHIFT)) & CTIMER_IR_MR2INT_MASK)
#define CTIMER_IR_MR3INT_MASK                    (0x8U)
#define CTIMER_IR_MR3INT_SHIFT                   (3U)
#define CTIMER_IR_MR3INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_MR3INT_SHIFT)) & CTIMER_IR_MR3INT_MASK)
#define CTIMER_IR_CR0INT_MASK                    (0x10U)
#define CTIMER_IR_CR0INT_SHIFT                   (4U)
#define CTIMER_IR_CR0INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_CR0INT_SHIFT)) & CTIMER_IR_CR0INT_MASK)
#define CTIMER_IR_CR1INT_MASK                    (0x20U)
#define CTIMER_IR_CR1INT_SHIFT                   (5U)
#define CTIMER_IR_CR1INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_CR1INT_SHIFT)) & CTIMER_IR_CR1INT_MASK)
#define CTIMER_IR_CR2INT_MASK                    (0x40U)
#define CTIMER_IR_CR2INT_SHIFT                   (6U)
#define CTIMER_IR_CR2INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_CR2INT_SHIFT)) & CTIMER_IR_CR2INT_MASK)
#define CTIMER_IR_CR3INT_MASK                    (0x80U)
#define CTIMER_IR_CR3INT_SHIFT                   (7U)
#define CTIMER_IR_CR3INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_CR3INT_SHIFT)) & CTIMER_IR_CR3INT_MASK)

/*! @name TCR - Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR. */
#define CTIMER_TCR_CEN_MASK                      (0x1U)
#define CTIMER_TCR_CEN_SHIFT                     (0U)
#define CTIMER_TCR_CEN(x)                        (((uint32_t)(((uint32_t)(x)) << CTIMER_TCR_CEN_SHIFT)) & CTIMER_TCR_CEN_MASK)
#define CTIMER_TCR_CRST_MASK                     (0x2U)
#define CTIMER_TCR_CRST_SHIFT                    (1U)
#define CTIMER_TCR_CRST(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_TCR_CRST_SHIFT)) & CTIMER_TCR_CRST_MASK)

/*! @name TC - Timer Counter */
#define CTIMER_TC_TCVAL_MASK                     (0xFFFFFFFFU)
#define CTIMER_TC_TCVAL_SHIFT                    (0U)
#define CTIMER_TC_TCVAL(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_TC_TCVAL_SHIFT)) & CTIMER_TC_TCVAL_MASK)

/*! @name PR - Prescale Register */
#define CTIMER_PR_PRVAL_MASK                     (0xFFFFFFFFU)
#define CTIMER_PR_PRVAL_SHIFT                    (0U)
#define CTIMER_PR_PRVAL(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_PR_PRVAL_SHIFT)) & CTIMER_PR_PRVAL_MASK)

/*! @name PC - Prescale Counter */
#define CTIMER_PC_PCVAL_MASK                     (0xFFFFFFFFU)
#define CTIMER_PC_PCVAL_SHIFT                    (0U)
#define CTIMER_PC_PCVAL(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_PC_PCVAL_SHIFT)) & CTIMER_PC_PCVAL_MASK)

/*! @name MCR - Match Control Register */
#define CTIMER_MCR_MR0I_MASK                     (0x1U)
#define CTIMER_MCR_MR0I_SHIFT                    (0U)
#define CTIMER_MCR_MR0I(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR0I_SHIFT)) & CTIMER_MCR_MR0I_MASK)
#define CTIMER_MCR_MR0R_MASK                     (0x2U)
#define CTIMER_MCR_MR0R_SHIFT                    (1U)
#define CTIMER_MCR_MR0R(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR0R_SHIFT)) & CTIMER_MCR_MR0R_MASK)
#define CTIMER_MCR_MR0S_MASK                     (0x4U)
#define CTIMER_MCR_MR0S_SHIFT                    (2U)
#define CTIMER_MCR_MR0S(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR0S_SHIFT)) & CTIMER_MCR_MR0S_MASK)
#define CTIMER_MCR_MR1I_MASK                     (0x8U)
#define CTIMER_MCR_MR1I_SHIFT                    (3U)
#define CTIMER_MCR_MR1I(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR1I_SHIFT)) & CTIMER_MCR_MR1I_MASK)
#define CTIMER_MCR_MR1R_MASK                     (0x10U)
#define CTIMER_MCR_MR1R_SHIFT                    (4U)
#define CTIMER_MCR_MR1R(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR1R_SHIFT)) & CTIMER_MCR_MR1R_MASK)
#define CTIMER_MCR_MR1S_MASK                     (0x20U)
#define CTIMER_MCR_MR1S_SHIFT                    (5U)
#define CTIMER_MCR_MR1S(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR1S_SHIFT)) & CTIMER_MCR_MR1S_MASK)
#define CTIMER_MCR_MR2I_MASK                     (0x40U)
#define CTIMER_MCR_MR2I_SHIFT                    (6U)
#define CTIMER_MCR_MR2I(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR2I_SHIFT)) & CTIMER_MCR_MR2I_MASK)
#define CTIMER_MCR_MR2R_MASK                     (0x80U)
#define CTIMER_MCR_MR2R_SHIFT                    (7U)
#define CTIMER_MCR_MR2R(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR2R_SHIFT)) & CTIMER_MCR_MR2R_MASK)
#define CTIMER_MCR_MR2S_MASK                     (0x100U)
#define CTIMER_MCR_MR2S_SHIFT                    (8U)
#define CTIMER_MCR_MR2S(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR2S_SHIFT)) & CTIMER_MCR_MR2S_MASK)
#define CTIMER_MCR_MR3I_MASK                     (0x200U)
#define CTIMER_MCR_MR3I_SHIFT                    (9U)
#define CTIMER_MCR_MR3I(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR3I_SHIFT)) & CTIMER_MCR_MR3I_MASK)
#define CTIMER_MCR_MR3R_MASK                     (0x400U)
#define CTIMER_MCR_MR3R_SHIFT                    (10U)
#define CTIMER_MCR_MR3R(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR3R_SHIFT)) & CTIMER_MCR_MR3R_MASK)
#define CTIMER_MCR_MR3S_MASK                     (0x800U)
#define CTIMER_MCR_MR3S_SHIFT                    (11U)
#define CTIMER_MCR_MR3S(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR3S_SHIFT)) & CTIMER_MCR_MR3S_MASK)
#define CTIMER_MCR_MR0RL_MASK                    (0x1000000U)
#define CTIMER_MCR_MR0RL_SHIFT                   (24U)
#define CTIMER_MCR_MR0RL(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR0RL_SHIFT)) & CTIMER_MCR_MR0RL_MASK)
#define CTIMER_MCR_MR1RL_MASK                    (0x2000000U)
#define CTIMER_MCR_MR1RL_SHIFT                   (25U)
#define CTIMER_MCR_MR1RL(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR1RL_SHIFT)) & CTIMER_MCR_MR1RL_MASK)
#define CTIMER_MCR_MR2RL_MASK                    (0x4000000U)
#define CTIMER_MCR_MR2RL_SHIFT                   (26U)
#define CTIMER_MCR_MR2RL(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR2RL_SHIFT)) & CTIMER_MCR_MR2RL_MASK)
#define CTIMER_MCR_MR3RL_MASK                    (0x8000000U)
#define CTIMER_MCR_MR3RL_SHIFT                   (27U)
#define CTIMER_MCR_MR3RL(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR3RL_SHIFT)) & CTIMER_MCR_MR3RL_MASK)

/*! @name MR - Match Register . MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC. */
#define CTIMER_MR_MATCH_MASK                     (0xFFFFFFFFU)
#define CTIMER_MR_MATCH_SHIFT                    (0U)
#define CTIMER_MR_MATCH(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MR_MATCH_SHIFT)) & CTIMER_MR_MATCH_MASK)

/* The count of CTIMER_MR */
#define CTIMER_MR_COUNT                          (4U)

/*! @name CCR - Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place. */
#define CTIMER_CCR_CAP0RE_MASK                   (0x1U)
#define CTIMER_CCR_CAP0RE_SHIFT                  (0U)
#define CTIMER_CCR_CAP0RE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP0RE_SHIFT)) & CTIMER_CCR_CAP0RE_MASK)
#define CTIMER_CCR_CAP0FE_MASK                   (0x2U)
#define CTIMER_CCR_CAP0FE_SHIFT                  (1U)
#define CTIMER_CCR_CAP0FE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP0FE_SHIFT)) & CTIMER_CCR_CAP0FE_MASK)
#define CTIMER_CCR_CAP0I_MASK                    (0x4U)
#define CTIMER_CCR_CAP0I_SHIFT                   (2U)
#define CTIMER_CCR_CAP0I(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP0I_SHIFT)) & CTIMER_CCR_CAP0I_MASK)
#define CTIMER_CCR_CAP1RE_MASK                   (0x8U)
#define CTIMER_CCR_CAP1RE_SHIFT                  (3U)
#define CTIMER_CCR_CAP1RE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP1RE_SHIFT)) & CTIMER_CCR_CAP1RE_MASK)
#define CTIMER_CCR_CAP1FE_MASK                   (0x10U)
#define CTIMER_CCR_CAP1FE_SHIFT                  (4U)
#define CTIMER_CCR_CAP1FE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP1FE_SHIFT)) & CTIMER_CCR_CAP1FE_MASK)
#define CTIMER_CCR_CAP1I_MASK                    (0x20U)
#define CTIMER_CCR_CAP1I_SHIFT                   (5U)
#define CTIMER_CCR_CAP1I(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP1I_SHIFT)) & CTIMER_CCR_CAP1I_MASK)
#define CTIMER_CCR_CAP2RE_MASK                   (0x40U)
#define CTIMER_CCR_CAP2RE_SHIFT                  (6U)
#define CTIMER_CCR_CAP2RE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP2RE_SHIFT)) & CTIMER_CCR_CAP2RE_MASK)
#define CTIMER_CCR_CAP2FE_MASK                   (0x80U)
#define CTIMER_CCR_CAP2FE_SHIFT                  (7U)
#define CTIMER_CCR_CAP2FE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP2FE_SHIFT)) & CTIMER_CCR_CAP2FE_MASK)
#define CTIMER_CCR_CAP2I_MASK                    (0x100U)
#define CTIMER_CCR_CAP2I_SHIFT                   (8U)
#define CTIMER_CCR_CAP2I(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP2I_SHIFT)) & CTIMER_CCR_CAP2I_MASK)
#define CTIMER_CCR_CAP3RE_MASK                   (0x200U)
#define CTIMER_CCR_CAP3RE_SHIFT                  (9U)
#define CTIMER_CCR_CAP3RE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP3RE_SHIFT)) & CTIMER_CCR_CAP3RE_MASK)
#define CTIMER_CCR_CAP3FE_MASK                   (0x400U)
#define CTIMER_CCR_CAP3FE_SHIFT                  (10U)
#define CTIMER_CCR_CAP3FE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP3FE_SHIFT)) & CTIMER_CCR_CAP3FE_MASK)
#define CTIMER_CCR_CAP3I_MASK                    (0x800U)
#define CTIMER_CCR_CAP3I_SHIFT                   (11U)
#define CTIMER_CCR_CAP3I(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP3I_SHIFT)) & CTIMER_CCR_CAP3I_MASK)

/*! @name CR - Capture Register . CR is loaded with the value of TC when there is an event on the CAPn. input. */
#define CTIMER_CR_CAP_MASK                       (0xFFFFFFFFU)
#define CTIMER_CR_CAP_SHIFT                      (0U)
#define CTIMER_CR_CAP(x)                         (((uint32_t)(((uint32_t)(x)) << CTIMER_CR_CAP_SHIFT)) & CTIMER_CR_CAP_MASK)

/* The count of CTIMER_CR */
#define CTIMER_CR_COUNT                          (4U)

/*! @name EMR - External Match Register. The EMR controls the match function and the external match pins. */
#define CTIMER_EMR_EM0_MASK                      (0x1U)
#define CTIMER_EMR_EM0_SHIFT                     (0U)
#define CTIMER_EMR_EM0(x)                        (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EM0_SHIFT)) & CTIMER_EMR_EM0_MASK)
#define CTIMER_EMR_EM1_MASK                      (0x2U)
#define CTIMER_EMR_EM1_SHIFT                     (1U)
#define CTIMER_EMR_EM1(x)                        (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EM1_SHIFT)) & CTIMER_EMR_EM1_MASK)
#define CTIMER_EMR_EM2_MASK                      (0x4U)
#define CTIMER_EMR_EM2_SHIFT                     (2U)
#define CTIMER_EMR_EM2(x)                        (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EM2_SHIFT)) & CTIMER_EMR_EM2_MASK)
#define CTIMER_EMR_EM3_MASK                      (0x8U)
#define CTIMER_EMR_EM3_SHIFT                     (3U)
#define CTIMER_EMR_EM3(x)                        (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EM3_SHIFT)) & CTIMER_EMR_EM3_MASK)
#define CTIMER_EMR_EMC0_MASK                     (0x30U)
#define CTIMER_EMR_EMC0_SHIFT                    (4U)
#define CTIMER_EMR_EMC0(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EMC0_SHIFT)) & CTIMER_EMR_EMC0_MASK)
#define CTIMER_EMR_EMC1_MASK                     (0xC0U)
#define CTIMER_EMR_EMC1_SHIFT                    (6U)
#define CTIMER_EMR_EMC1(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EMC1_SHIFT)) & CTIMER_EMR_EMC1_MASK)
#define CTIMER_EMR_EMC2_MASK                     (0x300U)
#define CTIMER_EMR_EMC2_SHIFT                    (8U)
#define CTIMER_EMR_EMC2(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EMC2_SHIFT)) & CTIMER_EMR_EMC2_MASK)
#define CTIMER_EMR_EMC3_MASK                     (0xC00U)
#define CTIMER_EMR_EMC3_SHIFT                    (10U)
#define CTIMER_EMR_EMC3(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EMC3_SHIFT)) & CTIMER_EMR_EMC3_MASK)

/*! @name CTCR - Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting. */
#define CTIMER_CTCR_CTMODE_MASK                  (0x3U)
#define CTIMER_CTCR_CTMODE_SHIFT                 (0U)
#define CTIMER_CTCR_CTMODE(x)                    (((uint32_t)(((uint32_t)(x)) << CTIMER_CTCR_CTMODE_SHIFT)) & CTIMER_CTCR_CTMODE_MASK)
#define CTIMER_CTCR_CINSEL_MASK                  (0xCU)
#define CTIMER_CTCR_CINSEL_SHIFT                 (2U)
#define CTIMER_CTCR_CINSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CTIMER_CTCR_CINSEL_SHIFT)) & CTIMER_CTCR_CINSEL_MASK)
#define CTIMER_CTCR_ENCC_MASK                    (0x10U)
#define CTIMER_CTCR_ENCC_SHIFT                   (4U)
#define CTIMER_CTCR_ENCC(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_CTCR_ENCC_SHIFT)) & CTIMER_CTCR_ENCC_MASK)
#define CTIMER_CTCR_SELCC_MASK                   (0xE0U)
#define CTIMER_CTCR_SELCC_SHIFT                  (5U)
#define CTIMER_CTCR_SELCC(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CTCR_SELCC_SHIFT)) & CTIMER_CTCR_SELCC_MASK)

/*! @name PWMC - PWM Control Register. The PWMCON enables PWM mode for the external match pins. */
#define CTIMER_PWMC_PWMEN0_MASK                  (0x1U)
#define CTIMER_PWMC_PWMEN0_SHIFT                 (0U)
#define CTIMER_PWMC_PWMEN0(x)                    (((uint32_t)(((uint32_t)(x)) << CTIMER_PWMC_PWMEN0_SHIFT)) & CTIMER_PWMC_PWMEN0_MASK)
#define CTIMER_PWMC_PWMEN1_MASK                  (0x2U)
#define CTIMER_PWMC_PWMEN1_SHIFT                 (1U)
#define CTIMER_PWMC_PWMEN1(x)                    (((uint32_t)(((uint32_t)(x)) << CTIMER_PWMC_PWMEN1_SHIFT)) & CTIMER_PWMC_PWMEN1_MASK)
#define CTIMER_PWMC_PWMEN2_MASK                  (0x4U)
#define CTIMER_PWMC_PWMEN2_SHIFT                 (2U)
#define CTIMER_PWMC_PWMEN2(x)                    (((uint32_t)(((uint32_t)(x)) << CTIMER_PWMC_PWMEN2_SHIFT)) & CTIMER_PWMC_PWMEN2_MASK)
#define CTIMER_PWMC_PWMEN3_MASK                  (0x8U)
#define CTIMER_PWMC_PWMEN3_SHIFT                 (3U)
#define CTIMER_PWMC_PWMEN3(x)                    (((uint32_t)(((uint32_t)(x)) << CTIMER_PWMC_PWMEN3_SHIFT)) & CTIMER_PWMC_PWMEN3_MASK)

/*! @name MSR - Match Shadow Register */
#define CTIMER_MSR_SHADOWW_MASK                  (0xFFFFFFFFU)
#define CTIMER_MSR_SHADOWW_SHIFT                 (0U)
#define CTIMER_MSR_SHADOWW(x)                    (((uint32_t)(((uint32_t)(x)) << CTIMER_MSR_SHADOWW_SHIFT)) & CTIMER_MSR_SHADOWW_MASK)

/* The count of CTIMER_MSR */
#define CTIMER_MSR_COUNT                         (4U)


/*!
 * @}
 */ /* end of group CTIMER_Register_Masks */


/* CTIMER - Peripheral instance base addresses */
/** Peripheral CTIMER0 base address */
#define CTIMER0_BASE                             (0x40008000u)
/** Peripheral CTIMER0 base pointer */
#define CTIMER0                                  ((CTIMER_Type *)CTIMER0_BASE)
/** Peripheral CTIMER1 base address */
#define CTIMER1_BASE                             (0x40009000u)
/** Peripheral CTIMER1 base pointer */
#define CTIMER1                                  ((CTIMER_Type *)CTIMER1_BASE)
/** Peripheral CTIMER2 base address */
#define CTIMER2_BASE                             (0x40028000u)
/** Peripheral CTIMER2 base pointer */
#define CTIMER2                                  ((CTIMER_Type *)CTIMER2_BASE)
/** Peripheral CTIMER3 base address */
#define CTIMER3_BASE                             (0x40048000u)
/** Peripheral CTIMER3 base pointer */
#define CTIMER3                                  ((CTIMER_Type *)CTIMER3_BASE)
/** Peripheral CTIMER4 base address */
#define CTIMER4_BASE                             (0x40049000u)
/** Peripheral CTIMER4 base pointer */
#define CTIMER4                                  ((CTIMER_Type *)CTIMER4_BASE)
/** Array initializer of CTIMER peripheral base addresses */
#define CTIMER_BASE_ADDRS                        { CTIMER0_BASE, CTIMER1_BASE, CTIMER2_BASE, CTIMER3_BASE, CTIMER4_BASE }
/** Array initializer of CTIMER peripheral base pointers */
#define CTIMER_BASE_PTRS                         { CTIMER0, CTIMER1, CTIMER2, CTIMER3, CTIMER4 }
/** Interrupt vectors for the CTIMER peripheral type */
#define CTIMER_IRQS                              { CTIMER0_IRQn, CTIMER1_IRQn, CTIMER2_IRQn, CTIMER3_IRQn, CTIMER4_IRQn }

/*!
 * @}
 */ /* end of group CTIMER_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- DMA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Peripheral_Access_Layer DMA Peripheral Access Layer
 * @{
 */

/** DMA - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< DMA control., offset: 0x0 */
  __I  uint32_t INTSTAT;                           /**< Interrupt status., offset: 0x4 */
  __IO uint32_t SRAMBASE;                          /**< SRAM address of the channel configuration table., offset: 0x8 */
       uint8_t RESERVED_0[20];
  struct {                                         /* offset: 0x20, array step: 0x5C */
    __IO uint32_t ENABLESET;                         /**< Channel Enable read and Set for all DMA channels., array offset: 0x20, array step: 0x5C */
         uint8_t RESERVED_0[4];
    __O  uint32_t ENABLECLR;                         /**< Channel Enable Clear for all DMA channels., array offset: 0x28, array step: 0x5C */
         uint8_t RESERVED_1[4];
    __I  uint32_t ACTIVE;                            /**< Channel Active status for all DMA channels., array offset: 0x30, array step: 0x5C */
         uint8_t RESERVED_2[4];
    __I  uint32_t BUSY;                              /**< Channel Busy status for all DMA channels., array offset: 0x38, array step: 0x5C */
         uint8_t RESERVED_3[4];
    __IO uint32_t ERRINT;                            /**< Error Interrupt status for all DMA channels., array offset: 0x40, array step: 0x5C */
         uint8_t RESERVED_4[4];
    __IO uint32_t INTENSET;                          /**< Interrupt Enable read and Set for all DMA channels., array offset: 0x48, array step: 0x5C */
         uint8_t RESERVED_5[4];
    __O  uint32_t INTENCLR;                          /**< Interrupt Enable Clear for all DMA channels., array offset: 0x50, array step: 0x5C */
         uint8_t RESERVED_6[4];
    __IO uint32_t INTA;                              /**< Interrupt A status for all DMA channels., array offset: 0x58, array step: 0x5C */
         uint8_t RESERVED_7[4];
    __IO uint32_t INTB;                              /**< Interrupt B status for all DMA channels., array offset: 0x60, array step: 0x5C */
         uint8_t RESERVED_8[4];
    __O  uint32_t SETVALID;                          /**< Set ValidPending control bits for all DMA channels., array offset: 0x68, array step: 0x5C */
         uint8_t RESERVED_9[4];
    __O  uint32_t SETTRIG;                           /**< Set Trigger control bits for all DMA channels., array offset: 0x70, array step: 0x5C */
         uint8_t RESERVED_10[4];
    __O  uint32_t ABORT;                             /**< Channel Abort control for all DMA channels., array offset: 0x78, array step: 0x5C */
  } COMMON[1];
       uint8_t RESERVED_1[900];
  struct {                                         /* offset: 0x400, array step: 0x10 */
    __IO uint32_t CFG;                               /**< Configuration register for DMA channel ., array offset: 0x400, array step: 0x10 */
    __I  uint32_t CTLSTAT;                           /**< Control and status register for DMA channel ., array offset: 0x404, array step: 0x10 */
    __IO uint32_t XFERCFG;                           /**< Transfer configuration register for DMA channel ., array offset: 0x408, array step: 0x10 */
         uint8_t RESERVED_0[4];
  } CHANNEL[30];
} DMA_Type;

/* ----------------------------------------------------------------------------
   -- DMA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Masks DMA Register Masks
 * @{
 */

/*! @name CTRL - DMA control. */
#define DMA_CTRL_ENABLE_MASK                     (0x1U)
#define DMA_CTRL_ENABLE_SHIFT                    (0U)
#define DMA_CTRL_ENABLE(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_CTRL_ENABLE_SHIFT)) & DMA_CTRL_ENABLE_MASK)

/*! @name INTSTAT - Interrupt status. */
#define DMA_INTSTAT_ACTIVEINT_MASK               (0x2U)
#define DMA_INTSTAT_ACTIVEINT_SHIFT              (1U)
#define DMA_INTSTAT_ACTIVEINT(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_INTSTAT_ACTIVEINT_SHIFT)) & DMA_INTSTAT_ACTIVEINT_MASK)
#define DMA_INTSTAT_ACTIVEERRINT_MASK            (0x4U)
#define DMA_INTSTAT_ACTIVEERRINT_SHIFT           (2U)
#define DMA_INTSTAT_ACTIVEERRINT(x)              (((uint32_t)(((uint32_t)(x)) << DMA_INTSTAT_ACTIVEERRINT_SHIFT)) & DMA_INTSTAT_ACTIVEERRINT_MASK)

/*! @name SRAMBASE - SRAM address of the channel configuration table. */
#define DMA_SRAMBASE_OFFSET_MASK                 (0xFFFFFE00U)
#define DMA_SRAMBASE_OFFSET_SHIFT                (9U)
#define DMA_SRAMBASE_OFFSET(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_SRAMBASE_OFFSET_SHIFT)) & DMA_SRAMBASE_OFFSET_MASK)

/*! @name COMMON_ENABLESET - Channel Enable read and Set for all DMA channels. */
#define DMA_COMMON_ENABLESET_ENA_MASK            (0xFFFFFFFFU)
#define DMA_COMMON_ENABLESET_ENA_SHIFT           (0U)
#define DMA_COMMON_ENABLESET_ENA(x)              (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ENABLESET_ENA_SHIFT)) & DMA_COMMON_ENABLESET_ENA_MASK)

/* The count of DMA_COMMON_ENABLESET */
#define DMA_COMMON_ENABLESET_COUNT               (1U)

/*! @name COMMON_ENABLECLR - Channel Enable Clear for all DMA channels. */
#define DMA_COMMON_ENABLECLR_CLR_MASK            (0xFFFFFFFFU)
#define DMA_COMMON_ENABLECLR_CLR_SHIFT           (0U)
#define DMA_COMMON_ENABLECLR_CLR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ENABLECLR_CLR_SHIFT)) & DMA_COMMON_ENABLECLR_CLR_MASK)

/* The count of DMA_COMMON_ENABLECLR */
#define DMA_COMMON_ENABLECLR_COUNT               (1U)

/*! @name COMMON_ACTIVE - Channel Active status for all DMA channels. */
#define DMA_COMMON_ACTIVE_ACT_MASK               (0xFFFFFFFFU)
#define DMA_COMMON_ACTIVE_ACT_SHIFT              (0U)
#define DMA_COMMON_ACTIVE_ACT(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ACTIVE_ACT_SHIFT)) & DMA_COMMON_ACTIVE_ACT_MASK)

/* The count of DMA_COMMON_ACTIVE */
#define DMA_COMMON_ACTIVE_COUNT                  (1U)

/*! @name COMMON_BUSY - Channel Busy status for all DMA channels. */
#define DMA_COMMON_BUSY_BSY_MASK                 (0xFFFFFFFFU)
#define DMA_COMMON_BUSY_BSY_SHIFT                (0U)
#define DMA_COMMON_BUSY_BSY(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_BUSY_BSY_SHIFT)) & DMA_COMMON_BUSY_BSY_MASK)

/* The count of DMA_COMMON_BUSY */
#define DMA_COMMON_BUSY_COUNT                    (1U)

/*! @name COMMON_ERRINT - Error Interrupt status for all DMA channels. */
#define DMA_COMMON_ERRINT_ERR_MASK               (0xFFFFFFFFU)
#define DMA_COMMON_ERRINT_ERR_SHIFT              (0U)
#define DMA_COMMON_ERRINT_ERR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ERRINT_ERR_SHIFT)) & DMA_COMMON_ERRINT_ERR_MASK)

/* The count of DMA_COMMON_ERRINT */
#define DMA_COMMON_ERRINT_COUNT                  (1U)

/*! @name COMMON_INTENSET - Interrupt Enable read and Set for all DMA channels. */
#define DMA_COMMON_INTENSET_INTEN_MASK           (0xFFFFFFFFU)
#define DMA_COMMON_INTENSET_INTEN_SHIFT          (0U)
#define DMA_COMMON_INTENSET_INTEN(x)             (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_INTENSET_INTEN_SHIFT)) & DMA_COMMON_INTENSET_INTEN_MASK)

/* The count of DMA_COMMON_INTENSET */
#define DMA_COMMON_INTENSET_COUNT                (1U)

/*! @name COMMON_INTENCLR - Interrupt Enable Clear for all DMA channels. */
#define DMA_COMMON_INTENCLR_CLR_MASK             (0xFFFFFFFFU)
#define DMA_COMMON_INTENCLR_CLR_SHIFT            (0U)
#define DMA_COMMON_INTENCLR_CLR(x)               (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_INTENCLR_CLR_SHIFT)) & DMA_COMMON_INTENCLR_CLR_MASK)

/* The count of DMA_COMMON_INTENCLR */
#define DMA_COMMON_INTENCLR_COUNT                (1U)

/*! @name COMMON_INTA - Interrupt A status for all DMA channels. */
#define DMA_COMMON_INTA_IA_MASK                  (0xFFFFFFFFU)
#define DMA_COMMON_INTA_IA_SHIFT                 (0U)
#define DMA_COMMON_INTA_IA(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_INTA_IA_SHIFT)) & DMA_COMMON_INTA_IA_MASK)

/* The count of DMA_COMMON_INTA */
#define DMA_COMMON_INTA_COUNT                    (1U)

/*! @name COMMON_INTB - Interrupt B status for all DMA channels. */
#define DMA_COMMON_INTB_IB_MASK                  (0xFFFFFFFFU)
#define DMA_COMMON_INTB_IB_SHIFT                 (0U)
#define DMA_COMMON_INTB_IB(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_INTB_IB_SHIFT)) & DMA_COMMON_INTB_IB_MASK)

/* The count of DMA_COMMON_INTB */
#define DMA_COMMON_INTB_COUNT                    (1U)

/*! @name COMMON_SETVALID - Set ValidPending control bits for all DMA channels. */
#define DMA_COMMON_SETVALID_SV_MASK              (0xFFFFFFFFU)
#define DMA_COMMON_SETVALID_SV_SHIFT             (0U)
#define DMA_COMMON_SETVALID_SV(x)                (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_SETVALID_SV_SHIFT)) & DMA_COMMON_SETVALID_SV_MASK)

/* The count of DMA_COMMON_SETVALID */
#define DMA_COMMON_SETVALID_COUNT                (1U)

/*! @name COMMON_SETTRIG - Set Trigger control bits for all DMA channels. */
#define DMA_COMMON_SETTRIG_TRIG_MASK             (0xFFFFFFFFU)
#define DMA_COMMON_SETTRIG_TRIG_SHIFT            (0U)
#define DMA_COMMON_SETTRIG_TRIG(x)               (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_SETTRIG_TRIG_SHIFT)) & DMA_COMMON_SETTRIG_TRIG_MASK)

/* The count of DMA_COMMON_SETTRIG */
#define DMA_COMMON_SETTRIG_COUNT                 (1U)

/*! @name COMMON_ABORT - Channel Abort control for all DMA channels. */
#define DMA_COMMON_ABORT_ABORTCTRL_MASK          (0xFFFFFFFFU)
#define DMA_COMMON_ABORT_ABORTCTRL_SHIFT         (0U)
#define DMA_COMMON_ABORT_ABORTCTRL(x)            (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ABORT_ABORTCTRL_SHIFT)) & DMA_COMMON_ABORT_ABORTCTRL_MASK)

/* The count of DMA_COMMON_ABORT */
#define DMA_COMMON_ABORT_COUNT                   (1U)

/*! @name CHANNEL_CFG - Configuration register for DMA channel . */
#define DMA_CHANNEL_CFG_PERIPHREQEN_MASK         (0x1U)
#define DMA_CHANNEL_CFG_PERIPHREQEN_SHIFT        (0U)
#define DMA_CHANNEL_CFG_PERIPHREQEN(x)           (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_PERIPHREQEN_SHIFT)) & DMA_CHANNEL_CFG_PERIPHREQEN_MASK)
#define DMA_CHANNEL_CFG_HWTRIGEN_MASK            (0x2U)
#define DMA_CHANNEL_CFG_HWTRIGEN_SHIFT           (1U)
#define DMA_CHANNEL_CFG_HWTRIGEN(x)              (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_HWTRIGEN_SHIFT)) & DMA_CHANNEL_CFG_HWTRIGEN_MASK)
#define DMA_CHANNEL_CFG_TRIGPOL_MASK             (0x10U)
#define DMA_CHANNEL_CFG_TRIGPOL_SHIFT            (4U)
#define DMA_CHANNEL_CFG_TRIGPOL(x)               (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_TRIGPOL_SHIFT)) & DMA_CHANNEL_CFG_TRIGPOL_MASK)
#define DMA_CHANNEL_CFG_TRIGTYPE_MASK            (0x20U)
#define DMA_CHANNEL_CFG_TRIGTYPE_SHIFT           (5U)
#define DMA_CHANNEL_CFG_TRIGTYPE(x)              (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_TRIGTYPE_SHIFT)) & DMA_CHANNEL_CFG_TRIGTYPE_MASK)
#define DMA_CHANNEL_CFG_TRIGBURST_MASK           (0x40U)
#define DMA_CHANNEL_CFG_TRIGBURST_SHIFT          (6U)
#define DMA_CHANNEL_CFG_TRIGBURST(x)             (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_TRIGBURST_SHIFT)) & DMA_CHANNEL_CFG_TRIGBURST_MASK)
#define DMA_CHANNEL_CFG_BURSTPOWER_MASK          (0xF00U)
#define DMA_CHANNEL_CFG_BURSTPOWER_SHIFT         (8U)
#define DMA_CHANNEL_CFG_BURSTPOWER(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_BURSTPOWER_SHIFT)) & DMA_CHANNEL_CFG_BURSTPOWER_MASK)
#define DMA_CHANNEL_CFG_SRCBURSTWRAP_MASK        (0x4000U)
#define DMA_CHANNEL_CFG_SRCBURSTWRAP_SHIFT       (14U)
#define DMA_CHANNEL_CFG_SRCBURSTWRAP(x)          (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_SRCBURSTWRAP_SHIFT)) & DMA_CHANNEL_CFG_SRCBURSTWRAP_MASK)
#define DMA_CHANNEL_CFG_DSTBURSTWRAP_MASK        (0x8000U)
#define DMA_CHANNEL_CFG_DSTBURSTWRAP_SHIFT       (15U)
#define DMA_CHANNEL_CFG_DSTBURSTWRAP(x)          (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_DSTBURSTWRAP_SHIFT)) & DMA_CHANNEL_CFG_DSTBURSTWRAP_MASK)
#define DMA_CHANNEL_CFG_CHPRIORITY_MASK          (0x70000U)
#define DMA_CHANNEL_CFG_CHPRIORITY_SHIFT         (16U)
#define DMA_CHANNEL_CFG_CHPRIORITY(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_CHPRIORITY_SHIFT)) & DMA_CHANNEL_CFG_CHPRIORITY_MASK)

/* The count of DMA_CHANNEL_CFG */
#define DMA_CHANNEL_CFG_COUNT                    (30U)

/*! @name CHANNEL_CTLSTAT - Control and status register for DMA channel . */
#define DMA_CHANNEL_CTLSTAT_VALIDPENDING_MASK    (0x1U)
#define DMA_CHANNEL_CTLSTAT_VALIDPENDING_SHIFT   (0U)
#define DMA_CHANNEL_CTLSTAT_VALIDPENDING(x)      (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CTLSTAT_VALIDPENDING_SHIFT)) & DMA_CHANNEL_CTLSTAT_VALIDPENDING_MASK)
#define DMA_CHANNEL_CTLSTAT_TRIG_MASK            (0x4U)
#define DMA_CHANNEL_CTLSTAT_TRIG_SHIFT           (2U)
#define DMA_CHANNEL_CTLSTAT_TRIG(x)              (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CTLSTAT_TRIG_SHIFT)) & DMA_CHANNEL_CTLSTAT_TRIG_MASK)

/* The count of DMA_CHANNEL_CTLSTAT */
#define DMA_CHANNEL_CTLSTAT_COUNT                (30U)

/*! @name CHANNEL_XFERCFG - Transfer configuration register for DMA channel . */
#define DMA_CHANNEL_XFERCFG_CFGVALID_MASK        (0x1U)
#define DMA_CHANNEL_XFERCFG_CFGVALID_SHIFT       (0U)
#define DMA_CHANNEL_XFERCFG_CFGVALID(x)          (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_CFGVALID_SHIFT)) & DMA_CHANNEL_XFERCFG_CFGVALID_MASK)
#define DMA_CHANNEL_XFERCFG_RELOAD_MASK          (0x2U)
#define DMA_CHANNEL_XFERCFG_RELOAD_SHIFT         (1U)
#define DMA_CHANNEL_XFERCFG_RELOAD(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_RELOAD_SHIFT)) & DMA_CHANNEL_XFERCFG_RELOAD_MASK)
#define DMA_CHANNEL_XFERCFG_SWTRIG_MASK          (0x4U)
#define DMA_CHANNEL_XFERCFG_SWTRIG_SHIFT         (2U)
#define DMA_CHANNEL_XFERCFG_SWTRIG(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_SWTRIG_SHIFT)) & DMA_CHANNEL_XFERCFG_SWTRIG_MASK)
#define DMA_CHANNEL_XFERCFG_CLRTRIG_MASK         (0x8U)
#define DMA_CHANNEL_XFERCFG_CLRTRIG_SHIFT        (3U)
#define DMA_CHANNEL_XFERCFG_CLRTRIG(x)           (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_CLRTRIG_SHIFT)) & DMA_CHANNEL_XFERCFG_CLRTRIG_MASK)
#define DMA_CHANNEL_XFERCFG_SETINTA_MASK         (0x10U)
#define DMA_CHANNEL_XFERCFG_SETINTA_SHIFT        (4U)
#define DMA_CHANNEL_XFERCFG_SETINTA(x)           (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_SETINTA_SHIFT)) & DMA_CHANNEL_XFERCFG_SETINTA_MASK)
#define DMA_CHANNEL_XFERCFG_SETINTB_MASK         (0x20U)
#define DMA_CHANNEL_XFERCFG_SETINTB_SHIFT        (5U)
#define DMA_CHANNEL_XFERCFG_SETINTB(x)           (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_SETINTB_SHIFT)) & DMA_CHANNEL_XFERCFG_SETINTB_MASK)
#define DMA_CHANNEL_XFERCFG_WIDTH_MASK           (0x300U)
#define DMA_CHANNEL_XFERCFG_WIDTH_SHIFT          (8U)
#define DMA_CHANNEL_XFERCFG_WIDTH(x)             (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_WIDTH_SHIFT)) & DMA_CHANNEL_XFERCFG_WIDTH_MASK)
#define DMA_CHANNEL_XFERCFG_SRCINC_MASK          (0x3000U)
#define DMA_CHANNEL_XFERCFG_SRCINC_SHIFT         (12U)
#define DMA_CHANNEL_XFERCFG_SRCINC(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_SRCINC_SHIFT)) & DMA_CHANNEL_XFERCFG_SRCINC_MASK)
#define DMA_CHANNEL_XFERCFG_DSTINC_MASK          (0xC000U)
#define DMA_CHANNEL_XFERCFG_DSTINC_SHIFT         (14U)
#define DMA_CHANNEL_XFERCFG_DSTINC(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_DSTINC_SHIFT)) & DMA_CHANNEL_XFERCFG_DSTINC_MASK)
#define DMA_CHANNEL_XFERCFG_XFERCOUNT_MASK       (0x3FF0000U)
#define DMA_CHANNEL_XFERCFG_XFERCOUNT_SHIFT      (16U)
#define DMA_CHANNEL_XFERCFG_XFERCOUNT(x)         (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_XFERCOUNT_SHIFT)) & DMA_CHANNEL_XFERCFG_XFERCOUNT_MASK)

/* The count of DMA_CHANNEL_XFERCFG */
#define DMA_CHANNEL_XFERCFG_COUNT                (30U)


/*!
 * @}
 */ /* end of group DMA_Register_Masks */


/* DMA - Peripheral instance base addresses */
/** Peripheral DMA0 base address */
#define DMA0_BASE                                (0x40082000u)
/** Peripheral DMA0 base pointer */
#define DMA0                                     ((DMA_Type *)DMA0_BASE)
/** Array initializer of DMA peripheral base addresses */
#define DMA_BASE_ADDRS                           { DMA0_BASE }
/** Array initializer of DMA peripheral base pointers */
#define DMA_BASE_PTRS                            { DMA0 }
/** Interrupt vectors for the DMA peripheral type */
#define DMA_IRQS                                 { DMA0_IRQn }

/*!
 * @}
 */ /* end of group DMA_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- DMIC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMIC_Peripheral_Access_Layer DMIC Peripheral Access Layer
 * @{
 */

/** DMIC - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x100 */
    __IO uint32_t OSR;                               /**< Oversample Rate register 0, array offset: 0x0, array step: 0x100 */
    __IO uint32_t DIVHFCLK;                          /**< DMIC Clock Register 0, array offset: 0x4, array step: 0x100 */
    __IO uint32_t PREAC2FSCOEF;                      /**< Pre-Emphasis Filter Coefficient for 2 FS register, array offset: 0x8, array step: 0x100 */
    __IO uint32_t PREAC4FSCOEF;                      /**< Pre-Emphasis Filter Coefficient for 4 FS register, array offset: 0xC, array step: 0x100 */
    __IO uint32_t GAINSHIFT;                         /**< Decimator Gain Shift register, array offset: 0x10, array step: 0x100 */
         uint8_t RESERVED_0[108];
    __IO uint32_t FIFO_CTRL;                         /**< FIFO Control register 0, array offset: 0x80, array step: 0x100 */
    __IO uint32_t FIFO_STATUS;                       /**< FIFO Status register 0, array offset: 0x84, array step: 0x100 */
    __IO uint32_t FIFO_DATA;                         /**< FIFO Data Register 0, array offset: 0x88, array step: 0x100 */
    __IO uint32_t PHY_CTRL;                          /**< PDM Source Configuration register 0, array offset: 0x8C, array step: 0x100 */
    __IO uint32_t DC_CTRL;                           /**< DC Control register 0, array offset: 0x90, array step: 0x100 */
         uint8_t RESERVED_1[108];
  } CHANNEL[2];
       uint8_t RESERVED_0[3328];
  __IO uint32_t CHANEN;                            /**< Channel Enable register, offset: 0xF00 */
       uint8_t RESERVED_1[8];
  __IO uint32_t IOCFG;                             /**< I/O Configuration register, offset: 0xF0C */
  __IO uint32_t USE2FS;                            /**< Use 2FS register, offset: 0xF10 */
       uint8_t RESERVED_2[108];
  __IO uint32_t HWVADGAIN;                         /**< HWVAD input gain register, offset: 0xF80 */
  __IO uint32_t HWVADHPFS;                         /**< HWVAD filter control register, offset: 0xF84 */
  __IO uint32_t HWVADST10;                         /**< HWVAD control register, offset: 0xF88 */
  __IO uint32_t HWVADRSTT;                         /**< HWVAD filter reset register, offset: 0xF8C */
  __IO uint32_t HWVADTHGN;                         /**< HWVAD noise estimator gain register, offset: 0xF90 */
  __IO uint32_t HWVADTHGS;                         /**< HWVAD signal estimator gain register, offset: 0xF94 */
  __I  uint32_t HWVADLOWZ;                         /**< HWVAD noise envelope estimator register, offset: 0xF98 */
       uint8_t RESERVED_3[96];
  __I  uint32_t ID;                                /**< Module Identification register, offset: 0xFFC */
} DMIC_Type;

/* ----------------------------------------------------------------------------
   -- DMIC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMIC_Register_Masks DMIC Register Masks
 * @{
 */

/*! @name CHANNEL_OSR - Oversample Rate register 0 */
#define DMIC_CHANNEL_OSR_OSR_MASK                (0xFFU)
#define DMIC_CHANNEL_OSR_OSR_SHIFT               (0U)
#define DMIC_CHANNEL_OSR_OSR(x)                  (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_OSR_OSR_SHIFT)) & DMIC_CHANNEL_OSR_OSR_MASK)

/* The count of DMIC_CHANNEL_OSR */
#define DMIC_CHANNEL_OSR_COUNT                   (2U)

/*! @name CHANNEL_DIVHFCLK - DMIC Clock Register 0 */
#define DMIC_CHANNEL_DIVHFCLK_PDMDIV_MASK        (0xFU)
#define DMIC_CHANNEL_DIVHFCLK_PDMDIV_SHIFT       (0U)
#define DMIC_CHANNEL_DIVHFCLK_PDMDIV(x)          (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_DIVHFCLK_PDMDIV_SHIFT)) & DMIC_CHANNEL_DIVHFCLK_PDMDIV_MASK)

/* The count of DMIC_CHANNEL_DIVHFCLK */
#define DMIC_CHANNEL_DIVHFCLK_COUNT              (2U)

/*! @name CHANNEL_PREAC2FSCOEF - Pre-Emphasis Filter Coefficient for 2 FS register */
#define DMIC_CHANNEL_PREAC2FSCOEF_COMP_MASK      (0x3U)
#define DMIC_CHANNEL_PREAC2FSCOEF_COMP_SHIFT     (0U)
#define DMIC_CHANNEL_PREAC2FSCOEF_COMP(x)        (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_PREAC2FSCOEF_COMP_SHIFT)) & DMIC_CHANNEL_PREAC2FSCOEF_COMP_MASK)

/* The count of DMIC_CHANNEL_PREAC2FSCOEF */
#define DMIC_CHANNEL_PREAC2FSCOEF_COUNT          (2U)

/*! @name CHANNEL_PREAC4FSCOEF - Pre-Emphasis Filter Coefficient for 4 FS register */
#define DMIC_CHANNEL_PREAC4FSCOEF_COMP_MASK      (0x3U)
#define DMIC_CHANNEL_PREAC4FSCOEF_COMP_SHIFT     (0U)
#define DMIC_CHANNEL_PREAC4FSCOEF_COMP(x)        (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_PREAC4FSCOEF_COMP_SHIFT)) & DMIC_CHANNEL_PREAC4FSCOEF_COMP_MASK)

/* The count of DMIC_CHANNEL_PREAC4FSCOEF */
#define DMIC_CHANNEL_PREAC4FSCOEF_COUNT          (2U)

/*! @name CHANNEL_GAINSHIFT - Decimator Gain Shift register */
#define DMIC_CHANNEL_GAINSHIFT_GAIN_MASK         (0x3FU)
#define DMIC_CHANNEL_GAINSHIFT_GAIN_SHIFT        (0U)
#define DMIC_CHANNEL_GAINSHIFT_GAIN(x)           (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_GAINSHIFT_GAIN_SHIFT)) & DMIC_CHANNEL_GAINSHIFT_GAIN_MASK)

/* The count of DMIC_CHANNEL_GAINSHIFT */
#define DMIC_CHANNEL_GAINSHIFT_COUNT             (2U)

/*! @name CHANNEL_FIFO_CTRL - FIFO Control register 0 */
#define DMIC_CHANNEL_FIFO_CTRL_ENABLE_MASK       (0x1U)
#define DMIC_CHANNEL_FIFO_CTRL_ENABLE_SHIFT      (0U)
#define DMIC_CHANNEL_FIFO_CTRL_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_FIFO_CTRL_ENABLE_SHIFT)) & DMIC_CHANNEL_FIFO_CTRL_ENABLE_MASK)
#define DMIC_CHANNEL_FIFO_CTRL_RESETN_MASK       (0x2U)
#define DMIC_CHANNEL_FIFO_CTRL_RESETN_SHIFT      (1U)
#define DMIC_CHANNEL_FIFO_CTRL_RESETN(x)         (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_FIFO_CTRL_RESETN_SHIFT)) & DMIC_CHANNEL_FIFO_CTRL_RESETN_MASK)
#define DMIC_CHANNEL_FIFO_CTRL_INTEN_MASK        (0x4U)
#define DMIC_CHANNEL_FIFO_CTRL_INTEN_SHIFT       (2U)
#define DMIC_CHANNEL_FIFO_CTRL_INTEN(x)          (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_FIFO_CTRL_INTEN_SHIFT)) & DMIC_CHANNEL_FIFO_CTRL_INTEN_MASK)
#define DMIC_CHANNEL_FIFO_CTRL_DMAEN_MASK        (0x8U)
#define DMIC_CHANNEL_FIFO_CTRL_DMAEN_SHIFT       (3U)
#define DMIC_CHANNEL_FIFO_CTRL_DMAEN(x)          (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_FIFO_CTRL_DMAEN_SHIFT)) & DMIC_CHANNEL_FIFO_CTRL_DMAEN_MASK)
#define DMIC_CHANNEL_FIFO_CTRL_TRIGLVL_MASK      (0x1F0000U)
#define DMIC_CHANNEL_FIFO_CTRL_TRIGLVL_SHIFT     (16U)
#define DMIC_CHANNEL_FIFO_CTRL_TRIGLVL(x)        (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_FIFO_CTRL_TRIGLVL_SHIFT)) & DMIC_CHANNEL_FIFO_CTRL_TRIGLVL_MASK)

/* The count of DMIC_CHANNEL_FIFO_CTRL */
#define DMIC_CHANNEL_FIFO_CTRL_COUNT             (2U)

/*! @name CHANNEL_FIFO_STATUS - FIFO Status register 0 */
#define DMIC_CHANNEL_FIFO_STATUS_INT_MASK        (0x1U)
#define DMIC_CHANNEL_FIFO_STATUS_INT_SHIFT       (0U)
#define DMIC_CHANNEL_FIFO_STATUS_INT(x)          (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_FIFO_STATUS_INT_SHIFT)) & DMIC_CHANNEL_FIFO_STATUS_INT_MASK)
#define DMIC_CHANNEL_FIFO_STATUS_OVERRUN_MASK    (0x2U)
#define DMIC_CHANNEL_FIFO_STATUS_OVERRUN_SHIFT   (1U)
#define DMIC_CHANNEL_FIFO_STATUS_OVERRUN(x)      (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_FIFO_STATUS_OVERRUN_SHIFT)) & DMIC_CHANNEL_FIFO_STATUS_OVERRUN_MASK)
#define DMIC_CHANNEL_FIFO_STATUS_UNDERRUN_MASK   (0x4U)
#define DMIC_CHANNEL_FIFO_STATUS_UNDERRUN_SHIFT  (2U)
#define DMIC_CHANNEL_FIFO_STATUS_UNDERRUN(x)     (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_FIFO_STATUS_UNDERRUN_SHIFT)) & DMIC_CHANNEL_FIFO_STATUS_UNDERRUN_MASK)

/* The count of DMIC_CHANNEL_FIFO_STATUS */
#define DMIC_CHANNEL_FIFO_STATUS_COUNT           (2U)

/*! @name CHANNEL_FIFO_DATA - FIFO Data Register 0 */
#define DMIC_CHANNEL_FIFO_DATA_DATA_MASK         (0xFFFFFFU)
#define DMIC_CHANNEL_FIFO_DATA_DATA_SHIFT        (0U)
#define DMIC_CHANNEL_FIFO_DATA_DATA(x)           (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_FIFO_DATA_DATA_SHIFT)) & DMIC_CHANNEL_FIFO_DATA_DATA_MASK)

/* The count of DMIC_CHANNEL_FIFO_DATA */
#define DMIC_CHANNEL_FIFO_DATA_COUNT             (2U)

/*! @name CHANNEL_PHY_CTRL - PDM Source Configuration register 0 */
#define DMIC_CHANNEL_PHY_CTRL_PHY_FALL_MASK      (0x1U)
#define DMIC_CHANNEL_PHY_CTRL_PHY_FALL_SHIFT     (0U)
#define DMIC_CHANNEL_PHY_CTRL_PHY_FALL(x)        (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_PHY_CTRL_PHY_FALL_SHIFT)) & DMIC_CHANNEL_PHY_CTRL_PHY_FALL_MASK)
#define DMIC_CHANNEL_PHY_CTRL_PHY_HALF_MASK      (0x2U)
#define DMIC_CHANNEL_PHY_CTRL_PHY_HALF_SHIFT     (1U)
#define DMIC_CHANNEL_PHY_CTRL_PHY_HALF(x)        (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_PHY_CTRL_PHY_HALF_SHIFT)) & DMIC_CHANNEL_PHY_CTRL_PHY_HALF_MASK)

/* The count of DMIC_CHANNEL_PHY_CTRL */
#define DMIC_CHANNEL_PHY_CTRL_COUNT              (2U)

/*! @name CHANNEL_DC_CTRL - DC Control register 0 */
#define DMIC_CHANNEL_DC_CTRL_DCPOLE_MASK         (0x3U)
#define DMIC_CHANNEL_DC_CTRL_DCPOLE_SHIFT        (0U)
#define DMIC_CHANNEL_DC_CTRL_DCPOLE(x)           (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_DC_CTRL_DCPOLE_SHIFT)) & DMIC_CHANNEL_DC_CTRL_DCPOLE_MASK)
#define DMIC_CHANNEL_DC_CTRL_DCGAIN_MASK         (0xF0U)
#define DMIC_CHANNEL_DC_CTRL_DCGAIN_SHIFT        (4U)
#define DMIC_CHANNEL_DC_CTRL_DCGAIN(x)           (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_DC_CTRL_DCGAIN_SHIFT)) & DMIC_CHANNEL_DC_CTRL_DCGAIN_MASK)
#define DMIC_CHANNEL_DC_CTRL_SATURATEAT16BIT_MASK (0x100U)
#define DMIC_CHANNEL_DC_CTRL_SATURATEAT16BIT_SHIFT (8U)
#define DMIC_CHANNEL_DC_CTRL_SATURATEAT16BIT(x)  (((uint32_t)(((uint32_t)(x)) << DMIC_CHANNEL_DC_CTRL_SATURATEAT16BIT_SHIFT)) & DMIC_CHANNEL_DC_CTRL_SATURATEAT16BIT_MASK)

/* The count of DMIC_CHANNEL_DC_CTRL */
#define DMIC_CHANNEL_DC_CTRL_COUNT               (2U)

/*! @name CHANEN - Channel Enable register */
#define DMIC_CHANEN_EN_CH0_MASK                  (0x1U)
#define DMIC_CHANEN_EN_CH0_SHIFT                 (0U)
#define DMIC_CHANEN_EN_CH0(x)                    (((uint32_t)(((uint32_t)(x)) << DMIC_CHANEN_EN_CH0_SHIFT)) & DMIC_CHANEN_EN_CH0_MASK)
#define DMIC_CHANEN_EN_CH1_MASK                  (0x2U)
#define DMIC_CHANEN_EN_CH1_SHIFT                 (1U)
#define DMIC_CHANEN_EN_CH1(x)                    (((uint32_t)(((uint32_t)(x)) << DMIC_CHANEN_EN_CH1_SHIFT)) & DMIC_CHANEN_EN_CH1_MASK)

/*! @name IOCFG - I/O Configuration register */
#define DMIC_IOCFG_CLK_BYPASS0_MASK              (0x1U)
#define DMIC_IOCFG_CLK_BYPASS0_SHIFT             (0U)
#define DMIC_IOCFG_CLK_BYPASS0(x)                (((uint32_t)(((uint32_t)(x)) << DMIC_IOCFG_CLK_BYPASS0_SHIFT)) & DMIC_IOCFG_CLK_BYPASS0_MASK)
#define DMIC_IOCFG_CLK_BYPASS1_MASK              (0x2U)
#define DMIC_IOCFG_CLK_BYPASS1_SHIFT             (1U)
#define DMIC_IOCFG_CLK_BYPASS1(x)                (((uint32_t)(((uint32_t)(x)) << DMIC_IOCFG_CLK_BYPASS1_SHIFT)) & DMIC_IOCFG_CLK_BYPASS1_MASK)
#define DMIC_IOCFG_STEREO_DATA0_MASK             (0x4U)
#define DMIC_IOCFG_STEREO_DATA0_SHIFT            (2U)
#define DMIC_IOCFG_STEREO_DATA0(x)               (((uint32_t)(((uint32_t)(x)) << DMIC_IOCFG_STEREO_DATA0_SHIFT)) & DMIC_IOCFG_STEREO_DATA0_MASK)

/*! @name USE2FS - Use 2FS register */
#define DMIC_USE2FS_USE2FS_MASK                  (0x1U)
#define DMIC_USE2FS_USE2FS_SHIFT                 (0U)
#define DMIC_USE2FS_USE2FS(x)                    (((uint32_t)(((uint32_t)(x)) << DMIC_USE2FS_USE2FS_SHIFT)) & DMIC_USE2FS_USE2FS_MASK)

/*! @name HWVADGAIN - HWVAD input gain register */
#define DMIC_HWVADGAIN_INPUTGAIN_MASK            (0xFU)
#define DMIC_HWVADGAIN_INPUTGAIN_SHIFT           (0U)
#define DMIC_HWVADGAIN_INPUTGAIN(x)              (((uint32_t)(((uint32_t)(x)) << DMIC_HWVADGAIN_INPUTGAIN_SHIFT)) & DMIC_HWVADGAIN_INPUTGAIN_MASK)

/*! @name HWVADHPFS - HWVAD filter control register */
#define DMIC_HWVADHPFS_HPFS_MASK                 (0x3U)
#define DMIC_HWVADHPFS_HPFS_SHIFT                (0U)
#define DMIC_HWVADHPFS_HPFS(x)                   (((uint32_t)(((uint32_t)(x)) << DMIC_HWVADHPFS_HPFS_SHIFT)) & DMIC_HWVADHPFS_HPFS_MASK)

/*! @name HWVADST10 - HWVAD control register */
#define DMIC_HWVADST10_ST10_MASK                 (0x1U)
#define DMIC_HWVADST10_ST10_SHIFT                (0U)
#define DMIC_HWVADST10_ST10(x)                   (((uint32_t)(((uint32_t)(x)) << DMIC_HWVADST10_ST10_SHIFT)) & DMIC_HWVADST10_ST10_MASK)

/*! @name HWVADRSTT - HWVAD filter reset register */
#define DMIC_HWVADRSTT_RSTT_MASK                 (0x1U)
#define DMIC_HWVADRSTT_RSTT_SHIFT                (0U)
#define DMIC_HWVADRSTT_RSTT(x)                   (((uint32_t)(((uint32_t)(x)) << DMIC_HWVADRSTT_RSTT_SHIFT)) & DMIC_HWVADRSTT_RSTT_MASK)

/*! @name HWVADTHGN - HWVAD noise estimator gain register */
#define DMIC_HWVADTHGN_THGN_MASK                 (0xFU)
#define DMIC_HWVADTHGN_THGN_SHIFT                (0U)
#define DMIC_HWVADTHGN_THGN(x)                   (((uint32_t)(((uint32_t)(x)) << DMIC_HWVADTHGN_THGN_SHIFT)) & DMIC_HWVADTHGN_THGN_MASK)

/*! @name HWVADTHGS - HWVAD signal estimator gain register */
#define DMIC_HWVADTHGS_THGS_MASK                 (0xFU)
#define DMIC_HWVADTHGS_THGS_SHIFT                (0U)
#define DMIC_HWVADTHGS_THGS(x)                   (((uint32_t)(((uint32_t)(x)) << DMIC_HWVADTHGS_THGS_SHIFT)) & DMIC_HWVADTHGS_THGS_MASK)

/*! @name HWVADLOWZ - HWVAD noise envelope estimator register */
#define DMIC_HWVADLOWZ_LOWZ_MASK                 (0xFFFFU)
#define DMIC_HWVADLOWZ_LOWZ_SHIFT                (0U)
#define DMIC_HWVADLOWZ_LOWZ(x)                   (((uint32_t)(((uint32_t)(x)) << DMIC_HWVADLOWZ_LOWZ_SHIFT)) & DMIC_HWVADLOWZ_LOWZ_MASK)

/*! @name ID - Module Identification register */
#define DMIC_ID_ID_MASK                          (0xFFFFFFFFU)
#define DMIC_ID_ID_SHIFT                         (0U)
#define DMIC_ID_ID(x)                            (((uint32_t)(((uint32_t)(x)) << DMIC_ID_ID_SHIFT)) & DMIC_ID_ID_MASK)


/*!
 * @}
 */ /* end of group DMIC_Register_Masks */


/* DMIC - Peripheral instance base addresses */
/** Peripheral DMIC0 base address */
#define DMIC0_BASE                               (0x40090000u)
/** Peripheral DMIC0 base pointer */
#define DMIC0                                    ((DMIC_Type *)DMIC0_BASE)
/** Array initializer of DMIC peripheral base addresses */
#define DMIC_BASE_ADDRS                          { DMIC0_BASE }
/** Array initializer of DMIC peripheral base pointers */
#define DMIC_BASE_PTRS                           { DMIC0 }
/** Interrupt vectors for the DMIC peripheral type */
#define DMIC_IRQS                                { DMIC0_IRQn }
#define DMIC_HWVAD_IRQS                          { HWVAD0_IRQn }

/*!
 * @}
 */ /* end of group DMIC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- EEPROM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EEPROM_Peripheral_Access_Layer EEPROM Peripheral Access Layer
 * @{
 */

/** EEPROM - Register Layout Typedef */
typedef struct {
  __IO uint32_t CMD;                               /**< EEPROM command register, offset: 0x0 */
       uint8_t RESERVED_0[4];
  __IO uint32_t RWSTATE;                           /**< EEPROM read wait state register, offset: 0x8 */
  __IO uint32_t AUTOPROG;                          /**< EEPROM auto programming register, offset: 0xC */
  __IO uint32_t WSTATE;                            /**< EEPROM wait state register, offset: 0x10 */
  __IO uint32_t CLKDIV;                            /**< EEPROM clock divider register, offset: 0x14 */
  __IO uint32_t PWRDWN;                            /**< EEPROM power-down register, offset: 0x18 */
       uint8_t RESERVED_1[4028];
  __O  uint32_t INTENCLR;                          /**< EEPROM interrupt enable clear, offset: 0xFD8 */
  __O  uint32_t INTENSET;                          /**< EEPROM interrupt enable set, offset: 0xFDC */
  __I  uint32_t INTSTAT;                           /**< EEPROM interrupt status, offset: 0xFE0 */
  __I  uint32_t INTEN;                             /**< EEPROM interrupt enable, offset: 0xFE4 */
  __O  uint32_t INTSTATCLR;                        /**< EEPROM interrupt status clear, offset: 0xFE8 */
  __O  uint32_t INTSTATSET;                        /**< EEPROM interrupt status set, offset: 0xFEC */
} EEPROM_Type;

/* ----------------------------------------------------------------------------
   -- EEPROM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EEPROM_Register_Masks EEPROM Register Masks
 * @{
 */

/*! @name CMD - EEPROM command register */
#define EEPROM_CMD_CMD_MASK                      (0x7U)
#define EEPROM_CMD_CMD_SHIFT                     (0U)
#define EEPROM_CMD_CMD(x)                        (((uint32_t)(((uint32_t)(x)) << EEPROM_CMD_CMD_SHIFT)) & EEPROM_CMD_CMD_MASK)

/*! @name RWSTATE - EEPROM read wait state register */
#define EEPROM_RWSTATE_RPHASE2_MASK              (0xFFU)
#define EEPROM_RWSTATE_RPHASE2_SHIFT             (0U)
#define EEPROM_RWSTATE_RPHASE2(x)                (((uint32_t)(((uint32_t)(x)) << EEPROM_RWSTATE_RPHASE2_SHIFT)) & EEPROM_RWSTATE_RPHASE2_MASK)
#define EEPROM_RWSTATE_RPHASE1_MASK              (0xFF00U)
#define EEPROM_RWSTATE_RPHASE1_SHIFT             (8U)
#define EEPROM_RWSTATE_RPHASE1(x)                (((uint32_t)(((uint32_t)(x)) << EEPROM_RWSTATE_RPHASE1_SHIFT)) & EEPROM_RWSTATE_RPHASE1_MASK)

/*! @name AUTOPROG - EEPROM auto programming register */
#define EEPROM_AUTOPROG_AUTOPROG_MASK            (0x3U)
#define EEPROM_AUTOPROG_AUTOPROG_SHIFT           (0U)
#define EEPROM_AUTOPROG_AUTOPROG(x)              (((uint32_t)(((uint32_t)(x)) << EEPROM_AUTOPROG_AUTOPROG_SHIFT)) & EEPROM_AUTOPROG_AUTOPROG_MASK)

/*! @name WSTATE - EEPROM wait state register */
#define EEPROM_WSTATE_PHASE3_MASK                (0xFFU)
#define EEPROM_WSTATE_PHASE3_SHIFT               (0U)
#define EEPROM_WSTATE_PHASE3(x)                  (((uint32_t)(((uint32_t)(x)) << EEPROM_WSTATE_PHASE3_SHIFT)) & EEPROM_WSTATE_PHASE3_MASK)
#define EEPROM_WSTATE_PHASE2_MASK                (0xFF00U)
#define EEPROM_WSTATE_PHASE2_SHIFT               (8U)
#define EEPROM_WSTATE_PHASE2(x)                  (((uint32_t)(((uint32_t)(x)) << EEPROM_WSTATE_PHASE2_SHIFT)) & EEPROM_WSTATE_PHASE2_MASK)
#define EEPROM_WSTATE_PHASE1_MASK                (0xFF0000U)
#define EEPROM_WSTATE_PHASE1_SHIFT               (16U)
#define EEPROM_WSTATE_PHASE1(x)                  (((uint32_t)(((uint32_t)(x)) << EEPROM_WSTATE_PHASE1_SHIFT)) & EEPROM_WSTATE_PHASE1_MASK)
#define EEPROM_WSTATE_LCK_PARWEP_MASK            (0x80000000U)
#define EEPROM_WSTATE_LCK_PARWEP_SHIFT           (31U)
#define EEPROM_WSTATE_LCK_PARWEP(x)              (((uint32_t)(((uint32_t)(x)) << EEPROM_WSTATE_LCK_PARWEP_SHIFT)) & EEPROM_WSTATE_LCK_PARWEP_MASK)

/*! @name CLKDIV - EEPROM clock divider register */
#define EEPROM_CLKDIV_CLKDIV_MASK                (0xFFFFU)
#define EEPROM_CLKDIV_CLKDIV_SHIFT               (0U)
#define EEPROM_CLKDIV_CLKDIV(x)                  (((uint32_t)(((uint32_t)(x)) << EEPROM_CLKDIV_CLKDIV_SHIFT)) & EEPROM_CLKDIV_CLKDIV_MASK)

/*! @name PWRDWN - EEPROM power-down register */
#define EEPROM_PWRDWN_PWRDWN_MASK                (0x1U)
#define EEPROM_PWRDWN_PWRDWN_SHIFT               (0U)
#define EEPROM_PWRDWN_PWRDWN(x)                  (((uint32_t)(((uint32_t)(x)) << EEPROM_PWRDWN_PWRDWN_SHIFT)) & EEPROM_PWRDWN_PWRDWN_MASK)

/*! @name INTENCLR - EEPROM interrupt enable clear */
#define EEPROM_INTENCLR_PROG_CLR_EN_MASK         (0x4U)
#define EEPROM_INTENCLR_PROG_CLR_EN_SHIFT        (2U)
#define EEPROM_INTENCLR_PROG_CLR_EN(x)           (((uint32_t)(((uint32_t)(x)) << EEPROM_INTENCLR_PROG_CLR_EN_SHIFT)) & EEPROM_INTENCLR_PROG_CLR_EN_MASK)

/*! @name INTENSET - EEPROM interrupt enable set */
#define EEPROM_INTENSET_PROG_SET_EN_MASK         (0x4U)
#define EEPROM_INTENSET_PROG_SET_EN_SHIFT        (2U)
#define EEPROM_INTENSET_PROG_SET_EN(x)           (((uint32_t)(((uint32_t)(x)) << EEPROM_INTENSET_PROG_SET_EN_SHIFT)) & EEPROM_INTENSET_PROG_SET_EN_MASK)

/*! @name INTSTAT - EEPROM interrupt status */
#define EEPROM_INTSTAT_END_OF_PROG_MASK          (0x4U)
#define EEPROM_INTSTAT_END_OF_PROG_SHIFT         (2U)
#define EEPROM_INTSTAT_END_OF_PROG(x)            (((uint32_t)(((uint32_t)(x)) << EEPROM_INTSTAT_END_OF_PROG_SHIFT)) & EEPROM_INTSTAT_END_OF_PROG_MASK)

/*! @name INTEN - EEPROM interrupt enable */
#define EEPROM_INTEN_EE_PROG_DONE_MASK           (0x4U)
#define EEPROM_INTEN_EE_PROG_DONE_SHIFT          (2U)
#define EEPROM_INTEN_EE_PROG_DONE(x)             (((uint32_t)(((uint32_t)(x)) << EEPROM_INTEN_EE_PROG_DONE_SHIFT)) & EEPROM_INTEN_EE_PROG_DONE_MASK)

/*! @name INTSTATCLR - EEPROM interrupt status clear */
#define EEPROM_INTSTATCLR_PROG_CLR_ST_MASK       (0x4U)
#define EEPROM_INTSTATCLR_PROG_CLR_ST_SHIFT      (2U)
#define EEPROM_INTSTATCLR_PROG_CLR_ST(x)         (((uint32_t)(((uint32_t)(x)) << EEPROM_INTSTATCLR_PROG_CLR_ST_SHIFT)) & EEPROM_INTSTATCLR_PROG_CLR_ST_MASK)

/*! @name INTSTATSET - EEPROM interrupt status set */
#define EEPROM_INTSTATSET_PROG_SET_ST_MASK       (0x4U)
#define EEPROM_INTSTATSET_PROG_SET_ST_SHIFT      (2U)
#define EEPROM_INTSTATSET_PROG_SET_ST(x)         (((uint32_t)(((uint32_t)(x)) << EEPROM_INTSTATSET_PROG_SET_ST_SHIFT)) & EEPROM_INTSTATSET_PROG_SET_ST_MASK)


/*!
 * @}
 */ /* end of group EEPROM_Register_Masks */


/* EEPROM - Peripheral instance base addresses */
/** Peripheral EEPROM base address */
#define EEPROM_BASE                              (0x40014000u)
/** Peripheral EEPROM base pointer */
#define EEPROM                                   ((EEPROM_Type *)EEPROM_BASE)
/** Array initializer of EEPROM peripheral base addresses */
#define EEPROM_BASE_ADDRS                        { EEPROM_BASE }
/** Array initializer of EEPROM peripheral base pointers */
#define EEPROM_BASE_PTRS                         { EEPROM }
/** Interrupt vectors for the EEPROM peripheral type */
#define EEPROM_IRQS                              { EEPROM_IRQn }

/*!
 * @}
 */ /* end of group EEPROM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- EMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EMC_Peripheral_Access_Layer EMC Peripheral Access Layer
 * @{
 */

/** EMC - Register Layout Typedef */
typedef struct {
  __IO uint32_t CONTROL;                           /**< Controls operation of the memory controller, offset: 0x0 */
  __I  uint32_t STATUS;                            /**< Provides EMC status information, offset: 0x4 */
  __IO uint32_t CONFIG;                            /**< Configures operation of the memory controller, offset: 0x8 */
       uint8_t RESERVED_0[20];
  __IO uint32_t DYNAMICCONTROL;                    /**< Controls dynamic memory operation, offset: 0x20 */
  __IO uint32_t DYNAMICREFRESH;                    /**< Configures dynamic memory refresh, offset: 0x24 */
  __IO uint32_t DYNAMICREADCONFIG;                 /**< Configures dynamic memory read strategy, offset: 0x28 */
       uint8_t RESERVED_1[4];
  __IO uint32_t DYNAMICRP;                         /**< Precharge command period, offset: 0x30 */
  __IO uint32_t DYNAMICRAS;                        /**< Active to precharge command period, offset: 0x34 */
  __IO uint32_t DYNAMICSREX;                       /**< Self-refresh exit time, offset: 0x38 */
  __IO uint32_t DYNAMICAPR;                        /**< Last-data-out to active command time, offset: 0x3C */
  __IO uint32_t DYNAMICDAL;                        /**< Data-in to active command time, offset: 0x40 */
  __IO uint32_t DYNAMICWR;                         /**< Write recovery time, offset: 0x44 */
  __IO uint32_t DYNAMICRC;                         /**< Selects the active to active command period, offset: 0x48 */
  __IO uint32_t DYNAMICRFC;                        /**< Selects the auto-refresh period, offset: 0x4C */
  __IO uint32_t DYNAMICXSR;                        /**< Time for exit self-refresh to active command, offset: 0x50 */
  __IO uint32_t DYNAMICRRD;                        /**< Latency for active bank A to active bank B, offset: 0x54 */
  __IO uint32_t DYNAMICMRD;                        /**< Time for load mode register to active command, offset: 0x58 */
       uint8_t RESERVED_2[36];
  __IO uint32_t STATICEXTENDEDWAIT;                /**< Time for long static memory read and write transfers, offset: 0x80 */
       uint8_t RESERVED_3[124];
  struct {                                         /* offset: 0x100, array step: 0x20 */
    __IO uint32_t DYNAMICCONFIG;                     /**< Configuration information for EMC_DYCSx, array offset: 0x100, array step: 0x20 */
    __IO uint32_t DYNAMICRASCAS;                     /**< RAS and CAS latencies for EMC_DYCSx, array offset: 0x104, array step: 0x20 */
         uint8_t RESERVED_0[24];
  } DYNAMIC[4];
       uint8_t RESERVED_4[128];
  struct {                                         /* offset: 0x200, array step: 0x20 */
    __IO uint32_t STATICCONFIG;                      /**< Configuration for EMC_CSx, array offset: 0x200, array step: 0x20 */
    __IO uint32_t STATICWAITWEN;                     /**< Delay from EMC_CSx to write enable, array offset: 0x204, array step: 0x20 */
    __IO uint32_t STATICWAITOEN;                     /**< Delay from EMC_CSx or address change, whichever is later, to output enable, array offset: 0x208, array step: 0x20 */
    __IO uint32_t STATICWAITRD;                      /**< Delay from EMC_CSx to a read access, array offset: 0x20C, array step: 0x20 */
    __IO uint32_t STATICWAITPAGE;                    /**< Delay for asynchronous page mode sequential accesses for EMC_CSx, array offset: 0x210, array step: 0x20 */
    __IO uint32_t STATICWAITWR;                      /**< Delay from EMC_CSx to a write access, array offset: 0x214, array step: 0x20 */
    __IO uint32_t STATICWAITTURN;                    /**< Number of bus turnaround cycles EMC_CSx, array offset: 0x218, array step: 0x20 */
         uint8_t RESERVED_0[4];
  } STATIC[4];
} EMC_Type;

/* ----------------------------------------------------------------------------
   -- EMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EMC_Register_Masks EMC Register Masks
 * @{
 */

/*! @name CONTROL - Controls operation of the memory controller */
#define EMC_CONTROL_E_MASK                       (0x1U)
#define EMC_CONTROL_E_SHIFT                      (0U)
#define EMC_CONTROL_E(x)                         (((uint32_t)(((uint32_t)(x)) << EMC_CONTROL_E_SHIFT)) & EMC_CONTROL_E_MASK)
#define EMC_CONTROL_M_MASK                       (0x2U)
#define EMC_CONTROL_M_SHIFT                      (1U)
#define EMC_CONTROL_M(x)                         (((uint32_t)(((uint32_t)(x)) << EMC_CONTROL_M_SHIFT)) & EMC_CONTROL_M_MASK)
#define EMC_CONTROL_L_MASK                       (0x4U)
#define EMC_CONTROL_L_SHIFT                      (2U)
#define EMC_CONTROL_L(x)                         (((uint32_t)(((uint32_t)(x)) << EMC_CONTROL_L_SHIFT)) & EMC_CONTROL_L_MASK)

/*! @name STATUS - Provides EMC status information */
#define EMC_STATUS_B_MASK                        (0x1U)
#define EMC_STATUS_B_SHIFT                       (0U)
#define EMC_STATUS_B(x)                          (((uint32_t)(((uint32_t)(x)) << EMC_STATUS_B_SHIFT)) & EMC_STATUS_B_MASK)
#define EMC_STATUS_S_MASK                        (0x2U)
#define EMC_STATUS_S_SHIFT                       (1U)
#define EMC_STATUS_S(x)                          (((uint32_t)(((uint32_t)(x)) << EMC_STATUS_S_SHIFT)) & EMC_STATUS_S_MASK)
#define EMC_STATUS_SA_MASK                       (0x4U)
#define EMC_STATUS_SA_SHIFT                      (2U)
#define EMC_STATUS_SA(x)                         (((uint32_t)(((uint32_t)(x)) << EMC_STATUS_SA_SHIFT)) & EMC_STATUS_SA_MASK)

/*! @name CONFIG - Configures operation of the memory controller */
#define EMC_CONFIG_EM_MASK                       (0x1U)
#define EMC_CONFIG_EM_SHIFT                      (0U)
#define EMC_CONFIG_EM(x)                         (((uint32_t)(((uint32_t)(x)) << EMC_CONFIG_EM_SHIFT)) & EMC_CONFIG_EM_MASK)
#define EMC_CONFIG_CLKR_MASK                     (0x100U)
#define EMC_CONFIG_CLKR_SHIFT                    (8U)
#define EMC_CONFIG_CLKR(x)                       (((uint32_t)(((uint32_t)(x)) << EMC_CONFIG_CLKR_SHIFT)) & EMC_CONFIG_CLKR_MASK)

/*! @name DYNAMICCONTROL - Controls dynamic memory operation */
#define EMC_DYNAMICCONTROL_CE_MASK               (0x1U)
#define EMC_DYNAMICCONTROL_CE_SHIFT              (0U)
#define EMC_DYNAMICCONTROL_CE(x)                 (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICCONTROL_CE_SHIFT)) & EMC_DYNAMICCONTROL_CE_MASK)
#define EMC_DYNAMICCONTROL_CS_MASK               (0x2U)
#define EMC_DYNAMICCONTROL_CS_SHIFT              (1U)
#define EMC_DYNAMICCONTROL_CS(x)                 (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICCONTROL_CS_SHIFT)) & EMC_DYNAMICCONTROL_CS_MASK)
#define EMC_DYNAMICCONTROL_SR_MASK               (0x4U)
#define EMC_DYNAMICCONTROL_SR_SHIFT              (2U)
#define EMC_DYNAMICCONTROL_SR(x)                 (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICCONTROL_SR_SHIFT)) & EMC_DYNAMICCONTROL_SR_MASK)
#define EMC_DYNAMICCONTROL_MMC_MASK              (0x20U)
#define EMC_DYNAMICCONTROL_MMC_SHIFT             (5U)
#define EMC_DYNAMICCONTROL_MMC(x)                (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICCONTROL_MMC_SHIFT)) & EMC_DYNAMICCONTROL_MMC_MASK)
#define EMC_DYNAMICCONTROL_I_MASK                (0x180U)
#define EMC_DYNAMICCONTROL_I_SHIFT               (7U)
#define EMC_DYNAMICCONTROL_I(x)                  (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICCONTROL_I_SHIFT)) & EMC_DYNAMICCONTROL_I_MASK)

/*! @name DYNAMICREFRESH - Configures dynamic memory refresh */
#define EMC_DYNAMICREFRESH_REFRESH_MASK          (0x7FFU)
#define EMC_DYNAMICREFRESH_REFRESH_SHIFT         (0U)
#define EMC_DYNAMICREFRESH_REFRESH(x)            (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICREFRESH_REFRESH_SHIFT)) & EMC_DYNAMICREFRESH_REFRESH_MASK)

/*! @name DYNAMICREADCONFIG - Configures dynamic memory read strategy */
#define EMC_DYNAMICREADCONFIG_RD_MASK            (0x3U)
#define EMC_DYNAMICREADCONFIG_RD_SHIFT           (0U)
#define EMC_DYNAMICREADCONFIG_RD(x)              (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICREADCONFIG_RD_SHIFT)) & EMC_DYNAMICREADCONFIG_RD_MASK)

/*! @name DYNAMICRP - Precharge command period */
#define EMC_DYNAMICRP_TRP_MASK                   (0xFU)
#define EMC_DYNAMICRP_TRP_SHIFT                  (0U)
#define EMC_DYNAMICRP_TRP(x)                     (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICRP_TRP_SHIFT)) & EMC_DYNAMICRP_TRP_MASK)

/*! @name DYNAMICRAS - Active to precharge command period */
#define EMC_DYNAMICRAS_TRAS_MASK                 (0xFU)
#define EMC_DYNAMICRAS_TRAS_SHIFT                (0U)
#define EMC_DYNAMICRAS_TRAS(x)                   (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICRAS_TRAS_SHIFT)) & EMC_DYNAMICRAS_TRAS_MASK)

/*! @name DYNAMICSREX - Self-refresh exit time */
#define EMC_DYNAMICSREX_TSREX_MASK               (0xFU)
#define EMC_DYNAMICSREX_TSREX_SHIFT              (0U)
#define EMC_DYNAMICSREX_TSREX(x)                 (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICSREX_TSREX_SHIFT)) & EMC_DYNAMICSREX_TSREX_MASK)

/*! @name DYNAMICAPR - Last-data-out to active command time */
#define EMC_DYNAMICAPR_TAPR_MASK                 (0xFU)
#define EMC_DYNAMICAPR_TAPR_SHIFT                (0U)
#define EMC_DYNAMICAPR_TAPR(x)                   (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICAPR_TAPR_SHIFT)) & EMC_DYNAMICAPR_TAPR_MASK)

/*! @name DYNAMICDAL - Data-in to active command time */
#define EMC_DYNAMICDAL_TDAL_MASK                 (0xFU)
#define EMC_DYNAMICDAL_TDAL_SHIFT                (0U)
#define EMC_DYNAMICDAL_TDAL(x)                   (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICDAL_TDAL_SHIFT)) & EMC_DYNAMICDAL_TDAL_MASK)

/*! @name DYNAMICWR - Write recovery time */
#define EMC_DYNAMICWR_TWR_MASK                   (0xFU)
#define EMC_DYNAMICWR_TWR_SHIFT                  (0U)
#define EMC_DYNAMICWR_TWR(x)                     (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICWR_TWR_SHIFT)) & EMC_DYNAMICWR_TWR_MASK)

/*! @name DYNAMICRC - Selects the active to active command period */
#define EMC_DYNAMICRC_TRC_MASK                   (0x1FU)
#define EMC_DYNAMICRC_TRC_SHIFT                  (0U)
#define EMC_DYNAMICRC_TRC(x)                     (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICRC_TRC_SHIFT)) & EMC_DYNAMICRC_TRC_MASK)

/*! @name DYNAMICRFC - Selects the auto-refresh period */
#define EMC_DYNAMICRFC_TRFC_MASK                 (0x1FU)
#define EMC_DYNAMICRFC_TRFC_SHIFT                (0U)
#define EMC_DYNAMICRFC_TRFC(x)                   (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICRFC_TRFC_SHIFT)) & EMC_DYNAMICRFC_TRFC_MASK)

/*! @name DYNAMICXSR - Time for exit self-refresh to active command */
#define EMC_DYNAMICXSR_TXSR_MASK                 (0x1FU)
#define EMC_DYNAMICXSR_TXSR_SHIFT                (0U)
#define EMC_DYNAMICXSR_TXSR(x)                   (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICXSR_TXSR_SHIFT)) & EMC_DYNAMICXSR_TXSR_MASK)

/*! @name DYNAMICRRD - Latency for active bank A to active bank B */
#define EMC_DYNAMICRRD_TRRD_MASK                 (0xFU)
#define EMC_DYNAMICRRD_TRRD_SHIFT                (0U)
#define EMC_DYNAMICRRD_TRRD(x)                   (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICRRD_TRRD_SHIFT)) & EMC_DYNAMICRRD_TRRD_MASK)

/*! @name DYNAMICMRD - Time for load mode register to active command */
#define EMC_DYNAMICMRD_TMRD_MASK                 (0xFU)
#define EMC_DYNAMICMRD_TMRD_SHIFT                (0U)
#define EMC_DYNAMICMRD_TMRD(x)                   (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMICMRD_TMRD_SHIFT)) & EMC_DYNAMICMRD_TMRD_MASK)

/*! @name STATICEXTENDEDWAIT - Time for long static memory read and write transfers */
#define EMC_STATICEXTENDEDWAIT_EXTENDEDWAIT_MASK (0x3FFU)
#define EMC_STATICEXTENDEDWAIT_EXTENDEDWAIT_SHIFT (0U)
#define EMC_STATICEXTENDEDWAIT_EXTENDEDWAIT(x)   (((uint32_t)(((uint32_t)(x)) << EMC_STATICEXTENDEDWAIT_EXTENDEDWAIT_SHIFT)) & EMC_STATICEXTENDEDWAIT_EXTENDEDWAIT_MASK)

/*! @name DYNAMIC_DYNAMICCONFIG - Configuration information for EMC_DYCSx */
#define EMC_DYNAMIC_DYNAMICCONFIG_MD_MASK        (0x18U)
#define EMC_DYNAMIC_DYNAMICCONFIG_MD_SHIFT       (3U)
#define EMC_DYNAMIC_DYNAMICCONFIG_MD(x)          (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMIC_DYNAMICCONFIG_MD_SHIFT)) & EMC_DYNAMIC_DYNAMICCONFIG_MD_MASK)
#define EMC_DYNAMIC_DYNAMICCONFIG_AM0_MASK       (0x1F80U)
#define EMC_DYNAMIC_DYNAMICCONFIG_AM0_SHIFT      (7U)
#define EMC_DYNAMIC_DYNAMICCONFIG_AM0(x)         (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMIC_DYNAMICCONFIG_AM0_SHIFT)) & EMC_DYNAMIC_DYNAMICCONFIG_AM0_MASK)
#define EMC_DYNAMIC_DYNAMICCONFIG_AM1_MASK       (0x4000U)
#define EMC_DYNAMIC_DYNAMICCONFIG_AM1_SHIFT      (14U)
#define EMC_DYNAMIC_DYNAMICCONFIG_AM1(x)         (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMIC_DYNAMICCONFIG_AM1_SHIFT)) & EMC_DYNAMIC_DYNAMICCONFIG_AM1_MASK)
#define EMC_DYNAMIC_DYNAMICCONFIG_B_MASK         (0x80000U)
#define EMC_DYNAMIC_DYNAMICCONFIG_B_SHIFT        (19U)
#define EMC_DYNAMIC_DYNAMICCONFIG_B(x)           (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMIC_DYNAMICCONFIG_B_SHIFT)) & EMC_DYNAMIC_DYNAMICCONFIG_B_MASK)
#define EMC_DYNAMIC_DYNAMICCONFIG_P_MASK         (0x100000U)
#define EMC_DYNAMIC_DYNAMICCONFIG_P_SHIFT        (20U)
#define EMC_DYNAMIC_DYNAMICCONFIG_P(x)           (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMIC_DYNAMICCONFIG_P_SHIFT)) & EMC_DYNAMIC_DYNAMICCONFIG_P_MASK)

/* The count of EMC_DYNAMIC_DYNAMICCONFIG */
#define EMC_DYNAMIC_DYNAMICCONFIG_COUNT          (4U)

/*! @name DYNAMIC_DYNAMICRASCAS - RAS and CAS latencies for EMC_DYCSx */
#define EMC_DYNAMIC_DYNAMICRASCAS_RAS_MASK       (0x3U)
#define EMC_DYNAMIC_DYNAMICRASCAS_RAS_SHIFT      (0U)
#define EMC_DYNAMIC_DYNAMICRASCAS_RAS(x)         (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMIC_DYNAMICRASCAS_RAS_SHIFT)) & EMC_DYNAMIC_DYNAMICRASCAS_RAS_MASK)
#define EMC_DYNAMIC_DYNAMICRASCAS_CAS_MASK       (0x300U)
#define EMC_DYNAMIC_DYNAMICRASCAS_CAS_SHIFT      (8U)
#define EMC_DYNAMIC_DYNAMICRASCAS_CAS(x)         (((uint32_t)(((uint32_t)(x)) << EMC_DYNAMIC_DYNAMICRASCAS_CAS_SHIFT)) & EMC_DYNAMIC_DYNAMICRASCAS_CAS_MASK)

/* The count of EMC_DYNAMIC_DYNAMICRASCAS */
#define EMC_DYNAMIC_DYNAMICRASCAS_COUNT          (4U)

/*! @name STATIC_STATICCONFIG - Configuration for EMC_CSx */
#define EMC_STATIC_STATICCONFIG_MW_MASK          (0x3U)
#define EMC_STATIC_STATICCONFIG_MW_SHIFT         (0U)
#define EMC_STATIC_STATICCONFIG_MW(x)            (((uint32_t)(((uint32_t)(x)) << EMC_STATIC_STATICCONFIG_MW_SHIFT)) & EMC_STATIC_STATICCONFIG_MW_MASK)
#define EMC_STATIC_STATICCONFIG_PM_MASK          (0x8U)
#define EMC_STATIC_STATICCONFIG_PM_SHIFT         (3U)
#define EMC_STATIC_STATICCONFIG_PM(x)            (((uint32_t)(((uint32_t)(x)) << EMC_STATIC_STATICCONFIG_PM_SHIFT)) & EMC_STATIC_STATICCONFIG_PM_MASK)
#define EMC_STATIC_STATICCONFIG_PC_MASK          (0x40U)
#define EMC_STATIC_STATICCONFIG_PC_SHIFT         (6U)
#define EMC_STATIC_STATICCONFIG_PC(x)            (((uint32_t)(((uint32_t)(x)) << EMC_STATIC_STATICCONFIG_PC_SHIFT)) & EMC_STATIC_STATICCONFIG_PC_MASK)
#define EMC_STATIC_STATICCONFIG_PB_MASK          (0x80U)
#define EMC_STATIC_STATICCONFIG_PB_SHIFT         (7U)
#define EMC_STATIC_STATICCONFIG_PB(x)            (((uint32_t)(((uint32_t)(x)) << EMC_STATIC_STATICCONFIG_PB_SHIFT)) & EMC_STATIC_STATICCONFIG_PB_MASK)
#define EMC_STATIC_STATICCONFIG_EW_MASK          (0x100U)
#define EMC_STATIC_STATICCONFIG_EW_SHIFT         (8U)
#define EMC_STATIC_STATICCONFIG_EW(x)            (((uint32_t)(((uint32_t)(x)) << EMC_STATIC_STATICCONFIG_EW_SHIFT)) & EMC_STATIC_STATICCONFIG_EW_MASK)
#define EMC_STATIC_STATICCONFIG_B_MASK           (0x80000U)
#define EMC_STATIC_STATICCONFIG_B_SHIFT          (19U)
#define EMC_STATIC_STATICCONFIG_B(x)             (((uint32_t)(((uint32_t)(x)) << EMC_STATIC_STATICCONFIG_B_SHIFT)) & EMC_STATIC_STATICCONFIG_B_MASK)
#define EMC_STATIC_STATICCONFIG_P_MASK           (0x100000U)
#define EMC_STATIC_STATICCONFIG_P_SHIFT          (20U)
#define EMC_STATIC_STATICCONFIG_P(x)             (((uint32_t)(((uint32_t)(x)) << EMC_STATIC_STATICCONFIG_P_SHIFT)) & EMC_STATIC_STATICCONFIG_P_MASK)

/* The count of EMC_STATIC_STATICCONFIG */
#define EMC_STATIC_STATICCONFIG_COUNT            (4U)

/*! @name STATIC_STATICWAITWEN - Delay from EMC_CSx to write enable */
#define EMC_STATIC_STATICWAITWEN_WAITWEN_MASK    (0xFU)
#define EMC_STATIC_STATICWAITWEN_WAITWEN_SHIFT   (0U)
#define EMC_STATIC_STATICWAITWEN_WAITWEN(x)      (((uint32_t)(((uint32_t)(x)) << EMC_STATIC_STATICWAITWEN_WAITWEN_SHIFT)) & EMC_STATIC_STATICWAITWEN_WAITWEN_MASK)

/* The count of EMC_STATIC_STATICWAITWEN */
#define EMC_STATIC_STATICWAITWEN_COUNT           (4U)

/*! @name STATIC_STATICWAITOEN - Delay from EMC_CSx or address change, whichever is later, to output enable */
#define EMC_STATIC_STATICWAITOEN_WAITOEN_MASK    (0xFU)
#define EMC_STATIC_STATICWAITOEN_WAITOEN_SHIFT   (0U)
#define EMC_STATIC_STATICWAITOEN_WAITOEN(x)      (((uint32_t)(((uint32_t)(x)) << EMC_STATIC_STATICWAITOEN_WAITOEN_SHIFT)) & EMC_STATIC_STATICWAITOEN_WAITOEN_MASK)

/* The count of EMC_STATIC_STATICWAITOEN */
#define EMC_STATIC_STATICWAITOEN_COUNT           (4U)

/*! @name STATIC_STATICWAITRD - Delay from EMC_CSx to a read access */
#define EMC_STATIC_STATICWAITRD_WAITRD_MASK      (0x1FU)
#define EMC_STATIC_STATICWAITRD_WAITRD_SHIFT     (0U)
#define EMC_STATIC_STATICWAITRD_WAITRD(x)        (((uint32_t)(((uint32_t)(x)) << EMC_STATIC_STATICWAITRD_WAITRD_SHIFT)) & EMC_STATIC_STATICWAITRD_WAITRD_MASK)

/* The count of EMC_STATIC_STATICWAITRD */
#define EMC_STATIC_STATICWAITRD_COUNT            (4U)

/*! @name STATIC_STATICWAITPAGE - Delay for asynchronous page mode sequential accesses for EMC_CSx */
#define EMC_STATIC_STATICWAITPAGE_WAITPAGE_MASK  (0x1FU)
#define EMC_STATIC_STATICWAITPAGE_WAITPAGE_SHIFT (0U)
#define EMC_STATIC_STATICWAITPAGE_WAITPAGE(x)    (((uint32_t)(((uint32_t)(x)) << EMC_STATIC_STATICWAITPAGE_WAITPAGE_SHIFT)) & EMC_STATIC_STATICWAITPAGE_WAITPAGE_MASK)

/* The count of EMC_STATIC_STATICWAITPAGE */
#define EMC_STATIC_STATICWAITPAGE_COUNT          (4U)

/*! @name STATIC_STATICWAITWR - Delay from EMC_CSx to a write access */
#define EMC_STATIC_STATICWAITWR_WAITWR_MASK      (0x1FU)
#define EMC_STATIC_STATICWAITWR_WAITWR_SHIFT     (0U)
#define EMC_STATIC_STATICWAITWR_WAITWR(x)        (((uint32_t)(((uint32_t)(x)) << EMC_STATIC_STATICWAITWR_WAITWR_SHIFT)) & EMC_STATIC_STATICWAITWR_WAITWR_MASK)

/* The count of EMC_STATIC_STATICWAITWR */
#define EMC_STATIC_STATICWAITWR_COUNT            (4U)

/*! @name STATIC_STATICWAITTURN - Number of bus turnaround cycles EMC_CSx */
#define EMC_STATIC_STATICWAITTURN_WAITTURN_MASK  (0xFU)
#define EMC_STATIC_STATICWAITTURN_WAITTURN_SHIFT (0U)
#define EMC_STATIC_STATICWAITTURN_WAITTURN(x)    (((uint32_t)(((uint32_t)(x)) << EMC_STATIC_STATICWAITTURN_WAITTURN_SHIFT)) & EMC_STATIC_STATICWAITTURN_WAITTURN_MASK)

/* The count of EMC_STATIC_STATICWAITTURN */
#define EMC_STATIC_STATICWAITTURN_COUNT          (4U)


/*!
 * @}
 */ /* end of group EMC_Register_Masks */


/* EMC - Peripheral instance base addresses */
/** Peripheral EMC base address */
#define EMC_BASE                                 (0x40081000u)
/** Peripheral EMC base pointer */
#define EMC                                      ((EMC_Type *)EMC_BASE)
/** Array initializer of EMC peripheral base addresses */
#define EMC_BASE_ADDRS                           { EMC_BASE }
/** Array initializer of EMC peripheral base pointers */
#define EMC_BASE_PTRS                            { EMC }

/*!
 * @}
 */ /* end of group EMC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- ENET Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ENET_Peripheral_Access_Layer ENET Peripheral Access Layer
 * @{
 */

/** ENET - Register Layout Typedef */
typedef struct {
  __IO uint32_t MAC_CONFIG;                        /**< MAC configuration register, offset: 0x0 */
  __IO uint32_t MAC_EXT_CONFIG;                    /**< , offset: 0x4 */
  __IO uint32_t MAC_FRAME_FILTER;                  /**< MAC frame filter register, offset: 0x8 */
  __IO uint32_t MAC_WD_TIMEROUT;                   /**< MAC watchdog Timeout register, offset: 0xC */
       uint8_t RESERVED_0[64];
  __IO uint32_t MAC_VLAN_TAG;                      /**< MAC vlan tag register, offset: 0x50 */
       uint8_t RESERVED_1[28];
  __IO uint32_t MAC_TX_FLOW_CTRL_Q[2];             /**< Transmit flow control register, array offset: 0x70, array step: 0x4 */
       uint8_t RESERVED_2[24];
  __IO uint32_t MAC_RX_FLOW_CTRL;                  /**< Receive flow control register, offset: 0x90 */
       uint8_t RESERVED_3[4];
  __IO uint32_t MAC_TXQ_PRIO_MAP;                  /**< , offset: 0x98 */
       uint8_t RESERVED_4[4];
  __IO uint32_t MAC_RXQ_CTRL[3];                   /**< Receive Queue Control 0 register 0x0000, array offset: 0xA0, array step: 0x4 */
       uint8_t RESERVED_5[4];
  __I  uint32_t MAC_INTR_STAT;                     /**< Interrupt status register 0x0000, offset: 0xB0 */
  __IO uint32_t MAC_INTR_EN;                       /**< Interrupt enable register 0x0000, offset: 0xB4 */
  __I  uint32_t MAC_RXTX_STAT;                     /**< Receive Transmit Status register, offset: 0xB8 */
       uint8_t RESERVED_6[4];
  __IO uint32_t MAC_PMT_CRTL_STAT;                 /**< , offset: 0xC0 */
  __IO uint32_t MAC_RWAKE_FRFLT;                   /**< Remote wake-up frame filter, offset: 0xC4 */
       uint8_t RESERVED_7[8];
  __IO uint32_t MAC_LPI_CTRL_STAT;                 /**< LPI Control and Status Register, offset: 0xD0 */
  __IO uint32_t MAC_LPI_TIMER_CTRL;                /**< LPI Timers Control register, offset: 0xD4 */
  __IO uint32_t MAC_LPI_ENTR_TIMR;                 /**< LPI entry Timer register, offset: 0xD8 */
  __IO uint32_t MAC_1US_TIC_COUNTR;                /**< , offset: 0xDC */
       uint8_t RESERVED_8[48];
  __IO uint32_t MAC_VERSION;                       /**< MAC version register, offset: 0x110 */
  __I  uint32_t MAC_DBG;                           /**< MAC debug register, offset: 0x114 */
       uint8_t RESERVED_9[4];
  __IO uint32_t MAC_HW_FEAT[3];                    /**< MAC hardware feature register 0x0201, array offset: 0x11C, array step: 0x4 */
       uint8_t RESERVED_10[216];
  __IO uint32_t MAC_MDIO_ADDR;                     /**< MIDO address Register, offset: 0x200 */
  __IO uint32_t MAC_MDIO_DATA;                     /**< MDIO Data register, offset: 0x204 */
       uint8_t RESERVED_11[248];
  __IO uint32_t MAC_ADDR_HIGH;                     /**< MAC address0 high register, offset: 0x300 */
  __IO uint32_t MAC_ADDR_LOW;                      /**< MAC address0 low register, offset: 0x304 */
       uint8_t RESERVED_12[2040];
  __IO uint32_t MAC_TIMESTAMP_CTRL;                /**< Time stamp control register, offset: 0xB00 */
  __IO uint32_t MAC_SUB_SCND_INCR;                 /**< Sub-second increment register, offset: 0xB04 */
  __I  uint32_t MAC_SYS_TIME_SCND;                 /**< System time seconds register, offset: 0xB08 */
  __I  uint32_t MAC_SYS_TIME_NSCND;                /**< System time nanoseconds register, offset: 0xB0C */
  __IO uint32_t MAC_SYS_TIME_SCND_UPD;             /**< , offset: 0xB10 */
  __IO uint32_t MAC_SYS_TIME_NSCND_UPD;            /**< , offset: 0xB14 */
  __IO uint32_t MAC_SYS_TIMESTMP_ADDEND;           /**< Time stamp addend register, offset: 0xB18 */
  __IO uint32_t MAC_SYS_TIME_HWORD_SCND;           /**< , offset: 0xB1C */
  __I  uint32_t MAC_SYS_TIMESTMP_STAT;             /**< Time stamp status register, offset: 0xB20 */
       uint8_t RESERVED_13[12];
  __I  uint32_t MAC_TX_TIMESTAMP_STATUS_NANOSECONDS; /**< Tx timestamp status nanoseconds, offset: 0xB30 */
  __I  uint32_t MAC_TX_TIMESTAMP_STATUS_SECONDS;   /**< Tx timestamp status seconds, offset: 0xB34 */
       uint8_t RESERVED_14[32];
  __IO uint32_t MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND; /**< Timestamp ingress correction, offset: 0xB58 */
  __IO uint32_t MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND; /**< Timestamp egress correction, offset: 0xB5C */
       uint8_t RESERVED_15[160];
  __IO uint32_t MTL_OP_MODE;                       /**< MTL Operation Mode Register, offset: 0xC00 */
       uint8_t RESERVED_16[28];
  __I  uint32_t MTL_INTR_STAT;                     /**< MTL Interrupt Status register, offset: 0xC20 */
       uint8_t RESERVED_17[12];
  __IO uint32_t MTL_RXQ_DMA_MAP;                   /**< MTL Receive Queue and DMA Channel Mapping register, offset: 0xC30 */
       uint8_t RESERVED_18[204];
  struct {                                         /* offset: 0xD00, array step: 0x40 */
    __IO uint32_t MTL_TXQX_OP_MODE;                  /**< MTL TxQx Operation Mode register, array offset: 0xD00, array step: 0x40 */
    __I  uint32_t MTL_TXQX_UNDRFLW;                  /**< MTL TxQx Underflow register, array offset: 0xD04, array step: 0x40 */
    __I  uint32_t MTL_TXQX_DBG;                      /**< MTL TxQx Debug register, array offset: 0xD08, array step: 0x40 */
         uint8_t RESERVED_0[4];
    __IO uint32_t MTL_TXQX_ETS_CTRL;                 /**< MTL TxQx ETS control register, only TxQ1 support, array offset: 0xD10, array step: 0x40 */
    __IO uint32_t MTL_TXQX_ETS_STAT;                 /**< MTL TxQx ETS Status register, array offset: 0xD14, array step: 0x40 */
    __IO uint32_t MTL_TXQX_QNTM_WGHT;                /**< , array offset: 0xD18, array step: 0x40 */
    __IO uint32_t MTL_TXQX_SNDSLP_CRDT;              /**< MTL TxQx SendSlopCredit register, only TxQ1 support, array offset: 0xD1C, array step: 0x40 */
    __IO uint32_t MTL_TXQX_HI_CRDT;                  /**< MTL TxQx hiCredit register, only TxQ1 support, array offset: 0xD20, array step: 0x40 */
    __IO uint32_t MTL_TXQX_LO_CRDT;                  /**< MTL TxQx loCredit register, only TxQ1 support, array offset: 0xD24, array step: 0x40 */
         uint8_t RESERVED_1[4];
    __IO uint32_t MTL_TXQX_INTCTRL_STAT;             /**< , array offset: 0xD2C, array step: 0x40 */
    __IO uint32_t MTL_RXQX_OP_MODE;                  /**< MTL RxQx Operation Mode register, array offset: 0xD30, array step: 0x40 */
    __IO uint32_t MTL_RXQX_MISSPKT_OVRFLW_CNT;       /**< MTL RxQx Missed Packet Overflow Counter register, array offset: 0xD34, array step: 0x40 */
    __IO uint32_t MTL_RXQX_DBG;                      /**< MTL RxQx Debug register, array offset: 0xD38, array step: 0x40 */
    __IO uint32_t MTL_RXQX_CTRL;                     /**< MTL RxQx Control register, array offset: 0xD3C, array step: 0x40 */
  } MTL_QUEUE[2];
       uint8_t RESERVED_19[640];
  __IO uint32_t DMA_MODE;                          /**< DMA mode register, offset: 0x1000 */
  __IO uint32_t DMA_SYSBUS_MODE;                   /**< DMA System Bus mode, offset: 0x1004 */
  __IO uint32_t DMA_INTR_STAT;                     /**< DMA Interrupt status, offset: 0x1008 */
  __IO uint32_t DMA_DBG_STAT;                      /**< DMA Debug Status, offset: 0x100C */
       uint8_t RESERVED_20[240];
  struct {                                         /* offset: 0x1100, array step: 0x80 */
    __IO uint32_t DMA_CHX_CTRL;                      /**< DMA Channelx Control, array offset: 0x1100, array step: 0x80 */
    __IO uint32_t DMA_CHX_TX_CTRL;                   /**< DMA Channelx Transmit Control, array offset: 0x1104, array step: 0x80 */
    __IO uint32_t DMA_CHX_RX_CTRL;                   /**< DMA Channelx Receive Control, array offset: 0x1108, array step: 0x80 */
         uint8_t RESERVED_0[8];
    __IO uint32_t DMA_CHX_TXDESC_LIST_ADDR;          /**< , array offset: 0x1114, array step: 0x80 */
         uint8_t RESERVED_1[4];
    __IO uint32_t DMA_CHX_RXDESC_LIST_ADDR;          /**< , array offset: 0x111C, array step: 0x80 */
    __IO uint32_t DMA_CHX_TXDESC_TAIL_PTR;           /**< , array offset: 0x1120, array step: 0x80 */
         uint8_t RESERVED_2[4];
    __IO uint32_t DMA_CHX_RXDESC_TAIL_PTR;           /**< , array offset: 0x1128, array step: 0x80 */
    __IO uint32_t DMA_CHX_TXDESC_RING_LENGTH;        /**< , array offset: 0x112C, array step: 0x80 */
    __IO uint32_t DMA_CHX_RXDESC_RING_LENGTH;        /**< Channelx Rx descriptor Ring Length, array offset: 0x1130, array step: 0x80 */
    __IO uint32_t DMA_CHX_INT_EN;                    /**< Channelx Interrupt Enable, array offset: 0x1134, array step: 0x80 */
    __IO uint32_t DMA_CHX_RX_INT_WDTIMER;            /**< Receive Interrupt Watchdog Timer, array offset: 0x1138, array step: 0x80 */
    __IO uint32_t DMA_CHX_SLOT_FUNC_CTRL_STAT;       /**< Slot Function Control and Status, array offset: 0x113C, array step: 0x80 */
         uint8_t RESERVED_3[4];
    __I  uint32_t DMA_CHX_CUR_HST_TXDESC;            /**< Channelx Current Host Transmit descriptor, array offset: 0x1144, array step: 0x80 */
         uint8_t RESERVED_4[4];
    __I  uint32_t DMA_CHX_CUR_HST_RXDESC;            /**< , array offset: 0x114C, array step: 0x80 */
         uint8_t RESERVED_5[4];
    __I  uint32_t DMA_CHX_CUR_HST_TXBUF;             /**< , array offset: 0x1154, array step: 0x80 */
         uint8_t RESERVED_6[4];
    __I  uint32_t DMA_CHX_CUR_HST_RXBUF;             /**< Channelx Current Application Receive Buffer Address, array offset: 0x115C, array step: 0x80 */
    __IO uint32_t DMA_CHX_STAT;                      /**< Channelx DMA status register, array offset: 0x1160, array step: 0x80 */
         uint8_t RESERVED_7[28];
  } DMA_CH[2];
} ENET_Type;

/* ----------------------------------------------------------------------------
   -- ENET Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ENET_Register_Masks ENET Register Masks
 * @{
 */

/*! @name MAC_CONFIG - MAC configuration register */
#define ENET_MAC_CONFIG_RE_MASK                  (0x1U)
#define ENET_MAC_CONFIG_RE_SHIFT                 (0U)
#define ENET_MAC_CONFIG_RE(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_RE_SHIFT)) & ENET_MAC_CONFIG_RE_MASK)
#define ENET_MAC_CONFIG_TE_MASK                  (0x2U)
#define ENET_MAC_CONFIG_TE_SHIFT                 (1U)
#define ENET_MAC_CONFIG_TE(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_TE_SHIFT)) & ENET_MAC_CONFIG_TE_MASK)
#define ENET_MAC_CONFIG_PRELEN_MASK              (0xCU)
#define ENET_MAC_CONFIG_PRELEN_SHIFT             (2U)
#define ENET_MAC_CONFIG_PRELEN(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_PRELEN_SHIFT)) & ENET_MAC_CONFIG_PRELEN_MASK)
#define ENET_MAC_CONFIG_DC_MASK                  (0x10U)
#define ENET_MAC_CONFIG_DC_SHIFT                 (4U)
#define ENET_MAC_CONFIG_DC(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_DC_SHIFT)) & ENET_MAC_CONFIG_DC_MASK)
#define ENET_MAC_CONFIG_BL_MASK                  (0x60U)
#define ENET_MAC_CONFIG_BL_SHIFT                 (5U)
#define ENET_MAC_CONFIG_BL(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_BL_SHIFT)) & ENET_MAC_CONFIG_BL_MASK)
#define ENET_MAC_CONFIG_DR_MASK                  (0x100U)
#define ENET_MAC_CONFIG_DR_SHIFT                 (8U)
#define ENET_MAC_CONFIG_DR(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_DR_SHIFT)) & ENET_MAC_CONFIG_DR_MASK)
#define ENET_MAC_CONFIG_DCRS_MASK                (0x200U)
#define ENET_MAC_CONFIG_DCRS_SHIFT               (9U)
#define ENET_MAC_CONFIG_DCRS(x)                  (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_DCRS_SHIFT)) & ENET_MAC_CONFIG_DCRS_MASK)
#define ENET_MAC_CONFIG_DO_MASK                  (0x400U)
#define ENET_MAC_CONFIG_DO_SHIFT                 (10U)
#define ENET_MAC_CONFIG_DO(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_DO_SHIFT)) & ENET_MAC_CONFIG_DO_MASK)
#define ENET_MAC_CONFIG_ECRSFD_MASK              (0x800U)
#define ENET_MAC_CONFIG_ECRSFD_SHIFT             (11U)
#define ENET_MAC_CONFIG_ECRSFD(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_ECRSFD_SHIFT)) & ENET_MAC_CONFIG_ECRSFD_MASK)
#define ENET_MAC_CONFIG_LM_MASK                  (0x1000U)
#define ENET_MAC_CONFIG_LM_SHIFT                 (12U)
#define ENET_MAC_CONFIG_LM(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_LM_SHIFT)) & ENET_MAC_CONFIG_LM_MASK)
#define ENET_MAC_CONFIG_DM_MASK                  (0x2000U)
#define ENET_MAC_CONFIG_DM_SHIFT                 (13U)
#define ENET_MAC_CONFIG_DM(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_DM_SHIFT)) & ENET_MAC_CONFIG_DM_MASK)
#define ENET_MAC_CONFIG_FES_MASK                 (0x4000U)
#define ENET_MAC_CONFIG_FES_SHIFT                (14U)
#define ENET_MAC_CONFIG_FES(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_FES_SHIFT)) & ENET_MAC_CONFIG_FES_MASK)
#define ENET_MAC_CONFIG_PS_MASK                  (0x8000U)
#define ENET_MAC_CONFIG_PS_SHIFT                 (15U)
#define ENET_MAC_CONFIG_PS(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_PS_SHIFT)) & ENET_MAC_CONFIG_PS_MASK)
#define ENET_MAC_CONFIG_JE_MASK                  (0x10000U)
#define ENET_MAC_CONFIG_JE_SHIFT                 (16U)
#define ENET_MAC_CONFIG_JE(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_JE_SHIFT)) & ENET_MAC_CONFIG_JE_MASK)
#define ENET_MAC_CONFIG_JD_MASK                  (0x20000U)
#define ENET_MAC_CONFIG_JD_SHIFT                 (17U)
#define ENET_MAC_CONFIG_JD(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_JD_SHIFT)) & ENET_MAC_CONFIG_JD_MASK)
#define ENET_MAC_CONFIG_BE_MASK                  (0x40000U)
#define ENET_MAC_CONFIG_BE_SHIFT                 (18U)
#define ENET_MAC_CONFIG_BE(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_BE_SHIFT)) & ENET_MAC_CONFIG_BE_MASK)
#define ENET_MAC_CONFIG_WD_MASK                  (0x80000U)
#define ENET_MAC_CONFIG_WD_SHIFT                 (19U)
#define ENET_MAC_CONFIG_WD(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_WD_SHIFT)) & ENET_MAC_CONFIG_WD_MASK)
#define ENET_MAC_CONFIG_ACS_MASK                 (0x100000U)
#define ENET_MAC_CONFIG_ACS_SHIFT                (20U)
#define ENET_MAC_CONFIG_ACS(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_ACS_SHIFT)) & ENET_MAC_CONFIG_ACS_MASK)
#define ENET_MAC_CONFIG_CST_MASK                 (0x200000U)
#define ENET_MAC_CONFIG_CST_SHIFT                (21U)
#define ENET_MAC_CONFIG_CST(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_CST_SHIFT)) & ENET_MAC_CONFIG_CST_MASK)
#define ENET_MAC_CONFIG_S2KP_MASK                (0x400000U)
#define ENET_MAC_CONFIG_S2KP_SHIFT               (22U)
#define ENET_MAC_CONFIG_S2KP(x)                  (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_S2KP_SHIFT)) & ENET_MAC_CONFIG_S2KP_MASK)
#define ENET_MAC_CONFIG_GPSLCE_MASK              (0x800000U)
#define ENET_MAC_CONFIG_GPSLCE_SHIFT             (23U)
#define ENET_MAC_CONFIG_GPSLCE(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_GPSLCE_SHIFT)) & ENET_MAC_CONFIG_GPSLCE_MASK)
#define ENET_MAC_CONFIG_IPG_MASK                 (0x7000000U)
#define ENET_MAC_CONFIG_IPG_SHIFT                (24U)
#define ENET_MAC_CONFIG_IPG(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_IPG_SHIFT)) & ENET_MAC_CONFIG_IPG_MASK)
#define ENET_MAC_CONFIG_IPC_MASK                 (0x8000000U)
#define ENET_MAC_CONFIG_IPC_SHIFT                (27U)
#define ENET_MAC_CONFIG_IPC(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_MAC_CONFIG_IPC_SHIFT)) & ENET_MAC_CONFIG_IPC_MASK)

/*! @name MAC_EXT_CONFIG -  */
#define ENET_MAC_EXT_CONFIG_GPSL_MASK            (0x3FFFU)
#define ENET_MAC_EXT_CONFIG_GPSL_SHIFT           (0U)
#define ENET_MAC_EXT_CONFIG_GPSL(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_EXT_CONFIG_GPSL_SHIFT)) & ENET_MAC_EXT_CONFIG_GPSL_MASK)
#define ENET_MAC_EXT_CONFIG_DCRCC_MASK           (0x10000U)
#define ENET_MAC_EXT_CONFIG_DCRCC_SHIFT          (16U)
#define ENET_MAC_EXT_CONFIG_DCRCC(x)             (((uint32_t)(((uint32_t)(x)) << ENET_MAC_EXT_CONFIG_DCRCC_SHIFT)) & ENET_MAC_EXT_CONFIG_DCRCC_MASK)
#define ENET_MAC_EXT_CONFIG_SPEN_MASK            (0x20000U)
#define ENET_MAC_EXT_CONFIG_SPEN_SHIFT           (17U)
#define ENET_MAC_EXT_CONFIG_SPEN(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_EXT_CONFIG_SPEN_SHIFT)) & ENET_MAC_EXT_CONFIG_SPEN_MASK)
#define ENET_MAC_EXT_CONFIG_USP_MASK             (0x40000U)
#define ENET_MAC_EXT_CONFIG_USP_SHIFT            (18U)
#define ENET_MAC_EXT_CONFIG_USP(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_EXT_CONFIG_USP_SHIFT)) & ENET_MAC_EXT_CONFIG_USP_MASK)

/*! @name MAC_FRAME_FILTER - MAC frame filter register */
#define ENET_MAC_FRAME_FILTER_PR_MASK            (0x1U)
#define ENET_MAC_FRAME_FILTER_PR_SHIFT           (0U)
#define ENET_MAC_FRAME_FILTER_PR(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_FRAME_FILTER_PR_SHIFT)) & ENET_MAC_FRAME_FILTER_PR_MASK)
#define ENET_MAC_FRAME_FILTER_DAIF_MASK          (0x8U)
#define ENET_MAC_FRAME_FILTER_DAIF_SHIFT         (3U)
#define ENET_MAC_FRAME_FILTER_DAIF(x)            (((uint32_t)(((uint32_t)(x)) << ENET_MAC_FRAME_FILTER_DAIF_SHIFT)) & ENET_MAC_FRAME_FILTER_DAIF_MASK)
#define ENET_MAC_FRAME_FILTER_PM_MASK            (0x10U)
#define ENET_MAC_FRAME_FILTER_PM_SHIFT           (4U)
#define ENET_MAC_FRAME_FILTER_PM(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_FRAME_FILTER_PM_SHIFT)) & ENET_MAC_FRAME_FILTER_PM_MASK)
#define ENET_MAC_FRAME_FILTER_DBF_MASK           (0x20U)
#define ENET_MAC_FRAME_FILTER_DBF_SHIFT          (5U)
#define ENET_MAC_FRAME_FILTER_DBF(x)             (((uint32_t)(((uint32_t)(x)) << ENET_MAC_FRAME_FILTER_DBF_SHIFT)) & ENET_MAC_FRAME_FILTER_DBF_MASK)
#define ENET_MAC_FRAME_FILTER_PCF_MASK           (0xC0U)
#define ENET_MAC_FRAME_FILTER_PCF_SHIFT          (6U)
#define ENET_MAC_FRAME_FILTER_PCF(x)             (((uint32_t)(((uint32_t)(x)) << ENET_MAC_FRAME_FILTER_PCF_SHIFT)) & ENET_MAC_FRAME_FILTER_PCF_MASK)
#define ENET_MAC_FRAME_FILTER_SAIF_MASK          (0x100U)
#define ENET_MAC_FRAME_FILTER_SAIF_SHIFT         (8U)
#define ENET_MAC_FRAME_FILTER_SAIF(x)            (((uint32_t)(((uint32_t)(x)) << ENET_MAC_FRAME_FILTER_SAIF_SHIFT)) & ENET_MAC_FRAME_FILTER_SAIF_MASK)
#define ENET_MAC_FRAME_FILTER_SAF_MASK           (0x200U)
#define ENET_MAC_FRAME_FILTER_SAF_SHIFT          (9U)
#define ENET_MAC_FRAME_FILTER_SAF(x)             (((uint32_t)(((uint32_t)(x)) << ENET_MAC_FRAME_FILTER_SAF_SHIFT)) & ENET_MAC_FRAME_FILTER_SAF_MASK)
#define ENET_MAC_FRAME_FILTER_RA_MASK            (0x80000000U)
#define ENET_MAC_FRAME_FILTER_RA_SHIFT           (31U)
#define ENET_MAC_FRAME_FILTER_RA(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_FRAME_FILTER_RA_SHIFT)) & ENET_MAC_FRAME_FILTER_RA_MASK)

/*! @name MAC_WD_TIMEROUT - MAC watchdog Timeout register */
#define ENET_MAC_WD_TIMEROUT_WTO_MASK            (0xFU)
#define ENET_MAC_WD_TIMEROUT_WTO_SHIFT           (0U)
#define ENET_MAC_WD_TIMEROUT_WTO(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_WD_TIMEROUT_WTO_SHIFT)) & ENET_MAC_WD_TIMEROUT_WTO_MASK)
#define ENET_MAC_WD_TIMEROUT_PWE_MASK            (0x100U)
#define ENET_MAC_WD_TIMEROUT_PWE_SHIFT           (8U)
#define ENET_MAC_WD_TIMEROUT_PWE(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_WD_TIMEROUT_PWE_SHIFT)) & ENET_MAC_WD_TIMEROUT_PWE_MASK)

/*! @name MAC_VLAN_TAG - MAC vlan tag register */
#define ENET_MAC_VLAN_TAG_VL_MASK                (0xFFFFU)
#define ENET_MAC_VLAN_TAG_VL_SHIFT               (0U)
#define ENET_MAC_VLAN_TAG_VL(x)                  (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VLAN_TAG_VL_SHIFT)) & ENET_MAC_VLAN_TAG_VL_MASK)
#define ENET_MAC_VLAN_TAG_ETV_MASK               (0x10000U)
#define ENET_MAC_VLAN_TAG_ETV_SHIFT              (16U)
#define ENET_MAC_VLAN_TAG_ETV(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VLAN_TAG_ETV_SHIFT)) & ENET_MAC_VLAN_TAG_ETV_MASK)
#define ENET_MAC_VLAN_TAG_VTIM_MASK              (0x20000U)
#define ENET_MAC_VLAN_TAG_VTIM_SHIFT             (17U)
#define ENET_MAC_VLAN_TAG_VTIM(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VLAN_TAG_VTIM_SHIFT)) & ENET_MAC_VLAN_TAG_VTIM_MASK)
#define ENET_MAC_VLAN_TAG_ESVL_MASK              (0x40000U)
#define ENET_MAC_VLAN_TAG_ESVL_SHIFT             (18U)
#define ENET_MAC_VLAN_TAG_ESVL(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VLAN_TAG_ESVL_SHIFT)) & ENET_MAC_VLAN_TAG_ESVL_MASK)
#define ENET_MAC_VLAN_TAG_ERSVLM_MASK            (0x80000U)
#define ENET_MAC_VLAN_TAG_ERSVLM_SHIFT           (19U)
#define ENET_MAC_VLAN_TAG_ERSVLM(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VLAN_TAG_ERSVLM_SHIFT)) & ENET_MAC_VLAN_TAG_ERSVLM_MASK)
#define ENET_MAC_VLAN_TAG_DOVLTC_MASK            (0x100000U)
#define ENET_MAC_VLAN_TAG_DOVLTC_SHIFT           (20U)
#define ENET_MAC_VLAN_TAG_DOVLTC(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VLAN_TAG_DOVLTC_SHIFT)) & ENET_MAC_VLAN_TAG_DOVLTC_MASK)
#define ENET_MAC_VLAN_TAG_EVLS_MASK              (0x600000U)
#define ENET_MAC_VLAN_TAG_EVLS_SHIFT             (21U)
#define ENET_MAC_VLAN_TAG_EVLS(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VLAN_TAG_EVLS_SHIFT)) & ENET_MAC_VLAN_TAG_EVLS_MASK)
#define ENET_MAC_VLAN_TAG_EVLRXS_MASK            (0x1000000U)
#define ENET_MAC_VLAN_TAG_EVLRXS_SHIFT           (24U)
#define ENET_MAC_VLAN_TAG_EVLRXS(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VLAN_TAG_EVLRXS_SHIFT)) & ENET_MAC_VLAN_TAG_EVLRXS_MASK)
#define ENET_MAC_VLAN_TAG_VTHM_MASK              (0x2000000U)
#define ENET_MAC_VLAN_TAG_VTHM_SHIFT             (25U)
#define ENET_MAC_VLAN_TAG_VTHM(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VLAN_TAG_VTHM_SHIFT)) & ENET_MAC_VLAN_TAG_VTHM_MASK)
#define ENET_MAC_VLAN_TAG_EDVLP_MASK             (0x4000000U)
#define ENET_MAC_VLAN_TAG_EDVLP_SHIFT            (26U)
#define ENET_MAC_VLAN_TAG_EDVLP(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VLAN_TAG_EDVLP_SHIFT)) & ENET_MAC_VLAN_TAG_EDVLP_MASK)
#define ENET_MAC_VLAN_TAG_ERIVLT_MASK            (0x8000000U)
#define ENET_MAC_VLAN_TAG_ERIVLT_SHIFT           (27U)
#define ENET_MAC_VLAN_TAG_ERIVLT(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VLAN_TAG_ERIVLT_SHIFT)) & ENET_MAC_VLAN_TAG_ERIVLT_MASK)
#define ENET_MAC_VLAN_TAG_EIVLS_MASK             (0x30000000U)
#define ENET_MAC_VLAN_TAG_EIVLS_SHIFT            (28U)
#define ENET_MAC_VLAN_TAG_EIVLS(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VLAN_TAG_EIVLS_SHIFT)) & ENET_MAC_VLAN_TAG_EIVLS_MASK)
#define ENET_MAC_VLAN_TAG_EIVLRXS_MASK           (0x80000000U)
#define ENET_MAC_VLAN_TAG_EIVLRXS_SHIFT          (31U)
#define ENET_MAC_VLAN_TAG_EIVLRXS(x)             (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VLAN_TAG_EIVLRXS_SHIFT)) & ENET_MAC_VLAN_TAG_EIVLRXS_MASK)

/*! @name MAC_TX_FLOW_CTRL_Q - Transmit flow control register */
#define ENET_MAC_TX_FLOW_CTRL_Q_FCB_MASK         (0x1U)
#define ENET_MAC_TX_FLOW_CTRL_Q_FCB_SHIFT        (0U)
#define ENET_MAC_TX_FLOW_CTRL_Q_FCB(x)           (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TX_FLOW_CTRL_Q_FCB_SHIFT)) & ENET_MAC_TX_FLOW_CTRL_Q_FCB_MASK)
#define ENET_MAC_TX_FLOW_CTRL_Q_TFE_MASK         (0x2U)
#define ENET_MAC_TX_FLOW_CTRL_Q_TFE_SHIFT        (1U)
#define ENET_MAC_TX_FLOW_CTRL_Q_TFE(x)           (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TX_FLOW_CTRL_Q_TFE_SHIFT)) & ENET_MAC_TX_FLOW_CTRL_Q_TFE_MASK)
#define ENET_MAC_TX_FLOW_CTRL_Q_PLT_MASK         (0x70U)
#define ENET_MAC_TX_FLOW_CTRL_Q_PLT_SHIFT        (4U)
#define ENET_MAC_TX_FLOW_CTRL_Q_PLT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TX_FLOW_CTRL_Q_PLT_SHIFT)) & ENET_MAC_TX_FLOW_CTRL_Q_PLT_MASK)
#define ENET_MAC_TX_FLOW_CTRL_Q_DZPQ_MASK        (0x80U)
#define ENET_MAC_TX_FLOW_CTRL_Q_DZPQ_SHIFT       (7U)
#define ENET_MAC_TX_FLOW_CTRL_Q_DZPQ(x)          (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TX_FLOW_CTRL_Q_DZPQ_SHIFT)) & ENET_MAC_TX_FLOW_CTRL_Q_DZPQ_MASK)
#define ENET_MAC_TX_FLOW_CTRL_Q_PT_MASK          (0xFFFF0000U)
#define ENET_MAC_TX_FLOW_CTRL_Q_PT_SHIFT         (16U)
#define ENET_MAC_TX_FLOW_CTRL_Q_PT(x)            (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TX_FLOW_CTRL_Q_PT_SHIFT)) & ENET_MAC_TX_FLOW_CTRL_Q_PT_MASK)

/* The count of ENET_MAC_TX_FLOW_CTRL_Q */
#define ENET_MAC_TX_FLOW_CTRL_Q_COUNT            (2U)

/*! @name MAC_RX_FLOW_CTRL - Receive flow control register */
#define ENET_MAC_RX_FLOW_CTRL_RFE_MASK           (0x1U)
#define ENET_MAC_RX_FLOW_CTRL_RFE_SHIFT          (0U)
#define ENET_MAC_RX_FLOW_CTRL_RFE(x)             (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RX_FLOW_CTRL_RFE_SHIFT)) & ENET_MAC_RX_FLOW_CTRL_RFE_MASK)
#define ENET_MAC_RX_FLOW_CTRL_UP_MASK            (0x2U)
#define ENET_MAC_RX_FLOW_CTRL_UP_SHIFT           (1U)
#define ENET_MAC_RX_FLOW_CTRL_UP(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RX_FLOW_CTRL_UP_SHIFT)) & ENET_MAC_RX_FLOW_CTRL_UP_MASK)

/*! @name MAC_TXQ_PRIO_MAP -  */
#define ENET_MAC_TXQ_PRIO_MAP_PSTQ0_MASK         (0xFFU)
#define ENET_MAC_TXQ_PRIO_MAP_PSTQ0_SHIFT        (0U)
#define ENET_MAC_TXQ_PRIO_MAP_PSTQ0(x)           (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TXQ_PRIO_MAP_PSTQ0_SHIFT)) & ENET_MAC_TXQ_PRIO_MAP_PSTQ0_MASK)
#define ENET_MAC_TXQ_PRIO_MAP_PSTQ1_MASK         (0xFF00U)
#define ENET_MAC_TXQ_PRIO_MAP_PSTQ1_SHIFT        (8U)
#define ENET_MAC_TXQ_PRIO_MAP_PSTQ1(x)           (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TXQ_PRIO_MAP_PSTQ1_SHIFT)) & ENET_MAC_TXQ_PRIO_MAP_PSTQ1_MASK)

/*! @name MAC_RXQ_CTRL - Receive Queue Control 0 register 0x0000 */
#define ENET_MAC_RXQ_CTRL_RXQ0EN_MASK            (0x3U)
#define ENET_MAC_RXQ_CTRL_RXQ0EN_SHIFT           (0U)
#define ENET_MAC_RXQ_CTRL_RXQ0EN(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXQ_CTRL_RXQ0EN_SHIFT)) & ENET_MAC_RXQ_CTRL_RXQ0EN_MASK)
#define ENET_MAC_RXQ_CTRL_PSRQ0_MASK             (0xFFU)
#define ENET_MAC_RXQ_CTRL_PSRQ0_SHIFT            (0U)
#define ENET_MAC_RXQ_CTRL_PSRQ0(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXQ_CTRL_PSRQ0_SHIFT)) & ENET_MAC_RXQ_CTRL_PSRQ0_MASK)
#define ENET_MAC_RXQ_CTRL_AVCPQ_MASK             (0x7U)
#define ENET_MAC_RXQ_CTRL_AVCPQ_SHIFT            (0U)
#define ENET_MAC_RXQ_CTRL_AVCPQ(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXQ_CTRL_AVCPQ_SHIFT)) & ENET_MAC_RXQ_CTRL_AVCPQ_MASK)
#define ENET_MAC_RXQ_CTRL_RXQ1EN_MASK            (0xCU)
#define ENET_MAC_RXQ_CTRL_RXQ1EN_SHIFT           (2U)
#define ENET_MAC_RXQ_CTRL_RXQ1EN(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXQ_CTRL_RXQ1EN_SHIFT)) & ENET_MAC_RXQ_CTRL_RXQ1EN_MASK)
#define ENET_MAC_RXQ_CTRL_AVPTPQ_MASK            (0x70U)
#define ENET_MAC_RXQ_CTRL_AVPTPQ_SHIFT           (4U)
#define ENET_MAC_RXQ_CTRL_AVPTPQ(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXQ_CTRL_AVPTPQ_SHIFT)) & ENET_MAC_RXQ_CTRL_AVPTPQ_MASK)
#define ENET_MAC_RXQ_CTRL_PSRQ1_MASK             (0xFF00U)
#define ENET_MAC_RXQ_CTRL_PSRQ1_SHIFT            (8U)
#define ENET_MAC_RXQ_CTRL_PSRQ1(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXQ_CTRL_PSRQ1_SHIFT)) & ENET_MAC_RXQ_CTRL_PSRQ1_MASK)
#define ENET_MAC_RXQ_CTRL_UPQ_MASK               (0x7000U)
#define ENET_MAC_RXQ_CTRL_UPQ_SHIFT              (12U)
#define ENET_MAC_RXQ_CTRL_UPQ(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXQ_CTRL_UPQ_SHIFT)) & ENET_MAC_RXQ_CTRL_UPQ_MASK)
#define ENET_MAC_RXQ_CTRL_PSRQ2_MASK             (0xFF0000U)
#define ENET_MAC_RXQ_CTRL_PSRQ2_SHIFT            (16U)
#define ENET_MAC_RXQ_CTRL_PSRQ2(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXQ_CTRL_PSRQ2_SHIFT)) & ENET_MAC_RXQ_CTRL_PSRQ2_MASK)
#define ENET_MAC_RXQ_CTRL_MCBCQ_MASK             (0x70000U)
#define ENET_MAC_RXQ_CTRL_MCBCQ_SHIFT            (16U)
#define ENET_MAC_RXQ_CTRL_MCBCQ(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXQ_CTRL_MCBCQ_SHIFT)) & ENET_MAC_RXQ_CTRL_MCBCQ_MASK)
#define ENET_MAC_RXQ_CTRL_MCBCQEN_MASK           (0x100000U)
#define ENET_MAC_RXQ_CTRL_MCBCQEN_SHIFT          (20U)
#define ENET_MAC_RXQ_CTRL_MCBCQEN(x)             (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXQ_CTRL_MCBCQEN_SHIFT)) & ENET_MAC_RXQ_CTRL_MCBCQEN_MASK)
#define ENET_MAC_RXQ_CTRL_PSRQ3_MASK             (0xFF000000U)
#define ENET_MAC_RXQ_CTRL_PSRQ3_SHIFT            (24U)
#define ENET_MAC_RXQ_CTRL_PSRQ3(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXQ_CTRL_PSRQ3_SHIFT)) & ENET_MAC_RXQ_CTRL_PSRQ3_MASK)

/* The count of ENET_MAC_RXQ_CTRL */
#define ENET_MAC_RXQ_CTRL_COUNT                  (3U)

/*! @name MAC_INTR_STAT - Interrupt status register 0x0000 */
#define ENET_MAC_INTR_STAT_PHYIS_MASK            (0x8U)
#define ENET_MAC_INTR_STAT_PHYIS_SHIFT           (3U)
#define ENET_MAC_INTR_STAT_PHYIS(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_INTR_STAT_PHYIS_SHIFT)) & ENET_MAC_INTR_STAT_PHYIS_MASK)
#define ENET_MAC_INTR_STAT_PMTIS_MASK            (0x10U)
#define ENET_MAC_INTR_STAT_PMTIS_SHIFT           (4U)
#define ENET_MAC_INTR_STAT_PMTIS(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_INTR_STAT_PMTIS_SHIFT)) & ENET_MAC_INTR_STAT_PMTIS_MASK)
#define ENET_MAC_INTR_STAT_LPIIS_MASK            (0x20U)
#define ENET_MAC_INTR_STAT_LPIIS_SHIFT           (5U)
#define ENET_MAC_INTR_STAT_LPIIS(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_INTR_STAT_LPIIS_SHIFT)) & ENET_MAC_INTR_STAT_LPIIS_MASK)
#define ENET_MAC_INTR_STAT_TSIS_MASK             (0x1000U)
#define ENET_MAC_INTR_STAT_TSIS_SHIFT            (12U)
#define ENET_MAC_INTR_STAT_TSIS(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_INTR_STAT_TSIS_SHIFT)) & ENET_MAC_INTR_STAT_TSIS_MASK)
#define ENET_MAC_INTR_STAT_TXSTSIS_MASK          (0x2000U)
#define ENET_MAC_INTR_STAT_TXSTSIS_SHIFT         (13U)
#define ENET_MAC_INTR_STAT_TXSTSIS(x)            (((uint32_t)(((uint32_t)(x)) << ENET_MAC_INTR_STAT_TXSTSIS_SHIFT)) & ENET_MAC_INTR_STAT_TXSTSIS_MASK)
#define ENET_MAC_INTR_STAT_RXSTSIS_MASK          (0x4000U)
#define ENET_MAC_INTR_STAT_RXSTSIS_SHIFT         (14U)
#define ENET_MAC_INTR_STAT_RXSTSIS(x)            (((uint32_t)(((uint32_t)(x)) << ENET_MAC_INTR_STAT_RXSTSIS_SHIFT)) & ENET_MAC_INTR_STAT_RXSTSIS_MASK)

/*! @name MAC_INTR_EN - Interrupt enable register 0x0000 */
#define ENET_MAC_INTR_EN_PHYIE_MASK              (0x8U)
#define ENET_MAC_INTR_EN_PHYIE_SHIFT             (3U)
#define ENET_MAC_INTR_EN_PHYIE(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_INTR_EN_PHYIE_SHIFT)) & ENET_MAC_INTR_EN_PHYIE_MASK)
#define ENET_MAC_INTR_EN_PMTIE_MASK              (0x10U)
#define ENET_MAC_INTR_EN_PMTIE_SHIFT             (4U)
#define ENET_MAC_INTR_EN_PMTIE(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_INTR_EN_PMTIE_SHIFT)) & ENET_MAC_INTR_EN_PMTIE_MASK)
#define ENET_MAC_INTR_EN_LPIIE_MASK              (0x20U)
#define ENET_MAC_INTR_EN_LPIIE_SHIFT             (5U)
#define ENET_MAC_INTR_EN_LPIIE(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_INTR_EN_LPIIE_SHIFT)) & ENET_MAC_INTR_EN_LPIIE_MASK)
#define ENET_MAC_INTR_EN_TSIE_MASK               (0x1000U)
#define ENET_MAC_INTR_EN_TSIE_SHIFT              (12U)
#define ENET_MAC_INTR_EN_TSIE(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_MAC_INTR_EN_TSIE_SHIFT)) & ENET_MAC_INTR_EN_TSIE_MASK)
#define ENET_MAC_INTR_EN_TXSTSIE_MASK            (0x2000U)
#define ENET_MAC_INTR_EN_TXSTSIE_SHIFT           (13U)
#define ENET_MAC_INTR_EN_TXSTSIE(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_INTR_EN_TXSTSIE_SHIFT)) & ENET_MAC_INTR_EN_TXSTSIE_MASK)
#define ENET_MAC_INTR_EN_RXSTSIS_MASK            (0x4000U)
#define ENET_MAC_INTR_EN_RXSTSIS_SHIFT           (14U)
#define ENET_MAC_INTR_EN_RXSTSIS(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_INTR_EN_RXSTSIS_SHIFT)) & ENET_MAC_INTR_EN_RXSTSIS_MASK)

/*! @name MAC_RXTX_STAT - Receive Transmit Status register */
#define ENET_MAC_RXTX_STAT_TJT_MASK              (0x1U)
#define ENET_MAC_RXTX_STAT_TJT_SHIFT             (0U)
#define ENET_MAC_RXTX_STAT_TJT(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXTX_STAT_TJT_SHIFT)) & ENET_MAC_RXTX_STAT_TJT_MASK)
#define ENET_MAC_RXTX_STAT_NCARR_MASK            (0x2U)
#define ENET_MAC_RXTX_STAT_NCARR_SHIFT           (1U)
#define ENET_MAC_RXTX_STAT_NCARR(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXTX_STAT_NCARR_SHIFT)) & ENET_MAC_RXTX_STAT_NCARR_MASK)
#define ENET_MAC_RXTX_STAT_LCARR_MASK            (0x4U)
#define ENET_MAC_RXTX_STAT_LCARR_SHIFT           (2U)
#define ENET_MAC_RXTX_STAT_LCARR(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXTX_STAT_LCARR_SHIFT)) & ENET_MAC_RXTX_STAT_LCARR_MASK)
#define ENET_MAC_RXTX_STAT_EXDEF_MASK            (0x8U)
#define ENET_MAC_RXTX_STAT_EXDEF_SHIFT           (3U)
#define ENET_MAC_RXTX_STAT_EXDEF(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXTX_STAT_EXDEF_SHIFT)) & ENET_MAC_RXTX_STAT_EXDEF_MASK)
#define ENET_MAC_RXTX_STAT_LCOL_MASK             (0x10U)
#define ENET_MAC_RXTX_STAT_LCOL_SHIFT            (4U)
#define ENET_MAC_RXTX_STAT_LCOL(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXTX_STAT_LCOL_SHIFT)) & ENET_MAC_RXTX_STAT_LCOL_MASK)
#define ENET_MAC_RXTX_STAT_EXCOL_MASK            (0x20U)
#define ENET_MAC_RXTX_STAT_EXCOL_SHIFT           (5U)
#define ENET_MAC_RXTX_STAT_EXCOL(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXTX_STAT_EXCOL_SHIFT)) & ENET_MAC_RXTX_STAT_EXCOL_MASK)
#define ENET_MAC_RXTX_STAT_RWT_MASK              (0x100U)
#define ENET_MAC_RXTX_STAT_RWT_SHIFT             (8U)
#define ENET_MAC_RXTX_STAT_RWT(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RXTX_STAT_RWT_SHIFT)) & ENET_MAC_RXTX_STAT_RWT_MASK)

/*! @name MAC_PMT_CRTL_STAT -  */
#define ENET_MAC_PMT_CRTL_STAT_PWRDWN_MASK       (0x1U)
#define ENET_MAC_PMT_CRTL_STAT_PWRDWN_SHIFT      (0U)
#define ENET_MAC_PMT_CRTL_STAT_PWRDWN(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MAC_PMT_CRTL_STAT_PWRDWN_SHIFT)) & ENET_MAC_PMT_CRTL_STAT_PWRDWN_MASK)
#define ENET_MAC_PMT_CRTL_STAT_MGKPKTEN_MASK     (0x2U)
#define ENET_MAC_PMT_CRTL_STAT_MGKPKTEN_SHIFT    (1U)
#define ENET_MAC_PMT_CRTL_STAT_MGKPKTEN(x)       (((uint32_t)(((uint32_t)(x)) << ENET_MAC_PMT_CRTL_STAT_MGKPKTEN_SHIFT)) & ENET_MAC_PMT_CRTL_STAT_MGKPKTEN_MASK)
#define ENET_MAC_PMT_CRTL_STAT_RWKPKTEN_MASK     (0x4U)
#define ENET_MAC_PMT_CRTL_STAT_RWKPKTEN_SHIFT    (2U)
#define ENET_MAC_PMT_CRTL_STAT_RWKPKTEN(x)       (((uint32_t)(((uint32_t)(x)) << ENET_MAC_PMT_CRTL_STAT_RWKPKTEN_SHIFT)) & ENET_MAC_PMT_CRTL_STAT_RWKPKTEN_MASK)
#define ENET_MAC_PMT_CRTL_STAT_MGKPRCVD_MASK     (0x20U)
#define ENET_MAC_PMT_CRTL_STAT_MGKPRCVD_SHIFT    (5U)
#define ENET_MAC_PMT_CRTL_STAT_MGKPRCVD(x)       (((uint32_t)(((uint32_t)(x)) << ENET_MAC_PMT_CRTL_STAT_MGKPRCVD_SHIFT)) & ENET_MAC_PMT_CRTL_STAT_MGKPRCVD_MASK)
#define ENET_MAC_PMT_CRTL_STAT_RWKPRCVD_MASK     (0x40U)
#define ENET_MAC_PMT_CRTL_STAT_RWKPRCVD_SHIFT    (6U)
#define ENET_MAC_PMT_CRTL_STAT_RWKPRCVD(x)       (((uint32_t)(((uint32_t)(x)) << ENET_MAC_PMT_CRTL_STAT_RWKPRCVD_SHIFT)) & ENET_MAC_PMT_CRTL_STAT_RWKPRCVD_MASK)
#define ENET_MAC_PMT_CRTL_STAT_GLBLUCAST_MASK    (0x200U)
#define ENET_MAC_PMT_CRTL_STAT_GLBLUCAST_SHIFT   (9U)
#define ENET_MAC_PMT_CRTL_STAT_GLBLUCAST(x)      (((uint32_t)(((uint32_t)(x)) << ENET_MAC_PMT_CRTL_STAT_GLBLUCAST_SHIFT)) & ENET_MAC_PMT_CRTL_STAT_GLBLUCAST_MASK)
#define ENET_MAC_PMT_CRTL_STAT_RWKPFE_MASK       (0x400U)
#define ENET_MAC_PMT_CRTL_STAT_RWKPFE_SHIFT      (10U)
#define ENET_MAC_PMT_CRTL_STAT_RWKPFE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MAC_PMT_CRTL_STAT_RWKPFE_SHIFT)) & ENET_MAC_PMT_CRTL_STAT_RWKPFE_MASK)
#define ENET_MAC_PMT_CRTL_STAT_RWKPTR_MASK       (0x1F000000U)
#define ENET_MAC_PMT_CRTL_STAT_RWKPTR_SHIFT      (24U)
#define ENET_MAC_PMT_CRTL_STAT_RWKPTR(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MAC_PMT_CRTL_STAT_RWKPTR_SHIFT)) & ENET_MAC_PMT_CRTL_STAT_RWKPTR_MASK)
#define ENET_MAC_PMT_CRTL_STAT_RWKFILTRST_MASK   (0x80000000U)
#define ENET_MAC_PMT_CRTL_STAT_RWKFILTRST_SHIFT  (31U)
#define ENET_MAC_PMT_CRTL_STAT_RWKFILTRST(x)     (((uint32_t)(((uint32_t)(x)) << ENET_MAC_PMT_CRTL_STAT_RWKFILTRST_SHIFT)) & ENET_MAC_PMT_CRTL_STAT_RWKFILTRST_MASK)

/*! @name MAC_RWAKE_FRFLT - Remote wake-up frame filter */
#define ENET_MAC_RWAKE_FRFLT_ADDR_MASK           (0xFFFFFFFFU)
#define ENET_MAC_RWAKE_FRFLT_ADDR_SHIFT          (0U)
#define ENET_MAC_RWAKE_FRFLT_ADDR(x)             (((uint32_t)(((uint32_t)(x)) << ENET_MAC_RWAKE_FRFLT_ADDR_SHIFT)) & ENET_MAC_RWAKE_FRFLT_ADDR_MASK)

/*! @name MAC_LPI_CTRL_STAT - LPI Control and Status Register */
#define ENET_MAC_LPI_CTRL_STAT_TLPIEN_MASK       (0x1U)
#define ENET_MAC_LPI_CTRL_STAT_TLPIEN_SHIFT      (0U)
#define ENET_MAC_LPI_CTRL_STAT_TLPIEN(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_CTRL_STAT_TLPIEN_SHIFT)) & ENET_MAC_LPI_CTRL_STAT_TLPIEN_MASK)
#define ENET_MAC_LPI_CTRL_STAT_TLPIEX_MASK       (0x2U)
#define ENET_MAC_LPI_CTRL_STAT_TLPIEX_SHIFT      (1U)
#define ENET_MAC_LPI_CTRL_STAT_TLPIEX(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_CTRL_STAT_TLPIEX_SHIFT)) & ENET_MAC_LPI_CTRL_STAT_TLPIEX_MASK)
#define ENET_MAC_LPI_CTRL_STAT_RLPIEN_MASK       (0x4U)
#define ENET_MAC_LPI_CTRL_STAT_RLPIEN_SHIFT      (2U)
#define ENET_MAC_LPI_CTRL_STAT_RLPIEN(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_CTRL_STAT_RLPIEN_SHIFT)) & ENET_MAC_LPI_CTRL_STAT_RLPIEN_MASK)
#define ENET_MAC_LPI_CTRL_STAT_RLPIEX_MASK       (0x8U)
#define ENET_MAC_LPI_CTRL_STAT_RLPIEX_SHIFT      (3U)
#define ENET_MAC_LPI_CTRL_STAT_RLPIEX(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_CTRL_STAT_RLPIEX_SHIFT)) & ENET_MAC_LPI_CTRL_STAT_RLPIEX_MASK)
#define ENET_MAC_LPI_CTRL_STAT_TLPIST_MASK       (0x100U)
#define ENET_MAC_LPI_CTRL_STAT_TLPIST_SHIFT      (8U)
#define ENET_MAC_LPI_CTRL_STAT_TLPIST(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_CTRL_STAT_TLPIST_SHIFT)) & ENET_MAC_LPI_CTRL_STAT_TLPIST_MASK)
#define ENET_MAC_LPI_CTRL_STAT_RLPIST_MASK       (0x200U)
#define ENET_MAC_LPI_CTRL_STAT_RLPIST_SHIFT      (9U)
#define ENET_MAC_LPI_CTRL_STAT_RLPIST(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_CTRL_STAT_RLPIST_SHIFT)) & ENET_MAC_LPI_CTRL_STAT_RLPIST_MASK)
#define ENET_MAC_LPI_CTRL_STAT_LPIEN_MASK        (0x10000U)
#define ENET_MAC_LPI_CTRL_STAT_LPIEN_SHIFT       (16U)
#define ENET_MAC_LPI_CTRL_STAT_LPIEN(x)          (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_CTRL_STAT_LPIEN_SHIFT)) & ENET_MAC_LPI_CTRL_STAT_LPIEN_MASK)
#define ENET_MAC_LPI_CTRL_STAT_PLS_MASK          (0x20000U)
#define ENET_MAC_LPI_CTRL_STAT_PLS_SHIFT         (17U)
#define ENET_MAC_LPI_CTRL_STAT_PLS(x)            (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_CTRL_STAT_PLS_SHIFT)) & ENET_MAC_LPI_CTRL_STAT_PLS_MASK)
#define ENET_MAC_LPI_CTRL_STAT_LPITXA_MASK       (0x80000U)
#define ENET_MAC_LPI_CTRL_STAT_LPITXA_SHIFT      (19U)
#define ENET_MAC_LPI_CTRL_STAT_LPITXA(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_CTRL_STAT_LPITXA_SHIFT)) & ENET_MAC_LPI_CTRL_STAT_LPITXA_MASK)
#define ENET_MAC_LPI_CTRL_STAT_LPIATE_MASK       (0x100000U)
#define ENET_MAC_LPI_CTRL_STAT_LPIATE_SHIFT      (20U)
#define ENET_MAC_LPI_CTRL_STAT_LPIATE(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_CTRL_STAT_LPIATE_SHIFT)) & ENET_MAC_LPI_CTRL_STAT_LPIATE_MASK)
#define ENET_MAC_LPI_CTRL_STAT_LPITCSE_MASK      (0x200000U)
#define ENET_MAC_LPI_CTRL_STAT_LPITCSE_SHIFT     (21U)
#define ENET_MAC_LPI_CTRL_STAT_LPITCSE(x)        (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_CTRL_STAT_LPITCSE_SHIFT)) & ENET_MAC_LPI_CTRL_STAT_LPITCSE_MASK)

/*! @name MAC_LPI_TIMER_CTRL - LPI Timers Control register */
#define ENET_MAC_LPI_TIMER_CTRL_TWT_MASK         (0xFFFFU)
#define ENET_MAC_LPI_TIMER_CTRL_TWT_SHIFT        (0U)
#define ENET_MAC_LPI_TIMER_CTRL_TWT(x)           (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_TIMER_CTRL_TWT_SHIFT)) & ENET_MAC_LPI_TIMER_CTRL_TWT_MASK)
#define ENET_MAC_LPI_TIMER_CTRL_LST_MASK         (0x3FF0000U)
#define ENET_MAC_LPI_TIMER_CTRL_LST_SHIFT        (16U)
#define ENET_MAC_LPI_TIMER_CTRL_LST(x)           (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_TIMER_CTRL_LST_SHIFT)) & ENET_MAC_LPI_TIMER_CTRL_LST_MASK)

/*! @name MAC_LPI_ENTR_TIMR - LPI entry Timer register */
#define ENET_MAC_LPI_ENTR_TIMR_LPIET_MASK        (0xFFFF8U)
#define ENET_MAC_LPI_ENTR_TIMR_LPIET_SHIFT       (3U)
#define ENET_MAC_LPI_ENTR_TIMR_LPIET(x)          (((uint32_t)(((uint32_t)(x)) << ENET_MAC_LPI_ENTR_TIMR_LPIET_SHIFT)) & ENET_MAC_LPI_ENTR_TIMR_LPIET_MASK)

/*! @name MAC_1US_TIC_COUNTR -  */
#define ENET_MAC_1US_TIC_COUNTR_TIC_1US_CNTR_MASK (0xFFFU)
#define ENET_MAC_1US_TIC_COUNTR_TIC_1US_CNTR_SHIFT (0U)
#define ENET_MAC_1US_TIC_COUNTR_TIC_1US_CNTR(x)  (((uint32_t)(((uint32_t)(x)) << ENET_MAC_1US_TIC_COUNTR_TIC_1US_CNTR_SHIFT)) & ENET_MAC_1US_TIC_COUNTR_TIC_1US_CNTR_MASK)

/*! @name MAC_VERSION - MAC version register */
#define ENET_MAC_VERSION_SNPVER_MASK             (0xFFU)
#define ENET_MAC_VERSION_SNPVER_SHIFT            (0U)
#define ENET_MAC_VERSION_SNPVER(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VERSION_SNPVER_SHIFT)) & ENET_MAC_VERSION_SNPVER_MASK)
#define ENET_MAC_VERSION_USERVER_MASK            (0xFF00U)
#define ENET_MAC_VERSION_USERVER_SHIFT           (8U)
#define ENET_MAC_VERSION_USERVER(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_VERSION_USERVER_SHIFT)) & ENET_MAC_VERSION_USERVER_MASK)

/*! @name MAC_DBG - MAC debug register */
#define ENET_MAC_DBG_REPESTS_MASK                (0x1U)
#define ENET_MAC_DBG_REPESTS_SHIFT               (0U)
#define ENET_MAC_DBG_REPESTS(x)                  (((uint32_t)(((uint32_t)(x)) << ENET_MAC_DBG_REPESTS_SHIFT)) & ENET_MAC_DBG_REPESTS_MASK)
#define ENET_MAC_DBG_RFCFCSTS_MASK               (0x6U)
#define ENET_MAC_DBG_RFCFCSTS_SHIFT              (1U)
#define ENET_MAC_DBG_RFCFCSTS(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_MAC_DBG_RFCFCSTS_SHIFT)) & ENET_MAC_DBG_RFCFCSTS_MASK)
#define ENET_MAC_DBG_TPESTS_MASK                 (0x10000U)
#define ENET_MAC_DBG_TPESTS_SHIFT                (16U)
#define ENET_MAC_DBG_TPESTS(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_MAC_DBG_TPESTS_SHIFT)) & ENET_MAC_DBG_TPESTS_MASK)
#define ENET_MAC_DBG_TFCSTS_MASK                 (0x60000U)
#define ENET_MAC_DBG_TFCSTS_SHIFT                (17U)
#define ENET_MAC_DBG_TFCSTS(x)                   (((uint32_t)(((uint32_t)(x)) << ENET_MAC_DBG_TFCSTS_SHIFT)) & ENET_MAC_DBG_TFCSTS_MASK)

/*! @name MAC_HW_FEAT - MAC hardware feature register 0x0201 */
#define ENET_MAC_HW_FEAT_RXFIFOSIZE_MASK         (0x1FU)
#define ENET_MAC_HW_FEAT_RXFIFOSIZE_SHIFT        (0U)
#define ENET_MAC_HW_FEAT_RXFIFOSIZE(x)           (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_RXFIFOSIZE_SHIFT)) & ENET_MAC_HW_FEAT_RXFIFOSIZE_MASK)
#define ENET_MAC_HW_FEAT_RXQCNT_MASK             (0xFU)
#define ENET_MAC_HW_FEAT_RXQCNT_SHIFT            (0U)
#define ENET_MAC_HW_FEAT_RXQCNT(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_RXQCNT_SHIFT)) & ENET_MAC_HW_FEAT_RXQCNT_MASK)
#define ENET_MAC_HW_FEAT_MIISEL_MASK             (0x1U)
#define ENET_MAC_HW_FEAT_MIISEL_SHIFT            (0U)
#define ENET_MAC_HW_FEAT_MIISEL(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_MIISEL_SHIFT)) & ENET_MAC_HW_FEAT_MIISEL_MASK)
#define ENET_MAC_HW_FEAT_HDSEL_MASK              (0x4U)
#define ENET_MAC_HW_FEAT_HDSEL_SHIFT             (2U)
#define ENET_MAC_HW_FEAT_HDSEL(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_HDSEL_SHIFT)) & ENET_MAC_HW_FEAT_HDSEL_MASK)
#define ENET_MAC_HW_FEAT_VLHASH_MASK             (0x10U)
#define ENET_MAC_HW_FEAT_VLHASH_SHIFT            (4U)
#define ENET_MAC_HW_FEAT_VLHASH(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_VLHASH_SHIFT)) & ENET_MAC_HW_FEAT_VLHASH_MASK)
#define ENET_MAC_HW_FEAT_SMASEL_MASK             (0x20U)
#define ENET_MAC_HW_FEAT_SMASEL_SHIFT            (5U)
#define ENET_MAC_HW_FEAT_SMASEL(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_SMASEL_SHIFT)) & ENET_MAC_HW_FEAT_SMASEL_MASK)
#define ENET_MAC_HW_FEAT_TXQCNT_MASK             (0x3C0U)
#define ENET_MAC_HW_FEAT_TXQCNT_SHIFT            (6U)
#define ENET_MAC_HW_FEAT_TXQCNT(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_TXQCNT_SHIFT)) & ENET_MAC_HW_FEAT_TXQCNT_MASK)
#define ENET_MAC_HW_FEAT_RWKSEL_MASK             (0x40U)
#define ENET_MAC_HW_FEAT_RWKSEL_SHIFT            (6U)
#define ENET_MAC_HW_FEAT_RWKSEL(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_RWKSEL_SHIFT)) & ENET_MAC_HW_FEAT_RWKSEL_MASK)
#define ENET_MAC_HW_FEAT_TXFIFOSIZE_MASK         (0x7C0U)
#define ENET_MAC_HW_FEAT_TXFIFOSIZE_SHIFT        (6U)
#define ENET_MAC_HW_FEAT_TXFIFOSIZE(x)           (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_TXFIFOSIZE_SHIFT)) & ENET_MAC_HW_FEAT_TXFIFOSIZE_MASK)
#define ENET_MAC_HW_FEAT_MGKSEL_MASK             (0x80U)
#define ENET_MAC_HW_FEAT_MGKSEL_SHIFT            (7U)
#define ENET_MAC_HW_FEAT_MGKSEL(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_MGKSEL_SHIFT)) & ENET_MAC_HW_FEAT_MGKSEL_MASK)
#define ENET_MAC_HW_FEAT_MMCSEL_MASK             (0x100U)
#define ENET_MAC_HW_FEAT_MMCSEL_SHIFT            (8U)
#define ENET_MAC_HW_FEAT_MMCSEL(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_MMCSEL_SHIFT)) & ENET_MAC_HW_FEAT_MMCSEL_MASK)
#define ENET_MAC_HW_FEAT_ARPOFFSEL_MASK          (0x200U)
#define ENET_MAC_HW_FEAT_ARPOFFSEL_SHIFT         (9U)
#define ENET_MAC_HW_FEAT_ARPOFFSEL(x)            (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_ARPOFFSEL_SHIFT)) & ENET_MAC_HW_FEAT_ARPOFFSEL_MASK)
#define ENET_MAC_HW_FEAT_OSTEN_MASK              (0x800U)
#define ENET_MAC_HW_FEAT_OSTEN_SHIFT             (11U)
#define ENET_MAC_HW_FEAT_OSTEN(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_OSTEN_SHIFT)) & ENET_MAC_HW_FEAT_OSTEN_MASK)
#define ENET_MAC_HW_FEAT_RXCHCNT_MASK            (0xF000U)
#define ENET_MAC_HW_FEAT_RXCHCNT_SHIFT           (12U)
#define ENET_MAC_HW_FEAT_RXCHCNT(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_RXCHCNT_SHIFT)) & ENET_MAC_HW_FEAT_RXCHCNT_MASK)
#define ENET_MAC_HW_FEAT_TSSEL_MASK              (0x1000U)
#define ENET_MAC_HW_FEAT_TSSEL_SHIFT             (12U)
#define ENET_MAC_HW_FEAT_TSSEL(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_TSSEL_SHIFT)) & ENET_MAC_HW_FEAT_TSSEL_MASK)
#define ENET_MAC_HW_FEAT_PTOEN_MASK              (0x1000U)
#define ENET_MAC_HW_FEAT_PTOEN_SHIFT             (12U)
#define ENET_MAC_HW_FEAT_PTOEN(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_PTOEN_SHIFT)) & ENET_MAC_HW_FEAT_PTOEN_MASK)
#define ENET_MAC_HW_FEAT_EEESEL_MASK             (0x2000U)
#define ENET_MAC_HW_FEAT_EEESEL_SHIFT            (13U)
#define ENET_MAC_HW_FEAT_EEESEL(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_EEESEL_SHIFT)) & ENET_MAC_HW_FEAT_EEESEL_MASK)
#define ENET_MAC_HW_FEAT_ADVTHWORD_MASK          (0x2000U)
#define ENET_MAC_HW_FEAT_ADVTHWORD_SHIFT         (13U)
#define ENET_MAC_HW_FEAT_ADVTHWORD(x)            (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_ADVTHWORD_SHIFT)) & ENET_MAC_HW_FEAT_ADVTHWORD_MASK)
#define ENET_MAC_HW_FEAT_ADDR64_MASK             (0xC000U)
#define ENET_MAC_HW_FEAT_ADDR64_SHIFT            (14U)
#define ENET_MAC_HW_FEAT_ADDR64(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_ADDR64_SHIFT)) & ENET_MAC_HW_FEAT_ADDR64_MASK)
#define ENET_MAC_HW_FEAT_TXCOESEL_MASK           (0x4000U)
#define ENET_MAC_HW_FEAT_TXCOESEL_SHIFT          (14U)
#define ENET_MAC_HW_FEAT_TXCOESEL(x)             (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_TXCOESEL_SHIFT)) & ENET_MAC_HW_FEAT_TXCOESEL_MASK)
#define ENET_MAC_HW_FEAT_DCBEN_MASK              (0x10000U)
#define ENET_MAC_HW_FEAT_DCBEN_SHIFT             (16U)
#define ENET_MAC_HW_FEAT_DCBEN(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_DCBEN_SHIFT)) & ENET_MAC_HW_FEAT_DCBEN_MASK)
#define ENET_MAC_HW_FEAT_RXCOESEL_MASK           (0x10000U)
#define ENET_MAC_HW_FEAT_RXCOESEL_SHIFT          (16U)
#define ENET_MAC_HW_FEAT_RXCOESEL(x)             (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_RXCOESEL_SHIFT)) & ENET_MAC_HW_FEAT_RXCOESEL_MASK)
#define ENET_MAC_HW_FEAT_SPEN_MASK               (0x20000U)
#define ENET_MAC_HW_FEAT_SPEN_SHIFT              (17U)
#define ENET_MAC_HW_FEAT_SPEN(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_SPEN_SHIFT)) & ENET_MAC_HW_FEAT_SPEN_MASK)
#define ENET_MAC_HW_FEAT_TXCHCNT_MASK            (0x3C0000U)
#define ENET_MAC_HW_FEAT_TXCHCNT_SHIFT           (18U)
#define ENET_MAC_HW_FEAT_TXCHCNT(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_TXCHCNT_SHIFT)) & ENET_MAC_HW_FEAT_TXCHCNT_MASK)
#define ENET_MAC_HW_FEAT_TSOEN_MASK              (0x40000U)
#define ENET_MAC_HW_FEAT_TSOEN_SHIFT             (18U)
#define ENET_MAC_HW_FEAT_TSOEN(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_TSOEN_SHIFT)) & ENET_MAC_HW_FEAT_TSOEN_MASK)
#define ENET_MAC_HW_FEAT_DBGMEMA_MASK            (0x80000U)
#define ENET_MAC_HW_FEAT_DBGMEMA_SHIFT           (19U)
#define ENET_MAC_HW_FEAT_DBGMEMA(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_DBGMEMA_SHIFT)) & ENET_MAC_HW_FEAT_DBGMEMA_MASK)
#define ENET_MAC_HW_FEAT_AVSEL_MASK              (0x100000U)
#define ENET_MAC_HW_FEAT_AVSEL_SHIFT             (20U)
#define ENET_MAC_HW_FEAT_AVSEL(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_AVSEL_SHIFT)) & ENET_MAC_HW_FEAT_AVSEL_MASK)
#define ENET_MAC_HW_FEAT_LPMODEEN_MASK           (0x800000U)
#define ENET_MAC_HW_FEAT_LPMODEEN_SHIFT          (23U)
#define ENET_MAC_HW_FEAT_LPMODEEN(x)             (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_LPMODEEN_SHIFT)) & ENET_MAC_HW_FEAT_LPMODEEN_MASK)
#define ENET_MAC_HW_FEAT_PPSOUTNUM_MASK          (0x7000000U)
#define ENET_MAC_HW_FEAT_PPSOUTNUM_SHIFT         (24U)
#define ENET_MAC_HW_FEAT_PPSOUTNUM(x)            (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_PPSOUTNUM_SHIFT)) & ENET_MAC_HW_FEAT_PPSOUTNUM_MASK)
#define ENET_MAC_HW_FEAT_HASHTBLSZ_MASK          (0x3000000U)
#define ENET_MAC_HW_FEAT_HASHTBLSZ_SHIFT         (24U)
#define ENET_MAC_HW_FEAT_HASHTBLSZ(x)            (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_HASHTBLSZ_SHIFT)) & ENET_MAC_HW_FEAT_HASHTBLSZ_MASK)
#define ENET_MAC_HW_FEAT_TSSTSSEL_MASK           (0x6000000U)
#define ENET_MAC_HW_FEAT_TSSTSSEL_SHIFT          (25U)
#define ENET_MAC_HW_FEAT_TSSTSSEL(x)             (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_TSSTSSEL_SHIFT)) & ENET_MAC_HW_FEAT_TSSTSSEL_MASK)
#define ENET_MAC_HW_FEAT_L3_L4_FILTER_MASK       (0x78000000U)
#define ENET_MAC_HW_FEAT_L3_L4_FILTER_SHIFT      (27U)
#define ENET_MAC_HW_FEAT_L3_L4_FILTER(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_L3_L4_FILTER_SHIFT)) & ENET_MAC_HW_FEAT_L3_L4_FILTER_MASK)
#define ENET_MAC_HW_FEAT_AUXSNAPNUM_MASK         (0x70000000U)
#define ENET_MAC_HW_FEAT_AUXSNAPNUM_SHIFT        (28U)
#define ENET_MAC_HW_FEAT_AUXSNAPNUM(x)           (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_AUXSNAPNUM_SHIFT)) & ENET_MAC_HW_FEAT_AUXSNAPNUM_MASK)
#define ENET_MAC_HW_FEAT_ACTPHYSEL_MASK          (0x70000000U)
#define ENET_MAC_HW_FEAT_ACTPHYSEL_SHIFT         (28U)
#define ENET_MAC_HW_FEAT_ACTPHYSEL(x)            (((uint32_t)(((uint32_t)(x)) << ENET_MAC_HW_FEAT_ACTPHYSEL_SHIFT)) & ENET_MAC_HW_FEAT_ACTPHYSEL_MASK)

/* The count of ENET_MAC_HW_FEAT */
#define ENET_MAC_HW_FEAT_COUNT                   (3U)

/*! @name MAC_MDIO_ADDR - MIDO address Register */
#define ENET_MAC_MDIO_ADDR_MB_MASK               (0x1U)
#define ENET_MAC_MDIO_ADDR_MB_SHIFT              (0U)
#define ENET_MAC_MDIO_ADDR_MB(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_MAC_MDIO_ADDR_MB_SHIFT)) & ENET_MAC_MDIO_ADDR_MB_MASK)
#define ENET_MAC_MDIO_ADDR_MOC_MASK              (0xCU)
#define ENET_MAC_MDIO_ADDR_MOC_SHIFT             (2U)
#define ENET_MAC_MDIO_ADDR_MOC(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_MDIO_ADDR_MOC_SHIFT)) & ENET_MAC_MDIO_ADDR_MOC_MASK)
#define ENET_MAC_MDIO_ADDR_CR_MASK               (0xF00U)
#define ENET_MAC_MDIO_ADDR_CR_SHIFT              (8U)
#define ENET_MAC_MDIO_ADDR_CR(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_MAC_MDIO_ADDR_CR_SHIFT)) & ENET_MAC_MDIO_ADDR_CR_MASK)
#define ENET_MAC_MDIO_ADDR_NTC_MASK              (0x7000U)
#define ENET_MAC_MDIO_ADDR_NTC_SHIFT             (12U)
#define ENET_MAC_MDIO_ADDR_NTC(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_MDIO_ADDR_NTC_SHIFT)) & ENET_MAC_MDIO_ADDR_NTC_MASK)
#define ENET_MAC_MDIO_ADDR_RDA_MASK              (0x1F0000U)
#define ENET_MAC_MDIO_ADDR_RDA_SHIFT             (16U)
#define ENET_MAC_MDIO_ADDR_RDA(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_MDIO_ADDR_RDA_SHIFT)) & ENET_MAC_MDIO_ADDR_RDA_MASK)
#define ENET_MAC_MDIO_ADDR_PA_MASK               (0x3E00000U)
#define ENET_MAC_MDIO_ADDR_PA_SHIFT              (21U)
#define ENET_MAC_MDIO_ADDR_PA(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_MAC_MDIO_ADDR_PA_SHIFT)) & ENET_MAC_MDIO_ADDR_PA_MASK)
#define ENET_MAC_MDIO_ADDR_BTB_MASK              (0x4000000U)
#define ENET_MAC_MDIO_ADDR_BTB_SHIFT             (26U)
#define ENET_MAC_MDIO_ADDR_BTB(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_MDIO_ADDR_BTB_SHIFT)) & ENET_MAC_MDIO_ADDR_BTB_MASK)
#define ENET_MAC_MDIO_ADDR_PSE_MASK              (0x8000000U)
#define ENET_MAC_MDIO_ADDR_PSE_SHIFT             (27U)
#define ENET_MAC_MDIO_ADDR_PSE(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_MDIO_ADDR_PSE_SHIFT)) & ENET_MAC_MDIO_ADDR_PSE_MASK)

/*! @name MAC_MDIO_DATA - MDIO Data register */
#define ENET_MAC_MDIO_DATA_MD_MASK               (0xFFFFU)
#define ENET_MAC_MDIO_DATA_MD_SHIFT              (0U)
#define ENET_MAC_MDIO_DATA_MD(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_MAC_MDIO_DATA_MD_SHIFT)) & ENET_MAC_MDIO_DATA_MD_MASK)

/*! @name MAC_ADDR_HIGH - MAC address0 high register */
#define ENET_MAC_ADDR_HIGH_A47_32_MASK           (0xFFFFU)
#define ENET_MAC_ADDR_HIGH_A47_32_SHIFT          (0U)
#define ENET_MAC_ADDR_HIGH_A47_32(x)             (((uint32_t)(((uint32_t)(x)) << ENET_MAC_ADDR_HIGH_A47_32_SHIFT)) & ENET_MAC_ADDR_HIGH_A47_32_MASK)
#define ENET_MAC_ADDR_HIGH_DCS_MASK              (0x10000U)
#define ENET_MAC_ADDR_HIGH_DCS_SHIFT             (16U)
#define ENET_MAC_ADDR_HIGH_DCS(x)                (((uint32_t)(((uint32_t)(x)) << ENET_MAC_ADDR_HIGH_DCS_SHIFT)) & ENET_MAC_ADDR_HIGH_DCS_MASK)
#define ENET_MAC_ADDR_HIGH_AE_MASK               (0x80000000U)
#define ENET_MAC_ADDR_HIGH_AE_SHIFT              (31U)
#define ENET_MAC_ADDR_HIGH_AE(x)                 (((uint32_t)(((uint32_t)(x)) << ENET_MAC_ADDR_HIGH_AE_SHIFT)) & ENET_MAC_ADDR_HIGH_AE_MASK)

/*! @name MAC_ADDR_LOW - MAC address0 low register */
#define ENET_MAC_ADDR_LOW_A31_0_MASK             (0xFFFFFFFFU)
#define ENET_MAC_ADDR_LOW_A31_0_SHIFT            (0U)
#define ENET_MAC_ADDR_LOW_A31_0(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MAC_ADDR_LOW_A31_0_SHIFT)) & ENET_MAC_ADDR_LOW_A31_0_MASK)

/*! @name MAC_TIMESTAMP_CTRL - Time stamp control register */
#define ENET_MAC_TIMESTAMP_CTRL_TSENA_MASK       (0x1U)
#define ENET_MAC_TIMESTAMP_CTRL_TSENA_SHIFT      (0U)
#define ENET_MAC_TIMESTAMP_CTRL_TSENA(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSENA_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSENA_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TSCFUPDT_MASK    (0x2U)
#define ENET_MAC_TIMESTAMP_CTRL_TSCFUPDT_SHIFT   (1U)
#define ENET_MAC_TIMESTAMP_CTRL_TSCFUPDT(x)      (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSCFUPDT_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSCFUPDT_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TSINIT_MASK      (0x4U)
#define ENET_MAC_TIMESTAMP_CTRL_TSINIT_SHIFT     (2U)
#define ENET_MAC_TIMESTAMP_CTRL_TSINIT(x)        (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSINIT_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSINIT_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TSUPDT_MASK      (0x8U)
#define ENET_MAC_TIMESTAMP_CTRL_TSUPDT_SHIFT     (3U)
#define ENET_MAC_TIMESTAMP_CTRL_TSUPDT(x)        (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSUPDT_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSUPDT_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TSTRIG_MASK      (0x10U)
#define ENET_MAC_TIMESTAMP_CTRL_TSTRIG_SHIFT     (4U)
#define ENET_MAC_TIMESTAMP_CTRL_TSTRIG(x)        (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSTRIG_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSTRIG_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TADDREG_MASK     (0x20U)
#define ENET_MAC_TIMESTAMP_CTRL_TADDREG_SHIFT    (5U)
#define ENET_MAC_TIMESTAMP_CTRL_TADDREG(x)       (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TADDREG_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TADDREG_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TSENALL_MASK     (0x100U)
#define ENET_MAC_TIMESTAMP_CTRL_TSENALL_SHIFT    (8U)
#define ENET_MAC_TIMESTAMP_CTRL_TSENALL(x)       (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSENALL_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSENALL_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TSCTRLSSR_MASK   (0x200U)
#define ENET_MAC_TIMESTAMP_CTRL_TSCTRLSSR_SHIFT  (9U)
#define ENET_MAC_TIMESTAMP_CTRL_TSCTRLSSR(x)     (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSCTRLSSR_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSCTRLSSR_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TSVER2ENA_MASK   (0x400U)
#define ENET_MAC_TIMESTAMP_CTRL_TSVER2ENA_SHIFT  (10U)
#define ENET_MAC_TIMESTAMP_CTRL_TSVER2ENA(x)     (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSVER2ENA_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSVER2ENA_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TSIPENA_MASK     (0x800U)
#define ENET_MAC_TIMESTAMP_CTRL_TSIPENA_SHIFT    (11U)
#define ENET_MAC_TIMESTAMP_CTRL_TSIPENA(x)       (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSIPENA_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSIPENA_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TSIPV6ENA_MASK   (0x1000U)
#define ENET_MAC_TIMESTAMP_CTRL_TSIPV6ENA_SHIFT  (12U)
#define ENET_MAC_TIMESTAMP_CTRL_TSIPV6ENA(x)     (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSIPV6ENA_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSIPV6ENA_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TSIPV4ENA_MASK   (0x2000U)
#define ENET_MAC_TIMESTAMP_CTRL_TSIPV4ENA_SHIFT  (13U)
#define ENET_MAC_TIMESTAMP_CTRL_TSIPV4ENA(x)     (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSIPV4ENA_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSIPV4ENA_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TSEVTENA_MASK    (0x4000U)
#define ENET_MAC_TIMESTAMP_CTRL_TSEVTENA_SHIFT   (14U)
#define ENET_MAC_TIMESTAMP_CTRL_TSEVTENA(x)      (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSEVTENA_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSEVTENA_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TSMSTRENA_MASK   (0x8000U)
#define ENET_MAC_TIMESTAMP_CTRL_TSMSTRENA_SHIFT  (15U)
#define ENET_MAC_TIMESTAMP_CTRL_TSMSTRENA(x)     (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSMSTRENA_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSMSTRENA_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_SNAPTYPSEL_MASK  (0x30000U)
#define ENET_MAC_TIMESTAMP_CTRL_SNAPTYPSEL_SHIFT (16U)
#define ENET_MAC_TIMESTAMP_CTRL_SNAPTYPSEL(x)    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_SNAPTYPSEL_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_SNAPTYPSEL_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TSENMACADDR_MASK (0x40000U)
#define ENET_MAC_TIMESTAMP_CTRL_TSENMACADDR_SHIFT (18U)
#define ENET_MAC_TIMESTAMP_CTRL_TSENMACADDR(x)   (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TSENMACADDR_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TSENMACADDR_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_TXTTSSTSM_MASK   (0x1000000U)
#define ENET_MAC_TIMESTAMP_CTRL_TXTTSSTSM_SHIFT  (24U)
#define ENET_MAC_TIMESTAMP_CTRL_TXTTSSTSM(x)     (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_TXTTSSTSM_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_TXTTSSTSM_MASK)
#define ENET_MAC_TIMESTAMP_CTRL_AV8021ASMEN_MASK (0x10000000U)
#define ENET_MAC_TIMESTAMP_CTRL_AV8021ASMEN_SHIFT (28U)
#define ENET_MAC_TIMESTAMP_CTRL_AV8021ASMEN(x)   (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_CTRL_AV8021ASMEN_SHIFT)) & ENET_MAC_TIMESTAMP_CTRL_AV8021ASMEN_MASK)

/*! @name MAC_SUB_SCND_INCR - Sub-second increment register */
#define ENET_MAC_SUB_SCND_INCR_SSINC_MASK        (0xFF0000U)
#define ENET_MAC_SUB_SCND_INCR_SSINC_SHIFT       (16U)
#define ENET_MAC_SUB_SCND_INCR_SSINC(x)          (((uint32_t)(((uint32_t)(x)) << ENET_MAC_SUB_SCND_INCR_SSINC_SHIFT)) & ENET_MAC_SUB_SCND_INCR_SSINC_MASK)

/*! @name MAC_SYS_TIME_SCND - System time seconds register */
#define ENET_MAC_SYS_TIME_SCND_TSS_MASK          (0xFFFFFFFFU)
#define ENET_MAC_SYS_TIME_SCND_TSS_SHIFT         (0U)
#define ENET_MAC_SYS_TIME_SCND_TSS(x)            (((uint32_t)(((uint32_t)(x)) << ENET_MAC_SYS_TIME_SCND_TSS_SHIFT)) & ENET_MAC_SYS_TIME_SCND_TSS_MASK)

/*! @name MAC_SYS_TIME_NSCND - System time nanoseconds register */
#define ENET_MAC_SYS_TIME_NSCND_TSSS_MASK        (0x7FFFFFFFU)
#define ENET_MAC_SYS_TIME_NSCND_TSSS_SHIFT       (0U)
#define ENET_MAC_SYS_TIME_NSCND_TSSS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_MAC_SYS_TIME_NSCND_TSSS_SHIFT)) & ENET_MAC_SYS_TIME_NSCND_TSSS_MASK)

/*! @name MAC_SYS_TIME_SCND_UPD -  */
#define ENET_MAC_SYS_TIME_SCND_UPD_TSS_MASK      (0xFFFFFFFFU)
#define ENET_MAC_SYS_TIME_SCND_UPD_TSS_SHIFT     (0U)
#define ENET_MAC_SYS_TIME_SCND_UPD_TSS(x)        (((uint32_t)(((uint32_t)(x)) << ENET_MAC_SYS_TIME_SCND_UPD_TSS_SHIFT)) & ENET_MAC_SYS_TIME_SCND_UPD_TSS_MASK)

/*! @name MAC_SYS_TIME_NSCND_UPD -  */
#define ENET_MAC_SYS_TIME_NSCND_UPD_TSSS_MASK    (0x7FFFFFFFU)
#define ENET_MAC_SYS_TIME_NSCND_UPD_TSSS_SHIFT   (0U)
#define ENET_MAC_SYS_TIME_NSCND_UPD_TSSS(x)      (((uint32_t)(((uint32_t)(x)) << ENET_MAC_SYS_TIME_NSCND_UPD_TSSS_SHIFT)) & ENET_MAC_SYS_TIME_NSCND_UPD_TSSS_MASK)
#define ENET_MAC_SYS_TIME_NSCND_UPD_ADDSUB_MASK  (0x80000000U)
#define ENET_MAC_SYS_TIME_NSCND_UPD_ADDSUB_SHIFT (31U)
#define ENET_MAC_SYS_TIME_NSCND_UPD_ADDSUB(x)    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_SYS_TIME_NSCND_UPD_ADDSUB_SHIFT)) & ENET_MAC_SYS_TIME_NSCND_UPD_ADDSUB_MASK)

/*! @name MAC_SYS_TIMESTMP_ADDEND - Time stamp addend register */
#define ENET_MAC_SYS_TIMESTMP_ADDEND_TSAR_MASK   (0xFFFFFFFFU)
#define ENET_MAC_SYS_TIMESTMP_ADDEND_TSAR_SHIFT  (0U)
#define ENET_MAC_SYS_TIMESTMP_ADDEND_TSAR(x)     (((uint32_t)(((uint32_t)(x)) << ENET_MAC_SYS_TIMESTMP_ADDEND_TSAR_SHIFT)) & ENET_MAC_SYS_TIMESTMP_ADDEND_TSAR_MASK)

/*! @name MAC_SYS_TIME_HWORD_SCND -  */
#define ENET_MAC_SYS_TIME_HWORD_SCND_TSHWR_MASK  (0xFFFFU)
#define ENET_MAC_SYS_TIME_HWORD_SCND_TSHWR_SHIFT (0U)
#define ENET_MAC_SYS_TIME_HWORD_SCND_TSHWR(x)    (((uint32_t)(((uint32_t)(x)) << ENET_MAC_SYS_TIME_HWORD_SCND_TSHWR_SHIFT)) & ENET_MAC_SYS_TIME_HWORD_SCND_TSHWR_MASK)

/*! @name MAC_SYS_TIMESTMP_STAT - Time stamp status register */
#define ENET_MAC_SYS_TIMESTMP_STAT_TSSOVF_MASK   (0x1U)
#define ENET_MAC_SYS_TIMESTMP_STAT_TSSOVF_SHIFT  (0U)
#define ENET_MAC_SYS_TIMESTMP_STAT_TSSOVF(x)     (((uint32_t)(((uint32_t)(x)) << ENET_MAC_SYS_TIMESTMP_STAT_TSSOVF_SHIFT)) & ENET_MAC_SYS_TIMESTMP_STAT_TSSOVF_MASK)

/*! @name MAC_TX_TIMESTAMP_STATUS_NANOSECONDS - Tx timestamp status nanoseconds */
#define ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSTSLO_MASK (0x7FFFFFFFU)
#define ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSTSLO_SHIFT (0U)
#define ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSTSLO(x) (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSTSLO_SHIFT)) & ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSTSLO_MASK)
#define ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSTSMIS_MASK (0x80000000U)
#define ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSTSMIS_SHIFT (31U)
#define ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSTSMIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSTSMIS_SHIFT)) & ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSTSMIS_MASK)

/*! @name MAC_TX_TIMESTAMP_STATUS_SECONDS - Tx timestamp status seconds */
#define ENET_MAC_TX_TIMESTAMP_STATUS_SECONDS_TXTSSTSHI_MASK (0xFFFFFFFFU)
#define ENET_MAC_TX_TIMESTAMP_STATUS_SECONDS_TXTSSTSHI_SHIFT (0U)
#define ENET_MAC_TX_TIMESTAMP_STATUS_SECONDS_TXTSSTSHI(x) (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TX_TIMESTAMP_STATUS_SECONDS_TXTSSTSHI_SHIFT)) & ENET_MAC_TX_TIMESTAMP_STATUS_SECONDS_TXTSSTSHI_MASK)

/*! @name MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND - Timestamp ingress correction */
#define ENET_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_TSIC_MASK (0xFFFFFFFFU)
#define ENET_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_TSIC_SHIFT (0U)
#define ENET_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_TSIC(x) (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_TSIC_SHIFT)) & ENET_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_TSIC_MASK)

/*! @name MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND - Timestamp egress correction */
#define ENET_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_TSEC_MASK (0xFFFFFFFFU)
#define ENET_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_TSEC_SHIFT (0U)
#define ENET_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_TSEC(x) (((uint32_t)(((uint32_t)(x)) << ENET_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_TSEC_SHIFT)) & ENET_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_TSEC_MASK)

/*! @name MTL_OP_MODE - MTL Operation Mode Register */
#define ENET_MTL_OP_MODE_DTXSTS_MASK             (0x2U)
#define ENET_MTL_OP_MODE_DTXSTS_SHIFT            (1U)
#define ENET_MTL_OP_MODE_DTXSTS(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MTL_OP_MODE_DTXSTS_SHIFT)) & ENET_MTL_OP_MODE_DTXSTS_MASK)
#define ENET_MTL_OP_MODE_RAA_MASK                (0x4U)
#define ENET_MTL_OP_MODE_RAA_SHIFT               (2U)
#define ENET_MTL_OP_MODE_RAA(x)                  (((uint32_t)(((uint32_t)(x)) << ENET_MTL_OP_MODE_RAA_SHIFT)) & ENET_MTL_OP_MODE_RAA_MASK)
#define ENET_MTL_OP_MODE_SCHALG_MASK             (0x60U)
#define ENET_MTL_OP_MODE_SCHALG_SHIFT            (5U)
#define ENET_MTL_OP_MODE_SCHALG(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MTL_OP_MODE_SCHALG_SHIFT)) & ENET_MTL_OP_MODE_SCHALG_MASK)
#define ENET_MTL_OP_MODE_CNTPRST_MASK            (0x100U)
#define ENET_MTL_OP_MODE_CNTPRST_SHIFT           (8U)
#define ENET_MTL_OP_MODE_CNTPRST(x)              (((uint32_t)(((uint32_t)(x)) << ENET_MTL_OP_MODE_CNTPRST_SHIFT)) & ENET_MTL_OP_MODE_CNTPRST_MASK)
#define ENET_MTL_OP_MODE_CNTCLR_MASK             (0x200U)
#define ENET_MTL_OP_MODE_CNTCLR_SHIFT            (9U)
#define ENET_MTL_OP_MODE_CNTCLR(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MTL_OP_MODE_CNTCLR_SHIFT)) & ENET_MTL_OP_MODE_CNTCLR_MASK)

/*! @name MTL_INTR_STAT - MTL Interrupt Status register */
#define ENET_MTL_INTR_STAT_Q0IS_MASK             (0x1U)
#define ENET_MTL_INTR_STAT_Q0IS_SHIFT            (0U)
#define ENET_MTL_INTR_STAT_Q0IS(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MTL_INTR_STAT_Q0IS_SHIFT)) & ENET_MTL_INTR_STAT_Q0IS_MASK)
#define ENET_MTL_INTR_STAT_Q1IS_MASK             (0x2U)
#define ENET_MTL_INTR_STAT_Q1IS_SHIFT            (1U)
#define ENET_MTL_INTR_STAT_Q1IS(x)               (((uint32_t)(((uint32_t)(x)) << ENET_MTL_INTR_STAT_Q1IS_SHIFT)) & ENET_MTL_INTR_STAT_Q1IS_MASK)

/*! @name MTL_RXQ_DMA_MAP - MTL Receive Queue and DMA Channel Mapping register */
#define ENET_MTL_RXQ_DMA_MAP_Q0MDMACH_MASK       (0x1U)
#define ENET_MTL_RXQ_DMA_MAP_Q0MDMACH_SHIFT      (0U)
#define ENET_MTL_RXQ_DMA_MAP_Q0MDMACH(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MTL_RXQ_DMA_MAP_Q0MDMACH_SHIFT)) & ENET_MTL_RXQ_DMA_MAP_Q0MDMACH_MASK)
#define ENET_MTL_RXQ_DMA_MAP_Q0DDMACH_MASK       (0x10U)
#define ENET_MTL_RXQ_DMA_MAP_Q0DDMACH_SHIFT      (4U)
#define ENET_MTL_RXQ_DMA_MAP_Q0DDMACH(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MTL_RXQ_DMA_MAP_Q0DDMACH_SHIFT)) & ENET_MTL_RXQ_DMA_MAP_Q0DDMACH_MASK)
#define ENET_MTL_RXQ_DMA_MAP_Q1MDMACH_MASK       (0x100U)
#define ENET_MTL_RXQ_DMA_MAP_Q1MDMACH_SHIFT      (8U)
#define ENET_MTL_RXQ_DMA_MAP_Q1MDMACH(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MTL_RXQ_DMA_MAP_Q1MDMACH_SHIFT)) & ENET_MTL_RXQ_DMA_MAP_Q1MDMACH_MASK)
#define ENET_MTL_RXQ_DMA_MAP_Q1DDMACH_MASK       (0x1000U)
#define ENET_MTL_RXQ_DMA_MAP_Q1DDMACH_SHIFT      (12U)
#define ENET_MTL_RXQ_DMA_MAP_Q1DDMACH(x)         (((uint32_t)(((uint32_t)(x)) << ENET_MTL_RXQ_DMA_MAP_Q1DDMACH_SHIFT)) & ENET_MTL_RXQ_DMA_MAP_Q1DDMACH_MASK)

/*! @name MTL_QUEUE_MTL_TXQX_OP_MODE - MTL TxQx Operation Mode register */
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_FTQ_MASK (0x1U)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_FTQ_SHIFT (0U)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_FTQ(x)   (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_FTQ_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_FTQ_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TSF_MASK (0x2U)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TSF_SHIFT (1U)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TSF(x)   (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TSF_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TSF_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TXQEN_MASK (0xCU)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TXQEN_SHIFT (2U)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TXQEN(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TXQEN_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TXQEN_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TTC_MASK (0x70U)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TTC_SHIFT (4U)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TTC(x)   (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TTC_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TTC_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TQS_MASK (0x70000U)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TQS_SHIFT (16U)
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TQS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TQS_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_TQS_MASK)

/* The count of ENET_MTL_QUEUE_MTL_TXQX_OP_MODE */
#define ENET_MTL_QUEUE_MTL_TXQX_OP_MODE_COUNT    (2U)

/*! @name MTL_QUEUE_MTL_TXQX_UNDRFLW - MTL TxQx Underflow register */
#define ENET_MTL_QUEUE_MTL_TXQX_UNDRFLW_UFFRMCNT_MASK (0x7FFU)
#define ENET_MTL_QUEUE_MTL_TXQX_UNDRFLW_UFFRMCNT_SHIFT (0U)
#define ENET_MTL_QUEUE_MTL_TXQX_UNDRFLW_UFFRMCNT(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_UNDRFLW_UFFRMCNT_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_UNDRFLW_UFFRMCNT_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_UNDRFLW_UFCNTOVF_MASK (0x800U)
#define ENET_MTL_QUEUE_MTL_TXQX_UNDRFLW_UFCNTOVF_SHIFT (11U)
#define ENET_MTL_QUEUE_MTL_TXQX_UNDRFLW_UFCNTOVF(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_UNDRFLW_UFCNTOVF_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_UNDRFLW_UFCNTOVF_MASK)

/* The count of ENET_MTL_QUEUE_MTL_TXQX_UNDRFLW */
#define ENET_MTL_QUEUE_MTL_TXQX_UNDRFLW_COUNT    (2U)

/*! @name MTL_QUEUE_MTL_TXQX_DBG - MTL TxQx Debug register */
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TXQPAUSED_MASK (0x1U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TXQPAUSED_SHIFT (0U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TXQPAUSED(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_DBG_TXQPAUSED_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_DBG_TXQPAUSED_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TRCSTS_MASK  (0x6U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TRCSTS_SHIFT (1U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TRCSTS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_DBG_TRCSTS_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_DBG_TRCSTS_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TWCSTS_MASK  (0x8U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TWCSTS_SHIFT (3U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TWCSTS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_DBG_TWCSTS_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_DBG_TWCSTS_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TXQSTS_MASK  (0x10U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TXQSTS_SHIFT (4U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TXQSTS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_DBG_TXQSTS_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_DBG_TXQSTS_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TXSTSFSTS_MASK (0x20U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TXSTSFSTS_SHIFT (5U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_TXSTSFSTS(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_DBG_TXSTSFSTS_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_DBG_TXSTSFSTS_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_PTXQ_MASK    (0x70000U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_PTXQ_SHIFT   (16U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_PTXQ(x)      (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_DBG_PTXQ_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_DBG_PTXQ_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_STSXSTSF_MASK (0x700000U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_STSXSTSF_SHIFT (20U)
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_STSXSTSF(x)  (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_DBG_STSXSTSF_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_DBG_STSXSTSF_MASK)

/* The count of ENET_MTL_QUEUE_MTL_TXQX_DBG */
#define ENET_MTL_QUEUE_MTL_TXQX_DBG_COUNT        (2U)

/*! @name MTL_QUEUE_MTL_TXQX_ETS_CTRL - MTL TxQx ETS control register, only TxQ1 support */
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_AVALG_MASK (0x4U)
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_AVALG_SHIFT (2U)
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_AVALG(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_AVALG_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_AVALG_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_CC_MASK (0x8U)
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_CC_SHIFT (3U)
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_CC(x)   (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_CC_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_CC_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_SLC_MASK (0x70U)
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_SLC_SHIFT (4U)
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_SLC(x)  (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_SLC_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_SLC_MASK)

/* The count of ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL */
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_CTRL_COUNT   (2U)

/*! @name MTL_QUEUE_MTL_TXQX_ETS_STAT - MTL TxQx ETS Status register */
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_STAT_ABS_MASK (0xFFFFFFU)
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_STAT_ABS_SHIFT (0U)
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_STAT_ABS(x)  (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_ETS_STAT_ABS_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_ETS_STAT_ABS_MASK)

/* The count of ENET_MTL_QUEUE_MTL_TXQX_ETS_STAT */
#define ENET_MTL_QUEUE_MTL_TXQX_ETS_STAT_COUNT   (2U)

/*! @name MTL_QUEUE_MTL_TXQX_QNTM_WGHT -  */
#define ENET_MTL_QUEUE_MTL_TXQX_QNTM_WGHT_ISCQW_MASK (0x1FFFFFU)
#define ENET_MTL_QUEUE_MTL_TXQX_QNTM_WGHT_ISCQW_SHIFT (0U)
#define ENET_MTL_QUEUE_MTL_TXQX_QNTM_WGHT_ISCQW(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_QNTM_WGHT_ISCQW_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_QNTM_WGHT_ISCQW_MASK)

/* The count of ENET_MTL_QUEUE_MTL_TXQX_QNTM_WGHT */
#define ENET_MTL_QUEUE_MTL_TXQX_QNTM_WGHT_COUNT  (2U)

/*! @name MTL_QUEUE_MTL_TXQX_SNDSLP_CRDT - MTL TxQx SendSlopCredit register, only TxQ1 support */
#define ENET_MTL_QUEUE_MTL_TXQX_SNDSLP_CRDT_SSC_MASK (0x3FFFU)
#define ENET_MTL_QUEUE_MTL_TXQX_SNDSLP_CRDT_SSC_SHIFT (0U)
#define ENET_MTL_QUEUE_MTL_TXQX_SNDSLP_CRDT_SSC(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_SNDSLP_CRDT_SSC_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_SNDSLP_CRDT_SSC_MASK)

/* The count of ENET_MTL_QUEUE_MTL_TXQX_SNDSLP_CRDT */
#define ENET_MTL_QUEUE_MTL_TXQX_SNDSLP_CRDT_COUNT (2U)

/*! @name MTL_QUEUE_MTL_TXQX_HI_CRDT - MTL TxQx hiCredit register, only TxQ1 support */
#define ENET_MTL_QUEUE_MTL_TXQX_HI_CRDT_HC_MASK  (0x1FFFFFFFU)
#define ENET_MTL_QUEUE_MTL_TXQX_HI_CRDT_HC_SHIFT (0U)
#define ENET_MTL_QUEUE_MTL_TXQX_HI_CRDT_HC(x)    (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_HI_CRDT_HC_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_HI_CRDT_HC_MASK)

/* The count of ENET_MTL_QUEUE_MTL_TXQX_HI_CRDT */
#define ENET_MTL_QUEUE_MTL_TXQX_HI_CRDT_COUNT    (2U)

/*! @name MTL_QUEUE_MTL_TXQX_LO_CRDT - MTL TxQx loCredit register, only TxQ1 support */
#define ENET_MTL_QUEUE_MTL_TXQX_LO_CRDT_LC_MASK  (0x1FFFFFFFU)
#define ENET_MTL_QUEUE_MTL_TXQX_LO_CRDT_LC_SHIFT (0U)
#define ENET_MTL_QUEUE_MTL_TXQX_LO_CRDT_LC(x)    (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_LO_CRDT_LC_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_LO_CRDT_LC_MASK)

/* The count of ENET_MTL_QUEUE_MTL_TXQX_LO_CRDT */
#define ENET_MTL_QUEUE_MTL_TXQX_LO_CRDT_COUNT    (2U)

/*! @name MTL_QUEUE_MTL_TXQX_INTCTRL_STAT -  */
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_TXUNFIS_MASK (0x1U)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_TXUNFIS_SHIFT (0U)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_TXUNFIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_TXUNFIS_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_TXUNFIS_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_ABPSIS_MASK (0x2U)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_ABPSIS_SHIFT (1U)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_ABPSIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_ABPSIS_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_ABPSIS_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_TXUIE_MASK (0x100U)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_TXUIE_SHIFT (8U)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_TXUIE(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_TXUIE_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_TXUIE_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_ABPSIE_MASK (0x200U)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_ABPSIE_SHIFT (9U)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_ABPSIE(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_ABPSIE_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_ABPSIE_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_RXOVFIS_MASK (0x10000U)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_RXOVFIS_SHIFT (16U)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_RXOVFIS(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_RXOVFIS_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_RXOVFIS_MASK)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_RXOIE_MASK (0x1000000U)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_RXOIE_SHIFT (24U)
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_RXOIE(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_RXOIE_SHIFT)) & ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_RXOIE_MASK)

/* The count of ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT */
#define ENET_MTL_QUEUE_MTL_TXQX_INTCTRL_STAT_COUNT (2U)

/*! @name MTL_QUEUE_MTL_RXQX_OP_MODE - MTL RxQx Operation Mode register */
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RTC_MASK (0x3U)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RTC_SHIFT (0U)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RTC(x)   (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RTC_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RTC_MASK)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_FUP_MASK (0x8U)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_FUP_SHIFT (3U)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_FUP(x)   (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_FUP_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_FUP_MASK)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_FEP_MASK (0x10U)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_FEP_SHIFT (4U)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_FEP(x)   (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_FEP_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_FEP_MASK)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RSF_MASK (0x20U)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RSF_SHIFT (5U)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RSF(x)   (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RSF_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RSF_MASK)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_DIS_TCP_EF_MASK (0x40U)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_DIS_TCP_EF_SHIFT (6U)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_DIS_TCP_EF(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_DIS_TCP_EF_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_DIS_TCP_EF_MASK)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RQS_MASK (0x700000U)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RQS_SHIFT (20U)
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RQS(x)   (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RQS_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_RQS_MASK)

/* The count of ENET_MTL_QUEUE_MTL_RXQX_OP_MODE */
#define ENET_MTL_QUEUE_MTL_RXQX_OP_MODE_COUNT    (2U)

/*! @name MTL_QUEUE_MTL_RXQX_MISSPKT_OVRFLW_CNT - MTL RxQx Missed Packet Overflow Counter register */
#define ENET_MTL_QUEUE_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFPKTCNT_MASK (0x7FFU)
#define ENET_MTL_QUEUE_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFPKTCNT_SHIFT (0U)
#define ENET_MTL_QUEUE_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFPKTCNT(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFPKTCNT_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFPKTCNT_MASK)
#define ENET_MTL_QUEUE_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFCNTOVF_MASK (0x800U)
#define ENET_MTL_QUEUE_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFCNTOVF_SHIFT (11U)
#define ENET_MTL_QUEUE_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFCNTOVF(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFCNTOVF_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_MISSPKT_OVRFLW_CNT_OVFCNTOVF_MASK)

/* The count of ENET_MTL_QUEUE_MTL_RXQX_MISSPKT_OVRFLW_CNT */
#define ENET_MTL_QUEUE_MTL_RXQX_MISSPKT_OVRFLW_CNT_COUNT (2U)

/*! @name MTL_QUEUE_MTL_RXQX_DBG - MTL RxQx Debug register */
#define ENET_MTL_QUEUE_MTL_RXQX_DBG_RWCSTS_MASK  (0x1U)
#define ENET_MTL_QUEUE_MTL_RXQX_DBG_RWCSTS_SHIFT (0U)
#define ENET_MTL_QUEUE_MTL_RXQX_DBG_RWCSTS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_DBG_RWCSTS_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_DBG_RWCSTS_MASK)
#define ENET_MTL_QUEUE_MTL_RXQX_DBG_RRCSTS_MASK  (0x6U)
#define ENET_MTL_QUEUE_MTL_RXQX_DBG_RRCSTS_SHIFT (1U)
#define ENET_MTL_QUEUE_MTL_RXQX_DBG_RRCSTS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_DBG_RRCSTS_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_DBG_RRCSTS_MASK)
#define ENET_MTL_QUEUE_MTL_RXQX_DBG_RXQSTS_MASK  (0x30U)
#define ENET_MTL_QUEUE_MTL_RXQX_DBG_RXQSTS_SHIFT (4U)
#define ENET_MTL_QUEUE_MTL_RXQX_DBG_RXQSTS(x)    (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_DBG_RXQSTS_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_DBG_RXQSTS_MASK)
#define ENET_MTL_QUEUE_MTL_RXQX_DBG_PRXQ_MASK    (0x3FFF0000U)
#define ENET_MTL_QUEUE_MTL_RXQX_DBG_PRXQ_SHIFT   (16U)
#define ENET_MTL_QUEUE_MTL_RXQX_DBG_PRXQ(x)      (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_DBG_PRXQ_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_DBG_PRXQ_MASK)

/* The count of ENET_MTL_QUEUE_MTL_RXQX_DBG */
#define ENET_MTL_QUEUE_MTL_RXQX_DBG_COUNT        (2U)

/*! @name MTL_QUEUE_MTL_RXQX_CTRL - MTL RxQx Control register */
#define ENET_MTL_QUEUE_MTL_RXQX_CTRL_RXQ_WEGT_MASK (0x7U)
#define ENET_MTL_QUEUE_MTL_RXQX_CTRL_RXQ_WEGT_SHIFT (0U)
#define ENET_MTL_QUEUE_MTL_RXQX_CTRL_RXQ_WEGT(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_CTRL_RXQ_WEGT_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_CTRL_RXQ_WEGT_MASK)
#define ENET_MTL_QUEUE_MTL_RXQX_CTRL_RXQ_FRM_ARBIT_MASK (0x8U)
#define ENET_MTL_QUEUE_MTL_RXQX_CTRL_RXQ_FRM_ARBIT_SHIFT (3U)
#define ENET_MTL_QUEUE_MTL_RXQX_CTRL_RXQ_FRM_ARBIT(x) (((uint32_t)(((uint32_t)(x)) << ENET_MTL_QUEUE_MTL_RXQX_CTRL_RXQ_FRM_ARBIT_SHIFT)) & ENET_MTL_QUEUE_MTL_RXQX_CTRL_RXQ_FRM_ARBIT_MASK)

/* The count of ENET_MTL_QUEUE_MTL_RXQX_CTRL */
#define ENET_MTL_QUEUE_MTL_RXQX_CTRL_COUNT       (2U)

/*! @name DMA_MODE - DMA mode register */
#define ENET_DMA_MODE_SWR_MASK                   (0x1U)
#define ENET_DMA_MODE_SWR_SHIFT                  (0U)
#define ENET_DMA_MODE_SWR(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_DMA_MODE_SWR_SHIFT)) & ENET_DMA_MODE_SWR_MASK)
#define ENET_DMA_MODE_DA_MASK                    (0x2U)
#define ENET_DMA_MODE_DA_SHIFT                   (1U)
#define ENET_DMA_MODE_DA(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_DMA_MODE_DA_SHIFT)) & ENET_DMA_MODE_DA_MASK)
#define ENET_DMA_MODE_TAA_MASK                   (0x1CU)
#define ENET_DMA_MODE_TAA_SHIFT                  (2U)
#define ENET_DMA_MODE_TAA(x)                     (((uint32_t)(((uint32_t)(x)) << ENET_DMA_MODE_TAA_SHIFT)) & ENET_DMA_MODE_TAA_MASK)
#define ENET_DMA_MODE_TXPR_MASK                  (0x800U)
#define ENET_DMA_MODE_TXPR_SHIFT                 (11U)
#define ENET_DMA_MODE_TXPR(x)                    (((uint32_t)(((uint32_t)(x)) << ENET_DMA_MODE_TXPR_SHIFT)) & ENET_DMA_MODE_TXPR_MASK)
#define ENET_DMA_MODE_PR_MASK                    (0x7000U)
#define ENET_DMA_MODE_PR_SHIFT                   (12U)
#define ENET_DMA_MODE_PR(x)                      (((uint32_t)(((uint32_t)(x)) << ENET_DMA_MODE_PR_SHIFT)) & ENET_DMA_MODE_PR_MASK)

/*! @name DMA_SYSBUS_MODE - DMA System Bus mode */
#define ENET_DMA_SYSBUS_MODE_FB_MASK             (0x1U)
#define ENET_DMA_SYSBUS_MODE_FB_SHIFT            (0U)
#define ENET_DMA_SYSBUS_MODE_FB(x)               (((uint32_t)(((uint32_t)(x)) << ENET_DMA_SYSBUS_MODE_FB_SHIFT)) & ENET_DMA_SYSBUS_MODE_FB_MASK)
#define ENET_DMA_SYSBUS_MODE_AAL_MASK            (0x1000U)
#define ENET_DMA_SYSBUS_MODE_AAL_SHIFT           (12U)
#define ENET_DMA_SYSBUS_MODE_AAL(x)              (((uint32_t)(((uint32_t)(x)) << ENET_DMA_SYSBUS_MODE_AAL_SHIFT)) & ENET_DMA_SYSBUS_MODE_AAL_MASK)
#define ENET_DMA_SYSBUS_MODE_MB_MASK             (0x4000U)
#define ENET_DMA_SYSBUS_MODE_MB_SHIFT            (14U)
#define ENET_DMA_SYSBUS_MODE_MB(x)               (((uint32_t)(((uint32_t)(x)) << ENET_DMA_SYSBUS_MODE_MB_SHIFT)) & ENET_DMA_SYSBUS_MODE_MB_MASK)
#define ENET_DMA_SYSBUS_MODE_RB_MASK             (0x8000U)
#define ENET_DMA_SYSBUS_MODE_RB_SHIFT            (15U)
#define ENET_DMA_SYSBUS_MODE_RB(x)               (((uint32_t)(((uint32_t)(x)) << ENET_DMA_SYSBUS_MODE_RB_SHIFT)) & ENET_DMA_SYSBUS_MODE_RB_MASK)

/*! @name DMA_INTR_STAT - DMA Interrupt status */
#define ENET_DMA_INTR_STAT_DC0IS_MASK            (0x1U)
#define ENET_DMA_INTR_STAT_DC0IS_SHIFT           (0U)
#define ENET_DMA_INTR_STAT_DC0IS(x)              (((uint32_t)(((uint32_t)(x)) << ENET_DMA_INTR_STAT_DC0IS_SHIFT)) & ENET_DMA_INTR_STAT_DC0IS_MASK)
#define ENET_DMA_INTR_STAT_DC1IS_MASK            (0x2U)
#define ENET_DMA_INTR_STAT_DC1IS_SHIFT           (1U)
#define ENET_DMA_INTR_STAT_DC1IS(x)              (((uint32_t)(((uint32_t)(x)) << ENET_DMA_INTR_STAT_DC1IS_SHIFT)) & ENET_DMA_INTR_STAT_DC1IS_MASK)
#define ENET_DMA_INTR_STAT_MTLIS_MASK            (0x10000U)
#define ENET_DMA_INTR_STAT_MTLIS_SHIFT           (16U)
#define ENET_DMA_INTR_STAT_MTLIS(x)              (((uint32_t)(((uint32_t)(x)) << ENET_DMA_INTR_STAT_MTLIS_SHIFT)) & ENET_DMA_INTR_STAT_MTLIS_MASK)
#define ENET_DMA_INTR_STAT_MACIS_MASK            (0x20000U)
#define ENET_DMA_INTR_STAT_MACIS_SHIFT           (17U)
#define ENET_DMA_INTR_STAT_MACIS(x)              (((uint32_t)(((uint32_t)(x)) << ENET_DMA_INTR_STAT_MACIS_SHIFT)) & ENET_DMA_INTR_STAT_MACIS_MASK)

/*! @name DMA_DBG_STAT - DMA Debug Status */
#define ENET_DMA_DBG_STAT_AHSTS_MASK             (0x1U)
#define ENET_DMA_DBG_STAT_AHSTS_SHIFT            (0U)
#define ENET_DMA_DBG_STAT_AHSTS(x)               (((uint32_t)(((uint32_t)(x)) << ENET_DMA_DBG_STAT_AHSTS_SHIFT)) & ENET_DMA_DBG_STAT_AHSTS_MASK)
#define ENET_DMA_DBG_STAT_RPS0_MASK              (0xF00U)
#define ENET_DMA_DBG_STAT_RPS0_SHIFT             (8U)
#define ENET_DMA_DBG_STAT_RPS0(x)                (((uint32_t)(((uint32_t)(x)) << ENET_DMA_DBG_STAT_RPS0_SHIFT)) & ENET_DMA_DBG_STAT_RPS0_MASK)
#define ENET_DMA_DBG_STAT_TPS0_MASK              (0xF000U)
#define ENET_DMA_DBG_STAT_TPS0_SHIFT             (12U)
#define ENET_DMA_DBG_STAT_TPS0(x)                (((uint32_t)(((uint32_t)(x)) << ENET_DMA_DBG_STAT_TPS0_SHIFT)) & ENET_DMA_DBG_STAT_TPS0_MASK)
#define ENET_DMA_DBG_STAT_RPS1_MASK              (0xF0000U)
#define ENET_DMA_DBG_STAT_RPS1_SHIFT             (16U)
#define ENET_DMA_DBG_STAT_RPS1(x)                (((uint32_t)(((uint32_t)(x)) << ENET_DMA_DBG_STAT_RPS1_SHIFT)) & ENET_DMA_DBG_STAT_RPS1_MASK)
#define ENET_DMA_DBG_STAT_TPS1_MASK              (0xF00000U)
#define ENET_DMA_DBG_STAT_TPS1_SHIFT             (20U)
#define ENET_DMA_DBG_STAT_TPS1(x)                (((uint32_t)(((uint32_t)(x)) << ENET_DMA_DBG_STAT_TPS1_SHIFT)) & ENET_DMA_DBG_STAT_TPS1_MASK)

/*! @name DMA_CH_DMA_CHX_CTRL - DMA Channelx Control */
#define ENET_DMA_CH_DMA_CHX_CTRL_PBLx8_MASK      (0x10000U)
#define ENET_DMA_CH_DMA_CHX_CTRL_PBLx8_SHIFT     (16U)
#define ENET_DMA_CH_DMA_CHX_CTRL_PBLx8(x)        (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_CTRL_PBLx8_SHIFT)) & ENET_DMA_CH_DMA_CHX_CTRL_PBLx8_MASK)
#define ENET_DMA_CH_DMA_CHX_CTRL_DSL_MASK        (0x1C0000U)
#define ENET_DMA_CH_DMA_CHX_CTRL_DSL_SHIFT       (18U)
#define ENET_DMA_CH_DMA_CHX_CTRL_DSL(x)          (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_CTRL_DSL_SHIFT)) & ENET_DMA_CH_DMA_CHX_CTRL_DSL_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_CTRL */
#define ENET_DMA_CH_DMA_CHX_CTRL_COUNT           (2U)

/*! @name DMA_CH_DMA_CHX_TX_CTRL - DMA Channelx Transmit Control */
#define ENET_DMA_CH_DMA_CHX_TX_CTRL_ST_MASK      (0x1U)
#define ENET_DMA_CH_DMA_CHX_TX_CTRL_ST_SHIFT     (0U)
#define ENET_DMA_CH_DMA_CHX_TX_CTRL_ST(x)        (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_TX_CTRL_ST_SHIFT)) & ENET_DMA_CH_DMA_CHX_TX_CTRL_ST_MASK)
#define ENET_DMA_CH_DMA_CHX_TX_CTRL_TCW_MASK     (0xEU)
#define ENET_DMA_CH_DMA_CHX_TX_CTRL_TCW_SHIFT    (1U)
#define ENET_DMA_CH_DMA_CHX_TX_CTRL_TCW(x)       (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_TX_CTRL_TCW_SHIFT)) & ENET_DMA_CH_DMA_CHX_TX_CTRL_TCW_MASK)
#define ENET_DMA_CH_DMA_CHX_TX_CTRL_OSF_MASK     (0x10U)
#define ENET_DMA_CH_DMA_CHX_TX_CTRL_OSF_SHIFT    (4U)
#define ENET_DMA_CH_DMA_CHX_TX_CTRL_OSF(x)       (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_TX_CTRL_OSF_SHIFT)) & ENET_DMA_CH_DMA_CHX_TX_CTRL_OSF_MASK)
#define ENET_DMA_CH_DMA_CHX_TX_CTRL_TxPBL_MASK   (0x3F0000U)
#define ENET_DMA_CH_DMA_CHX_TX_CTRL_TxPBL_SHIFT  (16U)
#define ENET_DMA_CH_DMA_CHX_TX_CTRL_TxPBL(x)     (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_TX_CTRL_TxPBL_SHIFT)) & ENET_DMA_CH_DMA_CHX_TX_CTRL_TxPBL_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_TX_CTRL */
#define ENET_DMA_CH_DMA_CHX_TX_CTRL_COUNT        (2U)

/*! @name DMA_CH_DMA_CHX_RX_CTRL - DMA Channelx Receive Control */
#define ENET_DMA_CH_DMA_CHX_RX_CTRL_SR_MASK      (0x1U)
#define ENET_DMA_CH_DMA_CHX_RX_CTRL_SR_SHIFT     (0U)
#define ENET_DMA_CH_DMA_CHX_RX_CTRL_SR(x)        (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_RX_CTRL_SR_SHIFT)) & ENET_DMA_CH_DMA_CHX_RX_CTRL_SR_MASK)
#define ENET_DMA_CH_DMA_CHX_RX_CTRL_RBSZ_MASK    (0x7FF8U)
#define ENET_DMA_CH_DMA_CHX_RX_CTRL_RBSZ_SHIFT   (3U)
#define ENET_DMA_CH_DMA_CHX_RX_CTRL_RBSZ(x)      (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_RX_CTRL_RBSZ_SHIFT)) & ENET_DMA_CH_DMA_CHX_RX_CTRL_RBSZ_MASK)
#define ENET_DMA_CH_DMA_CHX_RX_CTRL_RxPBL_MASK   (0x3F0000U)
#define ENET_DMA_CH_DMA_CHX_RX_CTRL_RxPBL_SHIFT  (16U)
#define ENET_DMA_CH_DMA_CHX_RX_CTRL_RxPBL(x)     (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_RX_CTRL_RxPBL_SHIFT)) & ENET_DMA_CH_DMA_CHX_RX_CTRL_RxPBL_MASK)
#define ENET_DMA_CH_DMA_CHX_RX_CTRL_RPF_MASK     (0x80000000U)
#define ENET_DMA_CH_DMA_CHX_RX_CTRL_RPF_SHIFT    (31U)
#define ENET_DMA_CH_DMA_CHX_RX_CTRL_RPF(x)       (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_RX_CTRL_RPF_SHIFT)) & ENET_DMA_CH_DMA_CHX_RX_CTRL_RPF_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_RX_CTRL */
#define ENET_DMA_CH_DMA_CHX_RX_CTRL_COUNT        (2U)

/*! @name DMA_CH_DMA_CHX_TXDESC_LIST_ADDR -  */
#define ENET_DMA_CH_DMA_CHX_TXDESC_LIST_ADDR_STL_MASK (0xFFFFFFFCU)
#define ENET_DMA_CH_DMA_CHX_TXDESC_LIST_ADDR_STL_SHIFT (2U)
#define ENET_DMA_CH_DMA_CHX_TXDESC_LIST_ADDR_STL(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_TXDESC_LIST_ADDR_STL_SHIFT)) & ENET_DMA_CH_DMA_CHX_TXDESC_LIST_ADDR_STL_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_TXDESC_LIST_ADDR */
#define ENET_DMA_CH_DMA_CHX_TXDESC_LIST_ADDR_COUNT (2U)

/*! @name DMA_CH_DMA_CHX_RXDESC_LIST_ADDR -  */
#define ENET_DMA_CH_DMA_CHX_RXDESC_LIST_ADDR_SRL_MASK (0xFFFFFFFCU)
#define ENET_DMA_CH_DMA_CHX_RXDESC_LIST_ADDR_SRL_SHIFT (2U)
#define ENET_DMA_CH_DMA_CHX_RXDESC_LIST_ADDR_SRL(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_RXDESC_LIST_ADDR_SRL_SHIFT)) & ENET_DMA_CH_DMA_CHX_RXDESC_LIST_ADDR_SRL_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_RXDESC_LIST_ADDR */
#define ENET_DMA_CH_DMA_CHX_RXDESC_LIST_ADDR_COUNT (2U)

/*! @name DMA_CH_DMA_CHX_TXDESC_TAIL_PTR -  */
#define ENET_DMA_CH_DMA_CHX_TXDESC_TAIL_PTR_TDTP_MASK (0xFFFFFFFCU)
#define ENET_DMA_CH_DMA_CHX_TXDESC_TAIL_PTR_TDTP_SHIFT (2U)
#define ENET_DMA_CH_DMA_CHX_TXDESC_TAIL_PTR_TDTP(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_TXDESC_TAIL_PTR_TDTP_SHIFT)) & ENET_DMA_CH_DMA_CHX_TXDESC_TAIL_PTR_TDTP_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_TXDESC_TAIL_PTR */
#define ENET_DMA_CH_DMA_CHX_TXDESC_TAIL_PTR_COUNT (2U)

/*! @name DMA_CH_DMA_CHX_RXDESC_TAIL_PTR -  */
#define ENET_DMA_CH_DMA_CHX_RXDESC_TAIL_PTR_RDTP_MASK (0xFFFFFFFCU)
#define ENET_DMA_CH_DMA_CHX_RXDESC_TAIL_PTR_RDTP_SHIFT (2U)
#define ENET_DMA_CH_DMA_CHX_RXDESC_TAIL_PTR_RDTP(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_RXDESC_TAIL_PTR_RDTP_SHIFT)) & ENET_DMA_CH_DMA_CHX_RXDESC_TAIL_PTR_RDTP_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_RXDESC_TAIL_PTR */
#define ENET_DMA_CH_DMA_CHX_RXDESC_TAIL_PTR_COUNT (2U)

/*! @name DMA_CH_DMA_CHX_TXDESC_RING_LENGTH -  */
#define ENET_DMA_CH_DMA_CHX_TXDESC_RING_LENGTH_TDRL_MASK (0x3FFU)
#define ENET_DMA_CH_DMA_CHX_TXDESC_RING_LENGTH_TDRL_SHIFT (0U)
#define ENET_DMA_CH_DMA_CHX_TXDESC_RING_LENGTH_TDRL(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_TXDESC_RING_LENGTH_TDRL_SHIFT)) & ENET_DMA_CH_DMA_CHX_TXDESC_RING_LENGTH_TDRL_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_TXDESC_RING_LENGTH */
#define ENET_DMA_CH_DMA_CHX_TXDESC_RING_LENGTH_COUNT (2U)

/*! @name DMA_CH_DMA_CHX_RXDESC_RING_LENGTH - Channelx Rx descriptor Ring Length */
#define ENET_DMA_CH_DMA_CHX_RXDESC_RING_LENGTH_RDRL_MASK (0x3FFU)
#define ENET_DMA_CH_DMA_CHX_RXDESC_RING_LENGTH_RDRL_SHIFT (0U)
#define ENET_DMA_CH_DMA_CHX_RXDESC_RING_LENGTH_RDRL(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_RXDESC_RING_LENGTH_RDRL_SHIFT)) & ENET_DMA_CH_DMA_CHX_RXDESC_RING_LENGTH_RDRL_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_RXDESC_RING_LENGTH */
#define ENET_DMA_CH_DMA_CHX_RXDESC_RING_LENGTH_COUNT (2U)

/*! @name DMA_CH_DMA_CHX_INT_EN - Channelx Interrupt Enable */
#define ENET_DMA_CH_DMA_CHX_INT_EN_TIE_MASK      (0x1U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_TIE_SHIFT     (0U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_TIE(x)        (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_INT_EN_TIE_SHIFT)) & ENET_DMA_CH_DMA_CHX_INT_EN_TIE_MASK)
#define ENET_DMA_CH_DMA_CHX_INT_EN_TSE_MASK      (0x2U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_TSE_SHIFT     (1U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_TSE(x)        (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_INT_EN_TSE_SHIFT)) & ENET_DMA_CH_DMA_CHX_INT_EN_TSE_MASK)
#define ENET_DMA_CH_DMA_CHX_INT_EN_TBUE_MASK     (0x4U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_TBUE_SHIFT    (2U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_TBUE(x)       (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_INT_EN_TBUE_SHIFT)) & ENET_DMA_CH_DMA_CHX_INT_EN_TBUE_MASK)
#define ENET_DMA_CH_DMA_CHX_INT_EN_RIE_MASK      (0x40U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_RIE_SHIFT     (6U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_RIE(x)        (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_INT_EN_RIE_SHIFT)) & ENET_DMA_CH_DMA_CHX_INT_EN_RIE_MASK)
#define ENET_DMA_CH_DMA_CHX_INT_EN_RBUE_MASK     (0x80U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_RBUE_SHIFT    (7U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_RBUE(x)       (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_INT_EN_RBUE_SHIFT)) & ENET_DMA_CH_DMA_CHX_INT_EN_RBUE_MASK)
#define ENET_DMA_CH_DMA_CHX_INT_EN_RSE_MASK      (0x100U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_RSE_SHIFT     (8U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_RSE(x)        (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_INT_EN_RSE_SHIFT)) & ENET_DMA_CH_DMA_CHX_INT_EN_RSE_MASK)
#define ENET_DMA_CH_DMA_CHX_INT_EN_RWTE_MASK     (0x200U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_RWTE_SHIFT    (9U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_RWTE(x)       (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_INT_EN_RWTE_SHIFT)) & ENET_DMA_CH_DMA_CHX_INT_EN_RWTE_MASK)
#define ENET_DMA_CH_DMA_CHX_INT_EN_ETIE_MASK     (0x400U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_ETIE_SHIFT    (10U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_ETIE(x)       (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_INT_EN_ETIE_SHIFT)) & ENET_DMA_CH_DMA_CHX_INT_EN_ETIE_MASK)
#define ENET_DMA_CH_DMA_CHX_INT_EN_ERIE_MASK     (0x800U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_ERIE_SHIFT    (11U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_ERIE(x)       (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_INT_EN_ERIE_SHIFT)) & ENET_DMA_CH_DMA_CHX_INT_EN_ERIE_MASK)
#define ENET_DMA_CH_DMA_CHX_INT_EN_FBEE_MASK     (0x1000U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_FBEE_SHIFT    (12U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_FBEE(x)       (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_INT_EN_FBEE_SHIFT)) & ENET_DMA_CH_DMA_CHX_INT_EN_FBEE_MASK)
#define ENET_DMA_CH_DMA_CHX_INT_EN_AIE_MASK      (0x4000U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_AIE_SHIFT     (14U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_AIE(x)        (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_INT_EN_AIE_SHIFT)) & ENET_DMA_CH_DMA_CHX_INT_EN_AIE_MASK)
#define ENET_DMA_CH_DMA_CHX_INT_EN_NIE_MASK      (0x8000U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_NIE_SHIFT     (15U)
#define ENET_DMA_CH_DMA_CHX_INT_EN_NIE(x)        (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_INT_EN_NIE_SHIFT)) & ENET_DMA_CH_DMA_CHX_INT_EN_NIE_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_INT_EN */
#define ENET_DMA_CH_DMA_CHX_INT_EN_COUNT         (2U)

/*! @name DMA_CH_DMA_CHX_RX_INT_WDTIMER - Receive Interrupt Watchdog Timer */
#define ENET_DMA_CH_DMA_CHX_RX_INT_WDTIMER_RIWT_MASK (0xFFU)
#define ENET_DMA_CH_DMA_CHX_RX_INT_WDTIMER_RIWT_SHIFT (0U)
#define ENET_DMA_CH_DMA_CHX_RX_INT_WDTIMER_RIWT(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_RX_INT_WDTIMER_RIWT_SHIFT)) & ENET_DMA_CH_DMA_CHX_RX_INT_WDTIMER_RIWT_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_RX_INT_WDTIMER */
#define ENET_DMA_CH_DMA_CHX_RX_INT_WDTIMER_COUNT (2U)

/*! @name DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT - Slot Function Control and Status */
#define ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_ESC_MASK (0x1U)
#define ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_ESC_SHIFT (0U)
#define ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_ESC(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_ESC_SHIFT)) & ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_ESC_MASK)
#define ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_ASC_MASK (0x2U)
#define ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_ASC_SHIFT (1U)
#define ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_ASC(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_ASC_SHIFT)) & ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_ASC_MASK)
#define ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_RSN_MASK (0xF0000U)
#define ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_RSN_SHIFT (16U)
#define ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_RSN(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_RSN_SHIFT)) & ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_RSN_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT */
#define ENET_DMA_CH_DMA_CHX_SLOT_FUNC_CTRL_STAT_COUNT (2U)

/*! @name DMA_CH_DMA_CHX_CUR_HST_TXDESC - Channelx Current Host Transmit descriptor */
#define ENET_DMA_CH_DMA_CHX_CUR_HST_TXDESC_HTD_MASK (0xFFFFFFFFU)
#define ENET_DMA_CH_DMA_CHX_CUR_HST_TXDESC_HTD_SHIFT (0U)
#define ENET_DMA_CH_DMA_CHX_CUR_HST_TXDESC_HTD(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_CUR_HST_TXDESC_HTD_SHIFT)) & ENET_DMA_CH_DMA_CHX_CUR_HST_TXDESC_HTD_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_CUR_HST_TXDESC */
#define ENET_DMA_CH_DMA_CHX_CUR_HST_TXDESC_COUNT (2U)

/*! @name DMA_CH_DMA_CHX_CUR_HST_RXDESC -  */
#define ENET_DMA_CH_DMA_CHX_CUR_HST_RXDESC_HRD_MASK (0xFFFFFFFFU)
#define ENET_DMA_CH_DMA_CHX_CUR_HST_RXDESC_HRD_SHIFT (0U)
#define ENET_DMA_CH_DMA_CHX_CUR_HST_RXDESC_HRD(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_CUR_HST_RXDESC_HRD_SHIFT)) & ENET_DMA_CH_DMA_CHX_CUR_HST_RXDESC_HRD_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_CUR_HST_RXDESC */
#define ENET_DMA_CH_DMA_CHX_CUR_HST_RXDESC_COUNT (2U)

/*! @name DMA_CH_DMA_CHX_CUR_HST_TXBUF -  */
#define ENET_DMA_CH_DMA_CHX_CUR_HST_TXBUF_HTB_MASK (0xFFFFFFFFU)
#define ENET_DMA_CH_DMA_CHX_CUR_HST_TXBUF_HTB_SHIFT (0U)
#define ENET_DMA_CH_DMA_CHX_CUR_HST_TXBUF_HTB(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_CUR_HST_TXBUF_HTB_SHIFT)) & ENET_DMA_CH_DMA_CHX_CUR_HST_TXBUF_HTB_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_CUR_HST_TXBUF */
#define ENET_DMA_CH_DMA_CHX_CUR_HST_TXBUF_COUNT  (2U)

/*! @name DMA_CH_DMA_CHX_CUR_HST_RXBUF - Channelx Current Application Receive Buffer Address */
#define ENET_DMA_CH_DMA_CHX_CUR_HST_RXBUF_HRB_MASK (0xFFFFFFFFU)
#define ENET_DMA_CH_DMA_CHX_CUR_HST_RXBUF_HRB_SHIFT (0U)
#define ENET_DMA_CH_DMA_CHX_CUR_HST_RXBUF_HRB(x) (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_CUR_HST_RXBUF_HRB_SHIFT)) & ENET_DMA_CH_DMA_CHX_CUR_HST_RXBUF_HRB_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_CUR_HST_RXBUF */
#define ENET_DMA_CH_DMA_CHX_CUR_HST_RXBUF_COUNT  (2U)

/*! @name DMA_CH_DMA_CHX_STAT - Channelx DMA status register */
#define ENET_DMA_CH_DMA_CHX_STAT_TI_MASK         (0x1U)
#define ENET_DMA_CH_DMA_CHX_STAT_TI_SHIFT        (0U)
#define ENET_DMA_CH_DMA_CHX_STAT_TI(x)           (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_STAT_TI_SHIFT)) & ENET_DMA_CH_DMA_CHX_STAT_TI_MASK)
#define ENET_DMA_CH_DMA_CHX_STAT_TPS_MASK        (0x2U)
#define ENET_DMA_CH_DMA_CHX_STAT_TPS_SHIFT       (1U)
#define ENET_DMA_CH_DMA_CHX_STAT_TPS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_STAT_TPS_SHIFT)) & ENET_DMA_CH_DMA_CHX_STAT_TPS_MASK)
#define ENET_DMA_CH_DMA_CHX_STAT_TBU_MASK        (0x4U)
#define ENET_DMA_CH_DMA_CHX_STAT_TBU_SHIFT       (2U)
#define ENET_DMA_CH_DMA_CHX_STAT_TBU(x)          (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_STAT_TBU_SHIFT)) & ENET_DMA_CH_DMA_CHX_STAT_TBU_MASK)
#define ENET_DMA_CH_DMA_CHX_STAT_RI_MASK         (0x40U)
#define ENET_DMA_CH_DMA_CHX_STAT_RI_SHIFT        (6U)
#define ENET_DMA_CH_DMA_CHX_STAT_RI(x)           (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_STAT_RI_SHIFT)) & ENET_DMA_CH_DMA_CHX_STAT_RI_MASK)
#define ENET_DMA_CH_DMA_CHX_STAT_RBU_MASK        (0x80U)
#define ENET_DMA_CH_DMA_CHX_STAT_RBU_SHIFT       (7U)
#define ENET_DMA_CH_DMA_CHX_STAT_RBU(x)          (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_STAT_RBU_SHIFT)) & ENET_DMA_CH_DMA_CHX_STAT_RBU_MASK)
#define ENET_DMA_CH_DMA_CHX_STAT_RPS_MASK        (0x100U)
#define ENET_DMA_CH_DMA_CHX_STAT_RPS_SHIFT       (8U)
#define ENET_DMA_CH_DMA_CHX_STAT_RPS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_STAT_RPS_SHIFT)) & ENET_DMA_CH_DMA_CHX_STAT_RPS_MASK)
#define ENET_DMA_CH_DMA_CHX_STAT_RWT_MASK        (0x200U)
#define ENET_DMA_CH_DMA_CHX_STAT_RWT_SHIFT       (9U)
#define ENET_DMA_CH_DMA_CHX_STAT_RWT(x)          (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_STAT_RWT_SHIFT)) & ENET_DMA_CH_DMA_CHX_STAT_RWT_MASK)
#define ENET_DMA_CH_DMA_CHX_STAT_ETI_MASK        (0x400U)
#define ENET_DMA_CH_DMA_CHX_STAT_ETI_SHIFT       (10U)
#define ENET_DMA_CH_DMA_CHX_STAT_ETI(x)          (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_STAT_ETI_SHIFT)) & ENET_DMA_CH_DMA_CHX_STAT_ETI_MASK)
#define ENET_DMA_CH_DMA_CHX_STAT_ERI_MASK        (0x800U)
#define ENET_DMA_CH_DMA_CHX_STAT_ERI_SHIFT       (11U)
#define ENET_DMA_CH_DMA_CHX_STAT_ERI(x)          (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_STAT_ERI_SHIFT)) & ENET_DMA_CH_DMA_CHX_STAT_ERI_MASK)
#define ENET_DMA_CH_DMA_CHX_STAT_FBE_MASK        (0x1000U)
#define ENET_DMA_CH_DMA_CHX_STAT_FBE_SHIFT       (12U)
#define ENET_DMA_CH_DMA_CHX_STAT_FBE(x)          (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_STAT_FBE_SHIFT)) & ENET_DMA_CH_DMA_CHX_STAT_FBE_MASK)
#define ENET_DMA_CH_DMA_CHX_STAT_AIS_MASK        (0x4000U)
#define ENET_DMA_CH_DMA_CHX_STAT_AIS_SHIFT       (14U)
#define ENET_DMA_CH_DMA_CHX_STAT_AIS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_STAT_AIS_SHIFT)) & ENET_DMA_CH_DMA_CHX_STAT_AIS_MASK)
#define ENET_DMA_CH_DMA_CHX_STAT_NIS_MASK        (0x8000U)
#define ENET_DMA_CH_DMA_CHX_STAT_NIS_SHIFT       (15U)
#define ENET_DMA_CH_DMA_CHX_STAT_NIS(x)          (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_STAT_NIS_SHIFT)) & ENET_DMA_CH_DMA_CHX_STAT_NIS_MASK)
#define ENET_DMA_CH_DMA_CHX_STAT_EB_MASK         (0x70000U)
#define ENET_DMA_CH_DMA_CHX_STAT_EB_SHIFT        (16U)
#define ENET_DMA_CH_DMA_CHX_STAT_EB(x)           (((uint32_t)(((uint32_t)(x)) << ENET_DMA_CH_DMA_CHX_STAT_EB_SHIFT)) & ENET_DMA_CH_DMA_CHX_STAT_EB_MASK)

/* The count of ENET_DMA_CH_DMA_CHX_STAT */
#define ENET_DMA_CH_DMA_CHX_STAT_COUNT           (2U)


/*!
 * @}
 */ /* end of group ENET_Register_Masks */


/* ENET - Peripheral instance base addresses */
/** Peripheral ENET base address */
#define ENET_BASE                                (0x40092000u)
/** Peripheral ENET base pointer */
#define ENET                                     ((ENET_Type *)ENET_BASE)
/** Array initializer of ENET peripheral base addresses */
#define ENET_BASE_ADDRS                          { ENET_BASE }
/** Array initializer of ENET peripheral base pointers */
#define ENET_BASE_PTRS                           { ENET }
/** Interrupt vectors for the ENET peripheral type */
#define ENET_IRQS                                { ETHERNET_IRQn }
#define ENET_PMT_IRQS                            { ETHERNET_PMT_IRQn }
#define ENET_MACLP_IRQS                          { ETHERNET_MACLP_IRQn }

/*!
 * @}
 */ /* end of group ENET_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- FLEXCOMM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLEXCOMM_Peripheral_Access_Layer FLEXCOMM Peripheral Access Layer
 * @{
 */

/** FLEXCOMM - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[4088];
  __IO uint32_t PSELID;                            /**< Peripheral Select and Flexcomm ID register., offset: 0xFF8 */
  __IO uint32_t PID;                               /**< Peripheral identification register., offset: 0xFFC */
} FLEXCOMM_Type;

/* ----------------------------------------------------------------------------
   -- FLEXCOMM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLEXCOMM_Register_Masks FLEXCOMM Register Masks
 * @{
 */

/*! @name PSELID - Peripheral Select and Flexcomm ID register. */
#define FLEXCOMM_PSELID_PERSEL_MASK              (0x7U)
#define FLEXCOMM_PSELID_PERSEL_SHIFT             (0U)
#define FLEXCOMM_PSELID_PERSEL(x)                (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_PERSEL_SHIFT)) & FLEXCOMM_PSELID_PERSEL_MASK)
#define FLEXCOMM_PSELID_LOCK_MASK                (0x8U)
#define FLEXCOMM_PSELID_LOCK_SHIFT               (3U)
#define FLEXCOMM_PSELID_LOCK(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_LOCK_SHIFT)) & FLEXCOMM_PSELID_LOCK_MASK)
#define FLEXCOMM_PSELID_USARTPRESENT_MASK        (0x10U)
#define FLEXCOMM_PSELID_USARTPRESENT_SHIFT       (4U)
#define FLEXCOMM_PSELID_USARTPRESENT(x)          (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_USARTPRESENT_SHIFT)) & FLEXCOMM_PSELID_USARTPRESENT_MASK)
#define FLEXCOMM_PSELID_SPIPRESENT_MASK          (0x20U)
#define FLEXCOMM_PSELID_SPIPRESENT_SHIFT         (5U)
#define FLEXCOMM_PSELID_SPIPRESENT(x)            (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_SPIPRESENT_SHIFT)) & FLEXCOMM_PSELID_SPIPRESENT_MASK)
#define FLEXCOMM_PSELID_I2CPRESENT_MASK          (0x40U)
#define FLEXCOMM_PSELID_I2CPRESENT_SHIFT         (6U)
#define FLEXCOMM_PSELID_I2CPRESENT(x)            (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_I2CPRESENT_SHIFT)) & FLEXCOMM_PSELID_I2CPRESENT_MASK)
#define FLEXCOMM_PSELID_I2SPRESENT_MASK          (0x80U)
#define FLEXCOMM_PSELID_I2SPRESENT_SHIFT         (7U)
#define FLEXCOMM_PSELID_I2SPRESENT(x)            (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_I2SPRESENT_SHIFT)) & FLEXCOMM_PSELID_I2SPRESENT_MASK)
#define FLEXCOMM_PSELID_ID_MASK                  (0xFFFFF000U)
#define FLEXCOMM_PSELID_ID_SHIFT                 (12U)
#define FLEXCOMM_PSELID_ID(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_ID_SHIFT)) & FLEXCOMM_PSELID_ID_MASK)

/*! @name PID - Peripheral identification register. */
#define FLEXCOMM_PID_Minor_Rev_MASK              (0xF00U)
#define FLEXCOMM_PID_Minor_Rev_SHIFT             (8U)
#define FLEXCOMM_PID_Minor_Rev(x)                (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PID_Minor_Rev_SHIFT)) & FLEXCOMM_PID_Minor_Rev_MASK)
#define FLEXCOMM_PID_Major_Rev_MASK              (0xF000U)
#define FLEXCOMM_PID_Major_Rev_SHIFT             (12U)
#define FLEXCOMM_PID_Major_Rev(x)                (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PID_Major_Rev_SHIFT)) & FLEXCOMM_PID_Major_Rev_MASK)
#define FLEXCOMM_PID_ID_MASK                     (0xFFFF0000U)
#define FLEXCOMM_PID_ID_SHIFT                    (16U)
#define FLEXCOMM_PID_ID(x)                       (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PID_ID_SHIFT)) & FLEXCOMM_PID_ID_MASK)


/*!
 * @}
 */ /* end of group FLEXCOMM_Register_Masks */


/* FLEXCOMM - Peripheral instance base addresses */
/** Peripheral FLEXCOMM0 base address */
#define FLEXCOMM0_BASE                           (0x40086000u)
/** Peripheral FLEXCOMM0 base pointer */
#define FLEXCOMM0                                ((FLEXCOMM_Type *)FLEXCOMM0_BASE)
/** Peripheral FLEXCOMM1 base address */
#define FLEXCOMM1_BASE                           (0x40087000u)
/** Peripheral FLEXCOMM1 base pointer */
#define FLEXCOMM1                                ((FLEXCOMM_Type *)FLEXCOMM1_BASE)
/** Peripheral FLEXCOMM2 base address */
#define FLEXCOMM2_BASE                           (0x40088000u)
/** Peripheral FLEXCOMM2 base pointer */
#define FLEXCOMM2                                ((FLEXCOMM_Type *)FLEXCOMM2_BASE)
/** Peripheral FLEXCOMM3 base address */
#define FLEXCOMM3_BASE                           (0x40089000u)
/** Peripheral FLEXCOMM3 base pointer */
#define FLEXCOMM3                                ((FLEXCOMM_Type *)FLEXCOMM3_BASE)
/** Peripheral FLEXCOMM4 base address */
#define FLEXCOMM4_BASE                           (0x4008A000u)
/** Peripheral FLEXCOMM4 base pointer */
#define FLEXCOMM4                                ((FLEXCOMM_Type *)FLEXCOMM4_BASE)
/** Peripheral FLEXCOMM5 base address */
#define FLEXCOMM5_BASE                           (0x40096000u)
/** Peripheral FLEXCOMM5 base pointer */
#define FLEXCOMM5                                ((FLEXCOMM_Type *)FLEXCOMM5_BASE)
/** Peripheral FLEXCOMM6 base address */
#define FLEXCOMM6_BASE                           (0x40097000u)
/** Peripheral FLEXCOMM6 base pointer */
#define FLEXCOMM6                                ((FLEXCOMM_Type *)FLEXCOMM6_BASE)
/** Peripheral FLEXCOMM7 base address */
#define FLEXCOMM7_BASE                           (0x40098000u)
/** Peripheral FLEXCOMM7 base pointer */
#define FLEXCOMM7                                ((FLEXCOMM_Type *)FLEXCOMM7_BASE)
/** Peripheral FLEXCOMM8 base address */
#define FLEXCOMM8_BASE                           (0x40099000u)
/** Peripheral FLEXCOMM8 base pointer */
#define FLEXCOMM8                                ((FLEXCOMM_Type *)FLEXCOMM8_BASE)
/** Peripheral FLEXCOMM9 base address */
#define FLEXCOMM9_BASE                           (0x4009A000u)
/** Peripheral FLEXCOMM9 base pointer */
#define FLEXCOMM9                                ((FLEXCOMM_Type *)FLEXCOMM9_BASE)
/** Array initializer of FLEXCOMM peripheral base addresses */
#define FLEXCOMM_BASE_ADDRS                      { FLEXCOMM0_BASE, FLEXCOMM1_BASE, FLEXCOMM2_BASE, FLEXCOMM3_BASE, FLEXCOMM4_BASE, FLEXCOMM5_BASE, FLEXCOMM6_BASE, FLEXCOMM7_BASE, FLEXCOMM8_BASE, FLEXCOMM9_BASE }
/** Array initializer of FLEXCOMM peripheral base pointers */
#define FLEXCOMM_BASE_PTRS                       { FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7, FLEXCOMM8, FLEXCOMM9 }
/** Interrupt vectors for the FLEXCOMM peripheral type */
#define FLEXCOMM_IRQS                            { FLEXCOMM0_IRQn, FLEXCOMM1_IRQn, FLEXCOMM2_IRQn, FLEXCOMM3_IRQn, FLEXCOMM4_IRQn, FLEXCOMM5_IRQn, FLEXCOMM6_IRQn, FLEXCOMM7_IRQn, FLEXCOMM8_IRQn, FLEXCOMM9_IRQn }

/*!
 * @}
 */ /* end of group FLEXCOMM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- FMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FMC_Peripheral_Access_Layer FMC Peripheral Access Layer
 * @{
 */

/** FMC - Register Layout Typedef */
typedef struct {
  __IO uint32_t FCTR;                              /**< Control register, offset: 0x0 */
       uint8_t RESERVED_0[12];
  __IO uint32_t FBWST;                             /**< Wait state register, offset: 0x10 */
       uint8_t RESERVED_1[12];
  __IO uint32_t FMSSTART;                          /**< Signature start address register, offset: 0x20 */
  __IO uint32_t FMSSTOP;                           /**< Signature stop-address register, offset: 0x24 */
       uint8_t RESERVED_2[4];
  __I  uint32_t FMSW[4];                           /**< Words of 128-bit signature word, array offset: 0x2C, array step: 0x4 */
       uint8_t RESERVED_3[4004];
  __I  uint32_t FMSTAT;                            /**< Signature generation status register, offset: 0xFE0 */
       uint8_t RESERVED_4[4];
  __O  uint32_t FMSTATCLR;                         /**< Signature generation status clear register, offset: 0xFE8 */
} FMC_Type;

/* ----------------------------------------------------------------------------
   -- FMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FMC_Register_Masks FMC Register Masks
 * @{
 */

/*! @name FCTR - Control register */
#define FMC_FCTR_FS_RD0_MASK                     (0x8U)
#define FMC_FCTR_FS_RD0_SHIFT                    (3U)
#define FMC_FCTR_FS_RD0(x)                       (((uint32_t)(((uint32_t)(x)) << FMC_FCTR_FS_RD0_SHIFT)) & FMC_FCTR_FS_RD0_MASK)
#define FMC_FCTR_FS_RD1_MASK                     (0x10U)
#define FMC_FCTR_FS_RD1_SHIFT                    (4U)
#define FMC_FCTR_FS_RD1(x)                       (((uint32_t)(((uint32_t)(x)) << FMC_FCTR_FS_RD1_SHIFT)) & FMC_FCTR_FS_RD1_MASK)

/*! @name FBWST - Wait state register */
#define FMC_FBWST_WAITSTATES_MASK                (0xFFU)
#define FMC_FBWST_WAITSTATES_SHIFT               (0U)
#define FMC_FBWST_WAITSTATES(x)                  (((uint32_t)(((uint32_t)(x)) << FMC_FBWST_WAITSTATES_SHIFT)) & FMC_FBWST_WAITSTATES_MASK)

/*! @name FMSSTART - Signature start address register */
#define FMC_FMSSTART_START_MASK                  (0x1FFFFU)
#define FMC_FMSSTART_START_SHIFT                 (0U)
#define FMC_FMSSTART_START(x)                    (((uint32_t)(((uint32_t)(x)) << FMC_FMSSTART_START_SHIFT)) & FMC_FMSSTART_START_MASK)

/*! @name FMSSTOP - Signature stop-address register */
#define FMC_FMSSTOP_STOP_MASK                    (0x1FFFFU)
#define FMC_FMSSTOP_STOP_SHIFT                   (0U)
#define FMC_FMSSTOP_STOP(x)                      (((uint32_t)(((uint32_t)(x)) << FMC_FMSSTOP_STOP_SHIFT)) & FMC_FMSSTOP_STOP_MASK)
#define FMC_FMSSTOP_SIG_START_MASK               (0x20000U)
#define FMC_FMSSTOP_SIG_START_SHIFT              (17U)
#define FMC_FMSSTOP_SIG_START(x)                 (((uint32_t)(((uint32_t)(x)) << FMC_FMSSTOP_SIG_START_SHIFT)) & FMC_FMSSTOP_SIG_START_MASK)

/*! @name FMSW - Words of 128-bit signature word */
#define FMC_FMSW_SW_MASK                         (0xFFFFFFFFU)
#define FMC_FMSW_SW_SHIFT                        (0U)
#define FMC_FMSW_SW(x)                           (((uint32_t)(((uint32_t)(x)) << FMC_FMSW_SW_SHIFT)) & FMC_FMSW_SW_MASK)

/* The count of FMC_FMSW */
#define FMC_FMSW_COUNT                           (4U)

/*! @name FMSTAT - Signature generation status register */
#define FMC_FMSTAT_SIG_DONE_MASK                 (0x4U)
#define FMC_FMSTAT_SIG_DONE_SHIFT                (2U)
#define FMC_FMSTAT_SIG_DONE(x)                   (((uint32_t)(((uint32_t)(x)) << FMC_FMSTAT_SIG_DONE_SHIFT)) & FMC_FMSTAT_SIG_DONE_MASK)

/*! @name FMSTATCLR - Signature generation status clear register */
#define FMC_FMSTATCLR_SIG_DONE_CLR_MASK          (0x4U)
#define FMC_FMSTATCLR_SIG_DONE_CLR_SHIFT         (2U)
#define FMC_FMSTATCLR_SIG_DONE_CLR(x)            (((uint32_t)(((uint32_t)(x)) << FMC_FMSTATCLR_SIG_DONE_CLR_SHIFT)) & FMC_FMSTATCLR_SIG_DONE_CLR_MASK)


/*!
 * @}
 */ /* end of group FMC_Register_Masks */


/* FMC - Peripheral instance base addresses */
/** Peripheral FMC base address */
#define FMC_BASE                                 (0x40034000u)
/** Peripheral FMC base pointer */
#define FMC                                      ((FMC_Type *)FMC_BASE)
/** Array initializer of FMC peripheral base addresses */
#define FMC_BASE_ADDRS                           { FMC_BASE }
/** Array initializer of FMC peripheral base pointers */
#define FMC_BASE_PTRS                            { FMC }

/*!
 * @}
 */ /* end of group FMC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- GINT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GINT_Peripheral_Access_Layer GINT Peripheral Access Layer
 * @{
 */

/** GINT - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< GPIO grouped interrupt control register, offset: 0x0 */
       uint8_t RESERVED_0[28];
  __IO uint32_t PORT_POL[2];                       /**< GPIO grouped interrupt port 0 polarity register, array offset: 0x20, array step: 0x4 */
       uint8_t RESERVED_1[24];
  __IO uint32_t PORT_ENA[2];                       /**< GPIO grouped interrupt port 0 enable register, array offset: 0x40, array step: 0x4 */
} GINT_Type;

/* ----------------------------------------------------------------------------
   -- GINT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GINT_Register_Masks GINT Register Masks
 * @{
 */

/*! @name CTRL - GPIO grouped interrupt control register */
#define GINT_CTRL_INT_MASK                       (0x1U)
#define GINT_CTRL_INT_SHIFT                      (0U)
#define GINT_CTRL_INT(x)                         (((uint32_t)(((uint32_t)(x)) << GINT_CTRL_INT_SHIFT)) & GINT_CTRL_INT_MASK)
#define GINT_CTRL_COMB_MASK                      (0x2U)
#define GINT_CTRL_COMB_SHIFT                     (1U)
#define GINT_CTRL_COMB(x)                        (((uint32_t)(((uint32_t)(x)) << GINT_CTRL_COMB_SHIFT)) & GINT_CTRL_COMB_MASK)
#define GINT_CTRL_TRIG_MASK                      (0x4U)
#define GINT_CTRL_TRIG_SHIFT                     (2U)
#define GINT_CTRL_TRIG(x)                        (((uint32_t)(((uint32_t)(x)) << GINT_CTRL_TRIG_SHIFT)) & GINT_CTRL_TRIG_MASK)

/*! @name PORT_POL - GPIO grouped interrupt port 0 polarity register */
#define GINT_PORT_POL_POL_MASK                   (0xFFFFFFFFU)
#define GINT_PORT_POL_POL_SHIFT                  (0U)
#define GINT_PORT_POL_POL(x)                     (((uint32_t)(((uint32_t)(x)) << GINT_PORT_POL_POL_SHIFT)) & GINT_PORT_POL_POL_MASK)

/* The count of GINT_PORT_POL */
#define GINT_PORT_POL_COUNT                      (2U)

/*! @name PORT_ENA - GPIO grouped interrupt port 0 enable register */
#define GINT_PORT_ENA_ENA_MASK                   (0xFFFFFFFFU)
#define GINT_PORT_ENA_ENA_SHIFT                  (0U)
#define GINT_PORT_ENA_ENA(x)                     (((uint32_t)(((uint32_t)(x)) << GINT_PORT_ENA_ENA_SHIFT)) & GINT_PORT_ENA_ENA_MASK)

/* The count of GINT_PORT_ENA */
#define GINT_PORT_ENA_COUNT                      (2U)


/*!
 * @}
 */ /* end of group GINT_Register_Masks */


/* GINT - Peripheral instance base addresses */
/** Peripheral GINT0 base address */
#define GINT0_BASE                               (0x40002000u)
/** Peripheral GINT0 base pointer */
#define GINT0                                    ((GINT_Type *)GINT0_BASE)
/** Peripheral GINT1 base address */
#define GINT1_BASE                               (0x40003000u)
/** Peripheral GINT1 base pointer */
#define GINT1                                    ((GINT_Type *)GINT1_BASE)
/** Array initializer of GINT peripheral base addresses */
#define GINT_BASE_ADDRS                          { GINT0_BASE, GINT1_BASE }
/** Array initializer of GINT peripheral base pointers */
#define GINT_BASE_PTRS                           { GINT0, GINT1 }
/** Interrupt vectors for the GINT peripheral type */
#define GINT_IRQS                                { GINT0_IRQn, GINT1_IRQn }

/*!
 * @}
 */ /* end of group GINT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- GPIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer
 * @{
 */

/** GPIO - Register Layout Typedef */
typedef struct {
  __IO uint8_t B[6][32];                           /**< Byte pin registers for all port 0 and 1 GPIO pins, array offset: 0x0, array step: index*0x20, index2*0x1 */
       uint8_t RESERVED_0[3904];
  __IO uint32_t W[6][32];                          /**< Word pin registers for all port 0 and 1 GPIO pins, array offset: 0x1000, array step: index*0x80, index2*0x4 */
       uint8_t RESERVED_1[3328];
  __IO uint32_t DIR[6];                            /**< Direction registers, array offset: 0x2000, array step: 0x4 */
       uint8_t RESERVED_2[104];
  __IO uint32_t MASK[6];                           /**< Mask register, array offset: 0x2080, array step: 0x4 */
       uint8_t RESERVED_3[104];
  __IO uint32_t PIN[6];                            /**< Port pin register, array offset: 0x2100, array step: 0x4 */
       uint8_t RESERVED_4[104];
  __IO uint32_t MPIN[6];                           /**< Masked port register, array offset: 0x2180, array step: 0x4 */
       uint8_t RESERVED_5[104];
  __IO uint32_t SET[6];                            /**< Write: Set register for port Read: output bits for port, array offset: 0x2200, array step: 0x4 */
       uint8_t RESERVED_6[104];
  __O  uint32_t CLR[6];                            /**< Clear port, array offset: 0x2280, array step: 0x4 */
       uint8_t RESERVED_7[104];
  __O  uint32_t NOT[6];                            /**< Toggle port, array offset: 0x2300, array step: 0x4 */
       uint8_t RESERVED_8[104];
  __O  uint32_t DIRSET[6];                         /**< Set pin direction bits for port, array offset: 0x2380, array step: 0x4 */
       uint8_t RESERVED_9[104];
  __O  uint32_t DIRCLR[6];                         /**< Clear pin direction bits for port, array offset: 0x2400, array step: 0x4 */
       uint8_t RESERVED_10[104];
  __O  uint32_t DIRNOT[6];                         /**< Toggle pin direction bits for port, array offset: 0x2480, array step: 0x4 */
} GPIO_Type;

/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Masks GPIO Register Masks
 * @{
 */

/*! @name B - Byte pin registers for all port 0 and 1 GPIO pins */
#define GPIO_B_PBYTE_MASK                        (0x1U)
#define GPIO_B_PBYTE_SHIFT                       (0U)
#define GPIO_B_PBYTE(x)                          (((uint8_t)(((uint8_t)(x)) << GPIO_B_PBYTE_SHIFT)) & GPIO_B_PBYTE_MASK)

/* The count of GPIO_B */
#define GPIO_B_COUNT                             (6U)

/* The count of GPIO_B */
#define GPIO_B_COUNT2                            (32U)

/*! @name W - Word pin registers for all port 0 and 1 GPIO pins */
#define GPIO_W_PWORD_MASK                        (0xFFFFFFFFU)
#define GPIO_W_PWORD_SHIFT                       (0U)
#define GPIO_W_PWORD(x)                          (((uint32_t)(((uint32_t)(x)) << GPIO_W_PWORD_SHIFT)) & GPIO_W_PWORD_MASK)

/* The count of GPIO_W */
#define GPIO_W_COUNT                             (6U)

/* The count of GPIO_W */
#define GPIO_W_COUNT2                            (32U)

/*! @name DIR - Direction registers */
#define GPIO_DIR_DIRP_MASK                       (0xFFFFFFFFU)
#define GPIO_DIR_DIRP_SHIFT                      (0U)
#define GPIO_DIR_DIRP(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_DIR_DIRP_SHIFT)) & GPIO_DIR_DIRP_MASK)

/* The count of GPIO_DIR */
#define GPIO_DIR_COUNT                           (6U)

/*! @name MASK - Mask register */
#define GPIO_MASK_MASKP_MASK                     (0xFFFFFFFFU)
#define GPIO_MASK_MASKP_SHIFT                    (0U)
#define GPIO_MASK_MASKP(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_MASK_MASKP_SHIFT)) & GPIO_MASK_MASKP_MASK)

/* The count of GPIO_MASK */
#define GPIO_MASK_COUNT                          (6U)

/*! @name PIN - Port pin register */
#define GPIO_PIN_PORT_MASK                       (0xFFFFFFFFU)
#define GPIO_PIN_PORT_SHIFT                      (0U)
#define GPIO_PIN_PORT(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_PIN_PORT_SHIFT)) & GPIO_PIN_PORT_MASK)

/* The count of GPIO_PIN */
#define GPIO_PIN_COUNT                           (6U)

/*! @name MPIN - Masked port register */
#define GPIO_MPIN_MPORTP_MASK                    (0xFFFFFFFFU)
#define GPIO_MPIN_MPORTP_SHIFT                   (0U)
#define GPIO_MPIN_MPORTP(x)                      (((uint32_t)(((uint32_t)(x)) << GPIO_MPIN_MPORTP_SHIFT)) & GPIO_MPIN_MPORTP_MASK)

/* The count of GPIO_MPIN */
#define GPIO_MPIN_COUNT                          (6U)

/*! @name SET - Write: Set register for port Read: output bits for port */
#define GPIO_SET_SETP_MASK                       (0xFFFFFFFFU)
#define GPIO_SET_SETP_SHIFT                      (0U)
#define GPIO_SET_SETP(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_SET_SETP_SHIFT)) & GPIO_SET_SETP_MASK)

/* The count of GPIO_SET */
#define GPIO_SET_COUNT                           (6U)

/*! @name CLR - Clear port */
#define GPIO_CLR_CLRP_MASK                       (0xFFFFFFFFU)
#define GPIO_CLR_CLRP_SHIFT                      (0U)
#define GPIO_CLR_CLRP(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_CLR_CLRP_SHIFT)) & GPIO_CLR_CLRP_MASK)

/* The count of GPIO_CLR */
#define GPIO_CLR_COUNT                           (6U)

/*! @name NOT - Toggle port */
#define GPIO_NOT_NOTP_MASK                       (0xFFFFFFFFU)
#define GPIO_NOT_NOTP_SHIFT                      (0U)
#define GPIO_NOT_NOTP(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_NOT_NOTP_SHIFT)) & GPIO_NOT_NOTP_MASK)

/* The count of GPIO_NOT */
#define GPIO_NOT_COUNT                           (6U)

/*! @name DIRSET - Set pin direction bits for port */
#define GPIO_DIRSET_DIRSETP_MASK                 (0x1FFFFFFFU)
#define GPIO_DIRSET_DIRSETP_SHIFT                (0U)
#define GPIO_DIRSET_DIRSETP(x)                   (((uint32_t)(((uint32_t)(x)) << GPIO_DIRSET_DIRSETP_SHIFT)) & GPIO_DIRSET_DIRSETP_MASK)

/* The count of GPIO_DIRSET */
#define GPIO_DIRSET_COUNT                        (6U)

/*! @name DIRCLR - Clear pin direction bits for port */
#define GPIO_DIRCLR_DIRCLRP_MASK                 (0x1FFFFFFFU)
#define GPIO_DIRCLR_DIRCLRP_SHIFT                (0U)
#define GPIO_DIRCLR_DIRCLRP(x)                   (((uint32_t)(((uint32_t)(x)) << GPIO_DIRCLR_DIRCLRP_SHIFT)) & GPIO_DIRCLR_DIRCLRP_MASK)

/* The count of GPIO_DIRCLR */
#define GPIO_DIRCLR_COUNT                        (6U)

/*! @name DIRNOT - Toggle pin direction bits for port */
#define GPIO_DIRNOT_DIRNOTP_MASK                 (0x1FFFFFFFU)
#define GPIO_DIRNOT_DIRNOTP_SHIFT                (0U)
#define GPIO_DIRNOT_DIRNOTP(x)                   (((uint32_t)(((uint32_t)(x)) << GPIO_DIRNOT_DIRNOTP_SHIFT)) & GPIO_DIRNOT_DIRNOTP_MASK)

/* The count of GPIO_DIRNOT */
#define GPIO_DIRNOT_COUNT                        (6U)


/*!
 * @}
 */ /* end of group GPIO_Register_Masks */


/* GPIO - Peripheral instance base addresses */
/** Peripheral GPIO base address */
#define GPIO_BASE                                (0x4008C000u)
/** Peripheral GPIO base pointer */
#define GPIO                                     ((GPIO_Type *)GPIO_BASE)
/** Array initializer of GPIO peripheral base addresses */
#define GPIO_BASE_ADDRS                          { GPIO_BASE }
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { GPIO }

/*!
 * @}
 */ /* end of group GPIO_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- I2C Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Peripheral_Access_Layer I2C Peripheral Access Layer
 * @{
 */

/** I2C - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[2048];
  __IO uint32_t CFG;                               /**< Configuration for shared functions., offset: 0x800 */
  __IO uint32_t STAT;                              /**< Status register for Master, Slave, and Monitor functions., offset: 0x804 */
  __IO uint32_t INTENSET;                          /**< Interrupt Enable Set and read register., offset: 0x808 */
  __O  uint32_t INTENCLR;                          /**< Interrupt Enable Clear register., offset: 0x80C */
  __IO uint32_t TIMEOUT;                           /**< Time-out value register., offset: 0x810 */
  __IO uint32_t CLKDIV;                            /**< Clock pre-divider for the entire I2C interface. This determines what time increments are used for the MSTTIME register, and controls some timing of the Slave function., offset: 0x814 */
  __I  uint32_t INTSTAT;                           /**< Interrupt Status register for Master, Slave, and Monitor functions., offset: 0x818 */
       uint8_t RESERVED_1[4];
  __IO uint32_t MSTCTL;                            /**< Master control register., offset: 0x820 */
  __IO uint32_t MSTTIME;                           /**< Master timing configuration., offset: 0x824 */
  __IO uint32_t MSTDAT;                            /**< Combined Master receiver and transmitter data register., offset: 0x828 */
       uint8_t RESERVED_2[20];
  __IO uint32_t SLVCTL;                            /**< Slave control register., offset: 0x840 */
  __IO uint32_t SLVDAT;                            /**< Combined Slave receiver and transmitter data register., offset: 0x844 */
  __IO uint32_t SLVADR[4];                         /**< Slave address register., array offset: 0x848, array step: 0x4 */
  __IO uint32_t SLVQUAL0;                          /**< Slave Qualification for address 0., offset: 0x858 */
       uint8_t RESERVED_3[36];
  __I  uint32_t MONRXDAT;                          /**< Monitor receiver data register., offset: 0x880 */
       uint8_t RESERVED_4[1912];
  __I  uint32_t ID;                                /**< Peripheral identification register., offset: 0xFFC */
} I2C_Type;

/* ----------------------------------------------------------------------------
   -- I2C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Masks I2C Register Masks
 * @{
 */

/*! @name CFG - Configuration for shared functions. */
#define I2C_CFG_MSTEN_MASK                       (0x1U)
#define I2C_CFG_MSTEN_SHIFT                      (0U)
#define I2C_CFG_MSTEN(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_CFG_MSTEN_SHIFT)) & I2C_CFG_MSTEN_MASK)
#define I2C_CFG_SLVEN_MASK                       (0x2U)
#define I2C_CFG_SLVEN_SHIFT                      (1U)
#define I2C_CFG_SLVEN(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_CFG_SLVEN_SHIFT)) & I2C_CFG_SLVEN_MASK)
#define I2C_CFG_MONEN_MASK                       (0x4U)
#define I2C_CFG_MONEN_SHIFT                      (2U)
#define I2C_CFG_MONEN(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_CFG_MONEN_SHIFT)) & I2C_CFG_MONEN_MASK)
#define I2C_CFG_TIMEOUTEN_MASK                   (0x8U)
#define I2C_CFG_TIMEOUTEN_SHIFT                  (3U)
#define I2C_CFG_TIMEOUTEN(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_CFG_TIMEOUTEN_SHIFT)) & I2C_CFG_TIMEOUTEN_MASK)
#define I2C_CFG_MONCLKSTR_MASK                   (0x10U)
#define I2C_CFG_MONCLKSTR_SHIFT                  (4U)
#define I2C_CFG_MONCLKSTR(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_CFG_MONCLKSTR_SHIFT)) & I2C_CFG_MONCLKSTR_MASK)
#define I2C_CFG_HSCAPABLE_MASK                   (0x20U)
#define I2C_CFG_HSCAPABLE_SHIFT                  (5U)
#define I2C_CFG_HSCAPABLE(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_CFG_HSCAPABLE_SHIFT)) & I2C_CFG_HSCAPABLE_MASK)

/*! @name STAT - Status register for Master, Slave, and Monitor functions. */
#define I2C_STAT_MSTPENDING_MASK                 (0x1U)
#define I2C_STAT_MSTPENDING_SHIFT                (0U)
#define I2C_STAT_MSTPENDING(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MSTPENDING_SHIFT)) & I2C_STAT_MSTPENDING_MASK)
#define I2C_STAT_MSTSTATE_MASK                   (0xEU)
#define I2C_STAT_MSTSTATE_SHIFT                  (1U)
#define I2C_STAT_MSTSTATE(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MSTSTATE_SHIFT)) & I2C_STAT_MSTSTATE_MASK)
#define I2C_STAT_MSTARBLOSS_MASK                 (0x10U)
#define I2C_STAT_MSTARBLOSS_SHIFT                (4U)
#define I2C_STAT_MSTARBLOSS(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MSTARBLOSS_SHIFT)) & I2C_STAT_MSTARBLOSS_MASK)
#define I2C_STAT_MSTSTSTPERR_MASK                (0x40U)
#define I2C_STAT_MSTSTSTPERR_SHIFT               (6U)
#define I2C_STAT_MSTSTSTPERR(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MSTSTSTPERR_SHIFT)) & I2C_STAT_MSTSTSTPERR_MASK)
#define I2C_STAT_SLVPENDING_MASK                 (0x100U)
#define I2C_STAT_SLVPENDING_SHIFT                (8U)
#define I2C_STAT_SLVPENDING(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVPENDING_SHIFT)) & I2C_STAT_SLVPENDING_MASK)
#define I2C_STAT_SLVSTATE_MASK                   (0x600U)
#define I2C_STAT_SLVSTATE_SHIFT                  (9U)
#define I2C_STAT_SLVSTATE(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVSTATE_SHIFT)) & I2C_STAT_SLVSTATE_MASK)
#define I2C_STAT_SLVNOTSTR_MASK                  (0x800U)
#define I2C_STAT_SLVNOTSTR_SHIFT                 (11U)
#define I2C_STAT_SLVNOTSTR(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVNOTSTR_SHIFT)) & I2C_STAT_SLVNOTSTR_MASK)
#define I2C_STAT_SLVIDX_MASK                     (0x3000U)
#define I2C_STAT_SLVIDX_SHIFT                    (12U)
#define I2C_STAT_SLVIDX(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVIDX_SHIFT)) & I2C_STAT_SLVIDX_MASK)
#define I2C_STAT_SLVSEL_MASK                     (0x4000U)
#define I2C_STAT_SLVSEL_SHIFT                    (14U)
#define I2C_STAT_SLVSEL(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVSEL_SHIFT)) & I2C_STAT_SLVSEL_MASK)
#define I2C_STAT_SLVDESEL_MASK                   (0x8000U)
#define I2C_STAT_SLVDESEL_SHIFT                  (15U)
#define I2C_STAT_SLVDESEL(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVDESEL_SHIFT)) & I2C_STAT_SLVDESEL_MASK)
#define I2C_STAT_MONRDY_MASK                     (0x10000U)
#define I2C_STAT_MONRDY_SHIFT                    (16U)
#define I2C_STAT_MONRDY(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MONRDY_SHIFT)) & I2C_STAT_MONRDY_MASK)
#define I2C_STAT_MONOV_MASK                      (0x20000U)
#define I2C_STAT_MONOV_SHIFT                     (17U)
#define I2C_STAT_MONOV(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MONOV_SHIFT)) & I2C_STAT_MONOV_MASK)
#define I2C_STAT_MONACTIVE_MASK                  (0x40000U)
#define I2C_STAT_MONACTIVE_SHIFT                 (18U)
#define I2C_STAT_MONACTIVE(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MONACTIVE_SHIFT)) & I2C_STAT_MONACTIVE_MASK)
#define I2C_STAT_MONIDLE_MASK                    (0x80000U)
#define I2C_STAT_MONIDLE_SHIFT                   (19U)
#define I2C_STAT_MONIDLE(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MONIDLE_SHIFT)) & I2C_STAT_MONIDLE_MASK)
#define I2C_STAT_EVENTTIMEOUT_MASK               (0x1000000U)
#define I2C_STAT_EVENTTIMEOUT_SHIFT              (24U)
#define I2C_STAT_EVENTTIMEOUT(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_STAT_EVENTTIMEOUT_SHIFT)) & I2C_STAT_EVENTTIMEOUT_MASK)
#define I2C_STAT_SCLTIMEOUT_MASK                 (0x2000000U)
#define I2C_STAT_SCLTIMEOUT_SHIFT                (25U)
#define I2C_STAT_SCLTIMEOUT(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SCLTIMEOUT_SHIFT)) & I2C_STAT_SCLTIMEOUT_MASK)

/*! @name INTENSET - Interrupt Enable Set and read register. */
#define I2C_INTENSET_MSTPENDINGEN_MASK           (0x1U)
#define I2C_INTENSET_MSTPENDINGEN_SHIFT          (0U)
#define I2C_INTENSET_MSTPENDINGEN(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MSTPENDINGEN_SHIFT)) & I2C_INTENSET_MSTPENDINGEN_MASK)
#define I2C_INTENSET_MSTARBLOSSEN_MASK           (0x10U)
#define I2C_INTENSET_MSTARBLOSSEN_SHIFT          (4U)
#define I2C_INTENSET_MSTARBLOSSEN(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MSTARBLOSSEN_SHIFT)) & I2C_INTENSET_MSTARBLOSSEN_MASK)
#define I2C_INTENSET_MSTSTSTPERREN_MASK          (0x40U)
#define I2C_INTENSET_MSTSTSTPERREN_SHIFT         (6U)
#define I2C_INTENSET_MSTSTSTPERREN(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MSTSTSTPERREN_SHIFT)) & I2C_INTENSET_MSTSTSTPERREN_MASK)
#define I2C_INTENSET_SLVPENDINGEN_MASK           (0x100U)
#define I2C_INTENSET_SLVPENDINGEN_SHIFT          (8U)
#define I2C_INTENSET_SLVPENDINGEN(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_SLVPENDINGEN_SHIFT)) & I2C_INTENSET_SLVPENDINGEN_MASK)
#define I2C_INTENSET_SLVNOTSTREN_MASK            (0x800U)
#define I2C_INTENSET_SLVNOTSTREN_SHIFT           (11U)
#define I2C_INTENSET_SLVNOTSTREN(x)              (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_SLVNOTSTREN_SHIFT)) & I2C_INTENSET_SLVNOTSTREN_MASK)
#define I2C_INTENSET_SLVDESELEN_MASK             (0x8000U)
#define I2C_INTENSET_SLVDESELEN_SHIFT            (15U)
#define I2C_INTENSET_SLVDESELEN(x)               (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_SLVDESELEN_SHIFT)) & I2C_INTENSET_SLVDESELEN_MASK)
#define I2C_INTENSET_MONRDYEN_MASK               (0x10000U)
#define I2C_INTENSET_MONRDYEN_SHIFT              (16U)
#define I2C_INTENSET_MONRDYEN(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MONRDYEN_SHIFT)) & I2C_INTENSET_MONRDYEN_MASK)
#define I2C_INTENSET_MONOVEN_MASK                (0x20000U)
#define I2C_INTENSET_MONOVEN_SHIFT               (17U)
#define I2C_INTENSET_MONOVEN(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MONOVEN_SHIFT)) & I2C_INTENSET_MONOVEN_MASK)
#define I2C_INTENSET_MONIDLEEN_MASK              (0x80000U)
#define I2C_INTENSET_MONIDLEEN_SHIFT             (19U)
#define I2C_INTENSET_MONIDLEEN(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MONIDLEEN_SHIFT)) & I2C_INTENSET_MONIDLEEN_MASK)
#define I2C_INTENSET_EVENTTIMEOUTEN_MASK         (0x1000000U)
#define I2C_INTENSET_EVENTTIMEOUTEN_SHIFT        (24U)
#define I2C_INTENSET_EVENTTIMEOUTEN(x)           (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_EVENTTIMEOUTEN_SHIFT)) & I2C_INTENSET_EVENTTIMEOUTEN_MASK)
#define I2C_INTENSET_SCLTIMEOUTEN_MASK           (0x2000000U)
#define I2C_INTENSET_SCLTIMEOUTEN_SHIFT          (25U)
#define I2C_INTENSET_SCLTIMEOUTEN(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_SCLTIMEOUTEN_SHIFT)) & I2C_INTENSET_SCLTIMEOUTEN_MASK)

/*! @name INTENCLR - Interrupt Enable Clear register. */
#define I2C_INTENCLR_MSTPENDINGCLR_MASK          (0x1U)
#define I2C_INTENCLR_MSTPENDINGCLR_SHIFT         (0U)
#define I2C_INTENCLR_MSTPENDINGCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MSTPENDINGCLR_SHIFT)) & I2C_INTENCLR_MSTPENDINGCLR_MASK)
#define I2C_INTENCLR_MSTARBLOSSCLR_MASK          (0x10U)
#define I2C_INTENCLR_MSTARBLOSSCLR_SHIFT         (4U)
#define I2C_INTENCLR_MSTARBLOSSCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MSTARBLOSSCLR_SHIFT)) & I2C_INTENCLR_MSTARBLOSSCLR_MASK)
#define I2C_INTENCLR_MSTSTSTPERRCLR_MASK         (0x40U)
#define I2C_INTENCLR_MSTSTSTPERRCLR_SHIFT        (6U)
#define I2C_INTENCLR_MSTSTSTPERRCLR(x)           (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MSTSTSTPERRCLR_SHIFT)) & I2C_INTENCLR_MSTSTSTPERRCLR_MASK)
#define I2C_INTENCLR_SLVPENDINGCLR_MASK          (0x100U)
#define I2C_INTENCLR_SLVPENDINGCLR_SHIFT         (8U)
#define I2C_INTENCLR_SLVPENDINGCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SLVPENDINGCLR_SHIFT)) & I2C_INTENCLR_SLVPENDINGCLR_MASK)
#define I2C_INTENCLR_SLVNOTSTRCLR_MASK           (0x800U)
#define I2C_INTENCLR_SLVNOTSTRCLR_SHIFT          (11U)
#define I2C_INTENCLR_SLVNOTSTRCLR(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SLVNOTSTRCLR_SHIFT)) & I2C_INTENCLR_SLVNOTSTRCLR_MASK)
#define I2C_INTENCLR_SLVDESELCLR_MASK            (0x8000U)
#define I2C_INTENCLR_SLVDESELCLR_SHIFT           (15U)
#define I2C_INTENCLR_SLVDESELCLR(x)              (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SLVDESELCLR_SHIFT)) & I2C_INTENCLR_SLVDESELCLR_MASK)
#define I2C_INTENCLR_MONRDYCLR_MASK              (0x10000U)
#define I2C_INTENCLR_MONRDYCLR_SHIFT             (16U)
#define I2C_INTENCLR_MONRDYCLR(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MONRDYCLR_SHIFT)) & I2C_INTENCLR_MONRDYCLR_MASK)
#define I2C_INTENCLR_MONOVCLR_MASK               (0x20000U)
#define I2C_INTENCLR_MONOVCLR_SHIFT              (17U)
#define I2C_INTENCLR_MONOVCLR(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MONOVCLR_SHIFT)) & I2C_INTENCLR_MONOVCLR_MASK)
#define I2C_INTENCLR_MONIDLECLR_MASK             (0x80000U)
#define I2C_INTENCLR_MONIDLECLR_SHIFT            (19U)
#define I2C_INTENCLR_MONIDLECLR(x)               (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MONIDLECLR_SHIFT)) & I2C_INTENCLR_MONIDLECLR_MASK)
#define I2C_INTENCLR_EVENTTIMEOUTCLR_MASK        (0x1000000U)
#define I2C_INTENCLR_EVENTTIMEOUTCLR_SHIFT       (24U)
#define I2C_INTENCLR_EVENTTIMEOUTCLR(x)          (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_EVENTTIMEOUTCLR_SHIFT)) & I2C_INTENCLR_EVENTTIMEOUTCLR_MASK)
#define I2C_INTENCLR_SCLTIMEOUTCLR_MASK          (0x2000000U)
#define I2C_INTENCLR_SCLTIMEOUTCLR_SHIFT         (25U)
#define I2C_INTENCLR_SCLTIMEOUTCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SCLTIMEOUTCLR_SHIFT)) & I2C_INTENCLR_SCLTIMEOUTCLR_MASK)

/*! @name TIMEOUT - Time-out value register. */
#define I2C_TIMEOUT_TOMIN_MASK                   (0xFU)
#define I2C_TIMEOUT_TOMIN_SHIFT                  (0U)
#define I2C_TIMEOUT_TOMIN(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_TIMEOUT_TOMIN_SHIFT)) & I2C_TIMEOUT_TOMIN_MASK)
#define I2C_TIMEOUT_TO_MASK                      (0xFFF0U)
#define I2C_TIMEOUT_TO_SHIFT                     (4U)
#define I2C_TIMEOUT_TO(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_TIMEOUT_TO_SHIFT)) & I2C_TIMEOUT_TO_MASK)

/*! @name CLKDIV - Clock pre-divider for the entire I2C interface. This determines what time increments are used for the MSTTIME register, and controls some timing of the Slave function. */
#define I2C_CLKDIV_DIVVAL_MASK                   (0xFFFFU)
#define I2C_CLKDIV_DIVVAL_SHIFT                  (0U)
#define I2C_CLKDIV_DIVVAL(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_CLKDIV_DIVVAL_SHIFT)) & I2C_CLKDIV_DIVVAL_MASK)

/*! @name INTSTAT - Interrupt Status register for Master, Slave, and Monitor functions. */
#define I2C_INTSTAT_MSTPENDING_MASK              (0x1U)
#define I2C_INTSTAT_MSTPENDING_SHIFT             (0U)
#define I2C_INTSTAT_MSTPENDING(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MSTPENDING_SHIFT)) & I2C_INTSTAT_MSTPENDING_MASK)
#define I2C_INTSTAT_MSTARBLOSS_MASK              (0x10U)
#define I2C_INTSTAT_MSTARBLOSS_SHIFT             (4U)
#define I2C_INTSTAT_MSTARBLOSS(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MSTARBLOSS_SHIFT)) & I2C_INTSTAT_MSTARBLOSS_MASK)
#define I2C_INTSTAT_MSTSTSTPERR_MASK             (0x40U)
#define I2C_INTSTAT_MSTSTSTPERR_SHIFT            (6U)
#define I2C_INTSTAT_MSTSTSTPERR(x)               (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MSTSTSTPERR_SHIFT)) & I2C_INTSTAT_MSTSTSTPERR_MASK)
#define I2C_INTSTAT_SLVPENDING_MASK              (0x100U)
#define I2C_INTSTAT_SLVPENDING_SHIFT             (8U)
#define I2C_INTSTAT_SLVPENDING(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SLVPENDING_SHIFT)) & I2C_INTSTAT_SLVPENDING_MASK)
#define I2C_INTSTAT_SLVNOTSTR_MASK               (0x800U)
#define I2C_INTSTAT_SLVNOTSTR_SHIFT              (11U)
#define I2C_INTSTAT_SLVNOTSTR(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SLVNOTSTR_SHIFT)) & I2C_INTSTAT_SLVNOTSTR_MASK)
#define I2C_INTSTAT_SLVDESEL_MASK                (0x8000U)
#define I2C_INTSTAT_SLVDESEL_SHIFT               (15U)
#define I2C_INTSTAT_SLVDESEL(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SLVDESEL_SHIFT)) & I2C_INTSTAT_SLVDESEL_MASK)
#define I2C_INTSTAT_MONRDY_MASK                  (0x10000U)
#define I2C_INTSTAT_MONRDY_SHIFT                 (16U)
#define I2C_INTSTAT_MONRDY(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MONRDY_SHIFT)) & I2C_INTSTAT_MONRDY_MASK)
#define I2C_INTSTAT_MONOV_MASK                   (0x20000U)
#define I2C_INTSTAT_MONOV_SHIFT                  (17U)
#define I2C_INTSTAT_MONOV(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MONOV_SHIFT)) & I2C_INTSTAT_MONOV_MASK)
#define I2C_INTSTAT_MONIDLE_MASK                 (0x80000U)
#define I2C_INTSTAT_MONIDLE_SHIFT                (19U)
#define I2C_INTSTAT_MONIDLE(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MONIDLE_SHIFT)) & I2C_INTSTAT_MONIDLE_MASK)
#define I2C_INTSTAT_EVENTTIMEOUT_MASK            (0x1000000U)
#define I2C_INTSTAT_EVENTTIMEOUT_SHIFT           (24U)
#define I2C_INTSTAT_EVENTTIMEOUT(x)              (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_EVENTTIMEOUT_SHIFT)) & I2C_INTSTAT_EVENTTIMEOUT_MASK)
#define I2C_INTSTAT_SCLTIMEOUT_MASK              (0x2000000U)
#define I2C_INTSTAT_SCLTIMEOUT_SHIFT             (25U)
#define I2C_INTSTAT_SCLTIMEOUT(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SCLTIMEOUT_SHIFT)) & I2C_INTSTAT_SCLTIMEOUT_MASK)

/*! @name MSTCTL - Master control register. */
#define I2C_MSTCTL_MSTCONTINUE_MASK              (0x1U)
#define I2C_MSTCTL_MSTCONTINUE_SHIFT             (0U)
#define I2C_MSTCTL_MSTCONTINUE(x)                (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTCONTINUE_SHIFT)) & I2C_MSTCTL_MSTCONTINUE_MASK)
#define I2C_MSTCTL_MSTSTART_MASK                 (0x2U)
#define I2C_MSTCTL_MSTSTART_SHIFT                (1U)
#define I2C_MSTCTL_MSTSTART(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTSTART_SHIFT)) & I2C_MSTCTL_MSTSTART_MASK)
#define I2C_MSTCTL_MSTSTOP_MASK                  (0x4U)
#define I2C_MSTCTL_MSTSTOP_SHIFT                 (2U)
#define I2C_MSTCTL_MSTSTOP(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTSTOP_SHIFT)) & I2C_MSTCTL_MSTSTOP_MASK)
#define I2C_MSTCTL_MSTDMA_MASK                   (0x8U)
#define I2C_MSTCTL_MSTDMA_SHIFT                  (3U)
#define I2C_MSTCTL_MSTDMA(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTDMA_SHIFT)) & I2C_MSTCTL_MSTDMA_MASK)

/*! @name MSTTIME - Master timing configuration. */
#define I2C_MSTTIME_MSTSCLLOW_MASK               (0x7U)
#define I2C_MSTTIME_MSTSCLLOW_SHIFT              (0U)
#define I2C_MSTTIME_MSTSCLLOW(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_MSTTIME_MSTSCLLOW_SHIFT)) & I2C_MSTTIME_MSTSCLLOW_MASK)
#define I2C_MSTTIME_MSTSCLHIGH_MASK              (0x70U)
#define I2C_MSTTIME_MSTSCLHIGH_SHIFT             (4U)
#define I2C_MSTTIME_MSTSCLHIGH(x)                (((uint32_t)(((uint32_t)(x)) << I2C_MSTTIME_MSTSCLHIGH_SHIFT)) & I2C_MSTTIME_MSTSCLHIGH_MASK)

/*! @name MSTDAT - Combined Master receiver and transmitter data register. */
#define I2C_MSTDAT_DATA_MASK                     (0xFFU)
#define I2C_MSTDAT_DATA_SHIFT                    (0U)
#define I2C_MSTDAT_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_MSTDAT_DATA_SHIFT)) & I2C_MSTDAT_DATA_MASK)

/*! @name SLVCTL - Slave control register. */
#define I2C_SLVCTL_SLVCONTINUE_MASK              (0x1U)
#define I2C_SLVCTL_SLVCONTINUE_SHIFT             (0U)
#define I2C_SLVCTL_SLVCONTINUE(x)                (((uint32_t)(((uint32_t)(x)) << I2C_SLVCTL_SLVCONTINUE_SHIFT)) & I2C_SLVCTL_SLVCONTINUE_MASK)
#define I2C_SLVCTL_SLVNACK_MASK                  (0x2U)
#define I2C_SLVCTL_SLVNACK_SHIFT                 (1U)
#define I2C_SLVCTL_SLVNACK(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_SLVCTL_SLVNACK_SHIFT)) & I2C_SLVCTL_SLVNACK_MASK)
#define I2C_SLVCTL_SLVDMA_MASK                   (0x8U)
#define I2C_SLVCTL_SLVDMA_SHIFT                  (3U)
#define I2C_SLVCTL_SLVDMA(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_SLVCTL_SLVDMA_SHIFT)) & I2C_SLVCTL_SLVDMA_MASK)
#define I2C_SLVCTL_AUTOACK_MASK                  (0x100U)
#define I2C_SLVCTL_AUTOACK_SHIFT                 (8U)
#define I2C_SLVCTL_AUTOACK(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_SLVCTL_AUTOACK_SHIFT)) & I2C_SLVCTL_AUTOACK_MASK)
#define I2C_SLVCTL_AUTOMATCHREAD_MASK            (0x200U)
#define I2C_SLVCTL_AUTOMATCHREAD_SHIFT           (9U)
#define I2C_SLVCTL_AUTOMATCHREAD(x)              (((uint32_t)(((uint32_t)(x)) << I2C_SLVCTL_AUTOMATCHREAD_SHIFT)) & I2C_SLVCTL_AUTOMATCHREAD_MASK)

/*! @name SLVDAT - Combined Slave receiver and transmitter data register. */
#define I2C_SLVDAT_DATA_MASK                     (0xFFU)
#define I2C_SLVDAT_DATA_SHIFT                    (0U)
#define I2C_SLVDAT_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_SLVDAT_DATA_SHIFT)) & I2C_SLVDAT_DATA_MASK)

/*! @name SLVADR - Slave address register. */
#define I2C_SLVADR_SADISABLE_MASK                (0x1U)
#define I2C_SLVADR_SADISABLE_SHIFT               (0U)
#define I2C_SLVADR_SADISABLE(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_SLVADR_SADISABLE_SHIFT)) & I2C_SLVADR_SADISABLE_MASK)
#define I2C_SLVADR_SLVADR_MASK                   (0xFEU)
#define I2C_SLVADR_SLVADR_SHIFT                  (1U)
#define I2C_SLVADR_SLVADR(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_SLVADR_SLVADR_SHIFT)) & I2C_SLVADR_SLVADR_MASK)
#define I2C_SLVADR_AUTONACK_MASK                 (0x8000U)
#define I2C_SLVADR_AUTONACK_SHIFT                (15U)
#define I2C_SLVADR_AUTONACK(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_SLVADR_AUTONACK_SHIFT)) & I2C_SLVADR_AUTONACK_MASK)

/* The count of I2C_SLVADR */
#define I2C_SLVADR_COUNT                         (4U)

/*! @name SLVQUAL0 - Slave Qualification for address 0. */
#define I2C_SLVQUAL0_QUALMODE0_MASK              (0x1U)
#define I2C_SLVQUAL0_QUALMODE0_SHIFT             (0U)
#define I2C_SLVQUAL0_QUALMODE0(x)                (((uint32_t)(((uint32_t)(x)) << I2C_SLVQUAL0_QUALMODE0_SHIFT)) & I2C_SLVQUAL0_QUALMODE0_MASK)
#define I2C_SLVQUAL0_SLVQUAL0_MASK               (0xFEU)
#define I2C_SLVQUAL0_SLVQUAL0_SHIFT              (1U)
#define I2C_SLVQUAL0_SLVQUAL0(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_SLVQUAL0_SLVQUAL0_SHIFT)) & I2C_SLVQUAL0_SLVQUAL0_MASK)

/*! @name MONRXDAT - Monitor receiver data register. */
#define I2C_MONRXDAT_MONRXDAT_MASK               (0xFFU)
#define I2C_MONRXDAT_MONRXDAT_SHIFT              (0U)
#define I2C_MONRXDAT_MONRXDAT(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_MONRXDAT_MONRXDAT_SHIFT)) & I2C_MONRXDAT_MONRXDAT_MASK)
#define I2C_MONRXDAT_MONSTART_MASK               (0x100U)
#define I2C_MONRXDAT_MONSTART_SHIFT              (8U)
#define I2C_MONRXDAT_MONSTART(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_MONRXDAT_MONSTART_SHIFT)) & I2C_MONRXDAT_MONSTART_MASK)
#define I2C_MONRXDAT_MONRESTART_MASK             (0x200U)
#define I2C_MONRXDAT_MONRESTART_SHIFT            (9U)
#define I2C_MONRXDAT_MONRESTART(x)               (((uint32_t)(((uint32_t)(x)) << I2C_MONRXDAT_MONRESTART_SHIFT)) & I2C_MONRXDAT_MONRESTART_MASK)
#define I2C_MONRXDAT_MONNACK_MASK                (0x400U)
#define I2C_MONRXDAT_MONNACK_SHIFT               (10U)
#define I2C_MONRXDAT_MONNACK(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_MONRXDAT_MONNACK_SHIFT)) & I2C_MONRXDAT_MONNACK_MASK)

/*! @name ID - Peripheral identification register. */
#define I2C_ID_APERTURE_MASK                     (0xFFU)
#define I2C_ID_APERTURE_SHIFT                    (0U)
#define I2C_ID_APERTURE(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_ID_APERTURE_SHIFT)) & I2C_ID_APERTURE_MASK)
#define I2C_ID_MINOR_REV_MASK                    (0xF00U)
#define I2C_ID_MINOR_REV_SHIFT                   (8U)
#define I2C_ID_MINOR_REV(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_ID_MINOR_REV_SHIFT)) & I2C_ID_MINOR_REV_MASK)
#define I2C_ID_MAJOR_REV_MASK                    (0xF000U)
#define I2C_ID_MAJOR_REV_SHIFT                   (12U)
#define I2C_ID_MAJOR_REV(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_ID_MAJOR_REV_SHIFT)) & I2C_ID_MAJOR_REV_MASK)
#define I2C_ID_ID_MASK                           (0xFFFF0000U)
#define I2C_ID_ID_SHIFT                          (16U)
#define I2C_ID_ID(x)                             (((uint32_t)(((uint32_t)(x)) << I2C_ID_ID_SHIFT)) & I2C_ID_ID_MASK)


/*!
 * @}
 */ /* end of group I2C_Register_Masks */


/* I2C - Peripheral instance base addresses */
/** Peripheral I2C0 base address */
#define I2C0_BASE                                (0x40086000u)
/** Peripheral I2C0 base pointer */
#define I2C0                                     ((I2C_Type *)I2C0_BASE)
/** Peripheral I2C1 base address */
#define I2C1_BASE                                (0x40087000u)
/** Peripheral I2C1 base pointer */
#define I2C1                                     ((I2C_Type *)I2C1_BASE)
/** Peripheral I2C2 base address */
#define I2C2_BASE                                (0x40088000u)
/** Peripheral I2C2 base pointer */
#define I2C2                                     ((I2C_Type *)I2C2_BASE)
/** Peripheral I2C3 base address */
#define I2C3_BASE                                (0x40089000u)
/** Peripheral I2C3 base pointer */
#define I2C3                                     ((I2C_Type *)I2C3_BASE)
/** Peripheral I2C4 base address */
#define I2C4_BASE                                (0x4008A000u)
/** Peripheral I2C4 base pointer */
#define I2C4                                     ((I2C_Type *)I2C4_BASE)
/** Peripheral I2C5 base address */
#define I2C5_BASE                                (0x40096000u)
/** Peripheral I2C5 base pointer */
#define I2C5                                     ((I2C_Type *)I2C5_BASE)
/** Peripheral I2C6 base address */
#define I2C6_BASE                                (0x40097000u)
/** Peripheral I2C6 base pointer */
#define I2C6                                     ((I2C_Type *)I2C6_BASE)
/** Peripheral I2C7 base address */
#define I2C7_BASE                                (0x40098000u)
/** Peripheral I2C7 base pointer */
#define I2C7                                     ((I2C_Type *)I2C7_BASE)
/** Peripheral I2C8 base address */
#define I2C8_BASE                                (0x40099000u)
/** Peripheral I2C8 base pointer */
#define I2C8                                     ((I2C_Type *)I2C8_BASE)
/** Peripheral I2C9 base address */
#define I2C9_BASE                                (0x4009A000u)
/** Peripheral I2C9 base pointer */
#define I2C9                                     ((I2C_Type *)I2C9_BASE)
/** Array initializer of I2C peripheral base addresses */
#define I2C_BASE_ADDRS                           { I2C0_BASE, I2C1_BASE, I2C2_BASE, I2C3_BASE, I2C4_BASE, I2C5_BASE, I2C6_BASE, I2C7_BASE, I2C8_BASE, I2C9_BASE }
/** Array initializer of I2C peripheral base pointers */
#define I2C_BASE_PTRS                            { I2C0, I2C1, I2C2, I2C3, I2C4, I2C5, I2C6, I2C7, I2C8, I2C9 }
/** Interrupt vectors for the I2C peripheral type */
#define I2C_IRQS                                 { FLEXCOMM0_IRQn, FLEXCOMM1_IRQn, FLEXCOMM2_IRQn, FLEXCOMM3_IRQn, FLEXCOMM4_IRQn, FLEXCOMM5_IRQn, FLEXCOMM6_IRQn, FLEXCOMM7_IRQn, FLEXCOMM8_IRQn, FLEXCOMM9_IRQn }

/*!
 * @}
 */ /* end of group I2C_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- I2S Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2S_Peripheral_Access_Layer I2S Peripheral Access Layer
 * @{
 */

/** I2S - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[32];
  struct {                                         /* offset: 0x20, array step: 0x20 */
    __IO uint32_t PCFG1;                             /**< Configuration register 1 for channel pair, array offset: 0x20, array step: 0x20 */
    __IO uint32_t PCFG2;                             /**< Configuration register 2 for channel pair, array offset: 0x24, array step: 0x20 */
    __IO uint32_t PSTAT;                             /**< Status register for channel pair, array offset: 0x28, array step: 0x20 */
         uint8_t RESERVED_0[20];
  } SECCHANNEL[3];
       uint8_t RESERVED_1[2944];
  __IO uint32_t CFG1;                              /**< Configuration register 1 for the primary channel pair., offset: 0xC00 */
  __IO uint32_t CFG2;                              /**< Configuration register 2 for the primary channel pair., offset: 0xC04 */
  __IO uint32_t STAT;                              /**< Status register for the primary channel pair., offset: 0xC08 */
       uint8_t RESERVED_2[16];
  __IO uint32_t DIV;                               /**< Clock divider, used by all channel pairs., offset: 0xC1C */
       uint8_t RESERVED_3[480];
  __IO uint32_t FIFOCFG;                           /**< FIFO configuration and enable register., offset: 0xE00 */
  __IO uint32_t FIFOSTAT;                          /**< FIFO status register., offset: 0xE04 */
  __IO uint32_t FIFOTRIG;                          /**< FIFO trigger settings for interrupt and DMA request., offset: 0xE08 */
       uint8_t RESERVED_4[4];
  __IO uint32_t FIFOINTENSET;                      /**< FIFO interrupt enable set (enable) and read register., offset: 0xE10 */
  __IO uint32_t FIFOINTENCLR;                      /**< FIFO interrupt enable clear (disable) and read register., offset: 0xE14 */
  __I  uint32_t FIFOINTSTAT;                       /**< FIFO interrupt status register., offset: 0xE18 */
       uint8_t RESERVED_5[4];
  __O  uint32_t FIFOWR;                            /**< FIFO write data., offset: 0xE20 */
  __O  uint32_t FIFOWR48H;                         /**< FIFO write data for upper data bits. May only be used if the I2S is configured for 2x 24-bit data and not using DMA., offset: 0xE24 */
       uint8_t RESERVED_6[8];
  __I  uint32_t FIFORD;                            /**< FIFO read data., offset: 0xE30 */
  __I  uint32_t FIFORD48H;                         /**< FIFO read data for upper data bits. May only be used if the I2S is configured for 2x 24-bit data and not using DMA., offset: 0xE34 */
       uint8_t RESERVED_7[8];
  __I  uint32_t FIFORDNOPOP;                       /**< FIFO data read with no FIFO pop., offset: 0xE40 */
  __I  uint32_t FIFORD48HNOPOP;                    /**< FIFO data read for upper data bits with no FIFO pop. May only be used if the I2S is configured for 2x 24-bit data and not using DMA., offset: 0xE44 */
       uint8_t RESERVED_8[4020];
  __I  uint32_t ID;                                /**< I2S Module identification, offset: 0x1DFC */
} I2S_Type;

/* ----------------------------------------------------------------------------
   -- I2S Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2S_Register_Masks I2S Register Masks
 * @{
 */

/*! @name SECCHANNEL_PCFG1 - Configuration register 1 for channel pair */
#define I2S_SECCHANNEL_PCFG1_PAIRENABLE_MASK     (0x1U)
#define I2S_SECCHANNEL_PCFG1_PAIRENABLE_SHIFT    (0U)
#define I2S_SECCHANNEL_PCFG1_PAIRENABLE(x)       (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PCFG1_PAIRENABLE_SHIFT)) & I2S_SECCHANNEL_PCFG1_PAIRENABLE_MASK)
#define I2S_SECCHANNEL_PCFG1_ONECHANNEL_MASK     (0x400U)
#define I2S_SECCHANNEL_PCFG1_ONECHANNEL_SHIFT    (10U)
#define I2S_SECCHANNEL_PCFG1_ONECHANNEL(x)       (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PCFG1_ONECHANNEL_SHIFT)) & I2S_SECCHANNEL_PCFG1_ONECHANNEL_MASK)

/* The count of I2S_SECCHANNEL_PCFG1 */
#define I2S_SECCHANNEL_PCFG1_COUNT               (3U)

/*! @name SECCHANNEL_PCFG2 - Configuration register 2 for channel pair */
#define I2S_SECCHANNEL_PCFG2_POSITION_MASK       (0x1FF0000U)
#define I2S_SECCHANNEL_PCFG2_POSITION_SHIFT      (16U)
#define I2S_SECCHANNEL_PCFG2_POSITION(x)         (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PCFG2_POSITION_SHIFT)) & I2S_SECCHANNEL_PCFG2_POSITION_MASK)

/* The count of I2S_SECCHANNEL_PCFG2 */
#define I2S_SECCHANNEL_PCFG2_COUNT               (3U)

/*! @name SECCHANNEL_PSTAT - Status register for channel pair */
#define I2S_SECCHANNEL_PSTAT_BUSY_MASK           (0x1U)
#define I2S_SECCHANNEL_PSTAT_BUSY_SHIFT          (0U)
#define I2S_SECCHANNEL_PSTAT_BUSY(x)             (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PSTAT_BUSY_SHIFT)) & I2S_SECCHANNEL_PSTAT_BUSY_MASK)
#define I2S_SECCHANNEL_PSTAT_SLVFRMERR_MASK      (0x2U)
#define I2S_SECCHANNEL_PSTAT_SLVFRMERR_SHIFT     (1U)
#define I2S_SECCHANNEL_PSTAT_SLVFRMERR(x)        (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PSTAT_SLVFRMERR_SHIFT)) & I2S_SECCHANNEL_PSTAT_SLVFRMERR_MASK)
#define I2S_SECCHANNEL_PSTAT_LR_MASK             (0x4U)
#define I2S_SECCHANNEL_PSTAT_LR_SHIFT            (2U)
#define I2S_SECCHANNEL_PSTAT_LR(x)               (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PSTAT_LR_SHIFT)) & I2S_SECCHANNEL_PSTAT_LR_MASK)
#define I2S_SECCHANNEL_PSTAT_DATAPAUSED_MASK     (0x8U)
#define I2S_SECCHANNEL_PSTAT_DATAPAUSED_SHIFT    (3U)
#define I2S_SECCHANNEL_PSTAT_DATAPAUSED(x)       (((uint32_t)(((uint32_t)(x)) << I2S_SECCHANNEL_PSTAT_DATAPAUSED_SHIFT)) & I2S_SECCHANNEL_PSTAT_DATAPAUSED_MASK)

/* The count of I2S_SECCHANNEL_PSTAT */
#define I2S_SECCHANNEL_PSTAT_COUNT               (3U)

/*! @name CFG1 - Configuration register 1 for the primary channel pair. */
#define I2S_CFG1_MAINENABLE_MASK                 (0x1U)
#define I2S_CFG1_MAINENABLE_SHIFT                (0U)
#define I2S_CFG1_MAINENABLE(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_MAINENABLE_SHIFT)) & I2S_CFG1_MAINENABLE_MASK)
#define I2S_CFG1_DATAPAUSE_MASK                  (0x2U)
#define I2S_CFG1_DATAPAUSE_SHIFT                 (1U)
#define I2S_CFG1_DATAPAUSE(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_DATAPAUSE_SHIFT)) & I2S_CFG1_DATAPAUSE_MASK)
#define I2S_CFG1_PAIRCOUNT_MASK                  (0xCU)
#define I2S_CFG1_PAIRCOUNT_SHIFT                 (2U)
#define I2S_CFG1_PAIRCOUNT(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_PAIRCOUNT_SHIFT)) & I2S_CFG1_PAIRCOUNT_MASK)
#define I2S_CFG1_MSTSLVCFG_MASK                  (0x30U)
#define I2S_CFG1_MSTSLVCFG_SHIFT                 (4U)
#define I2S_CFG1_MSTSLVCFG(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_MSTSLVCFG_SHIFT)) & I2S_CFG1_MSTSLVCFG_MASK)
#define I2S_CFG1_MODE_MASK                       (0xC0U)
#define I2S_CFG1_MODE_SHIFT                      (6U)
#define I2S_CFG1_MODE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_MODE_SHIFT)) & I2S_CFG1_MODE_MASK)
#define I2S_CFG1_RIGHTLOW_MASK                   (0x100U)
#define I2S_CFG1_RIGHTLOW_SHIFT                  (8U)
#define I2S_CFG1_RIGHTLOW(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_RIGHTLOW_SHIFT)) & I2S_CFG1_RIGHTLOW_MASK)
#define I2S_CFG1_LEFTJUST_MASK                   (0x200U)
#define I2S_CFG1_LEFTJUST_SHIFT                  (9U)
#define I2S_CFG1_LEFTJUST(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_LEFTJUST_SHIFT)) & I2S_CFG1_LEFTJUST_MASK)
#define I2S_CFG1_ONECHANNEL_MASK                 (0x400U)
#define I2S_CFG1_ONECHANNEL_SHIFT                (10U)
#define I2S_CFG1_ONECHANNEL(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_ONECHANNEL_SHIFT)) & I2S_CFG1_ONECHANNEL_MASK)
#define I2S_CFG1_PDMDATA_MASK                    (0x800U)
#define I2S_CFG1_PDMDATA_SHIFT                   (11U)
#define I2S_CFG1_PDMDATA(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_PDMDATA_SHIFT)) & I2S_CFG1_PDMDATA_MASK)
#define I2S_CFG1_SCK_POL_MASK                    (0x1000U)
#define I2S_CFG1_SCK_POL_SHIFT                   (12U)
#define I2S_CFG1_SCK_POL(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_SCK_POL_SHIFT)) & I2S_CFG1_SCK_POL_MASK)
#define I2S_CFG1_WS_POL_MASK                     (0x2000U)
#define I2S_CFG1_WS_POL_SHIFT                    (13U)
#define I2S_CFG1_WS_POL(x)                       (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_WS_POL_SHIFT)) & I2S_CFG1_WS_POL_MASK)
#define I2S_CFG1_DATALEN_MASK                    (0x1F0000U)
#define I2S_CFG1_DATALEN_SHIFT                   (16U)
#define I2S_CFG1_DATALEN(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_DATALEN_SHIFT)) & I2S_CFG1_DATALEN_MASK)

/*! @name CFG2 - Configuration register 2 for the primary channel pair. */
#define I2S_CFG2_FRAMELEN_MASK                   (0x1FFU)
#define I2S_CFG2_FRAMELEN_SHIFT                  (0U)
#define I2S_CFG2_FRAMELEN(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_CFG2_FRAMELEN_SHIFT)) & I2S_CFG2_FRAMELEN_MASK)
#define I2S_CFG2_POSITION_MASK                   (0x1FF0000U)
#define I2S_CFG2_POSITION_SHIFT                  (16U)
#define I2S_CFG2_POSITION(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_CFG2_POSITION_SHIFT)) & I2S_CFG2_POSITION_MASK)

/*! @name STAT - Status register for the primary channel pair. */
#define I2S_STAT_BUSY_MASK                       (0x1U)
#define I2S_STAT_BUSY_SHIFT                      (0U)
#define I2S_STAT_BUSY(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_STAT_BUSY_SHIFT)) & I2S_STAT_BUSY_MASK)
#define I2S_STAT_SLVFRMERR_MASK                  (0x2U)
#define I2S_STAT_SLVFRMERR_SHIFT                 (1U)
#define I2S_STAT_SLVFRMERR(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_STAT_SLVFRMERR_SHIFT)) & I2S_STAT_SLVFRMERR_MASK)
#define I2S_STAT_LR_MASK                         (0x4U)
#define I2S_STAT_LR_SHIFT                        (2U)
#define I2S_STAT_LR(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_STAT_LR_SHIFT)) & I2S_STAT_LR_MASK)
#define I2S_STAT_DATAPAUSED_MASK                 (0x8U)
#define I2S_STAT_DATAPAUSED_SHIFT                (3U)
#define I2S_STAT_DATAPAUSED(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_STAT_DATAPAUSED_SHIFT)) & I2S_STAT_DATAPAUSED_MASK)

/*! @name DIV - Clock divider, used by all channel pairs. */
#define I2S_DIV_DIV_MASK                         (0xFFFU)
#define I2S_DIV_DIV_SHIFT                        (0U)
#define I2S_DIV_DIV(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_DIV_DIV_SHIFT)) & I2S_DIV_DIV_MASK)

/*! @name FIFOCFG - FIFO configuration and enable register. */
#define I2S_FIFOCFG_ENABLETX_MASK                (0x1U)
#define I2S_FIFOCFG_ENABLETX_SHIFT               (0U)
#define I2S_FIFOCFG_ENABLETX(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_ENABLETX_SHIFT)) & I2S_FIFOCFG_ENABLETX_MASK)
#define I2S_FIFOCFG_ENABLERX_MASK                (0x2U)
#define I2S_FIFOCFG_ENABLERX_SHIFT               (1U)
#define I2S_FIFOCFG_ENABLERX(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_ENABLERX_SHIFT)) & I2S_FIFOCFG_ENABLERX_MASK)
#define I2S_FIFOCFG_TXI2SE0_MASK                 (0x4U)
#define I2S_FIFOCFG_TXI2SE0_SHIFT                (2U)
#define I2S_FIFOCFG_TXI2SE0(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_TXI2SE0_SHIFT)) & I2S_FIFOCFG_TXI2SE0_MASK)
#define I2S_FIFOCFG_PACK48_MASK                  (0x8U)
#define I2S_FIFOCFG_PACK48_SHIFT                 (3U)
#define I2S_FIFOCFG_PACK48(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_PACK48_SHIFT)) & I2S_FIFOCFG_PACK48_MASK)
#define I2S_FIFOCFG_SIZE_MASK                    (0x30U)
#define I2S_FIFOCFG_SIZE_SHIFT                   (4U)
#define I2S_FIFOCFG_SIZE(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_SIZE_SHIFT)) & I2S_FIFOCFG_SIZE_MASK)
#define I2S_FIFOCFG_DMATX_MASK                   (0x1000U)
#define I2S_FIFOCFG_DMATX_SHIFT                  (12U)
#define I2S_FIFOCFG_DMATX(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_DMATX_SHIFT)) & I2S_FIFOCFG_DMATX_MASK)
#define I2S_FIFOCFG_DMARX_MASK                   (0x2000U)
#define I2S_FIFOCFG_DMARX_SHIFT                  (13U)
#define I2S_FIFOCFG_DMARX(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_DMARX_SHIFT)) & I2S_FIFOCFG_DMARX_MASK)
#define I2S_FIFOCFG_WAKETX_MASK                  (0x4000U)
#define I2S_FIFOCFG_WAKETX_SHIFT                 (14U)
#define I2S_FIFOCFG_WAKETX(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_WAKETX_SHIFT)) & I2S_FIFOCFG_WAKETX_MASK)
#define I2S_FIFOCFG_WAKERX_MASK                  (0x8000U)
#define I2S_FIFOCFG_WAKERX_SHIFT                 (15U)
#define I2S_FIFOCFG_WAKERX(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_WAKERX_SHIFT)) & I2S_FIFOCFG_WAKERX_MASK)
#define I2S_FIFOCFG_EMPTYTX_MASK                 (0x10000U)
#define I2S_FIFOCFG_EMPTYTX_SHIFT                (16U)
#define I2S_FIFOCFG_EMPTYTX(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_EMPTYTX_SHIFT)) & I2S_FIFOCFG_EMPTYTX_MASK)
#define I2S_FIFOCFG_EMPTYRX_MASK                 (0x20000U)
#define I2S_FIFOCFG_EMPTYRX_SHIFT                (17U)
#define I2S_FIFOCFG_EMPTYRX(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_EMPTYRX_SHIFT)) & I2S_FIFOCFG_EMPTYRX_MASK)
#define I2S_FIFOCFG_POPDBG_MASK                  (0x40000U)
#define I2S_FIFOCFG_POPDBG_SHIFT                 (18U)
#define I2S_FIFOCFG_POPDBG(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_POPDBG_SHIFT)) & I2S_FIFOCFG_POPDBG_MASK)

/*! @name FIFOSTAT - FIFO status register. */
#define I2S_FIFOSTAT_TXERR_MASK                  (0x1U)
#define I2S_FIFOSTAT_TXERR_SHIFT                 (0U)
#define I2S_FIFOSTAT_TXERR(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_TXERR_SHIFT)) & I2S_FIFOSTAT_TXERR_MASK)
#define I2S_FIFOSTAT_RXERR_MASK                  (0x2U)
#define I2S_FIFOSTAT_RXERR_SHIFT                 (1U)
#define I2S_FIFOSTAT_RXERR(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_RXERR_SHIFT)) & I2S_FIFOSTAT_RXERR_MASK)
#define I2S_FIFOSTAT_PERINT_MASK                 (0x8U)
#define I2S_FIFOSTAT_PERINT_SHIFT                (3U)
#define I2S_FIFOSTAT_PERINT(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_PERINT_SHIFT)) & I2S_FIFOSTAT_PERINT_MASK)
#define I2S_FIFOSTAT_TXEMPTY_MASK                (0x10U)
#define I2S_FIFOSTAT_TXEMPTY_SHIFT               (4U)
#define I2S_FIFOSTAT_TXEMPTY(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_TXEMPTY_SHIFT)) & I2S_FIFOSTAT_TXEMPTY_MASK)
#define I2S_FIFOSTAT_TXNOTFULL_MASK              (0x20U)
#define I2S_FIFOSTAT_TXNOTFULL_SHIFT             (5U)
#define I2S_FIFOSTAT_TXNOTFULL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_TXNOTFULL_SHIFT)) & I2S_FIFOSTAT_TXNOTFULL_MASK)
#define I2S_FIFOSTAT_RXNOTEMPTY_MASK             (0x40U)
#define I2S_FIFOSTAT_RXNOTEMPTY_SHIFT            (6U)
#define I2S_FIFOSTAT_RXNOTEMPTY(x)               (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_RXNOTEMPTY_SHIFT)) & I2S_FIFOSTAT_RXNOTEMPTY_MASK)
#define I2S_FIFOSTAT_RXFULL_MASK                 (0x80U)
#define I2S_FIFOSTAT_RXFULL_SHIFT                (7U)
#define I2S_FIFOSTAT_RXFULL(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_RXFULL_SHIFT)) & I2S_FIFOSTAT_RXFULL_MASK)
#define I2S_FIFOSTAT_TXLVL_MASK                  (0x1F00U)
#define I2S_FIFOSTAT_TXLVL_SHIFT                 (8U)
#define I2S_FIFOSTAT_TXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_TXLVL_SHIFT)) & I2S_FIFOSTAT_TXLVL_MASK)
#define I2S_FIFOSTAT_RXLVL_MASK                  (0x1F0000U)
#define I2S_FIFOSTAT_RXLVL_SHIFT                 (16U)
#define I2S_FIFOSTAT_RXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_RXLVL_SHIFT)) & I2S_FIFOSTAT_RXLVL_MASK)

/*! @name FIFOTRIG - FIFO trigger settings for interrupt and DMA request. */
#define I2S_FIFOTRIG_TXLVLENA_MASK               (0x1U)
#define I2S_FIFOTRIG_TXLVLENA_SHIFT              (0U)
#define I2S_FIFOTRIG_TXLVLENA(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOTRIG_TXLVLENA_SHIFT)) & I2S_FIFOTRIG_TXLVLENA_MASK)
#define I2S_FIFOTRIG_RXLVLENA_MASK               (0x2U)
#define I2S_FIFOTRIG_RXLVLENA_SHIFT              (1U)
#define I2S_FIFOTRIG_RXLVLENA(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOTRIG_RXLVLENA_SHIFT)) & I2S_FIFOTRIG_RXLVLENA_MASK)
#define I2S_FIFOTRIG_TXLVL_MASK                  (0xF00U)
#define I2S_FIFOTRIG_TXLVL_SHIFT                 (8U)
#define I2S_FIFOTRIG_TXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOTRIG_TXLVL_SHIFT)) & I2S_FIFOTRIG_TXLVL_MASK)
#define I2S_FIFOTRIG_RXLVL_MASK                  (0xF0000U)
#define I2S_FIFOTRIG_RXLVL_SHIFT                 (16U)
#define I2S_FIFOTRIG_RXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOTRIG_RXLVL_SHIFT)) & I2S_FIFOTRIG_RXLVL_MASK)

/*! @name FIFOINTENSET - FIFO interrupt enable set (enable) and read register. */
#define I2S_FIFOINTENSET_TXERR_MASK              (0x1U)
#define I2S_FIFOINTENSET_TXERR_SHIFT             (0U)
#define I2S_FIFOINTENSET_TXERR(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENSET_TXERR_SHIFT)) & I2S_FIFOINTENSET_TXERR_MASK)
#define I2S_FIFOINTENSET_RXERR_MASK              (0x2U)
#define I2S_FIFOINTENSET_RXERR_SHIFT             (1U)
#define I2S_FIFOINTENSET_RXERR(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENSET_RXERR_SHIFT)) & I2S_FIFOINTENSET_RXERR_MASK)
#define I2S_FIFOINTENSET_TXLVL_MASK              (0x4U)
#define I2S_FIFOINTENSET_TXLVL_SHIFT             (2U)
#define I2S_FIFOINTENSET_TXLVL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENSET_TXLVL_SHIFT)) & I2S_FIFOINTENSET_TXLVL_MASK)
#define I2S_FIFOINTENSET_RXLVL_MASK              (0x8U)
#define I2S_FIFOINTENSET_RXLVL_SHIFT             (3U)
#define I2S_FIFOINTENSET_RXLVL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENSET_RXLVL_SHIFT)) & I2S_FIFOINTENSET_RXLVL_MASK)

/*! @name FIFOINTENCLR - FIFO interrupt enable clear (disable) and read register. */
#define I2S_FIFOINTENCLR_TXERR_MASK              (0x1U)
#define I2S_FIFOINTENCLR_TXERR_SHIFT             (0U)
#define I2S_FIFOINTENCLR_TXERR(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENCLR_TXERR_SHIFT)) & I2S_FIFOINTENCLR_TXERR_MASK)
#define I2S_FIFOINTENCLR_RXERR_MASK              (0x2U)
#define I2S_FIFOINTENCLR_RXERR_SHIFT             (1U)
#define I2S_FIFOINTENCLR_RXERR(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENCLR_RXERR_SHIFT)) & I2S_FIFOINTENCLR_RXERR_MASK)
#define I2S_FIFOINTENCLR_TXLVL_MASK              (0x4U)
#define I2S_FIFOINTENCLR_TXLVL_SHIFT             (2U)
#define I2S_FIFOINTENCLR_TXLVL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENCLR_TXLVL_SHIFT)) & I2S_FIFOINTENCLR_TXLVL_MASK)
#define I2S_FIFOINTENCLR_RXLVL_MASK              (0x8U)
#define I2S_FIFOINTENCLR_RXLVL_SHIFT             (3U)
#define I2S_FIFOINTENCLR_RXLVL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENCLR_RXLVL_SHIFT)) & I2S_FIFOINTENCLR_RXLVL_MASK)

/*! @name FIFOINTSTAT - FIFO interrupt status register. */
#define I2S_FIFOINTSTAT_TXERR_MASK               (0x1U)
#define I2S_FIFOINTSTAT_TXERR_SHIFT              (0U)
#define I2S_FIFOINTSTAT_TXERR(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_TXERR_SHIFT)) & I2S_FIFOINTSTAT_TXERR_MASK)
#define I2S_FIFOINTSTAT_RXERR_MASK               (0x2U)
#define I2S_FIFOINTSTAT_RXERR_SHIFT              (1U)
#define I2S_FIFOINTSTAT_RXERR(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_RXERR_SHIFT)) & I2S_FIFOINTSTAT_RXERR_MASK)
#define I2S_FIFOINTSTAT_TXLVL_MASK               (0x4U)
#define I2S_FIFOINTSTAT_TXLVL_SHIFT              (2U)
#define I2S_FIFOINTSTAT_TXLVL(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_TXLVL_SHIFT)) & I2S_FIFOINTSTAT_TXLVL_MASK)
#define I2S_FIFOINTSTAT_RXLVL_MASK               (0x8U)
#define I2S_FIFOINTSTAT_RXLVL_SHIFT              (3U)
#define I2S_FIFOINTSTAT_RXLVL(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_RXLVL_SHIFT)) & I2S_FIFOINTSTAT_RXLVL_MASK)
#define I2S_FIFOINTSTAT_PERINT_MASK              (0x10U)
#define I2S_FIFOINTSTAT_PERINT_SHIFT             (4U)
#define I2S_FIFOINTSTAT_PERINT(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_PERINT_SHIFT)) & I2S_FIFOINTSTAT_PERINT_MASK)

/*! @name FIFOWR - FIFO write data. */
#define I2S_FIFOWR_TXDATA_MASK                   (0xFFFFFFFFU)
#define I2S_FIFOWR_TXDATA_SHIFT                  (0U)
#define I2S_FIFOWR_TXDATA(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_FIFOWR_TXDATA_SHIFT)) & I2S_FIFOWR_TXDATA_MASK)

/*! @name FIFOWR48H - FIFO write data for upper data bits. May only be used if the I2S is configured for 2x 24-bit data and not using DMA. */
#define I2S_FIFOWR48H_TXDATA_MASK                (0xFFFFFFU)
#define I2S_FIFOWR48H_TXDATA_SHIFT               (0U)
#define I2S_FIFOWR48H_TXDATA(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFOWR48H_TXDATA_SHIFT)) & I2S_FIFOWR48H_TXDATA_MASK)

/*! @name FIFORD - FIFO read data. */
#define I2S_FIFORD_RXDATA_MASK                   (0xFFFFFFFFU)
#define I2S_FIFORD_RXDATA_SHIFT                  (0U)
#define I2S_FIFORD_RXDATA(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_FIFORD_RXDATA_SHIFT)) & I2S_FIFORD_RXDATA_MASK)

/*! @name FIFORD48H - FIFO read data for upper data bits. May only be used if the I2S is configured for 2x 24-bit data and not using DMA. */
#define I2S_FIFORD48H_RXDATA_MASK                (0xFFFFFFU)
#define I2S_FIFORD48H_RXDATA_SHIFT               (0U)
#define I2S_FIFORD48H_RXDATA(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFORD48H_RXDATA_SHIFT)) & I2S_FIFORD48H_RXDATA_MASK)

/*! @name FIFORDNOPOP - FIFO data read with no FIFO pop. */
#define I2S_FIFORDNOPOP_RXDATA_MASK              (0xFFFFFFFFU)
#define I2S_FIFORDNOPOP_RXDATA_SHIFT             (0U)
#define I2S_FIFORDNOPOP_RXDATA(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFORDNOPOP_RXDATA_SHIFT)) & I2S_FIFORDNOPOP_RXDATA_MASK)

/*! @name FIFORD48HNOPOP - FIFO data read for upper data bits with no FIFO pop. May only be used if the I2S is configured for 2x 24-bit data and not using DMA. */
#define I2S_FIFORD48HNOPOP_RXDATA_MASK           (0xFFFFFFU)
#define I2S_FIFORD48HNOPOP_RXDATA_SHIFT          (0U)
#define I2S_FIFORD48HNOPOP_RXDATA(x)             (((uint32_t)(((uint32_t)(x)) << I2S_FIFORD48HNOPOP_RXDATA_SHIFT)) & I2S_FIFORD48HNOPOP_RXDATA_MASK)

/*! @name ID - I2S Module identification */
#define I2S_ID_Aperture_MASK                     (0xFFU)
#define I2S_ID_Aperture_SHIFT                    (0U)
#define I2S_ID_Aperture(x)                       (((uint32_t)(((uint32_t)(x)) << I2S_ID_Aperture_SHIFT)) & I2S_ID_Aperture_MASK)
#define I2S_ID_Minor_Rev_MASK                    (0xF00U)
#define I2S_ID_Minor_Rev_SHIFT                   (8U)
#define I2S_ID_Minor_Rev(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_ID_Minor_Rev_SHIFT)) & I2S_ID_Minor_Rev_MASK)
#define I2S_ID_Major_Rev_MASK                    (0xF000U)
#define I2S_ID_Major_Rev_SHIFT                   (12U)
#define I2S_ID_Major_Rev(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_ID_Major_Rev_SHIFT)) & I2S_ID_Major_Rev_MASK)
#define I2S_ID_ID_MASK                           (0xFFFF0000U)
#define I2S_ID_ID_SHIFT                          (16U)
#define I2S_ID_ID(x)                             (((uint32_t)(((uint32_t)(x)) << I2S_ID_ID_SHIFT)) & I2S_ID_ID_MASK)


/*!
 * @}
 */ /* end of group I2S_Register_Masks */


/* I2S - Peripheral instance base addresses */
/** Peripheral I2S0 base address */
#define I2S0_BASE                                (0x40097000u)
/** Peripheral I2S0 base pointer */
#define I2S0                                     ((I2S_Type *)I2S0_BASE)
/** Peripheral I2S1 base address */
#define I2S1_BASE                                (0x40098000u)
/** Peripheral I2S1 base pointer */
#define I2S1                                     ((I2S_Type *)I2S1_BASE)
/** Array initializer of I2S peripheral base addresses */
#define I2S_BASE_ADDRS                           { I2S0_BASE, I2S1_BASE }
/** Array initializer of I2S peripheral base pointers */
#define I2S_BASE_PTRS                            { I2S0, I2S1 }
/** Interrupt vectors for the I2S peripheral type */
#define I2S_IRQS                                 { FLEXCOMM6_IRQn, FLEXCOMM7_IRQn }

/*!
 * @}
 */ /* end of group I2S_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- INPUTMUX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup INPUTMUX_Peripheral_Access_Layer INPUTMUX Peripheral Access Layer
 * @{
 */

/** INPUTMUX - Register Layout Typedef */
typedef struct {
  __IO uint32_t SCT0_INMUX[7];                     /**< Trigger select register for DMA channel, array offset: 0x0, array step: 0x4 */
       uint8_t RESERVED_0[164];
  __IO uint32_t PINTSEL[8];                        /**< Pin interrupt select register, array offset: 0xC0, array step: 0x4 */
  __IO uint32_t DMA_ITRIG_INMUX[30];               /**< Trigger select register for DMA channel, array offset: 0xE0, array step: 0x4 */
       uint8_t RESERVED_1[8];
  __IO uint32_t DMA_OTRIG_INMUX[4];                /**< DMA output trigger selection to become DMA trigger, array offset: 0x160, array step: 0x4 */
       uint8_t RESERVED_2[16];
  __IO uint32_t FREQMEAS_REF;                      /**< Selection for frequency measurement reference clock, offset: 0x180 */
  __IO uint32_t FREQMEAS_TARGET;                   /**< Selection for frequency measurement target clock, offset: 0x184 */
} INPUTMUX_Type;

/* ----------------------------------------------------------------------------
   -- INPUTMUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup INPUTMUX_Register_Masks INPUTMUX Register Masks
 * @{
 */

/*! @name SCT0_INMUX - Trigger select register for DMA channel */
#define INPUTMUX_SCT0_INMUX_INP_N_MASK           (0x1FU)
#define INPUTMUX_SCT0_INMUX_INP_N_SHIFT          (0U)
#define INPUTMUX_SCT0_INMUX_INP_N(x)             (((uint32_t)(((uint32_t)(x)) << INPUTMUX_SCT0_INMUX_INP_N_SHIFT)) & INPUTMUX_SCT0_INMUX_INP_N_MASK)

/* The count of INPUTMUX_SCT0_INMUX */
#define INPUTMUX_SCT0_INMUX_COUNT                (7U)

/*! @name PINTSEL - Pin interrupt select register */
#define INPUTMUX_PINTSEL_INTPIN_MASK             (0xFFU)
#define INPUTMUX_PINTSEL_INTPIN_SHIFT            (0U)
#define INPUTMUX_PINTSEL_INTPIN(x)               (((uint32_t)(((uint32_t)(x)) << INPUTMUX_PINTSEL_INTPIN_SHIFT)) & INPUTMUX_PINTSEL_INTPIN_MASK)

/* The count of INPUTMUX_PINTSEL */
#define INPUTMUX_PINTSEL_COUNT                   (8U)

/*! @name DMA_ITRIG_INMUX - Trigger select register for DMA channel */
#define INPUTMUX_DMA_ITRIG_INMUX_INP_MASK        (0x1FU)
#define INPUTMUX_DMA_ITRIG_INMUX_INP_SHIFT       (0U)
#define INPUTMUX_DMA_ITRIG_INMUX_INP(x)          (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA_ITRIG_INMUX_INP_SHIFT)) & INPUTMUX_DMA_ITRIG_INMUX_INP_MASK)

/* The count of INPUTMUX_DMA_ITRIG_INMUX */
#define INPUTMUX_DMA_ITRIG_INMUX_COUNT           (30U)

/*! @name DMA_OTRIG_INMUX - DMA output trigger selection to become DMA trigger */
#define INPUTMUX_DMA_OTRIG_INMUX_INP_MASK        (0x1FU)
#define INPUTMUX_DMA_OTRIG_INMUX_INP_SHIFT       (0U)
#define INPUTMUX_DMA_OTRIG_INMUX_INP(x)          (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA_OTRIG_INMUX_INP_SHIFT)) & INPUTMUX_DMA_OTRIG_INMUX_INP_MASK)

/* The count of INPUTMUX_DMA_OTRIG_INMUX */
#define INPUTMUX_DMA_OTRIG_INMUX_COUNT           (4U)

/*! @name FREQMEAS_REF - Selection for frequency measurement reference clock */
#define INPUTMUX_FREQMEAS_REF_CLKIN_MASK         (0x1FU)
#define INPUTMUX_FREQMEAS_REF_CLKIN_SHIFT        (0U)
#define INPUTMUX_FREQMEAS_REF_CLKIN(x)           (((uint32_t)(((uint32_t)(x)) << INPUTMUX_FREQMEAS_REF_CLKIN_SHIFT)) & INPUTMUX_FREQMEAS_REF_CLKIN_MASK)

/*! @name FREQMEAS_TARGET - Selection for frequency measurement target clock */
#define INPUTMUX_FREQMEAS_TARGET_CLKIN_MASK      (0x1FU)
#define INPUTMUX_FREQMEAS_TARGET_CLKIN_SHIFT     (0U)
#define INPUTMUX_FREQMEAS_TARGET_CLKIN(x)        (((uint32_t)(((uint32_t)(x)) << INPUTMUX_FREQMEAS_TARGET_CLKIN_SHIFT)) & INPUTMUX_FREQMEAS_TARGET_CLKIN_MASK)


/*!
 * @}
 */ /* end of group INPUTMUX_Register_Masks */


/* INPUTMUX - Peripheral instance base addresses */
/** Peripheral INPUTMUX base address */
#define INPUTMUX_BASE                            (0x40005000u)
/** Peripheral INPUTMUX base pointer */
#define INPUTMUX                                 ((INPUTMUX_Type *)INPUTMUX_BASE)
/** Array initializer of INPUTMUX peripheral base addresses */
#define INPUTMUX_BASE_ADDRS                      { INPUTMUX_BASE }
/** Array initializer of INPUTMUX peripheral base pointers */
#define INPUTMUX_BASE_PTRS                       { INPUTMUX }

/*!
 * @}
 */ /* end of group INPUTMUX_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- IOCON Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOCON_Peripheral_Access_Layer IOCON Peripheral Access Layer
 * @{
 */

/** IOCON - Register Layout Typedef */
typedef struct {
  __IO uint32_t PIO[6][32];                        /**< Digital I/O control for port 0 pins PIO0_0..Digital I/O control for port 5 pins PIO5_31, array offset: 0x0, array step: index*0x80, index2*0x4 */
} IOCON_Type;

/* ----------------------------------------------------------------------------
   -- IOCON Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOCON_Register_Masks IOCON Register Masks
 * @{
 */

/*! @name PIO - Digital I/O control for port 0 pins PIO0_0..Digital I/O control for port 5 pins PIO5_31 */
#define IOCON_PIO_FUNC_MASK                      (0xFU)
#define IOCON_PIO_FUNC_SHIFT                     (0U)
#define IOCON_PIO_FUNC(x)                        (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_FUNC_SHIFT)) & IOCON_PIO_FUNC_MASK)
#define IOCON_PIO_MODE_MASK                      (0x30U)
#define IOCON_PIO_MODE_SHIFT                     (4U)
#define IOCON_PIO_MODE(x)                        (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_MODE_SHIFT)) & IOCON_PIO_MODE_MASK)
#define IOCON_PIO_I2CSLEW_MASK                   (0x40U)
#define IOCON_PIO_I2CSLEW_SHIFT                  (6U)
#define IOCON_PIO_I2CSLEW(x)                     (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_I2CSLEW_SHIFT)) & IOCON_PIO_I2CSLEW_MASK)
#define IOCON_PIO_INVERT_MASK                    (0x80U)
#define IOCON_PIO_INVERT_SHIFT                   (7U)
#define IOCON_PIO_INVERT(x)                      (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_INVERT_SHIFT)) & IOCON_PIO_INVERT_MASK)
#define IOCON_PIO_DIGIMODE_MASK                  (0x100U)
#define IOCON_PIO_DIGIMODE_SHIFT                 (8U)
#define IOCON_PIO_DIGIMODE(x)                    (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_DIGIMODE_SHIFT)) & IOCON_PIO_DIGIMODE_MASK)
#define IOCON_PIO_FILTEROFF_MASK                 (0x200U)
#define IOCON_PIO_FILTEROFF_SHIFT                (9U)
#define IOCON_PIO_FILTEROFF(x)                   (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_FILTEROFF_SHIFT)) & IOCON_PIO_FILTEROFF_MASK)
#define IOCON_PIO_I2CDRIVE_MASK                  (0x400U)
#define IOCON_PIO_I2CDRIVE_SHIFT                 (10U)
#define IOCON_PIO_I2CDRIVE(x)                    (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_I2CDRIVE_SHIFT)) & IOCON_PIO_I2CDRIVE_MASK)
#define IOCON_PIO_SLEW_MASK                      (0x400U)
#define IOCON_PIO_SLEW_SHIFT                     (10U)
#define IOCON_PIO_SLEW(x)                        (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_SLEW_SHIFT)) & IOCON_PIO_SLEW_MASK)
#define IOCON_PIO_OD_MASK                        (0x800U)
#define IOCON_PIO_OD_SHIFT                       (11U)
#define IOCON_PIO_OD(x)                          (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_OD_SHIFT)) & IOCON_PIO_OD_MASK)
#define IOCON_PIO_I2CFILTER_MASK                 (0x800U)
#define IOCON_PIO_I2CFILTER_SHIFT                (11U)
#define IOCON_PIO_I2CFILTER(x)                   (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_I2CFILTER_SHIFT)) & IOCON_PIO_I2CFILTER_MASK)

/* The count of IOCON_PIO */
#define IOCON_PIO_COUNT                          (6U)

/* The count of IOCON_PIO */
#define IOCON_PIO_COUNT2                         (32U)


/*!
 * @}
 */ /* end of group IOCON_Register_Masks */


/* IOCON - Peripheral instance base addresses */
/** Peripheral IOCON base address */
#define IOCON_BASE                               (0x40001000u)
/** Peripheral IOCON base pointer */
#define IOCON                                    ((IOCON_Type *)IOCON_BASE)
/** Array initializer of IOCON peripheral base addresses */
#define IOCON_BASE_ADDRS                         { IOCON_BASE }
/** Array initializer of IOCON peripheral base pointers */
#define IOCON_BASE_PTRS                          { IOCON }

/*!
 * @}
 */ /* end of group IOCON_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- LCD Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LCD_Peripheral_Access_Layer LCD Peripheral Access Layer
 * @{
 */

/** LCD - Register Layout Typedef */
typedef struct {
  __IO uint32_t TIMH;                              /**< Horizontal Timing Control register, offset: 0x0 */
  __IO uint32_t TIMV;                              /**< Vertical Timing Control register, offset: 0x4 */
  __IO uint32_t POL;                               /**< Clock and Signal Polarity Control register, offset: 0x8 */
  __IO uint32_t LE;                                /**< Line End Control register, offset: 0xC */
  __IO uint32_t UPBASE;                            /**< Upper Panel Frame Base Address register, offset: 0x10 */
  __IO uint32_t LPBASE;                            /**< Lower Panel Frame Base Address register, offset: 0x14 */
  __IO uint32_t CTRL;                              /**< LCD Control register, offset: 0x18 */
  __IO uint32_t INTMSK;                            /**< Interrupt Mask register, offset: 0x1C */
  __I  uint32_t INTRAW;                            /**< Raw Interrupt Status register, offset: 0x20 */
  __I  uint32_t INTSTAT;                           /**< Masked Interrupt Status register, offset: 0x24 */
  __IO uint32_t INTCLR;                            /**< Interrupt Clear register, offset: 0x28 */
  __I  uint32_t UPCURR;                            /**< Upper Panel Current Address Value register, offset: 0x2C */
  __I  uint32_t LPCURR;                            /**< Lower Panel Current Address Value register, offset: 0x30 */
       uint8_t RESERVED_0[460];
  __IO uint32_t PAL[128];                          /**< 256x16-bit Color Palette registers, array offset: 0x200, array step: 0x4 */
       uint8_t RESERVED_1[1024];
  __IO uint32_t CRSR_IMG[256];                     /**< Cursor Image registers, array offset: 0x800, array step: 0x4 */
  __IO uint32_t CRSR_CTRL;                         /**< Cursor Control register, offset: 0xC00 */
  __IO uint32_t CRSR_CFG;                          /**< Cursor Configuration register, offset: 0xC04 */
  __IO uint32_t CRSR_PAL0;                         /**< Cursor Palette register 0, offset: 0xC08 */
  __IO uint32_t CRSR_PAL1;                         /**< Cursor Palette register 1, offset: 0xC0C */
  __IO uint32_t CRSR_XY;                           /**< Cursor XY Position register, offset: 0xC10 */
  __IO uint32_t CRSR_CLIP;                         /**< Cursor Clip Position register, offset: 0xC14 */
       uint8_t RESERVED_2[8];
  __IO uint32_t CRSR_INTMSK;                       /**< Cursor Interrupt Mask register, offset: 0xC20 */
  __O  uint32_t CRSR_INTCLR;                       /**< Cursor Interrupt Clear register, offset: 0xC24 */
  __I  uint32_t CRSR_INTRAW;                       /**< Cursor Raw Interrupt Status register, offset: 0xC28 */
  __I  uint32_t CRSR_INTSTAT;                      /**< Cursor Masked Interrupt Status register, offset: 0xC2C */
} LCD_Type;

/* ----------------------------------------------------------------------------
   -- LCD Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LCD_Register_Masks LCD Register Masks
 * @{
 */

/*! @name TIMH - Horizontal Timing Control register */
#define LCD_TIMH_PPL_MASK                        (0xFCU)
#define LCD_TIMH_PPL_SHIFT                       (2U)
#define LCD_TIMH_PPL(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_TIMH_PPL_SHIFT)) & LCD_TIMH_PPL_MASK)
#define LCD_TIMH_HSW_MASK                        (0xFF00U)
#define LCD_TIMH_HSW_SHIFT                       (8U)
#define LCD_TIMH_HSW(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_TIMH_HSW_SHIFT)) & LCD_TIMH_HSW_MASK)
#define LCD_TIMH_HFP_MASK                        (0xFF0000U)
#define LCD_TIMH_HFP_SHIFT                       (16U)
#define LCD_TIMH_HFP(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_TIMH_HFP_SHIFT)) & LCD_TIMH_HFP_MASK)
#define LCD_TIMH_HBP_MASK                        (0xFF000000U)
#define LCD_TIMH_HBP_SHIFT                       (24U)
#define LCD_TIMH_HBP(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_TIMH_HBP_SHIFT)) & LCD_TIMH_HBP_MASK)

/*! @name TIMV - Vertical Timing Control register */
#define LCD_TIMV_LPP_MASK                        (0x3FFU)
#define LCD_TIMV_LPP_SHIFT                       (0U)
#define LCD_TIMV_LPP(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_TIMV_LPP_SHIFT)) & LCD_TIMV_LPP_MASK)
#define LCD_TIMV_VSW_MASK                        (0xFC00U)
#define LCD_TIMV_VSW_SHIFT                       (10U)
#define LCD_TIMV_VSW(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_TIMV_VSW_SHIFT)) & LCD_TIMV_VSW_MASK)
#define LCD_TIMV_VFP_MASK                        (0xFF0000U)
#define LCD_TIMV_VFP_SHIFT                       (16U)
#define LCD_TIMV_VFP(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_TIMV_VFP_SHIFT)) & LCD_TIMV_VFP_MASK)
#define LCD_TIMV_VBP_MASK                        (0xFF000000U)
#define LCD_TIMV_VBP_SHIFT                       (24U)
#define LCD_TIMV_VBP(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_TIMV_VBP_SHIFT)) & LCD_TIMV_VBP_MASK)

/*! @name POL - Clock and Signal Polarity Control register */
#define LCD_POL_PCD_LO_MASK                      (0x1FU)
#define LCD_POL_PCD_LO_SHIFT                     (0U)
#define LCD_POL_PCD_LO(x)                        (((uint32_t)(((uint32_t)(x)) << LCD_POL_PCD_LO_SHIFT)) & LCD_POL_PCD_LO_MASK)
#define LCD_POL_ACB_MASK                         (0x7C0U)
#define LCD_POL_ACB_SHIFT                        (6U)
#define LCD_POL_ACB(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_POL_ACB_SHIFT)) & LCD_POL_ACB_MASK)
#define LCD_POL_IVS_MASK                         (0x800U)
#define LCD_POL_IVS_SHIFT                        (11U)
#define LCD_POL_IVS(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_POL_IVS_SHIFT)) & LCD_POL_IVS_MASK)
#define LCD_POL_IHS_MASK                         (0x1000U)
#define LCD_POL_IHS_SHIFT                        (12U)
#define LCD_POL_IHS(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_POL_IHS_SHIFT)) & LCD_POL_IHS_MASK)
#define LCD_POL_IPC_MASK                         (0x2000U)
#define LCD_POL_IPC_SHIFT                        (13U)
#define LCD_POL_IPC(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_POL_IPC_SHIFT)) & LCD_POL_IPC_MASK)
#define LCD_POL_IOE_MASK                         (0x4000U)
#define LCD_POL_IOE_SHIFT                        (14U)
#define LCD_POL_IOE(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_POL_IOE_SHIFT)) & LCD_POL_IOE_MASK)
#define LCD_POL_CPL_MASK                         (0x3FF0000U)
#define LCD_POL_CPL_SHIFT                        (16U)
#define LCD_POL_CPL(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_POL_CPL_SHIFT)) & LCD_POL_CPL_MASK)
#define LCD_POL_BCD_MASK                         (0x4000000U)
#define LCD_POL_BCD_SHIFT                        (26U)
#define LCD_POL_BCD(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_POL_BCD_SHIFT)) & LCD_POL_BCD_MASK)
#define LCD_POL_PCD_HI_MASK                      (0xF8000000U)
#define LCD_POL_PCD_HI_SHIFT                     (27U)
#define LCD_POL_PCD_HI(x)                        (((uint32_t)(((uint32_t)(x)) << LCD_POL_PCD_HI_SHIFT)) & LCD_POL_PCD_HI_MASK)

/*! @name LE - Line End Control register */
#define LCD_LE_LED_MASK                          (0x7FU)
#define LCD_LE_LED_SHIFT                         (0U)
#define LCD_LE_LED(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_LE_LED_SHIFT)) & LCD_LE_LED_MASK)
#define LCD_LE_LEE_MASK                          (0x10000U)
#define LCD_LE_LEE_SHIFT                         (16U)
#define LCD_LE_LEE(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_LE_LEE_SHIFT)) & LCD_LE_LEE_MASK)

/*! @name UPBASE - Upper Panel Frame Base Address register */
#define LCD_UPBASE_LCDUPBASE_MASK                (0xFFFFFFF8U)
#define LCD_UPBASE_LCDUPBASE_SHIFT               (3U)
#define LCD_UPBASE_LCDUPBASE(x)                  (((uint32_t)(((uint32_t)(x)) << LCD_UPBASE_LCDUPBASE_SHIFT)) & LCD_UPBASE_LCDUPBASE_MASK)

/*! @name LPBASE - Lower Panel Frame Base Address register */
#define LCD_LPBASE_LCDLPBASE_MASK                (0xFFFFFFF8U)
#define LCD_LPBASE_LCDLPBASE_SHIFT               (3U)
#define LCD_LPBASE_LCDLPBASE(x)                  (((uint32_t)(((uint32_t)(x)) << LCD_LPBASE_LCDLPBASE_SHIFT)) & LCD_LPBASE_LCDLPBASE_MASK)

/*! @name CTRL - LCD Control register */
#define LCD_CTRL_LCDEN_MASK                      (0x1U)
#define LCD_CTRL_LCDEN_SHIFT                     (0U)
#define LCD_CTRL_LCDEN(x)                        (((uint32_t)(((uint32_t)(x)) << LCD_CTRL_LCDEN_SHIFT)) & LCD_CTRL_LCDEN_MASK)
#define LCD_CTRL_LCDBPP_MASK                     (0xEU)
#define LCD_CTRL_LCDBPP_SHIFT                    (1U)
#define LCD_CTRL_LCDBPP(x)                       (((uint32_t)(((uint32_t)(x)) << LCD_CTRL_LCDBPP_SHIFT)) & LCD_CTRL_LCDBPP_MASK)
#define LCD_CTRL_LCDBW_MASK                      (0x10U)
#define LCD_CTRL_LCDBW_SHIFT                     (4U)
#define LCD_CTRL_LCDBW(x)                        (((uint32_t)(((uint32_t)(x)) << LCD_CTRL_LCDBW_SHIFT)) & LCD_CTRL_LCDBW_MASK)
#define LCD_CTRL_LCDTFT_MASK                     (0x20U)
#define LCD_CTRL_LCDTFT_SHIFT                    (5U)
#define LCD_CTRL_LCDTFT(x)                       (((uint32_t)(((uint32_t)(x)) << LCD_CTRL_LCDTFT_SHIFT)) & LCD_CTRL_LCDTFT_MASK)
#define LCD_CTRL_LCDMONO8_MASK                   (0x40U)
#define LCD_CTRL_LCDMONO8_SHIFT                  (6U)
#define LCD_CTRL_LCDMONO8(x)                     (((uint32_t)(((uint32_t)(x)) << LCD_CTRL_LCDMONO8_SHIFT)) & LCD_CTRL_LCDMONO8_MASK)
#define LCD_CTRL_LCDDUAL_MASK                    (0x80U)
#define LCD_CTRL_LCDDUAL_SHIFT                   (7U)
#define LCD_CTRL_LCDDUAL(x)                      (((uint32_t)(((uint32_t)(x)) << LCD_CTRL_LCDDUAL_SHIFT)) & LCD_CTRL_LCDDUAL_MASK)
#define LCD_CTRL_BGR_MASK                        (0x100U)
#define LCD_CTRL_BGR_SHIFT                       (8U)
#define LCD_CTRL_BGR(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_CTRL_BGR_SHIFT)) & LCD_CTRL_BGR_MASK)
#define LCD_CTRL_BEBO_MASK                       (0x200U)
#define LCD_CTRL_BEBO_SHIFT                      (9U)
#define LCD_CTRL_BEBO(x)                         (((uint32_t)(((uint32_t)(x)) << LCD_CTRL_BEBO_SHIFT)) & LCD_CTRL_BEBO_MASK)
#define LCD_CTRL_BEPO_MASK                       (0x400U)
#define LCD_CTRL_BEPO_SHIFT                      (10U)
#define LCD_CTRL_BEPO(x)                         (((uint32_t)(((uint32_t)(x)) << LCD_CTRL_BEPO_SHIFT)) & LCD_CTRL_BEPO_MASK)
#define LCD_CTRL_LCDPWR_MASK                     (0x800U)
#define LCD_CTRL_LCDPWR_SHIFT                    (11U)
#define LCD_CTRL_LCDPWR(x)                       (((uint32_t)(((uint32_t)(x)) << LCD_CTRL_LCDPWR_SHIFT)) & LCD_CTRL_LCDPWR_MASK)
#define LCD_CTRL_LCDVCOMP_MASK                   (0x3000U)
#define LCD_CTRL_LCDVCOMP_SHIFT                  (12U)
#define LCD_CTRL_LCDVCOMP(x)                     (((uint32_t)(((uint32_t)(x)) << LCD_CTRL_LCDVCOMP_SHIFT)) & LCD_CTRL_LCDVCOMP_MASK)
#define LCD_CTRL_WATERMARK_MASK                  (0x10000U)
#define LCD_CTRL_WATERMARK_SHIFT                 (16U)
#define LCD_CTRL_WATERMARK(x)                    (((uint32_t)(((uint32_t)(x)) << LCD_CTRL_WATERMARK_SHIFT)) & LCD_CTRL_WATERMARK_MASK)

/*! @name INTMSK - Interrupt Mask register */
#define LCD_INTMSK_FUFIM_MASK                    (0x2U)
#define LCD_INTMSK_FUFIM_SHIFT                   (1U)
#define LCD_INTMSK_FUFIM(x)                      (((uint32_t)(((uint32_t)(x)) << LCD_INTMSK_FUFIM_SHIFT)) & LCD_INTMSK_FUFIM_MASK)
#define LCD_INTMSK_LNBUIM_MASK                   (0x4U)
#define LCD_INTMSK_LNBUIM_SHIFT                  (2U)
#define LCD_INTMSK_LNBUIM(x)                     (((uint32_t)(((uint32_t)(x)) << LCD_INTMSK_LNBUIM_SHIFT)) & LCD_INTMSK_LNBUIM_MASK)
#define LCD_INTMSK_VCOMPIM_MASK                  (0x8U)
#define LCD_INTMSK_VCOMPIM_SHIFT                 (3U)
#define LCD_INTMSK_VCOMPIM(x)                    (((uint32_t)(((uint32_t)(x)) << LCD_INTMSK_VCOMPIM_SHIFT)) & LCD_INTMSK_VCOMPIM_MASK)
#define LCD_INTMSK_BERIM_MASK                    (0x10U)
#define LCD_INTMSK_BERIM_SHIFT                   (4U)
#define LCD_INTMSK_BERIM(x)                      (((uint32_t)(((uint32_t)(x)) << LCD_INTMSK_BERIM_SHIFT)) & LCD_INTMSK_BERIM_MASK)

/*! @name INTRAW - Raw Interrupt Status register */
#define LCD_INTRAW_FUFRIS_MASK                   (0x2U)
#define LCD_INTRAW_FUFRIS_SHIFT                  (1U)
#define LCD_INTRAW_FUFRIS(x)                     (((uint32_t)(((uint32_t)(x)) << LCD_INTRAW_FUFRIS_SHIFT)) & LCD_INTRAW_FUFRIS_MASK)
#define LCD_INTRAW_LNBURIS_MASK                  (0x4U)
#define LCD_INTRAW_LNBURIS_SHIFT                 (2U)
#define LCD_INTRAW_LNBURIS(x)                    (((uint32_t)(((uint32_t)(x)) << LCD_INTRAW_LNBURIS_SHIFT)) & LCD_INTRAW_LNBURIS_MASK)
#define LCD_INTRAW_VCOMPRIS_MASK                 (0x8U)
#define LCD_INTRAW_VCOMPRIS_SHIFT                (3U)
#define LCD_INTRAW_VCOMPRIS(x)                   (((uint32_t)(((uint32_t)(x)) << LCD_INTRAW_VCOMPRIS_SHIFT)) & LCD_INTRAW_VCOMPRIS_MASK)
#define LCD_INTRAW_BERRAW_MASK                   (0x10U)
#define LCD_INTRAW_BERRAW_SHIFT                  (4U)
#define LCD_INTRAW_BERRAW(x)                     (((uint32_t)(((uint32_t)(x)) << LCD_INTRAW_BERRAW_SHIFT)) & LCD_INTRAW_BERRAW_MASK)

/*! @name INTSTAT - Masked Interrupt Status register */
#define LCD_INTSTAT_FUFMIS_MASK                  (0x2U)
#define LCD_INTSTAT_FUFMIS_SHIFT                 (1U)
#define LCD_INTSTAT_FUFMIS(x)                    (((uint32_t)(((uint32_t)(x)) << LCD_INTSTAT_FUFMIS_SHIFT)) & LCD_INTSTAT_FUFMIS_MASK)
#define LCD_INTSTAT_LNBUMIS_MASK                 (0x4U)
#define LCD_INTSTAT_LNBUMIS_SHIFT                (2U)
#define LCD_INTSTAT_LNBUMIS(x)                   (((uint32_t)(((uint32_t)(x)) << LCD_INTSTAT_LNBUMIS_SHIFT)) & LCD_INTSTAT_LNBUMIS_MASK)
#define LCD_INTSTAT_VCOMPMIS_MASK                (0x8U)
#define LCD_INTSTAT_VCOMPMIS_SHIFT               (3U)
#define LCD_INTSTAT_VCOMPMIS(x)                  (((uint32_t)(((uint32_t)(x)) << LCD_INTSTAT_VCOMPMIS_SHIFT)) & LCD_INTSTAT_VCOMPMIS_MASK)
#define LCD_INTSTAT_BERMIS_MASK                  (0x10U)
#define LCD_INTSTAT_BERMIS_SHIFT                 (4U)
#define LCD_INTSTAT_BERMIS(x)                    (((uint32_t)(((uint32_t)(x)) << LCD_INTSTAT_BERMIS_SHIFT)) & LCD_INTSTAT_BERMIS_MASK)

/*! @name INTCLR - Interrupt Clear register */
#define LCD_INTCLR_FUFIC_MASK                    (0x2U)
#define LCD_INTCLR_FUFIC_SHIFT                   (1U)
#define LCD_INTCLR_FUFIC(x)                      (((uint32_t)(((uint32_t)(x)) << LCD_INTCLR_FUFIC_SHIFT)) & LCD_INTCLR_FUFIC_MASK)
#define LCD_INTCLR_LNBUIC_MASK                   (0x4U)
#define LCD_INTCLR_LNBUIC_SHIFT                  (2U)
#define LCD_INTCLR_LNBUIC(x)                     (((uint32_t)(((uint32_t)(x)) << LCD_INTCLR_LNBUIC_SHIFT)) & LCD_INTCLR_LNBUIC_MASK)
#define LCD_INTCLR_VCOMPIC_MASK                  (0x8U)
#define LCD_INTCLR_VCOMPIC_SHIFT                 (3U)
#define LCD_INTCLR_VCOMPIC(x)                    (((uint32_t)(((uint32_t)(x)) << LCD_INTCLR_VCOMPIC_SHIFT)) & LCD_INTCLR_VCOMPIC_MASK)
#define LCD_INTCLR_BERIC_MASK                    (0x10U)
#define LCD_INTCLR_BERIC_SHIFT                   (4U)
#define LCD_INTCLR_BERIC(x)                      (((uint32_t)(((uint32_t)(x)) << LCD_INTCLR_BERIC_SHIFT)) & LCD_INTCLR_BERIC_MASK)

/*! @name UPCURR - Upper Panel Current Address Value register */
#define LCD_UPCURR_LCDUPCURR_MASK                (0xFFFFFFFFU)
#define LCD_UPCURR_LCDUPCURR_SHIFT               (0U)
#define LCD_UPCURR_LCDUPCURR(x)                  (((uint32_t)(((uint32_t)(x)) << LCD_UPCURR_LCDUPCURR_SHIFT)) & LCD_UPCURR_LCDUPCURR_MASK)

/*! @name LPCURR - Lower Panel Current Address Value register */
#define LCD_LPCURR_LCDLPCURR_MASK                (0xFFFFFFFFU)
#define LCD_LPCURR_LCDLPCURR_SHIFT               (0U)
#define LCD_LPCURR_LCDLPCURR(x)                  (((uint32_t)(((uint32_t)(x)) << LCD_LPCURR_LCDLPCURR_SHIFT)) & LCD_LPCURR_LCDLPCURR_MASK)

/*! @name PAL - 256x16-bit Color Palette registers */
#define LCD_PAL_R04_0_MASK                       (0x1FU)
#define LCD_PAL_R04_0_SHIFT                      (0U)
#define LCD_PAL_R04_0(x)                         (((uint32_t)(((uint32_t)(x)) << LCD_PAL_R04_0_SHIFT)) & LCD_PAL_R04_0_MASK)
#define LCD_PAL_G04_0_MASK                       (0x3E0U)
#define LCD_PAL_G04_0_SHIFT                      (5U)
#define LCD_PAL_G04_0(x)                         (((uint32_t)(((uint32_t)(x)) << LCD_PAL_G04_0_SHIFT)) & LCD_PAL_G04_0_MASK)
#define LCD_PAL_B04_0_MASK                       (0x7C00U)
#define LCD_PAL_B04_0_SHIFT                      (10U)
#define LCD_PAL_B04_0(x)                         (((uint32_t)(((uint32_t)(x)) << LCD_PAL_B04_0_SHIFT)) & LCD_PAL_B04_0_MASK)
#define LCD_PAL_I0_MASK                          (0x8000U)
#define LCD_PAL_I0_SHIFT                         (15U)
#define LCD_PAL_I0(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_PAL_I0_SHIFT)) & LCD_PAL_I0_MASK)
#define LCD_PAL_R14_0_MASK                       (0x1F0000U)
#define LCD_PAL_R14_0_SHIFT                      (16U)
#define LCD_PAL_R14_0(x)                         (((uint32_t)(((uint32_t)(x)) << LCD_PAL_R14_0_SHIFT)) & LCD_PAL_R14_0_MASK)
#define LCD_PAL_G14_0_MASK                       (0x3E00000U)
#define LCD_PAL_G14_0_SHIFT                      (21U)
#define LCD_PAL_G14_0(x)                         (((uint32_t)(((uint32_t)(x)) << LCD_PAL_G14_0_SHIFT)) & LCD_PAL_G14_0_MASK)
#define LCD_PAL_B14_0_MASK                       (0x7C000000U)
#define LCD_PAL_B14_0_SHIFT                      (26U)
#define LCD_PAL_B14_0(x)                         (((uint32_t)(((uint32_t)(x)) << LCD_PAL_B14_0_SHIFT)) & LCD_PAL_B14_0_MASK)
#define LCD_PAL_I1_MASK                          (0x80000000U)
#define LCD_PAL_I1_SHIFT                         (31U)
#define LCD_PAL_I1(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_PAL_I1_SHIFT)) & LCD_PAL_I1_MASK)

/* The count of LCD_PAL */
#define LCD_PAL_COUNT                            (128U)

/*! @name CRSR_IMG - Cursor Image registers */
#define LCD_CRSR_IMG_CRSR_IMG_MASK               (0xFFFFFFFFU)
#define LCD_CRSR_IMG_CRSR_IMG_SHIFT              (0U)
#define LCD_CRSR_IMG_CRSR_IMG(x)                 (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_IMG_CRSR_IMG_SHIFT)) & LCD_CRSR_IMG_CRSR_IMG_MASK)

/* The count of LCD_CRSR_IMG */
#define LCD_CRSR_IMG_COUNT                       (256U)

/*! @name CRSR_CTRL - Cursor Control register */
#define LCD_CRSR_CTRL_CRSRON_MASK                (0x1U)
#define LCD_CRSR_CTRL_CRSRON_SHIFT               (0U)
#define LCD_CRSR_CTRL_CRSRON(x)                  (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_CTRL_CRSRON_SHIFT)) & LCD_CRSR_CTRL_CRSRON_MASK)
#define LCD_CRSR_CTRL_CRSRNUM1_0_MASK            (0x30U)
#define LCD_CRSR_CTRL_CRSRNUM1_0_SHIFT           (4U)
#define LCD_CRSR_CTRL_CRSRNUM1_0(x)              (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_CTRL_CRSRNUM1_0_SHIFT)) & LCD_CRSR_CTRL_CRSRNUM1_0_MASK)

/*! @name CRSR_CFG - Cursor Configuration register */
#define LCD_CRSR_CFG_CRSRSIZE_MASK               (0x1U)
#define LCD_CRSR_CFG_CRSRSIZE_SHIFT              (0U)
#define LCD_CRSR_CFG_CRSRSIZE(x)                 (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_CFG_CRSRSIZE_SHIFT)) & LCD_CRSR_CFG_CRSRSIZE_MASK)
#define LCD_CRSR_CFG_FRAMESYNC_MASK              (0x2U)
#define LCD_CRSR_CFG_FRAMESYNC_SHIFT             (1U)
#define LCD_CRSR_CFG_FRAMESYNC(x)                (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_CFG_FRAMESYNC_SHIFT)) & LCD_CRSR_CFG_FRAMESYNC_MASK)

/*! @name CRSR_PAL0 - Cursor Palette register 0 */
#define LCD_CRSR_PAL0_RED_MASK                   (0xFFU)
#define LCD_CRSR_PAL0_RED_SHIFT                  (0U)
#define LCD_CRSR_PAL0_RED(x)                     (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_PAL0_RED_SHIFT)) & LCD_CRSR_PAL0_RED_MASK)
#define LCD_CRSR_PAL0_GREEN_MASK                 (0xFF00U)
#define LCD_CRSR_PAL0_GREEN_SHIFT                (8U)
#define LCD_CRSR_PAL0_GREEN(x)                   (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_PAL0_GREEN_SHIFT)) & LCD_CRSR_PAL0_GREEN_MASK)
#define LCD_CRSR_PAL0_BLUE_MASK                  (0xFF0000U)
#define LCD_CRSR_PAL0_BLUE_SHIFT                 (16U)
#define LCD_CRSR_PAL0_BLUE(x)                    (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_PAL0_BLUE_SHIFT)) & LCD_CRSR_PAL0_BLUE_MASK)

/*! @name CRSR_PAL1 - Cursor Palette register 1 */
#define LCD_CRSR_PAL1_RED_MASK                   (0xFFU)
#define LCD_CRSR_PAL1_RED_SHIFT                  (0U)
#define LCD_CRSR_PAL1_RED(x)                     (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_PAL1_RED_SHIFT)) & LCD_CRSR_PAL1_RED_MASK)
#define LCD_CRSR_PAL1_GREEN_MASK                 (0xFF00U)
#define LCD_CRSR_PAL1_GREEN_SHIFT                (8U)
#define LCD_CRSR_PAL1_GREEN(x)                   (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_PAL1_GREEN_SHIFT)) & LCD_CRSR_PAL1_GREEN_MASK)
#define LCD_CRSR_PAL1_BLUE_MASK                  (0xFF0000U)
#define LCD_CRSR_PAL1_BLUE_SHIFT                 (16U)
#define LCD_CRSR_PAL1_BLUE(x)                    (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_PAL1_BLUE_SHIFT)) & LCD_CRSR_PAL1_BLUE_MASK)

/*! @name CRSR_XY - Cursor XY Position register */
#define LCD_CRSR_XY_CRSRX_MASK                   (0x3FFU)
#define LCD_CRSR_XY_CRSRX_SHIFT                  (0U)
#define LCD_CRSR_XY_CRSRX(x)                     (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_XY_CRSRX_SHIFT)) & LCD_CRSR_XY_CRSRX_MASK)
#define LCD_CRSR_XY_CRSRY_MASK                   (0x3FF0000U)
#define LCD_CRSR_XY_CRSRY_SHIFT                  (16U)
#define LCD_CRSR_XY_CRSRY(x)                     (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_XY_CRSRY_SHIFT)) & LCD_CRSR_XY_CRSRY_MASK)

/*! @name CRSR_CLIP - Cursor Clip Position register */
#define LCD_CRSR_CLIP_CRSRCLIPX_MASK             (0x3FU)
#define LCD_CRSR_CLIP_CRSRCLIPX_SHIFT            (0U)
#define LCD_CRSR_CLIP_CRSRCLIPX(x)               (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_CLIP_CRSRCLIPX_SHIFT)) & LCD_CRSR_CLIP_CRSRCLIPX_MASK)
#define LCD_CRSR_CLIP_CRSRCLIPY_MASK             (0x3F00U)
#define LCD_CRSR_CLIP_CRSRCLIPY_SHIFT            (8U)
#define LCD_CRSR_CLIP_CRSRCLIPY(x)               (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_CLIP_CRSRCLIPY_SHIFT)) & LCD_CRSR_CLIP_CRSRCLIPY_MASK)

/*! @name CRSR_INTMSK - Cursor Interrupt Mask register */
#define LCD_CRSR_INTMSK_CRSRIM_MASK              (0x1U)
#define LCD_CRSR_INTMSK_CRSRIM_SHIFT             (0U)
#define LCD_CRSR_INTMSK_CRSRIM(x)                (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_INTMSK_CRSRIM_SHIFT)) & LCD_CRSR_INTMSK_CRSRIM_MASK)

/*! @name CRSR_INTCLR - Cursor Interrupt Clear register */
#define LCD_CRSR_INTCLR_CRSRIC_MASK              (0x1U)
#define LCD_CRSR_INTCLR_CRSRIC_SHIFT             (0U)
#define LCD_CRSR_INTCLR_CRSRIC(x)                (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_INTCLR_CRSRIC_SHIFT)) & LCD_CRSR_INTCLR_CRSRIC_MASK)

/*! @name CRSR_INTRAW - Cursor Raw Interrupt Status register */
#define LCD_CRSR_INTRAW_CRSRRIS_MASK             (0x1U)
#define LCD_CRSR_INTRAW_CRSRRIS_SHIFT            (0U)
#define LCD_CRSR_INTRAW_CRSRRIS(x)               (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_INTRAW_CRSRRIS_SHIFT)) & LCD_CRSR_INTRAW_CRSRRIS_MASK)

/*! @name CRSR_INTSTAT - Cursor Masked Interrupt Status register */
#define LCD_CRSR_INTSTAT_CRSRMIS_MASK            (0x1U)
#define LCD_CRSR_INTSTAT_CRSRMIS_SHIFT           (0U)
#define LCD_CRSR_INTSTAT_CRSRMIS(x)              (((uint32_t)(((uint32_t)(x)) << LCD_CRSR_INTSTAT_CRSRMIS_SHIFT)) & LCD_CRSR_INTSTAT_CRSRMIS_MASK)


/*!
 * @}
 */ /* end of group LCD_Register_Masks */


/* LCD - Peripheral instance base addresses */
/** Peripheral LCD base address */
#define LCD_BASE                                 (0x40083000u)
/** Peripheral LCD base pointer */
#define LCD                                      ((LCD_Type *)LCD_BASE)
/** Array initializer of LCD peripheral base addresses */
#define LCD_BASE_ADDRS                           { LCD_BASE }
/** Array initializer of LCD peripheral base pointers */
#define LCD_BASE_PTRS                            { LCD }
/** Interrupt vectors for the LCD peripheral type */
#define LCD_IRQS                                 { LCD_IRQn }

/*!
 * @}
 */ /* end of group LCD_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MRT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MRT_Peripheral_Access_Layer MRT Peripheral Access Layer
 * @{
 */

/** MRT - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x10 */
    __IO uint32_t INTVAL;                            /**< MRT Time interval value register. This value is loaded into the TIMER register., array offset: 0x0, array step: 0x10 */
    __I  uint32_t TIMER;                             /**< MRT Timer register. This register reads the value of the down-counter., array offset: 0x4, array step: 0x10 */
    __IO uint32_t CTRL;                              /**< MRT Control register. This register controls the MRT modes., array offset: 0x8, array step: 0x10 */
    __IO uint32_t STAT;                              /**< MRT Status register., array offset: 0xC, array step: 0x10 */
  } CHANNEL[4];
       uint8_t RESERVED_0[176];
  __IO uint32_t MODCFG;                            /**< Module Configuration register. This register provides information about this particular MRT instance, and allows choosing an overall mode for the idle channel feature., offset: 0xF0 */
  __I  uint32_t IDLE_CH;                           /**< Idle channel register. This register returns the number of the first idle channel., offset: 0xF4 */
  __IO uint32_t IRQ_FLAG;                          /**< Global interrupt flag register, offset: 0xF8 */
} MRT_Type;

/* ----------------------------------------------------------------------------
   -- MRT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MRT_Register_Masks MRT Register Masks
 * @{
 */

/*! @name CHANNEL_INTVAL - MRT Time interval value register. This value is loaded into the TIMER register. */
#define MRT_CHANNEL_INTVAL_IVALUE_MASK           (0xFFFFFFU)
#define MRT_CHANNEL_INTVAL_IVALUE_SHIFT          (0U)
#define MRT_CHANNEL_INTVAL_IVALUE(x)             (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_INTVAL_IVALUE_SHIFT)) & MRT_CHANNEL_INTVAL_IVALUE_MASK)
#define MRT_CHANNEL_INTVAL_LOAD_MASK             (0x80000000U)
#define MRT_CHANNEL_INTVAL_LOAD_SHIFT            (31U)
#define MRT_CHANNEL_INTVAL_LOAD(x)               (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_INTVAL_LOAD_SHIFT)) & MRT_CHANNEL_INTVAL_LOAD_MASK)

/* The count of MRT_CHANNEL_INTVAL */
#define MRT_CHANNEL_INTVAL_COUNT                 (4U)

/*! @name CHANNEL_TIMER - MRT Timer register. This register reads the value of the down-counter. */
#define MRT_CHANNEL_TIMER_VALUE_MASK             (0xFFFFFFU)
#define MRT_CHANNEL_TIMER_VALUE_SHIFT            (0U)
#define MRT_CHANNEL_TIMER_VALUE(x)               (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_TIMER_VALUE_SHIFT)) & MRT_CHANNEL_TIMER_VALUE_MASK)

/* The count of MRT_CHANNEL_TIMER */
#define MRT_CHANNEL_TIMER_COUNT                  (4U)

/*! @name CHANNEL_CTRL - MRT Control register. This register controls the MRT modes. */
#define MRT_CHANNEL_CTRL_INTEN_MASK              (0x1U)
#define MRT_CHANNEL_CTRL_INTEN_SHIFT             (0U)
#define MRT_CHANNEL_CTRL_INTEN(x)                (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_CTRL_INTEN_SHIFT)) & MRT_CHANNEL_CTRL_INTEN_MASK)
#define MRT_CHANNEL_CTRL_MODE_MASK               (0x6U)
#define MRT_CHANNEL_CTRL_MODE_SHIFT              (1U)
#define MRT_CHANNEL_CTRL_MODE(x)                 (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_CTRL_MODE_SHIFT)) & MRT_CHANNEL_CTRL_MODE_MASK)

/* The count of MRT_CHANNEL_CTRL */
#define MRT_CHANNEL_CTRL_COUNT                   (4U)

/*! @name CHANNEL_STAT - MRT Status register. */
#define MRT_CHANNEL_STAT_INTFLAG_MASK            (0x1U)
#define MRT_CHANNEL_STAT_INTFLAG_SHIFT           (0U)
#define MRT_CHANNEL_STAT_INTFLAG(x)              (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_STAT_INTFLAG_SHIFT)) & MRT_CHANNEL_STAT_INTFLAG_MASK)
#define MRT_CHANNEL_STAT_RUN_MASK                (0x2U)
#define MRT_CHANNEL_STAT_RUN_SHIFT               (1U)
#define MRT_CHANNEL_STAT_RUN(x)                  (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_STAT_RUN_SHIFT)) & MRT_CHANNEL_STAT_RUN_MASK)
#define MRT_CHANNEL_STAT_INUSE_MASK              (0x4U)
#define MRT_CHANNEL_STAT_INUSE_SHIFT             (2U)
#define MRT_CHANNEL_STAT_INUSE(x)                (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_STAT_INUSE_SHIFT)) & MRT_CHANNEL_STAT_INUSE_MASK)

/* The count of MRT_CHANNEL_STAT */
#define MRT_CHANNEL_STAT_COUNT                   (4U)

/*! @name MODCFG - Module Configuration register. This register provides information about this particular MRT instance, and allows choosing an overall mode for the idle channel feature. */
#define MRT_MODCFG_NOC_MASK                      (0xFU)
#define MRT_MODCFG_NOC_SHIFT                     (0U)
#define MRT_MODCFG_NOC(x)                        (((uint32_t)(((uint32_t)(x)) << MRT_MODCFG_NOC_SHIFT)) & MRT_MODCFG_NOC_MASK)
#define MRT_MODCFG_NOB_MASK                      (0x1F0U)
#define MRT_MODCFG_NOB_SHIFT                     (4U)
#define MRT_MODCFG_NOB(x)                        (((uint32_t)(((uint32_t)(x)) << MRT_MODCFG_NOB_SHIFT)) & MRT_MODCFG_NOB_MASK)
#define MRT_MODCFG_MULTITASK_MASK                (0x80000000U)
#define MRT_MODCFG_MULTITASK_SHIFT               (31U)
#define MRT_MODCFG_MULTITASK(x)                  (((uint32_t)(((uint32_t)(x)) << MRT_MODCFG_MULTITASK_SHIFT)) & MRT_MODCFG_MULTITASK_MASK)

/*! @name IDLE_CH - Idle channel register. This register returns the number of the first idle channel. */
#define MRT_IDLE_CH_CHAN_MASK                    (0xF0U)
#define MRT_IDLE_CH_CHAN_SHIFT                   (4U)
#define MRT_IDLE_CH_CHAN(x)                      (((uint32_t)(((uint32_t)(x)) << MRT_IDLE_CH_CHAN_SHIFT)) & MRT_IDLE_CH_CHAN_MASK)

/*! @name IRQ_FLAG - Global interrupt flag register */
#define MRT_IRQ_FLAG_GFLAG0_MASK                 (0x1U)
#define MRT_IRQ_FLAG_GFLAG0_SHIFT                (0U)
#define MRT_IRQ_FLAG_GFLAG0(x)                   (((uint32_t)(((uint32_t)(x)) << MRT_IRQ_FLAG_GFLAG0_SHIFT)) & MRT_IRQ_FLAG_GFLAG0_MASK)
#define MRT_IRQ_FLAG_GFLAG1_MASK                 (0x2U)
#define MRT_IRQ_FLAG_GFLAG1_SHIFT                (1U)
#define MRT_IRQ_FLAG_GFLAG1(x)                   (((uint32_t)(((uint32_t)(x)) << MRT_IRQ_FLAG_GFLAG1_SHIFT)) & MRT_IRQ_FLAG_GFLAG1_MASK)
#define MRT_IRQ_FLAG_GFLAG2_MASK                 (0x4U)
#define MRT_IRQ_FLAG_GFLAG2_SHIFT                (2U)
#define MRT_IRQ_FLAG_GFLAG2(x)                   (((uint32_t)(((uint32_t)(x)) << MRT_IRQ_FLAG_GFLAG2_SHIFT)) & MRT_IRQ_FLAG_GFLAG2_MASK)
#define MRT_IRQ_FLAG_GFLAG3_MASK                 (0x8U)
#define MRT_IRQ_FLAG_GFLAG3_SHIFT                (3U)
#define MRT_IRQ_FLAG_GFLAG3(x)                   (((uint32_t)(((uint32_t)(x)) << MRT_IRQ_FLAG_GFLAG3_SHIFT)) & MRT_IRQ_FLAG_GFLAG3_MASK)


/*!
 * @}
 */ /* end of group MRT_Register_Masks */


/* MRT - Peripheral instance base addresses */
/** Peripheral MRT0 base address */
#define MRT0_BASE                                (0x4000D000u)
/** Peripheral MRT0 base pointer */
#define MRT0                                     ((MRT_Type *)MRT0_BASE)
/** Array initializer of MRT peripheral base addresses */
#define MRT_BASE_ADDRS                           { MRT0_BASE }
/** Array initializer of MRT peripheral base pointers */
#define MRT_BASE_PTRS                            { MRT0 }
/** Interrupt vectors for the MRT peripheral type */
#define MRT_IRQS                                 { MRT0_IRQn }

/*!
 * @}
 */ /* end of group MRT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- OTPC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OTPC_Peripheral_Access_Layer OTPC Peripheral Access Layer
 * @{
 */

/** OTPC - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[16];
  __I  uint32_t AESKEY[8];                         /**< Register for reading the AES key., array offset: 0x10, array step: 0x4 */
  __I  uint32_t ECRP;                              /**< ECRP options., offset: 0x30 */
       uint8_t RESERVED_1[4];
  __I  uint32_t USER0;                             /**< User application specific options., offset: 0x38 */
  __I  uint32_t USER1;                             /**< User application specific options., offset: 0x3C */
} OTPC_Type;

/* ----------------------------------------------------------------------------
   -- OTPC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OTPC_Register_Masks OTPC Register Masks
 * @{
 */

/*! @name AESKEY - Register for reading the AES key. */
#define OTPC_AESKEY_KEY_MASK                     (0xFFFFFFFFU)
#define OTPC_AESKEY_KEY_SHIFT                    (0U)
#define OTPC_AESKEY_KEY(x)                       (((uint32_t)(((uint32_t)(x)) << OTPC_AESKEY_KEY_SHIFT)) & OTPC_AESKEY_KEY_MASK)

/* The count of OTPC_AESKEY */
#define OTPC_AESKEY_COUNT                        (8U)

/*! @name ECRP - ECRP options. */
#define OTPC_ECRP_CRP_MASS_ERASE_DISABLE_MASK    (0x10U)
#define OTPC_ECRP_CRP_MASS_ERASE_DISABLE_SHIFT   (4U)
#define OTPC_ECRP_CRP_MASS_ERASE_DISABLE(x)      (((uint32_t)(((uint32_t)(x)) << OTPC_ECRP_CRP_MASS_ERASE_DISABLE_SHIFT)) & OTPC_ECRP_CRP_MASS_ERASE_DISABLE_MASK)
#define OTPC_ECRP_IAP_PROTECTION_ENABLE_MASK     (0x20U)
#define OTPC_ECRP_IAP_PROTECTION_ENABLE_SHIFT    (5U)
#define OTPC_ECRP_IAP_PROTECTION_ENABLE(x)       (((uint32_t)(((uint32_t)(x)) << OTPC_ECRP_IAP_PROTECTION_ENABLE_SHIFT)) & OTPC_ECRP_IAP_PROTECTION_ENABLE_MASK)
#define OTPC_ECRP_CRP_ISP_DISABLE_PIN_MASK       (0x40U)
#define OTPC_ECRP_CRP_ISP_DISABLE_PIN_SHIFT      (6U)
#define OTPC_ECRP_CRP_ISP_DISABLE_PIN(x)         (((uint32_t)(((uint32_t)(x)) << OTPC_ECRP_CRP_ISP_DISABLE_PIN_SHIFT)) & OTPC_ECRP_CRP_ISP_DISABLE_PIN_MASK)
#define OTPC_ECRP_CRP_ISP_DISABLE_IAP_MASK       (0x80U)
#define OTPC_ECRP_CRP_ISP_DISABLE_IAP_SHIFT      (7U)
#define OTPC_ECRP_CRP_ISP_DISABLE_IAP(x)         (((uint32_t)(((uint32_t)(x)) << OTPC_ECRP_CRP_ISP_DISABLE_IAP_SHIFT)) & OTPC_ECRP_CRP_ISP_DISABLE_IAP_MASK)
#define OTPC_ECRP_CRP_ALLOW_ZERO_MASK            (0x200U)
#define OTPC_ECRP_CRP_ALLOW_ZERO_SHIFT           (9U)
#define OTPC_ECRP_CRP_ALLOW_ZERO(x)              (((uint32_t)(((uint32_t)(x)) << OTPC_ECRP_CRP_ALLOW_ZERO_SHIFT)) & OTPC_ECRP_CRP_ALLOW_ZERO_MASK)
#define OTPC_ECRP_JTAG_DISABLE_MASK              (0x80000000U)
#define OTPC_ECRP_JTAG_DISABLE_SHIFT             (31U)
#define OTPC_ECRP_JTAG_DISABLE(x)                (((uint32_t)(((uint32_t)(x)) << OTPC_ECRP_JTAG_DISABLE_SHIFT)) & OTPC_ECRP_JTAG_DISABLE_MASK)

/*! @name USER0 - User application specific options. */
#define OTPC_USER0_USER0_MASK                    (0xFFFFFFFFU)
#define OTPC_USER0_USER0_SHIFT                   (0U)
#define OTPC_USER0_USER0(x)                      (((uint32_t)(((uint32_t)(x)) << OTPC_USER0_USER0_SHIFT)) & OTPC_USER0_USER0_MASK)

/*! @name USER1 - User application specific options. */
#define OTPC_USER1_USER1_MASK                    (0xFFFFFFFFU)
#define OTPC_USER1_USER1_SHIFT                   (0U)
#define OTPC_USER1_USER1(x)                      (((uint32_t)(((uint32_t)(x)) << OTPC_USER1_USER1_SHIFT)) & OTPC_USER1_USER1_MASK)


/*!
 * @}
 */ /* end of group OTPC_Register_Masks */


/* OTPC - Peripheral instance base addresses */
/** Peripheral OTPC base address */
#define OTPC_BASE                                (0x40015000u)
/** Peripheral OTPC base pointer */
#define OTPC                                     ((OTPC_Type *)OTPC_BASE)
/** Array initializer of OTPC peripheral base addresses */
#define OTPC_BASE_ADDRS                          { OTPC_BASE }
/** Array initializer of OTPC peripheral base pointers */
#define OTPC_BASE_PTRS                           { OTPC }

/*!
 * @}
 */ /* end of group OTPC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PINT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PINT_Peripheral_Access_Layer PINT Peripheral Access Layer
 * @{
 */

/** PINT - Register Layout Typedef */
typedef struct {
  __IO uint32_t ISEL;                              /**< Pin Interrupt Mode register, offset: 0x0 */
  __IO uint32_t IENR;                              /**< Pin interrupt level or rising edge interrupt enable register, offset: 0x4 */
  __O  uint32_t SIENR;                             /**< Pin interrupt level or rising edge interrupt set register, offset: 0x8 */
  __O  uint32_t CIENR;                             /**< Pin interrupt level (rising edge interrupt) clear register, offset: 0xC */
  __IO uint32_t IENF;                              /**< Pin interrupt active level or falling edge interrupt enable register, offset: 0x10 */
  __O  uint32_t SIENF;                             /**< Pin interrupt active level or falling edge interrupt set register, offset: 0x14 */
  __O  uint32_t CIENF;                             /**< Pin interrupt active level or falling edge interrupt clear register, offset: 0x18 */
  __IO uint32_t RISE;                              /**< Pin interrupt rising edge register, offset: 0x1C */
  __IO uint32_t FALL;                              /**< Pin interrupt falling edge register, offset: 0x20 */
  __IO uint32_t IST;                               /**< Pin interrupt status register, offset: 0x24 */
  __IO uint32_t PMCTRL;                            /**< Pattern match interrupt control register, offset: 0x28 */
  __IO uint32_t PMSRC;                             /**< Pattern match interrupt bit-slice source register, offset: 0x2C */
  __IO uint32_t PMCFG;                             /**< Pattern match interrupt bit slice configuration register, offset: 0x30 */
} PINT_Type;

/* ----------------------------------------------------------------------------
   -- PINT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PINT_Register_Masks PINT Register Masks
 * @{
 */

/*! @name ISEL - Pin Interrupt Mode register */
#define PINT_ISEL_PMODE_MASK                     (0xFFU)
#define PINT_ISEL_PMODE_SHIFT                    (0U)
#define PINT_ISEL_PMODE(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_ISEL_PMODE_SHIFT)) & PINT_ISEL_PMODE_MASK)

/*! @name IENR - Pin interrupt level or rising edge interrupt enable register */
#define PINT_IENR_ENRL_MASK                      (0xFFU)
#define PINT_IENR_ENRL_SHIFT                     (0U)
#define PINT_IENR_ENRL(x)                        (((uint32_t)(((uint32_t)(x)) << PINT_IENR_ENRL_SHIFT)) & PINT_IENR_ENRL_MASK)

/*! @name SIENR - Pin interrupt level or rising edge interrupt set register */
#define PINT_SIENR_SETENRL_MASK                  (0xFFU)
#define PINT_SIENR_SETENRL_SHIFT                 (0U)
#define PINT_SIENR_SETENRL(x)                    (((uint32_t)(((uint32_t)(x)) << PINT_SIENR_SETENRL_SHIFT)) & PINT_SIENR_SETENRL_MASK)

/*! @name CIENR - Pin interrupt level (rising edge interrupt) clear register */
#define PINT_CIENR_CENRL_MASK                    (0xFFU)
#define PINT_CIENR_CENRL_SHIFT                   (0U)
#define PINT_CIENR_CENRL(x)                      (((uint32_t)(((uint32_t)(x)) << PINT_CIENR_CENRL_SHIFT)) & PINT_CIENR_CENRL_MASK)

/*! @name IENF - Pin interrupt active level or falling edge interrupt enable register */
#define PINT_IENF_ENAF_MASK                      (0xFFU)
#define PINT_IENF_ENAF_SHIFT                     (0U)
#define PINT_IENF_ENAF(x)                        (((uint32_t)(((uint32_t)(x)) << PINT_IENF_ENAF_SHIFT)) & PINT_IENF_ENAF_MASK)

/*! @name SIENF - Pin interrupt active level or falling edge interrupt set register */
#define PINT_SIENF_SETENAF_MASK                  (0xFFU)
#define PINT_SIENF_SETENAF_SHIFT                 (0U)
#define PINT_SIENF_SETENAF(x)                    (((uint32_t)(((uint32_t)(x)) << PINT_SIENF_SETENAF_SHIFT)) & PINT_SIENF_SETENAF_MASK)

/*! @name CIENF - Pin interrupt active level or falling edge interrupt clear register */
#define PINT_CIENF_CENAF_MASK                    (0xFFU)
#define PINT_CIENF_CENAF_SHIFT                   (0U)
#define PINT_CIENF_CENAF(x)                      (((uint32_t)(((uint32_t)(x)) << PINT_CIENF_CENAF_SHIFT)) & PINT_CIENF_CENAF_MASK)

/*! @name RISE - Pin interrupt rising edge register */
#define PINT_RISE_RDET_MASK                      (0xFFU)
#define PINT_RISE_RDET_SHIFT                     (0U)
#define PINT_RISE_RDET(x)                        (((uint32_t)(((uint32_t)(x)) << PINT_RISE_RDET_SHIFT)) & PINT_RISE_RDET_MASK)

/*! @name FALL - Pin interrupt falling edge register */
#define PINT_FALL_FDET_MASK                      (0xFFU)
#define PINT_FALL_FDET_SHIFT                     (0U)
#define PINT_FALL_FDET(x)                        (((uint32_t)(((uint32_t)(x)) << PINT_FALL_FDET_SHIFT)) & PINT_FALL_FDET_MASK)

/*! @name IST - Pin interrupt status register */
#define PINT_IST_PSTAT_MASK                      (0xFFU)
#define PINT_IST_PSTAT_SHIFT                     (0U)
#define PINT_IST_PSTAT(x)                        (((uint32_t)(((uint32_t)(x)) << PINT_IST_PSTAT_SHIFT)) & PINT_IST_PSTAT_MASK)

/*! @name PMCTRL - Pattern match interrupt control register */
#define PINT_PMCTRL_SEL_PMATCH_MASK              (0x1U)
#define PINT_PMCTRL_SEL_PMATCH_SHIFT             (0U)
#define PINT_PMCTRL_SEL_PMATCH(x)                (((uint32_t)(((uint32_t)(x)) << PINT_PMCTRL_SEL_PMATCH_SHIFT)) & PINT_PMCTRL_SEL_PMATCH_MASK)
#define PINT_PMCTRL_ENA_RXEV_MASK                (0x2U)
#define PINT_PMCTRL_ENA_RXEV_SHIFT               (1U)
#define PINT_PMCTRL_ENA_RXEV(x)                  (((uint32_t)(((uint32_t)(x)) << PINT_PMCTRL_ENA_RXEV_SHIFT)) & PINT_PMCTRL_ENA_RXEV_MASK)
#define PINT_PMCTRL_PMAT_MASK                    (0xFF000000U)
#define PINT_PMCTRL_PMAT_SHIFT                   (24U)
#define PINT_PMCTRL_PMAT(x)                      (((uint32_t)(((uint32_t)(x)) << PINT_PMCTRL_PMAT_SHIFT)) & PINT_PMCTRL_PMAT_MASK)

/*! @name PMSRC - Pattern match interrupt bit-slice source register */
#define PINT_PMSRC_SRC0_MASK                     (0x700U)
#define PINT_PMSRC_SRC0_SHIFT                    (8U)
#define PINT_PMSRC_SRC0(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC0_SHIFT)) & PINT_PMSRC_SRC0_MASK)
#define PINT_PMSRC_SRC1_MASK                     (0x3800U)
#define PINT_PMSRC_SRC1_SHIFT                    (11U)
#define PINT_PMSRC_SRC1(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC1_SHIFT)) & PINT_PMSRC_SRC1_MASK)
#define PINT_PMSRC_SRC2_MASK                     (0x1C000U)
#define PINT_PMSRC_SRC2_SHIFT                    (14U)
#define PINT_PMSRC_SRC2(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC2_SHIFT)) & PINT_PMSRC_SRC2_MASK)
#define PINT_PMSRC_SRC3_MASK                     (0xE0000U)
#define PINT_PMSRC_SRC3_SHIFT                    (17U)
#define PINT_PMSRC_SRC3(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC3_SHIFT)) & PINT_PMSRC_SRC3_MASK)
#define PINT_PMSRC_SRC4_MASK                     (0x700000U)
#define PINT_PMSRC_SRC4_SHIFT                    (20U)
#define PINT_PMSRC_SRC4(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC4_SHIFT)) & PINT_PMSRC_SRC4_MASK)
#define PINT_PMSRC_SRC5_MASK                     (0x3800000U)
#define PINT_PMSRC_SRC5_SHIFT                    (23U)
#define PINT_PMSRC_SRC5(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC5_SHIFT)) & PINT_PMSRC_SRC5_MASK)
#define PINT_PMSRC_SRC6_MASK                     (0x1C000000U)
#define PINT_PMSRC_SRC6_SHIFT                    (26U)
#define PINT_PMSRC_SRC6(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC6_SHIFT)) & PINT_PMSRC_SRC6_MASK)
#define PINT_PMSRC_SRC7_MASK                     (0xE0000000U)
#define PINT_PMSRC_SRC7_SHIFT                    (29U)
#define PINT_PMSRC_SRC7(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC7_SHIFT)) & PINT_PMSRC_SRC7_MASK)

/*! @name PMCFG - Pattern match interrupt bit slice configuration register */
#define PINT_PMCFG_PROD_ENDPTS0_MASK             (0x1U)
#define PINT_PMCFG_PROD_ENDPTS0_SHIFT            (0U)
#define PINT_PMCFG_PROD_ENDPTS0(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS0_SHIFT)) & PINT_PMCFG_PROD_ENDPTS0_MASK)
#define PINT_PMCFG_PROD_ENDPTS1_MASK             (0x2U)
#define PINT_PMCFG_PROD_ENDPTS1_SHIFT            (1U)
#define PINT_PMCFG_PROD_ENDPTS1(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS1_SHIFT)) & PINT_PMCFG_PROD_ENDPTS1_MASK)
#define PINT_PMCFG_PROD_ENDPTS2_MASK             (0x4U)
#define PINT_PMCFG_PROD_ENDPTS2_SHIFT            (2U)
#define PINT_PMCFG_PROD_ENDPTS2(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS2_SHIFT)) & PINT_PMCFG_PROD_ENDPTS2_MASK)
#define PINT_PMCFG_PROD_ENDPTS3_MASK             (0x8U)
#define PINT_PMCFG_PROD_ENDPTS3_SHIFT            (3U)
#define PINT_PMCFG_PROD_ENDPTS3(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS3_SHIFT)) & PINT_PMCFG_PROD_ENDPTS3_MASK)
#define PINT_PMCFG_PROD_ENDPTS4_MASK             (0x10U)
#define PINT_PMCFG_PROD_ENDPTS4_SHIFT            (4U)
#define PINT_PMCFG_PROD_ENDPTS4(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS4_SHIFT)) & PINT_PMCFG_PROD_ENDPTS4_MASK)
#define PINT_PMCFG_PROD_ENDPTS5_MASK             (0x20U)
#define PINT_PMCFG_PROD_ENDPTS5_SHIFT            (5U)
#define PINT_PMCFG_PROD_ENDPTS5(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS5_SHIFT)) & PINT_PMCFG_PROD_ENDPTS5_MASK)
#define PINT_PMCFG_PROD_ENDPTS6_MASK             (0x40U)
#define PINT_PMCFG_PROD_ENDPTS6_SHIFT            (6U)
#define PINT_PMCFG_PROD_ENDPTS6(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS6_SHIFT)) & PINT_PMCFG_PROD_ENDPTS6_MASK)
#define PINT_PMCFG_CFG0_MASK                     (0x700U)
#define PINT_PMCFG_CFG0_SHIFT                    (8U)
#define PINT_PMCFG_CFG0(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG0_SHIFT)) & PINT_PMCFG_CFG0_MASK)
#define PINT_PMCFG_CFG1_MASK                     (0x3800U)
#define PINT_PMCFG_CFG1_SHIFT                    (11U)
#define PINT_PMCFG_CFG1(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG1_SHIFT)) & PINT_PMCFG_CFG1_MASK)
#define PINT_PMCFG_CFG2_MASK                     (0x1C000U)
#define PINT_PMCFG_CFG2_SHIFT                    (14U)
#define PINT_PMCFG_CFG2(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG2_SHIFT)) & PINT_PMCFG_CFG2_MASK)
#define PINT_PMCFG_CFG3_MASK                     (0xE0000U)
#define PINT_PMCFG_CFG3_SHIFT                    (17U)
#define PINT_PMCFG_CFG3(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG3_SHIFT)) & PINT_PMCFG_CFG3_MASK)
#define PINT_PMCFG_CFG4_MASK                     (0x700000U)
#define PINT_PMCFG_CFG4_SHIFT                    (20U)
#define PINT_PMCFG_CFG4(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG4_SHIFT)) & PINT_PMCFG_CFG4_MASK)
#define PINT_PMCFG_CFG5_MASK                     (0x3800000U)
#define PINT_PMCFG_CFG5_SHIFT                    (23U)
#define PINT_PMCFG_CFG5(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG5_SHIFT)) & PINT_PMCFG_CFG5_MASK)
#define PINT_PMCFG_CFG6_MASK                     (0x1C000000U)
#define PINT_PMCFG_CFG6_SHIFT                    (26U)
#define PINT_PMCFG_CFG6(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG6_SHIFT)) & PINT_PMCFG_CFG6_MASK)
#define PINT_PMCFG_CFG7_MASK                     (0xE0000000U)
#define PINT_PMCFG_CFG7_SHIFT                    (29U)
#define PINT_PMCFG_CFG7(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG7_SHIFT)) & PINT_PMCFG_CFG7_MASK)


/*!
 * @}
 */ /* end of group PINT_Register_Masks */


/* PINT - Peripheral instance base addresses */
/** Peripheral PINT base address */
#define PINT_BASE                                (0x40004000u)
/** Peripheral PINT base pointer */
#define PINT                                     ((PINT_Type *)PINT_BASE)
/** Array initializer of PINT peripheral base addresses */
#define PINT_BASE_ADDRS                          { PINT_BASE }
/** Array initializer of PINT peripheral base pointers */
#define PINT_BASE_PTRS                           { PINT }
/** Interrupt vectors for the PINT peripheral type */
#define PINT_IRQS                                { PIN_INT0_IRQn, PIN_INT1_IRQn, PIN_INT2_IRQn, PIN_INT3_IRQn, PIN_INT4_IRQn, PIN_INT5_IRQn, PIN_INT6_IRQn, PIN_INT7_IRQn }

/*!
 * @}
 */ /* end of group PINT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RIT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RIT_Peripheral_Access_Layer RIT Peripheral Access Layer
 * @{
 */

/** RIT - Register Layout Typedef */
typedef struct {
  __IO uint32_t COMPVAL;                           /**< Compare value LSB register, offset: 0x0 */
  __IO uint32_t MASK;                              /**< Mask LSB register, offset: 0x4 */
  __IO uint32_t CTRL;                              /**< Control register, offset: 0x8 */
  __IO uint32_t COUNTER;                           /**< Counter LSB register, offset: 0xC */
  __IO uint32_t COMPVAL_H;                         /**< Compare value MSB register, offset: 0x10 */
  __IO uint32_t MASK_H;                            /**< Mask MSB register, offset: 0x14 */
       uint8_t RESERVED_0[4];
  __IO uint32_t COUNTER_H;                         /**< Counter MSB register, offset: 0x1C */
} RIT_Type;

/* ----------------------------------------------------------------------------
   -- RIT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RIT_Register_Masks RIT Register Masks
 * @{
 */

/*! @name COMPVAL - Compare value LSB register */
#define RIT_COMPVAL_RICOMP_MASK                  (0xFFFFFFFFU)
#define RIT_COMPVAL_RICOMP_SHIFT                 (0U)
#define RIT_COMPVAL_RICOMP(x)                    (((uint32_t)(((uint32_t)(x)) << RIT_COMPVAL_RICOMP_SHIFT)) & RIT_COMPVAL_RICOMP_MASK)

/*! @name MASK - Mask LSB register */
#define RIT_MASK_RIMASK_MASK                     (0xFFFFFFFFU)
#define RIT_MASK_RIMASK_SHIFT                    (0U)
#define RIT_MASK_RIMASK(x)                       (((uint32_t)(((uint32_t)(x)) << RIT_MASK_RIMASK_SHIFT)) & RIT_MASK_RIMASK_MASK)

/*! @name CTRL - Control register */
#define RIT_CTRL_RITINT_MASK                     (0x1U)
#define RIT_CTRL_RITINT_SHIFT                    (0U)
#define RIT_CTRL_RITINT(x)                       (((uint32_t)(((uint32_t)(x)) << RIT_CTRL_RITINT_SHIFT)) & RIT_CTRL_RITINT_MASK)
#define RIT_CTRL_RITENCLR_MASK                   (0x2U)
#define RIT_CTRL_RITENCLR_SHIFT                  (1U)
#define RIT_CTRL_RITENCLR(x)                     (((uint32_t)(((uint32_t)(x)) << RIT_CTRL_RITENCLR_SHIFT)) & RIT_CTRL_RITENCLR_MASK)
#define RIT_CTRL_RITENBR_MASK                    (0x4U)
#define RIT_CTRL_RITENBR_SHIFT                   (2U)
#define RIT_CTRL_RITENBR(x)                      (((uint32_t)(((uint32_t)(x)) << RIT_CTRL_RITENBR_SHIFT)) & RIT_CTRL_RITENBR_MASK)
#define RIT_CTRL_RITEN_MASK                      (0x8U)
#define RIT_CTRL_RITEN_SHIFT                     (3U)
#define RIT_CTRL_RITEN(x)                        (((uint32_t)(((uint32_t)(x)) << RIT_CTRL_RITEN_SHIFT)) & RIT_CTRL_RITEN_MASK)

/*! @name COUNTER - Counter LSB register */
#define RIT_COUNTER_RICOUNTER_MASK               (0xFFFFFFFFU)
#define RIT_COUNTER_RICOUNTER_SHIFT              (0U)
#define RIT_COUNTER_RICOUNTER(x)                 (((uint32_t)(((uint32_t)(x)) << RIT_COUNTER_RICOUNTER_SHIFT)) & RIT_COUNTER_RICOUNTER_MASK)

/*! @name COMPVAL_H - Compare value MSB register */
#define RIT_COMPVAL_H_RICOMP_MASK                (0xFFFFU)
#define RIT_COMPVAL_H_RICOMP_SHIFT               (0U)
#define RIT_COMPVAL_H_RICOMP(x)                  (((uint32_t)(((uint32_t)(x)) << RIT_COMPVAL_H_RICOMP_SHIFT)) & RIT_COMPVAL_H_RICOMP_MASK)

/*! @name MASK_H - Mask MSB register */
#define RIT_MASK_H_RIMASK_MASK                   (0xFFFFU)
#define RIT_MASK_H_RIMASK_SHIFT                  (0U)
#define RIT_MASK_H_RIMASK(x)                     (((uint32_t)(((uint32_t)(x)) << RIT_MASK_H_RIMASK_SHIFT)) & RIT_MASK_H_RIMASK_MASK)

/*! @name COUNTER_H - Counter MSB register */
#define RIT_COUNTER_H_RICOUNTER_MASK             (0xFFFFU)
#define RIT_COUNTER_H_RICOUNTER_SHIFT            (0U)
#define RIT_COUNTER_H_RICOUNTER(x)               (((uint32_t)(((uint32_t)(x)) << RIT_COUNTER_H_RICOUNTER_SHIFT)) & RIT_COUNTER_H_RICOUNTER_MASK)


/*!
 * @}
 */ /* end of group RIT_Register_Masks */


/* RIT - Peripheral instance base addresses */
/** Peripheral RIT base address */
#define RIT_BASE                                 (0x4002D000u)
/** Peripheral RIT base pointer */
#define RIT                                      ((RIT_Type *)RIT_BASE)
/** Array initializer of RIT peripheral base addresses */
#define RIT_BASE_ADDRS                           { RIT_BASE }
/** Array initializer of RIT peripheral base pointers */
#define RIT_BASE_PTRS                            { RIT }
/** Interrupt vectors for the RIT peripheral type */
#define RIT_IRQS                                 { RIT_IRQn }

/*!
 * @}
 */ /* end of group RIT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RTC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Peripheral_Access_Layer RTC Peripheral Access Layer
 * @{
 */

/** RTC - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< RTC control register, offset: 0x0 */
  __IO uint32_t MATCH;                             /**< RTC match register, offset: 0x4 */
  __IO uint32_t COUNT;                             /**< RTC counter register, offset: 0x8 */
  __IO uint32_t WAKE;                              /**< High-resolution/wake-up timer control register, offset: 0xC */
       uint8_t RESERVED_0[48];
  __IO uint32_t GPREG[8];                          /**< General Purpose register, array offset: 0x40, array step: 0x4 */
} RTC_Type;

/* ----------------------------------------------------------------------------
   -- RTC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Masks RTC Register Masks
 * @{
 */

/*! @name CTRL - RTC control register */
#define RTC_CTRL_SWRESET_MASK                    (0x1U)
#define RTC_CTRL_SWRESET_SHIFT                   (0U)
#define RTC_CTRL_SWRESET(x)                      (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_SWRESET_SHIFT)) & RTC_CTRL_SWRESET_MASK)
#define RTC_CTRL_ALARM1HZ_MASK                   (0x4U)
#define RTC_CTRL_ALARM1HZ_SHIFT                  (2U)
#define RTC_CTRL_ALARM1HZ(x)                     (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_ALARM1HZ_SHIFT)) & RTC_CTRL_ALARM1HZ_MASK)
#define RTC_CTRL_WAKE1KHZ_MASK                   (0x8U)
#define RTC_CTRL_WAKE1KHZ_SHIFT                  (3U)
#define RTC_CTRL_WAKE1KHZ(x)                     (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_WAKE1KHZ_SHIFT)) & RTC_CTRL_WAKE1KHZ_MASK)
#define RTC_CTRL_ALARMDPD_EN_MASK                (0x10U)
#define RTC_CTRL_ALARMDPD_EN_SHIFT               (4U)
#define RTC_CTRL_ALARMDPD_EN(x)                  (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_ALARMDPD_EN_SHIFT)) & RTC_CTRL_ALARMDPD_EN_MASK)
#define RTC_CTRL_WAKEDPD_EN_MASK                 (0x20U)
#define RTC_CTRL_WAKEDPD_EN_SHIFT                (5U)
#define RTC_CTRL_WAKEDPD_EN(x)                   (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_WAKEDPD_EN_SHIFT)) & RTC_CTRL_WAKEDPD_EN_MASK)
#define RTC_CTRL_RTC1KHZ_EN_MASK                 (0x40U)
#define RTC_CTRL_RTC1KHZ_EN_SHIFT                (6U)
#define RTC_CTRL_RTC1KHZ_EN(x)                   (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_RTC1KHZ_EN_SHIFT)) & RTC_CTRL_RTC1KHZ_EN_MASK)
#define RTC_CTRL_RTC_EN_MASK                     (0x80U)
#define RTC_CTRL_RTC_EN_SHIFT                    (7U)
#define RTC_CTRL_RTC_EN(x)                       (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_RTC_EN_SHIFT)) & RTC_CTRL_RTC_EN_MASK)
#define RTC_CTRL_RTC_OSC_PD_MASK                 (0x100U)
#define RTC_CTRL_RTC_OSC_PD_SHIFT                (8U)
#define RTC_CTRL_RTC_OSC_PD(x)                   (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_RTC_OSC_PD_SHIFT)) & RTC_CTRL_RTC_OSC_PD_MASK)

/*! @name MATCH - RTC match register */
#define RTC_MATCH_MATVAL_MASK                    (0xFFFFFFFFU)
#define RTC_MATCH_MATVAL_SHIFT                   (0U)
#define RTC_MATCH_MATVAL(x)                      (((uint32_t)(((uint32_t)(x)) << RTC_MATCH_MATVAL_SHIFT)) & RTC_MATCH_MATVAL_MASK)

/*! @name COUNT - RTC counter register */
#define RTC_COUNT_VAL_MASK                       (0xFFFFFFFFU)
#define RTC_COUNT_VAL_SHIFT                      (0U)
#define RTC_COUNT_VAL(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_COUNT_VAL_SHIFT)) & RTC_COUNT_VAL_MASK)

/*! @name WAKE - High-resolution/wake-up timer control register */
#define RTC_WAKE_VAL_MASK                        (0xFFFFU)
#define RTC_WAKE_VAL_SHIFT                       (0U)
#define RTC_WAKE_VAL(x)                          (((uint32_t)(((uint32_t)(x)) << RTC_WAKE_VAL_SHIFT)) & RTC_WAKE_VAL_MASK)

/*! @name GPREG - General Purpose register */
#define RTC_GPREG_GPDATA_MASK                    (0xFFFFFFFFU)
#define RTC_GPREG_GPDATA_SHIFT                   (0U)
#define RTC_GPREG_GPDATA(x)                      (((uint32_t)(((uint32_t)(x)) << RTC_GPREG_GPDATA_SHIFT)) & RTC_GPREG_GPDATA_MASK)

/* The count of RTC_GPREG */
#define RTC_GPREG_COUNT                          (8U)


/*!
 * @}
 */ /* end of group RTC_Register_Masks */


/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base address */
#define RTC_BASE                                 (0x4002C000u)
/** Peripheral RTC base pointer */
#define RTC                                      ((RTC_Type *)RTC_BASE)
/** Array initializer of RTC peripheral base addresses */
#define RTC_BASE_ADDRS                           { RTC_BASE }
/** Array initializer of RTC peripheral base pointers */
#define RTC_BASE_PTRS                            { RTC }
/** Interrupt vectors for the RTC peripheral type */
#define RTC_IRQS                                 { RTC_IRQn }

/*!
 * @}
 */ /* end of group RTC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SCT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCT_Peripheral_Access_Layer SCT Peripheral Access Layer
 * @{
 */

/** SCT - Register Layout Typedef */
typedef struct {
  __IO uint32_t CONFIG;                            /**< SCT configuration register, offset: 0x0 */
  __IO uint32_t CTRL;                              /**< SCT control register, offset: 0x4 */
  __IO uint32_t LIMIT;                             /**< SCT limit event select register, offset: 0x8 */
  __IO uint32_t HALT;                              /**< SCT halt event select register, offset: 0xC */
  __IO uint32_t STOP;                              /**< SCT stop event select register, offset: 0x10 */
  __IO uint32_t START;                             /**< SCT start event select register, offset: 0x14 */
       uint8_t RESERVED_0[40];
  __IO uint32_t COUNT;                             /**< SCT counter register, offset: 0x40 */
  __IO uint32_t STATE;                             /**< SCT state register, offset: 0x44 */
  __I  uint32_t INPUT;                             /**< SCT input register, offset: 0x48 */
  __IO uint32_t REGMODE;                           /**< SCT match/capture mode register, offset: 0x4C */
  __IO uint32_t OUTPUT;                            /**< SCT output register, offset: 0x50 */
  __IO uint32_t OUTPUTDIRCTRL;                     /**< SCT output counter direction control register, offset: 0x54 */
  __IO uint32_t RES;                               /**< SCT conflict resolution register, offset: 0x58 */
  __IO uint32_t DMA0REQUEST;                       /**< SCT DMA request 0 register, offset: 0x5C */
  __IO uint32_t DMA1REQUEST;                       /**< SCT DMA request 1 register, offset: 0x60 */
       uint8_t RESERVED_1[140];
  __IO uint32_t EVEN;                              /**< SCT event interrupt enable register, offset: 0xF0 */
  __IO uint32_t EVFLAG;                            /**< SCT event flag register, offset: 0xF4 */
  __IO uint32_t CONEN;                             /**< SCT conflict interrupt enable register, offset: 0xF8 */
  __IO uint32_t CONFLAG;                           /**< SCT conflict flag register, offset: 0xFC */
  union {                                          /* offset: 0x100 */
    __IO uint32_t SCTCAP[10];                        /**< SCT capture register of capture channel, array offset: 0x100, array step: 0x4 */
    __IO uint32_t SCTMATCH[10];                      /**< SCT match value register of match channels, array offset: 0x100, array step: 0x4 */
  };
       uint8_t RESERVED_2[216];
  union {                                          /* offset: 0x200 */
    __IO uint32_t SCTCAPCTRL[10];                    /**< SCT capture control register, array offset: 0x200, array step: 0x4 */
    __IO uint32_t SCTMATCHREL[10];                   /**< SCT match reload value register, array offset: 0x200, array step: 0x4 */
  };
       uint8_t RESERVED_3[216];
  struct {                                         /* offset: 0x300, array step: 0x8 */
    __IO uint32_t STATE;                             /**< SCT event state register 0, array offset: 0x300, array step: 0x8 */
    __IO uint32_t CTRL;                              /**< SCT event control register 0, array offset: 0x304, array step: 0x8 */
  } EVENT[10];
       uint8_t RESERVED_4[432];
  struct {                                         /* offset: 0x500, array step: 0x8 */
    __IO uint32_t SET;                               /**< SCT output 0 set register, array offset: 0x500, array step: 0x8 */
    __IO uint32_t CLR;                               /**< SCT output 0 clear register, array offset: 0x504, array step: 0x8 */
  } OUT[10];
} SCT_Type;

/* ----------------------------------------------------------------------------
   -- SCT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCT_Register_Masks SCT Register Masks
 * @{
 */

/*! @name CONFIG - SCT configuration register */
#define SCT_CONFIG_UNIFY_MASK                    (0x1U)
#define SCT_CONFIG_UNIFY_SHIFT                   (0U)
#define SCT_CONFIG_UNIFY(x)                      (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_UNIFY_SHIFT)) & SCT_CONFIG_UNIFY_MASK)
#define SCT_CONFIG_CLKMODE_MASK                  (0x6U)
#define SCT_CONFIG_CLKMODE_SHIFT                 (1U)
#define SCT_CONFIG_CLKMODE(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_CLKMODE_SHIFT)) & SCT_CONFIG_CLKMODE_MASK)
#define SCT_CONFIG_CKSEL_MASK                    (0x78U)
#define SCT_CONFIG_CKSEL_SHIFT                   (3U)
#define SCT_CONFIG_CKSEL(x)                      (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_CKSEL_SHIFT)) & SCT_CONFIG_CKSEL_MASK)
#define SCT_CONFIG_NORELAOD_L_MASK               (0x80U)
#define SCT_CONFIG_NORELAOD_L_SHIFT              (7U)
#define SCT_CONFIG_NORELAOD_L(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_NORELAOD_L_SHIFT)) & SCT_CONFIG_NORELAOD_L_MASK)
#define SCT_CONFIG_NORELOAD_H_MASK               (0x100U)
#define SCT_CONFIG_NORELOAD_H_SHIFT              (8U)
#define SCT_CONFIG_NORELOAD_H(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_NORELOAD_H_SHIFT)) & SCT_CONFIG_NORELOAD_H_MASK)
#define SCT_CONFIG_INSYNC_MASK                   (0x1E00U)
#define SCT_CONFIG_INSYNC_SHIFT                  (9U)
#define SCT_CONFIG_INSYNC(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_INSYNC_SHIFT)) & SCT_CONFIG_INSYNC_MASK)
#define SCT_CONFIG_AUTOLIMIT_L_MASK              (0x20000U)
#define SCT_CONFIG_AUTOLIMIT_L_SHIFT             (17U)
#define SCT_CONFIG_AUTOLIMIT_L(x)                (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_AUTOLIMIT_L_SHIFT)) & SCT_CONFIG_AUTOLIMIT_L_MASK)
#define SCT_CONFIG_AUTOLIMIT_H_MASK              (0x40000U)
#define SCT_CONFIG_AUTOLIMIT_H_SHIFT             (18U)
#define SCT_CONFIG_AUTOLIMIT_H(x)                (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_AUTOLIMIT_H_SHIFT)) & SCT_CONFIG_AUTOLIMIT_H_MASK)

/*! @name CTRL - SCT control register */
#define SCT_CTRL_DOWN_L_MASK                     (0x1U)
#define SCT_CTRL_DOWN_L_SHIFT                    (0U)
#define SCT_CTRL_DOWN_L(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_DOWN_L_SHIFT)) & SCT_CTRL_DOWN_L_MASK)
#define SCT_CTRL_STOP_L_MASK                     (0x2U)
#define SCT_CTRL_STOP_L_SHIFT                    (1U)
#define SCT_CTRL_STOP_L(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_STOP_L_SHIFT)) & SCT_CTRL_STOP_L_MASK)
#define SCT_CTRL_HALT_L_MASK                     (0x4U)
#define SCT_CTRL_HALT_L_SHIFT                    (2U)
#define SCT_CTRL_HALT_L(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_HALT_L_SHIFT)) & SCT_CTRL_HALT_L_MASK)
#define SCT_CTRL_CLRCTR_L_MASK                   (0x8U)
#define SCT_CTRL_CLRCTR_L_SHIFT                  (3U)
#define SCT_CTRL_CLRCTR_L(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_CLRCTR_L_SHIFT)) & SCT_CTRL_CLRCTR_L_MASK)
#define SCT_CTRL_BIDIR_L_MASK                    (0x10U)
#define SCT_CTRL_BIDIR_L_SHIFT                   (4U)
#define SCT_CTRL_BIDIR_L(x)                      (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_BIDIR_L_SHIFT)) & SCT_CTRL_BIDIR_L_MASK)
#define SCT_CTRL_PRE_L_MASK                      (0x1FE0U)
#define SCT_CTRL_PRE_L_SHIFT                     (5U)
#define SCT_CTRL_PRE_L(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_PRE_L_SHIFT)) & SCT_CTRL_PRE_L_MASK)
#define SCT_CTRL_DOWN_H_MASK                     (0x10000U)
#define SCT_CTRL_DOWN_H_SHIFT                    (16U)
#define SCT_CTRL_DOWN_H(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_DOWN_H_SHIFT)) & SCT_CTRL_DOWN_H_MASK)
#define SCT_CTRL_STOP_H_MASK                     (0x20000U)
#define SCT_CTRL_STOP_H_SHIFT                    (17U)
#define SCT_CTRL_STOP_H(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_STOP_H_SHIFT)) & SCT_CTRL_STOP_H_MASK)
#define SCT_CTRL_HALT_H_MASK                     (0x40000U)
#define SCT_CTRL_HALT_H_SHIFT                    (18U)
#define SCT_CTRL_HALT_H(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_HALT_H_SHIFT)) & SCT_CTRL_HALT_H_MASK)
#define SCT_CTRL_CLRCTR_H_MASK                   (0x80000U)
#define SCT_CTRL_CLRCTR_H_SHIFT                  (19U)
#define SCT_CTRL_CLRCTR_H(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_CLRCTR_H_SHIFT)) & SCT_CTRL_CLRCTR_H_MASK)
#define SCT_CTRL_BIDIR_H_MASK                    (0x100000U)
#define SCT_CTRL_BIDIR_H_SHIFT                   (20U)
#define SCT_CTRL_BIDIR_H(x)                      (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_BIDIR_H_SHIFT)) & SCT_CTRL_BIDIR_H_MASK)
#define SCT_CTRL_PRE_H_MASK                      (0x1FE00000U)
#define SCT_CTRL_PRE_H_SHIFT                     (21U)
#define SCT_CTRL_PRE_H(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_PRE_H_SHIFT)) & SCT_CTRL_PRE_H_MASK)

/*! @name LIMIT - SCT limit event select register */
#define SCT_LIMIT_LIMMSK_L_MASK                  (0xFFFFU)
#define SCT_LIMIT_LIMMSK_L_SHIFT                 (0U)
#define SCT_LIMIT_LIMMSK_L(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_LIMIT_LIMMSK_L_SHIFT)) & SCT_LIMIT_LIMMSK_L_MASK)
#define SCT_LIMIT_LIMMSK_H_MASK                  (0xFFFF0000U)
#define SCT_LIMIT_LIMMSK_H_SHIFT                 (16U)
#define SCT_LIMIT_LIMMSK_H(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_LIMIT_LIMMSK_H_SHIFT)) & SCT_LIMIT_LIMMSK_H_MASK)

/*! @name HALT - SCT halt event select register */
#define SCT_HALT_HALTMSK_L_MASK                  (0xFFFFU)
#define SCT_HALT_HALTMSK_L_SHIFT                 (0U)
#define SCT_HALT_HALTMSK_L(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_HALT_HALTMSK_L_SHIFT)) & SCT_HALT_HALTMSK_L_MASK)
#define SCT_HALT_HALTMSK_H_MASK                  (0xFFFF0000U)
#define SCT_HALT_HALTMSK_H_SHIFT                 (16U)
#define SCT_HALT_HALTMSK_H(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_HALT_HALTMSK_H_SHIFT)) & SCT_HALT_HALTMSK_H_MASK)

/*! @name STOP - SCT stop event select register */
#define SCT_STOP_STOPMSK_L_MASK                  (0xFFFFU)
#define SCT_STOP_STOPMSK_L_SHIFT                 (0U)
#define SCT_STOP_STOPMSK_L(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_STOP_STOPMSK_L_SHIFT)) & SCT_STOP_STOPMSK_L_MASK)
#define SCT_STOP_STOPMSK_H_MASK                  (0xFFFF0000U)
#define SCT_STOP_STOPMSK_H_SHIFT                 (16U)
#define SCT_STOP_STOPMSK_H(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_STOP_STOPMSK_H_SHIFT)) & SCT_STOP_STOPMSK_H_MASK)

/*! @name START - SCT start event select register */
#define SCT_START_STARTMSK_L_MASK                (0xFFFFU)
#define SCT_START_STARTMSK_L_SHIFT               (0U)
#define SCT_START_STARTMSK_L(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_START_STARTMSK_L_SHIFT)) & SCT_START_STARTMSK_L_MASK)
#define SCT_START_STARTMSK_H_MASK                (0xFFFF0000U)
#define SCT_START_STARTMSK_H_SHIFT               (16U)
#define SCT_START_STARTMSK_H(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_START_STARTMSK_H_SHIFT)) & SCT_START_STARTMSK_H_MASK)

/*! @name COUNT - SCT counter register */
#define SCT_COUNT_CTR_L_MASK                     (0xFFFFU)
#define SCT_COUNT_CTR_L_SHIFT                    (0U)
#define SCT_COUNT_CTR_L(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_COUNT_CTR_L_SHIFT)) & SCT_COUNT_CTR_L_MASK)
#define SCT_COUNT_CTR_H_MASK                     (0xFFFF0000U)
#define SCT_COUNT_CTR_H_SHIFT                    (16U)
#define SCT_COUNT_CTR_H(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_COUNT_CTR_H_SHIFT)) & SCT_COUNT_CTR_H_MASK)

/*! @name STATE - SCT state register */
#define SCT_STATE_STATE_L_MASK                   (0x1FU)
#define SCT_STATE_STATE_L_SHIFT                  (0U)
#define SCT_STATE_STATE_L(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_STATE_STATE_L_SHIFT)) & SCT_STATE_STATE_L_MASK)
#define SCT_STATE_STATE_H_MASK                   (0x1F0000U)
#define SCT_STATE_STATE_H_SHIFT                  (16U)
#define SCT_STATE_STATE_H(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_STATE_STATE_H_SHIFT)) & SCT_STATE_STATE_H_MASK)

/*! @name INPUT - SCT input register */
#define SCT_INPUT_AIN0_MASK                      (0x1U)
#define SCT_INPUT_AIN0_SHIFT                     (0U)
#define SCT_INPUT_AIN0(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN0_SHIFT)) & SCT_INPUT_AIN0_MASK)
#define SCT_INPUT_AIN1_MASK                      (0x2U)
#define SCT_INPUT_AIN1_SHIFT                     (1U)
#define SCT_INPUT_AIN1(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN1_SHIFT)) & SCT_INPUT_AIN1_MASK)
#define SCT_INPUT_AIN2_MASK                      (0x4U)
#define SCT_INPUT_AIN2_SHIFT                     (2U)
#define SCT_INPUT_AIN2(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN2_SHIFT)) & SCT_INPUT_AIN2_MASK)
#define SCT_INPUT_AIN3_MASK                      (0x8U)
#define SCT_INPUT_AIN3_SHIFT                     (3U)
#define SCT_INPUT_AIN3(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN3_SHIFT)) & SCT_INPUT_AIN3_MASK)
#define SCT_INPUT_AIN4_MASK                      (0x10U)
#define SCT_INPUT_AIN4_SHIFT                     (4U)
#define SCT_INPUT_AIN4(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN4_SHIFT)) & SCT_INPUT_AIN4_MASK)
#define SCT_INPUT_AIN5_MASK                      (0x20U)
#define SCT_INPUT_AIN5_SHIFT                     (5U)
#define SCT_INPUT_AIN5(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN5_SHIFT)) & SCT_INPUT_AIN5_MASK)
#define SCT_INPUT_AIN6_MASK                      (0x40U)
#define SCT_INPUT_AIN6_SHIFT                     (6U)
#define SCT_INPUT_AIN6(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN6_SHIFT)) & SCT_INPUT_AIN6_MASK)
#define SCT_INPUT_AIN7_MASK                      (0x80U)
#define SCT_INPUT_AIN7_SHIFT                     (7U)
#define SCT_INPUT_AIN7(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN7_SHIFT)) & SCT_INPUT_AIN7_MASK)
#define SCT_INPUT_AIN8_MASK                      (0x100U)
#define SCT_INPUT_AIN8_SHIFT                     (8U)
#define SCT_INPUT_AIN8(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN8_SHIFT)) & SCT_INPUT_AIN8_MASK)
#define SCT_INPUT_AIN9_MASK                      (0x200U)
#define SCT_INPUT_AIN9_SHIFT                     (9U)
#define SCT_INPUT_AIN9(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN9_SHIFT)) & SCT_INPUT_AIN9_MASK)
#define SCT_INPUT_AIN10_MASK                     (0x400U)
#define SCT_INPUT_AIN10_SHIFT                    (10U)
#define SCT_INPUT_AIN10(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN10_SHIFT)) & SCT_INPUT_AIN10_MASK)
#define SCT_INPUT_AIN11_MASK                     (0x800U)
#define SCT_INPUT_AIN11_SHIFT                    (11U)
#define SCT_INPUT_AIN11(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN11_SHIFT)) & SCT_INPUT_AIN11_MASK)
#define SCT_INPUT_AIN12_MASK                     (0x1000U)
#define SCT_INPUT_AIN12_SHIFT                    (12U)
#define SCT_INPUT_AIN12(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN12_SHIFT)) & SCT_INPUT_AIN12_MASK)
#define SCT_INPUT_AIN13_MASK                     (0x2000U)
#define SCT_INPUT_AIN13_SHIFT                    (13U)
#define SCT_INPUT_AIN13(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN13_SHIFT)) & SCT_INPUT_AIN13_MASK)
#define SCT_INPUT_AIN14_MASK                     (0x4000U)
#define SCT_INPUT_AIN14_SHIFT                    (14U)
#define SCT_INPUT_AIN14(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN14_SHIFT)) & SCT_INPUT_AIN14_MASK)
#define SCT_INPUT_AIN15_MASK                     (0x8000U)
#define SCT_INPUT_AIN15_SHIFT                    (15U)
#define SCT_INPUT_AIN15(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN15_SHIFT)) & SCT_INPUT_AIN15_MASK)
#define SCT_INPUT_SIN0_MASK                      (0x10000U)
#define SCT_INPUT_SIN0_SHIFT                     (16U)
#define SCT_INPUT_SIN0(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN0_SHIFT)) & SCT_INPUT_SIN0_MASK)
#define SCT_INPUT_SIN1_MASK                      (0x20000U)
#define SCT_INPUT_SIN1_SHIFT                     (17U)
#define SCT_INPUT_SIN1(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN1_SHIFT)) & SCT_INPUT_SIN1_MASK)
#define SCT_INPUT_SIN2_MASK                      (0x40000U)
#define SCT_INPUT_SIN2_SHIFT                     (18U)
#define SCT_INPUT_SIN2(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN2_SHIFT)) & SCT_INPUT_SIN2_MASK)
#define SCT_INPUT_SIN3_MASK                      (0x80000U)
#define SCT_INPUT_SIN3_SHIFT                     (19U)
#define SCT_INPUT_SIN3(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN3_SHIFT)) & SCT_INPUT_SIN3_MASK)
#define SCT_INPUT_SIN4_MASK                      (0x100000U)
#define SCT_INPUT_SIN4_SHIFT                     (20U)
#define SCT_INPUT_SIN4(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN4_SHIFT)) & SCT_INPUT_SIN4_MASK)
#define SCT_INPUT_SIN5_MASK                      (0x200000U)
#define SCT_INPUT_SIN5_SHIFT                     (21U)
#define SCT_INPUT_SIN5(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN5_SHIFT)) & SCT_INPUT_SIN5_MASK)
#define SCT_INPUT_SIN6_MASK                      (0x400000U)
#define SCT_INPUT_SIN6_SHIFT                     (22U)
#define SCT_INPUT_SIN6(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN6_SHIFT)) & SCT_INPUT_SIN6_MASK)
#define SCT_INPUT_SIN7_MASK                      (0x800000U)
#define SCT_INPUT_SIN7_SHIFT                     (23U)
#define SCT_INPUT_SIN7(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN7_SHIFT)) & SCT_INPUT_SIN7_MASK)
#define SCT_INPUT_SIN8_MASK                      (0x1000000U)
#define SCT_INPUT_SIN8_SHIFT                     (24U)
#define SCT_INPUT_SIN8(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN8_SHIFT)) & SCT_INPUT_SIN8_MASK)
#define SCT_INPUT_SIN9_MASK                      (0x2000000U)
#define SCT_INPUT_SIN9_SHIFT                     (25U)
#define SCT_INPUT_SIN9(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN9_SHIFT)) & SCT_INPUT_SIN9_MASK)
#define SCT_INPUT_SIN10_MASK                     (0x4000000U)
#define SCT_INPUT_SIN10_SHIFT                    (26U)
#define SCT_INPUT_SIN10(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN10_SHIFT)) & SCT_INPUT_SIN10_MASK)
#define SCT_INPUT_SIN11_MASK                     (0x8000000U)
#define SCT_INPUT_SIN11_SHIFT                    (27U)
#define SCT_INPUT_SIN11(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN11_SHIFT)) & SCT_INPUT_SIN11_MASK)
#define SCT_INPUT_SIN12_MASK                     (0x10000000U)
#define SCT_INPUT_SIN12_SHIFT                    (28U)
#define SCT_INPUT_SIN12(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN12_SHIFT)) & SCT_INPUT_SIN12_MASK)
#define SCT_INPUT_SIN13_MASK                     (0x20000000U)
#define SCT_INPUT_SIN13_SHIFT                    (29U)
#define SCT_INPUT_SIN13(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN13_SHIFT)) & SCT_INPUT_SIN13_MASK)
#define SCT_INPUT_SIN14_MASK                     (0x40000000U)
#define SCT_INPUT_SIN14_SHIFT                    (30U)
#define SCT_INPUT_SIN14(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN14_SHIFT)) & SCT_INPUT_SIN14_MASK)
#define SCT_INPUT_SIN15_MASK                     (0x80000000U)
#define SCT_INPUT_SIN15_SHIFT                    (31U)
#define SCT_INPUT_SIN15(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN15_SHIFT)) & SCT_INPUT_SIN15_MASK)

/*! @name REGMODE - SCT match/capture mode register */
#define SCT_REGMODE_REGMOD_L_MASK                (0xFFFFU)
#define SCT_REGMODE_REGMOD_L_SHIFT               (0U)
#define SCT_REGMODE_REGMOD_L(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_REGMODE_REGMOD_L_SHIFT)) & SCT_REGMODE_REGMOD_L_MASK)
#define SCT_REGMODE_REGMOD_H_MASK                (0xFFFF0000U)
#define SCT_REGMODE_REGMOD_H_SHIFT               (16U)
#define SCT_REGMODE_REGMOD_H(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_REGMODE_REGMOD_H_SHIFT)) & SCT_REGMODE_REGMOD_H_MASK)

/*! @name OUTPUT - SCT output register */
#define SCT_OUTPUT_OUT_MASK                      (0xFFFFU)
#define SCT_OUTPUT_OUT_SHIFT                     (0U)
#define SCT_OUTPUT_OUT(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUT_OUT_SHIFT)) & SCT_OUTPUT_OUT_MASK)

/*! @name OUTPUTDIRCTRL - SCT output counter direction control register */
#define SCT_OUTPUTDIRCTRL_SETCLR0_MASK           (0x3U)
#define SCT_OUTPUTDIRCTRL_SETCLR0_SHIFT          (0U)
#define SCT_OUTPUTDIRCTRL_SETCLR0(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR0_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR0_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR1_MASK           (0xCU)
#define SCT_OUTPUTDIRCTRL_SETCLR1_SHIFT          (2U)
#define SCT_OUTPUTDIRCTRL_SETCLR1(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR1_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR1_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR2_MASK           (0x30U)
#define SCT_OUTPUTDIRCTRL_SETCLR2_SHIFT          (4U)
#define SCT_OUTPUTDIRCTRL_SETCLR2(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR2_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR2_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR3_MASK           (0xC0U)
#define SCT_OUTPUTDIRCTRL_SETCLR3_SHIFT          (6U)
#define SCT_OUTPUTDIRCTRL_SETCLR3(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR3_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR3_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR4_MASK           (0x300U)
#define SCT_OUTPUTDIRCTRL_SETCLR4_SHIFT          (8U)
#define SCT_OUTPUTDIRCTRL_SETCLR4(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR4_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR4_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR5_MASK           (0xC00U)
#define SCT_OUTPUTDIRCTRL_SETCLR5_SHIFT          (10U)
#define SCT_OUTPUTDIRCTRL_SETCLR5(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR5_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR5_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR6_MASK           (0x3000U)
#define SCT_OUTPUTDIRCTRL_SETCLR6_SHIFT          (12U)
#define SCT_OUTPUTDIRCTRL_SETCLR6(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR6_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR6_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR7_MASK           (0xC000U)
#define SCT_OUTPUTDIRCTRL_SETCLR7_SHIFT          (14U)
#define SCT_OUTPUTDIRCTRL_SETCLR7(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR7_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR7_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR8_MASK           (0x30000U)
#define SCT_OUTPUTDIRCTRL_SETCLR8_SHIFT          (16U)
#define SCT_OUTPUTDIRCTRL_SETCLR8(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR8_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR8_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR9_MASK           (0xC0000U)
#define SCT_OUTPUTDIRCTRL_SETCLR9_SHIFT          (18U)
#define SCT_OUTPUTDIRCTRL_SETCLR9(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR9_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR9_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR10_MASK          (0x300000U)
#define SCT_OUTPUTDIRCTRL_SETCLR10_SHIFT         (20U)
#define SCT_OUTPUTDIRCTRL_SETCLR10(x)            (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR10_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR10_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR11_MASK          (0xC00000U)
#define SCT_OUTPUTDIRCTRL_SETCLR11_SHIFT         (22U)
#define SCT_OUTPUTDIRCTRL_SETCLR11(x)            (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR11_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR11_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR12_MASK          (0x3000000U)
#define SCT_OUTPUTDIRCTRL_SETCLR12_SHIFT         (24U)
#define SCT_OUTPUTDIRCTRL_SETCLR12(x)            (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR12_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR12_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR13_MASK          (0xC000000U)
#define SCT_OUTPUTDIRCTRL_SETCLR13_SHIFT         (26U)
#define SCT_OUTPUTDIRCTRL_SETCLR13(x)            (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR13_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR13_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR14_MASK          (0x30000000U)
#define SCT_OUTPUTDIRCTRL_SETCLR14_SHIFT         (28U)
#define SCT_OUTPUTDIRCTRL_SETCLR14(x)            (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR14_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR14_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR15_MASK          (0xC0000000U)
#define SCT_OUTPUTDIRCTRL_SETCLR15_SHIFT         (30U)
#define SCT_OUTPUTDIRCTRL_SETCLR15(x)            (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR15_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR15_MASK)

/*! @name RES - SCT conflict resolution register */
#define SCT_RES_O0RES_MASK                       (0x3U)
#define SCT_RES_O0RES_SHIFT                      (0U)
#define SCT_RES_O0RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O0RES_SHIFT)) & SCT_RES_O0RES_MASK)
#define SCT_RES_O1RES_MASK                       (0xCU)
#define SCT_RES_O1RES_SHIFT                      (2U)
#define SCT_RES_O1RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O1RES_SHIFT)) & SCT_RES_O1RES_MASK)
#define SCT_RES_O2RES_MASK                       (0x30U)
#define SCT_RES_O2RES_SHIFT                      (4U)
#define SCT_RES_O2RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O2RES_SHIFT)) & SCT_RES_O2RES_MASK)
#define SCT_RES_O3RES_MASK                       (0xC0U)
#define SCT_RES_O3RES_SHIFT                      (6U)
#define SCT_RES_O3RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O3RES_SHIFT)) & SCT_RES_O3RES_MASK)
#define SCT_RES_O4RES_MASK                       (0x300U)
#define SCT_RES_O4RES_SHIFT                      (8U)
#define SCT_RES_O4RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O4RES_SHIFT)) & SCT_RES_O4RES_MASK)
#define SCT_RES_O5RES_MASK                       (0xC00U)
#define SCT_RES_O5RES_SHIFT                      (10U)
#define SCT_RES_O5RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O5RES_SHIFT)) & SCT_RES_O5RES_MASK)
#define SCT_RES_O6RES_MASK                       (0x3000U)
#define SCT_RES_O6RES_SHIFT                      (12U)
#define SCT_RES_O6RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O6RES_SHIFT)) & SCT_RES_O6RES_MASK)
#define SCT_RES_O7RES_MASK                       (0xC000U)
#define SCT_RES_O7RES_SHIFT                      (14U)
#define SCT_RES_O7RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O7RES_SHIFT)) & SCT_RES_O7RES_MASK)
#define SCT_RES_O8RES_MASK                       (0x30000U)
#define SCT_RES_O8RES_SHIFT                      (16U)
#define SCT_RES_O8RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O8RES_SHIFT)) & SCT_RES_O8RES_MASK)
#define SCT_RES_O9RES_MASK                       (0xC0000U)
#define SCT_RES_O9RES_SHIFT                      (18U)
#define SCT_RES_O9RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O9RES_SHIFT)) & SCT_RES_O9RES_MASK)
#define SCT_RES_O10RES_MASK                      (0x300000U)
#define SCT_RES_O10RES_SHIFT                     (20U)
#define SCT_RES_O10RES(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_RES_O10RES_SHIFT)) & SCT_RES_O10RES_MASK)
#define SCT_RES_O11RES_MASK                      (0xC00000U)
#define SCT_RES_O11RES_SHIFT                     (22U)
#define SCT_RES_O11RES(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_RES_O11RES_SHIFT)) & SCT_RES_O11RES_MASK)
#define SCT_RES_O12RES_MASK                      (0x3000000U)
#define SCT_RES_O12RES_SHIFT                     (24U)
#define SCT_RES_O12RES(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_RES_O12RES_SHIFT)) & SCT_RES_O12RES_MASK)
#define SCT_RES_O13RES_MASK                      (0xC000000U)
#define SCT_RES_O13RES_SHIFT                     (26U)
#define SCT_RES_O13RES(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_RES_O13RES_SHIFT)) & SCT_RES_O13RES_MASK)
#define SCT_RES_O14RES_MASK                      (0x30000000U)
#define SCT_RES_O14RES_SHIFT                     (28U)
#define SCT_RES_O14RES(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_RES_O14RES_SHIFT)) & SCT_RES_O14RES_MASK)
#define SCT_RES_O15RES_MASK                      (0xC0000000U)
#define SCT_RES_O15RES_SHIFT                     (30U)
#define SCT_RES_O15RES(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_RES_O15RES_SHIFT)) & SCT_RES_O15RES_MASK)

/*! @name DMA0REQUEST - SCT DMA request 0 register */
#define SCT_DMA0REQUEST_DEV_0_MASK               (0xFFFFU)
#define SCT_DMA0REQUEST_DEV_0_SHIFT              (0U)
#define SCT_DMA0REQUEST_DEV_0(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_DMA0REQUEST_DEV_0_SHIFT)) & SCT_DMA0REQUEST_DEV_0_MASK)
#define SCT_DMA0REQUEST_DRL0_MASK                (0x40000000U)
#define SCT_DMA0REQUEST_DRL0_SHIFT               (30U)
#define SCT_DMA0REQUEST_DRL0(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_DMA0REQUEST_DRL0_SHIFT)) & SCT_DMA0REQUEST_DRL0_MASK)
#define SCT_DMA0REQUEST_DRQ0_MASK                (0x80000000U)
#define SCT_DMA0REQUEST_DRQ0_SHIFT               (31U)
#define SCT_DMA0REQUEST_DRQ0(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_DMA0REQUEST_DRQ0_SHIFT)) & SCT_DMA0REQUEST_DRQ0_MASK)

/*! @name DMA1REQUEST - SCT DMA request 1 register */
#define SCT_DMA1REQUEST_DEV_1_MASK               (0xFFFFU)
#define SCT_DMA1REQUEST_DEV_1_SHIFT              (0U)
#define SCT_DMA1REQUEST_DEV_1(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_DMA1REQUEST_DEV_1_SHIFT)) & SCT_DMA1REQUEST_DEV_1_MASK)
#define SCT_DMA1REQUEST_DRL1_MASK                (0x40000000U)
#define SCT_DMA1REQUEST_DRL1_SHIFT               (30U)
#define SCT_DMA1REQUEST_DRL1(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_DMA1REQUEST_DRL1_SHIFT)) & SCT_DMA1REQUEST_DRL1_MASK)
#define SCT_DMA1REQUEST_DRQ1_MASK                (0x80000000U)
#define SCT_DMA1REQUEST_DRQ1_SHIFT               (31U)
#define SCT_DMA1REQUEST_DRQ1(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_DMA1REQUEST_DRQ1_SHIFT)) & SCT_DMA1REQUEST_DRQ1_MASK)

/*! @name EVEN - SCT event interrupt enable register */
#define SCT_EVEN_IEN_MASK                        (0xFFFFU)
#define SCT_EVEN_IEN_SHIFT                       (0U)
#define SCT_EVEN_IEN(x)                          (((uint32_t)(((uint32_t)(x)) << SCT_EVEN_IEN_SHIFT)) & SCT_EVEN_IEN_MASK)

/*! @name EVFLAG - SCT event flag register */
#define SCT_EVFLAG_FLAG_MASK                     (0xFFFFU)
#define SCT_EVFLAG_FLAG_SHIFT                    (0U)
#define SCT_EVFLAG_FLAG(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_EVFLAG_FLAG_SHIFT)) & SCT_EVFLAG_FLAG_MASK)

/*! @name CONEN - SCT conflict interrupt enable register */
#define SCT_CONEN_NCEN_MASK                      (0xFFFFU)
#define SCT_CONEN_NCEN_SHIFT                     (0U)
#define SCT_CONEN_NCEN(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_CONEN_NCEN_SHIFT)) & SCT_CONEN_NCEN_MASK)

/*! @name CONFLAG - SCT conflict flag register */
#define SCT_CONFLAG_NCFLAG_MASK                  (0xFFFFU)
#define SCT_CONFLAG_NCFLAG_SHIFT                 (0U)
#define SCT_CONFLAG_NCFLAG(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_CONFLAG_NCFLAG_SHIFT)) & SCT_CONFLAG_NCFLAG_MASK)
#define SCT_CONFLAG_BUSERRL_MASK                 (0x40000000U)
#define SCT_CONFLAG_BUSERRL_SHIFT                (30U)
#define SCT_CONFLAG_BUSERRL(x)                   (((uint32_t)(((uint32_t)(x)) << SCT_CONFLAG_BUSERRL_SHIFT)) & SCT_CONFLAG_BUSERRL_MASK)
#define SCT_CONFLAG_BUSERRH_MASK                 (0x80000000U)
#define SCT_CONFLAG_BUSERRH_SHIFT                (31U)
#define SCT_CONFLAG_BUSERRH(x)                   (((uint32_t)(((uint32_t)(x)) << SCT_CONFLAG_BUSERRH_SHIFT)) & SCT_CONFLAG_BUSERRH_MASK)

/*! @name SCTCAP - SCT capture register of capture channel */
#define SCT_SCTCAP_CAPn_L_MASK                   (0xFFFFU)
#define SCT_SCTCAP_CAPn_L_SHIFT                  (0U)
#define SCT_SCTCAP_CAPn_L(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_SCTCAP_CAPn_L_SHIFT)) & SCT_SCTCAP_CAPn_L_MASK)
#define SCT_SCTCAP_CAPn_H_MASK                   (0xFFFF0000U)
#define SCT_SCTCAP_CAPn_H_SHIFT                  (16U)
#define SCT_SCTCAP_CAPn_H(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_SCTCAP_CAPn_H_SHIFT)) & SCT_SCTCAP_CAPn_H_MASK)

/* The count of SCT_SCTCAP */
#define SCT_SCTCAP_COUNT                         (10U)

/*! @name SCTMATCH - SCT match value register of match channels */
#define SCT_SCTMATCH_MATCHn_L_MASK               (0xFFFFU)
#define SCT_SCTMATCH_MATCHn_L_SHIFT              (0U)
#define SCT_SCTMATCH_MATCHn_L(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_SCTMATCH_MATCHn_L_SHIFT)) & SCT_SCTMATCH_MATCHn_L_MASK)
#define SCT_SCTMATCH_MATCHn_H_MASK               (0xFFFF0000U)
#define SCT_SCTMATCH_MATCHn_H_SHIFT              (16U)
#define SCT_SCTMATCH_MATCHn_H(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_SCTMATCH_MATCHn_H_SHIFT)) & SCT_SCTMATCH_MATCHn_H_MASK)

/* The count of SCT_SCTMATCH */
#define SCT_SCTMATCH_COUNT                       (10U)

/*! @name SCTCAPCTRL - SCT capture control register */
#define SCT_SCTCAPCTRL_CAPCONn_L_MASK            (0xFFFFU)
#define SCT_SCTCAPCTRL_CAPCONn_L_SHIFT           (0U)
#define SCT_SCTCAPCTRL_CAPCONn_L(x)              (((uint32_t)(((uint32_t)(x)) << SCT_SCTCAPCTRL_CAPCONn_L_SHIFT)) & SCT_SCTCAPCTRL_CAPCONn_L_MASK)
#define SCT_SCTCAPCTRL_CAPCONn_H_MASK            (0xFFFF0000U)
#define SCT_SCTCAPCTRL_CAPCONn_H_SHIFT           (16U)
#define SCT_SCTCAPCTRL_CAPCONn_H(x)              (((uint32_t)(((uint32_t)(x)) << SCT_SCTCAPCTRL_CAPCONn_H_SHIFT)) & SCT_SCTCAPCTRL_CAPCONn_H_MASK)

/* The count of SCT_SCTCAPCTRL */
#define SCT_SCTCAPCTRL_COUNT                     (10U)

/*! @name SCTMATCHREL - SCT match reload value register */
#define SCT_SCTMATCHREL_RELOADn_L_MASK           (0xFFFFU)
#define SCT_SCTMATCHREL_RELOADn_L_SHIFT          (0U)
#define SCT_SCTMATCHREL_RELOADn_L(x)             (((uint32_t)(((uint32_t)(x)) << SCT_SCTMATCHREL_RELOADn_L_SHIFT)) & SCT_SCTMATCHREL_RELOADn_L_MASK)
#define SCT_SCTMATCHREL_RELOADn_H_MASK           (0xFFFF0000U)
#define SCT_SCTMATCHREL_RELOADn_H_SHIFT          (16U)
#define SCT_SCTMATCHREL_RELOADn_H(x)             (((uint32_t)(((uint32_t)(x)) << SCT_SCTMATCHREL_RELOADn_H_SHIFT)) & SCT_SCTMATCHREL_RELOADn_H_MASK)

/* The count of SCT_SCTMATCHREL */
#define SCT_SCTMATCHREL_COUNT                    (10U)

/*! @name EVENT_STATE - SCT event state register 0 */
#define SCT_EVENT_STATE_STATEMSKn_MASK           (0xFFFFU)
#define SCT_EVENT_STATE_STATEMSKn_SHIFT          (0U)
#define SCT_EVENT_STATE_STATEMSKn(x)             (((uint32_t)(((uint32_t)(x)) << SCT_EVENT_STATE_STATEMSKn_SHIFT)) & SCT_EVENT_STATE_STATEMSKn_MASK)

/* The count of SCT_EVENT_STATE */
#define SCT_EVENT_STATE_COUNT                    (10U)

/*! @name EVENT_CTRL - SCT event control register 0 */
#define SCT_EVENT_CTRL_MATCHSEL_MASK             (0xFU)
#define SCT_EVENT_CTRL_MATCHSEL_SHIFT            (0U)
#define SCT_EVENT_CTRL_MATCHSEL(x)               (((uint32_t)(((uint32_t)(x)) << SCT_EVENT_CTRL_MATCHSEL_SHIFT)) & SCT_EVENT_CTRL_MATCHSEL_MASK)
#define SCT_EVENT_CTRL_HEVENT_MASK               (0x10U)
#define SCT_EVENT_CTRL_HEVENT_SHIFT              (4U)
#define SCT_EVENT_CTRL_HEVENT(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_EVENT_CTRL_HEVENT_SHIFT)) & SCT_EVENT_CTRL_HEVENT_MASK)
#define SCT_EVENT_CTRL_OUTSEL_MASK               (0x20U)
#define SCT_EVENT_CTRL_OUTSEL_SHIFT              (5U)
#define SCT_EVENT_CTRL_OUTSEL(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_EVENT_CTRL_OUTSEL_SHIFT)) & SCT_EVENT_CTRL_OUTSEL_MASK)
#define SCT_EVENT_CTRL_IOSEL_MASK                (0x3C0U)
#define SCT_EVENT_CTRL_IOSEL_SHIFT               (6U)
#define SCT_EVENT_CTRL_IOSEL(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_EVENT_CTRL_IOSEL_SHIFT)) & SCT_EVENT_CTRL_IOSEL_MASK)
#define SCT_EVENT_CTRL_IOCOND_MASK               (0xC00U)
#define SCT_EVENT_CTRL_IOCOND_SHIFT              (10U)
#define SCT_EVENT_CTRL_IOCOND(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_EVENT_CTRL_IOCOND_SHIFT)) & SCT_EVENT_CTRL_IOCOND_MASK)
#define SCT_EVENT_CTRL_COMBMODE_MASK             (0x3000U)
#define SCT_EVENT_CTRL_COMBMODE_SHIFT            (12U)
#define SCT_EVENT_CTRL_COMBMODE(x)               (((uint32_t)(((uint32_t)(x)) << SCT_EVENT_CTRL_COMBMODE_SHIFT)) & SCT_EVENT_CTRL_COMBMODE_MASK)
#define SCT_EVENT_CTRL_STATELD_MASK              (0x4000U)
#define SCT_EVENT_CTRL_STATELD_SHIFT             (14U)
#define SCT_EVENT_CTRL_STATELD(x)                (((uint32_t)(((uint32_t)(x)) << SCT_EVENT_CTRL_STATELD_SHIFT)) & SCT_EVENT_CTRL_STATELD_MASK)
#define SCT_EVENT_CTRL_STATEV_MASK               (0xF8000U)
#define SCT_EVENT_CTRL_STATEV_SHIFT              (15U)
#define SCT_EVENT_CTRL_STATEV(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_EVENT_CTRL_STATEV_SHIFT)) & SCT_EVENT_CTRL_STATEV_MASK)
#define SCT_EVENT_CTRL_MATCHMEM_MASK             (0x100000U)
#define SCT_EVENT_CTRL_MATCHMEM_SHIFT            (20U)
#define SCT_EVENT_CTRL_MATCHMEM(x)               (((uint32_t)(((uint32_t)(x)) << SCT_EVENT_CTRL_MATCHMEM_SHIFT)) & SCT_EVENT_CTRL_MATCHMEM_MASK)
#define SCT_EVENT_CTRL_DIRECTION_MASK            (0x600000U)
#define SCT_EVENT_CTRL_DIRECTION_SHIFT           (21U)
#define SCT_EVENT_CTRL_DIRECTION(x)              (((uint32_t)(((uint32_t)(x)) << SCT_EVENT_CTRL_DIRECTION_SHIFT)) & SCT_EVENT_CTRL_DIRECTION_MASK)

/* The count of SCT_EVENT_CTRL */
#define SCT_EVENT_CTRL_COUNT                     (10U)

/*! @name OUT_SET - SCT output 0 set register */
#define SCT_OUT_SET_SET_MASK                     (0xFFFFU)
#define SCT_OUT_SET_SET_SHIFT                    (0U)
#define SCT_OUT_SET_SET(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_OUT_SET_SET_SHIFT)) & SCT_OUT_SET_SET_MASK)

/* The count of SCT_OUT_SET */
#define SCT_OUT_SET_COUNT                        (10U)

/*! @name OUT_CLR - SCT output 0 clear register */
#define SCT_OUT_CLR_CLR_MASK                     (0xFFFFU)
#define SCT_OUT_CLR_CLR_SHIFT                    (0U)
#define SCT_OUT_CLR_CLR(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_OUT_CLR_CLR_SHIFT)) & SCT_OUT_CLR_CLR_MASK)

/* The count of SCT_OUT_CLR */
#define SCT_OUT_CLR_COUNT                        (10U)


/*!
 * @}
 */ /* end of group SCT_Register_Masks */


/* SCT - Peripheral instance base addresses */
/** Peripheral SCT0 base address */
#define SCT0_BASE                                (0x40085000u)
/** Peripheral SCT0 base pointer */
#define SCT0                                     ((SCT_Type *)SCT0_BASE)
/** Array initializer of SCT peripheral base addresses */
#define SCT_BASE_ADDRS                           { SCT0_BASE }
/** Array initializer of SCT peripheral base pointers */
#define SCT_BASE_PTRS                            { SCT0 }
/** Interrupt vectors for the SCT peripheral type */
#define SCT_IRQS                                 { SCT0_IRQn }

/*!
 * @}
 */ /* end of group SCT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SDIF Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SDIF_Peripheral_Access_Layer SDIF Peripheral Access Layer
 * @{
 */

/** SDIF - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< Control register, offset: 0x0 */
  __IO uint32_t PWREN;                             /**< Power Enable register, offset: 0x4 */
  __IO uint32_t CLKDIV;                            /**< Clock Divider register, offset: 0x8 */
       uint8_t RESERVED_0[4];
  __IO uint32_t CLKENA;                            /**< Clock Enable register, offset: 0x10 */
  __IO uint32_t TMOUT;                             /**< Time-out register, offset: 0x14 */
  __IO uint32_t CTYPE;                             /**< Card Type register, offset: 0x18 */
  __IO uint32_t BLKSIZ;                            /**< Block Size register, offset: 0x1C */
  __IO uint32_t BYTCNT;                            /**< Byte Count register, offset: 0x20 */
  __IO uint32_t INTMASK;                           /**< Interrupt Mask register, offset: 0x24 */
  __IO uint32_t CMDARG;                            /**< Command Argument register, offset: 0x28 */
  __IO uint32_t CMD;                               /**< Command register, offset: 0x2C */
  __IO uint32_t RESP[4];                           /**< Response register, array offset: 0x30, array step: 0x4 */
  __IO uint32_t MINTSTS;                           /**< Masked Interrupt Status register, offset: 0x40 */
  __IO uint32_t RINTSTS;                           /**< Raw Interrupt Status register, offset: 0x44 */
  __IO uint32_t STATUS;                            /**< Status register, offset: 0x48 */
  __IO uint32_t FIFOTH;                            /**< FIFO Threshold Watermark register, offset: 0x4C */
  __IO uint32_t CDETECT;                           /**< Card Detect register, offset: 0x50 */
  __IO uint32_t WRTPRT;                            /**< Write Protect register, offset: 0x54 */
       uint8_t RESERVED_1[4];
  __IO uint32_t TCBCNT;                            /**< Transferred CIU Card Byte Count register, offset: 0x5C */
  __IO uint32_t TBBCNT;                            /**< Transferred Host to BIU-FIFO Byte Count register, offset: 0x60 */
  __IO uint32_t DEBNCE;                            /**< Debounce Count register, offset: 0x64 */
       uint8_t RESERVED_2[16];
  __IO uint32_t RST_N;                             /**< Hardware Reset, offset: 0x78 */
       uint8_t RESERVED_3[4];
  __IO uint32_t BMOD;                              /**< Bus Mode register, offset: 0x80 */
  __IO uint32_t PLDMND;                            /**< Poll Demand register, offset: 0x84 */
  __IO uint32_t DBADDR;                            /**< Descriptor List Base Address register, offset: 0x88 */
  __IO uint32_t IDSTS;                             /**< Internal DMAC Status register, offset: 0x8C */
  __IO uint32_t IDINTEN;                           /**< Internal DMAC Interrupt Enable register, offset: 0x90 */
  __IO uint32_t DSCADDR;                           /**< Current Host Descriptor Address register, offset: 0x94 */
  __IO uint32_t BUFADDR;                           /**< Current Buffer Descriptor Address register, offset: 0x98 */
       uint8_t RESERVED_4[100];
  __IO uint32_t CARDTHRCTL;                        /**< Card Threshold Control, offset: 0x100 */
  __IO uint32_t BACKENDPWR;                        /**< Power control, offset: 0x104 */
       uint8_t RESERVED_5[248];
  __IO uint32_t FIFO[64];                          /**< SDIF FIFO, array offset: 0x200, array step: 0x4 */
} SDIF_Type;

/* ----------------------------------------------------------------------------
   -- SDIF Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SDIF_Register_Masks SDIF Register Masks
 * @{
 */

/*! @name CTRL - Control register */
#define SDIF_CTRL_CONTROLLER_RESET_MASK          (0x1U)
#define SDIF_CTRL_CONTROLLER_RESET_SHIFT         (0U)
#define SDIF_CTRL_CONTROLLER_RESET(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_CONTROLLER_RESET_SHIFT)) & SDIF_CTRL_CONTROLLER_RESET_MASK)
#define SDIF_CTRL_FIFO_RESET_MASK                (0x2U)
#define SDIF_CTRL_FIFO_RESET_SHIFT               (1U)
#define SDIF_CTRL_FIFO_RESET(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_FIFO_RESET_SHIFT)) & SDIF_CTRL_FIFO_RESET_MASK)
#define SDIF_CTRL_DMA_RESET_MASK                 (0x4U)
#define SDIF_CTRL_DMA_RESET_SHIFT                (2U)
#define SDIF_CTRL_DMA_RESET(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_DMA_RESET_SHIFT)) & SDIF_CTRL_DMA_RESET_MASK)
#define SDIF_CTRL_INT_ENABLE_MASK                (0x10U)
#define SDIF_CTRL_INT_ENABLE_SHIFT               (4U)
#define SDIF_CTRL_INT_ENABLE(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_INT_ENABLE_SHIFT)) & SDIF_CTRL_INT_ENABLE_MASK)
#define SDIF_CTRL_READ_WAIT_MASK                 (0x40U)
#define SDIF_CTRL_READ_WAIT_SHIFT                (6U)
#define SDIF_CTRL_READ_WAIT(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_READ_WAIT_SHIFT)) & SDIF_CTRL_READ_WAIT_MASK)
#define SDIF_CTRL_SEND_IRQ_RESPONSE_MASK         (0x80U)
#define SDIF_CTRL_SEND_IRQ_RESPONSE_SHIFT        (7U)
#define SDIF_CTRL_SEND_IRQ_RESPONSE(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_SEND_IRQ_RESPONSE_SHIFT)) & SDIF_CTRL_SEND_IRQ_RESPONSE_MASK)
#define SDIF_CTRL_ABORT_READ_DATA_MASK           (0x100U)
#define SDIF_CTRL_ABORT_READ_DATA_SHIFT          (8U)
#define SDIF_CTRL_ABORT_READ_DATA(x)             (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_ABORT_READ_DATA_SHIFT)) & SDIF_CTRL_ABORT_READ_DATA_MASK)
#define SDIF_CTRL_SEND_CCSD_MASK                 (0x200U)
#define SDIF_CTRL_SEND_CCSD_SHIFT                (9U)
#define SDIF_CTRL_SEND_CCSD(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_SEND_CCSD_SHIFT)) & SDIF_CTRL_SEND_CCSD_MASK)
#define SDIF_CTRL_SEND_AUTO_STOP_CCSD_MASK       (0x400U)
#define SDIF_CTRL_SEND_AUTO_STOP_CCSD_SHIFT      (10U)
#define SDIF_CTRL_SEND_AUTO_STOP_CCSD(x)         (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_SEND_AUTO_STOP_CCSD_SHIFT)) & SDIF_CTRL_SEND_AUTO_STOP_CCSD_MASK)
#define SDIF_CTRL_CEATA_DEVICE_INTERRUPT_STATUS_MASK (0x800U)
#define SDIF_CTRL_CEATA_DEVICE_INTERRUPT_STATUS_SHIFT (11U)
#define SDIF_CTRL_CEATA_DEVICE_INTERRUPT_STATUS(x) (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_CEATA_DEVICE_INTERRUPT_STATUS_SHIFT)) & SDIF_CTRL_CEATA_DEVICE_INTERRUPT_STATUS_MASK)
#define SDIF_CTRL_CARD_VOLTAGE_A0_MASK           (0x10000U)
#define SDIF_CTRL_CARD_VOLTAGE_A0_SHIFT          (16U)
#define SDIF_CTRL_CARD_VOLTAGE_A0(x)             (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_CARD_VOLTAGE_A0_SHIFT)) & SDIF_CTRL_CARD_VOLTAGE_A0_MASK)
#define SDIF_CTRL_CARD_VOLTAGE_A1_MASK           (0x20000U)
#define SDIF_CTRL_CARD_VOLTAGE_A1_SHIFT          (17U)
#define SDIF_CTRL_CARD_VOLTAGE_A1(x)             (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_CARD_VOLTAGE_A1_SHIFT)) & SDIF_CTRL_CARD_VOLTAGE_A1_MASK)
#define SDIF_CTRL_CARD_VOLTAGE_A2_MASK           (0x40000U)
#define SDIF_CTRL_CARD_VOLTAGE_A2_SHIFT          (18U)
#define SDIF_CTRL_CARD_VOLTAGE_A2(x)             (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_CARD_VOLTAGE_A2_SHIFT)) & SDIF_CTRL_CARD_VOLTAGE_A2_MASK)
#define SDIF_CTRL_USE_INTERNAL_DMAC_MASK         (0x2000000U)
#define SDIF_CTRL_USE_INTERNAL_DMAC_SHIFT        (25U)
#define SDIF_CTRL_USE_INTERNAL_DMAC(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_CTRL_USE_INTERNAL_DMAC_SHIFT)) & SDIF_CTRL_USE_INTERNAL_DMAC_MASK)

/*! @name PWREN - Power Enable register */
#define SDIF_PWREN_POWER_ENABLE_MASK             (0x1U)
#define SDIF_PWREN_POWER_ENABLE_SHIFT            (0U)
#define SDIF_PWREN_POWER_ENABLE(x)               (((uint32_t)(((uint32_t)(x)) << SDIF_PWREN_POWER_ENABLE_SHIFT)) & SDIF_PWREN_POWER_ENABLE_MASK)

/*! @name CLKDIV - Clock Divider register */
#define SDIF_CLKDIV_CLK_DIVIDER0_MASK            (0xFFU)
#define SDIF_CLKDIV_CLK_DIVIDER0_SHIFT           (0U)
#define SDIF_CLKDIV_CLK_DIVIDER0(x)              (((uint32_t)(((uint32_t)(x)) << SDIF_CLKDIV_CLK_DIVIDER0_SHIFT)) & SDIF_CLKDIV_CLK_DIVIDER0_MASK)

/*! @name CLKENA - Clock Enable register */
#define SDIF_CLKENA_CCLK_ENABLE_MASK             (0x1U)
#define SDIF_CLKENA_CCLK_ENABLE_SHIFT            (0U)
#define SDIF_CLKENA_CCLK_ENABLE(x)               (((uint32_t)(((uint32_t)(x)) << SDIF_CLKENA_CCLK_ENABLE_SHIFT)) & SDIF_CLKENA_CCLK_ENABLE_MASK)
#define SDIF_CLKENA_CCLK_LOW_POWER_MASK          (0x10000U)
#define SDIF_CLKENA_CCLK_LOW_POWER_SHIFT         (16U)
#define SDIF_CLKENA_CCLK_LOW_POWER(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_CLKENA_CCLK_LOW_POWER_SHIFT)) & SDIF_CLKENA_CCLK_LOW_POWER_MASK)

/*! @name TMOUT - Time-out register */
#define SDIF_TMOUT_RESPONSE_TIMEOUT_MASK         (0xFFU)
#define SDIF_TMOUT_RESPONSE_TIMEOUT_SHIFT        (0U)
#define SDIF_TMOUT_RESPONSE_TIMEOUT(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_TMOUT_RESPONSE_TIMEOUT_SHIFT)) & SDIF_TMOUT_RESPONSE_TIMEOUT_MASK)
#define SDIF_TMOUT_DATA_TIMEOUT_MASK             (0xFFFFFF00U)
#define SDIF_TMOUT_DATA_TIMEOUT_SHIFT            (8U)
#define SDIF_TMOUT_DATA_TIMEOUT(x)               (((uint32_t)(((uint32_t)(x)) << SDIF_TMOUT_DATA_TIMEOUT_SHIFT)) & SDIF_TMOUT_DATA_TIMEOUT_MASK)

/*! @name CTYPE - Card Type register */
#define SDIF_CTYPE_CARD_WIDTH0_MASK              (0x1U)
#define SDIF_CTYPE_CARD_WIDTH0_SHIFT             (0U)
#define SDIF_CTYPE_CARD_WIDTH0(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_CTYPE_CARD_WIDTH0_SHIFT)) & SDIF_CTYPE_CARD_WIDTH0_MASK)
#define SDIF_CTYPE_CARD_WIDTH1_MASK              (0x10000U)
#define SDIF_CTYPE_CARD_WIDTH1_SHIFT             (16U)
#define SDIF_CTYPE_CARD_WIDTH1(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_CTYPE_CARD_WIDTH1_SHIFT)) & SDIF_CTYPE_CARD_WIDTH1_MASK)

/*! @name BLKSIZ - Block Size register */
#define SDIF_BLKSIZ_BLOCK_SIZE_MASK              (0xFFFFU)
#define SDIF_BLKSIZ_BLOCK_SIZE_SHIFT             (0U)
#define SDIF_BLKSIZ_BLOCK_SIZE(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_BLKSIZ_BLOCK_SIZE_SHIFT)) & SDIF_BLKSIZ_BLOCK_SIZE_MASK)

/*! @name BYTCNT - Byte Count register */
#define SDIF_BYTCNT_BYTE_COUNT_MASK              (0xFFFFFFFFU)
#define SDIF_BYTCNT_BYTE_COUNT_SHIFT             (0U)
#define SDIF_BYTCNT_BYTE_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_BYTCNT_BYTE_COUNT_SHIFT)) & SDIF_BYTCNT_BYTE_COUNT_MASK)

/*! @name INTMASK - Interrupt Mask register */
#define SDIF_INTMASK_CDET_MASK                   (0x1U)
#define SDIF_INTMASK_CDET_SHIFT                  (0U)
#define SDIF_INTMASK_CDET(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_CDET_SHIFT)) & SDIF_INTMASK_CDET_MASK)
#define SDIF_INTMASK_RE_MASK                     (0x2U)
#define SDIF_INTMASK_RE_SHIFT                    (1U)
#define SDIF_INTMASK_RE(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_RE_SHIFT)) & SDIF_INTMASK_RE_MASK)
#define SDIF_INTMASK_CDONE_MASK                  (0x4U)
#define SDIF_INTMASK_CDONE_SHIFT                 (2U)
#define SDIF_INTMASK_CDONE(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_CDONE_SHIFT)) & SDIF_INTMASK_CDONE_MASK)
#define SDIF_INTMASK_DTO_MASK                    (0x8U)
#define SDIF_INTMASK_DTO_SHIFT                   (3U)
#define SDIF_INTMASK_DTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_DTO_SHIFT)) & SDIF_INTMASK_DTO_MASK)
#define SDIF_INTMASK_TXDR_MASK                   (0x10U)
#define SDIF_INTMASK_TXDR_SHIFT                  (4U)
#define SDIF_INTMASK_TXDR(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_TXDR_SHIFT)) & SDIF_INTMASK_TXDR_MASK)
#define SDIF_INTMASK_RXDR_MASK                   (0x20U)
#define SDIF_INTMASK_RXDR_SHIFT                  (5U)
#define SDIF_INTMASK_RXDR(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_RXDR_SHIFT)) & SDIF_INTMASK_RXDR_MASK)
#define SDIF_INTMASK_RCRC_MASK                   (0x40U)
#define SDIF_INTMASK_RCRC_SHIFT                  (6U)
#define SDIF_INTMASK_RCRC(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_RCRC_SHIFT)) & SDIF_INTMASK_RCRC_MASK)
#define SDIF_INTMASK_DCRC_MASK                   (0x80U)
#define SDIF_INTMASK_DCRC_SHIFT                  (7U)
#define SDIF_INTMASK_DCRC(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_DCRC_SHIFT)) & SDIF_INTMASK_DCRC_MASK)
#define SDIF_INTMASK_RTO_MASK                    (0x100U)
#define SDIF_INTMASK_RTO_SHIFT                   (8U)
#define SDIF_INTMASK_RTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_RTO_SHIFT)) & SDIF_INTMASK_RTO_MASK)
#define SDIF_INTMASK_DRTO_MASK                   (0x200U)
#define SDIF_INTMASK_DRTO_SHIFT                  (9U)
#define SDIF_INTMASK_DRTO(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_DRTO_SHIFT)) & SDIF_INTMASK_DRTO_MASK)
#define SDIF_INTMASK_HTO_MASK                    (0x400U)
#define SDIF_INTMASK_HTO_SHIFT                   (10U)
#define SDIF_INTMASK_HTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_HTO_SHIFT)) & SDIF_INTMASK_HTO_MASK)
#define SDIF_INTMASK_FRUN_MASK                   (0x800U)
#define SDIF_INTMASK_FRUN_SHIFT                  (11U)
#define SDIF_INTMASK_FRUN(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_FRUN_SHIFT)) & SDIF_INTMASK_FRUN_MASK)
#define SDIF_INTMASK_HLE_MASK                    (0x1000U)
#define SDIF_INTMASK_HLE_SHIFT                   (12U)
#define SDIF_INTMASK_HLE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_HLE_SHIFT)) & SDIF_INTMASK_HLE_MASK)
#define SDIF_INTMASK_SBE_MASK                    (0x2000U)
#define SDIF_INTMASK_SBE_SHIFT                   (13U)
#define SDIF_INTMASK_SBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_SBE_SHIFT)) & SDIF_INTMASK_SBE_MASK)
#define SDIF_INTMASK_ACD_MASK                    (0x4000U)
#define SDIF_INTMASK_ACD_SHIFT                   (14U)
#define SDIF_INTMASK_ACD(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_ACD_SHIFT)) & SDIF_INTMASK_ACD_MASK)
#define SDIF_INTMASK_EBE_MASK                    (0x8000U)
#define SDIF_INTMASK_EBE_SHIFT                   (15U)
#define SDIF_INTMASK_EBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_EBE_SHIFT)) & SDIF_INTMASK_EBE_MASK)
#define SDIF_INTMASK_SDIO_INT_MASK_MASK          (0x10000U)
#define SDIF_INTMASK_SDIO_INT_MASK_SHIFT         (16U)
#define SDIF_INTMASK_SDIO_INT_MASK(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_INTMASK_SDIO_INT_MASK_SHIFT)) & SDIF_INTMASK_SDIO_INT_MASK_MASK)

/*! @name CMDARG - Command Argument register */
#define SDIF_CMDARG_CMD_ARG_MASK                 (0xFFFFFFFFU)
#define SDIF_CMDARG_CMD_ARG_SHIFT                (0U)
#define SDIF_CMDARG_CMD_ARG(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_CMDARG_CMD_ARG_SHIFT)) & SDIF_CMDARG_CMD_ARG_MASK)

/*! @name CMD - Command register */
#define SDIF_CMD_CMD_INDEX_MASK                  (0x3FU)
#define SDIF_CMD_CMD_INDEX_SHIFT                 (0U)
#define SDIF_CMD_CMD_INDEX(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_CMD_INDEX_SHIFT)) & SDIF_CMD_CMD_INDEX_MASK)
#define SDIF_CMD_RESPONSE_EXPECT_MASK            (0x40U)
#define SDIF_CMD_RESPONSE_EXPECT_SHIFT           (6U)
#define SDIF_CMD_RESPONSE_EXPECT(x)              (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_RESPONSE_EXPECT_SHIFT)) & SDIF_CMD_RESPONSE_EXPECT_MASK)
#define SDIF_CMD_RESPONSE_LENGTH_MASK            (0x80U)
#define SDIF_CMD_RESPONSE_LENGTH_SHIFT           (7U)
#define SDIF_CMD_RESPONSE_LENGTH(x)              (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_RESPONSE_LENGTH_SHIFT)) & SDIF_CMD_RESPONSE_LENGTH_MASK)
#define SDIF_CMD_CHECK_RESPONSE_CRC_MASK         (0x100U)
#define SDIF_CMD_CHECK_RESPONSE_CRC_SHIFT        (8U)
#define SDIF_CMD_CHECK_RESPONSE_CRC(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_CHECK_RESPONSE_CRC_SHIFT)) & SDIF_CMD_CHECK_RESPONSE_CRC_MASK)
#define SDIF_CMD_DATA_EXPECTED_MASK              (0x200U)
#define SDIF_CMD_DATA_EXPECTED_SHIFT             (9U)
#define SDIF_CMD_DATA_EXPECTED(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_DATA_EXPECTED_SHIFT)) & SDIF_CMD_DATA_EXPECTED_MASK)
#define SDIF_CMD_READ_WRITE_MASK                 (0x400U)
#define SDIF_CMD_READ_WRITE_SHIFT                (10U)
#define SDIF_CMD_READ_WRITE(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_READ_WRITE_SHIFT)) & SDIF_CMD_READ_WRITE_MASK)
#define SDIF_CMD_TRANSFER_MODE_MASK              (0x800U)
#define SDIF_CMD_TRANSFER_MODE_SHIFT             (11U)
#define SDIF_CMD_TRANSFER_MODE(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_TRANSFER_MODE_SHIFT)) & SDIF_CMD_TRANSFER_MODE_MASK)
#define SDIF_CMD_SEND_AUTO_STOP_MASK             (0x1000U)
#define SDIF_CMD_SEND_AUTO_STOP_SHIFT            (12U)
#define SDIF_CMD_SEND_AUTO_STOP(x)               (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_SEND_AUTO_STOP_SHIFT)) & SDIF_CMD_SEND_AUTO_STOP_MASK)
#define SDIF_CMD_WAIT_PRVDATA_COMPLETE_MASK      (0x2000U)
#define SDIF_CMD_WAIT_PRVDATA_COMPLETE_SHIFT     (13U)
#define SDIF_CMD_WAIT_PRVDATA_COMPLETE(x)        (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_WAIT_PRVDATA_COMPLETE_SHIFT)) & SDIF_CMD_WAIT_PRVDATA_COMPLETE_MASK)
#define SDIF_CMD_STOP_ABORT_CMD_MASK             (0x4000U)
#define SDIF_CMD_STOP_ABORT_CMD_SHIFT            (14U)
#define SDIF_CMD_STOP_ABORT_CMD(x)               (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_STOP_ABORT_CMD_SHIFT)) & SDIF_CMD_STOP_ABORT_CMD_MASK)
#define SDIF_CMD_SEND_INITIALIZATION_MASK        (0x8000U)
#define SDIF_CMD_SEND_INITIALIZATION_SHIFT       (15U)
#define SDIF_CMD_SEND_INITIALIZATION(x)          (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_SEND_INITIALIZATION_SHIFT)) & SDIF_CMD_SEND_INITIALIZATION_MASK)
#define SDIF_CMD_UPDATE_CLOCK_REGISTERS_ONLY_MASK (0x200000U)
#define SDIF_CMD_UPDATE_CLOCK_REGISTERS_ONLY_SHIFT (21U)
#define SDIF_CMD_UPDATE_CLOCK_REGISTERS_ONLY(x)  (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_UPDATE_CLOCK_REGISTERS_ONLY_SHIFT)) & SDIF_CMD_UPDATE_CLOCK_REGISTERS_ONLY_MASK)
#define SDIF_CMD_READ_CEATA_DEVICE_MASK          (0x400000U)
#define SDIF_CMD_READ_CEATA_DEVICE_SHIFT         (22U)
#define SDIF_CMD_READ_CEATA_DEVICE(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_READ_CEATA_DEVICE_SHIFT)) & SDIF_CMD_READ_CEATA_DEVICE_MASK)
#define SDIF_CMD_CCS_EXPECTED_MASK               (0x800000U)
#define SDIF_CMD_CCS_EXPECTED_SHIFT              (23U)
#define SDIF_CMD_CCS_EXPECTED(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_CCS_EXPECTED_SHIFT)) & SDIF_CMD_CCS_EXPECTED_MASK)
#define SDIF_CMD_ENABLE_BOOT_MASK                (0x1000000U)
#define SDIF_CMD_ENABLE_BOOT_SHIFT               (24U)
#define SDIF_CMD_ENABLE_BOOT(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_ENABLE_BOOT_SHIFT)) & SDIF_CMD_ENABLE_BOOT_MASK)
#define SDIF_CMD_EXPECT_BOOT_ACK_MASK            (0x2000000U)
#define SDIF_CMD_EXPECT_BOOT_ACK_SHIFT           (25U)
#define SDIF_CMD_EXPECT_BOOT_ACK(x)              (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_EXPECT_BOOT_ACK_SHIFT)) & SDIF_CMD_EXPECT_BOOT_ACK_MASK)
#define SDIF_CMD_DISABLE_BOOT_MASK               (0x4000000U)
#define SDIF_CMD_DISABLE_BOOT_SHIFT              (26U)
#define SDIF_CMD_DISABLE_BOOT(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_DISABLE_BOOT_SHIFT)) & SDIF_CMD_DISABLE_BOOT_MASK)
#define SDIF_CMD_BOOT_MODE_MASK                  (0x8000000U)
#define SDIF_CMD_BOOT_MODE_SHIFT                 (27U)
#define SDIF_CMD_BOOT_MODE(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_BOOT_MODE_SHIFT)) & SDIF_CMD_BOOT_MODE_MASK)
#define SDIF_CMD_VOLT_SWITCH_MASK                (0x10000000U)
#define SDIF_CMD_VOLT_SWITCH_SHIFT               (28U)
#define SDIF_CMD_VOLT_SWITCH(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_VOLT_SWITCH_SHIFT)) & SDIF_CMD_VOLT_SWITCH_MASK)
#define SDIF_CMD_USE_HOLD_REG_MASK               (0x20000000U)
#define SDIF_CMD_USE_HOLD_REG_SHIFT              (29U)
#define SDIF_CMD_USE_HOLD_REG(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_USE_HOLD_REG_SHIFT)) & SDIF_CMD_USE_HOLD_REG_MASK)
#define SDIF_CMD_START_CMD_MASK                  (0x80000000U)
#define SDIF_CMD_START_CMD_SHIFT                 (31U)
#define SDIF_CMD_START_CMD(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_CMD_START_CMD_SHIFT)) & SDIF_CMD_START_CMD_MASK)

/*! @name RESP - Response register */
#define SDIF_RESP_RESPONSE_MASK                  (0xFFFFFFFFU)
#define SDIF_RESP_RESPONSE_SHIFT                 (0U)
#define SDIF_RESP_RESPONSE(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_RESP_RESPONSE_SHIFT)) & SDIF_RESP_RESPONSE_MASK)

/* The count of SDIF_RESP */
#define SDIF_RESP_COUNT                          (4U)

/*! @name MINTSTS - Masked Interrupt Status register */
#define SDIF_MINTSTS_CDET_MASK                   (0x1U)
#define SDIF_MINTSTS_CDET_SHIFT                  (0U)
#define SDIF_MINTSTS_CDET(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_CDET_SHIFT)) & SDIF_MINTSTS_CDET_MASK)
#define SDIF_MINTSTS_RE_MASK                     (0x2U)
#define SDIF_MINTSTS_RE_SHIFT                    (1U)
#define SDIF_MINTSTS_RE(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_RE_SHIFT)) & SDIF_MINTSTS_RE_MASK)
#define SDIF_MINTSTS_CDONE_MASK                  (0x4U)
#define SDIF_MINTSTS_CDONE_SHIFT                 (2U)
#define SDIF_MINTSTS_CDONE(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_CDONE_SHIFT)) & SDIF_MINTSTS_CDONE_MASK)
#define SDIF_MINTSTS_DTO_MASK                    (0x8U)
#define SDIF_MINTSTS_DTO_SHIFT                   (3U)
#define SDIF_MINTSTS_DTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_DTO_SHIFT)) & SDIF_MINTSTS_DTO_MASK)
#define SDIF_MINTSTS_TXDR_MASK                   (0x10U)
#define SDIF_MINTSTS_TXDR_SHIFT                  (4U)
#define SDIF_MINTSTS_TXDR(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_TXDR_SHIFT)) & SDIF_MINTSTS_TXDR_MASK)
#define SDIF_MINTSTS_RXDR_MASK                   (0x20U)
#define SDIF_MINTSTS_RXDR_SHIFT                  (5U)
#define SDIF_MINTSTS_RXDR(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_RXDR_SHIFT)) & SDIF_MINTSTS_RXDR_MASK)
#define SDIF_MINTSTS_RCRC_MASK                   (0x40U)
#define SDIF_MINTSTS_RCRC_SHIFT                  (6U)
#define SDIF_MINTSTS_RCRC(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_RCRC_SHIFT)) & SDIF_MINTSTS_RCRC_MASK)
#define SDIF_MINTSTS_DCRC_MASK                   (0x80U)
#define SDIF_MINTSTS_DCRC_SHIFT                  (7U)
#define SDIF_MINTSTS_DCRC(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_DCRC_SHIFT)) & SDIF_MINTSTS_DCRC_MASK)
#define SDIF_MINTSTS_RTO_MASK                    (0x100U)
#define SDIF_MINTSTS_RTO_SHIFT                   (8U)
#define SDIF_MINTSTS_RTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_RTO_SHIFT)) & SDIF_MINTSTS_RTO_MASK)
#define SDIF_MINTSTS_DRTO_MASK                   (0x200U)
#define SDIF_MINTSTS_DRTO_SHIFT                  (9U)
#define SDIF_MINTSTS_DRTO(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_DRTO_SHIFT)) & SDIF_MINTSTS_DRTO_MASK)
#define SDIF_MINTSTS_HTO_MASK                    (0x400U)
#define SDIF_MINTSTS_HTO_SHIFT                   (10U)
#define SDIF_MINTSTS_HTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_HTO_SHIFT)) & SDIF_MINTSTS_HTO_MASK)
#define SDIF_MINTSTS_FRUN_MASK                   (0x800U)
#define SDIF_MINTSTS_FRUN_SHIFT                  (11U)
#define SDIF_MINTSTS_FRUN(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_FRUN_SHIFT)) & SDIF_MINTSTS_FRUN_MASK)
#define SDIF_MINTSTS_HLE_MASK                    (0x1000U)
#define SDIF_MINTSTS_HLE_SHIFT                   (12U)
#define SDIF_MINTSTS_HLE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_HLE_SHIFT)) & SDIF_MINTSTS_HLE_MASK)
#define SDIF_MINTSTS_SBE_MASK                    (0x2000U)
#define SDIF_MINTSTS_SBE_SHIFT                   (13U)
#define SDIF_MINTSTS_SBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_SBE_SHIFT)) & SDIF_MINTSTS_SBE_MASK)
#define SDIF_MINTSTS_ACD_MASK                    (0x4000U)
#define SDIF_MINTSTS_ACD_SHIFT                   (14U)
#define SDIF_MINTSTS_ACD(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_ACD_SHIFT)) & SDIF_MINTSTS_ACD_MASK)
#define SDIF_MINTSTS_EBE_MASK                    (0x8000U)
#define SDIF_MINTSTS_EBE_SHIFT                   (15U)
#define SDIF_MINTSTS_EBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_EBE_SHIFT)) & SDIF_MINTSTS_EBE_MASK)
#define SDIF_MINTSTS_SDIO_INTERRUPT_MASK         (0x10000U)
#define SDIF_MINTSTS_SDIO_INTERRUPT_SHIFT        (16U)
#define SDIF_MINTSTS_SDIO_INTERRUPT(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_MINTSTS_SDIO_INTERRUPT_SHIFT)) & SDIF_MINTSTS_SDIO_INTERRUPT_MASK)

/*! @name RINTSTS - Raw Interrupt Status register */
#define SDIF_RINTSTS_CDET_MASK                   (0x1U)
#define SDIF_RINTSTS_CDET_SHIFT                  (0U)
#define SDIF_RINTSTS_CDET(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_CDET_SHIFT)) & SDIF_RINTSTS_CDET_MASK)
#define SDIF_RINTSTS_RE_MASK                     (0x2U)
#define SDIF_RINTSTS_RE_SHIFT                    (1U)
#define SDIF_RINTSTS_RE(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_RE_SHIFT)) & SDIF_RINTSTS_RE_MASK)
#define SDIF_RINTSTS_CDONE_MASK                  (0x4U)
#define SDIF_RINTSTS_CDONE_SHIFT                 (2U)
#define SDIF_RINTSTS_CDONE(x)                    (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_CDONE_SHIFT)) & SDIF_RINTSTS_CDONE_MASK)
#define SDIF_RINTSTS_DTO_MASK                    (0x8U)
#define SDIF_RINTSTS_DTO_SHIFT                   (3U)
#define SDIF_RINTSTS_DTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_DTO_SHIFT)) & SDIF_RINTSTS_DTO_MASK)
#define SDIF_RINTSTS_TXDR_MASK                   (0x10U)
#define SDIF_RINTSTS_TXDR_SHIFT                  (4U)
#define SDIF_RINTSTS_TXDR(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_TXDR_SHIFT)) & SDIF_RINTSTS_TXDR_MASK)
#define SDIF_RINTSTS_RXDR_MASK                   (0x20U)
#define SDIF_RINTSTS_RXDR_SHIFT                  (5U)
#define SDIF_RINTSTS_RXDR(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_RXDR_SHIFT)) & SDIF_RINTSTS_RXDR_MASK)
#define SDIF_RINTSTS_RCRC_MASK                   (0x40U)
#define SDIF_RINTSTS_RCRC_SHIFT                  (6U)
#define SDIF_RINTSTS_RCRC(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_RCRC_SHIFT)) & SDIF_RINTSTS_RCRC_MASK)
#define SDIF_RINTSTS_DCRC_MASK                   (0x80U)
#define SDIF_RINTSTS_DCRC_SHIFT                  (7U)
#define SDIF_RINTSTS_DCRC(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_DCRC_SHIFT)) & SDIF_RINTSTS_DCRC_MASK)
#define SDIF_RINTSTS_RTO_BAR_MASK                (0x100U)
#define SDIF_RINTSTS_RTO_BAR_SHIFT               (8U)
#define SDIF_RINTSTS_RTO_BAR(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_RTO_BAR_SHIFT)) & SDIF_RINTSTS_RTO_BAR_MASK)
#define SDIF_RINTSTS_DRTO_BDS_MASK               (0x200U)
#define SDIF_RINTSTS_DRTO_BDS_SHIFT              (9U)
#define SDIF_RINTSTS_DRTO_BDS(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_DRTO_BDS_SHIFT)) & SDIF_RINTSTS_DRTO_BDS_MASK)
#define SDIF_RINTSTS_HTO_MASK                    (0x400U)
#define SDIF_RINTSTS_HTO_SHIFT                   (10U)
#define SDIF_RINTSTS_HTO(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_HTO_SHIFT)) & SDIF_RINTSTS_HTO_MASK)
#define SDIF_RINTSTS_FRUN_MASK                   (0x800U)
#define SDIF_RINTSTS_FRUN_SHIFT                  (11U)
#define SDIF_RINTSTS_FRUN(x)                     (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_FRUN_SHIFT)) & SDIF_RINTSTS_FRUN_MASK)
#define SDIF_RINTSTS_HLE_MASK                    (0x1000U)
#define SDIF_RINTSTS_HLE_SHIFT                   (12U)
#define SDIF_RINTSTS_HLE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_HLE_SHIFT)) & SDIF_RINTSTS_HLE_MASK)
#define SDIF_RINTSTS_SBE_MASK                    (0x2000U)
#define SDIF_RINTSTS_SBE_SHIFT                   (13U)
#define SDIF_RINTSTS_SBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_SBE_SHIFT)) & SDIF_RINTSTS_SBE_MASK)
#define SDIF_RINTSTS_ACD_MASK                    (0x4000U)
#define SDIF_RINTSTS_ACD_SHIFT                   (14U)
#define SDIF_RINTSTS_ACD(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_ACD_SHIFT)) & SDIF_RINTSTS_ACD_MASK)
#define SDIF_RINTSTS_EBE_MASK                    (0x8000U)
#define SDIF_RINTSTS_EBE_SHIFT                   (15U)
#define SDIF_RINTSTS_EBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_EBE_SHIFT)) & SDIF_RINTSTS_EBE_MASK)
#define SDIF_RINTSTS_SDIO_INTERRUPT_MASK         (0x10000U)
#define SDIF_RINTSTS_SDIO_INTERRUPT_SHIFT        (16U)
#define SDIF_RINTSTS_SDIO_INTERRUPT(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_RINTSTS_SDIO_INTERRUPT_SHIFT)) & SDIF_RINTSTS_SDIO_INTERRUPT_MASK)

/*! @name STATUS - Status register */
#define SDIF_STATUS_FIFO_RX_WATERMARK_MASK       (0x1U)
#define SDIF_STATUS_FIFO_RX_WATERMARK_SHIFT      (0U)
#define SDIF_STATUS_FIFO_RX_WATERMARK(x)         (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_FIFO_RX_WATERMARK_SHIFT)) & SDIF_STATUS_FIFO_RX_WATERMARK_MASK)
#define SDIF_STATUS_FIFO_TX_WATERMARK_MASK       (0x2U)
#define SDIF_STATUS_FIFO_TX_WATERMARK_SHIFT      (1U)
#define SDIF_STATUS_FIFO_TX_WATERMARK(x)         (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_FIFO_TX_WATERMARK_SHIFT)) & SDIF_STATUS_FIFO_TX_WATERMARK_MASK)
#define SDIF_STATUS_FIFO_EMPTY_MASK              (0x4U)
#define SDIF_STATUS_FIFO_EMPTY_SHIFT             (2U)
#define SDIF_STATUS_FIFO_EMPTY(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_FIFO_EMPTY_SHIFT)) & SDIF_STATUS_FIFO_EMPTY_MASK)
#define SDIF_STATUS_FIFO_FULL_MASK               (0x8U)
#define SDIF_STATUS_FIFO_FULL_SHIFT              (3U)
#define SDIF_STATUS_FIFO_FULL(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_FIFO_FULL_SHIFT)) & SDIF_STATUS_FIFO_FULL_MASK)
#define SDIF_STATUS_CMDFSMSTATES_MASK            (0xF0U)
#define SDIF_STATUS_CMDFSMSTATES_SHIFT           (4U)
#define SDIF_STATUS_CMDFSMSTATES(x)              (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_CMDFSMSTATES_SHIFT)) & SDIF_STATUS_CMDFSMSTATES_MASK)
#define SDIF_STATUS_DATA_3_STATUS_MASK           (0x100U)
#define SDIF_STATUS_DATA_3_STATUS_SHIFT          (8U)
#define SDIF_STATUS_DATA_3_STATUS(x)             (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_DATA_3_STATUS_SHIFT)) & SDIF_STATUS_DATA_3_STATUS_MASK)
#define SDIF_STATUS_DATA_BUSY_MASK               (0x200U)
#define SDIF_STATUS_DATA_BUSY_SHIFT              (9U)
#define SDIF_STATUS_DATA_BUSY(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_DATA_BUSY_SHIFT)) & SDIF_STATUS_DATA_BUSY_MASK)
#define SDIF_STATUS_DATA_STATE_MC_BUSY_MASK      (0x400U)
#define SDIF_STATUS_DATA_STATE_MC_BUSY_SHIFT     (10U)
#define SDIF_STATUS_DATA_STATE_MC_BUSY(x)        (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_DATA_STATE_MC_BUSY_SHIFT)) & SDIF_STATUS_DATA_STATE_MC_BUSY_MASK)
#define SDIF_STATUS_RESPONSE_INDEX_MASK          (0x1F800U)
#define SDIF_STATUS_RESPONSE_INDEX_SHIFT         (11U)
#define SDIF_STATUS_RESPONSE_INDEX(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_RESPONSE_INDEX_SHIFT)) & SDIF_STATUS_RESPONSE_INDEX_MASK)
#define SDIF_STATUS_FIFO_COUNT_MASK              (0x3FFE0000U)
#define SDIF_STATUS_FIFO_COUNT_SHIFT             (17U)
#define SDIF_STATUS_FIFO_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_FIFO_COUNT_SHIFT)) & SDIF_STATUS_FIFO_COUNT_MASK)
#define SDIF_STATUS_DMA_ACK_MASK                 (0x40000000U)
#define SDIF_STATUS_DMA_ACK_SHIFT                (30U)
#define SDIF_STATUS_DMA_ACK(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_DMA_ACK_SHIFT)) & SDIF_STATUS_DMA_ACK_MASK)
#define SDIF_STATUS_DMA_REQ_MASK                 (0x80000000U)
#define SDIF_STATUS_DMA_REQ_SHIFT                (31U)
#define SDIF_STATUS_DMA_REQ(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_STATUS_DMA_REQ_SHIFT)) & SDIF_STATUS_DMA_REQ_MASK)

/*! @name FIFOTH - FIFO Threshold Watermark register */
#define SDIF_FIFOTH_TX_WMARK_MASK                (0xFFFU)
#define SDIF_FIFOTH_TX_WMARK_SHIFT               (0U)
#define SDIF_FIFOTH_TX_WMARK(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_FIFOTH_TX_WMARK_SHIFT)) & SDIF_FIFOTH_TX_WMARK_MASK)
#define SDIF_FIFOTH_RX_WMARK_MASK                (0xFFF0000U)
#define SDIF_FIFOTH_RX_WMARK_SHIFT               (16U)
#define SDIF_FIFOTH_RX_WMARK(x)                  (((uint32_t)(((uint32_t)(x)) << SDIF_FIFOTH_RX_WMARK_SHIFT)) & SDIF_FIFOTH_RX_WMARK_MASK)
#define SDIF_FIFOTH_DMA_MTS_MASK                 (0x70000000U)
#define SDIF_FIFOTH_DMA_MTS_SHIFT                (28U)
#define SDIF_FIFOTH_DMA_MTS(x)                   (((uint32_t)(((uint32_t)(x)) << SDIF_FIFOTH_DMA_MTS_SHIFT)) & SDIF_FIFOTH_DMA_MTS_MASK)

/*! @name CDETECT - Card Detect register */
#define SDIF_CDETECT_CARD_DETECT_MASK            (0x1U)
#define SDIF_CDETECT_CARD_DETECT_SHIFT           (0U)
#define SDIF_CDETECT_CARD_DETECT(x)              (((uint32_t)(((uint32_t)(x)) << SDIF_CDETECT_CARD_DETECT_SHIFT)) & SDIF_CDETECT_CARD_DETECT_MASK)

/*! @name WRTPRT - Write Protect register */
#define SDIF_WRTPRT_WRITE_PROTECT_MASK           (0x1U)
#define SDIF_WRTPRT_WRITE_PROTECT_SHIFT          (0U)
#define SDIF_WRTPRT_WRITE_PROTECT(x)             (((uint32_t)(((uint32_t)(x)) << SDIF_WRTPRT_WRITE_PROTECT_SHIFT)) & SDIF_WRTPRT_WRITE_PROTECT_MASK)

/*! @name TCBCNT - Transferred CIU Card Byte Count register */
#define SDIF_TCBCNT_TRANS_CARD_BYTE_COUNT_MASK   (0xFFFFFFFFU)
#define SDIF_TCBCNT_TRANS_CARD_BYTE_COUNT_SHIFT  (0U)
#define SDIF_TCBCNT_TRANS_CARD_BYTE_COUNT(x)     (((uint32_t)(((uint32_t)(x)) << SDIF_TCBCNT_TRANS_CARD_BYTE_COUNT_SHIFT)) & SDIF_TCBCNT_TRANS_CARD_BYTE_COUNT_MASK)

/*! @name TBBCNT - Transferred Host to BIU-FIFO Byte Count register */
#define SDIF_TBBCNT_TRANS_FIFO_BYTE_COUNT_MASK   (0xFFFFFFFFU)
#define SDIF_TBBCNT_TRANS_FIFO_BYTE_COUNT_SHIFT  (0U)
#define SDIF_TBBCNT_TRANS_FIFO_BYTE_COUNT(x)     (((uint32_t)(((uint32_t)(x)) << SDIF_TBBCNT_TRANS_FIFO_BYTE_COUNT_SHIFT)) & SDIF_TBBCNT_TRANS_FIFO_BYTE_COUNT_MASK)

/*! @name DEBNCE - Debounce Count register */
#define SDIF_DEBNCE_DEBOUNCE_COUNT_MASK          (0xFFFFFFU)
#define SDIF_DEBNCE_DEBOUNCE_COUNT_SHIFT         (0U)
#define SDIF_DEBNCE_DEBOUNCE_COUNT(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_DEBNCE_DEBOUNCE_COUNT_SHIFT)) & SDIF_DEBNCE_DEBOUNCE_COUNT_MASK)

/*! @name RST_N - Hardware Reset */
#define SDIF_RST_N_CARD_RESET_MASK               (0x1U)
#define SDIF_RST_N_CARD_RESET_SHIFT              (0U)
#define SDIF_RST_N_CARD_RESET(x)                 (((uint32_t)(((uint32_t)(x)) << SDIF_RST_N_CARD_RESET_SHIFT)) & SDIF_RST_N_CARD_RESET_MASK)

/*! @name BMOD - Bus Mode register */
#define SDIF_BMOD_SWR_MASK                       (0x1U)
#define SDIF_BMOD_SWR_SHIFT                      (0U)
#define SDIF_BMOD_SWR(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_BMOD_SWR_SHIFT)) & SDIF_BMOD_SWR_MASK)
#define SDIF_BMOD_FB_MASK                        (0x2U)
#define SDIF_BMOD_FB_SHIFT                       (1U)
#define SDIF_BMOD_FB(x)                          (((uint32_t)(((uint32_t)(x)) << SDIF_BMOD_FB_SHIFT)) & SDIF_BMOD_FB_MASK)
#define SDIF_BMOD_DSL_MASK                       (0x7CU)
#define SDIF_BMOD_DSL_SHIFT                      (2U)
#define SDIF_BMOD_DSL(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_BMOD_DSL_SHIFT)) & SDIF_BMOD_DSL_MASK)
#define SDIF_BMOD_DE_MASK                        (0x80U)
#define SDIF_BMOD_DE_SHIFT                       (7U)
#define SDIF_BMOD_DE(x)                          (((uint32_t)(((uint32_t)(x)) << SDIF_BMOD_DE_SHIFT)) & SDIF_BMOD_DE_MASK)
#define SDIF_BMOD_PBL_MASK                       (0x700U)
#define SDIF_BMOD_PBL_SHIFT                      (8U)
#define SDIF_BMOD_PBL(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_BMOD_PBL_SHIFT)) & SDIF_BMOD_PBL_MASK)

/*! @name PLDMND - Poll Demand register */
#define SDIF_PLDMND_PD_MASK                      (0xFFFFFFFFU)
#define SDIF_PLDMND_PD_SHIFT                     (0U)
#define SDIF_PLDMND_PD(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_PLDMND_PD_SHIFT)) & SDIF_PLDMND_PD_MASK)

/*! @name DBADDR - Descriptor List Base Address register */
#define SDIF_DBADDR_SDL_MASK                     (0xFFFFFFFFU)
#define SDIF_DBADDR_SDL_SHIFT                    (0U)
#define SDIF_DBADDR_SDL(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_DBADDR_SDL_SHIFT)) & SDIF_DBADDR_SDL_MASK)

/*! @name IDSTS - Internal DMAC Status register */
#define SDIF_IDSTS_TI_MASK                       (0x1U)
#define SDIF_IDSTS_TI_SHIFT                      (0U)
#define SDIF_IDSTS_TI(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_TI_SHIFT)) & SDIF_IDSTS_TI_MASK)
#define SDIF_IDSTS_RI_MASK                       (0x2U)
#define SDIF_IDSTS_RI_SHIFT                      (1U)
#define SDIF_IDSTS_RI(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_RI_SHIFT)) & SDIF_IDSTS_RI_MASK)
#define SDIF_IDSTS_FBE_MASK                      (0x4U)
#define SDIF_IDSTS_FBE_SHIFT                     (2U)
#define SDIF_IDSTS_FBE(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_FBE_SHIFT)) & SDIF_IDSTS_FBE_MASK)
#define SDIF_IDSTS_DU_MASK                       (0x10U)
#define SDIF_IDSTS_DU_SHIFT                      (4U)
#define SDIF_IDSTS_DU(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_DU_SHIFT)) & SDIF_IDSTS_DU_MASK)
#define SDIF_IDSTS_CES_MASK                      (0x20U)
#define SDIF_IDSTS_CES_SHIFT                     (5U)
#define SDIF_IDSTS_CES(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_CES_SHIFT)) & SDIF_IDSTS_CES_MASK)
#define SDIF_IDSTS_NIS_MASK                      (0x100U)
#define SDIF_IDSTS_NIS_SHIFT                     (8U)
#define SDIF_IDSTS_NIS(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_NIS_SHIFT)) & SDIF_IDSTS_NIS_MASK)
#define SDIF_IDSTS_AIS_MASK                      (0x200U)
#define SDIF_IDSTS_AIS_SHIFT                     (9U)
#define SDIF_IDSTS_AIS(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_AIS_SHIFT)) & SDIF_IDSTS_AIS_MASK)
#define SDIF_IDSTS_EB_MASK                       (0x1C00U)
#define SDIF_IDSTS_EB_SHIFT                      (10U)
#define SDIF_IDSTS_EB(x)                         (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_EB_SHIFT)) & SDIF_IDSTS_EB_MASK)
#define SDIF_IDSTS_FSM_MASK                      (0x1E000U)
#define SDIF_IDSTS_FSM_SHIFT                     (13U)
#define SDIF_IDSTS_FSM(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_IDSTS_FSM_SHIFT)) & SDIF_IDSTS_FSM_MASK)

/*! @name IDINTEN - Internal DMAC Interrupt Enable register */
#define SDIF_IDINTEN_TI_MASK                     (0x1U)
#define SDIF_IDINTEN_TI_SHIFT                    (0U)
#define SDIF_IDINTEN_TI(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_TI_SHIFT)) & SDIF_IDINTEN_TI_MASK)
#define SDIF_IDINTEN_RI_MASK                     (0x2U)
#define SDIF_IDINTEN_RI_SHIFT                    (1U)
#define SDIF_IDINTEN_RI(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_RI_SHIFT)) & SDIF_IDINTEN_RI_MASK)
#define SDIF_IDINTEN_FBE_MASK                    (0x4U)
#define SDIF_IDINTEN_FBE_SHIFT                   (2U)
#define SDIF_IDINTEN_FBE(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_FBE_SHIFT)) & SDIF_IDINTEN_FBE_MASK)
#define SDIF_IDINTEN_DU_MASK                     (0x10U)
#define SDIF_IDINTEN_DU_SHIFT                    (4U)
#define SDIF_IDINTEN_DU(x)                       (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_DU_SHIFT)) & SDIF_IDINTEN_DU_MASK)
#define SDIF_IDINTEN_CES_MASK                    (0x20U)
#define SDIF_IDINTEN_CES_SHIFT                   (5U)
#define SDIF_IDINTEN_CES(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_CES_SHIFT)) & SDIF_IDINTEN_CES_MASK)
#define SDIF_IDINTEN_NIS_MASK                    (0x100U)
#define SDIF_IDINTEN_NIS_SHIFT                   (8U)
#define SDIF_IDINTEN_NIS(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_NIS_SHIFT)) & SDIF_IDINTEN_NIS_MASK)
#define SDIF_IDINTEN_AIS_MASK                    (0x200U)
#define SDIF_IDINTEN_AIS_SHIFT                   (9U)
#define SDIF_IDINTEN_AIS(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_IDINTEN_AIS_SHIFT)) & SDIF_IDINTEN_AIS_MASK)

/*! @name DSCADDR - Current Host Descriptor Address register */
#define SDIF_DSCADDR_HDA_MASK                    (0xFFFFFFFFU)
#define SDIF_DSCADDR_HDA_SHIFT                   (0U)
#define SDIF_DSCADDR_HDA(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_DSCADDR_HDA_SHIFT)) & SDIF_DSCADDR_HDA_MASK)

/*! @name BUFADDR - Current Buffer Descriptor Address register */
#define SDIF_BUFADDR_HBA_MASK                    (0xFFFFFFFFU)
#define SDIF_BUFADDR_HBA_SHIFT                   (0U)
#define SDIF_BUFADDR_HBA(x)                      (((uint32_t)(((uint32_t)(x)) << SDIF_BUFADDR_HBA_SHIFT)) & SDIF_BUFADDR_HBA_MASK)

/*! @name CARDTHRCTL - Card Threshold Control */
#define SDIF_CARDTHRCTL_CARDRDTHREN_MASK         (0x1U)
#define SDIF_CARDTHRCTL_CARDRDTHREN_SHIFT        (0U)
#define SDIF_CARDTHRCTL_CARDRDTHREN(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_CARDTHRCTL_CARDRDTHREN_SHIFT)) & SDIF_CARDTHRCTL_CARDRDTHREN_MASK)
#define SDIF_CARDTHRCTL_BSYCLRINTEN_MASK         (0x2U)
#define SDIF_CARDTHRCTL_BSYCLRINTEN_SHIFT        (1U)
#define SDIF_CARDTHRCTL_BSYCLRINTEN(x)           (((uint32_t)(((uint32_t)(x)) << SDIF_CARDTHRCTL_BSYCLRINTEN_SHIFT)) & SDIF_CARDTHRCTL_BSYCLRINTEN_MASK)
#define SDIF_CARDTHRCTL_CARDTHRESHOLD_MASK       (0xFF0000U)
#define SDIF_CARDTHRCTL_CARDTHRESHOLD_SHIFT      (16U)
#define SDIF_CARDTHRCTL_CARDTHRESHOLD(x)         (((uint32_t)(((uint32_t)(x)) << SDIF_CARDTHRCTL_CARDTHRESHOLD_SHIFT)) & SDIF_CARDTHRCTL_CARDTHRESHOLD_MASK)

/*! @name BACKENDPWR - Power control */
#define SDIF_BACKENDPWR_BACKENDPWR_MASK          (0x1U)
#define SDIF_BACKENDPWR_BACKENDPWR_SHIFT         (0U)
#define SDIF_BACKENDPWR_BACKENDPWR(x)            (((uint32_t)(((uint32_t)(x)) << SDIF_BACKENDPWR_BACKENDPWR_SHIFT)) & SDIF_BACKENDPWR_BACKENDPWR_MASK)

/*! @name FIFO - SDIF FIFO */
#define SDIF_FIFO_DATA_MASK                      (0xFFFFFFFFU)
#define SDIF_FIFO_DATA_SHIFT                     (0U)
#define SDIF_FIFO_DATA(x)                        (((uint32_t)(((uint32_t)(x)) << SDIF_FIFO_DATA_SHIFT)) & SDIF_FIFO_DATA_MASK)

/* The count of SDIF_FIFO */
#define SDIF_FIFO_COUNT                          (64U)


/*!
 * @}
 */ /* end of group SDIF_Register_Masks */


/* SDIF - Peripheral instance base addresses */
/** Peripheral SDIF base address */
#define SDIF_BASE                                (0x4009B000u)
/** Peripheral SDIF base pointer */
#define SDIF                                     ((SDIF_Type *)SDIF_BASE)
/** Array initializer of SDIF peripheral base addresses */
#define SDIF_BASE_ADDRS                          { SDIF_BASE }
/** Array initializer of SDIF peripheral base pointers */
#define SDIF_BASE_PTRS                           { SDIF }
/** Interrupt vectors for the SDIF peripheral type */
#define SDIF_IRQS                                { SDIO_IRQn }

/*!
 * @}
 */ /* end of group SDIF_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SMARTCARD Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMARTCARD_Peripheral_Access_Layer SMARTCARD Peripheral Access Layer
 * @{
 */

/** SMARTCARD - Register Layout Typedef */
typedef struct {
  union {                                          /* offset: 0x0 */
    __IO uint32_t DLL;                               /**< Divisor Latch LSB, offset: 0x0 */
    __I  uint32_t RBR;                               /**< Receiver Buffer Register, offset: 0x0 */
    __O  uint32_t THR;                               /**< Transmit Holding Register, offset: 0x0 */
  };
  union {                                          /* offset: 0x4 */
    __IO uint32_t DLM;                               /**< Divisor Latch MSB, offset: 0x4 */
    __IO uint32_t IER;                               /**< Interrupt Enable Register, offset: 0x4 */
  };
  union {                                          /* offset: 0x8 */
    __O  uint32_t FCR;                               /**< FIFO Control Register, offset: 0x8 */
    __I  uint32_t IIR;                               /**< Interrupt ID Register, offset: 0x8 */
  };
  __IO uint32_t LCR;                               /**< Line Control Register, offset: 0xC */
       uint8_t RESERVED_0[4];
  __I  uint32_t LSR;                               /**< Line Status Register, offset: 0x14 */
       uint8_t RESERVED_1[4];
  __IO uint32_t SCR;                               /**< Scratch Pad Register, offset: 0x1C */
       uint8_t RESERVED_2[12];
  __IO uint32_t OSR;                               /**< Oversampling register, offset: 0x2C */
       uint8_t RESERVED_3[24];
  __IO uint32_t SCICTRL;                           /**< Smart Card Interface control register, offset: 0x48 */
} SMARTCARD_Type;

/* ----------------------------------------------------------------------------
   -- SMARTCARD Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMARTCARD_Register_Masks SMARTCARD Register Masks
 * @{
 */

/*! @name DLL - Divisor Latch LSB */
#define SMARTCARD_DLL_DLLSB_MASK                 (0xFFU)
#define SMARTCARD_DLL_DLLSB_SHIFT                (0U)
#define SMARTCARD_DLL_DLLSB(x)                   (((uint32_t)(((uint32_t)(x)) << SMARTCARD_DLL_DLLSB_SHIFT)) & SMARTCARD_DLL_DLLSB_MASK)

/*! @name RBR - Receiver Buffer Register */
#define SMARTCARD_RBR_RBR_MASK                   (0xFFU)
#define SMARTCARD_RBR_RBR_SHIFT                  (0U)
#define SMARTCARD_RBR_RBR(x)                     (((uint32_t)(((uint32_t)(x)) << SMARTCARD_RBR_RBR_SHIFT)) & SMARTCARD_RBR_RBR_MASK)

/*! @name THR - Transmit Holding Register */
#define SMARTCARD_THR_THR_MASK                   (0xFFU)
#define SMARTCARD_THR_THR_SHIFT                  (0U)
#define SMARTCARD_THR_THR(x)                     (((uint32_t)(((uint32_t)(x)) << SMARTCARD_THR_THR_SHIFT)) & SMARTCARD_THR_THR_MASK)

/*! @name DLM - Divisor Latch MSB */
#define SMARTCARD_DLM_DLMSB_MASK                 (0xFFU)
#define SMARTCARD_DLM_DLMSB_SHIFT                (0U)
#define SMARTCARD_DLM_DLMSB(x)                   (((uint32_t)(((uint32_t)(x)) << SMARTCARD_DLM_DLMSB_SHIFT)) & SMARTCARD_DLM_DLMSB_MASK)

/*! @name IER - Interrupt Enable Register */
#define SMARTCARD_IER_RBRIE_MASK                 (0x1U)
#define SMARTCARD_IER_RBRIE_SHIFT                (0U)
#define SMARTCARD_IER_RBRIE(x)                   (((uint32_t)(((uint32_t)(x)) << SMARTCARD_IER_RBRIE_SHIFT)) & SMARTCARD_IER_RBRIE_MASK)
#define SMARTCARD_IER_THREIE_MASK                (0x2U)
#define SMARTCARD_IER_THREIE_SHIFT               (1U)
#define SMARTCARD_IER_THREIE(x)                  (((uint32_t)(((uint32_t)(x)) << SMARTCARD_IER_THREIE_SHIFT)) & SMARTCARD_IER_THREIE_MASK)
#define SMARTCARD_IER_RXIE_MASK                  (0x4U)
#define SMARTCARD_IER_RXIE_SHIFT                 (2U)
#define SMARTCARD_IER_RXIE(x)                    (((uint32_t)(((uint32_t)(x)) << SMARTCARD_IER_RXIE_SHIFT)) & SMARTCARD_IER_RXIE_MASK)

/*! @name FCR - FIFO Control Register */
#define SMARTCARD_FCR_FIFOEN_MASK                (0x1U)
#define SMARTCARD_FCR_FIFOEN_SHIFT               (0U)
#define SMARTCARD_FCR_FIFOEN(x)                  (((uint32_t)(((uint32_t)(x)) << SMARTCARD_FCR_FIFOEN_SHIFT)) & SMARTCARD_FCR_FIFOEN_MASK)
#define SMARTCARD_FCR_RXFIFORES_MASK             (0x2U)
#define SMARTCARD_FCR_RXFIFORES_SHIFT            (1U)
#define SMARTCARD_FCR_RXFIFORES(x)               (((uint32_t)(((uint32_t)(x)) << SMARTCARD_FCR_RXFIFORES_SHIFT)) & SMARTCARD_FCR_RXFIFORES_MASK)
#define SMARTCARD_FCR_TXFIFORES_MASK             (0x4U)
#define SMARTCARD_FCR_TXFIFORES_SHIFT            (2U)
#define SMARTCARD_FCR_TXFIFORES(x)               (((uint32_t)(((uint32_t)(x)) << SMARTCARD_FCR_TXFIFORES_SHIFT)) & SMARTCARD_FCR_TXFIFORES_MASK)
#define SMARTCARD_FCR_DMAMODE_MASK               (0x8U)
#define SMARTCARD_FCR_DMAMODE_SHIFT              (3U)
#define SMARTCARD_FCR_DMAMODE(x)                 (((uint32_t)(((uint32_t)(x)) << SMARTCARD_FCR_DMAMODE_SHIFT)) & SMARTCARD_FCR_DMAMODE_MASK)
#define SMARTCARD_FCR_RXTRIGLVL_MASK             (0xC0U)
#define SMARTCARD_FCR_RXTRIGLVL_SHIFT            (6U)
#define SMARTCARD_FCR_RXTRIGLVL(x)               (((uint32_t)(((uint32_t)(x)) << SMARTCARD_FCR_RXTRIGLVL_SHIFT)) & SMARTCARD_FCR_RXTRIGLVL_MASK)

/*! @name IIR - Interrupt ID Register */
#define SMARTCARD_IIR_INTSTATUS_MASK             (0x1U)
#define SMARTCARD_IIR_INTSTATUS_SHIFT            (0U)
#define SMARTCARD_IIR_INTSTATUS(x)               (((uint32_t)(((uint32_t)(x)) << SMARTCARD_IIR_INTSTATUS_SHIFT)) & SMARTCARD_IIR_INTSTATUS_MASK)
#define SMARTCARD_IIR_INTID_MASK                 (0xEU)
#define SMARTCARD_IIR_INTID_SHIFT                (1U)
#define SMARTCARD_IIR_INTID(x)                   (((uint32_t)(((uint32_t)(x)) << SMARTCARD_IIR_INTID_SHIFT)) & SMARTCARD_IIR_INTID_MASK)
#define SMARTCARD_IIR_FIFOENABLE_MASK            (0xC0U)
#define SMARTCARD_IIR_FIFOENABLE_SHIFT           (6U)
#define SMARTCARD_IIR_FIFOENABLE(x)              (((uint32_t)(((uint32_t)(x)) << SMARTCARD_IIR_FIFOENABLE_SHIFT)) & SMARTCARD_IIR_FIFOENABLE_MASK)

/*! @name LCR - Line Control Register */
#define SMARTCARD_LCR_WLS_MASK                   (0x3U)
#define SMARTCARD_LCR_WLS_SHIFT                  (0U)
#define SMARTCARD_LCR_WLS(x)                     (((uint32_t)(((uint32_t)(x)) << SMARTCARD_LCR_WLS_SHIFT)) & SMARTCARD_LCR_WLS_MASK)
#define SMARTCARD_LCR_SBS_MASK                   (0x4U)
#define SMARTCARD_LCR_SBS_SHIFT                  (2U)
#define SMARTCARD_LCR_SBS(x)                     (((uint32_t)(((uint32_t)(x)) << SMARTCARD_LCR_SBS_SHIFT)) & SMARTCARD_LCR_SBS_MASK)
#define SMARTCARD_LCR_PE_MASK                    (0x8U)
#define SMARTCARD_LCR_PE_SHIFT                   (3U)
#define SMARTCARD_LCR_PE(x)                      (((uint32_t)(((uint32_t)(x)) << SMARTCARD_LCR_PE_SHIFT)) & SMARTCARD_LCR_PE_MASK)
#define SMARTCARD_LCR_PS_MASK                    (0x30U)
#define SMARTCARD_LCR_PS_SHIFT                   (4U)
#define SMARTCARD_LCR_PS(x)                      (((uint32_t)(((uint32_t)(x)) << SMARTCARD_LCR_PS_SHIFT)) & SMARTCARD_LCR_PS_MASK)
#define SMARTCARD_LCR_DLAB_MASK                  (0x80U)
#define SMARTCARD_LCR_DLAB_SHIFT                 (7U)
#define SMARTCARD_LCR_DLAB(x)                    (((uint32_t)(((uint32_t)(x)) << SMARTCARD_LCR_DLAB_SHIFT)) & SMARTCARD_LCR_DLAB_MASK)

/*! @name LSR - Line Status Register */
#define SMARTCARD_LSR_RDR_MASK                   (0x1U)
#define SMARTCARD_LSR_RDR_SHIFT                  (0U)
#define SMARTCARD_LSR_RDR(x)                     (((uint32_t)(((uint32_t)(x)) << SMARTCARD_LSR_RDR_SHIFT)) & SMARTCARD_LSR_RDR_MASK)
#define SMARTCARD_LSR_OE_MASK                    (0x2U)
#define SMARTCARD_LSR_OE_SHIFT                   (1U)
#define SMARTCARD_LSR_OE(x)                      (((uint32_t)(((uint32_t)(x)) << SMARTCARD_LSR_OE_SHIFT)) & SMARTCARD_LSR_OE_MASK)
#define SMARTCARD_LSR_PE_MASK                    (0x4U)
#define SMARTCARD_LSR_PE_SHIFT                   (2U)
#define SMARTCARD_LSR_PE(x)                      (((uint32_t)(((uint32_t)(x)) << SMARTCARD_LSR_PE_SHIFT)) & SMARTCARD_LSR_PE_MASK)
#define SMARTCARD_LSR_FE_MASK                    (0x8U)
#define SMARTCARD_LSR_FE_SHIFT                   (3U)
#define SMARTCARD_LSR_FE(x)                      (((uint32_t)(((uint32_t)(x)) << SMARTCARD_LSR_FE_SHIFT)) & SMARTCARD_LSR_FE_MASK)
#define SMARTCARD_LSR_THRE_MASK                  (0x20U)
#define SMARTCARD_LSR_THRE_SHIFT                 (5U)
#define SMARTCARD_LSR_THRE(x)                    (((uint32_t)(((uint32_t)(x)) << SMARTCARD_LSR_THRE_SHIFT)) & SMARTCARD_LSR_THRE_MASK)
#define SMARTCARD_LSR_TEMT_MASK                  (0x40U)
#define SMARTCARD_LSR_TEMT_SHIFT                 (6U)
#define SMARTCARD_LSR_TEMT(x)                    (((uint32_t)(((uint32_t)(x)) << SMARTCARD_LSR_TEMT_SHIFT)) & SMARTCARD_LSR_TEMT_MASK)
#define SMARTCARD_LSR_RXFE_MASK                  (0x80U)
#define SMARTCARD_LSR_RXFE_SHIFT                 (7U)
#define SMARTCARD_LSR_RXFE(x)                    (((uint32_t)(((uint32_t)(x)) << SMARTCARD_LSR_RXFE_SHIFT)) & SMARTCARD_LSR_RXFE_MASK)

/*! @name SCR - Scratch Pad Register */
#define SMARTCARD_SCR_PAD_MASK                   (0xFFU)
#define SMARTCARD_SCR_PAD_SHIFT                  (0U)
#define SMARTCARD_SCR_PAD(x)                     (((uint32_t)(((uint32_t)(x)) << SMARTCARD_SCR_PAD_SHIFT)) & SMARTCARD_SCR_PAD_MASK)

/*! @name OSR - Oversampling register */
#define SMARTCARD_OSR_OSFRAC_MASK                (0xEU)
#define SMARTCARD_OSR_OSFRAC_SHIFT               (1U)
#define SMARTCARD_OSR_OSFRAC(x)                  (((uint32_t)(((uint32_t)(x)) << SMARTCARD_OSR_OSFRAC_SHIFT)) & SMARTCARD_OSR_OSFRAC_MASK)
#define SMARTCARD_OSR_OSINT_MASK                 (0xF0U)
#define SMARTCARD_OSR_OSINT_SHIFT                (4U)
#define SMARTCARD_OSR_OSINT(x)                   (((uint32_t)(((uint32_t)(x)) << SMARTCARD_OSR_OSINT_SHIFT)) & SMARTCARD_OSR_OSINT_MASK)
#define SMARTCARD_OSR_FDINT_MASK                 (0x7F00U)
#define SMARTCARD_OSR_FDINT_SHIFT                (8U)
#define SMARTCARD_OSR_FDINT(x)                   (((uint32_t)(((uint32_t)(x)) << SMARTCARD_OSR_FDINT_SHIFT)) & SMARTCARD_OSR_FDINT_MASK)

/*! @name SCICTRL - Smart Card Interface control register */
#define SMARTCARD_SCICTRL_SCIEN_MASK             (0x1U)
#define SMARTCARD_SCICTRL_SCIEN_SHIFT            (0U)
#define SMARTCARD_SCICTRL_SCIEN(x)               (((uint32_t)(((uint32_t)(x)) << SMARTCARD_SCICTRL_SCIEN_SHIFT)) & SMARTCARD_SCICTRL_SCIEN_MASK)
#define SMARTCARD_SCICTRL_NACKDIS_MASK           (0x2U)
#define SMARTCARD_SCICTRL_NACKDIS_SHIFT          (1U)
#define SMARTCARD_SCICTRL_NACKDIS(x)             (((uint32_t)(((uint32_t)(x)) << SMARTCARD_SCICTRL_NACKDIS_SHIFT)) & SMARTCARD_SCICTRL_NACKDIS_MASK)
#define SMARTCARD_SCICTRL_PROTSEL_MASK           (0x4U)
#define SMARTCARD_SCICTRL_PROTSEL_SHIFT          (2U)
#define SMARTCARD_SCICTRL_PROTSEL(x)             (((uint32_t)(((uint32_t)(x)) << SMARTCARD_SCICTRL_PROTSEL_SHIFT)) & SMARTCARD_SCICTRL_PROTSEL_MASK)
#define SMARTCARD_SCICTRL_TXRETRY_MASK           (0xE0U)
#define SMARTCARD_SCICTRL_TXRETRY_SHIFT          (5U)
#define SMARTCARD_SCICTRL_TXRETRY(x)             (((uint32_t)(((uint32_t)(x)) << SMARTCARD_SCICTRL_TXRETRY_SHIFT)) & SMARTCARD_SCICTRL_TXRETRY_MASK)
#define SMARTCARD_SCICTRL_GUARDTIME_MASK         (0xFF00U)
#define SMARTCARD_SCICTRL_GUARDTIME_SHIFT        (8U)
#define SMARTCARD_SCICTRL_GUARDTIME(x)           (((uint32_t)(((uint32_t)(x)) << SMARTCARD_SCICTRL_GUARDTIME_SHIFT)) & SMARTCARD_SCICTRL_GUARDTIME_MASK)


/*!
 * @}
 */ /* end of group SMARTCARD_Register_Masks */


/* SMARTCARD - Peripheral instance base addresses */
/** Peripheral SMARTCARD0 base address */
#define SMARTCARD0_BASE                          (0x40036000u)
/** Peripheral SMARTCARD0 base pointer */
#define SMARTCARD0                               ((SMARTCARD_Type *)SMARTCARD0_BASE)
/** Peripheral SMARTCARD1 base address */
#define SMARTCARD1_BASE                          (0x40037000u)
/** Peripheral SMARTCARD1 base pointer */
#define SMARTCARD1                               ((SMARTCARD_Type *)SMARTCARD1_BASE)
/** Array initializer of SMARTCARD peripheral base addresses */
#define SMARTCARD_BASE_ADDRS                     { SMARTCARD0_BASE, SMARTCARD1_BASE }
/** Array initializer of SMARTCARD peripheral base pointers */
#define SMARTCARD_BASE_PTRS                      { SMARTCARD0, SMARTCARD1 }
/** Interrupt vectors for the SMARTCARD peripheral type */
#define SMARTCARD_IRQS                           { SMARTCARD0_IRQn, SMARTCARD1_IRQn }

/*!
 * @}
 */ /* end of group SMARTCARD_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SPI Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Peripheral_Access_Layer SPI Peripheral Access Layer
 * @{
 */

/** SPI - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[1024];
  __IO uint32_t CFG;                               /**< SPI Configuration register, offset: 0x400 */
  __IO uint32_t DLY;                               /**< SPI Delay register, offset: 0x404 */
  __IO uint32_t STAT;                              /**< SPI Status. Some status flags can be cleared by writing a 1 to that bit position., offset: 0x408 */
  __IO uint32_t INTENSET;                          /**< SPI Interrupt Enable read and Set. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set., offset: 0x40C */
  __O  uint32_t INTENCLR;                          /**< SPI Interrupt Enable Clear. Writing a 1 to any implemented bit position causes the corresponding bit in INTENSET to be cleared., offset: 0x410 */
       uint8_t RESERVED_1[16];
  __IO uint32_t DIV;                               /**< SPI clock Divider, offset: 0x424 */
  __I  uint32_t INTSTAT;                           /**< SPI Interrupt Status, offset: 0x428 */
       uint8_t RESERVED_2[2516];
  __IO uint32_t FIFOCFG;                           /**< FIFO configuration and enable register., offset: 0xE00 */
  __IO uint32_t FIFOSTAT;                          /**< FIFO status register., offset: 0xE04 */
  __IO uint32_t FIFOTRIG;                          /**< FIFO trigger settings for interrupt and DMA request., offset: 0xE08 */
       uint8_t RESERVED_3[4];
  __IO uint32_t FIFOINTENSET;                      /**< FIFO interrupt enable set (enable) and read register., offset: 0xE10 */
  __IO uint32_t FIFOINTENCLR;                      /**< FIFO interrupt enable clear (disable) and read register., offset: 0xE14 */
  __I  uint32_t FIFOINTSTAT;                       /**< FIFO interrupt status register., offset: 0xE18 */
       uint8_t RESERVED_4[4];
  __IO uint32_t FIFOWR;                            /**< FIFO write data., offset: 0xE20 */
       uint8_t RESERVED_5[12];
  __I  uint32_t FIFORD;                            /**< FIFO read data., offset: 0xE30 */
       uint8_t RESERVED_6[12];
  __I  uint32_t FIFORDNOPOP;                       /**< FIFO data read with no FIFO pop., offset: 0xE40 */
       uint8_t RESERVED_7[440];
  __I  uint32_t ID;                                /**< Peripheral identification register., offset: 0xFFC */
} SPI_Type;

/* ----------------------------------------------------------------------------
   -- SPI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Masks SPI Register Masks
 * @{
 */

/*! @name CFG - SPI Configuration register */
#define SPI_CFG_ENABLE_MASK                      (0x1U)
#define SPI_CFG_ENABLE_SHIFT                     (0U)
#define SPI_CFG_ENABLE(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_CFG_ENABLE_SHIFT)) & SPI_CFG_ENABLE_MASK)
#define SPI_CFG_MASTER_MASK                      (0x4U)
#define SPI_CFG_MASTER_SHIFT                     (2U)
#define SPI_CFG_MASTER(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_CFG_MASTER_SHIFT)) & SPI_CFG_MASTER_MASK)
#define SPI_CFG_LSBF_MASK                        (0x8U)
#define SPI_CFG_LSBF_SHIFT                       (3U)
#define SPI_CFG_LSBF(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CFG_LSBF_SHIFT)) & SPI_CFG_LSBF_MASK)
#define SPI_CFG_CPHA_MASK                        (0x10U)
#define SPI_CFG_CPHA_SHIFT                       (4U)
#define SPI_CFG_CPHA(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CFG_CPHA_SHIFT)) & SPI_CFG_CPHA_MASK)
#define SPI_CFG_CPOL_MASK                        (0x20U)
#define SPI_CFG_CPOL_SHIFT                       (5U)
#define SPI_CFG_CPOL(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CFG_CPOL_SHIFT)) & SPI_CFG_CPOL_MASK)
#define SPI_CFG_LOOP_MASK                        (0x80U)
#define SPI_CFG_LOOP_SHIFT                       (7U)
#define SPI_CFG_LOOP(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CFG_LOOP_SHIFT)) & SPI_CFG_LOOP_MASK)
#define SPI_CFG_SPOL0_MASK                       (0x100U)
#define SPI_CFG_SPOL0_SHIFT                      (8U)
#define SPI_CFG_SPOL0(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CFG_SPOL0_SHIFT)) & SPI_CFG_SPOL0_MASK)
#define SPI_CFG_SPOL1_MASK                       (0x200U)
#define SPI_CFG_SPOL1_SHIFT                      (9U)
#define SPI_CFG_SPOL1(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CFG_SPOL1_SHIFT)) & SPI_CFG_SPOL1_MASK)
#define SPI_CFG_SPOL2_MASK                       (0x400U)
#define SPI_CFG_SPOL2_SHIFT                      (10U)
#define SPI_CFG_SPOL2(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CFG_SPOL2_SHIFT)) & SPI_CFG_SPOL2_MASK)
#define SPI_CFG_SPOL3_MASK                       (0x800U)
#define SPI_CFG_SPOL3_SHIFT                      (11U)
#define SPI_CFG_SPOL3(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CFG_SPOL3_SHIFT)) & SPI_CFG_SPOL3_MASK)

/*! @name DLY - SPI Delay register */
#define SPI_DLY_PRE_DELAY_MASK                   (0xFU)
#define SPI_DLY_PRE_DELAY_SHIFT                  (0U)
#define SPI_DLY_PRE_DELAY(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_DLY_PRE_DELAY_SHIFT)) & SPI_DLY_PRE_DELAY_MASK)
#define SPI_DLY_POST_DELAY_MASK                  (0xF0U)
#define SPI_DLY_POST_DELAY_SHIFT                 (4U)
#define SPI_DLY_POST_DELAY(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_DLY_POST_DELAY_SHIFT)) & SPI_DLY_POST_DELAY_MASK)
#define SPI_DLY_FRAME_DELAY_MASK                 (0xF00U)
#define SPI_DLY_FRAME_DELAY_SHIFT                (8U)
#define SPI_DLY_FRAME_DELAY(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_DLY_FRAME_DELAY_SHIFT)) & SPI_DLY_FRAME_DELAY_MASK)
#define SPI_DLY_TRANSFER_DELAY_MASK              (0xF000U)
#define SPI_DLY_TRANSFER_DELAY_SHIFT             (12U)
#define SPI_DLY_TRANSFER_DELAY(x)                (((uint32_t)(((uint32_t)(x)) << SPI_DLY_TRANSFER_DELAY_SHIFT)) & SPI_DLY_TRANSFER_DELAY_MASK)

/*! @name STAT - SPI Status. Some status flags can be cleared by writing a 1 to that bit position. */
#define SPI_STAT_SSA_MASK                        (0x10U)
#define SPI_STAT_SSA_SHIFT                       (4U)
#define SPI_STAT_SSA(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_STAT_SSA_SHIFT)) & SPI_STAT_SSA_MASK)
#define SPI_STAT_SSD_MASK                        (0x20U)
#define SPI_STAT_SSD_SHIFT                       (5U)
#define SPI_STAT_SSD(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_STAT_SSD_SHIFT)) & SPI_STAT_SSD_MASK)
#define SPI_STAT_STALLED_MASK                    (0x40U)
#define SPI_STAT_STALLED_SHIFT                   (6U)
#define SPI_STAT_STALLED(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_STAT_STALLED_SHIFT)) & SPI_STAT_STALLED_MASK)
#define SPI_STAT_ENDTRANSFER_MASK                (0x80U)
#define SPI_STAT_ENDTRANSFER_SHIFT               (7U)
#define SPI_STAT_ENDTRANSFER(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_STAT_ENDTRANSFER_SHIFT)) & SPI_STAT_ENDTRANSFER_MASK)
#define SPI_STAT_MSTIDLE_MASK                    (0x100U)
#define SPI_STAT_MSTIDLE_SHIFT                   (8U)
#define SPI_STAT_MSTIDLE(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_STAT_MSTIDLE_SHIFT)) & SPI_STAT_MSTIDLE_MASK)

/*! @name INTENSET - SPI Interrupt Enable read and Set. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set. */
#define SPI_INTENSET_SSAEN_MASK                  (0x10U)
#define SPI_INTENSET_SSAEN_SHIFT                 (4U)
#define SPI_INTENSET_SSAEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_SSAEN_SHIFT)) & SPI_INTENSET_SSAEN_MASK)
#define SPI_INTENSET_SSDEN_MASK                  (0x20U)
#define SPI_INTENSET_SSDEN_SHIFT                 (5U)
#define SPI_INTENSET_SSDEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_SSDEN_SHIFT)) & SPI_INTENSET_SSDEN_MASK)
#define SPI_INTENSET_MSTIDLEEN_MASK              (0x100U)
#define SPI_INTENSET_MSTIDLEEN_SHIFT             (8U)
#define SPI_INTENSET_MSTIDLEEN(x)                (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_MSTIDLEEN_SHIFT)) & SPI_INTENSET_MSTIDLEEN_MASK)

/*! @name INTENCLR - SPI Interrupt Enable Clear. Writing a 1 to any implemented bit position causes the corresponding bit in INTENSET to be cleared. */
#define SPI_INTENCLR_SSAEN_MASK                  (0x10U)
#define SPI_INTENCLR_SSAEN_SHIFT                 (4U)
#define SPI_INTENCLR_SSAEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_SSAEN_SHIFT)) & SPI_INTENCLR_SSAEN_MASK)
#define SPI_INTENCLR_SSDEN_MASK                  (0x20U)
#define SPI_INTENCLR_SSDEN_SHIFT                 (5U)
#define SPI_INTENCLR_SSDEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_SSDEN_SHIFT)) & SPI_INTENCLR_SSDEN_MASK)
#define SPI_INTENCLR_MSTIDLE_MASK                (0x100U)
#define SPI_INTENCLR_MSTIDLE_SHIFT               (8U)
#define SPI_INTENCLR_MSTIDLE(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_MSTIDLE_SHIFT)) & SPI_INTENCLR_MSTIDLE_MASK)

/*! @name DIV - SPI clock Divider */
#define SPI_DIV_DIVVAL_MASK                      (0xFFFFU)
#define SPI_DIV_DIVVAL_SHIFT                     (0U)
#define SPI_DIV_DIVVAL(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_DIV_DIVVAL_SHIFT)) & SPI_DIV_DIVVAL_MASK)

/*! @name INTSTAT - SPI Interrupt Status */
#define SPI_INTSTAT_SSA_MASK                     (0x10U)
#define SPI_INTSTAT_SSA_SHIFT                    (4U)
#define SPI_INTSTAT_SSA(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_SSA_SHIFT)) & SPI_INTSTAT_SSA_MASK)
#define SPI_INTSTAT_SSD_MASK                     (0x20U)
#define SPI_INTSTAT_SSD_SHIFT                    (5U)
#define SPI_INTSTAT_SSD(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_SSD_SHIFT)) & SPI_INTSTAT_SSD_MASK)
#define SPI_INTSTAT_MSTIDLE_MASK                 (0x100U)
#define SPI_INTSTAT_MSTIDLE_SHIFT                (8U)
#define SPI_INTSTAT_MSTIDLE(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_MSTIDLE_SHIFT)) & SPI_INTSTAT_MSTIDLE_MASK)

/*! @name FIFOCFG - FIFO configuration and enable register. */
#define SPI_FIFOCFG_ENABLETX_MASK                (0x1U)
#define SPI_FIFOCFG_ENABLETX_SHIFT               (0U)
#define SPI_FIFOCFG_ENABLETX(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_ENABLETX_SHIFT)) & SPI_FIFOCFG_ENABLETX_MASK)
#define SPI_FIFOCFG_ENABLERX_MASK                (0x2U)
#define SPI_FIFOCFG_ENABLERX_SHIFT               (1U)
#define SPI_FIFOCFG_ENABLERX(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_ENABLERX_SHIFT)) & SPI_FIFOCFG_ENABLERX_MASK)
#define SPI_FIFOCFG_SIZE_MASK                    (0x30U)
#define SPI_FIFOCFG_SIZE_SHIFT                   (4U)
#define SPI_FIFOCFG_SIZE(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_SIZE_SHIFT)) & SPI_FIFOCFG_SIZE_MASK)
#define SPI_FIFOCFG_DMATX_MASK                   (0x1000U)
#define SPI_FIFOCFG_DMATX_SHIFT                  (12U)
#define SPI_FIFOCFG_DMATX(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_DMATX_SHIFT)) & SPI_FIFOCFG_DMATX_MASK)
#define SPI_FIFOCFG_DMARX_MASK                   (0x2000U)
#define SPI_FIFOCFG_DMARX_SHIFT                  (13U)
#define SPI_FIFOCFG_DMARX(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_DMARX_SHIFT)) & SPI_FIFOCFG_DMARX_MASK)
#define SPI_FIFOCFG_WAKETX_MASK                  (0x4000U)
#define SPI_FIFOCFG_WAKETX_SHIFT                 (14U)
#define SPI_FIFOCFG_WAKETX(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_WAKETX_SHIFT)) & SPI_FIFOCFG_WAKETX_MASK)
#define SPI_FIFOCFG_WAKERX_MASK                  (0x8000U)
#define SPI_FIFOCFG_WAKERX_SHIFT                 (15U)
#define SPI_FIFOCFG_WAKERX(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_WAKERX_SHIFT)) & SPI_FIFOCFG_WAKERX_MASK)
#define SPI_FIFOCFG_EMPTYTX_MASK                 (0x10000U)
#define SPI_FIFOCFG_EMPTYTX_SHIFT                (16U)
#define SPI_FIFOCFG_EMPTYTX(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_EMPTYTX_SHIFT)) & SPI_FIFOCFG_EMPTYTX_MASK)
#define SPI_FIFOCFG_EMPTYRX_MASK                 (0x20000U)
#define SPI_FIFOCFG_EMPTYRX_SHIFT                (17U)
#define SPI_FIFOCFG_EMPTYRX(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_EMPTYRX_SHIFT)) & SPI_FIFOCFG_EMPTYRX_MASK)
#define SPI_FIFOCFG_POPDBG_MASK                  (0x40000U)
#define SPI_FIFOCFG_POPDBG_SHIFT                 (18U)
#define SPI_FIFOCFG_POPDBG(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_POPDBG_SHIFT)) & SPI_FIFOCFG_POPDBG_MASK)

/*! @name FIFOSTAT - FIFO status register. */
#define SPI_FIFOSTAT_TXERR_MASK                  (0x1U)
#define SPI_FIFOSTAT_TXERR_SHIFT                 (0U)
#define SPI_FIFOSTAT_TXERR(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_TXERR_SHIFT)) & SPI_FIFOSTAT_TXERR_MASK)
#define SPI_FIFOSTAT_RXERR_MASK                  (0x2U)
#define SPI_FIFOSTAT_RXERR_SHIFT                 (1U)
#define SPI_FIFOSTAT_RXERR(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_RXERR_SHIFT)) & SPI_FIFOSTAT_RXERR_MASK)
#define SPI_FIFOSTAT_PERINT_MASK                 (0x8U)
#define SPI_FIFOSTAT_PERINT_SHIFT                (3U)
#define SPI_FIFOSTAT_PERINT(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_PERINT_SHIFT)) & SPI_FIFOSTAT_PERINT_MASK)
#define SPI_FIFOSTAT_TXEMPTY_MASK                (0x10U)
#define SPI_FIFOSTAT_TXEMPTY_SHIFT               (4U)
#define SPI_FIFOSTAT_TXEMPTY(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_TXEMPTY_SHIFT)) & SPI_FIFOSTAT_TXEMPTY_MASK)
#define SPI_FIFOSTAT_TXNOTFULL_MASK              (0x20U)
#define SPI_FIFOSTAT_TXNOTFULL_SHIFT             (5U)
#define SPI_FIFOSTAT_TXNOTFULL(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_TXNOTFULL_SHIFT)) & SPI_FIFOSTAT_TXNOTFULL_MASK)
#define SPI_FIFOSTAT_RXNOTEMPTY_MASK             (0x40U)
#define SPI_FIFOSTAT_RXNOTEMPTY_SHIFT            (6U)
#define SPI_FIFOSTAT_RXNOTEMPTY(x)               (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_RXNOTEMPTY_SHIFT)) & SPI_FIFOSTAT_RXNOTEMPTY_MASK)
#define SPI_FIFOSTAT_RXFULL_MASK                 (0x80U)
#define SPI_FIFOSTAT_RXFULL_SHIFT                (7U)
#define SPI_FIFOSTAT_RXFULL(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_RXFULL_SHIFT)) & SPI_FIFOSTAT_RXFULL_MASK)
#define SPI_FIFOSTAT_TXLVL_MASK                  (0x1F00U)
#define SPI_FIFOSTAT_TXLVL_SHIFT                 (8U)
#define SPI_FIFOSTAT_TXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_TXLVL_SHIFT)) & SPI_FIFOSTAT_TXLVL_MASK)
#define SPI_FIFOSTAT_RXLVL_MASK                  (0x1F0000U)
#define SPI_FIFOSTAT_RXLVL_SHIFT                 (16U)
#define SPI_FIFOSTAT_RXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_RXLVL_SHIFT)) & SPI_FIFOSTAT_RXLVL_MASK)

/*! @name FIFOTRIG - FIFO trigger settings for interrupt and DMA request. */
#define SPI_FIFOTRIG_TXLVLENA_MASK               (0x1U)
#define SPI_FIFOTRIG_TXLVLENA_SHIFT              (0U)
#define SPI_FIFOTRIG_TXLVLENA(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_FIFOTRIG_TXLVLENA_SHIFT)) & SPI_FIFOTRIG_TXLVLENA_MASK)
#define SPI_FIFOTRIG_RXLVLENA_MASK               (0x2U)
#define SPI_FIFOTRIG_RXLVLENA_SHIFT              (1U)
#define SPI_FIFOTRIG_RXLVLENA(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_FIFOTRIG_RXLVLENA_SHIFT)) & SPI_FIFOTRIG_RXLVLENA_MASK)
#define SPI_FIFOTRIG_TXLVL_MASK                  (0xF00U)
#define SPI_FIFOTRIG_TXLVL_SHIFT                 (8U)
#define SPI_FIFOTRIG_TXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOTRIG_TXLVL_SHIFT)) & SPI_FIFOTRIG_TXLVL_MASK)
#define SPI_FIFOTRIG_RXLVL_MASK                  (0xF0000U)
#define SPI_FIFOTRIG_RXLVL_SHIFT                 (16U)
#define SPI_FIFOTRIG_RXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOTRIG_RXLVL_SHIFT)) & SPI_FIFOTRIG_RXLVL_MASK)

/*! @name FIFOINTENSET - FIFO interrupt enable set (enable) and read register. */
#define SPI_FIFOINTENSET_TXERR_MASK              (0x1U)
#define SPI_FIFOINTENSET_TXERR_SHIFT             (0U)
#define SPI_FIFOINTENSET_TXERR(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENSET_TXERR_SHIFT)) & SPI_FIFOINTENSET_TXERR_MASK)
#define SPI_FIFOINTENSET_RXERR_MASK              (0x2U)
#define SPI_FIFOINTENSET_RXERR_SHIFT             (1U)
#define SPI_FIFOINTENSET_RXERR(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENSET_RXERR_SHIFT)) & SPI_FIFOINTENSET_RXERR_MASK)
#define SPI_FIFOINTENSET_TXLVL_MASK              (0x4U)
#define SPI_FIFOINTENSET_TXLVL_SHIFT             (2U)
#define SPI_FIFOINTENSET_TXLVL(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENSET_TXLVL_SHIFT)) & SPI_FIFOINTENSET_TXLVL_MASK)
#define SPI_FIFOINTENSET_RXLVL_MASK              (0x8U)
#define SPI_FIFOINTENSET_RXLVL_SHIFT             (3U)
#define SPI_FIFOINTENSET_RXLVL(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENSET_RXLVL_SHIFT)) & SPI_FIFOINTENSET_RXLVL_MASK)

/*! @name FIFOINTENCLR - FIFO interrupt enable clear (disable) and read register. */
#define SPI_FIFOINTENCLR_TXERR_MASK              (0x1U)
#define SPI_FIFOINTENCLR_TXERR_SHIFT             (0U)
#define SPI_FIFOINTENCLR_TXERR(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENCLR_TXERR_SHIFT)) & SPI_FIFOINTENCLR_TXERR_MASK)
#define SPI_FIFOINTENCLR_RXERR_MASK              (0x2U)
#define SPI_FIFOINTENCLR_RXERR_SHIFT             (1U)
#define SPI_FIFOINTENCLR_RXERR(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENCLR_RXERR_SHIFT)) & SPI_FIFOINTENCLR_RXERR_MASK)
#define SPI_FIFOINTENCLR_TXLVL_MASK              (0x4U)
#define SPI_FIFOINTENCLR_TXLVL_SHIFT             (2U)
#define SPI_FIFOINTENCLR_TXLVL(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENCLR_TXLVL_SHIFT)) & SPI_FIFOINTENCLR_TXLVL_MASK)
#define SPI_FIFOINTENCLR_RXLVL_MASK              (0x8U)
#define SPI_FIFOINTENCLR_RXLVL_SHIFT             (3U)
#define SPI_FIFOINTENCLR_RXLVL(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENCLR_RXLVL_SHIFT)) & SPI_FIFOINTENCLR_RXLVL_MASK)

/*! @name FIFOINTSTAT - FIFO interrupt status register. */
#define SPI_FIFOINTSTAT_TXERR_MASK               (0x1U)
#define SPI_FIFOINTSTAT_TXERR_SHIFT              (0U)
#define SPI_FIFOINTSTAT_TXERR(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTSTAT_TXERR_SHIFT)) & SPI_FIFOINTSTAT_TXERR_MASK)
#define SPI_FIFOINTSTAT_RXERR_MASK               (0x2U)
#define SPI_FIFOINTSTAT_RXERR_SHIFT              (1U)
#define SPI_FIFOINTSTAT_RXERR(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTSTAT_RXERR_SHIFT)) & SPI_FIFOINTSTAT_RXERR_MASK)
#define SPI_FIFOINTSTAT_TXLVL_MASK               (0x4U)
#define SPI_FIFOINTSTAT_TXLVL_SHIFT              (2U)
#define SPI_FIFOINTSTAT_TXLVL(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTSTAT_TXLVL_SHIFT)) & SPI_FIFOINTSTAT_TXLVL_MASK)
#define SPI_FIFOINTSTAT_RXLVL_MASK               (0x8U)
#define SPI_FIFOINTSTAT_RXLVL_SHIFT              (3U)
#define SPI_FIFOINTSTAT_RXLVL(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTSTAT_RXLVL_SHIFT)) & SPI_FIFOINTSTAT_RXLVL_MASK)
#define SPI_FIFOINTSTAT_PERINT_MASK              (0x10U)
#define SPI_FIFOINTSTAT_PERINT_SHIFT             (4U)
#define SPI_FIFOINTSTAT_PERINT(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTSTAT_PERINT_SHIFT)) & SPI_FIFOINTSTAT_PERINT_MASK)

/*! @name FIFOWR - FIFO write data. */
#define SPI_FIFOWR_TXDATA_MASK                   (0xFFFFU)
#define SPI_FIFOWR_TXDATA_SHIFT                  (0U)
#define SPI_FIFOWR_TXDATA(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_TXDATA_SHIFT)) & SPI_FIFOWR_TXDATA_MASK)
#define SPI_FIFOWR_TXSSEL0_N_MASK                (0x10000U)
#define SPI_FIFOWR_TXSSEL0_N_SHIFT               (16U)
#define SPI_FIFOWR_TXSSEL0_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_TXSSEL0_N_SHIFT)) & SPI_FIFOWR_TXSSEL0_N_MASK)
#define SPI_FIFOWR_TXSSEL1_N_MASK                (0x20000U)
#define SPI_FIFOWR_TXSSEL1_N_SHIFT               (17U)
#define SPI_FIFOWR_TXSSEL1_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_TXSSEL1_N_SHIFT)) & SPI_FIFOWR_TXSSEL1_N_MASK)
#define SPI_FIFOWR_TXSSEL2_N_MASK                (0x40000U)
#define SPI_FIFOWR_TXSSEL2_N_SHIFT               (18U)
#define SPI_FIFOWR_TXSSEL2_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_TXSSEL2_N_SHIFT)) & SPI_FIFOWR_TXSSEL2_N_MASK)
#define SPI_FIFOWR_TXSSEL3_N_MASK                (0x80000U)
#define SPI_FIFOWR_TXSSEL3_N_SHIFT               (19U)
#define SPI_FIFOWR_TXSSEL3_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_TXSSEL3_N_SHIFT)) & SPI_FIFOWR_TXSSEL3_N_MASK)
#define SPI_FIFOWR_EOT_MASK                      (0x100000U)
#define SPI_FIFOWR_EOT_SHIFT                     (20U)
#define SPI_FIFOWR_EOT(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_EOT_SHIFT)) & SPI_FIFOWR_EOT_MASK)
#define SPI_FIFOWR_EOF_MASK                      (0x200000U)
#define SPI_FIFOWR_EOF_SHIFT                     (21U)
#define SPI_FIFOWR_EOF(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_EOF_SHIFT)) & SPI_FIFOWR_EOF_MASK)
#define SPI_FIFOWR_RXIGNORE_MASK                 (0x400000U)
#define SPI_FIFOWR_RXIGNORE_SHIFT                (22U)
#define SPI_FIFOWR_RXIGNORE(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_RXIGNORE_SHIFT)) & SPI_FIFOWR_RXIGNORE_MASK)
#define SPI_FIFOWR_LEN_MASK                      (0xF000000U)
#define SPI_FIFOWR_LEN_SHIFT                     (24U)
#define SPI_FIFOWR_LEN(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_LEN_SHIFT)) & SPI_FIFOWR_LEN_MASK)

/*! @name FIFORD - FIFO read data. */
#define SPI_FIFORD_RXDATA_MASK                   (0xFFFFU)
#define SPI_FIFORD_RXDATA_SHIFT                  (0U)
#define SPI_FIFORD_RXDATA(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_FIFORD_RXDATA_SHIFT)) & SPI_FIFORD_RXDATA_MASK)
#define SPI_FIFORD_RXSSEL0_N_MASK                (0x10000U)
#define SPI_FIFORD_RXSSEL0_N_SHIFT               (16U)
#define SPI_FIFORD_RXSSEL0_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFORD_RXSSEL0_N_SHIFT)) & SPI_FIFORD_RXSSEL0_N_MASK)
#define SPI_FIFORD_RXSSEL1_N_MASK                (0x20000U)
#define SPI_FIFORD_RXSSEL1_N_SHIFT               (17U)
#define SPI_FIFORD_RXSSEL1_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFORD_RXSSEL1_N_SHIFT)) & SPI_FIFORD_RXSSEL1_N_MASK)
#define SPI_FIFORD_RXSSEL2_N_MASK                (0x40000U)
#define SPI_FIFORD_RXSSEL2_N_SHIFT               (18U)
#define SPI_FIFORD_RXSSEL2_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFORD_RXSSEL2_N_SHIFT)) & SPI_FIFORD_RXSSEL2_N_MASK)
#define SPI_FIFORD_RXSSEL3_N_MASK                (0x80000U)
#define SPI_FIFORD_RXSSEL3_N_SHIFT               (19U)
#define SPI_FIFORD_RXSSEL3_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFORD_RXSSEL3_N_SHIFT)) & SPI_FIFORD_RXSSEL3_N_MASK)
#define SPI_FIFORD_SOT_MASK                      (0x100000U)
#define SPI_FIFORD_SOT_SHIFT                     (20U)
#define SPI_FIFORD_SOT(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_FIFORD_SOT_SHIFT)) & SPI_FIFORD_SOT_MASK)

/*! @name FIFORDNOPOP - FIFO data read with no FIFO pop. */
#define SPI_FIFORDNOPOP_RXDATA_MASK              (0xFFFFU)
#define SPI_FIFORDNOPOP_RXDATA_SHIFT             (0U)
#define SPI_FIFORDNOPOP_RXDATA(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFORDNOPOP_RXDATA_SHIFT)) & SPI_FIFORDNOPOP_RXDATA_MASK)
#define SPI_FIFORDNOPOP_RXSSEL0_N_MASK           (0x10000U)
#define SPI_FIFORDNOPOP_RXSSEL0_N_SHIFT          (16U)
#define SPI_FIFORDNOPOP_RXSSEL0_N(x)             (((uint32_t)(((uint32_t)(x)) << SPI_FIFORDNOPOP_RXSSEL0_N_SHIFT)) & SPI_FIFORDNOPOP_RXSSEL0_N_MASK)
#define SPI_FIFORDNOPOP_RXSSEL1_N_MASK           (0x20000U)
#define SPI_FIFORDNOPOP_RXSSEL1_N_SHIFT          (17U)
#define SPI_FIFORDNOPOP_RXSSEL1_N(x)             (((uint32_t)(((uint32_t)(x)) << SPI_FIFORDNOPOP_RXSSEL1_N_SHIFT)) & SPI_FIFORDNOPOP_RXSSEL1_N_MASK)
#define SPI_FIFORDNOPOP_RXSSEL2_N_MASK           (0x40000U)
#define SPI_FIFORDNOPOP_RXSSEL2_N_SHIFT          (18U)
#define SPI_FIFORDNOPOP_RXSSEL2_N(x)             (((uint32_t)(((uint32_t)(x)) << SPI_FIFORDNOPOP_RXSSEL2_N_SHIFT)) & SPI_FIFORDNOPOP_RXSSEL2_N_MASK)
#define SPI_FIFORDNOPOP_RXSSEL3_N_MASK           (0x80000U)
#define SPI_FIFORDNOPOP_RXSSEL3_N_SHIFT          (19U)
#define SPI_FIFORDNOPOP_RXSSEL3_N(x)             (((uint32_t)(((uint32_t)(x)) << SPI_FIFORDNOPOP_RXSSEL3_N_SHIFT)) & SPI_FIFORDNOPOP_RXSSEL3_N_MASK)
#define SPI_FIFORDNOPOP_SOT_MASK                 (0x100000U)
#define SPI_FIFORDNOPOP_SOT_SHIFT                (20U)
#define SPI_FIFORDNOPOP_SOT(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_FIFORDNOPOP_SOT_SHIFT)) & SPI_FIFORDNOPOP_SOT_MASK)

/*! @name ID - Peripheral identification register. */
#define SPI_ID_APERTURE_MASK                     (0xFFU)
#define SPI_ID_APERTURE_SHIFT                    (0U)
#define SPI_ID_APERTURE(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_ID_APERTURE_SHIFT)) & SPI_ID_APERTURE_MASK)
#define SPI_ID_MINOR_REV_MASK                    (0xF00U)
#define SPI_ID_MINOR_REV_SHIFT                   (8U)
#define SPI_ID_MINOR_REV(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_ID_MINOR_REV_SHIFT)) & SPI_ID_MINOR_REV_MASK)
#define SPI_ID_MAJOR_REV_MASK                    (0xF000U)
#define SPI_ID_MAJOR_REV_SHIFT                   (12U)
#define SPI_ID_MAJOR_REV(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_ID_MAJOR_REV_SHIFT)) & SPI_ID_MAJOR_REV_MASK)
#define SPI_ID_ID_MASK                           (0xFFFF0000U)
#define SPI_ID_ID_SHIFT                          (16U)
#define SPI_ID_ID(x)                             (((uint32_t)(((uint32_t)(x)) << SPI_ID_ID_SHIFT)) & SPI_ID_ID_MASK)


/*!
 * @}
 */ /* end of group SPI_Register_Masks */


/* SPI - Peripheral instance base addresses */
/** Peripheral SPI0 base address */
#define SPI0_BASE                                (0x40086000u)
/** Peripheral SPI0 base pointer */
#define SPI0                                     ((SPI_Type *)SPI0_BASE)
/** Peripheral SPI1 base address */
#define SPI1_BASE                                (0x40087000u)
/** Peripheral SPI1 base pointer */
#define SPI1                                     ((SPI_Type *)SPI1_BASE)
/** Peripheral SPI2 base address */
#define SPI2_BASE                                (0x40088000u)
/** Peripheral SPI2 base pointer */
#define SPI2                                     ((SPI_Type *)SPI2_BASE)
/** Peripheral SPI3 base address */
#define SPI3_BASE                                (0x40089000u)
/** Peripheral SPI3 base pointer */
#define SPI3                                     ((SPI_Type *)SPI3_BASE)
/** Peripheral SPI4 base address */
#define SPI4_BASE                                (0x4008A000u)
/** Peripheral SPI4 base pointer */
#define SPI4                                     ((SPI_Type *)SPI4_BASE)
/** Peripheral SPI5 base address */
#define SPI5_BASE                                (0x40096000u)
/** Peripheral SPI5 base pointer */
#define SPI5                                     ((SPI_Type *)SPI5_BASE)
/** Peripheral SPI6 base address */
#define SPI6_BASE                                (0x40097000u)
/** Peripheral SPI6 base pointer */
#define SPI6                                     ((SPI_Type *)SPI6_BASE)
/** Peripheral SPI7 base address */
#define SPI7_BASE                                (0x40098000u)
/** Peripheral SPI7 base pointer */
#define SPI7                                     ((SPI_Type *)SPI7_BASE)
/** Peripheral SPI8 base address */
#define SPI8_BASE                                (0x40099000u)
/** Peripheral SPI8 base pointer */
#define SPI8                                     ((SPI_Type *)SPI8_BASE)
/** Peripheral SPI9 base address */
#define SPI9_BASE                                (0x4009A000u)
/** Peripheral SPI9 base pointer */
#define SPI9                                     ((SPI_Type *)SPI9_BASE)
/** Array initializer of SPI peripheral base addresses */
#define SPI_BASE_ADDRS                           { SPI0_BASE, SPI1_BASE, SPI2_BASE, SPI3_BASE, SPI4_BASE, SPI5_BASE, SPI6_BASE, SPI7_BASE, SPI8_BASE, SPI9_BASE }
/** Array initializer of SPI peripheral base pointers */
#define SPI_BASE_PTRS                            { SPI0, SPI1, SPI2, SPI3, SPI4, SPI5, SPI6, SPI7, SPI8, SPI9 }
/** Interrupt vectors for the SPI peripheral type */
#define SPI_IRQS                                 { FLEXCOMM0_IRQn, FLEXCOMM1_IRQn, FLEXCOMM2_IRQn, FLEXCOMM3_IRQn, FLEXCOMM4_IRQn, FLEXCOMM5_IRQn, FLEXCOMM6_IRQn, FLEXCOMM7_IRQn, FLEXCOMM8_IRQn, FLEXCOMM9_IRQn }

/*!
 * @}
 */ /* end of group SPI_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SPIFI Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPIFI_Peripheral_Access_Layer SPIFI Peripheral Access Layer
 * @{
 */

/** SPIFI - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< SPIFI control register, offset: 0x0 */
  __IO uint32_t CMD;                               /**< SPIFI command register, offset: 0x4 */
  __IO uint32_t ADDR;                              /**< SPIFI address register, offset: 0x8 */
  __IO uint32_t IDATA;                             /**< SPIFI intermediate data register, offset: 0xC */
  __IO uint32_t CLIMIT;                            /**< SPIFI limit register, offset: 0x10 */
  __IO uint32_t DATA;                              /**< SPIFI data register, offset: 0x14 */
  __IO uint32_t MCMD;                              /**< SPIFI memory command register, offset: 0x18 */
  __IO uint32_t STAT;                              /**< SPIFI status register, offset: 0x1C */
} SPIFI_Type;

/* ----------------------------------------------------------------------------
   -- SPIFI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPIFI_Register_Masks SPIFI Register Masks
 * @{
 */

/*! @name CTRL - SPIFI control register */
#define SPIFI_CTRL_TIMEOUT_MASK                  (0xFFFFU)
#define SPIFI_CTRL_TIMEOUT_SHIFT                 (0U)
#define SPIFI_CTRL_TIMEOUT(x)                    (((uint32_t)(((uint32_t)(x)) << SPIFI_CTRL_TIMEOUT_SHIFT)) & SPIFI_CTRL_TIMEOUT_MASK)
#define SPIFI_CTRL_CSHIGH_MASK                   (0xF0000U)
#define SPIFI_CTRL_CSHIGH_SHIFT                  (16U)
#define SPIFI_CTRL_CSHIGH(x)                     (((uint32_t)(((uint32_t)(x)) << SPIFI_CTRL_CSHIGH_SHIFT)) & SPIFI_CTRL_CSHIGH_MASK)
#define SPIFI_CTRL_D_PRFTCH_DIS_MASK             (0x200000U)
#define SPIFI_CTRL_D_PRFTCH_DIS_SHIFT            (21U)
#define SPIFI_CTRL_D_PRFTCH_DIS(x)               (((uint32_t)(((uint32_t)(x)) << SPIFI_CTRL_D_PRFTCH_DIS_SHIFT)) & SPIFI_CTRL_D_PRFTCH_DIS_MASK)
#define SPIFI_CTRL_INTEN_MASK                    (0x400000U)
#define SPIFI_CTRL_INTEN_SHIFT                   (22U)
#define SPIFI_CTRL_INTEN(x)                      (((uint32_t)(((uint32_t)(x)) << SPIFI_CTRL_INTEN_SHIFT)) & SPIFI_CTRL_INTEN_MASK)
#define SPIFI_CTRL_MODE3_MASK                    (0x800000U)
#define SPIFI_CTRL_MODE3_SHIFT                   (23U)
#define SPIFI_CTRL_MODE3(x)                      (((uint32_t)(((uint32_t)(x)) << SPIFI_CTRL_MODE3_SHIFT)) & SPIFI_CTRL_MODE3_MASK)
#define SPIFI_CTRL_PRFTCH_DIS_MASK               (0x8000000U)
#define SPIFI_CTRL_PRFTCH_DIS_SHIFT              (27U)
#define SPIFI_CTRL_PRFTCH_DIS(x)                 (((uint32_t)(((uint32_t)(x)) << SPIFI_CTRL_PRFTCH_DIS_SHIFT)) & SPIFI_CTRL_PRFTCH_DIS_MASK)
#define SPIFI_CTRL_DUAL_MASK                     (0x10000000U)
#define SPIFI_CTRL_DUAL_SHIFT                    (28U)
#define SPIFI_CTRL_DUAL(x)                       (((uint32_t)(((uint32_t)(x)) << SPIFI_CTRL_DUAL_SHIFT)) & SPIFI_CTRL_DUAL_MASK)
#define SPIFI_CTRL_RFCLK_MASK                    (0x20000000U)
#define SPIFI_CTRL_RFCLK_SHIFT                   (29U)
#define SPIFI_CTRL_RFCLK(x)                      (((uint32_t)(((uint32_t)(x)) << SPIFI_CTRL_RFCLK_SHIFT)) & SPIFI_CTRL_RFCLK_MASK)
#define SPIFI_CTRL_FBCLK_MASK                    (0x40000000U)
#define SPIFI_CTRL_FBCLK_SHIFT                   (30U)
#define SPIFI_CTRL_FBCLK(x)                      (((uint32_t)(((uint32_t)(x)) << SPIFI_CTRL_FBCLK_SHIFT)) & SPIFI_CTRL_FBCLK_MASK)
#define SPIFI_CTRL_DMAEN_MASK                    (0x80000000U)
#define SPIFI_CTRL_DMAEN_SHIFT                   (31U)
#define SPIFI_CTRL_DMAEN(x)                      (((uint32_t)(((uint32_t)(x)) << SPIFI_CTRL_DMAEN_SHIFT)) & SPIFI_CTRL_DMAEN_MASK)

/*! @name CMD - SPIFI command register */
#define SPIFI_CMD_DATALEN_MASK                   (0x3FFFU)
#define SPIFI_CMD_DATALEN_SHIFT                  (0U)
#define SPIFI_CMD_DATALEN(x)                     (((uint32_t)(((uint32_t)(x)) << SPIFI_CMD_DATALEN_SHIFT)) & SPIFI_CMD_DATALEN_MASK)
#define SPIFI_CMD_POLL_MASK                      (0x4000U)
#define SPIFI_CMD_POLL_SHIFT                     (14U)
#define SPIFI_CMD_POLL(x)                        (((uint32_t)(((uint32_t)(x)) << SPIFI_CMD_POLL_SHIFT)) & SPIFI_CMD_POLL_MASK)
#define SPIFI_CMD_DOUT_MASK                      (0x8000U)
#define SPIFI_CMD_DOUT_SHIFT                     (15U)
#define SPIFI_CMD_DOUT(x)                        (((uint32_t)(((uint32_t)(x)) << SPIFI_CMD_DOUT_SHIFT)) & SPIFI_CMD_DOUT_MASK)
#define SPIFI_CMD_INTLEN_MASK                    (0x70000U)
#define SPIFI_CMD_INTLEN_SHIFT                   (16U)
#define SPIFI_CMD_INTLEN(x)                      (((uint32_t)(((uint32_t)(x)) << SPIFI_CMD_INTLEN_SHIFT)) & SPIFI_CMD_INTLEN_MASK)
#define SPIFI_CMD_FIELDFORM_MASK                 (0x180000U)
#define SPIFI_CMD_FIELDFORM_SHIFT                (19U)
#define SPIFI_CMD_FIELDFORM(x)                   (((uint32_t)(((uint32_t)(x)) << SPIFI_CMD_FIELDFORM_SHIFT)) & SPIFI_CMD_FIELDFORM_MASK)
#define SPIFI_CMD_FRAMEFORM_MASK                 (0xE00000U)
#define SPIFI_CMD_FRAMEFORM_SHIFT                (21U)
#define SPIFI_CMD_FRAMEFORM(x)                   (((uint32_t)(((uint32_t)(x)) << SPIFI_CMD_FRAMEFORM_SHIFT)) & SPIFI_CMD_FRAMEFORM_MASK)
#define SPIFI_CMD_OPCODE_MASK                    (0xFF000000U)
#define SPIFI_CMD_OPCODE_SHIFT                   (24U)
#define SPIFI_CMD_OPCODE(x)                      (((uint32_t)(((uint32_t)(x)) << SPIFI_CMD_OPCODE_SHIFT)) & SPIFI_CMD_OPCODE_MASK)

/*! @name ADDR - SPIFI address register */
#define SPIFI_ADDR_ADDRESS_MASK                  (0xFFFFFFFFU)
#define SPIFI_ADDR_ADDRESS_SHIFT                 (0U)
#define SPIFI_ADDR_ADDRESS(x)                    (((uint32_t)(((uint32_t)(x)) << SPIFI_ADDR_ADDRESS_SHIFT)) & SPIFI_ADDR_ADDRESS_MASK)

/*! @name IDATA - SPIFI intermediate data register */
#define SPIFI_IDATA_IDATA_MASK                   (0xFFFFFFFFU)
#define SPIFI_IDATA_IDATA_SHIFT                  (0U)
#define SPIFI_IDATA_IDATA(x)                     (((uint32_t)(((uint32_t)(x)) << SPIFI_IDATA_IDATA_SHIFT)) & SPIFI_IDATA_IDATA_MASK)

/*! @name CLIMIT - SPIFI limit register */
#define SPIFI_CLIMIT_CLIMIT_MASK                 (0xFFFFFFFFU)
#define SPIFI_CLIMIT_CLIMIT_SHIFT                (0U)
#define SPIFI_CLIMIT_CLIMIT(x)                   (((uint32_t)(((uint32_t)(x)) << SPIFI_CLIMIT_CLIMIT_SHIFT)) & SPIFI_CLIMIT_CLIMIT_MASK)

/*! @name DATA - SPIFI data register */
#define SPIFI_DATA_DATA_MASK                     (0xFFFFFFFFU)
#define SPIFI_DATA_DATA_SHIFT                    (0U)
#define SPIFI_DATA_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << SPIFI_DATA_DATA_SHIFT)) & SPIFI_DATA_DATA_MASK)

/*! @name MCMD - SPIFI memory command register */
#define SPIFI_MCMD_POLL_MASK                     (0x4000U)
#define SPIFI_MCMD_POLL_SHIFT                    (14U)
#define SPIFI_MCMD_POLL(x)                       (((uint32_t)(((uint32_t)(x)) << SPIFI_MCMD_POLL_SHIFT)) & SPIFI_MCMD_POLL_MASK)
#define SPIFI_MCMD_DOUT_MASK                     (0x8000U)
#define SPIFI_MCMD_DOUT_SHIFT                    (15U)
#define SPIFI_MCMD_DOUT(x)                       (((uint32_t)(((uint32_t)(x)) << SPIFI_MCMD_DOUT_SHIFT)) & SPIFI_MCMD_DOUT_MASK)
#define SPIFI_MCMD_INTLEN_MASK                   (0x70000U)
#define SPIFI_MCMD_INTLEN_SHIFT                  (16U)
#define SPIFI_MCMD_INTLEN(x)                     (((uint32_t)(((uint32_t)(x)) << SPIFI_MCMD_INTLEN_SHIFT)) & SPIFI_MCMD_INTLEN_MASK)
#define SPIFI_MCMD_FIELDFORM_MASK                (0x180000U)
#define SPIFI_MCMD_FIELDFORM_SHIFT               (19U)
#define SPIFI_MCMD_FIELDFORM(x)                  (((uint32_t)(((uint32_t)(x)) << SPIFI_MCMD_FIELDFORM_SHIFT)) & SPIFI_MCMD_FIELDFORM_MASK)
#define SPIFI_MCMD_FRAMEFORM_MASK                (0xE00000U)
#define SPIFI_MCMD_FRAMEFORM_SHIFT               (21U)
#define SPIFI_MCMD_FRAMEFORM(x)                  (((uint32_t)(((uint32_t)(x)) << SPIFI_MCMD_FRAMEFORM_SHIFT)) & SPIFI_MCMD_FRAMEFORM_MASK)
#define SPIFI_MCMD_OPCODE_MASK                   (0xFF000000U)
#define SPIFI_MCMD_OPCODE_SHIFT                  (24U)
#define SPIFI_MCMD_OPCODE(x)                     (((uint32_t)(((uint32_t)(x)) << SPIFI_MCMD_OPCODE_SHIFT)) & SPIFI_MCMD_OPCODE_MASK)

/*! @name STAT - SPIFI status register */
#define SPIFI_STAT_MCINIT_MASK                   (0x1U)
#define SPIFI_STAT_MCINIT_SHIFT                  (0U)
#define SPIFI_STAT_MCINIT(x)                     (((uint32_t)(((uint32_t)(x)) << SPIFI_STAT_MCINIT_SHIFT)) & SPIFI_STAT_MCINIT_MASK)
#define SPIFI_STAT_CMD_MASK                      (0x2U)
#define SPIFI_STAT_CMD_SHIFT                     (1U)
#define SPIFI_STAT_CMD(x)                        (((uint32_t)(((uint32_t)(x)) << SPIFI_STAT_CMD_SHIFT)) & SPIFI_STAT_CMD_MASK)
#define SPIFI_STAT_RESET_MASK                    (0x10U)
#define SPIFI_STAT_RESET_SHIFT                   (4U)
#define SPIFI_STAT_RESET(x)                      (((uint32_t)(((uint32_t)(x)) << SPIFI_STAT_RESET_SHIFT)) & SPIFI_STAT_RESET_MASK)
#define SPIFI_STAT_INTRQ_MASK                    (0x20U)
#define SPIFI_STAT_INTRQ_SHIFT                   (5U)
#define SPIFI_STAT_INTRQ(x)                      (((uint32_t)(((uint32_t)(x)) << SPIFI_STAT_INTRQ_SHIFT)) & SPIFI_STAT_INTRQ_MASK)


/*!
 * @}
 */ /* end of group SPIFI_Register_Masks */


/* SPIFI - Peripheral instance base addresses */
/** Peripheral SPIFI0 base address */
#define SPIFI0_BASE                              (0x40080000u)
/** Peripheral SPIFI0 base pointer */
#define SPIFI0                                   ((SPIFI_Type *)SPIFI0_BASE)
/** Array initializer of SPIFI peripheral base addresses */
#define SPIFI_BASE_ADDRS                         { SPIFI0_BASE }
/** Array initializer of SPIFI peripheral base pointers */
#define SPIFI_BASE_PTRS                          { SPIFI0 }
/** Interrupt vectors for the SPIFI peripheral type */
#define SPIFI_IRQS                               { SPIFI0_IRQn }

/*!
 * @}
 */ /* end of group SPIFI_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SYSCON Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSCON_Peripheral_Access_Layer SYSCON Peripheral Access Layer
 * @{
 */

/** SYSCON - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[16];
  __IO uint32_t AHBMATPRIO;                        /**< AHB multilayer matrix priority control, offset: 0x10 */
       uint8_t RESERVED_1[44];
  __IO uint32_t SYSTCKCAL;                         /**< System tick counter calibration, offset: 0x40 */
       uint8_t RESERVED_2[4];
  __IO uint32_t NMISRC;                            /**< NMI Source Select, offset: 0x48 */
  __IO uint32_t ASYNCAPBCTRL;                      /**< Asynchronous APB Control, offset: 0x4C */
       uint8_t RESERVED_3[112];
  __I  uint32_t PIOPORCAP[2];                      /**< POR captured value of port n, array offset: 0xC0, array step: 0x4 */
       uint8_t RESERVED_4[8];
  __I  uint32_t PIORESCAP[2];                      /**< Reset captured value of port n, array offset: 0xD0, array step: 0x4 */
       uint8_t RESERVED_5[40];
  __IO uint32_t PRESETCTRL[3];                     /**< Peripheral reset control n, array offset: 0x100, array step: 0x4 */
       uint8_t RESERVED_6[20];
  __O  uint32_t PRESETCTRLSET[3];                  /**< Set bits in PRESETCTRLn, array offset: 0x120, array step: 0x4 */
       uint8_t RESERVED_7[20];
  __O  uint32_t PRESETCTRLCLR[3];                  /**< Clear bits in PRESETCTRLn, array offset: 0x140, array step: 0x4 */
       uint8_t RESERVED_8[164];
  __IO uint32_t SYSRSTSTAT;                        /**< System reset status register, offset: 0x1F0 */
       uint8_t RESERVED_9[12];
  __IO uint32_t AHBCLKCTRL[3];                     /**< AHB Clock control n, array offset: 0x200, array step: 0x4 */
       uint8_t RESERVED_10[20];
  __O  uint32_t AHBCLKCTRLSET[3];                  /**< Set bits in AHBCLKCTRLn, array offset: 0x220, array step: 0x4 */
       uint8_t RESERVED_11[20];
  __O  uint32_t AHBCLKCTRLCLR[3];                  /**< Clear bits in AHBCLKCTRLn, array offset: 0x240, array step: 0x4 */
       uint8_t RESERVED_12[52];
  __IO uint32_t MAINCLKSELA;                       /**< Main clock source select A, offset: 0x280 */
  __IO uint32_t MAINCLKSELB;                       /**< Main clock source select B, offset: 0x284 */
  __IO uint32_t CLKOUTSELA;                        /**< CLKOUT clock source select A, offset: 0x288 */
       uint8_t RESERVED_13[4];
  __IO uint32_t SYSPLLCLKSEL;                      /**< PLL clock source select, offset: 0x290 */
       uint8_t RESERVED_14[4];
  __IO uint32_t AUDPLLCLKSEL;                      /**< Audio PLL clock source select, offset: 0x298 */
       uint8_t RESERVED_15[4];
  __IO uint32_t SPIFICLKSEL;                       /**< SPIFI clock source select, offset: 0x2A0 */
  __IO uint32_t ADCCLKSEL;                         /**< ADC clock source select, offset: 0x2A4 */
  __IO uint32_t USB0CLKSEL;                        /**< USB0 clock source select, offset: 0x2A8 */
  __IO uint32_t USB1CLKSEL;                        /**< USB1 clock source select, offset: 0x2AC */
  __IO uint32_t FCLKSEL[10];                       /**< Flexcomm 0 clock source select, array offset: 0x2B0, array step: 0x4 */
       uint8_t RESERVED_16[8];
  __IO uint32_t MCLKCLKSEL;                        /**< MCLK clock source select, offset: 0x2E0 */
       uint8_t RESERVED_17[4];
  __IO uint32_t FRGCLKSEL;                         /**< Fractional Rate Generator clock source select, offset: 0x2E8 */
  __IO uint32_t DMICCLKSEL;                        /**< Digital microphone (DMIC) subsystem clock select, offset: 0x2EC */
  __IO uint32_t SCTCLKSEL;                         /**< SCTimer/PWM clock source select, offset: 0x2F0 */
  __IO uint32_t LCDCLKSEL;                         /**< LCD clock source select, offset: 0x2F4 */
  __IO uint32_t SDIOCLKSEL;                        /**< SDIO clock source select, offset: 0x2F8 */
       uint8_t RESERVED_18[4];
  __IO uint32_t SYSTICKCLKDIV;                     /**< SYSTICK clock divider, offset: 0x300 */
  __IO uint32_t ARMTRACECLKDIV;                    /**< ARM Trace clock divider, offset: 0x304 */
  __IO uint32_t CAN0CLKDIV;                        /**< MCAN0 clock divider, offset: 0x308 */
  __IO uint32_t CAN1CLKDIV;                        /**< MCAN1 clock divider, offset: 0x30C */
  __IO uint32_t SC0CLKDIV;                         /**< Smartcard0 clock divider, offset: 0x310 */
  __IO uint32_t SC1CLKDIV;                         /**< Smartcard1 clock divider, offset: 0x314 */
       uint8_t RESERVED_19[104];
  __IO uint32_t AHBCLKDIV;                         /**< AHB clock divider, offset: 0x380 */
  __IO uint32_t CLKOUTDIV;                         /**< CLKOUT clock divider, offset: 0x384 */
  __IO uint32_t FROHFCLKDIV;                       /**< FROHF clock divider, offset: 0x388 */
       uint8_t RESERVED_20[4];
  __IO uint32_t SPIFICLKDIV;                       /**< SPIFI clock divider, offset: 0x390 */
  __IO uint32_t ADCCLKDIV;                         /**< ADC clock divider, offset: 0x394 */
  __IO uint32_t USB0CLKDIV;                        /**< USB0 clock divider, offset: 0x398 */
  __IO uint32_t USB1CLKDIV;                        /**< USB1 clock divider, offset: 0x39C */
  __IO uint32_t FRGCTRL;                           /**< Fractional rate divider, offset: 0x3A0 */
       uint8_t RESERVED_21[4];
  __IO uint32_t DMICCLKDIV;                        /**< DMIC clock divider, offset: 0x3A8 */
  __IO uint32_t MCLKDIV;                           /**< I2S MCLK clock divider, offset: 0x3AC */
  __IO uint32_t LCDCLKDIV;                         /**< LCD clock divider, offset: 0x3B0 */
  __IO uint32_t SCTCLKDIV;                         /**< SCT/PWM clock divider, offset: 0x3B4 */
  __IO uint32_t EMCCLKDIV;                         /**< EMC clock divider, offset: 0x3B8 */
  __IO uint32_t SDIOCLKDIV;                        /**< SDIO clock divider, offset: 0x3BC */
       uint8_t RESERVED_22[64];
  __IO uint32_t FLASHCFG;                          /**< Flash wait states configuration, offset: 0x400 */
       uint8_t RESERVED_23[8];
  __IO uint32_t USB0CLKCTRL;                       /**< USB0 clock control, offset: 0x40C */
  __IO uint32_t USB0CLKSTAT;                       /**< USB0 clock status, offset: 0x410 */
       uint8_t RESERVED_24[4];
  __IO uint32_t FREQMECTRL;                        /**< Frequency measure register, offset: 0x418 */
       uint8_t RESERVED_25[4];
  __IO uint32_t MCLKIO;                            /**< MCLK input/output control, offset: 0x420 */
  __IO uint32_t USB1CLKCTRL;                       /**< USB1 clock control, offset: 0x424 */
  __IO uint32_t USB1CLKSTAT;                       /**< USB1 clock status, offset: 0x428 */
       uint8_t RESERVED_26[24];
  __IO uint32_t EMCSYSCTRL;                        /**< EMC system control, offset: 0x444 */
  __IO uint32_t EMCDLYCTRL;                        /**< EMC clock delay control, offset: 0x448 */
  __IO uint32_t EMCDLYCAL;                         /**< EMC delay chain calibration control, offset: 0x44C */
  __IO uint32_t ETHPHYSEL;                         /**< Ethernet PHY Selection, offset: 0x450 */
  __IO uint32_t ETHSBDCTRL;                        /**< Ethernet SBD flow control, offset: 0x454 */
       uint8_t RESERVED_27[8];
  __IO uint32_t SDIOCLKCTRL;                       /**< SDIO CCLKIN phase and delay control, offset: 0x460 */
       uint8_t RESERVED_28[156];
  __IO uint32_t FROCTRL;                           /**< FRO oscillator control, offset: 0x500 */
  __IO uint32_t SYSOSCCTRL;                        /**< System oscillator control, offset: 0x504 */
  __IO uint32_t WDTOSCCTRL;                        /**< Watchdog oscillator control, offset: 0x508 */
  __IO uint32_t RTCOSCCTRL;                        /**< RTC oscillator 32 kHz output control, offset: 0x50C */
       uint8_t RESERVED_29[12];
  __IO uint32_t USBPLLCTRL;                        /**< USB PLL control, offset: 0x51C */
  __IO uint32_t USBPLLSTAT;                        /**< USB PLL status, offset: 0x520 */
       uint8_t RESERVED_30[92];
  __IO uint32_t SYSPLLCTRL;                        /**< System PLL control, offset: 0x580 */
  __IO uint32_t SYSPLLSTAT;                        /**< PLL status, offset: 0x584 */
  __IO uint32_t SYSPLLNDEC;                        /**< PLL N divider, offset: 0x588 */
  __IO uint32_t SYSPLLPDEC;                        /**< PLL P divider, offset: 0x58C */
  __IO uint32_t SYSPLLMDEC;                        /**< System PLL M divider, offset: 0x590 */
       uint8_t RESERVED_31[12];
  __IO uint32_t AUDPLLCTRL;                        /**< Audio PLL control, offset: 0x5A0 */
  __IO uint32_t AUDPLLSTAT;                        /**< Audio PLL status, offset: 0x5A4 */
  __IO uint32_t AUDPLLNDEC;                        /**< Audio PLL N divider, offset: 0x5A8 */
  __IO uint32_t AUDPLLPDEC;                        /**< Audio PLL P divider, offset: 0x5AC */
  __IO uint32_t AUDPLLMDEC;                        /**< Audio PLL M divider, offset: 0x5B0 */
  __IO uint32_t AUDPLLFRAC;                        /**< Audio PLL fractional divider control, offset: 0x5B4 */
       uint8_t RESERVED_32[72];
  __IO uint32_t PDSLEEPCFG[2];                     /**< Power configuration register 0, array offset: 0x600, array step: 0x4 */
       uint8_t RESERVED_33[8];
  __IO uint32_t PDRUNCFG[2];                       /**< Power configuration register 0, array offset: 0x610, array step: 0x4 */
       uint8_t RESERVED_34[8];
  __IO uint32_t PDRUNCFGSET[2];                    /**< Set bits in PDRUNCFG0, array offset: 0x620, array step: 0x4 */
       uint8_t RESERVED_35[8];
  __IO uint32_t PDRUNCFGCLR[2];                    /**< Clear bits in PDRUNCFG0, array offset: 0x630, array step: 0x4 */
       uint8_t RESERVED_36[72];
  __IO uint32_t STARTER[2];                        /**< Start logic 0 wake-up enable register, array offset: 0x680, array step: 0x4 */
       uint8_t RESERVED_37[24];
  __O  uint32_t STARTERSET[2];                     /**< Set bits in STARTER, array offset: 0x6A0, array step: 0x4 */
       uint8_t RESERVED_38[24];
  __O  uint32_t STARTERCLR[2];                     /**< Clear bits in STARTER0, array offset: 0x6C0, array step: 0x4 */
       uint8_t RESERVED_39[184];
  __IO uint32_t HWWAKE;                            /**< Configures special cases of hardware wake-up, offset: 0x780 */
       uint8_t RESERVED_40[1664];
  __IO uint32_t AUTOCGOR;                          /**< Auto Clock-Gate Override Register, offset: 0xE04 */
       uint8_t RESERVED_41[492];
  __I  uint32_t JTAGIDCODE;                        /**< JTAG ID code register, offset: 0xFF4 */
  __I  uint32_t DEVICE_ID0;                        /**< Part ID register, offset: 0xFF8 */
  __I  uint32_t DEVICE_ID1;                        /**< Boot ROM and die revision register, offset: 0xFFC */
       uint8_t RESERVED_42[127044];
  __IO uint32_t BODCTRL;                           /**< Brown-Out Detect control, offset: 0x20044 */
} SYSCON_Type;

/* ----------------------------------------------------------------------------
   -- SYSCON Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSCON_Register_Masks SYSCON Register Masks
 * @{
 */

/*! @name AHBMATPRIO - AHB multilayer matrix priority control */
#define SYSCON_AHBMATPRIO_PRI_ICODE_MASK         (0x3U)
#define SYSCON_AHBMATPRIO_PRI_ICODE_SHIFT        (0U)
#define SYSCON_AHBMATPRIO_PRI_ICODE(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_ICODE_SHIFT)) & SYSCON_AHBMATPRIO_PRI_ICODE_MASK)
#define SYSCON_AHBMATPRIO_PRI_DCODE_MASK         (0xCU)
#define SYSCON_AHBMATPRIO_PRI_DCODE_SHIFT        (2U)
#define SYSCON_AHBMATPRIO_PRI_DCODE(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_DCODE_SHIFT)) & SYSCON_AHBMATPRIO_PRI_DCODE_MASK)
#define SYSCON_AHBMATPRIO_PRI_SYS_MASK           (0x30U)
#define SYSCON_AHBMATPRIO_PRI_SYS_SHIFT          (4U)
#define SYSCON_AHBMATPRIO_PRI_SYS(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_SYS_SHIFT)) & SYSCON_AHBMATPRIO_PRI_SYS_MASK)
#define SYSCON_AHBMATPRIO_PRI_DMA_MASK           (0x3C0U)
#define SYSCON_AHBMATPRIO_PRI_DMA_SHIFT          (6U)
#define SYSCON_AHBMATPRIO_PRI_DMA(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_DMA_SHIFT)) & SYSCON_AHBMATPRIO_PRI_DMA_MASK)
#define SYSCON_AHBMATPRIO_PRI_ETH_MASK           (0xC00U)
#define SYSCON_AHBMATPRIO_PRI_ETH_SHIFT          (10U)
#define SYSCON_AHBMATPRIO_PRI_ETH(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_ETH_SHIFT)) & SYSCON_AHBMATPRIO_PRI_ETH_MASK)
#define SYSCON_AHBMATPRIO_PRI_LCD_MASK           (0x3000U)
#define SYSCON_AHBMATPRIO_PRI_LCD_SHIFT          (12U)
#define SYSCON_AHBMATPRIO_PRI_LCD(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_LCD_SHIFT)) & SYSCON_AHBMATPRIO_PRI_LCD_MASK)
#define SYSCON_AHBMATPRIO_PRI_USB0_MASK          (0xC000U)
#define SYSCON_AHBMATPRIO_PRI_USB0_SHIFT         (14U)
#define SYSCON_AHBMATPRIO_PRI_USB0(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_USB0_SHIFT)) & SYSCON_AHBMATPRIO_PRI_USB0_MASK)
#define SYSCON_AHBMATPRIO_PRI_USB1_MASK          (0x30000U)
#define SYSCON_AHBMATPRIO_PRI_USB1_SHIFT         (16U)
#define SYSCON_AHBMATPRIO_PRI_USB1(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_USB1_SHIFT)) & SYSCON_AHBMATPRIO_PRI_USB1_MASK)
#define SYSCON_AHBMATPRIO_PRI_SDIO_MASK          (0xC0000U)
#define SYSCON_AHBMATPRIO_PRI_SDIO_SHIFT         (18U)
#define SYSCON_AHBMATPRIO_PRI_SDIO(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_SDIO_SHIFT)) & SYSCON_AHBMATPRIO_PRI_SDIO_MASK)
#define SYSCON_AHBMATPRIO_PRI_MCAN1_MASK         (0x300000U)
#define SYSCON_AHBMATPRIO_PRI_MCAN1_SHIFT        (20U)
#define SYSCON_AHBMATPRIO_PRI_MCAN1(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_MCAN1_SHIFT)) & SYSCON_AHBMATPRIO_PRI_MCAN1_MASK)
#define SYSCON_AHBMATPRIO_PRI_MCAN2_MASK         (0xC00000U)
#define SYSCON_AHBMATPRIO_PRI_MCAN2_SHIFT        (22U)
#define SYSCON_AHBMATPRIO_PRI_MCAN2(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_MCAN2_SHIFT)) & SYSCON_AHBMATPRIO_PRI_MCAN2_MASK)
#define SYSCON_AHBMATPRIO_PRI_SHA_MASK           (0x3000000U)
#define SYSCON_AHBMATPRIO_PRI_SHA_SHIFT          (24U)
#define SYSCON_AHBMATPRIO_PRI_SHA(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_SHA_SHIFT)) & SYSCON_AHBMATPRIO_PRI_SHA_MASK)

/*! @name SYSTCKCAL - System tick counter calibration */
#define SYSCON_SYSTCKCAL_CAL_MASK                (0xFFFFFFU)
#define SYSCON_SYSTCKCAL_CAL_SHIFT               (0U)
#define SYSCON_SYSTCKCAL_CAL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTCKCAL_CAL_SHIFT)) & SYSCON_SYSTCKCAL_CAL_MASK)
#define SYSCON_SYSTCKCAL_SKEW_MASK               (0x1000000U)
#define SYSCON_SYSTCKCAL_SKEW_SHIFT              (24U)
#define SYSCON_SYSTCKCAL_SKEW(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTCKCAL_SKEW_SHIFT)) & SYSCON_SYSTCKCAL_SKEW_MASK)
#define SYSCON_SYSTCKCAL_NOREF_MASK              (0x2000000U)
#define SYSCON_SYSTCKCAL_NOREF_SHIFT             (25U)
#define SYSCON_SYSTCKCAL_NOREF(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTCKCAL_NOREF_SHIFT)) & SYSCON_SYSTCKCAL_NOREF_MASK)

/*! @name NMISRC - NMI Source Select */
#define SYSCON_NMISRC_IRQM4_MASK                 (0x3FU)
#define SYSCON_NMISRC_IRQM4_SHIFT                (0U)
#define SYSCON_NMISRC_IRQM4(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_NMISRC_IRQM4_SHIFT)) & SYSCON_NMISRC_IRQM4_MASK)
#define SYSCON_NMISRC_NMIENM4_MASK               (0x80000000U)
#define SYSCON_NMISRC_NMIENM4_SHIFT              (31U)
#define SYSCON_NMISRC_NMIENM4(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_NMISRC_NMIENM4_SHIFT)) & SYSCON_NMISRC_NMIENM4_MASK)

/*! @name ASYNCAPBCTRL - Asynchronous APB Control */
#define SYSCON_ASYNCAPBCTRL_ENABLE_MASK          (0x1U)
#define SYSCON_ASYNCAPBCTRL_ENABLE_SHIFT         (0U)
#define SYSCON_ASYNCAPBCTRL_ENABLE(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_ASYNCAPBCTRL_ENABLE_SHIFT)) & SYSCON_ASYNCAPBCTRL_ENABLE_MASK)

/*! @name PIOPORCAP - POR captured value of port n */
#define SYSCON_PIOPORCAP_PIOPORCAP_MASK          (0xFFFFFFFFU)
#define SYSCON_PIOPORCAP_PIOPORCAP_SHIFT         (0U)
#define SYSCON_PIOPORCAP_PIOPORCAP(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PIOPORCAP_PIOPORCAP_SHIFT)) & SYSCON_PIOPORCAP_PIOPORCAP_MASK)

/* The count of SYSCON_PIOPORCAP */
#define SYSCON_PIOPORCAP_COUNT                   (2U)

/*! @name PIORESCAP - Reset captured value of port n */
#define SYSCON_PIORESCAP_PIORESCAP_MASK          (0xFFFFFFFFU)
#define SYSCON_PIORESCAP_PIORESCAP_SHIFT         (0U)
#define SYSCON_PIORESCAP_PIORESCAP(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PIORESCAP_PIORESCAP_SHIFT)) & SYSCON_PIORESCAP_PIORESCAP_MASK)

/* The count of SYSCON_PIORESCAP */
#define SYSCON_PIORESCAP_COUNT                   (2U)

/*! @name PRESETCTRL - Peripheral reset control n */
#define SYSCON_PRESETCTRL_MRT_RST_MASK           (0x1U)
#define SYSCON_PRESETCTRL_MRT_RST_SHIFT          (0U)
#define SYSCON_PRESETCTRL_MRT_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_MRT_RST_SHIFT)) & SYSCON_PRESETCTRL_MRT_RST_MASK)
#define SYSCON_PRESETCTRL_SCT0_RST_MASK          (0x4U)
#define SYSCON_PRESETCTRL_SCT0_RST_SHIFT         (2U)
#define SYSCON_PRESETCTRL_SCT0_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_SCT0_RST_SHIFT)) & SYSCON_PRESETCTRL_SCT0_RST_MASK)
#define SYSCON_PRESETCTRL_LCD_RST_MASK           (0x4U)
#define SYSCON_PRESETCTRL_LCD_RST_SHIFT          (2U)
#define SYSCON_PRESETCTRL_LCD_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_LCD_RST_SHIFT)) & SYSCON_PRESETCTRL_LCD_RST_MASK)
#define SYSCON_PRESETCTRL_SDIO_RST_MASK          (0x8U)
#define SYSCON_PRESETCTRL_SDIO_RST_SHIFT         (3U)
#define SYSCON_PRESETCTRL_SDIO_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_SDIO_RST_SHIFT)) & SYSCON_PRESETCTRL_SDIO_RST_MASK)
#define SYSCON_PRESETCTRL_USB1H_RST_MASK         (0x10U)
#define SYSCON_PRESETCTRL_USB1H_RST_SHIFT        (4U)
#define SYSCON_PRESETCTRL_USB1H_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_USB1H_RST_SHIFT)) & SYSCON_PRESETCTRL_USB1H_RST_MASK)
#define SYSCON_PRESETCTRL_USB1D_RST_MASK         (0x20U)
#define SYSCON_PRESETCTRL_USB1D_RST_SHIFT        (5U)
#define SYSCON_PRESETCTRL_USB1D_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_USB1D_RST_SHIFT)) & SYSCON_PRESETCTRL_USB1D_RST_MASK)
#define SYSCON_PRESETCTRL_USB1RAM_RST_MASK       (0x40U)
#define SYSCON_PRESETCTRL_USB1RAM_RST_SHIFT      (6U)
#define SYSCON_PRESETCTRL_USB1RAM_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_USB1RAM_RST_SHIFT)) & SYSCON_PRESETCTRL_USB1RAM_RST_MASK)
#define SYSCON_PRESETCTRL_EMC_RESET_MASK         (0x80U)
#define SYSCON_PRESETCTRL_EMC_RESET_SHIFT        (7U)
#define SYSCON_PRESETCTRL_EMC_RESET(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_EMC_RESET_SHIFT)) & SYSCON_PRESETCTRL_EMC_RESET_MASK)
#define SYSCON_PRESETCTRL_FLASH_RST_MASK         (0x80U)
#define SYSCON_PRESETCTRL_FLASH_RST_SHIFT        (7U)
#define SYSCON_PRESETCTRL_FLASH_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FLASH_RST_SHIFT)) & SYSCON_PRESETCTRL_FLASH_RST_MASK)
#define SYSCON_PRESETCTRL_MCAN0_RST_MASK         (0x80U)
#define SYSCON_PRESETCTRL_MCAN0_RST_SHIFT        (7U)
#define SYSCON_PRESETCTRL_MCAN0_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_MCAN0_RST_SHIFT)) & SYSCON_PRESETCTRL_MCAN0_RST_MASK)
#define SYSCON_PRESETCTRL_FMC_RST_MASK           (0x100U)
#define SYSCON_PRESETCTRL_FMC_RST_SHIFT          (8U)
#define SYSCON_PRESETCTRL_FMC_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FMC_RST_SHIFT)) & SYSCON_PRESETCTRL_FMC_RST_MASK)
#define SYSCON_PRESETCTRL_ETH_RST_MASK           (0x100U)
#define SYSCON_PRESETCTRL_ETH_RST_SHIFT          (8U)
#define SYSCON_PRESETCTRL_ETH_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_ETH_RST_SHIFT)) & SYSCON_PRESETCTRL_ETH_RST_MASK)
#define SYSCON_PRESETCTRL_MCAN1_RST_MASK         (0x100U)
#define SYSCON_PRESETCTRL_MCAN1_RST_SHIFT        (8U)
#define SYSCON_PRESETCTRL_MCAN1_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_MCAN1_RST_SHIFT)) & SYSCON_PRESETCTRL_MCAN1_RST_MASK)
#define SYSCON_PRESETCTRL_GPIO4_RST_MASK         (0x200U)
#define SYSCON_PRESETCTRL_GPIO4_RST_SHIFT        (9U)
#define SYSCON_PRESETCTRL_GPIO4_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_GPIO4_RST_SHIFT)) & SYSCON_PRESETCTRL_GPIO4_RST_MASK)
#define SYSCON_PRESETCTRL_EEPROM_RST_MASK        (0x200U)
#define SYSCON_PRESETCTRL_EEPROM_RST_SHIFT       (9U)
#define SYSCON_PRESETCTRL_EEPROM_RST(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_EEPROM_RST_SHIFT)) & SYSCON_PRESETCTRL_EEPROM_RST_MASK)
#define SYSCON_PRESETCTRL_GPIO5_RST_MASK         (0x400U)
#define SYSCON_PRESETCTRL_GPIO5_RST_SHIFT        (10U)
#define SYSCON_PRESETCTRL_GPIO5_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_GPIO5_RST_SHIFT)) & SYSCON_PRESETCTRL_GPIO5_RST_MASK)
#define SYSCON_PRESETCTRL_UTICK_RST_MASK         (0x400U)
#define SYSCON_PRESETCTRL_UTICK_RST_SHIFT        (10U)
#define SYSCON_PRESETCTRL_UTICK_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_UTICK_RST_SHIFT)) & SYSCON_PRESETCTRL_UTICK_RST_MASK)
#define SYSCON_PRESETCTRL_SPIFI_RST_MASK         (0x400U)
#define SYSCON_PRESETCTRL_SPIFI_RST_SHIFT        (10U)
#define SYSCON_PRESETCTRL_SPIFI_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_SPIFI_RST_SHIFT)) & SYSCON_PRESETCTRL_SPIFI_RST_MASK)
#define SYSCON_PRESETCTRL_AES_RST_MASK           (0x800U)
#define SYSCON_PRESETCTRL_AES_RST_SHIFT          (11U)
#define SYSCON_PRESETCTRL_AES_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_AES_RST_SHIFT)) & SYSCON_PRESETCTRL_AES_RST_MASK)
#define SYSCON_PRESETCTRL_MUX_RST_MASK           (0x800U)
#define SYSCON_PRESETCTRL_MUX_RST_SHIFT          (11U)
#define SYSCON_PRESETCTRL_MUX_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_MUX_RST_SHIFT)) & SYSCON_PRESETCTRL_MUX_RST_MASK)
#define SYSCON_PRESETCTRL_FC0_RST_MASK           (0x800U)
#define SYSCON_PRESETCTRL_FC0_RST_SHIFT          (11U)
#define SYSCON_PRESETCTRL_FC0_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC0_RST_SHIFT)) & SYSCON_PRESETCTRL_FC0_RST_MASK)
#define SYSCON_PRESETCTRL_OTP_RST_MASK           (0x1000U)
#define SYSCON_PRESETCTRL_OTP_RST_SHIFT          (12U)
#define SYSCON_PRESETCTRL_OTP_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_OTP_RST_SHIFT)) & SYSCON_PRESETCTRL_OTP_RST_MASK)
#define SYSCON_PRESETCTRL_FC1_RST_MASK           (0x1000U)
#define SYSCON_PRESETCTRL_FC1_RST_SHIFT          (12U)
#define SYSCON_PRESETCTRL_FC1_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC1_RST_SHIFT)) & SYSCON_PRESETCTRL_FC1_RST_MASK)
#define SYSCON_PRESETCTRL_IOCON_RST_MASK         (0x2000U)
#define SYSCON_PRESETCTRL_IOCON_RST_SHIFT        (13U)
#define SYSCON_PRESETCTRL_IOCON_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_IOCON_RST_SHIFT)) & SYSCON_PRESETCTRL_IOCON_RST_MASK)
#define SYSCON_PRESETCTRL_RNG_RST_MASK           (0x2000U)
#define SYSCON_PRESETCTRL_RNG_RST_SHIFT          (13U)
#define SYSCON_PRESETCTRL_RNG_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_RNG_RST_SHIFT)) & SYSCON_PRESETCTRL_RNG_RST_MASK)
#define SYSCON_PRESETCTRL_FC2_RST_MASK           (0x2000U)
#define SYSCON_PRESETCTRL_FC2_RST_SHIFT          (13U)
#define SYSCON_PRESETCTRL_FC2_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC2_RST_SHIFT)) & SYSCON_PRESETCTRL_FC2_RST_MASK)
#define SYSCON_PRESETCTRL_FC8_RST_MASK           (0x4000U)
#define SYSCON_PRESETCTRL_FC8_RST_SHIFT          (14U)
#define SYSCON_PRESETCTRL_FC8_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC8_RST_SHIFT)) & SYSCON_PRESETCTRL_FC8_RST_MASK)
#define SYSCON_PRESETCTRL_FC3_RST_MASK           (0x4000U)
#define SYSCON_PRESETCTRL_FC3_RST_SHIFT          (14U)
#define SYSCON_PRESETCTRL_FC3_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC3_RST_SHIFT)) & SYSCON_PRESETCTRL_FC3_RST_MASK)
#define SYSCON_PRESETCTRL_GPIO0_RST_MASK         (0x4000U)
#define SYSCON_PRESETCTRL_GPIO0_RST_SHIFT        (14U)
#define SYSCON_PRESETCTRL_GPIO0_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_GPIO0_RST_SHIFT)) & SYSCON_PRESETCTRL_GPIO0_RST_MASK)
#define SYSCON_PRESETCTRL_GPIO1_RST_MASK         (0x8000U)
#define SYSCON_PRESETCTRL_GPIO1_RST_SHIFT        (15U)
#define SYSCON_PRESETCTRL_GPIO1_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_GPIO1_RST_SHIFT)) & SYSCON_PRESETCTRL_GPIO1_RST_MASK)
#define SYSCON_PRESETCTRL_FC9_RST_MASK           (0x8000U)
#define SYSCON_PRESETCTRL_FC9_RST_SHIFT          (15U)
#define SYSCON_PRESETCTRL_FC9_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC9_RST_SHIFT)) & SYSCON_PRESETCTRL_FC9_RST_MASK)
#define SYSCON_PRESETCTRL_FC4_RST_MASK           (0x8000U)
#define SYSCON_PRESETCTRL_FC4_RST_SHIFT          (15U)
#define SYSCON_PRESETCTRL_FC4_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC4_RST_SHIFT)) & SYSCON_PRESETCTRL_FC4_RST_MASK)
#define SYSCON_PRESETCTRL_USB0HMR_RST_MASK       (0x10000U)
#define SYSCON_PRESETCTRL_USB0HMR_RST_SHIFT      (16U)
#define SYSCON_PRESETCTRL_USB0HMR_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_USB0HMR_RST_SHIFT)) & SYSCON_PRESETCTRL_USB0HMR_RST_MASK)
#define SYSCON_PRESETCTRL_GPIO2_RST_MASK         (0x10000U)
#define SYSCON_PRESETCTRL_GPIO2_RST_SHIFT        (16U)
#define SYSCON_PRESETCTRL_GPIO2_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_GPIO2_RST_SHIFT)) & SYSCON_PRESETCTRL_GPIO2_RST_MASK)
#define SYSCON_PRESETCTRL_FC5_RST_MASK           (0x10000U)
#define SYSCON_PRESETCTRL_FC5_RST_SHIFT          (16U)
#define SYSCON_PRESETCTRL_FC5_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC5_RST_SHIFT)) & SYSCON_PRESETCTRL_FC5_RST_MASK)
#define SYSCON_PRESETCTRL_GPIO3_RST_MASK         (0x20000U)
#define SYSCON_PRESETCTRL_GPIO3_RST_SHIFT        (17U)
#define SYSCON_PRESETCTRL_GPIO3_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_GPIO3_RST_SHIFT)) & SYSCON_PRESETCTRL_GPIO3_RST_MASK)
#define SYSCON_PRESETCTRL_FC6_RST_MASK           (0x20000U)
#define SYSCON_PRESETCTRL_FC6_RST_SHIFT          (17U)
#define SYSCON_PRESETCTRL_FC6_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC6_RST_SHIFT)) & SYSCON_PRESETCTRL_FC6_RST_MASK)
#define SYSCON_PRESETCTRL_USB0HSL_RST_MASK       (0x20000U)
#define SYSCON_PRESETCTRL_USB0HSL_RST_SHIFT      (17U)
#define SYSCON_PRESETCTRL_USB0HSL_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_USB0HSL_RST_SHIFT)) & SYSCON_PRESETCTRL_USB0HSL_RST_MASK)
#define SYSCON_PRESETCTRL_FC7_RST_MASK           (0x40000U)
#define SYSCON_PRESETCTRL_FC7_RST_SHIFT          (18U)
#define SYSCON_PRESETCTRL_FC7_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC7_RST_SHIFT)) & SYSCON_PRESETCTRL_FC7_RST_MASK)
#define SYSCON_PRESETCTRL_SHA_RST_MASK           (0x40000U)
#define SYSCON_PRESETCTRL_SHA_RST_SHIFT          (18U)
#define SYSCON_PRESETCTRL_SHA_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_SHA_RST_SHIFT)) & SYSCON_PRESETCTRL_SHA_RST_MASK)
#define SYSCON_PRESETCTRL_PINT_RST_MASK          (0x40000U)
#define SYSCON_PRESETCTRL_PINT_RST_SHIFT         (18U)
#define SYSCON_PRESETCTRL_PINT_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_PINT_RST_SHIFT)) & SYSCON_PRESETCTRL_PINT_RST_MASK)
#define SYSCON_PRESETCTRL_DMIC_RST_MASK          (0x80000U)
#define SYSCON_PRESETCTRL_DMIC_RST_SHIFT         (19U)
#define SYSCON_PRESETCTRL_DMIC_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_DMIC_RST_SHIFT)) & SYSCON_PRESETCTRL_DMIC_RST_MASK)
#define SYSCON_PRESETCTRL_SC0_RST_MASK           (0x80000U)
#define SYSCON_PRESETCTRL_SC0_RST_SHIFT          (19U)
#define SYSCON_PRESETCTRL_SC0_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_SC0_RST_SHIFT)) & SYSCON_PRESETCTRL_SC0_RST_MASK)
#define SYSCON_PRESETCTRL_GINT_RST_MASK          (0x80000U)
#define SYSCON_PRESETCTRL_GINT_RST_SHIFT         (19U)
#define SYSCON_PRESETCTRL_GINT_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_GINT_RST_SHIFT)) & SYSCON_PRESETCTRL_GINT_RST_MASK)
#define SYSCON_PRESETCTRL_SC1_RST_MASK           (0x100000U)
#define SYSCON_PRESETCTRL_SC1_RST_SHIFT          (20U)
#define SYSCON_PRESETCTRL_SC1_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_SC1_RST_SHIFT)) & SYSCON_PRESETCTRL_SC1_RST_MASK)
#define SYSCON_PRESETCTRL_DMA0_RST_MASK          (0x100000U)
#define SYSCON_PRESETCTRL_DMA0_RST_SHIFT         (20U)
#define SYSCON_PRESETCTRL_DMA0_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_DMA0_RST_SHIFT)) & SYSCON_PRESETCTRL_DMA0_RST_MASK)
#define SYSCON_PRESETCTRL_CRC_RST_MASK           (0x200000U)
#define SYSCON_PRESETCTRL_CRC_RST_SHIFT          (21U)
#define SYSCON_PRESETCTRL_CRC_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_CRC_RST_SHIFT)) & SYSCON_PRESETCTRL_CRC_RST_MASK)
#define SYSCON_PRESETCTRL_CTIMER2_RST_MASK       (0x400000U)
#define SYSCON_PRESETCTRL_CTIMER2_RST_SHIFT      (22U)
#define SYSCON_PRESETCTRL_CTIMER2_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_CTIMER2_RST_SHIFT)) & SYSCON_PRESETCTRL_CTIMER2_RST_MASK)
#define SYSCON_PRESETCTRL_WWDT_RST_MASK          (0x400000U)
#define SYSCON_PRESETCTRL_WWDT_RST_SHIFT         (22U)
#define SYSCON_PRESETCTRL_WWDT_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_WWDT_RST_SHIFT)) & SYSCON_PRESETCTRL_WWDT_RST_MASK)
#define SYSCON_PRESETCTRL_USB0D_RST_MASK         (0x2000000U)
#define SYSCON_PRESETCTRL_USB0D_RST_SHIFT        (25U)
#define SYSCON_PRESETCTRL_USB0D_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_USB0D_RST_SHIFT)) & SYSCON_PRESETCTRL_USB0D_RST_MASK)
#define SYSCON_PRESETCTRL_CTIMER0_RST_MASK       (0x4000000U)
#define SYSCON_PRESETCTRL_CTIMER0_RST_SHIFT      (26U)
#define SYSCON_PRESETCTRL_CTIMER0_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_CTIMER0_RST_SHIFT)) & SYSCON_PRESETCTRL_CTIMER0_RST_MASK)
#define SYSCON_PRESETCTRL_ADC0_RST_MASK          (0x8000000U)
#define SYSCON_PRESETCTRL_ADC0_RST_SHIFT         (27U)
#define SYSCON_PRESETCTRL_ADC0_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_ADC0_RST_SHIFT)) & SYSCON_PRESETCTRL_ADC0_RST_MASK)
#define SYSCON_PRESETCTRL_CTIMER1_RST_MASK       (0x8000000U)
#define SYSCON_PRESETCTRL_CTIMER1_RST_SHIFT      (27U)
#define SYSCON_PRESETCTRL_CTIMER1_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_CTIMER1_RST_SHIFT)) & SYSCON_PRESETCTRL_CTIMER1_RST_MASK)

/* The count of SYSCON_PRESETCTRL */
#define SYSCON_PRESETCTRL_COUNT                  (3U)

/*! @name PRESETCTRLSET - Set bits in PRESETCTRLn */
#define SYSCON_PRESETCTRLSET_RST_SET_MASK        (0xFFFFFFFFU)
#define SYSCON_PRESETCTRLSET_RST_SET_SHIFT       (0U)
#define SYSCON_PRESETCTRLSET_RST_SET(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRLSET_RST_SET_SHIFT)) & SYSCON_PRESETCTRLSET_RST_SET_MASK)

/* The count of SYSCON_PRESETCTRLSET */
#define SYSCON_PRESETCTRLSET_COUNT               (3U)

/*! @name PRESETCTRLCLR - Clear bits in PRESETCTRLn */
#define SYSCON_PRESETCTRLCLR_RST_CLR_MASK        (0xFFFFFFFFU)
#define SYSCON_PRESETCTRLCLR_RST_CLR_SHIFT       (0U)
#define SYSCON_PRESETCTRLCLR_RST_CLR(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRLCLR_RST_CLR_SHIFT)) & SYSCON_PRESETCTRLCLR_RST_CLR_MASK)

/* The count of SYSCON_PRESETCTRLCLR */
#define SYSCON_PRESETCTRLCLR_COUNT               (3U)

/*! @name SYSRSTSTAT - System reset status register */
#define SYSCON_SYSRSTSTAT_POR_MASK               (0x1U)
#define SYSCON_SYSRSTSTAT_POR_SHIFT              (0U)
#define SYSCON_SYSRSTSTAT_POR(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSRSTSTAT_POR_SHIFT)) & SYSCON_SYSRSTSTAT_POR_MASK)
#define SYSCON_SYSRSTSTAT_EXTRST_MASK            (0x2U)
#define SYSCON_SYSRSTSTAT_EXTRST_SHIFT           (1U)
#define SYSCON_SYSRSTSTAT_EXTRST(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSRSTSTAT_EXTRST_SHIFT)) & SYSCON_SYSRSTSTAT_EXTRST_MASK)
#define SYSCON_SYSRSTSTAT_WDT_MASK               (0x4U)
#define SYSCON_SYSRSTSTAT_WDT_SHIFT              (2U)
#define SYSCON_SYSRSTSTAT_WDT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSRSTSTAT_WDT_SHIFT)) & SYSCON_SYSRSTSTAT_WDT_MASK)
#define SYSCON_SYSRSTSTAT_BOD_MASK               (0x8U)
#define SYSCON_SYSRSTSTAT_BOD_SHIFT              (3U)
#define SYSCON_SYSRSTSTAT_BOD(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSRSTSTAT_BOD_SHIFT)) & SYSCON_SYSRSTSTAT_BOD_MASK)
#define SYSCON_SYSRSTSTAT_SYSRST_MASK            (0x10U)
#define SYSCON_SYSRSTSTAT_SYSRST_SHIFT           (4U)
#define SYSCON_SYSRSTSTAT_SYSRST(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSRSTSTAT_SYSRST_SHIFT)) & SYSCON_SYSRSTSTAT_SYSRST_MASK)

/*! @name AHBCLKCTRL - AHB Clock control n */
#define SYSCON_AHBCLKCTRL_MRT_MASK               (0x1U)
#define SYSCON_AHBCLKCTRL_MRT_SHIFT              (0U)
#define SYSCON_AHBCLKCTRL_MRT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_MRT_SHIFT)) & SYSCON_AHBCLKCTRL_MRT_MASK)
#define SYSCON_AHBCLKCTRL_RIT_MASK               (0x2U)
#define SYSCON_AHBCLKCTRL_RIT_SHIFT              (1U)
#define SYSCON_AHBCLKCTRL_RIT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_RIT_SHIFT)) & SYSCON_AHBCLKCTRL_RIT_MASK)
#define SYSCON_AHBCLKCTRL_ROM_MASK               (0x2U)
#define SYSCON_AHBCLKCTRL_ROM_SHIFT              (1U)
#define SYSCON_AHBCLKCTRL_ROM(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_ROM_SHIFT)) & SYSCON_AHBCLKCTRL_ROM_MASK)
#define SYSCON_AHBCLKCTRL_SCT0_MASK              (0x4U)
#define SYSCON_AHBCLKCTRL_SCT0_SHIFT             (2U)
#define SYSCON_AHBCLKCTRL_SCT0(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_SCT0_SHIFT)) & SYSCON_AHBCLKCTRL_SCT0_MASK)
#define SYSCON_AHBCLKCTRL_LCD_MASK               (0x4U)
#define SYSCON_AHBCLKCTRL_LCD_SHIFT              (2U)
#define SYSCON_AHBCLKCTRL_LCD(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_LCD_SHIFT)) & SYSCON_AHBCLKCTRL_LCD_MASK)
#define SYSCON_AHBCLKCTRL_SRAM1_MASK             (0x8U)
#define SYSCON_AHBCLKCTRL_SRAM1_SHIFT            (3U)
#define SYSCON_AHBCLKCTRL_SRAM1(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_SRAM1_SHIFT)) & SYSCON_AHBCLKCTRL_SRAM1_MASK)
#define SYSCON_AHBCLKCTRL_SDIO_MASK              (0x8U)
#define SYSCON_AHBCLKCTRL_SDIO_SHIFT             (3U)
#define SYSCON_AHBCLKCTRL_SDIO(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_SDIO_SHIFT)) & SYSCON_AHBCLKCTRL_SDIO_MASK)
#define SYSCON_AHBCLKCTRL_SRAM2_MASK             (0x10U)
#define SYSCON_AHBCLKCTRL_SRAM2_SHIFT            (4U)
#define SYSCON_AHBCLKCTRL_SRAM2(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_SRAM2_SHIFT)) & SYSCON_AHBCLKCTRL_SRAM2_MASK)
#define SYSCON_AHBCLKCTRL_USB1H_MASK             (0x10U)
#define SYSCON_AHBCLKCTRL_USB1H_SHIFT            (4U)
#define SYSCON_AHBCLKCTRL_USB1H(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_USB1H_SHIFT)) & SYSCON_AHBCLKCTRL_USB1H_MASK)
#define SYSCON_AHBCLKCTRL_SRAM3_MASK             (0x20U)
#define SYSCON_AHBCLKCTRL_SRAM3_SHIFT            (5U)
#define SYSCON_AHBCLKCTRL_SRAM3(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_SRAM3_SHIFT)) & SYSCON_AHBCLKCTRL_SRAM3_MASK)
#define SYSCON_AHBCLKCTRL_USB1D_MASK             (0x20U)
#define SYSCON_AHBCLKCTRL_USB1D_SHIFT            (5U)
#define SYSCON_AHBCLKCTRL_USB1D(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_USB1D_SHIFT)) & SYSCON_AHBCLKCTRL_USB1D_MASK)
#define SYSCON_AHBCLKCTRL_USB1RAM_MASK           (0x40U)
#define SYSCON_AHBCLKCTRL_USB1RAM_SHIFT          (6U)
#define SYSCON_AHBCLKCTRL_USB1RAM(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_USB1RAM_SHIFT)) & SYSCON_AHBCLKCTRL_USB1RAM_MASK)
#define SYSCON_AHBCLKCTRL_FLASH_MASK             (0x80U)
#define SYSCON_AHBCLKCTRL_FLASH_SHIFT            (7U)
#define SYSCON_AHBCLKCTRL_FLASH(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLASH_SHIFT)) & SYSCON_AHBCLKCTRL_FLASH_MASK)
#define SYSCON_AHBCLKCTRL_EMC_MASK               (0x80U)
#define SYSCON_AHBCLKCTRL_EMC_SHIFT              (7U)
#define SYSCON_AHBCLKCTRL_EMC(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_EMC_SHIFT)) & SYSCON_AHBCLKCTRL_EMC_MASK)
#define SYSCON_AHBCLKCTRL_MCAN0_MASK             (0x80U)
#define SYSCON_AHBCLKCTRL_MCAN0_SHIFT            (7U)
#define SYSCON_AHBCLKCTRL_MCAN0(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_MCAN0_SHIFT)) & SYSCON_AHBCLKCTRL_MCAN0_MASK)
#define SYSCON_AHBCLKCTRL_FMC_MASK               (0x100U)
#define SYSCON_AHBCLKCTRL_FMC_SHIFT              (8U)
#define SYSCON_AHBCLKCTRL_FMC(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FMC_SHIFT)) & SYSCON_AHBCLKCTRL_FMC_MASK)
#define SYSCON_AHBCLKCTRL_ETH_MASK               (0x100U)
#define SYSCON_AHBCLKCTRL_ETH_SHIFT              (8U)
#define SYSCON_AHBCLKCTRL_ETH(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_ETH_SHIFT)) & SYSCON_AHBCLKCTRL_ETH_MASK)
#define SYSCON_AHBCLKCTRL_MCAN1_MASK             (0x100U)
#define SYSCON_AHBCLKCTRL_MCAN1_SHIFT            (8U)
#define SYSCON_AHBCLKCTRL_MCAN1(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_MCAN1_SHIFT)) & SYSCON_AHBCLKCTRL_MCAN1_MASK)
#define SYSCON_AHBCLKCTRL_EEPROM_MASK            (0x200U)
#define SYSCON_AHBCLKCTRL_EEPROM_SHIFT           (9U)
#define SYSCON_AHBCLKCTRL_EEPROM(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_EEPROM_SHIFT)) & SYSCON_AHBCLKCTRL_EEPROM_MASK)
#define SYSCON_AHBCLKCTRL_GPIO4_MASK             (0x200U)
#define SYSCON_AHBCLKCTRL_GPIO4_SHIFT            (9U)
#define SYSCON_AHBCLKCTRL_GPIO4(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_GPIO4_SHIFT)) & SYSCON_AHBCLKCTRL_GPIO4_MASK)
#define SYSCON_AHBCLKCTRL_GPIO5_MASK             (0x400U)
#define SYSCON_AHBCLKCTRL_GPIO5_SHIFT            (10U)
#define SYSCON_AHBCLKCTRL_GPIO5(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_GPIO5_SHIFT)) & SYSCON_AHBCLKCTRL_GPIO5_MASK)
#define SYSCON_AHBCLKCTRL_UTICK_MASK             (0x400U)
#define SYSCON_AHBCLKCTRL_UTICK_SHIFT            (10U)
#define SYSCON_AHBCLKCTRL_UTICK(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_UTICK_SHIFT)) & SYSCON_AHBCLKCTRL_UTICK_MASK)
#define SYSCON_AHBCLKCTRL_SPIFI_MASK             (0x400U)
#define SYSCON_AHBCLKCTRL_SPIFI_SHIFT            (10U)
#define SYSCON_AHBCLKCTRL_SPIFI(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_SPIFI_SHIFT)) & SYSCON_AHBCLKCTRL_SPIFI_MASK)
#define SYSCON_AHBCLKCTRL_INPUTMUX_MASK          (0x800U)
#define SYSCON_AHBCLKCTRL_INPUTMUX_SHIFT         (11U)
#define SYSCON_AHBCLKCTRL_INPUTMUX(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_INPUTMUX_SHIFT)) & SYSCON_AHBCLKCTRL_INPUTMUX_MASK)
#define SYSCON_AHBCLKCTRL_AES_MASK               (0x800U)
#define SYSCON_AHBCLKCTRL_AES_SHIFT              (11U)
#define SYSCON_AHBCLKCTRL_AES(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_AES_SHIFT)) & SYSCON_AHBCLKCTRL_AES_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM0_MASK         (0x800U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM0_SHIFT        (11U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM0(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM0_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM0_MASK)
#define SYSCON_AHBCLKCTRL_OTP_MASK               (0x1000U)
#define SYSCON_AHBCLKCTRL_OTP_SHIFT              (12U)
#define SYSCON_AHBCLKCTRL_OTP(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_OTP_SHIFT)) & SYSCON_AHBCLKCTRL_OTP_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM1_MASK         (0x1000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM1_SHIFT        (12U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM1(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM1_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM1_MASK)
#define SYSCON_AHBCLKCTRL_RNG_MASK               (0x2000U)
#define SYSCON_AHBCLKCTRL_RNG_SHIFT              (13U)
#define SYSCON_AHBCLKCTRL_RNG(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_RNG_SHIFT)) & SYSCON_AHBCLKCTRL_RNG_MASK)
#define SYSCON_AHBCLKCTRL_IOCON_MASK             (0x2000U)
#define SYSCON_AHBCLKCTRL_IOCON_SHIFT            (13U)
#define SYSCON_AHBCLKCTRL_IOCON(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_IOCON_SHIFT)) & SYSCON_AHBCLKCTRL_IOCON_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM2_MASK         (0x2000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM2_SHIFT        (13U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM2(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM2_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM2_MASK)
#define SYSCON_AHBCLKCTRL_GPIO0_MASK             (0x4000U)
#define SYSCON_AHBCLKCTRL_GPIO0_SHIFT            (14U)
#define SYSCON_AHBCLKCTRL_GPIO0(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_GPIO0_SHIFT)) & SYSCON_AHBCLKCTRL_GPIO0_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM3_MASK         (0x4000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM3_SHIFT        (14U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM3(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM3_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM3_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM8_MASK         (0x4000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM8_SHIFT        (14U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM8(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM8_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM8_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM9_MASK         (0x8000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM9_SHIFT        (15U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM9(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM9_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM9_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM4_MASK         (0x8000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM4_SHIFT        (15U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM4(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM4_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM4_MASK)
#define SYSCON_AHBCLKCTRL_GPIO1_MASK             (0x8000U)
#define SYSCON_AHBCLKCTRL_GPIO1_SHIFT            (15U)
#define SYSCON_AHBCLKCTRL_GPIO1(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_GPIO1_SHIFT)) & SYSCON_AHBCLKCTRL_GPIO1_MASK)
#define SYSCON_AHBCLKCTRL_GPIO2_MASK             (0x10000U)
#define SYSCON_AHBCLKCTRL_GPIO2_SHIFT            (16U)
#define SYSCON_AHBCLKCTRL_GPIO2(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_GPIO2_SHIFT)) & SYSCON_AHBCLKCTRL_GPIO2_MASK)
#define SYSCON_AHBCLKCTRL_USB0HMR_MASK           (0x10000U)
#define SYSCON_AHBCLKCTRL_USB0HMR_SHIFT          (16U)
#define SYSCON_AHBCLKCTRL_USB0HMR(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_USB0HMR_SHIFT)) & SYSCON_AHBCLKCTRL_USB0HMR_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM5_MASK         (0x10000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM5_SHIFT        (16U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM5(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM5_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM5_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM6_MASK         (0x20000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM6_SHIFT        (17U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM6(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM6_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM6_MASK)
#define SYSCON_AHBCLKCTRL_GPIO3_MASK             (0x20000U)
#define SYSCON_AHBCLKCTRL_GPIO3_SHIFT            (17U)
#define SYSCON_AHBCLKCTRL_GPIO3(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_GPIO3_SHIFT)) & SYSCON_AHBCLKCTRL_GPIO3_MASK)
#define SYSCON_AHBCLKCTRL_USB0HSL_MASK           (0x20000U)
#define SYSCON_AHBCLKCTRL_USB0HSL_SHIFT          (17U)
#define SYSCON_AHBCLKCTRL_USB0HSL(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_USB0HSL_SHIFT)) & SYSCON_AHBCLKCTRL_USB0HSL_MASK)
#define SYSCON_AHBCLKCTRL_PINT_MASK              (0x40000U)
#define SYSCON_AHBCLKCTRL_PINT_SHIFT             (18U)
#define SYSCON_AHBCLKCTRL_PINT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_PINT_SHIFT)) & SYSCON_AHBCLKCTRL_PINT_MASK)
#define SYSCON_AHBCLKCTRL_SHA0_MASK              (0x40000U)
#define SYSCON_AHBCLKCTRL_SHA0_SHIFT             (18U)
#define SYSCON_AHBCLKCTRL_SHA0(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_SHA0_SHIFT)) & SYSCON_AHBCLKCTRL_SHA0_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM7_MASK         (0x40000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM7_SHIFT        (18U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM7(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM7_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM7_MASK)
#define SYSCON_AHBCLKCTRL_DMIC_MASK              (0x80000U)
#define SYSCON_AHBCLKCTRL_DMIC_SHIFT             (19U)
#define SYSCON_AHBCLKCTRL_DMIC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_DMIC_SHIFT)) & SYSCON_AHBCLKCTRL_DMIC_MASK)
#define SYSCON_AHBCLKCTRL_GINT_MASK              (0x80000U)
#define SYSCON_AHBCLKCTRL_GINT_SHIFT             (19U)
#define SYSCON_AHBCLKCTRL_GINT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_GINT_SHIFT)) & SYSCON_AHBCLKCTRL_GINT_MASK)
#define SYSCON_AHBCLKCTRL_SC0_MASK               (0x80000U)
#define SYSCON_AHBCLKCTRL_SC0_SHIFT              (19U)
#define SYSCON_AHBCLKCTRL_SC0(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_SC0_SHIFT)) & SYSCON_AHBCLKCTRL_SC0_MASK)
#define SYSCON_AHBCLKCTRL_SC1_MASK               (0x100000U)
#define SYSCON_AHBCLKCTRL_SC1_SHIFT              (20U)
#define SYSCON_AHBCLKCTRL_SC1(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_SC1_SHIFT)) & SYSCON_AHBCLKCTRL_SC1_MASK)
#define SYSCON_AHBCLKCTRL_DMA_MASK               (0x100000U)
#define SYSCON_AHBCLKCTRL_DMA_SHIFT              (20U)
#define SYSCON_AHBCLKCTRL_DMA(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_DMA_SHIFT)) & SYSCON_AHBCLKCTRL_DMA_MASK)
#define SYSCON_AHBCLKCTRL_CRC_MASK               (0x200000U)
#define SYSCON_AHBCLKCTRL_CRC_SHIFT              (21U)
#define SYSCON_AHBCLKCTRL_CRC(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_CRC_SHIFT)) & SYSCON_AHBCLKCTRL_CRC_MASK)
#define SYSCON_AHBCLKCTRL_WWDT_MASK              (0x400000U)
#define SYSCON_AHBCLKCTRL_WWDT_SHIFT             (22U)
#define SYSCON_AHBCLKCTRL_WWDT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_WWDT_SHIFT)) & SYSCON_AHBCLKCTRL_WWDT_MASK)
#define SYSCON_AHBCLKCTRL_CTIMER2_MASK           (0x400000U)
#define SYSCON_AHBCLKCTRL_CTIMER2_SHIFT          (22U)
#define SYSCON_AHBCLKCTRL_CTIMER2(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_CTIMER2_SHIFT)) & SYSCON_AHBCLKCTRL_CTIMER2_MASK)
#define SYSCON_AHBCLKCTRL_RTC_MASK               (0x800000U)
#define SYSCON_AHBCLKCTRL_RTC_SHIFT              (23U)
#define SYSCON_AHBCLKCTRL_RTC(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_RTC_SHIFT)) & SYSCON_AHBCLKCTRL_RTC_MASK)
#define SYSCON_AHBCLKCTRL_USB0D_MASK             (0x2000000U)
#define SYSCON_AHBCLKCTRL_USB0D_SHIFT            (25U)
#define SYSCON_AHBCLKCTRL_USB0D(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_USB0D_SHIFT)) & SYSCON_AHBCLKCTRL_USB0D_MASK)
#define SYSCON_AHBCLKCTRL_CTIMER0_MASK           (0x4000000U)
#define SYSCON_AHBCLKCTRL_CTIMER0_SHIFT          (26U)
#define SYSCON_AHBCLKCTRL_CTIMER0(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_CTIMER0_SHIFT)) & SYSCON_AHBCLKCTRL_CTIMER0_MASK)
#define SYSCON_AHBCLKCTRL_CTIMER1_MASK           (0x8000000U)
#define SYSCON_AHBCLKCTRL_CTIMER1_SHIFT          (27U)
#define SYSCON_AHBCLKCTRL_CTIMER1(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_CTIMER1_SHIFT)) & SYSCON_AHBCLKCTRL_CTIMER1_MASK)
#define SYSCON_AHBCLKCTRL_ADC0_MASK              (0x8000000U)
#define SYSCON_AHBCLKCTRL_ADC0_SHIFT             (27U)
#define SYSCON_AHBCLKCTRL_ADC0(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_ADC0_SHIFT)) & SYSCON_AHBCLKCTRL_ADC0_MASK)

/* The count of SYSCON_AHBCLKCTRL */
#define SYSCON_AHBCLKCTRL_COUNT                  (3U)

/*! @name AHBCLKCTRLSET - Set bits in AHBCLKCTRLn */
#define SYSCON_AHBCLKCTRLSET_CLK_SET_MASK        (0xFFFFFFFFU)
#define SYSCON_AHBCLKCTRLSET_CLK_SET_SHIFT       (0U)
#define SYSCON_AHBCLKCTRLSET_CLK_SET(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRLSET_CLK_SET_SHIFT)) & SYSCON_AHBCLKCTRLSET_CLK_SET_MASK)

/* The count of SYSCON_AHBCLKCTRLSET */
#define SYSCON_AHBCLKCTRLSET_COUNT               (3U)

/*! @name AHBCLKCTRLCLR - Clear bits in AHBCLKCTRLn */
#define SYSCON_AHBCLKCTRLCLR_CLK_CLR_MASK        (0xFFFFFFFFU)
#define SYSCON_AHBCLKCTRLCLR_CLK_CLR_SHIFT       (0U)
#define SYSCON_AHBCLKCTRLCLR_CLK_CLR(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRLCLR_CLK_CLR_SHIFT)) & SYSCON_AHBCLKCTRLCLR_CLK_CLR_MASK)

/* The count of SYSCON_AHBCLKCTRLCLR */
#define SYSCON_AHBCLKCTRLCLR_COUNT               (3U)

/*! @name MAINCLKSELA - Main clock source select A */
#define SYSCON_MAINCLKSELA_SEL_MASK              (0x3U)
#define SYSCON_MAINCLKSELA_SEL_SHIFT             (0U)
#define SYSCON_MAINCLKSELA_SEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_MAINCLKSELA_SEL_SHIFT)) & SYSCON_MAINCLKSELA_SEL_MASK)

/*! @name MAINCLKSELB - Main clock source select B */
#define SYSCON_MAINCLKSELB_SEL_MASK              (0x3U)
#define SYSCON_MAINCLKSELB_SEL_SHIFT             (0U)
#define SYSCON_MAINCLKSELB_SEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_MAINCLKSELB_SEL_SHIFT)) & SYSCON_MAINCLKSELB_SEL_MASK)

/*! @name CLKOUTSELA - CLKOUT clock source select A */
#define SYSCON_CLKOUTSELA_SEL_MASK               (0x7U)
#define SYSCON_CLKOUTSELA_SEL_SHIFT              (0U)
#define SYSCON_CLKOUTSELA_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTSELA_SEL_SHIFT)) & SYSCON_CLKOUTSELA_SEL_MASK)

/*! @name SYSPLLCLKSEL - PLL clock source select */
#define SYSCON_SYSPLLCLKSEL_SEL_MASK             (0x7U)
#define SYSCON_SYSPLLCLKSEL_SEL_SHIFT            (0U)
#define SYSCON_SYSPLLCLKSEL_SEL(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCLKSEL_SEL_SHIFT)) & SYSCON_SYSPLLCLKSEL_SEL_MASK)

/*! @name AUDPLLCLKSEL - Audio PLL clock source select */
#define SYSCON_AUDPLLCLKSEL_SEL_MASK             (0x7U)
#define SYSCON_AUDPLLCLKSEL_SEL_SHIFT            (0U)
#define SYSCON_AUDPLLCLKSEL_SEL(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLCLKSEL_SEL_SHIFT)) & SYSCON_AUDPLLCLKSEL_SEL_MASK)

/*! @name SPIFICLKSEL - SPIFI clock source select */
#define SYSCON_SPIFICLKSEL_SEL_MASK              (0x7U)
#define SYSCON_SPIFICLKSEL_SEL_SHIFT             (0U)
#define SYSCON_SPIFICLKSEL_SEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SPIFICLKSEL_SEL_SHIFT)) & SYSCON_SPIFICLKSEL_SEL_MASK)

/*! @name ADCCLKSEL - ADC clock source select */
#define SYSCON_ADCCLKSEL_SEL_MASK                (0x7U)
#define SYSCON_ADCCLKSEL_SEL_SHIFT               (0U)
#define SYSCON_ADCCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKSEL_SEL_SHIFT)) & SYSCON_ADCCLKSEL_SEL_MASK)

/*! @name USB0CLKSEL - USB0 clock source select */
#define SYSCON_USB0CLKSEL_SEL_MASK               (0x7U)
#define SYSCON_USB0CLKSEL_SEL_SHIFT              (0U)
#define SYSCON_USB0CLKSEL_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKSEL_SEL_SHIFT)) & SYSCON_USB0CLKSEL_SEL_MASK)

/*! @name USB1CLKSEL - USB1 clock source select */
#define SYSCON_USB1CLKSEL_SEL_MASK               (0x7U)
#define SYSCON_USB1CLKSEL_SEL_SHIFT              (0U)
#define SYSCON_USB1CLKSEL_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1CLKSEL_SEL_SHIFT)) & SYSCON_USB1CLKSEL_SEL_MASK)

/*! @name FCLKSEL - Flexcomm 0 clock source select */
#define SYSCON_FCLKSEL_SEL_MASK                  (0x7U)
#define SYSCON_FCLKSEL_SEL_SHIFT                 (0U)
#define SYSCON_FCLKSEL_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_FCLKSEL_SEL_SHIFT)) & SYSCON_FCLKSEL_SEL_MASK)

/* The count of SYSCON_FCLKSEL */
#define SYSCON_FCLKSEL_COUNT                     (10U)

/*! @name MCLKCLKSEL - MCLK clock source select */
#define SYSCON_MCLKCLKSEL_SEL_MASK               (0x7U)
#define SYSCON_MCLKCLKSEL_SEL_SHIFT              (0U)
#define SYSCON_MCLKCLKSEL_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKCLKSEL_SEL_SHIFT)) & SYSCON_MCLKCLKSEL_SEL_MASK)

/*! @name FRGCLKSEL - Fractional Rate Generator clock source select */
#define SYSCON_FRGCLKSEL_SEL_MASK                (0x7U)
#define SYSCON_FRGCLKSEL_SEL_SHIFT               (0U)
#define SYSCON_FRGCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_FRGCLKSEL_SEL_SHIFT)) & SYSCON_FRGCLKSEL_SEL_MASK)

/*! @name DMICCLKSEL - Digital microphone (DMIC) subsystem clock select */
#define SYSCON_DMICCLKSEL_SEL_MASK               (0x7U)
#define SYSCON_DMICCLKSEL_SEL_SHIFT              (0U)
#define SYSCON_DMICCLKSEL_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_DMICCLKSEL_SEL_SHIFT)) & SYSCON_DMICCLKSEL_SEL_MASK)

/*! @name SCTCLKSEL - SCTimer/PWM clock source select */
#define SYSCON_SCTCLKSEL_SEL_MASK                (0x7U)
#define SYSCON_SCTCLKSEL_SEL_SHIFT               (0U)
#define SYSCON_SCTCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_SCTCLKSEL_SEL_SHIFT)) & SYSCON_SCTCLKSEL_SEL_MASK)

/*! @name LCDCLKSEL - LCD clock source select */
#define SYSCON_LCDCLKSEL_SEL_MASK                (0x3U)
#define SYSCON_LCDCLKSEL_SEL_SHIFT               (0U)
#define SYSCON_LCDCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_LCDCLKSEL_SEL_SHIFT)) & SYSCON_LCDCLKSEL_SEL_MASK)

/*! @name SDIOCLKSEL - SDIO clock source select */
#define SYSCON_SDIOCLKSEL_SEL_MASK               (0x7U)
#define SYSCON_SDIOCLKSEL_SEL_SHIFT              (0U)
#define SYSCON_SDIOCLKSEL_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SDIOCLKSEL_SEL_SHIFT)) & SYSCON_SDIOCLKSEL_SEL_MASK)

/*! @name SYSTICKCLKDIV - SYSTICK clock divider */
#define SYSCON_SYSTICKCLKDIV_DIV_MASK            (0xFFU)
#define SYSCON_SYSTICKCLKDIV_DIV_SHIFT           (0U)
#define SYSCON_SYSTICKCLKDIV_DIV(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTICKCLKDIV_DIV_SHIFT)) & SYSCON_SYSTICKCLKDIV_DIV_MASK)
#define SYSCON_SYSTICKCLKDIV_RESET_MASK          (0x20000000U)
#define SYSCON_SYSTICKCLKDIV_RESET_SHIFT         (29U)
#define SYSCON_SYSTICKCLKDIV_RESET(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTICKCLKDIV_RESET_SHIFT)) & SYSCON_SYSTICKCLKDIV_RESET_MASK)
#define SYSCON_SYSTICKCLKDIV_HALT_MASK           (0x40000000U)
#define SYSCON_SYSTICKCLKDIV_HALT_SHIFT          (30U)
#define SYSCON_SYSTICKCLKDIV_HALT(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTICKCLKDIV_HALT_SHIFT)) & SYSCON_SYSTICKCLKDIV_HALT_MASK)
#define SYSCON_SYSTICKCLKDIV_REQFLAG_MASK        (0x80000000U)
#define SYSCON_SYSTICKCLKDIV_REQFLAG_SHIFT       (31U)
#define SYSCON_SYSTICKCLKDIV_REQFLAG(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTICKCLKDIV_REQFLAG_SHIFT)) & SYSCON_SYSTICKCLKDIV_REQFLAG_MASK)

/*! @name ARMTRACECLKDIV - ARM Trace clock divider */
#define SYSCON_ARMTRACECLKDIV_DIV_MASK           (0xFFU)
#define SYSCON_ARMTRACECLKDIV_DIV_SHIFT          (0U)
#define SYSCON_ARMTRACECLKDIV_DIV(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_ARMTRACECLKDIV_DIV_SHIFT)) & SYSCON_ARMTRACECLKDIV_DIV_MASK)
#define SYSCON_ARMTRACECLKDIV_RESET_MASK         (0x20000000U)
#define SYSCON_ARMTRACECLKDIV_RESET_SHIFT        (29U)
#define SYSCON_ARMTRACECLKDIV_RESET(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_ARMTRACECLKDIV_RESET_SHIFT)) & SYSCON_ARMTRACECLKDIV_RESET_MASK)
#define SYSCON_ARMTRACECLKDIV_HALT_MASK          (0x40000000U)
#define SYSCON_ARMTRACECLKDIV_HALT_SHIFT         (30U)
#define SYSCON_ARMTRACECLKDIV_HALT(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_ARMTRACECLKDIV_HALT_SHIFT)) & SYSCON_ARMTRACECLKDIV_HALT_MASK)
#define SYSCON_ARMTRACECLKDIV_REQFLAG_MASK       (0x80000000U)
#define SYSCON_ARMTRACECLKDIV_REQFLAG_SHIFT      (31U)
#define SYSCON_ARMTRACECLKDIV_REQFLAG(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_ARMTRACECLKDIV_REQFLAG_SHIFT)) & SYSCON_ARMTRACECLKDIV_REQFLAG_MASK)

/*! @name CAN0CLKDIV - MCAN0 clock divider */
#define SYSCON_CAN0CLKDIV_DIV_MASK               (0xFFU)
#define SYSCON_CAN0CLKDIV_DIV_SHIFT              (0U)
#define SYSCON_CAN0CLKDIV_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_CAN0CLKDIV_DIV_SHIFT)) & SYSCON_CAN0CLKDIV_DIV_MASK)
#define SYSCON_CAN0CLKDIV_RESET_MASK             (0x20000000U)
#define SYSCON_CAN0CLKDIV_RESET_SHIFT            (29U)
#define SYSCON_CAN0CLKDIV_RESET(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_CAN0CLKDIV_RESET_SHIFT)) & SYSCON_CAN0CLKDIV_RESET_MASK)
#define SYSCON_CAN0CLKDIV_HALT_MASK              (0x40000000U)
#define SYSCON_CAN0CLKDIV_HALT_SHIFT             (30U)
#define SYSCON_CAN0CLKDIV_HALT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_CAN0CLKDIV_HALT_SHIFT)) & SYSCON_CAN0CLKDIV_HALT_MASK)
#define SYSCON_CAN0CLKDIV_REQFLAG_MASK           (0x80000000U)
#define SYSCON_CAN0CLKDIV_REQFLAG_SHIFT          (31U)
#define SYSCON_CAN0CLKDIV_REQFLAG(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_CAN0CLKDIV_REQFLAG_SHIFT)) & SYSCON_CAN0CLKDIV_REQFLAG_MASK)

/*! @name CAN1CLKDIV - MCAN1 clock divider */
#define SYSCON_CAN1CLKDIV_DIV_MASK               (0xFFU)
#define SYSCON_CAN1CLKDIV_DIV_SHIFT              (0U)
#define SYSCON_CAN1CLKDIV_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_CAN1CLKDIV_DIV_SHIFT)) & SYSCON_CAN1CLKDIV_DIV_MASK)
#define SYSCON_CAN1CLKDIV_RESET_MASK             (0x20000000U)
#define SYSCON_CAN1CLKDIV_RESET_SHIFT            (29U)
#define SYSCON_CAN1CLKDIV_RESET(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_CAN1CLKDIV_RESET_SHIFT)) & SYSCON_CAN1CLKDIV_RESET_MASK)
#define SYSCON_CAN1CLKDIV_HALT_MASK              (0x40000000U)
#define SYSCON_CAN1CLKDIV_HALT_SHIFT             (30U)
#define SYSCON_CAN1CLKDIV_HALT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_CAN1CLKDIV_HALT_SHIFT)) & SYSCON_CAN1CLKDIV_HALT_MASK)
#define SYSCON_CAN1CLKDIV_REQFLAG_MASK           (0x80000000U)
#define SYSCON_CAN1CLKDIV_REQFLAG_SHIFT          (31U)
#define SYSCON_CAN1CLKDIV_REQFLAG(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_CAN1CLKDIV_REQFLAG_SHIFT)) & SYSCON_CAN1CLKDIV_REQFLAG_MASK)

/*! @name SC0CLKDIV - Smartcard0 clock divider */
#define SYSCON_SC0CLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_SC0CLKDIV_DIV_SHIFT               (0U)
#define SYSCON_SC0CLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_SC0CLKDIV_DIV_SHIFT)) & SYSCON_SC0CLKDIV_DIV_MASK)
#define SYSCON_SC0CLKDIV_RESET_MASK              (0x20000000U)
#define SYSCON_SC0CLKDIV_RESET_SHIFT             (29U)
#define SYSCON_SC0CLKDIV_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SC0CLKDIV_RESET_SHIFT)) & SYSCON_SC0CLKDIV_RESET_MASK)
#define SYSCON_SC0CLKDIV_HALT_MASK               (0x40000000U)
#define SYSCON_SC0CLKDIV_HALT_SHIFT              (30U)
#define SYSCON_SC0CLKDIV_HALT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SC0CLKDIV_HALT_SHIFT)) & SYSCON_SC0CLKDIV_HALT_MASK)
#define SYSCON_SC0CLKDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_SC0CLKDIV_REQFLAG_SHIFT           (31U)
#define SYSCON_SC0CLKDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SC0CLKDIV_REQFLAG_SHIFT)) & SYSCON_SC0CLKDIV_REQFLAG_MASK)

/*! @name SC1CLKDIV - Smartcard1 clock divider */
#define SYSCON_SC1CLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_SC1CLKDIV_DIV_SHIFT               (0U)
#define SYSCON_SC1CLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_SC1CLKDIV_DIV_SHIFT)) & SYSCON_SC1CLKDIV_DIV_MASK)
#define SYSCON_SC1CLKDIV_RESET_MASK              (0x20000000U)
#define SYSCON_SC1CLKDIV_RESET_SHIFT             (29U)
#define SYSCON_SC1CLKDIV_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SC1CLKDIV_RESET_SHIFT)) & SYSCON_SC1CLKDIV_RESET_MASK)
#define SYSCON_SC1CLKDIV_HALT_MASK               (0x40000000U)
#define SYSCON_SC1CLKDIV_HALT_SHIFT              (30U)
#define SYSCON_SC1CLKDIV_HALT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SC1CLKDIV_HALT_SHIFT)) & SYSCON_SC1CLKDIV_HALT_MASK)
#define SYSCON_SC1CLKDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_SC1CLKDIV_REQFLAG_SHIFT           (31U)
#define SYSCON_SC1CLKDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SC1CLKDIV_REQFLAG_SHIFT)) & SYSCON_SC1CLKDIV_REQFLAG_MASK)

/*! @name AHBCLKDIV - AHB clock divider */
#define SYSCON_AHBCLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_AHBCLKDIV_DIV_SHIFT               (0U)
#define SYSCON_AHBCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKDIV_DIV_SHIFT)) & SYSCON_AHBCLKDIV_DIV_MASK)
#define SYSCON_AHBCLKDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_AHBCLKDIV_REQFLAG_SHIFT           (31U)
#define SYSCON_AHBCLKDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKDIV_REQFLAG_SHIFT)) & SYSCON_AHBCLKDIV_REQFLAG_MASK)

/*! @name CLKOUTDIV - CLKOUT clock divider */
#define SYSCON_CLKOUTDIV_DIV_MASK                (0xFFU)
#define SYSCON_CLKOUTDIV_DIV_SHIFT               (0U)
#define SYSCON_CLKOUTDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTDIV_DIV_SHIFT)) & SYSCON_CLKOUTDIV_DIV_MASK)
#define SYSCON_CLKOUTDIV_RESET_MASK              (0x20000000U)
#define SYSCON_CLKOUTDIV_RESET_SHIFT             (29U)
#define SYSCON_CLKOUTDIV_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTDIV_RESET_SHIFT)) & SYSCON_CLKOUTDIV_RESET_MASK)
#define SYSCON_CLKOUTDIV_HALT_MASK               (0x40000000U)
#define SYSCON_CLKOUTDIV_HALT_SHIFT              (30U)
#define SYSCON_CLKOUTDIV_HALT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTDIV_HALT_SHIFT)) & SYSCON_CLKOUTDIV_HALT_MASK)
#define SYSCON_CLKOUTDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_CLKOUTDIV_REQFLAG_SHIFT           (31U)
#define SYSCON_CLKOUTDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTDIV_REQFLAG_SHIFT)) & SYSCON_CLKOUTDIV_REQFLAG_MASK)

/*! @name FROHFCLKDIV - FROHF clock divider */
#define SYSCON_FROHFCLKDIV_DIV_MASK              (0xFFU)
#define SYSCON_FROHFCLKDIV_DIV_SHIFT             (0U)
#define SYSCON_FROHFCLKDIV_DIV(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_FROHFCLKDIV_DIV_SHIFT)) & SYSCON_FROHFCLKDIV_DIV_MASK)
#define SYSCON_FROHFCLKDIV_RESET_MASK            (0x20000000U)
#define SYSCON_FROHFCLKDIV_RESET_SHIFT           (29U)
#define SYSCON_FROHFCLKDIV_RESET(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FROHFCLKDIV_RESET_SHIFT)) & SYSCON_FROHFCLKDIV_RESET_MASK)
#define SYSCON_FROHFCLKDIV_HALT_MASK             (0x40000000U)
#define SYSCON_FROHFCLKDIV_HALT_SHIFT            (30U)
#define SYSCON_FROHFCLKDIV_HALT(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FROHFCLKDIV_HALT_SHIFT)) & SYSCON_FROHFCLKDIV_HALT_MASK)
#define SYSCON_FROHFCLKDIV_REQFLAG_MASK          (0x80000000U)
#define SYSCON_FROHFCLKDIV_REQFLAG_SHIFT         (31U)
#define SYSCON_FROHFCLKDIV_REQFLAG(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_FROHFCLKDIV_REQFLAG_SHIFT)) & SYSCON_FROHFCLKDIV_REQFLAG_MASK)

/*! @name SPIFICLKDIV - SPIFI clock divider */
#define SYSCON_SPIFICLKDIV_DIV_MASK              (0xFFU)
#define SYSCON_SPIFICLKDIV_DIV_SHIFT             (0U)
#define SYSCON_SPIFICLKDIV_DIV(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SPIFICLKDIV_DIV_SHIFT)) & SYSCON_SPIFICLKDIV_DIV_MASK)
#define SYSCON_SPIFICLKDIV_RESET_MASK            (0x20000000U)
#define SYSCON_SPIFICLKDIV_RESET_SHIFT           (29U)
#define SYSCON_SPIFICLKDIV_RESET(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SPIFICLKDIV_RESET_SHIFT)) & SYSCON_SPIFICLKDIV_RESET_MASK)
#define SYSCON_SPIFICLKDIV_HALT_MASK             (0x40000000U)
#define SYSCON_SPIFICLKDIV_HALT_SHIFT            (30U)
#define SYSCON_SPIFICLKDIV_HALT(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_SPIFICLKDIV_HALT_SHIFT)) & SYSCON_SPIFICLKDIV_HALT_MASK)
#define SYSCON_SPIFICLKDIV_REQFLAG_MASK          (0x80000000U)
#define SYSCON_SPIFICLKDIV_REQFLAG_SHIFT         (31U)
#define SYSCON_SPIFICLKDIV_REQFLAG(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SPIFICLKDIV_REQFLAG_SHIFT)) & SYSCON_SPIFICLKDIV_REQFLAG_MASK)

/*! @name ADCCLKDIV - ADC clock divider */
#define SYSCON_ADCCLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_ADCCLKDIV_DIV_SHIFT               (0U)
#define SYSCON_ADCCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKDIV_DIV_SHIFT)) & SYSCON_ADCCLKDIV_DIV_MASK)
#define SYSCON_ADCCLKDIV_RESET_MASK              (0x20000000U)
#define SYSCON_ADCCLKDIV_RESET_SHIFT             (29U)
#define SYSCON_ADCCLKDIV_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKDIV_RESET_SHIFT)) & SYSCON_ADCCLKDIV_RESET_MASK)
#define SYSCON_ADCCLKDIV_HALT_MASK               (0x40000000U)
#define SYSCON_ADCCLKDIV_HALT_SHIFT              (30U)
#define SYSCON_ADCCLKDIV_HALT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKDIV_HALT_SHIFT)) & SYSCON_ADCCLKDIV_HALT_MASK)
#define SYSCON_ADCCLKDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_ADCCLKDIV_REQFLAG_SHIFT           (31U)
#define SYSCON_ADCCLKDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKDIV_REQFLAG_SHIFT)) & SYSCON_ADCCLKDIV_REQFLAG_MASK)

/*! @name USB0CLKDIV - USB0 clock divider */
#define SYSCON_USB0CLKDIV_DIV_MASK               (0xFFU)
#define SYSCON_USB0CLKDIV_DIV_SHIFT              (0U)
#define SYSCON_USB0CLKDIV_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKDIV_DIV_SHIFT)) & SYSCON_USB0CLKDIV_DIV_MASK)
#define SYSCON_USB0CLKDIV_RESET_MASK             (0x20000000U)
#define SYSCON_USB0CLKDIV_RESET_SHIFT            (29U)
#define SYSCON_USB0CLKDIV_RESET(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKDIV_RESET_SHIFT)) & SYSCON_USB0CLKDIV_RESET_MASK)
#define SYSCON_USB0CLKDIV_HALT_MASK              (0x40000000U)
#define SYSCON_USB0CLKDIV_HALT_SHIFT             (30U)
#define SYSCON_USB0CLKDIV_HALT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKDIV_HALT_SHIFT)) & SYSCON_USB0CLKDIV_HALT_MASK)
#define SYSCON_USB0CLKDIV_REQFLAG_MASK           (0x80000000U)
#define SYSCON_USB0CLKDIV_REQFLAG_SHIFT          (31U)
#define SYSCON_USB0CLKDIV_REQFLAG(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKDIV_REQFLAG_SHIFT)) & SYSCON_USB0CLKDIV_REQFLAG_MASK)

/*! @name USB1CLKDIV - USB1 clock divider */
#define SYSCON_USB1CLKDIV_DIV_MASK               (0xFFU)
#define SYSCON_USB1CLKDIV_DIV_SHIFT              (0U)
#define SYSCON_USB1CLKDIV_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1CLKDIV_DIV_SHIFT)) & SYSCON_USB1CLKDIV_DIV_MASK)
#define SYSCON_USB1CLKDIV_RESET_MASK             (0x20000000U)
#define SYSCON_USB1CLKDIV_RESET_SHIFT            (29U)
#define SYSCON_USB1CLKDIV_RESET(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1CLKDIV_RESET_SHIFT)) & SYSCON_USB1CLKDIV_RESET_MASK)
#define SYSCON_USB1CLKDIV_HALT_MASK              (0x40000000U)
#define SYSCON_USB1CLKDIV_HALT_SHIFT             (30U)
#define SYSCON_USB1CLKDIV_HALT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1CLKDIV_HALT_SHIFT)) & SYSCON_USB1CLKDIV_HALT_MASK)
#define SYSCON_USB1CLKDIV_REQFLAG_MASK           (0x80000000U)
#define SYSCON_USB1CLKDIV_REQFLAG_SHIFT          (31U)
#define SYSCON_USB1CLKDIV_REQFLAG(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1CLKDIV_REQFLAG_SHIFT)) & SYSCON_USB1CLKDIV_REQFLAG_MASK)

/*! @name FRGCTRL - Fractional rate divider */
#define SYSCON_FRGCTRL_DIV_MASK                  (0xFFU)
#define SYSCON_FRGCTRL_DIV_SHIFT                 (0U)
#define SYSCON_FRGCTRL_DIV(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_FRGCTRL_DIV_SHIFT)) & SYSCON_FRGCTRL_DIV_MASK)
#define SYSCON_FRGCTRL_MULT_MASK                 (0xFF00U)
#define SYSCON_FRGCTRL_MULT_SHIFT                (8U)
#define SYSCON_FRGCTRL_MULT(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_FRGCTRL_MULT_SHIFT)) & SYSCON_FRGCTRL_MULT_MASK)

/*! @name DMICCLKDIV - DMIC clock divider */
#define SYSCON_DMICCLKDIV_DIV_MASK               (0xFFU)
#define SYSCON_DMICCLKDIV_DIV_SHIFT              (0U)
#define SYSCON_DMICCLKDIV_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_DMICCLKDIV_DIV_SHIFT)) & SYSCON_DMICCLKDIV_DIV_MASK)
#define SYSCON_DMICCLKDIV_RESET_MASK             (0x20000000U)
#define SYSCON_DMICCLKDIV_RESET_SHIFT            (29U)
#define SYSCON_DMICCLKDIV_RESET(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_DMICCLKDIV_RESET_SHIFT)) & SYSCON_DMICCLKDIV_RESET_MASK)
#define SYSCON_DMICCLKDIV_HALT_MASK              (0x40000000U)
#define SYSCON_DMICCLKDIV_HALT_SHIFT             (30U)
#define SYSCON_DMICCLKDIV_HALT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_DMICCLKDIV_HALT_SHIFT)) & SYSCON_DMICCLKDIV_HALT_MASK)
#define SYSCON_DMICCLKDIV_REQFLAG_MASK           (0x80000000U)
#define SYSCON_DMICCLKDIV_REQFLAG_SHIFT          (31U)
#define SYSCON_DMICCLKDIV_REQFLAG(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_DMICCLKDIV_REQFLAG_SHIFT)) & SYSCON_DMICCLKDIV_REQFLAG_MASK)

/*! @name MCLKDIV - I2S MCLK clock divider */
#define SYSCON_MCLKDIV_DIV_MASK                  (0xFFU)
#define SYSCON_MCLKDIV_DIV_SHIFT                 (0U)
#define SYSCON_MCLKDIV_DIV(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKDIV_DIV_SHIFT)) & SYSCON_MCLKDIV_DIV_MASK)
#define SYSCON_MCLKDIV_RESET_MASK                (0x20000000U)
#define SYSCON_MCLKDIV_RESET_SHIFT               (29U)
#define SYSCON_MCLKDIV_RESET(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKDIV_RESET_SHIFT)) & SYSCON_MCLKDIV_RESET_MASK)
#define SYSCON_MCLKDIV_HALT_MASK                 (0x40000000U)
#define SYSCON_MCLKDIV_HALT_SHIFT                (30U)
#define SYSCON_MCLKDIV_HALT(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKDIV_HALT_SHIFT)) & SYSCON_MCLKDIV_HALT_MASK)
#define SYSCON_MCLKDIV_REQFLAG_MASK              (0x80000000U)
#define SYSCON_MCLKDIV_REQFLAG_SHIFT             (31U)
#define SYSCON_MCLKDIV_REQFLAG(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKDIV_REQFLAG_SHIFT)) & SYSCON_MCLKDIV_REQFLAG_MASK)

/*! @name LCDCLKDIV - LCD clock divider */
#define SYSCON_LCDCLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_LCDCLKDIV_DIV_SHIFT               (0U)
#define SYSCON_LCDCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_LCDCLKDIV_DIV_SHIFT)) & SYSCON_LCDCLKDIV_DIV_MASK)
#define SYSCON_LCDCLKDIV_RESET_MASK              (0x20000000U)
#define SYSCON_LCDCLKDIV_RESET_SHIFT             (29U)
#define SYSCON_LCDCLKDIV_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_LCDCLKDIV_RESET_SHIFT)) & SYSCON_LCDCLKDIV_RESET_MASK)
#define SYSCON_LCDCLKDIV_HALT_MASK               (0x40000000U)
#define SYSCON_LCDCLKDIV_HALT_SHIFT              (30U)
#define SYSCON_LCDCLKDIV_HALT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_LCDCLKDIV_HALT_SHIFT)) & SYSCON_LCDCLKDIV_HALT_MASK)
#define SYSCON_LCDCLKDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_LCDCLKDIV_REQFLAG_SHIFT           (31U)
#define SYSCON_LCDCLKDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_LCDCLKDIV_REQFLAG_SHIFT)) & SYSCON_LCDCLKDIV_REQFLAG_MASK)

/*! @name SCTCLKDIV - SCT/PWM clock divider */
#define SYSCON_SCTCLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_SCTCLKDIV_DIV_SHIFT               (0U)
#define SYSCON_SCTCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_SCTCLKDIV_DIV_SHIFT)) & SYSCON_SCTCLKDIV_DIV_MASK)
#define SYSCON_SCTCLKDIV_RESET_MASK              (0x20000000U)
#define SYSCON_SCTCLKDIV_RESET_SHIFT             (29U)
#define SYSCON_SCTCLKDIV_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SCTCLKDIV_RESET_SHIFT)) & SYSCON_SCTCLKDIV_RESET_MASK)
#define SYSCON_SCTCLKDIV_HALT_MASK               (0x40000000U)
#define SYSCON_SCTCLKDIV_HALT_SHIFT              (30U)
#define SYSCON_SCTCLKDIV_HALT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SCTCLKDIV_HALT_SHIFT)) & SYSCON_SCTCLKDIV_HALT_MASK)
#define SYSCON_SCTCLKDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_SCTCLKDIV_REQFLAG_SHIFT           (31U)
#define SYSCON_SCTCLKDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SCTCLKDIV_REQFLAG_SHIFT)) & SYSCON_SCTCLKDIV_REQFLAG_MASK)

/*! @name EMCCLKDIV - EMC clock divider */
#define SYSCON_EMCCLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_EMCCLKDIV_DIV_SHIFT               (0U)
#define SYSCON_EMCCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_EMCCLKDIV_DIV_SHIFT)) & SYSCON_EMCCLKDIV_DIV_MASK)
#define SYSCON_EMCCLKDIV_RESET_MASK              (0x20000000U)
#define SYSCON_EMCCLKDIV_RESET_SHIFT             (29U)
#define SYSCON_EMCCLKDIV_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_EMCCLKDIV_RESET_SHIFT)) & SYSCON_EMCCLKDIV_RESET_MASK)
#define SYSCON_EMCCLKDIV_HALT_MASK               (0x40000000U)
#define SYSCON_EMCCLKDIV_HALT_SHIFT              (30U)
#define SYSCON_EMCCLKDIV_HALT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_EMCCLKDIV_HALT_SHIFT)) & SYSCON_EMCCLKDIV_HALT_MASK)
#define SYSCON_EMCCLKDIV_REQFLAG_MASK            (0x80000000U)
#define SYSCON_EMCCLKDIV_REQFLAG_SHIFT           (31U)
#define SYSCON_EMCCLKDIV_REQFLAG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_EMCCLKDIV_REQFLAG_SHIFT)) & SYSCON_EMCCLKDIV_REQFLAG_MASK)

/*! @name SDIOCLKDIV - SDIO clock divider */
#define SYSCON_SDIOCLKDIV_DIV_MASK               (0xFFU)
#define SYSCON_SDIOCLKDIV_DIV_SHIFT              (0U)
#define SYSCON_SDIOCLKDIV_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SDIOCLKDIV_DIV_SHIFT)) & SYSCON_SDIOCLKDIV_DIV_MASK)
#define SYSCON_SDIOCLKDIV_RESET_MASK             (0x20000000U)
#define SYSCON_SDIOCLKDIV_RESET_SHIFT            (29U)
#define SYSCON_SDIOCLKDIV_RESET(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_SDIOCLKDIV_RESET_SHIFT)) & SYSCON_SDIOCLKDIV_RESET_MASK)
#define SYSCON_SDIOCLKDIV_HALT_MASK              (0x40000000U)
#define SYSCON_SDIOCLKDIV_HALT_SHIFT             (30U)
#define SYSCON_SDIOCLKDIV_HALT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SDIOCLKDIV_HALT_SHIFT)) & SYSCON_SDIOCLKDIV_HALT_MASK)
#define SYSCON_SDIOCLKDIV_REQFLAG_MASK           (0x80000000U)
#define SYSCON_SDIOCLKDIV_REQFLAG_SHIFT          (31U)
#define SYSCON_SDIOCLKDIV_REQFLAG(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SDIOCLKDIV_REQFLAG_SHIFT)) & SYSCON_SDIOCLKDIV_REQFLAG_MASK)

/*! @name FLASHCFG - Flash wait states configuration */
#define SYSCON_FLASHCFG_FETCHCFG_MASK            (0x3U)
#define SYSCON_FLASHCFG_FETCHCFG_SHIFT           (0U)
#define SYSCON_FLASHCFG_FETCHCFG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCFG_FETCHCFG_SHIFT)) & SYSCON_FLASHCFG_FETCHCFG_MASK)
#define SYSCON_FLASHCFG_DATACFG_MASK             (0xCU)
#define SYSCON_FLASHCFG_DATACFG_SHIFT            (2U)
#define SYSCON_FLASHCFG_DATACFG(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCFG_DATACFG_SHIFT)) & SYSCON_FLASHCFG_DATACFG_MASK)
#define SYSCON_FLASHCFG_ACCEL_MASK               (0x10U)
#define SYSCON_FLASHCFG_ACCEL_SHIFT              (4U)
#define SYSCON_FLASHCFG_ACCEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCFG_ACCEL_SHIFT)) & SYSCON_FLASHCFG_ACCEL_MASK)
#define SYSCON_FLASHCFG_PREFEN_MASK              (0x20U)
#define SYSCON_FLASHCFG_PREFEN_SHIFT             (5U)
#define SYSCON_FLASHCFG_PREFEN(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCFG_PREFEN_SHIFT)) & SYSCON_FLASHCFG_PREFEN_MASK)
#define SYSCON_FLASHCFG_PREFOVR_MASK             (0x40U)
#define SYSCON_FLASHCFG_PREFOVR_SHIFT            (6U)
#define SYSCON_FLASHCFG_PREFOVR(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCFG_PREFOVR_SHIFT)) & SYSCON_FLASHCFG_PREFOVR_MASK)
#define SYSCON_FLASHCFG_FLASHTIM_MASK            (0xF000U)
#define SYSCON_FLASHCFG_FLASHTIM_SHIFT           (12U)
#define SYSCON_FLASHCFG_FLASHTIM(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCFG_FLASHTIM_SHIFT)) & SYSCON_FLASHCFG_FLASHTIM_MASK)

/*! @name USB0CLKCTRL - USB0 clock control */
#define SYSCON_USB0CLKCTRL_AP_FS_DEV_CLK_MASK    (0x1U)
#define SYSCON_USB0CLKCTRL_AP_FS_DEV_CLK_SHIFT   (0U)
#define SYSCON_USB0CLKCTRL_AP_FS_DEV_CLK(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKCTRL_AP_FS_DEV_CLK_SHIFT)) & SYSCON_USB0CLKCTRL_AP_FS_DEV_CLK_MASK)
#define SYSCON_USB0CLKCTRL_POL_FS_DEV_CLK_MASK   (0x2U)
#define SYSCON_USB0CLKCTRL_POL_FS_DEV_CLK_SHIFT  (1U)
#define SYSCON_USB0CLKCTRL_POL_FS_DEV_CLK(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKCTRL_POL_FS_DEV_CLK_SHIFT)) & SYSCON_USB0CLKCTRL_POL_FS_DEV_CLK_MASK)
#define SYSCON_USB0CLKCTRL_AP_FS_HOST_CLK_MASK   (0x4U)
#define SYSCON_USB0CLKCTRL_AP_FS_HOST_CLK_SHIFT  (2U)
#define SYSCON_USB0CLKCTRL_AP_FS_HOST_CLK(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKCTRL_AP_FS_HOST_CLK_SHIFT)) & SYSCON_USB0CLKCTRL_AP_FS_HOST_CLK_MASK)
#define SYSCON_USB0CLKCTRL_POL_FS_HOST_CLK_MASK  (0x8U)
#define SYSCON_USB0CLKCTRL_POL_FS_HOST_CLK_SHIFT (3U)
#define SYSCON_USB0CLKCTRL_POL_FS_HOST_CLK(x)    (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKCTRL_POL_FS_HOST_CLK_SHIFT)) & SYSCON_USB0CLKCTRL_POL_FS_HOST_CLK_MASK)
#define SYSCON_USB0CLKCTRL_PU_DISABLE_MASK       (0x10U)
#define SYSCON_USB0CLKCTRL_PU_DISABLE_SHIFT      (4U)
#define SYSCON_USB0CLKCTRL_PU_DISABLE(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKCTRL_PU_DISABLE_SHIFT)) & SYSCON_USB0CLKCTRL_PU_DISABLE_MASK)

/*! @name USB0CLKSTAT - USB0 clock status */
#define SYSCON_USB0CLKSTAT_DEV_NEED_CLKST_MASK   (0x1U)
#define SYSCON_USB0CLKSTAT_DEV_NEED_CLKST_SHIFT  (0U)
#define SYSCON_USB0CLKSTAT_DEV_NEED_CLKST(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKSTAT_DEV_NEED_CLKST_SHIFT)) & SYSCON_USB0CLKSTAT_DEV_NEED_CLKST_MASK)
#define SYSCON_USB0CLKSTAT_HOST_NEED_CLKST_MASK  (0x2U)
#define SYSCON_USB0CLKSTAT_HOST_NEED_CLKST_SHIFT (1U)
#define SYSCON_USB0CLKSTAT_HOST_NEED_CLKST(x)    (((uint32_t)(((uint32_t)(x)) << SYSCON_USB0CLKSTAT_HOST_NEED_CLKST_SHIFT)) & SYSCON_USB0CLKSTAT_HOST_NEED_CLKST_MASK)

/*! @name FREQMECTRL - Frequency measure register */
#define SYSCON_FREQMECTRL_CAPVAL_MASK            (0x3FFFU)
#define SYSCON_FREQMECTRL_CAPVAL_SHIFT           (0U)
#define SYSCON_FREQMECTRL_CAPVAL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FREQMECTRL_CAPVAL_SHIFT)) & SYSCON_FREQMECTRL_CAPVAL_MASK)
#define SYSCON_FREQMECTRL_PROG_MASK              (0x80000000U)
#define SYSCON_FREQMECTRL_PROG_SHIFT             (31U)
#define SYSCON_FREQMECTRL_PROG(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_FREQMECTRL_PROG_SHIFT)) & SYSCON_FREQMECTRL_PROG_MASK)

/*! @name MCLKIO - MCLK input/output control */
#define SYSCON_MCLKIO_DIR_MASK                   (0x1U)
#define SYSCON_MCLKIO_DIR_SHIFT                  (0U)
#define SYSCON_MCLKIO_DIR(x)                     (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKIO_DIR_SHIFT)) & SYSCON_MCLKIO_DIR_MASK)

/*! @name USB1CLKCTRL - USB1 clock control */
#define SYSCON_USB1CLKCTRL_AP_FS_DEV_CLK_MASK    (0x1U)
#define SYSCON_USB1CLKCTRL_AP_FS_DEV_CLK_SHIFT   (0U)
#define SYSCON_USB1CLKCTRL_AP_FS_DEV_CLK(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1CLKCTRL_AP_FS_DEV_CLK_SHIFT)) & SYSCON_USB1CLKCTRL_AP_FS_DEV_CLK_MASK)
#define SYSCON_USB1CLKCTRL_POL_FS_DEV_CLK_MASK   (0x2U)
#define SYSCON_USB1CLKCTRL_POL_FS_DEV_CLK_SHIFT  (1U)
#define SYSCON_USB1CLKCTRL_POL_FS_DEV_CLK(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1CLKCTRL_POL_FS_DEV_CLK_SHIFT)) & SYSCON_USB1CLKCTRL_POL_FS_DEV_CLK_MASK)
#define SYSCON_USB1CLKCTRL_AP_FS_HOST_CLK_MASK   (0x4U)
#define SYSCON_USB1CLKCTRL_AP_FS_HOST_CLK_SHIFT  (2U)
#define SYSCON_USB1CLKCTRL_AP_FS_HOST_CLK(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1CLKCTRL_AP_FS_HOST_CLK_SHIFT)) & SYSCON_USB1CLKCTRL_AP_FS_HOST_CLK_MASK)
#define SYSCON_USB1CLKCTRL_POL_FS_HOST_CLK_MASK  (0x8U)
#define SYSCON_USB1CLKCTRL_POL_FS_HOST_CLK_SHIFT (3U)
#define SYSCON_USB1CLKCTRL_POL_FS_HOST_CLK(x)    (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1CLKCTRL_POL_FS_HOST_CLK_SHIFT)) & SYSCON_USB1CLKCTRL_POL_FS_HOST_CLK_MASK)
#define SYSCON_USB1CLKCTRL_HS_DEV_WAKEUP_N_MASK  (0x10U)
#define SYSCON_USB1CLKCTRL_HS_DEV_WAKEUP_N_SHIFT (4U)
#define SYSCON_USB1CLKCTRL_HS_DEV_WAKEUP_N(x)    (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1CLKCTRL_HS_DEV_WAKEUP_N_SHIFT)) & SYSCON_USB1CLKCTRL_HS_DEV_WAKEUP_N_MASK)

/*! @name USB1CLKSTAT - USB1 clock status */
#define SYSCON_USB1CLKSTAT_DEV_NEED_CLKST_MASK   (0x1U)
#define SYSCON_USB1CLKSTAT_DEV_NEED_CLKST_SHIFT  (0U)
#define SYSCON_USB1CLKSTAT_DEV_NEED_CLKST(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1CLKSTAT_DEV_NEED_CLKST_SHIFT)) & SYSCON_USB1CLKSTAT_DEV_NEED_CLKST_MASK)
#define SYSCON_USB1CLKSTAT_HOST_NEED_CLKST_MASK  (0x2U)
#define SYSCON_USB1CLKSTAT_HOST_NEED_CLKST_SHIFT (1U)
#define SYSCON_USB1CLKSTAT_HOST_NEED_CLKST(x)    (((uint32_t)(((uint32_t)(x)) << SYSCON_USB1CLKSTAT_HOST_NEED_CLKST_SHIFT)) & SYSCON_USB1CLKSTAT_HOST_NEED_CLKST_MASK)

/*! @name EMCSYSCTRL - EMC system control */
#define SYSCON_EMCSYSCTRL_EMCSC_MASK             (0x1U)
#define SYSCON_EMCSYSCTRL_EMCSC_SHIFT            (0U)
#define SYSCON_EMCSYSCTRL_EMCSC(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_EMCSYSCTRL_EMCSC_SHIFT)) & SYSCON_EMCSYSCTRL_EMCSC_MASK)
#define SYSCON_EMCSYSCTRL_EMCRD_MASK             (0x2U)
#define SYSCON_EMCSYSCTRL_EMCRD_SHIFT            (1U)
#define SYSCON_EMCSYSCTRL_EMCRD(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_EMCSYSCTRL_EMCRD_SHIFT)) & SYSCON_EMCSYSCTRL_EMCRD_MASK)
#define SYSCON_EMCSYSCTRL_EMCBC_MASK             (0x4U)
#define SYSCON_EMCSYSCTRL_EMCBC_SHIFT            (2U)
#define SYSCON_EMCSYSCTRL_EMCBC(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_EMCSYSCTRL_EMCBC_SHIFT)) & SYSCON_EMCSYSCTRL_EMCBC_MASK)
#define SYSCON_EMCSYSCTRL_EMCFBCLKINSEL_MASK     (0x8U)
#define SYSCON_EMCSYSCTRL_EMCFBCLKINSEL_SHIFT    (3U)
#define SYSCON_EMCSYSCTRL_EMCFBCLKINSEL(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_EMCSYSCTRL_EMCFBCLKINSEL_SHIFT)) & SYSCON_EMCSYSCTRL_EMCFBCLKINSEL_MASK)

/*! @name EMCDLYCTRL - EMC clock delay control */
#define SYSCON_EMCDLYCTRL_CMD_DELAY_MASK         (0x1FU)
#define SYSCON_EMCDLYCTRL_CMD_DELAY_SHIFT        (0U)
#define SYSCON_EMCDLYCTRL_CMD_DELAY(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_EMCDLYCTRL_CMD_DELAY_SHIFT)) & SYSCON_EMCDLYCTRL_CMD_DELAY_MASK)
#define SYSCON_EMCDLYCTRL_FBCLK_DELAY_MASK       (0x1F00U)
#define SYSCON_EMCDLYCTRL_FBCLK_DELAY_SHIFT      (8U)
#define SYSCON_EMCDLYCTRL_FBCLK_DELAY(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_EMCDLYCTRL_FBCLK_DELAY_SHIFT)) & SYSCON_EMCDLYCTRL_FBCLK_DELAY_MASK)

/*! @name EMCDLYCAL - EMC delay chain calibration control */
#define SYSCON_EMCDLYCAL_CALVALUE_MASK           (0xFFU)
#define SYSCON_EMCDLYCAL_CALVALUE_SHIFT          (0U)
#define SYSCON_EMCDLYCAL_CALVALUE(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_EMCDLYCAL_CALVALUE_SHIFT)) & SYSCON_EMCDLYCAL_CALVALUE_MASK)
#define SYSCON_EMCDLYCAL_START_MASK              (0x4000U)
#define SYSCON_EMCDLYCAL_START_SHIFT             (14U)
#define SYSCON_EMCDLYCAL_START(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_EMCDLYCAL_START_SHIFT)) & SYSCON_EMCDLYCAL_START_MASK)
#define SYSCON_EMCDLYCAL_DONE_MASK               (0x8000U)
#define SYSCON_EMCDLYCAL_DONE_SHIFT              (15U)
#define SYSCON_EMCDLYCAL_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_EMCDLYCAL_DONE_SHIFT)) & SYSCON_EMCDLYCAL_DONE_MASK)

/*! @name ETHPHYSEL - Ethernet PHY Selection */
#define SYSCON_ETHPHYSEL_PHY_SEL_MASK            (0x4U)
#define SYSCON_ETHPHYSEL_PHY_SEL_SHIFT           (2U)
#define SYSCON_ETHPHYSEL_PHY_SEL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_ETHPHYSEL_PHY_SEL_SHIFT)) & SYSCON_ETHPHYSEL_PHY_SEL_MASK)

/*! @name ETHSBDCTRL - Ethernet SBD flow control */
#define SYSCON_ETHSBDCTRL_SBD_CTRL_MASK          (0x3U)
#define SYSCON_ETHSBDCTRL_SBD_CTRL_SHIFT         (0U)
#define SYSCON_ETHSBDCTRL_SBD_CTRL(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_ETHSBDCTRL_SBD_CTRL_SHIFT)) & SYSCON_ETHSBDCTRL_SBD_CTRL_MASK)

/*! @name SDIOCLKCTRL - SDIO CCLKIN phase and delay control */
#define SYSCON_SDIOCLKCTRL_CCLK_DRV_PHASE_MASK   (0x3U)
#define SYSCON_SDIOCLKCTRL_CCLK_DRV_PHASE_SHIFT  (0U)
#define SYSCON_SDIOCLKCTRL_CCLK_DRV_PHASE(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_SDIOCLKCTRL_CCLK_DRV_PHASE_SHIFT)) & SYSCON_SDIOCLKCTRL_CCLK_DRV_PHASE_MASK)
#define SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_PHASE_MASK (0xCU)
#define SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_PHASE_SHIFT (2U)
#define SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_PHASE(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_PHASE_SHIFT)) & SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_PHASE_MASK)
#define SYSCON_SDIOCLKCTRL_PHASE_ACTIVE_MASK     (0x80U)
#define SYSCON_SDIOCLKCTRL_PHASE_ACTIVE_SHIFT    (7U)
#define SYSCON_SDIOCLKCTRL_PHASE_ACTIVE(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_SDIOCLKCTRL_PHASE_ACTIVE_SHIFT)) & SYSCON_SDIOCLKCTRL_PHASE_ACTIVE_MASK)
#define SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY_MASK   (0x1F0000U)
#define SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY_SHIFT  (16U)
#define SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY_SHIFT)) & SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY_MASK)
#define SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY_ACTIVE_MASK (0x800000U)
#define SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY_ACTIVE_SHIFT (23U)
#define SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY_ACTIVE(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY_ACTIVE_SHIFT)) & SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY_ACTIVE_MASK)
#define SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY_MASK (0x1F000000U)
#define SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY_SHIFT (24U)
#define SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY_SHIFT)) & SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY_MASK)
#define SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY_ACTIVE_MASK (0x80000000U)
#define SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY_ACTIVE_SHIFT (31U)
#define SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY_ACTIVE(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY_ACTIVE_SHIFT)) & SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY_ACTIVE_MASK)

/*! @name FROCTRL - FRO oscillator control */
#define SYSCON_FROCTRL_TRIM_MASK                 (0x3FFFU)
#define SYSCON_FROCTRL_TRIM_SHIFT                (0U)
#define SYSCON_FROCTRL_TRIM(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_TRIM_SHIFT)) & SYSCON_FROCTRL_TRIM_MASK)
#define SYSCON_FROCTRL_SEL_MASK                  (0x4000U)
#define SYSCON_FROCTRL_SEL_SHIFT                 (14U)
#define SYSCON_FROCTRL_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_SEL_SHIFT)) & SYSCON_FROCTRL_SEL_MASK)
#define SYSCON_FROCTRL_FREQTRIM_MASK             (0xFF0000U)
#define SYSCON_FROCTRL_FREQTRIM_SHIFT            (16U)
#define SYSCON_FROCTRL_FREQTRIM(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_FREQTRIM_SHIFT)) & SYSCON_FROCTRL_FREQTRIM_MASK)
#define SYSCON_FROCTRL_USBCLKADJ_MASK            (0x1000000U)
#define SYSCON_FROCTRL_USBCLKADJ_SHIFT           (24U)
#define SYSCON_FROCTRL_USBCLKADJ(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_USBCLKADJ_SHIFT)) & SYSCON_FROCTRL_USBCLKADJ_MASK)
#define SYSCON_FROCTRL_USBMODCHG_MASK            (0x2000000U)
#define SYSCON_FROCTRL_USBMODCHG_SHIFT           (25U)
#define SYSCON_FROCTRL_USBMODCHG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_USBMODCHG_SHIFT)) & SYSCON_FROCTRL_USBMODCHG_MASK)
#define SYSCON_FROCTRL_HSPDCLK_MASK              (0x40000000U)
#define SYSCON_FROCTRL_HSPDCLK_SHIFT             (30U)
#define SYSCON_FROCTRL_HSPDCLK(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_HSPDCLK_SHIFT)) & SYSCON_FROCTRL_HSPDCLK_MASK)
#define SYSCON_FROCTRL_WRTRIM_MASK               (0x80000000U)
#define SYSCON_FROCTRL_WRTRIM_SHIFT              (31U)
#define SYSCON_FROCTRL_WRTRIM(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_WRTRIM_SHIFT)) & SYSCON_FROCTRL_WRTRIM_MASK)

/*! @name SYSOSCCTRL - System oscillator control */
#define SYSCON_SYSOSCCTRL_BYPASS_MASK            (0x1U)
#define SYSCON_SYSOSCCTRL_BYPASS_SHIFT           (0U)
#define SYSCON_SYSOSCCTRL_BYPASS(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSOSCCTRL_BYPASS_SHIFT)) & SYSCON_SYSOSCCTRL_BYPASS_MASK)
#define SYSCON_SYSOSCCTRL_FREQRANGE_MASK         (0x2U)
#define SYSCON_SYSOSCCTRL_FREQRANGE_SHIFT        (1U)
#define SYSCON_SYSOSCCTRL_FREQRANGE(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSOSCCTRL_FREQRANGE_SHIFT)) & SYSCON_SYSOSCCTRL_FREQRANGE_MASK)

/*! @name WDTOSCCTRL - Watchdog oscillator control */
#define SYSCON_WDTOSCCTRL_DIVSEL_MASK            (0x1FU)
#define SYSCON_WDTOSCCTRL_DIVSEL_SHIFT           (0U)
#define SYSCON_WDTOSCCTRL_DIVSEL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_WDTOSCCTRL_DIVSEL_SHIFT)) & SYSCON_WDTOSCCTRL_DIVSEL_MASK)
#define SYSCON_WDTOSCCTRL_FREQSEL_MASK           (0x3E0U)
#define SYSCON_WDTOSCCTRL_FREQSEL_SHIFT          (5U)
#define SYSCON_WDTOSCCTRL_FREQSEL(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_WDTOSCCTRL_FREQSEL_SHIFT)) & SYSCON_WDTOSCCTRL_FREQSEL_MASK)

/*! @name RTCOSCCTRL - RTC oscillator 32 kHz output control */
#define SYSCON_RTCOSCCTRL_EN_MASK                (0x1U)
#define SYSCON_RTCOSCCTRL_EN_SHIFT               (0U)
#define SYSCON_RTCOSCCTRL_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_RTCOSCCTRL_EN_SHIFT)) & SYSCON_RTCOSCCTRL_EN_MASK)

/*! @name USBPLLCTRL - USB PLL control */
#define SYSCON_USBPLLCTRL_MSEL_MASK              (0xFFU)
#define SYSCON_USBPLLCTRL_MSEL_SHIFT             (0U)
#define SYSCON_USBPLLCTRL_MSEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_USBPLLCTRL_MSEL_SHIFT)) & SYSCON_USBPLLCTRL_MSEL_MASK)
#define SYSCON_USBPLLCTRL_PSEL_MASK              (0x300U)
#define SYSCON_USBPLLCTRL_PSEL_SHIFT             (8U)
#define SYSCON_USBPLLCTRL_PSEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_USBPLLCTRL_PSEL_SHIFT)) & SYSCON_USBPLLCTRL_PSEL_MASK)
#define SYSCON_USBPLLCTRL_NSEL_MASK              (0xC00U)
#define SYSCON_USBPLLCTRL_NSEL_SHIFT             (10U)
#define SYSCON_USBPLLCTRL_NSEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_USBPLLCTRL_NSEL_SHIFT)) & SYSCON_USBPLLCTRL_NSEL_MASK)
#define SYSCON_USBPLLCTRL_DIRECT_MASK            (0x1000U)
#define SYSCON_USBPLLCTRL_DIRECT_SHIFT           (12U)
#define SYSCON_USBPLLCTRL_DIRECT(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_USBPLLCTRL_DIRECT_SHIFT)) & SYSCON_USBPLLCTRL_DIRECT_MASK)
#define SYSCON_USBPLLCTRL_BYPASS_MASK            (0x2000U)
#define SYSCON_USBPLLCTRL_BYPASS_SHIFT           (13U)
#define SYSCON_USBPLLCTRL_BYPASS(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_USBPLLCTRL_BYPASS_SHIFT)) & SYSCON_USBPLLCTRL_BYPASS_MASK)
#define SYSCON_USBPLLCTRL_FBSEL_MASK             (0x4000U)
#define SYSCON_USBPLLCTRL_FBSEL_SHIFT            (14U)
#define SYSCON_USBPLLCTRL_FBSEL(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_USBPLLCTRL_FBSEL_SHIFT)) & SYSCON_USBPLLCTRL_FBSEL_MASK)

/*! @name USBPLLSTAT - USB PLL status */
#define SYSCON_USBPLLSTAT_LOCK_MASK              (0x1U)
#define SYSCON_USBPLLSTAT_LOCK_SHIFT             (0U)
#define SYSCON_USBPLLSTAT_LOCK(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_USBPLLSTAT_LOCK_SHIFT)) & SYSCON_USBPLLSTAT_LOCK_MASK)

/*! @name SYSPLLCTRL - System PLL control */
#define SYSCON_SYSPLLCTRL_SELR_MASK              (0xFU)
#define SYSCON_SYSPLLCTRL_SELR_SHIFT             (0U)
#define SYSCON_SYSPLLCTRL_SELR(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_SELR_SHIFT)) & SYSCON_SYSPLLCTRL_SELR_MASK)
#define SYSCON_SYSPLLCTRL_SELI_MASK              (0x3F0U)
#define SYSCON_SYSPLLCTRL_SELI_SHIFT             (4U)
#define SYSCON_SYSPLLCTRL_SELI(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_SELI_SHIFT)) & SYSCON_SYSPLLCTRL_SELI_MASK)
#define SYSCON_SYSPLLCTRL_SELP_MASK              (0x7C00U)
#define SYSCON_SYSPLLCTRL_SELP_SHIFT             (10U)
#define SYSCON_SYSPLLCTRL_SELP(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_SELP_SHIFT)) & SYSCON_SYSPLLCTRL_SELP_MASK)
#define SYSCON_SYSPLLCTRL_BYPASS_MASK            (0x8000U)
#define SYSCON_SYSPLLCTRL_BYPASS_SHIFT           (15U)
#define SYSCON_SYSPLLCTRL_BYPASS(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_BYPASS_SHIFT)) & SYSCON_SYSPLLCTRL_BYPASS_MASK)
#define SYSCON_SYSPLLCTRL_UPLIMOFF_MASK          (0x20000U)
#define SYSCON_SYSPLLCTRL_UPLIMOFF_SHIFT         (17U)
#define SYSCON_SYSPLLCTRL_UPLIMOFF(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_UPLIMOFF_SHIFT)) & SYSCON_SYSPLLCTRL_UPLIMOFF_MASK)
#define SYSCON_SYSPLLCTRL_DIRECTI_MASK           (0x80000U)
#define SYSCON_SYSPLLCTRL_DIRECTI_SHIFT          (19U)
#define SYSCON_SYSPLLCTRL_DIRECTI(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_DIRECTI_SHIFT)) & SYSCON_SYSPLLCTRL_DIRECTI_MASK)
#define SYSCON_SYSPLLCTRL_DIRECTO_MASK           (0x100000U)
#define SYSCON_SYSPLLCTRL_DIRECTO_SHIFT          (20U)
#define SYSCON_SYSPLLCTRL_DIRECTO(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_DIRECTO_SHIFT)) & SYSCON_SYSPLLCTRL_DIRECTO_MASK)

/*! @name SYSPLLSTAT - PLL status */
#define SYSCON_SYSPLLSTAT_LOCK_MASK              (0x1U)
#define SYSCON_SYSPLLSTAT_LOCK_SHIFT             (0U)
#define SYSCON_SYSPLLSTAT_LOCK(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLSTAT_LOCK_SHIFT)) & SYSCON_SYSPLLSTAT_LOCK_MASK)

/*! @name SYSPLLNDEC - PLL N divider */
#define SYSCON_SYSPLLNDEC_NDEC_MASK              (0x3FFU)
#define SYSCON_SYSPLLNDEC_NDEC_SHIFT             (0U)
#define SYSCON_SYSPLLNDEC_NDEC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLNDEC_NDEC_SHIFT)) & SYSCON_SYSPLLNDEC_NDEC_MASK)
#define SYSCON_SYSPLLNDEC_NREQ_MASK              (0x400U)
#define SYSCON_SYSPLLNDEC_NREQ_SHIFT             (10U)
#define SYSCON_SYSPLLNDEC_NREQ(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLNDEC_NREQ_SHIFT)) & SYSCON_SYSPLLNDEC_NREQ_MASK)

/*! @name SYSPLLPDEC - PLL P divider */
#define SYSCON_SYSPLLPDEC_PDEC_MASK              (0x7FU)
#define SYSCON_SYSPLLPDEC_PDEC_SHIFT             (0U)
#define SYSCON_SYSPLLPDEC_PDEC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLPDEC_PDEC_SHIFT)) & SYSCON_SYSPLLPDEC_PDEC_MASK)
#define SYSCON_SYSPLLPDEC_PREQ_MASK              (0x80U)
#define SYSCON_SYSPLLPDEC_PREQ_SHIFT             (7U)
#define SYSCON_SYSPLLPDEC_PREQ(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLPDEC_PREQ_SHIFT)) & SYSCON_SYSPLLPDEC_PREQ_MASK)

/*! @name SYSPLLMDEC - System PLL M divider */
#define SYSCON_SYSPLLMDEC_MDEC_MASK              (0x1FFFFU)
#define SYSCON_SYSPLLMDEC_MDEC_SHIFT             (0U)
#define SYSCON_SYSPLLMDEC_MDEC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLMDEC_MDEC_SHIFT)) & SYSCON_SYSPLLMDEC_MDEC_MASK)
#define SYSCON_SYSPLLMDEC_MREQ_MASK              (0x20000U)
#define SYSCON_SYSPLLMDEC_MREQ_SHIFT             (17U)
#define SYSCON_SYSPLLMDEC_MREQ(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLMDEC_MREQ_SHIFT)) & SYSCON_SYSPLLMDEC_MREQ_MASK)

/*! @name AUDPLLCTRL - Audio PLL control */
#define SYSCON_AUDPLLCTRL_SELR_MASK              (0xFU)
#define SYSCON_AUDPLLCTRL_SELR_SHIFT             (0U)
#define SYSCON_AUDPLLCTRL_SELR(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLCTRL_SELR_SHIFT)) & SYSCON_AUDPLLCTRL_SELR_MASK)
#define SYSCON_AUDPLLCTRL_SELI_MASK              (0x3F0U)
#define SYSCON_AUDPLLCTRL_SELI_SHIFT             (4U)
#define SYSCON_AUDPLLCTRL_SELI(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLCTRL_SELI_SHIFT)) & SYSCON_AUDPLLCTRL_SELI_MASK)
#define SYSCON_AUDPLLCTRL_SELP_MASK              (0x7C00U)
#define SYSCON_AUDPLLCTRL_SELP_SHIFT             (10U)
#define SYSCON_AUDPLLCTRL_SELP(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLCTRL_SELP_SHIFT)) & SYSCON_AUDPLLCTRL_SELP_MASK)
#define SYSCON_AUDPLLCTRL_BYPASS_MASK            (0x8000U)
#define SYSCON_AUDPLLCTRL_BYPASS_SHIFT           (15U)
#define SYSCON_AUDPLLCTRL_BYPASS(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLCTRL_BYPASS_SHIFT)) & SYSCON_AUDPLLCTRL_BYPASS_MASK)
#define SYSCON_AUDPLLCTRL_UPLIMOFF_MASK          (0x20000U)
#define SYSCON_AUDPLLCTRL_UPLIMOFF_SHIFT         (17U)
#define SYSCON_AUDPLLCTRL_UPLIMOFF(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLCTRL_UPLIMOFF_SHIFT)) & SYSCON_AUDPLLCTRL_UPLIMOFF_MASK)
#define SYSCON_AUDPLLCTRL_DIRECTI_MASK           (0x80000U)
#define SYSCON_AUDPLLCTRL_DIRECTI_SHIFT          (19U)
#define SYSCON_AUDPLLCTRL_DIRECTI(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLCTRL_DIRECTI_SHIFT)) & SYSCON_AUDPLLCTRL_DIRECTI_MASK)
#define SYSCON_AUDPLLCTRL_DIRECTO_MASK           (0x100000U)
#define SYSCON_AUDPLLCTRL_DIRECTO_SHIFT          (20U)
#define SYSCON_AUDPLLCTRL_DIRECTO(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLCTRL_DIRECTO_SHIFT)) & SYSCON_AUDPLLCTRL_DIRECTO_MASK)

/*! @name AUDPLLSTAT - Audio PLL status */
#define SYSCON_AUDPLLSTAT_LOCK_MASK              (0x1U)
#define SYSCON_AUDPLLSTAT_LOCK_SHIFT             (0U)
#define SYSCON_AUDPLLSTAT_LOCK(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLSTAT_LOCK_SHIFT)) & SYSCON_AUDPLLSTAT_LOCK_MASK)

/*! @name AUDPLLNDEC - Audio PLL N divider */
#define SYSCON_AUDPLLNDEC_NDEC_MASK              (0x3FFU)
#define SYSCON_AUDPLLNDEC_NDEC_SHIFT             (0U)
#define SYSCON_AUDPLLNDEC_NDEC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLNDEC_NDEC_SHIFT)) & SYSCON_AUDPLLNDEC_NDEC_MASK)
#define SYSCON_AUDPLLNDEC_NREQ_MASK              (0x400U)
#define SYSCON_AUDPLLNDEC_NREQ_SHIFT             (10U)
#define SYSCON_AUDPLLNDEC_NREQ(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLNDEC_NREQ_SHIFT)) & SYSCON_AUDPLLNDEC_NREQ_MASK)

/*! @name AUDPLLPDEC - Audio PLL P divider */
#define SYSCON_AUDPLLPDEC_PDEC_MASK              (0x7FU)
#define SYSCON_AUDPLLPDEC_PDEC_SHIFT             (0U)
#define SYSCON_AUDPLLPDEC_PDEC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLPDEC_PDEC_SHIFT)) & SYSCON_AUDPLLPDEC_PDEC_MASK)
#define SYSCON_AUDPLLPDEC_PREQ_MASK              (0x80U)
#define SYSCON_AUDPLLPDEC_PREQ_SHIFT             (7U)
#define SYSCON_AUDPLLPDEC_PREQ(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLPDEC_PREQ_SHIFT)) & SYSCON_AUDPLLPDEC_PREQ_MASK)

/*! @name AUDPLLMDEC - Audio PLL M divider */
#define SYSCON_AUDPLLMDEC_MDEC_MASK              (0x1FFFFU)
#define SYSCON_AUDPLLMDEC_MDEC_SHIFT             (0U)
#define SYSCON_AUDPLLMDEC_MDEC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLMDEC_MDEC_SHIFT)) & SYSCON_AUDPLLMDEC_MDEC_MASK)
#define SYSCON_AUDPLLMDEC_MREQ_MASK              (0x20000U)
#define SYSCON_AUDPLLMDEC_MREQ_SHIFT             (17U)
#define SYSCON_AUDPLLMDEC_MREQ(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLMDEC_MREQ_SHIFT)) & SYSCON_AUDPLLMDEC_MREQ_MASK)

/*! @name AUDPLLFRAC - Audio PLL fractional divider control */
#define SYSCON_AUDPLLFRAC_CTRL_MASK              (0x3FFFFFU)
#define SYSCON_AUDPLLFRAC_CTRL_SHIFT             (0U)
#define SYSCON_AUDPLLFRAC_CTRL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLFRAC_CTRL_SHIFT)) & SYSCON_AUDPLLFRAC_CTRL_MASK)
#define SYSCON_AUDPLLFRAC_REQ_MASK               (0x400000U)
#define SYSCON_AUDPLLFRAC_REQ_SHIFT              (22U)
#define SYSCON_AUDPLLFRAC_REQ(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLFRAC_REQ_SHIFT)) & SYSCON_AUDPLLFRAC_REQ_MASK)
#define SYSCON_AUDPLLFRAC_SEL_EXT_MASK           (0x800000U)
#define SYSCON_AUDPLLFRAC_SEL_EXT_SHIFT          (23U)
#define SYSCON_AUDPLLFRAC_SEL_EXT(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AUDPLLFRAC_SEL_EXT_SHIFT)) & SYSCON_AUDPLLFRAC_SEL_EXT_MASK)

/*! @name PDSLEEPCFG - Power configuration register 0 */
#define SYSCON_PDSLEEPCFG_PDEN_USB1_PHY_MASK     (0x1U)
#define SYSCON_PDSLEEPCFG_PDEN_USB1_PHY_SHIFT    (0U)
#define SYSCON_PDSLEEPCFG_PDEN_USB1_PHY(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_USB1_PHY_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_USB1_PHY_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_USB1_PLL_MASK     (0x2U)
#define SYSCON_PDSLEEPCFG_PDEN_USB1_PLL_SHIFT    (1U)
#define SYSCON_PDSLEEPCFG_PDEN_USB1_PLL(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_USB1_PLL_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_USB1_PLL_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_AUD_PLL_MASK      (0x4U)
#define SYSCON_PDSLEEPCFG_PDEN_AUD_PLL_SHIFT     (2U)
#define SYSCON_PDSLEEPCFG_PDEN_AUD_PLL(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_AUD_PLL_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_AUD_PLL_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_SYSOSC_MASK       (0x8U)
#define SYSCON_PDSLEEPCFG_PDEN_SYSOSC_SHIFT      (3U)
#define SYSCON_PDSLEEPCFG_PDEN_SYSOSC(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_SYSOSC_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_SYSOSC_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_FRO_MASK          (0x10U)
#define SYSCON_PDSLEEPCFG_PDEN_FRO_SHIFT         (4U)
#define SYSCON_PDSLEEPCFG_PDEN_FRO(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_FRO_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_FRO_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_EEPROM_MASK       (0x20U)
#define SYSCON_PDSLEEPCFG_PDEN_EEPROM_SHIFT      (5U)
#define SYSCON_PDSLEEPCFG_PDEN_EEPROM(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_EEPROM_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_EEPROM_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_TS_MASK           (0x40U)
#define SYSCON_PDSLEEPCFG_PDEN_TS_SHIFT          (6U)
#define SYSCON_PDSLEEPCFG_PDEN_TS(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_TS_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_TS_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_BOD_RST_MASK      (0x80U)
#define SYSCON_PDSLEEPCFG_PDEN_BOD_RST_SHIFT     (7U)
#define SYSCON_PDSLEEPCFG_PDEN_BOD_RST(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_BOD_RST_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_BOD_RST_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_RNG_MASK          (0x80U)
#define SYSCON_PDSLEEPCFG_PDEN_RNG_SHIFT         (7U)
#define SYSCON_PDSLEEPCFG_PDEN_RNG(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_RNG_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_RNG_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_BOD_INTR_MASK     (0x100U)
#define SYSCON_PDSLEEPCFG_PDEN_BOD_INTR_SHIFT    (8U)
#define SYSCON_PDSLEEPCFG_PDEN_BOD_INTR(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_BOD_INTR_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_BOD_INTR_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_VD2_ANA_MASK      (0x200U)
#define SYSCON_PDSLEEPCFG_PDEN_VD2_ANA_SHIFT     (9U)
#define SYSCON_PDSLEEPCFG_PDEN_VD2_ANA(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_VD2_ANA_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_VD2_ANA_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_ADC0_MASK         (0x400U)
#define SYSCON_PDSLEEPCFG_PDEN_ADC0_SHIFT        (10U)
#define SYSCON_PDSLEEPCFG_PDEN_ADC0(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_ADC0_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_ADC0_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_SRAMX_MASK        (0x2000U)
#define SYSCON_PDSLEEPCFG_PDEN_SRAMX_SHIFT       (13U)
#define SYSCON_PDSLEEPCFG_PDEN_SRAMX(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_SRAMX_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_SRAMX_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_SRAM0_MASK        (0x4000U)
#define SYSCON_PDSLEEPCFG_PDEN_SRAM0_SHIFT       (14U)
#define SYSCON_PDSLEEPCFG_PDEN_SRAM0(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_SRAM0_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_SRAM0_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_SRAM1_2_3_MASK    (0x8000U)
#define SYSCON_PDSLEEPCFG_PDEN_SRAM1_2_3_SHIFT   (15U)
#define SYSCON_PDSLEEPCFG_PDEN_SRAM1_2_3(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_SRAM1_2_3_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_SRAM1_2_3_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_USB_RAM_MASK      (0x10000U)
#define SYSCON_PDSLEEPCFG_PDEN_USB_RAM_SHIFT     (16U)
#define SYSCON_PDSLEEPCFG_PDEN_USB_RAM(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_USB_RAM_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_USB_RAM_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_ROM_MASK          (0x20000U)
#define SYSCON_PDSLEEPCFG_PDEN_ROM_SHIFT         (17U)
#define SYSCON_PDSLEEPCFG_PDEN_ROM(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_ROM_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_ROM_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_VDDA_MASK         (0x80000U)
#define SYSCON_PDSLEEPCFG_PDEN_VDDA_SHIFT        (19U)
#define SYSCON_PDSLEEPCFG_PDEN_VDDA(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_VDDA_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_VDDA_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_WDT_OSC_MASK      (0x100000U)
#define SYSCON_PDSLEEPCFG_PDEN_WDT_OSC_SHIFT     (20U)
#define SYSCON_PDSLEEPCFG_PDEN_WDT_OSC(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_WDT_OSC_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_WDT_OSC_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_USB0_PHY_MASK     (0x200000U)
#define SYSCON_PDSLEEPCFG_PDEN_USB0_PHY_SHIFT    (21U)
#define SYSCON_PDSLEEPCFG_PDEN_USB0_PHY(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_USB0_PHY_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_USB0_PHY_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_SYS_PLL_MASK      (0x400000U)
#define SYSCON_PDSLEEPCFG_PDEN_SYS_PLL_SHIFT     (22U)
#define SYSCON_PDSLEEPCFG_PDEN_SYS_PLL(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_SYS_PLL_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_SYS_PLL_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_VREFP_MASK        (0x800000U)
#define SYSCON_PDSLEEPCFG_PDEN_VREFP_SHIFT       (23U)
#define SYSCON_PDSLEEPCFG_PDEN_VREFP(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_VREFP_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_VREFP_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_VD3_MASK          (0x4000000U)
#define SYSCON_PDSLEEPCFG_PDEN_VD3_SHIFT         (26U)
#define SYSCON_PDSLEEPCFG_PDEN_VD3(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_VD3_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_VD3_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_VD4_MASK          (0x8000000U)
#define SYSCON_PDSLEEPCFG_PDEN_VD4_SHIFT         (27U)
#define SYSCON_PDSLEEPCFG_PDEN_VD4(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_VD4_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_VD4_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_VD5_MASK          (0x10000000U)
#define SYSCON_PDSLEEPCFG_PDEN_VD5_SHIFT         (28U)
#define SYSCON_PDSLEEPCFG_PDEN_VD5(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_VD5_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_VD5_MASK)
#define SYSCON_PDSLEEPCFG_PDEN_VD6_MASK          (0x20000000U)
#define SYSCON_PDSLEEPCFG_PDEN_VD6_SHIFT         (29U)
#define SYSCON_PDSLEEPCFG_PDEN_VD6(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PDEN_VD6_SHIFT)) & SYSCON_PDSLEEPCFG_PDEN_VD6_MASK)

/* The count of SYSCON_PDSLEEPCFG */
#define SYSCON_PDSLEEPCFG_COUNT                  (2U)

/*! @name PDRUNCFG - Power configuration register 0 */
#define SYSCON_PDRUNCFG_PDEN_USB1_PHY_MASK       (0x1U)
#define SYSCON_PDRUNCFG_PDEN_USB1_PHY_SHIFT      (0U)
#define SYSCON_PDRUNCFG_PDEN_USB1_PHY(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_USB1_PHY_SHIFT)) & SYSCON_PDRUNCFG_PDEN_USB1_PHY_MASK)
#define SYSCON_PDRUNCFG_PDEN_USB1_PLL_MASK       (0x2U)
#define SYSCON_PDRUNCFG_PDEN_USB1_PLL_SHIFT      (1U)
#define SYSCON_PDRUNCFG_PDEN_USB1_PLL(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_USB1_PLL_SHIFT)) & SYSCON_PDRUNCFG_PDEN_USB1_PLL_MASK)
#define SYSCON_PDRUNCFG_PDEN_AUD_PLL_MASK        (0x4U)
#define SYSCON_PDRUNCFG_PDEN_AUD_PLL_SHIFT       (2U)
#define SYSCON_PDRUNCFG_PDEN_AUD_PLL(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_AUD_PLL_SHIFT)) & SYSCON_PDRUNCFG_PDEN_AUD_PLL_MASK)
#define SYSCON_PDRUNCFG_PDEN_SYSOSC_MASK         (0x8U)
#define SYSCON_PDRUNCFG_PDEN_SYSOSC_SHIFT        (3U)
#define SYSCON_PDRUNCFG_PDEN_SYSOSC(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_SYSOSC_SHIFT)) & SYSCON_PDRUNCFG_PDEN_SYSOSC_MASK)
#define SYSCON_PDRUNCFG_PDEN_FRO_MASK            (0x10U)
#define SYSCON_PDRUNCFG_PDEN_FRO_SHIFT           (4U)
#define SYSCON_PDRUNCFG_PDEN_FRO(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_FRO_SHIFT)) & SYSCON_PDRUNCFG_PDEN_FRO_MASK)
#define SYSCON_PDRUNCFG_PDEN_EEPROM_MASK         (0x20U)
#define SYSCON_PDRUNCFG_PDEN_EEPROM_SHIFT        (5U)
#define SYSCON_PDRUNCFG_PDEN_EEPROM(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_EEPROM_SHIFT)) & SYSCON_PDRUNCFG_PDEN_EEPROM_MASK)
#define SYSCON_PDRUNCFG_PDEN_TS_MASK             (0x40U)
#define SYSCON_PDRUNCFG_PDEN_TS_SHIFT            (6U)
#define SYSCON_PDRUNCFG_PDEN_TS(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_TS_SHIFT)) & SYSCON_PDRUNCFG_PDEN_TS_MASK)
#define SYSCON_PDRUNCFG_PDEN_BOD_RST_MASK        (0x80U)
#define SYSCON_PDRUNCFG_PDEN_BOD_RST_SHIFT       (7U)
#define SYSCON_PDRUNCFG_PDEN_BOD_RST(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_BOD_RST_SHIFT)) & SYSCON_PDRUNCFG_PDEN_BOD_RST_MASK)
#define SYSCON_PDRUNCFG_PDEN_RNG_MASK            (0x80U)
#define SYSCON_PDRUNCFG_PDEN_RNG_SHIFT           (7U)
#define SYSCON_PDRUNCFG_PDEN_RNG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_RNG_SHIFT)) & SYSCON_PDRUNCFG_PDEN_RNG_MASK)
#define SYSCON_PDRUNCFG_PDEN_BOD_INTR_MASK       (0x100U)
#define SYSCON_PDRUNCFG_PDEN_BOD_INTR_SHIFT      (8U)
#define SYSCON_PDRUNCFG_PDEN_BOD_INTR(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_BOD_INTR_SHIFT)) & SYSCON_PDRUNCFG_PDEN_BOD_INTR_MASK)
#define SYSCON_PDRUNCFG_PDEN_VD2_ANA_MASK        (0x200U)
#define SYSCON_PDRUNCFG_PDEN_VD2_ANA_SHIFT       (9U)
#define SYSCON_PDRUNCFG_PDEN_VD2_ANA(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_VD2_ANA_SHIFT)) & SYSCON_PDRUNCFG_PDEN_VD2_ANA_MASK)
#define SYSCON_PDRUNCFG_PDEN_ADC0_MASK           (0x400U)
#define SYSCON_PDRUNCFG_PDEN_ADC0_SHIFT          (10U)
#define SYSCON_PDRUNCFG_PDEN_ADC0(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_ADC0_SHIFT)) & SYSCON_PDRUNCFG_PDEN_ADC0_MASK)
#define SYSCON_PDRUNCFG_PDEN_SRAMX_MASK          (0x2000U)
#define SYSCON_PDRUNCFG_PDEN_SRAMX_SHIFT         (13U)
#define SYSCON_PDRUNCFG_PDEN_SRAMX(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_SRAMX_SHIFT)) & SYSCON_PDRUNCFG_PDEN_SRAMX_MASK)
#define SYSCON_PDRUNCFG_PDEN_SRAM0_MASK          (0x4000U)
#define SYSCON_PDRUNCFG_PDEN_SRAM0_SHIFT         (14U)
#define SYSCON_PDRUNCFG_PDEN_SRAM0(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_SRAM0_SHIFT)) & SYSCON_PDRUNCFG_PDEN_SRAM0_MASK)
#define SYSCON_PDRUNCFG_PDEN_SRAM1_2_3_MASK      (0x8000U)
#define SYSCON_PDRUNCFG_PDEN_SRAM1_2_3_SHIFT     (15U)
#define SYSCON_PDRUNCFG_PDEN_SRAM1_2_3(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_SRAM1_2_3_SHIFT)) & SYSCON_PDRUNCFG_PDEN_SRAM1_2_3_MASK)
#define SYSCON_PDRUNCFG_PDEN_USB_RAM_MASK        (0x10000U)
#define SYSCON_PDRUNCFG_PDEN_USB_RAM_SHIFT       (16U)
#define SYSCON_PDRUNCFG_PDEN_USB_RAM(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_USB_RAM_SHIFT)) & SYSCON_PDRUNCFG_PDEN_USB_RAM_MASK)
#define SYSCON_PDRUNCFG_PDEN_ROM_MASK            (0x20000U)
#define SYSCON_PDRUNCFG_PDEN_ROM_SHIFT           (17U)
#define SYSCON_PDRUNCFG_PDEN_ROM(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_ROM_SHIFT)) & SYSCON_PDRUNCFG_PDEN_ROM_MASK)
#define SYSCON_PDRUNCFG_PDEN_VDDA_MASK           (0x80000U)
#define SYSCON_PDRUNCFG_PDEN_VDDA_SHIFT          (19U)
#define SYSCON_PDRUNCFG_PDEN_VDDA(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_VDDA_SHIFT)) & SYSCON_PDRUNCFG_PDEN_VDDA_MASK)
#define SYSCON_PDRUNCFG_PDEN_WDT_OSC_MASK        (0x100000U)
#define SYSCON_PDRUNCFG_PDEN_WDT_OSC_SHIFT       (20U)
#define SYSCON_PDRUNCFG_PDEN_WDT_OSC(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_WDT_OSC_SHIFT)) & SYSCON_PDRUNCFG_PDEN_WDT_OSC_MASK)
#define SYSCON_PDRUNCFG_PDEN_USB0_PHY_MASK       (0x200000U)
#define SYSCON_PDRUNCFG_PDEN_USB0_PHY_SHIFT      (21U)
#define SYSCON_PDRUNCFG_PDEN_USB0_PHY(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_USB0_PHY_SHIFT)) & SYSCON_PDRUNCFG_PDEN_USB0_PHY_MASK)
#define SYSCON_PDRUNCFG_PDEN_SYS_PLL_MASK        (0x400000U)
#define SYSCON_PDRUNCFG_PDEN_SYS_PLL_SHIFT       (22U)
#define SYSCON_PDRUNCFG_PDEN_SYS_PLL(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_SYS_PLL_SHIFT)) & SYSCON_PDRUNCFG_PDEN_SYS_PLL_MASK)
#define SYSCON_PDRUNCFG_PDEN_VREFP_MASK          (0x800000U)
#define SYSCON_PDRUNCFG_PDEN_VREFP_SHIFT         (23U)
#define SYSCON_PDRUNCFG_PDEN_VREFP(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_VREFP_SHIFT)) & SYSCON_PDRUNCFG_PDEN_VREFP_MASK)
#define SYSCON_PDRUNCFG_PDEN_VD3_MASK            (0x4000000U)
#define SYSCON_PDRUNCFG_PDEN_VD3_SHIFT           (26U)
#define SYSCON_PDRUNCFG_PDEN_VD3(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_VD3_SHIFT)) & SYSCON_PDRUNCFG_PDEN_VD3_MASK)
#define SYSCON_PDRUNCFG_PDEN_VD4_MASK            (0x8000000U)
#define SYSCON_PDRUNCFG_PDEN_VD4_SHIFT           (27U)
#define SYSCON_PDRUNCFG_PDEN_VD4(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_VD4_SHIFT)) & SYSCON_PDRUNCFG_PDEN_VD4_MASK)
#define SYSCON_PDRUNCFG_PDEN_VD5_MASK            (0x10000000U)
#define SYSCON_PDRUNCFG_PDEN_VD5_SHIFT           (28U)
#define SYSCON_PDRUNCFG_PDEN_VD5(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_VD5_SHIFT)) & SYSCON_PDRUNCFG_PDEN_VD5_MASK)
#define SYSCON_PDRUNCFG_PDEN_VD6_MASK            (0x20000000U)
#define SYSCON_PDRUNCFG_PDEN_VD6_SHIFT           (29U)
#define SYSCON_PDRUNCFG_PDEN_VD6(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_VD6_SHIFT)) & SYSCON_PDRUNCFG_PDEN_VD6_MASK)

/* The count of SYSCON_PDRUNCFG */
#define SYSCON_PDRUNCFG_COUNT                    (2U)

/*! @name PDRUNCFGSET - Set bits in PDRUNCFG0 */
#define SYSCON_PDRUNCFGSET_PDEN_USB1_PHY_MASK    (0x1U)
#define SYSCON_PDRUNCFGSET_PDEN_USB1_PHY_SHIFT   (0U)
#define SYSCON_PDRUNCFGSET_PDEN_USB1_PHY(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_USB1_PHY_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_USB1_PHY_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_USB1_PLL_MASK    (0x2U)
#define SYSCON_PDRUNCFGSET_PDEN_USB1_PLL_SHIFT   (1U)
#define SYSCON_PDRUNCFGSET_PDEN_USB1_PLL(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_USB1_PLL_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_USB1_PLL_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_AUD_PLL_MASK     (0x4U)
#define SYSCON_PDRUNCFGSET_PDEN_AUD_PLL_SHIFT    (2U)
#define SYSCON_PDRUNCFGSET_PDEN_AUD_PLL(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_AUD_PLL_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_AUD_PLL_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_SYSOSC_MASK      (0x8U)
#define SYSCON_PDRUNCFGSET_PDEN_SYSOSC_SHIFT     (3U)
#define SYSCON_PDRUNCFGSET_PDEN_SYSOSC(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_SYSOSC_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_SYSOSC_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_FRO_MASK         (0x10U)
#define SYSCON_PDRUNCFGSET_PDEN_FRO_SHIFT        (4U)
#define SYSCON_PDRUNCFGSET_PDEN_FRO(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_FRO_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_FRO_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_EEPROM_MASK      (0x20U)
#define SYSCON_PDRUNCFGSET_PDEN_EEPROM_SHIFT     (5U)
#define SYSCON_PDRUNCFGSET_PDEN_EEPROM(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_EEPROM_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_EEPROM_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_TS_MASK          (0x40U)
#define SYSCON_PDRUNCFGSET_PDEN_TS_SHIFT         (6U)
#define SYSCON_PDRUNCFGSET_PDEN_TS(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_TS_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_TS_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_BOD_RST_MASK     (0x80U)
#define SYSCON_PDRUNCFGSET_PDEN_BOD_RST_SHIFT    (7U)
#define SYSCON_PDRUNCFGSET_PDEN_BOD_RST(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_BOD_RST_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_BOD_RST_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_RNG_MASK         (0x80U)
#define SYSCON_PDRUNCFGSET_PDEN_RNG_SHIFT        (7U)
#define SYSCON_PDRUNCFGSET_PDEN_RNG(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_RNG_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_RNG_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_BOD_INTR_MASK    (0x100U)
#define SYSCON_PDRUNCFGSET_PDEN_BOD_INTR_SHIFT   (8U)
#define SYSCON_PDRUNCFGSET_PDEN_BOD_INTR(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_BOD_INTR_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_BOD_INTR_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_VD2_ANA_MASK     (0x200U)
#define SYSCON_PDRUNCFGSET_PDEN_VD2_ANA_SHIFT    (9U)
#define SYSCON_PDRUNCFGSET_PDEN_VD2_ANA(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_VD2_ANA_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_VD2_ANA_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_ADC0_MASK        (0x400U)
#define SYSCON_PDRUNCFGSET_PDEN_ADC0_SHIFT       (10U)
#define SYSCON_PDRUNCFGSET_PDEN_ADC0(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_ADC0_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_ADC0_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_SRAMX_MASK       (0x2000U)
#define SYSCON_PDRUNCFGSET_PDEN_SRAMX_SHIFT      (13U)
#define SYSCON_PDRUNCFGSET_PDEN_SRAMX(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_SRAMX_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_SRAMX_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_SRAM0_MASK       (0x4000U)
#define SYSCON_PDRUNCFGSET_PDEN_SRAM0_SHIFT      (14U)
#define SYSCON_PDRUNCFGSET_PDEN_SRAM0(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_SRAM0_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_SRAM0_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_SRAM1_2_3_MASK   (0x8000U)
#define SYSCON_PDRUNCFGSET_PDEN_SRAM1_2_3_SHIFT  (15U)
#define SYSCON_PDRUNCFGSET_PDEN_SRAM1_2_3(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_SRAM1_2_3_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_SRAM1_2_3_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_USB_RAM_MASK     (0x10000U)
#define SYSCON_PDRUNCFGSET_PDEN_USB_RAM_SHIFT    (16U)
#define SYSCON_PDRUNCFGSET_PDEN_USB_RAM(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_USB_RAM_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_USB_RAM_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_ROM_MASK         (0x20000U)
#define SYSCON_PDRUNCFGSET_PDEN_ROM_SHIFT        (17U)
#define SYSCON_PDRUNCFGSET_PDEN_ROM(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_ROM_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_ROM_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_VDDA_MASK        (0x80000U)
#define SYSCON_PDRUNCFGSET_PDEN_VDDA_SHIFT       (19U)
#define SYSCON_PDRUNCFGSET_PDEN_VDDA(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_VDDA_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_VDDA_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_WDT_OSC_MASK     (0x100000U)
#define SYSCON_PDRUNCFGSET_PDEN_WDT_OSC_SHIFT    (20U)
#define SYSCON_PDRUNCFGSET_PDEN_WDT_OSC(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_WDT_OSC_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_WDT_OSC_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_USB0_PHY_MASK    (0x200000U)
#define SYSCON_PDRUNCFGSET_PDEN_USB0_PHY_SHIFT   (21U)
#define SYSCON_PDRUNCFGSET_PDEN_USB0_PHY(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_USB0_PHY_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_USB0_PHY_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_SYS_PLL_MASK     (0x400000U)
#define SYSCON_PDRUNCFGSET_PDEN_SYS_PLL_SHIFT    (22U)
#define SYSCON_PDRUNCFGSET_PDEN_SYS_PLL(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_SYS_PLL_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_SYS_PLL_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_VREFP_MASK       (0x800000U)
#define SYSCON_PDRUNCFGSET_PDEN_VREFP_SHIFT      (23U)
#define SYSCON_PDRUNCFGSET_PDEN_VREFP(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_VREFP_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_VREFP_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_VD3_MASK         (0x4000000U)
#define SYSCON_PDRUNCFGSET_PDEN_VD3_SHIFT        (26U)
#define SYSCON_PDRUNCFGSET_PDEN_VD3(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_VD3_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_VD3_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_VD4_MASK         (0x8000000U)
#define SYSCON_PDRUNCFGSET_PDEN_VD4_SHIFT        (27U)
#define SYSCON_PDRUNCFGSET_PDEN_VD4(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_VD4_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_VD4_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_VD5_MASK         (0x10000000U)
#define SYSCON_PDRUNCFGSET_PDEN_VD5_SHIFT        (28U)
#define SYSCON_PDRUNCFGSET_PDEN_VD5(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_VD5_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_VD5_MASK)
#define SYSCON_PDRUNCFGSET_PDEN_VD6_MASK         (0x20000000U)
#define SYSCON_PDRUNCFGSET_PDEN_VD6_SHIFT        (29U)
#define SYSCON_PDRUNCFGSET_PDEN_VD6(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PDEN_VD6_SHIFT)) & SYSCON_PDRUNCFGSET_PDEN_VD6_MASK)

/* The count of SYSCON_PDRUNCFGSET */
#define SYSCON_PDRUNCFGSET_COUNT                 (2U)

/*! @name PDRUNCFGCLR - Clear bits in PDRUNCFG0 */
#define SYSCON_PDRUNCFGCLR_PDEN_USB1_PHY_MASK    (0x1U)
#define SYSCON_PDRUNCFGCLR_PDEN_USB1_PHY_SHIFT   (0U)
#define SYSCON_PDRUNCFGCLR_PDEN_USB1_PHY(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_USB1_PHY_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_USB1_PHY_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_USB1_PLL_MASK    (0x2U)
#define SYSCON_PDRUNCFGCLR_PDEN_USB1_PLL_SHIFT   (1U)
#define SYSCON_PDRUNCFGCLR_PDEN_USB1_PLL(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_USB1_PLL_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_USB1_PLL_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_AUD_PLL_MASK     (0x4U)
#define SYSCON_PDRUNCFGCLR_PDEN_AUD_PLL_SHIFT    (2U)
#define SYSCON_PDRUNCFGCLR_PDEN_AUD_PLL(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_AUD_PLL_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_AUD_PLL_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_SYSOSC_MASK      (0x8U)
#define SYSCON_PDRUNCFGCLR_PDEN_SYSOSC_SHIFT     (3U)
#define SYSCON_PDRUNCFGCLR_PDEN_SYSOSC(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_SYSOSC_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_SYSOSC_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_FRO_MASK         (0x10U)
#define SYSCON_PDRUNCFGCLR_PDEN_FRO_SHIFT        (4U)
#define SYSCON_PDRUNCFGCLR_PDEN_FRO(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_FRO_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_FRO_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_EEPROM_MASK      (0x20U)
#define SYSCON_PDRUNCFGCLR_PDEN_EEPROM_SHIFT     (5U)
#define SYSCON_PDRUNCFGCLR_PDEN_EEPROM(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_EEPROM_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_EEPROM_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_TS_MASK          (0x40U)
#define SYSCON_PDRUNCFGCLR_PDEN_TS_SHIFT         (6U)
#define SYSCON_PDRUNCFGCLR_PDEN_TS(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_TS_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_TS_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_BOD_RST_MASK     (0x80U)
#define SYSCON_PDRUNCFGCLR_PDEN_BOD_RST_SHIFT    (7U)
#define SYSCON_PDRUNCFGCLR_PDEN_BOD_RST(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_BOD_RST_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_BOD_RST_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_RNG_MASK         (0x80U)
#define SYSCON_PDRUNCFGCLR_PDEN_RNG_SHIFT        (7U)
#define SYSCON_PDRUNCFGCLR_PDEN_RNG(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_RNG_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_RNG_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_BOD_INTR_MASK    (0x100U)
#define SYSCON_PDRUNCFGCLR_PDEN_BOD_INTR_SHIFT   (8U)
#define SYSCON_PDRUNCFGCLR_PDEN_BOD_INTR(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_BOD_INTR_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_BOD_INTR_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_VD2_ANA_MASK     (0x200U)
#define SYSCON_PDRUNCFGCLR_PDEN_VD2_ANA_SHIFT    (9U)
#define SYSCON_PDRUNCFGCLR_PDEN_VD2_ANA(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_VD2_ANA_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_VD2_ANA_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_ADC0_MASK        (0x400U)
#define SYSCON_PDRUNCFGCLR_PDEN_ADC0_SHIFT       (10U)
#define SYSCON_PDRUNCFGCLR_PDEN_ADC0(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_ADC0_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_ADC0_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_SRAMX_MASK       (0x2000U)
#define SYSCON_PDRUNCFGCLR_PDEN_SRAMX_SHIFT      (13U)
#define SYSCON_PDRUNCFGCLR_PDEN_SRAMX(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_SRAMX_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_SRAMX_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_SRAM0_MASK       (0x4000U)
#define SYSCON_PDRUNCFGCLR_PDEN_SRAM0_SHIFT      (14U)
#define SYSCON_PDRUNCFGCLR_PDEN_SRAM0(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_SRAM0_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_SRAM0_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_SRAM1_2_3_MASK   (0x8000U)
#define SYSCON_PDRUNCFGCLR_PDEN_SRAM1_2_3_SHIFT  (15U)
#define SYSCON_PDRUNCFGCLR_PDEN_SRAM1_2_3(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_SRAM1_2_3_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_SRAM1_2_3_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_USB_RAM_MASK     (0x10000U)
#define SYSCON_PDRUNCFGCLR_PDEN_USB_RAM_SHIFT    (16U)
#define SYSCON_PDRUNCFGCLR_PDEN_USB_RAM(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_USB_RAM_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_USB_RAM_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_ROM_MASK         (0x20000U)
#define SYSCON_PDRUNCFGCLR_PDEN_ROM_SHIFT        (17U)
#define SYSCON_PDRUNCFGCLR_PDEN_ROM(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_ROM_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_ROM_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_VDDA_MASK        (0x80000U)
#define SYSCON_PDRUNCFGCLR_PDEN_VDDA_SHIFT       (19U)
#define SYSCON_PDRUNCFGCLR_PDEN_VDDA(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_VDDA_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_VDDA_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_WDT_OSC_MASK     (0x100000U)
#define SYSCON_PDRUNCFGCLR_PDEN_WDT_OSC_SHIFT    (20U)
#define SYSCON_PDRUNCFGCLR_PDEN_WDT_OSC(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_WDT_OSC_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_WDT_OSC_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_USB0_PHY_MASK    (0x200000U)
#define SYSCON_PDRUNCFGCLR_PDEN_USB0_PHY_SHIFT   (21U)
#define SYSCON_PDRUNCFGCLR_PDEN_USB0_PHY(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_USB0_PHY_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_USB0_PHY_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_SYS_PLL_MASK     (0x400000U)
#define SYSCON_PDRUNCFGCLR_PDEN_SYS_PLL_SHIFT    (22U)
#define SYSCON_PDRUNCFGCLR_PDEN_SYS_PLL(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_SYS_PLL_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_SYS_PLL_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_VREFP_MASK       (0x800000U)
#define SYSCON_PDRUNCFGCLR_PDEN_VREFP_SHIFT      (23U)
#define SYSCON_PDRUNCFGCLR_PDEN_VREFP(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_VREFP_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_VREFP_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_VD3_MASK         (0x4000000U)
#define SYSCON_PDRUNCFGCLR_PDEN_VD3_SHIFT        (26U)
#define SYSCON_PDRUNCFGCLR_PDEN_VD3(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_VD3_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_VD3_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_VD4_MASK         (0x8000000U)
#define SYSCON_PDRUNCFGCLR_PDEN_VD4_SHIFT        (27U)
#define SYSCON_PDRUNCFGCLR_PDEN_VD4(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_VD4_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_VD4_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_VD5_MASK         (0x10000000U)
#define SYSCON_PDRUNCFGCLR_PDEN_VD5_SHIFT        (28U)
#define SYSCON_PDRUNCFGCLR_PDEN_VD5(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_VD5_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_VD5_MASK)
#define SYSCON_PDRUNCFGCLR_PDEN_VD6_MASK         (0x20000000U)
#define SYSCON_PDRUNCFGCLR_PDEN_VD6_SHIFT        (29U)
#define SYSCON_PDRUNCFGCLR_PDEN_VD6(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PDEN_VD6_SHIFT)) & SYSCON_PDRUNCFGCLR_PDEN_VD6_MASK)

/* The count of SYSCON_PDRUNCFGCLR */
#define SYSCON_PDRUNCFGCLR_COUNT                 (2U)

/*! @name STARTER - Start logic 0 wake-up enable register */
#define SYSCON_STARTER_WDT_BOD_MASK              (0x1U)
#define SYSCON_STARTER_WDT_BOD_SHIFT             (0U)
#define SYSCON_STARTER_WDT_BOD(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_WDT_BOD_SHIFT)) & SYSCON_STARTER_WDT_BOD_MASK)
#define SYSCON_STARTER_PINT4_MASK                (0x1U)
#define SYSCON_STARTER_PINT4_SHIFT               (0U)
#define SYSCON_STARTER_PINT4(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_PINT4_SHIFT)) & SYSCON_STARTER_PINT4_MASK)
#define SYSCON_STARTER_PINT5_MASK                (0x2U)
#define SYSCON_STARTER_PINT5_SHIFT               (1U)
#define SYSCON_STARTER_PINT5(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_PINT5_SHIFT)) & SYSCON_STARTER_PINT5_MASK)
#define SYSCON_STARTER_DMA_MASK                  (0x2U)
#define SYSCON_STARTER_DMA_SHIFT                 (1U)
#define SYSCON_STARTER_DMA(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_DMA_SHIFT)) & SYSCON_STARTER_DMA_MASK)
#define SYSCON_STARTER_GINT0_MASK                (0x4U)
#define SYSCON_STARTER_GINT0_SHIFT               (2U)
#define SYSCON_STARTER_GINT0(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_GINT0_SHIFT)) & SYSCON_STARTER_GINT0_MASK)
#define SYSCON_STARTER_PINT6_MASK                (0x4U)
#define SYSCON_STARTER_PINT6_SHIFT               (2U)
#define SYSCON_STARTER_PINT6(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_PINT6_SHIFT)) & SYSCON_STARTER_PINT6_MASK)
#define SYSCON_STARTER_GINT1_MASK                (0x8U)
#define SYSCON_STARTER_GINT1_SHIFT               (3U)
#define SYSCON_STARTER_GINT1(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_GINT1_SHIFT)) & SYSCON_STARTER_GINT1_MASK)
#define SYSCON_STARTER_PINT7_MASK                (0x8U)
#define SYSCON_STARTER_PINT7_SHIFT               (3U)
#define SYSCON_STARTER_PINT7(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_PINT7_SHIFT)) & SYSCON_STARTER_PINT7_MASK)
#define SYSCON_STARTER_CTIMER2_MASK              (0x10U)
#define SYSCON_STARTER_CTIMER2_SHIFT             (4U)
#define SYSCON_STARTER_CTIMER2(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_CTIMER2_SHIFT)) & SYSCON_STARTER_CTIMER2_MASK)
#define SYSCON_STARTER_PIN_INT0_MASK             (0x10U)
#define SYSCON_STARTER_PIN_INT0_SHIFT            (4U)
#define SYSCON_STARTER_PIN_INT0(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_PIN_INT0_SHIFT)) & SYSCON_STARTER_PIN_INT0_MASK)
#define SYSCON_STARTER_CTIMER4_MASK              (0x20U)
#define SYSCON_STARTER_CTIMER4_SHIFT             (5U)
#define SYSCON_STARTER_CTIMER4(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_CTIMER4_SHIFT)) & SYSCON_STARTER_CTIMER4_MASK)
#define SYSCON_STARTER_PIN_INT1_MASK             (0x20U)
#define SYSCON_STARTER_PIN_INT1_SHIFT            (5U)
#define SYSCON_STARTER_PIN_INT1(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_PIN_INT1_SHIFT)) & SYSCON_STARTER_PIN_INT1_MASK)
#define SYSCON_STARTER_PIN_INT2_MASK             (0x40U)
#define SYSCON_STARTER_PIN_INT2_SHIFT            (6U)
#define SYSCON_STARTER_PIN_INT2(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_PIN_INT2_SHIFT)) & SYSCON_STARTER_PIN_INT2_MASK)
#define SYSCON_STARTER_PIN_INT3_MASK             (0x80U)
#define SYSCON_STARTER_PIN_INT3_SHIFT            (7U)
#define SYSCON_STARTER_PIN_INT3(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_PIN_INT3_SHIFT)) & SYSCON_STARTER_PIN_INT3_MASK)
#define SYSCON_STARTER_SPIFI_MASK                (0x80U)
#define SYSCON_STARTER_SPIFI_SHIFT               (7U)
#define SYSCON_STARTER_SPIFI(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_SPIFI_SHIFT)) & SYSCON_STARTER_SPIFI_MASK)
#define SYSCON_STARTER_FLEXCOMM8_MASK            (0x100U)
#define SYSCON_STARTER_FLEXCOMM8_SHIFT           (8U)
#define SYSCON_STARTER_FLEXCOMM8(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM8_SHIFT)) & SYSCON_STARTER_FLEXCOMM8_MASK)
#define SYSCON_STARTER_UTICK_MASK                (0x100U)
#define SYSCON_STARTER_UTICK_SHIFT               (8U)
#define SYSCON_STARTER_UTICK(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_UTICK_SHIFT)) & SYSCON_STARTER_UTICK_MASK)
#define SYSCON_STARTER_MRT_MASK                  (0x200U)
#define SYSCON_STARTER_MRT_SHIFT                 (9U)
#define SYSCON_STARTER_MRT(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_MRT_SHIFT)) & SYSCON_STARTER_MRT_MASK)
#define SYSCON_STARTER_FLEXCOMM9_MASK            (0x200U)
#define SYSCON_STARTER_FLEXCOMM9_SHIFT           (9U)
#define SYSCON_STARTER_FLEXCOMM9(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM9_SHIFT)) & SYSCON_STARTER_FLEXCOMM9_MASK)
#define SYSCON_STARTER_CTIMER0_MASK              (0x400U)
#define SYSCON_STARTER_CTIMER0_SHIFT             (10U)
#define SYSCON_STARTER_CTIMER0(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_CTIMER0_SHIFT)) & SYSCON_STARTER_CTIMER0_MASK)
#define SYSCON_STARTER_CTIMER1_MASK              (0x800U)
#define SYSCON_STARTER_CTIMER1_SHIFT             (11U)
#define SYSCON_STARTER_CTIMER1(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_CTIMER1_SHIFT)) & SYSCON_STARTER_CTIMER1_MASK)
#define SYSCON_STARTER_SCT0_MASK                 (0x1000U)
#define SYSCON_STARTER_SCT0_SHIFT                (12U)
#define SYSCON_STARTER_SCT0(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_SCT0_SHIFT)) & SYSCON_STARTER_SCT0_MASK)
#define SYSCON_STARTER_CTIMER3_MASK              (0x2000U)
#define SYSCON_STARTER_CTIMER3_SHIFT             (13U)
#define SYSCON_STARTER_CTIMER3(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_CTIMER3_SHIFT)) & SYSCON_STARTER_CTIMER3_MASK)
#define SYSCON_STARTER_FLEXCOMM0_MASK            (0x4000U)
#define SYSCON_STARTER_FLEXCOMM0_SHIFT           (14U)
#define SYSCON_STARTER_FLEXCOMM0(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM0_SHIFT)) & SYSCON_STARTER_FLEXCOMM0_MASK)
#define SYSCON_STARTER_FLEXCOMM1_MASK            (0x8000U)
#define SYSCON_STARTER_FLEXCOMM1_SHIFT           (15U)
#define SYSCON_STARTER_FLEXCOMM1(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM1_SHIFT)) & SYSCON_STARTER_FLEXCOMM1_MASK)
#define SYSCON_STARTER_USB1_MASK                 (0x8000U)
#define SYSCON_STARTER_USB1_SHIFT                (15U)
#define SYSCON_STARTER_USB1(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_USB1_SHIFT)) & SYSCON_STARTER_USB1_MASK)
#define SYSCON_STARTER_FLEXCOMM2_MASK            (0x10000U)
#define SYSCON_STARTER_FLEXCOMM2_SHIFT           (16U)
#define SYSCON_STARTER_FLEXCOMM2(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM2_SHIFT)) & SYSCON_STARTER_FLEXCOMM2_MASK)
#define SYSCON_STARTER_USB1_ACT_MASK             (0x10000U)
#define SYSCON_STARTER_USB1_ACT_SHIFT            (16U)
#define SYSCON_STARTER_USB1_ACT(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_USB1_ACT_SHIFT)) & SYSCON_STARTER_USB1_ACT_MASK)
#define SYSCON_STARTER_ENET_INT1_MASK            (0x20000U)
#define SYSCON_STARTER_ENET_INT1_SHIFT           (17U)
#define SYSCON_STARTER_ENET_INT1(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_ENET_INT1_SHIFT)) & SYSCON_STARTER_ENET_INT1_MASK)
#define SYSCON_STARTER_FLEXCOMM3_MASK            (0x20000U)
#define SYSCON_STARTER_FLEXCOMM3_SHIFT           (17U)
#define SYSCON_STARTER_FLEXCOMM3(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM3_SHIFT)) & SYSCON_STARTER_FLEXCOMM3_MASK)
#define SYSCON_STARTER_ENET_INT2_MASK            (0x40000U)
#define SYSCON_STARTER_ENET_INT2_SHIFT           (18U)
#define SYSCON_STARTER_ENET_INT2(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_ENET_INT2_SHIFT)) & SYSCON_STARTER_ENET_INT2_MASK)
#define SYSCON_STARTER_FLEXCOMM4_MASK            (0x40000U)
#define SYSCON_STARTER_FLEXCOMM4_SHIFT           (18U)
#define SYSCON_STARTER_FLEXCOMM4(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM4_SHIFT)) & SYSCON_STARTER_FLEXCOMM4_MASK)
#define SYSCON_STARTER_ENET_INT0_MASK            (0x80000U)
#define SYSCON_STARTER_ENET_INT0_SHIFT           (19U)
#define SYSCON_STARTER_ENET_INT0(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_ENET_INT0_SHIFT)) & SYSCON_STARTER_ENET_INT0_MASK)
#define SYSCON_STARTER_FLEXCOMM5_MASK            (0x80000U)
#define SYSCON_STARTER_FLEXCOMM5_SHIFT           (19U)
#define SYSCON_STARTER_FLEXCOMM5(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM5_SHIFT)) & SYSCON_STARTER_FLEXCOMM5_MASK)
#define SYSCON_STARTER_FLEXCOMM6_MASK            (0x100000U)
#define SYSCON_STARTER_FLEXCOMM6_SHIFT           (20U)
#define SYSCON_STARTER_FLEXCOMM6(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM6_SHIFT)) & SYSCON_STARTER_FLEXCOMM6_MASK)
#define SYSCON_STARTER_FLEXCOMM7_MASK            (0x200000U)
#define SYSCON_STARTER_FLEXCOMM7_SHIFT           (21U)
#define SYSCON_STARTER_FLEXCOMM7(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM7_SHIFT)) & SYSCON_STARTER_FLEXCOMM7_MASK)
#define SYSCON_STARTER_ADC0_SEQA_MASK            (0x400000U)
#define SYSCON_STARTER_ADC0_SEQA_SHIFT           (22U)
#define SYSCON_STARTER_ADC0_SEQA(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_ADC0_SEQA_SHIFT)) & SYSCON_STARTER_ADC0_SEQA_MASK)
#define SYSCON_STARTER_SMARTCARD0_MASK           (0x800000U)
#define SYSCON_STARTER_SMARTCARD0_SHIFT          (23U)
#define SYSCON_STARTER_SMARTCARD0(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_SMARTCARD0_SHIFT)) & SYSCON_STARTER_SMARTCARD0_MASK)
#define SYSCON_STARTER_ADC0_SEQB_MASK            (0x800000U)
#define SYSCON_STARTER_ADC0_SEQB_SHIFT           (23U)
#define SYSCON_STARTER_ADC0_SEQB(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_ADC0_SEQB_SHIFT)) & SYSCON_STARTER_ADC0_SEQB_MASK)
#define SYSCON_STARTER_ADC0_THCMP_MASK           (0x1000000U)
#define SYSCON_STARTER_ADC0_THCMP_SHIFT          (24U)
#define SYSCON_STARTER_ADC0_THCMP(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_ADC0_THCMP_SHIFT)) & SYSCON_STARTER_ADC0_THCMP_MASK)
#define SYSCON_STARTER_SMARTCARD1_MASK           (0x1000000U)
#define SYSCON_STARTER_SMARTCARD1_SHIFT          (24U)
#define SYSCON_STARTER_SMARTCARD1(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_SMARTCARD1_SHIFT)) & SYSCON_STARTER_SMARTCARD1_MASK)
#define SYSCON_STARTER_DMIC_MASK                 (0x2000000U)
#define SYSCON_STARTER_DMIC_SHIFT                (25U)
#define SYSCON_STARTER_DMIC(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_DMIC_SHIFT)) & SYSCON_STARTER_DMIC_MASK)
#define SYSCON_STARTER_HWVAD_MASK                (0x4000000U)
#define SYSCON_STARTER_HWVAD_SHIFT               (26U)
#define SYSCON_STARTER_HWVAD(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_HWVAD_SHIFT)) & SYSCON_STARTER_HWVAD_MASK)
#define SYSCON_STARTER_USB0_NEEDCLK_MASK         (0x8000000U)
#define SYSCON_STARTER_USB0_NEEDCLK_SHIFT        (27U)
#define SYSCON_STARTER_USB0_NEEDCLK(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_USB0_NEEDCLK_SHIFT)) & SYSCON_STARTER_USB0_NEEDCLK_MASK)
#define SYSCON_STARTER_USB0_MASK                 (0x10000000U)
#define SYSCON_STARTER_USB0_SHIFT                (28U)
#define SYSCON_STARTER_USB0(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_USB0_SHIFT)) & SYSCON_STARTER_USB0_MASK)
#define SYSCON_STARTER_RTC_MASK                  (0x20000000U)
#define SYSCON_STARTER_RTC_SHIFT                 (29U)
#define SYSCON_STARTER_RTC(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_RTC_SHIFT)) & SYSCON_STARTER_RTC_MASK)

/* The count of SYSCON_STARTER */
#define SYSCON_STARTER_COUNT                     (2U)

/*! @name STARTERSET - Set bits in STARTER */
#define SYSCON_STARTERSET_START_SET_MASK         (0xFFFFFFFFU)
#define SYSCON_STARTERSET_START_SET_SHIFT        (0U)
#define SYSCON_STARTERSET_START_SET(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERSET_START_SET_SHIFT)) & SYSCON_STARTERSET_START_SET_MASK)

/* The count of SYSCON_STARTERSET */
#define SYSCON_STARTERSET_COUNT                  (2U)

/*! @name STARTERCLR - Clear bits in STARTER0 */
#define SYSCON_STARTERCLR_START_CLR_MASK         (0xFFFFFFFFU)
#define SYSCON_STARTERCLR_START_CLR_SHIFT        (0U)
#define SYSCON_STARTERCLR_START_CLR(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERCLR_START_CLR_SHIFT)) & SYSCON_STARTERCLR_START_CLR_MASK)

/* The count of SYSCON_STARTERCLR */
#define SYSCON_STARTERCLR_COUNT                  (2U)

/*! @name HWWAKE - Configures special cases of hardware wake-up */
#define SYSCON_HWWAKE_FORCEWAKE_MASK             (0x1U)
#define SYSCON_HWWAKE_FORCEWAKE_SHIFT            (0U)
#define SYSCON_HWWAKE_FORCEWAKE(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_HWWAKE_FORCEWAKE_SHIFT)) & SYSCON_HWWAKE_FORCEWAKE_MASK)
#define SYSCON_HWWAKE_FCWAKE_MASK                (0x2U)
#define SYSCON_HWWAKE_FCWAKE_SHIFT               (1U)
#define SYSCON_HWWAKE_FCWAKE(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_HWWAKE_FCWAKE_SHIFT)) & SYSCON_HWWAKE_FCWAKE_MASK)
#define SYSCON_HWWAKE_WAKEDMIC_MASK              (0x4U)
#define SYSCON_HWWAKE_WAKEDMIC_SHIFT             (2U)
#define SYSCON_HWWAKE_WAKEDMIC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_HWWAKE_WAKEDMIC_SHIFT)) & SYSCON_HWWAKE_WAKEDMIC_MASK)
#define SYSCON_HWWAKE_WAKEDMA_MASK               (0x8U)
#define SYSCON_HWWAKE_WAKEDMA_SHIFT              (3U)
#define SYSCON_HWWAKE_WAKEDMA(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_HWWAKE_WAKEDMA_SHIFT)) & SYSCON_HWWAKE_WAKEDMA_MASK)

/*! @name AUTOCGOR - Auto Clock-Gate Override Register */
#define SYSCON_AUTOCGOR_RAM0X_MASK               (0x2U)
#define SYSCON_AUTOCGOR_RAM0X_SHIFT              (1U)
#define SYSCON_AUTOCGOR_RAM0X(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCGOR_RAM0X_SHIFT)) & SYSCON_AUTOCGOR_RAM0X_MASK)
#define SYSCON_AUTOCGOR_RAM1_MASK                (0x4U)
#define SYSCON_AUTOCGOR_RAM1_SHIFT               (2U)
#define SYSCON_AUTOCGOR_RAM1(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCGOR_RAM1_SHIFT)) & SYSCON_AUTOCGOR_RAM1_MASK)
#define SYSCON_AUTOCGOR_RAM2_MASK                (0x8U)
#define SYSCON_AUTOCGOR_RAM2_SHIFT               (3U)
#define SYSCON_AUTOCGOR_RAM2(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCGOR_RAM2_SHIFT)) & SYSCON_AUTOCGOR_RAM2_MASK)
#define SYSCON_AUTOCGOR_RAM3_MASK                (0x10U)
#define SYSCON_AUTOCGOR_RAM3_SHIFT               (4U)
#define SYSCON_AUTOCGOR_RAM3(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_AUTOCGOR_RAM3_SHIFT)) & SYSCON_AUTOCGOR_RAM3_MASK)

/*! @name JTAGIDCODE - JTAG ID code register */
#define SYSCON_JTAGIDCODE_JTAGID_MASK            (0xFFFFFFFFU)
#define SYSCON_JTAGIDCODE_JTAGID_SHIFT           (0U)
#define SYSCON_JTAGIDCODE_JTAGID(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_JTAGIDCODE_JTAGID_SHIFT)) & SYSCON_JTAGIDCODE_JTAGID_MASK)

/*! @name DEVICE_ID0 - Part ID register */
#define SYSCON_DEVICE_ID0_PARTID_MASK            (0xFFFFFFFFU)
#define SYSCON_DEVICE_ID0_PARTID_SHIFT           (0U)
#define SYSCON_DEVICE_ID0_PARTID(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_DEVICE_ID0_PARTID_SHIFT)) & SYSCON_DEVICE_ID0_PARTID_MASK)

/*! @name DEVICE_ID1 - Boot ROM and die revision register */
#define SYSCON_DEVICE_ID1_REVID_MASK             (0xFFFFFFFFU)
#define SYSCON_DEVICE_ID1_REVID_SHIFT            (0U)
#define SYSCON_DEVICE_ID1_REVID(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_DEVICE_ID1_REVID_SHIFT)) & SYSCON_DEVICE_ID1_REVID_MASK)

/*! @name BODCTRL - Brown-Out Detect control */
#define SYSCON_BODCTRL_BODRSTLEV_MASK            (0x3U)
#define SYSCON_BODCTRL_BODRSTLEV_SHIFT           (0U)
#define SYSCON_BODCTRL_BODRSTLEV(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODRSTLEV_SHIFT)) & SYSCON_BODCTRL_BODRSTLEV_MASK)
#define SYSCON_BODCTRL_BODRSTENA_MASK            (0x4U)
#define SYSCON_BODCTRL_BODRSTENA_SHIFT           (2U)
#define SYSCON_BODCTRL_BODRSTENA(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODRSTENA_SHIFT)) & SYSCON_BODCTRL_BODRSTENA_MASK)
#define SYSCON_BODCTRL_BODINTLEV_MASK            (0x18U)
#define SYSCON_BODCTRL_BODINTLEV_SHIFT           (3U)
#define SYSCON_BODCTRL_BODINTLEV(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODINTLEV_SHIFT)) & SYSCON_BODCTRL_BODINTLEV_MASK)
#define SYSCON_BODCTRL_BODINTENA_MASK            (0x20U)
#define SYSCON_BODCTRL_BODINTENA_SHIFT           (5U)
#define SYSCON_BODCTRL_BODINTENA(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODINTENA_SHIFT)) & SYSCON_BODCTRL_BODINTENA_MASK)
#define SYSCON_BODCTRL_BODRSTSTAT_MASK           (0x40U)
#define SYSCON_BODCTRL_BODRSTSTAT_SHIFT          (6U)
#define SYSCON_BODCTRL_BODRSTSTAT(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODRSTSTAT_SHIFT)) & SYSCON_BODCTRL_BODRSTSTAT_MASK)
#define SYSCON_BODCTRL_BODINTSTAT_MASK           (0x80U)
#define SYSCON_BODCTRL_BODINTSTAT_SHIFT          (7U)
#define SYSCON_BODCTRL_BODINTSTAT(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODINTSTAT_SHIFT)) & SYSCON_BODCTRL_BODINTSTAT_MASK)


/*!
 * @}
 */ /* end of group SYSCON_Register_Masks */


/* SYSCON - Peripheral instance base addresses */
/** Peripheral SYSCON base address */
#define SYSCON_BASE                              (0x40000000u)
/** Peripheral SYSCON base pointer */
#define SYSCON                                   ((SYSCON_Type *)SYSCON_BASE)
/** Array initializer of SYSCON peripheral base addresses */
#define SYSCON_BASE_ADDRS                        { SYSCON_BASE }
/** Array initializer of SYSCON peripheral base pointers */
#define SYSCON_BASE_PTRS                         { SYSCON }

/*!
 * @}
 */ /* end of group SYSCON_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- USART Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USART_Peripheral_Access_Layer USART Peripheral Access Layer
 * @{
 */

/** USART - Register Layout Typedef */
typedef struct {
  __IO uint32_t CFG;                               /**< USART Configuration register. Basic USART configuration settings that typically are not changed during operation., offset: 0x0 */
  __IO uint32_t CTL;                               /**< USART Control register. USART control settings that are more likely to change during operation., offset: 0x4 */
  __IO uint32_t STAT;                              /**< USART Status register. The complete status value can be read here. Writing ones clears some bits in the register. Some bits can be cleared by writing a 1 to them., offset: 0x8 */
  __IO uint32_t INTENSET;                          /**< Interrupt Enable read and Set register for USART (not FIFO) status. Contains individual interrupt enable bits for each potential USART interrupt. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set., offset: 0xC */
  __O  uint32_t INTENCLR;                          /**< Interrupt Enable Clear register. Allows clearing any combination of bits in the INTENSET register. Writing a 1 to any implemented bit position causes the corresponding bit to be cleared., offset: 0x10 */
       uint8_t RESERVED_0[12];
  __IO uint32_t BRG;                               /**< Baud Rate Generator register. 16-bit integer baud rate divisor value., offset: 0x20 */
  __I  uint32_t INTSTAT;                           /**< Interrupt status register. Reflects interrupts that are currently enabled., offset: 0x24 */
  __IO uint32_t OSR;                               /**< Oversample selection register for asynchronous communication., offset: 0x28 */
  __IO uint32_t ADDR;                              /**< Address register for automatic address matching., offset: 0x2C */
       uint8_t RESERVED_1[3536];
  __IO uint32_t FIFOCFG;                           /**< FIFO configuration and enable register., offset: 0xE00 */
  __IO uint32_t FIFOSTAT;                          /**< FIFO status register., offset: 0xE04 */
  __IO uint32_t FIFOTRIG;                          /**< FIFO trigger settings for interrupt and DMA request., offset: 0xE08 */
       uint8_t RESERVED_2[4];
  __IO uint32_t FIFOINTENSET;                      /**< FIFO interrupt enable set (enable) and read register., offset: 0xE10 */
  __IO uint32_t FIFOINTENCLR;                      /**< FIFO interrupt enable clear (disable) and read register., offset: 0xE14 */
  __I  uint32_t FIFOINTSTAT;                       /**< FIFO interrupt status register., offset: 0xE18 */
       uint8_t RESERVED_3[4];
  __IO uint32_t FIFOWR;                            /**< FIFO write data., offset: 0xE20 */
       uint8_t RESERVED_4[12];
  __I  uint32_t FIFORD;                            /**< FIFO read data., offset: 0xE30 */
       uint8_t RESERVED_5[12];
  __I  uint32_t FIFORDNOPOP;                       /**< FIFO data read with no FIFO pop., offset: 0xE40 */
       uint8_t RESERVED_6[440];
  __I  uint32_t ID;                                /**< Peripheral identification register., offset: 0xFFC */
} USART_Type;

/* ----------------------------------------------------------------------------
   -- USART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USART_Register_Masks USART Register Masks
 * @{
 */

/*! @name CFG - USART Configuration register. Basic USART configuration settings that typically are not changed during operation. */
#define USART_CFG_ENABLE_MASK                    (0x1U)
#define USART_CFG_ENABLE_SHIFT                   (0U)
#define USART_CFG_ENABLE(x)                      (((uint32_t)(((uint32_t)(x)) << USART_CFG_ENABLE_SHIFT)) & USART_CFG_ENABLE_MASK)
#define USART_CFG_DATALEN_MASK                   (0xCU)
#define USART_CFG_DATALEN_SHIFT                  (2U)
#define USART_CFG_DATALEN(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_DATALEN_SHIFT)) & USART_CFG_DATALEN_MASK)
#define USART_CFG_PARITYSEL_MASK                 (0x30U)
#define USART_CFG_PARITYSEL_SHIFT                (4U)
#define USART_CFG_PARITYSEL(x)                   (((uint32_t)(((uint32_t)(x)) << USART_CFG_PARITYSEL_SHIFT)) & USART_CFG_PARITYSEL_MASK)
#define USART_CFG_STOPLEN_MASK                   (0x40U)
#define USART_CFG_STOPLEN_SHIFT                  (6U)
#define USART_CFG_STOPLEN(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_STOPLEN_SHIFT)) & USART_CFG_STOPLEN_MASK)
#define USART_CFG_MODE32K_MASK                   (0x80U)
#define USART_CFG_MODE32K_SHIFT                  (7U)
#define USART_CFG_MODE32K(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_MODE32K_SHIFT)) & USART_CFG_MODE32K_MASK)
#define USART_CFG_LINMODE_MASK                   (0x100U)
#define USART_CFG_LINMODE_SHIFT                  (8U)
#define USART_CFG_LINMODE(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_LINMODE_SHIFT)) & USART_CFG_LINMODE_MASK)
#define USART_CFG_CTSEN_MASK                     (0x200U)
#define USART_CFG_CTSEN_SHIFT                    (9U)
#define USART_CFG_CTSEN(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_CTSEN_SHIFT)) & USART_CFG_CTSEN_MASK)
#define USART_CFG_SYNCEN_MASK                    (0x800U)
#define USART_CFG_SYNCEN_SHIFT                   (11U)
#define USART_CFG_SYNCEN(x)                      (((uint32_t)(((uint32_t)(x)) << USART_CFG_SYNCEN_SHIFT)) & USART_CFG_SYNCEN_MASK)
#define USART_CFG_CLKPOL_MASK                    (0x1000U)
#define USART_CFG_CLKPOL_SHIFT                   (12U)
#define USART_CFG_CLKPOL(x)                      (((uint32_t)(((uint32_t)(x)) << USART_CFG_CLKPOL_SHIFT)) & USART_CFG_CLKPOL_MASK)
#define USART_CFG_SYNCMST_MASK                   (0x4000U)
#define USART_CFG_SYNCMST_SHIFT                  (14U)
#define USART_CFG_SYNCMST(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_SYNCMST_SHIFT)) & USART_CFG_SYNCMST_MASK)
#define USART_CFG_LOOP_MASK                      (0x8000U)
#define USART_CFG_LOOP_SHIFT                     (15U)
#define USART_CFG_LOOP(x)                        (((uint32_t)(((uint32_t)(x)) << USART_CFG_LOOP_SHIFT)) & USART_CFG_LOOP_MASK)
#define USART_CFG_OETA_MASK                      (0x40000U)
#define USART_CFG_OETA_SHIFT                     (18U)
#define USART_CFG_OETA(x)                        (((uint32_t)(((uint32_t)(x)) << USART_CFG_OETA_SHIFT)) & USART_CFG_OETA_MASK)
#define USART_CFG_AUTOADDR_MASK                  (0x80000U)
#define USART_CFG_AUTOADDR_SHIFT                 (19U)
#define USART_CFG_AUTOADDR(x)                    (((uint32_t)(((uint32_t)(x)) << USART_CFG_AUTOADDR_SHIFT)) & USART_CFG_AUTOADDR_MASK)
#define USART_CFG_OESEL_MASK                     (0x100000U)
#define USART_CFG_OESEL_SHIFT                    (20U)
#define USART_CFG_OESEL(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_OESEL_SHIFT)) & USART_CFG_OESEL_MASK)
#define USART_CFG_OEPOL_MASK                     (0x200000U)
#define USART_CFG_OEPOL_SHIFT                    (21U)
#define USART_CFG_OEPOL(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_OEPOL_SHIFT)) & USART_CFG_OEPOL_MASK)
#define USART_CFG_RXPOL_MASK                     (0x400000U)
#define USART_CFG_RXPOL_SHIFT                    (22U)
#define USART_CFG_RXPOL(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_RXPOL_SHIFT)) & USART_CFG_RXPOL_MASK)
#define USART_CFG_TXPOL_MASK                     (0x800000U)
#define USART_CFG_TXPOL_SHIFT                    (23U)
#define USART_CFG_TXPOL(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_TXPOL_SHIFT)) & USART_CFG_TXPOL_MASK)

/*! @name CTL - USART Control register. USART control settings that are more likely to change during operation. */
#define USART_CTL_TXBRKEN_MASK                   (0x2U)
#define USART_CTL_TXBRKEN_SHIFT                  (1U)
#define USART_CTL_TXBRKEN(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CTL_TXBRKEN_SHIFT)) & USART_CTL_TXBRKEN_MASK)
#define USART_CTL_ADDRDET_MASK                   (0x4U)
#define USART_CTL_ADDRDET_SHIFT                  (2U)
#define USART_CTL_ADDRDET(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CTL_ADDRDET_SHIFT)) & USART_CTL_ADDRDET_MASK)
#define USART_CTL_TXDIS_MASK                     (0x40U)
#define USART_CTL_TXDIS_SHIFT                    (6U)
#define USART_CTL_TXDIS(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CTL_TXDIS_SHIFT)) & USART_CTL_TXDIS_MASK)
#define USART_CTL_CC_MASK                        (0x100U)
#define USART_CTL_CC_SHIFT                       (8U)
#define USART_CTL_CC(x)                          (((uint32_t)(((uint32_t)(x)) << USART_CTL_CC_SHIFT)) & USART_CTL_CC_MASK)
#define USART_CTL_CLRCCONRX_MASK                 (0x200U)
#define USART_CTL_CLRCCONRX_SHIFT                (9U)
#define USART_CTL_CLRCCONRX(x)                   (((uint32_t)(((uint32_t)(x)) << USART_CTL_CLRCCONRX_SHIFT)) & USART_CTL_CLRCCONRX_MASK)
#define USART_CTL_AUTOBAUD_MASK                  (0x10000U)
#define USART_CTL_AUTOBAUD_SHIFT                 (16U)
#define USART_CTL_AUTOBAUD(x)                    (((uint32_t)(((uint32_t)(x)) << USART_CTL_AUTOBAUD_SHIFT)) & USART_CTL_AUTOBAUD_MASK)

/*! @name STAT - USART Status register. The complete status value can be read here. Writing ones clears some bits in the register. Some bits can be cleared by writing a 1 to them. */
#define USART_STAT_RXIDLE_MASK                   (0x2U)
#define USART_STAT_RXIDLE_SHIFT                  (1U)
#define USART_STAT_RXIDLE(x)                     (((uint32_t)(((uint32_t)(x)) << USART_STAT_RXIDLE_SHIFT)) & USART_STAT_RXIDLE_MASK)
#define USART_STAT_TXIDLE_MASK                   (0x8U)
#define USART_STAT_TXIDLE_SHIFT                  (3U)
#define USART_STAT_TXIDLE(x)                     (((uint32_t)(((uint32_t)(x)) << USART_STAT_TXIDLE_SHIFT)) & USART_STAT_TXIDLE_MASK)
#define USART_STAT_CTS_MASK                      (0x10U)
#define USART_STAT_CTS_SHIFT                     (4U)
#define USART_STAT_CTS(x)                        (((uint32_t)(((uint32_t)(x)) << USART_STAT_CTS_SHIFT)) & USART_STAT_CTS_MASK)
#define USART_STAT_DELTACTS_MASK                 (0x20U)
#define USART_STAT_DELTACTS_SHIFT                (5U)
#define USART_STAT_DELTACTS(x)                   (((uint32_t)(((uint32_t)(x)) << USART_STAT_DELTACTS_SHIFT)) & USART_STAT_DELTACTS_MASK)
#define USART_STAT_TXDISSTAT_MASK                (0x40U)
#define USART_STAT_TXDISSTAT_SHIFT               (6U)
#define USART_STAT_TXDISSTAT(x)                  (((uint32_t)(((uint32_t)(x)) << USART_STAT_TXDISSTAT_SHIFT)) & USART_STAT_TXDISSTAT_MASK)
#define USART_STAT_RXBRK_MASK                    (0x400U)
#define USART_STAT_RXBRK_SHIFT                   (10U)
#define USART_STAT_RXBRK(x)                      (((uint32_t)(((uint32_t)(x)) << USART_STAT_RXBRK_SHIFT)) & USART_STAT_RXBRK_MASK)
#define USART_STAT_DELTARXBRK_MASK               (0x800U)
#define USART_STAT_DELTARXBRK_SHIFT              (11U)
#define USART_STAT_DELTARXBRK(x)                 (((uint32_t)(((uint32_t)(x)) << USART_STAT_DELTARXBRK_SHIFT)) & USART_STAT_DELTARXBRK_MASK)
#define USART_STAT_START_MASK                    (0x1000U)
#define USART_STAT_START_SHIFT                   (12U)
#define USART_STAT_START(x)                      (((uint32_t)(((uint32_t)(x)) << USART_STAT_START_SHIFT)) & USART_STAT_START_MASK)
#define USART_STAT_FRAMERRINT_MASK               (0x2000U)
#define USART_STAT_FRAMERRINT_SHIFT              (13U)
#define USART_STAT_FRAMERRINT(x)                 (((uint32_t)(((uint32_t)(x)) << USART_STAT_FRAMERRINT_SHIFT)) & USART_STAT_FRAMERRINT_MASK)
#define USART_STAT_PARITYERRINT_MASK             (0x4000U)
#define USART_STAT_PARITYERRINT_SHIFT            (14U)
#define USART_STAT_PARITYERRINT(x)               (((uint32_t)(((uint32_t)(x)) << USART_STAT_PARITYERRINT_SHIFT)) & USART_STAT_PARITYERRINT_MASK)
#define USART_STAT_RXNOISEINT_MASK               (0x8000U)
#define USART_STAT_RXNOISEINT_SHIFT              (15U)
#define USART_STAT_RXNOISEINT(x)                 (((uint32_t)(((uint32_t)(x)) << USART_STAT_RXNOISEINT_SHIFT)) & USART_STAT_RXNOISEINT_MASK)
#define USART_STAT_ABERR_MASK                    (0x10000U)
#define USART_STAT_ABERR_SHIFT                   (16U)
#define USART_STAT_ABERR(x)                      (((uint32_t)(((uint32_t)(x)) << USART_STAT_ABERR_SHIFT)) & USART_STAT_ABERR_MASK)

/*! @name INTENSET - Interrupt Enable read and Set register for USART (not FIFO) status. Contains individual interrupt enable bits for each potential USART interrupt. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set. */
#define USART_INTENSET_TXIDLEEN_MASK             (0x8U)
#define USART_INTENSET_TXIDLEEN_SHIFT            (3U)
#define USART_INTENSET_TXIDLEEN(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_TXIDLEEN_SHIFT)) & USART_INTENSET_TXIDLEEN_MASK)
#define USART_INTENSET_DELTACTSEN_MASK           (0x20U)
#define USART_INTENSET_DELTACTSEN_SHIFT          (5U)
#define USART_INTENSET_DELTACTSEN(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_DELTACTSEN_SHIFT)) & USART_INTENSET_DELTACTSEN_MASK)
#define USART_INTENSET_TXDISEN_MASK              (0x40U)
#define USART_INTENSET_TXDISEN_SHIFT             (6U)
#define USART_INTENSET_TXDISEN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_TXDISEN_SHIFT)) & USART_INTENSET_TXDISEN_MASK)
#define USART_INTENSET_DELTARXBRKEN_MASK         (0x800U)
#define USART_INTENSET_DELTARXBRKEN_SHIFT        (11U)
#define USART_INTENSET_DELTARXBRKEN(x)           (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_DELTARXBRKEN_SHIFT)) & USART_INTENSET_DELTARXBRKEN_MASK)
#define USART_INTENSET_STARTEN_MASK              (0x1000U)
#define USART_INTENSET_STARTEN_SHIFT             (12U)
#define USART_INTENSET_STARTEN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_STARTEN_SHIFT)) & USART_INTENSET_STARTEN_MASK)
#define USART_INTENSET_FRAMERREN_MASK            (0x2000U)
#define USART_INTENSET_FRAMERREN_SHIFT           (13U)
#define USART_INTENSET_FRAMERREN(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_FRAMERREN_SHIFT)) & USART_INTENSET_FRAMERREN_MASK)
#define USART_INTENSET_PARITYERREN_MASK          (0x4000U)
#define USART_INTENSET_PARITYERREN_SHIFT         (14U)
#define USART_INTENSET_PARITYERREN(x)            (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_PARITYERREN_SHIFT)) & USART_INTENSET_PARITYERREN_MASK)
#define USART_INTENSET_RXNOISEEN_MASK            (0x8000U)
#define USART_INTENSET_RXNOISEEN_SHIFT           (15U)
#define USART_INTENSET_RXNOISEEN(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_RXNOISEEN_SHIFT)) & USART_INTENSET_RXNOISEEN_MASK)
#define USART_INTENSET_ABERREN_MASK              (0x10000U)
#define USART_INTENSET_ABERREN_SHIFT             (16U)
#define USART_INTENSET_ABERREN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_ABERREN_SHIFT)) & USART_INTENSET_ABERREN_MASK)

/*! @name INTENCLR - Interrupt Enable Clear register. Allows clearing any combination of bits in the INTENSET register. Writing a 1 to any implemented bit position causes the corresponding bit to be cleared. */
#define USART_INTENCLR_TXIDLECLR_MASK            (0x8U)
#define USART_INTENCLR_TXIDLECLR_SHIFT           (3U)
#define USART_INTENCLR_TXIDLECLR(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_TXIDLECLR_SHIFT)) & USART_INTENCLR_TXIDLECLR_MASK)
#define USART_INTENCLR_DELTACTSCLR_MASK          (0x20U)
#define USART_INTENCLR_DELTACTSCLR_SHIFT         (5U)
#define USART_INTENCLR_DELTACTSCLR(x)            (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_DELTACTSCLR_SHIFT)) & USART_INTENCLR_DELTACTSCLR_MASK)
#define USART_INTENCLR_TXDISCLR_MASK             (0x40U)
#define USART_INTENCLR_TXDISCLR_SHIFT            (6U)
#define USART_INTENCLR_TXDISCLR(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_TXDISCLR_SHIFT)) & USART_INTENCLR_TXDISCLR_MASK)
#define USART_INTENCLR_DELTARXBRKCLR_MASK        (0x800U)
#define USART_INTENCLR_DELTARXBRKCLR_SHIFT       (11U)
#define USART_INTENCLR_DELTARXBRKCLR(x)          (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_DELTARXBRKCLR_SHIFT)) & USART_INTENCLR_DELTARXBRKCLR_MASK)
#define USART_INTENCLR_STARTCLR_MASK             (0x1000U)
#define USART_INTENCLR_STARTCLR_SHIFT            (12U)
#define USART_INTENCLR_STARTCLR(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_STARTCLR_SHIFT)) & USART_INTENCLR_STARTCLR_MASK)
#define USART_INTENCLR_FRAMERRCLR_MASK           (0x2000U)
#define USART_INTENCLR_FRAMERRCLR_SHIFT          (13U)
#define USART_INTENCLR_FRAMERRCLR(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_FRAMERRCLR_SHIFT)) & USART_INTENCLR_FRAMERRCLR_MASK)
#define USART_INTENCLR_PARITYERRCLR_MASK         (0x4000U)
#define USART_INTENCLR_PARITYERRCLR_SHIFT        (14U)
#define USART_INTENCLR_PARITYERRCLR(x)           (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_PARITYERRCLR_SHIFT)) & USART_INTENCLR_PARITYERRCLR_MASK)
#define USART_INTENCLR_RXNOISECLR_MASK           (0x8000U)
#define USART_INTENCLR_RXNOISECLR_SHIFT          (15U)
#define USART_INTENCLR_RXNOISECLR(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_RXNOISECLR_SHIFT)) & USART_INTENCLR_RXNOISECLR_MASK)
#define USART_INTENCLR_ABERRCLR_MASK             (0x10000U)
#define USART_INTENCLR_ABERRCLR_SHIFT            (16U)
#define USART_INTENCLR_ABERRCLR(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_ABERRCLR_SHIFT)) & USART_INTENCLR_ABERRCLR_MASK)

/*! @name BRG - Baud Rate Generator register. 16-bit integer baud rate divisor value. */
#define USART_BRG_BRGVAL_MASK                    (0xFFFFU)
#define USART_BRG_BRGVAL_SHIFT                   (0U)
#define USART_BRG_BRGVAL(x)                      (((uint32_t)(((uint32_t)(x)) << USART_BRG_BRGVAL_SHIFT)) & USART_BRG_BRGVAL_MASK)

/*! @name INTSTAT - Interrupt status register. Reflects interrupts that are currently enabled. */
#define USART_INTSTAT_TXIDLE_MASK                (0x8U)
#define USART_INTSTAT_TXIDLE_SHIFT               (3U)
#define USART_INTSTAT_TXIDLE(x)                  (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_TXIDLE_SHIFT)) & USART_INTSTAT_TXIDLE_MASK)
#define USART_INTSTAT_DELTACTS_MASK              (0x20U)
#define USART_INTSTAT_DELTACTS_SHIFT             (5U)
#define USART_INTSTAT_DELTACTS(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_DELTACTS_SHIFT)) & USART_INTSTAT_DELTACTS_MASK)
#define USART_INTSTAT_TXDISINT_MASK              (0x40U)
#define USART_INTSTAT_TXDISINT_SHIFT             (6U)
#define USART_INTSTAT_TXDISINT(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_TXDISINT_SHIFT)) & USART_INTSTAT_TXDISINT_MASK)
#define USART_INTSTAT_DELTARXBRK_MASK            (0x800U)
#define USART_INTSTAT_DELTARXBRK_SHIFT           (11U)
#define USART_INTSTAT_DELTARXBRK(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_DELTARXBRK_SHIFT)) & USART_INTSTAT_DELTARXBRK_MASK)
#define USART_INTSTAT_START_MASK                 (0x1000U)
#define USART_INTSTAT_START_SHIFT                (12U)
#define USART_INTSTAT_START(x)                   (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_START_SHIFT)) & USART_INTSTAT_START_MASK)
#define USART_INTSTAT_FRAMERRINT_MASK            (0x2000U)
#define USART_INTSTAT_FRAMERRINT_SHIFT           (13U)
#define USART_INTSTAT_FRAMERRINT(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_FRAMERRINT_SHIFT)) & USART_INTSTAT_FRAMERRINT_MASK)
#define USART_INTSTAT_PARITYERRINT_MASK          (0x4000U)
#define USART_INTSTAT_PARITYERRINT_SHIFT         (14U)
#define USART_INTSTAT_PARITYERRINT(x)            (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_PARITYERRINT_SHIFT)) & USART_INTSTAT_PARITYERRINT_MASK)
#define USART_INTSTAT_RXNOISEINT_MASK            (0x8000U)
#define USART_INTSTAT_RXNOISEINT_SHIFT           (15U)
#define USART_INTSTAT_RXNOISEINT(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_RXNOISEINT_SHIFT)) & USART_INTSTAT_RXNOISEINT_MASK)
#define USART_INTSTAT_ABERRINT_MASK              (0x10000U)
#define USART_INTSTAT_ABERRINT_SHIFT             (16U)
#define USART_INTSTAT_ABERRINT(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_ABERRINT_SHIFT)) & USART_INTSTAT_ABERRINT_MASK)

/*! @name OSR - Oversample selection register for asynchronous communication. */
#define USART_OSR_OSRVAL_MASK                    (0xFU)
#define USART_OSR_OSRVAL_SHIFT                   (0U)
#define USART_OSR_OSRVAL(x)                      (((uint32_t)(((uint32_t)(x)) << USART_OSR_OSRVAL_SHIFT)) & USART_OSR_OSRVAL_MASK)

/*! @name ADDR - Address register for automatic address matching. */
#define USART_ADDR_ADDRESS_MASK                  (0xFFU)
#define USART_ADDR_ADDRESS_SHIFT                 (0U)
#define USART_ADDR_ADDRESS(x)                    (((uint32_t)(((uint32_t)(x)) << USART_ADDR_ADDRESS_SHIFT)) & USART_ADDR_ADDRESS_MASK)

/*! @name FIFOCFG - FIFO configuration and enable register. */
#define USART_FIFOCFG_ENABLETX_MASK              (0x1U)
#define USART_FIFOCFG_ENABLETX_SHIFT             (0U)
#define USART_FIFOCFG_ENABLETX(x)                (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_ENABLETX_SHIFT)) & USART_FIFOCFG_ENABLETX_MASK)
#define USART_FIFOCFG_ENABLERX_MASK              (0x2U)
#define USART_FIFOCFG_ENABLERX_SHIFT             (1U)
#define USART_FIFOCFG_ENABLERX(x)                (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_ENABLERX_SHIFT)) & USART_FIFOCFG_ENABLERX_MASK)
#define USART_FIFOCFG_SIZE_MASK                  (0x30U)
#define USART_FIFOCFG_SIZE_SHIFT                 (4U)
#define USART_FIFOCFG_SIZE(x)                    (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_SIZE_SHIFT)) & USART_FIFOCFG_SIZE_MASK)
#define USART_FIFOCFG_DMATX_MASK                 (0x1000U)
#define USART_FIFOCFG_DMATX_SHIFT                (12U)
#define USART_FIFOCFG_DMATX(x)                   (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_DMATX_SHIFT)) & USART_FIFOCFG_DMATX_MASK)
#define USART_FIFOCFG_DMARX_MASK                 (0x2000U)
#define USART_FIFOCFG_DMARX_SHIFT                (13U)
#define USART_FIFOCFG_DMARX(x)                   (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_DMARX_SHIFT)) & USART_FIFOCFG_DMARX_MASK)
#define USART_FIFOCFG_WAKETX_MASK                (0x4000U)
#define USART_FIFOCFG_WAKETX_SHIFT               (14U)
#define USART_FIFOCFG_WAKETX(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_WAKETX_SHIFT)) & USART_FIFOCFG_WAKETX_MASK)
#define USART_FIFOCFG_WAKERX_MASK                (0x8000U)
#define USART_FIFOCFG_WAKERX_SHIFT               (15U)
#define USART_FIFOCFG_WAKERX(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_WAKERX_SHIFT)) & USART_FIFOCFG_WAKERX_MASK)
#define USART_FIFOCFG_EMPTYTX_MASK               (0x10000U)
#define USART_FIFOCFG_EMPTYTX_SHIFT              (16U)
#define USART_FIFOCFG_EMPTYTX(x)                 (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_EMPTYTX_SHIFT)) & USART_FIFOCFG_EMPTYTX_MASK)
#define USART_FIFOCFG_EMPTYRX_MASK               (0x20000U)
#define USART_FIFOCFG_EMPTYRX_SHIFT              (17U)
#define USART_FIFOCFG_EMPTYRX(x)                 (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_EMPTYRX_SHIFT)) & USART_FIFOCFG_EMPTYRX_MASK)
#define USART_FIFOCFG_POPDBG_MASK                (0x40000U)
#define USART_FIFOCFG_POPDBG_SHIFT               (18U)
#define USART_FIFOCFG_POPDBG(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_POPDBG_SHIFT)) & USART_FIFOCFG_POPDBG_MASK)

/*! @name FIFOSTAT - FIFO status register. */
#define USART_FIFOSTAT_TXERR_MASK                (0x1U)
#define USART_FIFOSTAT_TXERR_SHIFT               (0U)
#define USART_FIFOSTAT_TXERR(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_TXERR_SHIFT)) & USART_FIFOSTAT_TXERR_MASK)
#define USART_FIFOSTAT_RXERR_MASK                (0x2U)
#define USART_FIFOSTAT_RXERR_SHIFT               (1U)
#define USART_FIFOSTAT_RXERR(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_RXERR_SHIFT)) & USART_FIFOSTAT_RXERR_MASK)
#define USART_FIFOSTAT_PERINT_MASK               (0x8U)
#define USART_FIFOSTAT_PERINT_SHIFT              (3U)
#define USART_FIFOSTAT_PERINT(x)                 (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_PERINT_SHIFT)) & USART_FIFOSTAT_PERINT_MASK)
#define USART_FIFOSTAT_TXEMPTY_MASK              (0x10U)
#define USART_FIFOSTAT_TXEMPTY_SHIFT             (4U)
#define USART_FIFOSTAT_TXEMPTY(x)                (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_TXEMPTY_SHIFT)) & USART_FIFOSTAT_TXEMPTY_MASK)
#define USART_FIFOSTAT_TXNOTFULL_MASK            (0x20U)
#define USART_FIFOSTAT_TXNOTFULL_SHIFT           (5U)
#define USART_FIFOSTAT_TXNOTFULL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_TXNOTFULL_SHIFT)) & USART_FIFOSTAT_TXNOTFULL_MASK)
#define USART_FIFOSTAT_RXNOTEMPTY_MASK           (0x40U)
#define USART_FIFOSTAT_RXNOTEMPTY_SHIFT          (6U)
#define USART_FIFOSTAT_RXNOTEMPTY(x)             (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_RXNOTEMPTY_SHIFT)) & USART_FIFOSTAT_RXNOTEMPTY_MASK)
#define USART_FIFOSTAT_RXFULL_MASK               (0x80U)
#define USART_FIFOSTAT_RXFULL_SHIFT              (7U)
#define USART_FIFOSTAT_RXFULL(x)                 (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_RXFULL_SHIFT)) & USART_FIFOSTAT_RXFULL_MASK)
#define USART_FIFOSTAT_TXLVL_MASK                (0x1F00U)
#define USART_FIFOSTAT_TXLVL_SHIFT               (8U)
#define USART_FIFOSTAT_TXLVL(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_TXLVL_SHIFT)) & USART_FIFOSTAT_TXLVL_MASK)
#define USART_FIFOSTAT_RXLVL_MASK                (0x1F0000U)
#define USART_FIFOSTAT_RXLVL_SHIFT               (16U)
#define USART_FIFOSTAT_RXLVL(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_RXLVL_SHIFT)) & USART_FIFOSTAT_RXLVL_MASK)

/*! @name FIFOTRIG - FIFO trigger settings for interrupt and DMA request. */
#define USART_FIFOTRIG_TXLVLENA_MASK             (0x1U)
#define USART_FIFOTRIG_TXLVLENA_SHIFT            (0U)
#define USART_FIFOTRIG_TXLVLENA(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOTRIG_TXLVLENA_SHIFT)) & USART_FIFOTRIG_TXLVLENA_MASK)
#define USART_FIFOTRIG_RXLVLENA_MASK             (0x2U)
#define USART_FIFOTRIG_RXLVLENA_SHIFT            (1U)
#define USART_FIFOTRIG_RXLVLENA(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOTRIG_RXLVLENA_SHIFT)) & USART_FIFOTRIG_RXLVLENA_MASK)
#define USART_FIFOTRIG_TXLVL_MASK                (0xF00U)
#define USART_FIFOTRIG_TXLVL_SHIFT               (8U)
#define USART_FIFOTRIG_TXLVL(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOTRIG_TXLVL_SHIFT)) & USART_FIFOTRIG_TXLVL_MASK)
#define USART_FIFOTRIG_RXLVL_MASK                (0xF0000U)
#define USART_FIFOTRIG_RXLVL_SHIFT               (16U)
#define USART_FIFOTRIG_RXLVL(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOTRIG_RXLVL_SHIFT)) & USART_FIFOTRIG_RXLVL_MASK)

/*! @name FIFOINTENSET - FIFO interrupt enable set (enable) and read register. */
#define USART_FIFOINTENSET_TXERR_MASK            (0x1U)
#define USART_FIFOINTENSET_TXERR_SHIFT           (0U)
#define USART_FIFOINTENSET_TXERR(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENSET_TXERR_SHIFT)) & USART_FIFOINTENSET_TXERR_MASK)
#define USART_FIFOINTENSET_RXERR_MASK            (0x2U)
#define USART_FIFOINTENSET_RXERR_SHIFT           (1U)
#define USART_FIFOINTENSET_RXERR(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENSET_RXERR_SHIFT)) & USART_FIFOINTENSET_RXERR_MASK)
#define USART_FIFOINTENSET_TXLVL_MASK            (0x4U)
#define USART_FIFOINTENSET_TXLVL_SHIFT           (2U)
#define USART_FIFOINTENSET_TXLVL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENSET_TXLVL_SHIFT)) & USART_FIFOINTENSET_TXLVL_MASK)
#define USART_FIFOINTENSET_RXLVL_MASK            (0x8U)
#define USART_FIFOINTENSET_RXLVL_SHIFT           (3U)
#define USART_FIFOINTENSET_RXLVL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENSET_RXLVL_SHIFT)) & USART_FIFOINTENSET_RXLVL_MASK)

/*! @name FIFOINTENCLR - FIFO interrupt enable clear (disable) and read register. */
#define USART_FIFOINTENCLR_TXERR_MASK            (0x1U)
#define USART_FIFOINTENCLR_TXERR_SHIFT           (0U)
#define USART_FIFOINTENCLR_TXERR(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENCLR_TXERR_SHIFT)) & USART_FIFOINTENCLR_TXERR_MASK)
#define USART_FIFOINTENCLR_RXERR_MASK            (0x2U)
#define USART_FIFOINTENCLR_RXERR_SHIFT           (1U)
#define USART_FIFOINTENCLR_RXERR(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENCLR_RXERR_SHIFT)) & USART_FIFOINTENCLR_RXERR_MASK)
#define USART_FIFOINTENCLR_TXLVL_MASK            (0x4U)
#define USART_FIFOINTENCLR_TXLVL_SHIFT           (2U)
#define USART_FIFOINTENCLR_TXLVL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENCLR_TXLVL_SHIFT)) & USART_FIFOINTENCLR_TXLVL_MASK)
#define USART_FIFOINTENCLR_RXLVL_MASK            (0x8U)
#define USART_FIFOINTENCLR_RXLVL_SHIFT           (3U)
#define USART_FIFOINTENCLR_RXLVL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENCLR_RXLVL_SHIFT)) & USART_FIFOINTENCLR_RXLVL_MASK)

/*! @name FIFOINTSTAT - FIFO interrupt status register. */
#define USART_FIFOINTSTAT_TXERR_MASK             (0x1U)
#define USART_FIFOINTSTAT_TXERR_SHIFT            (0U)
#define USART_FIFOINTSTAT_TXERR(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_TXERR_SHIFT)) & USART_FIFOINTSTAT_TXERR_MASK)
#define USART_FIFOINTSTAT_RXERR_MASK             (0x2U)
#define USART_FIFOINTSTAT_RXERR_SHIFT            (1U)
#define USART_FIFOINTSTAT_RXERR(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_RXERR_SHIFT)) & USART_FIFOINTSTAT_RXERR_MASK)
#define USART_FIFOINTSTAT_TXLVL_MASK             (0x4U)
#define USART_FIFOINTSTAT_TXLVL_SHIFT            (2U)
#define USART_FIFOINTSTAT_TXLVL(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_TXLVL_SHIFT)) & USART_FIFOINTSTAT_TXLVL_MASK)
#define USART_FIFOINTSTAT_RXLVL_MASK             (0x8U)
#define USART_FIFOINTSTAT_RXLVL_SHIFT            (3U)
#define USART_FIFOINTSTAT_RXLVL(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_RXLVL_SHIFT)) & USART_FIFOINTSTAT_RXLVL_MASK)
#define USART_FIFOINTSTAT_PERINT_MASK            (0x10U)
#define USART_FIFOINTSTAT_PERINT_SHIFT           (4U)
#define USART_FIFOINTSTAT_PERINT(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_PERINT_SHIFT)) & USART_FIFOINTSTAT_PERINT_MASK)

/*! @name FIFOWR - FIFO write data. */
#define USART_FIFOWR_TXDATA_MASK                 (0x1FFU)
#define USART_FIFOWR_TXDATA_SHIFT                (0U)
#define USART_FIFOWR_TXDATA(x)                   (((uint32_t)(((uint32_t)(x)) << USART_FIFOWR_TXDATA_SHIFT)) & USART_FIFOWR_TXDATA_MASK)

/*! @name FIFORD - FIFO read data. */
#define USART_FIFORD_RXDATA_MASK                 (0x1FFU)
#define USART_FIFORD_RXDATA_SHIFT                (0U)
#define USART_FIFORD_RXDATA(x)                   (((uint32_t)(((uint32_t)(x)) << USART_FIFORD_RXDATA_SHIFT)) & USART_FIFORD_RXDATA_MASK)
#define USART_FIFORD_FRAMERR_MASK                (0x2000U)
#define USART_FIFORD_FRAMERR_SHIFT               (13U)
#define USART_FIFORD_FRAMERR(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFORD_FRAMERR_SHIFT)) & USART_FIFORD_FRAMERR_MASK)
#define USART_FIFORD_PARITYERR_MASK              (0x4000U)
#define USART_FIFORD_PARITYERR_SHIFT             (14U)
#define USART_FIFORD_PARITYERR(x)                (((uint32_t)(((uint32_t)(x)) << USART_FIFORD_PARITYERR_SHIFT)) & USART_FIFORD_PARITYERR_MASK)
#define USART_FIFORD_RXNOISE_MASK                (0x8000U)
#define USART_FIFORD_RXNOISE_SHIFT               (15U)
#define USART_FIFORD_RXNOISE(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFORD_RXNOISE_SHIFT)) & USART_FIFORD_RXNOISE_MASK)

/*! @name FIFORDNOPOP - FIFO data read with no FIFO pop. */
#define USART_FIFORDNOPOP_RXDATA_MASK            (0x1FFU)
#define USART_FIFORDNOPOP_RXDATA_SHIFT           (0U)
#define USART_FIFORDNOPOP_RXDATA(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFORDNOPOP_RXDATA_SHIFT)) & USART_FIFORDNOPOP_RXDATA_MASK)
#define USART_FIFORDNOPOP_FRAMERR_MASK           (0x2000U)
#define USART_FIFORDNOPOP_FRAMERR_SHIFT          (13U)
#define USART_FIFORDNOPOP_FRAMERR(x)             (((uint32_t)(((uint32_t)(x)) << USART_FIFORDNOPOP_FRAMERR_SHIFT)) & USART_FIFORDNOPOP_FRAMERR_MASK)
#define USART_FIFORDNOPOP_PARITYERR_MASK         (0x4000U)
#define USART_FIFORDNOPOP_PARITYERR_SHIFT        (14U)
#define USART_FIFORDNOPOP_PARITYERR(x)           (((uint32_t)(((uint32_t)(x)) << USART_FIFORDNOPOP_PARITYERR_SHIFT)) & USART_FIFORDNOPOP_PARITYERR_MASK)
#define USART_FIFORDNOPOP_RXNOISE_MASK           (0x8000U)
#define USART_FIFORDNOPOP_RXNOISE_SHIFT          (15U)
#define USART_FIFORDNOPOP_RXNOISE(x)             (((uint32_t)(((uint32_t)(x)) << USART_FIFORDNOPOP_RXNOISE_SHIFT)) & USART_FIFORDNOPOP_RXNOISE_MASK)

/*! @name ID - Peripheral identification register. */
#define USART_ID_APERTURE_MASK                   (0xFFU)
#define USART_ID_APERTURE_SHIFT                  (0U)
#define USART_ID_APERTURE(x)                     (((uint32_t)(((uint32_t)(x)) << USART_ID_APERTURE_SHIFT)) & USART_ID_APERTURE_MASK)
#define USART_ID_MINOR_REV_MASK                  (0xF00U)
#define USART_ID_MINOR_REV_SHIFT                 (8U)
#define USART_ID_MINOR_REV(x)                    (((uint32_t)(((uint32_t)(x)) << USART_ID_MINOR_REV_SHIFT)) & USART_ID_MINOR_REV_MASK)
#define USART_ID_MAJOR_REV_MASK                  (0xF000U)
#define USART_ID_MAJOR_REV_SHIFT                 (12U)
#define USART_ID_MAJOR_REV(x)                    (((uint32_t)(((uint32_t)(x)) << USART_ID_MAJOR_REV_SHIFT)) & USART_ID_MAJOR_REV_MASK)
#define USART_ID_ID_MASK                         (0xFFFF0000U)
#define USART_ID_ID_SHIFT                        (16U)
#define USART_ID_ID(x)                           (((uint32_t)(((uint32_t)(x)) << USART_ID_ID_SHIFT)) & USART_ID_ID_MASK)


/*!
 * @}
 */ /* end of group USART_Register_Masks */


/* USART - Peripheral instance base addresses */
/** Peripheral USART0 base address */
#define USART0_BASE                              (0x40086000u)
/** Peripheral USART0 base pointer */
#define USART0                                   ((USART_Type *)USART0_BASE)
/** Peripheral USART1 base address */
#define USART1_BASE                              (0x40087000u)
/** Peripheral USART1 base pointer */
#define USART1                                   ((USART_Type *)USART1_BASE)
/** Peripheral USART2 base address */
#define USART2_BASE                              (0x40088000u)
/** Peripheral USART2 base pointer */
#define USART2                                   ((USART_Type *)USART2_BASE)
/** Peripheral USART3 base address */
#define USART3_BASE                              (0x40089000u)
/** Peripheral USART3 base pointer */
#define USART3                                   ((USART_Type *)USART3_BASE)
/** Peripheral USART4 base address */
#define USART4_BASE                              (0x4008A000u)
/** Peripheral USART4 base pointer */
#define USART4                                   ((USART_Type *)USART4_BASE)
/** Peripheral USART5 base address */
#define USART5_BASE                              (0x40096000u)
/** Peripheral USART5 base pointer */
#define USART5                                   ((USART_Type *)USART5_BASE)
/** Peripheral USART6 base address */
#define USART6_BASE                              (0x40097000u)
/** Peripheral USART6 base pointer */
#define USART6                                   ((USART_Type *)USART6_BASE)
/** Peripheral USART7 base address */
#define USART7_BASE                              (0x40098000u)
/** Peripheral USART7 base pointer */
#define USART7                                   ((USART_Type *)USART7_BASE)
/** Peripheral USART8 base address */
#define USART8_BASE                              (0x40099000u)
/** Peripheral USART8 base pointer */
#define USART8                                   ((USART_Type *)USART8_BASE)
/** Peripheral USART9 base address */
#define USART9_BASE                              (0x4009A000u)
/** Peripheral USART9 base pointer */
#define USART9                                   ((USART_Type *)USART9_BASE)
/** Array initializer of USART peripheral base addresses */
#define USART_BASE_ADDRS                         { USART0_BASE, USART1_BASE, USART2_BASE, USART3_BASE, USART4_BASE, USART5_BASE, USART6_BASE, USART7_BASE, USART8_BASE, USART9_BASE }
/** Array initializer of USART peripheral base pointers */
#define USART_BASE_PTRS                          { USART0, USART1, USART2, USART3, USART4, USART5, USART6, USART7, USART8, USART9 }
/** Interrupt vectors for the USART peripheral type */
#define USART_IRQS                               { FLEXCOMM0_IRQn, FLEXCOMM1_IRQn, FLEXCOMM2_IRQn, FLEXCOMM3_IRQn, FLEXCOMM4_IRQn, FLEXCOMM5_IRQn, FLEXCOMM6_IRQn, FLEXCOMM7_IRQn, FLEXCOMM8_IRQn, FLEXCOMM9_IRQn }

/*!
 * @}
 */ /* end of group USART_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- USB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Peripheral_Access_Layer USB Peripheral Access Layer
 * @{
 */

/** USB - Register Layout Typedef */
typedef struct {
  __IO uint32_t DEVCMDSTAT;                        /**< USB Device Command/Status register, offset: 0x0 */
  __IO uint32_t INFO;                              /**< USB Info register, offset: 0x4 */
  __IO uint32_t EPLISTSTART;                       /**< USB EP Command/Status List start address, offset: 0x8 */
  __IO uint32_t DATABUFSTART;                      /**< USB Data buffer start address, offset: 0xC */
  __IO uint32_t LPM;                               /**< USB Link Power Management register, offset: 0x10 */
  __IO uint32_t EPSKIP;                            /**< USB Endpoint skip, offset: 0x14 */
  __IO uint32_t EPINUSE;                           /**< USB Endpoint Buffer in use, offset: 0x18 */
  __IO uint32_t EPBUFCFG;                          /**< USB Endpoint Buffer Configuration register, offset: 0x1C */
  __IO uint32_t INTSTAT;                           /**< USB interrupt status register, offset: 0x20 */
  __IO uint32_t INTEN;                             /**< USB interrupt enable register, offset: 0x24 */
  __IO uint32_t INTSETSTAT;                        /**< USB set interrupt status register, offset: 0x28 */
       uint8_t RESERVED_0[8];
  __IO uint32_t EPTOGGLE;                          /**< USB Endpoint toggle register, offset: 0x34 */
} USB_Type;

/* ----------------------------------------------------------------------------
   -- USB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Register_Masks USB Register Masks
 * @{
 */

/*! @name DEVCMDSTAT - USB Device Command/Status register */
#define USB_DEVCMDSTAT_DEV_ADDR_MASK             (0x7FU)
#define USB_DEVCMDSTAT_DEV_ADDR_SHIFT            (0U)
#define USB_DEVCMDSTAT_DEV_ADDR(x)               (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DEV_ADDR_SHIFT)) & USB_DEVCMDSTAT_DEV_ADDR_MASK)
#define USB_DEVCMDSTAT_DEV_EN_MASK               (0x80U)
#define USB_DEVCMDSTAT_DEV_EN_SHIFT              (7U)
#define USB_DEVCMDSTAT_DEV_EN(x)                 (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DEV_EN_SHIFT)) & USB_DEVCMDSTAT_DEV_EN_MASK)
#define USB_DEVCMDSTAT_SETUP_MASK                (0x100U)
#define USB_DEVCMDSTAT_SETUP_SHIFT               (8U)
#define USB_DEVCMDSTAT_SETUP(x)                  (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_SETUP_SHIFT)) & USB_DEVCMDSTAT_SETUP_MASK)
#define USB_DEVCMDSTAT_FORCE_NEEDCLK_MASK        (0x200U)
#define USB_DEVCMDSTAT_FORCE_NEEDCLK_SHIFT       (9U)
#define USB_DEVCMDSTAT_FORCE_NEEDCLK(x)          (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_FORCE_NEEDCLK_SHIFT)) & USB_DEVCMDSTAT_FORCE_NEEDCLK_MASK)
#define USB_DEVCMDSTAT_LPM_SUP_MASK              (0x800U)
#define USB_DEVCMDSTAT_LPM_SUP_SHIFT             (11U)
#define USB_DEVCMDSTAT_LPM_SUP(x)                (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_LPM_SUP_SHIFT)) & USB_DEVCMDSTAT_LPM_SUP_MASK)
#define USB_DEVCMDSTAT_INTONNAK_AO_MASK          (0x1000U)
#define USB_DEVCMDSTAT_INTONNAK_AO_SHIFT         (12U)
#define USB_DEVCMDSTAT_INTONNAK_AO(x)            (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_INTONNAK_AO_SHIFT)) & USB_DEVCMDSTAT_INTONNAK_AO_MASK)
#define USB_DEVCMDSTAT_INTONNAK_AI_MASK          (0x2000U)
#define USB_DEVCMDSTAT_INTONNAK_AI_SHIFT         (13U)
#define USB_DEVCMDSTAT_INTONNAK_AI(x)            (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_INTONNAK_AI_SHIFT)) & USB_DEVCMDSTAT_INTONNAK_AI_MASK)
#define USB_DEVCMDSTAT_INTONNAK_CO_MASK          (0x4000U)
#define USB_DEVCMDSTAT_INTONNAK_CO_SHIFT         (14U)
#define USB_DEVCMDSTAT_INTONNAK_CO(x)            (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_INTONNAK_CO_SHIFT)) & USB_DEVCMDSTAT_INTONNAK_CO_MASK)
#define USB_DEVCMDSTAT_INTONNAK_CI_MASK          (0x8000U)
#define USB_DEVCMDSTAT_INTONNAK_CI_SHIFT         (15U)
#define USB_DEVCMDSTAT_INTONNAK_CI(x)            (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_INTONNAK_CI_SHIFT)) & USB_DEVCMDSTAT_INTONNAK_CI_MASK)
#define USB_DEVCMDSTAT_DCON_MASK                 (0x10000U)
#define USB_DEVCMDSTAT_DCON_SHIFT                (16U)
#define USB_DEVCMDSTAT_DCON(x)                   (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DCON_SHIFT)) & USB_DEVCMDSTAT_DCON_MASK)
#define USB_DEVCMDSTAT_DSUS_MASK                 (0x20000U)
#define USB_DEVCMDSTAT_DSUS_SHIFT                (17U)
#define USB_DEVCMDSTAT_DSUS(x)                   (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DSUS_SHIFT)) & USB_DEVCMDSTAT_DSUS_MASK)
#define USB_DEVCMDSTAT_LPM_SUS_MASK              (0x80000U)
#define USB_DEVCMDSTAT_LPM_SUS_SHIFT             (19U)
#define USB_DEVCMDSTAT_LPM_SUS(x)                (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_LPM_SUS_SHIFT)) & USB_DEVCMDSTAT_LPM_SUS_MASK)
#define USB_DEVCMDSTAT_LPM_REWP_MASK             (0x100000U)
#define USB_DEVCMDSTAT_LPM_REWP_SHIFT            (20U)
#define USB_DEVCMDSTAT_LPM_REWP(x)               (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_LPM_REWP_SHIFT)) & USB_DEVCMDSTAT_LPM_REWP_MASK)
#define USB_DEVCMDSTAT_DCON_C_MASK               (0x1000000U)
#define USB_DEVCMDSTAT_DCON_C_SHIFT              (24U)
#define USB_DEVCMDSTAT_DCON_C(x)                 (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DCON_C_SHIFT)) & USB_DEVCMDSTAT_DCON_C_MASK)
#define USB_DEVCMDSTAT_DSUS_C_MASK               (0x2000000U)
#define USB_DEVCMDSTAT_DSUS_C_SHIFT              (25U)
#define USB_DEVCMDSTAT_DSUS_C(x)                 (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DSUS_C_SHIFT)) & USB_DEVCMDSTAT_DSUS_C_MASK)
#define USB_DEVCMDSTAT_DRES_C_MASK               (0x4000000U)
#define USB_DEVCMDSTAT_DRES_C_SHIFT              (26U)
#define USB_DEVCMDSTAT_DRES_C(x)                 (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DRES_C_SHIFT)) & USB_DEVCMDSTAT_DRES_C_MASK)
#define USB_DEVCMDSTAT_VBUSDEBOUNCED_MASK        (0x10000000U)
#define USB_DEVCMDSTAT_VBUSDEBOUNCED_SHIFT       (28U)
#define USB_DEVCMDSTAT_VBUSDEBOUNCED(x)          (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_VBUSDEBOUNCED_SHIFT)) & USB_DEVCMDSTAT_VBUSDEBOUNCED_MASK)

/*! @name INFO - USB Info register */
#define USB_INFO_FRAME_NR_MASK                   (0x7FFU)
#define USB_INFO_FRAME_NR_SHIFT                  (0U)
#define USB_INFO_FRAME_NR(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INFO_FRAME_NR_SHIFT)) & USB_INFO_FRAME_NR_MASK)
#define USB_INFO_ERR_CODE_MASK                   (0x7800U)
#define USB_INFO_ERR_CODE_SHIFT                  (11U)
#define USB_INFO_ERR_CODE(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INFO_ERR_CODE_SHIFT)) & USB_INFO_ERR_CODE_MASK)
#define USB_INFO_MINREV_MASK                     (0xFF0000U)
#define USB_INFO_MINREV_SHIFT                    (16U)
#define USB_INFO_MINREV(x)                       (((uint32_t)(((uint32_t)(x)) << USB_INFO_MINREV_SHIFT)) & USB_INFO_MINREV_MASK)
#define USB_INFO_MAJREV_MASK                     (0xFF000000U)
#define USB_INFO_MAJREV_SHIFT                    (24U)
#define USB_INFO_MAJREV(x)                       (((uint32_t)(((uint32_t)(x)) << USB_INFO_MAJREV_SHIFT)) & USB_INFO_MAJREV_MASK)

/*! @name EPLISTSTART - USB EP Command/Status List start address */
#define USB_EPLISTSTART_EP_LIST_MASK             (0xFFFFFF00U)
#define USB_EPLISTSTART_EP_LIST_SHIFT            (8U)
#define USB_EPLISTSTART_EP_LIST(x)               (((uint32_t)(((uint32_t)(x)) << USB_EPLISTSTART_EP_LIST_SHIFT)) & USB_EPLISTSTART_EP_LIST_MASK)

/*! @name DATABUFSTART - USB Data buffer start address */
#define USB_DATABUFSTART_DA_BUF_MASK             (0xFFC00000U)
#define USB_DATABUFSTART_DA_BUF_SHIFT            (22U)
#define USB_DATABUFSTART_DA_BUF(x)               (((uint32_t)(((uint32_t)(x)) << USB_DATABUFSTART_DA_BUF_SHIFT)) & USB_DATABUFSTART_DA_BUF_MASK)

/*! @name LPM - USB Link Power Management register */
#define USB_LPM_HIRD_HW_MASK                     (0xFU)
#define USB_LPM_HIRD_HW_SHIFT                    (0U)
#define USB_LPM_HIRD_HW(x)                       (((uint32_t)(((uint32_t)(x)) << USB_LPM_HIRD_HW_SHIFT)) & USB_LPM_HIRD_HW_MASK)
#define USB_LPM_HIRD_SW_MASK                     (0xF0U)
#define USB_LPM_HIRD_SW_SHIFT                    (4U)
#define USB_LPM_HIRD_SW(x)                       (((uint32_t)(((uint32_t)(x)) << USB_LPM_HIRD_SW_SHIFT)) & USB_LPM_HIRD_SW_MASK)
#define USB_LPM_DATA_PENDING_MASK                (0x100U)
#define USB_LPM_DATA_PENDING_SHIFT               (8U)
#define USB_LPM_DATA_PENDING(x)                  (((uint32_t)(((uint32_t)(x)) << USB_LPM_DATA_PENDING_SHIFT)) & USB_LPM_DATA_PENDING_MASK)

/*! @name EPSKIP - USB Endpoint skip */
#define USB_EPSKIP_SKIP_MASK                     (0x3FFU)
#define USB_EPSKIP_SKIP_SHIFT                    (0U)
#define USB_EPSKIP_SKIP(x)                       (((uint32_t)(((uint32_t)(x)) << USB_EPSKIP_SKIP_SHIFT)) & USB_EPSKIP_SKIP_MASK)

/*! @name EPINUSE - USB Endpoint Buffer in use */
#define USB_EPINUSE_BUF_MASK                     (0x3FCU)
#define USB_EPINUSE_BUF_SHIFT                    (2U)
#define USB_EPINUSE_BUF(x)                       (((uint32_t)(((uint32_t)(x)) << USB_EPINUSE_BUF_SHIFT)) & USB_EPINUSE_BUF_MASK)

/*! @name EPBUFCFG - USB Endpoint Buffer Configuration register */
#define USB_EPBUFCFG_BUF_SB_MASK                 (0x3FCU)
#define USB_EPBUFCFG_BUF_SB_SHIFT                (2U)
#define USB_EPBUFCFG_BUF_SB(x)                   (((uint32_t)(((uint32_t)(x)) << USB_EPBUFCFG_BUF_SB_SHIFT)) & USB_EPBUFCFG_BUF_SB_MASK)

/*! @name INTSTAT - USB interrupt status register */
#define USB_INTSTAT_EP0OUT_MASK                  (0x1U)
#define USB_INTSTAT_EP0OUT_SHIFT                 (0U)
#define USB_INTSTAT_EP0OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP0OUT_SHIFT)) & USB_INTSTAT_EP0OUT_MASK)
#define USB_INTSTAT_EP0IN_MASK                   (0x2U)
#define USB_INTSTAT_EP0IN_SHIFT                  (1U)
#define USB_INTSTAT_EP0IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP0IN_SHIFT)) & USB_INTSTAT_EP0IN_MASK)
#define USB_INTSTAT_EP1OUT_MASK                  (0x4U)
#define USB_INTSTAT_EP1OUT_SHIFT                 (2U)
#define USB_INTSTAT_EP1OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP1OUT_SHIFT)) & USB_INTSTAT_EP1OUT_MASK)
#define USB_INTSTAT_EP1IN_MASK                   (0x8U)
#define USB_INTSTAT_EP1IN_SHIFT                  (3U)
#define USB_INTSTAT_EP1IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP1IN_SHIFT)) & USB_INTSTAT_EP1IN_MASK)
#define USB_INTSTAT_EP2OUT_MASK                  (0x10U)
#define USB_INTSTAT_EP2OUT_SHIFT                 (4U)
#define USB_INTSTAT_EP2OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP2OUT_SHIFT)) & USB_INTSTAT_EP2OUT_MASK)
#define USB_INTSTAT_EP2IN_MASK                   (0x20U)
#define USB_INTSTAT_EP2IN_SHIFT                  (5U)
#define USB_INTSTAT_EP2IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP2IN_SHIFT)) & USB_INTSTAT_EP2IN_MASK)
#define USB_INTSTAT_EP3OUT_MASK                  (0x40U)
#define USB_INTSTAT_EP3OUT_SHIFT                 (6U)
#define USB_INTSTAT_EP3OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP3OUT_SHIFT)) & USB_INTSTAT_EP3OUT_MASK)
#define USB_INTSTAT_EP3IN_MASK                   (0x80U)
#define USB_INTSTAT_EP3IN_SHIFT                  (7U)
#define USB_INTSTAT_EP3IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP3IN_SHIFT)) & USB_INTSTAT_EP3IN_MASK)
#define USB_INTSTAT_EP4OUT_MASK                  (0x100U)
#define USB_INTSTAT_EP4OUT_SHIFT                 (8U)
#define USB_INTSTAT_EP4OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP4OUT_SHIFT)) & USB_INTSTAT_EP4OUT_MASK)
#define USB_INTSTAT_EP4IN_MASK                   (0x200U)
#define USB_INTSTAT_EP4IN_SHIFT                  (9U)
#define USB_INTSTAT_EP4IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP4IN_SHIFT)) & USB_INTSTAT_EP4IN_MASK)
#define USB_INTSTAT_FRAME_INT_MASK               (0x40000000U)
#define USB_INTSTAT_FRAME_INT_SHIFT              (30U)
#define USB_INTSTAT_FRAME_INT(x)                 (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_FRAME_INT_SHIFT)) & USB_INTSTAT_FRAME_INT_MASK)
#define USB_INTSTAT_DEV_INT_MASK                 (0x80000000U)
#define USB_INTSTAT_DEV_INT_SHIFT                (31U)
#define USB_INTSTAT_DEV_INT(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_DEV_INT_SHIFT)) & USB_INTSTAT_DEV_INT_MASK)

/*! @name INTEN - USB interrupt enable register */
#define USB_INTEN_EP_INT_EN_MASK                 (0x3FFU)
#define USB_INTEN_EP_INT_EN_SHIFT                (0U)
#define USB_INTEN_EP_INT_EN(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTEN_EP_INT_EN_SHIFT)) & USB_INTEN_EP_INT_EN_MASK)
#define USB_INTEN_FRAME_INT_EN_MASK              (0x40000000U)
#define USB_INTEN_FRAME_INT_EN_SHIFT             (30U)
#define USB_INTEN_FRAME_INT_EN(x)                (((uint32_t)(((uint32_t)(x)) << USB_INTEN_FRAME_INT_EN_SHIFT)) & USB_INTEN_FRAME_INT_EN_MASK)
#define USB_INTEN_DEV_INT_EN_MASK                (0x80000000U)
#define USB_INTEN_DEV_INT_EN_SHIFT               (31U)
#define USB_INTEN_DEV_INT_EN(x)                  (((uint32_t)(((uint32_t)(x)) << USB_INTEN_DEV_INT_EN_SHIFT)) & USB_INTEN_DEV_INT_EN_MASK)

/*! @name INTSETSTAT - USB set interrupt status register */
#define USB_INTSETSTAT_EP_SET_INT_MASK           (0x3FFU)
#define USB_INTSETSTAT_EP_SET_INT_SHIFT          (0U)
#define USB_INTSETSTAT_EP_SET_INT(x)             (((uint32_t)(((uint32_t)(x)) << USB_INTSETSTAT_EP_SET_INT_SHIFT)) & USB_INTSETSTAT_EP_SET_INT_MASK)
#define USB_INTSETSTAT_FRAME_SET_INT_MASK        (0x40000000U)
#define USB_INTSETSTAT_FRAME_SET_INT_SHIFT       (30U)
#define USB_INTSETSTAT_FRAME_SET_INT(x)          (((uint32_t)(((uint32_t)(x)) << USB_INTSETSTAT_FRAME_SET_INT_SHIFT)) & USB_INTSETSTAT_FRAME_SET_INT_MASK)
#define USB_INTSETSTAT_DEV_SET_INT_MASK          (0x80000000U)
#define USB_INTSETSTAT_DEV_SET_INT_SHIFT         (31U)
#define USB_INTSETSTAT_DEV_SET_INT(x)            (((uint32_t)(((uint32_t)(x)) << USB_INTSETSTAT_DEV_SET_INT_SHIFT)) & USB_INTSETSTAT_DEV_SET_INT_MASK)

/*! @name EPTOGGLE - USB Endpoint toggle register */
#define USB_EPTOGGLE_TOGGLE_MASK                 (0x3FFU)
#define USB_EPTOGGLE_TOGGLE_SHIFT                (0U)
#define USB_EPTOGGLE_TOGGLE(x)                   (((uint32_t)(((uint32_t)(x)) << USB_EPTOGGLE_TOGGLE_SHIFT)) & USB_EPTOGGLE_TOGGLE_MASK)


/*!
 * @}
 */ /* end of group USB_Register_Masks */


/* USB - Peripheral instance base addresses */
/** Peripheral USB0 base address */
#define USB0_BASE                                (0x40084000u)
/** Peripheral USB0 base pointer */
#define USB0                                     ((USB_Type *)USB0_BASE)
/** Array initializer of USB peripheral base addresses */
#define USB_BASE_ADDRS                           { USB0_BASE }
/** Array initializer of USB peripheral base pointers */
#define USB_BASE_PTRS                            { USB0 }
/** Interrupt vectors for the USB peripheral type */
#define USB_IRQS                                 { USB0_IRQn }
#define USB_NEEDCLK_IRQS                         { USB0_NEEDCLK_IRQn }

/*!
 * @}
 */ /* end of group USB_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- USBFSH Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBFSH_Peripheral_Access_Layer USBFSH Peripheral Access Layer
 * @{
 */

/** USBFSH - Register Layout Typedef */
typedef struct {
  __I  uint32_t HCREVISION;                        /**< BCD representation of the version of the HCI specification that is implemented by the Host Controller (HC), offset: 0x0 */
  __IO uint32_t HCCONTROL;                         /**< Defines the operating modes of the HC, offset: 0x4 */
  __IO uint32_t HCCOMMANDSTATUS;                   /**< This register is used to receive the commands from the Host Controller Driver (HCD), offset: 0x8 */
  __IO uint32_t HCINTERRUPTSTATUS;                 /**< Indicates the status on various events that cause hardware interrupts by setting the appropriate bits, offset: 0xC */
  __IO uint32_t HCINTERRUPTENABLE;                 /**< Controls the bits in the HcInterruptStatus register and indicates which events will generate a hardware interrupt, offset: 0x10 */
  __IO uint32_t HCINTERRUPTDISABLE;                /**< The bits in this register are used to disable corresponding bits in the HCInterruptStatus register and in turn disable that event leading to hardware interrupt, offset: 0x14 */
  __IO uint32_t HCHCCA;                            /**< Contains the physical address of the host controller communication area, offset: 0x18 */
  __IO uint32_t HCPERIODCURRENTED;                 /**< Contains the physical address of the current isochronous or interrupt endpoint descriptor, offset: 0x1C */
  __IO uint32_t HCCONTROLHEADED;                   /**< Contains the physical address of the first endpoint descriptor of the control list, offset: 0x20 */
  __IO uint32_t HCCONTROLCURRENTED;                /**< Contains the physical address of the current endpoint descriptor of the control list, offset: 0x24 */
  __IO uint32_t HCBULKHEADED;                      /**< Contains the physical address of the first endpoint descriptor of the bulk list, offset: 0x28 */
  __IO uint32_t HCBULKCURRENTED;                   /**< Contains the physical address of the current endpoint descriptor of the bulk list, offset: 0x2C */
  __IO uint32_t HCDONEHEAD;                        /**< Contains the physical address of the last transfer descriptor added to the 'Done' queue, offset: 0x30 */
  __IO uint32_t HCFMINTERVAL;                      /**< Defines the bit time interval in a frame and the full speed maximum packet size which would not cause an overrun, offset: 0x34 */
  __IO uint32_t HCFMREMAINING;                     /**< A 14-bit counter showing the bit time remaining in the current frame, offset: 0x38 */
  __IO uint32_t HCFMNUMBER;                        /**< Contains a 16-bit counter and provides the timing reference among events happening in the HC and the HCD, offset: 0x3C */
  __IO uint32_t HCPERIODICSTART;                   /**< Contains a programmable 14-bit value which determines the earliest time HC should start processing a periodic list, offset: 0x40 */
  __IO uint32_t HCLSTHRESHOLD;                     /**< Contains 11-bit value which is used by the HC to determine whether to commit to transfer a maximum of 8-byte LS packet before EOF, offset: 0x44 */
  __IO uint32_t HCRHDESCRIPTORA;                   /**< First of the two registers which describes the characteristics of the root hub, offset: 0x48 */
  __IO uint32_t HCRHDESCRIPTORB;                   /**< Second of the two registers which describes the characteristics of the Root Hub, offset: 0x4C */
  __IO uint32_t HCRHSTATUS;                        /**< This register is divided into two parts, offset: 0x50 */
  __IO uint32_t HCRHPORTSTATUS;                    /**< Controls and reports the port events on a per-port basis, offset: 0x54 */
       uint8_t RESERVED_0[4];
  __IO uint32_t PORTMODE;                          /**< Controls the port if it is attached to the host block or the device block, offset: 0x5C */
} USBFSH_Type;

/* ----------------------------------------------------------------------------
   -- USBFSH Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBFSH_Register_Masks USBFSH Register Masks
 * @{
 */

/*! @name HCREVISION - BCD representation of the version of the HCI specification that is implemented by the Host Controller (HC) */
#define USBFSH_HCREVISION_REV_MASK               (0xFFU)
#define USBFSH_HCREVISION_REV_SHIFT              (0U)
#define USBFSH_HCREVISION_REV(x)                 (((uint32_t)(((uint32_t)(x)) << USBFSH_HCREVISION_REV_SHIFT)) & USBFSH_HCREVISION_REV_MASK)

/*! @name HCCONTROL - Defines the operating modes of the HC */
#define USBFSH_HCCONTROL_CBSR_MASK               (0x3U)
#define USBFSH_HCCONTROL_CBSR_SHIFT              (0U)
#define USBFSH_HCCONTROL_CBSR(x)                 (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_CBSR_SHIFT)) & USBFSH_HCCONTROL_CBSR_MASK)
#define USBFSH_HCCONTROL_PLE_MASK                (0x4U)
#define USBFSH_HCCONTROL_PLE_SHIFT               (2U)
#define USBFSH_HCCONTROL_PLE(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_PLE_SHIFT)) & USBFSH_HCCONTROL_PLE_MASK)
#define USBFSH_HCCONTROL_IE_MASK                 (0x8U)
#define USBFSH_HCCONTROL_IE_SHIFT                (3U)
#define USBFSH_HCCONTROL_IE(x)                   (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_IE_SHIFT)) & USBFSH_HCCONTROL_IE_MASK)
#define USBFSH_HCCONTROL_CLE_MASK                (0x10U)
#define USBFSH_HCCONTROL_CLE_SHIFT               (4U)
#define USBFSH_HCCONTROL_CLE(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_CLE_SHIFT)) & USBFSH_HCCONTROL_CLE_MASK)
#define USBFSH_HCCONTROL_BLE_MASK                (0x20U)
#define USBFSH_HCCONTROL_BLE_SHIFT               (5U)
#define USBFSH_HCCONTROL_BLE(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_BLE_SHIFT)) & USBFSH_HCCONTROL_BLE_MASK)
#define USBFSH_HCCONTROL_HCFS_MASK               (0xC0U)
#define USBFSH_HCCONTROL_HCFS_SHIFT              (6U)
#define USBFSH_HCCONTROL_HCFS(x)                 (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_HCFS_SHIFT)) & USBFSH_HCCONTROL_HCFS_MASK)
#define USBFSH_HCCONTROL_IR_MASK                 (0x100U)
#define USBFSH_HCCONTROL_IR_SHIFT                (8U)
#define USBFSH_HCCONTROL_IR(x)                   (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_IR_SHIFT)) & USBFSH_HCCONTROL_IR_MASK)
#define USBFSH_HCCONTROL_RWC_MASK                (0x200U)
#define USBFSH_HCCONTROL_RWC_SHIFT               (9U)
#define USBFSH_HCCONTROL_RWC(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_RWC_SHIFT)) & USBFSH_HCCONTROL_RWC_MASK)
#define USBFSH_HCCONTROL_RWE_MASK                (0x400U)
#define USBFSH_HCCONTROL_RWE_SHIFT               (10U)
#define USBFSH_HCCONTROL_RWE(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROL_RWE_SHIFT)) & USBFSH_HCCONTROL_RWE_MASK)

/*! @name HCCOMMANDSTATUS - This register is used to receive the commands from the Host Controller Driver (HCD) */
#define USBFSH_HCCOMMANDSTATUS_HCR_MASK          (0x1U)
#define USBFSH_HCCOMMANDSTATUS_HCR_SHIFT         (0U)
#define USBFSH_HCCOMMANDSTATUS_HCR(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCOMMANDSTATUS_HCR_SHIFT)) & USBFSH_HCCOMMANDSTATUS_HCR_MASK)
#define USBFSH_HCCOMMANDSTATUS_CLF_MASK          (0x2U)
#define USBFSH_HCCOMMANDSTATUS_CLF_SHIFT         (1U)
#define USBFSH_HCCOMMANDSTATUS_CLF(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCOMMANDSTATUS_CLF_SHIFT)) & USBFSH_HCCOMMANDSTATUS_CLF_MASK)
#define USBFSH_HCCOMMANDSTATUS_BLF_MASK          (0x4U)
#define USBFSH_HCCOMMANDSTATUS_BLF_SHIFT         (2U)
#define USBFSH_HCCOMMANDSTATUS_BLF(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCOMMANDSTATUS_BLF_SHIFT)) & USBFSH_HCCOMMANDSTATUS_BLF_MASK)
#define USBFSH_HCCOMMANDSTATUS_OCR_MASK          (0x8U)
#define USBFSH_HCCOMMANDSTATUS_OCR_SHIFT         (3U)
#define USBFSH_HCCOMMANDSTATUS_OCR(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCOMMANDSTATUS_OCR_SHIFT)) & USBFSH_HCCOMMANDSTATUS_OCR_MASK)
#define USBFSH_HCCOMMANDSTATUS_SOC_MASK          (0xC0U)
#define USBFSH_HCCOMMANDSTATUS_SOC_SHIFT         (6U)
#define USBFSH_HCCOMMANDSTATUS_SOC(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCOMMANDSTATUS_SOC_SHIFT)) & USBFSH_HCCOMMANDSTATUS_SOC_MASK)

/*! @name HCINTERRUPTSTATUS - Indicates the status on various events that cause hardware interrupts by setting the appropriate bits */
#define USBFSH_HCINTERRUPTSTATUS_SO_MASK         (0x1U)
#define USBFSH_HCINTERRUPTSTATUS_SO_SHIFT        (0U)
#define USBFSH_HCINTERRUPTSTATUS_SO(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_SO_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_SO_MASK)
#define USBFSH_HCINTERRUPTSTATUS_WDH_MASK        (0x2U)
#define USBFSH_HCINTERRUPTSTATUS_WDH_SHIFT       (1U)
#define USBFSH_HCINTERRUPTSTATUS_WDH(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_WDH_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_WDH_MASK)
#define USBFSH_HCINTERRUPTSTATUS_SF_MASK         (0x4U)
#define USBFSH_HCINTERRUPTSTATUS_SF_SHIFT        (2U)
#define USBFSH_HCINTERRUPTSTATUS_SF(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_SF_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_SF_MASK)
#define USBFSH_HCINTERRUPTSTATUS_RD_MASK         (0x8U)
#define USBFSH_HCINTERRUPTSTATUS_RD_SHIFT        (3U)
#define USBFSH_HCINTERRUPTSTATUS_RD(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_RD_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_RD_MASK)
#define USBFSH_HCINTERRUPTSTATUS_UE_MASK         (0x10U)
#define USBFSH_HCINTERRUPTSTATUS_UE_SHIFT        (4U)
#define USBFSH_HCINTERRUPTSTATUS_UE(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_UE_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_UE_MASK)
#define USBFSH_HCINTERRUPTSTATUS_FNO_MASK        (0x20U)
#define USBFSH_HCINTERRUPTSTATUS_FNO_SHIFT       (5U)
#define USBFSH_HCINTERRUPTSTATUS_FNO(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_FNO_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_FNO_MASK)
#define USBFSH_HCINTERRUPTSTATUS_RHSC_MASK       (0x40U)
#define USBFSH_HCINTERRUPTSTATUS_RHSC_SHIFT      (6U)
#define USBFSH_HCINTERRUPTSTATUS_RHSC(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_RHSC_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_RHSC_MASK)
#define USBFSH_HCINTERRUPTSTATUS_OC_MASK         (0xFFFFFC00U)
#define USBFSH_HCINTERRUPTSTATUS_OC_SHIFT        (10U)
#define USBFSH_HCINTERRUPTSTATUS_OC(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTSTATUS_OC_SHIFT)) & USBFSH_HCINTERRUPTSTATUS_OC_MASK)

/*! @name HCINTERRUPTENABLE - Controls the bits in the HcInterruptStatus register and indicates which events will generate a hardware interrupt */
#define USBFSH_HCINTERRUPTENABLE_SO_MASK         (0x1U)
#define USBFSH_HCINTERRUPTENABLE_SO_SHIFT        (0U)
#define USBFSH_HCINTERRUPTENABLE_SO(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_SO_SHIFT)) & USBFSH_HCINTERRUPTENABLE_SO_MASK)
#define USBFSH_HCINTERRUPTENABLE_WDH_MASK        (0x2U)
#define USBFSH_HCINTERRUPTENABLE_WDH_SHIFT       (1U)
#define USBFSH_HCINTERRUPTENABLE_WDH(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_WDH_SHIFT)) & USBFSH_HCINTERRUPTENABLE_WDH_MASK)
#define USBFSH_HCINTERRUPTENABLE_SF_MASK         (0x4U)
#define USBFSH_HCINTERRUPTENABLE_SF_SHIFT        (2U)
#define USBFSH_HCINTERRUPTENABLE_SF(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_SF_SHIFT)) & USBFSH_HCINTERRUPTENABLE_SF_MASK)
#define USBFSH_HCINTERRUPTENABLE_RD_MASK         (0x8U)
#define USBFSH_HCINTERRUPTENABLE_RD_SHIFT        (3U)
#define USBFSH_HCINTERRUPTENABLE_RD(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_RD_SHIFT)) & USBFSH_HCINTERRUPTENABLE_RD_MASK)
#define USBFSH_HCINTERRUPTENABLE_UE_MASK         (0x10U)
#define USBFSH_HCINTERRUPTENABLE_UE_SHIFT        (4U)
#define USBFSH_HCINTERRUPTENABLE_UE(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_UE_SHIFT)) & USBFSH_HCINTERRUPTENABLE_UE_MASK)
#define USBFSH_HCINTERRUPTENABLE_FNO_MASK        (0x20U)
#define USBFSH_HCINTERRUPTENABLE_FNO_SHIFT       (5U)
#define USBFSH_HCINTERRUPTENABLE_FNO(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_FNO_SHIFT)) & USBFSH_HCINTERRUPTENABLE_FNO_MASK)
#define USBFSH_HCINTERRUPTENABLE_RHSC_MASK       (0x40U)
#define USBFSH_HCINTERRUPTENABLE_RHSC_SHIFT      (6U)
#define USBFSH_HCINTERRUPTENABLE_RHSC(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_RHSC_SHIFT)) & USBFSH_HCINTERRUPTENABLE_RHSC_MASK)
#define USBFSH_HCINTERRUPTENABLE_OC_MASK         (0x40000000U)
#define USBFSH_HCINTERRUPTENABLE_OC_SHIFT        (30U)
#define USBFSH_HCINTERRUPTENABLE_OC(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_OC_SHIFT)) & USBFSH_HCINTERRUPTENABLE_OC_MASK)
#define USBFSH_HCINTERRUPTENABLE_MIE_MASK        (0x80000000U)
#define USBFSH_HCINTERRUPTENABLE_MIE_SHIFT       (31U)
#define USBFSH_HCINTERRUPTENABLE_MIE(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTENABLE_MIE_SHIFT)) & USBFSH_HCINTERRUPTENABLE_MIE_MASK)

/*! @name HCINTERRUPTDISABLE - The bits in this register are used to disable corresponding bits in the HCInterruptStatus register and in turn disable that event leading to hardware interrupt */
#define USBFSH_HCINTERRUPTDISABLE_SO_MASK        (0x1U)
#define USBFSH_HCINTERRUPTDISABLE_SO_SHIFT       (0U)
#define USBFSH_HCINTERRUPTDISABLE_SO(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_SO_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_SO_MASK)
#define USBFSH_HCINTERRUPTDISABLE_WDH_MASK       (0x2U)
#define USBFSH_HCINTERRUPTDISABLE_WDH_SHIFT      (1U)
#define USBFSH_HCINTERRUPTDISABLE_WDH(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_WDH_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_WDH_MASK)
#define USBFSH_HCINTERRUPTDISABLE_SF_MASK        (0x4U)
#define USBFSH_HCINTERRUPTDISABLE_SF_SHIFT       (2U)
#define USBFSH_HCINTERRUPTDISABLE_SF(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_SF_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_SF_MASK)
#define USBFSH_HCINTERRUPTDISABLE_RD_MASK        (0x8U)
#define USBFSH_HCINTERRUPTDISABLE_RD_SHIFT       (3U)
#define USBFSH_HCINTERRUPTDISABLE_RD(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_RD_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_RD_MASK)
#define USBFSH_HCINTERRUPTDISABLE_UE_MASK        (0x10U)
#define USBFSH_HCINTERRUPTDISABLE_UE_SHIFT       (4U)
#define USBFSH_HCINTERRUPTDISABLE_UE(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_UE_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_UE_MASK)
#define USBFSH_HCINTERRUPTDISABLE_FNO_MASK       (0x20U)
#define USBFSH_HCINTERRUPTDISABLE_FNO_SHIFT      (5U)
#define USBFSH_HCINTERRUPTDISABLE_FNO(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_FNO_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_FNO_MASK)
#define USBFSH_HCINTERRUPTDISABLE_RHSC_MASK      (0x40U)
#define USBFSH_HCINTERRUPTDISABLE_RHSC_SHIFT     (6U)
#define USBFSH_HCINTERRUPTDISABLE_RHSC(x)        (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_RHSC_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_RHSC_MASK)
#define USBFSH_HCINTERRUPTDISABLE_OC_MASK        (0x40000000U)
#define USBFSH_HCINTERRUPTDISABLE_OC_SHIFT       (30U)
#define USBFSH_HCINTERRUPTDISABLE_OC(x)          (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_OC_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_OC_MASK)
#define USBFSH_HCINTERRUPTDISABLE_MIE_MASK       (0x80000000U)
#define USBFSH_HCINTERRUPTDISABLE_MIE_SHIFT      (31U)
#define USBFSH_HCINTERRUPTDISABLE_MIE(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCINTERRUPTDISABLE_MIE_SHIFT)) & USBFSH_HCINTERRUPTDISABLE_MIE_MASK)

/*! @name HCHCCA - Contains the physical address of the host controller communication area */
#define USBFSH_HCHCCA_HCCA_MASK                  (0xFFFFFF00U)
#define USBFSH_HCHCCA_HCCA_SHIFT                 (8U)
#define USBFSH_HCHCCA_HCCA(x)                    (((uint32_t)(((uint32_t)(x)) << USBFSH_HCHCCA_HCCA_SHIFT)) & USBFSH_HCHCCA_HCCA_MASK)

/*! @name HCPERIODCURRENTED - Contains the physical address of the current isochronous or interrupt endpoint descriptor */
#define USBFSH_HCPERIODCURRENTED_PCED_MASK       (0xFFFFFFF0U)
#define USBFSH_HCPERIODCURRENTED_PCED_SHIFT      (4U)
#define USBFSH_HCPERIODCURRENTED_PCED(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCPERIODCURRENTED_PCED_SHIFT)) & USBFSH_HCPERIODCURRENTED_PCED_MASK)

/*! @name HCCONTROLHEADED - Contains the physical address of the first endpoint descriptor of the control list */
#define USBFSH_HCCONTROLHEADED_CHED_MASK         (0xFFFFFFF0U)
#define USBFSH_HCCONTROLHEADED_CHED_SHIFT        (4U)
#define USBFSH_HCCONTROLHEADED_CHED(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROLHEADED_CHED_SHIFT)) & USBFSH_HCCONTROLHEADED_CHED_MASK)

/*! @name HCCONTROLCURRENTED - Contains the physical address of the current endpoint descriptor of the control list */
#define USBFSH_HCCONTROLCURRENTED_CCED_MASK      (0xFFFFFFF0U)
#define USBFSH_HCCONTROLCURRENTED_CCED_SHIFT     (4U)
#define USBFSH_HCCONTROLCURRENTED_CCED(x)        (((uint32_t)(((uint32_t)(x)) << USBFSH_HCCONTROLCURRENTED_CCED_SHIFT)) & USBFSH_HCCONTROLCURRENTED_CCED_MASK)

/*! @name HCBULKHEADED - Contains the physical address of the first endpoint descriptor of the bulk list */
#define USBFSH_HCBULKHEADED_BHED_MASK            (0xFFFFFFF0U)
#define USBFSH_HCBULKHEADED_BHED_SHIFT           (4U)
#define USBFSH_HCBULKHEADED_BHED(x)              (((uint32_t)(((uint32_t)(x)) << USBFSH_HCBULKHEADED_BHED_SHIFT)) & USBFSH_HCBULKHEADED_BHED_MASK)

/*! @name HCBULKCURRENTED - Contains the physical address of the current endpoint descriptor of the bulk list */
#define USBFSH_HCBULKCURRENTED_BCED_MASK         (0xFFFFFFF0U)
#define USBFSH_HCBULKCURRENTED_BCED_SHIFT        (4U)
#define USBFSH_HCBULKCURRENTED_BCED(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCBULKCURRENTED_BCED_SHIFT)) & USBFSH_HCBULKCURRENTED_BCED_MASK)

/*! @name HCDONEHEAD - Contains the physical address of the last transfer descriptor added to the 'Done' queue */
#define USBFSH_HCDONEHEAD_DH_MASK                (0xFFFFFFF0U)
#define USBFSH_HCDONEHEAD_DH_SHIFT               (4U)
#define USBFSH_HCDONEHEAD_DH(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCDONEHEAD_DH_SHIFT)) & USBFSH_HCDONEHEAD_DH_MASK)

/*! @name HCFMINTERVAL - Defines the bit time interval in a frame and the full speed maximum packet size which would not cause an overrun */
#define USBFSH_HCFMINTERVAL_FI_MASK              (0x3FFFU)
#define USBFSH_HCFMINTERVAL_FI_SHIFT             (0U)
#define USBFSH_HCFMINTERVAL_FI(x)                (((uint32_t)(((uint32_t)(x)) << USBFSH_HCFMINTERVAL_FI_SHIFT)) & USBFSH_HCFMINTERVAL_FI_MASK)
#define USBFSH_HCFMINTERVAL_FSMPS_MASK           (0x7FFF0000U)
#define USBFSH_HCFMINTERVAL_FSMPS_SHIFT          (16U)
#define USBFSH_HCFMINTERVAL_FSMPS(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCFMINTERVAL_FSMPS_SHIFT)) & USBFSH_HCFMINTERVAL_FSMPS_MASK)
#define USBFSH_HCFMINTERVAL_FIT_MASK             (0x80000000U)
#define USBFSH_HCFMINTERVAL_FIT_SHIFT            (31U)
#define USBFSH_HCFMINTERVAL_FIT(x)               (((uint32_t)(((uint32_t)(x)) << USBFSH_HCFMINTERVAL_FIT_SHIFT)) & USBFSH_HCFMINTERVAL_FIT_MASK)

/*! @name HCFMREMAINING - A 14-bit counter showing the bit time remaining in the current frame */
#define USBFSH_HCFMREMAINING_FR_MASK             (0x3FFFU)
#define USBFSH_HCFMREMAINING_FR_SHIFT            (0U)
#define USBFSH_HCFMREMAINING_FR(x)               (((uint32_t)(((uint32_t)(x)) << USBFSH_HCFMREMAINING_FR_SHIFT)) & USBFSH_HCFMREMAINING_FR_MASK)
#define USBFSH_HCFMREMAINING_FRT_MASK            (0x80000000U)
#define USBFSH_HCFMREMAINING_FRT_SHIFT           (31U)
#define USBFSH_HCFMREMAINING_FRT(x)              (((uint32_t)(((uint32_t)(x)) << USBFSH_HCFMREMAINING_FRT_SHIFT)) & USBFSH_HCFMREMAINING_FRT_MASK)

/*! @name HCFMNUMBER - Contains a 16-bit counter and provides the timing reference among events happening in the HC and the HCD */
#define USBFSH_HCFMNUMBER_FN_MASK                (0xFFFFU)
#define USBFSH_HCFMNUMBER_FN_SHIFT               (0U)
#define USBFSH_HCFMNUMBER_FN(x)                  (((uint32_t)(((uint32_t)(x)) << USBFSH_HCFMNUMBER_FN_SHIFT)) & USBFSH_HCFMNUMBER_FN_MASK)

/*! @name HCPERIODICSTART - Contains a programmable 14-bit value which determines the earliest time HC should start processing a periodic list */
#define USBFSH_HCPERIODICSTART_PS_MASK           (0x3FFFU)
#define USBFSH_HCPERIODICSTART_PS_SHIFT          (0U)
#define USBFSH_HCPERIODICSTART_PS(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCPERIODICSTART_PS_SHIFT)) & USBFSH_HCPERIODICSTART_PS_MASK)

/*! @name HCLSTHRESHOLD - Contains 11-bit value which is used by the HC to determine whether to commit to transfer a maximum of 8-byte LS packet before EOF */
#define USBFSH_HCLSTHRESHOLD_LST_MASK            (0xFFFU)
#define USBFSH_HCLSTHRESHOLD_LST_SHIFT           (0U)
#define USBFSH_HCLSTHRESHOLD_LST(x)              (((uint32_t)(((uint32_t)(x)) << USBFSH_HCLSTHRESHOLD_LST_SHIFT)) & USBFSH_HCLSTHRESHOLD_LST_MASK)

/*! @name HCRHDESCRIPTORA - First of the two registers which describes the characteristics of the root hub */
#define USBFSH_HCRHDESCRIPTORA_NDP_MASK          (0xFFU)
#define USBFSH_HCRHDESCRIPTORA_NDP_SHIFT         (0U)
#define USBFSH_HCRHDESCRIPTORA_NDP(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_NDP_SHIFT)) & USBFSH_HCRHDESCRIPTORA_NDP_MASK)
#define USBFSH_HCRHDESCRIPTORA_PSM_MASK          (0x100U)
#define USBFSH_HCRHDESCRIPTORA_PSM_SHIFT         (8U)
#define USBFSH_HCRHDESCRIPTORA_PSM(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_PSM_SHIFT)) & USBFSH_HCRHDESCRIPTORA_PSM_MASK)
#define USBFSH_HCRHDESCRIPTORA_NPS_MASK          (0x200U)
#define USBFSH_HCRHDESCRIPTORA_NPS_SHIFT         (9U)
#define USBFSH_HCRHDESCRIPTORA_NPS(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_NPS_SHIFT)) & USBFSH_HCRHDESCRIPTORA_NPS_MASK)
#define USBFSH_HCRHDESCRIPTORA_DT_MASK           (0x400U)
#define USBFSH_HCRHDESCRIPTORA_DT_SHIFT          (10U)
#define USBFSH_HCRHDESCRIPTORA_DT(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_DT_SHIFT)) & USBFSH_HCRHDESCRIPTORA_DT_MASK)
#define USBFSH_HCRHDESCRIPTORA_OCPM_MASK         (0x800U)
#define USBFSH_HCRHDESCRIPTORA_OCPM_SHIFT        (11U)
#define USBFSH_HCRHDESCRIPTORA_OCPM(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_OCPM_SHIFT)) & USBFSH_HCRHDESCRIPTORA_OCPM_MASK)
#define USBFSH_HCRHDESCRIPTORA_NOCP_MASK         (0x1000U)
#define USBFSH_HCRHDESCRIPTORA_NOCP_SHIFT        (12U)
#define USBFSH_HCRHDESCRIPTORA_NOCP(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_NOCP_SHIFT)) & USBFSH_HCRHDESCRIPTORA_NOCP_MASK)
#define USBFSH_HCRHDESCRIPTORA_POTPGT_MASK       (0xFF000000U)
#define USBFSH_HCRHDESCRIPTORA_POTPGT_SHIFT      (24U)
#define USBFSH_HCRHDESCRIPTORA_POTPGT(x)         (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORA_POTPGT_SHIFT)) & USBFSH_HCRHDESCRIPTORA_POTPGT_MASK)

/*! @name HCRHDESCRIPTORB - Second of the two registers which describes the characteristics of the Root Hub */
#define USBFSH_HCRHDESCRIPTORB_DR_MASK           (0xFFFFU)
#define USBFSH_HCRHDESCRIPTORB_DR_SHIFT          (0U)
#define USBFSH_HCRHDESCRIPTORB_DR(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORB_DR_SHIFT)) & USBFSH_HCRHDESCRIPTORB_DR_MASK)
#define USBFSH_HCRHDESCRIPTORB_PPCM_MASK         (0xFFFF0000U)
#define USBFSH_HCRHDESCRIPTORB_PPCM_SHIFT        (16U)
#define USBFSH_HCRHDESCRIPTORB_PPCM(x)           (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHDESCRIPTORB_PPCM_SHIFT)) & USBFSH_HCRHDESCRIPTORB_PPCM_MASK)

/*! @name HCRHSTATUS - This register is divided into two parts */
#define USBFSH_HCRHSTATUS_LPS_MASK               (0x1U)
#define USBFSH_HCRHSTATUS_LPS_SHIFT              (0U)
#define USBFSH_HCRHSTATUS_LPS(x)                 (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHSTATUS_LPS_SHIFT)) & USBFSH_HCRHSTATUS_LPS_MASK)
#define USBFSH_HCRHSTATUS_OCI_MASK               (0x2U)
#define USBFSH_HCRHSTATUS_OCI_SHIFT              (1U)
#define USBFSH_HCRHSTATUS_OCI(x)                 (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHSTATUS_OCI_SHIFT)) & USBFSH_HCRHSTATUS_OCI_MASK)
#define USBFSH_HCRHSTATUS_DRWE_MASK              (0x8000U)
#define USBFSH_HCRHSTATUS_DRWE_SHIFT             (15U)
#define USBFSH_HCRHSTATUS_DRWE(x)                (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHSTATUS_DRWE_SHIFT)) & USBFSH_HCRHSTATUS_DRWE_MASK)
#define USBFSH_HCRHSTATUS_LPSC_MASK              (0x10000U)
#define USBFSH_HCRHSTATUS_LPSC_SHIFT             (16U)
#define USBFSH_HCRHSTATUS_LPSC(x)                (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHSTATUS_LPSC_SHIFT)) & USBFSH_HCRHSTATUS_LPSC_MASK)
#define USBFSH_HCRHSTATUS_OCIC_MASK              (0x20000U)
#define USBFSH_HCRHSTATUS_OCIC_SHIFT             (17U)
#define USBFSH_HCRHSTATUS_OCIC(x)                (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHSTATUS_OCIC_SHIFT)) & USBFSH_HCRHSTATUS_OCIC_MASK)
#define USBFSH_HCRHSTATUS_CRWE_MASK              (0x80000000U)
#define USBFSH_HCRHSTATUS_CRWE_SHIFT             (31U)
#define USBFSH_HCRHSTATUS_CRWE(x)                (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHSTATUS_CRWE_SHIFT)) & USBFSH_HCRHSTATUS_CRWE_MASK)

/*! @name HCRHPORTSTATUS - Controls and reports the port events on a per-port basis */
#define USBFSH_HCRHPORTSTATUS_CCS_MASK           (0x1U)
#define USBFSH_HCRHPORTSTATUS_CCS_SHIFT          (0U)
#define USBFSH_HCRHPORTSTATUS_CCS(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_CCS_SHIFT)) & USBFSH_HCRHPORTSTATUS_CCS_MASK)
#define USBFSH_HCRHPORTSTATUS_PES_MASK           (0x2U)
#define USBFSH_HCRHPORTSTATUS_PES_SHIFT          (1U)
#define USBFSH_HCRHPORTSTATUS_PES(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PES_SHIFT)) & USBFSH_HCRHPORTSTATUS_PES_MASK)
#define USBFSH_HCRHPORTSTATUS_PSS_MASK           (0x4U)
#define USBFSH_HCRHPORTSTATUS_PSS_SHIFT          (2U)
#define USBFSH_HCRHPORTSTATUS_PSS(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PSS_SHIFT)) & USBFSH_HCRHPORTSTATUS_PSS_MASK)
#define USBFSH_HCRHPORTSTATUS_POCI_MASK          (0x8U)
#define USBFSH_HCRHPORTSTATUS_POCI_SHIFT         (3U)
#define USBFSH_HCRHPORTSTATUS_POCI(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_POCI_SHIFT)) & USBFSH_HCRHPORTSTATUS_POCI_MASK)
#define USBFSH_HCRHPORTSTATUS_PRS_MASK           (0x10U)
#define USBFSH_HCRHPORTSTATUS_PRS_SHIFT          (4U)
#define USBFSH_HCRHPORTSTATUS_PRS(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PRS_SHIFT)) & USBFSH_HCRHPORTSTATUS_PRS_MASK)
#define USBFSH_HCRHPORTSTATUS_PPS_MASK           (0x100U)
#define USBFSH_HCRHPORTSTATUS_PPS_SHIFT          (8U)
#define USBFSH_HCRHPORTSTATUS_PPS(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PPS_SHIFT)) & USBFSH_HCRHPORTSTATUS_PPS_MASK)
#define USBFSH_HCRHPORTSTATUS_LSDA_MASK          (0x200U)
#define USBFSH_HCRHPORTSTATUS_LSDA_SHIFT         (9U)
#define USBFSH_HCRHPORTSTATUS_LSDA(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_LSDA_SHIFT)) & USBFSH_HCRHPORTSTATUS_LSDA_MASK)
#define USBFSH_HCRHPORTSTATUS_CSC_MASK           (0x10000U)
#define USBFSH_HCRHPORTSTATUS_CSC_SHIFT          (16U)
#define USBFSH_HCRHPORTSTATUS_CSC(x)             (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_CSC_SHIFT)) & USBFSH_HCRHPORTSTATUS_CSC_MASK)
#define USBFSH_HCRHPORTSTATUS_PESC_MASK          (0x20000U)
#define USBFSH_HCRHPORTSTATUS_PESC_SHIFT         (17U)
#define USBFSH_HCRHPORTSTATUS_PESC(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PESC_SHIFT)) & USBFSH_HCRHPORTSTATUS_PESC_MASK)
#define USBFSH_HCRHPORTSTATUS_PSSC_MASK          (0x40000U)
#define USBFSH_HCRHPORTSTATUS_PSSC_SHIFT         (18U)
#define USBFSH_HCRHPORTSTATUS_PSSC(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PSSC_SHIFT)) & USBFSH_HCRHPORTSTATUS_PSSC_MASK)
#define USBFSH_HCRHPORTSTATUS_OCIC_MASK          (0x80000U)
#define USBFSH_HCRHPORTSTATUS_OCIC_SHIFT         (19U)
#define USBFSH_HCRHPORTSTATUS_OCIC(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_OCIC_SHIFT)) & USBFSH_HCRHPORTSTATUS_OCIC_MASK)
#define USBFSH_HCRHPORTSTATUS_PRSC_MASK          (0x100000U)
#define USBFSH_HCRHPORTSTATUS_PRSC_SHIFT         (20U)
#define USBFSH_HCRHPORTSTATUS_PRSC(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_HCRHPORTSTATUS_PRSC_SHIFT)) & USBFSH_HCRHPORTSTATUS_PRSC_MASK)

/*! @name PORTMODE - Controls the port if it is attached to the host block or the device block */
#define USBFSH_PORTMODE_ID_MASK                  (0x1U)
#define USBFSH_PORTMODE_ID_SHIFT                 (0U)
#define USBFSH_PORTMODE_ID(x)                    (((uint32_t)(((uint32_t)(x)) << USBFSH_PORTMODE_ID_SHIFT)) & USBFSH_PORTMODE_ID_MASK)
#define USBFSH_PORTMODE_ID_EN_MASK               (0x100U)
#define USBFSH_PORTMODE_ID_EN_SHIFT              (8U)
#define USBFSH_PORTMODE_ID_EN(x)                 (((uint32_t)(((uint32_t)(x)) << USBFSH_PORTMODE_ID_EN_SHIFT)) & USBFSH_PORTMODE_ID_EN_MASK)
#define USBFSH_PORTMODE_DEV_ENABLE_MASK          (0x10000U)
#define USBFSH_PORTMODE_DEV_ENABLE_SHIFT         (16U)
#define USBFSH_PORTMODE_DEV_ENABLE(x)            (((uint32_t)(((uint32_t)(x)) << USBFSH_PORTMODE_DEV_ENABLE_SHIFT)) & USBFSH_PORTMODE_DEV_ENABLE_MASK)


/*!
 * @}
 */ /* end of group USBFSH_Register_Masks */


/* USBFSH - Peripheral instance base addresses */
/** Peripheral USBFSH base address */
#define USBFSH_BASE                              (0x400A2000u)
/** Peripheral USBFSH base pointer */
#define USBFSH                                   ((USBFSH_Type *)USBFSH_BASE)
/** Array initializer of USBFSH peripheral base addresses */
#define USBFSH_BASE_ADDRS                        { USBFSH_BASE }
/** Array initializer of USBFSH peripheral base pointers */
#define USBFSH_BASE_PTRS                         { USBFSH }
/** Interrupt vectors for the USBFSH peripheral type */
#define USBFSH_IRQS                              { USB0_IRQn }
#define USBFSH_NEEDCLK_IRQS                      { USB0_NEEDCLK_IRQn }

/*!
 * @}
 */ /* end of group USBFSH_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- USBHSD Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBHSD_Peripheral_Access_Layer USBHSD Peripheral Access Layer
 * @{
 */

/** USBHSD - Register Layout Typedef */
typedef struct {
  __IO uint32_t DEVCMDSTAT;                        /**< USB Device Command/Status register, offset: 0x0 */
  __I  uint32_t INFO;                              /**< USB Info register, offset: 0x4 */
  __IO uint32_t EPLISTSTART;                       /**< USB EP Command/Status List start address, offset: 0x8 */
  __I  uint32_t DATABUFSTART;                      /**< USB Data buffer start address, offset: 0xC */
  __IO uint32_t LPM;                               /**< USB Link Power Management register, offset: 0x10 */
  __IO uint32_t EPSKIP;                            /**< USB Endpoint skip, offset: 0x14 */
  __IO uint32_t EPINUSE;                           /**< USB Endpoint Buffer in use, offset: 0x18 */
  __IO uint32_t EPBUFCFG;                          /**< USB Endpoint Buffer Configuration register, offset: 0x1C */
  __IO uint32_t INTSTAT;                           /**< USB interrupt status register, offset: 0x20 */
  __IO uint32_t INTEN;                             /**< USB interrupt enable register, offset: 0x24 */
  __IO uint32_t INTSETSTAT;                        /**< USB set interrupt status register, offset: 0x28 */
       uint8_t RESERVED_0[8];
  __I  uint32_t EPTOGGLE;                          /**< USB Endpoint toggle register, offset: 0x34 */
       uint8_t RESERVED_1[4];
  __IO uint32_t ULPIDEBUG;                         /**< UTMI/ULPI debug register, offset: 0x3C */
} USBHSD_Type;

/* ----------------------------------------------------------------------------
   -- USBHSD Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBHSD_Register_Masks USBHSD Register Masks
 * @{
 */

/*! @name DEVCMDSTAT - USB Device Command/Status register */
#define USBHSD_DEVCMDSTAT_DEV_ADDR_MASK          (0x7FU)
#define USBHSD_DEVCMDSTAT_DEV_ADDR_SHIFT         (0U)
#define USBHSD_DEVCMDSTAT_DEV_ADDR(x)            (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DEV_ADDR_SHIFT)) & USBHSD_DEVCMDSTAT_DEV_ADDR_MASK)
#define USBHSD_DEVCMDSTAT_DEV_EN_MASK            (0x80U)
#define USBHSD_DEVCMDSTAT_DEV_EN_SHIFT           (7U)
#define USBHSD_DEVCMDSTAT_DEV_EN(x)              (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DEV_EN_SHIFT)) & USBHSD_DEVCMDSTAT_DEV_EN_MASK)
#define USBHSD_DEVCMDSTAT_SETUP_MASK             (0x100U)
#define USBHSD_DEVCMDSTAT_SETUP_SHIFT            (8U)
#define USBHSD_DEVCMDSTAT_SETUP(x)               (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_SETUP_SHIFT)) & USBHSD_DEVCMDSTAT_SETUP_MASK)
#define USBHSD_DEVCMDSTAT_FORCE_NEEDCLK_MASK     (0x200U)
#define USBHSD_DEVCMDSTAT_FORCE_NEEDCLK_SHIFT    (9U)
#define USBHSD_DEVCMDSTAT_FORCE_NEEDCLK(x)       (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_FORCE_NEEDCLK_SHIFT)) & USBHSD_DEVCMDSTAT_FORCE_NEEDCLK_MASK)
#define USBHSD_DEVCMDSTAT_FORCE_VBUS_MASK        (0x400U)
#define USBHSD_DEVCMDSTAT_FORCE_VBUS_SHIFT       (10U)
#define USBHSD_DEVCMDSTAT_FORCE_VBUS(x)          (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_FORCE_VBUS_SHIFT)) & USBHSD_DEVCMDSTAT_FORCE_VBUS_MASK)
#define USBHSD_DEVCMDSTAT_LPM_SUP_MASK           (0x800U)
#define USBHSD_DEVCMDSTAT_LPM_SUP_SHIFT          (11U)
#define USBHSD_DEVCMDSTAT_LPM_SUP(x)             (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_LPM_SUP_SHIFT)) & USBHSD_DEVCMDSTAT_LPM_SUP_MASK)
#define USBHSD_DEVCMDSTAT_INTONNAK_AO_MASK       (0x1000U)
#define USBHSD_DEVCMDSTAT_INTONNAK_AO_SHIFT      (12U)
#define USBHSD_DEVCMDSTAT_INTONNAK_AO(x)         (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_INTONNAK_AO_SHIFT)) & USBHSD_DEVCMDSTAT_INTONNAK_AO_MASK)
#define USBHSD_DEVCMDSTAT_INTONNAK_AI_MASK       (0x2000U)
#define USBHSD_DEVCMDSTAT_INTONNAK_AI_SHIFT      (13U)
#define USBHSD_DEVCMDSTAT_INTONNAK_AI(x)         (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_INTONNAK_AI_SHIFT)) & USBHSD_DEVCMDSTAT_INTONNAK_AI_MASK)
#define USBHSD_DEVCMDSTAT_INTONNAK_CO_MASK       (0x4000U)
#define USBHSD_DEVCMDSTAT_INTONNAK_CO_SHIFT      (14U)
#define USBHSD_DEVCMDSTAT_INTONNAK_CO(x)         (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_INTONNAK_CO_SHIFT)) & USBHSD_DEVCMDSTAT_INTONNAK_CO_MASK)
#define USBHSD_DEVCMDSTAT_INTONNAK_CI_MASK       (0x8000U)
#define USBHSD_DEVCMDSTAT_INTONNAK_CI_SHIFT      (15U)
#define USBHSD_DEVCMDSTAT_INTONNAK_CI(x)         (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_INTONNAK_CI_SHIFT)) & USBHSD_DEVCMDSTAT_INTONNAK_CI_MASK)
#define USBHSD_DEVCMDSTAT_DCON_MASK              (0x10000U)
#define USBHSD_DEVCMDSTAT_DCON_SHIFT             (16U)
#define USBHSD_DEVCMDSTAT_DCON(x)                (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DCON_SHIFT)) & USBHSD_DEVCMDSTAT_DCON_MASK)
#define USBHSD_DEVCMDSTAT_DSUS_MASK              (0x20000U)
#define USBHSD_DEVCMDSTAT_DSUS_SHIFT             (17U)
#define USBHSD_DEVCMDSTAT_DSUS(x)                (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DSUS_SHIFT)) & USBHSD_DEVCMDSTAT_DSUS_MASK)
#define USBHSD_DEVCMDSTAT_LPM_SUS_MASK           (0x80000U)
#define USBHSD_DEVCMDSTAT_LPM_SUS_SHIFT          (19U)
#define USBHSD_DEVCMDSTAT_LPM_SUS(x)             (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_LPM_SUS_SHIFT)) & USBHSD_DEVCMDSTAT_LPM_SUS_MASK)
#define USBHSD_DEVCMDSTAT_LPM_REWP_MASK          (0x100000U)
#define USBHSD_DEVCMDSTAT_LPM_REWP_SHIFT         (20U)
#define USBHSD_DEVCMDSTAT_LPM_REWP(x)            (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_LPM_REWP_SHIFT)) & USBHSD_DEVCMDSTAT_LPM_REWP_MASK)
#define USBHSD_DEVCMDSTAT_Speed_MASK             (0xC00000U)
#define USBHSD_DEVCMDSTAT_Speed_SHIFT            (22U)
#define USBHSD_DEVCMDSTAT_Speed(x)               (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_Speed_SHIFT)) & USBHSD_DEVCMDSTAT_Speed_MASK)
#define USBHSD_DEVCMDSTAT_DCON_C_MASK            (0x1000000U)
#define USBHSD_DEVCMDSTAT_DCON_C_SHIFT           (24U)
#define USBHSD_DEVCMDSTAT_DCON_C(x)              (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DCON_C_SHIFT)) & USBHSD_DEVCMDSTAT_DCON_C_MASK)
#define USBHSD_DEVCMDSTAT_DSUS_C_MASK            (0x2000000U)
#define USBHSD_DEVCMDSTAT_DSUS_C_SHIFT           (25U)
#define USBHSD_DEVCMDSTAT_DSUS_C(x)              (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DSUS_C_SHIFT)) & USBHSD_DEVCMDSTAT_DSUS_C_MASK)
#define USBHSD_DEVCMDSTAT_DRES_C_MASK            (0x4000000U)
#define USBHSD_DEVCMDSTAT_DRES_C_SHIFT           (26U)
#define USBHSD_DEVCMDSTAT_DRES_C(x)              (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_DRES_C_SHIFT)) & USBHSD_DEVCMDSTAT_DRES_C_MASK)
#define USBHSD_DEVCMDSTAT_VBUS_DEBOUNCED_MASK    (0x10000000U)
#define USBHSD_DEVCMDSTAT_VBUS_DEBOUNCED_SHIFT   (28U)
#define USBHSD_DEVCMDSTAT_VBUS_DEBOUNCED(x)      (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_VBUS_DEBOUNCED_SHIFT)) & USBHSD_DEVCMDSTAT_VBUS_DEBOUNCED_MASK)
#define USBHSD_DEVCMDSTAT_PHY_TEST_MODE_MASK     (0xE0000000U)
#define USBHSD_DEVCMDSTAT_PHY_TEST_MODE_SHIFT    (29U)
#define USBHSD_DEVCMDSTAT_PHY_TEST_MODE(x)       (((uint32_t)(((uint32_t)(x)) << USBHSD_DEVCMDSTAT_PHY_TEST_MODE_SHIFT)) & USBHSD_DEVCMDSTAT_PHY_TEST_MODE_MASK)

/*! @name INFO - USB Info register */
#define USBHSD_INFO_FRAME_NR_MASK                (0x7FFU)
#define USBHSD_INFO_FRAME_NR_SHIFT               (0U)
#define USBHSD_INFO_FRAME_NR(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INFO_FRAME_NR_SHIFT)) & USBHSD_INFO_FRAME_NR_MASK)
#define USBHSD_INFO_ERR_CODE_MASK                (0x7800U)
#define USBHSD_INFO_ERR_CODE_SHIFT               (11U)
#define USBHSD_INFO_ERR_CODE(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INFO_ERR_CODE_SHIFT)) & USBHSD_INFO_ERR_CODE_MASK)
#define USBHSD_INFO_Minrev_MASK                  (0xFF0000U)
#define USBHSD_INFO_Minrev_SHIFT                 (16U)
#define USBHSD_INFO_Minrev(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSD_INFO_Minrev_SHIFT)) & USBHSD_INFO_Minrev_MASK)
#define USBHSD_INFO_Majrev_MASK                  (0xFF000000U)
#define USBHSD_INFO_Majrev_SHIFT                 (24U)
#define USBHSD_INFO_Majrev(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSD_INFO_Majrev_SHIFT)) & USBHSD_INFO_Majrev_MASK)

/*! @name EPLISTSTART - USB EP Command/Status List start address */
#define USBHSD_EPLISTSTART_EP_LIST_PRG_MASK      (0xFFF00U)
#define USBHSD_EPLISTSTART_EP_LIST_PRG_SHIFT     (8U)
#define USBHSD_EPLISTSTART_EP_LIST_PRG(x)        (((uint32_t)(((uint32_t)(x)) << USBHSD_EPLISTSTART_EP_LIST_PRG_SHIFT)) & USBHSD_EPLISTSTART_EP_LIST_PRG_MASK)
#define USBHSD_EPLISTSTART_EP_LIST_FIXED_MASK    (0xFFF00000U)
#define USBHSD_EPLISTSTART_EP_LIST_FIXED_SHIFT   (20U)
#define USBHSD_EPLISTSTART_EP_LIST_FIXED(x)      (((uint32_t)(((uint32_t)(x)) << USBHSD_EPLISTSTART_EP_LIST_FIXED_SHIFT)) & USBHSD_EPLISTSTART_EP_LIST_FIXED_MASK)

/*! @name DATABUFSTART - USB Data buffer start address */
#define USBHSD_DATABUFSTART_DA_BUF_MASK          (0xFFFFFFFFU)
#define USBHSD_DATABUFSTART_DA_BUF_SHIFT         (0U)
#define USBHSD_DATABUFSTART_DA_BUF(x)            (((uint32_t)(((uint32_t)(x)) << USBHSD_DATABUFSTART_DA_BUF_SHIFT)) & USBHSD_DATABUFSTART_DA_BUF_MASK)

/*! @name LPM - USB Link Power Management register */
#define USBHSD_LPM_HIRD_HW_MASK                  (0xFU)
#define USBHSD_LPM_HIRD_HW_SHIFT                 (0U)
#define USBHSD_LPM_HIRD_HW(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSD_LPM_HIRD_HW_SHIFT)) & USBHSD_LPM_HIRD_HW_MASK)
#define USBHSD_LPM_HIRD_SW_MASK                  (0xF0U)
#define USBHSD_LPM_HIRD_SW_SHIFT                 (4U)
#define USBHSD_LPM_HIRD_SW(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSD_LPM_HIRD_SW_SHIFT)) & USBHSD_LPM_HIRD_SW_MASK)
#define USBHSD_LPM_DATA_PENDING_MASK             (0x100U)
#define USBHSD_LPM_DATA_PENDING_SHIFT            (8U)
#define USBHSD_LPM_DATA_PENDING(x)               (((uint32_t)(((uint32_t)(x)) << USBHSD_LPM_DATA_PENDING_SHIFT)) & USBHSD_LPM_DATA_PENDING_MASK)

/*! @name EPSKIP - USB Endpoint skip */
#define USBHSD_EPSKIP_SKIP_MASK                  (0xFFFU)
#define USBHSD_EPSKIP_SKIP_SHIFT                 (0U)
#define USBHSD_EPSKIP_SKIP(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSD_EPSKIP_SKIP_SHIFT)) & USBHSD_EPSKIP_SKIP_MASK)

/*! @name EPINUSE - USB Endpoint Buffer in use */
#define USBHSD_EPINUSE_BUF_MASK                  (0xFFCU)
#define USBHSD_EPINUSE_BUF_SHIFT                 (2U)
#define USBHSD_EPINUSE_BUF(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSD_EPINUSE_BUF_SHIFT)) & USBHSD_EPINUSE_BUF_MASK)

/*! @name EPBUFCFG - USB Endpoint Buffer Configuration register */
#define USBHSD_EPBUFCFG_BUF_SB_MASK              (0xFFCU)
#define USBHSD_EPBUFCFG_BUF_SB_SHIFT             (2U)
#define USBHSD_EPBUFCFG_BUF_SB(x)                (((uint32_t)(((uint32_t)(x)) << USBHSD_EPBUFCFG_BUF_SB_SHIFT)) & USBHSD_EPBUFCFG_BUF_SB_MASK)

/*! @name INTSTAT - USB interrupt status register */
#define USBHSD_INTSTAT_EP0OUT_MASK               (0x1U)
#define USBHSD_INTSTAT_EP0OUT_SHIFT              (0U)
#define USBHSD_INTSTAT_EP0OUT(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP0OUT_SHIFT)) & USBHSD_INTSTAT_EP0OUT_MASK)
#define USBHSD_INTSTAT_EP0IN_MASK                (0x2U)
#define USBHSD_INTSTAT_EP0IN_SHIFT               (1U)
#define USBHSD_INTSTAT_EP0IN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP0IN_SHIFT)) & USBHSD_INTSTAT_EP0IN_MASK)
#define USBHSD_INTSTAT_EP1OUT_MASK               (0x4U)
#define USBHSD_INTSTAT_EP1OUT_SHIFT              (2U)
#define USBHSD_INTSTAT_EP1OUT(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP1OUT_SHIFT)) & USBHSD_INTSTAT_EP1OUT_MASK)
#define USBHSD_INTSTAT_EP1IN_MASK                (0x8U)
#define USBHSD_INTSTAT_EP1IN_SHIFT               (3U)
#define USBHSD_INTSTAT_EP1IN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP1IN_SHIFT)) & USBHSD_INTSTAT_EP1IN_MASK)
#define USBHSD_INTSTAT_EP2OUT_MASK               (0x10U)
#define USBHSD_INTSTAT_EP2OUT_SHIFT              (4U)
#define USBHSD_INTSTAT_EP2OUT(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP2OUT_SHIFT)) & USBHSD_INTSTAT_EP2OUT_MASK)
#define USBHSD_INTSTAT_EP2IN_MASK                (0x20U)
#define USBHSD_INTSTAT_EP2IN_SHIFT               (5U)
#define USBHSD_INTSTAT_EP2IN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP2IN_SHIFT)) & USBHSD_INTSTAT_EP2IN_MASK)
#define USBHSD_INTSTAT_EP3OUT_MASK               (0x40U)
#define USBHSD_INTSTAT_EP3OUT_SHIFT              (6U)
#define USBHSD_INTSTAT_EP3OUT(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP3OUT_SHIFT)) & USBHSD_INTSTAT_EP3OUT_MASK)
#define USBHSD_INTSTAT_EP3IN_MASK                (0x80U)
#define USBHSD_INTSTAT_EP3IN_SHIFT               (7U)
#define USBHSD_INTSTAT_EP3IN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP3IN_SHIFT)) & USBHSD_INTSTAT_EP3IN_MASK)
#define USBHSD_INTSTAT_EP4OUT_MASK               (0x100U)
#define USBHSD_INTSTAT_EP4OUT_SHIFT              (8U)
#define USBHSD_INTSTAT_EP4OUT(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP4OUT_SHIFT)) & USBHSD_INTSTAT_EP4OUT_MASK)
#define USBHSD_INTSTAT_EP4IN_MASK                (0x200U)
#define USBHSD_INTSTAT_EP4IN_SHIFT               (9U)
#define USBHSD_INTSTAT_EP4IN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP4IN_SHIFT)) & USBHSD_INTSTAT_EP4IN_MASK)
#define USBHSD_INTSTAT_EP5OUT_MASK               (0x400U)
#define USBHSD_INTSTAT_EP5OUT_SHIFT              (10U)
#define USBHSD_INTSTAT_EP5OUT(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP5OUT_SHIFT)) & USBHSD_INTSTAT_EP5OUT_MASK)
#define USBHSD_INTSTAT_EP5IN_MASK                (0x800U)
#define USBHSD_INTSTAT_EP5IN_SHIFT               (11U)
#define USBHSD_INTSTAT_EP5IN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_EP5IN_SHIFT)) & USBHSD_INTSTAT_EP5IN_MASK)
#define USBHSD_INTSTAT_FRAME_INT_MASK            (0x40000000U)
#define USBHSD_INTSTAT_FRAME_INT_SHIFT           (30U)
#define USBHSD_INTSTAT_FRAME_INT(x)              (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_FRAME_INT_SHIFT)) & USBHSD_INTSTAT_FRAME_INT_MASK)
#define USBHSD_INTSTAT_DEV_INT_MASK              (0x80000000U)
#define USBHSD_INTSTAT_DEV_INT_SHIFT             (31U)
#define USBHSD_INTSTAT_DEV_INT(x)                (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSTAT_DEV_INT_SHIFT)) & USBHSD_INTSTAT_DEV_INT_MASK)

/*! @name INTEN - USB interrupt enable register */
#define USBHSD_INTEN_EP_INT_EN_MASK              (0xFFFU)
#define USBHSD_INTEN_EP_INT_EN_SHIFT             (0U)
#define USBHSD_INTEN_EP_INT_EN(x)                (((uint32_t)(((uint32_t)(x)) << USBHSD_INTEN_EP_INT_EN_SHIFT)) & USBHSD_INTEN_EP_INT_EN_MASK)
#define USBHSD_INTEN_FRAME_INT_EN_MASK           (0x40000000U)
#define USBHSD_INTEN_FRAME_INT_EN_SHIFT          (30U)
#define USBHSD_INTEN_FRAME_INT_EN(x)             (((uint32_t)(((uint32_t)(x)) << USBHSD_INTEN_FRAME_INT_EN_SHIFT)) & USBHSD_INTEN_FRAME_INT_EN_MASK)
#define USBHSD_INTEN_DEV_INT_EN_MASK             (0x80000000U)
#define USBHSD_INTEN_DEV_INT_EN_SHIFT            (31U)
#define USBHSD_INTEN_DEV_INT_EN(x)               (((uint32_t)(((uint32_t)(x)) << USBHSD_INTEN_DEV_INT_EN_SHIFT)) & USBHSD_INTEN_DEV_INT_EN_MASK)

/*! @name INTSETSTAT - USB set interrupt status register */
#define USBHSD_INTSETSTAT_EP_SET_INT_MASK        (0xFFFU)
#define USBHSD_INTSETSTAT_EP_SET_INT_SHIFT       (0U)
#define USBHSD_INTSETSTAT_EP_SET_INT(x)          (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSETSTAT_EP_SET_INT_SHIFT)) & USBHSD_INTSETSTAT_EP_SET_INT_MASK)
#define USBHSD_INTSETSTAT_FRAME_SET_INT_MASK     (0x40000000U)
#define USBHSD_INTSETSTAT_FRAME_SET_INT_SHIFT    (30U)
#define USBHSD_INTSETSTAT_FRAME_SET_INT(x)       (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSETSTAT_FRAME_SET_INT_SHIFT)) & USBHSD_INTSETSTAT_FRAME_SET_INT_MASK)
#define USBHSD_INTSETSTAT_DEV_SET_INT_MASK       (0x80000000U)
#define USBHSD_INTSETSTAT_DEV_SET_INT_SHIFT      (31U)
#define USBHSD_INTSETSTAT_DEV_SET_INT(x)         (((uint32_t)(((uint32_t)(x)) << USBHSD_INTSETSTAT_DEV_SET_INT_SHIFT)) & USBHSD_INTSETSTAT_DEV_SET_INT_MASK)

/*! @name EPTOGGLE - USB Endpoint toggle register */
#define USBHSD_EPTOGGLE_TOGGLE_MASK              (0x3FFFFFFFU)
#define USBHSD_EPTOGGLE_TOGGLE_SHIFT             (0U)
#define USBHSD_EPTOGGLE_TOGGLE(x)                (((uint32_t)(((uint32_t)(x)) << USBHSD_EPTOGGLE_TOGGLE_SHIFT)) & USBHSD_EPTOGGLE_TOGGLE_MASK)

/*! @name ULPIDEBUG - UTMI/ULPI debug register */
#define USBHSD_ULPIDEBUG_PHY_ADDR_MASK           (0xFFU)
#define USBHSD_ULPIDEBUG_PHY_ADDR_SHIFT          (0U)
#define USBHSD_ULPIDEBUG_PHY_ADDR(x)             (((uint32_t)(((uint32_t)(x)) << USBHSD_ULPIDEBUG_PHY_ADDR_SHIFT)) & USBHSD_ULPIDEBUG_PHY_ADDR_MASK)
#define USBHSD_ULPIDEBUG_PHY_WDATA_MASK          (0xFF00U)
#define USBHSD_ULPIDEBUG_PHY_WDATA_SHIFT         (8U)
#define USBHSD_ULPIDEBUG_PHY_WDATA(x)            (((uint32_t)(((uint32_t)(x)) << USBHSD_ULPIDEBUG_PHY_WDATA_SHIFT)) & USBHSD_ULPIDEBUG_PHY_WDATA_MASK)
#define USBHSD_ULPIDEBUG_PHY_RDATA_MASK          (0xFF0000U)
#define USBHSD_ULPIDEBUG_PHY_RDATA_SHIFT         (16U)
#define USBHSD_ULPIDEBUG_PHY_RDATA(x)            (((uint32_t)(((uint32_t)(x)) << USBHSD_ULPIDEBUG_PHY_RDATA_SHIFT)) & USBHSD_ULPIDEBUG_PHY_RDATA_MASK)
#define USBHSD_ULPIDEBUG_PHY_RW_MASK             (0x1000000U)
#define USBHSD_ULPIDEBUG_PHY_RW_SHIFT            (24U)
#define USBHSD_ULPIDEBUG_PHY_RW(x)               (((uint32_t)(((uint32_t)(x)) << USBHSD_ULPIDEBUG_PHY_RW_SHIFT)) & USBHSD_ULPIDEBUG_PHY_RW_MASK)
#define USBHSD_ULPIDEBUG_PHY_ACCESS_MASK         (0x2000000U)
#define USBHSD_ULPIDEBUG_PHY_ACCESS_SHIFT        (25U)
#define USBHSD_ULPIDEBUG_PHY_ACCESS(x)           (((uint32_t)(((uint32_t)(x)) << USBHSD_ULPIDEBUG_PHY_ACCESS_SHIFT)) & USBHSD_ULPIDEBUG_PHY_ACCESS_MASK)
#define USBHSD_ULPIDEBUG_PHY_MODE_MASK           (0x80000000U)
#define USBHSD_ULPIDEBUG_PHY_MODE_SHIFT          (31U)
#define USBHSD_ULPIDEBUG_PHY_MODE(x)             (((uint32_t)(((uint32_t)(x)) << USBHSD_ULPIDEBUG_PHY_MODE_SHIFT)) & USBHSD_ULPIDEBUG_PHY_MODE_MASK)


/*!
 * @}
 */ /* end of group USBHSD_Register_Masks */


/* USBHSD - Peripheral instance base addresses */
/** Peripheral USBHSD base address */
#define USBHSD_BASE                              (0x40094000u)
/** Peripheral USBHSD base pointer */
#define USBHSD                                   ((USBHSD_Type *)USBHSD_BASE)
/** Array initializer of USBHSD peripheral base addresses */
#define USBHSD_BASE_ADDRS                        { USBHSD_BASE }
/** Array initializer of USBHSD peripheral base pointers */
#define USBHSD_BASE_PTRS                         { USBHSD }
/** Interrupt vectors for the USBHSD peripheral type */
#define USBHSD_IRQS                              { USB1_IRQn }
#define USBHSD_NEEDCLK_IRQS                      { USB1_NEEDCLK_IRQn }

/*!
 * @}
 */ /* end of group USBHSD_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- USBHSH Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBHSH_Peripheral_Access_Layer USBHSH Peripheral Access Layer
 * @{
 */

/** USBHSH - Register Layout Typedef */
typedef struct {
  __I  uint32_t CAPLENGTH_CHIPID;                  /**< This register contains the offset value towards the start of the operational register space and the version number of the IP block, offset: 0x0 */
  __I  uint32_t HCSPARAMS;                         /**< Host Controller Structural Parameters, offset: 0x4 */
  __I  uint32_t HCCPARAMS;                         /**< Host Controller Capability Parameters, offset: 0x8 */
  __IO uint32_t FLADJ_FRINDEX;                     /**< Frame Length Adjustment, offset: 0xC */
  __IO uint32_t ATL_PTD_BASE_ADDR;                 /**< Memory base address where ATL PTD0 is stored, offset: 0x10 */
  __IO uint32_t ISO_PTD_BASE_ADDR;                 /**< Memory base address where ISO PTD0 is stored, offset: 0x14 */
  __IO uint32_t INT_PTD_BASE_ADDR;                 /**< Memory base address where INT PTD0 is stored, offset: 0x18 */
  __IO uint32_t DATA_PAYLOAD_BASE_ADDR;            /**< Memory base address that indicates the start of the data payload buffers, offset: 0x1C */
  __IO uint32_t USBCMD;                            /**< USB Command register, offset: 0x20 */
  __IO uint32_t USBSTS;                            /**< USB Interrupt Status register, offset: 0x24 */
  __IO uint32_t USBINTR;                           /**< USB Interrupt Enable register, offset: 0x28 */
  __IO uint32_t PORTSC1;                           /**< Port Status and Control register, offset: 0x2C */
  __IO uint32_t ATL_PTD_DONE_MAP;                  /**< Done map for each ATL PTD, offset: 0x30 */
  __IO uint32_t ATL_PTD_SKIP_MAP;                  /**< Skip map for each ATL PTD, offset: 0x34 */
  __IO uint32_t ISO_PTD_DONE_MAP;                  /**< Done map for each ISO PTD, offset: 0x38 */
  __IO uint32_t ISO_PTD_SKIP_MAP;                  /**< Skip map for each ISO PTD, offset: 0x3C */
  __IO uint32_t INT_PTD_DONE_MAP;                  /**< Done map for each INT PTD, offset: 0x40 */
  __IO uint32_t INT_PTD_SKIP_MAP;                  /**< Skip map for each INT PTD, offset: 0x44 */
  __IO uint32_t LAST_PTD_INUSE;                    /**< Marks the last PTD in the list for ISO, INT and ATL, offset: 0x48 */
  __IO uint32_t UTMIPLUS_ULPI_DEBUG;               /**< Register to read/write registers in the attached USB PHY, offset: 0x4C */
  __IO uint32_t PORTMODE;                          /**< Controls the port if it is attached to the host block or the device block, offset: 0x50 */
} USBHSH_Type;

/* ----------------------------------------------------------------------------
   -- USBHSH Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBHSH_Register_Masks USBHSH Register Masks
 * @{
 */

/*! @name CAPLENGTH_CHIPID - This register contains the offset value towards the start of the operational register space and the version number of the IP block */
#define USBHSH_CAPLENGTH_CHIPID_CAPLENGTH_MASK   (0xFFU)
#define USBHSH_CAPLENGTH_CHIPID_CAPLENGTH_SHIFT  (0U)
#define USBHSH_CAPLENGTH_CHIPID_CAPLENGTH(x)     (((uint32_t)(((uint32_t)(x)) << USBHSH_CAPLENGTH_CHIPID_CAPLENGTH_SHIFT)) & USBHSH_CAPLENGTH_CHIPID_CAPLENGTH_MASK)
#define USBHSH_CAPLENGTH_CHIPID_CHIPID_MASK      (0xFFFF0000U)
#define USBHSH_CAPLENGTH_CHIPID_CHIPID_SHIFT     (16U)
#define USBHSH_CAPLENGTH_CHIPID_CHIPID(x)        (((uint32_t)(((uint32_t)(x)) << USBHSH_CAPLENGTH_CHIPID_CHIPID_SHIFT)) & USBHSH_CAPLENGTH_CHIPID_CHIPID_MASK)

/*! @name HCSPARAMS - Host Controller Structural Parameters */
#define USBHSH_HCSPARAMS_N_PORTS_MASK            (0xFU)
#define USBHSH_HCSPARAMS_N_PORTS_SHIFT           (0U)
#define USBHSH_HCSPARAMS_N_PORTS(x)              (((uint32_t)(((uint32_t)(x)) << USBHSH_HCSPARAMS_N_PORTS_SHIFT)) & USBHSH_HCSPARAMS_N_PORTS_MASK)
#define USBHSH_HCSPARAMS_PPC_MASK                (0x10U)
#define USBHSH_HCSPARAMS_PPC_SHIFT               (4U)
#define USBHSH_HCSPARAMS_PPC(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSH_HCSPARAMS_PPC_SHIFT)) & USBHSH_HCSPARAMS_PPC_MASK)
#define USBHSH_HCSPARAMS_P_INDICATOR_MASK        (0x10000U)
#define USBHSH_HCSPARAMS_P_INDICATOR_SHIFT       (16U)
#define USBHSH_HCSPARAMS_P_INDICATOR(x)          (((uint32_t)(((uint32_t)(x)) << USBHSH_HCSPARAMS_P_INDICATOR_SHIFT)) & USBHSH_HCSPARAMS_P_INDICATOR_MASK)

/*! @name HCCPARAMS - Host Controller Capability Parameters */
#define USBHSH_HCCPARAMS_LPMC_MASK               (0x20000U)
#define USBHSH_HCCPARAMS_LPMC_SHIFT              (17U)
#define USBHSH_HCCPARAMS_LPMC(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSH_HCCPARAMS_LPMC_SHIFT)) & USBHSH_HCCPARAMS_LPMC_MASK)

/*! @name FLADJ_FRINDEX - Frame Length Adjustment */
#define USBHSH_FLADJ_FRINDEX_FLADJ_MASK          (0x3FU)
#define USBHSH_FLADJ_FRINDEX_FLADJ_SHIFT         (0U)
#define USBHSH_FLADJ_FRINDEX_FLADJ(x)            (((uint32_t)(((uint32_t)(x)) << USBHSH_FLADJ_FRINDEX_FLADJ_SHIFT)) & USBHSH_FLADJ_FRINDEX_FLADJ_MASK)
#define USBHSH_FLADJ_FRINDEX_FRINDEX_MASK        (0x3FFF0000U)
#define USBHSH_FLADJ_FRINDEX_FRINDEX_SHIFT       (16U)
#define USBHSH_FLADJ_FRINDEX_FRINDEX(x)          (((uint32_t)(((uint32_t)(x)) << USBHSH_FLADJ_FRINDEX_FRINDEX_SHIFT)) & USBHSH_FLADJ_FRINDEX_FRINDEX_MASK)

/*! @name ATL_PTD_BASE_ADDR - Memory base address where ATL PTD0 is stored */
#define USBHSH_ATL_PTD_BASE_ADDR_ATL_CUR_MASK    (0x1F0U)
#define USBHSH_ATL_PTD_BASE_ADDR_ATL_CUR_SHIFT   (4U)
#define USBHSH_ATL_PTD_BASE_ADDR_ATL_CUR(x)      (((uint32_t)(((uint32_t)(x)) << USBHSH_ATL_PTD_BASE_ADDR_ATL_CUR_SHIFT)) & USBHSH_ATL_PTD_BASE_ADDR_ATL_CUR_MASK)
#define USBHSH_ATL_PTD_BASE_ADDR_ATL_BASE_MASK   (0xFFFFFE00U)
#define USBHSH_ATL_PTD_BASE_ADDR_ATL_BASE_SHIFT  (9U)
#define USBHSH_ATL_PTD_BASE_ADDR_ATL_BASE(x)     (((uint32_t)(((uint32_t)(x)) << USBHSH_ATL_PTD_BASE_ADDR_ATL_BASE_SHIFT)) & USBHSH_ATL_PTD_BASE_ADDR_ATL_BASE_MASK)

/*! @name ISO_PTD_BASE_ADDR - Memory base address where ISO PTD0 is stored */
#define USBHSH_ISO_PTD_BASE_ADDR_ISO_FIRST_MASK  (0x3E0U)
#define USBHSH_ISO_PTD_BASE_ADDR_ISO_FIRST_SHIFT (5U)
#define USBHSH_ISO_PTD_BASE_ADDR_ISO_FIRST(x)    (((uint32_t)(((uint32_t)(x)) << USBHSH_ISO_PTD_BASE_ADDR_ISO_FIRST_SHIFT)) & USBHSH_ISO_PTD_BASE_ADDR_ISO_FIRST_MASK)
#define USBHSH_ISO_PTD_BASE_ADDR_ISO_BASE_MASK   (0xFFFFFC00U)
#define USBHSH_ISO_PTD_BASE_ADDR_ISO_BASE_SHIFT  (10U)
#define USBHSH_ISO_PTD_BASE_ADDR_ISO_BASE(x)     (((uint32_t)(((uint32_t)(x)) << USBHSH_ISO_PTD_BASE_ADDR_ISO_BASE_SHIFT)) & USBHSH_ISO_PTD_BASE_ADDR_ISO_BASE_MASK)

/*! @name INT_PTD_BASE_ADDR - Memory base address where INT PTD0 is stored */
#define USBHSH_INT_PTD_BASE_ADDR_INT_FIRST_MASK  (0x3E0U)
#define USBHSH_INT_PTD_BASE_ADDR_INT_FIRST_SHIFT (5U)
#define USBHSH_INT_PTD_BASE_ADDR_INT_FIRST(x)    (((uint32_t)(((uint32_t)(x)) << USBHSH_INT_PTD_BASE_ADDR_INT_FIRST_SHIFT)) & USBHSH_INT_PTD_BASE_ADDR_INT_FIRST_MASK)
#define USBHSH_INT_PTD_BASE_ADDR_INT_BASE_MASK   (0xFFFFFC00U)
#define USBHSH_INT_PTD_BASE_ADDR_INT_BASE_SHIFT  (10U)
#define USBHSH_INT_PTD_BASE_ADDR_INT_BASE(x)     (((uint32_t)(((uint32_t)(x)) << USBHSH_INT_PTD_BASE_ADDR_INT_BASE_SHIFT)) & USBHSH_INT_PTD_BASE_ADDR_INT_BASE_MASK)

/*! @name DATA_PAYLOAD_BASE_ADDR - Memory base address that indicates the start of the data payload buffers */
#define USBHSH_DATA_PAYLOAD_BASE_ADDR_DAT_BASE_MASK (0xFFFF0000U)
#define USBHSH_DATA_PAYLOAD_BASE_ADDR_DAT_BASE_SHIFT (16U)
#define USBHSH_DATA_PAYLOAD_BASE_ADDR_DAT_BASE(x) (((uint32_t)(((uint32_t)(x)) << USBHSH_DATA_PAYLOAD_BASE_ADDR_DAT_BASE_SHIFT)) & USBHSH_DATA_PAYLOAD_BASE_ADDR_DAT_BASE_MASK)

/*! @name USBCMD - USB Command register */
#define USBHSH_USBCMD_RS_MASK                    (0x1U)
#define USBHSH_USBCMD_RS_SHIFT                   (0U)
#define USBHSH_USBCMD_RS(x)                      (((uint32_t)(((uint32_t)(x)) << USBHSH_USBCMD_RS_SHIFT)) & USBHSH_USBCMD_RS_MASK)
#define USBHSH_USBCMD_HCRESET_MASK               (0x2U)
#define USBHSH_USBCMD_HCRESET_SHIFT              (1U)
#define USBHSH_USBCMD_HCRESET(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSH_USBCMD_HCRESET_SHIFT)) & USBHSH_USBCMD_HCRESET_MASK)
#define USBHSH_USBCMD_FLS_MASK                   (0xCU)
#define USBHSH_USBCMD_FLS_SHIFT                  (2U)
#define USBHSH_USBCMD_FLS(x)                     (((uint32_t)(((uint32_t)(x)) << USBHSH_USBCMD_FLS_SHIFT)) & USBHSH_USBCMD_FLS_MASK)
#define USBHSH_USBCMD_LHCR_MASK                  (0x80U)
#define USBHSH_USBCMD_LHCR_SHIFT                 (7U)
#define USBHSH_USBCMD_LHCR(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSH_USBCMD_LHCR_SHIFT)) & USBHSH_USBCMD_LHCR_MASK)
#define USBHSH_USBCMD_ATL_EN_MASK                (0x100U)
#define USBHSH_USBCMD_ATL_EN_SHIFT               (8U)
#define USBHSH_USBCMD_ATL_EN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSH_USBCMD_ATL_EN_SHIFT)) & USBHSH_USBCMD_ATL_EN_MASK)
#define USBHSH_USBCMD_ISO_EN_MASK                (0x200U)
#define USBHSH_USBCMD_ISO_EN_SHIFT               (9U)
#define USBHSH_USBCMD_ISO_EN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSH_USBCMD_ISO_EN_SHIFT)) & USBHSH_USBCMD_ISO_EN_MASK)
#define USBHSH_USBCMD_INT_EN_MASK                (0x400U)
#define USBHSH_USBCMD_INT_EN_SHIFT               (10U)
#define USBHSH_USBCMD_INT_EN(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSH_USBCMD_INT_EN_SHIFT)) & USBHSH_USBCMD_INT_EN_MASK)
#define USBHSH_USBCMD_HIRD_MASK                  (0xF000000U)
#define USBHSH_USBCMD_HIRD_SHIFT                 (24U)
#define USBHSH_USBCMD_HIRD(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSH_USBCMD_HIRD_SHIFT)) & USBHSH_USBCMD_HIRD_MASK)
#define USBHSH_USBCMD_LPM_RWU_MASK               (0x10000000U)
#define USBHSH_USBCMD_LPM_RWU_SHIFT              (28U)
#define USBHSH_USBCMD_LPM_RWU(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSH_USBCMD_LPM_RWU_SHIFT)) & USBHSH_USBCMD_LPM_RWU_MASK)

/*! @name USBSTS - USB Interrupt Status register */
#define USBHSH_USBSTS_PCD_MASK                   (0x4U)
#define USBHSH_USBSTS_PCD_SHIFT                  (2U)
#define USBHSH_USBSTS_PCD(x)                     (((uint32_t)(((uint32_t)(x)) << USBHSH_USBSTS_PCD_SHIFT)) & USBHSH_USBSTS_PCD_MASK)
#define USBHSH_USBSTS_FLR_MASK                   (0x8U)
#define USBHSH_USBSTS_FLR_SHIFT                  (3U)
#define USBHSH_USBSTS_FLR(x)                     (((uint32_t)(((uint32_t)(x)) << USBHSH_USBSTS_FLR_SHIFT)) & USBHSH_USBSTS_FLR_MASK)
#define USBHSH_USBSTS_ATL_IRQ_MASK               (0x10000U)
#define USBHSH_USBSTS_ATL_IRQ_SHIFT              (16U)
#define USBHSH_USBSTS_ATL_IRQ(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSH_USBSTS_ATL_IRQ_SHIFT)) & USBHSH_USBSTS_ATL_IRQ_MASK)
#define USBHSH_USBSTS_ISO_IRQ_MASK               (0x20000U)
#define USBHSH_USBSTS_ISO_IRQ_SHIFT              (17U)
#define USBHSH_USBSTS_ISO_IRQ(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSH_USBSTS_ISO_IRQ_SHIFT)) & USBHSH_USBSTS_ISO_IRQ_MASK)
#define USBHSH_USBSTS_INT_IRQ_MASK               (0x40000U)
#define USBHSH_USBSTS_INT_IRQ_SHIFT              (18U)
#define USBHSH_USBSTS_INT_IRQ(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSH_USBSTS_INT_IRQ_SHIFT)) & USBHSH_USBSTS_INT_IRQ_MASK)
#define USBHSH_USBSTS_SOF_IRQ_MASK               (0x80000U)
#define USBHSH_USBSTS_SOF_IRQ_SHIFT              (19U)
#define USBHSH_USBSTS_SOF_IRQ(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSH_USBSTS_SOF_IRQ_SHIFT)) & USBHSH_USBSTS_SOF_IRQ_MASK)

/*! @name USBINTR - USB Interrupt Enable register */
#define USBHSH_USBINTR_PCDE_MASK                 (0x4U)
#define USBHSH_USBINTR_PCDE_SHIFT                (2U)
#define USBHSH_USBINTR_PCDE(x)                   (((uint32_t)(((uint32_t)(x)) << USBHSH_USBINTR_PCDE_SHIFT)) & USBHSH_USBINTR_PCDE_MASK)
#define USBHSH_USBINTR_FLRE_MASK                 (0x8U)
#define USBHSH_USBINTR_FLRE_SHIFT                (3U)
#define USBHSH_USBINTR_FLRE(x)                   (((uint32_t)(((uint32_t)(x)) << USBHSH_USBINTR_FLRE_SHIFT)) & USBHSH_USBINTR_FLRE_MASK)
#define USBHSH_USBINTR_ATL_IRQ_E_MASK            (0x10000U)
#define USBHSH_USBINTR_ATL_IRQ_E_SHIFT           (16U)
#define USBHSH_USBINTR_ATL_IRQ_E(x)              (((uint32_t)(((uint32_t)(x)) << USBHSH_USBINTR_ATL_IRQ_E_SHIFT)) & USBHSH_USBINTR_ATL_IRQ_E_MASK)
#define USBHSH_USBINTR_ISO_IRQ_E_MASK            (0x20000U)
#define USBHSH_USBINTR_ISO_IRQ_E_SHIFT           (17U)
#define USBHSH_USBINTR_ISO_IRQ_E(x)              (((uint32_t)(((uint32_t)(x)) << USBHSH_USBINTR_ISO_IRQ_E_SHIFT)) & USBHSH_USBINTR_ISO_IRQ_E_MASK)
#define USBHSH_USBINTR_INT_IRQ_E_MASK            (0x40000U)
#define USBHSH_USBINTR_INT_IRQ_E_SHIFT           (18U)
#define USBHSH_USBINTR_INT_IRQ_E(x)              (((uint32_t)(((uint32_t)(x)) << USBHSH_USBINTR_INT_IRQ_E_SHIFT)) & USBHSH_USBINTR_INT_IRQ_E_MASK)
#define USBHSH_USBINTR_SOF_E_MASK                (0x80000U)
#define USBHSH_USBINTR_SOF_E_SHIFT               (19U)
#define USBHSH_USBINTR_SOF_E(x)                  (((uint32_t)(((uint32_t)(x)) << USBHSH_USBINTR_SOF_E_SHIFT)) & USBHSH_USBINTR_SOF_E_MASK)

/*! @name PORTSC1 - Port Status and Control register */
#define USBHSH_PORTSC1_CCS_MASK                  (0x1U)
#define USBHSH_PORTSC1_CCS_SHIFT                 (0U)
#define USBHSH_PORTSC1_CCS(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_CCS_SHIFT)) & USBHSH_PORTSC1_CCS_MASK)
#define USBHSH_PORTSC1_CSC_MASK                  (0x2U)
#define USBHSH_PORTSC1_CSC_SHIFT                 (1U)
#define USBHSH_PORTSC1_CSC(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_CSC_SHIFT)) & USBHSH_PORTSC1_CSC_MASK)
#define USBHSH_PORTSC1_PED_MASK                  (0x4U)
#define USBHSH_PORTSC1_PED_SHIFT                 (2U)
#define USBHSH_PORTSC1_PED(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_PED_SHIFT)) & USBHSH_PORTSC1_PED_MASK)
#define USBHSH_PORTSC1_PEDC_MASK                 (0x8U)
#define USBHSH_PORTSC1_PEDC_SHIFT                (3U)
#define USBHSH_PORTSC1_PEDC(x)                   (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_PEDC_SHIFT)) & USBHSH_PORTSC1_PEDC_MASK)
#define USBHSH_PORTSC1_OCA_MASK                  (0x10U)
#define USBHSH_PORTSC1_OCA_SHIFT                 (4U)
#define USBHSH_PORTSC1_OCA(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_OCA_SHIFT)) & USBHSH_PORTSC1_OCA_MASK)
#define USBHSH_PORTSC1_OCC_MASK                  (0x20U)
#define USBHSH_PORTSC1_OCC_SHIFT                 (5U)
#define USBHSH_PORTSC1_OCC(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_OCC_SHIFT)) & USBHSH_PORTSC1_OCC_MASK)
#define USBHSH_PORTSC1_FPR_MASK                  (0x40U)
#define USBHSH_PORTSC1_FPR_SHIFT                 (6U)
#define USBHSH_PORTSC1_FPR(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_FPR_SHIFT)) & USBHSH_PORTSC1_FPR_MASK)
#define USBHSH_PORTSC1_SUSP_MASK                 (0x80U)
#define USBHSH_PORTSC1_SUSP_SHIFT                (7U)
#define USBHSH_PORTSC1_SUSP(x)                   (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_SUSP_SHIFT)) & USBHSH_PORTSC1_SUSP_MASK)
#define USBHSH_PORTSC1_PR_MASK                   (0x100U)
#define USBHSH_PORTSC1_PR_SHIFT                  (8U)
#define USBHSH_PORTSC1_PR(x)                     (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_PR_SHIFT)) & USBHSH_PORTSC1_PR_MASK)
#define USBHSH_PORTSC1_SUS_L1_MASK               (0x200U)
#define USBHSH_PORTSC1_SUS_L1_SHIFT              (9U)
#define USBHSH_PORTSC1_SUS_L1(x)                 (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_SUS_L1_SHIFT)) & USBHSH_PORTSC1_SUS_L1_MASK)
#define USBHSH_PORTSC1_LS_MASK                   (0xC00U)
#define USBHSH_PORTSC1_LS_SHIFT                  (10U)
#define USBHSH_PORTSC1_LS(x)                     (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_LS_SHIFT)) & USBHSH_PORTSC1_LS_MASK)
#define USBHSH_PORTSC1_PP_MASK                   (0x1000U)
#define USBHSH_PORTSC1_PP_SHIFT                  (12U)
#define USBHSH_PORTSC1_PP(x)                     (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_PP_SHIFT)) & USBHSH_PORTSC1_PP_MASK)
#define USBHSH_PORTSC1_PIC_MASK                  (0xC000U)
#define USBHSH_PORTSC1_PIC_SHIFT                 (14U)
#define USBHSH_PORTSC1_PIC(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_PIC_SHIFT)) & USBHSH_PORTSC1_PIC_MASK)
#define USBHSH_PORTSC1_PTC_MASK                  (0xF0000U)
#define USBHSH_PORTSC1_PTC_SHIFT                 (16U)
#define USBHSH_PORTSC1_PTC(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_PTC_SHIFT)) & USBHSH_PORTSC1_PTC_MASK)
#define USBHSH_PORTSC1_PSPD_MASK                 (0x300000U)
#define USBHSH_PORTSC1_PSPD_SHIFT                (20U)
#define USBHSH_PORTSC1_PSPD(x)                   (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_PSPD_SHIFT)) & USBHSH_PORTSC1_PSPD_MASK)
#define USBHSH_PORTSC1_WOO_MASK                  (0x400000U)
#define USBHSH_PORTSC1_WOO_SHIFT                 (22U)
#define USBHSH_PORTSC1_WOO(x)                    (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_WOO_SHIFT)) & USBHSH_PORTSC1_WOO_MASK)
#define USBHSH_PORTSC1_SUS_STAT_MASK             (0x1800000U)
#define USBHSH_PORTSC1_SUS_STAT_SHIFT            (23U)
#define USBHSH_PORTSC1_SUS_STAT(x)               (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_SUS_STAT_SHIFT)) & USBHSH_PORTSC1_SUS_STAT_MASK)
#define USBHSH_PORTSC1_DEV_ADD_MASK              (0xFE000000U)
#define USBHSH_PORTSC1_DEV_ADD_SHIFT             (25U)
#define USBHSH_PORTSC1_DEV_ADD(x)                (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTSC1_DEV_ADD_SHIFT)) & USBHSH_PORTSC1_DEV_ADD_MASK)

/*! @name ATL_PTD_DONE_MAP - Done map for each ATL PTD */
#define USBHSH_ATL_PTD_DONE_MAP_ATL_DONE_MASK    (0xFFFFFFFFU)
#define USBHSH_ATL_PTD_DONE_MAP_ATL_DONE_SHIFT   (0U)
#define USBHSH_ATL_PTD_DONE_MAP_ATL_DONE(x)      (((uint32_t)(((uint32_t)(x)) << USBHSH_ATL_PTD_DONE_MAP_ATL_DONE_SHIFT)) & USBHSH_ATL_PTD_DONE_MAP_ATL_DONE_MASK)

/*! @name ATL_PTD_SKIP_MAP - Skip map for each ATL PTD */
#define USBHSH_ATL_PTD_SKIP_MAP_ATL_SKIP_MASK    (0xFFFFFFFFU)
#define USBHSH_ATL_PTD_SKIP_MAP_ATL_SKIP_SHIFT   (0U)
#define USBHSH_ATL_PTD_SKIP_MAP_ATL_SKIP(x)      (((uint32_t)(((uint32_t)(x)) << USBHSH_ATL_PTD_SKIP_MAP_ATL_SKIP_SHIFT)) & USBHSH_ATL_PTD_SKIP_MAP_ATL_SKIP_MASK)

/*! @name ISO_PTD_DONE_MAP - Done map for each ISO PTD */
#define USBHSH_ISO_PTD_DONE_MAP_ISO_DONE_MASK    (0xFFFFFFFFU)
#define USBHSH_ISO_PTD_DONE_MAP_ISO_DONE_SHIFT   (0U)
#define USBHSH_ISO_PTD_DONE_MAP_ISO_DONE(x)      (((uint32_t)(((uint32_t)(x)) << USBHSH_ISO_PTD_DONE_MAP_ISO_DONE_SHIFT)) & USBHSH_ISO_PTD_DONE_MAP_ISO_DONE_MASK)

/*! @name ISO_PTD_SKIP_MAP - Skip map for each ISO PTD */
#define USBHSH_ISO_PTD_SKIP_MAP_ISO_SKIP_MASK    (0xFFFFFFFFU)
#define USBHSH_ISO_PTD_SKIP_MAP_ISO_SKIP_SHIFT   (0U)
#define USBHSH_ISO_PTD_SKIP_MAP_ISO_SKIP(x)      (((uint32_t)(((uint32_t)(x)) << USBHSH_ISO_PTD_SKIP_MAP_ISO_SKIP_SHIFT)) & USBHSH_ISO_PTD_SKIP_MAP_ISO_SKIP_MASK)

/*! @name INT_PTD_DONE_MAP - Done map for each INT PTD */
#define USBHSH_INT_PTD_DONE_MAP_INT_DONE_MASK    (0xFFFFFFFFU)
#define USBHSH_INT_PTD_DONE_MAP_INT_DONE_SHIFT   (0U)
#define USBHSH_INT_PTD_DONE_MAP_INT_DONE(x)      (((uint32_t)(((uint32_t)(x)) << USBHSH_INT_PTD_DONE_MAP_INT_DONE_SHIFT)) & USBHSH_INT_PTD_DONE_MAP_INT_DONE_MASK)

/*! @name INT_PTD_SKIP_MAP - Skip map for each INT PTD */
#define USBHSH_INT_PTD_SKIP_MAP_INT_SKIP_MASK    (0xFFFFFFFFU)
#define USBHSH_INT_PTD_SKIP_MAP_INT_SKIP_SHIFT   (0U)
#define USBHSH_INT_PTD_SKIP_MAP_INT_SKIP(x)      (((uint32_t)(((uint32_t)(x)) << USBHSH_INT_PTD_SKIP_MAP_INT_SKIP_SHIFT)) & USBHSH_INT_PTD_SKIP_MAP_INT_SKIP_MASK)

/*! @name LAST_PTD_INUSE - Marks the last PTD in the list for ISO, INT and ATL */
#define USBHSH_LAST_PTD_INUSE_ATL_LAST_MASK      (0x1FU)
#define USBHSH_LAST_PTD_INUSE_ATL_LAST_SHIFT     (0U)
#define USBHSH_LAST_PTD_INUSE_ATL_LAST(x)        (((uint32_t)(((uint32_t)(x)) << USBHSH_LAST_PTD_INUSE_ATL_LAST_SHIFT)) & USBHSH_LAST_PTD_INUSE_ATL_LAST_MASK)
#define USBHSH_LAST_PTD_INUSE_ISO_LAST_MASK      (0x1F00U)
#define USBHSH_LAST_PTD_INUSE_ISO_LAST_SHIFT     (8U)
#define USBHSH_LAST_PTD_INUSE_ISO_LAST(x)        (((uint32_t)(((uint32_t)(x)) << USBHSH_LAST_PTD_INUSE_ISO_LAST_SHIFT)) & USBHSH_LAST_PTD_INUSE_ISO_LAST_MASK)
#define USBHSH_LAST_PTD_INUSE_INT_LAST_MASK      (0x1F0000U)
#define USBHSH_LAST_PTD_INUSE_INT_LAST_SHIFT     (16U)
#define USBHSH_LAST_PTD_INUSE_INT_LAST(x)        (((uint32_t)(((uint32_t)(x)) << USBHSH_LAST_PTD_INUSE_INT_LAST_SHIFT)) & USBHSH_LAST_PTD_INUSE_INT_LAST_MASK)

/*! @name UTMIPLUS_ULPI_DEBUG - Register to read/write registers in the attached USB PHY */
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_ADDR_MASK (0xFFU)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_ADDR_SHIFT (0U)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_ADDR(x)   (((uint32_t)(((uint32_t)(x)) << USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_ADDR_SHIFT)) & USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_ADDR_MASK)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_WDATA_MASK (0xFF00U)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_WDATA_SHIFT (8U)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_WDATA(x)  (((uint32_t)(((uint32_t)(x)) << USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_WDATA_SHIFT)) & USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_WDATA_MASK)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_RDATA_MASK (0xFF0000U)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_RDATA_SHIFT (16U)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_RDATA(x)  (((uint32_t)(((uint32_t)(x)) << USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_RDATA_SHIFT)) & USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_RDATA_MASK)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_RW_MASK   (0x1000000U)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_RW_SHIFT  (24U)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_RW(x)     (((uint32_t)(((uint32_t)(x)) << USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_RW_SHIFT)) & USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_RW_MASK)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_ACCESS_MASK (0x2000000U)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_ACCESS_SHIFT (25U)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_ACCESS(x) (((uint32_t)(((uint32_t)(x)) << USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_ACCESS_SHIFT)) & USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_ACCESS_MASK)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_MODE_MASK (0x80000000U)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_MODE_SHIFT (31U)
#define USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_MODE(x)   (((uint32_t)(((uint32_t)(x)) << USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_MODE_SHIFT)) & USBHSH_UTMIPLUS_ULPI_DEBUG_PHY_MODE_MASK)

/*! @name PORTMODE - Controls the port if it is attached to the host block or the device block */
#define USBHSH_PORTMODE_ID0_MASK                 (0x1U)
#define USBHSH_PORTMODE_ID0_SHIFT                (0U)
#define USBHSH_PORTMODE_ID0(x)                   (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTMODE_ID0_SHIFT)) & USBHSH_PORTMODE_ID0_MASK)
#define USBHSH_PORTMODE_ID0_EN_MASK              (0x100U)
#define USBHSH_PORTMODE_ID0_EN_SHIFT             (8U)
#define USBHSH_PORTMODE_ID0_EN(x)                (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTMODE_ID0_EN_SHIFT)) & USBHSH_PORTMODE_ID0_EN_MASK)
#define USBHSH_PORTMODE_DEV_ENABLE_MASK          (0x10000U)
#define USBHSH_PORTMODE_DEV_ENABLE_SHIFT         (16U)
#define USBHSH_PORTMODE_DEV_ENABLE(x)            (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTMODE_DEV_ENABLE_SHIFT)) & USBHSH_PORTMODE_DEV_ENABLE_MASK)
#define USBHSH_PORTMODE_SW_CTRL_PDCOM_MASK       (0x40000U)
#define USBHSH_PORTMODE_SW_CTRL_PDCOM_SHIFT      (18U)
#define USBHSH_PORTMODE_SW_CTRL_PDCOM(x)         (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTMODE_SW_CTRL_PDCOM_SHIFT)) & USBHSH_PORTMODE_SW_CTRL_PDCOM_MASK)
#define USBHSH_PORTMODE_SW_PDCOM_MASK            (0x80000U)
#define USBHSH_PORTMODE_SW_PDCOM_SHIFT           (19U)
#define USBHSH_PORTMODE_SW_PDCOM(x)              (((uint32_t)(((uint32_t)(x)) << USBHSH_PORTMODE_SW_PDCOM_SHIFT)) & USBHSH_PORTMODE_SW_PDCOM_MASK)


/*!
 * @}
 */ /* end of group USBHSH_Register_Masks */


/* USBHSH - Peripheral instance base addresses */
/** Peripheral USBHSH base address */
#define USBHSH_BASE                              (0x400A3000u)
/** Peripheral USBHSH base pointer */
#define USBHSH                                   ((USBHSH_Type *)USBHSH_BASE)
/** Array initializer of USBHSH peripheral base addresses */
#define USBHSH_BASE_ADDRS                        { USBHSH_BASE }
/** Array initializer of USBHSH peripheral base pointers */
#define USBHSH_BASE_PTRS                         { USBHSH }
/** Interrupt vectors for the USBHSH peripheral type */
#define USBHSH_IRQS                              { USB1_IRQn }
#define USBHSH_NEEDCLK_IRQS                      { USB1_NEEDCLK_IRQn }

/*!
 * @}
 */ /* end of group USBHSH_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- UTICK Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UTICK_Peripheral_Access_Layer UTICK Peripheral Access Layer
 * @{
 */

/** UTICK - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< Control register., offset: 0x0 */
  __IO uint32_t STAT;                              /**< Status register., offset: 0x4 */
  __IO uint32_t CFG;                               /**< Capture configuration register., offset: 0x8 */
  __O  uint32_t CAPCLR;                            /**< Capture clear register., offset: 0xC */
  __I  uint32_t CAP[4];                            /**< Capture register ., array offset: 0x10, array step: 0x4 */
} UTICK_Type;

/* ----------------------------------------------------------------------------
   -- UTICK Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UTICK_Register_Masks UTICK Register Masks
 * @{
 */

/*! @name CTRL - Control register. */
#define UTICK_CTRL_DELAYVAL_MASK                 (0x7FFFFFFFU)
#define UTICK_CTRL_DELAYVAL_SHIFT                (0U)
#define UTICK_CTRL_DELAYVAL(x)                   (((uint32_t)(((uint32_t)(x)) << UTICK_CTRL_DELAYVAL_SHIFT)) & UTICK_CTRL_DELAYVAL_MASK)
#define UTICK_CTRL_REPEAT_MASK                   (0x80000000U)
#define UTICK_CTRL_REPEAT_SHIFT                  (31U)
#define UTICK_CTRL_REPEAT(x)                     (((uint32_t)(((uint32_t)(x)) << UTICK_CTRL_REPEAT_SHIFT)) & UTICK_CTRL_REPEAT_MASK)

/*! @name STAT - Status register. */
#define UTICK_STAT_INTR_MASK                     (0x1U)
#define UTICK_STAT_INTR_SHIFT                    (0U)
#define UTICK_STAT_INTR(x)                       (((uint32_t)(((uint32_t)(x)) << UTICK_STAT_INTR_SHIFT)) & UTICK_STAT_INTR_MASK)
#define UTICK_STAT_ACTIVE_MASK                   (0x2U)
#define UTICK_STAT_ACTIVE_SHIFT                  (1U)
#define UTICK_STAT_ACTIVE(x)                     (((uint32_t)(((uint32_t)(x)) << UTICK_STAT_ACTIVE_SHIFT)) & UTICK_STAT_ACTIVE_MASK)

/*! @name CFG - Capture configuration register. */
#define UTICK_CFG_CAPEN0_MASK                    (0x1U)
#define UTICK_CFG_CAPEN0_SHIFT                   (0U)
#define UTICK_CFG_CAPEN0(x)                      (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPEN0_SHIFT)) & UTICK_CFG_CAPEN0_MASK)
#define UTICK_CFG_CAPEN1_MASK                    (0x2U)
#define UTICK_CFG_CAPEN1_SHIFT                   (1U)
#define UTICK_CFG_CAPEN1(x)                      (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPEN1_SHIFT)) & UTICK_CFG_CAPEN1_MASK)
#define UTICK_CFG_CAPEN2_MASK                    (0x4U)
#define UTICK_CFG_CAPEN2_SHIFT                   (2U)
#define UTICK_CFG_CAPEN2(x)                      (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPEN2_SHIFT)) & UTICK_CFG_CAPEN2_MASK)
#define UTICK_CFG_CAPEN3_MASK                    (0x8U)
#define UTICK_CFG_CAPEN3_SHIFT                   (3U)
#define UTICK_CFG_CAPEN3(x)                      (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPEN3_SHIFT)) & UTICK_CFG_CAPEN3_MASK)
#define UTICK_CFG_CAPPOL0_MASK                   (0x100U)
#define UTICK_CFG_CAPPOL0_SHIFT                  (8U)
#define UTICK_CFG_CAPPOL0(x)                     (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPPOL0_SHIFT)) & UTICK_CFG_CAPPOL0_MASK)
#define UTICK_CFG_CAPPOL1_MASK                   (0x200U)
#define UTICK_CFG_CAPPOL1_SHIFT                  (9U)
#define UTICK_CFG_CAPPOL1(x)                     (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPPOL1_SHIFT)) & UTICK_CFG_CAPPOL1_MASK)
#define UTICK_CFG_CAPPOL2_MASK                   (0x400U)
#define UTICK_CFG_CAPPOL2_SHIFT                  (10U)
#define UTICK_CFG_CAPPOL2(x)                     (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPPOL2_SHIFT)) & UTICK_CFG_CAPPOL2_MASK)
#define UTICK_CFG_CAPPOL3_MASK                   (0x800U)
#define UTICK_CFG_CAPPOL3_SHIFT                  (11U)
#define UTICK_CFG_CAPPOL3(x)                     (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPPOL3_SHIFT)) & UTICK_CFG_CAPPOL3_MASK)

/*! @name CAPCLR - Capture clear register. */
#define UTICK_CAPCLR_CAPCLR0_MASK                (0x1U)
#define UTICK_CAPCLR_CAPCLR0_SHIFT               (0U)
#define UTICK_CAPCLR_CAPCLR0(x)                  (((uint32_t)(((uint32_t)(x)) << UTICK_CAPCLR_CAPCLR0_SHIFT)) & UTICK_CAPCLR_CAPCLR0_MASK)
#define UTICK_CAPCLR_CAPCLR1_MASK                (0x2U)
#define UTICK_CAPCLR_CAPCLR1_SHIFT               (1U)
#define UTICK_CAPCLR_CAPCLR1(x)                  (((uint32_t)(((uint32_t)(x)) << UTICK_CAPCLR_CAPCLR1_SHIFT)) & UTICK_CAPCLR_CAPCLR1_MASK)
#define UTICK_CAPCLR_CAPCLR2_MASK                (0x4U)
#define UTICK_CAPCLR_CAPCLR2_SHIFT               (2U)
#define UTICK_CAPCLR_CAPCLR2(x)                  (((uint32_t)(((uint32_t)(x)) << UTICK_CAPCLR_CAPCLR2_SHIFT)) & UTICK_CAPCLR_CAPCLR2_MASK)
#define UTICK_CAPCLR_CAPCLR3_MASK                (0x8U)
#define UTICK_CAPCLR_CAPCLR3_SHIFT               (3U)
#define UTICK_CAPCLR_CAPCLR3(x)                  (((uint32_t)(((uint32_t)(x)) << UTICK_CAPCLR_CAPCLR3_SHIFT)) & UTICK_CAPCLR_CAPCLR3_MASK)

/*! @name CAP - Capture register . */
#define UTICK_CAP_CAP_VALUE_MASK                 (0x7FFFFFFFU)
#define UTICK_CAP_CAP_VALUE_SHIFT                (0U)
#define UTICK_CAP_CAP_VALUE(x)                   (((uint32_t)(((uint32_t)(x)) << UTICK_CAP_CAP_VALUE_SHIFT)) & UTICK_CAP_CAP_VALUE_MASK)
#define UTICK_CAP_VALID_MASK                     (0x80000000U)
#define UTICK_CAP_VALID_SHIFT                    (31U)
#define UTICK_CAP_VALID(x)                       (((uint32_t)(((uint32_t)(x)) << UTICK_CAP_VALID_SHIFT)) & UTICK_CAP_VALID_MASK)

/* The count of UTICK_CAP */
#define UTICK_CAP_COUNT                          (4U)


/*!
 * @}
 */ /* end of group UTICK_Register_Masks */


/* UTICK - Peripheral instance base addresses */
/** Peripheral UTICK0 base address */
#define UTICK0_BASE                              (0x4000E000u)
/** Peripheral UTICK0 base pointer */
#define UTICK0                                   ((UTICK_Type *)UTICK0_BASE)
/** Array initializer of UTICK peripheral base addresses */
#define UTICK_BASE_ADDRS                         { UTICK0_BASE }
/** Array initializer of UTICK peripheral base pointers */
#define UTICK_BASE_PTRS                          { UTICK0 }
/** Interrupt vectors for the UTICK peripheral type */
#define UTICK_IRQS                               { UTICK0_IRQn }

/*!
 * @}
 */ /* end of group UTICK_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- WWDT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WWDT_Peripheral_Access_Layer WWDT Peripheral Access Layer
 * @{
 */

/** WWDT - Register Layout Typedef */
typedef struct {
  __IO uint32_t MOD;                               /**< Watchdog mode register. This register contains the basic mode and status of the Watchdog Timer., offset: 0x0 */
  __IO uint32_t TC;                                /**< Watchdog timer constant register. This 24-bit register determines the time-out value., offset: 0x4 */
  __O  uint32_t FEED;                              /**< Watchdog feed sequence register. Writing 0xAA followed by 0x55 to this register reloads the Watchdog timer with the value contained in TC., offset: 0x8 */
  __I  uint32_t TV;                                /**< Watchdog timer value register. This 24-bit register reads out the current value of the Watchdog timer., offset: 0xC */
       uint8_t RESERVED_0[4];
  __IO uint32_t WARNINT;                           /**< Watchdog Warning Interrupt compare value., offset: 0x14 */
  __IO uint32_t WINDOW;                            /**< Watchdog Window compare value., offset: 0x18 */
} WWDT_Type;

/* ----------------------------------------------------------------------------
   -- WWDT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WWDT_Register_Masks WWDT Register Masks
 * @{
 */

/*! @name MOD - Watchdog mode register. This register contains the basic mode and status of the Watchdog Timer. */
#define WWDT_MOD_WDEN_MASK                       (0x1U)
#define WWDT_MOD_WDEN_SHIFT                      (0U)
#define WWDT_MOD_WDEN(x)                         (((uint32_t)(((uint32_t)(x)) << WWDT_MOD_WDEN_SHIFT)) & WWDT_MOD_WDEN_MASK)
#define WWDT_MOD_WDRESET_MASK                    (0x2U)
#define WWDT_MOD_WDRESET_SHIFT                   (1U)
#define WWDT_MOD_WDRESET(x)                      (((uint32_t)(((uint32_t)(x)) << WWDT_MOD_WDRESET_SHIFT)) & WWDT_MOD_WDRESET_MASK)
#define WWDT_MOD_WDTOF_MASK                      (0x4U)
#define WWDT_MOD_WDTOF_SHIFT                     (2U)
#define WWDT_MOD_WDTOF(x)                        (((uint32_t)(((uint32_t)(x)) << WWDT_MOD_WDTOF_SHIFT)) & WWDT_MOD_WDTOF_MASK)
#define WWDT_MOD_WDINT_MASK                      (0x8U)
#define WWDT_MOD_WDINT_SHIFT                     (3U)
#define WWDT_MOD_WDINT(x)                        (((uint32_t)(((uint32_t)(x)) << WWDT_MOD_WDINT_SHIFT)) & WWDT_MOD_WDINT_MASK)
#define WWDT_MOD_WDPROTECT_MASK                  (0x10U)
#define WWDT_MOD_WDPROTECT_SHIFT                 (4U)
#define WWDT_MOD_WDPROTECT(x)                    (((uint32_t)(((uint32_t)(x)) << WWDT_MOD_WDPROTECT_SHIFT)) & WWDT_MOD_WDPROTECT_MASK)
#define WWDT_MOD_LOCK_MASK                       (0x20U)
#define WWDT_MOD_LOCK_SHIFT                      (5U)
#define WWDT_MOD_LOCK(x)                         (((uint32_t)(((uint32_t)(x)) << WWDT_MOD_LOCK_SHIFT)) & WWDT_MOD_LOCK_MASK)

/*! @name TC - Watchdog timer constant register. This 24-bit register determines the time-out value. */
#define WWDT_TC_COUNT_MASK                       (0xFFFFFFU)
#define WWDT_TC_COUNT_SHIFT                      (0U)
#define WWDT_TC_COUNT(x)                         (((uint32_t)(((uint32_t)(x)) << WWDT_TC_COUNT_SHIFT)) & WWDT_TC_COUNT_MASK)

/*! @name FEED - Watchdog feed sequence register. Writing 0xAA followed by 0x55 to this register reloads the Watchdog timer with the value contained in TC. */
#define WWDT_FEED_FEED_MASK                      (0xFFU)
#define WWDT_FEED_FEED_SHIFT                     (0U)
#define WWDT_FEED_FEED(x)                        (((uint32_t)(((uint32_t)(x)) << WWDT_FEED_FEED_SHIFT)) & WWDT_FEED_FEED_MASK)

/*! @name TV - Watchdog timer value register. This 24-bit register reads out the current value of the Watchdog timer. */
#define WWDT_TV_COUNT_MASK                       (0xFFFFFFU)
#define WWDT_TV_COUNT_SHIFT                      (0U)
#define WWDT_TV_COUNT(x)                         (((uint32_t)(((uint32_t)(x)) << WWDT_TV_COUNT_SHIFT)) & WWDT_TV_COUNT_MASK)

/*! @name WARNINT - Watchdog Warning Interrupt compare value. */
#define WWDT_WARNINT_WARNINT_MASK                (0x3FFU)
#define WWDT_WARNINT_WARNINT_SHIFT               (0U)
#define WWDT_WARNINT_WARNINT(x)                  (((uint32_t)(((uint32_t)(x)) << WWDT_WARNINT_WARNINT_SHIFT)) & WWDT_WARNINT_WARNINT_MASK)

/*! @name WINDOW - Watchdog Window compare value. */
#define WWDT_WINDOW_WINDOW_MASK                  (0xFFFFFFU)
#define WWDT_WINDOW_WINDOW_SHIFT                 (0U)
#define WWDT_WINDOW_WINDOW(x)                    (((uint32_t)(((uint32_t)(x)) << WWDT_WINDOW_WINDOW_SHIFT)) & WWDT_WINDOW_WINDOW_MASK)


/*!
 * @}
 */ /* end of group WWDT_Register_Masks */


/* WWDT - Peripheral instance base addresses */
/** Peripheral WWDT base address */
#define WWDT_BASE                                (0x4000C000u)
/** Peripheral WWDT base pointer */
#define WWDT                                     ((WWDT_Type *)WWDT_BASE)
/** Array initializer of WWDT peripheral base addresses */
#define WWDT_BASE_ADDRS                          { WWDT_BASE }
/** Array initializer of WWDT peripheral base pointers */
#define WWDT_BASE_PTRS                           { WWDT }
/** Interrupt vectors for the WWDT peripheral type */
#define WWDT_IRQS                                { WDT_BOD_IRQn }

/*!
 * @}
 */ /* end of group WWDT_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
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

/** EMC CS base address */
#define EMC_CS0_BASE                                (0x80000000u)
#define EMC_CS1_BASE                                (0x90000000u)
#define EMC_CS2_BASE                                (0x98000000u)
#define EMC_CS3_BASE                                (0x9C000000u)
#define EMC_DYCS0_BASE                              (0xA0000000u)
#define EMC_DYCS1_BASE                              (0xB0000000u)
#define EMC_DYCS2_BASE                              (0xC0000000u)
#define EMC_DYCS3_BASE                              (0xD0000000u)
#define EMC_CS_ADDRESS                              {EMC_CS0_BASE, EMC_CS1_BASE, EMC_CS2_BASE, EMC_CS3_BASE}
#define EMC_DYCS_ADDRESS                            {EMC_DYCS0_BASE, EMC_DYCS1_BASE, EMC_DYCS2_BASE, EMC_DYCS3_BASE}

/** OTP API */
typedef struct {
  uint32_t (*otpInit)(void);                                    /** Initializes OTP controller */
  uint32_t (*otpEnableBankWriteMask)(uint32_t bankMask);        /** Unlock one or more OTP banks for write access */
  uint32_t (*otpDisableBankWriteMask)(uint32_t bankMask);       /** Lock one or more OTP banks for write access */
  uint32_t (*otpEnableBankWriteLock)(uint32_t bankIndex, uint32_t regEnableMask, uint32_t regDisableMask,
                                          uint32_t lockWrite);  /** Locks or unlocks write access to a register of an OTP bank and the write lock */
  uint32_t (*otpEnableBankReadLock)(uint32_t bankIndex, uint32_t regEnableMask, uint32_t regDisableMask,
                                         uint32_t lockWrite);   /** Locks or unlocks read access to a register of an OTP bank and the write lock */
  uint32_t (*otpProgramReg)(uint32_t bankIndex, uint32_t regIndex, uint32_t value);  /** Program a single register in an OTP bank */
  uint32_t RESERVED_0[5];
  uint32_t (*rngRead)(void);                                    /** Returns 32-bit number from hardware random number generator */
  uint32_t (*otpGetDriverVersion)(void);                        /** Returns the version of the OTP driver in ROM */
} OTP_API_Type;

/** ROM API */
typedef struct {
  __I uint32_t usbdApiBase;                      /** USB API Base */
      uint32_t RESERVED_0[13];
  __I OTP_API_Type *otpApiBase;                  /** OTP API Base */
  __I uint32_t aesApiBase;                       /** AES API Base */
  __I uint32_t secureApiBase;                    /** Secure API Base */
} ROM_API_Type;

/** ROM API base address */
#define ROM_API_BASE                             (0x03000200u)
/** ROM API base pointer */
#define ROM_API                                  (*(ROM_API_Type**) ROM_API_BASE)
/** OTP API base pointer */
#define OTP_API                                  (ROM_API->otpApiBase)

/*!
 * @}
 */ /* end of group SDK_Compatibility_Symbols */


#endif  /* _LPC54608_H_ */

