/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_rcc.h
  * @author  FMSH Application Team
  * @brief   Head file of RCC FL Module
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
#ifndef __FM33LC0XX_FL_RCC_H
#define __FM33LC0XX_FL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup RCC RCC
  * @brief RCC FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup RCC_FL_ES_INIT RCC Exported Init structures
  * @{
  */

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup RCC_FL_Exported_Constants RCC Exported Constants
  * @{
  */

#define    FDET_IER_HFDET_IE_Pos                                  (1U)
#define    FDET_IER_HFDET_IE_Msk                                  (0x1U << FDET_IER_HFDET_IE_Pos)
#define    FDET_IER_HFDET_IE                                      FDET_IER_HFDET_IE_Msk

#define    FDET_IER_LFDET_IE_Pos                                  (0U)
#define    FDET_IER_LFDET_IE_Msk                                  (0x1U << FDET_IER_LFDET_IE_Pos)
#define    FDET_IER_LFDET_IE                                      FDET_IER_LFDET_IE_Msk

#define    FDET_ISR_HFDETO_Pos                                    (9U)
#define    FDET_ISR_HFDETO_Msk                                    (0x1U << FDET_ISR_HFDETO_Pos)
#define    FDET_ISR_HFDETO                                        FDET_ISR_HFDETO_Msk

#define    FDET_ISR_LFDETO_Pos                                    (8U)
#define    FDET_ISR_LFDETO_Msk                                    (0x1U << FDET_ISR_LFDETO_Pos)
#define    FDET_ISR_LFDETO                                        FDET_ISR_LFDETO_Msk

#define    FDET_ISR_HFDETIF_Pos                                   (1U)
#define    FDET_ISR_HFDETIF_Msk                                   (0x1U << FDET_ISR_HFDETIF_Pos)
#define    FDET_ISR_HFDETIF                                       FDET_ISR_HFDETIF_Msk

#define    FDET_ISR_LFDETIF_Pos                                   (0U)
#define    FDET_ISR_LFDETIF_Msk                                   (0x1U << FDET_ISR_LFDETIF_Pos)
#define    FDET_ISR_LFDETIF                                       FDET_ISR_LFDETIF_Msk

#define    RCC_SYSCLKCR_LSCATS_Pos                                (27U)
#define    RCC_SYSCLKCR_LSCATS_Msk                                (0x1U << RCC_SYSCLKCR_LSCATS_Pos)
#define    RCC_SYSCLKCR_LSCATS                                    RCC_SYSCLKCR_LSCATS_Msk

#define    RCC_SYSCLKCR_SLP_ENEXTI_Pos                            (25U)
#define    RCC_SYSCLKCR_SLP_ENEXTI_Msk                            (0x1U << RCC_SYSCLKCR_SLP_ENEXTI_Pos)
#define    RCC_SYSCLKCR_SLP_ENEXTI                                RCC_SYSCLKCR_SLP_ENEXTI_Msk

#define    RCC_SYSCLKCR_APBPRES2_Pos                              (19U)
#define    RCC_SYSCLKCR_APBPRES2_Msk                              (0x7U << RCC_SYSCLKCR_APBPRES2_Pos)
#define    RCC_SYSCLKCR_APBPRES2                                  RCC_SYSCLKCR_APBPRES2_Msk

#define    RCC_SYSCLKCR_APBPRES1_Pos                              (16U)
#define    RCC_SYSCLKCR_APBPRES1_Msk                              (0x7U << RCC_SYSCLKCR_APBPRES1_Pos)
#define    RCC_SYSCLKCR_APBPRES1                                  RCC_SYSCLKCR_APBPRES1_Msk

#define    RCC_SYSCLKCR_AHBPRES_Pos                               (8U)
#define    RCC_SYSCLKCR_AHBPRES_Msk                               (0x7U << RCC_SYSCLKCR_AHBPRES_Pos)
#define    RCC_SYSCLKCR_AHBPRES                                   RCC_SYSCLKCR_AHBPRES_Msk

#define    RCC_SYSCLKCR_STCLKSEL_Pos                              (6U)
#define    RCC_SYSCLKCR_STCLKSEL_Msk                              (0x3U << RCC_SYSCLKCR_STCLKSEL_Pos)
#define    RCC_SYSCLKCR_STCLKSEL                                  RCC_SYSCLKCR_STCLKSEL_Msk

#define    RCC_SYSCLKCR_BCKOSEL_Pos                               (3U)
#define    RCC_SYSCLKCR_BCKOSEL_Msk                               (0x1U << RCC_SYSCLKCR_BCKOSEL_Pos)
#define    RCC_SYSCLKCR_BCKOSEL                                   RCC_SYSCLKCR_BCKOSEL_Msk

#define    RCC_SYSCLKCR_SYSCLKSEL_Pos                             (0U)
#define    RCC_SYSCLKCR_SYSCLKSEL_Msk                             (0x7U << RCC_SYSCLKCR_SYSCLKSEL_Pos)
#define    RCC_SYSCLKCR_SYSCLKSEL                                 RCC_SYSCLKCR_SYSCLKSEL_Msk

#define    RCC_RCHFCR_FSEL_Pos                                    (16U)
#define    RCC_RCHFCR_FSEL_Msk                                    (0xfU << RCC_RCHFCR_FSEL_Pos)
#define    RCC_RCHFCR_FSEL                                        RCC_RCHFCR_FSEL_Msk

#define    RCC_RCHFCR_EN_Pos                                      (0U)
#define    RCC_RCHFCR_EN_Msk                                      (0x1U << RCC_RCHFCR_EN_Pos)
#define    RCC_RCHFCR_EN                                          RCC_RCHFCR_EN_Msk

#define    RCC_RCMFTR_TRIM_Pos                                    (0U)
#define    RCC_RCMFTR_TRIM_Msk                                    (0x7fU << RCC_RCMFTR_TRIM_Pos)
#define    RCC_RCMFTR_TRIM                                        RCC_RCMFTR_TRIM_Msk

#define    RCC_PLLCR_EN_Pos                                       (0U)
#define    RCC_PLLCR_EN_Msk                                       (0x1U << RCC_PLLCR_EN_Pos)
#define    RCC_PLLCR_EN                                           RCC_PLLCR_EN_Msk

#define    RCC_PLLCR_LOCKED_Pos                                   (7U)
#define    RCC_PLLCR_LOCKED_Msk                                   (0x1U << RCC_PLLCR_LOCKED_Pos)
#define    RCC_PLLCR_LOCKED                                       RCC_PLLCR_LOCKED_Msk

#define    RCC_PLLCR_INSEL_Pos                                    (1U)
#define    RCC_PLLCR_INSEL_Msk                                    (0x1U << RCC_PLLCR_INSEL_Pos)
#define    RCC_PLLCR_INSEL                                        RCC_PLLCR_INSEL_Msk

#define    RCC_PLLCR_DB_Pos                                       (16U)
#define    RCC_PLLCR_DB_Msk                                       (0x7fU << RCC_PLLCR_DB_Pos)
#define    RCC_PLLCR_DB                                           RCC_PLLCR_DB_Msk

#define    RCC_PLLCR_REFPRSC_Pos                                  (4U)
#define    RCC_PLLCR_REFPRSC_Msk                                  (0x7U << RCC_PLLCR_REFPRSC_Pos)
#define    RCC_PLLCR_REFPRSC                                      RCC_PLLCR_REFPRSC_Msk

#define    RCC_PLLCR_OSEL_Pos                                     (3U)
#define    RCC_PLLCR_OSEL_Msk                                     (0x1U << RCC_PLLCR_OSEL_Pos)
#define    RCC_PLLCR_OSEL                                         RCC_PLLCR_OSEL_Msk

#define    RCC_LPOSCCR_LPOENB_Pos                                 (1U)
#define    RCC_LPOSCCR_LPOENB_Msk                                 (0x1U << RCC_LPOSCCR_LPOENB_Pos)
#define    RCC_LPOSCCR_LPOENB                                     RCC_LPOSCCR_LPOENB_Msk

#define    RCC_LPOSCCR_LPM_LPO_OFF_Pos                            (0U)
#define    RCC_LPOSCCR_LPM_LPO_OFF_Msk                            (0x1U << RCC_LPOSCCR_LPM_LPO_OFF_Pos)
#define    RCC_LPOSCCR_LPM_LPO_OFF                                RCC_LPOSCCR_LPM_LPO_OFF_Msk

#define    RCC_LPOSCCR_LPO_CHOP_EN_Pos                            (2U)
#define    RCC_LPOSCCR_LPO_CHOP_EN_Msk                            (0x1U << RCC_LPOSCCR_LPO_CHOP_EN_Pos)
#define    RCC_LPOSCCR_LPO_CHOP_EN                                RCC_LPOSCCR_LPO_CHOP_EN_Msk

#define    RCC_LPOSCTR_TRIM_Pos                                   (0U)
#define    RCC_LPOSCTR_TRIM_Msk                                   (0xffU << RCC_LPOSCTR_TRIM_Pos)
#define    RCC_LPOSCTR_TRIM                                       RCC_LPOSCTR_TRIM_Msk

#define    RCC_XTLFCR_EN_Pos                                      (8U)
#define    RCC_XTLFCR_EN_Msk                                      (0xfU << RCC_XTLFCR_EN_Pos)
#define    RCC_XTLFCR_EN                                          RCC_XTLFCR_EN_Msk

#define    RCC_XTLFCR_IPW_Pos                                     (0U)
#define    RCC_XTLFCR_IPW_Msk                                     (0x7U << RCC_XTLFCR_IPW_Pos)
#define    RCC_XTLFCR_IPW                                         RCC_XTLFCR_IPW_Msk

#define    RCC_XTHFCR_CFG_Pos                                     (8U)
#define    RCC_XTHFCR_CFG_Msk                                     (0x7U << RCC_XTHFCR_CFG_Pos)
#define    RCC_XTHFCR_CFG                                         RCC_XTHFCR_CFG_Msk

#define    RCC_XTHFCR_EN_Pos                                      (0U)
#define    RCC_XTHFCR_EN_Msk                                      (0x1U << RCC_XTHFCR_EN_Pos)
#define    RCC_XTHFCR_EN                                          RCC_XTHFCR_EN_Msk

#define    RCC_RCMFCR_PSC_Pos                                     (16U)
#define    RCC_RCMFCR_PSC_Msk                                     (0x3U << RCC_RCMFCR_PSC_Pos)
#define    RCC_RCMFCR_PSC                                         RCC_RCMFCR_PSC_Msk

#define    RCC_RCMFCR_EN_Pos                                      (0U)
#define    RCC_RCMFCR_EN_Msk                                      (0x1U << RCC_RCMFCR_EN_Pos)
#define    RCC_RCMFCR_EN                                          RCC_RCMFCR_EN_Msk

#define    RCC_RCHFTR_TRIM_Pos                                    (0U)
#define    RCC_RCHFTR_TRIM_Msk                                    (0x7fU << RCC_RCHFTR_TRIM_Pos)
#define    RCC_RCHFTR_TRIM                                        RCC_RCHFTR_TRIM_Msk

#define    RCC_OPCCR1_EXTICKS_Pos                                 (30U)
#define    RCC_OPCCR1_EXTICKS_Msk                                 (0x1U << RCC_OPCCR1_EXTICKS_Pos)
#define    RCC_OPCCR1_EXTICKS                                     RCC_OPCCR1_EXTICKS_Msk

#define    RCC_OPCCR1_LPUART1CKS_Pos                              (26U)
#define    RCC_OPCCR1_LPUART1CKS_Msk                              (0x3U << RCC_OPCCR1_LPUART1CKS_Pos)
#define    RCC_OPCCR1_LPUART1CKS                                  RCC_OPCCR1_LPUART1CKS_Msk

#define    RCC_OPCCR1_LPUART0CKS_Pos                              (24U)
#define    RCC_OPCCR1_LPUART0CKS_Msk                              (0x3U << RCC_OPCCR1_LPUART0CKS_Pos)
#define    RCC_OPCCR1_LPUART0CKS                                  RCC_OPCCR1_LPUART0CKS_Msk

#define    RCC_OPCCR1_I2CCKS_Pos                                  (16U)
#define    RCC_OPCCR1_I2CCKS_Msk                                  (0x3U << RCC_OPCCR1_I2CCKS_Pos)
#define    RCC_OPCCR1_I2CCKS                                      RCC_OPCCR1_I2CCKS_Msk

#define    RCC_OPCCR1_ATCKS_Pos                                   (6U)
#define    RCC_OPCCR1_ATCKS_Msk                                   (0x3U << RCC_OPCCR1_ATCKS_Pos)
#define    RCC_OPCCR1_ATCKS                                       RCC_OPCCR1_ATCKS_Msk

#define    RCC_OPCCR1_UART1CKS_Pos                                (2U)
#define    RCC_OPCCR1_UART1CKS_Msk                                (0x3U << RCC_OPCCR1_UART1CKS_Pos)
#define    RCC_OPCCR1_UART1CKS                                    RCC_OPCCR1_UART1CKS_Msk

#define    RCC_OPCCR1_UART0CKS_Pos                                (0U)
#define    RCC_OPCCR1_UART0CKS_Msk                                (0x3U << RCC_OPCCR1_UART0CKS_Pos)
#define    RCC_OPCCR1_UART0CKS                                    RCC_OPCCR1_UART0CKS_Msk

#define    RCC_OPCCR2_RNGPRSC_Pos                                 (28U)
#define    RCC_OPCCR2_RNGPRSC_Msk                                 (0x7U << RCC_OPCCR2_RNGPRSC_Pos)
#define    RCC_OPCCR2_RNGPRSC                                     RCC_OPCCR2_RNGPRSC_Msk

#define    RCC_OPCCR2_ADCPRSC_Pos                                 (24U)
#define    RCC_OPCCR2_ADCPRSC_Msk                                 (0x7U << RCC_OPCCR2_ADCPRSC_Pos)
#define    RCC_OPCCR2_ADCPRSC                                     RCC_OPCCR2_ADCPRSC_Msk

#define    RCC_OPCCR2_USBCKS_Pos                                  (18U)
#define    RCC_OPCCR2_USBCKS_Msk                                  (0x3U << RCC_OPCCR2_USBCKS_Pos)
#define    RCC_OPCCR2_USBCKS                                      RCC_OPCCR2_USBCKS_Msk

#define    RCC_OPCCR2_ADCCKS_Pos                                  (16U)
#define    RCC_OPCCR2_ADCCKS_Msk                                  (0x3U << RCC_OPCCR2_ADCCKS_Pos)
#define    RCC_OPCCR2_ADCCKS                                      RCC_OPCCR2_ADCCKS_Msk

#define    RCC_OPCCR2_LPT32CKS_Pos                                (8U)
#define    RCC_OPCCR2_LPT32CKS_Msk                                (0x3U << RCC_OPCCR2_LPT32CKS_Pos)
#define    RCC_OPCCR2_LPT32CKS                                    RCC_OPCCR2_LPT32CKS_Msk

#define    RCC_OPCCR2_BT32CKS_Pos                                 (0U)
#define    RCC_OPCCR2_BT32CKS_Msk                                 (0x3U << RCC_OPCCR2_BT32CKS_Pos)
#define    RCC_OPCCR2_BT32CKS                                     RCC_OPCCR2_BT32CKS_Msk

#define    RCC_AHBMCR_MPRIL_Pos                                   (0U)
#define    RCC_AHBMCR_MPRIL_Msk                                   (0x1U << RCC_AHBMCR_MPRIL_Pos)
#define    RCC_AHBMCR_MPRIL                                       RCC_AHBMCR_MPRIL_Msk

#define    RCC_LSCLKSEL_SEL_Pos                                   (0U)
#define    RCC_LSCLKSEL_SEL_Msk                                   (0xffU << RCC_LSCLKSEL_SEL_Pos)
#define    RCC_LSCLKSEL_SEL                                       RCC_LSCLKSEL_SEL_Msk

#define    RCC_PHYCR_PHYRST_Pos                                   (4U)
#define    RCC_PHYCR_PHYRST_Msk                                   (0x1U << RCC_PHYCR_PHYRST_Pos)
#define    RCC_PHYCR_PHYRST                                       RCC_PHYCR_PHYRST_Msk

#define    RCC_PHYCR_PD_Pos                                       (3U)
#define    RCC_PHYCR_PD_Msk                                       (0x1U << RCC_PHYCR_PD_Pos)
#define    RCC_PHYCR_PD                                           RCC_PHYCR_PD_Msk

#define    RCC_PHYCR_PLVREADY_Pos                                 (2U)
#define    RCC_PHYCR_PLVREADY_Msk                                 (0x1U << RCC_PHYCR_PLVREADY_Pos)
#define    RCC_PHYCR_PLVREADY                                     RCC_PHYCR_PLVREADY_Msk

#define    RCC_PHYCR_BCKPD_Pos                                    (1U)
#define    RCC_PHYCR_BCKPD_Msk                                    (0x1U << RCC_PHYCR_BCKPD_Pos)
#define    RCC_PHYCR_BCKPD                                        RCC_PHYCR_BCKPD_Msk

#define    RCC_PHYCR_BCKRST_Pos                                   (0U)
#define    RCC_PHYCR_BCKRST_Msk                                   (0x1U << RCC_PHYCR_BCKRST_Pos)
#define    RCC_PHYCR_BCKRST                                       RCC_PHYCR_BCKRST_Msk

#define    RCC_PHYBCKCR_CK48M_EN_Pos                              (8U)
#define    RCC_PHYBCKCR_CK48M_EN_Msk                              (0x1U << RCC_PHYBCKCR_CK48M_EN_Pos)
#define    RCC_PHYBCKCR_CK48M_EN                                  RCC_PHYBCKCR_CK48M_EN_Msk

#define    RCC_PHYBCKCR_CLKRDY_Pos                                (7U)
#define    RCC_PHYBCKCR_CLKRDY_Msk                                (0x1U << RCC_PHYBCKCR_CLKRDY_Pos)
#define    RCC_PHYBCKCR_CLKRDY                                    RCC_PHYBCKCR_CLKRDY_Msk

#define    RCC_PHYBCKCR_OUTCLKSEL_Pos                             (0U)
#define    RCC_PHYBCKCR_OUTCLKSEL_Msk                             (0x1U << RCC_PHYBCKCR_OUTCLKSEL_Pos)
#define    RCC_PHYBCKCR_OUTCLKSEL                                 RCC_PHYBCKCR_OUTCLKSEL_Msk

#define    RCC_LKPCR_RST_EN_Pos                                   (1U)
#define    RCC_LKPCR_RST_EN_Msk                                   (0x1U << RCC_LKPCR_RST_EN_Pos)
#define    RCC_LKPCR_RST_EN                                       RCC_LKPCR_RST_EN_Msk

#define    RCC_RSTFR_MDFN_FLAG_Pos                                (12U)
#define    RCC_RSTFR_MDFN_FLAG_Msk                                (0x1U << RCC_RSTFR_MDFN_FLAG_Pos)
#define    RCC_RSTFR_MDFN_FLAG                                    RCC_RSTFR_MDFN_FLAG_Msk

#define    RCC_RSTFR_NRSTN_FLAG_Pos                               (11U)
#define    RCC_RSTFR_NRSTN_FLAG_Msk                               (0x1U << RCC_RSTFR_NRSTN_FLAG_Pos)
#define    RCC_RSTFR_NRSTN_FLAG                                   RCC_RSTFR_NRSTN_FLAG_Msk

#define    RCC_RSTFR_TESTN_FLAG_Pos                               (10U)
#define    RCC_RSTFR_TESTN_FLAG_Msk                               (0x1U << RCC_RSTFR_TESTN_FLAG_Pos)
#define    RCC_RSTFR_TESTN_FLAG                                   RCC_RSTFR_TESTN_FLAG_Msk

#define    RCC_RSTFR_PORN_FLAG_Pos                                (9U)
#define    RCC_RSTFR_PORN_FLAG_Msk                                (0x1U << RCC_RSTFR_PORN_FLAG_Pos)
#define    RCC_RSTFR_PORN_FLAG                                    RCC_RSTFR_PORN_FLAG_Msk

#define    RCC_RSTFR_PDRN_FLAG_Pos                                (8U)
#define    RCC_RSTFR_PDRN_FLAG_Msk                                (0x1U << RCC_RSTFR_PDRN_FLAG_Pos)
#define    RCC_RSTFR_PDRN_FLAG                                    RCC_RSTFR_PDRN_FLAG_Msk

#define    RCC_RSTFR_SOFTN_FLAG_Pos                               (5U)
#define    RCC_RSTFR_SOFTN_FLAG_Msk                               (0x1U << RCC_RSTFR_SOFTN_FLAG_Pos)
#define    RCC_RSTFR_SOFTN_FLAG                                   RCC_RSTFR_SOFTN_FLAG_Msk

#define    RCC_RSTFR_IWDTN_FLAG_Pos                               (4U)
#define    RCC_RSTFR_IWDTN_FLAG_Msk                               (0x1U << RCC_RSTFR_IWDTN_FLAG_Pos)
#define    RCC_RSTFR_IWDTN_FLAG                                   RCC_RSTFR_IWDTN_FLAG_Msk

#define    RCC_RSTFR_WWDTN_FLAG_Pos                               (2U)
#define    RCC_RSTFR_WWDTN_FLAG_Msk                               (0x1U << RCC_RSTFR_WWDTN_FLAG_Pos)
#define    RCC_RSTFR_WWDTN_FLAG                                   RCC_RSTFR_WWDTN_FLAG_Msk

#define    RCC_RSTFR_LKUPN_FLAG_Pos                               (1U)
#define    RCC_RSTFR_LKUPN_FLAG_Msk                               (0x1U << RCC_RSTFR_LKUPN_FLAG_Pos)
#define    RCC_RSTFR_LKUPN_FLAG                                   RCC_RSTFR_LKUPN_FLAG_Msk

#define    RCC_RSTFR_NVICN_FLAG_Pos                               (0U)
#define    RCC_RSTFR_NVICN_FLAG_Msk                               (0x1U << RCC_RSTFR_NVICN_FLAG_Pos)
#define    RCC_RSTFR_NVICN_FLAG                                   RCC_RSTFR_NVICN_FLAG_Msk



#define    FL_RCC_GROUP1_BUSCLK_LPTIM32                           (0x1U << 0U)
#define    FL_RCC_GROUP1_BUSCLK_USB                               (0x1U << 1U)
#define    FL_RCC_GROUP1_BUSCLK_RTC                               (0x1U << 2U)
#define    FL_RCC_GROUP1_BUSCLK_PMU                               (0x1U << 3U)
#define    FL_RCC_GROUP1_BUSCLK_SCU                               (0x1U << 4U)
#define    FL_RCC_GROUP1_BUSCLK_IWDT                              (0x1U << 5U)
#define    FL_RCC_GROUP1_BUSCLK_ANAC                              (0x1U << 6U)
#define    FL_RCC_GROUP1_BUSCLK_PAD                               (0x1U << 7U)
#define    FL_RCC_GROUP1_BUSCLK_DCU                               (0x1U << 31U)
#define    FL_RCC_GROUP2_BUSCLK_CRC                               (0x1U << 0U)
#define    FL_RCC_GROUP2_BUSCLK_RNG                               (0x1U << 1U)
#define    FL_RCC_GROUP2_BUSCLK_AES                               (0x1U << 2U)
#define    FL_RCC_GROUP2_BUSCLK_LCD                               (0x1U << 3U)
#define    FL_RCC_GROUP2_BUSCLK_DMA                               (0x1U << 4U)
#define    FL_RCC_GROUP2_BUSCLK_FLASH                             (0x1U << 5U)
#define    FL_RCC_GROUP2_BUSCLK_RAMBIST                           (0x1U << 6U)
#define    FL_RCC_GROUP2_BUSCLK_WWDT                              (0x1U << 7U)
#define    FL_RCC_GROUP2_BUSCLK_ADC                               (0x1U << 8U)
#define    FL_RCC_GROUP2_BUSCLK_HDIV                              (0x1U << 9U)
#define    FL_RCC_GROUP3_BUSCLK_SPI1                              (0x1U << 0U)
#define    FL_RCC_GROUP3_BUSCLK_SPI2                              (0x1U << 1U)
#define    FL_RCC_GROUP3_BUSCLK_UART0                             (0x1U << 8U)
#define    FL_RCC_GROUP3_BUSCLK_UART1                             (0x1U << 9U)
#define    FL_RCC_GROUP3_BUSCLK_UART4                             (0x1U << 12U)
#define    FL_RCC_GROUP3_BUSCLK_UART5                             (0x1U << 13U)
#define    FL_RCC_GROUP3_BUSCLK_UARTIR                            (0x1U << 14U)
#define    FL_RCC_GROUP3_BUSCLK_LPUART0                           (0x1U << 15U)
#define    FL_RCC_GROUP3_BUSCLK_U7816                             (0x1U << 16U)
#define    FL_RCC_GROUP3_BUSCLK_LPUART1                           (0x1U << 18U)
#define    FL_RCC_GROUP3_BUSCLK_I2C                               (0x1U << 24U)
#define    FL_RCC_GROUP4_BUSCLK_BSTIM32                           (0x1U << 0U)
#define    FL_RCC_GROUP4_BUSCLK_GPTIM0                            (0x1U << 2U)
#define    FL_RCC_GROUP4_BUSCLK_GPTIM1                            (0x1U << 3U)
#define    FL_RCC_GROUP4_BUSCLK_ATIM                              (0x1U << 4U)
#define    FL_RCC_GROUP1_OPCLK_EXTI                               (0x1U << 31U)
#define    FL_RCC_GROUP1_OPCLK_LPUART1                            (0x1U << 29U)
#define    FL_RCC_GROUP1_OPCLK_LPUART0                            (0x1U << 28U)
#define    FL_RCC_GROUP1_OPCLK_I2C                                (0x1U << 20U)
#define    FL_RCC_GROUP1_OPCLK_ATIM                               (0x1U << 15U)
#define    FL_RCC_GROUP1_OPCLK_UART1                              (0x1U << 9U)
#define    FL_RCC_GROUP1_OPCLK_UART0                              (0x1U << 8U)
#define    FL_RCC_GROUP2_OPCLK_USB                                (0x1U << 23U)
#define    FL_RCC_GROUP2_OPCLK_FLASH                              (0x1U << 22U)
#define    FL_RCC_GROUP2_OPCLK_RNG                                (0x1U << 21U)
#define    FL_RCC_GROUP2_OPCLK_ADC                                (0x1U << 20U)
#define    FL_RCC_GROUP2_OPCLK_LPTIM32                            (0x1U << 12U)
#define    FL_RCC_GROUP2_OPCLK_BSTIM32                            (0x1U << 4U)
#define    FL_RCC_RSTAHB_DMA                                      (0x1U << 0U)
#define    FL_RCC_RSTAHB_USB                                      (0x1U << 1U)
#define    FL_RCC_RSTAPB_UART5                                    (0x1U << 31U)
#define    FL_RCC_RSTAPB_UART4                                    (0x1U << 30U)
#define    FL_RCC_RSTAPB_GPTIM1                                   (0x1U << 25U)
#define    FL_RCC_RSTAPB_GPTIM0                                   (0x1U << 24U)
#define    FL_RCC_RSTAPB_LCD                                      (0x1U << 16U)
#define    FL_RCC_RSTAPB_U7816                                    (0x1U << 14U)
#define    FL_RCC_RSTAPB_SPI2                                     (0x1U << 10U)
#define    FL_RCC_RSTAPB_LPUART0                                  (0x1U << 6U)
#define    FL_RCC_RSTAPB_I2C                                      (0x1U << 3U)
#define    FL_RCC_RSTAPB_LPTIM32                                  (0x1U << 0U)
#define    FL_RCC_RSTAPB_ATIM                                     (0x1U << 31U)
#define    FL_RCC_RSTAPB_BSTIM32                                  (0x1U << 28U)
#define    FL_RCC_RSTAPB_ADCCR                                    (0x1U << 24U)
#define    FL_RCC_RSTAPB_ADC                                      (0x1U << 23U)
#define    FL_RCC_RSTAPB_OPA                                      (0x1U << 22U)
#define    FL_RCC_RSTAPB_DIVAS                                    (0x1U << 19U)
#define    FL_RCC_RSTAPB_AES                                      (0x1U << 18U)
#define    FL_RCC_RSTAPB_CRC                                      (0x1U << 17U)
#define    FL_RCC_RSTAPB_RNG                                      (0x1U << 16U)
#define    FL_RCC_RSTAPB_UART1                                    (0x1U << 12U)
#define    FL_RCC_RSTAPB_UART0                                    (0x1U << 11U)
#define    FL_RCC_RSTAPB_SPI1                                     (0x1U << 9U)
#define    FL_RCC_RSTAPB_UCIR                                     (0x1U << 8U)
#define    FL_RCC_RSTAPB_LPUART1                                  (0x1U << 7U)
#define    FL_RCC_PERIPHERAL_RESET_KEY                            0x13579BDFU
#define    FL_RCC_SOFTWARE_RESET_KEY                              0x5C5CAABBU
#define    FL_RCC_LPUART_CLK_SOURCE_LSCLK                         0x0U
#define    FL_RCC_LPUART_CLK_SOURCE_RCHF                          0x1U
#define    FL_RCC_LPUART_CLK_SOURCE_RCMF                          0x2U



#define    FL_RCC_APB2CLK_PSC_DIV1                                (0x0U << RCC_SYSCLKCR_APBPRES2_Pos)
#define    FL_RCC_APB2CLK_PSC_DIV2                                (0x4U << RCC_SYSCLKCR_APBPRES2_Pos)
#define    FL_RCC_APB2CLK_PSC_DIV4                                (0x5U << RCC_SYSCLKCR_APBPRES2_Pos)
#define    FL_RCC_APB2CLK_PSC_DIV8                                (0x6U << RCC_SYSCLKCR_APBPRES2_Pos)
#define    FL_RCC_APB2CLK_PSC_DIV16                               (0x7U << RCC_SYSCLKCR_APBPRES2_Pos)


#define    FL_RCC_APB1CLK_PSC_DIV1                                (0x0U << RCC_SYSCLKCR_APBPRES1_Pos)
#define    FL_RCC_APB1CLK_PSC_DIV2                                (0x4U << RCC_SYSCLKCR_APBPRES1_Pos)
#define    FL_RCC_APB1CLK_PSC_DIV4                                (0x5U << RCC_SYSCLKCR_APBPRES1_Pos)
#define    FL_RCC_APB1CLK_PSC_DIV8                                (0x6U << RCC_SYSCLKCR_APBPRES1_Pos)
#define    FL_RCC_APB1CLK_PSC_DIV16                               (0x7U << RCC_SYSCLKCR_APBPRES1_Pos)


#define    FL_RCC_AHBCLK_PSC_DIV1                                 (0x0U << RCC_SYSCLKCR_AHBPRES_Pos)
#define    FL_RCC_AHBCLK_PSC_DIV2                                 (0x4U << RCC_SYSCLKCR_AHBPRES_Pos)
#define    FL_RCC_AHBCLK_PSC_DIV4                                 (0x5U << RCC_SYSCLKCR_AHBPRES_Pos)
#define    FL_RCC_AHBCLK_PSC_DIV8                                 (0x6U << RCC_SYSCLKCR_AHBPRES_Pos)
#define    FL_RCC_AHBCLK_PSC_DIV16                                (0x7U << RCC_SYSCLKCR_AHBPRES_Pos)


#define    FL_RCC_SYSTICK_CLK_SOURCE_SCLK                         (0x0U << RCC_SYSCLKCR_STCLKSEL_Pos)
#define    FL_RCC_SYSTICK_CLK_SOURCE_LSCLK                        (0x1U << RCC_SYSCLKCR_STCLKSEL_Pos)
#define    FL_RCC_SYSTICK_CLK_SOURCE_RCMF                         (0x2U << RCC_SYSCLKCR_STCLKSEL_Pos)
#define    FL_RCC_SYSTICK_CLK_SOURCE_SYSCLK                       (0x3U << RCC_SYSCLKCR_STCLKSEL_Pos)


#define    FL_RCC_USB_CLK_OUT_48M                                 (0x0U << RCC_SYSCLKCR_BCKOSEL_Pos)
#define    FL_RCC_USB_CLK_OUT_120M                                (0x1U << RCC_SYSCLKCR_BCKOSEL_Pos)


#define    FL_RCC_SYSTEM_CLK_SOURCE_RCHF                          (0x0U << RCC_SYSCLKCR_SYSCLKSEL_Pos)
#define    FL_RCC_SYSTEM_CLK_SOURCE_XTHF                          (0x1U << RCC_SYSCLKCR_SYSCLKSEL_Pos)
#define    FL_RCC_SYSTEM_CLK_SOURCE_PLL                           (0x2U << RCC_SYSCLKCR_SYSCLKSEL_Pos)
#define    FL_RCC_SYSTEM_CLK_SOURCE_RCMF_PSC                      (0x4U << RCC_SYSCLKCR_SYSCLKSEL_Pos)
#define    FL_RCC_SYSTEM_CLK_SOURCE_LSCLK                         (0x5U << RCC_SYSCLKCR_SYSCLKSEL_Pos)
#define    FL_RCC_SYSTEM_CLK_SOURCE_LPOSC                         (0x6U << RCC_SYSCLKCR_SYSCLKSEL_Pos)
#define    FL_RCC_SYSTEM_CLK_SOURCE_USBCLK                        (0x7U << RCC_SYSCLKCR_SYSCLKSEL_Pos)


#define    FL_RCC_RCHF_FREQUENCY_8MHZ                             (0x0U << RCC_RCHFCR_FSEL_Pos)
#define    FL_RCC_RCHF_FREQUENCY_16MHZ                            (0x1U << RCC_RCHFCR_FSEL_Pos)
#define    FL_RCC_RCHF_FREQUENCY_24MHZ                            (0x2U << RCC_RCHFCR_FSEL_Pos)


#define    FL_RCC_PLL_CLK_SOURCE_RCHF                             (0x0U << RCC_PLLCR_INSEL_Pos)
#define    FL_RCC_PLL_CLK_SOURCE_XTHF                             (0x1U << RCC_PLLCR_INSEL_Pos)


#define    FL_RCC_PLL_MUL_32                                      (0x1fU << RCC_PLLCR_DB_Pos)

#define    FL_RCC_PLL_MUL_48                                      (0x2fU << RCC_PLLCR_DB_Pos)

#define    FL_RCC_PLL_PSC_DIV1                                    (0x0U << RCC_PLLCR_REFPRSC_Pos)
#define    FL_RCC_PLL_PSC_DIV2                                    (0x1U << RCC_PLLCR_REFPRSC_Pos)
#define    FL_RCC_PLL_PSC_DIV4                                    (0x2U << RCC_PLLCR_REFPRSC_Pos)
#define    FL_RCC_PLL_PSC_DIV8                                    (0x3U << RCC_PLLCR_REFPRSC_Pos)
#define    FL_RCC_PLL_PSC_DIV12                                   (0x4U << RCC_PLLCR_REFPRSC_Pos)
#define    FL_RCC_PLL_PSC_DIV16                                   (0x5U << RCC_PLLCR_REFPRSC_Pos)
#define    FL_RCC_PLL_PSC_DIV24                                   (0x6U << RCC_PLLCR_REFPRSC_Pos)
#define    FL_RCC_PLL_PSC_DIV32                                   (0x7U << RCC_PLLCR_REFPRSC_Pos)


#define    FL_RCC_PLL_OUTPUT_X1                                   (0x0U << RCC_PLLCR_OSEL_Pos)
#define    FL_RCC_PLL_OUTPUT_X2                                   (0x1U << RCC_PLLCR_OSEL_Pos)


#define    FL_RCC_XTLF_FDET_ENABLE                                (0x5U << RCC_XTLFCR_EN_Pos)
#define    FL_RCC_XTLF_FDET_DISABLE                               (0xaU << RCC_XTLFCR_EN_Pos)

#define    FL_RCC_XTLF_WORK_CURRENT_450NA                         (0x0U << RCC_XTLFCR_IPW_Pos)
#define    FL_RCC_XTLF_WORK_CURRENT_400NA                         (0x1U << RCC_XTLFCR_IPW_Pos)
#define    FL_RCC_XTLF_WORK_CURRENT_350NA                         (0x2U << RCC_XTLFCR_IPW_Pos)
#define    FL_RCC_XTLF_WORK_CURRENT_300NA                         (0x3U << RCC_XTLFCR_IPW_Pos)
#define    FL_RCC_XTLF_WORK_CURRENT_250NA                         (0x4U << RCC_XTLFCR_IPW_Pos)
#define    FL_RCC_XTLF_WORK_CURRENT_200NA                         (0x5U << RCC_XTLFCR_IPW_Pos)
#define    FL_RCC_XTLF_WORK_CURRENT_150NA                         (0x6U << RCC_XTLFCR_IPW_Pos)
#define    FL_RCC_XTLF_WORK_CURRENT_100NA                         (0x7U << RCC_XTLFCR_IPW_Pos)


#define    FL_RCC_RCMF_PSC_DIV1                                   (0x0U << RCC_RCMFCR_PSC_Pos)
#define    FL_RCC_RCMF_PSC_DIV4                                   (0x1U << RCC_RCMFCR_PSC_Pos)
#define    FL_RCC_RCMF_PSC_DIV8                                   (0x2U << RCC_RCMFCR_PSC_Pos)
#define    FL_RCC_RCMF_PSC_DIV16                                  (0x3U << RCC_RCMFCR_PSC_Pos)


#define    FL_RCC_EXTI_CLK_SOURCE_LSCLK                           (0x1U << RCC_OPCCR1_EXTICKS_Pos)
#define    FL_RCC_EXTI_CLK_SOURCE_HCLK                            (0x0U << RCC_OPCCR1_EXTICKS_Pos)


#define    FL_RCC_LPUART1_CLK_SOURCE_LSCLK                        (0x0U << RCC_OPCCR1_LPUART1CKS_Pos)
#define    FL_RCC_LPUART1_CLK_SOURCE_RCHF                         (0x1U << RCC_OPCCR1_LPUART1CKS_Pos)
#define    FL_RCC_LPUART1_CLK_SOURCE_RCMF                         (0x2U << RCC_OPCCR1_LPUART1CKS_Pos)


#define    FL_RCC_LPUART0_CLK_SOURCE_LSCLK                        (0x0U << RCC_OPCCR1_LPUART0CKS_Pos)
#define    FL_RCC_LPUART0_CLK_SOURCE_RCHF                         (0x1U << RCC_OPCCR1_LPUART0CKS_Pos)
#define    FL_RCC_LPUART0_CLK_SOURCE_RCMF                         (0x2U << RCC_OPCCR1_LPUART0CKS_Pos)


#define    FL_RCC_I2C_CLK_SOURCE_APB1CLK                          (0x0U << RCC_OPCCR1_I2CCKS_Pos)
#define    FL_RCC_I2C_CLK_SOURCE_RCHF                             (0x1U << RCC_OPCCR1_I2CCKS_Pos)
#define    FL_RCC_I2C_CLK_SOURCE_SYSCLK                           (0x2U << RCC_OPCCR1_I2CCKS_Pos)
#define    FL_RCC_I2C_CLK_SOURCE_RCMF_PSC                         (0x3U << RCC_OPCCR1_I2CCKS_Pos)


#define    FL_RCC_ATIM_CLK_SOURCE_APB2CLK                         (0x0U << RCC_OPCCR1_ATCKS_Pos)
#define    FL_RCC_ATIM_CLK_SOURCE_USBPHYBCK120M                   (0x1U << RCC_OPCCR1_ATCKS_Pos)
#define    FL_RCC_ATIM_CLK_SOURCE_PLLx2                           (0x3U << RCC_OPCCR1_ATCKS_Pos)


#define    FL_RCC_UART1_CLK_SOURCE_APB1CLK                        (0x0U << RCC_OPCCR1_UART1CKS_Pos)
#define    FL_RCC_UART1_CLK_SOURCE_RCHF                           (0x1U << RCC_OPCCR1_UART1CKS_Pos)
#define    FL_RCC_UART1_CLK_SOURCE_SYSCLK                         (0x2U << RCC_OPCCR1_UART1CKS_Pos)
#define    FL_RCC_UART1_CLK_SOURCE_RCMF_PSC                       (0x3U << RCC_OPCCR1_UART1CKS_Pos)


#define    FL_RCC_UART0_CLK_SOURCE_APB1CLK                        (0x0U << RCC_OPCCR1_UART0CKS_Pos)
#define    FL_RCC_UART0_CLK_SOURCE_RCHF                           (0x1U << RCC_OPCCR1_UART0CKS_Pos)
#define    FL_RCC_UART0_CLK_SOURCE_SYSCLK                         (0x2U << RCC_OPCCR1_UART0CKS_Pos)
#define    FL_RCC_UART0_CLK_SOURCE_RCMF_PSC                       (0x3U << RCC_OPCCR1_UART0CKS_Pos)


#define    FL_RCC_RNG_PSC_DIV1                                    (0x0U << RCC_OPCCR2_RNGPRSC_Pos)
#define    FL_RCC_RNG_PSC_DIV2                                    (0x1U << RCC_OPCCR2_RNGPRSC_Pos)
#define    FL_RCC_RNG_PSC_DIV4                                    (0x2U << RCC_OPCCR2_RNGPRSC_Pos)
#define    FL_RCC_RNG_PSC_DIV8                                    (0x3U << RCC_OPCCR2_RNGPRSC_Pos)
#define    FL_RCC_RNG_PSC_DIV16                                   (0x4U << RCC_OPCCR2_RNGPRSC_Pos)
#define    FL_RCC_RNG_PSC_DIV32                                   (0x5U << RCC_OPCCR2_RNGPRSC_Pos)


#define    FL_RCC_ADC_PSC_DIV1                                    (0x0U << RCC_OPCCR2_ADCPRSC_Pos)
#define    FL_RCC_ADC_PSC_DIV2                                    (0x1U << RCC_OPCCR2_ADCPRSC_Pos)
#define    FL_RCC_ADC_PSC_DIV4                                    (0x2U << RCC_OPCCR2_ADCPRSC_Pos)
#define    FL_RCC_ADC_PSC_DIV8                                    (0x3U << RCC_OPCCR2_ADCPRSC_Pos)
#define    FL_RCC_ADC_PSC_DIV16                                   (0x4U << RCC_OPCCR2_ADCPRSC_Pos)
#define    FL_RCC_ADC_PSC_DIV32                                   (0x5U << RCC_OPCCR2_ADCPRSC_Pos)


#define    FL_RCC_USB_CLK_REF_XTLF                                (0x0U << RCC_OPCCR2_USBCKS_Pos)
#define    FL_RCC_USB_CLK_REF_XTHF                                (0x1U << RCC_OPCCR2_USBCKS_Pos)
#define    FL_RCC_USB_CLK_REF_RCHF                                (0x2U << RCC_OPCCR2_USBCKS_Pos)


#define    FL_RCC_ADC_CLK_SOURCE_RCMF_PSC                         (0x0U << RCC_OPCCR2_ADCCKS_Pos)
#define    FL_RCC_ADC_CLK_SOURCE_RCHF                             (0x1U << RCC_OPCCR2_ADCCKS_Pos)
#define    FL_RCC_ADC_CLK_SOURCE_XTHF                             (0x2U << RCC_OPCCR2_ADCCKS_Pos)
#define    FL_RCC_ADC_CLK_SOURCE_PLL                              (0x3U << RCC_OPCCR2_ADCCKS_Pos)


#define    FL_RCC_LPTIM32_CLK_SOURCE_APB1CLK                      (0x0U << RCC_OPCCR2_LPT32CKS_Pos)
#define    FL_RCC_LPTIM32_CLK_SOURCE_LSCLK                        (0x1U << RCC_OPCCR2_LPT32CKS_Pos)
#define    FL_RCC_LPTIM32_CLK_SOURCE_LPOSC                        (0x2U << RCC_OPCCR2_LPT32CKS_Pos)
#define    FL_RCC_LPTIM32_CLK_SOURCE_RCMF_PSC                     (0x3U << RCC_OPCCR2_LPT32CKS_Pos)


#define    FL_RCC_BSTIM32_CLK_SOURCE_APB2CLK                      (0x0U << RCC_OPCCR2_BT32CKS_Pos)
#define    FL_RCC_BSTIM32_CLK_SOURCE_LSCLK                        (0x1U << RCC_OPCCR2_BT32CKS_Pos)
#define    FL_RCC_BSTIM32_CLK_SOURCE_LPOSC                        (0x2U << RCC_OPCCR2_BT32CKS_Pos)
#define    FL_RCC_BSTIM32_CLK_SOURCE_RCMF_PSC                     (0x3U << RCC_OPCCR2_BT32CKS_Pos)


#define    FL_RCC_AHB_MASTER_PRIORITY_DMA_FIRST                   (0x0U << RCC_AHBMCR_MPRIL_Pos)
#define    FL_RCC_AHB_MASTER_PRIORITY_CPU_FIRST                   (0x1U << RCC_AHBMCR_MPRIL_Pos)


#define    FL_RCC_LSCLK_CLK_SOURCE_LPOSC                          (0x55U << RCC_LSCLKSEL_SEL_Pos)
#define    FL_RCC_LSCLK_CLK_SOURCE_XTLF                           (0xAAU << RCC_LSCLKSEL_SEL_Pos)

#define    FL_RCC_USB_CLK_REF_SOURCE_SOF                          (0x0U << RCC_PHYBCKCR_OUTCLKSEL_Pos)
#define    FL_RCC_USB_CLK_REF_SOURCE_CORECLKIN                    (0x1U << RCC_PHYBCKCR_OUTCLKSEL_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup RCC_FL_Exported_Functions RCC Exported Functions
  * @{
  */

/**
  * @brief    Enable XTHF Fail Interrupt
  * @rmtoll   IER    HFDET_IE    FL_FDET_EnableIT_XTHFFail
  * @retval   None
  */
__STATIC_INLINE void FL_FDET_EnableIT_XTHFFail(void)
{
    SET_BIT(FDET->IER, FDET_IER_HFDET_IE_Msk);
}

/**
  * @brief    Get XTHF Fail Interrupt Enable Status
  * @rmtoll   IER    HFDET_IE    FL_FDET_IsEnabledIT_XTHFFail
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FDET_IsEnabledIT_XTHFFail(void)
{
    return (uint32_t)(READ_BIT(FDET->IER, FDET_IER_HFDET_IE_Msk) == FDET_IER_HFDET_IE_Msk);
}

/**
  * @brief    Disable XTHF Fail Interrupt
  * @rmtoll   IER    HFDET_IE    FL_FDET_DisableIT_XTHFFail
  * @retval   None
  */
__STATIC_INLINE void FL_FDET_DisableIT_XTHFFail(void)
{
    CLEAR_BIT(FDET->IER, FDET_IER_HFDET_IE_Msk);
}

/**
  * @brief    Enable XTLF Fail Interrupt
  * @rmtoll   IER    LFDET_IE    FL_FDET_EnableIT_XTLFFail
  * @retval   None
  */
__STATIC_INLINE void FL_FDET_EnableIT_XTLFFail(void)
{
    SET_BIT(FDET->IER, FDET_IER_LFDET_IE_Msk);
}

/**
  * @brief    Get XTLF Fail Interrupt Enable Status
  * @rmtoll   IER    LFDET_IE    FL_FDET_IsEnabledIT_XTLFFail
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FDET_IsEnabledIT_XTLFFail(void)
{
    return (uint32_t)(READ_BIT(FDET->IER, FDET_IER_LFDET_IE_Msk) == FDET_IER_LFDET_IE_Msk);
}

/**
  * @brief    Disable XTLF Fail Interrupt
  * @rmtoll   IER    LFDET_IE    FL_FDET_DisableIT_XTLFFail
  * @retval   None
  */
__STATIC_INLINE void FL_FDET_DisableIT_XTLFFail(void)
{
    CLEAR_BIT(FDET->IER, FDET_IER_LFDET_IE_Msk);
}

/**
  * @brief    Get XTHF Vibrating Output
  * @rmtoll   ISR    HFDETO    FL_FDET_IsActiveFlag_XTHFFailOutput
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FDET_IsActiveFlag_XTHFFailOutput(void)
{
    return (uint32_t)(READ_BIT(FDET->ISR, FDET_ISR_HFDETO_Msk) == (FDET_ISR_HFDETO_Msk));
}

/**
  * @brief    Get XTLF Vibrating Output
  * @rmtoll   ISR    LFDETO    FL_FDET_IsActiveFlag_XTLFFailOutput
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FDET_IsActiveFlag_XTLFFailOutput(void)
{
    return (uint32_t)(READ_BIT(FDET->ISR, FDET_ISR_LFDETO_Msk) == (FDET_ISR_LFDETO_Msk));
}

/**
  * @brief    Get XTHF Vibrating Flag
  * @rmtoll   ISR    HFDETIF    FL_FDET_IsActiveFlag_XTHFFail
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FDET_IsActiveFlag_XTHFFail(void)
{
    return (uint32_t)(READ_BIT(FDET->ISR, FDET_ISR_HFDETIF_Msk) == (FDET_ISR_HFDETIF_Msk));
}

/**
  * @brief    Clear XTHF Vibrating Flag
  * @rmtoll   ISR    HFDETIF    FL_FDET_ClearFlag_XTHFFail
  * @retval   None
  */
__STATIC_INLINE void FL_FDET_ClearFlag_XTHFFail(void)
{
    WRITE_REG(FDET->ISR, FDET_ISR_LFDETIF_Msk);
}

/**
  * @brief    Get XTLF Vibrating Output
  * @rmtoll   ISR    LFDETIF    FL_FDET_IsActiveFlag_XTLFFail
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FDET_IsActiveFlag_XTLFFail(void)
{
    return (uint32_t)(READ_BIT(FDET->ISR, FDET_ISR_LFDETIF_Msk) == (FDET_ISR_LFDETIF_Msk));
}

/**
  * @brief    Clear XTLF Vibrating Output
  * @rmtoll   ISR    LFDETIF    FL_FDET_ClearFlag_XTLFFail
  * @retval   None
  */
__STATIC_INLINE void FL_FDET_ClearFlag_XTLFFail(void)
{
    WRITE_REG(FDET->ISR, FDET_ISR_HFDETIF_Msk);
}

/**
  * @brief    Enable LSCLK Auto Switch
  * @rmtoll   SYSCLKCR    LSCATS    FL_RCC_EnableLSCLKAutoSwitch
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableLSCLKAutoSwitch(void)
{
    SET_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_LSCATS_Msk);
}

/**
  * @brief    Get LSCLK Auto Switch Enable Status
  * @rmtoll   SYSCLKCR    LSCATS    FL_RCC_IsEnabledLSCLKAutoSwitch
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledLSCLKAutoSwitch(void)
{
    return (uint32_t)(READ_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_LSCATS_Msk) == RCC_SYSCLKCR_LSCATS_Msk);
}

/**
  * @brief    Disable LSCLK Auto Switch
  * @rmtoll   SYSCLKCR    LSCATS    FL_RCC_DisableLSCLKAutoSwitch
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableLSCLKAutoSwitch(void)
{
    CLEAR_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_LSCATS_Msk);
}

/**
  * @brief    Enable Sleep/DeepSleep Mode External Interrupt
  * @rmtoll   SYSCLKCR    SLP_ENEXTI    FL_RCC_EnableEXTIOnSleep
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableEXTIOnSleep(void)
{
    SET_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_SLP_ENEXTI_Msk);
}

/**
  * @brief    Get Sleep/DeepSleep Mode External Interrupt Enable Status
  * @rmtoll   SYSCLKCR    SLP_ENEXTI    FL_RCC_IsEnabledEXTIOnSleep
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledEXTIOnSleep(void)
{
    return (uint32_t)(READ_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_SLP_ENEXTI_Msk) == RCC_SYSCLKCR_SLP_ENEXTI_Msk);
}

/**
  * @brief    Disable Sleep/DeepSleep Mode External Interrupt
  * @rmtoll   SYSCLKCR    SLP_ENEXTI    FL_RCC_DisableEXTIOnSleep
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableEXTIOnSleep(void)
{
    CLEAR_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_SLP_ENEXTI_Msk);
}

/**
  * @brief    Set APB2 Prescaler
  * @rmtoll   SYSCLKCR    APBPRES2    FL_RCC_SetAPB2Prescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_RCC_APB2CLK_PSC_DIV1
  *           @arg @ref FL_RCC_APB2CLK_PSC_DIV2
  *           @arg @ref FL_RCC_APB2CLK_PSC_DIV4
  *           @arg @ref FL_RCC_APB2CLK_PSC_DIV8
  *           @arg @ref FL_RCC_APB2CLK_PSC_DIV16
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetAPB2Prescaler(uint32_t prescaler)
{
    MODIFY_REG(RCC->SYSCLKCR, RCC_SYSCLKCR_APBPRES2_Msk, prescaler);
}

/**
  * @brief    Get APB2 Prescaler
  * @rmtoll   SYSCLKCR    APBPRES2    FL_RCC_GetAPB2Prescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_APB2CLK_PSC_DIV1
  *           @arg @ref FL_RCC_APB2CLK_PSC_DIV2
  *           @arg @ref FL_RCC_APB2CLK_PSC_DIV4
  *           @arg @ref FL_RCC_APB2CLK_PSC_DIV8
  *           @arg @ref FL_RCC_APB2CLK_PSC_DIV16
  */
__STATIC_INLINE uint32_t FL_RCC_GetAPB2Prescaler(void)
{
    return (uint32_t)(READ_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_APBPRES2_Msk));
}

/**
  * @brief    Set APB1 Prescaler
  * @rmtoll   SYSCLKCR    APBPRES1    FL_RCC_SetAPB1Prescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_RCC_APB1CLK_PSC_DIV1
  *           @arg @ref FL_RCC_APB1CLK_PSC_DIV2
  *           @arg @ref FL_RCC_APB1CLK_PSC_DIV4
  *           @arg @ref FL_RCC_APB1CLK_PSC_DIV8
  *           @arg @ref FL_RCC_APB1CLK_PSC_DIV16
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetAPB1Prescaler(uint32_t prescaler)
{
    MODIFY_REG(RCC->SYSCLKCR, RCC_SYSCLKCR_APBPRES1_Msk, prescaler);
}

/**
  * @brief    Get APB1 Prescaler
  * @rmtoll   SYSCLKCR    APBPRES1    FL_RCC_GetAPB1Prescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_APB1CLK_PSC_DIV1
  *           @arg @ref FL_RCC_APB1CLK_PSC_DIV2
  *           @arg @ref FL_RCC_APB1CLK_PSC_DIV4
  *           @arg @ref FL_RCC_APB1CLK_PSC_DIV8
  *           @arg @ref FL_RCC_APB1CLK_PSC_DIV16
  */
__STATIC_INLINE uint32_t FL_RCC_GetAPB1Prescaler(void)
{
    return (uint32_t)(READ_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_APBPRES1_Msk));
}

/**
  * @brief    Set AHB Prescaler
  * @rmtoll   SYSCLKCR    AHBPRES    FL_RCC_SetAHBPrescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_RCC_AHBCLK_PSC_DIV1
  *           @arg @ref FL_RCC_AHBCLK_PSC_DIV2
  *           @arg @ref FL_RCC_AHBCLK_PSC_DIV4
  *           @arg @ref FL_RCC_AHBCLK_PSC_DIV8
  *           @arg @ref FL_RCC_AHBCLK_PSC_DIV16
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetAHBPrescaler(uint32_t prescaler)
{
    MODIFY_REG(RCC->SYSCLKCR, RCC_SYSCLKCR_AHBPRES_Msk, prescaler);
}

/**
  * @brief    Get AHB Prescaler
  * @rmtoll   SYSCLKCR    AHBPRES    FL_RCC_GetAHBPrescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_AHBCLK_PSC_DIV1
  *           @arg @ref FL_RCC_AHBCLK_PSC_DIV2
  *           @arg @ref FL_RCC_AHBCLK_PSC_DIV4
  *           @arg @ref FL_RCC_AHBCLK_PSC_DIV8
  *           @arg @ref FL_RCC_AHBCLK_PSC_DIV16
  */
__STATIC_INLINE uint32_t FL_RCC_GetAHBPrescaler(void)
{
    return (uint32_t)(READ_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_AHBPRES_Msk));
}

/**
  * @brief    Set USB PHY BCK Output Clock Source
  * @rmtoll   SYSCLKCR    BCKOSEL    FL_RCC_SetUSBClockOutput
  * @param    output This parameter can be one of the following values:
  *           @arg @ref FL_RCC_USB_CLK_OUT_48M
  *           @arg @ref FL_RCC_USB_CLK_OUT_120M
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetUSBClockOutput(uint32_t output)
{
    MODIFY_REG(RCC->SYSCLKCR, RCC_SYSCLKCR_BCKOSEL_Msk, output);
}

/**
  * @brief    Get USB PHY BCK Output Clock Source Setting
  * @rmtoll   SYSCLKCR    BCKOSEL    FL_RCC_GetUSBClockOutput
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_USB_CLK_OUT_48M
  *           @arg @ref FL_RCC_USB_CLK_OUT_120M
  */
__STATIC_INLINE uint32_t FL_RCC_GetUSBClockOutput(void)
{
    return (uint32_t)(READ_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_BCKOSEL_Msk));
}

/**
  * @brief    Set System Clock Source
  * @rmtoll   SYSCLKCR    SYSCLKSEL    FL_RCC_SetSystemClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_XTHF
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_PLL
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_RCMF_PSC
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_LSCLK
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_LPOSC
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_USBCLK
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetSystemClockSource(uint32_t clock)
{
    MODIFY_REG(RCC->SYSCLKCR, RCC_SYSCLKCR_SYSCLKSEL_Msk, clock);
}

/**
  * @brief    Set System Clock Source Setting
  * @rmtoll   SYSCLKCR    SYSCLKSEL    FL_RCC_GetSystemClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_XTHF
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_PLL
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_RCMF_PSC
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_LSCLK
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_LPOSC
  *           @arg @ref FL_RCC_SYSTEM_CLK_SOURCE_USBCLK
  */
__STATIC_INLINE uint32_t FL_RCC_GetSystemClockSource(void)
{
    return (uint32_t)(READ_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_SYSCLKSEL_Msk));
}

/**
  * @brief    Set RCHF Frequency
  * @rmtoll   RCHFCR    FSEL    FL_RCC_RCHF_SetFrequency
  * @param    frequency This parameter can be one of the following values:
  *           @arg @ref FL_RCC_RCHF_FREQUENCY_8MHZ
  *           @arg @ref FL_RCC_RCHF_FREQUENCY_16MHZ
  *           @arg @ref FL_RCC_RCHF_FREQUENCY_24MHZ
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_RCHF_SetFrequency(uint32_t frequency)
{
    MODIFY_REG(RCC->RCHFCR, RCC_RCHFCR_FSEL_Msk, frequency);
}

/**
  * @brief    Get RCHF Frequency Setting
  * @rmtoll   RCHFCR    FSEL    FL_RCC_RCHF_GetFrequency
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_RCHF_FREQUENCY_8MHZ
  *           @arg @ref FL_RCC_RCHF_FREQUENCY_16MHZ
  *           @arg @ref FL_RCC_RCHF_FREQUENCY_24MHZ
  */
__STATIC_INLINE uint32_t FL_RCC_RCHF_GetFrequency(void)
{
    return (uint32_t)(READ_BIT(RCC->RCHFCR, RCC_RCHFCR_FSEL_Msk));
}

/**
  * @brief    Enable RCHF
  * @rmtoll   RCHFCR    EN    FL_RCC_RCHF_Enable
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_RCHF_Enable(void)
{
    SET_BIT(RCC->RCHFCR, RCC_RCHFCR_EN_Msk);
}

/**
  * @brief    Get RCHF Enable Status
  * @rmtoll   RCHFCR    EN    FL_RCC_RCHF_IsEnabled
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_RCHF_IsEnabled(void)
{
    return (uint32_t)(READ_BIT(RCC->RCHFCR, RCC_RCHFCR_EN_Msk) == RCC_RCHFCR_EN_Msk);
}

/**
  * @brief    Disable RCHF
  * @rmtoll   RCHFCR    EN    FL_RCC_RCHF_Disable
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_RCHF_Disable(void)
{
    CLEAR_BIT(RCC->RCHFCR, RCC_RCHFCR_EN_Msk);
}

/**
  * @brief    Set RCMF Frequency Trim Value
  * @rmtoll   RCMFTR    TRIM    FL_RCC_RCMF_WriteTrimValue
  * @param    value TrimValue The value of RCMF trim
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_RCMF_WriteTrimValue(uint32_t value)
{
    MODIFY_REG(RCC->RCMFTR, (0x7fU << 0U), (value << 0U));
}

/**
  * @brief    Get RCMF Frequency Trim Value
  * @rmtoll   RCMFTR    TRIM    FL_RCC_RCMF_ReadTrimValue
  * @retval   The Value of RCMF trim
  */
__STATIC_INLINE uint32_t FL_RCC_RCMF_ReadTrimValue(void)
{
    return (uint32_t)(READ_BIT(RCC->RCMFTR, 0x7fU) >> 0U);
}

/**
  * @brief    Enable PLL
  * @rmtoll   PLLCR    EN    FL_RCC_PLL_Enable
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_PLL_Enable(void)
{
    SET_BIT(RCC->PLLCR, RCC_PLLCR_EN_Msk);
}

/**
  * @brief    Get PLL Enable Status
  * @rmtoll   PLLCR    EN    FL_RCC_PLL_Disable
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_PLL_Disable(void)
{
    CLEAR_BIT(RCC->PLLCR, RCC_PLLCR_EN_Msk);
}

/**
  * @brief    Disable PLL
  * @rmtoll   PLLCR    EN    FL_RCC_PLL_IsEnabled
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_PLL_IsEnabled(void)
{
    return (uint32_t)(READ_BIT(RCC->PLLCR, RCC_PLLCR_EN_Msk) == RCC_PLLCR_EN_Msk);
}

/**
  * @brief    Get PLL Ready Status
  * @rmtoll   PLLCR    LOCKED    FL_RCC_IsActiveFlag_PLLReady
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsActiveFlag_PLLReady(void)
{
    return (uint32_t)(READ_BIT(RCC->PLLCR, RCC_PLLCR_LOCKED_Msk) == (RCC_PLLCR_LOCKED_Msk));
}

/**
  * @brief    Set PLL Input Source
  * @rmtoll   PLLCR    INSEL    FL_RCC_PLL_SetClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_PLL_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_PLL_CLK_SOURCE_XTHF
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_PLL_SetClockSource(uint32_t clock)
{
    MODIFY_REG(RCC->PLLCR, RCC_PLLCR_INSEL_Msk, clock);
}

/**
  * @brief    Get PLL Input Source Setting
  * @rmtoll   PLLCR    INSEL    FL_RCC_PLL_GetClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_PLL_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_PLL_CLK_SOURCE_XTHF
  */
__STATIC_INLINE uint32_t FL_RCC_PLL_GetClockSource(void)
{
    return (uint32_t)(READ_BIT(RCC->PLLCR, RCC_PLLCR_INSEL_Msk));
}

/**
  * @brief    Set PLL Multiplier
  * @rmtoll   PLLCR    DB    FL_RCC_PLL_WriteMultiplier
  * @param    multiplier
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_PLL_WriteMultiplier(uint32_t multiplier)
{
    MODIFY_REG(RCC->PLLCR, (0x7fU << 16U), (multiplier << 16U));
}

/**
  * @brief    Get PLL Multiplier Setting
  * @rmtoll   PLLCR    DB    FL_RCC_PLL_ReadMultiplier
  * @retval
  */
__STATIC_INLINE uint32_t FL_RCC_PLL_ReadMultiplier(void)
{
    return (uint32_t)(READ_BIT(RCC->PLLCR, (0x7fU << 16U)) >> 16U);
}

/**
  * @brief    Set PLL Prescaler
  * @rmtoll   PLLCR    REFPRSC    FL_RCC_PLL_SetPrescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_RCC_PLL_PSC_DIV1
  *           @arg @ref FL_RCC_PLL_PSC_DIV2
  *           @arg @ref FL_RCC_PLL_PSC_DIV4
  *           @arg @ref FL_RCC_PLL_PSC_DIV8
  *           @arg @ref FL_RCC_PLL_PSC_DIV12
  *           @arg @ref FL_RCC_PLL_PSC_DIV16
  *           @arg @ref FL_RCC_PLL_PSC_DIV24
  *           @arg @ref FL_RCC_PLL_PSC_DIV32
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_PLL_SetPrescaler(uint32_t prescaler)
{
    MODIFY_REG(RCC->PLLCR, RCC_PLLCR_REFPRSC_Msk, prescaler);
}

/**
  * @brief    Get PLL Prescaler Setting
  * @rmtoll   PLLCR    REFPRSC    FL_RCC_PLL_GetPrescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_PLL_PSC_DIV1
  *           @arg @ref FL_RCC_PLL_PSC_DIV2
  *           @arg @ref FL_RCC_PLL_PSC_DIV4
  *           @arg @ref FL_RCC_PLL_PSC_DIV8
  *           @arg @ref FL_RCC_PLL_PSC_DIV12
  *           @arg @ref FL_RCC_PLL_PSC_DIV16
  *           @arg @ref FL_RCC_PLL_PSC_DIV24
  *           @arg @ref FL_RCC_PLL_PSC_DIV32
  */
__STATIC_INLINE uint32_t FL_RCC_PLL_GetPrescaler(void)
{
    return (uint32_t)(READ_BIT(RCC->PLLCR, RCC_PLLCR_REFPRSC_Msk));
}

/**
  * @brief    Set PLL Digital Domain Output
  * @rmtoll   PLLCR    OSEL    FL_RCC_PLL_SetOutputMultiplier
  * @param    multiplier This parameter can be one of the following values:
  *           @arg @ref FL_RCC_PLL_OUTPUT_X1
  *           @arg @ref FL_RCC_PLL_OUTPUT_X2
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_PLL_SetOutputMultiplier(uint32_t multiplier)
{
    MODIFY_REG(RCC->PLLCR, RCC_PLLCR_OSEL_Msk, multiplier);
}

/**
  * @brief    Get PLL Digital Domain Output Setting
  * @rmtoll   PLLCR    OSEL    FL_RCC_PLL_GetOutputMultiplier
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_PLL_OUTPUT_X1
  *           @arg @ref FL_RCC_PLL_OUTPUT_X2
  */
__STATIC_INLINE uint32_t FL_RCC_PLL_GetOutputMultiplier(void)
{
    return (uint32_t)(READ_BIT(RCC->PLLCR, RCC_PLLCR_OSEL_Msk));
}

/**
  * @brief    Get LPOSC Enable Flag
  * @rmtoll   LPOSCCR    LPOENB    FL_RCC_LPOSC_IsEnabled
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_LPOSC_IsEnabled(void)
{
    return (uint32_t)!(READ_BIT(RCC->LPOSCCR, RCC_LPOSCCR_LPOENB_Msk) == RCC_LPOSCCR_LPOENB_Msk);
}

/**
  * @brief    Enable LPOSC On/Off in Low Power Mode
  * @rmtoll   LPOSCCR    LPM_LPO_OFF    FL_RCC_LPOSC_EnableSleepModeWork
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_LPOSC_EnableSleepModeWork(void)
{
    CLEAR_BIT(RCC->LPOSCCR, RCC_LPOSCCR_LPM_LPO_OFF_Msk);
}

/**
  * @brief    Get LPOSC On/Off Setting in Low Power Mode
  * @rmtoll   LPOSCCR    LPM_LPO_OFF    FL_RCC_LPOSC_IsEnableSleepModeWork
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_LPOSC_IsEnableSleepModeWork(void)
{
    return (uint32_t)!(READ_BIT(RCC->LPOSCCR, RCC_LPOSCCR_LPM_LPO_OFF_Msk) == RCC_LPOSCCR_LPM_LPO_OFF_Msk);
}

/**
  * @brief    Disable LPOSC On/Off Setting in Low Power Mode
  * @rmtoll   LPOSCCR    LPM_LPO_OFF    FL_RCC_LPOSC_DisableSleepModeWork
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_LPOSC_DisableSleepModeWork(void)
{
    SET_BIT(RCC->LPOSCCR, RCC_LPOSCCR_LPM_LPO_OFF_Msk);
}

/**
  * @brief    Enable LPOSC Chopper
  * @rmtoll   LPOSCCR    LPO_CHOP_EN    FL_RCC_LPOSC_EnableChopper
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_LPOSC_EnableChopper(void)
{
    SET_BIT(RCC->LPOSCCR, RCC_LPOSCCR_LPO_CHOP_EN_Msk);
}

/**
  * @brief    Get LPOSC Chopper Enable Status
  * @rmtoll   LPOSCCR    LPO_CHOP_EN    FL_RCC_LPOSC_IsEnabledChopper
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_LPOSC_IsEnabledChopper(void)
{
    return (uint32_t)(READ_BIT(RCC->LPOSCCR, RCC_LPOSCCR_LPO_CHOP_EN_Msk) == RCC_LPOSCCR_LPO_CHOP_EN_Msk);
}

/**
  * @brief    Disable LPOSC Chopper
  * @rmtoll   LPOSCCR    LPO_CHOP_EN    FL_RCC_LPOSC_DisableChopper
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_LPOSC_DisableChopper(void)
{
    CLEAR_BIT(RCC->LPOSCCR, RCC_LPOSCCR_LPO_CHOP_EN_Msk);
}

/**
  * @brief    Set LPOSC Frequency Trim Value
  * @rmtoll   LPOSCTR    TRIM    FL_RCC_LPOSC_WriteTrimValue
  * @param    value TrimValue The value of LPOSC trim
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_LPOSC_WriteTrimValue(uint32_t value)
{
    MODIFY_REG(RCC->LPOSCTR, (0xffU << 0U), (value << 0U));
}

/**
  * @brief    Get LPOSC Frequency Trim Value
  * @rmtoll   LPOSCTR    TRIM    FL_RCC_LPOSC_ReadTrimValue
  * @retval   The Value of LPOSC trim
  */
__STATIC_INLINE uint32_t FL_RCC_LPOSC_ReadTrimValue(void)
{
    return (uint32_t)(READ_BIT(RCC->LPOSCTR, 0xffU) >> 0U);
}

/**
  * @brief    Enable XTLF
  * @rmtoll   XTLFCR    EN    FL_RCC_XTLF_Enable
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_XTLF_Enable(void)
{
    MODIFY_REG(RCC->XTLFCR, RCC_XTLFCR_EN_Msk, FL_RCC_XTLF_FDET_ENABLE);
}

/**
  * @brief    Disable XTLF
  * @rmtoll   XTLFCR    EN    FL_RCC_XTLF_Disable
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_XTLF_Disable(void)
{
    MODIFY_REG(RCC->XTLFCR, RCC_XTLFCR_EN_Msk, FL_RCC_XTLF_FDET_DISABLE);
}

/**
  * @brief    Set XTLF Current
  * @rmtoll   XTLFCR    IPW    FL_RCC_XTLF_SetWorkCurrent
  * @param    current This parameter can be one of the following values:
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_450NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_400NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_350NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_300NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_250NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_200NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_150NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_100NA
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_XTLF_SetWorkCurrent(uint32_t current)
{
    MODIFY_REG(RCC->XTLFCR, RCC_XTLFCR_IPW_Msk, current);
}

/**
  * @brief    Get XTLF Current Setting
  * @rmtoll   XTLFCR    IPW    FL_RCC_XTLF_GetWorkCurrent
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_450NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_400NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_350NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_300NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_250NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_200NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_150NA
  *           @arg @ref FL_RCC_XTLF_WORK_CURRENT_100NA
  */
__STATIC_INLINE uint32_t FL_RCC_XTLF_GetWorkCurrent(void)
{
    return (uint32_t)(READ_BIT(RCC->XTLFCR, RCC_XTLFCR_IPW_Msk));
}

/**
  * @brief    Set XTHF Oscillation Strength
  * @rmtoll   XTHFCR    CFG    FL_RCC_XTHF_WriteDriverStrength
  * @param    strength
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_XTHF_WriteDriverStrength(uint32_t strength)
{
    MODIFY_REG(RCC->XTHFCR, (0x7U << 8U), (strength << 8U));
}

/**
  * @brief    Get XTHF Oscillation Strength Setting
  * @rmtoll   XTHFCR    CFG    FL_RCC_XTHF_ReadDriverStrength
  * @retval
  */
__STATIC_INLINE uint32_t FL_RCC_XTHF_ReadDriverStrength(void)
{
    return (uint32_t)(READ_BIT(RCC->XTHFCR, (0x7U << 8U)) >> 8U);
}

/**
  * @brief    Enable XTHF
  * @rmtoll   XTHFCR    EN    FL_RCC_XTHF_Enable
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_XTHF_Enable(void)
{
    SET_BIT(RCC->XTHFCR, RCC_XTHFCR_EN_Msk);
}

/**
  * @brief    Get XTHF Enable Status
  * @rmtoll   XTHFCR    EN    FL_RCC_XTHF_IsEnabled
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_XTHF_IsEnabled(void)
{
    return (uint32_t)(READ_BIT(RCC->XTHFCR, RCC_XTHFCR_EN_Msk) == RCC_XTHFCR_EN_Msk);
}

/**
  * @brief    Disable XTHF
  * @rmtoll   XTHFCR    EN    FL_RCC_XTHF_Disable
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_XTHF_Disable(void)
{
    CLEAR_BIT(RCC->XTHFCR, RCC_XTHFCR_EN_Msk);
}

/**
  * @brief    Set RCMF Output Prescaler
  * @rmtoll   RCMFCR    PSC    FL_RCC_RCMF_SetPrescaler
  * @param    Prescaler This parameter can be one of the following values:
  *           @arg @ref FL_RCC_RCMF_PSC_DIV1
  *           @arg @ref FL_RCC_RCMF_PSC_DIV4
  *           @arg @ref FL_RCC_RCMF_PSC_DIV8
  *           @arg @ref FL_RCC_RCMF_PSC_DIV16
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_RCMF_SetPrescaler(uint32_t Prescaler)
{
    MODIFY_REG(RCC->RCMFCR, RCC_RCMFCR_PSC_Msk, Prescaler);
}

/**
  * @brief    Get RCMF Output Prescaler Setting
  * @rmtoll   RCMFCR    PSC    FL_RCC_RCMF_GetPrescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_RCMF_PSC_DIV1
  *           @arg @ref FL_RCC_RCMF_PSC_DIV4
  *           @arg @ref FL_RCC_RCMF_PSC_DIV8
  *           @arg @ref FL_RCC_RCMF_PSC_DIV16
  */
__STATIC_INLINE uint32_t FL_RCC_RCMF_GetPrescaler(void)
{
    return (uint32_t)(READ_BIT(RCC->RCMFCR, RCC_RCMFCR_PSC_Msk));
}

/**
  * @brief    Enable RCMF
  * @rmtoll   RCMFCR    EN    FL_RCC_RCMF_Enable
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_RCMF_Enable(void)
{
    SET_BIT(RCC->RCMFCR, RCC_RCMFCR_EN_Msk);
}

/**
  * @brief    Get RCMF Enable Status
  * @rmtoll   RCMFCR    EN    FL_RCC_RCMF_IsEnabled
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_RCMF_IsEnabled(void)
{
    return (uint32_t)(READ_BIT(RCC->RCMFCR, RCC_RCMFCR_EN_Msk) == RCC_RCMFCR_EN_Msk);
}

/**
  * @brief    Disable RCMF
  * @rmtoll   RCMFCR    EN    FL_RCC_RCMF_Disable
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_RCMF_Disable(void)
{
    CLEAR_BIT(RCC->RCMFCR, RCC_RCMFCR_EN_Msk);
}

/**
  * @brief    Set RCHF Freqency Trim Value
  * @rmtoll   RCHFTR    TRIM    FL_RCC_RCHF_WriteTrimValue
  * @param    value TrimValue The value of RCHF trim
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_RCHF_WriteTrimValue(uint32_t value)
{
    MODIFY_REG(RCC->RCHFTR, (0x7fU << 0U), (value << 0U));
}

/**
  * @brief    Get RCHF Freqency Trim Value
  * @rmtoll   RCHFTR    TRIM    FL_RCC_RCHF_ReadTrimValue
  * @retval   The value of RCHF trim
  */
__STATIC_INLINE uint32_t FL_RCC_RCHF_ReadTrimValue(void)
{
    return (uint32_t)(READ_BIT(RCC->RCHFTR, 0x7fU) >> 0U);
}

/**
  * @brief    Enable Group1 Periph Bus Clock
  * @rmtoll   PCLKCR1        FL_RCC_EnableGroup1BusClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_LPTIM32
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_USB
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_RTC
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_PMU
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_SCU
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_IWDT
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_ANAC
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_PAD
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_DCU
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableGroup1BusClock(uint32_t Peripheral)
{
    SET_BIT(RCC->PCLKCR1, ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Enable Group2 Periph Bus Clock
  * @rmtoll   PCLKCR2        FL_RCC_EnableGroup2BusClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_CRC
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_RNG
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_AES
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_LCD
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_DMA
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_FLASH
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_RAMBIST
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_WWDT
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_ADC
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_HDIV
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableGroup2BusClock(uint32_t Peripheral)
{
    SET_BIT(RCC->PCLKCR2, ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Enable Group3 Periph Bus Clock
  * @rmtoll   PCLKCR3        FL_RCC_EnableGroup3BusClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_SPI1
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_SPI2
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UART0
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UART1
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UART4
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UART5
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UARTIR
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_LPUART0
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_U7816
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_LPUART1
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_I2C
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableGroup3BusClock(uint32_t Peripheral)
{
    SET_BIT(RCC->PCLKCR3, ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Enable Group4 Periph Bus Clock
  * @rmtoll   PCLKCR4        FL_RCC_EnableGroup4BusClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP4_BUSCLK_BSTIM32
  *           @arg @ref FL_RCC_GROUP4_BUSCLK_GPTIM0
  *           @arg @ref FL_RCC_GROUP4_BUSCLK_GPTIM1
  *           @arg @ref FL_RCC_GROUP4_BUSCLK_ATIM
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableGroup4BusClock(uint32_t Peripheral)
{
    SET_BIT(RCC->PCLKCR4, ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable Group1 Periph Bus Clock
  * @rmtoll   PCLKCR1        FL_RCC_DisableGroup1BusClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_LPTIM32
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_USB
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_RTC
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_PMU
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_SCU
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_IWDT
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_ANAC
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_PAD
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_DCU
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableGroup1BusClock(uint32_t Peripheral)
{
    CLEAR_BIT(RCC->PCLKCR1, ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable Group2 Periph Bus Clock
  * @rmtoll   PCLKCR2        FL_RCC_DisableGroup2BusClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_CRC
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_RNG
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_AES
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_LCD
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_DMA
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_FLASH
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_RAMBIST
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_WWDT
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_ADC
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_HDIV
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableGroup2BusClock(uint32_t Peripheral)
{
    CLEAR_BIT(RCC->PCLKCR2, ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable Group3 Periph Bus Clock
  * @rmtoll   PCLKCR3        FL_RCC_DisableGroup3BusClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_SPI1
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_SPI2
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UART0
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UART1
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UART4
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UART5
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UARTIR
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_LPUART0
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_U7816
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_LPUART1
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_I2C
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableGroup3BusClock(uint32_t Peripheral)
{
    CLEAR_BIT(RCC->PCLKCR3, ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable Group4 Periph Bus Clock
  * @rmtoll   PCLKCR4        FL_RCC_DisableGroup4BusClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP4_BUSCLK_BSTIM32
  *           @arg @ref FL_RCC_GROUP4_BUSCLK_GPTIM0
  *           @arg @ref FL_RCC_GROUP4_BUSCLK_GPTIM1
  *           @arg @ref FL_RCC_GROUP4_BUSCLK_ATIM
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableGroup4BusClock(uint32_t Peripheral)
{
    CLEAR_BIT(RCC->PCLKCR4, ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Get Group1 Periph Bus Clock Enable Status
  * @rmtoll   PCLKCR1        FL_RCC_IsEnabledGroup1BusClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_LPTIM32
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_USB
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_RTC
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_PMU
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_SCU
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_IWDT
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_ANAC
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_PAD
  *           @arg @ref FL_RCC_GROUP1_BUSCLK_DCU
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledGroup1BusClock(uint32_t Peripheral)
{
    return (uint32_t)(READ_BIT(RCC->PCLKCR1, ((Peripheral & 0xffffffff) << 0x0U)) == ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Get Group2 Periph Bus Clock Enable Status
  * @rmtoll   PCLKCR2        FL_RCC_IsEnabledGroup2BusClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_CRC
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_RNG
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_AES
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_LCD
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_DMA
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_FLASH
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_RAMBIST
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_WWDT
  *           @arg @ref FL_RCC_GROUP2_BUSCLK_ADC
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledGroup2BusClock(uint32_t Peripheral)
{
    return (uint32_t)(READ_BIT(RCC->PCLKCR2, ((Peripheral & 0xffffffff) << 0x0U)) == ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Get Group3 Periph Bus Clock Enable Status
  * @rmtoll   PCLKCR3        FL_RCC_IsEnabledGroup3BusClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_SPI1
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_SPI2
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UART0
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UART1
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UART4
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UART5
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_UARTIR
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_LPUART0
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_U7816
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_LPUART1
  *           @arg @ref FL_RCC_GROUP3_BUSCLK_I2C
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledGroup3BusClock(uint32_t Peripheral)
{
    return (uint32_t)(READ_BIT(RCC->PCLKCR3, ((Peripheral & 0xffffffff) << 0x0U)) == ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Get Group4 Periph Bus Clock Enable Status
  * @rmtoll   PCLKCR4        FL_RCC_IsEnabledGroup4BusClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP4_BUSCLK_BSTIM32
  *           @arg @ref FL_RCC_GROUP4_BUSCLK_GPTIM0
  *           @arg @ref FL_RCC_GROUP4_BUSCLK_GPTIM1
  *           @arg @ref FL_RCC_GROUP4_BUSCLK_ATIM
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledGroup4BusClock(uint32_t Peripheral)
{
    return (uint32_t)(READ_BIT(RCC->PCLKCR4, ((Peripheral & 0xffffffff) << 0x0U)) == ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Enable Group1 Periph Operation Clock
  * @rmtoll   OPCCR1        FL_RCC_EnableGroup1OperationClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP1_OPCLK_EXTI
  *           @arg @ref FL_RCC_GROUP1_OPCLK_LPUART1
  *           @arg @ref FL_RCC_GROUP1_OPCLK_LPUART0
  *           @arg @ref FL_RCC_GROUP1_OPCLK_I2C
  *           @arg @ref FL_RCC_GROUP1_OPCLK_ATIM
  *           @arg @ref FL_RCC_GROUP1_OPCLK_UART1
  *           @arg @ref FL_RCC_GROUP1_OPCLK_UART0
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableGroup1OperationClock(uint32_t Peripheral)
{
    SET_BIT(RCC->OPCCR1, ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Enable Group2 Periph Operation Clock
  * @rmtoll   OPCCR2        FL_RCC_EnableGroup2OperationClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP2_OPCLK_USB
  *           @arg @ref FL_RCC_GROUP2_OPCLK_FLASH
  *           @arg @ref FL_RCC_GROUP2_OPCLK_RNG
  *           @arg @ref FL_RCC_GROUP2_OPCLK_ADC
  *           @arg @ref FL_RCC_GROUP2_OPCLK_LPTIM32
  *           @arg @ref FL_RCC_GROUP2_OPCLK_BSTIM32
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableGroup2OperationClock(uint32_t Peripheral)
{
    SET_BIT(RCC->OPCCR2, ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable Group1 Periph Operation Clock
  * @rmtoll   OPCCR1        FL_RCC_DisableGroup1OperationClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP1_OPCLK_EXTI
  *           @arg @ref FL_RCC_GROUP1_OPCLK_LPUART1
  *           @arg @ref FL_RCC_GROUP1_OPCLK_LPUART0
  *           @arg @ref FL_RCC_GROUP1_OPCLK_I2C
  *           @arg @ref FL_RCC_GROUP1_OPCLK_ATIM
  *           @arg @ref FL_RCC_GROUP1_OPCLK_UART1
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableGroup1OperationClock(uint32_t Peripheral)
{
    CLEAR_BIT(RCC->OPCCR1, ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable Group2 Periph Operation Clock
  * @rmtoll   OPCCR2        FL_RCC_DisableGroup2OperationClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP2_OPCLK_USB
  *           @arg @ref FL_RCC_GROUP2_OPCLK_FLASH
  *           @arg @ref FL_RCC_GROUP2_OPCLK_RNG
  *           @arg @ref FL_RCC_GROUP2_OPCLK_ADC
  *           @arg @ref FL_RCC_GROUP2_OPCLK_LPTIM32
  *           @arg @ref FL_RCC_GROUP2_OPCLK_BSTIM32
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableGroup2OperationClock(uint32_t Peripheral)
{
    CLEAR_BIT(RCC->OPCCR2, ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Get Group1 Periph Operation Clock Enable Status
  * @rmtoll   OPCCR1        FL_RCC_IsEnabledGroup1OperationClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP1_OPCLK_EXTI
  *           @arg @ref FL_RCC_GROUP1_OPCLK_LPUART1
  *           @arg @ref FL_RCC_GROUP1_OPCLK_LPUART0
  *           @arg @ref FL_RCC_GROUP1_OPCLK_I2C
  *           @arg @ref FL_RCC_GROUP1_OPCLK_ATIM
  *           @arg @ref FL_RCC_GROUP1_OPCLK_UART1
  *           @arg @ref FL_RCC_GROUP1_OPCLK_UART0
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledGroup1OperationClock(uint32_t Peripheral)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR1, ((Peripheral & 0xffffffff) << 0x0U)) == ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Get Group2 Periph Operation Clock Enable Status
  * @rmtoll   OPCCR2        FL_RCC_IsEnabledGroup2OperationClock
  * @param    Peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_GROUP2_OPCLK_USB
  *           @arg @ref FL_RCC_GROUP2_OPCLK_FLASH
  *           @arg @ref FL_RCC_GROUP2_OPCLK_RNG
  *           @arg @ref FL_RCC_GROUP2_OPCLK_ADC
  *           @arg @ref FL_RCC_GROUP2_OPCLK_LPTIM32
  *           @arg @ref FL_RCC_GROUP2_OPCLK_BSTIM32
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledGroup2OperationClock(uint32_t Peripheral)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR2, ((Peripheral & 0xffffffff) << 0x0U)) == ((Peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Set EXTI Clock Source
  * @rmtoll   OPCCR1    EXTICKS    FL_RCC_SetEXTIClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_EXTI_CLK_SOURCE_LSCLK
  *           @arg @ref FL_RCC_EXTI_CLK_SOURCE_HCLK
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetEXTIClockSource(uint32_t clock)
{
    MODIFY_REG(RCC->OPCCR1, RCC_OPCCR1_EXTICKS_Msk, clock);
}

/**
  * @brief    Get EXTI Clock Source Setting
  * @rmtoll   OPCCR1    EXTICKS    FL_RCC_GetEXTIClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_EXTI_CLK_SOURCE_LSCLK
  *           @arg @ref FL_RCC_EXTI_CLK_SOURCE_HCLK
  */
__STATIC_INLINE uint32_t FL_RCC_GetEXTIClockSource(void)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR1, RCC_OPCCR1_EXTICKS_Msk));
}

/**
  * @brief    Set LPUART1 Clock Source
  * @rmtoll   OPCCR1    LPUART1CKS    FL_RCC_SetLPUART1ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_LPUART1_CLK_SOURCE_LSCLK
  *           @arg @ref FL_RCC_LPUART1_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_LPUART1_CLK_SOURCE_RCMF
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetLPUART1ClockSource(uint32_t clock)
{
    MODIFY_REG(RCC->OPCCR1, RCC_OPCCR1_LPUART1CKS_Msk, clock);
}

/**
  * @brief    Get LPUART1 Clock Source Setting
  * @rmtoll   OPCCR1    LPUART1CKS    FL_RCC_GetLPUART1ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_LPUART1_CLK_SOURCE_LSCLK
  *           @arg @ref FL_RCC_LPUART1_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_LPUART1_CLK_SOURCE_RCMF
  */
__STATIC_INLINE uint32_t FL_RCC_GetLPUART1ClockSource(void)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR1, RCC_OPCCR1_LPUART1CKS_Msk));
}

/**
  * @brief    Set LPUART0 Clock Source
  * @rmtoll   OPCCR1    LPUART0CKS    FL_RCC_SetLPUART0ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_LPUART0_CLK_SOURCE_LSCLK
  *           @arg @ref FL_RCC_LPUART0_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_LPUART0_CLK_SOURCE_RCMF
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetLPUART0ClockSource(uint32_t clock)
{
    MODIFY_REG(RCC->OPCCR1, RCC_OPCCR1_LPUART0CKS_Msk, clock);
}

/**
  * @brief    Get LPUART0 Clock Source Setting
  * @rmtoll   OPCCR1    LPUART0CKS    FL_RCC_GetLPUART0ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_LPUART0_CLK_SOURCE_LSCLK
  *           @arg @ref FL_RCC_LPUART0_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_LPUART0_CLK_SOURCE_RCMF
  */
__STATIC_INLINE uint32_t FL_RCC_GetLPUART0ClockSource(void)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR1, RCC_OPCCR1_LPUART0CKS_Msk));
}

/**
  * @brief    Set I2C Clock Source
  * @rmtoll   OPCCR1    I2CCKS    FL_RCC_SetI2CClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_I2C_CLK_SOURCE_APB1CLK
  *           @arg @ref FL_RCC_I2C_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_I2C_CLK_SOURCE_SYSCLK
  *           @arg @ref FL_RCC_I2C_CLK_SOURCE_RCMF_PSC
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetI2CClockSource(uint32_t clock)
{
    MODIFY_REG(RCC->OPCCR1, RCC_OPCCR1_I2CCKS_Msk, clock);
}

/**
  * @brief    Get I2C Clock Source Setting
  * @rmtoll   OPCCR1    I2CCKS    FL_RCC_GetI2CClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_I2C_CLK_SOURCE_APB1CLK
  *           @arg @ref FL_RCC_I2C_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_I2C_CLK_SOURCE_SYSCLK
  *           @arg @ref FL_RCC_I2C_CLK_SOURCE_RCMF_PSC
  */
__STATIC_INLINE uint32_t FL_RCC_GetI2CClockSource(void)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR1, RCC_OPCCR1_I2CCKS_Msk));
}

/**
  * @brief    Set ATIM Clock Source
  * @rmtoll   OPCCR1    ATCKS    FL_RCC_SetATIMClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_ATIM_CLK_SOURCE_APB2CLK
  *           @arg @ref FL_RCC_ATIM_CLK_SOURCE_USBPHYBCK120M
  *           @arg @ref FL_RCC_ATIM_CLK_SOURCE_PLLx2
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetATIMClockSource(uint32_t clock)
{
    MODIFY_REG(RCC->OPCCR1, RCC_OPCCR1_ATCKS_Msk, clock);
}

/**
  * @brief    Get ATIM Clock Source Setting
  * @rmtoll   OPCCR1    ATCKS    FL_RCC_GetATIMClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_ATIM_CLK_SOURCE_APB2CLK
  *           @arg @ref FL_RCC_ATIM_CLK_SOURCE_USBPHYBCK120M
  *           @arg @ref FL_RCC_ATIM_CLK_SOURCE_PLLx2
  */
__STATIC_INLINE uint32_t FL_RCC_GetATIMClockSource(void)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR1, RCC_OPCCR1_ATCKS_Msk));
}

/**
  * @brief    Set UART1 Clock Source
  * @rmtoll   OPCCR1    UART1CKS    FL_RCC_SetUART1ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_UART1_CLK_SOURCE_APB1CLK
  *           @arg @ref FL_RCC_UART1_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_UART1_CLK_SOURCE_SYSCLK
  *           @arg @ref FL_RCC_UART1_CLK_SOURCE_RCMF_PSC
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetUART1ClockSource(uint32_t clock)
{
    MODIFY_REG(RCC->OPCCR1, RCC_OPCCR1_UART1CKS_Msk, clock);
}

/**
  * @brief    Get UART1 Clock Source Setting
  * @rmtoll   OPCCR1    UART1CKS    FL_RCC_GetUART1ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_UART1_CLK_SOURCE_APB1CLK
  *           @arg @ref FL_RCC_UART1_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_UART1_CLK_SOURCE_SYSCLK
  *           @arg @ref FL_RCC_UART1_CLK_SOURCE_RCMF_PSC
  */
__STATIC_INLINE uint32_t FL_RCC_GetUART1ClockSource(void)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR1, RCC_OPCCR1_UART1CKS_Msk));
}

/**
  * @brief    Set UART0 Clock Source
  * @rmtoll   OPCCR1    UART0CKS    FL_RCC_SetUART0ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_UART0_CLK_SOURCE_APB1CLK
  *           @arg @ref FL_RCC_UART0_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_UART0_CLK_SOURCE_SYSCLK
  *           @arg @ref FL_RCC_UART0_CLK_SOURCE_RCMF_PSC
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetUART0ClockSource(uint32_t clock)
{
    MODIFY_REG(RCC->OPCCR1, RCC_OPCCR1_UART0CKS_Msk, clock);
}

/**
  * @brief    Get UART0 Clock Source Setting
  * @rmtoll   OPCCR1    UART0CKS    FL_RCC_GetUART0ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_UART0_CLK_SOURCE_APB1CLK
  *           @arg @ref FL_RCC_UART0_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_UART0_CLK_SOURCE_SYSCLK
  *           @arg @ref FL_RCC_UART0_CLK_SOURCE_RCMF_PSC
  */
__STATIC_INLINE uint32_t FL_RCC_GetUART0ClockSource(void)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR1, RCC_OPCCR1_UART0CKS_Msk));
}

/**
  * @brief    Set RNG Prescaler
  * @rmtoll   OPCCR2    RNGPRSC    FL_RCC_SetRNGPrescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_RCC_RNG_PSC_DIV1
  *           @arg @ref FL_RCC_RNG_PSC_DIV2
  *           @arg @ref FL_RCC_RNG_PSC_DIV4
  *           @arg @ref FL_RCC_RNG_PSC_DIV8
  *           @arg @ref FL_RCC_RNG_PSC_DIV16
  *           @arg @ref FL_RCC_RNG_PSC_DIV32
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetRNGPrescaler(uint32_t prescaler)
{
    MODIFY_REG(RCC->OPCCR2, RCC_OPCCR2_RNGPRSC_Msk, prescaler);
}

/**
  * @brief    Get RNG Prescaler Setting
  * @rmtoll   OPCCR2    RNGPRSC    FL_RCC_GetRNGPrescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_RNG_PSC_DIV1
  *           @arg @ref FL_RCC_RNG_PSC_DIV2
  *           @arg @ref FL_RCC_RNG_PSC_DIV4
  *           @arg @ref FL_RCC_RNG_PSC_DIV8
  *           @arg @ref FL_RCC_RNG_PSC_DIV16
  *           @arg @ref FL_RCC_RNG_PSC_DIV32
  */
__STATIC_INLINE uint32_t FL_RCC_GetRNGPrescaler(void)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR2, RCC_OPCCR2_RNGPRSC_Msk));
}

/**
  * @brief    Set ADC Prescaler
  * @rmtoll   OPCCR2    ADCPRSC    FL_RCC_SetADCPrescaler
  * @param    prescaler This parameter can be one of the following values:
  *           @arg @ref FL_RCC_ADC_PSC_DIV1
  *           @arg @ref FL_RCC_ADC_PSC_DIV2
  *           @arg @ref FL_RCC_ADC_PSC_DIV4
  *           @arg @ref FL_RCC_ADC_PSC_DIV8
  *           @arg @ref FL_RCC_ADC_PSC_DIV16
  *           @arg @ref FL_RCC_ADC_PSC_DIV32
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetADCPrescaler(uint32_t prescaler)
{
    MODIFY_REG(RCC->OPCCR2, RCC_OPCCR2_ADCPRSC_Msk, prescaler);
}

/**
  * @brief    Get ADC Prescaler Setting
  * @rmtoll   OPCCR2    ADCPRSC    FL_RCC_GetADCPrescaler
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_ADC_PSC_DIV1
  *           @arg @ref FL_RCC_ADC_PSC_DIV2
  *           @arg @ref FL_RCC_ADC_PSC_DIV4
  *           @arg @ref FL_RCC_ADC_PSC_DIV8
  *           @arg @ref FL_RCC_ADC_PSC_DIV16
  *           @arg @ref FL_RCC_ADC_PSC_DIV32
  */
__STATIC_INLINE uint32_t FL_RCC_GetADCPrescaler(void)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR2, RCC_OPCCR2_ADCPRSC_Msk));
}

/**
  * @brief    Set USB Reference Clock
  * @rmtoll   OPCCR2    USBCKS    FL_RCC_SetUSBClockReference
  * @param    ref This parameter can be one of the following values:
  *           @arg @ref FL_RCC_USB_CLK_REF_XTLF
  *           @arg @ref FL_RCC_USB_CLK_REF_XTHF
  *           @arg @ref FL_RCC_USB_CLK_REF_RCHF
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetUSBClockReference(uint32_t ref)
{
    MODIFY_REG(RCC->OPCCR2, RCC_OPCCR2_USBCKS_Msk, ref);
}

/**
  * @brief    Get USB Reference Clock Setting
  * @rmtoll   OPCCR2    USBCKS    FL_RCC_GetUSBClockReference
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_USB_CLK_REF_XTLF
  *           @arg @ref FL_RCC_USB_CLK_REF_XTHF
  *           @arg @ref FL_RCC_USB_CLK_REF_RCHF
  */
__STATIC_INLINE uint32_t FL_RCC_GetUSBClockReference(void)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR2, RCC_OPCCR2_USBCKS_Msk));
}

/**
  * @brief    Set ADC Clock Source
  * @rmtoll   OPCCR2    ADCCKS    FL_RCC_SetADCClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_ADC_CLK_SOURCE_RCMF_PSC
  *           @arg @ref FL_RCC_ADC_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_ADC_CLK_SOURCE_XTHF
  *           @arg @ref FL_RCC_ADC_CLK_SOURCE_PLL
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetADCClockSource(uint32_t clock)
{
    MODIFY_REG(RCC->OPCCR2, RCC_OPCCR2_ADCCKS_Msk, clock);
}

/**
  * @brief    Get ADC Clock Source Setting
  * @rmtoll   OPCCR2    ADCCKS    FL_RCC_GetADCClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_ADC_CLK_SOURCE_RCMF_PSC
  *           @arg @ref FL_RCC_ADC_CLK_SOURCE_RCHF
  *           @arg @ref FL_RCC_ADC_CLK_SOURCE_XTHF
  *           @arg @ref FL_RCC_ADC_CLK_SOURCE_PLL
  */
__STATIC_INLINE uint32_t FL_RCC_GetADCClockSource(void)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR2, RCC_OPCCR2_ADCCKS_Msk));
}

/**
  * @brief    Set LPTIM Clock Source
  * @rmtoll   OPCCR2    LPT32CKS    FL_RCC_SetLPTIM32ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_LPTIM32_CLK_SOURCE_APB1CLK
  *           @arg @ref FL_RCC_LPTIM32_CLK_SOURCE_LSCLK
  *           @arg @ref FL_RCC_LPTIM32_CLK_SOURCE_LPOSC
  *           @arg @ref FL_RCC_LPTIM32_CLK_SOURCE_RCMF_PSC
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetLPTIM32ClockSource(uint32_t clock)
{
    MODIFY_REG(RCC->OPCCR2, RCC_OPCCR2_LPT32CKS_Msk, clock);
}

/**
  * @brief    Get LPTIM Clock Source Setting
  * @rmtoll   OPCCR2    LPT32CKS    FL_RCC_GetLPTIM32ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_LPTIM32_CLK_SOURCE_APB1CLK
  *           @arg @ref FL_RCC_LPTIM32_CLK_SOURCE_LSCLK
  *           @arg @ref FL_RCC_LPTIM32_CLK_SOURCE_LPOSC
  *           @arg @ref FL_RCC_LPTIM32_CLK_SOURCE_RCMF_PSC
  */
__STATIC_INLINE uint32_t FL_RCC_GetLPTIM32ClockSource(void)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR2, RCC_OPCCR2_LPT32CKS_Msk));
}

/**
  * @brief    Set BSTIM Clock Source
  * @rmtoll   OPCCR2    BT32CKS    FL_RCC_SetBSTIM32ClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_BSTIM32_CLK_SOURCE_APB2CLK
  *           @arg @ref FL_RCC_BSTIM32_CLK_SOURCE_LSCLK
  *           @arg @ref FL_RCC_BSTIM32_CLK_SOURCE_LPOSC
  *           @arg @ref FL_RCC_BSTIM32_CLK_SOURCE_RCMF_PSC
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetBSTIM32ClockSource(uint32_t clock)
{
    MODIFY_REG(RCC->OPCCR2, RCC_OPCCR2_BT32CKS_Msk, clock);
}

/**
  * @brief    Get BSTIM Clock Source Setting
  * @rmtoll   OPCCR2    BT32CKS    FL_RCC_GetBSTIM32ClockSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_BSTIM32_CLK_SOURCE_APB2CLK
  *           @arg @ref FL_RCC_BSTIM32_CLK_SOURCE_LSCLK
  *           @arg @ref FL_RCC_BSTIM32_CLK_SOURCE_LPOSC
  *           @arg @ref FL_RCC_BSTIM32_CLK_SOURCE_RCMF_PSC
  */
__STATIC_INLINE uint32_t FL_RCC_GetBSTIM32ClockSource(void)
{
    return (uint32_t)(READ_BIT(RCC->OPCCR2, RCC_OPCCR2_BT32CKS_Msk));
}

/**
  * @brief    Set AHB Master Priority
  * @rmtoll   AHBMCR    MPRIL    FL_RCC_SetAHBMasterPriority
  * @param    priority This parameter can be one of the following values:
  *           @arg @ref FL_RCC_AHB_MASTER_PRIORITY_DMA_FIRST
  *           @arg @ref FL_RCC_AHB_MASTER_PRIORITY_CPU_FIRST
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetAHBMasterPriority(uint32_t priority)
{
    MODIFY_REG(RCC->AHBMCR, RCC_AHBMCR_MPRIL_Msk, priority);
}

/**
  * @brief    Get AHB Master Priority Setting
  * @rmtoll   AHBMCR    MPRIL    FL_RCC_GetAHBMasterPriority
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_AHB_MASTER_PRIORITY_DMA_FIRST
  *           @arg @ref FL_RCC_AHB_MASTER_PRIORITY_CPU_FIRST
  */
__STATIC_INLINE uint32_t FL_RCC_GetAHBMasterPriority(void)
{
    return (uint32_t)(READ_BIT(RCC->AHBMCR, RCC_AHBMCR_MPRIL_Msk));
}

/**
  * @brief    Set LSCLK Clock Source
  * @rmtoll   LSCLKSEL    SEL    FL_RCC_SetLSCLKClockSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_LSCLK_CLK_SOURCE_LPOSC
  *           @arg @ref FL_RCC_LSCLK_CLK_SOURCE_XTLF
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetLSCLKClockSource(uint32_t clock)
{
    MODIFY_REG(RCC->LSCLKSEL, RCC_LSCLKSEL_SEL_Msk, clock);
}

/**
  * @brief    Enable USB PHY Reset
  * @rmtoll   PHYCR    PHYRST    FL_RCC_EnableUSBPHYReset
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableUSBPHYReset(void)
{
    CLEAR_BIT(RCC->PHYCR, RCC_PHYCR_PHYRST_Msk);
}

/**
  * @brief    Get USB PHY Enable Status
  * @rmtoll   PHYCR    PHYRST    FL_RCC_IsEnabledUSBPHYReset
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledUSBPHYReset(void)
{
    return (uint32_t)!(READ_BIT(RCC->PHYCR, RCC_PHYCR_PHYRST_Msk) == RCC_PHYCR_PHYRST_Msk);
}

/**
  * @brief    Disable USB PHY Reset
  * @rmtoll   PHYCR    PHYRST    FL_RCC_DisableUSBPHYReset
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableUSBPHYReset(void)
{
    SET_BIT(RCC->PHYCR, RCC_PHYCR_PHYRST_Msk);
}

/**
  * @brief    Enable USB PHY Power Down
  * @rmtoll   PHYCR    PD    FL_RCC_EnableUSBPHYPowerDown
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableUSBPHYPowerDown(void)
{
    SET_BIT(RCC->PHYCR, RCC_PHYCR_PD_Msk);
}

/**
  * @brief    Get USB PHY Power Down Enable Status
  * @rmtoll   PHYCR    PD    FL_RCC_IsEnabledUSBPHYPowerDown
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledUSBPHYPowerDown(void)
{
    return (uint32_t)(READ_BIT(RCC->PHYCR, RCC_PHYCR_PD_Msk) == RCC_PHYCR_PD_Msk);
}

/**
  * @brief    Disable USB PHY Power Down
  * @rmtoll   PHYCR    PD    FL_RCC_DisableUSBPHYPowerDown
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableUSBPHYPowerDown(void)
{
    CLEAR_BIT(RCC->PHYCR, RCC_PHYCR_PD_Msk);
}

/**
  * @brief    Set USB PHY Power Ready Flag
  * @rmtoll   PHYCR    PLVREADY    FL_RCC_SetUSBPHYPowerReadyFlag
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetUSBPHYPowerReadyFlag(void)
{
    SET_BIT(RCC->PHYCR, RCC_PHYCR_PLVREADY_Msk);
}

/**
  * @brief    Reset USB PHY Power Ready Flag
  * @rmtoll   PHYCR    PLVREADY    FL_RCC_ResetUSBPHYPowerReadyFlag
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_ResetUSBPHYPowerReadyFlag(void)
{
    CLEAR_BIT(RCC->PHYCR, RCC_PHYCR_PLVREADY_Msk);
}

/**
  * @brief    Enable USB BCK
  * @rmtoll   PHYCR    BCKPD    FL_RCC_EnableUSBBCK
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableUSBBCK(void)
{
    CLEAR_BIT(RCC->PHYCR, RCC_PHYCR_BCKPD_Msk);
}

/**
  * @brief    Get USB BCK Enable Status
  * @rmtoll   PHYCR    BCKPD    FL_RCC_IsEnabledUSBBCK
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledUSBBCK(void)
{
    return (uint32_t)(READ_BIT(RCC->PHYCR, RCC_PHYCR_BCKPD_Msk) == RCC_PHYCR_BCKPD_Msk);
}

/**
  * @brief    Disable USB BCK
  * @rmtoll   PHYCR    BCKPD    FL_RCC_DisableUSBBCK
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableUSBBCK(void)
{
    SET_BIT(RCC->PHYCR, RCC_PHYCR_BCKPD_Msk);
}

/**
  * @brief    Enable USB BCK Reset
  * @rmtoll   PHYCR    BCKRST    FL_RCC_EnableUSBBCKReset
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableUSBBCKReset(void)
{
    CLEAR_BIT(RCC->PHYCR, RCC_PHYCR_BCKRST_Msk);
}

/**
  * @brief    Get USB BCK Reset Enable Status
  * @rmtoll   PHYCR    BCKRST    FL_RCC_IsEnabledUSBBCKReset
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledUSBBCKReset(void)
{
    return (uint32_t)!(READ_BIT(RCC->PHYCR, RCC_PHYCR_BCKRST_Msk) == RCC_PHYCR_BCKRST_Msk);
}

/**
  * @brief    Disable USB BCK Reset
  * @rmtoll   PHYCR    BCKRST    FL_RCC_DisableUSBBCKReset
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableUSBBCKReset(void)
{
    SET_BIT(RCC->PHYCR, RCC_PHYCR_BCKRST_Msk);
}

/**
  * @brief    Enable USB 48M Clock
  * @rmtoll   PHYBCKCR    CK48M_EN    FL_RCC_EnableUSB48MClock
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableUSB48MClock(void)
{
    SET_BIT(RCC->PHYBCKCR, RCC_PHYBCKCR_CK48M_EN_Msk);
}

/**
  * @brief    Get USB 48M Clock  Enable Status
  * @rmtoll   PHYBCKCR    CK48M_EN    FL_RCC_IsEnabledUSB48MClock
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledUSB48MClock(void)
{
    return (uint32_t)(READ_BIT(RCC->PHYBCKCR, RCC_PHYBCKCR_CK48M_EN_Msk) == RCC_PHYBCKCR_CK48M_EN_Msk);
}

/**
  * @brief    Disable USB 48M Clock
  * @rmtoll   PHYBCKCR    CK48M_EN    FL_RCC_DisableUSB48MClock
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableUSB48MClock(void)
{
    CLEAR_BIT(RCC->PHYBCKCR, RCC_PHYBCKCR_CK48M_EN_Msk);
}

/**
  * @brief    Get USB Clock Ready Flag
  * @rmtoll   PHYBCKCR    CLKRDY    FL_RCC_IsActiveFlag_USBClockReady
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsActiveFlag_USBClockReady(void)
{
    return (uint32_t)(READ_BIT(RCC->PHYBCKCR, RCC_PHYBCKCR_CLKRDY_Msk) == RCC_PHYBCKCR_CLKRDY_Msk);
}

/**
  * @brief    Set USB Reference Clock Source
  * @rmtoll   PHYBCKCR    OUTCLKSEL    FL_RCC_SetUSBClockReferenceSource
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_RCC_USB_CLK_REF_SOURCE_SOF
  *           @arg @ref FL_RCC_USB_CLK_REF_SOURCE_CORECLKIN
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetUSBClockReferenceSource(uint32_t clock)
{
    MODIFY_REG(RCC->PHYBCKCR, RCC_PHYBCKCR_OUTCLKSEL_Msk, clock);
}

/**
  * @brief    Get USB Reference Clock Source
  * @rmtoll   PHYBCKCR    OUTCLKSEL    FL_RCC_GetUSBClockReferenceSource
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RCC_USB_CLK_REF_SOURCE_SOF
  *           @arg @ref FL_RCC_USB_CLK_REF_SOURCE_CORECLKIN
  */
__STATIC_INLINE uint32_t FL_RCC_GetUSBClockReferenceSource(void)
{
    return (uint32_t)(READ_BIT(RCC->PHYBCKCR, RCC_PHYBCKCR_OUTCLKSEL_Msk));
}

/**
  * @brief    Get LockUp Reset Enable Status
  * @rmtoll   LKPCR    RST_EN    FL_RCC_IsEnabledLockUpReset
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsEnabledLockUpReset(void)
{
    return (uint32_t)(READ_BIT(RCC->LKPCR, RCC_LKPCR_RST_EN_Msk) == RCC_LKPCR_RST_EN_Msk);
}

/**
  * @brief    Disable LockUp Reset
  * @rmtoll   LKPCR    RST_EN    FL_RCC_DisableLockUpReset
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableLockUpReset(void)
{
    CLEAR_BIT(RCC->LKPCR, RCC_LKPCR_RST_EN_Msk);
}

/**
  * @brief    Enable LockUp Reset
  * @rmtoll   LKPCR    RST_EN    FL_RCC_EnableLockUpReset
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableLockUpReset(void)
{
    SET_BIT(RCC->LKPCR, RCC_LKPCR_RST_EN_Msk);
}

/**
  * @brief    SoftReset Chip
  * @rmtoll   SOFTRST        FL_RCC_SetSoftReset
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_SetSoftReset(void)
{
    WRITE_REG(RCC->SOFTRST, FL_RCC_SOFTWARE_RESET_KEY);
}

/**
  * @brief    Get MDFN Reset Flag
  * @rmtoll   RSTFR    MDFN_FLAG    FL_RCC_IsActiveFlag_MDF
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsActiveFlag_MDF(void)
{
    return (uint32_t)(READ_BIT(RCC->RSTFR, RCC_RSTFR_MDFN_FLAG_Msk) == (RCC_RSTFR_MDFN_FLAG_Msk));
}

/**
  * @brief    Clear MDFN Reset Flag
  * @rmtoll   RSTFR    MDFN_FLAG    FL_RCC_ClearFlag_MDF
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_ClearFlag_MDF(void)
{
    WRITE_REG(RCC->RSTFR, RCC_RSTFR_MDFN_FLAG_Msk);
}

/**
  * @brief    Get NRST Reset Flag
  * @rmtoll   RSTFR    NRSTN_FLAG    FL_RCC_IsActiveFlag_NRSTN
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsActiveFlag_NRSTN(void)
{
    return (uint32_t)(READ_BIT(RCC->RSTFR, RCC_RSTFR_NRSTN_FLAG_Msk) == (RCC_RSTFR_NRSTN_FLAG_Msk));
}

/**
  * @brief    Clear NRST Reset Flag
  * @rmtoll   RSTFR    NRSTN_FLAG    FL_RCC_ClearFlag_NRSTN
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_ClearFlag_NRSTN(void)
{
    WRITE_REG(RCC->RSTFR, RCC_RSTFR_NRSTN_FLAG_Msk);
}

/**
  * @brief    Get TESTN Reset Flag
  * @rmtoll   RSTFR    TESTN_FLAG    FL_RCC_IsActiveFlag_TESTN
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsActiveFlag_TESTN(void)
{
    return (uint32_t)(READ_BIT(RCC->RSTFR, RCC_RSTFR_TESTN_FLAG_Msk) == (RCC_RSTFR_TESTN_FLAG_Msk));
}

/**
  * @brief    Clear TESTN Reset Flag
  * @rmtoll   RSTFR    TESTN_FLAG    FL_RCC_ClearFlag_TESTN
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_ClearFlag_TESTN(void)
{
    WRITE_REG(RCC->RSTFR, RCC_RSTFR_TESTN_FLAG_Msk);
}

/**
  * @brief    Get Power Up Reset Flag
  * @rmtoll   RSTFR    PORN_FLAG    FL_RCC_IsActiveFlag_PORN
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsActiveFlag_PORN(void)
{
    return (uint32_t)(READ_BIT(RCC->RSTFR, RCC_RSTFR_PORN_FLAG_Msk) == (RCC_RSTFR_PORN_FLAG_Msk));
}

/**
  * @brief    Clear Power Up Reset Flag
  * @rmtoll   RSTFR    PORN_FLAG    FL_RCC_ClearFlag_PORN
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_ClearFlag_PORN(void)
{
    WRITE_REG(RCC->RSTFR, RCC_RSTFR_PORN_FLAG_Msk);
}

/**
  * @brief    Get Power Down Reset Flag
  * @rmtoll   RSTFR    PDRN_FLAG    FL_RCC_IsActiveFlag_PDRN
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsActiveFlag_PDRN(void)
{
    return (uint32_t)(READ_BIT(RCC->RSTFR, RCC_RSTFR_PDRN_FLAG_Msk) == (RCC_RSTFR_PDRN_FLAG_Msk));
}

/**
  * @brief    Clear Power Down Reset Flag
  * @rmtoll   RSTFR    PDRN_FLAG    FL_RCC_ClearFlag_PDRN
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_ClearFlag_PDRN(void)
{
    WRITE_REG(RCC->RSTFR, RCC_RSTFR_PDRN_FLAG_Msk);
}

/**
  * @brief    Get Software Reset Flag
  * @rmtoll   RSTFR    SOFTN_FLAG    FL_RCC_IsActiveFlag_SOFTN
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsActiveFlag_SOFTN(void)
{
    return (uint32_t)(READ_BIT(RCC->RSTFR, RCC_RSTFR_SOFTN_FLAG_Msk) == (RCC_RSTFR_SOFTN_FLAG_Msk));
}

/**
  * @brief    Clear Software Reset Flag
  * @rmtoll   RSTFR    SOFTN_FLAG    FL_RCC_ClearFlag_SOFTN
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_ClearFlag_SOFTN(void)
{
    WRITE_REG(RCC->RSTFR, RCC_RSTFR_SOFTN_FLAG_Msk);
}

/**
  * @brief    Get IWDT Reset Flag
  * @rmtoll   RSTFR    IWDTN_FLAG    FL_RCC_IsActiveFlag_IWDTN
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsActiveFlag_IWDTN(void)
{
    return (uint32_t)(READ_BIT(RCC->RSTFR, RCC_RSTFR_IWDTN_FLAG_Msk) == (RCC_RSTFR_IWDTN_FLAG_Msk));
}

/**
  * @brief    Clear IWDT Reset Flag
  * @rmtoll   RSTFR    IWDTN_FLAG    FL_RCC_ClearFlag_IWDTN
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_ClearFlag_IWDTN(void)
{
    WRITE_REG(RCC->RSTFR, RCC_RSTFR_IWDTN_FLAG_Msk);
}

/**
  * @brief    Get WWDT Reset Flag
  * @rmtoll   RSTFR    WWDTN_FLAG    FL_RCC_IsActiveFlag_WWDTN
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsActiveFlag_WWDTN(void)
{
    return (uint32_t)(READ_BIT(RCC->RSTFR, RCC_RSTFR_WWDTN_FLAG_Msk) == (RCC_RSTFR_WWDTN_FLAG_Msk));
}

/**
  * @brief    Clear WWDT Reset Flag
  * @rmtoll   RSTFR    WWDTN_FLAG    FL_RCC_ClearFlag_WWDTN
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_ClearFlag_WWDTN(void)
{
    WRITE_REG(RCC->RSTFR, RCC_RSTFR_WWDTN_FLAG_Msk);
}

/**
  * @brief    Get LockUp Reset Flag
  * @rmtoll   RSTFR    LKUPN_FLAG    FL_RCC_IsActiveFlag_LKUPN
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsActiveFlag_LKUPN(void)
{
    return (uint32_t)(READ_BIT(RCC->RSTFR, RCC_RSTFR_LKUPN_FLAG_Msk) == (RCC_RSTFR_LKUPN_FLAG_Msk));
}

/**
  * @brief    Clear LockUp Reset Flag
  * @rmtoll   RSTFR    LKUPN_FLAG    FL_RCC_ClearFlag_LKUPN
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_ClearFlag_LKUPN(void)
{
    WRITE_REG(RCC->RSTFR, RCC_RSTFR_LKUPN_FLAG_Msk);
}

/**
  * @brief    Get NVIC Reset Flag
  * @rmtoll   RSTFR    NVICN_FLAG    FL_RCC_IsActiveFlag_NVICN
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RCC_IsActiveFlag_NVICN(void)
{
    return (uint32_t)(READ_BIT(RCC->RSTFR, RCC_RSTFR_NVICN_FLAG_Msk) == (RCC_RSTFR_NVICN_FLAG_Msk));
}

/**
  * @brief    Clear NVIC Reset Flag
  * @rmtoll   RSTFR    NVICN_FLAG    FL_RCC_ClearFlag_NVICN
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_ClearFlag_NVICN(void)
{
    WRITE_REG(RCC->RSTFR, RCC_RSTFR_NVICN_FLAG_Msk);
}

/**
  * @brief    Disable Peripheral Reset
  * @rmtoll   PRSTEN        FL_RCC_DisablePeripheralReset
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisablePeripheralReset(void)
{
    WRITE_REG(RCC->PRSTEN, (~FL_RCC_PERIPHERAL_RESET_KEY));
}

/**
  * @brief    Enable Peripheral Reset
  * @rmtoll   PRSTEN        FL_RCC_EnablePeripheralReset
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnablePeripheralReset(void)
{
    WRITE_REG(RCC->PRSTEN, FL_RCC_PERIPHERAL_RESET_KEY);
}

/**
  * @brief    Enable AHB Peripheral Reset
  * @rmtoll   AHBRSTCR        FL_RCC_EnableResetAHBPeripheral
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_RSTAHB_DMA
  *           @arg @ref FL_RCC_RSTAHB_USB
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableResetAHBPeripheral(uint32_t peripheral)
{
    SET_BIT(RCC->AHBRSTCR, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Enable APB1 Peripheral Reset
  * @rmtoll   APBRSTCR1        FL_RCC_EnableResetAPB1Peripheral
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_RSTAPB_UART5
  *           @arg @ref FL_RCC_RSTAPB_UART4
  *           @arg @ref FL_RCC_RSTAPB_GPTIM1
  *           @arg @ref FL_RCC_RSTAPB_GPTIM0
  *           @arg @ref FL_RCC_RSTAPB_LCD
  *           @arg @ref FL_RCC_RSTAPB_U7816
  *           @arg @ref FL_RCC_RSTAPB_SPI2
  *           @arg @ref FL_RCC_RSTAPB_LPUART0
  *           @arg @ref FL_RCC_RSTAPB_I2C
  *           @arg @ref FL_RCC_RSTAPB_LPTIM32
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableResetAPB1Peripheral(uint32_t peripheral)
{
    SET_BIT(RCC->APBRSTCR1, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Enable APB2 Peripheral Reset
  * @rmtoll   APBRSTCR2        FL_RCC_EnableResetAPB2Peripheral
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_RSTAPB_ATIM
  *           @arg @ref FL_RCC_RSTAPB_BSTIM32
  *           @arg @ref FL_RCC_RSTAPB_ADCCR
  *           @arg @ref FL_RCC_RSTAPB_ADC
  *           @arg @ref FL_RCC_RSTAPB_OPA
  *           @arg @ref FL_RCC_RSTAPB_DIVAS
  *           @arg @ref FL_RCC_RSTAPB_AES
  *           @arg @ref FL_RCC_RSTAPB_CRC
  *           @arg @ref FL_RCC_RSTAPB_RNG
  *           @arg @ref FL_RCC_RSTAPB_UART1
  *           @arg @ref FL_RCC_RSTAPB_UART0
  *           @arg @ref FL_RCC_RSTAPB_SPI1
  *           @arg @ref FL_RCC_RSTAPB_UCIR
  *           @arg @ref FL_RCC_RSTAPB_LPUART1
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_EnableResetAPB2Peripheral(uint32_t peripheral)
{
    SET_BIT(RCC->APBRSTCR2, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable AHB Peripheral Reset
  * @rmtoll   AHBRSTCR        FL_RCC_DisableResetAHBPeripheral
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_RSTAHB_DMA
  *           @arg @ref FL_RCC_RSTAHB_USB
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableResetAHBPeripheral(uint32_t peripheral)
{
    CLEAR_BIT(RCC->AHBRSTCR, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable APB1 Peripheral Reset
  * @rmtoll   APBRSTCR1        FL_RCC_DisableResetAPB1Peripheral
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_RSTAPB_UART5
  *           @arg @ref FL_RCC_RSTAPB_UART4
  *           @arg @ref FL_RCC_RSTAPB_GPTIM1
  *           @arg @ref FL_RCC_RSTAPB_GPTIM0
  *           @arg @ref FL_RCC_RSTAPB_LCD
  *           @arg @ref FL_RCC_RSTAPB_U7816
  *           @arg @ref FL_RCC_RSTAPB_SPI2
  *           @arg @ref FL_RCC_RSTAPB_LPUART0
  *           @arg @ref FL_RCC_RSTAPB_I2C
  *           @arg @ref FL_RCC_RSTAPB_LPTIM32
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableResetAPB1Peripheral(uint32_t peripheral)
{
    CLEAR_BIT(RCC->APBRSTCR1, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable APB2 Peripheral Reset
  * @rmtoll   APBRSTCR2        FL_RCC_DisableResetAPB2Peripheral
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RCC_RSTAPB_ATIM
  *           @arg @ref FL_RCC_RSTAPB_BSTIM32
  *           @arg @ref FL_RCC_RSTAPB_ADCCR
  *           @arg @ref FL_RCC_RSTAPB_ADC
  *           @arg @ref FL_RCC_RSTAPB_OPA
  *           @arg @ref FL_RCC_RSTAPB_DIVAS
  *           @arg @ref FL_RCC_RSTAPB_AES
  *           @arg @ref FL_RCC_RSTAPB_CRC
  *           @arg @ref FL_RCC_RSTAPB_RNG
  *           @arg @ref FL_RCC_RSTAPB_UART1
  *           @arg @ref FL_RCC_RSTAPB_UART0
  *           @arg @ref FL_RCC_RSTAPB_SPI1
  *           @arg @ref FL_RCC_RSTAPB_UCIR
  *           @arg @ref FL_RCC_RSTAPB_LPUART1
  * @retval   None
  */
__STATIC_INLINE void FL_RCC_DisableResetAPB2Peripheral(uint32_t peripheral)
{
    CLEAR_BIT(RCC->APBRSTCR2, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @}
  */

/** @defgroup RCC_FL_EF_Init Initialization and de-initialization functions
  * @{
  */

/**
  * @}
  */


/** @defgroup RCC_FL_EF_Operation Opeartion functions
  * @{
  */

uint32_t FL_RCC_GetSystemClockFreq(void);
uint32_t FL_RCC_GetAHBClockFreq(void);
uint32_t FL_RCC_GetAPB1ClockFreq(void);
uint32_t FL_RCC_GetAPB2ClockFreq(void);

uint32_t FL_RCC_GetRCMFClockFreq(void);
uint32_t FL_RCC_GetRCHFClockFreq(void);
uint32_t FL_RCC_GetPLLClockFreq(void);

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

#endif /* __FM33LC0XX_FL_RCC_H*/

/*************************Py_Code_Generator Version: 0.1-0.14-0.2 @ 2021-07-08*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
