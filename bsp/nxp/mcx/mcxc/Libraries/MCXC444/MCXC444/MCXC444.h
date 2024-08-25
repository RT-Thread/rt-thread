/*
** ###################################################################
**     Processors:          MCXC444VLH
**                          MCXC444VMP
**
**     Compilers:           Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    MCXC444RM, Rev.1, Mar 2024
**     Version:             rev. 1.0, 2024-03-11
**     Build:               b240401
**
**     Abstract:
**         CMSIS Peripheral Access Layer for MCXC444
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2024-03-11)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file MCXC444.h
 * @version 1.0
 * @date 2024-03-11
 * @brief CMSIS Peripheral Access Layer for MCXC444
 *
 * CMSIS Peripheral Access Layer for MCXC444
 */

#if !defined(MCXC444_H_)
#define MCXC444_H_                               /**< Symbol preventing repeated inclusion */

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0100U
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
#define NUMBER_OF_INT_VECTORS 48                 /**< Number of interrupts in the Vector table */

typedef enum IRQn {
  /* Auxiliary constants */
  NotAvail_IRQn                = -128,             /**< Not available device specific interrupt */

  /* Core interrupts */
  NonMaskableInt_IRQn          = -14,              /**< Non Maskable Interrupt */
  HardFault_IRQn               = -13,              /**< Cortex-M0 SV Hard Fault Interrupt */
  SVCall_IRQn                  = -5,               /**< Cortex-M0 SV Call Interrupt */
  PendSV_IRQn                  = -2,               /**< Cortex-M0 Pend SV Interrupt */
  SysTick_IRQn                 = -1,               /**< Cortex-M0 System Tick Interrupt */

  /* Device specific interrupts */
  DMA0_IRQn                    = 0,                /**< DMA channel 0 transfer complete */
  DMA1_IRQn                    = 1,                /**< DMA channel 1 transfer complete */
  DMA2_IRQn                    = 2,                /**< DMA channel 2 transfer complete */
  DMA3_IRQn                    = 3,                /**< DMA channel 3 transfer complete */
  Reserved20_IRQn              = 4,                /**< Reserved interrupt */
  FTFA_IRQn                    = 5,                /**< Command complete and read collision */
  PMC_IRQn                     = 6,                /**< Low-voltage detect, low-voltage warning */
  LLWU_IRQn                    = 7,                /**< Low leakage wakeup */
  I2C0_IRQn                    = 8,                /**< I2C0 interrupt */
  I2C1_IRQn                    = 9,                /**< I2C1 interrupt */
  SPI0_IRQn                    = 10,               /**< SPI0 single interrupt vector for all sources */
  SPI1_IRQn                    = 11,               /**< SPI1 single interrupt vector for all sources */
  LPUART0_IRQn                 = 12,               /**< LPUART0 status and error */
  LPUART1_IRQn                 = 13,               /**< LPUART1 status and error */
  UART2_FLEXIO_IRQn            = 14,               /**< UART2 or FLEXIO */
  ADC0_IRQn                    = 15,               /**< ADC0 interrupt */
  CMP0_IRQn                    = 16,               /**< CMP0 interrupt */
  TPM0_IRQn                    = 17,               /**< TPM0 single interrupt vector for all sources */
  TPM1_IRQn                    = 18,               /**< TPM1 single interrupt vector for all sources */
  TPM2_IRQn                    = 19,               /**< TPM2 single interrupt vector for all sources */
  RTC_IRQn                     = 20,               /**< RTC alarm */
  RTC_Seconds_IRQn             = 21,               /**< RTC seconds */
  PIT_IRQn                     = 22,               /**< PIT interrupt */
  I2S0_IRQn                    = 23,               /**< I2S0 interrupt */
  USB0_IRQn                    = 24,               /**< USB0 interrupt */
  DAC0_IRQn                    = 25,               /**< DAC0 interrupt */
  Reserved42_IRQn              = 26,               /**< Reserved interrupt */
  Reserved43_IRQn              = 27,               /**< Reserved interrupt */
  LPTMR0_IRQn                  = 28,               /**< LPTMR0 interrupt */
  LCD_IRQn                     = 29,               /**< LCD interrupt */
  PORTA_IRQn                   = 30,               /**< PORTA Pin detect */
  PORTC_PORTD_IRQn             = 31                /**< Single interrupt vector for PORTC; PORTD Pin detect */
} IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Cortex M0 Core Configuration
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Cortex_Core_Configuration Cortex M0 Core Configuration
 * @{
 */

#define __CM0PLUS_REV                  0x0000    /**< Core revision r0p0 */
#define __MPU_PRESENT                  0         /**< Defines if an MPU is present or not */
#define __VTOR_PRESENT                 1         /**< Defines if VTOR is present or not */
#define __NVIC_PRIO_BITS               2         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig         0         /**< Vendor specific implementation of SysTickConfig is defined */

#include "core_cm0plus.h"              /* Core Peripheral Access Layer */
#include "system_MCXC444.h"            /* Device specific configuration file */

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
    kDmaRequestMux0Disable          = 0|0x100U,    /**< DMAMUX TriggerDisabled */
    kDmaRequestMux0Reserved1        = 1|0x100U,    /**< Reserved1 */
    kDmaRequestMux0LPUART0Rx        = 2|0x100U,    /**< LPUART0 Receive */
    kDmaRequestMux0LPUART0Tx        = 3|0x100U,    /**< LPUART0 Transmit */
    kDmaRequestMux0LPUART1Rx        = 4|0x100U,    /**< LPUART1 Receive */
    kDmaRequestMux0LPUART1Tx        = 5|0x100U,    /**< LPUART1 Transmit */
    kDmaRequestMux0UART2Rx          = 6|0x100U,    /**< UART2 Receive */
    kDmaRequestMux0UART2Tx          = 7|0x100U,    /**< UART2 Transmit */
    kDmaRequestMux0Reserved8        = 8|0x100U,    /**< Reserved8 */
    kDmaRequestMux0Reserved9        = 9|0x100U,    /**< Reserved9 */
    kDmaRequestMux0FlexIOChannel0   = 10|0x100U,   /**< FlexIO Channel 0 */
    kDmaRequestMux0FlexIOChannel1   = 11|0x100U,   /**< FlexIO Channel 1 */
    kDmaRequestMux0FlexIOChannel2   = 12|0x100U,   /**< FlexIO Channel 2 */
    kDmaRequestMux0FlexIOChannel3   = 13|0x100U,   /**< FlexIO Channel 3 */
    kDmaRequestMux0I2S0Rx           = 14|0x100U,   /**< I2S0 Receive */
    kDmaRequestMux0I2S0Tx           = 15|0x100U,   /**< I2S0 Transmit */
    kDmaRequestMux0SPI0Rx           = 16|0x100U,   /**< SPI0 Receive */
    kDmaRequestMux0SPI0Tx           = 17|0x100U,   /**< SPI0 Transmit */
    kDmaRequestMux0SPI1Rx           = 18|0x100U,   /**< SPI1 Receive */
    kDmaRequestMux0SPI1Tx           = 19|0x100U,   /**< SPI1 Transmit */
    kDmaRequestMux0Reserved20       = 20|0x100U,   /**< Reserved20 */
    kDmaRequestMux0Reserved21       = 21|0x100U,   /**< Reserved21 */
    kDmaRequestMux0I2C0             = 22|0x100U,   /**< I2C0 */
    kDmaRequestMux0I2C1             = 23|0x100U,   /**< I2C1 */
    kDmaRequestMux0TPM0Channel0     = 24|0x100U,   /**< TPM0 channel 0 */
    kDmaRequestMux0TPM0Channel1     = 25|0x100U,   /**< TPM0 channel 1 */
    kDmaRequestMux0TPM0Channel2     = 26|0x100U,   /**< TPM0 channel 2 */
    kDmaRequestMux0TPM0Channel3     = 27|0x100U,   /**< TPM0 channel 3 */
    kDmaRequestMux0TPM0Channel4     = 28|0x100U,   /**< TPM0 channel 4 */
    kDmaRequestMux0TPM0Channel5     = 29|0x100U,   /**< TPM0 channel 5 */
    kDmaRequestMux0Reserved30       = 30|0x100U,   /**< Reserved30 */
    kDmaRequestMux0Reserved31       = 31|0x100U,   /**< Reserved31 */
    kDmaRequestMux0TPM1Channel0     = 32|0x100U,   /**< TPM1 channel 0 */
    kDmaRequestMux0TPM1Channel1     = 33|0x100U,   /**< TPM1 channel 1 */
    kDmaRequestMux0TPM2Channel0     = 34|0x100U,   /**< TPM2 channel 0 */
    kDmaRequestMux0TPM2Channel1     = 35|0x100U,   /**< TPM2 channel 1 */
    kDmaRequestMux0Reserved36       = 36|0x100U,   /**< Reserved36 */
    kDmaRequestMux0Reserved37       = 37|0x100U,   /**< Reserved37 */
    kDmaRequestMux0Reserved38       = 38|0x100U,   /**< Reserved38 */
    kDmaRequestMux0Reserved39       = 39|0x100U,   /**< Reserved39 */
    kDmaRequestMux0ADC0             = 40|0x100U,   /**< ADC0 */
    kDmaRequestMux0Reserved41       = 41|0x100U,   /**< Reserved41 */
    kDmaRequestMux0CMP0             = 42|0x100U,   /**< CMP0 */
    kDmaRequestMux0Reserved43       = 43|0x100U,   /**< Reserved43 */
    kDmaRequestMux0Reserved44       = 44|0x100U,   /**< Reserved44 */
    kDmaRequestMux0DAC0             = 45|0x100U,   /**< DAC0 */
    kDmaRequestMux0Reserved46       = 46|0x100U,   /**< Reserved46 */
    kDmaRequestMux0Reserved47       = 47|0x100U,   /**< Reserved47 */
    kDmaRequestMux0Reserved48       = 48|0x100U,   /**< Reserved48 */
    kDmaRequestMux0PortA            = 49|0x100U,   /**< GPIO Port A */
    kDmaRequestMux0Reserved50       = 50|0x100U,   /**< Reserved50 */
    kDmaRequestMux0PortC            = 51|0x100U,   /**< GPIO Port C */
    kDmaRequestMux0PortD            = 52|0x100U,   /**< GPIO Port D */
    kDmaRequestMux0Reserved53       = 53|0x100U,   /**< Reserved53 */
    kDmaRequestMux0TPM0Overflow     = 54|0x100U,   /**< TPM0 overflow */
    kDmaRequestMux0TPM1Overflow     = 55|0x100U,   /**< TPM1 overflow */
    kDmaRequestMux0TPM2Overflow     = 56|0x100U,   /**< TPM2 overflow */
    kDmaRequestMux0Reserved57       = 57|0x100U,   /**< Reserved57 */
    kDmaRequestMux0Reserved58       = 58|0x100U,   /**< Reserved58 */
    kDmaRequestMux0Reserved59       = 59|0x100U,   /**< Reserved59 */
    kDmaRequestMux0AlwaysOn60       = 60|0x100U,   /**< DMAMUX Always Enabled slot */
    kDmaRequestMux0AlwaysOn61       = 61|0x100U,   /**< DMAMUX Always Enabled slot */
    kDmaRequestMux0AlwaysOn62       = 62|0x100U,   /**< DMAMUX Always Enabled slot */
    kDmaRequestMux0AlwaysOn63       = 63|0x100U,   /**< DMAMUX Always Enabled slot */
} dma_request_source_t;

/* @} */


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
   -- ADC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Peripheral_Access_Layer ADC Peripheral Access Layer
 * @{
 */

/** ADC - Register Layout Typedef */
typedef struct {
  __IO uint32_t SC1[2];                            /**< ADC Status and Control Registers 1, array offset: 0x0, array step: 0x4 */
  __IO uint32_t CFG1;                              /**< ADC Configuration Register 1, offset: 0x8 */
  __IO uint32_t CFG2;                              /**< ADC Configuration Register 2, offset: 0xC */
  __I  uint32_t R[2];                              /**< ADC Data Result Register, array offset: 0x10, array step: 0x4 */
  __IO uint32_t CV1;                               /**< Compare Value Registers, offset: 0x18 */
  __IO uint32_t CV2;                               /**< Compare Value Registers, offset: 0x1C */
  __IO uint32_t SC2;                               /**< Status and Control Register 2, offset: 0x20 */
  __IO uint32_t SC3;                               /**< Status and Control Register 3, offset: 0x24 */
  __IO uint32_t OFS;                               /**< ADC Offset Correction Register, offset: 0x28 */
  __IO uint32_t PG;                                /**< ADC Plus-Side Gain Register, offset: 0x2C */
  __IO uint32_t MG;                                /**< ADC Minus-Side Gain Register, offset: 0x30 */
  __IO uint32_t CLPD;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x34 */
  __IO uint32_t CLPS;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x38 */
  __IO uint32_t CLP4;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x3C */
  __IO uint32_t CLP3;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x40 */
  __IO uint32_t CLP2;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x44 */
  __IO uint32_t CLP1;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x48 */
  __IO uint32_t CLP0;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x4C */
       uint8_t RESERVED_0[4];
  __IO uint32_t CLMD;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x54 */
  __IO uint32_t CLMS;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x58 */
  __IO uint32_t CLM4;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x5C */
  __IO uint32_t CLM3;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x60 */
  __IO uint32_t CLM2;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x64 */
  __IO uint32_t CLM1;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x68 */
  __IO uint32_t CLM0;                              /**< ADC Minus-Side General Calibration Value Register, offset: 0x6C */
} ADC_Type;

/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */

/*! @name SC1 - ADC Status and Control Registers 1 */
/*! @{ */

#define ADC_SC1_ADCH_MASK                        (0x1FU)
#define ADC_SC1_ADCH_SHIFT                       (0U)
/*! ADCH - Input channel select
 *  0b00000..When DIFF=0, DADP0 is selected as input; when DIFF=1, DAD0 is selected as input.
 *  0b00001..When DIFF=0, DADP1 is selected as input; when DIFF=1, DAD1 is selected as input.
 *  0b00010..When DIFF=0, DADP2 is selected as input; when DIFF=1, DAD2 is selected as input.
 *  0b00011..When DIFF=0, DADP3 is selected as input; when DIFF=1, DAD3 is selected as input.
 *  0b00100..When DIFF=0, AD4 is selected as input; when DIFF=1, it is reserved.
 *  0b00101..When DIFF=0, AD5 is selected as input; when DIFF=1, it is reserved.
 *  0b00110..When DIFF=0, AD6 is selected as input; when DIFF=1, it is reserved.
 *  0b00111..When DIFF=0, AD7 is selected as input; when DIFF=1, it is reserved.
 *  0b01000..When DIFF=0, AD8 is selected as input; when DIFF=1, it is reserved.
 *  0b01001..When DIFF=0, AD9 is selected as input; when DIFF=1, it is reserved.
 *  0b01010..When DIFF=0, AD10 is selected as input; when DIFF=1, it is reserved.
 *  0b01011..When DIFF=0, AD11 is selected as input; when DIFF=1, it is reserved.
 *  0b01100..When DIFF=0, AD12 is selected as input; when DIFF=1, it is reserved.
 *  0b01101..When DIFF=0, AD13 is selected as input; when DIFF=1, it is reserved.
 *  0b01110..When DIFF=0, AD14 is selected as input; when DIFF=1, it is reserved.
 *  0b01111..When DIFF=0, AD15 is selected as input; when DIFF=1, it is reserved.
 *  0b10000..When DIFF=0, AD16 is selected as input; when DIFF=1, it is reserved.
 *  0b10001..When DIFF=0, AD17 is selected as input; when DIFF=1, it is reserved.
 *  0b10010..When DIFF=0, AD18 is selected as input; when DIFF=1, it is reserved.
 *  0b10011..When DIFF=0, AD19 is selected as input; when DIFF=1, it is reserved.
 *  0b10100..When DIFF=0, AD20 is selected as input; when DIFF=1, it is reserved.
 *  0b10101..When DIFF=0, AD21 is selected as input; when DIFF=1, it is reserved.
 *  0b10110..When DIFF=0, AD22 is selected as input; when DIFF=1, it is reserved.
 *  0b10111..When DIFF=0, AD23 is selected as input; when DIFF=1, it is reserved.
 *  0b11000..Reserved.
 *  0b11001..Reserved.
 *  0b11010..When DIFF=0, Temp Sensor (single-ended) is selected as input; when DIFF=1, Temp Sensor (differential) is selected as input.
 *  0b11011..When DIFF=0, Bandgap (single-ended) is selected as input; when DIFF=1, Bandgap (differential) is selected as input.
 *  0b11100..Reserved.
 *  0b11101..When DIFF=0,VREFSH is selected as input; when DIFF=1, -VREFSH (differential) is selected as input.
 *           Voltage reference selected is determined by SC2[REFSEL].
 *  0b11110..When DIFF=0,VREFSL is selected as input; when DIFF=1, it is reserved. Voltage reference selected is determined by SC2[REFSEL].
 *  0b11111..Module is disabled.
 */
#define ADC_SC1_ADCH(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC1_ADCH_SHIFT)) & ADC_SC1_ADCH_MASK)

#define ADC_SC1_DIFF_MASK                        (0x20U)
#define ADC_SC1_DIFF_SHIFT                       (5U)
/*! DIFF - Differential Mode Enable
 *  0b0..Single-ended conversions and input channels are selected.
 *  0b1..Differential conversions and input channels are selected.
 */
#define ADC_SC1_DIFF(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC1_DIFF_SHIFT)) & ADC_SC1_DIFF_MASK)

#define ADC_SC1_AIEN_MASK                        (0x40U)
#define ADC_SC1_AIEN_SHIFT                       (6U)
/*! AIEN - Interrupt Enable
 *  0b0..Conversion complete interrupt is disabled.
 *  0b1..Conversion complete interrupt is enabled.
 */
#define ADC_SC1_AIEN(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC1_AIEN_SHIFT)) & ADC_SC1_AIEN_MASK)

#define ADC_SC1_COCO_MASK                        (0x80U)
#define ADC_SC1_COCO_SHIFT                       (7U)
/*! COCO - Conversion Complete Flag
 *  0b0..Conversion is not completed.
 *  0b1..Conversion is completed.
 */
#define ADC_SC1_COCO(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC1_COCO_SHIFT)) & ADC_SC1_COCO_MASK)
/*! @} */

/* The count of ADC_SC1 */
#define ADC_SC1_COUNT                            (2U)

/*! @name CFG1 - ADC Configuration Register 1 */
/*! @{ */

#define ADC_CFG1_ADICLK_MASK                     (0x3U)
#define ADC_CFG1_ADICLK_SHIFT                    (0U)
/*! ADICLK - Input Clock Select
 *  0b00..Bus clock
 *  0b01..Bus clock divided by 2(BUSCLK/DIV2)
 *  0b10..Alternate clock (ALTCLK)
 *  0b11..Asynchronous clock (ADACK)
 */
#define ADC_CFG1_ADICLK(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADICLK_SHIFT)) & ADC_CFG1_ADICLK_MASK)

#define ADC_CFG1_MODE_MASK                       (0xCU)
#define ADC_CFG1_MODE_SHIFT                      (2U)
/*! MODE - Conversion mode selection
 *  0b00..When DIFF=0:It is single-ended 8-bit conversion; when DIFF=1, it is differential 9-bit conversion with 2's complement output.
 *  0b01..When DIFF=0:It is single-ended 12-bit conversion ; when DIFF=1, it is differential 13-bit conversion with 2's complement output.
 *  0b10..When DIFF=0:It is single-ended 10-bit conversion. ; when DIFF=1, it is differential 11-bit conversion with 2's complement output
 *  0b11..When DIFF=0:It is single-ended 16-bit conversion..; when DIFF=1, it is differential 16-bit conversion with 2's complement output
 */
#define ADC_CFG1_MODE(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_MODE_SHIFT)) & ADC_CFG1_MODE_MASK)

#define ADC_CFG1_ADLSMP_MASK                     (0x10U)
#define ADC_CFG1_ADLSMP_SHIFT                    (4U)
/*! ADLSMP - Sample Time Configuration
 *  0b0..Short sample time.
 *  0b1..Long sample time.
 */
#define ADC_CFG1_ADLSMP(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADLSMP_SHIFT)) & ADC_CFG1_ADLSMP_MASK)

#define ADC_CFG1_ADIV_MASK                       (0x60U)
#define ADC_CFG1_ADIV_SHIFT                      (5U)
/*! ADIV - Clock Divide Select
 *  0b00..The divide ratio is 1 and the clock rate is input clock.
 *  0b01..The divide ratio is 2 and the clock rate is (input clock)/2.
 *  0b10..The divide ratio is 4 and the clock rate is (input clock)/4.
 *  0b11..The divide ratio is 8 and the clock rate is (input clock)/8.
 */
#define ADC_CFG1_ADIV(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADIV_SHIFT)) & ADC_CFG1_ADIV_MASK)

#define ADC_CFG1_ADLPC_MASK                      (0x80U)
#define ADC_CFG1_ADLPC_SHIFT                     (7U)
/*! ADLPC - Low-Power Configuration
 *  0b0..Normal power configuration.
 *  0b1..Low-power configuration. The power is reduced at the expense of maximum clock speed.
 */
#define ADC_CFG1_ADLPC(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADLPC_SHIFT)) & ADC_CFG1_ADLPC_MASK)
/*! @} */

/*! @name CFG2 - ADC Configuration Register 2 */
/*! @{ */

#define ADC_CFG2_ADLSTS_MASK                     (0x3U)
#define ADC_CFG2_ADLSTS_SHIFT                    (0U)
/*! ADLSTS - Long Sample Time Select
 *  0b00..Default longest sample time; 20 extra ADCK cycles; 24 ADCK cycles total.
 *  0b01..12 extra ADCK cycles; 16 ADCK cycles total sample time.
 *  0b10..6 extra ADCK cycles; 10 ADCK cycles total sample time.
 *  0b11..2 extra ADCK cycles; 6 ADCK cycles total sample time.
 */
#define ADC_CFG2_ADLSTS(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_ADLSTS_SHIFT)) & ADC_CFG2_ADLSTS_MASK)

#define ADC_CFG2_ADHSC_MASK                      (0x4U)
#define ADC_CFG2_ADHSC_SHIFT                     (2U)
/*! ADHSC - High-Speed Configuration
 *  0b0..Normal conversion sequence selected.
 *  0b1..High-speed conversion sequence selected with 2 additional ADCK cycles to total conversion time.
 */
#define ADC_CFG2_ADHSC(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_ADHSC_SHIFT)) & ADC_CFG2_ADHSC_MASK)

#define ADC_CFG2_ADACKEN_MASK                    (0x8U)
#define ADC_CFG2_ADACKEN_SHIFT                   (3U)
/*! ADACKEN - Asynchronous Clock Output Enable
 *  0b0..Asynchronous clock output disabled; Asynchronous clock is enabled only if selected by ADICLK and a conversion is active.
 *  0b1..Asynchronous clock and clock output is enabled regardless of the state of the ADC.
 */
#define ADC_CFG2_ADACKEN(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_ADACKEN_SHIFT)) & ADC_CFG2_ADACKEN_MASK)

#define ADC_CFG2_MUXSEL_MASK                     (0x10U)
#define ADC_CFG2_MUXSEL_SHIFT                    (4U)
/*! MUXSEL - ADC Mux Select
 *  0b0..ADxxa channels are selected.
 *  0b1..ADxxb channels are selected.
 */
#define ADC_CFG2_MUXSEL(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_MUXSEL_SHIFT)) & ADC_CFG2_MUXSEL_MASK)
/*! @} */

/*! @name R - ADC Data Result Register */
/*! @{ */

#define ADC_R_D_MASK                             (0xFFFFU)
#define ADC_R_D_SHIFT                            (0U)
/*! D - Data result */
#define ADC_R_D(x)                               (((uint32_t)(((uint32_t)(x)) << ADC_R_D_SHIFT)) & ADC_R_D_MASK)
/*! @} */

/* The count of ADC_R */
#define ADC_R_COUNT                              (2U)

/*! @name CV1 - Compare Value Registers */
/*! @{ */

#define ADC_CV1_CV_MASK                          (0xFFFFU)
#define ADC_CV1_CV_SHIFT                         (0U)
/*! CV - Compare Value. */
#define ADC_CV1_CV(x)                            (((uint32_t)(((uint32_t)(x)) << ADC_CV1_CV_SHIFT)) & ADC_CV1_CV_MASK)
/*! @} */

/*! @name CV2 - Compare Value Registers */
/*! @{ */

#define ADC_CV2_CV_MASK                          (0xFFFFU)
#define ADC_CV2_CV_SHIFT                         (0U)
/*! CV - Compare Value. */
#define ADC_CV2_CV(x)                            (((uint32_t)(((uint32_t)(x)) << ADC_CV2_CV_SHIFT)) & ADC_CV2_CV_MASK)
/*! @} */

/*! @name SC2 - Status and Control Register 2 */
/*! @{ */

#define ADC_SC2_REFSEL_MASK                      (0x3U)
#define ADC_SC2_REFSEL_SHIFT                     (0U)
/*! REFSEL - Voltage Reference Selection
 *  0b00..Default voltage reference pin pair, that is, external pins VREFH and VREFL
 *  0b01..Alternate reference pair, that is, VALTH and VALTL . This pair may be additional external pins or
 *        internal sources depending on the MCU configuration. See the chip configuration information for details
 *        specific to this MCU
 *  0b10..Reserved
 *  0b11..Reserved
 */
#define ADC_SC2_REFSEL(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_SC2_REFSEL_SHIFT)) & ADC_SC2_REFSEL_MASK)

#define ADC_SC2_DMAEN_MASK                       (0x4U)
#define ADC_SC2_DMAEN_SHIFT                      (2U)
/*! DMAEN - DMA Enable
 *  0b0..DMA is disabled.
 *  0b1..DMA is enabled and will assert the ADC DMA request during an ADC conversion complete event noted when any
 *       of the SC1n[COCO] flags is asserted.
 */
#define ADC_SC2_DMAEN(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_DMAEN_SHIFT)) & ADC_SC2_DMAEN_MASK)

#define ADC_SC2_ACREN_MASK                       (0x8U)
#define ADC_SC2_ACREN_SHIFT                      (3U)
/*! ACREN - Compare Function Range Enable
 *  0b0..Range function disabled. Only CV1 is compared.
 *  0b1..Range function enabled. Both CV1 and CV2 are compared.
 */
#define ADC_SC2_ACREN(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ACREN_SHIFT)) & ADC_SC2_ACREN_MASK)

#define ADC_SC2_ACFGT_MASK                       (0x10U)
#define ADC_SC2_ACFGT_SHIFT                      (4U)
/*! ACFGT - Compare Function Greater Than Enable
 *  0b0..Configures less than threshold, outside range not inclusive and inside range not inclusive; functionality
 *       based on the values placed in CV1 and CV2.
 *  0b1..Configures greater than or equal to threshold, outside and inside ranges inclusive; functionality based on the values placed in CV1 and CV2.
 */
#define ADC_SC2_ACFGT(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ACFGT_SHIFT)) & ADC_SC2_ACFGT_MASK)

#define ADC_SC2_ACFE_MASK                        (0x20U)
#define ADC_SC2_ACFE_SHIFT                       (5U)
/*! ACFE - Compare Function Enable
 *  0b0..Compare function disabled.
 *  0b1..Compare function enabled.
 */
#define ADC_SC2_ACFE(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ACFE_SHIFT)) & ADC_SC2_ACFE_MASK)

#define ADC_SC2_ADTRG_MASK                       (0x40U)
#define ADC_SC2_ADTRG_SHIFT                      (6U)
/*! ADTRG - Conversion Trigger Select
 *  0b0..Software trigger selected.
 *  0b1..Hardware trigger selected.
 */
#define ADC_SC2_ADTRG(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ADTRG_SHIFT)) & ADC_SC2_ADTRG_MASK)

#define ADC_SC2_ADACT_MASK                       (0x80U)
#define ADC_SC2_ADACT_SHIFT                      (7U)
/*! ADACT - Conversion Active
 *  0b0..Conversion not in progress.
 *  0b1..Conversion in progress.
 */
#define ADC_SC2_ADACT(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ADACT_SHIFT)) & ADC_SC2_ADACT_MASK)
/*! @} */

/*! @name SC3 - Status and Control Register 3 */
/*! @{ */

#define ADC_SC3_AVGS_MASK                        (0x3U)
#define ADC_SC3_AVGS_SHIFT                       (0U)
/*! AVGS - Hardware Average Select
 *  0b00..4 samples averaged.
 *  0b01..8 samples averaged.
 *  0b10..16 samples averaged.
 *  0b11..32 samples averaged.
 */
#define ADC_SC3_AVGS(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC3_AVGS_SHIFT)) & ADC_SC3_AVGS_MASK)

#define ADC_SC3_AVGE_MASK                        (0x4U)
#define ADC_SC3_AVGE_SHIFT                       (2U)
/*! AVGE - Hardware Average Enable
 *  0b0..Hardware average function disabled.
 *  0b1..Hardware average function enabled.
 */
#define ADC_SC3_AVGE(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC3_AVGE_SHIFT)) & ADC_SC3_AVGE_MASK)

#define ADC_SC3_ADCO_MASK                        (0x8U)
#define ADC_SC3_ADCO_SHIFT                       (3U)
/*! ADCO - Continuous Conversion Enable
 *  0b0..One conversion or one set of conversions if the hardware average function is enabled, that is, AVGE=1, after initiating a conversion.
 *  0b1..Continuous conversions or sets of conversions if the hardware average function is enabled, that is, AVGE=1, after initiating a conversion.
 */
#define ADC_SC3_ADCO(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC3_ADCO_SHIFT)) & ADC_SC3_ADCO_MASK)

#define ADC_SC3_CALF_MASK                        (0x40U)
#define ADC_SC3_CALF_SHIFT                       (6U)
/*! CALF - Calibration Failed Flag
 *  0b0..Calibration completed normally.
 *  0b1..Calibration failed. ADC accuracy specifications are not guaranteed.
 */
#define ADC_SC3_CALF(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC3_CALF_SHIFT)) & ADC_SC3_CALF_MASK)

#define ADC_SC3_CAL_MASK                         (0x80U)
#define ADC_SC3_CAL_SHIFT                        (7U)
/*! CAL - Calibration */
#define ADC_SC3_CAL(x)                           (((uint32_t)(((uint32_t)(x)) << ADC_SC3_CAL_SHIFT)) & ADC_SC3_CAL_MASK)
/*! @} */

/*! @name OFS - ADC Offset Correction Register */
/*! @{ */

#define ADC_OFS_OFS_MASK                         (0xFFFFU)
#define ADC_OFS_OFS_SHIFT                        (0U)
/*! OFS - Offset Error Correction Value */
#define ADC_OFS_OFS(x)                           (((uint32_t)(((uint32_t)(x)) << ADC_OFS_OFS_SHIFT)) & ADC_OFS_OFS_MASK)
/*! @} */

/*! @name PG - ADC Plus-Side Gain Register */
/*! @{ */

#define ADC_PG_PG_MASK                           (0xFFFFU)
#define ADC_PG_PG_SHIFT                          (0U)
/*! PG - Plus-Side Gain */
#define ADC_PG_PG(x)                             (((uint32_t)(((uint32_t)(x)) << ADC_PG_PG_SHIFT)) & ADC_PG_PG_MASK)
/*! @} */

/*! @name MG - ADC Minus-Side Gain Register */
/*! @{ */

#define ADC_MG_MG_MASK                           (0xFFFFU)
#define ADC_MG_MG_SHIFT                          (0U)
/*! MG - Minus-Side Gain */
#define ADC_MG_MG(x)                             (((uint32_t)(((uint32_t)(x)) << ADC_MG_MG_SHIFT)) & ADC_MG_MG_MASK)
/*! @} */

/*! @name CLPD - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLPD_CLPD_MASK                       (0x3FU)
#define ADC_CLPD_CLPD_SHIFT                      (0U)
/*! CLPD - Calibration Value */
#define ADC_CLPD_CLPD(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLPD_CLPD_SHIFT)) & ADC_CLPD_CLPD_MASK)
/*! @} */

/*! @name CLPS - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLPS_CLPS_MASK                       (0x3FU)
#define ADC_CLPS_CLPS_SHIFT                      (0U)
/*! CLPS - Calibration Value */
#define ADC_CLPS_CLPS(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLPS_CLPS_SHIFT)) & ADC_CLPS_CLPS_MASK)
/*! @} */

/*! @name CLP4 - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLP4_CLP4_MASK                       (0x3FFU)
#define ADC_CLP4_CLP4_SHIFT                      (0U)
/*! CLP4 - Calibration Value */
#define ADC_CLP4_CLP4(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP4_CLP4_SHIFT)) & ADC_CLP4_CLP4_MASK)
/*! @} */

/*! @name CLP3 - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLP3_CLP3_MASK                       (0x1FFU)
#define ADC_CLP3_CLP3_SHIFT                      (0U)
/*! CLP3 - Calibration Value */
#define ADC_CLP3_CLP3(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP3_CLP3_SHIFT)) & ADC_CLP3_CLP3_MASK)
/*! @} */

/*! @name CLP2 - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLP2_CLP2_MASK                       (0xFFU)
#define ADC_CLP2_CLP2_SHIFT                      (0U)
/*! CLP2 - Calibration Value */
#define ADC_CLP2_CLP2(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP2_CLP2_SHIFT)) & ADC_CLP2_CLP2_MASK)
/*! @} */

/*! @name CLP1 - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLP1_CLP1_MASK                       (0x7FU)
#define ADC_CLP1_CLP1_SHIFT                      (0U)
/*! CLP1 - Calibration Value */
#define ADC_CLP1_CLP1(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP1_CLP1_SHIFT)) & ADC_CLP1_CLP1_MASK)
/*! @} */

/*! @name CLP0 - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLP0_CLP0_MASK                       (0x3FU)
#define ADC_CLP0_CLP0_SHIFT                      (0U)
/*! CLP0 - Calibration Value */
#define ADC_CLP0_CLP0(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP0_CLP0_SHIFT)) & ADC_CLP0_CLP0_MASK)
/*! @} */

/*! @name CLMD - ADC Minus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLMD_CLMD_MASK                       (0x3FU)
#define ADC_CLMD_CLMD_SHIFT                      (0U)
/*! CLMD - Calibration Value */
#define ADC_CLMD_CLMD(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLMD_CLMD_SHIFT)) & ADC_CLMD_CLMD_MASK)
/*! @} */

/*! @name CLMS - ADC Minus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLMS_CLMS_MASK                       (0x3FU)
#define ADC_CLMS_CLMS_SHIFT                      (0U)
/*! CLMS - Calibration Value */
#define ADC_CLMS_CLMS(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLMS_CLMS_SHIFT)) & ADC_CLMS_CLMS_MASK)
/*! @} */

/*! @name CLM4 - ADC Minus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLM4_CLM4_MASK                       (0x3FFU)
#define ADC_CLM4_CLM4_SHIFT                      (0U)
/*! CLM4 - Calibration Value */
#define ADC_CLM4_CLM4(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLM4_CLM4_SHIFT)) & ADC_CLM4_CLM4_MASK)
/*! @} */

/*! @name CLM3 - ADC Minus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLM3_CLM3_MASK                       (0x1FFU)
#define ADC_CLM3_CLM3_SHIFT                      (0U)
/*! CLM3 - Calibration Value */
#define ADC_CLM3_CLM3(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLM3_CLM3_SHIFT)) & ADC_CLM3_CLM3_MASK)
/*! @} */

/*! @name CLM2 - ADC Minus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLM2_CLM2_MASK                       (0xFFU)
#define ADC_CLM2_CLM2_SHIFT                      (0U)
/*! CLM2 - Calibration Value */
#define ADC_CLM2_CLM2(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLM2_CLM2_SHIFT)) & ADC_CLM2_CLM2_MASK)
/*! @} */

/*! @name CLM1 - ADC Minus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLM1_CLM1_MASK                       (0x7FU)
#define ADC_CLM1_CLM1_SHIFT                      (0U)
/*! CLM1 - Calibration Value */
#define ADC_CLM1_CLM1(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLM1_CLM1_SHIFT)) & ADC_CLM1_CLM1_MASK)
/*! @} */

/*! @name CLM0 - ADC Minus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLM0_CLM0_MASK                       (0x3FU)
#define ADC_CLM0_CLM0_SHIFT                      (0U)
/*! CLM0 - Calibration Value */
#define ADC_CLM0_CLM0(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLM0_CLM0_SHIFT)) & ADC_CLM0_CLM0_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base address */
#define ADC0_BASE                                (0x4003B000u)
/** Peripheral ADC0 base pointer */
#define ADC0                                     ((ADC_Type *)ADC0_BASE)
/** Array initializer of ADC peripheral base addresses */
#define ADC_BASE_ADDRS                           { ADC0_BASE }
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            { ADC0 }
/** Interrupt vectors for the ADC peripheral type */
#define ADC_IRQS                                 { ADC0_IRQn }

/*!
 * @}
 */ /* end of group ADC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CMP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Peripheral_Access_Layer CMP Peripheral Access Layer
 * @{
 */

/** CMP - Register Layout Typedef */
typedef struct {
  __IO uint8_t CR0;                                /**< CMP Control Register 0, offset: 0x0 */
  __IO uint8_t CR1;                                /**< CMP Control Register 1, offset: 0x1 */
  __IO uint8_t FPR;                                /**< CMP Filter Period Register, offset: 0x2 */
  __IO uint8_t SCR;                                /**< CMP Status and Control Register, offset: 0x3 */
  __IO uint8_t DACCR;                              /**< DAC Control Register, offset: 0x4 */
  __IO uint8_t MUXCR;                              /**< MUX Control Register, offset: 0x5 */
} CMP_Type;

/* ----------------------------------------------------------------------------
   -- CMP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Register_Masks CMP Register Masks
 * @{
 */

/*! @name CR0 - CMP Control Register 0 */
/*! @{ */

#define CMP_CR0_HYSTCTR_MASK                     (0x3U)
#define CMP_CR0_HYSTCTR_SHIFT                    (0U)
/*! HYSTCTR - Comparator hard block hysteresis control
 *  0b00..Level 0
 *  0b01..Level 1
 *  0b10..Level 2
 *  0b11..Level 3
 */
#define CMP_CR0_HYSTCTR(x)                       (((uint8_t)(((uint8_t)(x)) << CMP_CR0_HYSTCTR_SHIFT)) & CMP_CR0_HYSTCTR_MASK)

#define CMP_CR0_FILTER_CNT_MASK                  (0x70U)
#define CMP_CR0_FILTER_CNT_SHIFT                 (4U)
/*! FILTER_CNT - Filter Sample Count
 *  0b000..Filter is disabled. SE = 0, COUT = COUTA.
 *  0b001..One sample must agree. The comparator output is simply sampled.
 *  0b010..2 consecutive samples must agree.
 *  0b011..3 consecutive samples must agree.
 *  0b100..4 consecutive samples must agree.
 *  0b101..5 consecutive samples must agree.
 *  0b110..6 consecutive samples must agree.
 *  0b111..7 consecutive samples must agree.
 */
#define CMP_CR0_FILTER_CNT(x)                    (((uint8_t)(((uint8_t)(x)) << CMP_CR0_FILTER_CNT_SHIFT)) & CMP_CR0_FILTER_CNT_MASK)
/*! @} */

/*! @name CR1 - CMP Control Register 1 */
/*! @{ */

#define CMP_CR1_EN_MASK                          (0x1U)
#define CMP_CR1_EN_SHIFT                         (0U)
/*! EN - Comparator Module Enable
 *  0b0..Analog Comparator is disabled.
 *  0b1..Analog Comparator is enabled.
 */
#define CMP_CR1_EN(x)                            (((uint8_t)(((uint8_t)(x)) << CMP_CR1_EN_SHIFT)) & CMP_CR1_EN_MASK)

#define CMP_CR1_OPE_MASK                         (0x2U)
#define CMP_CR1_OPE_SHIFT                        (1U)
/*! OPE - Comparator Output Pin Enable
 *  0b0..CMPO is not available on the associated CMPO output pin. If the comparator does not own the pin, this field has no effect.
 *  0b1..CMPO is available on the associated CMPO output pin. The comparator output (CMPO) is driven out on the
 *       associated CMPO output pin if the comparator owns the pin. If the comparator does not own the field, this
 *       bit has no effect.
 */
#define CMP_CR1_OPE(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_CR1_OPE_SHIFT)) & CMP_CR1_OPE_MASK)

#define CMP_CR1_COS_MASK                         (0x4U)
#define CMP_CR1_COS_SHIFT                        (2U)
/*! COS - Comparator Output Select
 *  0b0..Set the filtered comparator output (CMPO) to equal COUT.
 *  0b1..Set the unfiltered comparator output (CMPO) to equal COUTA.
 */
#define CMP_CR1_COS(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_CR1_COS_SHIFT)) & CMP_CR1_COS_MASK)

#define CMP_CR1_INV_MASK                         (0x8U)
#define CMP_CR1_INV_SHIFT                        (3U)
/*! INV - Comparator INVERT
 *  0b0..Does not invert the comparator output.
 *  0b1..Inverts the comparator output.
 */
#define CMP_CR1_INV(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_CR1_INV_SHIFT)) & CMP_CR1_INV_MASK)

#define CMP_CR1_PMODE_MASK                       (0x10U)
#define CMP_CR1_PMODE_SHIFT                      (4U)
/*! PMODE - Power Mode Select
 *  0b0..Low-Speed (LS) Comparison mode selected. In this mode, CMP has slower output propagation delay and lower current consumption.
 *  0b1..High-Speed (HS) Comparison mode selected. In this mode, CMP has faster output propagation delay and higher current consumption.
 */
#define CMP_CR1_PMODE(x)                         (((uint8_t)(((uint8_t)(x)) << CMP_CR1_PMODE_SHIFT)) & CMP_CR1_PMODE_MASK)

#define CMP_CR1_TRIGM_MASK                       (0x20U)
#define CMP_CR1_TRIGM_SHIFT                      (5U)
/*! TRIGM - Trigger Mode Enable
 *  0b0..Trigger mode is disabled.
 *  0b1..Trigger mode is enabled.
 */
#define CMP_CR1_TRIGM(x)                         (((uint8_t)(((uint8_t)(x)) << CMP_CR1_TRIGM_SHIFT)) & CMP_CR1_TRIGM_MASK)

#define CMP_CR1_WE_MASK                          (0x40U)
#define CMP_CR1_WE_SHIFT                         (6U)
/*! WE - Windowing Enable
 *  0b0..Windowing mode is not selected.
 *  0b1..Windowing mode is selected.
 */
#define CMP_CR1_WE(x)                            (((uint8_t)(((uint8_t)(x)) << CMP_CR1_WE_SHIFT)) & CMP_CR1_WE_MASK)

#define CMP_CR1_SE_MASK                          (0x80U)
#define CMP_CR1_SE_SHIFT                         (7U)
/*! SE - Sample Enable
 *  0b0..Sampling mode is not selected.
 *  0b1..Sampling mode is selected.
 */
#define CMP_CR1_SE(x)                            (((uint8_t)(((uint8_t)(x)) << CMP_CR1_SE_SHIFT)) & CMP_CR1_SE_MASK)
/*! @} */

/*! @name FPR - CMP Filter Period Register */
/*! @{ */

#define CMP_FPR_FILT_PER_MASK                    (0xFFU)
#define CMP_FPR_FILT_PER_SHIFT                   (0U)
/*! FILT_PER - Filter Sample Period */
#define CMP_FPR_FILT_PER(x)                      (((uint8_t)(((uint8_t)(x)) << CMP_FPR_FILT_PER_SHIFT)) & CMP_FPR_FILT_PER_MASK)
/*! @} */

/*! @name SCR - CMP Status and Control Register */
/*! @{ */

#define CMP_SCR_COUT_MASK                        (0x1U)
#define CMP_SCR_COUT_SHIFT                       (0U)
/*! COUT - Analog Comparator Output */
#define CMP_SCR_COUT(x)                          (((uint8_t)(((uint8_t)(x)) << CMP_SCR_COUT_SHIFT)) & CMP_SCR_COUT_MASK)

#define CMP_SCR_CFF_MASK                         (0x2U)
#define CMP_SCR_CFF_SHIFT                        (1U)
/*! CFF - Analog Comparator Flag Falling
 *  0b0..Falling-edge on COUT has not been detected.
 *  0b1..Falling-edge on COUT has occurred.
 */
#define CMP_SCR_CFF(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_SCR_CFF_SHIFT)) & CMP_SCR_CFF_MASK)

#define CMP_SCR_CFR_MASK                         (0x4U)
#define CMP_SCR_CFR_SHIFT                        (2U)
/*! CFR - Analog Comparator Flag Rising
 *  0b0..Rising-edge on COUT has not been detected.
 *  0b1..Rising-edge on COUT has occurred.
 */
#define CMP_SCR_CFR(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_SCR_CFR_SHIFT)) & CMP_SCR_CFR_MASK)

#define CMP_SCR_IEF_MASK                         (0x8U)
#define CMP_SCR_IEF_SHIFT                        (3U)
/*! IEF - Comparator Interrupt Enable Falling
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define CMP_SCR_IEF(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_SCR_IEF_SHIFT)) & CMP_SCR_IEF_MASK)

#define CMP_SCR_IER_MASK                         (0x10U)
#define CMP_SCR_IER_SHIFT                        (4U)
/*! IER - Comparator Interrupt Enable Rising
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define CMP_SCR_IER(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_SCR_IER_SHIFT)) & CMP_SCR_IER_MASK)

#define CMP_SCR_DMAEN_MASK                       (0x40U)
#define CMP_SCR_DMAEN_SHIFT                      (6U)
/*! DMAEN - DMA Enable Control
 *  0b0..DMA is disabled.
 *  0b1..DMA is enabled.
 */
#define CMP_SCR_DMAEN(x)                         (((uint8_t)(((uint8_t)(x)) << CMP_SCR_DMAEN_SHIFT)) & CMP_SCR_DMAEN_MASK)
/*! @} */

/*! @name DACCR - DAC Control Register */
/*! @{ */

#define CMP_DACCR_VOSEL_MASK                     (0x3FU)
#define CMP_DACCR_VOSEL_SHIFT                    (0U)
/*! VOSEL - DAC Output Voltage Select */
#define CMP_DACCR_VOSEL(x)                       (((uint8_t)(((uint8_t)(x)) << CMP_DACCR_VOSEL_SHIFT)) & CMP_DACCR_VOSEL_MASK)

#define CMP_DACCR_VRSEL_MASK                     (0x40U)
#define CMP_DACCR_VRSEL_SHIFT                    (6U)
/*! VRSEL - Supply Voltage Reference Source Select
 *  0b0..Vin1 is selected as resistor ladder network supply reference.
 *  0b1..Vin2 is selected as resistor ladder network supply reference.
 */
#define CMP_DACCR_VRSEL(x)                       (((uint8_t)(((uint8_t)(x)) << CMP_DACCR_VRSEL_SHIFT)) & CMP_DACCR_VRSEL_MASK)

#define CMP_DACCR_DACEN_MASK                     (0x80U)
#define CMP_DACCR_DACEN_SHIFT                    (7U)
/*! DACEN - DAC Enable
 *  0b0..DAC is disabled.
 *  0b1..DAC is enabled.
 */
#define CMP_DACCR_DACEN(x)                       (((uint8_t)(((uint8_t)(x)) << CMP_DACCR_DACEN_SHIFT)) & CMP_DACCR_DACEN_MASK)
/*! @} */

/*! @name MUXCR - MUX Control Register */
/*! @{ */

#define CMP_MUXCR_MSEL_MASK                      (0x7U)
#define CMP_MUXCR_MSEL_SHIFT                     (0U)
/*! MSEL - Minus Input Mux Control
 *  0b000..IN0
 *  0b001..IN1
 *  0b010..IN2
 *  0b011..IN3
 *  0b100..IN4
 *  0b101..IN5
 *  0b110..IN6
 *  0b111..IN7
 */
#define CMP_MUXCR_MSEL(x)                        (((uint8_t)(((uint8_t)(x)) << CMP_MUXCR_MSEL_SHIFT)) & CMP_MUXCR_MSEL_MASK)

#define CMP_MUXCR_PSEL_MASK                      (0x38U)
#define CMP_MUXCR_PSEL_SHIFT                     (3U)
/*! PSEL - Plus Input Mux Control
 *  0b000..IN0
 *  0b001..IN1
 *  0b010..IN2
 *  0b011..IN3
 *  0b100..IN4
 *  0b101..IN5
 *  0b110..IN6
 *  0b111..IN7
 */
#define CMP_MUXCR_PSEL(x)                        (((uint8_t)(((uint8_t)(x)) << CMP_MUXCR_PSEL_SHIFT)) & CMP_MUXCR_PSEL_MASK)

#define CMP_MUXCR_PSTM_MASK                      (0x80U)
#define CMP_MUXCR_PSTM_SHIFT                     (7U)
/*! PSTM - Pass Through Mode Enable
 *  0b0..Pass Through Mode is disabled.
 *  0b1..Pass Through Mode is enabled.
 */
#define CMP_MUXCR_PSTM(x)                        (((uint8_t)(((uint8_t)(x)) << CMP_MUXCR_PSTM_SHIFT)) & CMP_MUXCR_PSTM_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group CMP_Register_Masks */


/* CMP - Peripheral instance base addresses */
/** Peripheral CMP0 base address */
#define CMP0_BASE                                (0x40073000u)
/** Peripheral CMP0 base pointer */
#define CMP0                                     ((CMP_Type *)CMP0_BASE)
/** Array initializer of CMP peripheral base addresses */
#define CMP_BASE_ADDRS                           { CMP0_BASE }
/** Array initializer of CMP peripheral base pointers */
#define CMP_BASE_PTRS                            { CMP0 }
/** Interrupt vectors for the CMP peripheral type */
#define CMP_IRQS                                 { CMP0_IRQn }

/*!
 * @}
 */ /* end of group CMP_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- DAC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DAC_Peripheral_Access_Layer DAC Peripheral Access Layer
 * @{
 */

/** DAC - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x2 */
    __IO uint8_t DATL;                               /**< DAC Data Low Register, array offset: 0x0, array step: 0x2 */
    __IO uint8_t DATH;                               /**< DAC Data High Register, array offset: 0x1, array step: 0x2 */
  } DAT[2];
       uint8_t RESERVED_0[28];
  __IO uint8_t SR;                                 /**< DAC Status Register, offset: 0x20 */
  __IO uint8_t C0;                                 /**< DAC Control Register, offset: 0x21 */
  __IO uint8_t C1;                                 /**< DAC Control Register 1, offset: 0x22 */
  __IO uint8_t C2;                                 /**< DAC Control Register 2, offset: 0x23 */
} DAC_Type;

/* ----------------------------------------------------------------------------
   -- DAC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DAC_Register_Masks DAC Register Masks
 * @{
 */

/*! @name DATL - DAC Data Low Register */
/*! @{ */

#define DAC_DATL_DATA0_MASK                      (0xFFU)
#define DAC_DATL_DATA0_SHIFT                     (0U)
/*! DATA0 - DATA0 */
#define DAC_DATL_DATA0(x)                        (((uint8_t)(((uint8_t)(x)) << DAC_DATL_DATA0_SHIFT)) & DAC_DATL_DATA0_MASK)
/*! @} */

/* The count of DAC_DATL */
#define DAC_DATL_COUNT                           (2U)

/*! @name DATH - DAC Data High Register */
/*! @{ */

#define DAC_DATH_DATA1_MASK                      (0xFU)
#define DAC_DATH_DATA1_SHIFT                     (0U)
/*! DATA1 - DATA1 */
#define DAC_DATH_DATA1(x)                        (((uint8_t)(((uint8_t)(x)) << DAC_DATH_DATA1_SHIFT)) & DAC_DATH_DATA1_MASK)
/*! @} */

/* The count of DAC_DATH */
#define DAC_DATH_COUNT                           (2U)

/*! @name SR - DAC Status Register */
/*! @{ */

#define DAC_SR_DACBFRPBF_MASK                    (0x1U)
#define DAC_SR_DACBFRPBF_SHIFT                   (0U)
/*! DACBFRPBF - DAC Buffer Read Pointer Bottom Position Flag
 *  0b0..The DAC buffer read pointer is not equal to C2[DACBFUP].
 *  0b1..The DAC buffer read pointer is equal to C2[DACBFUP].
 */
#define DAC_SR_DACBFRPBF(x)                      (((uint8_t)(((uint8_t)(x)) << DAC_SR_DACBFRPBF_SHIFT)) & DAC_SR_DACBFRPBF_MASK)

#define DAC_SR_DACBFRPTF_MASK                    (0x2U)
#define DAC_SR_DACBFRPTF_SHIFT                   (1U)
/*! DACBFRPTF - DAC Buffer Read Pointer Top Position Flag
 *  0b0..The DAC buffer read pointer is not zero.
 *  0b1..The DAC buffer read pointer is zero.
 */
#define DAC_SR_DACBFRPTF(x)                      (((uint8_t)(((uint8_t)(x)) << DAC_SR_DACBFRPTF_SHIFT)) & DAC_SR_DACBFRPTF_MASK)
/*! @} */

/*! @name C0 - DAC Control Register */
/*! @{ */

#define DAC_C0_DACBBIEN_MASK                     (0x1U)
#define DAC_C0_DACBBIEN_SHIFT                    (0U)
/*! DACBBIEN - DAC Buffer Read Pointer Bottom Flag Interrupt Enable
 *  0b0..The DAC buffer read pointer bottom flag interrupt is disabled.
 *  0b1..The DAC buffer read pointer bottom flag interrupt is enabled.
 */
#define DAC_C0_DACBBIEN(x)                       (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACBBIEN_SHIFT)) & DAC_C0_DACBBIEN_MASK)

#define DAC_C0_DACBTIEN_MASK                     (0x2U)
#define DAC_C0_DACBTIEN_SHIFT                    (1U)
/*! DACBTIEN - DAC Buffer Read Pointer Top Flag Interrupt Enable
 *  0b0..The DAC buffer read pointer top flag interrupt is disabled.
 *  0b1..The DAC buffer read pointer top flag interrupt is enabled.
 */
#define DAC_C0_DACBTIEN(x)                       (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACBTIEN_SHIFT)) & DAC_C0_DACBTIEN_MASK)

#define DAC_C0_LPEN_MASK                         (0x8U)
#define DAC_C0_LPEN_SHIFT                        (3U)
/*! LPEN - DAC Low Power Control
 *  0b0..High-Power mode
 *  0b1..Low-Power mode
 */
#define DAC_C0_LPEN(x)                           (((uint8_t)(((uint8_t)(x)) << DAC_C0_LPEN_SHIFT)) & DAC_C0_LPEN_MASK)

#define DAC_C0_DACSWTRG_MASK                     (0x10U)
#define DAC_C0_DACSWTRG_SHIFT                    (4U)
/*! DACSWTRG - DAC Software Trigger
 *  0b0..The DAC soft trigger is not valid.
 *  0b1..The DAC soft trigger is valid.
 */
#define DAC_C0_DACSWTRG(x)                       (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACSWTRG_SHIFT)) & DAC_C0_DACSWTRG_MASK)

#define DAC_C0_DACTRGSEL_MASK                    (0x20U)
#define DAC_C0_DACTRGSEL_SHIFT                   (5U)
/*! DACTRGSEL - DAC Trigger Select
 *  0b0..The DAC hardware trigger is selected.
 *  0b1..The DAC software trigger is selected.
 */
#define DAC_C0_DACTRGSEL(x)                      (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACTRGSEL_SHIFT)) & DAC_C0_DACTRGSEL_MASK)

#define DAC_C0_DACRFS_MASK                       (0x40U)
#define DAC_C0_DACRFS_SHIFT                      (6U)
/*! DACRFS - DAC Reference Select
 *  0b0..The DAC selects DACREF_1 as the reference voltage.
 *  0b1..The DAC selects DACREF_2 as the reference voltage.
 */
#define DAC_C0_DACRFS(x)                         (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACRFS_SHIFT)) & DAC_C0_DACRFS_MASK)

#define DAC_C0_DACEN_MASK                        (0x80U)
#define DAC_C0_DACEN_SHIFT                       (7U)
/*! DACEN - DAC Enable
 *  0b0..The DAC system is disabled.
 *  0b1..The DAC system is enabled.
 */
#define DAC_C0_DACEN(x)                          (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACEN_SHIFT)) & DAC_C0_DACEN_MASK)
/*! @} */

/*! @name C1 - DAC Control Register 1 */
/*! @{ */

#define DAC_C1_DACBFEN_MASK                      (0x1U)
#define DAC_C1_DACBFEN_SHIFT                     (0U)
/*! DACBFEN - DAC Buffer Enable
 *  0b0..Buffer read pointer is disabled. The converted data is always the first word of the buffer.
 *  0b1..Buffer read pointer is enabled. The converted data is the word that the read pointer points to. It means
 *       converted data can be from any word of the buffer.
 */
#define DAC_C1_DACBFEN(x)                        (((uint8_t)(((uint8_t)(x)) << DAC_C1_DACBFEN_SHIFT)) & DAC_C1_DACBFEN_MASK)

#define DAC_C1_DACBFMD_MASK                      (0x6U)
#define DAC_C1_DACBFMD_SHIFT                     (1U)
/*! DACBFMD - DAC Buffer Work Mode Select
 *  0b00..Normal mode
 *  0b01..Reserved
 *  0b10..One-Time Scan mode
 *  0b11..FIFO mode
 */
#define DAC_C1_DACBFMD(x)                        (((uint8_t)(((uint8_t)(x)) << DAC_C1_DACBFMD_SHIFT)) & DAC_C1_DACBFMD_MASK)

#define DAC_C1_DMAEN_MASK                        (0x80U)
#define DAC_C1_DMAEN_SHIFT                       (7U)
/*! DMAEN - DMA Enable Select
 *  0b0..DMA is disabled.
 *  0b1..DMA is enabled. When DMA is enabled, the DMA request will be generated by original interrupts. The
 *       interrupts will not be presented on this module at the same time.
 */
#define DAC_C1_DMAEN(x)                          (((uint8_t)(((uint8_t)(x)) << DAC_C1_DMAEN_SHIFT)) & DAC_C1_DMAEN_MASK)
/*! @} */

/*! @name C2 - DAC Control Register 2 */
/*! @{ */

#define DAC_C2_DACBFUP_MASK                      (0x1U)
#define DAC_C2_DACBFUP_SHIFT                     (0U)
/*! DACBFUP - DAC Buffer Upper Limit */
#define DAC_C2_DACBFUP(x)                        (((uint8_t)(((uint8_t)(x)) << DAC_C2_DACBFUP_SHIFT)) & DAC_C2_DACBFUP_MASK)

#define DAC_C2_DACBFRP_MASK                      (0x10U)
#define DAC_C2_DACBFRP_SHIFT                     (4U)
/*! DACBFRP - DAC Buffer Read Pointer */
#define DAC_C2_DACBFRP(x)                        (((uint8_t)(((uint8_t)(x)) << DAC_C2_DACBFRP_SHIFT)) & DAC_C2_DACBFRP_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group DAC_Register_Masks */


/* DAC - Peripheral instance base addresses */
/** Peripheral DAC0 base address */
#define DAC0_BASE                                (0x4003F000u)
/** Peripheral DAC0 base pointer */
#define DAC0                                     ((DAC_Type *)DAC0_BASE)
/** Array initializer of DAC peripheral base addresses */
#define DAC_BASE_ADDRS                           { DAC0_BASE }
/** Array initializer of DAC peripheral base pointers */
#define DAC_BASE_PTRS                            { DAC0 }
/** Interrupt vectors for the DAC peripheral type */
#define DAC_IRQS                                 { DAC0_IRQn }

/*!
 * @}
 */ /* end of group DAC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- DMA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Peripheral_Access_Layer DMA Peripheral Access Layer
 * @{
 */

/** DMA - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[256];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    __IO uint32_t SAR;                               /**< Source Address Register, array offset: 0x100, array step: 0x10 */
    __IO uint32_t DAR;                               /**< Destination Address Register, array offset: 0x104, array step: 0x10 */
    union {                                          /* offset: 0x108, array step: 0x10 */
      struct {                                         /* offset: 0x108, array step: 0x10 */
             uint8_t RESERVED_0[3];
             uint8_t DSR;                                /**< DMA_DSR0 register...DMA_DSR3 register., array offset: 0x10B, array step: 0x10 */
      } DMA_DSR_ACCESS8BIT;
      __IO uint32_t DSR_BCR;                           /**< DMA Status Register / Byte Count Register, array offset: 0x108, array step: 0x10 */
    };
    __IO uint32_t DCR;                               /**< DMA Control Register, array offset: 0x10C, array step: 0x10 */
  } DMA[4];
} DMA_Type;

/* ----------------------------------------------------------------------------
   -- DMA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Masks DMA Register Masks
 * @{
 */

/*! @name SAR - Source Address Register */
/*! @{ */

#define DMA_SAR_SAR_MASK                         (0xFFFFFFFFU)
#define DMA_SAR_SAR_SHIFT                        (0U)
/*! SAR - SAR */
#define DMA_SAR_SAR(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_SAR_SAR_SHIFT)) & DMA_SAR_SAR_MASK)
/*! @} */

/* The count of DMA_SAR */
#define DMA_SAR_COUNT                            (4U)

/*! @name DAR - Destination Address Register */
/*! @{ */

#define DMA_DAR_DAR_MASK                         (0xFFFFFFFFU)
#define DMA_DAR_DAR_SHIFT                        (0U)
/*! DAR - DAR */
#define DMA_DAR_DAR(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_DAR_DAR_SHIFT)) & DMA_DAR_DAR_MASK)
/*! @} */

/* The count of DMA_DAR */
#define DMA_DAR_COUNT                            (4U)

/* The count of DMA_DSR */
#define DMA_DSR_COUNT                            (4U)

/*! @name DSR_BCR - DMA Status Register / Byte Count Register */
/*! @{ */

#define DMA_DSR_BCR_BCR_MASK                     (0xFFFFFFU)
#define DMA_DSR_BCR_BCR_SHIFT                    (0U)
/*! BCR - BCR */
#define DMA_DSR_BCR_BCR(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_BCR_SHIFT)) & DMA_DSR_BCR_BCR_MASK)

#define DMA_DSR_BCR_DONE_MASK                    (0x1000000U)
#define DMA_DSR_BCR_DONE_SHIFT                   (24U)
/*! DONE - Transactions Done
 *  0b0..DMA transfer is not yet complete. Writing a 0 has no effect.
 *  0b1..DMA transfer completed. Writing a 1 to this bit clears all DMA status bits and should be used in an
 *       interrupt service routine to clear the DMA interrupt and error bits.
 */
#define DMA_DSR_BCR_DONE(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_DONE_SHIFT)) & DMA_DSR_BCR_DONE_MASK)

#define DMA_DSR_BCR_BSY_MASK                     (0x2000000U)
#define DMA_DSR_BCR_BSY_SHIFT                    (25U)
/*! BSY - Busy
 *  0b0..DMA channel is inactive. Cleared when the DMA has finished the last transaction.
 *  0b1..BSY is set the first time the channel is enabled after a transfer is initiated.
 */
#define DMA_DSR_BCR_BSY(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_BSY_SHIFT)) & DMA_DSR_BCR_BSY_MASK)

#define DMA_DSR_BCR_REQ_MASK                     (0x4000000U)
#define DMA_DSR_BCR_REQ_SHIFT                    (26U)
/*! REQ - Request
 *  0b0..No request is pending or the channel is currently active. Cleared when the channel is selected.
 *  0b1..The DMA channel has a transfer remaining and the channel is not selected.
 */
#define DMA_DSR_BCR_REQ(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_REQ_SHIFT)) & DMA_DSR_BCR_REQ_MASK)

#define DMA_DSR_BCR_BED_MASK                     (0x10000000U)
#define DMA_DSR_BCR_BED_SHIFT                    (28U)
/*! BED - Bus Error on Destination
 *  0b0..No bus error occurred.
 *  0b1..The DMA channel terminated with a bus error during the write portion of a transfer.
 */
#define DMA_DSR_BCR_BED(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_BED_SHIFT)) & DMA_DSR_BCR_BED_MASK)

#define DMA_DSR_BCR_BES_MASK                     (0x20000000U)
#define DMA_DSR_BCR_BES_SHIFT                    (29U)
/*! BES - Bus Error on Source
 *  0b0..No bus error occurred.
 *  0b1..The DMA channel terminated with a bus error during the read portion of a transfer.
 */
#define DMA_DSR_BCR_BES(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_BES_SHIFT)) & DMA_DSR_BCR_BES_MASK)

#define DMA_DSR_BCR_CE_MASK                      (0x40000000U)
#define DMA_DSR_BCR_CE_SHIFT                     (30U)
/*! CE - Configuration Error
 *  0b0..No configuration error exists.
 *  0b1..A configuration error has occurred.
 */
#define DMA_DSR_BCR_CE(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_CE_SHIFT)) & DMA_DSR_BCR_CE_MASK)
/*! @} */

/* The count of DMA_DSR_BCR */
#define DMA_DSR_BCR_COUNT                        (4U)

/*! @name DCR - DMA Control Register */
/*! @{ */

#define DMA_DCR_LCH2_MASK                        (0x3U)
#define DMA_DCR_LCH2_SHIFT                       (0U)
/*! LCH2 - Link Channel 2
 *  0b00..DMA Channel 0
 *  0b01..DMA Channel 1
 *  0b10..DMA Channel 2
 *  0b11..DMA Channel 3
 */
#define DMA_DCR_LCH2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_LCH2_SHIFT)) & DMA_DCR_LCH2_MASK)

#define DMA_DCR_LCH1_MASK                        (0xCU)
#define DMA_DCR_LCH1_SHIFT                       (2U)
/*! LCH1 - Link Channel 1
 *  0b00..DMA Channel 0
 *  0b01..DMA Channel 1
 *  0b10..DMA Channel 2
 *  0b11..DMA Channel 3
 */
#define DMA_DCR_LCH1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_LCH1_SHIFT)) & DMA_DCR_LCH1_MASK)

#define DMA_DCR_LINKCC_MASK                      (0x30U)
#define DMA_DCR_LINKCC_SHIFT                     (4U)
/*! LINKCC - Link Channel Control
 *  0b00..No channel-to-channel linking
 *  0b01..Perform a link to channel LCH1 after each cycle-steal transfer followed by a link to LCH2 after the BCR decrements to 0.
 *  0b10..Perform a link to channel LCH1 after each cycle-steal transfer
 *  0b11..Perform a link to channel LCH1 after the BCR decrements to 0.
 */
#define DMA_DCR_LINKCC(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_DCR_LINKCC_SHIFT)) & DMA_DCR_LINKCC_MASK)

#define DMA_DCR_D_REQ_MASK                       (0x80U)
#define DMA_DCR_D_REQ_SHIFT                      (7U)
/*! D_REQ - Disable Request
 *  0b0..ERQ bit is not affected.
 *  0b1..ERQ bit is cleared when the BCR is exhausted.
 */
#define DMA_DCR_D_REQ(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_DCR_D_REQ_SHIFT)) & DMA_DCR_D_REQ_MASK)

#define DMA_DCR_DMOD_MASK                        (0xF00U)
#define DMA_DCR_DMOD_SHIFT                       (8U)
/*! DMOD - Destination Address Modulo
 *  0b0000..Buffer disabled
 *  0b0001..Circular buffer size is 16 bytes
 *  0b0010..Circular buffer size is 32 bytes
 *  0b0011..Circular buffer size is 64 bytes
 *  0b0100..Circular buffer size is 128 bytes
 *  0b0101..Circular buffer size is 256 bytes
 *  0b0110..Circular buffer size is 512 bytes
 *  0b0111..Circular buffer size is 1 KB
 *  0b1000..Circular buffer size is 2 KB
 *  0b1001..Circular buffer size is 4 KB
 *  0b1010..Circular buffer size is 8 KB
 *  0b1011..Circular buffer size is 16 KB
 *  0b1100..Circular buffer size is 32 KB
 *  0b1101..Circular buffer size is 64 KB
 *  0b1110..Circular buffer size is 128 KB
 *  0b1111..Circular buffer size is 256 KB
 */
#define DMA_DCR_DMOD(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_DMOD_SHIFT)) & DMA_DCR_DMOD_MASK)

#define DMA_DCR_SMOD_MASK                        (0xF000U)
#define DMA_DCR_SMOD_SHIFT                       (12U)
/*! SMOD - Source Address Modulo
 *  0b0000..Buffer disabled
 *  0b0001..Circular buffer size is 16 bytes.
 *  0b0010..Circular buffer size is 32 bytes.
 *  0b0011..Circular buffer size is 64 bytes.
 *  0b0100..Circular buffer size is 128 bytes.
 *  0b0101..Circular buffer size is 256 bytes.
 *  0b0110..Circular buffer size is 512 bytes.
 *  0b0111..Circular buffer size is 1 KB.
 *  0b1000..Circular buffer size is 2 KB.
 *  0b1001..Circular buffer size is 4 KB.
 *  0b1010..Circular buffer size is 8 KB.
 *  0b1011..Circular buffer size is 16 KB.
 *  0b1100..Circular buffer size is 32 KB.
 *  0b1101..Circular buffer size is 64 KB.
 *  0b1110..Circular buffer size is 128 KB.
 *  0b1111..Circular buffer size is 256 KB.
 */
#define DMA_DCR_SMOD(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_SMOD_SHIFT)) & DMA_DCR_SMOD_MASK)

#define DMA_DCR_START_MASK                       (0x10000U)
#define DMA_DCR_START_SHIFT                      (16U)
/*! START - Start Transfer
 *  0b0..DMA inactive
 *  0b1..The DMA begins the transfer in accordance to the values in the TCDn. START is cleared automatically after
 *       one module clock and always reads as logic 0.
 */
#define DMA_DCR_START(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_DCR_START_SHIFT)) & DMA_DCR_START_MASK)

#define DMA_DCR_DSIZE_MASK                       (0x60000U)
#define DMA_DCR_DSIZE_SHIFT                      (17U)
/*! DSIZE - Destination Size
 *  0b00..32-bit
 *  0b01..8-bit
 *  0b10..16-bit
 *  0b11..Reserved (generates a configuration error (DSRn[CE]) if incorrectly specified at time of channel activation)
 */
#define DMA_DCR_DSIZE(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_DCR_DSIZE_SHIFT)) & DMA_DCR_DSIZE_MASK)

#define DMA_DCR_DINC_MASK                        (0x80000U)
#define DMA_DCR_DINC_SHIFT                       (19U)
/*! DINC - Destination Increment
 *  0b0..No change to the DAR after a successful transfer.
 *  0b1..The DAR increments by 1, 2, 4 depending upon the size of the transfer.
 */
#define DMA_DCR_DINC(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_DINC_SHIFT)) & DMA_DCR_DINC_MASK)

#define DMA_DCR_SSIZE_MASK                       (0x300000U)
#define DMA_DCR_SSIZE_SHIFT                      (20U)
/*! SSIZE - Source Size
 *  0b00..32-bit
 *  0b01..8-bit
 *  0b10..16-bit
 *  0b11..Reserved (generates a configuration error (DSRn[CE]) if incorrectly specified at time of channel activation)
 */
#define DMA_DCR_SSIZE(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_DCR_SSIZE_SHIFT)) & DMA_DCR_SSIZE_MASK)

#define DMA_DCR_SINC_MASK                        (0x400000U)
#define DMA_DCR_SINC_SHIFT                       (22U)
/*! SINC - Source Increment
 *  0b0..No change to SAR after a successful transfer.
 *  0b1..The SAR increments by 1, 2, 4 as determined by the transfer size.
 */
#define DMA_DCR_SINC(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_SINC_SHIFT)) & DMA_DCR_SINC_MASK)

#define DMA_DCR_EADREQ_MASK                      (0x800000U)
#define DMA_DCR_EADREQ_SHIFT                     (23U)
/*! EADREQ - Enable asynchronous DMA requests
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define DMA_DCR_EADREQ(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_DCR_EADREQ_SHIFT)) & DMA_DCR_EADREQ_MASK)

#define DMA_DCR_AA_MASK                          (0x10000000U)
#define DMA_DCR_AA_SHIFT                         (28U)
/*! AA - Auto-align
 *  0b0..Auto-align disabled
 *  0b1..If SSIZE indicates a transfer no smaller than DSIZE, source accesses are auto-aligned; otherwise,
 *       destination accesses are auto-aligned. Source alignment takes precedence over destination alignment. If
 *       auto-alignment is enabled, the appropriate address register increments, regardless of DINC or SINC.
 */
#define DMA_DCR_AA(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_DCR_AA_SHIFT)) & DMA_DCR_AA_MASK)

#define DMA_DCR_CS_MASK                          (0x20000000U)
#define DMA_DCR_CS_SHIFT                         (29U)
/*! CS - Cycle Steal
 *  0b0..DMA continuously makes read/write transfers until the BCR decrements to 0.
 *  0b1..Forces a single read/write transfer per request.
 */
#define DMA_DCR_CS(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_DCR_CS_SHIFT)) & DMA_DCR_CS_MASK)

#define DMA_DCR_ERQ_MASK                         (0x40000000U)
#define DMA_DCR_ERQ_SHIFT                        (30U)
/*! ERQ - Enable Peripheral Request
 *  0b0..Peripheral request is ignored.
 *  0b1..Enables peripheral request to initiate transfer. A software-initiated request (setting START) is always enabled.
 */
#define DMA_DCR_ERQ(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_DCR_ERQ_SHIFT)) & DMA_DCR_ERQ_MASK)

#define DMA_DCR_EINT_MASK                        (0x80000000U)
#define DMA_DCR_EINT_SHIFT                       (31U)
/*! EINT - Enable Interrupt on Completion of Transfer
 *  0b0..No interrupt is generated.
 *  0b1..Interrupt signal is enabled.
 */
#define DMA_DCR_EINT(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_EINT_SHIFT)) & DMA_DCR_EINT_MASK)
/*! @} */

/* The count of DMA_DCR */
#define DMA_DCR_COUNT                            (4U)


/*!
 * @}
 */ /* end of group DMA_Register_Masks */


/* DMA - Peripheral instance base addresses */
/** Peripheral DMA base address */
#define DMA_BASE                                 (0x40008000u)
/** Peripheral DMA base pointer */
#define DMA0                                     ((DMA_Type *)DMA_BASE)
/** Array initializer of DMA peripheral base addresses */
#define DMA_BASE_ADDRS                           { DMA_BASE }
/** Array initializer of DMA peripheral base pointers */
#define DMA_BASE_PTRS                            { DMA0 }
/** Interrupt vectors for the DMA peripheral type */
#define DMA_CHN_IRQS                             { { DMA0_IRQn, DMA1_IRQn, DMA2_IRQn, DMA3_IRQn } }

/*!
 * @}
 */ /* end of group DMA_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- DMAMUX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Peripheral_Access_Layer DMAMUX Peripheral Access Layer
 * @{
 */

/** DMAMUX - Register Layout Typedef */
typedef struct {
  __IO uint8_t CHCFG[4];                           /**< Channel Configuration register, array offset: 0x0, array step: 0x1 */
} DMAMUX_Type;

/* ----------------------------------------------------------------------------
   -- DMAMUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Register_Masks DMAMUX Register Masks
 * @{
 */

/*! @name CHCFG - Channel Configuration register */
/*! @{ */

#define DMAMUX_CHCFG_SOURCE_MASK                 (0x3FU)
#define DMAMUX_CHCFG_SOURCE_SHIFT                (0U)
/*! SOURCE - DMA Channel Source (Slot)
 *  0b000000..Disable_Signal
 *  0b000010..LPUART0_Rx_Signal
 *  0b000011..LPUART0_Tx_Signal
 *  0b000100..LPUART1_Rx_Signal
 *  0b000101..LPUART1_Tx_Signal
 *  0b000110..UART2_Rx_Signal
 *  0b000111..UART2_Tx_Signal
 *  0b001010..FlexIO_Channel0_Signal
 *  0b001011..FlexIO_Channel1_Signal
 *  0b001100..FlexIO_Channel2_Signal
 *  0b001101..FlexIO_Channel3_Signal
 *  0b001110..I2S0_Rx_Signal
 *  0b001111..I2S0_Tx_Signal
 *  0b010000..SPI0_Rx_Signal
 *  0b010001..SPI0_Tx_Signal
 *  0b010010..SPI1_Rx_Signal
 *  0b010011..SPI1_Tx_Signal
 *  0b010110..I2C0_Signal
 *  0b010111..I2C1_Signal
 *  0b011000..TPM0_Channel0_Signal
 *  0b011001..TPM0_Channel1_Signal
 *  0b011010..TPM0_Channel2_Signal
 *  0b011011..TPM0_Channel3_Signal
 *  0b011100..TPM0_Channel4_Signal
 *  0b011101..TPM0_Channel5_Signal
 *  0b100000..TPM1_Channel0_Signal
 *  0b100001..TPM1_Channel1_Signal
 *  0b100010..TPM2_Channel0_Signal
 *  0b100011..TPM2_Channel1_Signal
 *  0b101000..ADC0_Signal
 *  0b101010..CMP0_Signal
 *  0b101101..DAC0_Signal
 *  0b110001..Port_A_Signal
 *  0b110011..Port_C_Signal
 *  0b110100..Port_D_Signal
 *  0b110110..TPM0_Overflow_Signal
 *  0b110111..TPM1_Overflow_Signal
 *  0b111000..TPM2_Overflow_Signal
 *  0b111100..AlwaysOn60_Signal
 *  0b111101..AlwaysOn61_Signal
 *  0b111110..AlwaysOn62_Signal
 *  0b111111..AlwaysOn63_Signal
 */
#define DMAMUX_CHCFG_SOURCE(x)                   (((uint8_t)(((uint8_t)(x)) << DMAMUX_CHCFG_SOURCE_SHIFT)) & DMAMUX_CHCFG_SOURCE_MASK)

#define DMAMUX_CHCFG_TRIG_MASK                   (0x40U)
#define DMAMUX_CHCFG_TRIG_SHIFT                  (6U)
/*! TRIG - DMA Channel Trigger Enable
 *  0b0..Triggering is disabled. If triggering is disabled and ENBL is set, the DMA Channel will simply route the
 *       specified source to the DMA channel. (Normal mode)
 *  0b1..Triggering is enabled. If triggering is enabled and ENBL is set, the DMAMUX is in Periodic Trigger mode.
 */
#define DMAMUX_CHCFG_TRIG(x)                     (((uint8_t)(((uint8_t)(x)) << DMAMUX_CHCFG_TRIG_SHIFT)) & DMAMUX_CHCFG_TRIG_MASK)

#define DMAMUX_CHCFG_ENBL_MASK                   (0x80U)
#define DMAMUX_CHCFG_ENBL_SHIFT                  (7U)
/*! ENBL - DMA Channel Enable
 *  0b0..DMA channel is disabled. This mode is primarily used during configuration of the DMAMux. The DMA has
 *       separate channel enables/disables, which should be used to disable or reconfigure a DMA channel.
 *  0b1..DMA channel is enabled
 */
#define DMAMUX_CHCFG_ENBL(x)                     (((uint8_t)(((uint8_t)(x)) << DMAMUX_CHCFG_ENBL_SHIFT)) & DMAMUX_CHCFG_ENBL_MASK)
/*! @} */

/* The count of DMAMUX_CHCFG */
#define DMAMUX_CHCFG_COUNT                       (4U)


/*!
 * @}
 */ /* end of group DMAMUX_Register_Masks */


/* DMAMUX - Peripheral instance base addresses */
/** Peripheral DMAMUX0 base address */
#define DMAMUX0_BASE                             (0x40021000u)
/** Peripheral DMAMUX0 base pointer */
#define DMAMUX0                                  ((DMAMUX_Type *)DMAMUX0_BASE)
/** Array initializer of DMAMUX peripheral base addresses */
#define DMAMUX_BASE_ADDRS                        { DMAMUX0_BASE }
/** Array initializer of DMAMUX peripheral base pointers */
#define DMAMUX_BASE_PTRS                         { DMAMUX0 }

/*!
 * @}
 */ /* end of group DMAMUX_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- FGPIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Peripheral_Access_Layer FGPIO Peripheral Access Layer
 * @{
 */

/** FGPIO - Register Layout Typedef */
typedef struct {
  __IO uint32_t PDOR;                              /**< Port Data Output Register, offset: 0x0 */
  __O  uint32_t PSOR;                              /**< Port Set Output Register, offset: 0x4 */
  __O  uint32_t PCOR;                              /**< Port Clear Output Register, offset: 0x8 */
  __O  uint32_t PTOR;                              /**< Port Toggle Output Register, offset: 0xC */
  __I  uint32_t PDIR;                              /**< Port Data Input Register, offset: 0x10 */
  __IO uint32_t PDDR;                              /**< Port Data Direction Register, offset: 0x14 */
} FGPIO_Type;

/* ----------------------------------------------------------------------------
   -- FGPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Register_Masks FGPIO Register Masks
 * @{
 */

/*! @name PDOR - Port Data Output Register */
/*! @{ */

#define FGPIO_PDOR_PDO_MASK                      (0xFFFFFFFFU)
#define FGPIO_PDOR_PDO_SHIFT                     (0U)
/*! PDO - Port Data Output
 *  0b00000000000000000000000000000000..Logic level 0 is driven on pin, provided pin is configured for general-purpose output.
 *  0b00000000000000000000000000000001..Logic level 1 is driven on pin, provided pin is configured for general-purpose output.
 */
#define FGPIO_PDOR_PDO(x)                        (((uint32_t)(((uint32_t)(x)) << FGPIO_PDOR_PDO_SHIFT)) & FGPIO_PDOR_PDO_MASK)
/*! @} */

/*! @name PSOR - Port Set Output Register */
/*! @{ */

#define FGPIO_PSOR_PTSO_MASK                     (0xFFFFFFFFU)
#define FGPIO_PSOR_PTSO_SHIFT                    (0U)
/*! PTSO - Port Set Output
 *  0b00000000000000000000000000000000..Corresponding bit in PDORn does not change.
 *  0b00000000000000000000000000000001..Corresponding bit in PDORn is set to logic 1.
 */
#define FGPIO_PSOR_PTSO(x)                       (((uint32_t)(((uint32_t)(x)) << FGPIO_PSOR_PTSO_SHIFT)) & FGPIO_PSOR_PTSO_MASK)
/*! @} */

/*! @name PCOR - Port Clear Output Register */
/*! @{ */

#define FGPIO_PCOR_PTCO_MASK                     (0xFFFFFFFFU)
#define FGPIO_PCOR_PTCO_SHIFT                    (0U)
/*! PTCO - Port Clear Output
 *  0b00000000000000000000000000000000..Corresponding bit in PDORn does not change.
 *  0b00000000000000000000000000000001..Corresponding bit in PDORn is cleared to logic 0.
 */
#define FGPIO_PCOR_PTCO(x)                       (((uint32_t)(((uint32_t)(x)) << FGPIO_PCOR_PTCO_SHIFT)) & FGPIO_PCOR_PTCO_MASK)
/*! @} */

/*! @name PTOR - Port Toggle Output Register */
/*! @{ */

#define FGPIO_PTOR_PTTO_MASK                     (0xFFFFFFFFU)
#define FGPIO_PTOR_PTTO_SHIFT                    (0U)
/*! PTTO - Port Toggle Output
 *  0b00000000000000000000000000000000..Corresponding bit in PDORn does not change.
 *  0b00000000000000000000000000000001..Corresponding bit in PDORn is set to the inverse of its existing logic state.
 */
#define FGPIO_PTOR_PTTO(x)                       (((uint32_t)(((uint32_t)(x)) << FGPIO_PTOR_PTTO_SHIFT)) & FGPIO_PTOR_PTTO_MASK)
/*! @} */

/*! @name PDIR - Port Data Input Register */
/*! @{ */

#define FGPIO_PDIR_PDI_MASK                      (0xFFFFFFFFU)
#define FGPIO_PDIR_PDI_SHIFT                     (0U)
/*! PDI - Port Data Input
 *  0b00000000000000000000000000000000..Pin logic level is logic 0, or is not configured for use by digital function.
 *  0b00000000000000000000000000000001..Pin logic level is logic 1.
 */
#define FGPIO_PDIR_PDI(x)                        (((uint32_t)(((uint32_t)(x)) << FGPIO_PDIR_PDI_SHIFT)) & FGPIO_PDIR_PDI_MASK)
/*! @} */

/*! @name PDDR - Port Data Direction Register */
/*! @{ */

#define FGPIO_PDDR_PDD_MASK                      (0xFFFFFFFFU)
#define FGPIO_PDDR_PDD_SHIFT                     (0U)
/*! PDD - Port Data Direction
 *  0b00000000000000000000000000000000..Pin is configured as general-purpose input, for the GPIO function.
 *  0b00000000000000000000000000000001..Pin is configured as general-purpose output, for the GPIO function.
 */
#define FGPIO_PDDR_PDD(x)                        (((uint32_t)(((uint32_t)(x)) << FGPIO_PDDR_PDD_SHIFT)) & FGPIO_PDDR_PDD_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group FGPIO_Register_Masks */


/* FGPIO - Peripheral instance base addresses */
/** Peripheral FGPIOA base address */
#define FGPIOA_BASE                              (0xF8000000u)
/** Peripheral FGPIOA base pointer */
#define FGPIOA                                   ((FGPIO_Type *)FGPIOA_BASE)
/** Peripheral FGPIOB base address */
#define FGPIOB_BASE                              (0xF8000040u)
/** Peripheral FGPIOB base pointer */
#define FGPIOB                                   ((FGPIO_Type *)FGPIOB_BASE)
/** Peripheral FGPIOC base address */
#define FGPIOC_BASE                              (0xF8000080u)
/** Peripheral FGPIOC base pointer */
#define FGPIOC                                   ((FGPIO_Type *)FGPIOC_BASE)
/** Peripheral FGPIOD base address */
#define FGPIOD_BASE                              (0xF80000C0u)
/** Peripheral FGPIOD base pointer */
#define FGPIOD                                   ((FGPIO_Type *)FGPIOD_BASE)
/** Peripheral FGPIOE base address */
#define FGPIOE_BASE                              (0xF8000100u)
/** Peripheral FGPIOE base pointer */
#define FGPIOE                                   ((FGPIO_Type *)FGPIOE_BASE)
/** Array initializer of FGPIO peripheral base addresses */
#define FGPIO_BASE_ADDRS                         { FGPIOA_BASE, FGPIOB_BASE, FGPIOC_BASE, FGPIOD_BASE, FGPIOE_BASE }
/** Array initializer of FGPIO peripheral base pointers */
#define FGPIO_BASE_PTRS                          { FGPIOA, FGPIOB, FGPIOC, FGPIOD, FGPIOE }

/*!
 * @}
 */ /* end of group FGPIO_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- FLEXIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLEXIO_Peripheral_Access_Layer FLEXIO Peripheral Access Layer
 * @{
 */

/** FLEXIO - Register Layout Typedef */
typedef struct {
  __I  uint32_t VERID;                             /**< Version ID Register, offset: 0x0 */
  __I  uint32_t PARAM;                             /**< Parameter Register, offset: 0x4 */
  __IO uint32_t CTRL;                              /**< FlexIO Control Register, offset: 0x8 */
       uint8_t RESERVED_0[4];
  __IO uint32_t SHIFTSTAT;                         /**< Shifter Status Register, offset: 0x10 */
  __IO uint32_t SHIFTERR;                          /**< Shifter Error Register, offset: 0x14 */
  __IO uint32_t TIMSTAT;                           /**< Timer Status Register, offset: 0x18 */
       uint8_t RESERVED_1[4];
  __IO uint32_t SHIFTSIEN;                         /**< Shifter Status Interrupt Enable, offset: 0x20 */
  __IO uint32_t SHIFTEIEN;                         /**< Shifter Error Interrupt Enable, offset: 0x24 */
  __IO uint32_t TIMIEN;                            /**< Timer Interrupt Enable Register, offset: 0x28 */
       uint8_t RESERVED_2[4];
  __IO uint32_t SHIFTSDEN;                         /**< Shifter Status DMA Enable, offset: 0x30 */
       uint8_t RESERVED_3[76];
  __IO uint32_t SHIFTCTL[4];                       /**< Shifter Control N Register, array offset: 0x80, array step: 0x4 */
       uint8_t RESERVED_4[112];
  __IO uint32_t SHIFTCFG[4];                       /**< Shifter Configuration N Register, array offset: 0x100, array step: 0x4 */
       uint8_t RESERVED_5[240];
  __IO uint32_t SHIFTBUF[4];                       /**< Shifter Buffer N Register, array offset: 0x200, array step: 0x4 */
       uint8_t RESERVED_6[112];
  __IO uint32_t SHIFTBUFBIS[4];                    /**< Shifter Buffer N Bit Swapped Register, array offset: 0x280, array step: 0x4 */
       uint8_t RESERVED_7[112];
  __IO uint32_t SHIFTBUFBYS[4];                    /**< Shifter Buffer N Byte Swapped Register, array offset: 0x300, array step: 0x4 */
       uint8_t RESERVED_8[112];
  __IO uint32_t SHIFTBUFBBS[4];                    /**< Shifter Buffer N Bit Byte Swapped Register, array offset: 0x380, array step: 0x4 */
       uint8_t RESERVED_9[112];
  __IO uint32_t TIMCTL[4];                         /**< Timer Control N Register, array offset: 0x400, array step: 0x4 */
       uint8_t RESERVED_10[112];
  __IO uint32_t TIMCFG[4];                         /**< Timer Configuration N Register, array offset: 0x480, array step: 0x4 */
       uint8_t RESERVED_11[112];
  __IO uint32_t TIMCMP[4];                         /**< Timer Compare N Register, array offset: 0x500, array step: 0x4 */
} FLEXIO_Type;

/* ----------------------------------------------------------------------------
   -- FLEXIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLEXIO_Register_Masks FLEXIO Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */

#define FLEXIO_VERID_FEATURE_MASK                (0xFFFFU)
#define FLEXIO_VERID_FEATURE_SHIFT               (0U)
/*! FEATURE - Feature Specification Number
 *  0b0000000000000000..Standard features implemented.
 *  0b0000000000000001..Supports state, logic and parallel modes.
 */
#define FLEXIO_VERID_FEATURE(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_VERID_FEATURE_SHIFT)) & FLEXIO_VERID_FEATURE_MASK)

#define FLEXIO_VERID_MINOR_MASK                  (0xFF0000U)
#define FLEXIO_VERID_MINOR_SHIFT                 (16U)
/*! MINOR - Minor Version Number */
#define FLEXIO_VERID_MINOR(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_VERID_MINOR_SHIFT)) & FLEXIO_VERID_MINOR_MASK)

#define FLEXIO_VERID_MAJOR_MASK                  (0xFF000000U)
#define FLEXIO_VERID_MAJOR_SHIFT                 (24U)
/*! MAJOR - Major Version Number */
#define FLEXIO_VERID_MAJOR(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_VERID_MAJOR_SHIFT)) & FLEXIO_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */

#define FLEXIO_PARAM_SHIFTER_MASK                (0xFFU)
#define FLEXIO_PARAM_SHIFTER_SHIFT               (0U)
/*! SHIFTER - Shifter Number */
#define FLEXIO_PARAM_SHIFTER(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_PARAM_SHIFTER_SHIFT)) & FLEXIO_PARAM_SHIFTER_MASK)

#define FLEXIO_PARAM_TIMER_MASK                  (0xFF00U)
#define FLEXIO_PARAM_TIMER_SHIFT                 (8U)
/*! TIMER - Timer Number */
#define FLEXIO_PARAM_TIMER(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_PARAM_TIMER_SHIFT)) & FLEXIO_PARAM_TIMER_MASK)

#define FLEXIO_PARAM_PIN_MASK                    (0xFF0000U)
#define FLEXIO_PARAM_PIN_SHIFT                   (16U)
/*! PIN - Pin Number */
#define FLEXIO_PARAM_PIN(x)                      (((uint32_t)(((uint32_t)(x)) << FLEXIO_PARAM_PIN_SHIFT)) & FLEXIO_PARAM_PIN_MASK)

#define FLEXIO_PARAM_TRIGGER_MASK                (0xFF000000U)
#define FLEXIO_PARAM_TRIGGER_SHIFT               (24U)
/*! TRIGGER - Trigger Number */
#define FLEXIO_PARAM_TRIGGER(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_PARAM_TRIGGER_SHIFT)) & FLEXIO_PARAM_TRIGGER_MASK)
/*! @} */

/*! @name CTRL - FlexIO Control Register */
/*! @{ */

#define FLEXIO_CTRL_FLEXEN_MASK                  (0x1U)
#define FLEXIO_CTRL_FLEXEN_SHIFT                 (0U)
/*! FLEXEN - FlexIO Enable
 *  0b0..FlexIO module is disabled.
 *  0b1..FlexIO module is enabled.
 */
#define FLEXIO_CTRL_FLEXEN(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_FLEXEN_SHIFT)) & FLEXIO_CTRL_FLEXEN_MASK)

#define FLEXIO_CTRL_SWRST_MASK                   (0x2U)
#define FLEXIO_CTRL_SWRST_SHIFT                  (1U)
/*! SWRST - Software Reset
 *  0b0..Software reset is disabled
 *  0b1..Software reset is enabled, all FlexIO registers except the Control Register are reset.
 */
#define FLEXIO_CTRL_SWRST(x)                     (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_SWRST_SHIFT)) & FLEXIO_CTRL_SWRST_MASK)

#define FLEXIO_CTRL_FASTACC_MASK                 (0x4U)
#define FLEXIO_CTRL_FASTACC_SHIFT                (2U)
/*! FASTACC - Fast Access
 *  0b0..Configures for normal register accesses to FlexIO
 *  0b1..Configures for fast register accesses to FlexIO
 */
#define FLEXIO_CTRL_FASTACC(x)                   (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_FASTACC_SHIFT)) & FLEXIO_CTRL_FASTACC_MASK)

#define FLEXIO_CTRL_DBGE_MASK                    (0x40000000U)
#define FLEXIO_CTRL_DBGE_SHIFT                   (30U)
/*! DBGE - Debug Enable
 *  0b0..FlexIO is disabled in debug modes.
 *  0b1..FlexIO is enabled in debug modes
 */
#define FLEXIO_CTRL_DBGE(x)                      (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_DBGE_SHIFT)) & FLEXIO_CTRL_DBGE_MASK)

#define FLEXIO_CTRL_DOZEN_MASK                   (0x80000000U)
#define FLEXIO_CTRL_DOZEN_SHIFT                  (31U)
/*! DOZEN - Doze Enable
 *  0b0..FlexIO enabled in Doze modes.
 *  0b1..FlexIO disabled in Doze modes.
 */
#define FLEXIO_CTRL_DOZEN(x)                     (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_DOZEN_SHIFT)) & FLEXIO_CTRL_DOZEN_MASK)
/*! @} */

/*! @name SHIFTSTAT - Shifter Status Register */
/*! @{ */

#define FLEXIO_SHIFTSTAT_SSF_MASK                (0xFU)
#define FLEXIO_SHIFTSTAT_SSF_SHIFT               (0U)
/*! SSF - Shifter Status Flag
 *  0b0000..Status flag is clear
 *  0b0001..Status flag is set
 */
#define FLEXIO_SHIFTSTAT_SSF(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTSTAT_SSF_SHIFT)) & FLEXIO_SHIFTSTAT_SSF_MASK)
/*! @} */

/*! @name SHIFTERR - Shifter Error Register */
/*! @{ */

#define FLEXIO_SHIFTERR_SEF_MASK                 (0xFU)
#define FLEXIO_SHIFTERR_SEF_SHIFT                (0U)
/*! SEF - Shifter Error Flags
 *  0b0000..Shifter Error Flag is clear
 *  0b0001..Shifter Error Flag is set
 */
#define FLEXIO_SHIFTERR_SEF(x)                   (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTERR_SEF_SHIFT)) & FLEXIO_SHIFTERR_SEF_MASK)
/*! @} */

/*! @name TIMSTAT - Timer Status Register */
/*! @{ */

#define FLEXIO_TIMSTAT_TSF_MASK                  (0xFU)
#define FLEXIO_TIMSTAT_TSF_SHIFT                 (0U)
/*! TSF - Timer Status Flags
 *  0b0000..Timer Status Flag is clear
 *  0b0001..Timer Status Flag is set
 */
#define FLEXIO_TIMSTAT_TSF(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMSTAT_TSF_SHIFT)) & FLEXIO_TIMSTAT_TSF_MASK)
/*! @} */

/*! @name SHIFTSIEN - Shifter Status Interrupt Enable */
/*! @{ */

#define FLEXIO_SHIFTSIEN_SSIE_MASK               (0xFU)
#define FLEXIO_SHIFTSIEN_SSIE_SHIFT              (0U)
/*! SSIE - Shifter Status Interrupt Enable
 *  0b0000..Shifter Status Flag interrupt disabled
 *  0b0001..Shifter Status Flag interrupt enabled
 */
#define FLEXIO_SHIFTSIEN_SSIE(x)                 (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTSIEN_SSIE_SHIFT)) & FLEXIO_SHIFTSIEN_SSIE_MASK)
/*! @} */

/*! @name SHIFTEIEN - Shifter Error Interrupt Enable */
/*! @{ */

#define FLEXIO_SHIFTEIEN_SEIE_MASK               (0xFU)
#define FLEXIO_SHIFTEIEN_SEIE_SHIFT              (0U)
/*! SEIE - Shifter Error Interrupt Enable
 *  0b0000..Shifter Error Flag interrupt disabled
 *  0b0001..Shifter Error Flag interrupt enabled
 */
#define FLEXIO_SHIFTEIEN_SEIE(x)                 (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTEIEN_SEIE_SHIFT)) & FLEXIO_SHIFTEIEN_SEIE_MASK)
/*! @} */

/*! @name TIMIEN - Timer Interrupt Enable Register */
/*! @{ */

#define FLEXIO_TIMIEN_TEIE_MASK                  (0xFU)
#define FLEXIO_TIMIEN_TEIE_SHIFT                 (0U)
/*! TEIE - Timer Status Interrupt Enable
 *  0b0000..Timer Status Flag interrupt is disabled
 *  0b0001..Timer Status Flag interrupt is enabled
 */
#define FLEXIO_TIMIEN_TEIE(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMIEN_TEIE_SHIFT)) & FLEXIO_TIMIEN_TEIE_MASK)
/*! @} */

/*! @name SHIFTSDEN - Shifter Status DMA Enable */
/*! @{ */

#define FLEXIO_SHIFTSDEN_SSDE_MASK               (0xFU)
#define FLEXIO_SHIFTSDEN_SSDE_SHIFT              (0U)
/*! SSDE - Shifter Status DMA Enable
 *  0b0000..Shifter Status Flag DMA request is disabled
 *  0b0001..Shifter Status Flag DMA request is enabled
 */
#define FLEXIO_SHIFTSDEN_SSDE(x)                 (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTSDEN_SSDE_SHIFT)) & FLEXIO_SHIFTSDEN_SSDE_MASK)
/*! @} */

/*! @name SHIFTCTL - Shifter Control N Register */
/*! @{ */

#define FLEXIO_SHIFTCTL_SMOD_MASK                (0x7U)
#define FLEXIO_SHIFTCTL_SMOD_SHIFT               (0U)
/*! SMOD - Shifter Mode
 *  0b000..Disabled.
 *  0b001..Receive mode. Captures the current Shifter content into the SHIFTBUF on expiration of the Timer.
 *  0b010..Transmit mode. Load SHIFTBUF contents into the Shifter on expiration of the Timer.
 *  0b011..Reserved.
 *  0b100..Match Store mode. Shifter data is compared to SHIFTBUF content on expiration of the Timer.
 *  0b101..Match Continuous mode. Shifter data is continuously compared to SHIFTBUF contents.
 *  0b110..Reserved.
 *  0b111..Reserved.
 */
#define FLEXIO_SHIFTCTL_SMOD(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_SMOD_SHIFT)) & FLEXIO_SHIFTCTL_SMOD_MASK)

#define FLEXIO_SHIFTCTL_PINPOL_MASK              (0x80U)
#define FLEXIO_SHIFTCTL_PINPOL_SHIFT             (7U)
/*! PINPOL - Shifter Pin Polarity
 *  0b0..Pin is active high
 *  0b1..Pin is active low
 */
#define FLEXIO_SHIFTCTL_PINPOL(x)                (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_PINPOL_SHIFT)) & FLEXIO_SHIFTCTL_PINPOL_MASK)

#define FLEXIO_SHIFTCTL_PINSEL_MASK              (0x700U)
#define FLEXIO_SHIFTCTL_PINSEL_SHIFT             (8U)
/*! PINSEL - Shifter Pin Select */
#define FLEXIO_SHIFTCTL_PINSEL(x)                (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_PINSEL_SHIFT)) & FLEXIO_SHIFTCTL_PINSEL_MASK)

#define FLEXIO_SHIFTCTL_PINCFG_MASK              (0x30000U)
#define FLEXIO_SHIFTCTL_PINCFG_SHIFT             (16U)
/*! PINCFG - Shifter Pin Configuration
 *  0b00..Shifter pin output disabled
 *  0b01..Shifter pin open drain or bidirectional output enable
 *  0b10..Shifter pin bidirectional output data
 *  0b11..Shifter pin output
 */
#define FLEXIO_SHIFTCTL_PINCFG(x)                (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_PINCFG_SHIFT)) & FLEXIO_SHIFTCTL_PINCFG_MASK)

#define FLEXIO_SHIFTCTL_TIMPOL_MASK              (0x800000U)
#define FLEXIO_SHIFTCTL_TIMPOL_SHIFT             (23U)
/*! TIMPOL - Timer Polarity
 *  0b0..Shift on posedge of Shift clock
 *  0b1..Shift on negedge of Shift clock
 */
#define FLEXIO_SHIFTCTL_TIMPOL(x)                (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_TIMPOL_SHIFT)) & FLEXIO_SHIFTCTL_TIMPOL_MASK)

#define FLEXIO_SHIFTCTL_TIMSEL_MASK              (0x3000000U)
#define FLEXIO_SHIFTCTL_TIMSEL_SHIFT             (24U)
/*! TIMSEL - Timer Select */
#define FLEXIO_SHIFTCTL_TIMSEL(x)                (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_TIMSEL_SHIFT)) & FLEXIO_SHIFTCTL_TIMSEL_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTCTL */
#define FLEXIO_SHIFTCTL_COUNT                    (4U)

/*! @name SHIFTCFG - Shifter Configuration N Register */
/*! @{ */

#define FLEXIO_SHIFTCFG_SSTART_MASK              (0x3U)
#define FLEXIO_SHIFTCFG_SSTART_SHIFT             (0U)
/*! SSTART - Shifter Start bit
 *  0b00..Start bit disabled for transmitter/receiver/match store, transmitter loads data on enable
 *  0b01..Start bit disabled for transmitter/receiver/match store, transmitter loads data on first shift
 *  0b10..Transmitter outputs start bit value 0 before loading data on first shift, receiver/match store sets error flag if start bit is not 0
 *  0b11..Transmitter outputs start bit value 1 before loading data on first shift, receiver/match store sets error flag if start bit is not 1
 */
#define FLEXIO_SHIFTCFG_SSTART(x)                (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCFG_SSTART_SHIFT)) & FLEXIO_SHIFTCFG_SSTART_MASK)

#define FLEXIO_SHIFTCFG_SSTOP_MASK               (0x30U)
#define FLEXIO_SHIFTCFG_SSTOP_SHIFT              (4U)
/*! SSTOP - Shifter Stop bit
 *  0b00..Stop bit disabled for transmitter/receiver/match store
 *  0b01..Reserved for transmitter/receiver/match store
 *  0b10..Transmitter outputs stop bit value 0 on store, receiver/match store sets error flag if stop bit is not 0
 *  0b11..Transmitter outputs stop bit value 1 on store, receiver/match store sets error flag if stop bit is not 1
 */
#define FLEXIO_SHIFTCFG_SSTOP(x)                 (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCFG_SSTOP_SHIFT)) & FLEXIO_SHIFTCFG_SSTOP_MASK)

#define FLEXIO_SHIFTCFG_INSRC_MASK               (0x100U)
#define FLEXIO_SHIFTCFG_INSRC_SHIFT              (8U)
/*! INSRC - Input Source
 *  0b0..Pin
 *  0b1..Shifter N+1 Output
 */
#define FLEXIO_SHIFTCFG_INSRC(x)                 (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCFG_INSRC_SHIFT)) & FLEXIO_SHIFTCFG_INSRC_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTCFG */
#define FLEXIO_SHIFTCFG_COUNT                    (4U)

/*! @name SHIFTBUF - Shifter Buffer N Register */
/*! @{ */

#define FLEXIO_SHIFTBUF_SHIFTBUF_MASK            (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUF_SHIFTBUF_SHIFT           (0U)
/*! SHIFTBUF - Shift Buffer */
#define FLEXIO_SHIFTBUF_SHIFTBUF(x)              (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUF_SHIFTBUF_SHIFT)) & FLEXIO_SHIFTBUF_SHIFTBUF_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTBUF */
#define FLEXIO_SHIFTBUF_COUNT                    (4U)

/*! @name SHIFTBUFBIS - Shifter Buffer N Bit Swapped Register */
/*! @{ */

#define FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS_MASK      (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS_SHIFT     (0U)
/*! SHIFTBUFBIS - Shift Buffer */
#define FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS(x)        (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS_SHIFT)) & FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTBUFBIS */
#define FLEXIO_SHIFTBUFBIS_COUNT                 (4U)

/*! @name SHIFTBUFBYS - Shifter Buffer N Byte Swapped Register */
/*! @{ */

#define FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS_MASK      (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS_SHIFT     (0U)
/*! SHIFTBUFBYS - Shift Buffer */
#define FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS(x)        (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS_SHIFT)) & FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTBUFBYS */
#define FLEXIO_SHIFTBUFBYS_COUNT                 (4U)

/*! @name SHIFTBUFBBS - Shifter Buffer N Bit Byte Swapped Register */
/*! @{ */

#define FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS_MASK      (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS_SHIFT     (0U)
/*! SHIFTBUFBBS - Shift Buffer */
#define FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS(x)        (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS_SHIFT)) & FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTBUFBBS */
#define FLEXIO_SHIFTBUFBBS_COUNT                 (4U)

/*! @name TIMCTL - Timer Control N Register */
/*! @{ */

#define FLEXIO_TIMCTL_TIMOD_MASK                 (0x3U)
#define FLEXIO_TIMCTL_TIMOD_SHIFT                (0U)
/*! TIMOD - Timer Mode
 *  0b00..Timer Disabled.
 *  0b01..Dual 8-bit counters baud/bit mode.
 *  0b10..Dual 8-bit counters PWM mode.
 *  0b11..Single 16-bit counter mode.
 */
#define FLEXIO_TIMCTL_TIMOD(x)                   (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_TIMOD_SHIFT)) & FLEXIO_TIMCTL_TIMOD_MASK)

#define FLEXIO_TIMCTL_PINPOL_MASK                (0x80U)
#define FLEXIO_TIMCTL_PINPOL_SHIFT               (7U)
/*! PINPOL - Timer Pin Polarity
 *  0b0..Pin is active high
 *  0b1..Pin is active low
 */
#define FLEXIO_TIMCTL_PINPOL(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_PINPOL_SHIFT)) & FLEXIO_TIMCTL_PINPOL_MASK)

#define FLEXIO_TIMCTL_PINSEL_MASK                (0x700U)
#define FLEXIO_TIMCTL_PINSEL_SHIFT               (8U)
/*! PINSEL - Timer Pin Select */
#define FLEXIO_TIMCTL_PINSEL(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_PINSEL_SHIFT)) & FLEXIO_TIMCTL_PINSEL_MASK)

#define FLEXIO_TIMCTL_PINCFG_MASK                (0x30000U)
#define FLEXIO_TIMCTL_PINCFG_SHIFT               (16U)
/*! PINCFG - Timer Pin Configuration
 *  0b00..Timer pin output disabled
 *  0b01..Timer pin open drain or bidirectional output enable
 *  0b10..Timer pin bidirectional output data
 *  0b11..Timer pin output
 */
#define FLEXIO_TIMCTL_PINCFG(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_PINCFG_SHIFT)) & FLEXIO_TIMCTL_PINCFG_MASK)

#define FLEXIO_TIMCTL_TRGSRC_MASK                (0x400000U)
#define FLEXIO_TIMCTL_TRGSRC_SHIFT               (22U)
/*! TRGSRC - Trigger Source
 *  0b0..External trigger selected
 *  0b1..Internal trigger selected
 */
#define FLEXIO_TIMCTL_TRGSRC(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_TRGSRC_SHIFT)) & FLEXIO_TIMCTL_TRGSRC_MASK)

#define FLEXIO_TIMCTL_TRGPOL_MASK                (0x800000U)
#define FLEXIO_TIMCTL_TRGPOL_SHIFT               (23U)
/*! TRGPOL - Trigger Polarity
 *  0b0..Trigger active high
 *  0b1..Trigger active low
 */
#define FLEXIO_TIMCTL_TRGPOL(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_TRGPOL_SHIFT)) & FLEXIO_TIMCTL_TRGPOL_MASK)

#define FLEXIO_TIMCTL_TRGSEL_MASK                (0xF000000U)
#define FLEXIO_TIMCTL_TRGSEL_SHIFT               (24U)
/*! TRGSEL - Trigger Select */
#define FLEXIO_TIMCTL_TRGSEL(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_TRGSEL_SHIFT)) & FLEXIO_TIMCTL_TRGSEL_MASK)
/*! @} */

/* The count of FLEXIO_TIMCTL */
#define FLEXIO_TIMCTL_COUNT                      (4U)

/*! @name TIMCFG - Timer Configuration N Register */
/*! @{ */

#define FLEXIO_TIMCFG_TSTART_MASK                (0x2U)
#define FLEXIO_TIMCFG_TSTART_SHIFT               (1U)
/*! TSTART - Timer Start Bit
 *  0b0..Start bit disabled
 *  0b1..Start bit enabled
 */
#define FLEXIO_TIMCFG_TSTART(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TSTART_SHIFT)) & FLEXIO_TIMCFG_TSTART_MASK)

#define FLEXIO_TIMCFG_TSTOP_MASK                 (0x30U)
#define FLEXIO_TIMCFG_TSTOP_SHIFT                (4U)
/*! TSTOP - Timer Stop Bit
 *  0b00..Stop bit disabled
 *  0b01..Stop bit is enabled on timer compare
 *  0b10..Stop bit is enabled on timer disable
 *  0b11..Stop bit is enabled on timer compare and timer disable
 */
#define FLEXIO_TIMCFG_TSTOP(x)                   (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TSTOP_SHIFT)) & FLEXIO_TIMCFG_TSTOP_MASK)

#define FLEXIO_TIMCFG_TIMENA_MASK                (0x700U)
#define FLEXIO_TIMCFG_TIMENA_SHIFT               (8U)
/*! TIMENA - Timer Enable
 *  0b000..Timer always enabled
 *  0b001..Timer enabled on Timer N-1 enable
 *  0b010..Timer enabled on Trigger high
 *  0b011..Timer enabled on Trigger high and Pin high
 *  0b100..Timer enabled on Pin rising edge
 *  0b101..Timer enabled on Pin rising edge and Trigger high
 *  0b110..Timer enabled on Trigger rising edge
 *  0b111..Timer enabled on Trigger rising or falling edge
 */
#define FLEXIO_TIMCFG_TIMENA(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMENA_SHIFT)) & FLEXIO_TIMCFG_TIMENA_MASK)

#define FLEXIO_TIMCFG_TIMDIS_MASK                (0x7000U)
#define FLEXIO_TIMCFG_TIMDIS_SHIFT               (12U)
/*! TIMDIS - Timer Disable
 *  0b000..Timer never disabled
 *  0b001..Timer disabled on Timer N-1 disable
 *  0b010..Timer disabled on Timer compare
 *  0b011..Timer disabled on Timer compare and Trigger Low
 *  0b100..Timer disabled on Pin rising or falling edge
 *  0b101..Timer disabled on Pin rising or falling edge provided Trigger is high
 *  0b110..Timer disabled on Trigger falling edge
 *  0b111..Reserved
 */
#define FLEXIO_TIMCFG_TIMDIS(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMDIS_SHIFT)) & FLEXIO_TIMCFG_TIMDIS_MASK)

#define FLEXIO_TIMCFG_TIMRST_MASK                (0x70000U)
#define FLEXIO_TIMCFG_TIMRST_SHIFT               (16U)
/*! TIMRST - Timer Reset
 *  0b000..Timer never reset
 *  0b001..Reserved
 *  0b010..Timer reset on Timer Pin equal to Timer Output
 *  0b011..Timer reset on Timer Trigger equal to Timer Output
 *  0b100..Timer reset on Timer Pin rising edge
 *  0b101..Reserved
 *  0b110..Timer reset on Trigger rising edge
 *  0b111..Timer reset on Trigger rising or falling edge
 */
#define FLEXIO_TIMCFG_TIMRST(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMRST_SHIFT)) & FLEXIO_TIMCFG_TIMRST_MASK)

#define FLEXIO_TIMCFG_TIMDEC_MASK                (0x300000U)
#define FLEXIO_TIMCFG_TIMDEC_SHIFT               (20U)
/*! TIMDEC - Timer Decrement
 *  0b00..Decrement counter on FlexIO clock, Shift clock equals Timer output.
 *  0b01..Decrement counter on Trigger input (both edges), Shift clock equals Timer output.
 *  0b10..Decrement counter on Pin input (both edges), Shift clock equals Pin input.
 *  0b11..Decrement counter on Trigger input (both edges), Shift clock equals Trigger input.
 */
#define FLEXIO_TIMCFG_TIMDEC(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMDEC_SHIFT)) & FLEXIO_TIMCFG_TIMDEC_MASK)

#define FLEXIO_TIMCFG_TIMOUT_MASK                (0x3000000U)
#define FLEXIO_TIMCFG_TIMOUT_SHIFT               (24U)
/*! TIMOUT - Timer Output
 *  0b00..Timer output is logic one when enabled and is not affected by timer reset
 *  0b01..Timer output is logic zero when enabled and is not affected by timer reset
 *  0b10..Timer output is logic one when enabled and on timer reset
 *  0b11..Timer output is logic zero when enabled and on timer reset
 */
#define FLEXIO_TIMCFG_TIMOUT(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMOUT_SHIFT)) & FLEXIO_TIMCFG_TIMOUT_MASK)
/*! @} */

/* The count of FLEXIO_TIMCFG */
#define FLEXIO_TIMCFG_COUNT                      (4U)

/*! @name TIMCMP - Timer Compare N Register */
/*! @{ */

#define FLEXIO_TIMCMP_CMP_MASK                   (0xFFFFU)
#define FLEXIO_TIMCMP_CMP_SHIFT                  (0U)
/*! CMP - Timer Compare Value */
#define FLEXIO_TIMCMP_CMP(x)                     (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCMP_CMP_SHIFT)) & FLEXIO_TIMCMP_CMP_MASK)
/*! @} */

/* The count of FLEXIO_TIMCMP */
#define FLEXIO_TIMCMP_COUNT                      (4U)


/*!
 * @}
 */ /* end of group FLEXIO_Register_Masks */


/* FLEXIO - Peripheral instance base addresses */
/** Peripheral FLEXIO base address */
#define FLEXIO_BASE                              (0x4005F000u)
/** Peripheral FLEXIO base pointer */
#define FLEXIO                                   ((FLEXIO_Type *)FLEXIO_BASE)
/** Array initializer of FLEXIO peripheral base addresses */
#define FLEXIO_BASE_ADDRS                        { FLEXIO_BASE }
/** Array initializer of FLEXIO peripheral base pointers */
#define FLEXIO_BASE_PTRS                         { FLEXIO }
/** Interrupt vectors for the FLEXIO peripheral type */
#define FLEXIO_IRQS                              { UART2_FLEXIO_IRQn }

/*!
 * @}
 */ /* end of group FLEXIO_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- FTFA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFA_Peripheral_Access_Layer FTFA Peripheral Access Layer
 * @{
 */

/** FTFA - Register Layout Typedef */
typedef struct {
  __IO uint8_t FSTAT;                              /**< Flash Status Register, offset: 0x0 */
  __IO uint8_t FCNFG;                              /**< Flash Configuration Register, offset: 0x1 */
  __I  uint8_t FSEC;                               /**< Flash Security Register, offset: 0x2 */
  __I  uint8_t FOPT;                               /**< Flash Option Register, offset: 0x3 */
  __IO uint8_t FCCOB3;                             /**< Flash Common Command Object Registers, offset: 0x4 */
  __IO uint8_t FCCOB2;                             /**< Flash Common Command Object Registers, offset: 0x5 */
  __IO uint8_t FCCOB1;                             /**< Flash Common Command Object Registers, offset: 0x6 */
  __IO uint8_t FCCOB0;                             /**< Flash Common Command Object Registers, offset: 0x7 */
  __IO uint8_t FCCOB7;                             /**< Flash Common Command Object Registers, offset: 0x8 */
  __IO uint8_t FCCOB6;                             /**< Flash Common Command Object Registers, offset: 0x9 */
  __IO uint8_t FCCOB5;                             /**< Flash Common Command Object Registers, offset: 0xA */
  __IO uint8_t FCCOB4;                             /**< Flash Common Command Object Registers, offset: 0xB */
  __IO uint8_t FCCOBB;                             /**< Flash Common Command Object Registers, offset: 0xC */
  __IO uint8_t FCCOBA;                             /**< Flash Common Command Object Registers, offset: 0xD */
  __IO uint8_t FCCOB9;                             /**< Flash Common Command Object Registers, offset: 0xE */
  __IO uint8_t FCCOB8;                             /**< Flash Common Command Object Registers, offset: 0xF */
  __IO uint8_t FPROT3;                             /**< Program Flash Protection Registers, offset: 0x10 */
  __IO uint8_t FPROT2;                             /**< Program Flash Protection Registers, offset: 0x11 */
  __IO uint8_t FPROT1;                             /**< Program Flash Protection Registers, offset: 0x12 */
  __IO uint8_t FPROT0;                             /**< Program Flash Protection Registers, offset: 0x13 */
} FTFA_Type;

/* ----------------------------------------------------------------------------
   -- FTFA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFA_Register_Masks FTFA Register Masks
 * @{
 */

/*! @name FSTAT - Flash Status Register */
/*! @{ */

#define FTFA_FSTAT_MGSTAT0_MASK                  (0x1U)
#define FTFA_FSTAT_MGSTAT0_SHIFT                 (0U)
/*! MGSTAT0 - Memory Controller Command Completion Status Flag */
#define FTFA_FSTAT_MGSTAT0(x)                    (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_MGSTAT0_SHIFT)) & FTFA_FSTAT_MGSTAT0_MASK)

#define FTFA_FSTAT_FPVIOL_MASK                   (0x10U)
#define FTFA_FSTAT_FPVIOL_SHIFT                  (4U)
/*! FPVIOL - Flash Protection Violation Flag
 *  0b0..No protection violation detected
 *  0b1..Protection violation detected
 */
#define FTFA_FSTAT_FPVIOL(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_FPVIOL_SHIFT)) & FTFA_FSTAT_FPVIOL_MASK)

#define FTFA_FSTAT_ACCERR_MASK                   (0x20U)
#define FTFA_FSTAT_ACCERR_SHIFT                  (5U)
/*! ACCERR - Flash Access Error Flag
 *  0b0..No access error detected
 *  0b1..Access error detected
 */
#define FTFA_FSTAT_ACCERR(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_ACCERR_SHIFT)) & FTFA_FSTAT_ACCERR_MASK)

#define FTFA_FSTAT_RDCOLERR_MASK                 (0x40U)
#define FTFA_FSTAT_RDCOLERR_SHIFT                (6U)
/*! RDCOLERR - Flash Read Collision Error Flag
 *  0b0..No collision error detected
 *  0b1..Collision error detected
 */
#define FTFA_FSTAT_RDCOLERR(x)                   (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_RDCOLERR_SHIFT)) & FTFA_FSTAT_RDCOLERR_MASK)

#define FTFA_FSTAT_CCIF_MASK                     (0x80U)
#define FTFA_FSTAT_CCIF_SHIFT                    (7U)
/*! CCIF - Command Complete Interrupt Flag
 *  0b0..Flash command in progress
 *  0b1..Flash command has completed
 */
#define FTFA_FSTAT_CCIF(x)                       (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_CCIF_SHIFT)) & FTFA_FSTAT_CCIF_MASK)
/*! @} */

/*! @name FCNFG - Flash Configuration Register */
/*! @{ */

#define FTFA_FCNFG_ERSSUSP_MASK                  (0x10U)
#define FTFA_FCNFG_ERSSUSP_SHIFT                 (4U)
/*! ERSSUSP - Erase Suspend
 *  0b0..No suspend requested
 *  0b1..Suspend the current Erase Flash Sector command execution.
 */
#define FTFA_FCNFG_ERSSUSP(x)                    (((uint8_t)(((uint8_t)(x)) << FTFA_FCNFG_ERSSUSP_SHIFT)) & FTFA_FCNFG_ERSSUSP_MASK)

#define FTFA_FCNFG_ERSAREQ_MASK                  (0x20U)
#define FTFA_FCNFG_ERSAREQ_SHIFT                 (5U)
/*! ERSAREQ - Erase All Request
 *  0b0..No request or request complete
 *  0b1..Request to: run the Erase All Blocks command, verify the erased state, program the security byte in the
 *       Flash Configuration Field to the unsecure state, and release MCU security by setting the FSEC[SEC] field to
 *       the unsecure state.
 */
#define FTFA_FCNFG_ERSAREQ(x)                    (((uint8_t)(((uint8_t)(x)) << FTFA_FCNFG_ERSAREQ_SHIFT)) & FTFA_FCNFG_ERSAREQ_MASK)

#define FTFA_FCNFG_RDCOLLIE_MASK                 (0x40U)
#define FTFA_FCNFG_RDCOLLIE_SHIFT                (6U)
/*! RDCOLLIE - Read Collision Error Interrupt Enable
 *  0b0..Read collision error interrupt disabled
 *  0b1..Read collision error interrupt enabled. An interrupt request is generated whenever a flash memory read
 *       collision error is detected (see the description of FSTAT[RDCOLERR]).
 */
#define FTFA_FCNFG_RDCOLLIE(x)                   (((uint8_t)(((uint8_t)(x)) << FTFA_FCNFG_RDCOLLIE_SHIFT)) & FTFA_FCNFG_RDCOLLIE_MASK)

#define FTFA_FCNFG_CCIE_MASK                     (0x80U)
#define FTFA_FCNFG_CCIE_SHIFT                    (7U)
/*! CCIE - Command Complete Interrupt Enable
 *  0b0..Command complete interrupt disabled
 *  0b1..Command complete interrupt enabled. An interrupt request is generated whenever the FSTAT[CCIF] flag is set.
 */
#define FTFA_FCNFG_CCIE(x)                       (((uint8_t)(((uint8_t)(x)) << FTFA_FCNFG_CCIE_SHIFT)) & FTFA_FCNFG_CCIE_MASK)
/*! @} */

/*! @name FSEC - Flash Security Register */
/*! @{ */

#define FTFA_FSEC_SEC_MASK                       (0x3U)
#define FTFA_FSEC_SEC_SHIFT                      (0U)
/*! SEC - Flash Security
 *  0b00..MCU security status is secure.
 *  0b01..MCU security status is secure.
 *  0b10..MCU security status is unsecure. (The standard shipping condition of the flash memory module is unsecure.)
 *  0b11..MCU security status is secure.
 */
#define FTFA_FSEC_SEC(x)                         (((uint8_t)(((uint8_t)(x)) << FTFA_FSEC_SEC_SHIFT)) & FTFA_FSEC_SEC_MASK)

#define FTFA_FSEC_FSLACC_MASK                    (0xCU)
#define FTFA_FSEC_FSLACC_SHIFT                   (2U)
/*! FSLACC - Freescale Failure Analysis Access Code
 *  0b00..Freescale factory access granted
 *  0b01..Freescale factory access denied
 *  0b10..Freescale factory access denied
 *  0b11..Freescale factory access granted
 */
#define FTFA_FSEC_FSLACC(x)                      (((uint8_t)(((uint8_t)(x)) << FTFA_FSEC_FSLACC_SHIFT)) & FTFA_FSEC_FSLACC_MASK)

#define FTFA_FSEC_MEEN_MASK                      (0x30U)
#define FTFA_FSEC_MEEN_SHIFT                     (4U)
/*! MEEN - Mass Erase Enable Bits
 *  0b00..Mass erase is enabled
 *  0b01..Mass erase is enabled
 *  0b10..Mass erase is disabled
 *  0b11..Mass erase is enabled
 */
#define FTFA_FSEC_MEEN(x)                        (((uint8_t)(((uint8_t)(x)) << FTFA_FSEC_MEEN_SHIFT)) & FTFA_FSEC_MEEN_MASK)

#define FTFA_FSEC_KEYEN_MASK                     (0xC0U)
#define FTFA_FSEC_KEYEN_SHIFT                    (6U)
/*! KEYEN - Backdoor Key Security Enable
 *  0b00..Backdoor key access disabled
 *  0b01..Backdoor key access disabled (preferred KEYEN state to disable backdoor key access)
 *  0b10..Backdoor key access enabled
 *  0b11..Backdoor key access disabled
 */
#define FTFA_FSEC_KEYEN(x)                       (((uint8_t)(((uint8_t)(x)) << FTFA_FSEC_KEYEN_SHIFT)) & FTFA_FSEC_KEYEN_MASK)
/*! @} */

/*! @name FOPT - Flash Option Register */
/*! @{ */

#define FTFA_FOPT_OPT_MASK                       (0xFFU)
#define FTFA_FOPT_OPT_SHIFT                      (0U)
/*! OPT - Nonvolatile Option */
#define FTFA_FOPT_OPT(x)                         (((uint8_t)(((uint8_t)(x)) << FTFA_FOPT_OPT_SHIFT)) & FTFA_FOPT_OPT_MASK)
/*! @} */

/*! @name FCCOB3 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB3_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB3_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB3_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB3_CCOBn_SHIFT)) & FTFA_FCCOB3_CCOBn_MASK)
/*! @} */

/*! @name FCCOB2 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB2_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB2_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB2_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB2_CCOBn_SHIFT)) & FTFA_FCCOB2_CCOBn_MASK)
/*! @} */

/*! @name FCCOB1 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB1_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB1_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB1_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB1_CCOBn_SHIFT)) & FTFA_FCCOB1_CCOBn_MASK)
/*! @} */

/*! @name FCCOB0 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB0_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB0_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB0_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB0_CCOBn_SHIFT)) & FTFA_FCCOB0_CCOBn_MASK)
/*! @} */

/*! @name FCCOB7 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB7_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB7_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB7_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB7_CCOBn_SHIFT)) & FTFA_FCCOB7_CCOBn_MASK)
/*! @} */

/*! @name FCCOB6 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB6_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB6_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB6_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB6_CCOBn_SHIFT)) & FTFA_FCCOB6_CCOBn_MASK)
/*! @} */

/*! @name FCCOB5 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB5_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB5_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB5_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB5_CCOBn_SHIFT)) & FTFA_FCCOB5_CCOBn_MASK)
/*! @} */

/*! @name FCCOB4 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB4_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB4_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB4_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB4_CCOBn_SHIFT)) & FTFA_FCCOB4_CCOBn_MASK)
/*! @} */

/*! @name FCCOBB - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOBB_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOBB_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOBB_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOBB_CCOBn_SHIFT)) & FTFA_FCCOBB_CCOBn_MASK)
/*! @} */

/*! @name FCCOBA - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOBA_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOBA_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOBA_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOBA_CCOBn_SHIFT)) & FTFA_FCCOBA_CCOBn_MASK)
/*! @} */

/*! @name FCCOB9 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB9_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB9_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB9_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB9_CCOBn_SHIFT)) & FTFA_FCCOB9_CCOBn_MASK)
/*! @} */

/*! @name FCCOB8 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB8_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB8_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB8_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB8_CCOBn_SHIFT)) & FTFA_FCCOB8_CCOBn_MASK)
/*! @} */

/*! @name FPROT3 - Program Flash Protection Registers */
/*! @{ */

#define FTFA_FPROT3_PROT_MASK                    (0xFFU)
#define FTFA_FPROT3_PROT_SHIFT                   (0U)
/*! PROT - Program Flash Region Protect
 *  0b00000000..Program flash region is protected.
 *  0b00000001..Program flash region is not protected
 */
#define FTFA_FPROT3_PROT(x)                      (((uint8_t)(((uint8_t)(x)) << FTFA_FPROT3_PROT_SHIFT)) & FTFA_FPROT3_PROT_MASK)
/*! @} */

/*! @name FPROT2 - Program Flash Protection Registers */
/*! @{ */

#define FTFA_FPROT2_PROT_MASK                    (0xFFU)
#define FTFA_FPROT2_PROT_SHIFT                   (0U)
/*! PROT - Program Flash Region Protect
 *  0b00000000..Program flash region is protected.
 *  0b00000001..Program flash region is not protected
 */
#define FTFA_FPROT2_PROT(x)                      (((uint8_t)(((uint8_t)(x)) << FTFA_FPROT2_PROT_SHIFT)) & FTFA_FPROT2_PROT_MASK)
/*! @} */

/*! @name FPROT1 - Program Flash Protection Registers */
/*! @{ */

#define FTFA_FPROT1_PROT_MASK                    (0xFFU)
#define FTFA_FPROT1_PROT_SHIFT                   (0U)
/*! PROT - Program Flash Region Protect
 *  0b00000000..Program flash region is protected.
 *  0b00000001..Program flash region is not protected
 */
#define FTFA_FPROT1_PROT(x)                      (((uint8_t)(((uint8_t)(x)) << FTFA_FPROT1_PROT_SHIFT)) & FTFA_FPROT1_PROT_MASK)
/*! @} */

/*! @name FPROT0 - Program Flash Protection Registers */
/*! @{ */

#define FTFA_FPROT0_PROT_MASK                    (0xFFU)
#define FTFA_FPROT0_PROT_SHIFT                   (0U)
/*! PROT - Program Flash Region Protect
 *  0b00000000..Program flash region is protected.
 *  0b00000001..Program flash region is not protected
 */
#define FTFA_FPROT0_PROT(x)                      (((uint8_t)(((uint8_t)(x)) << FTFA_FPROT0_PROT_SHIFT)) & FTFA_FPROT0_PROT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group FTFA_Register_Masks */


/* FTFA - Peripheral instance base addresses */
/** Peripheral FTFA base address */
#define FTFA_BASE                                (0x40020000u)
/** Peripheral FTFA base pointer */
#define FTFA                                     ((FTFA_Type *)FTFA_BASE)
/** Array initializer of FTFA peripheral base addresses */
#define FTFA_BASE_ADDRS                          { FTFA_BASE }
/** Array initializer of FTFA peripheral base pointers */
#define FTFA_BASE_PTRS                           { FTFA }
/** Interrupt vectors for the FTFA peripheral type */
#define FTFA_COMMAND_COMPLETE_IRQS               { FTFA_IRQn }

/*!
 * @}
 */ /* end of group FTFA_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- GPIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer
 * @{
 */

/** GPIO - Register Layout Typedef */
typedef struct {
  __IO uint32_t PDOR;                              /**< Port Data Output Register, offset: 0x0 */
  __O  uint32_t PSOR;                              /**< Port Set Output Register, offset: 0x4 */
  __O  uint32_t PCOR;                              /**< Port Clear Output Register, offset: 0x8 */
  __O  uint32_t PTOR;                              /**< Port Toggle Output Register, offset: 0xC */
  __I  uint32_t PDIR;                              /**< Port Data Input Register, offset: 0x10 */
  __IO uint32_t PDDR;                              /**< Port Data Direction Register, offset: 0x14 */
} GPIO_Type;

/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Masks GPIO Register Masks
 * @{
 */

/*! @name PDOR - Port Data Output Register */
/*! @{ */

#define GPIO_PDOR_PDO_MASK                       (0xFFFFFFFFU)
#define GPIO_PDOR_PDO_SHIFT                      (0U)
/*! PDO - Port Data Output
 *  0b00000000000000000000000000000000..Logic level 0 is driven on pin, provided pin is configured for general-purpose output.
 *  0b00000000000000000000000000000001..Logic level 1 is driven on pin, provided pin is configured for general-purpose output.
 */
#define GPIO_PDOR_PDO(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_PDOR_PDO_SHIFT)) & GPIO_PDOR_PDO_MASK)
/*! @} */

/*! @name PSOR - Port Set Output Register */
/*! @{ */

#define GPIO_PSOR_PTSO_MASK                      (0xFFFFFFFFU)
#define GPIO_PSOR_PTSO_SHIFT                     (0U)
/*! PTSO - Port Set Output
 *  0b00000000000000000000000000000000..Corresponding bit in PDORn does not change.
 *  0b00000000000000000000000000000001..Corresponding bit in PDORn is set to logic 1.
 */
#define GPIO_PSOR_PTSO(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_PSOR_PTSO_SHIFT)) & GPIO_PSOR_PTSO_MASK)
/*! @} */

/*! @name PCOR - Port Clear Output Register */
/*! @{ */

#define GPIO_PCOR_PTCO_MASK                      (0xFFFFFFFFU)
#define GPIO_PCOR_PTCO_SHIFT                     (0U)
/*! PTCO - Port Clear Output
 *  0b00000000000000000000000000000000..Corresponding bit in PDORn does not change.
 *  0b00000000000000000000000000000001..Corresponding bit in PDORn is cleared to logic 0.
 */
#define GPIO_PCOR_PTCO(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_PCOR_PTCO_SHIFT)) & GPIO_PCOR_PTCO_MASK)
/*! @} */

/*! @name PTOR - Port Toggle Output Register */
/*! @{ */

#define GPIO_PTOR_PTTO_MASK                      (0xFFFFFFFFU)
#define GPIO_PTOR_PTTO_SHIFT                     (0U)
/*! PTTO - Port Toggle Output
 *  0b00000000000000000000000000000000..Corresponding bit in PDORn does not change.
 *  0b00000000000000000000000000000001..Corresponding bit in PDORn is set to the inverse of its existing logic state.
 */
#define GPIO_PTOR_PTTO(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_PTOR_PTTO_SHIFT)) & GPIO_PTOR_PTTO_MASK)
/*! @} */

/*! @name PDIR - Port Data Input Register */
/*! @{ */

#define GPIO_PDIR_PDI_MASK                       (0xFFFFFFFFU)
#define GPIO_PDIR_PDI_SHIFT                      (0U)
/*! PDI - Port Data Input
 *  0b00000000000000000000000000000000..Pin logic level is logic 0, or is not configured for use by digital function.
 *  0b00000000000000000000000000000001..Pin logic level is logic 1.
 */
#define GPIO_PDIR_PDI(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_PDIR_PDI_SHIFT)) & GPIO_PDIR_PDI_MASK)
/*! @} */

/*! @name PDDR - Port Data Direction Register */
/*! @{ */

#define GPIO_PDDR_PDD_MASK                       (0xFFFFFFFFU)
#define GPIO_PDDR_PDD_SHIFT                      (0U)
/*! PDD - Port Data Direction
 *  0b00000000000000000000000000000000..Pin is configured as general-purpose input, for the GPIO function.
 *  0b00000000000000000000000000000001..Pin is configured as general-purpose output, for the GPIO function.
 */
#define GPIO_PDDR_PDD(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_PDDR_PDD_SHIFT)) & GPIO_PDDR_PDD_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group GPIO_Register_Masks */


/* GPIO - Peripheral instance base addresses */
/** Peripheral GPIOA base address */
#define GPIOA_BASE                               (0x400FF000u)
/** Peripheral GPIOA base pointer */
#define GPIOA                                    ((GPIO_Type *)GPIOA_BASE)
/** Peripheral GPIOB base address */
#define GPIOB_BASE                               (0x400FF040u)
/** Peripheral GPIOB base pointer */
#define GPIOB                                    ((GPIO_Type *)GPIOB_BASE)
/** Peripheral GPIOC base address */
#define GPIOC_BASE                               (0x400FF080u)
/** Peripheral GPIOC base pointer */
#define GPIOC                                    ((GPIO_Type *)GPIOC_BASE)
/** Peripheral GPIOD base address */
#define GPIOD_BASE                               (0x400FF0C0u)
/** Peripheral GPIOD base pointer */
#define GPIOD                                    ((GPIO_Type *)GPIOD_BASE)
/** Peripheral GPIOE base address */
#define GPIOE_BASE                               (0x400FF100u)
/** Peripheral GPIOE base pointer */
#define GPIOE                                    ((GPIO_Type *)GPIOE_BASE)
/** Array initializer of GPIO peripheral base addresses */
#define GPIO_BASE_ADDRS                          { GPIOA_BASE, GPIOB_BASE, GPIOC_BASE, GPIOD_BASE, GPIOE_BASE }
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE }

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
  __IO uint8_t A1;                                 /**< I2C Address Register 1, offset: 0x0 */
  __IO uint8_t F;                                  /**< I2C Frequency Divider register, offset: 0x1 */
  __IO uint8_t C1;                                 /**< I2C Control Register 1, offset: 0x2 */
  __IO uint8_t S;                                  /**< I2C Status register, offset: 0x3 */
  __IO uint8_t D;                                  /**< I2C Data I/O register, offset: 0x4 */
  __IO uint8_t C2;                                 /**< I2C Control Register 2, offset: 0x5 */
  __IO uint8_t FLT;                                /**< I2C Programmable Input Glitch Filter Register, offset: 0x6 */
  __IO uint8_t RA;                                 /**< I2C Range Address register, offset: 0x7 */
  __IO uint8_t SMB;                                /**< I2C SMBus Control and Status register, offset: 0x8 */
  __IO uint8_t A2;                                 /**< I2C Address Register 2, offset: 0x9 */
  __IO uint8_t SLTH;                               /**< I2C SCL Low Timeout Register High, offset: 0xA */
  __IO uint8_t SLTL;                               /**< I2C SCL Low Timeout Register Low, offset: 0xB */
  __IO uint8_t S2;                                 /**< I2C Status register 2, offset: 0xC */
} I2C_Type;

/* ----------------------------------------------------------------------------
   -- I2C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Masks I2C Register Masks
 * @{
 */

/*! @name A1 - I2C Address Register 1 */
/*! @{ */

#define I2C_A1_AD_MASK                           (0xFEU)
#define I2C_A1_AD_SHIFT                          (1U)
/*! AD - Address */
#define I2C_A1_AD(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_A1_AD_SHIFT)) & I2C_A1_AD_MASK)
/*! @} */

/*! @name F - I2C Frequency Divider register */
/*! @{ */

#define I2C_F_ICR_MASK                           (0x3FU)
#define I2C_F_ICR_SHIFT                          (0U)
/*! ICR - ClockRate */
#define I2C_F_ICR(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_F_ICR_SHIFT)) & I2C_F_ICR_MASK)

#define I2C_F_MULT_MASK                          (0xC0U)
#define I2C_F_MULT_SHIFT                         (6U)
/*! MULT - Multiplier Factor
 *  0b00..mul = 1
 *  0b01..mul = 2
 *  0b10..mul = 4
 *  0b11..Reserved
 */
#define I2C_F_MULT(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_F_MULT_SHIFT)) & I2C_F_MULT_MASK)
/*! @} */

/*! @name C1 - I2C Control Register 1 */
/*! @{ */

#define I2C_C1_DMAEN_MASK                        (0x1U)
#define I2C_C1_DMAEN_SHIFT                       (0U)
/*! DMAEN - DMA Enable
 *  0b0..All DMA signalling disabled.
 *  0b1..DMA transfer is enabled. While SMB[FACK] = 0, the following conditions trigger the DMA request: a data
 *       byte is received, and either address or data is transmitted. (ACK/NACK is automatic) the first byte received
 *       matches the A1 register or is a general call address. If any address matching occurs, S[IAAS] and S[TCF]
 *       are set. If the direction of transfer is known from master to slave, then it is not required to check
 *       S[SRW]. With this assumption, DMA can also be used in this case. In other cases, if the master reads data from
 *       the slave, then it is required to rewrite the C1 register operation. With this assumption, DMA cannot be
 *       used. When FACK = 1, an address or a data byte is transmitted.
 */
#define I2C_C1_DMAEN(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C1_DMAEN_SHIFT)) & I2C_C1_DMAEN_MASK)

#define I2C_C1_WUEN_MASK                         (0x2U)
#define I2C_C1_WUEN_SHIFT                        (1U)
/*! WUEN - Wakeup Enable
 *  0b0..Normal operation. No interrupt generated when address matching in low power mode.
 *  0b1..Enables the wakeup function in low power mode.
 */
#define I2C_C1_WUEN(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C1_WUEN_SHIFT)) & I2C_C1_WUEN_MASK)

#define I2C_C1_RSTA_MASK                         (0x4U)
#define I2C_C1_RSTA_SHIFT                        (2U)
/*! RSTA - Repeat START */
#define I2C_C1_RSTA(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C1_RSTA_SHIFT)) & I2C_C1_RSTA_MASK)

#define I2C_C1_TXAK_MASK                         (0x8U)
#define I2C_C1_TXAK_SHIFT                        (3U)
/*! TXAK - Transmit Acknowledge Enable
 *  0b0..An acknowledge signal is sent to the bus on the following receiving byte (if FACK is cleared) or the
 *       current receiving byte (if FACK is set).
 *  0b1..No acknowledge signal is sent to the bus on the following receiving data byte (if FACK is cleared) or the
 *       current receiving data byte (if FACK is set).
 */
#define I2C_C1_TXAK(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C1_TXAK_SHIFT)) & I2C_C1_TXAK_MASK)

#define I2C_C1_TX_MASK                           (0x10U)
#define I2C_C1_TX_SHIFT                          (4U)
/*! TX - Transmit Mode Select
 *  0b0..Receive
 *  0b1..Transmit
 */
#define I2C_C1_TX(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_C1_TX_SHIFT)) & I2C_C1_TX_MASK)

#define I2C_C1_MST_MASK                          (0x20U)
#define I2C_C1_MST_SHIFT                         (5U)
/*! MST - Master Mode Select
 *  0b0..Slave mode
 *  0b1..Master mode
 */
#define I2C_C1_MST(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_C1_MST_SHIFT)) & I2C_C1_MST_MASK)

#define I2C_C1_IICIE_MASK                        (0x40U)
#define I2C_C1_IICIE_SHIFT                       (6U)
/*! IICIE - I2C Interrupt Enable
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define I2C_C1_IICIE(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C1_IICIE_SHIFT)) & I2C_C1_IICIE_MASK)

#define I2C_C1_IICEN_MASK                        (0x80U)
#define I2C_C1_IICEN_SHIFT                       (7U)
/*! IICEN - I2C Enable
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define I2C_C1_IICEN(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C1_IICEN_SHIFT)) & I2C_C1_IICEN_MASK)
/*! @} */

/*! @name S - I2C Status register */
/*! @{ */

#define I2C_S_RXAK_MASK                          (0x1U)
#define I2C_S_RXAK_SHIFT                         (0U)
/*! RXAK - Receive Acknowledge
 *  0b0..Acknowledge signal was received after the completion of one byte of data transmission on the bus
 *  0b1..No acknowledge signal detected
 */
#define I2C_S_RXAK(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_S_RXAK_SHIFT)) & I2C_S_RXAK_MASK)

#define I2C_S_IICIF_MASK                         (0x2U)
#define I2C_S_IICIF_SHIFT                        (1U)
/*! IICIF - Interrupt Flag
 *  0b0..No interrupt pending
 *  0b1..Interrupt pending
 */
#define I2C_S_IICIF(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_S_IICIF_SHIFT)) & I2C_S_IICIF_MASK)

#define I2C_S_SRW_MASK                           (0x4U)
#define I2C_S_SRW_SHIFT                          (2U)
/*! SRW - Slave Read/Write
 *  0b0..Slave receive, master writing to slave
 *  0b1..Slave transmit, master reading from slave
 */
#define I2C_S_SRW(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_S_SRW_SHIFT)) & I2C_S_SRW_MASK)

#define I2C_S_RAM_MASK                           (0x8U)
#define I2C_S_RAM_SHIFT                          (3U)
/*! RAM - Range Address Match
 *  0b0..Not addressed
 *  0b1..Addressed as a slave
 */
#define I2C_S_RAM(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_S_RAM_SHIFT)) & I2C_S_RAM_MASK)

#define I2C_S_ARBL_MASK                          (0x10U)
#define I2C_S_ARBL_SHIFT                         (4U)
/*! ARBL - Arbitration Lost
 *  0b0..Standard bus operation.
 *  0b1..Loss of arbitration.
 */
#define I2C_S_ARBL(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_S_ARBL_SHIFT)) & I2C_S_ARBL_MASK)

#define I2C_S_BUSY_MASK                          (0x20U)
#define I2C_S_BUSY_SHIFT                         (5U)
/*! BUSY - Bus Busy
 *  0b0..Bus is idle
 *  0b1..Bus is busy
 */
#define I2C_S_BUSY(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_S_BUSY_SHIFT)) & I2C_S_BUSY_MASK)

#define I2C_S_IAAS_MASK                          (0x40U)
#define I2C_S_IAAS_SHIFT                         (6U)
/*! IAAS - Addressed As A Slave
 *  0b0..Not addressed
 *  0b1..Addressed as a slave
 */
#define I2C_S_IAAS(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_S_IAAS_SHIFT)) & I2C_S_IAAS_MASK)

#define I2C_S_TCF_MASK                           (0x80U)
#define I2C_S_TCF_SHIFT                          (7U)
/*! TCF - Transfer Complete Flag
 *  0b0..Transfer in progress
 *  0b1..Transfer complete
 */
#define I2C_S_TCF(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_S_TCF_SHIFT)) & I2C_S_TCF_MASK)
/*! @} */

/*! @name D - I2C Data I/O register */
/*! @{ */

#define I2C_D_DATA_MASK                          (0xFFU)
#define I2C_D_DATA_SHIFT                         (0U)
/*! DATA - Data */
#define I2C_D_DATA(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_D_DATA_SHIFT)) & I2C_D_DATA_MASK)
/*! @} */

/*! @name C2 - I2C Control Register 2 */
/*! @{ */

#define I2C_C2_AD_MASK                           (0x7U)
#define I2C_C2_AD_SHIFT                          (0U)
/*! AD - Slave Address */
#define I2C_C2_AD(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_C2_AD_SHIFT)) & I2C_C2_AD_MASK)

#define I2C_C2_RMEN_MASK                         (0x8U)
#define I2C_C2_RMEN_SHIFT                        (3U)
/*! RMEN - Range Address Matching Enable
 *  0b0..Range mode disabled. No address matching occurs for an address within the range of values of the A1 and RA registers.
 *  0b1..Range mode enabled. Address matching occurs when a slave receives an address within the range of values of the A1 and RA registers.
 */
#define I2C_C2_RMEN(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C2_RMEN_SHIFT)) & I2C_C2_RMEN_MASK)

#define I2C_C2_SBRC_MASK                         (0x10U)
#define I2C_C2_SBRC_SHIFT                        (4U)
/*! SBRC - Slave Baud Rate Control
 *  0b0..The slave baud rate follows the master baud rate and clock stretching may occur
 *  0b1..Slave baud rate is independent of the master baud rate
 */
#define I2C_C2_SBRC(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C2_SBRC_SHIFT)) & I2C_C2_SBRC_MASK)

#define I2C_C2_HDRS_MASK                         (0x20U)
#define I2C_C2_HDRS_SHIFT                        (5U)
/*! HDRS - High Drive Select
 *  0b0..Normal drive mode
 *  0b1..High drive mode
 */
#define I2C_C2_HDRS(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C2_HDRS_SHIFT)) & I2C_C2_HDRS_MASK)

#define I2C_C2_ADEXT_MASK                        (0x40U)
#define I2C_C2_ADEXT_SHIFT                       (6U)
/*! ADEXT - Address Extension
 *  0b0..7-bit address scheme
 *  0b1..10-bit address scheme
 */
#define I2C_C2_ADEXT(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C2_ADEXT_SHIFT)) & I2C_C2_ADEXT_MASK)

#define I2C_C2_GCAEN_MASK                        (0x80U)
#define I2C_C2_GCAEN_SHIFT                       (7U)
/*! GCAEN - General Call Address Enable
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define I2C_C2_GCAEN(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C2_GCAEN_SHIFT)) & I2C_C2_GCAEN_MASK)
/*! @} */

/*! @name FLT - I2C Programmable Input Glitch Filter Register */
/*! @{ */

#define I2C_FLT_FLT_MASK                         (0xFU)
#define I2C_FLT_FLT_SHIFT                        (0U)
/*! FLT - I2C Programmable Filter Factor
 *  0b0000..No filter/bypass
 *  0b0001-0b1111..Filter glitches up to width of n I2C module clock cycles, where n=1-15d
 */
#define I2C_FLT_FLT(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_FLT_FLT_SHIFT)) & I2C_FLT_FLT_MASK)

#define I2C_FLT_STARTF_MASK                      (0x10U)
#define I2C_FLT_STARTF_SHIFT                     (4U)
/*! STARTF - I2C Bus Start Detect Flag
 *  0b0..No start happens on I2C bus
 *  0b1..Start detected on I2C bus
 */
#define I2C_FLT_STARTF(x)                        (((uint8_t)(((uint8_t)(x)) << I2C_FLT_STARTF_SHIFT)) & I2C_FLT_STARTF_MASK)

#define I2C_FLT_SSIE_MASK                        (0x20U)
#define I2C_FLT_SSIE_SHIFT                       (5U)
/*! SSIE - I2C Bus Stop or Start Interrupt Enable
 *  0b0..Stop or start detection interrupt is disabled
 *  0b1..Stop or start detection interrupt is enabled
 */
#define I2C_FLT_SSIE(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_FLT_SSIE_SHIFT)) & I2C_FLT_SSIE_MASK)

#define I2C_FLT_STOPF_MASK                       (0x40U)
#define I2C_FLT_STOPF_SHIFT                      (6U)
/*! STOPF - I2C Bus Stop Detect Flag
 *  0b0..No stop happens on I2C bus
 *  0b1..Stop detected on I2C bus
 */
#define I2C_FLT_STOPF(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_FLT_STOPF_SHIFT)) & I2C_FLT_STOPF_MASK)

#define I2C_FLT_SHEN_MASK                        (0x80U)
#define I2C_FLT_SHEN_SHIFT                       (7U)
/*! SHEN - Stop Hold Enable
 *  0b0..Stop holdoff is disabled. The MCU's entry to stop mode is not gated.
 *  0b1..Stop holdoff is enabled.
 */
#define I2C_FLT_SHEN(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_FLT_SHEN_SHIFT)) & I2C_FLT_SHEN_MASK)
/*! @} */

/*! @name RA - I2C Range Address register */
/*! @{ */

#define I2C_RA_RAD_MASK                          (0xFEU)
#define I2C_RA_RAD_SHIFT                         (1U)
/*! RAD - Range Slave Address */
#define I2C_RA_RAD(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_RA_RAD_SHIFT)) & I2C_RA_RAD_MASK)
/*! @} */

/*! @name SMB - I2C SMBus Control and Status register */
/*! @{ */

#define I2C_SMB_SHTF2IE_MASK                     (0x1U)
#define I2C_SMB_SHTF2IE_SHIFT                    (0U)
/*! SHTF2IE - SHTF2 Interrupt Enable
 *  0b0..SHTF2 interrupt is disabled
 *  0b1..SHTF2 interrupt is enabled
 */
#define I2C_SMB_SHTF2IE(x)                       (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SHTF2IE_SHIFT)) & I2C_SMB_SHTF2IE_MASK)

#define I2C_SMB_SHTF2_MASK                       (0x2U)
#define I2C_SMB_SHTF2_SHIFT                      (1U)
/*! SHTF2 - SCL High Timeout Flag 2
 *  0b0..No SCL high and SDA low timeout occurs
 *  0b1..SCL high and SDA low timeout occurs
 */
#define I2C_SMB_SHTF2(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SHTF2_SHIFT)) & I2C_SMB_SHTF2_MASK)

#define I2C_SMB_SHTF1_MASK                       (0x4U)
#define I2C_SMB_SHTF1_SHIFT                      (2U)
/*! SHTF1 - SCL High Timeout Flag 1
 *  0b0..No SCL high and SDA high timeout occurs
 *  0b1..SCL high and SDA high timeout occurs
 */
#define I2C_SMB_SHTF1(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SHTF1_SHIFT)) & I2C_SMB_SHTF1_MASK)

#define I2C_SMB_SLTF_MASK                        (0x8U)
#define I2C_SMB_SLTF_SHIFT                       (3U)
/*! SLTF - SCL Low Timeout Flag
 *  0b0..No low timeout occurs
 *  0b1..Low timeout occurs
 */
#define I2C_SMB_SLTF(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SLTF_SHIFT)) & I2C_SMB_SLTF_MASK)

#define I2C_SMB_TCKSEL_MASK                      (0x10U)
#define I2C_SMB_TCKSEL_SHIFT                     (4U)
/*! TCKSEL - Timeout Counter Clock Select
 *  0b0..Timeout counter counts at the frequency of the I2C module clock / 64
 *  0b1..Timeout counter counts at the frequency of the I2C module clock
 */
#define I2C_SMB_TCKSEL(x)                        (((uint8_t)(((uint8_t)(x)) << I2C_SMB_TCKSEL_SHIFT)) & I2C_SMB_TCKSEL_MASK)

#define I2C_SMB_SIICAEN_MASK                     (0x20U)
#define I2C_SMB_SIICAEN_SHIFT                    (5U)
/*! SIICAEN - Second I2C Address Enable
 *  0b0..I2C address register 2 matching is disabled
 *  0b1..I2C address register 2 matching is enabled
 */
#define I2C_SMB_SIICAEN(x)                       (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SIICAEN_SHIFT)) & I2C_SMB_SIICAEN_MASK)

#define I2C_SMB_ALERTEN_MASK                     (0x40U)
#define I2C_SMB_ALERTEN_SHIFT                    (6U)
/*! ALERTEN - SMBus Alert Response Address Enable
 *  0b0..SMBus alert response address matching is disabled
 *  0b1..SMBus alert response address matching is enabled
 */
#define I2C_SMB_ALERTEN(x)                       (((uint8_t)(((uint8_t)(x)) << I2C_SMB_ALERTEN_SHIFT)) & I2C_SMB_ALERTEN_MASK)

#define I2C_SMB_FACK_MASK                        (0x80U)
#define I2C_SMB_FACK_SHIFT                       (7U)
/*! FACK - Fast NACK/ACK Enable
 *  0b0..An ACK or NACK is sent on the following receiving data byte
 *  0b1..Writing 0 to TXAK after receiving a data byte generates an ACK. Writing 1 to TXAK after receiving a data byte generates a NACK.
 */
#define I2C_SMB_FACK(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_SMB_FACK_SHIFT)) & I2C_SMB_FACK_MASK)
/*! @} */

/*! @name A2 - I2C Address Register 2 */
/*! @{ */

#define I2C_A2_SAD_MASK                          (0xFEU)
#define I2C_A2_SAD_SHIFT                         (1U)
/*! SAD - SMBus Address */
#define I2C_A2_SAD(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_A2_SAD_SHIFT)) & I2C_A2_SAD_MASK)
/*! @} */

/*! @name SLTH - I2C SCL Low Timeout Register High */
/*! @{ */

#define I2C_SLTH_SSLT_MASK                       (0xFFU)
#define I2C_SLTH_SSLT_SHIFT                      (0U)
/*! SSLT - SSLT[15:8] */
#define I2C_SLTH_SSLT(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_SLTH_SSLT_SHIFT)) & I2C_SLTH_SSLT_MASK)
/*! @} */

/*! @name SLTL - I2C SCL Low Timeout Register Low */
/*! @{ */

#define I2C_SLTL_SSLT_MASK                       (0xFFU)
#define I2C_SLTL_SSLT_SHIFT                      (0U)
/*! SSLT - SSLT[7:0] */
#define I2C_SLTL_SSLT(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_SLTL_SSLT_SHIFT)) & I2C_SLTL_SSLT_MASK)
/*! @} */

/*! @name S2 - I2C Status register 2 */
/*! @{ */

#define I2C_S2_EMPTY_MASK                        (0x1U)
#define I2C_S2_EMPTY_SHIFT                       (0U)
/*! EMPTY - Empty flag
 *  0b0..Tx or Rx buffer is not empty and cannot be written to, that is new data cannot be loaded into the buffer.
 *  0b1..Tx or Rx buffer is empty and can be written to, that is new data can be loaded into the buffer.
 */
#define I2C_S2_EMPTY(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_S2_EMPTY_SHIFT)) & I2C_S2_EMPTY_MASK)

#define I2C_S2_ERROR_MASK                        (0x2U)
#define I2C_S2_ERROR_SHIFT                       (1U)
/*! ERROR - Error flag
 *  0b0..The buffer is not full and all write/read operations have no errors.
 *  0b1..There are 3 or more write/read errors during the data transfer phase (when the Empty flag is not set and the buffer is busy).
 */
#define I2C_S2_ERROR(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_S2_ERROR_SHIFT)) & I2C_S2_ERROR_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group I2C_Register_Masks */


/* I2C - Peripheral instance base addresses */
/** Peripheral I2C0 base address */
#define I2C0_BASE                                (0x40066000u)
/** Peripheral I2C0 base pointer */
#define I2C0                                     ((I2C_Type *)I2C0_BASE)
/** Peripheral I2C1 base address */
#define I2C1_BASE                                (0x40067000u)
/** Peripheral I2C1 base pointer */
#define I2C1                                     ((I2C_Type *)I2C1_BASE)
/** Array initializer of I2C peripheral base addresses */
#define I2C_BASE_ADDRS                           { I2C0_BASE, I2C1_BASE }
/** Array initializer of I2C peripheral base pointers */
#define I2C_BASE_PTRS                            { I2C0, I2C1 }
/** Interrupt vectors for the I2C peripheral type */
#define I2C_IRQS                                 { I2C0_IRQn, I2C1_IRQn }

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
  __IO uint32_t TCSR;                              /**< SAI Transmit Control Register, offset: 0x0 */
       uint8_t RESERVED_0[4];
  __IO uint32_t TCR2;                              /**< SAI Transmit Configuration 2 Register, offset: 0x8 */
  __IO uint32_t TCR3;                              /**< SAI Transmit Configuration 3 Register, offset: 0xC */
  __IO uint32_t TCR4;                              /**< SAI Transmit Configuration 4 Register, offset: 0x10 */
  __IO uint32_t TCR5;                              /**< SAI Transmit Configuration 5 Register, offset: 0x14 */
       uint8_t RESERVED_1[8];
  __O  uint32_t TDR[1];                            /**< SAI Transmit Data Register, array offset: 0x20, array step: 0x4 */
       uint8_t RESERVED_2[60];
  __IO uint32_t TMR;                               /**< SAI Transmit Mask Register, offset: 0x60 */
       uint8_t RESERVED_3[28];
  __IO uint32_t RCSR;                              /**< SAI Receive Control Register, offset: 0x80 */
       uint8_t RESERVED_4[4];
  __IO uint32_t RCR2;                              /**< SAI Receive Configuration 2 Register, offset: 0x88 */
  __IO uint32_t RCR3;                              /**< SAI Receive Configuration 3 Register, offset: 0x8C */
  __IO uint32_t RCR4;                              /**< SAI Receive Configuration 4 Register, offset: 0x90 */
  __IO uint32_t RCR5;                              /**< SAI Receive Configuration 5 Register, offset: 0x94 */
       uint8_t RESERVED_5[8];
  __I  uint32_t RDR[1];                            /**< SAI Receive Data Register, array offset: 0xA0, array step: 0x4 */
       uint8_t RESERVED_6[60];
  __IO uint32_t RMR;                               /**< SAI Receive Mask Register, offset: 0xE0 */
       uint8_t RESERVED_7[28];
  __IO uint32_t MCR;                               /**< SAI MCLK Control Register, offset: 0x100 */
} I2S_Type;

/* ----------------------------------------------------------------------------
   -- I2S Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2S_Register_Masks I2S Register Masks
 * @{
 */

/*! @name TCSR - SAI Transmit Control Register */
/*! @{ */

#define I2S_TCSR_FWDE_MASK                       (0x2U)
#define I2S_TCSR_FWDE_SHIFT                      (1U)
/*! FWDE - FIFO Warning DMA Enable
 *  0b0..Disables the DMA request.
 *  0b1..Enables the DMA request.
 */
#define I2S_TCSR_FWDE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_FWDE_SHIFT)) & I2S_TCSR_FWDE_MASK)

#define I2S_TCSR_FWIE_MASK                       (0x200U)
#define I2S_TCSR_FWIE_SHIFT                      (9U)
/*! FWIE - FIFO Warning Interrupt Enable
 *  0b0..Disables the interrupt.
 *  0b1..Enables the interrupt.
 */
#define I2S_TCSR_FWIE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_FWIE_SHIFT)) & I2S_TCSR_FWIE_MASK)

#define I2S_TCSR_FEIE_MASK                       (0x400U)
#define I2S_TCSR_FEIE_SHIFT                      (10U)
/*! FEIE - FIFO Error Interrupt Enable
 *  0b0..Disables the interrupt.
 *  0b1..Enables the interrupt.
 */
#define I2S_TCSR_FEIE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_FEIE_SHIFT)) & I2S_TCSR_FEIE_MASK)

#define I2S_TCSR_SEIE_MASK                       (0x800U)
#define I2S_TCSR_SEIE_SHIFT                      (11U)
/*! SEIE - Sync Error Interrupt Enable
 *  0b0..Disables interrupt.
 *  0b1..Enables interrupt.
 */
#define I2S_TCSR_SEIE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_SEIE_SHIFT)) & I2S_TCSR_SEIE_MASK)

#define I2S_TCSR_WSIE_MASK                       (0x1000U)
#define I2S_TCSR_WSIE_SHIFT                      (12U)
/*! WSIE - Word Start Interrupt Enable
 *  0b0..Disables interrupt.
 *  0b1..Enables interrupt.
 */
#define I2S_TCSR_WSIE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_WSIE_SHIFT)) & I2S_TCSR_WSIE_MASK)

#define I2S_TCSR_FWF_MASK                        (0x20000U)
#define I2S_TCSR_FWF_SHIFT                       (17U)
/*! FWF - FIFO Warning Flag
 *  0b0..No enabled transmit FIFO is empty.
 *  0b1..Enabled transmit FIFO is empty.
 */
#define I2S_TCSR_FWF(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_FWF_SHIFT)) & I2S_TCSR_FWF_MASK)

#define I2S_TCSR_FEF_MASK                        (0x40000U)
#define I2S_TCSR_FEF_SHIFT                       (18U)
/*! FEF - FIFO Error Flag
 *  0b0..Transmit underrun not detected.
 *  0b1..Transmit underrun detected.
 */
#define I2S_TCSR_FEF(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_FEF_SHIFT)) & I2S_TCSR_FEF_MASK)

#define I2S_TCSR_SEF_MASK                        (0x80000U)
#define I2S_TCSR_SEF_SHIFT                       (19U)
/*! SEF - Sync Error Flag
 *  0b0..Sync error not detected.
 *  0b1..Frame sync error detected.
 */
#define I2S_TCSR_SEF(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_SEF_SHIFT)) & I2S_TCSR_SEF_MASK)

#define I2S_TCSR_WSF_MASK                        (0x100000U)
#define I2S_TCSR_WSF_SHIFT                       (20U)
/*! WSF - Word Start Flag
 *  0b0..Start of word not detected.
 *  0b1..Start of word detected.
 */
#define I2S_TCSR_WSF(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_WSF_SHIFT)) & I2S_TCSR_WSF_MASK)

#define I2S_TCSR_SR_MASK                         (0x1000000U)
#define I2S_TCSR_SR_SHIFT                        (24U)
/*! SR - Software Reset
 *  0b0..No effect.
 *  0b1..Software reset.
 */
#define I2S_TCSR_SR(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_SR_SHIFT)) & I2S_TCSR_SR_MASK)

#define I2S_TCSR_FR_MASK                         (0x2000000U)
#define I2S_TCSR_FR_SHIFT                        (25U)
/*! FR - FIFO Reset
 *  0b0..No effect.
 *  0b1..FIFO reset.
 */
#define I2S_TCSR_FR(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_FR_SHIFT)) & I2S_TCSR_FR_MASK)

#define I2S_TCSR_BCE_MASK                        (0x10000000U)
#define I2S_TCSR_BCE_SHIFT                       (28U)
/*! BCE - Bit Clock Enable
 *  0b0..Transmit bit clock is disabled.
 *  0b1..Transmit bit clock is enabled.
 */
#define I2S_TCSR_BCE(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_BCE_SHIFT)) & I2S_TCSR_BCE_MASK)

#define I2S_TCSR_DBGE_MASK                       (0x20000000U)
#define I2S_TCSR_DBGE_SHIFT                      (29U)
/*! DBGE - Debug Enable
 *  0b0..Transmitter is disabled in Debug mode, after completing the current frame.
 *  0b1..Transmitter is enabled in Debug mode.
 */
#define I2S_TCSR_DBGE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_DBGE_SHIFT)) & I2S_TCSR_DBGE_MASK)

#define I2S_TCSR_STOPE_MASK                      (0x40000000U)
#define I2S_TCSR_STOPE_SHIFT                     (30U)
/*! STOPE - Stop Enable
 *  0b0..Transmitter disabled in Stop mode.
 *  0b1..Transmitter enabled in Stop mode.
 */
#define I2S_TCSR_STOPE(x)                        (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_STOPE_SHIFT)) & I2S_TCSR_STOPE_MASK)

#define I2S_TCSR_TE_MASK                         (0x80000000U)
#define I2S_TCSR_TE_SHIFT                        (31U)
/*! TE - Transmitter Enable
 *  0b0..Transmitter is disabled.
 *  0b1..Transmitter is enabled, or transmitter has been disabled and has not yet reached end of frame.
 */
#define I2S_TCSR_TE(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_TCSR_TE_SHIFT)) & I2S_TCSR_TE_MASK)
/*! @} */

/*! @name TCR2 - SAI Transmit Configuration 2 Register */
/*! @{ */

#define I2S_TCR2_DIV_MASK                        (0xFFU)
#define I2S_TCR2_DIV_SHIFT                       (0U)
/*! DIV - Bit Clock Divide */
#define I2S_TCR2_DIV(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCR2_DIV_SHIFT)) & I2S_TCR2_DIV_MASK)

#define I2S_TCR2_BCD_MASK                        (0x1000000U)
#define I2S_TCR2_BCD_SHIFT                       (24U)
/*! BCD - Bit Clock Direction
 *  0b0..Bit clock is generated externally in Slave mode.
 *  0b1..Bit clock is generated internally in Master mode.
 */
#define I2S_TCR2_BCD(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCR2_BCD_SHIFT)) & I2S_TCR2_BCD_MASK)

#define I2S_TCR2_BCP_MASK                        (0x2000000U)
#define I2S_TCR2_BCP_SHIFT                       (25U)
/*! BCP - Bit Clock Polarity
 *  0b0..Bit clock is active high with drive outputs on rising edge and sample inputs on falling edge.
 *  0b1..Bit clock is active low with drive outputs on falling edge and sample inputs on rising edge.
 */
#define I2S_TCR2_BCP(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCR2_BCP_SHIFT)) & I2S_TCR2_BCP_MASK)

#define I2S_TCR2_MSEL_MASK                       (0xC000000U)
#define I2S_TCR2_MSEL_SHIFT                      (26U)
/*! MSEL - MCLK Select
 *  0b00..Bus Clock selected.
 *  0b01..Master Clock (MCLK) 1 option selected.
 *  0b10..Master Clock (MCLK) 2 option selected.
 *  0b11..Master Clock (MCLK) 3 option selected.
 */
#define I2S_TCR2_MSEL(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_TCR2_MSEL_SHIFT)) & I2S_TCR2_MSEL_MASK)

#define I2S_TCR2_BCI_MASK                        (0x10000000U)
#define I2S_TCR2_BCI_SHIFT                       (28U)
/*! BCI - Bit Clock Input
 *  0b0..No effect.
 *  0b1..Internal logic is clocked as if bit clock was externally generated.
 */
#define I2S_TCR2_BCI(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCR2_BCI_SHIFT)) & I2S_TCR2_BCI_MASK)

#define I2S_TCR2_BCS_MASK                        (0x20000000U)
#define I2S_TCR2_BCS_SHIFT                       (29U)
/*! BCS - Bit Clock Swap
 *  0b0..Use the normal bit clock source.
 *  0b1..Swap the bit clock source.
 */
#define I2S_TCR2_BCS(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCR2_BCS_SHIFT)) & I2S_TCR2_BCS_MASK)

#define I2S_TCR2_SYNC_MASK                       (0xC0000000U)
#define I2S_TCR2_SYNC_SHIFT                      (30U)
/*! SYNC - Synchronous Mode
 *  0b00..Asynchronous mode.
 *  0b01..Synchronous with receiver.
 *  0b10..Synchronous with another SAI transmitter.
 *  0b11..Synchronous with another SAI receiver.
 */
#define I2S_TCR2_SYNC(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_TCR2_SYNC_SHIFT)) & I2S_TCR2_SYNC_MASK)
/*! @} */

/*! @name TCR3 - SAI Transmit Configuration 3 Register */
/*! @{ */

#define I2S_TCR3_WDFL_MASK                       (0x1U)
#define I2S_TCR3_WDFL_SHIFT                      (0U)
/*! WDFL - Word Flag Configuration */
#define I2S_TCR3_WDFL(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_TCR3_WDFL_SHIFT)) & I2S_TCR3_WDFL_MASK)

#define I2S_TCR3_TCE_MASK                        (0x10000U)
#define I2S_TCR3_TCE_SHIFT                       (16U)
/*! TCE - Transmit Channel Enable
 *  0b0..Transmit data channel N is disabled.
 *  0b1..Transmit data channel N is enabled.
 */
#define I2S_TCR3_TCE(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCR3_TCE_SHIFT)) & I2S_TCR3_TCE_MASK)
/*! @} */

/*! @name TCR4 - SAI Transmit Configuration 4 Register */
/*! @{ */

#define I2S_TCR4_FSD_MASK                        (0x1U)
#define I2S_TCR4_FSD_SHIFT                       (0U)
/*! FSD - Frame Sync Direction
 *  0b0..Frame sync is generated externally in Slave mode.
 *  0b1..Frame sync is generated internally in Master mode.
 */
#define I2S_TCR4_FSD(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCR4_FSD_SHIFT)) & I2S_TCR4_FSD_MASK)

#define I2S_TCR4_FSP_MASK                        (0x2U)
#define I2S_TCR4_FSP_SHIFT                       (1U)
/*! FSP - Frame Sync Polarity
 *  0b0..Frame sync is active high.
 *  0b1..Frame sync is active low.
 */
#define I2S_TCR4_FSP(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCR4_FSP_SHIFT)) & I2S_TCR4_FSP_MASK)

#define I2S_TCR4_ONDEM_MASK                      (0x4U)
#define I2S_TCR4_ONDEM_SHIFT                     (2U)
/*! ONDEM - On Demand Mode
 *  0b0..Internal frame sync is generated continuously.
 *  0b1..Internal frame sync is generated when the FIFO warning flag is clear.
 */
#define I2S_TCR4_ONDEM(x)                        (((uint32_t)(((uint32_t)(x)) << I2S_TCR4_ONDEM_SHIFT)) & I2S_TCR4_ONDEM_MASK)

#define I2S_TCR4_FSE_MASK                        (0x8U)
#define I2S_TCR4_FSE_SHIFT                       (3U)
/*! FSE - Frame Sync Early
 *  0b0..Frame sync asserts with the first bit of the frame.
 *  0b1..Frame sync asserts one bit before the first bit of the frame.
 */
#define I2S_TCR4_FSE(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCR4_FSE_SHIFT)) & I2S_TCR4_FSE_MASK)

#define I2S_TCR4_MF_MASK                         (0x10U)
#define I2S_TCR4_MF_SHIFT                        (4U)
/*! MF - MSB First
 *  0b0..LSB is transmitted first.
 *  0b1..MSB is transmitted first.
 */
#define I2S_TCR4_MF(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_TCR4_MF_SHIFT)) & I2S_TCR4_MF_MASK)

#define I2S_TCR4_SYWD_MASK                       (0x1F00U)
#define I2S_TCR4_SYWD_SHIFT                      (8U)
/*! SYWD - Sync Width */
#define I2S_TCR4_SYWD(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_TCR4_SYWD_SHIFT)) & I2S_TCR4_SYWD_MASK)

#define I2S_TCR4_FRSZ_MASK                       (0x10000U)
#define I2S_TCR4_FRSZ_SHIFT                      (16U)
/*! FRSZ - Frame size */
#define I2S_TCR4_FRSZ(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_TCR4_FRSZ_SHIFT)) & I2S_TCR4_FRSZ_MASK)

#define I2S_TCR4_FPACK_MASK                      (0x3000000U)
#define I2S_TCR4_FPACK_SHIFT                     (24U)
/*! FPACK - FIFO Packing Mode
 *  0b00..FIFO packing is disabled
 *  0b01..Reserved
 *  0b10..8-bit FIFO packing is enabled
 *  0b11..16-bit FIFO packing is enabled
 */
#define I2S_TCR4_FPACK(x)                        (((uint32_t)(((uint32_t)(x)) << I2S_TCR4_FPACK_SHIFT)) & I2S_TCR4_FPACK_MASK)

#define I2S_TCR4_FCONT_MASK                      (0x10000000U)
#define I2S_TCR4_FCONT_SHIFT                     (28U)
/*! FCONT - FIFO Continue on Error
 *  0b0..On FIFO error, the SAI will continue from the start of the next frame after the FIFO error flag has been cleared.
 *  0b1..On FIFO error, the SAI will continue from the same word that caused the FIFO error to set after the FIFO warning flag has been cleared.
 */
#define I2S_TCR4_FCONT(x)                        (((uint32_t)(((uint32_t)(x)) << I2S_TCR4_FCONT_SHIFT)) & I2S_TCR4_FCONT_MASK)
/*! @} */

/*! @name TCR5 - SAI Transmit Configuration 5 Register */
/*! @{ */

#define I2S_TCR5_FBT_MASK                        (0x1F00U)
#define I2S_TCR5_FBT_SHIFT                       (8U)
/*! FBT - First Bit Shifted */
#define I2S_TCR5_FBT(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCR5_FBT_SHIFT)) & I2S_TCR5_FBT_MASK)

#define I2S_TCR5_W0W_MASK                        (0x1F0000U)
#define I2S_TCR5_W0W_SHIFT                       (16U)
/*! W0W - Word 0 Width */
#define I2S_TCR5_W0W(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCR5_W0W_SHIFT)) & I2S_TCR5_W0W_MASK)

#define I2S_TCR5_WNW_MASK                        (0x1F000000U)
#define I2S_TCR5_WNW_SHIFT                       (24U)
/*! WNW - Word N Width */
#define I2S_TCR5_WNW(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_TCR5_WNW_SHIFT)) & I2S_TCR5_WNW_MASK)
/*! @} */

/*! @name TDR - SAI Transmit Data Register */
/*! @{ */

#define I2S_TDR_TDR_MASK                         (0xFFFFFFFFU)
#define I2S_TDR_TDR_SHIFT                        (0U)
/*! TDR - Transmit Data Register */
#define I2S_TDR_TDR(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_TDR_TDR_SHIFT)) & I2S_TDR_TDR_MASK)
/*! @} */

/* The count of I2S_TDR */
#define I2S_TDR_COUNT                            (1U)

/*! @name TMR - SAI Transmit Mask Register */
/*! @{ */

#define I2S_TMR_TWM_MASK                         (0x3U)
#define I2S_TMR_TWM_SHIFT                        (0U)
/*! TWM - Transmit Word Mask
 *  0b00..Word N is enabled.
 *  0b01..Word N is masked. The transmit data pins are tri-stated when masked.
 */
#define I2S_TMR_TWM(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_TMR_TWM_SHIFT)) & I2S_TMR_TWM_MASK)
/*! @} */

/*! @name RCSR - SAI Receive Control Register */
/*! @{ */

#define I2S_RCSR_FWDE_MASK                       (0x2U)
#define I2S_RCSR_FWDE_SHIFT                      (1U)
/*! FWDE - FIFO Warning DMA Enable
 *  0b0..Disables the DMA request.
 *  0b1..Enables the DMA request.
 */
#define I2S_RCSR_FWDE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_FWDE_SHIFT)) & I2S_RCSR_FWDE_MASK)

#define I2S_RCSR_FWIE_MASK                       (0x200U)
#define I2S_RCSR_FWIE_SHIFT                      (9U)
/*! FWIE - FIFO Warning Interrupt Enable
 *  0b0..Disables the interrupt.
 *  0b1..Enables the interrupt.
 */
#define I2S_RCSR_FWIE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_FWIE_SHIFT)) & I2S_RCSR_FWIE_MASK)

#define I2S_RCSR_FEIE_MASK                       (0x400U)
#define I2S_RCSR_FEIE_SHIFT                      (10U)
/*! FEIE - FIFO Error Interrupt Enable
 *  0b0..Disables the interrupt.
 *  0b1..Enables the interrupt.
 */
#define I2S_RCSR_FEIE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_FEIE_SHIFT)) & I2S_RCSR_FEIE_MASK)

#define I2S_RCSR_SEIE_MASK                       (0x800U)
#define I2S_RCSR_SEIE_SHIFT                      (11U)
/*! SEIE - Sync Error Interrupt Enable
 *  0b0..Disables interrupt.
 *  0b1..Enables interrupt.
 */
#define I2S_RCSR_SEIE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_SEIE_SHIFT)) & I2S_RCSR_SEIE_MASK)

#define I2S_RCSR_WSIE_MASK                       (0x1000U)
#define I2S_RCSR_WSIE_SHIFT                      (12U)
/*! WSIE - Word Start Interrupt Enable
 *  0b0..Disables interrupt.
 *  0b1..Enables interrupt.
 */
#define I2S_RCSR_WSIE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_WSIE_SHIFT)) & I2S_RCSR_WSIE_MASK)

#define I2S_RCSR_FWF_MASK                        (0x20000U)
#define I2S_RCSR_FWF_SHIFT                       (17U)
/*! FWF - FIFO Warning Flag
 *  0b0..No enabled receive FIFO is full.
 *  0b1..Enabled receive FIFO is full.
 */
#define I2S_RCSR_FWF(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_FWF_SHIFT)) & I2S_RCSR_FWF_MASK)

#define I2S_RCSR_FEF_MASK                        (0x40000U)
#define I2S_RCSR_FEF_SHIFT                       (18U)
/*! FEF - FIFO Error Flag
 *  0b0..Receive overflow not detected.
 *  0b1..Receive overflow detected.
 */
#define I2S_RCSR_FEF(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_FEF_SHIFT)) & I2S_RCSR_FEF_MASK)

#define I2S_RCSR_SEF_MASK                        (0x80000U)
#define I2S_RCSR_SEF_SHIFT                       (19U)
/*! SEF - Sync Error Flag
 *  0b0..Sync error not detected.
 *  0b1..Frame sync error detected.
 */
#define I2S_RCSR_SEF(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_SEF_SHIFT)) & I2S_RCSR_SEF_MASK)

#define I2S_RCSR_WSF_MASK                        (0x100000U)
#define I2S_RCSR_WSF_SHIFT                       (20U)
/*! WSF - Word Start Flag
 *  0b0..Start of word not detected.
 *  0b1..Start of word detected.
 */
#define I2S_RCSR_WSF(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_WSF_SHIFT)) & I2S_RCSR_WSF_MASK)

#define I2S_RCSR_SR_MASK                         (0x1000000U)
#define I2S_RCSR_SR_SHIFT                        (24U)
/*! SR - Software Reset
 *  0b0..No effect.
 *  0b1..Software reset.
 */
#define I2S_RCSR_SR(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_SR_SHIFT)) & I2S_RCSR_SR_MASK)

#define I2S_RCSR_FR_MASK                         (0x2000000U)
#define I2S_RCSR_FR_SHIFT                        (25U)
/*! FR - FIFO Reset
 *  0b0..No effect.
 *  0b1..FIFO reset.
 */
#define I2S_RCSR_FR(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_FR_SHIFT)) & I2S_RCSR_FR_MASK)

#define I2S_RCSR_BCE_MASK                        (0x10000000U)
#define I2S_RCSR_BCE_SHIFT                       (28U)
/*! BCE - Bit Clock Enable
 *  0b0..Receive bit clock is disabled.
 *  0b1..Receive bit clock is enabled.
 */
#define I2S_RCSR_BCE(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_BCE_SHIFT)) & I2S_RCSR_BCE_MASK)

#define I2S_RCSR_DBGE_MASK                       (0x20000000U)
#define I2S_RCSR_DBGE_SHIFT                      (29U)
/*! DBGE - Debug Enable
 *  0b0..Receiver is disabled in Debug mode, after completing the current frame.
 *  0b1..Receiver is enabled in Debug mode.
 */
#define I2S_RCSR_DBGE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_DBGE_SHIFT)) & I2S_RCSR_DBGE_MASK)

#define I2S_RCSR_STOPE_MASK                      (0x40000000U)
#define I2S_RCSR_STOPE_SHIFT                     (30U)
/*! STOPE - Stop Enable
 *  0b0..Receiver disabled in Stop mode.
 *  0b1..Receiver enabled in Stop mode.
 */
#define I2S_RCSR_STOPE(x)                        (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_STOPE_SHIFT)) & I2S_RCSR_STOPE_MASK)

#define I2S_RCSR_RE_MASK                         (0x80000000U)
#define I2S_RCSR_RE_SHIFT                        (31U)
/*! RE - Receiver Enable
 *  0b0..Receiver is disabled.
 *  0b1..Receiver is enabled, or receiver has been disabled and has not yet reached end of frame.
 */
#define I2S_RCSR_RE(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_RCSR_RE_SHIFT)) & I2S_RCSR_RE_MASK)
/*! @} */

/*! @name RCR2 - SAI Receive Configuration 2 Register */
/*! @{ */

#define I2S_RCR2_DIV_MASK                        (0xFFU)
#define I2S_RCR2_DIV_SHIFT                       (0U)
/*! DIV - Bit Clock Divide */
#define I2S_RCR2_DIV(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCR2_DIV_SHIFT)) & I2S_RCR2_DIV_MASK)

#define I2S_RCR2_BCD_MASK                        (0x1000000U)
#define I2S_RCR2_BCD_SHIFT                       (24U)
/*! BCD - Bit Clock Direction
 *  0b0..Bit clock is generated externally in Slave mode.
 *  0b1..Bit clock is generated internally in Master mode.
 */
#define I2S_RCR2_BCD(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCR2_BCD_SHIFT)) & I2S_RCR2_BCD_MASK)

#define I2S_RCR2_BCP_MASK                        (0x2000000U)
#define I2S_RCR2_BCP_SHIFT                       (25U)
/*! BCP - Bit Clock Polarity
 *  0b0..Bit Clock is active high with drive outputs on rising edge and sample inputs on falling edge.
 *  0b1..Bit Clock is active low with drive outputs on falling edge and sample inputs on rising edge.
 */
#define I2S_RCR2_BCP(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCR2_BCP_SHIFT)) & I2S_RCR2_BCP_MASK)

#define I2S_RCR2_MSEL_MASK                       (0xC000000U)
#define I2S_RCR2_MSEL_SHIFT                      (26U)
/*! MSEL - MCLK Select
 *  0b00..Bus Clock selected.
 *  0b01..Master Clock (MCLK) 1 option selected.
 *  0b10..Master Clock (MCLK) 2 option selected.
 *  0b11..Master Clock (MCLK) 3 option selected.
 */
#define I2S_RCR2_MSEL(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_RCR2_MSEL_SHIFT)) & I2S_RCR2_MSEL_MASK)

#define I2S_RCR2_BCI_MASK                        (0x10000000U)
#define I2S_RCR2_BCI_SHIFT                       (28U)
/*! BCI - Bit Clock Input
 *  0b0..No effect.
 *  0b1..Internal logic is clocked as if bit clock was externally generated.
 */
#define I2S_RCR2_BCI(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCR2_BCI_SHIFT)) & I2S_RCR2_BCI_MASK)

#define I2S_RCR2_BCS_MASK                        (0x20000000U)
#define I2S_RCR2_BCS_SHIFT                       (29U)
/*! BCS - Bit Clock Swap
 *  0b0..Use the normal bit clock source.
 *  0b1..Swap the bit clock source.
 */
#define I2S_RCR2_BCS(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCR2_BCS_SHIFT)) & I2S_RCR2_BCS_MASK)

#define I2S_RCR2_SYNC_MASK                       (0xC0000000U)
#define I2S_RCR2_SYNC_SHIFT                      (30U)
/*! SYNC - Synchronous Mode
 *  0b00..Asynchronous mode.
 *  0b01..Synchronous with transmitter.
 *  0b10..Synchronous with another SAI receiver.
 *  0b11..Synchronous with another SAI transmitter.
 */
#define I2S_RCR2_SYNC(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_RCR2_SYNC_SHIFT)) & I2S_RCR2_SYNC_MASK)
/*! @} */

/*! @name RCR3 - SAI Receive Configuration 3 Register */
/*! @{ */

#define I2S_RCR3_WDFL_MASK                       (0x1U)
#define I2S_RCR3_WDFL_SHIFT                      (0U)
/*! WDFL - Word Flag Configuration */
#define I2S_RCR3_WDFL(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_RCR3_WDFL_SHIFT)) & I2S_RCR3_WDFL_MASK)

#define I2S_RCR3_RCE_MASK                        (0x10000U)
#define I2S_RCR3_RCE_SHIFT                       (16U)
/*! RCE - Receive Channel Enable
 *  0b0..Receive data channel N is disabled.
 *  0b1..Receive data channel N is enabled.
 */
#define I2S_RCR3_RCE(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCR3_RCE_SHIFT)) & I2S_RCR3_RCE_MASK)
/*! @} */

/*! @name RCR4 - SAI Receive Configuration 4 Register */
/*! @{ */

#define I2S_RCR4_FSD_MASK                        (0x1U)
#define I2S_RCR4_FSD_SHIFT                       (0U)
/*! FSD - Frame Sync Direction
 *  0b0..Frame Sync is generated externally in Slave mode.
 *  0b1..Frame Sync is generated internally in Master mode.
 */
#define I2S_RCR4_FSD(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCR4_FSD_SHIFT)) & I2S_RCR4_FSD_MASK)

#define I2S_RCR4_FSP_MASK                        (0x2U)
#define I2S_RCR4_FSP_SHIFT                       (1U)
/*! FSP - Frame Sync Polarity
 *  0b0..Frame sync is active high.
 *  0b1..Frame sync is active low.
 */
#define I2S_RCR4_FSP(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCR4_FSP_SHIFT)) & I2S_RCR4_FSP_MASK)

#define I2S_RCR4_ONDEM_MASK                      (0x4U)
#define I2S_RCR4_ONDEM_SHIFT                     (2U)
/*! ONDEM - On Demand Mode
 *  0b0..Internal frame sync is generated continuously.
 *  0b1..Internal frame sync is generated when the FIFO warning flag is clear.
 */
#define I2S_RCR4_ONDEM(x)                        (((uint32_t)(((uint32_t)(x)) << I2S_RCR4_ONDEM_SHIFT)) & I2S_RCR4_ONDEM_MASK)

#define I2S_RCR4_FSE_MASK                        (0x8U)
#define I2S_RCR4_FSE_SHIFT                       (3U)
/*! FSE - Frame Sync Early
 *  0b0..Frame sync asserts with the first bit of the frame.
 *  0b1..Frame sync asserts one bit before the first bit of the frame.
 */
#define I2S_RCR4_FSE(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCR4_FSE_SHIFT)) & I2S_RCR4_FSE_MASK)

#define I2S_RCR4_MF_MASK                         (0x10U)
#define I2S_RCR4_MF_SHIFT                        (4U)
/*! MF - MSB First
 *  0b0..LSB is received first.
 *  0b1..MSB is received first.
 */
#define I2S_RCR4_MF(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_RCR4_MF_SHIFT)) & I2S_RCR4_MF_MASK)

#define I2S_RCR4_SYWD_MASK                       (0x1F00U)
#define I2S_RCR4_SYWD_SHIFT                      (8U)
/*! SYWD - Sync Width */
#define I2S_RCR4_SYWD(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_RCR4_SYWD_SHIFT)) & I2S_RCR4_SYWD_MASK)

#define I2S_RCR4_FRSZ_MASK                       (0x10000U)
#define I2S_RCR4_FRSZ_SHIFT                      (16U)
/*! FRSZ - Frame Size */
#define I2S_RCR4_FRSZ(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_RCR4_FRSZ_SHIFT)) & I2S_RCR4_FRSZ_MASK)

#define I2S_RCR4_FPACK_MASK                      (0x3000000U)
#define I2S_RCR4_FPACK_SHIFT                     (24U)
/*! FPACK - FIFO Packing Mode
 *  0b00..FIFO packing is disabled
 *  0b01..Reserved.
 *  0b10..8-bit FIFO packing is enabled
 *  0b11..16-bit FIFO packing is enabled
 */
#define I2S_RCR4_FPACK(x)                        (((uint32_t)(((uint32_t)(x)) << I2S_RCR4_FPACK_SHIFT)) & I2S_RCR4_FPACK_MASK)

#define I2S_RCR4_FCONT_MASK                      (0x10000000U)
#define I2S_RCR4_FCONT_SHIFT                     (28U)
/*! FCONT - FIFO Continue on Error
 *  0b0..On FIFO error, the SAI will continue from the start of the next frame after the FIFO error flag has been cleared.
 *  0b1..On FIFO error, the SAI will continue from the same word that caused the FIFO error to set after the FIFO warning flag has been cleared.
 */
#define I2S_RCR4_FCONT(x)                        (((uint32_t)(((uint32_t)(x)) << I2S_RCR4_FCONT_SHIFT)) & I2S_RCR4_FCONT_MASK)
/*! @} */

/*! @name RCR5 - SAI Receive Configuration 5 Register */
/*! @{ */

#define I2S_RCR5_FBT_MASK                        (0x1F00U)
#define I2S_RCR5_FBT_SHIFT                       (8U)
/*! FBT - First Bit Shifted */
#define I2S_RCR5_FBT(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCR5_FBT_SHIFT)) & I2S_RCR5_FBT_MASK)

#define I2S_RCR5_W0W_MASK                        (0x1F0000U)
#define I2S_RCR5_W0W_SHIFT                       (16U)
/*! W0W - Word 0 Width */
#define I2S_RCR5_W0W(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCR5_W0W_SHIFT)) & I2S_RCR5_W0W_MASK)

#define I2S_RCR5_WNW_MASK                        (0x1F000000U)
#define I2S_RCR5_WNW_SHIFT                       (24U)
/*! WNW - Word N Width */
#define I2S_RCR5_WNW(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_RCR5_WNW_SHIFT)) & I2S_RCR5_WNW_MASK)
/*! @} */

/*! @name RDR - SAI Receive Data Register */
/*! @{ */

#define I2S_RDR_RDR_MASK                         (0xFFFFFFFFU)
#define I2S_RDR_RDR_SHIFT                        (0U)
/*! RDR - Receive Data Register */
#define I2S_RDR_RDR(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_RDR_RDR_SHIFT)) & I2S_RDR_RDR_MASK)
/*! @} */

/* The count of I2S_RDR */
#define I2S_RDR_COUNT                            (1U)

/*! @name RMR - SAI Receive Mask Register */
/*! @{ */

#define I2S_RMR_RWM_MASK                         (0x3U)
#define I2S_RMR_RWM_SHIFT                        (0U)
/*! RWM - Receive Word Mask
 *  0b00..Word N is enabled.
 *  0b01..Word N is masked.
 */
#define I2S_RMR_RWM(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_RMR_RWM_SHIFT)) & I2S_RMR_RWM_MASK)
/*! @} */

/*! @name MCR - SAI MCLK Control Register */
/*! @{ */

#define I2S_MCR_MICS_MASK                        (0x3000000U)
#define I2S_MCR_MICS_SHIFT                       (24U)
/*! MICS - MCLK Input Clock Select
 *  0b00..MCLK divider input clock 0 selected.
 *  0b01..MCLK divider input clock 1 selected.
 *  0b10..MCLK divider input clock 2 selected.
 *  0b11..MCLK divider input clock 3 selected.
 */
#define I2S_MCR_MICS(x)                          (((uint32_t)(((uint32_t)(x)) << I2S_MCR_MICS_SHIFT)) & I2S_MCR_MICS_MASK)

#define I2S_MCR_MOE_MASK                         (0x40000000U)
#define I2S_MCR_MOE_SHIFT                        (30U)
/*! MOE - MCLK Output Enable
 *  0b0..MCLK signal pin is configured as an input that bypasses the MCLK divider.
 *  0b1..MCLK signal pin is configured as an output from the MCLK divider and the MCLK divider is enabled.
 */
#define I2S_MCR_MOE(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_MCR_MOE_SHIFT)) & I2S_MCR_MOE_MASK)

#define I2S_MCR_DUF_MASK                         (0x80000000U)
#define I2S_MCR_DUF_SHIFT                        (31U)
/*! DUF - Divider Update Flag
 *  0b0..MCLK divider ratio is not being updated currently.
 *  0b1..MCLK divider ratio is updating on-the-fly. Further updates to the MCLK divider ratio are blocked while this flag remains set.
 */
#define I2S_MCR_DUF(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_MCR_DUF_SHIFT)) & I2S_MCR_DUF_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group I2S_Register_Masks */


/* I2S - Peripheral instance base addresses */
/** Peripheral I2S0 base address */
#define I2S0_BASE                                (0x4002F000u)
/** Peripheral I2S0 base pointer */
#define I2S0                                     ((I2S_Type *)I2S0_BASE)
/** Array initializer of I2S peripheral base addresses */
#define I2S_BASE_ADDRS                           { I2S0_BASE }
/** Array initializer of I2S peripheral base pointers */
#define I2S_BASE_PTRS                            { I2S0 }
/** Interrupt vectors for the I2S peripheral type */
#define I2S_RX_IRQS                              { I2S0_IRQn }
#define I2S_TX_IRQS                              { I2S0_IRQn }

/*!
 * @}
 */ /* end of group I2S_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- LCD Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LCD_Peripheral_Access_Layer LCD Peripheral Access Layer
 * @{
 */

/** LCD - Register Layout Typedef */
typedef struct {
  __IO uint32_t GCR;                               /**< LCD General Control Register, offset: 0x0 */
  __IO uint32_t AR;                                /**< LCD Auxiliary Register, offset: 0x4 */
  __IO uint32_t FDCR;                              /**< LCD Fault Detect Control Register, offset: 0x8 */
  __IO uint32_t FDSR;                              /**< LCD Fault Detect Status Register, offset: 0xC */
  __IO uint32_t PEN[2];                            /**< LCD Pin Enable register, array offset: 0x10, array step: 0x4 */
  __IO uint32_t BPEN[2];                           /**< LCD Back Plane Enable register, array offset: 0x18, array step: 0x4 */
  union {                                          /* offset: 0x20 */
    __IO uint8_t WF8B[64];                           /**< LCD Waveform Register 0...LCD Waveform Register 63., array offset: 0x20, array step: 0x1 */
    __IO uint32_t WF[16];                            /**< LCD Waveform register, array offset: 0x20, array step: 0x4 */
  };
} LCD_Type;

/* ----------------------------------------------------------------------------
   -- LCD Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LCD_Register_Masks LCD Register Masks
 * @{
 */

/*! @name GCR - LCD General Control Register */
/*! @{ */

#define LCD_GCR_DUTY_MASK                        (0x7U)
#define LCD_GCR_DUTY_SHIFT                       (0U)
/*! DUTY - LCD duty select
 *  0b000..Use 1 BP (1/1 duty cycle).
 *  0b001..Use 2 BP (1/2 duty cycle).
 *  0b010..Use 3 BP (1/3 duty cycle).
 *  0b011..Use 4 BP (1/4 duty cycle). (Default)
 *  0b100..
 *  0b101..
 *  0b110..
 *  0b111..Use 8 BP (1/8 duty cycle).
 */
#define LCD_GCR_DUTY(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_GCR_DUTY_SHIFT)) & LCD_GCR_DUTY_MASK)

#define LCD_GCR_LCLK_MASK                        (0x38U)
#define LCD_GCR_LCLK_SHIFT                       (3U)
/*! LCLK - LCD Clock Prescaler */
#define LCD_GCR_LCLK(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_GCR_LCLK_SHIFT)) & LCD_GCR_LCLK_MASK)

#define LCD_GCR_SOURCE_MASK                      (0x40U)
#define LCD_GCR_SOURCE_SHIFT                     (6U)
/*! SOURCE - LCD Clock Source Select
 *  0b0..Selects the default clock as the LCD clock source.
 *  0b1..Selects output of the alternate clock source selection (see ALTSOURCE) as the LCD clock source.
 */
#define LCD_GCR_SOURCE(x)                        (((uint32_t)(((uint32_t)(x)) << LCD_GCR_SOURCE_SHIFT)) & LCD_GCR_SOURCE_MASK)

#define LCD_GCR_LCDEN_MASK                       (0x80U)
#define LCD_GCR_LCDEN_SHIFT                      (7U)
/*! LCDEN - LCD Driver Enable
 *  0b0..All front plane and back plane pins are disabled. The LCD controller system is also disabled, and all LCD
 *       waveform generation clocks are stopped. V LL3 is connected to V DD internally. All LCD pins, LCD_Pn,
 *       enabled using the LCD Pin Enable register, output a low value.
 *  0b1..LCD controller driver system is enabled, and front plane and back plane waveforms are generated. All LCD
 *       pins, LCD_Pn, enabled if PAD_SAFE is clearusing the LCD Pin Enable register, output an LCD driver
 *       waveform. The back plane pins output an LCD driver back plane waveform based on the settings of DUTY[2:0]. Charge
 *       pump or resistor bias is enabled.
 */
#define LCD_GCR_LCDEN(x)                         (((uint32_t)(((uint32_t)(x)) << LCD_GCR_LCDEN_SHIFT)) & LCD_GCR_LCDEN_MASK)

#define LCD_GCR_LCDSTP_MASK                      (0x100U)
#define LCD_GCR_LCDSTP_SHIFT                     (8U)
/*! LCDSTP - LCD Stop
 *  0b0..Allows the LCD driver, charge pump, resistor bias network, and voltage regulator to continue running during Stop mode.
 *  0b1..Disables the LCD driver, charge pump, resistor bias network, and voltage regulator when MCU enters Stop mode.
 */
#define LCD_GCR_LCDSTP(x)                        (((uint32_t)(((uint32_t)(x)) << LCD_GCR_LCDSTP_SHIFT)) & LCD_GCR_LCDSTP_MASK)

#define LCD_GCR_LCDDOZE_MASK                     (0x200U)
#define LCD_GCR_LCDDOZE_SHIFT                    (9U)
/*! LCDDOZE - LCD Doze enable
 *  0b0..Allows the LCD driver, charge pump, resistor bias network, and voltage regulator to continue running during Doze mode.
 *  0b1..Disables the LCD driver, charge pump, resistor bias network, and voltage regulator when MCU enters Doze mode.
 */
#define LCD_GCR_LCDDOZE(x)                       (((uint32_t)(((uint32_t)(x)) << LCD_GCR_LCDDOZE_SHIFT)) & LCD_GCR_LCDDOZE_MASK)

#define LCD_GCR_FFR_MASK                         (0x400U)
#define LCD_GCR_FFR_SHIFT                        (10U)
/*! FFR - Fast Frame Rate Select
 *  0b0..Standard Frame Rate LCD Frame Freq: 23.3 (min) 73.1 (max)
 *  0b1..Fast Frame Rate (Standard Frame Rate x2) LCD Frame Freq: 46.6 (min) 146.2 (max)
 */
#define LCD_GCR_FFR(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_GCR_FFR_SHIFT)) & LCD_GCR_FFR_MASK)

#define LCD_GCR_ALTSOURCE_MASK                   (0x800U)
#define LCD_GCR_ALTSOURCE_SHIFT                  (11U)
/*! ALTSOURCE - Selects the alternate clock source
 *  0b0..Select Alternate Clock Source 1 (default)
 *  0b1..Select Alternate Clock Source 2
 */
#define LCD_GCR_ALTSOURCE(x)                     (((uint32_t)(((uint32_t)(x)) << LCD_GCR_ALTSOURCE_SHIFT)) & LCD_GCR_ALTSOURCE_MASK)

#define LCD_GCR_ALTDIV_MASK                      (0x3000U)
#define LCD_GCR_ALTDIV_SHIFT                     (12U)
/*! ALTDIV - LCD AlternateClock Divider
 *  0b00..Divide factor = 1 (No divide)
 *  0b01..Divide factor = 8
 *  0b10..Divide factor = 64
 *  0b11..Divide factor = 512
 */
#define LCD_GCR_ALTDIV(x)                        (((uint32_t)(((uint32_t)(x)) << LCD_GCR_ALTDIV_SHIFT)) & LCD_GCR_ALTDIV_MASK)

#define LCD_GCR_FDCIEN_MASK                      (0x4000U)
#define LCD_GCR_FDCIEN_SHIFT                     (14U)
/*! FDCIEN - LCD Fault Detection Complete Interrupt Enable
 *  0b0..No interrupt request is generated by this event.
 *  0b1..When a fault is detected and FDCF bit is set, this event causes an interrupt request.
 */
#define LCD_GCR_FDCIEN(x)                        (((uint32_t)(((uint32_t)(x)) << LCD_GCR_FDCIEN_SHIFT)) & LCD_GCR_FDCIEN_MASK)

#define LCD_GCR_PADSAFE_MASK                     (0x8000U)
#define LCD_GCR_PADSAFE_SHIFT                    (15U)
/*! PADSAFE - Pad Safe State Enable
 *  0b0..LCD frontplane and backplane functions enabled according to other LCD control bits
 *  0b1..LCD frontplane and backplane functions disabled
 */
#define LCD_GCR_PADSAFE(x)                       (((uint32_t)(((uint32_t)(x)) << LCD_GCR_PADSAFE_SHIFT)) & LCD_GCR_PADSAFE_MASK)

#define LCD_GCR_VSUPPLY_MASK                     (0x20000U)
#define LCD_GCR_VSUPPLY_SHIFT                    (17U)
/*! VSUPPLY - Voltage Supply Control
 *  0b0..Drive VLL3 internally from VDD
 *  0b1..Drive VLL3 externally from VDD or drive VLL internally from vIREG
 */
#define LCD_GCR_VSUPPLY(x)                       (((uint32_t)(((uint32_t)(x)) << LCD_GCR_VSUPPLY_SHIFT)) & LCD_GCR_VSUPPLY_MASK)

#define LCD_GCR_LADJ_MASK                        (0x300000U)
#define LCD_GCR_LADJ_SHIFT                       (20U)
/*! LADJ - Load Adjust */
#define LCD_GCR_LADJ(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_GCR_LADJ_SHIFT)) & LCD_GCR_LADJ_MASK)

#define LCD_GCR_CPSEL_MASK                       (0x800000U)
#define LCD_GCR_CPSEL_SHIFT                      (23U)
/*! CPSEL - Charge Pump or Resistor Bias Select
 *  0b0..LCD charge pump is disabled. Resistor network selected. (The internal 1/3-bias is forced.)
 *  0b1..LCD charge pump is selected. Resistor network disabled. (The internal 1/3-bias is forced.)
 */
#define LCD_GCR_CPSEL(x)                         (((uint32_t)(((uint32_t)(x)) << LCD_GCR_CPSEL_SHIFT)) & LCD_GCR_CPSEL_MASK)

#define LCD_GCR_RVTRIM_MASK                      (0xF000000U)
#define LCD_GCR_RVTRIM_SHIFT                     (24U)
/*! RVTRIM - Regulated Voltage Trim */
#define LCD_GCR_RVTRIM(x)                        (((uint32_t)(((uint32_t)(x)) << LCD_GCR_RVTRIM_SHIFT)) & LCD_GCR_RVTRIM_MASK)

#define LCD_GCR_RVEN_MASK                        (0x80000000U)
#define LCD_GCR_RVEN_SHIFT                       (31U)
/*! RVEN - Regulated Voltage Enable
 *  0b0..Regulated voltage disabled.
 *  0b1..Regulated voltage enabled.
 */
#define LCD_GCR_RVEN(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_GCR_RVEN_SHIFT)) & LCD_GCR_RVEN_MASK)
/*! @} */

/*! @name AR - LCD Auxiliary Register */
/*! @{ */

#define LCD_AR_BRATE_MASK                        (0x7U)
#define LCD_AR_BRATE_SHIFT                       (0U)
/*! BRATE - Blink-rate configuration */
#define LCD_AR_BRATE(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_AR_BRATE_SHIFT)) & LCD_AR_BRATE_MASK)

#define LCD_AR_BMODE_MASK                        (0x8U)
#define LCD_AR_BMODE_SHIFT                       (3U)
/*! BMODE - Blink mode
 *  0b0..Display blank during the blink period.
 *  0b1..Display alternate display during blink period (Ignored if duty is 5 or greater).
 */
#define LCD_AR_BMODE(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_AR_BMODE_SHIFT)) & LCD_AR_BMODE_MASK)

#define LCD_AR_BLANK_MASK                        (0x20U)
#define LCD_AR_BLANK_SHIFT                       (5U)
/*! BLANK - Blank display mode
 *  0b0..Normal or alternate display mode.
 *  0b1..Blank display mode.
 */
#define LCD_AR_BLANK(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_AR_BLANK_SHIFT)) & LCD_AR_BLANK_MASK)

#define LCD_AR_ALT_MASK                          (0x40U)
#define LCD_AR_ALT_SHIFT                         (6U)
/*! ALT - Alternate display mode
 *  0b0..Normal display mode.
 *  0b1..Alternate display mode.
 */
#define LCD_AR_ALT(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_AR_ALT_SHIFT)) & LCD_AR_ALT_MASK)

#define LCD_AR_BLINK_MASK                        (0x80U)
#define LCD_AR_BLINK_SHIFT                       (7U)
/*! BLINK - Blink command
 *  0b0..Disables blinking.
 *  0b1..Starts blinking at blinking frequency specified by LCD blink rate calculation.
 */
#define LCD_AR_BLINK(x)                          (((uint32_t)(((uint32_t)(x)) << LCD_AR_BLINK_SHIFT)) & LCD_AR_BLINK_MASK)
/*! @} */

/*! @name FDCR - LCD Fault Detect Control Register */
/*! @{ */

#define LCD_FDCR_FDPINID_MASK                    (0x3FU)
#define LCD_FDCR_FDPINID_SHIFT                   (0U)
/*! FDPINID - Fault Detect Pin ID
 *  0b000000..Fault detection for LCD_P0 pin.
 *  0b000001..Fault detection for LCD_P1 pin.
 *  0b111111..Fault detection for LCD_P63 pin.
 */
#define LCD_FDCR_FDPINID(x)                      (((uint32_t)(((uint32_t)(x)) << LCD_FDCR_FDPINID_SHIFT)) & LCD_FDCR_FDPINID_MASK)

#define LCD_FDCR_FDBPEN_MASK                     (0x40U)
#define LCD_FDCR_FDBPEN_SHIFT                    (6U)
/*! FDBPEN - Fault Detect Back Plane Enable
 *  0b0..Type of the selected pin under fault detect test is front plane.
 *  0b1..Type of the selected pin under fault detect test is back plane.
 */
#define LCD_FDCR_FDBPEN(x)                       (((uint32_t)(((uint32_t)(x)) << LCD_FDCR_FDBPEN_SHIFT)) & LCD_FDCR_FDBPEN_MASK)

#define LCD_FDCR_FDEN_MASK                       (0x80U)
#define LCD_FDCR_FDEN_SHIFT                      (7U)
/*! FDEN - Fault Detect Enable
 *  0b0..Disable fault detection.
 *  0b1..Enable fault detection.
 */
#define LCD_FDCR_FDEN(x)                         (((uint32_t)(((uint32_t)(x)) << LCD_FDCR_FDEN_SHIFT)) & LCD_FDCR_FDEN_MASK)

#define LCD_FDCR_FDSWW_MASK                      (0xE00U)
#define LCD_FDCR_FDSWW_SHIFT                     (9U)
/*! FDSWW - Fault Detect Sample Window Width
 *  0b000..Sample window width is 4 sample clock cycles.
 *  0b001..Sample window width is 8 sample clock cycles.
 *  0b010..Sample window width is 16 sample clock cycles.
 *  0b011..Sample window width is 32 sample clock cycles.
 *  0b100..Sample window width is 64 sample clock cycles.
 *  0b101..Sample window width is 128 sample clock cycles.
 *  0b110..Sample window width is 256 sample clock cycles.
 *  0b111..Sample window width is 512 sample clock cycles.
 */
#define LCD_FDCR_FDSWW(x)                        (((uint32_t)(((uint32_t)(x)) << LCD_FDCR_FDSWW_SHIFT)) & LCD_FDCR_FDSWW_MASK)

#define LCD_FDCR_FDPRS_MASK                      (0x7000U)
#define LCD_FDCR_FDPRS_SHIFT                     (12U)
/*! FDPRS - Fault Detect Clock Prescaler
 *  0b000..1/1 bus clock.
 *  0b001..1/2 bus clock.
 *  0b010..1/4 bus clock.
 *  0b011..1/8 bus clock.
 *  0b100..1/16 bus clock.
 *  0b101..1/32 bus clock.
 *  0b110..1/64 bus clock.
 *  0b111..1/128 bus clock.
 */
#define LCD_FDCR_FDPRS(x)                        (((uint32_t)(((uint32_t)(x)) << LCD_FDCR_FDPRS_SHIFT)) & LCD_FDCR_FDPRS_MASK)
/*! @} */

/*! @name FDSR - LCD Fault Detect Status Register */
/*! @{ */

#define LCD_FDSR_FDCNT_MASK                      (0xFFU)
#define LCD_FDSR_FDCNT_SHIFT                     (0U)
/*! FDCNT - Fault Detect Counter
 *  0b00000000..No "one" samples.
 *  0b00000001..1 "one" samples.
 *  0b00000010..2 "one" samples.
 *  0b11111110..254 "one" samples.
 *  0b11111111..255 or more "one" samples. The FDCNT can overflow. Therefore, FDSWW and FDPRS must be reconfigured for proper sampling.
 */
#define LCD_FDSR_FDCNT(x)                        (((uint32_t)(((uint32_t)(x)) << LCD_FDSR_FDCNT_SHIFT)) & LCD_FDSR_FDCNT_MASK)

#define LCD_FDSR_FDCF_MASK                       (0x8000U)
#define LCD_FDSR_FDCF_SHIFT                      (15U)
/*! FDCF - Fault Detection Complete Flag
 *  0b0..Fault detection is not completed.
 *  0b1..Fault detection is completed.
 */
#define LCD_FDSR_FDCF(x)                         (((uint32_t)(((uint32_t)(x)) << LCD_FDSR_FDCF_SHIFT)) & LCD_FDSR_FDCF_MASK)
/*! @} */

/*! @name PEN - LCD Pin Enable register */
/*! @{ */

#define LCD_PEN_PEN_MASK                         (0xFFFFFFFFU)
#define LCD_PEN_PEN_SHIFT                        (0U)
/*! PEN - LCD Pin Enable
 *  0b00000000000000000000000000000000..LCD operation disabled on LCD_Pn.
 *  0b00000000000000000000000000000001..LCD operation enabled on LCD_Pn.
 */
#define LCD_PEN_PEN(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_PEN_PEN_SHIFT)) & LCD_PEN_PEN_MASK)
/*! @} */

/* The count of LCD_PEN */
#define LCD_PEN_COUNT                            (2U)

/*! @name BPEN - LCD Back Plane Enable register */
/*! @{ */

#define LCD_BPEN_BPEN_MASK                       (0xFFFFFFFFU)
#define LCD_BPEN_BPEN_SHIFT                      (0U)
/*! BPEN - Back Plane Enable
 *  0b00000000000000000000000000000000..Front plane operation enabled on LCD_Pn.
 *  0b00000000000000000000000000000001..Back plane operation enabled on LCD_Pn.
 */
#define LCD_BPEN_BPEN(x)                         (((uint32_t)(((uint32_t)(x)) << LCD_BPEN_BPEN_SHIFT)) & LCD_BPEN_BPEN_MASK)
/*! @} */

/* The count of LCD_BPEN */
#define LCD_BPEN_COUNT                           (2U)

/*! @name WF8B - LCD Waveform Register 0...LCD Waveform Register 63. */
/*! @{ */

#define LCD_WF8B_BPALCD0_MASK                    (0x1U)
#define LCD_WF8B_BPALCD0_SHIFT                   (0U)
/*! BPALCD0
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD0(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD0_SHIFT)) & LCD_WF8B_BPALCD0_MASK)

#define LCD_WF8B_BPALCD1_MASK                    (0x1U)
#define LCD_WF8B_BPALCD1_SHIFT                   (0U)
/*! BPALCD1
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD1(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD1_SHIFT)) & LCD_WF8B_BPALCD1_MASK)

#define LCD_WF8B_BPALCD2_MASK                    (0x1U)
#define LCD_WF8B_BPALCD2_SHIFT                   (0U)
/*! BPALCD2
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD2(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD2_SHIFT)) & LCD_WF8B_BPALCD2_MASK)

#define LCD_WF8B_BPALCD3_MASK                    (0x1U)
#define LCD_WF8B_BPALCD3_SHIFT                   (0U)
/*! BPALCD3
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD3(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD3_SHIFT)) & LCD_WF8B_BPALCD3_MASK)

#define LCD_WF8B_BPALCD4_MASK                    (0x1U)
#define LCD_WF8B_BPALCD4_SHIFT                   (0U)
/*! BPALCD4
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD4(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD4_SHIFT)) & LCD_WF8B_BPALCD4_MASK)

#define LCD_WF8B_BPALCD5_MASK                    (0x1U)
#define LCD_WF8B_BPALCD5_SHIFT                   (0U)
/*! BPALCD5
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD5(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD5_SHIFT)) & LCD_WF8B_BPALCD5_MASK)

#define LCD_WF8B_BPALCD6_MASK                    (0x1U)
#define LCD_WF8B_BPALCD6_SHIFT                   (0U)
/*! BPALCD6
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD6(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD6_SHIFT)) & LCD_WF8B_BPALCD6_MASK)

#define LCD_WF8B_BPALCD7_MASK                    (0x1U)
#define LCD_WF8B_BPALCD7_SHIFT                   (0U)
/*! BPALCD7
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD7(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD7_SHIFT)) & LCD_WF8B_BPALCD7_MASK)

#define LCD_WF8B_BPALCD8_MASK                    (0x1U)
#define LCD_WF8B_BPALCD8_SHIFT                   (0U)
/*! BPALCD8
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD8(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD8_SHIFT)) & LCD_WF8B_BPALCD8_MASK)

#define LCD_WF8B_BPALCD9_MASK                    (0x1U)
#define LCD_WF8B_BPALCD9_SHIFT                   (0U)
/*! BPALCD9
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD9(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD9_SHIFT)) & LCD_WF8B_BPALCD9_MASK)

#define LCD_WF8B_BPALCD10_MASK                   (0x1U)
#define LCD_WF8B_BPALCD10_SHIFT                  (0U)
/*! BPALCD10
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD10(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD10_SHIFT)) & LCD_WF8B_BPALCD10_MASK)

#define LCD_WF8B_BPALCD11_MASK                   (0x1U)
#define LCD_WF8B_BPALCD11_SHIFT                  (0U)
/*! BPALCD11
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD11(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD11_SHIFT)) & LCD_WF8B_BPALCD11_MASK)

#define LCD_WF8B_BPALCD12_MASK                   (0x1U)
#define LCD_WF8B_BPALCD12_SHIFT                  (0U)
/*! BPALCD12
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD12(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD12_SHIFT)) & LCD_WF8B_BPALCD12_MASK)

#define LCD_WF8B_BPALCD13_MASK                   (0x1U)
#define LCD_WF8B_BPALCD13_SHIFT                  (0U)
/*! BPALCD13
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD13(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD13_SHIFT)) & LCD_WF8B_BPALCD13_MASK)

#define LCD_WF8B_BPALCD14_MASK                   (0x1U)
#define LCD_WF8B_BPALCD14_SHIFT                  (0U)
/*! BPALCD14
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD14(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD14_SHIFT)) & LCD_WF8B_BPALCD14_MASK)

#define LCD_WF8B_BPALCD15_MASK                   (0x1U)
#define LCD_WF8B_BPALCD15_SHIFT                  (0U)
/*! BPALCD15
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD15(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD15_SHIFT)) & LCD_WF8B_BPALCD15_MASK)

#define LCD_WF8B_BPALCD16_MASK                   (0x1U)
#define LCD_WF8B_BPALCD16_SHIFT                  (0U)
/*! BPALCD16
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD16(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD16_SHIFT)) & LCD_WF8B_BPALCD16_MASK)

#define LCD_WF8B_BPALCD17_MASK                   (0x1U)
#define LCD_WF8B_BPALCD17_SHIFT                  (0U)
/*! BPALCD17
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD17(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD17_SHIFT)) & LCD_WF8B_BPALCD17_MASK)

#define LCD_WF8B_BPALCD18_MASK                   (0x1U)
#define LCD_WF8B_BPALCD18_SHIFT                  (0U)
/*! BPALCD18
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD18(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD18_SHIFT)) & LCD_WF8B_BPALCD18_MASK)

#define LCD_WF8B_BPALCD19_MASK                   (0x1U)
#define LCD_WF8B_BPALCD19_SHIFT                  (0U)
/*! BPALCD19
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD19(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD19_SHIFT)) & LCD_WF8B_BPALCD19_MASK)

#define LCD_WF8B_BPALCD20_MASK                   (0x1U)
#define LCD_WF8B_BPALCD20_SHIFT                  (0U)
/*! BPALCD20
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD20(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD20_SHIFT)) & LCD_WF8B_BPALCD20_MASK)

#define LCD_WF8B_BPALCD21_MASK                   (0x1U)
#define LCD_WF8B_BPALCD21_SHIFT                  (0U)
/*! BPALCD21
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD21(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD21_SHIFT)) & LCD_WF8B_BPALCD21_MASK)

#define LCD_WF8B_BPALCD22_MASK                   (0x1U)
#define LCD_WF8B_BPALCD22_SHIFT                  (0U)
/*! BPALCD22
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD22(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD22_SHIFT)) & LCD_WF8B_BPALCD22_MASK)

#define LCD_WF8B_BPALCD23_MASK                   (0x1U)
#define LCD_WF8B_BPALCD23_SHIFT                  (0U)
/*! BPALCD23
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD23(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD23_SHIFT)) & LCD_WF8B_BPALCD23_MASK)

#define LCD_WF8B_BPALCD24_MASK                   (0x1U)
#define LCD_WF8B_BPALCD24_SHIFT                  (0U)
/*! BPALCD24
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD24(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD24_SHIFT)) & LCD_WF8B_BPALCD24_MASK)

#define LCD_WF8B_BPALCD25_MASK                   (0x1U)
#define LCD_WF8B_BPALCD25_SHIFT                  (0U)
/*! BPALCD25
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD25(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD25_SHIFT)) & LCD_WF8B_BPALCD25_MASK)

#define LCD_WF8B_BPALCD26_MASK                   (0x1U)
#define LCD_WF8B_BPALCD26_SHIFT                  (0U)
/*! BPALCD26
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD26(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD26_SHIFT)) & LCD_WF8B_BPALCD26_MASK)

#define LCD_WF8B_BPALCD27_MASK                   (0x1U)
#define LCD_WF8B_BPALCD27_SHIFT                  (0U)
/*! BPALCD27
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD27(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD27_SHIFT)) & LCD_WF8B_BPALCD27_MASK)

#define LCD_WF8B_BPALCD28_MASK                   (0x1U)
#define LCD_WF8B_BPALCD28_SHIFT                  (0U)
/*! BPALCD28
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD28(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD28_SHIFT)) & LCD_WF8B_BPALCD28_MASK)

#define LCD_WF8B_BPALCD29_MASK                   (0x1U)
#define LCD_WF8B_BPALCD29_SHIFT                  (0U)
/*! BPALCD29
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD29(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD29_SHIFT)) & LCD_WF8B_BPALCD29_MASK)

#define LCD_WF8B_BPALCD30_MASK                   (0x1U)
#define LCD_WF8B_BPALCD30_SHIFT                  (0U)
/*! BPALCD30
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD30(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD30_SHIFT)) & LCD_WF8B_BPALCD30_MASK)

#define LCD_WF8B_BPALCD31_MASK                   (0x1U)
#define LCD_WF8B_BPALCD31_SHIFT                  (0U)
/*! BPALCD31
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD31(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD31_SHIFT)) & LCD_WF8B_BPALCD31_MASK)

#define LCD_WF8B_BPALCD32_MASK                   (0x1U)
#define LCD_WF8B_BPALCD32_SHIFT                  (0U)
/*! BPALCD32
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD32(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD32_SHIFT)) & LCD_WF8B_BPALCD32_MASK)

#define LCD_WF8B_BPALCD33_MASK                   (0x1U)
#define LCD_WF8B_BPALCD33_SHIFT                  (0U)
/*! BPALCD33
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD33(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD33_SHIFT)) & LCD_WF8B_BPALCD33_MASK)

#define LCD_WF8B_BPALCD34_MASK                   (0x1U)
#define LCD_WF8B_BPALCD34_SHIFT                  (0U)
/*! BPALCD34
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD34(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD34_SHIFT)) & LCD_WF8B_BPALCD34_MASK)

#define LCD_WF8B_BPALCD35_MASK                   (0x1U)
#define LCD_WF8B_BPALCD35_SHIFT                  (0U)
/*! BPALCD35
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD35(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD35_SHIFT)) & LCD_WF8B_BPALCD35_MASK)

#define LCD_WF8B_BPALCD36_MASK                   (0x1U)
#define LCD_WF8B_BPALCD36_SHIFT                  (0U)
/*! BPALCD36
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD36(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD36_SHIFT)) & LCD_WF8B_BPALCD36_MASK)

#define LCD_WF8B_BPALCD37_MASK                   (0x1U)
#define LCD_WF8B_BPALCD37_SHIFT                  (0U)
/*! BPALCD37
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD37(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD37_SHIFT)) & LCD_WF8B_BPALCD37_MASK)

#define LCD_WF8B_BPALCD38_MASK                   (0x1U)
#define LCD_WF8B_BPALCD38_SHIFT                  (0U)
/*! BPALCD38
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD38(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD38_SHIFT)) & LCD_WF8B_BPALCD38_MASK)

#define LCD_WF8B_BPALCD39_MASK                   (0x1U)
#define LCD_WF8B_BPALCD39_SHIFT                  (0U)
/*! BPALCD39
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD39(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD39_SHIFT)) & LCD_WF8B_BPALCD39_MASK)

#define LCD_WF8B_BPALCD40_MASK                   (0x1U)
#define LCD_WF8B_BPALCD40_SHIFT                  (0U)
/*! BPALCD40
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD40(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD40_SHIFT)) & LCD_WF8B_BPALCD40_MASK)

#define LCD_WF8B_BPALCD41_MASK                   (0x1U)
#define LCD_WF8B_BPALCD41_SHIFT                  (0U)
/*! BPALCD41
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD41(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD41_SHIFT)) & LCD_WF8B_BPALCD41_MASK)

#define LCD_WF8B_BPALCD42_MASK                   (0x1U)
#define LCD_WF8B_BPALCD42_SHIFT                  (0U)
/*! BPALCD42
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD42(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD42_SHIFT)) & LCD_WF8B_BPALCD42_MASK)

#define LCD_WF8B_BPALCD43_MASK                   (0x1U)
#define LCD_WF8B_BPALCD43_SHIFT                  (0U)
/*! BPALCD43
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD43(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD43_SHIFT)) & LCD_WF8B_BPALCD43_MASK)

#define LCD_WF8B_BPALCD44_MASK                   (0x1U)
#define LCD_WF8B_BPALCD44_SHIFT                  (0U)
/*! BPALCD44
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD44(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD44_SHIFT)) & LCD_WF8B_BPALCD44_MASK)

#define LCD_WF8B_BPALCD45_MASK                   (0x1U)
#define LCD_WF8B_BPALCD45_SHIFT                  (0U)
/*! BPALCD45
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD45(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD45_SHIFT)) & LCD_WF8B_BPALCD45_MASK)

#define LCD_WF8B_BPALCD46_MASK                   (0x1U)
#define LCD_WF8B_BPALCD46_SHIFT                  (0U)
/*! BPALCD46
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD46(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD46_SHIFT)) & LCD_WF8B_BPALCD46_MASK)

#define LCD_WF8B_BPALCD47_MASK                   (0x1U)
#define LCD_WF8B_BPALCD47_SHIFT                  (0U)
/*! BPALCD47
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD47(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD47_SHIFT)) & LCD_WF8B_BPALCD47_MASK)

#define LCD_WF8B_BPALCD48_MASK                   (0x1U)
#define LCD_WF8B_BPALCD48_SHIFT                  (0U)
/*! BPALCD48
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD48(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD48_SHIFT)) & LCD_WF8B_BPALCD48_MASK)

#define LCD_WF8B_BPALCD49_MASK                   (0x1U)
#define LCD_WF8B_BPALCD49_SHIFT                  (0U)
/*! BPALCD49
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD49(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD49_SHIFT)) & LCD_WF8B_BPALCD49_MASK)

#define LCD_WF8B_BPALCD50_MASK                   (0x1U)
#define LCD_WF8B_BPALCD50_SHIFT                  (0U)
/*! BPALCD50
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD50(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD50_SHIFT)) & LCD_WF8B_BPALCD50_MASK)

#define LCD_WF8B_BPALCD51_MASK                   (0x1U)
#define LCD_WF8B_BPALCD51_SHIFT                  (0U)
/*! BPALCD51
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD51(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD51_SHIFT)) & LCD_WF8B_BPALCD51_MASK)

#define LCD_WF8B_BPALCD52_MASK                   (0x1U)
#define LCD_WF8B_BPALCD52_SHIFT                  (0U)
/*! BPALCD52
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD52(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD52_SHIFT)) & LCD_WF8B_BPALCD52_MASK)

#define LCD_WF8B_BPALCD53_MASK                   (0x1U)
#define LCD_WF8B_BPALCD53_SHIFT                  (0U)
/*! BPALCD53
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD53(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD53_SHIFT)) & LCD_WF8B_BPALCD53_MASK)

#define LCD_WF8B_BPALCD54_MASK                   (0x1U)
#define LCD_WF8B_BPALCD54_SHIFT                  (0U)
/*! BPALCD54
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD54(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD54_SHIFT)) & LCD_WF8B_BPALCD54_MASK)

#define LCD_WF8B_BPALCD55_MASK                   (0x1U)
#define LCD_WF8B_BPALCD55_SHIFT                  (0U)
/*! BPALCD55
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD55(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD55_SHIFT)) & LCD_WF8B_BPALCD55_MASK)

#define LCD_WF8B_BPALCD56_MASK                   (0x1U)
#define LCD_WF8B_BPALCD56_SHIFT                  (0U)
/*! BPALCD56
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD56(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD56_SHIFT)) & LCD_WF8B_BPALCD56_MASK)

#define LCD_WF8B_BPALCD57_MASK                   (0x1U)
#define LCD_WF8B_BPALCD57_SHIFT                  (0U)
/*! BPALCD57
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD57(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD57_SHIFT)) & LCD_WF8B_BPALCD57_MASK)

#define LCD_WF8B_BPALCD58_MASK                   (0x1U)
#define LCD_WF8B_BPALCD58_SHIFT                  (0U)
/*! BPALCD58
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD58(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD58_SHIFT)) & LCD_WF8B_BPALCD58_MASK)

#define LCD_WF8B_BPALCD59_MASK                   (0x1U)
#define LCD_WF8B_BPALCD59_SHIFT                  (0U)
/*! BPALCD59
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD59(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD59_SHIFT)) & LCD_WF8B_BPALCD59_MASK)

#define LCD_WF8B_BPALCD60_MASK                   (0x1U)
#define LCD_WF8B_BPALCD60_SHIFT                  (0U)
/*! BPALCD60
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD60(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD60_SHIFT)) & LCD_WF8B_BPALCD60_MASK)

#define LCD_WF8B_BPALCD61_MASK                   (0x1U)
#define LCD_WF8B_BPALCD61_SHIFT                  (0U)
/*! BPALCD61
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD61(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD61_SHIFT)) & LCD_WF8B_BPALCD61_MASK)

#define LCD_WF8B_BPALCD62_MASK                   (0x1U)
#define LCD_WF8B_BPALCD62_SHIFT                  (0U)
/*! BPALCD62
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD62(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD62_SHIFT)) & LCD_WF8B_BPALCD62_MASK)

#define LCD_WF8B_BPALCD63_MASK                   (0x1U)
#define LCD_WF8B_BPALCD63_SHIFT                  (0U)
/*! BPALCD63
 *  0b0..LCD segment off or LCD backplane inactive for phase A
 *  0b1..LCD segment on or LCD backplane active for phase A
 */
#define LCD_WF8B_BPALCD63(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPALCD63_SHIFT)) & LCD_WF8B_BPALCD63_MASK)

#define LCD_WF8B_BPBLCD0_MASK                    (0x2U)
#define LCD_WF8B_BPBLCD0_SHIFT                   (1U)
/*! BPBLCD0
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD0(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD0_SHIFT)) & LCD_WF8B_BPBLCD0_MASK)

#define LCD_WF8B_BPBLCD1_MASK                    (0x2U)
#define LCD_WF8B_BPBLCD1_SHIFT                   (1U)
/*! BPBLCD1
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD1(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD1_SHIFT)) & LCD_WF8B_BPBLCD1_MASK)

#define LCD_WF8B_BPBLCD2_MASK                    (0x2U)
#define LCD_WF8B_BPBLCD2_SHIFT                   (1U)
/*! BPBLCD2
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD2(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD2_SHIFT)) & LCD_WF8B_BPBLCD2_MASK)

#define LCD_WF8B_BPBLCD3_MASK                    (0x2U)
#define LCD_WF8B_BPBLCD3_SHIFT                   (1U)
/*! BPBLCD3
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD3(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD3_SHIFT)) & LCD_WF8B_BPBLCD3_MASK)

#define LCD_WF8B_BPBLCD4_MASK                    (0x2U)
#define LCD_WF8B_BPBLCD4_SHIFT                   (1U)
/*! BPBLCD4
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD4(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD4_SHIFT)) & LCD_WF8B_BPBLCD4_MASK)

#define LCD_WF8B_BPBLCD5_MASK                    (0x2U)
#define LCD_WF8B_BPBLCD5_SHIFT                   (1U)
/*! BPBLCD5
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD5(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD5_SHIFT)) & LCD_WF8B_BPBLCD5_MASK)

#define LCD_WF8B_BPBLCD6_MASK                    (0x2U)
#define LCD_WF8B_BPBLCD6_SHIFT                   (1U)
/*! BPBLCD6
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD6(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD6_SHIFT)) & LCD_WF8B_BPBLCD6_MASK)

#define LCD_WF8B_BPBLCD7_MASK                    (0x2U)
#define LCD_WF8B_BPBLCD7_SHIFT                   (1U)
/*! BPBLCD7
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD7(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD7_SHIFT)) & LCD_WF8B_BPBLCD7_MASK)

#define LCD_WF8B_BPBLCD8_MASK                    (0x2U)
#define LCD_WF8B_BPBLCD8_SHIFT                   (1U)
/*! BPBLCD8
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD8(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD8_SHIFT)) & LCD_WF8B_BPBLCD8_MASK)

#define LCD_WF8B_BPBLCD9_MASK                    (0x2U)
#define LCD_WF8B_BPBLCD9_SHIFT                   (1U)
/*! BPBLCD9
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD9(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD9_SHIFT)) & LCD_WF8B_BPBLCD9_MASK)

#define LCD_WF8B_BPBLCD10_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD10_SHIFT                  (1U)
/*! BPBLCD10
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD10(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD10_SHIFT)) & LCD_WF8B_BPBLCD10_MASK)

#define LCD_WF8B_BPBLCD11_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD11_SHIFT                  (1U)
/*! BPBLCD11
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD11(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD11_SHIFT)) & LCD_WF8B_BPBLCD11_MASK)

#define LCD_WF8B_BPBLCD12_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD12_SHIFT                  (1U)
/*! BPBLCD12
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD12(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD12_SHIFT)) & LCD_WF8B_BPBLCD12_MASK)

#define LCD_WF8B_BPBLCD13_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD13_SHIFT                  (1U)
/*! BPBLCD13
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD13(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD13_SHIFT)) & LCD_WF8B_BPBLCD13_MASK)

#define LCD_WF8B_BPBLCD14_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD14_SHIFT                  (1U)
/*! BPBLCD14
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD14(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD14_SHIFT)) & LCD_WF8B_BPBLCD14_MASK)

#define LCD_WF8B_BPBLCD15_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD15_SHIFT                  (1U)
/*! BPBLCD15
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD15(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD15_SHIFT)) & LCD_WF8B_BPBLCD15_MASK)

#define LCD_WF8B_BPBLCD16_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD16_SHIFT                  (1U)
/*! BPBLCD16
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD16(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD16_SHIFT)) & LCD_WF8B_BPBLCD16_MASK)

#define LCD_WF8B_BPBLCD17_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD17_SHIFT                  (1U)
/*! BPBLCD17
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD17(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD17_SHIFT)) & LCD_WF8B_BPBLCD17_MASK)

#define LCD_WF8B_BPBLCD18_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD18_SHIFT                  (1U)
/*! BPBLCD18
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD18(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD18_SHIFT)) & LCD_WF8B_BPBLCD18_MASK)

#define LCD_WF8B_BPBLCD19_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD19_SHIFT                  (1U)
/*! BPBLCD19
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD19(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD19_SHIFT)) & LCD_WF8B_BPBLCD19_MASK)

#define LCD_WF8B_BPBLCD20_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD20_SHIFT                  (1U)
/*! BPBLCD20
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD20(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD20_SHIFT)) & LCD_WF8B_BPBLCD20_MASK)

#define LCD_WF8B_BPBLCD21_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD21_SHIFT                  (1U)
/*! BPBLCD21
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD21(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD21_SHIFT)) & LCD_WF8B_BPBLCD21_MASK)

#define LCD_WF8B_BPBLCD22_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD22_SHIFT                  (1U)
/*! BPBLCD22
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD22(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD22_SHIFT)) & LCD_WF8B_BPBLCD22_MASK)

#define LCD_WF8B_BPBLCD23_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD23_SHIFT                  (1U)
/*! BPBLCD23
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD23(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD23_SHIFT)) & LCD_WF8B_BPBLCD23_MASK)

#define LCD_WF8B_BPBLCD24_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD24_SHIFT                  (1U)
/*! BPBLCD24
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD24(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD24_SHIFT)) & LCD_WF8B_BPBLCD24_MASK)

#define LCD_WF8B_BPBLCD25_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD25_SHIFT                  (1U)
/*! BPBLCD25
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD25(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD25_SHIFT)) & LCD_WF8B_BPBLCD25_MASK)

#define LCD_WF8B_BPBLCD26_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD26_SHIFT                  (1U)
/*! BPBLCD26
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD26(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD26_SHIFT)) & LCD_WF8B_BPBLCD26_MASK)

#define LCD_WF8B_BPBLCD27_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD27_SHIFT                  (1U)
/*! BPBLCD27
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD27(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD27_SHIFT)) & LCD_WF8B_BPBLCD27_MASK)

#define LCD_WF8B_BPBLCD28_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD28_SHIFT                  (1U)
/*! BPBLCD28
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD28(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD28_SHIFT)) & LCD_WF8B_BPBLCD28_MASK)

#define LCD_WF8B_BPBLCD29_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD29_SHIFT                  (1U)
/*! BPBLCD29
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD29(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD29_SHIFT)) & LCD_WF8B_BPBLCD29_MASK)

#define LCD_WF8B_BPBLCD30_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD30_SHIFT                  (1U)
/*! BPBLCD30
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD30(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD30_SHIFT)) & LCD_WF8B_BPBLCD30_MASK)

#define LCD_WF8B_BPBLCD31_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD31_SHIFT                  (1U)
/*! BPBLCD31
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD31(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD31_SHIFT)) & LCD_WF8B_BPBLCD31_MASK)

#define LCD_WF8B_BPBLCD32_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD32_SHIFT                  (1U)
/*! BPBLCD32
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD32(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD32_SHIFT)) & LCD_WF8B_BPBLCD32_MASK)

#define LCD_WF8B_BPBLCD33_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD33_SHIFT                  (1U)
/*! BPBLCD33
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD33(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD33_SHIFT)) & LCD_WF8B_BPBLCD33_MASK)

#define LCD_WF8B_BPBLCD34_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD34_SHIFT                  (1U)
/*! BPBLCD34
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD34(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD34_SHIFT)) & LCD_WF8B_BPBLCD34_MASK)

#define LCD_WF8B_BPBLCD35_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD35_SHIFT                  (1U)
/*! BPBLCD35
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD35(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD35_SHIFT)) & LCD_WF8B_BPBLCD35_MASK)

#define LCD_WF8B_BPBLCD36_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD36_SHIFT                  (1U)
/*! BPBLCD36
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD36(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD36_SHIFT)) & LCD_WF8B_BPBLCD36_MASK)

#define LCD_WF8B_BPBLCD37_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD37_SHIFT                  (1U)
/*! BPBLCD37
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD37(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD37_SHIFT)) & LCD_WF8B_BPBLCD37_MASK)

#define LCD_WF8B_BPBLCD38_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD38_SHIFT                  (1U)
/*! BPBLCD38
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD38(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD38_SHIFT)) & LCD_WF8B_BPBLCD38_MASK)

#define LCD_WF8B_BPBLCD39_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD39_SHIFT                  (1U)
/*! BPBLCD39
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD39(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD39_SHIFT)) & LCD_WF8B_BPBLCD39_MASK)

#define LCD_WF8B_BPBLCD40_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD40_SHIFT                  (1U)
/*! BPBLCD40
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD40(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD40_SHIFT)) & LCD_WF8B_BPBLCD40_MASK)

#define LCD_WF8B_BPBLCD41_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD41_SHIFT                  (1U)
/*! BPBLCD41
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD41(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD41_SHIFT)) & LCD_WF8B_BPBLCD41_MASK)

#define LCD_WF8B_BPBLCD42_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD42_SHIFT                  (1U)
/*! BPBLCD42
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD42(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD42_SHIFT)) & LCD_WF8B_BPBLCD42_MASK)

#define LCD_WF8B_BPBLCD43_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD43_SHIFT                  (1U)
/*! BPBLCD43
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD43(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD43_SHIFT)) & LCD_WF8B_BPBLCD43_MASK)

#define LCD_WF8B_BPBLCD44_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD44_SHIFT                  (1U)
/*! BPBLCD44
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD44(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD44_SHIFT)) & LCD_WF8B_BPBLCD44_MASK)

#define LCD_WF8B_BPBLCD45_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD45_SHIFT                  (1U)
/*! BPBLCD45
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD45(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD45_SHIFT)) & LCD_WF8B_BPBLCD45_MASK)

#define LCD_WF8B_BPBLCD46_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD46_SHIFT                  (1U)
/*! BPBLCD46
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD46(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD46_SHIFT)) & LCD_WF8B_BPBLCD46_MASK)

#define LCD_WF8B_BPBLCD47_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD47_SHIFT                  (1U)
/*! BPBLCD47
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD47(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD47_SHIFT)) & LCD_WF8B_BPBLCD47_MASK)

#define LCD_WF8B_BPBLCD48_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD48_SHIFT                  (1U)
/*! BPBLCD48
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD48(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD48_SHIFT)) & LCD_WF8B_BPBLCD48_MASK)

#define LCD_WF8B_BPBLCD49_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD49_SHIFT                  (1U)
/*! BPBLCD49
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD49(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD49_SHIFT)) & LCD_WF8B_BPBLCD49_MASK)

#define LCD_WF8B_BPBLCD50_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD50_SHIFT                  (1U)
/*! BPBLCD50
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD50(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD50_SHIFT)) & LCD_WF8B_BPBLCD50_MASK)

#define LCD_WF8B_BPBLCD51_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD51_SHIFT                  (1U)
/*! BPBLCD51
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD51(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD51_SHIFT)) & LCD_WF8B_BPBLCD51_MASK)

#define LCD_WF8B_BPBLCD52_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD52_SHIFT                  (1U)
/*! BPBLCD52
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD52(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD52_SHIFT)) & LCD_WF8B_BPBLCD52_MASK)

#define LCD_WF8B_BPBLCD53_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD53_SHIFT                  (1U)
/*! BPBLCD53
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD53(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD53_SHIFT)) & LCD_WF8B_BPBLCD53_MASK)

#define LCD_WF8B_BPBLCD54_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD54_SHIFT                  (1U)
/*! BPBLCD54
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD54(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD54_SHIFT)) & LCD_WF8B_BPBLCD54_MASK)

#define LCD_WF8B_BPBLCD55_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD55_SHIFT                  (1U)
/*! BPBLCD55
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD55(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD55_SHIFT)) & LCD_WF8B_BPBLCD55_MASK)

#define LCD_WF8B_BPBLCD56_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD56_SHIFT                  (1U)
/*! BPBLCD56
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD56(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD56_SHIFT)) & LCD_WF8B_BPBLCD56_MASK)

#define LCD_WF8B_BPBLCD57_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD57_SHIFT                  (1U)
/*! BPBLCD57
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD57(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD57_SHIFT)) & LCD_WF8B_BPBLCD57_MASK)

#define LCD_WF8B_BPBLCD58_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD58_SHIFT                  (1U)
/*! BPBLCD58
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD58(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD58_SHIFT)) & LCD_WF8B_BPBLCD58_MASK)

#define LCD_WF8B_BPBLCD59_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD59_SHIFT                  (1U)
/*! BPBLCD59
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD59(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD59_SHIFT)) & LCD_WF8B_BPBLCD59_MASK)

#define LCD_WF8B_BPBLCD60_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD60_SHIFT                  (1U)
/*! BPBLCD60
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD60(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD60_SHIFT)) & LCD_WF8B_BPBLCD60_MASK)

#define LCD_WF8B_BPBLCD61_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD61_SHIFT                  (1U)
/*! BPBLCD61
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD61(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD61_SHIFT)) & LCD_WF8B_BPBLCD61_MASK)

#define LCD_WF8B_BPBLCD62_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD62_SHIFT                  (1U)
/*! BPBLCD62
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD62(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD62_SHIFT)) & LCD_WF8B_BPBLCD62_MASK)

#define LCD_WF8B_BPBLCD63_MASK                   (0x2U)
#define LCD_WF8B_BPBLCD63_SHIFT                  (1U)
/*! BPBLCD63
 *  0b0..LCD segment off or LCD backplane inactive for phase B
 *  0b1..LCD segment on or LCD backplane active for phase B
 */
#define LCD_WF8B_BPBLCD63(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPBLCD63_SHIFT)) & LCD_WF8B_BPBLCD63_MASK)

#define LCD_WF8B_BPCLCD0_MASK                    (0x4U)
#define LCD_WF8B_BPCLCD0_SHIFT                   (2U)
/*! BPCLCD0
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD0(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD0_SHIFT)) & LCD_WF8B_BPCLCD0_MASK)

#define LCD_WF8B_BPCLCD1_MASK                    (0x4U)
#define LCD_WF8B_BPCLCD1_SHIFT                   (2U)
/*! BPCLCD1
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD1(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD1_SHIFT)) & LCD_WF8B_BPCLCD1_MASK)

#define LCD_WF8B_BPCLCD2_MASK                    (0x4U)
#define LCD_WF8B_BPCLCD2_SHIFT                   (2U)
/*! BPCLCD2
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD2(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD2_SHIFT)) & LCD_WF8B_BPCLCD2_MASK)

#define LCD_WF8B_BPCLCD3_MASK                    (0x4U)
#define LCD_WF8B_BPCLCD3_SHIFT                   (2U)
/*! BPCLCD3
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD3(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD3_SHIFT)) & LCD_WF8B_BPCLCD3_MASK)

#define LCD_WF8B_BPCLCD4_MASK                    (0x4U)
#define LCD_WF8B_BPCLCD4_SHIFT                   (2U)
/*! BPCLCD4
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD4(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD4_SHIFT)) & LCD_WF8B_BPCLCD4_MASK)

#define LCD_WF8B_BPCLCD5_MASK                    (0x4U)
#define LCD_WF8B_BPCLCD5_SHIFT                   (2U)
/*! BPCLCD5
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD5(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD5_SHIFT)) & LCD_WF8B_BPCLCD5_MASK)

#define LCD_WF8B_BPCLCD6_MASK                    (0x4U)
#define LCD_WF8B_BPCLCD6_SHIFT                   (2U)
/*! BPCLCD6
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD6(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD6_SHIFT)) & LCD_WF8B_BPCLCD6_MASK)

#define LCD_WF8B_BPCLCD7_MASK                    (0x4U)
#define LCD_WF8B_BPCLCD7_SHIFT                   (2U)
/*! BPCLCD7
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD7(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD7_SHIFT)) & LCD_WF8B_BPCLCD7_MASK)

#define LCD_WF8B_BPCLCD8_MASK                    (0x4U)
#define LCD_WF8B_BPCLCD8_SHIFT                   (2U)
/*! BPCLCD8
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD8(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD8_SHIFT)) & LCD_WF8B_BPCLCD8_MASK)

#define LCD_WF8B_BPCLCD9_MASK                    (0x4U)
#define LCD_WF8B_BPCLCD9_SHIFT                   (2U)
/*! BPCLCD9
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD9(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD9_SHIFT)) & LCD_WF8B_BPCLCD9_MASK)

#define LCD_WF8B_BPCLCD10_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD10_SHIFT                  (2U)
/*! BPCLCD10
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD10(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD10_SHIFT)) & LCD_WF8B_BPCLCD10_MASK)

#define LCD_WF8B_BPCLCD11_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD11_SHIFT                  (2U)
/*! BPCLCD11
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD11(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD11_SHIFT)) & LCD_WF8B_BPCLCD11_MASK)

#define LCD_WF8B_BPCLCD12_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD12_SHIFT                  (2U)
/*! BPCLCD12
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD12(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD12_SHIFT)) & LCD_WF8B_BPCLCD12_MASK)

#define LCD_WF8B_BPCLCD13_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD13_SHIFT                  (2U)
/*! BPCLCD13
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD13(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD13_SHIFT)) & LCD_WF8B_BPCLCD13_MASK)

#define LCD_WF8B_BPCLCD14_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD14_SHIFT                  (2U)
/*! BPCLCD14
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD14(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD14_SHIFT)) & LCD_WF8B_BPCLCD14_MASK)

#define LCD_WF8B_BPCLCD15_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD15_SHIFT                  (2U)
/*! BPCLCD15
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD15(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD15_SHIFT)) & LCD_WF8B_BPCLCD15_MASK)

#define LCD_WF8B_BPCLCD16_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD16_SHIFT                  (2U)
/*! BPCLCD16
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD16(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD16_SHIFT)) & LCD_WF8B_BPCLCD16_MASK)

#define LCD_WF8B_BPCLCD17_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD17_SHIFT                  (2U)
/*! BPCLCD17
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD17(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD17_SHIFT)) & LCD_WF8B_BPCLCD17_MASK)

#define LCD_WF8B_BPCLCD18_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD18_SHIFT                  (2U)
/*! BPCLCD18
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD18(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD18_SHIFT)) & LCD_WF8B_BPCLCD18_MASK)

#define LCD_WF8B_BPCLCD19_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD19_SHIFT                  (2U)
/*! BPCLCD19
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD19(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD19_SHIFT)) & LCD_WF8B_BPCLCD19_MASK)

#define LCD_WF8B_BPCLCD20_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD20_SHIFT                  (2U)
/*! BPCLCD20
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD20(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD20_SHIFT)) & LCD_WF8B_BPCLCD20_MASK)

#define LCD_WF8B_BPCLCD21_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD21_SHIFT                  (2U)
/*! BPCLCD21
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD21(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD21_SHIFT)) & LCD_WF8B_BPCLCD21_MASK)

#define LCD_WF8B_BPCLCD22_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD22_SHIFT                  (2U)
/*! BPCLCD22
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD22(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD22_SHIFT)) & LCD_WF8B_BPCLCD22_MASK)

#define LCD_WF8B_BPCLCD23_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD23_SHIFT                  (2U)
/*! BPCLCD23
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD23(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD23_SHIFT)) & LCD_WF8B_BPCLCD23_MASK)

#define LCD_WF8B_BPCLCD24_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD24_SHIFT                  (2U)
/*! BPCLCD24
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD24(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD24_SHIFT)) & LCD_WF8B_BPCLCD24_MASK)

#define LCD_WF8B_BPCLCD25_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD25_SHIFT                  (2U)
/*! BPCLCD25
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD25(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD25_SHIFT)) & LCD_WF8B_BPCLCD25_MASK)

#define LCD_WF8B_BPCLCD26_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD26_SHIFT                  (2U)
/*! BPCLCD26
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD26(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD26_SHIFT)) & LCD_WF8B_BPCLCD26_MASK)

#define LCD_WF8B_BPCLCD27_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD27_SHIFT                  (2U)
/*! BPCLCD27
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD27(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD27_SHIFT)) & LCD_WF8B_BPCLCD27_MASK)

#define LCD_WF8B_BPCLCD28_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD28_SHIFT                  (2U)
/*! BPCLCD28
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD28(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD28_SHIFT)) & LCD_WF8B_BPCLCD28_MASK)

#define LCD_WF8B_BPCLCD29_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD29_SHIFT                  (2U)
/*! BPCLCD29
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD29(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD29_SHIFT)) & LCD_WF8B_BPCLCD29_MASK)

#define LCD_WF8B_BPCLCD30_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD30_SHIFT                  (2U)
/*! BPCLCD30
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD30(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD30_SHIFT)) & LCD_WF8B_BPCLCD30_MASK)

#define LCD_WF8B_BPCLCD31_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD31_SHIFT                  (2U)
/*! BPCLCD31
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD31(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD31_SHIFT)) & LCD_WF8B_BPCLCD31_MASK)

#define LCD_WF8B_BPCLCD32_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD32_SHIFT                  (2U)
/*! BPCLCD32
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD32(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD32_SHIFT)) & LCD_WF8B_BPCLCD32_MASK)

#define LCD_WF8B_BPCLCD33_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD33_SHIFT                  (2U)
/*! BPCLCD33
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD33(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD33_SHIFT)) & LCD_WF8B_BPCLCD33_MASK)

#define LCD_WF8B_BPCLCD34_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD34_SHIFT                  (2U)
/*! BPCLCD34
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD34(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD34_SHIFT)) & LCD_WF8B_BPCLCD34_MASK)

#define LCD_WF8B_BPCLCD35_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD35_SHIFT                  (2U)
/*! BPCLCD35
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD35(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD35_SHIFT)) & LCD_WF8B_BPCLCD35_MASK)

#define LCD_WF8B_BPCLCD36_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD36_SHIFT                  (2U)
/*! BPCLCD36
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD36(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD36_SHIFT)) & LCD_WF8B_BPCLCD36_MASK)

#define LCD_WF8B_BPCLCD37_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD37_SHIFT                  (2U)
/*! BPCLCD37
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD37(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD37_SHIFT)) & LCD_WF8B_BPCLCD37_MASK)

#define LCD_WF8B_BPCLCD38_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD38_SHIFT                  (2U)
/*! BPCLCD38
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD38(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD38_SHIFT)) & LCD_WF8B_BPCLCD38_MASK)

#define LCD_WF8B_BPCLCD39_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD39_SHIFT                  (2U)
/*! BPCLCD39
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD39(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD39_SHIFT)) & LCD_WF8B_BPCLCD39_MASK)

#define LCD_WF8B_BPCLCD40_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD40_SHIFT                  (2U)
/*! BPCLCD40
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD40(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD40_SHIFT)) & LCD_WF8B_BPCLCD40_MASK)

#define LCD_WF8B_BPCLCD41_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD41_SHIFT                  (2U)
/*! BPCLCD41
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD41(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD41_SHIFT)) & LCD_WF8B_BPCLCD41_MASK)

#define LCD_WF8B_BPCLCD42_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD42_SHIFT                  (2U)
/*! BPCLCD42
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD42(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD42_SHIFT)) & LCD_WF8B_BPCLCD42_MASK)

#define LCD_WF8B_BPCLCD43_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD43_SHIFT                  (2U)
/*! BPCLCD43
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD43(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD43_SHIFT)) & LCD_WF8B_BPCLCD43_MASK)

#define LCD_WF8B_BPCLCD44_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD44_SHIFT                  (2U)
/*! BPCLCD44
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD44(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD44_SHIFT)) & LCD_WF8B_BPCLCD44_MASK)

#define LCD_WF8B_BPCLCD45_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD45_SHIFT                  (2U)
/*! BPCLCD45
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD45(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD45_SHIFT)) & LCD_WF8B_BPCLCD45_MASK)

#define LCD_WF8B_BPCLCD46_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD46_SHIFT                  (2U)
/*! BPCLCD46
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD46(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD46_SHIFT)) & LCD_WF8B_BPCLCD46_MASK)

#define LCD_WF8B_BPCLCD47_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD47_SHIFT                  (2U)
/*! BPCLCD47
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD47(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD47_SHIFT)) & LCD_WF8B_BPCLCD47_MASK)

#define LCD_WF8B_BPCLCD48_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD48_SHIFT                  (2U)
/*! BPCLCD48
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD48(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD48_SHIFT)) & LCD_WF8B_BPCLCD48_MASK)

#define LCD_WF8B_BPCLCD49_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD49_SHIFT                  (2U)
/*! BPCLCD49
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD49(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD49_SHIFT)) & LCD_WF8B_BPCLCD49_MASK)

#define LCD_WF8B_BPCLCD50_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD50_SHIFT                  (2U)
/*! BPCLCD50
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD50(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD50_SHIFT)) & LCD_WF8B_BPCLCD50_MASK)

#define LCD_WF8B_BPCLCD51_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD51_SHIFT                  (2U)
/*! BPCLCD51
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD51(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD51_SHIFT)) & LCD_WF8B_BPCLCD51_MASK)

#define LCD_WF8B_BPCLCD52_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD52_SHIFT                  (2U)
/*! BPCLCD52
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD52(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD52_SHIFT)) & LCD_WF8B_BPCLCD52_MASK)

#define LCD_WF8B_BPCLCD53_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD53_SHIFT                  (2U)
/*! BPCLCD53
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD53(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD53_SHIFT)) & LCD_WF8B_BPCLCD53_MASK)

#define LCD_WF8B_BPCLCD54_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD54_SHIFT                  (2U)
/*! BPCLCD54
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD54(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD54_SHIFT)) & LCD_WF8B_BPCLCD54_MASK)

#define LCD_WF8B_BPCLCD55_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD55_SHIFT                  (2U)
/*! BPCLCD55
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD55(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD55_SHIFT)) & LCD_WF8B_BPCLCD55_MASK)

#define LCD_WF8B_BPCLCD56_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD56_SHIFT                  (2U)
/*! BPCLCD56
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD56(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD56_SHIFT)) & LCD_WF8B_BPCLCD56_MASK)

#define LCD_WF8B_BPCLCD57_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD57_SHIFT                  (2U)
/*! BPCLCD57
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD57(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD57_SHIFT)) & LCD_WF8B_BPCLCD57_MASK)

#define LCD_WF8B_BPCLCD58_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD58_SHIFT                  (2U)
/*! BPCLCD58
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD58(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD58_SHIFT)) & LCD_WF8B_BPCLCD58_MASK)

#define LCD_WF8B_BPCLCD59_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD59_SHIFT                  (2U)
/*! BPCLCD59
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD59(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD59_SHIFT)) & LCD_WF8B_BPCLCD59_MASK)

#define LCD_WF8B_BPCLCD60_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD60_SHIFT                  (2U)
/*! BPCLCD60
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD60(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD60_SHIFT)) & LCD_WF8B_BPCLCD60_MASK)

#define LCD_WF8B_BPCLCD61_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD61_SHIFT                  (2U)
/*! BPCLCD61
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD61(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD61_SHIFT)) & LCD_WF8B_BPCLCD61_MASK)

#define LCD_WF8B_BPCLCD62_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD62_SHIFT                  (2U)
/*! BPCLCD62
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD62(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD62_SHIFT)) & LCD_WF8B_BPCLCD62_MASK)

#define LCD_WF8B_BPCLCD63_MASK                   (0x4U)
#define LCD_WF8B_BPCLCD63_SHIFT                  (2U)
/*! BPCLCD63
 *  0b0..LCD segment off or LCD backplane inactive for phase C
 *  0b1..LCD segment on or LCD backplane active for phase C
 */
#define LCD_WF8B_BPCLCD63(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPCLCD63_SHIFT)) & LCD_WF8B_BPCLCD63_MASK)

#define LCD_WF8B_BPDLCD0_MASK                    (0x8U)
#define LCD_WF8B_BPDLCD0_SHIFT                   (3U)
/*! BPDLCD0
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD0(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD0_SHIFT)) & LCD_WF8B_BPDLCD0_MASK)

#define LCD_WF8B_BPDLCD1_MASK                    (0x8U)
#define LCD_WF8B_BPDLCD1_SHIFT                   (3U)
/*! BPDLCD1
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD1(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD1_SHIFT)) & LCD_WF8B_BPDLCD1_MASK)

#define LCD_WF8B_BPDLCD2_MASK                    (0x8U)
#define LCD_WF8B_BPDLCD2_SHIFT                   (3U)
/*! BPDLCD2
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD2(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD2_SHIFT)) & LCD_WF8B_BPDLCD2_MASK)

#define LCD_WF8B_BPDLCD3_MASK                    (0x8U)
#define LCD_WF8B_BPDLCD3_SHIFT                   (3U)
/*! BPDLCD3
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD3(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD3_SHIFT)) & LCD_WF8B_BPDLCD3_MASK)

#define LCD_WF8B_BPDLCD4_MASK                    (0x8U)
#define LCD_WF8B_BPDLCD4_SHIFT                   (3U)
/*! BPDLCD4
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD4(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD4_SHIFT)) & LCD_WF8B_BPDLCD4_MASK)

#define LCD_WF8B_BPDLCD5_MASK                    (0x8U)
#define LCD_WF8B_BPDLCD5_SHIFT                   (3U)
/*! BPDLCD5
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD5(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD5_SHIFT)) & LCD_WF8B_BPDLCD5_MASK)

#define LCD_WF8B_BPDLCD6_MASK                    (0x8U)
#define LCD_WF8B_BPDLCD6_SHIFT                   (3U)
/*! BPDLCD6
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD6(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD6_SHIFT)) & LCD_WF8B_BPDLCD6_MASK)

#define LCD_WF8B_BPDLCD7_MASK                    (0x8U)
#define LCD_WF8B_BPDLCD7_SHIFT                   (3U)
/*! BPDLCD7
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD7(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD7_SHIFT)) & LCD_WF8B_BPDLCD7_MASK)

#define LCD_WF8B_BPDLCD8_MASK                    (0x8U)
#define LCD_WF8B_BPDLCD8_SHIFT                   (3U)
/*! BPDLCD8
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD8(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD8_SHIFT)) & LCD_WF8B_BPDLCD8_MASK)

#define LCD_WF8B_BPDLCD9_MASK                    (0x8U)
#define LCD_WF8B_BPDLCD9_SHIFT                   (3U)
/*! BPDLCD9
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD9(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD9_SHIFT)) & LCD_WF8B_BPDLCD9_MASK)

#define LCD_WF8B_BPDLCD10_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD10_SHIFT                  (3U)
/*! BPDLCD10
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD10(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD10_SHIFT)) & LCD_WF8B_BPDLCD10_MASK)

#define LCD_WF8B_BPDLCD11_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD11_SHIFT                  (3U)
/*! BPDLCD11
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD11(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD11_SHIFT)) & LCD_WF8B_BPDLCD11_MASK)

#define LCD_WF8B_BPDLCD12_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD12_SHIFT                  (3U)
/*! BPDLCD12
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD12(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD12_SHIFT)) & LCD_WF8B_BPDLCD12_MASK)

#define LCD_WF8B_BPDLCD13_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD13_SHIFT                  (3U)
/*! BPDLCD13
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD13(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD13_SHIFT)) & LCD_WF8B_BPDLCD13_MASK)

#define LCD_WF8B_BPDLCD14_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD14_SHIFT                  (3U)
/*! BPDLCD14
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD14(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD14_SHIFT)) & LCD_WF8B_BPDLCD14_MASK)

#define LCD_WF8B_BPDLCD15_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD15_SHIFT                  (3U)
/*! BPDLCD15
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD15(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD15_SHIFT)) & LCD_WF8B_BPDLCD15_MASK)

#define LCD_WF8B_BPDLCD16_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD16_SHIFT                  (3U)
/*! BPDLCD16
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD16(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD16_SHIFT)) & LCD_WF8B_BPDLCD16_MASK)

#define LCD_WF8B_BPDLCD17_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD17_SHIFT                  (3U)
/*! BPDLCD17
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD17(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD17_SHIFT)) & LCD_WF8B_BPDLCD17_MASK)

#define LCD_WF8B_BPDLCD18_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD18_SHIFT                  (3U)
/*! BPDLCD18
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD18(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD18_SHIFT)) & LCD_WF8B_BPDLCD18_MASK)

#define LCD_WF8B_BPDLCD19_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD19_SHIFT                  (3U)
/*! BPDLCD19
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD19(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD19_SHIFT)) & LCD_WF8B_BPDLCD19_MASK)

#define LCD_WF8B_BPDLCD20_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD20_SHIFT                  (3U)
/*! BPDLCD20
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD20(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD20_SHIFT)) & LCD_WF8B_BPDLCD20_MASK)

#define LCD_WF8B_BPDLCD21_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD21_SHIFT                  (3U)
/*! BPDLCD21
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD21(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD21_SHIFT)) & LCD_WF8B_BPDLCD21_MASK)

#define LCD_WF8B_BPDLCD22_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD22_SHIFT                  (3U)
/*! BPDLCD22
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD22(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD22_SHIFT)) & LCD_WF8B_BPDLCD22_MASK)

#define LCD_WF8B_BPDLCD23_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD23_SHIFT                  (3U)
/*! BPDLCD23
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD23(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD23_SHIFT)) & LCD_WF8B_BPDLCD23_MASK)

#define LCD_WF8B_BPDLCD24_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD24_SHIFT                  (3U)
/*! BPDLCD24
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD24(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD24_SHIFT)) & LCD_WF8B_BPDLCD24_MASK)

#define LCD_WF8B_BPDLCD25_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD25_SHIFT                  (3U)
/*! BPDLCD25
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD25(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD25_SHIFT)) & LCD_WF8B_BPDLCD25_MASK)

#define LCD_WF8B_BPDLCD26_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD26_SHIFT                  (3U)
/*! BPDLCD26
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD26(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD26_SHIFT)) & LCD_WF8B_BPDLCD26_MASK)

#define LCD_WF8B_BPDLCD27_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD27_SHIFT                  (3U)
/*! BPDLCD27
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD27(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD27_SHIFT)) & LCD_WF8B_BPDLCD27_MASK)

#define LCD_WF8B_BPDLCD28_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD28_SHIFT                  (3U)
/*! BPDLCD28
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD28(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD28_SHIFT)) & LCD_WF8B_BPDLCD28_MASK)

#define LCD_WF8B_BPDLCD29_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD29_SHIFT                  (3U)
/*! BPDLCD29
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD29(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD29_SHIFT)) & LCD_WF8B_BPDLCD29_MASK)

#define LCD_WF8B_BPDLCD30_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD30_SHIFT                  (3U)
/*! BPDLCD30
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD30(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD30_SHIFT)) & LCD_WF8B_BPDLCD30_MASK)

#define LCD_WF8B_BPDLCD31_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD31_SHIFT                  (3U)
/*! BPDLCD31
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD31(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD31_SHIFT)) & LCD_WF8B_BPDLCD31_MASK)

#define LCD_WF8B_BPDLCD32_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD32_SHIFT                  (3U)
/*! BPDLCD32
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD32(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD32_SHIFT)) & LCD_WF8B_BPDLCD32_MASK)

#define LCD_WF8B_BPDLCD33_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD33_SHIFT                  (3U)
/*! BPDLCD33
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD33(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD33_SHIFT)) & LCD_WF8B_BPDLCD33_MASK)

#define LCD_WF8B_BPDLCD34_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD34_SHIFT                  (3U)
/*! BPDLCD34
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD34(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD34_SHIFT)) & LCD_WF8B_BPDLCD34_MASK)

#define LCD_WF8B_BPDLCD35_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD35_SHIFT                  (3U)
/*! BPDLCD35
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD35(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD35_SHIFT)) & LCD_WF8B_BPDLCD35_MASK)

#define LCD_WF8B_BPDLCD36_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD36_SHIFT                  (3U)
/*! BPDLCD36
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD36(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD36_SHIFT)) & LCD_WF8B_BPDLCD36_MASK)

#define LCD_WF8B_BPDLCD37_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD37_SHIFT                  (3U)
/*! BPDLCD37
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD37(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD37_SHIFT)) & LCD_WF8B_BPDLCD37_MASK)

#define LCD_WF8B_BPDLCD38_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD38_SHIFT                  (3U)
/*! BPDLCD38
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD38(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD38_SHIFT)) & LCD_WF8B_BPDLCD38_MASK)

#define LCD_WF8B_BPDLCD39_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD39_SHIFT                  (3U)
/*! BPDLCD39
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD39(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD39_SHIFT)) & LCD_WF8B_BPDLCD39_MASK)

#define LCD_WF8B_BPDLCD40_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD40_SHIFT                  (3U)
/*! BPDLCD40
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD40(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD40_SHIFT)) & LCD_WF8B_BPDLCD40_MASK)

#define LCD_WF8B_BPDLCD41_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD41_SHIFT                  (3U)
/*! BPDLCD41
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD41(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD41_SHIFT)) & LCD_WF8B_BPDLCD41_MASK)

#define LCD_WF8B_BPDLCD42_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD42_SHIFT                  (3U)
/*! BPDLCD42
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD42(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD42_SHIFT)) & LCD_WF8B_BPDLCD42_MASK)

#define LCD_WF8B_BPDLCD43_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD43_SHIFT                  (3U)
/*! BPDLCD43
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD43(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD43_SHIFT)) & LCD_WF8B_BPDLCD43_MASK)

#define LCD_WF8B_BPDLCD44_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD44_SHIFT                  (3U)
/*! BPDLCD44
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD44(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD44_SHIFT)) & LCD_WF8B_BPDLCD44_MASK)

#define LCD_WF8B_BPDLCD45_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD45_SHIFT                  (3U)
/*! BPDLCD45
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD45(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD45_SHIFT)) & LCD_WF8B_BPDLCD45_MASK)

#define LCD_WF8B_BPDLCD46_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD46_SHIFT                  (3U)
/*! BPDLCD46
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD46(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD46_SHIFT)) & LCD_WF8B_BPDLCD46_MASK)

#define LCD_WF8B_BPDLCD47_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD47_SHIFT                  (3U)
/*! BPDLCD47
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD47(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD47_SHIFT)) & LCD_WF8B_BPDLCD47_MASK)

#define LCD_WF8B_BPDLCD48_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD48_SHIFT                  (3U)
/*! BPDLCD48
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD48(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD48_SHIFT)) & LCD_WF8B_BPDLCD48_MASK)

#define LCD_WF8B_BPDLCD49_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD49_SHIFT                  (3U)
/*! BPDLCD49
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD49(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD49_SHIFT)) & LCD_WF8B_BPDLCD49_MASK)

#define LCD_WF8B_BPDLCD50_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD50_SHIFT                  (3U)
/*! BPDLCD50
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD50(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD50_SHIFT)) & LCD_WF8B_BPDLCD50_MASK)

#define LCD_WF8B_BPDLCD51_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD51_SHIFT                  (3U)
/*! BPDLCD51
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD51(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD51_SHIFT)) & LCD_WF8B_BPDLCD51_MASK)

#define LCD_WF8B_BPDLCD52_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD52_SHIFT                  (3U)
/*! BPDLCD52
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD52(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD52_SHIFT)) & LCD_WF8B_BPDLCD52_MASK)

#define LCD_WF8B_BPDLCD53_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD53_SHIFT                  (3U)
/*! BPDLCD53
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD53(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD53_SHIFT)) & LCD_WF8B_BPDLCD53_MASK)

#define LCD_WF8B_BPDLCD54_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD54_SHIFT                  (3U)
/*! BPDLCD54
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD54(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD54_SHIFT)) & LCD_WF8B_BPDLCD54_MASK)

#define LCD_WF8B_BPDLCD55_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD55_SHIFT                  (3U)
/*! BPDLCD55
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD55(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD55_SHIFT)) & LCD_WF8B_BPDLCD55_MASK)

#define LCD_WF8B_BPDLCD56_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD56_SHIFT                  (3U)
/*! BPDLCD56
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD56(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD56_SHIFT)) & LCD_WF8B_BPDLCD56_MASK)

#define LCD_WF8B_BPDLCD57_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD57_SHIFT                  (3U)
/*! BPDLCD57
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD57(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD57_SHIFT)) & LCD_WF8B_BPDLCD57_MASK)

#define LCD_WF8B_BPDLCD58_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD58_SHIFT                  (3U)
/*! BPDLCD58
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD58(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD58_SHIFT)) & LCD_WF8B_BPDLCD58_MASK)

#define LCD_WF8B_BPDLCD59_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD59_SHIFT                  (3U)
/*! BPDLCD59
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD59(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD59_SHIFT)) & LCD_WF8B_BPDLCD59_MASK)

#define LCD_WF8B_BPDLCD60_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD60_SHIFT                  (3U)
/*! BPDLCD60
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD60(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD60_SHIFT)) & LCD_WF8B_BPDLCD60_MASK)

#define LCD_WF8B_BPDLCD61_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD61_SHIFT                  (3U)
/*! BPDLCD61
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD61(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD61_SHIFT)) & LCD_WF8B_BPDLCD61_MASK)

#define LCD_WF8B_BPDLCD62_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD62_SHIFT                  (3U)
/*! BPDLCD62
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD62(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD62_SHIFT)) & LCD_WF8B_BPDLCD62_MASK)

#define LCD_WF8B_BPDLCD63_MASK                   (0x8U)
#define LCD_WF8B_BPDLCD63_SHIFT                  (3U)
/*! BPDLCD63
 *  0b0..LCD segment off or LCD backplane inactive for phase D
 *  0b1..LCD segment on or LCD backplane active for phase D
 */
#define LCD_WF8B_BPDLCD63(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPDLCD63_SHIFT)) & LCD_WF8B_BPDLCD63_MASK)

#define LCD_WF8B_BPELCD0_MASK                    (0x10U)
#define LCD_WF8B_BPELCD0_SHIFT                   (4U)
/*! BPELCD0
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD0(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD0_SHIFT)) & LCD_WF8B_BPELCD0_MASK)

#define LCD_WF8B_BPELCD1_MASK                    (0x10U)
#define LCD_WF8B_BPELCD1_SHIFT                   (4U)
/*! BPELCD1
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD1(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD1_SHIFT)) & LCD_WF8B_BPELCD1_MASK)

#define LCD_WF8B_BPELCD2_MASK                    (0x10U)
#define LCD_WF8B_BPELCD2_SHIFT                   (4U)
/*! BPELCD2
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD2(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD2_SHIFT)) & LCD_WF8B_BPELCD2_MASK)

#define LCD_WF8B_BPELCD3_MASK                    (0x10U)
#define LCD_WF8B_BPELCD3_SHIFT                   (4U)
/*! BPELCD3
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD3(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD3_SHIFT)) & LCD_WF8B_BPELCD3_MASK)

#define LCD_WF8B_BPELCD4_MASK                    (0x10U)
#define LCD_WF8B_BPELCD4_SHIFT                   (4U)
/*! BPELCD4
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD4(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD4_SHIFT)) & LCD_WF8B_BPELCD4_MASK)

#define LCD_WF8B_BPELCD5_MASK                    (0x10U)
#define LCD_WF8B_BPELCD5_SHIFT                   (4U)
/*! BPELCD5
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD5(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD5_SHIFT)) & LCD_WF8B_BPELCD5_MASK)

#define LCD_WF8B_BPELCD6_MASK                    (0x10U)
#define LCD_WF8B_BPELCD6_SHIFT                   (4U)
/*! BPELCD6
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD6(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD6_SHIFT)) & LCD_WF8B_BPELCD6_MASK)

#define LCD_WF8B_BPELCD7_MASK                    (0x10U)
#define LCD_WF8B_BPELCD7_SHIFT                   (4U)
/*! BPELCD7
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD7(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD7_SHIFT)) & LCD_WF8B_BPELCD7_MASK)

#define LCD_WF8B_BPELCD8_MASK                    (0x10U)
#define LCD_WF8B_BPELCD8_SHIFT                   (4U)
/*! BPELCD8
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD8(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD8_SHIFT)) & LCD_WF8B_BPELCD8_MASK)

#define LCD_WF8B_BPELCD9_MASK                    (0x10U)
#define LCD_WF8B_BPELCD9_SHIFT                   (4U)
/*! BPELCD9
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD9(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD9_SHIFT)) & LCD_WF8B_BPELCD9_MASK)

#define LCD_WF8B_BPELCD10_MASK                   (0x10U)
#define LCD_WF8B_BPELCD10_SHIFT                  (4U)
/*! BPELCD10
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD10(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD10_SHIFT)) & LCD_WF8B_BPELCD10_MASK)

#define LCD_WF8B_BPELCD11_MASK                   (0x10U)
#define LCD_WF8B_BPELCD11_SHIFT                  (4U)
/*! BPELCD11
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD11(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD11_SHIFT)) & LCD_WF8B_BPELCD11_MASK)

#define LCD_WF8B_BPELCD12_MASK                   (0x10U)
#define LCD_WF8B_BPELCD12_SHIFT                  (4U)
/*! BPELCD12
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD12(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD12_SHIFT)) & LCD_WF8B_BPELCD12_MASK)

#define LCD_WF8B_BPELCD13_MASK                   (0x10U)
#define LCD_WF8B_BPELCD13_SHIFT                  (4U)
/*! BPELCD13
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD13(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD13_SHIFT)) & LCD_WF8B_BPELCD13_MASK)

#define LCD_WF8B_BPELCD14_MASK                   (0x10U)
#define LCD_WF8B_BPELCD14_SHIFT                  (4U)
/*! BPELCD14
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD14(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD14_SHIFT)) & LCD_WF8B_BPELCD14_MASK)

#define LCD_WF8B_BPELCD15_MASK                   (0x10U)
#define LCD_WF8B_BPELCD15_SHIFT                  (4U)
/*! BPELCD15
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD15(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD15_SHIFT)) & LCD_WF8B_BPELCD15_MASK)

#define LCD_WF8B_BPELCD16_MASK                   (0x10U)
#define LCD_WF8B_BPELCD16_SHIFT                  (4U)
/*! BPELCD16
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD16(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD16_SHIFT)) & LCD_WF8B_BPELCD16_MASK)

#define LCD_WF8B_BPELCD17_MASK                   (0x10U)
#define LCD_WF8B_BPELCD17_SHIFT                  (4U)
/*! BPELCD17
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD17(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD17_SHIFT)) & LCD_WF8B_BPELCD17_MASK)

#define LCD_WF8B_BPELCD18_MASK                   (0x10U)
#define LCD_WF8B_BPELCD18_SHIFT                  (4U)
/*! BPELCD18
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD18(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD18_SHIFT)) & LCD_WF8B_BPELCD18_MASK)

#define LCD_WF8B_BPELCD19_MASK                   (0x10U)
#define LCD_WF8B_BPELCD19_SHIFT                  (4U)
/*! BPELCD19
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD19(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD19_SHIFT)) & LCD_WF8B_BPELCD19_MASK)

#define LCD_WF8B_BPELCD20_MASK                   (0x10U)
#define LCD_WF8B_BPELCD20_SHIFT                  (4U)
/*! BPELCD20
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD20(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD20_SHIFT)) & LCD_WF8B_BPELCD20_MASK)

#define LCD_WF8B_BPELCD21_MASK                   (0x10U)
#define LCD_WF8B_BPELCD21_SHIFT                  (4U)
/*! BPELCD21
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD21(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD21_SHIFT)) & LCD_WF8B_BPELCD21_MASK)

#define LCD_WF8B_BPELCD22_MASK                   (0x10U)
#define LCD_WF8B_BPELCD22_SHIFT                  (4U)
/*! BPELCD22
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD22(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD22_SHIFT)) & LCD_WF8B_BPELCD22_MASK)

#define LCD_WF8B_BPELCD23_MASK                   (0x10U)
#define LCD_WF8B_BPELCD23_SHIFT                  (4U)
/*! BPELCD23
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD23(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD23_SHIFT)) & LCD_WF8B_BPELCD23_MASK)

#define LCD_WF8B_BPELCD24_MASK                   (0x10U)
#define LCD_WF8B_BPELCD24_SHIFT                  (4U)
/*! BPELCD24
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD24(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD24_SHIFT)) & LCD_WF8B_BPELCD24_MASK)

#define LCD_WF8B_BPELCD25_MASK                   (0x10U)
#define LCD_WF8B_BPELCD25_SHIFT                  (4U)
/*! BPELCD25
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD25(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD25_SHIFT)) & LCD_WF8B_BPELCD25_MASK)

#define LCD_WF8B_BPELCD26_MASK                   (0x10U)
#define LCD_WF8B_BPELCD26_SHIFT                  (4U)
/*! BPELCD26
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD26(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD26_SHIFT)) & LCD_WF8B_BPELCD26_MASK)

#define LCD_WF8B_BPELCD27_MASK                   (0x10U)
#define LCD_WF8B_BPELCD27_SHIFT                  (4U)
/*! BPELCD27
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD27(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD27_SHIFT)) & LCD_WF8B_BPELCD27_MASK)

#define LCD_WF8B_BPELCD28_MASK                   (0x10U)
#define LCD_WF8B_BPELCD28_SHIFT                  (4U)
/*! BPELCD28
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD28(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD28_SHIFT)) & LCD_WF8B_BPELCD28_MASK)

#define LCD_WF8B_BPELCD29_MASK                   (0x10U)
#define LCD_WF8B_BPELCD29_SHIFT                  (4U)
/*! BPELCD29
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD29(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD29_SHIFT)) & LCD_WF8B_BPELCD29_MASK)

#define LCD_WF8B_BPELCD30_MASK                   (0x10U)
#define LCD_WF8B_BPELCD30_SHIFT                  (4U)
/*! BPELCD30
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD30(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD30_SHIFT)) & LCD_WF8B_BPELCD30_MASK)

#define LCD_WF8B_BPELCD31_MASK                   (0x10U)
#define LCD_WF8B_BPELCD31_SHIFT                  (4U)
/*! BPELCD31
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD31(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD31_SHIFT)) & LCD_WF8B_BPELCD31_MASK)

#define LCD_WF8B_BPELCD32_MASK                   (0x10U)
#define LCD_WF8B_BPELCD32_SHIFT                  (4U)
/*! BPELCD32
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD32(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD32_SHIFT)) & LCD_WF8B_BPELCD32_MASK)

#define LCD_WF8B_BPELCD33_MASK                   (0x10U)
#define LCD_WF8B_BPELCD33_SHIFT                  (4U)
/*! BPELCD33
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD33(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD33_SHIFT)) & LCD_WF8B_BPELCD33_MASK)

#define LCD_WF8B_BPELCD34_MASK                   (0x10U)
#define LCD_WF8B_BPELCD34_SHIFT                  (4U)
/*! BPELCD34
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD34(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD34_SHIFT)) & LCD_WF8B_BPELCD34_MASK)

#define LCD_WF8B_BPELCD35_MASK                   (0x10U)
#define LCD_WF8B_BPELCD35_SHIFT                  (4U)
/*! BPELCD35
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD35(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD35_SHIFT)) & LCD_WF8B_BPELCD35_MASK)

#define LCD_WF8B_BPELCD36_MASK                   (0x10U)
#define LCD_WF8B_BPELCD36_SHIFT                  (4U)
/*! BPELCD36
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD36(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD36_SHIFT)) & LCD_WF8B_BPELCD36_MASK)

#define LCD_WF8B_BPELCD37_MASK                   (0x10U)
#define LCD_WF8B_BPELCD37_SHIFT                  (4U)
/*! BPELCD37
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD37(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD37_SHIFT)) & LCD_WF8B_BPELCD37_MASK)

#define LCD_WF8B_BPELCD38_MASK                   (0x10U)
#define LCD_WF8B_BPELCD38_SHIFT                  (4U)
/*! BPELCD38
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD38(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD38_SHIFT)) & LCD_WF8B_BPELCD38_MASK)

#define LCD_WF8B_BPELCD39_MASK                   (0x10U)
#define LCD_WF8B_BPELCD39_SHIFT                  (4U)
/*! BPELCD39
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD39(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD39_SHIFT)) & LCD_WF8B_BPELCD39_MASK)

#define LCD_WF8B_BPELCD40_MASK                   (0x10U)
#define LCD_WF8B_BPELCD40_SHIFT                  (4U)
/*! BPELCD40
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD40(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD40_SHIFT)) & LCD_WF8B_BPELCD40_MASK)

#define LCD_WF8B_BPELCD41_MASK                   (0x10U)
#define LCD_WF8B_BPELCD41_SHIFT                  (4U)
/*! BPELCD41
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD41(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD41_SHIFT)) & LCD_WF8B_BPELCD41_MASK)

#define LCD_WF8B_BPELCD42_MASK                   (0x10U)
#define LCD_WF8B_BPELCD42_SHIFT                  (4U)
/*! BPELCD42
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD42(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD42_SHIFT)) & LCD_WF8B_BPELCD42_MASK)

#define LCD_WF8B_BPELCD43_MASK                   (0x10U)
#define LCD_WF8B_BPELCD43_SHIFT                  (4U)
/*! BPELCD43
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD43(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD43_SHIFT)) & LCD_WF8B_BPELCD43_MASK)

#define LCD_WF8B_BPELCD44_MASK                   (0x10U)
#define LCD_WF8B_BPELCD44_SHIFT                  (4U)
/*! BPELCD44
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD44(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD44_SHIFT)) & LCD_WF8B_BPELCD44_MASK)

#define LCD_WF8B_BPELCD45_MASK                   (0x10U)
#define LCD_WF8B_BPELCD45_SHIFT                  (4U)
/*! BPELCD45
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD45(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD45_SHIFT)) & LCD_WF8B_BPELCD45_MASK)

#define LCD_WF8B_BPELCD46_MASK                   (0x10U)
#define LCD_WF8B_BPELCD46_SHIFT                  (4U)
/*! BPELCD46
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD46(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD46_SHIFT)) & LCD_WF8B_BPELCD46_MASK)

#define LCD_WF8B_BPELCD47_MASK                   (0x10U)
#define LCD_WF8B_BPELCD47_SHIFT                  (4U)
/*! BPELCD47
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD47(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD47_SHIFT)) & LCD_WF8B_BPELCD47_MASK)

#define LCD_WF8B_BPELCD48_MASK                   (0x10U)
#define LCD_WF8B_BPELCD48_SHIFT                  (4U)
/*! BPELCD48
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD48(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD48_SHIFT)) & LCD_WF8B_BPELCD48_MASK)

#define LCD_WF8B_BPELCD49_MASK                   (0x10U)
#define LCD_WF8B_BPELCD49_SHIFT                  (4U)
/*! BPELCD49
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD49(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD49_SHIFT)) & LCD_WF8B_BPELCD49_MASK)

#define LCD_WF8B_BPELCD50_MASK                   (0x10U)
#define LCD_WF8B_BPELCD50_SHIFT                  (4U)
/*! BPELCD50
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD50(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD50_SHIFT)) & LCD_WF8B_BPELCD50_MASK)

#define LCD_WF8B_BPELCD51_MASK                   (0x10U)
#define LCD_WF8B_BPELCD51_SHIFT                  (4U)
/*! BPELCD51
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD51(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD51_SHIFT)) & LCD_WF8B_BPELCD51_MASK)

#define LCD_WF8B_BPELCD52_MASK                   (0x10U)
#define LCD_WF8B_BPELCD52_SHIFT                  (4U)
/*! BPELCD52
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD52(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD52_SHIFT)) & LCD_WF8B_BPELCD52_MASK)

#define LCD_WF8B_BPELCD53_MASK                   (0x10U)
#define LCD_WF8B_BPELCD53_SHIFT                  (4U)
/*! BPELCD53
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD53(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD53_SHIFT)) & LCD_WF8B_BPELCD53_MASK)

#define LCD_WF8B_BPELCD54_MASK                   (0x10U)
#define LCD_WF8B_BPELCD54_SHIFT                  (4U)
/*! BPELCD54
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD54(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD54_SHIFT)) & LCD_WF8B_BPELCD54_MASK)

#define LCD_WF8B_BPELCD55_MASK                   (0x10U)
#define LCD_WF8B_BPELCD55_SHIFT                  (4U)
/*! BPELCD55
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD55(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD55_SHIFT)) & LCD_WF8B_BPELCD55_MASK)

#define LCD_WF8B_BPELCD56_MASK                   (0x10U)
#define LCD_WF8B_BPELCD56_SHIFT                  (4U)
/*! BPELCD56
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD56(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD56_SHIFT)) & LCD_WF8B_BPELCD56_MASK)

#define LCD_WF8B_BPELCD57_MASK                   (0x10U)
#define LCD_WF8B_BPELCD57_SHIFT                  (4U)
/*! BPELCD57
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD57(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD57_SHIFT)) & LCD_WF8B_BPELCD57_MASK)

#define LCD_WF8B_BPELCD58_MASK                   (0x10U)
#define LCD_WF8B_BPELCD58_SHIFT                  (4U)
/*! BPELCD58
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD58(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD58_SHIFT)) & LCD_WF8B_BPELCD58_MASK)

#define LCD_WF8B_BPELCD59_MASK                   (0x10U)
#define LCD_WF8B_BPELCD59_SHIFT                  (4U)
/*! BPELCD59
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD59(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD59_SHIFT)) & LCD_WF8B_BPELCD59_MASK)

#define LCD_WF8B_BPELCD60_MASK                   (0x10U)
#define LCD_WF8B_BPELCD60_SHIFT                  (4U)
/*! BPELCD60
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD60(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD60_SHIFT)) & LCD_WF8B_BPELCD60_MASK)

#define LCD_WF8B_BPELCD61_MASK                   (0x10U)
#define LCD_WF8B_BPELCD61_SHIFT                  (4U)
/*! BPELCD61
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD61(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD61_SHIFT)) & LCD_WF8B_BPELCD61_MASK)

#define LCD_WF8B_BPELCD62_MASK                   (0x10U)
#define LCD_WF8B_BPELCD62_SHIFT                  (4U)
/*! BPELCD62
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD62(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD62_SHIFT)) & LCD_WF8B_BPELCD62_MASK)

#define LCD_WF8B_BPELCD63_MASK                   (0x10U)
#define LCD_WF8B_BPELCD63_SHIFT                  (4U)
/*! BPELCD63
 *  0b0..LCD segment off or LCD backplane inactive for phase E
 *  0b1..LCD segment on or LCD backplane active for phase E
 */
#define LCD_WF8B_BPELCD63(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPELCD63_SHIFT)) & LCD_WF8B_BPELCD63_MASK)

#define LCD_WF8B_BPFLCD0_MASK                    (0x20U)
#define LCD_WF8B_BPFLCD0_SHIFT                   (5U)
/*! BPFLCD0
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD0(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD0_SHIFT)) & LCD_WF8B_BPFLCD0_MASK)

#define LCD_WF8B_BPFLCD1_MASK                    (0x20U)
#define LCD_WF8B_BPFLCD1_SHIFT                   (5U)
/*! BPFLCD1
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD1(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD1_SHIFT)) & LCD_WF8B_BPFLCD1_MASK)

#define LCD_WF8B_BPFLCD2_MASK                    (0x20U)
#define LCD_WF8B_BPFLCD2_SHIFT                   (5U)
/*! BPFLCD2
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD2(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD2_SHIFT)) & LCD_WF8B_BPFLCD2_MASK)

#define LCD_WF8B_BPFLCD3_MASK                    (0x20U)
#define LCD_WF8B_BPFLCD3_SHIFT                   (5U)
/*! BPFLCD3
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD3(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD3_SHIFT)) & LCD_WF8B_BPFLCD3_MASK)

#define LCD_WF8B_BPFLCD4_MASK                    (0x20U)
#define LCD_WF8B_BPFLCD4_SHIFT                   (5U)
/*! BPFLCD4
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD4(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD4_SHIFT)) & LCD_WF8B_BPFLCD4_MASK)

#define LCD_WF8B_BPFLCD5_MASK                    (0x20U)
#define LCD_WF8B_BPFLCD5_SHIFT                   (5U)
/*! BPFLCD5
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD5(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD5_SHIFT)) & LCD_WF8B_BPFLCD5_MASK)

#define LCD_WF8B_BPFLCD6_MASK                    (0x20U)
#define LCD_WF8B_BPFLCD6_SHIFT                   (5U)
/*! BPFLCD6
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD6(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD6_SHIFT)) & LCD_WF8B_BPFLCD6_MASK)

#define LCD_WF8B_BPFLCD7_MASK                    (0x20U)
#define LCD_WF8B_BPFLCD7_SHIFT                   (5U)
/*! BPFLCD7
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD7(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD7_SHIFT)) & LCD_WF8B_BPFLCD7_MASK)

#define LCD_WF8B_BPFLCD8_MASK                    (0x20U)
#define LCD_WF8B_BPFLCD8_SHIFT                   (5U)
/*! BPFLCD8
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD8(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD8_SHIFT)) & LCD_WF8B_BPFLCD8_MASK)

#define LCD_WF8B_BPFLCD9_MASK                    (0x20U)
#define LCD_WF8B_BPFLCD9_SHIFT                   (5U)
/*! BPFLCD9
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD9(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD9_SHIFT)) & LCD_WF8B_BPFLCD9_MASK)

#define LCD_WF8B_BPFLCD10_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD10_SHIFT                  (5U)
/*! BPFLCD10
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD10(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD10_SHIFT)) & LCD_WF8B_BPFLCD10_MASK)

#define LCD_WF8B_BPFLCD11_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD11_SHIFT                  (5U)
/*! BPFLCD11
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD11(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD11_SHIFT)) & LCD_WF8B_BPFLCD11_MASK)

#define LCD_WF8B_BPFLCD12_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD12_SHIFT                  (5U)
/*! BPFLCD12
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD12(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD12_SHIFT)) & LCD_WF8B_BPFLCD12_MASK)

#define LCD_WF8B_BPFLCD13_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD13_SHIFT                  (5U)
/*! BPFLCD13
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD13(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD13_SHIFT)) & LCD_WF8B_BPFLCD13_MASK)

#define LCD_WF8B_BPFLCD14_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD14_SHIFT                  (5U)
/*! BPFLCD14
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD14(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD14_SHIFT)) & LCD_WF8B_BPFLCD14_MASK)

#define LCD_WF8B_BPFLCD15_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD15_SHIFT                  (5U)
/*! BPFLCD15
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD15(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD15_SHIFT)) & LCD_WF8B_BPFLCD15_MASK)

#define LCD_WF8B_BPFLCD16_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD16_SHIFT                  (5U)
/*! BPFLCD16
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD16(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD16_SHIFT)) & LCD_WF8B_BPFLCD16_MASK)

#define LCD_WF8B_BPFLCD17_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD17_SHIFT                  (5U)
/*! BPFLCD17
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD17(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD17_SHIFT)) & LCD_WF8B_BPFLCD17_MASK)

#define LCD_WF8B_BPFLCD18_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD18_SHIFT                  (5U)
/*! BPFLCD18
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD18(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD18_SHIFT)) & LCD_WF8B_BPFLCD18_MASK)

#define LCD_WF8B_BPFLCD19_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD19_SHIFT                  (5U)
/*! BPFLCD19
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD19(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD19_SHIFT)) & LCD_WF8B_BPFLCD19_MASK)

#define LCD_WF8B_BPFLCD20_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD20_SHIFT                  (5U)
/*! BPFLCD20
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD20(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD20_SHIFT)) & LCD_WF8B_BPFLCD20_MASK)

#define LCD_WF8B_BPFLCD21_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD21_SHIFT                  (5U)
/*! BPFLCD21
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD21(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD21_SHIFT)) & LCD_WF8B_BPFLCD21_MASK)

#define LCD_WF8B_BPFLCD22_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD22_SHIFT                  (5U)
/*! BPFLCD22
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD22(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD22_SHIFT)) & LCD_WF8B_BPFLCD22_MASK)

#define LCD_WF8B_BPFLCD23_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD23_SHIFT                  (5U)
/*! BPFLCD23
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD23(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD23_SHIFT)) & LCD_WF8B_BPFLCD23_MASK)

#define LCD_WF8B_BPFLCD24_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD24_SHIFT                  (5U)
/*! BPFLCD24
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD24(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD24_SHIFT)) & LCD_WF8B_BPFLCD24_MASK)

#define LCD_WF8B_BPFLCD25_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD25_SHIFT                  (5U)
/*! BPFLCD25
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD25(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD25_SHIFT)) & LCD_WF8B_BPFLCD25_MASK)

#define LCD_WF8B_BPFLCD26_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD26_SHIFT                  (5U)
/*! BPFLCD26
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD26(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD26_SHIFT)) & LCD_WF8B_BPFLCD26_MASK)

#define LCD_WF8B_BPFLCD27_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD27_SHIFT                  (5U)
/*! BPFLCD27
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD27(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD27_SHIFT)) & LCD_WF8B_BPFLCD27_MASK)

#define LCD_WF8B_BPFLCD28_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD28_SHIFT                  (5U)
/*! BPFLCD28
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD28(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD28_SHIFT)) & LCD_WF8B_BPFLCD28_MASK)

#define LCD_WF8B_BPFLCD29_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD29_SHIFT                  (5U)
/*! BPFLCD29
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD29(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD29_SHIFT)) & LCD_WF8B_BPFLCD29_MASK)

#define LCD_WF8B_BPFLCD30_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD30_SHIFT                  (5U)
/*! BPFLCD30
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD30(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD30_SHIFT)) & LCD_WF8B_BPFLCD30_MASK)

#define LCD_WF8B_BPFLCD31_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD31_SHIFT                  (5U)
/*! BPFLCD31
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD31(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD31_SHIFT)) & LCD_WF8B_BPFLCD31_MASK)

#define LCD_WF8B_BPFLCD32_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD32_SHIFT                  (5U)
/*! BPFLCD32
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD32(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD32_SHIFT)) & LCD_WF8B_BPFLCD32_MASK)

#define LCD_WF8B_BPFLCD33_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD33_SHIFT                  (5U)
/*! BPFLCD33
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD33(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD33_SHIFT)) & LCD_WF8B_BPFLCD33_MASK)

#define LCD_WF8B_BPFLCD34_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD34_SHIFT                  (5U)
/*! BPFLCD34
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD34(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD34_SHIFT)) & LCD_WF8B_BPFLCD34_MASK)

#define LCD_WF8B_BPFLCD35_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD35_SHIFT                  (5U)
/*! BPFLCD35
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD35(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD35_SHIFT)) & LCD_WF8B_BPFLCD35_MASK)

#define LCD_WF8B_BPFLCD36_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD36_SHIFT                  (5U)
/*! BPFLCD36
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD36(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD36_SHIFT)) & LCD_WF8B_BPFLCD36_MASK)

#define LCD_WF8B_BPFLCD37_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD37_SHIFT                  (5U)
/*! BPFLCD37
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD37(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD37_SHIFT)) & LCD_WF8B_BPFLCD37_MASK)

#define LCD_WF8B_BPFLCD38_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD38_SHIFT                  (5U)
/*! BPFLCD38
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD38(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD38_SHIFT)) & LCD_WF8B_BPFLCD38_MASK)

#define LCD_WF8B_BPFLCD39_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD39_SHIFT                  (5U)
/*! BPFLCD39
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD39(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD39_SHIFT)) & LCD_WF8B_BPFLCD39_MASK)

#define LCD_WF8B_BPFLCD40_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD40_SHIFT                  (5U)
/*! BPFLCD40
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD40(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD40_SHIFT)) & LCD_WF8B_BPFLCD40_MASK)

#define LCD_WF8B_BPFLCD41_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD41_SHIFT                  (5U)
/*! BPFLCD41
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD41(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD41_SHIFT)) & LCD_WF8B_BPFLCD41_MASK)

#define LCD_WF8B_BPFLCD42_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD42_SHIFT                  (5U)
/*! BPFLCD42
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD42(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD42_SHIFT)) & LCD_WF8B_BPFLCD42_MASK)

#define LCD_WF8B_BPFLCD43_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD43_SHIFT                  (5U)
/*! BPFLCD43
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD43(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD43_SHIFT)) & LCD_WF8B_BPFLCD43_MASK)

#define LCD_WF8B_BPFLCD44_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD44_SHIFT                  (5U)
/*! BPFLCD44
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD44(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD44_SHIFT)) & LCD_WF8B_BPFLCD44_MASK)

#define LCD_WF8B_BPFLCD45_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD45_SHIFT                  (5U)
/*! BPFLCD45
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD45(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD45_SHIFT)) & LCD_WF8B_BPFLCD45_MASK)

#define LCD_WF8B_BPFLCD46_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD46_SHIFT                  (5U)
/*! BPFLCD46
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD46(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD46_SHIFT)) & LCD_WF8B_BPFLCD46_MASK)

#define LCD_WF8B_BPFLCD47_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD47_SHIFT                  (5U)
/*! BPFLCD47
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD47(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD47_SHIFT)) & LCD_WF8B_BPFLCD47_MASK)

#define LCD_WF8B_BPFLCD48_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD48_SHIFT                  (5U)
/*! BPFLCD48
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD48(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD48_SHIFT)) & LCD_WF8B_BPFLCD48_MASK)

#define LCD_WF8B_BPFLCD49_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD49_SHIFT                  (5U)
/*! BPFLCD49
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD49(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD49_SHIFT)) & LCD_WF8B_BPFLCD49_MASK)

#define LCD_WF8B_BPFLCD50_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD50_SHIFT                  (5U)
/*! BPFLCD50
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD50(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD50_SHIFT)) & LCD_WF8B_BPFLCD50_MASK)

#define LCD_WF8B_BPFLCD51_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD51_SHIFT                  (5U)
/*! BPFLCD51
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD51(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD51_SHIFT)) & LCD_WF8B_BPFLCD51_MASK)

#define LCD_WF8B_BPFLCD52_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD52_SHIFT                  (5U)
/*! BPFLCD52
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD52(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD52_SHIFT)) & LCD_WF8B_BPFLCD52_MASK)

#define LCD_WF8B_BPFLCD53_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD53_SHIFT                  (5U)
/*! BPFLCD53
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD53(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD53_SHIFT)) & LCD_WF8B_BPFLCD53_MASK)

#define LCD_WF8B_BPFLCD54_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD54_SHIFT                  (5U)
/*! BPFLCD54
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD54(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD54_SHIFT)) & LCD_WF8B_BPFLCD54_MASK)

#define LCD_WF8B_BPFLCD55_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD55_SHIFT                  (5U)
/*! BPFLCD55
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD55(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD55_SHIFT)) & LCD_WF8B_BPFLCD55_MASK)

#define LCD_WF8B_BPFLCD56_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD56_SHIFT                  (5U)
/*! BPFLCD56
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD56(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD56_SHIFT)) & LCD_WF8B_BPFLCD56_MASK)

#define LCD_WF8B_BPFLCD57_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD57_SHIFT                  (5U)
/*! BPFLCD57
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD57(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD57_SHIFT)) & LCD_WF8B_BPFLCD57_MASK)

#define LCD_WF8B_BPFLCD58_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD58_SHIFT                  (5U)
/*! BPFLCD58
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD58(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD58_SHIFT)) & LCD_WF8B_BPFLCD58_MASK)

#define LCD_WF8B_BPFLCD59_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD59_SHIFT                  (5U)
/*! BPFLCD59
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD59(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD59_SHIFT)) & LCD_WF8B_BPFLCD59_MASK)

#define LCD_WF8B_BPFLCD60_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD60_SHIFT                  (5U)
/*! BPFLCD60
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD60(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD60_SHIFT)) & LCD_WF8B_BPFLCD60_MASK)

#define LCD_WF8B_BPFLCD61_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD61_SHIFT                  (5U)
/*! BPFLCD61
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD61(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD61_SHIFT)) & LCD_WF8B_BPFLCD61_MASK)

#define LCD_WF8B_BPFLCD62_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD62_SHIFT                  (5U)
/*! BPFLCD62
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD62(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD62_SHIFT)) & LCD_WF8B_BPFLCD62_MASK)

#define LCD_WF8B_BPFLCD63_MASK                   (0x20U)
#define LCD_WF8B_BPFLCD63_SHIFT                  (5U)
/*! BPFLCD63
 *  0b0..LCD segment off or LCD backplane inactive for phase F
 *  0b1..LCD segment on or LCD backplane active for phase F
 */
#define LCD_WF8B_BPFLCD63(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPFLCD63_SHIFT)) & LCD_WF8B_BPFLCD63_MASK)

#define LCD_WF8B_BPGLCD0_MASK                    (0x40U)
#define LCD_WF8B_BPGLCD0_SHIFT                   (6U)
/*! BPGLCD0
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD0(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD0_SHIFT)) & LCD_WF8B_BPGLCD0_MASK)

#define LCD_WF8B_BPGLCD1_MASK                    (0x40U)
#define LCD_WF8B_BPGLCD1_SHIFT                   (6U)
/*! BPGLCD1
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD1(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD1_SHIFT)) & LCD_WF8B_BPGLCD1_MASK)

#define LCD_WF8B_BPGLCD2_MASK                    (0x40U)
#define LCD_WF8B_BPGLCD2_SHIFT                   (6U)
/*! BPGLCD2
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD2(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD2_SHIFT)) & LCD_WF8B_BPGLCD2_MASK)

#define LCD_WF8B_BPGLCD3_MASK                    (0x40U)
#define LCD_WF8B_BPGLCD3_SHIFT                   (6U)
/*! BPGLCD3
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD3(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD3_SHIFT)) & LCD_WF8B_BPGLCD3_MASK)

#define LCD_WF8B_BPGLCD4_MASK                    (0x40U)
#define LCD_WF8B_BPGLCD4_SHIFT                   (6U)
/*! BPGLCD4
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD4(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD4_SHIFT)) & LCD_WF8B_BPGLCD4_MASK)

#define LCD_WF8B_BPGLCD5_MASK                    (0x40U)
#define LCD_WF8B_BPGLCD5_SHIFT                   (6U)
/*! BPGLCD5
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD5(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD5_SHIFT)) & LCD_WF8B_BPGLCD5_MASK)

#define LCD_WF8B_BPGLCD6_MASK                    (0x40U)
#define LCD_WF8B_BPGLCD6_SHIFT                   (6U)
/*! BPGLCD6
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD6(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD6_SHIFT)) & LCD_WF8B_BPGLCD6_MASK)

#define LCD_WF8B_BPGLCD7_MASK                    (0x40U)
#define LCD_WF8B_BPGLCD7_SHIFT                   (6U)
/*! BPGLCD7
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD7(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD7_SHIFT)) & LCD_WF8B_BPGLCD7_MASK)

#define LCD_WF8B_BPGLCD8_MASK                    (0x40U)
#define LCD_WF8B_BPGLCD8_SHIFT                   (6U)
/*! BPGLCD8
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD8(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD8_SHIFT)) & LCD_WF8B_BPGLCD8_MASK)

#define LCD_WF8B_BPGLCD9_MASK                    (0x40U)
#define LCD_WF8B_BPGLCD9_SHIFT                   (6U)
/*! BPGLCD9
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD9(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD9_SHIFT)) & LCD_WF8B_BPGLCD9_MASK)

#define LCD_WF8B_BPGLCD10_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD10_SHIFT                  (6U)
/*! BPGLCD10
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD10(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD10_SHIFT)) & LCD_WF8B_BPGLCD10_MASK)

#define LCD_WF8B_BPGLCD11_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD11_SHIFT                  (6U)
/*! BPGLCD11
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD11(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD11_SHIFT)) & LCD_WF8B_BPGLCD11_MASK)

#define LCD_WF8B_BPGLCD12_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD12_SHIFT                  (6U)
/*! BPGLCD12
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD12(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD12_SHIFT)) & LCD_WF8B_BPGLCD12_MASK)

#define LCD_WF8B_BPGLCD13_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD13_SHIFT                  (6U)
/*! BPGLCD13
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD13(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD13_SHIFT)) & LCD_WF8B_BPGLCD13_MASK)

#define LCD_WF8B_BPGLCD14_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD14_SHIFT                  (6U)
/*! BPGLCD14
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD14(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD14_SHIFT)) & LCD_WF8B_BPGLCD14_MASK)

#define LCD_WF8B_BPGLCD15_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD15_SHIFT                  (6U)
/*! BPGLCD15
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD15(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD15_SHIFT)) & LCD_WF8B_BPGLCD15_MASK)

#define LCD_WF8B_BPGLCD16_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD16_SHIFT                  (6U)
/*! BPGLCD16
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD16(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD16_SHIFT)) & LCD_WF8B_BPGLCD16_MASK)

#define LCD_WF8B_BPGLCD17_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD17_SHIFT                  (6U)
/*! BPGLCD17
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD17(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD17_SHIFT)) & LCD_WF8B_BPGLCD17_MASK)

#define LCD_WF8B_BPGLCD18_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD18_SHIFT                  (6U)
/*! BPGLCD18
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD18(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD18_SHIFT)) & LCD_WF8B_BPGLCD18_MASK)

#define LCD_WF8B_BPGLCD19_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD19_SHIFT                  (6U)
/*! BPGLCD19
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD19(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD19_SHIFT)) & LCD_WF8B_BPGLCD19_MASK)

#define LCD_WF8B_BPGLCD20_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD20_SHIFT                  (6U)
/*! BPGLCD20
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD20(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD20_SHIFT)) & LCD_WF8B_BPGLCD20_MASK)

#define LCD_WF8B_BPGLCD21_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD21_SHIFT                  (6U)
/*! BPGLCD21
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD21(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD21_SHIFT)) & LCD_WF8B_BPGLCD21_MASK)

#define LCD_WF8B_BPGLCD22_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD22_SHIFT                  (6U)
/*! BPGLCD22
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD22(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD22_SHIFT)) & LCD_WF8B_BPGLCD22_MASK)

#define LCD_WF8B_BPGLCD23_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD23_SHIFT                  (6U)
/*! BPGLCD23
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD23(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD23_SHIFT)) & LCD_WF8B_BPGLCD23_MASK)

#define LCD_WF8B_BPGLCD24_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD24_SHIFT                  (6U)
/*! BPGLCD24
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD24(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD24_SHIFT)) & LCD_WF8B_BPGLCD24_MASK)

#define LCD_WF8B_BPGLCD25_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD25_SHIFT                  (6U)
/*! BPGLCD25
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD25(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD25_SHIFT)) & LCD_WF8B_BPGLCD25_MASK)

#define LCD_WF8B_BPGLCD26_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD26_SHIFT                  (6U)
/*! BPGLCD26
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD26(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD26_SHIFT)) & LCD_WF8B_BPGLCD26_MASK)

#define LCD_WF8B_BPGLCD27_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD27_SHIFT                  (6U)
/*! BPGLCD27
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD27(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD27_SHIFT)) & LCD_WF8B_BPGLCD27_MASK)

#define LCD_WF8B_BPGLCD28_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD28_SHIFT                  (6U)
/*! BPGLCD28
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD28(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD28_SHIFT)) & LCD_WF8B_BPGLCD28_MASK)

#define LCD_WF8B_BPGLCD29_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD29_SHIFT                  (6U)
/*! BPGLCD29
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD29(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD29_SHIFT)) & LCD_WF8B_BPGLCD29_MASK)

#define LCD_WF8B_BPGLCD30_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD30_SHIFT                  (6U)
/*! BPGLCD30
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD30(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD30_SHIFT)) & LCD_WF8B_BPGLCD30_MASK)

#define LCD_WF8B_BPGLCD31_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD31_SHIFT                  (6U)
/*! BPGLCD31
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD31(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD31_SHIFT)) & LCD_WF8B_BPGLCD31_MASK)

#define LCD_WF8B_BPGLCD32_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD32_SHIFT                  (6U)
/*! BPGLCD32
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD32(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD32_SHIFT)) & LCD_WF8B_BPGLCD32_MASK)

#define LCD_WF8B_BPGLCD33_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD33_SHIFT                  (6U)
/*! BPGLCD33
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD33(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD33_SHIFT)) & LCD_WF8B_BPGLCD33_MASK)

#define LCD_WF8B_BPGLCD34_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD34_SHIFT                  (6U)
/*! BPGLCD34
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD34(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD34_SHIFT)) & LCD_WF8B_BPGLCD34_MASK)

#define LCD_WF8B_BPGLCD35_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD35_SHIFT                  (6U)
/*! BPGLCD35
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD35(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD35_SHIFT)) & LCD_WF8B_BPGLCD35_MASK)

#define LCD_WF8B_BPGLCD36_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD36_SHIFT                  (6U)
/*! BPGLCD36
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD36(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD36_SHIFT)) & LCD_WF8B_BPGLCD36_MASK)

#define LCD_WF8B_BPGLCD37_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD37_SHIFT                  (6U)
/*! BPGLCD37
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD37(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD37_SHIFT)) & LCD_WF8B_BPGLCD37_MASK)

#define LCD_WF8B_BPGLCD38_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD38_SHIFT                  (6U)
/*! BPGLCD38
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD38(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD38_SHIFT)) & LCD_WF8B_BPGLCD38_MASK)

#define LCD_WF8B_BPGLCD39_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD39_SHIFT                  (6U)
/*! BPGLCD39
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD39(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD39_SHIFT)) & LCD_WF8B_BPGLCD39_MASK)

#define LCD_WF8B_BPGLCD40_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD40_SHIFT                  (6U)
/*! BPGLCD40
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD40(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD40_SHIFT)) & LCD_WF8B_BPGLCD40_MASK)

#define LCD_WF8B_BPGLCD41_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD41_SHIFT                  (6U)
/*! BPGLCD41
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD41(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD41_SHIFT)) & LCD_WF8B_BPGLCD41_MASK)

#define LCD_WF8B_BPGLCD42_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD42_SHIFT                  (6U)
/*! BPGLCD42
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD42(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD42_SHIFT)) & LCD_WF8B_BPGLCD42_MASK)

#define LCD_WF8B_BPGLCD43_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD43_SHIFT                  (6U)
/*! BPGLCD43
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD43(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD43_SHIFT)) & LCD_WF8B_BPGLCD43_MASK)

#define LCD_WF8B_BPGLCD44_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD44_SHIFT                  (6U)
/*! BPGLCD44
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD44(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD44_SHIFT)) & LCD_WF8B_BPGLCD44_MASK)

#define LCD_WF8B_BPGLCD45_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD45_SHIFT                  (6U)
/*! BPGLCD45
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD45(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD45_SHIFT)) & LCD_WF8B_BPGLCD45_MASK)

#define LCD_WF8B_BPGLCD46_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD46_SHIFT                  (6U)
/*! BPGLCD46
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD46(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD46_SHIFT)) & LCD_WF8B_BPGLCD46_MASK)

#define LCD_WF8B_BPGLCD47_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD47_SHIFT                  (6U)
/*! BPGLCD47
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD47(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD47_SHIFT)) & LCD_WF8B_BPGLCD47_MASK)

#define LCD_WF8B_BPGLCD48_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD48_SHIFT                  (6U)
/*! BPGLCD48
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD48(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD48_SHIFT)) & LCD_WF8B_BPGLCD48_MASK)

#define LCD_WF8B_BPGLCD49_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD49_SHIFT                  (6U)
/*! BPGLCD49
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD49(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD49_SHIFT)) & LCD_WF8B_BPGLCD49_MASK)

#define LCD_WF8B_BPGLCD50_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD50_SHIFT                  (6U)
/*! BPGLCD50
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD50(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD50_SHIFT)) & LCD_WF8B_BPGLCD50_MASK)

#define LCD_WF8B_BPGLCD51_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD51_SHIFT                  (6U)
/*! BPGLCD51
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD51(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD51_SHIFT)) & LCD_WF8B_BPGLCD51_MASK)

#define LCD_WF8B_BPGLCD52_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD52_SHIFT                  (6U)
/*! BPGLCD52
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD52(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD52_SHIFT)) & LCD_WF8B_BPGLCD52_MASK)

#define LCD_WF8B_BPGLCD53_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD53_SHIFT                  (6U)
/*! BPGLCD53
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD53(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD53_SHIFT)) & LCD_WF8B_BPGLCD53_MASK)

#define LCD_WF8B_BPGLCD54_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD54_SHIFT                  (6U)
/*! BPGLCD54
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD54(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD54_SHIFT)) & LCD_WF8B_BPGLCD54_MASK)

#define LCD_WF8B_BPGLCD55_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD55_SHIFT                  (6U)
/*! BPGLCD55
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD55(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD55_SHIFT)) & LCD_WF8B_BPGLCD55_MASK)

#define LCD_WF8B_BPGLCD56_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD56_SHIFT                  (6U)
/*! BPGLCD56
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD56(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD56_SHIFT)) & LCD_WF8B_BPGLCD56_MASK)

#define LCD_WF8B_BPGLCD57_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD57_SHIFT                  (6U)
/*! BPGLCD57
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD57(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD57_SHIFT)) & LCD_WF8B_BPGLCD57_MASK)

#define LCD_WF8B_BPGLCD58_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD58_SHIFT                  (6U)
/*! BPGLCD58
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD58(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD58_SHIFT)) & LCD_WF8B_BPGLCD58_MASK)

#define LCD_WF8B_BPGLCD59_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD59_SHIFT                  (6U)
/*! BPGLCD59
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD59(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD59_SHIFT)) & LCD_WF8B_BPGLCD59_MASK)

#define LCD_WF8B_BPGLCD60_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD60_SHIFT                  (6U)
/*! BPGLCD60
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD60(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD60_SHIFT)) & LCD_WF8B_BPGLCD60_MASK)

#define LCD_WF8B_BPGLCD61_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD61_SHIFT                  (6U)
/*! BPGLCD61
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD61(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD61_SHIFT)) & LCD_WF8B_BPGLCD61_MASK)

#define LCD_WF8B_BPGLCD62_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD62_SHIFT                  (6U)
/*! BPGLCD62
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD62(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD62_SHIFT)) & LCD_WF8B_BPGLCD62_MASK)

#define LCD_WF8B_BPGLCD63_MASK                   (0x40U)
#define LCD_WF8B_BPGLCD63_SHIFT                  (6U)
/*! BPGLCD63
 *  0b0..LCD segment off or LCD backplane inactive for phase G
 *  0b1..LCD segment on or LCD backplane active for phase G
 */
#define LCD_WF8B_BPGLCD63(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPGLCD63_SHIFT)) & LCD_WF8B_BPGLCD63_MASK)

#define LCD_WF8B_BPHLCD0_MASK                    (0x80U)
#define LCD_WF8B_BPHLCD0_SHIFT                   (7U)
/*! BPHLCD0
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD0(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD0_SHIFT)) & LCD_WF8B_BPHLCD0_MASK)

#define LCD_WF8B_BPHLCD1_MASK                    (0x80U)
#define LCD_WF8B_BPHLCD1_SHIFT                   (7U)
/*! BPHLCD1
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD1(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD1_SHIFT)) & LCD_WF8B_BPHLCD1_MASK)

#define LCD_WF8B_BPHLCD2_MASK                    (0x80U)
#define LCD_WF8B_BPHLCD2_SHIFT                   (7U)
/*! BPHLCD2
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD2(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD2_SHIFT)) & LCD_WF8B_BPHLCD2_MASK)

#define LCD_WF8B_BPHLCD3_MASK                    (0x80U)
#define LCD_WF8B_BPHLCD3_SHIFT                   (7U)
/*! BPHLCD3
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD3(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD3_SHIFT)) & LCD_WF8B_BPHLCD3_MASK)

#define LCD_WF8B_BPHLCD4_MASK                    (0x80U)
#define LCD_WF8B_BPHLCD4_SHIFT                   (7U)
/*! BPHLCD4
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD4(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD4_SHIFT)) & LCD_WF8B_BPHLCD4_MASK)

#define LCD_WF8B_BPHLCD5_MASK                    (0x80U)
#define LCD_WF8B_BPHLCD5_SHIFT                   (7U)
/*! BPHLCD5
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD5(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD5_SHIFT)) & LCD_WF8B_BPHLCD5_MASK)

#define LCD_WF8B_BPHLCD6_MASK                    (0x80U)
#define LCD_WF8B_BPHLCD6_SHIFT                   (7U)
/*! BPHLCD6
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD6(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD6_SHIFT)) & LCD_WF8B_BPHLCD6_MASK)

#define LCD_WF8B_BPHLCD7_MASK                    (0x80U)
#define LCD_WF8B_BPHLCD7_SHIFT                   (7U)
/*! BPHLCD7
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD7(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD7_SHIFT)) & LCD_WF8B_BPHLCD7_MASK)

#define LCD_WF8B_BPHLCD8_MASK                    (0x80U)
#define LCD_WF8B_BPHLCD8_SHIFT                   (7U)
/*! BPHLCD8
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD8(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD8_SHIFT)) & LCD_WF8B_BPHLCD8_MASK)

#define LCD_WF8B_BPHLCD9_MASK                    (0x80U)
#define LCD_WF8B_BPHLCD9_SHIFT                   (7U)
/*! BPHLCD9
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD9(x)                      (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD9_SHIFT)) & LCD_WF8B_BPHLCD9_MASK)

#define LCD_WF8B_BPHLCD10_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD10_SHIFT                  (7U)
/*! BPHLCD10
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD10(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD10_SHIFT)) & LCD_WF8B_BPHLCD10_MASK)

#define LCD_WF8B_BPHLCD11_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD11_SHIFT                  (7U)
/*! BPHLCD11
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD11(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD11_SHIFT)) & LCD_WF8B_BPHLCD11_MASK)

#define LCD_WF8B_BPHLCD12_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD12_SHIFT                  (7U)
/*! BPHLCD12
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD12(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD12_SHIFT)) & LCD_WF8B_BPHLCD12_MASK)

#define LCD_WF8B_BPHLCD13_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD13_SHIFT                  (7U)
/*! BPHLCD13
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD13(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD13_SHIFT)) & LCD_WF8B_BPHLCD13_MASK)

#define LCD_WF8B_BPHLCD14_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD14_SHIFT                  (7U)
/*! BPHLCD14
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD14(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD14_SHIFT)) & LCD_WF8B_BPHLCD14_MASK)

#define LCD_WF8B_BPHLCD15_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD15_SHIFT                  (7U)
/*! BPHLCD15
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD15(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD15_SHIFT)) & LCD_WF8B_BPHLCD15_MASK)

#define LCD_WF8B_BPHLCD16_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD16_SHIFT                  (7U)
/*! BPHLCD16
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD16(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD16_SHIFT)) & LCD_WF8B_BPHLCD16_MASK)

#define LCD_WF8B_BPHLCD17_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD17_SHIFT                  (7U)
/*! BPHLCD17
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD17(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD17_SHIFT)) & LCD_WF8B_BPHLCD17_MASK)

#define LCD_WF8B_BPHLCD18_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD18_SHIFT                  (7U)
/*! BPHLCD18
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD18(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD18_SHIFT)) & LCD_WF8B_BPHLCD18_MASK)

#define LCD_WF8B_BPHLCD19_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD19_SHIFT                  (7U)
/*! BPHLCD19
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD19(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD19_SHIFT)) & LCD_WF8B_BPHLCD19_MASK)

#define LCD_WF8B_BPHLCD20_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD20_SHIFT                  (7U)
/*! BPHLCD20
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD20(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD20_SHIFT)) & LCD_WF8B_BPHLCD20_MASK)

#define LCD_WF8B_BPHLCD21_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD21_SHIFT                  (7U)
/*! BPHLCD21
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD21(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD21_SHIFT)) & LCD_WF8B_BPHLCD21_MASK)

#define LCD_WF8B_BPHLCD22_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD22_SHIFT                  (7U)
/*! BPHLCD22
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD22(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD22_SHIFT)) & LCD_WF8B_BPHLCD22_MASK)

#define LCD_WF8B_BPHLCD23_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD23_SHIFT                  (7U)
/*! BPHLCD23
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD23(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD23_SHIFT)) & LCD_WF8B_BPHLCD23_MASK)

#define LCD_WF8B_BPHLCD24_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD24_SHIFT                  (7U)
/*! BPHLCD24
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD24(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD24_SHIFT)) & LCD_WF8B_BPHLCD24_MASK)

#define LCD_WF8B_BPHLCD25_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD25_SHIFT                  (7U)
/*! BPHLCD25
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD25(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD25_SHIFT)) & LCD_WF8B_BPHLCD25_MASK)

#define LCD_WF8B_BPHLCD26_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD26_SHIFT                  (7U)
/*! BPHLCD26
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD26(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD26_SHIFT)) & LCD_WF8B_BPHLCD26_MASK)

#define LCD_WF8B_BPHLCD27_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD27_SHIFT                  (7U)
/*! BPHLCD27
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD27(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD27_SHIFT)) & LCD_WF8B_BPHLCD27_MASK)

#define LCD_WF8B_BPHLCD28_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD28_SHIFT                  (7U)
/*! BPHLCD28
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD28(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD28_SHIFT)) & LCD_WF8B_BPHLCD28_MASK)

#define LCD_WF8B_BPHLCD29_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD29_SHIFT                  (7U)
/*! BPHLCD29
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD29(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD29_SHIFT)) & LCD_WF8B_BPHLCD29_MASK)

#define LCD_WF8B_BPHLCD30_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD30_SHIFT                  (7U)
/*! BPHLCD30
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD30(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD30_SHIFT)) & LCD_WF8B_BPHLCD30_MASK)

#define LCD_WF8B_BPHLCD31_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD31_SHIFT                  (7U)
/*! BPHLCD31
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD31(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD31_SHIFT)) & LCD_WF8B_BPHLCD31_MASK)

#define LCD_WF8B_BPHLCD32_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD32_SHIFT                  (7U)
/*! BPHLCD32
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD32(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD32_SHIFT)) & LCD_WF8B_BPHLCD32_MASK)

#define LCD_WF8B_BPHLCD33_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD33_SHIFT                  (7U)
/*! BPHLCD33
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD33(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD33_SHIFT)) & LCD_WF8B_BPHLCD33_MASK)

#define LCD_WF8B_BPHLCD34_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD34_SHIFT                  (7U)
/*! BPHLCD34
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD34(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD34_SHIFT)) & LCD_WF8B_BPHLCD34_MASK)

#define LCD_WF8B_BPHLCD35_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD35_SHIFT                  (7U)
/*! BPHLCD35
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD35(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD35_SHIFT)) & LCD_WF8B_BPHLCD35_MASK)

#define LCD_WF8B_BPHLCD36_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD36_SHIFT                  (7U)
/*! BPHLCD36
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD36(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD36_SHIFT)) & LCD_WF8B_BPHLCD36_MASK)

#define LCD_WF8B_BPHLCD37_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD37_SHIFT                  (7U)
/*! BPHLCD37
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD37(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD37_SHIFT)) & LCD_WF8B_BPHLCD37_MASK)

#define LCD_WF8B_BPHLCD38_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD38_SHIFT                  (7U)
/*! BPHLCD38
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD38(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD38_SHIFT)) & LCD_WF8B_BPHLCD38_MASK)

#define LCD_WF8B_BPHLCD39_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD39_SHIFT                  (7U)
/*! BPHLCD39
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD39(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD39_SHIFT)) & LCD_WF8B_BPHLCD39_MASK)

#define LCD_WF8B_BPHLCD40_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD40_SHIFT                  (7U)
/*! BPHLCD40
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD40(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD40_SHIFT)) & LCD_WF8B_BPHLCD40_MASK)

#define LCD_WF8B_BPHLCD41_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD41_SHIFT                  (7U)
/*! BPHLCD41
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD41(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD41_SHIFT)) & LCD_WF8B_BPHLCD41_MASK)

#define LCD_WF8B_BPHLCD42_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD42_SHIFT                  (7U)
/*! BPHLCD42
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD42(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD42_SHIFT)) & LCD_WF8B_BPHLCD42_MASK)

#define LCD_WF8B_BPHLCD43_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD43_SHIFT                  (7U)
/*! BPHLCD43
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD43(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD43_SHIFT)) & LCD_WF8B_BPHLCD43_MASK)

#define LCD_WF8B_BPHLCD44_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD44_SHIFT                  (7U)
/*! BPHLCD44
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD44(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD44_SHIFT)) & LCD_WF8B_BPHLCD44_MASK)

#define LCD_WF8B_BPHLCD45_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD45_SHIFT                  (7U)
/*! BPHLCD45
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD45(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD45_SHIFT)) & LCD_WF8B_BPHLCD45_MASK)

#define LCD_WF8B_BPHLCD46_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD46_SHIFT                  (7U)
/*! BPHLCD46
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD46(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD46_SHIFT)) & LCD_WF8B_BPHLCD46_MASK)

#define LCD_WF8B_BPHLCD47_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD47_SHIFT                  (7U)
/*! BPHLCD47
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD47(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD47_SHIFT)) & LCD_WF8B_BPHLCD47_MASK)

#define LCD_WF8B_BPHLCD48_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD48_SHIFT                  (7U)
/*! BPHLCD48
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD48(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD48_SHIFT)) & LCD_WF8B_BPHLCD48_MASK)

#define LCD_WF8B_BPHLCD49_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD49_SHIFT                  (7U)
/*! BPHLCD49
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD49(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD49_SHIFT)) & LCD_WF8B_BPHLCD49_MASK)

#define LCD_WF8B_BPHLCD50_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD50_SHIFT                  (7U)
/*! BPHLCD50
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD50(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD50_SHIFT)) & LCD_WF8B_BPHLCD50_MASK)

#define LCD_WF8B_BPHLCD51_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD51_SHIFT                  (7U)
/*! BPHLCD51
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD51(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD51_SHIFT)) & LCD_WF8B_BPHLCD51_MASK)

#define LCD_WF8B_BPHLCD52_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD52_SHIFT                  (7U)
/*! BPHLCD52
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD52(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD52_SHIFT)) & LCD_WF8B_BPHLCD52_MASK)

#define LCD_WF8B_BPHLCD53_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD53_SHIFT                  (7U)
/*! BPHLCD53
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD53(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD53_SHIFT)) & LCD_WF8B_BPHLCD53_MASK)

#define LCD_WF8B_BPHLCD54_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD54_SHIFT                  (7U)
/*! BPHLCD54
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD54(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD54_SHIFT)) & LCD_WF8B_BPHLCD54_MASK)

#define LCD_WF8B_BPHLCD55_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD55_SHIFT                  (7U)
/*! BPHLCD55
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD55(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD55_SHIFT)) & LCD_WF8B_BPHLCD55_MASK)

#define LCD_WF8B_BPHLCD56_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD56_SHIFT                  (7U)
/*! BPHLCD56
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD56(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD56_SHIFT)) & LCD_WF8B_BPHLCD56_MASK)

#define LCD_WF8B_BPHLCD57_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD57_SHIFT                  (7U)
/*! BPHLCD57
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD57(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD57_SHIFT)) & LCD_WF8B_BPHLCD57_MASK)

#define LCD_WF8B_BPHLCD58_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD58_SHIFT                  (7U)
/*! BPHLCD58
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD58(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD58_SHIFT)) & LCD_WF8B_BPHLCD58_MASK)

#define LCD_WF8B_BPHLCD59_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD59_SHIFT                  (7U)
/*! BPHLCD59
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD59(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD59_SHIFT)) & LCD_WF8B_BPHLCD59_MASK)

#define LCD_WF8B_BPHLCD60_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD60_SHIFT                  (7U)
/*! BPHLCD60
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD60(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD60_SHIFT)) & LCD_WF8B_BPHLCD60_MASK)

#define LCD_WF8B_BPHLCD61_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD61_SHIFT                  (7U)
/*! BPHLCD61
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD61(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD61_SHIFT)) & LCD_WF8B_BPHLCD61_MASK)

#define LCD_WF8B_BPHLCD62_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD62_SHIFT                  (7U)
/*! BPHLCD62
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD62(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD62_SHIFT)) & LCD_WF8B_BPHLCD62_MASK)

#define LCD_WF8B_BPHLCD63_MASK                   (0x80U)
#define LCD_WF8B_BPHLCD63_SHIFT                  (7U)
/*! BPHLCD63
 *  0b0..LCD segment off or LCD backplane inactive for phase H
 *  0b1..LCD segment on or LCD backplane active for phase H
 */
#define LCD_WF8B_BPHLCD63(x)                     (((uint8_t)(((uint8_t)(x)) << LCD_WF8B_BPHLCD63_SHIFT)) & LCD_WF8B_BPHLCD63_MASK)
/*! @} */

/* The count of LCD_WF8B */
#define LCD_WF8B_COUNT                           (64U)

/*! @name WF - LCD Waveform register */
/*! @{ */

#define LCD_WF_WF0_MASK                          (0xFFU)
#define LCD_WF_WF0_SHIFT                         (0U)
#define LCD_WF_WF0(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF0_SHIFT)) & LCD_WF_WF0_MASK)

#define LCD_WF_WF4_MASK                          (0xFFU)
#define LCD_WF_WF4_SHIFT                         (0U)
#define LCD_WF_WF4(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF4_SHIFT)) & LCD_WF_WF4_MASK)

#define LCD_WF_WF8_MASK                          (0xFFU)
#define LCD_WF_WF8_SHIFT                         (0U)
#define LCD_WF_WF8(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF8_SHIFT)) & LCD_WF_WF8_MASK)

#define LCD_WF_WF12_MASK                         (0xFFU)
#define LCD_WF_WF12_SHIFT                        (0U)
#define LCD_WF_WF12(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF12_SHIFT)) & LCD_WF_WF12_MASK)

#define LCD_WF_WF16_MASK                         (0xFFU)
#define LCD_WF_WF16_SHIFT                        (0U)
#define LCD_WF_WF16(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF16_SHIFT)) & LCD_WF_WF16_MASK)

#define LCD_WF_WF20_MASK                         (0xFFU)
#define LCD_WF_WF20_SHIFT                        (0U)
#define LCD_WF_WF20(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF20_SHIFT)) & LCD_WF_WF20_MASK)

#define LCD_WF_WF24_MASK                         (0xFFU)
#define LCD_WF_WF24_SHIFT                        (0U)
#define LCD_WF_WF24(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF24_SHIFT)) & LCD_WF_WF24_MASK)

#define LCD_WF_WF28_MASK                         (0xFFU)
#define LCD_WF_WF28_SHIFT                        (0U)
#define LCD_WF_WF28(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF28_SHIFT)) & LCD_WF_WF28_MASK)

#define LCD_WF_WF32_MASK                         (0xFFU)
#define LCD_WF_WF32_SHIFT                        (0U)
#define LCD_WF_WF32(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF32_SHIFT)) & LCD_WF_WF32_MASK)

#define LCD_WF_WF36_MASK                         (0xFFU)
#define LCD_WF_WF36_SHIFT                        (0U)
#define LCD_WF_WF36(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF36_SHIFT)) & LCD_WF_WF36_MASK)

#define LCD_WF_WF40_MASK                         (0xFFU)
#define LCD_WF_WF40_SHIFT                        (0U)
#define LCD_WF_WF40(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF40_SHIFT)) & LCD_WF_WF40_MASK)

#define LCD_WF_WF44_MASK                         (0xFFU)
#define LCD_WF_WF44_SHIFT                        (0U)
#define LCD_WF_WF44(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF44_SHIFT)) & LCD_WF_WF44_MASK)

#define LCD_WF_WF48_MASK                         (0xFFU)
#define LCD_WF_WF48_SHIFT                        (0U)
#define LCD_WF_WF48(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF48_SHIFT)) & LCD_WF_WF48_MASK)

#define LCD_WF_WF52_MASK                         (0xFFU)
#define LCD_WF_WF52_SHIFT                        (0U)
#define LCD_WF_WF52(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF52_SHIFT)) & LCD_WF_WF52_MASK)

#define LCD_WF_WF56_MASK                         (0xFFU)
#define LCD_WF_WF56_SHIFT                        (0U)
#define LCD_WF_WF56(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF56_SHIFT)) & LCD_WF_WF56_MASK)

#define LCD_WF_WF60_MASK                         (0xFFU)
#define LCD_WF_WF60_SHIFT                        (0U)
#define LCD_WF_WF60(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF60_SHIFT)) & LCD_WF_WF60_MASK)

#define LCD_WF_WF1_MASK                          (0xFF00U)
#define LCD_WF_WF1_SHIFT                         (8U)
#define LCD_WF_WF1(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF1_SHIFT)) & LCD_WF_WF1_MASK)

#define LCD_WF_WF5_MASK                          (0xFF00U)
#define LCD_WF_WF5_SHIFT                         (8U)
#define LCD_WF_WF5(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF5_SHIFT)) & LCD_WF_WF5_MASK)

#define LCD_WF_WF9_MASK                          (0xFF00U)
#define LCD_WF_WF9_SHIFT                         (8U)
#define LCD_WF_WF9(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF9_SHIFT)) & LCD_WF_WF9_MASK)

#define LCD_WF_WF13_MASK                         (0xFF00U)
#define LCD_WF_WF13_SHIFT                        (8U)
#define LCD_WF_WF13(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF13_SHIFT)) & LCD_WF_WF13_MASK)

#define LCD_WF_WF17_MASK                         (0xFF00U)
#define LCD_WF_WF17_SHIFT                        (8U)
#define LCD_WF_WF17(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF17_SHIFT)) & LCD_WF_WF17_MASK)

#define LCD_WF_WF21_MASK                         (0xFF00U)
#define LCD_WF_WF21_SHIFT                        (8U)
#define LCD_WF_WF21(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF21_SHIFT)) & LCD_WF_WF21_MASK)

#define LCD_WF_WF25_MASK                         (0xFF00U)
#define LCD_WF_WF25_SHIFT                        (8U)
#define LCD_WF_WF25(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF25_SHIFT)) & LCD_WF_WF25_MASK)

#define LCD_WF_WF29_MASK                         (0xFF00U)
#define LCD_WF_WF29_SHIFT                        (8U)
#define LCD_WF_WF29(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF29_SHIFT)) & LCD_WF_WF29_MASK)

#define LCD_WF_WF33_MASK                         (0xFF00U)
#define LCD_WF_WF33_SHIFT                        (8U)
#define LCD_WF_WF33(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF33_SHIFT)) & LCD_WF_WF33_MASK)

#define LCD_WF_WF37_MASK                         (0xFF00U)
#define LCD_WF_WF37_SHIFT                        (8U)
#define LCD_WF_WF37(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF37_SHIFT)) & LCD_WF_WF37_MASK)

#define LCD_WF_WF41_MASK                         (0xFF00U)
#define LCD_WF_WF41_SHIFT                        (8U)
#define LCD_WF_WF41(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF41_SHIFT)) & LCD_WF_WF41_MASK)

#define LCD_WF_WF45_MASK                         (0xFF00U)
#define LCD_WF_WF45_SHIFT                        (8U)
#define LCD_WF_WF45(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF45_SHIFT)) & LCD_WF_WF45_MASK)

#define LCD_WF_WF49_MASK                         (0xFF00U)
#define LCD_WF_WF49_SHIFT                        (8U)
#define LCD_WF_WF49(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF49_SHIFT)) & LCD_WF_WF49_MASK)

#define LCD_WF_WF53_MASK                         (0xFF00U)
#define LCD_WF_WF53_SHIFT                        (8U)
#define LCD_WF_WF53(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF53_SHIFT)) & LCD_WF_WF53_MASK)

#define LCD_WF_WF57_MASK                         (0xFF00U)
#define LCD_WF_WF57_SHIFT                        (8U)
#define LCD_WF_WF57(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF57_SHIFT)) & LCD_WF_WF57_MASK)

#define LCD_WF_WF61_MASK                         (0xFF00U)
#define LCD_WF_WF61_SHIFT                        (8U)
#define LCD_WF_WF61(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF61_SHIFT)) & LCD_WF_WF61_MASK)

#define LCD_WF_WF2_MASK                          (0xFF0000U)
#define LCD_WF_WF2_SHIFT                         (16U)
#define LCD_WF_WF2(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF2_SHIFT)) & LCD_WF_WF2_MASK)

#define LCD_WF_WF6_MASK                          (0xFF0000U)
#define LCD_WF_WF6_SHIFT                         (16U)
#define LCD_WF_WF6(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF6_SHIFT)) & LCD_WF_WF6_MASK)

#define LCD_WF_WF10_MASK                         (0xFF0000U)
#define LCD_WF_WF10_SHIFT                        (16U)
#define LCD_WF_WF10(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF10_SHIFT)) & LCD_WF_WF10_MASK)

#define LCD_WF_WF14_MASK                         (0xFF0000U)
#define LCD_WF_WF14_SHIFT                        (16U)
#define LCD_WF_WF14(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF14_SHIFT)) & LCD_WF_WF14_MASK)

#define LCD_WF_WF18_MASK                         (0xFF0000U)
#define LCD_WF_WF18_SHIFT                        (16U)
#define LCD_WF_WF18(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF18_SHIFT)) & LCD_WF_WF18_MASK)

#define LCD_WF_WF22_MASK                         (0xFF0000U)
#define LCD_WF_WF22_SHIFT                        (16U)
#define LCD_WF_WF22(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF22_SHIFT)) & LCD_WF_WF22_MASK)

#define LCD_WF_WF26_MASK                         (0xFF0000U)
#define LCD_WF_WF26_SHIFT                        (16U)
#define LCD_WF_WF26(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF26_SHIFT)) & LCD_WF_WF26_MASK)

#define LCD_WF_WF30_MASK                         (0xFF0000U)
#define LCD_WF_WF30_SHIFT                        (16U)
#define LCD_WF_WF30(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF30_SHIFT)) & LCD_WF_WF30_MASK)

#define LCD_WF_WF34_MASK                         (0xFF0000U)
#define LCD_WF_WF34_SHIFT                        (16U)
#define LCD_WF_WF34(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF34_SHIFT)) & LCD_WF_WF34_MASK)

#define LCD_WF_WF38_MASK                         (0xFF0000U)
#define LCD_WF_WF38_SHIFT                        (16U)
#define LCD_WF_WF38(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF38_SHIFT)) & LCD_WF_WF38_MASK)

#define LCD_WF_WF42_MASK                         (0xFF0000U)
#define LCD_WF_WF42_SHIFT                        (16U)
#define LCD_WF_WF42(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF42_SHIFT)) & LCD_WF_WF42_MASK)

#define LCD_WF_WF46_MASK                         (0xFF0000U)
#define LCD_WF_WF46_SHIFT                        (16U)
#define LCD_WF_WF46(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF46_SHIFT)) & LCD_WF_WF46_MASK)

#define LCD_WF_WF50_MASK                         (0xFF0000U)
#define LCD_WF_WF50_SHIFT                        (16U)
#define LCD_WF_WF50(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF50_SHIFT)) & LCD_WF_WF50_MASK)

#define LCD_WF_WF54_MASK                         (0xFF0000U)
#define LCD_WF_WF54_SHIFT                        (16U)
#define LCD_WF_WF54(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF54_SHIFT)) & LCD_WF_WF54_MASK)

#define LCD_WF_WF58_MASK                         (0xFF0000U)
#define LCD_WF_WF58_SHIFT                        (16U)
#define LCD_WF_WF58(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF58_SHIFT)) & LCD_WF_WF58_MASK)

#define LCD_WF_WF62_MASK                         (0xFF0000U)
#define LCD_WF_WF62_SHIFT                        (16U)
#define LCD_WF_WF62(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF62_SHIFT)) & LCD_WF_WF62_MASK)

#define LCD_WF_WF3_MASK                          (0xFF000000U)
#define LCD_WF_WF3_SHIFT                         (24U)
#define LCD_WF_WF3(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF3_SHIFT)) & LCD_WF_WF3_MASK)

#define LCD_WF_WF7_MASK                          (0xFF000000U)
#define LCD_WF_WF7_SHIFT                         (24U)
#define LCD_WF_WF7(x)                            (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF7_SHIFT)) & LCD_WF_WF7_MASK)

#define LCD_WF_WF11_MASK                         (0xFF000000U)
#define LCD_WF_WF11_SHIFT                        (24U)
#define LCD_WF_WF11(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF11_SHIFT)) & LCD_WF_WF11_MASK)

#define LCD_WF_WF15_MASK                         (0xFF000000U)
#define LCD_WF_WF15_SHIFT                        (24U)
#define LCD_WF_WF15(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF15_SHIFT)) & LCD_WF_WF15_MASK)

#define LCD_WF_WF19_MASK                         (0xFF000000U)
#define LCD_WF_WF19_SHIFT                        (24U)
#define LCD_WF_WF19(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF19_SHIFT)) & LCD_WF_WF19_MASK)

#define LCD_WF_WF23_MASK                         (0xFF000000U)
#define LCD_WF_WF23_SHIFT                        (24U)
#define LCD_WF_WF23(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF23_SHIFT)) & LCD_WF_WF23_MASK)

#define LCD_WF_WF27_MASK                         (0xFF000000U)
#define LCD_WF_WF27_SHIFT                        (24U)
#define LCD_WF_WF27(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF27_SHIFT)) & LCD_WF_WF27_MASK)

#define LCD_WF_WF31_MASK                         (0xFF000000U)
#define LCD_WF_WF31_SHIFT                        (24U)
#define LCD_WF_WF31(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF31_SHIFT)) & LCD_WF_WF31_MASK)

#define LCD_WF_WF35_MASK                         (0xFF000000U)
#define LCD_WF_WF35_SHIFT                        (24U)
#define LCD_WF_WF35(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF35_SHIFT)) & LCD_WF_WF35_MASK)

#define LCD_WF_WF39_MASK                         (0xFF000000U)
#define LCD_WF_WF39_SHIFT                        (24U)
#define LCD_WF_WF39(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF39_SHIFT)) & LCD_WF_WF39_MASK)

#define LCD_WF_WF43_MASK                         (0xFF000000U)
#define LCD_WF_WF43_SHIFT                        (24U)
#define LCD_WF_WF43(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF43_SHIFT)) & LCD_WF_WF43_MASK)

#define LCD_WF_WF47_MASK                         (0xFF000000U)
#define LCD_WF_WF47_SHIFT                        (24U)
#define LCD_WF_WF47(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF47_SHIFT)) & LCD_WF_WF47_MASK)

#define LCD_WF_WF51_MASK                         (0xFF000000U)
#define LCD_WF_WF51_SHIFT                        (24U)
#define LCD_WF_WF51(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF51_SHIFT)) & LCD_WF_WF51_MASK)

#define LCD_WF_WF55_MASK                         (0xFF000000U)
#define LCD_WF_WF55_SHIFT                        (24U)
#define LCD_WF_WF55(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF55_SHIFT)) & LCD_WF_WF55_MASK)

#define LCD_WF_WF59_MASK                         (0xFF000000U)
#define LCD_WF_WF59_SHIFT                        (24U)
#define LCD_WF_WF59(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF59_SHIFT)) & LCD_WF_WF59_MASK)

#define LCD_WF_WF63_MASK                         (0xFF000000U)
#define LCD_WF_WF63_SHIFT                        (24U)
#define LCD_WF_WF63(x)                           (((uint32_t)(((uint32_t)(x)) << LCD_WF_WF63_SHIFT)) & LCD_WF_WF63_MASK)
/*! @} */

/* The count of LCD_WF */
#define LCD_WF_COUNT                             (16U)


/*!
 * @}
 */ /* end of group LCD_Register_Masks */


/* LCD - Peripheral instance base addresses */
/** Peripheral LCD base address */
#define LCD_BASE                                 (0x40053000u)
/** Peripheral LCD base pointer */
#define LCD                                      ((LCD_Type *)LCD_BASE)
/** Array initializer of LCD peripheral base addresses */
#define LCD_BASE_ADDRS                           { LCD_BASE }
/** Array initializer of LCD peripheral base pointers */
#define LCD_BASE_PTRS                            { LCD }
/** Interrupt vectors for the LCD peripheral type */
#define LCD_LCD_IRQS                             { LCD_IRQn }

/*!
 * @}
 */ /* end of group LCD_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- LLWU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Peripheral_Access_Layer LLWU Peripheral Access Layer
 * @{
 */

/** LLWU - Register Layout Typedef */
typedef struct {
  __IO uint8_t PE1;                                /**< LLWU Pin Enable 1 register, offset: 0x0 */
  __IO uint8_t PE2;                                /**< LLWU Pin Enable 2 register, offset: 0x1 */
  __IO uint8_t PE3;                                /**< LLWU Pin Enable 3 register, offset: 0x2 */
  __IO uint8_t PE4;                                /**< LLWU Pin Enable 4 register, offset: 0x3 */
  __IO uint8_t ME;                                 /**< LLWU Module Enable register, offset: 0x4 */
  __IO uint8_t F1;                                 /**< LLWU Flag 1 register, offset: 0x5 */
  __IO uint8_t F2;                                 /**< LLWU Flag 2 register, offset: 0x6 */
  __I  uint8_t F3;                                 /**< LLWU Flag 3 register, offset: 0x7 */
  __IO uint8_t FILT1;                              /**< LLWU Pin Filter 1 register, offset: 0x8 */
  __IO uint8_t FILT2;                              /**< LLWU Pin Filter 2 register, offset: 0x9 */
} LLWU_Type;

/* ----------------------------------------------------------------------------
   -- LLWU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Register_Masks LLWU Register Masks
 * @{
 */

/*! @name PE1 - LLWU Pin Enable 1 register */
/*! @{ */

#define LLWU_PE1_WUPE0_MASK                      (0x3U)
#define LLWU_PE1_WUPE0_SHIFT                     (0U)
/*! WUPE0 - Wakeup Pin Enable For LLWU_P0
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE0(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE1_WUPE0_SHIFT)) & LLWU_PE1_WUPE0_MASK)

#define LLWU_PE1_WUPE1_MASK                      (0xCU)
#define LLWU_PE1_WUPE1_SHIFT                     (2U)
/*! WUPE1 - Wakeup Pin Enable For LLWU_P1
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE1(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE1_WUPE1_SHIFT)) & LLWU_PE1_WUPE1_MASK)

#define LLWU_PE1_WUPE2_MASK                      (0x30U)
#define LLWU_PE1_WUPE2_SHIFT                     (4U)
/*! WUPE2 - Wakeup Pin Enable For LLWU_P2
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE2(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE1_WUPE2_SHIFT)) & LLWU_PE1_WUPE2_MASK)

#define LLWU_PE1_WUPE3_MASK                      (0xC0U)
#define LLWU_PE1_WUPE3_SHIFT                     (6U)
/*! WUPE3 - Wakeup Pin Enable For LLWU_P3
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE3(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE1_WUPE3_SHIFT)) & LLWU_PE1_WUPE3_MASK)
/*! @} */

/*! @name PE2 - LLWU Pin Enable 2 register */
/*! @{ */

#define LLWU_PE2_WUPE4_MASK                      (0x3U)
#define LLWU_PE2_WUPE4_SHIFT                     (0U)
/*! WUPE4 - Wakeup Pin Enable For LLWU_P4
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE4(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE2_WUPE4_SHIFT)) & LLWU_PE2_WUPE4_MASK)

#define LLWU_PE2_WUPE5_MASK                      (0xCU)
#define LLWU_PE2_WUPE5_SHIFT                     (2U)
/*! WUPE5 - Wakeup Pin Enable For LLWU_P5
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE5(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE2_WUPE5_SHIFT)) & LLWU_PE2_WUPE5_MASK)

#define LLWU_PE2_WUPE6_MASK                      (0x30U)
#define LLWU_PE2_WUPE6_SHIFT                     (4U)
/*! WUPE6 - Wakeup Pin Enable For LLWU_P6
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE6(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE2_WUPE6_SHIFT)) & LLWU_PE2_WUPE6_MASK)

#define LLWU_PE2_WUPE7_MASK                      (0xC0U)
#define LLWU_PE2_WUPE7_SHIFT                     (6U)
/*! WUPE7 - Wakeup Pin Enable For LLWU_P7
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE7(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE2_WUPE7_SHIFT)) & LLWU_PE2_WUPE7_MASK)
/*! @} */

/*! @name PE3 - LLWU Pin Enable 3 register */
/*! @{ */

#define LLWU_PE3_WUPE8_MASK                      (0x3U)
#define LLWU_PE3_WUPE8_SHIFT                     (0U)
/*! WUPE8 - Wakeup Pin Enable For LLWU_P8
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE3_WUPE8(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE3_WUPE8_SHIFT)) & LLWU_PE3_WUPE8_MASK)

#define LLWU_PE3_WUPE9_MASK                      (0xCU)
#define LLWU_PE3_WUPE9_SHIFT                     (2U)
/*! WUPE9 - Wakeup Pin Enable For LLWU_P9
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE3_WUPE9(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE3_WUPE9_SHIFT)) & LLWU_PE3_WUPE9_MASK)

#define LLWU_PE3_WUPE10_MASK                     (0x30U)
#define LLWU_PE3_WUPE10_SHIFT                    (4U)
/*! WUPE10 - Wakeup Pin Enable For LLWU_P10
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE3_WUPE10(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE3_WUPE10_SHIFT)) & LLWU_PE3_WUPE10_MASK)

#define LLWU_PE3_WUPE11_MASK                     (0xC0U)
#define LLWU_PE3_WUPE11_SHIFT                    (6U)
/*! WUPE11 - Wakeup Pin Enable For LLWU_P11
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE3_WUPE11(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE3_WUPE11_SHIFT)) & LLWU_PE3_WUPE11_MASK)
/*! @} */

/*! @name PE4 - LLWU Pin Enable 4 register */
/*! @{ */

#define LLWU_PE4_WUPE12_MASK                     (0x3U)
#define LLWU_PE4_WUPE12_SHIFT                    (0U)
/*! WUPE12 - Wakeup Pin Enable For LLWU_P12
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE4_WUPE12(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE4_WUPE12_SHIFT)) & LLWU_PE4_WUPE12_MASK)

#define LLWU_PE4_WUPE13_MASK                     (0xCU)
#define LLWU_PE4_WUPE13_SHIFT                    (2U)
/*! WUPE13 - Wakeup Pin Enable For LLWU_P13
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE4_WUPE13(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE4_WUPE13_SHIFT)) & LLWU_PE4_WUPE13_MASK)

#define LLWU_PE4_WUPE14_MASK                     (0x30U)
#define LLWU_PE4_WUPE14_SHIFT                    (4U)
/*! WUPE14 - Wakeup Pin Enable For LLWU_P14
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE4_WUPE14(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE4_WUPE14_SHIFT)) & LLWU_PE4_WUPE14_MASK)

#define LLWU_PE4_WUPE15_MASK                     (0xC0U)
#define LLWU_PE4_WUPE15_SHIFT                    (6U)
/*! WUPE15 - Wakeup Pin Enable For LLWU_P15
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE4_WUPE15(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE4_WUPE15_SHIFT)) & LLWU_PE4_WUPE15_MASK)
/*! @} */

/*! @name ME - LLWU Module Enable register */
/*! @{ */

#define LLWU_ME_WUME0_MASK                       (0x1U)
#define LLWU_ME_WUME0_SHIFT                      (0U)
/*! WUME0 - Wakeup Module Enable For Module 0
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME0(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME0_SHIFT)) & LLWU_ME_WUME0_MASK)

#define LLWU_ME_WUME1_MASK                       (0x2U)
#define LLWU_ME_WUME1_SHIFT                      (1U)
/*! WUME1 - Wakeup Module Enable for Module 1
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME1(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME1_SHIFT)) & LLWU_ME_WUME1_MASK)

#define LLWU_ME_WUME2_MASK                       (0x4U)
#define LLWU_ME_WUME2_SHIFT                      (2U)
/*! WUME2 - Wakeup Module Enable For Module 2
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME2(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME2_SHIFT)) & LLWU_ME_WUME2_MASK)

#define LLWU_ME_WUME3_MASK                       (0x8U)
#define LLWU_ME_WUME3_SHIFT                      (3U)
/*! WUME3 - Wakeup Module Enable For Module 3
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME3(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME3_SHIFT)) & LLWU_ME_WUME3_MASK)

#define LLWU_ME_WUME4_MASK                       (0x10U)
#define LLWU_ME_WUME4_SHIFT                      (4U)
/*! WUME4 - Wakeup Module Enable For Module 4
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME4(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME4_SHIFT)) & LLWU_ME_WUME4_MASK)

#define LLWU_ME_WUME5_MASK                       (0x20U)
#define LLWU_ME_WUME5_SHIFT                      (5U)
/*! WUME5 - Wakeup Module Enable For Module 5
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME5(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME5_SHIFT)) & LLWU_ME_WUME5_MASK)

#define LLWU_ME_WUME6_MASK                       (0x40U)
#define LLWU_ME_WUME6_SHIFT                      (6U)
/*! WUME6 - Wakeup Module Enable For Module 6
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME6(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME6_SHIFT)) & LLWU_ME_WUME6_MASK)

#define LLWU_ME_WUME7_MASK                       (0x80U)
#define LLWU_ME_WUME7_SHIFT                      (7U)
/*! WUME7 - Wakeup Module Enable For Module 7
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME7(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME7_SHIFT)) & LLWU_ME_WUME7_MASK)
/*! @} */

/*! @name F1 - LLWU Flag 1 register */
/*! @{ */

#define LLWU_F1_WUF0_MASK                        (0x1U)
#define LLWU_F1_WUF0_SHIFT                       (0U)
/*! WUF0 - Wakeup Flag For LLWU_P0
 *  0b0..LLWU_P0 input was not a wakeup source
 *  0b1..LLWU_P0 input was a wakeup source
 */
#define LLWU_F1_WUF0(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF0_SHIFT)) & LLWU_F1_WUF0_MASK)

#define LLWU_F1_WUF1_MASK                        (0x2U)
#define LLWU_F1_WUF1_SHIFT                       (1U)
/*! WUF1 - Wakeup Flag For LLWU_P1
 *  0b0..LLWU_P1 input was not a wakeup source
 *  0b1..LLWU_P1 input was a wakeup source
 */
#define LLWU_F1_WUF1(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF1_SHIFT)) & LLWU_F1_WUF1_MASK)

#define LLWU_F1_WUF2_MASK                        (0x4U)
#define LLWU_F1_WUF2_SHIFT                       (2U)
/*! WUF2 - Wakeup Flag For LLWU_P2
 *  0b0..LLWU_P2 input was not a wakeup source
 *  0b1..LLWU_P2 input was a wakeup source
 */
#define LLWU_F1_WUF2(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF2_SHIFT)) & LLWU_F1_WUF2_MASK)

#define LLWU_F1_WUF3_MASK                        (0x8U)
#define LLWU_F1_WUF3_SHIFT                       (3U)
/*! WUF3 - Wakeup Flag For LLWU_P3
 *  0b0..LLWU_P3 input was not a wake-up source
 *  0b1..LLWU_P3 input was a wake-up source
 */
#define LLWU_F1_WUF3(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF3_SHIFT)) & LLWU_F1_WUF3_MASK)

#define LLWU_F1_WUF4_MASK                        (0x10U)
#define LLWU_F1_WUF4_SHIFT                       (4U)
/*! WUF4 - Wakeup Flag For LLWU_P4
 *  0b0..LLWU_P4 input was not a wakeup source
 *  0b1..LLWU_P4 input was a wakeup source
 */
#define LLWU_F1_WUF4(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF4_SHIFT)) & LLWU_F1_WUF4_MASK)

#define LLWU_F1_WUF5_MASK                        (0x20U)
#define LLWU_F1_WUF5_SHIFT                       (5U)
/*! WUF5 - Wakeup Flag For LLWU_P5
 *  0b0..LLWU_P5 input was not a wakeup source
 *  0b1..LLWU_P5 input was a wakeup source
 */
#define LLWU_F1_WUF5(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF5_SHIFT)) & LLWU_F1_WUF5_MASK)

#define LLWU_F1_WUF6_MASK                        (0x40U)
#define LLWU_F1_WUF6_SHIFT                       (6U)
/*! WUF6 - Wakeup Flag For LLWU_P6
 *  0b0..LLWU_P6 input was not a wakeup source
 *  0b1..LLWU_P6 input was a wakeup source
 */
#define LLWU_F1_WUF6(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF6_SHIFT)) & LLWU_F1_WUF6_MASK)

#define LLWU_F1_WUF7_MASK                        (0x80U)
#define LLWU_F1_WUF7_SHIFT                       (7U)
/*! WUF7 - Wakeup Flag For LLWU_P7
 *  0b0..LLWU_P7 input was not a wakeup source
 *  0b1..LLWU_P7 input was a wakeup source
 */
#define LLWU_F1_WUF7(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF7_SHIFT)) & LLWU_F1_WUF7_MASK)
/*! @} */

/*! @name F2 - LLWU Flag 2 register */
/*! @{ */

#define LLWU_F2_WUF8_MASK                        (0x1U)
#define LLWU_F2_WUF8_SHIFT                       (0U)
/*! WUF8 - Wakeup Flag For LLWU_P8
 *  0b0..LLWU_P8 input was not a wakeup source
 *  0b1..LLWU_P8 input was a wakeup source
 */
#define LLWU_F2_WUF8(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF8_SHIFT)) & LLWU_F2_WUF8_MASK)

#define LLWU_F2_WUF9_MASK                        (0x2U)
#define LLWU_F2_WUF9_SHIFT                       (1U)
/*! WUF9 - Wakeup Flag For LLWU_P9
 *  0b0..LLWU_P9 input was not a wakeup source
 *  0b1..LLWU_P9 input was a wakeup source
 */
#define LLWU_F2_WUF9(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF9_SHIFT)) & LLWU_F2_WUF9_MASK)

#define LLWU_F2_WUF10_MASK                       (0x4U)
#define LLWU_F2_WUF10_SHIFT                      (2U)
/*! WUF10 - Wakeup Flag For LLWU_P10
 *  0b0..LLWU_P10 input was not a wakeup source
 *  0b1..LLWU_P10 input was a wakeup source
 */
#define LLWU_F2_WUF10(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF10_SHIFT)) & LLWU_F2_WUF10_MASK)

#define LLWU_F2_WUF11_MASK                       (0x8U)
#define LLWU_F2_WUF11_SHIFT                      (3U)
/*! WUF11 - Wakeup Flag For LLWU_P11
 *  0b0..LLWU_P11 input was not a wakeup source
 *  0b1..LLWU_P11 input was a wakeup source
 */
#define LLWU_F2_WUF11(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF11_SHIFT)) & LLWU_F2_WUF11_MASK)

#define LLWU_F2_WUF12_MASK                       (0x10U)
#define LLWU_F2_WUF12_SHIFT                      (4U)
/*! WUF12 - Wakeup Flag For LLWU_P12
 *  0b0..LLWU_P12 input was not a wakeup source
 *  0b1..LLWU_P12 input was a wakeup source
 */
#define LLWU_F2_WUF12(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF12_SHIFT)) & LLWU_F2_WUF12_MASK)

#define LLWU_F2_WUF13_MASK                       (0x20U)
#define LLWU_F2_WUF13_SHIFT                      (5U)
/*! WUF13 - Wakeup Flag For LLWU_P13
 *  0b0..LLWU_P13 input was not a wakeup source
 *  0b1..LLWU_P13 input was a wakeup source
 */
#define LLWU_F2_WUF13(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF13_SHIFT)) & LLWU_F2_WUF13_MASK)

#define LLWU_F2_WUF14_MASK                       (0x40U)
#define LLWU_F2_WUF14_SHIFT                      (6U)
/*! WUF14 - Wakeup Flag For LLWU_P14
 *  0b0..LLWU_P14 input was not a wakeup source
 *  0b1..LLWU_P14 input was a wakeup source
 */
#define LLWU_F2_WUF14(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF14_SHIFT)) & LLWU_F2_WUF14_MASK)

#define LLWU_F2_WUF15_MASK                       (0x80U)
#define LLWU_F2_WUF15_SHIFT                      (7U)
/*! WUF15 - Wakeup Flag For LLWU_P15
 *  0b0..LLWU_P15 input was not a wakeup source
 *  0b1..LLWU_P15 input was a wakeup source
 */
#define LLWU_F2_WUF15(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF15_SHIFT)) & LLWU_F2_WUF15_MASK)
/*! @} */

/*! @name F3 - LLWU Flag 3 register */
/*! @{ */

#define LLWU_F3_MWUF0_MASK                       (0x1U)
#define LLWU_F3_MWUF0_SHIFT                      (0U)
/*! MWUF0 - Wakeup flag For module 0
 *  0b0..Module 0 input was not a wakeup source
 *  0b1..Module 0 input was a wakeup source
 */
#define LLWU_F3_MWUF0(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF0_SHIFT)) & LLWU_F3_MWUF0_MASK)

#define LLWU_F3_MWUF1_MASK                       (0x2U)
#define LLWU_F3_MWUF1_SHIFT                      (1U)
/*! MWUF1 - Wakeup flag For module 1
 *  0b0..Module 1 input was not a wakeup source
 *  0b1..Module 1 input was a wakeup source
 */
#define LLWU_F3_MWUF1(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF1_SHIFT)) & LLWU_F3_MWUF1_MASK)

#define LLWU_F3_MWUF2_MASK                       (0x4U)
#define LLWU_F3_MWUF2_SHIFT                      (2U)
/*! MWUF2 - Wakeup flag For module 2
 *  0b0..Module 2 input was not a wakeup source
 *  0b1..Module 2 input was a wakeup source
 */
#define LLWU_F3_MWUF2(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF2_SHIFT)) & LLWU_F3_MWUF2_MASK)

#define LLWU_F3_MWUF3_MASK                       (0x8U)
#define LLWU_F3_MWUF3_SHIFT                      (3U)
/*! MWUF3 - Wakeup flag For module 3
 *  0b0..Module 3 input was not a wakeup source
 *  0b1..Module 3 input was a wakeup source
 */
#define LLWU_F3_MWUF3(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF3_SHIFT)) & LLWU_F3_MWUF3_MASK)

#define LLWU_F3_MWUF4_MASK                       (0x10U)
#define LLWU_F3_MWUF4_SHIFT                      (4U)
/*! MWUF4 - Wakeup flag For module 4
 *  0b0..Module 4 input was not a wakeup source
 *  0b1..Module 4 input was a wakeup source
 */
#define LLWU_F3_MWUF4(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF4_SHIFT)) & LLWU_F3_MWUF4_MASK)

#define LLWU_F3_MWUF5_MASK                       (0x20U)
#define LLWU_F3_MWUF5_SHIFT                      (5U)
/*! MWUF5 - Wakeup flag For module 5
 *  0b0..Module 5 input was not a wakeup source
 *  0b1..Module 5 input was a wakeup source
 */
#define LLWU_F3_MWUF5(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF5_SHIFT)) & LLWU_F3_MWUF5_MASK)

#define LLWU_F3_MWUF6_MASK                       (0x40U)
#define LLWU_F3_MWUF6_SHIFT                      (6U)
/*! MWUF6 - Wakeup flag For module 6
 *  0b0..Module 6 input was not a wakeup source
 *  0b1..Module 6 input was a wakeup source
 */
#define LLWU_F3_MWUF6(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF6_SHIFT)) & LLWU_F3_MWUF6_MASK)

#define LLWU_F3_MWUF7_MASK                       (0x80U)
#define LLWU_F3_MWUF7_SHIFT                      (7U)
/*! MWUF7 - Wakeup flag For module 7
 *  0b0..Module 7 input was not a wakeup source
 *  0b1..Module 7 input was a wakeup source
 */
#define LLWU_F3_MWUF7(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF7_SHIFT)) & LLWU_F3_MWUF7_MASK)
/*! @} */

/*! @name FILT1 - LLWU Pin Filter 1 register */
/*! @{ */

#define LLWU_FILT1_FILTSEL_MASK                  (0xFU)
#define LLWU_FILT1_FILTSEL_SHIFT                 (0U)
/*! FILTSEL - Filter Pin Select
 *  0b0000..Select LLWU_P0 for filter
 *  0b1111..Select LLWU_P15 for filter
 */
#define LLWU_FILT1_FILTSEL(x)                    (((uint8_t)(((uint8_t)(x)) << LLWU_FILT1_FILTSEL_SHIFT)) & LLWU_FILT1_FILTSEL_MASK)

#define LLWU_FILT1_FILTE_MASK                    (0x60U)
#define LLWU_FILT1_FILTE_SHIFT                   (5U)
/*! FILTE - Digital Filter On External Pin
 *  0b00..Filter disabled
 *  0b01..Filter posedge detect enabled
 *  0b10..Filter negedge detect enabled
 *  0b11..Filter any edge detect enabled
 */
#define LLWU_FILT1_FILTE(x)                      (((uint8_t)(((uint8_t)(x)) << LLWU_FILT1_FILTE_SHIFT)) & LLWU_FILT1_FILTE_MASK)

#define LLWU_FILT1_FILTF_MASK                    (0x80U)
#define LLWU_FILT1_FILTF_SHIFT                   (7U)
/*! FILTF - Filter Detect Flag
 *  0b0..Pin Filter 1 was not a wakeup source
 *  0b1..Pin Filter 1 was a wakeup source
 */
#define LLWU_FILT1_FILTF(x)                      (((uint8_t)(((uint8_t)(x)) << LLWU_FILT1_FILTF_SHIFT)) & LLWU_FILT1_FILTF_MASK)
/*! @} */

/*! @name FILT2 - LLWU Pin Filter 2 register */
/*! @{ */

#define LLWU_FILT2_FILTSEL_MASK                  (0xFU)
#define LLWU_FILT2_FILTSEL_SHIFT                 (0U)
/*! FILTSEL - Filter Pin Select
 *  0b0000..Select LLWU_P0 for filter
 *  0b1111..Select LLWU_P15 for filter
 */
#define LLWU_FILT2_FILTSEL(x)                    (((uint8_t)(((uint8_t)(x)) << LLWU_FILT2_FILTSEL_SHIFT)) & LLWU_FILT2_FILTSEL_MASK)

#define LLWU_FILT2_FILTE_MASK                    (0x60U)
#define LLWU_FILT2_FILTE_SHIFT                   (5U)
/*! FILTE - Digital Filter On External Pin
 *  0b00..Filter disabled
 *  0b01..Filter posedge detect enabled
 *  0b10..Filter negedge detect enabled
 *  0b11..Filter any edge detect enabled
 */
#define LLWU_FILT2_FILTE(x)                      (((uint8_t)(((uint8_t)(x)) << LLWU_FILT2_FILTE_SHIFT)) & LLWU_FILT2_FILTE_MASK)

#define LLWU_FILT2_FILTF_MASK                    (0x80U)
#define LLWU_FILT2_FILTF_SHIFT                   (7U)
/*! FILTF - Filter Detect Flag
 *  0b0..Pin Filter 2 was not a wakeup source
 *  0b1..Pin Filter 2 was a wakeup source
 */
#define LLWU_FILT2_FILTF(x)                      (((uint8_t)(((uint8_t)(x)) << LLWU_FILT2_FILTF_SHIFT)) & LLWU_FILT2_FILTF_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group LLWU_Register_Masks */


/* LLWU - Peripheral instance base addresses */
/** Peripheral LLWU base address */
#define LLWU_BASE                                (0x4007C000u)
/** Peripheral LLWU base pointer */
#define LLWU                                     ((LLWU_Type *)LLWU_BASE)
/** Array initializer of LLWU peripheral base addresses */
#define LLWU_BASE_ADDRS                          { LLWU_BASE }
/** Array initializer of LLWU peripheral base pointers */
#define LLWU_BASE_PTRS                           { LLWU }
/** Interrupt vectors for the LLWU peripheral type */
#define LLWU_IRQS                                { LLWU_IRQn }

/*!
 * @}
 */ /* end of group LLWU_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- LPTMR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Peripheral_Access_Layer LPTMR Peripheral Access Layer
 * @{
 */

/** LPTMR - Register Layout Typedef */
typedef struct {
  __IO uint32_t CSR;                               /**< Low Power Timer Control Status Register, offset: 0x0 */
  __IO uint32_t PSR;                               /**< Low Power Timer Prescale Register, offset: 0x4 */
  __IO uint32_t CMR;                               /**< Low Power Timer Compare Register, offset: 0x8 */
  __IO uint32_t CNR;                               /**< Low Power Timer Counter Register, offset: 0xC */
} LPTMR_Type;

/* ----------------------------------------------------------------------------
   -- LPTMR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Register_Masks LPTMR Register Masks
 * @{
 */

/*! @name CSR - Low Power Timer Control Status Register */
/*! @{ */

#define LPTMR_CSR_TEN_MASK                       (0x1U)
#define LPTMR_CSR_TEN_SHIFT                      (0U)
/*! TEN - Timer Enable
 *  0b0..LPTMR is disabled and internal logic is reset.
 *  0b1..LPTMR is enabled.
 */
#define LPTMR_CSR_TEN(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TEN_SHIFT)) & LPTMR_CSR_TEN_MASK)

#define LPTMR_CSR_TMS_MASK                       (0x2U)
#define LPTMR_CSR_TMS_SHIFT                      (1U)
/*! TMS - Timer Mode Select
 *  0b0..Time Counter mode.
 *  0b1..Pulse Counter mode.
 */
#define LPTMR_CSR_TMS(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TMS_SHIFT)) & LPTMR_CSR_TMS_MASK)

#define LPTMR_CSR_TFC_MASK                       (0x4U)
#define LPTMR_CSR_TFC_SHIFT                      (2U)
/*! TFC - Timer Free-Running Counter
 *  0b0..CNR is reset whenever TCF is set.
 *  0b1..CNR is reset on overflow.
 */
#define LPTMR_CSR_TFC(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TFC_SHIFT)) & LPTMR_CSR_TFC_MASK)

#define LPTMR_CSR_TPP_MASK                       (0x8U)
#define LPTMR_CSR_TPP_SHIFT                      (3U)
/*! TPP - Timer Pin Polarity
 *  0b0..Pulse Counter input source is active-high, and the CNR will increment on the rising-edge.
 *  0b1..Pulse Counter input source is active-low, and the CNR will increment on the falling-edge.
 */
#define LPTMR_CSR_TPP(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TPP_SHIFT)) & LPTMR_CSR_TPP_MASK)

#define LPTMR_CSR_TPS_MASK                       (0x30U)
#define LPTMR_CSR_TPS_SHIFT                      (4U)
/*! TPS - Timer Pin Select
 *  0b00..Pulse counter input 0 is selected.
 *  0b01..Pulse counter input 1 is selected.
 *  0b10..Pulse counter input 2 is selected.
 *  0b11..Pulse counter input 3 is selected.
 */
#define LPTMR_CSR_TPS(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TPS_SHIFT)) & LPTMR_CSR_TPS_MASK)

#define LPTMR_CSR_TIE_MASK                       (0x40U)
#define LPTMR_CSR_TIE_SHIFT                      (6U)
/*! TIE - Timer Interrupt Enable
 *  0b0..Timer interrupt disabled.
 *  0b1..Timer interrupt enabled.
 */
#define LPTMR_CSR_TIE(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TIE_SHIFT)) & LPTMR_CSR_TIE_MASK)

#define LPTMR_CSR_TCF_MASK                       (0x80U)
#define LPTMR_CSR_TCF_SHIFT                      (7U)
/*! TCF - Timer Compare Flag
 *  0b0..The value of CNR is not equal to CMR and increments.
 *  0b1..The value of CNR is equal to CMR and increments.
 */
#define LPTMR_CSR_TCF(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TCF_SHIFT)) & LPTMR_CSR_TCF_MASK)
/*! @} */

/*! @name PSR - Low Power Timer Prescale Register */
/*! @{ */

#define LPTMR_PSR_PCS_MASK                       (0x3U)
#define LPTMR_PSR_PCS_SHIFT                      (0U)
/*! PCS - Prescaler Clock Select
 *  0b00..Prescaler/glitch filter clock 0 selected.
 *  0b01..Prescaler/glitch filter clock 1 selected.
 *  0b10..Prescaler/glitch filter clock 2 selected.
 *  0b11..Prescaler/glitch filter clock 3 selected.
 */
#define LPTMR_PSR_PCS(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_PSR_PCS_SHIFT)) & LPTMR_PSR_PCS_MASK)

#define LPTMR_PSR_PBYP_MASK                      (0x4U)
#define LPTMR_PSR_PBYP_SHIFT                     (2U)
/*! PBYP - Prescaler Bypass
 *  0b0..Prescaler/glitch filter is enabled.
 *  0b1..Prescaler/glitch filter is bypassed.
 */
#define LPTMR_PSR_PBYP(x)                        (((uint32_t)(((uint32_t)(x)) << LPTMR_PSR_PBYP_SHIFT)) & LPTMR_PSR_PBYP_MASK)

#define LPTMR_PSR_PRESCALE_MASK                  (0x78U)
#define LPTMR_PSR_PRESCALE_SHIFT                 (3U)
/*! PRESCALE - Prescale Value
 *  0b0000..Prescaler divides the prescaler clock by 2; glitch filter does not support this configuration.
 *  0b0001..Prescaler divides the prescaler clock by 4; glitch filter recognizes change on input pin after 2 rising clock edges.
 *  0b0010..Prescaler divides the prescaler clock by 8; glitch filter recognizes change on input pin after 4 rising clock edges.
 *  0b0011..Prescaler divides the prescaler clock by 16; glitch filter recognizes change on input pin after 8 rising clock edges.
 *  0b0100..Prescaler divides the prescaler clock by 32; glitch filter recognizes change on input pin after 16 rising clock edges.
 *  0b0101..Prescaler divides the prescaler clock by 64; glitch filter recognizes change on input pin after 32 rising clock edges.
 *  0b0110..Prescaler divides the prescaler clock by 128; glitch filter recognizes change on input pin after 64 rising clock edges.
 *  0b0111..Prescaler divides the prescaler clock by 256; glitch filter recognizes change on input pin after 128 rising clock edges.
 *  0b1000..Prescaler divides the prescaler clock by 512; glitch filter recognizes change on input pin after 256 rising clock edges.
 *  0b1001..Prescaler divides the prescaler clock by 1024; glitch filter recognizes change on input pin after 512 rising clock edges.
 *  0b1010..Prescaler divides the prescaler clock by 2048; glitch filter recognizes change on input pin after 1024 rising clock edges.
 *  0b1011..Prescaler divides the prescaler clock by 4096; glitch filter recognizes change on input pin after 2048 rising clock edges.
 *  0b1100..Prescaler divides the prescaler clock by 8192; glitch filter recognizes change on input pin after 4096 rising clock edges.
 *  0b1101..Prescaler divides the prescaler clock by 16,384; glitch filter recognizes change on input pin after 8192 rising clock edges.
 *  0b1110..Prescaler divides the prescaler clock by 32,768; glitch filter recognizes change on input pin after 16,384 rising clock edges.
 *  0b1111..Prescaler divides the prescaler clock by 65,536; glitch filter recognizes change on input pin after 32,768 rising clock edges.
 */
#define LPTMR_PSR_PRESCALE(x)                    (((uint32_t)(((uint32_t)(x)) << LPTMR_PSR_PRESCALE_SHIFT)) & LPTMR_PSR_PRESCALE_MASK)
/*! @} */

/*! @name CMR - Low Power Timer Compare Register */
/*! @{ */

#define LPTMR_CMR_COMPARE_MASK                   (0xFFFFU)
#define LPTMR_CMR_COMPARE_SHIFT                  (0U)
/*! COMPARE - Compare Value */
#define LPTMR_CMR_COMPARE(x)                     (((uint32_t)(((uint32_t)(x)) << LPTMR_CMR_COMPARE_SHIFT)) & LPTMR_CMR_COMPARE_MASK)
/*! @} */

/*! @name CNR - Low Power Timer Counter Register */
/*! @{ */

#define LPTMR_CNR_COUNTER_MASK                   (0xFFFFU)
#define LPTMR_CNR_COUNTER_SHIFT                  (0U)
/*! COUNTER - Counter Value */
#define LPTMR_CNR_COUNTER(x)                     (((uint32_t)(((uint32_t)(x)) << LPTMR_CNR_COUNTER_SHIFT)) & LPTMR_CNR_COUNTER_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group LPTMR_Register_Masks */


/* LPTMR - Peripheral instance base addresses */
/** Peripheral LPTMR0 base address */
#define LPTMR0_BASE                              (0x40040000u)
/** Peripheral LPTMR0 base pointer */
#define LPTMR0                                   ((LPTMR_Type *)LPTMR0_BASE)
/** Array initializer of LPTMR peripheral base addresses */
#define LPTMR_BASE_ADDRS                         { LPTMR0_BASE }
/** Array initializer of LPTMR peripheral base pointers */
#define LPTMR_BASE_PTRS                          { LPTMR0 }
/** Interrupt vectors for the LPTMR peripheral type */
#define LPTMR_IRQS                               { LPTMR0_IRQn }

/*!
 * @}
 */ /* end of group LPTMR_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- LPUART Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPUART_Peripheral_Access_Layer LPUART Peripheral Access Layer
 * @{
 */

/** LPUART - Register Layout Typedef */
typedef struct {
  __IO uint32_t BAUD;                              /**< LPUART Baud Rate Register, offset: 0x0 */
  __IO uint32_t STAT;                              /**< LPUART Status Register, offset: 0x4 */
  __IO uint32_t CTRL;                              /**< LPUART Control Register, offset: 0x8 */
  __IO uint32_t DATA;                              /**< LPUART Data Register, offset: 0xC */
  __IO uint32_t MATCH;                             /**< LPUART Match Address Register, offset: 0x10 */
} LPUART_Type;

/* ----------------------------------------------------------------------------
   -- LPUART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPUART_Register_Masks LPUART Register Masks
 * @{
 */

/*! @name BAUD - LPUART Baud Rate Register */
/*! @{ */

#define LPUART_BAUD_SBR_MASK                     (0x1FFFU)
#define LPUART_BAUD_SBR_SHIFT                    (0U)
/*! SBR - Baud Rate Modulo Divisor. */
#define LPUART_BAUD_SBR(x)                       (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_SBR_SHIFT)) & LPUART_BAUD_SBR_MASK)

#define LPUART_BAUD_SBNS_MASK                    (0x2000U)
#define LPUART_BAUD_SBNS_SHIFT                   (13U)
/*! SBNS - Stop Bit Number Select
 *  0b0..One stop bit.
 *  0b1..Two stop bits.
 */
#define LPUART_BAUD_SBNS(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_SBNS_SHIFT)) & LPUART_BAUD_SBNS_MASK)

#define LPUART_BAUD_RXEDGIE_MASK                 (0x4000U)
#define LPUART_BAUD_RXEDGIE_SHIFT                (14U)
/*! RXEDGIE - RX Input Active Edge Interrupt Enable
 *  0b0..Hardware interrupts from LPUART_STAT[RXEDGIF] disabled (use polling).
 *  0b1..Hardware interrupt requested when LPUART_STAT[RXEDGIF] flag is 1.
 */
#define LPUART_BAUD_RXEDGIE(x)                   (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_RXEDGIE_SHIFT)) & LPUART_BAUD_RXEDGIE_MASK)

#define LPUART_BAUD_LBKDIE_MASK                  (0x8000U)
#define LPUART_BAUD_LBKDIE_SHIFT                 (15U)
/*! LBKDIE - LIN Break Detect Interrupt Enable
 *  0b0..Hardware interrupts from LPUART_STAT[LBKDIF] disabled (use polling).
 *  0b1..Hardware interrupt requested when LPUART_STAT[LBKDIF] flag is 1.
 */
#define LPUART_BAUD_LBKDIE(x)                    (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_LBKDIE_SHIFT)) & LPUART_BAUD_LBKDIE_MASK)

#define LPUART_BAUD_RESYNCDIS_MASK               (0x10000U)
#define LPUART_BAUD_RESYNCDIS_SHIFT              (16U)
/*! RESYNCDIS - Resynchronization Disable
 *  0b0..Resynchronization during received data word is supported
 *  0b1..Resynchronization during received data word is disabled
 */
#define LPUART_BAUD_RESYNCDIS(x)                 (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_RESYNCDIS_SHIFT)) & LPUART_BAUD_RESYNCDIS_MASK)

#define LPUART_BAUD_BOTHEDGE_MASK                (0x20000U)
#define LPUART_BAUD_BOTHEDGE_SHIFT               (17U)
/*! BOTHEDGE - Both Edge Sampling
 *  0b0..Receiver samples input data using the rising edge of the baud rate clock.
 *  0b1..Receiver samples input data using the rising and falling edge of the baud rate clock.
 */
#define LPUART_BAUD_BOTHEDGE(x)                  (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_BOTHEDGE_SHIFT)) & LPUART_BAUD_BOTHEDGE_MASK)

#define LPUART_BAUD_MATCFG_MASK                  (0xC0000U)
#define LPUART_BAUD_MATCFG_SHIFT                 (18U)
/*! MATCFG - Match Configuration
 *  0b00..Address Match Wakeup
 *  0b01..Idle Match Wakeup
 *  0b10..Match On and Match Off
 *  0b11..Enables RWU on Data Match and Match On/Off for transmitter CTS input
 */
#define LPUART_BAUD_MATCFG(x)                    (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_MATCFG_SHIFT)) & LPUART_BAUD_MATCFG_MASK)

#define LPUART_BAUD_RDMAE_MASK                   (0x200000U)
#define LPUART_BAUD_RDMAE_SHIFT                  (21U)
/*! RDMAE - Receiver Full DMA Enable
 *  0b0..DMA request disabled.
 *  0b1..DMA request enabled.
 */
#define LPUART_BAUD_RDMAE(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_RDMAE_SHIFT)) & LPUART_BAUD_RDMAE_MASK)

#define LPUART_BAUD_TDMAE_MASK                   (0x800000U)
#define LPUART_BAUD_TDMAE_SHIFT                  (23U)
/*! TDMAE - Transmitter DMA Enable
 *  0b0..DMA request disabled.
 *  0b1..DMA request enabled.
 */
#define LPUART_BAUD_TDMAE(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_TDMAE_SHIFT)) & LPUART_BAUD_TDMAE_MASK)

#define LPUART_BAUD_OSR_MASK                     (0x1F000000U)
#define LPUART_BAUD_OSR_SHIFT                    (24U)
/*! OSR - Over Sampling Ratio */
#define LPUART_BAUD_OSR(x)                       (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_OSR_SHIFT)) & LPUART_BAUD_OSR_MASK)

#define LPUART_BAUD_M10_MASK                     (0x20000000U)
#define LPUART_BAUD_M10_SHIFT                    (29U)
/*! M10 - 10-bit Mode select
 *  0b0..Receiver and transmitter use 8-bit or 9-bit data characters.
 *  0b1..Receiver and transmitter use 10-bit data characters.
 */
#define LPUART_BAUD_M10(x)                       (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_M10_SHIFT)) & LPUART_BAUD_M10_MASK)

#define LPUART_BAUD_MAEN2_MASK                   (0x40000000U)
#define LPUART_BAUD_MAEN2_SHIFT                  (30U)
/*! MAEN2 - Match Address Mode Enable 2
 *  0b0..Normal operation.
 *  0b1..Enables automatic address matching or data matching mode for MATCH[MA2].
 */
#define LPUART_BAUD_MAEN2(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_MAEN2_SHIFT)) & LPUART_BAUD_MAEN2_MASK)

#define LPUART_BAUD_MAEN1_MASK                   (0x80000000U)
#define LPUART_BAUD_MAEN1_SHIFT                  (31U)
/*! MAEN1 - Match Address Mode Enable 1
 *  0b0..Normal operation.
 *  0b1..Enables automatic address matching or data matching mode for MATCH[MA1].
 */
#define LPUART_BAUD_MAEN1(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_MAEN1_SHIFT)) & LPUART_BAUD_MAEN1_MASK)
/*! @} */

/*! @name STAT - LPUART Status Register */
/*! @{ */

#define LPUART_STAT_MA2F_MASK                    (0x4000U)
#define LPUART_STAT_MA2F_SHIFT                   (14U)
/*! MA2F - Match 2 Flag
 *  0b0..Received data is not equal to MA2
 *  0b1..Received data is equal to MA2
 */
#define LPUART_STAT_MA2F(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_MA2F_SHIFT)) & LPUART_STAT_MA2F_MASK)

#define LPUART_STAT_MA1F_MASK                    (0x8000U)
#define LPUART_STAT_MA1F_SHIFT                   (15U)
/*! MA1F - Match 1 Flag
 *  0b0..Received data is not equal to MA1
 *  0b1..Received data is equal to MA1
 */
#define LPUART_STAT_MA1F(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_MA1F_SHIFT)) & LPUART_STAT_MA1F_MASK)

#define LPUART_STAT_PF_MASK                      (0x10000U)
#define LPUART_STAT_PF_SHIFT                     (16U)
/*! PF - Parity Error Flag
 *  0b0..No parity error.
 *  0b1..Parity error.
 */
#define LPUART_STAT_PF(x)                        (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_PF_SHIFT)) & LPUART_STAT_PF_MASK)

#define LPUART_STAT_FE_MASK                      (0x20000U)
#define LPUART_STAT_FE_SHIFT                     (17U)
/*! FE - Framing Error Flag
 *  0b0..No framing error detected. This does not guarantee the framing is correct.
 *  0b1..Framing error.
 */
#define LPUART_STAT_FE(x)                        (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_FE_SHIFT)) & LPUART_STAT_FE_MASK)

#define LPUART_STAT_NF_MASK                      (0x40000U)
#define LPUART_STAT_NF_SHIFT                     (18U)
/*! NF - Noise Flag
 *  0b0..No noise detected.
 *  0b1..Noise detected in the received character in LPUART_DATA.
 */
#define LPUART_STAT_NF(x)                        (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_NF_SHIFT)) & LPUART_STAT_NF_MASK)

#define LPUART_STAT_OR_MASK                      (0x80000U)
#define LPUART_STAT_OR_SHIFT                     (19U)
/*! OR - Receiver Overrun Flag
 *  0b0..No overrun.
 *  0b1..Receive overrun (new LPUART data lost).
 */
#define LPUART_STAT_OR(x)                        (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_OR_SHIFT)) & LPUART_STAT_OR_MASK)

#define LPUART_STAT_IDLE_MASK                    (0x100000U)
#define LPUART_STAT_IDLE_SHIFT                   (20U)
/*! IDLE - Idle Line Flag
 *  0b0..No idle line detected.
 *  0b1..Idle line was detected.
 */
#define LPUART_STAT_IDLE(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_IDLE_SHIFT)) & LPUART_STAT_IDLE_MASK)

#define LPUART_STAT_RDRF_MASK                    (0x200000U)
#define LPUART_STAT_RDRF_SHIFT                   (21U)
/*! RDRF - Receive Data Register Full Flag
 *  0b0..Receive data buffer empty.
 *  0b1..Receive data buffer full.
 */
#define LPUART_STAT_RDRF(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_RDRF_SHIFT)) & LPUART_STAT_RDRF_MASK)

#define LPUART_STAT_TC_MASK                      (0x400000U)
#define LPUART_STAT_TC_SHIFT                     (22U)
/*! TC - Transmission Complete Flag
 *  0b0..Transmitter active (sending data, a preamble, or a break).
 *  0b1..Transmitter idle (transmission activity complete).
 */
#define LPUART_STAT_TC(x)                        (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_TC_SHIFT)) & LPUART_STAT_TC_MASK)

#define LPUART_STAT_TDRE_MASK                    (0x800000U)
#define LPUART_STAT_TDRE_SHIFT                   (23U)
/*! TDRE - Transmit Data Register Empty Flag
 *  0b0..Transmit data buffer full.
 *  0b1..Transmit data buffer empty.
 */
#define LPUART_STAT_TDRE(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_TDRE_SHIFT)) & LPUART_STAT_TDRE_MASK)

#define LPUART_STAT_RAF_MASK                     (0x1000000U)
#define LPUART_STAT_RAF_SHIFT                    (24U)
/*! RAF - Receiver Active Flag
 *  0b0..LPUART receiver idle waiting for a start bit.
 *  0b1..LPUART receiver active (LPUART_RX input not idle).
 */
#define LPUART_STAT_RAF(x)                       (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_RAF_SHIFT)) & LPUART_STAT_RAF_MASK)

#define LPUART_STAT_LBKDE_MASK                   (0x2000000U)
#define LPUART_STAT_LBKDE_SHIFT                  (25U)
/*! LBKDE - LIN Break Detection Enable
 *  0b0..Break character is detected at length 10 bit times (if M = 0, SBNS = 0) or 11 (if M = 1, SBNS = 0 or M =
 *       0, SBNS = 1) or 12 (if M = 1, SBNS = 1 or M10 = 1, SNBS = 0) or 13 (if M10 = 1, SNBS = 1).
 *  0b1..Break character is detected at length of 11 bit times (if M = 0, SBNS = 0) or 12 (if M = 1, SBNS = 0 or M
 *       = 0, SBNS = 1) or 14 (if M = 1, SBNS = 1 or M10 = 1, SNBS = 0) or 15 (if M10 = 1, SNBS = 1).
 */
#define LPUART_STAT_LBKDE(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_LBKDE_SHIFT)) & LPUART_STAT_LBKDE_MASK)

#define LPUART_STAT_BRK13_MASK                   (0x4000000U)
#define LPUART_STAT_BRK13_SHIFT                  (26U)
/*! BRK13 - Break Character Generation Length
 *  0b0..Break character is transmitted with length of 10 bit times (if M = 0, SBNS = 0) or 11 (if M = 1, SBNS = 0
 *       or M = 0, SBNS = 1) or 12 (if M = 1, SBNS = 1 or M10 = 1, SNBS = 0) or 13 (if M10 = 1, SNBS = 1).
 *  0b1..Break character is transmitted with length of 13 bit times (if M = 0, SBNS = 0) or 14 (if M = 1, SBNS = 0
 *       or M = 0, SBNS = 1) or 15 (if M = 1, SBNS = 1 or M10 = 1, SNBS = 0) or 16 (if M10 = 1, SNBS = 1).
 */
#define LPUART_STAT_BRK13(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_BRK13_SHIFT)) & LPUART_STAT_BRK13_MASK)

#define LPUART_STAT_RWUID_MASK                   (0x8000000U)
#define LPUART_STAT_RWUID_SHIFT                  (27U)
/*! RWUID - Receive Wake Up Idle Detect
 *  0b0..During receive standby state (RWU = 1), the IDLE bit does not get set upon detection of an idle
 *       character. During address match wakeup, the IDLE bit does not get set when an address does not match.
 *  0b1..During receive standby state (RWU = 1), the IDLE bit gets set upon detection of an idle character. During
 *       address match wakeup, the IDLE bit does get set when an address does not match.
 */
#define LPUART_STAT_RWUID(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_RWUID_SHIFT)) & LPUART_STAT_RWUID_MASK)

#define LPUART_STAT_RXINV_MASK                   (0x10000000U)
#define LPUART_STAT_RXINV_SHIFT                  (28U)
/*! RXINV - Receive Data Inversion
 *  0b0..Receive data not inverted.
 *  0b1..Receive data inverted.
 */
#define LPUART_STAT_RXINV(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_RXINV_SHIFT)) & LPUART_STAT_RXINV_MASK)

#define LPUART_STAT_MSBF_MASK                    (0x20000000U)
#define LPUART_STAT_MSBF_SHIFT                   (29U)
/*! MSBF - MSB First
 *  0b0..LSB (bit0) is the first bit that is transmitted following the start bit. Further, the first bit received
 *       after the start bit is identified as bit0.
 *  0b1..MSB (bit9, bit8, bit7 or bit6) is the first bit that is transmitted following the start bit depending on
 *       the setting of CTRL[M], CTRL[PE] and BAUD[M10]. Further, the first bit received after the start bit is
 *       identified as bit9, bit8, bit7 or bit6 depending on the setting of CTRL[M] and CTRL[PE].
 */
#define LPUART_STAT_MSBF(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_MSBF_SHIFT)) & LPUART_STAT_MSBF_MASK)

#define LPUART_STAT_RXEDGIF_MASK                 (0x40000000U)
#define LPUART_STAT_RXEDGIF_SHIFT                (30U)
/*! RXEDGIF - LPUART_RX Pin Active Edge Interrupt Flag
 *  0b0..No active edge on the receive pin has occurred.
 *  0b1..An active edge on the receive pin has occurred.
 */
#define LPUART_STAT_RXEDGIF(x)                   (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_RXEDGIF_SHIFT)) & LPUART_STAT_RXEDGIF_MASK)

#define LPUART_STAT_LBKDIF_MASK                  (0x80000000U)
#define LPUART_STAT_LBKDIF_SHIFT                 (31U)
/*! LBKDIF - LIN Break Detect Interrupt Flag
 *  0b0..No LIN break character has been detected.
 *  0b1..LIN break character has been detected.
 */
#define LPUART_STAT_LBKDIF(x)                    (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_LBKDIF_SHIFT)) & LPUART_STAT_LBKDIF_MASK)
/*! @} */

/*! @name CTRL - LPUART Control Register */
/*! @{ */

#define LPUART_CTRL_PT_MASK                      (0x1U)
#define LPUART_CTRL_PT_SHIFT                     (0U)
/*! PT - Parity Type
 *  0b0..Even parity.
 *  0b1..Odd parity.
 */
#define LPUART_CTRL_PT(x)                        (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_PT_SHIFT)) & LPUART_CTRL_PT_MASK)

#define LPUART_CTRL_PE_MASK                      (0x2U)
#define LPUART_CTRL_PE_SHIFT                     (1U)
/*! PE - Parity Enable
 *  0b0..No hardware parity generation or checking.
 *  0b1..Parity enabled.
 */
#define LPUART_CTRL_PE(x)                        (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_PE_SHIFT)) & LPUART_CTRL_PE_MASK)

#define LPUART_CTRL_ILT_MASK                     (0x4U)
#define LPUART_CTRL_ILT_SHIFT                    (2U)
/*! ILT - Idle Line Type Select
 *  0b0..Idle character bit count starts after start bit.
 *  0b1..Idle character bit count starts after stop bit.
 */
#define LPUART_CTRL_ILT(x)                       (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_ILT_SHIFT)) & LPUART_CTRL_ILT_MASK)

#define LPUART_CTRL_WAKE_MASK                    (0x8U)
#define LPUART_CTRL_WAKE_SHIFT                   (3U)
/*! WAKE - Receiver Wakeup Method Select
 *  0b0..Configures RWU for idle-line wakeup.
 *  0b1..Configures RWU with address-mark wakeup.
 */
#define LPUART_CTRL_WAKE(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_WAKE_SHIFT)) & LPUART_CTRL_WAKE_MASK)

#define LPUART_CTRL_M_MASK                       (0x10U)
#define LPUART_CTRL_M_SHIFT                      (4U)
/*! M - 9-Bit or 8-Bit Mode Select
 *  0b0..Receiver and transmitter use 8-bit data characters.
 *  0b1..Receiver and transmitter use 9-bit data characters.
 */
#define LPUART_CTRL_M(x)                         (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_M_SHIFT)) & LPUART_CTRL_M_MASK)

#define LPUART_CTRL_RSRC_MASK                    (0x20U)
#define LPUART_CTRL_RSRC_SHIFT                   (5U)
/*! RSRC - Receiver Source Select
 *  0b0..Provided LOOPS is set, RSRC is cleared, selects internal loop back mode and the LPUART does not use the LPUART_RX pin.
 *  0b1..Single-wire LPUART mode where the LPUART_TX pin is connected to the transmitter output and receiver input.
 */
#define LPUART_CTRL_RSRC(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_RSRC_SHIFT)) & LPUART_CTRL_RSRC_MASK)

#define LPUART_CTRL_DOZEEN_MASK                  (0x40U)
#define LPUART_CTRL_DOZEEN_SHIFT                 (6U)
/*! DOZEEN - Doze Enable
 *  0b0..LPUART is enabled in Doze mode.
 *  0b1..LPUART is disabled in Doze mode.
 */
#define LPUART_CTRL_DOZEEN(x)                    (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_DOZEEN_SHIFT)) & LPUART_CTRL_DOZEEN_MASK)

#define LPUART_CTRL_LOOPS_MASK                   (0x80U)
#define LPUART_CTRL_LOOPS_SHIFT                  (7U)
/*! LOOPS - Loop Mode Select
 *  0b0..Normal operation - LPUART_RX and LPUART_TX use separate pins.
 *  0b1..Loop mode or single-wire mode where transmitter outputs are internally connected to receiver input (see RSRC bit).
 */
#define LPUART_CTRL_LOOPS(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_LOOPS_SHIFT)) & LPUART_CTRL_LOOPS_MASK)

#define LPUART_CTRL_IDLECFG_MASK                 (0x700U)
#define LPUART_CTRL_IDLECFG_SHIFT                (8U)
/*! IDLECFG - Idle Configuration
 *  0b000..1 idle character
 *  0b001..2 idle characters
 *  0b010..4 idle characters
 *  0b011..8 idle characters
 *  0b100..16 idle characters
 *  0b101..32 idle characters
 *  0b110..64 idle characters
 *  0b111..128 idle characters
 */
#define LPUART_CTRL_IDLECFG(x)                   (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_IDLECFG_SHIFT)) & LPUART_CTRL_IDLECFG_MASK)

#define LPUART_CTRL_MA2IE_MASK                   (0x4000U)
#define LPUART_CTRL_MA2IE_SHIFT                  (14U)
/*! MA2IE - Match 2 Interrupt Enable
 *  0b0..MA2F interrupt disabled
 *  0b1..MA2F interrupt enabled
 */
#define LPUART_CTRL_MA2IE(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_MA2IE_SHIFT)) & LPUART_CTRL_MA2IE_MASK)

#define LPUART_CTRL_MA1IE_MASK                   (0x8000U)
#define LPUART_CTRL_MA1IE_SHIFT                  (15U)
/*! MA1IE - Match 1 Interrupt Enable
 *  0b0..MA1F interrupt disabled
 *  0b1..MA1F interrupt enabled
 */
#define LPUART_CTRL_MA1IE(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_MA1IE_SHIFT)) & LPUART_CTRL_MA1IE_MASK)

#define LPUART_CTRL_SBK_MASK                     (0x10000U)
#define LPUART_CTRL_SBK_SHIFT                    (16U)
/*! SBK - Send Break
 *  0b0..Normal transmitter operation.
 *  0b1..Queue break character(s) to be sent.
 */
#define LPUART_CTRL_SBK(x)                       (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_SBK_SHIFT)) & LPUART_CTRL_SBK_MASK)

#define LPUART_CTRL_RWU_MASK                     (0x20000U)
#define LPUART_CTRL_RWU_SHIFT                    (17U)
/*! RWU - Receiver Wakeup Control
 *  0b0..Normal receiver operation.
 *  0b1..LPUART receiver in standby waiting for wakeup condition.
 */
#define LPUART_CTRL_RWU(x)                       (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_RWU_SHIFT)) & LPUART_CTRL_RWU_MASK)

#define LPUART_CTRL_RE_MASK                      (0x40000U)
#define LPUART_CTRL_RE_SHIFT                     (18U)
/*! RE - Receiver Enable
 *  0b0..Receiver disabled.
 *  0b1..Receiver enabled.
 */
#define LPUART_CTRL_RE(x)                        (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_RE_SHIFT)) & LPUART_CTRL_RE_MASK)

#define LPUART_CTRL_TE_MASK                      (0x80000U)
#define LPUART_CTRL_TE_SHIFT                     (19U)
/*! TE - Transmitter Enable
 *  0b0..Transmitter disabled.
 *  0b1..Transmitter enabled.
 */
#define LPUART_CTRL_TE(x)                        (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_TE_SHIFT)) & LPUART_CTRL_TE_MASK)

#define LPUART_CTRL_ILIE_MASK                    (0x100000U)
#define LPUART_CTRL_ILIE_SHIFT                   (20U)
/*! ILIE - Idle Line Interrupt Enable
 *  0b0..Hardware interrupts from IDLE disabled; use polling.
 *  0b1..Hardware interrupt requested when IDLE flag is 1.
 */
#define LPUART_CTRL_ILIE(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_ILIE_SHIFT)) & LPUART_CTRL_ILIE_MASK)

#define LPUART_CTRL_RIE_MASK                     (0x200000U)
#define LPUART_CTRL_RIE_SHIFT                    (21U)
/*! RIE - Receiver Interrupt Enable
 *  0b0..Hardware interrupts from RDRF disabled; use polling.
 *  0b1..Hardware interrupt requested when RDRF flag is 1.
 */
#define LPUART_CTRL_RIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_RIE_SHIFT)) & LPUART_CTRL_RIE_MASK)

#define LPUART_CTRL_TCIE_MASK                    (0x400000U)
#define LPUART_CTRL_TCIE_SHIFT                   (22U)
/*! TCIE - Transmission Complete Interrupt Enable for
 *  0b0..Hardware interrupts from TC disabled; use polling.
 *  0b1..Hardware interrupt requested when TC flag is 1.
 */
#define LPUART_CTRL_TCIE(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_TCIE_SHIFT)) & LPUART_CTRL_TCIE_MASK)

#define LPUART_CTRL_TIE_MASK                     (0x800000U)
#define LPUART_CTRL_TIE_SHIFT                    (23U)
/*! TIE - Transmit Interrupt Enable
 *  0b0..Hardware interrupts from TDRE disabled; use polling.
 *  0b1..Hardware interrupt requested when TDRE flag is 1.
 */
#define LPUART_CTRL_TIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_TIE_SHIFT)) & LPUART_CTRL_TIE_MASK)

#define LPUART_CTRL_PEIE_MASK                    (0x1000000U)
#define LPUART_CTRL_PEIE_SHIFT                   (24U)
/*! PEIE - Parity Error Interrupt Enable
 *  0b0..PF interrupts disabled; use polling).
 *  0b1..Hardware interrupt requested when PF is set.
 */
#define LPUART_CTRL_PEIE(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_PEIE_SHIFT)) & LPUART_CTRL_PEIE_MASK)

#define LPUART_CTRL_FEIE_MASK                    (0x2000000U)
#define LPUART_CTRL_FEIE_SHIFT                   (25U)
/*! FEIE - Framing Error Interrupt Enable
 *  0b0..FE interrupts disabled; use polling.
 *  0b1..Hardware interrupt requested when FE is set.
 */
#define LPUART_CTRL_FEIE(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_FEIE_SHIFT)) & LPUART_CTRL_FEIE_MASK)

#define LPUART_CTRL_NEIE_MASK                    (0x4000000U)
#define LPUART_CTRL_NEIE_SHIFT                   (26U)
/*! NEIE - Noise Error Interrupt Enable
 *  0b0..NF interrupts disabled; use polling.
 *  0b1..Hardware interrupt requested when NF is set.
 */
#define LPUART_CTRL_NEIE(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_NEIE_SHIFT)) & LPUART_CTRL_NEIE_MASK)

#define LPUART_CTRL_ORIE_MASK                    (0x8000000U)
#define LPUART_CTRL_ORIE_SHIFT                   (27U)
/*! ORIE - Overrun Interrupt Enable
 *  0b0..OR interrupts disabled; use polling.
 *  0b1..Hardware interrupt requested when OR is set.
 */
#define LPUART_CTRL_ORIE(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_ORIE_SHIFT)) & LPUART_CTRL_ORIE_MASK)

#define LPUART_CTRL_TXINV_MASK                   (0x10000000U)
#define LPUART_CTRL_TXINV_SHIFT                  (28U)
/*! TXINV - Transmit Data Inversion
 *  0b0..Transmit data not inverted.
 *  0b1..Transmit data inverted.
 */
#define LPUART_CTRL_TXINV(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_TXINV_SHIFT)) & LPUART_CTRL_TXINV_MASK)

#define LPUART_CTRL_TXDIR_MASK                   (0x20000000U)
#define LPUART_CTRL_TXDIR_SHIFT                  (29U)
/*! TXDIR - LPUART_TX Pin Direction in Single-Wire Mode
 *  0b0..LPUART_TX pin is an input in single-wire mode.
 *  0b1..LPUART_TX pin is an output in single-wire mode.
 */
#define LPUART_CTRL_TXDIR(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_TXDIR_SHIFT)) & LPUART_CTRL_TXDIR_MASK)

#define LPUART_CTRL_R9T8_MASK                    (0x40000000U)
#define LPUART_CTRL_R9T8_SHIFT                   (30U)
/*! R9T8 - Receive Bit 9 / Transmit Bit 8 */
#define LPUART_CTRL_R9T8(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_R9T8_SHIFT)) & LPUART_CTRL_R9T8_MASK)

#define LPUART_CTRL_R8T9_MASK                    (0x80000000U)
#define LPUART_CTRL_R8T9_SHIFT                   (31U)
/*! R8T9 - Receive Bit 8 / Transmit Bit 9 */
#define LPUART_CTRL_R8T9(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_R8T9_SHIFT)) & LPUART_CTRL_R8T9_MASK)
/*! @} */

/*! @name DATA - LPUART Data Register */
/*! @{ */

#define LPUART_DATA_R0T0_MASK                    (0x1U)
#define LPUART_DATA_R0T0_SHIFT                   (0U)
#define LPUART_DATA_R0T0(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R0T0_SHIFT)) & LPUART_DATA_R0T0_MASK)

#define LPUART_DATA_R1T1_MASK                    (0x2U)
#define LPUART_DATA_R1T1_SHIFT                   (1U)
#define LPUART_DATA_R1T1(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R1T1_SHIFT)) & LPUART_DATA_R1T1_MASK)

#define LPUART_DATA_R2T2_MASK                    (0x4U)
#define LPUART_DATA_R2T2_SHIFT                   (2U)
#define LPUART_DATA_R2T2(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R2T2_SHIFT)) & LPUART_DATA_R2T2_MASK)

#define LPUART_DATA_R3T3_MASK                    (0x8U)
#define LPUART_DATA_R3T3_SHIFT                   (3U)
#define LPUART_DATA_R3T3(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R3T3_SHIFT)) & LPUART_DATA_R3T3_MASK)

#define LPUART_DATA_R4T4_MASK                    (0x10U)
#define LPUART_DATA_R4T4_SHIFT                   (4U)
#define LPUART_DATA_R4T4(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R4T4_SHIFT)) & LPUART_DATA_R4T4_MASK)

#define LPUART_DATA_R5T5_MASK                    (0x20U)
#define LPUART_DATA_R5T5_SHIFT                   (5U)
#define LPUART_DATA_R5T5(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R5T5_SHIFT)) & LPUART_DATA_R5T5_MASK)

#define LPUART_DATA_R6T6_MASK                    (0x40U)
#define LPUART_DATA_R6T6_SHIFT                   (6U)
#define LPUART_DATA_R6T6(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R6T6_SHIFT)) & LPUART_DATA_R6T6_MASK)

#define LPUART_DATA_R7T7_MASK                    (0x80U)
#define LPUART_DATA_R7T7_SHIFT                   (7U)
#define LPUART_DATA_R7T7(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R7T7_SHIFT)) & LPUART_DATA_R7T7_MASK)

#define LPUART_DATA_R8T8_MASK                    (0x100U)
#define LPUART_DATA_R8T8_SHIFT                   (8U)
#define LPUART_DATA_R8T8(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R8T8_SHIFT)) & LPUART_DATA_R8T8_MASK)

#define LPUART_DATA_R9T9_MASK                    (0x200U)
#define LPUART_DATA_R9T9_SHIFT                   (9U)
#define LPUART_DATA_R9T9(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R9T9_SHIFT)) & LPUART_DATA_R9T9_MASK)

#define LPUART_DATA_IDLINE_MASK                  (0x800U)
#define LPUART_DATA_IDLINE_SHIFT                 (11U)
/*! IDLINE - Idle Line
 *  0b0..Receiver was not idle before receiving this character.
 *  0b1..Receiver was idle before receiving this character.
 */
#define LPUART_DATA_IDLINE(x)                    (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_IDLINE_SHIFT)) & LPUART_DATA_IDLINE_MASK)

#define LPUART_DATA_RXEMPT_MASK                  (0x1000U)
#define LPUART_DATA_RXEMPT_SHIFT                 (12U)
/*! RXEMPT - Receive Buffer Empty
 *  0b0..Receive buffer contains valid data.
 *  0b1..Receive buffer is empty, data returned on read is not valid.
 */
#define LPUART_DATA_RXEMPT(x)                    (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_RXEMPT_SHIFT)) & LPUART_DATA_RXEMPT_MASK)

#define LPUART_DATA_FRETSC_MASK                  (0x2000U)
#define LPUART_DATA_FRETSC_SHIFT                 (13U)
/*! FRETSC - Frame Error / Transmit Special Character
 *  0b0..The dataword was received without a frame error on read, transmit a normal character on write.
 *  0b1..The dataword was received with a frame error, transmit an idle or break character on transmit.
 */
#define LPUART_DATA_FRETSC(x)                    (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_FRETSC_SHIFT)) & LPUART_DATA_FRETSC_MASK)

#define LPUART_DATA_PARITYE_MASK                 (0x4000U)
#define LPUART_DATA_PARITYE_SHIFT                (14U)
/*! PARITYE
 *  0b0..The dataword was received without a parity error.
 *  0b1..The dataword was received with a parity error.
 */
#define LPUART_DATA_PARITYE(x)                   (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_PARITYE_SHIFT)) & LPUART_DATA_PARITYE_MASK)

#define LPUART_DATA_NOISY_MASK                   (0x8000U)
#define LPUART_DATA_NOISY_SHIFT                  (15U)
/*! NOISY
 *  0b0..The dataword was received without noise.
 *  0b1..The data was received with noise.
 */
#define LPUART_DATA_NOISY(x)                     (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_NOISY_SHIFT)) & LPUART_DATA_NOISY_MASK)
/*! @} */

/*! @name MATCH - LPUART Match Address Register */
/*! @{ */

#define LPUART_MATCH_MA1_MASK                    (0x3FFU)
#define LPUART_MATCH_MA1_SHIFT                   (0U)
/*! MA1 - Match Address 1 */
#define LPUART_MATCH_MA1(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_MATCH_MA1_SHIFT)) & LPUART_MATCH_MA1_MASK)

#define LPUART_MATCH_MA2_MASK                    (0x3FF0000U)
#define LPUART_MATCH_MA2_SHIFT                   (16U)
/*! MA2 - Match Address 2 */
#define LPUART_MATCH_MA2(x)                      (((uint32_t)(((uint32_t)(x)) << LPUART_MATCH_MA2_SHIFT)) & LPUART_MATCH_MA2_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group LPUART_Register_Masks */


/* LPUART - Peripheral instance base addresses */
/** Peripheral LPUART0 base address */
#define LPUART0_BASE                             (0x40054000u)
/** Peripheral LPUART0 base pointer */
#define LPUART0                                  ((LPUART_Type *)LPUART0_BASE)
/** Peripheral LPUART1 base address */
#define LPUART1_BASE                             (0x40055000u)
/** Peripheral LPUART1 base pointer */
#define LPUART1                                  ((LPUART_Type *)LPUART1_BASE)
/** Array initializer of LPUART peripheral base addresses */
#define LPUART_BASE_ADDRS                        { LPUART0_BASE, LPUART1_BASE }
/** Array initializer of LPUART peripheral base pointers */
#define LPUART_BASE_PTRS                         { LPUART0, LPUART1 }
/** Interrupt vectors for the LPUART peripheral type */
#define LPUART_RX_TX_IRQS                        { LPUART0_IRQn, LPUART1_IRQn }
#define LPUART_ERR_IRQS                          { LPUART0_IRQn, LPUART1_IRQn }

/*!
 * @}
 */ /* end of group LPUART_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MCG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Peripheral_Access_Layer MCG Peripheral Access Layer
 * @{
 */

/** MCG - Register Layout Typedef */
typedef struct {
  __IO uint8_t C1;                                 /**< MCG Control Register 1, offset: 0x0 */
  __IO uint8_t C2;                                 /**< MCG Control Register 2, offset: 0x1 */
       uint8_t RESERVED_0[4];
  __I  uint8_t S;                                  /**< MCG Status Register, offset: 0x6 */
       uint8_t RESERVED_1[1];
  __IO uint8_t SC;                                 /**< MCG Status and Control Register, offset: 0x8 */
       uint8_t RESERVED_2[11];
  __I  uint8_t HCTRIM;                             /**< MCG High-frequency IRC Coarse Trim Register, offset: 0x14 */
  __I  uint8_t HTTRIM;                             /**< MCG High-frequency IRC Tempco (Temperature Coefficient) Trim Register, offset: 0x15 */
  __I  uint8_t HFTRIM;                             /**< MCG High-frequency IRC Fine Trim Register, offset: 0x16 */
       uint8_t RESERVED_3[1];
  __IO uint8_t MC;                                 /**< MCG Miscellaneous Control Register, offset: 0x18 */
  __I  uint8_t LTRIMRNG;                           /**< MCG Low-frequency IRC Trim Range Register, offset: 0x19 */
  __I  uint8_t LFTRIM;                             /**< MCG Low-frequency IRC8M Trim Register, offset: 0x1A */
  __I  uint8_t LSTRIM;                             /**< MCG Low-frequency IRC2M Trim Register, offset: 0x1B */
} MCG_Type;

/* ----------------------------------------------------------------------------
   -- MCG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Register_Masks MCG Register Masks
 * @{
 */

/*! @name C1 - MCG Control Register 1 */
/*! @{ */

#define MCG_C1_IREFSTEN_MASK                     (0x1U)
#define MCG_C1_IREFSTEN_SHIFT                    (0U)
/*! IREFSTEN - Internal Reference Stop Enable
 *  0b0..LIRC is disabled in Stop mode.
 *  0b1..LIRC is enabled in Stop mode, if IRCLKEN is set.
 */
#define MCG_C1_IREFSTEN(x)                       (((uint8_t)(((uint8_t)(x)) << MCG_C1_IREFSTEN_SHIFT)) & MCG_C1_IREFSTEN_MASK)

#define MCG_C1_IRCLKEN_MASK                      (0x2U)
#define MCG_C1_IRCLKEN_SHIFT                     (1U)
/*! IRCLKEN - Internal Reference Clock Enable
 *  0b0..LIRC is disabled.
 *  0b1..LIRC is enabled.
 */
#define MCG_C1_IRCLKEN(x)                        (((uint8_t)(((uint8_t)(x)) << MCG_C1_IRCLKEN_SHIFT)) & MCG_C1_IRCLKEN_MASK)

#define MCG_C1_CLKS_MASK                         (0xC0U)
#define MCG_C1_CLKS_SHIFT                        (6U)
/*! CLKS - Clock Source Select
 *  0b00..Selects HIRC clock as the main clock source. This is HIRC mode.
 *  0b01..Selects LIRC clock as the main clock source. This is LIRC2M or LIRC8M mode.
 *  0b10..Selects external clock as the main clock source. This is EXT mode.
 *  0b11..Reserved. Writing 11 takes no effect.
 */
#define MCG_C1_CLKS(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C1_CLKS_SHIFT)) & MCG_C1_CLKS_MASK)
/*! @} */

/*! @name C2 - MCG Control Register 2 */
/*! @{ */

#define MCG_C2_IRCS_MASK                         (0x1U)
#define MCG_C2_IRCS_SHIFT                        (0U)
/*! IRCS - Low-frequency Internal Reference Clock Select
 *  0b0..LIRC is in 2 MHz mode.
 *  0b1..LIRC is in 8 MHz mode.
 */
#define MCG_C2_IRCS(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C2_IRCS_SHIFT)) & MCG_C2_IRCS_MASK)

#define MCG_C2_EREFS0_MASK                       (0x4U)
#define MCG_C2_EREFS0_SHIFT                      (2U)
/*! EREFS0 - External Clock Source Select
 *  0b0..External clock requested.
 *  0b1..Oscillator requested.
 */
#define MCG_C2_EREFS0(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C2_EREFS0_SHIFT)) & MCG_C2_EREFS0_MASK)

#define MCG_C2_HGO0_MASK                         (0x8U)
#define MCG_C2_HGO0_SHIFT                        (3U)
/*! HGO0 - Crystal Oscillator Operation Mode Select
 *  0b0..Configure crystal oscillator for low-power operation.
 *  0b1..Configure crystal oscillator for high-gain operation.
 */
#define MCG_C2_HGO0(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C2_HGO0_SHIFT)) & MCG_C2_HGO0_MASK)

#define MCG_C2_RANGE0_MASK                       (0x30U)
#define MCG_C2_RANGE0_SHIFT                      (4U)
/*! RANGE0 - External Clock Source Frequency Range Select
 *  0b00..Low frequency range selected for the crystal oscillator or the external clock source.
 *  0b01..High frequency range selected for the crystal oscillator or the external clock source.
 *  0b10..Very high frequency range selected for the crystal oscillator or the external clock source.
 *  0b11..Very high frequency range selected for the crystal oscillator or the external clock source. Same effect as 10.
 */
#define MCG_C2_RANGE0(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C2_RANGE0_SHIFT)) & MCG_C2_RANGE0_MASK)
/*! @} */

/*! @name S - MCG Status Register */
/*! @{ */

#define MCG_S_OSCINIT0_MASK                      (0x2U)
#define MCG_S_OSCINIT0_SHIFT                     (1U)
/*! OSCINIT0 - OSC Initialization Status
 *  0b0..OSC is not ready.
 *  0b1..OSC clock is ready.
 */
#define MCG_S_OSCINIT0(x)                        (((uint8_t)(((uint8_t)(x)) << MCG_S_OSCINIT0_SHIFT)) & MCG_S_OSCINIT0_MASK)

#define MCG_S_CLKST_MASK                         (0xCU)
#define MCG_S_CLKST_SHIFT                        (2U)
/*! CLKST - Clock Mode Status
 *  0b00..HIRC clock is selected as the main clock source, and MCG_Lite works at HIRC mode.
 *  0b01..LIRC clock is selected as the main clock source, and MCG_Lite works at LIRC2M or LIRC8M mode.
 *  0b10..External clock is selected as the main clock source, and MCG_Lite works at EXT mode.
 *  0b11..Reserved.
 */
#define MCG_S_CLKST(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_S_CLKST_SHIFT)) & MCG_S_CLKST_MASK)
/*! @} */

/*! @name SC - MCG Status and Control Register */
/*! @{ */

#define MCG_SC_FCRDIV_MASK                       (0xEU)
#define MCG_SC_FCRDIV_SHIFT                      (1U)
/*! FCRDIV - Low-frequency Internal Reference Clock Divider
 *  0b000..Division factor is 1.
 *  0b001..Division factor is 2.
 *  0b010..Division factor is 4.
 *  0b011..Division factor is 8.
 *  0b100..Division factor is 16.
 *  0b101..Division factor is 32.
 *  0b110..Division factor is 64.
 *  0b111..Division factor is 128.
 */
#define MCG_SC_FCRDIV(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_SC_FCRDIV_SHIFT)) & MCG_SC_FCRDIV_MASK)
/*! @} */

/*! @name HCTRIM - MCG High-frequency IRC Coarse Trim Register */
/*! @{ */

#define MCG_HCTRIM_COARSE_TRIM_MASK              (0x3FU)
#define MCG_HCTRIM_COARSE_TRIM_SHIFT             (0U)
/*! COARSE_TRIM - High-frequency IRC Coarse Trim */
#define MCG_HCTRIM_COARSE_TRIM(x)                (((uint8_t)(((uint8_t)(x)) << MCG_HCTRIM_COARSE_TRIM_SHIFT)) & MCG_HCTRIM_COARSE_TRIM_MASK)
/*! @} */

/*! @name HTTRIM - MCG High-frequency IRC Tempco (Temperature Coefficient) Trim Register */
/*! @{ */

#define MCG_HTTRIM_TEMPCO_TRIM_MASK              (0x1FU)
#define MCG_HTTRIM_TEMPCO_TRIM_SHIFT             (0U)
/*! TEMPCO_TRIM - High-frequency IRC Tempco Trim */
#define MCG_HTTRIM_TEMPCO_TRIM(x)                (((uint8_t)(((uint8_t)(x)) << MCG_HTTRIM_TEMPCO_TRIM_SHIFT)) & MCG_HTTRIM_TEMPCO_TRIM_MASK)
/*! @} */

/*! @name HFTRIM - MCG High-frequency IRC Fine Trim Register */
/*! @{ */

#define MCG_HFTRIM_FINE_TRIM_MASK                (0x7FU)
#define MCG_HFTRIM_FINE_TRIM_SHIFT               (0U)
/*! FINE_TRIM - High-frequency IRC Fine Trim */
#define MCG_HFTRIM_FINE_TRIM(x)                  (((uint8_t)(((uint8_t)(x)) << MCG_HFTRIM_FINE_TRIM_SHIFT)) & MCG_HFTRIM_FINE_TRIM_MASK)
/*! @} */

/*! @name MC - MCG Miscellaneous Control Register */
/*! @{ */

#define MCG_MC_LIRC_DIV2_MASK                    (0x7U)
#define MCG_MC_LIRC_DIV2_SHIFT                   (0U)
/*! LIRC_DIV2 - Second Low-frequency Internal Reference Clock Divider
 *  0b000..Division factor is 1.
 *  0b001..Division factor is 2.
 *  0b010..Division factor is 4.
 *  0b011..Division factor is 8.
 *  0b100..Division factor is 16.
 *  0b101..Division factor is 32.
 *  0b110..Division factor is 64.
 *  0b111..Division factor is 128.
 */
#define MCG_MC_LIRC_DIV2(x)                      (((uint8_t)(((uint8_t)(x)) << MCG_MC_LIRC_DIV2_SHIFT)) & MCG_MC_LIRC_DIV2_MASK)

#define MCG_MC_HIRCEN_MASK                       (0x80U)
#define MCG_MC_HIRCEN_SHIFT                      (7U)
/*! HIRCEN - High-frequency IRC Enable
 *  0b0..HIRC source is not enabled.
 *  0b1..HIRC source is enabled.
 */
#define MCG_MC_HIRCEN(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_MC_HIRCEN_SHIFT)) & MCG_MC_HIRCEN_MASK)
/*! @} */

/*! @name LTRIMRNG - MCG Low-frequency IRC Trim Range Register */
/*! @{ */

#define MCG_LTRIMRNG_STRIMRNG_MASK               (0x3U)
#define MCG_LTRIMRNG_STRIMRNG_SHIFT              (0U)
/*! STRIMRNG - LIRC Slow TRIM (2 MHz) Range
 *  0b00..Frequency shift by 10%.
 *  0b01..No frequency shift.
 *  0b10..No frequency shift.
 *  0b11..Frequency shift by -10%.
 */
#define MCG_LTRIMRNG_STRIMRNG(x)                 (((uint8_t)(((uint8_t)(x)) << MCG_LTRIMRNG_STRIMRNG_SHIFT)) & MCG_LTRIMRNG_STRIMRNG_MASK)

#define MCG_LTRIMRNG_FTRIMRNG_MASK               (0xCU)
#define MCG_LTRIMRNG_FTRIMRNG_SHIFT              (2U)
/*! FTRIMRNG - LIRC Fast TRIM (8 MHz) Range
 *  0b00..Frequency shift by 10%.
 *  0b01..No frequency shift.
 *  0b10..No frequency shift.
 *  0b11..Frequency shift by -10%.
 */
#define MCG_LTRIMRNG_FTRIMRNG(x)                 (((uint8_t)(((uint8_t)(x)) << MCG_LTRIMRNG_FTRIMRNG_SHIFT)) & MCG_LTRIMRNG_FTRIMRNG_MASK)
/*! @} */

/*! @name LFTRIM - MCG Low-frequency IRC8M Trim Register */
/*! @{ */

#define MCG_LFTRIM_LIRC_FTRIM_MASK               (0x7FU)
#define MCG_LFTRIM_LIRC_FTRIM_SHIFT              (0U)
/*! LIRC_FTRIM - LIRC8M TRIM */
#define MCG_LFTRIM_LIRC_FTRIM(x)                 (((uint8_t)(((uint8_t)(x)) << MCG_LFTRIM_LIRC_FTRIM_SHIFT)) & MCG_LFTRIM_LIRC_FTRIM_MASK)
/*! @} */

/*! @name LSTRIM - MCG Low-frequency IRC2M Trim Register */
/*! @{ */

#define MCG_LSTRIM_LIRC_STRIM_MASK               (0x7FU)
#define MCG_LSTRIM_LIRC_STRIM_SHIFT              (0U)
/*! LIRC_STRIM - LIRC2M TRIM */
#define MCG_LSTRIM_LIRC_STRIM(x)                 (((uint8_t)(((uint8_t)(x)) << MCG_LSTRIM_LIRC_STRIM_SHIFT)) & MCG_LSTRIM_LIRC_STRIM_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group MCG_Register_Masks */


/* MCG - Peripheral instance base addresses */
/** Peripheral MCG base address */
#define MCG_BASE                                 (0x40064000u)
/** Peripheral MCG base pointer */
#define MCG                                      ((MCG_Type *)MCG_BASE)
/** Array initializer of MCG peripheral base addresses */
#define MCG_BASE_ADDRS                           { MCG_BASE }
/** Array initializer of MCG peripheral base pointers */
#define MCG_BASE_PTRS                            { MCG }

/*!
 * @}
 */ /* end of group MCG_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Peripheral_Access_Layer MCM Peripheral Access Layer
 * @{
 */

/** MCM - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[8];
  __I  uint16_t PLASC;                             /**< Crossbar Switch (AXBS) Slave Configuration, offset: 0x8 */
  __I  uint16_t PLAMC;                             /**< Crossbar Switch (AXBS) Master Configuration, offset: 0xA */
  __IO uint32_t PLACR;                             /**< Platform Control Register, offset: 0xC */
       uint8_t RESERVED_1[48];
  __IO uint32_t CPO;                               /**< Compute Operation Control Register, offset: 0x40 */
} MCM_Type;

/* ----------------------------------------------------------------------------
   -- MCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Masks MCM Register Masks
 * @{
 */

/*! @name PLASC - Crossbar Switch (AXBS) Slave Configuration */
/*! @{ */

#define MCM_PLASC_ASC_MASK                       (0xFFU)
#define MCM_PLASC_ASC_SHIFT                      (0U)
/*! ASC - Each bit in the ASC field indicates whether there is a corresponding connection to the
 *    crossbar switch's slave input port.
 *  0b00000000..A bus slave connection to AXBS input port n is absent.
 *  0b00000001..A bus slave connection to AXBS input port n is present.
 */
#define MCM_PLASC_ASC(x)                         (((uint16_t)(((uint16_t)(x)) << MCM_PLASC_ASC_SHIFT)) & MCM_PLASC_ASC_MASK)
/*! @} */

/*! @name PLAMC - Crossbar Switch (AXBS) Master Configuration */
/*! @{ */

#define MCM_PLAMC_AMC_MASK                       (0xFFU)
#define MCM_PLAMC_AMC_SHIFT                      (0U)
/*! AMC - Each bit in the AMC field indicates whether there is a corresponding connection to the AXBS master input port.
 *  0b00000000..A bus master connection to AXBS input port n is absent
 *  0b00000001..A bus master connection to AXBS input port n is present
 */
#define MCM_PLAMC_AMC(x)                         (((uint16_t)(((uint16_t)(x)) << MCM_PLAMC_AMC_SHIFT)) & MCM_PLAMC_AMC_MASK)
/*! @} */

/*! @name PLACR - Platform Control Register */
/*! @{ */

#define MCM_PLACR_ARB_MASK                       (0x200U)
#define MCM_PLACR_ARB_SHIFT                      (9U)
/*! ARB - Arbitration select
 *  0b0..Fixed-priority arbitration for the crossbar masters
 *  0b1..Round-robin arbitration for the crossbar masters
 */
#define MCM_PLACR_ARB(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_ARB_SHIFT)) & MCM_PLACR_ARB_MASK)

#define MCM_PLACR_CFCC_MASK                      (0x400U)
#define MCM_PLACR_CFCC_SHIFT                     (10U)
/*! CFCC - Clear Flash Controller Cache */
#define MCM_PLACR_CFCC(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_CFCC_SHIFT)) & MCM_PLACR_CFCC_MASK)

#define MCM_PLACR_DFCDA_MASK                     (0x800U)
#define MCM_PLACR_DFCDA_SHIFT                    (11U)
/*! DFCDA - Disable Flash Controller Data Caching
 *  0b0..Enable flash controller data caching
 *  0b1..Disable flash controller data caching.
 */
#define MCM_PLACR_DFCDA(x)                       (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_DFCDA_SHIFT)) & MCM_PLACR_DFCDA_MASK)

#define MCM_PLACR_DFCIC_MASK                     (0x1000U)
#define MCM_PLACR_DFCIC_SHIFT                    (12U)
/*! DFCIC - Disable Flash Controller Instruction Caching
 *  0b0..Enable flash controller instruction caching.
 *  0b1..Disable flash controller instruction caching.
 */
#define MCM_PLACR_DFCIC(x)                       (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_DFCIC_SHIFT)) & MCM_PLACR_DFCIC_MASK)

#define MCM_PLACR_DFCC_MASK                      (0x2000U)
#define MCM_PLACR_DFCC_SHIFT                     (13U)
/*! DFCC - Disable Flash Controller Cache
 *  0b0..Enable flash controller cache.
 *  0b1..Disable flash controller cache.
 */
#define MCM_PLACR_DFCC(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_DFCC_SHIFT)) & MCM_PLACR_DFCC_MASK)

#define MCM_PLACR_EFDS_MASK                      (0x4000U)
#define MCM_PLACR_EFDS_SHIFT                     (14U)
/*! EFDS - Enable Flash Data Speculation
 *  0b0..Disable flash data speculation.
 *  0b1..Enable flash data speculation.
 */
#define MCM_PLACR_EFDS(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_EFDS_SHIFT)) & MCM_PLACR_EFDS_MASK)

#define MCM_PLACR_DFCS_MASK                      (0x8000U)
#define MCM_PLACR_DFCS_SHIFT                     (15U)
/*! DFCS - Disable Flash Controller Speculation
 *  0b0..Enable flash controller speculation.
 *  0b1..Disable flash controller speculation.
 */
#define MCM_PLACR_DFCS(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_DFCS_SHIFT)) & MCM_PLACR_DFCS_MASK)

#define MCM_PLACR_ESFC_MASK                      (0x10000U)
#define MCM_PLACR_ESFC_SHIFT                     (16U)
/*! ESFC - Enable Stalling Flash Controller
 *  0b0..Disable stalling flash controller when flash is busy.
 *  0b1..Enable stalling flash controller when flash is busy.
 */
#define MCM_PLACR_ESFC(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_ESFC_SHIFT)) & MCM_PLACR_ESFC_MASK)
/*! @} */

/*! @name CPO - Compute Operation Control Register */
/*! @{ */

#define MCM_CPO_CPOREQ_MASK                      (0x1U)
#define MCM_CPO_CPOREQ_SHIFT                     (0U)
/*! CPOREQ - Compute Operation Request
 *  0b0..Request is cleared.
 *  0b1..Request Compute Operation.
 */
#define MCM_CPO_CPOREQ(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_CPO_CPOREQ_SHIFT)) & MCM_CPO_CPOREQ_MASK)

#define MCM_CPO_CPOACK_MASK                      (0x2U)
#define MCM_CPO_CPOACK_SHIFT                     (1U)
/*! CPOACK - Compute Operation Acknowledge
 *  0b0..Compute operation entry has not completed or compute operation exit has completed.
 *  0b1..Compute operation entry has completed or compute operation exit has not completed.
 */
#define MCM_CPO_CPOACK(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_CPO_CPOACK_SHIFT)) & MCM_CPO_CPOACK_MASK)

#define MCM_CPO_CPOWOI_MASK                      (0x4U)
#define MCM_CPO_CPOWOI_SHIFT                     (2U)
/*! CPOWOI - Compute Operation Wake-up on Interrupt
 *  0b0..No effect.
 *  0b1..When set, the CPOREQ is cleared on any interrupt or exception vector fetch.
 */
#define MCM_CPO_CPOWOI(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_CPO_CPOWOI_SHIFT)) & MCM_CPO_CPOWOI_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group MCM_Register_Masks */


/* MCM - Peripheral instance base addresses */
/** Peripheral MCM base address */
#define MCM_BASE                                 (0xF0003000u)
/** Peripheral MCM base pointer */
#define MCM                                      ((MCM_Type *)MCM_BASE)
/** Array initializer of MCM peripheral base addresses */
#define MCM_BASE_ADDRS                           { MCM_BASE }
/** Array initializer of MCM peripheral base pointers */
#define MCM_BASE_PTRS                            { MCM }

/*!
 * @}
 */ /* end of group MCM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MTB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_Peripheral_Access_Layer MTB Peripheral Access Layer
 * @{
 */

/** MTB - Register Layout Typedef */
typedef struct {
  __IO uint32_t POSITION;                          /**< MTB Position Register, offset: 0x0 */
  __IO uint32_t MASTER;                            /**< MTB Master Register, offset: 0x4 */
  __IO uint32_t FLOW;                              /**< MTB Flow Register, offset: 0x8 */
  __I  uint32_t BASE;                              /**< MTB Base Register, offset: 0xC */
       uint8_t RESERVED_0[3824];
  __I  uint32_t MODECTRL;                          /**< Integration Mode Control Register, offset: 0xF00 */
       uint8_t RESERVED_1[156];
  __I  uint32_t TAGSET;                            /**< Claim TAG Set Register, offset: 0xFA0 */
  __I  uint32_t TAGCLEAR;                          /**< Claim TAG Clear Register, offset: 0xFA4 */
       uint8_t RESERVED_2[8];
  __I  uint32_t LOCKACCESS;                        /**< Lock Access Register, offset: 0xFB0 */
  __I  uint32_t LOCKSTAT;                          /**< Lock Status Register, offset: 0xFB4 */
  __I  uint32_t AUTHSTAT;                          /**< Authentication Status Register, offset: 0xFB8 */
  __I  uint32_t DEVICEARCH;                        /**< Device Architecture Register, offset: 0xFBC */
       uint8_t RESERVED_3[8];
  __I  uint32_t DEVICECFG;                         /**< Device Configuration Register, offset: 0xFC8 */
  __I  uint32_t DEVICETYPID;                       /**< Device Type Identifier Register, offset: 0xFCC */
  __I  uint32_t PERIPHID4;                         /**< Peripheral ID Register, offset: 0xFD0 */
  __I  uint32_t PERIPHID5;                         /**< Peripheral ID Register, offset: 0xFD4 */
  __I  uint32_t PERIPHID6;                         /**< Peripheral ID Register, offset: 0xFD8 */
  __I  uint32_t PERIPHID7;                         /**< Peripheral ID Register, offset: 0xFDC */
  __I  uint32_t PERIPHID0;                         /**< Peripheral ID Register, offset: 0xFE0 */
  __I  uint32_t PERIPHID1;                         /**< Peripheral ID Register, offset: 0xFE4 */
  __I  uint32_t PERIPHID2;                         /**< Peripheral ID Register, offset: 0xFE8 */
  __I  uint32_t PERIPHID3;                         /**< Peripheral ID Register, offset: 0xFEC */
  __I  uint32_t COMPID[4];                         /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} MTB_Type;

/* ----------------------------------------------------------------------------
   -- MTB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_Register_Masks MTB Register Masks
 * @{
 */

/*! @name POSITION - MTB Position Register */
/*! @{ */

#define MTB_POSITION_WRAP_MASK                   (0x4U)
#define MTB_POSITION_WRAP_SHIFT                  (2U)
/*! WRAP - WRAP */
#define MTB_POSITION_WRAP(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_POSITION_WRAP_SHIFT)) & MTB_POSITION_WRAP_MASK)

#define MTB_POSITION_POINTER_MASK                (0xFFFFFFF8U)
#define MTB_POSITION_POINTER_SHIFT               (3U)
/*! POINTER - Trace Packet Address Pointer[28:0] */
#define MTB_POSITION_POINTER(x)                  (((uint32_t)(((uint32_t)(x)) << MTB_POSITION_POINTER_SHIFT)) & MTB_POSITION_POINTER_MASK)
/*! @} */

/*! @name MASTER - MTB Master Register */
/*! @{ */

#define MTB_MASTER_MASK_MASK                     (0x1FU)
#define MTB_MASTER_MASK_SHIFT                    (0U)
/*! MASK - Mask */
#define MTB_MASTER_MASK(x)                       (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_MASK_SHIFT)) & MTB_MASTER_MASK_MASK)

#define MTB_MASTER_TSTARTEN_MASK                 (0x20U)
#define MTB_MASTER_TSTARTEN_SHIFT                (5U)
/*! TSTARTEN - Trace Start Input Enable */
#define MTB_MASTER_TSTARTEN(x)                   (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_TSTARTEN_SHIFT)) & MTB_MASTER_TSTARTEN_MASK)

#define MTB_MASTER_TSTOPEN_MASK                  (0x40U)
#define MTB_MASTER_TSTOPEN_SHIFT                 (6U)
/*! TSTOPEN - Trace Stop Input Enable */
#define MTB_MASTER_TSTOPEN(x)                    (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_TSTOPEN_SHIFT)) & MTB_MASTER_TSTOPEN_MASK)

#define MTB_MASTER_SFRWPRIV_MASK                 (0x80U)
#define MTB_MASTER_SFRWPRIV_SHIFT                (7U)
/*! SFRWPRIV - Special Function Register Write Privilege */
#define MTB_MASTER_SFRWPRIV(x)                   (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_SFRWPRIV_SHIFT)) & MTB_MASTER_SFRWPRIV_MASK)

#define MTB_MASTER_RAMPRIV_MASK                  (0x100U)
#define MTB_MASTER_RAMPRIV_SHIFT                 (8U)
/*! RAMPRIV - RAM Privilege */
#define MTB_MASTER_RAMPRIV(x)                    (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_RAMPRIV_SHIFT)) & MTB_MASTER_RAMPRIV_MASK)

#define MTB_MASTER_HALTREQ_MASK                  (0x200U)
#define MTB_MASTER_HALTREQ_SHIFT                 (9U)
/*! HALTREQ - Halt Request */
#define MTB_MASTER_HALTREQ(x)                    (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_HALTREQ_SHIFT)) & MTB_MASTER_HALTREQ_MASK)

#define MTB_MASTER_EN_MASK                       (0x80000000U)
#define MTB_MASTER_EN_SHIFT                      (31U)
/*! EN - Main Trace Enable */
#define MTB_MASTER_EN(x)                         (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_EN_SHIFT)) & MTB_MASTER_EN_MASK)
/*! @} */

/*! @name FLOW - MTB Flow Register */
/*! @{ */

#define MTB_FLOW_AUTOSTOP_MASK                   (0x1U)
#define MTB_FLOW_AUTOSTOP_SHIFT                  (0U)
/*! AUTOSTOP - AUTOSTOP */
#define MTB_FLOW_AUTOSTOP(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_FLOW_AUTOSTOP_SHIFT)) & MTB_FLOW_AUTOSTOP_MASK)

#define MTB_FLOW_AUTOHALT_MASK                   (0x2U)
#define MTB_FLOW_AUTOHALT_SHIFT                  (1U)
/*! AUTOHALT - AUTOHALT */
#define MTB_FLOW_AUTOHALT(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_FLOW_AUTOHALT_SHIFT)) & MTB_FLOW_AUTOHALT_MASK)

#define MTB_FLOW_WATERMARK_MASK                  (0xFFFFFFF8U)
#define MTB_FLOW_WATERMARK_SHIFT                 (3U)
/*! WATERMARK - WATERMARK[28:0] */
#define MTB_FLOW_WATERMARK(x)                    (((uint32_t)(((uint32_t)(x)) << MTB_FLOW_WATERMARK_SHIFT)) & MTB_FLOW_WATERMARK_MASK)
/*! @} */

/*! @name BASE - MTB Base Register */
/*! @{ */

#define MTB_BASE_BASEADDR_MASK                   (0xFFFFFFFFU)
#define MTB_BASE_BASEADDR_SHIFT                  (0U)
/*! BASEADDR - BASEADDR */
#define MTB_BASE_BASEADDR(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_BASE_BASEADDR_SHIFT)) & MTB_BASE_BASEADDR_MASK)
/*! @} */

/*! @name MODECTRL - Integration Mode Control Register */
/*! @{ */

#define MTB_MODECTRL_MODECTRL_MASK               (0xFFFFFFFFU)
#define MTB_MODECTRL_MODECTRL_SHIFT              (0U)
/*! MODECTRL - MODECTRL */
#define MTB_MODECTRL_MODECTRL(x)                 (((uint32_t)(((uint32_t)(x)) << MTB_MODECTRL_MODECTRL_SHIFT)) & MTB_MODECTRL_MODECTRL_MASK)
/*! @} */

/*! @name TAGSET - Claim TAG Set Register */
/*! @{ */

#define MTB_TAGSET_TAGSET_MASK                   (0xFFFFFFFFU)
#define MTB_TAGSET_TAGSET_SHIFT                  (0U)
/*! TAGSET - TAGSET */
#define MTB_TAGSET_TAGSET(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_TAGSET_TAGSET_SHIFT)) & MTB_TAGSET_TAGSET_MASK)
/*! @} */

/*! @name TAGCLEAR - Claim TAG Clear Register */
/*! @{ */

#define MTB_TAGCLEAR_TAGCLEAR_MASK               (0xFFFFFFFFU)
#define MTB_TAGCLEAR_TAGCLEAR_SHIFT              (0U)
/*! TAGCLEAR - TAGCLEAR */
#define MTB_TAGCLEAR_TAGCLEAR(x)                 (((uint32_t)(((uint32_t)(x)) << MTB_TAGCLEAR_TAGCLEAR_SHIFT)) & MTB_TAGCLEAR_TAGCLEAR_MASK)
/*! @} */

/*! @name LOCKACCESS - Lock Access Register */
/*! @{ */

#define MTB_LOCKACCESS_LOCKACCESS_MASK           (0xFFFFFFFFU)
#define MTB_LOCKACCESS_LOCKACCESS_SHIFT          (0U)
#define MTB_LOCKACCESS_LOCKACCESS(x)             (((uint32_t)(((uint32_t)(x)) << MTB_LOCKACCESS_LOCKACCESS_SHIFT)) & MTB_LOCKACCESS_LOCKACCESS_MASK)
/*! @} */

/*! @name LOCKSTAT - Lock Status Register */
/*! @{ */

#define MTB_LOCKSTAT_LOCKSTAT_MASK               (0xFFFFFFFFU)
#define MTB_LOCKSTAT_LOCKSTAT_SHIFT              (0U)
/*! LOCKSTAT - LOCKSTAT */
#define MTB_LOCKSTAT_LOCKSTAT(x)                 (((uint32_t)(((uint32_t)(x)) << MTB_LOCKSTAT_LOCKSTAT_SHIFT)) & MTB_LOCKSTAT_LOCKSTAT_MASK)
/*! @} */

/*! @name AUTHSTAT - Authentication Status Register */
/*! @{ */

#define MTB_AUTHSTAT_BIT0_MASK                   (0x1U)
#define MTB_AUTHSTAT_BIT0_SHIFT                  (0U)
#define MTB_AUTHSTAT_BIT0(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_AUTHSTAT_BIT0_SHIFT)) & MTB_AUTHSTAT_BIT0_MASK)

#define MTB_AUTHSTAT_BIT1_MASK                   (0x2U)
#define MTB_AUTHSTAT_BIT1_SHIFT                  (1U)
/*! BIT1 - BIT1 */
#define MTB_AUTHSTAT_BIT1(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_AUTHSTAT_BIT1_SHIFT)) & MTB_AUTHSTAT_BIT1_MASK)

#define MTB_AUTHSTAT_BIT2_MASK                   (0x4U)
#define MTB_AUTHSTAT_BIT2_SHIFT                  (2U)
/*! BIT2 - BIT2 */
#define MTB_AUTHSTAT_BIT2(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_AUTHSTAT_BIT2_SHIFT)) & MTB_AUTHSTAT_BIT2_MASK)

#define MTB_AUTHSTAT_BIT3_MASK                   (0x8U)
#define MTB_AUTHSTAT_BIT3_SHIFT                  (3U)
/*! BIT3 - BIT3 */
#define MTB_AUTHSTAT_BIT3(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_AUTHSTAT_BIT3_SHIFT)) & MTB_AUTHSTAT_BIT3_MASK)
/*! @} */

/*! @name DEVICEARCH - Device Architecture Register */
/*! @{ */

#define MTB_DEVICEARCH_DEVICEARCH_MASK           (0xFFFFFFFFU)
#define MTB_DEVICEARCH_DEVICEARCH_SHIFT          (0U)
/*! DEVICEARCH - DEVICEARCH */
#define MTB_DEVICEARCH_DEVICEARCH(x)             (((uint32_t)(((uint32_t)(x)) << MTB_DEVICEARCH_DEVICEARCH_SHIFT)) & MTB_DEVICEARCH_DEVICEARCH_MASK)
/*! @} */

/*! @name DEVICECFG - Device Configuration Register */
/*! @{ */

#define MTB_DEVICECFG_DEVICECFG_MASK             (0xFFFFFFFFU)
#define MTB_DEVICECFG_DEVICECFG_SHIFT            (0U)
/*! DEVICECFG - DEVICECFG */
#define MTB_DEVICECFG_DEVICECFG(x)               (((uint32_t)(((uint32_t)(x)) << MTB_DEVICECFG_DEVICECFG_SHIFT)) & MTB_DEVICECFG_DEVICECFG_MASK)
/*! @} */

/*! @name DEVICETYPID - Device Type Identifier Register */
/*! @{ */

#define MTB_DEVICETYPID_DEVICETYPID_MASK         (0xFFFFFFFFU)
#define MTB_DEVICETYPID_DEVICETYPID_SHIFT        (0U)
/*! DEVICETYPID - DEVICETYPID */
#define MTB_DEVICETYPID_DEVICETYPID(x)           (((uint32_t)(((uint32_t)(x)) << MTB_DEVICETYPID_DEVICETYPID_SHIFT)) & MTB_DEVICETYPID_DEVICETYPID_MASK)
/*! @} */

/*! @name PERIPHID4 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID4_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID4_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define MTB_PERIPHID4_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID4_PERIPHID_SHIFT)) & MTB_PERIPHID4_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID5 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID5_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID5_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define MTB_PERIPHID5_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID5_PERIPHID_SHIFT)) & MTB_PERIPHID5_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID6 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID6_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID6_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define MTB_PERIPHID6_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID6_PERIPHID_SHIFT)) & MTB_PERIPHID6_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID7 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID7_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID7_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define MTB_PERIPHID7_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID7_PERIPHID_SHIFT)) & MTB_PERIPHID7_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID0 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID0_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID0_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define MTB_PERIPHID0_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID0_PERIPHID_SHIFT)) & MTB_PERIPHID0_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID1 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID1_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID1_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define MTB_PERIPHID1_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID1_PERIPHID_SHIFT)) & MTB_PERIPHID1_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID2 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID2_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID2_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define MTB_PERIPHID2_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID2_PERIPHID_SHIFT)) & MTB_PERIPHID2_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID3 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID3_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID3_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define MTB_PERIPHID3_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID3_PERIPHID_SHIFT)) & MTB_PERIPHID3_PERIPHID_MASK)
/*! @} */

/*! @name COMPID - Component ID Register */
/*! @{ */

#define MTB_COMPID_COMPID_MASK                   (0xFFFFFFFFU)
#define MTB_COMPID_COMPID_SHIFT                  (0U)
/*! COMPID - Component ID */
#define MTB_COMPID_COMPID(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_COMPID_COMPID_SHIFT)) & MTB_COMPID_COMPID_MASK)
/*! @} */

/* The count of MTB_COMPID */
#define MTB_COMPID_COUNT                         (4U)


/*!
 * @}
 */ /* end of group MTB_Register_Masks */


/* MTB - Peripheral instance base addresses */
/** Peripheral MTB base address */
#define MTB_BASE                                 (0xF0000000u)
/** Peripheral MTB base pointer */
#define MTB                                      ((MTB_Type *)MTB_BASE)
/** Array initializer of MTB peripheral base addresses */
#define MTB_BASE_ADDRS                           { MTB_BASE }
/** Array initializer of MTB peripheral base pointers */
#define MTB_BASE_PTRS                            { MTB }

/*!
 * @}
 */ /* end of group MTB_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MTBDWT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTBDWT_Peripheral_Access_Layer MTBDWT Peripheral Access Layer
 * @{
 */

/** MTBDWT - Register Layout Typedef */
typedef struct {
  __I  uint32_t CTRL;                              /**< MTB DWT Control Register, offset: 0x0 */
       uint8_t RESERVED_0[28];
  struct {                                         /* offset: 0x20, array step: 0x10 */
    __IO uint32_t COMP;                              /**< MTB_DWT Comparator Register, array offset: 0x20, array step: 0x10 */
    __IO uint32_t MASK;                              /**< MTB_DWT Comparator Mask Register, array offset: 0x24, array step: 0x10 */
    __IO uint32_t FCT;                               /**< MTB_DWT Comparator Function Register 0..MTB_DWT Comparator Function Register 1, array offset: 0x28, array step: 0x10 */
         uint8_t RESERVED_0[4];
  } COMPARATOR[2];
       uint8_t RESERVED_1[448];
  __IO uint32_t TBCTRL;                            /**< MTB_DWT Trace Buffer Control Register, offset: 0x200 */
       uint8_t RESERVED_2[3524];
  __I  uint32_t DEVICECFG;                         /**< Device Configuration Register, offset: 0xFC8 */
  __I  uint32_t DEVICETYPID;                       /**< Device Type Identifier Register, offset: 0xFCC */
  __I  uint32_t PERIPHID4;                         /**< Peripheral ID Register, offset: 0xFD0 */
  __I  uint32_t PERIPHID5;                         /**< Peripheral ID Register, offset: 0xFD4 */
  __I  uint32_t PERIPHID6;                         /**< Peripheral ID Register, offset: 0xFD8 */
  __I  uint32_t PERIPHID7;                         /**< Peripheral ID Register, offset: 0xFDC */
  __I  uint32_t PERIPHID0;                         /**< Peripheral ID Register, offset: 0xFE0 */
  __I  uint32_t PERIPHID1;                         /**< Peripheral ID Register, offset: 0xFE4 */
  __I  uint32_t PERIPHID2;                         /**< Peripheral ID Register, offset: 0xFE8 */
  __I  uint32_t PERIPHID3;                         /**< Peripheral ID Register, offset: 0xFEC */
  __I  uint32_t COMPID[4];                         /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} MTBDWT_Type;

/* ----------------------------------------------------------------------------
   -- MTBDWT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTBDWT_Register_Masks MTBDWT Register Masks
 * @{
 */

/*! @name CTRL - MTB DWT Control Register */
/*! @{ */

#define MTBDWT_CTRL_DWTCFGCTRL_MASK              (0xFFFFFFFU)
#define MTBDWT_CTRL_DWTCFGCTRL_SHIFT             (0U)
/*! DWTCFGCTRL - DWT configuration controls */
#define MTBDWT_CTRL_DWTCFGCTRL(x)                (((uint32_t)(((uint32_t)(x)) << MTBDWT_CTRL_DWTCFGCTRL_SHIFT)) & MTBDWT_CTRL_DWTCFGCTRL_MASK)

#define MTBDWT_CTRL_NUMCMP_MASK                  (0xF0000000U)
#define MTBDWT_CTRL_NUMCMP_SHIFT                 (28U)
/*! NUMCMP - Number of comparators */
#define MTBDWT_CTRL_NUMCMP(x)                    (((uint32_t)(((uint32_t)(x)) << MTBDWT_CTRL_NUMCMP_SHIFT)) & MTBDWT_CTRL_NUMCMP_MASK)
/*! @} */

/*! @name COMP - MTB_DWT Comparator Register */
/*! @{ */

#define MTBDWT_COMP_COMP_MASK                    (0xFFFFFFFFU)
#define MTBDWT_COMP_COMP_SHIFT                   (0U)
/*! COMP - Reference value for comparison */
#define MTBDWT_COMP_COMP(x)                      (((uint32_t)(((uint32_t)(x)) << MTBDWT_COMP_COMP_SHIFT)) & MTBDWT_COMP_COMP_MASK)
/*! @} */

/* The count of MTBDWT_COMP */
#define MTBDWT_COMP_COUNT                        (2U)

/*! @name MASK - MTB_DWT Comparator Mask Register */
/*! @{ */

#define MTBDWT_MASK_MASK_MASK                    (0x1FU)
#define MTBDWT_MASK_MASK_SHIFT                   (0U)
/*! MASK - MASK */
#define MTBDWT_MASK_MASK(x)                      (((uint32_t)(((uint32_t)(x)) << MTBDWT_MASK_MASK_SHIFT)) & MTBDWT_MASK_MASK_MASK)
/*! @} */

/* The count of MTBDWT_MASK */
#define MTBDWT_MASK_COUNT                        (2U)

/*! @name FCT - MTB_DWT Comparator Function Register 0..MTB_DWT Comparator Function Register 1 */
/*! @{ */

#define MTBDWT_FCT_FUNCTION_MASK                 (0xFU)
#define MTBDWT_FCT_FUNCTION_SHIFT                (0U)
/*! FUNCTION - Function
 *  0b0000..Disabled.
 *  0b0100..Instruction fetch.
 *  0b0101..Data operand read.
 *  0b0110..Data operand write.
 *  0b0111..Data operand (read + write).
 */
#define MTBDWT_FCT_FUNCTION(x)                   (((uint32_t)(((uint32_t)(x)) << MTBDWT_FCT_FUNCTION_SHIFT)) & MTBDWT_FCT_FUNCTION_MASK)

#define MTBDWT_FCT_DATAVMATCH_MASK               (0x100U)
#define MTBDWT_FCT_DATAVMATCH_SHIFT              (8U)
/*! DATAVMATCH - Data Value Match
 *  0b0..Perform address comparison.
 *  0b1..Perform data value comparison.
 */
#define MTBDWT_FCT_DATAVMATCH(x)                 (((uint32_t)(((uint32_t)(x)) << MTBDWT_FCT_DATAVMATCH_SHIFT)) & MTBDWT_FCT_DATAVMATCH_MASK)

#define MTBDWT_FCT_DATAVSIZE_MASK                (0xC00U)
#define MTBDWT_FCT_DATAVSIZE_SHIFT               (10U)
/*! DATAVSIZE - Data Value Size
 *  0b00..Byte.
 *  0b01..Halfword.
 *  0b10..Word.
 *  0b11..Reserved. Any attempts to use this value results in UNPREDICTABLE behavior.
 */
#define MTBDWT_FCT_DATAVSIZE(x)                  (((uint32_t)(((uint32_t)(x)) << MTBDWT_FCT_DATAVSIZE_SHIFT)) & MTBDWT_FCT_DATAVSIZE_MASK)

#define MTBDWT_FCT_DATAVADDR0_MASK               (0xF000U)
#define MTBDWT_FCT_DATAVADDR0_SHIFT              (12U)
/*! DATAVADDR0 - Data Value Address 0 */
#define MTBDWT_FCT_DATAVADDR0(x)                 (((uint32_t)(((uint32_t)(x)) << MTBDWT_FCT_DATAVADDR0_SHIFT)) & MTBDWT_FCT_DATAVADDR0_MASK)

#define MTBDWT_FCT_MATCHED_MASK                  (0x1000000U)
#define MTBDWT_FCT_MATCHED_SHIFT                 (24U)
/*! MATCHED - Comparator match
 *  0b0..No match.
 *  0b1..Match occurred.
 */
#define MTBDWT_FCT_MATCHED(x)                    (((uint32_t)(((uint32_t)(x)) << MTBDWT_FCT_MATCHED_SHIFT)) & MTBDWT_FCT_MATCHED_MASK)
/*! @} */

/* The count of MTBDWT_FCT */
#define MTBDWT_FCT_COUNT                         (2U)

/*! @name TBCTRL - MTB_DWT Trace Buffer Control Register */
/*! @{ */

#define MTBDWT_TBCTRL_ACOMP0_MASK                (0x1U)
#define MTBDWT_TBCTRL_ACOMP0_SHIFT               (0U)
/*! ACOMP0 - Action based on Comparator 0 match
 *  0b0..Trigger TSTOP based on the assertion of MTBDWT_FCT0[MATCHED].
 *  0b1..Trigger TSTART based on the assertion of MTBDWT_FCT0[MATCHED].
 */
#define MTBDWT_TBCTRL_ACOMP0(x)                  (((uint32_t)(((uint32_t)(x)) << MTBDWT_TBCTRL_ACOMP0_SHIFT)) & MTBDWT_TBCTRL_ACOMP0_MASK)

#define MTBDWT_TBCTRL_ACOMP1_MASK                (0x2U)
#define MTBDWT_TBCTRL_ACOMP1_SHIFT               (1U)
/*! ACOMP1 - Action based on Comparator 1 match
 *  0b0..Trigger TSTOP based on the assertion of MTBDWT_FCT1[MATCHED].
 *  0b1..Trigger TSTART based on the assertion of MTBDWT_FCT1[MATCHED].
 */
#define MTBDWT_TBCTRL_ACOMP1(x)                  (((uint32_t)(((uint32_t)(x)) << MTBDWT_TBCTRL_ACOMP1_SHIFT)) & MTBDWT_TBCTRL_ACOMP1_MASK)

#define MTBDWT_TBCTRL_NUMCOMP_MASK               (0xF0000000U)
#define MTBDWT_TBCTRL_NUMCOMP_SHIFT              (28U)
/*! NUMCOMP - Number of Comparators */
#define MTBDWT_TBCTRL_NUMCOMP(x)                 (((uint32_t)(((uint32_t)(x)) << MTBDWT_TBCTRL_NUMCOMP_SHIFT)) & MTBDWT_TBCTRL_NUMCOMP_MASK)
/*! @} */

/*! @name DEVICECFG - Device Configuration Register */
/*! @{ */

#define MTBDWT_DEVICECFG_DEVICECFG_MASK          (0xFFFFFFFFU)
#define MTBDWT_DEVICECFG_DEVICECFG_SHIFT         (0U)
/*! DEVICECFG - DEVICECFG */
#define MTBDWT_DEVICECFG_DEVICECFG(x)            (((uint32_t)(((uint32_t)(x)) << MTBDWT_DEVICECFG_DEVICECFG_SHIFT)) & MTBDWT_DEVICECFG_DEVICECFG_MASK)
/*! @} */

/*! @name DEVICETYPID - Device Type Identifier Register */
/*! @{ */

#define MTBDWT_DEVICETYPID_DEVICETYPID_MASK      (0xFFFFFFFFU)
#define MTBDWT_DEVICETYPID_DEVICETYPID_SHIFT     (0U)
/*! DEVICETYPID - DEVICETYPID */
#define MTBDWT_DEVICETYPID_DEVICETYPID(x)        (((uint32_t)(((uint32_t)(x)) << MTBDWT_DEVICETYPID_DEVICETYPID_SHIFT)) & MTBDWT_DEVICETYPID_DEVICETYPID_MASK)
/*! @} */

/*! @name PERIPHID4 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID4_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID4_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID */
#define MTBDWT_PERIPHID4_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID4_PERIPHID_SHIFT)) & MTBDWT_PERIPHID4_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID5 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID5_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID5_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID */
#define MTBDWT_PERIPHID5_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID5_PERIPHID_SHIFT)) & MTBDWT_PERIPHID5_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID6 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID6_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID6_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID */
#define MTBDWT_PERIPHID6_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID6_PERIPHID_SHIFT)) & MTBDWT_PERIPHID6_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID7 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID7_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID7_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID */
#define MTBDWT_PERIPHID7_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID7_PERIPHID_SHIFT)) & MTBDWT_PERIPHID7_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID0 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID0_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID0_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID */
#define MTBDWT_PERIPHID0_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID0_PERIPHID_SHIFT)) & MTBDWT_PERIPHID0_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID1 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID1_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID1_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID */
#define MTBDWT_PERIPHID1_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID1_PERIPHID_SHIFT)) & MTBDWT_PERIPHID1_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID2 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID2_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID2_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID */
#define MTBDWT_PERIPHID2_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID2_PERIPHID_SHIFT)) & MTBDWT_PERIPHID2_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID3 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID3_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID3_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID */
#define MTBDWT_PERIPHID3_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID3_PERIPHID_SHIFT)) & MTBDWT_PERIPHID3_PERIPHID_MASK)
/*! @} */

/*! @name COMPID - Component ID Register */
/*! @{ */

#define MTBDWT_COMPID_COMPID_MASK                (0xFFFFFFFFU)
#define MTBDWT_COMPID_COMPID_SHIFT               (0U)
/*! COMPID - Component ID */
#define MTBDWT_COMPID_COMPID(x)                  (((uint32_t)(((uint32_t)(x)) << MTBDWT_COMPID_COMPID_SHIFT)) & MTBDWT_COMPID_COMPID_MASK)
/*! @} */

/* The count of MTBDWT_COMPID */
#define MTBDWT_COMPID_COUNT                      (4U)


/*!
 * @}
 */ /* end of group MTBDWT_Register_Masks */


/* MTBDWT - Peripheral instance base addresses */
/** Peripheral MTBDWT base address */
#define MTBDWT_BASE                              (0xF0001000u)
/** Peripheral MTBDWT base pointer */
#define MTBDWT                                   ((MTBDWT_Type *)MTBDWT_BASE)
/** Array initializer of MTBDWT peripheral base addresses */
#define MTBDWT_BASE_ADDRS                        { MTBDWT_BASE }
/** Array initializer of MTBDWT peripheral base pointers */
#define MTBDWT_BASE_PTRS                         { MTBDWT }

/*!
 * @}
 */ /* end of group MTBDWT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- NV Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Peripheral_Access_Layer NV Peripheral Access Layer
 * @{
 */

/** NV - Register Layout Typedef */
typedef struct {
  __I  uint8_t BACKKEY3;                           /**< Backdoor Comparison Key 3., offset: 0x0 */
  __I  uint8_t BACKKEY2;                           /**< Backdoor Comparison Key 2., offset: 0x1 */
  __I  uint8_t BACKKEY1;                           /**< Backdoor Comparison Key 1., offset: 0x2 */
  __I  uint8_t BACKKEY0;                           /**< Backdoor Comparison Key 0., offset: 0x3 */
  __I  uint8_t BACKKEY7;                           /**< Backdoor Comparison Key 7., offset: 0x4 */
  __I  uint8_t BACKKEY6;                           /**< Backdoor Comparison Key 6., offset: 0x5 */
  __I  uint8_t BACKKEY5;                           /**< Backdoor Comparison Key 5., offset: 0x6 */
  __I  uint8_t BACKKEY4;                           /**< Backdoor Comparison Key 4., offset: 0x7 */
  __I  uint8_t FPROT3;                             /**< Non-volatile P-Flash Protection 1 - Low Register, offset: 0x8 */
  __I  uint8_t FPROT2;                             /**< Non-volatile P-Flash Protection 1 - High Register, offset: 0x9 */
  __I  uint8_t FPROT1;                             /**< Non-volatile P-Flash Protection 0 - Low Register, offset: 0xA */
  __I  uint8_t FPROT0;                             /**< Non-volatile P-Flash Protection 0 - High Register, offset: 0xB */
  __I  uint8_t FSEC;                               /**< Non-volatile Flash Security Register, offset: 0xC */
  __I  uint8_t FOPT;                               /**< Non-volatile Flash Option Register, offset: 0xD */
} NV_Type;

/* ----------------------------------------------------------------------------
   -- NV Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Masks NV Register Masks
 * @{
 */

/*! @name BACKKEY3 - Backdoor Comparison Key 3. */
/*! @{ */

#define NV_BACKKEY3_KEY_MASK                     (0xFFU)
#define NV_BACKKEY3_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key. */
#define NV_BACKKEY3_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY3_KEY_SHIFT)) & NV_BACKKEY3_KEY_MASK)
/*! @} */

/*! @name BACKKEY2 - Backdoor Comparison Key 2. */
/*! @{ */

#define NV_BACKKEY2_KEY_MASK                     (0xFFU)
#define NV_BACKKEY2_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key. */
#define NV_BACKKEY2_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY2_KEY_SHIFT)) & NV_BACKKEY2_KEY_MASK)
/*! @} */

/*! @name BACKKEY1 - Backdoor Comparison Key 1. */
/*! @{ */

#define NV_BACKKEY1_KEY_MASK                     (0xFFU)
#define NV_BACKKEY1_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key. */
#define NV_BACKKEY1_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY1_KEY_SHIFT)) & NV_BACKKEY1_KEY_MASK)
/*! @} */

/*! @name BACKKEY0 - Backdoor Comparison Key 0. */
/*! @{ */

#define NV_BACKKEY0_KEY_MASK                     (0xFFU)
#define NV_BACKKEY0_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key. */
#define NV_BACKKEY0_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY0_KEY_SHIFT)) & NV_BACKKEY0_KEY_MASK)
/*! @} */

/*! @name BACKKEY7 - Backdoor Comparison Key 7. */
/*! @{ */

#define NV_BACKKEY7_KEY_MASK                     (0xFFU)
#define NV_BACKKEY7_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key. */
#define NV_BACKKEY7_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY7_KEY_SHIFT)) & NV_BACKKEY7_KEY_MASK)
/*! @} */

/*! @name BACKKEY6 - Backdoor Comparison Key 6. */
/*! @{ */

#define NV_BACKKEY6_KEY_MASK                     (0xFFU)
#define NV_BACKKEY6_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key. */
#define NV_BACKKEY6_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY6_KEY_SHIFT)) & NV_BACKKEY6_KEY_MASK)
/*! @} */

/*! @name BACKKEY5 - Backdoor Comparison Key 5. */
/*! @{ */

#define NV_BACKKEY5_KEY_MASK                     (0xFFU)
#define NV_BACKKEY5_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key. */
#define NV_BACKKEY5_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY5_KEY_SHIFT)) & NV_BACKKEY5_KEY_MASK)
/*! @} */

/*! @name BACKKEY4 - Backdoor Comparison Key 4. */
/*! @{ */

#define NV_BACKKEY4_KEY_MASK                     (0xFFU)
#define NV_BACKKEY4_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key. */
#define NV_BACKKEY4_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY4_KEY_SHIFT)) & NV_BACKKEY4_KEY_MASK)
/*! @} */

/*! @name FPROT3 - Non-volatile P-Flash Protection 1 - Low Register */
/*! @{ */

#define NV_FPROT3_PROT_MASK                      (0xFFU)
#define NV_FPROT3_PROT_SHIFT                     (0U)
/*! PROT - P-Flash Region Protect */
#define NV_FPROT3_PROT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FPROT3_PROT_SHIFT)) & NV_FPROT3_PROT_MASK)
/*! @} */

/*! @name FPROT2 - Non-volatile P-Flash Protection 1 - High Register */
/*! @{ */

#define NV_FPROT2_PROT_MASK                      (0xFFU)
#define NV_FPROT2_PROT_SHIFT                     (0U)
/*! PROT - P-Flash Region Protect */
#define NV_FPROT2_PROT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FPROT2_PROT_SHIFT)) & NV_FPROT2_PROT_MASK)
/*! @} */

/*! @name FPROT1 - Non-volatile P-Flash Protection 0 - Low Register */
/*! @{ */

#define NV_FPROT1_PROT_MASK                      (0xFFU)
#define NV_FPROT1_PROT_SHIFT                     (0U)
/*! PROT - P-Flash Region Protect */
#define NV_FPROT1_PROT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FPROT1_PROT_SHIFT)) & NV_FPROT1_PROT_MASK)
/*! @} */

/*! @name FPROT0 - Non-volatile P-Flash Protection 0 - High Register */
/*! @{ */

#define NV_FPROT0_PROT_MASK                      (0xFFU)
#define NV_FPROT0_PROT_SHIFT                     (0U)
/*! PROT - P-Flash Region Protect */
#define NV_FPROT0_PROT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FPROT0_PROT_SHIFT)) & NV_FPROT0_PROT_MASK)
/*! @} */

/*! @name FSEC - Non-volatile Flash Security Register */
/*! @{ */

#define NV_FSEC_SEC_MASK                         (0x3U)
#define NV_FSEC_SEC_SHIFT                        (0U)
/*! SEC - Flash Security
 *  0b10..MCU security status is unsecure
 *  0b11..MCU security status is secure
 */
#define NV_FSEC_SEC(x)                           (((uint8_t)(((uint8_t)(x)) << NV_FSEC_SEC_SHIFT)) & NV_FSEC_SEC_MASK)

#define NV_FSEC_FSLACC_MASK                      (0xCU)
#define NV_FSEC_FSLACC_SHIFT                     (2U)
/*! FSLACC - Freescale Failure Analysis Access Code
 *  0b10..Freescale factory access denied
 *  0b11..Freescale factory access granted
 */
#define NV_FSEC_FSLACC(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FSEC_FSLACC_SHIFT)) & NV_FSEC_FSLACC_MASK)

#define NV_FSEC_MEEN_MASK                        (0x30U)
#define NV_FSEC_MEEN_SHIFT                       (4U)
/*! MEEN
 *  0b10..Mass erase is disabled
 *  0b11..Mass erase is enabled
 */
#define NV_FSEC_MEEN(x)                          (((uint8_t)(((uint8_t)(x)) << NV_FSEC_MEEN_SHIFT)) & NV_FSEC_MEEN_MASK)

#define NV_FSEC_KEYEN_MASK                       (0xC0U)
#define NV_FSEC_KEYEN_SHIFT                      (6U)
/*! KEYEN - Backdoor Key Security Enable
 *  0b10..Backdoor key access enabled
 *  0b11..Backdoor key access disabled
 */
#define NV_FSEC_KEYEN(x)                         (((uint8_t)(((uint8_t)(x)) << NV_FSEC_KEYEN_SHIFT)) & NV_FSEC_KEYEN_MASK)
/*! @} */

/*! @name FOPT - Non-volatile Flash Option Register */
/*! @{ */

#define NV_FOPT_LPBOOT0_MASK                     (0x1U)
#define NV_FOPT_LPBOOT0_SHIFT                    (0U)
/*! LPBOOT0
 *  0b0..Core and system clock divider (OUTDIV1) is 0x7 (divide by 8) when LPBOOT1=0 or 0x1 (divide by 2) when LPBOOT1=1.
 *  0b1..Core and system clock divider (OUTDIV1) is 0x3 (divide by 4) when LPBOOT1=0 or 0x0 (divide by 1) when LPBOOT1=1.
 */
#define NV_FOPT_LPBOOT0(x)                       (((uint8_t)(((uint8_t)(x)) << NV_FOPT_LPBOOT0_SHIFT)) & NV_FOPT_LPBOOT0_MASK)

#define NV_FOPT_BOOTPIN_OPT_MASK                 (0x2U)
#define NV_FOPT_BOOTPIN_OPT_SHIFT                (1U)
/*! BOOTPIN_OPT
 *  0b0..Force Boot from ROM if BOOTCFG0 asserted, where BOOTCFG0 is the boot config function which is muxed with NMI pin
 *  0b1..Boot source configured by FOPT (BOOTSRC_SEL) bits
 */
#define NV_FOPT_BOOTPIN_OPT(x)                   (((uint8_t)(((uint8_t)(x)) << NV_FOPT_BOOTPIN_OPT_SHIFT)) & NV_FOPT_BOOTPIN_OPT_MASK)

#define NV_FOPT_NMI_DIS_MASK                     (0x4U)
#define NV_FOPT_NMI_DIS_SHIFT                    (2U)
/*! NMI_DIS
 *  0b0..NMI interrupts are always blocked
 *  0b1..NMI_b pin/interrupts reset default to enabled
 */
#define NV_FOPT_NMI_DIS(x)                       (((uint8_t)(((uint8_t)(x)) << NV_FOPT_NMI_DIS_SHIFT)) & NV_FOPT_NMI_DIS_MASK)

#define NV_FOPT_RESET_PIN_CFG_MASK               (0x8U)
#define NV_FOPT_RESET_PIN_CFG_SHIFT              (3U)
/*! RESET_PIN_CFG
 *  0b0..RESET pin is disabled following a POR and cannot be enabled as reset function
 *  0b1..RESET_b pin is dedicated
 */
#define NV_FOPT_RESET_PIN_CFG(x)                 (((uint8_t)(((uint8_t)(x)) << NV_FOPT_RESET_PIN_CFG_SHIFT)) & NV_FOPT_RESET_PIN_CFG_MASK)

#define NV_FOPT_LPBOOT1_MASK                     (0x10U)
#define NV_FOPT_LPBOOT1_SHIFT                    (4U)
/*! LPBOOT1
 *  0b0..Core and system clock divider (OUTDIV1) is 0x7 (divide by 8) when LPBOOT0=0 or 0x3 (divide by 4) when LPBOOT0=1.
 *  0b1..Core and system clock divider (OUTDIV1) is 0x1 (divide by 2) when LPBOOT0=0 or 0x0 (divide by 1) when LPBOOT0=1.
 */
#define NV_FOPT_LPBOOT1(x)                       (((uint8_t)(((uint8_t)(x)) << NV_FOPT_LPBOOT1_SHIFT)) & NV_FOPT_LPBOOT1_MASK)

#define NV_FOPT_FAST_INIT_MASK                   (0x20U)
#define NV_FOPT_FAST_INIT_SHIFT                  (5U)
/*! FAST_INIT
 *  0b0..Slower initialization
 *  0b1..Fast Initialization
 */
#define NV_FOPT_FAST_INIT(x)                     (((uint8_t)(((uint8_t)(x)) << NV_FOPT_FAST_INIT_SHIFT)) & NV_FOPT_FAST_INIT_MASK)

#define NV_FOPT_BOOTSRC_SEL_MASK                 (0xC0U)
#define NV_FOPT_BOOTSRC_SEL_SHIFT                (6U)
/*! BOOTSRC_SEL - Boot source selection
 *  0b00..Boot from Flash
 *  0b10..Boot from ROM
 *  0b11..Boot from ROM
 */
#define NV_FOPT_BOOTSRC_SEL(x)                   (((uint8_t)(((uint8_t)(x)) << NV_FOPT_BOOTSRC_SEL_SHIFT)) & NV_FOPT_BOOTSRC_SEL_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group NV_Register_Masks */


/* NV - Peripheral instance base addresses */
/** Peripheral FTFA_FlashConfig base address */
#define FTFA_FlashConfig_BASE                    (0x400u)
/** Peripheral FTFA_FlashConfig base pointer */
#define FTFA_FlashConfig                         ((NV_Type *)FTFA_FlashConfig_BASE)
/** Array initializer of NV peripheral base addresses */
#define NV_BASE_ADDRS                            { FTFA_FlashConfig_BASE }
/** Array initializer of NV peripheral base pointers */
#define NV_BASE_PTRS                             { FTFA_FlashConfig }

/*!
 * @}
 */ /* end of group NV_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- OSC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Peripheral_Access_Layer OSC Peripheral Access Layer
 * @{
 */

/** OSC - Register Layout Typedef */
typedef struct {
  __IO uint8_t CR;                                 /**< OSC Control Register, offset: 0x0 */
} OSC_Type;

/* ----------------------------------------------------------------------------
   -- OSC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Masks OSC Register Masks
 * @{
 */

/*! @name CR - OSC Control Register */
/*! @{ */

#define OSC_CR_SC16P_MASK                        (0x1U)
#define OSC_CR_SC16P_SHIFT                       (0U)
/*! SC16P - Oscillator 16 pF Capacitor Load Configure
 *  0b0..Disable the selection.
 *  0b1..Add 16 pF capacitor to the oscillator load.
 */
#define OSC_CR_SC16P(x)                          (((uint8_t)(((uint8_t)(x)) << OSC_CR_SC16P_SHIFT)) & OSC_CR_SC16P_MASK)

#define OSC_CR_SC8P_MASK                         (0x2U)
#define OSC_CR_SC8P_SHIFT                        (1U)
/*! SC8P - Oscillator 8 pF Capacitor Load Configure
 *  0b0..Disable the selection.
 *  0b1..Add 8 pF capacitor to the oscillator load.
 */
#define OSC_CR_SC8P(x)                           (((uint8_t)(((uint8_t)(x)) << OSC_CR_SC8P_SHIFT)) & OSC_CR_SC8P_MASK)

#define OSC_CR_SC4P_MASK                         (0x4U)
#define OSC_CR_SC4P_SHIFT                        (2U)
/*! SC4P - Oscillator 4 pF Capacitor Load Configure
 *  0b0..Disable the selection.
 *  0b1..Add 4 pF capacitor to the oscillator load.
 */
#define OSC_CR_SC4P(x)                           (((uint8_t)(((uint8_t)(x)) << OSC_CR_SC4P_SHIFT)) & OSC_CR_SC4P_MASK)

#define OSC_CR_SC2P_MASK                         (0x8U)
#define OSC_CR_SC2P_SHIFT                        (3U)
/*! SC2P - Oscillator 2 pF Capacitor Load Configure
 *  0b0..Disable the selection.
 *  0b1..Add 2 pF capacitor to the oscillator load.
 */
#define OSC_CR_SC2P(x)                           (((uint8_t)(((uint8_t)(x)) << OSC_CR_SC2P_SHIFT)) & OSC_CR_SC2P_MASK)

#define OSC_CR_EREFSTEN_MASK                     (0x20U)
#define OSC_CR_EREFSTEN_SHIFT                    (5U)
/*! EREFSTEN - External Reference Stop Enable
 *  0b0..External reference clock is disabled in Stop mode.
 *  0b1..External reference clock stays enabled in Stop mode if ERCLKEN is set before entering Stop mode.
 */
#define OSC_CR_EREFSTEN(x)                       (((uint8_t)(((uint8_t)(x)) << OSC_CR_EREFSTEN_SHIFT)) & OSC_CR_EREFSTEN_MASK)

#define OSC_CR_ERCLKEN_MASK                      (0x80U)
#define OSC_CR_ERCLKEN_SHIFT                     (7U)
/*! ERCLKEN - External Reference Enable
 *  0b0..External reference clock is inactive.
 *  0b1..External reference clock is enabled.
 */
#define OSC_CR_ERCLKEN(x)                        (((uint8_t)(((uint8_t)(x)) << OSC_CR_ERCLKEN_SHIFT)) & OSC_CR_ERCLKEN_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group OSC_Register_Masks */


/* OSC - Peripheral instance base addresses */
/** Peripheral OSC0 base address */
#define OSC0_BASE                                (0x40065000u)
/** Peripheral OSC0 base pointer */
#define OSC0                                     ((OSC_Type *)OSC0_BASE)
/** Array initializer of OSC peripheral base addresses */
#define OSC_BASE_ADDRS                           { OSC0_BASE }
/** Array initializer of OSC peripheral base pointers */
#define OSC_BASE_PTRS                            { OSC0 }

/*!
 * @}
 */ /* end of group OSC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PIT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Peripheral_Access_Layer PIT Peripheral Access Layer
 * @{
 */

/** PIT - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCR;                               /**< PIT Module Control Register, offset: 0x0 */
       uint8_t RESERVED_0[220];
  __I  uint32_t LTMR64H;                           /**< PIT Upper Lifetime Timer Register, offset: 0xE0 */
  __I  uint32_t LTMR64L;                           /**< PIT Lower Lifetime Timer Register, offset: 0xE4 */
       uint8_t RESERVED_1[24];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    __IO uint32_t LDVAL;                             /**< Timer Load Value Register, array offset: 0x100, array step: 0x10 */
    __I  uint32_t CVAL;                              /**< Current Timer Value Register, array offset: 0x104, array step: 0x10 */
    __IO uint32_t TCTRL;                             /**< Timer Control Register, array offset: 0x108, array step: 0x10 */
    __IO uint32_t TFLG;                              /**< Timer Flag Register, array offset: 0x10C, array step: 0x10 */
  } CHANNEL[2];
} PIT_Type;

/* ----------------------------------------------------------------------------
   -- PIT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Masks PIT Register Masks
 * @{
 */

/*! @name MCR - PIT Module Control Register */
/*! @{ */

#define PIT_MCR_FRZ_MASK                         (0x1U)
#define PIT_MCR_FRZ_SHIFT                        (0U)
/*! FRZ - Freeze
 *  0b0..Timers continue to run in Debug mode.
 *  0b1..Timers are stopped in Debug mode.
 */
#define PIT_MCR_FRZ(x)                           (((uint32_t)(((uint32_t)(x)) << PIT_MCR_FRZ_SHIFT)) & PIT_MCR_FRZ_MASK)

#define PIT_MCR_MDIS_MASK                        (0x2U)
#define PIT_MCR_MDIS_SHIFT                       (1U)
/*! MDIS - Module Disable - (PIT section)
 *  0b0..Clock for standard PIT timers is enabled.
 *  0b1..Clock for standard PIT timers is disabled.
 */
#define PIT_MCR_MDIS(x)                          (((uint32_t)(((uint32_t)(x)) << PIT_MCR_MDIS_SHIFT)) & PIT_MCR_MDIS_MASK)
/*! @} */

/*! @name LTMR64H - PIT Upper Lifetime Timer Register */
/*! @{ */

#define PIT_LTMR64H_LTH_MASK                     (0xFFFFFFFFU)
#define PIT_LTMR64H_LTH_SHIFT                    (0U)
/*! LTH - Life Timer value */
#define PIT_LTMR64H_LTH(x)                       (((uint32_t)(((uint32_t)(x)) << PIT_LTMR64H_LTH_SHIFT)) & PIT_LTMR64H_LTH_MASK)
/*! @} */

/*! @name LTMR64L - PIT Lower Lifetime Timer Register */
/*! @{ */

#define PIT_LTMR64L_LTL_MASK                     (0xFFFFFFFFU)
#define PIT_LTMR64L_LTL_SHIFT                    (0U)
/*! LTL - Life Timer value */
#define PIT_LTMR64L_LTL(x)                       (((uint32_t)(((uint32_t)(x)) << PIT_LTMR64L_LTL_SHIFT)) & PIT_LTMR64L_LTL_MASK)
/*! @} */

/*! @name LDVAL - Timer Load Value Register */
/*! @{ */

#define PIT_LDVAL_TSV_MASK                       (0xFFFFFFFFU)
#define PIT_LDVAL_TSV_SHIFT                      (0U)
/*! TSV - Timer Start Value */
#define PIT_LDVAL_TSV(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_LDVAL_TSV_SHIFT)) & PIT_LDVAL_TSV_MASK)
/*! @} */

/* The count of PIT_LDVAL */
#define PIT_LDVAL_COUNT                          (2U)

/*! @name CVAL - Current Timer Value Register */
/*! @{ */

#define PIT_CVAL_TVL_MASK                        (0xFFFFFFFFU)
#define PIT_CVAL_TVL_SHIFT                       (0U)
/*! TVL - Current Timer Value */
#define PIT_CVAL_TVL(x)                          (((uint32_t)(((uint32_t)(x)) << PIT_CVAL_TVL_SHIFT)) & PIT_CVAL_TVL_MASK)
/*! @} */

/* The count of PIT_CVAL */
#define PIT_CVAL_COUNT                           (2U)

/*! @name TCTRL - Timer Control Register */
/*! @{ */

#define PIT_TCTRL_TEN_MASK                       (0x1U)
#define PIT_TCTRL_TEN_SHIFT                      (0U)
/*! TEN - Timer Enable
 *  0b0..Timer n is disabled.
 *  0b1..Timer n is enabled.
 */
#define PIT_TCTRL_TEN(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_TCTRL_TEN_SHIFT)) & PIT_TCTRL_TEN_MASK)

#define PIT_TCTRL_TIE_MASK                       (0x2U)
#define PIT_TCTRL_TIE_SHIFT                      (1U)
/*! TIE - Timer Interrupt Enable
 *  0b0..Interrupt requests from Timer n are disabled.
 *  0b1..Interrupt will be requested whenever TIF is set.
 */
#define PIT_TCTRL_TIE(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_TCTRL_TIE_SHIFT)) & PIT_TCTRL_TIE_MASK)

#define PIT_TCTRL_CHN_MASK                       (0x4U)
#define PIT_TCTRL_CHN_SHIFT                      (2U)
/*! CHN - Chain Mode
 *  0b0..Timer is not chained.
 *  0b1..Timer is chained to previous timer. For example, for Channel 2, if this field is set, Timer 2 is chained to Timer 1.
 */
#define PIT_TCTRL_CHN(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_TCTRL_CHN_SHIFT)) & PIT_TCTRL_CHN_MASK)
/*! @} */

/* The count of PIT_TCTRL */
#define PIT_TCTRL_COUNT                          (2U)

/*! @name TFLG - Timer Flag Register */
/*! @{ */

#define PIT_TFLG_TIF_MASK                        (0x1U)
#define PIT_TFLG_TIF_SHIFT                       (0U)
/*! TIF - Timer Interrupt Flag
 *  0b0..Timeout has not yet occurred.
 *  0b1..Timeout has occurred.
 */
#define PIT_TFLG_TIF(x)                          (((uint32_t)(((uint32_t)(x)) << PIT_TFLG_TIF_SHIFT)) & PIT_TFLG_TIF_MASK)
/*! @} */

/* The count of PIT_TFLG */
#define PIT_TFLG_COUNT                           (2U)


/*!
 * @}
 */ /* end of group PIT_Register_Masks */


/* PIT - Peripheral instance base addresses */
/** Peripheral PIT base address */
#define PIT_BASE                                 (0x40037000u)
/** Peripheral PIT base pointer */
#define PIT                                      ((PIT_Type *)PIT_BASE)
/** Array initializer of PIT peripheral base addresses */
#define PIT_BASE_ADDRS                           { PIT_BASE }
/** Array initializer of PIT peripheral base pointers */
#define PIT_BASE_PTRS                            { PIT }
/** Interrupt vectors for the PIT peripheral type */
#define PIT_IRQS                                 { { PIT_IRQn, PIT_IRQn } }

/*!
 * @}
 */ /* end of group PIT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Peripheral_Access_Layer PMC Peripheral Access Layer
 * @{
 */

/** PMC - Register Layout Typedef */
typedef struct {
  __IO uint8_t LVDSC1;                             /**< Low Voltage Detect Status And Control 1 register, offset: 0x0 */
  __IO uint8_t LVDSC2;                             /**< Low Voltage Detect Status And Control 2 register, offset: 0x1 */
  __IO uint8_t REGSC;                              /**< Regulator Status And Control register, offset: 0x2 */
} PMC_Type;

/* ----------------------------------------------------------------------------
   -- PMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Masks PMC Register Masks
 * @{
 */

/*! @name LVDSC1 - Low Voltage Detect Status And Control 1 register */
/*! @{ */

#define PMC_LVDSC1_LVDV_MASK                     (0x3U)
#define PMC_LVDSC1_LVDV_SHIFT                    (0U)
/*! LVDV - Low-Voltage Detect Voltage Select
 *  0b00..Low trip point selected (V LVD = V LVDL )
 *  0b01..High trip point selected (V LVD = V LVDH )
 *  0b10..Reserved
 *  0b11..Reserved
 */
#define PMC_LVDSC1_LVDV(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDV_SHIFT)) & PMC_LVDSC1_LVDV_MASK)

#define PMC_LVDSC1_LVDRE_MASK                    (0x10U)
#define PMC_LVDSC1_LVDRE_SHIFT                   (4U)
/*! LVDRE - Low-Voltage Detect Reset Enable
 *  0b0..LVDF does not generate hardware resets
 *  0b1..Force an MCU reset when LVDF = 1
 */
#define PMC_LVDSC1_LVDRE(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDRE_SHIFT)) & PMC_LVDSC1_LVDRE_MASK)

#define PMC_LVDSC1_LVDIE_MASK                    (0x20U)
#define PMC_LVDSC1_LVDIE_SHIFT                   (5U)
/*! LVDIE - Low-Voltage Detect Interrupt Enable
 *  0b0..Hardware interrupt disabled (use polling)
 *  0b1..Request a hardware interrupt when LVDF = 1
 */
#define PMC_LVDSC1_LVDIE(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDIE_SHIFT)) & PMC_LVDSC1_LVDIE_MASK)

#define PMC_LVDSC1_LVDACK_MASK                   (0x40U)
#define PMC_LVDSC1_LVDACK_SHIFT                  (6U)
/*! LVDACK - Low-Voltage Detect Acknowledge */
#define PMC_LVDSC1_LVDACK(x)                     (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDACK_SHIFT)) & PMC_LVDSC1_LVDACK_MASK)

#define PMC_LVDSC1_LVDF_MASK                     (0x80U)
#define PMC_LVDSC1_LVDF_SHIFT                    (7U)
/*! LVDF - Low-Voltage Detect Flag
 *  0b0..Low-voltage event not detected
 *  0b1..Low-voltage event detected
 */
#define PMC_LVDSC1_LVDF(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDF_SHIFT)) & PMC_LVDSC1_LVDF_MASK)
/*! @} */

/*! @name LVDSC2 - Low Voltage Detect Status And Control 2 register */
/*! @{ */

#define PMC_LVDSC2_LVWV_MASK                     (0x3U)
#define PMC_LVDSC2_LVWV_SHIFT                    (0U)
/*! LVWV - Low-Voltage Warning Voltage Select
 *  0b00..Low trip point selected (VLVW = VLVW1)
 *  0b01..Mid 1 trip point selected (VLVW = VLVW2)
 *  0b10..Mid 2 trip point selected (VLVW = VLVW3)
 *  0b11..High trip point selected (VLVW = VLVW4)
 */
#define PMC_LVDSC2_LVWV(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC2_LVWV_SHIFT)) & PMC_LVDSC2_LVWV_MASK)

#define PMC_LVDSC2_LVWIE_MASK                    (0x20U)
#define PMC_LVDSC2_LVWIE_SHIFT                   (5U)
/*! LVWIE - Low-Voltage Warning Interrupt Enable
 *  0b0..Hardware interrupt disabled (use polling)
 *  0b1..Request a hardware interrupt when LVWF = 1
 */
#define PMC_LVDSC2_LVWIE(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC2_LVWIE_SHIFT)) & PMC_LVDSC2_LVWIE_MASK)

#define PMC_LVDSC2_LVWACK_MASK                   (0x40U)
#define PMC_LVDSC2_LVWACK_SHIFT                  (6U)
/*! LVWACK - Low-Voltage Warning Acknowledge */
#define PMC_LVDSC2_LVWACK(x)                     (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC2_LVWACK_SHIFT)) & PMC_LVDSC2_LVWACK_MASK)

#define PMC_LVDSC2_LVWF_MASK                     (0x80U)
#define PMC_LVDSC2_LVWF_SHIFT                    (7U)
/*! LVWF - Low-Voltage Warning Flag
 *  0b0..Low-voltage warning event not detected
 *  0b1..Low-voltage warning event detected
 */
#define PMC_LVDSC2_LVWF(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC2_LVWF_SHIFT)) & PMC_LVDSC2_LVWF_MASK)
/*! @} */

/*! @name REGSC - Regulator Status And Control register */
/*! @{ */

#define PMC_REGSC_BGBE_MASK                      (0x1U)
#define PMC_REGSC_BGBE_SHIFT                     (0U)
/*! BGBE - Bandgap Buffer Enable
 *  0b0..Bandgap buffer not enabled
 *  0b1..Bandgap buffer enabled
 */
#define PMC_REGSC_BGBE(x)                        (((uint8_t)(((uint8_t)(x)) << PMC_REGSC_BGBE_SHIFT)) & PMC_REGSC_BGBE_MASK)

#define PMC_REGSC_REGONS_MASK                    (0x4U)
#define PMC_REGSC_REGONS_SHIFT                   (2U)
/*! REGONS - Regulator In Run Regulation Status
 *  0b0..Regulator is in stop regulation or in transition to/from it
 *  0b1..Regulator is in run regulation
 */
#define PMC_REGSC_REGONS(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_REGSC_REGONS_SHIFT)) & PMC_REGSC_REGONS_MASK)

#define PMC_REGSC_ACKISO_MASK                    (0x8U)
#define PMC_REGSC_ACKISO_SHIFT                   (3U)
/*! ACKISO - Acknowledge Isolation
 *  0b0..Peripherals and I/O pads are in normal run state.
 *  0b1..Certain peripherals and I/O pads are in an isolated and latched state.
 */
#define PMC_REGSC_ACKISO(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_REGSC_ACKISO_SHIFT)) & PMC_REGSC_ACKISO_MASK)

#define PMC_REGSC_BGEN_MASK                      (0x10U)
#define PMC_REGSC_BGEN_SHIFT                     (4U)
/*! BGEN - Bandgap Enable In VLPx Operation
 *  0b0..Bandgap voltage reference is disabled in VLPx , LLS , and VLLSx modes.
 *  0b1..Bandgap voltage reference is enabled in VLPx , LLS , and VLLSx modes.
 */
#define PMC_REGSC_BGEN(x)                        (((uint8_t)(((uint8_t)(x)) << PMC_REGSC_BGEN_SHIFT)) & PMC_REGSC_BGEN_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PMC_Register_Masks */


/* PMC - Peripheral instance base addresses */
/** Peripheral PMC base address */
#define PMC_BASE                                 (0x4007D000u)
/** Peripheral PMC base pointer */
#define PMC                                      ((PMC_Type *)PMC_BASE)
/** Array initializer of PMC peripheral base addresses */
#define PMC_BASE_ADDRS                           { PMC_BASE }
/** Array initializer of PMC peripheral base pointers */
#define PMC_BASE_PTRS                            { PMC }
/** Interrupt vectors for the PMC peripheral type */
#define PMC_IRQS                                 { PMC_IRQn }

/*!
 * @}
 */ /* end of group PMC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PORT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Peripheral_Access_Layer PORT Peripheral Access Layer
 * @{
 */

/** PORT - Register Layout Typedef */
typedef struct {
  __IO uint32_t PCR[32];                           /**< Pin Control Register n, array offset: 0x0, array step: 0x4 */
  __O  uint32_t GPCLR;                             /**< Global Pin Control Low Register, offset: 0x80 */
  __O  uint32_t GPCHR;                             /**< Global Pin Control High Register, offset: 0x84 */
       uint8_t RESERVED_0[24];
  __IO uint32_t ISFR;                              /**< Interrupt Status Flag Register, offset: 0xA0 */
} PORT_Type;

/* ----------------------------------------------------------------------------
   -- PORT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Masks PORT Register Masks
 * @{
 */

/*! @name PCR - Pin Control Register n */
/*! @{ */

#define PORT_PCR_PS_MASK                         (0x1U)
#define PORT_PCR_PS_SHIFT                        (0U)
/*! PS - Pull Select
 *  0b0..Internal pulldown resistor is enabled on the corresponding pin, if the corresponding PE field is set.
 *  0b1..Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set.
 */
#define PORT_PCR_PS(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PS_SHIFT)) & PORT_PCR_PS_MASK)

#define PORT_PCR_PE_MASK                         (0x2U)
#define PORT_PCR_PE_SHIFT                        (1U)
/*! PE - Pull Enable
 *  0b0..Internal pullup or pulldown resistor is not enabled on the corresponding pin.
 *  0b1..Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is configured as a digital input.
 */
#define PORT_PCR_PE(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PE_SHIFT)) & PORT_PCR_PE_MASK)

#define PORT_PCR_SRE_MASK                        (0x4U)
#define PORT_PCR_SRE_SHIFT                       (2U)
/*! SRE - Slew Rate Enable
 *  0b0..Fast slew rate is configured on the corresponding pin, if the pin is configured as a digital output.
 *  0b1..Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output.
 */
#define PORT_PCR_SRE(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_SRE_SHIFT)) & PORT_PCR_SRE_MASK)

#define PORT_PCR_PFE_MASK                        (0x10U)
#define PORT_PCR_PFE_SHIFT                       (4U)
/*! PFE - Passive Filter Enable
 *  0b0..Passive input filter is disabled on the corresponding pin.
 *  0b1..Passive input filter is enabled on the corresponding pin, if the pin is configured as a digital input.
 *       Refer to the device data sheet for filter characteristics.
 */
#define PORT_PCR_PFE(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PFE_SHIFT)) & PORT_PCR_PFE_MASK)

#define PORT_PCR_DSE_MASK                        (0x40U)
#define PORT_PCR_DSE_SHIFT                       (6U)
/*! DSE - Drive Strength Enable
 *  0b0..Low drive strength is configured on the corresponding pin, if pin is configured as a digital output.
 *  0b1..High drive strength is configured on the corresponding pin, if pin is configured as a digital output.
 */
#define PORT_PCR_DSE(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_DSE_SHIFT)) & PORT_PCR_DSE_MASK)

#define PORT_PCR_MUX_MASK                        (0x700U)
#define PORT_PCR_MUX_SHIFT                       (8U)
/*! MUX - Pin Mux Control
 *  0b000..Pin disabled (analog).
 *  0b001..Alternative 1 (GPIO).
 *  0b010..Alternative 2 (chip-specific).
 *  0b011..Alternative 3 (chip-specific).
 *  0b100..Alternative 4 (chip-specific).
 *  0b101..Alternative 5 (chip-specific).
 *  0b110..Alternative 6 (chip-specific).
 *  0b111..Alternative 7 (chip-specific).
 */
#define PORT_PCR_MUX(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_MUX_SHIFT)) & PORT_PCR_MUX_MASK)

#define PORT_PCR_IRQC_MASK                       (0xF0000U)
#define PORT_PCR_IRQC_SHIFT                      (16U)
/*! IRQC - Interrupt Configuration
 *  0b0000..Interrupt/DMA request disabled.
 *  0b0001..DMA request on rising edge.
 *  0b0010..DMA request on falling edge.
 *  0b0011..DMA request on either edge.
 *  0b1000..Interrupt when logic 0.
 *  0b1001..Interrupt on rising-edge.
 *  0b1010..Interrupt on falling-edge.
 *  0b1011..Interrupt on either edge.
 *  0b1100..Interrupt when logic 1.
 */
#define PORT_PCR_IRQC(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_PCR_IRQC_SHIFT)) & PORT_PCR_IRQC_MASK)

#define PORT_PCR_ISF_MASK                        (0x1000000U)
#define PORT_PCR_ISF_SHIFT                       (24U)
/*! ISF - Interrupt Status Flag
 *  0b0..Configured interrupt is not detected.
 *  0b1..Configured interrupt is detected. If the pin is configured to generate a DMA request, then the
 *       corresponding flag will be cleared automatically at the completion of the requested DMA transfer. Otherwise, the
 *       flag remains set until a logic 1 is written to the flag. If the pin is configured for a level sensitive
 *       interrupt and the pin remains asserted, then the flag is set again immediately after it is cleared.
 */
#define PORT_PCR_ISF(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_ISF_SHIFT)) & PORT_PCR_ISF_MASK)
/*! @} */

/* The count of PORT_PCR */
#define PORT_PCR_COUNT                           (32U)

/*! @name GPCLR - Global Pin Control Low Register */
/*! @{ */

#define PORT_GPCLR_GPWD_MASK                     (0xFFFFU)
#define PORT_GPCLR_GPWD_SHIFT                    (0U)
/*! GPWD - Global Pin Write Data */
#define PORT_GPCLR_GPWD(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCLR_GPWD_SHIFT)) & PORT_GPCLR_GPWD_MASK)

#define PORT_GPCLR_GPWE_MASK                     (0xFFFF0000U)
#define PORT_GPCLR_GPWE_SHIFT                    (16U)
/*! GPWE - Global Pin Write Enable
 *  0b0000000000000000..Corresponding Pin Control Register is not updated with the value in GPWD.
 *  0b0000000000000001..Corresponding Pin Control Register is updated with the value in GPWD.
 */
#define PORT_GPCLR_GPWE(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCLR_GPWE_SHIFT)) & PORT_GPCLR_GPWE_MASK)
/*! @} */

/*! @name GPCHR - Global Pin Control High Register */
/*! @{ */

#define PORT_GPCHR_GPWD_MASK                     (0xFFFFU)
#define PORT_GPCHR_GPWD_SHIFT                    (0U)
/*! GPWD - Global Pin Write Data */
#define PORT_GPCHR_GPWD(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCHR_GPWD_SHIFT)) & PORT_GPCHR_GPWD_MASK)

#define PORT_GPCHR_GPWE_MASK                     (0xFFFF0000U)
#define PORT_GPCHR_GPWE_SHIFT                    (16U)
/*! GPWE - Global Pin Write Enable
 *  0b0000000000000000..Corresponding Pin Control Register is not updated with the value in GPWD.
 *  0b0000000000000001..Corresponding Pin Control Register is updated with the value in GPWD.
 */
#define PORT_GPCHR_GPWE(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCHR_GPWE_SHIFT)) & PORT_GPCHR_GPWE_MASK)
/*! @} */

/*! @name ISFR - Interrupt Status Flag Register */
/*! @{ */

#define PORT_ISFR_ISF_MASK                       (0xFFFFFFFFU)
#define PORT_ISFR_ISF_SHIFT                      (0U)
/*! ISF - Interrupt Status Flag
 *  0b00000000000000000000000000000000..Configured interrupt is not detected.
 *  0b00000000000000000000000000000001..Configured interrupt is detected. If the pin is configured to generate a
 *                                      DMA request, then the corresponding flag will be cleared automatically at
 *                                      the completion of the requested DMA transfer. Otherwise, the flag remains set
 *                                      until a logic 1 is written to the flag. If the pin is configured for a
 *                                      level sensitive interrupt and the pin remains asserted, then the flag is set
 *                                      again immediately after it is cleared.
 */
#define PORT_ISFR_ISF(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_ISFR_ISF_SHIFT)) & PORT_ISFR_ISF_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PORT_Register_Masks */


/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base address */
#define PORTA_BASE                               (0x40049000u)
/** Peripheral PORTA base pointer */
#define PORTA                                    ((PORT_Type *)PORTA_BASE)
/** Peripheral PORTB base address */
#define PORTB_BASE                               (0x4004A000u)
/** Peripheral PORTB base pointer */
#define PORTB                                    ((PORT_Type *)PORTB_BASE)
/** Peripheral PORTC base address */
#define PORTC_BASE                               (0x4004B000u)
/** Peripheral PORTC base pointer */
#define PORTC                                    ((PORT_Type *)PORTC_BASE)
/** Peripheral PORTD base address */
#define PORTD_BASE                               (0x4004C000u)
/** Peripheral PORTD base pointer */
#define PORTD                                    ((PORT_Type *)PORTD_BASE)
/** Peripheral PORTE base address */
#define PORTE_BASE                               (0x4004D000u)
/** Peripheral PORTE base pointer */
#define PORTE                                    ((PORT_Type *)PORTE_BASE)
/** Array initializer of PORT peripheral base addresses */
#define PORT_BASE_ADDRS                          { PORTA_BASE, PORTB_BASE, PORTC_BASE, PORTD_BASE, PORTE_BASE }
/** Array initializer of PORT peripheral base pointers */
#define PORT_BASE_PTRS                           { PORTA, PORTB, PORTC, PORTD, PORTE }
/** Interrupt vectors for the PORT peripheral type */
#define PORT_IRQS                                { PORTA_IRQn, NotAvail_IRQn, PORTC_PORTD_IRQn, PORTC_PORTD_IRQn, NotAvail_IRQn }

/*!
 * @}
 */ /* end of group PORT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Peripheral_Access_Layer RCM Peripheral Access Layer
 * @{
 */

/** RCM - Register Layout Typedef */
typedef struct {
  __I  uint8_t SRS0;                               /**< System Reset Status Register 0, offset: 0x0 */
  __I  uint8_t SRS1;                               /**< System Reset Status Register 1, offset: 0x1 */
       uint8_t RESERVED_0[2];
  __IO uint8_t RPFC;                               /**< Reset Pin Filter Control register, offset: 0x4 */
  __IO uint8_t RPFW;                               /**< Reset Pin Filter Width register, offset: 0x5 */
  __IO uint8_t FM;                                 /**< Force Mode Register, offset: 0x6 */
  __IO uint8_t MR;                                 /**< Mode Register, offset: 0x7 */
  __IO uint8_t SSRS0;                              /**< Sticky System Reset Status Register 0, offset: 0x8 */
  __IO uint8_t SSRS1;                              /**< Sticky System Reset Status Register 1, offset: 0x9 */
} RCM_Type;

/* ----------------------------------------------------------------------------
   -- RCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Register_Masks RCM Register Masks
 * @{
 */

/*! @name SRS0 - System Reset Status Register 0 */
/*! @{ */

#define RCM_SRS0_WAKEUP_MASK                     (0x1U)
#define RCM_SRS0_WAKEUP_SHIFT                    (0U)
/*! WAKEUP - Low Leakage Wakeup Reset
 *  0b0..Reset not caused by LLWU module wakeup source
 *  0b1..Reset caused by LLWU module wakeup source
 */
#define RCM_SRS0_WAKEUP(x)                       (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_WAKEUP_SHIFT)) & RCM_SRS0_WAKEUP_MASK)

#define RCM_SRS0_LVD_MASK                        (0x2U)
#define RCM_SRS0_LVD_SHIFT                       (1U)
/*! LVD - Low-Voltage Detect Reset
 *  0b0..Reset not caused by LVD trip or POR
 *  0b1..Reset caused by LVD trip or POR
 */
#define RCM_SRS0_LVD(x)                          (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_LVD_SHIFT)) & RCM_SRS0_LVD_MASK)

#define RCM_SRS0_WDOG_MASK                       (0x20U)
#define RCM_SRS0_WDOG_SHIFT                      (5U)
/*! WDOG - Watchdog
 *  0b0..Reset not caused by watchdog timeout
 *  0b1..Reset caused by watchdog timeout
 */
#define RCM_SRS0_WDOG(x)                         (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_WDOG_SHIFT)) & RCM_SRS0_WDOG_MASK)

#define RCM_SRS0_PIN_MASK                        (0x40U)
#define RCM_SRS0_PIN_SHIFT                       (6U)
/*! PIN - External Reset Pin
 *  0b0..Reset not caused by external reset pin
 *  0b1..Reset caused by external reset pin
 */
#define RCM_SRS0_PIN(x)                          (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_PIN_SHIFT)) & RCM_SRS0_PIN_MASK)

#define RCM_SRS0_POR_MASK                        (0x80U)
#define RCM_SRS0_POR_SHIFT                       (7U)
/*! POR - Power-On Reset
 *  0b0..Reset not caused by POR
 *  0b1..Reset caused by POR
 */
#define RCM_SRS0_POR(x)                          (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_POR_SHIFT)) & RCM_SRS0_POR_MASK)
/*! @} */

/*! @name SRS1 - System Reset Status Register 1 */
/*! @{ */

#define RCM_SRS1_LOCKUP_MASK                     (0x2U)
#define RCM_SRS1_LOCKUP_SHIFT                    (1U)
/*! LOCKUP - Core Lockup
 *  0b0..Reset not caused by core LOCKUP event
 *  0b1..Reset caused by core LOCKUP event
 */
#define RCM_SRS1_LOCKUP(x)                       (((uint8_t)(((uint8_t)(x)) << RCM_SRS1_LOCKUP_SHIFT)) & RCM_SRS1_LOCKUP_MASK)

#define RCM_SRS1_SW_MASK                         (0x4U)
#define RCM_SRS1_SW_SHIFT                        (2U)
/*! SW - Software
 *  0b0..Reset not caused by software setting of SYSRESETREQ bit
 *  0b1..Reset caused by software setting of SYSRESETREQ bit
 */
#define RCM_SRS1_SW(x)                           (((uint8_t)(((uint8_t)(x)) << RCM_SRS1_SW_SHIFT)) & RCM_SRS1_SW_MASK)

#define RCM_SRS1_MDM_AP_MASK                     (0x8U)
#define RCM_SRS1_MDM_AP_SHIFT                    (3U)
/*! MDM_AP - MDM-AP System Reset Request
 *  0b0..Reset not caused by host debugger system setting of the System Reset Request bit
 *  0b1..Reset caused by host debugger system setting of the System Reset Request bit
 */
#define RCM_SRS1_MDM_AP(x)                       (((uint8_t)(((uint8_t)(x)) << RCM_SRS1_MDM_AP_SHIFT)) & RCM_SRS1_MDM_AP_MASK)

#define RCM_SRS1_SACKERR_MASK                    (0x20U)
#define RCM_SRS1_SACKERR_SHIFT                   (5U)
/*! SACKERR - Stop Mode Acknowledge Error Reset
 *  0b0..Reset not caused by peripheral failure to acknowledge attempt to enter stop mode
 *  0b1..Reset caused by peripheral failure to acknowledge attempt to enter stop mode
 */
#define RCM_SRS1_SACKERR(x)                      (((uint8_t)(((uint8_t)(x)) << RCM_SRS1_SACKERR_SHIFT)) & RCM_SRS1_SACKERR_MASK)
/*! @} */

/*! @name RPFC - Reset Pin Filter Control register */
/*! @{ */

#define RCM_RPFC_RSTFLTSRW_MASK                  (0x3U)
#define RCM_RPFC_RSTFLTSRW_SHIFT                 (0U)
/*! RSTFLTSRW - Reset Pin Filter Select in Run and Wait Modes
 *  0b00..All filtering disabled
 *  0b01..Bus clock filter enabled for normal operation
 *  0b10..LPO clock filter enabled for normal operation
 *  0b11..Reserved
 */
#define RCM_RPFC_RSTFLTSRW(x)                    (((uint8_t)(((uint8_t)(x)) << RCM_RPFC_RSTFLTSRW_SHIFT)) & RCM_RPFC_RSTFLTSRW_MASK)

#define RCM_RPFC_RSTFLTSS_MASK                   (0x4U)
#define RCM_RPFC_RSTFLTSS_SHIFT                  (2U)
/*! RSTFLTSS - Reset Pin Filter Select in Stop Mode
 *  0b0..All filtering disabled
 *  0b1..LPO clock filter enabled
 */
#define RCM_RPFC_RSTFLTSS(x)                     (((uint8_t)(((uint8_t)(x)) << RCM_RPFC_RSTFLTSS_SHIFT)) & RCM_RPFC_RSTFLTSS_MASK)
/*! @} */

/*! @name RPFW - Reset Pin Filter Width register */
/*! @{ */

#define RCM_RPFW_RSTFLTSEL_MASK                  (0x1FU)
#define RCM_RPFW_RSTFLTSEL_SHIFT                 (0U)
/*! RSTFLTSEL - Reset Pin Filter Bus Clock Select
 *  0b00000..Bus clock filter count is 1
 *  0b00001..Bus clock filter count is 2
 *  0b00010..Bus clock filter count is 3
 *  0b00011..Bus clock filter count is 4
 *  0b00100..Bus clock filter count is 5
 *  0b00101..Bus clock filter count is 6
 *  0b00110..Bus clock filter count is 7
 *  0b00111..Bus clock filter count is 8
 *  0b01000..Bus clock filter count is 9
 *  0b01001..Bus clock filter count is 10
 *  0b01010..Bus clock filter count is 11
 *  0b01011..Bus clock filter count is 12
 *  0b01100..Bus clock filter count is 13
 *  0b01101..Bus clock filter count is 14
 *  0b01110..Bus clock filter count is 15
 *  0b01111..Bus clock filter count is 16
 *  0b10000..Bus clock filter count is 17
 *  0b10001..Bus clock filter count is 18
 *  0b10010..Bus clock filter count is 19
 *  0b10011..Bus clock filter count is 20
 *  0b10100..Bus clock filter count is 21
 *  0b10101..Bus clock filter count is 22
 *  0b10110..Bus clock filter count is 23
 *  0b10111..Bus clock filter count is 24
 *  0b11000..Bus clock filter count is 25
 *  0b11001..Bus clock filter count is 26
 *  0b11010..Bus clock filter count is 27
 *  0b11011..Bus clock filter count is 28
 *  0b11100..Bus clock filter count is 29
 *  0b11101..Bus clock filter count is 30
 *  0b11110..Bus clock filter count is 31
 *  0b11111..Bus clock filter count is 32
 */
#define RCM_RPFW_RSTFLTSEL(x)                    (((uint8_t)(((uint8_t)(x)) << RCM_RPFW_RSTFLTSEL_SHIFT)) & RCM_RPFW_RSTFLTSEL_MASK)
/*! @} */

/*! @name FM - Force Mode Register */
/*! @{ */

#define RCM_FM_FORCEROM_MASK                     (0x6U)
#define RCM_FM_FORCEROM_SHIFT                    (1U)
/*! FORCEROM - Force ROM Boot
 *  0b00..No effect
 *  0b01..Force boot from ROM with RCM_MR[1] set.
 *  0b10..Force boot from ROM with RCM_MR[2] set.
 *  0b11..Force boot from ROM with RCM_MR[2:1] set.
 */
#define RCM_FM_FORCEROM(x)                       (((uint8_t)(((uint8_t)(x)) << RCM_FM_FORCEROM_SHIFT)) & RCM_FM_FORCEROM_MASK)
/*! @} */

/*! @name MR - Mode Register */
/*! @{ */

#define RCM_MR_BOOTROM_MASK                      (0x6U)
#define RCM_MR_BOOTROM_SHIFT                     (1U)
/*! BOOTROM - Boot ROM Configuration
 *  0b00..Boot from Flash
 *  0b01..Boot from ROM due to BOOTCFG0 pin assertion
 *  0b10..Boot form ROM due to FOPT[7] configuration
 *  0b11..Boot from ROM due to both BOOTCFG0 pin assertion and FOPT[7] configuration
 */
#define RCM_MR_BOOTROM(x)                        (((uint8_t)(((uint8_t)(x)) << RCM_MR_BOOTROM_SHIFT)) & RCM_MR_BOOTROM_MASK)
/*! @} */

/*! @name SSRS0 - Sticky System Reset Status Register 0 */
/*! @{ */

#define RCM_SSRS0_SWAKEUP_MASK                   (0x1U)
#define RCM_SSRS0_SWAKEUP_SHIFT                  (0U)
/*! SWAKEUP - Sticky Low Leakage Wakeup Reset
 *  0b0..Reset not caused by LLWU module wakeup source
 *  0b1..Reset caused by LLWU module wakeup source
 */
#define RCM_SSRS0_SWAKEUP(x)                     (((uint8_t)(((uint8_t)(x)) << RCM_SSRS0_SWAKEUP_SHIFT)) & RCM_SSRS0_SWAKEUP_MASK)

#define RCM_SSRS0_SLVD_MASK                      (0x2U)
#define RCM_SSRS0_SLVD_SHIFT                     (1U)
/*! SLVD - Sticky Low-Voltage Detect Reset
 *  0b0..Reset not caused by LVD trip or POR
 *  0b1..Reset caused by LVD trip or POR
 */
#define RCM_SSRS0_SLVD(x)                        (((uint8_t)(((uint8_t)(x)) << RCM_SSRS0_SLVD_SHIFT)) & RCM_SSRS0_SLVD_MASK)

#define RCM_SSRS0_SWDOG_MASK                     (0x20U)
#define RCM_SSRS0_SWDOG_SHIFT                    (5U)
/*! SWDOG - Sticky Watchdog
 *  0b0..Reset not caused by watchdog timeout
 *  0b1..Reset caused by watchdog timeout
 */
#define RCM_SSRS0_SWDOG(x)                       (((uint8_t)(((uint8_t)(x)) << RCM_SSRS0_SWDOG_SHIFT)) & RCM_SSRS0_SWDOG_MASK)

#define RCM_SSRS0_SPIN_MASK                      (0x40U)
#define RCM_SSRS0_SPIN_SHIFT                     (6U)
/*! SPIN - Sticky External Reset Pin
 *  0b0..Reset not caused by external reset pin
 *  0b1..Reset caused by external reset pin
 */
#define RCM_SSRS0_SPIN(x)                        (((uint8_t)(((uint8_t)(x)) << RCM_SSRS0_SPIN_SHIFT)) & RCM_SSRS0_SPIN_MASK)

#define RCM_SSRS0_SPOR_MASK                      (0x80U)
#define RCM_SSRS0_SPOR_SHIFT                     (7U)
/*! SPOR - Sticky Power-On Reset
 *  0b0..Reset not caused by POR
 *  0b1..Reset caused by POR
 */
#define RCM_SSRS0_SPOR(x)                        (((uint8_t)(((uint8_t)(x)) << RCM_SSRS0_SPOR_SHIFT)) & RCM_SSRS0_SPOR_MASK)
/*! @} */

/*! @name SSRS1 - Sticky System Reset Status Register 1 */
/*! @{ */

#define RCM_SSRS1_SLOCKUP_MASK                   (0x2U)
#define RCM_SSRS1_SLOCKUP_SHIFT                  (1U)
/*! SLOCKUP - Sticky Core Lockup
 *  0b0..Reset not caused by core LOCKUP event
 *  0b1..Reset caused by core LOCKUP event
 */
#define RCM_SSRS1_SLOCKUP(x)                     (((uint8_t)(((uint8_t)(x)) << RCM_SSRS1_SLOCKUP_SHIFT)) & RCM_SSRS1_SLOCKUP_MASK)

#define RCM_SSRS1_SSW_MASK                       (0x4U)
#define RCM_SSRS1_SSW_SHIFT                      (2U)
/*! SSW - Sticky Software
 *  0b0..Reset not caused by software setting of SYSRESETREQ bit
 *  0b1..Reset caused by software setting of SYSRESETREQ bit
 */
#define RCM_SSRS1_SSW(x)                         (((uint8_t)(((uint8_t)(x)) << RCM_SSRS1_SSW_SHIFT)) & RCM_SSRS1_SSW_MASK)

#define RCM_SSRS1_SMDM_AP_MASK                   (0x8U)
#define RCM_SSRS1_SMDM_AP_SHIFT                  (3U)
/*! SMDM_AP - Sticky MDM-AP System Reset Request
 *  0b0..Reset not caused by host debugger system setting of the System Reset Request bit
 *  0b1..Reset caused by host debugger system setting of the System Reset Request bit
 */
#define RCM_SSRS1_SMDM_AP(x)                     (((uint8_t)(((uint8_t)(x)) << RCM_SSRS1_SMDM_AP_SHIFT)) & RCM_SSRS1_SMDM_AP_MASK)

#define RCM_SSRS1_SSACKERR_MASK                  (0x20U)
#define RCM_SSRS1_SSACKERR_SHIFT                 (5U)
/*! SSACKERR - Sticky Stop Mode Acknowledge Error Reset
 *  0b0..Reset not caused by peripheral failure to acknowledge attempt to enter stop mode
 *  0b1..Reset caused by peripheral failure to acknowledge attempt to enter stop mode
 */
#define RCM_SSRS1_SSACKERR(x)                    (((uint8_t)(((uint8_t)(x)) << RCM_SSRS1_SSACKERR_SHIFT)) & RCM_SSRS1_SSACKERR_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group RCM_Register_Masks */


/* RCM - Peripheral instance base addresses */
/** Peripheral RCM base address */
#define RCM_BASE                                 (0x4007F000u)
/** Peripheral RCM base pointer */
#define RCM                                      ((RCM_Type *)RCM_BASE)
/** Array initializer of RCM peripheral base addresses */
#define RCM_BASE_ADDRS                           { RCM_BASE }
/** Array initializer of RCM peripheral base pointers */
#define RCM_BASE_PTRS                            { RCM }

/*!
 * @}
 */ /* end of group RCM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RFSYS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFSYS_Peripheral_Access_Layer RFSYS Peripheral Access Layer
 * @{
 */

/** RFSYS - Register Layout Typedef */
typedef struct {
  __IO uint32_t REG[8];                            /**< Register file register, array offset: 0x0, array step: 0x4 */
} RFSYS_Type;

/* ----------------------------------------------------------------------------
   -- RFSYS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFSYS_Register_Masks RFSYS Register Masks
 * @{
 */

/*! @name REG - Register file register */
/*! @{ */

#define RFSYS_REG_LL_MASK                        (0xFFU)
#define RFSYS_REG_LL_SHIFT                       (0U)
#define RFSYS_REG_LL(x)                          (((uint32_t)(((uint32_t)(x)) << RFSYS_REG_LL_SHIFT)) & RFSYS_REG_LL_MASK)

#define RFSYS_REG_LH_MASK                        (0xFF00U)
#define RFSYS_REG_LH_SHIFT                       (8U)
#define RFSYS_REG_LH(x)                          (((uint32_t)(((uint32_t)(x)) << RFSYS_REG_LH_SHIFT)) & RFSYS_REG_LH_MASK)

#define RFSYS_REG_HL_MASK                        (0xFF0000U)
#define RFSYS_REG_HL_SHIFT                       (16U)
#define RFSYS_REG_HL(x)                          (((uint32_t)(((uint32_t)(x)) << RFSYS_REG_HL_SHIFT)) & RFSYS_REG_HL_MASK)

#define RFSYS_REG_HH_MASK                        (0xFF000000U)
#define RFSYS_REG_HH_SHIFT                       (24U)
#define RFSYS_REG_HH(x)                          (((uint32_t)(((uint32_t)(x)) << RFSYS_REG_HH_SHIFT)) & RFSYS_REG_HH_MASK)
/*! @} */

/* The count of RFSYS_REG */
#define RFSYS_REG_COUNT                          (8U)


/*!
 * @}
 */ /* end of group RFSYS_Register_Masks */


/* RFSYS - Peripheral instance base addresses */
/** Peripheral RFSYS base address */
#define RFSYS_BASE                               (0x40041000u)
/** Peripheral RFSYS base pointer */
#define RFSYS                                    ((RFSYS_Type *)RFSYS_BASE)
/** Array initializer of RFSYS peripheral base addresses */
#define RFSYS_BASE_ADDRS                         { RFSYS_BASE }
/** Array initializer of RFSYS peripheral base pointers */
#define RFSYS_BASE_PTRS                          { RFSYS }

/*!
 * @}
 */ /* end of group RFSYS_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- ROM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Peripheral_Access_Layer ROM Peripheral Access Layer
 * @{
 */

/** ROM - Register Layout Typedef */
typedef struct {
  __I  uint32_t ENTRY[3];                          /**< Entry, array offset: 0x0, array step: 0x4 */
  __I  uint32_t TABLEMARK;                         /**< End of Table Marker Register, offset: 0xC */
       uint8_t RESERVED_0[4028];
  __I  uint32_t SYSACCESS;                         /**< System Access Register, offset: 0xFCC */
  __I  uint32_t PERIPHID4;                         /**< Peripheral ID Register, offset: 0xFD0 */
  __I  uint32_t PERIPHID5;                         /**< Peripheral ID Register, offset: 0xFD4 */
  __I  uint32_t PERIPHID6;                         /**< Peripheral ID Register, offset: 0xFD8 */
  __I  uint32_t PERIPHID7;                         /**< Peripheral ID Register, offset: 0xFDC */
  __I  uint32_t PERIPHID0;                         /**< Peripheral ID Register, offset: 0xFE0 */
  __I  uint32_t PERIPHID1;                         /**< Peripheral ID Register, offset: 0xFE4 */
  __I  uint32_t PERIPHID2;                         /**< Peripheral ID Register, offset: 0xFE8 */
  __I  uint32_t PERIPHID3;                         /**< Peripheral ID Register, offset: 0xFEC */
  __I  uint32_t COMPID[4];                         /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} ROM_Type;

/* ----------------------------------------------------------------------------
   -- ROM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Masks ROM Register Masks
 * @{
 */

/*! @name ENTRY - Entry */
/*! @{ */

#define ROM_ENTRY_ENTRY_MASK                     (0xFFFFFFFFU)
#define ROM_ENTRY_ENTRY_SHIFT                    (0U)
/*! ENTRY - ENTRY */
#define ROM_ENTRY_ENTRY(x)                       (((uint32_t)(((uint32_t)(x)) << ROM_ENTRY_ENTRY_SHIFT)) & ROM_ENTRY_ENTRY_MASK)
/*! @} */

/* The count of ROM_ENTRY */
#define ROM_ENTRY_COUNT                          (3U)

/*! @name TABLEMARK - End of Table Marker Register */
/*! @{ */

#define ROM_TABLEMARK_MARK_MASK                  (0xFFFFFFFFU)
#define ROM_TABLEMARK_MARK_SHIFT                 (0U)
/*! MARK - MARK */
#define ROM_TABLEMARK_MARK(x)                    (((uint32_t)(((uint32_t)(x)) << ROM_TABLEMARK_MARK_SHIFT)) & ROM_TABLEMARK_MARK_MASK)
/*! @} */

/*! @name SYSACCESS - System Access Register */
/*! @{ */

#define ROM_SYSACCESS_SYSACCESS_MASK             (0xFFFFFFFFU)
#define ROM_SYSACCESS_SYSACCESS_SHIFT            (0U)
/*! SYSACCESS - SYSACCESS */
#define ROM_SYSACCESS_SYSACCESS(x)               (((uint32_t)(((uint32_t)(x)) << ROM_SYSACCESS_SYSACCESS_SHIFT)) & ROM_SYSACCESS_SYSACCESS_MASK)
/*! @} */

/*! @name PERIPHID4 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID4_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID4_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define ROM_PERIPHID4_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID4_PERIPHID_SHIFT)) & ROM_PERIPHID4_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID5 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID5_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID5_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define ROM_PERIPHID5_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID5_PERIPHID_SHIFT)) & ROM_PERIPHID5_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID6 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID6_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID6_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define ROM_PERIPHID6_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID6_PERIPHID_SHIFT)) & ROM_PERIPHID6_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID7 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID7_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID7_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define ROM_PERIPHID7_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID7_PERIPHID_SHIFT)) & ROM_PERIPHID7_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID0 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID0_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID0_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define ROM_PERIPHID0_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID0_PERIPHID_SHIFT)) & ROM_PERIPHID0_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID1 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID1_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID1_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define ROM_PERIPHID1_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID1_PERIPHID_SHIFT)) & ROM_PERIPHID1_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID2 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID2_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID2_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define ROM_PERIPHID2_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID2_PERIPHID_SHIFT)) & ROM_PERIPHID2_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID3 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID3_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID3_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID */
#define ROM_PERIPHID3_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID3_PERIPHID_SHIFT)) & ROM_PERIPHID3_PERIPHID_MASK)
/*! @} */

/*! @name COMPID - Component ID Register */
/*! @{ */

#define ROM_COMPID_COMPID_MASK                   (0xFFFFFFFFU)
#define ROM_COMPID_COMPID_SHIFT                  (0U)
/*! COMPID - Component ID */
#define ROM_COMPID_COMPID(x)                     (((uint32_t)(((uint32_t)(x)) << ROM_COMPID_COMPID_SHIFT)) & ROM_COMPID_COMPID_MASK)
/*! @} */

/* The count of ROM_COMPID */
#define ROM_COMPID_COUNT                         (4U)


/*!
 * @}
 */ /* end of group ROM_Register_Masks */


/* ROM - Peripheral instance base addresses */
/** Peripheral ROM base address */
#define ROM_BASE                                 (0xF0002000u)
/** Peripheral ROM base pointer */
#define ROM                                      ((ROM_Type *)ROM_BASE)
/** Array initializer of ROM peripheral base addresses */
#define ROM_BASE_ADDRS                           { ROM_BASE }
/** Array initializer of ROM peripheral base pointers */
#define ROM_BASE_PTRS                            { ROM }

/*!
 * @}
 */ /* end of group ROM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RTC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Peripheral_Access_Layer RTC Peripheral Access Layer
 * @{
 */

/** RTC - Register Layout Typedef */
typedef struct {
  __IO uint32_t TSR;                               /**< RTC Time Seconds Register, offset: 0x0 */
  __IO uint32_t TPR;                               /**< RTC Time Prescaler Register, offset: 0x4 */
  __IO uint32_t TAR;                               /**< RTC Time Alarm Register, offset: 0x8 */
  __IO uint32_t TCR;                               /**< RTC Time Compensation Register, offset: 0xC */
  __IO uint32_t CR;                                /**< RTC Control Register, offset: 0x10 */
  __IO uint32_t SR;                                /**< RTC Status Register, offset: 0x14 */
  __IO uint32_t LR;                                /**< RTC Lock Register, offset: 0x18 */
  __IO uint32_t IER;                               /**< RTC Interrupt Enable Register, offset: 0x1C */
} RTC_Type;

/* ----------------------------------------------------------------------------
   -- RTC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Masks RTC Register Masks
 * @{
 */

/*! @name TSR - RTC Time Seconds Register */
/*! @{ */

#define RTC_TSR_TSR_MASK                         (0xFFFFFFFFU)
#define RTC_TSR_TSR_SHIFT                        (0U)
/*! TSR - Time Seconds Register */
#define RTC_TSR_TSR(x)                           (((uint32_t)(((uint32_t)(x)) << RTC_TSR_TSR_SHIFT)) & RTC_TSR_TSR_MASK)
/*! @} */

/*! @name TPR - RTC Time Prescaler Register */
/*! @{ */

#define RTC_TPR_TPR_MASK                         (0xFFFFU)
#define RTC_TPR_TPR_SHIFT                        (0U)
/*! TPR - Time Prescaler Register */
#define RTC_TPR_TPR(x)                           (((uint32_t)(((uint32_t)(x)) << RTC_TPR_TPR_SHIFT)) & RTC_TPR_TPR_MASK)
/*! @} */

/*! @name TAR - RTC Time Alarm Register */
/*! @{ */

#define RTC_TAR_TAR_MASK                         (0xFFFFFFFFU)
#define RTC_TAR_TAR_SHIFT                        (0U)
/*! TAR - Time Alarm Register */
#define RTC_TAR_TAR(x)                           (((uint32_t)(((uint32_t)(x)) << RTC_TAR_TAR_SHIFT)) & RTC_TAR_TAR_MASK)
/*! @} */

/*! @name TCR - RTC Time Compensation Register */
/*! @{ */

#define RTC_TCR_TCR_MASK                         (0xFFU)
#define RTC_TCR_TCR_SHIFT                        (0U)
/*! TCR - Time Compensation Register
 *  0b10000000..Time Prescaler Register overflows every 32896 clock cycles.
 *  0b11111111..Time Prescaler Register overflows every 32769 clock cycles.
 *  0b00000000..Time Prescaler Register overflows every 32768 clock cycles.
 *  0b00000001..Time Prescaler Register overflows every 32767 clock cycles.
 *  0b01111111..Time Prescaler Register overflows every 32641 clock cycles.
 */
#define RTC_TCR_TCR(x)                           (((uint32_t)(((uint32_t)(x)) << RTC_TCR_TCR_SHIFT)) & RTC_TCR_TCR_MASK)

#define RTC_TCR_CIR_MASK                         (0xFF00U)
#define RTC_TCR_CIR_SHIFT                        (8U)
/*! CIR - Compensation Interval Register */
#define RTC_TCR_CIR(x)                           (((uint32_t)(((uint32_t)(x)) << RTC_TCR_CIR_SHIFT)) & RTC_TCR_CIR_MASK)

#define RTC_TCR_TCV_MASK                         (0xFF0000U)
#define RTC_TCR_TCV_SHIFT                        (16U)
/*! TCV - Time Compensation Value */
#define RTC_TCR_TCV(x)                           (((uint32_t)(((uint32_t)(x)) << RTC_TCR_TCV_SHIFT)) & RTC_TCR_TCV_MASK)

#define RTC_TCR_CIC_MASK                         (0xFF000000U)
#define RTC_TCR_CIC_SHIFT                        (24U)
/*! CIC - Compensation Interval Counter */
#define RTC_TCR_CIC(x)                           (((uint32_t)(((uint32_t)(x)) << RTC_TCR_CIC_SHIFT)) & RTC_TCR_CIC_MASK)
/*! @} */

/*! @name CR - RTC Control Register */
/*! @{ */

#define RTC_CR_SWR_MASK                          (0x1U)
#define RTC_CR_SWR_SHIFT                         (0U)
/*! SWR - Software Reset
 *  0b0..No effect.
 *  0b1..Resets all RTC registers except for the SWR bit . The SWR bit is cleared by POR and by software explicitly clearing it.
 */
#define RTC_CR_SWR(x)                            (((uint32_t)(((uint32_t)(x)) << RTC_CR_SWR_SHIFT)) & RTC_CR_SWR_MASK)

#define RTC_CR_WPE_MASK                          (0x2U)
#define RTC_CR_WPE_SHIFT                         (1U)
/*! WPE - Wakeup Pin Enable
 *  0b0..Wakeup pin is disabled.
 *  0b1..Wakeup pin is enabled and wakeup pin asserts if the RTC interrupt asserts or the wakeup pin is turned on.
 */
#define RTC_CR_WPE(x)                            (((uint32_t)(((uint32_t)(x)) << RTC_CR_WPE_SHIFT)) & RTC_CR_WPE_MASK)

#define RTC_CR_SUP_MASK                          (0x4U)
#define RTC_CR_SUP_SHIFT                         (2U)
/*! SUP - Supervisor Access
 *  0b0..Non-supervisor mode write accesses are not supported and generate a bus error.
 *  0b1..Non-supervisor mode write accesses are supported.
 */
#define RTC_CR_SUP(x)                            (((uint32_t)(((uint32_t)(x)) << RTC_CR_SUP_SHIFT)) & RTC_CR_SUP_MASK)

#define RTC_CR_UM_MASK                           (0x8U)
#define RTC_CR_UM_SHIFT                          (3U)
/*! UM - Update Mode
 *  0b0..Registers cannot be written when locked.
 *  0b1..Registers can be written when locked under limited conditions.
 */
#define RTC_CR_UM(x)                             (((uint32_t)(((uint32_t)(x)) << RTC_CR_UM_SHIFT)) & RTC_CR_UM_MASK)

#define RTC_CR_WPS_MASK                          (0x10U)
#define RTC_CR_WPS_SHIFT                         (4U)
/*! WPS - Wakeup Pin Select
 *  0b0..Wakeup pin asserts (active low, open drain) if the RTC interrupt asserts or the wakeup pin is turned on.
 *  0b1..Wakeup pin instead outputs the RTC 32kHz clock, provided the wakeup pin is turned on and the 32kHz clock is output to other peripherals.
 */
#define RTC_CR_WPS(x)                            (((uint32_t)(((uint32_t)(x)) << RTC_CR_WPS_SHIFT)) & RTC_CR_WPS_MASK)

#define RTC_CR_OSCE_MASK                         (0x100U)
#define RTC_CR_OSCE_SHIFT                        (8U)
/*! OSCE - Oscillator Enable
 *  0b0..32.768 kHz oscillator is disabled.
 *  0b1..32.768 kHz oscillator is enabled. After setting this bit, wait the oscillator startup time before
 *       enabling the time counter to allow the 32.768 kHz clock time to stabilize.
 */
#define RTC_CR_OSCE(x)                           (((uint32_t)(((uint32_t)(x)) << RTC_CR_OSCE_SHIFT)) & RTC_CR_OSCE_MASK)

#define RTC_CR_CLKO_MASK                         (0x200U)
#define RTC_CR_CLKO_SHIFT                        (9U)
/*! CLKO - Clock Output
 *  0b0..The 32 kHz clock is output to other peripherals.
 *  0b1..The 32 kHz clock is not output to other peripherals.
 */
#define RTC_CR_CLKO(x)                           (((uint32_t)(((uint32_t)(x)) << RTC_CR_CLKO_SHIFT)) & RTC_CR_CLKO_MASK)

#define RTC_CR_SC16P_MASK                        (0x400U)
#define RTC_CR_SC16P_SHIFT                       (10U)
/*! SC16P - Oscillator 16pF Load Configure
 *  0b0..Disable the load.
 *  0b1..Enable the additional load.
 */
#define RTC_CR_SC16P(x)                          (((uint32_t)(((uint32_t)(x)) << RTC_CR_SC16P_SHIFT)) & RTC_CR_SC16P_MASK)

#define RTC_CR_SC8P_MASK                         (0x800U)
#define RTC_CR_SC8P_SHIFT                        (11U)
/*! SC8P - Oscillator 8pF Load Configure
 *  0b0..Disable the load.
 *  0b1..Enable the additional load.
 */
#define RTC_CR_SC8P(x)                           (((uint32_t)(((uint32_t)(x)) << RTC_CR_SC8P_SHIFT)) & RTC_CR_SC8P_MASK)

#define RTC_CR_SC4P_MASK                         (0x1000U)
#define RTC_CR_SC4P_SHIFT                        (12U)
/*! SC4P - Oscillator 4pF Load Configure
 *  0b0..Disable the load.
 *  0b1..Enable the additional load.
 */
#define RTC_CR_SC4P(x)                           (((uint32_t)(((uint32_t)(x)) << RTC_CR_SC4P_SHIFT)) & RTC_CR_SC4P_MASK)

#define RTC_CR_SC2P_MASK                         (0x2000U)
#define RTC_CR_SC2P_SHIFT                        (13U)
/*! SC2P - Oscillator 2pF Load Configure
 *  0b0..Disable the load.
 *  0b1..Enable the additional load.
 */
#define RTC_CR_SC2P(x)                           (((uint32_t)(((uint32_t)(x)) << RTC_CR_SC2P_SHIFT)) & RTC_CR_SC2P_MASK)
/*! @} */

/*! @name SR - RTC Status Register */
/*! @{ */

#define RTC_SR_TIF_MASK                          (0x1U)
#define RTC_SR_TIF_SHIFT                         (0U)
/*! TIF - Time Invalid Flag
 *  0b0..Time is valid.
 *  0b1..Time is invalid and time counter is read as zero.
 */
#define RTC_SR_TIF(x)                            (((uint32_t)(((uint32_t)(x)) << RTC_SR_TIF_SHIFT)) & RTC_SR_TIF_MASK)

#define RTC_SR_TOF_MASK                          (0x2U)
#define RTC_SR_TOF_SHIFT                         (1U)
/*! TOF - Time Overflow Flag
 *  0b0..Time overflow has not occurred.
 *  0b1..Time overflow has occurred and time counter is read as zero.
 */
#define RTC_SR_TOF(x)                            (((uint32_t)(((uint32_t)(x)) << RTC_SR_TOF_SHIFT)) & RTC_SR_TOF_MASK)

#define RTC_SR_TAF_MASK                          (0x4U)
#define RTC_SR_TAF_SHIFT                         (2U)
/*! TAF - Time Alarm Flag
 *  0b0..Time alarm has not occurred.
 *  0b1..Time alarm has occurred.
 */
#define RTC_SR_TAF(x)                            (((uint32_t)(((uint32_t)(x)) << RTC_SR_TAF_SHIFT)) & RTC_SR_TAF_MASK)

#define RTC_SR_TCE_MASK                          (0x10U)
#define RTC_SR_TCE_SHIFT                         (4U)
/*! TCE - Time Counter Enable
 *  0b0..Time counter is disabled.
 *  0b1..Time counter is enabled.
 */
#define RTC_SR_TCE(x)                            (((uint32_t)(((uint32_t)(x)) << RTC_SR_TCE_SHIFT)) & RTC_SR_TCE_MASK)
/*! @} */

/*! @name LR - RTC Lock Register */
/*! @{ */

#define RTC_LR_TCL_MASK                          (0x8U)
#define RTC_LR_TCL_SHIFT                         (3U)
/*! TCL - Time Compensation Lock
 *  0b0..Time Compensation Register is locked and writes are ignored.
 *  0b1..Time Compensation Register is not locked and writes complete as normal.
 */
#define RTC_LR_TCL(x)                            (((uint32_t)(((uint32_t)(x)) << RTC_LR_TCL_SHIFT)) & RTC_LR_TCL_MASK)

#define RTC_LR_CRL_MASK                          (0x10U)
#define RTC_LR_CRL_SHIFT                         (4U)
/*! CRL - Control Register Lock
 *  0b0..Control Register is locked and writes are ignored.
 *  0b1..Control Register is not locked and writes complete as normal.
 */
#define RTC_LR_CRL(x)                            (((uint32_t)(((uint32_t)(x)) << RTC_LR_CRL_SHIFT)) & RTC_LR_CRL_MASK)

#define RTC_LR_SRL_MASK                          (0x20U)
#define RTC_LR_SRL_SHIFT                         (5U)
/*! SRL - Status Register Lock
 *  0b0..Status Register is locked and writes are ignored.
 *  0b1..Status Register is not locked and writes complete as normal.
 */
#define RTC_LR_SRL(x)                            (((uint32_t)(((uint32_t)(x)) << RTC_LR_SRL_SHIFT)) & RTC_LR_SRL_MASK)

#define RTC_LR_LRL_MASK                          (0x40U)
#define RTC_LR_LRL_SHIFT                         (6U)
/*! LRL - Lock Register Lock
 *  0b0..Lock Register is locked and writes are ignored.
 *  0b1..Lock Register is not locked and writes complete as normal.
 */
#define RTC_LR_LRL(x)                            (((uint32_t)(((uint32_t)(x)) << RTC_LR_LRL_SHIFT)) & RTC_LR_LRL_MASK)
/*! @} */

/*! @name IER - RTC Interrupt Enable Register */
/*! @{ */

#define RTC_IER_TIIE_MASK                        (0x1U)
#define RTC_IER_TIIE_SHIFT                       (0U)
/*! TIIE - Time Invalid Interrupt Enable
 *  0b0..Time invalid flag does not generate an interrupt.
 *  0b1..Time invalid flag does generate an interrupt.
 */
#define RTC_IER_TIIE(x)                          (((uint32_t)(((uint32_t)(x)) << RTC_IER_TIIE_SHIFT)) & RTC_IER_TIIE_MASK)

#define RTC_IER_TOIE_MASK                        (0x2U)
#define RTC_IER_TOIE_SHIFT                       (1U)
/*! TOIE - Time Overflow Interrupt Enable
 *  0b0..Time overflow flag does not generate an interrupt.
 *  0b1..Time overflow flag does generate an interrupt.
 */
#define RTC_IER_TOIE(x)                          (((uint32_t)(((uint32_t)(x)) << RTC_IER_TOIE_SHIFT)) & RTC_IER_TOIE_MASK)

#define RTC_IER_TAIE_MASK                        (0x4U)
#define RTC_IER_TAIE_SHIFT                       (2U)
/*! TAIE - Time Alarm Interrupt Enable
 *  0b0..Time alarm flag does not generate an interrupt.
 *  0b1..Time alarm flag does generate an interrupt.
 */
#define RTC_IER_TAIE(x)                          (((uint32_t)(((uint32_t)(x)) << RTC_IER_TAIE_SHIFT)) & RTC_IER_TAIE_MASK)

#define RTC_IER_TSIE_MASK                        (0x10U)
#define RTC_IER_TSIE_SHIFT                       (4U)
/*! TSIE - Time Seconds Interrupt Enable
 *  0b0..Seconds interrupt is disabled.
 *  0b1..Seconds interrupt is enabled.
 */
#define RTC_IER_TSIE(x)                          (((uint32_t)(((uint32_t)(x)) << RTC_IER_TSIE_SHIFT)) & RTC_IER_TSIE_MASK)

#define RTC_IER_WPON_MASK                        (0x80U)
#define RTC_IER_WPON_SHIFT                       (7U)
/*! WPON - Wakeup Pin On
 *  0b0..No effect.
 *  0b1..If the wakeup pin is enabled, then the wakeup pin will assert.
 */
#define RTC_IER_WPON(x)                          (((uint32_t)(((uint32_t)(x)) << RTC_IER_WPON_SHIFT)) & RTC_IER_WPON_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group RTC_Register_Masks */


/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base address */
#define RTC_BASE                                 (0x4003D000u)
/** Peripheral RTC base pointer */
#define RTC                                      ((RTC_Type *)RTC_BASE)
/** Array initializer of RTC peripheral base addresses */
#define RTC_BASE_ADDRS                           { RTC_BASE }
/** Array initializer of RTC peripheral base pointers */
#define RTC_BASE_PTRS                            { RTC }
/** Interrupt vectors for the RTC peripheral type */
#define RTC_IRQS                                 { RTC_IRQn }
#define RTC_SECONDS_IRQS                         { RTC_Seconds_IRQn }

/*!
 * @}
 */ /* end of group RTC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SIM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Peripheral_Access_Layer SIM Peripheral Access Layer
 * @{
 */

/** SIM - Register Layout Typedef */
typedef struct {
  __IO uint32_t SOPT1;                             /**< System Options Register 1, offset: 0x0 */
  __IO uint32_t SOPT1CFG;                          /**< SOPT1 Configuration Register, offset: 0x4 */
       uint8_t RESERVED_0[4092];
  __IO uint32_t SOPT2;                             /**< System Options Register 2, offset: 0x1004 */
       uint8_t RESERVED_1[4];
  __IO uint32_t SOPT4;                             /**< System Options Register 4, offset: 0x100C */
  __IO uint32_t SOPT5;                             /**< System Options Register 5, offset: 0x1010 */
       uint8_t RESERVED_2[4];
  __IO uint32_t SOPT7;                             /**< System Options Register 7, offset: 0x1018 */
       uint8_t RESERVED_3[8];
  __I  uint32_t SDID;                              /**< System Device Identification Register, offset: 0x1024 */
       uint8_t RESERVED_4[12];
  __IO uint32_t SCGC4;                             /**< System Clock Gating Control Register 4, offset: 0x1034 */
  __IO uint32_t SCGC5;                             /**< System Clock Gating Control Register 5, offset: 0x1038 */
  __IO uint32_t SCGC6;                             /**< System Clock Gating Control Register 6, offset: 0x103C */
  __IO uint32_t SCGC7;                             /**< System Clock Gating Control Register 7, offset: 0x1040 */
  __IO uint32_t CLKDIV1;                           /**< System Clock Divider Register 1, offset: 0x1044 */
       uint8_t RESERVED_5[4];
  __IO uint32_t FCFG1;                             /**< Flash Configuration Register 1, offset: 0x104C */
  __I  uint32_t FCFG2;                             /**< Flash Configuration Register 2, offset: 0x1050 */
       uint8_t RESERVED_6[4];
  __I  uint32_t UIDMH;                             /**< Unique Identification Register Mid-High, offset: 0x1058 */
  __I  uint32_t UIDML;                             /**< Unique Identification Register Mid Low, offset: 0x105C */
  __I  uint32_t UIDL;                              /**< Unique Identification Register Low, offset: 0x1060 */
       uint8_t RESERVED_7[156];
  __IO uint32_t COPC;                              /**< COP Control Register, offset: 0x1100 */
  __O  uint32_t SRVCOP;                            /**< Service COP, offset: 0x1104 */
} SIM_Type;

/* ----------------------------------------------------------------------------
   -- SIM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Masks SIM Register Masks
 * @{
 */

/*! @name SOPT1 - System Options Register 1 */
/*! @{ */

#define SIM_SOPT1_OSC32KOUT_MASK                 (0x30000U)
#define SIM_SOPT1_OSC32KOUT_SHIFT                (16U)
/*! OSC32KOUT - 32K oscillator clock output
 *  0b00..ERCLK32K is not output.
 *  0b01..ERCLK32K is output on PTE0.
 *  0b10..ERCLK32K is output on PTE26.
 *  0b11..Reserved.
 */
#define SIM_SOPT1_OSC32KOUT(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_OSC32KOUT_SHIFT)) & SIM_SOPT1_OSC32KOUT_MASK)

#define SIM_SOPT1_OSC32KSEL_MASK                 (0xC0000U)
#define SIM_SOPT1_OSC32KSEL_SHIFT                (18U)
/*! OSC32KSEL - 32K Oscillator Clock Select
 *  0b00..System oscillator (OSC32KCLK)
 *  0b01..Reserved
 *  0b10..RTC_CLKIN
 *  0b11..LPO 1kHz
 */
#define SIM_SOPT1_OSC32KSEL(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_OSC32KSEL_SHIFT)) & SIM_SOPT1_OSC32KSEL_MASK)

#define SIM_SOPT1_USBVSTBY_MASK                  (0x20000000U)
#define SIM_SOPT1_USBVSTBY_SHIFT                 (29U)
/*! USBVSTBY - USB voltage regulator in standby mode during VLPR and VLPW modes
 *  0b0..USB voltage regulator not in standby during VLPR and VLPW modes.
 *  0b1..USB voltage regulator in standby during VLPR and VLPW modes.
 */
#define SIM_SOPT1_USBVSTBY(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_USBVSTBY_SHIFT)) & SIM_SOPT1_USBVSTBY_MASK)

#define SIM_SOPT1_USBSSTBY_MASK                  (0x40000000U)
#define SIM_SOPT1_USBSSTBY_SHIFT                 (30U)
/*! USBSSTBY - USB voltage regulator in standby mode during Stop, VLPS, LLS and VLLS modes.
 *  0b0..USB voltage regulator not in standby during Stop, VLPS, LLS and VLLS modes.
 *  0b1..USB voltage regulator in standby during Stop, VLPS, LLS and VLLS modes.
 */
#define SIM_SOPT1_USBSSTBY(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_USBSSTBY_SHIFT)) & SIM_SOPT1_USBSSTBY_MASK)

#define SIM_SOPT1_USBREGEN_MASK                  (0x80000000U)
#define SIM_SOPT1_USBREGEN_SHIFT                 (31U)
/*! USBREGEN - USB voltage regulator enable
 *  0b0..USB voltage regulator is disabled.
 *  0b1..USB voltage regulator is enabled.
 */
#define SIM_SOPT1_USBREGEN(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_USBREGEN_SHIFT)) & SIM_SOPT1_USBREGEN_MASK)
/*! @} */

/*! @name SOPT1CFG - SOPT1 Configuration Register */
/*! @{ */

#define SIM_SOPT1CFG_URWE_MASK                   (0x1000000U)
#define SIM_SOPT1CFG_URWE_SHIFT                  (24U)
/*! URWE - USB voltage regulator enable write enable
 *  0b0..SOPT1 USBREGEN cannot be written.
 *  0b1..SOPT1 USBREGEN can be written.
 */
#define SIM_SOPT1CFG_URWE(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1CFG_URWE_SHIFT)) & SIM_SOPT1CFG_URWE_MASK)

#define SIM_SOPT1CFG_UVSWE_MASK                  (0x2000000U)
#define SIM_SOPT1CFG_UVSWE_SHIFT                 (25U)
/*! UVSWE - USB voltage regulator VLP standby write enable
 *  0b0..SOPT1 USBVSTB cannot be written.
 *  0b1..SOPT1 USBVSTB can be written.
 */
#define SIM_SOPT1CFG_UVSWE(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1CFG_UVSWE_SHIFT)) & SIM_SOPT1CFG_UVSWE_MASK)

#define SIM_SOPT1CFG_USSWE_MASK                  (0x4000000U)
#define SIM_SOPT1CFG_USSWE_SHIFT                 (26U)
/*! USSWE - USB voltage regulator stop standby write enable
 *  0b0..SOPT1 USBSSTB cannot be written.
 *  0b1..SOPT1 USBSSTB can be written.
 */
#define SIM_SOPT1CFG_USSWE(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1CFG_USSWE_SHIFT)) & SIM_SOPT1CFG_USSWE_MASK)
/*! @} */

/*! @name SOPT2 - System Options Register 2 */
/*! @{ */

#define SIM_SOPT2_RTCCLKOUTSEL_MASK              (0x10U)
#define SIM_SOPT2_RTCCLKOUTSEL_SHIFT             (4U)
/*! RTCCLKOUTSEL - RTC Clock Out Select
 *  0b0..RTC 1 Hz clock is output on the RTC_CLKOUT pin.
 *  0b1..OSCERCLK clock is output on the RTC_CLKOUT pin.
 */
#define SIM_SOPT2_RTCCLKOUTSEL(x)                (((uint32_t)(((uint32_t)(x)) << SIM_SOPT2_RTCCLKOUTSEL_SHIFT)) & SIM_SOPT2_RTCCLKOUTSEL_MASK)

#define SIM_SOPT2_CLKOUTSEL_MASK                 (0xE0U)
#define SIM_SOPT2_CLKOUTSEL_SHIFT                (5U)
/*! CLKOUTSEL - CLKOUT select
 *  0b000..Reserved
 *  0b001..Reserved
 *  0b010..Bus clock
 *  0b011..LPO clock (1 kHz)
 *  0b100..LIRC_CLK
 *  0b101..Reserved
 *  0b110..OSCERCLK
 *  0b111..IRC48M clock (IRC48M clock can be output to PAD only when chip VDD is 2.7-3.6 V)
 */
#define SIM_SOPT2_CLKOUTSEL(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_SOPT2_CLKOUTSEL_SHIFT)) & SIM_SOPT2_CLKOUTSEL_MASK)

#define SIM_SOPT2_USBSRC_MASK                    (0x40000U)
#define SIM_SOPT2_USBSRC_SHIFT                   (18U)
/*! USBSRC - USB clock source select
 *  0b0..External bypass clock (USB_CLKIN).
 *  0b1..IRC48M clock
 */
#define SIM_SOPT2_USBSRC(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_SOPT2_USBSRC_SHIFT)) & SIM_SOPT2_USBSRC_MASK)

#define SIM_SOPT2_FLEXIOSRC_MASK                 (0xC00000U)
#define SIM_SOPT2_FLEXIOSRC_SHIFT                (22U)
/*! FLEXIOSRC - FlexIO Module Clock Source Select
 *  0b00..Clock disabled
 *  0b01..IRC48M clock
 *  0b10..OSCERCLK clock
 *  0b11..MCGIRCLK clock
 */
#define SIM_SOPT2_FLEXIOSRC(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_SOPT2_FLEXIOSRC_SHIFT)) & SIM_SOPT2_FLEXIOSRC_MASK)

#define SIM_SOPT2_TPMSRC_MASK                    (0x3000000U)
#define SIM_SOPT2_TPMSRC_SHIFT                   (24U)
/*! TPMSRC - TPM Clock Source Select
 *  0b00..Clock disabled
 *  0b01..IRC48M clock
 *  0b10..OSCERCLK clock
 *  0b11..MCGIRCLK clock
 */
#define SIM_SOPT2_TPMSRC(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_SOPT2_TPMSRC_SHIFT)) & SIM_SOPT2_TPMSRC_MASK)

#define SIM_SOPT2_LPUART0SRC_MASK                (0xC000000U)
#define SIM_SOPT2_LPUART0SRC_SHIFT               (26U)
/*! LPUART0SRC - LPUART0 Clock Source Select
 *  0b00..Clock disabled
 *  0b01..IRC48M clock
 *  0b10..OSCERCLK clock
 *  0b11..MCGIRCLK clock
 */
#define SIM_SOPT2_LPUART0SRC(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT2_LPUART0SRC_SHIFT)) & SIM_SOPT2_LPUART0SRC_MASK)

#define SIM_SOPT2_LPUART1SRC_MASK                (0x30000000U)
#define SIM_SOPT2_LPUART1SRC_SHIFT               (28U)
/*! LPUART1SRC - LPUART1 Clock Source Select
 *  0b00..Clock disabled
 *  0b01..IRC48M clock
 *  0b10..OSCERCLK clock
 *  0b11..MCGIRCLK clock
 */
#define SIM_SOPT2_LPUART1SRC(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT2_LPUART1SRC_SHIFT)) & SIM_SOPT2_LPUART1SRC_MASK)
/*! @} */

/*! @name SOPT4 - System Options Register 4 */
/*! @{ */

#define SIM_SOPT4_TPM1CH0SRC_MASK                (0xC0000U)
#define SIM_SOPT4_TPM1CH0SRC_SHIFT               (18U)
/*! TPM1CH0SRC - TPM1 channel 0 input capture source select
 *  0b00..TPM1_CH0 signal
 *  0b01..CMP0 output
 *  0b10..Reserved
 *  0b11..USB start of frame pulse
 */
#define SIM_SOPT4_TPM1CH0SRC(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_TPM1CH0SRC_SHIFT)) & SIM_SOPT4_TPM1CH0SRC_MASK)

#define SIM_SOPT4_TPM2CH0SRC_MASK                (0x100000U)
#define SIM_SOPT4_TPM2CH0SRC_SHIFT               (20U)
/*! TPM2CH0SRC - TPM2 Channel 0 Input Capture Source Select
 *  0b0..TPM2_CH0 signal
 *  0b1..CMP0 output
 */
#define SIM_SOPT4_TPM2CH0SRC(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_TPM2CH0SRC_SHIFT)) & SIM_SOPT4_TPM2CH0SRC_MASK)

#define SIM_SOPT4_TPM0CLKSEL_MASK                (0x1000000U)
#define SIM_SOPT4_TPM0CLKSEL_SHIFT               (24U)
/*! TPM0CLKSEL - TPM0 External Clock Pin Select
 *  0b0..TPM0 external clock driven by TPM_CLKIN0 pin.
 *  0b1..TPM0 external clock driven by TPM_CLKIN1 pin.
 */
#define SIM_SOPT4_TPM0CLKSEL(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_TPM0CLKSEL_SHIFT)) & SIM_SOPT4_TPM0CLKSEL_MASK)

#define SIM_SOPT4_TPM1CLKSEL_MASK                (0x2000000U)
#define SIM_SOPT4_TPM1CLKSEL_SHIFT               (25U)
/*! TPM1CLKSEL - TPM1 External Clock Pin Select
 *  0b0..TPM1 external clock driven by TPM_CLKIN0 pin.
 *  0b1..TPM1 external clock driven by TPM_CLKIN1 pin.
 */
#define SIM_SOPT4_TPM1CLKSEL(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_TPM1CLKSEL_SHIFT)) & SIM_SOPT4_TPM1CLKSEL_MASK)

#define SIM_SOPT4_TPM2CLKSEL_MASK                (0x4000000U)
#define SIM_SOPT4_TPM2CLKSEL_SHIFT               (26U)
/*! TPM2CLKSEL - TPM2 External Clock Pin Select
 *  0b0..TPM2 external clock driven by TPM_CLKIN0 pin.
 *  0b1..TPM2 external clock driven by TPM_CLKIN1 pin.
 */
#define SIM_SOPT4_TPM2CLKSEL(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT4_TPM2CLKSEL_SHIFT)) & SIM_SOPT4_TPM2CLKSEL_MASK)
/*! @} */

/*! @name SOPT5 - System Options Register 5 */
/*! @{ */

#define SIM_SOPT5_LPUART0TXSRC_MASK              (0x3U)
#define SIM_SOPT5_LPUART0TXSRC_SHIFT             (0U)
/*! LPUART0TXSRC - LPUART0 Transmit Data Source Select
 *  0b00..LPUART0_TX pin
 *  0b01..LPUART0_TX pin modulated with TPM1 channel 0 output
 *  0b10..LPUART0_TX pin modulated with TPM2 channel 0 output
 *  0b11..Reserved
 */
#define SIM_SOPT5_LPUART0TXSRC(x)                (((uint32_t)(((uint32_t)(x)) << SIM_SOPT5_LPUART0TXSRC_SHIFT)) & SIM_SOPT5_LPUART0TXSRC_MASK)

#define SIM_SOPT5_LPUART0RXSRC_MASK              (0x4U)
#define SIM_SOPT5_LPUART0RXSRC_SHIFT             (2U)
/*! LPUART0RXSRC - LPUART0 Receive Data Source Select
 *  0b0..LPUART_RX pin
 *  0b1..CMP0 output
 */
#define SIM_SOPT5_LPUART0RXSRC(x)                (((uint32_t)(((uint32_t)(x)) << SIM_SOPT5_LPUART0RXSRC_SHIFT)) & SIM_SOPT5_LPUART0RXSRC_MASK)

#define SIM_SOPT5_LPUART1TXSRC_MASK              (0x30U)
#define SIM_SOPT5_LPUART1TXSRC_SHIFT             (4U)
/*! LPUART1TXSRC - LPUART1 Transmit Data Source Select
 *  0b00..LPUART1_TX pin
 *  0b01..LPUART1_TX pin modulated with TPM1 channel 0 output
 *  0b10..LPUART1_TX pin modulated with TPM2 channel 0 output
 *  0b11..Reserved
 */
#define SIM_SOPT5_LPUART1TXSRC(x)                (((uint32_t)(((uint32_t)(x)) << SIM_SOPT5_LPUART1TXSRC_SHIFT)) & SIM_SOPT5_LPUART1TXSRC_MASK)

#define SIM_SOPT5_LPUART1RXSRC_MASK              (0x40U)
#define SIM_SOPT5_LPUART1RXSRC_SHIFT             (6U)
/*! LPUART1RXSRC - LPUART1 Receive Data Source Select
 *  0b0..LPUART1_RX pin
 *  0b1..CMP0 output
 */
#define SIM_SOPT5_LPUART1RXSRC(x)                (((uint32_t)(((uint32_t)(x)) << SIM_SOPT5_LPUART1RXSRC_SHIFT)) & SIM_SOPT5_LPUART1RXSRC_MASK)

#define SIM_SOPT5_LPUART0ODE_MASK                (0x10000U)
#define SIM_SOPT5_LPUART0ODE_SHIFT               (16U)
/*! LPUART0ODE - LPUART0 Open Drain Enable
 *  0b0..Open drain is disabled on LPUART0.
 *  0b1..Open drain is enabled on LPUART0.
 */
#define SIM_SOPT5_LPUART0ODE(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT5_LPUART0ODE_SHIFT)) & SIM_SOPT5_LPUART0ODE_MASK)

#define SIM_SOPT5_LPUART1ODE_MASK                (0x20000U)
#define SIM_SOPT5_LPUART1ODE_SHIFT               (17U)
/*! LPUART1ODE - LPUART1 Open Drain Enable
 *  0b0..Open drain is disabled on LPUART1.
 *  0b1..Open drain is enabled on LPUART1
 */
#define SIM_SOPT5_LPUART1ODE(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT5_LPUART1ODE_SHIFT)) & SIM_SOPT5_LPUART1ODE_MASK)

#define SIM_SOPT5_UART2ODE_MASK                  (0x40000U)
#define SIM_SOPT5_UART2ODE_SHIFT                 (18U)
/*! UART2ODE - UART2 Open Drain Enable
 *  0b0..Open drain is disabled on UART2
 *  0b1..Open drain is enabled on UART2
 */
#define SIM_SOPT5_UART2ODE(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT5_UART2ODE_SHIFT)) & SIM_SOPT5_UART2ODE_MASK)
/*! @} */

/*! @name SOPT7 - System Options Register 7 */
/*! @{ */

#define SIM_SOPT7_ADC0TRGSEL_MASK                (0xFU)
#define SIM_SOPT7_ADC0TRGSEL_SHIFT               (0U)
/*! ADC0TRGSEL - ADC0 Trigger Select
 *  0b0000..External trigger pin input (EXTRG_IN)
 *  0b0001..CMP0 output
 *  0b0010..Reserved
 *  0b0011..Reserved
 *  0b0100..PIT trigger 0
 *  0b0101..PIT trigger 1
 *  0b0110..Reserved
 *  0b0111..Reserved
 *  0b1000..TPM0 overflow
 *  0b1001..TPM1 overflow
 *  0b1010..TPM2 overflow
 *  0b1011..Reserved
 *  0b1100..RTC alarm
 *  0b1101..RTC seconds
 *  0b1110..LPTMR0 trigger
 *  0b1111..Reserved
 */
#define SIM_SOPT7_ADC0TRGSEL(x)                  (((uint32_t)(((uint32_t)(x)) << SIM_SOPT7_ADC0TRGSEL_SHIFT)) & SIM_SOPT7_ADC0TRGSEL_MASK)

#define SIM_SOPT7_ADC0PRETRGSEL_MASK             (0x10U)
#define SIM_SOPT7_ADC0PRETRGSEL_SHIFT            (4U)
/*! ADC0PRETRGSEL - ADC0 Pretrigger Select
 *  0b0..Pre-trigger ADHDWTSA is selected, thus ADC0 will use ADC0_SC1A configuration for the next ADC conversion
 *       and store the result in ADC0_RA register.
 *  0b1..Pre-trigger ADHDWTSB is selected, thus ADC0 will use ADC0_SC1B configuration for the next ADC conversion
 *       and store the result in ADC0_RB register.
 */
#define SIM_SOPT7_ADC0PRETRGSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_SOPT7_ADC0PRETRGSEL_SHIFT)) & SIM_SOPT7_ADC0PRETRGSEL_MASK)

#define SIM_SOPT7_ADC0ALTTRGEN_MASK              (0x80U)
#define SIM_SOPT7_ADC0ALTTRGEN_SHIFT             (7U)
/*! ADC0ALTTRGEN - ADC0 Alternate Trigger Enable
 *  0b0..ADC ADHWT trigger comes from TPM1 channel 0 and channel1. Prior to the assertion of TPM1 channel 0, a
 *       pre-trigger pulse will be sent to ADHWTSA to initiate an ADC acquisition using ADCx_SC1A configuration and
 *       store ADC conversion in ADCx_RA Register. Prior to the assertion of TPM1 channel 1 a pre-trigger pulse will
 *       be sent to ADHWTSB to initiate an ADC acquisition using ADCx_SC1Bconfiguration and store ADC conversion in
 *       ADCx_RB Register.
 *  0b1..ADC ADHWT trigger comes from a peripheral event selected by ADC0TRGSEL bits.ADC0PRETRGSEL bit will select
 *       the optional ADHWTSA or ADHWTSB select lines for choosing the ADCx_SC1x config and ADCx_Rx result
 *       regsiter to store the ADC conversion.
 */
#define SIM_SOPT7_ADC0ALTTRGEN(x)                (((uint32_t)(((uint32_t)(x)) << SIM_SOPT7_ADC0ALTTRGEN_SHIFT)) & SIM_SOPT7_ADC0ALTTRGEN_MASK)
/*! @} */

/*! @name SDID - System Device Identification Register */
/*! @{ */

#define SIM_SDID_PINID_MASK                      (0xFU)
#define SIM_SDID_PINID_SHIFT                     (0U)
/*! PINID - Pincount Identification
 *  0b0010..32-pin
 *  0b0100..48-pin
 *  0b0101..64-pin
 *  0b1011..Custom pinout (WLCSP)
 */
#define SIM_SDID_PINID(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SDID_PINID_SHIFT)) & SIM_SDID_PINID_MASK)

#define SIM_SDID_REVID_MASK                      (0xF000U)
#define SIM_SDID_REVID_SHIFT                     (12U)
/*! REVID - Device Revision Number */
#define SIM_SDID_REVID(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SDID_REVID_SHIFT)) & SIM_SDID_REVID_MASK)

#define SIM_SDID_SRAMSIZE_MASK                   (0xF0000U)
#define SIM_SDID_SRAMSIZE_SHIFT                  (16U)
/*! SRAMSIZE - System SRAM Size
 *  0b0101..16 KB
 *  0b0110..32 KB
 */
#define SIM_SDID_SRAMSIZE(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SDID_SRAMSIZE_SHIFT)) & SIM_SDID_SRAMSIZE_MASK)

#define SIM_SDID_SERIESID_MASK                   (0xF00000U)
#define SIM_SDID_SERIESID_SHIFT                  (20U)
/*! SERIESID - Kinetis Series ID
 *  0b0001..KL family
 */
#define SIM_SDID_SERIESID(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SDID_SERIESID_SHIFT)) & SIM_SDID_SERIESID_MASK)

#define SIM_SDID_SUBFAMID_MASK                   (0xF000000U)
#define SIM_SDID_SUBFAMID_SHIFT                  (24U)
/*! SUBFAMID - TBD Sub-Family ID
 *  0b0011..TBD Subfamily
 */
#define SIM_SDID_SUBFAMID(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SDID_SUBFAMID_SHIFT)) & SIM_SDID_SUBFAMID_MASK)

#define SIM_SDID_FAMID_MASK                      (0xF0000000U)
#define SIM_SDID_FAMID_SHIFT                     (28U)
/*! FAMID
 *  0b0001..TBD
 *  0b0010..TBD
 *  0b0011..TBD
 *  0b0100..TBD
 */
#define SIM_SDID_FAMID(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SDID_FAMID_SHIFT)) & SIM_SDID_FAMID_MASK)
/*! @} */

/*! @name SCGC4 - System Clock Gating Control Register 4 */
/*! @{ */

#define SIM_SCGC4_I2C0_MASK                      (0x40U)
#define SIM_SCGC4_I2C0_SHIFT                     (6U)
/*! I2C0 - I2C0 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_I2C0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_I2C0_SHIFT)) & SIM_SCGC4_I2C0_MASK)

#define SIM_SCGC4_I2C1_MASK                      (0x80U)
#define SIM_SCGC4_I2C1_SHIFT                     (7U)
/*! I2C1 - I2C1 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_I2C1(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_I2C1_SHIFT)) & SIM_SCGC4_I2C1_MASK)

#define SIM_SCGC4_UART2_MASK                     (0x1000U)
#define SIM_SCGC4_UART2_SHIFT                    (12U)
/*! UART2 - UART2 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_UART2(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_UART2_SHIFT)) & SIM_SCGC4_UART2_MASK)

#define SIM_SCGC4_USBFS_MASK                     (0x40000U)
#define SIM_SCGC4_USBFS_SHIFT                    (18U)
/*! USBFS - USB Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_USBFS(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_USBFS_SHIFT)) & SIM_SCGC4_USBFS_MASK)

#define SIM_SCGC4_CMP0_MASK                      (0x80000U)
#define SIM_SCGC4_CMP0_SHIFT                     (19U)
/*! CMP0 - Comparator Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_CMP0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_CMP0_SHIFT)) & SIM_SCGC4_CMP0_MASK)

#define SIM_SCGC4_VREF_MASK                      (0x100000U)
#define SIM_SCGC4_VREF_SHIFT                     (20U)
/*! VREF - VREF Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_VREF(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_VREF_SHIFT)) & SIM_SCGC4_VREF_MASK)

#define SIM_SCGC4_SPI0_MASK                      (0x400000U)
#define SIM_SCGC4_SPI0_SHIFT                     (22U)
/*! SPI0 - SPI0 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_SPI0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_SPI0_SHIFT)) & SIM_SCGC4_SPI0_MASK)

#define SIM_SCGC4_SPI1_MASK                      (0x800000U)
#define SIM_SCGC4_SPI1_SHIFT                     (23U)
/*! SPI1 - SPI1 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_SPI1(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_SPI1_SHIFT)) & SIM_SCGC4_SPI1_MASK)
/*! @} */

/*! @name SCGC5 - System Clock Gating Control Register 5 */
/*! @{ */

#define SIM_SCGC5_LPTMR_MASK                     (0x1U)
#define SIM_SCGC5_LPTMR_SHIFT                    (0U)
/*! LPTMR - Low Power Timer Access Control
 *  0b0..Access disabled
 *  0b1..Access enabled
 */
#define SIM_SCGC5_LPTMR(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_LPTMR_SHIFT)) & SIM_SCGC5_LPTMR_MASK)

#define SIM_SCGC5_PORTA_MASK                     (0x200U)
#define SIM_SCGC5_PORTA_SHIFT                    (9U)
/*! PORTA - Port A Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTA(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTA_SHIFT)) & SIM_SCGC5_PORTA_MASK)

#define SIM_SCGC5_PORTB_MASK                     (0x400U)
#define SIM_SCGC5_PORTB_SHIFT                    (10U)
/*! PORTB - Port B Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTB(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTB_SHIFT)) & SIM_SCGC5_PORTB_MASK)

#define SIM_SCGC5_PORTC_MASK                     (0x800U)
#define SIM_SCGC5_PORTC_SHIFT                    (11U)
/*! PORTC - Port C Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTC(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTC_SHIFT)) & SIM_SCGC5_PORTC_MASK)

#define SIM_SCGC5_PORTD_MASK                     (0x1000U)
#define SIM_SCGC5_PORTD_SHIFT                    (12U)
/*! PORTD - Port D Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTD(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTD_SHIFT)) & SIM_SCGC5_PORTD_MASK)

#define SIM_SCGC5_PORTE_MASK                     (0x2000U)
#define SIM_SCGC5_PORTE_SHIFT                    (13U)
/*! PORTE - Port E Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTE(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTE_SHIFT)) & SIM_SCGC5_PORTE_MASK)

#define SIM_SCGC5_SLCD_MASK                      (0x80000U)
#define SIM_SCGC5_SLCD_SHIFT                     (19U)
/*! SLCD - Segment LCD Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_SLCD(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_SLCD_SHIFT)) & SIM_SCGC5_SLCD_MASK)

#define SIM_SCGC5_LPUART0_MASK                   (0x100000U)
#define SIM_SCGC5_LPUART0_SHIFT                  (20U)
/*! LPUART0 - LPUART0 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_LPUART0(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_LPUART0_SHIFT)) & SIM_SCGC5_LPUART0_MASK)

#define SIM_SCGC5_LPUART1_MASK                   (0x200000U)
#define SIM_SCGC5_LPUART1_SHIFT                  (21U)
/*! LPUART1 - LPUART1 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_LPUART1(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_LPUART1_SHIFT)) & SIM_SCGC5_LPUART1_MASK)

#define SIM_SCGC5_FLEXIO_MASK                    (0x80000000U)
#define SIM_SCGC5_FLEXIO_SHIFT                   (31U)
/*! FLEXIO - FlexIO Module
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_FLEXIO(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_FLEXIO_SHIFT)) & SIM_SCGC5_FLEXIO_MASK)
/*! @} */

/*! @name SCGC6 - System Clock Gating Control Register 6 */
/*! @{ */

#define SIM_SCGC6_FTF_MASK                       (0x1U)
#define SIM_SCGC6_FTF_SHIFT                      (0U)
/*! FTF - Flash Memory Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_FTF(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_FTF_SHIFT)) & SIM_SCGC6_FTF_MASK)

#define SIM_SCGC6_DMAMUX_MASK                    (0x2U)
#define SIM_SCGC6_DMAMUX_SHIFT                   (1U)
/*! DMAMUX - DMA Mux Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_DMAMUX(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_DMAMUX_SHIFT)) & SIM_SCGC6_DMAMUX_MASK)

#define SIM_SCGC6_I2S_MASK                       (0x8000U)
#define SIM_SCGC6_I2S_SHIFT                      (15U)
/*! I2S - I2S Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_I2S(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_I2S_SHIFT)) & SIM_SCGC6_I2S_MASK)

#define SIM_SCGC6_PIT_MASK                       (0x800000U)
#define SIM_SCGC6_PIT_SHIFT                      (23U)
/*! PIT - PIT Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_PIT(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_PIT_SHIFT)) & SIM_SCGC6_PIT_MASK)

#define SIM_SCGC6_TPM0_MASK                      (0x1000000U)
#define SIM_SCGC6_TPM0_SHIFT                     (24U)
/*! TPM0 - TPM0 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_TPM0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_TPM0_SHIFT)) & SIM_SCGC6_TPM0_MASK)

#define SIM_SCGC6_TPM1_MASK                      (0x2000000U)
#define SIM_SCGC6_TPM1_SHIFT                     (25U)
/*! TPM1 - TPM1 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_TPM1(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_TPM1_SHIFT)) & SIM_SCGC6_TPM1_MASK)

#define SIM_SCGC6_TPM2_MASK                      (0x4000000U)
#define SIM_SCGC6_TPM2_SHIFT                     (26U)
/*! TPM2 - TPM2 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_TPM2(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_TPM2_SHIFT)) & SIM_SCGC6_TPM2_MASK)

#define SIM_SCGC6_ADC0_MASK                      (0x8000000U)
#define SIM_SCGC6_ADC0_SHIFT                     (27U)
/*! ADC0 - ADC0 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_ADC0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_ADC0_SHIFT)) & SIM_SCGC6_ADC0_MASK)

#define SIM_SCGC6_RTC_MASK                       (0x20000000U)
#define SIM_SCGC6_RTC_SHIFT                      (29U)
/*! RTC - RTC Access Control
 *  0b0..Access and interrupts disabled
 *  0b1..Access and interrupts enabled
 */
#define SIM_SCGC6_RTC(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_RTC_SHIFT)) & SIM_SCGC6_RTC_MASK)

#define SIM_SCGC6_DAC0_MASK                      (0x80000000U)
#define SIM_SCGC6_DAC0_SHIFT                     (31U)
/*! DAC0 - DAC0 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_DAC0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_DAC0_SHIFT)) & SIM_SCGC6_DAC0_MASK)
/*! @} */

/*! @name SCGC7 - System Clock Gating Control Register 7 */
/*! @{ */

#define SIM_SCGC7_DMA_MASK                       (0x100U)
#define SIM_SCGC7_DMA_SHIFT                      (8U)
/*! DMA - DMA Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC7_DMA(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC7_DMA_SHIFT)) & SIM_SCGC7_DMA_MASK)
/*! @} */

/*! @name CLKDIV1 - System Clock Divider Register 1 */
/*! @{ */

#define SIM_CLKDIV1_OUTDIV4_MASK                 (0x70000U)
#define SIM_CLKDIV1_OUTDIV4_SHIFT                (16U)
/*! OUTDIV4 - Clock 4 Output Divider value
 *  0b000..Divide-by-1.
 *  0b001..Divide-by-2.
 *  0b010..Divide-by-3.
 *  0b011..Divide-by-4.
 *  0b100..Divide-by-5.
 *  0b101..Divide-by-6.
 *  0b110..Divide-by-7.
 *  0b111..Divide-by-8.
 */
#define SIM_CLKDIV1_OUTDIV4(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_CLKDIV1_OUTDIV4_SHIFT)) & SIM_CLKDIV1_OUTDIV4_MASK)

#define SIM_CLKDIV1_OUTDIV1_MASK                 (0xF0000000U)
#define SIM_CLKDIV1_OUTDIV1_SHIFT                (28U)
/*! OUTDIV1 - Clock 1 Output Divider value
 *  0b0000..Divide-by-1.
 *  0b0001..Divide-by-2.
 *  0b0010..Divide-by-3.
 *  0b0011..Divide-by-4.
 *  0b0100..Divide-by-5.
 *  0b0101..Divide-by-6.
 *  0b0110..Divide-by-7.
 *  0b0111..Divide-by-8.
 *  0b1000..Divide-by-9.
 *  0b1001..Divide-by-10.
 *  0b1010..Divide-by-11.
 *  0b1011..Divide-by-12.
 *  0b1100..Divide-by-13.
 *  0b1101..Divide-by-14.
 *  0b1110..Divide-by-15.
 *  0b1111..Divide-by-16.
 */
#define SIM_CLKDIV1_OUTDIV1(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_CLKDIV1_OUTDIV1_SHIFT)) & SIM_CLKDIV1_OUTDIV1_MASK)
/*! @} */

/*! @name FCFG1 - Flash Configuration Register 1 */
/*! @{ */

#define SIM_FCFG1_FLASHDIS_MASK                  (0x1U)
#define SIM_FCFG1_FLASHDIS_SHIFT                 (0U)
/*! FLASHDIS - Flash Disable
 *  0b0..Flash is enabled.
 *  0b1..Flash is disabled.
 */
#define SIM_FCFG1_FLASHDIS(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_FCFG1_FLASHDIS_SHIFT)) & SIM_FCFG1_FLASHDIS_MASK)

#define SIM_FCFG1_FLASHDOZE_MASK                 (0x2U)
#define SIM_FCFG1_FLASHDOZE_SHIFT                (1U)
/*! FLASHDOZE - Flash Doze
 *  0b0..Flash remains enabled during Doze mode.
 *  0b1..Flash is disabled for the duration of Doze mode.
 */
#define SIM_FCFG1_FLASHDOZE(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_FCFG1_FLASHDOZE_SHIFT)) & SIM_FCFG1_FLASHDOZE_MASK)

#define SIM_FCFG1_PFSIZE_MASK                    (0xF000000U)
#define SIM_FCFG1_PFSIZE_SHIFT                   (24U)
/*! PFSIZE - Program Flash Size
 *  0b0000..8 KB of program flash memory, 1 KB protection region
 *  0b0001..16 KB of program flash memory, 1 KB protection region
 *  0b0011..32 KB of program flash memory, 1 KB protection region
 *  0b0101..64 KB of program flash memory, 2 KB protection region
 *  0b0111..128 KB of program flash memory, 4 KB protection region
 *  0b1001..256 KB of program flash memory, 8 KB protection region
 *  0b1111..256 KB of program flash memory, 8 KB protection region
 */
#define SIM_FCFG1_PFSIZE(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_FCFG1_PFSIZE_SHIFT)) & SIM_FCFG1_PFSIZE_MASK)
/*! @} */

/*! @name FCFG2 - Flash Configuration Register 2 */
/*! @{ */

#define SIM_FCFG2_MAXADDR1_MASK                  (0x7F0000U)
#define SIM_FCFG2_MAXADDR1_SHIFT                 (16U)
#define SIM_FCFG2_MAXADDR1(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_FCFG2_MAXADDR1_SHIFT)) & SIM_FCFG2_MAXADDR1_MASK)

#define SIM_FCFG2_MAXADDR0_MASK                  (0x7F000000U)
#define SIM_FCFG2_MAXADDR0_SHIFT                 (24U)
/*! MAXADDR0 - Max Address lock */
#define SIM_FCFG2_MAXADDR0(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_FCFG2_MAXADDR0_SHIFT)) & SIM_FCFG2_MAXADDR0_MASK)
/*! @} */

/*! @name UIDMH - Unique Identification Register Mid-High */
/*! @{ */

#define SIM_UIDMH_UID_MASK                       (0xFFFFU)
#define SIM_UIDMH_UID_SHIFT                      (0U)
/*! UID - Unique Identification */
#define SIM_UIDMH_UID(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_UIDMH_UID_SHIFT)) & SIM_UIDMH_UID_MASK)
/*! @} */

/*! @name UIDML - Unique Identification Register Mid Low */
/*! @{ */

#define SIM_UIDML_UID_MASK                       (0xFFFFFFFFU)
#define SIM_UIDML_UID_SHIFT                      (0U)
/*! UID - Unique Identification */
#define SIM_UIDML_UID(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_UIDML_UID_SHIFT)) & SIM_UIDML_UID_MASK)
/*! @} */

/*! @name UIDL - Unique Identification Register Low */
/*! @{ */

#define SIM_UIDL_UID_MASK                        (0xFFFFFFFFU)
#define SIM_UIDL_UID_SHIFT                       (0U)
/*! UID - Unique Identification */
#define SIM_UIDL_UID(x)                          (((uint32_t)(((uint32_t)(x)) << SIM_UIDL_UID_SHIFT)) & SIM_UIDL_UID_MASK)
/*! @} */

/*! @name COPC - COP Control Register */
/*! @{ */

#define SIM_COPC_COPW_MASK                       (0x1U)
#define SIM_COPC_COPW_SHIFT                      (0U)
/*! COPW - COP Windowed Mode
 *  0b0..Normal mode
 *  0b1..Windowed mode
 */
#define SIM_COPC_COPW(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_COPC_COPW_SHIFT)) & SIM_COPC_COPW_MASK)

#define SIM_COPC_COPCLKS_MASK                    (0x2U)
#define SIM_COPC_COPCLKS_SHIFT                   (1U)
/*! COPCLKS - COP Clock Select
 *  0b0..COP configured for short timeout
 *  0b1..COP configured for long timeout
 */
#define SIM_COPC_COPCLKS(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_COPC_COPCLKS_SHIFT)) & SIM_COPC_COPCLKS_MASK)

#define SIM_COPC_COPT_MASK                       (0xCU)
#define SIM_COPC_COPT_SHIFT                      (2U)
/*! COPT - COP Watchdog Timeout
 *  0b00..COP disabled
 *  0b01..COP timeout after 25 cycles for short timeout or 213 cycles for long timeout
 *  0b10..COP timeout after 28 cycles for short timeout or 216 cycles for long timeout
 *  0b11..COP timeout after 210 cycles for short timeout or 218 cycles for long timeout
 */
#define SIM_COPC_COPT(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_COPC_COPT_SHIFT)) & SIM_COPC_COPT_MASK)

#define SIM_COPC_COPSTPEN_MASK                   (0x10U)
#define SIM_COPC_COPSTPEN_SHIFT                  (4U)
/*! COPSTPEN - COP Stop Enable
 *  0b0..COP is disabled and the counter is reset in Stop modes
 *  0b1..COP is enabled in Stop modes
 */
#define SIM_COPC_COPSTPEN(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_COPC_COPSTPEN_SHIFT)) & SIM_COPC_COPSTPEN_MASK)

#define SIM_COPC_COPDBGEN_MASK                   (0x20U)
#define SIM_COPC_COPDBGEN_SHIFT                  (5U)
/*! COPDBGEN - COP Debug Enable
 *  0b0..COP is disabled and the counter is reset in Debug mode
 *  0b1..COP is enabled in Debug mode
 */
#define SIM_COPC_COPDBGEN(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_COPC_COPDBGEN_SHIFT)) & SIM_COPC_COPDBGEN_MASK)

#define SIM_COPC_COPCLKSEL_MASK                  (0xC0U)
#define SIM_COPC_COPCLKSEL_SHIFT                 (6U)
/*! COPCLKSEL - COP Clock Select
 *  0b00..LPO clock (1 kHz)
 *  0b01..MCGIRCLK
 *  0b10..OSCERCLK
 *  0b11..Bus clock
 */
#define SIM_COPC_COPCLKSEL(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_COPC_COPCLKSEL_SHIFT)) & SIM_COPC_COPCLKSEL_MASK)
/*! @} */

/*! @name SRVCOP - Service COP */
/*! @{ */

#define SIM_SRVCOP_SRVCOP_MASK                   (0xFFU)
#define SIM_SRVCOP_SRVCOP_SHIFT                  (0U)
/*! SRVCOP - Service COP Register */
#define SIM_SRVCOP_SRVCOP(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SRVCOP_SRVCOP_SHIFT)) & SIM_SRVCOP_SRVCOP_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SIM_Register_Masks */


/* SIM - Peripheral instance base addresses */
/** Peripheral SIM base address */
#define SIM_BASE                                 (0x40047000u)
/** Peripheral SIM base pointer */
#define SIM                                      ((SIM_Type *)SIM_BASE)
/** Array initializer of SIM peripheral base addresses */
#define SIM_BASE_ADDRS                           { SIM_BASE }
/** Array initializer of SIM peripheral base pointers */
#define SIM_BASE_PTRS                            { SIM }

/*!
 * @}
 */ /* end of group SIM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Peripheral_Access_Layer SMC Peripheral Access Layer
 * @{
 */

/** SMC - Register Layout Typedef */
typedef struct {
  __IO uint8_t PMPROT;                             /**< Power Mode Protection register, offset: 0x0 */
  __IO uint8_t PMCTRL;                             /**< Power Mode Control register, offset: 0x1 */
  __IO uint8_t STOPCTRL;                           /**< Stop Control Register, offset: 0x2 */
  __I  uint8_t PMSTAT;                             /**< Power Mode Status register, offset: 0x3 */
} SMC_Type;

/* ----------------------------------------------------------------------------
   -- SMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Register_Masks SMC Register Masks
 * @{
 */

/*! @name PMPROT - Power Mode Protection register */
/*! @{ */

#define SMC_PMPROT_AVLLS_MASK                    (0x2U)
#define SMC_PMPROT_AVLLS_SHIFT                   (1U)
/*! AVLLS - Allow Very-Low-Leakage Stop Mode
 *  0b0..Any VLLSx mode is not allowed
 *  0b1..Any VLLSx mode is allowed
 */
#define SMC_PMPROT_AVLLS(x)                      (((uint8_t)(((uint8_t)(x)) << SMC_PMPROT_AVLLS_SHIFT)) & SMC_PMPROT_AVLLS_MASK)

#define SMC_PMPROT_ALLS_MASK                     (0x8U)
#define SMC_PMPROT_ALLS_SHIFT                    (3U)
/*! ALLS - Allow Low-Leakage Stop Mode
 *  0b0..LLS is not allowed
 *  0b1..LLS is allowed
 */
#define SMC_PMPROT_ALLS(x)                       (((uint8_t)(((uint8_t)(x)) << SMC_PMPROT_ALLS_SHIFT)) & SMC_PMPROT_ALLS_MASK)

#define SMC_PMPROT_AVLP_MASK                     (0x20U)
#define SMC_PMPROT_AVLP_SHIFT                    (5U)
/*! AVLP - Allow Very-Low-Power Modes
 *  0b0..VLPR, VLPW, and VLPS are not allowed.
 *  0b1..VLPR, VLPW, and VLPS are allowed.
 */
#define SMC_PMPROT_AVLP(x)                       (((uint8_t)(((uint8_t)(x)) << SMC_PMPROT_AVLP_SHIFT)) & SMC_PMPROT_AVLP_MASK)
/*! @} */

/*! @name PMCTRL - Power Mode Control register */
/*! @{ */

#define SMC_PMCTRL_STOPM_MASK                    (0x7U)
#define SMC_PMCTRL_STOPM_SHIFT                   (0U)
/*! STOPM - Stop Mode Control
 *  0b000..Normal Stop (STOP)
 *  0b001..Reserved
 *  0b010..Very-Low-Power Stop (VLPS)
 *  0b011..Low-Leakage Stop (LLS)
 *  0b100..Very-Low-Leakage Stop (VLLSx)
 *  0b101..Reserved
 *  0b110..Reseved
 *  0b111..Reserved
 */
#define SMC_PMCTRL_STOPM(x)                      (((uint8_t)(((uint8_t)(x)) << SMC_PMCTRL_STOPM_SHIFT)) & SMC_PMCTRL_STOPM_MASK)

#define SMC_PMCTRL_STOPA_MASK                    (0x8U)
#define SMC_PMCTRL_STOPA_SHIFT                   (3U)
/*! STOPA - Stop Aborted
 *  0b0..The previous stop mode entry was successsful.
 *  0b1..The previous stop mode entry was aborted.
 */
#define SMC_PMCTRL_STOPA(x)                      (((uint8_t)(((uint8_t)(x)) << SMC_PMCTRL_STOPA_SHIFT)) & SMC_PMCTRL_STOPA_MASK)

#define SMC_PMCTRL_RUNM_MASK                     (0x60U)
#define SMC_PMCTRL_RUNM_SHIFT                    (5U)
/*! RUNM - Run Mode Control
 *  0b00..Normal Run mode (RUN)
 *  0b01..Reserved
 *  0b10..Very-Low-Power Run mode (VLPR)
 *  0b11..Reserved
 */
#define SMC_PMCTRL_RUNM(x)                       (((uint8_t)(((uint8_t)(x)) << SMC_PMCTRL_RUNM_SHIFT)) & SMC_PMCTRL_RUNM_MASK)
/*! @} */

/*! @name STOPCTRL - Stop Control Register */
/*! @{ */

#define SMC_STOPCTRL_VLLSM_MASK                  (0x7U)
#define SMC_STOPCTRL_VLLSM_SHIFT                 (0U)
/*! VLLSM - VLLS Mode Control
 *  0b000..VLLS0
 *  0b001..VLLS1
 *  0b010..Reserved
 *  0b011..VLLS3
 *  0b100..Reserved
 *  0b101..Reserved
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define SMC_STOPCTRL_VLLSM(x)                    (((uint8_t)(((uint8_t)(x)) << SMC_STOPCTRL_VLLSM_SHIFT)) & SMC_STOPCTRL_VLLSM_MASK)

#define SMC_STOPCTRL_PORPO_MASK                  (0x20U)
#define SMC_STOPCTRL_PORPO_SHIFT                 (5U)
/*! PORPO - POR Power Option
 *  0b0..POR detect circuit is enabled in VLLS0
 *  0b1..POR detect circuit is disabled in VLLS0
 */
#define SMC_STOPCTRL_PORPO(x)                    (((uint8_t)(((uint8_t)(x)) << SMC_STOPCTRL_PORPO_SHIFT)) & SMC_STOPCTRL_PORPO_MASK)

#define SMC_STOPCTRL_PSTOPO_MASK                 (0xC0U)
#define SMC_STOPCTRL_PSTOPO_SHIFT                (6U)
/*! PSTOPO - Partial Stop Option
 *  0b00..STOP - Normal Stop mode
 *  0b01..PSTOP1 - Partial Stop with both system and bus clocks disabled
 *  0b10..PSTOP2 - Partial Stop with system clock disabled and bus clock enabled
 *  0b11..Reserved
 */
#define SMC_STOPCTRL_PSTOPO(x)                   (((uint8_t)(((uint8_t)(x)) << SMC_STOPCTRL_PSTOPO_SHIFT)) & SMC_STOPCTRL_PSTOPO_MASK)
/*! @} */

/*! @name PMSTAT - Power Mode Status register */
/*! @{ */

#define SMC_PMSTAT_PMSTAT_MASK                   (0xFFU)
#define SMC_PMSTAT_PMSTAT_SHIFT                  (0U)
/*! PMSTAT - Power Mode Status */
#define SMC_PMSTAT_PMSTAT(x)                     (((uint8_t)(((uint8_t)(x)) << SMC_PMSTAT_PMSTAT_SHIFT)) & SMC_PMSTAT_PMSTAT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SMC_Register_Masks */


/* SMC - Peripheral instance base addresses */
/** Peripheral SMC base address */
#define SMC_BASE                                 (0x4007E000u)
/** Peripheral SMC base pointer */
#define SMC                                      ((SMC_Type *)SMC_BASE)
/** Array initializer of SMC peripheral base addresses */
#define SMC_BASE_ADDRS                           { SMC_BASE }
/** Array initializer of SMC peripheral base pointers */
#define SMC_BASE_PTRS                            { SMC }

/*!
 * @}
 */ /* end of group SMC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SPI Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Peripheral_Access_Layer SPI Peripheral Access Layer
 * @{
 */

/** SPI - Register Layout Typedef */
typedef struct {
  __IO uint8_t S;                                  /**< SPI Status Register, offset: 0x0 */
  __IO uint8_t BR;                                 /**< SPI Baud Rate Register, offset: 0x1 */
  __IO uint8_t C2;                                 /**< SPI Control Register 2, offset: 0x2 */
  __IO uint8_t C1;                                 /**< SPI Control Register 1, offset: 0x3 */
  __IO uint8_t ML;                                 /**< SPI Match Register low, offset: 0x4 */
  __IO uint8_t MH;                                 /**< SPI match register high, offset: 0x5 */
  __IO uint8_t DL;                                 /**< SPI Data Register low, offset: 0x6 */
  __IO uint8_t DH;                                 /**< SPI data register high, offset: 0x7 */
       uint8_t RESERVED_0[2];
  __IO uint8_t CI;                                 /**< SPI clear interrupt register, offset: 0xA, available only on: SPI1 (missing on SPI0) */
  __IO uint8_t C3;                                 /**< SPI control register 3, offset: 0xB, available only on: SPI1 (missing on SPI0) */
} SPI_Type;

/* ----------------------------------------------------------------------------
   -- SPI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Masks SPI Register Masks
 * @{
 */

/*! @name S - SPI Status Register */
/*! @{ */

#define SPI_S_RFIFOEF_MASK                       (0x1U)
#define SPI_S_RFIFOEF_SHIFT                      (0U)
/*! RFIFOEF - SPI read FIFO empty flag
 *  0b0..Read FIFO has data. Reads of the DH:DL registers in 16-bit mode or the DL register in 8-bit mode will empty the read FIFO.
 *  0b1..Read FIFO is empty.
 */
#define SPI_S_RFIFOEF(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_S_RFIFOEF_SHIFT)) & SPI_S_RFIFOEF_MASK)

#define SPI_S_TXFULLF_MASK                       (0x2U)
#define SPI_S_TXFULLF_SHIFT                      (1U)
/*! TXFULLF - Transmit FIFO full flag
 *  0b0..Transmit FIFO has less than 8 bytes
 *  0b1..Transmit FIFO has 8 bytes of data
 */
#define SPI_S_TXFULLF(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_S_TXFULLF_SHIFT)) & SPI_S_TXFULLF_MASK)

#define SPI_S_TNEAREF_MASK                       (0x4U)
#define SPI_S_TNEAREF_SHIFT                      (2U)
/*! TNEAREF - Transmit FIFO nearly empty flag
 *  0b0..Transmit FIFO has more than 16 bits (when C3[TNEAREF_MARK] is 0) or more than 32 bits (when C3[TNEAREF_MARK] is 1) remaining to transmit
 *  0b1..Transmit FIFO has an amount of data equal to or less than 16 bits (when C3[TNEAREF_MARK] is 0) or 32 bits
 *       (when C3[TNEAREF_MARK] is 1) remaining to transmit
 */
#define SPI_S_TNEAREF(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_S_TNEAREF_SHIFT)) & SPI_S_TNEAREF_MASK)

#define SPI_S_RNFULLF_MASK                       (0x8U)
#define SPI_S_RNFULLF_SHIFT                      (3U)
/*! RNFULLF - Receive FIFO nearly full flag
 *  0b0..Receive FIFO has received less than 48 bits (when C3[RNFULLF_MARK] is 0) or less than 32 bits (when C3[RNFULLF_MARK] is 1)
 *  0b1..Receive FIFO has received data of an amount equal to or greater than 48 bits (when C3[RNFULLF_MARK] is 0)
 *       or 32 bits (when C3[RNFULLF_MARK] is 1)
 */
#define SPI_S_RNFULLF(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_S_RNFULLF_SHIFT)) & SPI_S_RNFULLF_MASK)

#define SPI_S_MODF_MASK                          (0x10U)
#define SPI_S_MODF_SHIFT                         (4U)
/*! MODF - Master Mode Fault Flag
 *  0b0..No mode fault error
 *  0b1..Mode fault error detected
 */
#define SPI_S_MODF(x)                            (((uint8_t)(((uint8_t)(x)) << SPI_S_MODF_SHIFT)) & SPI_S_MODF_MASK)

#define SPI_S_SPTEF_MASK                         (0x20U)
#define SPI_S_SPTEF_SHIFT                        (5U)
/*! SPTEF - SPI Transmit Buffer Empty Flag (when FIFO is not supported or not enabled) or SPI
 *    transmit FIFO empty flag (when FIFO is supported and enabled)
 *  0b0..SPI transmit buffer not empty (when FIFOMODE is not present or is 0) or SPI FIFO not empty (when FIFOMODE is 1)
 *  0b1..SPI transmit buffer empty (when FIFOMODE is not present or is 0) or SPI FIFO empty (when FIFOMODE is 1)
 */
#define SPI_S_SPTEF(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_S_SPTEF_SHIFT)) & SPI_S_SPTEF_MASK)

#define SPI_S_SPMF_MASK                          (0x40U)
#define SPI_S_SPMF_SHIFT                         (6U)
/*! SPMF - SPI Match Flag
 *  0b0..Value in the receive data buffer does not match the value in the MH:ML registers
 *  0b1..Value in the receive data buffer matches the value in the MH:ML registers
 */
#define SPI_S_SPMF(x)                            (((uint8_t)(((uint8_t)(x)) << SPI_S_SPMF_SHIFT)) & SPI_S_SPMF_MASK)

#define SPI_S_SPRF_MASK                          (0x80U)
#define SPI_S_SPRF_SHIFT                         (7U)
/*! SPRF - SPI Read Buffer Full Flag (when FIFO is not supported or not enabled) or SPI read FIFO
 *    FULL flag (when FIFO is supported and enabled)
 *  0b0..No data available in the receive data buffer (when FIFOMODE is not present or is 0) or Read FIFO is not full (when FIFOMODE is 1)
 *  0b1..Data available in the receive data buffer (when FIFOMODE is not present or is 0) or Read FIFO is full (when FIFOMODE is 1)
 */
#define SPI_S_SPRF(x)                            (((uint8_t)(((uint8_t)(x)) << SPI_S_SPRF_SHIFT)) & SPI_S_SPRF_MASK)
/*! @} */

/*! @name BR - SPI Baud Rate Register */
/*! @{ */

#define SPI_BR_SPR_MASK                          (0xFU)
#define SPI_BR_SPR_SHIFT                         (0U)
/*! SPR - SPI Baud Rate Divisor
 *  0b0000..Baud rate divisor is 2.
 *  0b0001..Baud rate divisor is 4.
 *  0b0010..Baud rate divisor is 8.
 *  0b0011..Baud rate divisor is 16.
 *  0b0100..Baud rate divisor is 32.
 *  0b0101..Baud rate divisor is 64.
 *  0b0110..Baud rate divisor is 128.
 *  0b0111..Baud rate divisor is 256.
 *  0b1000..Baud rate divisor is 512.
 */
#define SPI_BR_SPR(x)                            (((uint8_t)(((uint8_t)(x)) << SPI_BR_SPR_SHIFT)) & SPI_BR_SPR_MASK)

#define SPI_BR_SPPR_MASK                         (0x70U)
#define SPI_BR_SPPR_SHIFT                        (4U)
/*! SPPR - SPI Baud Rate Prescale Divisor
 *  0b000..Baud rate prescaler divisor is 1.
 *  0b001..Baud rate prescaler divisor is 2.
 *  0b010..Baud rate prescaler divisor is 3.
 *  0b011..Baud rate prescaler divisor is 4.
 *  0b100..Baud rate prescaler divisor is 5.
 *  0b101..Baud rate prescaler divisor is 6.
 *  0b110..Baud rate prescaler divisor is 7.
 *  0b111..Baud rate prescaler divisor is 8.
 */
#define SPI_BR_SPPR(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_BR_SPPR_SHIFT)) & SPI_BR_SPPR_MASK)
/*! @} */

/*! @name C2 - SPI Control Register 2 */
/*! @{ */

#define SPI_C2_SPC0_MASK                         (0x1U)
#define SPI_C2_SPC0_SHIFT                        (0U)
/*! SPC0 - SPI Pin Control 0
 *  0b0..SPI uses separate pins for data input and data output (pin mode is normal). In master mode of operation:
 *       MISO is master in and MOSI is master out. In slave mode of operation: MISO is slave out and MOSI is slave
 *       in.
 *  0b1..SPI configured for single-wire bidirectional operation (pin mode is bidirectional). In master mode of
 *       operation: MISO is not used by SPI; MOSI is master in when BIDIROE is 0 or master I/O when BIDIROE is 1. In
 *       slave mode of operation: MISO is slave in when BIDIROE is 0 or slave I/O when BIDIROE is 1; MOSI is not
 *       used by SPI.
 */
#define SPI_C2_SPC0(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_C2_SPC0_SHIFT)) & SPI_C2_SPC0_MASK)

#define SPI_C2_SPISWAI_MASK                      (0x2U)
#define SPI_C2_SPISWAI_SHIFT                     (1U)
/*! SPISWAI - SPI Stop in Wait Mode
 *  0b0..SPI clocks continue to operate in Wait mode.
 *  0b1..SPI clocks stop when the MCU enters Wait mode.
 */
#define SPI_C2_SPISWAI(x)                        (((uint8_t)(((uint8_t)(x)) << SPI_C2_SPISWAI_SHIFT)) & SPI_C2_SPISWAI_MASK)

#define SPI_C2_RXDMAE_MASK                       (0x4U)
#define SPI_C2_RXDMAE_SHIFT                      (2U)
/*! RXDMAE - Receive DMA enable
 *  0b0..DMA request for receive is disabled and interrupt from SPRF is allowed
 *  0b1..DMA request for receive is enabled and interrupt from SPRF is disabled
 */
#define SPI_C2_RXDMAE(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_C2_RXDMAE_SHIFT)) & SPI_C2_RXDMAE_MASK)

#define SPI_C2_BIDIROE_MASK                      (0x8U)
#define SPI_C2_BIDIROE_SHIFT                     (3U)
/*! BIDIROE - Bidirectional Mode Output Enable
 *  0b0..Output driver disabled so SPI data I/O pin acts as an input
 *  0b1..SPI I/O pin enabled as an output
 */
#define SPI_C2_BIDIROE(x)                        (((uint8_t)(((uint8_t)(x)) << SPI_C2_BIDIROE_SHIFT)) & SPI_C2_BIDIROE_MASK)

#define SPI_C2_MODFEN_MASK                       (0x10U)
#define SPI_C2_MODFEN_SHIFT                      (4U)
/*! MODFEN - Master Mode-Fault Function Enable
 *  0b0..Mode fault function disabled, master SS pin reverts to general-purpose I/O not controlled by SPI
 *  0b1..Mode fault function enabled, master SS pin acts as the mode fault input or the slave select output
 */
#define SPI_C2_MODFEN(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_C2_MODFEN_SHIFT)) & SPI_C2_MODFEN_MASK)

#define SPI_C2_TXDMAE_MASK                       (0x20U)
#define SPI_C2_TXDMAE_SHIFT                      (5U)
/*! TXDMAE - Transmit DMA enable
 *  0b0..DMA request for transmit is disabled and interrupt from SPTEF is allowed
 *  0b1..DMA request for transmit is enabled and interrupt from SPTEF is disabled
 */
#define SPI_C2_TXDMAE(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_C2_TXDMAE_SHIFT)) & SPI_C2_TXDMAE_MASK)

#define SPI_C2_SPIMODE_MASK                      (0x40U)
#define SPI_C2_SPIMODE_SHIFT                     (6U)
/*! SPIMODE - SPI 8-bit or 16-bit mode
 *  0b0..8-bit SPI shift register, match register, and buffers
 *  0b1..16-bit SPI shift register, match register, and buffers
 */
#define SPI_C2_SPIMODE(x)                        (((uint8_t)(((uint8_t)(x)) << SPI_C2_SPIMODE_SHIFT)) & SPI_C2_SPIMODE_MASK)

#define SPI_C2_SPMIE_MASK                        (0x80U)
#define SPI_C2_SPMIE_SHIFT                       (7U)
/*! SPMIE - SPI Match Interrupt Enable
 *  0b0..Interrupts from SPMF inhibited (use polling)
 *  0b1..When SPMF is 1, requests a hardware interrupt
 */
#define SPI_C2_SPMIE(x)                          (((uint8_t)(((uint8_t)(x)) << SPI_C2_SPMIE_SHIFT)) & SPI_C2_SPMIE_MASK)
/*! @} */

/*! @name C1 - SPI Control Register 1 */
/*! @{ */

#define SPI_C1_LSBFE_MASK                        (0x1U)
#define SPI_C1_LSBFE_SHIFT                       (0U)
/*! LSBFE - LSB First (shifter direction)
 *  0b0..SPI serial data transfers start with the most significant bit.
 *  0b1..SPI serial data transfers start with the least significant bit.
 */
#define SPI_C1_LSBFE(x)                          (((uint8_t)(((uint8_t)(x)) << SPI_C1_LSBFE_SHIFT)) & SPI_C1_LSBFE_MASK)

#define SPI_C1_SSOE_MASK                         (0x2U)
#define SPI_C1_SSOE_SHIFT                        (1U)
/*! SSOE - Slave Select Output Enable
 *  0b0..When C2[MODFEN] is 0: In master mode, SS pin function is general-purpose I/O (not SPI). In slave mode, SS
 *       pin function is slave select input. When C2[MODFEN] is 1: In master mode, SS pin function is SS input for
 *       mode fault. In slave mode, SS pin function is slave select input.
 *  0b1..When C2[MODFEN] is 0: In master mode, SS pin function is general-purpose I/O (not SPI). In slave mode, SS
 *       pin function is slave select input. When C2[MODFEN] is 1: In master mode, SS pin function is automatic SS
 *       output. In slave mode: SS pin function is slave select input.
 */
#define SPI_C1_SSOE(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_C1_SSOE_SHIFT)) & SPI_C1_SSOE_MASK)

#define SPI_C1_CPHA_MASK                         (0x4U)
#define SPI_C1_CPHA_SHIFT                        (2U)
/*! CPHA - Clock Phase
 *  0b0..First edge on SPSCK occurs at the middle of the first cycle of a data transfer.
 *  0b1..First edge on SPSCK occurs at the start of the first cycle of a data transfer.
 */
#define SPI_C1_CPHA(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_C1_CPHA_SHIFT)) & SPI_C1_CPHA_MASK)

#define SPI_C1_CPOL_MASK                         (0x8U)
#define SPI_C1_CPOL_SHIFT                        (3U)
/*! CPOL - Clock Polarity
 *  0b0..Active-high SPI clock (idles low)
 *  0b1..Active-low SPI clock (idles high)
 */
#define SPI_C1_CPOL(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_C1_CPOL_SHIFT)) & SPI_C1_CPOL_MASK)

#define SPI_C1_MSTR_MASK                         (0x10U)
#define SPI_C1_MSTR_SHIFT                        (4U)
/*! MSTR - Master/Slave Mode Select
 *  0b0..SPI module configured as a slave SPI device
 *  0b1..SPI module configured as a master SPI device
 */
#define SPI_C1_MSTR(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_C1_MSTR_SHIFT)) & SPI_C1_MSTR_MASK)

#define SPI_C1_SPTIE_MASK                        (0x20U)
#define SPI_C1_SPTIE_SHIFT                       (5U)
/*! SPTIE - SPI Transmit Interrupt Enable
 *  0b0..Interrupts from SPTEF inhibited (use polling)
 *  0b1..When SPTEF is 1, hardware interrupt requested
 */
#define SPI_C1_SPTIE(x)                          (((uint8_t)(((uint8_t)(x)) << SPI_C1_SPTIE_SHIFT)) & SPI_C1_SPTIE_MASK)

#define SPI_C1_SPE_MASK                          (0x40U)
#define SPI_C1_SPE_SHIFT                         (6U)
/*! SPE - SPI System Enable
 *  0b0..SPI system inactive
 *  0b1..SPI system enabled
 */
#define SPI_C1_SPE(x)                            (((uint8_t)(((uint8_t)(x)) << SPI_C1_SPE_SHIFT)) & SPI_C1_SPE_MASK)

#define SPI_C1_SPIE_MASK                         (0x80U)
#define SPI_C1_SPIE_SHIFT                        (7U)
/*! SPIE - SPI Interrupt Enable: for SPRF and MODF (when FIFO is not supported or not enabled) or
 *    for read FIFO (when FIFO is supported and enabled)
 *  0b0..Interrupts from SPRF and MODF are inhibited-use polling (when FIFOMODE is not present or is 0) or Read
 *       FIFO Full Interrupts are disabled (when FIFOMODE is 1)
 *  0b1..Request a hardware interrupt when SPRF or MODF is 1 (when FIFOMODE is not present or is 0) or Read FIFO
 *       Full Interrupts are enabled (when FIFOMODE is 1)
 */
#define SPI_C1_SPIE(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_C1_SPIE_SHIFT)) & SPI_C1_SPIE_MASK)
/*! @} */

/*! @name ML - SPI Match Register low */
/*! @{ */

#define SPI_ML_Bits_MASK                         (0xFFU)
#define SPI_ML_Bits_SHIFT                        (0U)
/*! Bits - Hardware compare value (low byte) */
#define SPI_ML_Bits(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_ML_Bits_SHIFT)) & SPI_ML_Bits_MASK)
/*! @} */

/*! @name MH - SPI match register high */
/*! @{ */

#define SPI_MH_Bits_MASK                         (0xFFU)
#define SPI_MH_Bits_SHIFT                        (0U)
/*! Bits - Hardware compare value (high byte) */
#define SPI_MH_Bits(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_MH_Bits_SHIFT)) & SPI_MH_Bits_MASK)
/*! @} */

/*! @name DL - SPI Data Register low */
/*! @{ */

#define SPI_DL_Bits_MASK                         (0xFFU)
#define SPI_DL_Bits_SHIFT                        (0U)
/*! Bits - Data (low byte) */
#define SPI_DL_Bits(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_DL_Bits_SHIFT)) & SPI_DL_Bits_MASK)
/*! @} */

/*! @name DH - SPI data register high */
/*! @{ */

#define SPI_DH_Bits_MASK                         (0xFFU)
#define SPI_DH_Bits_SHIFT                        (0U)
/*! Bits - Data (high byte) */
#define SPI_DH_Bits(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_DH_Bits_SHIFT)) & SPI_DH_Bits_MASK)
/*! @} */

/*! @name CI - SPI clear interrupt register */
/*! @{ */

#define SPI_CI_SPRFCI_MASK                       (0x1U)
#define SPI_CI_SPRFCI_SHIFT                      (0U)
/*! SPRFCI - Receive FIFO full flag clear interrupt */
#define SPI_CI_SPRFCI(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_CI_SPRFCI_SHIFT)) & SPI_CI_SPRFCI_MASK)

#define SPI_CI_SPTEFCI_MASK                      (0x2U)
#define SPI_CI_SPTEFCI_SHIFT                     (1U)
/*! SPTEFCI - Transmit FIFO empty flag clear interrupt */
#define SPI_CI_SPTEFCI(x)                        (((uint8_t)(((uint8_t)(x)) << SPI_CI_SPTEFCI_SHIFT)) & SPI_CI_SPTEFCI_MASK)

#define SPI_CI_RNFULLFCI_MASK                    (0x4U)
#define SPI_CI_RNFULLFCI_SHIFT                   (2U)
/*! RNFULLFCI - Receive FIFO nearly full flag clear interrupt */
#define SPI_CI_RNFULLFCI(x)                      (((uint8_t)(((uint8_t)(x)) << SPI_CI_RNFULLFCI_SHIFT)) & SPI_CI_RNFULLFCI_MASK)

#define SPI_CI_TNEAREFCI_MASK                    (0x8U)
#define SPI_CI_TNEAREFCI_SHIFT                   (3U)
/*! TNEAREFCI - Transmit FIFO nearly empty flag clear interrupt */
#define SPI_CI_TNEAREFCI(x)                      (((uint8_t)(((uint8_t)(x)) << SPI_CI_TNEAREFCI_SHIFT)) & SPI_CI_TNEAREFCI_MASK)

#define SPI_CI_RXFOF_MASK                        (0x10U)
#define SPI_CI_RXFOF_SHIFT                       (4U)
/*! RXFOF - Receive FIFO overflow flag
 *  0b0..Receive FIFO overflow condition has not occurred
 *  0b1..Receive FIFO overflow condition occurred
 */
#define SPI_CI_RXFOF(x)                          (((uint8_t)(((uint8_t)(x)) << SPI_CI_RXFOF_SHIFT)) & SPI_CI_RXFOF_MASK)

#define SPI_CI_TXFOF_MASK                        (0x20U)
#define SPI_CI_TXFOF_SHIFT                       (5U)
/*! TXFOF - Transmit FIFO overflow flag
 *  0b0..Transmit FIFO overflow condition has not occurred
 *  0b1..Transmit FIFO overflow condition occurred
 */
#define SPI_CI_TXFOF(x)                          (((uint8_t)(((uint8_t)(x)) << SPI_CI_TXFOF_SHIFT)) & SPI_CI_TXFOF_MASK)

#define SPI_CI_RXFERR_MASK                       (0x40U)
#define SPI_CI_RXFERR_SHIFT                      (6U)
/*! RXFERR - Receive FIFO error flag
 *  0b0..No receive FIFO error occurred
 *  0b1..A receive FIFO error occurred
 */
#define SPI_CI_RXFERR(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_CI_RXFERR_SHIFT)) & SPI_CI_RXFERR_MASK)

#define SPI_CI_TXFERR_MASK                       (0x80U)
#define SPI_CI_TXFERR_SHIFT                      (7U)
/*! TXFERR - Transmit FIFO error flag
 *  0b0..No transmit FIFO error occurred
 *  0b1..A transmit FIFO error occurred
 */
#define SPI_CI_TXFERR(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_CI_TXFERR_SHIFT)) & SPI_CI_TXFERR_MASK)
/*! @} */

/*! @name C3 - SPI control register 3 */
/*! @{ */

#define SPI_C3_FIFOMODE_MASK                     (0x1U)
#define SPI_C3_FIFOMODE_SHIFT                    (0U)
/*! FIFOMODE - FIFO mode enable
 *  0b0..Buffer mode disabled
 *  0b1..Data available in the receive data buffer
 */
#define SPI_C3_FIFOMODE(x)                       (((uint8_t)(((uint8_t)(x)) << SPI_C3_FIFOMODE_SHIFT)) & SPI_C3_FIFOMODE_MASK)

#define SPI_C3_RNFULLIEN_MASK                    (0x2U)
#define SPI_C3_RNFULLIEN_SHIFT                   (1U)
/*! RNFULLIEN - Receive FIFO nearly full interrupt enable
 *  0b0..No interrupt upon RNFULLF being set
 *  0b1..Enable interrupts upon RNFULLF being set
 */
#define SPI_C3_RNFULLIEN(x)                      (((uint8_t)(((uint8_t)(x)) << SPI_C3_RNFULLIEN_SHIFT)) & SPI_C3_RNFULLIEN_MASK)

#define SPI_C3_TNEARIEN_MASK                     (0x4U)
#define SPI_C3_TNEARIEN_SHIFT                    (2U)
/*! TNEARIEN - Transmit FIFO nearly empty interrupt enable
 *  0b0..No interrupt upon TNEAREF being set
 *  0b1..Enable interrupts upon TNEAREF being set
 */
#define SPI_C3_TNEARIEN(x)                       (((uint8_t)(((uint8_t)(x)) << SPI_C3_TNEARIEN_SHIFT)) & SPI_C3_TNEARIEN_MASK)

#define SPI_C3_INTCLR_MASK                       (0x8U)
#define SPI_C3_INTCLR_SHIFT                      (3U)
/*! INTCLR - Interrupt clearing mechanism select
 *  0b0..These interrupts are cleared when the corresponding flags are cleared depending on the state of the FIFOs
 *  0b1..These interrupts are cleared by writing the corresponding bits in the CI register
 */
#define SPI_C3_INTCLR(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_C3_INTCLR_SHIFT)) & SPI_C3_INTCLR_MASK)

#define SPI_C3_RNFULLF_MARK_MASK                 (0x10U)
#define SPI_C3_RNFULLF_MARK_SHIFT                (4U)
/*! RNFULLF_MARK - Receive FIFO nearly full watermark
 *  0b0..RNFULLF is set when the receive FIFO has 48 bits or more
 *  0b1..RNFULLF is set when the receive FIFO has 32 bits or more
 */
#define SPI_C3_RNFULLF_MARK(x)                   (((uint8_t)(((uint8_t)(x)) << SPI_C3_RNFULLF_MARK_SHIFT)) & SPI_C3_RNFULLF_MARK_MASK)

#define SPI_C3_TNEAREF_MARK_MASK                 (0x20U)
#define SPI_C3_TNEAREF_MARK_SHIFT                (5U)
/*! TNEAREF_MARK - Transmit FIFO nearly empty watermark
 *  0b0..TNEAREF is set when the transmit FIFO has 16 bits or less
 *  0b1..TNEAREF is set when the transmit FIFO has 32 bits or less
 */
#define SPI_C3_TNEAREF_MARK(x)                   (((uint8_t)(((uint8_t)(x)) << SPI_C3_TNEAREF_MARK_SHIFT)) & SPI_C3_TNEAREF_MARK_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SPI_Register_Masks */


/* SPI - Peripheral instance base addresses */
/** Peripheral SPI0 base address */
#define SPI0_BASE                                (0x40076000u)
/** Peripheral SPI0 base pointer */
#define SPI0                                     ((SPI_Type *)SPI0_BASE)
/** Peripheral SPI1 base address */
#define SPI1_BASE                                (0x40077000u)
/** Peripheral SPI1 base pointer */
#define SPI1                                     ((SPI_Type *)SPI1_BASE)
/** Array initializer of SPI peripheral base addresses */
#define SPI_BASE_ADDRS                           { SPI0_BASE, SPI1_BASE }
/** Array initializer of SPI peripheral base pointers */
#define SPI_BASE_PTRS                            { SPI0, SPI1 }
/** Interrupt vectors for the SPI peripheral type */
#define SPI_IRQS                                 { SPI0_IRQn, SPI1_IRQn }

/*!
 * @}
 */ /* end of group SPI_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- TPM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TPM_Peripheral_Access_Layer TPM Peripheral Access Layer
 * @{
 */

/** TPM - Register Layout Typedef */
typedef struct {
  __IO uint32_t SC;                                /**< Status and Control, offset: 0x0 */
  __IO uint32_t CNT;                               /**< Counter, offset: 0x4 */
  __IO uint32_t MOD;                               /**< Modulo, offset: 0x8 */
  struct {                                         /* offset: 0xC, array step: 0x8 */
    __IO uint32_t CnSC;                              /**< Channel (n) Status and Control, array offset: 0xC, array step: 0x8, irregular array, not all indices are valid */
    __IO uint32_t CnV;                               /**< Channel (n) Value, array offset: 0x10, array step: 0x8, irregular array, not all indices are valid */
  } CONTROLS[6];
       uint8_t RESERVED_0[20];
  __IO uint32_t STATUS;                            /**< Capture and Compare Status, offset: 0x50 */
       uint8_t RESERVED_1[28];
  __IO uint32_t POL;                               /**< Channel Polarity, offset: 0x70 */
       uint8_t RESERVED_2[16];
  __IO uint32_t CONF;                              /**< Configuration, offset: 0x84 */
} TPM_Type;

/* ----------------------------------------------------------------------------
   -- TPM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TPM_Register_Masks TPM Register Masks
 * @{
 */

/*! @name SC - Status and Control */
/*! @{ */

#define TPM_SC_PS_MASK                           (0x7U)
#define TPM_SC_PS_SHIFT                          (0U)
/*! PS - Prescale Factor Selection
 *  0b000..Divide by 1
 *  0b001..Divide by 2
 *  0b010..Divide by 4
 *  0b011..Divide by 8
 *  0b100..Divide by 16
 *  0b101..Divide by 32
 *  0b110..Divide by 64
 *  0b111..Divide by 128
 */
#define TPM_SC_PS(x)                             (((uint32_t)(((uint32_t)(x)) << TPM_SC_PS_SHIFT)) & TPM_SC_PS_MASK)

#define TPM_SC_CMOD_MASK                         (0x18U)
#define TPM_SC_CMOD_SHIFT                        (3U)
/*! CMOD - Clock Mode Selection
 *  0b00..TPM counter is disabled
 *  0b01..TPM counter increments on every TPM counter clock
 *  0b10..TPM counter increments on rising edge of TPM_EXTCLK synchronized to the TPM counter clock
 *  0b11..Reserved
 */
#define TPM_SC_CMOD(x)                           (((uint32_t)(((uint32_t)(x)) << TPM_SC_CMOD_SHIFT)) & TPM_SC_CMOD_MASK)

#define TPM_SC_CPWMS_MASK                        (0x20U)
#define TPM_SC_CPWMS_SHIFT                       (5U)
/*! CPWMS - Center-Aligned PWM Select
 *  0b0..TPM counter operates in up counting mode.
 *  0b1..TPM counter operates in up-down counting mode.
 */
#define TPM_SC_CPWMS(x)                          (((uint32_t)(((uint32_t)(x)) << TPM_SC_CPWMS_SHIFT)) & TPM_SC_CPWMS_MASK)

#define TPM_SC_TOIE_MASK                         (0x40U)
#define TPM_SC_TOIE_SHIFT                        (6U)
/*! TOIE - Timer Overflow Interrupt Enable
 *  0b0..Disable TOF interrupts. Use software polling or DMA request.
 *  0b1..Enable TOF interrupts. An interrupt is generated when TOF equals one.
 */
#define TPM_SC_TOIE(x)                           (((uint32_t)(((uint32_t)(x)) << TPM_SC_TOIE_SHIFT)) & TPM_SC_TOIE_MASK)

#define TPM_SC_TOF_MASK                          (0x80U)
#define TPM_SC_TOF_SHIFT                         (7U)
/*! TOF - Timer Overflow Flag
 *  0b0..TPM counter has not overflowed.
 *  0b1..TPM counter has overflowed.
 */
#define TPM_SC_TOF(x)                            (((uint32_t)(((uint32_t)(x)) << TPM_SC_TOF_SHIFT)) & TPM_SC_TOF_MASK)

#define TPM_SC_DMA_MASK                          (0x100U)
#define TPM_SC_DMA_SHIFT                         (8U)
/*! DMA - DMA Enable
 *  0b0..Disables DMA transfers.
 *  0b1..Enables DMA transfers.
 */
#define TPM_SC_DMA(x)                            (((uint32_t)(((uint32_t)(x)) << TPM_SC_DMA_SHIFT)) & TPM_SC_DMA_MASK)
/*! @} */

/*! @name CNT - Counter */
/*! @{ */

#define TPM_CNT_COUNT_MASK                       (0xFFFFU)
#define TPM_CNT_COUNT_SHIFT                      (0U)
/*! COUNT - Counter value */
#define TPM_CNT_COUNT(x)                         (((uint32_t)(((uint32_t)(x)) << TPM_CNT_COUNT_SHIFT)) & TPM_CNT_COUNT_MASK)
/*! @} */

/*! @name MOD - Modulo */
/*! @{ */

#define TPM_MOD_MOD_MASK                         (0xFFFFU)
#define TPM_MOD_MOD_SHIFT                        (0U)
/*! MOD - Modulo value */
#define TPM_MOD_MOD(x)                           (((uint32_t)(((uint32_t)(x)) << TPM_MOD_MOD_SHIFT)) & TPM_MOD_MOD_MASK)
/*! @} */

/*! @name CnSC - Channel (n) Status and Control */
/*! @{ */

#define TPM_CnSC_DMA_MASK                        (0x1U)
#define TPM_CnSC_DMA_SHIFT                       (0U)
/*! DMA - DMA Enable
 *  0b0..Disable DMA transfers.
 *  0b1..Enable DMA transfers.
 */
#define TPM_CnSC_DMA(x)                          (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_DMA_SHIFT)) & TPM_CnSC_DMA_MASK)

#define TPM_CnSC_ELSA_MASK                       (0x4U)
#define TPM_CnSC_ELSA_SHIFT                      (2U)
/*! ELSA - Edge or Level Select */
#define TPM_CnSC_ELSA(x)                         (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_ELSA_SHIFT)) & TPM_CnSC_ELSA_MASK)

#define TPM_CnSC_ELSB_MASK                       (0x8U)
#define TPM_CnSC_ELSB_SHIFT                      (3U)
/*! ELSB - Edge or Level Select */
#define TPM_CnSC_ELSB(x)                         (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_ELSB_SHIFT)) & TPM_CnSC_ELSB_MASK)

#define TPM_CnSC_MSA_MASK                        (0x10U)
#define TPM_CnSC_MSA_SHIFT                       (4U)
/*! MSA - Channel Mode Select */
#define TPM_CnSC_MSA(x)                          (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_MSA_SHIFT)) & TPM_CnSC_MSA_MASK)

#define TPM_CnSC_MSB_MASK                        (0x20U)
#define TPM_CnSC_MSB_SHIFT                       (5U)
/*! MSB - Channel Mode Select */
#define TPM_CnSC_MSB(x)                          (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_MSB_SHIFT)) & TPM_CnSC_MSB_MASK)

#define TPM_CnSC_CHIE_MASK                       (0x40U)
#define TPM_CnSC_CHIE_SHIFT                      (6U)
/*! CHIE - Channel Interrupt Enable
 *  0b0..Disable channel interrupts.
 *  0b1..Enable channel interrupts.
 */
#define TPM_CnSC_CHIE(x)                         (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_CHIE_SHIFT)) & TPM_CnSC_CHIE_MASK)

#define TPM_CnSC_CHF_MASK                        (0x80U)
#define TPM_CnSC_CHF_SHIFT                       (7U)
/*! CHF - Channel Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_CnSC_CHF(x)                          (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_CHF_SHIFT)) & TPM_CnSC_CHF_MASK)
/*! @} */

/* The count of TPM_CnSC */
#define TPM_CnSC_COUNT                           (6U)

/*! @name CnV - Channel (n) Value */
/*! @{ */

#define TPM_CnV_VAL_MASK                         (0xFFFFU)
#define TPM_CnV_VAL_SHIFT                        (0U)
/*! VAL - Channel Value */
#define TPM_CnV_VAL(x)                           (((uint32_t)(((uint32_t)(x)) << TPM_CnV_VAL_SHIFT)) & TPM_CnV_VAL_MASK)
/*! @} */

/* The count of TPM_CnV */
#define TPM_CnV_COUNT                            (6U)

/*! @name STATUS - Capture and Compare Status */
/*! @{ */

#define TPM_STATUS_CH0F_MASK                     (0x1U)
#define TPM_STATUS_CH0F_SHIFT                    (0U)
/*! CH0F - Channel 0 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_STATUS_CH0F(x)                       (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_CH0F_SHIFT)) & TPM_STATUS_CH0F_MASK)

#define TPM_STATUS_CH1F_MASK                     (0x2U)
#define TPM_STATUS_CH1F_SHIFT                    (1U)
/*! CH1F - Channel 1 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_STATUS_CH1F(x)                       (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_CH1F_SHIFT)) & TPM_STATUS_CH1F_MASK)

#define TPM_STATUS_CH2F_MASK                     (0x4U)
#define TPM_STATUS_CH2F_SHIFT                    (2U)
/*! CH2F - Channel 2 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_STATUS_CH2F(x)                       (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_CH2F_SHIFT)) & TPM_STATUS_CH2F_MASK)

#define TPM_STATUS_CH3F_MASK                     (0x8U)
#define TPM_STATUS_CH3F_SHIFT                    (3U)
/*! CH3F - Channel 3 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_STATUS_CH3F(x)                       (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_CH3F_SHIFT)) & TPM_STATUS_CH3F_MASK)

#define TPM_STATUS_CH4F_MASK                     (0x10U)
#define TPM_STATUS_CH4F_SHIFT                    (4U)
/*! CH4F - Channel 4 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_STATUS_CH4F(x)                       (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_CH4F_SHIFT)) & TPM_STATUS_CH4F_MASK)

#define TPM_STATUS_CH5F_MASK                     (0x20U)
#define TPM_STATUS_CH5F_SHIFT                    (5U)
/*! CH5F - Channel 5 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_STATUS_CH5F(x)                       (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_CH5F_SHIFT)) & TPM_STATUS_CH5F_MASK)

#define TPM_STATUS_TOF_MASK                      (0x100U)
#define TPM_STATUS_TOF_SHIFT                     (8U)
/*! TOF - Timer Overflow Flag
 *  0b0..TPM counter has not overflowed.
 *  0b1..TPM counter has overflowed.
 */
#define TPM_STATUS_TOF(x)                        (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_TOF_SHIFT)) & TPM_STATUS_TOF_MASK)
/*! @} */

/*! @name POL - Channel Polarity */
/*! @{ */

#define TPM_POL_POL0_MASK                        (0x1U)
#define TPM_POL_POL0_SHIFT                       (0U)
/*! POL0 - Channel 0 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define TPM_POL_POL0(x)                          (((uint32_t)(((uint32_t)(x)) << TPM_POL_POL0_SHIFT)) & TPM_POL_POL0_MASK)

#define TPM_POL_POL1_MASK                        (0x2U)
#define TPM_POL_POL1_SHIFT                       (1U)
/*! POL1 - Channel 1 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define TPM_POL_POL1(x)                          (((uint32_t)(((uint32_t)(x)) << TPM_POL_POL1_SHIFT)) & TPM_POL_POL1_MASK)

#define TPM_POL_POL2_MASK                        (0x4U)
#define TPM_POL_POL2_SHIFT                       (2U)
/*! POL2 - Channel 2 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define TPM_POL_POL2(x)                          (((uint32_t)(((uint32_t)(x)) << TPM_POL_POL2_SHIFT)) & TPM_POL_POL2_MASK)

#define TPM_POL_POL3_MASK                        (0x8U)
#define TPM_POL_POL3_SHIFT                       (3U)
/*! POL3 - Channel 3 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define TPM_POL_POL3(x)                          (((uint32_t)(((uint32_t)(x)) << TPM_POL_POL3_SHIFT)) & TPM_POL_POL3_MASK)

#define TPM_POL_POL4_MASK                        (0x10U)
#define TPM_POL_POL4_SHIFT                       (4U)
/*! POL4 - Channel Polarity 4
 *  0b0..The channel polarity is active high
 *  0b1..The channel polarity is active low.
 */
#define TPM_POL_POL4(x)                          (((uint32_t)(((uint32_t)(x)) << TPM_POL_POL4_SHIFT)) & TPM_POL_POL4_MASK)

#define TPM_POL_POL5_MASK                        (0x20U)
#define TPM_POL_POL5_SHIFT                       (5U)
/*! POL5 - Channel 5 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define TPM_POL_POL5(x)                          (((uint32_t)(((uint32_t)(x)) << TPM_POL_POL5_SHIFT)) & TPM_POL_POL5_MASK)
/*! @} */

/*! @name CONF - Configuration */
/*! @{ */

#define TPM_CONF_DOZEEN_MASK                     (0x20U)
#define TPM_CONF_DOZEEN_SHIFT                    (5U)
/*! DOZEEN - Doze Enable
 *  0b0..Internal TPM counter continues in Doze mode.
 *  0b1..Internal TPM counter is paused and does not increment during Doze mode. Trigger inputs and input capture events are also ignored.
 */
#define TPM_CONF_DOZEEN(x)                       (((uint32_t)(((uint32_t)(x)) << TPM_CONF_DOZEEN_SHIFT)) & TPM_CONF_DOZEEN_MASK)

#define TPM_CONF_DBGMODE_MASK                    (0xC0U)
#define TPM_CONF_DBGMODE_SHIFT                   (6U)
/*! DBGMODE - Debug Mode
 *  0b00..TPM counter is paused and does not increment during debug mode. Trigger inputs and input capture events are also ignored.
 *  0b11..TPM counter continues in debug mode.
 */
#define TPM_CONF_DBGMODE(x)                      (((uint32_t)(((uint32_t)(x)) << TPM_CONF_DBGMODE_SHIFT)) & TPM_CONF_DBGMODE_MASK)

#define TPM_CONF_GTBSYNC_MASK                    (0x100U)
#define TPM_CONF_GTBSYNC_SHIFT                   (8U)
/*! GTBSYNC - Global Time Base Synchronization
 *  0b0..Global timebase synchronization disabled.
 *  0b1..Global timebase synchronization enabled.
 */
#define TPM_CONF_GTBSYNC(x)                      (((uint32_t)(((uint32_t)(x)) << TPM_CONF_GTBSYNC_SHIFT)) & TPM_CONF_GTBSYNC_MASK)

#define TPM_CONF_GTBEEN_MASK                     (0x200U)
#define TPM_CONF_GTBEEN_SHIFT                    (9U)
/*! GTBEEN - Global time base enable
 *  0b0..All channels use the internally generated TPM counter as their timebase
 *  0b1..All channels use an externally generated global timebase as their timebase
 */
#define TPM_CONF_GTBEEN(x)                       (((uint32_t)(((uint32_t)(x)) << TPM_CONF_GTBEEN_SHIFT)) & TPM_CONF_GTBEEN_MASK)

#define TPM_CONF_CSOT_MASK                       (0x10000U)
#define TPM_CONF_CSOT_SHIFT                      (16U)
/*! CSOT - Counter Start on Trigger
 *  0b0..TPM counter starts to increment immediately, once it is enabled.
 *  0b1..TPM counter only starts to increment when it a rising edge on the selected input trigger is detected,
 *       after it has been enabled or after it has stopped due to overflow.
 */
#define TPM_CONF_CSOT(x)                         (((uint32_t)(((uint32_t)(x)) << TPM_CONF_CSOT_SHIFT)) & TPM_CONF_CSOT_MASK)

#define TPM_CONF_CSOO_MASK                       (0x20000U)
#define TPM_CONF_CSOO_SHIFT                      (17U)
/*! CSOO - Counter Stop On Overflow
 *  0b0..TPM counter continues incrementing or decrementing after overflow
 *  0b1..TPM counter stops incrementing or decrementing after overflow.
 */
#define TPM_CONF_CSOO(x)                         (((uint32_t)(((uint32_t)(x)) << TPM_CONF_CSOO_SHIFT)) & TPM_CONF_CSOO_MASK)

#define TPM_CONF_CROT_MASK                       (0x40000U)
#define TPM_CONF_CROT_SHIFT                      (18U)
/*! CROT - Counter Reload On Trigger
 *  0b0..Counter is not reloaded due to a rising edge on the selected input trigger
 *  0b1..Counter is reloaded when a rising edge is detected on the selected input trigger
 */
#define TPM_CONF_CROT(x)                         (((uint32_t)(((uint32_t)(x)) << TPM_CONF_CROT_SHIFT)) & TPM_CONF_CROT_MASK)

#define TPM_CONF_CPOT_MASK                       (0x80000U)
#define TPM_CONF_CPOT_SHIFT                      (19U)
/*! CPOT - Counter Pause On Trigger */
#define TPM_CONF_CPOT(x)                         (((uint32_t)(((uint32_t)(x)) << TPM_CONF_CPOT_SHIFT)) & TPM_CONF_CPOT_MASK)

#define TPM_CONF_TRGPOL_MASK                     (0x400000U)
#define TPM_CONF_TRGPOL_SHIFT                    (22U)
/*! TRGPOL - Trigger Polarity
 *  0b0..Trigger is active high.
 *  0b1..Trigger is active low.
 */
#define TPM_CONF_TRGPOL(x)                       (((uint32_t)(((uint32_t)(x)) << TPM_CONF_TRGPOL_SHIFT)) & TPM_CONF_TRGPOL_MASK)

#define TPM_CONF_TRGSRC_MASK                     (0x800000U)
#define TPM_CONF_TRGSRC_SHIFT                    (23U)
/*! TRGSRC - Trigger Source
 *  0b0..Trigger source selected by TRGSEL is external.
 *  0b1..Trigger source selected by TRGSEL is internal (channel pin input capture).
 */
#define TPM_CONF_TRGSRC(x)                       (((uint32_t)(((uint32_t)(x)) << TPM_CONF_TRGSRC_SHIFT)) & TPM_CONF_TRGSRC_MASK)

#define TPM_CONF_TRGSEL_MASK                     (0xF000000U)
#define TPM_CONF_TRGSEL_SHIFT                    (24U)
/*! TRGSEL - Trigger Select
 *  0b0001..Channel 0 pin input capture
 *  0b0010..Channel 1 pin input capture
 *  0b0011..Channel 0 or Channel 1 pin input capture
 *  0b0100..Channel 2 pin input capture
 *  0b0101..Channel 0 or Channel 2 pin input capture
 *  0b0110..Channel 1 or Channel 2 pin input capture
 *  0b0111..Channel 0 or Channel 1 or Channel 2 pin input capture
 *  0b1000..Channel 3 pin input capture
 *  0b1001..Channel 0 or Channel 3 pin input capture
 *  0b1010..Channel 1 or Channel 3 pin input capture
 *  0b1011..Channel 0 or Channel 1 or Channel 3 pin input capture
 *  0b1100..Channel 2 or Channel 3 pin input capture
 *  0b1101..Channel 0 or Channel 2 or Channel 3 pin input capture
 *  0b1110..Channel 1 or Channel 2 or Channel 3 pin input capture
 *  0b1111..Channel 0 or Channel 1 or Channel 2 or Channel 3 pin input capture
 */
#define TPM_CONF_TRGSEL(x)                       (((uint32_t)(((uint32_t)(x)) << TPM_CONF_TRGSEL_SHIFT)) & TPM_CONF_TRGSEL_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group TPM_Register_Masks */


/* TPM - Peripheral instance base addresses */
/** Peripheral TPM0 base address */
#define TPM0_BASE                                (0x40038000u)
/** Peripheral TPM0 base pointer */
#define TPM0                                     ((TPM_Type *)TPM0_BASE)
/** Peripheral TPM1 base address */
#define TPM1_BASE                                (0x40039000u)
/** Peripheral TPM1 base pointer */
#define TPM1                                     ((TPM_Type *)TPM1_BASE)
/** Peripheral TPM2 base address */
#define TPM2_BASE                                (0x4003A000u)
/** Peripheral TPM2 base pointer */
#define TPM2                                     ((TPM_Type *)TPM2_BASE)
/** Array initializer of TPM peripheral base addresses */
#define TPM_BASE_ADDRS                           { TPM0_BASE, TPM1_BASE, TPM2_BASE }
/** Array initializer of TPM peripheral base pointers */
#define TPM_BASE_PTRS                            { TPM0, TPM1, TPM2 }
/** Interrupt vectors for the TPM peripheral type */
#define TPM_IRQS                                 { TPM0_IRQn, TPM1_IRQn, TPM2_IRQn }

/*!
 * @}
 */ /* end of group TPM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- UART Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Peripheral_Access_Layer UART Peripheral Access Layer
 * @{
 */

/** UART - Register Layout Typedef */
typedef struct {
  __IO uint8_t BDH;                                /**< UART Baud Rate Registers: High, offset: 0x0 */
  __IO uint8_t BDL;                                /**< UART Baud Rate Registers: Low, offset: 0x1 */
  __IO uint8_t C1;                                 /**< UART Control Register 1, offset: 0x2 */
  __IO uint8_t C2;                                 /**< UART Control Register 2, offset: 0x3 */
  __I  uint8_t S1;                                 /**< UART Status Register 1, offset: 0x4 */
  __IO uint8_t S2;                                 /**< UART Status Register 2, offset: 0x5 */
  __IO uint8_t C3;                                 /**< UART Control Register 3, offset: 0x6 */
  __IO uint8_t D;                                  /**< UART Data Register, offset: 0x7 */
  __IO uint8_t MA1;                                /**< UART Match Address Registers 1, offset: 0x8 */
  __IO uint8_t MA2;                                /**< UART Match Address Registers 2, offset: 0x9 */
  __IO uint8_t C4;                                 /**< UART Control Register 4, offset: 0xA */
  __IO uint8_t C5;                                 /**< UART Control Register 5, offset: 0xB */
       uint8_t RESERVED_0[12];
  __IO uint8_t C7816;                              /**< UART 7816 Control Register, offset: 0x18 */
  __IO uint8_t IE7816;                             /**< UART 7816 Interrupt Enable Register, offset: 0x19 */
  __IO uint8_t IS7816;                             /**< UART 7816 Interrupt Status Register, offset: 0x1A */
  __IO uint8_t WP7816;                             /**< UART 7816 Wait Parameter Register, offset: 0x1B */
  __IO uint8_t WN7816;                             /**< UART 7816 Wait N Register, offset: 0x1C */
  __IO uint8_t WF7816;                             /**< UART 7816 Wait FD Register, offset: 0x1D */
  __IO uint8_t ET7816;                             /**< UART 7816 Error Threshold Register, offset: 0x1E */
  __IO uint8_t TL7816;                             /**< UART 7816 Transmit Length Register, offset: 0x1F */
       uint8_t RESERVED_1[26];
  __IO uint8_t AP7816A_T0;                         /**< UART 7816 ATR Duration Timer Register A, offset: 0x3A */
  __IO uint8_t AP7816B_T0;                         /**< UART 7816 ATR Duration Timer Register B, offset: 0x3B */
  union {                                          /* offset: 0x3C */
    struct {                                         /* offset: 0x3C */
      __IO uint8_t WP7816A_T0;                         /**< UART 7816 Wait Parameter Register A, offset: 0x3C */
      __IO uint8_t WP7816B_T0;                         /**< UART 7816 Wait Parameter Register B, offset: 0x3D */
    } TYPE0;
    struct {                                         /* offset: 0x3C */
      __IO uint8_t WP7816A_T1;                         /**< UART 7816 Wait Parameter Register A, offset: 0x3C */
      __IO uint8_t WP7816B_T1;                         /**< UART 7816 Wait Parameter Register B, offset: 0x3D */
    } TYPE1;
  };
  __IO uint8_t WGP7816_T1;                         /**< UART 7816 Wait and Guard Parameter Register, offset: 0x3E */
  __IO uint8_t WP7816C_T1;                         /**< UART 7816 Wait Parameter Register C, offset: 0x3F */
} UART_Type;

/* ----------------------------------------------------------------------------
   -- UART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Masks UART Register Masks
 * @{
 */

/*! @name BDH - UART Baud Rate Registers: High */
/*! @{ */

#define UART_BDH_SBR_MASK                        (0x1FU)
#define UART_BDH_SBR_SHIFT                       (0U)
/*! SBR - UART Baud Rate Bits */
#define UART_BDH_SBR(x)                          (((uint8_t)(((uint8_t)(x)) << UART_BDH_SBR_SHIFT)) & UART_BDH_SBR_MASK)

#define UART_BDH_RXEDGIE_MASK                    (0x40U)
#define UART_BDH_RXEDGIE_SHIFT                   (6U)
/*! RXEDGIE - RxD Input Active Edge Interrupt Enable
 *  0b0..Hardware interrupts from RXEDGIF disabled using polling.
 *  0b1..RXEDGIF interrupt request enabled.
 */
#define UART_BDH_RXEDGIE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_BDH_RXEDGIE_SHIFT)) & UART_BDH_RXEDGIE_MASK)
/*! @} */

/*! @name BDL - UART Baud Rate Registers: Low */
/*! @{ */

#define UART_BDL_SBR_MASK                        (0xFFU)
#define UART_BDL_SBR_SHIFT                       (0U)
/*! SBR - UART Baud Rate Bits */
#define UART_BDL_SBR(x)                          (((uint8_t)(((uint8_t)(x)) << UART_BDL_SBR_SHIFT)) & UART_BDL_SBR_MASK)
/*! @} */

/*! @name C1 - UART Control Register 1 */
/*! @{ */

#define UART_C1_PT_MASK                          (0x1U)
#define UART_C1_PT_SHIFT                         (0U)
/*! PT - Parity Type
 *  0b0..Even parity.
 *  0b1..Odd parity.
 */
#define UART_C1_PT(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C1_PT_SHIFT)) & UART_C1_PT_MASK)

#define UART_C1_PE_MASK                          (0x2U)
#define UART_C1_PE_SHIFT                         (1U)
/*! PE - Parity Enable
 *  0b0..Parity function disabled.
 *  0b1..Parity function enabled.
 */
#define UART_C1_PE(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C1_PE_SHIFT)) & UART_C1_PE_MASK)

#define UART_C1_ILT_MASK                         (0x4U)
#define UART_C1_ILT_SHIFT                        (2U)
/*! ILT - Idle Line Type Select
 *  0b0..Idle character bit count starts after start bit.
 *  0b1..Idle character bit count starts after stop bit.
 */
#define UART_C1_ILT(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C1_ILT_SHIFT)) & UART_C1_ILT_MASK)

#define UART_C1_WAKE_MASK                        (0x8U)
#define UART_C1_WAKE_SHIFT                       (3U)
/*! WAKE - Receiver Wakeup Method Select
 *  0b0..Idle line wakeup.
 *  0b1..Address mark wakeup.
 */
#define UART_C1_WAKE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C1_WAKE_SHIFT)) & UART_C1_WAKE_MASK)

#define UART_C1_M_MASK                           (0x10U)
#define UART_C1_M_SHIFT                          (4U)
/*! M - 9-bit or 8-bit Mode Select
 *  0b0..Normal-start + 8 data bits (MSB/LSB first as determined by MSBF) + stop.
 *  0b1..Use-start + 9 data bits (MSB/LSB first as determined by MSBF) + stop.
 */
#define UART_C1_M(x)                             (((uint8_t)(((uint8_t)(x)) << UART_C1_M_SHIFT)) & UART_C1_M_MASK)

#define UART_C1_RSRC_MASK                        (0x20U)
#define UART_C1_RSRC_SHIFT                       (5U)
/*! RSRC - Receiver Source Select
 *  0b0..Selects internal loop back mode. The receiver input is internally connected to transmitter output.
 *  0b1..Single wire UART mode where the receiver input is connected to the transmit pin input signal.
 */
#define UART_C1_RSRC(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C1_RSRC_SHIFT)) & UART_C1_RSRC_MASK)

#define UART_C1_LOOPS_MASK                       (0x80U)
#define UART_C1_LOOPS_SHIFT                      (7U)
/*! LOOPS - Loop Mode Select
 *  0b0..Normal operation.
 *  0b1..Loop mode where transmitter output is internally connected to receiver input. The receiver input is determined by RSRC.
 */
#define UART_C1_LOOPS(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C1_LOOPS_SHIFT)) & UART_C1_LOOPS_MASK)
/*! @} */

/*! @name C2 - UART Control Register 2 */
/*! @{ */

#define UART_C2_SBK_MASK                         (0x1U)
#define UART_C2_SBK_SHIFT                        (0U)
/*! SBK - Send Break
 *  0b0..Normal transmitter operation.
 *  0b1..Queue break characters to be sent.
 */
#define UART_C2_SBK(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C2_SBK_SHIFT)) & UART_C2_SBK_MASK)

#define UART_C2_RWU_MASK                         (0x2U)
#define UART_C2_RWU_SHIFT                        (1U)
/*! RWU - Receiver Wakeup Control
 *  0b0..Normal operation.
 *  0b1..RWU enables the wakeup function and inhibits further receiver interrupt requests. Normally, hardware
 *       wakes the receiver by automatically clearing RWU.
 */
#define UART_C2_RWU(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C2_RWU_SHIFT)) & UART_C2_RWU_MASK)

#define UART_C2_RE_MASK                          (0x4U)
#define UART_C2_RE_SHIFT                         (2U)
/*! RE - Receiver Enable
 *  0b0..Receiver off.
 *  0b1..Receiver on.
 */
#define UART_C2_RE(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C2_RE_SHIFT)) & UART_C2_RE_MASK)

#define UART_C2_TE_MASK                          (0x8U)
#define UART_C2_TE_SHIFT                         (3U)
/*! TE - Transmitter Enable
 *  0b0..Transmitter off.
 *  0b1..Transmitter on.
 */
#define UART_C2_TE(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C2_TE_SHIFT)) & UART_C2_TE_MASK)

#define UART_C2_ILIE_MASK                        (0x10U)
#define UART_C2_ILIE_SHIFT                       (4U)
/*! ILIE - Idle Line Interrupt Enable
 *  0b0..IDLE interrupt requests disabled.
 *  0b1..IDLE interrupt requests enabled.
 */
#define UART_C2_ILIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C2_ILIE_SHIFT)) & UART_C2_ILIE_MASK)

#define UART_C2_RIE_MASK                         (0x20U)
#define UART_C2_RIE_SHIFT                        (5U)
/*! RIE - Receiver Full Interrupt or DMA Transfer Enable
 *  0b0..RDRF interrupt and DMA transfer requests disabled.
 *  0b1..RDRF interrupt or DMA transfer requests enabled.
 */
#define UART_C2_RIE(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C2_RIE_SHIFT)) & UART_C2_RIE_MASK)

#define UART_C2_TCIE_MASK                        (0x40U)
#define UART_C2_TCIE_SHIFT                       (6U)
/*! TCIE - Transmission Complete Interrupt Enable
 *  0b0..TC interrupt requests disabled.
 *  0b1..TC interrupt requests enabled.
 */
#define UART_C2_TCIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C2_TCIE_SHIFT)) & UART_C2_TCIE_MASK)

#define UART_C2_TIE_MASK                         (0x80U)
#define UART_C2_TIE_SHIFT                        (7U)
/*! TIE - Transmitter Interrupt or DMA Transfer Enable.
 *  0b0..TDRE interrupt and DMA transfer requests disabled.
 *  0b1..TDRE interrupt or DMA transfer requests enabled.
 */
#define UART_C2_TIE(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C2_TIE_SHIFT)) & UART_C2_TIE_MASK)
/*! @} */

/*! @name S1 - UART Status Register 1 */
/*! @{ */

#define UART_S1_PF_MASK                          (0x1U)
#define UART_S1_PF_SHIFT                         (0U)
/*! PF - Parity Error Flag
 *  0b0..No parity error detected since the last time this flag was cleared. If the receive buffer has a depth
 *       greater than 1, then there may be data in the receive buffer what was received with a parity error.
 *  0b1..At least one dataword was received with a parity error since the last time this flag was cleared.
 */
#define UART_S1_PF(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_PF_SHIFT)) & UART_S1_PF_MASK)

#define UART_S1_FE_MASK                          (0x2U)
#define UART_S1_FE_SHIFT                         (1U)
/*! FE - Framing Error Flag
 *  0b0..No framing error detected.
 *  0b1..Framing error.
 */
#define UART_S1_FE(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_FE_SHIFT)) & UART_S1_FE_MASK)

#define UART_S1_NF_MASK                          (0x4U)
#define UART_S1_NF_SHIFT                         (2U)
/*! NF - Noise Flag
 *  0b0..No noise detected since the last time this flag was cleared. If the receive buffer has a depth greater
 *       than 1 then there may be data in the receiver buffer that was received with noise.
 *  0b1..At least one dataword was received with noise detected since the last time the flag was cleared.
 */
#define UART_S1_NF(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_NF_SHIFT)) & UART_S1_NF_MASK)

#define UART_S1_OR_MASK                          (0x8U)
#define UART_S1_OR_SHIFT                         (3U)
/*! OR - Receiver Overrun Flag
 *  0b0..No overrun has occurred since the last time the flag was cleared.
 *  0b1..Overrun has occurred or the overrun flag has not been cleared since the last overrun occured.
 */
#define UART_S1_OR(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_OR_SHIFT)) & UART_S1_OR_MASK)

#define UART_S1_IDLE_MASK                        (0x10U)
#define UART_S1_IDLE_SHIFT                       (4U)
/*! IDLE - Idle Line Flag
 *  0b0..Receiver input is either active now or has never become active since the IDLE flag was last cleared.
 *  0b1..Receiver input has become idle or the flag has not been cleared since it last asserted.
 */
#define UART_S1_IDLE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_S1_IDLE_SHIFT)) & UART_S1_IDLE_MASK)

#define UART_S1_RDRF_MASK                        (0x20U)
#define UART_S1_RDRF_SHIFT                       (5U)
/*! RDRF - Receive Data Register Full Flag
 *  0b0..The number of datawords in the receive buffer is less than the number indicated by RXWATER.
 *  0b1..The number of datawords in the receive buffer is equal to or greater than the number indicated by RXWATER
 *       at some point in time since this flag was last cleared.
 */
#define UART_S1_RDRF(x)                          (((uint8_t)(((uint8_t)(x)) << UART_S1_RDRF_SHIFT)) & UART_S1_RDRF_MASK)

#define UART_S1_TC_MASK                          (0x40U)
#define UART_S1_TC_SHIFT                         (6U)
/*! TC - Transmit Complete Flag
 *  0b0..Transmitter active (sending data, a preamble, or a break).
 *  0b1..Transmitter idle (transmission activity complete).
 */
#define UART_S1_TC(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_TC_SHIFT)) & UART_S1_TC_MASK)

#define UART_S1_TDRE_MASK                        (0x80U)
#define UART_S1_TDRE_SHIFT                       (7U)
/*! TDRE - Transmit Data Register Empty Flag
 *  0b0..The amount of data in the transmit buffer is greater than the value indicated by TWFIFO[TXWATER].
 *  0b1..The amount of data in the transmit buffer is less than or equal to the value indicated by TWFIFO[TXWATER]
 *       at some point in time since the flag has been cleared.
 */
#define UART_S1_TDRE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_S1_TDRE_SHIFT)) & UART_S1_TDRE_MASK)
/*! @} */

/*! @name S2 - UART Status Register 2 */
/*! @{ */

#define UART_S2_RAF_MASK                         (0x1U)
#define UART_S2_RAF_SHIFT                        (0U)
/*! RAF - Receiver Active Flag
 *  0b0..UART receiver idle/inactive waiting for a start bit.
 *  0b1..UART receiver active, RxD input not idle.
 */
#define UART_S2_RAF(x)                           (((uint8_t)(((uint8_t)(x)) << UART_S2_RAF_SHIFT)) & UART_S2_RAF_MASK)

#define UART_S2_BRK13_MASK                       (0x4U)
#define UART_S2_BRK13_SHIFT                      (2U)
/*! BRK13 - Break Transmit Character Length
 *  0b0..Break character is 10, 11, or 12 bits long.
 *  0b1..Break character is 13 or 14 bits long.
 */
#define UART_S2_BRK13(x)                         (((uint8_t)(((uint8_t)(x)) << UART_S2_BRK13_SHIFT)) & UART_S2_BRK13_MASK)

#define UART_S2_RWUID_MASK                       (0x8U)
#define UART_S2_RWUID_SHIFT                      (3U)
/*! RWUID - Receive Wakeup Idle Detect
 *  0b0..S1[IDLE] is not set upon detection of an idle character.
 *  0b1..S1[IDLE] is set upon detection of an idle character.
 */
#define UART_S2_RWUID(x)                         (((uint8_t)(((uint8_t)(x)) << UART_S2_RWUID_SHIFT)) & UART_S2_RWUID_MASK)

#define UART_S2_RXINV_MASK                       (0x10U)
#define UART_S2_RXINV_SHIFT                      (4U)
/*! RXINV - Receive Data Inversion
 *  0b0..Receive data is not inverted.
 *  0b1..Receive data is inverted.
 */
#define UART_S2_RXINV(x)                         (((uint8_t)(((uint8_t)(x)) << UART_S2_RXINV_SHIFT)) & UART_S2_RXINV_MASK)

#define UART_S2_MSBF_MASK                        (0x20U)
#define UART_S2_MSBF_SHIFT                       (5U)
/*! MSBF - Most Significant Bit First
 *  0b0..LSB (bit0) is the first bit that is transmitted following the start bit. Further, the first bit received
 *       after the start bit is identified as bit0.
 *  0b1..MSB (bit8, bit7 or bit6) is the first bit that is transmitted following the start bit, depending on the
 *       setting of C1[M] and C1[PE]. Further, the first bit received after the start bit is identified as bit8,
 *       bit7, or bit6, depending on the setting of C1[M] and C1[PE].
 */
#define UART_S2_MSBF(x)                          (((uint8_t)(((uint8_t)(x)) << UART_S2_MSBF_SHIFT)) & UART_S2_MSBF_MASK)

#define UART_S2_RXEDGIF_MASK                     (0x40U)
#define UART_S2_RXEDGIF_SHIFT                    (6U)
/*! RXEDGIF - RxD Pin Active Edge Interrupt Flag
 *  0b0..No active edge on the receive pin has occurred.
 *  0b1..An active edge on the receive pin has occurred.
 */
#define UART_S2_RXEDGIF(x)                       (((uint8_t)(((uint8_t)(x)) << UART_S2_RXEDGIF_SHIFT)) & UART_S2_RXEDGIF_MASK)
/*! @} */

/*! @name C3 - UART Control Register 3 */
/*! @{ */

#define UART_C3_PEIE_MASK                        (0x1U)
#define UART_C3_PEIE_SHIFT                       (0U)
/*! PEIE - Parity Error Interrupt Enable
 *  0b0..PF interrupt requests are disabled.
 *  0b1..PF interrupt requests are enabled.
 */
#define UART_C3_PEIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C3_PEIE_SHIFT)) & UART_C3_PEIE_MASK)

#define UART_C3_FEIE_MASK                        (0x2U)
#define UART_C3_FEIE_SHIFT                       (1U)
/*! FEIE - Framing Error Interrupt Enable
 *  0b0..FE interrupt requests are disabled.
 *  0b1..FE interrupt requests are enabled.
 */
#define UART_C3_FEIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C3_FEIE_SHIFT)) & UART_C3_FEIE_MASK)

#define UART_C3_NEIE_MASK                        (0x4U)
#define UART_C3_NEIE_SHIFT                       (2U)
/*! NEIE - Noise Error Interrupt Enable
 *  0b0..NF interrupt requests are disabled.
 *  0b1..NF interrupt requests are enabled.
 */
#define UART_C3_NEIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C3_NEIE_SHIFT)) & UART_C3_NEIE_MASK)

#define UART_C3_ORIE_MASK                        (0x8U)
#define UART_C3_ORIE_SHIFT                       (3U)
/*! ORIE - Overrun Error Interrupt Enable
 *  0b0..OR interrupts are disabled.
 *  0b1..OR interrupt requests are enabled.
 */
#define UART_C3_ORIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C3_ORIE_SHIFT)) & UART_C3_ORIE_MASK)

#define UART_C3_TXINV_MASK                       (0x10U)
#define UART_C3_TXINV_SHIFT                      (4U)
/*! TXINV - Transmit Data Inversion.
 *  0b0..Transmit data is not inverted.
 *  0b1..Transmit data is inverted.
 */
#define UART_C3_TXINV(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C3_TXINV_SHIFT)) & UART_C3_TXINV_MASK)

#define UART_C3_TXDIR_MASK                       (0x20U)
#define UART_C3_TXDIR_SHIFT                      (5U)
/*! TXDIR - Transmitter Pin Data Direction in Single-Wire mode
 *  0b0..TXD pin is an input in single wire mode.
 *  0b1..TXD pin is an output in single wire mode.
 */
#define UART_C3_TXDIR(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C3_TXDIR_SHIFT)) & UART_C3_TXDIR_MASK)

#define UART_C3_T8_MASK                          (0x40U)
#define UART_C3_T8_SHIFT                         (6U)
/*! T8 - Transmit Bit 8 */
#define UART_C3_T8(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C3_T8_SHIFT)) & UART_C3_T8_MASK)

#define UART_C3_R8_MASK                          (0x80U)
#define UART_C3_R8_SHIFT                         (7U)
/*! R8 - Received Bit 8 */
#define UART_C3_R8(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C3_R8_SHIFT)) & UART_C3_R8_MASK)
/*! @} */

/*! @name D - UART Data Register */
/*! @{ */

#define UART_D_RT_MASK                           (0xFFU)
#define UART_D_RT_SHIFT                          (0U)
#define UART_D_RT(x)                             (((uint8_t)(((uint8_t)(x)) << UART_D_RT_SHIFT)) & UART_D_RT_MASK)
/*! @} */

/*! @name MA1 - UART Match Address Registers 1 */
/*! @{ */

#define UART_MA1_MA_MASK                         (0xFFU)
#define UART_MA1_MA_SHIFT                        (0U)
/*! MA - Match Address */
#define UART_MA1_MA(x)                           (((uint8_t)(((uint8_t)(x)) << UART_MA1_MA_SHIFT)) & UART_MA1_MA_MASK)
/*! @} */

/*! @name MA2 - UART Match Address Registers 2 */
/*! @{ */

#define UART_MA2_MA_MASK                         (0xFFU)
#define UART_MA2_MA_SHIFT                        (0U)
/*! MA - Match Address */
#define UART_MA2_MA(x)                           (((uint8_t)(((uint8_t)(x)) << UART_MA2_MA_SHIFT)) & UART_MA2_MA_MASK)
/*! @} */

/*! @name C4 - UART Control Register 4 */
/*! @{ */

#define UART_C4_BRFA_MASK                        (0x1FU)
#define UART_C4_BRFA_SHIFT                       (0U)
/*! BRFA - Baud Rate Fine Adjust */
#define UART_C4_BRFA(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C4_BRFA_SHIFT)) & UART_C4_BRFA_MASK)

#define UART_C4_M10_MASK                         (0x20U)
#define UART_C4_M10_SHIFT                        (5U)
/*! M10 - 10-bit Mode select
 *  0b0..The parity bit is the ninth bit in the serial transmission.
 *  0b1..The parity bit is the tenth bit in the serial transmission.
 */
#define UART_C4_M10(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C4_M10_SHIFT)) & UART_C4_M10_MASK)

#define UART_C4_MAEN2_MASK                       (0x40U)
#define UART_C4_MAEN2_SHIFT                      (6U)
/*! MAEN2 - Match Address Mode Enable 2
 *  0b0..All data received is transferred to the data buffer if MAEN1 is cleared.
 *  0b1..All data received with the most significant bit cleared, is discarded. All data received with the most
 *       significant bit set, is compared with contents of MA2 register. If no match occurs, the data is discarded.
 *       If a match occurs, data is transferred to the data buffer. This field must be cleared when C7816[ISO7816E]
 *       is set/enabled.
 */
#define UART_C4_MAEN2(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C4_MAEN2_SHIFT)) & UART_C4_MAEN2_MASK)

#define UART_C4_MAEN1_MASK                       (0x80U)
#define UART_C4_MAEN1_SHIFT                      (7U)
/*! MAEN1 - Match Address Mode Enable 1
 *  0b0..All data received is transferred to the data buffer if MAEN2 is cleared.
 *  0b1..All data received with the most significant bit cleared, is discarded. All data received with the most
 *       significant bit set, is compared with contents of MA1 register. If no match occurs, the data is discarded.
 *       If match occurs, data is transferred to the data buffer. This field must be cleared when C7816[ISO7816E] is
 *       set/enabled.
 */
#define UART_C4_MAEN1(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C4_MAEN1_SHIFT)) & UART_C4_MAEN1_MASK)
/*! @} */

/*! @name C5 - UART Control Register 5 */
/*! @{ */

#define UART_C5_RDMAS_MASK                       (0x20U)
#define UART_C5_RDMAS_SHIFT                      (5U)
/*! RDMAS - Receiver Full DMA Select
 *  0b0..If C2[RIE] and S1[RDRF] are set, the RDFR interrupt request signal is asserted to request an interrupt service.
 *  0b1..If C2[RIE] and S1[RDRF] are set, the RDRF DMA request signal is asserted to request a DMA transfer.
 */
#define UART_C5_RDMAS(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C5_RDMAS_SHIFT)) & UART_C5_RDMAS_MASK)

#define UART_C5_TDMAS_MASK                       (0x80U)
#define UART_C5_TDMAS_SHIFT                      (7U)
/*! TDMAS - Transmitter DMA Select
 *  0b0..If C2[TIE] is set and the S1[TDRE] flag is set, the TDRE interrupt request signal is asserted to request interrupt service.
 *  0b1..If C2[TIE] is set and the S1[TDRE] flag is set, the TDRE DMA request signal is asserted to request a DMA transfer.
 */
#define UART_C5_TDMAS(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C5_TDMAS_SHIFT)) & UART_C5_TDMAS_MASK)
/*! @} */

/*! @name C7816 - UART 7816 Control Register */
/*! @{ */

#define UART_C7816_ISO_7816E_MASK                (0x1U)
#define UART_C7816_ISO_7816E_SHIFT               (0U)
/*! ISO_7816E - ISO-7816 Functionality Enabled
 *  0b0..ISO-7816 functionality is turned off/not enabled.
 *  0b1..ISO-7816 functionality is turned on/enabled.
 */
#define UART_C7816_ISO_7816E(x)                  (((uint8_t)(((uint8_t)(x)) << UART_C7816_ISO_7816E_SHIFT)) & UART_C7816_ISO_7816E_MASK)

#define UART_C7816_TTYPE_MASK                    (0x2U)
#define UART_C7816_TTYPE_SHIFT                   (1U)
/*! TTYPE - Transfer Type
 *  0b0..T = 0 per the ISO-7816 specification.
 *  0b1..T = 1 per the ISO-7816 specification.
 */
#define UART_C7816_TTYPE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_C7816_TTYPE_SHIFT)) & UART_C7816_TTYPE_MASK)

#define UART_C7816_INIT_MASK                     (0x4U)
#define UART_C7816_INIT_SHIFT                    (2U)
/*! INIT - Detect Initial Character
 *  0b0..Normal operating mode. Receiver does not seek to identify initial character.
 *  0b1..Receiver searches for initial character.
 */
#define UART_C7816_INIT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_C7816_INIT_SHIFT)) & UART_C7816_INIT_MASK)

#define UART_C7816_ANACK_MASK                    (0x8U)
#define UART_C7816_ANACK_SHIFT                   (3U)
/*! ANACK - Generate NACK on Error
 *  0b0..No NACK is automatically generated.
 *  0b1..A NACK is automatically generated if a parity error is detected or if an invalid initial character is detected.
 */
#define UART_C7816_ANACK(x)                      (((uint8_t)(((uint8_t)(x)) << UART_C7816_ANACK_SHIFT)) & UART_C7816_ANACK_MASK)

#define UART_C7816_ONACK_MASK                    (0x10U)
#define UART_C7816_ONACK_SHIFT                   (4U)
/*! ONACK - Generate NACK on Overflow
 *  0b0..The received data does not generate a NACK when the receipt of the data results in an overflow event.
 *  0b1..If the receiver buffer overflows, a NACK is automatically sent on a received character.
 */
#define UART_C7816_ONACK(x)                      (((uint8_t)(((uint8_t)(x)) << UART_C7816_ONACK_SHIFT)) & UART_C7816_ONACK_MASK)
/*! @} */

/*! @name IE7816 - UART 7816 Interrupt Enable Register */
/*! @{ */

#define UART_IE7816_RXTE_MASK                    (0x1U)
#define UART_IE7816_RXTE_SHIFT                   (0U)
/*! RXTE - Receive Threshold Exceeded Interrupt Enable
 *  0b0..The assertion of IS7816[RXT] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[RXT] results in the generation of an interrupt.
 */
#define UART_IE7816_RXTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_RXTE_SHIFT)) & UART_IE7816_RXTE_MASK)

#define UART_IE7816_TXTE_MASK                    (0x2U)
#define UART_IE7816_TXTE_SHIFT                   (1U)
/*! TXTE - Transmit Threshold Exceeded Interrupt Enable
 *  0b0..The assertion of IS7816[TXT] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[TXT] results in the generation of an interrupt.
 */
#define UART_IE7816_TXTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_TXTE_SHIFT)) & UART_IE7816_TXTE_MASK)

#define UART_IE7816_GTVE_MASK                    (0x4U)
#define UART_IE7816_GTVE_SHIFT                   (2U)
/*! GTVE - Guard Timer Violated Interrupt Enable
 *  0b0..The assertion of IS7816[GTV] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[GTV] results in the generation of an interrupt.
 */
#define UART_IE7816_GTVE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_GTVE_SHIFT)) & UART_IE7816_GTVE_MASK)

#define UART_IE7816_ADTE_MASK                    (0x8U)
#define UART_IE7816_ADTE_SHIFT                   (3U)
/*! ADTE - ATR Duration Timer Interrupt Enable
 *  0b0..The assertion of IS7816[ADT] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[ADT] results in the generation of an interrupt.
 */
#define UART_IE7816_ADTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_ADTE_SHIFT)) & UART_IE7816_ADTE_MASK)

#define UART_IE7816_INITDE_MASK                  (0x10U)
#define UART_IE7816_INITDE_SHIFT                 (4U)
/*! INITDE - Initial Character Detected Interrupt Enable
 *  0b0..The assertion of IS7816[INITD] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[INITD] results in the generation of an interrupt.
 */
#define UART_IE7816_INITDE(x)                    (((uint8_t)(((uint8_t)(x)) << UART_IE7816_INITDE_SHIFT)) & UART_IE7816_INITDE_MASK)

#define UART_IE7816_BWTE_MASK                    (0x20U)
#define UART_IE7816_BWTE_SHIFT                   (5U)
/*! BWTE - Block Wait Timer Interrupt Enable
 *  0b0..The assertion of IS7816[BWT] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[BWT] results in the generation of an interrupt.
 */
#define UART_IE7816_BWTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_BWTE_SHIFT)) & UART_IE7816_BWTE_MASK)

#define UART_IE7816_CWTE_MASK                    (0x40U)
#define UART_IE7816_CWTE_SHIFT                   (6U)
/*! CWTE - Character Wait Timer Interrupt Enable
 *  0b0..The assertion of IS7816[CWT] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[CWT] results in the generation of an interrupt.
 */
#define UART_IE7816_CWTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_CWTE_SHIFT)) & UART_IE7816_CWTE_MASK)

#define UART_IE7816_WTE_MASK                     (0x80U)
#define UART_IE7816_WTE_SHIFT                    (7U)
/*! WTE - Wait Timer Interrupt Enable
 *  0b0..The assertion of IS7816[WT] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[WT] results in the generation of an interrupt.
 */
#define UART_IE7816_WTE(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IE7816_WTE_SHIFT)) & UART_IE7816_WTE_MASK)
/*! @} */

/*! @name IS7816 - UART 7816 Interrupt Status Register */
/*! @{ */

#define UART_IS7816_RXT_MASK                     (0x1U)
#define UART_IS7816_RXT_SHIFT                    (0U)
/*! RXT - Receive Threshold Exceeded Interrupt
 *  0b0..The number of consecutive NACKS generated as a result of parity errors and buffer overruns is less than
 *       or equal to the value in ET7816[RXTHRESHOLD].
 *  0b1..The number of consecutive NACKS generated as a result of parity errors and buffer overruns is greater than the value in ET7816[RXTHRESHOLD].
 */
#define UART_IS7816_RXT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_RXT_SHIFT)) & UART_IS7816_RXT_MASK)

#define UART_IS7816_TXT_MASK                     (0x2U)
#define UART_IS7816_TXT_SHIFT                    (1U)
/*! TXT - Transmit Threshold Exceeded Interrupt
 *  0b0..The number of retries and corresponding NACKS does not exceed the value in ET7816[TXTHRESHOLD].
 *  0b1..The number of retries and corresponding NACKS exceeds the value in ET7816[TXTHRESHOLD].
 */
#define UART_IS7816_TXT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_TXT_SHIFT)) & UART_IS7816_TXT_MASK)

#define UART_IS7816_GTV_MASK                     (0x4U)
#define UART_IS7816_GTV_SHIFT                    (2U)
/*! GTV - Guard Timer Violated Interrupt
 *  0b0..A guard time (GT, CGT, or BGT) has not been violated.
 *  0b1..A guard time (GT, CGT, or BGT) has been violated.
 */
#define UART_IS7816_GTV(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_GTV_SHIFT)) & UART_IS7816_GTV_MASK)

#define UART_IS7816_ADT_MASK                     (0x8U)
#define UART_IS7816_ADT_SHIFT                    (3U)
/*! ADT - ATR Duration Time Interrupt
 *  0b0..ATR Duration time (ADT) has not been violated.
 *  0b1..ATR Duration time (ADT) has been violated.
 */
#define UART_IS7816_ADT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_ADT_SHIFT)) & UART_IS7816_ADT_MASK)

#define UART_IS7816_INITD_MASK                   (0x10U)
#define UART_IS7816_INITD_SHIFT                  (4U)
/*! INITD - Initial Character Detected Interrupt
 *  0b0..A valid initial character has not been received.
 *  0b1..A valid initial character has been received.
 */
#define UART_IS7816_INITD(x)                     (((uint8_t)(((uint8_t)(x)) << UART_IS7816_INITD_SHIFT)) & UART_IS7816_INITD_MASK)

#define UART_IS7816_BWT_MASK                     (0x20U)
#define UART_IS7816_BWT_SHIFT                    (5U)
/*! BWT - Block Wait Timer Interrupt
 *  0b0..Block wait time (BWT) has not been violated.
 *  0b1..Block wait time (BWT) has been violated.
 */
#define UART_IS7816_BWT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_BWT_SHIFT)) & UART_IS7816_BWT_MASK)

#define UART_IS7816_CWT_MASK                     (0x40U)
#define UART_IS7816_CWT_SHIFT                    (6U)
/*! CWT - Character Wait Timer Interrupt
 *  0b0..Character wait time (CWT) has not been violated.
 *  0b1..Character wait time (CWT) has been violated.
 */
#define UART_IS7816_CWT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_CWT_SHIFT)) & UART_IS7816_CWT_MASK)

#define UART_IS7816_WT_MASK                      (0x80U)
#define UART_IS7816_WT_SHIFT                     (7U)
/*! WT - Wait Timer Interrupt
 *  0b0..Wait time (WT) has not been violated.
 *  0b1..Wait time (WT) has been violated.
 */
#define UART_IS7816_WT(x)                        (((uint8_t)(((uint8_t)(x)) << UART_IS7816_WT_SHIFT)) & UART_IS7816_WT_MASK)
/*! @} */

/*! @name WP7816 - UART 7816 Wait Parameter Register */
/*! @{ */

#define UART_WP7816_WTX_MASK                     (0xFFU)
#define UART_WP7816_WTX_SHIFT                    (0U)
/*! WTX - Wait Time Multiplier (C7816[TTYPE] = 1) */
#define UART_WP7816_WTX(x)                       (((uint8_t)(((uint8_t)(x)) << UART_WP7816_WTX_SHIFT)) & UART_WP7816_WTX_MASK)
/*! @} */

/*! @name WN7816 - UART 7816 Wait N Register */
/*! @{ */

#define UART_WN7816_GTN_MASK                     (0xFFU)
#define UART_WN7816_GTN_SHIFT                    (0U)
/*! GTN - Guard Band N */
#define UART_WN7816_GTN(x)                       (((uint8_t)(((uint8_t)(x)) << UART_WN7816_GTN_SHIFT)) & UART_WN7816_GTN_MASK)
/*! @} */

/*! @name WF7816 - UART 7816 Wait FD Register */
/*! @{ */

#define UART_WF7816_GTFD_MASK                    (0xFFU)
#define UART_WF7816_GTFD_SHIFT                   (0U)
/*! GTFD - FD Multiplier */
#define UART_WF7816_GTFD(x)                      (((uint8_t)(((uint8_t)(x)) << UART_WF7816_GTFD_SHIFT)) & UART_WF7816_GTFD_MASK)
/*! @} */

/*! @name ET7816 - UART 7816 Error Threshold Register */
/*! @{ */

#define UART_ET7816_RXTHRESHOLD_MASK             (0xFU)
#define UART_ET7816_RXTHRESHOLD_SHIFT            (0U)
/*! RXTHRESHOLD - Receive NACK Threshold */
#define UART_ET7816_RXTHRESHOLD(x)               (((uint8_t)(((uint8_t)(x)) << UART_ET7816_RXTHRESHOLD_SHIFT)) & UART_ET7816_RXTHRESHOLD_MASK)

#define UART_ET7816_TXTHRESHOLD_MASK             (0xF0U)
#define UART_ET7816_TXTHRESHOLD_SHIFT            (4U)
/*! TXTHRESHOLD - Transmit NACK Threshold
 *  0b0000..TXT asserts on the first NACK that is received.
 *  0b0001..TXT asserts on the second NACK that is received.
 */
#define UART_ET7816_TXTHRESHOLD(x)               (((uint8_t)(((uint8_t)(x)) << UART_ET7816_TXTHRESHOLD_SHIFT)) & UART_ET7816_TXTHRESHOLD_MASK)
/*! @} */

/*! @name TL7816 - UART 7816 Transmit Length Register */
/*! @{ */

#define UART_TL7816_TLEN_MASK                    (0xFFU)
#define UART_TL7816_TLEN_SHIFT                   (0U)
/*! TLEN - Transmit Length */
#define UART_TL7816_TLEN(x)                      (((uint8_t)(((uint8_t)(x)) << UART_TL7816_TLEN_SHIFT)) & UART_TL7816_TLEN_MASK)
/*! @} */

/*! @name AP7816A_T0 - UART 7816 ATR Duration Timer Register A */
/*! @{ */

#define UART_AP7816A_T0_ADTI_H_MASK              (0xFFU)
#define UART_AP7816A_T0_ADTI_H_SHIFT             (0U)
/*! ADTI_H - ATR Duration Time Integer High (C7816[TTYPE] = 0) */
#define UART_AP7816A_T0_ADTI_H(x)                (((uint8_t)(((uint8_t)(x)) << UART_AP7816A_T0_ADTI_H_SHIFT)) & UART_AP7816A_T0_ADTI_H_MASK)
/*! @} */

/*! @name AP7816B_T0 - UART 7816 ATR Duration Timer Register B */
/*! @{ */

#define UART_AP7816B_T0_ADTI_L_MASK              (0xFFU)
#define UART_AP7816B_T0_ADTI_L_SHIFT             (0U)
/*! ADTI_L - ATR Duration Time Integer Low (C7816[TTYPE] = 0) */
#define UART_AP7816B_T0_ADTI_L(x)                (((uint8_t)(((uint8_t)(x)) << UART_AP7816B_T0_ADTI_L_SHIFT)) & UART_AP7816B_T0_ADTI_L_MASK)
/*! @} */

/*! @name WP7816A_T0 - UART 7816 Wait Parameter Register A */
/*! @{ */

#define UART_WP7816A_T0_WI_H_MASK                (0xFFU)
#define UART_WP7816A_T0_WI_H_SHIFT               (0U)
/*! WI_H - Wait Time Integer High (C7816[TTYPE] = 0) */
#define UART_WP7816A_T0_WI_H(x)                  (((uint8_t)(((uint8_t)(x)) << UART_WP7816A_T0_WI_H_SHIFT)) & UART_WP7816A_T0_WI_H_MASK)
/*! @} */

/*! @name WP7816B_T0 - UART 7816 Wait Parameter Register B */
/*! @{ */

#define UART_WP7816B_T0_WI_L_MASK                (0xFFU)
#define UART_WP7816B_T0_WI_L_SHIFT               (0U)
/*! WI_L - Wait Time Integer Low (C7816[TTYPE] = 0) */
#define UART_WP7816B_T0_WI_L(x)                  (((uint8_t)(((uint8_t)(x)) << UART_WP7816B_T0_WI_L_SHIFT)) & UART_WP7816B_T0_WI_L_MASK)
/*! @} */

/*! @name WP7816A_T1 - UART 7816 Wait Parameter Register A */
/*! @{ */

#define UART_WP7816A_T1_BWI_H_MASK               (0xFFU)
#define UART_WP7816A_T1_BWI_H_SHIFT              (0U)
/*! BWI_H - Block Wait Time Integer High (C7816[TTYPE] = 1) */
#define UART_WP7816A_T1_BWI_H(x)                 (((uint8_t)(((uint8_t)(x)) << UART_WP7816A_T1_BWI_H_SHIFT)) & UART_WP7816A_T1_BWI_H_MASK)
/*! @} */

/*! @name WP7816B_T1 - UART 7816 Wait Parameter Register B */
/*! @{ */

#define UART_WP7816B_T1_BWI_L_MASK               (0xFFU)
#define UART_WP7816B_T1_BWI_L_SHIFT              (0U)
/*! BWI_L - Block Wait Time Integer Low (C7816[TTYPE] = 1) */
#define UART_WP7816B_T1_BWI_L(x)                 (((uint8_t)(((uint8_t)(x)) << UART_WP7816B_T1_BWI_L_SHIFT)) & UART_WP7816B_T1_BWI_L_MASK)
/*! @} */

/*! @name WGP7816_T1 - UART 7816 Wait and Guard Parameter Register */
/*! @{ */

#define UART_WGP7816_T1_BGI_MASK                 (0xFU)
#define UART_WGP7816_T1_BGI_SHIFT                (0U)
/*! BGI - Block Guard Time Integer (C7816[TTYPE] = 1) */
#define UART_WGP7816_T1_BGI(x)                   (((uint8_t)(((uint8_t)(x)) << UART_WGP7816_T1_BGI_SHIFT)) & UART_WGP7816_T1_BGI_MASK)

#define UART_WGP7816_T1_CWI1_MASK                (0xF0U)
#define UART_WGP7816_T1_CWI1_SHIFT               (4U)
/*! CWI1 - Character Wait Time Integer 1 (C7816[TTYPE] = 1) */
#define UART_WGP7816_T1_CWI1(x)                  (((uint8_t)(((uint8_t)(x)) << UART_WGP7816_T1_CWI1_SHIFT)) & UART_WGP7816_T1_CWI1_MASK)
/*! @} */

/*! @name WP7816C_T1 - UART 7816 Wait Parameter Register C */
/*! @{ */

#define UART_WP7816C_T1_CWI2_MASK                (0x1FU)
#define UART_WP7816C_T1_CWI2_SHIFT               (0U)
/*! CWI2 - Character Wait Time Integer 2 (C7816[TTYPE] = 1) */
#define UART_WP7816C_T1_CWI2(x)                  (((uint8_t)(((uint8_t)(x)) << UART_WP7816C_T1_CWI2_SHIFT)) & UART_WP7816C_T1_CWI2_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group UART_Register_Masks */


/* UART - Peripheral instance base addresses */
/** Peripheral UART2 base address */
#define UART2_BASE                               (0x4006C000u)
/** Peripheral UART2 base pointer */
#define UART2                                    ((UART_Type *)UART2_BASE)
/** Array initializer of UART peripheral base addresses */
#define UART_BASE_ADDRS                          { 0u, 0u, UART2_BASE }
/** Array initializer of UART peripheral base pointers */
#define UART_BASE_PTRS                           { (UART_Type *)0u, (UART_Type *)0u, UART2 }
/** Interrupt vectors for the UART peripheral type */
#define UART_RX_TX_IRQS                          { NotAvail_IRQn, NotAvail_IRQn, UART2_FLEXIO_IRQn }
#define UART_ERR_IRQS                            { NotAvail_IRQn, NotAvail_IRQn, UART2_FLEXIO_IRQn }

/*!
 * @}
 */ /* end of group UART_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- USB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Peripheral_Access_Layer USB Peripheral Access Layer
 * @{
 */

/** USB - Register Layout Typedef */
typedef struct {
  __I  uint8_t PERID;                              /**< Peripheral ID register, offset: 0x0 */
       uint8_t RESERVED_0[3];
  __I  uint8_t IDCOMP;                             /**< Peripheral ID Complement register, offset: 0x4 */
       uint8_t RESERVED_1[3];
  __I  uint8_t REV;                                /**< Peripheral Revision register, offset: 0x8 */
       uint8_t RESERVED_2[3];
  __I  uint8_t ADDINFO;                            /**< Peripheral Additional Info register, offset: 0xC */
       uint8_t RESERVED_3[115];
  __IO uint8_t ISTAT;                              /**< Interrupt Status register, offset: 0x80 */
       uint8_t RESERVED_4[3];
  __IO uint8_t INTEN;                              /**< Interrupt Enable register, offset: 0x84 */
       uint8_t RESERVED_5[3];
  __IO uint8_t ERRSTAT;                            /**< Error Interrupt Status register, offset: 0x88 */
       uint8_t RESERVED_6[3];
  __IO uint8_t ERREN;                              /**< Error Interrupt Enable register, offset: 0x8C */
       uint8_t RESERVED_7[3];
  __I  uint8_t STAT;                               /**< Status register, offset: 0x90 */
       uint8_t RESERVED_8[3];
  __IO uint8_t CTL;                                /**< Control register, offset: 0x94 */
       uint8_t RESERVED_9[3];
  __IO uint8_t ADDR;                               /**< Address register, offset: 0x98 */
       uint8_t RESERVED_10[3];
  __IO uint8_t BDTPAGE1;                           /**< BDT Page register 1, offset: 0x9C */
       uint8_t RESERVED_11[3];
  __IO uint8_t FRMNUML;                            /**< Frame Number register Low, offset: 0xA0 */
       uint8_t RESERVED_12[3];
  __IO uint8_t FRMNUMH;                            /**< Frame Number register High, offset: 0xA4 */
       uint8_t RESERVED_13[11];
  __IO uint8_t BDTPAGE2;                           /**< BDT Page Register 2, offset: 0xB0 */
       uint8_t RESERVED_14[3];
  __IO uint8_t BDTPAGE3;                           /**< BDT Page Register 3, offset: 0xB4 */
       uint8_t RESERVED_15[11];
  struct {                                         /* offset: 0xC0, array step: 0x4 */
    __IO uint8_t ENDPT;                              /**< Endpoint Control register, array offset: 0xC0, array step: 0x4 */
         uint8_t RESERVED_0[3];
  } ENDPOINT[16];
  __IO uint8_t USBCTRL;                            /**< USB Control register, offset: 0x100 */
       uint8_t RESERVED_16[3];
  __I  uint8_t OBSERVE;                            /**< USB OTG Observe register, offset: 0x104 */
       uint8_t RESERVED_17[3];
  __IO uint8_t CONTROL;                            /**< USB OTG Control register, offset: 0x108 */
       uint8_t RESERVED_18[3];
  __IO uint8_t USBTRC0;                            /**< USB Transceiver Control register 0, offset: 0x10C */
       uint8_t RESERVED_19[7];
  __IO uint8_t USBFRMADJUST;                       /**< Frame Adjust Register, offset: 0x114 */
       uint8_t RESERVED_20[43];
  __IO uint8_t CLK_RECOVER_CTRL;                   /**< USB Clock recovery control, offset: 0x140 */
       uint8_t RESERVED_21[3];
  __IO uint8_t CLK_RECOVER_IRC_EN;                 /**< IRC48M oscillator enable register, offset: 0x144 */
       uint8_t RESERVED_22[15];
  __IO uint8_t CLK_RECOVER_INT_EN;                 /**< Clock recovery combined interrupt enable, offset: 0x154 */
       uint8_t RESERVED_23[7];
  __IO uint8_t CLK_RECOVER_INT_STATUS;             /**< Clock recovery separated interrupt status, offset: 0x15C */
} USB_Type;

/* ----------------------------------------------------------------------------
   -- USB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Register_Masks USB Register Masks
 * @{
 */

/*! @name PERID - Peripheral ID register */
/*! @{ */

#define USB_PERID_ID_MASK                        (0x3FU)
#define USB_PERID_ID_SHIFT                       (0U)
/*! ID - Peripheral Identification */
#define USB_PERID_ID(x)                          (((uint8_t)(((uint8_t)(x)) << USB_PERID_ID_SHIFT)) & USB_PERID_ID_MASK)
/*! @} */

/*! @name IDCOMP - Peripheral ID Complement register */
/*! @{ */

#define USB_IDCOMP_NID_MASK                      (0x3FU)
#define USB_IDCOMP_NID_SHIFT                     (0U)
#define USB_IDCOMP_NID(x)                        (((uint8_t)(((uint8_t)(x)) << USB_IDCOMP_NID_SHIFT)) & USB_IDCOMP_NID_MASK)
/*! @} */

/*! @name REV - Peripheral Revision register */
/*! @{ */

#define USB_REV_REV_MASK                         (0xFFU)
#define USB_REV_REV_SHIFT                        (0U)
/*! REV - Revision */
#define USB_REV_REV(x)                           (((uint8_t)(((uint8_t)(x)) << USB_REV_REV_SHIFT)) & USB_REV_REV_MASK)
/*! @} */

/*! @name ADDINFO - Peripheral Additional Info register */
/*! @{ */

#define USB_ADDINFO_IEHOST_MASK                  (0x1U)
#define USB_ADDINFO_IEHOST_SHIFT                 (0U)
#define USB_ADDINFO_IEHOST(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ADDINFO_IEHOST_SHIFT)) & USB_ADDINFO_IEHOST_MASK)
/*! @} */

/*! @name ISTAT - Interrupt Status register */
/*! @{ */

#define USB_ISTAT_USBRST_MASK                    (0x1U)
#define USB_ISTAT_USBRST_SHIFT                   (0U)
#define USB_ISTAT_USBRST(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_USBRST_SHIFT)) & USB_ISTAT_USBRST_MASK)

#define USB_ISTAT_ERROR_MASK                     (0x2U)
#define USB_ISTAT_ERROR_SHIFT                    (1U)
#define USB_ISTAT_ERROR(x)                       (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_ERROR_SHIFT)) & USB_ISTAT_ERROR_MASK)

#define USB_ISTAT_SOFTOK_MASK                    (0x4U)
#define USB_ISTAT_SOFTOK_SHIFT                   (2U)
#define USB_ISTAT_SOFTOK(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_SOFTOK_SHIFT)) & USB_ISTAT_SOFTOK_MASK)

#define USB_ISTAT_TOKDNE_MASK                    (0x8U)
#define USB_ISTAT_TOKDNE_SHIFT                   (3U)
#define USB_ISTAT_TOKDNE(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_TOKDNE_SHIFT)) & USB_ISTAT_TOKDNE_MASK)

#define USB_ISTAT_SLEEP_MASK                     (0x10U)
#define USB_ISTAT_SLEEP_SHIFT                    (4U)
#define USB_ISTAT_SLEEP(x)                       (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_SLEEP_SHIFT)) & USB_ISTAT_SLEEP_MASK)

#define USB_ISTAT_RESUME_MASK                    (0x20U)
#define USB_ISTAT_RESUME_SHIFT                   (5U)
#define USB_ISTAT_RESUME(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_RESUME_SHIFT)) & USB_ISTAT_RESUME_MASK)

#define USB_ISTAT_STALL_MASK                     (0x80U)
#define USB_ISTAT_STALL_SHIFT                    (7U)
/*! STALL - Stall Interrupt */
#define USB_ISTAT_STALL(x)                       (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_STALL_SHIFT)) & USB_ISTAT_STALL_MASK)
/*! @} */

/*! @name INTEN - Interrupt Enable register */
/*! @{ */

#define USB_INTEN_USBRSTEN_MASK                  (0x1U)
#define USB_INTEN_USBRSTEN_SHIFT                 (0U)
/*! USBRSTEN - USBRST Interrupt Enable
 *  0b0..Disables the USBRST interrupt.
 *  0b1..Enables the USBRST interrupt.
 */
#define USB_INTEN_USBRSTEN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_INTEN_USBRSTEN_SHIFT)) & USB_INTEN_USBRSTEN_MASK)

#define USB_INTEN_ERROREN_MASK                   (0x2U)
#define USB_INTEN_ERROREN_SHIFT                  (1U)
/*! ERROREN - ERROR Interrupt Enable
 *  0b0..Disables the ERROR interrupt.
 *  0b1..Enables the ERROR interrupt.
 */
#define USB_INTEN_ERROREN(x)                     (((uint8_t)(((uint8_t)(x)) << USB_INTEN_ERROREN_SHIFT)) & USB_INTEN_ERROREN_MASK)

#define USB_INTEN_SOFTOKEN_MASK                  (0x4U)
#define USB_INTEN_SOFTOKEN_SHIFT                 (2U)
/*! SOFTOKEN - SOFTOK Interrupt Enable
 *  0b0..Disbles the SOFTOK interrupt.
 *  0b1..Enables the SOFTOK interrupt.
 */
#define USB_INTEN_SOFTOKEN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_INTEN_SOFTOKEN_SHIFT)) & USB_INTEN_SOFTOKEN_MASK)

#define USB_INTEN_TOKDNEEN_MASK                  (0x8U)
#define USB_INTEN_TOKDNEEN_SHIFT                 (3U)
/*! TOKDNEEN - TOKDNE Interrupt Enable
 *  0b0..Disables the TOKDNE interrupt.
 *  0b1..Enables the TOKDNE interrupt.
 */
#define USB_INTEN_TOKDNEEN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_INTEN_TOKDNEEN_SHIFT)) & USB_INTEN_TOKDNEEN_MASK)

#define USB_INTEN_SLEEPEN_MASK                   (0x10U)
#define USB_INTEN_SLEEPEN_SHIFT                  (4U)
/*! SLEEPEN - SLEEP Interrupt Enable
 *  0b0..Disables the SLEEP interrupt.
 *  0b1..Enables the SLEEP interrupt.
 */
#define USB_INTEN_SLEEPEN(x)                     (((uint8_t)(((uint8_t)(x)) << USB_INTEN_SLEEPEN_SHIFT)) & USB_INTEN_SLEEPEN_MASK)

#define USB_INTEN_RESUMEEN_MASK                  (0x20U)
#define USB_INTEN_RESUMEEN_SHIFT                 (5U)
/*! RESUMEEN - RESUME Interrupt Enable
 *  0b0..Disables the RESUME interrupt.
 *  0b1..Enables the RESUME interrupt.
 */
#define USB_INTEN_RESUMEEN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_INTEN_RESUMEEN_SHIFT)) & USB_INTEN_RESUMEEN_MASK)

#define USB_INTEN_STALLEN_MASK                   (0x80U)
#define USB_INTEN_STALLEN_SHIFT                  (7U)
/*! STALLEN - STALL Interrupt Enable
 *  0b0..Diasbles the STALL interrupt.
 *  0b1..Enables the STALL interrupt.
 */
#define USB_INTEN_STALLEN(x)                     (((uint8_t)(((uint8_t)(x)) << USB_INTEN_STALLEN_SHIFT)) & USB_INTEN_STALLEN_MASK)
/*! @} */

/*! @name ERRSTAT - Error Interrupt Status register */
/*! @{ */

#define USB_ERRSTAT_PIDERR_MASK                  (0x1U)
#define USB_ERRSTAT_PIDERR_SHIFT                 (0U)
#define USB_ERRSTAT_PIDERR(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_PIDERR_SHIFT)) & USB_ERRSTAT_PIDERR_MASK)

#define USB_ERRSTAT_CRC5_MASK                    (0x2U)
#define USB_ERRSTAT_CRC5_SHIFT                   (1U)
#define USB_ERRSTAT_CRC5(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_CRC5_SHIFT)) & USB_ERRSTAT_CRC5_MASK)

#define USB_ERRSTAT_CRC16_MASK                   (0x4U)
#define USB_ERRSTAT_CRC16_SHIFT                  (2U)
#define USB_ERRSTAT_CRC16(x)                     (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_CRC16_SHIFT)) & USB_ERRSTAT_CRC16_MASK)

#define USB_ERRSTAT_DFN8_MASK                    (0x8U)
#define USB_ERRSTAT_DFN8_SHIFT                   (3U)
#define USB_ERRSTAT_DFN8(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_DFN8_SHIFT)) & USB_ERRSTAT_DFN8_MASK)

#define USB_ERRSTAT_BTOERR_MASK                  (0x10U)
#define USB_ERRSTAT_BTOERR_SHIFT                 (4U)
#define USB_ERRSTAT_BTOERR(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_BTOERR_SHIFT)) & USB_ERRSTAT_BTOERR_MASK)

#define USB_ERRSTAT_DMAERR_MASK                  (0x20U)
#define USB_ERRSTAT_DMAERR_SHIFT                 (5U)
#define USB_ERRSTAT_DMAERR(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_DMAERR_SHIFT)) & USB_ERRSTAT_DMAERR_MASK)

#define USB_ERRSTAT_BTSERR_MASK                  (0x80U)
#define USB_ERRSTAT_BTSERR_SHIFT                 (7U)
#define USB_ERRSTAT_BTSERR(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_BTSERR_SHIFT)) & USB_ERRSTAT_BTSERR_MASK)
/*! @} */

/*! @name ERREN - Error Interrupt Enable register */
/*! @{ */

#define USB_ERREN_PIDERREN_MASK                  (0x1U)
#define USB_ERREN_PIDERREN_SHIFT                 (0U)
/*! PIDERREN - PIDERR Interrupt Enable
 *  0b0..Disables the PIDERR interrupt.
 *  0b1..Enters the PIDERR interrupt.
 */
#define USB_ERREN_PIDERREN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERREN_PIDERREN_SHIFT)) & USB_ERREN_PIDERREN_MASK)

#define USB_ERREN_CRC5EOFEN_MASK                 (0x2U)
#define USB_ERREN_CRC5EOFEN_SHIFT                (1U)
/*! CRC5EOFEN - CRC5/EOF Interrupt Enable
 *  0b0..Disables the CRC5/EOF interrupt.
 *  0b1..Enables the CRC5/EOF interrupt.
 */
#define USB_ERREN_CRC5EOFEN(x)                   (((uint8_t)(((uint8_t)(x)) << USB_ERREN_CRC5EOFEN_SHIFT)) & USB_ERREN_CRC5EOFEN_MASK)

#define USB_ERREN_CRC16EN_MASK                   (0x4U)
#define USB_ERREN_CRC16EN_SHIFT                  (2U)
/*! CRC16EN - CRC16 Interrupt Enable
 *  0b0..Disables the CRC16 interrupt.
 *  0b1..Enables the CRC16 interrupt.
 */
#define USB_ERREN_CRC16EN(x)                     (((uint8_t)(((uint8_t)(x)) << USB_ERREN_CRC16EN_SHIFT)) & USB_ERREN_CRC16EN_MASK)

#define USB_ERREN_DFN8EN_MASK                    (0x8U)
#define USB_ERREN_DFN8EN_SHIFT                   (3U)
/*! DFN8EN - DFN8 Interrupt Enable
 *  0b0..Disables the DFN8 interrupt.
 *  0b1..Enables the DFN8 interrupt.
 */
#define USB_ERREN_DFN8EN(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ERREN_DFN8EN_SHIFT)) & USB_ERREN_DFN8EN_MASK)

#define USB_ERREN_BTOERREN_MASK                  (0x10U)
#define USB_ERREN_BTOERREN_SHIFT                 (4U)
/*! BTOERREN - BTOERR Interrupt Enable
 *  0b0..Disables the BTOERR interrupt.
 *  0b1..Enables the BTOERR interrupt.
 */
#define USB_ERREN_BTOERREN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERREN_BTOERREN_SHIFT)) & USB_ERREN_BTOERREN_MASK)

#define USB_ERREN_DMAERREN_MASK                  (0x20U)
#define USB_ERREN_DMAERREN_SHIFT                 (5U)
/*! DMAERREN - DMAERR Interrupt Enable
 *  0b0..Disables the DMAERR interrupt.
 *  0b1..Enables the DMAERR interrupt.
 */
#define USB_ERREN_DMAERREN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERREN_DMAERREN_SHIFT)) & USB_ERREN_DMAERREN_MASK)

#define USB_ERREN_BTSERREN_MASK                  (0x80U)
#define USB_ERREN_BTSERREN_SHIFT                 (7U)
/*! BTSERREN - BTSERR Interrupt Enable
 *  0b0..Disables the BTSERR interrupt.
 *  0b1..Enables the BTSERR interrupt.
 */
#define USB_ERREN_BTSERREN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERREN_BTSERREN_SHIFT)) & USB_ERREN_BTSERREN_MASK)
/*! @} */

/*! @name STAT - Status register */
/*! @{ */

#define USB_STAT_ODD_MASK                        (0x4U)
#define USB_STAT_ODD_SHIFT                       (2U)
#define USB_STAT_ODD(x)                          (((uint8_t)(((uint8_t)(x)) << USB_STAT_ODD_SHIFT)) & USB_STAT_ODD_MASK)

#define USB_STAT_TX_MASK                         (0x8U)
#define USB_STAT_TX_SHIFT                        (3U)
/*! TX - Transmit Indicator
 *  0b0..The most recent transaction was a receive operation.
 *  0b1..The most recent transaction was a transmit operation.
 */
#define USB_STAT_TX(x)                           (((uint8_t)(((uint8_t)(x)) << USB_STAT_TX_SHIFT)) & USB_STAT_TX_MASK)

#define USB_STAT_ENDP_MASK                       (0xF0U)
#define USB_STAT_ENDP_SHIFT                      (4U)
#define USB_STAT_ENDP(x)                         (((uint8_t)(((uint8_t)(x)) << USB_STAT_ENDP_SHIFT)) & USB_STAT_ENDP_MASK)
/*! @} */

/*! @name CTL - Control register */
/*! @{ */

#define USB_CTL_USBENSOFEN_MASK                  (0x1U)
#define USB_CTL_USBENSOFEN_SHIFT                 (0U)
/*! USBENSOFEN - USB Enable
 *  0b0..Disables the USB Module.
 *  0b1..Enables the USB Module.
 */
#define USB_CTL_USBENSOFEN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_CTL_USBENSOFEN_SHIFT)) & USB_CTL_USBENSOFEN_MASK)

#define USB_CTL_ODDRST_MASK                      (0x2U)
#define USB_CTL_ODDRST_SHIFT                     (1U)
#define USB_CTL_ODDRST(x)                        (((uint8_t)(((uint8_t)(x)) << USB_CTL_ODDRST_SHIFT)) & USB_CTL_ODDRST_MASK)

#define USB_CTL_RESUME_MASK                      (0x4U)
#define USB_CTL_RESUME_SHIFT                     (2U)
#define USB_CTL_RESUME(x)                        (((uint8_t)(((uint8_t)(x)) << USB_CTL_RESUME_SHIFT)) & USB_CTL_RESUME_MASK)

#define USB_CTL_TXSUSPENDTOKENBUSY_MASK          (0x20U)
#define USB_CTL_TXSUSPENDTOKENBUSY_SHIFT         (5U)
#define USB_CTL_TXSUSPENDTOKENBUSY(x)            (((uint8_t)(((uint8_t)(x)) << USB_CTL_TXSUSPENDTOKENBUSY_SHIFT)) & USB_CTL_TXSUSPENDTOKENBUSY_MASK)

#define USB_CTL_SE0_MASK                         (0x40U)
#define USB_CTL_SE0_SHIFT                        (6U)
/*! SE0 - Live USB Single Ended Zero signal */
#define USB_CTL_SE0(x)                           (((uint8_t)(((uint8_t)(x)) << USB_CTL_SE0_SHIFT)) & USB_CTL_SE0_MASK)

#define USB_CTL_JSTATE_MASK                      (0x80U)
#define USB_CTL_JSTATE_SHIFT                     (7U)
/*! JSTATE - Live USB differential receiver JSTATE signal */
#define USB_CTL_JSTATE(x)                        (((uint8_t)(((uint8_t)(x)) << USB_CTL_JSTATE_SHIFT)) & USB_CTL_JSTATE_MASK)
/*! @} */

/*! @name ADDR - Address register */
/*! @{ */

#define USB_ADDR_ADDR_MASK                       (0x7FU)
#define USB_ADDR_ADDR_SHIFT                      (0U)
/*! ADDR - USB Address */
#define USB_ADDR_ADDR(x)                         (((uint8_t)(((uint8_t)(x)) << USB_ADDR_ADDR_SHIFT)) & USB_ADDR_ADDR_MASK)
/*! @} */

/*! @name BDTPAGE1 - BDT Page register 1 */
/*! @{ */

#define USB_BDTPAGE1_BDTBA_MASK                  (0xFEU)
#define USB_BDTPAGE1_BDTBA_SHIFT                 (1U)
#define USB_BDTPAGE1_BDTBA(x)                    (((uint8_t)(((uint8_t)(x)) << USB_BDTPAGE1_BDTBA_SHIFT)) & USB_BDTPAGE1_BDTBA_MASK)
/*! @} */

/*! @name FRMNUML - Frame Number register Low */
/*! @{ */

#define USB_FRMNUML_FRM_MASK                     (0xFFU)
#define USB_FRMNUML_FRM_SHIFT                    (0U)
#define USB_FRMNUML_FRM(x)                       (((uint8_t)(((uint8_t)(x)) << USB_FRMNUML_FRM_SHIFT)) & USB_FRMNUML_FRM_MASK)
/*! @} */

/*! @name FRMNUMH - Frame Number register High */
/*! @{ */

#define USB_FRMNUMH_FRM_MASK                     (0x7U)
#define USB_FRMNUMH_FRM_SHIFT                    (0U)
#define USB_FRMNUMH_FRM(x)                       (((uint8_t)(((uint8_t)(x)) << USB_FRMNUMH_FRM_SHIFT)) & USB_FRMNUMH_FRM_MASK)
/*! @} */

/*! @name BDTPAGE2 - BDT Page Register 2 */
/*! @{ */

#define USB_BDTPAGE2_BDTBA_MASK                  (0xFFU)
#define USB_BDTPAGE2_BDTBA_SHIFT                 (0U)
#define USB_BDTPAGE2_BDTBA(x)                    (((uint8_t)(((uint8_t)(x)) << USB_BDTPAGE2_BDTBA_SHIFT)) & USB_BDTPAGE2_BDTBA_MASK)
/*! @} */

/*! @name BDTPAGE3 - BDT Page Register 3 */
/*! @{ */

#define USB_BDTPAGE3_BDTBA_MASK                  (0xFFU)
#define USB_BDTPAGE3_BDTBA_SHIFT                 (0U)
#define USB_BDTPAGE3_BDTBA(x)                    (((uint8_t)(((uint8_t)(x)) << USB_BDTPAGE3_BDTBA_SHIFT)) & USB_BDTPAGE3_BDTBA_MASK)
/*! @} */

/*! @name ENDPT - Endpoint Control register */
/*! @{ */

#define USB_ENDPT_EPHSHK_MASK                    (0x1U)
#define USB_ENDPT_EPHSHK_SHIFT                   (0U)
#define USB_ENDPT_EPHSHK(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPHSHK_SHIFT)) & USB_ENDPT_EPHSHK_MASK)

#define USB_ENDPT_EPSTALL_MASK                   (0x2U)
#define USB_ENDPT_EPSTALL_SHIFT                  (1U)
#define USB_ENDPT_EPSTALL(x)                     (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPSTALL_SHIFT)) & USB_ENDPT_EPSTALL_MASK)

#define USB_ENDPT_EPTXEN_MASK                    (0x4U)
#define USB_ENDPT_EPTXEN_SHIFT                   (2U)
#define USB_ENDPT_EPTXEN(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPTXEN_SHIFT)) & USB_ENDPT_EPTXEN_MASK)

#define USB_ENDPT_EPRXEN_MASK                    (0x8U)
#define USB_ENDPT_EPRXEN_SHIFT                   (3U)
#define USB_ENDPT_EPRXEN(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPRXEN_SHIFT)) & USB_ENDPT_EPRXEN_MASK)

#define USB_ENDPT_EPCTLDIS_MASK                  (0x10U)
#define USB_ENDPT_EPCTLDIS_SHIFT                 (4U)
#define USB_ENDPT_EPCTLDIS(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPCTLDIS_SHIFT)) & USB_ENDPT_EPCTLDIS_MASK)
/*! @} */

/* The count of USB_ENDPT */
#define USB_ENDPT_COUNT                          (16U)

/*! @name USBCTRL - USB Control register */
/*! @{ */

#define USB_USBCTRL_PDE_MASK                     (0x40U)
#define USB_USBCTRL_PDE_SHIFT                    (6U)
/*! PDE
 *  0b0..Weak pulldowns are disabled on D+ and D-.
 *  0b1..Weak pulldowns are enabled on D+ and D-.
 */
#define USB_USBCTRL_PDE(x)                       (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_PDE_SHIFT)) & USB_USBCTRL_PDE_MASK)

#define USB_USBCTRL_SUSP_MASK                    (0x80U)
#define USB_USBCTRL_SUSP_SHIFT                   (7U)
/*! SUSP
 *  0b0..USB transceiver is not in suspend state.
 *  0b1..USB transceiver is in suspend state.
 */
#define USB_USBCTRL_SUSP(x)                      (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_SUSP_SHIFT)) & USB_USBCTRL_SUSP_MASK)
/*! @} */

/*! @name OBSERVE - USB OTG Observe register */
/*! @{ */

#define USB_OBSERVE_DMPD_MASK                    (0x10U)
#define USB_OBSERVE_DMPD_SHIFT                   (4U)
/*! DMPD
 *  0b0..D- pulldown disabled.
 *  0b1..D- pulldown enabled.
 */
#define USB_OBSERVE_DMPD(x)                      (((uint8_t)(((uint8_t)(x)) << USB_OBSERVE_DMPD_SHIFT)) & USB_OBSERVE_DMPD_MASK)

#define USB_OBSERVE_DPPD_MASK                    (0x40U)
#define USB_OBSERVE_DPPD_SHIFT                   (6U)
/*! DPPD
 *  0b0..D+ pulldown disabled.
 *  0b1..D+ pulldown enabled.
 */
#define USB_OBSERVE_DPPD(x)                      (((uint8_t)(((uint8_t)(x)) << USB_OBSERVE_DPPD_SHIFT)) & USB_OBSERVE_DPPD_MASK)

#define USB_OBSERVE_DPPU_MASK                    (0x80U)
#define USB_OBSERVE_DPPU_SHIFT                   (7U)
/*! DPPU
 *  0b0..D+ pullup disabled.
 *  0b1..D+ pullup enabled.
 */
#define USB_OBSERVE_DPPU(x)                      (((uint8_t)(((uint8_t)(x)) << USB_OBSERVE_DPPU_SHIFT)) & USB_OBSERVE_DPPU_MASK)
/*! @} */

/*! @name CONTROL - USB OTG Control register */
/*! @{ */

#define USB_CONTROL_DPPULLUPNONOTG_MASK          (0x10U)
#define USB_CONTROL_DPPULLUPNONOTG_SHIFT         (4U)
/*! DPPULLUPNONOTG
 *  0b0..DP Pullup in non-OTG device mode is not enabled.
 *  0b1..DP Pullup in non-OTG device mode is enabled.
 */
#define USB_CONTROL_DPPULLUPNONOTG(x)            (((uint8_t)(((uint8_t)(x)) << USB_CONTROL_DPPULLUPNONOTG_SHIFT)) & USB_CONTROL_DPPULLUPNONOTG_MASK)
/*! @} */

/*! @name USBTRC0 - USB Transceiver Control register 0 */
/*! @{ */

#define USB_USBTRC0_USB_RESUME_INT_MASK          (0x1U)
#define USB_USBTRC0_USB_RESUME_INT_SHIFT         (0U)
/*! USB_RESUME_INT - USB Asynchronous Interrupt
 *  0b0..No interrupt was generated.
 *  0b1..Interrupt was generated because of the USB asynchronous interrupt.
 */
#define USB_USBTRC0_USB_RESUME_INT(x)            (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USB_RESUME_INT_SHIFT)) & USB_USBTRC0_USB_RESUME_INT_MASK)

#define USB_USBTRC0_SYNC_DET_MASK                (0x2U)
#define USB_USBTRC0_SYNC_DET_SHIFT               (1U)
/*! SYNC_DET - Synchronous USB Interrupt Detect
 *  0b0..Synchronous interrupt has not been detected.
 *  0b1..Synchronous interrupt has been detected.
 */
#define USB_USBTRC0_SYNC_DET(x)                  (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_SYNC_DET_SHIFT)) & USB_USBTRC0_SYNC_DET_MASK)

#define USB_USBTRC0_USB_CLK_RECOVERY_INT_MASK    (0x4U)
#define USB_USBTRC0_USB_CLK_RECOVERY_INT_SHIFT   (2U)
/*! USB_CLK_RECOVERY_INT - Combined USB Clock Recovery interrupt status */
#define USB_USBTRC0_USB_CLK_RECOVERY_INT(x)      (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USB_CLK_RECOVERY_INT_SHIFT)) & USB_USBTRC0_USB_CLK_RECOVERY_INT_MASK)

#define USB_USBTRC0_USBRESMEN_MASK               (0x20U)
#define USB_USBTRC0_USBRESMEN_SHIFT              (5U)
/*! USBRESMEN - Asynchronous Resume Interrupt Enable
 *  0b0..USB asynchronous wakeup from suspend mode disabled.
 *  0b1..USB asynchronous wakeup from suspend mode enabled. The asynchronous resume interrupt differs from the
 *       synchronous resume interrupt in that it asynchronously detects K-state using the unfiltered state of the D+
 *       and D- pins. This interrupt should only be enabled when the Transceiver is suspended.
 */
#define USB_USBTRC0_USBRESMEN(x)                 (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USBRESMEN_SHIFT)) & USB_USBTRC0_USBRESMEN_MASK)

#define USB_USBTRC0_USBRESET_MASK                (0x80U)
#define USB_USBTRC0_USBRESET_SHIFT               (7U)
/*! USBRESET - USB Reset
 *  0b0..Normal USB module operation.
 *  0b1..Returns the USB module to its reset state.
 */
#define USB_USBTRC0_USBRESET(x)                  (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USBRESET_SHIFT)) & USB_USBTRC0_USBRESET_MASK)
/*! @} */

/*! @name USBFRMADJUST - Frame Adjust Register */
/*! @{ */

#define USB_USBFRMADJUST_ADJ_MASK                (0xFFU)
#define USB_USBFRMADJUST_ADJ_SHIFT               (0U)
/*! ADJ - Frame Adjustment */
#define USB_USBFRMADJUST_ADJ(x)                  (((uint8_t)(((uint8_t)(x)) << USB_USBFRMADJUST_ADJ_SHIFT)) & USB_USBFRMADJUST_ADJ_MASK)
/*! @} */

/*! @name CLK_RECOVER_CTRL - USB Clock recovery control */
/*! @{ */

#define USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_MASK (0x20U)
#define USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_SHIFT (5U)
/*! RESTART_IFRTRIM_EN - Restart from IFR trim value
 *  0b0..Trim fine adjustment always works based on the previous updated trim fine value (default)
 *  0b1..Trim fine restarts from the IFR trim value whenever bus_reset/bus_resume is detected or module enable is desasserted
 */
#define USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_SHIFT)) & USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_MASK)

#define USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_MASK (0x40U)
#define USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_SHIFT (6U)
/*! RESET_RESUME_ROUGH_EN - Reset/resume to rough phase enable
 *  0b0..Always works in tracking phase after the first time rough to track transition (default)
 *  0b1..Go back to rough stage whenever bus reset or bus resume occurs
 */
#define USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_SHIFT)) & USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_MASK)

#define USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK (0x80U)
#define USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_SHIFT (7U)
/*! CLOCK_RECOVER_EN - Crystal-less USB enable
 *  0b0..Disable clock recovery block (default)
 *  0b1..Enable clock recovery block
 */
#define USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_SHIFT)) & USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK)
/*! @} */

/*! @name CLK_RECOVER_IRC_EN - IRC48M oscillator enable register */
/*! @{ */

#define USB_CLK_RECOVER_IRC_EN_IRC_EN_MASK       (0x2U)
#define USB_CLK_RECOVER_IRC_EN_IRC_EN_SHIFT      (1U)
/*! IRC_EN - IRC48M enable
 *  0b0..Disable the IRC48M module (default)
 *  0b1..Enable the IRC48M module
 */
#define USB_CLK_RECOVER_IRC_EN_IRC_EN(x)         (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_IRC_EN_IRC_EN_SHIFT)) & USB_CLK_RECOVER_IRC_EN_IRC_EN_MASK)
/*! @} */

/*! @name CLK_RECOVER_INT_EN - Clock recovery combined interrupt enable */
/*! @{ */

#define USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_MASK (0x10U)
#define USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_SHIFT (4U)
/*! OVF_ERROR_EN
 *  0b0..The interrupt will be masked
 *  0b1..The interrupt will be enabled (default)
 */
#define USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN(x)   (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_SHIFT)) & USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_MASK)
/*! @} */

/*! @name CLK_RECOVER_INT_STATUS - Clock recovery separated interrupt status */
/*! @{ */

#define USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_MASK (0x10U)
#define USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_SHIFT (4U)
/*! OVF_ERROR
 *  0b0..No interrupt is reported
 *  0b1..Unmasked interrupt has been generated
 */
#define USB_CLK_RECOVER_INT_STATUS_OVF_ERROR(x)  (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_SHIFT)) & USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group USB_Register_Masks */


/* USB - Peripheral instance base addresses */
/** Peripheral USB0 base address */
#define USB0_BASE                                (0x40072000u)
/** Peripheral USB0 base pointer */
#define USB0                                     ((USB_Type *)USB0_BASE)
/** Array initializer of USB peripheral base addresses */
#define USB_BASE_ADDRS                           { USB0_BASE }
/** Array initializer of USB peripheral base pointers */
#define USB_BASE_PTRS                            { USB0 }
/** Interrupt vectors for the USB peripheral type */
#define USB_IRQS                                 { USB0_IRQn }

/*!
 * @}
 */ /* end of group USB_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- VREF Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Peripheral_Access_Layer VREF Peripheral Access Layer
 * @{
 */

/** VREF - Register Layout Typedef */
typedef struct {
  __IO uint8_t TRM;                                /**< VREF Trim Register, offset: 0x0 */
  __IO uint8_t SC;                                 /**< VREF Status and Control Register, offset: 0x1 */
} VREF_Type;

/* ----------------------------------------------------------------------------
   -- VREF Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Register_Masks VREF Register Masks
 * @{
 */

/*! @name TRM - VREF Trim Register */
/*! @{ */

#define VREF_TRM_TRIM_MASK                       (0x3FU)
#define VREF_TRM_TRIM_SHIFT                      (0U)
/*! TRIM - Trim bits
 *  0b000000..Min
 *  0b111111..Max
 */
#define VREF_TRM_TRIM(x)                         (((uint8_t)(((uint8_t)(x)) << VREF_TRM_TRIM_SHIFT)) & VREF_TRM_TRIM_MASK)

#define VREF_TRM_CHOPEN_MASK                     (0x40U)
#define VREF_TRM_CHOPEN_SHIFT                    (6U)
/*! CHOPEN - Chop oscillator enable. When set, internal chopping operation is enabled and the
 *    internal analog offset will be minimized.
 *  0b0..Chop oscillator is disabled.
 *  0b1..Chop oscillator is enabled.
 */
#define VREF_TRM_CHOPEN(x)                       (((uint8_t)(((uint8_t)(x)) << VREF_TRM_CHOPEN_SHIFT)) & VREF_TRM_CHOPEN_MASK)
/*! @} */

/*! @name SC - VREF Status and Control Register */
/*! @{ */

#define VREF_SC_MODE_LV_MASK                     (0x3U)
#define VREF_SC_MODE_LV_SHIFT                    (0U)
/*! MODE_LV - Buffer Mode selection
 *  0b00..Bandgap on only, for stabilization and startup
 *  0b01..High power buffer mode enabled
 *  0b10..Low-power buffer mode enabled
 *  0b11..Reserved
 */
#define VREF_SC_MODE_LV(x)                       (((uint8_t)(((uint8_t)(x)) << VREF_SC_MODE_LV_SHIFT)) & VREF_SC_MODE_LV_MASK)

#define VREF_SC_VREFST_MASK                      (0x4U)
#define VREF_SC_VREFST_SHIFT                     (2U)
/*! VREFST - Internal Voltage Reference stable
 *  0b0..The module is disabled or not stable.
 *  0b1..The module is stable.
 */
#define VREF_SC_VREFST(x)                        (((uint8_t)(((uint8_t)(x)) << VREF_SC_VREFST_SHIFT)) & VREF_SC_VREFST_MASK)

#define VREF_SC_ICOMPEN_MASK                     (0x20U)
#define VREF_SC_ICOMPEN_SHIFT                    (5U)
/*! ICOMPEN - Second order curvature compensation enable
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define VREF_SC_ICOMPEN(x)                       (((uint8_t)(((uint8_t)(x)) << VREF_SC_ICOMPEN_SHIFT)) & VREF_SC_ICOMPEN_MASK)

#define VREF_SC_REGEN_MASK                       (0x40U)
#define VREF_SC_REGEN_SHIFT                      (6U)
/*! REGEN - Regulator enable
 *  0b0..Internal 1.75 V regulator is disabled.
 *  0b1..Internal 1.75 V regulator is enabled.
 */
#define VREF_SC_REGEN(x)                         (((uint8_t)(((uint8_t)(x)) << VREF_SC_REGEN_SHIFT)) & VREF_SC_REGEN_MASK)

#define VREF_SC_VREFEN_MASK                      (0x80U)
#define VREF_SC_VREFEN_SHIFT                     (7U)
/*! VREFEN - Internal Voltage Reference enable
 *  0b0..The module is disabled.
 *  0b1..The module is enabled.
 */
#define VREF_SC_VREFEN(x)                        (((uint8_t)(((uint8_t)(x)) << VREF_SC_VREFEN_SHIFT)) & VREF_SC_VREFEN_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group VREF_Register_Masks */


/* VREF - Peripheral instance base addresses */
/** Peripheral VREF base address */
#define VREF_BASE                                (0x40074000u)
/** Peripheral VREF base pointer */
#define VREF                                     ((VREF_Type *)VREF_BASE)
/** Array initializer of VREF peripheral base addresses */
#define VREF_BASE_ADDRS                          { VREF_BASE }
/** Array initializer of VREF peripheral base pointers */
#define VREF_BASE_PTRS                           { VREF }

/*!
 * @}
 */ /* end of group VREF_Peripheral_Access_Layer */


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

#define I2C_S1_RXAK_MASK                       I2C_S_RXAK_MASK
#define I2C_S1_RXAK_SHIFT                      I2C_S_RXAK_SHIFT
#define I2C_S1_IICIF_MASK                      I2C_S_IICIF_MASK
#define I2C_S1_IICIF_SHIFT                     I2C_S_IICIF_SHIFTFT
#define I2C_S1_SRW_MASK                        I2C_S_SRW_MASK
#define I2C_S1_SRW_SHIFT                       I2C_S_SRW_SHIFT
#define I2C_S1_RAM_MASK                        I2C_S_RAM_MASK
#define I2C_S1_RAM_SHIFT                       I2C_S_RAM_SHIFT
#define I2C_S1_ARBL_MASK                       I2C_S_ARBL_MASK
#define I2C_S1_ARBL_SHIFT                      I2C_S_ARBL_SHIFT
#define I2C_S1_BUSY_MASK                       I2C_S_BUSY_MASK
#define I2C_S1_BUSY_SHIFT                      I2C_S_BUSY_SHIFT
#define I2C_S1_IAAS_MASK                       I2C_S_IAAS_MASK
#define I2C_S1_IAAS_SHIFT                      I2C_S_IAAS_SHIFT
#define I2C_S1_TCF_MASK                        I2C_S_TCF_MASK
#define I2C_S1_TCF_SHIFT                       I2C_S_TCF_SHIFT
#define I2C_S1_REG(base)                       I2C_S_REG(base)
#define I2C0_S1                                I2C0_S
#define I2C1_S1                                I2C1_S
#define PTA_BASE                               GPIOA_BASE
#define PTB_BASE                               GPIOB_BASE
#define PTC_BASE                               GPIOC_BASE
#define PTD_BASE                               GPIOD_BASE
#define PTE_BASE                               GPIOE_BASE
#define PTA                                    GPIOA
#define PTB                                    GPIOB
#define PTC                                    GPIOC
#define PTD                                    GPIOD
#define PTE                                    GPIOE
#define UART0_FLEXIO_IRQn                      UART2_FLEXIO_IRQn
#define UART0_FLEXIO_IRQHandler                UART2_FLEXIO_IRQHandler
#define SIM_SOPT5_UART0ODE_MASK                SIM_SOPT5_UART2ODE_MASK
#define SIM_SOPT5_UART0ODE_SHIFT               SIM_SOPT5_UART2ODE_SHIFT
#define SIM_SCGC4_UART0_MASK                   SIM_SCGC4_UART2_MASK
#define SIM_SCGC4_UART0_SHIFT                  SIM_SCGC4_UART2_SHIFT
#define UART0_BASE                             UART2_BASE
#define UART0_BDH                              UART2_BDH
#define UART0_BDL                              UART2_BDL
#define UART0_C1                               UART2_C1
#define UART0_C2                               UART2_C2
#define UART0_S1                               UART2_S1
#define UART0_S2                               UART2_S2
#define UART0_C3                               UART2_C3
#define UART0_D                                UART2_D
#define UART0_MA1                              UART2_MA1
#define UART0_MA2                              UART2_MA2
#define UART0_C4                               UART2_C4
#define UART0_C5                               UART2_C5
#define UART0_ED                               UART2_ED
#define UART0_MODEM                            UART2_MODEM
#define UART0_IR                               UART2_IR
#define UART0_PFIFO                            UART2_PFIFO
#define UART0_CFIFO                            UART2_CFIFO
#define UART0_SFIFO                            UART2_SFIFO
#define UART0_TWFIFO                           UART2_TWFIFO
#define UART0_TCFIFO                           UART2_TCFIFO
#define UART0_RWFIFO                           UART2_RWFIFO
#define UART0_RCFIFO                           UART2_RCFIFO
#define UART0_C7816                            UART2_C7816
#define UART0_IE7816                           UART2_IE7816
#define UART0_IS7816                           UART2_IS7816
#define UART0_WP7816                           UART2_WP7816
#define UART0_WN7816                           UART2_WN7816
#define UART0_WF7816                           UART2_WF7816
#define UART0_ET7816                           UART2_ET7816
#define UART0_TL7816                           UART2_TL7816
#define UART0_AP7816A_T0                       UART2_AP7816A_T0
#define UART0_AP7816B_T0                       UART2_AP7816B_T0
#define UART0_WP7816A_T0                       UART2_WP7816A_T0
#define UART0_WP7816A_T1                       UART2_WP7816A_T1
#define UART0_WP7816B_T0                       UART2_WP7816B_T0
#define UART0_WP7816B_T1                       UART2_WP7816B_T1
#define UART0_WGP7816_T1                       UART2_WGP7816_T1
#define UART0_WP7816C_T1                       UART2_WP7816C_T1
#define I2S0_MDR                               This_symb_has_been_deprecated
#define I2S_MDR_DIVIDE_MASK                    This_symb_has_been_deprecated
#define I2S_MDR_DIVIDE_SHIFT                   This_symb_has_been_deprecated
#define I2S_MDR_DIVIDE(x)                      This_symb_has_been_deprecated
#define I2S_MDR_FRACT_MASK                     This_symb_has_been_deprecated
#define I2S_MDR_FRACT_SHIFT                    This_symb_has_been_deprecated
#define I2S_MDR_FRACT(x)                       This_symb_has_been_deprecated
#define I2S_MDR_REG(base)                      This_symb_has_been_deprecated
#define CTL0                                   OTGCTL
#define USB0_CTL0                              USB0_OTGCTL
#define USB_CTL0_REG(base)                     USB_OTGCTL_REG(base)
#define USB_CTL0_DPHIGH_MASK                   USB_OTGCTL_DPHIGH_MASK
#define USB_CTL0_DPHIGH_SHIFT                  USB_OTGCTL_DPHIGH_SHIFT
#define CTL1                                   CTL
#define USB0_CTL1                              USB0_CTL
#define USB_CTL1_REG(base)                     USB_CTL_REG(base)
#define USB_CTL1_USBEN_MASK                    USB_CTL_USBEN_MASK
#define USB_CTL1_USBEN_SHIFT                   USB_CTL_USBEN_SHIFT
#define USB_CTL1_ODDRST_MASK                   USB_CTL_ODDRST_MASK
#define USB_CTL1_ODDRST_SHIFT                  USB_CTL_ODDRST_SHIFT
#define USB_CTL1_TXSUSPENDTOKENBUSY_MASK       USB_CTL_TXSUSPENDTOKENBUSY_MASK
#define USB_CTL1_TXSUSPENDTOKENBUSY_SHIFT      USB_CTL_TXSUSPENDTOKENBUSY_SHIFT
#define USB_CTL1_SE0_MASK                      USB_CTL_SE0_MASK
#define USB_CTL1_SE0_SHIFT                     USB_CTL_SE0_SHIFT
#define USB_CTL1_JSTATE_MASK                   USB_CTL_JSTATE_MASK
#define USB_CTL1_JSTATE_SHIFT                  USB_CTL_JSTATE_SHIFT
#define USB_CTL_USBEN_MASK                     USB_CTL_USBENSOFEN_MASK
#define USB_CTL_USBEN_SHIFT                    USB_CTL_USBENSOFEN_SHIFT

/*!
 * @}
 */ /* end of group SDK_Compatibility_Symbols */


#endif  /* MCXC444_H_ */

