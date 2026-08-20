/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_cmu.h
  * @author  FMSH Application Team
  * @brief   Head file of CMU FL Module
  *******************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  *******************************************************************************************************
  */


/* Define to prevent recursive inclusion---------------------------------------------------------------*/
#ifndef __FM33LG0XX_FL_CMU_H
#define __FM33LG0XX_FL_CMU_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup CMU CMU
  * @brief CMU FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup CMU_FL_ES_INIT CMU Exported Init structures
  * @{
  */

/**
  * @brief FL CMU Init Sturcture definition
  */

typedef enum
{
    FL_SYSTEM_CLOCK_RCHF_8M = 0,
    FL_SYSTEM_CLOCK_RCHF_16M,
    FL_SYSTEM_CLOCK_RCHF_24M,
    FL_SYSTEM_CLOCK_PLL_RCHF_32M,
    FL_SYSTEM_CLOCK_PLL_RCHF_48M,
    FL_SYSTEM_CLOCK_PLL_RCHF_64M,
    FL_SYSTEM_CLOCK_RCLP,
    FL_SYSTEM_CLOCK_RCLF,
    FL_SYSTEM_CLOCK_XTLF,
    FL_SYSTEM_CLOCK_XTHF,
} FL_SystemClock;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup CMU_FL_Exported_Constants CMU Exported Constants
  * @{
  */

#define    CMU_IER_HFDET_IE_Pos                                   (1U)
#define    CMU_IER_HFDET_IE_Msk                                   (0x1U << CMU_IER_HFDET_IE_Pos)
#define    CMU_IER_HFDET_IE                                       CMU_IER_HFDET_IE_Msk

#define    CMU_ISR_HFDETO_Pos                                     (9U)
#define    CMU_ISR_HFDETO_Msk                                     (0x1U << CMU_ISR_HFDETO_Pos)
#define    CMU_ISR_HFDETO                                         CMU_ISR_HFDETO_Msk

#define    CMU_ISR_HFDET_IF_Pos                                   (1U)
#define    CMU_ISR_HFDET_IF_Msk                                   (0x1U << CMU_ISR_HFDET_IF_Pos)
#define    CMU_ISR_HFDET_IF                                       CMU_ISR_HFDET_IF_Msk

#define    CMU_IER_SYSCES_IE_Pos                                  (2U)
#define    CMU_IER_SYSCES_IE_Msk                                  (0x1U << CMU_IER_SYSCES_IE_Pos)
#define    CMU_IER_SYSCES_IE                                      CMU_IER_SYSCES_IE_Msk

#define    CMU_ISR_SYSCES_IF_Pos                                  (2U)
#define    CMU_ISR_SYSCES_IF_Msk                                  (0x1U << CMU_ISR_SYSCES_IF_Pos)
#define    CMU_ISR_SYSCES_IF                                      CMU_ISR_SYSCES_IF_Msk

#define    CMU_SYSCLKCR_LSCATS_Pos                                (27U)
#define    CMU_SYSCLKCR_LSCATS_Msk                                (0x1U << CMU_SYSCLKCR_LSCATS_Pos)
#define    CMU_SYSCLKCR_LSCATS                                    CMU_SYSCLKCR_LSCATS_Msk

#define    CMU_SYSCLKCR_SLP_ENEXTI_Pos                            (25U)
#define    CMU_SYSCLKCR_SLP_ENEXTI_Msk                            (0x1U << CMU_SYSCLKCR_SLP_ENEXTI_Pos)
#define    CMU_SYSCLKCR_SLP_ENEXTI                                CMU_SYSCLKCR_SLP_ENEXTI_Msk

#define    CMU_SYSCLKCR_APBPRES_Pos                               (16U)
#define    CMU_SYSCLKCR_APBPRES_Msk                               (0x7U << CMU_SYSCLKCR_APBPRES_Pos)
#define    CMU_SYSCLKCR_APBPRES                                   CMU_SYSCLKCR_APBPRES_Msk

#define    CMU_SYSCLKCR_AHBPRES_Pos                               (8U)
#define    CMU_SYSCLKCR_AHBPRES_Msk                               (0x7U << CMU_SYSCLKCR_AHBPRES_Pos)
#define    CMU_SYSCLKCR_AHBPRES                                   CMU_SYSCLKCR_AHBPRES_Msk

#define    CMU_SYSCLKCR_STCLKSEL_Pos                              (6U)
#define    CMU_SYSCLKCR_STCLKSEL_Msk                              (0x3U << CMU_SYSCLKCR_STCLKSEL_Pos)
#define    CMU_SYSCLKCR_STCLKSEL                                  CMU_SYSCLKCR_STCLKSEL_Msk

#define    CMU_SYSCLKCR_SYSCLKSEL_Pos                             (0U)
#define    CMU_SYSCLKCR_SYSCLKSEL_Msk                             (0x7U << CMU_SYSCLKCR_SYSCLKSEL_Pos)
#define    CMU_SYSCLKCR_SYSCLKSEL                                 CMU_SYSCLKCR_SYSCLKSEL_Msk

#define    CMU_RCHFCR_FSEL_Pos                                    (16U)
#define    CMU_RCHFCR_FSEL_Msk                                    (0xfU << CMU_RCHFCR_FSEL_Pos)
#define    CMU_RCHFCR_FSEL                                        CMU_RCHFCR_FSEL_Msk

#define    CMU_RCHFCR_EN_Pos                                      (0U)
#define    CMU_RCHFCR_EN_Msk                                      (0x1U << CMU_RCHFCR_EN_Pos)
#define    CMU_RCHFCR_EN                                          CMU_RCHFCR_EN_Msk

#define    CMU_RCHFTR_TRIM_Pos                                    (0U)
#define    CMU_RCHFTR_TRIM_Msk                                    (0xffU << CMU_RCHFTR_TRIM_Pos)
#define    CMU_RCHFTR_TRIM                                        CMU_RCHFTR_TRIM_Msk

#define    CMU_PLLCR_EN_Pos                                       (0U)
#define    CMU_PLLCR_EN_Msk                                       (0x1U << CMU_PLLCR_EN_Pos)
#define    CMU_PLLCR_EN                                           CMU_PLLCR_EN_Msk

#define    CMU_PLLCR_LOCKED_Pos                                   (7U)
#define    CMU_PLLCR_LOCKED_Msk                                   (0x1U << CMU_PLLCR_LOCKED_Pos)
#define    CMU_PLLCR_LOCKED                                       CMU_PLLCR_LOCKED_Msk

#define    CMU_PLLCR_INSEL_Pos                                    (1U)
#define    CMU_PLLCR_INSEL_Msk                                    (0x1U << CMU_PLLCR_INSEL_Pos)
#define    CMU_PLLCR_INSEL                                        CMU_PLLCR_INSEL_Msk

#define    CMU_PLLCR_DB_Pos                                       (16U)
#define    CMU_PLLCR_DB_Msk                                       (0x7fU << CMU_PLLCR_DB_Pos)
#define    CMU_PLLCR_DB                                           CMU_PLLCR_DB_Msk

#define    CMU_PLLCR_REFPRSC_Pos                                  (4U)
#define    CMU_PLLCR_REFPRSC_Msk                                  (0x7U << CMU_PLLCR_REFPRSC_Pos)
#define    CMU_PLLCR_REFPRSC                                      CMU_PLLCR_REFPRSC_Msk

#define    CMU_PLLCR_OSEL_Pos                                     (3U)
#define    CMU_PLLCR_OSEL_Msk                                     (0x1U << CMU_PLLCR_OSEL_Pos)
#define    CMU_PLLCR_OSEL                                         CMU_PLLCR_OSEL_Msk

#define    CMU_RCLPCR_ENB_Pos                                     (0U)
#define    CMU_RCLPCR_ENB_Msk                                     (0x1U << CMU_RCLPCR_ENB_Pos)
#define    CMU_RCLPCR_ENB                                         CMU_RCLPCR_ENB_Msk

#define    CMU_RCLPTR_TRIM_Pos                                    (0U)
#define    CMU_RCLPTR_TRIM_Msk                                    (0xffU << CMU_RCLPTR_TRIM_Pos)
#define    CMU_RCLPTR_TRIM                                        CMU_RCLPTR_TRIM_Msk

#define    CMU_LSCLKSEL_SEL_Pos                                   (0U)
#define    CMU_LSCLKSEL_SEL_Msk                                   (0xffU << CMU_LSCLKSEL_SEL_Pos)
#define    CMU_LSCLKSEL_SEL                                       CMU_LSCLKSEL_SEL_Msk

#define    CMU_XTHFCR_CFG_Pos                                     (8U)
#define    CMU_XTHFCR_CFG_Msk                                     (0x1fU << CMU_XTHFCR_CFG_Pos)
#define    CMU_XTHFCR_CFG                                         CMU_XTHFCR_CFG_Msk

#define    CMU_XTHFCR_EN_Pos                                      (0U)
#define    CMU_XTHFCR_EN_Msk                                      (0x1U << CMU_XTHFCR_EN_Pos)
#define    CMU_XTHFCR_EN                                          CMU_XTHFCR_EN_Msk

#define    CMU_RCLFCR_PSC_Pos                                     (16U)
#define    CMU_RCLFCR_PSC_Msk                                     (0x3U << CMU_RCLFCR_PSC_Pos)
#define    CMU_RCLFCR_PSC                                         CMU_RCLFCR_PSC_Msk

#define    CMU_RCLFCR_EN_Pos                                      (0U)
#define    CMU_RCLFCR_EN_Msk                                      (0x1U << CMU_RCLFCR_EN_Pos)
#define    CMU_RCLFCR_EN                                          CMU_RCLFCR_EN_Msk

#define    CMU_RCLFTR_TRIM_Pos                                    (0U)
#define    CMU_RCLFTR_TRIM_Msk                                    (0xffU << CMU_RCLFTR_TRIM_Pos)
#define    CMU_RCLFTR_TRIM                                        CMU_RCLFTR_TRIM_Msk

#define    CMU_OPCCR1_EXTICKS_Pos                                 (30U)
#define    CMU_OPCCR1_EXTICKS_Msk                                 (0x1U << CMU_OPCCR1_EXTICKS_Pos)
#define    CMU_OPCCR1_EXTICKS                                     CMU_OPCCR1_EXTICKS_Msk

#define    CMU_OPCCR1_LPUART1CKS_Pos                              (26U)
#define    CMU_OPCCR1_LPUART1CKS_Msk                              (0x3U << CMU_OPCCR1_LPUART1CKS_Pos)
#define    CMU_OPCCR1_LPUART1CKS                                  CMU_OPCCR1_LPUART1CKS_Msk

#define    CMU_OPCCR1_LPUART0CKS_Pos                              (24U)
#define    CMU_OPCCR1_LPUART0CKS_Msk                              (0x3U << CMU_OPCCR1_LPUART0CKS_Pos)
#define    CMU_OPCCR1_LPUART0CKS                                  CMU_OPCCR1_LPUART0CKS_Msk

#define    CMU_OPCCR1_LPUART2CKS_Pos                              (22U)
#define    CMU_OPCCR1_LPUART2CKS_Msk                              (0x3U << CMU_OPCCR1_LPUART2CKS_Pos)
#define    CMU_OPCCR1_LPUART2CKS                                  CMU_OPCCR1_LPUART2CKS_Msk

#define    CMU_OPCCR1_I2CCKS_Pos                                  (16U)
#define    CMU_OPCCR1_I2CCKS_Msk                                  (0x3U << CMU_OPCCR1_I2CCKS_Pos)
#define    CMU_OPCCR1_I2CCKS                                      CMU_OPCCR1_I2CCKS_Msk

#define    CMU_OPCCR1_BT16CKS_Pos                                 (14U)
#define    CMU_OPCCR1_BT16CKS_Msk                                 (0x3U << CMU_OPCCR1_BT16CKS_Pos)
#define    CMU_OPCCR1_BT16CKS                                     CMU_OPCCR1_BT16CKS_Msk

#define    CMU_OPCCR1_BT32CKS_Pos                                 (12U)
#define    CMU_OPCCR1_BT32CKS_Msk                                 (0x3U << CMU_OPCCR1_BT32CKS_Pos)
#define    CMU_OPCCR1_BT32CKS                                     CMU_OPCCR1_BT32CKS_Msk

#define    CMU_OPCCR1_LPT16CKS_Pos                                (10U)
#define    CMU_OPCCR1_LPT16CKS_Msk                                (0x3U << CMU_OPCCR1_LPT16CKS_Pos)
#define    CMU_OPCCR1_LPT16CKS                                    CMU_OPCCR1_LPT16CKS_Msk

#define    CMU_OPCCR1_LPT32CKS_Pos                                (8U)
#define    CMU_OPCCR1_LPT32CKS_Msk                                (0x3U << CMU_OPCCR1_LPT32CKS_Pos)
#define    CMU_OPCCR1_LPT32CKS                                    CMU_OPCCR1_LPT32CKS_Msk

#define    CMU_OPCCR1_ATCKS_Pos                                   (7U)
#define    CMU_OPCCR1_ATCKS_Msk                                   (0x1U << CMU_OPCCR1_ATCKS_Pos)
#define    CMU_OPCCR1_ATCKS                                       CMU_OPCCR1_ATCKS_Msk

#define    CMU_OPCCR1_CANCKS_Pos                                  (4U)
#define    CMU_OPCCR1_CANCKS_Msk                                  (0x3U << CMU_OPCCR1_CANCKS_Pos)
#define    CMU_OPCCR1_CANCKS                                      CMU_OPCCR1_CANCKS_Msk

#define    CMU_OPCCR1_UART1CKS_Pos                                (2U)
#define    CMU_OPCCR1_UART1CKS_Msk                                (0x3U << CMU_OPCCR1_UART1CKS_Pos)
#define    CMU_OPCCR1_UART1CKS                                    CMU_OPCCR1_UART1CKS_Msk

#define    CMU_OPCCR1_UART0CKS_Pos                                (0U)
#define    CMU_OPCCR1_UART0CKS_Msk                                (0x3U << CMU_OPCCR1_UART0CKS_Pos)
#define    CMU_OPCCR1_UART0CKS                                    CMU_OPCCR1_UART0CKS_Msk

#define    CMU_OPCCR2_RNGPRSC_Pos                                 (10U)
#define    CMU_OPCCR2_RNGPRSC_Msk                                 (0x7U << CMU_OPCCR2_RNGPRSC_Pos)
#define    CMU_OPCCR2_RNGPRSC                                     CMU_OPCCR2_RNGPRSC_Msk

#define    CMU_OPCCR2_ADCPRSC_Pos                                 (2U)
#define    CMU_OPCCR2_ADCPRSC_Msk                                 (0x7U << CMU_OPCCR2_ADCPRSC_Pos)
#define    CMU_OPCCR2_ADCPRSC                                     CMU_OPCCR2_ADCPRSC_Msk

#define    CMU_OPCCR2_ADCCKS_Pos                                  (0U)
#define    CMU_OPCCR2_ADCCKS_Msk                                  (0x3U << CMU_OPCCR2_ADCCKS_Pos)
#define    CMU_OPCCR2_ADCCKS                                      CMU_OPCCR2_ADCCKS_Msk

#define    CMU_CCCR_CCLIE_Pos                                     (1U)
#define    CMU_CCCR_CCLIE_Msk                                     (0x1U << CMU_CCCR_CCLIE_Pos)
#define    CMU_CCCR_CCLIE                                         CMU_CCCR_CCLIE_Msk

#define    CMU_CCCR_EN_Pos                                        (0U)
#define    CMU_CCCR_EN_Msk                                        (0x1U << CMU_CCCR_EN_Pos)
#define    CMU_CCCR_EN                                            CMU_CCCR_EN_Msk

#define    CMU_CCFR_CALPSC_Pos                                    (10U)
#define    CMU_CCFR_CALPSC_Msk                                    (0x3U << CMU_CCFR_CALPSC_Pos)
#define    CMU_CCFR_CALPSC                                        CMU_CCFR_CALPSC_Msk

#define    CMU_CCFR_REFPSC_Pos                                    (8U)
#define    CMU_CCFR_REFPSC_Msk                                    (0x3U << CMU_CCFR_REFPSC_Pos)
#define    CMU_CCFR_REFPSC                                        CMU_CCFR_REFPSC_Msk

#define    CMU_CCFR_CALSEL_Pos                                    (1U)
#define    CMU_CCFR_CALSEL_Msk                                    (0x3U << CMU_CCFR_CALSEL_Pos)
#define    CMU_CCFR_CALSEL                                        CMU_CCFR_CALSEL_Msk

#define    CMU_CCFR_REFSEL_Pos                                    (0U)
#define    CMU_CCFR_REFSEL_Msk                                    (0x1U << CMU_CCFR_REFSEL_Pos)
#define    CMU_CCFR_REFSEL                                        CMU_CCFR_REFSEL_Msk

#define    CMU_CCNR_CCNT_Pos                                      (0U)
#define    CMU_CCNR_CCNT_Msk                                      (0xffffU << CMU_CCNR_CCNT_Pos)
#define    CMU_CCNR_CCNT                                          CMU_CCNR_CCNT_Msk

#define    CMU_CCISR_CCLIF_Pos                                    (0U)
#define    CMU_CCISR_CCLIF_Msk                                    (0x1U << CMU_CCISR_CCLIF_Pos)
#define    CMU_CCISR_CCLIF                                        CMU_CCISR_CCLIF_Msk



#define    FL_CMU_GROUP1_BUSCLK_LPTIM32                           (0x1U << 0U)
#define    FL_CMU_GROUP1_BUSCLK_LPTIM16                           (0x1U << 1U)
#define    FL_CMU_GROUP1_BUSCLK_RTCA                              (0x1U << 2U)
#define    FL_CMU_GROUP1_BUSCLK_PMU                               (0x1U << 3U)
#define    FL_CMU_GROUP1_BUSCLK_SCU                               (0x1U << 4U)
#define    FL_CMU_GROUP1_BUSCLK_IWDT                              (0x1U << 5U)
#define    FL_CMU_GROUP1_BUSCLK_ANAC                              (0x1U << 6U)
#define    FL_CMU_GROUP1_BUSCLK_PAD                               (0x1U << 7U)
#define    FL_CMU_GROUP1_BUSCLK_SVD                               (0x1U << 8U)
#define    FL_CMU_GROUP1_BUSCLK_COMP                              (0x1U << 9U)
#define    FL_CMU_GROUP1_BUSCLK_ATT                               (0x1U << 10U)
#define    FL_CMU_GROUP1_BUSCLK_OPA                               (0x1U << 11U)
#define    FL_CMU_GROUP1_BUSCLK_VREF1P2                           (0x1U << 12U)
#define    FL_CMU_GROUP2_BUSCLK_CRC                               (0x1U << 0U)
#define    FL_CMU_GROUP2_BUSCLK_RNG                               (0x1U << 1U)
#define    FL_CMU_GROUP2_BUSCLK_AES                               (0x1U << 2U)
#define    FL_CMU_GROUP2_BUSCLK_LCD                               (0x1U << 3U)
#define    FL_CMU_GROUP2_BUSCLK_DMA                               (0x1U << 4U)
#define    FL_CMU_GROUP2_BUSCLK_FLASH                             (0x1U << 5U)
#define    FL_CMU_GROUP2_BUSCLK_RAMBIST                           (0x1U << 6U)
#define    FL_CMU_GROUP2_BUSCLK_WWDT                              (0x1U << 7U)
#define    FL_CMU_GROUP2_BUSCLK_ADC                               (0x1U << 8U)
#define    FL_CMU_GROUP2_BUSCLK_DIVAS                             (0x1U << 9U)
#define    FL_CMU_GROUP2_BUSCLK_DAC                               (0x1U << 10U)
#define    FL_CMU_GROUP2_BUSCLK_PGL                               (0x1U << 11U)
#define    FL_CMU_GROUP3_BUSCLK_SPI0                              (0x1U << 0U)
#define    FL_CMU_GROUP3_BUSCLK_SPI1                              (0x1U << 1U)
#define    FL_CMU_GROUP3_BUSCLK_SPI2                              (0x1U << 2U)
#define    FL_CMU_GROUP3_BUSCLK_UART0                             (0x1U << 8U)
#define    FL_CMU_GROUP3_BUSCLK_UART1                             (0x1U << 9U)
#define    FL_CMU_GROUP3_BUSCLK_UART3                             (0x1U << 11U)
#define    FL_CMU_GROUP3_BUSCLK_UART4                             (0x1U << 12U)
#define    FL_CMU_GROUP3_BUSCLK_UART5                             (0x1U << 13U)
#define    FL_CMU_GROUP3_BUSCLK_UARTIR                            (0x1U << 14U)
#define    FL_CMU_GROUP3_BUSCLK_U7816                             (0x1U << 15U)
#define    FL_CMU_GROUP3_BUSCLK_LPUART0                           (0x1U << 16U)
#define    FL_CMU_GROUP3_BUSCLK_LPUART1                           (0x1U << 17U)
#define    FL_CMU_GROUP3_BUSCLK_LPUART2                           (0x1U << 18U)
#define    FL_CMU_GROUP3_BUSCLK_CAN                               (0x1U << 19U)
#define    FL_CMU_GROUP3_BUSCLK_I2C                               (0x1U << 24U)
#define    FL_CMU_GROUP4_BUSCLK_BSTIM32                           (0x1U << 0U)
#define    FL_CMU_GROUP4_BUSCLK_GPTIM0                            (0x1U << 1U)
#define    FL_CMU_GROUP4_BUSCLK_GPTIM1                            (0x1U << 2U)
#define    FL_CMU_GROUP4_BUSCLK_GPTIM2                            (0x1U << 3U)
#define    FL_CMU_GROUP4_BUSCLK_ATIM                              (0x1U << 4U)
#define    FL_CMU_GROUP4_BUSCLK_BSTIM16                           (0x1U << 8U)
#define    FL_CMU_GROUP3_OPCLK_EXTI                               (0x1U << 31U)
#define    FL_CMU_GROUP3_OPCLK_FLASH                              (0x1U << 30U)
#define    FL_CMU_GROUP3_OPCLK_LPUART1                            (0x1U << 29U)
#define    FL_CMU_GROUP3_OPCLK_LPUART0                            (0x1U << 28U)
#define    FL_CMU_GROUP3_OPCLK_RNG                                (0x1U << 24U)
#define    FL_CMU_GROUP3_OPCLK_LPUART2                            (0x1U << 21U)
#define    FL_CMU_GROUP3_OPCLK_I2C                                (0x1U << 20U)
#define    FL_CMU_GROUP3_OPCLK_ADC                                (0x1U << 16U)
#define    FL_CMU_GROUP3_OPCLK_ATIM                               (0x1U << 15U)
#define    FL_CMU_GROUP3_OPCLK_CAN                                (0x1U << 14U)
#define    FL_CMU_GROUP3_OPCLK_UART1                              (0x1U << 9U)
#define    FL_CMU_GROUP3_OPCLK_UART0                              (0x1U << 8U)
#define    FL_CMU_GROUP3_OPCLK_BSTIM16                            (0x1U << 3U)
#define    FL_CMU_GROUP3_OPCLK_BSTIM32                            (0x1U << 2U)
#define    FL_CMU_GROUP3_OPCLK_LPTIM16                            (0x1U << 1U)
#define    FL_CMU_GROUP3_OPCLK_LPTIM32                            (0x1U << 0U)



#define    FL_CMU_APBCLK_PSC_DIV1                                 (0x0U << CMU_SYSCLKCR_APBPRES_Pos)
#define    FL_CMU_APBCLK_PSC_DIV2                                 (0x4U << CMU_SYSCLKCR_APBPRES_Pos)
#define    FL_CMU_APBCLK_PSC_DIV4                                 (0x5U << CMU_SYSCLKCR_APBPRES_Pos)
#define    FL_CMU_APBCLK_PSC_DIV8                                 (0x6U << CMU_SYSCLKCR_APBPRES_Pos)
#define    FL_CMU_APBCLK_PSC_DIV16                                (0x7U << CMU_SYSCLKCR_APBPRES_Pos)


#define    FL_CMU_AHBCLK_PSC_DIV1                                 (0x0U << CMU_SYSCLKCR_AHBPRES_Pos)
#define    FL_CMU_AHBCLK_PSC_DIV2                                 (0x4U << CMU_SYSCLKCR_AHBPRES_Pos)
#define    FL_CMU_AHBCLK_PSC_DIV4                                 (0x5U << CMU_SYSCLKCR_AHBPRES_Pos)
#define    FL_CMU_AHBCLK_PSC_DIV8                                 (0x6U << CMU_SYSCLKCR_AHBPRES_Pos)
#define    FL_CMU_AHBCLK_PSC_DIV16                                (0x7U << CMU_SYSCLKCR_AHBPRES_Pos)


#define    FL_CMU_SYSTICK_CLK_SOURCE_SCLK                         (0x0U << CMU_SYSCLKCR_STCLKSEL_Pos)
#define    FL_CMU_SYSTICK_CLK_SOURCE_LSCLK                        (0x1U << CMU_SYSCLKCR_STCLKSEL_Pos)
#define    FL_CMU_SYSTICK_CLK_SOURCE_RCLF                         (0x2U << CMU_SYSCLKCR_STCLKSEL_Pos)
#define    FL_CMU_SYSTICK_CLK_SOURCE_SYSCLK                       (0x3U << CMU_SYSCLKCR_STCLKSEL_Pos)


#define    FL_CMU_SYSTEM_CLK_SOURCE_RCHF                          (0x0U << CMU_SYSCLKCR_SYSCLKSEL_Pos)
#define    FL_CMU_SYSTEM_CLK_SOURCE_XTHF                          (0x1U << CMU_SYSCLKCR_SYSCLKSEL_Pos)
#define    FL_CMU_SYSTEM_CLK_SOURCE_PLL                           (0x2U << CMU_SYSCLKCR_SYSCLKSEL_Pos)
#define    FL_CMU_SYSTEM_CLK_SOURCE_RCLF                          (0x4U << CMU_SYSCLKCR_SYSCLKSEL_Pos)
#define    FL_CMU_SYSTEM_CLK_SOURCE_XTLF                          (0x5U << CMU_SYSCLKCR_SYSCLKSEL_Pos)
#define    FL_CMU_SYSTEM_CLK_SOURCE_RCLP                          (0x6U << CMU_SYSCLKCR_SYSCLKSEL_Pos)


#define    FL_CMU_RCHF_FREQUENCY_8MHZ                             (0x0U << CMU_RCHFCR_FSEL_Pos)
#define    FL_CMU_RCHF_FREQUENCY_16MHZ                            (0x1U << CMU_RCHFCR_FSEL_Pos)
#define    FL_CMU_RCHF_FREQUENCY_24MHZ                            (0x2U << CMU_RCHFCR_FSEL_Pos)
#define    FL_CMU_RCHF_FREQUENCY_32MHZ                            (0x3U << CMU_RCHFCR_FSEL_Pos)


#define    FL_CMU_PLL_CLK_SOURCE_RCHF                             (0x0U << CMU_PLLCR_INSEL_Pos)
#define    FL_CMU_PLL_CLK_SOURCE_XTHF                             (0x1U << CMU_PLLCR_INSEL_Pos)


#define    FL_CMU_PLL_PSC_DIV1                                    (0x0U << CMU_PLLCR_REFPRSC_Pos)
#define    FL_CMU_PLL_PSC_DIV2                                    (0x1U << CMU_PLLCR_REFPRSC_Pos)
#define    FL_CMU_PLL_PSC_DIV4                                    (0x2U << CMU_PLLCR_REFPRSC_Pos)
#define    FL_CMU_PLL_PSC_DIV8                                    (0x3U << CMU_PLLCR_REFPRSC_Pos)
#define    FL_CMU_PLL_PSC_DIV12                                   (0x4U << CMU_PLLCR_REFPRSC_Pos)
#define    FL_CMU_PLL_PSC_DIV16                                   (0x5U << CMU_PLLCR_REFPRSC_Pos)
#define    FL_CMU_PLL_PSC_DIV24                                   (0x6U << CMU_PLLCR_REFPRSC_Pos)
#define    FL_CMU_PLL_PSC_DIV32                                   (0x7U << CMU_PLLCR_REFPRSC_Pos)


#define    FL_CMU_PLL_OUTPUT_X1                                   (0x0U << CMU_PLLCR_OSEL_Pos)
#define    FL_CMU_PLL_OUTPUT_X2                                   (0x1U << CMU_PLLCR_OSEL_Pos)


#define    FL_CMU_LSCLK_CLK_SOURCE_RCLP                           (0x55U << CMU_LSCLKSEL_SEL_Pos)
#define    FL_CMU_LSCLK_CLK_SOURCE_XTLF                           (0xAAU << CMU_LSCLKSEL_SEL_Pos)

#define    FL_CMU_RCLF_PSC_DIV1                                   (0x0U << CMU_RCLFCR_PSC_Pos)
#define    FL_CMU_RCLF_PSC_DIV4                                   (0x1U << CMU_RCLFCR_PSC_Pos)
#define    FL_CMU_RCLF_PSC_DIV8                                   (0x2U << CMU_RCLFCR_PSC_Pos)
#define    FL_CMU_RCLF_PSC_DIV16                                  (0x3U << CMU_RCLFCR_PSC_Pos)


#define    FL_CMU_EXTI_CLK_SOURCE_LSCLK                           (0x1U << CMU_OPCCR1_EXTICKS_Pos)
#define    FL_CMU_EXTI_CLK_SOURCE_HCLK                            (0x0U << CMU_OPCCR1_EXTICKS_Pos)


#define    FL_CMU_LPUART1_CLK_SOURCE_LSCLK                        (0x0U << CMU_OPCCR1_LPUART1CKS_Pos)
#define    FL_CMU_LPUART1_CLK_SOURCE_RCHF                         (0x1U << CMU_OPCCR1_LPUART1CKS_Pos)
#define    FL_CMU_LPUART1_CLK_SOURCE_RCLF                         (0x2U << CMU_OPCCR1_LPUART1CKS_Pos)


#define    FL_CMU_LPUART0_CLK_SOURCE_LSCLK                        (0x0U << CMU_OPCCR1_LPUART0CKS_Pos)
#define    FL_CMU_LPUART0_CLK_SOURCE_RCHF                         (0x1U << CMU_OPCCR1_LPUART0CKS_Pos)
#define    FL_CMU_LPUART0_CLK_SOURCE_RCLF                         (0x2U << CMU_OPCCR1_LPUART0CKS_Pos)


#define    FL_CMU_LPUART2_CLK_SOURCE_LSCLK                        (0x0U << CMU_OPCCR1_LPUART2CKS_Pos)
#define    FL_CMU_LPUART2_CLK_SOURCE_RCHF                         (0x1U << CMU_OPCCR1_LPUART2CKS_Pos)
#define    FL_CMU_LPUART2_CLK_SOURCE_RCLF                         (0x2U << CMU_OPCCR1_LPUART2CKS_Pos)

#define    FL_CMU_LPUART_CLK_SOURCE_LSCLK                         (0x0U)
#define    FL_CMU_LPUART_CLK_SOURCE_RCHF                          (0x1U)
#define    FL_CMU_LPUART_CLK_SOURCE_RCLF                          (0x2U)


#define    FL_CMU_I2C_CLK_SOURCE_APBCLK                           (0x0U << CMU_OPCCR1_I2CCKS_Pos)
#define    FL_CMU_I2C_CLK_SOURCE_RCHF                             (0x1U << CMU_OPCCR1_I2CCKS_Pos)
#define    FL_CMU_I2C_CLK_SOURCE_SYSCLK                           (0x2U << CMU_OPCCR1_I2CCKS_Pos)
#define    FL_CMU_I2C_CLK_SOURCE_RCLF                             (0x3U << CMU_OPCCR1_I2CCKS_Pos)


#define    FL_CMU_BSTIM16_CLK_SOURCE_APBCLK                       (0x0U << CMU_OPCCR1_BT16CKS_Pos)
#define    FL_CMU_BSTIM16_CLK_SOURCE_LSCLK                        (0x1U << CMU_OPCCR1_BT16CKS_Pos)
#define    FL_CMU_BSTIM16_CLK_SOURCE_RCLP                         (0x2U << CMU_OPCCR1_BT16CKS_Pos)
#define    FL_CMU_BSTIM16_CLK_SOURCE_RCLF                         (0x3U << CMU_OPCCR1_BT16CKS_Pos)


#define    FL_CMU_BSTIM32_CLK_SOURCE_APBCLK                       (0x0U << CMU_OPCCR1_BT32CKS_Pos)
#define    FL_CMU_BSTIM32_CLK_SOURCE_LSCLK                        (0x1U << CMU_OPCCR1_BT32CKS_Pos)
#define    FL_CMU_BSTIM32_CLK_SOURCE_RCLP                         (0x2U << CMU_OPCCR1_BT32CKS_Pos)
#define    FL_CMU_BSTIM32_CLK_SOURCE_RCLF                         (0x3U << CMU_OPCCR1_BT32CKS_Pos)


#define    FL_CMU_LPTIM16_CLK_SOURCE_APBCLK                       (0x0U << CMU_OPCCR1_LPT16CKS_Pos)
#define    FL_CMU_LPTIM16_CLK_SOURCE_LSCLK                        (0x1U << CMU_OPCCR1_LPT16CKS_Pos)
#define    FL_CMU_LPTIM16_CLK_SOURCE_RCLP                         (0x2U << CMU_OPCCR1_LPT16CKS_Pos)
#define    FL_CMU_LPTIM16_CLK_SOURCE_RCLF                         (0x3U << CMU_OPCCR1_LPT16CKS_Pos)


#define    FL_CMU_LPTIM32_CLK_SOURCE_APBCLK                       (0x0U << CMU_OPCCR1_LPT32CKS_Pos)
#define    FL_CMU_LPTIM32_CLK_SOURCE_LSCLK                        (0x1U << CMU_OPCCR1_LPT32CKS_Pos)
#define    FL_CMU_LPTIM32_CLK_SOURCE_RCLP                         (0x2U << CMU_OPCCR1_LPT32CKS_Pos)
#define    FL_CMU_LPTIM32_CLK_SOURCE_RCLF                         (0x3U << CMU_OPCCR1_LPT32CKS_Pos)


#define    FL_CMU_ATIM_CLK_SOURCE_APBCLK                          (0x0U << CMU_OPCCR1_ATCKS_Pos)
#define    FL_CMU_ATIM_CLK_SOURCE_PLL_X2                          (0x1U << CMU_OPCCR1_ATCKS_Pos)


#define    FL_CMU_CAN_CLK_SOURCE_RCHF                             (0x0U << CMU_OPCCR1_CANCKS_Pos)
#define    FL_CMU_CAN_CLK_SOURCE_XTHF                             (0x1U << CMU_OPCCR1_CANCKS_Pos)
#define    FL_CMU_CAN_CLK_SOURCE_PLL                              (0x2U << CMU_OPCCR1_CANCKS_Pos)
#define    FL_CMU_CAN_CLK_SOURCE_APBCLK                           (0x3U << CMU_OPCCR1_CANCKS_Pos)


#define    FL_CMU_UART1_CLK_SOURCE_APBCLK                         (0x0U << CMU_OPCCR1_UART1CKS_Pos)
#define    FL_CMU_UART1_CLK_SOURCE_RCHF                           (0x1U << CMU_OPCCR1_UART1CKS_Pos)
#define    FL_CMU_UART1_CLK_SOURCE_SYSCLK                         (0x2U << CMU_OPCCR1_UART1CKS_Pos)
#define    FL_CMU_UART1_CLK_SOURCE_XTHF                           (0x3U << CMU_OPCCR1_UART1CKS_Pos)


#define    FL_CMU_UART0_CLK_SOURCE_APBCLK                         (0x0U << CMU_OPCCR1_UART0CKS_Pos)
#define    FL_CMU_UART0_CLK_SOURCE_RCHF                           (0x1U << CMU_OPCCR1_UART0CKS_Pos)
#define    FL_CMU_UART0_CLK_SOURCE_SYSCLK                         (0x2U << CMU_OPCCR1_UART0CKS_Pos)
#define    FL_CMU_UART0_CLK_SOURCE_XTHF                           (0x3U << CMU_OPCCR1_UART0CKS_Pos)


#define    FL_CMU_RNG_PSC_DIV1                                    (0x0U << CMU_OPCCR2_RNGPRSC_Pos)
#define    FL_CMU_RNG_PSC_DIV2                                    (0x1U << CMU_OPCCR2_RNGPRSC_Pos)
#define    FL_CMU_RNG_PSC_DIV4                                    (0x2U << CMU_OPCCR2_RNGPRSC_Pos)
#define    FL_CMU_RNG_PSC_DIV8                                    (0x3U << CMU_OPCCR2_RNGPRSC_Pos)
#define    FL_CMU_RNG_PSC_DIV16                                   (0x4U << CMU_OPCCR2_RNGPRSC_Pos)
#define    FL_CMU_RNG_PSC_DIV32                                   (0x5U << CMU_OPCCR2_RNGPRSC_Pos)


#define    FL_CMU_ADC_PSC_DIV1                                    (0x0U << CMU_OPCCR2_ADCPRSC_Pos)
#define    FL_CMU_ADC_PSC_DIV2                                    (0x1U << CMU_OPCCR2_ADCPRSC_Pos)
#define    FL_CMU_ADC_PSC_DIV4                                    (0x2U << CMU_OPCCR2_ADCPRSC_Pos)
#define    FL_CMU_ADC_PSC_DIV8                                    (0x3U << CMU_OPCCR2_ADCPRSC_Pos)
#define    FL_CMU_ADC_PSC_DIV16                                   (0x4U << CMU_OPCCR2_ADCPRSC_Pos)
#define    FL_CMU_ADC_PSC_DIV32                                   (0x5U << CMU_OPCCR2_ADCPRSC_Pos)


#define    FL_CMU_ADC_CLK_SOURCE_RCLF                             (0x0U << CMU_OPCCR2_ADCCKS_Pos)
#define    FL_CMU_ADC_CLK_SOURCE_RCHF                             (0x1U << CMU_OPCCR2_ADCCKS_Pos)
#define    FL_CMU_ADC_CLK_SOURCE_XTHF                             (0x2U << CMU_OPCCR2_ADCCKS_Pos)
#define    FL_CMU_ADC_CLK_SOURCE_PLL                              (0x3U << CMU_OPCCR2_ADCCKS_Pos)
#define    FL_ADC_CLK_SOURCE_APBCLK                               (0x1U << ADC_CFGR1_CLKSEL_Pos)

#define    FL_CMU_CCL_CALCLK_PSC_DIV1                             (0x0U << CMU_CCFR_CALPSC_Pos)
#define    FL_CMU_CCL_CALCLK_PSC_DIV2                             (0x1U << CMU_CCFR_CALPSC_Pos)
#define    FL_CMU_CCL_CALCLK_PSC_DIV4                             (0x2U << CMU_CCFR_CALPSC_Pos)
#define    FL_CMU_CCL_CALCLK_PSC_DIV8                             (0x3U << CMU_CCFR_CALPSC_Pos)


#define    FL_CMU_CCL_REFCLK_PSC_DIV8                             (0x0U << CMU_CCFR_REFPSC_Pos)
#define    FL_CMU_CCL_REFCLK_PSC_DIV16                            (0x1U << CMU_CCFR_REFPSC_Pos)
#define    FL_CMU_CCL_REFCLK_PSC_DIV32                            (0x2U << CMU_CCFR_REFPSC_Pos)
#define    FL_CMU_CCL_REFCLK_PSC_DIV64                            (0x3U << CMU_CCFR_REFPSC_Pos)


#define    FL_CMU_CCL_CALCLK_SOURCE_RCHF                          (0x1U << CMU_CCFR_CALSEL_Pos)
#define    FL_CMU_CCL_CALCLK_SOURCE_RCLF                          (0x2U << CMU_CCFR_CALSEL_Pos)
#define    FL_CMU_CCL_CALCLK_SOURCE_XTHF                          (0x3U << CMU_CCFR_CALSEL_Pos)


#define    FL_CMU_CCL_REFCLK_SOURCE_XTLF                          (0x0U << CMU_CCFR_REFSEL_Pos)
#define    FL_CMU_CCL_REFCLK_SOURCE_RCLP                          (0x1U << CMU_CCFR_REFSEL_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup CMU_FL_Exported_Functions CMU Exported Functions
  * @{
  */

/**
  * @brief    Enable XTHF Fail Interrupt
  * @rmtoll   IER    HFDET_IE    FL_CMU_EnableIT_XTHFFail
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_EnableIT_XTHFFail(void)
{
    SET_BIT(CMU->IER, CMU_IER_HFDET_IE_Msk);
}

/**
  * @brief    Get XTHF Fail Interrupt Enable Status
  * @rmtoll   IER    HFDET_IE    FL_CMU_IsEnabledIT_XTHFFail
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsEnabledIT_XTHFFail(void)
{
    return (uint32_t)(READ_BIT(CMU->IER, CMU_IER_HFDET_IE_Msk) == CMU_IER_HFDET_IE_Msk);
}

/**
  * @brief    Disable XTHF Fail Interrupt
  * @rmtoll   IER    HFDET_IE    FL_CMU_DisableIT_XTHFFail
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_DisableIT_XTHFFail(void)
{
    CLEAR_BIT(CMU->IER, CMU_IER_HFDET_IE_Msk);
}

/**
  * @brief    Get XTHF Vibrating Output
  * @rmtoll   ISR    HFDETO    FL_CMU_IsActiveFlag_XTHFFailOutput
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsActiveFlag_XTHFFailOutput(void)
{
    return (uint32_t)(READ_BIT(CMU->ISR, CMU_ISR_HFDETO_Msk) == (CMU_ISR_HFDETO_Msk));
}

/**
  * @brief    Get XTHF Vibrating Flag
  * @rmtoll   ISR    HFDET_IF    FL_CMU_IsActiveFlag_XTHFFail
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsActiveFlag_XTHFFail(void)
{
    return (uint32_t)(READ_BIT(CMU->ISR, CMU_ISR_HFDET_IF_Msk) == (CMU_ISR_HFDET_IF_Msk));
}

/**
  * @brief    Clear XTHF Vibrating Flag
  * @rmtoll   ISR    HFDET_IF    FL_CMU_ClearFlag_XTHFFail
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_ClearFlag_XTHFFail(void)
{
    WRITE_REG(CMU->ISR, CMU_ISR_HFDET_IF_Msk);
}

/**
  * @brief    Enable SYSCLK select Fail Interrupt
  * @rmtoll   IER    SYSCES_IE    FL_CMU_EnableIT_SYSCLKSELError
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_EnableIT_SYSCLKSELError(void)
{
    SET_BIT(CMU->IER, CMU_IER_SYSCES_IE_Msk);
}

/**
  * @brief    Get SYSCLK select Fail Interrupt Enable Status
  * @rmtoll   IER    SYSCES_IE    FL_CMU_IsEnabledIT_SYSCLKSELError
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsEnabledIT_SYSCLKSELError(void)
{
    return (uint32_t)(READ_BIT(CMU->IER, CMU_IER_SYSCES_IE_Msk) == CMU_IER_SYSCES_IE_Msk);
}

/**
  * @brief    Disable SYSCLK select Fail Interrupt
  * @rmtoll   IER    SYSCES_IE    FL_CMU_DisableIT_SYSCLKSELError
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_DisableIT_SYSCLKSELError(void)
{
    CLEAR_BIT(CMU->IER, CMU_IER_SYSCES_IE_Msk);
}

/**
  * @brief    Get SYSCLK select Vibrating Flag
  * @rmtoll   ISR    SYSCES_IF    FL_CMU_IsActiveFlag_SYSCLKSELError
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsActiveFlag_SYSCLKSELError(void)
{
    return (uint32_t)(READ_BIT(CMU->ISR, CMU_ISR_SYSCES_IF_Msk) == (CMU_ISR_SYSCES_IF_Msk));
}

/**
  * @brief    Clear SYSCLK select Vibrating Flag
  * @rmtoll   ISR    SYSCES_IF    FL_CMU_ClearFlag_SYSCLKSELError
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_ClearFlag_SYSCLKSELError(void)
{
    WRITE_REG(CMU->ISR, CMU_ISR_SYSCES_IF_Msk);
}

/**
  * @brief    Enable LSCLK Auto Switch
  * @rmtoll   SYSCLKCR    LSCATS    FL_CMU_EnableLSCLKAutoSwitch
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_EnableLSCLKAutoSwitch(void)
{
    SET_BIT(CMU->SYSCLKCR, CMU_SYSCLKCR_LSCATS_Msk);
}

/**
  * @brief    Get LSCLK Auto Switch Enable Status
  * @rmtoll   SYSCLKCR    LSCATS    FL_CMU_IsEnabledLSCLKAutoSwitch
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsEnabledLSCLKAutoSwitch(void)
{
    return (uint32_t)(READ_BIT(CMU->SYSCLKCR, CMU_SYSCLKCR_LSCATS_Msk) == CMU_SYSCLKCR_LSCATS_Msk);
}

/**
  * @brief    Disable LSCLK Auto Switch
  * @rmtoll   SYSCLKCR    LSCATS    FL_CMU_DisableLSCLKAutoSwitch
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_DisableLSCLKAutoSwitch(void)
{
    CLEAR_BIT(CMU->SYSCLKCR, CMU_SYSCLKCR_LSCATS_Msk);
}

/**
  * @brief    Enable Sleep/DeepSleep Mode External Interrupt
  * @rmtoll   SYSCLKCR    SLP_ENEXTI    FL_CMU_EnableEXTIOnSleep
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_EnableEXTIOnSleep(void)
{
    SET_BIT(CMU->SYSCLKCR, CMU_SYSCLKCR_SLP_ENEXTI_Msk);
}

/**
  * @brief    Get Sleep/DeepSleep Mode External Interrupt Enable Status
  * @rmtoll   SYSCLKCR    SLP_ENEXTI    FL_CMU_IsEnabledEXTIOnSleep
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsEnabledEXTIOnSleep(void)
{
    return (uint32_t)(READ_BIT(CMU->SYSCLKCR, CMU_SYSCLKCR_SLP_ENEXTI_Msk) == CMU_SYSCLKCR_SLP_ENEXTI_Msk);
}

/**
  * @brief    Disable Sleep/DeepSleep Mode External Interrupt
  * @rmtoll   SYSCLKCR    SLP_ENEXTI    FL_CMU_DisableEXTIOnSleep
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_DisableEXTIOnSleep(void)
{
    CLEAR_BIT(CMU->SYSCLKCR, CMU_SYSCLKCR_SLP_ENEXTI_Msk);
}

/**
  * @brief    Set APB Prescaler
  * @rmtoll   SYSCLKCR    APBPRES    FL_CMU_SetAPBPrescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_CMU_APBCLK_PSC_DIV1
  *           @arg @ref FL_CMU_APBCLK_PSC_DIV2
  *           @arg @ref FL_CMU_APBCLK_PSC_DIV4
  *           @arg @ref FL_CMU_APBCLK_PSC_DIV8
  *           @arg @ref FL_CMU_APBCLK_PSC_DIV16
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetAPBPrescaler(uint32_t prescaler)
{
    MODIFY_REG(CMU->SYSCLKCR, CMU_SYSCLKCR_APBPRES_Msk, prescaler);
}

/**
  * @brief    Get APB Prescaler
  * @rmtoll   SYSCLKCR    APBPRES    FL_CMU_GetAPBPrescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_APBCLK_PSC_DIV1
  *           @arg @ref FL_CMU_APBCLK_PSC_DIV2
  *           @arg @ref FL_CMU_APBCLK_PSC_DIV4
  *           @arg @ref FL_CMU_APBCLK_PSC_DIV8
  *           @arg @ref FL_CMU_APBCLK_PSC_DIV16
  */
__STATIC_INLINE uint32_t FL_CMU_GetAPBPrescaler(void)
{
    return (uint32_t)(READ_BIT(CMU->SYSCLKCR, CMU_SYSCLKCR_APBPRES_Msk));
}

/**
  * @brief    Set AHB Prescaler
  * @rmtoll   SYSCLKCR    AHBPRES    FL_CMU_SetAHBPrescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_CMU_AHBCLK_PSC_DIV1
  *           @arg @ref FL_CMU_AHBCLK_PSC_DIV2
  *           @arg @ref FL_CMU_AHBCLK_PSC_DIV4
  *           @arg @ref FL_CMU_AHBCLK_PSC_DIV8
  *           @arg @ref FL_CMU_AHBCLK_PSC_DIV16
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetAHBPrescaler(uint32_t prescaler)
{
    MODIFY_REG(CMU->SYSCLKCR, CMU_SYSCLKCR_AHBPRES_Msk, prescaler);
}

/**
  * @brief    Get AHB Prescaler
  * @rmtoll   SYSCLKCR    AHBPRES    FL_CMU_GetAHBPrescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_AHBCLK_PSC_DIV1
  *           @arg @ref FL_CMU_AHBCLK_PSC_DIV2
  *           @arg @ref FL_CMU_AHBCLK_PSC_DIV4
  *           @arg @ref FL_CMU_AHBCLK_PSC_DIV8
  *           @arg @ref FL_CMU_AHBCLK_PSC_DIV16
  */
__STATIC_INLINE uint32_t FL_CMU_GetAHBPrescaler(void)
{
    return (uint32_t)(READ_BIT(CMU->SYSCLKCR, CMU_SYSCLKCR_AHBPRES_Msk));
}

/**
  * @brief    Set SysTick Clock Source
  * @rmtoll   SYSCLKCR    STCLKSEL    FL_CMU_SetSysTickClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_SYSTICK_CLK_SOURCE_SCLK
  *           @arg @ref FL_CMU_SYSTICK_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_SYSTICK_CLK_SOURCE_RCLF
  *           @arg @ref FL_CMU_SYSTICK_CLK_SOURCE_SYSCLK
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetSysTickClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->SYSCLKCR, CMU_SYSCLKCR_STCLKSEL_Msk, clock);
}

/**
  * @brief    Get SysTick Clock Source
  * @rmtoll   SYSCLKCR    STCLKSEL    FL_CMU_GetSysTickClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_SYSTICK_CLK_SOURCE_SCLK
  *           @arg @ref FL_CMU_SYSTICK_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_SYSTICK_CLK_SOURCE_RCLF
  *           @arg @ref FL_CMU_SYSTICK_CLK_SOURCE_SYSCLK
  */
__STATIC_INLINE uint32_t FL_CMU_GetSysTickClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->SYSCLKCR, CMU_SYSCLKCR_STCLKSEL_Msk));
}

/**
  * @brief    Set System Clock Source
  * @rmtoll   SYSCLKCR    SYSCLKSEL    FL_CMU_SetSystemClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_SYSTEM_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_SYSTEM_CLK_SOURCE_XTHF
  *           @arg @ref FL_CMU_SYSTEM_CLK_SOURCE_PLL
  *           @arg @ref FL_CMU_SYSTEM_CLK_SOURCE_RCLF
  *           @arg @ref FL_CMU_SYSTEM_CLK_SOURCE_XTLF
  *           @arg @ref FL_CMU_SYSTEM_CLK_SOURCE_RCLP
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetSystemClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->SYSCLKCR, CMU_SYSCLKCR_SYSCLKSEL_Msk, clock);
}

/**
  * @brief    Set System Clock Source Setting
  * @rmtoll   SYSCLKCR    SYSCLKSEL    FL_CMU_GetSystemClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_SYSTEM_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_SYSTEM_CLK_SOURCE_XTHF
  *           @arg @ref FL_CMU_SYSTEM_CLK_SOURCE_PLL
  *           @arg @ref FL_CMU_SYSTEM_CLK_SOURCE_RCLF
  *           @arg @ref FL_CMU_SYSTEM_CLK_SOURCE_XTLF
  *           @arg @ref FL_CMU_SYSTEM_CLK_SOURCE_RCLP
  */
__STATIC_INLINE uint32_t FL_CMU_GetSystemClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->SYSCLKCR, CMU_SYSCLKCR_SYSCLKSEL_Msk));
}

/**
  * @brief    Set RCHF Frequency
  * @rmtoll   RCHFCR    FSEL    FL_CMU_RCHF_SetFrequency
  * @param    frequency This parameter can be one of the following values:
  *           @arg @ref FL_CMU_RCHF_FREQUENCY_8MHZ
  *           @arg @ref FL_CMU_RCHF_FREQUENCY_16MHZ
  *           @arg @ref FL_CMU_RCHF_FREQUENCY_24MHZ
  *           @arg @ref FL_CMU_RCHF_FREQUENCY_32MHZ
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_RCHF_SetFrequency(uint32_t frequency)
{
    MODIFY_REG(CMU->RCHFCR, CMU_RCHFCR_FSEL_Msk, frequency);
}

/**
  * @brief    Get RCHF Frequency Setting
  * @rmtoll   RCHFCR    FSEL    FL_CMU_RCHF_GetFrequency
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_RCHF_FREQUENCY_8MHZ
  *           @arg @ref FL_CMU_RCHF_FREQUENCY_16MHZ
  *           @arg @ref FL_CMU_RCHF_FREQUENCY_24MHZ
  *           @arg @ref FL_CMU_RCHF_FREQUENCY_32MHZ
  */
__STATIC_INLINE uint32_t FL_CMU_RCHF_GetFrequency(void)
{
    return (uint32_t)(READ_BIT(CMU->RCHFCR, CMU_RCHFCR_FSEL_Msk));
}

/**
  * @brief    Enable RCHF
  * @rmtoll   RCHFCR    EN    FL_CMU_RCHF_Enable
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_RCHF_Enable(void)
{
    SET_BIT(CMU->RCHFCR, CMU_RCHFCR_EN_Msk);
}

/**
  * @brief    Get RCHF Enable Status
  * @rmtoll   RCHFCR    EN    FL_CMU_RCHF_IsEnabled
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_RCHF_IsEnabled(void)
{
    return (uint32_t)(READ_BIT(CMU->RCHFCR, CMU_RCHFCR_EN_Msk) == CMU_RCHFCR_EN_Msk);
}

/**
  * @brief    Disable RCHF
  * @rmtoll   RCHFCR    EN    FL_CMU_RCHF_Disable
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_RCHF_Disable(void)
{
    CLEAR_BIT(CMU->RCHFCR, CMU_RCHFCR_EN_Msk);
}

/**
  * @brief    Set RCHF Freqency Trim Value
  * @rmtoll   RCHFTR    TRIM    FL_CMU_RCHF_WriteTrimValue
  * @param    value TrimValue The value of RCHF trim
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_RCHF_WriteTrimValue(uint32_t value)
{
    MODIFY_REG(CMU->RCHFTR, (0xffU << 0U), (value << 0U));
}

/**
  * @brief    Get RCHF Freqency Trim Value
  * @rmtoll   RCHFTR    TRIM    FL_CMU_RCHF_ReadTrimValue
  * @retval   The value of RCHF trim
  */
__STATIC_INLINE uint32_t FL_CMU_RCHF_ReadTrimValue(void)
{
    return (uint32_t)(READ_BIT(CMU->RCHFTR, (0xffU << 0U)) >> 0U);
}

/**
  * @brief    Enable PLL
  * @rmtoll   PLLCR    EN    FL_CMU_PLL_Enable
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_PLL_Enable(void)
{
    SET_BIT(CMU->PLLCR, CMU_PLLCR_EN_Msk);
}

/**
  * @brief    Get PLL Enable Status
  * @rmtoll   PLLCR    EN    FL_CMU_PLL_Disable
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_PLL_Disable(void)
{
    CLEAR_BIT(CMU->PLLCR, CMU_PLLCR_EN_Msk);
}

/**
  * @brief    Disable PLL
  * @rmtoll   PLLCR    EN    FL_CMU_PLL_IsEnabled
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_PLL_IsEnabled(void)
{
    return (uint32_t)(READ_BIT(CMU->PLLCR, CMU_PLLCR_EN_Msk) == CMU_PLLCR_EN_Msk);
}

/**
  * @brief    Get PLL Ready Status
  * @rmtoll   PLLCR    LOCKED    FL_CMU_IsActiveFlag_PLLReady
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsActiveFlag_PLLReady(void)
{
    return (uint32_t)(READ_BIT(CMU->PLLCR, CMU_PLLCR_LOCKED_Msk) == (CMU_PLLCR_LOCKED_Msk));
}

/**
  * @brief    Set PLL Input Source
  * @rmtoll   PLLCR    INSEL    FL_CMU_PLL_SetClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_PLL_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_PLL_CLK_SOURCE_XTHF
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_PLL_SetClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->PLLCR, CMU_PLLCR_INSEL_Msk, clock);
}

/**
  * @brief    Get PLL Input Source Setting
  * @rmtoll   PLLCR    INSEL    FL_CMU_PLL_GetClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_PLL_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_PLL_CLK_SOURCE_XTHF
  */
__STATIC_INLINE uint32_t FL_CMU_PLL_GetClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->PLLCR, CMU_PLLCR_INSEL_Msk));
}

/**
  * @brief    Set PLL Multiplier
  * @rmtoll   PLLCR    DB    FL_CMU_PLL_WriteMultiplier
  * @param    multiplier
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_PLL_WriteMultiplier(uint32_t multiplier)
{
    MODIFY_REG(CMU->PLLCR, (0x7fU << 16U), (multiplier << 16U));
}

/**
  * @brief    Get PLL Multiplier Setting
  * @rmtoll   PLLCR    DB    FL_CMU_PLL_ReadMultiplier
  * @retval
  */
__STATIC_INLINE uint32_t FL_CMU_PLL_ReadMultiplier(void)
{
    return (uint32_t)(READ_BIT(CMU->PLLCR, (0x7fU << 16U)) >> 16U);
}

/**
  * @brief    Set PLL Prescaler
  * @rmtoll   PLLCR    REFPRSC    FL_CMU_PLL_SetPrescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_CMU_PLL_PSC_DIV1
  *           @arg @ref FL_CMU_PLL_PSC_DIV2
  *           @arg @ref FL_CMU_PLL_PSC_DIV4
  *           @arg @ref FL_CMU_PLL_PSC_DIV8
  *           @arg @ref FL_CMU_PLL_PSC_DIV12
  *           @arg @ref FL_CMU_PLL_PSC_DIV16
  *           @arg @ref FL_CMU_PLL_PSC_DIV24
  *           @arg @ref FL_CMU_PLL_PSC_DIV32
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_PLL_SetPrescaler(uint32_t prescaler)
{
    MODIFY_REG(CMU->PLLCR, CMU_PLLCR_REFPRSC_Msk, prescaler);
}

/**
  * @brief    Get PLL Prescaler Setting
  * @rmtoll   PLLCR    REFPRSC    FL_CMU_PLL_GetPrescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_PLL_PSC_DIV1
  *           @arg @ref FL_CMU_PLL_PSC_DIV2
  *           @arg @ref FL_CMU_PLL_PSC_DIV4
  *           @arg @ref FL_CMU_PLL_PSC_DIV8
  *           @arg @ref FL_CMU_PLL_PSC_DIV12
  *           @arg @ref FL_CMU_PLL_PSC_DIV16
  *           @arg @ref FL_CMU_PLL_PSC_DIV24
  *           @arg @ref FL_CMU_PLL_PSC_DIV32
  */
__STATIC_INLINE uint32_t FL_CMU_PLL_GetPrescaler(void)
{
    return (uint32_t)(READ_BIT(CMU->PLLCR, CMU_PLLCR_REFPRSC_Msk));
}

/**
  * @brief    Set PLL Digital Domain Output
  * @rmtoll   PLLCR    OSEL    FL_CMU_PLL_SetOutputMultiplier
  * @param    multiplier This parameter can be one of the following values:
  *           @arg @ref FL_CMU_PLL_OUTPUT_X1
  *           @arg @ref FL_CMU_PLL_OUTPUT_X2
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_PLL_SetOutputMultiplier(uint32_t multiplier)
{
    MODIFY_REG(CMU->PLLCR, CMU_PLLCR_OSEL_Msk, multiplier);
}

/**
  * @brief    Get PLL Digital Domain Output Setting
  * @rmtoll   PLLCR    OSEL    FL_CMU_PLL_GetOutputMultiplier
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_PLL_OUTPUT_X1
  *           @arg @ref FL_CMU_PLL_OUTPUT_X2
  */
__STATIC_INLINE uint32_t FL_CMU_PLL_GetOutputMultiplier(void)
{
    return (uint32_t)(READ_BIT(CMU->PLLCR, CMU_PLLCR_OSEL_Msk));
}

/**
  * @brief    Set RCLP Enable
  * @rmtoll   RCLPCR    ENB    FL_CMU_RCLP_Enable
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_RCLP_Enable(void)
{
    CLEAR_BIT(CMU->RCLPCR, CMU_RCLPCR_ENB_Msk);
}

/**
  * @brief    Get RCLP Enable Flag
  * @rmtoll   RCLPCR    ENB    FL_CMU_RCLP_IsEnabled
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_RCLP_IsEnabled(void)
{
    return (uint32_t)!(READ_BIT(CMU->RCLPCR, CMU_RCLPCR_ENB_Msk) == CMU_RCLPCR_ENB_Msk);
}

/**
  * @brief    Set RCLP Disable
  * @rmtoll   RCLPCR    ENB    FL_CMU_RCLP_Disable
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_RCLP_Disable(void)
{
    SET_BIT(CMU->RCLPCR, CMU_RCLPCR_ENB_Msk);
}

/**
  * @brief    Set RCLP Frequency Trim Value
  * @rmtoll   RCLPTR    TRIM    FL_CMU_RCLP_WriteTrimValue
  * @param    value TrimValue The value of RCLP trim
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_RCLP_WriteTrimValue(uint32_t value)
{
    MODIFY_REG(CMU->RCLPTR, (0xffU << 0U), (value << 0U));
}

/**
  * @brief    Get RCLP Frequency Trim Value
  * @rmtoll   RCLPTR    TRIM    FL_CMU_RCLP_ReadTrimValue
  * @retval   The Value of RCLP trim
  */
__STATIC_INLINE uint32_t FL_CMU_RCLP_ReadTrimValue(void)
{
    return (uint32_t)(READ_BIT(CMU->RCLPTR, (0xffU << 0U)) >> 0U);
}

/**
  * @brief    Set LSCLK Clock Source
  * @rmtoll   LSCLKSEL    SEL    FL_CMU_SetLSCLKClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_LSCLK_CLK_SOURCE_RCLP
  *           @arg @ref FL_CMU_LSCLK_CLK_SOURCE_XTLF
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetLSCLKClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->LSCLKSEL, CMU_LSCLKSEL_SEL_Msk, clock);
}

/**
  * @brief    Set XTHF Oscillation Strength
  * @rmtoll   XTHFCR    CFG    FL_CMU_XTHF_WriteDriverStrength
  * @param    strength
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_XTHF_WriteDriverStrength(uint32_t strength)
{
    MODIFY_REG(CMU->XTHFCR, (0x1fU << 8U), (strength << 8U));
}

/**
  * @brief    Get XTHF Oscillation Strength Setting
  * @rmtoll   XTHFCR    CFG    FL_CMU_XTHF_ReadDriverStrength
  * @retval
  */
__STATIC_INLINE uint32_t FL_CMU_XTHF_ReadDriverStrength(void)
{
    return (uint32_t)(READ_BIT(CMU->XTHFCR, (0x1fU << 8U)) >> 8U);
}

/**
  * @brief    Enable XTHF
  * @rmtoll   XTHFCR    EN    FL_CMU_XTHF_Enable
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_XTHF_Enable(void)
{
    SET_BIT(CMU->XTHFCR, CMU_XTHFCR_EN_Msk);
}

/**
  * @brief    Get XTHF Enable Status
  * @rmtoll   XTHFCR    EN    FL_CMU_XTHF_IsEnabled
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_XTHF_IsEnabled(void)
{
    return (uint32_t)(READ_BIT(CMU->XTHFCR, CMU_XTHFCR_EN_Msk) == CMU_XTHFCR_EN_Msk);
}

/**
  * @brief    Disable XTHF
  * @rmtoll   XTHFCR    EN    FL_CMU_XTHF_Disable
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_XTHF_Disable(void)
{
    CLEAR_BIT(CMU->XTHFCR, CMU_XTHFCR_EN_Msk);
}

/**
  * @brief    Set RCLF Output Prescaler
  * @rmtoll   RCLFCR    PSC    FL_CMU_RCLF_SetPrescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_CMU_RCLF_PSC_DIV1
  *           @arg @ref FL_CMU_RCLF_PSC_DIV4
  *           @arg @ref FL_CMU_RCLF_PSC_DIV8
  *           @arg @ref FL_CMU_RCLF_PSC_DIV16
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_RCLF_SetPrescaler(uint32_t prescaler)
{
    MODIFY_REG(CMU->RCLFCR, CMU_RCLFCR_PSC_Msk, prescaler);
}

/**
  * @brief    Get RCLF Output Prescaler Setting
  * @rmtoll   RCLFCR    PSC    FL_CMU_RCLF_GetPrescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_RCLF_PSC_DIV1
  *           @arg @ref FL_CMU_RCLF_PSC_DIV4
  *           @arg @ref FL_CMU_RCLF_PSC_DIV8
  *           @arg @ref FL_CMU_RCLF_PSC_DIV16
  */
__STATIC_INLINE uint32_t FL_CMU_RCLF_GetPrescaler(void)
{
    return (uint32_t)(READ_BIT(CMU->RCLFCR, CMU_RCLFCR_PSC_Msk));
}

/**
  * @brief    Enable RCLF
  * @rmtoll   RCLFCR    EN    FL_CMU_RCLF_Enable
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_RCLF_Enable(void)
{
    SET_BIT(CMU->RCLFCR, CMU_RCLFCR_EN_Msk);
}

/**
  * @brief    Get RCLF Enable Status
  * @rmtoll   RCLFCR    EN    FL_CMU_RCLF_IsEnabled
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_RCLF_IsEnabled(void)
{
    return (uint32_t)(READ_BIT(CMU->RCLFCR, CMU_RCLFCR_EN_Msk) == CMU_RCLFCR_EN_Msk);
}

/**
  * @brief    Disable RCLF
  * @rmtoll   RCLFCR    EN    FL_CMU_RCLF_Disable
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_RCLF_Disable(void)
{
    CLEAR_BIT(CMU->RCLFCR, CMU_RCLFCR_EN_Msk);
}

/**
  * @brief    Set RCLF Frequency Trim Value
  * @rmtoll   RCLFTR    TRIM    FL_CMU_RCLF_WriteTrimValue
  * @param    value TrimValue The value of RCLF trim
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_RCLF_WriteTrimValue(uint32_t value)
{
    MODIFY_REG(CMU->RCLFTR, (0xffU << 0U), (value << 0U));
}

/**
  * @brief    Get RCLF Frequency Trim Value
  * @rmtoll   RCLFTR    TRIM    FL_CMU_RCLF_ReadTrimValue
  * @retval   The Value of RCLF trim
  */
__STATIC_INLINE uint32_t FL_CMU_RCLF_ReadTrimValue(void)
{
    return (uint32_t)(READ_BIT(CMU->RCLFTR, (0xffU << 0U)) >> 0U);
}

/**
  * @brief    Enable Group1 Periph Bus Clock
  * @rmtoll   PCLKCR1        FL_CMU_EnableGroup1BusClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_LPTIM32
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_LPTIM16
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_RTCA
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_PMU
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_SCU
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_IWDT
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_ANAC
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_PAD
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_SVD
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_COMP
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_ATT
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_OPA
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_VREF1P2
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_EnableGroup1BusClock(uint32_t peripheral)
{
    SET_BIT(CMU->PCLKCR1, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Enable Group2 Periph Bus Clock
  * @rmtoll   PCLKCR2        FL_CMU_EnableGroup2BusClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_CRC
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_RNG
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_AES
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_LCD
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_DMA
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_FLASH
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_RAMBIST
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_WWDT
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_ADC
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_DIVAS
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_DAC
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_PGL
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_EnableGroup2BusClock(uint32_t peripheral)
{
    SET_BIT(CMU->PCLKCR2, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Enable Group3 Periph Bus Clock
  * @rmtoll   PCLKCR3        FL_CMU_EnableGroup3BusClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_SPI0
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_SPI1
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_SPI2
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART0
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART1
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART3
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART4
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART5
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UARTIR
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_U7816
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_LPUART0
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_LPUART1
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_LPUART2
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_CAN
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_I2C
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_EnableGroup3BusClock(uint32_t peripheral)
{
    SET_BIT(CMU->PCLKCR3, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Enable Group4 Periph Bus Clock
  * @rmtoll   PCLKCR4        FL_CMU_EnableGroup4BusClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_BSTIM32
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_GPTIM0
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_GPTIM1
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_GPTIM2
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_ATIM
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_BSTIM16
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_EnableGroup4BusClock(uint32_t peripheral)
{
    SET_BIT(CMU->PCLKCR4, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable Group1 Periph Bus Clock
  * @rmtoll   PCLKCR1        FL_CMU_DisableGroup1BusClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_LPTIM32
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_LPTIM16
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_RTCA
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_PMU
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_SCU
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_IWDT
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_ANAC
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_PAD
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_SVD
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_COMP
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_ATT
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_OPA
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_VREF1P2
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_DisableGroup1BusClock(uint32_t peripheral)
{
    CLEAR_BIT(CMU->PCLKCR1, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable Group2 Periph Bus Clock
  * @rmtoll   PCLKCR2        FL_CMU_DisableGroup2BusClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_CRC
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_RNG
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_AES
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_LCD
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_DMA
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_FLASH
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_RAMBIST
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_WWDT
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_ADC
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_DIVAS
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_DAC
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_PGL
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_DisableGroup2BusClock(uint32_t peripheral)
{
    CLEAR_BIT(CMU->PCLKCR2, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable Group3 Periph Bus Clock
  * @rmtoll   PCLKCR3        FL_CMU_DisableGroup3BusClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_SPI0
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_SPI1
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_SPI2
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART0
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART1
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART3
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART4
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART5
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UARTIR
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_U7816
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_LPUART0
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_LPUART1
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_LPUART2
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_CAN
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_I2C
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_DisableGroup3BusClock(uint32_t peripheral)
{
    CLEAR_BIT(CMU->PCLKCR3, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable Group4 Periph Bus Clock
  * @rmtoll   PCLKCR4        FL_CMU_DisableGroup4BusClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_BSTIM32
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_GPTIM0
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_GPTIM1
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_GPTIM2
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_ATIM
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_BSTIM16
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_DisableGroup4BusClock(uint32_t peripheral)
{
    CLEAR_BIT(CMU->PCLKCR4, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Get Group1 Periph Bus Clock Enable Status
  * @rmtoll   PCLKCR1        FL_CMU_IsEnabledGroup1BusClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_LPTIM32
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_LPTIM16
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_RTCA
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_PMU
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_SCU
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_IWDT
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_ANAC
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_PAD
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_SVD
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_COMP
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_ATT
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_OPA
  *           @arg @ref FL_CMU_GROUP1_BUSCLK_VREF1P2
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsEnabledGroup1BusClock(uint32_t peripheral)
{
    return (uint32_t)(READ_BIT(CMU->PCLKCR1, ((peripheral & 0xffffffff) << 0x0U)) == ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Get Group2 Periph Bus Clock Enable Status
  * @rmtoll   PCLKCR2        FL_CMU_IsEnabledGroup2BusClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_CRC
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_RNG
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_AES
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_LCD
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_DMA
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_FLASH
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_RAMBIST
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_WWDT
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_ADC
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_DIVAS
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_DAC
  *           @arg @ref FL_CMU_GROUP2_BUSCLK_PGL
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsEnabledGroup2BusClock(uint32_t peripheral)
{
    return (uint32_t)(READ_BIT(CMU->PCLKCR2, ((peripheral & 0xffffffff) << 0x0U)) == ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Get Group3 Periph Bus Clock Enable Status
  * @rmtoll   PCLKCR3        FL_CMU_IsEnabledGroup3BusClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_SPI0
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_SPI1
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_SPI2
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART0
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART1
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART3
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART4
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UART5
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_UARTIR
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_U7816
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_LPUART0
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_LPUART1
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_LPUART2
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_CAN
  *           @arg @ref FL_CMU_GROUP3_BUSCLK_I2C
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsEnabledGroup3BusClock(uint32_t peripheral)
{
    return (uint32_t)(READ_BIT(CMU->PCLKCR3, ((peripheral & 0xffffffff) << 0x0U)) == ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Get Group4 Periph Bus Clock Enable Status
  * @rmtoll   PCLKCR4        FL_CMU_IsEnabledGroup4BusClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_BSTIM32
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_GPTIM0
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_GPTIM1
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_GPTIM2
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_ATIM
  *           @arg @ref FL_CMU_GROUP4_BUSCLK_BSTIM16
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsEnabledGroup4BusClock(uint32_t peripheral)
{
    return (uint32_t)(READ_BIT(CMU->PCLKCR4, ((peripheral & 0xffffffff) << 0x0U)) == ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Enable Group3 Periph Operation Clock
  * @rmtoll   OPCCR3        FL_CMU_EnableGroup3OperationClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP3_OPCLK_EXTI
  *           @arg @ref FL_CMU_GROUP3_OPCLK_FLASH
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPUART1
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPUART0
  *           @arg @ref FL_CMU_GROUP3_OPCLK_RNG
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPUART2
  *           @arg @ref FL_CMU_GROUP3_OPCLK_I2C
  *           @arg @ref FL_CMU_GROUP3_OPCLK_ADC
  *           @arg @ref FL_CMU_GROUP3_OPCLK_ATIM
  *           @arg @ref FL_CMU_GROUP3_OPCLK_CAN
  *           @arg @ref FL_CMU_GROUP3_OPCLK_UART1
  *           @arg @ref FL_CMU_GROUP3_OPCLK_UART0
  *           @arg @ref FL_CMU_GROUP3_OPCLK_BSTIM16
  *           @arg @ref FL_CMU_GROUP3_OPCLK_BSTIM32
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPTIM16
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPTIM32
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_EnableGroup3OperationClock(uint32_t peripheral)
{
    SET_BIT(CMU->OPCCR3, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable Group3 Periph Operation Clock
  * @rmtoll   OPCCR3        FL_CMU_DisableGroup3OperationClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP3_OPCLK_EXTI
  *           @arg @ref FL_CMU_GROUP3_OPCLK_FLASH
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPUART1
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPUART0
  *           @arg @ref FL_CMU_GROUP3_OPCLK_RNG
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPUART2
  *           @arg @ref FL_CMU_GROUP3_OPCLK_I2C
  *           @arg @ref FL_CMU_GROUP3_OPCLK_ADC
  *           @arg @ref FL_CMU_GROUP3_OPCLK_ATIM
  *           @arg @ref FL_CMU_GROUP3_OPCLK_CAN
  *           @arg @ref FL_CMU_GROUP3_OPCLK_UART1
  *           @arg @ref FL_CMU_GROUP3_OPCLK_UART0
  *           @arg @ref FL_CMU_GROUP3_OPCLK_BSTIM16
  *           @arg @ref FL_CMU_GROUP3_OPCLK_BSTIM32
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPTIM16
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPTIM32
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_DisableGroup3OperationClock(uint32_t peripheral)
{
    CLEAR_BIT(CMU->OPCCR3, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Get Group3 Periph Operation Clock Enable Status
  * @rmtoll   OPCCR3        FL_CMU_IsEnabledGroup3OperationClock
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_CMU_GROUP3_OPCLK_EXTI
  *           @arg @ref FL_CMU_GROUP3_OPCLK_FLASH
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPUART1
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPUART0
  *           @arg @ref FL_CMU_GROUP3_OPCLK_RNG
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPUART2
  *           @arg @ref FL_CMU_GROUP3_OPCLK_I2C
  *           @arg @ref FL_CMU_GROUP3_OPCLK_ADC
  *           @arg @ref FL_CMU_GROUP3_OPCLK_ATIM
  *           @arg @ref FL_CMU_GROUP3_OPCLK_CAN
  *           @arg @ref FL_CMU_GROUP3_OPCLK_UART1
  *           @arg @ref FL_CMU_GROUP3_OPCLK_UART0
  *           @arg @ref FL_CMU_GROUP3_OPCLK_BSTIM16
  *           @arg @ref FL_CMU_GROUP3_OPCLK_BSTIM32
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPTIM16
  *           @arg @ref FL_CMU_GROUP3_OPCLK_LPTIM32
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsEnabledGroup3OperationClock(uint32_t peripheral)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR3, ((peripheral & 0xffffffff) << 0x0U)) == ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Set EXTI Clock Source
  * @rmtoll   OPCCR1    EXTICKS    FL_CMU_SetEXTIClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_EXTI_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_EXTI_CLK_SOURCE_HCLK
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetEXTIClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR1, CMU_OPCCR1_EXTICKS_Msk, clock);
}

/**
  * @brief    Get EXTI Clock Source Setting
  * @rmtoll   OPCCR1    EXTICKS    FL_CMU_GetEXTIClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_EXTI_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_EXTI_CLK_SOURCE_HCLK
  */
__STATIC_INLINE uint32_t FL_CMU_GetEXTIClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR1, CMU_OPCCR1_EXTICKS_Msk));
}

/**
  * @brief    Set LPUART1 Clock Source
  * @rmtoll   OPCCR1    LPUART1CKS    FL_CMU_SetLPUART1ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_LPUART1_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_LPUART1_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_LPUART1_CLK_SOURCE_RCLF
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetLPUART1ClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR1, CMU_OPCCR1_LPUART1CKS_Msk, clock);
}

/**
  * @brief    Get LPUART1 Clock Source Setting
  * @rmtoll   OPCCR1    LPUART1CKS    FL_CMU_GetLPUART1ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_LPUART1_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_LPUART1_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_LPUART1_CLK_SOURCE_RCLF
  */
__STATIC_INLINE uint32_t FL_CMU_GetLPUART1ClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR1, CMU_OPCCR1_LPUART1CKS_Msk));
}

/**
  * @brief    Set LPUART0 Clock Source
  * @rmtoll   OPCCR1    LPUART0CKS    FL_CMU_SetLPUART0ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_LPUART0_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_LPUART0_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_LPUART0_CLK_SOURCE_RCLF
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetLPUART0ClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR1, CMU_OPCCR1_LPUART0CKS_Msk, clock);
}

/**
  * @brief    Get LPUART0 Clock Source Setting
  * @rmtoll   OPCCR1    LPUART0CKS    FL_CMU_GetLPUART0ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_LPUART0_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_LPUART0_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_LPUART0_CLK_SOURCE_RCLF
  */
__STATIC_INLINE uint32_t FL_CMU_GetLPUART0ClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR1, CMU_OPCCR1_LPUART0CKS_Msk));
}

/**
  * @brief    Set LPUART2 Clock Source
  * @rmtoll   OPCCR1    LPUART2CKS    FL_CMU_SetLPUART2ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_LPUART2_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_LPUART2_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_LPUART2_CLK_SOURCE_RCLF
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetLPUART2ClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR1, CMU_OPCCR1_LPUART2CKS_Msk, clock);
}

/**
  * @brief    Get LPUART2 Clock Source Setting
  * @rmtoll   OPCCR1    LPUART2CKS    FL_CMU_GetLPUART2ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_LPUART2_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_LPUART2_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_LPUART2_CLK_SOURCE_RCLF
  */
__STATIC_INLINE uint32_t FL_CMU_GetLPUART2ClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR1, CMU_OPCCR1_LPUART2CKS_Msk));
}

/**
  * @brief    Set I2C Clock Source
  * @rmtoll   OPCCR1    I2CCKS    FL_CMU_SetI2CClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_I2C_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_I2C_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_I2C_CLK_SOURCE_SYSCLK
  *           @arg @ref FL_CMU_I2C_CLK_SOURCE_RCLF
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetI2CClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR1, CMU_OPCCR1_I2CCKS_Msk, clock);
}

/**
  * @brief    Get I2C Clock Source Setting
  * @rmtoll   OPCCR1    I2CCKS    FL_CMU_GetI2CClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_I2C_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_I2C_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_I2C_CLK_SOURCE_SYSCLK
  *           @arg @ref FL_CMU_I2C_CLK_SOURCE_RCLF
  */
__STATIC_INLINE uint32_t FL_CMU_GetI2CClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR1, CMU_OPCCR1_I2CCKS_Msk));
}

/**
  * @brief    Set BSTIM16 Clock Source
  * @rmtoll   OPCCR1    BT16CKS    FL_CMU_SetBSTIM16ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_BSTIM16_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_BSTIM16_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_BSTIM16_CLK_SOURCE_RCLP
  *           @arg @ref FL_CMU_BSTIM16_CLK_SOURCE_RCLF
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetBSTIM16ClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR1, CMU_OPCCR1_BT16CKS_Msk, clock);
}

/**
  * @brief    Get BSTIM16 Clock Source Setting
  * @rmtoll   OPCCR1    BT16CKS    FL_CMU_GetBSTIM16ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_BSTIM16_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_BSTIM16_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_BSTIM16_CLK_SOURCE_RCLP
  *           @arg @ref FL_CMU_BSTIM16_CLK_SOURCE_RCLF
  */
__STATIC_INLINE uint32_t FL_CMU_GetBSTIM16ClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR1, CMU_OPCCR1_BT16CKS_Msk));
}

/**
  * @brief    Set BSTIM32 Clock Source
  * @rmtoll   OPCCR1    BT32CKS    FL_CMU_SetBSTIM32ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_BSTIM32_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_BSTIM32_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_BSTIM32_CLK_SOURCE_RCLP
  *           @arg @ref FL_CMU_BSTIM32_CLK_SOURCE_RCLF
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetBSTIM32ClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR1, CMU_OPCCR1_BT32CKS_Msk, clock);
}

/**
  * @brief    Get BSTIM32 Clock Source Setting
  * @rmtoll   OPCCR1    BT32CKS    FL_CMU_GetBSTIM32ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_BSTIM32_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_BSTIM32_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_BSTIM32_CLK_SOURCE_RCLP
  *           @arg @ref FL_CMU_BSTIM32_CLK_SOURCE_RCLF
  */
__STATIC_INLINE uint32_t FL_CMU_GetBSTIM32ClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR1, CMU_OPCCR1_BT32CKS_Msk));
}

/**
  * @brief    Set LPTIM16 Clock Source
  * @rmtoll   OPCCR1    LPT16CKS    FL_CMU_SetLPTIM16ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_LPTIM16_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_LPTIM16_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_LPTIM16_CLK_SOURCE_RCLP
  *           @arg @ref FL_CMU_LPTIM16_CLK_SOURCE_RCLF
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetLPTIM16ClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR1, CMU_OPCCR1_LPT16CKS_Msk, clock);
}

/**
  * @brief    Get LPTIM16 Clock Source Setting
  * @rmtoll   OPCCR1    LPT16CKS    FL_CMU_GetLPTIM16ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_LPTIM16_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_LPTIM16_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_LPTIM16_CLK_SOURCE_RCLP
  *           @arg @ref FL_CMU_LPTIM16_CLK_SOURCE_RCLF
  */
__STATIC_INLINE uint32_t FL_CMU_GetLPTIM16ClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR1, CMU_OPCCR1_LPT16CKS_Msk));
}

/**
  * @brief    Set LPTIM32 Clock Source
  * @rmtoll   OPCCR1    LPT32CKS    FL_CMU_SetLPTIM32ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_LPTIM32_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_LPTIM32_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_LPTIM32_CLK_SOURCE_RCLP
  *           @arg @ref FL_CMU_LPTIM32_CLK_SOURCE_RCLF
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetLPTIM32ClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR1, CMU_OPCCR1_LPT32CKS_Msk, clock);
}

/**
  * @brief    Get LPTIM32 Clock Source Setting
  * @rmtoll   OPCCR1    LPT32CKS    FL_CMU_GetLPTIM32ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_LPTIM32_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_LPTIM32_CLK_SOURCE_LSCLK
  *           @arg @ref FL_CMU_LPTIM32_CLK_SOURCE_RCLP
  *           @arg @ref FL_CMU_LPTIM32_CLK_SOURCE_RCLF
  */
__STATIC_INLINE uint32_t FL_CMU_GetLPTIM32ClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR1, CMU_OPCCR1_LPT32CKS_Msk));
}

/**
  * @brief    Set ATIM Clock Source
  * @rmtoll   OPCCR1    ATCKS    FL_CMU_SetATIMClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_ATIM_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_ATIM_CLK_SOURCE_PLL_X2
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetATIMClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR1, CMU_OPCCR1_ATCKS_Msk, clock);
}

/**
  * @brief    Get ATIM Clock Source Setting
  * @rmtoll   OPCCR1    ATCKS    FL_CMU_GetATIMClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_ATIM_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_ATIM_CLK_SOURCE_PLL_X2
  */
__STATIC_INLINE uint32_t FL_CMU_GetATIMClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR1, CMU_OPCCR1_ATCKS_Msk));
}

/**
  * @brief    Set CAN Clock Source
  * @rmtoll   OPCCR1    CANCKS    FL_CMU_SetCANClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_CAN_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_CAN_CLK_SOURCE_XTHF
  *           @arg @ref FL_CMU_CAN_CLK_SOURCE_PLL
  *           @arg @ref FL_CMU_CAN_CLK_SOURCE_APBCLK
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetCANClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR1, CMU_OPCCR1_CANCKS_Msk, clock);
}

/**
  * @brief    Get CAN Clock Source Setting
  * @rmtoll   OPCCR1    CANCKS    FL_CMU_GetCANClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_CAN_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_CAN_CLK_SOURCE_XTHF
  *           @arg @ref FL_CMU_CAN_CLK_SOURCE_PLL
  *           @arg @ref FL_CMU_CAN_CLK_SOURCE_APBCLK
  */
__STATIC_INLINE uint32_t FL_CMU_GetCANClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR1, CMU_OPCCR1_CANCKS_Msk));
}

/**
  * @brief    Set UART1 Clock Source
  * @rmtoll   OPCCR1    UART1CKS    FL_CMU_SetUART1ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_UART1_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_UART1_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_UART1_CLK_SOURCE_SYSCLK
  *           @arg @ref FL_CMU_UART1_CLK_SOURCE_XTHF
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetUART1ClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR1, CMU_OPCCR1_UART1CKS_Msk, clock);
}

/**
  * @brief    Get UART1 Clock Source Setting
  * @rmtoll   OPCCR1    UART1CKS    FL_CMU_GetUART1ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_UART1_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_UART1_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_UART1_CLK_SOURCE_SYSCLK
  *           @arg @ref FL_CMU_UART1_CLK_SOURCE_XTHF
  */
__STATIC_INLINE uint32_t FL_CMU_GetUART1ClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR1, CMU_OPCCR1_UART1CKS_Msk));
}

/**
  * @brief    Set UART0 Clock Source
  * @rmtoll   OPCCR1    UART0CKS    FL_CMU_SetUART0ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_UART0_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_UART0_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_UART0_CLK_SOURCE_SYSCLK
  *           @arg @ref FL_CMU_UART0_CLK_SOURCE_XTHF
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetUART0ClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR1, CMU_OPCCR1_UART0CKS_Msk, clock);
}

/**
  * @brief    Get UART0 Clock Source Setting
  * @rmtoll   OPCCR1    UART0CKS    FL_CMU_GetUART0ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_UART0_CLK_SOURCE_APBCLK
  *           @arg @ref FL_CMU_UART0_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_UART0_CLK_SOURCE_SYSCLK
  *           @arg @ref FL_CMU_UART0_CLK_SOURCE_XTHF
  */
__STATIC_INLINE uint32_t FL_CMU_GetUART0ClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR1, CMU_OPCCR1_UART0CKS_Msk));
}

/**
  * @brief    Set RNG Prescaler
  * @rmtoll   OPCCR2    RNGPRSC    FL_CMU_SetRNGPrescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_CMU_RNG_PSC_DIV1
  *           @arg @ref FL_CMU_RNG_PSC_DIV2
  *           @arg @ref FL_CMU_RNG_PSC_DIV4
  *           @arg @ref FL_CMU_RNG_PSC_DIV8
  *           @arg @ref FL_CMU_RNG_PSC_DIV16
  *           @arg @ref FL_CMU_RNG_PSC_DIV32
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetRNGPrescaler(uint32_t prescaler)
{
    MODIFY_REG(CMU->OPCCR2, CMU_OPCCR2_RNGPRSC_Msk, prescaler);
}

/**
  * @brief    Get RNG Prescaler Setting
  * @rmtoll   OPCCR2    RNGPRSC    FL_CMU_GetRNGPrescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_RNG_PSC_DIV1
  *           @arg @ref FL_CMU_RNG_PSC_DIV2
  *           @arg @ref FL_CMU_RNG_PSC_DIV4
  *           @arg @ref FL_CMU_RNG_PSC_DIV8
  *           @arg @ref FL_CMU_RNG_PSC_DIV16
  *           @arg @ref FL_CMU_RNG_PSC_DIV32
  */
__STATIC_INLINE uint32_t FL_CMU_GetRNGPrescaler(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR2, CMU_OPCCR2_RNGPRSC_Msk));
}

/**
  * @brief    Set ADC Prescaler
  * @rmtoll   OPCCR2    ADCPRSC    FL_CMU_SetADCPrescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_CMU_ADC_PSC_DIV1
  *           @arg @ref FL_CMU_ADC_PSC_DIV2
  *           @arg @ref FL_CMU_ADC_PSC_DIV4
  *           @arg @ref FL_CMU_ADC_PSC_DIV8
  *           @arg @ref FL_CMU_ADC_PSC_DIV16
  *           @arg @ref FL_CMU_ADC_PSC_DIV32
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetADCPrescaler(uint32_t prescaler)
{
    MODIFY_REG(CMU->OPCCR2, CMU_OPCCR2_ADCPRSC_Msk, prescaler);
}

/**
  * @brief    Get ADC Prescaler Setting
  * @rmtoll   OPCCR2    ADCPRSC    FL_CMU_GetADCPrescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_ADC_PSC_DIV1
  *           @arg @ref FL_CMU_ADC_PSC_DIV2
  *           @arg @ref FL_CMU_ADC_PSC_DIV4
  *           @arg @ref FL_CMU_ADC_PSC_DIV8
  *           @arg @ref FL_CMU_ADC_PSC_DIV16
  *           @arg @ref FL_CMU_ADC_PSC_DIV32
  */
__STATIC_INLINE uint32_t FL_CMU_GetADCPrescaler(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR2, CMU_OPCCR2_ADCPRSC_Msk));
}

/**
  * @brief    Set ADC Clock Source
  * @rmtoll   OPCCR2    ADCCKS    FL_CMU_SetADCClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_ADC_CLK_SOURCE_RCLF
  *           @arg @ref FL_CMU_ADC_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_ADC_CLK_SOURCE_XTHF
  *           @arg @ref FL_CMU_ADC_CLK_SOURCE_PLL
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_SetADCClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->OPCCR2, CMU_OPCCR2_ADCCKS_Msk, clock);
}

/**
  * @brief    Get ADC Clock Source Setting
  * @rmtoll   OPCCR2    ADCCKS    FL_CMU_GetADCClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_ADC_CLK_SOURCE_RCLF
  *           @arg @ref FL_CMU_ADC_CLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_ADC_CLK_SOURCE_XTHF
  *           @arg @ref FL_CMU_ADC_CLK_SOURCE_PLL
  */
__STATIC_INLINE uint32_t FL_CMU_GetADCClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->OPCCR2, CMU_OPCCR2_ADCCKS_Msk));
}

/**
  * @brief    Disable CCL Interrupt
  * @rmtoll   CCCR    CCLIE    FL_CMU_CCL_DisableIT
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_CCL_DisableIT(void)
{
    CLEAR_BIT(CMU->CCCR, CMU_CCCR_CCLIE_Msk);
}

/**
  * @brief    Enable CCL Interrupt
  * @rmtoll   CCCR    CCLIE    FL_CMU_CCL_EnableIT
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_CCL_EnableIT(void)
{
    SET_BIT(CMU->CCCR, CMU_CCCR_CCLIE_Msk);
}

/**
  * @brief    Get CCL Interrupt Enable Status
  * @rmtoll   CCCR    CCLIE    FL_CMU_CCL_IsEnabledIT
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_CCL_IsEnabledIT(void)
{
    return (uint32_t)(READ_BIT(CMU->CCCR, CMU_CCCR_CCLIE_Msk) == CMU_CCCR_CCLIE_Msk);
}

/**
  * @brief    Enable CCL
  * @rmtoll   CCCR    EN    FL_CMU_CCL_Enable
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_CCL_Enable(void)
{
    SET_BIT(CMU->CCCR, CMU_CCCR_EN_Msk);
}

/**
  * @brief    Get CCL Enable Status
  * @rmtoll   CCCR    EN    FL_CMU_CCL_IsEnabled
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_CCL_IsEnabled(void)
{
    return (uint32_t)(READ_BIT(CMU->CCCR, CMU_CCCR_EN_Msk) == CMU_CCCR_EN_Msk);
}

/**
  * @brief    Disable CCL
  * @rmtoll   CCCR    EN    FL_CMU_CCL_Disable
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_CCL_Disable(void)
{
    CLEAR_BIT(CMU->CCCR, CMU_CCCR_EN_Msk);
}

/**
  * @brief    Set CCL Calibration Clock Prescaler
  * @rmtoll   CCFR    CALPSC    FL_CMU_CCL_SetCalibrationClockPrescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_CMU_CCL_CALCLK_PSC_DIV1
  *           @arg @ref FL_CMU_CCL_CALCLK_PSC_DIV2
  *           @arg @ref FL_CMU_CCL_CALCLK_PSC_DIV4
  *           @arg @ref FL_CMU_CCL_CALCLK_PSC_DIV8
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_CCL_SetCalibrationClockPrescaler(uint32_t prescaler)
{
    MODIFY_REG(CMU->CCFR, CMU_CCFR_CALPSC_Msk, prescaler);
}

/**
  * @brief    Get CCL Calibration Clock Prescaler
  * @rmtoll   CCFR    CALPSC    FL_CMU_CCL_GetCalibrationClockPrescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_CCL_CALCLK_PSC_DIV1
  *           @arg @ref FL_CMU_CCL_CALCLK_PSC_DIV2
  *           @arg @ref FL_CMU_CCL_CALCLK_PSC_DIV4
  *           @arg @ref FL_CMU_CCL_CALCLK_PSC_DIV8
  */
__STATIC_INLINE uint32_t FL_CMU_CCL_GetCalibrationClockPrescaler(void)
{
    return (uint32_t)(READ_BIT(CMU->CCFR, CMU_CCFR_CALPSC_Msk));
}

/**
  * @brief    Set CCL Reference Clock Prescaler
  * @rmtoll   CCFR    REFPSC    FL_CMU_CCL_SetReferenceClockPrescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_CMU_CCL_REFCLK_PSC_DIV8
  *           @arg @ref FL_CMU_CCL_REFCLK_PSC_DIV16
  *           @arg @ref FL_CMU_CCL_REFCLK_PSC_DIV32
  *           @arg @ref FL_CMU_CCL_REFCLK_PSC_DIV64
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_CCL_SetReferenceClockPrescaler(uint32_t prescaler)
{
    MODIFY_REG(CMU->CCFR, CMU_CCFR_REFPSC_Msk, prescaler);
}

/**
  * @brief    Get CCL Reference Clock Prescaler
  * @rmtoll   CCFR    REFPSC    FL_CMU_CCL_GetReferenceClockPrescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_CCL_REFCLK_PSC_DIV8
  *           @arg @ref FL_CMU_CCL_REFCLK_PSC_DIV16
  *           @arg @ref FL_CMU_CCL_REFCLK_PSC_DIV32
  *           @arg @ref FL_CMU_CCL_REFCLK_PSC_DIV64
  */
__STATIC_INLINE uint32_t FL_CMU_CCL_GetReferenceClockPrescaler(void)
{
    return (uint32_t)(READ_BIT(CMU->CCFR, CMU_CCFR_REFPSC_Msk));
}

/**
  * @brief    Set CCL Calibration Clock Source
  * @rmtoll   CCFR    CALSEL    FL_CMU_CCL_SetCalibrationClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_CCL_CALCLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_CCL_CALCLK_SOURCE_RCLF
  *           @arg @ref FL_CMU_CCL_CALCLK_SOURCE_XTHF
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_CCL_SetCalibrationClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->CCFR, CMU_CCFR_CALSEL_Msk, clock);
}

/**
  * @brief    Get CCL Calibration Clock Source Setting
  * @rmtoll   CCFR    CALSEL    FL_CMU_CCL_GetCalibrationClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_CCL_CALCLK_SOURCE_RCHF
  *           @arg @ref FL_CMU_CCL_CALCLK_SOURCE_RCLF
  *           @arg @ref FL_CMU_CCL_CALCLK_SOURCE_XTHF
  */
__STATIC_INLINE uint32_t FL_CMU_CCL_GetCalibrationClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->CCFR, CMU_CCFR_CALSEL_Msk));
}

/**
  * @brief    Set CCL Reference Clock Source
  * @rmtoll   CCFR    REFSEL    FL_CMU_CCL_SetReferenceClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_CMU_CCL_REFCLK_SOURCE_XTLF
  *           @arg @ref FL_CMU_CCL_REFCLK_SOURCE_RCLP
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_CCL_SetReferenceClockSource(uint32_t clock)
{
    MODIFY_REG(CMU->CCFR, CMU_CCFR_REFSEL_Msk, clock);
}

/**
  * @brief    Get CCL Reference Clock Source Setting
  * @rmtoll   CCFR    REFSEL    FL_CMU_CCL_GetReferenceClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CMU_CCL_REFCLK_SOURCE_XTLF
  *           @arg @ref FL_CMU_CCL_REFCLK_SOURCE_RCLP
  */
__STATIC_INLINE uint32_t FL_CMU_CCL_GetReferenceClockSource(void)
{
    return (uint32_t)(READ_BIT(CMU->CCFR, CMU_CCFR_REFSEL_Msk));
}

/**
  * @brief    Get CCL Counter value
  * @rmtoll   CCNR    CCNT    FL_CMU_CCL_ReadCounter
  * @retval
  */
__STATIC_INLINE uint32_t FL_CMU_CCL_ReadCounter(void)
{
    return (uint32_t)(READ_BIT(CMU->CCNR, (0xffffU << 0U)) >> 0U);
}

/**
  * @brief    Get CCL interrupt flag
  * @rmtoll   CCISR    CCLIF    FL_CMU_IsActiveFlag_CCLComplete
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CMU_IsActiveFlag_CCLComplete(void)
{
    return (uint32_t)(READ_BIT(CMU->CCISR, CMU_CCISR_CCLIF_Msk) == (CMU_CCISR_CCLIF_Msk));
}

/**
  * @brief    Clear CCL interrupt flag
  * @rmtoll   CCISR    CCLIF    FL_CMU_ClearFlag_CCLComplete
  * @retval   None
  */
__STATIC_INLINE void FL_CMU_ClearFlag_CCLComplete(void)
{
    WRITE_REG(CMU->CCISR, CMU_CCISR_CCLIF_Msk);
}

/**
  * @}
  */

/** @defgroup CMU_FL_EF_QUERY Clock frequency query functions
  * @{
  */

uint32_t FL_CMU_GetPLLClockFreq(void);
uint32_t FL_CMU_GetRCHFClockFreq(void);
uint32_t FL_CMU_GetRCLFClockFreq(void);
uint32_t FL_CMU_GetSystemClockFreq(void);
uint32_t FL_CMU_GetAPBClockFreq(void);
uint32_t FL_CMU_GetAHBClockFreq(void);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __FM33LG0XX_FL_CMU_H*/

/*************************Py_Code_Generator Version: 0.1-0.14-0.1 @ 2020-10-20*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
