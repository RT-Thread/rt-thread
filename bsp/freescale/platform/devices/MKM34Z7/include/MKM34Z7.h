/*
** ###################################################################
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          GNU C Compiler - CodeSourcery Sourcery G++
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    KM34P144M75SF0RM, Rev.1, Jan 2015
**     Version:             rev. 1.2, 2015-03-06
**     Build:               b150513
**
**     Abstract:
**         CMSIS Peripheral Access Layer for MKM34Z7
**
**     Copyright (c) 1997 - 2015 Freescale Semiconductor, Inc.
**     All rights reserved.
**
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
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2014-10-17)
**         Initial version.
**     - rev. 1.1 (2015-01-27)
**         Update according to reference manual rev. 1, RC.
**     - rev. 1.2 (2015-03-06)
**         Update according to reference manual rev. 1.
**
** ###################################################################
*/

/*!
 * @file MKM34Z7.h
 * @version 1.2
 * @date 2015-03-06
 * @brief CMSIS Peripheral Access Layer for MKM34Z7
 *
 * CMSIS Peripheral Access Layer for MKM34Z7
 */


/* ----------------------------------------------------------------------------
   -- MCU activation
   ---------------------------------------------------------------------------- */

/* Prevention from multiple including the same memory map */
#if !defined(MKM34Z7_H_)  /* Check if memory map has not been already included */
#define MKM34Z7_H_
#define MCU_MKM34Z7

/* Check if another memory map has not been also included */
#if (defined(MCU_ACTIVE))
  #error MKM34Z7 memory map: There is already included another memory map. Only one memory map can be included.
#endif /* (defined(MCU_ACTIVE)) */
#define MCU_ACTIVE

#include <stdint.h>

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0100u
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0002u


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
  SPI0_SPI1_IRQn               = 4,                /**< SPI0/SPI1 ORed interrupt */
  PDB0_IRQn                    = 5,                /**< PDB0 ORed interrupt */
  PMC_IRQn                     = 6,                /**< Low-voltage detect, low-voltage warning */
  TMR0_IRQn                    = 7,                /**< Quad Timer Channel 0 */
  TMR1_IRQn                    = 8,                /**< Quad Timer Channel 1 */
  TMR2_IRQn                    = 9,                /**< Quad Timer Channel 2 */
  TMR3_IRQn                    = 10,               /**< Quad Timer Channel 3 */
  PIT0_PIT1_IRQn               = 11,               /**< PIT0/PIT1 ORed interrupt */
  LLWU_IRQn                    = 12,               /**< Low Leakage Wakeup */
  FTFA_IRQn                    = 13,               /**< Command complete and read collision */
  CMP0_CMP1_CMP2_IRQn          = 14,               /**< CMP0/CMP1/CMP2 ORed interrupt */
  LCD_IRQn                     = 15,               /**< LCD interrupt */
  ADC0_IRQn                    = 16,               /**< ADC0 interrupt */
  PTx_IRQn                     = 17,               /**< Single interrupt vector for GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH,GPIOI,GPIOJ,GPIOK,GPIOL,GPIOM */
  RNGA_IRQn                    = 18,               /**< RNGA interrupt */
  UART0_UART1_UART2_UART3_IRQn = 19,               /**< UART0/UART1/UART2/UART3 ORed interrupt */
  MMAU_IRQn                    = 20,               /**< Memory Mapped Arithmetic Unit interrupt */
  AFE_CH0_IRQn                 = 21,               /**< AFE Channel 0 */
  AFE_CH1_IRQn                 = 22,               /**< AFE Channel 1 */
  AFE_CH2_IRQn                 = 23,               /**< AFE Channel 2 */
  AFE_CH3_IRQn                 = 24,               /**< AFE Channel 3 */
  RTC_IRQn                     = 25,               /**< IRTC interrupt */
  I2C0_I2C1_IRQn               = 26,               /**< I2C0/I2C1 ORed interrupt */
  LPUART0_IRQn                 = 27,               /**< LPUART0 status and error interrupt */
  MCG_IRQn                     = 28,               /**< MCG interrupt */
  WDOG_EWM_IRQn                = 29,               /**< WDOG/EWM ORed interrupt */
  LPTMR0_IRQn                  = 30,               /**< LPTMR0 interrupt */
  XBAR_IRQn                    = 31                /**< XBAR interrupt */
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
#define __VTOR_PRESENT                 1         /**< Defines if an MPU is present or not */
#define __NVIC_PRIO_BITS               2         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig         0         /**< Vendor specific implementation of SysTickConfig is defined */

#include "core_cm0plus.h"              /* Core Peripheral Access Layer */
#include "system_MKM34Z7.h"            /* Device specific configuration file */

/*!
 * @}
 */ /* end of group Cortex_Core_Configuration */


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
  __IO uint32_t SC1[4];                            /**< ADC Status and Control Registers 1, array offset: 0x0, array step: 0x4 */
  __IO uint32_t CFG1;                              /**< ADC Configuration Register 1, offset: 0x10 */
  __IO uint32_t CFG2;                              /**< ADC Configuration Register 2, offset: 0x14 */
  __I  uint32_t R[4];                              /**< ADC Data Result Register, array offset: 0x18, array step: 0x4 */
  __IO uint32_t CV1;                               /**< Compare Value Registers, offset: 0x28 */
  __IO uint32_t CV2;                               /**< Compare Value Registers, offset: 0x2C */
  __IO uint32_t SC2;                               /**< Status and Control Register 2, offset: 0x30 */
  __IO uint32_t SC3;                               /**< Status and Control Register 3, offset: 0x34 */
  __IO uint32_t OFS;                               /**< ADC Offset Correction Register, offset: 0x38 */
  __IO uint32_t PG;                                /**< ADC Plus-Side Gain Register, offset: 0x3C */
       uint8_t RESERVED_0[4];
  __IO uint32_t CLPD;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x44 */
  __IO uint32_t CLPS;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x48 */
  __IO uint32_t CLP4;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x4C */
  __IO uint32_t CLP3;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x50 */
  __IO uint32_t CLP2;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x54 */
  __IO uint32_t CLP1;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x58 */
  __IO uint32_t CLP0;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x5C */
} ADC_Type, *ADC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register accessors */
#define ADC_SC1_REG(base,index)                  ((base)->SC1[index])
#define ADC_SC1_COUNT                            4
#define ADC_CFG1_REG(base)                       ((base)->CFG1)
#define ADC_CFG2_REG(base)                       ((base)->CFG2)
#define ADC_R_REG(base,index)                    ((base)->R[index])
#define ADC_R_COUNT                              4
#define ADC_CV1_REG(base)                        ((base)->CV1)
#define ADC_CV2_REG(base)                        ((base)->CV2)
#define ADC_SC2_REG(base)                        ((base)->SC2)
#define ADC_SC3_REG(base)                        ((base)->SC3)
#define ADC_OFS_REG(base)                        ((base)->OFS)
#define ADC_PG_REG(base)                         ((base)->PG)
#define ADC_CLPD_REG(base)                       ((base)->CLPD)
#define ADC_CLPS_REG(base)                       ((base)->CLPS)
#define ADC_CLP4_REG(base)                       ((base)->CLP4)
#define ADC_CLP3_REG(base)                       ((base)->CLP3)
#define ADC_CLP2_REG(base)                       ((base)->CLP2)
#define ADC_CLP1_REG(base)                       ((base)->CLP1)
#define ADC_CLP0_REG(base)                       ((base)->CLP0)

/*!
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */

/* SC1 Bit Fields */
#define ADC_SC1_ADCH_MASK                        0x1Fu
#define ADC_SC1_ADCH_SHIFT                       0
#define ADC_SC1_ADCH_WIDTH                       5
#define ADC_SC1_ADCH(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC1_ADCH_SHIFT))&ADC_SC1_ADCH_MASK)
#define ADC_SC1_AIEN_MASK                        0x40u
#define ADC_SC1_AIEN_SHIFT                       6
#define ADC_SC1_AIEN_WIDTH                       1
#define ADC_SC1_AIEN(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC1_AIEN_SHIFT))&ADC_SC1_AIEN_MASK)
#define ADC_SC1_COCO_MASK                        0x80u
#define ADC_SC1_COCO_SHIFT                       7
#define ADC_SC1_COCO_WIDTH                       1
#define ADC_SC1_COCO(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC1_COCO_SHIFT))&ADC_SC1_COCO_MASK)
/* CFG1 Bit Fields */
#define ADC_CFG1_ADICLK_MASK                     0x3u
#define ADC_CFG1_ADICLK_SHIFT                    0
#define ADC_CFG1_ADICLK_WIDTH                    2
#define ADC_CFG1_ADICLK(x)                       (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_ADICLK_SHIFT))&ADC_CFG1_ADICLK_MASK)
#define ADC_CFG1_MODE_MASK                       0xCu
#define ADC_CFG1_MODE_SHIFT                      2
#define ADC_CFG1_MODE_WIDTH                      2
#define ADC_CFG1_MODE(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_MODE_SHIFT))&ADC_CFG1_MODE_MASK)
#define ADC_CFG1_ADLSMP_MASK                     0x10u
#define ADC_CFG1_ADLSMP_SHIFT                    4
#define ADC_CFG1_ADLSMP_WIDTH                    1
#define ADC_CFG1_ADLSMP(x)                       (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_ADLSMP_SHIFT))&ADC_CFG1_ADLSMP_MASK)
#define ADC_CFG1_ADIV_MASK                       0x60u
#define ADC_CFG1_ADIV_SHIFT                      5
#define ADC_CFG1_ADIV_WIDTH                      2
#define ADC_CFG1_ADIV(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_ADIV_SHIFT))&ADC_CFG1_ADIV_MASK)
#define ADC_CFG1_ADLPC_MASK                      0x80u
#define ADC_CFG1_ADLPC_SHIFT                     7
#define ADC_CFG1_ADLPC_WIDTH                     1
#define ADC_CFG1_ADLPC(x)                        (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_ADLPC_SHIFT))&ADC_CFG1_ADLPC_MASK)
/* CFG2 Bit Fields */
#define ADC_CFG2_ADLSTS_MASK                     0x3u
#define ADC_CFG2_ADLSTS_SHIFT                    0
#define ADC_CFG2_ADLSTS_WIDTH                    2
#define ADC_CFG2_ADLSTS(x)                       (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_ADLSTS_SHIFT))&ADC_CFG2_ADLSTS_MASK)
#define ADC_CFG2_ADHSC_MASK                      0x4u
#define ADC_CFG2_ADHSC_SHIFT                     2
#define ADC_CFG2_ADHSC_WIDTH                     1
#define ADC_CFG2_ADHSC(x)                        (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_ADHSC_SHIFT))&ADC_CFG2_ADHSC_MASK)
#define ADC_CFG2_ADACKEN_MASK                    0x8u
#define ADC_CFG2_ADACKEN_SHIFT                   3
#define ADC_CFG2_ADACKEN_WIDTH                   1
#define ADC_CFG2_ADACKEN(x)                      (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_ADACKEN_SHIFT))&ADC_CFG2_ADACKEN_MASK)
#define ADC_CFG2_MUXSEL_MASK                     0x10u
#define ADC_CFG2_MUXSEL_SHIFT                    4
#define ADC_CFG2_MUXSEL_WIDTH                    1
#define ADC_CFG2_MUXSEL(x)                       (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_MUXSEL_SHIFT))&ADC_CFG2_MUXSEL_MASK)
/* R Bit Fields */
#define ADC_R_D_MASK                             0xFFFFu
#define ADC_R_D_SHIFT                            0
#define ADC_R_D_WIDTH                            16
#define ADC_R_D(x)                               (((uint32_t)(((uint32_t)(x))<<ADC_R_D_SHIFT))&ADC_R_D_MASK)
/* CV1 Bit Fields */
#define ADC_CV1_CV_MASK                          0xFFFFu
#define ADC_CV1_CV_SHIFT                         0
#define ADC_CV1_CV_WIDTH                         16
#define ADC_CV1_CV(x)                            (((uint32_t)(((uint32_t)(x))<<ADC_CV1_CV_SHIFT))&ADC_CV1_CV_MASK)
/* CV2 Bit Fields */
#define ADC_CV2_CV_MASK                          0xFFFFu
#define ADC_CV2_CV_SHIFT                         0
#define ADC_CV2_CV_WIDTH                         16
#define ADC_CV2_CV(x)                            (((uint32_t)(((uint32_t)(x))<<ADC_CV2_CV_SHIFT))&ADC_CV2_CV_MASK)
/* SC2 Bit Fields */
#define ADC_SC2_REFSEL_MASK                      0x3u
#define ADC_SC2_REFSEL_SHIFT                     0
#define ADC_SC2_REFSEL_WIDTH                     2
#define ADC_SC2_REFSEL(x)                        (((uint32_t)(((uint32_t)(x))<<ADC_SC2_REFSEL_SHIFT))&ADC_SC2_REFSEL_MASK)
#define ADC_SC2_DMAEN_MASK                       0x4u
#define ADC_SC2_DMAEN_SHIFT                      2
#define ADC_SC2_DMAEN_WIDTH                      1
#define ADC_SC2_DMAEN(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_DMAEN_SHIFT))&ADC_SC2_DMAEN_MASK)
#define ADC_SC2_ACREN_MASK                       0x8u
#define ADC_SC2_ACREN_SHIFT                      3
#define ADC_SC2_ACREN_WIDTH                      1
#define ADC_SC2_ACREN(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ACREN_SHIFT))&ADC_SC2_ACREN_MASK)
#define ADC_SC2_ACFGT_MASK                       0x10u
#define ADC_SC2_ACFGT_SHIFT                      4
#define ADC_SC2_ACFGT_WIDTH                      1
#define ADC_SC2_ACFGT(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ACFGT_SHIFT))&ADC_SC2_ACFGT_MASK)
#define ADC_SC2_ACFE_MASK                        0x20u
#define ADC_SC2_ACFE_SHIFT                       5
#define ADC_SC2_ACFE_WIDTH                       1
#define ADC_SC2_ACFE(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ACFE_SHIFT))&ADC_SC2_ACFE_MASK)
#define ADC_SC2_ADTRG_MASK                       0x40u
#define ADC_SC2_ADTRG_SHIFT                      6
#define ADC_SC2_ADTRG_WIDTH                      1
#define ADC_SC2_ADTRG(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ADTRG_SHIFT))&ADC_SC2_ADTRG_MASK)
#define ADC_SC2_ADACT_MASK                       0x80u
#define ADC_SC2_ADACT_SHIFT                      7
#define ADC_SC2_ADACT_WIDTH                      1
#define ADC_SC2_ADACT(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ADACT_SHIFT))&ADC_SC2_ADACT_MASK)
/* SC3 Bit Fields */
#define ADC_SC3_AVGS_MASK                        0x3u
#define ADC_SC3_AVGS_SHIFT                       0
#define ADC_SC3_AVGS_WIDTH                       2
#define ADC_SC3_AVGS(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC3_AVGS_SHIFT))&ADC_SC3_AVGS_MASK)
#define ADC_SC3_AVGE_MASK                        0x4u
#define ADC_SC3_AVGE_SHIFT                       2
#define ADC_SC3_AVGE_WIDTH                       1
#define ADC_SC3_AVGE(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC3_AVGE_SHIFT))&ADC_SC3_AVGE_MASK)
#define ADC_SC3_ADCO_MASK                        0x8u
#define ADC_SC3_ADCO_SHIFT                       3
#define ADC_SC3_ADCO_WIDTH                       1
#define ADC_SC3_ADCO(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC3_ADCO_SHIFT))&ADC_SC3_ADCO_MASK)
#define ADC_SC3_CALF_MASK                        0x40u
#define ADC_SC3_CALF_SHIFT                       6
#define ADC_SC3_CALF_WIDTH                       1
#define ADC_SC3_CALF(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC3_CALF_SHIFT))&ADC_SC3_CALF_MASK)
#define ADC_SC3_CAL_MASK                         0x80u
#define ADC_SC3_CAL_SHIFT                        7
#define ADC_SC3_CAL_WIDTH                        1
#define ADC_SC3_CAL(x)                           (((uint32_t)(((uint32_t)(x))<<ADC_SC3_CAL_SHIFT))&ADC_SC3_CAL_MASK)
/* OFS Bit Fields */
#define ADC_OFS_OFS_MASK                         0xFFFFu
#define ADC_OFS_OFS_SHIFT                        0
#define ADC_OFS_OFS_WIDTH                        16
#define ADC_OFS_OFS(x)                           (((uint32_t)(((uint32_t)(x))<<ADC_OFS_OFS_SHIFT))&ADC_OFS_OFS_MASK)
/* PG Bit Fields */
#define ADC_PG_PG_MASK                           0xFFFFu
#define ADC_PG_PG_SHIFT                          0
#define ADC_PG_PG_WIDTH                          16
#define ADC_PG_PG(x)                             (((uint32_t)(((uint32_t)(x))<<ADC_PG_PG_SHIFT))&ADC_PG_PG_MASK)
/* CLPD Bit Fields */
#define ADC_CLPD_CLPD_MASK                       0x3Fu
#define ADC_CLPD_CLPD_SHIFT                      0
#define ADC_CLPD_CLPD_WIDTH                      6
#define ADC_CLPD_CLPD(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLPD_CLPD_SHIFT))&ADC_CLPD_CLPD_MASK)
/* CLPS Bit Fields */
#define ADC_CLPS_CLPS_MASK                       0x3Fu
#define ADC_CLPS_CLPS_SHIFT                      0
#define ADC_CLPS_CLPS_WIDTH                      6
#define ADC_CLPS_CLPS(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLPS_CLPS_SHIFT))&ADC_CLPS_CLPS_MASK)
/* CLP4 Bit Fields */
#define ADC_CLP4_CLP4_MASK                       0x3FFu
#define ADC_CLP4_CLP4_SHIFT                      0
#define ADC_CLP4_CLP4_WIDTH                      10
#define ADC_CLP4_CLP4(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP4_CLP4_SHIFT))&ADC_CLP4_CLP4_MASK)
/* CLP3 Bit Fields */
#define ADC_CLP3_CLP3_MASK                       0x1FFu
#define ADC_CLP3_CLP3_SHIFT                      0
#define ADC_CLP3_CLP3_WIDTH                      9
#define ADC_CLP3_CLP3(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP3_CLP3_SHIFT))&ADC_CLP3_CLP3_MASK)
/* CLP2 Bit Fields */
#define ADC_CLP2_CLP2_MASK                       0xFFu
#define ADC_CLP2_CLP2_SHIFT                      0
#define ADC_CLP2_CLP2_WIDTH                      8
#define ADC_CLP2_CLP2(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP2_CLP2_SHIFT))&ADC_CLP2_CLP2_MASK)
/* CLP1 Bit Fields */
#define ADC_CLP1_CLP1_MASK                       0x7Fu
#define ADC_CLP1_CLP1_SHIFT                      0
#define ADC_CLP1_CLP1_WIDTH                      7
#define ADC_CLP1_CLP1(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP1_CLP1_SHIFT))&ADC_CLP1_CLP1_MASK)
/* CLP0 Bit Fields */
#define ADC_CLP0_CLP0_MASK                       0x3Fu
#define ADC_CLP0_CLP0_SHIFT                      0
#define ADC_CLP0_CLP0_WIDTH                      6
#define ADC_CLP0_CLP0(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP0_CLP0_SHIFT))&ADC_CLP0_CLP0_MASK)

/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base address */
#define ADC0_BASE                                (0x4002B000u)
/** Peripheral ADC0 base pointer */
#define ADC0                                     ((ADC_Type *)ADC0_BASE)
#define ADC0_BASE_PTR                            (ADC0)
/** Array initializer of ADC peripheral base addresses */
#define ADC_BASE_ADDRS                           { ADC0_BASE }
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            { ADC0 }
/** Interrupt vectors for the ADC peripheral type */
#define ADC_IRQS                                 { ADC0_IRQn }

/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register instance definitions */
/* ADC0 */
#define ADC0_SC1A                                ADC_SC1_REG(ADC0,0)
#define ADC0_SC1B                                ADC_SC1_REG(ADC0,1)
#define ADC0_SC1C                                ADC_SC1_REG(ADC0,2)
#define ADC0_SC1D                                ADC_SC1_REG(ADC0,3)
#define ADC0_CFG1                                ADC_CFG1_REG(ADC0)
#define ADC0_CFG2                                ADC_CFG2_REG(ADC0)
#define ADC0_RA                                  ADC_R_REG(ADC0,0)
#define ADC0_RB                                  ADC_R_REG(ADC0,1)
#define ADC0_RC                                  ADC_R_REG(ADC0,2)
#define ADC0_RD                                  ADC_R_REG(ADC0,3)
#define ADC0_CV1                                 ADC_CV1_REG(ADC0)
#define ADC0_CV2                                 ADC_CV2_REG(ADC0)
#define ADC0_SC2                                 ADC_SC2_REG(ADC0)
#define ADC0_SC3                                 ADC_SC3_REG(ADC0)
#define ADC0_OFS                                 ADC_OFS_REG(ADC0)
#define ADC0_PG                                  ADC_PG_REG(ADC0)
#define ADC0_CLPD                                ADC_CLPD_REG(ADC0)
#define ADC0_CLPS                                ADC_CLPS_REG(ADC0)
#define ADC0_CLP4                                ADC_CLP4_REG(ADC0)
#define ADC0_CLP3                                ADC_CLP3_REG(ADC0)
#define ADC0_CLP2                                ADC_CLP2_REG(ADC0)
#define ADC0_CLP1                                ADC_CLP1_REG(ADC0)
#define ADC0_CLP0                                ADC_CLP0_REG(ADC0)

/* ADC - Register array accessors */
#define ADC0_SC1(index)                          ADC_SC1_REG(ADC0,index)
#define ADC0_R(index)                            ADC_R_REG(ADC0,index)

/*!
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ADC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- AFE Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AFE_Peripheral_Access_Layer AFE Peripheral Access Layer
 * @{
 */

/** AFE - Register Layout Typedef */
typedef struct {
  __IO uint32_t CFR[4];                            /**< Channel0 Configuration Register..Channel3 Configuration Register, array offset: 0x0, array step: 0x4 */
       uint8_t RESERVED_0[8];
  __IO uint32_t CR;                                /**< Control Register, offset: 0x18 */
  __IO uint32_t CKR;                               /**< Clock Configuration Register, offset: 0x1C */
  __IO uint32_t DI;                                /**< DMA and Interrupt Register, offset: 0x20 */
       uint8_t RESERVED_1[8];
  __IO uint32_t DR[4];                             /**< Channel0 Delay Register..Channel3 Delay Register, array offset: 0x2C, array step: 0x4 */
       uint8_t RESERVED_2[8];
  __I  uint32_t RR[4];                             /**< Channel0 Result Register..Channel3 Result Register, array offset: 0x44, array step: 0x4 */
       uint8_t RESERVED_3[8];
  __I  uint32_t SR;                                /**< Status Register, offset: 0x5C */
} AFE_Type, *AFE_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- AFE - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AFE_Register_Accessor_Macros AFE - Register accessor macros
 * @{
 */


/* AFE - Register accessors */
#define AFE_CFR_REG(base,index)                  ((base)->CFR[index])
#define AFE_CFR_COUNT                            4
#define AFE_CR_REG(base)                         ((base)->CR)
#define AFE_CKR_REG(base)                        ((base)->CKR)
#define AFE_DI_REG(base)                         ((base)->DI)
#define AFE_DR_REG(base,index)                   ((base)->DR[index])
#define AFE_DR_COUNT                             4
#define AFE_RR_REG(base,index)                   ((base)->RR[index])
#define AFE_RR_COUNT                             4
#define AFE_SR_REG(base)                         ((base)->SR)

/*!
 * @}
 */ /* end of group AFE_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- AFE Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AFE_Register_Masks AFE Register Masks
 * @{
 */

/* CFR Bit Fields */
#define AFE_CFR_HW_TRG_MASK                      0x200u
#define AFE_CFR_HW_TRG_SHIFT                     9
#define AFE_CFR_HW_TRG_WIDTH                     1
#define AFE_CFR_HW_TRG(x)                        (((uint32_t)(((uint32_t)(x))<<AFE_CFR_HW_TRG_SHIFT))&AFE_CFR_HW_TRG_MASK)
#define AFE_CFR_DEC_CLK_INP_SEL_MASK             0x400u
#define AFE_CFR_DEC_CLK_INP_SEL_SHIFT            10
#define AFE_CFR_DEC_CLK_INP_SEL_WIDTH            1
#define AFE_CFR_DEC_CLK_INP_SEL(x)               (((uint32_t)(((uint32_t)(x))<<AFE_CFR_DEC_CLK_INP_SEL_SHIFT))&AFE_CFR_DEC_CLK_INP_SEL_MASK)
#define AFE_CFR_DEC_CLK_EDGE_SEL_MASK            0x800u
#define AFE_CFR_DEC_CLK_EDGE_SEL_SHIFT           11
#define AFE_CFR_DEC_CLK_EDGE_SEL_WIDTH           1
#define AFE_CFR_DEC_CLK_EDGE_SEL(x)              (((uint32_t)(((uint32_t)(x))<<AFE_CFR_DEC_CLK_EDGE_SEL_SHIFT))&AFE_CFR_DEC_CLK_EDGE_SEL_MASK)
#define AFE_CFR_CC_MASK                          0x1000u
#define AFE_CFR_CC_SHIFT                         12
#define AFE_CFR_CC_WIDTH                         1
#define AFE_CFR_CC(x)                            (((uint32_t)(((uint32_t)(x))<<AFE_CFR_CC_SHIFT))&AFE_CFR_CC_MASK)
#define AFE_CFR_DEC_EN_MASK                      0x2000u
#define AFE_CFR_DEC_EN_SHIFT                     13
#define AFE_CFR_DEC_EN_WIDTH                     1
#define AFE_CFR_DEC_EN(x)                        (((uint32_t)(((uint32_t)(x))<<AFE_CFR_DEC_EN_SHIFT))&AFE_CFR_DEC_EN_MASK)
#define AFE_CFR_SD_MOD_EN_MASK                   0x4000u
#define AFE_CFR_SD_MOD_EN_SHIFT                  14
#define AFE_CFR_SD_MOD_EN_WIDTH                  1
#define AFE_CFR_SD_MOD_EN(x)                     (((uint32_t)(((uint32_t)(x))<<AFE_CFR_SD_MOD_EN_SHIFT))&AFE_CFR_SD_MOD_EN_MASK)
#define AFE_CFR_BYP_MODE_MASK                    0x20000u
#define AFE_CFR_BYP_MODE_SHIFT                   17
#define AFE_CFR_BYP_MODE_WIDTH                   1
#define AFE_CFR_BYP_MODE(x)                      (((uint32_t)(((uint32_t)(x))<<AFE_CFR_BYP_MODE_SHIFT))&AFE_CFR_BYP_MODE_MASK)
#define AFE_CFR_PGA_GAIN_SEL_MASK                0x380000u
#define AFE_CFR_PGA_GAIN_SEL_SHIFT               19
#define AFE_CFR_PGA_GAIN_SEL_WIDTH               3
#define AFE_CFR_PGA_GAIN_SEL(x)                  (((uint32_t)(((uint32_t)(x))<<AFE_CFR_PGA_GAIN_SEL_SHIFT))&AFE_CFR_PGA_GAIN_SEL_MASK)
#define AFE_CFR_PGA_EN_MASK                      0x1000000u
#define AFE_CFR_PGA_EN_SHIFT                     24
#define AFE_CFR_PGA_EN_WIDTH                     1
#define AFE_CFR_PGA_EN(x)                        (((uint32_t)(((uint32_t)(x))<<AFE_CFR_PGA_EN_SHIFT))&AFE_CFR_PGA_EN_MASK)
#define AFE_CFR_DEC_OSR_MASK                     0xE0000000u
#define AFE_CFR_DEC_OSR_SHIFT                    29
#define AFE_CFR_DEC_OSR_WIDTH                    3
#define AFE_CFR_DEC_OSR(x)                       (((uint32_t)(((uint32_t)(x))<<AFE_CFR_DEC_OSR_SHIFT))&AFE_CFR_DEC_OSR_MASK)
/* CR Bit Fields */
#define AFE_CR_STRTUP_CNT_MASK                   0xFE00u
#define AFE_CR_STRTUP_CNT_SHIFT                  9
#define AFE_CR_STRTUP_CNT_WIDTH                  7
#define AFE_CR_STRTUP_CNT(x)                     (((uint32_t)(((uint32_t)(x))<<AFE_CR_STRTUP_CNT_SHIFT))&AFE_CR_STRTUP_CNT_MASK)
#define AFE_CR_RESULT_FORMAT_MASK                0x40000u
#define AFE_CR_RESULT_FORMAT_SHIFT               18
#define AFE_CR_RESULT_FORMAT_WIDTH               1
#define AFE_CR_RESULT_FORMAT(x)                  (((uint32_t)(((uint32_t)(x))<<AFE_CR_RESULT_FORMAT_SHIFT))&AFE_CR_RESULT_FORMAT_MASK)
#define AFE_CR_DLY_OK_MASK                       0x200000u
#define AFE_CR_DLY_OK_SHIFT                      21
#define AFE_CR_DLY_OK_WIDTH                      1
#define AFE_CR_DLY_OK(x)                         (((uint32_t)(((uint32_t)(x))<<AFE_CR_DLY_OK_SHIFT))&AFE_CR_DLY_OK_MASK)
#define AFE_CR_RST_B_MASK                        0x400000u
#define AFE_CR_RST_B_SHIFT                       22
#define AFE_CR_RST_B_WIDTH                       1
#define AFE_CR_RST_B(x)                          (((uint32_t)(((uint32_t)(x))<<AFE_CR_RST_B_SHIFT))&AFE_CR_RST_B_MASK)
#define AFE_CR_LPM_EN_MASK                       0x2000000u
#define AFE_CR_LPM_EN_SHIFT                      25
#define AFE_CR_LPM_EN_WIDTH                      1
#define AFE_CR_LPM_EN(x)                         (((uint32_t)(((uint32_t)(x))<<AFE_CR_LPM_EN_SHIFT))&AFE_CR_LPM_EN_MASK)
#define AFE_CR_SOFT_TRG3_MASK                    0x8000000u
#define AFE_CR_SOFT_TRG3_SHIFT                   27
#define AFE_CR_SOFT_TRG3_WIDTH                   1
#define AFE_CR_SOFT_TRG3(x)                      (((uint32_t)(((uint32_t)(x))<<AFE_CR_SOFT_TRG3_SHIFT))&AFE_CR_SOFT_TRG3_MASK)
#define AFE_CR_SOFT_TRG2_MASK                    0x10000000u
#define AFE_CR_SOFT_TRG2_SHIFT                   28
#define AFE_CR_SOFT_TRG2_WIDTH                   1
#define AFE_CR_SOFT_TRG2(x)                      (((uint32_t)(((uint32_t)(x))<<AFE_CR_SOFT_TRG2_SHIFT))&AFE_CR_SOFT_TRG2_MASK)
#define AFE_CR_SOFT_TRG1_MASK                    0x20000000u
#define AFE_CR_SOFT_TRG1_SHIFT                   29
#define AFE_CR_SOFT_TRG1_WIDTH                   1
#define AFE_CR_SOFT_TRG1(x)                      (((uint32_t)(((uint32_t)(x))<<AFE_CR_SOFT_TRG1_SHIFT))&AFE_CR_SOFT_TRG1_MASK)
#define AFE_CR_SOFT_TRG0_MASK                    0x40000000u
#define AFE_CR_SOFT_TRG0_SHIFT                   30
#define AFE_CR_SOFT_TRG0_WIDTH                   1
#define AFE_CR_SOFT_TRG0(x)                      (((uint32_t)(((uint32_t)(x))<<AFE_CR_SOFT_TRG0_SHIFT))&AFE_CR_SOFT_TRG0_MASK)
#define AFE_CR_MSTR_EN_MASK                      0x80000000u
#define AFE_CR_MSTR_EN_SHIFT                     31
#define AFE_CR_MSTR_EN_WIDTH                     1
#define AFE_CR_MSTR_EN(x)                        (((uint32_t)(((uint32_t)(x))<<AFE_CR_MSTR_EN_SHIFT))&AFE_CR_MSTR_EN_MASK)
/* CKR Bit Fields */
#define AFE_CKR_CLS_MASK                         0x600000u
#define AFE_CKR_CLS_SHIFT                        21
#define AFE_CKR_CLS_WIDTH                        2
#define AFE_CKR_CLS(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_CKR_CLS_SHIFT))&AFE_CKR_CLS_MASK)
#define AFE_CKR_DIV_MASK                         0xF0000000u
#define AFE_CKR_DIV_SHIFT                        28
#define AFE_CKR_DIV_WIDTH                        4
#define AFE_CKR_DIV(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_CKR_DIV_SHIFT))&AFE_CKR_DIV_MASK)
/* DI Bit Fields */
#define AFE_DI_INTEN3_MASK                       0x800000u
#define AFE_DI_INTEN3_SHIFT                      23
#define AFE_DI_INTEN3_WIDTH                      1
#define AFE_DI_INTEN3(x)                         (((uint32_t)(((uint32_t)(x))<<AFE_DI_INTEN3_SHIFT))&AFE_DI_INTEN3_MASK)
#define AFE_DI_INTEN2_MASK                       0x1000000u
#define AFE_DI_INTEN2_SHIFT                      24
#define AFE_DI_INTEN2_WIDTH                      1
#define AFE_DI_INTEN2(x)                         (((uint32_t)(((uint32_t)(x))<<AFE_DI_INTEN2_SHIFT))&AFE_DI_INTEN2_MASK)
#define AFE_DI_INTEN1_MASK                       0x2000000u
#define AFE_DI_INTEN1_SHIFT                      25
#define AFE_DI_INTEN1_WIDTH                      1
#define AFE_DI_INTEN1(x)                         (((uint32_t)(((uint32_t)(x))<<AFE_DI_INTEN1_SHIFT))&AFE_DI_INTEN1_MASK)
#define AFE_DI_INTEN0_MASK                       0x4000000u
#define AFE_DI_INTEN0_SHIFT                      26
#define AFE_DI_INTEN0_WIDTH                      1
#define AFE_DI_INTEN0(x)                         (((uint32_t)(((uint32_t)(x))<<AFE_DI_INTEN0_SHIFT))&AFE_DI_INTEN0_MASK)
#define AFE_DI_DMAEN3_MASK                       0x10000000u
#define AFE_DI_DMAEN3_SHIFT                      28
#define AFE_DI_DMAEN3_WIDTH                      1
#define AFE_DI_DMAEN3(x)                         (((uint32_t)(((uint32_t)(x))<<AFE_DI_DMAEN3_SHIFT))&AFE_DI_DMAEN3_MASK)
#define AFE_DI_DMAEN2_MASK                       0x20000000u
#define AFE_DI_DMAEN2_SHIFT                      29
#define AFE_DI_DMAEN2_WIDTH                      1
#define AFE_DI_DMAEN2(x)                         (((uint32_t)(((uint32_t)(x))<<AFE_DI_DMAEN2_SHIFT))&AFE_DI_DMAEN2_MASK)
#define AFE_DI_DMAEN1_MASK                       0x40000000u
#define AFE_DI_DMAEN1_SHIFT                      30
#define AFE_DI_DMAEN1_WIDTH                      1
#define AFE_DI_DMAEN1(x)                         (((uint32_t)(((uint32_t)(x))<<AFE_DI_DMAEN1_SHIFT))&AFE_DI_DMAEN1_MASK)
#define AFE_DI_DMAEN0_MASK                       0x80000000u
#define AFE_DI_DMAEN0_SHIFT                      31
#define AFE_DI_DMAEN0_WIDTH                      1
#define AFE_DI_DMAEN0(x)                         (((uint32_t)(((uint32_t)(x))<<AFE_DI_DMAEN0_SHIFT))&AFE_DI_DMAEN0_MASK)
/* DR Bit Fields */
#define AFE_DR_DLY_MASK                          0x7FFu
#define AFE_DR_DLY_SHIFT                         0
#define AFE_DR_DLY_WIDTH                         11
#define AFE_DR_DLY(x)                            (((uint32_t)(((uint32_t)(x))<<AFE_DR_DLY_SHIFT))&AFE_DR_DLY_MASK)
/* RR Bit Fields */
#define AFE_RR_SDR_MASK                          0x7FFFFFu
#define AFE_RR_SDR_SHIFT                         0
#define AFE_RR_SDR_WIDTH                         23
#define AFE_RR_SDR(x)                            (((uint32_t)(((uint32_t)(x))<<AFE_RR_SDR_SHIFT))&AFE_RR_SDR_MASK)
#define AFE_RR_SIGN_BITS_MASK                    0xFF800000u
#define AFE_RR_SIGN_BITS_SHIFT                   23
#define AFE_RR_SIGN_BITS_WIDTH                   9
#define AFE_RR_SIGN_BITS(x)                      (((uint32_t)(((uint32_t)(x))<<AFE_RR_SIGN_BITS_SHIFT))&AFE_RR_SIGN_BITS_MASK)
/* SR Bit Fields */
#define AFE_SR_RDY3_MASK                         0x10000u
#define AFE_SR_RDY3_SHIFT                        16
#define AFE_SR_RDY3_WIDTH                        1
#define AFE_SR_RDY3(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_SR_RDY3_SHIFT))&AFE_SR_RDY3_MASK)
#define AFE_SR_RDY2_MASK                         0x20000u
#define AFE_SR_RDY2_SHIFT                        17
#define AFE_SR_RDY2_WIDTH                        1
#define AFE_SR_RDY2(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_SR_RDY2_SHIFT))&AFE_SR_RDY2_MASK)
#define AFE_SR_RDY1_MASK                         0x40000u
#define AFE_SR_RDY1_SHIFT                        18
#define AFE_SR_RDY1_WIDTH                        1
#define AFE_SR_RDY1(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_SR_RDY1_SHIFT))&AFE_SR_RDY1_MASK)
#define AFE_SR_RDY0_MASK                         0x80000u
#define AFE_SR_RDY0_SHIFT                        19
#define AFE_SR_RDY0_WIDTH                        1
#define AFE_SR_RDY0(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_SR_RDY0_SHIFT))&AFE_SR_RDY0_MASK)
#define AFE_SR_OVR3_MASK                         0x200000u
#define AFE_SR_OVR3_SHIFT                        21
#define AFE_SR_OVR3_WIDTH                        1
#define AFE_SR_OVR3(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_SR_OVR3_SHIFT))&AFE_SR_OVR3_MASK)
#define AFE_SR_OVR2_MASK                         0x400000u
#define AFE_SR_OVR2_SHIFT                        22
#define AFE_SR_OVR2_WIDTH                        1
#define AFE_SR_OVR2(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_SR_OVR2_SHIFT))&AFE_SR_OVR2_MASK)
#define AFE_SR_OVR1_MASK                         0x800000u
#define AFE_SR_OVR1_SHIFT                        23
#define AFE_SR_OVR1_WIDTH                        1
#define AFE_SR_OVR1(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_SR_OVR1_SHIFT))&AFE_SR_OVR1_MASK)
#define AFE_SR_OVR0_MASK                         0x1000000u
#define AFE_SR_OVR0_SHIFT                        24
#define AFE_SR_OVR0_WIDTH                        1
#define AFE_SR_OVR0(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_SR_OVR0_SHIFT))&AFE_SR_OVR0_MASK)
#define AFE_SR_COC3_MASK                         0x10000000u
#define AFE_SR_COC3_SHIFT                        28
#define AFE_SR_COC3_WIDTH                        1
#define AFE_SR_COC3(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_SR_COC3_SHIFT))&AFE_SR_COC3_MASK)
#define AFE_SR_COC2_MASK                         0x20000000u
#define AFE_SR_COC2_SHIFT                        29
#define AFE_SR_COC2_WIDTH                        1
#define AFE_SR_COC2(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_SR_COC2_SHIFT))&AFE_SR_COC2_MASK)
#define AFE_SR_COC1_MASK                         0x40000000u
#define AFE_SR_COC1_SHIFT                        30
#define AFE_SR_COC1_WIDTH                        1
#define AFE_SR_COC1(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_SR_COC1_SHIFT))&AFE_SR_COC1_MASK)
#define AFE_SR_COC0_MASK                         0x80000000u
#define AFE_SR_COC0_SHIFT                        31
#define AFE_SR_COC0_WIDTH                        1
#define AFE_SR_COC0(x)                           (((uint32_t)(((uint32_t)(x))<<AFE_SR_COC0_SHIFT))&AFE_SR_COC0_MASK)

/*!
 * @}
 */ /* end of group AFE_Register_Masks */


/* AFE - Peripheral instance base addresses */
/** Peripheral AFE base address */
#define AFE_BASE                                 (0x40030000u)
/** Peripheral AFE base pointer */
#define AFE                                      ((AFE_Type *)AFE_BASE)
#define AFE_BASE_PTR                             (AFE)
/** Array initializer of AFE peripheral base addresses */
#define AFE_BASE_ADDRS                           { AFE_BASE }
/** Array initializer of AFE peripheral base pointers */
#define AFE_BASE_PTRS                            { AFE }
/** Interrupt vectors for the AFE peripheral type */
#define AFE_IRQS                                 { AFE_CH0_IRQn, AFE_CH1_IRQn, AFE_CH2_IRQn, AFE_CH3_IRQn }

/* ----------------------------------------------------------------------------
   -- AFE - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AFE_Register_Accessor_Macros AFE - Register accessor macros
 * @{
 */


/* AFE - Register instance definitions */
/* AFE */
#define AFE_CH0_CFR                              AFE_CFR_REG(AFE,0)
#define AFE_CH1_CFR                              AFE_CFR_REG(AFE,1)
#define AFE_CH2_CFR                              AFE_CFR_REG(AFE,2)
#define AFE_CH3_CFR                              AFE_CFR_REG(AFE,3)
#define AFE_CR                                   AFE_CR_REG(AFE)
#define AFE_CKR                                  AFE_CKR_REG(AFE)
#define AFE_DI                                   AFE_DI_REG(AFE)
#define AFE_CH0_DR                               AFE_DR_REG(AFE,0)
#define AFE_CH1_DR                               AFE_DR_REG(AFE,1)
#define AFE_CH2_DR                               AFE_DR_REG(AFE,2)
#define AFE_CH3_DR                               AFE_DR_REG(AFE,3)
#define AFE_CH0_RR                               AFE_RR_REG(AFE,0)
#define AFE_CH1_RR                               AFE_RR_REG(AFE,1)
#define AFE_CH2_RR                               AFE_RR_REG(AFE,2)
#define AFE_CH3_RR                               AFE_RR_REG(AFE,3)
#define AFE_SR                                   AFE_SR_REG(AFE)

/* AFE - Register array accessors */
#define AFE_CFR(index)                           AFE_CFR_REG(AFE,index)
#define AFE_DR(index)                            AFE_DR_REG(AFE,index)
#define AFE_RR(index)                            AFE_RR_REG(AFE,index)

/*!
 * @}
 */ /* end of group AFE_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group AFE_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- AIPS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AIPS_Peripheral_Access_Layer AIPS Peripheral Access Layer
 * @{
 */

/** AIPS - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[32];
  __IO uint32_t PACRA;                             /**< Peripheral Access Control Register, offset: 0x20 */
  __IO uint32_t PACRB;                             /**< Peripheral Access Control Register, offset: 0x24 */
       uint8_t RESERVED_1[24];
  __IO uint32_t PACRE;                             /**< Peripheral Access Control Register, offset: 0x40 */
  __IO uint32_t PACRF;                             /**< Peripheral Access Control Register, offset: 0x44 */
  __IO uint32_t PACRG;                             /**< Peripheral Access Control Register, offset: 0x48 */
  __IO uint32_t PACRH;                             /**< Peripheral Access Control Register, offset: 0x4C */
  __IO uint32_t PACRI;                             /**< Peripheral Access Control Register, offset: 0x50 */
  __IO uint32_t PACRJ;                             /**< Peripheral Access Control Register, offset: 0x54 */
  __IO uint32_t PACRK;                             /**< Peripheral Access Control Register, offset: 0x58 */
  __IO uint32_t PACRL;                             /**< Peripheral Access Control Register, offset: 0x5C */
  __IO uint32_t PACRM;                             /**< Peripheral Access Control Register, offset: 0x60 */
  __IO uint32_t PACRN;                             /**< Peripheral Access Control Register, offset: 0x64 */
  __IO uint32_t PACRO;                             /**< Peripheral Access Control Register, offset: 0x68 */
  __IO uint32_t PACRP;                             /**< Peripheral Access Control Register, offset: 0x6C */
} AIPS_Type, *AIPS_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- AIPS - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AIPS_Register_Accessor_Macros AIPS - Register accessor macros
 * @{
 */


/* AIPS - Register accessors */
#define AIPS_PACRA_REG(base)                     ((base)->PACRA)
#define AIPS_PACRB_REG(base)                     ((base)->PACRB)
#define AIPS_PACRE_REG(base)                     ((base)->PACRE)
#define AIPS_PACRF_REG(base)                     ((base)->PACRF)
#define AIPS_PACRG_REG(base)                     ((base)->PACRG)
#define AIPS_PACRH_REG(base)                     ((base)->PACRH)
#define AIPS_PACRI_REG(base)                     ((base)->PACRI)
#define AIPS_PACRJ_REG(base)                     ((base)->PACRJ)
#define AIPS_PACRK_REG(base)                     ((base)->PACRK)
#define AIPS_PACRL_REG(base)                     ((base)->PACRL)
#define AIPS_PACRM_REG(base)                     ((base)->PACRM)
#define AIPS_PACRN_REG(base)                     ((base)->PACRN)
#define AIPS_PACRO_REG(base)                     ((base)->PACRO)
#define AIPS_PACRP_REG(base)                     ((base)->PACRP)

/*!
 * @}
 */ /* end of group AIPS_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- AIPS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AIPS_Register_Masks AIPS Register Masks
 * @{
 */

/* PACRA Bit Fields */
#define AIPS_PACRA_AC7_MASK                      0x7u
#define AIPS_PACRA_AC7_SHIFT                     0
#define AIPS_PACRA_AC7_WIDTH                     3
#define AIPS_PACRA_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_AC7_SHIFT))&AIPS_PACRA_AC7_MASK)
#define AIPS_PACRA_RO7_MASK                      0x8u
#define AIPS_PACRA_RO7_SHIFT                     3
#define AIPS_PACRA_RO7_WIDTH                     1
#define AIPS_PACRA_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_RO7_SHIFT))&AIPS_PACRA_RO7_MASK)
#define AIPS_PACRA_AC6_MASK                      0x70u
#define AIPS_PACRA_AC6_SHIFT                     4
#define AIPS_PACRA_AC6_WIDTH                     3
#define AIPS_PACRA_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_AC6_SHIFT))&AIPS_PACRA_AC6_MASK)
#define AIPS_PACRA_RO6_MASK                      0x80u
#define AIPS_PACRA_RO6_SHIFT                     7
#define AIPS_PACRA_RO6_WIDTH                     1
#define AIPS_PACRA_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_RO6_SHIFT))&AIPS_PACRA_RO6_MASK)
#define AIPS_PACRA_AC5_MASK                      0x700u
#define AIPS_PACRA_AC5_SHIFT                     8
#define AIPS_PACRA_AC5_WIDTH                     3
#define AIPS_PACRA_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_AC5_SHIFT))&AIPS_PACRA_AC5_MASK)
#define AIPS_PACRA_RO5_MASK                      0x800u
#define AIPS_PACRA_RO5_SHIFT                     11
#define AIPS_PACRA_RO5_WIDTH                     1
#define AIPS_PACRA_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_RO5_SHIFT))&AIPS_PACRA_RO5_MASK)
#define AIPS_PACRA_AC4_MASK                      0x7000u
#define AIPS_PACRA_AC4_SHIFT                     12
#define AIPS_PACRA_AC4_WIDTH                     3
#define AIPS_PACRA_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_AC4_SHIFT))&AIPS_PACRA_AC4_MASK)
#define AIPS_PACRA_RO4_MASK                      0x8000u
#define AIPS_PACRA_RO4_SHIFT                     15
#define AIPS_PACRA_RO4_WIDTH                     1
#define AIPS_PACRA_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_RO4_SHIFT))&AIPS_PACRA_RO4_MASK)
#define AIPS_PACRA_AC3_MASK                      0x70000u
#define AIPS_PACRA_AC3_SHIFT                     16
#define AIPS_PACRA_AC3_WIDTH                     3
#define AIPS_PACRA_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_AC3_SHIFT))&AIPS_PACRA_AC3_MASK)
#define AIPS_PACRA_RO3_MASK                      0x80000u
#define AIPS_PACRA_RO3_SHIFT                     19
#define AIPS_PACRA_RO3_WIDTH                     1
#define AIPS_PACRA_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_RO3_SHIFT))&AIPS_PACRA_RO3_MASK)
#define AIPS_PACRA_AC2_MASK                      0x700000u
#define AIPS_PACRA_AC2_SHIFT                     20
#define AIPS_PACRA_AC2_WIDTH                     3
#define AIPS_PACRA_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_AC2_SHIFT))&AIPS_PACRA_AC2_MASK)
#define AIPS_PACRA_RO2_MASK                      0x800000u
#define AIPS_PACRA_RO2_SHIFT                     23
#define AIPS_PACRA_RO2_WIDTH                     1
#define AIPS_PACRA_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_RO2_SHIFT))&AIPS_PACRA_RO2_MASK)
#define AIPS_PACRA_AC1_MASK                      0x7000000u
#define AIPS_PACRA_AC1_SHIFT                     24
#define AIPS_PACRA_AC1_WIDTH                     3
#define AIPS_PACRA_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_AC1_SHIFT))&AIPS_PACRA_AC1_MASK)
#define AIPS_PACRA_RO1_MASK                      0x8000000u
#define AIPS_PACRA_RO1_SHIFT                     27
#define AIPS_PACRA_RO1_WIDTH                     1
#define AIPS_PACRA_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_RO1_SHIFT))&AIPS_PACRA_RO1_MASK)
#define AIPS_PACRA_AC0_MASK                      0x70000000u
#define AIPS_PACRA_AC0_SHIFT                     28
#define AIPS_PACRA_AC0_WIDTH                     3
#define AIPS_PACRA_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_AC0_SHIFT))&AIPS_PACRA_AC0_MASK)
#define AIPS_PACRA_RO0_MASK                      0x80000000u
#define AIPS_PACRA_RO0_SHIFT                     31
#define AIPS_PACRA_RO0_WIDTH                     1
#define AIPS_PACRA_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRA_RO0_SHIFT))&AIPS_PACRA_RO0_MASK)
/* PACRB Bit Fields */
#define AIPS_PACRB_AC7_MASK                      0x7u
#define AIPS_PACRB_AC7_SHIFT                     0
#define AIPS_PACRB_AC7_WIDTH                     3
#define AIPS_PACRB_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_AC7_SHIFT))&AIPS_PACRB_AC7_MASK)
#define AIPS_PACRB_RO7_MASK                      0x8u
#define AIPS_PACRB_RO7_SHIFT                     3
#define AIPS_PACRB_RO7_WIDTH                     1
#define AIPS_PACRB_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_RO7_SHIFT))&AIPS_PACRB_RO7_MASK)
#define AIPS_PACRB_AC6_MASK                      0x70u
#define AIPS_PACRB_AC6_SHIFT                     4
#define AIPS_PACRB_AC6_WIDTH                     3
#define AIPS_PACRB_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_AC6_SHIFT))&AIPS_PACRB_AC6_MASK)
#define AIPS_PACRB_RO6_MASK                      0x80u
#define AIPS_PACRB_RO6_SHIFT                     7
#define AIPS_PACRB_RO6_WIDTH                     1
#define AIPS_PACRB_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_RO6_SHIFT))&AIPS_PACRB_RO6_MASK)
#define AIPS_PACRB_AC5_MASK                      0x700u
#define AIPS_PACRB_AC5_SHIFT                     8
#define AIPS_PACRB_AC5_WIDTH                     3
#define AIPS_PACRB_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_AC5_SHIFT))&AIPS_PACRB_AC5_MASK)
#define AIPS_PACRB_RO5_MASK                      0x800u
#define AIPS_PACRB_RO5_SHIFT                     11
#define AIPS_PACRB_RO5_WIDTH                     1
#define AIPS_PACRB_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_RO5_SHIFT))&AIPS_PACRB_RO5_MASK)
#define AIPS_PACRB_AC4_MASK                      0x7000u
#define AIPS_PACRB_AC4_SHIFT                     12
#define AIPS_PACRB_AC4_WIDTH                     3
#define AIPS_PACRB_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_AC4_SHIFT))&AIPS_PACRB_AC4_MASK)
#define AIPS_PACRB_RO4_MASK                      0x8000u
#define AIPS_PACRB_RO4_SHIFT                     15
#define AIPS_PACRB_RO4_WIDTH                     1
#define AIPS_PACRB_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_RO4_SHIFT))&AIPS_PACRB_RO4_MASK)
#define AIPS_PACRB_AC3_MASK                      0x70000u
#define AIPS_PACRB_AC3_SHIFT                     16
#define AIPS_PACRB_AC3_WIDTH                     3
#define AIPS_PACRB_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_AC3_SHIFT))&AIPS_PACRB_AC3_MASK)
#define AIPS_PACRB_RO3_MASK                      0x80000u
#define AIPS_PACRB_RO3_SHIFT                     19
#define AIPS_PACRB_RO3_WIDTH                     1
#define AIPS_PACRB_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_RO3_SHIFT))&AIPS_PACRB_RO3_MASK)
#define AIPS_PACRB_AC2_MASK                      0x700000u
#define AIPS_PACRB_AC2_SHIFT                     20
#define AIPS_PACRB_AC2_WIDTH                     3
#define AIPS_PACRB_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_AC2_SHIFT))&AIPS_PACRB_AC2_MASK)
#define AIPS_PACRB_RO2_MASK                      0x800000u
#define AIPS_PACRB_RO2_SHIFT                     23
#define AIPS_PACRB_RO2_WIDTH                     1
#define AIPS_PACRB_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_RO2_SHIFT))&AIPS_PACRB_RO2_MASK)
#define AIPS_PACRB_AC1_MASK                      0x7000000u
#define AIPS_PACRB_AC1_SHIFT                     24
#define AIPS_PACRB_AC1_WIDTH                     3
#define AIPS_PACRB_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_AC1_SHIFT))&AIPS_PACRB_AC1_MASK)
#define AIPS_PACRB_RO1_MASK                      0x8000000u
#define AIPS_PACRB_RO1_SHIFT                     27
#define AIPS_PACRB_RO1_WIDTH                     1
#define AIPS_PACRB_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_RO1_SHIFT))&AIPS_PACRB_RO1_MASK)
#define AIPS_PACRB_AC0_MASK                      0x70000000u
#define AIPS_PACRB_AC0_SHIFT                     28
#define AIPS_PACRB_AC0_WIDTH                     3
#define AIPS_PACRB_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_AC0_SHIFT))&AIPS_PACRB_AC0_MASK)
#define AIPS_PACRB_RO0_MASK                      0x80000000u
#define AIPS_PACRB_RO0_SHIFT                     31
#define AIPS_PACRB_RO0_WIDTH                     1
#define AIPS_PACRB_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRB_RO0_SHIFT))&AIPS_PACRB_RO0_MASK)
/* PACRE Bit Fields */
#define AIPS_PACRE_AC7_MASK                      0x7u
#define AIPS_PACRE_AC7_SHIFT                     0
#define AIPS_PACRE_AC7_WIDTH                     3
#define AIPS_PACRE_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_AC7_SHIFT))&AIPS_PACRE_AC7_MASK)
#define AIPS_PACRE_RO7_MASK                      0x8u
#define AIPS_PACRE_RO7_SHIFT                     3
#define AIPS_PACRE_RO7_WIDTH                     1
#define AIPS_PACRE_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_RO7_SHIFT))&AIPS_PACRE_RO7_MASK)
#define AIPS_PACRE_AC6_MASK                      0x70u
#define AIPS_PACRE_AC6_SHIFT                     4
#define AIPS_PACRE_AC6_WIDTH                     3
#define AIPS_PACRE_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_AC6_SHIFT))&AIPS_PACRE_AC6_MASK)
#define AIPS_PACRE_RO6_MASK                      0x80u
#define AIPS_PACRE_RO6_SHIFT                     7
#define AIPS_PACRE_RO6_WIDTH                     1
#define AIPS_PACRE_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_RO6_SHIFT))&AIPS_PACRE_RO6_MASK)
#define AIPS_PACRE_AC5_MASK                      0x700u
#define AIPS_PACRE_AC5_SHIFT                     8
#define AIPS_PACRE_AC5_WIDTH                     3
#define AIPS_PACRE_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_AC5_SHIFT))&AIPS_PACRE_AC5_MASK)
#define AIPS_PACRE_RO5_MASK                      0x800u
#define AIPS_PACRE_RO5_SHIFT                     11
#define AIPS_PACRE_RO5_WIDTH                     1
#define AIPS_PACRE_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_RO5_SHIFT))&AIPS_PACRE_RO5_MASK)
#define AIPS_PACRE_AC4_MASK                      0x7000u
#define AIPS_PACRE_AC4_SHIFT                     12
#define AIPS_PACRE_AC4_WIDTH                     3
#define AIPS_PACRE_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_AC4_SHIFT))&AIPS_PACRE_AC4_MASK)
#define AIPS_PACRE_RO4_MASK                      0x8000u
#define AIPS_PACRE_RO4_SHIFT                     15
#define AIPS_PACRE_RO4_WIDTH                     1
#define AIPS_PACRE_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_RO4_SHIFT))&AIPS_PACRE_RO4_MASK)
#define AIPS_PACRE_AC3_MASK                      0x70000u
#define AIPS_PACRE_AC3_SHIFT                     16
#define AIPS_PACRE_AC3_WIDTH                     3
#define AIPS_PACRE_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_AC3_SHIFT))&AIPS_PACRE_AC3_MASK)
#define AIPS_PACRE_RO3_MASK                      0x80000u
#define AIPS_PACRE_RO3_SHIFT                     19
#define AIPS_PACRE_RO3_WIDTH                     1
#define AIPS_PACRE_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_RO3_SHIFT))&AIPS_PACRE_RO3_MASK)
#define AIPS_PACRE_AC2_MASK                      0x700000u
#define AIPS_PACRE_AC2_SHIFT                     20
#define AIPS_PACRE_AC2_WIDTH                     3
#define AIPS_PACRE_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_AC2_SHIFT))&AIPS_PACRE_AC2_MASK)
#define AIPS_PACRE_RO2_MASK                      0x800000u
#define AIPS_PACRE_RO2_SHIFT                     23
#define AIPS_PACRE_RO2_WIDTH                     1
#define AIPS_PACRE_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_RO2_SHIFT))&AIPS_PACRE_RO2_MASK)
#define AIPS_PACRE_AC1_MASK                      0x7000000u
#define AIPS_PACRE_AC1_SHIFT                     24
#define AIPS_PACRE_AC1_WIDTH                     3
#define AIPS_PACRE_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_AC1_SHIFT))&AIPS_PACRE_AC1_MASK)
#define AIPS_PACRE_RO1_MASK                      0x8000000u
#define AIPS_PACRE_RO1_SHIFT                     27
#define AIPS_PACRE_RO1_WIDTH                     1
#define AIPS_PACRE_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_RO1_SHIFT))&AIPS_PACRE_RO1_MASK)
#define AIPS_PACRE_AC0_MASK                      0x70000000u
#define AIPS_PACRE_AC0_SHIFT                     28
#define AIPS_PACRE_AC0_WIDTH                     3
#define AIPS_PACRE_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_AC0_SHIFT))&AIPS_PACRE_AC0_MASK)
#define AIPS_PACRE_RO0_MASK                      0x80000000u
#define AIPS_PACRE_RO0_SHIFT                     31
#define AIPS_PACRE_RO0_WIDTH                     1
#define AIPS_PACRE_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRE_RO0_SHIFT))&AIPS_PACRE_RO0_MASK)
/* PACRF Bit Fields */
#define AIPS_PACRF_AC7_MASK                      0x7u
#define AIPS_PACRF_AC7_SHIFT                     0
#define AIPS_PACRF_AC7_WIDTH                     3
#define AIPS_PACRF_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_AC7_SHIFT))&AIPS_PACRF_AC7_MASK)
#define AIPS_PACRF_RO7_MASK                      0x8u
#define AIPS_PACRF_RO7_SHIFT                     3
#define AIPS_PACRF_RO7_WIDTH                     1
#define AIPS_PACRF_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_RO7_SHIFT))&AIPS_PACRF_RO7_MASK)
#define AIPS_PACRF_AC6_MASK                      0x70u
#define AIPS_PACRF_AC6_SHIFT                     4
#define AIPS_PACRF_AC6_WIDTH                     3
#define AIPS_PACRF_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_AC6_SHIFT))&AIPS_PACRF_AC6_MASK)
#define AIPS_PACRF_RO6_MASK                      0x80u
#define AIPS_PACRF_RO6_SHIFT                     7
#define AIPS_PACRF_RO6_WIDTH                     1
#define AIPS_PACRF_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_RO6_SHIFT))&AIPS_PACRF_RO6_MASK)
#define AIPS_PACRF_AC5_MASK                      0x700u
#define AIPS_PACRF_AC5_SHIFT                     8
#define AIPS_PACRF_AC5_WIDTH                     3
#define AIPS_PACRF_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_AC5_SHIFT))&AIPS_PACRF_AC5_MASK)
#define AIPS_PACRF_RO5_MASK                      0x800u
#define AIPS_PACRF_RO5_SHIFT                     11
#define AIPS_PACRF_RO5_WIDTH                     1
#define AIPS_PACRF_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_RO5_SHIFT))&AIPS_PACRF_RO5_MASK)
#define AIPS_PACRF_AC4_MASK                      0x7000u
#define AIPS_PACRF_AC4_SHIFT                     12
#define AIPS_PACRF_AC4_WIDTH                     3
#define AIPS_PACRF_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_AC4_SHIFT))&AIPS_PACRF_AC4_MASK)
#define AIPS_PACRF_RO4_MASK                      0x8000u
#define AIPS_PACRF_RO4_SHIFT                     15
#define AIPS_PACRF_RO4_WIDTH                     1
#define AIPS_PACRF_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_RO4_SHIFT))&AIPS_PACRF_RO4_MASK)
#define AIPS_PACRF_AC3_MASK                      0x70000u
#define AIPS_PACRF_AC3_SHIFT                     16
#define AIPS_PACRF_AC3_WIDTH                     3
#define AIPS_PACRF_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_AC3_SHIFT))&AIPS_PACRF_AC3_MASK)
#define AIPS_PACRF_RO3_MASK                      0x80000u
#define AIPS_PACRF_RO3_SHIFT                     19
#define AIPS_PACRF_RO3_WIDTH                     1
#define AIPS_PACRF_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_RO3_SHIFT))&AIPS_PACRF_RO3_MASK)
#define AIPS_PACRF_AC2_MASK                      0x700000u
#define AIPS_PACRF_AC2_SHIFT                     20
#define AIPS_PACRF_AC2_WIDTH                     3
#define AIPS_PACRF_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_AC2_SHIFT))&AIPS_PACRF_AC2_MASK)
#define AIPS_PACRF_RO2_MASK                      0x800000u
#define AIPS_PACRF_RO2_SHIFT                     23
#define AIPS_PACRF_RO2_WIDTH                     1
#define AIPS_PACRF_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_RO2_SHIFT))&AIPS_PACRF_RO2_MASK)
#define AIPS_PACRF_AC1_MASK                      0x7000000u
#define AIPS_PACRF_AC1_SHIFT                     24
#define AIPS_PACRF_AC1_WIDTH                     3
#define AIPS_PACRF_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_AC1_SHIFT))&AIPS_PACRF_AC1_MASK)
#define AIPS_PACRF_RO1_MASK                      0x8000000u
#define AIPS_PACRF_RO1_SHIFT                     27
#define AIPS_PACRF_RO1_WIDTH                     1
#define AIPS_PACRF_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_RO1_SHIFT))&AIPS_PACRF_RO1_MASK)
#define AIPS_PACRF_AC0_MASK                      0x70000000u
#define AIPS_PACRF_AC0_SHIFT                     28
#define AIPS_PACRF_AC0_WIDTH                     3
#define AIPS_PACRF_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_AC0_SHIFT))&AIPS_PACRF_AC0_MASK)
#define AIPS_PACRF_RO0_MASK                      0x80000000u
#define AIPS_PACRF_RO0_SHIFT                     31
#define AIPS_PACRF_RO0_WIDTH                     1
#define AIPS_PACRF_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRF_RO0_SHIFT))&AIPS_PACRF_RO0_MASK)
/* PACRG Bit Fields */
#define AIPS_PACRG_AC7_MASK                      0x7u
#define AIPS_PACRG_AC7_SHIFT                     0
#define AIPS_PACRG_AC7_WIDTH                     3
#define AIPS_PACRG_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_AC7_SHIFT))&AIPS_PACRG_AC7_MASK)
#define AIPS_PACRG_RO7_MASK                      0x8u
#define AIPS_PACRG_RO7_SHIFT                     3
#define AIPS_PACRG_RO7_WIDTH                     1
#define AIPS_PACRG_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_RO7_SHIFT))&AIPS_PACRG_RO7_MASK)
#define AIPS_PACRG_AC6_MASK                      0x70u
#define AIPS_PACRG_AC6_SHIFT                     4
#define AIPS_PACRG_AC6_WIDTH                     3
#define AIPS_PACRG_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_AC6_SHIFT))&AIPS_PACRG_AC6_MASK)
#define AIPS_PACRG_RO6_MASK                      0x80u
#define AIPS_PACRG_RO6_SHIFT                     7
#define AIPS_PACRG_RO6_WIDTH                     1
#define AIPS_PACRG_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_RO6_SHIFT))&AIPS_PACRG_RO6_MASK)
#define AIPS_PACRG_AC5_MASK                      0x700u
#define AIPS_PACRG_AC5_SHIFT                     8
#define AIPS_PACRG_AC5_WIDTH                     3
#define AIPS_PACRG_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_AC5_SHIFT))&AIPS_PACRG_AC5_MASK)
#define AIPS_PACRG_RO5_MASK                      0x800u
#define AIPS_PACRG_RO5_SHIFT                     11
#define AIPS_PACRG_RO5_WIDTH                     1
#define AIPS_PACRG_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_RO5_SHIFT))&AIPS_PACRG_RO5_MASK)
#define AIPS_PACRG_AC4_MASK                      0x7000u
#define AIPS_PACRG_AC4_SHIFT                     12
#define AIPS_PACRG_AC4_WIDTH                     3
#define AIPS_PACRG_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_AC4_SHIFT))&AIPS_PACRG_AC4_MASK)
#define AIPS_PACRG_RO4_MASK                      0x8000u
#define AIPS_PACRG_RO4_SHIFT                     15
#define AIPS_PACRG_RO4_WIDTH                     1
#define AIPS_PACRG_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_RO4_SHIFT))&AIPS_PACRG_RO4_MASK)
#define AIPS_PACRG_AC3_MASK                      0x70000u
#define AIPS_PACRG_AC3_SHIFT                     16
#define AIPS_PACRG_AC3_WIDTH                     3
#define AIPS_PACRG_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_AC3_SHIFT))&AIPS_PACRG_AC3_MASK)
#define AIPS_PACRG_RO3_MASK                      0x80000u
#define AIPS_PACRG_RO3_SHIFT                     19
#define AIPS_PACRG_RO3_WIDTH                     1
#define AIPS_PACRG_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_RO3_SHIFT))&AIPS_PACRG_RO3_MASK)
#define AIPS_PACRG_AC2_MASK                      0x700000u
#define AIPS_PACRG_AC2_SHIFT                     20
#define AIPS_PACRG_AC2_WIDTH                     3
#define AIPS_PACRG_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_AC2_SHIFT))&AIPS_PACRG_AC2_MASK)
#define AIPS_PACRG_RO2_MASK                      0x800000u
#define AIPS_PACRG_RO2_SHIFT                     23
#define AIPS_PACRG_RO2_WIDTH                     1
#define AIPS_PACRG_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_RO2_SHIFT))&AIPS_PACRG_RO2_MASK)
#define AIPS_PACRG_AC1_MASK                      0x7000000u
#define AIPS_PACRG_AC1_SHIFT                     24
#define AIPS_PACRG_AC1_WIDTH                     3
#define AIPS_PACRG_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_AC1_SHIFT))&AIPS_PACRG_AC1_MASK)
#define AIPS_PACRG_RO1_MASK                      0x8000000u
#define AIPS_PACRG_RO1_SHIFT                     27
#define AIPS_PACRG_RO1_WIDTH                     1
#define AIPS_PACRG_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_RO1_SHIFT))&AIPS_PACRG_RO1_MASK)
#define AIPS_PACRG_AC0_MASK                      0x70000000u
#define AIPS_PACRG_AC0_SHIFT                     28
#define AIPS_PACRG_AC0_WIDTH                     3
#define AIPS_PACRG_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_AC0_SHIFT))&AIPS_PACRG_AC0_MASK)
#define AIPS_PACRG_RO0_MASK                      0x80000000u
#define AIPS_PACRG_RO0_SHIFT                     31
#define AIPS_PACRG_RO0_WIDTH                     1
#define AIPS_PACRG_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRG_RO0_SHIFT))&AIPS_PACRG_RO0_MASK)
/* PACRH Bit Fields */
#define AIPS_PACRH_AC7_MASK                      0x7u
#define AIPS_PACRH_AC7_SHIFT                     0
#define AIPS_PACRH_AC7_WIDTH                     3
#define AIPS_PACRH_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_AC7_SHIFT))&AIPS_PACRH_AC7_MASK)
#define AIPS_PACRH_RO7_MASK                      0x8u
#define AIPS_PACRH_RO7_SHIFT                     3
#define AIPS_PACRH_RO7_WIDTH                     1
#define AIPS_PACRH_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_RO7_SHIFT))&AIPS_PACRH_RO7_MASK)
#define AIPS_PACRH_AC6_MASK                      0x70u
#define AIPS_PACRH_AC6_SHIFT                     4
#define AIPS_PACRH_AC6_WIDTH                     3
#define AIPS_PACRH_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_AC6_SHIFT))&AIPS_PACRH_AC6_MASK)
#define AIPS_PACRH_RO6_MASK                      0x80u
#define AIPS_PACRH_RO6_SHIFT                     7
#define AIPS_PACRH_RO6_WIDTH                     1
#define AIPS_PACRH_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_RO6_SHIFT))&AIPS_PACRH_RO6_MASK)
#define AIPS_PACRH_AC5_MASK                      0x700u
#define AIPS_PACRH_AC5_SHIFT                     8
#define AIPS_PACRH_AC5_WIDTH                     3
#define AIPS_PACRH_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_AC5_SHIFT))&AIPS_PACRH_AC5_MASK)
#define AIPS_PACRH_RO5_MASK                      0x800u
#define AIPS_PACRH_RO5_SHIFT                     11
#define AIPS_PACRH_RO5_WIDTH                     1
#define AIPS_PACRH_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_RO5_SHIFT))&AIPS_PACRH_RO5_MASK)
#define AIPS_PACRH_AC4_MASK                      0x7000u
#define AIPS_PACRH_AC4_SHIFT                     12
#define AIPS_PACRH_AC4_WIDTH                     3
#define AIPS_PACRH_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_AC4_SHIFT))&AIPS_PACRH_AC4_MASK)
#define AIPS_PACRH_RO4_MASK                      0x8000u
#define AIPS_PACRH_RO4_SHIFT                     15
#define AIPS_PACRH_RO4_WIDTH                     1
#define AIPS_PACRH_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_RO4_SHIFT))&AIPS_PACRH_RO4_MASK)
#define AIPS_PACRH_AC3_MASK                      0x70000u
#define AIPS_PACRH_AC3_SHIFT                     16
#define AIPS_PACRH_AC3_WIDTH                     3
#define AIPS_PACRH_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_AC3_SHIFT))&AIPS_PACRH_AC3_MASK)
#define AIPS_PACRH_RO3_MASK                      0x80000u
#define AIPS_PACRH_RO3_SHIFT                     19
#define AIPS_PACRH_RO3_WIDTH                     1
#define AIPS_PACRH_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_RO3_SHIFT))&AIPS_PACRH_RO3_MASK)
#define AIPS_PACRH_AC2_MASK                      0x700000u
#define AIPS_PACRH_AC2_SHIFT                     20
#define AIPS_PACRH_AC2_WIDTH                     3
#define AIPS_PACRH_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_AC2_SHIFT))&AIPS_PACRH_AC2_MASK)
#define AIPS_PACRH_RO2_MASK                      0x800000u
#define AIPS_PACRH_RO2_SHIFT                     23
#define AIPS_PACRH_RO2_WIDTH                     1
#define AIPS_PACRH_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_RO2_SHIFT))&AIPS_PACRH_RO2_MASK)
#define AIPS_PACRH_AC1_MASK                      0x7000000u
#define AIPS_PACRH_AC1_SHIFT                     24
#define AIPS_PACRH_AC1_WIDTH                     3
#define AIPS_PACRH_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_AC1_SHIFT))&AIPS_PACRH_AC1_MASK)
#define AIPS_PACRH_RO1_MASK                      0x8000000u
#define AIPS_PACRH_RO1_SHIFT                     27
#define AIPS_PACRH_RO1_WIDTH                     1
#define AIPS_PACRH_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_RO1_SHIFT))&AIPS_PACRH_RO1_MASK)
#define AIPS_PACRH_AC0_MASK                      0x70000000u
#define AIPS_PACRH_AC0_SHIFT                     28
#define AIPS_PACRH_AC0_WIDTH                     3
#define AIPS_PACRH_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_AC0_SHIFT))&AIPS_PACRH_AC0_MASK)
#define AIPS_PACRH_RO0_MASK                      0x80000000u
#define AIPS_PACRH_RO0_SHIFT                     31
#define AIPS_PACRH_RO0_WIDTH                     1
#define AIPS_PACRH_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRH_RO0_SHIFT))&AIPS_PACRH_RO0_MASK)
/* PACRI Bit Fields */
#define AIPS_PACRI_AC7_MASK                      0x7u
#define AIPS_PACRI_AC7_SHIFT                     0
#define AIPS_PACRI_AC7_WIDTH                     3
#define AIPS_PACRI_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_AC7_SHIFT))&AIPS_PACRI_AC7_MASK)
#define AIPS_PACRI_RO7_MASK                      0x8u
#define AIPS_PACRI_RO7_SHIFT                     3
#define AIPS_PACRI_RO7_WIDTH                     1
#define AIPS_PACRI_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_RO7_SHIFT))&AIPS_PACRI_RO7_MASK)
#define AIPS_PACRI_AC6_MASK                      0x70u
#define AIPS_PACRI_AC6_SHIFT                     4
#define AIPS_PACRI_AC6_WIDTH                     3
#define AIPS_PACRI_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_AC6_SHIFT))&AIPS_PACRI_AC6_MASK)
#define AIPS_PACRI_RO6_MASK                      0x80u
#define AIPS_PACRI_RO6_SHIFT                     7
#define AIPS_PACRI_RO6_WIDTH                     1
#define AIPS_PACRI_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_RO6_SHIFT))&AIPS_PACRI_RO6_MASK)
#define AIPS_PACRI_AC5_MASK                      0x700u
#define AIPS_PACRI_AC5_SHIFT                     8
#define AIPS_PACRI_AC5_WIDTH                     3
#define AIPS_PACRI_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_AC5_SHIFT))&AIPS_PACRI_AC5_MASK)
#define AIPS_PACRI_RO5_MASK                      0x800u
#define AIPS_PACRI_RO5_SHIFT                     11
#define AIPS_PACRI_RO5_WIDTH                     1
#define AIPS_PACRI_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_RO5_SHIFT))&AIPS_PACRI_RO5_MASK)
#define AIPS_PACRI_AC4_MASK                      0x7000u
#define AIPS_PACRI_AC4_SHIFT                     12
#define AIPS_PACRI_AC4_WIDTH                     3
#define AIPS_PACRI_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_AC4_SHIFT))&AIPS_PACRI_AC4_MASK)
#define AIPS_PACRI_RO4_MASK                      0x8000u
#define AIPS_PACRI_RO4_SHIFT                     15
#define AIPS_PACRI_RO4_WIDTH                     1
#define AIPS_PACRI_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_RO4_SHIFT))&AIPS_PACRI_RO4_MASK)
#define AIPS_PACRI_AC3_MASK                      0x70000u
#define AIPS_PACRI_AC3_SHIFT                     16
#define AIPS_PACRI_AC3_WIDTH                     3
#define AIPS_PACRI_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_AC3_SHIFT))&AIPS_PACRI_AC3_MASK)
#define AIPS_PACRI_RO3_MASK                      0x80000u
#define AIPS_PACRI_RO3_SHIFT                     19
#define AIPS_PACRI_RO3_WIDTH                     1
#define AIPS_PACRI_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_RO3_SHIFT))&AIPS_PACRI_RO3_MASK)
#define AIPS_PACRI_AC2_MASK                      0x700000u
#define AIPS_PACRI_AC2_SHIFT                     20
#define AIPS_PACRI_AC2_WIDTH                     3
#define AIPS_PACRI_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_AC2_SHIFT))&AIPS_PACRI_AC2_MASK)
#define AIPS_PACRI_RO2_MASK                      0x800000u
#define AIPS_PACRI_RO2_SHIFT                     23
#define AIPS_PACRI_RO2_WIDTH                     1
#define AIPS_PACRI_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_RO2_SHIFT))&AIPS_PACRI_RO2_MASK)
#define AIPS_PACRI_AC1_MASK                      0x7000000u
#define AIPS_PACRI_AC1_SHIFT                     24
#define AIPS_PACRI_AC1_WIDTH                     3
#define AIPS_PACRI_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_AC1_SHIFT))&AIPS_PACRI_AC1_MASK)
#define AIPS_PACRI_RO1_MASK                      0x8000000u
#define AIPS_PACRI_RO1_SHIFT                     27
#define AIPS_PACRI_RO1_WIDTH                     1
#define AIPS_PACRI_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_RO1_SHIFT))&AIPS_PACRI_RO1_MASK)
#define AIPS_PACRI_AC0_MASK                      0x70000000u
#define AIPS_PACRI_AC0_SHIFT                     28
#define AIPS_PACRI_AC0_WIDTH                     3
#define AIPS_PACRI_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_AC0_SHIFT))&AIPS_PACRI_AC0_MASK)
#define AIPS_PACRI_RO0_MASK                      0x80000000u
#define AIPS_PACRI_RO0_SHIFT                     31
#define AIPS_PACRI_RO0_WIDTH                     1
#define AIPS_PACRI_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRI_RO0_SHIFT))&AIPS_PACRI_RO0_MASK)
/* PACRJ Bit Fields */
#define AIPS_PACRJ_AC7_MASK                      0x7u
#define AIPS_PACRJ_AC7_SHIFT                     0
#define AIPS_PACRJ_AC7_WIDTH                     3
#define AIPS_PACRJ_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_AC7_SHIFT))&AIPS_PACRJ_AC7_MASK)
#define AIPS_PACRJ_RO7_MASK                      0x8u
#define AIPS_PACRJ_RO7_SHIFT                     3
#define AIPS_PACRJ_RO7_WIDTH                     1
#define AIPS_PACRJ_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_RO7_SHIFT))&AIPS_PACRJ_RO7_MASK)
#define AIPS_PACRJ_AC6_MASK                      0x70u
#define AIPS_PACRJ_AC6_SHIFT                     4
#define AIPS_PACRJ_AC6_WIDTH                     3
#define AIPS_PACRJ_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_AC6_SHIFT))&AIPS_PACRJ_AC6_MASK)
#define AIPS_PACRJ_RO6_MASK                      0x80u
#define AIPS_PACRJ_RO6_SHIFT                     7
#define AIPS_PACRJ_RO6_WIDTH                     1
#define AIPS_PACRJ_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_RO6_SHIFT))&AIPS_PACRJ_RO6_MASK)
#define AIPS_PACRJ_AC5_MASK                      0x700u
#define AIPS_PACRJ_AC5_SHIFT                     8
#define AIPS_PACRJ_AC5_WIDTH                     3
#define AIPS_PACRJ_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_AC5_SHIFT))&AIPS_PACRJ_AC5_MASK)
#define AIPS_PACRJ_RO5_MASK                      0x800u
#define AIPS_PACRJ_RO5_SHIFT                     11
#define AIPS_PACRJ_RO5_WIDTH                     1
#define AIPS_PACRJ_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_RO5_SHIFT))&AIPS_PACRJ_RO5_MASK)
#define AIPS_PACRJ_AC4_MASK                      0x7000u
#define AIPS_PACRJ_AC4_SHIFT                     12
#define AIPS_PACRJ_AC4_WIDTH                     3
#define AIPS_PACRJ_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_AC4_SHIFT))&AIPS_PACRJ_AC4_MASK)
#define AIPS_PACRJ_RO4_MASK                      0x8000u
#define AIPS_PACRJ_RO4_SHIFT                     15
#define AIPS_PACRJ_RO4_WIDTH                     1
#define AIPS_PACRJ_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_RO4_SHIFT))&AIPS_PACRJ_RO4_MASK)
#define AIPS_PACRJ_AC3_MASK                      0x70000u
#define AIPS_PACRJ_AC3_SHIFT                     16
#define AIPS_PACRJ_AC3_WIDTH                     3
#define AIPS_PACRJ_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_AC3_SHIFT))&AIPS_PACRJ_AC3_MASK)
#define AIPS_PACRJ_RO3_MASK                      0x80000u
#define AIPS_PACRJ_RO3_SHIFT                     19
#define AIPS_PACRJ_RO3_WIDTH                     1
#define AIPS_PACRJ_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_RO3_SHIFT))&AIPS_PACRJ_RO3_MASK)
#define AIPS_PACRJ_AC2_MASK                      0x700000u
#define AIPS_PACRJ_AC2_SHIFT                     20
#define AIPS_PACRJ_AC2_WIDTH                     3
#define AIPS_PACRJ_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_AC2_SHIFT))&AIPS_PACRJ_AC2_MASK)
#define AIPS_PACRJ_RO2_MASK                      0x800000u
#define AIPS_PACRJ_RO2_SHIFT                     23
#define AIPS_PACRJ_RO2_WIDTH                     1
#define AIPS_PACRJ_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_RO2_SHIFT))&AIPS_PACRJ_RO2_MASK)
#define AIPS_PACRJ_AC1_MASK                      0x7000000u
#define AIPS_PACRJ_AC1_SHIFT                     24
#define AIPS_PACRJ_AC1_WIDTH                     3
#define AIPS_PACRJ_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_AC1_SHIFT))&AIPS_PACRJ_AC1_MASK)
#define AIPS_PACRJ_RO1_MASK                      0x8000000u
#define AIPS_PACRJ_RO1_SHIFT                     27
#define AIPS_PACRJ_RO1_WIDTH                     1
#define AIPS_PACRJ_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_RO1_SHIFT))&AIPS_PACRJ_RO1_MASK)
#define AIPS_PACRJ_AC0_MASK                      0x70000000u
#define AIPS_PACRJ_AC0_SHIFT                     28
#define AIPS_PACRJ_AC0_WIDTH                     3
#define AIPS_PACRJ_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_AC0_SHIFT))&AIPS_PACRJ_AC0_MASK)
#define AIPS_PACRJ_RO0_MASK                      0x80000000u
#define AIPS_PACRJ_RO0_SHIFT                     31
#define AIPS_PACRJ_RO0_WIDTH                     1
#define AIPS_PACRJ_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRJ_RO0_SHIFT))&AIPS_PACRJ_RO0_MASK)
/* PACRK Bit Fields */
#define AIPS_PACRK_AC7_MASK                      0x7u
#define AIPS_PACRK_AC7_SHIFT                     0
#define AIPS_PACRK_AC7_WIDTH                     3
#define AIPS_PACRK_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_AC7_SHIFT))&AIPS_PACRK_AC7_MASK)
#define AIPS_PACRK_RO7_MASK                      0x8u
#define AIPS_PACRK_RO7_SHIFT                     3
#define AIPS_PACRK_RO7_WIDTH                     1
#define AIPS_PACRK_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_RO7_SHIFT))&AIPS_PACRK_RO7_MASK)
#define AIPS_PACRK_AC6_MASK                      0x70u
#define AIPS_PACRK_AC6_SHIFT                     4
#define AIPS_PACRK_AC6_WIDTH                     3
#define AIPS_PACRK_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_AC6_SHIFT))&AIPS_PACRK_AC6_MASK)
#define AIPS_PACRK_RO6_MASK                      0x80u
#define AIPS_PACRK_RO6_SHIFT                     7
#define AIPS_PACRK_RO6_WIDTH                     1
#define AIPS_PACRK_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_RO6_SHIFT))&AIPS_PACRK_RO6_MASK)
#define AIPS_PACRK_AC5_MASK                      0x700u
#define AIPS_PACRK_AC5_SHIFT                     8
#define AIPS_PACRK_AC5_WIDTH                     3
#define AIPS_PACRK_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_AC5_SHIFT))&AIPS_PACRK_AC5_MASK)
#define AIPS_PACRK_RO5_MASK                      0x800u
#define AIPS_PACRK_RO5_SHIFT                     11
#define AIPS_PACRK_RO5_WIDTH                     1
#define AIPS_PACRK_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_RO5_SHIFT))&AIPS_PACRK_RO5_MASK)
#define AIPS_PACRK_AC4_MASK                      0x7000u
#define AIPS_PACRK_AC4_SHIFT                     12
#define AIPS_PACRK_AC4_WIDTH                     3
#define AIPS_PACRK_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_AC4_SHIFT))&AIPS_PACRK_AC4_MASK)
#define AIPS_PACRK_RO4_MASK                      0x8000u
#define AIPS_PACRK_RO4_SHIFT                     15
#define AIPS_PACRK_RO4_WIDTH                     1
#define AIPS_PACRK_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_RO4_SHIFT))&AIPS_PACRK_RO4_MASK)
#define AIPS_PACRK_AC3_MASK                      0x70000u
#define AIPS_PACRK_AC3_SHIFT                     16
#define AIPS_PACRK_AC3_WIDTH                     3
#define AIPS_PACRK_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_AC3_SHIFT))&AIPS_PACRK_AC3_MASK)
#define AIPS_PACRK_RO3_MASK                      0x80000u
#define AIPS_PACRK_RO3_SHIFT                     19
#define AIPS_PACRK_RO3_WIDTH                     1
#define AIPS_PACRK_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_RO3_SHIFT))&AIPS_PACRK_RO3_MASK)
#define AIPS_PACRK_AC2_MASK                      0x700000u
#define AIPS_PACRK_AC2_SHIFT                     20
#define AIPS_PACRK_AC2_WIDTH                     3
#define AIPS_PACRK_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_AC2_SHIFT))&AIPS_PACRK_AC2_MASK)
#define AIPS_PACRK_RO2_MASK                      0x800000u
#define AIPS_PACRK_RO2_SHIFT                     23
#define AIPS_PACRK_RO2_WIDTH                     1
#define AIPS_PACRK_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_RO2_SHIFT))&AIPS_PACRK_RO2_MASK)
#define AIPS_PACRK_AC1_MASK                      0x7000000u
#define AIPS_PACRK_AC1_SHIFT                     24
#define AIPS_PACRK_AC1_WIDTH                     3
#define AIPS_PACRK_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_AC1_SHIFT))&AIPS_PACRK_AC1_MASK)
#define AIPS_PACRK_RO1_MASK                      0x8000000u
#define AIPS_PACRK_RO1_SHIFT                     27
#define AIPS_PACRK_RO1_WIDTH                     1
#define AIPS_PACRK_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_RO1_SHIFT))&AIPS_PACRK_RO1_MASK)
#define AIPS_PACRK_AC0_MASK                      0x70000000u
#define AIPS_PACRK_AC0_SHIFT                     28
#define AIPS_PACRK_AC0_WIDTH                     3
#define AIPS_PACRK_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_AC0_SHIFT))&AIPS_PACRK_AC0_MASK)
#define AIPS_PACRK_RO0_MASK                      0x80000000u
#define AIPS_PACRK_RO0_SHIFT                     31
#define AIPS_PACRK_RO0_WIDTH                     1
#define AIPS_PACRK_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRK_RO0_SHIFT))&AIPS_PACRK_RO0_MASK)
/* PACRL Bit Fields */
#define AIPS_PACRL_AC7_MASK                      0x7u
#define AIPS_PACRL_AC7_SHIFT                     0
#define AIPS_PACRL_AC7_WIDTH                     3
#define AIPS_PACRL_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_AC7_SHIFT))&AIPS_PACRL_AC7_MASK)
#define AIPS_PACRL_RO7_MASK                      0x8u
#define AIPS_PACRL_RO7_SHIFT                     3
#define AIPS_PACRL_RO7_WIDTH                     1
#define AIPS_PACRL_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_RO7_SHIFT))&AIPS_PACRL_RO7_MASK)
#define AIPS_PACRL_AC6_MASK                      0x70u
#define AIPS_PACRL_AC6_SHIFT                     4
#define AIPS_PACRL_AC6_WIDTH                     3
#define AIPS_PACRL_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_AC6_SHIFT))&AIPS_PACRL_AC6_MASK)
#define AIPS_PACRL_RO6_MASK                      0x80u
#define AIPS_PACRL_RO6_SHIFT                     7
#define AIPS_PACRL_RO6_WIDTH                     1
#define AIPS_PACRL_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_RO6_SHIFT))&AIPS_PACRL_RO6_MASK)
#define AIPS_PACRL_AC5_MASK                      0x700u
#define AIPS_PACRL_AC5_SHIFT                     8
#define AIPS_PACRL_AC5_WIDTH                     3
#define AIPS_PACRL_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_AC5_SHIFT))&AIPS_PACRL_AC5_MASK)
#define AIPS_PACRL_RO5_MASK                      0x800u
#define AIPS_PACRL_RO5_SHIFT                     11
#define AIPS_PACRL_RO5_WIDTH                     1
#define AIPS_PACRL_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_RO5_SHIFT))&AIPS_PACRL_RO5_MASK)
#define AIPS_PACRL_AC4_MASK                      0x7000u
#define AIPS_PACRL_AC4_SHIFT                     12
#define AIPS_PACRL_AC4_WIDTH                     3
#define AIPS_PACRL_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_AC4_SHIFT))&AIPS_PACRL_AC4_MASK)
#define AIPS_PACRL_RO4_MASK                      0x8000u
#define AIPS_PACRL_RO4_SHIFT                     15
#define AIPS_PACRL_RO4_WIDTH                     1
#define AIPS_PACRL_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_RO4_SHIFT))&AIPS_PACRL_RO4_MASK)
#define AIPS_PACRL_AC3_MASK                      0x70000u
#define AIPS_PACRL_AC3_SHIFT                     16
#define AIPS_PACRL_AC3_WIDTH                     3
#define AIPS_PACRL_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_AC3_SHIFT))&AIPS_PACRL_AC3_MASK)
#define AIPS_PACRL_RO3_MASK                      0x80000u
#define AIPS_PACRL_RO3_SHIFT                     19
#define AIPS_PACRL_RO3_WIDTH                     1
#define AIPS_PACRL_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_RO3_SHIFT))&AIPS_PACRL_RO3_MASK)
#define AIPS_PACRL_AC2_MASK                      0x700000u
#define AIPS_PACRL_AC2_SHIFT                     20
#define AIPS_PACRL_AC2_WIDTH                     3
#define AIPS_PACRL_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_AC2_SHIFT))&AIPS_PACRL_AC2_MASK)
#define AIPS_PACRL_RO2_MASK                      0x800000u
#define AIPS_PACRL_RO2_SHIFT                     23
#define AIPS_PACRL_RO2_WIDTH                     1
#define AIPS_PACRL_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_RO2_SHIFT))&AIPS_PACRL_RO2_MASK)
#define AIPS_PACRL_AC1_MASK                      0x7000000u
#define AIPS_PACRL_AC1_SHIFT                     24
#define AIPS_PACRL_AC1_WIDTH                     3
#define AIPS_PACRL_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_AC1_SHIFT))&AIPS_PACRL_AC1_MASK)
#define AIPS_PACRL_RO1_MASK                      0x8000000u
#define AIPS_PACRL_RO1_SHIFT                     27
#define AIPS_PACRL_RO1_WIDTH                     1
#define AIPS_PACRL_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_RO1_SHIFT))&AIPS_PACRL_RO1_MASK)
#define AIPS_PACRL_AC0_MASK                      0x70000000u
#define AIPS_PACRL_AC0_SHIFT                     28
#define AIPS_PACRL_AC0_WIDTH                     3
#define AIPS_PACRL_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_AC0_SHIFT))&AIPS_PACRL_AC0_MASK)
#define AIPS_PACRL_RO0_MASK                      0x80000000u
#define AIPS_PACRL_RO0_SHIFT                     31
#define AIPS_PACRL_RO0_WIDTH                     1
#define AIPS_PACRL_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRL_RO0_SHIFT))&AIPS_PACRL_RO0_MASK)
/* PACRM Bit Fields */
#define AIPS_PACRM_AC7_MASK                      0x7u
#define AIPS_PACRM_AC7_SHIFT                     0
#define AIPS_PACRM_AC7_WIDTH                     3
#define AIPS_PACRM_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_AC7_SHIFT))&AIPS_PACRM_AC7_MASK)
#define AIPS_PACRM_RO7_MASK                      0x8u
#define AIPS_PACRM_RO7_SHIFT                     3
#define AIPS_PACRM_RO7_WIDTH                     1
#define AIPS_PACRM_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_RO7_SHIFT))&AIPS_PACRM_RO7_MASK)
#define AIPS_PACRM_AC6_MASK                      0x70u
#define AIPS_PACRM_AC6_SHIFT                     4
#define AIPS_PACRM_AC6_WIDTH                     3
#define AIPS_PACRM_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_AC6_SHIFT))&AIPS_PACRM_AC6_MASK)
#define AIPS_PACRM_RO6_MASK                      0x80u
#define AIPS_PACRM_RO6_SHIFT                     7
#define AIPS_PACRM_RO6_WIDTH                     1
#define AIPS_PACRM_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_RO6_SHIFT))&AIPS_PACRM_RO6_MASK)
#define AIPS_PACRM_AC5_MASK                      0x700u
#define AIPS_PACRM_AC5_SHIFT                     8
#define AIPS_PACRM_AC5_WIDTH                     3
#define AIPS_PACRM_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_AC5_SHIFT))&AIPS_PACRM_AC5_MASK)
#define AIPS_PACRM_RO5_MASK                      0x800u
#define AIPS_PACRM_RO5_SHIFT                     11
#define AIPS_PACRM_RO5_WIDTH                     1
#define AIPS_PACRM_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_RO5_SHIFT))&AIPS_PACRM_RO5_MASK)
#define AIPS_PACRM_AC4_MASK                      0x7000u
#define AIPS_PACRM_AC4_SHIFT                     12
#define AIPS_PACRM_AC4_WIDTH                     3
#define AIPS_PACRM_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_AC4_SHIFT))&AIPS_PACRM_AC4_MASK)
#define AIPS_PACRM_RO4_MASK                      0x8000u
#define AIPS_PACRM_RO4_SHIFT                     15
#define AIPS_PACRM_RO4_WIDTH                     1
#define AIPS_PACRM_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_RO4_SHIFT))&AIPS_PACRM_RO4_MASK)
#define AIPS_PACRM_AC3_MASK                      0x70000u
#define AIPS_PACRM_AC3_SHIFT                     16
#define AIPS_PACRM_AC3_WIDTH                     3
#define AIPS_PACRM_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_AC3_SHIFT))&AIPS_PACRM_AC3_MASK)
#define AIPS_PACRM_RO3_MASK                      0x80000u
#define AIPS_PACRM_RO3_SHIFT                     19
#define AIPS_PACRM_RO3_WIDTH                     1
#define AIPS_PACRM_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_RO3_SHIFT))&AIPS_PACRM_RO3_MASK)
#define AIPS_PACRM_AC2_MASK                      0x700000u
#define AIPS_PACRM_AC2_SHIFT                     20
#define AIPS_PACRM_AC2_WIDTH                     3
#define AIPS_PACRM_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_AC2_SHIFT))&AIPS_PACRM_AC2_MASK)
#define AIPS_PACRM_RO2_MASK                      0x800000u
#define AIPS_PACRM_RO2_SHIFT                     23
#define AIPS_PACRM_RO2_WIDTH                     1
#define AIPS_PACRM_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_RO2_SHIFT))&AIPS_PACRM_RO2_MASK)
#define AIPS_PACRM_AC1_MASK                      0x7000000u
#define AIPS_PACRM_AC1_SHIFT                     24
#define AIPS_PACRM_AC1_WIDTH                     3
#define AIPS_PACRM_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_AC1_SHIFT))&AIPS_PACRM_AC1_MASK)
#define AIPS_PACRM_RO1_MASK                      0x8000000u
#define AIPS_PACRM_RO1_SHIFT                     27
#define AIPS_PACRM_RO1_WIDTH                     1
#define AIPS_PACRM_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_RO1_SHIFT))&AIPS_PACRM_RO1_MASK)
#define AIPS_PACRM_AC0_MASK                      0x70000000u
#define AIPS_PACRM_AC0_SHIFT                     28
#define AIPS_PACRM_AC0_WIDTH                     3
#define AIPS_PACRM_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_AC0_SHIFT))&AIPS_PACRM_AC0_MASK)
#define AIPS_PACRM_RO0_MASK                      0x80000000u
#define AIPS_PACRM_RO0_SHIFT                     31
#define AIPS_PACRM_RO0_WIDTH                     1
#define AIPS_PACRM_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRM_RO0_SHIFT))&AIPS_PACRM_RO0_MASK)
/* PACRN Bit Fields */
#define AIPS_PACRN_AC7_MASK                      0x7u
#define AIPS_PACRN_AC7_SHIFT                     0
#define AIPS_PACRN_AC7_WIDTH                     3
#define AIPS_PACRN_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_AC7_SHIFT))&AIPS_PACRN_AC7_MASK)
#define AIPS_PACRN_RO7_MASK                      0x8u
#define AIPS_PACRN_RO7_SHIFT                     3
#define AIPS_PACRN_RO7_WIDTH                     1
#define AIPS_PACRN_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_RO7_SHIFT))&AIPS_PACRN_RO7_MASK)
#define AIPS_PACRN_AC6_MASK                      0x70u
#define AIPS_PACRN_AC6_SHIFT                     4
#define AIPS_PACRN_AC6_WIDTH                     3
#define AIPS_PACRN_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_AC6_SHIFT))&AIPS_PACRN_AC6_MASK)
#define AIPS_PACRN_RO6_MASK                      0x80u
#define AIPS_PACRN_RO6_SHIFT                     7
#define AIPS_PACRN_RO6_WIDTH                     1
#define AIPS_PACRN_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_RO6_SHIFT))&AIPS_PACRN_RO6_MASK)
#define AIPS_PACRN_AC5_MASK                      0x700u
#define AIPS_PACRN_AC5_SHIFT                     8
#define AIPS_PACRN_AC5_WIDTH                     3
#define AIPS_PACRN_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_AC5_SHIFT))&AIPS_PACRN_AC5_MASK)
#define AIPS_PACRN_RO5_MASK                      0x800u
#define AIPS_PACRN_RO5_SHIFT                     11
#define AIPS_PACRN_RO5_WIDTH                     1
#define AIPS_PACRN_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_RO5_SHIFT))&AIPS_PACRN_RO5_MASK)
#define AIPS_PACRN_AC4_MASK                      0x7000u
#define AIPS_PACRN_AC4_SHIFT                     12
#define AIPS_PACRN_AC4_WIDTH                     3
#define AIPS_PACRN_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_AC4_SHIFT))&AIPS_PACRN_AC4_MASK)
#define AIPS_PACRN_RO4_MASK                      0x8000u
#define AIPS_PACRN_RO4_SHIFT                     15
#define AIPS_PACRN_RO4_WIDTH                     1
#define AIPS_PACRN_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_RO4_SHIFT))&AIPS_PACRN_RO4_MASK)
#define AIPS_PACRN_AC3_MASK                      0x70000u
#define AIPS_PACRN_AC3_SHIFT                     16
#define AIPS_PACRN_AC3_WIDTH                     3
#define AIPS_PACRN_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_AC3_SHIFT))&AIPS_PACRN_AC3_MASK)
#define AIPS_PACRN_RO3_MASK                      0x80000u
#define AIPS_PACRN_RO3_SHIFT                     19
#define AIPS_PACRN_RO3_WIDTH                     1
#define AIPS_PACRN_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_RO3_SHIFT))&AIPS_PACRN_RO3_MASK)
#define AIPS_PACRN_AC2_MASK                      0x700000u
#define AIPS_PACRN_AC2_SHIFT                     20
#define AIPS_PACRN_AC2_WIDTH                     3
#define AIPS_PACRN_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_AC2_SHIFT))&AIPS_PACRN_AC2_MASK)
#define AIPS_PACRN_RO2_MASK                      0x800000u
#define AIPS_PACRN_RO2_SHIFT                     23
#define AIPS_PACRN_RO2_WIDTH                     1
#define AIPS_PACRN_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_RO2_SHIFT))&AIPS_PACRN_RO2_MASK)
#define AIPS_PACRN_AC1_MASK                      0x7000000u
#define AIPS_PACRN_AC1_SHIFT                     24
#define AIPS_PACRN_AC1_WIDTH                     3
#define AIPS_PACRN_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_AC1_SHIFT))&AIPS_PACRN_AC1_MASK)
#define AIPS_PACRN_RO1_MASK                      0x8000000u
#define AIPS_PACRN_RO1_SHIFT                     27
#define AIPS_PACRN_RO1_WIDTH                     1
#define AIPS_PACRN_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_RO1_SHIFT))&AIPS_PACRN_RO1_MASK)
#define AIPS_PACRN_AC0_MASK                      0x70000000u
#define AIPS_PACRN_AC0_SHIFT                     28
#define AIPS_PACRN_AC0_WIDTH                     3
#define AIPS_PACRN_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_AC0_SHIFT))&AIPS_PACRN_AC0_MASK)
#define AIPS_PACRN_RO0_MASK                      0x80000000u
#define AIPS_PACRN_RO0_SHIFT                     31
#define AIPS_PACRN_RO0_WIDTH                     1
#define AIPS_PACRN_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRN_RO0_SHIFT))&AIPS_PACRN_RO0_MASK)
/* PACRO Bit Fields */
#define AIPS_PACRO_AC7_MASK                      0x7u
#define AIPS_PACRO_AC7_SHIFT                     0
#define AIPS_PACRO_AC7_WIDTH                     3
#define AIPS_PACRO_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_AC7_SHIFT))&AIPS_PACRO_AC7_MASK)
#define AIPS_PACRO_RO7_MASK                      0x8u
#define AIPS_PACRO_RO7_SHIFT                     3
#define AIPS_PACRO_RO7_WIDTH                     1
#define AIPS_PACRO_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_RO7_SHIFT))&AIPS_PACRO_RO7_MASK)
#define AIPS_PACRO_AC6_MASK                      0x70u
#define AIPS_PACRO_AC6_SHIFT                     4
#define AIPS_PACRO_AC6_WIDTH                     3
#define AIPS_PACRO_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_AC6_SHIFT))&AIPS_PACRO_AC6_MASK)
#define AIPS_PACRO_RO6_MASK                      0x80u
#define AIPS_PACRO_RO6_SHIFT                     7
#define AIPS_PACRO_RO6_WIDTH                     1
#define AIPS_PACRO_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_RO6_SHIFT))&AIPS_PACRO_RO6_MASK)
#define AIPS_PACRO_AC5_MASK                      0x700u
#define AIPS_PACRO_AC5_SHIFT                     8
#define AIPS_PACRO_AC5_WIDTH                     3
#define AIPS_PACRO_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_AC5_SHIFT))&AIPS_PACRO_AC5_MASK)
#define AIPS_PACRO_RO5_MASK                      0x800u
#define AIPS_PACRO_RO5_SHIFT                     11
#define AIPS_PACRO_RO5_WIDTH                     1
#define AIPS_PACRO_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_RO5_SHIFT))&AIPS_PACRO_RO5_MASK)
#define AIPS_PACRO_AC4_MASK                      0x7000u
#define AIPS_PACRO_AC4_SHIFT                     12
#define AIPS_PACRO_AC4_WIDTH                     3
#define AIPS_PACRO_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_AC4_SHIFT))&AIPS_PACRO_AC4_MASK)
#define AIPS_PACRO_RO4_MASK                      0x8000u
#define AIPS_PACRO_RO4_SHIFT                     15
#define AIPS_PACRO_RO4_WIDTH                     1
#define AIPS_PACRO_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_RO4_SHIFT))&AIPS_PACRO_RO4_MASK)
#define AIPS_PACRO_AC3_MASK                      0x70000u
#define AIPS_PACRO_AC3_SHIFT                     16
#define AIPS_PACRO_AC3_WIDTH                     3
#define AIPS_PACRO_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_AC3_SHIFT))&AIPS_PACRO_AC3_MASK)
#define AIPS_PACRO_RO3_MASK                      0x80000u
#define AIPS_PACRO_RO3_SHIFT                     19
#define AIPS_PACRO_RO3_WIDTH                     1
#define AIPS_PACRO_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_RO3_SHIFT))&AIPS_PACRO_RO3_MASK)
#define AIPS_PACRO_AC2_MASK                      0x700000u
#define AIPS_PACRO_AC2_SHIFT                     20
#define AIPS_PACRO_AC2_WIDTH                     3
#define AIPS_PACRO_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_AC2_SHIFT))&AIPS_PACRO_AC2_MASK)
#define AIPS_PACRO_RO2_MASK                      0x800000u
#define AIPS_PACRO_RO2_SHIFT                     23
#define AIPS_PACRO_RO2_WIDTH                     1
#define AIPS_PACRO_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_RO2_SHIFT))&AIPS_PACRO_RO2_MASK)
#define AIPS_PACRO_AC1_MASK                      0x7000000u
#define AIPS_PACRO_AC1_SHIFT                     24
#define AIPS_PACRO_AC1_WIDTH                     3
#define AIPS_PACRO_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_AC1_SHIFT))&AIPS_PACRO_AC1_MASK)
#define AIPS_PACRO_RO1_MASK                      0x8000000u
#define AIPS_PACRO_RO1_SHIFT                     27
#define AIPS_PACRO_RO1_WIDTH                     1
#define AIPS_PACRO_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_RO1_SHIFT))&AIPS_PACRO_RO1_MASK)
#define AIPS_PACRO_AC0_MASK                      0x70000000u
#define AIPS_PACRO_AC0_SHIFT                     28
#define AIPS_PACRO_AC0_WIDTH                     3
#define AIPS_PACRO_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_AC0_SHIFT))&AIPS_PACRO_AC0_MASK)
#define AIPS_PACRO_RO0_MASK                      0x80000000u
#define AIPS_PACRO_RO0_SHIFT                     31
#define AIPS_PACRO_RO0_WIDTH                     1
#define AIPS_PACRO_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRO_RO0_SHIFT))&AIPS_PACRO_RO0_MASK)
/* PACRP Bit Fields */
#define AIPS_PACRP_AC7_MASK                      0x7u
#define AIPS_PACRP_AC7_SHIFT                     0
#define AIPS_PACRP_AC7_WIDTH                     3
#define AIPS_PACRP_AC7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_AC7_SHIFT))&AIPS_PACRP_AC7_MASK)
#define AIPS_PACRP_RO7_MASK                      0x8u
#define AIPS_PACRP_RO7_SHIFT                     3
#define AIPS_PACRP_RO7_WIDTH                     1
#define AIPS_PACRP_RO7(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_RO7_SHIFT))&AIPS_PACRP_RO7_MASK)
#define AIPS_PACRP_AC6_MASK                      0x70u
#define AIPS_PACRP_AC6_SHIFT                     4
#define AIPS_PACRP_AC6_WIDTH                     3
#define AIPS_PACRP_AC6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_AC6_SHIFT))&AIPS_PACRP_AC6_MASK)
#define AIPS_PACRP_RO6_MASK                      0x80u
#define AIPS_PACRP_RO6_SHIFT                     7
#define AIPS_PACRP_RO6_WIDTH                     1
#define AIPS_PACRP_RO6(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_RO6_SHIFT))&AIPS_PACRP_RO6_MASK)
#define AIPS_PACRP_AC5_MASK                      0x700u
#define AIPS_PACRP_AC5_SHIFT                     8
#define AIPS_PACRP_AC5_WIDTH                     3
#define AIPS_PACRP_AC5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_AC5_SHIFT))&AIPS_PACRP_AC5_MASK)
#define AIPS_PACRP_RO5_MASK                      0x800u
#define AIPS_PACRP_RO5_SHIFT                     11
#define AIPS_PACRP_RO5_WIDTH                     1
#define AIPS_PACRP_RO5(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_RO5_SHIFT))&AIPS_PACRP_RO5_MASK)
#define AIPS_PACRP_AC4_MASK                      0x7000u
#define AIPS_PACRP_AC4_SHIFT                     12
#define AIPS_PACRP_AC4_WIDTH                     3
#define AIPS_PACRP_AC4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_AC4_SHIFT))&AIPS_PACRP_AC4_MASK)
#define AIPS_PACRP_RO4_MASK                      0x8000u
#define AIPS_PACRP_RO4_SHIFT                     15
#define AIPS_PACRP_RO4_WIDTH                     1
#define AIPS_PACRP_RO4(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_RO4_SHIFT))&AIPS_PACRP_RO4_MASK)
#define AIPS_PACRP_AC3_MASK                      0x70000u
#define AIPS_PACRP_AC3_SHIFT                     16
#define AIPS_PACRP_AC3_WIDTH                     3
#define AIPS_PACRP_AC3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_AC3_SHIFT))&AIPS_PACRP_AC3_MASK)
#define AIPS_PACRP_RO3_MASK                      0x80000u
#define AIPS_PACRP_RO3_SHIFT                     19
#define AIPS_PACRP_RO3_WIDTH                     1
#define AIPS_PACRP_RO3(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_RO3_SHIFT))&AIPS_PACRP_RO3_MASK)
#define AIPS_PACRP_AC2_MASK                      0x700000u
#define AIPS_PACRP_AC2_SHIFT                     20
#define AIPS_PACRP_AC2_WIDTH                     3
#define AIPS_PACRP_AC2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_AC2_SHIFT))&AIPS_PACRP_AC2_MASK)
#define AIPS_PACRP_RO2_MASK                      0x800000u
#define AIPS_PACRP_RO2_SHIFT                     23
#define AIPS_PACRP_RO2_WIDTH                     1
#define AIPS_PACRP_RO2(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_RO2_SHIFT))&AIPS_PACRP_RO2_MASK)
#define AIPS_PACRP_AC1_MASK                      0x7000000u
#define AIPS_PACRP_AC1_SHIFT                     24
#define AIPS_PACRP_AC1_WIDTH                     3
#define AIPS_PACRP_AC1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_AC1_SHIFT))&AIPS_PACRP_AC1_MASK)
#define AIPS_PACRP_RO1_MASK                      0x8000000u
#define AIPS_PACRP_RO1_SHIFT                     27
#define AIPS_PACRP_RO1_WIDTH                     1
#define AIPS_PACRP_RO1(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_RO1_SHIFT))&AIPS_PACRP_RO1_MASK)
#define AIPS_PACRP_AC0_MASK                      0x70000000u
#define AIPS_PACRP_AC0_SHIFT                     28
#define AIPS_PACRP_AC0_WIDTH                     3
#define AIPS_PACRP_AC0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_AC0_SHIFT))&AIPS_PACRP_AC0_MASK)
#define AIPS_PACRP_RO0_MASK                      0x80000000u
#define AIPS_PACRP_RO0_SHIFT                     31
#define AIPS_PACRP_RO0_WIDTH                     1
#define AIPS_PACRP_RO0(x)                        (((uint32_t)(((uint32_t)(x))<<AIPS_PACRP_RO0_SHIFT))&AIPS_PACRP_RO0_MASK)

/*!
 * @}
 */ /* end of group AIPS_Register_Masks */


/* AIPS - Peripheral instance base addresses */
/** Peripheral AIPS base address */
#define AIPS_BASE                                (0x40000000u)
/** Peripheral AIPS base pointer */
#define AIPS                                     ((AIPS_Type *)AIPS_BASE)
#define AIPS_BASE_PTR                            (AIPS)
/** Array initializer of AIPS peripheral base addresses */
#define AIPS_BASE_ADDRS                          { AIPS_BASE }
/** Array initializer of AIPS peripheral base pointers */
#define AIPS_BASE_PTRS                           { AIPS }

/* ----------------------------------------------------------------------------
   -- AIPS - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AIPS_Register_Accessor_Macros AIPS - Register accessor macros
 * @{
 */


/* AIPS - Register instance definitions */
/* AIPS */
#define AIPS_PACRA                               AIPS_PACRA_REG(AIPS)
#define AIPS_PACRB                               AIPS_PACRB_REG(AIPS)
#define AIPS_PACRE                               AIPS_PACRE_REG(AIPS)
#define AIPS_PACRF                               AIPS_PACRF_REG(AIPS)
#define AIPS_PACRG                               AIPS_PACRG_REG(AIPS)
#define AIPS_PACRH                               AIPS_PACRH_REG(AIPS)
#define AIPS_PACRI                               AIPS_PACRI_REG(AIPS)
#define AIPS_PACRJ                               AIPS_PACRJ_REG(AIPS)
#define AIPS_PACRK                               AIPS_PACRK_REG(AIPS)
#define AIPS_PACRL                               AIPS_PACRL_REG(AIPS)
#define AIPS_PACRM                               AIPS_PACRM_REG(AIPS)
#define AIPS_PACRN                               AIPS_PACRN_REG(AIPS)
#define AIPS_PACRO                               AIPS_PACRO_REG(AIPS)
#define AIPS_PACRP                               AIPS_PACRP_REG(AIPS)

/*!
 * @}
 */ /* end of group AIPS_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group AIPS_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CAU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAU_Peripheral_Access_Layer CAU Peripheral Access Layer
 * @{
 */

/** CAU - Register Layout Typedef */
typedef struct {
  __O  uint32_t DIRECT[16];                        /**< Direct access register 0..Direct access register 15, array offset: 0x0, array step: 0x4 */
       uint8_t RESERVED_0[2048];
  __O  uint32_t LDR_CASR;                          /**< Status register - Load Register command, offset: 0x840 */
  __O  uint32_t LDR_CAA;                           /**< Accumulator register - Load Register command, offset: 0x844 */
  __O  uint32_t LDR_CA[9];                         /**< General Purpose Register 0 - Load Register command..General Purpose Register 8 - Load Register command, array offset: 0x848, array step: 0x4 */
       uint8_t RESERVED_1[20];
  __I  uint32_t STR_CASR;                          /**< Status register - Store Register command, offset: 0x880 */
  __I  uint32_t STR_CAA;                           /**< Accumulator register - Store Register command, offset: 0x884 */
  __I  uint32_t STR_CA[9];                         /**< General Purpose Register 0 - Store Register command..General Purpose Register 8 - Store Register command, array offset: 0x888, array step: 0x4 */
       uint8_t RESERVED_2[20];
  __O  uint32_t ADR_CASR;                          /**< Status register - Add Register command, offset: 0x8C0 */
  __O  uint32_t ADR_CAA;                           /**< Accumulator register - Add to register command, offset: 0x8C4 */
  __O  uint32_t ADR_CA[9];                         /**< General Purpose Register 0 - Add to register command..General Purpose Register 8 - Add to register command, array offset: 0x8C8, array step: 0x4 */
       uint8_t RESERVED_3[20];
  __O  uint32_t RADR_CASR;                         /**< Status register - Reverse and Add to Register command, offset: 0x900 */
  __O  uint32_t RADR_CAA;                          /**< Accumulator register - Reverse and Add to Register command, offset: 0x904 */
  __O  uint32_t RADR_CA[9];                        /**< General Purpose Register 0 - Reverse and Add to Register command..General Purpose Register 8 - Reverse and Add to Register command, array offset: 0x908, array step: 0x4 */
       uint8_t RESERVED_4[84];
  __O  uint32_t XOR_CASR;                          /**< Status register - Exclusive Or command, offset: 0x980 */
  __O  uint32_t XOR_CAA;                           /**< Accumulator register - Exclusive Or command, offset: 0x984 */
  __O  uint32_t XOR_CA[9];                         /**< General Purpose Register 0 - Exclusive Or command..General Purpose Register 8 - Exclusive Or command, array offset: 0x988, array step: 0x4 */
       uint8_t RESERVED_5[20];
  __O  uint32_t ROTL_CASR;                         /**< Status register - Rotate Left command, offset: 0x9C0 */
  __O  uint32_t ROTL_CAA;                          /**< Accumulator register - Rotate Left command, offset: 0x9C4 */
  __O  uint32_t ROTL_CA[9];                        /**< General Purpose Register 0 - Rotate Left command..General Purpose Register 8 - Rotate Left command, array offset: 0x9C8, array step: 0x4 */
       uint8_t RESERVED_6[276];
  __O  uint32_t AESC_CASR;                         /**< Status register - AES Column Operation command, offset: 0xB00 */
  __O  uint32_t AESC_CAA;                          /**< Accumulator register - AES Column Operation command, offset: 0xB04 */
  __O  uint32_t AESC_CA[9];                        /**< General Purpose Register 0 - AES Column Operation command..General Purpose Register 8 - AES Column Operation command, array offset: 0xB08, array step: 0x4 */
       uint8_t RESERVED_7[20];
  __O  uint32_t AESIC_CASR;                        /**< Status register - AES Inverse Column Operation command, offset: 0xB40 */
  __O  uint32_t AESIC_CAA;                         /**< Accumulator register - AES Inverse Column Operation command, offset: 0xB44 */
  __O  uint32_t AESIC_CA[9];                       /**< General Purpose Register 0 - AES Inverse Column Operation command..General Purpose Register 8 - AES Inverse Column Operation command, array offset: 0xB48, array step: 0x4 */
} CAU_Type, *CAU_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CAU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAU_Register_Accessor_Macros CAU - Register accessor macros
 * @{
 */


/* CAU - Register accessors */
#define CAU_DIRECT_REG(base,index)               ((base)->DIRECT[index])
#define CAU_DIRECT_COUNT                         16
#define CAU_LDR_CASR_REG(base)                   ((base)->LDR_CASR)
#define CAU_LDR_CAA_REG(base)                    ((base)->LDR_CAA)
#define CAU_LDR_CA_REG(base,index)               ((base)->LDR_CA[index])
#define CAU_LDR_CA_COUNT                         9
#define CAU_STR_CASR_REG(base)                   ((base)->STR_CASR)
#define CAU_STR_CAA_REG(base)                    ((base)->STR_CAA)
#define CAU_STR_CA_REG(base,index)               ((base)->STR_CA[index])
#define CAU_STR_CA_COUNT                         9
#define CAU_ADR_CASR_REG(base)                   ((base)->ADR_CASR)
#define CAU_ADR_CAA_REG(base)                    ((base)->ADR_CAA)
#define CAU_ADR_CA_REG(base,index)               ((base)->ADR_CA[index])
#define CAU_ADR_CA_COUNT                         9
#define CAU_RADR_CASR_REG(base)                  ((base)->RADR_CASR)
#define CAU_RADR_CAA_REG(base)                   ((base)->RADR_CAA)
#define CAU_RADR_CA_REG(base,index)              ((base)->RADR_CA[index])
#define CAU_RADR_CA_COUNT                        9
#define CAU_XOR_CASR_REG(base)                   ((base)->XOR_CASR)
#define CAU_XOR_CAA_REG(base)                    ((base)->XOR_CAA)
#define CAU_XOR_CA_REG(base,index)               ((base)->XOR_CA[index])
#define CAU_XOR_CA_COUNT                         9
#define CAU_ROTL_CASR_REG(base)                  ((base)->ROTL_CASR)
#define CAU_ROTL_CAA_REG(base)                   ((base)->ROTL_CAA)
#define CAU_ROTL_CA_REG(base,index)              ((base)->ROTL_CA[index])
#define CAU_ROTL_CA_COUNT                        9
#define CAU_AESC_CASR_REG(base)                  ((base)->AESC_CASR)
#define CAU_AESC_CAA_REG(base)                   ((base)->AESC_CAA)
#define CAU_AESC_CA_REG(base,index)              ((base)->AESC_CA[index])
#define CAU_AESC_CA_COUNT                        9
#define CAU_AESIC_CASR_REG(base)                 ((base)->AESIC_CASR)
#define CAU_AESIC_CAA_REG(base)                  ((base)->AESIC_CAA)
#define CAU_AESIC_CA_REG(base,index)             ((base)->AESIC_CA[index])
#define CAU_AESIC_CA_COUNT                       9

/*!
 * @}
 */ /* end of group CAU_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CAU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAU_Register_Masks CAU Register Masks
 * @{
 */

/* DIRECT Bit Fields */
#define CAU_DIRECT_CAU_DIRECT0_MASK              0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT0_SHIFT             0
#define CAU_DIRECT_CAU_DIRECT0_WIDTH             32
#define CAU_DIRECT_CAU_DIRECT0(x)                (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT0_SHIFT))&CAU_DIRECT_CAU_DIRECT0_MASK)
#define CAU_DIRECT_CAU_DIRECT1_MASK              0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT1_SHIFT             0
#define CAU_DIRECT_CAU_DIRECT1_WIDTH             32
#define CAU_DIRECT_CAU_DIRECT1(x)                (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT1_SHIFT))&CAU_DIRECT_CAU_DIRECT1_MASK)
#define CAU_DIRECT_CAU_DIRECT2_MASK              0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT2_SHIFT             0
#define CAU_DIRECT_CAU_DIRECT2_WIDTH             32
#define CAU_DIRECT_CAU_DIRECT2(x)                (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT2_SHIFT))&CAU_DIRECT_CAU_DIRECT2_MASK)
#define CAU_DIRECT_CAU_DIRECT3_MASK              0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT3_SHIFT             0
#define CAU_DIRECT_CAU_DIRECT3_WIDTH             32
#define CAU_DIRECT_CAU_DIRECT3(x)                (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT3_SHIFT))&CAU_DIRECT_CAU_DIRECT3_MASK)
#define CAU_DIRECT_CAU_DIRECT4_MASK              0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT4_SHIFT             0
#define CAU_DIRECT_CAU_DIRECT4_WIDTH             32
#define CAU_DIRECT_CAU_DIRECT4(x)                (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT4_SHIFT))&CAU_DIRECT_CAU_DIRECT4_MASK)
#define CAU_DIRECT_CAU_DIRECT5_MASK              0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT5_SHIFT             0
#define CAU_DIRECT_CAU_DIRECT5_WIDTH             32
#define CAU_DIRECT_CAU_DIRECT5(x)                (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT5_SHIFT))&CAU_DIRECT_CAU_DIRECT5_MASK)
#define CAU_DIRECT_CAU_DIRECT6_MASK              0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT6_SHIFT             0
#define CAU_DIRECT_CAU_DIRECT6_WIDTH             32
#define CAU_DIRECT_CAU_DIRECT6(x)                (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT6_SHIFT))&CAU_DIRECT_CAU_DIRECT6_MASK)
#define CAU_DIRECT_CAU_DIRECT7_MASK              0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT7_SHIFT             0
#define CAU_DIRECT_CAU_DIRECT7_WIDTH             32
#define CAU_DIRECT_CAU_DIRECT7(x)                (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT7_SHIFT))&CAU_DIRECT_CAU_DIRECT7_MASK)
#define CAU_DIRECT_CAU_DIRECT8_MASK              0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT8_SHIFT             0
#define CAU_DIRECT_CAU_DIRECT8_WIDTH             32
#define CAU_DIRECT_CAU_DIRECT8(x)                (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT8_SHIFT))&CAU_DIRECT_CAU_DIRECT8_MASK)
#define CAU_DIRECT_CAU_DIRECT9_MASK              0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT9_SHIFT             0
#define CAU_DIRECT_CAU_DIRECT9_WIDTH             32
#define CAU_DIRECT_CAU_DIRECT9(x)                (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT9_SHIFT))&CAU_DIRECT_CAU_DIRECT9_MASK)
#define CAU_DIRECT_CAU_DIRECT10_MASK             0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT10_SHIFT            0
#define CAU_DIRECT_CAU_DIRECT10_WIDTH            32
#define CAU_DIRECT_CAU_DIRECT10(x)               (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT10_SHIFT))&CAU_DIRECT_CAU_DIRECT10_MASK)
#define CAU_DIRECT_CAU_DIRECT11_MASK             0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT11_SHIFT            0
#define CAU_DIRECT_CAU_DIRECT11_WIDTH            32
#define CAU_DIRECT_CAU_DIRECT11(x)               (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT11_SHIFT))&CAU_DIRECT_CAU_DIRECT11_MASK)
#define CAU_DIRECT_CAU_DIRECT12_MASK             0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT12_SHIFT            0
#define CAU_DIRECT_CAU_DIRECT12_WIDTH            32
#define CAU_DIRECT_CAU_DIRECT12(x)               (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT12_SHIFT))&CAU_DIRECT_CAU_DIRECT12_MASK)
#define CAU_DIRECT_CAU_DIRECT13_MASK             0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT13_SHIFT            0
#define CAU_DIRECT_CAU_DIRECT13_WIDTH            32
#define CAU_DIRECT_CAU_DIRECT13(x)               (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT13_SHIFT))&CAU_DIRECT_CAU_DIRECT13_MASK)
#define CAU_DIRECT_CAU_DIRECT14_MASK             0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT14_SHIFT            0
#define CAU_DIRECT_CAU_DIRECT14_WIDTH            32
#define CAU_DIRECT_CAU_DIRECT14(x)               (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT14_SHIFT))&CAU_DIRECT_CAU_DIRECT14_MASK)
#define CAU_DIRECT_CAU_DIRECT15_MASK             0xFFFFFFFFu
#define CAU_DIRECT_CAU_DIRECT15_SHIFT            0
#define CAU_DIRECT_CAU_DIRECT15_WIDTH            32
#define CAU_DIRECT_CAU_DIRECT15(x)               (((uint32_t)(((uint32_t)(x))<<CAU_DIRECT_CAU_DIRECT15_SHIFT))&CAU_DIRECT_CAU_DIRECT15_MASK)
/* LDR_CASR Bit Fields */
#define CAU_LDR_CASR_IC_MASK                     0x1u
#define CAU_LDR_CASR_IC_SHIFT                    0
#define CAU_LDR_CASR_IC_WIDTH                    1
#define CAU_LDR_CASR_IC(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_LDR_CASR_IC_SHIFT))&CAU_LDR_CASR_IC_MASK)
#define CAU_LDR_CASR_DPE_MASK                    0x2u
#define CAU_LDR_CASR_DPE_SHIFT                   1
#define CAU_LDR_CASR_DPE_WIDTH                   1
#define CAU_LDR_CASR_DPE(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_LDR_CASR_DPE_SHIFT))&CAU_LDR_CASR_DPE_MASK)
#define CAU_LDR_CASR_VER_MASK                    0xF0000000u
#define CAU_LDR_CASR_VER_SHIFT                   28
#define CAU_LDR_CASR_VER_WIDTH                   4
#define CAU_LDR_CASR_VER(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_LDR_CASR_VER_SHIFT))&CAU_LDR_CASR_VER_MASK)
/* LDR_CAA Bit Fields */
#define CAU_LDR_CAA_ACC_MASK                     0xFFFFFFFFu
#define CAU_LDR_CAA_ACC_SHIFT                    0
#define CAU_LDR_CAA_ACC_WIDTH                    32
#define CAU_LDR_CAA_ACC(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_LDR_CAA_ACC_SHIFT))&CAU_LDR_CAA_ACC_MASK)
/* LDR_CA Bit Fields */
#define CAU_LDR_CA_CA0_MASK                      0xFFFFFFFFu
#define CAU_LDR_CA_CA0_SHIFT                     0
#define CAU_LDR_CA_CA0_WIDTH                     32
#define CAU_LDR_CA_CA0(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_LDR_CA_CA0_SHIFT))&CAU_LDR_CA_CA0_MASK)
#define CAU_LDR_CA_CA1_MASK                      0xFFFFFFFFu
#define CAU_LDR_CA_CA1_SHIFT                     0
#define CAU_LDR_CA_CA1_WIDTH                     32
#define CAU_LDR_CA_CA1(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_LDR_CA_CA1_SHIFT))&CAU_LDR_CA_CA1_MASK)
#define CAU_LDR_CA_CA2_MASK                      0xFFFFFFFFu
#define CAU_LDR_CA_CA2_SHIFT                     0
#define CAU_LDR_CA_CA2_WIDTH                     32
#define CAU_LDR_CA_CA2(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_LDR_CA_CA2_SHIFT))&CAU_LDR_CA_CA2_MASK)
#define CAU_LDR_CA_CA3_MASK                      0xFFFFFFFFu
#define CAU_LDR_CA_CA3_SHIFT                     0
#define CAU_LDR_CA_CA3_WIDTH                     32
#define CAU_LDR_CA_CA3(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_LDR_CA_CA3_SHIFT))&CAU_LDR_CA_CA3_MASK)
#define CAU_LDR_CA_CA4_MASK                      0xFFFFFFFFu
#define CAU_LDR_CA_CA4_SHIFT                     0
#define CAU_LDR_CA_CA4_WIDTH                     32
#define CAU_LDR_CA_CA4(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_LDR_CA_CA4_SHIFT))&CAU_LDR_CA_CA4_MASK)
#define CAU_LDR_CA_CA5_MASK                      0xFFFFFFFFu
#define CAU_LDR_CA_CA5_SHIFT                     0
#define CAU_LDR_CA_CA5_WIDTH                     32
#define CAU_LDR_CA_CA5(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_LDR_CA_CA5_SHIFT))&CAU_LDR_CA_CA5_MASK)
#define CAU_LDR_CA_CA6_MASK                      0xFFFFFFFFu
#define CAU_LDR_CA_CA6_SHIFT                     0
#define CAU_LDR_CA_CA6_WIDTH                     32
#define CAU_LDR_CA_CA6(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_LDR_CA_CA6_SHIFT))&CAU_LDR_CA_CA6_MASK)
#define CAU_LDR_CA_CA7_MASK                      0xFFFFFFFFu
#define CAU_LDR_CA_CA7_SHIFT                     0
#define CAU_LDR_CA_CA7_WIDTH                     32
#define CAU_LDR_CA_CA7(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_LDR_CA_CA7_SHIFT))&CAU_LDR_CA_CA7_MASK)
#define CAU_LDR_CA_CA8_MASK                      0xFFFFFFFFu
#define CAU_LDR_CA_CA8_SHIFT                     0
#define CAU_LDR_CA_CA8_WIDTH                     32
#define CAU_LDR_CA_CA8(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_LDR_CA_CA8_SHIFT))&CAU_LDR_CA_CA8_MASK)
/* STR_CASR Bit Fields */
#define CAU_STR_CASR_IC_MASK                     0x1u
#define CAU_STR_CASR_IC_SHIFT                    0
#define CAU_STR_CASR_IC_WIDTH                    1
#define CAU_STR_CASR_IC(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_STR_CASR_IC_SHIFT))&CAU_STR_CASR_IC_MASK)
#define CAU_STR_CASR_DPE_MASK                    0x2u
#define CAU_STR_CASR_DPE_SHIFT                   1
#define CAU_STR_CASR_DPE_WIDTH                   1
#define CAU_STR_CASR_DPE(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_STR_CASR_DPE_SHIFT))&CAU_STR_CASR_DPE_MASK)
#define CAU_STR_CASR_VER_MASK                    0xF0000000u
#define CAU_STR_CASR_VER_SHIFT                   28
#define CAU_STR_CASR_VER_WIDTH                   4
#define CAU_STR_CASR_VER(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_STR_CASR_VER_SHIFT))&CAU_STR_CASR_VER_MASK)
/* STR_CAA Bit Fields */
#define CAU_STR_CAA_ACC_MASK                     0xFFFFFFFFu
#define CAU_STR_CAA_ACC_SHIFT                    0
#define CAU_STR_CAA_ACC_WIDTH                    32
#define CAU_STR_CAA_ACC(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_STR_CAA_ACC_SHIFT))&CAU_STR_CAA_ACC_MASK)
/* STR_CA Bit Fields */
#define CAU_STR_CA_CA0_MASK                      0xFFFFFFFFu
#define CAU_STR_CA_CA0_SHIFT                     0
#define CAU_STR_CA_CA0_WIDTH                     32
#define CAU_STR_CA_CA0(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_STR_CA_CA0_SHIFT))&CAU_STR_CA_CA0_MASK)
#define CAU_STR_CA_CA1_MASK                      0xFFFFFFFFu
#define CAU_STR_CA_CA1_SHIFT                     0
#define CAU_STR_CA_CA1_WIDTH                     32
#define CAU_STR_CA_CA1(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_STR_CA_CA1_SHIFT))&CAU_STR_CA_CA1_MASK)
#define CAU_STR_CA_CA2_MASK                      0xFFFFFFFFu
#define CAU_STR_CA_CA2_SHIFT                     0
#define CAU_STR_CA_CA2_WIDTH                     32
#define CAU_STR_CA_CA2(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_STR_CA_CA2_SHIFT))&CAU_STR_CA_CA2_MASK)
#define CAU_STR_CA_CA3_MASK                      0xFFFFFFFFu
#define CAU_STR_CA_CA3_SHIFT                     0
#define CAU_STR_CA_CA3_WIDTH                     32
#define CAU_STR_CA_CA3(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_STR_CA_CA3_SHIFT))&CAU_STR_CA_CA3_MASK)
#define CAU_STR_CA_CA4_MASK                      0xFFFFFFFFu
#define CAU_STR_CA_CA4_SHIFT                     0
#define CAU_STR_CA_CA4_WIDTH                     32
#define CAU_STR_CA_CA4(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_STR_CA_CA4_SHIFT))&CAU_STR_CA_CA4_MASK)
#define CAU_STR_CA_CA5_MASK                      0xFFFFFFFFu
#define CAU_STR_CA_CA5_SHIFT                     0
#define CAU_STR_CA_CA5_WIDTH                     32
#define CAU_STR_CA_CA5(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_STR_CA_CA5_SHIFT))&CAU_STR_CA_CA5_MASK)
#define CAU_STR_CA_CA6_MASK                      0xFFFFFFFFu
#define CAU_STR_CA_CA6_SHIFT                     0
#define CAU_STR_CA_CA6_WIDTH                     32
#define CAU_STR_CA_CA6(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_STR_CA_CA6_SHIFT))&CAU_STR_CA_CA6_MASK)
#define CAU_STR_CA_CA7_MASK                      0xFFFFFFFFu
#define CAU_STR_CA_CA7_SHIFT                     0
#define CAU_STR_CA_CA7_WIDTH                     32
#define CAU_STR_CA_CA7(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_STR_CA_CA7_SHIFT))&CAU_STR_CA_CA7_MASK)
#define CAU_STR_CA_CA8_MASK                      0xFFFFFFFFu
#define CAU_STR_CA_CA8_SHIFT                     0
#define CAU_STR_CA_CA8_WIDTH                     32
#define CAU_STR_CA_CA8(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_STR_CA_CA8_SHIFT))&CAU_STR_CA_CA8_MASK)
/* ADR_CASR Bit Fields */
#define CAU_ADR_CASR_IC_MASK                     0x1u
#define CAU_ADR_CASR_IC_SHIFT                    0
#define CAU_ADR_CASR_IC_WIDTH                    1
#define CAU_ADR_CASR_IC(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_ADR_CASR_IC_SHIFT))&CAU_ADR_CASR_IC_MASK)
#define CAU_ADR_CASR_DPE_MASK                    0x2u
#define CAU_ADR_CASR_DPE_SHIFT                   1
#define CAU_ADR_CASR_DPE_WIDTH                   1
#define CAU_ADR_CASR_DPE(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_ADR_CASR_DPE_SHIFT))&CAU_ADR_CASR_DPE_MASK)
#define CAU_ADR_CASR_VER_MASK                    0xF0000000u
#define CAU_ADR_CASR_VER_SHIFT                   28
#define CAU_ADR_CASR_VER_WIDTH                   4
#define CAU_ADR_CASR_VER(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_ADR_CASR_VER_SHIFT))&CAU_ADR_CASR_VER_MASK)
/* ADR_CAA Bit Fields */
#define CAU_ADR_CAA_ACC_MASK                     0xFFFFFFFFu
#define CAU_ADR_CAA_ACC_SHIFT                    0
#define CAU_ADR_CAA_ACC_WIDTH                    32
#define CAU_ADR_CAA_ACC(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_ADR_CAA_ACC_SHIFT))&CAU_ADR_CAA_ACC_MASK)
/* ADR_CA Bit Fields */
#define CAU_ADR_CA_CA0_MASK                      0xFFFFFFFFu
#define CAU_ADR_CA_CA0_SHIFT                     0
#define CAU_ADR_CA_CA0_WIDTH                     32
#define CAU_ADR_CA_CA0(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_ADR_CA_CA0_SHIFT))&CAU_ADR_CA_CA0_MASK)
#define CAU_ADR_CA_CA1_MASK                      0xFFFFFFFFu
#define CAU_ADR_CA_CA1_SHIFT                     0
#define CAU_ADR_CA_CA1_WIDTH                     32
#define CAU_ADR_CA_CA1(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_ADR_CA_CA1_SHIFT))&CAU_ADR_CA_CA1_MASK)
#define CAU_ADR_CA_CA2_MASK                      0xFFFFFFFFu
#define CAU_ADR_CA_CA2_SHIFT                     0
#define CAU_ADR_CA_CA2_WIDTH                     32
#define CAU_ADR_CA_CA2(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_ADR_CA_CA2_SHIFT))&CAU_ADR_CA_CA2_MASK)
#define CAU_ADR_CA_CA3_MASK                      0xFFFFFFFFu
#define CAU_ADR_CA_CA3_SHIFT                     0
#define CAU_ADR_CA_CA3_WIDTH                     32
#define CAU_ADR_CA_CA3(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_ADR_CA_CA3_SHIFT))&CAU_ADR_CA_CA3_MASK)
#define CAU_ADR_CA_CA4_MASK                      0xFFFFFFFFu
#define CAU_ADR_CA_CA4_SHIFT                     0
#define CAU_ADR_CA_CA4_WIDTH                     32
#define CAU_ADR_CA_CA4(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_ADR_CA_CA4_SHIFT))&CAU_ADR_CA_CA4_MASK)
#define CAU_ADR_CA_CA5_MASK                      0xFFFFFFFFu
#define CAU_ADR_CA_CA5_SHIFT                     0
#define CAU_ADR_CA_CA5_WIDTH                     32
#define CAU_ADR_CA_CA5(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_ADR_CA_CA5_SHIFT))&CAU_ADR_CA_CA5_MASK)
#define CAU_ADR_CA_CA6_MASK                      0xFFFFFFFFu
#define CAU_ADR_CA_CA6_SHIFT                     0
#define CAU_ADR_CA_CA6_WIDTH                     32
#define CAU_ADR_CA_CA6(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_ADR_CA_CA6_SHIFT))&CAU_ADR_CA_CA6_MASK)
#define CAU_ADR_CA_CA7_MASK                      0xFFFFFFFFu
#define CAU_ADR_CA_CA7_SHIFT                     0
#define CAU_ADR_CA_CA7_WIDTH                     32
#define CAU_ADR_CA_CA7(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_ADR_CA_CA7_SHIFT))&CAU_ADR_CA_CA7_MASK)
#define CAU_ADR_CA_CA8_MASK                      0xFFFFFFFFu
#define CAU_ADR_CA_CA8_SHIFT                     0
#define CAU_ADR_CA_CA8_WIDTH                     32
#define CAU_ADR_CA_CA8(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_ADR_CA_CA8_SHIFT))&CAU_ADR_CA_CA8_MASK)
/* RADR_CASR Bit Fields */
#define CAU_RADR_CASR_IC_MASK                    0x1u
#define CAU_RADR_CASR_IC_SHIFT                   0
#define CAU_RADR_CASR_IC_WIDTH                   1
#define CAU_RADR_CASR_IC(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_RADR_CASR_IC_SHIFT))&CAU_RADR_CASR_IC_MASK)
#define CAU_RADR_CASR_DPE_MASK                   0x2u
#define CAU_RADR_CASR_DPE_SHIFT                  1
#define CAU_RADR_CASR_DPE_WIDTH                  1
#define CAU_RADR_CASR_DPE(x)                     (((uint32_t)(((uint32_t)(x))<<CAU_RADR_CASR_DPE_SHIFT))&CAU_RADR_CASR_DPE_MASK)
#define CAU_RADR_CASR_VER_MASK                   0xF0000000u
#define CAU_RADR_CASR_VER_SHIFT                  28
#define CAU_RADR_CASR_VER_WIDTH                  4
#define CAU_RADR_CASR_VER(x)                     (((uint32_t)(((uint32_t)(x))<<CAU_RADR_CASR_VER_SHIFT))&CAU_RADR_CASR_VER_MASK)
/* RADR_CAA Bit Fields */
#define CAU_RADR_CAA_ACC_MASK                    0xFFFFFFFFu
#define CAU_RADR_CAA_ACC_SHIFT                   0
#define CAU_RADR_CAA_ACC_WIDTH                   32
#define CAU_RADR_CAA_ACC(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_RADR_CAA_ACC_SHIFT))&CAU_RADR_CAA_ACC_MASK)
/* RADR_CA Bit Fields */
#define CAU_RADR_CA_CA0_MASK                     0xFFFFFFFFu
#define CAU_RADR_CA_CA0_SHIFT                    0
#define CAU_RADR_CA_CA0_WIDTH                    32
#define CAU_RADR_CA_CA0(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_RADR_CA_CA0_SHIFT))&CAU_RADR_CA_CA0_MASK)
#define CAU_RADR_CA_CA1_MASK                     0xFFFFFFFFu
#define CAU_RADR_CA_CA1_SHIFT                    0
#define CAU_RADR_CA_CA1_WIDTH                    32
#define CAU_RADR_CA_CA1(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_RADR_CA_CA1_SHIFT))&CAU_RADR_CA_CA1_MASK)
#define CAU_RADR_CA_CA2_MASK                     0xFFFFFFFFu
#define CAU_RADR_CA_CA2_SHIFT                    0
#define CAU_RADR_CA_CA2_WIDTH                    32
#define CAU_RADR_CA_CA2(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_RADR_CA_CA2_SHIFT))&CAU_RADR_CA_CA2_MASK)
#define CAU_RADR_CA_CA3_MASK                     0xFFFFFFFFu
#define CAU_RADR_CA_CA3_SHIFT                    0
#define CAU_RADR_CA_CA3_WIDTH                    32
#define CAU_RADR_CA_CA3(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_RADR_CA_CA3_SHIFT))&CAU_RADR_CA_CA3_MASK)
#define CAU_RADR_CA_CA4_MASK                     0xFFFFFFFFu
#define CAU_RADR_CA_CA4_SHIFT                    0
#define CAU_RADR_CA_CA4_WIDTH                    32
#define CAU_RADR_CA_CA4(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_RADR_CA_CA4_SHIFT))&CAU_RADR_CA_CA4_MASK)
#define CAU_RADR_CA_CA5_MASK                     0xFFFFFFFFu
#define CAU_RADR_CA_CA5_SHIFT                    0
#define CAU_RADR_CA_CA5_WIDTH                    32
#define CAU_RADR_CA_CA5(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_RADR_CA_CA5_SHIFT))&CAU_RADR_CA_CA5_MASK)
#define CAU_RADR_CA_CA6_MASK                     0xFFFFFFFFu
#define CAU_RADR_CA_CA6_SHIFT                    0
#define CAU_RADR_CA_CA6_WIDTH                    32
#define CAU_RADR_CA_CA6(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_RADR_CA_CA6_SHIFT))&CAU_RADR_CA_CA6_MASK)
#define CAU_RADR_CA_CA7_MASK                     0xFFFFFFFFu
#define CAU_RADR_CA_CA7_SHIFT                    0
#define CAU_RADR_CA_CA7_WIDTH                    32
#define CAU_RADR_CA_CA7(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_RADR_CA_CA7_SHIFT))&CAU_RADR_CA_CA7_MASK)
#define CAU_RADR_CA_CA8_MASK                     0xFFFFFFFFu
#define CAU_RADR_CA_CA8_SHIFT                    0
#define CAU_RADR_CA_CA8_WIDTH                    32
#define CAU_RADR_CA_CA8(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_RADR_CA_CA8_SHIFT))&CAU_RADR_CA_CA8_MASK)
/* XOR_CASR Bit Fields */
#define CAU_XOR_CASR_IC_MASK                     0x1u
#define CAU_XOR_CASR_IC_SHIFT                    0
#define CAU_XOR_CASR_IC_WIDTH                    1
#define CAU_XOR_CASR_IC(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_XOR_CASR_IC_SHIFT))&CAU_XOR_CASR_IC_MASK)
#define CAU_XOR_CASR_DPE_MASK                    0x2u
#define CAU_XOR_CASR_DPE_SHIFT                   1
#define CAU_XOR_CASR_DPE_WIDTH                   1
#define CAU_XOR_CASR_DPE(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_XOR_CASR_DPE_SHIFT))&CAU_XOR_CASR_DPE_MASK)
#define CAU_XOR_CASR_VER_MASK                    0xF0000000u
#define CAU_XOR_CASR_VER_SHIFT                   28
#define CAU_XOR_CASR_VER_WIDTH                   4
#define CAU_XOR_CASR_VER(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_XOR_CASR_VER_SHIFT))&CAU_XOR_CASR_VER_MASK)
/* XOR_CAA Bit Fields */
#define CAU_XOR_CAA_ACC_MASK                     0xFFFFFFFFu
#define CAU_XOR_CAA_ACC_SHIFT                    0
#define CAU_XOR_CAA_ACC_WIDTH                    32
#define CAU_XOR_CAA_ACC(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_XOR_CAA_ACC_SHIFT))&CAU_XOR_CAA_ACC_MASK)
/* XOR_CA Bit Fields */
#define CAU_XOR_CA_CA0_MASK                      0xFFFFFFFFu
#define CAU_XOR_CA_CA0_SHIFT                     0
#define CAU_XOR_CA_CA0_WIDTH                     32
#define CAU_XOR_CA_CA0(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_XOR_CA_CA0_SHIFT))&CAU_XOR_CA_CA0_MASK)
#define CAU_XOR_CA_CA1_MASK                      0xFFFFFFFFu
#define CAU_XOR_CA_CA1_SHIFT                     0
#define CAU_XOR_CA_CA1_WIDTH                     32
#define CAU_XOR_CA_CA1(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_XOR_CA_CA1_SHIFT))&CAU_XOR_CA_CA1_MASK)
#define CAU_XOR_CA_CA2_MASK                      0xFFFFFFFFu
#define CAU_XOR_CA_CA2_SHIFT                     0
#define CAU_XOR_CA_CA2_WIDTH                     32
#define CAU_XOR_CA_CA2(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_XOR_CA_CA2_SHIFT))&CAU_XOR_CA_CA2_MASK)
#define CAU_XOR_CA_CA3_MASK                      0xFFFFFFFFu
#define CAU_XOR_CA_CA3_SHIFT                     0
#define CAU_XOR_CA_CA3_WIDTH                     32
#define CAU_XOR_CA_CA3(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_XOR_CA_CA3_SHIFT))&CAU_XOR_CA_CA3_MASK)
#define CAU_XOR_CA_CA4_MASK                      0xFFFFFFFFu
#define CAU_XOR_CA_CA4_SHIFT                     0
#define CAU_XOR_CA_CA4_WIDTH                     32
#define CAU_XOR_CA_CA4(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_XOR_CA_CA4_SHIFT))&CAU_XOR_CA_CA4_MASK)
#define CAU_XOR_CA_CA5_MASK                      0xFFFFFFFFu
#define CAU_XOR_CA_CA5_SHIFT                     0
#define CAU_XOR_CA_CA5_WIDTH                     32
#define CAU_XOR_CA_CA5(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_XOR_CA_CA5_SHIFT))&CAU_XOR_CA_CA5_MASK)
#define CAU_XOR_CA_CA6_MASK                      0xFFFFFFFFu
#define CAU_XOR_CA_CA6_SHIFT                     0
#define CAU_XOR_CA_CA6_WIDTH                     32
#define CAU_XOR_CA_CA6(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_XOR_CA_CA6_SHIFT))&CAU_XOR_CA_CA6_MASK)
#define CAU_XOR_CA_CA7_MASK                      0xFFFFFFFFu
#define CAU_XOR_CA_CA7_SHIFT                     0
#define CAU_XOR_CA_CA7_WIDTH                     32
#define CAU_XOR_CA_CA7(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_XOR_CA_CA7_SHIFT))&CAU_XOR_CA_CA7_MASK)
#define CAU_XOR_CA_CA8_MASK                      0xFFFFFFFFu
#define CAU_XOR_CA_CA8_SHIFT                     0
#define CAU_XOR_CA_CA8_WIDTH                     32
#define CAU_XOR_CA_CA8(x)                        (((uint32_t)(((uint32_t)(x))<<CAU_XOR_CA_CA8_SHIFT))&CAU_XOR_CA_CA8_MASK)
/* ROTL_CASR Bit Fields */
#define CAU_ROTL_CASR_IC_MASK                    0x1u
#define CAU_ROTL_CASR_IC_SHIFT                   0
#define CAU_ROTL_CASR_IC_WIDTH                   1
#define CAU_ROTL_CASR_IC(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_ROTL_CASR_IC_SHIFT))&CAU_ROTL_CASR_IC_MASK)
#define CAU_ROTL_CASR_DPE_MASK                   0x2u
#define CAU_ROTL_CASR_DPE_SHIFT                  1
#define CAU_ROTL_CASR_DPE_WIDTH                  1
#define CAU_ROTL_CASR_DPE(x)                     (((uint32_t)(((uint32_t)(x))<<CAU_ROTL_CASR_DPE_SHIFT))&CAU_ROTL_CASR_DPE_MASK)
#define CAU_ROTL_CASR_VER_MASK                   0xF0000000u
#define CAU_ROTL_CASR_VER_SHIFT                  28
#define CAU_ROTL_CASR_VER_WIDTH                  4
#define CAU_ROTL_CASR_VER(x)                     (((uint32_t)(((uint32_t)(x))<<CAU_ROTL_CASR_VER_SHIFT))&CAU_ROTL_CASR_VER_MASK)
/* ROTL_CAA Bit Fields */
#define CAU_ROTL_CAA_ACC_MASK                    0xFFFFFFFFu
#define CAU_ROTL_CAA_ACC_SHIFT                   0
#define CAU_ROTL_CAA_ACC_WIDTH                   32
#define CAU_ROTL_CAA_ACC(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_ROTL_CAA_ACC_SHIFT))&CAU_ROTL_CAA_ACC_MASK)
/* ROTL_CA Bit Fields */
#define CAU_ROTL_CA_CA0_MASK                     0xFFFFFFFFu
#define CAU_ROTL_CA_CA0_SHIFT                    0
#define CAU_ROTL_CA_CA0_WIDTH                    32
#define CAU_ROTL_CA_CA0(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_ROTL_CA_CA0_SHIFT))&CAU_ROTL_CA_CA0_MASK)
#define CAU_ROTL_CA_CA1_MASK                     0xFFFFFFFFu
#define CAU_ROTL_CA_CA1_SHIFT                    0
#define CAU_ROTL_CA_CA1_WIDTH                    32
#define CAU_ROTL_CA_CA1(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_ROTL_CA_CA1_SHIFT))&CAU_ROTL_CA_CA1_MASK)
#define CAU_ROTL_CA_CA2_MASK                     0xFFFFFFFFu
#define CAU_ROTL_CA_CA2_SHIFT                    0
#define CAU_ROTL_CA_CA2_WIDTH                    32
#define CAU_ROTL_CA_CA2(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_ROTL_CA_CA2_SHIFT))&CAU_ROTL_CA_CA2_MASK)
#define CAU_ROTL_CA_CA3_MASK                     0xFFFFFFFFu
#define CAU_ROTL_CA_CA3_SHIFT                    0
#define CAU_ROTL_CA_CA3_WIDTH                    32
#define CAU_ROTL_CA_CA3(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_ROTL_CA_CA3_SHIFT))&CAU_ROTL_CA_CA3_MASK)
#define CAU_ROTL_CA_CA4_MASK                     0xFFFFFFFFu
#define CAU_ROTL_CA_CA4_SHIFT                    0
#define CAU_ROTL_CA_CA4_WIDTH                    32
#define CAU_ROTL_CA_CA4(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_ROTL_CA_CA4_SHIFT))&CAU_ROTL_CA_CA4_MASK)
#define CAU_ROTL_CA_CA5_MASK                     0xFFFFFFFFu
#define CAU_ROTL_CA_CA5_SHIFT                    0
#define CAU_ROTL_CA_CA5_WIDTH                    32
#define CAU_ROTL_CA_CA5(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_ROTL_CA_CA5_SHIFT))&CAU_ROTL_CA_CA5_MASK)
#define CAU_ROTL_CA_CA6_MASK                     0xFFFFFFFFu
#define CAU_ROTL_CA_CA6_SHIFT                    0
#define CAU_ROTL_CA_CA6_WIDTH                    32
#define CAU_ROTL_CA_CA6(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_ROTL_CA_CA6_SHIFT))&CAU_ROTL_CA_CA6_MASK)
#define CAU_ROTL_CA_CA7_MASK                     0xFFFFFFFFu
#define CAU_ROTL_CA_CA7_SHIFT                    0
#define CAU_ROTL_CA_CA7_WIDTH                    32
#define CAU_ROTL_CA_CA7(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_ROTL_CA_CA7_SHIFT))&CAU_ROTL_CA_CA7_MASK)
#define CAU_ROTL_CA_CA8_MASK                     0xFFFFFFFFu
#define CAU_ROTL_CA_CA8_SHIFT                    0
#define CAU_ROTL_CA_CA8_WIDTH                    32
#define CAU_ROTL_CA_CA8(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_ROTL_CA_CA8_SHIFT))&CAU_ROTL_CA_CA8_MASK)
/* AESC_CASR Bit Fields */
#define CAU_AESC_CASR_IC_MASK                    0x1u
#define CAU_AESC_CASR_IC_SHIFT                   0
#define CAU_AESC_CASR_IC_WIDTH                   1
#define CAU_AESC_CASR_IC(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_AESC_CASR_IC_SHIFT))&CAU_AESC_CASR_IC_MASK)
#define CAU_AESC_CASR_DPE_MASK                   0x2u
#define CAU_AESC_CASR_DPE_SHIFT                  1
#define CAU_AESC_CASR_DPE_WIDTH                  1
#define CAU_AESC_CASR_DPE(x)                     (((uint32_t)(((uint32_t)(x))<<CAU_AESC_CASR_DPE_SHIFT))&CAU_AESC_CASR_DPE_MASK)
#define CAU_AESC_CASR_VER_MASK                   0xF0000000u
#define CAU_AESC_CASR_VER_SHIFT                  28
#define CAU_AESC_CASR_VER_WIDTH                  4
#define CAU_AESC_CASR_VER(x)                     (((uint32_t)(((uint32_t)(x))<<CAU_AESC_CASR_VER_SHIFT))&CAU_AESC_CASR_VER_MASK)
/* AESC_CAA Bit Fields */
#define CAU_AESC_CAA_ACC_MASK                    0xFFFFFFFFu
#define CAU_AESC_CAA_ACC_SHIFT                   0
#define CAU_AESC_CAA_ACC_WIDTH                   32
#define CAU_AESC_CAA_ACC(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_AESC_CAA_ACC_SHIFT))&CAU_AESC_CAA_ACC_MASK)
/* AESC_CA Bit Fields */
#define CAU_AESC_CA_CA0_MASK                     0xFFFFFFFFu
#define CAU_AESC_CA_CA0_SHIFT                    0
#define CAU_AESC_CA_CA0_WIDTH                    32
#define CAU_AESC_CA_CA0(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_AESC_CA_CA0_SHIFT))&CAU_AESC_CA_CA0_MASK)
#define CAU_AESC_CA_CA1_MASK                     0xFFFFFFFFu
#define CAU_AESC_CA_CA1_SHIFT                    0
#define CAU_AESC_CA_CA1_WIDTH                    32
#define CAU_AESC_CA_CA1(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_AESC_CA_CA1_SHIFT))&CAU_AESC_CA_CA1_MASK)
#define CAU_AESC_CA_CA2_MASK                     0xFFFFFFFFu
#define CAU_AESC_CA_CA2_SHIFT                    0
#define CAU_AESC_CA_CA2_WIDTH                    32
#define CAU_AESC_CA_CA2(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_AESC_CA_CA2_SHIFT))&CAU_AESC_CA_CA2_MASK)
#define CAU_AESC_CA_CA3_MASK                     0xFFFFFFFFu
#define CAU_AESC_CA_CA3_SHIFT                    0
#define CAU_AESC_CA_CA3_WIDTH                    32
#define CAU_AESC_CA_CA3(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_AESC_CA_CA3_SHIFT))&CAU_AESC_CA_CA3_MASK)
#define CAU_AESC_CA_CA4_MASK                     0xFFFFFFFFu
#define CAU_AESC_CA_CA4_SHIFT                    0
#define CAU_AESC_CA_CA4_WIDTH                    32
#define CAU_AESC_CA_CA4(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_AESC_CA_CA4_SHIFT))&CAU_AESC_CA_CA4_MASK)
#define CAU_AESC_CA_CA5_MASK                     0xFFFFFFFFu
#define CAU_AESC_CA_CA5_SHIFT                    0
#define CAU_AESC_CA_CA5_WIDTH                    32
#define CAU_AESC_CA_CA5(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_AESC_CA_CA5_SHIFT))&CAU_AESC_CA_CA5_MASK)
#define CAU_AESC_CA_CA6_MASK                     0xFFFFFFFFu
#define CAU_AESC_CA_CA6_SHIFT                    0
#define CAU_AESC_CA_CA6_WIDTH                    32
#define CAU_AESC_CA_CA6(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_AESC_CA_CA6_SHIFT))&CAU_AESC_CA_CA6_MASK)
#define CAU_AESC_CA_CA7_MASK                     0xFFFFFFFFu
#define CAU_AESC_CA_CA7_SHIFT                    0
#define CAU_AESC_CA_CA7_WIDTH                    32
#define CAU_AESC_CA_CA7(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_AESC_CA_CA7_SHIFT))&CAU_AESC_CA_CA7_MASK)
#define CAU_AESC_CA_CA8_MASK                     0xFFFFFFFFu
#define CAU_AESC_CA_CA8_SHIFT                    0
#define CAU_AESC_CA_CA8_WIDTH                    32
#define CAU_AESC_CA_CA8(x)                       (((uint32_t)(((uint32_t)(x))<<CAU_AESC_CA_CA8_SHIFT))&CAU_AESC_CA_CA8_MASK)
/* AESIC_CASR Bit Fields */
#define CAU_AESIC_CASR_IC_MASK                   0x1u
#define CAU_AESIC_CASR_IC_SHIFT                  0
#define CAU_AESIC_CASR_IC_WIDTH                  1
#define CAU_AESIC_CASR_IC(x)                     (((uint32_t)(((uint32_t)(x))<<CAU_AESIC_CASR_IC_SHIFT))&CAU_AESIC_CASR_IC_MASK)
#define CAU_AESIC_CASR_DPE_MASK                  0x2u
#define CAU_AESIC_CASR_DPE_SHIFT                 1
#define CAU_AESIC_CASR_DPE_WIDTH                 1
#define CAU_AESIC_CASR_DPE(x)                    (((uint32_t)(((uint32_t)(x))<<CAU_AESIC_CASR_DPE_SHIFT))&CAU_AESIC_CASR_DPE_MASK)
#define CAU_AESIC_CASR_VER_MASK                  0xF0000000u
#define CAU_AESIC_CASR_VER_SHIFT                 28
#define CAU_AESIC_CASR_VER_WIDTH                 4
#define CAU_AESIC_CASR_VER(x)                    (((uint32_t)(((uint32_t)(x))<<CAU_AESIC_CASR_VER_SHIFT))&CAU_AESIC_CASR_VER_MASK)
/* AESIC_CAA Bit Fields */
#define CAU_AESIC_CAA_ACC_MASK                   0xFFFFFFFFu
#define CAU_AESIC_CAA_ACC_SHIFT                  0
#define CAU_AESIC_CAA_ACC_WIDTH                  32
#define CAU_AESIC_CAA_ACC(x)                     (((uint32_t)(((uint32_t)(x))<<CAU_AESIC_CAA_ACC_SHIFT))&CAU_AESIC_CAA_ACC_MASK)
/* AESIC_CA Bit Fields */
#define CAU_AESIC_CA_CA0_MASK                    0xFFFFFFFFu
#define CAU_AESIC_CA_CA0_SHIFT                   0
#define CAU_AESIC_CA_CA0_WIDTH                   32
#define CAU_AESIC_CA_CA0(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_AESIC_CA_CA0_SHIFT))&CAU_AESIC_CA_CA0_MASK)
#define CAU_AESIC_CA_CA1_MASK                    0xFFFFFFFFu
#define CAU_AESIC_CA_CA1_SHIFT                   0
#define CAU_AESIC_CA_CA1_WIDTH                   32
#define CAU_AESIC_CA_CA1(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_AESIC_CA_CA1_SHIFT))&CAU_AESIC_CA_CA1_MASK)
#define CAU_AESIC_CA_CA2_MASK                    0xFFFFFFFFu
#define CAU_AESIC_CA_CA2_SHIFT                   0
#define CAU_AESIC_CA_CA2_WIDTH                   32
#define CAU_AESIC_CA_CA2(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_AESIC_CA_CA2_SHIFT))&CAU_AESIC_CA_CA2_MASK)
#define CAU_AESIC_CA_CA3_MASK                    0xFFFFFFFFu
#define CAU_AESIC_CA_CA3_SHIFT                   0
#define CAU_AESIC_CA_CA3_WIDTH                   32
#define CAU_AESIC_CA_CA3(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_AESIC_CA_CA3_SHIFT))&CAU_AESIC_CA_CA3_MASK)
#define CAU_AESIC_CA_CA4_MASK                    0xFFFFFFFFu
#define CAU_AESIC_CA_CA4_SHIFT                   0
#define CAU_AESIC_CA_CA4_WIDTH                   32
#define CAU_AESIC_CA_CA4(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_AESIC_CA_CA4_SHIFT))&CAU_AESIC_CA_CA4_MASK)
#define CAU_AESIC_CA_CA5_MASK                    0xFFFFFFFFu
#define CAU_AESIC_CA_CA5_SHIFT                   0
#define CAU_AESIC_CA_CA5_WIDTH                   32
#define CAU_AESIC_CA_CA5(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_AESIC_CA_CA5_SHIFT))&CAU_AESIC_CA_CA5_MASK)
#define CAU_AESIC_CA_CA6_MASK                    0xFFFFFFFFu
#define CAU_AESIC_CA_CA6_SHIFT                   0
#define CAU_AESIC_CA_CA6_WIDTH                   32
#define CAU_AESIC_CA_CA6(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_AESIC_CA_CA6_SHIFT))&CAU_AESIC_CA_CA6_MASK)
#define CAU_AESIC_CA_CA7_MASK                    0xFFFFFFFFu
#define CAU_AESIC_CA_CA7_SHIFT                   0
#define CAU_AESIC_CA_CA7_WIDTH                   32
#define CAU_AESIC_CA_CA7(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_AESIC_CA_CA7_SHIFT))&CAU_AESIC_CA_CA7_MASK)
#define CAU_AESIC_CA_CA8_MASK                    0xFFFFFFFFu
#define CAU_AESIC_CA_CA8_SHIFT                   0
#define CAU_AESIC_CA_CA8_WIDTH                   32
#define CAU_AESIC_CA_CA8(x)                      (((uint32_t)(((uint32_t)(x))<<CAU_AESIC_CA_CA8_SHIFT))&CAU_AESIC_CA_CA8_MASK)

/*!
 * @}
 */ /* end of group CAU_Register_Masks */


/* CAU - Peripheral instance base addresses */
/** Peripheral CAU base address */
#define CAU_BASE                                 (0xF0005000u)
/** Peripheral CAU base pointer */
#define CAU                                      ((CAU_Type *)CAU_BASE)
#define CAU_BASE_PTR                             (CAU)
/** Array initializer of CAU peripheral base addresses */
#define CAU_BASE_ADDRS                           { CAU_BASE }
/** Array initializer of CAU peripheral base pointers */
#define CAU_BASE_PTRS                            { CAU }

/* ----------------------------------------------------------------------------
   -- CAU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAU_Register_Accessor_Macros CAU - Register accessor macros
 * @{
 */


/* CAU - Register instance definitions */
/* CAU */
#define CAU_DIRECT0                              CAU_DIRECT_REG(CAU,0)
#define CAU_DIRECT1                              CAU_DIRECT_REG(CAU,1)
#define CAU_DIRECT2                              CAU_DIRECT_REG(CAU,2)
#define CAU_DIRECT3                              CAU_DIRECT_REG(CAU,3)
#define CAU_DIRECT4                              CAU_DIRECT_REG(CAU,4)
#define CAU_DIRECT5                              CAU_DIRECT_REG(CAU,5)
#define CAU_DIRECT6                              CAU_DIRECT_REG(CAU,6)
#define CAU_DIRECT7                              CAU_DIRECT_REG(CAU,7)
#define CAU_DIRECT8                              CAU_DIRECT_REG(CAU,8)
#define CAU_DIRECT9                              CAU_DIRECT_REG(CAU,9)
#define CAU_DIRECT10                             CAU_DIRECT_REG(CAU,10)
#define CAU_DIRECT11                             CAU_DIRECT_REG(CAU,11)
#define CAU_DIRECT12                             CAU_DIRECT_REG(CAU,12)
#define CAU_DIRECT13                             CAU_DIRECT_REG(CAU,13)
#define CAU_DIRECT14                             CAU_DIRECT_REG(CAU,14)
#define CAU_DIRECT15                             CAU_DIRECT_REG(CAU,15)
#define CAU_LDR_CASR                             CAU_LDR_CASR_REG(CAU)
#define CAU_LDR_CAA                              CAU_LDR_CAA_REG(CAU)
#define CAU_LDR_CA0                              CAU_LDR_CA_REG(CAU,0)
#define CAU_LDR_CA1                              CAU_LDR_CA_REG(CAU,1)
#define CAU_LDR_CA2                              CAU_LDR_CA_REG(CAU,2)
#define CAU_LDR_CA3                              CAU_LDR_CA_REG(CAU,3)
#define CAU_LDR_CA4                              CAU_LDR_CA_REG(CAU,4)
#define CAU_LDR_CA5                              CAU_LDR_CA_REG(CAU,5)
#define CAU_LDR_CA6                              CAU_LDR_CA_REG(CAU,6)
#define CAU_LDR_CA7                              CAU_LDR_CA_REG(CAU,7)
#define CAU_LDR_CA8                              CAU_LDR_CA_REG(CAU,8)
#define CAU_STR_CASR                             CAU_STR_CASR_REG(CAU)
#define CAU_STR_CAA                              CAU_STR_CAA_REG(CAU)
#define CAU_STR_CA0                              CAU_STR_CA_REG(CAU,0)
#define CAU_STR_CA1                              CAU_STR_CA_REG(CAU,1)
#define CAU_STR_CA2                              CAU_STR_CA_REG(CAU,2)
#define CAU_STR_CA3                              CAU_STR_CA_REG(CAU,3)
#define CAU_STR_CA4                              CAU_STR_CA_REG(CAU,4)
#define CAU_STR_CA5                              CAU_STR_CA_REG(CAU,5)
#define CAU_STR_CA6                              CAU_STR_CA_REG(CAU,6)
#define CAU_STR_CA7                              CAU_STR_CA_REG(CAU,7)
#define CAU_STR_CA8                              CAU_STR_CA_REG(CAU,8)
#define CAU_ADR_CASR                             CAU_ADR_CASR_REG(CAU)
#define CAU_ADR_CAA                              CAU_ADR_CAA_REG(CAU)
#define CAU_ADR_CA0                              CAU_ADR_CA_REG(CAU,0)
#define CAU_ADR_CA1                              CAU_ADR_CA_REG(CAU,1)
#define CAU_ADR_CA2                              CAU_ADR_CA_REG(CAU,2)
#define CAU_ADR_CA3                              CAU_ADR_CA_REG(CAU,3)
#define CAU_ADR_CA4                              CAU_ADR_CA_REG(CAU,4)
#define CAU_ADR_CA5                              CAU_ADR_CA_REG(CAU,5)
#define CAU_ADR_CA6                              CAU_ADR_CA_REG(CAU,6)
#define CAU_ADR_CA7                              CAU_ADR_CA_REG(CAU,7)
#define CAU_ADR_CA8                              CAU_ADR_CA_REG(CAU,8)
#define CAU_RADR_CASR                            CAU_RADR_CASR_REG(CAU)
#define CAU_RADR_CAA                             CAU_RADR_CAA_REG(CAU)
#define CAU_RADR_CA0                             CAU_RADR_CA_REG(CAU,0)
#define CAU_RADR_CA1                             CAU_RADR_CA_REG(CAU,1)
#define CAU_RADR_CA2                             CAU_RADR_CA_REG(CAU,2)
#define CAU_RADR_CA3                             CAU_RADR_CA_REG(CAU,3)
#define CAU_RADR_CA4                             CAU_RADR_CA_REG(CAU,4)
#define CAU_RADR_CA5                             CAU_RADR_CA_REG(CAU,5)
#define CAU_RADR_CA6                             CAU_RADR_CA_REG(CAU,6)
#define CAU_RADR_CA7                             CAU_RADR_CA_REG(CAU,7)
#define CAU_RADR_CA8                             CAU_RADR_CA_REG(CAU,8)
#define CAU_XOR_CASR                             CAU_XOR_CASR_REG(CAU)
#define CAU_XOR_CAA                              CAU_XOR_CAA_REG(CAU)
#define CAU_XOR_CA0                              CAU_XOR_CA_REG(CAU,0)
#define CAU_XOR_CA1                              CAU_XOR_CA_REG(CAU,1)
#define CAU_XOR_CA2                              CAU_XOR_CA_REG(CAU,2)
#define CAU_XOR_CA3                              CAU_XOR_CA_REG(CAU,3)
#define CAU_XOR_CA4                              CAU_XOR_CA_REG(CAU,4)
#define CAU_XOR_CA5                              CAU_XOR_CA_REG(CAU,5)
#define CAU_XOR_CA6                              CAU_XOR_CA_REG(CAU,6)
#define CAU_XOR_CA7                              CAU_XOR_CA_REG(CAU,7)
#define CAU_XOR_CA8                              CAU_XOR_CA_REG(CAU,8)
#define CAU_ROTL_CASR                            CAU_ROTL_CASR_REG(CAU)
#define CAU_ROTL_CAA                             CAU_ROTL_CAA_REG(CAU)
#define CAU_ROTL_CA0                             CAU_ROTL_CA_REG(CAU,0)
#define CAU_ROTL_CA1                             CAU_ROTL_CA_REG(CAU,1)
#define CAU_ROTL_CA2                             CAU_ROTL_CA_REG(CAU,2)
#define CAU_ROTL_CA3                             CAU_ROTL_CA_REG(CAU,3)
#define CAU_ROTL_CA4                             CAU_ROTL_CA_REG(CAU,4)
#define CAU_ROTL_CA5                             CAU_ROTL_CA_REG(CAU,5)
#define CAU_ROTL_CA6                             CAU_ROTL_CA_REG(CAU,6)
#define CAU_ROTL_CA7                             CAU_ROTL_CA_REG(CAU,7)
#define CAU_ROTL_CA8                             CAU_ROTL_CA_REG(CAU,8)
#define CAU_AESC_CASR                            CAU_AESC_CASR_REG(CAU)
#define CAU_AESC_CAA                             CAU_AESC_CAA_REG(CAU)
#define CAU_AESC_CA0                             CAU_AESC_CA_REG(CAU,0)
#define CAU_AESC_CA1                             CAU_AESC_CA_REG(CAU,1)
#define CAU_AESC_CA2                             CAU_AESC_CA_REG(CAU,2)
#define CAU_AESC_CA3                             CAU_AESC_CA_REG(CAU,3)
#define CAU_AESC_CA4                             CAU_AESC_CA_REG(CAU,4)
#define CAU_AESC_CA5                             CAU_AESC_CA_REG(CAU,5)
#define CAU_AESC_CA6                             CAU_AESC_CA_REG(CAU,6)
#define CAU_AESC_CA7                             CAU_AESC_CA_REG(CAU,7)
#define CAU_AESC_CA8                             CAU_AESC_CA_REG(CAU,8)
#define CAU_AESIC_CASR                           CAU_AESIC_CASR_REG(CAU)
#define CAU_AESIC_CAA                            CAU_AESIC_CAA_REG(CAU)
#define CAU_AESIC_CA0                            CAU_AESIC_CA_REG(CAU,0)
#define CAU_AESIC_CA1                            CAU_AESIC_CA_REG(CAU,1)
#define CAU_AESIC_CA2                            CAU_AESIC_CA_REG(CAU,2)
#define CAU_AESIC_CA3                            CAU_AESIC_CA_REG(CAU,3)
#define CAU_AESIC_CA4                            CAU_AESIC_CA_REG(CAU,4)
#define CAU_AESIC_CA5                            CAU_AESIC_CA_REG(CAU,5)
#define CAU_AESIC_CA6                            CAU_AESIC_CA_REG(CAU,6)
#define CAU_AESIC_CA7                            CAU_AESIC_CA_REG(CAU,7)
#define CAU_AESIC_CA8                            CAU_AESIC_CA_REG(CAU,8)

/* CAU - Register array accessors */
#define CAU_DIRECT(index)                        CAU_DIRECT_REG(CAU,index)
#define CAU_LDR_CA(index)                        CAU_LDR_CA_REG(CAU,index)
#define CAU_STR_CA(index)                        CAU_STR_CA_REG(CAU,index)
#define CAU_ADR_CA(index)                        CAU_ADR_CA_REG(CAU,index)
#define CAU_RADR_CA(index)                       CAU_RADR_CA_REG(CAU,index)
#define CAU_XOR_CA(index)                        CAU_XOR_CA_REG(CAU,index)
#define CAU_ROTL_CA(index)                       CAU_ROTL_CA_REG(CAU,index)
#define CAU_AESC_CA(index)                       CAU_AESC_CA_REG(CAU,index)
#define CAU_AESIC_CA(index)                      CAU_AESIC_CA_REG(CAU,index)

/*!
 * @}
 */ /* end of group CAU_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CAU_Peripheral_Access_Layer */


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
} CMP_Type, *CMP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CMP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Register_Accessor_Macros CMP - Register accessor macros
 * @{
 */


/* CMP - Register accessors */
#define CMP_CR0_REG(base)                        ((base)->CR0)
#define CMP_CR1_REG(base)                        ((base)->CR1)
#define CMP_FPR_REG(base)                        ((base)->FPR)
#define CMP_SCR_REG(base)                        ((base)->SCR)
#define CMP_DACCR_REG(base)                      ((base)->DACCR)
#define CMP_MUXCR_REG(base)                      ((base)->MUXCR)

/*!
 * @}
 */ /* end of group CMP_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CMP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Register_Masks CMP Register Masks
 * @{
 */

/* CR0 Bit Fields */
#define CMP_CR0_HYSTCTR_MASK                     0x3u
#define CMP_CR0_HYSTCTR_SHIFT                    0
#define CMP_CR0_HYSTCTR_WIDTH                    2
#define CMP_CR0_HYSTCTR(x)                       (((uint8_t)(((uint8_t)(x))<<CMP_CR0_HYSTCTR_SHIFT))&CMP_CR0_HYSTCTR_MASK)
#define CMP_CR0_FILTER_CNT_MASK                  0x70u
#define CMP_CR0_FILTER_CNT_SHIFT                 4
#define CMP_CR0_FILTER_CNT_WIDTH                 3
#define CMP_CR0_FILTER_CNT(x)                    (((uint8_t)(((uint8_t)(x))<<CMP_CR0_FILTER_CNT_SHIFT))&CMP_CR0_FILTER_CNT_MASK)
/* CR1 Bit Fields */
#define CMP_CR1_EN_MASK                          0x1u
#define CMP_CR1_EN_SHIFT                         0
#define CMP_CR1_EN_WIDTH                         1
#define CMP_CR1_EN(x)                            (((uint8_t)(((uint8_t)(x))<<CMP_CR1_EN_SHIFT))&CMP_CR1_EN_MASK)
#define CMP_CR1_OPE_MASK                         0x2u
#define CMP_CR1_OPE_SHIFT                        1
#define CMP_CR1_OPE_WIDTH                        1
#define CMP_CR1_OPE(x)                           (((uint8_t)(((uint8_t)(x))<<CMP_CR1_OPE_SHIFT))&CMP_CR1_OPE_MASK)
#define CMP_CR1_COS_MASK                         0x4u
#define CMP_CR1_COS_SHIFT                        2
#define CMP_CR1_COS_WIDTH                        1
#define CMP_CR1_COS(x)                           (((uint8_t)(((uint8_t)(x))<<CMP_CR1_COS_SHIFT))&CMP_CR1_COS_MASK)
#define CMP_CR1_INV_MASK                         0x8u
#define CMP_CR1_INV_SHIFT                        3
#define CMP_CR1_INV_WIDTH                        1
#define CMP_CR1_INV(x)                           (((uint8_t)(((uint8_t)(x))<<CMP_CR1_INV_SHIFT))&CMP_CR1_INV_MASK)
#define CMP_CR1_PMODE_MASK                       0x10u
#define CMP_CR1_PMODE_SHIFT                      4
#define CMP_CR1_PMODE_WIDTH                      1
#define CMP_CR1_PMODE(x)                         (((uint8_t)(((uint8_t)(x))<<CMP_CR1_PMODE_SHIFT))&CMP_CR1_PMODE_MASK)
#define CMP_CR1_TRIGM_MASK                       0x20u
#define CMP_CR1_TRIGM_SHIFT                      5
#define CMP_CR1_TRIGM_WIDTH                      1
#define CMP_CR1_TRIGM(x)                         (((uint8_t)(((uint8_t)(x))<<CMP_CR1_TRIGM_SHIFT))&CMP_CR1_TRIGM_MASK)
#define CMP_CR1_WE_MASK                          0x40u
#define CMP_CR1_WE_SHIFT                         6
#define CMP_CR1_WE_WIDTH                         1
#define CMP_CR1_WE(x)                            (((uint8_t)(((uint8_t)(x))<<CMP_CR1_WE_SHIFT))&CMP_CR1_WE_MASK)
#define CMP_CR1_SE_MASK                          0x80u
#define CMP_CR1_SE_SHIFT                         7
#define CMP_CR1_SE_WIDTH                         1
#define CMP_CR1_SE(x)                            (((uint8_t)(((uint8_t)(x))<<CMP_CR1_SE_SHIFT))&CMP_CR1_SE_MASK)
/* FPR Bit Fields */
#define CMP_FPR_FILT_PER_MASK                    0xFFu
#define CMP_FPR_FILT_PER_SHIFT                   0
#define CMP_FPR_FILT_PER_WIDTH                   8
#define CMP_FPR_FILT_PER(x)                      (((uint8_t)(((uint8_t)(x))<<CMP_FPR_FILT_PER_SHIFT))&CMP_FPR_FILT_PER_MASK)
/* SCR Bit Fields */
#define CMP_SCR_COUT_MASK                        0x1u
#define CMP_SCR_COUT_SHIFT                       0
#define CMP_SCR_COUT_WIDTH                       1
#define CMP_SCR_COUT(x)                          (((uint8_t)(((uint8_t)(x))<<CMP_SCR_COUT_SHIFT))&CMP_SCR_COUT_MASK)
#define CMP_SCR_CFF_MASK                         0x2u
#define CMP_SCR_CFF_SHIFT                        1
#define CMP_SCR_CFF_WIDTH                        1
#define CMP_SCR_CFF(x)                           (((uint8_t)(((uint8_t)(x))<<CMP_SCR_CFF_SHIFT))&CMP_SCR_CFF_MASK)
#define CMP_SCR_CFR_MASK                         0x4u
#define CMP_SCR_CFR_SHIFT                        2
#define CMP_SCR_CFR_WIDTH                        1
#define CMP_SCR_CFR(x)                           (((uint8_t)(((uint8_t)(x))<<CMP_SCR_CFR_SHIFT))&CMP_SCR_CFR_MASK)
#define CMP_SCR_IEF_MASK                         0x8u
#define CMP_SCR_IEF_SHIFT                        3
#define CMP_SCR_IEF_WIDTH                        1
#define CMP_SCR_IEF(x)                           (((uint8_t)(((uint8_t)(x))<<CMP_SCR_IEF_SHIFT))&CMP_SCR_IEF_MASK)
#define CMP_SCR_IER_MASK                         0x10u
#define CMP_SCR_IER_SHIFT                        4
#define CMP_SCR_IER_WIDTH                        1
#define CMP_SCR_IER(x)                           (((uint8_t)(((uint8_t)(x))<<CMP_SCR_IER_SHIFT))&CMP_SCR_IER_MASK)
#define CMP_SCR_DMAEN_MASK                       0x40u
#define CMP_SCR_DMAEN_SHIFT                      6
#define CMP_SCR_DMAEN_WIDTH                      1
#define CMP_SCR_DMAEN(x)                         (((uint8_t)(((uint8_t)(x))<<CMP_SCR_DMAEN_SHIFT))&CMP_SCR_DMAEN_MASK)
/* DACCR Bit Fields */
#define CMP_DACCR_VOSEL_MASK                     0x3Fu
#define CMP_DACCR_VOSEL_SHIFT                    0
#define CMP_DACCR_VOSEL_WIDTH                    6
#define CMP_DACCR_VOSEL(x)                       (((uint8_t)(((uint8_t)(x))<<CMP_DACCR_VOSEL_SHIFT))&CMP_DACCR_VOSEL_MASK)
#define CMP_DACCR_VRSEL_MASK                     0x40u
#define CMP_DACCR_VRSEL_SHIFT                    6
#define CMP_DACCR_VRSEL_WIDTH                    1
#define CMP_DACCR_VRSEL(x)                       (((uint8_t)(((uint8_t)(x))<<CMP_DACCR_VRSEL_SHIFT))&CMP_DACCR_VRSEL_MASK)
#define CMP_DACCR_DACEN_MASK                     0x80u
#define CMP_DACCR_DACEN_SHIFT                    7
#define CMP_DACCR_DACEN_WIDTH                    1
#define CMP_DACCR_DACEN(x)                       (((uint8_t)(((uint8_t)(x))<<CMP_DACCR_DACEN_SHIFT))&CMP_DACCR_DACEN_MASK)
/* MUXCR Bit Fields */
#define CMP_MUXCR_MSEL_MASK                      0x7u
#define CMP_MUXCR_MSEL_SHIFT                     0
#define CMP_MUXCR_MSEL_WIDTH                     3
#define CMP_MUXCR_MSEL(x)                        (((uint8_t)(((uint8_t)(x))<<CMP_MUXCR_MSEL_SHIFT))&CMP_MUXCR_MSEL_MASK)
#define CMP_MUXCR_PSEL_MASK                      0x38u
#define CMP_MUXCR_PSEL_SHIFT                     3
#define CMP_MUXCR_PSEL_WIDTH                     3
#define CMP_MUXCR_PSEL(x)                        (((uint8_t)(((uint8_t)(x))<<CMP_MUXCR_PSEL_SHIFT))&CMP_MUXCR_PSEL_MASK)

/*!
 * @}
 */ /* end of group CMP_Register_Masks */


/* CMP - Peripheral instance base addresses */
/** Peripheral CMP0 base address */
#define CMP0_BASE                                (0x40072000u)
/** Peripheral CMP0 base pointer */
#define CMP0                                     ((CMP_Type *)CMP0_BASE)
#define CMP0_BASE_PTR                            (CMP0)
/** Peripheral CMP1 base address */
#define CMP1_BASE                                (0x40072008u)
/** Peripheral CMP1 base pointer */
#define CMP1                                     ((CMP_Type *)CMP1_BASE)
#define CMP1_BASE_PTR                            (CMP1)
/** Peripheral CMP2 base address */
#define CMP2_BASE                                (0x40072010u)
/** Peripheral CMP2 base pointer */
#define CMP2                                     ((CMP_Type *)CMP2_BASE)
#define CMP2_BASE_PTR                            (CMP2)
/** Array initializer of CMP peripheral base addresses */
#define CMP_BASE_ADDRS                           { CMP0_BASE, CMP1_BASE, CMP2_BASE }
/** Array initializer of CMP peripheral base pointers */
#define CMP_BASE_PTRS                            { CMP0, CMP1, CMP2 }
/** Interrupt vectors for the CMP peripheral type */
#define CMP_IRQS                                 { CMP0_CMP1_CMP2_IRQn, CMP0_CMP1_CMP2_IRQn, CMP0_CMP1_CMP2_IRQn }

/* ----------------------------------------------------------------------------
   -- CMP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Register_Accessor_Macros CMP - Register accessor macros
 * @{
 */


/* CMP - Register instance definitions */
/* CMP0 */
#define CMP0_CR0                                 CMP_CR0_REG(CMP0)
#define CMP0_CR1                                 CMP_CR1_REG(CMP0)
#define CMP0_FPR                                 CMP_FPR_REG(CMP0)
#define CMP0_SCR                                 CMP_SCR_REG(CMP0)
#define CMP0_DACCR                               CMP_DACCR_REG(CMP0)
#define CMP0_MUXCR                               CMP_MUXCR_REG(CMP0)
/* CMP1 */
#define CMP1_CR0                                 CMP_CR0_REG(CMP1)
#define CMP1_CR1                                 CMP_CR1_REG(CMP1)
#define CMP1_FPR                                 CMP_FPR_REG(CMP1)
#define CMP1_SCR                                 CMP_SCR_REG(CMP1)
#define CMP1_DACCR                               CMP_DACCR_REG(CMP1)
#define CMP1_MUXCR                               CMP_MUXCR_REG(CMP1)
/* CMP2 */
#define CMP2_CR0                                 CMP_CR0_REG(CMP2)
#define CMP2_CR1                                 CMP_CR1_REG(CMP2)
#define CMP2_FPR                                 CMP_FPR_REG(CMP2)
#define CMP2_SCR                                 CMP_SCR_REG(CMP2)
#define CMP2_DACCR                               CMP_DACCR_REG(CMP2)
#define CMP2_MUXCR                               CMP_MUXCR_REG(CMP2)

/*!
 * @}
 */ /* end of group CMP_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CMP_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CRC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Peripheral_Access_Layer CRC Peripheral Access Layer
 * @{
 */

/** CRC - Register Layout Typedef */
typedef struct {
  union {                                          /* offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      __IO uint16_t DATAL;                             /**< CRC_DATAL register., offset: 0x0 */
      __IO uint16_t DATAH;                             /**< CRC_DATAH register., offset: 0x2 */
    } ACCESS16BIT;
    __IO uint32_t DATA;                              /**< CRC Data register, offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      __IO uint8_t DATALL;                             /**< CRC_DATALL register., offset: 0x0 */
      __IO uint8_t DATALU;                             /**< CRC_DATALU register., offset: 0x1 */
      __IO uint8_t DATAHL;                             /**< CRC_DATAHL register., offset: 0x2 */
      __IO uint8_t DATAHU;                             /**< CRC_DATAHU register., offset: 0x3 */
    } ACCESS8BIT;
  };
  union {                                          /* offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      __IO uint16_t GPOLYL;                            /**< CRC_GPOLYL register., offset: 0x4 */
      __IO uint16_t GPOLYH;                            /**< CRC_GPOLYH register., offset: 0x6 */
    } GPOLY_ACCESS16BIT;
    __IO uint32_t GPOLY;                             /**< CRC Polynomial register, offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      __IO uint8_t GPOLYLL;                            /**< CRC_GPOLYLL register., offset: 0x4 */
      __IO uint8_t GPOLYLU;                            /**< CRC_GPOLYLU register., offset: 0x5 */
      __IO uint8_t GPOLYHL;                            /**< CRC_GPOLYHL register., offset: 0x6 */
      __IO uint8_t GPOLYHU;                            /**< CRC_GPOLYHU register., offset: 0x7 */
    } GPOLY_ACCESS8BIT;
  };
  union {                                          /* offset: 0x8 */
    __IO uint32_t CTRL;                              /**< CRC Control register, offset: 0x8 */
    struct {                                         /* offset: 0x8 */
           uint8_t RESERVED_0[3];
      __IO uint8_t CTRLHU;                             /**< CRC_CTRLHU register., offset: 0xB */
    } CTRL_ACCESS8BIT;
  };
} CRC_Type, *CRC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CRC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Accessor_Macros CRC - Register accessor macros
 * @{
 */


/* CRC - Register accessors */
#define CRC_DATAL_REG(base)                      ((base)->ACCESS16BIT.DATAL)
#define CRC_DATAH_REG(base)                      ((base)->ACCESS16BIT.DATAH)
#define CRC_DATA_REG(base)                       ((base)->DATA)
#define CRC_DATALL_REG(base)                     ((base)->ACCESS8BIT.DATALL)
#define CRC_DATALU_REG(base)                     ((base)->ACCESS8BIT.DATALU)
#define CRC_DATAHL_REG(base)                     ((base)->ACCESS8BIT.DATAHL)
#define CRC_DATAHU_REG(base)                     ((base)->ACCESS8BIT.DATAHU)
#define CRC_GPOLYL_REG(base)                     ((base)->GPOLY_ACCESS16BIT.GPOLYL)
#define CRC_GPOLYH_REG(base)                     ((base)->GPOLY_ACCESS16BIT.GPOLYH)
#define CRC_GPOLY_REG(base)                      ((base)->GPOLY)
#define CRC_GPOLYLL_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYLL)
#define CRC_GPOLYLU_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYLU)
#define CRC_GPOLYHL_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYHL)
#define CRC_GPOLYHU_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYHU)
#define CRC_CTRL_REG(base)                       ((base)->CTRL)
#define CRC_CTRLHU_REG(base)                     ((base)->CTRL_ACCESS8BIT.CTRLHU)

/*!
 * @}
 */ /* end of group CRC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CRC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Masks CRC Register Masks
 * @{
 */

/* DATAL Bit Fields */
#define CRC_DATAL_DATAL_MASK                     0xFFFFu
#define CRC_DATAL_DATAL_SHIFT                    0
#define CRC_DATAL_DATAL_WIDTH                    16
#define CRC_DATAL_DATAL(x)                       (((uint16_t)(((uint16_t)(x))<<CRC_DATAL_DATAL_SHIFT))&CRC_DATAL_DATAL_MASK)
/* DATAH Bit Fields */
#define CRC_DATAH_DATAH_MASK                     0xFFFFu
#define CRC_DATAH_DATAH_SHIFT                    0
#define CRC_DATAH_DATAH_WIDTH                    16
#define CRC_DATAH_DATAH(x)                       (((uint16_t)(((uint16_t)(x))<<CRC_DATAH_DATAH_SHIFT))&CRC_DATAH_DATAH_MASK)
/* DATA Bit Fields */
#define CRC_DATA_LL_MASK                         0xFFu
#define CRC_DATA_LL_SHIFT                        0
#define CRC_DATA_LL_WIDTH                        8
#define CRC_DATA_LL(x)                           (((uint32_t)(((uint32_t)(x))<<CRC_DATA_LL_SHIFT))&CRC_DATA_LL_MASK)
#define CRC_DATA_LU_MASK                         0xFF00u
#define CRC_DATA_LU_SHIFT                        8
#define CRC_DATA_LU_WIDTH                        8
#define CRC_DATA_LU(x)                           (((uint32_t)(((uint32_t)(x))<<CRC_DATA_LU_SHIFT))&CRC_DATA_LU_MASK)
#define CRC_DATA_HL_MASK                         0xFF0000u
#define CRC_DATA_HL_SHIFT                        16
#define CRC_DATA_HL_WIDTH                        8
#define CRC_DATA_HL(x)                           (((uint32_t)(((uint32_t)(x))<<CRC_DATA_HL_SHIFT))&CRC_DATA_HL_MASK)
#define CRC_DATA_HU_MASK                         0xFF000000u
#define CRC_DATA_HU_SHIFT                        24
#define CRC_DATA_HU_WIDTH                        8
#define CRC_DATA_HU(x)                           (((uint32_t)(((uint32_t)(x))<<CRC_DATA_HU_SHIFT))&CRC_DATA_HU_MASK)
/* DATALL Bit Fields */
#define CRC_DATALL_DATALL_MASK                   0xFFu
#define CRC_DATALL_DATALL_SHIFT                  0
#define CRC_DATALL_DATALL_WIDTH                  8
#define CRC_DATALL_DATALL(x)                     (((uint8_t)(((uint8_t)(x))<<CRC_DATALL_DATALL_SHIFT))&CRC_DATALL_DATALL_MASK)
/* DATALU Bit Fields */
#define CRC_DATALU_DATALU_MASK                   0xFFu
#define CRC_DATALU_DATALU_SHIFT                  0
#define CRC_DATALU_DATALU_WIDTH                  8
#define CRC_DATALU_DATALU(x)                     (((uint8_t)(((uint8_t)(x))<<CRC_DATALU_DATALU_SHIFT))&CRC_DATALU_DATALU_MASK)
/* DATAHL Bit Fields */
#define CRC_DATAHL_DATAHL_MASK                   0xFFu
#define CRC_DATAHL_DATAHL_SHIFT                  0
#define CRC_DATAHL_DATAHL_WIDTH                  8
#define CRC_DATAHL_DATAHL(x)                     (((uint8_t)(((uint8_t)(x))<<CRC_DATAHL_DATAHL_SHIFT))&CRC_DATAHL_DATAHL_MASK)
/* DATAHU Bit Fields */
#define CRC_DATAHU_DATAHU_MASK                   0xFFu
#define CRC_DATAHU_DATAHU_SHIFT                  0
#define CRC_DATAHU_DATAHU_WIDTH                  8
#define CRC_DATAHU_DATAHU(x)                     (((uint8_t)(((uint8_t)(x))<<CRC_DATAHU_DATAHU_SHIFT))&CRC_DATAHU_DATAHU_MASK)
/* GPOLYL Bit Fields */
#define CRC_GPOLYL_GPOLYL_MASK                   0xFFFFu
#define CRC_GPOLYL_GPOLYL_SHIFT                  0
#define CRC_GPOLYL_GPOLYL_WIDTH                  16
#define CRC_GPOLYL_GPOLYL(x)                     (((uint16_t)(((uint16_t)(x))<<CRC_GPOLYL_GPOLYL_SHIFT))&CRC_GPOLYL_GPOLYL_MASK)
/* GPOLYH Bit Fields */
#define CRC_GPOLYH_GPOLYH_MASK                   0xFFFFu
#define CRC_GPOLYH_GPOLYH_SHIFT                  0
#define CRC_GPOLYH_GPOLYH_WIDTH                  16
#define CRC_GPOLYH_GPOLYH(x)                     (((uint16_t)(((uint16_t)(x))<<CRC_GPOLYH_GPOLYH_SHIFT))&CRC_GPOLYH_GPOLYH_MASK)
/* GPOLY Bit Fields */
#define CRC_GPOLY_LOW_MASK                       0xFFFFu
#define CRC_GPOLY_LOW_SHIFT                      0
#define CRC_GPOLY_LOW_WIDTH                      16
#define CRC_GPOLY_LOW(x)                         (((uint32_t)(((uint32_t)(x))<<CRC_GPOLY_LOW_SHIFT))&CRC_GPOLY_LOW_MASK)
#define CRC_GPOLY_HIGH_MASK                      0xFFFF0000u
#define CRC_GPOLY_HIGH_SHIFT                     16
#define CRC_GPOLY_HIGH_WIDTH                     16
#define CRC_GPOLY_HIGH(x)                        (((uint32_t)(((uint32_t)(x))<<CRC_GPOLY_HIGH_SHIFT))&CRC_GPOLY_HIGH_MASK)
/* GPOLYLL Bit Fields */
#define CRC_GPOLYLL_GPOLYLL_MASK                 0xFFu
#define CRC_GPOLYLL_GPOLYLL_SHIFT                0
#define CRC_GPOLYLL_GPOLYLL_WIDTH                8
#define CRC_GPOLYLL_GPOLYLL(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYLL_GPOLYLL_SHIFT))&CRC_GPOLYLL_GPOLYLL_MASK)
/* GPOLYLU Bit Fields */
#define CRC_GPOLYLU_GPOLYLU_MASK                 0xFFu
#define CRC_GPOLYLU_GPOLYLU_SHIFT                0
#define CRC_GPOLYLU_GPOLYLU_WIDTH                8
#define CRC_GPOLYLU_GPOLYLU(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYLU_GPOLYLU_SHIFT))&CRC_GPOLYLU_GPOLYLU_MASK)
/* GPOLYHL Bit Fields */
#define CRC_GPOLYHL_GPOLYHL_MASK                 0xFFu
#define CRC_GPOLYHL_GPOLYHL_SHIFT                0
#define CRC_GPOLYHL_GPOLYHL_WIDTH                8
#define CRC_GPOLYHL_GPOLYHL(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYHL_GPOLYHL_SHIFT))&CRC_GPOLYHL_GPOLYHL_MASK)
/* GPOLYHU Bit Fields */
#define CRC_GPOLYHU_GPOLYHU_MASK                 0xFFu
#define CRC_GPOLYHU_GPOLYHU_SHIFT                0
#define CRC_GPOLYHU_GPOLYHU_WIDTH                8
#define CRC_GPOLYHU_GPOLYHU(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYHU_GPOLYHU_SHIFT))&CRC_GPOLYHU_GPOLYHU_MASK)
/* CTRL Bit Fields */
#define CRC_CTRL_TCRC_MASK                       0x1000000u
#define CRC_CTRL_TCRC_SHIFT                      24
#define CRC_CTRL_TCRC_WIDTH                      1
#define CRC_CTRL_TCRC(x)                         (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_TCRC_SHIFT))&CRC_CTRL_TCRC_MASK)
#define CRC_CTRL_WAS_MASK                        0x2000000u
#define CRC_CTRL_WAS_SHIFT                       25
#define CRC_CTRL_WAS_WIDTH                       1
#define CRC_CTRL_WAS(x)                          (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_WAS_SHIFT))&CRC_CTRL_WAS_MASK)
#define CRC_CTRL_FXOR_MASK                       0x4000000u
#define CRC_CTRL_FXOR_SHIFT                      26
#define CRC_CTRL_FXOR_WIDTH                      1
#define CRC_CTRL_FXOR(x)                         (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_FXOR_SHIFT))&CRC_CTRL_FXOR_MASK)
#define CRC_CTRL_TOTR_MASK                       0x30000000u
#define CRC_CTRL_TOTR_SHIFT                      28
#define CRC_CTRL_TOTR_WIDTH                      2
#define CRC_CTRL_TOTR(x)                         (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_TOTR_SHIFT))&CRC_CTRL_TOTR_MASK)
#define CRC_CTRL_TOT_MASK                        0xC0000000u
#define CRC_CTRL_TOT_SHIFT                       30
#define CRC_CTRL_TOT_WIDTH                       2
#define CRC_CTRL_TOT(x)                          (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_TOT_SHIFT))&CRC_CTRL_TOT_MASK)
/* CTRLHU Bit Fields */
#define CRC_CTRLHU_TCRC_MASK                     0x1u
#define CRC_CTRLHU_TCRC_SHIFT                    0
#define CRC_CTRLHU_TCRC_WIDTH                    1
#define CRC_CTRLHU_TCRC(x)                       (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_TCRC_SHIFT))&CRC_CTRLHU_TCRC_MASK)
#define CRC_CTRLHU_WAS_MASK                      0x2u
#define CRC_CTRLHU_WAS_SHIFT                     1
#define CRC_CTRLHU_WAS_WIDTH                     1
#define CRC_CTRLHU_WAS(x)                        (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_WAS_SHIFT))&CRC_CTRLHU_WAS_MASK)
#define CRC_CTRLHU_FXOR_MASK                     0x4u
#define CRC_CTRLHU_FXOR_SHIFT                    2
#define CRC_CTRLHU_FXOR_WIDTH                    1
#define CRC_CTRLHU_FXOR(x)                       (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_FXOR_SHIFT))&CRC_CTRLHU_FXOR_MASK)
#define CRC_CTRLHU_TOTR_MASK                     0x30u
#define CRC_CTRLHU_TOTR_SHIFT                    4
#define CRC_CTRLHU_TOTR_WIDTH                    2
#define CRC_CTRLHU_TOTR(x)                       (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_TOTR_SHIFT))&CRC_CTRLHU_TOTR_MASK)
#define CRC_CTRLHU_TOT_MASK                      0xC0u
#define CRC_CTRLHU_TOT_SHIFT                     6
#define CRC_CTRLHU_TOT_WIDTH                     2
#define CRC_CTRLHU_TOT(x)                        (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_TOT_SHIFT))&CRC_CTRLHU_TOT_MASK)

/*!
 * @}
 */ /* end of group CRC_Register_Masks */


/* CRC - Peripheral instance base addresses */
/** Peripheral CRC base address */
#define CRC_BASE                                 (0x40034000u)
/** Peripheral CRC base pointer */
#define CRC0                                     ((CRC_Type *)CRC_BASE)
#define CRC_BASE_PTR                             (CRC0)
/** Array initializer of CRC peripheral base addresses */
#define CRC_BASE_ADDRS                           { CRC_BASE }
/** Array initializer of CRC peripheral base pointers */
#define CRC_BASE_PTRS                            { CRC0 }

/* ----------------------------------------------------------------------------
   -- CRC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Accessor_Macros CRC - Register accessor macros
 * @{
 */


/* CRC - Register instance definitions */
/* CRC */
#define CRC_DATA                                 CRC_DATA_REG(CRC0)
#define CRC_DATAL                                CRC_DATAL_REG(CRC0)
#define CRC_DATALL                               CRC_DATALL_REG(CRC0)
#define CRC_DATALU                               CRC_DATALU_REG(CRC0)
#define CRC_DATAH                                CRC_DATAH_REG(CRC0)
#define CRC_DATAHL                               CRC_DATAHL_REG(CRC0)
#define CRC_DATAHU                               CRC_DATAHU_REG(CRC0)
#define CRC_GPOLY                                CRC_GPOLY_REG(CRC0)
#define CRC_GPOLYL                               CRC_GPOLYL_REG(CRC0)
#define CRC_GPOLYLL                              CRC_GPOLYLL_REG(CRC0)
#define CRC_GPOLYLU                              CRC_GPOLYLU_REG(CRC0)
#define CRC_GPOLYH                               CRC_GPOLYH_REG(CRC0)
#define CRC_GPOLYHL                              CRC_GPOLYHL_REG(CRC0)
#define CRC_GPOLYHU                              CRC_GPOLYHU_REG(CRC0)
#define CRC_CTRL                                 CRC_CTRL_REG(CRC0)
#define CRC_CTRLHU                               CRC_CTRLHU_REG(CRC0)

/*!
 * @}
 */ /* end of group CRC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CRC_Peripheral_Access_Layer */


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
      __IO uint32_t DSR_BCR;                           /**< DMA Status Register / Byte Count Register, array offset: 0x108, array step: 0x10 */
      struct {                                         /* offset: 0x108, array step: 0x10 */
             uint8_t RESERVED_0[3];
        __IO uint8_t DSR;                                /**< DMA_DSR0 register...DMA_DSR3 register., array offset: 0x10B, array step: 0x10 */
      } DMA_DSR_ACCESS8BIT;
    };
    __IO uint32_t DCR;                               /**< DMA Control Register, array offset: 0x10C, array step: 0x10 */
  } DMA[4];
} DMA_Type, *DMA_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DMA - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Accessor_Macros DMA - Register accessor macros
 * @{
 */


/* DMA - Register accessors */
#define DMA_SAR_REG(base,index)                  ((base)->DMA[index].SAR)
#define DMA_SAR_COUNT                            4
#define DMA_DAR_REG(base,index)                  ((base)->DMA[index].DAR)
#define DMA_DAR_COUNT                            4
#define DMA_DSR_BCR_REG(base,index)              ((base)->DMA[index].DSR_BCR)
#define DMA_DSR_BCR_COUNT                        4
#define DMA_DSR_REG(base,index)                  ((base)->DMA[index].DMA_DSR_ACCESS8BIT.DSR)
#define DMA_DSR_COUNT                            4
#define DMA_DCR_REG(base,index)                  ((base)->DMA[index].DCR)
#define DMA_DCR_COUNT                            4

/*!
 * @}
 */ /* end of group DMA_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- DMA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Masks DMA Register Masks
 * @{
 */

/* SAR Bit Fields */
#define DMA_SAR_SAR_MASK                         0xFFFFFFFFu
#define DMA_SAR_SAR_SHIFT                        0
#define DMA_SAR_SAR_WIDTH                        32
#define DMA_SAR_SAR(x)                           (((uint32_t)(((uint32_t)(x))<<DMA_SAR_SAR_SHIFT))&DMA_SAR_SAR_MASK)
/* DAR Bit Fields */
#define DMA_DAR_DAR_MASK                         0xFFFFFFFFu
#define DMA_DAR_DAR_SHIFT                        0
#define DMA_DAR_DAR_WIDTH                        32
#define DMA_DAR_DAR(x)                           (((uint32_t)(((uint32_t)(x))<<DMA_DAR_DAR_SHIFT))&DMA_DAR_DAR_MASK)
/* DSR_BCR Bit Fields */
#define DMA_DSR_BCR_BCR_MASK                     0xFFFFFFu
#define DMA_DSR_BCR_BCR_SHIFT                    0
#define DMA_DSR_BCR_BCR_WIDTH                    24
#define DMA_DSR_BCR_BCR(x)                       (((uint32_t)(((uint32_t)(x))<<DMA_DSR_BCR_BCR_SHIFT))&DMA_DSR_BCR_BCR_MASK)
#define DMA_DSR_BCR_DONE_MASK                    0x1000000u
#define DMA_DSR_BCR_DONE_SHIFT                   24
#define DMA_DSR_BCR_DONE_WIDTH                   1
#define DMA_DSR_BCR_DONE(x)                      (((uint32_t)(((uint32_t)(x))<<DMA_DSR_BCR_DONE_SHIFT))&DMA_DSR_BCR_DONE_MASK)
#define DMA_DSR_BCR_BSY_MASK                     0x2000000u
#define DMA_DSR_BCR_BSY_SHIFT                    25
#define DMA_DSR_BCR_BSY_WIDTH                    1
#define DMA_DSR_BCR_BSY(x)                       (((uint32_t)(((uint32_t)(x))<<DMA_DSR_BCR_BSY_SHIFT))&DMA_DSR_BCR_BSY_MASK)
#define DMA_DSR_BCR_REQ_MASK                     0x4000000u
#define DMA_DSR_BCR_REQ_SHIFT                    26
#define DMA_DSR_BCR_REQ_WIDTH                    1
#define DMA_DSR_BCR_REQ(x)                       (((uint32_t)(((uint32_t)(x))<<DMA_DSR_BCR_REQ_SHIFT))&DMA_DSR_BCR_REQ_MASK)
#define DMA_DSR_BCR_BED_MASK                     0x10000000u
#define DMA_DSR_BCR_BED_SHIFT                    28
#define DMA_DSR_BCR_BED_WIDTH                    1
#define DMA_DSR_BCR_BED(x)                       (((uint32_t)(((uint32_t)(x))<<DMA_DSR_BCR_BED_SHIFT))&DMA_DSR_BCR_BED_MASK)
#define DMA_DSR_BCR_BES_MASK                     0x20000000u
#define DMA_DSR_BCR_BES_SHIFT                    29
#define DMA_DSR_BCR_BES_WIDTH                    1
#define DMA_DSR_BCR_BES(x)                       (((uint32_t)(((uint32_t)(x))<<DMA_DSR_BCR_BES_SHIFT))&DMA_DSR_BCR_BES_MASK)
#define DMA_DSR_BCR_CE_MASK                      0x40000000u
#define DMA_DSR_BCR_CE_SHIFT                     30
#define DMA_DSR_BCR_CE_WIDTH                     1
#define DMA_DSR_BCR_CE(x)                        (((uint32_t)(((uint32_t)(x))<<DMA_DSR_BCR_CE_SHIFT))&DMA_DSR_BCR_CE_MASK)
/* DCR Bit Fields */
#define DMA_DCR_LCH2_MASK                        0x3u
#define DMA_DCR_LCH2_SHIFT                       0
#define DMA_DCR_LCH2_WIDTH                       2
#define DMA_DCR_LCH2(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_DCR_LCH2_SHIFT))&DMA_DCR_LCH2_MASK)
#define DMA_DCR_LCH1_MASK                        0xCu
#define DMA_DCR_LCH1_SHIFT                       2
#define DMA_DCR_LCH1_WIDTH                       2
#define DMA_DCR_LCH1(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_DCR_LCH1_SHIFT))&DMA_DCR_LCH1_MASK)
#define DMA_DCR_LINKCC_MASK                      0x30u
#define DMA_DCR_LINKCC_SHIFT                     4
#define DMA_DCR_LINKCC_WIDTH                     2
#define DMA_DCR_LINKCC(x)                        (((uint32_t)(((uint32_t)(x))<<DMA_DCR_LINKCC_SHIFT))&DMA_DCR_LINKCC_MASK)
#define DMA_DCR_D_REQ_MASK                       0x80u
#define DMA_DCR_D_REQ_SHIFT                      7
#define DMA_DCR_D_REQ_WIDTH                      1
#define DMA_DCR_D_REQ(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_DCR_D_REQ_SHIFT))&DMA_DCR_D_REQ_MASK)
#define DMA_DCR_DMOD_MASK                        0xF00u
#define DMA_DCR_DMOD_SHIFT                       8
#define DMA_DCR_DMOD_WIDTH                       4
#define DMA_DCR_DMOD(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_DCR_DMOD_SHIFT))&DMA_DCR_DMOD_MASK)
#define DMA_DCR_SMOD_MASK                        0xF000u
#define DMA_DCR_SMOD_SHIFT                       12
#define DMA_DCR_SMOD_WIDTH                       4
#define DMA_DCR_SMOD(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_DCR_SMOD_SHIFT))&DMA_DCR_SMOD_MASK)
#define DMA_DCR_START_MASK                       0x10000u
#define DMA_DCR_START_SHIFT                      16
#define DMA_DCR_START_WIDTH                      1
#define DMA_DCR_START(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_DCR_START_SHIFT))&DMA_DCR_START_MASK)
#define DMA_DCR_DSIZE_MASK                       0x60000u
#define DMA_DCR_DSIZE_SHIFT                      17
#define DMA_DCR_DSIZE_WIDTH                      2
#define DMA_DCR_DSIZE(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_DCR_DSIZE_SHIFT))&DMA_DCR_DSIZE_MASK)
#define DMA_DCR_DINC_MASK                        0x80000u
#define DMA_DCR_DINC_SHIFT                       19
#define DMA_DCR_DINC_WIDTH                       1
#define DMA_DCR_DINC(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_DCR_DINC_SHIFT))&DMA_DCR_DINC_MASK)
#define DMA_DCR_SSIZE_MASK                       0x300000u
#define DMA_DCR_SSIZE_SHIFT                      20
#define DMA_DCR_SSIZE_WIDTH                      2
#define DMA_DCR_SSIZE(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_DCR_SSIZE_SHIFT))&DMA_DCR_SSIZE_MASK)
#define DMA_DCR_SINC_MASK                        0x400000u
#define DMA_DCR_SINC_SHIFT                       22
#define DMA_DCR_SINC_WIDTH                       1
#define DMA_DCR_SINC(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_DCR_SINC_SHIFT))&DMA_DCR_SINC_MASK)
#define DMA_DCR_EADREQ_MASK                      0x800000u
#define DMA_DCR_EADREQ_SHIFT                     23
#define DMA_DCR_EADREQ_WIDTH                     1
#define DMA_DCR_EADREQ(x)                        (((uint32_t)(((uint32_t)(x))<<DMA_DCR_EADREQ_SHIFT))&DMA_DCR_EADREQ_MASK)
#define DMA_DCR_UMNSM_MASK                       0x3000000u
#define DMA_DCR_UMNSM_SHIFT                      24
#define DMA_DCR_UMNSM_WIDTH                      2
#define DMA_DCR_UMNSM(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_DCR_UMNSM_SHIFT))&DMA_DCR_UMNSM_MASK)
#define DMA_DCR_CHACR_MASK                       0xC000000u
#define DMA_DCR_CHACR_SHIFT                      26
#define DMA_DCR_CHACR_WIDTH                      2
#define DMA_DCR_CHACR(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_DCR_CHACR_SHIFT))&DMA_DCR_CHACR_MASK)
#define DMA_DCR_AA_MASK                          0x10000000u
#define DMA_DCR_AA_SHIFT                         28
#define DMA_DCR_AA_WIDTH                         1
#define DMA_DCR_AA(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_DCR_AA_SHIFT))&DMA_DCR_AA_MASK)
#define DMA_DCR_CS_MASK                          0x20000000u
#define DMA_DCR_CS_SHIFT                         29
#define DMA_DCR_CS_WIDTH                         1
#define DMA_DCR_CS(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_DCR_CS_SHIFT))&DMA_DCR_CS_MASK)
#define DMA_DCR_ERQ_MASK                         0x40000000u
#define DMA_DCR_ERQ_SHIFT                        30
#define DMA_DCR_ERQ_WIDTH                        1
#define DMA_DCR_ERQ(x)                           (((uint32_t)(((uint32_t)(x))<<DMA_DCR_ERQ_SHIFT))&DMA_DCR_ERQ_MASK)
#define DMA_DCR_EINT_MASK                        0x80000000u
#define DMA_DCR_EINT_SHIFT                       31
#define DMA_DCR_EINT_WIDTH                       1
#define DMA_DCR_EINT(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_DCR_EINT_SHIFT))&DMA_DCR_EINT_MASK)

/*!
 * @}
 */ /* end of group DMA_Register_Masks */


/* DMA - Peripheral instance base addresses */
/** Peripheral DMA base address */
#define DMA_BASE                                 (0x40008000u)
/** Peripheral DMA base pointer */
#define DMA0                                     ((DMA_Type *)DMA_BASE)
#define DMA_BASE_PTR                             (DMA0)
/** Array initializer of DMA peripheral base addresses */
#define DMA_BASE_ADDRS                           { DMA_BASE }
/** Array initializer of DMA peripheral base pointers */
#define DMA_BASE_PTRS                            { DMA0 }
/** Interrupt vectors for the DMA peripheral type */
#define DMA_CHN_IRQS                             { DMA0_IRQn, DMA1_IRQn, DMA2_IRQn, DMA3_IRQn }

/* ----------------------------------------------------------------------------
   -- DMA - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Accessor_Macros DMA - Register accessor macros
 * @{
 */


/* DMA - Register instance definitions */
/* DMA */
#define DMA_SAR0                                 DMA_SAR_REG(DMA0,0)
#define DMA_DAR0                                 DMA_DAR_REG(DMA0,0)
#define DMA_DSR_BCR0                             DMA_DSR_BCR_REG(DMA0,0)
#define DMA_DSR0                                 DMA_DSR_REG(DMA0,0)
#define DMA_DCR0                                 DMA_DCR_REG(DMA0,0)
#define DMA_SAR1                                 DMA_SAR_REG(DMA0,1)
#define DMA_DAR1                                 DMA_DAR_REG(DMA0,1)
#define DMA_DSR_BCR1                             DMA_DSR_BCR_REG(DMA0,1)
#define DMA_DSR1                                 DMA_DSR_REG(DMA0,1)
#define DMA_DCR1                                 DMA_DCR_REG(DMA0,1)
#define DMA_SAR2                                 DMA_SAR_REG(DMA0,2)
#define DMA_DAR2                                 DMA_DAR_REG(DMA0,2)
#define DMA_DSR_BCR2                             DMA_DSR_BCR_REG(DMA0,2)
#define DMA_DSR2                                 DMA_DSR_REG(DMA0,2)
#define DMA_DCR2                                 DMA_DCR_REG(DMA0,2)
#define DMA_SAR3                                 DMA_SAR_REG(DMA0,3)
#define DMA_DAR3                                 DMA_DAR_REG(DMA0,3)
#define DMA_DSR_BCR3                             DMA_DSR_BCR_REG(DMA0,3)
#define DMA_DSR3                                 DMA_DSR_REG(DMA0,3)
#define DMA_DCR3                                 DMA_DCR_REG(DMA0,3)

/* DMA - Register array accessors */
#define DMA_SAR(index)                           DMA_SAR_REG(DMA0,index)
#define DMA_DAR(index)                           DMA_DAR_REG(DMA0,index)
#define DMA_DSR_BCR(index)                       DMA_DSR_BCR_REG(DMA0,index)
#define DMA_DSR(index)                           DMA_DSR_REG(DMA0,index)
#define DMA_DCR(index)                           DMA_DCR_REG(DMA0,index)

/*!
 * @}
 */ /* end of group DMA_Register_Accessor_Macros */


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
} DMAMUX_Type, *DMAMUX_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DMAMUX - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Register_Accessor_Macros DMAMUX - Register accessor macros
 * @{
 */


/* DMAMUX - Register accessors */
#define DMAMUX_CHCFG_REG(base,index)             ((base)->CHCFG[index])
#define DMAMUX_CHCFG_COUNT                       4

/*!
 * @}
 */ /* end of group DMAMUX_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- DMAMUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Register_Masks DMAMUX Register Masks
 * @{
 */

/* CHCFG Bit Fields */
#define DMAMUX_CHCFG_SOURCE_MASK                 0x3Fu
#define DMAMUX_CHCFG_SOURCE_SHIFT                0
#define DMAMUX_CHCFG_SOURCE_WIDTH                6
#define DMAMUX_CHCFG_SOURCE(x)                   (((uint8_t)(((uint8_t)(x))<<DMAMUX_CHCFG_SOURCE_SHIFT))&DMAMUX_CHCFG_SOURCE_MASK)
#define DMAMUX_CHCFG_TRIG_MASK                   0x40u
#define DMAMUX_CHCFG_TRIG_SHIFT                  6
#define DMAMUX_CHCFG_TRIG_WIDTH                  1
#define DMAMUX_CHCFG_TRIG(x)                     (((uint8_t)(((uint8_t)(x))<<DMAMUX_CHCFG_TRIG_SHIFT))&DMAMUX_CHCFG_TRIG_MASK)
#define DMAMUX_CHCFG_ENBL_MASK                   0x80u
#define DMAMUX_CHCFG_ENBL_SHIFT                  7
#define DMAMUX_CHCFG_ENBL_WIDTH                  1
#define DMAMUX_CHCFG_ENBL(x)                     (((uint8_t)(((uint8_t)(x))<<DMAMUX_CHCFG_ENBL_SHIFT))&DMAMUX_CHCFG_ENBL_MASK)

/*!
 * @}
 */ /* end of group DMAMUX_Register_Masks */


/* DMAMUX - Peripheral instance base addresses */
/** Peripheral DMAMUX0 base address */
#define DMAMUX0_BASE                             (0x40021000u)
/** Peripheral DMAMUX0 base pointer */
#define DMAMUX0                                  ((DMAMUX_Type *)DMAMUX0_BASE)
#define DMAMUX0_BASE_PTR                         (DMAMUX0)
/** Array initializer of DMAMUX peripheral base addresses */
#define DMAMUX_BASE_ADDRS                        { DMAMUX0_BASE }
/** Array initializer of DMAMUX peripheral base pointers */
#define DMAMUX_BASE_PTRS                         { DMAMUX0 }

/* ----------------------------------------------------------------------------
   -- DMAMUX - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Register_Accessor_Macros DMAMUX - Register accessor macros
 * @{
 */


/* DMAMUX - Register instance definitions */
/* DMAMUX0 */
#define DMAMUX_CHCFG0                            DMAMUX_CHCFG_REG(DMAMUX0,0)
#define DMAMUX_CHCFG1                            DMAMUX_CHCFG_REG(DMAMUX0,1)
#define DMAMUX_CHCFG2                            DMAMUX_CHCFG_REG(DMAMUX0,2)
#define DMAMUX_CHCFG3                            DMAMUX_CHCFG_REG(DMAMUX0,3)

/* DMAMUX - Register array accessors */
#define DMAMUX0_CHCFG(index)                     DMAMUX_CHCFG_REG(DMAMUX0,index)

/*!
 * @}
 */ /* end of group DMAMUX_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group DMAMUX_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- EWM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EWM_Peripheral_Access_Layer EWM Peripheral Access Layer
 * @{
 */

/** EWM - Register Layout Typedef */
typedef struct {
  __IO uint8_t CTRL;                               /**< Control Register, offset: 0x0 */
  __O  uint8_t SERV;                               /**< Service Register, offset: 0x1 */
  __IO uint8_t CMPL;                               /**< Compare Low Register, offset: 0x2 */
  __IO uint8_t CMPH;                               /**< Compare High Register, offset: 0x3 */
  __IO uint8_t CLKCTRL;                            /**< Clock Control Register, offset: 0x4 */
  __IO uint8_t CLKPRESCALER;                       /**< Clock Prescaler Register, offset: 0x5 */
} EWM_Type, *EWM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- EWM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EWM_Register_Accessor_Macros EWM - Register accessor macros
 * @{
 */


/* EWM - Register accessors */
#define EWM_CTRL_REG(base)                       ((base)->CTRL)
#define EWM_SERV_REG(base)                       ((base)->SERV)
#define EWM_CMPL_REG(base)                       ((base)->CMPL)
#define EWM_CMPH_REG(base)                       ((base)->CMPH)
#define EWM_CLKCTRL_REG(base)                    ((base)->CLKCTRL)
#define EWM_CLKPRESCALER_REG(base)               ((base)->CLKPRESCALER)

/*!
 * @}
 */ /* end of group EWM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- EWM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EWM_Register_Masks EWM Register Masks
 * @{
 */

/* CTRL Bit Fields */
#define EWM_CTRL_EWMEN_MASK                      0x1u
#define EWM_CTRL_EWMEN_SHIFT                     0
#define EWM_CTRL_EWMEN_WIDTH                     1
#define EWM_CTRL_EWMEN(x)                        (((uint8_t)(((uint8_t)(x))<<EWM_CTRL_EWMEN_SHIFT))&EWM_CTRL_EWMEN_MASK)
#define EWM_CTRL_ASSIN_MASK                      0x2u
#define EWM_CTRL_ASSIN_SHIFT                     1
#define EWM_CTRL_ASSIN_WIDTH                     1
#define EWM_CTRL_ASSIN(x)                        (((uint8_t)(((uint8_t)(x))<<EWM_CTRL_ASSIN_SHIFT))&EWM_CTRL_ASSIN_MASK)
#define EWM_CTRL_INEN_MASK                       0x4u
#define EWM_CTRL_INEN_SHIFT                      2
#define EWM_CTRL_INEN_WIDTH                      1
#define EWM_CTRL_INEN(x)                         (((uint8_t)(((uint8_t)(x))<<EWM_CTRL_INEN_SHIFT))&EWM_CTRL_INEN_MASK)
#define EWM_CTRL_INTEN_MASK                      0x8u
#define EWM_CTRL_INTEN_SHIFT                     3
#define EWM_CTRL_INTEN_WIDTH                     1
#define EWM_CTRL_INTEN(x)                        (((uint8_t)(((uint8_t)(x))<<EWM_CTRL_INTEN_SHIFT))&EWM_CTRL_INTEN_MASK)
/* SERV Bit Fields */
#define EWM_SERV_SERVICE_MASK                    0xFFu
#define EWM_SERV_SERVICE_SHIFT                   0
#define EWM_SERV_SERVICE_WIDTH                   8
#define EWM_SERV_SERVICE(x)                      (((uint8_t)(((uint8_t)(x))<<EWM_SERV_SERVICE_SHIFT))&EWM_SERV_SERVICE_MASK)
/* CMPL Bit Fields */
#define EWM_CMPL_COMPAREL_MASK                   0xFFu
#define EWM_CMPL_COMPAREL_SHIFT                  0
#define EWM_CMPL_COMPAREL_WIDTH                  8
#define EWM_CMPL_COMPAREL(x)                     (((uint8_t)(((uint8_t)(x))<<EWM_CMPL_COMPAREL_SHIFT))&EWM_CMPL_COMPAREL_MASK)
/* CMPH Bit Fields */
#define EWM_CMPH_COMPAREH_MASK                   0xFFu
#define EWM_CMPH_COMPAREH_SHIFT                  0
#define EWM_CMPH_COMPAREH_WIDTH                  8
#define EWM_CMPH_COMPAREH(x)                     (((uint8_t)(((uint8_t)(x))<<EWM_CMPH_COMPAREH_SHIFT))&EWM_CMPH_COMPAREH_MASK)
/* CLKCTRL Bit Fields */
#define EWM_CLKCTRL_CLKSEL_MASK                  0x3u
#define EWM_CLKCTRL_CLKSEL_SHIFT                 0
#define EWM_CLKCTRL_CLKSEL_WIDTH                 2
#define EWM_CLKCTRL_CLKSEL(x)                    (((uint8_t)(((uint8_t)(x))<<EWM_CLKCTRL_CLKSEL_SHIFT))&EWM_CLKCTRL_CLKSEL_MASK)
/* CLKPRESCALER Bit Fields */
#define EWM_CLKPRESCALER_CLK_DIV_MASK            0xFFu
#define EWM_CLKPRESCALER_CLK_DIV_SHIFT           0
#define EWM_CLKPRESCALER_CLK_DIV_WIDTH           8
#define EWM_CLKPRESCALER_CLK_DIV(x)              (((uint8_t)(((uint8_t)(x))<<EWM_CLKPRESCALER_CLK_DIV_SHIFT))&EWM_CLKPRESCALER_CLK_DIV_MASK)

/*!
 * @}
 */ /* end of group EWM_Register_Masks */


/* EWM - Peripheral instance base addresses */
/** Peripheral EWM base address */
#define EWM_BASE                                 (0x40061000u)
/** Peripheral EWM base pointer */
#define EWM                                      ((EWM_Type *)EWM_BASE)
#define EWM_BASE_PTR                             (EWM)
/** Array initializer of EWM peripheral base addresses */
#define EWM_BASE_ADDRS                           { EWM_BASE }
/** Array initializer of EWM peripheral base pointers */
#define EWM_BASE_PTRS                            { EWM }
/** Interrupt vectors for the EWM peripheral type */
#define EWM_IRQS                                 { WDOG_EWM_IRQn }

/* ----------------------------------------------------------------------------
   -- EWM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EWM_Register_Accessor_Macros EWM - Register accessor macros
 * @{
 */


/* EWM - Register instance definitions */
/* EWM */
#define EWM_CTRL                                 EWM_CTRL_REG(EWM)
#define EWM_SERV                                 EWM_SERV_REG(EWM)
#define EWM_CMPL                                 EWM_CMPL_REG(EWM)
#define EWM_CMPH                                 EWM_CMPH_REG(EWM)
#define EWM_CLKCTRL                              EWM_CLKCTRL_REG(EWM)
#define EWM_CLKPRESCALER                         EWM_CLKPRESCALER_REG(EWM)

/*!
 * @}
 */ /* end of group EWM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group EWM_Peripheral_Access_Layer */


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
} FTFA_Type, *FTFA_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FTFA - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFA_Register_Accessor_Macros FTFA - Register accessor macros
 * @{
 */


/* FTFA - Register accessors */
#define FTFA_FSTAT_REG(base)                     ((base)->FSTAT)
#define FTFA_FCNFG_REG(base)                     ((base)->FCNFG)
#define FTFA_FSEC_REG(base)                      ((base)->FSEC)
#define FTFA_FOPT_REG(base)                      ((base)->FOPT)
#define FTFA_FCCOB3_REG(base)                    ((base)->FCCOB3)
#define FTFA_FCCOB2_REG(base)                    ((base)->FCCOB2)
#define FTFA_FCCOB1_REG(base)                    ((base)->FCCOB1)
#define FTFA_FCCOB0_REG(base)                    ((base)->FCCOB0)
#define FTFA_FCCOB7_REG(base)                    ((base)->FCCOB7)
#define FTFA_FCCOB6_REG(base)                    ((base)->FCCOB6)
#define FTFA_FCCOB5_REG(base)                    ((base)->FCCOB5)
#define FTFA_FCCOB4_REG(base)                    ((base)->FCCOB4)
#define FTFA_FCCOBB_REG(base)                    ((base)->FCCOBB)
#define FTFA_FCCOBA_REG(base)                    ((base)->FCCOBA)
#define FTFA_FCCOB9_REG(base)                    ((base)->FCCOB9)
#define FTFA_FCCOB8_REG(base)                    ((base)->FCCOB8)
#define FTFA_FPROT3_REG(base)                    ((base)->FPROT3)
#define FTFA_FPROT2_REG(base)                    ((base)->FPROT2)
#define FTFA_FPROT1_REG(base)                    ((base)->FPROT1)
#define FTFA_FPROT0_REG(base)                    ((base)->FPROT0)

/*!
 * @}
 */ /* end of group FTFA_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FTFA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFA_Register_Masks FTFA Register Masks
 * @{
 */

/* FSTAT Bit Fields */
#define FTFA_FSTAT_MGSTAT0_MASK                  0x1u
#define FTFA_FSTAT_MGSTAT0_SHIFT                 0
#define FTFA_FSTAT_MGSTAT0_WIDTH                 1
#define FTFA_FSTAT_MGSTAT0(x)                    (((uint8_t)(((uint8_t)(x))<<FTFA_FSTAT_MGSTAT0_SHIFT))&FTFA_FSTAT_MGSTAT0_MASK)
#define FTFA_FSTAT_FPVIOL_MASK                   0x10u
#define FTFA_FSTAT_FPVIOL_SHIFT                  4
#define FTFA_FSTAT_FPVIOL_WIDTH                  1
#define FTFA_FSTAT_FPVIOL(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FSTAT_FPVIOL_SHIFT))&FTFA_FSTAT_FPVIOL_MASK)
#define FTFA_FSTAT_ACCERR_MASK                   0x20u
#define FTFA_FSTAT_ACCERR_SHIFT                  5
#define FTFA_FSTAT_ACCERR_WIDTH                  1
#define FTFA_FSTAT_ACCERR(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FSTAT_ACCERR_SHIFT))&FTFA_FSTAT_ACCERR_MASK)
#define FTFA_FSTAT_RDCOLERR_MASK                 0x40u
#define FTFA_FSTAT_RDCOLERR_SHIFT                6
#define FTFA_FSTAT_RDCOLERR_WIDTH                1
#define FTFA_FSTAT_RDCOLERR(x)                   (((uint8_t)(((uint8_t)(x))<<FTFA_FSTAT_RDCOLERR_SHIFT))&FTFA_FSTAT_RDCOLERR_MASK)
#define FTFA_FSTAT_CCIF_MASK                     0x80u
#define FTFA_FSTAT_CCIF_SHIFT                    7
#define FTFA_FSTAT_CCIF_WIDTH                    1
#define FTFA_FSTAT_CCIF(x)                       (((uint8_t)(((uint8_t)(x))<<FTFA_FSTAT_CCIF_SHIFT))&FTFA_FSTAT_CCIF_MASK)
/* FCNFG Bit Fields */
#define FTFA_FCNFG_ERSSUSP_MASK                  0x10u
#define FTFA_FCNFG_ERSSUSP_SHIFT                 4
#define FTFA_FCNFG_ERSSUSP_WIDTH                 1
#define FTFA_FCNFG_ERSSUSP(x)                    (((uint8_t)(((uint8_t)(x))<<FTFA_FCNFG_ERSSUSP_SHIFT))&FTFA_FCNFG_ERSSUSP_MASK)
#define FTFA_FCNFG_ERSAREQ_MASK                  0x20u
#define FTFA_FCNFG_ERSAREQ_SHIFT                 5
#define FTFA_FCNFG_ERSAREQ_WIDTH                 1
#define FTFA_FCNFG_ERSAREQ(x)                    (((uint8_t)(((uint8_t)(x))<<FTFA_FCNFG_ERSAREQ_SHIFT))&FTFA_FCNFG_ERSAREQ_MASK)
#define FTFA_FCNFG_RDCOLLIE_MASK                 0x40u
#define FTFA_FCNFG_RDCOLLIE_SHIFT                6
#define FTFA_FCNFG_RDCOLLIE_WIDTH                1
#define FTFA_FCNFG_RDCOLLIE(x)                   (((uint8_t)(((uint8_t)(x))<<FTFA_FCNFG_RDCOLLIE_SHIFT))&FTFA_FCNFG_RDCOLLIE_MASK)
#define FTFA_FCNFG_CCIE_MASK                     0x80u
#define FTFA_FCNFG_CCIE_SHIFT                    7
#define FTFA_FCNFG_CCIE_WIDTH                    1
#define FTFA_FCNFG_CCIE(x)                       (((uint8_t)(((uint8_t)(x))<<FTFA_FCNFG_CCIE_SHIFT))&FTFA_FCNFG_CCIE_MASK)
/* FSEC Bit Fields */
#define FTFA_FSEC_SEC_MASK                       0x3u
#define FTFA_FSEC_SEC_SHIFT                      0
#define FTFA_FSEC_SEC_WIDTH                      2
#define FTFA_FSEC_SEC(x)                         (((uint8_t)(((uint8_t)(x))<<FTFA_FSEC_SEC_SHIFT))&FTFA_FSEC_SEC_MASK)
#define FTFA_FSEC_FSLACC_MASK                    0xCu
#define FTFA_FSEC_FSLACC_SHIFT                   2
#define FTFA_FSEC_FSLACC_WIDTH                   2
#define FTFA_FSEC_FSLACC(x)                      (((uint8_t)(((uint8_t)(x))<<FTFA_FSEC_FSLACC_SHIFT))&FTFA_FSEC_FSLACC_MASK)
#define FTFA_FSEC_MEEN_MASK                      0x30u
#define FTFA_FSEC_MEEN_SHIFT                     4
#define FTFA_FSEC_MEEN_WIDTH                     2
#define FTFA_FSEC_MEEN(x)                        (((uint8_t)(((uint8_t)(x))<<FTFA_FSEC_MEEN_SHIFT))&FTFA_FSEC_MEEN_MASK)
#define FTFA_FSEC_KEYEN_MASK                     0xC0u
#define FTFA_FSEC_KEYEN_SHIFT                    6
#define FTFA_FSEC_KEYEN_WIDTH                    2
#define FTFA_FSEC_KEYEN(x)                       (((uint8_t)(((uint8_t)(x))<<FTFA_FSEC_KEYEN_SHIFT))&FTFA_FSEC_KEYEN_MASK)
/* FOPT Bit Fields */
#define FTFA_FOPT_OPT_MASK                       0xFFu
#define FTFA_FOPT_OPT_SHIFT                      0
#define FTFA_FOPT_OPT_WIDTH                      8
#define FTFA_FOPT_OPT(x)                         (((uint8_t)(((uint8_t)(x))<<FTFA_FOPT_OPT_SHIFT))&FTFA_FOPT_OPT_MASK)
/* FCCOB3 Bit Fields */
#define FTFA_FCCOB3_CCOBn_MASK                   0xFFu
#define FTFA_FCCOB3_CCOBn_SHIFT                  0
#define FTFA_FCCOB3_CCOBn_WIDTH                  8
#define FTFA_FCCOB3_CCOBn(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FCCOB3_CCOBn_SHIFT))&FTFA_FCCOB3_CCOBn_MASK)
/* FCCOB2 Bit Fields */
#define FTFA_FCCOB2_CCOBn_MASK                   0xFFu
#define FTFA_FCCOB2_CCOBn_SHIFT                  0
#define FTFA_FCCOB2_CCOBn_WIDTH                  8
#define FTFA_FCCOB2_CCOBn(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FCCOB2_CCOBn_SHIFT))&FTFA_FCCOB2_CCOBn_MASK)
/* FCCOB1 Bit Fields */
#define FTFA_FCCOB1_CCOBn_MASK                   0xFFu
#define FTFA_FCCOB1_CCOBn_SHIFT                  0
#define FTFA_FCCOB1_CCOBn_WIDTH                  8
#define FTFA_FCCOB1_CCOBn(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FCCOB1_CCOBn_SHIFT))&FTFA_FCCOB1_CCOBn_MASK)
/* FCCOB0 Bit Fields */
#define FTFA_FCCOB0_CCOBn_MASK                   0xFFu
#define FTFA_FCCOB0_CCOBn_SHIFT                  0
#define FTFA_FCCOB0_CCOBn_WIDTH                  8
#define FTFA_FCCOB0_CCOBn(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FCCOB0_CCOBn_SHIFT))&FTFA_FCCOB0_CCOBn_MASK)
/* FCCOB7 Bit Fields */
#define FTFA_FCCOB7_CCOBn_MASK                   0xFFu
#define FTFA_FCCOB7_CCOBn_SHIFT                  0
#define FTFA_FCCOB7_CCOBn_WIDTH                  8
#define FTFA_FCCOB7_CCOBn(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FCCOB7_CCOBn_SHIFT))&FTFA_FCCOB7_CCOBn_MASK)
/* FCCOB6 Bit Fields */
#define FTFA_FCCOB6_CCOBn_MASK                   0xFFu
#define FTFA_FCCOB6_CCOBn_SHIFT                  0
#define FTFA_FCCOB6_CCOBn_WIDTH                  8
#define FTFA_FCCOB6_CCOBn(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FCCOB6_CCOBn_SHIFT))&FTFA_FCCOB6_CCOBn_MASK)
/* FCCOB5 Bit Fields */
#define FTFA_FCCOB5_CCOBn_MASK                   0xFFu
#define FTFA_FCCOB5_CCOBn_SHIFT                  0
#define FTFA_FCCOB5_CCOBn_WIDTH                  8
#define FTFA_FCCOB5_CCOBn(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FCCOB5_CCOBn_SHIFT))&FTFA_FCCOB5_CCOBn_MASK)
/* FCCOB4 Bit Fields */
#define FTFA_FCCOB4_CCOBn_MASK                   0xFFu
#define FTFA_FCCOB4_CCOBn_SHIFT                  0
#define FTFA_FCCOB4_CCOBn_WIDTH                  8
#define FTFA_FCCOB4_CCOBn(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FCCOB4_CCOBn_SHIFT))&FTFA_FCCOB4_CCOBn_MASK)
/* FCCOBB Bit Fields */
#define FTFA_FCCOBB_CCOBn_MASK                   0xFFu
#define FTFA_FCCOBB_CCOBn_SHIFT                  0
#define FTFA_FCCOBB_CCOBn_WIDTH                  8
#define FTFA_FCCOBB_CCOBn(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FCCOBB_CCOBn_SHIFT))&FTFA_FCCOBB_CCOBn_MASK)
/* FCCOBA Bit Fields */
#define FTFA_FCCOBA_CCOBn_MASK                   0xFFu
#define FTFA_FCCOBA_CCOBn_SHIFT                  0
#define FTFA_FCCOBA_CCOBn_WIDTH                  8
#define FTFA_FCCOBA_CCOBn(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FCCOBA_CCOBn_SHIFT))&FTFA_FCCOBA_CCOBn_MASK)
/* FCCOB9 Bit Fields */
#define FTFA_FCCOB9_CCOBn_MASK                   0xFFu
#define FTFA_FCCOB9_CCOBn_SHIFT                  0
#define FTFA_FCCOB9_CCOBn_WIDTH                  8
#define FTFA_FCCOB9_CCOBn(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FCCOB9_CCOBn_SHIFT))&FTFA_FCCOB9_CCOBn_MASK)
/* FCCOB8 Bit Fields */
#define FTFA_FCCOB8_CCOBn_MASK                   0xFFu
#define FTFA_FCCOB8_CCOBn_SHIFT                  0
#define FTFA_FCCOB8_CCOBn_WIDTH                  8
#define FTFA_FCCOB8_CCOBn(x)                     (((uint8_t)(((uint8_t)(x))<<FTFA_FCCOB8_CCOBn_SHIFT))&FTFA_FCCOB8_CCOBn_MASK)
/* FPROT3 Bit Fields */
#define FTFA_FPROT3_PROT_MASK                    0xFFu
#define FTFA_FPROT3_PROT_SHIFT                   0
#define FTFA_FPROT3_PROT_WIDTH                   8
#define FTFA_FPROT3_PROT(x)                      (((uint8_t)(((uint8_t)(x))<<FTFA_FPROT3_PROT_SHIFT))&FTFA_FPROT3_PROT_MASK)
/* FPROT2 Bit Fields */
#define FTFA_FPROT2_PROT_MASK                    0xFFu
#define FTFA_FPROT2_PROT_SHIFT                   0
#define FTFA_FPROT2_PROT_WIDTH                   8
#define FTFA_FPROT2_PROT(x)                      (((uint8_t)(((uint8_t)(x))<<FTFA_FPROT2_PROT_SHIFT))&FTFA_FPROT2_PROT_MASK)
/* FPROT1 Bit Fields */
#define FTFA_FPROT1_PROT_MASK                    0xFFu
#define FTFA_FPROT1_PROT_SHIFT                   0
#define FTFA_FPROT1_PROT_WIDTH                   8
#define FTFA_FPROT1_PROT(x)                      (((uint8_t)(((uint8_t)(x))<<FTFA_FPROT1_PROT_SHIFT))&FTFA_FPROT1_PROT_MASK)
/* FPROT0 Bit Fields */
#define FTFA_FPROT0_PROT_MASK                    0xFFu
#define FTFA_FPROT0_PROT_SHIFT                   0
#define FTFA_FPROT0_PROT_WIDTH                   8
#define FTFA_FPROT0_PROT(x)                      (((uint8_t)(((uint8_t)(x))<<FTFA_FPROT0_PROT_SHIFT))&FTFA_FPROT0_PROT_MASK)

/*!
 * @}
 */ /* end of group FTFA_Register_Masks */


/* FTFA - Peripheral instance base addresses */
/** Peripheral FTFA base address */
#define FTFA_BASE                                (0x40020000u)
/** Peripheral FTFA base pointer */
#define FTFA                                     ((FTFA_Type *)FTFA_BASE)
#define FTFA_BASE_PTR                            (FTFA)
/** Array initializer of FTFA peripheral base addresses */
#define FTFA_BASE_ADDRS                          { FTFA_BASE }
/** Array initializer of FTFA peripheral base pointers */
#define FTFA_BASE_PTRS                           { FTFA }
/** Interrupt vectors for the FTFA peripheral type */
#define FTFA_COMMAND_COMPLETE_IRQS               { FTFA_IRQn }

/* ----------------------------------------------------------------------------
   -- FTFA - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFA_Register_Accessor_Macros FTFA - Register accessor macros
 * @{
 */


/* FTFA - Register instance definitions */
/* FTFA */
#define FTFA_FSTAT                               FTFA_FSTAT_REG(FTFA)
#define FTFA_FCNFG                               FTFA_FCNFG_REG(FTFA)
#define FTFA_FSEC                                FTFA_FSEC_REG(FTFA)
#define FTFA_FOPT                                FTFA_FOPT_REG(FTFA)
#define FTFA_FCCOB3                              FTFA_FCCOB3_REG(FTFA)
#define FTFA_FCCOB2                              FTFA_FCCOB2_REG(FTFA)
#define FTFA_FCCOB1                              FTFA_FCCOB1_REG(FTFA)
#define FTFA_FCCOB0                              FTFA_FCCOB0_REG(FTFA)
#define FTFA_FCCOB7                              FTFA_FCCOB7_REG(FTFA)
#define FTFA_FCCOB6                              FTFA_FCCOB6_REG(FTFA)
#define FTFA_FCCOB5                              FTFA_FCCOB5_REG(FTFA)
#define FTFA_FCCOB4                              FTFA_FCCOB4_REG(FTFA)
#define FTFA_FCCOBB                              FTFA_FCCOBB_REG(FTFA)
#define FTFA_FCCOBA                              FTFA_FCCOBA_REG(FTFA)
#define FTFA_FCCOB9                              FTFA_FCCOB9_REG(FTFA)
#define FTFA_FCCOB8                              FTFA_FCCOB8_REG(FTFA)
#define FTFA_FPROT3                              FTFA_FPROT3_REG(FTFA)
#define FTFA_FPROT2                              FTFA_FPROT2_REG(FTFA)
#define FTFA_FPROT1                              FTFA_FPROT1_REG(FTFA)
#define FTFA_FPROT0                              FTFA_FPROT0_REG(FTFA)

/*!
 * @}
 */ /* end of group FTFA_Register_Accessor_Macros */


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
  __IO uint8_t PDOR;                               /**< Port Data Output Register, offset: 0x0 */
       uint8_t RESERVED_0[3];
  __O  uint8_t PSOR;                               /**< Port Set Output Register, offset: 0x4 */
       uint8_t RESERVED_1[3];
  __O  uint8_t PCOR;                               /**< Port Clear Output Register, offset: 0x8 */
       uint8_t RESERVED_2[3];
  __O  uint8_t PTOR;                               /**< Port Toggle Output Register, offset: 0xC */
       uint8_t RESERVED_3[3];
  __I  uint8_t PDIR;                               /**< Port Data Input Register, offset: 0x10 */
       uint8_t RESERVED_4[3];
  __IO uint8_t PDDR;                               /**< Port Data Direction Register, offset: 0x14 */
       uint8_t RESERVED_5[7];
  __IO uint8_t GACR;                               /**< GPIO Attribute Checker Register, offset: 0x1C */
} GPIO_Type, *GPIO_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- GPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Accessor_Macros GPIO - Register accessor macros
 * @{
 */


/* GPIO - Register accessors */
#define GPIO_PDOR_REG(base)                      ((base)->PDOR)
#define GPIO_PSOR_REG(base)                      ((base)->PSOR)
#define GPIO_PCOR_REG(base)                      ((base)->PCOR)
#define GPIO_PTOR_REG(base)                      ((base)->PTOR)
#define GPIO_PDIR_REG(base)                      ((base)->PDIR)
#define GPIO_PDDR_REG(base)                      ((base)->PDDR)
#define GPIO_GACR_REG(base)                      ((base)->GACR)

/*!
 * @}
 */ /* end of group GPIO_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Masks GPIO Register Masks
 * @{
 */

/* PDOR Bit Fields */
#define GPIO_PDOR_PDO_MASK                       0xFFu
#define GPIO_PDOR_PDO_SHIFT                      0
#define GPIO_PDOR_PDO_WIDTH                      8
#define GPIO_PDOR_PDO(x)                         (((uint8_t)(((uint8_t)(x))<<GPIO_PDOR_PDO_SHIFT))&GPIO_PDOR_PDO_MASK)
/* PSOR Bit Fields */
#define GPIO_PSOR_PTSO_MASK                      0xFFu
#define GPIO_PSOR_PTSO_SHIFT                     0
#define GPIO_PSOR_PTSO_WIDTH                     8
#define GPIO_PSOR_PTSO(x)                        (((uint8_t)(((uint8_t)(x))<<GPIO_PSOR_PTSO_SHIFT))&GPIO_PSOR_PTSO_MASK)
/* PCOR Bit Fields */
#define GPIO_PCOR_PTCO_MASK                      0xFFu
#define GPIO_PCOR_PTCO_SHIFT                     0
#define GPIO_PCOR_PTCO_WIDTH                     8
#define GPIO_PCOR_PTCO(x)                        (((uint8_t)(((uint8_t)(x))<<GPIO_PCOR_PTCO_SHIFT))&GPIO_PCOR_PTCO_MASK)
/* PTOR Bit Fields */
#define GPIO_PTOR_PTTO_MASK                      0xFFu
#define GPIO_PTOR_PTTO_SHIFT                     0
#define GPIO_PTOR_PTTO_WIDTH                     8
#define GPIO_PTOR_PTTO(x)                        (((uint8_t)(((uint8_t)(x))<<GPIO_PTOR_PTTO_SHIFT))&GPIO_PTOR_PTTO_MASK)
/* PDIR Bit Fields */
#define GPIO_PDIR_PDI_MASK                       0xFFu
#define GPIO_PDIR_PDI_SHIFT                      0
#define GPIO_PDIR_PDI_WIDTH                      8
#define GPIO_PDIR_PDI(x)                         (((uint8_t)(((uint8_t)(x))<<GPIO_PDIR_PDI_SHIFT))&GPIO_PDIR_PDI_MASK)
/* PDDR Bit Fields */
#define GPIO_PDDR_PDD_MASK                       0xFFu
#define GPIO_PDDR_PDD_SHIFT                      0
#define GPIO_PDDR_PDD_WIDTH                      8
#define GPIO_PDDR_PDD(x)                         (((uint8_t)(((uint8_t)(x))<<GPIO_PDDR_PDD_SHIFT))&GPIO_PDDR_PDD_MASK)
/* GACR Bit Fields */
#define GPIO_GACR_ACB_MASK                       0x7u
#define GPIO_GACR_ACB_SHIFT                      0
#define GPIO_GACR_ACB_WIDTH                      3
#define GPIO_GACR_ACB(x)                         (((uint8_t)(((uint8_t)(x))<<GPIO_GACR_ACB_SHIFT))&GPIO_GACR_ACB_MASK)
#define GPIO_GACR_ROB_MASK                       0x80u
#define GPIO_GACR_ROB_SHIFT                      7
#define GPIO_GACR_ROB_WIDTH                      1
#define GPIO_GACR_ROB(x)                         (((uint8_t)(((uint8_t)(x))<<GPIO_GACR_ROB_SHIFT))&GPIO_GACR_ROB_MASK)

/*!
 * @}
 */ /* end of group GPIO_Register_Masks */


/* GPIO - Peripheral instance base addresses */
/** Peripheral GPIOA base address */
#define GPIOA_BASE                               (0x400FF000u)
/** Peripheral GPIOA base pointer */
#define GPIOA                                    ((GPIO_Type *)GPIOA_BASE)
#define GPIOA_BASE_PTR                           (GPIOA)
/** Peripheral GPIOB base address */
#define GPIOB_BASE                               (0x400FF001u)
/** Peripheral GPIOB base pointer */
#define GPIOB                                    ((GPIO_Type *)GPIOB_BASE)
#define GPIOB_BASE_PTR                           (GPIOB)
/** Peripheral GPIOC base address */
#define GPIOC_BASE                               (0x400FF002u)
/** Peripheral GPIOC base pointer */
#define GPIOC                                    ((GPIO_Type *)GPIOC_BASE)
#define GPIOC_BASE_PTR                           (GPIOC)
/** Peripheral GPIOD base address */
#define GPIOD_BASE                               (0x400FF003u)
/** Peripheral GPIOD base pointer */
#define GPIOD                                    ((GPIO_Type *)GPIOD_BASE)
#define GPIOD_BASE_PTR                           (GPIOD)
/** Peripheral GPIOE base address */
#define GPIOE_BASE                               (0x400FF040u)
/** Peripheral GPIOE base pointer */
#define GPIOE                                    ((GPIO_Type *)GPIOE_BASE)
#define GPIOE_BASE_PTR                           (GPIOE)
/** Peripheral GPIOF base address */
#define GPIOF_BASE                               (0x400FF041u)
/** Peripheral GPIOF base pointer */
#define GPIOF                                    ((GPIO_Type *)GPIOF_BASE)
#define GPIOF_BASE_PTR                           (GPIOF)
/** Peripheral GPIOG base address */
#define GPIOG_BASE                               (0x400FF042u)
/** Peripheral GPIOG base pointer */
#define GPIOG                                    ((GPIO_Type *)GPIOG_BASE)
#define GPIOG_BASE_PTR                           (GPIOG)
/** Peripheral GPIOH base address */
#define GPIOH_BASE                               (0x400FF043u)
/** Peripheral GPIOH base pointer */
#define GPIOH                                    ((GPIO_Type *)GPIOH_BASE)
#define GPIOH_BASE_PTR                           (GPIOH)
/** Peripheral GPIOI base address */
#define GPIOI_BASE                               (0x400FF080u)
/** Peripheral GPIOI base pointer */
#define GPIOI                                    ((GPIO_Type *)GPIOI_BASE)
#define GPIOI_BASE_PTR                           (GPIOI)
/** Peripheral GPIOJ base address */
#define GPIOJ_BASE                               (0x400FF081u)
/** Peripheral GPIOJ base pointer */
#define GPIOJ                                    ((GPIO_Type *)GPIOJ_BASE)
#define GPIOJ_BASE_PTR                           (GPIOJ)
/** Peripheral GPIOK base address */
#define GPIOK_BASE                               (0x400FF082u)
/** Peripheral GPIOK base pointer */
#define GPIOK                                    ((GPIO_Type *)GPIOK_BASE)
#define GPIOK_BASE_PTR                           (GPIOK)
/** Peripheral GPIOL base address */
#define GPIOL_BASE                               (0x400FF083u)
/** Peripheral GPIOL base pointer */
#define GPIOL                                    ((GPIO_Type *)GPIOL_BASE)
#define GPIOL_BASE_PTR                           (GPIOL)
/** Peripheral GPIOM base address */
#define GPIOM_BASE                               (0x400FF0C0u)
/** Peripheral GPIOM base pointer */
#define GPIOM                                    ((GPIO_Type *)GPIOM_BASE)
#define GPIOM_BASE_PTR                           (GPIOM)
/** Array initializer of GPIO peripheral base addresses */
#define GPIO_BASE_ADDRS                          { GPIOA_BASE, GPIOB_BASE, GPIOC_BASE, GPIOD_BASE, GPIOE_BASE, GPIOF_BASE, GPIOG_BASE, GPIOH_BASE, GPIOI_BASE, GPIOJ_BASE, GPIOK_BASE, GPIOL_BASE, GPIOM_BASE }
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI, GPIOJ, GPIOK, GPIOL, GPIOM }

/* ----------------------------------------------------------------------------
   -- GPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Accessor_Macros GPIO - Register accessor macros
 * @{
 */


/* GPIO - Register instance definitions */
/* GPIOA */
#define GPIOA_PDOR                               GPIO_PDOR_REG(GPIOA)
#define GPIOA_PSOR                               GPIO_PSOR_REG(GPIOA)
#define GPIOA_PCOR                               GPIO_PCOR_REG(GPIOA)
#define GPIOA_PTOR                               GPIO_PTOR_REG(GPIOA)
#define GPIOA_PDIR                               GPIO_PDIR_REG(GPIOA)
#define GPIOA_PDDR                               GPIO_PDDR_REG(GPIOA)
#define GPIOA_GACR                               GPIO_GACR_REG(GPIOA)
/* GPIOB */
#define GPIOB_PDOR                               GPIO_PDOR_REG(GPIOB)
#define GPIOB_PSOR                               GPIO_PSOR_REG(GPIOB)
#define GPIOB_PCOR                               GPIO_PCOR_REG(GPIOB)
#define GPIOB_PTOR                               GPIO_PTOR_REG(GPIOB)
#define GPIOB_PDIR                               GPIO_PDIR_REG(GPIOB)
#define GPIOB_PDDR                               GPIO_PDDR_REG(GPIOB)
#define GPIOB_GACR                               GPIO_GACR_REG(GPIOB)
/* GPIOC */
#define GPIOC_PDOR                               GPIO_PDOR_REG(GPIOC)
#define GPIOC_PSOR                               GPIO_PSOR_REG(GPIOC)
#define GPIOC_PCOR                               GPIO_PCOR_REG(GPIOC)
#define GPIOC_PTOR                               GPIO_PTOR_REG(GPIOC)
#define GPIOC_PDIR                               GPIO_PDIR_REG(GPIOC)
#define GPIOC_PDDR                               GPIO_PDDR_REG(GPIOC)
#define GPIOC_GACR                               GPIO_GACR_REG(GPIOC)
/* GPIOD */
#define GPIOD_PDOR                               GPIO_PDOR_REG(GPIOD)
#define GPIOD_PSOR                               GPIO_PSOR_REG(GPIOD)
#define GPIOD_PCOR                               GPIO_PCOR_REG(GPIOD)
#define GPIOD_PTOR                               GPIO_PTOR_REG(GPIOD)
#define GPIOD_PDIR                               GPIO_PDIR_REG(GPIOD)
#define GPIOD_PDDR                               GPIO_PDDR_REG(GPIOD)
#define GPIOD_GACR                               GPIO_GACR_REG(GPIOD)
/* GPIOE */
#define GPIOE_PDOR                               GPIO_PDOR_REG(GPIOE)
#define GPIOE_PSOR                               GPIO_PSOR_REG(GPIOE)
#define GPIOE_PCOR                               GPIO_PCOR_REG(GPIOE)
#define GPIOE_PTOR                               GPIO_PTOR_REG(GPIOE)
#define GPIOE_PDIR                               GPIO_PDIR_REG(GPIOE)
#define GPIOE_PDDR                               GPIO_PDDR_REG(GPIOE)
#define GPIOE_GACR                               GPIO_GACR_REG(GPIOE)
/* GPIOF */
#define GPIOF_PDOR                               GPIO_PDOR_REG(GPIOF)
#define GPIOF_PSOR                               GPIO_PSOR_REG(GPIOF)
#define GPIOF_PCOR                               GPIO_PCOR_REG(GPIOF)
#define GPIOF_PTOR                               GPIO_PTOR_REG(GPIOF)
#define GPIOF_PDIR                               GPIO_PDIR_REG(GPIOF)
#define GPIOF_PDDR                               GPIO_PDDR_REG(GPIOF)
#define GPIOF_GACR                               GPIO_GACR_REG(GPIOF)
/* GPIOG */
#define GPIOG_PDOR                               GPIO_PDOR_REG(GPIOG)
#define GPIOG_PSOR                               GPIO_PSOR_REG(GPIOG)
#define GPIOG_PCOR                               GPIO_PCOR_REG(GPIOG)
#define GPIOG_PTOR                               GPIO_PTOR_REG(GPIOG)
#define GPIOG_PDIR                               GPIO_PDIR_REG(GPIOG)
#define GPIOG_PDDR                               GPIO_PDDR_REG(GPIOG)
#define GPIOG_GACR                               GPIO_GACR_REG(GPIOG)
/* GPIOH */
#define GPIOH_PDOR                               GPIO_PDOR_REG(GPIOH)
#define GPIOH_PSOR                               GPIO_PSOR_REG(GPIOH)
#define GPIOH_PCOR                               GPIO_PCOR_REG(GPIOH)
#define GPIOH_PTOR                               GPIO_PTOR_REG(GPIOH)
#define GPIOH_PDIR                               GPIO_PDIR_REG(GPIOH)
#define GPIOH_PDDR                               GPIO_PDDR_REG(GPIOH)
#define GPIOH_GACR                               GPIO_GACR_REG(GPIOH)
/* GPIOI */
#define GPIOI_PDOR                               GPIO_PDOR_REG(GPIOI)
#define GPIOI_PSOR                               GPIO_PSOR_REG(GPIOI)
#define GPIOI_PCOR                               GPIO_PCOR_REG(GPIOI)
#define GPIOI_PTOR                               GPIO_PTOR_REG(GPIOI)
#define GPIOI_PDIR                               GPIO_PDIR_REG(GPIOI)
#define GPIOI_PDDR                               GPIO_PDDR_REG(GPIOI)
#define GPIOI_GACR                               GPIO_GACR_REG(GPIOI)
/* GPIOJ */
#define GPIOJ_PDOR                               GPIO_PDOR_REG(GPIOJ)
#define GPIOJ_PSOR                               GPIO_PSOR_REG(GPIOJ)
#define GPIOJ_PCOR                               GPIO_PCOR_REG(GPIOJ)
#define GPIOJ_PTOR                               GPIO_PTOR_REG(GPIOJ)
#define GPIOJ_PDIR                               GPIO_PDIR_REG(GPIOJ)
#define GPIOJ_PDDR                               GPIO_PDDR_REG(GPIOJ)
#define GPIOJ_GACR                               GPIO_GACR_REG(GPIOJ)
/* GPIOK */
#define GPIOK_PDOR                               GPIO_PDOR_REG(GPIOK)
#define GPIOK_PSOR                               GPIO_PSOR_REG(GPIOK)
#define GPIOK_PCOR                               GPIO_PCOR_REG(GPIOK)
#define GPIOK_PTOR                               GPIO_PTOR_REG(GPIOK)
#define GPIOK_PDIR                               GPIO_PDIR_REG(GPIOK)
#define GPIOK_PDDR                               GPIO_PDDR_REG(GPIOK)
#define GPIOK_GACR                               GPIO_GACR_REG(GPIOK)
/* GPIOL */
#define GPIOL_PDOR                               GPIO_PDOR_REG(GPIOL)
#define GPIOL_PSOR                               GPIO_PSOR_REG(GPIOL)
#define GPIOL_PCOR                               GPIO_PCOR_REG(GPIOL)
#define GPIOL_PTOR                               GPIO_PTOR_REG(GPIOL)
#define GPIOL_PDIR                               GPIO_PDIR_REG(GPIOL)
#define GPIOL_PDDR                               GPIO_PDDR_REG(GPIOL)
#define GPIOL_GACR                               GPIO_GACR_REG(GPIOL)
/* GPIOM */
#define GPIOM_PDOR                               GPIO_PDOR_REG(GPIOM)
#define GPIOM_PSOR                               GPIO_PSOR_REG(GPIOM)
#define GPIOM_PCOR                               GPIO_PCOR_REG(GPIOM)
#define GPIOM_PTOR                               GPIO_PTOR_REG(GPIOM)
#define GPIOM_PDIR                               GPIO_PDIR_REG(GPIOM)
#define GPIOM_PDDR                               GPIO_PDDR_REG(GPIOM)
#define GPIOM_GACR                               GPIO_GACR_REG(GPIOM)

/*!
 * @}
 */ /* end of group GPIO_Register_Accessor_Macros */


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
} I2C_Type, *I2C_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register accessors */
#define I2C_A1_REG(base)                         ((base)->A1)
#define I2C_F_REG(base)                          ((base)->F)
#define I2C_C1_REG(base)                         ((base)->C1)
#define I2C_S_REG(base)                          ((base)->S)
#define I2C_D_REG(base)                          ((base)->D)
#define I2C_C2_REG(base)                         ((base)->C2)
#define I2C_FLT_REG(base)                        ((base)->FLT)
#define I2C_RA_REG(base)                         ((base)->RA)
#define I2C_SMB_REG(base)                        ((base)->SMB)
#define I2C_A2_REG(base)                         ((base)->A2)
#define I2C_SLTH_REG(base)                       ((base)->SLTH)
#define I2C_SLTL_REG(base)                       ((base)->SLTL)
#define I2C_S2_REG(base)                         ((base)->S2)

/*!
 * @}
 */ /* end of group I2C_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- I2C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Masks I2C Register Masks
 * @{
 */

/* A1 Bit Fields */
#define I2C_A1_AD_MASK                           0xFEu
#define I2C_A1_AD_SHIFT                          1
#define I2C_A1_AD_WIDTH                          7
#define I2C_A1_AD(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_A1_AD_SHIFT))&I2C_A1_AD_MASK)
/* F Bit Fields */
#define I2C_F_ICR_MASK                           0x3Fu
#define I2C_F_ICR_SHIFT                          0
#define I2C_F_ICR_WIDTH                          6
#define I2C_F_ICR(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_F_ICR_SHIFT))&I2C_F_ICR_MASK)
#define I2C_F_MULT_MASK                          0xC0u
#define I2C_F_MULT_SHIFT                         6
#define I2C_F_MULT_WIDTH                         2
#define I2C_F_MULT(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_F_MULT_SHIFT))&I2C_F_MULT_MASK)
/* C1 Bit Fields */
#define I2C_C1_DMAEN_MASK                        0x1u
#define I2C_C1_DMAEN_SHIFT                       0
#define I2C_C1_DMAEN_WIDTH                       1
#define I2C_C1_DMAEN(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_C1_DMAEN_SHIFT))&I2C_C1_DMAEN_MASK)
#define I2C_C1_WUEN_MASK                         0x2u
#define I2C_C1_WUEN_SHIFT                        1
#define I2C_C1_WUEN_WIDTH                        1
#define I2C_C1_WUEN(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_C1_WUEN_SHIFT))&I2C_C1_WUEN_MASK)
#define I2C_C1_RSTA_MASK                         0x4u
#define I2C_C1_RSTA_SHIFT                        2
#define I2C_C1_RSTA_WIDTH                        1
#define I2C_C1_RSTA(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_C1_RSTA_SHIFT))&I2C_C1_RSTA_MASK)
#define I2C_C1_TXAK_MASK                         0x8u
#define I2C_C1_TXAK_SHIFT                        3
#define I2C_C1_TXAK_WIDTH                        1
#define I2C_C1_TXAK(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_C1_TXAK_SHIFT))&I2C_C1_TXAK_MASK)
#define I2C_C1_TX_MASK                           0x10u
#define I2C_C1_TX_SHIFT                          4
#define I2C_C1_TX_WIDTH                          1
#define I2C_C1_TX(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_C1_TX_SHIFT))&I2C_C1_TX_MASK)
#define I2C_C1_MST_MASK                          0x20u
#define I2C_C1_MST_SHIFT                         5
#define I2C_C1_MST_WIDTH                         1
#define I2C_C1_MST(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_C1_MST_SHIFT))&I2C_C1_MST_MASK)
#define I2C_C1_IICIE_MASK                        0x40u
#define I2C_C1_IICIE_SHIFT                       6
#define I2C_C1_IICIE_WIDTH                       1
#define I2C_C1_IICIE(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_C1_IICIE_SHIFT))&I2C_C1_IICIE_MASK)
#define I2C_C1_IICEN_MASK                        0x80u
#define I2C_C1_IICEN_SHIFT                       7
#define I2C_C1_IICEN_WIDTH                       1
#define I2C_C1_IICEN(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_C1_IICEN_SHIFT))&I2C_C1_IICEN_MASK)
/* S Bit Fields */
#define I2C_S_RXAK_MASK                          0x1u
#define I2C_S_RXAK_SHIFT                         0
#define I2C_S_RXAK_WIDTH                         1
#define I2C_S_RXAK(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_S_RXAK_SHIFT))&I2C_S_RXAK_MASK)
#define I2C_S_IICIF_MASK                         0x2u
#define I2C_S_IICIF_SHIFT                        1
#define I2C_S_IICIF_WIDTH                        1
#define I2C_S_IICIF(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_S_IICIF_SHIFT))&I2C_S_IICIF_MASK)
#define I2C_S_SRW_MASK                           0x4u
#define I2C_S_SRW_SHIFT                          2
#define I2C_S_SRW_WIDTH                          1
#define I2C_S_SRW(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_S_SRW_SHIFT))&I2C_S_SRW_MASK)
#define I2C_S_RAM_MASK                           0x8u
#define I2C_S_RAM_SHIFT                          3
#define I2C_S_RAM_WIDTH                          1
#define I2C_S_RAM(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_S_RAM_SHIFT))&I2C_S_RAM_MASK)
#define I2C_S_ARBL_MASK                          0x10u
#define I2C_S_ARBL_SHIFT                         4
#define I2C_S_ARBL_WIDTH                         1
#define I2C_S_ARBL(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_S_ARBL_SHIFT))&I2C_S_ARBL_MASK)
#define I2C_S_BUSY_MASK                          0x20u
#define I2C_S_BUSY_SHIFT                         5
#define I2C_S_BUSY_WIDTH                         1
#define I2C_S_BUSY(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_S_BUSY_SHIFT))&I2C_S_BUSY_MASK)
#define I2C_S_IAAS_MASK                          0x40u
#define I2C_S_IAAS_SHIFT                         6
#define I2C_S_IAAS_WIDTH                         1
#define I2C_S_IAAS(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_S_IAAS_SHIFT))&I2C_S_IAAS_MASK)
#define I2C_S_TCF_MASK                           0x80u
#define I2C_S_TCF_SHIFT                          7
#define I2C_S_TCF_WIDTH                          1
#define I2C_S_TCF(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_S_TCF_SHIFT))&I2C_S_TCF_MASK)
/* D Bit Fields */
#define I2C_D_DATA_MASK                          0xFFu
#define I2C_D_DATA_SHIFT                         0
#define I2C_D_DATA_WIDTH                         8
#define I2C_D_DATA(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_D_DATA_SHIFT))&I2C_D_DATA_MASK)
/* C2 Bit Fields */
#define I2C_C2_AD_MASK                           0x7u
#define I2C_C2_AD_SHIFT                          0
#define I2C_C2_AD_WIDTH                          3
#define I2C_C2_AD(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_C2_AD_SHIFT))&I2C_C2_AD_MASK)
#define I2C_C2_RMEN_MASK                         0x8u
#define I2C_C2_RMEN_SHIFT                        3
#define I2C_C2_RMEN_WIDTH                        1
#define I2C_C2_RMEN(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_C2_RMEN_SHIFT))&I2C_C2_RMEN_MASK)
#define I2C_C2_SBRC_MASK                         0x10u
#define I2C_C2_SBRC_SHIFT                        4
#define I2C_C2_SBRC_WIDTH                        1
#define I2C_C2_SBRC(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_C2_SBRC_SHIFT))&I2C_C2_SBRC_MASK)
#define I2C_C2_HDRS_MASK                         0x20u
#define I2C_C2_HDRS_SHIFT                        5
#define I2C_C2_HDRS_WIDTH                        1
#define I2C_C2_HDRS(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_C2_HDRS_SHIFT))&I2C_C2_HDRS_MASK)
#define I2C_C2_ADEXT_MASK                        0x40u
#define I2C_C2_ADEXT_SHIFT                       6
#define I2C_C2_ADEXT_WIDTH                       1
#define I2C_C2_ADEXT(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_C2_ADEXT_SHIFT))&I2C_C2_ADEXT_MASK)
#define I2C_C2_GCAEN_MASK                        0x80u
#define I2C_C2_GCAEN_SHIFT                       7
#define I2C_C2_GCAEN_WIDTH                       1
#define I2C_C2_GCAEN(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_C2_GCAEN_SHIFT))&I2C_C2_GCAEN_MASK)
/* FLT Bit Fields */
#define I2C_FLT_FLT_MASK                         0xFu
#define I2C_FLT_FLT_SHIFT                        0
#define I2C_FLT_FLT_WIDTH                        4
#define I2C_FLT_FLT(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_FLT_FLT_SHIFT))&I2C_FLT_FLT_MASK)
#define I2C_FLT_STARTF_MASK                      0x10u
#define I2C_FLT_STARTF_SHIFT                     4
#define I2C_FLT_STARTF_WIDTH                     1
#define I2C_FLT_STARTF(x)                        (((uint8_t)(((uint8_t)(x))<<I2C_FLT_STARTF_SHIFT))&I2C_FLT_STARTF_MASK)
#define I2C_FLT_SSIE_MASK                        0x20u
#define I2C_FLT_SSIE_SHIFT                       5
#define I2C_FLT_SSIE_WIDTH                       1
#define I2C_FLT_SSIE(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_FLT_SSIE_SHIFT))&I2C_FLT_SSIE_MASK)
#define I2C_FLT_STOPF_MASK                       0x40u
#define I2C_FLT_STOPF_SHIFT                      6
#define I2C_FLT_STOPF_WIDTH                      1
#define I2C_FLT_STOPF(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_FLT_STOPF_SHIFT))&I2C_FLT_STOPF_MASK)
#define I2C_FLT_SHEN_MASK                        0x80u
#define I2C_FLT_SHEN_SHIFT                       7
#define I2C_FLT_SHEN_WIDTH                       1
#define I2C_FLT_SHEN(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_FLT_SHEN_SHIFT))&I2C_FLT_SHEN_MASK)
/* RA Bit Fields */
#define I2C_RA_RAD_MASK                          0xFEu
#define I2C_RA_RAD_SHIFT                         1
#define I2C_RA_RAD_WIDTH                         7
#define I2C_RA_RAD(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_RA_RAD_SHIFT))&I2C_RA_RAD_MASK)
/* SMB Bit Fields */
#define I2C_SMB_SHTF2IE_MASK                     0x1u
#define I2C_SMB_SHTF2IE_SHIFT                    0
#define I2C_SMB_SHTF2IE_WIDTH                    1
#define I2C_SMB_SHTF2IE(x)                       (((uint8_t)(((uint8_t)(x))<<I2C_SMB_SHTF2IE_SHIFT))&I2C_SMB_SHTF2IE_MASK)
#define I2C_SMB_SHTF2_MASK                       0x2u
#define I2C_SMB_SHTF2_SHIFT                      1
#define I2C_SMB_SHTF2_WIDTH                      1
#define I2C_SMB_SHTF2(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_SMB_SHTF2_SHIFT))&I2C_SMB_SHTF2_MASK)
#define I2C_SMB_SHTF1_MASK                       0x4u
#define I2C_SMB_SHTF1_SHIFT                      2
#define I2C_SMB_SHTF1_WIDTH                      1
#define I2C_SMB_SHTF1(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_SMB_SHTF1_SHIFT))&I2C_SMB_SHTF1_MASK)
#define I2C_SMB_SLTF_MASK                        0x8u
#define I2C_SMB_SLTF_SHIFT                       3
#define I2C_SMB_SLTF_WIDTH                       1
#define I2C_SMB_SLTF(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_SMB_SLTF_SHIFT))&I2C_SMB_SLTF_MASK)
#define I2C_SMB_TCKSEL_MASK                      0x10u
#define I2C_SMB_TCKSEL_SHIFT                     4
#define I2C_SMB_TCKSEL_WIDTH                     1
#define I2C_SMB_TCKSEL(x)                        (((uint8_t)(((uint8_t)(x))<<I2C_SMB_TCKSEL_SHIFT))&I2C_SMB_TCKSEL_MASK)
#define I2C_SMB_SIICAEN_MASK                     0x20u
#define I2C_SMB_SIICAEN_SHIFT                    5
#define I2C_SMB_SIICAEN_WIDTH                    1
#define I2C_SMB_SIICAEN(x)                       (((uint8_t)(((uint8_t)(x))<<I2C_SMB_SIICAEN_SHIFT))&I2C_SMB_SIICAEN_MASK)
#define I2C_SMB_ALERTEN_MASK                     0x40u
#define I2C_SMB_ALERTEN_SHIFT                    6
#define I2C_SMB_ALERTEN_WIDTH                    1
#define I2C_SMB_ALERTEN(x)                       (((uint8_t)(((uint8_t)(x))<<I2C_SMB_ALERTEN_SHIFT))&I2C_SMB_ALERTEN_MASK)
#define I2C_SMB_FACK_MASK                        0x80u
#define I2C_SMB_FACK_SHIFT                       7
#define I2C_SMB_FACK_WIDTH                       1
#define I2C_SMB_FACK(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_SMB_FACK_SHIFT))&I2C_SMB_FACK_MASK)
/* A2 Bit Fields */
#define I2C_A2_SAD_MASK                          0xFEu
#define I2C_A2_SAD_SHIFT                         1
#define I2C_A2_SAD_WIDTH                         7
#define I2C_A2_SAD(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_A2_SAD_SHIFT))&I2C_A2_SAD_MASK)
/* SLTH Bit Fields */
#define I2C_SLTH_SSLT_MASK                       0xFFu
#define I2C_SLTH_SSLT_SHIFT                      0
#define I2C_SLTH_SSLT_WIDTH                      8
#define I2C_SLTH_SSLT(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_SLTH_SSLT_SHIFT))&I2C_SLTH_SSLT_MASK)
/* SLTL Bit Fields */
#define I2C_SLTL_SSLT_MASK                       0xFFu
#define I2C_SLTL_SSLT_SHIFT                      0
#define I2C_SLTL_SSLT_WIDTH                      8
#define I2C_SLTL_SSLT(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_SLTL_SSLT_SHIFT))&I2C_SLTL_SSLT_MASK)
/* S2 Bit Fields */
#define I2C_S2_EMPTY_MASK                        0x1u
#define I2C_S2_EMPTY_SHIFT                       0
#define I2C_S2_EMPTY_WIDTH                       1
#define I2C_S2_EMPTY(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_S2_EMPTY_SHIFT))&I2C_S2_EMPTY_MASK)
#define I2C_S2_ERROR_MASK                        0x2u
#define I2C_S2_ERROR_SHIFT                       1
#define I2C_S2_ERROR_WIDTH                       1
#define I2C_S2_ERROR(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_S2_ERROR_SHIFT))&I2C_S2_ERROR_MASK)

/*!
 * @}
 */ /* end of group I2C_Register_Masks */


/* I2C - Peripheral instance base addresses */
/** Peripheral I2C0 base address */
#define I2C0_BASE                                (0x40067000u)
/** Peripheral I2C0 base pointer */
#define I2C0                                     ((I2C_Type *)I2C0_BASE)
#define I2C0_BASE_PTR                            (I2C0)
/** Peripheral I2C1 base address */
#define I2C1_BASE                                (0x40068000u)
/** Peripheral I2C1 base pointer */
#define I2C1                                     ((I2C_Type *)I2C1_BASE)
#define I2C1_BASE_PTR                            (I2C1)
/** Array initializer of I2C peripheral base addresses */
#define I2C_BASE_ADDRS                           { I2C0_BASE, I2C1_BASE }
/** Array initializer of I2C peripheral base pointers */
#define I2C_BASE_PTRS                            { I2C0, I2C1 }
/** Interrupt vectors for the I2C peripheral type */
#define I2C_IRQS                                 { I2C0_I2C1_IRQn, I2C0_I2C1_IRQn }

/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register instance definitions */
/* I2C0 */
#define I2C0_A1                                  I2C_A1_REG(I2C0)
#define I2C0_F                                   I2C_F_REG(I2C0)
#define I2C0_C1                                  I2C_C1_REG(I2C0)
#define I2C0_S                                   I2C_S_REG(I2C0)
#define I2C0_D                                   I2C_D_REG(I2C0)
#define I2C0_C2                                  I2C_C2_REG(I2C0)
#define I2C0_FLT                                 I2C_FLT_REG(I2C0)
#define I2C0_RA                                  I2C_RA_REG(I2C0)
#define I2C0_SMB                                 I2C_SMB_REG(I2C0)
#define I2C0_A2                                  I2C_A2_REG(I2C0)
#define I2C0_SLTH                                I2C_SLTH_REG(I2C0)
#define I2C0_SLTL                                I2C_SLTL_REG(I2C0)
#define I2C0_S2                                  I2C_S2_REG(I2C0)
/* I2C1 */
#define I2C1_A1                                  I2C_A1_REG(I2C1)
#define I2C1_F                                   I2C_F_REG(I2C1)
#define I2C1_C1                                  I2C_C1_REG(I2C1)
#define I2C1_S                                   I2C_S_REG(I2C1)
#define I2C1_D                                   I2C_D_REG(I2C1)
#define I2C1_C2                                  I2C_C2_REG(I2C1)
#define I2C1_FLT                                 I2C_FLT_REG(I2C1)
#define I2C1_RA                                  I2C_RA_REG(I2C1)
#define I2C1_SMB                                 I2C_SMB_REG(I2C1)
#define I2C1_A2                                  I2C_A2_REG(I2C1)
#define I2C1_SLTH                                I2C_SLTH_REG(I2C1)
#define I2C1_SLTL                                I2C_SLTL_REG(I2C1)
#define I2C1_S2                                  I2C_S2_REG(I2C1)

/*!
 * @}
 */ /* end of group I2C_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group I2C_Peripheral_Access_Layer */


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
    __IO uint32_t WF[16];                            /**< LCD Waveform register, array offset: 0x20, array step: 0x4 */
    __IO uint8_t WF8B[64];                           /**< LCD Waveform Register 0...LCD Waveform Register 63., array offset: 0x20, array step: 0x1 */
  };
} LCD_Type, *LCD_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- LCD - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LCD_Register_Accessor_Macros LCD - Register accessor macros
 * @{
 */


/* LCD - Register accessors */
#define LCD_GCR_REG(base)                        ((base)->GCR)
#define LCD_AR_REG(base)                         ((base)->AR)
#define LCD_FDCR_REG(base)                       ((base)->FDCR)
#define LCD_FDSR_REG(base)                       ((base)->FDSR)
#define LCD_PEN_REG(base,index)                  ((base)->PEN[index])
#define LCD_PEN_COUNT                            2
#define LCD_BPEN_REG(base,index)                 ((base)->BPEN[index])
#define LCD_BPEN_COUNT                           2
#define LCD_WF_REG(base,index2)                  ((base)->WF[index2])
#define LCD_WF_COUNT                             16
#define LCD_WF8B_REG(base,index2)                ((base)->WF8B[index2])
#define LCD_WF8B_COUNT                           64

/*!
 * @}
 */ /* end of group LCD_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- LCD Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LCD_Register_Masks LCD Register Masks
 * @{
 */

/* GCR Bit Fields */
#define LCD_GCR_DUTY_MASK                        0x7u
#define LCD_GCR_DUTY_SHIFT                       0
#define LCD_GCR_DUTY_WIDTH                       3
#define LCD_GCR_DUTY(x)                          (((uint32_t)(((uint32_t)(x))<<LCD_GCR_DUTY_SHIFT))&LCD_GCR_DUTY_MASK)
#define LCD_GCR_LCLK_MASK                        0x38u
#define LCD_GCR_LCLK_SHIFT                       3
#define LCD_GCR_LCLK_WIDTH                       3
#define LCD_GCR_LCLK(x)                          (((uint32_t)(((uint32_t)(x))<<LCD_GCR_LCLK_SHIFT))&LCD_GCR_LCLK_MASK)
#define LCD_GCR_SOURCE_MASK                      0x40u
#define LCD_GCR_SOURCE_SHIFT                     6
#define LCD_GCR_SOURCE_WIDTH                     1
#define LCD_GCR_SOURCE(x)                        (((uint32_t)(((uint32_t)(x))<<LCD_GCR_SOURCE_SHIFT))&LCD_GCR_SOURCE_MASK)
#define LCD_GCR_LCDEN_MASK                       0x80u
#define LCD_GCR_LCDEN_SHIFT                      7
#define LCD_GCR_LCDEN_WIDTH                      1
#define LCD_GCR_LCDEN(x)                         (((uint32_t)(((uint32_t)(x))<<LCD_GCR_LCDEN_SHIFT))&LCD_GCR_LCDEN_MASK)
#define LCD_GCR_LCDSTP_MASK                      0x100u
#define LCD_GCR_LCDSTP_SHIFT                     8
#define LCD_GCR_LCDSTP_WIDTH                     1
#define LCD_GCR_LCDSTP(x)                        (((uint32_t)(((uint32_t)(x))<<LCD_GCR_LCDSTP_SHIFT))&LCD_GCR_LCDSTP_MASK)
#define LCD_GCR_LCDDOZE_MASK                     0x200u
#define LCD_GCR_LCDDOZE_SHIFT                    9
#define LCD_GCR_LCDDOZE_WIDTH                    1
#define LCD_GCR_LCDDOZE(x)                       (((uint32_t)(((uint32_t)(x))<<LCD_GCR_LCDDOZE_SHIFT))&LCD_GCR_LCDDOZE_MASK)
#define LCD_GCR_ALTDIV_MASK                      0x3000u
#define LCD_GCR_ALTDIV_SHIFT                     12
#define LCD_GCR_ALTDIV_WIDTH                     2
#define LCD_GCR_ALTDIV(x)                        (((uint32_t)(((uint32_t)(x))<<LCD_GCR_ALTDIV_SHIFT))&LCD_GCR_ALTDIV_MASK)
#define LCD_GCR_FDCIEN_MASK                      0x4000u
#define LCD_GCR_FDCIEN_SHIFT                     14
#define LCD_GCR_FDCIEN_WIDTH                     1
#define LCD_GCR_FDCIEN(x)                        (((uint32_t)(((uint32_t)(x))<<LCD_GCR_FDCIEN_SHIFT))&LCD_GCR_FDCIEN_MASK)
#define LCD_GCR_LCDIEN_MASK                      0x8000u
#define LCD_GCR_LCDIEN_SHIFT                     15
#define LCD_GCR_LCDIEN_WIDTH                     1
#define LCD_GCR_LCDIEN(x)                        (((uint32_t)(((uint32_t)(x))<<LCD_GCR_LCDIEN_SHIFT))&LCD_GCR_LCDIEN_MASK)
#define LCD_GCR_VSUPPLY_MASK                     0x20000u
#define LCD_GCR_VSUPPLY_SHIFT                    17
#define LCD_GCR_VSUPPLY_WIDTH                    1
#define LCD_GCR_VSUPPLY(x)                       (((uint32_t)(((uint32_t)(x))<<LCD_GCR_VSUPPLY_SHIFT))&LCD_GCR_VSUPPLY_MASK)
#define LCD_GCR_LADJ_MASK                        0x300000u
#define LCD_GCR_LADJ_SHIFT                       20
#define LCD_GCR_LADJ_WIDTH                       2
#define LCD_GCR_LADJ(x)                          (((uint32_t)(((uint32_t)(x))<<LCD_GCR_LADJ_SHIFT))&LCD_GCR_LADJ_MASK)
#define LCD_GCR_CPSEL_MASK                       0x800000u
#define LCD_GCR_CPSEL_SHIFT                      23
#define LCD_GCR_CPSEL_WIDTH                      1
#define LCD_GCR_CPSEL(x)                         (((uint32_t)(((uint32_t)(x))<<LCD_GCR_CPSEL_SHIFT))&LCD_GCR_CPSEL_MASK)
#define LCD_GCR_RVTRIM_MASK                      0xF000000u
#define LCD_GCR_RVTRIM_SHIFT                     24
#define LCD_GCR_RVTRIM_WIDTH                     4
#define LCD_GCR_RVTRIM(x)                        (((uint32_t)(((uint32_t)(x))<<LCD_GCR_RVTRIM_SHIFT))&LCD_GCR_RVTRIM_MASK)
#define LCD_GCR_RVEN_MASK                        0x80000000u
#define LCD_GCR_RVEN_SHIFT                       31
#define LCD_GCR_RVEN_WIDTH                       1
#define LCD_GCR_RVEN(x)                          (((uint32_t)(((uint32_t)(x))<<LCD_GCR_RVEN_SHIFT))&LCD_GCR_RVEN_MASK)
/* AR Bit Fields */
#define LCD_AR_BRATE_MASK                        0x7u
#define LCD_AR_BRATE_SHIFT                       0
#define LCD_AR_BRATE_WIDTH                       3
#define LCD_AR_BRATE(x)                          (((uint32_t)(((uint32_t)(x))<<LCD_AR_BRATE_SHIFT))&LCD_AR_BRATE_MASK)
#define LCD_AR_BMODE_MASK                        0x8u
#define LCD_AR_BMODE_SHIFT                       3
#define LCD_AR_BMODE_WIDTH                       1
#define LCD_AR_BMODE(x)                          (((uint32_t)(((uint32_t)(x))<<LCD_AR_BMODE_SHIFT))&LCD_AR_BMODE_MASK)
#define LCD_AR_BLANK_MASK                        0x20u
#define LCD_AR_BLANK_SHIFT                       5
#define LCD_AR_BLANK_WIDTH                       1
#define LCD_AR_BLANK(x)                          (((uint32_t)(((uint32_t)(x))<<LCD_AR_BLANK_SHIFT))&LCD_AR_BLANK_MASK)
#define LCD_AR_ALT_MASK                          0x40u
#define LCD_AR_ALT_SHIFT                         6
#define LCD_AR_ALT_WIDTH                         1
#define LCD_AR_ALT(x)                            (((uint32_t)(((uint32_t)(x))<<LCD_AR_ALT_SHIFT))&LCD_AR_ALT_MASK)
#define LCD_AR_BLINK_MASK                        0x80u
#define LCD_AR_BLINK_SHIFT                       7
#define LCD_AR_BLINK_WIDTH                       1
#define LCD_AR_BLINK(x)                          (((uint32_t)(((uint32_t)(x))<<LCD_AR_BLINK_SHIFT))&LCD_AR_BLINK_MASK)
#define LCD_AR_LCDIF_MASK                        0x8000u
#define LCD_AR_LCDIF_SHIFT                       15
#define LCD_AR_LCDIF_WIDTH                       1
#define LCD_AR_LCDIF(x)                          (((uint32_t)(((uint32_t)(x))<<LCD_AR_LCDIF_SHIFT))&LCD_AR_LCDIF_MASK)
/* FDCR Bit Fields */
#define LCD_FDCR_FDPINID_MASK                    0x3Fu
#define LCD_FDCR_FDPINID_SHIFT                   0
#define LCD_FDCR_FDPINID_WIDTH                   6
#define LCD_FDCR_FDPINID(x)                      (((uint32_t)(((uint32_t)(x))<<LCD_FDCR_FDPINID_SHIFT))&LCD_FDCR_FDPINID_MASK)
#define LCD_FDCR_FDBPEN_MASK                     0x40u
#define LCD_FDCR_FDBPEN_SHIFT                    6
#define LCD_FDCR_FDBPEN_WIDTH                    1
#define LCD_FDCR_FDBPEN(x)                       (((uint32_t)(((uint32_t)(x))<<LCD_FDCR_FDBPEN_SHIFT))&LCD_FDCR_FDBPEN_MASK)
#define LCD_FDCR_FDEN_MASK                       0x80u
#define LCD_FDCR_FDEN_SHIFT                      7
#define LCD_FDCR_FDEN_WIDTH                      1
#define LCD_FDCR_FDEN(x)                         (((uint32_t)(((uint32_t)(x))<<LCD_FDCR_FDEN_SHIFT))&LCD_FDCR_FDEN_MASK)
#define LCD_FDCR_FDSWW_MASK                      0xE00u
#define LCD_FDCR_FDSWW_SHIFT                     9
#define LCD_FDCR_FDSWW_WIDTH                     3
#define LCD_FDCR_FDSWW(x)                        (((uint32_t)(((uint32_t)(x))<<LCD_FDCR_FDSWW_SHIFT))&LCD_FDCR_FDSWW_MASK)
#define LCD_FDCR_FDPRS_MASK                      0x7000u
#define LCD_FDCR_FDPRS_SHIFT                     12
#define LCD_FDCR_FDPRS_WIDTH                     3
#define LCD_FDCR_FDPRS(x)                        (((uint32_t)(((uint32_t)(x))<<LCD_FDCR_FDPRS_SHIFT))&LCD_FDCR_FDPRS_MASK)
/* FDSR Bit Fields */
#define LCD_FDSR_FDCNT_MASK                      0xFFu
#define LCD_FDSR_FDCNT_SHIFT                     0
#define LCD_FDSR_FDCNT_WIDTH                     8
#define LCD_FDSR_FDCNT(x)                        (((uint32_t)(((uint32_t)(x))<<LCD_FDSR_FDCNT_SHIFT))&LCD_FDSR_FDCNT_MASK)
#define LCD_FDSR_FDCF_MASK                       0x8000u
#define LCD_FDSR_FDCF_SHIFT                      15
#define LCD_FDSR_FDCF_WIDTH                      1
#define LCD_FDSR_FDCF(x)                         (((uint32_t)(((uint32_t)(x))<<LCD_FDSR_FDCF_SHIFT))&LCD_FDSR_FDCF_MASK)
/* PEN Bit Fields */
#define LCD_PEN_PEN_MASK                         0xFFFFFFFFu
#define LCD_PEN_PEN_SHIFT                        0
#define LCD_PEN_PEN_WIDTH                        32
#define LCD_PEN_PEN(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_PEN_PEN_SHIFT))&LCD_PEN_PEN_MASK)
/* BPEN Bit Fields */
#define LCD_BPEN_BPEN_MASK                       0xFFFFFFFFu
#define LCD_BPEN_BPEN_SHIFT                      0
#define LCD_BPEN_BPEN_WIDTH                      32
#define LCD_BPEN_BPEN(x)                         (((uint32_t)(((uint32_t)(x))<<LCD_BPEN_BPEN_SHIFT))&LCD_BPEN_BPEN_MASK)
/* WF Bit Fields */
#define LCD_WF_WF0_MASK                          0xFFu
#define LCD_WF_WF0_SHIFT                         0
#define LCD_WF_WF0_WIDTH                         8
#define LCD_WF_WF0(x)                            (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF0_SHIFT))&LCD_WF_WF0_MASK)
#define LCD_WF_WF60_MASK                         0xFFu
#define LCD_WF_WF60_SHIFT                        0
#define LCD_WF_WF60_WIDTH                        8
#define LCD_WF_WF60(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF60_SHIFT))&LCD_WF_WF60_MASK)
#define LCD_WF_WF56_MASK                         0xFFu
#define LCD_WF_WF56_SHIFT                        0
#define LCD_WF_WF56_WIDTH                        8
#define LCD_WF_WF56(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF56_SHIFT))&LCD_WF_WF56_MASK)
#define LCD_WF_WF52_MASK                         0xFFu
#define LCD_WF_WF52_SHIFT                        0
#define LCD_WF_WF52_WIDTH                        8
#define LCD_WF_WF52(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF52_SHIFT))&LCD_WF_WF52_MASK)
#define LCD_WF_WF4_MASK                          0xFFu
#define LCD_WF_WF4_SHIFT                         0
#define LCD_WF_WF4_WIDTH                         8
#define LCD_WF_WF4(x)                            (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF4_SHIFT))&LCD_WF_WF4_MASK)
#define LCD_WF_WF48_MASK                         0xFFu
#define LCD_WF_WF48_SHIFT                        0
#define LCD_WF_WF48_WIDTH                        8
#define LCD_WF_WF48(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF48_SHIFT))&LCD_WF_WF48_MASK)
#define LCD_WF_WF44_MASK                         0xFFu
#define LCD_WF_WF44_SHIFT                        0
#define LCD_WF_WF44_WIDTH                        8
#define LCD_WF_WF44(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF44_SHIFT))&LCD_WF_WF44_MASK)
#define LCD_WF_WF40_MASK                         0xFFu
#define LCD_WF_WF40_SHIFT                        0
#define LCD_WF_WF40_WIDTH                        8
#define LCD_WF_WF40(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF40_SHIFT))&LCD_WF_WF40_MASK)
#define LCD_WF_WF8_MASK                          0xFFu
#define LCD_WF_WF8_SHIFT                         0
#define LCD_WF_WF8_WIDTH                         8
#define LCD_WF_WF8(x)                            (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF8_SHIFT))&LCD_WF_WF8_MASK)
#define LCD_WF_WF36_MASK                         0xFFu
#define LCD_WF_WF36_SHIFT                        0
#define LCD_WF_WF36_WIDTH                        8
#define LCD_WF_WF36(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF36_SHIFT))&LCD_WF_WF36_MASK)
#define LCD_WF_WF32_MASK                         0xFFu
#define LCD_WF_WF32_SHIFT                        0
#define LCD_WF_WF32_WIDTH                        8
#define LCD_WF_WF32(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF32_SHIFT))&LCD_WF_WF32_MASK)
#define LCD_WF_WF28_MASK                         0xFFu
#define LCD_WF_WF28_SHIFT                        0
#define LCD_WF_WF28_WIDTH                        8
#define LCD_WF_WF28(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF28_SHIFT))&LCD_WF_WF28_MASK)
#define LCD_WF_WF12_MASK                         0xFFu
#define LCD_WF_WF12_SHIFT                        0
#define LCD_WF_WF12_WIDTH                        8
#define LCD_WF_WF12(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF12_SHIFT))&LCD_WF_WF12_MASK)
#define LCD_WF_WF24_MASK                         0xFFu
#define LCD_WF_WF24_SHIFT                        0
#define LCD_WF_WF24_WIDTH                        8
#define LCD_WF_WF24(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF24_SHIFT))&LCD_WF_WF24_MASK)
#define LCD_WF_WF20_MASK                         0xFFu
#define LCD_WF_WF20_SHIFT                        0
#define LCD_WF_WF20_WIDTH                        8
#define LCD_WF_WF20(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF20_SHIFT))&LCD_WF_WF20_MASK)
#define LCD_WF_WF16_MASK                         0xFFu
#define LCD_WF_WF16_SHIFT                        0
#define LCD_WF_WF16_WIDTH                        8
#define LCD_WF_WF16(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF16_SHIFT))&LCD_WF_WF16_MASK)
#define LCD_WF_WF5_MASK                          0xFF00u
#define LCD_WF_WF5_SHIFT                         8
#define LCD_WF_WF5_WIDTH                         8
#define LCD_WF_WF5(x)                            (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF5_SHIFT))&LCD_WF_WF5_MASK)
#define LCD_WF_WF49_MASK                         0xFF00u
#define LCD_WF_WF49_SHIFT                        8
#define LCD_WF_WF49_WIDTH                        8
#define LCD_WF_WF49(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF49_SHIFT))&LCD_WF_WF49_MASK)
#define LCD_WF_WF45_MASK                         0xFF00u
#define LCD_WF_WF45_SHIFT                        8
#define LCD_WF_WF45_WIDTH                        8
#define LCD_WF_WF45(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF45_SHIFT))&LCD_WF_WF45_MASK)
#define LCD_WF_WF61_MASK                         0xFF00u
#define LCD_WF_WF61_SHIFT                        8
#define LCD_WF_WF61_WIDTH                        8
#define LCD_WF_WF61(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF61_SHIFT))&LCD_WF_WF61_MASK)
#define LCD_WF_WF25_MASK                         0xFF00u
#define LCD_WF_WF25_SHIFT                        8
#define LCD_WF_WF25_WIDTH                        8
#define LCD_WF_WF25(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF25_SHIFT))&LCD_WF_WF25_MASK)
#define LCD_WF_WF17_MASK                         0xFF00u
#define LCD_WF_WF17_SHIFT                        8
#define LCD_WF_WF17_WIDTH                        8
#define LCD_WF_WF17(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF17_SHIFT))&LCD_WF_WF17_MASK)
#define LCD_WF_WF41_MASK                         0xFF00u
#define LCD_WF_WF41_SHIFT                        8
#define LCD_WF_WF41_WIDTH                        8
#define LCD_WF_WF41(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF41_SHIFT))&LCD_WF_WF41_MASK)
#define LCD_WF_WF13_MASK                         0xFF00u
#define LCD_WF_WF13_SHIFT                        8
#define LCD_WF_WF13_WIDTH                        8
#define LCD_WF_WF13(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF13_SHIFT))&LCD_WF_WF13_MASK)
#define LCD_WF_WF57_MASK                         0xFF00u
#define LCD_WF_WF57_SHIFT                        8
#define LCD_WF_WF57_WIDTH                        8
#define LCD_WF_WF57(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF57_SHIFT))&LCD_WF_WF57_MASK)
#define LCD_WF_WF53_MASK                         0xFF00u
#define LCD_WF_WF53_SHIFT                        8
#define LCD_WF_WF53_WIDTH                        8
#define LCD_WF_WF53(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF53_SHIFT))&LCD_WF_WF53_MASK)
#define LCD_WF_WF37_MASK                         0xFF00u
#define LCD_WF_WF37_SHIFT                        8
#define LCD_WF_WF37_WIDTH                        8
#define LCD_WF_WF37(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF37_SHIFT))&LCD_WF_WF37_MASK)
#define LCD_WF_WF9_MASK                          0xFF00u
#define LCD_WF_WF9_SHIFT                         8
#define LCD_WF_WF9_WIDTH                         8
#define LCD_WF_WF9(x)                            (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF9_SHIFT))&LCD_WF_WF9_MASK)
#define LCD_WF_WF1_MASK                          0xFF00u
#define LCD_WF_WF1_SHIFT                         8
#define LCD_WF_WF1_WIDTH                         8
#define LCD_WF_WF1(x)                            (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF1_SHIFT))&LCD_WF_WF1_MASK)
#define LCD_WF_WF29_MASK                         0xFF00u
#define LCD_WF_WF29_SHIFT                        8
#define LCD_WF_WF29_WIDTH                        8
#define LCD_WF_WF29(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF29_SHIFT))&LCD_WF_WF29_MASK)
#define LCD_WF_WF33_MASK                         0xFF00u
#define LCD_WF_WF33_SHIFT                        8
#define LCD_WF_WF33_WIDTH                        8
#define LCD_WF_WF33(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF33_SHIFT))&LCD_WF_WF33_MASK)
#define LCD_WF_WF21_MASK                         0xFF00u
#define LCD_WF_WF21_SHIFT                        8
#define LCD_WF_WF21_WIDTH                        8
#define LCD_WF_WF21(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF21_SHIFT))&LCD_WF_WF21_MASK)
#define LCD_WF_WF26_MASK                         0xFF0000u
#define LCD_WF_WF26_SHIFT                        16
#define LCD_WF_WF26_WIDTH                        8
#define LCD_WF_WF26(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF26_SHIFT))&LCD_WF_WF26_MASK)
#define LCD_WF_WF46_MASK                         0xFF0000u
#define LCD_WF_WF46_SHIFT                        16
#define LCD_WF_WF46_WIDTH                        8
#define LCD_WF_WF46(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF46_SHIFT))&LCD_WF_WF46_MASK)
#define LCD_WF_WF6_MASK                          0xFF0000u
#define LCD_WF_WF6_SHIFT                         16
#define LCD_WF_WF6_WIDTH                         8
#define LCD_WF_WF6(x)                            (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF6_SHIFT))&LCD_WF_WF6_MASK)
#define LCD_WF_WF42_MASK                         0xFF0000u
#define LCD_WF_WF42_SHIFT                        16
#define LCD_WF_WF42_WIDTH                        8
#define LCD_WF_WF42(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF42_SHIFT))&LCD_WF_WF42_MASK)
#define LCD_WF_WF18_MASK                         0xFF0000u
#define LCD_WF_WF18_SHIFT                        16
#define LCD_WF_WF18_WIDTH                        8
#define LCD_WF_WF18(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF18_SHIFT))&LCD_WF_WF18_MASK)
#define LCD_WF_WF38_MASK                         0xFF0000u
#define LCD_WF_WF38_SHIFT                        16
#define LCD_WF_WF38_WIDTH                        8
#define LCD_WF_WF38(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF38_SHIFT))&LCD_WF_WF38_MASK)
#define LCD_WF_WF22_MASK                         0xFF0000u
#define LCD_WF_WF22_SHIFT                        16
#define LCD_WF_WF22_WIDTH                        8
#define LCD_WF_WF22(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF22_SHIFT))&LCD_WF_WF22_MASK)
#define LCD_WF_WF34_MASK                         0xFF0000u
#define LCD_WF_WF34_SHIFT                        16
#define LCD_WF_WF34_WIDTH                        8
#define LCD_WF_WF34(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF34_SHIFT))&LCD_WF_WF34_MASK)
#define LCD_WF_WF50_MASK                         0xFF0000u
#define LCD_WF_WF50_SHIFT                        16
#define LCD_WF_WF50_WIDTH                        8
#define LCD_WF_WF50(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF50_SHIFT))&LCD_WF_WF50_MASK)
#define LCD_WF_WF14_MASK                         0xFF0000u
#define LCD_WF_WF14_SHIFT                        16
#define LCD_WF_WF14_WIDTH                        8
#define LCD_WF_WF14(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF14_SHIFT))&LCD_WF_WF14_MASK)
#define LCD_WF_WF54_MASK                         0xFF0000u
#define LCD_WF_WF54_SHIFT                        16
#define LCD_WF_WF54_WIDTH                        8
#define LCD_WF_WF54(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF54_SHIFT))&LCD_WF_WF54_MASK)
#define LCD_WF_WF2_MASK                          0xFF0000u
#define LCD_WF_WF2_SHIFT                         16
#define LCD_WF_WF2_WIDTH                         8
#define LCD_WF_WF2(x)                            (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF2_SHIFT))&LCD_WF_WF2_MASK)
#define LCD_WF_WF58_MASK                         0xFF0000u
#define LCD_WF_WF58_SHIFT                        16
#define LCD_WF_WF58_WIDTH                        8
#define LCD_WF_WF58(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF58_SHIFT))&LCD_WF_WF58_MASK)
#define LCD_WF_WF30_MASK                         0xFF0000u
#define LCD_WF_WF30_SHIFT                        16
#define LCD_WF_WF30_WIDTH                        8
#define LCD_WF_WF30(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF30_SHIFT))&LCD_WF_WF30_MASK)
#define LCD_WF_WF62_MASK                         0xFF0000u
#define LCD_WF_WF62_SHIFT                        16
#define LCD_WF_WF62_WIDTH                        8
#define LCD_WF_WF62(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF62_SHIFT))&LCD_WF_WF62_MASK)
#define LCD_WF_WF10_MASK                         0xFF0000u
#define LCD_WF_WF10_SHIFT                        16
#define LCD_WF_WF10_WIDTH                        8
#define LCD_WF_WF10(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF10_SHIFT))&LCD_WF_WF10_MASK)
#define LCD_WF_WF63_MASK                         0xFF000000u
#define LCD_WF_WF63_SHIFT                        24
#define LCD_WF_WF63_WIDTH                        8
#define LCD_WF_WF63(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF63_SHIFT))&LCD_WF_WF63_MASK)
#define LCD_WF_WF59_MASK                         0xFF000000u
#define LCD_WF_WF59_SHIFT                        24
#define LCD_WF_WF59_WIDTH                        8
#define LCD_WF_WF59(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF59_SHIFT))&LCD_WF_WF59_MASK)
#define LCD_WF_WF55_MASK                         0xFF000000u
#define LCD_WF_WF55_SHIFT                        24
#define LCD_WF_WF55_WIDTH                        8
#define LCD_WF_WF55(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF55_SHIFT))&LCD_WF_WF55_MASK)
#define LCD_WF_WF3_MASK                          0xFF000000u
#define LCD_WF_WF3_SHIFT                         24
#define LCD_WF_WF3_WIDTH                         8
#define LCD_WF_WF3(x)                            (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF3_SHIFT))&LCD_WF_WF3_MASK)
#define LCD_WF_WF51_MASK                         0xFF000000u
#define LCD_WF_WF51_SHIFT                        24
#define LCD_WF_WF51_WIDTH                        8
#define LCD_WF_WF51(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF51_SHIFT))&LCD_WF_WF51_MASK)
#define LCD_WF_WF47_MASK                         0xFF000000u
#define LCD_WF_WF47_SHIFT                        24
#define LCD_WF_WF47_WIDTH                        8
#define LCD_WF_WF47(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF47_SHIFT))&LCD_WF_WF47_MASK)
#define LCD_WF_WF43_MASK                         0xFF000000u
#define LCD_WF_WF43_SHIFT                        24
#define LCD_WF_WF43_WIDTH                        8
#define LCD_WF_WF43(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF43_SHIFT))&LCD_WF_WF43_MASK)
#define LCD_WF_WF7_MASK                          0xFF000000u
#define LCD_WF_WF7_SHIFT                         24
#define LCD_WF_WF7_WIDTH                         8
#define LCD_WF_WF7(x)                            (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF7_SHIFT))&LCD_WF_WF7_MASK)
#define LCD_WF_WF39_MASK                         0xFF000000u
#define LCD_WF_WF39_SHIFT                        24
#define LCD_WF_WF39_WIDTH                        8
#define LCD_WF_WF39(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF39_SHIFT))&LCD_WF_WF39_MASK)
#define LCD_WF_WF35_MASK                         0xFF000000u
#define LCD_WF_WF35_SHIFT                        24
#define LCD_WF_WF35_WIDTH                        8
#define LCD_WF_WF35(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF35_SHIFT))&LCD_WF_WF35_MASK)
#define LCD_WF_WF31_MASK                         0xFF000000u
#define LCD_WF_WF31_SHIFT                        24
#define LCD_WF_WF31_WIDTH                        8
#define LCD_WF_WF31(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF31_SHIFT))&LCD_WF_WF31_MASK)
#define LCD_WF_WF11_MASK                         0xFF000000u
#define LCD_WF_WF11_SHIFT                        24
#define LCD_WF_WF11_WIDTH                        8
#define LCD_WF_WF11(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF11_SHIFT))&LCD_WF_WF11_MASK)
#define LCD_WF_WF27_MASK                         0xFF000000u
#define LCD_WF_WF27_SHIFT                        24
#define LCD_WF_WF27_WIDTH                        8
#define LCD_WF_WF27(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF27_SHIFT))&LCD_WF_WF27_MASK)
#define LCD_WF_WF23_MASK                         0xFF000000u
#define LCD_WF_WF23_SHIFT                        24
#define LCD_WF_WF23_WIDTH                        8
#define LCD_WF_WF23(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF23_SHIFT))&LCD_WF_WF23_MASK)
#define LCD_WF_WF19_MASK                         0xFF000000u
#define LCD_WF_WF19_SHIFT                        24
#define LCD_WF_WF19_WIDTH                        8
#define LCD_WF_WF19(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF19_SHIFT))&LCD_WF_WF19_MASK)
#define LCD_WF_WF15_MASK                         0xFF000000u
#define LCD_WF_WF15_SHIFT                        24
#define LCD_WF_WF15_WIDTH                        8
#define LCD_WF_WF15(x)                           (((uint32_t)(((uint32_t)(x))<<LCD_WF_WF15_SHIFT))&LCD_WF_WF15_MASK)
/* WF8B Bit Fields */
#define LCD_WF8B_BPALCD0_MASK                    0x1u
#define LCD_WF8B_BPALCD0_SHIFT                   0
#define LCD_WF8B_BPALCD0_WIDTH                   1
#define LCD_WF8B_BPALCD0(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD0_SHIFT))&LCD_WF8B_BPALCD0_MASK)
#define LCD_WF8B_BPALCD63_MASK                   0x1u
#define LCD_WF8B_BPALCD63_SHIFT                  0
#define LCD_WF8B_BPALCD63_WIDTH                  1
#define LCD_WF8B_BPALCD63(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD63_SHIFT))&LCD_WF8B_BPALCD63_MASK)
#define LCD_WF8B_BPALCD62_MASK                   0x1u
#define LCD_WF8B_BPALCD62_SHIFT                  0
#define LCD_WF8B_BPALCD62_WIDTH                  1
#define LCD_WF8B_BPALCD62(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD62_SHIFT))&LCD_WF8B_BPALCD62_MASK)
#define LCD_WF8B_BPALCD61_MASK                   0x1u
#define LCD_WF8B_BPALCD61_SHIFT                  0
#define LCD_WF8B_BPALCD61_WIDTH                  1
#define LCD_WF8B_BPALCD61(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD61_SHIFT))&LCD_WF8B_BPALCD61_MASK)
#define LCD_WF8B_BPALCD60_MASK                   0x1u
#define LCD_WF8B_BPALCD60_SHIFT                  0
#define LCD_WF8B_BPALCD60_WIDTH                  1
#define LCD_WF8B_BPALCD60(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD60_SHIFT))&LCD_WF8B_BPALCD60_MASK)
#define LCD_WF8B_BPALCD59_MASK                   0x1u
#define LCD_WF8B_BPALCD59_SHIFT                  0
#define LCD_WF8B_BPALCD59_WIDTH                  1
#define LCD_WF8B_BPALCD59(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD59_SHIFT))&LCD_WF8B_BPALCD59_MASK)
#define LCD_WF8B_BPALCD58_MASK                   0x1u
#define LCD_WF8B_BPALCD58_SHIFT                  0
#define LCD_WF8B_BPALCD58_WIDTH                  1
#define LCD_WF8B_BPALCD58(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD58_SHIFT))&LCD_WF8B_BPALCD58_MASK)
#define LCD_WF8B_BPALCD57_MASK                   0x1u
#define LCD_WF8B_BPALCD57_SHIFT                  0
#define LCD_WF8B_BPALCD57_WIDTH                  1
#define LCD_WF8B_BPALCD57(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD57_SHIFT))&LCD_WF8B_BPALCD57_MASK)
#define LCD_WF8B_BPALCD1_MASK                    0x1u
#define LCD_WF8B_BPALCD1_SHIFT                   0
#define LCD_WF8B_BPALCD1_WIDTH                   1
#define LCD_WF8B_BPALCD1(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD1_SHIFT))&LCD_WF8B_BPALCD1_MASK)
#define LCD_WF8B_BPALCD56_MASK                   0x1u
#define LCD_WF8B_BPALCD56_SHIFT                  0
#define LCD_WF8B_BPALCD56_WIDTH                  1
#define LCD_WF8B_BPALCD56(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD56_SHIFT))&LCD_WF8B_BPALCD56_MASK)
#define LCD_WF8B_BPALCD55_MASK                   0x1u
#define LCD_WF8B_BPALCD55_SHIFT                  0
#define LCD_WF8B_BPALCD55_WIDTH                  1
#define LCD_WF8B_BPALCD55(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD55_SHIFT))&LCD_WF8B_BPALCD55_MASK)
#define LCD_WF8B_BPALCD54_MASK                   0x1u
#define LCD_WF8B_BPALCD54_SHIFT                  0
#define LCD_WF8B_BPALCD54_WIDTH                  1
#define LCD_WF8B_BPALCD54(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD54_SHIFT))&LCD_WF8B_BPALCD54_MASK)
#define LCD_WF8B_BPALCD53_MASK                   0x1u
#define LCD_WF8B_BPALCD53_SHIFT                  0
#define LCD_WF8B_BPALCD53_WIDTH                  1
#define LCD_WF8B_BPALCD53(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD53_SHIFT))&LCD_WF8B_BPALCD53_MASK)
#define LCD_WF8B_BPALCD52_MASK                   0x1u
#define LCD_WF8B_BPALCD52_SHIFT                  0
#define LCD_WF8B_BPALCD52_WIDTH                  1
#define LCD_WF8B_BPALCD52(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD52_SHIFT))&LCD_WF8B_BPALCD52_MASK)
#define LCD_WF8B_BPALCD51_MASK                   0x1u
#define LCD_WF8B_BPALCD51_SHIFT                  0
#define LCD_WF8B_BPALCD51_WIDTH                  1
#define LCD_WF8B_BPALCD51(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD51_SHIFT))&LCD_WF8B_BPALCD51_MASK)
#define LCD_WF8B_BPALCD50_MASK                   0x1u
#define LCD_WF8B_BPALCD50_SHIFT                  0
#define LCD_WF8B_BPALCD50_WIDTH                  1
#define LCD_WF8B_BPALCD50(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD50_SHIFT))&LCD_WF8B_BPALCD50_MASK)
#define LCD_WF8B_BPALCD2_MASK                    0x1u
#define LCD_WF8B_BPALCD2_SHIFT                   0
#define LCD_WF8B_BPALCD2_WIDTH                   1
#define LCD_WF8B_BPALCD2(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD2_SHIFT))&LCD_WF8B_BPALCD2_MASK)
#define LCD_WF8B_BPALCD49_MASK                   0x1u
#define LCD_WF8B_BPALCD49_SHIFT                  0
#define LCD_WF8B_BPALCD49_WIDTH                  1
#define LCD_WF8B_BPALCD49(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD49_SHIFT))&LCD_WF8B_BPALCD49_MASK)
#define LCD_WF8B_BPALCD48_MASK                   0x1u
#define LCD_WF8B_BPALCD48_SHIFT                  0
#define LCD_WF8B_BPALCD48_WIDTH                  1
#define LCD_WF8B_BPALCD48(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD48_SHIFT))&LCD_WF8B_BPALCD48_MASK)
#define LCD_WF8B_BPALCD47_MASK                   0x1u
#define LCD_WF8B_BPALCD47_SHIFT                  0
#define LCD_WF8B_BPALCD47_WIDTH                  1
#define LCD_WF8B_BPALCD47(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD47_SHIFT))&LCD_WF8B_BPALCD47_MASK)
#define LCD_WF8B_BPALCD46_MASK                   0x1u
#define LCD_WF8B_BPALCD46_SHIFT                  0
#define LCD_WF8B_BPALCD46_WIDTH                  1
#define LCD_WF8B_BPALCD46(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD46_SHIFT))&LCD_WF8B_BPALCD46_MASK)
#define LCD_WF8B_BPALCD45_MASK                   0x1u
#define LCD_WF8B_BPALCD45_SHIFT                  0
#define LCD_WF8B_BPALCD45_WIDTH                  1
#define LCD_WF8B_BPALCD45(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD45_SHIFT))&LCD_WF8B_BPALCD45_MASK)
#define LCD_WF8B_BPALCD44_MASK                   0x1u
#define LCD_WF8B_BPALCD44_SHIFT                  0
#define LCD_WF8B_BPALCD44_WIDTH                  1
#define LCD_WF8B_BPALCD44(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD44_SHIFT))&LCD_WF8B_BPALCD44_MASK)
#define LCD_WF8B_BPALCD43_MASK                   0x1u
#define LCD_WF8B_BPALCD43_SHIFT                  0
#define LCD_WF8B_BPALCD43_WIDTH                  1
#define LCD_WF8B_BPALCD43(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD43_SHIFT))&LCD_WF8B_BPALCD43_MASK)
#define LCD_WF8B_BPALCD3_MASK                    0x1u
#define LCD_WF8B_BPALCD3_SHIFT                   0
#define LCD_WF8B_BPALCD3_WIDTH                   1
#define LCD_WF8B_BPALCD3(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD3_SHIFT))&LCD_WF8B_BPALCD3_MASK)
#define LCD_WF8B_BPALCD42_MASK                   0x1u
#define LCD_WF8B_BPALCD42_SHIFT                  0
#define LCD_WF8B_BPALCD42_WIDTH                  1
#define LCD_WF8B_BPALCD42(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD42_SHIFT))&LCD_WF8B_BPALCD42_MASK)
#define LCD_WF8B_BPALCD41_MASK                   0x1u
#define LCD_WF8B_BPALCD41_SHIFT                  0
#define LCD_WF8B_BPALCD41_WIDTH                  1
#define LCD_WF8B_BPALCD41(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD41_SHIFT))&LCD_WF8B_BPALCD41_MASK)
#define LCD_WF8B_BPALCD40_MASK                   0x1u
#define LCD_WF8B_BPALCD40_SHIFT                  0
#define LCD_WF8B_BPALCD40_WIDTH                  1
#define LCD_WF8B_BPALCD40(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD40_SHIFT))&LCD_WF8B_BPALCD40_MASK)
#define LCD_WF8B_BPALCD39_MASK                   0x1u
#define LCD_WF8B_BPALCD39_SHIFT                  0
#define LCD_WF8B_BPALCD39_WIDTH                  1
#define LCD_WF8B_BPALCD39(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD39_SHIFT))&LCD_WF8B_BPALCD39_MASK)
#define LCD_WF8B_BPALCD38_MASK                   0x1u
#define LCD_WF8B_BPALCD38_SHIFT                  0
#define LCD_WF8B_BPALCD38_WIDTH                  1
#define LCD_WF8B_BPALCD38(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD38_SHIFT))&LCD_WF8B_BPALCD38_MASK)
#define LCD_WF8B_BPALCD37_MASK                   0x1u
#define LCD_WF8B_BPALCD37_SHIFT                  0
#define LCD_WF8B_BPALCD37_WIDTH                  1
#define LCD_WF8B_BPALCD37(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD37_SHIFT))&LCD_WF8B_BPALCD37_MASK)
#define LCD_WF8B_BPALCD36_MASK                   0x1u
#define LCD_WF8B_BPALCD36_SHIFT                  0
#define LCD_WF8B_BPALCD36_WIDTH                  1
#define LCD_WF8B_BPALCD36(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD36_SHIFT))&LCD_WF8B_BPALCD36_MASK)
#define LCD_WF8B_BPALCD4_MASK                    0x1u
#define LCD_WF8B_BPALCD4_SHIFT                   0
#define LCD_WF8B_BPALCD4_WIDTH                   1
#define LCD_WF8B_BPALCD4(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD4_SHIFT))&LCD_WF8B_BPALCD4_MASK)
#define LCD_WF8B_BPALCD35_MASK                   0x1u
#define LCD_WF8B_BPALCD35_SHIFT                  0
#define LCD_WF8B_BPALCD35_WIDTH                  1
#define LCD_WF8B_BPALCD35(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD35_SHIFT))&LCD_WF8B_BPALCD35_MASK)
#define LCD_WF8B_BPALCD34_MASK                   0x1u
#define LCD_WF8B_BPALCD34_SHIFT                  0
#define LCD_WF8B_BPALCD34_WIDTH                  1
#define LCD_WF8B_BPALCD34(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD34_SHIFT))&LCD_WF8B_BPALCD34_MASK)
#define LCD_WF8B_BPALCD33_MASK                   0x1u
#define LCD_WF8B_BPALCD33_SHIFT                  0
#define LCD_WF8B_BPALCD33_WIDTH                  1
#define LCD_WF8B_BPALCD33(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD33_SHIFT))&LCD_WF8B_BPALCD33_MASK)
#define LCD_WF8B_BPALCD32_MASK                   0x1u
#define LCD_WF8B_BPALCD32_SHIFT                  0
#define LCD_WF8B_BPALCD32_WIDTH                  1
#define LCD_WF8B_BPALCD32(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD32_SHIFT))&LCD_WF8B_BPALCD32_MASK)
#define LCD_WF8B_BPALCD31_MASK                   0x1u
#define LCD_WF8B_BPALCD31_SHIFT                  0
#define LCD_WF8B_BPALCD31_WIDTH                  1
#define LCD_WF8B_BPALCD31(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD31_SHIFT))&LCD_WF8B_BPALCD31_MASK)
#define LCD_WF8B_BPALCD30_MASK                   0x1u
#define LCD_WF8B_BPALCD30_SHIFT                  0
#define LCD_WF8B_BPALCD30_WIDTH                  1
#define LCD_WF8B_BPALCD30(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD30_SHIFT))&LCD_WF8B_BPALCD30_MASK)
#define LCD_WF8B_BPALCD29_MASK                   0x1u
#define LCD_WF8B_BPALCD29_SHIFT                  0
#define LCD_WF8B_BPALCD29_WIDTH                  1
#define LCD_WF8B_BPALCD29(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD29_SHIFT))&LCD_WF8B_BPALCD29_MASK)
#define LCD_WF8B_BPALCD5_MASK                    0x1u
#define LCD_WF8B_BPALCD5_SHIFT                   0
#define LCD_WF8B_BPALCD5_WIDTH                   1
#define LCD_WF8B_BPALCD5(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD5_SHIFT))&LCD_WF8B_BPALCD5_MASK)
#define LCD_WF8B_BPALCD28_MASK                   0x1u
#define LCD_WF8B_BPALCD28_SHIFT                  0
#define LCD_WF8B_BPALCD28_WIDTH                  1
#define LCD_WF8B_BPALCD28(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD28_SHIFT))&LCD_WF8B_BPALCD28_MASK)
#define LCD_WF8B_BPALCD27_MASK                   0x1u
#define LCD_WF8B_BPALCD27_SHIFT                  0
#define LCD_WF8B_BPALCD27_WIDTH                  1
#define LCD_WF8B_BPALCD27(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD27_SHIFT))&LCD_WF8B_BPALCD27_MASK)
#define LCD_WF8B_BPALCD26_MASK                   0x1u
#define LCD_WF8B_BPALCD26_SHIFT                  0
#define LCD_WF8B_BPALCD26_WIDTH                  1
#define LCD_WF8B_BPALCD26(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD26_SHIFT))&LCD_WF8B_BPALCD26_MASK)
#define LCD_WF8B_BPALCD25_MASK                   0x1u
#define LCD_WF8B_BPALCD25_SHIFT                  0
#define LCD_WF8B_BPALCD25_WIDTH                  1
#define LCD_WF8B_BPALCD25(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD25_SHIFT))&LCD_WF8B_BPALCD25_MASK)
#define LCD_WF8B_BPALCD24_MASK                   0x1u
#define LCD_WF8B_BPALCD24_SHIFT                  0
#define LCD_WF8B_BPALCD24_WIDTH                  1
#define LCD_WF8B_BPALCD24(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD24_SHIFT))&LCD_WF8B_BPALCD24_MASK)
#define LCD_WF8B_BPALCD23_MASK                   0x1u
#define LCD_WF8B_BPALCD23_SHIFT                  0
#define LCD_WF8B_BPALCD23_WIDTH                  1
#define LCD_WF8B_BPALCD23(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD23_SHIFT))&LCD_WF8B_BPALCD23_MASK)
#define LCD_WF8B_BPALCD22_MASK                   0x1u
#define LCD_WF8B_BPALCD22_SHIFT                  0
#define LCD_WF8B_BPALCD22_WIDTH                  1
#define LCD_WF8B_BPALCD22(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD22_SHIFT))&LCD_WF8B_BPALCD22_MASK)
#define LCD_WF8B_BPALCD6_MASK                    0x1u
#define LCD_WF8B_BPALCD6_SHIFT                   0
#define LCD_WF8B_BPALCD6_WIDTH                   1
#define LCD_WF8B_BPALCD6(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD6_SHIFT))&LCD_WF8B_BPALCD6_MASK)
#define LCD_WF8B_BPALCD21_MASK                   0x1u
#define LCD_WF8B_BPALCD21_SHIFT                  0
#define LCD_WF8B_BPALCD21_WIDTH                  1
#define LCD_WF8B_BPALCD21(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD21_SHIFT))&LCD_WF8B_BPALCD21_MASK)
#define LCD_WF8B_BPALCD20_MASK                   0x1u
#define LCD_WF8B_BPALCD20_SHIFT                  0
#define LCD_WF8B_BPALCD20_WIDTH                  1
#define LCD_WF8B_BPALCD20(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD20_SHIFT))&LCD_WF8B_BPALCD20_MASK)
#define LCD_WF8B_BPALCD19_MASK                   0x1u
#define LCD_WF8B_BPALCD19_SHIFT                  0
#define LCD_WF8B_BPALCD19_WIDTH                  1
#define LCD_WF8B_BPALCD19(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD19_SHIFT))&LCD_WF8B_BPALCD19_MASK)
#define LCD_WF8B_BPALCD18_MASK                   0x1u
#define LCD_WF8B_BPALCD18_SHIFT                  0
#define LCD_WF8B_BPALCD18_WIDTH                  1
#define LCD_WF8B_BPALCD18(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD18_SHIFT))&LCD_WF8B_BPALCD18_MASK)
#define LCD_WF8B_BPALCD17_MASK                   0x1u
#define LCD_WF8B_BPALCD17_SHIFT                  0
#define LCD_WF8B_BPALCD17_WIDTH                  1
#define LCD_WF8B_BPALCD17(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD17_SHIFT))&LCD_WF8B_BPALCD17_MASK)
#define LCD_WF8B_BPALCD16_MASK                   0x1u
#define LCD_WF8B_BPALCD16_SHIFT                  0
#define LCD_WF8B_BPALCD16_WIDTH                  1
#define LCD_WF8B_BPALCD16(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD16_SHIFT))&LCD_WF8B_BPALCD16_MASK)
#define LCD_WF8B_BPALCD15_MASK                   0x1u
#define LCD_WF8B_BPALCD15_SHIFT                  0
#define LCD_WF8B_BPALCD15_WIDTH                  1
#define LCD_WF8B_BPALCD15(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD15_SHIFT))&LCD_WF8B_BPALCD15_MASK)
#define LCD_WF8B_BPALCD7_MASK                    0x1u
#define LCD_WF8B_BPALCD7_SHIFT                   0
#define LCD_WF8B_BPALCD7_WIDTH                   1
#define LCD_WF8B_BPALCD7(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD7_SHIFT))&LCD_WF8B_BPALCD7_MASK)
#define LCD_WF8B_BPALCD14_MASK                   0x1u
#define LCD_WF8B_BPALCD14_SHIFT                  0
#define LCD_WF8B_BPALCD14_WIDTH                  1
#define LCD_WF8B_BPALCD14(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD14_SHIFT))&LCD_WF8B_BPALCD14_MASK)
#define LCD_WF8B_BPALCD13_MASK                   0x1u
#define LCD_WF8B_BPALCD13_SHIFT                  0
#define LCD_WF8B_BPALCD13_WIDTH                  1
#define LCD_WF8B_BPALCD13(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD13_SHIFT))&LCD_WF8B_BPALCD13_MASK)
#define LCD_WF8B_BPALCD12_MASK                   0x1u
#define LCD_WF8B_BPALCD12_SHIFT                  0
#define LCD_WF8B_BPALCD12_WIDTH                  1
#define LCD_WF8B_BPALCD12(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD12_SHIFT))&LCD_WF8B_BPALCD12_MASK)
#define LCD_WF8B_BPALCD11_MASK                   0x1u
#define LCD_WF8B_BPALCD11_SHIFT                  0
#define LCD_WF8B_BPALCD11_WIDTH                  1
#define LCD_WF8B_BPALCD11(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD11_SHIFT))&LCD_WF8B_BPALCD11_MASK)
#define LCD_WF8B_BPALCD10_MASK                   0x1u
#define LCD_WF8B_BPALCD10_SHIFT                  0
#define LCD_WF8B_BPALCD10_WIDTH                  1
#define LCD_WF8B_BPALCD10(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD10_SHIFT))&LCD_WF8B_BPALCD10_MASK)
#define LCD_WF8B_BPALCD9_MASK                    0x1u
#define LCD_WF8B_BPALCD9_SHIFT                   0
#define LCD_WF8B_BPALCD9_WIDTH                   1
#define LCD_WF8B_BPALCD9(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD9_SHIFT))&LCD_WF8B_BPALCD9_MASK)
#define LCD_WF8B_BPALCD8_MASK                    0x1u
#define LCD_WF8B_BPALCD8_SHIFT                   0
#define LCD_WF8B_BPALCD8_WIDTH                   1
#define LCD_WF8B_BPALCD8(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPALCD8_SHIFT))&LCD_WF8B_BPALCD8_MASK)
#define LCD_WF8B_BPBLCD1_MASK                    0x2u
#define LCD_WF8B_BPBLCD1_SHIFT                   1
#define LCD_WF8B_BPBLCD1_WIDTH                   1
#define LCD_WF8B_BPBLCD1(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD1_SHIFT))&LCD_WF8B_BPBLCD1_MASK)
#define LCD_WF8B_BPBLCD32_MASK                   0x2u
#define LCD_WF8B_BPBLCD32_SHIFT                  1
#define LCD_WF8B_BPBLCD32_WIDTH                  1
#define LCD_WF8B_BPBLCD32(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD32_SHIFT))&LCD_WF8B_BPBLCD32_MASK)
#define LCD_WF8B_BPBLCD30_MASK                   0x2u
#define LCD_WF8B_BPBLCD30_SHIFT                  1
#define LCD_WF8B_BPBLCD30_WIDTH                  1
#define LCD_WF8B_BPBLCD30(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD30_SHIFT))&LCD_WF8B_BPBLCD30_MASK)
#define LCD_WF8B_BPBLCD60_MASK                   0x2u
#define LCD_WF8B_BPBLCD60_SHIFT                  1
#define LCD_WF8B_BPBLCD60_WIDTH                  1
#define LCD_WF8B_BPBLCD60(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD60_SHIFT))&LCD_WF8B_BPBLCD60_MASK)
#define LCD_WF8B_BPBLCD24_MASK                   0x2u
#define LCD_WF8B_BPBLCD24_SHIFT                  1
#define LCD_WF8B_BPBLCD24_WIDTH                  1
#define LCD_WF8B_BPBLCD24(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD24_SHIFT))&LCD_WF8B_BPBLCD24_MASK)
#define LCD_WF8B_BPBLCD28_MASK                   0x2u
#define LCD_WF8B_BPBLCD28_SHIFT                  1
#define LCD_WF8B_BPBLCD28_WIDTH                  1
#define LCD_WF8B_BPBLCD28(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD28_SHIFT))&LCD_WF8B_BPBLCD28_MASK)
#define LCD_WF8B_BPBLCD23_MASK                   0x2u
#define LCD_WF8B_BPBLCD23_SHIFT                  1
#define LCD_WF8B_BPBLCD23_WIDTH                  1
#define LCD_WF8B_BPBLCD23(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD23_SHIFT))&LCD_WF8B_BPBLCD23_MASK)
#define LCD_WF8B_BPBLCD48_MASK                   0x2u
#define LCD_WF8B_BPBLCD48_SHIFT                  1
#define LCD_WF8B_BPBLCD48_WIDTH                  1
#define LCD_WF8B_BPBLCD48(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD48_SHIFT))&LCD_WF8B_BPBLCD48_MASK)
#define LCD_WF8B_BPBLCD10_MASK                   0x2u
#define LCD_WF8B_BPBLCD10_SHIFT                  1
#define LCD_WF8B_BPBLCD10_WIDTH                  1
#define LCD_WF8B_BPBLCD10(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD10_SHIFT))&LCD_WF8B_BPBLCD10_MASK)
#define LCD_WF8B_BPBLCD15_MASK                   0x2u
#define LCD_WF8B_BPBLCD15_SHIFT                  1
#define LCD_WF8B_BPBLCD15_WIDTH                  1
#define LCD_WF8B_BPBLCD15(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD15_SHIFT))&LCD_WF8B_BPBLCD15_MASK)
#define LCD_WF8B_BPBLCD36_MASK                   0x2u
#define LCD_WF8B_BPBLCD36_SHIFT                  1
#define LCD_WF8B_BPBLCD36_WIDTH                  1
#define LCD_WF8B_BPBLCD36(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD36_SHIFT))&LCD_WF8B_BPBLCD36_MASK)
#define LCD_WF8B_BPBLCD44_MASK                   0x2u
#define LCD_WF8B_BPBLCD44_SHIFT                  1
#define LCD_WF8B_BPBLCD44_WIDTH                  1
#define LCD_WF8B_BPBLCD44(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD44_SHIFT))&LCD_WF8B_BPBLCD44_MASK)
#define LCD_WF8B_BPBLCD62_MASK                   0x2u
#define LCD_WF8B_BPBLCD62_SHIFT                  1
#define LCD_WF8B_BPBLCD62_WIDTH                  1
#define LCD_WF8B_BPBLCD62(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD62_SHIFT))&LCD_WF8B_BPBLCD62_MASK)
#define LCD_WF8B_BPBLCD53_MASK                   0x2u
#define LCD_WF8B_BPBLCD53_SHIFT                  1
#define LCD_WF8B_BPBLCD53_WIDTH                  1
#define LCD_WF8B_BPBLCD53(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD53_SHIFT))&LCD_WF8B_BPBLCD53_MASK)
#define LCD_WF8B_BPBLCD22_MASK                   0x2u
#define LCD_WF8B_BPBLCD22_SHIFT                  1
#define LCD_WF8B_BPBLCD22_WIDTH                  1
#define LCD_WF8B_BPBLCD22(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD22_SHIFT))&LCD_WF8B_BPBLCD22_MASK)
#define LCD_WF8B_BPBLCD47_MASK                   0x2u
#define LCD_WF8B_BPBLCD47_SHIFT                  1
#define LCD_WF8B_BPBLCD47_WIDTH                  1
#define LCD_WF8B_BPBLCD47(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD47_SHIFT))&LCD_WF8B_BPBLCD47_MASK)
#define LCD_WF8B_BPBLCD33_MASK                   0x2u
#define LCD_WF8B_BPBLCD33_SHIFT                  1
#define LCD_WF8B_BPBLCD33_WIDTH                  1
#define LCD_WF8B_BPBLCD33(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD33_SHIFT))&LCD_WF8B_BPBLCD33_MASK)
#define LCD_WF8B_BPBLCD2_MASK                    0x2u
#define LCD_WF8B_BPBLCD2_SHIFT                   1
#define LCD_WF8B_BPBLCD2_WIDTH                   1
#define LCD_WF8B_BPBLCD2(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD2_SHIFT))&LCD_WF8B_BPBLCD2_MASK)
#define LCD_WF8B_BPBLCD49_MASK                   0x2u
#define LCD_WF8B_BPBLCD49_SHIFT                  1
#define LCD_WF8B_BPBLCD49_WIDTH                  1
#define LCD_WF8B_BPBLCD49(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD49_SHIFT))&LCD_WF8B_BPBLCD49_MASK)
#define LCD_WF8B_BPBLCD0_MASK                    0x2u
#define LCD_WF8B_BPBLCD0_SHIFT                   1
#define LCD_WF8B_BPBLCD0_WIDTH                   1
#define LCD_WF8B_BPBLCD0(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD0_SHIFT))&LCD_WF8B_BPBLCD0_MASK)
#define LCD_WF8B_BPBLCD55_MASK                   0x2u
#define LCD_WF8B_BPBLCD55_SHIFT                  1
#define LCD_WF8B_BPBLCD55_WIDTH                  1
#define LCD_WF8B_BPBLCD55(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD55_SHIFT))&LCD_WF8B_BPBLCD55_MASK)
#define LCD_WF8B_BPBLCD56_MASK                   0x2u
#define LCD_WF8B_BPBLCD56_SHIFT                  1
#define LCD_WF8B_BPBLCD56_WIDTH                  1
#define LCD_WF8B_BPBLCD56(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD56_SHIFT))&LCD_WF8B_BPBLCD56_MASK)
#define LCD_WF8B_BPBLCD21_MASK                   0x2u
#define LCD_WF8B_BPBLCD21_SHIFT                  1
#define LCD_WF8B_BPBLCD21_WIDTH                  1
#define LCD_WF8B_BPBLCD21(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD21_SHIFT))&LCD_WF8B_BPBLCD21_MASK)
#define LCD_WF8B_BPBLCD6_MASK                    0x2u
#define LCD_WF8B_BPBLCD6_SHIFT                   1
#define LCD_WF8B_BPBLCD6_WIDTH                   1
#define LCD_WF8B_BPBLCD6(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD6_SHIFT))&LCD_WF8B_BPBLCD6_MASK)
#define LCD_WF8B_BPBLCD29_MASK                   0x2u
#define LCD_WF8B_BPBLCD29_SHIFT                  1
#define LCD_WF8B_BPBLCD29_WIDTH                  1
#define LCD_WF8B_BPBLCD29(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD29_SHIFT))&LCD_WF8B_BPBLCD29_MASK)
#define LCD_WF8B_BPBLCD25_MASK                   0x2u
#define LCD_WF8B_BPBLCD25_SHIFT                  1
#define LCD_WF8B_BPBLCD25_WIDTH                  1
#define LCD_WF8B_BPBLCD25(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD25_SHIFT))&LCD_WF8B_BPBLCD25_MASK)
#define LCD_WF8B_BPBLCD8_MASK                    0x2u
#define LCD_WF8B_BPBLCD8_SHIFT                   1
#define LCD_WF8B_BPBLCD8_WIDTH                   1
#define LCD_WF8B_BPBLCD8(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD8_SHIFT))&LCD_WF8B_BPBLCD8_MASK)
#define LCD_WF8B_BPBLCD54_MASK                   0x2u
#define LCD_WF8B_BPBLCD54_SHIFT                  1
#define LCD_WF8B_BPBLCD54_WIDTH                  1
#define LCD_WF8B_BPBLCD54(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD54_SHIFT))&LCD_WF8B_BPBLCD54_MASK)
#define LCD_WF8B_BPBLCD38_MASK                   0x2u
#define LCD_WF8B_BPBLCD38_SHIFT                  1
#define LCD_WF8B_BPBLCD38_WIDTH                  1
#define LCD_WF8B_BPBLCD38(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD38_SHIFT))&LCD_WF8B_BPBLCD38_MASK)
#define LCD_WF8B_BPBLCD43_MASK                   0x2u
#define LCD_WF8B_BPBLCD43_SHIFT                  1
#define LCD_WF8B_BPBLCD43_WIDTH                  1
#define LCD_WF8B_BPBLCD43(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD43_SHIFT))&LCD_WF8B_BPBLCD43_MASK)
#define LCD_WF8B_BPBLCD20_MASK                   0x2u
#define LCD_WF8B_BPBLCD20_SHIFT                  1
#define LCD_WF8B_BPBLCD20_WIDTH                  1
#define LCD_WF8B_BPBLCD20(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD20_SHIFT))&LCD_WF8B_BPBLCD20_MASK)
#define LCD_WF8B_BPBLCD9_MASK                    0x2u
#define LCD_WF8B_BPBLCD9_SHIFT                   1
#define LCD_WF8B_BPBLCD9_WIDTH                   1
#define LCD_WF8B_BPBLCD9(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD9_SHIFT))&LCD_WF8B_BPBLCD9_MASK)
#define LCD_WF8B_BPBLCD7_MASK                    0x2u
#define LCD_WF8B_BPBLCD7_SHIFT                   1
#define LCD_WF8B_BPBLCD7_WIDTH                   1
#define LCD_WF8B_BPBLCD7(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD7_SHIFT))&LCD_WF8B_BPBLCD7_MASK)
#define LCD_WF8B_BPBLCD50_MASK                   0x2u
#define LCD_WF8B_BPBLCD50_SHIFT                  1
#define LCD_WF8B_BPBLCD50_WIDTH                  1
#define LCD_WF8B_BPBLCD50(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD50_SHIFT))&LCD_WF8B_BPBLCD50_MASK)
#define LCD_WF8B_BPBLCD40_MASK                   0x2u
#define LCD_WF8B_BPBLCD40_SHIFT                  1
#define LCD_WF8B_BPBLCD40_WIDTH                  1
#define LCD_WF8B_BPBLCD40(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD40_SHIFT))&LCD_WF8B_BPBLCD40_MASK)
#define LCD_WF8B_BPBLCD63_MASK                   0x2u
#define LCD_WF8B_BPBLCD63_SHIFT                  1
#define LCD_WF8B_BPBLCD63_WIDTH                  1
#define LCD_WF8B_BPBLCD63(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD63_SHIFT))&LCD_WF8B_BPBLCD63_MASK)
#define LCD_WF8B_BPBLCD26_MASK                   0x2u
#define LCD_WF8B_BPBLCD26_SHIFT                  1
#define LCD_WF8B_BPBLCD26_WIDTH                  1
#define LCD_WF8B_BPBLCD26(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD26_SHIFT))&LCD_WF8B_BPBLCD26_MASK)
#define LCD_WF8B_BPBLCD12_MASK                   0x2u
#define LCD_WF8B_BPBLCD12_SHIFT                  1
#define LCD_WF8B_BPBLCD12_WIDTH                  1
#define LCD_WF8B_BPBLCD12(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD12_SHIFT))&LCD_WF8B_BPBLCD12_MASK)
#define LCD_WF8B_BPBLCD19_MASK                   0x2u
#define LCD_WF8B_BPBLCD19_SHIFT                  1
#define LCD_WF8B_BPBLCD19_WIDTH                  1
#define LCD_WF8B_BPBLCD19(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD19_SHIFT))&LCD_WF8B_BPBLCD19_MASK)
#define LCD_WF8B_BPBLCD34_MASK                   0x2u
#define LCD_WF8B_BPBLCD34_SHIFT                  1
#define LCD_WF8B_BPBLCD34_WIDTH                  1
#define LCD_WF8B_BPBLCD34(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD34_SHIFT))&LCD_WF8B_BPBLCD34_MASK)
#define LCD_WF8B_BPBLCD39_MASK                   0x2u
#define LCD_WF8B_BPBLCD39_SHIFT                  1
#define LCD_WF8B_BPBLCD39_WIDTH                  1
#define LCD_WF8B_BPBLCD39(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD39_SHIFT))&LCD_WF8B_BPBLCD39_MASK)
#define LCD_WF8B_BPBLCD59_MASK                   0x2u
#define LCD_WF8B_BPBLCD59_SHIFT                  1
#define LCD_WF8B_BPBLCD59_WIDTH                  1
#define LCD_WF8B_BPBLCD59(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD59_SHIFT))&LCD_WF8B_BPBLCD59_MASK)
#define LCD_WF8B_BPBLCD61_MASK                   0x2u
#define LCD_WF8B_BPBLCD61_SHIFT                  1
#define LCD_WF8B_BPBLCD61_WIDTH                  1
#define LCD_WF8B_BPBLCD61(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD61_SHIFT))&LCD_WF8B_BPBLCD61_MASK)
#define LCD_WF8B_BPBLCD37_MASK                   0x2u
#define LCD_WF8B_BPBLCD37_SHIFT                  1
#define LCD_WF8B_BPBLCD37_WIDTH                  1
#define LCD_WF8B_BPBLCD37(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD37_SHIFT))&LCD_WF8B_BPBLCD37_MASK)
#define LCD_WF8B_BPBLCD31_MASK                   0x2u
#define LCD_WF8B_BPBLCD31_SHIFT                  1
#define LCD_WF8B_BPBLCD31_WIDTH                  1
#define LCD_WF8B_BPBLCD31(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD31_SHIFT))&LCD_WF8B_BPBLCD31_MASK)
#define LCD_WF8B_BPBLCD58_MASK                   0x2u
#define LCD_WF8B_BPBLCD58_SHIFT                  1
#define LCD_WF8B_BPBLCD58_WIDTH                  1
#define LCD_WF8B_BPBLCD58(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD58_SHIFT))&LCD_WF8B_BPBLCD58_MASK)
#define LCD_WF8B_BPBLCD18_MASK                   0x2u
#define LCD_WF8B_BPBLCD18_SHIFT                  1
#define LCD_WF8B_BPBLCD18_WIDTH                  1
#define LCD_WF8B_BPBLCD18(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD18_SHIFT))&LCD_WF8B_BPBLCD18_MASK)
#define LCD_WF8B_BPBLCD45_MASK                   0x2u
#define LCD_WF8B_BPBLCD45_SHIFT                  1
#define LCD_WF8B_BPBLCD45_WIDTH                  1
#define LCD_WF8B_BPBLCD45(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD45_SHIFT))&LCD_WF8B_BPBLCD45_MASK)
#define LCD_WF8B_BPBLCD27_MASK                   0x2u
#define LCD_WF8B_BPBLCD27_SHIFT                  1
#define LCD_WF8B_BPBLCD27_WIDTH                  1
#define LCD_WF8B_BPBLCD27(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD27_SHIFT))&LCD_WF8B_BPBLCD27_MASK)
#define LCD_WF8B_BPBLCD14_MASK                   0x2u
#define LCD_WF8B_BPBLCD14_SHIFT                  1
#define LCD_WF8B_BPBLCD14_WIDTH                  1
#define LCD_WF8B_BPBLCD14(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD14_SHIFT))&LCD_WF8B_BPBLCD14_MASK)
#define LCD_WF8B_BPBLCD51_MASK                   0x2u
#define LCD_WF8B_BPBLCD51_SHIFT                  1
#define LCD_WF8B_BPBLCD51_WIDTH                  1
#define LCD_WF8B_BPBLCD51(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD51_SHIFT))&LCD_WF8B_BPBLCD51_MASK)
#define LCD_WF8B_BPBLCD52_MASK                   0x2u
#define LCD_WF8B_BPBLCD52_SHIFT                  1
#define LCD_WF8B_BPBLCD52_WIDTH                  1
#define LCD_WF8B_BPBLCD52(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD52_SHIFT))&LCD_WF8B_BPBLCD52_MASK)
#define LCD_WF8B_BPBLCD4_MASK                    0x2u
#define LCD_WF8B_BPBLCD4_SHIFT                   1
#define LCD_WF8B_BPBLCD4_WIDTH                   1
#define LCD_WF8B_BPBLCD4(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD4_SHIFT))&LCD_WF8B_BPBLCD4_MASK)
#define LCD_WF8B_BPBLCD35_MASK                   0x2u
#define LCD_WF8B_BPBLCD35_SHIFT                  1
#define LCD_WF8B_BPBLCD35_WIDTH                  1
#define LCD_WF8B_BPBLCD35(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD35_SHIFT))&LCD_WF8B_BPBLCD35_MASK)
#define LCD_WF8B_BPBLCD17_MASK                   0x2u
#define LCD_WF8B_BPBLCD17_SHIFT                  1
#define LCD_WF8B_BPBLCD17_WIDTH                  1
#define LCD_WF8B_BPBLCD17(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD17_SHIFT))&LCD_WF8B_BPBLCD17_MASK)
#define LCD_WF8B_BPBLCD41_MASK                   0x2u
#define LCD_WF8B_BPBLCD41_SHIFT                  1
#define LCD_WF8B_BPBLCD41_WIDTH                  1
#define LCD_WF8B_BPBLCD41(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD41_SHIFT))&LCD_WF8B_BPBLCD41_MASK)
#define LCD_WF8B_BPBLCD11_MASK                   0x2u
#define LCD_WF8B_BPBLCD11_SHIFT                  1
#define LCD_WF8B_BPBLCD11_WIDTH                  1
#define LCD_WF8B_BPBLCD11(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD11_SHIFT))&LCD_WF8B_BPBLCD11_MASK)
#define LCD_WF8B_BPBLCD46_MASK                   0x2u
#define LCD_WF8B_BPBLCD46_SHIFT                  1
#define LCD_WF8B_BPBLCD46_WIDTH                  1
#define LCD_WF8B_BPBLCD46(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD46_SHIFT))&LCD_WF8B_BPBLCD46_MASK)
#define LCD_WF8B_BPBLCD57_MASK                   0x2u
#define LCD_WF8B_BPBLCD57_SHIFT                  1
#define LCD_WF8B_BPBLCD57_WIDTH                  1
#define LCD_WF8B_BPBLCD57(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD57_SHIFT))&LCD_WF8B_BPBLCD57_MASK)
#define LCD_WF8B_BPBLCD42_MASK                   0x2u
#define LCD_WF8B_BPBLCD42_SHIFT                  1
#define LCD_WF8B_BPBLCD42_WIDTH                  1
#define LCD_WF8B_BPBLCD42(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD42_SHIFT))&LCD_WF8B_BPBLCD42_MASK)
#define LCD_WF8B_BPBLCD5_MASK                    0x2u
#define LCD_WF8B_BPBLCD5_SHIFT                   1
#define LCD_WF8B_BPBLCD5_WIDTH                   1
#define LCD_WF8B_BPBLCD5(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD5_SHIFT))&LCD_WF8B_BPBLCD5_MASK)
#define LCD_WF8B_BPBLCD3_MASK                    0x2u
#define LCD_WF8B_BPBLCD3_SHIFT                   1
#define LCD_WF8B_BPBLCD3_WIDTH                   1
#define LCD_WF8B_BPBLCD3(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD3_SHIFT))&LCD_WF8B_BPBLCD3_MASK)
#define LCD_WF8B_BPBLCD16_MASK                   0x2u
#define LCD_WF8B_BPBLCD16_SHIFT                  1
#define LCD_WF8B_BPBLCD16_WIDTH                  1
#define LCD_WF8B_BPBLCD16(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD16_SHIFT))&LCD_WF8B_BPBLCD16_MASK)
#define LCD_WF8B_BPBLCD13_MASK                   0x2u
#define LCD_WF8B_BPBLCD13_SHIFT                  1
#define LCD_WF8B_BPBLCD13_WIDTH                  1
#define LCD_WF8B_BPBLCD13(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPBLCD13_SHIFT))&LCD_WF8B_BPBLCD13_MASK)
#define LCD_WF8B_BPCLCD10_MASK                   0x4u
#define LCD_WF8B_BPCLCD10_SHIFT                  2
#define LCD_WF8B_BPCLCD10_WIDTH                  1
#define LCD_WF8B_BPCLCD10(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD10_SHIFT))&LCD_WF8B_BPCLCD10_MASK)
#define LCD_WF8B_BPCLCD55_MASK                   0x4u
#define LCD_WF8B_BPCLCD55_SHIFT                  2
#define LCD_WF8B_BPCLCD55_WIDTH                  1
#define LCD_WF8B_BPCLCD55(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD55_SHIFT))&LCD_WF8B_BPCLCD55_MASK)
#define LCD_WF8B_BPCLCD2_MASK                    0x4u
#define LCD_WF8B_BPCLCD2_SHIFT                   2
#define LCD_WF8B_BPCLCD2_WIDTH                   1
#define LCD_WF8B_BPCLCD2(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD2_SHIFT))&LCD_WF8B_BPCLCD2_MASK)
#define LCD_WF8B_BPCLCD23_MASK                   0x4u
#define LCD_WF8B_BPCLCD23_SHIFT                  2
#define LCD_WF8B_BPCLCD23_WIDTH                  1
#define LCD_WF8B_BPCLCD23(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD23_SHIFT))&LCD_WF8B_BPCLCD23_MASK)
#define LCD_WF8B_BPCLCD48_MASK                   0x4u
#define LCD_WF8B_BPCLCD48_SHIFT                  2
#define LCD_WF8B_BPCLCD48_WIDTH                  1
#define LCD_WF8B_BPCLCD48(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD48_SHIFT))&LCD_WF8B_BPCLCD48_MASK)
#define LCD_WF8B_BPCLCD24_MASK                   0x4u
#define LCD_WF8B_BPCLCD24_SHIFT                  2
#define LCD_WF8B_BPCLCD24_WIDTH                  1
#define LCD_WF8B_BPCLCD24(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD24_SHIFT))&LCD_WF8B_BPCLCD24_MASK)
#define LCD_WF8B_BPCLCD60_MASK                   0x4u
#define LCD_WF8B_BPCLCD60_SHIFT                  2
#define LCD_WF8B_BPCLCD60_WIDTH                  1
#define LCD_WF8B_BPCLCD60(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD60_SHIFT))&LCD_WF8B_BPCLCD60_MASK)
#define LCD_WF8B_BPCLCD47_MASK                   0x4u
#define LCD_WF8B_BPCLCD47_SHIFT                  2
#define LCD_WF8B_BPCLCD47_WIDTH                  1
#define LCD_WF8B_BPCLCD47(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD47_SHIFT))&LCD_WF8B_BPCLCD47_MASK)
#define LCD_WF8B_BPCLCD22_MASK                   0x4u
#define LCD_WF8B_BPCLCD22_SHIFT                  2
#define LCD_WF8B_BPCLCD22_WIDTH                  1
#define LCD_WF8B_BPCLCD22(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD22_SHIFT))&LCD_WF8B_BPCLCD22_MASK)
#define LCD_WF8B_BPCLCD8_MASK                    0x4u
#define LCD_WF8B_BPCLCD8_SHIFT                   2
#define LCD_WF8B_BPCLCD8_WIDTH                   1
#define LCD_WF8B_BPCLCD8(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD8_SHIFT))&LCD_WF8B_BPCLCD8_MASK)
#define LCD_WF8B_BPCLCD21_MASK                   0x4u
#define LCD_WF8B_BPCLCD21_SHIFT                  2
#define LCD_WF8B_BPCLCD21_WIDTH                  1
#define LCD_WF8B_BPCLCD21(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD21_SHIFT))&LCD_WF8B_BPCLCD21_MASK)
#define LCD_WF8B_BPCLCD49_MASK                   0x4u
#define LCD_WF8B_BPCLCD49_SHIFT                  2
#define LCD_WF8B_BPCLCD49_WIDTH                  1
#define LCD_WF8B_BPCLCD49(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD49_SHIFT))&LCD_WF8B_BPCLCD49_MASK)
#define LCD_WF8B_BPCLCD25_MASK                   0x4u
#define LCD_WF8B_BPCLCD25_SHIFT                  2
#define LCD_WF8B_BPCLCD25_WIDTH                  1
#define LCD_WF8B_BPCLCD25(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD25_SHIFT))&LCD_WF8B_BPCLCD25_MASK)
#define LCD_WF8B_BPCLCD1_MASK                    0x4u
#define LCD_WF8B_BPCLCD1_SHIFT                   2
#define LCD_WF8B_BPCLCD1_WIDTH                   1
#define LCD_WF8B_BPCLCD1(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD1_SHIFT))&LCD_WF8B_BPCLCD1_MASK)
#define LCD_WF8B_BPCLCD20_MASK                   0x4u
#define LCD_WF8B_BPCLCD20_SHIFT                  2
#define LCD_WF8B_BPCLCD20_WIDTH                  1
#define LCD_WF8B_BPCLCD20(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD20_SHIFT))&LCD_WF8B_BPCLCD20_MASK)
#define LCD_WF8B_BPCLCD50_MASK                   0x4u
#define LCD_WF8B_BPCLCD50_SHIFT                  2
#define LCD_WF8B_BPCLCD50_WIDTH                  1
#define LCD_WF8B_BPCLCD50(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD50_SHIFT))&LCD_WF8B_BPCLCD50_MASK)
#define LCD_WF8B_BPCLCD19_MASK                   0x4u
#define LCD_WF8B_BPCLCD19_SHIFT                  2
#define LCD_WF8B_BPCLCD19_WIDTH                  1
#define LCD_WF8B_BPCLCD19(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD19_SHIFT))&LCD_WF8B_BPCLCD19_MASK)
#define LCD_WF8B_BPCLCD26_MASK                   0x4u
#define LCD_WF8B_BPCLCD26_SHIFT                  2
#define LCD_WF8B_BPCLCD26_WIDTH                  1
#define LCD_WF8B_BPCLCD26(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD26_SHIFT))&LCD_WF8B_BPCLCD26_MASK)
#define LCD_WF8B_BPCLCD59_MASK                   0x4u
#define LCD_WF8B_BPCLCD59_SHIFT                  2
#define LCD_WF8B_BPCLCD59_WIDTH                  1
#define LCD_WF8B_BPCLCD59(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD59_SHIFT))&LCD_WF8B_BPCLCD59_MASK)
#define LCD_WF8B_BPCLCD61_MASK                   0x4u
#define LCD_WF8B_BPCLCD61_SHIFT                  2
#define LCD_WF8B_BPCLCD61_WIDTH                  1
#define LCD_WF8B_BPCLCD61(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD61_SHIFT))&LCD_WF8B_BPCLCD61_MASK)
#define LCD_WF8B_BPCLCD46_MASK                   0x4u
#define LCD_WF8B_BPCLCD46_SHIFT                  2
#define LCD_WF8B_BPCLCD46_WIDTH                  1
#define LCD_WF8B_BPCLCD46(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD46_SHIFT))&LCD_WF8B_BPCLCD46_MASK)
#define LCD_WF8B_BPCLCD18_MASK                   0x4u
#define LCD_WF8B_BPCLCD18_SHIFT                  2
#define LCD_WF8B_BPCLCD18_WIDTH                  1
#define LCD_WF8B_BPCLCD18(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD18_SHIFT))&LCD_WF8B_BPCLCD18_MASK)
#define LCD_WF8B_BPCLCD5_MASK                    0x4u
#define LCD_WF8B_BPCLCD5_SHIFT                   2
#define LCD_WF8B_BPCLCD5_WIDTH                   1
#define LCD_WF8B_BPCLCD5(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD5_SHIFT))&LCD_WF8B_BPCLCD5_MASK)
#define LCD_WF8B_BPCLCD63_MASK                   0x4u
#define LCD_WF8B_BPCLCD63_SHIFT                  2
#define LCD_WF8B_BPCLCD63_WIDTH                  1
#define LCD_WF8B_BPCLCD63(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD63_SHIFT))&LCD_WF8B_BPCLCD63_MASK)
#define LCD_WF8B_BPCLCD27_MASK                   0x4u
#define LCD_WF8B_BPCLCD27_SHIFT                  2
#define LCD_WF8B_BPCLCD27_WIDTH                  1
#define LCD_WF8B_BPCLCD27(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD27_SHIFT))&LCD_WF8B_BPCLCD27_MASK)
#define LCD_WF8B_BPCLCD17_MASK                   0x4u
#define LCD_WF8B_BPCLCD17_SHIFT                  2
#define LCD_WF8B_BPCLCD17_WIDTH                  1
#define LCD_WF8B_BPCLCD17(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD17_SHIFT))&LCD_WF8B_BPCLCD17_MASK)
#define LCD_WF8B_BPCLCD51_MASK                   0x4u
#define LCD_WF8B_BPCLCD51_SHIFT                  2
#define LCD_WF8B_BPCLCD51_WIDTH                  1
#define LCD_WF8B_BPCLCD51(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD51_SHIFT))&LCD_WF8B_BPCLCD51_MASK)
#define LCD_WF8B_BPCLCD9_MASK                    0x4u
#define LCD_WF8B_BPCLCD9_SHIFT                   2
#define LCD_WF8B_BPCLCD9_WIDTH                   1
#define LCD_WF8B_BPCLCD9(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD9_SHIFT))&LCD_WF8B_BPCLCD9_MASK)
#define LCD_WF8B_BPCLCD54_MASK                   0x4u
#define LCD_WF8B_BPCLCD54_SHIFT                  2
#define LCD_WF8B_BPCLCD54_WIDTH                  1
#define LCD_WF8B_BPCLCD54(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD54_SHIFT))&LCD_WF8B_BPCLCD54_MASK)
#define LCD_WF8B_BPCLCD15_MASK                   0x4u
#define LCD_WF8B_BPCLCD15_SHIFT                  2
#define LCD_WF8B_BPCLCD15_WIDTH                  1
#define LCD_WF8B_BPCLCD15(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD15_SHIFT))&LCD_WF8B_BPCLCD15_MASK)
#define LCD_WF8B_BPCLCD16_MASK                   0x4u
#define LCD_WF8B_BPCLCD16_SHIFT                  2
#define LCD_WF8B_BPCLCD16_WIDTH                  1
#define LCD_WF8B_BPCLCD16(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD16_SHIFT))&LCD_WF8B_BPCLCD16_MASK)
#define LCD_WF8B_BPCLCD14_MASK                   0x4u
#define LCD_WF8B_BPCLCD14_SHIFT                  2
#define LCD_WF8B_BPCLCD14_WIDTH                  1
#define LCD_WF8B_BPCLCD14(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD14_SHIFT))&LCD_WF8B_BPCLCD14_MASK)
#define LCD_WF8B_BPCLCD32_MASK                   0x4u
#define LCD_WF8B_BPCLCD32_SHIFT                  2
#define LCD_WF8B_BPCLCD32_WIDTH                  1
#define LCD_WF8B_BPCLCD32(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD32_SHIFT))&LCD_WF8B_BPCLCD32_MASK)
#define LCD_WF8B_BPCLCD28_MASK                   0x4u
#define LCD_WF8B_BPCLCD28_SHIFT                  2
#define LCD_WF8B_BPCLCD28_WIDTH                  1
#define LCD_WF8B_BPCLCD28(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD28_SHIFT))&LCD_WF8B_BPCLCD28_MASK)
#define LCD_WF8B_BPCLCD53_MASK                   0x4u
#define LCD_WF8B_BPCLCD53_SHIFT                  2
#define LCD_WF8B_BPCLCD53_WIDTH                  1
#define LCD_WF8B_BPCLCD53(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD53_SHIFT))&LCD_WF8B_BPCLCD53_MASK)
#define LCD_WF8B_BPCLCD33_MASK                   0x4u
#define LCD_WF8B_BPCLCD33_SHIFT                  2
#define LCD_WF8B_BPCLCD33_WIDTH                  1
#define LCD_WF8B_BPCLCD33(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD33_SHIFT))&LCD_WF8B_BPCLCD33_MASK)
#define LCD_WF8B_BPCLCD0_MASK                    0x4u
#define LCD_WF8B_BPCLCD0_SHIFT                   2
#define LCD_WF8B_BPCLCD0_WIDTH                   1
#define LCD_WF8B_BPCLCD0(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD0_SHIFT))&LCD_WF8B_BPCLCD0_MASK)
#define LCD_WF8B_BPCLCD43_MASK                   0x4u
#define LCD_WF8B_BPCLCD43_SHIFT                  2
#define LCD_WF8B_BPCLCD43_WIDTH                  1
#define LCD_WF8B_BPCLCD43(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD43_SHIFT))&LCD_WF8B_BPCLCD43_MASK)
#define LCD_WF8B_BPCLCD7_MASK                    0x4u
#define LCD_WF8B_BPCLCD7_SHIFT                   2
#define LCD_WF8B_BPCLCD7_WIDTH                   1
#define LCD_WF8B_BPCLCD7(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD7_SHIFT))&LCD_WF8B_BPCLCD7_MASK)
#define LCD_WF8B_BPCLCD4_MASK                    0x4u
#define LCD_WF8B_BPCLCD4_SHIFT                   2
#define LCD_WF8B_BPCLCD4_WIDTH                   1
#define LCD_WF8B_BPCLCD4(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD4_SHIFT))&LCD_WF8B_BPCLCD4_MASK)
#define LCD_WF8B_BPCLCD34_MASK                   0x4u
#define LCD_WF8B_BPCLCD34_SHIFT                  2
#define LCD_WF8B_BPCLCD34_WIDTH                  1
#define LCD_WF8B_BPCLCD34(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD34_SHIFT))&LCD_WF8B_BPCLCD34_MASK)
#define LCD_WF8B_BPCLCD29_MASK                   0x4u
#define LCD_WF8B_BPCLCD29_SHIFT                  2
#define LCD_WF8B_BPCLCD29_WIDTH                  1
#define LCD_WF8B_BPCLCD29(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD29_SHIFT))&LCD_WF8B_BPCLCD29_MASK)
#define LCD_WF8B_BPCLCD45_MASK                   0x4u
#define LCD_WF8B_BPCLCD45_SHIFT                  2
#define LCD_WF8B_BPCLCD45_WIDTH                  1
#define LCD_WF8B_BPCLCD45(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD45_SHIFT))&LCD_WF8B_BPCLCD45_MASK)
#define LCD_WF8B_BPCLCD57_MASK                   0x4u
#define LCD_WF8B_BPCLCD57_SHIFT                  2
#define LCD_WF8B_BPCLCD57_WIDTH                  1
#define LCD_WF8B_BPCLCD57(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD57_SHIFT))&LCD_WF8B_BPCLCD57_MASK)
#define LCD_WF8B_BPCLCD42_MASK                   0x4u
#define LCD_WF8B_BPCLCD42_SHIFT                  2
#define LCD_WF8B_BPCLCD42_WIDTH                  1
#define LCD_WF8B_BPCLCD42(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD42_SHIFT))&LCD_WF8B_BPCLCD42_MASK)
#define LCD_WF8B_BPCLCD35_MASK                   0x4u
#define LCD_WF8B_BPCLCD35_SHIFT                  2
#define LCD_WF8B_BPCLCD35_WIDTH                  1
#define LCD_WF8B_BPCLCD35(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD35_SHIFT))&LCD_WF8B_BPCLCD35_MASK)
#define LCD_WF8B_BPCLCD13_MASK                   0x4u
#define LCD_WF8B_BPCLCD13_SHIFT                  2
#define LCD_WF8B_BPCLCD13_WIDTH                  1
#define LCD_WF8B_BPCLCD13(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD13_SHIFT))&LCD_WF8B_BPCLCD13_MASK)
#define LCD_WF8B_BPCLCD36_MASK                   0x4u
#define LCD_WF8B_BPCLCD36_SHIFT                  2
#define LCD_WF8B_BPCLCD36_WIDTH                  1
#define LCD_WF8B_BPCLCD36(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD36_SHIFT))&LCD_WF8B_BPCLCD36_MASK)
#define LCD_WF8B_BPCLCD30_MASK                   0x4u
#define LCD_WF8B_BPCLCD30_SHIFT                  2
#define LCD_WF8B_BPCLCD30_WIDTH                  1
#define LCD_WF8B_BPCLCD30(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD30_SHIFT))&LCD_WF8B_BPCLCD30_MASK)
#define LCD_WF8B_BPCLCD52_MASK                   0x4u
#define LCD_WF8B_BPCLCD52_SHIFT                  2
#define LCD_WF8B_BPCLCD52_WIDTH                  1
#define LCD_WF8B_BPCLCD52(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD52_SHIFT))&LCD_WF8B_BPCLCD52_MASK)
#define LCD_WF8B_BPCLCD58_MASK                   0x4u
#define LCD_WF8B_BPCLCD58_SHIFT                  2
#define LCD_WF8B_BPCLCD58_WIDTH                  1
#define LCD_WF8B_BPCLCD58(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD58_SHIFT))&LCD_WF8B_BPCLCD58_MASK)
#define LCD_WF8B_BPCLCD41_MASK                   0x4u
#define LCD_WF8B_BPCLCD41_SHIFT                  2
#define LCD_WF8B_BPCLCD41_WIDTH                  1
#define LCD_WF8B_BPCLCD41(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD41_SHIFT))&LCD_WF8B_BPCLCD41_MASK)
#define LCD_WF8B_BPCLCD37_MASK                   0x4u
#define LCD_WF8B_BPCLCD37_SHIFT                  2
#define LCD_WF8B_BPCLCD37_WIDTH                  1
#define LCD_WF8B_BPCLCD37(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD37_SHIFT))&LCD_WF8B_BPCLCD37_MASK)
#define LCD_WF8B_BPCLCD3_MASK                    0x4u
#define LCD_WF8B_BPCLCD3_SHIFT                   2
#define LCD_WF8B_BPCLCD3_WIDTH                   1
#define LCD_WF8B_BPCLCD3(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD3_SHIFT))&LCD_WF8B_BPCLCD3_MASK)
#define LCD_WF8B_BPCLCD12_MASK                   0x4u
#define LCD_WF8B_BPCLCD12_SHIFT                  2
#define LCD_WF8B_BPCLCD12_WIDTH                  1
#define LCD_WF8B_BPCLCD12(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD12_SHIFT))&LCD_WF8B_BPCLCD12_MASK)
#define LCD_WF8B_BPCLCD11_MASK                   0x4u
#define LCD_WF8B_BPCLCD11_SHIFT                  2
#define LCD_WF8B_BPCLCD11_WIDTH                  1
#define LCD_WF8B_BPCLCD11(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD11_SHIFT))&LCD_WF8B_BPCLCD11_MASK)
#define LCD_WF8B_BPCLCD38_MASK                   0x4u
#define LCD_WF8B_BPCLCD38_SHIFT                  2
#define LCD_WF8B_BPCLCD38_WIDTH                  1
#define LCD_WF8B_BPCLCD38(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD38_SHIFT))&LCD_WF8B_BPCLCD38_MASK)
#define LCD_WF8B_BPCLCD44_MASK                   0x4u
#define LCD_WF8B_BPCLCD44_SHIFT                  2
#define LCD_WF8B_BPCLCD44_WIDTH                  1
#define LCD_WF8B_BPCLCD44(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD44_SHIFT))&LCD_WF8B_BPCLCD44_MASK)
#define LCD_WF8B_BPCLCD31_MASK                   0x4u
#define LCD_WF8B_BPCLCD31_SHIFT                  2
#define LCD_WF8B_BPCLCD31_WIDTH                  1
#define LCD_WF8B_BPCLCD31(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD31_SHIFT))&LCD_WF8B_BPCLCD31_MASK)
#define LCD_WF8B_BPCLCD40_MASK                   0x4u
#define LCD_WF8B_BPCLCD40_SHIFT                  2
#define LCD_WF8B_BPCLCD40_WIDTH                  1
#define LCD_WF8B_BPCLCD40(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD40_SHIFT))&LCD_WF8B_BPCLCD40_MASK)
#define LCD_WF8B_BPCLCD62_MASK                   0x4u
#define LCD_WF8B_BPCLCD62_SHIFT                  2
#define LCD_WF8B_BPCLCD62_WIDTH                  1
#define LCD_WF8B_BPCLCD62(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD62_SHIFT))&LCD_WF8B_BPCLCD62_MASK)
#define LCD_WF8B_BPCLCD56_MASK                   0x4u
#define LCD_WF8B_BPCLCD56_SHIFT                  2
#define LCD_WF8B_BPCLCD56_WIDTH                  1
#define LCD_WF8B_BPCLCD56(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD56_SHIFT))&LCD_WF8B_BPCLCD56_MASK)
#define LCD_WF8B_BPCLCD39_MASK                   0x4u
#define LCD_WF8B_BPCLCD39_SHIFT                  2
#define LCD_WF8B_BPCLCD39_WIDTH                  1
#define LCD_WF8B_BPCLCD39(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD39_SHIFT))&LCD_WF8B_BPCLCD39_MASK)
#define LCD_WF8B_BPCLCD6_MASK                    0x4u
#define LCD_WF8B_BPCLCD6_SHIFT                   2
#define LCD_WF8B_BPCLCD6_WIDTH                   1
#define LCD_WF8B_BPCLCD6(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPCLCD6_SHIFT))&LCD_WF8B_BPCLCD6_MASK)
#define LCD_WF8B_BPDLCD47_MASK                   0x8u
#define LCD_WF8B_BPDLCD47_SHIFT                  3
#define LCD_WF8B_BPDLCD47_WIDTH                  1
#define LCD_WF8B_BPDLCD47(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD47_SHIFT))&LCD_WF8B_BPDLCD47_MASK)
#define LCD_WF8B_BPDLCD23_MASK                   0x8u
#define LCD_WF8B_BPDLCD23_SHIFT                  3
#define LCD_WF8B_BPDLCD23_WIDTH                  1
#define LCD_WF8B_BPDLCD23(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD23_SHIFT))&LCD_WF8B_BPDLCD23_MASK)
#define LCD_WF8B_BPDLCD48_MASK                   0x8u
#define LCD_WF8B_BPDLCD48_SHIFT                  3
#define LCD_WF8B_BPDLCD48_WIDTH                  1
#define LCD_WF8B_BPDLCD48(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD48_SHIFT))&LCD_WF8B_BPDLCD48_MASK)
#define LCD_WF8B_BPDLCD24_MASK                   0x8u
#define LCD_WF8B_BPDLCD24_SHIFT                  3
#define LCD_WF8B_BPDLCD24_WIDTH                  1
#define LCD_WF8B_BPDLCD24(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD24_SHIFT))&LCD_WF8B_BPDLCD24_MASK)
#define LCD_WF8B_BPDLCD15_MASK                   0x8u
#define LCD_WF8B_BPDLCD15_SHIFT                  3
#define LCD_WF8B_BPDLCD15_WIDTH                  1
#define LCD_WF8B_BPDLCD15(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD15_SHIFT))&LCD_WF8B_BPDLCD15_MASK)
#define LCD_WF8B_BPDLCD22_MASK                   0x8u
#define LCD_WF8B_BPDLCD22_SHIFT                  3
#define LCD_WF8B_BPDLCD22_WIDTH                  1
#define LCD_WF8B_BPDLCD22(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD22_SHIFT))&LCD_WF8B_BPDLCD22_MASK)
#define LCD_WF8B_BPDLCD60_MASK                   0x8u
#define LCD_WF8B_BPDLCD60_SHIFT                  3
#define LCD_WF8B_BPDLCD60_WIDTH                  1
#define LCD_WF8B_BPDLCD60(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD60_SHIFT))&LCD_WF8B_BPDLCD60_MASK)
#define LCD_WF8B_BPDLCD10_MASK                   0x8u
#define LCD_WF8B_BPDLCD10_SHIFT                  3
#define LCD_WF8B_BPDLCD10_WIDTH                  1
#define LCD_WF8B_BPDLCD10(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD10_SHIFT))&LCD_WF8B_BPDLCD10_MASK)
#define LCD_WF8B_BPDLCD21_MASK                   0x8u
#define LCD_WF8B_BPDLCD21_SHIFT                  3
#define LCD_WF8B_BPDLCD21_WIDTH                  1
#define LCD_WF8B_BPDLCD21(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD21_SHIFT))&LCD_WF8B_BPDLCD21_MASK)
#define LCD_WF8B_BPDLCD49_MASK                   0x8u
#define LCD_WF8B_BPDLCD49_SHIFT                  3
#define LCD_WF8B_BPDLCD49_WIDTH                  1
#define LCD_WF8B_BPDLCD49(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD49_SHIFT))&LCD_WF8B_BPDLCD49_MASK)
#define LCD_WF8B_BPDLCD1_MASK                    0x8u
#define LCD_WF8B_BPDLCD1_SHIFT                   3
#define LCD_WF8B_BPDLCD1_WIDTH                   1
#define LCD_WF8B_BPDLCD1(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD1_SHIFT))&LCD_WF8B_BPDLCD1_MASK)
#define LCD_WF8B_BPDLCD25_MASK                   0x8u
#define LCD_WF8B_BPDLCD25_SHIFT                  3
#define LCD_WF8B_BPDLCD25_WIDTH                  1
#define LCD_WF8B_BPDLCD25(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD25_SHIFT))&LCD_WF8B_BPDLCD25_MASK)
#define LCD_WF8B_BPDLCD20_MASK                   0x8u
#define LCD_WF8B_BPDLCD20_SHIFT                  3
#define LCD_WF8B_BPDLCD20_WIDTH                  1
#define LCD_WF8B_BPDLCD20(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD20_SHIFT))&LCD_WF8B_BPDLCD20_MASK)
#define LCD_WF8B_BPDLCD2_MASK                    0x8u
#define LCD_WF8B_BPDLCD2_SHIFT                   3
#define LCD_WF8B_BPDLCD2_WIDTH                   1
#define LCD_WF8B_BPDLCD2(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD2_SHIFT))&LCD_WF8B_BPDLCD2_MASK)
#define LCD_WF8B_BPDLCD55_MASK                   0x8u
#define LCD_WF8B_BPDLCD55_SHIFT                  3
#define LCD_WF8B_BPDLCD55_WIDTH                  1
#define LCD_WF8B_BPDLCD55(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD55_SHIFT))&LCD_WF8B_BPDLCD55_MASK)
#define LCD_WF8B_BPDLCD59_MASK                   0x8u
#define LCD_WF8B_BPDLCD59_SHIFT                  3
#define LCD_WF8B_BPDLCD59_WIDTH                  1
#define LCD_WF8B_BPDLCD59(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD59_SHIFT))&LCD_WF8B_BPDLCD59_MASK)
#define LCD_WF8B_BPDLCD5_MASK                    0x8u
#define LCD_WF8B_BPDLCD5_SHIFT                   3
#define LCD_WF8B_BPDLCD5_WIDTH                   1
#define LCD_WF8B_BPDLCD5(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD5_SHIFT))&LCD_WF8B_BPDLCD5_MASK)
#define LCD_WF8B_BPDLCD19_MASK                   0x8u
#define LCD_WF8B_BPDLCD19_SHIFT                  3
#define LCD_WF8B_BPDLCD19_WIDTH                  1
#define LCD_WF8B_BPDLCD19(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD19_SHIFT))&LCD_WF8B_BPDLCD19_MASK)
#define LCD_WF8B_BPDLCD6_MASK                    0x8u
#define LCD_WF8B_BPDLCD6_SHIFT                   3
#define LCD_WF8B_BPDLCD6_WIDTH                   1
#define LCD_WF8B_BPDLCD6(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD6_SHIFT))&LCD_WF8B_BPDLCD6_MASK)
#define LCD_WF8B_BPDLCD26_MASK                   0x8u
#define LCD_WF8B_BPDLCD26_SHIFT                  3
#define LCD_WF8B_BPDLCD26_WIDTH                  1
#define LCD_WF8B_BPDLCD26(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD26_SHIFT))&LCD_WF8B_BPDLCD26_MASK)
#define LCD_WF8B_BPDLCD0_MASK                    0x8u
#define LCD_WF8B_BPDLCD0_SHIFT                   3
#define LCD_WF8B_BPDLCD0_WIDTH                   1
#define LCD_WF8B_BPDLCD0(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD0_SHIFT))&LCD_WF8B_BPDLCD0_MASK)
#define LCD_WF8B_BPDLCD50_MASK                   0x8u
#define LCD_WF8B_BPDLCD50_SHIFT                  3
#define LCD_WF8B_BPDLCD50_WIDTH                  1
#define LCD_WF8B_BPDLCD50(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD50_SHIFT))&LCD_WF8B_BPDLCD50_MASK)
#define LCD_WF8B_BPDLCD46_MASK                   0x8u
#define LCD_WF8B_BPDLCD46_SHIFT                  3
#define LCD_WF8B_BPDLCD46_WIDTH                  1
#define LCD_WF8B_BPDLCD46(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD46_SHIFT))&LCD_WF8B_BPDLCD46_MASK)
#define LCD_WF8B_BPDLCD18_MASK                   0x8u
#define LCD_WF8B_BPDLCD18_SHIFT                  3
#define LCD_WF8B_BPDLCD18_WIDTH                  1
#define LCD_WF8B_BPDLCD18(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD18_SHIFT))&LCD_WF8B_BPDLCD18_MASK)
#define LCD_WF8B_BPDLCD61_MASK                   0x8u
#define LCD_WF8B_BPDLCD61_SHIFT                  3
#define LCD_WF8B_BPDLCD61_WIDTH                  1
#define LCD_WF8B_BPDLCD61(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD61_SHIFT))&LCD_WF8B_BPDLCD61_MASK)
#define LCD_WF8B_BPDLCD9_MASK                    0x8u
#define LCD_WF8B_BPDLCD9_SHIFT                   3
#define LCD_WF8B_BPDLCD9_WIDTH                   1
#define LCD_WF8B_BPDLCD9(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD9_SHIFT))&LCD_WF8B_BPDLCD9_MASK)
#define LCD_WF8B_BPDLCD17_MASK                   0x8u
#define LCD_WF8B_BPDLCD17_SHIFT                  3
#define LCD_WF8B_BPDLCD17_WIDTH                  1
#define LCD_WF8B_BPDLCD17(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD17_SHIFT))&LCD_WF8B_BPDLCD17_MASK)
#define LCD_WF8B_BPDLCD27_MASK                   0x8u
#define LCD_WF8B_BPDLCD27_SHIFT                  3
#define LCD_WF8B_BPDLCD27_WIDTH                  1
#define LCD_WF8B_BPDLCD27(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD27_SHIFT))&LCD_WF8B_BPDLCD27_MASK)
#define LCD_WF8B_BPDLCD53_MASK                   0x8u
#define LCD_WF8B_BPDLCD53_SHIFT                  3
#define LCD_WF8B_BPDLCD53_WIDTH                  1
#define LCD_WF8B_BPDLCD53(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD53_SHIFT))&LCD_WF8B_BPDLCD53_MASK)
#define LCD_WF8B_BPDLCD51_MASK                   0x8u
#define LCD_WF8B_BPDLCD51_SHIFT                  3
#define LCD_WF8B_BPDLCD51_WIDTH                  1
#define LCD_WF8B_BPDLCD51(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD51_SHIFT))&LCD_WF8B_BPDLCD51_MASK)
#define LCD_WF8B_BPDLCD54_MASK                   0x8u
#define LCD_WF8B_BPDLCD54_SHIFT                  3
#define LCD_WF8B_BPDLCD54_WIDTH                  1
#define LCD_WF8B_BPDLCD54(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD54_SHIFT))&LCD_WF8B_BPDLCD54_MASK)
#define LCD_WF8B_BPDLCD13_MASK                   0x8u
#define LCD_WF8B_BPDLCD13_SHIFT                  3
#define LCD_WF8B_BPDLCD13_WIDTH                  1
#define LCD_WF8B_BPDLCD13(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD13_SHIFT))&LCD_WF8B_BPDLCD13_MASK)
#define LCD_WF8B_BPDLCD16_MASK                   0x8u
#define LCD_WF8B_BPDLCD16_SHIFT                  3
#define LCD_WF8B_BPDLCD16_WIDTH                  1
#define LCD_WF8B_BPDLCD16(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD16_SHIFT))&LCD_WF8B_BPDLCD16_MASK)
#define LCD_WF8B_BPDLCD32_MASK                   0x8u
#define LCD_WF8B_BPDLCD32_SHIFT                  3
#define LCD_WF8B_BPDLCD32_WIDTH                  1
#define LCD_WF8B_BPDLCD32(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD32_SHIFT))&LCD_WF8B_BPDLCD32_MASK)
#define LCD_WF8B_BPDLCD14_MASK                   0x8u
#define LCD_WF8B_BPDLCD14_SHIFT                  3
#define LCD_WF8B_BPDLCD14_WIDTH                  1
#define LCD_WF8B_BPDLCD14(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD14_SHIFT))&LCD_WF8B_BPDLCD14_MASK)
#define LCD_WF8B_BPDLCD28_MASK                   0x8u
#define LCD_WF8B_BPDLCD28_SHIFT                  3
#define LCD_WF8B_BPDLCD28_WIDTH                  1
#define LCD_WF8B_BPDLCD28(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD28_SHIFT))&LCD_WF8B_BPDLCD28_MASK)
#define LCD_WF8B_BPDLCD43_MASK                   0x8u
#define LCD_WF8B_BPDLCD43_SHIFT                  3
#define LCD_WF8B_BPDLCD43_WIDTH                  1
#define LCD_WF8B_BPDLCD43(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD43_SHIFT))&LCD_WF8B_BPDLCD43_MASK)
#define LCD_WF8B_BPDLCD4_MASK                    0x8u
#define LCD_WF8B_BPDLCD4_SHIFT                   3
#define LCD_WF8B_BPDLCD4_WIDTH                   1
#define LCD_WF8B_BPDLCD4(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD4_SHIFT))&LCD_WF8B_BPDLCD4_MASK)
#define LCD_WF8B_BPDLCD45_MASK                   0x8u
#define LCD_WF8B_BPDLCD45_SHIFT                  3
#define LCD_WF8B_BPDLCD45_WIDTH                  1
#define LCD_WF8B_BPDLCD45(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD45_SHIFT))&LCD_WF8B_BPDLCD45_MASK)
#define LCD_WF8B_BPDLCD8_MASK                    0x8u
#define LCD_WF8B_BPDLCD8_SHIFT                   3
#define LCD_WF8B_BPDLCD8_WIDTH                   1
#define LCD_WF8B_BPDLCD8(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD8_SHIFT))&LCD_WF8B_BPDLCD8_MASK)
#define LCD_WF8B_BPDLCD62_MASK                   0x8u
#define LCD_WF8B_BPDLCD62_SHIFT                  3
#define LCD_WF8B_BPDLCD62_WIDTH                  1
#define LCD_WF8B_BPDLCD62(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD62_SHIFT))&LCD_WF8B_BPDLCD62_MASK)
#define LCD_WF8B_BPDLCD33_MASK                   0x8u
#define LCD_WF8B_BPDLCD33_SHIFT                  3
#define LCD_WF8B_BPDLCD33_WIDTH                  1
#define LCD_WF8B_BPDLCD33(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD33_SHIFT))&LCD_WF8B_BPDLCD33_MASK)
#define LCD_WF8B_BPDLCD34_MASK                   0x8u
#define LCD_WF8B_BPDLCD34_SHIFT                  3
#define LCD_WF8B_BPDLCD34_WIDTH                  1
#define LCD_WF8B_BPDLCD34(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD34_SHIFT))&LCD_WF8B_BPDLCD34_MASK)
#define LCD_WF8B_BPDLCD29_MASK                   0x8u
#define LCD_WF8B_BPDLCD29_SHIFT                  3
#define LCD_WF8B_BPDLCD29_WIDTH                  1
#define LCD_WF8B_BPDLCD29(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD29_SHIFT))&LCD_WF8B_BPDLCD29_MASK)
#define LCD_WF8B_BPDLCD58_MASK                   0x8u
#define LCD_WF8B_BPDLCD58_SHIFT                  3
#define LCD_WF8B_BPDLCD58_WIDTH                  1
#define LCD_WF8B_BPDLCD58(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD58_SHIFT))&LCD_WF8B_BPDLCD58_MASK)
#define LCD_WF8B_BPDLCD57_MASK                   0x8u
#define LCD_WF8B_BPDLCD57_SHIFT                  3
#define LCD_WF8B_BPDLCD57_WIDTH                  1
#define LCD_WF8B_BPDLCD57(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD57_SHIFT))&LCD_WF8B_BPDLCD57_MASK)
#define LCD_WF8B_BPDLCD42_MASK                   0x8u
#define LCD_WF8B_BPDLCD42_SHIFT                  3
#define LCD_WF8B_BPDLCD42_WIDTH                  1
#define LCD_WF8B_BPDLCD42(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD42_SHIFT))&LCD_WF8B_BPDLCD42_MASK)
#define LCD_WF8B_BPDLCD35_MASK                   0x8u
#define LCD_WF8B_BPDLCD35_SHIFT                  3
#define LCD_WF8B_BPDLCD35_WIDTH                  1
#define LCD_WF8B_BPDLCD35(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD35_SHIFT))&LCD_WF8B_BPDLCD35_MASK)
#define LCD_WF8B_BPDLCD52_MASK                   0x8u
#define LCD_WF8B_BPDLCD52_SHIFT                  3
#define LCD_WF8B_BPDLCD52_WIDTH                  1
#define LCD_WF8B_BPDLCD52(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD52_SHIFT))&LCD_WF8B_BPDLCD52_MASK)
#define LCD_WF8B_BPDLCD7_MASK                    0x8u
#define LCD_WF8B_BPDLCD7_SHIFT                   3
#define LCD_WF8B_BPDLCD7_WIDTH                   1
#define LCD_WF8B_BPDLCD7(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD7_SHIFT))&LCD_WF8B_BPDLCD7_MASK)
#define LCD_WF8B_BPDLCD36_MASK                   0x8u
#define LCD_WF8B_BPDLCD36_SHIFT                  3
#define LCD_WF8B_BPDLCD36_WIDTH                  1
#define LCD_WF8B_BPDLCD36(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD36_SHIFT))&LCD_WF8B_BPDLCD36_MASK)
#define LCD_WF8B_BPDLCD30_MASK                   0x8u
#define LCD_WF8B_BPDLCD30_SHIFT                  3
#define LCD_WF8B_BPDLCD30_WIDTH                  1
#define LCD_WF8B_BPDLCD30(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD30_SHIFT))&LCD_WF8B_BPDLCD30_MASK)
#define LCD_WF8B_BPDLCD41_MASK                   0x8u
#define LCD_WF8B_BPDLCD41_SHIFT                  3
#define LCD_WF8B_BPDLCD41_WIDTH                  1
#define LCD_WF8B_BPDLCD41(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD41_SHIFT))&LCD_WF8B_BPDLCD41_MASK)
#define LCD_WF8B_BPDLCD37_MASK                   0x8u
#define LCD_WF8B_BPDLCD37_SHIFT                  3
#define LCD_WF8B_BPDLCD37_WIDTH                  1
#define LCD_WF8B_BPDLCD37(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD37_SHIFT))&LCD_WF8B_BPDLCD37_MASK)
#define LCD_WF8B_BPDLCD44_MASK                   0x8u
#define LCD_WF8B_BPDLCD44_SHIFT                  3
#define LCD_WF8B_BPDLCD44_WIDTH                  1
#define LCD_WF8B_BPDLCD44(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD44_SHIFT))&LCD_WF8B_BPDLCD44_MASK)
#define LCD_WF8B_BPDLCD63_MASK                   0x8u
#define LCD_WF8B_BPDLCD63_SHIFT                  3
#define LCD_WF8B_BPDLCD63_WIDTH                  1
#define LCD_WF8B_BPDLCD63(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD63_SHIFT))&LCD_WF8B_BPDLCD63_MASK)
#define LCD_WF8B_BPDLCD38_MASK                   0x8u
#define LCD_WF8B_BPDLCD38_SHIFT                  3
#define LCD_WF8B_BPDLCD38_WIDTH                  1
#define LCD_WF8B_BPDLCD38(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD38_SHIFT))&LCD_WF8B_BPDLCD38_MASK)
#define LCD_WF8B_BPDLCD56_MASK                   0x8u
#define LCD_WF8B_BPDLCD56_SHIFT                  3
#define LCD_WF8B_BPDLCD56_WIDTH                  1
#define LCD_WF8B_BPDLCD56(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD56_SHIFT))&LCD_WF8B_BPDLCD56_MASK)
#define LCD_WF8B_BPDLCD40_MASK                   0x8u
#define LCD_WF8B_BPDLCD40_SHIFT                  3
#define LCD_WF8B_BPDLCD40_WIDTH                  1
#define LCD_WF8B_BPDLCD40(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD40_SHIFT))&LCD_WF8B_BPDLCD40_MASK)
#define LCD_WF8B_BPDLCD31_MASK                   0x8u
#define LCD_WF8B_BPDLCD31_SHIFT                  3
#define LCD_WF8B_BPDLCD31_WIDTH                  1
#define LCD_WF8B_BPDLCD31(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD31_SHIFT))&LCD_WF8B_BPDLCD31_MASK)
#define LCD_WF8B_BPDLCD12_MASK                   0x8u
#define LCD_WF8B_BPDLCD12_SHIFT                  3
#define LCD_WF8B_BPDLCD12_WIDTH                  1
#define LCD_WF8B_BPDLCD12(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD12_SHIFT))&LCD_WF8B_BPDLCD12_MASK)
#define LCD_WF8B_BPDLCD39_MASK                   0x8u
#define LCD_WF8B_BPDLCD39_SHIFT                  3
#define LCD_WF8B_BPDLCD39_WIDTH                  1
#define LCD_WF8B_BPDLCD39(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD39_SHIFT))&LCD_WF8B_BPDLCD39_MASK)
#define LCD_WF8B_BPDLCD3_MASK                    0x8u
#define LCD_WF8B_BPDLCD3_SHIFT                   3
#define LCD_WF8B_BPDLCD3_WIDTH                   1
#define LCD_WF8B_BPDLCD3(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD3_SHIFT))&LCD_WF8B_BPDLCD3_MASK)
#define LCD_WF8B_BPDLCD11_MASK                   0x8u
#define LCD_WF8B_BPDLCD11_SHIFT                  3
#define LCD_WF8B_BPDLCD11_WIDTH                  1
#define LCD_WF8B_BPDLCD11(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPDLCD11_SHIFT))&LCD_WF8B_BPDLCD11_MASK)
#define LCD_WF8B_BPELCD12_MASK                   0x10u
#define LCD_WF8B_BPELCD12_SHIFT                  4
#define LCD_WF8B_BPELCD12_WIDTH                  1
#define LCD_WF8B_BPELCD12(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD12_SHIFT))&LCD_WF8B_BPELCD12_MASK)
#define LCD_WF8B_BPELCD39_MASK                   0x10u
#define LCD_WF8B_BPELCD39_SHIFT                  4
#define LCD_WF8B_BPELCD39_WIDTH                  1
#define LCD_WF8B_BPELCD39(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD39_SHIFT))&LCD_WF8B_BPELCD39_MASK)
#define LCD_WF8B_BPELCD3_MASK                    0x10u
#define LCD_WF8B_BPELCD3_SHIFT                   4
#define LCD_WF8B_BPELCD3_WIDTH                   1
#define LCD_WF8B_BPELCD3(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD3_SHIFT))&LCD_WF8B_BPELCD3_MASK)
#define LCD_WF8B_BPELCD38_MASK                   0x10u
#define LCD_WF8B_BPELCD38_SHIFT                  4
#define LCD_WF8B_BPELCD38_WIDTH                  1
#define LCD_WF8B_BPELCD38(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD38_SHIFT))&LCD_WF8B_BPELCD38_MASK)
#define LCD_WF8B_BPELCD40_MASK                   0x10u
#define LCD_WF8B_BPELCD40_SHIFT                  4
#define LCD_WF8B_BPELCD40_WIDTH                  1
#define LCD_WF8B_BPELCD40(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD40_SHIFT))&LCD_WF8B_BPELCD40_MASK)
#define LCD_WF8B_BPELCD37_MASK                   0x10u
#define LCD_WF8B_BPELCD37_SHIFT                  4
#define LCD_WF8B_BPELCD37_WIDTH                  1
#define LCD_WF8B_BPELCD37(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD37_SHIFT))&LCD_WF8B_BPELCD37_MASK)
#define LCD_WF8B_BPELCD41_MASK                   0x10u
#define LCD_WF8B_BPELCD41_SHIFT                  4
#define LCD_WF8B_BPELCD41_WIDTH                  1
#define LCD_WF8B_BPELCD41(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD41_SHIFT))&LCD_WF8B_BPELCD41_MASK)
#define LCD_WF8B_BPELCD36_MASK                   0x10u
#define LCD_WF8B_BPELCD36_SHIFT                  4
#define LCD_WF8B_BPELCD36_WIDTH                  1
#define LCD_WF8B_BPELCD36(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD36_SHIFT))&LCD_WF8B_BPELCD36_MASK)
#define LCD_WF8B_BPELCD8_MASK                    0x10u
#define LCD_WF8B_BPELCD8_SHIFT                   4
#define LCD_WF8B_BPELCD8_WIDTH                   1
#define LCD_WF8B_BPELCD8(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD8_SHIFT))&LCD_WF8B_BPELCD8_MASK)
#define LCD_WF8B_BPELCD35_MASK                   0x10u
#define LCD_WF8B_BPELCD35_SHIFT                  4
#define LCD_WF8B_BPELCD35_WIDTH                  1
#define LCD_WF8B_BPELCD35(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD35_SHIFT))&LCD_WF8B_BPELCD35_MASK)
#define LCD_WF8B_BPELCD42_MASK                   0x10u
#define LCD_WF8B_BPELCD42_SHIFT                  4
#define LCD_WF8B_BPELCD42_WIDTH                  1
#define LCD_WF8B_BPELCD42(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD42_SHIFT))&LCD_WF8B_BPELCD42_MASK)
#define LCD_WF8B_BPELCD34_MASK                   0x10u
#define LCD_WF8B_BPELCD34_SHIFT                  4
#define LCD_WF8B_BPELCD34_WIDTH                  1
#define LCD_WF8B_BPELCD34(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD34_SHIFT))&LCD_WF8B_BPELCD34_MASK)
#define LCD_WF8B_BPELCD33_MASK                   0x10u
#define LCD_WF8B_BPELCD33_SHIFT                  4
#define LCD_WF8B_BPELCD33_WIDTH                  1
#define LCD_WF8B_BPELCD33(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD33_SHIFT))&LCD_WF8B_BPELCD33_MASK)
#define LCD_WF8B_BPELCD11_MASK                   0x10u
#define LCD_WF8B_BPELCD11_SHIFT                  4
#define LCD_WF8B_BPELCD11_WIDTH                  1
#define LCD_WF8B_BPELCD11(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD11_SHIFT))&LCD_WF8B_BPELCD11_MASK)
#define LCD_WF8B_BPELCD43_MASK                   0x10u
#define LCD_WF8B_BPELCD43_SHIFT                  4
#define LCD_WF8B_BPELCD43_WIDTH                  1
#define LCD_WF8B_BPELCD43(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD43_SHIFT))&LCD_WF8B_BPELCD43_MASK)
#define LCD_WF8B_BPELCD32_MASK                   0x10u
#define LCD_WF8B_BPELCD32_SHIFT                  4
#define LCD_WF8B_BPELCD32_WIDTH                  1
#define LCD_WF8B_BPELCD32(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD32_SHIFT))&LCD_WF8B_BPELCD32_MASK)
#define LCD_WF8B_BPELCD31_MASK                   0x10u
#define LCD_WF8B_BPELCD31_SHIFT                  4
#define LCD_WF8B_BPELCD31_WIDTH                  1
#define LCD_WF8B_BPELCD31(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD31_SHIFT))&LCD_WF8B_BPELCD31_MASK)
#define LCD_WF8B_BPELCD44_MASK                   0x10u
#define LCD_WF8B_BPELCD44_SHIFT                  4
#define LCD_WF8B_BPELCD44_WIDTH                  1
#define LCD_WF8B_BPELCD44(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD44_SHIFT))&LCD_WF8B_BPELCD44_MASK)
#define LCD_WF8B_BPELCD30_MASK                   0x10u
#define LCD_WF8B_BPELCD30_SHIFT                  4
#define LCD_WF8B_BPELCD30_WIDTH                  1
#define LCD_WF8B_BPELCD30(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD30_SHIFT))&LCD_WF8B_BPELCD30_MASK)
#define LCD_WF8B_BPELCD29_MASK                   0x10u
#define LCD_WF8B_BPELCD29_SHIFT                  4
#define LCD_WF8B_BPELCD29_WIDTH                  1
#define LCD_WF8B_BPELCD29(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD29_SHIFT))&LCD_WF8B_BPELCD29_MASK)
#define LCD_WF8B_BPELCD7_MASK                    0x10u
#define LCD_WF8B_BPELCD7_SHIFT                   4
#define LCD_WF8B_BPELCD7_WIDTH                   1
#define LCD_WF8B_BPELCD7(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD7_SHIFT))&LCD_WF8B_BPELCD7_MASK)
#define LCD_WF8B_BPELCD45_MASK                   0x10u
#define LCD_WF8B_BPELCD45_SHIFT                  4
#define LCD_WF8B_BPELCD45_WIDTH                  1
#define LCD_WF8B_BPELCD45(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD45_SHIFT))&LCD_WF8B_BPELCD45_MASK)
#define LCD_WF8B_BPELCD28_MASK                   0x10u
#define LCD_WF8B_BPELCD28_SHIFT                  4
#define LCD_WF8B_BPELCD28_WIDTH                  1
#define LCD_WF8B_BPELCD28(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD28_SHIFT))&LCD_WF8B_BPELCD28_MASK)
#define LCD_WF8B_BPELCD2_MASK                    0x10u
#define LCD_WF8B_BPELCD2_SHIFT                   4
#define LCD_WF8B_BPELCD2_WIDTH                   1
#define LCD_WF8B_BPELCD2(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD2_SHIFT))&LCD_WF8B_BPELCD2_MASK)
#define LCD_WF8B_BPELCD27_MASK                   0x10u
#define LCD_WF8B_BPELCD27_SHIFT                  4
#define LCD_WF8B_BPELCD27_WIDTH                  1
#define LCD_WF8B_BPELCD27(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD27_SHIFT))&LCD_WF8B_BPELCD27_MASK)
#define LCD_WF8B_BPELCD46_MASK                   0x10u
#define LCD_WF8B_BPELCD46_SHIFT                  4
#define LCD_WF8B_BPELCD46_WIDTH                  1
#define LCD_WF8B_BPELCD46(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD46_SHIFT))&LCD_WF8B_BPELCD46_MASK)
#define LCD_WF8B_BPELCD26_MASK                   0x10u
#define LCD_WF8B_BPELCD26_SHIFT                  4
#define LCD_WF8B_BPELCD26_WIDTH                  1
#define LCD_WF8B_BPELCD26(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD26_SHIFT))&LCD_WF8B_BPELCD26_MASK)
#define LCD_WF8B_BPELCD10_MASK                   0x10u
#define LCD_WF8B_BPELCD10_SHIFT                  4
#define LCD_WF8B_BPELCD10_WIDTH                  1
#define LCD_WF8B_BPELCD10(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD10_SHIFT))&LCD_WF8B_BPELCD10_MASK)
#define LCD_WF8B_BPELCD13_MASK                   0x10u
#define LCD_WF8B_BPELCD13_SHIFT                  4
#define LCD_WF8B_BPELCD13_WIDTH                  1
#define LCD_WF8B_BPELCD13(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD13_SHIFT))&LCD_WF8B_BPELCD13_MASK)
#define LCD_WF8B_BPELCD25_MASK                   0x10u
#define LCD_WF8B_BPELCD25_SHIFT                  4
#define LCD_WF8B_BPELCD25_WIDTH                  1
#define LCD_WF8B_BPELCD25(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD25_SHIFT))&LCD_WF8B_BPELCD25_MASK)
#define LCD_WF8B_BPELCD5_MASK                    0x10u
#define LCD_WF8B_BPELCD5_SHIFT                   4
#define LCD_WF8B_BPELCD5_WIDTH                   1
#define LCD_WF8B_BPELCD5(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD5_SHIFT))&LCD_WF8B_BPELCD5_MASK)
#define LCD_WF8B_BPELCD24_MASK                   0x10u
#define LCD_WF8B_BPELCD24_SHIFT                  4
#define LCD_WF8B_BPELCD24_WIDTH                  1
#define LCD_WF8B_BPELCD24(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD24_SHIFT))&LCD_WF8B_BPELCD24_MASK)
#define LCD_WF8B_BPELCD47_MASK                   0x10u
#define LCD_WF8B_BPELCD47_SHIFT                  4
#define LCD_WF8B_BPELCD47_WIDTH                  1
#define LCD_WF8B_BPELCD47(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD47_SHIFT))&LCD_WF8B_BPELCD47_MASK)
#define LCD_WF8B_BPELCD23_MASK                   0x10u
#define LCD_WF8B_BPELCD23_SHIFT                  4
#define LCD_WF8B_BPELCD23_WIDTH                  1
#define LCD_WF8B_BPELCD23(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD23_SHIFT))&LCD_WF8B_BPELCD23_MASK)
#define LCD_WF8B_BPELCD22_MASK                   0x10u
#define LCD_WF8B_BPELCD22_SHIFT                  4
#define LCD_WF8B_BPELCD22_WIDTH                  1
#define LCD_WF8B_BPELCD22(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD22_SHIFT))&LCD_WF8B_BPELCD22_MASK)
#define LCD_WF8B_BPELCD48_MASK                   0x10u
#define LCD_WF8B_BPELCD48_SHIFT                  4
#define LCD_WF8B_BPELCD48_WIDTH                  1
#define LCD_WF8B_BPELCD48(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD48_SHIFT))&LCD_WF8B_BPELCD48_MASK)
#define LCD_WF8B_BPELCD21_MASK                   0x10u
#define LCD_WF8B_BPELCD21_SHIFT                  4
#define LCD_WF8B_BPELCD21_WIDTH                  1
#define LCD_WF8B_BPELCD21(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD21_SHIFT))&LCD_WF8B_BPELCD21_MASK)
#define LCD_WF8B_BPELCD49_MASK                   0x10u
#define LCD_WF8B_BPELCD49_SHIFT                  4
#define LCD_WF8B_BPELCD49_WIDTH                  1
#define LCD_WF8B_BPELCD49(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD49_SHIFT))&LCD_WF8B_BPELCD49_MASK)
#define LCD_WF8B_BPELCD20_MASK                   0x10u
#define LCD_WF8B_BPELCD20_SHIFT                  4
#define LCD_WF8B_BPELCD20_WIDTH                  1
#define LCD_WF8B_BPELCD20(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD20_SHIFT))&LCD_WF8B_BPELCD20_MASK)
#define LCD_WF8B_BPELCD19_MASK                   0x10u
#define LCD_WF8B_BPELCD19_SHIFT                  4
#define LCD_WF8B_BPELCD19_WIDTH                  1
#define LCD_WF8B_BPELCD19(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD19_SHIFT))&LCD_WF8B_BPELCD19_MASK)
#define LCD_WF8B_BPELCD9_MASK                    0x10u
#define LCD_WF8B_BPELCD9_SHIFT                   4
#define LCD_WF8B_BPELCD9_WIDTH                   1
#define LCD_WF8B_BPELCD9(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD9_SHIFT))&LCD_WF8B_BPELCD9_MASK)
#define LCD_WF8B_BPELCD50_MASK                   0x10u
#define LCD_WF8B_BPELCD50_SHIFT                  4
#define LCD_WF8B_BPELCD50_WIDTH                  1
#define LCD_WF8B_BPELCD50(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD50_SHIFT))&LCD_WF8B_BPELCD50_MASK)
#define LCD_WF8B_BPELCD18_MASK                   0x10u
#define LCD_WF8B_BPELCD18_SHIFT                  4
#define LCD_WF8B_BPELCD18_WIDTH                  1
#define LCD_WF8B_BPELCD18(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD18_SHIFT))&LCD_WF8B_BPELCD18_MASK)
#define LCD_WF8B_BPELCD6_MASK                    0x10u
#define LCD_WF8B_BPELCD6_SHIFT                   4
#define LCD_WF8B_BPELCD6_WIDTH                   1
#define LCD_WF8B_BPELCD6(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD6_SHIFT))&LCD_WF8B_BPELCD6_MASK)
#define LCD_WF8B_BPELCD17_MASK                   0x10u
#define LCD_WF8B_BPELCD17_SHIFT                  4
#define LCD_WF8B_BPELCD17_WIDTH                  1
#define LCD_WF8B_BPELCD17(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD17_SHIFT))&LCD_WF8B_BPELCD17_MASK)
#define LCD_WF8B_BPELCD51_MASK                   0x10u
#define LCD_WF8B_BPELCD51_SHIFT                  4
#define LCD_WF8B_BPELCD51_WIDTH                  1
#define LCD_WF8B_BPELCD51(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD51_SHIFT))&LCD_WF8B_BPELCD51_MASK)
#define LCD_WF8B_BPELCD16_MASK                   0x10u
#define LCD_WF8B_BPELCD16_SHIFT                  4
#define LCD_WF8B_BPELCD16_WIDTH                  1
#define LCD_WF8B_BPELCD16(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD16_SHIFT))&LCD_WF8B_BPELCD16_MASK)
#define LCD_WF8B_BPELCD56_MASK                   0x10u
#define LCD_WF8B_BPELCD56_SHIFT                  4
#define LCD_WF8B_BPELCD56_WIDTH                  1
#define LCD_WF8B_BPELCD56(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD56_SHIFT))&LCD_WF8B_BPELCD56_MASK)
#define LCD_WF8B_BPELCD57_MASK                   0x10u
#define LCD_WF8B_BPELCD57_SHIFT                  4
#define LCD_WF8B_BPELCD57_WIDTH                  1
#define LCD_WF8B_BPELCD57(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD57_SHIFT))&LCD_WF8B_BPELCD57_MASK)
#define LCD_WF8B_BPELCD52_MASK                   0x10u
#define LCD_WF8B_BPELCD52_SHIFT                  4
#define LCD_WF8B_BPELCD52_WIDTH                  1
#define LCD_WF8B_BPELCD52(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD52_SHIFT))&LCD_WF8B_BPELCD52_MASK)
#define LCD_WF8B_BPELCD1_MASK                    0x10u
#define LCD_WF8B_BPELCD1_SHIFT                   4
#define LCD_WF8B_BPELCD1_WIDTH                   1
#define LCD_WF8B_BPELCD1(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD1_SHIFT))&LCD_WF8B_BPELCD1_MASK)
#define LCD_WF8B_BPELCD58_MASK                   0x10u
#define LCD_WF8B_BPELCD58_SHIFT                  4
#define LCD_WF8B_BPELCD58_WIDTH                  1
#define LCD_WF8B_BPELCD58(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD58_SHIFT))&LCD_WF8B_BPELCD58_MASK)
#define LCD_WF8B_BPELCD59_MASK                   0x10u
#define LCD_WF8B_BPELCD59_SHIFT                  4
#define LCD_WF8B_BPELCD59_WIDTH                  1
#define LCD_WF8B_BPELCD59(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD59_SHIFT))&LCD_WF8B_BPELCD59_MASK)
#define LCD_WF8B_BPELCD53_MASK                   0x10u
#define LCD_WF8B_BPELCD53_SHIFT                  4
#define LCD_WF8B_BPELCD53_WIDTH                  1
#define LCD_WF8B_BPELCD53(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD53_SHIFT))&LCD_WF8B_BPELCD53_MASK)
#define LCD_WF8B_BPELCD14_MASK                   0x10u
#define LCD_WF8B_BPELCD14_SHIFT                  4
#define LCD_WF8B_BPELCD14_WIDTH                  1
#define LCD_WF8B_BPELCD14(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD14_SHIFT))&LCD_WF8B_BPELCD14_MASK)
#define LCD_WF8B_BPELCD0_MASK                    0x10u
#define LCD_WF8B_BPELCD0_SHIFT                   4
#define LCD_WF8B_BPELCD0_WIDTH                   1
#define LCD_WF8B_BPELCD0(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD0_SHIFT))&LCD_WF8B_BPELCD0_MASK)
#define LCD_WF8B_BPELCD60_MASK                   0x10u
#define LCD_WF8B_BPELCD60_SHIFT                  4
#define LCD_WF8B_BPELCD60_WIDTH                  1
#define LCD_WF8B_BPELCD60(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD60_SHIFT))&LCD_WF8B_BPELCD60_MASK)
#define LCD_WF8B_BPELCD15_MASK                   0x10u
#define LCD_WF8B_BPELCD15_SHIFT                  4
#define LCD_WF8B_BPELCD15_WIDTH                  1
#define LCD_WF8B_BPELCD15(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD15_SHIFT))&LCD_WF8B_BPELCD15_MASK)
#define LCD_WF8B_BPELCD61_MASK                   0x10u
#define LCD_WF8B_BPELCD61_SHIFT                  4
#define LCD_WF8B_BPELCD61_WIDTH                  1
#define LCD_WF8B_BPELCD61(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD61_SHIFT))&LCD_WF8B_BPELCD61_MASK)
#define LCD_WF8B_BPELCD54_MASK                   0x10u
#define LCD_WF8B_BPELCD54_SHIFT                  4
#define LCD_WF8B_BPELCD54_WIDTH                  1
#define LCD_WF8B_BPELCD54(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD54_SHIFT))&LCD_WF8B_BPELCD54_MASK)
#define LCD_WF8B_BPELCD62_MASK                   0x10u
#define LCD_WF8B_BPELCD62_SHIFT                  4
#define LCD_WF8B_BPELCD62_WIDTH                  1
#define LCD_WF8B_BPELCD62(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD62_SHIFT))&LCD_WF8B_BPELCD62_MASK)
#define LCD_WF8B_BPELCD63_MASK                   0x10u
#define LCD_WF8B_BPELCD63_SHIFT                  4
#define LCD_WF8B_BPELCD63_WIDTH                  1
#define LCD_WF8B_BPELCD63(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD63_SHIFT))&LCD_WF8B_BPELCD63_MASK)
#define LCD_WF8B_BPELCD55_MASK                   0x10u
#define LCD_WF8B_BPELCD55_SHIFT                  4
#define LCD_WF8B_BPELCD55_WIDTH                  1
#define LCD_WF8B_BPELCD55(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD55_SHIFT))&LCD_WF8B_BPELCD55_MASK)
#define LCD_WF8B_BPELCD4_MASK                    0x10u
#define LCD_WF8B_BPELCD4_SHIFT                   4
#define LCD_WF8B_BPELCD4_WIDTH                   1
#define LCD_WF8B_BPELCD4(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPELCD4_SHIFT))&LCD_WF8B_BPELCD4_MASK)
#define LCD_WF8B_BPFLCD13_MASK                   0x20u
#define LCD_WF8B_BPFLCD13_SHIFT                  5
#define LCD_WF8B_BPFLCD13_WIDTH                  1
#define LCD_WF8B_BPFLCD13(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD13_SHIFT))&LCD_WF8B_BPFLCD13_MASK)
#define LCD_WF8B_BPFLCD39_MASK                   0x20u
#define LCD_WF8B_BPFLCD39_SHIFT                  5
#define LCD_WF8B_BPFLCD39_WIDTH                  1
#define LCD_WF8B_BPFLCD39(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD39_SHIFT))&LCD_WF8B_BPFLCD39_MASK)
#define LCD_WF8B_BPFLCD55_MASK                   0x20u
#define LCD_WF8B_BPFLCD55_SHIFT                  5
#define LCD_WF8B_BPFLCD55_WIDTH                  1
#define LCD_WF8B_BPFLCD55(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD55_SHIFT))&LCD_WF8B_BPFLCD55_MASK)
#define LCD_WF8B_BPFLCD47_MASK                   0x20u
#define LCD_WF8B_BPFLCD47_SHIFT                  5
#define LCD_WF8B_BPFLCD47_WIDTH                  1
#define LCD_WF8B_BPFLCD47(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD47_SHIFT))&LCD_WF8B_BPFLCD47_MASK)
#define LCD_WF8B_BPFLCD63_MASK                   0x20u
#define LCD_WF8B_BPFLCD63_SHIFT                  5
#define LCD_WF8B_BPFLCD63_WIDTH                  1
#define LCD_WF8B_BPFLCD63(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD63_SHIFT))&LCD_WF8B_BPFLCD63_MASK)
#define LCD_WF8B_BPFLCD43_MASK                   0x20u
#define LCD_WF8B_BPFLCD43_SHIFT                  5
#define LCD_WF8B_BPFLCD43_WIDTH                  1
#define LCD_WF8B_BPFLCD43(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD43_SHIFT))&LCD_WF8B_BPFLCD43_MASK)
#define LCD_WF8B_BPFLCD5_MASK                    0x20u
#define LCD_WF8B_BPFLCD5_SHIFT                   5
#define LCD_WF8B_BPFLCD5_WIDTH                   1
#define LCD_WF8B_BPFLCD5(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD5_SHIFT))&LCD_WF8B_BPFLCD5_MASK)
#define LCD_WF8B_BPFLCD62_MASK                   0x20u
#define LCD_WF8B_BPFLCD62_SHIFT                  5
#define LCD_WF8B_BPFLCD62_WIDTH                  1
#define LCD_WF8B_BPFLCD62(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD62_SHIFT))&LCD_WF8B_BPFLCD62_MASK)
#define LCD_WF8B_BPFLCD14_MASK                   0x20u
#define LCD_WF8B_BPFLCD14_SHIFT                  5
#define LCD_WF8B_BPFLCD14_WIDTH                  1
#define LCD_WF8B_BPFLCD14(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD14_SHIFT))&LCD_WF8B_BPFLCD14_MASK)
#define LCD_WF8B_BPFLCD24_MASK                   0x20u
#define LCD_WF8B_BPFLCD24_SHIFT                  5
#define LCD_WF8B_BPFLCD24_WIDTH                  1
#define LCD_WF8B_BPFLCD24(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD24_SHIFT))&LCD_WF8B_BPFLCD24_MASK)
#define LCD_WF8B_BPFLCD54_MASK                   0x20u
#define LCD_WF8B_BPFLCD54_SHIFT                  5
#define LCD_WF8B_BPFLCD54_WIDTH                  1
#define LCD_WF8B_BPFLCD54(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD54_SHIFT))&LCD_WF8B_BPFLCD54_MASK)
#define LCD_WF8B_BPFLCD15_MASK                   0x20u
#define LCD_WF8B_BPFLCD15_SHIFT                  5
#define LCD_WF8B_BPFLCD15_WIDTH                  1
#define LCD_WF8B_BPFLCD15(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD15_SHIFT))&LCD_WF8B_BPFLCD15_MASK)
#define LCD_WF8B_BPFLCD32_MASK                   0x20u
#define LCD_WF8B_BPFLCD32_SHIFT                  5
#define LCD_WF8B_BPFLCD32_WIDTH                  1
#define LCD_WF8B_BPFLCD32(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD32_SHIFT))&LCD_WF8B_BPFLCD32_MASK)
#define LCD_WF8B_BPFLCD61_MASK                   0x20u
#define LCD_WF8B_BPFLCD61_SHIFT                  5
#define LCD_WF8B_BPFLCD61_WIDTH                  1
#define LCD_WF8B_BPFLCD61(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD61_SHIFT))&LCD_WF8B_BPFLCD61_MASK)
#define LCD_WF8B_BPFLCD25_MASK                   0x20u
#define LCD_WF8B_BPFLCD25_SHIFT                  5
#define LCD_WF8B_BPFLCD25_WIDTH                  1
#define LCD_WF8B_BPFLCD25(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD25_SHIFT))&LCD_WF8B_BPFLCD25_MASK)
#define LCD_WF8B_BPFLCD60_MASK                   0x20u
#define LCD_WF8B_BPFLCD60_SHIFT                  5
#define LCD_WF8B_BPFLCD60_WIDTH                  1
#define LCD_WF8B_BPFLCD60(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD60_SHIFT))&LCD_WF8B_BPFLCD60_MASK)
#define LCD_WF8B_BPFLCD41_MASK                   0x20u
#define LCD_WF8B_BPFLCD41_SHIFT                  5
#define LCD_WF8B_BPFLCD41_WIDTH                  1
#define LCD_WF8B_BPFLCD41(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD41_SHIFT))&LCD_WF8B_BPFLCD41_MASK)
#define LCD_WF8B_BPFLCD33_MASK                   0x20u
#define LCD_WF8B_BPFLCD33_SHIFT                  5
#define LCD_WF8B_BPFLCD33_WIDTH                  1
#define LCD_WF8B_BPFLCD33(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD33_SHIFT))&LCD_WF8B_BPFLCD33_MASK)
#define LCD_WF8B_BPFLCD53_MASK                   0x20u
#define LCD_WF8B_BPFLCD53_SHIFT                  5
#define LCD_WF8B_BPFLCD53_WIDTH                  1
#define LCD_WF8B_BPFLCD53(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD53_SHIFT))&LCD_WF8B_BPFLCD53_MASK)
#define LCD_WF8B_BPFLCD59_MASK                   0x20u
#define LCD_WF8B_BPFLCD59_SHIFT                  5
#define LCD_WF8B_BPFLCD59_WIDTH                  1
#define LCD_WF8B_BPFLCD59(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD59_SHIFT))&LCD_WF8B_BPFLCD59_MASK)
#define LCD_WF8B_BPFLCD0_MASK                    0x20u
#define LCD_WF8B_BPFLCD0_SHIFT                   5
#define LCD_WF8B_BPFLCD0_WIDTH                   1
#define LCD_WF8B_BPFLCD0(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD0_SHIFT))&LCD_WF8B_BPFLCD0_MASK)
#define LCD_WF8B_BPFLCD46_MASK                   0x20u
#define LCD_WF8B_BPFLCD46_SHIFT                  5
#define LCD_WF8B_BPFLCD46_WIDTH                  1
#define LCD_WF8B_BPFLCD46(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD46_SHIFT))&LCD_WF8B_BPFLCD46_MASK)
#define LCD_WF8B_BPFLCD58_MASK                   0x20u
#define LCD_WF8B_BPFLCD58_SHIFT                  5
#define LCD_WF8B_BPFLCD58_WIDTH                  1
#define LCD_WF8B_BPFLCD58(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD58_SHIFT))&LCD_WF8B_BPFLCD58_MASK)
#define LCD_WF8B_BPFLCD26_MASK                   0x20u
#define LCD_WF8B_BPFLCD26_SHIFT                  5
#define LCD_WF8B_BPFLCD26_WIDTH                  1
#define LCD_WF8B_BPFLCD26(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD26_SHIFT))&LCD_WF8B_BPFLCD26_MASK)
#define LCD_WF8B_BPFLCD36_MASK                   0x20u
#define LCD_WF8B_BPFLCD36_SHIFT                  5
#define LCD_WF8B_BPFLCD36_WIDTH                  1
#define LCD_WF8B_BPFLCD36(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD36_SHIFT))&LCD_WF8B_BPFLCD36_MASK)
#define LCD_WF8B_BPFLCD10_MASK                   0x20u
#define LCD_WF8B_BPFLCD10_SHIFT                  5
#define LCD_WF8B_BPFLCD10_WIDTH                  1
#define LCD_WF8B_BPFLCD10(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD10_SHIFT))&LCD_WF8B_BPFLCD10_MASK)
#define LCD_WF8B_BPFLCD52_MASK                   0x20u
#define LCD_WF8B_BPFLCD52_SHIFT                  5
#define LCD_WF8B_BPFLCD52_WIDTH                  1
#define LCD_WF8B_BPFLCD52(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD52_SHIFT))&LCD_WF8B_BPFLCD52_MASK)
#define LCD_WF8B_BPFLCD57_MASK                   0x20u
#define LCD_WF8B_BPFLCD57_SHIFT                  5
#define LCD_WF8B_BPFLCD57_WIDTH                  1
#define LCD_WF8B_BPFLCD57(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD57_SHIFT))&LCD_WF8B_BPFLCD57_MASK)
#define LCD_WF8B_BPFLCD27_MASK                   0x20u
#define LCD_WF8B_BPFLCD27_SHIFT                  5
#define LCD_WF8B_BPFLCD27_WIDTH                  1
#define LCD_WF8B_BPFLCD27(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD27_SHIFT))&LCD_WF8B_BPFLCD27_MASK)
#define LCD_WF8B_BPFLCD11_MASK                   0x20u
#define LCD_WF8B_BPFLCD11_SHIFT                  5
#define LCD_WF8B_BPFLCD11_WIDTH                  1
#define LCD_WF8B_BPFLCD11(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD11_SHIFT))&LCD_WF8B_BPFLCD11_MASK)
#define LCD_WF8B_BPFLCD56_MASK                   0x20u
#define LCD_WF8B_BPFLCD56_SHIFT                  5
#define LCD_WF8B_BPFLCD56_WIDTH                  1
#define LCD_WF8B_BPFLCD56(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD56_SHIFT))&LCD_WF8B_BPFLCD56_MASK)
#define LCD_WF8B_BPFLCD1_MASK                    0x20u
#define LCD_WF8B_BPFLCD1_SHIFT                   5
#define LCD_WF8B_BPFLCD1_WIDTH                   1
#define LCD_WF8B_BPFLCD1(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD1_SHIFT))&LCD_WF8B_BPFLCD1_MASK)
#define LCD_WF8B_BPFLCD8_MASK                    0x20u
#define LCD_WF8B_BPFLCD8_SHIFT                   5
#define LCD_WF8B_BPFLCD8_WIDTH                   1
#define LCD_WF8B_BPFLCD8(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD8_SHIFT))&LCD_WF8B_BPFLCD8_MASK)
#define LCD_WF8B_BPFLCD40_MASK                   0x20u
#define LCD_WF8B_BPFLCD40_SHIFT                  5
#define LCD_WF8B_BPFLCD40_WIDTH                  1
#define LCD_WF8B_BPFLCD40(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD40_SHIFT))&LCD_WF8B_BPFLCD40_MASK)
#define LCD_WF8B_BPFLCD51_MASK                   0x20u
#define LCD_WF8B_BPFLCD51_SHIFT                  5
#define LCD_WF8B_BPFLCD51_WIDTH                  1
#define LCD_WF8B_BPFLCD51(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD51_SHIFT))&LCD_WF8B_BPFLCD51_MASK)
#define LCD_WF8B_BPFLCD16_MASK                   0x20u
#define LCD_WF8B_BPFLCD16_SHIFT                  5
#define LCD_WF8B_BPFLCD16_WIDTH                  1
#define LCD_WF8B_BPFLCD16(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD16_SHIFT))&LCD_WF8B_BPFLCD16_MASK)
#define LCD_WF8B_BPFLCD45_MASK                   0x20u
#define LCD_WF8B_BPFLCD45_SHIFT                  5
#define LCD_WF8B_BPFLCD45_WIDTH                  1
#define LCD_WF8B_BPFLCD45(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD45_SHIFT))&LCD_WF8B_BPFLCD45_MASK)
#define LCD_WF8B_BPFLCD6_MASK                    0x20u
#define LCD_WF8B_BPFLCD6_SHIFT                   5
#define LCD_WF8B_BPFLCD6_WIDTH                   1
#define LCD_WF8B_BPFLCD6(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD6_SHIFT))&LCD_WF8B_BPFLCD6_MASK)
#define LCD_WF8B_BPFLCD17_MASK                   0x20u
#define LCD_WF8B_BPFLCD17_SHIFT                  5
#define LCD_WF8B_BPFLCD17_WIDTH                  1
#define LCD_WF8B_BPFLCD17(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD17_SHIFT))&LCD_WF8B_BPFLCD17_MASK)
#define LCD_WF8B_BPFLCD28_MASK                   0x20u
#define LCD_WF8B_BPFLCD28_SHIFT                  5
#define LCD_WF8B_BPFLCD28_WIDTH                  1
#define LCD_WF8B_BPFLCD28(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD28_SHIFT))&LCD_WF8B_BPFLCD28_MASK)
#define LCD_WF8B_BPFLCD42_MASK                   0x20u
#define LCD_WF8B_BPFLCD42_SHIFT                  5
#define LCD_WF8B_BPFLCD42_WIDTH                  1
#define LCD_WF8B_BPFLCD42(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD42_SHIFT))&LCD_WF8B_BPFLCD42_MASK)
#define LCD_WF8B_BPFLCD29_MASK                   0x20u
#define LCD_WF8B_BPFLCD29_SHIFT                  5
#define LCD_WF8B_BPFLCD29_WIDTH                  1
#define LCD_WF8B_BPFLCD29(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD29_SHIFT))&LCD_WF8B_BPFLCD29_MASK)
#define LCD_WF8B_BPFLCD50_MASK                   0x20u
#define LCD_WF8B_BPFLCD50_SHIFT                  5
#define LCD_WF8B_BPFLCD50_WIDTH                  1
#define LCD_WF8B_BPFLCD50(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD50_SHIFT))&LCD_WF8B_BPFLCD50_MASK)
#define LCD_WF8B_BPFLCD18_MASK                   0x20u
#define LCD_WF8B_BPFLCD18_SHIFT                  5
#define LCD_WF8B_BPFLCD18_WIDTH                  1
#define LCD_WF8B_BPFLCD18(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD18_SHIFT))&LCD_WF8B_BPFLCD18_MASK)
#define LCD_WF8B_BPFLCD34_MASK                   0x20u
#define LCD_WF8B_BPFLCD34_SHIFT                  5
#define LCD_WF8B_BPFLCD34_WIDTH                  1
#define LCD_WF8B_BPFLCD34(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD34_SHIFT))&LCD_WF8B_BPFLCD34_MASK)
#define LCD_WF8B_BPFLCD19_MASK                   0x20u
#define LCD_WF8B_BPFLCD19_SHIFT                  5
#define LCD_WF8B_BPFLCD19_WIDTH                  1
#define LCD_WF8B_BPFLCD19(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD19_SHIFT))&LCD_WF8B_BPFLCD19_MASK)
#define LCD_WF8B_BPFLCD2_MASK                    0x20u
#define LCD_WF8B_BPFLCD2_SHIFT                   5
#define LCD_WF8B_BPFLCD2_WIDTH                   1
#define LCD_WF8B_BPFLCD2(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD2_SHIFT))&LCD_WF8B_BPFLCD2_MASK)
#define LCD_WF8B_BPFLCD9_MASK                    0x20u
#define LCD_WF8B_BPFLCD9_SHIFT                   5
#define LCD_WF8B_BPFLCD9_WIDTH                   1
#define LCD_WF8B_BPFLCD9(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD9_SHIFT))&LCD_WF8B_BPFLCD9_MASK)
#define LCD_WF8B_BPFLCD3_MASK                    0x20u
#define LCD_WF8B_BPFLCD3_SHIFT                   5
#define LCD_WF8B_BPFLCD3_WIDTH                   1
#define LCD_WF8B_BPFLCD3(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD3_SHIFT))&LCD_WF8B_BPFLCD3_MASK)
#define LCD_WF8B_BPFLCD37_MASK                   0x20u
#define LCD_WF8B_BPFLCD37_SHIFT                  5
#define LCD_WF8B_BPFLCD37_WIDTH                  1
#define LCD_WF8B_BPFLCD37(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD37_SHIFT))&LCD_WF8B_BPFLCD37_MASK)
#define LCD_WF8B_BPFLCD49_MASK                   0x20u
#define LCD_WF8B_BPFLCD49_SHIFT                  5
#define LCD_WF8B_BPFLCD49_WIDTH                  1
#define LCD_WF8B_BPFLCD49(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD49_SHIFT))&LCD_WF8B_BPFLCD49_MASK)
#define LCD_WF8B_BPFLCD20_MASK                   0x20u
#define LCD_WF8B_BPFLCD20_SHIFT                  5
#define LCD_WF8B_BPFLCD20_WIDTH                  1
#define LCD_WF8B_BPFLCD20(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD20_SHIFT))&LCD_WF8B_BPFLCD20_MASK)
#define LCD_WF8B_BPFLCD44_MASK                   0x20u
#define LCD_WF8B_BPFLCD44_SHIFT                  5
#define LCD_WF8B_BPFLCD44_WIDTH                  1
#define LCD_WF8B_BPFLCD44(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD44_SHIFT))&LCD_WF8B_BPFLCD44_MASK)
#define LCD_WF8B_BPFLCD30_MASK                   0x20u
#define LCD_WF8B_BPFLCD30_SHIFT                  5
#define LCD_WF8B_BPFLCD30_WIDTH                  1
#define LCD_WF8B_BPFLCD30(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD30_SHIFT))&LCD_WF8B_BPFLCD30_MASK)
#define LCD_WF8B_BPFLCD21_MASK                   0x20u
#define LCD_WF8B_BPFLCD21_SHIFT                  5
#define LCD_WF8B_BPFLCD21_WIDTH                  1
#define LCD_WF8B_BPFLCD21(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD21_SHIFT))&LCD_WF8B_BPFLCD21_MASK)
#define LCD_WF8B_BPFLCD35_MASK                   0x20u
#define LCD_WF8B_BPFLCD35_SHIFT                  5
#define LCD_WF8B_BPFLCD35_WIDTH                  1
#define LCD_WF8B_BPFLCD35(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD35_SHIFT))&LCD_WF8B_BPFLCD35_MASK)
#define LCD_WF8B_BPFLCD4_MASK                    0x20u
#define LCD_WF8B_BPFLCD4_SHIFT                   5
#define LCD_WF8B_BPFLCD4_WIDTH                   1
#define LCD_WF8B_BPFLCD4(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD4_SHIFT))&LCD_WF8B_BPFLCD4_MASK)
#define LCD_WF8B_BPFLCD31_MASK                   0x20u
#define LCD_WF8B_BPFLCD31_SHIFT                  5
#define LCD_WF8B_BPFLCD31_WIDTH                  1
#define LCD_WF8B_BPFLCD31(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD31_SHIFT))&LCD_WF8B_BPFLCD31_MASK)
#define LCD_WF8B_BPFLCD48_MASK                   0x20u
#define LCD_WF8B_BPFLCD48_SHIFT                  5
#define LCD_WF8B_BPFLCD48_WIDTH                  1
#define LCD_WF8B_BPFLCD48(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD48_SHIFT))&LCD_WF8B_BPFLCD48_MASK)
#define LCD_WF8B_BPFLCD7_MASK                    0x20u
#define LCD_WF8B_BPFLCD7_SHIFT                   5
#define LCD_WF8B_BPFLCD7_WIDTH                   1
#define LCD_WF8B_BPFLCD7(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD7_SHIFT))&LCD_WF8B_BPFLCD7_MASK)
#define LCD_WF8B_BPFLCD22_MASK                   0x20u
#define LCD_WF8B_BPFLCD22_SHIFT                  5
#define LCD_WF8B_BPFLCD22_WIDTH                  1
#define LCD_WF8B_BPFLCD22(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD22_SHIFT))&LCD_WF8B_BPFLCD22_MASK)
#define LCD_WF8B_BPFLCD38_MASK                   0x20u
#define LCD_WF8B_BPFLCD38_SHIFT                  5
#define LCD_WF8B_BPFLCD38_WIDTH                  1
#define LCD_WF8B_BPFLCD38(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD38_SHIFT))&LCD_WF8B_BPFLCD38_MASK)
#define LCD_WF8B_BPFLCD12_MASK                   0x20u
#define LCD_WF8B_BPFLCD12_SHIFT                  5
#define LCD_WF8B_BPFLCD12_WIDTH                  1
#define LCD_WF8B_BPFLCD12(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD12_SHIFT))&LCD_WF8B_BPFLCD12_MASK)
#define LCD_WF8B_BPFLCD23_MASK                   0x20u
#define LCD_WF8B_BPFLCD23_SHIFT                  5
#define LCD_WF8B_BPFLCD23_WIDTH                  1
#define LCD_WF8B_BPFLCD23(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPFLCD23_SHIFT))&LCD_WF8B_BPFLCD23_MASK)
#define LCD_WF8B_BPGLCD14_MASK                   0x40u
#define LCD_WF8B_BPGLCD14_SHIFT                  6
#define LCD_WF8B_BPGLCD14_WIDTH                  1
#define LCD_WF8B_BPGLCD14(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD14_SHIFT))&LCD_WF8B_BPGLCD14_MASK)
#define LCD_WF8B_BPGLCD55_MASK                   0x40u
#define LCD_WF8B_BPGLCD55_SHIFT                  6
#define LCD_WF8B_BPGLCD55_WIDTH                  1
#define LCD_WF8B_BPGLCD55(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD55_SHIFT))&LCD_WF8B_BPGLCD55_MASK)
#define LCD_WF8B_BPGLCD63_MASK                   0x40u
#define LCD_WF8B_BPGLCD63_SHIFT                  6
#define LCD_WF8B_BPGLCD63_WIDTH                  1
#define LCD_WF8B_BPGLCD63(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD63_SHIFT))&LCD_WF8B_BPGLCD63_MASK)
#define LCD_WF8B_BPGLCD15_MASK                   0x40u
#define LCD_WF8B_BPGLCD15_SHIFT                  6
#define LCD_WF8B_BPGLCD15_WIDTH                  1
#define LCD_WF8B_BPGLCD15(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD15_SHIFT))&LCD_WF8B_BPGLCD15_MASK)
#define LCD_WF8B_BPGLCD62_MASK                   0x40u
#define LCD_WF8B_BPGLCD62_SHIFT                  6
#define LCD_WF8B_BPGLCD62_WIDTH                  1
#define LCD_WF8B_BPGLCD62(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD62_SHIFT))&LCD_WF8B_BPGLCD62_MASK)
#define LCD_WF8B_BPGLCD54_MASK                   0x40u
#define LCD_WF8B_BPGLCD54_SHIFT                  6
#define LCD_WF8B_BPGLCD54_WIDTH                  1
#define LCD_WF8B_BPGLCD54(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD54_SHIFT))&LCD_WF8B_BPGLCD54_MASK)
#define LCD_WF8B_BPGLCD61_MASK                   0x40u
#define LCD_WF8B_BPGLCD61_SHIFT                  6
#define LCD_WF8B_BPGLCD61_WIDTH                  1
#define LCD_WF8B_BPGLCD61(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD61_SHIFT))&LCD_WF8B_BPGLCD61_MASK)
#define LCD_WF8B_BPGLCD60_MASK                   0x40u
#define LCD_WF8B_BPGLCD60_SHIFT                  6
#define LCD_WF8B_BPGLCD60_WIDTH                  1
#define LCD_WF8B_BPGLCD60(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD60_SHIFT))&LCD_WF8B_BPGLCD60_MASK)
#define LCD_WF8B_BPGLCD59_MASK                   0x40u
#define LCD_WF8B_BPGLCD59_SHIFT                  6
#define LCD_WF8B_BPGLCD59_WIDTH                  1
#define LCD_WF8B_BPGLCD59(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD59_SHIFT))&LCD_WF8B_BPGLCD59_MASK)
#define LCD_WF8B_BPGLCD53_MASK                   0x40u
#define LCD_WF8B_BPGLCD53_SHIFT                  6
#define LCD_WF8B_BPGLCD53_WIDTH                  1
#define LCD_WF8B_BPGLCD53(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD53_SHIFT))&LCD_WF8B_BPGLCD53_MASK)
#define LCD_WF8B_BPGLCD58_MASK                   0x40u
#define LCD_WF8B_BPGLCD58_SHIFT                  6
#define LCD_WF8B_BPGLCD58_WIDTH                  1
#define LCD_WF8B_BPGLCD58(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD58_SHIFT))&LCD_WF8B_BPGLCD58_MASK)
#define LCD_WF8B_BPGLCD0_MASK                    0x40u
#define LCD_WF8B_BPGLCD0_SHIFT                   6
#define LCD_WF8B_BPGLCD0_WIDTH                   1
#define LCD_WF8B_BPGLCD0(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD0_SHIFT))&LCD_WF8B_BPGLCD0_MASK)
#define LCD_WF8B_BPGLCD57_MASK                   0x40u
#define LCD_WF8B_BPGLCD57_SHIFT                  6
#define LCD_WF8B_BPGLCD57_WIDTH                  1
#define LCD_WF8B_BPGLCD57(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD57_SHIFT))&LCD_WF8B_BPGLCD57_MASK)
#define LCD_WF8B_BPGLCD52_MASK                   0x40u
#define LCD_WF8B_BPGLCD52_SHIFT                  6
#define LCD_WF8B_BPGLCD52_WIDTH                  1
#define LCD_WF8B_BPGLCD52(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD52_SHIFT))&LCD_WF8B_BPGLCD52_MASK)
#define LCD_WF8B_BPGLCD7_MASK                    0x40u
#define LCD_WF8B_BPGLCD7_SHIFT                   6
#define LCD_WF8B_BPGLCD7_WIDTH                   1
#define LCD_WF8B_BPGLCD7(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD7_SHIFT))&LCD_WF8B_BPGLCD7_MASK)
#define LCD_WF8B_BPGLCD56_MASK                   0x40u
#define LCD_WF8B_BPGLCD56_SHIFT                  6
#define LCD_WF8B_BPGLCD56_WIDTH                  1
#define LCD_WF8B_BPGLCD56(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD56_SHIFT))&LCD_WF8B_BPGLCD56_MASK)
#define LCD_WF8B_BPGLCD6_MASK                    0x40u
#define LCD_WF8B_BPGLCD6_SHIFT                   6
#define LCD_WF8B_BPGLCD6_WIDTH                   1
#define LCD_WF8B_BPGLCD6(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD6_SHIFT))&LCD_WF8B_BPGLCD6_MASK)
#define LCD_WF8B_BPGLCD51_MASK                   0x40u
#define LCD_WF8B_BPGLCD51_SHIFT                  6
#define LCD_WF8B_BPGLCD51_WIDTH                  1
#define LCD_WF8B_BPGLCD51(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD51_SHIFT))&LCD_WF8B_BPGLCD51_MASK)
#define LCD_WF8B_BPGLCD16_MASK                   0x40u
#define LCD_WF8B_BPGLCD16_SHIFT                  6
#define LCD_WF8B_BPGLCD16_WIDTH                  1
#define LCD_WF8B_BPGLCD16(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD16_SHIFT))&LCD_WF8B_BPGLCD16_MASK)
#define LCD_WF8B_BPGLCD1_MASK                    0x40u
#define LCD_WF8B_BPGLCD1_SHIFT                   6
#define LCD_WF8B_BPGLCD1_WIDTH                   1
#define LCD_WF8B_BPGLCD1(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD1_SHIFT))&LCD_WF8B_BPGLCD1_MASK)
#define LCD_WF8B_BPGLCD17_MASK                   0x40u
#define LCD_WF8B_BPGLCD17_SHIFT                  6
#define LCD_WF8B_BPGLCD17_WIDTH                  1
#define LCD_WF8B_BPGLCD17(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD17_SHIFT))&LCD_WF8B_BPGLCD17_MASK)
#define LCD_WF8B_BPGLCD50_MASK                   0x40u
#define LCD_WF8B_BPGLCD50_SHIFT                  6
#define LCD_WF8B_BPGLCD50_WIDTH                  1
#define LCD_WF8B_BPGLCD50(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD50_SHIFT))&LCD_WF8B_BPGLCD50_MASK)
#define LCD_WF8B_BPGLCD18_MASK                   0x40u
#define LCD_WF8B_BPGLCD18_SHIFT                  6
#define LCD_WF8B_BPGLCD18_WIDTH                  1
#define LCD_WF8B_BPGLCD18(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD18_SHIFT))&LCD_WF8B_BPGLCD18_MASK)
#define LCD_WF8B_BPGLCD19_MASK                   0x40u
#define LCD_WF8B_BPGLCD19_SHIFT                  6
#define LCD_WF8B_BPGLCD19_WIDTH                  1
#define LCD_WF8B_BPGLCD19(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD19_SHIFT))&LCD_WF8B_BPGLCD19_MASK)
#define LCD_WF8B_BPGLCD8_MASK                    0x40u
#define LCD_WF8B_BPGLCD8_SHIFT                   6
#define LCD_WF8B_BPGLCD8_WIDTH                   1
#define LCD_WF8B_BPGLCD8(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD8_SHIFT))&LCD_WF8B_BPGLCD8_MASK)
#define LCD_WF8B_BPGLCD49_MASK                   0x40u
#define LCD_WF8B_BPGLCD49_SHIFT                  6
#define LCD_WF8B_BPGLCD49_WIDTH                  1
#define LCD_WF8B_BPGLCD49(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD49_SHIFT))&LCD_WF8B_BPGLCD49_MASK)
#define LCD_WF8B_BPGLCD20_MASK                   0x40u
#define LCD_WF8B_BPGLCD20_SHIFT                  6
#define LCD_WF8B_BPGLCD20_WIDTH                  1
#define LCD_WF8B_BPGLCD20(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD20_SHIFT))&LCD_WF8B_BPGLCD20_MASK)
#define LCD_WF8B_BPGLCD9_MASK                    0x40u
#define LCD_WF8B_BPGLCD9_SHIFT                   6
#define LCD_WF8B_BPGLCD9_WIDTH                   1
#define LCD_WF8B_BPGLCD9(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD9_SHIFT))&LCD_WF8B_BPGLCD9_MASK)
#define LCD_WF8B_BPGLCD21_MASK                   0x40u
#define LCD_WF8B_BPGLCD21_SHIFT                  6
#define LCD_WF8B_BPGLCD21_WIDTH                  1
#define LCD_WF8B_BPGLCD21(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD21_SHIFT))&LCD_WF8B_BPGLCD21_MASK)
#define LCD_WF8B_BPGLCD13_MASK                   0x40u
#define LCD_WF8B_BPGLCD13_SHIFT                  6
#define LCD_WF8B_BPGLCD13_WIDTH                  1
#define LCD_WF8B_BPGLCD13(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD13_SHIFT))&LCD_WF8B_BPGLCD13_MASK)
#define LCD_WF8B_BPGLCD48_MASK                   0x40u
#define LCD_WF8B_BPGLCD48_SHIFT                  6
#define LCD_WF8B_BPGLCD48_WIDTH                  1
#define LCD_WF8B_BPGLCD48(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD48_SHIFT))&LCD_WF8B_BPGLCD48_MASK)
#define LCD_WF8B_BPGLCD22_MASK                   0x40u
#define LCD_WF8B_BPGLCD22_SHIFT                  6
#define LCD_WF8B_BPGLCD22_WIDTH                  1
#define LCD_WF8B_BPGLCD22(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD22_SHIFT))&LCD_WF8B_BPGLCD22_MASK)
#define LCD_WF8B_BPGLCD5_MASK                    0x40u
#define LCD_WF8B_BPGLCD5_SHIFT                   6
#define LCD_WF8B_BPGLCD5_WIDTH                   1
#define LCD_WF8B_BPGLCD5(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD5_SHIFT))&LCD_WF8B_BPGLCD5_MASK)
#define LCD_WF8B_BPGLCD47_MASK                   0x40u
#define LCD_WF8B_BPGLCD47_SHIFT                  6
#define LCD_WF8B_BPGLCD47_WIDTH                  1
#define LCD_WF8B_BPGLCD47(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD47_SHIFT))&LCD_WF8B_BPGLCD47_MASK)
#define LCD_WF8B_BPGLCD23_MASK                   0x40u
#define LCD_WF8B_BPGLCD23_SHIFT                  6
#define LCD_WF8B_BPGLCD23_WIDTH                  1
#define LCD_WF8B_BPGLCD23(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD23_SHIFT))&LCD_WF8B_BPGLCD23_MASK)
#define LCD_WF8B_BPGLCD24_MASK                   0x40u
#define LCD_WF8B_BPGLCD24_SHIFT                  6
#define LCD_WF8B_BPGLCD24_WIDTH                  1
#define LCD_WF8B_BPGLCD24(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD24_SHIFT))&LCD_WF8B_BPGLCD24_MASK)
#define LCD_WF8B_BPGLCD25_MASK                   0x40u
#define LCD_WF8B_BPGLCD25_SHIFT                  6
#define LCD_WF8B_BPGLCD25_WIDTH                  1
#define LCD_WF8B_BPGLCD25(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD25_SHIFT))&LCD_WF8B_BPGLCD25_MASK)
#define LCD_WF8B_BPGLCD46_MASK                   0x40u
#define LCD_WF8B_BPGLCD46_SHIFT                  6
#define LCD_WF8B_BPGLCD46_WIDTH                  1
#define LCD_WF8B_BPGLCD46(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD46_SHIFT))&LCD_WF8B_BPGLCD46_MASK)
#define LCD_WF8B_BPGLCD26_MASK                   0x40u
#define LCD_WF8B_BPGLCD26_SHIFT                  6
#define LCD_WF8B_BPGLCD26_WIDTH                  1
#define LCD_WF8B_BPGLCD26(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD26_SHIFT))&LCD_WF8B_BPGLCD26_MASK)
#define LCD_WF8B_BPGLCD27_MASK                   0x40u
#define LCD_WF8B_BPGLCD27_SHIFT                  6
#define LCD_WF8B_BPGLCD27_WIDTH                  1
#define LCD_WF8B_BPGLCD27(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD27_SHIFT))&LCD_WF8B_BPGLCD27_MASK)
#define LCD_WF8B_BPGLCD10_MASK                   0x40u
#define LCD_WF8B_BPGLCD10_SHIFT                  6
#define LCD_WF8B_BPGLCD10_WIDTH                  1
#define LCD_WF8B_BPGLCD10(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD10_SHIFT))&LCD_WF8B_BPGLCD10_MASK)
#define LCD_WF8B_BPGLCD45_MASK                   0x40u
#define LCD_WF8B_BPGLCD45_SHIFT                  6
#define LCD_WF8B_BPGLCD45_WIDTH                  1
#define LCD_WF8B_BPGLCD45(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD45_SHIFT))&LCD_WF8B_BPGLCD45_MASK)
#define LCD_WF8B_BPGLCD28_MASK                   0x40u
#define LCD_WF8B_BPGLCD28_SHIFT                  6
#define LCD_WF8B_BPGLCD28_WIDTH                  1
#define LCD_WF8B_BPGLCD28(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD28_SHIFT))&LCD_WF8B_BPGLCD28_MASK)
#define LCD_WF8B_BPGLCD29_MASK                   0x40u
#define LCD_WF8B_BPGLCD29_SHIFT                  6
#define LCD_WF8B_BPGLCD29_WIDTH                  1
#define LCD_WF8B_BPGLCD29(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD29_SHIFT))&LCD_WF8B_BPGLCD29_MASK)
#define LCD_WF8B_BPGLCD4_MASK                    0x40u
#define LCD_WF8B_BPGLCD4_SHIFT                   6
#define LCD_WF8B_BPGLCD4_WIDTH                   1
#define LCD_WF8B_BPGLCD4(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD4_SHIFT))&LCD_WF8B_BPGLCD4_MASK)
#define LCD_WF8B_BPGLCD44_MASK                   0x40u
#define LCD_WF8B_BPGLCD44_SHIFT                  6
#define LCD_WF8B_BPGLCD44_WIDTH                  1
#define LCD_WF8B_BPGLCD44(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD44_SHIFT))&LCD_WF8B_BPGLCD44_MASK)
#define LCD_WF8B_BPGLCD30_MASK                   0x40u
#define LCD_WF8B_BPGLCD30_SHIFT                  6
#define LCD_WF8B_BPGLCD30_WIDTH                  1
#define LCD_WF8B_BPGLCD30(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD30_SHIFT))&LCD_WF8B_BPGLCD30_MASK)
#define LCD_WF8B_BPGLCD2_MASK                    0x40u
#define LCD_WF8B_BPGLCD2_SHIFT                   6
#define LCD_WF8B_BPGLCD2_WIDTH                   1
#define LCD_WF8B_BPGLCD2(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD2_SHIFT))&LCD_WF8B_BPGLCD2_MASK)
#define LCD_WF8B_BPGLCD31_MASK                   0x40u
#define LCD_WF8B_BPGLCD31_SHIFT                  6
#define LCD_WF8B_BPGLCD31_WIDTH                  1
#define LCD_WF8B_BPGLCD31(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD31_SHIFT))&LCD_WF8B_BPGLCD31_MASK)
#define LCD_WF8B_BPGLCD43_MASK                   0x40u
#define LCD_WF8B_BPGLCD43_SHIFT                  6
#define LCD_WF8B_BPGLCD43_WIDTH                  1
#define LCD_WF8B_BPGLCD43(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD43_SHIFT))&LCD_WF8B_BPGLCD43_MASK)
#define LCD_WF8B_BPGLCD32_MASK                   0x40u
#define LCD_WF8B_BPGLCD32_SHIFT                  6
#define LCD_WF8B_BPGLCD32_WIDTH                  1
#define LCD_WF8B_BPGLCD32(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD32_SHIFT))&LCD_WF8B_BPGLCD32_MASK)
#define LCD_WF8B_BPGLCD33_MASK                   0x40u
#define LCD_WF8B_BPGLCD33_SHIFT                  6
#define LCD_WF8B_BPGLCD33_WIDTH                  1
#define LCD_WF8B_BPGLCD33(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD33_SHIFT))&LCD_WF8B_BPGLCD33_MASK)
#define LCD_WF8B_BPGLCD42_MASK                   0x40u
#define LCD_WF8B_BPGLCD42_SHIFT                  6
#define LCD_WF8B_BPGLCD42_WIDTH                  1
#define LCD_WF8B_BPGLCD42(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD42_SHIFT))&LCD_WF8B_BPGLCD42_MASK)
#define LCD_WF8B_BPGLCD34_MASK                   0x40u
#define LCD_WF8B_BPGLCD34_SHIFT                  6
#define LCD_WF8B_BPGLCD34_WIDTH                  1
#define LCD_WF8B_BPGLCD34(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD34_SHIFT))&LCD_WF8B_BPGLCD34_MASK)
#define LCD_WF8B_BPGLCD11_MASK                   0x40u
#define LCD_WF8B_BPGLCD11_SHIFT                  6
#define LCD_WF8B_BPGLCD11_WIDTH                  1
#define LCD_WF8B_BPGLCD11(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD11_SHIFT))&LCD_WF8B_BPGLCD11_MASK)
#define LCD_WF8B_BPGLCD35_MASK                   0x40u
#define LCD_WF8B_BPGLCD35_SHIFT                  6
#define LCD_WF8B_BPGLCD35_WIDTH                  1
#define LCD_WF8B_BPGLCD35(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD35_SHIFT))&LCD_WF8B_BPGLCD35_MASK)
#define LCD_WF8B_BPGLCD12_MASK                   0x40u
#define LCD_WF8B_BPGLCD12_SHIFT                  6
#define LCD_WF8B_BPGLCD12_WIDTH                  1
#define LCD_WF8B_BPGLCD12(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD12_SHIFT))&LCD_WF8B_BPGLCD12_MASK)
#define LCD_WF8B_BPGLCD41_MASK                   0x40u
#define LCD_WF8B_BPGLCD41_SHIFT                  6
#define LCD_WF8B_BPGLCD41_WIDTH                  1
#define LCD_WF8B_BPGLCD41(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD41_SHIFT))&LCD_WF8B_BPGLCD41_MASK)
#define LCD_WF8B_BPGLCD36_MASK                   0x40u
#define LCD_WF8B_BPGLCD36_SHIFT                  6
#define LCD_WF8B_BPGLCD36_WIDTH                  1
#define LCD_WF8B_BPGLCD36(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD36_SHIFT))&LCD_WF8B_BPGLCD36_MASK)
#define LCD_WF8B_BPGLCD3_MASK                    0x40u
#define LCD_WF8B_BPGLCD3_SHIFT                   6
#define LCD_WF8B_BPGLCD3_WIDTH                   1
#define LCD_WF8B_BPGLCD3(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD3_SHIFT))&LCD_WF8B_BPGLCD3_MASK)
#define LCD_WF8B_BPGLCD37_MASK                   0x40u
#define LCD_WF8B_BPGLCD37_SHIFT                  6
#define LCD_WF8B_BPGLCD37_WIDTH                  1
#define LCD_WF8B_BPGLCD37(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD37_SHIFT))&LCD_WF8B_BPGLCD37_MASK)
#define LCD_WF8B_BPGLCD40_MASK                   0x40u
#define LCD_WF8B_BPGLCD40_SHIFT                  6
#define LCD_WF8B_BPGLCD40_WIDTH                  1
#define LCD_WF8B_BPGLCD40(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD40_SHIFT))&LCD_WF8B_BPGLCD40_MASK)
#define LCD_WF8B_BPGLCD38_MASK                   0x40u
#define LCD_WF8B_BPGLCD38_SHIFT                  6
#define LCD_WF8B_BPGLCD38_WIDTH                  1
#define LCD_WF8B_BPGLCD38(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD38_SHIFT))&LCD_WF8B_BPGLCD38_MASK)
#define LCD_WF8B_BPGLCD39_MASK                   0x40u
#define LCD_WF8B_BPGLCD39_SHIFT                  6
#define LCD_WF8B_BPGLCD39_WIDTH                  1
#define LCD_WF8B_BPGLCD39(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPGLCD39_SHIFT))&LCD_WF8B_BPGLCD39_MASK)
#define LCD_WF8B_BPHLCD63_MASK                   0x80u
#define LCD_WF8B_BPHLCD63_SHIFT                  7
#define LCD_WF8B_BPHLCD63_WIDTH                  1
#define LCD_WF8B_BPHLCD63(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD63_SHIFT))&LCD_WF8B_BPHLCD63_MASK)
#define LCD_WF8B_BPHLCD62_MASK                   0x80u
#define LCD_WF8B_BPHLCD62_SHIFT                  7
#define LCD_WF8B_BPHLCD62_WIDTH                  1
#define LCD_WF8B_BPHLCD62(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD62_SHIFT))&LCD_WF8B_BPHLCD62_MASK)
#define LCD_WF8B_BPHLCD61_MASK                   0x80u
#define LCD_WF8B_BPHLCD61_SHIFT                  7
#define LCD_WF8B_BPHLCD61_WIDTH                  1
#define LCD_WF8B_BPHLCD61(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD61_SHIFT))&LCD_WF8B_BPHLCD61_MASK)
#define LCD_WF8B_BPHLCD60_MASK                   0x80u
#define LCD_WF8B_BPHLCD60_SHIFT                  7
#define LCD_WF8B_BPHLCD60_WIDTH                  1
#define LCD_WF8B_BPHLCD60(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD60_SHIFT))&LCD_WF8B_BPHLCD60_MASK)
#define LCD_WF8B_BPHLCD59_MASK                   0x80u
#define LCD_WF8B_BPHLCD59_SHIFT                  7
#define LCD_WF8B_BPHLCD59_WIDTH                  1
#define LCD_WF8B_BPHLCD59(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD59_SHIFT))&LCD_WF8B_BPHLCD59_MASK)
#define LCD_WF8B_BPHLCD58_MASK                   0x80u
#define LCD_WF8B_BPHLCD58_SHIFT                  7
#define LCD_WF8B_BPHLCD58_WIDTH                  1
#define LCD_WF8B_BPHLCD58(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD58_SHIFT))&LCD_WF8B_BPHLCD58_MASK)
#define LCD_WF8B_BPHLCD57_MASK                   0x80u
#define LCD_WF8B_BPHLCD57_SHIFT                  7
#define LCD_WF8B_BPHLCD57_WIDTH                  1
#define LCD_WF8B_BPHLCD57(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD57_SHIFT))&LCD_WF8B_BPHLCD57_MASK)
#define LCD_WF8B_BPHLCD0_MASK                    0x80u
#define LCD_WF8B_BPHLCD0_SHIFT                   7
#define LCD_WF8B_BPHLCD0_WIDTH                   1
#define LCD_WF8B_BPHLCD0(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD0_SHIFT))&LCD_WF8B_BPHLCD0_MASK)
#define LCD_WF8B_BPHLCD56_MASK                   0x80u
#define LCD_WF8B_BPHLCD56_SHIFT                  7
#define LCD_WF8B_BPHLCD56_WIDTH                  1
#define LCD_WF8B_BPHLCD56(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD56_SHIFT))&LCD_WF8B_BPHLCD56_MASK)
#define LCD_WF8B_BPHLCD55_MASK                   0x80u
#define LCD_WF8B_BPHLCD55_SHIFT                  7
#define LCD_WF8B_BPHLCD55_WIDTH                  1
#define LCD_WF8B_BPHLCD55(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD55_SHIFT))&LCD_WF8B_BPHLCD55_MASK)
#define LCD_WF8B_BPHLCD54_MASK                   0x80u
#define LCD_WF8B_BPHLCD54_SHIFT                  7
#define LCD_WF8B_BPHLCD54_WIDTH                  1
#define LCD_WF8B_BPHLCD54(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD54_SHIFT))&LCD_WF8B_BPHLCD54_MASK)
#define LCD_WF8B_BPHLCD53_MASK                   0x80u
#define LCD_WF8B_BPHLCD53_SHIFT                  7
#define LCD_WF8B_BPHLCD53_WIDTH                  1
#define LCD_WF8B_BPHLCD53(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD53_SHIFT))&LCD_WF8B_BPHLCD53_MASK)
#define LCD_WF8B_BPHLCD52_MASK                   0x80u
#define LCD_WF8B_BPHLCD52_SHIFT                  7
#define LCD_WF8B_BPHLCD52_WIDTH                  1
#define LCD_WF8B_BPHLCD52(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD52_SHIFT))&LCD_WF8B_BPHLCD52_MASK)
#define LCD_WF8B_BPHLCD51_MASK                   0x80u
#define LCD_WF8B_BPHLCD51_SHIFT                  7
#define LCD_WF8B_BPHLCD51_WIDTH                  1
#define LCD_WF8B_BPHLCD51(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD51_SHIFT))&LCD_WF8B_BPHLCD51_MASK)
#define LCD_WF8B_BPHLCD50_MASK                   0x80u
#define LCD_WF8B_BPHLCD50_SHIFT                  7
#define LCD_WF8B_BPHLCD50_WIDTH                  1
#define LCD_WF8B_BPHLCD50(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD50_SHIFT))&LCD_WF8B_BPHLCD50_MASK)
#define LCD_WF8B_BPHLCD1_MASK                    0x80u
#define LCD_WF8B_BPHLCD1_SHIFT                   7
#define LCD_WF8B_BPHLCD1_WIDTH                   1
#define LCD_WF8B_BPHLCD1(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD1_SHIFT))&LCD_WF8B_BPHLCD1_MASK)
#define LCD_WF8B_BPHLCD49_MASK                   0x80u
#define LCD_WF8B_BPHLCD49_SHIFT                  7
#define LCD_WF8B_BPHLCD49_WIDTH                  1
#define LCD_WF8B_BPHLCD49(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD49_SHIFT))&LCD_WF8B_BPHLCD49_MASK)
#define LCD_WF8B_BPHLCD48_MASK                   0x80u
#define LCD_WF8B_BPHLCD48_SHIFT                  7
#define LCD_WF8B_BPHLCD48_WIDTH                  1
#define LCD_WF8B_BPHLCD48(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD48_SHIFT))&LCD_WF8B_BPHLCD48_MASK)
#define LCD_WF8B_BPHLCD47_MASK                   0x80u
#define LCD_WF8B_BPHLCD47_SHIFT                  7
#define LCD_WF8B_BPHLCD47_WIDTH                  1
#define LCD_WF8B_BPHLCD47(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD47_SHIFT))&LCD_WF8B_BPHLCD47_MASK)
#define LCD_WF8B_BPHLCD46_MASK                   0x80u
#define LCD_WF8B_BPHLCD46_SHIFT                  7
#define LCD_WF8B_BPHLCD46_WIDTH                  1
#define LCD_WF8B_BPHLCD46(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD46_SHIFT))&LCD_WF8B_BPHLCD46_MASK)
#define LCD_WF8B_BPHLCD45_MASK                   0x80u
#define LCD_WF8B_BPHLCD45_SHIFT                  7
#define LCD_WF8B_BPHLCD45_WIDTH                  1
#define LCD_WF8B_BPHLCD45(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD45_SHIFT))&LCD_WF8B_BPHLCD45_MASK)
#define LCD_WF8B_BPHLCD44_MASK                   0x80u
#define LCD_WF8B_BPHLCD44_SHIFT                  7
#define LCD_WF8B_BPHLCD44_WIDTH                  1
#define LCD_WF8B_BPHLCD44(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD44_SHIFT))&LCD_WF8B_BPHLCD44_MASK)
#define LCD_WF8B_BPHLCD43_MASK                   0x80u
#define LCD_WF8B_BPHLCD43_SHIFT                  7
#define LCD_WF8B_BPHLCD43_WIDTH                  1
#define LCD_WF8B_BPHLCD43(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD43_SHIFT))&LCD_WF8B_BPHLCD43_MASK)
#define LCD_WF8B_BPHLCD2_MASK                    0x80u
#define LCD_WF8B_BPHLCD2_SHIFT                   7
#define LCD_WF8B_BPHLCD2_WIDTH                   1
#define LCD_WF8B_BPHLCD2(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD2_SHIFT))&LCD_WF8B_BPHLCD2_MASK)
#define LCD_WF8B_BPHLCD42_MASK                   0x80u
#define LCD_WF8B_BPHLCD42_SHIFT                  7
#define LCD_WF8B_BPHLCD42_WIDTH                  1
#define LCD_WF8B_BPHLCD42(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD42_SHIFT))&LCD_WF8B_BPHLCD42_MASK)
#define LCD_WF8B_BPHLCD41_MASK                   0x80u
#define LCD_WF8B_BPHLCD41_SHIFT                  7
#define LCD_WF8B_BPHLCD41_WIDTH                  1
#define LCD_WF8B_BPHLCD41(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD41_SHIFT))&LCD_WF8B_BPHLCD41_MASK)
#define LCD_WF8B_BPHLCD40_MASK                   0x80u
#define LCD_WF8B_BPHLCD40_SHIFT                  7
#define LCD_WF8B_BPHLCD40_WIDTH                  1
#define LCD_WF8B_BPHLCD40(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD40_SHIFT))&LCD_WF8B_BPHLCD40_MASK)
#define LCD_WF8B_BPHLCD39_MASK                   0x80u
#define LCD_WF8B_BPHLCD39_SHIFT                  7
#define LCD_WF8B_BPHLCD39_WIDTH                  1
#define LCD_WF8B_BPHLCD39(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD39_SHIFT))&LCD_WF8B_BPHLCD39_MASK)
#define LCD_WF8B_BPHLCD38_MASK                   0x80u
#define LCD_WF8B_BPHLCD38_SHIFT                  7
#define LCD_WF8B_BPHLCD38_WIDTH                  1
#define LCD_WF8B_BPHLCD38(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD38_SHIFT))&LCD_WF8B_BPHLCD38_MASK)
#define LCD_WF8B_BPHLCD37_MASK                   0x80u
#define LCD_WF8B_BPHLCD37_SHIFT                  7
#define LCD_WF8B_BPHLCD37_WIDTH                  1
#define LCD_WF8B_BPHLCD37(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD37_SHIFT))&LCD_WF8B_BPHLCD37_MASK)
#define LCD_WF8B_BPHLCD36_MASK                   0x80u
#define LCD_WF8B_BPHLCD36_SHIFT                  7
#define LCD_WF8B_BPHLCD36_WIDTH                  1
#define LCD_WF8B_BPHLCD36(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD36_SHIFT))&LCD_WF8B_BPHLCD36_MASK)
#define LCD_WF8B_BPHLCD3_MASK                    0x80u
#define LCD_WF8B_BPHLCD3_SHIFT                   7
#define LCD_WF8B_BPHLCD3_WIDTH                   1
#define LCD_WF8B_BPHLCD3(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD3_SHIFT))&LCD_WF8B_BPHLCD3_MASK)
#define LCD_WF8B_BPHLCD35_MASK                   0x80u
#define LCD_WF8B_BPHLCD35_SHIFT                  7
#define LCD_WF8B_BPHLCD35_WIDTH                  1
#define LCD_WF8B_BPHLCD35(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD35_SHIFT))&LCD_WF8B_BPHLCD35_MASK)
#define LCD_WF8B_BPHLCD34_MASK                   0x80u
#define LCD_WF8B_BPHLCD34_SHIFT                  7
#define LCD_WF8B_BPHLCD34_WIDTH                  1
#define LCD_WF8B_BPHLCD34(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD34_SHIFT))&LCD_WF8B_BPHLCD34_MASK)
#define LCD_WF8B_BPHLCD33_MASK                   0x80u
#define LCD_WF8B_BPHLCD33_SHIFT                  7
#define LCD_WF8B_BPHLCD33_WIDTH                  1
#define LCD_WF8B_BPHLCD33(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD33_SHIFT))&LCD_WF8B_BPHLCD33_MASK)
#define LCD_WF8B_BPHLCD32_MASK                   0x80u
#define LCD_WF8B_BPHLCD32_SHIFT                  7
#define LCD_WF8B_BPHLCD32_WIDTH                  1
#define LCD_WF8B_BPHLCD32(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD32_SHIFT))&LCD_WF8B_BPHLCD32_MASK)
#define LCD_WF8B_BPHLCD31_MASK                   0x80u
#define LCD_WF8B_BPHLCD31_SHIFT                  7
#define LCD_WF8B_BPHLCD31_WIDTH                  1
#define LCD_WF8B_BPHLCD31(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD31_SHIFT))&LCD_WF8B_BPHLCD31_MASK)
#define LCD_WF8B_BPHLCD30_MASK                   0x80u
#define LCD_WF8B_BPHLCD30_SHIFT                  7
#define LCD_WF8B_BPHLCD30_WIDTH                  1
#define LCD_WF8B_BPHLCD30(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD30_SHIFT))&LCD_WF8B_BPHLCD30_MASK)
#define LCD_WF8B_BPHLCD29_MASK                   0x80u
#define LCD_WF8B_BPHLCD29_SHIFT                  7
#define LCD_WF8B_BPHLCD29_WIDTH                  1
#define LCD_WF8B_BPHLCD29(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD29_SHIFT))&LCD_WF8B_BPHLCD29_MASK)
#define LCD_WF8B_BPHLCD4_MASK                    0x80u
#define LCD_WF8B_BPHLCD4_SHIFT                   7
#define LCD_WF8B_BPHLCD4_WIDTH                   1
#define LCD_WF8B_BPHLCD4(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD4_SHIFT))&LCD_WF8B_BPHLCD4_MASK)
#define LCD_WF8B_BPHLCD28_MASK                   0x80u
#define LCD_WF8B_BPHLCD28_SHIFT                  7
#define LCD_WF8B_BPHLCD28_WIDTH                  1
#define LCD_WF8B_BPHLCD28(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD28_SHIFT))&LCD_WF8B_BPHLCD28_MASK)
#define LCD_WF8B_BPHLCD27_MASK                   0x80u
#define LCD_WF8B_BPHLCD27_SHIFT                  7
#define LCD_WF8B_BPHLCD27_WIDTH                  1
#define LCD_WF8B_BPHLCD27(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD27_SHIFT))&LCD_WF8B_BPHLCD27_MASK)
#define LCD_WF8B_BPHLCD26_MASK                   0x80u
#define LCD_WF8B_BPHLCD26_SHIFT                  7
#define LCD_WF8B_BPHLCD26_WIDTH                  1
#define LCD_WF8B_BPHLCD26(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD26_SHIFT))&LCD_WF8B_BPHLCD26_MASK)
#define LCD_WF8B_BPHLCD25_MASK                   0x80u
#define LCD_WF8B_BPHLCD25_SHIFT                  7
#define LCD_WF8B_BPHLCD25_WIDTH                  1
#define LCD_WF8B_BPHLCD25(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD25_SHIFT))&LCD_WF8B_BPHLCD25_MASK)
#define LCD_WF8B_BPHLCD24_MASK                   0x80u
#define LCD_WF8B_BPHLCD24_SHIFT                  7
#define LCD_WF8B_BPHLCD24_WIDTH                  1
#define LCD_WF8B_BPHLCD24(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD24_SHIFT))&LCD_WF8B_BPHLCD24_MASK)
#define LCD_WF8B_BPHLCD23_MASK                   0x80u
#define LCD_WF8B_BPHLCD23_SHIFT                  7
#define LCD_WF8B_BPHLCD23_WIDTH                  1
#define LCD_WF8B_BPHLCD23(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD23_SHIFT))&LCD_WF8B_BPHLCD23_MASK)
#define LCD_WF8B_BPHLCD22_MASK                   0x80u
#define LCD_WF8B_BPHLCD22_SHIFT                  7
#define LCD_WF8B_BPHLCD22_WIDTH                  1
#define LCD_WF8B_BPHLCD22(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD22_SHIFT))&LCD_WF8B_BPHLCD22_MASK)
#define LCD_WF8B_BPHLCD5_MASK                    0x80u
#define LCD_WF8B_BPHLCD5_SHIFT                   7
#define LCD_WF8B_BPHLCD5_WIDTH                   1
#define LCD_WF8B_BPHLCD5(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD5_SHIFT))&LCD_WF8B_BPHLCD5_MASK)
#define LCD_WF8B_BPHLCD21_MASK                   0x80u
#define LCD_WF8B_BPHLCD21_SHIFT                  7
#define LCD_WF8B_BPHLCD21_WIDTH                  1
#define LCD_WF8B_BPHLCD21(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD21_SHIFT))&LCD_WF8B_BPHLCD21_MASK)
#define LCD_WF8B_BPHLCD20_MASK                   0x80u
#define LCD_WF8B_BPHLCD20_SHIFT                  7
#define LCD_WF8B_BPHLCD20_WIDTH                  1
#define LCD_WF8B_BPHLCD20(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD20_SHIFT))&LCD_WF8B_BPHLCD20_MASK)
#define LCD_WF8B_BPHLCD19_MASK                   0x80u
#define LCD_WF8B_BPHLCD19_SHIFT                  7
#define LCD_WF8B_BPHLCD19_WIDTH                  1
#define LCD_WF8B_BPHLCD19(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD19_SHIFT))&LCD_WF8B_BPHLCD19_MASK)
#define LCD_WF8B_BPHLCD18_MASK                   0x80u
#define LCD_WF8B_BPHLCD18_SHIFT                  7
#define LCD_WF8B_BPHLCD18_WIDTH                  1
#define LCD_WF8B_BPHLCD18(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD18_SHIFT))&LCD_WF8B_BPHLCD18_MASK)
#define LCD_WF8B_BPHLCD17_MASK                   0x80u
#define LCD_WF8B_BPHLCD17_SHIFT                  7
#define LCD_WF8B_BPHLCD17_WIDTH                  1
#define LCD_WF8B_BPHLCD17(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD17_SHIFT))&LCD_WF8B_BPHLCD17_MASK)
#define LCD_WF8B_BPHLCD16_MASK                   0x80u
#define LCD_WF8B_BPHLCD16_SHIFT                  7
#define LCD_WF8B_BPHLCD16_WIDTH                  1
#define LCD_WF8B_BPHLCD16(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD16_SHIFT))&LCD_WF8B_BPHLCD16_MASK)
#define LCD_WF8B_BPHLCD15_MASK                   0x80u
#define LCD_WF8B_BPHLCD15_SHIFT                  7
#define LCD_WF8B_BPHLCD15_WIDTH                  1
#define LCD_WF8B_BPHLCD15(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD15_SHIFT))&LCD_WF8B_BPHLCD15_MASK)
#define LCD_WF8B_BPHLCD6_MASK                    0x80u
#define LCD_WF8B_BPHLCD6_SHIFT                   7
#define LCD_WF8B_BPHLCD6_WIDTH                   1
#define LCD_WF8B_BPHLCD6(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD6_SHIFT))&LCD_WF8B_BPHLCD6_MASK)
#define LCD_WF8B_BPHLCD14_MASK                   0x80u
#define LCD_WF8B_BPHLCD14_SHIFT                  7
#define LCD_WF8B_BPHLCD14_WIDTH                  1
#define LCD_WF8B_BPHLCD14(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD14_SHIFT))&LCD_WF8B_BPHLCD14_MASK)
#define LCD_WF8B_BPHLCD13_MASK                   0x80u
#define LCD_WF8B_BPHLCD13_SHIFT                  7
#define LCD_WF8B_BPHLCD13_WIDTH                  1
#define LCD_WF8B_BPHLCD13(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD13_SHIFT))&LCD_WF8B_BPHLCD13_MASK)
#define LCD_WF8B_BPHLCD12_MASK                   0x80u
#define LCD_WF8B_BPHLCD12_SHIFT                  7
#define LCD_WF8B_BPHLCD12_WIDTH                  1
#define LCD_WF8B_BPHLCD12(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD12_SHIFT))&LCD_WF8B_BPHLCD12_MASK)
#define LCD_WF8B_BPHLCD11_MASK                   0x80u
#define LCD_WF8B_BPHLCD11_SHIFT                  7
#define LCD_WF8B_BPHLCD11_WIDTH                  1
#define LCD_WF8B_BPHLCD11(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD11_SHIFT))&LCD_WF8B_BPHLCD11_MASK)
#define LCD_WF8B_BPHLCD10_MASK                   0x80u
#define LCD_WF8B_BPHLCD10_SHIFT                  7
#define LCD_WF8B_BPHLCD10_WIDTH                  1
#define LCD_WF8B_BPHLCD10(x)                     (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD10_SHIFT))&LCD_WF8B_BPHLCD10_MASK)
#define LCD_WF8B_BPHLCD9_MASK                    0x80u
#define LCD_WF8B_BPHLCD9_SHIFT                   7
#define LCD_WF8B_BPHLCD9_WIDTH                   1
#define LCD_WF8B_BPHLCD9(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD9_SHIFT))&LCD_WF8B_BPHLCD9_MASK)
#define LCD_WF8B_BPHLCD8_MASK                    0x80u
#define LCD_WF8B_BPHLCD8_SHIFT                   7
#define LCD_WF8B_BPHLCD8_WIDTH                   1
#define LCD_WF8B_BPHLCD8(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD8_SHIFT))&LCD_WF8B_BPHLCD8_MASK)
#define LCD_WF8B_BPHLCD7_MASK                    0x80u
#define LCD_WF8B_BPHLCD7_SHIFT                   7
#define LCD_WF8B_BPHLCD7_WIDTH                   1
#define LCD_WF8B_BPHLCD7(x)                      (((uint8_t)(((uint8_t)(x))<<LCD_WF8B_BPHLCD7_SHIFT))&LCD_WF8B_BPHLCD7_MASK)

/*!
 * @}
 */ /* end of group LCD_Register_Masks */


/* LCD - Peripheral instance base addresses */
/** Peripheral LCD base address */
#define LCD_BASE                                 (0x40043000u)
/** Peripheral LCD base pointer */
#define LCD                                      ((LCD_Type *)LCD_BASE)
#define LCD_BASE_PTR                             (LCD)
/** Array initializer of LCD peripheral base addresses */
#define LCD_BASE_ADDRS                           { LCD_BASE }
/** Array initializer of LCD peripheral base pointers */
#define LCD_BASE_PTRS                            { LCD }
/** Interrupt vectors for the LCD peripheral type */
#define LCD_LCD_IRQS                             { LCD_IRQn }

/* ----------------------------------------------------------------------------
   -- LCD - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LCD_Register_Accessor_Macros LCD - Register accessor macros
 * @{
 */


/* LCD - Register instance definitions */
/* LCD */
#define LCD_GCR                                  LCD_GCR_REG(LCD)
#define LCD_AR                                   LCD_AR_REG(LCD)
#define LCD_FDCR                                 LCD_FDCR_REG(LCD)
#define LCD_FDSR                                 LCD_FDSR_REG(LCD)
#define LCD_PENL                                 LCD_PEN_REG(LCD,0)
#define LCD_PENH                                 LCD_PEN_REG(LCD,1)
#define LCD_BPENL                                LCD_BPEN_REG(LCD,0)
#define LCD_BPENH                                LCD_BPEN_REG(LCD,1)
#define LCD_WF0                                  LCD_WF8B_REG(LCD,0)
#define LCD_WF3TO0                               LCD_WF_REG(LCD,0)
#define LCD_WF1                                  LCD_WF8B_REG(LCD,1)
#define LCD_WF2                                  LCD_WF8B_REG(LCD,2)
#define LCD_WF3                                  LCD_WF8B_REG(LCD,3)
#define LCD_WF4                                  LCD_WF8B_REG(LCD,4)
#define LCD_WF7TO4                               LCD_WF_REG(LCD,1)
#define LCD_WF5                                  LCD_WF8B_REG(LCD,5)
#define LCD_WF6                                  LCD_WF8B_REG(LCD,6)
#define LCD_WF7                                  LCD_WF8B_REG(LCD,7)
#define LCD_WF11TO8                              LCD_WF_REG(LCD,2)
#define LCD_WF8                                  LCD_WF8B_REG(LCD,8)
#define LCD_WF9                                  LCD_WF8B_REG(LCD,9)
#define LCD_WF10                                 LCD_WF8B_REG(LCD,10)
#define LCD_WF11                                 LCD_WF8B_REG(LCD,11)
#define LCD_WF12                                 LCD_WF8B_REG(LCD,12)
#define LCD_WF15TO12                             LCD_WF_REG(LCD,3)
#define LCD_WF13                                 LCD_WF8B_REG(LCD,13)
#define LCD_WF14                                 LCD_WF8B_REG(LCD,14)
#define LCD_WF15                                 LCD_WF8B_REG(LCD,15)
#define LCD_WF16                                 LCD_WF8B_REG(LCD,16)
#define LCD_WF19TO16                             LCD_WF_REG(LCD,4)
#define LCD_WF17                                 LCD_WF8B_REG(LCD,17)
#define LCD_WF18                                 LCD_WF8B_REG(LCD,18)
#define LCD_WF19                                 LCD_WF8B_REG(LCD,19)
#define LCD_WF20                                 LCD_WF8B_REG(LCD,20)
#define LCD_WF23TO20                             LCD_WF_REG(LCD,5)
#define LCD_WF21                                 LCD_WF8B_REG(LCD,21)
#define LCD_WF22                                 LCD_WF8B_REG(LCD,22)
#define LCD_WF23                                 LCD_WF8B_REG(LCD,23)
#define LCD_WF24                                 LCD_WF8B_REG(LCD,24)
#define LCD_WF27TO24                             LCD_WF_REG(LCD,6)
#define LCD_WF25                                 LCD_WF8B_REG(LCD,25)
#define LCD_WF26                                 LCD_WF8B_REG(LCD,26)
#define LCD_WF27                                 LCD_WF8B_REG(LCD,27)
#define LCD_WF28                                 LCD_WF8B_REG(LCD,28)
#define LCD_WF31TO28                             LCD_WF_REG(LCD,7)
#define LCD_WF29                                 LCD_WF8B_REG(LCD,29)
#define LCD_WF30                                 LCD_WF8B_REG(LCD,30)
#define LCD_WF31                                 LCD_WF8B_REG(LCD,31)
#define LCD_WF32                                 LCD_WF8B_REG(LCD,32)
#define LCD_WF35TO32                             LCD_WF_REG(LCD,8)
#define LCD_WF33                                 LCD_WF8B_REG(LCD,33)
#define LCD_WF34                                 LCD_WF8B_REG(LCD,34)
#define LCD_WF35                                 LCD_WF8B_REG(LCD,35)
#define LCD_WF36                                 LCD_WF8B_REG(LCD,36)
#define LCD_WF39TO36                             LCD_WF_REG(LCD,9)
#define LCD_WF37                                 LCD_WF8B_REG(LCD,37)
#define LCD_WF38                                 LCD_WF8B_REG(LCD,38)
#define LCD_WF39                                 LCD_WF8B_REG(LCD,39)
#define LCD_WF40                                 LCD_WF8B_REG(LCD,40)
#define LCD_WF43TO40                             LCD_WF_REG(LCD,10)
#define LCD_WF41                                 LCD_WF8B_REG(LCD,41)
#define LCD_WF42                                 LCD_WF8B_REG(LCD,42)
#define LCD_WF43                                 LCD_WF8B_REG(LCD,43)
#define LCD_WF44                                 LCD_WF8B_REG(LCD,44)
#define LCD_WF47TO44                             LCD_WF_REG(LCD,11)
#define LCD_WF45                                 LCD_WF8B_REG(LCD,45)
#define LCD_WF46                                 LCD_WF8B_REG(LCD,46)
#define LCD_WF47                                 LCD_WF8B_REG(LCD,47)
#define LCD_WF48                                 LCD_WF8B_REG(LCD,48)
#define LCD_WF51TO48                             LCD_WF_REG(LCD,12)
#define LCD_WF49                                 LCD_WF8B_REG(LCD,49)
#define LCD_WF50                                 LCD_WF8B_REG(LCD,50)
#define LCD_WF51                                 LCD_WF8B_REG(LCD,51)
#define LCD_WF52                                 LCD_WF8B_REG(LCD,52)
#define LCD_WF55TO52                             LCD_WF_REG(LCD,13)
#define LCD_WF53                                 LCD_WF8B_REG(LCD,53)
#define LCD_WF54                                 LCD_WF8B_REG(LCD,54)
#define LCD_WF55                                 LCD_WF8B_REG(LCD,55)
#define LCD_WF56                                 LCD_WF8B_REG(LCD,56)
#define LCD_WF59TO56                             LCD_WF_REG(LCD,14)
#define LCD_WF57                                 LCD_WF8B_REG(LCD,57)
#define LCD_WF58                                 LCD_WF8B_REG(LCD,58)
#define LCD_WF59                                 LCD_WF8B_REG(LCD,59)
#define LCD_WF60                                 LCD_WF8B_REG(LCD,60)
#define LCD_WF63TO60                             LCD_WF_REG(LCD,15)
#define LCD_WF61                                 LCD_WF8B_REG(LCD,61)
#define LCD_WF62                                 LCD_WF8B_REG(LCD,62)
#define LCD_WF63                                 LCD_WF8B_REG(LCD,63)

/* LCD - Register array accessors */
#define LCD_PEN(index)                           LCD_PEN_REG(LCD,index)
#define LCD_BPEN(index)                          LCD_BPEN_REG(LCD,index)
#define LCD_WF(index2)                           LCD_WF_REG(LCD,index2)
#define LCD_WF8B(index2)                         LCD_WF8B_REG(LCD,index2)

/*!
 * @}
 */ /* end of group LCD_Register_Accessor_Macros */


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
  __IO uint8_t PE5;                                /**< LLWU Pin Enable 5 register, offset: 0x4 */
  __IO uint8_t PE6;                                /**< LLWU Pin Enable 6 register, offset: 0x5 */
       uint8_t RESERVED_0[2];
  __IO uint8_t ME;                                 /**< LLWU Module Enable register, offset: 0x8 */
  __IO uint8_t PF1;                                /**< LLWU Pin Flag 1 register, offset: 0x9 */
  __IO uint8_t PF2;                                /**< LLWU Pin Flag 2 register, offset: 0xA */
  __IO uint8_t PF3;                                /**< LLWU Pin Flag 3 register, offset: 0xB */
       uint8_t RESERVED_1[1];
  __I  uint8_t MF5;                                /**< LLWU Module Flag 5 register, offset: 0xD */
  __IO uint8_t FILT1;                              /**< LLWU Pin Filter 1 register, offset: 0xE */
  __IO uint8_t FILT2;                              /**< LLWU Pin Filter 2 register, offset: 0xF */
} LLWU_Type, *LLWU_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- LLWU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Register_Accessor_Macros LLWU - Register accessor macros
 * @{
 */


/* LLWU - Register accessors */
#define LLWU_PE1_REG(base)                       ((base)->PE1)
#define LLWU_PE2_REG(base)                       ((base)->PE2)
#define LLWU_PE3_REG(base)                       ((base)->PE3)
#define LLWU_PE4_REG(base)                       ((base)->PE4)
#define LLWU_PE5_REG(base)                       ((base)->PE5)
#define LLWU_PE6_REG(base)                       ((base)->PE6)
#define LLWU_ME_REG(base)                        ((base)->ME)
#define LLWU_PF1_REG(base)                       ((base)->PF1)
#define LLWU_PF2_REG(base)                       ((base)->PF2)
#define LLWU_PF3_REG(base)                       ((base)->PF3)
#define LLWU_MF5_REG(base)                       ((base)->MF5)
#define LLWU_FILT1_REG(base)                     ((base)->FILT1)
#define LLWU_FILT2_REG(base)                     ((base)->FILT2)

/*!
 * @}
 */ /* end of group LLWU_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- LLWU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Register_Masks LLWU Register Masks
 * @{
 */

/* PE1 Bit Fields */
#define LLWU_PE1_WUPE0_MASK                      0x3u
#define LLWU_PE1_WUPE0_SHIFT                     0
#define LLWU_PE1_WUPE0_WIDTH                     2
#define LLWU_PE1_WUPE0(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PE1_WUPE0_SHIFT))&LLWU_PE1_WUPE0_MASK)
#define LLWU_PE1_WUPE1_MASK                      0xCu
#define LLWU_PE1_WUPE1_SHIFT                     2
#define LLWU_PE1_WUPE1_WIDTH                     2
#define LLWU_PE1_WUPE1(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PE1_WUPE1_SHIFT))&LLWU_PE1_WUPE1_MASK)
#define LLWU_PE1_WUPE2_MASK                      0x30u
#define LLWU_PE1_WUPE2_SHIFT                     4
#define LLWU_PE1_WUPE2_WIDTH                     2
#define LLWU_PE1_WUPE2(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PE1_WUPE2_SHIFT))&LLWU_PE1_WUPE2_MASK)
#define LLWU_PE1_WUPE3_MASK                      0xC0u
#define LLWU_PE1_WUPE3_SHIFT                     6
#define LLWU_PE1_WUPE3_WIDTH                     2
#define LLWU_PE1_WUPE3(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PE1_WUPE3_SHIFT))&LLWU_PE1_WUPE3_MASK)
/* PE2 Bit Fields */
#define LLWU_PE2_WUPE4_MASK                      0x3u
#define LLWU_PE2_WUPE4_SHIFT                     0
#define LLWU_PE2_WUPE4_WIDTH                     2
#define LLWU_PE2_WUPE4(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PE2_WUPE4_SHIFT))&LLWU_PE2_WUPE4_MASK)
#define LLWU_PE2_WUPE5_MASK                      0xCu
#define LLWU_PE2_WUPE5_SHIFT                     2
#define LLWU_PE2_WUPE5_WIDTH                     2
#define LLWU_PE2_WUPE5(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PE2_WUPE5_SHIFT))&LLWU_PE2_WUPE5_MASK)
#define LLWU_PE2_WUPE6_MASK                      0x30u
#define LLWU_PE2_WUPE6_SHIFT                     4
#define LLWU_PE2_WUPE6_WIDTH                     2
#define LLWU_PE2_WUPE6(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PE2_WUPE6_SHIFT))&LLWU_PE2_WUPE6_MASK)
#define LLWU_PE2_WUPE7_MASK                      0xC0u
#define LLWU_PE2_WUPE7_SHIFT                     6
#define LLWU_PE2_WUPE7_WIDTH                     2
#define LLWU_PE2_WUPE7(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PE2_WUPE7_SHIFT))&LLWU_PE2_WUPE7_MASK)
/* PE3 Bit Fields */
#define LLWU_PE3_WUPE8_MASK                      0x3u
#define LLWU_PE3_WUPE8_SHIFT                     0
#define LLWU_PE3_WUPE8_WIDTH                     2
#define LLWU_PE3_WUPE8(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PE3_WUPE8_SHIFT))&LLWU_PE3_WUPE8_MASK)
#define LLWU_PE3_WUPE9_MASK                      0xCu
#define LLWU_PE3_WUPE9_SHIFT                     2
#define LLWU_PE3_WUPE9_WIDTH                     2
#define LLWU_PE3_WUPE9(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PE3_WUPE9_SHIFT))&LLWU_PE3_WUPE9_MASK)
#define LLWU_PE3_WUPE10_MASK                     0x30u
#define LLWU_PE3_WUPE10_SHIFT                    4
#define LLWU_PE3_WUPE10_WIDTH                    2
#define LLWU_PE3_WUPE10(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE3_WUPE10_SHIFT))&LLWU_PE3_WUPE10_MASK)
#define LLWU_PE3_WUPE11_MASK                     0xC0u
#define LLWU_PE3_WUPE11_SHIFT                    6
#define LLWU_PE3_WUPE11_WIDTH                    2
#define LLWU_PE3_WUPE11(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE3_WUPE11_SHIFT))&LLWU_PE3_WUPE11_MASK)
/* PE4 Bit Fields */
#define LLWU_PE4_WUPE12_MASK                     0x3u
#define LLWU_PE4_WUPE12_SHIFT                    0
#define LLWU_PE4_WUPE12_WIDTH                    2
#define LLWU_PE4_WUPE12(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE4_WUPE12_SHIFT))&LLWU_PE4_WUPE12_MASK)
#define LLWU_PE4_WUPE13_MASK                     0xCu
#define LLWU_PE4_WUPE13_SHIFT                    2
#define LLWU_PE4_WUPE13_WIDTH                    2
#define LLWU_PE4_WUPE13(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE4_WUPE13_SHIFT))&LLWU_PE4_WUPE13_MASK)
#define LLWU_PE4_WUPE14_MASK                     0x30u
#define LLWU_PE4_WUPE14_SHIFT                    4
#define LLWU_PE4_WUPE14_WIDTH                    2
#define LLWU_PE4_WUPE14(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE4_WUPE14_SHIFT))&LLWU_PE4_WUPE14_MASK)
#define LLWU_PE4_WUPE15_MASK                     0xC0u
#define LLWU_PE4_WUPE15_SHIFT                    6
#define LLWU_PE4_WUPE15_WIDTH                    2
#define LLWU_PE4_WUPE15(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE4_WUPE15_SHIFT))&LLWU_PE4_WUPE15_MASK)
/* PE5 Bit Fields */
#define LLWU_PE5_WUPE16_MASK                     0x3u
#define LLWU_PE5_WUPE16_SHIFT                    0
#define LLWU_PE5_WUPE16_WIDTH                    2
#define LLWU_PE5_WUPE16(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE5_WUPE16_SHIFT))&LLWU_PE5_WUPE16_MASK)
#define LLWU_PE5_WUPE17_MASK                     0xCu
#define LLWU_PE5_WUPE17_SHIFT                    2
#define LLWU_PE5_WUPE17_WIDTH                    2
#define LLWU_PE5_WUPE17(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE5_WUPE17_SHIFT))&LLWU_PE5_WUPE17_MASK)
#define LLWU_PE5_WUPE18_MASK                     0x30u
#define LLWU_PE5_WUPE18_SHIFT                    4
#define LLWU_PE5_WUPE18_WIDTH                    2
#define LLWU_PE5_WUPE18(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE5_WUPE18_SHIFT))&LLWU_PE5_WUPE18_MASK)
#define LLWU_PE5_WUPE19_MASK                     0xC0u
#define LLWU_PE5_WUPE19_SHIFT                    6
#define LLWU_PE5_WUPE19_WIDTH                    2
#define LLWU_PE5_WUPE19(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE5_WUPE19_SHIFT))&LLWU_PE5_WUPE19_MASK)
/* PE6 Bit Fields */
#define LLWU_PE6_WUPE20_MASK                     0x3u
#define LLWU_PE6_WUPE20_SHIFT                    0
#define LLWU_PE6_WUPE20_WIDTH                    2
#define LLWU_PE6_WUPE20(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE6_WUPE20_SHIFT))&LLWU_PE6_WUPE20_MASK)
#define LLWU_PE6_WUPE21_MASK                     0xCu
#define LLWU_PE6_WUPE21_SHIFT                    2
#define LLWU_PE6_WUPE21_WIDTH                    2
#define LLWU_PE6_WUPE21(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE6_WUPE21_SHIFT))&LLWU_PE6_WUPE21_MASK)
#define LLWU_PE6_WUPE22_MASK                     0x30u
#define LLWU_PE6_WUPE22_SHIFT                    4
#define LLWU_PE6_WUPE22_WIDTH                    2
#define LLWU_PE6_WUPE22(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE6_WUPE22_SHIFT))&LLWU_PE6_WUPE22_MASK)
#define LLWU_PE6_WUPE23_MASK                     0xC0u
#define LLWU_PE6_WUPE23_SHIFT                    6
#define LLWU_PE6_WUPE23_WIDTH                    2
#define LLWU_PE6_WUPE23(x)                       (((uint8_t)(((uint8_t)(x))<<LLWU_PE6_WUPE23_SHIFT))&LLWU_PE6_WUPE23_MASK)
/* ME Bit Fields */
#define LLWU_ME_WUME0_MASK                       0x1u
#define LLWU_ME_WUME0_SHIFT                      0
#define LLWU_ME_WUME0_WIDTH                      1
#define LLWU_ME_WUME0(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_ME_WUME0_SHIFT))&LLWU_ME_WUME0_MASK)
#define LLWU_ME_WUME1_MASK                       0x2u
#define LLWU_ME_WUME1_SHIFT                      1
#define LLWU_ME_WUME1_WIDTH                      1
#define LLWU_ME_WUME1(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_ME_WUME1_SHIFT))&LLWU_ME_WUME1_MASK)
#define LLWU_ME_WUME2_MASK                       0x4u
#define LLWU_ME_WUME2_SHIFT                      2
#define LLWU_ME_WUME2_WIDTH                      1
#define LLWU_ME_WUME2(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_ME_WUME2_SHIFT))&LLWU_ME_WUME2_MASK)
#define LLWU_ME_WUME3_MASK                       0x8u
#define LLWU_ME_WUME3_SHIFT                      3
#define LLWU_ME_WUME3_WIDTH                      1
#define LLWU_ME_WUME3(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_ME_WUME3_SHIFT))&LLWU_ME_WUME3_MASK)
#define LLWU_ME_WUME4_MASK                       0x10u
#define LLWU_ME_WUME4_SHIFT                      4
#define LLWU_ME_WUME4_WIDTH                      1
#define LLWU_ME_WUME4(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_ME_WUME4_SHIFT))&LLWU_ME_WUME4_MASK)
#define LLWU_ME_WUME5_MASK                       0x20u
#define LLWU_ME_WUME5_SHIFT                      5
#define LLWU_ME_WUME5_WIDTH                      1
#define LLWU_ME_WUME5(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_ME_WUME5_SHIFT))&LLWU_ME_WUME5_MASK)
#define LLWU_ME_WUME6_MASK                       0x40u
#define LLWU_ME_WUME6_SHIFT                      6
#define LLWU_ME_WUME6_WIDTH                      1
#define LLWU_ME_WUME6(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_ME_WUME6_SHIFT))&LLWU_ME_WUME6_MASK)
#define LLWU_ME_WUME7_MASK                       0x80u
#define LLWU_ME_WUME7_SHIFT                      7
#define LLWU_ME_WUME7_WIDTH                      1
#define LLWU_ME_WUME7(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_ME_WUME7_SHIFT))&LLWU_ME_WUME7_MASK)
/* PF1 Bit Fields */
#define LLWU_PF1_WUF0_MASK                       0x1u
#define LLWU_PF1_WUF0_SHIFT                      0
#define LLWU_PF1_WUF0_WIDTH                      1
#define LLWU_PF1_WUF0(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_PF1_WUF0_SHIFT))&LLWU_PF1_WUF0_MASK)
#define LLWU_PF1_WUF1_MASK                       0x2u
#define LLWU_PF1_WUF1_SHIFT                      1
#define LLWU_PF1_WUF1_WIDTH                      1
#define LLWU_PF1_WUF1(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_PF1_WUF1_SHIFT))&LLWU_PF1_WUF1_MASK)
#define LLWU_PF1_WUF2_MASK                       0x4u
#define LLWU_PF1_WUF2_SHIFT                      2
#define LLWU_PF1_WUF2_WIDTH                      1
#define LLWU_PF1_WUF2(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_PF1_WUF2_SHIFT))&LLWU_PF1_WUF2_MASK)
#define LLWU_PF1_WUF3_MASK                       0x8u
#define LLWU_PF1_WUF3_SHIFT                      3
#define LLWU_PF1_WUF3_WIDTH                      1
#define LLWU_PF1_WUF3(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_PF1_WUF3_SHIFT))&LLWU_PF1_WUF3_MASK)
#define LLWU_PF1_WUF4_MASK                       0x10u
#define LLWU_PF1_WUF4_SHIFT                      4
#define LLWU_PF1_WUF4_WIDTH                      1
#define LLWU_PF1_WUF4(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_PF1_WUF4_SHIFT))&LLWU_PF1_WUF4_MASK)
#define LLWU_PF1_WUF5_MASK                       0x20u
#define LLWU_PF1_WUF5_SHIFT                      5
#define LLWU_PF1_WUF5_WIDTH                      1
#define LLWU_PF1_WUF5(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_PF1_WUF5_SHIFT))&LLWU_PF1_WUF5_MASK)
#define LLWU_PF1_WUF6_MASK                       0x40u
#define LLWU_PF1_WUF6_SHIFT                      6
#define LLWU_PF1_WUF6_WIDTH                      1
#define LLWU_PF1_WUF6(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_PF1_WUF6_SHIFT))&LLWU_PF1_WUF6_MASK)
#define LLWU_PF1_WUF7_MASK                       0x80u
#define LLWU_PF1_WUF7_SHIFT                      7
#define LLWU_PF1_WUF7_WIDTH                      1
#define LLWU_PF1_WUF7(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_PF1_WUF7_SHIFT))&LLWU_PF1_WUF7_MASK)
/* PF2 Bit Fields */
#define LLWU_PF2_WUF8_MASK                       0x1u
#define LLWU_PF2_WUF8_SHIFT                      0
#define LLWU_PF2_WUF8_WIDTH                      1
#define LLWU_PF2_WUF8(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_PF2_WUF8_SHIFT))&LLWU_PF2_WUF8_MASK)
#define LLWU_PF2_WUF9_MASK                       0x2u
#define LLWU_PF2_WUF9_SHIFT                      1
#define LLWU_PF2_WUF9_WIDTH                      1
#define LLWU_PF2_WUF9(x)                         (((uint8_t)(((uint8_t)(x))<<LLWU_PF2_WUF9_SHIFT))&LLWU_PF2_WUF9_MASK)
#define LLWU_PF2_WUF10_MASK                      0x4u
#define LLWU_PF2_WUF10_SHIFT                     2
#define LLWU_PF2_WUF10_WIDTH                     1
#define LLWU_PF2_WUF10(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF2_WUF10_SHIFT))&LLWU_PF2_WUF10_MASK)
#define LLWU_PF2_WUF11_MASK                      0x8u
#define LLWU_PF2_WUF11_SHIFT                     3
#define LLWU_PF2_WUF11_WIDTH                     1
#define LLWU_PF2_WUF11(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF2_WUF11_SHIFT))&LLWU_PF2_WUF11_MASK)
#define LLWU_PF2_WUF12_MASK                      0x10u
#define LLWU_PF2_WUF12_SHIFT                     4
#define LLWU_PF2_WUF12_WIDTH                     1
#define LLWU_PF2_WUF12(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF2_WUF12_SHIFT))&LLWU_PF2_WUF12_MASK)
#define LLWU_PF2_WUF13_MASK                      0x20u
#define LLWU_PF2_WUF13_SHIFT                     5
#define LLWU_PF2_WUF13_WIDTH                     1
#define LLWU_PF2_WUF13(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF2_WUF13_SHIFT))&LLWU_PF2_WUF13_MASK)
#define LLWU_PF2_WUF14_MASK                      0x40u
#define LLWU_PF2_WUF14_SHIFT                     6
#define LLWU_PF2_WUF14_WIDTH                     1
#define LLWU_PF2_WUF14(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF2_WUF14_SHIFT))&LLWU_PF2_WUF14_MASK)
#define LLWU_PF2_WUF15_MASK                      0x80u
#define LLWU_PF2_WUF15_SHIFT                     7
#define LLWU_PF2_WUF15_WIDTH                     1
#define LLWU_PF2_WUF15(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF2_WUF15_SHIFT))&LLWU_PF2_WUF15_MASK)
/* PF3 Bit Fields */
#define LLWU_PF3_WUF16_MASK                      0x1u
#define LLWU_PF3_WUF16_SHIFT                     0
#define LLWU_PF3_WUF16_WIDTH                     1
#define LLWU_PF3_WUF16(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF3_WUF16_SHIFT))&LLWU_PF3_WUF16_MASK)
#define LLWU_PF3_WUF17_MASK                      0x2u
#define LLWU_PF3_WUF17_SHIFT                     1
#define LLWU_PF3_WUF17_WIDTH                     1
#define LLWU_PF3_WUF17(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF3_WUF17_SHIFT))&LLWU_PF3_WUF17_MASK)
#define LLWU_PF3_WUF18_MASK                      0x4u
#define LLWU_PF3_WUF18_SHIFT                     2
#define LLWU_PF3_WUF18_WIDTH                     1
#define LLWU_PF3_WUF18(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF3_WUF18_SHIFT))&LLWU_PF3_WUF18_MASK)
#define LLWU_PF3_WUF19_MASK                      0x8u
#define LLWU_PF3_WUF19_SHIFT                     3
#define LLWU_PF3_WUF19_WIDTH                     1
#define LLWU_PF3_WUF19(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF3_WUF19_SHIFT))&LLWU_PF3_WUF19_MASK)
#define LLWU_PF3_WUF20_MASK                      0x10u
#define LLWU_PF3_WUF20_SHIFT                     4
#define LLWU_PF3_WUF20_WIDTH                     1
#define LLWU_PF3_WUF20(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF3_WUF20_SHIFT))&LLWU_PF3_WUF20_MASK)
#define LLWU_PF3_WUF21_MASK                      0x20u
#define LLWU_PF3_WUF21_SHIFT                     5
#define LLWU_PF3_WUF21_WIDTH                     1
#define LLWU_PF3_WUF21(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF3_WUF21_SHIFT))&LLWU_PF3_WUF21_MASK)
#define LLWU_PF3_WUF22_MASK                      0x40u
#define LLWU_PF3_WUF22_SHIFT                     6
#define LLWU_PF3_WUF22_WIDTH                     1
#define LLWU_PF3_WUF22(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF3_WUF22_SHIFT))&LLWU_PF3_WUF22_MASK)
#define LLWU_PF3_WUF23_MASK                      0x80u
#define LLWU_PF3_WUF23_SHIFT                     7
#define LLWU_PF3_WUF23_WIDTH                     1
#define LLWU_PF3_WUF23(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_PF3_WUF23_SHIFT))&LLWU_PF3_WUF23_MASK)
/* MF5 Bit Fields */
#define LLWU_MF5_MWUF0_MASK                      0x1u
#define LLWU_MF5_MWUF0_SHIFT                     0
#define LLWU_MF5_MWUF0_WIDTH                     1
#define LLWU_MF5_MWUF0(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_MF5_MWUF0_SHIFT))&LLWU_MF5_MWUF0_MASK)
#define LLWU_MF5_MWUF1_MASK                      0x2u
#define LLWU_MF5_MWUF1_SHIFT                     1
#define LLWU_MF5_MWUF1_WIDTH                     1
#define LLWU_MF5_MWUF1(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_MF5_MWUF1_SHIFT))&LLWU_MF5_MWUF1_MASK)
#define LLWU_MF5_MWUF2_MASK                      0x4u
#define LLWU_MF5_MWUF2_SHIFT                     2
#define LLWU_MF5_MWUF2_WIDTH                     1
#define LLWU_MF5_MWUF2(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_MF5_MWUF2_SHIFT))&LLWU_MF5_MWUF2_MASK)
#define LLWU_MF5_MWUF3_MASK                      0x8u
#define LLWU_MF5_MWUF3_SHIFT                     3
#define LLWU_MF5_MWUF3_WIDTH                     1
#define LLWU_MF5_MWUF3(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_MF5_MWUF3_SHIFT))&LLWU_MF5_MWUF3_MASK)
#define LLWU_MF5_MWUF4_MASK                      0x10u
#define LLWU_MF5_MWUF4_SHIFT                     4
#define LLWU_MF5_MWUF4_WIDTH                     1
#define LLWU_MF5_MWUF4(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_MF5_MWUF4_SHIFT))&LLWU_MF5_MWUF4_MASK)
#define LLWU_MF5_MWUF5_MASK                      0x20u
#define LLWU_MF5_MWUF5_SHIFT                     5
#define LLWU_MF5_MWUF5_WIDTH                     1
#define LLWU_MF5_MWUF5(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_MF5_MWUF5_SHIFT))&LLWU_MF5_MWUF5_MASK)
#define LLWU_MF5_MWUF6_MASK                      0x40u
#define LLWU_MF5_MWUF6_SHIFT                     6
#define LLWU_MF5_MWUF6_WIDTH                     1
#define LLWU_MF5_MWUF6(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_MF5_MWUF6_SHIFT))&LLWU_MF5_MWUF6_MASK)
#define LLWU_MF5_MWUF7_MASK                      0x80u
#define LLWU_MF5_MWUF7_SHIFT                     7
#define LLWU_MF5_MWUF7_WIDTH                     1
#define LLWU_MF5_MWUF7(x)                        (((uint8_t)(((uint8_t)(x))<<LLWU_MF5_MWUF7_SHIFT))&LLWU_MF5_MWUF7_MASK)
/* FILT1 Bit Fields */
#define LLWU_FILT1_FILTSEL_MASK                  0x1Fu
#define LLWU_FILT1_FILTSEL_SHIFT                 0
#define LLWU_FILT1_FILTSEL_WIDTH                 5
#define LLWU_FILT1_FILTSEL(x)                    (((uint8_t)(((uint8_t)(x))<<LLWU_FILT1_FILTSEL_SHIFT))&LLWU_FILT1_FILTSEL_MASK)
#define LLWU_FILT1_FILTE_MASK                    0x60u
#define LLWU_FILT1_FILTE_SHIFT                   5
#define LLWU_FILT1_FILTE_WIDTH                   2
#define LLWU_FILT1_FILTE(x)                      (((uint8_t)(((uint8_t)(x))<<LLWU_FILT1_FILTE_SHIFT))&LLWU_FILT1_FILTE_MASK)
#define LLWU_FILT1_FILTF_MASK                    0x80u
#define LLWU_FILT1_FILTF_SHIFT                   7
#define LLWU_FILT1_FILTF_WIDTH                   1
#define LLWU_FILT1_FILTF(x)                      (((uint8_t)(((uint8_t)(x))<<LLWU_FILT1_FILTF_SHIFT))&LLWU_FILT1_FILTF_MASK)
/* FILT2 Bit Fields */
#define LLWU_FILT2_FILTSEL_MASK                  0x1Fu
#define LLWU_FILT2_FILTSEL_SHIFT                 0
#define LLWU_FILT2_FILTSEL_WIDTH                 5
#define LLWU_FILT2_FILTSEL(x)                    (((uint8_t)(((uint8_t)(x))<<LLWU_FILT2_FILTSEL_SHIFT))&LLWU_FILT2_FILTSEL_MASK)
#define LLWU_FILT2_FILTE_MASK                    0x60u
#define LLWU_FILT2_FILTE_SHIFT                   5
#define LLWU_FILT2_FILTE_WIDTH                   2
#define LLWU_FILT2_FILTE(x)                      (((uint8_t)(((uint8_t)(x))<<LLWU_FILT2_FILTE_SHIFT))&LLWU_FILT2_FILTE_MASK)
#define LLWU_FILT2_FILTF_MASK                    0x80u
#define LLWU_FILT2_FILTF_SHIFT                   7
#define LLWU_FILT2_FILTF_WIDTH                   1
#define LLWU_FILT2_FILTF(x)                      (((uint8_t)(((uint8_t)(x))<<LLWU_FILT2_FILTF_SHIFT))&LLWU_FILT2_FILTF_MASK)

/*!
 * @}
 */ /* end of group LLWU_Register_Masks */


/* LLWU - Peripheral instance base addresses */
/** Peripheral LLWU base address */
#define LLWU_BASE                                (0x4007C000u)
/** Peripheral LLWU base pointer */
#define LLWU                                     ((LLWU_Type *)LLWU_BASE)
#define LLWU_BASE_PTR                            (LLWU)
/** Array initializer of LLWU peripheral base addresses */
#define LLWU_BASE_ADDRS                          { LLWU_BASE }
/** Array initializer of LLWU peripheral base pointers */
#define LLWU_BASE_PTRS                           { LLWU }
/** Interrupt vectors for the LLWU peripheral type */
#define LLWU_IRQS                                { LLWU_IRQn }

/* ----------------------------------------------------------------------------
   -- LLWU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Register_Accessor_Macros LLWU - Register accessor macros
 * @{
 */


/* LLWU - Register instance definitions */
/* LLWU */
#define LLWU_PE1                                 LLWU_PE1_REG(LLWU)
#define LLWU_PE2                                 LLWU_PE2_REG(LLWU)
#define LLWU_PE3                                 LLWU_PE3_REG(LLWU)
#define LLWU_PE4                                 LLWU_PE4_REG(LLWU)
#define LLWU_PE5                                 LLWU_PE5_REG(LLWU)
#define LLWU_PE6                                 LLWU_PE6_REG(LLWU)
#define LLWU_ME                                  LLWU_ME_REG(LLWU)
#define LLWU_PF1                                 LLWU_PF1_REG(LLWU)
#define LLWU_PF2                                 LLWU_PF2_REG(LLWU)
#define LLWU_PF3                                 LLWU_PF3_REG(LLWU)
#define LLWU_MF5                                 LLWU_MF5_REG(LLWU)
#define LLWU_FILT1                               LLWU_FILT1_REG(LLWU)
#define LLWU_FILT2                               LLWU_FILT2_REG(LLWU)

/*!
 * @}
 */ /* end of group LLWU_Register_Accessor_Macros */


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
} LPTMR_Type, *LPTMR_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- LPTMR - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Register_Accessor_Macros LPTMR - Register accessor macros
 * @{
 */


/* LPTMR - Register accessors */
#define LPTMR_CSR_REG(base)                      ((base)->CSR)
#define LPTMR_PSR_REG(base)                      ((base)->PSR)
#define LPTMR_CMR_REG(base)                      ((base)->CMR)
#define LPTMR_CNR_REG(base)                      ((base)->CNR)

/*!
 * @}
 */ /* end of group LPTMR_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- LPTMR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Register_Masks LPTMR Register Masks
 * @{
 */

/* CSR Bit Fields */
#define LPTMR_CSR_TEN_MASK                       0x1u
#define LPTMR_CSR_TEN_SHIFT                      0
#define LPTMR_CSR_TEN_WIDTH                      1
#define LPTMR_CSR_TEN(x)                         (((uint32_t)(((uint32_t)(x))<<LPTMR_CSR_TEN_SHIFT))&LPTMR_CSR_TEN_MASK)
#define LPTMR_CSR_TMS_MASK                       0x2u
#define LPTMR_CSR_TMS_SHIFT                      1
#define LPTMR_CSR_TMS_WIDTH                      1
#define LPTMR_CSR_TMS(x)                         (((uint32_t)(((uint32_t)(x))<<LPTMR_CSR_TMS_SHIFT))&LPTMR_CSR_TMS_MASK)
#define LPTMR_CSR_TFC_MASK                       0x4u
#define LPTMR_CSR_TFC_SHIFT                      2
#define LPTMR_CSR_TFC_WIDTH                      1
#define LPTMR_CSR_TFC(x)                         (((uint32_t)(((uint32_t)(x))<<LPTMR_CSR_TFC_SHIFT))&LPTMR_CSR_TFC_MASK)
#define LPTMR_CSR_TPP_MASK                       0x8u
#define LPTMR_CSR_TPP_SHIFT                      3
#define LPTMR_CSR_TPP_WIDTH                      1
#define LPTMR_CSR_TPP(x)                         (((uint32_t)(((uint32_t)(x))<<LPTMR_CSR_TPP_SHIFT))&LPTMR_CSR_TPP_MASK)
#define LPTMR_CSR_TPS_MASK                       0x30u
#define LPTMR_CSR_TPS_SHIFT                      4
#define LPTMR_CSR_TPS_WIDTH                      2
#define LPTMR_CSR_TPS(x)                         (((uint32_t)(((uint32_t)(x))<<LPTMR_CSR_TPS_SHIFT))&LPTMR_CSR_TPS_MASK)
#define LPTMR_CSR_TIE_MASK                       0x40u
#define LPTMR_CSR_TIE_SHIFT                      6
#define LPTMR_CSR_TIE_WIDTH                      1
#define LPTMR_CSR_TIE(x)                         (((uint32_t)(((uint32_t)(x))<<LPTMR_CSR_TIE_SHIFT))&LPTMR_CSR_TIE_MASK)
#define LPTMR_CSR_TCF_MASK                       0x80u
#define LPTMR_CSR_TCF_SHIFT                      7
#define LPTMR_CSR_TCF_WIDTH                      1
#define LPTMR_CSR_TCF(x)                         (((uint32_t)(((uint32_t)(x))<<LPTMR_CSR_TCF_SHIFT))&LPTMR_CSR_TCF_MASK)
/* PSR Bit Fields */
#define LPTMR_PSR_PCS_MASK                       0x3u
#define LPTMR_PSR_PCS_SHIFT                      0
#define LPTMR_PSR_PCS_WIDTH                      2
#define LPTMR_PSR_PCS(x)                         (((uint32_t)(((uint32_t)(x))<<LPTMR_PSR_PCS_SHIFT))&LPTMR_PSR_PCS_MASK)
#define LPTMR_PSR_PBYP_MASK                      0x4u
#define LPTMR_PSR_PBYP_SHIFT                     2
#define LPTMR_PSR_PBYP_WIDTH                     1
#define LPTMR_PSR_PBYP(x)                        (((uint32_t)(((uint32_t)(x))<<LPTMR_PSR_PBYP_SHIFT))&LPTMR_PSR_PBYP_MASK)
#define LPTMR_PSR_PRESCALE_MASK                  0x78u
#define LPTMR_PSR_PRESCALE_SHIFT                 3
#define LPTMR_PSR_PRESCALE_WIDTH                 4
#define LPTMR_PSR_PRESCALE(x)                    (((uint32_t)(((uint32_t)(x))<<LPTMR_PSR_PRESCALE_SHIFT))&LPTMR_PSR_PRESCALE_MASK)
/* CMR Bit Fields */
#define LPTMR_CMR_COMPARE_MASK                   0xFFFFu
#define LPTMR_CMR_COMPARE_SHIFT                  0
#define LPTMR_CMR_COMPARE_WIDTH                  16
#define LPTMR_CMR_COMPARE(x)                     (((uint32_t)(((uint32_t)(x))<<LPTMR_CMR_COMPARE_SHIFT))&LPTMR_CMR_COMPARE_MASK)
/* CNR Bit Fields */
#define LPTMR_CNR_COUNTER_MASK                   0xFFFFu
#define LPTMR_CNR_COUNTER_SHIFT                  0
#define LPTMR_CNR_COUNTER_WIDTH                  16
#define LPTMR_CNR_COUNTER(x)                     (((uint32_t)(((uint32_t)(x))<<LPTMR_CNR_COUNTER_SHIFT))&LPTMR_CNR_COUNTER_MASK)

/*!
 * @}
 */ /* end of group LPTMR_Register_Masks */


/* LPTMR - Peripheral instance base addresses */
/** Peripheral LPTMR0 base address */
#define LPTMR0_BASE                              (0x4003C000u)
/** Peripheral LPTMR0 base pointer */
#define LPTMR0                                   ((LPTMR_Type *)LPTMR0_BASE)
#define LPTMR0_BASE_PTR                          (LPTMR0)
/** Array initializer of LPTMR peripheral base addresses */
#define LPTMR_BASE_ADDRS                         { LPTMR0_BASE }
/** Array initializer of LPTMR peripheral base pointers */
#define LPTMR_BASE_PTRS                          { LPTMR0 }
/** Interrupt vectors for the LPTMR peripheral type */
#define LPTMR_IRQS                               { LPTMR0_IRQn }

/* ----------------------------------------------------------------------------
   -- LPTMR - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Register_Accessor_Macros LPTMR - Register accessor macros
 * @{
 */


/* LPTMR - Register instance definitions */
/* LPTMR0 */
#define LPTMR_CSR                                LPTMR_CSR_REG(LPTMR0)
#define LPTMR_PSR                                LPTMR_PSR_REG(LPTMR0)
#define LPTMR_CMR                                LPTMR_CMR_REG(LPTMR0)
#define LPTMR_CNR                                LPTMR_CNR_REG(LPTMR0)

/*!
 * @}
 */ /* end of group LPTMR_Register_Accessor_Macros */


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
  __IO uint32_t MODIR;                             /**< LPUART Modem IrDA Register, offset: 0x14 */
} LPUART_Type, *LPUART_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- LPUART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPUART_Register_Accessor_Macros LPUART - Register accessor macros
 * @{
 */


/* LPUART - Register accessors */
#define LPUART_BAUD_REG(base)                    ((base)->BAUD)
#define LPUART_STAT_REG(base)                    ((base)->STAT)
#define LPUART_CTRL_REG(base)                    ((base)->CTRL)
#define LPUART_DATA_REG(base)                    ((base)->DATA)
#define LPUART_MATCH_REG(base)                   ((base)->MATCH)
#define LPUART_MODIR_REG(base)                   ((base)->MODIR)

/*!
 * @}
 */ /* end of group LPUART_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- LPUART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPUART_Register_Masks LPUART Register Masks
 * @{
 */

/* BAUD Bit Fields */
#define LPUART_BAUD_SBR_MASK                     0x1FFFu
#define LPUART_BAUD_SBR_SHIFT                    0
#define LPUART_BAUD_SBR_WIDTH                    13
#define LPUART_BAUD_SBR(x)                       (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_SBR_SHIFT))&LPUART_BAUD_SBR_MASK)
#define LPUART_BAUD_SBNS_MASK                    0x2000u
#define LPUART_BAUD_SBNS_SHIFT                   13
#define LPUART_BAUD_SBNS_WIDTH                   1
#define LPUART_BAUD_SBNS(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_SBNS_SHIFT))&LPUART_BAUD_SBNS_MASK)
#define LPUART_BAUD_RXEDGIE_MASK                 0x4000u
#define LPUART_BAUD_RXEDGIE_SHIFT                14
#define LPUART_BAUD_RXEDGIE_WIDTH                1
#define LPUART_BAUD_RXEDGIE(x)                   (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_RXEDGIE_SHIFT))&LPUART_BAUD_RXEDGIE_MASK)
#define LPUART_BAUD_LBKDIE_MASK                  0x8000u
#define LPUART_BAUD_LBKDIE_SHIFT                 15
#define LPUART_BAUD_LBKDIE_WIDTH                 1
#define LPUART_BAUD_LBKDIE(x)                    (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_LBKDIE_SHIFT))&LPUART_BAUD_LBKDIE_MASK)
#define LPUART_BAUD_RESYNCDIS_MASK               0x10000u
#define LPUART_BAUD_RESYNCDIS_SHIFT              16
#define LPUART_BAUD_RESYNCDIS_WIDTH              1
#define LPUART_BAUD_RESYNCDIS(x)                 (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_RESYNCDIS_SHIFT))&LPUART_BAUD_RESYNCDIS_MASK)
#define LPUART_BAUD_BOTHEDGE_MASK                0x20000u
#define LPUART_BAUD_BOTHEDGE_SHIFT               17
#define LPUART_BAUD_BOTHEDGE_WIDTH               1
#define LPUART_BAUD_BOTHEDGE(x)                  (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_BOTHEDGE_SHIFT))&LPUART_BAUD_BOTHEDGE_MASK)
#define LPUART_BAUD_MATCFG_MASK                  0xC0000u
#define LPUART_BAUD_MATCFG_SHIFT                 18
#define LPUART_BAUD_MATCFG_WIDTH                 2
#define LPUART_BAUD_MATCFG(x)                    (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_MATCFG_SHIFT))&LPUART_BAUD_MATCFG_MASK)
#define LPUART_BAUD_RDMAE_MASK                   0x200000u
#define LPUART_BAUD_RDMAE_SHIFT                  21
#define LPUART_BAUD_RDMAE_WIDTH                  1
#define LPUART_BAUD_RDMAE(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_RDMAE_SHIFT))&LPUART_BAUD_RDMAE_MASK)
#define LPUART_BAUD_TDMAE_MASK                   0x800000u
#define LPUART_BAUD_TDMAE_SHIFT                  23
#define LPUART_BAUD_TDMAE_WIDTH                  1
#define LPUART_BAUD_TDMAE(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_TDMAE_SHIFT))&LPUART_BAUD_TDMAE_MASK)
#define LPUART_BAUD_OSR_MASK                     0x1F000000u
#define LPUART_BAUD_OSR_SHIFT                    24
#define LPUART_BAUD_OSR_WIDTH                    5
#define LPUART_BAUD_OSR(x)                       (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_OSR_SHIFT))&LPUART_BAUD_OSR_MASK)
#define LPUART_BAUD_M10_MASK                     0x20000000u
#define LPUART_BAUD_M10_SHIFT                    29
#define LPUART_BAUD_M10_WIDTH                    1
#define LPUART_BAUD_M10(x)                       (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_M10_SHIFT))&LPUART_BAUD_M10_MASK)
#define LPUART_BAUD_MAEN2_MASK                   0x40000000u
#define LPUART_BAUD_MAEN2_SHIFT                  30
#define LPUART_BAUD_MAEN2_WIDTH                  1
#define LPUART_BAUD_MAEN2(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_MAEN2_SHIFT))&LPUART_BAUD_MAEN2_MASK)
#define LPUART_BAUD_MAEN1_MASK                   0x80000000u
#define LPUART_BAUD_MAEN1_SHIFT                  31
#define LPUART_BAUD_MAEN1_WIDTH                  1
#define LPUART_BAUD_MAEN1(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_MAEN1_SHIFT))&LPUART_BAUD_MAEN1_MASK)
/* STAT Bit Fields */
#define LPUART_STAT_MA2F_MASK                    0x4000u
#define LPUART_STAT_MA2F_SHIFT                   14
#define LPUART_STAT_MA2F_WIDTH                   1
#define LPUART_STAT_MA2F(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_MA2F_SHIFT))&LPUART_STAT_MA2F_MASK)
#define LPUART_STAT_MA1F_MASK                    0x8000u
#define LPUART_STAT_MA1F_SHIFT                   15
#define LPUART_STAT_MA1F_WIDTH                   1
#define LPUART_STAT_MA1F(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_MA1F_SHIFT))&LPUART_STAT_MA1F_MASK)
#define LPUART_STAT_PF_MASK                      0x10000u
#define LPUART_STAT_PF_SHIFT                     16
#define LPUART_STAT_PF_WIDTH                     1
#define LPUART_STAT_PF(x)                        (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_PF_SHIFT))&LPUART_STAT_PF_MASK)
#define LPUART_STAT_FE_MASK                      0x20000u
#define LPUART_STAT_FE_SHIFT                     17
#define LPUART_STAT_FE_WIDTH                     1
#define LPUART_STAT_FE(x)                        (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_FE_SHIFT))&LPUART_STAT_FE_MASK)
#define LPUART_STAT_NF_MASK                      0x40000u
#define LPUART_STAT_NF_SHIFT                     18
#define LPUART_STAT_NF_WIDTH                     1
#define LPUART_STAT_NF(x)                        (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_NF_SHIFT))&LPUART_STAT_NF_MASK)
#define LPUART_STAT_OR_MASK                      0x80000u
#define LPUART_STAT_OR_SHIFT                     19
#define LPUART_STAT_OR_WIDTH                     1
#define LPUART_STAT_OR(x)                        (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_OR_SHIFT))&LPUART_STAT_OR_MASK)
#define LPUART_STAT_IDLE_MASK                    0x100000u
#define LPUART_STAT_IDLE_SHIFT                   20
#define LPUART_STAT_IDLE_WIDTH                   1
#define LPUART_STAT_IDLE(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_IDLE_SHIFT))&LPUART_STAT_IDLE_MASK)
#define LPUART_STAT_RDRF_MASK                    0x200000u
#define LPUART_STAT_RDRF_SHIFT                   21
#define LPUART_STAT_RDRF_WIDTH                   1
#define LPUART_STAT_RDRF(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_RDRF_SHIFT))&LPUART_STAT_RDRF_MASK)
#define LPUART_STAT_TC_MASK                      0x400000u
#define LPUART_STAT_TC_SHIFT                     22
#define LPUART_STAT_TC_WIDTH                     1
#define LPUART_STAT_TC(x)                        (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_TC_SHIFT))&LPUART_STAT_TC_MASK)
#define LPUART_STAT_TDRE_MASK                    0x800000u
#define LPUART_STAT_TDRE_SHIFT                   23
#define LPUART_STAT_TDRE_WIDTH                   1
#define LPUART_STAT_TDRE(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_TDRE_SHIFT))&LPUART_STAT_TDRE_MASK)
#define LPUART_STAT_RAF_MASK                     0x1000000u
#define LPUART_STAT_RAF_SHIFT                    24
#define LPUART_STAT_RAF_WIDTH                    1
#define LPUART_STAT_RAF(x)                       (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_RAF_SHIFT))&LPUART_STAT_RAF_MASK)
#define LPUART_STAT_LBKDE_MASK                   0x2000000u
#define LPUART_STAT_LBKDE_SHIFT                  25
#define LPUART_STAT_LBKDE_WIDTH                  1
#define LPUART_STAT_LBKDE(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_LBKDE_SHIFT))&LPUART_STAT_LBKDE_MASK)
#define LPUART_STAT_BRK13_MASK                   0x4000000u
#define LPUART_STAT_BRK13_SHIFT                  26
#define LPUART_STAT_BRK13_WIDTH                  1
#define LPUART_STAT_BRK13(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_BRK13_SHIFT))&LPUART_STAT_BRK13_MASK)
#define LPUART_STAT_RWUID_MASK                   0x8000000u
#define LPUART_STAT_RWUID_SHIFT                  27
#define LPUART_STAT_RWUID_WIDTH                  1
#define LPUART_STAT_RWUID(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_RWUID_SHIFT))&LPUART_STAT_RWUID_MASK)
#define LPUART_STAT_RXINV_MASK                   0x10000000u
#define LPUART_STAT_RXINV_SHIFT                  28
#define LPUART_STAT_RXINV_WIDTH                  1
#define LPUART_STAT_RXINV(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_RXINV_SHIFT))&LPUART_STAT_RXINV_MASK)
#define LPUART_STAT_MSBF_MASK                    0x20000000u
#define LPUART_STAT_MSBF_SHIFT                   29
#define LPUART_STAT_MSBF_WIDTH                   1
#define LPUART_STAT_MSBF(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_MSBF_SHIFT))&LPUART_STAT_MSBF_MASK)
#define LPUART_STAT_RXEDGIF_MASK                 0x40000000u
#define LPUART_STAT_RXEDGIF_SHIFT                30
#define LPUART_STAT_RXEDGIF_WIDTH                1
#define LPUART_STAT_RXEDGIF(x)                   (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_RXEDGIF_SHIFT))&LPUART_STAT_RXEDGIF_MASK)
#define LPUART_STAT_LBKDIF_MASK                  0x80000000u
#define LPUART_STAT_LBKDIF_SHIFT                 31
#define LPUART_STAT_LBKDIF_WIDTH                 1
#define LPUART_STAT_LBKDIF(x)                    (((uint32_t)(((uint32_t)(x))<<LPUART_STAT_LBKDIF_SHIFT))&LPUART_STAT_LBKDIF_MASK)
/* CTRL Bit Fields */
#define LPUART_CTRL_PT_MASK                      0x1u
#define LPUART_CTRL_PT_SHIFT                     0
#define LPUART_CTRL_PT_WIDTH                     1
#define LPUART_CTRL_PT(x)                        (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_PT_SHIFT))&LPUART_CTRL_PT_MASK)
#define LPUART_CTRL_PE_MASK                      0x2u
#define LPUART_CTRL_PE_SHIFT                     1
#define LPUART_CTRL_PE_WIDTH                     1
#define LPUART_CTRL_PE(x)                        (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_PE_SHIFT))&LPUART_CTRL_PE_MASK)
#define LPUART_CTRL_ILT_MASK                     0x4u
#define LPUART_CTRL_ILT_SHIFT                    2
#define LPUART_CTRL_ILT_WIDTH                    1
#define LPUART_CTRL_ILT(x)                       (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_ILT_SHIFT))&LPUART_CTRL_ILT_MASK)
#define LPUART_CTRL_WAKE_MASK                    0x8u
#define LPUART_CTRL_WAKE_SHIFT                   3
#define LPUART_CTRL_WAKE_WIDTH                   1
#define LPUART_CTRL_WAKE(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_WAKE_SHIFT))&LPUART_CTRL_WAKE_MASK)
#define LPUART_CTRL_M_MASK                       0x10u
#define LPUART_CTRL_M_SHIFT                      4
#define LPUART_CTRL_M_WIDTH                      1
#define LPUART_CTRL_M(x)                         (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_M_SHIFT))&LPUART_CTRL_M_MASK)
#define LPUART_CTRL_RSRC_MASK                    0x20u
#define LPUART_CTRL_RSRC_SHIFT                   5
#define LPUART_CTRL_RSRC_WIDTH                   1
#define LPUART_CTRL_RSRC(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_RSRC_SHIFT))&LPUART_CTRL_RSRC_MASK)
#define LPUART_CTRL_DOZEEN_MASK                  0x40u
#define LPUART_CTRL_DOZEEN_SHIFT                 6
#define LPUART_CTRL_DOZEEN_WIDTH                 1
#define LPUART_CTRL_DOZEEN(x)                    (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_DOZEEN_SHIFT))&LPUART_CTRL_DOZEEN_MASK)
#define LPUART_CTRL_LOOPS_MASK                   0x80u
#define LPUART_CTRL_LOOPS_SHIFT                  7
#define LPUART_CTRL_LOOPS_WIDTH                  1
#define LPUART_CTRL_LOOPS(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_LOOPS_SHIFT))&LPUART_CTRL_LOOPS_MASK)
#define LPUART_CTRL_IDLECFG_MASK                 0x700u
#define LPUART_CTRL_IDLECFG_SHIFT                8
#define LPUART_CTRL_IDLECFG_WIDTH                3
#define LPUART_CTRL_IDLECFG(x)                   (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_IDLECFG_SHIFT))&LPUART_CTRL_IDLECFG_MASK)
#define LPUART_CTRL_MA2IE_MASK                   0x4000u
#define LPUART_CTRL_MA2IE_SHIFT                  14
#define LPUART_CTRL_MA2IE_WIDTH                  1
#define LPUART_CTRL_MA2IE(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_MA2IE_SHIFT))&LPUART_CTRL_MA2IE_MASK)
#define LPUART_CTRL_MA1IE_MASK                   0x8000u
#define LPUART_CTRL_MA1IE_SHIFT                  15
#define LPUART_CTRL_MA1IE_WIDTH                  1
#define LPUART_CTRL_MA1IE(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_MA1IE_SHIFT))&LPUART_CTRL_MA1IE_MASK)
#define LPUART_CTRL_SBK_MASK                     0x10000u
#define LPUART_CTRL_SBK_SHIFT                    16
#define LPUART_CTRL_SBK_WIDTH                    1
#define LPUART_CTRL_SBK(x)                       (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_SBK_SHIFT))&LPUART_CTRL_SBK_MASK)
#define LPUART_CTRL_RWU_MASK                     0x20000u
#define LPUART_CTRL_RWU_SHIFT                    17
#define LPUART_CTRL_RWU_WIDTH                    1
#define LPUART_CTRL_RWU(x)                       (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_RWU_SHIFT))&LPUART_CTRL_RWU_MASK)
#define LPUART_CTRL_RE_MASK                      0x40000u
#define LPUART_CTRL_RE_SHIFT                     18
#define LPUART_CTRL_RE_WIDTH                     1
#define LPUART_CTRL_RE(x)                        (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_RE_SHIFT))&LPUART_CTRL_RE_MASK)
#define LPUART_CTRL_TE_MASK                      0x80000u
#define LPUART_CTRL_TE_SHIFT                     19
#define LPUART_CTRL_TE_WIDTH                     1
#define LPUART_CTRL_TE(x)                        (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_TE_SHIFT))&LPUART_CTRL_TE_MASK)
#define LPUART_CTRL_ILIE_MASK                    0x100000u
#define LPUART_CTRL_ILIE_SHIFT                   20
#define LPUART_CTRL_ILIE_WIDTH                   1
#define LPUART_CTRL_ILIE(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_ILIE_SHIFT))&LPUART_CTRL_ILIE_MASK)
#define LPUART_CTRL_RIE_MASK                     0x200000u
#define LPUART_CTRL_RIE_SHIFT                    21
#define LPUART_CTRL_RIE_WIDTH                    1
#define LPUART_CTRL_RIE(x)                       (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_RIE_SHIFT))&LPUART_CTRL_RIE_MASK)
#define LPUART_CTRL_TCIE_MASK                    0x400000u
#define LPUART_CTRL_TCIE_SHIFT                   22
#define LPUART_CTRL_TCIE_WIDTH                   1
#define LPUART_CTRL_TCIE(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_TCIE_SHIFT))&LPUART_CTRL_TCIE_MASK)
#define LPUART_CTRL_TIE_MASK                     0x800000u
#define LPUART_CTRL_TIE_SHIFT                    23
#define LPUART_CTRL_TIE_WIDTH                    1
#define LPUART_CTRL_TIE(x)                       (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_TIE_SHIFT))&LPUART_CTRL_TIE_MASK)
#define LPUART_CTRL_PEIE_MASK                    0x1000000u
#define LPUART_CTRL_PEIE_SHIFT                   24
#define LPUART_CTRL_PEIE_WIDTH                   1
#define LPUART_CTRL_PEIE(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_PEIE_SHIFT))&LPUART_CTRL_PEIE_MASK)
#define LPUART_CTRL_FEIE_MASK                    0x2000000u
#define LPUART_CTRL_FEIE_SHIFT                   25
#define LPUART_CTRL_FEIE_WIDTH                   1
#define LPUART_CTRL_FEIE(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_FEIE_SHIFT))&LPUART_CTRL_FEIE_MASK)
#define LPUART_CTRL_NEIE_MASK                    0x4000000u
#define LPUART_CTRL_NEIE_SHIFT                   26
#define LPUART_CTRL_NEIE_WIDTH                   1
#define LPUART_CTRL_NEIE(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_NEIE_SHIFT))&LPUART_CTRL_NEIE_MASK)
#define LPUART_CTRL_ORIE_MASK                    0x8000000u
#define LPUART_CTRL_ORIE_SHIFT                   27
#define LPUART_CTRL_ORIE_WIDTH                   1
#define LPUART_CTRL_ORIE(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_ORIE_SHIFT))&LPUART_CTRL_ORIE_MASK)
#define LPUART_CTRL_TXINV_MASK                   0x10000000u
#define LPUART_CTRL_TXINV_SHIFT                  28
#define LPUART_CTRL_TXINV_WIDTH                  1
#define LPUART_CTRL_TXINV(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_TXINV_SHIFT))&LPUART_CTRL_TXINV_MASK)
#define LPUART_CTRL_TXDIR_MASK                   0x20000000u
#define LPUART_CTRL_TXDIR_SHIFT                  29
#define LPUART_CTRL_TXDIR_WIDTH                  1
#define LPUART_CTRL_TXDIR(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_TXDIR_SHIFT))&LPUART_CTRL_TXDIR_MASK)
#define LPUART_CTRL_R9T8_MASK                    0x40000000u
#define LPUART_CTRL_R9T8_SHIFT                   30
#define LPUART_CTRL_R9T8_WIDTH                   1
#define LPUART_CTRL_R9T8(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_R9T8_SHIFT))&LPUART_CTRL_R9T8_MASK)
#define LPUART_CTRL_R8T9_MASK                    0x80000000u
#define LPUART_CTRL_R8T9_SHIFT                   31
#define LPUART_CTRL_R8T9_WIDTH                   1
#define LPUART_CTRL_R8T9(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_CTRL_R8T9_SHIFT))&LPUART_CTRL_R8T9_MASK)
/* DATA Bit Fields */
#define LPUART_DATA_R0T0_MASK                    0x1u
#define LPUART_DATA_R0T0_SHIFT                   0
#define LPUART_DATA_R0T0_WIDTH                   1
#define LPUART_DATA_R0T0(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_R0T0_SHIFT))&LPUART_DATA_R0T0_MASK)
#define LPUART_DATA_R1T1_MASK                    0x2u
#define LPUART_DATA_R1T1_SHIFT                   1
#define LPUART_DATA_R1T1_WIDTH                   1
#define LPUART_DATA_R1T1(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_R1T1_SHIFT))&LPUART_DATA_R1T1_MASK)
#define LPUART_DATA_R2T2_MASK                    0x4u
#define LPUART_DATA_R2T2_SHIFT                   2
#define LPUART_DATA_R2T2_WIDTH                   1
#define LPUART_DATA_R2T2(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_R2T2_SHIFT))&LPUART_DATA_R2T2_MASK)
#define LPUART_DATA_R3T3_MASK                    0x8u
#define LPUART_DATA_R3T3_SHIFT                   3
#define LPUART_DATA_R3T3_WIDTH                   1
#define LPUART_DATA_R3T3(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_R3T3_SHIFT))&LPUART_DATA_R3T3_MASK)
#define LPUART_DATA_R4T4_MASK                    0x10u
#define LPUART_DATA_R4T4_SHIFT                   4
#define LPUART_DATA_R4T4_WIDTH                   1
#define LPUART_DATA_R4T4(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_R4T4_SHIFT))&LPUART_DATA_R4T4_MASK)
#define LPUART_DATA_R5T5_MASK                    0x20u
#define LPUART_DATA_R5T5_SHIFT                   5
#define LPUART_DATA_R5T5_WIDTH                   1
#define LPUART_DATA_R5T5(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_R5T5_SHIFT))&LPUART_DATA_R5T5_MASK)
#define LPUART_DATA_R6T6_MASK                    0x40u
#define LPUART_DATA_R6T6_SHIFT                   6
#define LPUART_DATA_R6T6_WIDTH                   1
#define LPUART_DATA_R6T6(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_R6T6_SHIFT))&LPUART_DATA_R6T6_MASK)
#define LPUART_DATA_R7T7_MASK                    0x80u
#define LPUART_DATA_R7T7_SHIFT                   7
#define LPUART_DATA_R7T7_WIDTH                   1
#define LPUART_DATA_R7T7(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_R7T7_SHIFT))&LPUART_DATA_R7T7_MASK)
#define LPUART_DATA_R8T8_MASK                    0x100u
#define LPUART_DATA_R8T8_SHIFT                   8
#define LPUART_DATA_R8T8_WIDTH                   1
#define LPUART_DATA_R8T8(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_R8T8_SHIFT))&LPUART_DATA_R8T8_MASK)
#define LPUART_DATA_R9T9_MASK                    0x200u
#define LPUART_DATA_R9T9_SHIFT                   9
#define LPUART_DATA_R9T9_WIDTH                   1
#define LPUART_DATA_R9T9(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_R9T9_SHIFT))&LPUART_DATA_R9T9_MASK)
#define LPUART_DATA_IDLINE_MASK                  0x800u
#define LPUART_DATA_IDLINE_SHIFT                 11
#define LPUART_DATA_IDLINE_WIDTH                 1
#define LPUART_DATA_IDLINE(x)                    (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_IDLINE_SHIFT))&LPUART_DATA_IDLINE_MASK)
#define LPUART_DATA_RXEMPT_MASK                  0x1000u
#define LPUART_DATA_RXEMPT_SHIFT                 12
#define LPUART_DATA_RXEMPT_WIDTH                 1
#define LPUART_DATA_RXEMPT(x)                    (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_RXEMPT_SHIFT))&LPUART_DATA_RXEMPT_MASK)
#define LPUART_DATA_FRETSC_MASK                  0x2000u
#define LPUART_DATA_FRETSC_SHIFT                 13
#define LPUART_DATA_FRETSC_WIDTH                 1
#define LPUART_DATA_FRETSC(x)                    (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_FRETSC_SHIFT))&LPUART_DATA_FRETSC_MASK)
#define LPUART_DATA_PARITYE_MASK                 0x4000u
#define LPUART_DATA_PARITYE_SHIFT                14
#define LPUART_DATA_PARITYE_WIDTH                1
#define LPUART_DATA_PARITYE(x)                   (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_PARITYE_SHIFT))&LPUART_DATA_PARITYE_MASK)
#define LPUART_DATA_NOISY_MASK                   0x8000u
#define LPUART_DATA_NOISY_SHIFT                  15
#define LPUART_DATA_NOISY_WIDTH                  1
#define LPUART_DATA_NOISY(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_DATA_NOISY_SHIFT))&LPUART_DATA_NOISY_MASK)
/* MATCH Bit Fields */
#define LPUART_MATCH_MA1_MASK                    0x3FFu
#define LPUART_MATCH_MA1_SHIFT                   0
#define LPUART_MATCH_MA1_WIDTH                   10
#define LPUART_MATCH_MA1(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_MATCH_MA1_SHIFT))&LPUART_MATCH_MA1_MASK)
#define LPUART_MATCH_MA2_MASK                    0x3FF0000u
#define LPUART_MATCH_MA2_SHIFT                   16
#define LPUART_MATCH_MA2_WIDTH                   10
#define LPUART_MATCH_MA2(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_MATCH_MA2_SHIFT))&LPUART_MATCH_MA2_MASK)
/* MODIR Bit Fields */
#define LPUART_MODIR_TXCTSE_MASK                 0x1u
#define LPUART_MODIR_TXCTSE_SHIFT                0
#define LPUART_MODIR_TXCTSE_WIDTH                1
#define LPUART_MODIR_TXCTSE(x)                   (((uint32_t)(((uint32_t)(x))<<LPUART_MODIR_TXCTSE_SHIFT))&LPUART_MODIR_TXCTSE_MASK)
#define LPUART_MODIR_TXRTSE_MASK                 0x2u
#define LPUART_MODIR_TXRTSE_SHIFT                1
#define LPUART_MODIR_TXRTSE_WIDTH                1
#define LPUART_MODIR_TXRTSE(x)                   (((uint32_t)(((uint32_t)(x))<<LPUART_MODIR_TXRTSE_SHIFT))&LPUART_MODIR_TXRTSE_MASK)
#define LPUART_MODIR_TXRTSPOL_MASK               0x4u
#define LPUART_MODIR_TXRTSPOL_SHIFT              2
#define LPUART_MODIR_TXRTSPOL_WIDTH              1
#define LPUART_MODIR_TXRTSPOL(x)                 (((uint32_t)(((uint32_t)(x))<<LPUART_MODIR_TXRTSPOL_SHIFT))&LPUART_MODIR_TXRTSPOL_MASK)
#define LPUART_MODIR_RXRTSE_MASK                 0x8u
#define LPUART_MODIR_RXRTSE_SHIFT                3
#define LPUART_MODIR_RXRTSE_WIDTH                1
#define LPUART_MODIR_RXRTSE(x)                   (((uint32_t)(((uint32_t)(x))<<LPUART_MODIR_RXRTSE_SHIFT))&LPUART_MODIR_RXRTSE_MASK)
#define LPUART_MODIR_TXCTSC_MASK                 0x10u
#define LPUART_MODIR_TXCTSC_SHIFT                4
#define LPUART_MODIR_TXCTSC_WIDTH                1
#define LPUART_MODIR_TXCTSC(x)                   (((uint32_t)(((uint32_t)(x))<<LPUART_MODIR_TXCTSC_SHIFT))&LPUART_MODIR_TXCTSC_MASK)
#define LPUART_MODIR_TXCTSSRC_MASK               0x20u
#define LPUART_MODIR_TXCTSSRC_SHIFT              5
#define LPUART_MODIR_TXCTSSRC_WIDTH              1
#define LPUART_MODIR_TXCTSSRC(x)                 (((uint32_t)(((uint32_t)(x))<<LPUART_MODIR_TXCTSSRC_SHIFT))&LPUART_MODIR_TXCTSSRC_MASK)
#define LPUART_MODIR_TNP_MASK                    0x30000u
#define LPUART_MODIR_TNP_SHIFT                   16
#define LPUART_MODIR_TNP_WIDTH                   2
#define LPUART_MODIR_TNP(x)                      (((uint32_t)(((uint32_t)(x))<<LPUART_MODIR_TNP_SHIFT))&LPUART_MODIR_TNP_MASK)
#define LPUART_MODIR_IREN_MASK                   0x40000u
#define LPUART_MODIR_IREN_SHIFT                  18
#define LPUART_MODIR_IREN_WIDTH                  1
#define LPUART_MODIR_IREN(x)                     (((uint32_t)(((uint32_t)(x))<<LPUART_MODIR_IREN_SHIFT))&LPUART_MODIR_IREN_MASK)

/*!
 * @}
 */ /* end of group LPUART_Register_Masks */


/* LPUART - Peripheral instance base addresses */
/** Peripheral LPUART0 base address */
#define LPUART0_BASE                             (0x4002A000u)
/** Peripheral LPUART0 base pointer */
#define LPUART0                                  ((LPUART_Type *)LPUART0_BASE)
#define LPUART0_BASE_PTR                         (LPUART0)
/** Array initializer of LPUART peripheral base addresses */
#define LPUART_BASE_ADDRS                        { LPUART0_BASE }
/** Array initializer of LPUART peripheral base pointers */
#define LPUART_BASE_PTRS                         { LPUART0 }
/** Interrupt vectors for the LPUART peripheral type */
#define LPUART_RX_TX_IRQS                        { LPUART0_IRQn }
#define LPUART_ERR_IRQS                          { LPUART0_IRQn }

/* ----------------------------------------------------------------------------
   -- LPUART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPUART_Register_Accessor_Macros LPUART - Register accessor macros
 * @{
 */


/* LPUART - Register instance definitions */
/* LPUART0 */
#define LPUART0_BAUD                             LPUART_BAUD_REG(LPUART0)
#define LPUART0_STAT                             LPUART_STAT_REG(LPUART0)
#define LPUART0_CTRL                             LPUART_CTRL_REG(LPUART0)
#define LPUART0_DATA                             LPUART_DATA_REG(LPUART0)
#define LPUART0_MATCH                            LPUART_MATCH_REG(LPUART0)
#define LPUART0_MODIR                            LPUART_MODIR_REG(LPUART0)

/*!
 * @}
 */ /* end of group LPUART_Register_Accessor_Macros */


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
  __IO uint8_t C1;                                 /**< MCG Control 1 Register, offset: 0x0 */
  __IO uint8_t C2;                                 /**< MCG Control 2 Register, offset: 0x1 */
  __IO uint8_t C3;                                 /**< MCG Control 3 Register, offset: 0x2 */
  __IO uint8_t C4;                                 /**< MCG Control 4 Register, offset: 0x3 */
  __IO uint8_t C5;                                 /**< MCG Control 5 Register, offset: 0x4 */
  __IO uint8_t C6;                                 /**< MCG Control 6 Register, offset: 0x5 */
  __IO uint8_t S;                                  /**< MCG Status Register, offset: 0x6 */
       uint8_t RESERVED_0[1];
  __IO uint8_t SC;                                 /**< MCG Status and Control Register, offset: 0x8 */
       uint8_t RESERVED_1[1];
  __IO uint8_t ATCVH;                              /**< MCG Auto Trim Compare Value High Register, offset: 0xA */
  __IO uint8_t ATCVL;                              /**< MCG Auto Trim Compare Value Low Register, offset: 0xB */
  __IO uint8_t C7;                                 /**< MCG Control 7 Register, offset: 0xC */
  __IO uint8_t C8;                                 /**< MCG Control 8 Register, offset: 0xD */
  __I  uint8_t C9;                                 /**< MCG Control 9 Register, offset: 0xE */
} MCG_Type, *MCG_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MCG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Register_Accessor_Macros MCG - Register accessor macros
 * @{
 */


/* MCG - Register accessors */
#define MCG_C1_REG(base)                         ((base)->C1)
#define MCG_C2_REG(base)                         ((base)->C2)
#define MCG_C3_REG(base)                         ((base)->C3)
#define MCG_C4_REG(base)                         ((base)->C4)
#define MCG_C5_REG(base)                         ((base)->C5)
#define MCG_C6_REG(base)                         ((base)->C6)
#define MCG_S_REG(base)                          ((base)->S)
#define MCG_SC_REG(base)                         ((base)->SC)
#define MCG_ATCVH_REG(base)                      ((base)->ATCVH)
#define MCG_ATCVL_REG(base)                      ((base)->ATCVL)
#define MCG_C7_REG(base)                         ((base)->C7)
#define MCG_C8_REG(base)                         ((base)->C8)
#define MCG_C9_REG(base)                         ((base)->C9)

/*!
 * @}
 */ /* end of group MCG_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MCG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Register_Masks MCG Register Masks
 * @{
 */

/* C1 Bit Fields */
#define MCG_C1_IREFSTEN_MASK                     0x1u
#define MCG_C1_IREFSTEN_SHIFT                    0
#define MCG_C1_IREFSTEN_WIDTH                    1
#define MCG_C1_IREFSTEN(x)                       (((uint8_t)(((uint8_t)(x))<<MCG_C1_IREFSTEN_SHIFT))&MCG_C1_IREFSTEN_MASK)
#define MCG_C1_IRCLKEN_MASK                      0x2u
#define MCG_C1_IRCLKEN_SHIFT                     1
#define MCG_C1_IRCLKEN_WIDTH                     1
#define MCG_C1_IRCLKEN(x)                        (((uint8_t)(((uint8_t)(x))<<MCG_C1_IRCLKEN_SHIFT))&MCG_C1_IRCLKEN_MASK)
#define MCG_C1_IREFS_MASK                        0x4u
#define MCG_C1_IREFS_SHIFT                       2
#define MCG_C1_IREFS_WIDTH                       1
#define MCG_C1_IREFS(x)                          (((uint8_t)(((uint8_t)(x))<<MCG_C1_IREFS_SHIFT))&MCG_C1_IREFS_MASK)
#define MCG_C1_FRDIV_MASK                        0x38u
#define MCG_C1_FRDIV_SHIFT                       3
#define MCG_C1_FRDIV_WIDTH                       3
#define MCG_C1_FRDIV(x)                          (((uint8_t)(((uint8_t)(x))<<MCG_C1_FRDIV_SHIFT))&MCG_C1_FRDIV_MASK)
#define MCG_C1_CLKS_MASK                         0xC0u
#define MCG_C1_CLKS_SHIFT                        6
#define MCG_C1_CLKS_WIDTH                        2
#define MCG_C1_CLKS(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_C1_CLKS_SHIFT))&MCG_C1_CLKS_MASK)
/* C2 Bit Fields */
#define MCG_C2_IRCS_MASK                         0x1u
#define MCG_C2_IRCS_SHIFT                        0
#define MCG_C2_IRCS_WIDTH                        1
#define MCG_C2_IRCS(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_C2_IRCS_SHIFT))&MCG_C2_IRCS_MASK)
#define MCG_C2_LP_MASK                           0x2u
#define MCG_C2_LP_SHIFT                          1
#define MCG_C2_LP_WIDTH                          1
#define MCG_C2_LP(x)                             (((uint8_t)(((uint8_t)(x))<<MCG_C2_LP_SHIFT))&MCG_C2_LP_MASK)
#define MCG_C2_EREFS0_MASK                       0x4u
#define MCG_C2_EREFS0_SHIFT                      2
#define MCG_C2_EREFS0_WIDTH                      1
#define MCG_C2_EREFS0(x)                         (((uint8_t)(((uint8_t)(x))<<MCG_C2_EREFS0_SHIFT))&MCG_C2_EREFS0_MASK)
#define MCG_C2_HGO0_MASK                         0x8u
#define MCG_C2_HGO0_SHIFT                        3
#define MCG_C2_HGO0_WIDTH                        1
#define MCG_C2_HGO0(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_C2_HGO0_SHIFT))&MCG_C2_HGO0_MASK)
#define MCG_C2_RANGE0_MASK                       0x30u
#define MCG_C2_RANGE0_SHIFT                      4
#define MCG_C2_RANGE0_WIDTH                      2
#define MCG_C2_RANGE0(x)                         (((uint8_t)(((uint8_t)(x))<<MCG_C2_RANGE0_SHIFT))&MCG_C2_RANGE0_MASK)
#define MCG_C2_LOCRE0_MASK                       0x80u
#define MCG_C2_LOCRE0_SHIFT                      7
#define MCG_C2_LOCRE0_WIDTH                      1
#define MCG_C2_LOCRE0(x)                         (((uint8_t)(((uint8_t)(x))<<MCG_C2_LOCRE0_SHIFT))&MCG_C2_LOCRE0_MASK)
/* C3 Bit Fields */
#define MCG_C3_SCTRIM_MASK                       0xFFu
#define MCG_C3_SCTRIM_SHIFT                      0
#define MCG_C3_SCTRIM_WIDTH                      8
#define MCG_C3_SCTRIM(x)                         (((uint8_t)(((uint8_t)(x))<<MCG_C3_SCTRIM_SHIFT))&MCG_C3_SCTRIM_MASK)
/* C4 Bit Fields */
#define MCG_C4_SCFTRIM_MASK                      0x1u
#define MCG_C4_SCFTRIM_SHIFT                     0
#define MCG_C4_SCFTRIM_WIDTH                     1
#define MCG_C4_SCFTRIM(x)                        (((uint8_t)(((uint8_t)(x))<<MCG_C4_SCFTRIM_SHIFT))&MCG_C4_SCFTRIM_MASK)
#define MCG_C4_FCTRIM_MASK                       0x1Eu
#define MCG_C4_FCTRIM_SHIFT                      1
#define MCG_C4_FCTRIM_WIDTH                      4
#define MCG_C4_FCTRIM(x)                         (((uint8_t)(((uint8_t)(x))<<MCG_C4_FCTRIM_SHIFT))&MCG_C4_FCTRIM_MASK)
#define MCG_C4_DRST_DRS_MASK                     0x60u
#define MCG_C4_DRST_DRS_SHIFT                    5
#define MCG_C4_DRST_DRS_WIDTH                    2
#define MCG_C4_DRST_DRS(x)                       (((uint8_t)(((uint8_t)(x))<<MCG_C4_DRST_DRS_SHIFT))&MCG_C4_DRST_DRS_MASK)
#define MCG_C4_DMX32_MASK                        0x80u
#define MCG_C4_DMX32_SHIFT                       7
#define MCG_C4_DMX32_WIDTH                       1
#define MCG_C4_DMX32(x)                          (((uint8_t)(((uint8_t)(x))<<MCG_C4_DMX32_SHIFT))&MCG_C4_DMX32_MASK)
/* C5 Bit Fields */
#define MCG_C5_PLLSTEN0_MASK                     0x20u
#define MCG_C5_PLLSTEN0_SHIFT                    5
#define MCG_C5_PLLSTEN0_WIDTH                    1
#define MCG_C5_PLLSTEN0(x)                       (((uint8_t)(((uint8_t)(x))<<MCG_C5_PLLSTEN0_SHIFT))&MCG_C5_PLLSTEN0_MASK)
#define MCG_C5_PLLCLKEN0_MASK                    0x40u
#define MCG_C5_PLLCLKEN0_SHIFT                   6
#define MCG_C5_PLLCLKEN0_WIDTH                   1
#define MCG_C5_PLLCLKEN0(x)                      (((uint8_t)(((uint8_t)(x))<<MCG_C5_PLLCLKEN0_SHIFT))&MCG_C5_PLLCLKEN0_MASK)
/* C6 Bit Fields */
#define MCG_C6_CHGPMP_BIAS_MASK                  0x1Fu
#define MCG_C6_CHGPMP_BIAS_SHIFT                 0
#define MCG_C6_CHGPMP_BIAS_WIDTH                 5
#define MCG_C6_CHGPMP_BIAS(x)                    (((uint8_t)(((uint8_t)(x))<<MCG_C6_CHGPMP_BIAS_SHIFT))&MCG_C6_CHGPMP_BIAS_MASK)
#define MCG_C6_CME0_MASK                         0x20u
#define MCG_C6_CME0_SHIFT                        5
#define MCG_C6_CME0_WIDTH                        1
#define MCG_C6_CME0(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_C6_CME0_SHIFT))&MCG_C6_CME0_MASK)
#define MCG_C6_PLLS_MASK                         0x40u
#define MCG_C6_PLLS_SHIFT                        6
#define MCG_C6_PLLS_WIDTH                        1
#define MCG_C6_PLLS(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_C6_PLLS_SHIFT))&MCG_C6_PLLS_MASK)
#define MCG_C6_LOLIE0_MASK                       0x80u
#define MCG_C6_LOLIE0_SHIFT                      7
#define MCG_C6_LOLIE0_WIDTH                      1
#define MCG_C6_LOLIE0(x)                         (((uint8_t)(((uint8_t)(x))<<MCG_C6_LOLIE0_SHIFT))&MCG_C6_LOLIE0_MASK)
/* S Bit Fields */
#define MCG_S_IRCST_MASK                         0x1u
#define MCG_S_IRCST_SHIFT                        0
#define MCG_S_IRCST_WIDTH                        1
#define MCG_S_IRCST(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_S_IRCST_SHIFT))&MCG_S_IRCST_MASK)
#define MCG_S_OSCINIT0_MASK                      0x2u
#define MCG_S_OSCINIT0_SHIFT                     1
#define MCG_S_OSCINIT0_WIDTH                     1
#define MCG_S_OSCINIT0(x)                        (((uint8_t)(((uint8_t)(x))<<MCG_S_OSCINIT0_SHIFT))&MCG_S_OSCINIT0_MASK)
#define MCG_S_CLKST_MASK                         0xCu
#define MCG_S_CLKST_SHIFT                        2
#define MCG_S_CLKST_WIDTH                        2
#define MCG_S_CLKST(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_S_CLKST_SHIFT))&MCG_S_CLKST_MASK)
#define MCG_S_IREFST_MASK                        0x10u
#define MCG_S_IREFST_SHIFT                       4
#define MCG_S_IREFST_WIDTH                       1
#define MCG_S_IREFST(x)                          (((uint8_t)(((uint8_t)(x))<<MCG_S_IREFST_SHIFT))&MCG_S_IREFST_MASK)
#define MCG_S_PLLST_MASK                         0x20u
#define MCG_S_PLLST_SHIFT                        5
#define MCG_S_PLLST_WIDTH                        1
#define MCG_S_PLLST(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_S_PLLST_SHIFT))&MCG_S_PLLST_MASK)
#define MCG_S_LOCK0_MASK                         0x40u
#define MCG_S_LOCK0_SHIFT                        6
#define MCG_S_LOCK0_WIDTH                        1
#define MCG_S_LOCK0(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_S_LOCK0_SHIFT))&MCG_S_LOCK0_MASK)
#define MCG_S_LOLS0_MASK                         0x80u
#define MCG_S_LOLS0_SHIFT                        7
#define MCG_S_LOLS0_WIDTH                        1
#define MCG_S_LOLS0(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_S_LOLS0_SHIFT))&MCG_S_LOLS0_MASK)
/* SC Bit Fields */
#define MCG_SC_LOCS0_MASK                        0x1u
#define MCG_SC_LOCS0_SHIFT                       0
#define MCG_SC_LOCS0_WIDTH                       1
#define MCG_SC_LOCS0(x)                          (((uint8_t)(((uint8_t)(x))<<MCG_SC_LOCS0_SHIFT))&MCG_SC_LOCS0_MASK)
#define MCG_SC_FCRDIV_MASK                       0xEu
#define MCG_SC_FCRDIV_SHIFT                      1
#define MCG_SC_FCRDIV_WIDTH                      3
#define MCG_SC_FCRDIV(x)                         (((uint8_t)(((uint8_t)(x))<<MCG_SC_FCRDIV_SHIFT))&MCG_SC_FCRDIV_MASK)
#define MCG_SC_FLTPRSRV_MASK                     0x10u
#define MCG_SC_FLTPRSRV_SHIFT                    4
#define MCG_SC_FLTPRSRV_WIDTH                    1
#define MCG_SC_FLTPRSRV(x)                       (((uint8_t)(((uint8_t)(x))<<MCG_SC_FLTPRSRV_SHIFT))&MCG_SC_FLTPRSRV_MASK)
#define MCG_SC_ATMF_MASK                         0x20u
#define MCG_SC_ATMF_SHIFT                        5
#define MCG_SC_ATMF_WIDTH                        1
#define MCG_SC_ATMF(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_SC_ATMF_SHIFT))&MCG_SC_ATMF_MASK)
#define MCG_SC_ATMS_MASK                         0x40u
#define MCG_SC_ATMS_SHIFT                        6
#define MCG_SC_ATMS_WIDTH                        1
#define MCG_SC_ATMS(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_SC_ATMS_SHIFT))&MCG_SC_ATMS_MASK)
#define MCG_SC_ATME_MASK                         0x80u
#define MCG_SC_ATME_SHIFT                        7
#define MCG_SC_ATME_WIDTH                        1
#define MCG_SC_ATME(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_SC_ATME_SHIFT))&MCG_SC_ATME_MASK)
/* ATCVH Bit Fields */
#define MCG_ATCVH_ATCVH_MASK                     0xFFu
#define MCG_ATCVH_ATCVH_SHIFT                    0
#define MCG_ATCVH_ATCVH_WIDTH                    8
#define MCG_ATCVH_ATCVH(x)                       (((uint8_t)(((uint8_t)(x))<<MCG_ATCVH_ATCVH_SHIFT))&MCG_ATCVH_ATCVH_MASK)
/* ATCVL Bit Fields */
#define MCG_ATCVL_ATCVL_MASK                     0xFFu
#define MCG_ATCVL_ATCVL_SHIFT                    0
#define MCG_ATCVL_ATCVL_WIDTH                    8
#define MCG_ATCVL_ATCVL(x)                       (((uint8_t)(((uint8_t)(x))<<MCG_ATCVL_ATCVL_SHIFT))&MCG_ATCVL_ATCVL_MASK)
/* C7 Bit Fields */
#define MCG_C7_OSCSEL_MASK                       0x1u
#define MCG_C7_OSCSEL_SHIFT                      0
#define MCG_C7_OSCSEL_WIDTH                      1
#define MCG_C7_OSCSEL(x)                         (((uint8_t)(((uint8_t)(x))<<MCG_C7_OSCSEL_SHIFT))&MCG_C7_OSCSEL_MASK)
#define MCG_C7_PLL32KREFSEL_MASK                 0xC0u
#define MCG_C7_PLL32KREFSEL_SHIFT                6
#define MCG_C7_PLL32KREFSEL_WIDTH                2
#define MCG_C7_PLL32KREFSEL(x)                   (((uint8_t)(((uint8_t)(x))<<MCG_C7_PLL32KREFSEL_SHIFT))&MCG_C7_PLL32KREFSEL_MASK)
/* C8 Bit Fields */
#define MCG_C8_LOCS1_MASK                        0x1u
#define MCG_C8_LOCS1_SHIFT                       0
#define MCG_C8_LOCS1_WIDTH                       1
#define MCG_C8_LOCS1(x)                          (((uint8_t)(((uint8_t)(x))<<MCG_C8_LOCS1_SHIFT))&MCG_C8_LOCS1_MASK)
#define MCG_C8_COARSE_LOLIE_MASK                 0x10u
#define MCG_C8_COARSE_LOLIE_SHIFT                4
#define MCG_C8_COARSE_LOLIE_WIDTH                1
#define MCG_C8_COARSE_LOLIE(x)                   (((uint8_t)(((uint8_t)(x))<<MCG_C8_COARSE_LOLIE_SHIFT))&MCG_C8_COARSE_LOLIE_MASK)
#define MCG_C8_CME1_MASK                         0x20u
#define MCG_C8_CME1_SHIFT                        5
#define MCG_C8_CME1_WIDTH                        1
#define MCG_C8_CME1(x)                           (((uint8_t)(((uint8_t)(x))<<MCG_C8_CME1_SHIFT))&MCG_C8_CME1_MASK)
#define MCG_C8_LOLRE_MASK                        0x40u
#define MCG_C8_LOLRE_SHIFT                       6
#define MCG_C8_LOLRE_WIDTH                       1
#define MCG_C8_LOLRE(x)                          (((uint8_t)(((uint8_t)(x))<<MCG_C8_LOLRE_SHIFT))&MCG_C8_LOLRE_MASK)
#define MCG_C8_LOCRE1_MASK                       0x80u
#define MCG_C8_LOCRE1_SHIFT                      7
#define MCG_C8_LOCRE1_WIDTH                      1
#define MCG_C8_LOCRE1(x)                         (((uint8_t)(((uint8_t)(x))<<MCG_C8_LOCRE1_SHIFT))&MCG_C8_LOCRE1_MASK)
/* C9 Bit Fields */
#define MCG_C9_COARSE_LOCK_MASK                  0x40u
#define MCG_C9_COARSE_LOCK_SHIFT                 6
#define MCG_C9_COARSE_LOCK_WIDTH                 1
#define MCG_C9_COARSE_LOCK(x)                    (((uint8_t)(((uint8_t)(x))<<MCG_C9_COARSE_LOCK_SHIFT))&MCG_C9_COARSE_LOCK_MASK)
#define MCG_C9_COARSE_LOLS_MASK                  0x80u
#define MCG_C9_COARSE_LOLS_SHIFT                 7
#define MCG_C9_COARSE_LOLS_WIDTH                 1
#define MCG_C9_COARSE_LOLS(x)                    (((uint8_t)(((uint8_t)(x))<<MCG_C9_COARSE_LOLS_SHIFT))&MCG_C9_COARSE_LOLS_MASK)

/*!
 * @}
 */ /* end of group MCG_Register_Masks */


/* MCG - Peripheral instance base addresses */
/** Peripheral MCG base address */
#define MCG_BASE                                 (0x40064000u)
/** Peripheral MCG base pointer */
#define MCG                                      ((MCG_Type *)MCG_BASE)
#define MCG_BASE_PTR                             (MCG)
/** Array initializer of MCG peripheral base addresses */
#define MCG_BASE_ADDRS                           { MCG_BASE }
/** Array initializer of MCG peripheral base pointers */
#define MCG_BASE_PTRS                            { MCG }
/** Interrupt vectors for the MCG peripheral type */
#define MCG_IRQS                                 { MCG_IRQn }

/* ----------------------------------------------------------------------------
   -- MCG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Register_Accessor_Macros MCG - Register accessor macros
 * @{
 */


/* MCG - Register instance definitions */
/* MCG */
#define MCG_C1                                   MCG_C1_REG(MCG)
#define MCG_C2                                   MCG_C2_REG(MCG)
#define MCG_C3                                   MCG_C3_REG(MCG)
#define MCG_C4                                   MCG_C4_REG(MCG)
#define MCG_C5                                   MCG_C5_REG(MCG)
#define MCG_C6                                   MCG_C6_REG(MCG)
#define MCG_S                                    MCG_S_REG(MCG)
#define MCG_SC                                   MCG_SC_REG(MCG)
#define MCG_ATCVH                                MCG_ATCVH_REG(MCG)
#define MCG_ATCVL                                MCG_ATCVL_REG(MCG)
#define MCG_C7                                   MCG_C7_REG(MCG)
#define MCG_C8                                   MCG_C8_REG(MCG)
#define MCG_C9                                   MCG_C9_REG(MCG)

/*!
 * @}
 */ /* end of group MCG_Register_Accessor_Macros */

/* MCG C2[EREFS] backward compatibility */
#define MCG_C2_EREFS_MASK         (MCG_C2_EREFS0_MASK)
#define MCG_C2_EREFS_SHIFT        (MCG_C2_EREFS0_SHIFT)
#define MCG_C2_EREFS_WIDTH        (MCG_C2_EREFS0_WIDTH)
#define MCG_C2_EREFS(x)           (MCG_C2_EREFS0(x))

/* MCG C2[HGO] backward compatibility */
#define MCG_C2_HGO_MASK         (MCG_C2_HGO0_MASK)
#define MCG_C2_HGO_SHIFT        (MCG_C2_HGO0_SHIFT)
#define MCG_C2_HGO_WIDTH        (MCG_C2_HGO0_WIDTH)
#define MCG_C2_HGO(x)           (MCG_C2_HGO0(x))

/* MCG C2[RANGE] backward compatibility */
#define MCG_C2_RANGE_MASK         (MCG_C2_RANGE0_MASK)
#define MCG_C2_RANGE_SHIFT        (MCG_C2_RANGE0_SHIFT)
#define MCG_C2_RANGE_WIDTH        (MCG_C2_RANGE0_WIDTH)
#define MCG_C2_RANGE(x)           (MCG_C2_RANGE0(x))


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
       uint8_t RESERVED_1[32];
  __IO uint32_t PID;                               /**< Process ID register, offset: 0x30 */
       uint8_t RESERVED_2[12];
  __IO uint32_t CPO;                               /**< Compute Operation Control Register, offset: 0x40 */
       uint8_t RESERVED_3[60];
  __IO uint32_t MATCR[1];                          /**< Master Attribute Configuration Register, array offset: 0x80, array step: 0x4 */
} MCM_Type, *MCM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Accessor_Macros MCM - Register accessor macros
 * @{
 */


/* MCM - Register accessors */
#define MCM_PLASC_REG(base)                      ((base)->PLASC)
#define MCM_PLAMC_REG(base)                      ((base)->PLAMC)
#define MCM_PLACR_REG(base)                      ((base)->PLACR)
#define MCM_PID_REG(base)                        ((base)->PID)
#define MCM_CPO_REG(base)                        ((base)->CPO)
#define MCM_MATCR_REG(base,index)                ((base)->MATCR[index])
#define MCM_MATCR_COUNT                          1

/*!
 * @}
 */ /* end of group MCM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Masks MCM Register Masks
 * @{
 */

/* PLASC Bit Fields */
#define MCM_PLASC_ASC_MASK                       0xFFu
#define MCM_PLASC_ASC_SHIFT                      0
#define MCM_PLASC_ASC_WIDTH                      8
#define MCM_PLASC_ASC(x)                         (((uint16_t)(((uint16_t)(x))<<MCM_PLASC_ASC_SHIFT))&MCM_PLASC_ASC_MASK)
/* PLAMC Bit Fields */
#define MCM_PLAMC_AMC_MASK                       0xFFu
#define MCM_PLAMC_AMC_SHIFT                      0
#define MCM_PLAMC_AMC_WIDTH                      8
#define MCM_PLAMC_AMC(x)                         (((uint16_t)(((uint16_t)(x))<<MCM_PLAMC_AMC_SHIFT))&MCM_PLAMC_AMC_MASK)
/* PLACR Bit Fields */
#define MCM_PLACR_ARB_MASK                       0x200u
#define MCM_PLACR_ARB_SHIFT                      9
#define MCM_PLACR_ARB_WIDTH                      1
#define MCM_PLACR_ARB(x)                         (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_ARB_SHIFT))&MCM_PLACR_ARB_MASK)
#define MCM_PLACR_CFCC_MASK                      0x400u
#define MCM_PLACR_CFCC_SHIFT                     10
#define MCM_PLACR_CFCC_WIDTH                     1
#define MCM_PLACR_CFCC(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_CFCC_SHIFT))&MCM_PLACR_CFCC_MASK)
#define MCM_PLACR_DFCDA_MASK                     0x800u
#define MCM_PLACR_DFCDA_SHIFT                    11
#define MCM_PLACR_DFCDA_WIDTH                    1
#define MCM_PLACR_DFCDA(x)                       (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_DFCDA_SHIFT))&MCM_PLACR_DFCDA_MASK)
#define MCM_PLACR_DFCIC_MASK                     0x1000u
#define MCM_PLACR_DFCIC_SHIFT                    12
#define MCM_PLACR_DFCIC_WIDTH                    1
#define MCM_PLACR_DFCIC(x)                       (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_DFCIC_SHIFT))&MCM_PLACR_DFCIC_MASK)
#define MCM_PLACR_DFCC_MASK                      0x2000u
#define MCM_PLACR_DFCC_SHIFT                     13
#define MCM_PLACR_DFCC_WIDTH                     1
#define MCM_PLACR_DFCC(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_DFCC_SHIFT))&MCM_PLACR_DFCC_MASK)
#define MCM_PLACR_EFDS_MASK                      0x4000u
#define MCM_PLACR_EFDS_SHIFT                     14
#define MCM_PLACR_EFDS_WIDTH                     1
#define MCM_PLACR_EFDS(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_EFDS_SHIFT))&MCM_PLACR_EFDS_MASK)
#define MCM_PLACR_DFCS_MASK                      0x8000u
#define MCM_PLACR_DFCS_SHIFT                     15
#define MCM_PLACR_DFCS_WIDTH                     1
#define MCM_PLACR_DFCS(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_DFCS_SHIFT))&MCM_PLACR_DFCS_MASK)
#define MCM_PLACR_ESFC_MASK                      0x10000u
#define MCM_PLACR_ESFC_SHIFT                     16
#define MCM_PLACR_ESFC_WIDTH                     1
#define MCM_PLACR_ESFC(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_ESFC_SHIFT))&MCM_PLACR_ESFC_MASK)
/* PID Bit Fields */
#define MCM_PID_PID_MASK                         0xFFu
#define MCM_PID_PID_SHIFT                        0
#define MCM_PID_PID_WIDTH                        8
#define MCM_PID_PID(x)                           (((uint32_t)(((uint32_t)(x))<<MCM_PID_PID_SHIFT))&MCM_PID_PID_MASK)
/* CPO Bit Fields */
#define MCM_CPO_CPOREQ_MASK                      0x1u
#define MCM_CPO_CPOREQ_SHIFT                     0
#define MCM_CPO_CPOREQ_WIDTH                     1
#define MCM_CPO_CPOREQ(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_CPO_CPOREQ_SHIFT))&MCM_CPO_CPOREQ_MASK)
#define MCM_CPO_CPOACK_MASK                      0x2u
#define MCM_CPO_CPOACK_SHIFT                     1
#define MCM_CPO_CPOACK_WIDTH                     1
#define MCM_CPO_CPOACK(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_CPO_CPOACK_SHIFT))&MCM_CPO_CPOACK_MASK)
#define MCM_CPO_CPOWOI_MASK                      0x4u
#define MCM_CPO_CPOWOI_SHIFT                     2
#define MCM_CPO_CPOWOI_WIDTH                     1
#define MCM_CPO_CPOWOI(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_CPO_CPOWOI_SHIFT))&MCM_CPO_CPOWOI_MASK)
/* MATCR Bit Fields */
#define MCM_MATCR_ATC0_MASK                      0x7u
#define MCM_MATCR_ATC0_SHIFT                     0
#define MCM_MATCR_ATC0_WIDTH                     3
#define MCM_MATCR_ATC0(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_MATCR_ATC0_SHIFT))&MCM_MATCR_ATC0_MASK)
#define MCM_MATCR_RO0_MASK                       0x80u
#define MCM_MATCR_RO0_SHIFT                      7
#define MCM_MATCR_RO0_WIDTH                      1
#define MCM_MATCR_RO0(x)                         (((uint32_t)(((uint32_t)(x))<<MCM_MATCR_RO0_SHIFT))&MCM_MATCR_RO0_MASK)
#define MCM_MATCR_ATC2_MASK                      0x70000u
#define MCM_MATCR_ATC2_SHIFT                     16
#define MCM_MATCR_ATC2_WIDTH                     3
#define MCM_MATCR_ATC2(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_MATCR_ATC2_SHIFT))&MCM_MATCR_ATC2_MASK)
#define MCM_MATCR_RO2_MASK                       0x800000u
#define MCM_MATCR_RO2_SHIFT                      23
#define MCM_MATCR_RO2_WIDTH                      1
#define MCM_MATCR_RO2(x)                         (((uint32_t)(((uint32_t)(x))<<MCM_MATCR_RO2_SHIFT))&MCM_MATCR_RO2_MASK)

/*!
 * @}
 */ /* end of group MCM_Register_Masks */


/* MCM - Peripheral instance base addresses */
/** Peripheral MCM base address */
#define MCM_BASE                                 (0xF0003000u)
/** Peripheral MCM base pointer */
#define MCM                                      ((MCM_Type *)MCM_BASE)
#define MCM_BASE_PTR                             (MCM)
/** Array initializer of MCM peripheral base addresses */
#define MCM_BASE_ADDRS                           { MCM_BASE }
/** Array initializer of MCM peripheral base pointers */
#define MCM_BASE_PTRS                            { MCM }

/* ----------------------------------------------------------------------------
   -- MCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Accessor_Macros MCM - Register accessor macros
 * @{
 */


/* MCM - Register instance definitions */
/* MCM */
#define MCM_PLASC                                MCM_PLASC_REG(MCM)
#define MCM_PLAMC                                MCM_PLAMC_REG(MCM)
#define MCM_PLACR                                MCM_PLACR_REG(MCM)
#define MCM_PID                                  MCM_PID_REG(MCM)
#define MCM_CPO                                  MCM_CPO_REG(MCM)
#define MCM_MATCR0                               MCM_MATCR_REG(MCM,0)

/* MCM - Register array accessors */
#define MCM_MATCR(index)                         MCM_MATCR_REG(MCM,index)

/*!
 * @}
 */ /* end of group MCM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group MCM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MMAU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MMAU_Peripheral_Access_Layer MMAU Peripheral Access Layer
 * @{
 */

/** MMAU - Register Layout Typedef */
typedef struct {
  __IO uint32_t X0;                                /**< Operand Register X0, offset: 0x0 */
  __IO uint32_t X1;                                /**< Operand Register X1, offset: 0x4 */
  __IO uint32_t X2;                                /**< Operand Register X2, offset: 0x8 */
  __IO uint32_t X3;                                /**< Operand Register X3, offset: 0xC */
  __IO uint32_t A0;                                /**< Accumulator Register A0, offset: 0x10 */
  __IO uint32_t A1;                                /**< Accumulator Register A1, offset: 0x14 */
  __IO uint32_t CSR;                               /**< Control/Status Register, offset: 0x18 */
  __IO uint32_t CSR_IF_CLR;                        /**< CSR Interrupt Flags Clearance Register, offset: 0x1C */
} MMAU_Type, *MMAU_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MMAU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MMAU_Register_Accessor_Macros MMAU - Register accessor macros
 * @{
 */


/* MMAU - Register accessors */
#define MMAU_X0_REG(base)                        ((base)->X0)
#define MMAU_X1_REG(base)                        ((base)->X1)
#define MMAU_X2_REG(base)                        ((base)->X2)
#define MMAU_X3_REG(base)                        ((base)->X3)
#define MMAU_A0_REG(base)                        ((base)->A0)
#define MMAU_A1_REG(base)                        ((base)->A1)
#define MMAU_CSR_REG(base)                       ((base)->CSR)
#define MMAU_CSR_IF_CLR_REG(base)                ((base)->CSR_IF_CLR)

/*!
 * @}
 */ /* end of group MMAU_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MMAU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MMAU_Register_Masks MMAU Register Masks
 * @{
 */

/* X0 Bit Fields */
#define MMAU_X0_X0_MASK                          0xFFFFFFFFu
#define MMAU_X0_X0_SHIFT                         0
#define MMAU_X0_X0_WIDTH                         32
#define MMAU_X0_X0(x)                            (((uint32_t)(((uint32_t)(x))<<MMAU_X0_X0_SHIFT))&MMAU_X0_X0_MASK)
/* X1 Bit Fields */
#define MMAU_X1_X1_MASK                          0xFFFFFFFFu
#define MMAU_X1_X1_SHIFT                         0
#define MMAU_X1_X1_WIDTH                         32
#define MMAU_X1_X1(x)                            (((uint32_t)(((uint32_t)(x))<<MMAU_X1_X1_SHIFT))&MMAU_X1_X1_MASK)
/* X2 Bit Fields */
#define MMAU_X2_X2_MASK                          0xFFFFFFFFu
#define MMAU_X2_X2_SHIFT                         0
#define MMAU_X2_X2_WIDTH                         32
#define MMAU_X2_X2(x)                            (((uint32_t)(((uint32_t)(x))<<MMAU_X2_X2_SHIFT))&MMAU_X2_X2_MASK)
/* X3 Bit Fields */
#define MMAU_X3_X3_MASK                          0xFFFFFFFFu
#define MMAU_X3_X3_SHIFT                         0
#define MMAU_X3_X3_WIDTH                         32
#define MMAU_X3_X3(x)                            (((uint32_t)(((uint32_t)(x))<<MMAU_X3_X3_SHIFT))&MMAU_X3_X3_MASK)
/* A0 Bit Fields */
#define MMAU_A0_A0_MASK                          0xFFFFFFFFu
#define MMAU_A0_A0_SHIFT                         0
#define MMAU_A0_A0_WIDTH                         32
#define MMAU_A0_A0(x)                            (((uint32_t)(((uint32_t)(x))<<MMAU_A0_A0_SHIFT))&MMAU_A0_A0_MASK)
/* A1 Bit Fields */
#define MMAU_A1_A1_MASK                          0xFFFFFFFFu
#define MMAU_A1_A1_SHIFT                         0
#define MMAU_A1_A1_WIDTH                         32
#define MMAU_A1_A1(x)                            (((uint32_t)(((uint32_t)(x))<<MMAU_A1_A1_SHIFT))&MMAU_A1_A1_MASK)
/* CSR Bit Fields */
#define MMAU_CSR_Q_MASK                          0x1u
#define MMAU_CSR_Q_SHIFT                         0
#define MMAU_CSR_Q_WIDTH                         1
#define MMAU_CSR_Q(x)                            (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_Q_SHIFT))&MMAU_CSR_Q_MASK)
#define MMAU_CSR_V_MASK                          0x2u
#define MMAU_CSR_V_SHIFT                         1
#define MMAU_CSR_V_WIDTH                         1
#define MMAU_CSR_V(x)                            (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_V_SHIFT))&MMAU_CSR_V_MASK)
#define MMAU_CSR_DZ_MASK                         0x4u
#define MMAU_CSR_DZ_SHIFT                        2
#define MMAU_CSR_DZ_WIDTH                        1
#define MMAU_CSR_DZ(x)                           (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_DZ_SHIFT))&MMAU_CSR_DZ_MASK)
#define MMAU_CSR_N_MASK                          0x8u
#define MMAU_CSR_N_SHIFT                         3
#define MMAU_CSR_N_WIDTH                         1
#define MMAU_CSR_N(x)                            (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_N_SHIFT))&MMAU_CSR_N_MASK)
#define MMAU_CSR_QIF_MASK                        0x10u
#define MMAU_CSR_QIF_SHIFT                       4
#define MMAU_CSR_QIF_WIDTH                       1
#define MMAU_CSR_QIF(x)                          (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_QIF_SHIFT))&MMAU_CSR_QIF_MASK)
#define MMAU_CSR_VIF_MASK                        0x20u
#define MMAU_CSR_VIF_SHIFT                       5
#define MMAU_CSR_VIF_WIDTH                       1
#define MMAU_CSR_VIF(x)                          (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_VIF_SHIFT))&MMAU_CSR_VIF_MASK)
#define MMAU_CSR_DZIF_MASK                       0x40u
#define MMAU_CSR_DZIF_SHIFT                      6
#define MMAU_CSR_DZIF_WIDTH                      1
#define MMAU_CSR_DZIF(x)                         (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_DZIF_SHIFT))&MMAU_CSR_DZIF_MASK)
#define MMAU_CSR_QIE_MASK                        0x1000u
#define MMAU_CSR_QIE_SHIFT                       12
#define MMAU_CSR_QIE_WIDTH                       1
#define MMAU_CSR_QIE(x)                          (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_QIE_SHIFT))&MMAU_CSR_QIE_MASK)
#define MMAU_CSR_VIE_MASK                        0x2000u
#define MMAU_CSR_VIE_SHIFT                       13
#define MMAU_CSR_VIE_WIDTH                       1
#define MMAU_CSR_VIE(x)                          (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_VIE_SHIFT))&MMAU_CSR_VIE_MASK)
#define MMAU_CSR_DZIE_MASK                       0x4000u
#define MMAU_CSR_DZIE_SHIFT                      14
#define MMAU_CSR_DZIE_WIDTH                      1
#define MMAU_CSR_DZIE(x)                         (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_DZIE_SHIFT))&MMAU_CSR_DZIE_MASK)
#define MMAU_CSR_DRE_MASK                        0x10000u
#define MMAU_CSR_DRE_SHIFT                       16
#define MMAU_CSR_DRE_WIDTH                       1
#define MMAU_CSR_DRE(x)                          (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_DRE_SHIFT))&MMAU_CSR_DRE_MASK)
#define MMAU_CSR_SO_MASK                         0x20000u
#define MMAU_CSR_SO_SHIFT                        17
#define MMAU_CSR_SO_WIDTH                        1
#define MMAU_CSR_SO(x)                           (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_SO_SHIFT))&MMAU_CSR_SO_MASK)
#define MMAU_CSR_HDR_MASK                        0xF00000u
#define MMAU_CSR_HDR_SHIFT                       20
#define MMAU_CSR_HDR_WIDTH                       4
#define MMAU_CSR_HDR(x)                          (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_HDR_SHIFT))&MMAU_CSR_HDR_MASK)
#define MMAU_CSR_BUSY_MASK                       0x80000000u
#define MMAU_CSR_BUSY_SHIFT                      31
#define MMAU_CSR_BUSY_WIDTH                      1
#define MMAU_CSR_BUSY(x)                         (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_BUSY_SHIFT))&MMAU_CSR_BUSY_MASK)
/* CSR_IF_CLR Bit Fields */
#define MMAU_CSR_IF_CLR_Q_MASK                   0x1u
#define MMAU_CSR_IF_CLR_Q_SHIFT                  0
#define MMAU_CSR_IF_CLR_Q_WIDTH                  1
#define MMAU_CSR_IF_CLR_Q(x)                     (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_IF_CLR_Q_SHIFT))&MMAU_CSR_IF_CLR_Q_MASK)
#define MMAU_CSR_IF_CLR_V_MASK                   0x2u
#define MMAU_CSR_IF_CLR_V_SHIFT                  1
#define MMAU_CSR_IF_CLR_V_WIDTH                  1
#define MMAU_CSR_IF_CLR_V(x)                     (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_IF_CLR_V_SHIFT))&MMAU_CSR_IF_CLR_V_MASK)
#define MMAU_CSR_IF_CLR_DZ_MASK                  0x4u
#define MMAU_CSR_IF_CLR_DZ_SHIFT                 2
#define MMAU_CSR_IF_CLR_DZ_WIDTH                 1
#define MMAU_CSR_IF_CLR_DZ(x)                    (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_IF_CLR_DZ_SHIFT))&MMAU_CSR_IF_CLR_DZ_MASK)
#define MMAU_CSR_IF_CLR_N_MASK                   0x8u
#define MMAU_CSR_IF_CLR_N_SHIFT                  3
#define MMAU_CSR_IF_CLR_N_WIDTH                  1
#define MMAU_CSR_IF_CLR_N(x)                     (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_IF_CLR_N_SHIFT))&MMAU_CSR_IF_CLR_N_MASK)
#define MMAU_CSR_IF_CLR_QIF_MASK                 0x10u
#define MMAU_CSR_IF_CLR_QIF_SHIFT                4
#define MMAU_CSR_IF_CLR_QIF_WIDTH                1
#define MMAU_CSR_IF_CLR_QIF(x)                   (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_IF_CLR_QIF_SHIFT))&MMAU_CSR_IF_CLR_QIF_MASK)
#define MMAU_CSR_IF_CLR_VIF_MASK                 0x20u
#define MMAU_CSR_IF_CLR_VIF_SHIFT                5
#define MMAU_CSR_IF_CLR_VIF_WIDTH                1
#define MMAU_CSR_IF_CLR_VIF(x)                   (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_IF_CLR_VIF_SHIFT))&MMAU_CSR_IF_CLR_VIF_MASK)
#define MMAU_CSR_IF_CLR_DZIF_MASK                0x40u
#define MMAU_CSR_IF_CLR_DZIF_SHIFT               6
#define MMAU_CSR_IF_CLR_DZIF_WIDTH               1
#define MMAU_CSR_IF_CLR_DZIF(x)                  (((uint32_t)(((uint32_t)(x))<<MMAU_CSR_IF_CLR_DZIF_SHIFT))&MMAU_CSR_IF_CLR_DZIF_MASK)

/*!
 * @}
 */ /* end of group MMAU_Register_Masks */


/* MMAU - Peripheral instance base addresses */
/** Peripheral MMAU base address */
#define MMAU_BASE                                (0xF0004000u)
/** Peripheral MMAU base pointer */
#define MMAU                                     ((MMAU_Type *)MMAU_BASE)
#define MMAU_BASE_PTR                            (MMAU)
/** Array initializer of MMAU peripheral base addresses */
#define MMAU_BASE_ADDRS                          { MMAU_BASE }
/** Array initializer of MMAU peripheral base pointers */
#define MMAU_BASE_PTRS                           { MMAU }
/** Interrupt vectors for the MMAU peripheral type */
#define MMAU_IRQS                                { MMAU_IRQn }

/* ----------------------------------------------------------------------------
   -- MMAU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MMAU_Register_Accessor_Macros MMAU - Register accessor macros
 * @{
 */


/* MMAU - Register instance definitions */
/* MMAU */
#define MMAU_X0                                  MMAU_X0_REG(MMAU)
#define MMAU_X1                                  MMAU_X1_REG(MMAU)
#define MMAU_X2                                  MMAU_X2_REG(MMAU)
#define MMAU_X3                                  MMAU_X3_REG(MMAU)
#define MMAU_A0                                  MMAU_A0_REG(MMAU)
#define MMAU_A1                                  MMAU_A1_REG(MMAU)
#define MMAU_CSR                                 MMAU_CSR_REG(MMAU)
#define MMAU_CSR_IF_CLR                          MMAU_CSR_IF_CLR_REG(MMAU)

/*!
 * @}
 */ /* end of group MMAU_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group MMAU_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MPU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MPU_Peripheral_Access_Layer MPU Peripheral Access Layer
 * @{
 */

/** MPU - Register Layout Typedef */
typedef struct {
  __IO uint32_t CESR;                              /**< Control/Error Status Register, offset: 0x0 */
       uint8_t RESERVED_0[12];
  struct {                                         /* offset: 0x10, array step: 0x8 */
    __I  uint32_t EAR;                               /**< Error Address Register, slave port n, array offset: 0x10, array step: 0x8 */
    __I  uint32_t EDR;                               /**< Error Detail Register, slave port n, array offset: 0x14, array step: 0x8 */
  } SP[2];
       uint8_t RESERVED_1[992];
  __IO uint32_t WORD[8][4];                        /**< Region Descriptor n, Word 0..Region Descriptor n, Word 3, array offset: 0x400, array step: index*0x10, index2*0x4 */
       uint8_t RESERVED_2[896];
  __IO uint32_t RGDAAC[8];                         /**< Region Descriptor Alternate Access Control n, array offset: 0x800, array step: 0x4 */
} MPU_Type, *MPU_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MPU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MPU_Register_Accessor_Macros MPU - Register accessor macros
 * @{
 */


/* MPU - Register accessors */
#define MPU_CESR_REG(base)                       ((base)->CESR)
#define MPU_EAR_REG(base,index)                  ((base)->SP[index].EAR)
#define MPU_EAR_COUNT                            2
#define MPU_EDR_REG(base,index)                  ((base)->SP[index].EDR)
#define MPU_EDR_COUNT                            2
#define MPU_WORD_REG(base,index,index2)          ((base)->WORD[index][index2])
#define MPU_WORD_COUNT                           8
#define MPU_WORD_COUNT2                          4
#define MPU_RGDAAC_REG(base,index)               ((base)->RGDAAC[index])
#define MPU_RGDAAC_COUNT                         8

/*!
 * @}
 */ /* end of group MPU_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MPU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MPU_Register_Masks MPU Register Masks
 * @{
 */

/* CESR Bit Fields */
#define MPU_CESR_VLD_MASK                        0x1u
#define MPU_CESR_VLD_SHIFT                       0
#define MPU_CESR_VLD_WIDTH                       1
#define MPU_CESR_VLD(x)                          (((uint32_t)(((uint32_t)(x))<<MPU_CESR_VLD_SHIFT))&MPU_CESR_VLD_MASK)
#define MPU_CESR_NRGD_MASK                       0xF00u
#define MPU_CESR_NRGD_SHIFT                      8
#define MPU_CESR_NRGD_WIDTH                      4
#define MPU_CESR_NRGD(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_CESR_NRGD_SHIFT))&MPU_CESR_NRGD_MASK)
#define MPU_CESR_NSP_MASK                        0xF000u
#define MPU_CESR_NSP_SHIFT                       12
#define MPU_CESR_NSP_WIDTH                       4
#define MPU_CESR_NSP(x)                          (((uint32_t)(((uint32_t)(x))<<MPU_CESR_NSP_SHIFT))&MPU_CESR_NSP_MASK)
#define MPU_CESR_HRL_MASK                        0xF0000u
#define MPU_CESR_HRL_SHIFT                       16
#define MPU_CESR_HRL_WIDTH                       4
#define MPU_CESR_HRL(x)                          (((uint32_t)(((uint32_t)(x))<<MPU_CESR_HRL_SHIFT))&MPU_CESR_HRL_MASK)
#define MPU_CESR_SPERR_MASK                      0xC0000000u
#define MPU_CESR_SPERR_SHIFT                     30
#define MPU_CESR_SPERR_WIDTH                     2
#define MPU_CESR_SPERR(x)                        (((uint32_t)(((uint32_t)(x))<<MPU_CESR_SPERR_SHIFT))&MPU_CESR_SPERR_MASK)
/* EAR Bit Fields */
#define MPU_EAR_EADDR_MASK                       0xFFFFFFFFu
#define MPU_EAR_EADDR_SHIFT                      0
#define MPU_EAR_EADDR_WIDTH                      32
#define MPU_EAR_EADDR(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_EAR_EADDR_SHIFT))&MPU_EAR_EADDR_MASK)
/* EDR Bit Fields */
#define MPU_EDR_ERW_MASK                         0x1u
#define MPU_EDR_ERW_SHIFT                        0
#define MPU_EDR_ERW_WIDTH                        1
#define MPU_EDR_ERW(x)                           (((uint32_t)(((uint32_t)(x))<<MPU_EDR_ERW_SHIFT))&MPU_EDR_ERW_MASK)
#define MPU_EDR_EATTR_MASK                       0xEu
#define MPU_EDR_EATTR_SHIFT                      1
#define MPU_EDR_EATTR_WIDTH                      3
#define MPU_EDR_EATTR(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_EDR_EATTR_SHIFT))&MPU_EDR_EATTR_MASK)
#define MPU_EDR_EMN_MASK                         0xF0u
#define MPU_EDR_EMN_SHIFT                        4
#define MPU_EDR_EMN_WIDTH                        4
#define MPU_EDR_EMN(x)                           (((uint32_t)(((uint32_t)(x))<<MPU_EDR_EMN_SHIFT))&MPU_EDR_EMN_MASK)
#define MPU_EDR_EPID_MASK                        0xFF00u
#define MPU_EDR_EPID_SHIFT                       8
#define MPU_EDR_EPID_WIDTH                       8
#define MPU_EDR_EPID(x)                          (((uint32_t)(((uint32_t)(x))<<MPU_EDR_EPID_SHIFT))&MPU_EDR_EPID_MASK)
#define MPU_EDR_EACD_MASK                        0xFFFF0000u
#define MPU_EDR_EACD_SHIFT                       16
#define MPU_EDR_EACD_WIDTH                       16
#define MPU_EDR_EACD(x)                          (((uint32_t)(((uint32_t)(x))<<MPU_EDR_EACD_SHIFT))&MPU_EDR_EACD_MASK)
/* WORD Bit Fields */
#define MPU_WORD_VLD_MASK                        0x1u
#define MPU_WORD_VLD_SHIFT                       0
#define MPU_WORD_VLD_WIDTH                       1
#define MPU_WORD_VLD(x)                          (((uint32_t)(((uint32_t)(x))<<MPU_WORD_VLD_SHIFT))&MPU_WORD_VLD_MASK)
#define MPU_WORD_M0UM_MASK                       0x7u
#define MPU_WORD_M0UM_SHIFT                      0
#define MPU_WORD_M0UM_WIDTH                      3
#define MPU_WORD_M0UM(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M0UM_SHIFT))&MPU_WORD_M0UM_MASK)
#define MPU_WORD_M0SM_MASK                       0x18u
#define MPU_WORD_M0SM_SHIFT                      3
#define MPU_WORD_M0SM_WIDTH                      2
#define MPU_WORD_M0SM(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M0SM_SHIFT))&MPU_WORD_M0SM_MASK)
#define MPU_WORD_M0PE_MASK                       0x20u
#define MPU_WORD_M0PE_SHIFT                      5
#define MPU_WORD_M0PE_WIDTH                      1
#define MPU_WORD_M0PE(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M0PE_SHIFT))&MPU_WORD_M0PE_MASK)
#define MPU_WORD_ENDADDR_MASK                    0xFFFFFFE0u
#define MPU_WORD_ENDADDR_SHIFT                   5
#define MPU_WORD_ENDADDR_WIDTH                   27
#define MPU_WORD_ENDADDR(x)                      (((uint32_t)(((uint32_t)(x))<<MPU_WORD_ENDADDR_SHIFT))&MPU_WORD_ENDADDR_MASK)
#define MPU_WORD_SRTADDR_MASK                    0xFFFFFFE0u
#define MPU_WORD_SRTADDR_SHIFT                   5
#define MPU_WORD_SRTADDR_WIDTH                   27
#define MPU_WORD_SRTADDR(x)                      (((uint32_t)(((uint32_t)(x))<<MPU_WORD_SRTADDR_SHIFT))&MPU_WORD_SRTADDR_MASK)
#define MPU_WORD_M1UM_MASK                       0x1C0u
#define MPU_WORD_M1UM_SHIFT                      6
#define MPU_WORD_M1UM_WIDTH                      3
#define MPU_WORD_M1UM(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M1UM_SHIFT))&MPU_WORD_M1UM_MASK)
#define MPU_WORD_M1SM_MASK                       0x600u
#define MPU_WORD_M1SM_SHIFT                      9
#define MPU_WORD_M1SM_WIDTH                      2
#define MPU_WORD_M1SM(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M1SM_SHIFT))&MPU_WORD_M1SM_MASK)
#define MPU_WORD_M1PE_MASK                       0x800u
#define MPU_WORD_M1PE_SHIFT                      11
#define MPU_WORD_M1PE_WIDTH                      1
#define MPU_WORD_M1PE(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M1PE_SHIFT))&MPU_WORD_M1PE_MASK)
#define MPU_WORD_M2UM_MASK                       0x7000u
#define MPU_WORD_M2UM_SHIFT                      12
#define MPU_WORD_M2UM_WIDTH                      3
#define MPU_WORD_M2UM(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M2UM_SHIFT))&MPU_WORD_M2UM_MASK)
#define MPU_WORD_M2SM_MASK                       0x18000u
#define MPU_WORD_M2SM_SHIFT                      15
#define MPU_WORD_M2SM_WIDTH                      2
#define MPU_WORD_M2SM(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M2SM_SHIFT))&MPU_WORD_M2SM_MASK)
#define MPU_WORD_PIDMASK_MASK                    0xFF0000u
#define MPU_WORD_PIDMASK_SHIFT                   16
#define MPU_WORD_PIDMASK_WIDTH                   8
#define MPU_WORD_PIDMASK(x)                      (((uint32_t)(((uint32_t)(x))<<MPU_WORD_PIDMASK_SHIFT))&MPU_WORD_PIDMASK_MASK)
#define MPU_WORD_M2PE_MASK                       0x20000u
#define MPU_WORD_M2PE_SHIFT                      17
#define MPU_WORD_M2PE_WIDTH                      1
#define MPU_WORD_M2PE(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M2PE_SHIFT))&MPU_WORD_M2PE_MASK)
#define MPU_WORD_M3UM_MASK                       0x1C0000u
#define MPU_WORD_M3UM_SHIFT                      18
#define MPU_WORD_M3UM_WIDTH                      3
#define MPU_WORD_M3UM(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M3UM_SHIFT))&MPU_WORD_M3UM_MASK)
#define MPU_WORD_M3SM_MASK                       0x600000u
#define MPU_WORD_M3SM_SHIFT                      21
#define MPU_WORD_M3SM_WIDTH                      2
#define MPU_WORD_M3SM(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M3SM_SHIFT))&MPU_WORD_M3SM_MASK)
#define MPU_WORD_M3PE_MASK                       0x800000u
#define MPU_WORD_M3PE_SHIFT                      23
#define MPU_WORD_M3PE_WIDTH                      1
#define MPU_WORD_M3PE(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M3PE_SHIFT))&MPU_WORD_M3PE_MASK)
#define MPU_WORD_PID_MASK                        0xFF000000u
#define MPU_WORD_PID_SHIFT                       24
#define MPU_WORD_PID_WIDTH                       8
#define MPU_WORD_PID(x)                          (((uint32_t)(((uint32_t)(x))<<MPU_WORD_PID_SHIFT))&MPU_WORD_PID_MASK)
#define MPU_WORD_M4WE_MASK                       0x1000000u
#define MPU_WORD_M4WE_SHIFT                      24
#define MPU_WORD_M4WE_WIDTH                      1
#define MPU_WORD_M4WE(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M4WE_SHIFT))&MPU_WORD_M4WE_MASK)
#define MPU_WORD_M4RE_MASK                       0x2000000u
#define MPU_WORD_M4RE_SHIFT                      25
#define MPU_WORD_M4RE_WIDTH                      1
#define MPU_WORD_M4RE(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M4RE_SHIFT))&MPU_WORD_M4RE_MASK)
#define MPU_WORD_M5WE_MASK                       0x4000000u
#define MPU_WORD_M5WE_SHIFT                      26
#define MPU_WORD_M5WE_WIDTH                      1
#define MPU_WORD_M5WE(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M5WE_SHIFT))&MPU_WORD_M5WE_MASK)
#define MPU_WORD_M5RE_MASK                       0x8000000u
#define MPU_WORD_M5RE_SHIFT                      27
#define MPU_WORD_M5RE_WIDTH                      1
#define MPU_WORD_M5RE(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M5RE_SHIFT))&MPU_WORD_M5RE_MASK)
#define MPU_WORD_M6WE_MASK                       0x10000000u
#define MPU_WORD_M6WE_SHIFT                      28
#define MPU_WORD_M6WE_WIDTH                      1
#define MPU_WORD_M6WE(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M6WE_SHIFT))&MPU_WORD_M6WE_MASK)
#define MPU_WORD_M6RE_MASK                       0x20000000u
#define MPU_WORD_M6RE_SHIFT                      29
#define MPU_WORD_M6RE_WIDTH                      1
#define MPU_WORD_M6RE(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M6RE_SHIFT))&MPU_WORD_M6RE_MASK)
#define MPU_WORD_M7WE_MASK                       0x40000000u
#define MPU_WORD_M7WE_SHIFT                      30
#define MPU_WORD_M7WE_WIDTH                      1
#define MPU_WORD_M7WE(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M7WE_SHIFT))&MPU_WORD_M7WE_MASK)
#define MPU_WORD_M7RE_MASK                       0x80000000u
#define MPU_WORD_M7RE_SHIFT                      31
#define MPU_WORD_M7RE_WIDTH                      1
#define MPU_WORD_M7RE(x)                         (((uint32_t)(((uint32_t)(x))<<MPU_WORD_M7RE_SHIFT))&MPU_WORD_M7RE_MASK)
/* RGDAAC Bit Fields */
#define MPU_RGDAAC_M0UM_MASK                     0x7u
#define MPU_RGDAAC_M0UM_SHIFT                    0
#define MPU_RGDAAC_M0UM_WIDTH                    3
#define MPU_RGDAAC_M0UM(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M0UM_SHIFT))&MPU_RGDAAC_M0UM_MASK)
#define MPU_RGDAAC_M0SM_MASK                     0x18u
#define MPU_RGDAAC_M0SM_SHIFT                    3
#define MPU_RGDAAC_M0SM_WIDTH                    2
#define MPU_RGDAAC_M0SM(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M0SM_SHIFT))&MPU_RGDAAC_M0SM_MASK)
#define MPU_RGDAAC_M0PE_MASK                     0x20u
#define MPU_RGDAAC_M0PE_SHIFT                    5
#define MPU_RGDAAC_M0PE_WIDTH                    1
#define MPU_RGDAAC_M0PE(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M0PE_SHIFT))&MPU_RGDAAC_M0PE_MASK)
#define MPU_RGDAAC_M1UM_MASK                     0x1C0u
#define MPU_RGDAAC_M1UM_SHIFT                    6
#define MPU_RGDAAC_M1UM_WIDTH                    3
#define MPU_RGDAAC_M1UM(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M1UM_SHIFT))&MPU_RGDAAC_M1UM_MASK)
#define MPU_RGDAAC_M1SM_MASK                     0x600u
#define MPU_RGDAAC_M1SM_SHIFT                    9
#define MPU_RGDAAC_M1SM_WIDTH                    2
#define MPU_RGDAAC_M1SM(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M1SM_SHIFT))&MPU_RGDAAC_M1SM_MASK)
#define MPU_RGDAAC_M1PE_MASK                     0x800u
#define MPU_RGDAAC_M1PE_SHIFT                    11
#define MPU_RGDAAC_M1PE_WIDTH                    1
#define MPU_RGDAAC_M1PE(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M1PE_SHIFT))&MPU_RGDAAC_M1PE_MASK)
#define MPU_RGDAAC_M2UM_MASK                     0x7000u
#define MPU_RGDAAC_M2UM_SHIFT                    12
#define MPU_RGDAAC_M2UM_WIDTH                    3
#define MPU_RGDAAC_M2UM(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M2UM_SHIFT))&MPU_RGDAAC_M2UM_MASK)
#define MPU_RGDAAC_M2SM_MASK                     0x18000u
#define MPU_RGDAAC_M2SM_SHIFT                    15
#define MPU_RGDAAC_M2SM_WIDTH                    2
#define MPU_RGDAAC_M2SM(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M2SM_SHIFT))&MPU_RGDAAC_M2SM_MASK)
#define MPU_RGDAAC_M2PE_MASK                     0x20000u
#define MPU_RGDAAC_M2PE_SHIFT                    17
#define MPU_RGDAAC_M2PE_WIDTH                    1
#define MPU_RGDAAC_M2PE(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M2PE_SHIFT))&MPU_RGDAAC_M2PE_MASK)
#define MPU_RGDAAC_M3UM_MASK                     0x1C0000u
#define MPU_RGDAAC_M3UM_SHIFT                    18
#define MPU_RGDAAC_M3UM_WIDTH                    3
#define MPU_RGDAAC_M3UM(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M3UM_SHIFT))&MPU_RGDAAC_M3UM_MASK)
#define MPU_RGDAAC_M3SM_MASK                     0x600000u
#define MPU_RGDAAC_M3SM_SHIFT                    21
#define MPU_RGDAAC_M3SM_WIDTH                    2
#define MPU_RGDAAC_M3SM(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M3SM_SHIFT))&MPU_RGDAAC_M3SM_MASK)
#define MPU_RGDAAC_M3PE_MASK                     0x800000u
#define MPU_RGDAAC_M3PE_SHIFT                    23
#define MPU_RGDAAC_M3PE_WIDTH                    1
#define MPU_RGDAAC_M3PE(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M3PE_SHIFT))&MPU_RGDAAC_M3PE_MASK)
#define MPU_RGDAAC_M4WE_MASK                     0x1000000u
#define MPU_RGDAAC_M4WE_SHIFT                    24
#define MPU_RGDAAC_M4WE_WIDTH                    1
#define MPU_RGDAAC_M4WE(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M4WE_SHIFT))&MPU_RGDAAC_M4WE_MASK)
#define MPU_RGDAAC_M4RE_MASK                     0x2000000u
#define MPU_RGDAAC_M4RE_SHIFT                    25
#define MPU_RGDAAC_M4RE_WIDTH                    1
#define MPU_RGDAAC_M4RE(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M4RE_SHIFT))&MPU_RGDAAC_M4RE_MASK)
#define MPU_RGDAAC_M5WE_MASK                     0x4000000u
#define MPU_RGDAAC_M5WE_SHIFT                    26
#define MPU_RGDAAC_M5WE_WIDTH                    1
#define MPU_RGDAAC_M5WE(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M5WE_SHIFT))&MPU_RGDAAC_M5WE_MASK)
#define MPU_RGDAAC_M5RE_MASK                     0x8000000u
#define MPU_RGDAAC_M5RE_SHIFT                    27
#define MPU_RGDAAC_M5RE_WIDTH                    1
#define MPU_RGDAAC_M5RE(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M5RE_SHIFT))&MPU_RGDAAC_M5RE_MASK)
#define MPU_RGDAAC_M6WE_MASK                     0x10000000u
#define MPU_RGDAAC_M6WE_SHIFT                    28
#define MPU_RGDAAC_M6WE_WIDTH                    1
#define MPU_RGDAAC_M6WE(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M6WE_SHIFT))&MPU_RGDAAC_M6WE_MASK)
#define MPU_RGDAAC_M6RE_MASK                     0x20000000u
#define MPU_RGDAAC_M6RE_SHIFT                    29
#define MPU_RGDAAC_M6RE_WIDTH                    1
#define MPU_RGDAAC_M6RE(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M6RE_SHIFT))&MPU_RGDAAC_M6RE_MASK)
#define MPU_RGDAAC_M7WE_MASK                     0x40000000u
#define MPU_RGDAAC_M7WE_SHIFT                    30
#define MPU_RGDAAC_M7WE_WIDTH                    1
#define MPU_RGDAAC_M7WE(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M7WE_SHIFT))&MPU_RGDAAC_M7WE_MASK)
#define MPU_RGDAAC_M7RE_MASK                     0x80000000u
#define MPU_RGDAAC_M7RE_SHIFT                    31
#define MPU_RGDAAC_M7RE_WIDTH                    1
#define MPU_RGDAAC_M7RE(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RGDAAC_M7RE_SHIFT))&MPU_RGDAAC_M7RE_MASK)

/*!
 * @}
 */ /* end of group MPU_Register_Masks */


/* MPU - Peripheral instance base addresses */
/** Peripheral MPU base address */
#define MPU_BASE                                 (0x4000A000u)
/** Peripheral MPU base pointer */
#define MPU                                      ((MPU_Type *)MPU_BASE)
#define MPU_BASE_PTR                             (MPU)
/** Array initializer of MPU peripheral base addresses */
#define MPU_BASE_ADDRS                           { MPU_BASE }
/** Array initializer of MPU peripheral base pointers */
#define MPU_BASE_PTRS                            { MPU }

/* ----------------------------------------------------------------------------
   -- MPU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MPU_Register_Accessor_Macros MPU - Register accessor macros
 * @{
 */


/* MPU - Register instance definitions */
/* MPU */
#define MPU_CESR                                 MPU_CESR_REG(MPU)
#define MPU_EAR0                                 MPU_EAR_REG(MPU,0)
#define MPU_EDR0                                 MPU_EDR_REG(MPU,0)
#define MPU_EAR1                                 MPU_EAR_REG(MPU,1)
#define MPU_EDR1                                 MPU_EDR_REG(MPU,1)
#define MPU_RGD0_WORD0                           MPU_WORD_REG(MPU,0,0)
#define MPU_RGD0_WORD1                           MPU_WORD_REG(MPU,0,1)
#define MPU_RGD0_WORD2                           MPU_WORD_REG(MPU,0,2)
#define MPU_RGD0_WORD3                           MPU_WORD_REG(MPU,0,3)
#define MPU_RGD1_WORD0                           MPU_WORD_REG(MPU,1,0)
#define MPU_RGD1_WORD1                           MPU_WORD_REG(MPU,1,1)
#define MPU_RGD1_WORD2                           MPU_WORD_REG(MPU,1,2)
#define MPU_RGD1_WORD3                           MPU_WORD_REG(MPU,1,3)
#define MPU_RGD2_WORD0                           MPU_WORD_REG(MPU,2,0)
#define MPU_RGD2_WORD1                           MPU_WORD_REG(MPU,2,1)
#define MPU_RGD2_WORD2                           MPU_WORD_REG(MPU,2,2)
#define MPU_RGD2_WORD3                           MPU_WORD_REG(MPU,2,3)
#define MPU_RGD3_WORD0                           MPU_WORD_REG(MPU,3,0)
#define MPU_RGD3_WORD1                           MPU_WORD_REG(MPU,3,1)
#define MPU_RGD3_WORD2                           MPU_WORD_REG(MPU,3,2)
#define MPU_RGD3_WORD3                           MPU_WORD_REG(MPU,3,3)
#define MPU_RGD4_WORD0                           MPU_WORD_REG(MPU,4,0)
#define MPU_RGD4_WORD1                           MPU_WORD_REG(MPU,4,1)
#define MPU_RGD4_WORD2                           MPU_WORD_REG(MPU,4,2)
#define MPU_RGD4_WORD3                           MPU_WORD_REG(MPU,4,3)
#define MPU_RGD5_WORD0                           MPU_WORD_REG(MPU,5,0)
#define MPU_RGD5_WORD1                           MPU_WORD_REG(MPU,5,1)
#define MPU_RGD5_WORD2                           MPU_WORD_REG(MPU,5,2)
#define MPU_RGD5_WORD3                           MPU_WORD_REG(MPU,5,3)
#define MPU_RGD6_WORD0                           MPU_WORD_REG(MPU,6,0)
#define MPU_RGD6_WORD1                           MPU_WORD_REG(MPU,6,1)
#define MPU_RGD6_WORD2                           MPU_WORD_REG(MPU,6,2)
#define MPU_RGD6_WORD3                           MPU_WORD_REG(MPU,6,3)
#define MPU_RGD7_WORD0                           MPU_WORD_REG(MPU,7,0)
#define MPU_RGD7_WORD1                           MPU_WORD_REG(MPU,7,1)
#define MPU_RGD7_WORD2                           MPU_WORD_REG(MPU,7,2)
#define MPU_RGD7_WORD3                           MPU_WORD_REG(MPU,7,3)
#define MPU_RGDAAC0                              MPU_RGDAAC_REG(MPU,0)
#define MPU_RGDAAC1                              MPU_RGDAAC_REG(MPU,1)
#define MPU_RGDAAC2                              MPU_RGDAAC_REG(MPU,2)
#define MPU_RGDAAC3                              MPU_RGDAAC_REG(MPU,3)
#define MPU_RGDAAC4                              MPU_RGDAAC_REG(MPU,4)
#define MPU_RGDAAC5                              MPU_RGDAAC_REG(MPU,5)
#define MPU_RGDAAC6                              MPU_RGDAAC_REG(MPU,6)
#define MPU_RGDAAC7                              MPU_RGDAAC_REG(MPU,7)

/* MPU - Register array accessors */
#define MPU_EAR(index)                           MPU_EAR_REG(MPU,index)
#define MPU_EDR(index)                           MPU_EDR_REG(MPU,index)
#define MPU_WORD(index,index2)                   MPU_WORD_REG(MPU,index,index2)
#define MPU_RGDAAC(index)                        MPU_RGDAAC_REG(MPU,index)

/*!
 * @}
 */ /* end of group MPU_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group MPU_Peripheral_Access_Layer */


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
  __I  uint32_t PERIPHID[8];                       /**< Peripheral ID Register, array offset: 0xFD0, array step: 0x4 */
  __I  uint32_t COMPID[4];                         /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} MTB_Type, *MTB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MTB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_Register_Accessor_Macros MTB - Register accessor macros
 * @{
 */


/* MTB - Register accessors */
#define MTB_POSITION_REG(base)                   ((base)->POSITION)
#define MTB_MASTER_REG(base)                     ((base)->MASTER)
#define MTB_FLOW_REG(base)                       ((base)->FLOW)
#define MTB_BASE_REG(base)                       ((base)->BASE)
#define MTB_MODECTRL_REG(base)                   ((base)->MODECTRL)
#define MTB_TAGSET_REG(base)                     ((base)->TAGSET)
#define MTB_TAGCLEAR_REG(base)                   ((base)->TAGCLEAR)
#define MTB_LOCKACCESS_REG(base)                 ((base)->LOCKACCESS)
#define MTB_LOCKSTAT_REG(base)                   ((base)->LOCKSTAT)
#define MTB_AUTHSTAT_REG(base)                   ((base)->AUTHSTAT)
#define MTB_DEVICEARCH_REG(base)                 ((base)->DEVICEARCH)
#define MTB_DEVICECFG_REG(base)                  ((base)->DEVICECFG)
#define MTB_DEVICETYPID_REG(base)                ((base)->DEVICETYPID)
#define MTB_PERIPHID_REG(base,index)             ((base)->PERIPHID[index])
#define MTB_PERIPHID_COUNT                       8
#define MTB_COMPID_REG(base,index)               ((base)->COMPID[index])
#define MTB_COMPID_COUNT                         4

/*!
 * @}
 */ /* end of group MTB_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MTB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_Register_Masks MTB Register Masks
 * @{
 */

/* POSITION Bit Fields */
#define MTB_POSITION_WRAP_MASK                   0x4u
#define MTB_POSITION_WRAP_SHIFT                  2
#define MTB_POSITION_WRAP_WIDTH                  1
#define MTB_POSITION_WRAP(x)                     (((uint32_t)(((uint32_t)(x))<<MTB_POSITION_WRAP_SHIFT))&MTB_POSITION_WRAP_MASK)
#define MTB_POSITION_POINTER_MASK                0xFFFFFFF8u
#define MTB_POSITION_POINTER_SHIFT               3
#define MTB_POSITION_POINTER_WIDTH               29
#define MTB_POSITION_POINTER(x)                  (((uint32_t)(((uint32_t)(x))<<MTB_POSITION_POINTER_SHIFT))&MTB_POSITION_POINTER_MASK)
/* MASTER Bit Fields */
#define MTB_MASTER_MASK_MASK                     0x1Fu
#define MTB_MASTER_MASK_SHIFT                    0
#define MTB_MASTER_MASK_WIDTH                    5
#define MTB_MASTER_MASK(x)                       (((uint32_t)(((uint32_t)(x))<<MTB_MASTER_MASK_SHIFT))&MTB_MASTER_MASK_MASK)
#define MTB_MASTER_TSTARTEN_MASK                 0x20u
#define MTB_MASTER_TSTARTEN_SHIFT                5
#define MTB_MASTER_TSTARTEN_WIDTH                1
#define MTB_MASTER_TSTARTEN(x)                   (((uint32_t)(((uint32_t)(x))<<MTB_MASTER_TSTARTEN_SHIFT))&MTB_MASTER_TSTARTEN_MASK)
#define MTB_MASTER_TSTOPEN_MASK                  0x40u
#define MTB_MASTER_TSTOPEN_SHIFT                 6
#define MTB_MASTER_TSTOPEN_WIDTH                 1
#define MTB_MASTER_TSTOPEN(x)                    (((uint32_t)(((uint32_t)(x))<<MTB_MASTER_TSTOPEN_SHIFT))&MTB_MASTER_TSTOPEN_MASK)
#define MTB_MASTER_SFRWPRIV_MASK                 0x80u
#define MTB_MASTER_SFRWPRIV_SHIFT                7
#define MTB_MASTER_SFRWPRIV_WIDTH                1
#define MTB_MASTER_SFRWPRIV(x)                   (((uint32_t)(((uint32_t)(x))<<MTB_MASTER_SFRWPRIV_SHIFT))&MTB_MASTER_SFRWPRIV_MASK)
#define MTB_MASTER_RAMPRIV_MASK                  0x100u
#define MTB_MASTER_RAMPRIV_SHIFT                 8
#define MTB_MASTER_RAMPRIV_WIDTH                 1
#define MTB_MASTER_RAMPRIV(x)                    (((uint32_t)(((uint32_t)(x))<<MTB_MASTER_RAMPRIV_SHIFT))&MTB_MASTER_RAMPRIV_MASK)
#define MTB_MASTER_HALTREQ_MASK                  0x200u
#define MTB_MASTER_HALTREQ_SHIFT                 9
#define MTB_MASTER_HALTREQ_WIDTH                 1
#define MTB_MASTER_HALTREQ(x)                    (((uint32_t)(((uint32_t)(x))<<MTB_MASTER_HALTREQ_SHIFT))&MTB_MASTER_HALTREQ_MASK)
#define MTB_MASTER_EN_MASK                       0x80000000u
#define MTB_MASTER_EN_SHIFT                      31
#define MTB_MASTER_EN_WIDTH                      1
#define MTB_MASTER_EN(x)                         (((uint32_t)(((uint32_t)(x))<<MTB_MASTER_EN_SHIFT))&MTB_MASTER_EN_MASK)
/* FLOW Bit Fields */
#define MTB_FLOW_AUTOSTOP_MASK                   0x1u
#define MTB_FLOW_AUTOSTOP_SHIFT                  0
#define MTB_FLOW_AUTOSTOP_WIDTH                  1
#define MTB_FLOW_AUTOSTOP(x)                     (((uint32_t)(((uint32_t)(x))<<MTB_FLOW_AUTOSTOP_SHIFT))&MTB_FLOW_AUTOSTOP_MASK)
#define MTB_FLOW_AUTOHALT_MASK                   0x2u
#define MTB_FLOW_AUTOHALT_SHIFT                  1
#define MTB_FLOW_AUTOHALT_WIDTH                  1
#define MTB_FLOW_AUTOHALT(x)                     (((uint32_t)(((uint32_t)(x))<<MTB_FLOW_AUTOHALT_SHIFT))&MTB_FLOW_AUTOHALT_MASK)
#define MTB_FLOW_WATERMARK_MASK                  0xFFFFFFF8u
#define MTB_FLOW_WATERMARK_SHIFT                 3
#define MTB_FLOW_WATERMARK_WIDTH                 29
#define MTB_FLOW_WATERMARK(x)                    (((uint32_t)(((uint32_t)(x))<<MTB_FLOW_WATERMARK_SHIFT))&MTB_FLOW_WATERMARK_MASK)
/* BASE Bit Fields */
#define MTB_BASE_BASEADDR_MASK                   0xFFFFFFFFu
#define MTB_BASE_BASEADDR_SHIFT                  0
#define MTB_BASE_BASEADDR_WIDTH                  32
#define MTB_BASE_BASEADDR(x)                     (((uint32_t)(((uint32_t)(x))<<MTB_BASE_BASEADDR_SHIFT))&MTB_BASE_BASEADDR_MASK)
/* MODECTRL Bit Fields */
#define MTB_MODECTRL_MODECTRL_MASK               0xFFFFFFFFu
#define MTB_MODECTRL_MODECTRL_SHIFT              0
#define MTB_MODECTRL_MODECTRL_WIDTH              32
#define MTB_MODECTRL_MODECTRL(x)                 (((uint32_t)(((uint32_t)(x))<<MTB_MODECTRL_MODECTRL_SHIFT))&MTB_MODECTRL_MODECTRL_MASK)
/* TAGSET Bit Fields */
#define MTB_TAGSET_TAGSET_MASK                   0xFFFFFFFFu
#define MTB_TAGSET_TAGSET_SHIFT                  0
#define MTB_TAGSET_TAGSET_WIDTH                  32
#define MTB_TAGSET_TAGSET(x)                     (((uint32_t)(((uint32_t)(x))<<MTB_TAGSET_TAGSET_SHIFT))&MTB_TAGSET_TAGSET_MASK)
/* TAGCLEAR Bit Fields */
#define MTB_TAGCLEAR_TAGCLEAR_MASK               0xFFFFFFFFu
#define MTB_TAGCLEAR_TAGCLEAR_SHIFT              0
#define MTB_TAGCLEAR_TAGCLEAR_WIDTH              32
#define MTB_TAGCLEAR_TAGCLEAR(x)                 (((uint32_t)(((uint32_t)(x))<<MTB_TAGCLEAR_TAGCLEAR_SHIFT))&MTB_TAGCLEAR_TAGCLEAR_MASK)
/* LOCKACCESS Bit Fields */
#define MTB_LOCKACCESS_LOCKACCESS_MASK           0xFFFFFFFFu
#define MTB_LOCKACCESS_LOCKACCESS_SHIFT          0
#define MTB_LOCKACCESS_LOCKACCESS_WIDTH          32
#define MTB_LOCKACCESS_LOCKACCESS(x)             (((uint32_t)(((uint32_t)(x))<<MTB_LOCKACCESS_LOCKACCESS_SHIFT))&MTB_LOCKACCESS_LOCKACCESS_MASK)
/* LOCKSTAT Bit Fields */
#define MTB_LOCKSTAT_LOCKSTAT_MASK               0xFFFFFFFFu
#define MTB_LOCKSTAT_LOCKSTAT_SHIFT              0
#define MTB_LOCKSTAT_LOCKSTAT_WIDTH              32
#define MTB_LOCKSTAT_LOCKSTAT(x)                 (((uint32_t)(((uint32_t)(x))<<MTB_LOCKSTAT_LOCKSTAT_SHIFT))&MTB_LOCKSTAT_LOCKSTAT_MASK)
/* AUTHSTAT Bit Fields */
#define MTB_AUTHSTAT_BIT0_MASK                   0x1u
#define MTB_AUTHSTAT_BIT0_SHIFT                  0
#define MTB_AUTHSTAT_BIT0_WIDTH                  1
#define MTB_AUTHSTAT_BIT0(x)                     (((uint32_t)(((uint32_t)(x))<<MTB_AUTHSTAT_BIT0_SHIFT))&MTB_AUTHSTAT_BIT0_MASK)
#define MTB_AUTHSTAT_BIT1_MASK                   0x2u
#define MTB_AUTHSTAT_BIT1_SHIFT                  1
#define MTB_AUTHSTAT_BIT1_WIDTH                  1
#define MTB_AUTHSTAT_BIT1(x)                     (((uint32_t)(((uint32_t)(x))<<MTB_AUTHSTAT_BIT1_SHIFT))&MTB_AUTHSTAT_BIT1_MASK)
#define MTB_AUTHSTAT_BIT2_MASK                   0x4u
#define MTB_AUTHSTAT_BIT2_SHIFT                  2
#define MTB_AUTHSTAT_BIT2_WIDTH                  1
#define MTB_AUTHSTAT_BIT2(x)                     (((uint32_t)(((uint32_t)(x))<<MTB_AUTHSTAT_BIT2_SHIFT))&MTB_AUTHSTAT_BIT2_MASK)
#define MTB_AUTHSTAT_BIT3_MASK                   0x8u
#define MTB_AUTHSTAT_BIT3_SHIFT                  3
#define MTB_AUTHSTAT_BIT3_WIDTH                  1
#define MTB_AUTHSTAT_BIT3(x)                     (((uint32_t)(((uint32_t)(x))<<MTB_AUTHSTAT_BIT3_SHIFT))&MTB_AUTHSTAT_BIT3_MASK)
/* DEVICEARCH Bit Fields */
#define MTB_DEVICEARCH_DEVICEARCH_MASK           0xFFFFFFFFu
#define MTB_DEVICEARCH_DEVICEARCH_SHIFT          0
#define MTB_DEVICEARCH_DEVICEARCH_WIDTH          32
#define MTB_DEVICEARCH_DEVICEARCH(x)             (((uint32_t)(((uint32_t)(x))<<MTB_DEVICEARCH_DEVICEARCH_SHIFT))&MTB_DEVICEARCH_DEVICEARCH_MASK)
/* DEVICECFG Bit Fields */
#define MTB_DEVICECFG_DEVICECFG_MASK             0xFFFFFFFFu
#define MTB_DEVICECFG_DEVICECFG_SHIFT            0
#define MTB_DEVICECFG_DEVICECFG_WIDTH            32
#define MTB_DEVICECFG_DEVICECFG(x)               (((uint32_t)(((uint32_t)(x))<<MTB_DEVICECFG_DEVICECFG_SHIFT))&MTB_DEVICECFG_DEVICECFG_MASK)
/* DEVICETYPID Bit Fields */
#define MTB_DEVICETYPID_DEVICETYPID_MASK         0xFFFFFFFFu
#define MTB_DEVICETYPID_DEVICETYPID_SHIFT        0
#define MTB_DEVICETYPID_DEVICETYPID_WIDTH        32
#define MTB_DEVICETYPID_DEVICETYPID(x)           (((uint32_t)(((uint32_t)(x))<<MTB_DEVICETYPID_DEVICETYPID_SHIFT))&MTB_DEVICETYPID_DEVICETYPID_MASK)
/* PERIPHID Bit Fields */
#define MTB_PERIPHID_PERIPHID_MASK               0xFFFFFFFFu
#define MTB_PERIPHID_PERIPHID_SHIFT              0
#define MTB_PERIPHID_PERIPHID_WIDTH              32
#define MTB_PERIPHID_PERIPHID(x)                 (((uint32_t)(((uint32_t)(x))<<MTB_PERIPHID_PERIPHID_SHIFT))&MTB_PERIPHID_PERIPHID_MASK)
/* COMPID Bit Fields */
#define MTB_COMPID_COMPID_MASK                   0xFFFFFFFFu
#define MTB_COMPID_COMPID_SHIFT                  0
#define MTB_COMPID_COMPID_WIDTH                  32
#define MTB_COMPID_COMPID(x)                     (((uint32_t)(((uint32_t)(x))<<MTB_COMPID_COMPID_SHIFT))&MTB_COMPID_COMPID_MASK)

/*!
 * @}
 */ /* end of group MTB_Register_Masks */


/* MTB - Peripheral instance base addresses */
/** Peripheral MTB base address */
#define MTB_BASE                                 (0xF0000000u)
/** Peripheral MTB base pointer */
#define MTB                                      ((MTB_Type *)MTB_BASE)
#define MTB_BASE_PTR                             (MTB)
/** Array initializer of MTB peripheral base addresses */
#define MTB_BASE_ADDRS                           { MTB_BASE }
/** Array initializer of MTB peripheral base pointers */
#define MTB_BASE_PTRS                            { MTB }

/* ----------------------------------------------------------------------------
   -- MTB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_Register_Accessor_Macros MTB - Register accessor macros
 * @{
 */


/* MTB - Register instance definitions */
/* MTB */
#define MTB_POSITION                             MTB_POSITION_REG(MTB)
#define MTB_MASTER                               MTB_MASTER_REG(MTB)
#define MTB_FLOW                                 MTB_FLOW_REG(MTB)
#define MTB_BASEr                                MTB_BASE_REG(MTB)
#define MTB_MODECTRL                             MTB_MODECTRL_REG(MTB)
#define MTB_TAGSET                               MTB_TAGSET_REG(MTB)
#define MTB_TAGCLEAR                             MTB_TAGCLEAR_REG(MTB)
#define MTB_LOCKACCESS                           MTB_LOCKACCESS_REG(MTB)
#define MTB_LOCKSTAT                             MTB_LOCKSTAT_REG(MTB)
#define MTB_AUTHSTAT                             MTB_AUTHSTAT_REG(MTB)
#define MTB_DEVICEARCH                           MTB_DEVICEARCH_REG(MTB)
#define MTB_DEVICECFG                            MTB_DEVICECFG_REG(MTB)
#define MTB_DEVICETYPID                          MTB_DEVICETYPID_REG(MTB)
#define MTB_PERIPHID4                            MTB_PERIPHID_REG(MTB,0)
#define MTB_PERIPHID5                            MTB_PERIPHID_REG(MTB,1)
#define MTB_PERIPHID6                            MTB_PERIPHID_REG(MTB,2)
#define MTB_PERIPHID7                            MTB_PERIPHID_REG(MTB,3)
#define MTB_PERIPHID0                            MTB_PERIPHID_REG(MTB,4)
#define MTB_PERIPHID1                            MTB_PERIPHID_REG(MTB,5)
#define MTB_PERIPHID2                            MTB_PERIPHID_REG(MTB,6)
#define MTB_PERIPHID3                            MTB_PERIPHID_REG(MTB,7)
#define MTB_COMPID0                              MTB_COMPID_REG(MTB,0)
#define MTB_COMPID1                              MTB_COMPID_REG(MTB,1)
#define MTB_COMPID2                              MTB_COMPID_REG(MTB,2)
#define MTB_COMPID3                              MTB_COMPID_REG(MTB,3)

/* MTB - Register array accessors */
#define MTB_PERIPHID(index)                      MTB_PERIPHID_REG(MTB,index)
#define MTB_COMPID(index)                        MTB_COMPID_REG(MTB,index)

/*!
 * @}
 */ /* end of group MTB_Register_Accessor_Macros */


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
  __I  uint32_t PERIPHID[8];                       /**< Peripheral ID Register, array offset: 0xFD0, array step: 0x4 */
  __I  uint32_t COMPID[4];                         /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} MTBDWT_Type, *MTBDWT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MTBDWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTBDWT_Register_Accessor_Macros MTBDWT - Register accessor macros
 * @{
 */


/* MTBDWT - Register accessors */
#define MTBDWT_CTRL_REG(base)                    ((base)->CTRL)
#define MTBDWT_COMP_REG(base,index)              ((base)->COMPARATOR[index].COMP)
#define MTBDWT_COMP_COUNT                        2
#define MTBDWT_MASK_REG(base,index)              ((base)->COMPARATOR[index].MASK)
#define MTBDWT_MASK_COUNT                        2
#define MTBDWT_FCT_REG(base,index)               ((base)->COMPARATOR[index].FCT)
#define MTBDWT_FCT_COUNT                         2
#define MTBDWT_TBCTRL_REG(base)                  ((base)->TBCTRL)
#define MTBDWT_DEVICECFG_REG(base)               ((base)->DEVICECFG)
#define MTBDWT_DEVICETYPID_REG(base)             ((base)->DEVICETYPID)
#define MTBDWT_PERIPHID_REG(base,index)          ((base)->PERIPHID[index])
#define MTBDWT_PERIPHID_COUNT                    8
#define MTBDWT_COMPID_REG(base,index)            ((base)->COMPID[index])
#define MTBDWT_COMPID_COUNT                      4

/*!
 * @}
 */ /* end of group MTBDWT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MTBDWT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTBDWT_Register_Masks MTBDWT Register Masks
 * @{
 */

/* CTRL Bit Fields */
#define MTBDWT_CTRL_DWTCFGCTRL_MASK              0xFFFFFFFu
#define MTBDWT_CTRL_DWTCFGCTRL_SHIFT             0
#define MTBDWT_CTRL_DWTCFGCTRL_WIDTH             28
#define MTBDWT_CTRL_DWTCFGCTRL(x)                (((uint32_t)(((uint32_t)(x))<<MTBDWT_CTRL_DWTCFGCTRL_SHIFT))&MTBDWT_CTRL_DWTCFGCTRL_MASK)
#define MTBDWT_CTRL_NUMCMP_MASK                  0xF0000000u
#define MTBDWT_CTRL_NUMCMP_SHIFT                 28
#define MTBDWT_CTRL_NUMCMP_WIDTH                 4
#define MTBDWT_CTRL_NUMCMP(x)                    (((uint32_t)(((uint32_t)(x))<<MTBDWT_CTRL_NUMCMP_SHIFT))&MTBDWT_CTRL_NUMCMP_MASK)
/* COMP Bit Fields */
#define MTBDWT_COMP_COMP_MASK                    0xFFFFFFFFu
#define MTBDWT_COMP_COMP_SHIFT                   0
#define MTBDWT_COMP_COMP_WIDTH                   32
#define MTBDWT_COMP_COMP(x)                      (((uint32_t)(((uint32_t)(x))<<MTBDWT_COMP_COMP_SHIFT))&MTBDWT_COMP_COMP_MASK)
/* MASK Bit Fields */
#define MTBDWT_MASK_MASK_MASK                    0x1Fu
#define MTBDWT_MASK_MASK_SHIFT                   0
#define MTBDWT_MASK_MASK_WIDTH                   5
#define MTBDWT_MASK_MASK(x)                      (((uint32_t)(((uint32_t)(x))<<MTBDWT_MASK_MASK_SHIFT))&MTBDWT_MASK_MASK_MASK)
/* FCT Bit Fields */
#define MTBDWT_FCT_FUNCTION_MASK                 0xFu
#define MTBDWT_FCT_FUNCTION_SHIFT                0
#define MTBDWT_FCT_FUNCTION_WIDTH                4
#define MTBDWT_FCT_FUNCTION(x)                   (((uint32_t)(((uint32_t)(x))<<MTBDWT_FCT_FUNCTION_SHIFT))&MTBDWT_FCT_FUNCTION_MASK)
#define MTBDWT_FCT_DATAVMATCH_MASK               0x100u
#define MTBDWT_FCT_DATAVMATCH_SHIFT              8
#define MTBDWT_FCT_DATAVMATCH_WIDTH              1
#define MTBDWT_FCT_DATAVMATCH(x)                 (((uint32_t)(((uint32_t)(x))<<MTBDWT_FCT_DATAVMATCH_SHIFT))&MTBDWT_FCT_DATAVMATCH_MASK)
#define MTBDWT_FCT_DATAVSIZE_MASK                0xC00u
#define MTBDWT_FCT_DATAVSIZE_SHIFT               10
#define MTBDWT_FCT_DATAVSIZE_WIDTH               2
#define MTBDWT_FCT_DATAVSIZE(x)                  (((uint32_t)(((uint32_t)(x))<<MTBDWT_FCT_DATAVSIZE_SHIFT))&MTBDWT_FCT_DATAVSIZE_MASK)
#define MTBDWT_FCT_DATAVADDR0_MASK               0xF000u
#define MTBDWT_FCT_DATAVADDR0_SHIFT              12
#define MTBDWT_FCT_DATAVADDR0_WIDTH              4
#define MTBDWT_FCT_DATAVADDR0(x)                 (((uint32_t)(((uint32_t)(x))<<MTBDWT_FCT_DATAVADDR0_SHIFT))&MTBDWT_FCT_DATAVADDR0_MASK)
#define MTBDWT_FCT_MATCHED_MASK                  0x1000000u
#define MTBDWT_FCT_MATCHED_SHIFT                 24
#define MTBDWT_FCT_MATCHED_WIDTH                 1
#define MTBDWT_FCT_MATCHED(x)                    (((uint32_t)(((uint32_t)(x))<<MTBDWT_FCT_MATCHED_SHIFT))&MTBDWT_FCT_MATCHED_MASK)
/* TBCTRL Bit Fields */
#define MTBDWT_TBCTRL_ACOMP0_MASK                0x1u
#define MTBDWT_TBCTRL_ACOMP0_SHIFT               0
#define MTBDWT_TBCTRL_ACOMP0_WIDTH               1
#define MTBDWT_TBCTRL_ACOMP0(x)                  (((uint32_t)(((uint32_t)(x))<<MTBDWT_TBCTRL_ACOMP0_SHIFT))&MTBDWT_TBCTRL_ACOMP0_MASK)
#define MTBDWT_TBCTRL_ACOMP1_MASK                0x2u
#define MTBDWT_TBCTRL_ACOMP1_SHIFT               1
#define MTBDWT_TBCTRL_ACOMP1_WIDTH               1
#define MTBDWT_TBCTRL_ACOMP1(x)                  (((uint32_t)(((uint32_t)(x))<<MTBDWT_TBCTRL_ACOMP1_SHIFT))&MTBDWT_TBCTRL_ACOMP1_MASK)
#define MTBDWT_TBCTRL_NUMCOMP_MASK               0xF0000000u
#define MTBDWT_TBCTRL_NUMCOMP_SHIFT              28
#define MTBDWT_TBCTRL_NUMCOMP_WIDTH              4
#define MTBDWT_TBCTRL_NUMCOMP(x)                 (((uint32_t)(((uint32_t)(x))<<MTBDWT_TBCTRL_NUMCOMP_SHIFT))&MTBDWT_TBCTRL_NUMCOMP_MASK)
/* DEVICECFG Bit Fields */
#define MTBDWT_DEVICECFG_DEVICECFG_MASK          0xFFFFFFFFu
#define MTBDWT_DEVICECFG_DEVICECFG_SHIFT         0
#define MTBDWT_DEVICECFG_DEVICECFG_WIDTH         32
#define MTBDWT_DEVICECFG_DEVICECFG(x)            (((uint32_t)(((uint32_t)(x))<<MTBDWT_DEVICECFG_DEVICECFG_SHIFT))&MTBDWT_DEVICECFG_DEVICECFG_MASK)
/* DEVICETYPID Bit Fields */
#define MTBDWT_DEVICETYPID_DEVICETYPID_MASK      0xFFFFFFFFu
#define MTBDWT_DEVICETYPID_DEVICETYPID_SHIFT     0
#define MTBDWT_DEVICETYPID_DEVICETYPID_WIDTH     32
#define MTBDWT_DEVICETYPID_DEVICETYPID(x)        (((uint32_t)(((uint32_t)(x))<<MTBDWT_DEVICETYPID_DEVICETYPID_SHIFT))&MTBDWT_DEVICETYPID_DEVICETYPID_MASK)
/* PERIPHID Bit Fields */
#define MTBDWT_PERIPHID_PERIPHID_MASK            0xFFFFFFFFu
#define MTBDWT_PERIPHID_PERIPHID_SHIFT           0
#define MTBDWT_PERIPHID_PERIPHID_WIDTH           32
#define MTBDWT_PERIPHID_PERIPHID(x)              (((uint32_t)(((uint32_t)(x))<<MTBDWT_PERIPHID_PERIPHID_SHIFT))&MTBDWT_PERIPHID_PERIPHID_MASK)
/* COMPID Bit Fields */
#define MTBDWT_COMPID_COMPID_MASK                0xFFFFFFFFu
#define MTBDWT_COMPID_COMPID_SHIFT               0
#define MTBDWT_COMPID_COMPID_WIDTH               32
#define MTBDWT_COMPID_COMPID(x)                  (((uint32_t)(((uint32_t)(x))<<MTBDWT_COMPID_COMPID_SHIFT))&MTBDWT_COMPID_COMPID_MASK)

/*!
 * @}
 */ /* end of group MTBDWT_Register_Masks */


/* MTBDWT - Peripheral instance base addresses */
/** Peripheral MTBDWT base address */
#define MTBDWT_BASE                              (0xF0001000u)
/** Peripheral MTBDWT base pointer */
#define MTBDWT                                   ((MTBDWT_Type *)MTBDWT_BASE)
#define MTBDWT_BASE_PTR                          (MTBDWT)
/** Array initializer of MTBDWT peripheral base addresses */
#define MTBDWT_BASE_ADDRS                        { MTBDWT_BASE }
/** Array initializer of MTBDWT peripheral base pointers */
#define MTBDWT_BASE_PTRS                         { MTBDWT }

/* ----------------------------------------------------------------------------
   -- MTBDWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTBDWT_Register_Accessor_Macros MTBDWT - Register accessor macros
 * @{
 */


/* MTBDWT - Register instance definitions */
/* MTBDWT */
#define MTBDWT_CTRL                              MTBDWT_CTRL_REG(MTBDWT)
#define MTBDWT_COMP0                             MTBDWT_COMP_REG(MTBDWT,0)
#define MTBDWT_MASK0                             MTBDWT_MASK_REG(MTBDWT,0)
#define MTBDWT_FCT0                              MTBDWT_FCT_REG(MTBDWT,0)
#define MTBDWT_COMP1                             MTBDWT_COMP_REG(MTBDWT,1)
#define MTBDWT_MASK1                             MTBDWT_MASK_REG(MTBDWT,1)
#define MTBDWT_FCT1                              MTBDWT_FCT_REG(MTBDWT,1)
#define MTBDWT_TBCTRL                            MTBDWT_TBCTRL_REG(MTBDWT)
#define MTBDWT_DEVICECFG                         MTBDWT_DEVICECFG_REG(MTBDWT)
#define MTBDWT_DEVICETYPID                       MTBDWT_DEVICETYPID_REG(MTBDWT)
#define MTBDWT_PERIPHID4                         MTBDWT_PERIPHID_REG(MTBDWT,0)
#define MTBDWT_PERIPHID5                         MTBDWT_PERIPHID_REG(MTBDWT,1)
#define MTBDWT_PERIPHID6                         MTBDWT_PERIPHID_REG(MTBDWT,2)
#define MTBDWT_PERIPHID7                         MTBDWT_PERIPHID_REG(MTBDWT,3)
#define MTBDWT_PERIPHID0                         MTBDWT_PERIPHID_REG(MTBDWT,4)
#define MTBDWT_PERIPHID1                         MTBDWT_PERIPHID_REG(MTBDWT,5)
#define MTBDWT_PERIPHID2                         MTBDWT_PERIPHID_REG(MTBDWT,6)
#define MTBDWT_PERIPHID3                         MTBDWT_PERIPHID_REG(MTBDWT,7)
#define MTBDWT_COMPID0                           MTBDWT_COMPID_REG(MTBDWT,0)
#define MTBDWT_COMPID1                           MTBDWT_COMPID_REG(MTBDWT,1)
#define MTBDWT_COMPID2                           MTBDWT_COMPID_REG(MTBDWT,2)
#define MTBDWT_COMPID3                           MTBDWT_COMPID_REG(MTBDWT,3)

/* MTBDWT - Register array accessors */
#define MTBDWT_COMP(index)                       MTBDWT_COMP_REG(MTBDWT,index)
#define MTBDWT_MASK(index)                       MTBDWT_MASK_REG(MTBDWT,index)
#define MTBDWT_FCT(index)                        MTBDWT_FCT_REG(MTBDWT,index)
#define MTBDWT_PERIPHID(index)                   MTBDWT_PERIPHID_REG(MTBDWT,index)
#define MTBDWT_COMPID(index)                     MTBDWT_COMPID_REG(MTBDWT,index)

/*!
 * @}
 */ /* end of group MTBDWT_Register_Accessor_Macros */


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
} NV_Type, *NV_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register accessors */
#define NV_BACKKEY3_REG(base)                    ((base)->BACKKEY3)
#define NV_BACKKEY2_REG(base)                    ((base)->BACKKEY2)
#define NV_BACKKEY1_REG(base)                    ((base)->BACKKEY1)
#define NV_BACKKEY0_REG(base)                    ((base)->BACKKEY0)
#define NV_BACKKEY7_REG(base)                    ((base)->BACKKEY7)
#define NV_BACKKEY6_REG(base)                    ((base)->BACKKEY6)
#define NV_BACKKEY5_REG(base)                    ((base)->BACKKEY5)
#define NV_BACKKEY4_REG(base)                    ((base)->BACKKEY4)
#define NV_FPROT3_REG(base)                      ((base)->FPROT3)
#define NV_FPROT2_REG(base)                      ((base)->FPROT2)
#define NV_FPROT1_REG(base)                      ((base)->FPROT1)
#define NV_FPROT0_REG(base)                      ((base)->FPROT0)
#define NV_FSEC_REG(base)                        ((base)->FSEC)
#define NV_FOPT_REG(base)                        ((base)->FOPT)

/*!
 * @}
 */ /* end of group NV_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- NV Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Masks NV Register Masks
 * @{
 */

/* BACKKEY3 Bit Fields */
#define NV_BACKKEY3_KEY_MASK                     0xFFu
#define NV_BACKKEY3_KEY_SHIFT                    0
#define NV_BACKKEY3_KEY_WIDTH                    8
#define NV_BACKKEY3_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY3_KEY_SHIFT))&NV_BACKKEY3_KEY_MASK)
/* BACKKEY2 Bit Fields */
#define NV_BACKKEY2_KEY_MASK                     0xFFu
#define NV_BACKKEY2_KEY_SHIFT                    0
#define NV_BACKKEY2_KEY_WIDTH                    8
#define NV_BACKKEY2_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY2_KEY_SHIFT))&NV_BACKKEY2_KEY_MASK)
/* BACKKEY1 Bit Fields */
#define NV_BACKKEY1_KEY_MASK                     0xFFu
#define NV_BACKKEY1_KEY_SHIFT                    0
#define NV_BACKKEY1_KEY_WIDTH                    8
#define NV_BACKKEY1_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY1_KEY_SHIFT))&NV_BACKKEY1_KEY_MASK)
/* BACKKEY0 Bit Fields */
#define NV_BACKKEY0_KEY_MASK                     0xFFu
#define NV_BACKKEY0_KEY_SHIFT                    0
#define NV_BACKKEY0_KEY_WIDTH                    8
#define NV_BACKKEY0_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY0_KEY_SHIFT))&NV_BACKKEY0_KEY_MASK)
/* BACKKEY7 Bit Fields */
#define NV_BACKKEY7_KEY_MASK                     0xFFu
#define NV_BACKKEY7_KEY_SHIFT                    0
#define NV_BACKKEY7_KEY_WIDTH                    8
#define NV_BACKKEY7_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY7_KEY_SHIFT))&NV_BACKKEY7_KEY_MASK)
/* BACKKEY6 Bit Fields */
#define NV_BACKKEY6_KEY_MASK                     0xFFu
#define NV_BACKKEY6_KEY_SHIFT                    0
#define NV_BACKKEY6_KEY_WIDTH                    8
#define NV_BACKKEY6_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY6_KEY_SHIFT))&NV_BACKKEY6_KEY_MASK)
/* BACKKEY5 Bit Fields */
#define NV_BACKKEY5_KEY_MASK                     0xFFu
#define NV_BACKKEY5_KEY_SHIFT                    0
#define NV_BACKKEY5_KEY_WIDTH                    8
#define NV_BACKKEY5_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY5_KEY_SHIFT))&NV_BACKKEY5_KEY_MASK)
/* BACKKEY4 Bit Fields */
#define NV_BACKKEY4_KEY_MASK                     0xFFu
#define NV_BACKKEY4_KEY_SHIFT                    0
#define NV_BACKKEY4_KEY_WIDTH                    8
#define NV_BACKKEY4_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY4_KEY_SHIFT))&NV_BACKKEY4_KEY_MASK)
/* FPROT3 Bit Fields */
#define NV_FPROT3_PROT_MASK                      0xFFu
#define NV_FPROT3_PROT_SHIFT                     0
#define NV_FPROT3_PROT_WIDTH                     8
#define NV_FPROT3_PROT(x)                        (((uint8_t)(((uint8_t)(x))<<NV_FPROT3_PROT_SHIFT))&NV_FPROT3_PROT_MASK)
/* FPROT2 Bit Fields */
#define NV_FPROT2_PROT_MASK                      0xFFu
#define NV_FPROT2_PROT_SHIFT                     0
#define NV_FPROT2_PROT_WIDTH                     8
#define NV_FPROT2_PROT(x)                        (((uint8_t)(((uint8_t)(x))<<NV_FPROT2_PROT_SHIFT))&NV_FPROT2_PROT_MASK)
/* FPROT1 Bit Fields */
#define NV_FPROT1_PROT_MASK                      0xFFu
#define NV_FPROT1_PROT_SHIFT                     0
#define NV_FPROT1_PROT_WIDTH                     8
#define NV_FPROT1_PROT(x)                        (((uint8_t)(((uint8_t)(x))<<NV_FPROT1_PROT_SHIFT))&NV_FPROT1_PROT_MASK)
/* FPROT0 Bit Fields */
#define NV_FPROT0_PROT_MASK                      0xFFu
#define NV_FPROT0_PROT_SHIFT                     0
#define NV_FPROT0_PROT_WIDTH                     8
#define NV_FPROT0_PROT(x)                        (((uint8_t)(((uint8_t)(x))<<NV_FPROT0_PROT_SHIFT))&NV_FPROT0_PROT_MASK)
/* FSEC Bit Fields */
#define NV_FSEC_SEC_MASK                         0x3u
#define NV_FSEC_SEC_SHIFT                        0
#define NV_FSEC_SEC_WIDTH                        2
#define NV_FSEC_SEC(x)                           (((uint8_t)(((uint8_t)(x))<<NV_FSEC_SEC_SHIFT))&NV_FSEC_SEC_MASK)
#define NV_FSEC_FSLACC_MASK                      0xCu
#define NV_FSEC_FSLACC_SHIFT                     2
#define NV_FSEC_FSLACC_WIDTH                     2
#define NV_FSEC_FSLACC(x)                        (((uint8_t)(((uint8_t)(x))<<NV_FSEC_FSLACC_SHIFT))&NV_FSEC_FSLACC_MASK)
#define NV_FSEC_MEEN_MASK                        0x30u
#define NV_FSEC_MEEN_SHIFT                       4
#define NV_FSEC_MEEN_WIDTH                       2
#define NV_FSEC_MEEN(x)                          (((uint8_t)(((uint8_t)(x))<<NV_FSEC_MEEN_SHIFT))&NV_FSEC_MEEN_MASK)
#define NV_FSEC_KEYEN_MASK                       0xC0u
#define NV_FSEC_KEYEN_SHIFT                      6
#define NV_FSEC_KEYEN_WIDTH                      2
#define NV_FSEC_KEYEN(x)                         (((uint8_t)(((uint8_t)(x))<<NV_FSEC_KEYEN_SHIFT))&NV_FSEC_KEYEN_MASK)
/* FOPT Bit Fields */
#define NV_FOPT_LPBOOT_MASK                      0x1u
#define NV_FOPT_LPBOOT_SHIFT                     0
#define NV_FOPT_LPBOOT_WIDTH                     1
#define NV_FOPT_LPBOOT(x)                        (((uint8_t)(((uint8_t)(x))<<NV_FOPT_LPBOOT_SHIFT))&NV_FOPT_LPBOOT_MASK)
#define NV_FOPT_NMI_EN_MASK                      0x4u
#define NV_FOPT_NMI_EN_SHIFT                     2
#define NV_FOPT_NMI_EN_WIDTH                     1
#define NV_FOPT_NMI_EN(x)                        (((uint8_t)(((uint8_t)(x))<<NV_FOPT_NMI_EN_SHIFT))&NV_FOPT_NMI_EN_MASK)
#define NV_FOPT_EXE_MODE_MASK                    0x8u
#define NV_FOPT_EXE_MODE_SHIFT                   3
#define NV_FOPT_EXE_MODE_WIDTH                   1
#define NV_FOPT_EXE_MODE(x)                      (((uint8_t)(((uint8_t)(x))<<NV_FOPT_EXE_MODE_SHIFT))&NV_FOPT_EXE_MODE_MASK)
#define NV_FOPT_CLK_SRC_MASK                     0x20u
#define NV_FOPT_CLK_SRC_SHIFT                    5
#define NV_FOPT_CLK_SRC_WIDTH                    1
#define NV_FOPT_CLK_SRC(x)                       (((uint8_t)(((uint8_t)(x))<<NV_FOPT_CLK_SRC_SHIFT))&NV_FOPT_CLK_SRC_MASK)

/*!
 * @}
 */ /* end of group NV_Register_Masks */


/* NV - Peripheral instance base addresses */
/** Peripheral FTFA_FlashConfig base address */
#define FTFA_FlashConfig_BASE                    (0x400u)
/** Peripheral FTFA_FlashConfig base pointer */
#define FTFA_FlashConfig                         ((NV_Type *)FTFA_FlashConfig_BASE)
#define FTFA_FlashConfig_BASE_PTR                (FTFA_FlashConfig)
/** Array initializer of NV peripheral base addresses */
#define NV_BASE_ADDRS                            { FTFA_FlashConfig_BASE }
/** Array initializer of NV peripheral base pointers */
#define NV_BASE_PTRS                             { FTFA_FlashConfig }

/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register instance definitions */
/* FTFA_FlashConfig */
#define NV_BACKKEY3                              NV_BACKKEY3_REG(FTFA_FlashConfig)
#define NV_BACKKEY2                              NV_BACKKEY2_REG(FTFA_FlashConfig)
#define NV_BACKKEY1                              NV_BACKKEY1_REG(FTFA_FlashConfig)
#define NV_BACKKEY0                              NV_BACKKEY0_REG(FTFA_FlashConfig)
#define NV_BACKKEY7                              NV_BACKKEY7_REG(FTFA_FlashConfig)
#define NV_BACKKEY6                              NV_BACKKEY6_REG(FTFA_FlashConfig)
#define NV_BACKKEY5                              NV_BACKKEY5_REG(FTFA_FlashConfig)
#define NV_BACKKEY4                              NV_BACKKEY4_REG(FTFA_FlashConfig)
#define NV_FPROT3                                NV_FPROT3_REG(FTFA_FlashConfig)
#define NV_FPROT2                                NV_FPROT2_REG(FTFA_FlashConfig)
#define NV_FPROT1                                NV_FPROT1_REG(FTFA_FlashConfig)
#define NV_FPROT0                                NV_FPROT0_REG(FTFA_FlashConfig)
#define NV_FSEC                                  NV_FSEC_REG(FTFA_FlashConfig)
#define NV_FOPT                                  NV_FOPT_REG(FTFA_FlashConfig)

/*!
 * @}
 */ /* end of group NV_Register_Accessor_Macros */


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
} OSC_Type, *OSC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- OSC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Accessor_Macros OSC - Register accessor macros
 * @{
 */


/* OSC - Register accessors */
#define OSC_CR_REG(base)                         ((base)->CR)

/*!
 * @}
 */ /* end of group OSC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- OSC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Masks OSC Register Masks
 * @{
 */

/* CR Bit Fields */
#define OSC_CR_SC16P_MASK                        0x1u
#define OSC_CR_SC16P_SHIFT                       0
#define OSC_CR_SC16P_WIDTH                       1
#define OSC_CR_SC16P(x)                          (((uint8_t)(((uint8_t)(x))<<OSC_CR_SC16P_SHIFT))&OSC_CR_SC16P_MASK)
#define OSC_CR_SC8P_MASK                         0x2u
#define OSC_CR_SC8P_SHIFT                        1
#define OSC_CR_SC8P_WIDTH                        1
#define OSC_CR_SC8P(x)                           (((uint8_t)(((uint8_t)(x))<<OSC_CR_SC8P_SHIFT))&OSC_CR_SC8P_MASK)
#define OSC_CR_SC4P_MASK                         0x4u
#define OSC_CR_SC4P_SHIFT                        2
#define OSC_CR_SC4P_WIDTH                        1
#define OSC_CR_SC4P(x)                           (((uint8_t)(((uint8_t)(x))<<OSC_CR_SC4P_SHIFT))&OSC_CR_SC4P_MASK)
#define OSC_CR_SC2P_MASK                         0x8u
#define OSC_CR_SC2P_SHIFT                        3
#define OSC_CR_SC2P_WIDTH                        1
#define OSC_CR_SC2P(x)                           (((uint8_t)(((uint8_t)(x))<<OSC_CR_SC2P_SHIFT))&OSC_CR_SC2P_MASK)
#define OSC_CR_EREFSTEN_MASK                     0x20u
#define OSC_CR_EREFSTEN_SHIFT                    5
#define OSC_CR_EREFSTEN_WIDTH                    1
#define OSC_CR_EREFSTEN(x)                       (((uint8_t)(((uint8_t)(x))<<OSC_CR_EREFSTEN_SHIFT))&OSC_CR_EREFSTEN_MASK)
#define OSC_CR_ERCLKEN_MASK                      0x80u
#define OSC_CR_ERCLKEN_SHIFT                     7
#define OSC_CR_ERCLKEN_WIDTH                     1
#define OSC_CR_ERCLKEN(x)                        (((uint8_t)(((uint8_t)(x))<<OSC_CR_ERCLKEN_SHIFT))&OSC_CR_ERCLKEN_MASK)

/*!
 * @}
 */ /* end of group OSC_Register_Masks */


/* OSC - Peripheral instance base addresses */
/** Peripheral OSC base address */
#define OSC_BASE                                 (0x40066000u)
/** Peripheral OSC base pointer */
#define OSC                                      ((OSC_Type *)OSC_BASE)
#define OSC_BASE_PTR                             (OSC)
/** Array initializer of OSC peripheral base addresses */
#define OSC_BASE_ADDRS                           { OSC_BASE }
/** Array initializer of OSC peripheral base pointers */
#define OSC_BASE_PTRS                            { OSC }

/* ----------------------------------------------------------------------------
   -- OSC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Accessor_Macros OSC - Register accessor macros
 * @{
 */


/* OSC - Register instance definitions */
/* OSC */
#define OSC_CR                                   OSC_CR_REG(OSC)

/*!
 * @}
 */ /* end of group OSC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group OSC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PDB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDB_Peripheral_Access_Layer PDB Peripheral Access Layer
 * @{
 */

/** PDB - Register Layout Typedef */
typedef struct {
  __IO uint32_t SC;                                /**< Status and Control register, offset: 0x0 */
  __IO uint32_t MOD;                               /**< Modulus register, offset: 0x4 */
  __I  uint32_t CNT;                               /**< Counter register, offset: 0x8 */
  __IO uint32_t IDLY;                              /**< Interrupt Delay register, offset: 0xC */
  struct {                                         /* offset: 0x10, array step: 0x18 */
    __IO uint32_t C1;                                /**< Channel n Control register 1, array offset: 0x10, array step: 0x18 */
    __IO uint32_t S;                                 /**< Channel n Status register, array offset: 0x14, array step: 0x18 */
    __IO uint32_t DLY[4];                            /**< Channel n Delay 0 register..Channel n Delay 3 register, array offset: 0x18, array step: index*0x18, index2*0x4 */
  } CH[1];
       uint8_t RESERVED_0[360];
  __IO uint32_t POEN;                              /**< Pulse-Out n Enable register, offset: 0x190 */
  __IO uint32_t PODLY[1];                          /**< Pulse-Out n Delay register, array offset: 0x194, array step: 0x4 */
} PDB_Type, *PDB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PDB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDB_Register_Accessor_Macros PDB - Register accessor macros
 * @{
 */


/* PDB - Register accessors */
#define PDB_SC_REG(base)                         ((base)->SC)
#define PDB_MOD_REG(base)                        ((base)->MOD)
#define PDB_CNT_REG(base)                        ((base)->CNT)
#define PDB_IDLY_REG(base)                       ((base)->IDLY)
#define PDB_C1_REG(base,index)                   ((base)->CH[index].C1)
#define PDB_C1_COUNT                             1
#define PDB_S_REG(base,index)                    ((base)->CH[index].S)
#define PDB_S_COUNT                              1
#define PDB_DLY_REG(base,index,index2)           ((base)->CH[index].DLY[index2])
#define PDB_DLY_COUNT                            1
#define PDB_DLY_COUNT2                           4
#define PDB_POEN_REG(base)                       ((base)->POEN)
#define PDB_PODLY_REG(base,index)                ((base)->PODLY[index])
#define PDB_PODLY_COUNT                          1

/*!
 * @}
 */ /* end of group PDB_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PDB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDB_Register_Masks PDB Register Masks
 * @{
 */

/* SC Bit Fields */
#define PDB_SC_LDOK_MASK                         0x1u
#define PDB_SC_LDOK_SHIFT                        0
#define PDB_SC_LDOK_WIDTH                        1
#define PDB_SC_LDOK(x)                           (((uint32_t)(((uint32_t)(x))<<PDB_SC_LDOK_SHIFT))&PDB_SC_LDOK_MASK)
#define PDB_SC_CONT_MASK                         0x2u
#define PDB_SC_CONT_SHIFT                        1
#define PDB_SC_CONT_WIDTH                        1
#define PDB_SC_CONT(x)                           (((uint32_t)(((uint32_t)(x))<<PDB_SC_CONT_SHIFT))&PDB_SC_CONT_MASK)
#define PDB_SC_MULT_MASK                         0xCu
#define PDB_SC_MULT_SHIFT                        2
#define PDB_SC_MULT_WIDTH                        2
#define PDB_SC_MULT(x)                           (((uint32_t)(((uint32_t)(x))<<PDB_SC_MULT_SHIFT))&PDB_SC_MULT_MASK)
#define PDB_SC_PDBIE_MASK                        0x20u
#define PDB_SC_PDBIE_SHIFT                       5
#define PDB_SC_PDBIE_WIDTH                       1
#define PDB_SC_PDBIE(x)                          (((uint32_t)(((uint32_t)(x))<<PDB_SC_PDBIE_SHIFT))&PDB_SC_PDBIE_MASK)
#define PDB_SC_PDBIF_MASK                        0x40u
#define PDB_SC_PDBIF_SHIFT                       6
#define PDB_SC_PDBIF_WIDTH                       1
#define PDB_SC_PDBIF(x)                          (((uint32_t)(((uint32_t)(x))<<PDB_SC_PDBIF_SHIFT))&PDB_SC_PDBIF_MASK)
#define PDB_SC_PDBEN_MASK                        0x80u
#define PDB_SC_PDBEN_SHIFT                       7
#define PDB_SC_PDBEN_WIDTH                       1
#define PDB_SC_PDBEN(x)                          (((uint32_t)(((uint32_t)(x))<<PDB_SC_PDBEN_SHIFT))&PDB_SC_PDBEN_MASK)
#define PDB_SC_TRGSEL_MASK                       0xF00u
#define PDB_SC_TRGSEL_SHIFT                      8
#define PDB_SC_TRGSEL_WIDTH                      4
#define PDB_SC_TRGSEL(x)                         (((uint32_t)(((uint32_t)(x))<<PDB_SC_TRGSEL_SHIFT))&PDB_SC_TRGSEL_MASK)
#define PDB_SC_PRESCALER_MASK                    0x7000u
#define PDB_SC_PRESCALER_SHIFT                   12
#define PDB_SC_PRESCALER_WIDTH                   3
#define PDB_SC_PRESCALER(x)                      (((uint32_t)(((uint32_t)(x))<<PDB_SC_PRESCALER_SHIFT))&PDB_SC_PRESCALER_MASK)
#define PDB_SC_DMAEN_MASK                        0x8000u
#define PDB_SC_DMAEN_SHIFT                       15
#define PDB_SC_DMAEN_WIDTH                       1
#define PDB_SC_DMAEN(x)                          (((uint32_t)(((uint32_t)(x))<<PDB_SC_DMAEN_SHIFT))&PDB_SC_DMAEN_MASK)
#define PDB_SC_SWTRIG_MASK                       0x10000u
#define PDB_SC_SWTRIG_SHIFT                      16
#define PDB_SC_SWTRIG_WIDTH                      1
#define PDB_SC_SWTRIG(x)                         (((uint32_t)(((uint32_t)(x))<<PDB_SC_SWTRIG_SHIFT))&PDB_SC_SWTRIG_MASK)
#define PDB_SC_PDBEIE_MASK                       0x20000u
#define PDB_SC_PDBEIE_SHIFT                      17
#define PDB_SC_PDBEIE_WIDTH                      1
#define PDB_SC_PDBEIE(x)                         (((uint32_t)(((uint32_t)(x))<<PDB_SC_PDBEIE_SHIFT))&PDB_SC_PDBEIE_MASK)
#define PDB_SC_LDMOD_MASK                        0xC0000u
#define PDB_SC_LDMOD_SHIFT                       18
#define PDB_SC_LDMOD_WIDTH                       2
#define PDB_SC_LDMOD(x)                          (((uint32_t)(((uint32_t)(x))<<PDB_SC_LDMOD_SHIFT))&PDB_SC_LDMOD_MASK)
/* MOD Bit Fields */
#define PDB_MOD_MOD_MASK                         0xFFFFu
#define PDB_MOD_MOD_SHIFT                        0
#define PDB_MOD_MOD_WIDTH                        16
#define PDB_MOD_MOD(x)                           (((uint32_t)(((uint32_t)(x))<<PDB_MOD_MOD_SHIFT))&PDB_MOD_MOD_MASK)
/* CNT Bit Fields */
#define PDB_CNT_CNT_MASK                         0xFFFFu
#define PDB_CNT_CNT_SHIFT                        0
#define PDB_CNT_CNT_WIDTH                        16
#define PDB_CNT_CNT(x)                           (((uint32_t)(((uint32_t)(x))<<PDB_CNT_CNT_SHIFT))&PDB_CNT_CNT_MASK)
/* IDLY Bit Fields */
#define PDB_IDLY_IDLY_MASK                       0xFFFFu
#define PDB_IDLY_IDLY_SHIFT                      0
#define PDB_IDLY_IDLY_WIDTH                      16
#define PDB_IDLY_IDLY(x)                         (((uint32_t)(((uint32_t)(x))<<PDB_IDLY_IDLY_SHIFT))&PDB_IDLY_IDLY_MASK)
/* C1 Bit Fields */
#define PDB_C1_EN_MASK                           0xFFu
#define PDB_C1_EN_SHIFT                          0
#define PDB_C1_EN_WIDTH                          8
#define PDB_C1_EN(x)                             (((uint32_t)(((uint32_t)(x))<<PDB_C1_EN_SHIFT))&PDB_C1_EN_MASK)
#define PDB_C1_TOS_MASK                          0xFF00u
#define PDB_C1_TOS_SHIFT                         8
#define PDB_C1_TOS_WIDTH                         8
#define PDB_C1_TOS(x)                            (((uint32_t)(((uint32_t)(x))<<PDB_C1_TOS_SHIFT))&PDB_C1_TOS_MASK)
#define PDB_C1_BB_MASK                           0xFF0000u
#define PDB_C1_BB_SHIFT                          16
#define PDB_C1_BB_WIDTH                          8
#define PDB_C1_BB(x)                             (((uint32_t)(((uint32_t)(x))<<PDB_C1_BB_SHIFT))&PDB_C1_BB_MASK)
/* S Bit Fields */
#define PDB_S_ERR_MASK                           0xFFu
#define PDB_S_ERR_SHIFT                          0
#define PDB_S_ERR_WIDTH                          8
#define PDB_S_ERR(x)                             (((uint32_t)(((uint32_t)(x))<<PDB_S_ERR_SHIFT))&PDB_S_ERR_MASK)
#define PDB_S_CF_MASK                            0xFF0000u
#define PDB_S_CF_SHIFT                           16
#define PDB_S_CF_WIDTH                           8
#define PDB_S_CF(x)                              (((uint32_t)(((uint32_t)(x))<<PDB_S_CF_SHIFT))&PDB_S_CF_MASK)
/* DLY Bit Fields */
#define PDB_DLY_DLY_MASK                         0xFFFFu
#define PDB_DLY_DLY_SHIFT                        0
#define PDB_DLY_DLY_WIDTH                        16
#define PDB_DLY_DLY(x)                           (((uint32_t)(((uint32_t)(x))<<PDB_DLY_DLY_SHIFT))&PDB_DLY_DLY_MASK)
/* POEN Bit Fields */
#define PDB_POEN_POEN_MASK                       0xFFu
#define PDB_POEN_POEN_SHIFT                      0
#define PDB_POEN_POEN_WIDTH                      8
#define PDB_POEN_POEN(x)                         (((uint32_t)(((uint32_t)(x))<<PDB_POEN_POEN_SHIFT))&PDB_POEN_POEN_MASK)
/* PODLY Bit Fields */
#define PDB_PODLY_DLY2_MASK                      0xFFFFu
#define PDB_PODLY_DLY2_SHIFT                     0
#define PDB_PODLY_DLY2_WIDTH                     16
#define PDB_PODLY_DLY2(x)                        (((uint32_t)(((uint32_t)(x))<<PDB_PODLY_DLY2_SHIFT))&PDB_PODLY_DLY2_MASK)
#define PDB_PODLY_DLY1_MASK                      0xFFFF0000u
#define PDB_PODLY_DLY1_SHIFT                     16
#define PDB_PODLY_DLY1_WIDTH                     16
#define PDB_PODLY_DLY1(x)                        (((uint32_t)(((uint32_t)(x))<<PDB_PODLY_DLY1_SHIFT))&PDB_PODLY_DLY1_MASK)

/*!
 * @}
 */ /* end of group PDB_Register_Masks */


/* PDB - Peripheral instance base addresses */
/** Peripheral PDB0 base address */
#define PDB0_BASE                                (0x40036000u)
/** Peripheral PDB0 base pointer */
#define PDB0                                     ((PDB_Type *)PDB0_BASE)
#define PDB0_BASE_PTR                            (PDB0)
/** Array initializer of PDB peripheral base addresses */
#define PDB_BASE_ADDRS                           { PDB0_BASE }
/** Array initializer of PDB peripheral base pointers */
#define PDB_BASE_PTRS                            { PDB0 }
/** Interrupt vectors for the PDB peripheral type */
#define PDB_IRQS                                 { PDB0_IRQn }

/* ----------------------------------------------------------------------------
   -- PDB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDB_Register_Accessor_Macros PDB - Register accessor macros
 * @{
 */


/* PDB - Register instance definitions */
/* PDB0 */
#define PDB0_SC                                  PDB_SC_REG(PDB0)
#define PDB0_MOD                                 PDB_MOD_REG(PDB0)
#define PDB0_CNT                                 PDB_CNT_REG(PDB0)
#define PDB0_IDLY                                PDB_IDLY_REG(PDB0)
#define PDB0_CH0C1                               PDB_C1_REG(PDB0,0)
#define PDB0_CH0S                                PDB_S_REG(PDB0,0)
#define PDB0_CH0DLY0                             PDB_DLY_REG(PDB0,0,0)
#define PDB0_CH0DLY1                             PDB_DLY_REG(PDB0,0,1)
#define PDB0_CH0DLY2                             PDB_DLY_REG(PDB0,0,2)
#define PDB0_CH0DLY3                             PDB_DLY_REG(PDB0,0,3)
#define PDB0_POEN                                PDB_POEN_REG(PDB0)
#define PDB0_PO0DLY                              PDB_PODLY_REG(PDB0,0)

/* PDB - Register array accessors */
#define PDB0_C1(index)                           PDB_C1_REG(PDB0,index)
#define PDB0_S(index)                            PDB_S_REG(PDB0,index)
#define PDB0_DLY(index,index2)                   PDB_DLY_REG(PDB0,index,index2)
#define PDB0_PODLY(index)                        PDB_PODLY_REG(PDB0,index)

/*!
 * @}
 */ /* end of group PDB_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PDB_Peripheral_Access_Layer */


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
       uint8_t RESERVED_0[252];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    __IO uint32_t LDVAL;                             /**< Timer Load Value Register, array offset: 0x100, array step: 0x10 */
    __I  uint32_t CVAL;                              /**< Current Timer Value Register, array offset: 0x104, array step: 0x10 */
    __IO uint32_t TCTRL;                             /**< Timer Control Register, array offset: 0x108, array step: 0x10 */
    __IO uint32_t TFLG;                              /**< Timer Flag Register, array offset: 0x10C, array step: 0x10 */
  } CHANNEL[2];
} PIT_Type, *PIT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PIT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Accessor_Macros PIT - Register accessor macros
 * @{
 */


/* PIT - Register accessors */
#define PIT_MCR_REG(base)                        ((base)->MCR)
#define PIT_LDVAL_REG(base,index)                ((base)->CHANNEL[index].LDVAL)
#define PIT_LDVAL_COUNT                          2
#define PIT_CVAL_REG(base,index)                 ((base)->CHANNEL[index].CVAL)
#define PIT_CVAL_COUNT                           2
#define PIT_TCTRL_REG(base,index)                ((base)->CHANNEL[index].TCTRL)
#define PIT_TCTRL_COUNT                          2
#define PIT_TFLG_REG(base,index)                 ((base)->CHANNEL[index].TFLG)
#define PIT_TFLG_COUNT                           2

/*!
 * @}
 */ /* end of group PIT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PIT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Masks PIT Register Masks
 * @{
 */

/* MCR Bit Fields */
#define PIT_MCR_FRZ_MASK                         0x1u
#define PIT_MCR_FRZ_SHIFT                        0
#define PIT_MCR_FRZ_WIDTH                        1
#define PIT_MCR_FRZ(x)                           (((uint32_t)(((uint32_t)(x))<<PIT_MCR_FRZ_SHIFT))&PIT_MCR_FRZ_MASK)
#define PIT_MCR_MDIS_MASK                        0x2u
#define PIT_MCR_MDIS_SHIFT                       1
#define PIT_MCR_MDIS_WIDTH                       1
#define PIT_MCR_MDIS(x)                          (((uint32_t)(((uint32_t)(x))<<PIT_MCR_MDIS_SHIFT))&PIT_MCR_MDIS_MASK)
/* LDVAL Bit Fields */
#define PIT_LDVAL_TSV_MASK                       0xFFFFFFFFu
#define PIT_LDVAL_TSV_SHIFT                      0
#define PIT_LDVAL_TSV_WIDTH                      32
#define PIT_LDVAL_TSV(x)                         (((uint32_t)(((uint32_t)(x))<<PIT_LDVAL_TSV_SHIFT))&PIT_LDVAL_TSV_MASK)
/* CVAL Bit Fields */
#define PIT_CVAL_TVL_MASK                        0xFFFFFFFFu
#define PIT_CVAL_TVL_SHIFT                       0
#define PIT_CVAL_TVL_WIDTH                       32
#define PIT_CVAL_TVL(x)                          (((uint32_t)(((uint32_t)(x))<<PIT_CVAL_TVL_SHIFT))&PIT_CVAL_TVL_MASK)
/* TCTRL Bit Fields */
#define PIT_TCTRL_TEN_MASK                       0x1u
#define PIT_TCTRL_TEN_SHIFT                      0
#define PIT_TCTRL_TEN_WIDTH                      1
#define PIT_TCTRL_TEN(x)                         (((uint32_t)(((uint32_t)(x))<<PIT_TCTRL_TEN_SHIFT))&PIT_TCTRL_TEN_MASK)
#define PIT_TCTRL_TIE_MASK                       0x2u
#define PIT_TCTRL_TIE_SHIFT                      1
#define PIT_TCTRL_TIE_WIDTH                      1
#define PIT_TCTRL_TIE(x)                         (((uint32_t)(((uint32_t)(x))<<PIT_TCTRL_TIE_SHIFT))&PIT_TCTRL_TIE_MASK)
#define PIT_TCTRL_CHN_MASK                       0x4u
#define PIT_TCTRL_CHN_SHIFT                      2
#define PIT_TCTRL_CHN_WIDTH                      1
#define PIT_TCTRL_CHN(x)                         (((uint32_t)(((uint32_t)(x))<<PIT_TCTRL_CHN_SHIFT))&PIT_TCTRL_CHN_MASK)
/* TFLG Bit Fields */
#define PIT_TFLG_TIF_MASK                        0x1u
#define PIT_TFLG_TIF_SHIFT                       0
#define PIT_TFLG_TIF_WIDTH                       1
#define PIT_TFLG_TIF(x)                          (((uint32_t)(((uint32_t)(x))<<PIT_TFLG_TIF_SHIFT))&PIT_TFLG_TIF_MASK)

/*!
 * @}
 */ /* end of group PIT_Register_Masks */


/* PIT - Peripheral instance base addresses */
/** Peripheral PIT0 base address */
#define PIT0_BASE                                (0x4002D000u)
/** Peripheral PIT0 base pointer */
#define PIT0                                     ((PIT_Type *)PIT0_BASE)
#define PIT0_BASE_PTR                            (PIT0)
/** Peripheral PIT1 base address */
#define PIT1_BASE                                (0x4002E000u)
/** Peripheral PIT1 base pointer */
#define PIT1                                     ((PIT_Type *)PIT1_BASE)
#define PIT1_BASE_PTR                            (PIT1)
/** Array initializer of PIT peripheral base addresses */
#define PIT_BASE_ADDRS                           { PIT0_BASE, PIT1_BASE }
/** Array initializer of PIT peripheral base pointers */
#define PIT_BASE_PTRS                            { PIT0, PIT1 }
/** Interrupt vectors for the PIT peripheral type */
#define PIT_IRQS                                 { PIT0_PIT1_IRQn, PIT0_PIT1_IRQn }

/* ----------------------------------------------------------------------------
   -- PIT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Accessor_Macros PIT - Register accessor macros
 * @{
 */


/* PIT - Register instance definitions */
/* PIT0 */
#define PIT0_MCR                                 PIT_MCR_REG(PIT0)
#define PIT0_LDVAL0                              PIT_LDVAL_REG(PIT0,0)
#define PIT0_CVAL0                               PIT_CVAL_REG(PIT0,0)
#define PIT0_TCTRL0                              PIT_TCTRL_REG(PIT0,0)
#define PIT0_TFLG0                               PIT_TFLG_REG(PIT0,0)
#define PIT0_LDVAL1                              PIT_LDVAL_REG(PIT0,1)
#define PIT0_CVAL1                               PIT_CVAL_REG(PIT0,1)
#define PIT0_TCTRL1                              PIT_TCTRL_REG(PIT0,1)
#define PIT0_TFLG1                               PIT_TFLG_REG(PIT0,1)
/* PIT1 */
#define PIT1_MCR                                 PIT_MCR_REG(PIT1)
#define PIT1_LDVAL0                              PIT_LDVAL_REG(PIT1,0)
#define PIT1_CVAL0                               PIT_CVAL_REG(PIT1,0)
#define PIT1_TCTRL0                              PIT_TCTRL_REG(PIT1,0)
#define PIT1_TFLG0                               PIT_TFLG_REG(PIT1,0)
#define PIT1_LDVAL1                              PIT_LDVAL_REG(PIT1,1)
#define PIT1_CVAL1                               PIT_CVAL_REG(PIT1,1)
#define PIT1_TCTRL1                              PIT_TCTRL_REG(PIT1,1)
#define PIT1_TFLG1                               PIT_TFLG_REG(PIT1,1)

/* PIT - Register array accessors */
#define PIT0_LDVAL(index)                        PIT_LDVAL_REG(PIT0,index)
#define PIT1_LDVAL(index)                        PIT_LDVAL_REG(PIT1,index)
#define PIT0_CVAL(index)                         PIT_CVAL_REG(PIT0,index)
#define PIT1_CVAL(index)                         PIT_CVAL_REG(PIT1,index)
#define PIT0_TCTRL(index)                        PIT_TCTRL_REG(PIT0,index)
#define PIT1_TCTRL(index)                        PIT_TCTRL_REG(PIT1,index)
#define PIT0_TFLG(index)                         PIT_TFLG_REG(PIT0,index)
#define PIT1_TFLG(index)                         PIT_TFLG_REG(PIT1,index)

/*!
 * @}
 */ /* end of group PIT_Register_Accessor_Macros */


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
} PMC_Type, *PMC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Accessor_Macros PMC - Register accessor macros
 * @{
 */


/* PMC - Register accessors */
#define PMC_LVDSC1_REG(base)                     ((base)->LVDSC1)
#define PMC_LVDSC2_REG(base)                     ((base)->LVDSC2)
#define PMC_REGSC_REG(base)                      ((base)->REGSC)

/*!
 * @}
 */ /* end of group PMC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Masks PMC Register Masks
 * @{
 */

/* LVDSC1 Bit Fields */
#define PMC_LVDSC1_LVDV_MASK                     0x3u
#define PMC_LVDSC1_LVDV_SHIFT                    0
#define PMC_LVDSC1_LVDV_WIDTH                    2
#define PMC_LVDSC1_LVDV(x)                       (((uint8_t)(((uint8_t)(x))<<PMC_LVDSC1_LVDV_SHIFT))&PMC_LVDSC1_LVDV_MASK)
#define PMC_LVDSC1_LVDRE_MASK                    0x10u
#define PMC_LVDSC1_LVDRE_SHIFT                   4
#define PMC_LVDSC1_LVDRE_WIDTH                   1
#define PMC_LVDSC1_LVDRE(x)                      (((uint8_t)(((uint8_t)(x))<<PMC_LVDSC1_LVDRE_SHIFT))&PMC_LVDSC1_LVDRE_MASK)
#define PMC_LVDSC1_LVDIE_MASK                    0x20u
#define PMC_LVDSC1_LVDIE_SHIFT                   5
#define PMC_LVDSC1_LVDIE_WIDTH                   1
#define PMC_LVDSC1_LVDIE(x)                      (((uint8_t)(((uint8_t)(x))<<PMC_LVDSC1_LVDIE_SHIFT))&PMC_LVDSC1_LVDIE_MASK)
#define PMC_LVDSC1_LVDACK_MASK                   0x40u
#define PMC_LVDSC1_LVDACK_SHIFT                  6
#define PMC_LVDSC1_LVDACK_WIDTH                  1
#define PMC_LVDSC1_LVDACK(x)                     (((uint8_t)(((uint8_t)(x))<<PMC_LVDSC1_LVDACK_SHIFT))&PMC_LVDSC1_LVDACK_MASK)
#define PMC_LVDSC1_LVDF_MASK                     0x80u
#define PMC_LVDSC1_LVDF_SHIFT                    7
#define PMC_LVDSC1_LVDF_WIDTH                    1
#define PMC_LVDSC1_LVDF(x)                       (((uint8_t)(((uint8_t)(x))<<PMC_LVDSC1_LVDF_SHIFT))&PMC_LVDSC1_LVDF_MASK)
/* LVDSC2 Bit Fields */
#define PMC_LVDSC2_LVWV_MASK                     0x3u
#define PMC_LVDSC2_LVWV_SHIFT                    0
#define PMC_LVDSC2_LVWV_WIDTH                    2
#define PMC_LVDSC2_LVWV(x)                       (((uint8_t)(((uint8_t)(x))<<PMC_LVDSC2_LVWV_SHIFT))&PMC_LVDSC2_LVWV_MASK)
#define PMC_LVDSC2_LVWIE_MASK                    0x20u
#define PMC_LVDSC2_LVWIE_SHIFT                   5
#define PMC_LVDSC2_LVWIE_WIDTH                   1
#define PMC_LVDSC2_LVWIE(x)                      (((uint8_t)(((uint8_t)(x))<<PMC_LVDSC2_LVWIE_SHIFT))&PMC_LVDSC2_LVWIE_MASK)
#define PMC_LVDSC2_LVWACK_MASK                   0x40u
#define PMC_LVDSC2_LVWACK_SHIFT                  6
#define PMC_LVDSC2_LVWACK_WIDTH                  1
#define PMC_LVDSC2_LVWACK(x)                     (((uint8_t)(((uint8_t)(x))<<PMC_LVDSC2_LVWACK_SHIFT))&PMC_LVDSC2_LVWACK_MASK)
#define PMC_LVDSC2_LVWF_MASK                     0x80u
#define PMC_LVDSC2_LVWF_SHIFT                    7
#define PMC_LVDSC2_LVWF_WIDTH                    1
#define PMC_LVDSC2_LVWF(x)                       (((uint8_t)(((uint8_t)(x))<<PMC_LVDSC2_LVWF_SHIFT))&PMC_LVDSC2_LVWF_MASK)
/* REGSC Bit Fields */
#define PMC_REGSC_BGBE_MASK                      0x1u
#define PMC_REGSC_BGBE_SHIFT                     0
#define PMC_REGSC_BGBE_WIDTH                     1
#define PMC_REGSC_BGBE(x)                        (((uint8_t)(((uint8_t)(x))<<PMC_REGSC_BGBE_SHIFT))&PMC_REGSC_BGBE_MASK)
#define PMC_REGSC_REGONS_MASK                    0x4u
#define PMC_REGSC_REGONS_SHIFT                   2
#define PMC_REGSC_REGONS_WIDTH                   1
#define PMC_REGSC_REGONS(x)                      (((uint8_t)(((uint8_t)(x))<<PMC_REGSC_REGONS_SHIFT))&PMC_REGSC_REGONS_MASK)
#define PMC_REGSC_ACKISO_MASK                    0x8u
#define PMC_REGSC_ACKISO_SHIFT                   3
#define PMC_REGSC_ACKISO_WIDTH                   1
#define PMC_REGSC_ACKISO(x)                      (((uint8_t)(((uint8_t)(x))<<PMC_REGSC_ACKISO_SHIFT))&PMC_REGSC_ACKISO_MASK)
#define PMC_REGSC_BGEN_MASK                      0x10u
#define PMC_REGSC_BGEN_SHIFT                     4
#define PMC_REGSC_BGEN_WIDTH                     1
#define PMC_REGSC_BGEN(x)                        (((uint8_t)(((uint8_t)(x))<<PMC_REGSC_BGEN_SHIFT))&PMC_REGSC_BGEN_MASK)

/*!
 * @}
 */ /* end of group PMC_Register_Masks */


/* PMC - Peripheral instance base addresses */
/** Peripheral PMC base address */
#define PMC_BASE                                 (0x4007D000u)
/** Peripheral PMC base pointer */
#define PMC                                      ((PMC_Type *)PMC_BASE)
#define PMC_BASE_PTR                             (PMC)
/** Array initializer of PMC peripheral base addresses */
#define PMC_BASE_ADDRS                           { PMC_BASE }
/** Array initializer of PMC peripheral base pointers */
#define PMC_BASE_PTRS                            { PMC }
/** Interrupt vectors for the PMC peripheral type */
#define PMC_IRQS                                 { PMC_IRQn }

/* ----------------------------------------------------------------------------
   -- PMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Accessor_Macros PMC - Register accessor macros
 * @{
 */


/* PMC - Register instance definitions */
/* PMC */
#define PMC_LVDSC1                               PMC_LVDSC1_REG(PMC)
#define PMC_LVDSC2                               PMC_LVDSC2_REG(PMC)
#define PMC_REGSC                                PMC_REGSC_REG(PMC)

/*!
 * @}
 */ /* end of group PMC_Register_Accessor_Macros */


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
  __IO uint32_t PCR[8];                            /**< Pin Control Register n, array offset: 0x0, array step: 0x4 */
       uint8_t RESERVED_0[96];
  __O  uint32_t GPCLR;                             /**< Global Pin Control Low Register, offset: 0x80 */
  __O  uint32_t GPCHR;                             /**< Global Pin Control High Register, offset: 0x84 */
       uint8_t RESERVED_1[24];
  __IO uint32_t ISFR;                              /**< Interrupt Status Flag Register, offset: 0xA0 */
       uint8_t RESERVED_2[28];
  __IO uint32_t DFER;                              /**< Digital Filter Enable Register, offset: 0xC0 */
  __IO uint32_t DFCR;                              /**< Digital Filter Clock Register, offset: 0xC4 */
  __IO uint32_t DFWR;                              /**< Digital Filter Width Register, offset: 0xC8 */
} PORT_Type, *PORT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PORT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Accessor_Macros PORT - Register accessor macros
 * @{
 */


/* PORT - Register accessors */
#define PORT_PCR_REG(base,index)                 ((base)->PCR[index])
#define PORT_PCR_COUNT                           8
#define PORT_GPCLR_REG(base)                     ((base)->GPCLR)
#define PORT_GPCHR_REG(base)                     ((base)->GPCHR)
#define PORT_ISFR_REG(base)                      ((base)->ISFR)
#define PORT_DFER_REG(base)                      ((base)->DFER)
#define PORT_DFCR_REG(base)                      ((base)->DFCR)
#define PORT_DFWR_REG(base)                      ((base)->DFWR)

/*!
 * @}
 */ /* end of group PORT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PORT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Masks PORT Register Masks
 * @{
 */

/* PCR Bit Fields */
#define PORT_PCR_PS_MASK                         0x1u
#define PORT_PCR_PS_SHIFT                        0
#define PORT_PCR_PS_WIDTH                        1
#define PORT_PCR_PS(x)                           (((uint32_t)(((uint32_t)(x))<<PORT_PCR_PS_SHIFT))&PORT_PCR_PS_MASK)
#define PORT_PCR_PE_MASK                         0x2u
#define PORT_PCR_PE_SHIFT                        1
#define PORT_PCR_PE_WIDTH                        1
#define PORT_PCR_PE(x)                           (((uint32_t)(((uint32_t)(x))<<PORT_PCR_PE_SHIFT))&PORT_PCR_PE_MASK)
#define PORT_PCR_SRE_MASK                        0x4u
#define PORT_PCR_SRE_SHIFT                       2
#define PORT_PCR_SRE_WIDTH                       1
#define PORT_PCR_SRE(x)                          (((uint32_t)(((uint32_t)(x))<<PORT_PCR_SRE_SHIFT))&PORT_PCR_SRE_MASK)
#define PORT_PCR_ODE_MASK                        0x20u
#define PORT_PCR_ODE_SHIFT                       5
#define PORT_PCR_ODE_WIDTH                       1
#define PORT_PCR_ODE(x)                          (((uint32_t)(((uint32_t)(x))<<PORT_PCR_ODE_SHIFT))&PORT_PCR_ODE_MASK)
#define PORT_PCR_MUX_MASK                        0x700u
#define PORT_PCR_MUX_SHIFT                       8
#define PORT_PCR_MUX_WIDTH                       3
#define PORT_PCR_MUX(x)                          (((uint32_t)(((uint32_t)(x))<<PORT_PCR_MUX_SHIFT))&PORT_PCR_MUX_MASK)
#define PORT_PCR_LK_MASK                         0x8000u
#define PORT_PCR_LK_SHIFT                        15
#define PORT_PCR_LK_WIDTH                        1
#define PORT_PCR_LK(x)                           (((uint32_t)(((uint32_t)(x))<<PORT_PCR_LK_SHIFT))&PORT_PCR_LK_MASK)
#define PORT_PCR_IRQC_MASK                       0xF0000u
#define PORT_PCR_IRQC_SHIFT                      16
#define PORT_PCR_IRQC_WIDTH                      4
#define PORT_PCR_IRQC(x)                         (((uint32_t)(((uint32_t)(x))<<PORT_PCR_IRQC_SHIFT))&PORT_PCR_IRQC_MASK)
#define PORT_PCR_ISF_MASK                        0x1000000u
#define PORT_PCR_ISF_SHIFT                       24
#define PORT_PCR_ISF_WIDTH                       1
#define PORT_PCR_ISF(x)                          (((uint32_t)(((uint32_t)(x))<<PORT_PCR_ISF_SHIFT))&PORT_PCR_ISF_MASK)
/* GPCLR Bit Fields */
#define PORT_GPCLR_GPWD_MASK                     0xFFFFu
#define PORT_GPCLR_GPWD_SHIFT                    0
#define PORT_GPCLR_GPWD_WIDTH                    16
#define PORT_GPCLR_GPWD(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_GPCLR_GPWD_SHIFT))&PORT_GPCLR_GPWD_MASK)
#define PORT_GPCLR_GPWE_MASK                     0xFFFF0000u
#define PORT_GPCLR_GPWE_SHIFT                    16
#define PORT_GPCLR_GPWE_WIDTH                    16
#define PORT_GPCLR_GPWE(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_GPCLR_GPWE_SHIFT))&PORT_GPCLR_GPWE_MASK)
/* GPCHR Bit Fields */
#define PORT_GPCHR_GPWD_MASK                     0xFFFFu
#define PORT_GPCHR_GPWD_SHIFT                    0
#define PORT_GPCHR_GPWD_WIDTH                    16
#define PORT_GPCHR_GPWD(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_GPCHR_GPWD_SHIFT))&PORT_GPCHR_GPWD_MASK)
#define PORT_GPCHR_GPWE_MASK                     0xFFFF0000u
#define PORT_GPCHR_GPWE_SHIFT                    16
#define PORT_GPCHR_GPWE_WIDTH                    16
#define PORT_GPCHR_GPWE(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_GPCHR_GPWE_SHIFT))&PORT_GPCHR_GPWE_MASK)
/* ISFR Bit Fields */
#define PORT_ISFR_ISF_MASK                       0xFFFFFFFFu
#define PORT_ISFR_ISF_SHIFT                      0
#define PORT_ISFR_ISF_WIDTH                      32
#define PORT_ISFR_ISF(x)                         (((uint32_t)(((uint32_t)(x))<<PORT_ISFR_ISF_SHIFT))&PORT_ISFR_ISF_MASK)
/* DFER Bit Fields */
#define PORT_DFER_DFE_MASK                       0xFFFFFFFFu
#define PORT_DFER_DFE_SHIFT                      0
#define PORT_DFER_DFE_WIDTH                      32
#define PORT_DFER_DFE(x)                         (((uint32_t)(((uint32_t)(x))<<PORT_DFER_DFE_SHIFT))&PORT_DFER_DFE_MASK)
/* DFCR Bit Fields */
#define PORT_DFCR_CS_MASK                        0x1u
#define PORT_DFCR_CS_SHIFT                       0
#define PORT_DFCR_CS_WIDTH                       1
#define PORT_DFCR_CS(x)                          (((uint32_t)(((uint32_t)(x))<<PORT_DFCR_CS_SHIFT))&PORT_DFCR_CS_MASK)
/* DFWR Bit Fields */
#define PORT_DFWR_FILT_MASK                      0x1Fu
#define PORT_DFWR_FILT_SHIFT                     0
#define PORT_DFWR_FILT_WIDTH                     5
#define PORT_DFWR_FILT(x)                        (((uint32_t)(((uint32_t)(x))<<PORT_DFWR_FILT_SHIFT))&PORT_DFWR_FILT_MASK)

/*!
 * @}
 */ /* end of group PORT_Register_Masks */


/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base address */
#define PORTA_BASE                               (0x40046000u)
/** Peripheral PORTA base pointer */
#define PORTA                                    ((PORT_Type *)PORTA_BASE)
#define PORTA_BASE_PTR                           (PORTA)
/** Peripheral PORTB base address */
#define PORTB_BASE                               (0x40047000u)
/** Peripheral PORTB base pointer */
#define PORTB                                    ((PORT_Type *)PORTB_BASE)
#define PORTB_BASE_PTR                           (PORTB)
/** Peripheral PORTC base address */
#define PORTC_BASE                               (0x40048000u)
/** Peripheral PORTC base pointer */
#define PORTC                                    ((PORT_Type *)PORTC_BASE)
#define PORTC_BASE_PTR                           (PORTC)
/** Peripheral PORTD base address */
#define PORTD_BASE                               (0x40049000u)
/** Peripheral PORTD base pointer */
#define PORTD                                    ((PORT_Type *)PORTD_BASE)
#define PORTD_BASE_PTR                           (PORTD)
/** Peripheral PORTE base address */
#define PORTE_BASE                               (0x4004A000u)
/** Peripheral PORTE base pointer */
#define PORTE                                    ((PORT_Type *)PORTE_BASE)
#define PORTE_BASE_PTR                           (PORTE)
/** Peripheral PORTF base address */
#define PORTF_BASE                               (0x4004B000u)
/** Peripheral PORTF base pointer */
#define PORTF                                    ((PORT_Type *)PORTF_BASE)
#define PORTF_BASE_PTR                           (PORTF)
/** Peripheral PORTG base address */
#define PORTG_BASE                               (0x4004C000u)
/** Peripheral PORTG base pointer */
#define PORTG                                    ((PORT_Type *)PORTG_BASE)
#define PORTG_BASE_PTR                           (PORTG)
/** Peripheral PORTH base address */
#define PORTH_BASE                               (0x4004D000u)
/** Peripheral PORTH base pointer */
#define PORTH                                    ((PORT_Type *)PORTH_BASE)
#define PORTH_BASE_PTR                           (PORTH)
/** Peripheral PORTI base address */
#define PORTI_BASE                               (0x4004E000u)
/** Peripheral PORTI base pointer */
#define PORTI                                    ((PORT_Type *)PORTI_BASE)
#define PORTI_BASE_PTR                           (PORTI)
/** Peripheral PORTJ base address */
#define PORTJ_BASE                               (0x40037000u)
/** Peripheral PORTJ base pointer */
#define PORTJ                                    ((PORT_Type *)PORTJ_BASE)
#define PORTJ_BASE_PTR                           (PORTJ)
/** Peripheral PORTK base address */
#define PORTK_BASE                               (0x40038000u)
/** Peripheral PORTK base pointer */
#define PORTK                                    ((PORT_Type *)PORTK_BASE)
#define PORTK_BASE_PTR                           (PORTK)
/** Peripheral PORTL base address */
#define PORTL_BASE                               (0x40039000u)
/** Peripheral PORTL base pointer */
#define PORTL                                    ((PORT_Type *)PORTL_BASE)
#define PORTL_BASE_PTR                           (PORTL)
/** Peripheral PORTM base address */
#define PORTM_BASE                               (0x4003A000u)
/** Peripheral PORTM base pointer */
#define PORTM                                    ((PORT_Type *)PORTM_BASE)
#define PORTM_BASE_PTR                           (PORTM)
/** Array initializer of PORT peripheral base addresses */
#define PORT_BASE_ADDRS                          { PORTA_BASE, PORTB_BASE, PORTC_BASE, PORTD_BASE, PORTE_BASE, PORTF_BASE, PORTG_BASE, PORTH_BASE, PORTI_BASE, PORTJ_BASE, PORTK_BASE, PORTL_BASE, PORTM_BASE }
/** Array initializer of PORT peripheral base pointers */
#define PORT_BASE_PTRS                           { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF, PORTG, PORTH, PORTI, PORTJ, PORTK, PORTL, PORTM }
/** Interrupt vectors for the PORT peripheral type */
#define PORT_IRQS                                { PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn }

/* ----------------------------------------------------------------------------
   -- PORT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Accessor_Macros PORT - Register accessor macros
 * @{
 */


/* PORT - Register instance definitions */
/* PORTA */
#define PORTA_PCR0                               PORT_PCR_REG(PORTA,0)
#define PORTA_PCR1                               PORT_PCR_REG(PORTA,1)
#define PORTA_PCR2                               PORT_PCR_REG(PORTA,2)
#define PORTA_PCR3                               PORT_PCR_REG(PORTA,3)
#define PORTA_PCR4                               PORT_PCR_REG(PORTA,4)
#define PORTA_PCR5                               PORT_PCR_REG(PORTA,5)
#define PORTA_PCR6                               PORT_PCR_REG(PORTA,6)
#define PORTA_PCR7                               PORT_PCR_REG(PORTA,7)
#define PORTA_GPCLR                              PORT_GPCLR_REG(PORTA)
#define PORTA_GPCHR                              PORT_GPCHR_REG(PORTA)
#define PORTA_ISFR                               PORT_ISFR_REG(PORTA)
/* PORTB */
#define PORTB_PCR0                               PORT_PCR_REG(PORTB,0)
#define PORTB_PCR1                               PORT_PCR_REG(PORTB,1)
#define PORTB_PCR2                               PORT_PCR_REG(PORTB,2)
#define PORTB_PCR3                               PORT_PCR_REG(PORTB,3)
#define PORTB_PCR4                               PORT_PCR_REG(PORTB,4)
#define PORTB_PCR5                               PORT_PCR_REG(PORTB,5)
#define PORTB_PCR6                               PORT_PCR_REG(PORTB,6)
#define PORTB_PCR7                               PORT_PCR_REG(PORTB,7)
#define PORTB_GPCLR                              PORT_GPCLR_REG(PORTB)
#define PORTB_GPCHR                              PORT_GPCHR_REG(PORTB)
#define PORTB_ISFR                               PORT_ISFR_REG(PORTB)
/* PORTC */
#define PORTC_PCR0                               PORT_PCR_REG(PORTC,0)
#define PORTC_PCR1                               PORT_PCR_REG(PORTC,1)
#define PORTC_PCR2                               PORT_PCR_REG(PORTC,2)
#define PORTC_PCR3                               PORT_PCR_REG(PORTC,3)
#define PORTC_PCR4                               PORT_PCR_REG(PORTC,4)
#define PORTC_PCR5                               PORT_PCR_REG(PORTC,5)
#define PORTC_PCR6                               PORT_PCR_REG(PORTC,6)
#define PORTC_PCR7                               PORT_PCR_REG(PORTC,7)
#define PORTC_GPCLR                              PORT_GPCLR_REG(PORTC)
#define PORTC_GPCHR                              PORT_GPCHR_REG(PORTC)
#define PORTC_ISFR                               PORT_ISFR_REG(PORTC)
/* PORTD */
#define PORTD_PCR0                               PORT_PCR_REG(PORTD,0)
#define PORTD_PCR1                               PORT_PCR_REG(PORTD,1)
#define PORTD_PCR2                               PORT_PCR_REG(PORTD,2)
#define PORTD_PCR3                               PORT_PCR_REG(PORTD,3)
#define PORTD_PCR4                               PORT_PCR_REG(PORTD,4)
#define PORTD_PCR5                               PORT_PCR_REG(PORTD,5)
#define PORTD_PCR6                               PORT_PCR_REG(PORTD,6)
#define PORTD_PCR7                               PORT_PCR_REG(PORTD,7)
#define PORTD_GPCLR                              PORT_GPCLR_REG(PORTD)
#define PORTD_GPCHR                              PORT_GPCHR_REG(PORTD)
#define PORTD_ISFR                               PORT_ISFR_REG(PORTD)
/* PORTE */
#define PORTE_PCR0                               PORT_PCR_REG(PORTE,0)
#define PORTE_PCR1                               PORT_PCR_REG(PORTE,1)
#define PORTE_PCR2                               PORT_PCR_REG(PORTE,2)
#define PORTE_PCR3                               PORT_PCR_REG(PORTE,3)
#define PORTE_PCR4                               PORT_PCR_REG(PORTE,4)
#define PORTE_PCR5                               PORT_PCR_REG(PORTE,5)
#define PORTE_PCR6                               PORT_PCR_REG(PORTE,6)
#define PORTE_PCR7                               PORT_PCR_REG(PORTE,7)
#define PORTE_GPCLR                              PORT_GPCLR_REG(PORTE)
#define PORTE_GPCHR                              PORT_GPCHR_REG(PORTE)
#define PORTE_ISFR                               PORT_ISFR_REG(PORTE)
#define PORTE_DFER                               PORT_DFER_REG(PORTE)
#define PORTE_DFCR                               PORT_DFCR_REG(PORTE)
#define PORTE_DFWR                               PORT_DFWR_REG(PORTE)
/* PORTF */
#define PORTF_PCR0                               PORT_PCR_REG(PORTF,0)
#define PORTF_PCR1                               PORT_PCR_REG(PORTF,1)
#define PORTF_PCR2                               PORT_PCR_REG(PORTF,2)
#define PORTF_PCR3                               PORT_PCR_REG(PORTF,3)
#define PORTF_PCR4                               PORT_PCR_REG(PORTF,4)
#define PORTF_PCR5                               PORT_PCR_REG(PORTF,5)
#define PORTF_PCR6                               PORT_PCR_REG(PORTF,6)
#define PORTF_PCR7                               PORT_PCR_REG(PORTF,7)
#define PORTF_GPCLR                              PORT_GPCLR_REG(PORTF)
#define PORTF_GPCHR                              PORT_GPCHR_REG(PORTF)
#define PORTF_ISFR                               PORT_ISFR_REG(PORTF)
/* PORTG */
#define PORTG_PCR0                               PORT_PCR_REG(PORTG,0)
#define PORTG_PCR1                               PORT_PCR_REG(PORTG,1)
#define PORTG_PCR2                               PORT_PCR_REG(PORTG,2)
#define PORTG_PCR3                               PORT_PCR_REG(PORTG,3)
#define PORTG_PCR4                               PORT_PCR_REG(PORTG,4)
#define PORTG_PCR5                               PORT_PCR_REG(PORTG,5)
#define PORTG_PCR6                               PORT_PCR_REG(PORTG,6)
#define PORTG_PCR7                               PORT_PCR_REG(PORTG,7)
#define PORTG_GPCLR                              PORT_GPCLR_REG(PORTG)
#define PORTG_GPCHR                              PORT_GPCHR_REG(PORTG)
#define PORTG_ISFR                               PORT_ISFR_REG(PORTG)
/* PORTH */
#define PORTH_PCR0                               PORT_PCR_REG(PORTH,0)
#define PORTH_PCR1                               PORT_PCR_REG(PORTH,1)
#define PORTH_PCR2                               PORT_PCR_REG(PORTH,2)
#define PORTH_PCR3                               PORT_PCR_REG(PORTH,3)
#define PORTH_PCR4                               PORT_PCR_REG(PORTH,4)
#define PORTH_PCR5                               PORT_PCR_REG(PORTH,5)
#define PORTH_PCR6                               PORT_PCR_REG(PORTH,6)
#define PORTH_PCR7                               PORT_PCR_REG(PORTH,7)
#define PORTH_GPCLR                              PORT_GPCLR_REG(PORTH)
#define PORTH_GPCHR                              PORT_GPCHR_REG(PORTH)
#define PORTH_ISFR                               PORT_ISFR_REG(PORTH)
/* PORTI */
#define PORTI_PCR0                               PORT_PCR_REG(PORTI,0)
#define PORTI_PCR1                               PORT_PCR_REG(PORTI,1)
#define PORTI_PCR2                               PORT_PCR_REG(PORTI,2)
#define PORTI_PCR3                               PORT_PCR_REG(PORTI,3)
#define PORTI_PCR4                               PORT_PCR_REG(PORTI,4)
#define PORTI_PCR5                               PORT_PCR_REG(PORTI,5)
#define PORTI_PCR6                               PORT_PCR_REG(PORTI,6)
#define PORTI_PCR7                               PORT_PCR_REG(PORTI,7)
#define PORTI_GPCLR                              PORT_GPCLR_REG(PORTI)
#define PORTI_GPCHR                              PORT_GPCHR_REG(PORTI)
#define PORTI_ISFR                               PORT_ISFR_REG(PORTI)
/* PORTJ */
#define PORTJ_PCR0                               PORT_PCR_REG(PORTJ,0)
#define PORTJ_PCR1                               PORT_PCR_REG(PORTJ,1)
#define PORTJ_PCR2                               PORT_PCR_REG(PORTJ,2)
#define PORTJ_PCR3                               PORT_PCR_REG(PORTJ,3)
#define PORTJ_PCR4                               PORT_PCR_REG(PORTJ,4)
#define PORTJ_PCR5                               PORT_PCR_REG(PORTJ,5)
#define PORTJ_PCR6                               PORT_PCR_REG(PORTJ,6)
#define PORTJ_PCR7                               PORT_PCR_REG(PORTJ,7)
#define PORTJ_GPCLR                              PORT_GPCLR_REG(PORTJ)
#define PORTJ_GPCHR                              PORT_GPCHR_REG(PORTJ)
#define PORTJ_ISFR                               PORT_ISFR_REG(PORTJ)
/* PORTK */
#define PORTK_PCR0                               PORT_PCR_REG(PORTK,0)
#define PORTK_PCR1                               PORT_PCR_REG(PORTK,1)
#define PORTK_PCR2                               PORT_PCR_REG(PORTK,2)
#define PORTK_PCR3                               PORT_PCR_REG(PORTK,3)
#define PORTK_PCR4                               PORT_PCR_REG(PORTK,4)
#define PORTK_PCR5                               PORT_PCR_REG(PORTK,5)
#define PORTK_PCR6                               PORT_PCR_REG(PORTK,6)
#define PORTK_PCR7                               PORT_PCR_REG(PORTK,7)
#define PORTK_GPCLR                              PORT_GPCLR_REG(PORTK)
#define PORTK_GPCHR                              PORT_GPCHR_REG(PORTK)
#define PORTK_ISFR                               PORT_ISFR_REG(PORTK)
/* PORTL */
#define PORTL_PCR0                               PORT_PCR_REG(PORTL,0)
#define PORTL_PCR1                               PORT_PCR_REG(PORTL,1)
#define PORTL_PCR2                               PORT_PCR_REG(PORTL,2)
#define PORTL_PCR3                               PORT_PCR_REG(PORTL,3)
#define PORTL_PCR4                               PORT_PCR_REG(PORTL,4)
#define PORTL_PCR5                               PORT_PCR_REG(PORTL,5)
#define PORTL_PCR6                               PORT_PCR_REG(PORTL,6)
#define PORTL_PCR7                               PORT_PCR_REG(PORTL,7)
#define PORTL_GPCLR                              PORT_GPCLR_REG(PORTL)
#define PORTL_GPCHR                              PORT_GPCHR_REG(PORTL)
#define PORTL_ISFR                               PORT_ISFR_REG(PORTL)
/* PORTM */
#define PORTM_PCR0                               PORT_PCR_REG(PORTM,0)
#define PORTM_PCR1                               PORT_PCR_REG(PORTM,1)
#define PORTM_PCR2                               PORT_PCR_REG(PORTM,2)
#define PORTM_PCR3                               PORT_PCR_REG(PORTM,3)
#define PORTM_PCR4                               PORT_PCR_REG(PORTM,4)
#define PORTM_PCR5                               PORT_PCR_REG(PORTM,5)
#define PORTM_PCR6                               PORT_PCR_REG(PORTM,6)
#define PORTM_PCR7                               PORT_PCR_REG(PORTM,7)
#define PORTM_GPCLR                              PORT_GPCLR_REG(PORTM)
#define PORTM_GPCHR                              PORT_GPCHR_REG(PORTM)
#define PORTM_ISFR                               PORT_ISFR_REG(PORTM)

/* PORT - Register array accessors */
#define PORTA_PCR(index)                         PORT_PCR_REG(PORTA,index)
#define PORTB_PCR(index)                         PORT_PCR_REG(PORTB,index)
#define PORTC_PCR(index)                         PORT_PCR_REG(PORTC,index)
#define PORTD_PCR(index)                         PORT_PCR_REG(PORTD,index)
#define PORTE_PCR(index)                         PORT_PCR_REG(PORTE,index)
#define PORTF_PCR(index)                         PORT_PCR_REG(PORTF,index)
#define PORTG_PCR(index)                         PORT_PCR_REG(PORTG,index)
#define PORTH_PCR(index)                         PORT_PCR_REG(PORTH,index)
#define PORTI_PCR(index)                         PORT_PCR_REG(PORTI,index)
#define PORTJ_PCR(index)                         PORT_PCR_REG(PORTJ,index)
#define PORTK_PCR(index)                         PORT_PCR_REG(PORTK,index)
#define PORTL_PCR(index)                         PORT_PCR_REG(PORTL,index)
#define PORTM_PCR(index)                         PORT_PCR_REG(PORTM,index)

/*!
 * @}
 */ /* end of group PORT_Register_Accessor_Macros */


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
       uint8_t RESERVED_1[2];
  __IO uint8_t SSRS0;                              /**< Sticky System Reset Status Register 0, offset: 0x8 */
  __IO uint8_t SSRS1;                              /**< Sticky System Reset Status Register 1, offset: 0x9 */
} RCM_Type, *RCM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Register_Accessor_Macros RCM - Register accessor macros
 * @{
 */


/* RCM - Register accessors */
#define RCM_SRS0_REG(base)                       ((base)->SRS0)
#define RCM_SRS1_REG(base)                       ((base)->SRS1)
#define RCM_RPFC_REG(base)                       ((base)->RPFC)
#define RCM_RPFW_REG(base)                       ((base)->RPFW)
#define RCM_SSRS0_REG(base)                      ((base)->SSRS0)
#define RCM_SSRS1_REG(base)                      ((base)->SSRS1)

/*!
 * @}
 */ /* end of group RCM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- RCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Register_Masks RCM Register Masks
 * @{
 */

/* SRS0 Bit Fields */
#define RCM_SRS0_WAKEUP_MASK                     0x1u
#define RCM_SRS0_WAKEUP_SHIFT                    0
#define RCM_SRS0_WAKEUP_WIDTH                    1
#define RCM_SRS0_WAKEUP(x)                       (((uint8_t)(((uint8_t)(x))<<RCM_SRS0_WAKEUP_SHIFT))&RCM_SRS0_WAKEUP_MASK)
#define RCM_SRS0_LVD_MASK                        0x2u
#define RCM_SRS0_LVD_SHIFT                       1
#define RCM_SRS0_LVD_WIDTH                       1
#define RCM_SRS0_LVD(x)                          (((uint8_t)(((uint8_t)(x))<<RCM_SRS0_LVD_SHIFT))&RCM_SRS0_LVD_MASK)
#define RCM_SRS0_LOC_MASK                        0x4u
#define RCM_SRS0_LOC_SHIFT                       2
#define RCM_SRS0_LOC_WIDTH                       1
#define RCM_SRS0_LOC(x)                          (((uint8_t)(((uint8_t)(x))<<RCM_SRS0_LOC_SHIFT))&RCM_SRS0_LOC_MASK)
#define RCM_SRS0_LOL_MASK                        0x8u
#define RCM_SRS0_LOL_SHIFT                       3
#define RCM_SRS0_LOL_WIDTH                       1
#define RCM_SRS0_LOL(x)                          (((uint8_t)(((uint8_t)(x))<<RCM_SRS0_LOL_SHIFT))&RCM_SRS0_LOL_MASK)
#define RCM_SRS0_WDOG_MASK                       0x20u
#define RCM_SRS0_WDOG_SHIFT                      5
#define RCM_SRS0_WDOG_WIDTH                      1
#define RCM_SRS0_WDOG(x)                         (((uint8_t)(((uint8_t)(x))<<RCM_SRS0_WDOG_SHIFT))&RCM_SRS0_WDOG_MASK)
#define RCM_SRS0_PIN_MASK                        0x40u
#define RCM_SRS0_PIN_SHIFT                       6
#define RCM_SRS0_PIN_WIDTH                       1
#define RCM_SRS0_PIN(x)                          (((uint8_t)(((uint8_t)(x))<<RCM_SRS0_PIN_SHIFT))&RCM_SRS0_PIN_MASK)
#define RCM_SRS0_POR_MASK                        0x80u
#define RCM_SRS0_POR_SHIFT                       7
#define RCM_SRS0_POR_WIDTH                       1
#define RCM_SRS0_POR(x)                          (((uint8_t)(((uint8_t)(x))<<RCM_SRS0_POR_SHIFT))&RCM_SRS0_POR_MASK)
/* SRS1 Bit Fields */
#define RCM_SRS1_LOCKUP_MASK                     0x2u
#define RCM_SRS1_LOCKUP_SHIFT                    1
#define RCM_SRS1_LOCKUP_WIDTH                    1
#define RCM_SRS1_LOCKUP(x)                       (((uint8_t)(((uint8_t)(x))<<RCM_SRS1_LOCKUP_SHIFT))&RCM_SRS1_LOCKUP_MASK)
#define RCM_SRS1_SW_MASK                         0x4u
#define RCM_SRS1_SW_SHIFT                        2
#define RCM_SRS1_SW_WIDTH                        1
#define RCM_SRS1_SW(x)                           (((uint8_t)(((uint8_t)(x))<<RCM_SRS1_SW_SHIFT))&RCM_SRS1_SW_MASK)
#define RCM_SRS1_MDM_AP_MASK                     0x8u
#define RCM_SRS1_MDM_AP_SHIFT                    3
#define RCM_SRS1_MDM_AP_WIDTH                    1
#define RCM_SRS1_MDM_AP(x)                       (((uint8_t)(((uint8_t)(x))<<RCM_SRS1_MDM_AP_SHIFT))&RCM_SRS1_MDM_AP_MASK)
#define RCM_SRS1_SACKERR_MASK                    0x20u
#define RCM_SRS1_SACKERR_SHIFT                   5
#define RCM_SRS1_SACKERR_WIDTH                   1
#define RCM_SRS1_SACKERR(x)                      (((uint8_t)(((uint8_t)(x))<<RCM_SRS1_SACKERR_SHIFT))&RCM_SRS1_SACKERR_MASK)
/* RPFC Bit Fields */
#define RCM_RPFC_RSTFLTSRW_MASK                  0x3u
#define RCM_RPFC_RSTFLTSRW_SHIFT                 0
#define RCM_RPFC_RSTFLTSRW_WIDTH                 2
#define RCM_RPFC_RSTFLTSRW(x)                    (((uint8_t)(((uint8_t)(x))<<RCM_RPFC_RSTFLTSRW_SHIFT))&RCM_RPFC_RSTFLTSRW_MASK)
#define RCM_RPFC_RSTFLTSS_MASK                   0x4u
#define RCM_RPFC_RSTFLTSS_SHIFT                  2
#define RCM_RPFC_RSTFLTSS_WIDTH                  1
#define RCM_RPFC_RSTFLTSS(x)                     (((uint8_t)(((uint8_t)(x))<<RCM_RPFC_RSTFLTSS_SHIFT))&RCM_RPFC_RSTFLTSS_MASK)
/* RPFW Bit Fields */
#define RCM_RPFW_RSTFLTSEL_MASK                  0x1Fu
#define RCM_RPFW_RSTFLTSEL_SHIFT                 0
#define RCM_RPFW_RSTFLTSEL_WIDTH                 5
#define RCM_RPFW_RSTFLTSEL(x)                    (((uint8_t)(((uint8_t)(x))<<RCM_RPFW_RSTFLTSEL_SHIFT))&RCM_RPFW_RSTFLTSEL_MASK)
/* SSRS0 Bit Fields */
#define RCM_SSRS0_SWAKEUP_MASK                   0x1u
#define RCM_SSRS0_SWAKEUP_SHIFT                  0
#define RCM_SSRS0_SWAKEUP_WIDTH                  1
#define RCM_SSRS0_SWAKEUP(x)                     (((uint8_t)(((uint8_t)(x))<<RCM_SSRS0_SWAKEUP_SHIFT))&RCM_SSRS0_SWAKEUP_MASK)
#define RCM_SSRS0_SLVD_MASK                      0x2u
#define RCM_SSRS0_SLVD_SHIFT                     1
#define RCM_SSRS0_SLVD_WIDTH                     1
#define RCM_SSRS0_SLVD(x)                        (((uint8_t)(((uint8_t)(x))<<RCM_SSRS0_SLVD_SHIFT))&RCM_SSRS0_SLVD_MASK)
#define RCM_SSRS0_SLOL_MASK                      0x8u
#define RCM_SSRS0_SLOL_SHIFT                     3
#define RCM_SSRS0_SLOL_WIDTH                     1
#define RCM_SSRS0_SLOL(x)                        (((uint8_t)(((uint8_t)(x))<<RCM_SSRS0_SLOL_SHIFT))&RCM_SSRS0_SLOL_MASK)
#define RCM_SSRS0_SWDOG_MASK                     0x20u
#define RCM_SSRS0_SWDOG_SHIFT                    5
#define RCM_SSRS0_SWDOG_WIDTH                    1
#define RCM_SSRS0_SWDOG(x)                       (((uint8_t)(((uint8_t)(x))<<RCM_SSRS0_SWDOG_SHIFT))&RCM_SSRS0_SWDOG_MASK)
#define RCM_SSRS0_SPIN_MASK                      0x40u
#define RCM_SSRS0_SPIN_SHIFT                     6
#define RCM_SSRS0_SPIN_WIDTH                     1
#define RCM_SSRS0_SPIN(x)                        (((uint8_t)(((uint8_t)(x))<<RCM_SSRS0_SPIN_SHIFT))&RCM_SSRS0_SPIN_MASK)
#define RCM_SSRS0_SPOR_MASK                      0x80u
#define RCM_SSRS0_SPOR_SHIFT                     7
#define RCM_SSRS0_SPOR_WIDTH                     1
#define RCM_SSRS0_SPOR(x)                        (((uint8_t)(((uint8_t)(x))<<RCM_SSRS0_SPOR_SHIFT))&RCM_SSRS0_SPOR_MASK)
/* SSRS1 Bit Fields */
#define RCM_SSRS1_SLOCKUP_MASK                   0x2u
#define RCM_SSRS1_SLOCKUP_SHIFT                  1
#define RCM_SSRS1_SLOCKUP_WIDTH                  1
#define RCM_SSRS1_SLOCKUP(x)                     (((uint8_t)(((uint8_t)(x))<<RCM_SSRS1_SLOCKUP_SHIFT))&RCM_SSRS1_SLOCKUP_MASK)
#define RCM_SSRS1_SSW_MASK                       0x4u
#define RCM_SSRS1_SSW_SHIFT                      2
#define RCM_SSRS1_SSW_WIDTH                      1
#define RCM_SSRS1_SSW(x)                         (((uint8_t)(((uint8_t)(x))<<RCM_SSRS1_SSW_SHIFT))&RCM_SSRS1_SSW_MASK)
#define RCM_SSRS1_SMDM_AP_MASK                   0x8u
#define RCM_SSRS1_SMDM_AP_SHIFT                  3
#define RCM_SSRS1_SMDM_AP_WIDTH                  1
#define RCM_SSRS1_SMDM_AP(x)                     (((uint8_t)(((uint8_t)(x))<<RCM_SSRS1_SMDM_AP_SHIFT))&RCM_SSRS1_SMDM_AP_MASK)
#define RCM_SSRS1_SSACKERR_MASK                  0x20u
#define RCM_SSRS1_SSACKERR_SHIFT                 5
#define RCM_SSRS1_SSACKERR_WIDTH                 1
#define RCM_SSRS1_SSACKERR(x)                    (((uint8_t)(((uint8_t)(x))<<RCM_SSRS1_SSACKERR_SHIFT))&RCM_SSRS1_SSACKERR_MASK)

/*!
 * @}
 */ /* end of group RCM_Register_Masks */


/* RCM - Peripheral instance base addresses */
/** Peripheral RCM base address */
#define RCM_BASE                                 (0x4007B000u)
/** Peripheral RCM base pointer */
#define RCM                                      ((RCM_Type *)RCM_BASE)
#define RCM_BASE_PTR                             (RCM)
/** Array initializer of RCM peripheral base addresses */
#define RCM_BASE_ADDRS                           { RCM_BASE }
/** Array initializer of RCM peripheral base pointers */
#define RCM_BASE_PTRS                            { RCM }

/* ----------------------------------------------------------------------------
   -- RCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Register_Accessor_Macros RCM - Register accessor macros
 * @{
 */


/* RCM - Register instance definitions */
/* RCM */
#define RCM_SRS0                                 RCM_SRS0_REG(RCM)
#define RCM_SRS1                                 RCM_SRS1_REG(RCM)
#define RCM_RPFC                                 RCM_RPFC_REG(RCM)
#define RCM_RPFW                                 RCM_RPFW_REG(RCM)
#define RCM_SSRS0                                RCM_SSRS0_REG(RCM)
#define RCM_SSRS1                                RCM_SSRS1_REG(RCM)

/*!
 * @}
 */ /* end of group RCM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group RCM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RNG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RNG_Peripheral_Access_Layer RNG Peripheral Access Layer
 * @{
 */

/** RNG - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR;                                /**< RNGA Control Register, offset: 0x0 */
  __I  uint32_t SR;                                /**< RNGA Status Register, offset: 0x4 */
  __O  uint32_t ER;                                /**< RNGA Entropy Register, offset: 0x8 */
  __I  uint32_t OR;                                /**< RNGA Output Register, offset: 0xC */
} RNG_Type, *RNG_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RNG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RNG_Register_Accessor_Macros RNG - Register accessor macros
 * @{
 */


/* RNG - Register accessors */
#define RNG_CR_REG(base)                         ((base)->CR)
#define RNG_SR_REG(base)                         ((base)->SR)
#define RNG_ER_REG(base)                         ((base)->ER)
#define RNG_OR_REG(base)                         ((base)->OR)

/*!
 * @}
 */ /* end of group RNG_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- RNG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RNG_Register_Masks RNG Register Masks
 * @{
 */

/* CR Bit Fields */
#define RNG_CR_GO_MASK                           0x1u
#define RNG_CR_GO_SHIFT                          0
#define RNG_CR_GO_WIDTH                          1
#define RNG_CR_GO(x)                             (((uint32_t)(((uint32_t)(x))<<RNG_CR_GO_SHIFT))&RNG_CR_GO_MASK)
#define RNG_CR_HA_MASK                           0x2u
#define RNG_CR_HA_SHIFT                          1
#define RNG_CR_HA_WIDTH                          1
#define RNG_CR_HA(x)                             (((uint32_t)(((uint32_t)(x))<<RNG_CR_HA_SHIFT))&RNG_CR_HA_MASK)
#define RNG_CR_INTM_MASK                         0x4u
#define RNG_CR_INTM_SHIFT                        2
#define RNG_CR_INTM_WIDTH                        1
#define RNG_CR_INTM(x)                           (((uint32_t)(((uint32_t)(x))<<RNG_CR_INTM_SHIFT))&RNG_CR_INTM_MASK)
#define RNG_CR_CLRI_MASK                         0x8u
#define RNG_CR_CLRI_SHIFT                        3
#define RNG_CR_CLRI_WIDTH                        1
#define RNG_CR_CLRI(x)                           (((uint32_t)(((uint32_t)(x))<<RNG_CR_CLRI_SHIFT))&RNG_CR_CLRI_MASK)
#define RNG_CR_SLP_MASK                          0x10u
#define RNG_CR_SLP_SHIFT                         4
#define RNG_CR_SLP_WIDTH                         1
#define RNG_CR_SLP(x)                            (((uint32_t)(((uint32_t)(x))<<RNG_CR_SLP_SHIFT))&RNG_CR_SLP_MASK)
/* SR Bit Fields */
#define RNG_SR_SECV_MASK                         0x1u
#define RNG_SR_SECV_SHIFT                        0
#define RNG_SR_SECV_WIDTH                        1
#define RNG_SR_SECV(x)                           (((uint32_t)(((uint32_t)(x))<<RNG_SR_SECV_SHIFT))&RNG_SR_SECV_MASK)
#define RNG_SR_LRS_MASK                          0x2u
#define RNG_SR_LRS_SHIFT                         1
#define RNG_SR_LRS_WIDTH                         1
#define RNG_SR_LRS(x)                            (((uint32_t)(((uint32_t)(x))<<RNG_SR_LRS_SHIFT))&RNG_SR_LRS_MASK)
#define RNG_SR_ORU_MASK                          0x4u
#define RNG_SR_ORU_SHIFT                         2
#define RNG_SR_ORU_WIDTH                         1
#define RNG_SR_ORU(x)                            (((uint32_t)(((uint32_t)(x))<<RNG_SR_ORU_SHIFT))&RNG_SR_ORU_MASK)
#define RNG_SR_ERRI_MASK                         0x8u
#define RNG_SR_ERRI_SHIFT                        3
#define RNG_SR_ERRI_WIDTH                        1
#define RNG_SR_ERRI(x)                           (((uint32_t)(((uint32_t)(x))<<RNG_SR_ERRI_SHIFT))&RNG_SR_ERRI_MASK)
#define RNG_SR_SLP_MASK                          0x10u
#define RNG_SR_SLP_SHIFT                         4
#define RNG_SR_SLP_WIDTH                         1
#define RNG_SR_SLP(x)                            (((uint32_t)(((uint32_t)(x))<<RNG_SR_SLP_SHIFT))&RNG_SR_SLP_MASK)
#define RNG_SR_OREG_LVL_MASK                     0xFF00u
#define RNG_SR_OREG_LVL_SHIFT                    8
#define RNG_SR_OREG_LVL_WIDTH                    8
#define RNG_SR_OREG_LVL(x)                       (((uint32_t)(((uint32_t)(x))<<RNG_SR_OREG_LVL_SHIFT))&RNG_SR_OREG_LVL_MASK)
#define RNG_SR_OREG_SIZE_MASK                    0xFF0000u
#define RNG_SR_OREG_SIZE_SHIFT                   16
#define RNG_SR_OREG_SIZE_WIDTH                   8
#define RNG_SR_OREG_SIZE(x)                      (((uint32_t)(((uint32_t)(x))<<RNG_SR_OREG_SIZE_SHIFT))&RNG_SR_OREG_SIZE_MASK)
/* ER Bit Fields */
#define RNG_ER_EXT_ENT_MASK                      0xFFFFFFFFu
#define RNG_ER_EXT_ENT_SHIFT                     0
#define RNG_ER_EXT_ENT_WIDTH                     32
#define RNG_ER_EXT_ENT(x)                        (((uint32_t)(((uint32_t)(x))<<RNG_ER_EXT_ENT_SHIFT))&RNG_ER_EXT_ENT_MASK)
/* OR Bit Fields */
#define RNG_OR_RANDOUT_MASK                      0xFFFFFFFFu
#define RNG_OR_RANDOUT_SHIFT                     0
#define RNG_OR_RANDOUT_WIDTH                     32
#define RNG_OR_RANDOUT(x)                        (((uint32_t)(((uint32_t)(x))<<RNG_OR_RANDOUT_SHIFT))&RNG_OR_RANDOUT_MASK)

/*!
 * @}
 */ /* end of group RNG_Register_Masks */


/* RNG - Peripheral instance base addresses */
/** Peripheral RNG base address */
#define RNG_BASE                                 (0x40029000u)
/** Peripheral RNG base pointer */
#define RNG                                      ((RNG_Type *)RNG_BASE)
#define RNG_BASE_PTR                             (RNG)
/** Array initializer of RNG peripheral base addresses */
#define RNG_BASE_ADDRS                           { RNG_BASE }
/** Array initializer of RNG peripheral base pointers */
#define RNG_BASE_PTRS                            { RNG }
/** Interrupt vectors for the RNG peripheral type */
#define RNG_IRQS                                 { RNGA_IRQn }

/* ----------------------------------------------------------------------------
   -- RNG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RNG_Register_Accessor_Macros RNG - Register accessor macros
 * @{
 */


/* RNG - Register instance definitions */
/* RNG */
#define RNG_CR                                   RNG_CR_REG(RNG)
#define RNG_SR                                   RNG_SR_REG(RNG)
#define RNG_ER                                   RNG_ER_REG(RNG)
#define RNG_OR                                   RNG_OR_REG(RNG)

/*!
 * @}
 */ /* end of group RNG_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group RNG_Peripheral_Access_Layer */


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
} ROM_Type, *ROM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ROM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Accessor_Macros ROM - Register accessor macros
 * @{
 */


/* ROM - Register accessors */
#define ROM_ENTRY_REG(base,index)                ((base)->ENTRY[index])
#define ROM_ENTRY_COUNT                          3
#define ROM_TABLEMARK_REG(base)                  ((base)->TABLEMARK)
#define ROM_SYSACCESS_REG(base)                  ((base)->SYSACCESS)
#define ROM_PERIPHID4_REG(base)                  ((base)->PERIPHID4)
#define ROM_PERIPHID5_REG(base)                  ((base)->PERIPHID5)
#define ROM_PERIPHID6_REG(base)                  ((base)->PERIPHID6)
#define ROM_PERIPHID7_REG(base)                  ((base)->PERIPHID7)
#define ROM_PERIPHID0_REG(base)                  ((base)->PERIPHID0)
#define ROM_PERIPHID1_REG(base)                  ((base)->PERIPHID1)
#define ROM_PERIPHID2_REG(base)                  ((base)->PERIPHID2)
#define ROM_PERIPHID3_REG(base)                  ((base)->PERIPHID3)
#define ROM_COMPID_REG(base,index)               ((base)->COMPID[index])
#define ROM_COMPID_COUNT                         4

/*!
 * @}
 */ /* end of group ROM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ROM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Masks ROM Register Masks
 * @{
 */

/* ENTRY Bit Fields */
#define ROM_ENTRY_ENTRY_MASK                     0xFFFFFFFFu
#define ROM_ENTRY_ENTRY_SHIFT                    0
#define ROM_ENTRY_ENTRY_WIDTH                    32
#define ROM_ENTRY_ENTRY(x)                       (((uint32_t)(((uint32_t)(x))<<ROM_ENTRY_ENTRY_SHIFT))&ROM_ENTRY_ENTRY_MASK)
/* TABLEMARK Bit Fields */
#define ROM_TABLEMARK_MARK_MASK                  0xFFFFFFFFu
#define ROM_TABLEMARK_MARK_SHIFT                 0
#define ROM_TABLEMARK_MARK_WIDTH                 32
#define ROM_TABLEMARK_MARK(x)                    (((uint32_t)(((uint32_t)(x))<<ROM_TABLEMARK_MARK_SHIFT))&ROM_TABLEMARK_MARK_MASK)
/* SYSACCESS Bit Fields */
#define ROM_SYSACCESS_SYSACCESS_MASK             0xFFFFFFFFu
#define ROM_SYSACCESS_SYSACCESS_SHIFT            0
#define ROM_SYSACCESS_SYSACCESS_WIDTH            32
#define ROM_SYSACCESS_SYSACCESS(x)               (((uint32_t)(((uint32_t)(x))<<ROM_SYSACCESS_SYSACCESS_SHIFT))&ROM_SYSACCESS_SYSACCESS_MASK)
/* PERIPHID4 Bit Fields */
#define ROM_PERIPHID4_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID4_PERIPHID_SHIFT             0
#define ROM_PERIPHID4_PERIPHID_WIDTH             32
#define ROM_PERIPHID4_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID4_PERIPHID_SHIFT))&ROM_PERIPHID4_PERIPHID_MASK)
/* PERIPHID5 Bit Fields */
#define ROM_PERIPHID5_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID5_PERIPHID_SHIFT             0
#define ROM_PERIPHID5_PERIPHID_WIDTH             32
#define ROM_PERIPHID5_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID5_PERIPHID_SHIFT))&ROM_PERIPHID5_PERIPHID_MASK)
/* PERIPHID6 Bit Fields */
#define ROM_PERIPHID6_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID6_PERIPHID_SHIFT             0
#define ROM_PERIPHID6_PERIPHID_WIDTH             32
#define ROM_PERIPHID6_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID6_PERIPHID_SHIFT))&ROM_PERIPHID6_PERIPHID_MASK)
/* PERIPHID7 Bit Fields */
#define ROM_PERIPHID7_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID7_PERIPHID_SHIFT             0
#define ROM_PERIPHID7_PERIPHID_WIDTH             32
#define ROM_PERIPHID7_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID7_PERIPHID_SHIFT))&ROM_PERIPHID7_PERIPHID_MASK)
/* PERIPHID0 Bit Fields */
#define ROM_PERIPHID0_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID0_PERIPHID_SHIFT             0
#define ROM_PERIPHID0_PERIPHID_WIDTH             32
#define ROM_PERIPHID0_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID0_PERIPHID_SHIFT))&ROM_PERIPHID0_PERIPHID_MASK)
/* PERIPHID1 Bit Fields */
#define ROM_PERIPHID1_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID1_PERIPHID_SHIFT             0
#define ROM_PERIPHID1_PERIPHID_WIDTH             32
#define ROM_PERIPHID1_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID1_PERIPHID_SHIFT))&ROM_PERIPHID1_PERIPHID_MASK)
/* PERIPHID2 Bit Fields */
#define ROM_PERIPHID2_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID2_PERIPHID_SHIFT             0
#define ROM_PERIPHID2_PERIPHID_WIDTH             32
#define ROM_PERIPHID2_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID2_PERIPHID_SHIFT))&ROM_PERIPHID2_PERIPHID_MASK)
/* PERIPHID3 Bit Fields */
#define ROM_PERIPHID3_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID3_PERIPHID_SHIFT             0
#define ROM_PERIPHID3_PERIPHID_WIDTH             32
#define ROM_PERIPHID3_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID3_PERIPHID_SHIFT))&ROM_PERIPHID3_PERIPHID_MASK)
/* COMPID Bit Fields */
#define ROM_COMPID_COMPID_MASK                   0xFFFFFFFFu
#define ROM_COMPID_COMPID_SHIFT                  0
#define ROM_COMPID_COMPID_WIDTH                  32
#define ROM_COMPID_COMPID(x)                     (((uint32_t)(((uint32_t)(x))<<ROM_COMPID_COMPID_SHIFT))&ROM_COMPID_COMPID_MASK)

/*!
 * @}
 */ /* end of group ROM_Register_Masks */


/* ROM - Peripheral instance base addresses */
/** Peripheral ROM base address */
#define ROM_BASE                                 (0xF0002000u)
/** Peripheral ROM base pointer */
#define ROM                                      ((ROM_Type *)ROM_BASE)
#define ROM_BASE_PTR                             (ROM)
/** Array initializer of ROM peripheral base addresses */
#define ROM_BASE_ADDRS                           { ROM_BASE }
/** Array initializer of ROM peripheral base pointers */
#define ROM_BASE_PTRS                            { ROM }

/* ----------------------------------------------------------------------------
   -- ROM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Accessor_Macros ROM - Register accessor macros
 * @{
 */


/* ROM - Register instance definitions */
/* ROM */
#define ROM_ENTRY0                               ROM_ENTRY_REG(ROM,0)
#define ROM_ENTRY1                               ROM_ENTRY_REG(ROM,1)
#define ROM_ENTRY2                               ROM_ENTRY_REG(ROM,2)
#define ROM_TABLEMARK                            ROM_TABLEMARK_REG(ROM)
#define ROM_SYSACCESS                            ROM_SYSACCESS_REG(ROM)
#define ROM_PERIPHID4                            ROM_PERIPHID4_REG(ROM)
#define ROM_PERIPHID5                            ROM_PERIPHID5_REG(ROM)
#define ROM_PERIPHID6                            ROM_PERIPHID6_REG(ROM)
#define ROM_PERIPHID7                            ROM_PERIPHID7_REG(ROM)
#define ROM_PERIPHID0                            ROM_PERIPHID0_REG(ROM)
#define ROM_PERIPHID1                            ROM_PERIPHID1_REG(ROM)
#define ROM_PERIPHID2                            ROM_PERIPHID2_REG(ROM)
#define ROM_PERIPHID3                            ROM_PERIPHID3_REG(ROM)
#define ROM_COMPID0                              ROM_COMPID_REG(ROM,0)
#define ROM_COMPID1                              ROM_COMPID_REG(ROM,1)
#define ROM_COMPID2                              ROM_COMPID_REG(ROM,2)
#define ROM_COMPID3                              ROM_COMPID_REG(ROM,3)

/* ROM - Register array accessors */
#define ROM_ENTRY(index)                         ROM_ENTRY_REG(ROM,index)
#define ROM_COMPID(index)                        ROM_COMPID_REG(ROM,index)

/*!
 * @}
 */ /* end of group ROM_Register_Accessor_Macros */


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
  __IO uint16_t YEARMON;                           /**< RTC Year and Month Counters Register, offset: 0x0 */
  __IO uint16_t DAYS;                              /**< RTC Days and Day-of-Week Counters Register, offset: 0x2 */
  __IO uint16_t HOURMIN;                           /**< RTC Hours and Minutes Counters Register, offset: 0x4 */
  __IO uint16_t SECONDS;                           /**< RTC Seconds Counters Register, offset: 0x6 */
  __IO uint16_t ALM_YEARMON;                       /**< RTC Year and Months Alarm Register, offset: 0x8 */
  __IO uint16_t ALM_DAYS;                          /**< RTC Days Alarm Register, offset: 0xA */
  __IO uint16_t ALM_HOURMIN;                       /**< RTC Hours and Minutes Alarm Register, offset: 0xC */
  __IO uint16_t ALM_SECONDS;                       /**< RTC Seconds Alarm Register, offset: 0xE */
  __IO uint16_t CTRL;                              /**< RTC Control Register, offset: 0x10 */
  __IO uint16_t STATUS;                            /**< RTC Status Register, offset: 0x12 */
  __IO uint16_t ISR;                               /**< RTC Interrupt Status Register, offset: 0x14 */
  __IO uint16_t IER;                               /**< RTC Interrupt Enable Register, offset: 0x16 */
       uint8_t RESERVED_0[8];
  __IO uint16_t GP_DATA_REG;                       /**< RTC General Purpose Data Register, offset: 0x20 */
  __IO uint16_t DST_HOUR;                          /**< RTC Daylight Saving Hour Register, offset: 0x22 */
  __IO uint16_t DST_MONTH;                         /**< RTC Daylight Saving Month Register, offset: 0x24 */
  __IO uint16_t DST_DAY;                           /**< RTC Daylight Saving Day Register, offset: 0x26 */
  __IO uint16_t COMPEN;                            /**< RTC Compensation Register, offset: 0x28 */
       uint8_t RESERVED_1[8];
  __IO uint16_t TAMPER_SCR;                        /**< RTC Tamper Status and Control Register, offset: 0x32 */
  __IO uint16_t FILTER01_CFG;                      /**< RTC Tamper 0 1 Filter Configuration Register, offset: 0x34 */
  __IO uint16_t FILTER2_CFG;                       /**< RTC Tamper 2 Filter Configuration Register, offset: 0x36 */
       uint8_t RESERVED_2[10];
  __IO uint16_t CTRL2;                             /**< RTC Control 2 Register, offset: 0x42 */
} RTC_Type, *RTC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RTC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Accessor_Macros RTC - Register accessor macros
 * @{
 */


/* RTC - Register accessors */
#define RTC_YEARMON_REG(base)                    ((base)->YEARMON)
#define RTC_DAYS_REG(base)                       ((base)->DAYS)
#define RTC_HOURMIN_REG(base)                    ((base)->HOURMIN)
#define RTC_SECONDS_REG(base)                    ((base)->SECONDS)
#define RTC_ALM_YEARMON_REG(base)                ((base)->ALM_YEARMON)
#define RTC_ALM_DAYS_REG(base)                   ((base)->ALM_DAYS)
#define RTC_ALM_HOURMIN_REG(base)                ((base)->ALM_HOURMIN)
#define RTC_ALM_SECONDS_REG(base)                ((base)->ALM_SECONDS)
#define RTC_CTRL_REG(base)                       ((base)->CTRL)
#define RTC_STATUS_REG(base)                     ((base)->STATUS)
#define RTC_ISR_REG(base)                        ((base)->ISR)
#define RTC_IER_REG(base)                        ((base)->IER)
#define RTC_GP_DATA_REG_REG(base)                ((base)->GP_DATA_REG)
#define RTC_DST_HOUR_REG(base)                   ((base)->DST_HOUR)
#define RTC_DST_MONTH_REG(base)                  ((base)->DST_MONTH)
#define RTC_DST_DAY_REG(base)                    ((base)->DST_DAY)
#define RTC_COMPEN_REG(base)                     ((base)->COMPEN)
#define RTC_TAMPER_SCR_REG(base)                 ((base)->TAMPER_SCR)
#define RTC_FILTER01_CFG_REG(base)               ((base)->FILTER01_CFG)
#define RTC_FILTER2_CFG_REG(base)                ((base)->FILTER2_CFG)
#define RTC_CTRL2_REG(base)                      ((base)->CTRL2)

/*!
 * @}
 */ /* end of group RTC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- RTC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Masks RTC Register Masks
 * @{
 */

/* YEARMON Bit Fields */
#define RTC_YEARMON_MON_CNT_MASK                 0xFu
#define RTC_YEARMON_MON_CNT_SHIFT                0
#define RTC_YEARMON_MON_CNT_WIDTH                4
#define RTC_YEARMON_MON_CNT(x)                   (((uint16_t)(((uint16_t)(x))<<RTC_YEARMON_MON_CNT_SHIFT))&RTC_YEARMON_MON_CNT_MASK)
#define RTC_YEARMON_YROFST_MASK                  0xFF00u
#define RTC_YEARMON_YROFST_SHIFT                 8
#define RTC_YEARMON_YROFST_WIDTH                 8
#define RTC_YEARMON_YROFST(x)                    (((uint16_t)(((uint16_t)(x))<<RTC_YEARMON_YROFST_SHIFT))&RTC_YEARMON_YROFST_MASK)
/* DAYS Bit Fields */
#define RTC_DAYS_DAY_CNT_MASK                    0x1Fu
#define RTC_DAYS_DAY_CNT_SHIFT                   0
#define RTC_DAYS_DAY_CNT_WIDTH                   5
#define RTC_DAYS_DAY_CNT(x)                      (((uint16_t)(((uint16_t)(x))<<RTC_DAYS_DAY_CNT_SHIFT))&RTC_DAYS_DAY_CNT_MASK)
#define RTC_DAYS_DOW_MASK                        0x700u
#define RTC_DAYS_DOW_SHIFT                       8
#define RTC_DAYS_DOW_WIDTH                       3
#define RTC_DAYS_DOW(x)                          (((uint16_t)(((uint16_t)(x))<<RTC_DAYS_DOW_SHIFT))&RTC_DAYS_DOW_MASK)
/* HOURMIN Bit Fields */
#define RTC_HOURMIN_MIN_CNT_MASK                 0x3Fu
#define RTC_HOURMIN_MIN_CNT_SHIFT                0
#define RTC_HOURMIN_MIN_CNT_WIDTH                6
#define RTC_HOURMIN_MIN_CNT(x)                   (((uint16_t)(((uint16_t)(x))<<RTC_HOURMIN_MIN_CNT_SHIFT))&RTC_HOURMIN_MIN_CNT_MASK)
#define RTC_HOURMIN_HOUR_CNT_MASK                0x1F00u
#define RTC_HOURMIN_HOUR_CNT_SHIFT               8
#define RTC_HOURMIN_HOUR_CNT_WIDTH               5
#define RTC_HOURMIN_HOUR_CNT(x)                  (((uint16_t)(((uint16_t)(x))<<RTC_HOURMIN_HOUR_CNT_SHIFT))&RTC_HOURMIN_HOUR_CNT_MASK)
/* SECONDS Bit Fields */
#define RTC_SECONDS_SEC_CNT_MASK                 0x3Fu
#define RTC_SECONDS_SEC_CNT_SHIFT                0
#define RTC_SECONDS_SEC_CNT_WIDTH                6
#define RTC_SECONDS_SEC_CNT(x)                   (((uint16_t)(((uint16_t)(x))<<RTC_SECONDS_SEC_CNT_SHIFT))&RTC_SECONDS_SEC_CNT_MASK)
/* ALM_YEARMON Bit Fields */
#define RTC_ALM_YEARMON_ALM_MON_MASK             0xFu
#define RTC_ALM_YEARMON_ALM_MON_SHIFT            0
#define RTC_ALM_YEARMON_ALM_MON_WIDTH            4
#define RTC_ALM_YEARMON_ALM_MON(x)               (((uint16_t)(((uint16_t)(x))<<RTC_ALM_YEARMON_ALM_MON_SHIFT))&RTC_ALM_YEARMON_ALM_MON_MASK)
#define RTC_ALM_YEARMON_ALM_YEAR_MASK            0xFF00u
#define RTC_ALM_YEARMON_ALM_YEAR_SHIFT           8
#define RTC_ALM_YEARMON_ALM_YEAR_WIDTH           8
#define RTC_ALM_YEARMON_ALM_YEAR(x)              (((uint16_t)(((uint16_t)(x))<<RTC_ALM_YEARMON_ALM_YEAR_SHIFT))&RTC_ALM_YEARMON_ALM_YEAR_MASK)
/* ALM_DAYS Bit Fields */
#define RTC_ALM_DAYS_ALM_DAY_MASK                0x1Fu
#define RTC_ALM_DAYS_ALM_DAY_SHIFT               0
#define RTC_ALM_DAYS_ALM_DAY_WIDTH               5
#define RTC_ALM_DAYS_ALM_DAY(x)                  (((uint16_t)(((uint16_t)(x))<<RTC_ALM_DAYS_ALM_DAY_SHIFT))&RTC_ALM_DAYS_ALM_DAY_MASK)
/* ALM_HOURMIN Bit Fields */
#define RTC_ALM_HOURMIN_ALM_MIN_MASK             0x3Fu
#define RTC_ALM_HOURMIN_ALM_MIN_SHIFT            0
#define RTC_ALM_HOURMIN_ALM_MIN_WIDTH            6
#define RTC_ALM_HOURMIN_ALM_MIN(x)               (((uint16_t)(((uint16_t)(x))<<RTC_ALM_HOURMIN_ALM_MIN_SHIFT))&RTC_ALM_HOURMIN_ALM_MIN_MASK)
#define RTC_ALM_HOURMIN_ALM_HOUR_MASK            0x1F00u
#define RTC_ALM_HOURMIN_ALM_HOUR_SHIFT           8
#define RTC_ALM_HOURMIN_ALM_HOUR_WIDTH           5
#define RTC_ALM_HOURMIN_ALM_HOUR(x)              (((uint16_t)(((uint16_t)(x))<<RTC_ALM_HOURMIN_ALM_HOUR_SHIFT))&RTC_ALM_HOURMIN_ALM_HOUR_MASK)
/* ALM_SECONDS Bit Fields */
#define RTC_ALM_SECONDS_ALM_SEC_MASK             0x3Fu
#define RTC_ALM_SECONDS_ALM_SEC_SHIFT            0
#define RTC_ALM_SECONDS_ALM_SEC_WIDTH            6
#define RTC_ALM_SECONDS_ALM_SEC(x)               (((uint16_t)(((uint16_t)(x))<<RTC_ALM_SECONDS_ALM_SEC_SHIFT))&RTC_ALM_SECONDS_ALM_SEC_MASK)
#define RTC_ALM_SECONDS_DEC_SEC_MASK             0x100u
#define RTC_ALM_SECONDS_DEC_SEC_SHIFT            8
#define RTC_ALM_SECONDS_DEC_SEC_WIDTH            1
#define RTC_ALM_SECONDS_DEC_SEC(x)               (((uint16_t)(((uint16_t)(x))<<RTC_ALM_SECONDS_DEC_SEC_SHIFT))&RTC_ALM_SECONDS_DEC_SEC_MASK)
#define RTC_ALM_SECONDS_INC_SEC_MASK             0x200u
#define RTC_ALM_SECONDS_INC_SEC_SHIFT            9
#define RTC_ALM_SECONDS_INC_SEC_WIDTH            1
#define RTC_ALM_SECONDS_INC_SEC(x)               (((uint16_t)(((uint16_t)(x))<<RTC_ALM_SECONDS_INC_SEC_SHIFT))&RTC_ALM_SECONDS_INC_SEC_MASK)
/* CTRL Bit Fields */
#define RTC_CTRL_FINEEN_MASK                     0x1u
#define RTC_CTRL_FINEEN_SHIFT                    0
#define RTC_CTRL_FINEEN_WIDTH                    1
#define RTC_CTRL_FINEEN(x)                       (((uint16_t)(((uint16_t)(x))<<RTC_CTRL_FINEEN_SHIFT))&RTC_CTRL_FINEEN_MASK)
#define RTC_CTRL_COMP_EN_MASK                    0x2u
#define RTC_CTRL_COMP_EN_SHIFT                   1
#define RTC_CTRL_COMP_EN_WIDTH                   1
#define RTC_CTRL_COMP_EN(x)                      (((uint16_t)(((uint16_t)(x))<<RTC_CTRL_COMP_EN_SHIFT))&RTC_CTRL_COMP_EN_MASK)
#define RTC_CTRL_ALM_MATCH_MASK                  0xCu
#define RTC_CTRL_ALM_MATCH_SHIFT                 2
#define RTC_CTRL_ALM_MATCH_WIDTH                 2
#define RTC_CTRL_ALM_MATCH(x)                    (((uint16_t)(((uint16_t)(x))<<RTC_CTRL_ALM_MATCH_SHIFT))&RTC_CTRL_ALM_MATCH_MASK)
#define RTC_CTRL_TIMER_STB_MASK_MASK             0x10u
#define RTC_CTRL_TIMER_STB_MASK_SHIFT            4
#define RTC_CTRL_TIMER_STB_MASK_WIDTH            1
#define RTC_CTRL_TIMER_STB_MASK(x)               (((uint16_t)(((uint16_t)(x))<<RTC_CTRL_TIMER_STB_MASK_SHIFT))&RTC_CTRL_TIMER_STB_MASK_MASK)
#define RTC_CTRL_DST_EN_MASK                     0x40u
#define RTC_CTRL_DST_EN_SHIFT                    6
#define RTC_CTRL_DST_EN_WIDTH                    1
#define RTC_CTRL_DST_EN(x)                       (((uint16_t)(((uint16_t)(x))<<RTC_CTRL_DST_EN_SHIFT))&RTC_CTRL_DST_EN_MASK)
#define RTC_CTRL_SWR_MASK                        0x100u
#define RTC_CTRL_SWR_SHIFT                       8
#define RTC_CTRL_SWR_WIDTH                       1
#define RTC_CTRL_SWR(x)                          (((uint16_t)(((uint16_t)(x))<<RTC_CTRL_SWR_SHIFT))&RTC_CTRL_SWR_MASK)
#define RTC_CTRL_CLKOUT_MASK                     0x6000u
#define RTC_CTRL_CLKOUT_SHIFT                    13
#define RTC_CTRL_CLKOUT_WIDTH                    2
#define RTC_CTRL_CLKOUT(x)                       (((uint16_t)(((uint16_t)(x))<<RTC_CTRL_CLKOUT_SHIFT))&RTC_CTRL_CLKOUT_MASK)
/* STATUS Bit Fields */
#define RTC_STATUS_INVAL_BIT_MASK                0x1u
#define RTC_STATUS_INVAL_BIT_SHIFT               0
#define RTC_STATUS_INVAL_BIT_WIDTH               1
#define RTC_STATUS_INVAL_BIT(x)                  (((uint16_t)(((uint16_t)(x))<<RTC_STATUS_INVAL_BIT_SHIFT))&RTC_STATUS_INVAL_BIT_MASK)
#define RTC_STATUS_WRITE_PROT_EN_MASK            0x2u
#define RTC_STATUS_WRITE_PROT_EN_SHIFT           1
#define RTC_STATUS_WRITE_PROT_EN_WIDTH           1
#define RTC_STATUS_WRITE_PROT_EN(x)              (((uint16_t)(((uint16_t)(x))<<RTC_STATUS_WRITE_PROT_EN_SHIFT))&RTC_STATUS_WRITE_PROT_EN_MASK)
#define RTC_STATUS_CPU_LOW_VOLT_MASK             0x4u
#define RTC_STATUS_CPU_LOW_VOLT_SHIFT            2
#define RTC_STATUS_CPU_LOW_VOLT_WIDTH            1
#define RTC_STATUS_CPU_LOW_VOLT(x)               (((uint16_t)(((uint16_t)(x))<<RTC_STATUS_CPU_LOW_VOLT_SHIFT))&RTC_STATUS_CPU_LOW_VOLT_MASK)
#define RTC_STATUS_RST_SRC_MASK                  0x8u
#define RTC_STATUS_RST_SRC_SHIFT                 3
#define RTC_STATUS_RST_SRC_WIDTH                 1
#define RTC_STATUS_RST_SRC(x)                    (((uint16_t)(((uint16_t)(x))<<RTC_STATUS_RST_SRC_SHIFT))&RTC_STATUS_RST_SRC_MASK)
#define RTC_STATUS_CMP_INT_MASK                  0x20u
#define RTC_STATUS_CMP_INT_SHIFT                 5
#define RTC_STATUS_CMP_INT_WIDTH                 1
#define RTC_STATUS_CMP_INT(x)                    (((uint16_t)(((uint16_t)(x))<<RTC_STATUS_CMP_INT_SHIFT))&RTC_STATUS_CMP_INT_MASK)
#define RTC_STATUS_WE_MASK                       0xC0u
#define RTC_STATUS_WE_SHIFT                      6
#define RTC_STATUS_WE_WIDTH                      2
#define RTC_STATUS_WE(x)                         (((uint16_t)(((uint16_t)(x))<<RTC_STATUS_WE_SHIFT))&RTC_STATUS_WE_MASK)
#define RTC_STATUS_BUS_ERR_MASK                  0x100u
#define RTC_STATUS_BUS_ERR_SHIFT                 8
#define RTC_STATUS_BUS_ERR_WIDTH                 1
#define RTC_STATUS_BUS_ERR(x)                    (((uint16_t)(((uint16_t)(x))<<RTC_STATUS_BUS_ERR_SHIFT))&RTC_STATUS_BUS_ERR_MASK)
#define RTC_STATUS_CMP_DONE_MASK                 0x800u
#define RTC_STATUS_CMP_DONE_SHIFT                11
#define RTC_STATUS_CMP_DONE_WIDTH                1
#define RTC_STATUS_CMP_DONE(x)                   (((uint16_t)(((uint16_t)(x))<<RTC_STATUS_CMP_DONE_SHIFT))&RTC_STATUS_CMP_DONE_MASK)
/* ISR Bit Fields */
#define RTC_ISR_TAMPER_IS_MASK                   0x1u
#define RTC_ISR_TAMPER_IS_SHIFT                  0
#define RTC_ISR_TAMPER_IS_WIDTH                  1
#define RTC_ISR_TAMPER_IS(x)                     (((uint16_t)(((uint16_t)(x))<<RTC_ISR_TAMPER_IS_SHIFT))&RTC_ISR_TAMPER_IS_MASK)
#define RTC_ISR_ALM_IS_MASK                      0x4u
#define RTC_ISR_ALM_IS_SHIFT                     2
#define RTC_ISR_ALM_IS_WIDTH                     1
#define RTC_ISR_ALM_IS(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_ISR_ALM_IS_SHIFT))&RTC_ISR_ALM_IS_MASK)
#define RTC_ISR_DAY_IS_MASK                      0x8u
#define RTC_ISR_DAY_IS_SHIFT                     3
#define RTC_ISR_DAY_IS_WIDTH                     1
#define RTC_ISR_DAY_IS(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_ISR_DAY_IS_SHIFT))&RTC_ISR_DAY_IS_MASK)
#define RTC_ISR_HOUR_IS_MASK                     0x10u
#define RTC_ISR_HOUR_IS_SHIFT                    4
#define RTC_ISR_HOUR_IS_WIDTH                    1
#define RTC_ISR_HOUR_IS(x)                       (((uint16_t)(((uint16_t)(x))<<RTC_ISR_HOUR_IS_SHIFT))&RTC_ISR_HOUR_IS_MASK)
#define RTC_ISR_MIN_IS_MASK                      0x20u
#define RTC_ISR_MIN_IS_SHIFT                     5
#define RTC_ISR_MIN_IS_WIDTH                     1
#define RTC_ISR_MIN_IS(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_ISR_MIN_IS_SHIFT))&RTC_ISR_MIN_IS_MASK)
#define RTC_ISR_IS_1HZ_MASK                      0x40u
#define RTC_ISR_IS_1HZ_SHIFT                     6
#define RTC_ISR_IS_1HZ_WIDTH                     1
#define RTC_ISR_IS_1HZ(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_ISR_IS_1HZ_SHIFT))&RTC_ISR_IS_1HZ_MASK)
#define RTC_ISR_IS_2HZ_MASK                      0x80u
#define RTC_ISR_IS_2HZ_SHIFT                     7
#define RTC_ISR_IS_2HZ_WIDTH                     1
#define RTC_ISR_IS_2HZ(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_ISR_IS_2HZ_SHIFT))&RTC_ISR_IS_2HZ_MASK)
#define RTC_ISR_IS_4HZ_MASK                      0x100u
#define RTC_ISR_IS_4HZ_SHIFT                     8
#define RTC_ISR_IS_4HZ_WIDTH                     1
#define RTC_ISR_IS_4HZ(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_ISR_IS_4HZ_SHIFT))&RTC_ISR_IS_4HZ_MASK)
#define RTC_ISR_IS_8HZ_MASK                      0x200u
#define RTC_ISR_IS_8HZ_SHIFT                     9
#define RTC_ISR_IS_8HZ_WIDTH                     1
#define RTC_ISR_IS_8HZ(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_ISR_IS_8HZ_SHIFT))&RTC_ISR_IS_8HZ_MASK)
#define RTC_ISR_IS_16HZ_MASK                     0x400u
#define RTC_ISR_IS_16HZ_SHIFT                    10
#define RTC_ISR_IS_16HZ_WIDTH                    1
#define RTC_ISR_IS_16HZ(x)                       (((uint16_t)(((uint16_t)(x))<<RTC_ISR_IS_16HZ_SHIFT))&RTC_ISR_IS_16HZ_MASK)
#define RTC_ISR_IS_32HZ_MASK                     0x800u
#define RTC_ISR_IS_32HZ_SHIFT                    11
#define RTC_ISR_IS_32HZ_WIDTH                    1
#define RTC_ISR_IS_32HZ(x)                       (((uint16_t)(((uint16_t)(x))<<RTC_ISR_IS_32HZ_SHIFT))&RTC_ISR_IS_32HZ_MASK)
#define RTC_ISR_IS_64HZ_MASK                     0x1000u
#define RTC_ISR_IS_64HZ_SHIFT                    12
#define RTC_ISR_IS_64HZ_WIDTH                    1
#define RTC_ISR_IS_64HZ(x)                       (((uint16_t)(((uint16_t)(x))<<RTC_ISR_IS_64HZ_SHIFT))&RTC_ISR_IS_64HZ_MASK)
#define RTC_ISR_IS_128HZ_MASK                    0x2000u
#define RTC_ISR_IS_128HZ_SHIFT                   13
#define RTC_ISR_IS_128HZ_WIDTH                   1
#define RTC_ISR_IS_128HZ(x)                      (((uint16_t)(((uint16_t)(x))<<RTC_ISR_IS_128HZ_SHIFT))&RTC_ISR_IS_128HZ_MASK)
#define RTC_ISR_IS_256HZ_MASK                    0x4000u
#define RTC_ISR_IS_256HZ_SHIFT                   14
#define RTC_ISR_IS_256HZ_WIDTH                   1
#define RTC_ISR_IS_256HZ(x)                      (((uint16_t)(((uint16_t)(x))<<RTC_ISR_IS_256HZ_SHIFT))&RTC_ISR_IS_256HZ_MASK)
#define RTC_ISR_IS_512HZ_MASK                    0x8000u
#define RTC_ISR_IS_512HZ_SHIFT                   15
#define RTC_ISR_IS_512HZ_WIDTH                   1
#define RTC_ISR_IS_512HZ(x)                      (((uint16_t)(((uint16_t)(x))<<RTC_ISR_IS_512HZ_SHIFT))&RTC_ISR_IS_512HZ_MASK)
/* IER Bit Fields */
#define RTC_IER_TAMPER_IE_MASK                   0x1u
#define RTC_IER_TAMPER_IE_SHIFT                  0
#define RTC_IER_TAMPER_IE_WIDTH                  1
#define RTC_IER_TAMPER_IE(x)                     (((uint16_t)(((uint16_t)(x))<<RTC_IER_TAMPER_IE_SHIFT))&RTC_IER_TAMPER_IE_MASK)
#define RTC_IER_ALM_IE_MASK                      0x4u
#define RTC_IER_ALM_IE_SHIFT                     2
#define RTC_IER_ALM_IE_WIDTH                     1
#define RTC_IER_ALM_IE(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_IER_ALM_IE_SHIFT))&RTC_IER_ALM_IE_MASK)
#define RTC_IER_DAY_IE_MASK                      0x8u
#define RTC_IER_DAY_IE_SHIFT                     3
#define RTC_IER_DAY_IE_WIDTH                     1
#define RTC_IER_DAY_IE(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_IER_DAY_IE_SHIFT))&RTC_IER_DAY_IE_MASK)
#define RTC_IER_HOUR_IE_MASK                     0x10u
#define RTC_IER_HOUR_IE_SHIFT                    4
#define RTC_IER_HOUR_IE_WIDTH                    1
#define RTC_IER_HOUR_IE(x)                       (((uint16_t)(((uint16_t)(x))<<RTC_IER_HOUR_IE_SHIFT))&RTC_IER_HOUR_IE_MASK)
#define RTC_IER_MIN_IE_MASK                      0x20u
#define RTC_IER_MIN_IE_SHIFT                     5
#define RTC_IER_MIN_IE_WIDTH                     1
#define RTC_IER_MIN_IE(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_IER_MIN_IE_SHIFT))&RTC_IER_MIN_IE_MASK)
#define RTC_IER_IE_1HZ_MASK                      0x40u
#define RTC_IER_IE_1HZ_SHIFT                     6
#define RTC_IER_IE_1HZ_WIDTH                     1
#define RTC_IER_IE_1HZ(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_IER_IE_1HZ_SHIFT))&RTC_IER_IE_1HZ_MASK)
#define RTC_IER_IE_2HZ_MASK                      0x80u
#define RTC_IER_IE_2HZ_SHIFT                     7
#define RTC_IER_IE_2HZ_WIDTH                     1
#define RTC_IER_IE_2HZ(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_IER_IE_2HZ_SHIFT))&RTC_IER_IE_2HZ_MASK)
#define RTC_IER_IE_4HZ_MASK                      0x100u
#define RTC_IER_IE_4HZ_SHIFT                     8
#define RTC_IER_IE_4HZ_WIDTH                     1
#define RTC_IER_IE_4HZ(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_IER_IE_4HZ_SHIFT))&RTC_IER_IE_4HZ_MASK)
#define RTC_IER_IE_8HZ_MASK                      0x200u
#define RTC_IER_IE_8HZ_SHIFT                     9
#define RTC_IER_IE_8HZ_WIDTH                     1
#define RTC_IER_IE_8HZ(x)                        (((uint16_t)(((uint16_t)(x))<<RTC_IER_IE_8HZ_SHIFT))&RTC_IER_IE_8HZ_MASK)
#define RTC_IER_IE_16HZ_MASK                     0x400u
#define RTC_IER_IE_16HZ_SHIFT                    10
#define RTC_IER_IE_16HZ_WIDTH                    1
#define RTC_IER_IE_16HZ(x)                       (((uint16_t)(((uint16_t)(x))<<RTC_IER_IE_16HZ_SHIFT))&RTC_IER_IE_16HZ_MASK)
#define RTC_IER_IE_32HZ_MASK                     0x800u
#define RTC_IER_IE_32HZ_SHIFT                    11
#define RTC_IER_IE_32HZ_WIDTH                    1
#define RTC_IER_IE_32HZ(x)                       (((uint16_t)(((uint16_t)(x))<<RTC_IER_IE_32HZ_SHIFT))&RTC_IER_IE_32HZ_MASK)
#define RTC_IER_IE_64HZ_MASK                     0x1000u
#define RTC_IER_IE_64HZ_SHIFT                    12
#define RTC_IER_IE_64HZ_WIDTH                    1
#define RTC_IER_IE_64HZ(x)                       (((uint16_t)(((uint16_t)(x))<<RTC_IER_IE_64HZ_SHIFT))&RTC_IER_IE_64HZ_MASK)
#define RTC_IER_IE_128HZ_MASK                    0x2000u
#define RTC_IER_IE_128HZ_SHIFT                   13
#define RTC_IER_IE_128HZ_WIDTH                   1
#define RTC_IER_IE_128HZ(x)                      (((uint16_t)(((uint16_t)(x))<<RTC_IER_IE_128HZ_SHIFT))&RTC_IER_IE_128HZ_MASK)
#define RTC_IER_IE_256HZ_MASK                    0x4000u
#define RTC_IER_IE_256HZ_SHIFT                   14
#define RTC_IER_IE_256HZ_WIDTH                   1
#define RTC_IER_IE_256HZ(x)                      (((uint16_t)(((uint16_t)(x))<<RTC_IER_IE_256HZ_SHIFT))&RTC_IER_IE_256HZ_MASK)
#define RTC_IER_IE_512HZ_MASK                    0x8000u
#define RTC_IER_IE_512HZ_SHIFT                   15
#define RTC_IER_IE_512HZ_WIDTH                   1
#define RTC_IER_IE_512HZ(x)                      (((uint16_t)(((uint16_t)(x))<<RTC_IER_IE_512HZ_SHIFT))&RTC_IER_IE_512HZ_MASK)
/* GP_DATA_REG Bit Fields */
#define RTC_GP_DATA_REG_GP_DATA_REG_MASK         0xFFFFu
#define RTC_GP_DATA_REG_GP_DATA_REG_SHIFT        0
#define RTC_GP_DATA_REG_GP_DATA_REG_WIDTH        16
#define RTC_GP_DATA_REG_GP_DATA_REG(x)           (((uint16_t)(((uint16_t)(x))<<RTC_GP_DATA_REG_GP_DATA_REG_SHIFT))&RTC_GP_DATA_REG_GP_DATA_REG_MASK)
/* DST_HOUR Bit Fields */
#define RTC_DST_HOUR_DST_END_HOUR_MASK           0x1Fu
#define RTC_DST_HOUR_DST_END_HOUR_SHIFT          0
#define RTC_DST_HOUR_DST_END_HOUR_WIDTH          5
#define RTC_DST_HOUR_DST_END_HOUR(x)             (((uint16_t)(((uint16_t)(x))<<RTC_DST_HOUR_DST_END_HOUR_SHIFT))&RTC_DST_HOUR_DST_END_HOUR_MASK)
#define RTC_DST_HOUR_DST_START_HOUR_MASK         0x1F00u
#define RTC_DST_HOUR_DST_START_HOUR_SHIFT        8
#define RTC_DST_HOUR_DST_START_HOUR_WIDTH        5
#define RTC_DST_HOUR_DST_START_HOUR(x)           (((uint16_t)(((uint16_t)(x))<<RTC_DST_HOUR_DST_START_HOUR_SHIFT))&RTC_DST_HOUR_DST_START_HOUR_MASK)
/* DST_MONTH Bit Fields */
#define RTC_DST_MONTH_DST_END_MONTH_MASK         0xFu
#define RTC_DST_MONTH_DST_END_MONTH_SHIFT        0
#define RTC_DST_MONTH_DST_END_MONTH_WIDTH        4
#define RTC_DST_MONTH_DST_END_MONTH(x)           (((uint16_t)(((uint16_t)(x))<<RTC_DST_MONTH_DST_END_MONTH_SHIFT))&RTC_DST_MONTH_DST_END_MONTH_MASK)
#define RTC_DST_MONTH_DST_START_MONTH_MASK       0xF00u
#define RTC_DST_MONTH_DST_START_MONTH_SHIFT      8
#define RTC_DST_MONTH_DST_START_MONTH_WIDTH      4
#define RTC_DST_MONTH_DST_START_MONTH(x)         (((uint16_t)(((uint16_t)(x))<<RTC_DST_MONTH_DST_START_MONTH_SHIFT))&RTC_DST_MONTH_DST_START_MONTH_MASK)
/* DST_DAY Bit Fields */
#define RTC_DST_DAY_DST_END_DAY_MASK             0x1Fu
#define RTC_DST_DAY_DST_END_DAY_SHIFT            0
#define RTC_DST_DAY_DST_END_DAY_WIDTH            5
#define RTC_DST_DAY_DST_END_DAY(x)               (((uint16_t)(((uint16_t)(x))<<RTC_DST_DAY_DST_END_DAY_SHIFT))&RTC_DST_DAY_DST_END_DAY_MASK)
#define RTC_DST_DAY_DST_START_DAY_MASK           0x1F00u
#define RTC_DST_DAY_DST_START_DAY_SHIFT          8
#define RTC_DST_DAY_DST_START_DAY_WIDTH          5
#define RTC_DST_DAY_DST_START_DAY(x)             (((uint16_t)(((uint16_t)(x))<<RTC_DST_DAY_DST_START_DAY_SHIFT))&RTC_DST_DAY_DST_START_DAY_MASK)
/* COMPEN Bit Fields */
#define RTC_COMPEN_COMPEN_VAL_MASK               0xFFFFu
#define RTC_COMPEN_COMPEN_VAL_SHIFT              0
#define RTC_COMPEN_COMPEN_VAL_WIDTH              16
#define RTC_COMPEN_COMPEN_VAL(x)                 (((uint16_t)(((uint16_t)(x))<<RTC_COMPEN_COMPEN_VAL_SHIFT))&RTC_COMPEN_COMPEN_VAL_MASK)
/* TAMPER_SCR Bit Fields */
#define RTC_TAMPER_SCR_TMPR_EN_MASK              0xFu
#define RTC_TAMPER_SCR_TMPR_EN_SHIFT             0
#define RTC_TAMPER_SCR_TMPR_EN_WIDTH             4
#define RTC_TAMPER_SCR_TMPR_EN(x)                (((uint16_t)(((uint16_t)(x))<<RTC_TAMPER_SCR_TMPR_EN_SHIFT))&RTC_TAMPER_SCR_TMPR_EN_MASK)
#define RTC_TAMPER_SCR_TMPR_STS_MASK             0xF00u
#define RTC_TAMPER_SCR_TMPR_STS_SHIFT            8
#define RTC_TAMPER_SCR_TMPR_STS_WIDTH            4
#define RTC_TAMPER_SCR_TMPR_STS(x)               (((uint16_t)(((uint16_t)(x))<<RTC_TAMPER_SCR_TMPR_STS_SHIFT))&RTC_TAMPER_SCR_TMPR_STS_MASK)
/* FILTER01_CFG Bit Fields */
#define RTC_FILTER01_CFG_FIL_DUR1_MASK           0xFu
#define RTC_FILTER01_CFG_FIL_DUR1_SHIFT          0
#define RTC_FILTER01_CFG_FIL_DUR1_WIDTH          4
#define RTC_FILTER01_CFG_FIL_DUR1(x)             (((uint16_t)(((uint16_t)(x))<<RTC_FILTER01_CFG_FIL_DUR1_SHIFT))&RTC_FILTER01_CFG_FIL_DUR1_MASK)
#define RTC_FILTER01_CFG_CLK_SEL1_MASK           0x70u
#define RTC_FILTER01_CFG_CLK_SEL1_SHIFT          4
#define RTC_FILTER01_CFG_CLK_SEL1_WIDTH          3
#define RTC_FILTER01_CFG_CLK_SEL1(x)             (((uint16_t)(((uint16_t)(x))<<RTC_FILTER01_CFG_CLK_SEL1_SHIFT))&RTC_FILTER01_CFG_CLK_SEL1_MASK)
#define RTC_FILTER01_CFG_POL1_MASK               0x80u
#define RTC_FILTER01_CFG_POL1_SHIFT              7
#define RTC_FILTER01_CFG_POL1_WIDTH              1
#define RTC_FILTER01_CFG_POL1(x)                 (((uint16_t)(((uint16_t)(x))<<RTC_FILTER01_CFG_POL1_SHIFT))&RTC_FILTER01_CFG_POL1_MASK)
#define RTC_FILTER01_CFG_FIL_DUR0_MASK           0xF00u
#define RTC_FILTER01_CFG_FIL_DUR0_SHIFT          8
#define RTC_FILTER01_CFG_FIL_DUR0_WIDTH          4
#define RTC_FILTER01_CFG_FIL_DUR0(x)             (((uint16_t)(((uint16_t)(x))<<RTC_FILTER01_CFG_FIL_DUR0_SHIFT))&RTC_FILTER01_CFG_FIL_DUR0_MASK)
#define RTC_FILTER01_CFG_CLK_SEL0_MASK           0x7000u
#define RTC_FILTER01_CFG_CLK_SEL0_SHIFT          12
#define RTC_FILTER01_CFG_CLK_SEL0_WIDTH          3
#define RTC_FILTER01_CFG_CLK_SEL0(x)             (((uint16_t)(((uint16_t)(x))<<RTC_FILTER01_CFG_CLK_SEL0_SHIFT))&RTC_FILTER01_CFG_CLK_SEL0_MASK)
#define RTC_FILTER01_CFG_POL0_MASK               0x8000u
#define RTC_FILTER01_CFG_POL0_SHIFT              15
#define RTC_FILTER01_CFG_POL0_WIDTH              1
#define RTC_FILTER01_CFG_POL0(x)                 (((uint16_t)(((uint16_t)(x))<<RTC_FILTER01_CFG_POL0_SHIFT))&RTC_FILTER01_CFG_POL0_MASK)
/* FILTER2_CFG Bit Fields */
#define RTC_FILTER2_CFG_FIL_DUR2_MASK            0xF00u
#define RTC_FILTER2_CFG_FIL_DUR2_SHIFT           8
#define RTC_FILTER2_CFG_FIL_DUR2_WIDTH           4
#define RTC_FILTER2_CFG_FIL_DUR2(x)              (((uint16_t)(((uint16_t)(x))<<RTC_FILTER2_CFG_FIL_DUR2_SHIFT))&RTC_FILTER2_CFG_FIL_DUR2_MASK)
#define RTC_FILTER2_CFG_CLK_SEL2_MASK            0x7000u
#define RTC_FILTER2_CFG_CLK_SEL2_SHIFT           12
#define RTC_FILTER2_CFG_CLK_SEL2_WIDTH           3
#define RTC_FILTER2_CFG_CLK_SEL2(x)              (((uint16_t)(((uint16_t)(x))<<RTC_FILTER2_CFG_CLK_SEL2_SHIFT))&RTC_FILTER2_CFG_CLK_SEL2_MASK)
#define RTC_FILTER2_CFG_POL2_MASK                0x8000u
#define RTC_FILTER2_CFG_POL2_SHIFT               15
#define RTC_FILTER2_CFG_POL2_WIDTH               1
#define RTC_FILTER2_CFG_POL2(x)                  (((uint16_t)(((uint16_t)(x))<<RTC_FILTER2_CFG_POL2_SHIFT))&RTC_FILTER2_CFG_POL2_MASK)
/* CTRL2 Bit Fields */
#define RTC_CTRL2_TAMP_CFG_OVER_MASK             0x1u
#define RTC_CTRL2_TAMP_CFG_OVER_SHIFT            0
#define RTC_CTRL2_TAMP_CFG_OVER_WIDTH            1
#define RTC_CTRL2_TAMP_CFG_OVER(x)               (((uint16_t)(((uint16_t)(x))<<RTC_CTRL2_TAMP_CFG_OVER_SHIFT))&RTC_CTRL2_TAMP_CFG_OVER_MASK)
#define RTC_CTRL2_WAKEUP_STATUS_MASK             0x60u
#define RTC_CTRL2_WAKEUP_STATUS_SHIFT            5
#define RTC_CTRL2_WAKEUP_STATUS_WIDTH            2
#define RTC_CTRL2_WAKEUP_STATUS(x)               (((uint16_t)(((uint16_t)(x))<<RTC_CTRL2_WAKEUP_STATUS_SHIFT))&RTC_CTRL2_WAKEUP_STATUS_MASK)
#define RTC_CTRL2_WAKEUP_MODE_MASK               0x80u
#define RTC_CTRL2_WAKEUP_MODE_SHIFT              7
#define RTC_CTRL2_WAKEUP_MODE_WIDTH              1
#define RTC_CTRL2_WAKEUP_MODE(x)                 (((uint16_t)(((uint16_t)(x))<<RTC_CTRL2_WAKEUP_MODE_SHIFT))&RTC_CTRL2_WAKEUP_MODE_MASK)

/*!
 * @}
 */ /* end of group RTC_Register_Masks */


/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base address */
#define RTC_BASE                                 (0x40050000u)
/** Peripheral RTC base pointer */
#define RTC                                      ((RTC_Type *)RTC_BASE)
#define RTC_BASE_PTR                             (RTC)
/** Array initializer of RTC peripheral base addresses */
#define RTC_BASE_ADDRS                           { RTC_BASE }
/** Array initializer of RTC peripheral base pointers */
#define RTC_BASE_PTRS                            { RTC }
/** Interrupt vectors for the RTC peripheral type */
#define RTC_IRQS                                 { RTC_IRQn }

/* ----------------------------------------------------------------------------
   -- RTC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Accessor_Macros RTC - Register accessor macros
 * @{
 */


/* RTC - Register instance definitions */
/* RTC */
#define RTC_YEARMON                              RTC_YEARMON_REG(RTC)
#define RTC_DAYS                                 RTC_DAYS_REG(RTC)
#define RTC_HOURMIN                              RTC_HOURMIN_REG(RTC)
#define RTC_SECONDS                              RTC_SECONDS_REG(RTC)
#define RTC_ALM_YEARMON                          RTC_ALM_YEARMON_REG(RTC)
#define RTC_ALM_DAYS                             RTC_ALM_DAYS_REG(RTC)
#define RTC_ALM_HOURMIN                          RTC_ALM_HOURMIN_REG(RTC)
#define RTC_ALM_SECONDS                          RTC_ALM_SECONDS_REG(RTC)
#define RTC_CTRL                                 RTC_CTRL_REG(RTC)
#define RTC_STATUS                               RTC_STATUS_REG(RTC)
#define RTC_ISR                                  RTC_ISR_REG(RTC)
#define RTC_IER                                  RTC_IER_REG(RTC)
#define RTC_GP_DATA_REG                          RTC_GP_DATA_REG_REG(RTC)
#define RTC_DST_HOUR                             RTC_DST_HOUR_REG(RTC)
#define RTC_DST_MONTH                            RTC_DST_MONTH_REG(RTC)
#define RTC_DST_DAY                              RTC_DST_DAY_REG(RTC)
#define RTC_COMPEN                               RTC_COMPEN_REG(RTC)
#define RTC_TAMPER_SCR                           RTC_TAMPER_SCR_REG(RTC)
#define RTC_FILTER01_CFG                         RTC_FILTER01_CFG_REG(RTC)
#define RTC_FILTER2_CFG                          RTC_FILTER2_CFG_REG(RTC)
#define RTC_CTRL2                                RTC_CTRL2_REG(RTC)

/*!
 * @}
 */ /* end of group RTC_Register_Accessor_Macros */


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
  __IO uint32_t SOPT1_CFG;                         /**< SOPT1 Configuration Register, offset: 0x4 */
       uint8_t RESERVED_0[4092];
  __IO uint32_t CTRL_REG;                          /**< System Control Register, offset: 0x1004 */
       uint8_t RESERVED_1[28];
  __I  uint32_t SDID;                              /**< System Device Identification Register, offset: 0x1024 */
       uint8_t RESERVED_2[12];
  __IO uint32_t SCGC4;                             /**< System Clock Gating Control Register 4, offset: 0x1034 */
  __IO uint32_t SCGC5;                             /**< System Clock Gating Control Register 5, offset: 0x1038 */
  __IO uint32_t SCGC6;                             /**< System Clock Gating Control Register 6, offset: 0x103C */
  __IO uint32_t SCGC7;                             /**< System Clock Gating Control Register 7, offset: 0x1040 */
  __IO uint32_t CLKDIV1;                           /**< System Clock Divider Register 1, offset: 0x1044 */
       uint8_t RESERVED_3[4];
  __IO uint32_t FCFG1;                             /**< Flash Configuration Register 1, offset: 0x104C */
  __I  uint32_t FCFG2;                             /**< Flash Configuration Register 2, offset: 0x1050 */
  __I  uint32_t UIDH;                              /**< Unique Identification Register High, offset: 0x1054 */
  __I  uint32_t UIDMH;                             /**< Unique Identification Register Mid-High, offset: 0x1058 */
  __I  uint32_t UIDML;                             /**< Unique Identification Register Mid-Low, offset: 0x105C */
  __I  uint32_t UIDL;                              /**< Unique Identification Register Low, offset: 0x1060 */
       uint8_t RESERVED_4[8];
  __IO uint32_t MISC_CTL;                          /**< Miscellaneous Control Register, offset: 0x106C */
       uint8_t RESERVED_5[88];
  __I  uint32_t ADC_COMP0;                         /**< ADC Compensation Register 0, offset: 0x10C8 */
  __I  uint32_t ADC_COMP1;                         /**< ADC Compensation Register 1, offset: 0x10CC */
} SIM_Type, *SIM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SIM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Accessor_Macros SIM - Register accessor macros
 * @{
 */


/* SIM - Register accessors */
#define SIM_SOPT1_REG(base)                      ((base)->SOPT1)
#define SIM_SOPT1_CFG_REG(base)                  ((base)->SOPT1_CFG)
#define SIM_CTRL_REG_REG(base)                   ((base)->CTRL_REG)
#define SIM_SDID_REG(base)                       ((base)->SDID)
#define SIM_SCGC4_REG(base)                      ((base)->SCGC4)
#define SIM_SCGC5_REG(base)                      ((base)->SCGC5)
#define SIM_SCGC6_REG(base)                      ((base)->SCGC6)
#define SIM_SCGC7_REG(base)                      ((base)->SCGC7)
#define SIM_CLKDIV1_REG(base)                    ((base)->CLKDIV1)
#define SIM_FCFG1_REG(base)                      ((base)->FCFG1)
#define SIM_FCFG2_REG(base)                      ((base)->FCFG2)
#define SIM_UIDH_REG(base)                       ((base)->UIDH)
#define SIM_UIDMH_REG(base)                      ((base)->UIDMH)
#define SIM_UIDML_REG(base)                      ((base)->UIDML)
#define SIM_UIDL_REG(base)                       ((base)->UIDL)
#define SIM_MISC_CTL_REG(base)                   ((base)->MISC_CTL)
#define SIM_ADC_COMP0_REG(base)                  ((base)->ADC_COMP0)
#define SIM_ADC_COMP1_REG(base)                  ((base)->ADC_COMP1)

/*!
 * @}
 */ /* end of group SIM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SIM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Masks SIM Register Masks
 * @{
 */

/* SOPT1 Bit Fields */
#define SIM_SOPT1_SRAMSIZE_MASK                  0xF000u
#define SIM_SOPT1_SRAMSIZE_SHIFT                 12
#define SIM_SOPT1_SRAMSIZE_WIDTH                 4
#define SIM_SOPT1_SRAMSIZE(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_SOPT1_SRAMSIZE_SHIFT))&SIM_SOPT1_SRAMSIZE_MASK)
#define SIM_SOPT1_OSC32KSEL_MASK                 0xC0000u
#define SIM_SOPT1_OSC32KSEL_SHIFT                18
#define SIM_SOPT1_OSC32KSEL_WIDTH                2
#define SIM_SOPT1_OSC32KSEL(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_SOPT1_OSC32KSEL_SHIFT))&SIM_SOPT1_OSC32KSEL_MASK)
/* SOPT1_CFG Bit Fields */
#define SIM_SOPT1_CFG_LPTMR0SEL_MASK             0x3u
#define SIM_SOPT1_CFG_LPTMR0SEL_SHIFT            0
#define SIM_SOPT1_CFG_LPTMR0SEL_WIDTH            2
#define SIM_SOPT1_CFG_LPTMR0SEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_SOPT1_CFG_LPTMR0SEL_SHIFT))&SIM_SOPT1_CFG_LPTMR0SEL_MASK)
#define SIM_SOPT1_CFG_LPTMR1SEL_MASK             0xCu
#define SIM_SOPT1_CFG_LPTMR1SEL_SHIFT            2
#define SIM_SOPT1_CFG_LPTMR1SEL_WIDTH            2
#define SIM_SOPT1_CFG_LPTMR1SEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_SOPT1_CFG_LPTMR1SEL_SHIFT))&SIM_SOPT1_CFG_LPTMR1SEL_MASK)
#define SIM_SOPT1_CFG_LPTMR2SEL_MASK             0x30u
#define SIM_SOPT1_CFG_LPTMR2SEL_SHIFT            4
#define SIM_SOPT1_CFG_LPTMR2SEL_WIDTH            2
#define SIM_SOPT1_CFG_LPTMR2SEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_SOPT1_CFG_LPTMR2SEL_SHIFT))&SIM_SOPT1_CFG_LPTMR2SEL_MASK)
#define SIM_SOPT1_CFG_LPTMR3SEL_MASK             0xC0u
#define SIM_SOPT1_CFG_LPTMR3SEL_SHIFT            6
#define SIM_SOPT1_CFG_LPTMR3SEL_WIDTH            2
#define SIM_SOPT1_CFG_LPTMR3SEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_SOPT1_CFG_LPTMR3SEL_SHIFT))&SIM_SOPT1_CFG_LPTMR3SEL_MASK)
#define SIM_SOPT1_CFG_RAMSBDIS_MASK              0x100u
#define SIM_SOPT1_CFG_RAMSBDIS_SHIFT             8
#define SIM_SOPT1_CFG_RAMSBDIS_WIDTH             1
#define SIM_SOPT1_CFG_RAMSBDIS(x)                (((uint32_t)(((uint32_t)(x))<<SIM_SOPT1_CFG_RAMSBDIS_SHIFT))&SIM_SOPT1_CFG_RAMSBDIS_MASK)
#define SIM_SOPT1_CFG_RAMBPEN_MASK               0x200u
#define SIM_SOPT1_CFG_RAMBPEN_SHIFT              9
#define SIM_SOPT1_CFG_RAMBPEN_WIDTH              1
#define SIM_SOPT1_CFG_RAMBPEN(x)                 (((uint32_t)(((uint32_t)(x))<<SIM_SOPT1_CFG_RAMBPEN_SHIFT))&SIM_SOPT1_CFG_RAMBPEN_MASK)
/* CTRL_REG Bit Fields */
#define SIM_CTRL_REG_NMIDIS_MASK                 0x1u
#define SIM_CTRL_REG_NMIDIS_SHIFT                0
#define SIM_CTRL_REG_NMIDIS_WIDTH                1
#define SIM_CTRL_REG_NMIDIS(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_NMIDIS_SHIFT))&SIM_CTRL_REG_NMIDIS_MASK)
#define SIM_CTRL_REG_PLLVLPEN_MASK               0x2u
#define SIM_CTRL_REG_PLLVLPEN_SHIFT              1
#define SIM_CTRL_REG_PLLVLPEN_WIDTH              1
#define SIM_CTRL_REG_PLLVLPEN(x)                 (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_PLLVLPEN_SHIFT))&SIM_CTRL_REG_PLLVLPEN_MASK)
#define SIM_CTRL_REG_ADCTRGSEL_MASK              0x18u
#define SIM_CTRL_REG_ADCTRGSEL_SHIFT             3
#define SIM_CTRL_REG_ADCTRGSEL_WIDTH             2
#define SIM_CTRL_REG_ADCTRGSEL(x)                (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_ADCTRGSEL_SHIFT))&SIM_CTRL_REG_ADCTRGSEL_MASK)
#define SIM_CTRL_REG_CLKOUT_MASK                 0xE0u
#define SIM_CTRL_REG_CLKOUT_SHIFT                5
#define SIM_CTRL_REG_CLKOUT_WIDTH                3
#define SIM_CTRL_REG_CLKOUT(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_CLKOUT_SHIFT))&SIM_CTRL_REG_CLKOUT_MASK)
#define SIM_CTRL_REG_SPI0_INV0_MASK              0x100u
#define SIM_CTRL_REG_SPI0_INV0_SHIFT             8
#define SIM_CTRL_REG_SPI0_INV0_WIDTH             1
#define SIM_CTRL_REG_SPI0_INV0(x)                (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_SPI0_INV0_SHIFT))&SIM_CTRL_REG_SPI0_INV0_MASK)
#define SIM_CTRL_REG_SPI0_INV1_MASK              0x200u
#define SIM_CTRL_REG_SPI0_INV1_SHIFT             9
#define SIM_CTRL_REG_SPI0_INV1_WIDTH             1
#define SIM_CTRL_REG_SPI0_INV1(x)                (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_SPI0_INV1_SHIFT))&SIM_CTRL_REG_SPI0_INV1_MASK)
#define SIM_CTRL_REG_SPI0_INV2_MASK              0x400u
#define SIM_CTRL_REG_SPI0_INV2_SHIFT             10
#define SIM_CTRL_REG_SPI0_INV2_WIDTH             1
#define SIM_CTRL_REG_SPI0_INV2(x)                (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_SPI0_INV2_SHIFT))&SIM_CTRL_REG_SPI0_INV2_MASK)
#define SIM_CTRL_REG_SPI0_INV3_MASK              0x800u
#define SIM_CTRL_REG_SPI0_INV3_SHIFT             11
#define SIM_CTRL_REG_SPI0_INV3_WIDTH             1
#define SIM_CTRL_REG_SPI0_INV3(x)                (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_SPI0_INV3_SHIFT))&SIM_CTRL_REG_SPI0_INV3_MASK)
#define SIM_CTRL_REG_SPI1_INV0_MASK              0x1000u
#define SIM_CTRL_REG_SPI1_INV0_SHIFT             12
#define SIM_CTRL_REG_SPI1_INV0_WIDTH             1
#define SIM_CTRL_REG_SPI1_INV0(x)                (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_SPI1_INV0_SHIFT))&SIM_CTRL_REG_SPI1_INV0_MASK)
#define SIM_CTRL_REG_SPI1_INV1_MASK              0x2000u
#define SIM_CTRL_REG_SPI1_INV1_SHIFT             13
#define SIM_CTRL_REG_SPI1_INV1_WIDTH             1
#define SIM_CTRL_REG_SPI1_INV1(x)                (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_SPI1_INV1_SHIFT))&SIM_CTRL_REG_SPI1_INV1_MASK)
#define SIM_CTRL_REG_SPI1_INV2_MASK              0x4000u
#define SIM_CTRL_REG_SPI1_INV2_SHIFT             14
#define SIM_CTRL_REG_SPI1_INV2_WIDTH             1
#define SIM_CTRL_REG_SPI1_INV2(x)                (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_SPI1_INV2_SHIFT))&SIM_CTRL_REG_SPI1_INV2_MASK)
#define SIM_CTRL_REG_SPI1_INV3_MASK              0x8000u
#define SIM_CTRL_REG_SPI1_INV3_SHIFT             15
#define SIM_CTRL_REG_SPI1_INV3_WIDTH             1
#define SIM_CTRL_REG_SPI1_INV3(x)                (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_SPI1_INV3_SHIFT))&SIM_CTRL_REG_SPI1_INV3_MASK)
#define SIM_CTRL_REG_PLLFLLSEL_MASK              0x30000u
#define SIM_CTRL_REG_PLLFLLSEL_SHIFT             16
#define SIM_CTRL_REG_PLLFLLSEL_WIDTH             2
#define SIM_CTRL_REG_PLLFLLSEL(x)                (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_PLLFLLSEL_SHIFT))&SIM_CTRL_REG_PLLFLLSEL_MASK)
#define SIM_CTRL_REG_XBARCLKOUT_MASK             0xE00000u
#define SIM_CTRL_REG_XBARCLKOUT_SHIFT            21
#define SIM_CTRL_REG_XBARCLKOUT_WIDTH            3
#define SIM_CTRL_REG_XBARCLKOUT(x)               (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_XBARCLKOUT_SHIFT))&SIM_CTRL_REG_XBARCLKOUT_MASK)
#define SIM_CTRL_REG_AFEOUTCLKSEL_MASK           0x1000000u
#define SIM_CTRL_REG_AFEOUTCLKSEL_SHIFT          24
#define SIM_CTRL_REG_AFEOUTCLKSEL_WIDTH          1
#define SIM_CTRL_REG_AFEOUTCLKSEL(x)             (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_AFEOUTCLKSEL_SHIFT))&SIM_CTRL_REG_AFEOUTCLKSEL_MASK)
#define SIM_CTRL_REG_LPUARTSRC_MASK              0xC000000u
#define SIM_CTRL_REG_LPUARTSRC_SHIFT             26
#define SIM_CTRL_REG_LPUARTSRC_WIDTH             2
#define SIM_CTRL_REG_LPUARTSRC(x)                (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_LPUARTSRC_SHIFT))&SIM_CTRL_REG_LPUARTSRC_MASK)
#define SIM_CTRL_REG_TMRFREEZE_MASK              0x80000000u
#define SIM_CTRL_REG_TMRFREEZE_SHIFT             31
#define SIM_CTRL_REG_TMRFREEZE_WIDTH             1
#define SIM_CTRL_REG_TMRFREEZE(x)                (((uint32_t)(((uint32_t)(x))<<SIM_CTRL_REG_TMRFREEZE_SHIFT))&SIM_CTRL_REG_TMRFREEZE_MASK)
/* SDID Bit Fields */
#define SIM_SDID_PINID_MASK                      0xFu
#define SIM_SDID_PINID_SHIFT                     0
#define SIM_SDID_PINID_WIDTH                     4
#define SIM_SDID_PINID(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SDID_PINID_SHIFT))&SIM_SDID_PINID_MASK)
#define SIM_SDID_DIEID_MASK                      0xF0u
#define SIM_SDID_DIEID_SHIFT                     4
#define SIM_SDID_DIEID_WIDTH                     4
#define SIM_SDID_DIEID(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SDID_DIEID_SHIFT))&SIM_SDID_DIEID_MASK)
#define SIM_SDID_REVID_MASK                      0xF00u
#define SIM_SDID_REVID_SHIFT                     8
#define SIM_SDID_REVID_WIDTH                     4
#define SIM_SDID_REVID(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SDID_REVID_SHIFT))&SIM_SDID_REVID_MASK)
#define SIM_SDID_SRAMSIZE_MASK                   0xF000u
#define SIM_SDID_SRAMSIZE_SHIFT                  12
#define SIM_SDID_SRAMSIZE_WIDTH                  4
#define SIM_SDID_SRAMSIZE(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_SDID_SRAMSIZE_SHIFT))&SIM_SDID_SRAMSIZE_MASK)
#define SIM_SDID_ATTR_MASK                       0xF0000u
#define SIM_SDID_ATTR_SHIFT                      16
#define SIM_SDID_ATTR_WIDTH                      4
#define SIM_SDID_ATTR(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SDID_ATTR_SHIFT))&SIM_SDID_ATTR_MASK)
#define SIM_SDID_SERIESID_MASK                   0xF00000u
#define SIM_SDID_SERIESID_SHIFT                  20
#define SIM_SDID_SERIESID_WIDTH                  4
#define SIM_SDID_SERIESID(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_SDID_SERIESID_SHIFT))&SIM_SDID_SERIESID_MASK)
#define SIM_SDID_SUBFAMID_MASK                   0xF000000u
#define SIM_SDID_SUBFAMID_SHIFT                  24
#define SIM_SDID_SUBFAMID_WIDTH                  4
#define SIM_SDID_SUBFAMID(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_SDID_SUBFAMID_SHIFT))&SIM_SDID_SUBFAMID_MASK)
#define SIM_SDID_FAMID_MASK                      0xF0000000u
#define SIM_SDID_FAMID_SHIFT                     28
#define SIM_SDID_FAMID_WIDTH                     4
#define SIM_SDID_FAMID(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SDID_FAMID_SHIFT))&SIM_SDID_FAMID_MASK)
/* SCGC4 Bit Fields */
#define SIM_SCGC4_EWM_MASK                       0x2u
#define SIM_SCGC4_EWM_SHIFT                      1
#define SIM_SCGC4_EWM_WIDTH                      1
#define SIM_SCGC4_EWM(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC4_EWM_SHIFT))&SIM_SCGC4_EWM_MASK)
#define SIM_SCGC4_I2C0_MASK                      0x80u
#define SIM_SCGC4_I2C0_SHIFT                     7
#define SIM_SCGC4_I2C0_WIDTH                     1
#define SIM_SCGC4_I2C0(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC4_I2C0_SHIFT))&SIM_SCGC4_I2C0_MASK)
#define SIM_SCGC4_I2C1_MASK                      0x100u
#define SIM_SCGC4_I2C1_SHIFT                     8
#define SIM_SCGC4_I2C1_WIDTH                     1
#define SIM_SCGC4_I2C1(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC4_I2C1_SHIFT))&SIM_SCGC4_I2C1_MASK)
#define SIM_SCGC4_UART0_MASK                     0x400u
#define SIM_SCGC4_UART0_SHIFT                    10
#define SIM_SCGC4_UART0_WIDTH                    1
#define SIM_SCGC4_UART0(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC4_UART0_SHIFT))&SIM_SCGC4_UART0_MASK)
#define SIM_SCGC4_UART1_MASK                     0x800u
#define SIM_SCGC4_UART1_SHIFT                    11
#define SIM_SCGC4_UART1_WIDTH                    1
#define SIM_SCGC4_UART1(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC4_UART1_SHIFT))&SIM_SCGC4_UART1_MASK)
#define SIM_SCGC4_UART2_MASK                     0x1000u
#define SIM_SCGC4_UART2_SHIFT                    12
#define SIM_SCGC4_UART2_WIDTH                    1
#define SIM_SCGC4_UART2(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC4_UART2_SHIFT))&SIM_SCGC4_UART2_MASK)
#define SIM_SCGC4_UART3_MASK                     0x2000u
#define SIM_SCGC4_UART3_SHIFT                    13
#define SIM_SCGC4_UART3_WIDTH                    1
#define SIM_SCGC4_UART3(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC4_UART3_SHIFT))&SIM_SCGC4_UART3_MASK)
#define SIM_SCGC4_VREF_MASK                      0x8000u
#define SIM_SCGC4_VREF_SHIFT                     15
#define SIM_SCGC4_VREF_WIDTH                     1
#define SIM_SCGC4_VREF(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC4_VREF_SHIFT))&SIM_SCGC4_VREF_MASK)
#define SIM_SCGC4_CMP_MASK                       0x40000u
#define SIM_SCGC4_CMP_SHIFT                      18
#define SIM_SCGC4_CMP_WIDTH                      1
#define SIM_SCGC4_CMP(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC4_CMP_SHIFT))&SIM_SCGC4_CMP_MASK)
#define SIM_SCGC4_SPI0_MASK                      0x200000u
#define SIM_SCGC4_SPI0_SHIFT                     21
#define SIM_SCGC4_SPI0_WIDTH                     1
#define SIM_SCGC4_SPI0(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC4_SPI0_SHIFT))&SIM_SCGC4_SPI0_MASK)
#define SIM_SCGC4_SPI1_MASK                      0x400000u
#define SIM_SCGC4_SPI1_SHIFT                     22
#define SIM_SCGC4_SPI1_WIDTH                     1
#define SIM_SCGC4_SPI1(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC4_SPI1_SHIFT))&SIM_SCGC4_SPI1_MASK)
/* SCGC5 Bit Fields */
#define SIM_SCGC5_SLCD_MASK                      0x8u
#define SIM_SCGC5_SLCD_SHIFT                     3
#define SIM_SCGC5_SLCD_WIDTH                     1
#define SIM_SCGC5_SLCD(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_SLCD_SHIFT))&SIM_SCGC5_SLCD_MASK)
#define SIM_SCGC5_PORTA_MASK                     0x40u
#define SIM_SCGC5_PORTA_SHIFT                    6
#define SIM_SCGC5_PORTA_WIDTH                    1
#define SIM_SCGC5_PORTA(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_PORTA_SHIFT))&SIM_SCGC5_PORTA_MASK)
#define SIM_SCGC5_PORTB_MASK                     0x80u
#define SIM_SCGC5_PORTB_SHIFT                    7
#define SIM_SCGC5_PORTB_WIDTH                    1
#define SIM_SCGC5_PORTB(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_PORTB_SHIFT))&SIM_SCGC5_PORTB_MASK)
#define SIM_SCGC5_PORTC_MASK                     0x100u
#define SIM_SCGC5_PORTC_SHIFT                    8
#define SIM_SCGC5_PORTC_WIDTH                    1
#define SIM_SCGC5_PORTC(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_PORTC_SHIFT))&SIM_SCGC5_PORTC_MASK)
#define SIM_SCGC5_PORTD_MASK                     0x200u
#define SIM_SCGC5_PORTD_SHIFT                    9
#define SIM_SCGC5_PORTD_WIDTH                    1
#define SIM_SCGC5_PORTD(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_PORTD_SHIFT))&SIM_SCGC5_PORTD_MASK)
#define SIM_SCGC5_PORTE_MASK                     0x400u
#define SIM_SCGC5_PORTE_SHIFT                    10
#define SIM_SCGC5_PORTE_WIDTH                    1
#define SIM_SCGC5_PORTE(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_PORTE_SHIFT))&SIM_SCGC5_PORTE_MASK)
#define SIM_SCGC5_PORTF_MASK                     0x800u
#define SIM_SCGC5_PORTF_SHIFT                    11
#define SIM_SCGC5_PORTF_WIDTH                    1
#define SIM_SCGC5_PORTF(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_PORTF_SHIFT))&SIM_SCGC5_PORTF_MASK)
#define SIM_SCGC5_PORTG_MASK                     0x1000u
#define SIM_SCGC5_PORTG_SHIFT                    12
#define SIM_SCGC5_PORTG_WIDTH                    1
#define SIM_SCGC5_PORTG(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_PORTG_SHIFT))&SIM_SCGC5_PORTG_MASK)
#define SIM_SCGC5_PORTH_MASK                     0x2000u
#define SIM_SCGC5_PORTH_SHIFT                    13
#define SIM_SCGC5_PORTH_WIDTH                    1
#define SIM_SCGC5_PORTH(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_PORTH_SHIFT))&SIM_SCGC5_PORTH_MASK)
#define SIM_SCGC5_PORTI_MASK                     0x4000u
#define SIM_SCGC5_PORTI_SHIFT                    14
#define SIM_SCGC5_PORTI_WIDTH                    1
#define SIM_SCGC5_PORTI(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_PORTI_SHIFT))&SIM_SCGC5_PORTI_MASK)
#define SIM_SCGC5_RTC_MASK                       0x10000u
#define SIM_SCGC5_RTC_SHIFT                      16
#define SIM_SCGC5_RTC_WIDTH                      1
#define SIM_SCGC5_RTC(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_RTC_SHIFT))&SIM_SCGC5_RTC_MASK)
#define SIM_SCGC5_RTCREG_MASK                    0x20000u
#define SIM_SCGC5_RTCREG_SHIFT                   17
#define SIM_SCGC5_RTCREG_WIDTH                   1
#define SIM_SCGC5_RTCREG(x)                      (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_RTCREG_SHIFT))&SIM_SCGC5_RTCREG_MASK)
#define SIM_SCGC5_XBAR_MASK                      0x200000u
#define SIM_SCGC5_XBAR_SHIFT                     21
#define SIM_SCGC5_XBAR_WIDTH                     1
#define SIM_SCGC5_XBAR(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_XBAR_SHIFT))&SIM_SCGC5_XBAR_MASK)
#define SIM_SCGC5_TMR0_MASK                      0x800000u
#define SIM_SCGC5_TMR0_SHIFT                     23
#define SIM_SCGC5_TMR0_WIDTH                     1
#define SIM_SCGC5_TMR0(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_TMR0_SHIFT))&SIM_SCGC5_TMR0_MASK)
#define SIM_SCGC5_TMR1_MASK                      0x1000000u
#define SIM_SCGC5_TMR1_SHIFT                     24
#define SIM_SCGC5_TMR1_WIDTH                     1
#define SIM_SCGC5_TMR1(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_TMR1_SHIFT))&SIM_SCGC5_TMR1_MASK)
#define SIM_SCGC5_TMR2_MASK                      0x2000000u
#define SIM_SCGC5_TMR2_SHIFT                     25
#define SIM_SCGC5_TMR2_WIDTH                     1
#define SIM_SCGC5_TMR2(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_TMR2_SHIFT))&SIM_SCGC5_TMR2_MASK)
#define SIM_SCGC5_TMR3_MASK                      0x4000000u
#define SIM_SCGC5_TMR3_SHIFT                     26
#define SIM_SCGC5_TMR3_WIDTH                     1
#define SIM_SCGC5_TMR3(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC5_TMR3_SHIFT))&SIM_SCGC5_TMR3_MASK)
/* SCGC6 Bit Fields */
#define SIM_SCGC6_FTFA_MASK                      0x1u
#define SIM_SCGC6_FTFA_SHIFT                     0
#define SIM_SCGC6_FTFA_WIDTH                     1
#define SIM_SCGC6_FTFA(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_FTFA_SHIFT))&SIM_SCGC6_FTFA_MASK)
#define SIM_SCGC6_DMACHMUX_MASK                  0x2u
#define SIM_SCGC6_DMACHMUX_SHIFT                 1
#define SIM_SCGC6_DMACHMUX_WIDTH                 1
#define SIM_SCGC6_DMACHMUX(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_DMACHMUX_SHIFT))&SIM_SCGC6_DMACHMUX_MASK)
#define SIM_SCGC6_RNGA_MASK                      0x200u
#define SIM_SCGC6_RNGA_SHIFT                     9
#define SIM_SCGC6_RNGA_WIDTH                     1
#define SIM_SCGC6_RNGA(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_RNGA_SHIFT))&SIM_SCGC6_RNGA_MASK)
#define SIM_SCGC6_LPUART_MASK                    0x400u
#define SIM_SCGC6_LPUART_SHIFT                   10
#define SIM_SCGC6_LPUART_WIDTH                   1
#define SIM_SCGC6_LPUART(x)                      (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_LPUART_SHIFT))&SIM_SCGC6_LPUART_MASK)
#define SIM_SCGC6_ADC_MASK                       0x800u
#define SIM_SCGC6_ADC_SHIFT                      11
#define SIM_SCGC6_ADC_WIDTH                      1
#define SIM_SCGC6_ADC(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_ADC_SHIFT))&SIM_SCGC6_ADC_MASK)
#define SIM_SCGC6_PIT0_MASK                      0x2000u
#define SIM_SCGC6_PIT0_SHIFT                     13
#define SIM_SCGC6_PIT0_WIDTH                     1
#define SIM_SCGC6_PIT0(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_PIT0_SHIFT))&SIM_SCGC6_PIT0_MASK)
#define SIM_SCGC6_PIT1_MASK                      0x4000u
#define SIM_SCGC6_PIT1_SHIFT                     14
#define SIM_SCGC6_PIT1_WIDTH                     1
#define SIM_SCGC6_PIT1(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_PIT1_SHIFT))&SIM_SCGC6_PIT1_MASK)
#define SIM_SCGC6_AFE_MASK                       0x10000u
#define SIM_SCGC6_AFE_SHIFT                      16
#define SIM_SCGC6_AFE_WIDTH                      1
#define SIM_SCGC6_AFE(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_AFE_SHIFT))&SIM_SCGC6_AFE_MASK)
#define SIM_SCGC6_CRC_MASK                       0x100000u
#define SIM_SCGC6_CRC_SHIFT                      20
#define SIM_SCGC6_CRC_WIDTH                      1
#define SIM_SCGC6_CRC(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_CRC_SHIFT))&SIM_SCGC6_CRC_MASK)
#define SIM_SCGC6_PDB_MASK                       0x400000u
#define SIM_SCGC6_PDB_SHIFT                      22
#define SIM_SCGC6_PDB_WIDTH                      1
#define SIM_SCGC6_PDB(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_PDB_SHIFT))&SIM_SCGC6_PDB_MASK)
#define SIM_SCGC6_PORTJ_MASK                     0x800000u
#define SIM_SCGC6_PORTJ_SHIFT                    23
#define SIM_SCGC6_PORTJ_WIDTH                    1
#define SIM_SCGC6_PORTJ(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_PORTJ_SHIFT))&SIM_SCGC6_PORTJ_MASK)
#define SIM_SCGC6_PORTK_MASK                     0x1000000u
#define SIM_SCGC6_PORTK_SHIFT                    24
#define SIM_SCGC6_PORTK_WIDTH                    1
#define SIM_SCGC6_PORTK(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_PORTK_SHIFT))&SIM_SCGC6_PORTK_MASK)
#define SIM_SCGC6_PORTL_MASK                     0x2000000u
#define SIM_SCGC6_PORTL_SHIFT                    25
#define SIM_SCGC6_PORTL_WIDTH                    1
#define SIM_SCGC6_PORTL(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_PORTL_SHIFT))&SIM_SCGC6_PORTL_MASK)
#define SIM_SCGC6_PORTM_MASK                     0x4000000u
#define SIM_SCGC6_PORTM_SHIFT                    26
#define SIM_SCGC6_PORTM_WIDTH                    1
#define SIM_SCGC6_PORTM(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_PORTM_SHIFT))&SIM_SCGC6_PORTM_MASK)
#define SIM_SCGC6_LPTMR_MASK                     0x10000000u
#define SIM_SCGC6_LPTMR_SHIFT                    28
#define SIM_SCGC6_LPTMR_WIDTH                    1
#define SIM_SCGC6_LPTMR(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SCGC6_LPTMR_SHIFT))&SIM_SCGC6_LPTMR_MASK)
/* SCGC7 Bit Fields */
#define SIM_SCGC7_MPU_MASK                       0x1u
#define SIM_SCGC7_MPU_SHIFT                      0
#define SIM_SCGC7_MPU_WIDTH                      1
#define SIM_SCGC7_MPU(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC7_MPU_SHIFT))&SIM_SCGC7_MPU_MASK)
#define SIM_SCGC7_DMA_MASK                       0x2u
#define SIM_SCGC7_DMA_SHIFT                      1
#define SIM_SCGC7_DMA_WIDTH                      1
#define SIM_SCGC7_DMA(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC7_DMA_SHIFT))&SIM_SCGC7_DMA_MASK)
#define SIM_SCGC7_CAU_MASK                       0x4u
#define SIM_SCGC7_CAU_SHIFT                      2
#define SIM_SCGC7_CAU_WIDTH                      1
#define SIM_SCGC7_CAU(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC7_CAU_SHIFT))&SIM_SCGC7_CAU_MASK)
/* CLKDIV1 Bit Fields */
#define SIM_CLKDIV1_FLASHCLKMODE_MASK            0x10000u
#define SIM_CLKDIV1_FLASHCLKMODE_SHIFT           16
#define SIM_CLKDIV1_FLASHCLKMODE_WIDTH           1
#define SIM_CLKDIV1_FLASHCLKMODE(x)              (((uint32_t)(((uint32_t)(x))<<SIM_CLKDIV1_FLASHCLKMODE_SHIFT))&SIM_CLKDIV1_FLASHCLKMODE_MASK)
#define SIM_CLKDIV1_CLKDIVBUS_MASK               0x3000000u
#define SIM_CLKDIV1_CLKDIVBUS_SHIFT              24
#define SIM_CLKDIV1_CLKDIVBUS_WIDTH              2
#define SIM_CLKDIV1_CLKDIVBUS(x)                 (((uint32_t)(((uint32_t)(x))<<SIM_CLKDIV1_CLKDIVBUS_SHIFT))&SIM_CLKDIV1_CLKDIVBUS_MASK)
#define SIM_CLKDIV1_CLKDIVSYS_MASK               0xF0000000u
#define SIM_CLKDIV1_CLKDIVSYS_SHIFT              28
#define SIM_CLKDIV1_CLKDIVSYS_WIDTH              4
#define SIM_CLKDIV1_CLKDIVSYS(x)                 (((uint32_t)(((uint32_t)(x))<<SIM_CLKDIV1_CLKDIVSYS_SHIFT))&SIM_CLKDIV1_CLKDIVSYS_MASK)
/* FCFG1 Bit Fields */
#define SIM_FCFG1_FLASHDIS_MASK                  0x1u
#define SIM_FCFG1_FLASHDIS_SHIFT                 0
#define SIM_FCFG1_FLASHDIS_WIDTH                 1
#define SIM_FCFG1_FLASHDIS(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_FCFG1_FLASHDIS_SHIFT))&SIM_FCFG1_FLASHDIS_MASK)
#define SIM_FCFG1_FLASHDOZE_MASK                 0x2u
#define SIM_FCFG1_FLASHDOZE_SHIFT                1
#define SIM_FCFG1_FLASHDOZE_WIDTH                1
#define SIM_FCFG1_FLASHDOZE(x)                   (((uint32_t)(((uint32_t)(x))<<SIM_FCFG1_FLASHDOZE_SHIFT))&SIM_FCFG1_FLASHDOZE_MASK)
#define SIM_FCFG1_PFSIZE_MASK                    0xF000000u
#define SIM_FCFG1_PFSIZE_SHIFT                   24
#define SIM_FCFG1_PFSIZE_WIDTH                   4
#define SIM_FCFG1_PFSIZE(x)                      (((uint32_t)(((uint32_t)(x))<<SIM_FCFG1_PFSIZE_SHIFT))&SIM_FCFG1_PFSIZE_MASK)
/* FCFG2 Bit Fields */
#define SIM_FCFG2_MAXADDR_MASK                   0x7F000000u
#define SIM_FCFG2_MAXADDR_SHIFT                  24
#define SIM_FCFG2_MAXADDR_WIDTH                  7
#define SIM_FCFG2_MAXADDR(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_FCFG2_MAXADDR_SHIFT))&SIM_FCFG2_MAXADDR_MASK)
/* UIDH Bit Fields */
#define SIM_UIDH_UID127_96_MASK                  0xFFFFFFFFu
#define SIM_UIDH_UID127_96_SHIFT                 0
#define SIM_UIDH_UID127_96_WIDTH                 32
#define SIM_UIDH_UID127_96(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_UIDH_UID127_96_SHIFT))&SIM_UIDH_UID127_96_MASK)
/* UIDMH Bit Fields */
#define SIM_UIDMH_UID95_64_MASK                  0xFFFFFFFFu
#define SIM_UIDMH_UID95_64_SHIFT                 0
#define SIM_UIDMH_UID95_64_WIDTH                 32
#define SIM_UIDMH_UID95_64(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_UIDMH_UID95_64_SHIFT))&SIM_UIDMH_UID95_64_MASK)
/* UIDML Bit Fields */
#define SIM_UIDML_UID63_32_MASK                  0xFFFFFFFFu
#define SIM_UIDML_UID63_32_SHIFT                 0
#define SIM_UIDML_UID63_32_WIDTH                 32
#define SIM_UIDML_UID63_32(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_UIDML_UID63_32_SHIFT))&SIM_UIDML_UID63_32_MASK)
/* UIDL Bit Fields */
#define SIM_UIDL_UID31_0_MASK                    0xFFFFFFFFu
#define SIM_UIDL_UID31_0_SHIFT                   0
#define SIM_UIDL_UID31_0_WIDTH                   32
#define SIM_UIDL_UID31_0(x)                      (((uint32_t)(((uint32_t)(x))<<SIM_UIDL_UID31_0_SHIFT))&SIM_UIDL_UID31_0_MASK)
/* MISC_CTL Bit Fields */
#define SIM_MISC_CTL_OSCON_MASK                  0x1u
#define SIM_MISC_CTL_OSCON_SHIFT                 0
#define SIM_MISC_CTL_OSCON_WIDTH                 1
#define SIM_MISC_CTL_OSCON(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_OSCON_SHIFT))&SIM_MISC_CTL_OSCON_MASK)
#define SIM_MISC_CTL_PDBADCTRG_MASK              0x2u
#define SIM_MISC_CTL_PDBADCTRG_SHIFT             1
#define SIM_MISC_CTL_PDBADCTRG_WIDTH             1
#define SIM_MISC_CTL_PDBADCTRG(x)                (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_PDBADCTRG_SHIFT))&SIM_MISC_CTL_PDBADCTRG_MASK)
#define SIM_MISC_CTL_DMADONESEL_MASK             0xCu
#define SIM_MISC_CTL_DMADONESEL_SHIFT            2
#define SIM_MISC_CTL_DMADONESEL_WIDTH            2
#define SIM_MISC_CTL_DMADONESEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_DMADONESEL_SHIFT))&SIM_MISC_CTL_DMADONESEL_MASK)
#define SIM_MISC_CTL_AFECLKSEL_MASK              0x30u
#define SIM_MISC_CTL_AFECLKSEL_SHIFT             4
#define SIM_MISC_CTL_AFECLKSEL_WIDTH             2
#define SIM_MISC_CTL_AFECLKSEL(x)                (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_AFECLKSEL_SHIFT))&SIM_MISC_CTL_AFECLKSEL_MASK)
#define SIM_MISC_CTL_AFECLKPADDIR_MASK           0x40u
#define SIM_MISC_CTL_AFECLKPADDIR_SHIFT          6
#define SIM_MISC_CTL_AFECLKPADDIR_WIDTH          1
#define SIM_MISC_CTL_AFECLKPADDIR(x)             (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_AFECLKPADDIR_SHIFT))&SIM_MISC_CTL_AFECLKPADDIR_MASK)
#define SIM_MISC_CTL_UARTMODTYPE_MASK            0x80u
#define SIM_MISC_CTL_UARTMODTYPE_SHIFT           7
#define SIM_MISC_CTL_UARTMODTYPE_WIDTH           1
#define SIM_MISC_CTL_UARTMODTYPE(x)              (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_UARTMODTYPE_SHIFT))&SIM_MISC_CTL_UARTMODTYPE_MASK)
#define SIM_MISC_CTL_UART0IRSEL_MASK             0x100u
#define SIM_MISC_CTL_UART0IRSEL_SHIFT            8
#define SIM_MISC_CTL_UART0IRSEL_WIDTH            1
#define SIM_MISC_CTL_UART0IRSEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_UART0IRSEL_SHIFT))&SIM_MISC_CTL_UART0IRSEL_MASK)
#define SIM_MISC_CTL_UART1IRSEL_MASK             0x200u
#define SIM_MISC_CTL_UART1IRSEL_SHIFT            9
#define SIM_MISC_CTL_UART1IRSEL_WIDTH            1
#define SIM_MISC_CTL_UART1IRSEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_UART1IRSEL_SHIFT))&SIM_MISC_CTL_UART1IRSEL_MASK)
#define SIM_MISC_CTL_UART2IRSEL_MASK             0x400u
#define SIM_MISC_CTL_UART2IRSEL_SHIFT            10
#define SIM_MISC_CTL_UART2IRSEL_WIDTH            1
#define SIM_MISC_CTL_UART2IRSEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_UART2IRSEL_SHIFT))&SIM_MISC_CTL_UART2IRSEL_MASK)
#define SIM_MISC_CTL_UART3IRSEL_MASK             0x800u
#define SIM_MISC_CTL_UART3IRSEL_SHIFT            11
#define SIM_MISC_CTL_UART3IRSEL_WIDTH            1
#define SIM_MISC_CTL_UART3IRSEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_UART3IRSEL_SHIFT))&SIM_MISC_CTL_UART3IRSEL_MASK)
#define SIM_MISC_CTL_EWMINSEL_MASK               0x4000u
#define SIM_MISC_CTL_EWMINSEL_SHIFT              14
#define SIM_MISC_CTL_EWMINSEL_WIDTH              1
#define SIM_MISC_CTL_EWMINSEL(x)                 (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_EWMINSEL_SHIFT))&SIM_MISC_CTL_EWMINSEL_MASK)
#define SIM_MISC_CTL_TMR0PLLSEL_MASK             0x8000u
#define SIM_MISC_CTL_TMR0PLLSEL_SHIFT            15
#define SIM_MISC_CTL_TMR0PLLSEL_WIDTH            1
#define SIM_MISC_CTL_TMR0PLLSEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_TMR0PLLSEL_SHIFT))&SIM_MISC_CTL_TMR0PLLSEL_MASK)
#define SIM_MISC_CTL_TMR0SCSEL_MASK              0x10000u
#define SIM_MISC_CTL_TMR0SCSEL_SHIFT             16
#define SIM_MISC_CTL_TMR0SCSEL_WIDTH             1
#define SIM_MISC_CTL_TMR0SCSEL(x)                (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_TMR0SCSEL_SHIFT))&SIM_MISC_CTL_TMR0SCSEL_MASK)
#define SIM_MISC_CTL_TMR1SCSEL_MASK              0x20000u
#define SIM_MISC_CTL_TMR1SCSEL_SHIFT             17
#define SIM_MISC_CTL_TMR1SCSEL_WIDTH             1
#define SIM_MISC_CTL_TMR1SCSEL(x)                (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_TMR1SCSEL_SHIFT))&SIM_MISC_CTL_TMR1SCSEL_MASK)
#define SIM_MISC_CTL_TMR2SCSEL_MASK              0x40000u
#define SIM_MISC_CTL_TMR2SCSEL_SHIFT             18
#define SIM_MISC_CTL_TMR2SCSEL_WIDTH             1
#define SIM_MISC_CTL_TMR2SCSEL(x)                (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_TMR2SCSEL_SHIFT))&SIM_MISC_CTL_TMR2SCSEL_MASK)
#define SIM_MISC_CTL_TMR3SCSEL_MASK              0x80000u
#define SIM_MISC_CTL_TMR3SCSEL_SHIFT             19
#define SIM_MISC_CTL_TMR3SCSEL_WIDTH             1
#define SIM_MISC_CTL_TMR3SCSEL(x)                (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_TMR3SCSEL_SHIFT))&SIM_MISC_CTL_TMR3SCSEL_MASK)
#define SIM_MISC_CTL_TMR0PCSSEL_MASK             0x300000u
#define SIM_MISC_CTL_TMR0PCSSEL_SHIFT            20
#define SIM_MISC_CTL_TMR0PCSSEL_WIDTH            2
#define SIM_MISC_CTL_TMR0PCSSEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_TMR0PCSSEL_SHIFT))&SIM_MISC_CTL_TMR0PCSSEL_MASK)
#define SIM_MISC_CTL_TMR1PCSSEL_MASK             0xC00000u
#define SIM_MISC_CTL_TMR1PCSSEL_SHIFT            22
#define SIM_MISC_CTL_TMR1PCSSEL_WIDTH            2
#define SIM_MISC_CTL_TMR1PCSSEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_TMR1PCSSEL_SHIFT))&SIM_MISC_CTL_TMR1PCSSEL_MASK)
#define SIM_MISC_CTL_TMR2PCSSEL_MASK             0x3000000u
#define SIM_MISC_CTL_TMR2PCSSEL_SHIFT            24
#define SIM_MISC_CTL_TMR2PCSSEL_WIDTH            2
#define SIM_MISC_CTL_TMR2PCSSEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_TMR2PCSSEL_SHIFT))&SIM_MISC_CTL_TMR2PCSSEL_MASK)
#define SIM_MISC_CTL_TMR3PCSSEL_MASK             0xC000000u
#define SIM_MISC_CTL_TMR3PCSSEL_SHIFT            26
#define SIM_MISC_CTL_TMR3PCSSEL_WIDTH            2
#define SIM_MISC_CTL_TMR3PCSSEL(x)               (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_TMR3PCSSEL_SHIFT))&SIM_MISC_CTL_TMR3PCSSEL_MASK)
#define SIM_MISC_CTL_RTCCLKSEL_MASK              0x10000000u
#define SIM_MISC_CTL_RTCCLKSEL_SHIFT             28
#define SIM_MISC_CTL_RTCCLKSEL_WIDTH             1
#define SIM_MISC_CTL_RTCCLKSEL(x)                (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_RTCCLKSEL_SHIFT))&SIM_MISC_CTL_RTCCLKSEL_MASK)
#define SIM_MISC_CTL_VREFBUFOUTEN_MASK           0x20000000u
#define SIM_MISC_CTL_VREFBUFOUTEN_SHIFT          29
#define SIM_MISC_CTL_VREFBUFOUTEN_WIDTH          1
#define SIM_MISC_CTL_VREFBUFOUTEN(x)             (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_VREFBUFOUTEN_SHIFT))&SIM_MISC_CTL_VREFBUFOUTEN_MASK)
#define SIM_MISC_CTL_VREFBUFINSEL_MASK           0x40000000u
#define SIM_MISC_CTL_VREFBUFINSEL_SHIFT          30
#define SIM_MISC_CTL_VREFBUFINSEL_WIDTH          1
#define SIM_MISC_CTL_VREFBUFINSEL(x)             (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_VREFBUFINSEL_SHIFT))&SIM_MISC_CTL_VREFBUFINSEL_MASK)
#define SIM_MISC_CTL_VREFBUFPD_MASK              0x80000000u
#define SIM_MISC_CTL_VREFBUFPD_SHIFT             31
#define SIM_MISC_CTL_VREFBUFPD_WIDTH             1
#define SIM_MISC_CTL_VREFBUFPD(x)                (((uint32_t)(((uint32_t)(x))<<SIM_MISC_CTL_VREFBUFPD_SHIFT))&SIM_MISC_CTL_VREFBUFPD_MASK)
/* ADC_COMP0 Bit Fields */
#define SIM_ADC_COMP0_ADCCOMPVAL0_MASK           0xFFFFu
#define SIM_ADC_COMP0_ADCCOMPVAL0_SHIFT          0
#define SIM_ADC_COMP0_ADCCOMPVAL0_WIDTH          16
#define SIM_ADC_COMP0_ADCCOMPVAL0(x)             (((uint32_t)(((uint32_t)(x))<<SIM_ADC_COMP0_ADCCOMPVAL0_SHIFT))&SIM_ADC_COMP0_ADCCOMPVAL0_MASK)
#define SIM_ADC_COMP0_ADCCOMPVAL1_MASK           0xFFFF0000u
#define SIM_ADC_COMP0_ADCCOMPVAL1_SHIFT          16
#define SIM_ADC_COMP0_ADCCOMPVAL1_WIDTH          16
#define SIM_ADC_COMP0_ADCCOMPVAL1(x)             (((uint32_t)(((uint32_t)(x))<<SIM_ADC_COMP0_ADCCOMPVAL1_SHIFT))&SIM_ADC_COMP0_ADCCOMPVAL1_MASK)
/* ADC_COMP1 Bit Fields */
#define SIM_ADC_COMP1_ADCCOMPVAL2_MASK           0xFFFFu
#define SIM_ADC_COMP1_ADCCOMPVAL2_SHIFT          0
#define SIM_ADC_COMP1_ADCCOMPVAL2_WIDTH          16
#define SIM_ADC_COMP1_ADCCOMPVAL2(x)             (((uint32_t)(((uint32_t)(x))<<SIM_ADC_COMP1_ADCCOMPVAL2_SHIFT))&SIM_ADC_COMP1_ADCCOMPVAL2_MASK)

/*!
 * @}
 */ /* end of group SIM_Register_Masks */


/* SIM - Peripheral instance base addresses */
/** Peripheral SIM base address */
#define SIM_BASE                                 (0x4003E000u)
/** Peripheral SIM base pointer */
#define SIM                                      ((SIM_Type *)SIM_BASE)
#define SIM_BASE_PTR                             (SIM)
/** Array initializer of SIM peripheral base addresses */
#define SIM_BASE_ADDRS                           { SIM_BASE }
/** Array initializer of SIM peripheral base pointers */
#define SIM_BASE_PTRS                            { SIM }

/* ----------------------------------------------------------------------------
   -- SIM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Accessor_Macros SIM - Register accessor macros
 * @{
 */


/* SIM - Register instance definitions */
/* SIM */
#define SIM_SOPT1                                SIM_SOPT1_REG(SIM)
#define SIM_SOPT1_CFG                            SIM_SOPT1_CFG_REG(SIM)
#define SIM_CTRL_REG                             SIM_CTRL_REG_REG(SIM)
#define SIM_SDID                                 SIM_SDID_REG(SIM)
#define SIM_SCGC4                                SIM_SCGC4_REG(SIM)
#define SIM_SCGC5                                SIM_SCGC5_REG(SIM)
#define SIM_SCGC6                                SIM_SCGC6_REG(SIM)
#define SIM_SCGC7                                SIM_SCGC7_REG(SIM)
#define SIM_CLKDIV1                              SIM_CLKDIV1_REG(SIM)
#define SIM_FCFG1                                SIM_FCFG1_REG(SIM)
#define SIM_FCFG2                                SIM_FCFG2_REG(SIM)
#define SIM_UIDH                                 SIM_UIDH_REG(SIM)
#define SIM_UIDMH                                SIM_UIDMH_REG(SIM)
#define SIM_UIDML                                SIM_UIDML_REG(SIM)
#define SIM_UIDL                                 SIM_UIDL_REG(SIM)
#define SIM_MISC_CTL                             SIM_MISC_CTL_REG(SIM)
#define SIM_ADC_COMP0                            SIM_ADC_COMP0_REG(SIM)
#define SIM_ADC_COMP1                            SIM_ADC_COMP1_REG(SIM)

/*!
 * @}
 */ /* end of group SIM_Register_Accessor_Macros */


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
} SMC_Type, *SMC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Register_Accessor_Macros SMC - Register accessor macros
 * @{
 */


/* SMC - Register accessors */
#define SMC_PMPROT_REG(base)                     ((base)->PMPROT)
#define SMC_PMCTRL_REG(base)                     ((base)->PMCTRL)
#define SMC_STOPCTRL_REG(base)                   ((base)->STOPCTRL)
#define SMC_PMSTAT_REG(base)                     ((base)->PMSTAT)

/*!
 * @}
 */ /* end of group SMC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Register_Masks SMC Register Masks
 * @{
 */

/* PMPROT Bit Fields */
#define SMC_PMPROT_AVLLS_MASK                    0x2u
#define SMC_PMPROT_AVLLS_SHIFT                   1
#define SMC_PMPROT_AVLLS_WIDTH                   1
#define SMC_PMPROT_AVLLS(x)                      (((uint8_t)(((uint8_t)(x))<<SMC_PMPROT_AVLLS_SHIFT))&SMC_PMPROT_AVLLS_MASK)
#define SMC_PMPROT_AVLP_MASK                     0x20u
#define SMC_PMPROT_AVLP_SHIFT                    5
#define SMC_PMPROT_AVLP_WIDTH                    1
#define SMC_PMPROT_AVLP(x)                       (((uint8_t)(((uint8_t)(x))<<SMC_PMPROT_AVLP_SHIFT))&SMC_PMPROT_AVLP_MASK)
/* PMCTRL Bit Fields */
#define SMC_PMCTRL_STOPM_MASK                    0x7u
#define SMC_PMCTRL_STOPM_SHIFT                   0
#define SMC_PMCTRL_STOPM_WIDTH                   3
#define SMC_PMCTRL_STOPM(x)                      (((uint8_t)(((uint8_t)(x))<<SMC_PMCTRL_STOPM_SHIFT))&SMC_PMCTRL_STOPM_MASK)
#define SMC_PMCTRL_STOPA_MASK                    0x8u
#define SMC_PMCTRL_STOPA_SHIFT                   3
#define SMC_PMCTRL_STOPA_WIDTH                   1
#define SMC_PMCTRL_STOPA(x)                      (((uint8_t)(((uint8_t)(x))<<SMC_PMCTRL_STOPA_SHIFT))&SMC_PMCTRL_STOPA_MASK)
#define SMC_PMCTRL_RUNM_MASK                     0x60u
#define SMC_PMCTRL_RUNM_SHIFT                    5
#define SMC_PMCTRL_RUNM_WIDTH                    2
#define SMC_PMCTRL_RUNM(x)                       (((uint8_t)(((uint8_t)(x))<<SMC_PMCTRL_RUNM_SHIFT))&SMC_PMCTRL_RUNM_MASK)
/* STOPCTRL Bit Fields */
#define SMC_STOPCTRL_VLLSM_MASK                  0x7u
#define SMC_STOPCTRL_VLLSM_SHIFT                 0
#define SMC_STOPCTRL_VLLSM_WIDTH                 3
#define SMC_STOPCTRL_VLLSM(x)                    (((uint8_t)(((uint8_t)(x))<<SMC_STOPCTRL_VLLSM_SHIFT))&SMC_STOPCTRL_VLLSM_MASK)
#define SMC_STOPCTRL_PORPO_MASK                  0x20u
#define SMC_STOPCTRL_PORPO_SHIFT                 5
#define SMC_STOPCTRL_PORPO_WIDTH                 1
#define SMC_STOPCTRL_PORPO(x)                    (((uint8_t)(((uint8_t)(x))<<SMC_STOPCTRL_PORPO_SHIFT))&SMC_STOPCTRL_PORPO_MASK)
#define SMC_STOPCTRL_PSTOPO_MASK                 0xC0u
#define SMC_STOPCTRL_PSTOPO_SHIFT                6
#define SMC_STOPCTRL_PSTOPO_WIDTH                2
#define SMC_STOPCTRL_PSTOPO(x)                   (((uint8_t)(((uint8_t)(x))<<SMC_STOPCTRL_PSTOPO_SHIFT))&SMC_STOPCTRL_PSTOPO_MASK)
/* PMSTAT Bit Fields */
#define SMC_PMSTAT_PMSTAT_MASK                   0xFFu
#define SMC_PMSTAT_PMSTAT_SHIFT                  0
#define SMC_PMSTAT_PMSTAT_WIDTH                  8
#define SMC_PMSTAT_PMSTAT(x)                     (((uint8_t)(((uint8_t)(x))<<SMC_PMSTAT_PMSTAT_SHIFT))&SMC_PMSTAT_PMSTAT_MASK)

/*!
 * @}
 */ /* end of group SMC_Register_Masks */


/* SMC - Peripheral instance base addresses */
/** Peripheral SMC base address */
#define SMC_BASE                                 (0x4007E000u)
/** Peripheral SMC base pointer */
#define SMC                                      ((SMC_Type *)SMC_BASE)
#define SMC_BASE_PTR                             (SMC)
/** Array initializer of SMC peripheral base addresses */
#define SMC_BASE_ADDRS                           { SMC_BASE }
/** Array initializer of SMC peripheral base pointers */
#define SMC_BASE_PTRS                            { SMC }

/* ----------------------------------------------------------------------------
   -- SMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Register_Accessor_Macros SMC - Register accessor macros
 * @{
 */


/* SMC - Register instance definitions */
/* SMC */
#define SMC_PMPROT                               SMC_PMPROT_REG(SMC)
#define SMC_PMCTRL                               SMC_PMCTRL_REG(SMC)
#define SMC_STOPCTRL                             SMC_STOPCTRL_REG(SMC)
#define SMC_PMSTAT                               SMC_PMSTAT_REG(SMC)

/*!
 * @}
 */ /* end of group SMC_Register_Accessor_Macros */


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
  __IO uint8_t CI;                                 /**< SPI clear interrupt register, offset: 0xA */
  __IO uint8_t C3;                                 /**< SPI control register 3, offset: 0xB */
} SPI_Type, *SPI_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SPI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Accessor_Macros SPI - Register accessor macros
 * @{
 */


/* SPI - Register accessors */
#define SPI_S_REG(base)                          ((base)->S)
#define SPI_BR_REG(base)                         ((base)->BR)
#define SPI_C2_REG(base)                         ((base)->C2)
#define SPI_C1_REG(base)                         ((base)->C1)
#define SPI_ML_REG(base)                         ((base)->ML)
#define SPI_MH_REG(base)                         ((base)->MH)
#define SPI_DL_REG(base)                         ((base)->DL)
#define SPI_DH_REG(base)                         ((base)->DH)
#define SPI_CI_REG(base)                         ((base)->CI)
#define SPI_C3_REG(base)                         ((base)->C3)

/*!
 * @}
 */ /* end of group SPI_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SPI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Masks SPI Register Masks
 * @{
 */

/* S Bit Fields */
#define SPI_S_RFIFOEF_MASK                       0x1u
#define SPI_S_RFIFOEF_SHIFT                      0
#define SPI_S_RFIFOEF_WIDTH                      1
#define SPI_S_RFIFOEF(x)                         (((uint8_t)(((uint8_t)(x))<<SPI_S_RFIFOEF_SHIFT))&SPI_S_RFIFOEF_MASK)
#define SPI_S_TXFULLF_MASK                       0x2u
#define SPI_S_TXFULLF_SHIFT                      1
#define SPI_S_TXFULLF_WIDTH                      1
#define SPI_S_TXFULLF(x)                         (((uint8_t)(((uint8_t)(x))<<SPI_S_TXFULLF_SHIFT))&SPI_S_TXFULLF_MASK)
#define SPI_S_TNEAREF_MASK                       0x4u
#define SPI_S_TNEAREF_SHIFT                      2
#define SPI_S_TNEAREF_WIDTH                      1
#define SPI_S_TNEAREF(x)                         (((uint8_t)(((uint8_t)(x))<<SPI_S_TNEAREF_SHIFT))&SPI_S_TNEAREF_MASK)
#define SPI_S_RNFULLF_MASK                       0x8u
#define SPI_S_RNFULLF_SHIFT                      3
#define SPI_S_RNFULLF_WIDTH                      1
#define SPI_S_RNFULLF(x)                         (((uint8_t)(((uint8_t)(x))<<SPI_S_RNFULLF_SHIFT))&SPI_S_RNFULLF_MASK)
#define SPI_S_MODF_MASK                          0x10u
#define SPI_S_MODF_SHIFT                         4
#define SPI_S_MODF_WIDTH                         1
#define SPI_S_MODF(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_S_MODF_SHIFT))&SPI_S_MODF_MASK)
#define SPI_S_SPTEF_MASK                         0x20u
#define SPI_S_SPTEF_SHIFT                        5
#define SPI_S_SPTEF_WIDTH                        1
#define SPI_S_SPTEF(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_S_SPTEF_SHIFT))&SPI_S_SPTEF_MASK)
#define SPI_S_SPMF_MASK                          0x40u
#define SPI_S_SPMF_SHIFT                         6
#define SPI_S_SPMF_WIDTH                         1
#define SPI_S_SPMF(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_S_SPMF_SHIFT))&SPI_S_SPMF_MASK)
#define SPI_S_SPRF_MASK                          0x80u
#define SPI_S_SPRF_SHIFT                         7
#define SPI_S_SPRF_WIDTH                         1
#define SPI_S_SPRF(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_S_SPRF_SHIFT))&SPI_S_SPRF_MASK)
/* BR Bit Fields */
#define SPI_BR_SPR_MASK                          0xFu
#define SPI_BR_SPR_SHIFT                         0
#define SPI_BR_SPR_WIDTH                         4
#define SPI_BR_SPR(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_BR_SPR_SHIFT))&SPI_BR_SPR_MASK)
#define SPI_BR_SPPR_MASK                         0x70u
#define SPI_BR_SPPR_SHIFT                        4
#define SPI_BR_SPPR_WIDTH                        3
#define SPI_BR_SPPR(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_BR_SPPR_SHIFT))&SPI_BR_SPPR_MASK)
/* C2 Bit Fields */
#define SPI_C2_SPC0_MASK                         0x1u
#define SPI_C2_SPC0_SHIFT                        0
#define SPI_C2_SPC0_WIDTH                        1
#define SPI_C2_SPC0(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_C2_SPC0_SHIFT))&SPI_C2_SPC0_MASK)
#define SPI_C2_SPISWAI_MASK                      0x2u
#define SPI_C2_SPISWAI_SHIFT                     1
#define SPI_C2_SPISWAI_WIDTH                     1
#define SPI_C2_SPISWAI(x)                        (((uint8_t)(((uint8_t)(x))<<SPI_C2_SPISWAI_SHIFT))&SPI_C2_SPISWAI_MASK)
#define SPI_C2_RXDMAE_MASK                       0x4u
#define SPI_C2_RXDMAE_SHIFT                      2
#define SPI_C2_RXDMAE_WIDTH                      1
#define SPI_C2_RXDMAE(x)                         (((uint8_t)(((uint8_t)(x))<<SPI_C2_RXDMAE_SHIFT))&SPI_C2_RXDMAE_MASK)
#define SPI_C2_BIDIROE_MASK                      0x8u
#define SPI_C2_BIDIROE_SHIFT                     3
#define SPI_C2_BIDIROE_WIDTH                     1
#define SPI_C2_BIDIROE(x)                        (((uint8_t)(((uint8_t)(x))<<SPI_C2_BIDIROE_SHIFT))&SPI_C2_BIDIROE_MASK)
#define SPI_C2_MODFEN_MASK                       0x10u
#define SPI_C2_MODFEN_SHIFT                      4
#define SPI_C2_MODFEN_WIDTH                      1
#define SPI_C2_MODFEN(x)                         (((uint8_t)(((uint8_t)(x))<<SPI_C2_MODFEN_SHIFT))&SPI_C2_MODFEN_MASK)
#define SPI_C2_TXDMAE_MASK                       0x20u
#define SPI_C2_TXDMAE_SHIFT                      5
#define SPI_C2_TXDMAE_WIDTH                      1
#define SPI_C2_TXDMAE(x)                         (((uint8_t)(((uint8_t)(x))<<SPI_C2_TXDMAE_SHIFT))&SPI_C2_TXDMAE_MASK)
#define SPI_C2_SPIMODE_MASK                      0x40u
#define SPI_C2_SPIMODE_SHIFT                     6
#define SPI_C2_SPIMODE_WIDTH                     1
#define SPI_C2_SPIMODE(x)                        (((uint8_t)(((uint8_t)(x))<<SPI_C2_SPIMODE_SHIFT))&SPI_C2_SPIMODE_MASK)
#define SPI_C2_SPMIE_MASK                        0x80u
#define SPI_C2_SPMIE_SHIFT                       7
#define SPI_C2_SPMIE_WIDTH                       1
#define SPI_C2_SPMIE(x)                          (((uint8_t)(((uint8_t)(x))<<SPI_C2_SPMIE_SHIFT))&SPI_C2_SPMIE_MASK)
/* C1 Bit Fields */
#define SPI_C1_LSBFE_MASK                        0x1u
#define SPI_C1_LSBFE_SHIFT                       0
#define SPI_C1_LSBFE_WIDTH                       1
#define SPI_C1_LSBFE(x)                          (((uint8_t)(((uint8_t)(x))<<SPI_C1_LSBFE_SHIFT))&SPI_C1_LSBFE_MASK)
#define SPI_C1_SSOE_MASK                         0x2u
#define SPI_C1_SSOE_SHIFT                        1
#define SPI_C1_SSOE_WIDTH                        1
#define SPI_C1_SSOE(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_C1_SSOE_SHIFT))&SPI_C1_SSOE_MASK)
#define SPI_C1_CPHA_MASK                         0x4u
#define SPI_C1_CPHA_SHIFT                        2
#define SPI_C1_CPHA_WIDTH                        1
#define SPI_C1_CPHA(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_C1_CPHA_SHIFT))&SPI_C1_CPHA_MASK)
#define SPI_C1_CPOL_MASK                         0x8u
#define SPI_C1_CPOL_SHIFT                        3
#define SPI_C1_CPOL_WIDTH                        1
#define SPI_C1_CPOL(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_C1_CPOL_SHIFT))&SPI_C1_CPOL_MASK)
#define SPI_C1_MSTR_MASK                         0x10u
#define SPI_C1_MSTR_SHIFT                        4
#define SPI_C1_MSTR_WIDTH                        1
#define SPI_C1_MSTR(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_C1_MSTR_SHIFT))&SPI_C1_MSTR_MASK)
#define SPI_C1_SPTIE_MASK                        0x20u
#define SPI_C1_SPTIE_SHIFT                       5
#define SPI_C1_SPTIE_WIDTH                       1
#define SPI_C1_SPTIE(x)                          (((uint8_t)(((uint8_t)(x))<<SPI_C1_SPTIE_SHIFT))&SPI_C1_SPTIE_MASK)
#define SPI_C1_SPE_MASK                          0x40u
#define SPI_C1_SPE_SHIFT                         6
#define SPI_C1_SPE_WIDTH                         1
#define SPI_C1_SPE(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_C1_SPE_SHIFT))&SPI_C1_SPE_MASK)
#define SPI_C1_SPIE_MASK                         0x80u
#define SPI_C1_SPIE_SHIFT                        7
#define SPI_C1_SPIE_WIDTH                        1
#define SPI_C1_SPIE(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_C1_SPIE_SHIFT))&SPI_C1_SPIE_MASK)
/* ML Bit Fields */
#define SPI_ML_Bits_MASK                         0xFFu
#define SPI_ML_Bits_SHIFT                        0
#define SPI_ML_Bits_WIDTH                        8
#define SPI_ML_Bits(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_ML_Bits_SHIFT))&SPI_ML_Bits_MASK)
/* MH Bit Fields */
#define SPI_MH_Bits_MASK                         0xFFu
#define SPI_MH_Bits_SHIFT                        0
#define SPI_MH_Bits_WIDTH                        8
#define SPI_MH_Bits(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_MH_Bits_SHIFT))&SPI_MH_Bits_MASK)
/* DL Bit Fields */
#define SPI_DL_Bits_MASK                         0xFFu
#define SPI_DL_Bits_SHIFT                        0
#define SPI_DL_Bits_WIDTH                        8
#define SPI_DL_Bits(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_DL_Bits_SHIFT))&SPI_DL_Bits_MASK)
/* DH Bit Fields */
#define SPI_DH_Bits_MASK                         0xFFu
#define SPI_DH_Bits_SHIFT                        0
#define SPI_DH_Bits_WIDTH                        8
#define SPI_DH_Bits(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_DH_Bits_SHIFT))&SPI_DH_Bits_MASK)
/* CI Bit Fields */
#define SPI_CI_SPRFCI_MASK                       0x1u
#define SPI_CI_SPRFCI_SHIFT                      0
#define SPI_CI_SPRFCI_WIDTH                      1
#define SPI_CI_SPRFCI(x)                         (((uint8_t)(((uint8_t)(x))<<SPI_CI_SPRFCI_SHIFT))&SPI_CI_SPRFCI_MASK)
#define SPI_CI_SPTEFCI_MASK                      0x2u
#define SPI_CI_SPTEFCI_SHIFT                     1
#define SPI_CI_SPTEFCI_WIDTH                     1
#define SPI_CI_SPTEFCI(x)                        (((uint8_t)(((uint8_t)(x))<<SPI_CI_SPTEFCI_SHIFT))&SPI_CI_SPTEFCI_MASK)
#define SPI_CI_RNFULLFCI_MASK                    0x4u
#define SPI_CI_RNFULLFCI_SHIFT                   2
#define SPI_CI_RNFULLFCI_WIDTH                   1
#define SPI_CI_RNFULLFCI(x)                      (((uint8_t)(((uint8_t)(x))<<SPI_CI_RNFULLFCI_SHIFT))&SPI_CI_RNFULLFCI_MASK)
#define SPI_CI_TNEAREFCI_MASK                    0x8u
#define SPI_CI_TNEAREFCI_SHIFT                   3
#define SPI_CI_TNEAREFCI_WIDTH                   1
#define SPI_CI_TNEAREFCI(x)                      (((uint8_t)(((uint8_t)(x))<<SPI_CI_TNEAREFCI_SHIFT))&SPI_CI_TNEAREFCI_MASK)
#define SPI_CI_RXFOF_MASK                        0x10u
#define SPI_CI_RXFOF_SHIFT                       4
#define SPI_CI_RXFOF_WIDTH                       1
#define SPI_CI_RXFOF(x)                          (((uint8_t)(((uint8_t)(x))<<SPI_CI_RXFOF_SHIFT))&SPI_CI_RXFOF_MASK)
#define SPI_CI_TXFOF_MASK                        0x20u
#define SPI_CI_TXFOF_SHIFT                       5
#define SPI_CI_TXFOF_WIDTH                       1
#define SPI_CI_TXFOF(x)                          (((uint8_t)(((uint8_t)(x))<<SPI_CI_TXFOF_SHIFT))&SPI_CI_TXFOF_MASK)
#define SPI_CI_RXFERR_MASK                       0x40u
#define SPI_CI_RXFERR_SHIFT                      6
#define SPI_CI_RXFERR_WIDTH                      1
#define SPI_CI_RXFERR(x)                         (((uint8_t)(((uint8_t)(x))<<SPI_CI_RXFERR_SHIFT))&SPI_CI_RXFERR_MASK)
#define SPI_CI_TXFERR_MASK                       0x80u
#define SPI_CI_TXFERR_SHIFT                      7
#define SPI_CI_TXFERR_WIDTH                      1
#define SPI_CI_TXFERR(x)                         (((uint8_t)(((uint8_t)(x))<<SPI_CI_TXFERR_SHIFT))&SPI_CI_TXFERR_MASK)
/* C3 Bit Fields */
#define SPI_C3_FIFOMODE_MASK                     0x1u
#define SPI_C3_FIFOMODE_SHIFT                    0
#define SPI_C3_FIFOMODE_WIDTH                    1
#define SPI_C3_FIFOMODE(x)                       (((uint8_t)(((uint8_t)(x))<<SPI_C3_FIFOMODE_SHIFT))&SPI_C3_FIFOMODE_MASK)
#define SPI_C3_RNFULLIEN_MASK                    0x2u
#define SPI_C3_RNFULLIEN_SHIFT                   1
#define SPI_C3_RNFULLIEN_WIDTH                   1
#define SPI_C3_RNFULLIEN(x)                      (((uint8_t)(((uint8_t)(x))<<SPI_C3_RNFULLIEN_SHIFT))&SPI_C3_RNFULLIEN_MASK)
#define SPI_C3_TNEARIEN_MASK                     0x4u
#define SPI_C3_TNEARIEN_SHIFT                    2
#define SPI_C3_TNEARIEN_WIDTH                    1
#define SPI_C3_TNEARIEN(x)                       (((uint8_t)(((uint8_t)(x))<<SPI_C3_TNEARIEN_SHIFT))&SPI_C3_TNEARIEN_MASK)
#define SPI_C3_INTCLR_MASK                       0x8u
#define SPI_C3_INTCLR_SHIFT                      3
#define SPI_C3_INTCLR_WIDTH                      1
#define SPI_C3_INTCLR(x)                         (((uint8_t)(((uint8_t)(x))<<SPI_C3_INTCLR_SHIFT))&SPI_C3_INTCLR_MASK)
#define SPI_C3_RNFULLF_MARK_MASK                 0x10u
#define SPI_C3_RNFULLF_MARK_SHIFT                4
#define SPI_C3_RNFULLF_MARK_WIDTH                1
#define SPI_C3_RNFULLF_MARK(x)                   (((uint8_t)(((uint8_t)(x))<<SPI_C3_RNFULLF_MARK_SHIFT))&SPI_C3_RNFULLF_MARK_MASK)
#define SPI_C3_TNEAREF_MARK_MASK                 0x20u
#define SPI_C3_TNEAREF_MARK_SHIFT                5
#define SPI_C3_TNEAREF_MARK_WIDTH                1
#define SPI_C3_TNEAREF_MARK(x)                   (((uint8_t)(((uint8_t)(x))<<SPI_C3_TNEAREF_MARK_SHIFT))&SPI_C3_TNEAREF_MARK_MASK)

/*!
 * @}
 */ /* end of group SPI_Register_Masks */


/* SPI - Peripheral instance base addresses */
/** Peripheral SPI0 base address */
#define SPI0_BASE                                (0x40075000u)
/** Peripheral SPI0 base pointer */
#define SPI0                                     ((SPI_Type *)SPI0_BASE)
#define SPI0_BASE_PTR                            (SPI0)
/** Peripheral SPI1 base address */
#define SPI1_BASE                                (0x40076000u)
/** Peripheral SPI1 base pointer */
#define SPI1                                     ((SPI_Type *)SPI1_BASE)
#define SPI1_BASE_PTR                            (SPI1)
/** Array initializer of SPI peripheral base addresses */
#define SPI_BASE_ADDRS                           { SPI0_BASE, SPI1_BASE }
/** Array initializer of SPI peripheral base pointers */
#define SPI_BASE_PTRS                            { SPI0, SPI1 }
/** Interrupt vectors for the SPI peripheral type */
#define SPI_IRQS                                 { SPI0_SPI1_IRQn, SPI0_SPI1_IRQn }

/* ----------------------------------------------------------------------------
   -- SPI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Accessor_Macros SPI - Register accessor macros
 * @{
 */


/* SPI - Register instance definitions */
/* SPI0 */
#define SPI0_S                                   SPI_S_REG(SPI0)
#define SPI0_BR                                  SPI_BR_REG(SPI0)
#define SPI0_C2                                  SPI_C2_REG(SPI0)
#define SPI0_C1                                  SPI_C1_REG(SPI0)
#define SPI0_ML                                  SPI_ML_REG(SPI0)
#define SPI0_MH                                  SPI_MH_REG(SPI0)
#define SPI0_DL                                  SPI_DL_REG(SPI0)
#define SPI0_DH                                  SPI_DH_REG(SPI0)
/* SPI1 */
#define SPI1_S                                   SPI_S_REG(SPI1)
#define SPI1_BR                                  SPI_BR_REG(SPI1)
#define SPI1_C2                                  SPI_C2_REG(SPI1)
#define SPI1_C1                                  SPI_C1_REG(SPI1)
#define SPI1_ML                                  SPI_ML_REG(SPI1)
#define SPI1_MH                                  SPI_MH_REG(SPI1)
#define SPI1_DL                                  SPI_DL_REG(SPI1)
#define SPI1_DH                                  SPI_DH_REG(SPI1)
#define SPI1_CI                                  SPI_CI_REG(SPI1)
#define SPI1_C3                                  SPI_C3_REG(SPI1)

/*!
 * @}
 */ /* end of group SPI_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SPI_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- TMR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TMR_Peripheral_Access_Layer TMR Peripheral Access Layer
 * @{
 */

/** TMR - Register Layout Typedef */
typedef struct {
  __IO uint16_t COMP1;                             /**< Timer Channel Compare Register 1, offset: 0x0 */
  __IO uint16_t COMP2;                             /**< Timer Channel Compare Register 2, offset: 0x2 */
  __IO uint16_t CAPT;                              /**< Timer Channel Capture Register, offset: 0x4 */
  __IO uint16_t LOAD;                              /**< Timer Channel Load Register, offset: 0x6 */
  __IO uint16_t HOLD;                              /**< Timer Channel Hold Register, offset: 0x8 */
  __IO uint16_t CNTR;                              /**< Timer Channel Counter Register, offset: 0xA */
  __IO uint16_t CTRL;                              /**< Timer Channel Control Register, offset: 0xC */
  __IO uint16_t SCTRL;                             /**< Timer Channel Status and Control Register, offset: 0xE */
  __IO uint16_t CMPLD1;                            /**< Timer Channel Comparator Load Register 1, offset: 0x10 */
  __IO uint16_t CMPLD2;                            /**< Timer Channel Comparator Load Register 2, offset: 0x12 */
  __IO uint16_t CSCTRL;                            /**< Timer Channel Comparator Status and Control Register, offset: 0x14 */
  __IO uint16_t FILT;                              /**< Timer Channel Input Filter Register, offset: 0x16 */
       uint8_t RESERVED_0[6];
  __IO uint16_t ENBL;                              /**< Timer Channel Enable Register, offset: 0x1E */
} TMR_Type, *TMR_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- TMR - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TMR_Register_Accessor_Macros TMR - Register accessor macros
 * @{
 */


/* TMR - Register accessors */
#define TMR_COMP1_REG(base)                      ((base)->COMP1)
#define TMR_COMP2_REG(base)                      ((base)->COMP2)
#define TMR_CAPT_REG(base)                       ((base)->CAPT)
#define TMR_LOAD_REG(base)                       ((base)->LOAD)
#define TMR_HOLD_REG(base)                       ((base)->HOLD)
#define TMR_CNTR_REG(base)                       ((base)->CNTR)
#define TMR_CTRL_REG(base)                       ((base)->CTRL)
#define TMR_SCTRL_REG(base)                      ((base)->SCTRL)
#define TMR_CMPLD1_REG(base)                     ((base)->CMPLD1)
#define TMR_CMPLD2_REG(base)                     ((base)->CMPLD2)
#define TMR_CSCTRL_REG(base)                     ((base)->CSCTRL)
#define TMR_FILT_REG(base)                       ((base)->FILT)
#define TMR_ENBL_REG(base)                       ((base)->ENBL)

/*!
 * @}
 */ /* end of group TMR_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- TMR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TMR_Register_Masks TMR Register Masks
 * @{
 */

/* COMP1 Bit Fields */
#define TMR_COMP1_COMPARISON_1_MASK              0xFFFFu
#define TMR_COMP1_COMPARISON_1_SHIFT             0
#define TMR_COMP1_COMPARISON_1_WIDTH             16
#define TMR_COMP1_COMPARISON_1(x)                (((uint16_t)(((uint16_t)(x))<<TMR_COMP1_COMPARISON_1_SHIFT))&TMR_COMP1_COMPARISON_1_MASK)
/* COMP2 Bit Fields */
#define TMR_COMP2_COMPARISON_2_MASK              0xFFFFu
#define TMR_COMP2_COMPARISON_2_SHIFT             0
#define TMR_COMP2_COMPARISON_2_WIDTH             16
#define TMR_COMP2_COMPARISON_2(x)                (((uint16_t)(((uint16_t)(x))<<TMR_COMP2_COMPARISON_2_SHIFT))&TMR_COMP2_COMPARISON_2_MASK)
/* CAPT Bit Fields */
#define TMR_CAPT_CAPTURE_MASK                    0xFFFFu
#define TMR_CAPT_CAPTURE_SHIFT                   0
#define TMR_CAPT_CAPTURE_WIDTH                   16
#define TMR_CAPT_CAPTURE(x)                      (((uint16_t)(((uint16_t)(x))<<TMR_CAPT_CAPTURE_SHIFT))&TMR_CAPT_CAPTURE_MASK)
/* LOAD Bit Fields */
#define TMR_LOAD_LOAD_MASK                       0xFFFFu
#define TMR_LOAD_LOAD_SHIFT                      0
#define TMR_LOAD_LOAD_WIDTH                      16
#define TMR_LOAD_LOAD(x)                         (((uint16_t)(((uint16_t)(x))<<TMR_LOAD_LOAD_SHIFT))&TMR_LOAD_LOAD_MASK)
/* HOLD Bit Fields */
#define TMR_HOLD_HOLD_MASK                       0xFFFFu
#define TMR_HOLD_HOLD_SHIFT                      0
#define TMR_HOLD_HOLD_WIDTH                      16
#define TMR_HOLD_HOLD(x)                         (((uint16_t)(((uint16_t)(x))<<TMR_HOLD_HOLD_SHIFT))&TMR_HOLD_HOLD_MASK)
/* CNTR Bit Fields */
#define TMR_CNTR_COUNTER_MASK                    0xFFFFu
#define TMR_CNTR_COUNTER_SHIFT                   0
#define TMR_CNTR_COUNTER_WIDTH                   16
#define TMR_CNTR_COUNTER(x)                      (((uint16_t)(((uint16_t)(x))<<TMR_CNTR_COUNTER_SHIFT))&TMR_CNTR_COUNTER_MASK)
/* CTRL Bit Fields */
#define TMR_CTRL_OUTMODE_MASK                    0x7u
#define TMR_CTRL_OUTMODE_SHIFT                   0
#define TMR_CTRL_OUTMODE_WIDTH                   3
#define TMR_CTRL_OUTMODE(x)                      (((uint16_t)(((uint16_t)(x))<<TMR_CTRL_OUTMODE_SHIFT))&TMR_CTRL_OUTMODE_MASK)
#define TMR_CTRL_COINIT_MASK                     0x8u
#define TMR_CTRL_COINIT_SHIFT                    3
#define TMR_CTRL_COINIT_WIDTH                    1
#define TMR_CTRL_COINIT(x)                       (((uint16_t)(((uint16_t)(x))<<TMR_CTRL_COINIT_SHIFT))&TMR_CTRL_COINIT_MASK)
#define TMR_CTRL_DIR_MASK                        0x10u
#define TMR_CTRL_DIR_SHIFT                       4
#define TMR_CTRL_DIR_WIDTH                       1
#define TMR_CTRL_DIR(x)                          (((uint16_t)(((uint16_t)(x))<<TMR_CTRL_DIR_SHIFT))&TMR_CTRL_DIR_MASK)
#define TMR_CTRL_LENGTH_MASK                     0x20u
#define TMR_CTRL_LENGTH_SHIFT                    5
#define TMR_CTRL_LENGTH_WIDTH                    1
#define TMR_CTRL_LENGTH(x)                       (((uint16_t)(((uint16_t)(x))<<TMR_CTRL_LENGTH_SHIFT))&TMR_CTRL_LENGTH_MASK)
#define TMR_CTRL_ONCE_MASK                       0x40u
#define TMR_CTRL_ONCE_SHIFT                      6
#define TMR_CTRL_ONCE_WIDTH                      1
#define TMR_CTRL_ONCE(x)                         (((uint16_t)(((uint16_t)(x))<<TMR_CTRL_ONCE_SHIFT))&TMR_CTRL_ONCE_MASK)
#define TMR_CTRL_SCS_MASK                        0x180u
#define TMR_CTRL_SCS_SHIFT                       7
#define TMR_CTRL_SCS_WIDTH                       2
#define TMR_CTRL_SCS(x)                          (((uint16_t)(((uint16_t)(x))<<TMR_CTRL_SCS_SHIFT))&TMR_CTRL_SCS_MASK)
#define TMR_CTRL_PCS_MASK                        0x1E00u
#define TMR_CTRL_PCS_SHIFT                       9
#define TMR_CTRL_PCS_WIDTH                       4
#define TMR_CTRL_PCS(x)                          (((uint16_t)(((uint16_t)(x))<<TMR_CTRL_PCS_SHIFT))&TMR_CTRL_PCS_MASK)
#define TMR_CTRL_CM_MASK                         0xE000u
#define TMR_CTRL_CM_SHIFT                        13
#define TMR_CTRL_CM_WIDTH                        3
#define TMR_CTRL_CM(x)                           (((uint16_t)(((uint16_t)(x))<<TMR_CTRL_CM_SHIFT))&TMR_CTRL_CM_MASK)
/* SCTRL Bit Fields */
#define TMR_SCTRL_OEN_MASK                       0x1u
#define TMR_SCTRL_OEN_SHIFT                      0
#define TMR_SCTRL_OEN_WIDTH                      1
#define TMR_SCTRL_OEN(x)                         (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_OEN_SHIFT))&TMR_SCTRL_OEN_MASK)
#define TMR_SCTRL_OPS_MASK                       0x2u
#define TMR_SCTRL_OPS_SHIFT                      1
#define TMR_SCTRL_OPS_WIDTH                      1
#define TMR_SCTRL_OPS(x)                         (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_OPS_SHIFT))&TMR_SCTRL_OPS_MASK)
#define TMR_SCTRL_FORCE_MASK                     0x4u
#define TMR_SCTRL_FORCE_SHIFT                    2
#define TMR_SCTRL_FORCE_WIDTH                    1
#define TMR_SCTRL_FORCE(x)                       (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_FORCE_SHIFT))&TMR_SCTRL_FORCE_MASK)
#define TMR_SCTRL_VAL_MASK                       0x8u
#define TMR_SCTRL_VAL_SHIFT                      3
#define TMR_SCTRL_VAL_WIDTH                      1
#define TMR_SCTRL_VAL(x)                         (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_VAL_SHIFT))&TMR_SCTRL_VAL_MASK)
#define TMR_SCTRL_EEOF_MASK                      0x10u
#define TMR_SCTRL_EEOF_SHIFT                     4
#define TMR_SCTRL_EEOF_WIDTH                     1
#define TMR_SCTRL_EEOF(x)                        (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_EEOF_SHIFT))&TMR_SCTRL_EEOF_MASK)
#define TMR_SCTRL_MSTR_MASK                      0x20u
#define TMR_SCTRL_MSTR_SHIFT                     5
#define TMR_SCTRL_MSTR_WIDTH                     1
#define TMR_SCTRL_MSTR(x)                        (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_MSTR_SHIFT))&TMR_SCTRL_MSTR_MASK)
#define TMR_SCTRL_CAPTURE_MODE_MASK              0xC0u
#define TMR_SCTRL_CAPTURE_MODE_SHIFT             6
#define TMR_SCTRL_CAPTURE_MODE_WIDTH             2
#define TMR_SCTRL_CAPTURE_MODE(x)                (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_CAPTURE_MODE_SHIFT))&TMR_SCTRL_CAPTURE_MODE_MASK)
#define TMR_SCTRL_INPUT_MASK                     0x100u
#define TMR_SCTRL_INPUT_SHIFT                    8
#define TMR_SCTRL_INPUT_WIDTH                    1
#define TMR_SCTRL_INPUT(x)                       (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_INPUT_SHIFT))&TMR_SCTRL_INPUT_MASK)
#define TMR_SCTRL_IPS_MASK                       0x200u
#define TMR_SCTRL_IPS_SHIFT                      9
#define TMR_SCTRL_IPS_WIDTH                      1
#define TMR_SCTRL_IPS(x)                         (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_IPS_SHIFT))&TMR_SCTRL_IPS_MASK)
#define TMR_SCTRL_IEFIE_MASK                     0x400u
#define TMR_SCTRL_IEFIE_SHIFT                    10
#define TMR_SCTRL_IEFIE_WIDTH                    1
#define TMR_SCTRL_IEFIE(x)                       (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_IEFIE_SHIFT))&TMR_SCTRL_IEFIE_MASK)
#define TMR_SCTRL_IEF_MASK                       0x800u
#define TMR_SCTRL_IEF_SHIFT                      11
#define TMR_SCTRL_IEF_WIDTH                      1
#define TMR_SCTRL_IEF(x)                         (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_IEF_SHIFT))&TMR_SCTRL_IEF_MASK)
#define TMR_SCTRL_TOFIE_MASK                     0x1000u
#define TMR_SCTRL_TOFIE_SHIFT                    12
#define TMR_SCTRL_TOFIE_WIDTH                    1
#define TMR_SCTRL_TOFIE(x)                       (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_TOFIE_SHIFT))&TMR_SCTRL_TOFIE_MASK)
#define TMR_SCTRL_TOF_MASK                       0x2000u
#define TMR_SCTRL_TOF_SHIFT                      13
#define TMR_SCTRL_TOF_WIDTH                      1
#define TMR_SCTRL_TOF(x)                         (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_TOF_SHIFT))&TMR_SCTRL_TOF_MASK)
#define TMR_SCTRL_TCFIE_MASK                     0x4000u
#define TMR_SCTRL_TCFIE_SHIFT                    14
#define TMR_SCTRL_TCFIE_WIDTH                    1
#define TMR_SCTRL_TCFIE(x)                       (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_TCFIE_SHIFT))&TMR_SCTRL_TCFIE_MASK)
#define TMR_SCTRL_TCF_MASK                       0x8000u
#define TMR_SCTRL_TCF_SHIFT                      15
#define TMR_SCTRL_TCF_WIDTH                      1
#define TMR_SCTRL_TCF(x)                         (((uint16_t)(((uint16_t)(x))<<TMR_SCTRL_TCF_SHIFT))&TMR_SCTRL_TCF_MASK)
/* CMPLD1 Bit Fields */
#define TMR_CMPLD1_COMPARATOR_LOAD_1_MASK        0xFFFFu
#define TMR_CMPLD1_COMPARATOR_LOAD_1_SHIFT       0
#define TMR_CMPLD1_COMPARATOR_LOAD_1_WIDTH       16
#define TMR_CMPLD1_COMPARATOR_LOAD_1(x)          (((uint16_t)(((uint16_t)(x))<<TMR_CMPLD1_COMPARATOR_LOAD_1_SHIFT))&TMR_CMPLD1_COMPARATOR_LOAD_1_MASK)
/* CMPLD2 Bit Fields */
#define TMR_CMPLD2_COMPARATOR_LOAD_2_MASK        0xFFFFu
#define TMR_CMPLD2_COMPARATOR_LOAD_2_SHIFT       0
#define TMR_CMPLD2_COMPARATOR_LOAD_2_WIDTH       16
#define TMR_CMPLD2_COMPARATOR_LOAD_2(x)          (((uint16_t)(((uint16_t)(x))<<TMR_CMPLD2_COMPARATOR_LOAD_2_SHIFT))&TMR_CMPLD2_COMPARATOR_LOAD_2_MASK)
/* CSCTRL Bit Fields */
#define TMR_CSCTRL_CL1_MASK                      0x3u
#define TMR_CSCTRL_CL1_SHIFT                     0
#define TMR_CSCTRL_CL1_WIDTH                     2
#define TMR_CSCTRL_CL1(x)                        (((uint16_t)(((uint16_t)(x))<<TMR_CSCTRL_CL1_SHIFT))&TMR_CSCTRL_CL1_MASK)
#define TMR_CSCTRL_CL2_MASK                      0xCu
#define TMR_CSCTRL_CL2_SHIFT                     2
#define TMR_CSCTRL_CL2_WIDTH                     2
#define TMR_CSCTRL_CL2(x)                        (((uint16_t)(((uint16_t)(x))<<TMR_CSCTRL_CL2_SHIFT))&TMR_CSCTRL_CL2_MASK)
#define TMR_CSCTRL_TCF1_MASK                     0x10u
#define TMR_CSCTRL_TCF1_SHIFT                    4
#define TMR_CSCTRL_TCF1_WIDTH                    1
#define TMR_CSCTRL_TCF1(x)                       (((uint16_t)(((uint16_t)(x))<<TMR_CSCTRL_TCF1_SHIFT))&TMR_CSCTRL_TCF1_MASK)
#define TMR_CSCTRL_TCF2_MASK                     0x20u
#define TMR_CSCTRL_TCF2_SHIFT                    5
#define TMR_CSCTRL_TCF2_WIDTH                    1
#define TMR_CSCTRL_TCF2(x)                       (((uint16_t)(((uint16_t)(x))<<TMR_CSCTRL_TCF2_SHIFT))&TMR_CSCTRL_TCF2_MASK)
#define TMR_CSCTRL_TCF1EN_MASK                   0x40u
#define TMR_CSCTRL_TCF1EN_SHIFT                  6
#define TMR_CSCTRL_TCF1EN_WIDTH                  1
#define TMR_CSCTRL_TCF1EN(x)                     (((uint16_t)(((uint16_t)(x))<<TMR_CSCTRL_TCF1EN_SHIFT))&TMR_CSCTRL_TCF1EN_MASK)
#define TMR_CSCTRL_TCF2EN_MASK                   0x80u
#define TMR_CSCTRL_TCF2EN_SHIFT                  7
#define TMR_CSCTRL_TCF2EN_WIDTH                  1
#define TMR_CSCTRL_TCF2EN(x)                     (((uint16_t)(((uint16_t)(x))<<TMR_CSCTRL_TCF2EN_SHIFT))&TMR_CSCTRL_TCF2EN_MASK)
#define TMR_CSCTRL_OFLAG_MASK                    0x100u
#define TMR_CSCTRL_OFLAG_SHIFT                   8
#define TMR_CSCTRL_OFLAG_WIDTH                   1
#define TMR_CSCTRL_OFLAG(x)                      (((uint16_t)(((uint16_t)(x))<<TMR_CSCTRL_OFLAG_SHIFT))&TMR_CSCTRL_OFLAG_MASK)
#define TMR_CSCTRL_UP_MASK                       0x200u
#define TMR_CSCTRL_UP_SHIFT                      9
#define TMR_CSCTRL_UP_WIDTH                      1
#define TMR_CSCTRL_UP(x)                         (((uint16_t)(((uint16_t)(x))<<TMR_CSCTRL_UP_SHIFT))&TMR_CSCTRL_UP_MASK)
#define TMR_CSCTRL_TCI_MASK                      0x400u
#define TMR_CSCTRL_TCI_SHIFT                     10
#define TMR_CSCTRL_TCI_WIDTH                     1
#define TMR_CSCTRL_TCI(x)                        (((uint16_t)(((uint16_t)(x))<<TMR_CSCTRL_TCI_SHIFT))&TMR_CSCTRL_TCI_MASK)
#define TMR_CSCTRL_ROC_MASK                      0x800u
#define TMR_CSCTRL_ROC_SHIFT                     11
#define TMR_CSCTRL_ROC_WIDTH                     1
#define TMR_CSCTRL_ROC(x)                        (((uint16_t)(((uint16_t)(x))<<TMR_CSCTRL_ROC_SHIFT))&TMR_CSCTRL_ROC_MASK)
#define TMR_CSCTRL_ALT_LOAD_MASK                 0x1000u
#define TMR_CSCTRL_ALT_LOAD_SHIFT                12
#define TMR_CSCTRL_ALT_LOAD_WIDTH                1
#define TMR_CSCTRL_ALT_LOAD(x)                   (((uint16_t)(((uint16_t)(x))<<TMR_CSCTRL_ALT_LOAD_SHIFT))&TMR_CSCTRL_ALT_LOAD_MASK)
#define TMR_CSCTRL_FAULT_MASK                    0x2000u
#define TMR_CSCTRL_FAULT_SHIFT                   13
#define TMR_CSCTRL_FAULT_WIDTH                   1
#define TMR_CSCTRL_FAULT(x)                      (((uint16_t)(((uint16_t)(x))<<TMR_CSCTRL_FAULT_SHIFT))&TMR_CSCTRL_FAULT_MASK)
#define TMR_CSCTRL_DBG_EN_MASK                   0xC000u
#define TMR_CSCTRL_DBG_EN_SHIFT                  14
#define TMR_CSCTRL_DBG_EN_WIDTH                  2
#define TMR_CSCTRL_DBG_EN(x)                     (((uint16_t)(((uint16_t)(x))<<TMR_CSCTRL_DBG_EN_SHIFT))&TMR_CSCTRL_DBG_EN_MASK)
/* FILT Bit Fields */
#define TMR_FILT_FILT_PER_MASK                   0xFFu
#define TMR_FILT_FILT_PER_SHIFT                  0
#define TMR_FILT_FILT_PER_WIDTH                  8
#define TMR_FILT_FILT_PER(x)                     (((uint16_t)(((uint16_t)(x))<<TMR_FILT_FILT_PER_SHIFT))&TMR_FILT_FILT_PER_MASK)
#define TMR_FILT_FILT_CNT_MASK                   0x700u
#define TMR_FILT_FILT_CNT_SHIFT                  8
#define TMR_FILT_FILT_CNT_WIDTH                  3
#define TMR_FILT_FILT_CNT(x)                     (((uint16_t)(((uint16_t)(x))<<TMR_FILT_FILT_CNT_SHIFT))&TMR_FILT_FILT_CNT_MASK)
/* ENBL Bit Fields */
#define TMR_ENBL_ENBL_MASK                       0xFu
#define TMR_ENBL_ENBL_SHIFT                      0
#define TMR_ENBL_ENBL_WIDTH                      4
#define TMR_ENBL_ENBL(x)                         (((uint16_t)(((uint16_t)(x))<<TMR_ENBL_ENBL_SHIFT))&TMR_ENBL_ENBL_MASK)

/*!
 * @}
 */ /* end of group TMR_Register_Masks */


/* TMR - Peripheral instance base addresses */
/** Peripheral TMR0 base address */
#define TMR0_BASE                                (0x40057000u)
/** Peripheral TMR0 base pointer */
#define TMR0                                     ((TMR_Type *)TMR0_BASE)
#define TMR0_BASE_PTR                            (TMR0)
/** Peripheral TMR1 base address */
#define TMR1_BASE                                (0x40058000u)
/** Peripheral TMR1 base pointer */
#define TMR1                                     ((TMR_Type *)TMR1_BASE)
#define TMR1_BASE_PTR                            (TMR1)
/** Peripheral TMR2 base address */
#define TMR2_BASE                                (0x40059000u)
/** Peripheral TMR2 base pointer */
#define TMR2                                     ((TMR_Type *)TMR2_BASE)
#define TMR2_BASE_PTR                            (TMR2)
/** Peripheral TMR3 base address */
#define TMR3_BASE                                (0x4005A000u)
/** Peripheral TMR3 base pointer */
#define TMR3                                     ((TMR_Type *)TMR3_BASE)
#define TMR3_BASE_PTR                            (TMR3)
/** Array initializer of TMR peripheral base addresses */
#define TMR_BASE_ADDRS                           { TMR0_BASE, TMR1_BASE, TMR2_BASE, TMR3_BASE }
/** Array initializer of TMR peripheral base pointers */
#define TMR_BASE_PTRS                            { TMR0, TMR1, TMR2, TMR3 }
/** Interrupt vectors for the TMR peripheral type */
#define TMR_IRQS                                 { TMR0_IRQn, TMR1_IRQn, TMR2_IRQn, TMR3_IRQn }

/* ----------------------------------------------------------------------------
   -- TMR - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TMR_Register_Accessor_Macros TMR - Register accessor macros
 * @{
 */


/* TMR - Register instance definitions */
/* TMR0 */
#define TMR0_COMP1                               TMR_COMP1_REG(TMR0)
#define TMR0_COMP2                               TMR_COMP2_REG(TMR0)
#define TMR0_CAPT                                TMR_CAPT_REG(TMR0)
#define TMR0_LOAD                                TMR_LOAD_REG(TMR0)
#define TMR0_HOLD                                TMR_HOLD_REG(TMR0)
#define TMR0_CNTR                                TMR_CNTR_REG(TMR0)
#define TMR0_CTRL                                TMR_CTRL_REG(TMR0)
#define TMR0_SCTRL                               TMR_SCTRL_REG(TMR0)
#define TMR0_CMPLD1                              TMR_CMPLD1_REG(TMR0)
#define TMR0_CMPLD2                              TMR_CMPLD2_REG(TMR0)
#define TMR0_CSCTRL                              TMR_CSCTRL_REG(TMR0)
#define TMR0_FILT                                TMR_FILT_REG(TMR0)
#define TMR0_ENBL                                TMR_ENBL_REG(TMR0)
/* TMR1 */
#define TMR1_COMP1                               TMR_COMP1_REG(TMR1)
#define TMR1_COMP2                               TMR_COMP2_REG(TMR1)
#define TMR1_CAPT                                TMR_CAPT_REG(TMR1)
#define TMR1_LOAD                                TMR_LOAD_REG(TMR1)
#define TMR1_HOLD                                TMR_HOLD_REG(TMR1)
#define TMR1_CNTR                                TMR_CNTR_REG(TMR1)
#define TMR1_CTRL                                TMR_CTRL_REG(TMR1)
#define TMR1_SCTRL                               TMR_SCTRL_REG(TMR1)
#define TMR1_CMPLD1                              TMR_CMPLD1_REG(TMR1)
#define TMR1_CMPLD2                              TMR_CMPLD2_REG(TMR1)
#define TMR1_CSCTRL                              TMR_CSCTRL_REG(TMR1)
#define TMR1_FILT                                TMR_FILT_REG(TMR1)
#define TMR1_ENBL                                TMR_ENBL_REG(TMR1)
/* TMR2 */
#define TMR2_COMP1                               TMR_COMP1_REG(TMR2)
#define TMR2_COMP2                               TMR_COMP2_REG(TMR2)
#define TMR2_CAPT                                TMR_CAPT_REG(TMR2)
#define TMR2_LOAD                                TMR_LOAD_REG(TMR2)
#define TMR2_HOLD                                TMR_HOLD_REG(TMR2)
#define TMR2_CNTR                                TMR_CNTR_REG(TMR2)
#define TMR2_CTRL                                TMR_CTRL_REG(TMR2)
#define TMR2_SCTRL                               TMR_SCTRL_REG(TMR2)
#define TMR2_CMPLD1                              TMR_CMPLD1_REG(TMR2)
#define TMR2_CMPLD2                              TMR_CMPLD2_REG(TMR2)
#define TMR2_CSCTRL                              TMR_CSCTRL_REG(TMR2)
#define TMR2_FILT                                TMR_FILT_REG(TMR2)
#define TMR2_ENBL                                TMR_ENBL_REG(TMR2)
/* TMR3 */
#define TMR3_COMP1                               TMR_COMP1_REG(TMR3)
#define TMR3_COMP2                               TMR_COMP2_REG(TMR3)
#define TMR3_CAPT                                TMR_CAPT_REG(TMR3)
#define TMR3_LOAD                                TMR_LOAD_REG(TMR3)
#define TMR3_HOLD                                TMR_HOLD_REG(TMR3)
#define TMR3_CNTR                                TMR_CNTR_REG(TMR3)
#define TMR3_CTRL                                TMR_CTRL_REG(TMR3)
#define TMR3_SCTRL                               TMR_SCTRL_REG(TMR3)
#define TMR3_CMPLD1                              TMR_CMPLD1_REG(TMR3)
#define TMR3_CMPLD2                              TMR_CMPLD2_REG(TMR3)
#define TMR3_CSCTRL                              TMR_CSCTRL_REG(TMR3)
#define TMR3_FILT                                TMR_FILT_REG(TMR3)
#define TMR3_ENBL                                TMR_ENBL_REG(TMR3)

/*!
 * @}
 */ /* end of group TMR_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group TMR_Peripheral_Access_Layer */


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
  __I  uint8_t ED;                                 /**< UART Extended Data Register, offset: 0xC */
  __IO uint8_t MODEM;                              /**< UART Modem Register, offset: 0xD */
       uint8_t RESERVED_0[2];
  __IO uint8_t PFIFO;                              /**< UART FIFO Parameters, offset: 0x10 */
  __IO uint8_t CFIFO;                              /**< UART FIFO Control Register, offset: 0x11 */
  __IO uint8_t SFIFO;                              /**< UART FIFO Status Register, offset: 0x12 */
  __IO uint8_t TWFIFO;                             /**< UART FIFO Transmit Watermark, offset: 0x13 */
  __I  uint8_t TCFIFO;                             /**< UART FIFO Transmit Count, offset: 0x14 */
  __IO uint8_t RWFIFO;                             /**< UART FIFO Receive Watermark, offset: 0x15 */
  __I  uint8_t RCFIFO;                             /**< UART FIFO Receive Count, offset: 0x16 */
       uint8_t RESERVED_1[1];
  __IO uint8_t C7816;                              /**< UART 7816 Control Register, offset: 0x18 */
  __IO uint8_t IE7816;                             /**< UART 7816 Interrupt Enable Register, offset: 0x19 */
  __IO uint8_t IS7816;                             /**< UART 7816 Interrupt Status Register, offset: 0x1A */
  __IO uint8_t WP7816;                             /**< UART 7816 Wait Parameter Register, offset: 0x1B */
  __IO uint8_t WN7816;                             /**< UART 7816 Wait N Register, offset: 0x1C */
  __IO uint8_t WF7816;                             /**< UART 7816 Wait FD Register, offset: 0x1D */
  __IO uint8_t ET7816;                             /**< UART 7816 Error Threshold Register, offset: 0x1E */
  __IO uint8_t TL7816;                             /**< UART 7816 Transmit Length Register, offset: 0x1F */
       uint8_t RESERVED_2[26];
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
} UART_Type, *UART_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- UART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Accessor_Macros UART - Register accessor macros
 * @{
 */


/* UART - Register accessors */
#define UART_BDH_REG(base)                       ((base)->BDH)
#define UART_BDL_REG(base)                       ((base)->BDL)
#define UART_C1_REG(base)                        ((base)->C1)
#define UART_C2_REG(base)                        ((base)->C2)
#define UART_S1_REG(base)                        ((base)->S1)
#define UART_S2_REG(base)                        ((base)->S2)
#define UART_C3_REG(base)                        ((base)->C3)
#define UART_D_REG(base)                         ((base)->D)
#define UART_MA1_REG(base)                       ((base)->MA1)
#define UART_MA2_REG(base)                       ((base)->MA2)
#define UART_C4_REG(base)                        ((base)->C4)
#define UART_C5_REG(base)                        ((base)->C5)
#define UART_ED_REG(base)                        ((base)->ED)
#define UART_MODEM_REG(base)                     ((base)->MODEM)
#define UART_PFIFO_REG(base)                     ((base)->PFIFO)
#define UART_CFIFO_REG(base)                     ((base)->CFIFO)
#define UART_SFIFO_REG(base)                     ((base)->SFIFO)
#define UART_TWFIFO_REG(base)                    ((base)->TWFIFO)
#define UART_TCFIFO_REG(base)                    ((base)->TCFIFO)
#define UART_RWFIFO_REG(base)                    ((base)->RWFIFO)
#define UART_RCFIFO_REG(base)                    ((base)->RCFIFO)
#define UART_C7816_REG(base)                     ((base)->C7816)
#define UART_IE7816_REG(base)                    ((base)->IE7816)
#define UART_IS7816_REG(base)                    ((base)->IS7816)
#define UART_WP7816_REG(base)                    ((base)->WP7816)
#define UART_WN7816_REG(base)                    ((base)->WN7816)
#define UART_WF7816_REG(base)                    ((base)->WF7816)
#define UART_ET7816_REG(base)                    ((base)->ET7816)
#define UART_TL7816_REG(base)                    ((base)->TL7816)
#define UART_AP7816A_T0_REG(base)                ((base)->AP7816A_T0)
#define UART_AP7816B_T0_REG(base)                ((base)->AP7816B_T0)
#define UART_WP7816A_T0_REG(base)                ((base)->TYPE0.WP7816A_T0)
#define UART_WP7816B_T0_REG(base)                ((base)->TYPE0.WP7816B_T0)
#define UART_WP7816A_T1_REG(base)                ((base)->TYPE1.WP7816A_T1)
#define UART_WP7816B_T1_REG(base)                ((base)->TYPE1.WP7816B_T1)
#define UART_WGP7816_T1_REG(base)                ((base)->WGP7816_T1)
#define UART_WP7816C_T1_REG(base)                ((base)->WP7816C_T1)

/*!
 * @}
 */ /* end of group UART_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- UART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Masks UART Register Masks
 * @{
 */

/* BDH Bit Fields */
#define UART_BDH_SBR_MASK                        0x1Fu
#define UART_BDH_SBR_SHIFT                       0
#define UART_BDH_SBR_WIDTH                       5
#define UART_BDH_SBR(x)                          (((uint8_t)(((uint8_t)(x))<<UART_BDH_SBR_SHIFT))&UART_BDH_SBR_MASK)
#define UART_BDH_RXEDGIE_MASK                    0x40u
#define UART_BDH_RXEDGIE_SHIFT                   6
#define UART_BDH_RXEDGIE_WIDTH                   1
#define UART_BDH_RXEDGIE(x)                      (((uint8_t)(((uint8_t)(x))<<UART_BDH_RXEDGIE_SHIFT))&UART_BDH_RXEDGIE_MASK)
/* BDL Bit Fields */
#define UART_BDL_SBR_MASK                        0xFFu
#define UART_BDL_SBR_SHIFT                       0
#define UART_BDL_SBR_WIDTH                       8
#define UART_BDL_SBR(x)                          (((uint8_t)(((uint8_t)(x))<<UART_BDL_SBR_SHIFT))&UART_BDL_SBR_MASK)
/* C1 Bit Fields */
#define UART_C1_PT_MASK                          0x1u
#define UART_C1_PT_SHIFT                         0
#define UART_C1_PT_WIDTH                         1
#define UART_C1_PT(x)                            (((uint8_t)(((uint8_t)(x))<<UART_C1_PT_SHIFT))&UART_C1_PT_MASK)
#define UART_C1_PE_MASK                          0x2u
#define UART_C1_PE_SHIFT                         1
#define UART_C1_PE_WIDTH                         1
#define UART_C1_PE(x)                            (((uint8_t)(((uint8_t)(x))<<UART_C1_PE_SHIFT))&UART_C1_PE_MASK)
#define UART_C1_ILT_MASK                         0x4u
#define UART_C1_ILT_SHIFT                        2
#define UART_C1_ILT_WIDTH                        1
#define UART_C1_ILT(x)                           (((uint8_t)(((uint8_t)(x))<<UART_C1_ILT_SHIFT))&UART_C1_ILT_MASK)
#define UART_C1_WAKE_MASK                        0x8u
#define UART_C1_WAKE_SHIFT                       3
#define UART_C1_WAKE_WIDTH                       1
#define UART_C1_WAKE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C1_WAKE_SHIFT))&UART_C1_WAKE_MASK)
#define UART_C1_M_MASK                           0x10u
#define UART_C1_M_SHIFT                          4
#define UART_C1_M_WIDTH                          1
#define UART_C1_M(x)                             (((uint8_t)(((uint8_t)(x))<<UART_C1_M_SHIFT))&UART_C1_M_MASK)
#define UART_C1_RSRC_MASK                        0x20u
#define UART_C1_RSRC_SHIFT                       5
#define UART_C1_RSRC_WIDTH                       1
#define UART_C1_RSRC(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C1_RSRC_SHIFT))&UART_C1_RSRC_MASK)
#define UART_C1_LOOPS_MASK                       0x80u
#define UART_C1_LOOPS_SHIFT                      7
#define UART_C1_LOOPS_WIDTH                      1
#define UART_C1_LOOPS(x)                         (((uint8_t)(((uint8_t)(x))<<UART_C1_LOOPS_SHIFT))&UART_C1_LOOPS_MASK)
/* C2 Bit Fields */
#define UART_C2_SBK_MASK                         0x1u
#define UART_C2_SBK_SHIFT                        0
#define UART_C2_SBK_WIDTH                        1
#define UART_C2_SBK(x)                           (((uint8_t)(((uint8_t)(x))<<UART_C2_SBK_SHIFT))&UART_C2_SBK_MASK)
#define UART_C2_RWU_MASK                         0x2u
#define UART_C2_RWU_SHIFT                        1
#define UART_C2_RWU_WIDTH                        1
#define UART_C2_RWU(x)                           (((uint8_t)(((uint8_t)(x))<<UART_C2_RWU_SHIFT))&UART_C2_RWU_MASK)
#define UART_C2_RE_MASK                          0x4u
#define UART_C2_RE_SHIFT                         2
#define UART_C2_RE_WIDTH                         1
#define UART_C2_RE(x)                            (((uint8_t)(((uint8_t)(x))<<UART_C2_RE_SHIFT))&UART_C2_RE_MASK)
#define UART_C2_TE_MASK                          0x8u
#define UART_C2_TE_SHIFT                         3
#define UART_C2_TE_WIDTH                         1
#define UART_C2_TE(x)                            (((uint8_t)(((uint8_t)(x))<<UART_C2_TE_SHIFT))&UART_C2_TE_MASK)
#define UART_C2_ILIE_MASK                        0x10u
#define UART_C2_ILIE_SHIFT                       4
#define UART_C2_ILIE_WIDTH                       1
#define UART_C2_ILIE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C2_ILIE_SHIFT))&UART_C2_ILIE_MASK)
#define UART_C2_RIE_MASK                         0x20u
#define UART_C2_RIE_SHIFT                        5
#define UART_C2_RIE_WIDTH                        1
#define UART_C2_RIE(x)                           (((uint8_t)(((uint8_t)(x))<<UART_C2_RIE_SHIFT))&UART_C2_RIE_MASK)
#define UART_C2_TCIE_MASK                        0x40u
#define UART_C2_TCIE_SHIFT                       6
#define UART_C2_TCIE_WIDTH                       1
#define UART_C2_TCIE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C2_TCIE_SHIFT))&UART_C2_TCIE_MASK)
#define UART_C2_TIE_MASK                         0x80u
#define UART_C2_TIE_SHIFT                        7
#define UART_C2_TIE_WIDTH                        1
#define UART_C2_TIE(x)                           (((uint8_t)(((uint8_t)(x))<<UART_C2_TIE_SHIFT))&UART_C2_TIE_MASK)
/* S1 Bit Fields */
#define UART_S1_PF_MASK                          0x1u
#define UART_S1_PF_SHIFT                         0
#define UART_S1_PF_WIDTH                         1
#define UART_S1_PF(x)                            (((uint8_t)(((uint8_t)(x))<<UART_S1_PF_SHIFT))&UART_S1_PF_MASK)
#define UART_S1_FE_MASK                          0x2u
#define UART_S1_FE_SHIFT                         1
#define UART_S1_FE_WIDTH                         1
#define UART_S1_FE(x)                            (((uint8_t)(((uint8_t)(x))<<UART_S1_FE_SHIFT))&UART_S1_FE_MASK)
#define UART_S1_NF_MASK                          0x4u
#define UART_S1_NF_SHIFT                         2
#define UART_S1_NF_WIDTH                         1
#define UART_S1_NF(x)                            (((uint8_t)(((uint8_t)(x))<<UART_S1_NF_SHIFT))&UART_S1_NF_MASK)
#define UART_S1_OR_MASK                          0x8u
#define UART_S1_OR_SHIFT                         3
#define UART_S1_OR_WIDTH                         1
#define UART_S1_OR(x)                            (((uint8_t)(((uint8_t)(x))<<UART_S1_OR_SHIFT))&UART_S1_OR_MASK)
#define UART_S1_IDLE_MASK                        0x10u
#define UART_S1_IDLE_SHIFT                       4
#define UART_S1_IDLE_WIDTH                       1
#define UART_S1_IDLE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_S1_IDLE_SHIFT))&UART_S1_IDLE_MASK)
#define UART_S1_RDRF_MASK                        0x20u
#define UART_S1_RDRF_SHIFT                       5
#define UART_S1_RDRF_WIDTH                       1
#define UART_S1_RDRF(x)                          (((uint8_t)(((uint8_t)(x))<<UART_S1_RDRF_SHIFT))&UART_S1_RDRF_MASK)
#define UART_S1_TC_MASK                          0x40u
#define UART_S1_TC_SHIFT                         6
#define UART_S1_TC_WIDTH                         1
#define UART_S1_TC(x)                            (((uint8_t)(((uint8_t)(x))<<UART_S1_TC_SHIFT))&UART_S1_TC_MASK)
#define UART_S1_TDRE_MASK                        0x80u
#define UART_S1_TDRE_SHIFT                       7
#define UART_S1_TDRE_WIDTH                       1
#define UART_S1_TDRE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_S1_TDRE_SHIFT))&UART_S1_TDRE_MASK)
/* S2 Bit Fields */
#define UART_S2_RAF_MASK                         0x1u
#define UART_S2_RAF_SHIFT                        0
#define UART_S2_RAF_WIDTH                        1
#define UART_S2_RAF(x)                           (((uint8_t)(((uint8_t)(x))<<UART_S2_RAF_SHIFT))&UART_S2_RAF_MASK)
#define UART_S2_BRK13_MASK                       0x4u
#define UART_S2_BRK13_SHIFT                      2
#define UART_S2_BRK13_WIDTH                      1
#define UART_S2_BRK13(x)                         (((uint8_t)(((uint8_t)(x))<<UART_S2_BRK13_SHIFT))&UART_S2_BRK13_MASK)
#define UART_S2_RWUID_MASK                       0x8u
#define UART_S2_RWUID_SHIFT                      3
#define UART_S2_RWUID_WIDTH                      1
#define UART_S2_RWUID(x)                         (((uint8_t)(((uint8_t)(x))<<UART_S2_RWUID_SHIFT))&UART_S2_RWUID_MASK)
#define UART_S2_RXINV_MASK                       0x10u
#define UART_S2_RXINV_SHIFT                      4
#define UART_S2_RXINV_WIDTH                      1
#define UART_S2_RXINV(x)                         (((uint8_t)(((uint8_t)(x))<<UART_S2_RXINV_SHIFT))&UART_S2_RXINV_MASK)
#define UART_S2_MSBF_MASK                        0x20u
#define UART_S2_MSBF_SHIFT                       5
#define UART_S2_MSBF_WIDTH                       1
#define UART_S2_MSBF(x)                          (((uint8_t)(((uint8_t)(x))<<UART_S2_MSBF_SHIFT))&UART_S2_MSBF_MASK)
#define UART_S2_RXEDGIF_MASK                     0x40u
#define UART_S2_RXEDGIF_SHIFT                    6
#define UART_S2_RXEDGIF_WIDTH                    1
#define UART_S2_RXEDGIF(x)                       (((uint8_t)(((uint8_t)(x))<<UART_S2_RXEDGIF_SHIFT))&UART_S2_RXEDGIF_MASK)
/* C3 Bit Fields */
#define UART_C3_PEIE_MASK                        0x1u
#define UART_C3_PEIE_SHIFT                       0
#define UART_C3_PEIE_WIDTH                       1
#define UART_C3_PEIE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C3_PEIE_SHIFT))&UART_C3_PEIE_MASK)
#define UART_C3_FEIE_MASK                        0x2u
#define UART_C3_FEIE_SHIFT                       1
#define UART_C3_FEIE_WIDTH                       1
#define UART_C3_FEIE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C3_FEIE_SHIFT))&UART_C3_FEIE_MASK)
#define UART_C3_NEIE_MASK                        0x4u
#define UART_C3_NEIE_SHIFT                       2
#define UART_C3_NEIE_WIDTH                       1
#define UART_C3_NEIE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C3_NEIE_SHIFT))&UART_C3_NEIE_MASK)
#define UART_C3_ORIE_MASK                        0x8u
#define UART_C3_ORIE_SHIFT                       3
#define UART_C3_ORIE_WIDTH                       1
#define UART_C3_ORIE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C3_ORIE_SHIFT))&UART_C3_ORIE_MASK)
#define UART_C3_TXINV_MASK                       0x10u
#define UART_C3_TXINV_SHIFT                      4
#define UART_C3_TXINV_WIDTH                      1
#define UART_C3_TXINV(x)                         (((uint8_t)(((uint8_t)(x))<<UART_C3_TXINV_SHIFT))&UART_C3_TXINV_MASK)
#define UART_C3_TXDIR_MASK                       0x20u
#define UART_C3_TXDIR_SHIFT                      5
#define UART_C3_TXDIR_WIDTH                      1
#define UART_C3_TXDIR(x)                         (((uint8_t)(((uint8_t)(x))<<UART_C3_TXDIR_SHIFT))&UART_C3_TXDIR_MASK)
#define UART_C3_T8_MASK                          0x40u
#define UART_C3_T8_SHIFT                         6
#define UART_C3_T8_WIDTH                         1
#define UART_C3_T8(x)                            (((uint8_t)(((uint8_t)(x))<<UART_C3_T8_SHIFT))&UART_C3_T8_MASK)
#define UART_C3_R8_MASK                          0x80u
#define UART_C3_R8_SHIFT                         7
#define UART_C3_R8_WIDTH                         1
#define UART_C3_R8(x)                            (((uint8_t)(((uint8_t)(x))<<UART_C3_R8_SHIFT))&UART_C3_R8_MASK)
/* D Bit Fields */
#define UART_D_RT_MASK                           0xFFu
#define UART_D_RT_SHIFT                          0
#define UART_D_RT_WIDTH                          8
#define UART_D_RT(x)                             (((uint8_t)(((uint8_t)(x))<<UART_D_RT_SHIFT))&UART_D_RT_MASK)
/* MA1 Bit Fields */
#define UART_MA1_MA_MASK                         0xFFu
#define UART_MA1_MA_SHIFT                        0
#define UART_MA1_MA_WIDTH                        8
#define UART_MA1_MA(x)                           (((uint8_t)(((uint8_t)(x))<<UART_MA1_MA_SHIFT))&UART_MA1_MA_MASK)
/* MA2 Bit Fields */
#define UART_MA2_MA_MASK                         0xFFu
#define UART_MA2_MA_SHIFT                        0
#define UART_MA2_MA_WIDTH                        8
#define UART_MA2_MA(x)                           (((uint8_t)(((uint8_t)(x))<<UART_MA2_MA_SHIFT))&UART_MA2_MA_MASK)
/* C4 Bit Fields */
#define UART_C4_BRFA_MASK                        0x1Fu
#define UART_C4_BRFA_SHIFT                       0
#define UART_C4_BRFA_WIDTH                       5
#define UART_C4_BRFA(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C4_BRFA_SHIFT))&UART_C4_BRFA_MASK)
#define UART_C4_M10_MASK                         0x20u
#define UART_C4_M10_SHIFT                        5
#define UART_C4_M10_WIDTH                        1
#define UART_C4_M10(x)                           (((uint8_t)(((uint8_t)(x))<<UART_C4_M10_SHIFT))&UART_C4_M10_MASK)
#define UART_C4_MAEN2_MASK                       0x40u
#define UART_C4_MAEN2_SHIFT                      6
#define UART_C4_MAEN2_WIDTH                      1
#define UART_C4_MAEN2(x)                         (((uint8_t)(((uint8_t)(x))<<UART_C4_MAEN2_SHIFT))&UART_C4_MAEN2_MASK)
#define UART_C4_MAEN1_MASK                       0x80u
#define UART_C4_MAEN1_SHIFT                      7
#define UART_C4_MAEN1_WIDTH                      1
#define UART_C4_MAEN1(x)                         (((uint8_t)(((uint8_t)(x))<<UART_C4_MAEN1_SHIFT))&UART_C4_MAEN1_MASK)
/* C5 Bit Fields */
#define UART_C5_ILDMAS_MASK                      0x10u
#define UART_C5_ILDMAS_SHIFT                     4
#define UART_C5_ILDMAS_WIDTH                     1
#define UART_C5_ILDMAS(x)                        (((uint8_t)(((uint8_t)(x))<<UART_C5_ILDMAS_SHIFT))&UART_C5_ILDMAS_MASK)
#define UART_C5_RDMAS_MASK                       0x20u
#define UART_C5_RDMAS_SHIFT                      5
#define UART_C5_RDMAS_WIDTH                      1
#define UART_C5_RDMAS(x)                         (((uint8_t)(((uint8_t)(x))<<UART_C5_RDMAS_SHIFT))&UART_C5_RDMAS_MASK)
#define UART_C5_TDMAS_MASK                       0x80u
#define UART_C5_TDMAS_SHIFT                      7
#define UART_C5_TDMAS_WIDTH                      1
#define UART_C5_TDMAS(x)                         (((uint8_t)(((uint8_t)(x))<<UART_C5_TDMAS_SHIFT))&UART_C5_TDMAS_MASK)
/* ED Bit Fields */
#define UART_ED_PARITYE_MASK                     0x40u
#define UART_ED_PARITYE_SHIFT                    6
#define UART_ED_PARITYE_WIDTH                    1
#define UART_ED_PARITYE(x)                       (((uint8_t)(((uint8_t)(x))<<UART_ED_PARITYE_SHIFT))&UART_ED_PARITYE_MASK)
#define UART_ED_NOISY_MASK                       0x80u
#define UART_ED_NOISY_SHIFT                      7
#define UART_ED_NOISY_WIDTH                      1
#define UART_ED_NOISY(x)                         (((uint8_t)(((uint8_t)(x))<<UART_ED_NOISY_SHIFT))&UART_ED_NOISY_MASK)
/* MODEM Bit Fields */
#define UART_MODEM_TXCTSE_MASK                   0x1u
#define UART_MODEM_TXCTSE_SHIFT                  0
#define UART_MODEM_TXCTSE_WIDTH                  1
#define UART_MODEM_TXCTSE(x)                     (((uint8_t)(((uint8_t)(x))<<UART_MODEM_TXCTSE_SHIFT))&UART_MODEM_TXCTSE_MASK)
#define UART_MODEM_TXRTSE_MASK                   0x2u
#define UART_MODEM_TXRTSE_SHIFT                  1
#define UART_MODEM_TXRTSE_WIDTH                  1
#define UART_MODEM_TXRTSE(x)                     (((uint8_t)(((uint8_t)(x))<<UART_MODEM_TXRTSE_SHIFT))&UART_MODEM_TXRTSE_MASK)
#define UART_MODEM_TXRTSPOL_MASK                 0x4u
#define UART_MODEM_TXRTSPOL_SHIFT                2
#define UART_MODEM_TXRTSPOL_WIDTH                1
#define UART_MODEM_TXRTSPOL(x)                   (((uint8_t)(((uint8_t)(x))<<UART_MODEM_TXRTSPOL_SHIFT))&UART_MODEM_TXRTSPOL_MASK)
#define UART_MODEM_RXRTSE_MASK                   0x8u
#define UART_MODEM_RXRTSE_SHIFT                  3
#define UART_MODEM_RXRTSE_WIDTH                  1
#define UART_MODEM_RXRTSE(x)                     (((uint8_t)(((uint8_t)(x))<<UART_MODEM_RXRTSE_SHIFT))&UART_MODEM_RXRTSE_MASK)
/* PFIFO Bit Fields */
#define UART_PFIFO_RXFIFOSIZE_MASK               0x7u
#define UART_PFIFO_RXFIFOSIZE_SHIFT              0
#define UART_PFIFO_RXFIFOSIZE_WIDTH              3
#define UART_PFIFO_RXFIFOSIZE(x)                 (((uint8_t)(((uint8_t)(x))<<UART_PFIFO_RXFIFOSIZE_SHIFT))&UART_PFIFO_RXFIFOSIZE_MASK)
#define UART_PFIFO_RXFE_MASK                     0x8u
#define UART_PFIFO_RXFE_SHIFT                    3
#define UART_PFIFO_RXFE_WIDTH                    1
#define UART_PFIFO_RXFE(x)                       (((uint8_t)(((uint8_t)(x))<<UART_PFIFO_RXFE_SHIFT))&UART_PFIFO_RXFE_MASK)
#define UART_PFIFO_TXFIFOSIZE_MASK               0x70u
#define UART_PFIFO_TXFIFOSIZE_SHIFT              4
#define UART_PFIFO_TXFIFOSIZE_WIDTH              3
#define UART_PFIFO_TXFIFOSIZE(x)                 (((uint8_t)(((uint8_t)(x))<<UART_PFIFO_TXFIFOSIZE_SHIFT))&UART_PFIFO_TXFIFOSIZE_MASK)
#define UART_PFIFO_TXFE_MASK                     0x80u
#define UART_PFIFO_TXFE_SHIFT                    7
#define UART_PFIFO_TXFE_WIDTH                    1
#define UART_PFIFO_TXFE(x)                       (((uint8_t)(((uint8_t)(x))<<UART_PFIFO_TXFE_SHIFT))&UART_PFIFO_TXFE_MASK)
/* CFIFO Bit Fields */
#define UART_CFIFO_RXUFE_MASK                    0x1u
#define UART_CFIFO_RXUFE_SHIFT                   0
#define UART_CFIFO_RXUFE_WIDTH                   1
#define UART_CFIFO_RXUFE(x)                      (((uint8_t)(((uint8_t)(x))<<UART_CFIFO_RXUFE_SHIFT))&UART_CFIFO_RXUFE_MASK)
#define UART_CFIFO_TXOFE_MASK                    0x2u
#define UART_CFIFO_TXOFE_SHIFT                   1
#define UART_CFIFO_TXOFE_WIDTH                   1
#define UART_CFIFO_TXOFE(x)                      (((uint8_t)(((uint8_t)(x))<<UART_CFIFO_TXOFE_SHIFT))&UART_CFIFO_TXOFE_MASK)
#define UART_CFIFO_RXOFE_MASK                    0x4u
#define UART_CFIFO_RXOFE_SHIFT                   2
#define UART_CFIFO_RXOFE_WIDTH                   1
#define UART_CFIFO_RXOFE(x)                      (((uint8_t)(((uint8_t)(x))<<UART_CFIFO_RXOFE_SHIFT))&UART_CFIFO_RXOFE_MASK)
#define UART_CFIFO_RXFLUSH_MASK                  0x40u
#define UART_CFIFO_RXFLUSH_SHIFT                 6
#define UART_CFIFO_RXFLUSH_WIDTH                 1
#define UART_CFIFO_RXFLUSH(x)                    (((uint8_t)(((uint8_t)(x))<<UART_CFIFO_RXFLUSH_SHIFT))&UART_CFIFO_RXFLUSH_MASK)
#define UART_CFIFO_TXFLUSH_MASK                  0x80u
#define UART_CFIFO_TXFLUSH_SHIFT                 7
#define UART_CFIFO_TXFLUSH_WIDTH                 1
#define UART_CFIFO_TXFLUSH(x)                    (((uint8_t)(((uint8_t)(x))<<UART_CFIFO_TXFLUSH_SHIFT))&UART_CFIFO_TXFLUSH_MASK)
/* SFIFO Bit Fields */
#define UART_SFIFO_RXUF_MASK                     0x1u
#define UART_SFIFO_RXUF_SHIFT                    0
#define UART_SFIFO_RXUF_WIDTH                    1
#define UART_SFIFO_RXUF(x)                       (((uint8_t)(((uint8_t)(x))<<UART_SFIFO_RXUF_SHIFT))&UART_SFIFO_RXUF_MASK)
#define UART_SFIFO_TXOF_MASK                     0x2u
#define UART_SFIFO_TXOF_SHIFT                    1
#define UART_SFIFO_TXOF_WIDTH                    1
#define UART_SFIFO_TXOF(x)                       (((uint8_t)(((uint8_t)(x))<<UART_SFIFO_TXOF_SHIFT))&UART_SFIFO_TXOF_MASK)
#define UART_SFIFO_RXOF_MASK                     0x4u
#define UART_SFIFO_RXOF_SHIFT                    2
#define UART_SFIFO_RXOF_WIDTH                    1
#define UART_SFIFO_RXOF(x)                       (((uint8_t)(((uint8_t)(x))<<UART_SFIFO_RXOF_SHIFT))&UART_SFIFO_RXOF_MASK)
#define UART_SFIFO_RXEMPT_MASK                   0x40u
#define UART_SFIFO_RXEMPT_SHIFT                  6
#define UART_SFIFO_RXEMPT_WIDTH                  1
#define UART_SFIFO_RXEMPT(x)                     (((uint8_t)(((uint8_t)(x))<<UART_SFIFO_RXEMPT_SHIFT))&UART_SFIFO_RXEMPT_MASK)
#define UART_SFIFO_TXEMPT_MASK                   0x80u
#define UART_SFIFO_TXEMPT_SHIFT                  7
#define UART_SFIFO_TXEMPT_WIDTH                  1
#define UART_SFIFO_TXEMPT(x)                     (((uint8_t)(((uint8_t)(x))<<UART_SFIFO_TXEMPT_SHIFT))&UART_SFIFO_TXEMPT_MASK)
/* TWFIFO Bit Fields */
#define UART_TWFIFO_TXWATER_MASK                 0xFFu
#define UART_TWFIFO_TXWATER_SHIFT                0
#define UART_TWFIFO_TXWATER_WIDTH                8
#define UART_TWFIFO_TXWATER(x)                   (((uint8_t)(((uint8_t)(x))<<UART_TWFIFO_TXWATER_SHIFT))&UART_TWFIFO_TXWATER_MASK)
/* TCFIFO Bit Fields */
#define UART_TCFIFO_TXCOUNT_MASK                 0xFFu
#define UART_TCFIFO_TXCOUNT_SHIFT                0
#define UART_TCFIFO_TXCOUNT_WIDTH                8
#define UART_TCFIFO_TXCOUNT(x)                   (((uint8_t)(((uint8_t)(x))<<UART_TCFIFO_TXCOUNT_SHIFT))&UART_TCFIFO_TXCOUNT_MASK)
/* RWFIFO Bit Fields */
#define UART_RWFIFO_RXWATER_MASK                 0xFFu
#define UART_RWFIFO_RXWATER_SHIFT                0
#define UART_RWFIFO_RXWATER_WIDTH                8
#define UART_RWFIFO_RXWATER(x)                   (((uint8_t)(((uint8_t)(x))<<UART_RWFIFO_RXWATER_SHIFT))&UART_RWFIFO_RXWATER_MASK)
/* RCFIFO Bit Fields */
#define UART_RCFIFO_RXCOUNT_MASK                 0xFFu
#define UART_RCFIFO_RXCOUNT_SHIFT                0
#define UART_RCFIFO_RXCOUNT_WIDTH                8
#define UART_RCFIFO_RXCOUNT(x)                   (((uint8_t)(((uint8_t)(x))<<UART_RCFIFO_RXCOUNT_SHIFT))&UART_RCFIFO_RXCOUNT_MASK)
/* C7816 Bit Fields */
#define UART_C7816_ISO_7816E_MASK                0x1u
#define UART_C7816_ISO_7816E_SHIFT               0
#define UART_C7816_ISO_7816E_WIDTH               1
#define UART_C7816_ISO_7816E(x)                  (((uint8_t)(((uint8_t)(x))<<UART_C7816_ISO_7816E_SHIFT))&UART_C7816_ISO_7816E_MASK)
#define UART_C7816_TTYPE_MASK                    0x2u
#define UART_C7816_TTYPE_SHIFT                   1
#define UART_C7816_TTYPE_WIDTH                   1
#define UART_C7816_TTYPE(x)                      (((uint8_t)(((uint8_t)(x))<<UART_C7816_TTYPE_SHIFT))&UART_C7816_TTYPE_MASK)
#define UART_C7816_INIT_MASK                     0x4u
#define UART_C7816_INIT_SHIFT                    2
#define UART_C7816_INIT_WIDTH                    1
#define UART_C7816_INIT(x)                       (((uint8_t)(((uint8_t)(x))<<UART_C7816_INIT_SHIFT))&UART_C7816_INIT_MASK)
#define UART_C7816_ANACK_MASK                    0x8u
#define UART_C7816_ANACK_SHIFT                   3
#define UART_C7816_ANACK_WIDTH                   1
#define UART_C7816_ANACK(x)                      (((uint8_t)(((uint8_t)(x))<<UART_C7816_ANACK_SHIFT))&UART_C7816_ANACK_MASK)
#define UART_C7816_ONACK_MASK                    0x10u
#define UART_C7816_ONACK_SHIFT                   4
#define UART_C7816_ONACK_WIDTH                   1
#define UART_C7816_ONACK(x)                      (((uint8_t)(((uint8_t)(x))<<UART_C7816_ONACK_SHIFT))&UART_C7816_ONACK_MASK)
/* IE7816 Bit Fields */
#define UART_IE7816_RXTE_MASK                    0x1u
#define UART_IE7816_RXTE_SHIFT                   0
#define UART_IE7816_RXTE_WIDTH                   1
#define UART_IE7816_RXTE(x)                      (((uint8_t)(((uint8_t)(x))<<UART_IE7816_RXTE_SHIFT))&UART_IE7816_RXTE_MASK)
#define UART_IE7816_TXTE_MASK                    0x2u
#define UART_IE7816_TXTE_SHIFT                   1
#define UART_IE7816_TXTE_WIDTH                   1
#define UART_IE7816_TXTE(x)                      (((uint8_t)(((uint8_t)(x))<<UART_IE7816_TXTE_SHIFT))&UART_IE7816_TXTE_MASK)
#define UART_IE7816_GTVE_MASK                    0x4u
#define UART_IE7816_GTVE_SHIFT                   2
#define UART_IE7816_GTVE_WIDTH                   1
#define UART_IE7816_GTVE(x)                      (((uint8_t)(((uint8_t)(x))<<UART_IE7816_GTVE_SHIFT))&UART_IE7816_GTVE_MASK)
#define UART_IE7816_ADTE_MASK                    0x8u
#define UART_IE7816_ADTE_SHIFT                   3
#define UART_IE7816_ADTE_WIDTH                   1
#define UART_IE7816_ADTE(x)                      (((uint8_t)(((uint8_t)(x))<<UART_IE7816_ADTE_SHIFT))&UART_IE7816_ADTE_MASK)
#define UART_IE7816_INITDE_MASK                  0x10u
#define UART_IE7816_INITDE_SHIFT                 4
#define UART_IE7816_INITDE_WIDTH                 1
#define UART_IE7816_INITDE(x)                    (((uint8_t)(((uint8_t)(x))<<UART_IE7816_INITDE_SHIFT))&UART_IE7816_INITDE_MASK)
#define UART_IE7816_BWTE_MASK                    0x20u
#define UART_IE7816_BWTE_SHIFT                   5
#define UART_IE7816_BWTE_WIDTH                   1
#define UART_IE7816_BWTE(x)                      (((uint8_t)(((uint8_t)(x))<<UART_IE7816_BWTE_SHIFT))&UART_IE7816_BWTE_MASK)
#define UART_IE7816_CWTE_MASK                    0x40u
#define UART_IE7816_CWTE_SHIFT                   6
#define UART_IE7816_CWTE_WIDTH                   1
#define UART_IE7816_CWTE(x)                      (((uint8_t)(((uint8_t)(x))<<UART_IE7816_CWTE_SHIFT))&UART_IE7816_CWTE_MASK)
#define UART_IE7816_WTE_MASK                     0x80u
#define UART_IE7816_WTE_SHIFT                    7
#define UART_IE7816_WTE_WIDTH                    1
#define UART_IE7816_WTE(x)                       (((uint8_t)(((uint8_t)(x))<<UART_IE7816_WTE_SHIFT))&UART_IE7816_WTE_MASK)
/* IS7816 Bit Fields */
#define UART_IS7816_RXT_MASK                     0x1u
#define UART_IS7816_RXT_SHIFT                    0
#define UART_IS7816_RXT_WIDTH                    1
#define UART_IS7816_RXT(x)                       (((uint8_t)(((uint8_t)(x))<<UART_IS7816_RXT_SHIFT))&UART_IS7816_RXT_MASK)
#define UART_IS7816_TXT_MASK                     0x2u
#define UART_IS7816_TXT_SHIFT                    1
#define UART_IS7816_TXT_WIDTH                    1
#define UART_IS7816_TXT(x)                       (((uint8_t)(((uint8_t)(x))<<UART_IS7816_TXT_SHIFT))&UART_IS7816_TXT_MASK)
#define UART_IS7816_GTV_MASK                     0x4u
#define UART_IS7816_GTV_SHIFT                    2
#define UART_IS7816_GTV_WIDTH                    1
#define UART_IS7816_GTV(x)                       (((uint8_t)(((uint8_t)(x))<<UART_IS7816_GTV_SHIFT))&UART_IS7816_GTV_MASK)
#define UART_IS7816_ADT_MASK                     0x8u
#define UART_IS7816_ADT_SHIFT                    3
#define UART_IS7816_ADT_WIDTH                    1
#define UART_IS7816_ADT(x)                       (((uint8_t)(((uint8_t)(x))<<UART_IS7816_ADT_SHIFT))&UART_IS7816_ADT_MASK)
#define UART_IS7816_INITD_MASK                   0x10u
#define UART_IS7816_INITD_SHIFT                  4
#define UART_IS7816_INITD_WIDTH                  1
#define UART_IS7816_INITD(x)                     (((uint8_t)(((uint8_t)(x))<<UART_IS7816_INITD_SHIFT))&UART_IS7816_INITD_MASK)
#define UART_IS7816_BWT_MASK                     0x20u
#define UART_IS7816_BWT_SHIFT                    5
#define UART_IS7816_BWT_WIDTH                    1
#define UART_IS7816_BWT(x)                       (((uint8_t)(((uint8_t)(x))<<UART_IS7816_BWT_SHIFT))&UART_IS7816_BWT_MASK)
#define UART_IS7816_CWT_MASK                     0x40u
#define UART_IS7816_CWT_SHIFT                    6
#define UART_IS7816_CWT_WIDTH                    1
#define UART_IS7816_CWT(x)                       (((uint8_t)(((uint8_t)(x))<<UART_IS7816_CWT_SHIFT))&UART_IS7816_CWT_MASK)
#define UART_IS7816_WT_MASK                      0x80u
#define UART_IS7816_WT_SHIFT                     7
#define UART_IS7816_WT_WIDTH                     1
#define UART_IS7816_WT(x)                        (((uint8_t)(((uint8_t)(x))<<UART_IS7816_WT_SHIFT))&UART_IS7816_WT_MASK)
/* WP7816 Bit Fields */
#define UART_WP7816_WTX_MASK                     0xFFu
#define UART_WP7816_WTX_SHIFT                    0
#define UART_WP7816_WTX_WIDTH                    8
#define UART_WP7816_WTX(x)                       (((uint8_t)(((uint8_t)(x))<<UART_WP7816_WTX_SHIFT))&UART_WP7816_WTX_MASK)
/* WN7816 Bit Fields */
#define UART_WN7816_GTN_MASK                     0xFFu
#define UART_WN7816_GTN_SHIFT                    0
#define UART_WN7816_GTN_WIDTH                    8
#define UART_WN7816_GTN(x)                       (((uint8_t)(((uint8_t)(x))<<UART_WN7816_GTN_SHIFT))&UART_WN7816_GTN_MASK)
/* WF7816 Bit Fields */
#define UART_WF7816_GTFD_MASK                    0xFFu
#define UART_WF7816_GTFD_SHIFT                   0
#define UART_WF7816_GTFD_WIDTH                   8
#define UART_WF7816_GTFD(x)                      (((uint8_t)(((uint8_t)(x))<<UART_WF7816_GTFD_SHIFT))&UART_WF7816_GTFD_MASK)
/* ET7816 Bit Fields */
#define UART_ET7816_RXTHRESHOLD_MASK             0xFu
#define UART_ET7816_RXTHRESHOLD_SHIFT            0
#define UART_ET7816_RXTHRESHOLD_WIDTH            4
#define UART_ET7816_RXTHRESHOLD(x)               (((uint8_t)(((uint8_t)(x))<<UART_ET7816_RXTHRESHOLD_SHIFT))&UART_ET7816_RXTHRESHOLD_MASK)
#define UART_ET7816_TXTHRESHOLD_MASK             0xF0u
#define UART_ET7816_TXTHRESHOLD_SHIFT            4
#define UART_ET7816_TXTHRESHOLD_WIDTH            4
#define UART_ET7816_TXTHRESHOLD(x)               (((uint8_t)(((uint8_t)(x))<<UART_ET7816_TXTHRESHOLD_SHIFT))&UART_ET7816_TXTHRESHOLD_MASK)
/* TL7816 Bit Fields */
#define UART_TL7816_TLEN_MASK                    0xFFu
#define UART_TL7816_TLEN_SHIFT                   0
#define UART_TL7816_TLEN_WIDTH                   8
#define UART_TL7816_TLEN(x)                      (((uint8_t)(((uint8_t)(x))<<UART_TL7816_TLEN_SHIFT))&UART_TL7816_TLEN_MASK)
/* AP7816A_T0 Bit Fields */
#define UART_AP7816A_T0_ADTI_H_MASK              0xFFu
#define UART_AP7816A_T0_ADTI_H_SHIFT             0
#define UART_AP7816A_T0_ADTI_H_WIDTH             8
#define UART_AP7816A_T0_ADTI_H(x)                (((uint8_t)(((uint8_t)(x))<<UART_AP7816A_T0_ADTI_H_SHIFT))&UART_AP7816A_T0_ADTI_H_MASK)
/* AP7816B_T0 Bit Fields */
#define UART_AP7816B_T0_ADTI_L_MASK              0xFFu
#define UART_AP7816B_T0_ADTI_L_SHIFT             0
#define UART_AP7816B_T0_ADTI_L_WIDTH             8
#define UART_AP7816B_T0_ADTI_L(x)                (((uint8_t)(((uint8_t)(x))<<UART_AP7816B_T0_ADTI_L_SHIFT))&UART_AP7816B_T0_ADTI_L_MASK)
/* WP7816A_T0 Bit Fields */
#define UART_WP7816A_T0_WI_H_MASK                0xFFu
#define UART_WP7816A_T0_WI_H_SHIFT               0
#define UART_WP7816A_T0_WI_H_WIDTH               8
#define UART_WP7816A_T0_WI_H(x)                  (((uint8_t)(((uint8_t)(x))<<UART_WP7816A_T0_WI_H_SHIFT))&UART_WP7816A_T0_WI_H_MASK)
/* WP7816B_T0 Bit Fields */
#define UART_WP7816B_T0_WI_L_MASK                0xFFu
#define UART_WP7816B_T0_WI_L_SHIFT               0
#define UART_WP7816B_T0_WI_L_WIDTH               8
#define UART_WP7816B_T0_WI_L(x)                  (((uint8_t)(((uint8_t)(x))<<UART_WP7816B_T0_WI_L_SHIFT))&UART_WP7816B_T0_WI_L_MASK)
/* WP7816A_T1 Bit Fields */
#define UART_WP7816A_T1_BWI_H_MASK               0xFFu
#define UART_WP7816A_T1_BWI_H_SHIFT              0
#define UART_WP7816A_T1_BWI_H_WIDTH              8
#define UART_WP7816A_T1_BWI_H(x)                 (((uint8_t)(((uint8_t)(x))<<UART_WP7816A_T1_BWI_H_SHIFT))&UART_WP7816A_T1_BWI_H_MASK)
/* WP7816B_T1 Bit Fields */
#define UART_WP7816B_T1_BWI_L_MASK               0xFFu
#define UART_WP7816B_T1_BWI_L_SHIFT              0
#define UART_WP7816B_T1_BWI_L_WIDTH              8
#define UART_WP7816B_T1_BWI_L(x)                 (((uint8_t)(((uint8_t)(x))<<UART_WP7816B_T1_BWI_L_SHIFT))&UART_WP7816B_T1_BWI_L_MASK)
/* WGP7816_T1 Bit Fields */
#define UART_WGP7816_T1_BGI_MASK                 0xFu
#define UART_WGP7816_T1_BGI_SHIFT                0
#define UART_WGP7816_T1_BGI_WIDTH                4
#define UART_WGP7816_T1_BGI(x)                   (((uint8_t)(((uint8_t)(x))<<UART_WGP7816_T1_BGI_SHIFT))&UART_WGP7816_T1_BGI_MASK)
#define UART_WGP7816_T1_CWI1_MASK                0xF0u
#define UART_WGP7816_T1_CWI1_SHIFT               4
#define UART_WGP7816_T1_CWI1_WIDTH               4
#define UART_WGP7816_T1_CWI1(x)                  (((uint8_t)(((uint8_t)(x))<<UART_WGP7816_T1_CWI1_SHIFT))&UART_WGP7816_T1_CWI1_MASK)
/* WP7816C_T1 Bit Fields */
#define UART_WP7816C_T1_CWI2_MASK                0x1Fu
#define UART_WP7816C_T1_CWI2_SHIFT               0
#define UART_WP7816C_T1_CWI2_WIDTH               5
#define UART_WP7816C_T1_CWI2(x)                  (((uint8_t)(((uint8_t)(x))<<UART_WP7816C_T1_CWI2_SHIFT))&UART_WP7816C_T1_CWI2_MASK)

/*!
 * @}
 */ /* end of group UART_Register_Masks */


/* UART - Peripheral instance base addresses */
/** Peripheral UART0 base address */
#define UART0_BASE                               (0x4006A000u)
/** Peripheral UART0 base pointer */
#define UART0                                    ((UART_Type *)UART0_BASE)
#define UART0_BASE_PTR                           (UART0)
/** Peripheral UART1 base address */
#define UART1_BASE                               (0x4006B000u)
/** Peripheral UART1 base pointer */
#define UART1                                    ((UART_Type *)UART1_BASE)
#define UART1_BASE_PTR                           (UART1)
/** Peripheral UART2 base address */
#define UART2_BASE                               (0x4006C000u)
/** Peripheral UART2 base pointer */
#define UART2                                    ((UART_Type *)UART2_BASE)
#define UART2_BASE_PTR                           (UART2)
/** Peripheral UART3 base address */
#define UART3_BASE                               (0x4006D000u)
/** Peripheral UART3 base pointer */
#define UART3                                    ((UART_Type *)UART3_BASE)
#define UART3_BASE_PTR                           (UART3)
/** Array initializer of UART peripheral base addresses */
#define UART_BASE_ADDRS                          { UART0_BASE, UART1_BASE, UART2_BASE, UART3_BASE }
/** Array initializer of UART peripheral base pointers */
#define UART_BASE_PTRS                           { UART0, UART1, UART2, UART3 }
/** Interrupt vectors for the UART peripheral type */
#define UART_RX_TX_IRQS                          { UART0_UART1_UART2_UART3_IRQn, UART0_UART1_UART2_UART3_IRQn, UART0_UART1_UART2_UART3_IRQn, UART0_UART1_UART2_UART3_IRQn }
#define UART_ERR_IRQS                            { UART0_UART1_UART2_UART3_IRQn, UART0_UART1_UART2_UART3_IRQn, UART0_UART1_UART2_UART3_IRQn, UART0_UART1_UART2_UART3_IRQn }

/* ----------------------------------------------------------------------------
   -- UART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Accessor_Macros UART - Register accessor macros
 * @{
 */


/* UART - Register instance definitions */
/* UART0 */
#define UART0_BDH                                UART_BDH_REG(UART0)
#define UART0_BDL                                UART_BDL_REG(UART0)
#define UART0_C1                                 UART_C1_REG(UART0)
#define UART0_C2                                 UART_C2_REG(UART0)
#define UART0_S1                                 UART_S1_REG(UART0)
#define UART0_S2                                 UART_S2_REG(UART0)
#define UART0_C3                                 UART_C3_REG(UART0)
#define UART0_D                                  UART_D_REG(UART0)
#define UART0_MA1                                UART_MA1_REG(UART0)
#define UART0_MA2                                UART_MA2_REG(UART0)
#define UART0_C4                                 UART_C4_REG(UART0)
#define UART0_C5                                 UART_C5_REG(UART0)
#define UART0_ED                                 UART_ED_REG(UART0)
#define UART0_MODEM                              UART_MODEM_REG(UART0)
#define UART0_PFIFO                              UART_PFIFO_REG(UART0)
#define UART0_CFIFO                              UART_CFIFO_REG(UART0)
#define UART0_SFIFO                              UART_SFIFO_REG(UART0)
#define UART0_TWFIFO                             UART_TWFIFO_REG(UART0)
#define UART0_TCFIFO                             UART_TCFIFO_REG(UART0)
#define UART0_RWFIFO                             UART_RWFIFO_REG(UART0)
#define UART0_RCFIFO                             UART_RCFIFO_REG(UART0)
/* UART1 */
#define UART1_BDH                                UART_BDH_REG(UART1)
#define UART1_BDL                                UART_BDL_REG(UART1)
#define UART1_C1                                 UART_C1_REG(UART1)
#define UART1_C2                                 UART_C2_REG(UART1)
#define UART1_S1                                 UART_S1_REG(UART1)
#define UART1_S2                                 UART_S2_REG(UART1)
#define UART1_C3                                 UART_C3_REG(UART1)
#define UART1_D                                  UART_D_REG(UART1)
#define UART1_MA1                                UART_MA1_REG(UART1)
#define UART1_MA2                                UART_MA2_REG(UART1)
#define UART1_C4                                 UART_C4_REG(UART1)
#define UART1_C5                                 UART_C5_REG(UART1)
#define UART1_ED                                 UART_ED_REG(UART1)
#define UART1_MODEM                              UART_MODEM_REG(UART1)
#define UART1_PFIFO                              UART_PFIFO_REG(UART1)
#define UART1_CFIFO                              UART_CFIFO_REG(UART1)
#define UART1_SFIFO                              UART_SFIFO_REG(UART1)
#define UART1_TWFIFO                             UART_TWFIFO_REG(UART1)
#define UART1_TCFIFO                             UART_TCFIFO_REG(UART1)
#define UART1_RWFIFO                             UART_RWFIFO_REG(UART1)
#define UART1_RCFIFO                             UART_RCFIFO_REG(UART1)
#define UART1_C7816                              UART_C7816_REG(UART1)
#define UART1_IE7816                             UART_IE7816_REG(UART1)
#define UART1_IS7816                             UART_IS7816_REG(UART1)
#define UART1_WP7816                             UART_WP7816_REG(UART1)
#define UART1_WN7816                             UART_WN7816_REG(UART1)
#define UART1_WF7816                             UART_WF7816_REG(UART1)
#define UART1_ET7816                             UART_ET7816_REG(UART1)
#define UART1_TL7816                             UART_TL7816_REG(UART1)
#define UART1_AP7816A_T0                         UART_AP7816A_T0_REG(UART1)
#define UART1_AP7816B_T0                         UART_AP7816B_T0_REG(UART1)
#define UART1_WP7816A_T0                         UART_WP7816A_T0_REG(UART1)
#define UART1_WP7816A_T1                         UART_WP7816A_T1_REG(UART1)
#define UART1_WP7816B_T0                         UART_WP7816B_T0_REG(UART1)
#define UART1_WP7816B_T1                         UART_WP7816B_T1_REG(UART1)
#define UART1_WGP7816_T1                         UART_WGP7816_T1_REG(UART1)
#define UART1_WP7816C_T1                         UART_WP7816C_T1_REG(UART1)
/* UART2 */
#define UART2_BDH                                UART_BDH_REG(UART2)
#define UART2_BDL                                UART_BDL_REG(UART2)
#define UART2_C1                                 UART_C1_REG(UART2)
#define UART2_C2                                 UART_C2_REG(UART2)
#define UART2_S1                                 UART_S1_REG(UART2)
#define UART2_S2                                 UART_S2_REG(UART2)
#define UART2_C3                                 UART_C3_REG(UART2)
#define UART2_D                                  UART_D_REG(UART2)
#define UART2_MA1                                UART_MA1_REG(UART2)
#define UART2_MA2                                UART_MA2_REG(UART2)
#define UART2_C4                                 UART_C4_REG(UART2)
#define UART2_C5                                 UART_C5_REG(UART2)
#define UART2_ED                                 UART_ED_REG(UART2)
#define UART2_MODEM                              UART_MODEM_REG(UART2)
#define UART2_PFIFO                              UART_PFIFO_REG(UART2)
#define UART2_CFIFO                              UART_CFIFO_REG(UART2)
#define UART2_SFIFO                              UART_SFIFO_REG(UART2)
#define UART2_TWFIFO                             UART_TWFIFO_REG(UART2)
#define UART2_TCFIFO                             UART_TCFIFO_REG(UART2)
#define UART2_RWFIFO                             UART_RWFIFO_REG(UART2)
#define UART2_RCFIFO                             UART_RCFIFO_REG(UART2)
/* UART3 */
#define UART3_BDH                                UART_BDH_REG(UART3)
#define UART3_BDL                                UART_BDL_REG(UART3)
#define UART3_C1                                 UART_C1_REG(UART3)
#define UART3_C2                                 UART_C2_REG(UART3)
#define UART3_S1                                 UART_S1_REG(UART3)
#define UART3_S2                                 UART_S2_REG(UART3)
#define UART3_C3                                 UART_C3_REG(UART3)
#define UART3_D                                  UART_D_REG(UART3)
#define UART3_MA1                                UART_MA1_REG(UART3)
#define UART3_MA2                                UART_MA2_REG(UART3)
#define UART3_C4                                 UART_C4_REG(UART3)
#define UART3_C5                                 UART_C5_REG(UART3)
#define UART3_ED                                 UART_ED_REG(UART3)
#define UART3_MODEM                              UART_MODEM_REG(UART3)
#define UART3_PFIFO                              UART_PFIFO_REG(UART3)
#define UART3_CFIFO                              UART_CFIFO_REG(UART3)
#define UART3_SFIFO                              UART_SFIFO_REG(UART3)
#define UART3_TWFIFO                             UART_TWFIFO_REG(UART3)
#define UART3_TCFIFO                             UART_TCFIFO_REG(UART3)
#define UART3_RWFIFO                             UART_RWFIFO_REG(UART3)
#define UART3_RCFIFO                             UART_RCFIFO_REG(UART3)
#define UART3_C7816                              UART_C7816_REG(UART3)
#define UART3_IE7816                             UART_IE7816_REG(UART3)
#define UART3_IS7816                             UART_IS7816_REG(UART3)
#define UART3_WP7816                             UART_WP7816_REG(UART3)
#define UART3_WN7816                             UART_WN7816_REG(UART3)
#define UART3_WF7816                             UART_WF7816_REG(UART3)
#define UART3_ET7816                             UART_ET7816_REG(UART3)
#define UART3_TL7816                             UART_TL7816_REG(UART3)
#define UART3_AP7816A_T0                         UART_AP7816A_T0_REG(UART3)
#define UART3_AP7816B_T0                         UART_AP7816B_T0_REG(UART3)
#define UART3_WP7816A_T0                         UART_WP7816A_T0_REG(UART3)
#define UART3_WP7816A_T1                         UART_WP7816A_T1_REG(UART3)
#define UART3_WP7816B_T0                         UART_WP7816B_T0_REG(UART3)
#define UART3_WP7816B_T1                         UART_WP7816B_T1_REG(UART3)
#define UART3_WGP7816_T1                         UART_WGP7816_T1_REG(UART3)
#define UART3_WP7816C_T1                         UART_WP7816C_T1_REG(UART3)

/*!
 * @}
 */ /* end of group UART_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group UART_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- VREF Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Peripheral_Access_Layer VREF Peripheral Access Layer
 * @{
 */

/** VREF - Register Layout Typedef */
typedef struct {
  __IO uint8_t VREFH_TRM;                          /**< VREF Trim Register, offset: 0x0 */
  __IO uint8_t VREFH_SC;                           /**< VREF Status and Control Register, offset: 0x1 */
       uint8_t RESERVED_0[3];
  __IO uint8_t VREFL_TRM;                          /**< VREFL TRIM Register, offset: 0x5 */
} VREF_Type, *VREF_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- VREF - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Register_Accessor_Macros VREF - Register accessor macros
 * @{
 */


/* VREF - Register accessors */
#define VREF_VREFH_TRM_REG(base)                 ((base)->VREFH_TRM)
#define VREF_VREFH_SC_REG(base)                  ((base)->VREFH_SC)
#define VREF_VREFL_TRM_REG(base)                 ((base)->VREFL_TRM)

/*!
 * @}
 */ /* end of group VREF_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- VREF Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Register_Masks VREF Register Masks
 * @{
 */

/* VREFH_TRM Bit Fields */
#define VREF_VREFH_TRM_TRIM_MASK                 0x3Fu
#define VREF_VREFH_TRM_TRIM_SHIFT                0
#define VREF_VREFH_TRM_TRIM_WIDTH                6
#define VREF_VREFH_TRM_TRIM(x)                   (((uint8_t)(((uint8_t)(x))<<VREF_VREFH_TRM_TRIM_SHIFT))&VREF_VREFH_TRM_TRIM_MASK)
#define VREF_VREFH_TRM_CHOPEN_MASK               0x40u
#define VREF_VREFH_TRM_CHOPEN_SHIFT              6
#define VREF_VREFH_TRM_CHOPEN_WIDTH              1
#define VREF_VREFH_TRM_CHOPEN(x)                 (((uint8_t)(((uint8_t)(x))<<VREF_VREFH_TRM_CHOPEN_SHIFT))&VREF_VREFH_TRM_CHOPEN_MASK)
/* VREFH_SC Bit Fields */
#define VREF_VREFH_SC_MODE_LV_MASK               0x3u
#define VREF_VREFH_SC_MODE_LV_SHIFT              0
#define VREF_VREFH_SC_MODE_LV_WIDTH              2
#define VREF_VREFH_SC_MODE_LV(x)                 (((uint8_t)(((uint8_t)(x))<<VREF_VREFH_SC_MODE_LV_SHIFT))&VREF_VREFH_SC_MODE_LV_MASK)
#define VREF_VREFH_SC_VREFST_MASK                0x4u
#define VREF_VREFH_SC_VREFST_SHIFT               2
#define VREF_VREFH_SC_VREFST_WIDTH               1
#define VREF_VREFH_SC_VREFST(x)                  (((uint8_t)(((uint8_t)(x))<<VREF_VREFH_SC_VREFST_SHIFT))&VREF_VREFH_SC_VREFST_MASK)
#define VREF_VREFH_SC_ICOMPEN_MASK               0x20u
#define VREF_VREFH_SC_ICOMPEN_SHIFT              5
#define VREF_VREFH_SC_ICOMPEN_WIDTH              1
#define VREF_VREFH_SC_ICOMPEN(x)                 (((uint8_t)(((uint8_t)(x))<<VREF_VREFH_SC_ICOMPEN_SHIFT))&VREF_VREFH_SC_ICOMPEN_MASK)
#define VREF_VREFH_SC_REGEN_MASK                 0x40u
#define VREF_VREFH_SC_REGEN_SHIFT                6
#define VREF_VREFH_SC_REGEN_WIDTH                1
#define VREF_VREFH_SC_REGEN(x)                   (((uint8_t)(((uint8_t)(x))<<VREF_VREFH_SC_REGEN_SHIFT))&VREF_VREFH_SC_REGEN_MASK)
#define VREF_VREFH_SC_VREFEN_MASK                0x80u
#define VREF_VREFH_SC_VREFEN_SHIFT               7
#define VREF_VREFH_SC_VREFEN_WIDTH               1
#define VREF_VREFH_SC_VREFEN(x)                  (((uint8_t)(((uint8_t)(x))<<VREF_VREFH_SC_VREFEN_SHIFT))&VREF_VREFH_SC_VREFEN_MASK)
/* VREFL_TRM Bit Fields */
#define VREF_VREFL_TRM_VREFL_TRIM_MASK           0x7u
#define VREF_VREFL_TRM_VREFL_TRIM_SHIFT          0
#define VREF_VREFL_TRM_VREFL_TRIM_WIDTH          3
#define VREF_VREFL_TRM_VREFL_TRIM(x)             (((uint8_t)(((uint8_t)(x))<<VREF_VREFL_TRM_VREFL_TRIM_SHIFT))&VREF_VREFL_TRM_VREFL_TRIM_MASK)
#define VREF_VREFL_TRM_VREFL_EN_MASK             0x8u
#define VREF_VREFL_TRM_VREFL_EN_SHIFT            3
#define VREF_VREFL_TRM_VREFL_EN_WIDTH            1
#define VREF_VREFL_TRM_VREFL_EN(x)               (((uint8_t)(((uint8_t)(x))<<VREF_VREFL_TRM_VREFL_EN_SHIFT))&VREF_VREFL_TRM_VREFL_EN_MASK)
#define VREF_VREFL_TRM_VREFL_SEL_MASK            0x10u
#define VREF_VREFL_TRM_VREFL_SEL_SHIFT           4
#define VREF_VREFL_TRM_VREFL_SEL_WIDTH           1
#define VREF_VREFL_TRM_VREFL_SEL(x)              (((uint8_t)(((uint8_t)(x))<<VREF_VREFL_TRM_VREFL_SEL_SHIFT))&VREF_VREFL_TRM_VREFL_SEL_MASK)

/*!
 * @}
 */ /* end of group VREF_Register_Masks */


/* VREF - Peripheral instance base addresses */
/** Peripheral VREF base address */
#define VREF_BASE                                (0x4006F000u)
/** Peripheral VREF base pointer */
#define VREF                                     ((VREF_Type *)VREF_BASE)
#define VREF_BASE_PTR                            (VREF)
/** Array initializer of VREF peripheral base addresses */
#define VREF_BASE_ADDRS                          { VREF_BASE }
/** Array initializer of VREF peripheral base pointers */
#define VREF_BASE_PTRS                           { VREF }

/* ----------------------------------------------------------------------------
   -- VREF - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Register_Accessor_Macros VREF - Register accessor macros
 * @{
 */


/* VREF - Register instance definitions */
/* VREF */
#define VREF_VREFH_TRM                           VREF_VREFH_TRM_REG(VREF)
#define VREF_VREFH_SC                            VREF_VREFH_SC_REG(VREF)
#define VREF_VREFL_TRM                           VREF_VREFL_TRM_REG(VREF)

/*!
 * @}
 */ /* end of group VREF_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group VREF_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- WDOG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Peripheral_Access_Layer WDOG Peripheral Access Layer
 * @{
 */

/** WDOG - Register Layout Typedef */
typedef struct {
  __IO uint16_t STCTRLH;                           /**< Watchdog Status and Control Register High, offset: 0x0 */
  __IO uint16_t STCTRLL;                           /**< Watchdog Status and Control Register Low, offset: 0x2 */
  __IO uint16_t TOVALH;                            /**< Watchdog Time-out Value Register High, offset: 0x4 */
  __IO uint16_t TOVALL;                            /**< Watchdog Time-out Value Register Low, offset: 0x6 */
  __IO uint16_t WINH;                              /**< Watchdog Window Register High, offset: 0x8 */
  __IO uint16_t WINL;                              /**< Watchdog Window Register Low, offset: 0xA */
  __IO uint16_t REFRESH;                           /**< Watchdog Refresh register, offset: 0xC */
  __IO uint16_t UNLOCK;                            /**< Watchdog Unlock register, offset: 0xE */
  __IO uint16_t TMROUTH;                           /**< Watchdog Timer Output Register High, offset: 0x10 */
  __IO uint16_t TMROUTL;                           /**< Watchdog Timer Output Register Low, offset: 0x12 */
  __IO uint16_t RSTCNT;                            /**< Watchdog Reset Count register, offset: 0x14 */
  __IO uint16_t PRESC;                             /**< Watchdog Prescaler register, offset: 0x16 */
} WDOG_Type, *WDOG_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- WDOG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Accessor_Macros WDOG - Register accessor macros
 * @{
 */


/* WDOG - Register accessors */
#define WDOG_STCTRLH_REG(base)                   ((base)->STCTRLH)
#define WDOG_STCTRLL_REG(base)                   ((base)->STCTRLL)
#define WDOG_TOVALH_REG(base)                    ((base)->TOVALH)
#define WDOG_TOVALL_REG(base)                    ((base)->TOVALL)
#define WDOG_WINH_REG(base)                      ((base)->WINH)
#define WDOG_WINL_REG(base)                      ((base)->WINL)
#define WDOG_REFRESH_REG(base)                   ((base)->REFRESH)
#define WDOG_UNLOCK_REG(base)                    ((base)->UNLOCK)
#define WDOG_TMROUTH_REG(base)                   ((base)->TMROUTH)
#define WDOG_TMROUTL_REG(base)                   ((base)->TMROUTL)
#define WDOG_RSTCNT_REG(base)                    ((base)->RSTCNT)
#define WDOG_PRESC_REG(base)                     ((base)->PRESC)

/*!
 * @}
 */ /* end of group WDOG_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- WDOG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Masks WDOG Register Masks
 * @{
 */

/* STCTRLH Bit Fields */
#define WDOG_STCTRLH_WDOGEN_MASK                 0x1u
#define WDOG_STCTRLH_WDOGEN_SHIFT                0
#define WDOG_STCTRLH_WDOGEN_WIDTH                1
#define WDOG_STCTRLH_WDOGEN(x)                   (((uint16_t)(((uint16_t)(x))<<WDOG_STCTRLH_WDOGEN_SHIFT))&WDOG_STCTRLH_WDOGEN_MASK)
#define WDOG_STCTRLH_CLKSRC_MASK                 0x2u
#define WDOG_STCTRLH_CLKSRC_SHIFT                1
#define WDOG_STCTRLH_CLKSRC_WIDTH                1
#define WDOG_STCTRLH_CLKSRC(x)                   (((uint16_t)(((uint16_t)(x))<<WDOG_STCTRLH_CLKSRC_SHIFT))&WDOG_STCTRLH_CLKSRC_MASK)
#define WDOG_STCTRLH_IRQRSTEN_MASK               0x4u
#define WDOG_STCTRLH_IRQRSTEN_SHIFT              2
#define WDOG_STCTRLH_IRQRSTEN_WIDTH              1
#define WDOG_STCTRLH_IRQRSTEN(x)                 (((uint16_t)(((uint16_t)(x))<<WDOG_STCTRLH_IRQRSTEN_SHIFT))&WDOG_STCTRLH_IRQRSTEN_MASK)
#define WDOG_STCTRLH_WINEN_MASK                  0x8u
#define WDOG_STCTRLH_WINEN_SHIFT                 3
#define WDOG_STCTRLH_WINEN_WIDTH                 1
#define WDOG_STCTRLH_WINEN(x)                    (((uint16_t)(((uint16_t)(x))<<WDOG_STCTRLH_WINEN_SHIFT))&WDOG_STCTRLH_WINEN_MASK)
#define WDOG_STCTRLH_ALLOWUPDATE_MASK            0x10u
#define WDOG_STCTRLH_ALLOWUPDATE_SHIFT           4
#define WDOG_STCTRLH_ALLOWUPDATE_WIDTH           1
#define WDOG_STCTRLH_ALLOWUPDATE(x)              (((uint16_t)(((uint16_t)(x))<<WDOG_STCTRLH_ALLOWUPDATE_SHIFT))&WDOG_STCTRLH_ALLOWUPDATE_MASK)
#define WDOG_STCTRLH_DBGEN_MASK                  0x20u
#define WDOG_STCTRLH_DBGEN_SHIFT                 5
#define WDOG_STCTRLH_DBGEN_WIDTH                 1
#define WDOG_STCTRLH_DBGEN(x)                    (((uint16_t)(((uint16_t)(x))<<WDOG_STCTRLH_DBGEN_SHIFT))&WDOG_STCTRLH_DBGEN_MASK)
#define WDOG_STCTRLH_STOPEN_MASK                 0x40u
#define WDOG_STCTRLH_STOPEN_SHIFT                6
#define WDOG_STCTRLH_STOPEN_WIDTH                1
#define WDOG_STCTRLH_STOPEN(x)                   (((uint16_t)(((uint16_t)(x))<<WDOG_STCTRLH_STOPEN_SHIFT))&WDOG_STCTRLH_STOPEN_MASK)
#define WDOG_STCTRLH_TESTWDOG_MASK               0x400u
#define WDOG_STCTRLH_TESTWDOG_SHIFT              10
#define WDOG_STCTRLH_TESTWDOG_WIDTH              1
#define WDOG_STCTRLH_TESTWDOG(x)                 (((uint16_t)(((uint16_t)(x))<<WDOG_STCTRLH_TESTWDOG_SHIFT))&WDOG_STCTRLH_TESTWDOG_MASK)
#define WDOG_STCTRLH_TESTSEL_MASK                0x800u
#define WDOG_STCTRLH_TESTSEL_SHIFT               11
#define WDOG_STCTRLH_TESTSEL_WIDTH               1
#define WDOG_STCTRLH_TESTSEL(x)                  (((uint16_t)(((uint16_t)(x))<<WDOG_STCTRLH_TESTSEL_SHIFT))&WDOG_STCTRLH_TESTSEL_MASK)
#define WDOG_STCTRLH_BYTESEL_MASK                0x3000u
#define WDOG_STCTRLH_BYTESEL_SHIFT               12
#define WDOG_STCTRLH_BYTESEL_WIDTH               2
#define WDOG_STCTRLH_BYTESEL(x)                  (((uint16_t)(((uint16_t)(x))<<WDOG_STCTRLH_BYTESEL_SHIFT))&WDOG_STCTRLH_BYTESEL_MASK)
#define WDOG_STCTRLH_DISTESTWDOG_MASK            0x4000u
#define WDOG_STCTRLH_DISTESTWDOG_SHIFT           14
#define WDOG_STCTRLH_DISTESTWDOG_WIDTH           1
#define WDOG_STCTRLH_DISTESTWDOG(x)              (((uint16_t)(((uint16_t)(x))<<WDOG_STCTRLH_DISTESTWDOG_SHIFT))&WDOG_STCTRLH_DISTESTWDOG_MASK)
/* STCTRLL Bit Fields */
#define WDOG_STCTRLL_INTFLG_MASK                 0x8000u
#define WDOG_STCTRLL_INTFLG_SHIFT                15
#define WDOG_STCTRLL_INTFLG_WIDTH                1
#define WDOG_STCTRLL_INTFLG(x)                   (((uint16_t)(((uint16_t)(x))<<WDOG_STCTRLL_INTFLG_SHIFT))&WDOG_STCTRLL_INTFLG_MASK)
/* TOVALH Bit Fields */
#define WDOG_TOVALH_TOVALHIGH_MASK               0xFFFFu
#define WDOG_TOVALH_TOVALHIGH_SHIFT              0
#define WDOG_TOVALH_TOVALHIGH_WIDTH              16
#define WDOG_TOVALH_TOVALHIGH(x)                 (((uint16_t)(((uint16_t)(x))<<WDOG_TOVALH_TOVALHIGH_SHIFT))&WDOG_TOVALH_TOVALHIGH_MASK)
/* TOVALL Bit Fields */
#define WDOG_TOVALL_TOVALLOW_MASK                0xFFFFu
#define WDOG_TOVALL_TOVALLOW_SHIFT               0
#define WDOG_TOVALL_TOVALLOW_WIDTH               16
#define WDOG_TOVALL_TOVALLOW(x)                  (((uint16_t)(((uint16_t)(x))<<WDOG_TOVALL_TOVALLOW_SHIFT))&WDOG_TOVALL_TOVALLOW_MASK)
/* WINH Bit Fields */
#define WDOG_WINH_WINHIGH_MASK                   0xFFFFu
#define WDOG_WINH_WINHIGH_SHIFT                  0
#define WDOG_WINH_WINHIGH_WIDTH                  16
#define WDOG_WINH_WINHIGH(x)                     (((uint16_t)(((uint16_t)(x))<<WDOG_WINH_WINHIGH_SHIFT))&WDOG_WINH_WINHIGH_MASK)
/* WINL Bit Fields */
#define WDOG_WINL_WINLOW_MASK                    0xFFFFu
#define WDOG_WINL_WINLOW_SHIFT                   0
#define WDOG_WINL_WINLOW_WIDTH                   16
#define WDOG_WINL_WINLOW(x)                      (((uint16_t)(((uint16_t)(x))<<WDOG_WINL_WINLOW_SHIFT))&WDOG_WINL_WINLOW_MASK)
/* REFRESH Bit Fields */
#define WDOG_REFRESH_WDOGREFRESH_MASK            0xFFFFu
#define WDOG_REFRESH_WDOGREFRESH_SHIFT           0
#define WDOG_REFRESH_WDOGREFRESH_WIDTH           16
#define WDOG_REFRESH_WDOGREFRESH(x)              (((uint16_t)(((uint16_t)(x))<<WDOG_REFRESH_WDOGREFRESH_SHIFT))&WDOG_REFRESH_WDOGREFRESH_MASK)
/* UNLOCK Bit Fields */
#define WDOG_UNLOCK_WDOGUNLOCK_MASK              0xFFFFu
#define WDOG_UNLOCK_WDOGUNLOCK_SHIFT             0
#define WDOG_UNLOCK_WDOGUNLOCK_WIDTH             16
#define WDOG_UNLOCK_WDOGUNLOCK(x)                (((uint16_t)(((uint16_t)(x))<<WDOG_UNLOCK_WDOGUNLOCK_SHIFT))&WDOG_UNLOCK_WDOGUNLOCK_MASK)
/* TMROUTH Bit Fields */
#define WDOG_TMROUTH_TIMEROUTHIGH_MASK           0xFFFFu
#define WDOG_TMROUTH_TIMEROUTHIGH_SHIFT          0
#define WDOG_TMROUTH_TIMEROUTHIGH_WIDTH          16
#define WDOG_TMROUTH_TIMEROUTHIGH(x)             (((uint16_t)(((uint16_t)(x))<<WDOG_TMROUTH_TIMEROUTHIGH_SHIFT))&WDOG_TMROUTH_TIMEROUTHIGH_MASK)
/* TMROUTL Bit Fields */
#define WDOG_TMROUTL_TIMEROUTLOW_MASK            0xFFFFu
#define WDOG_TMROUTL_TIMEROUTLOW_SHIFT           0
#define WDOG_TMROUTL_TIMEROUTLOW_WIDTH           16
#define WDOG_TMROUTL_TIMEROUTLOW(x)              (((uint16_t)(((uint16_t)(x))<<WDOG_TMROUTL_TIMEROUTLOW_SHIFT))&WDOG_TMROUTL_TIMEROUTLOW_MASK)
/* RSTCNT Bit Fields */
#define WDOG_RSTCNT_RSTCNT_MASK                  0xFFFFu
#define WDOG_RSTCNT_RSTCNT_SHIFT                 0
#define WDOG_RSTCNT_RSTCNT_WIDTH                 16
#define WDOG_RSTCNT_RSTCNT(x)                    (((uint16_t)(((uint16_t)(x))<<WDOG_RSTCNT_RSTCNT_SHIFT))&WDOG_RSTCNT_RSTCNT_MASK)
/* PRESC Bit Fields */
#define WDOG_PRESC_PRESCVAL_MASK                 0x700u
#define WDOG_PRESC_PRESCVAL_SHIFT                8
#define WDOG_PRESC_PRESCVAL_WIDTH                3
#define WDOG_PRESC_PRESCVAL(x)                   (((uint16_t)(((uint16_t)(x))<<WDOG_PRESC_PRESCVAL_SHIFT))&WDOG_PRESC_PRESCVAL_MASK)

/*!
 * @}
 */ /* end of group WDOG_Register_Masks */


/* WDOG - Peripheral instance base addresses */
/** Peripheral WDOG base address */
#define WDOG_BASE                                (0x40053000u)
/** Peripheral WDOG base pointer */
#define WDOG                                     ((WDOG_Type *)WDOG_BASE)
#define WDOG_BASE_PTR                            (WDOG)
/** Array initializer of WDOG peripheral base addresses */
#define WDOG_BASE_ADDRS                          { WDOG_BASE }
/** Array initializer of WDOG peripheral base pointers */
#define WDOG_BASE_PTRS                           { WDOG }
/** Interrupt vectors for the WDOG peripheral type */
#define WDOG_IRQS                                { WDOG_EWM_IRQn }

/* ----------------------------------------------------------------------------
   -- WDOG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Accessor_Macros WDOG - Register accessor macros
 * @{
 */


/* WDOG - Register instance definitions */
/* WDOG */
#define WDOG_STCTRLH                             WDOG_STCTRLH_REG(WDOG)
#define WDOG_STCTRLL                             WDOG_STCTRLL_REG(WDOG)
#define WDOG_TOVALH                              WDOG_TOVALH_REG(WDOG)
#define WDOG_TOVALL                              WDOG_TOVALL_REG(WDOG)
#define WDOG_WINH                                WDOG_WINH_REG(WDOG)
#define WDOG_WINL                                WDOG_WINL_REG(WDOG)
#define WDOG_REFRESH                             WDOG_REFRESH_REG(WDOG)
#define WDOG_UNLOCK                              WDOG_UNLOCK_REG(WDOG)
#define WDOG_TMROUTH                             WDOG_TMROUTH_REG(WDOG)
#define WDOG_TMROUTL                             WDOG_TMROUTL_REG(WDOG)
#define WDOG_RSTCNT                              WDOG_RSTCNT_REG(WDOG)
#define WDOG_PRESC                               WDOG_PRESC_REG(WDOG)

/*!
 * @}
 */ /* end of group WDOG_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group WDOG_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- XBAR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBAR_Peripheral_Access_Layer XBAR Peripheral Access Layer
 * @{
 */

/** XBAR - Register Layout Typedef */
typedef struct {
  __IO uint16_t SEL0;                              /**< Crossbar Select Register 0, offset: 0x0 */
  __IO uint16_t SEL1;                              /**< Crossbar Select Register 1, offset: 0x2 */
  __IO uint16_t SEL2;                              /**< Crossbar Select Register 2, offset: 0x4 */
  __IO uint16_t SEL3;                              /**< Crossbar Select Register 3, offset: 0x6 */
  __IO uint16_t SEL4;                              /**< Crossbar Select Register 4, offset: 0x8 */
  __IO uint16_t SEL5;                              /**< Crossbar Select Register 5, offset: 0xA */
  __IO uint16_t SEL6;                              /**< Crossbar Select Register 6, offset: 0xC */
  __IO uint16_t SEL7;                              /**< Crossbar Select Register 7, offset: 0xE */
  __IO uint16_t SEL8;                              /**< Crossbar Select Register 8, offset: 0x10 */
  __IO uint16_t SEL9;                              /**< Crossbar Select Register 9, offset: 0x12 */
  __IO uint16_t SEL10;                             /**< Crossbar Select Register 10, offset: 0x14 */
  __IO uint16_t SEL11;                             /**< Crossbar Select Register 11, offset: 0x16 */
  __IO uint16_t SEL12;                             /**< Crossbar Select Register 12, offset: 0x18 */
  __IO uint16_t SEL13;                             /**< Crossbar Select Register 13, offset: 0x1A */
  __IO uint16_t SEL14;                             /**< Crossbar Select Register 14, offset: 0x1C */
  __IO uint16_t SEL15;                             /**< Crossbar Select Register 15, offset: 0x1E */
  __IO uint16_t SEL16;                             /**< Crossbar Select Register 16, offset: 0x20 */
  __IO uint16_t SEL17;                             /**< Crossbar Select Register 17, offset: 0x22 */
  __IO uint16_t SEL18;                             /**< Crossbar Select Register 18, offset: 0x24 */
  __IO uint16_t SEL19;                             /**< Crossbar Select Register 19, offset: 0x26 */
  __IO uint16_t SEL20;                             /**< Crossbar Select Register 20, offset: 0x28 */
  __IO uint16_t SEL21;                             /**< Crossbar Select Register 21, offset: 0x2A */
  __IO uint16_t CTRL0;                             /**< Crossbar Control Register 0, offset: 0x2C */
  __IO uint16_t CTRL1;                             /**< Crossbar Control Register 1, offset: 0x2E */
} XBAR_Type, *XBAR_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- XBAR - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBAR_Register_Accessor_Macros XBAR - Register accessor macros
 * @{
 */


/* XBAR - Register accessors */
#define XBAR_SEL0_REG(base)                      ((base)->SEL0)
#define XBAR_SEL1_REG(base)                      ((base)->SEL1)
#define XBAR_SEL2_REG(base)                      ((base)->SEL2)
#define XBAR_SEL3_REG(base)                      ((base)->SEL3)
#define XBAR_SEL4_REG(base)                      ((base)->SEL4)
#define XBAR_SEL5_REG(base)                      ((base)->SEL5)
#define XBAR_SEL6_REG(base)                      ((base)->SEL6)
#define XBAR_SEL7_REG(base)                      ((base)->SEL7)
#define XBAR_SEL8_REG(base)                      ((base)->SEL8)
#define XBAR_SEL9_REG(base)                      ((base)->SEL9)
#define XBAR_SEL10_REG(base)                     ((base)->SEL10)
#define XBAR_SEL11_REG(base)                     ((base)->SEL11)
#define XBAR_SEL12_REG(base)                     ((base)->SEL12)
#define XBAR_SEL13_REG(base)                     ((base)->SEL13)
#define XBAR_SEL14_REG(base)                     ((base)->SEL14)
#define XBAR_SEL15_REG(base)                     ((base)->SEL15)
#define XBAR_SEL16_REG(base)                     ((base)->SEL16)
#define XBAR_SEL17_REG(base)                     ((base)->SEL17)
#define XBAR_SEL18_REG(base)                     ((base)->SEL18)
#define XBAR_SEL19_REG(base)                     ((base)->SEL19)
#define XBAR_SEL20_REG(base)                     ((base)->SEL20)
#define XBAR_SEL21_REG(base)                     ((base)->SEL21)
#define XBAR_CTRL0_REG(base)                     ((base)->CTRL0)
#define XBAR_CTRL1_REG(base)                     ((base)->CTRL1)

/*!
 * @}
 */ /* end of group XBAR_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- XBAR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBAR_Register_Masks XBAR Register Masks
 * @{
 */

/* SEL0 Bit Fields */
#define XBAR_SEL0_SEL0_MASK                      0x3Fu
#define XBAR_SEL0_SEL0_SHIFT                     0
#define XBAR_SEL0_SEL0_WIDTH                     6
#define XBAR_SEL0_SEL0(x)                        (((uint16_t)(((uint16_t)(x))<<XBAR_SEL0_SEL0_SHIFT))&XBAR_SEL0_SEL0_MASK)
#define XBAR_SEL0_SEL1_MASK                      0x3F00u
#define XBAR_SEL0_SEL1_SHIFT                     8
#define XBAR_SEL0_SEL1_WIDTH                     6
#define XBAR_SEL0_SEL1(x)                        (((uint16_t)(((uint16_t)(x))<<XBAR_SEL0_SEL1_SHIFT))&XBAR_SEL0_SEL1_MASK)
/* SEL1 Bit Fields */
#define XBAR_SEL1_SEL2_MASK                      0x3Fu
#define XBAR_SEL1_SEL2_SHIFT                     0
#define XBAR_SEL1_SEL2_WIDTH                     6
#define XBAR_SEL1_SEL2(x)                        (((uint16_t)(((uint16_t)(x))<<XBAR_SEL1_SEL2_SHIFT))&XBAR_SEL1_SEL2_MASK)
#define XBAR_SEL1_SEL3_MASK                      0x3F00u
#define XBAR_SEL1_SEL3_SHIFT                     8
#define XBAR_SEL1_SEL3_WIDTH                     6
#define XBAR_SEL1_SEL3(x)                        (((uint16_t)(((uint16_t)(x))<<XBAR_SEL1_SEL3_SHIFT))&XBAR_SEL1_SEL3_MASK)
/* SEL2 Bit Fields */
#define XBAR_SEL2_SEL4_MASK                      0x3Fu
#define XBAR_SEL2_SEL4_SHIFT                     0
#define XBAR_SEL2_SEL4_WIDTH                     6
#define XBAR_SEL2_SEL4(x)                        (((uint16_t)(((uint16_t)(x))<<XBAR_SEL2_SEL4_SHIFT))&XBAR_SEL2_SEL4_MASK)
#define XBAR_SEL2_SEL5_MASK                      0x3F00u
#define XBAR_SEL2_SEL5_SHIFT                     8
#define XBAR_SEL2_SEL5_WIDTH                     6
#define XBAR_SEL2_SEL5(x)                        (((uint16_t)(((uint16_t)(x))<<XBAR_SEL2_SEL5_SHIFT))&XBAR_SEL2_SEL5_MASK)
/* SEL3 Bit Fields */
#define XBAR_SEL3_SEL6_MASK                      0x3Fu
#define XBAR_SEL3_SEL6_SHIFT                     0
#define XBAR_SEL3_SEL6_WIDTH                     6
#define XBAR_SEL3_SEL6(x)                        (((uint16_t)(((uint16_t)(x))<<XBAR_SEL3_SEL6_SHIFT))&XBAR_SEL3_SEL6_MASK)
#define XBAR_SEL3_SEL7_MASK                      0x3F00u
#define XBAR_SEL3_SEL7_SHIFT                     8
#define XBAR_SEL3_SEL7_WIDTH                     6
#define XBAR_SEL3_SEL7(x)                        (((uint16_t)(((uint16_t)(x))<<XBAR_SEL3_SEL7_SHIFT))&XBAR_SEL3_SEL7_MASK)
/* SEL4 Bit Fields */
#define XBAR_SEL4_SEL8_MASK                      0x3Fu
#define XBAR_SEL4_SEL8_SHIFT                     0
#define XBAR_SEL4_SEL8_WIDTH                     6
#define XBAR_SEL4_SEL8(x)                        (((uint16_t)(((uint16_t)(x))<<XBAR_SEL4_SEL8_SHIFT))&XBAR_SEL4_SEL8_MASK)
#define XBAR_SEL4_SEL9_MASK                      0x3F00u
#define XBAR_SEL4_SEL9_SHIFT                     8
#define XBAR_SEL4_SEL9_WIDTH                     6
#define XBAR_SEL4_SEL9(x)                        (((uint16_t)(((uint16_t)(x))<<XBAR_SEL4_SEL9_SHIFT))&XBAR_SEL4_SEL9_MASK)
/* SEL5 Bit Fields */
#define XBAR_SEL5_SEL10_MASK                     0x3Fu
#define XBAR_SEL5_SEL10_SHIFT                    0
#define XBAR_SEL5_SEL10_WIDTH                    6
#define XBAR_SEL5_SEL10(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_SEL5_SEL10_SHIFT))&XBAR_SEL5_SEL10_MASK)
#define XBAR_SEL5_SEL11_MASK                     0x3F00u
#define XBAR_SEL5_SEL11_SHIFT                    8
#define XBAR_SEL5_SEL11_WIDTH                    6
#define XBAR_SEL5_SEL11(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_SEL5_SEL11_SHIFT))&XBAR_SEL5_SEL11_MASK)
/* SEL6 Bit Fields */
#define XBAR_SEL6_SEL12_MASK                     0x3Fu
#define XBAR_SEL6_SEL12_SHIFT                    0
#define XBAR_SEL6_SEL12_WIDTH                    6
#define XBAR_SEL6_SEL12(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_SEL6_SEL12_SHIFT))&XBAR_SEL6_SEL12_MASK)
#define XBAR_SEL6_SEL13_MASK                     0x3F00u
#define XBAR_SEL6_SEL13_SHIFT                    8
#define XBAR_SEL6_SEL13_WIDTH                    6
#define XBAR_SEL6_SEL13(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_SEL6_SEL13_SHIFT))&XBAR_SEL6_SEL13_MASK)
/* SEL7 Bit Fields */
#define XBAR_SEL7_SEL14_MASK                     0x3Fu
#define XBAR_SEL7_SEL14_SHIFT                    0
#define XBAR_SEL7_SEL14_WIDTH                    6
#define XBAR_SEL7_SEL14(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_SEL7_SEL14_SHIFT))&XBAR_SEL7_SEL14_MASK)
#define XBAR_SEL7_SEL15_MASK                     0x3F00u
#define XBAR_SEL7_SEL15_SHIFT                    8
#define XBAR_SEL7_SEL15_WIDTH                    6
#define XBAR_SEL7_SEL15(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_SEL7_SEL15_SHIFT))&XBAR_SEL7_SEL15_MASK)
/* SEL8 Bit Fields */
#define XBAR_SEL8_SEL16_MASK                     0x3Fu
#define XBAR_SEL8_SEL16_SHIFT                    0
#define XBAR_SEL8_SEL16_WIDTH                    6
#define XBAR_SEL8_SEL16(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_SEL8_SEL16_SHIFT))&XBAR_SEL8_SEL16_MASK)
#define XBAR_SEL8_SEL17_MASK                     0x3F00u
#define XBAR_SEL8_SEL17_SHIFT                    8
#define XBAR_SEL8_SEL17_WIDTH                    6
#define XBAR_SEL8_SEL17(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_SEL8_SEL17_SHIFT))&XBAR_SEL8_SEL17_MASK)
/* SEL9 Bit Fields */
#define XBAR_SEL9_SEL18_MASK                     0x3Fu
#define XBAR_SEL9_SEL18_SHIFT                    0
#define XBAR_SEL9_SEL18_WIDTH                    6
#define XBAR_SEL9_SEL18(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_SEL9_SEL18_SHIFT))&XBAR_SEL9_SEL18_MASK)
#define XBAR_SEL9_SEL19_MASK                     0x3F00u
#define XBAR_SEL9_SEL19_SHIFT                    8
#define XBAR_SEL9_SEL19_WIDTH                    6
#define XBAR_SEL9_SEL19(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_SEL9_SEL19_SHIFT))&XBAR_SEL9_SEL19_MASK)
/* SEL10 Bit Fields */
#define XBAR_SEL10_SEL20_MASK                    0x3Fu
#define XBAR_SEL10_SEL20_SHIFT                   0
#define XBAR_SEL10_SEL20_WIDTH                   6
#define XBAR_SEL10_SEL20(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL10_SEL20_SHIFT))&XBAR_SEL10_SEL20_MASK)
#define XBAR_SEL10_SEL21_MASK                    0x3F00u
#define XBAR_SEL10_SEL21_SHIFT                   8
#define XBAR_SEL10_SEL21_WIDTH                   6
#define XBAR_SEL10_SEL21(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL10_SEL21_SHIFT))&XBAR_SEL10_SEL21_MASK)
/* SEL11 Bit Fields */
#define XBAR_SEL11_SEL22_MASK                    0x3Fu
#define XBAR_SEL11_SEL22_SHIFT                   0
#define XBAR_SEL11_SEL22_WIDTH                   6
#define XBAR_SEL11_SEL22(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL11_SEL22_SHIFT))&XBAR_SEL11_SEL22_MASK)
#define XBAR_SEL11_SEL23_MASK                    0x3F00u
#define XBAR_SEL11_SEL23_SHIFT                   8
#define XBAR_SEL11_SEL23_WIDTH                   6
#define XBAR_SEL11_SEL23(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL11_SEL23_SHIFT))&XBAR_SEL11_SEL23_MASK)
/* SEL12 Bit Fields */
#define XBAR_SEL12_SEL24_MASK                    0x3Fu
#define XBAR_SEL12_SEL24_SHIFT                   0
#define XBAR_SEL12_SEL24_WIDTH                   6
#define XBAR_SEL12_SEL24(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL12_SEL24_SHIFT))&XBAR_SEL12_SEL24_MASK)
#define XBAR_SEL12_SEL25_MASK                    0x3F00u
#define XBAR_SEL12_SEL25_SHIFT                   8
#define XBAR_SEL12_SEL25_WIDTH                   6
#define XBAR_SEL12_SEL25(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL12_SEL25_SHIFT))&XBAR_SEL12_SEL25_MASK)
/* SEL13 Bit Fields */
#define XBAR_SEL13_SEL26_MASK                    0x3Fu
#define XBAR_SEL13_SEL26_SHIFT                   0
#define XBAR_SEL13_SEL26_WIDTH                   6
#define XBAR_SEL13_SEL26(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL13_SEL26_SHIFT))&XBAR_SEL13_SEL26_MASK)
#define XBAR_SEL13_SEL27_MASK                    0x3F00u
#define XBAR_SEL13_SEL27_SHIFT                   8
#define XBAR_SEL13_SEL27_WIDTH                   6
#define XBAR_SEL13_SEL27(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL13_SEL27_SHIFT))&XBAR_SEL13_SEL27_MASK)
/* SEL14 Bit Fields */
#define XBAR_SEL14_SEL28_MASK                    0x3Fu
#define XBAR_SEL14_SEL28_SHIFT                   0
#define XBAR_SEL14_SEL28_WIDTH                   6
#define XBAR_SEL14_SEL28(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL14_SEL28_SHIFT))&XBAR_SEL14_SEL28_MASK)
#define XBAR_SEL14_SEL29_MASK                    0x3F00u
#define XBAR_SEL14_SEL29_SHIFT                   8
#define XBAR_SEL14_SEL29_WIDTH                   6
#define XBAR_SEL14_SEL29(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL14_SEL29_SHIFT))&XBAR_SEL14_SEL29_MASK)
/* SEL15 Bit Fields */
#define XBAR_SEL15_SEL30_MASK                    0x3Fu
#define XBAR_SEL15_SEL30_SHIFT                   0
#define XBAR_SEL15_SEL30_WIDTH                   6
#define XBAR_SEL15_SEL30(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL15_SEL30_SHIFT))&XBAR_SEL15_SEL30_MASK)
#define XBAR_SEL15_SEL31_MASK                    0x3F00u
#define XBAR_SEL15_SEL31_SHIFT                   8
#define XBAR_SEL15_SEL31_WIDTH                   6
#define XBAR_SEL15_SEL31(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL15_SEL31_SHIFT))&XBAR_SEL15_SEL31_MASK)
/* SEL16 Bit Fields */
#define XBAR_SEL16_SEL32_MASK                    0x3Fu
#define XBAR_SEL16_SEL32_SHIFT                   0
#define XBAR_SEL16_SEL32_WIDTH                   6
#define XBAR_SEL16_SEL32(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL16_SEL32_SHIFT))&XBAR_SEL16_SEL32_MASK)
#define XBAR_SEL16_SEL33_MASK                    0x3F00u
#define XBAR_SEL16_SEL33_SHIFT                   8
#define XBAR_SEL16_SEL33_WIDTH                   6
#define XBAR_SEL16_SEL33(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL16_SEL33_SHIFT))&XBAR_SEL16_SEL33_MASK)
/* SEL17 Bit Fields */
#define XBAR_SEL17_SEL34_MASK                    0x3Fu
#define XBAR_SEL17_SEL34_SHIFT                   0
#define XBAR_SEL17_SEL34_WIDTH                   6
#define XBAR_SEL17_SEL34(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL17_SEL34_SHIFT))&XBAR_SEL17_SEL34_MASK)
#define XBAR_SEL17_SEL35_MASK                    0x3F00u
#define XBAR_SEL17_SEL35_SHIFT                   8
#define XBAR_SEL17_SEL35_WIDTH                   6
#define XBAR_SEL17_SEL35(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL17_SEL35_SHIFT))&XBAR_SEL17_SEL35_MASK)
/* SEL18 Bit Fields */
#define XBAR_SEL18_SEL36_MASK                    0x3Fu
#define XBAR_SEL18_SEL36_SHIFT                   0
#define XBAR_SEL18_SEL36_WIDTH                   6
#define XBAR_SEL18_SEL36(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL18_SEL36_SHIFT))&XBAR_SEL18_SEL36_MASK)
#define XBAR_SEL18_SEL37_MASK                    0x3F00u
#define XBAR_SEL18_SEL37_SHIFT                   8
#define XBAR_SEL18_SEL37_WIDTH                   6
#define XBAR_SEL18_SEL37(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL18_SEL37_SHIFT))&XBAR_SEL18_SEL37_MASK)
/* SEL19 Bit Fields */
#define XBAR_SEL19_SEL38_MASK                    0x3Fu
#define XBAR_SEL19_SEL38_SHIFT                   0
#define XBAR_SEL19_SEL38_WIDTH                   6
#define XBAR_SEL19_SEL38(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL19_SEL38_SHIFT))&XBAR_SEL19_SEL38_MASK)
#define XBAR_SEL19_SEL39_MASK                    0x3F00u
#define XBAR_SEL19_SEL39_SHIFT                   8
#define XBAR_SEL19_SEL39_WIDTH                   6
#define XBAR_SEL19_SEL39(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL19_SEL39_SHIFT))&XBAR_SEL19_SEL39_MASK)
/* SEL20 Bit Fields */
#define XBAR_SEL20_SEL40_MASK                    0x3Fu
#define XBAR_SEL20_SEL40_SHIFT                   0
#define XBAR_SEL20_SEL40_WIDTH                   6
#define XBAR_SEL20_SEL40(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL20_SEL40_SHIFT))&XBAR_SEL20_SEL40_MASK)
#define XBAR_SEL20_SEL41_MASK                    0x3F00u
#define XBAR_SEL20_SEL41_SHIFT                   8
#define XBAR_SEL20_SEL41_WIDTH                   6
#define XBAR_SEL20_SEL41(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL20_SEL41_SHIFT))&XBAR_SEL20_SEL41_MASK)
/* SEL21 Bit Fields */
#define XBAR_SEL21_SEL42_MASK                    0x3Fu
#define XBAR_SEL21_SEL42_SHIFT                   0
#define XBAR_SEL21_SEL42_WIDTH                   6
#define XBAR_SEL21_SEL42(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL21_SEL42_SHIFT))&XBAR_SEL21_SEL42_MASK)
#define XBAR_SEL21_SEL43_MASK                    0x3F00u
#define XBAR_SEL21_SEL43_SHIFT                   8
#define XBAR_SEL21_SEL43_WIDTH                   6
#define XBAR_SEL21_SEL43(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_SEL21_SEL43_SHIFT))&XBAR_SEL21_SEL43_MASK)
/* CTRL0 Bit Fields */
#define XBAR_CTRL0_DEN0_MASK                     0x1u
#define XBAR_CTRL0_DEN0_SHIFT                    0
#define XBAR_CTRL0_DEN0_WIDTH                    1
#define XBAR_CTRL0_DEN0(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL0_DEN0_SHIFT))&XBAR_CTRL0_DEN0_MASK)
#define XBAR_CTRL0_IEN0_MASK                     0x2u
#define XBAR_CTRL0_IEN0_SHIFT                    1
#define XBAR_CTRL0_IEN0_WIDTH                    1
#define XBAR_CTRL0_IEN0(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL0_IEN0_SHIFT))&XBAR_CTRL0_IEN0_MASK)
#define XBAR_CTRL0_EDGE0_MASK                    0xCu
#define XBAR_CTRL0_EDGE0_SHIFT                   2
#define XBAR_CTRL0_EDGE0_WIDTH                   2
#define XBAR_CTRL0_EDGE0(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL0_EDGE0_SHIFT))&XBAR_CTRL0_EDGE0_MASK)
#define XBAR_CTRL0_STS0_MASK                     0x10u
#define XBAR_CTRL0_STS0_SHIFT                    4
#define XBAR_CTRL0_STS0_WIDTH                    1
#define XBAR_CTRL0_STS0(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL0_STS0_SHIFT))&XBAR_CTRL0_STS0_MASK)
#define XBAR_CTRL0_DEN1_MASK                     0x100u
#define XBAR_CTRL0_DEN1_SHIFT                    8
#define XBAR_CTRL0_DEN1_WIDTH                    1
#define XBAR_CTRL0_DEN1(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL0_DEN1_SHIFT))&XBAR_CTRL0_DEN1_MASK)
#define XBAR_CTRL0_IEN1_MASK                     0x200u
#define XBAR_CTRL0_IEN1_SHIFT                    9
#define XBAR_CTRL0_IEN1_WIDTH                    1
#define XBAR_CTRL0_IEN1(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL0_IEN1_SHIFT))&XBAR_CTRL0_IEN1_MASK)
#define XBAR_CTRL0_EDGE1_MASK                    0xC00u
#define XBAR_CTRL0_EDGE1_SHIFT                   10
#define XBAR_CTRL0_EDGE1_WIDTH                   2
#define XBAR_CTRL0_EDGE1(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL0_EDGE1_SHIFT))&XBAR_CTRL0_EDGE1_MASK)
#define XBAR_CTRL0_STS1_MASK                     0x1000u
#define XBAR_CTRL0_STS1_SHIFT                    12
#define XBAR_CTRL0_STS1_WIDTH                    1
#define XBAR_CTRL0_STS1(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL0_STS1_SHIFT))&XBAR_CTRL0_STS1_MASK)
/* CTRL1 Bit Fields */
#define XBAR_CTRL1_DEN2_MASK                     0x1u
#define XBAR_CTRL1_DEN2_SHIFT                    0
#define XBAR_CTRL1_DEN2_WIDTH                    1
#define XBAR_CTRL1_DEN2(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL1_DEN2_SHIFT))&XBAR_CTRL1_DEN2_MASK)
#define XBAR_CTRL1_IEN2_MASK                     0x2u
#define XBAR_CTRL1_IEN2_SHIFT                    1
#define XBAR_CTRL1_IEN2_WIDTH                    1
#define XBAR_CTRL1_IEN2(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL1_IEN2_SHIFT))&XBAR_CTRL1_IEN2_MASK)
#define XBAR_CTRL1_EDGE2_MASK                    0xCu
#define XBAR_CTRL1_EDGE2_SHIFT                   2
#define XBAR_CTRL1_EDGE2_WIDTH                   2
#define XBAR_CTRL1_EDGE2(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL1_EDGE2_SHIFT))&XBAR_CTRL1_EDGE2_MASK)
#define XBAR_CTRL1_STS2_MASK                     0x10u
#define XBAR_CTRL1_STS2_SHIFT                    4
#define XBAR_CTRL1_STS2_WIDTH                    1
#define XBAR_CTRL1_STS2(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL1_STS2_SHIFT))&XBAR_CTRL1_STS2_MASK)
#define XBAR_CTRL1_DEN3_MASK                     0x100u
#define XBAR_CTRL1_DEN3_SHIFT                    8
#define XBAR_CTRL1_DEN3_WIDTH                    1
#define XBAR_CTRL1_DEN3(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL1_DEN3_SHIFT))&XBAR_CTRL1_DEN3_MASK)
#define XBAR_CTRL1_IEN3_MASK                     0x200u
#define XBAR_CTRL1_IEN3_SHIFT                    9
#define XBAR_CTRL1_IEN3_WIDTH                    1
#define XBAR_CTRL1_IEN3(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL1_IEN3_SHIFT))&XBAR_CTRL1_IEN3_MASK)
#define XBAR_CTRL1_EDGE3_MASK                    0xC00u
#define XBAR_CTRL1_EDGE3_SHIFT                   10
#define XBAR_CTRL1_EDGE3_WIDTH                   2
#define XBAR_CTRL1_EDGE3(x)                      (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL1_EDGE3_SHIFT))&XBAR_CTRL1_EDGE3_MASK)
#define XBAR_CTRL1_STS3_MASK                     0x1000u
#define XBAR_CTRL1_STS3_SHIFT                    12
#define XBAR_CTRL1_STS3_WIDTH                    1
#define XBAR_CTRL1_STS3(x)                       (((uint16_t)(((uint16_t)(x))<<XBAR_CTRL1_STS3_SHIFT))&XBAR_CTRL1_STS3_MASK)

/*!
 * @}
 */ /* end of group XBAR_Register_Masks */


/* XBAR - Peripheral instance base addresses */
/** Peripheral XBAR base address */
#define XBAR_BASE                                (0x40055000u)
/** Peripheral XBAR base pointer */
#define XBAR                                     ((XBAR_Type *)XBAR_BASE)
#define XBAR_BASE_PTR                            (XBAR)
/** Array initializer of XBAR peripheral base addresses */
#define XBAR_BASE_ADDRS                          { XBAR_BASE }
/** Array initializer of XBAR peripheral base pointers */
#define XBAR_BASE_PTRS                           { XBAR }
/** Interrupt vectors for the XBAR peripheral type */
#define XBAR_IRQS                                { XBAR_IRQn }

/* ----------------------------------------------------------------------------
   -- XBAR - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBAR_Register_Accessor_Macros XBAR - Register accessor macros
 * @{
 */


/* XBAR - Register instance definitions */
/* XBAR */
#define XBAR_SEL0                                XBAR_SEL0_REG(XBAR)
#define XBAR_SEL1                                XBAR_SEL1_REG(XBAR)
#define XBAR_SEL2                                XBAR_SEL2_REG(XBAR)
#define XBAR_SEL3                                XBAR_SEL3_REG(XBAR)
#define XBAR_SEL4                                XBAR_SEL4_REG(XBAR)
#define XBAR_SEL5                                XBAR_SEL5_REG(XBAR)
#define XBAR_SEL6                                XBAR_SEL6_REG(XBAR)
#define XBAR_SEL7                                XBAR_SEL7_REG(XBAR)
#define XBAR_SEL8                                XBAR_SEL8_REG(XBAR)
#define XBAR_SEL9                                XBAR_SEL9_REG(XBAR)
#define XBAR_SEL10                               XBAR_SEL10_REG(XBAR)
#define XBAR_SEL11                               XBAR_SEL11_REG(XBAR)
#define XBAR_SEL12                               XBAR_SEL12_REG(XBAR)
#define XBAR_SEL13                               XBAR_SEL13_REG(XBAR)
#define XBAR_SEL14                               XBAR_SEL14_REG(XBAR)
#define XBAR_SEL15                               XBAR_SEL15_REG(XBAR)
#define XBAR_SEL16                               XBAR_SEL16_REG(XBAR)
#define XBAR_SEL17                               XBAR_SEL17_REG(XBAR)
#define XBAR_SEL18                               XBAR_SEL18_REG(XBAR)
#define XBAR_SEL19                               XBAR_SEL19_REG(XBAR)
#define XBAR_SEL20                               XBAR_SEL20_REG(XBAR)
#define XBAR_SEL21                               XBAR_SEL21_REG(XBAR)
#define XBAR_CTRL0                               XBAR_CTRL0_REG(XBAR)
#define XBAR_CTRL1                               XBAR_CTRL1_REG(XBAR)

/*!
 * @}
 */ /* end of group XBAR_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group XBAR_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #pragma pop
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
   -- Backward Compatibility
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Backward_Compatibility_Symbols Backward Compatibility
 * @{
 */

/* No backward compatibility issues. */

/*!
 * @}
 */ /* end of group Backward_Compatibility_Symbols */


#else /* #if !defined(MKM34Z7_H_) */
  /* There is already included the same memory map. Check if it is compatible (has the same major version) */
  #if (MCU_MEM_MAP_VERSION != 0x0100u)
    #if (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING))
      #warning There are included two not compatible versions of memory maps. Please check possible differences.
    #endif /* (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING)) */
  #endif /* (MCU_MEM_MAP_VERSION != 0x0100u) */
#endif  /* #if !defined(MKM34Z7_H_) */

/* MKM34Z7.h, eof. */
