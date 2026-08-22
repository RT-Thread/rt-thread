/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_can.h
  * @author  FMSH Application Team
  * @brief   Head file of CAN FL Module
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
#ifndef __FM33LG0XX_FL_CAN_H
#define __FM33LG0XX_FL_CAN_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup CAN CAN
  * @brief CAN FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup CAN_FL_ES_INIT CAN Exported Init structures
  * @{
  */

/**
  * @brief FL CAN Init Sturcture definition
  */
typedef struct
{
    /*工作模式*/
    uint8_t mode;
    /*同步段长度*/
    uint8_t SJW;
    /*时间段1*/
    uint8_t TS1;
    /*时间段2*/
    uint8_t TS2;
    /*波特率预分频*/
    uint8_t BRP;
    /*时钟源选择*/
    uint8_t clockSource;

} FL_CAN_InitTypeDef;

/**
  * @brief  CAN filter init structure definition
  */
typedef struct
{

    /*滤波器SRR位*/
    uint32_t filterIdSRR;
    /*滤波器IDE位*/
    uint32_t filterIdIDE;
    /*滤波器RTR位*/
    uint32_t filterIdRTR;
    /*滤波器使能*/
    uint32_t  filterEn;
    /*滤波器标准ID*/
    uint32_t filterIdStandard;
    /*滤波器扩展ID*/
    uint32_t filterIdExtend;
    /*滤波器ID高11位掩码*/
    uint32_t filterMaskIdHigh;
    /*滤波器SRR位掩码*/
    uint32_t filterMaskIdSRR;
    /*滤波器IDE位掩码*/
    uint32_t filterMaskIdIDE;
    /*滤波器ID低18位掩码*/
    uint32_t filterMaskIdLow;
    /*滤波器RTR位掩码*/
    uint32_t filterMaskIdRTR;

} FL_CAN_FilterInitTypeDef;


/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup CAN_FL_Exported_Constants CAN Exported Constants
  * @{
  */

#define    CAN_CR_CEN_Pos                                         (1U)
#define    CAN_CR_CEN_Msk                                         (0x1U << CAN_CR_CEN_Pos)
#define    CAN_CR_CEN                                             CAN_CR_CEN_Msk

#define    CAN_CR_SRST_Pos                                        (0U)
#define    CAN_CR_SRST_Msk                                        (0x1U << CAN_CR_SRST_Pos)
#define    CAN_CR_SRST                                            CAN_CR_SRST_Msk

#define    CAN_MSR_LPBACK_Pos                                     (1U)
#define    CAN_MSR_LPBACK_Msk                                     (0x1U << CAN_MSR_LPBACK_Pos)
#define    CAN_MSR_LPBACK                                         CAN_MSR_LPBACK_Msk

#define    CAN_BRPR_BRP_Pos                                       (0U)
#define    CAN_BRPR_BRP_Msk                                       (0xffU << CAN_BRPR_BRP_Pos)
#define    CAN_BRPR_BRP                                           CAN_BRPR_BRP_Msk

#define    CAN_BTR_SJW_Pos                                        (7U)
#define    CAN_BTR_SJW_Msk                                        (0x3U << CAN_BTR_SJW_Pos)
#define    CAN_BTR_SJW                                            CAN_BTR_SJW_Msk

#define    CAN_BTR_TS2_Pos                                        (4U)
#define    CAN_BTR_TS2_Msk                                        (0x7U << CAN_BTR_TS2_Pos)
#define    CAN_BTR_TS2                                            CAN_BTR_TS2_Msk

#define    CAN_BTR_TS1_Pos                                        (0U)
#define    CAN_BTR_TS1_Msk                                        (0xfU << CAN_BTR_TS1_Pos)
#define    CAN_BTR_TS1                                            CAN_BTR_TS1_Msk

#define    CAN_ECR_REC_Pos                                        (8U)
#define    CAN_ECR_REC_Msk                                        (0xffU << CAN_ECR_REC_Pos)
#define    CAN_ECR_REC                                            CAN_ECR_REC_Msk

#define    CAN_ECR_TEC_Pos                                        (0U)
#define    CAN_ECR_TEC_Msk                                        (0xffU << CAN_ECR_TEC_Pos)
#define    CAN_ECR_TEC                                            CAN_ECR_TEC_Msk

#define    CAN_ESR_ACKER_Pos                                      (4U)
#define    CAN_ESR_ACKER_Msk                                      (0x1U << CAN_ESR_ACKER_Pos)
#define    CAN_ESR_ACKER                                          CAN_ESR_ACKER_Msk

#define    CAN_ESR_BERR_Pos                                       (3U)
#define    CAN_ESR_BERR_Msk                                       (0x1U << CAN_ESR_BERR_Pos)
#define    CAN_ESR_BERR                                           CAN_ESR_BERR_Msk

#define    CAN_ESR_STER_Pos                                       (2U)
#define    CAN_ESR_STER_Msk                                       (0x1U << CAN_ESR_STER_Pos)
#define    CAN_ESR_STER                                           CAN_ESR_STER_Msk

#define    CAN_ESR_FMER_Pos                                       (1U)
#define    CAN_ESR_FMER_Msk                                       (0x1U << CAN_ESR_FMER_Pos)
#define    CAN_ESR_FMER                                           CAN_ESR_FMER_Msk

#define    CAN_ESR_CRCER_Pos                                      (0U)
#define    CAN_ESR_CRCER_Msk                                      (0x1U << CAN_ESR_CRCER_Pos)
#define    CAN_ESR_CRCER                                          CAN_ESR_CRCER_Msk

#define    CAN_SR_ACFBSY_Pos                                      (11U)
#define    CAN_SR_ACFBSY_Msk                                      (0x1U << CAN_SR_ACFBSY_Pos)
#define    CAN_SR_ACFBSY                                          CAN_SR_ACFBSY_Msk

#define    CAN_SR_TXFLL_Pos                                       (10U)
#define    CAN_SR_TXFLL_Msk                                       (0x1U << CAN_SR_TXFLL_Pos)
#define    CAN_SR_TXFLL                                           CAN_SR_TXFLL_Msk

#define    CAN_SR_TXBFLL_Pos                                      (9U)
#define    CAN_SR_TXBFLL_Msk                                      (0x1U << CAN_SR_TXBFLL_Pos)
#define    CAN_SR_TXBFLL                                          CAN_SR_TXBFLL_Msk

#define    CAN_SR_ESTAT_Pos                                       (7U)
#define    CAN_SR_ESTAT_Msk                                       (0x3U << CAN_SR_ESTAT_Pos)
#define    CAN_SR_ESTAT                                           CAN_SR_ESTAT_Msk

#define    CAN_SR_ERRWRN_Pos                                      (6U)
#define    CAN_SR_ERRWRN_Msk                                      (0x1U << CAN_SR_ERRWRN_Pos)
#define    CAN_SR_ERRWRN                                          CAN_SR_ERRWRN_Msk

#define    CAN_SR_BBSY_Pos                                        (5U)
#define    CAN_SR_BBSY_Msk                                        (0x1U << CAN_SR_BBSY_Pos)
#define    CAN_SR_BBSY                                            CAN_SR_BBSY_Msk

#define    CAN_SR_BIDLE_Pos                                       (4U)
#define    CAN_SR_BIDLE_Msk                                       (0x1U << CAN_SR_BIDLE_Pos)
#define    CAN_SR_BIDLE                                           CAN_SR_BIDLE_Msk

#define    CAN_SR_NORMAL_Pos                                      (3U)
#define    CAN_SR_NORMAL_Msk                                      (0x1U << CAN_SR_NORMAL_Pos)
#define    CAN_SR_NORMAL                                          CAN_SR_NORMAL_Msk

#define    CAN_SR_LBACK_Pos                                       (1U)
#define    CAN_SR_LBACK_Msk                                       (0x1U << CAN_SR_LBACK_Pos)
#define    CAN_SR_LBACK                                           CAN_SR_LBACK_Msk

#define    CAN_SR_CONFIG_Pos                                      (0U)
#define    CAN_SR_CONFIG_Msk                                      (0x1U << CAN_SR_CONFIG_Pos)
#define    CAN_SR_CONFIG                                          CAN_SR_CONFIG_Msk

#define    CAN_ISR_BSOFF_Pos                                      (9U)
#define    CAN_ISR_BSOFF_Msk                                      (0x1U << CAN_ISR_BSOFF_Pos)
#define    CAN_ISR_BSOFF                                          CAN_ISR_BSOFF_Msk

#define    CAN_ISR_ERROR_Pos                                      (8U)
#define    CAN_ISR_ERROR_Msk                                      (0x1U << CAN_ISR_ERROR_Pos)
#define    CAN_ISR_ERROR                                          CAN_ISR_ERROR_Msk

#define    CAN_ISR_RXNEMP_Pos                                     (7U)
#define    CAN_ISR_RXNEMP_Msk                                     (0x1U << CAN_ISR_RXNEMP_Pos)
#define    CAN_ISR_RXNEMP                                         CAN_ISR_RXNEMP_Msk

#define    CAN_ISR_RXOFLW_Pos                                     (6U)
#define    CAN_ISR_RXOFLW_Msk                                     (0x1U << CAN_ISR_RXOFLW_Pos)
#define    CAN_ISR_RXOFLW                                         CAN_ISR_RXOFLW_Msk

#define    CAN_ISR_RXUFLW_Pos                                     (5U)
#define    CAN_ISR_RXUFLW_Msk                                     (0x1U << CAN_ISR_RXUFLW_Pos)
#define    CAN_ISR_RXUFLW                                         CAN_ISR_RXUFLW_Msk

#define    CAN_ISR_RXOK_Pos                                       (4U)
#define    CAN_ISR_RXOK_Msk                                       (0x1U << CAN_ISR_RXOK_Pos)
#define    CAN_ISR_RXOK                                           CAN_ISR_RXOK_Msk

#define    CAN_ISR_TXBFLL_Pos                                     (3U)
#define    CAN_ISR_TXBFLL_Msk                                     (0x1U << CAN_ISR_TXBFLL_Pos)
#define    CAN_ISR_TXBFLL                                         CAN_ISR_TXBFLL_Msk

#define    CAN_ISR_TXFLL_Pos                                      (2U)
#define    CAN_ISR_TXFLL_Msk                                      (0x1U << CAN_ISR_TXFLL_Pos)
#define    CAN_ISR_TXFLL                                          CAN_ISR_TXFLL_Msk

#define    CAN_ISR_TXOK_Pos                                       (1U)
#define    CAN_ISR_TXOK_Msk                                       (0x1U << CAN_ISR_TXOK_Pos)
#define    CAN_ISR_TXOK                                           CAN_ISR_TXOK_Msk

#define    CAN_ISR_ARBLST_Pos                                     (0U)
#define    CAN_ISR_ARBLST_Msk                                     (0x1U << CAN_ISR_ARBLST_Pos)
#define    CAN_ISR_ARBLST                                         CAN_ISR_ARBLST_Msk

#define    CAN_IER_BSOFFIE_Pos                                    (9U)
#define    CAN_IER_BSOFFIE_Msk                                    (0x1U << CAN_IER_BSOFFIE_Pos)
#define    CAN_IER_BSOFFIE                                        CAN_IER_BSOFFIE_Msk

#define    CAN_IER_ERRORIE_Pos                                    (8U)
#define    CAN_IER_ERRORIE_Msk                                    (0x1U << CAN_IER_ERRORIE_Pos)
#define    CAN_IER_ERRORIE                                        CAN_IER_ERRORIE_Msk

#define    CAN_IER_RXNEMPIE_Pos                                   (7U)
#define    CAN_IER_RXNEMPIE_Msk                                   (0x1U << CAN_IER_RXNEMPIE_Pos)
#define    CAN_IER_RXNEMPIE                                       CAN_IER_RXNEMPIE_Msk

#define    CAN_IER_RXOFLWIE_Pos                                   (6U)
#define    CAN_IER_RXOFLWIE_Msk                                   (0x1U << CAN_IER_RXOFLWIE_Pos)
#define    CAN_IER_RXOFLWIE                                       CAN_IER_RXOFLWIE_Msk

#define    CAN_IER_RXUFLWIE_Pos                                   (5U)
#define    CAN_IER_RXUFLWIE_Msk                                   (0x1U << CAN_IER_RXUFLWIE_Pos)
#define    CAN_IER_RXUFLWIE                                       CAN_IER_RXUFLWIE_Msk

#define    CAN_IER_RXOKIE_Pos                                     (4U)
#define    CAN_IER_RXOKIE_Msk                                     (0x1U << CAN_IER_RXOKIE_Pos)
#define    CAN_IER_RXOKIE                                         CAN_IER_RXOKIE_Msk

#define    CAN_IER_TXBFLLIE_Pos                                   (3U)
#define    CAN_IER_TXBFLLIE_Msk                                   (0x1U << CAN_IER_TXBFLLIE_Pos)
#define    CAN_IER_TXBFLLIE                                       CAN_IER_TXBFLLIE_Msk

#define    CAN_IER_TXFLLIE_Pos                                    (2U)
#define    CAN_IER_TXFLLIE_Msk                                    (0x1U << CAN_IER_TXFLLIE_Pos)
#define    CAN_IER_TXFLLIE                                        CAN_IER_TXFLLIE_Msk

#define    CAN_IER_TXOKIE_Pos                                     (1U)
#define    CAN_IER_TXOKIE_Msk                                     (0x1U << CAN_IER_TXOKIE_Pos)
#define    CAN_IER_TXOKIE                                         CAN_IER_TXOKIE_Msk

#define    CAN_IER_ARBLSTIE_Pos                                   (0U)
#define    CAN_IER_ARBLSTIE_Msk                                   (0x1U << CAN_IER_ARBLSTIE_Pos)
#define    CAN_IER_ARBLSTIE                                       CAN_IER_ARBLSTIE_Msk

#define    CAN_ICR_CBSOFF_Pos                                     (9U)
#define    CAN_ICR_CBSOFF_Msk                                     (0x1U << CAN_ICR_CBSOFF_Pos)
#define    CAN_ICR_CBSOFF                                         CAN_ICR_CBSOFF_Msk

#define    CAN_ICR_CERROR_Pos                                     (8U)
#define    CAN_ICR_CERROR_Msk                                     (0x1U << CAN_ICR_CERROR_Pos)
#define    CAN_ICR_CERROR                                         CAN_ICR_CERROR_Msk

#define    CAN_ICR_CRXNEMP_Pos                                    (7U)
#define    CAN_ICR_CRXNEMP_Msk                                    (0x1U << CAN_ICR_CRXNEMP_Pos)
#define    CAN_ICR_CRXNEMP                                        CAN_ICR_CRXNEMP_Msk

#define    CAN_ICR_CRXOFLW_Pos                                    (6U)
#define    CAN_ICR_CRXOFLW_Msk                                    (0x1U << CAN_ICR_CRXOFLW_Pos)
#define    CAN_ICR_CRXOFLW                                        CAN_ICR_CRXOFLW_Msk

#define    CAN_ICR_CRXUFLW_Pos                                    (5U)
#define    CAN_ICR_CRXUFLW_Msk                                    (0x1U << CAN_ICR_CRXUFLW_Pos)
#define    CAN_ICR_CRXUFLW                                        CAN_ICR_CRXUFLW_Msk

#define    CAN_ICR_CRXOK_Pos                                      (4U)
#define    CAN_ICR_CRXOK_Msk                                      (0x1U << CAN_ICR_CRXOK_Pos)
#define    CAN_ICR_CRXOK                                          CAN_ICR_CRXOK_Msk

#define    CAN_ICR_CTXBFLL_Pos                                    (3U)
#define    CAN_ICR_CTXBFLL_Msk                                    (0x1U << CAN_ICR_CTXBFLL_Pos)
#define    CAN_ICR_CTXBFLL                                        CAN_ICR_CTXBFLL_Msk

#define    CAN_ICR_CTXFLL_Pos                                     (2U)
#define    CAN_ICR_CTXFLL_Msk                                     (0x1U << CAN_ICR_CTXFLL_Pos)
#define    CAN_ICR_CTXFLL                                         CAN_ICR_CTXFLL_Msk

#define    CAN_ICR_CTXOK_Pos                                      (1U)
#define    CAN_ICR_CTXOK_Msk                                      (0x1U << CAN_ICR_CTXOK_Pos)
#define    CAN_ICR_CTXOK                                          CAN_ICR_CTXOK_Msk

#define    CAN_ICR_CARBLST_Pos                                    (0U)
#define    CAN_ICR_CARBLST_Msk                                    (0x1U << CAN_ICR_CARBLST_Pos)
#define    CAN_ICR_CARBLST                                        CAN_ICR_CARBLST_Msk

#define    CAN_TXFIDR_IDR_Pos                                     (0U)
#define    CAN_TXFIDR_IDR_Msk                                     (0xffffffffU << CAN_TXFIDR_IDR_Pos)
#define    CAN_TXFIDR_IDR                                         CAN_TXFIDR_IDR_Msk

#define    CAN_TXFDLCR_DLC_Pos                                    (0U)
#define    CAN_TXFDLCR_DLC_Msk                                    (0xfU << CAN_TXFDLCR_DLC_Pos)
#define    CAN_TXFDLCR_DLC                                        CAN_TXFDLCR_DLC_Msk

#define    CAN_TXFDW1R_DB_Pos                                     (0U)
#define    CAN_TXFDW1R_DB_Msk                                     (0xffffffffU << CAN_TXFDW1R_DB_Pos)
#define    CAN_TXFDW1R_DB                                         CAN_TXFDW1R_DB_Msk

#define    CAN_TXFDW2R_DB_Pos                                     (0U)
#define    CAN_TXFDW2R_DB_Msk                                     (0xffffffffU << CAN_TXFDW2R_DB_Pos)
#define    CAN_TXFDW2R_DB                                         CAN_TXFDW2R_DB_Msk

#define    CAN_HPBIDR_IDR_Pos                                     (0U)
#define    CAN_HPBIDR_IDR_Msk                                     (0xffffffffU << CAN_HPBIDR_IDR_Pos)
#define    CAN_HPBIDR_IDR                                         CAN_HPBIDR_IDR_Msk

#define    CAN_HPBDLCR_DLC_Pos                                    (0U)
#define    CAN_HPBDLCR_DLC_Msk                                    (0xfU << CAN_HPBDLCR_DLC_Pos)
#define    CAN_HPBDLCR_DLC                                        CAN_HPBDLCR_DLC_Msk

#define    CAN_HPBDW1R_DB_Pos                                     (0U)
#define    CAN_HPBDW1R_DB_Msk                                     (0xffffffffU << CAN_HPBDW1R_DB_Pos)
#define    CAN_HPBDW1R_DB                                         CAN_HPBDW1R_DB_Msk

#define    CAN_HPBDW2R_DB_Pos                                     (0U)
#define    CAN_HPBDW2R_DB_Msk                                     (0xffffffffU << CAN_HPBDW2R_DB_Pos)
#define    CAN_HPBDW2R_DB                                         CAN_HPBDW2R_DB_Msk

#define    CAN_RXFIDR_IDR_Pos                                     (0U)
#define    CAN_RXFIDR_IDR_Msk                                     (0xffffffffU << CAN_RXFIDR_IDR_Pos)
#define    CAN_RXFIDR_IDR                                         CAN_RXFIDR_IDR_Msk

#define    CAN_RXFDLCR_DLC_Pos                                    (0U)
#define    CAN_RXFDLCR_DLC_Msk                                    (0xfU << CAN_RXFDLCR_DLC_Pos)
#define    CAN_RXFDLCR_DLC                                        CAN_RXFDLCR_DLC_Msk

#define    CAN_RXFDW1R_DB_Pos                                     (0U)
#define    CAN_RXFDW1R_DB_Msk                                     (0xffffffffU << CAN_RXFDW1R_DB_Pos)
#define    CAN_RXFDW1R_DB                                         CAN_RXFDW1R_DB_Msk

#define    CAN_RXFDW2R_DB_Pos                                     (0U)
#define    CAN_RXFDW2R_DB_Msk                                     (0xffffffffU << CAN_RXFDW2R_DB_Pos)
#define    CAN_RXFDW2R_DB                                         CAN_RXFDW2R_DB_Msk

#define    CAN_AFR_UAF_Pos                                        (0U)
#define    CAN_AFR_UAF_Msk                                        (0xfU << CAN_AFR_UAF_Pos)
#define    CAN_AFR_UAF                                            CAN_AFR_UAF_Msk

#define    CAN_AFMR_AMRTR_Pos                                     (31U)
#define    CAN_AFMR_AMRTR_Msk                                     (0x1U << CAN_AFMR_AMRTR_Pos)
#define    CAN_AFMR_AMRTR                                         CAN_AFMR_AMRTR_Msk

#define    CAN_AFMR_AMID18_Pos                                    (13U)
#define    CAN_AFMR_AMID18_Msk                                    (0x3ffffU << CAN_AFMR_AMID18_Pos)
#define    CAN_AFMR_AMID18                                        CAN_AFMR_AMID18_Msk

#define    CAN_AFMR_AMIDE_Pos                                     (12U)
#define    CAN_AFMR_AMIDE_Msk                                     (0x1U << CAN_AFMR_AMIDE_Pos)
#define    CAN_AFMR_AMIDE                                         CAN_AFMR_AMIDE_Msk

#define    CAN_AFMR_AMSRR_Pos                                     (11U)
#define    CAN_AFMR_AMSRR_Msk                                     (0x1U << CAN_AFMR_AMSRR_Pos)
#define    CAN_AFMR_AMSRR                                         CAN_AFMR_AMSRR_Msk

#define    CAN_AFMR_AMID11_Pos                                    (0U)
#define    CAN_AFMR_AMID11_Msk                                    (0x7ffU << CAN_AFMR_AMID11_Pos)
#define    CAN_AFMR_AMID11                                        CAN_AFMR_AMID11_Msk

#define    CAN_AFIR_AIRTR_Pos                                     (31U)
#define    CAN_AFIR_AIRTR_Msk                                     (0x1U << CAN_AFIR_AIRTR_Pos)
#define    CAN_AFIR_AIRTR                                         CAN_AFIR_AIRTR_Msk

#define    CAN_AFIR_AIID18_Pos                                    (13U)
#define    CAN_AFIR_AIID18_Msk                                    (0x3ffffU << CAN_AFIR_AIID18_Pos)
#define    CAN_AFIR_AIID18                                        CAN_AFIR_AIID18_Msk

#define    CAN_AFIR_AIIDE_Pos                                     (12U)
#define    CAN_AFIR_AIIDE_Msk                                     (0x1U << CAN_AFIR_AIIDE_Pos)
#define    CAN_AFIR_AIIDE                                         CAN_AFIR_AIIDE_Msk

#define    CAN_AFIR_AISRR_Pos                                     (11U)
#define    CAN_AFIR_AISRR_Msk                                     (0x1U << CAN_AFIR_AISRR_Pos)
#define    CAN_AFIR_AISRR                                         CAN_AFIR_AISRR_Msk

#define    CAN_AFIR_AIID11_Pos                                    (0U)
#define    CAN_AFIR_AIID11_Msk                                    (0x7ffU << CAN_AFIR_AIID11_Pos)
#define    CAN_AFIR_AIID11                                        CAN_AFIR_AIID11_Msk



#define    FL_CAN_ERROR_STATUS_CONFIG                              (0x0U << CAN_SR_ESTAT_Pos)
#define    FL_CAN_ERROR_STATUS_ACTIVE                              (0x1U << CAN_SR_ESTAT_Pos)
#define    FL_CAN_ERROR_STATUS_BUSOFF                              (0x2U << CAN_SR_ESTAT_Pos)
#define    FL_CAN_ERROR_STATUS_PASSIVE                             (0x3U << CAN_SR_ESTAT_Pos)


#define    FL_CAN_RTR_BIT_LOW                                      (0x0U << CAN_AFIR_AIRTR_Pos)
#define    FL_CAN_RTR_BIT_HIGH                                     (0x1U << CAN_AFIR_AIRTR_Pos)


#define    FL_CAN_IDE_BIT_LOW                                      (0x0U << CAN_AFIR_AIIDE_Pos)
#define    FL_CAN_IDE_BIT_HIGH                                     (0x1U << CAN_AFIR_AIIDE_Pos)

#define    FL_CAN_SRR_BIT_LOW                                      (0x0U << CAN_AFIR_AISRR_Pos)
#define    FL_CAN_SRR_BIT_HIGH                                     (0x1U << CAN_AFIR_AISRR_Pos)


#define    FL_CAN_SOFTWARE_NO_RESET                                 (0x0U << CAN_CR_SRST_Pos)
#define    FL_CAN_SOFTWARE_RESET                                    (0x1U << CAN_CR_SRST_Pos)



#define    FL_CAN_TS1_1Tq                                         (0U)
#define    FL_CAN_TS1_2Tq                                         (1U)
#define    FL_CAN_TS1_3Tq                                         (2U)
#define    FL_CAN_TS1_4Tq                                         (3U)
#define    FL_CAN_TS1_5Tq                                         (4U)
#define    FL_CAN_TS1_6Tq                                         (5U)
#define    FL_CAN_TS1_7Tq                                         (6U)
#define    FL_CAN_TS1_8Tq                                         (7U)
#define    FL_CAN_TS1_9Tq                                         (8U)
#define    FL_CAN_TS1_10Tq                                        (9U)
#define    FL_CAN_TS1_11Tq                                        (10U)
#define    FL_CAN_TS1_12Tq                                        (11U)
#define    FL_CAN_TS1_13Tq                                        (12U)
#define    FL_CAN_TS1_14Tq                                        (13U)
#define    FL_CAN_TS1_15Tq                                        (14U)
#define    FL_CAN_TS1_16Tq                                        (15U)

#define    FL_CAN_TS2_1Tq                                         (0U)
#define    FL_CAN_TS2_2Tq                                         (1U)
#define    FL_CAN_TS2_3Tq                                         (2U)
#define    FL_CAN_TS2_4Tq                                         (3U)
#define    FL_CAN_TS2_5Tq                                         (4U)
#define    FL_CAN_TS2_6Tq                                         (5U)
#define    FL_CAN_TS2_7Tq                                         (6U)
#define    FL_CAN_TS2_8Tq                                         (7U)


#define    FL_CAN_SJW_1Tq                                         (0U)
#define    FL_CAN_SJW_2Tq                                         (1U)
#define    FL_CAN_SJW_3Tq                                         (2U)
#define    FL_CAN_SJW_4Tq                                         (3U)

#define    FL_CAN_MODE_NORMAL                                     (0U)
#define    FL_CAN_MODE_LOOPBACK                                   (1U)
#define    FL_CAN_MODE_CONFIG                                     (2U)

#define    FL_CAN_FIL1_EN                                         (1U << 0U)
#define    FL_CAN_FIL2_EN                                         (1U << 1U)
#define    FL_CAN_FIL3_EN                                         (1U << 2U)
#define    FL_CAN_FIL4_EN                                         (1U << 3U)

#define    FL_CAN_FIL1_MSK                                        (1U << 0U)
#define    FL_CAN_FIL2_MSK                                        (1U << 1U)
#define    FL_CAN_FIL3_MSK                                        (1U << 2U)
#define    FL_CAN_FIL4_MSK                                        (1U << 3U)


#define    FL_CAN_FILTER1                                         (0x0U << 0U)
#define    FL_CAN_FILTER2                                         (0x1U << 0U)
#define    FL_CAN_FILTER3                                         (0x2U << 0U)
#define    FL_CAN_FILTER4                                         (0x3U << 0U)



#define    FL_CAN_FORMAT_STANDARD_DATA                            (0U)
#define    FL_CAN_FORMAT_STANDARD_REMOTE                          (1U)
#define    FL_CAN_FORMAT_EXTEND_DATA                              (2U)
#define    FL_CAN_FORMAT_EXTEND_REMOTE                            (3U)


#define CAN_TIMEOUT      0xFFFFFU

/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup CAN_FL_Exported_Functions CAN Exported Functions
  * @{
  */

/**
  * @brief    CAN enable
  * @rmtoll   CR    CEN    FL_CAN_Enable
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Enable(CAN_Type *CANx)
{
    SET_BIT(CANx->CR, CAN_CR_CEN_Msk);
}

/**
  * @brief    Get CAN enable status
  * @rmtoll   CR    CEN    FL_CAN_IsEnabled
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsEnabled(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->CR, CAN_CR_CEN_Msk) == CAN_CR_CEN_Msk);
}

/**
  * @brief    CAN disable
  * @rmtoll   CR    CEN    FL_CAN_Disable
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Disable(CAN_Type *CANx)
{
    CLEAR_BIT(CANx->CR, CAN_CR_CEN_Msk);
}

/**
  * @brief    Set CAN software reset
  * @rmtoll   CR    SRST    FL_CAN_SetSoftwareReset
  * @param    CANx CAN instance
  * @param    reset This parameter can be one of the following values:
  *           @arg @ref FL_CAN_SOFTWARE_NO_RESET
  *           @arg @ref FL_CAN_SOFTWARE_RESET
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_SetSoftwareReset(CAN_Type *CANx, uint32_t reset)
{
    MODIFY_REG(CANx->CR, CAN_CR_SRST_Msk, reset);
}

/**
  * @brief    Get CAN software reset
  * @rmtoll   CR    SRST    FL_CAN_GetSoftwareReset
  * @param    CANx CAN instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CAN_SOFTWARE_NO_RESET
  *           @arg @ref FL_CAN_SOFTWARE_RESET
  */
__STATIC_INLINE uint32_t FL_CAN_GetSoftwareReset(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->CR, CAN_CR_SRST_Msk));
}

/**
  * @brief    Enable loop back mode
  * @rmtoll   MSR    LPBACK    FL_CAN_EnableLoopBackMode
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_EnableLoopBackMode(CAN_Type *CANx)
{
    SET_BIT(CANx->MSR, CAN_MSR_LPBACK_Msk);
}
/**
  * @brief    CAN disable
  * @rmtoll   CR    CEN    FL_CAN_Disable
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_DisableLoopBackMode(CAN_Type *CANx)
{
    CLEAR_BIT(CANx->MSR, CAN_MSR_LPBACK_Msk);
}
/**
  * @brief    Get loop back mode Enable Status
  * @rmtoll   MSR    LPBACK    FL_CAN_IsEnabledLoopBackMode
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsEnabledLoopBackMode(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->MSR, CAN_MSR_LPBACK_Msk) == CAN_MSR_LPBACK_Msk);
}

/**
  * @brief    Set baud rate prescaler
  * @rmtoll   BRPR    BRP    FL_CAN_WriteBaudRatePrescaler
  * @param    CANx CAN instance
  * @param    psc
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteBaudRatePrescaler(CAN_Type *CANx, uint32_t psc)
{
    MODIFY_REG(CANx->BRPR, CAN_BRPR_BRP_Msk, (psc << CAN_BRPR_BRP_Pos));
}

/**
  * @brief    Get baud rate prescaler
  * @rmtoll   BRPR    BRP    FL_CAN_ReadBaudRatePrescaler
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadBaudRatePrescaler(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->BRPR, CAN_BRPR_BRP_Msk) >> CAN_BRPR_BRP_Pos);
}

/**
  * @brief    Set synchronization jump width
  * @rmtoll   BTR    SJW    FL_CAN_WriteSyncJumpWidth
  * @param    CANx CAN instance
  * @param    width
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteSyncJumpWidth(CAN_Type *CANx, uint32_t width)
{
    MODIFY_REG(CANx->BTR, CAN_BTR_SJW_Msk, (width << CAN_BTR_SJW_Pos));
}

/**
  * @brief    Get synchronization jump width
  * @rmtoll   BTR    SJW    FL_CAN_ReadSyncJumpWidth
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadSyncJumpWidth(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->BTR, CAN_BTR_SJW_Msk) >> CAN_BTR_SJW_Pos);
}

/**
  * @brief    Set time segment2 length
  * @rmtoll   BTR    TS2    FL_CAN_WriteTimeSegment2Length
  * @param    CANx CAN instance
  * @param    length
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteTimeSegment2Length(CAN_Type *CANx, uint32_t length)
{
    MODIFY_REG(CANx->BTR, CAN_BTR_TS2_Msk, (length << CAN_BTR_TS2_Pos));
}

/**
  * @brief    Get time segment2 length
  * @rmtoll   BTR    TS2    FL_CAN_ReadTimeSegment2Length
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadTimeSegment2Length(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->BTR, CAN_BTR_TS2_Msk) >> CAN_BTR_TS2_Pos);
}

/**
  * @brief    Set time segment2 length
  * @rmtoll   BTR    TS1    FL_CAN_WriteTimeSegment1Length
  * @param    CANx CAN instance
  * @param    length
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteTimeSegment1Length(CAN_Type *CANx, uint32_t length)
{
    MODIFY_REG(CANx->BTR, CAN_BTR_TS1_Msk, (length << CAN_BTR_TS1_Pos));
}

/**
  * @brief    Get time segment2 length
  * @rmtoll   BTR    TS1    FL_CAN_ReadTimeSegment1Length
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadTimeSegment1Length(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->BTR, CAN_BTR_TS1_Msk) >> CAN_BTR_TS1_Pos);
}

/**
  * @brief    Get receive error number
  * @rmtoll   ECR    REC    FL_CAN_ReadRXErrorCount
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadRXErrorCount(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ECR, CAN_ECR_REC_Msk) >> CAN_ECR_REC_Pos);
}

/**
  * @brief    Get transmit error number
  * @rmtoll   ECR    TEC    FL_CAN_ReadTXErrorCount
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadTXErrorCount(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ECR, CAN_ECR_TEC_Msk) >> CAN_ECR_TEC_Pos);
}

/**
  * @brief    Get ACK error flag
  * @rmtoll   ESR    ACKER    FL_CAN_IsActiveFlag_AckError
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_AckError(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ESR, CAN_ESR_ACKER_Msk) == (CAN_ESR_ACKER_Msk));
}

/**
  * @brief    Clear ACK error flag
  * @rmtoll   ESR    ACKER    FL_CAN_ClearFlag_AckError
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_AckError(CAN_Type *CANx)
{
    WRITE_REG(CANx->ESR, CAN_ESR_ACKER_Msk);
}

/**
  * @brief    Get receive bit error flag
  * @rmtoll   ESR    BERR    FL_CAN_IsActiveFlag_BitError
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_BitError(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ESR, CAN_ESR_BERR_Msk) == (CAN_ESR_BERR_Msk));
}

/**
  * @brief    Clear receive bit error flag
  * @rmtoll   ESR    BERR    FL_CAN_ClearFlag_BitError
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_BitError(CAN_Type *CANx)
{
    WRITE_REG(CANx->ESR, CAN_ESR_BERR_Msk);
}

/**
  * @brief    Get stuffing error flag
  * @rmtoll   ESR    STER    FL_CAN_IsActiveFlag_StuffError
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_StuffError(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ESR, CAN_ESR_STER_Msk) == (CAN_ESR_STER_Msk));
}

/**
  * @brief    Clear stuffing error flag
  * @rmtoll   ESR    STER    FL_CAN_ClearFlag_StuffError
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_StuffError(CAN_Type *CANx)
{
    WRITE_REG(CANx->ESR, CAN_ESR_STER_Msk);
}

/**
  * @brief    Get form error flag
  * @rmtoll   ESR    FMER    FL_CAN_IsActiveFlag_FormatError
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_FormatError(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ESR, CAN_ESR_FMER_Msk) == (CAN_ESR_FMER_Msk));
}

/**
  * @brief    Clear form error flag
  * @rmtoll   ESR    FMER    FL_CAN_ClearFlag_FormatError
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_FormatError(CAN_Type *CANx)
{
    WRITE_REG(CANx->ESR, CAN_ESR_FMER_Msk);
}

/**
  * @brief    Get CRC error fiag
  * @rmtoll   ESR    CRCER    FL_CAN_IsActiveFlag_CRCError
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_CRCError(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ESR, CAN_ESR_CRCER_Msk) == (CAN_ESR_CRCER_Msk));
}

/**
  * @brief    Clear CRC error flag
  * @rmtoll   ESR    CRCER    FL_CAN_ClearFlag_CRCError
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_CRCError(CAN_Type *CANx)
{
    WRITE_REG(CANx->ESR, CAN_ESR_CRCER_Msk);
}

/**
  * @brief    Get acceptance filter busy flag
  * @rmtoll   SR    ACFBSY    FL_CAN_IsActiveFlag_FilterBusy
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_FilterBusy(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->SR, CAN_SR_ACFBSY_Msk) == (CAN_SR_ACFBSY_Msk));
}

/**
  * @brief    Get transmit FIFO FULL interrupt flag
  * @rmtoll   SR    TXFLL    FL_CAN_IsActiveFlag_TXBuffFullSignal
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_TXBuffFullSignal(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->SR, CAN_SR_TXFLL_Msk) == (CAN_SR_TXFLL_Msk));
}

/**
  * @brief    Get high priority transmit buffer FULL interrupt flag
  * @rmtoll   SR    TXBFLL    FL_CAN_IsActiveFlag_TXHighPriorBuffFullSignal
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_TXHighPriorBuffFullSignal(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->SR, CAN_SR_TXBFLL_Msk) == (CAN_SR_TXBFLL_Msk));
}

/**
  * @brief    Get error status flag
  * @rmtoll   SR    ESTAT    FL_CAN_GetErrorStatus
  * @param    CANx CAN instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CAN_ERROR_STATUS_CONFIG
  *           @arg @ref FL_CAN_ERROR_STATUS_ACTIVE
  *           @arg @ref FL_CAN_ERROR_STATUS_BUSOFF
  *           @arg @ref FL_CAN_ERROR_STATUS_PASSIVE
  */
__STATIC_INLINE uint32_t FL_CAN_GetErrorStatus(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->SR, CAN_SR_ESTAT_Msk));
}

/**
  * @brief    Get error warning
  * @rmtoll   SR    ERRWRN    FL_CAN_IsActiveFlag_ErrorWarning
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_ErrorWarning(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->SR, CAN_SR_ERRWRN_Msk) == (CAN_SR_ERRWRN_Msk));
}

/**
  * @brief    Get bus busy flag
  * @rmtoll   SR    BBSY    FL_CAN_IsActiveFlag_BusBusy
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_BusBusy(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->SR, CAN_SR_BBSY_Msk) == (CAN_SR_BBSY_Msk));
}

/**
  * @brief    Get bus IDLE flag
  * @rmtoll   SR    BIDLE    FL_CAN_IsActiveFlag_BusIdle
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_BusIdle(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->SR, CAN_SR_BIDLE_Msk) == (CAN_SR_BIDLE_Msk));
}

/**
  * @brief    Get normal mode flag
  * @rmtoll   SR    NORMAL    FL_CAN_IsActiveFlag_NormalMode
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_NormalMode(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->SR, CAN_SR_NORMAL_Msk) == (CAN_SR_NORMAL_Msk));
}

/**
  * @brief    Get loop back mode flag
  * @rmtoll   SR    LBACK    FL_CAN_IsActiveFlag_LoopbackMode
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_LoopbackMode(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->SR, CAN_SR_LBACK_Msk) == (CAN_SR_LBACK_Msk));
}

/**
  * @brief    Get configuration mode flag
  * @rmtoll   SR    CONFIG    FL_CAN_IsActiveFlag_ConfigMode
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_ConfigMode(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->SR, CAN_SR_CONFIG_Msk) == (CAN_SR_CONFIG_Msk));
}

/**
  * @brief    Get bus off interrupt flag
  * @rmtoll   ISR    BSOFF    FL_CAN_IsActiveFlag_BusOff
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_BusOff(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ISR, CAN_ISR_BSOFF_Msk) == (CAN_ISR_BSOFF_Msk));
}

/**
  * @brief    Get error interrupt  flag
  * @rmtoll   ISR    ERROR    FL_CAN_IsActiveFlag_Error
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_Error(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ISR, CAN_ISR_ERROR_Msk) == (CAN_ISR_ERROR_Msk));
}

/**
  * @brief    Get receive FIFO not empty interrupt flag
  * @rmtoll   ISR    RXNEMP    FL_CAN_IsActiveFlag_RXNotEmpty
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_RXNotEmpty(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ISR, CAN_ISR_RXNEMP_Msk) == (CAN_ISR_RXNEMP_Msk));
}

/**
  * @brief    Get receive FIFO overflow interrupt flag
  * @rmtoll   ISR    RXOFLW    FL_CAN_IsActiveFlag_RXOverflow
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_RXOverflow(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ISR, CAN_ISR_RXOFLW_Msk) == (CAN_ISR_RXOFLW_Msk));
}

/**
  * @brief    Get receive FIFO empty interrupt flag
  * @rmtoll   ISR    RXUFLW    FL_CAN_IsActiveFlag_RXEmpty
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_RXEmpty(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ISR, CAN_ISR_RXUFLW_Msk) == (CAN_ISR_RXUFLW_Msk));
}

/**
  * @brief    Get receive Ok interrupt flag
  * @rmtoll   ISR    RXOK    FL_CAN_IsActiveFlag_RXOK
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_RXOK(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ISR, CAN_ISR_RXOK_Msk) == (CAN_ISR_RXOK_Msk));
}

/**
  * @brief    Get high priority transmit buffer FULL interrupt flag
  * @rmtoll   ISR    TXBFLL    FL_CAN_IsActiveFlag_TXHighPriorBuffFull
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_TXHighPriorBuffFull(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ISR, CAN_ISR_TXBFLL_Msk) == (CAN_ISR_TXBFLL_Msk));
}

/**
  * @brief    Get transmit FIFO FULL interrupt flag
  * @rmtoll   ISR    TXFLL    FL_CAN_IsActiveFlag_TXBuffFull
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_TXBuffFull(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ISR, CAN_ISR_TXFLL_Msk) == (CAN_ISR_TXFLL_Msk));
}

/**
  * @brief    Get transmission OK interrupt flag
  * @rmtoll   ISR    TXOK    FL_CAN_IsActiveFlag_TXOK
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_TXOK(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ISR, CAN_ISR_TXOK_Msk) == (CAN_ISR_TXOK_Msk));
}

/**
  * @brief    Get arbitration lost interrupt flag
  * @rmtoll   ISR    ARBLST    FL_CAN_IsActiveFlag_ArbitrationLost
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsActiveFlag_ArbitrationLost(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->ISR, CAN_ISR_ARBLST_Msk) == (CAN_ISR_ARBLST_Msk));
}

/**
  * @brief    Bus OFF interrupt enable
  * @rmtoll   IER    BSOFFIE    FL_CAN_EnableIT_BusOff
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_EnableIT_BusOff(CAN_Type *CANx)
{
    SET_BIT(CANx->IER, CAN_IER_BSOFFIE_Msk);
}

/**
  * @brief    Get bus OFF interrupt enable status
  * @rmtoll   IER    BSOFFIE    FL_CAN_IsEnabledIT_BusOff
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsEnabledIT_BusOff(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->IER, CAN_IER_BSOFFIE_Msk) == CAN_IER_BSOFFIE_Msk);
}

/**
  * @brief    Bus OFF interrupt disable
  * @rmtoll   IER    BSOFFIE    FL_CAN_DisableIT_BusOff
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_DisableIT_BusOff(CAN_Type *CANx)
{
    CLEAR_BIT(CANx->IER, CAN_IER_BSOFFIE_Msk);
}

/**
  * @brief    Error interrupt enable
  * @rmtoll   IER    ERRORIE    FL_CAN_EnableIT_Error
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_EnableIT_Error(CAN_Type *CANx)
{
    SET_BIT(CANx->IER, CAN_IER_ERRORIE_Msk);
}

/**
  * @brief    Get error interrupt enable status
  * @rmtoll   IER    ERRORIE    FL_CAN_IsEnabledIT_Error
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsEnabledIT_Error(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->IER, CAN_IER_ERRORIE_Msk) == CAN_IER_ERRORIE_Msk);
}

/**
  * @brief    Error interrupt disable
  * @rmtoll   IER    ERRORIE    FL_CAN_DisableIT_Error
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_DisableIT_Error(CAN_Type *CANx)
{
    CLEAR_BIT(CANx->IER, CAN_IER_ERRORIE_Msk);
}

/**
  * @brief    Receive FIFO not empty interrupt enable
  * @rmtoll   IER    RXNEMPIE    FL_CAN_EnableIT_RXNotEmpty
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_EnableIT_RXNotEmpty(CAN_Type *CANx)
{
    SET_BIT(CANx->IER, CAN_IER_RXNEMPIE_Msk);
}

/**
  * @brief    Get receive FIFO not empty interrupt enable status
  * @rmtoll   IER    RXNEMPIE    FL_CAN_IsEnabledIT_RXNotEmpty
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsEnabledIT_RXNotEmpty(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->IER, CAN_IER_RXNEMPIE_Msk) == CAN_IER_RXNEMPIE_Msk);
}

/**
  * @brief    Receive FIFO not empty interrupt disable
  * @rmtoll   IER    RXNEMPIE    FL_CAN_DisableIT_RXNotEmpty
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_DisableIT_RXNotEmpty(CAN_Type *CANx)
{
    CLEAR_BIT(CANx->IER, CAN_IER_RXNEMPIE_Msk);
}

/**
  * @brief    Receive FIFO overflow interrupt ennable
  * @rmtoll   IER    RXOFLWIE    FL_CAN_EnableIT_RXOverflow
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_EnableIT_RXOverflow(CAN_Type *CANx)
{
    SET_BIT(CANx->IER, CAN_IER_RXOFLWIE_Msk);
}

/**
  * @brief    Get receive FIFO overflow interrupt enable status
  * @rmtoll   IER    RXOFLWIE    FL_CAN_IsEnabledIT_RXOverflow
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsEnabledIT_RXOverflow(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->IER, CAN_IER_RXOFLWIE_Msk) == CAN_IER_RXOFLWIE_Msk);
}

/**
  * @brief    Receive FIFO overflow interrupt disable
  * @rmtoll   IER    RXOFLWIE    FL_CAN_DisableIT_RXOverflow
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_DisableIT_RXOverflow(CAN_Type *CANx)
{
    CLEAR_BIT(CANx->IER, CAN_IER_RXOFLWIE_Msk);
}

/**
  * @brief    Receive FIFO empty interrupt enable
  * @rmtoll   IER    RXUFLWIE    FL_CAN_EnableIT_RXEmpty
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_EnableIT_RXEmpty(CAN_Type *CANx)
{
    SET_BIT(CANx->IER, CAN_IER_RXUFLWIE_Msk);
}

/**
  * @brief    Get receive FIFO empty interrupt enable status
  * @rmtoll   IER    RXUFLWIE    FL_CAN_IsEnabledIT_RXEmpty
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsEnabledIT_RXEmpty(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->IER, CAN_IER_RXUFLWIE_Msk) == CAN_IER_RXUFLWIE_Msk);
}

/**
  * @brief    Receive FIFO empty interrupt disable
  * @rmtoll   IER    RXUFLWIE    FL_CAN_DisableIT_RXEmpty
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_DisableIT_RXEmpty(CAN_Type *CANx)
{
    CLEAR_BIT(CANx->IER, CAN_IER_RXUFLWIE_Msk);
}

/**
  * @brief    Receive OK interrupt enable
  * @rmtoll   IER    RXOKIE    FL_CAN_EnableIT_RXOK
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_EnableIT_RXOK(CAN_Type *CANx)
{
    SET_BIT(CANx->IER, CAN_IER_RXOKIE_Msk);
}

/**
  * @brief    Get receive OK interrupt enable
  * @rmtoll   IER    RXOKIE    FL_CAN_IsEnabledIT_RXOK
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsEnabledIT_RXOK(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->IER, CAN_IER_RXOKIE_Msk) == CAN_IER_RXOKIE_Msk);
}

/**
  * @brief    Receive OK interrupt disable
  * @rmtoll   IER    RXOKIE    FL_CAN_DisableIT_RXOK
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_DisableIT_RXOK(CAN_Type *CANx)
{
    CLEAR_BIT(CANx->IER, CAN_IER_RXOKIE_Msk);
}

/**
  * @brief    High priority transmit buffer FULL interrupt enable
  * @rmtoll   IER    TXBFLLIE    FL_CAN_EnableIT_TXHighPriorBuffFull
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_EnableIT_TXHighPriorBuffFull(CAN_Type *CANx)
{
    SET_BIT(CANx->IER, CAN_IER_TXBFLLIE_Msk);
}

/**
  * @brief    Get high priority transmit buffer FULL interrupt enable status
  * @rmtoll   IER    TXBFLLIE    FL_CAN_IsEnabledIT_TXHighPriorBuffFull
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsEnabledIT_TXHighPriorBuffFull(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->IER, CAN_IER_TXBFLLIE_Msk) == CAN_IER_TXBFLLIE_Msk);
}

/**
  * @brief    High priority transmit buffer FULL interrupt disable
  * @rmtoll   IER    TXBFLLIE    FL_CAN_DisableIT_TXHighPriorBuffFull
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_DisableIT_TXHighPriorBuffFull(CAN_Type *CANx)
{
    CLEAR_BIT(CANx->IER, CAN_IER_TXBFLLIE_Msk);
}

/**
  * @brief    Transmit FIFO FULL interrupt enable
  * @rmtoll   IER    TXFLLIE    FL_CAN_EnableIT_TXBuffFull
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_EnableIT_TXBuffFull(CAN_Type *CANx)
{
    SET_BIT(CANx->IER, CAN_IER_TXFLLIE_Msk);
}

/**
  * @brief    Get transmit FIFO FULL interrupt enable
  * @rmtoll   IER    TXFLLIE    FL_CAN_IsEnabledIT_TXBuffFull
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsEnabledIT_TXBuffFull(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->IER, CAN_IER_TXFLLIE_Msk) == CAN_IER_TXFLLIE_Msk);
}

/**
  * @brief    Transmit FIFO FULL interrupt disable
  * @rmtoll   IER    TXFLLIE    FL_CAN_DisableIT_TXBuffFull
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_DisableIT_TXBuffFull(CAN_Type *CANx)
{
    CLEAR_BIT(CANx->IER, CAN_IER_TXFLLIE_Msk);
}

/**
  * @brief    Transmission OK interrupt enable
  * @rmtoll   IER    TXOKIE    FL_CAN_EnableIT_TXOK
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_EnableIT_TXOK(CAN_Type *CANx)
{
    SET_BIT(CANx->IER, CAN_IER_TXOKIE_Msk);
}

/**
  * @brief    Get transmission OK interrupt enable status
  * @rmtoll   IER    TXOKIE    FL_CAN_IsEnabledIT_TXOK
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsEnabledIT_TXOK(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->IER, CAN_IER_TXOKIE_Msk) == CAN_IER_TXOKIE_Msk);
}

/**
  * @brief    Transmission OK interrupt disable
  * @rmtoll   IER    TXOKIE    FL_CAN_DisableIT_TXOK
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_DisableIT_TXOK(CAN_Type *CANx)
{
    CLEAR_BIT(CANx->IER, CAN_IER_TXOKIE_Msk);
}

/**
  * @brief    Arbitration lost interrupt enable
  * @rmtoll   IER    ARBLSTIE    FL_CAN_EnableIT_ArbitrationLost
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_EnableIT_ArbitrationLost(CAN_Type *CANx)
{
    SET_BIT(CANx->IER, CAN_IER_ARBLSTIE_Msk);
}

/**
  * @brief    Get arbitration lost interrupt enable
  * @rmtoll   IER    ARBLSTIE    FL_CAN_IsEnabledIT_ArbitrationLost
  * @param    CANx CAN instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_IsEnabledIT_ArbitrationLost(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->IER, CAN_IER_ARBLSTIE_Msk) == CAN_IER_ARBLSTIE_Msk);
}

/**
  * @brief    Arbitration lost interrupt disable
  * @rmtoll   IER    ARBLSTIE    FL_CAN_DisableIT_ArbitrationLost
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_DisableIT_ArbitrationLost(CAN_Type *CANx)
{
    CLEAR_BIT(CANx->IER, CAN_IER_ARBLSTIE_Msk);
}

/**
  * @brief    Clear bus off interrupt flag
  * @rmtoll   ICR    CBSOFF    FL_CAN_ClearFlag_BusOff
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_BusOff(CAN_Type *CANx)
{
    WRITE_REG(CANx->ICR, CAN_ICR_CBSOFF_Msk);
}

/**
  * @brief    Clear error interrupt flag
  * @rmtoll   ICR    CERROR    FL_CAN_ClearFlag_Error
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_Error(CAN_Type *CANx)
{
    WRITE_REG(CANx->ICR, CAN_ICR_CERROR_Msk);
}

/**
  * @brief    Clear receive FIFO not empty interrupt flag
  * @rmtoll   ICR    CRXNEMP    FL_CAN_ClearFlag_RXNotEmpty
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_RXNotEmpty(CAN_Type *CANx)
{
    WRITE_REG(CANx->ICR, CAN_ICR_CRXNEMP_Msk);
}

/**
  * @brief    Clear  receive FIFO overflow interrupt flag
  * @rmtoll   ICR    CRXOFLW    FL_CAN_ClearFlag_RXOverflow
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_RXOverflow(CAN_Type *CANx)
{
    WRITE_REG(CANx->ICR, CAN_ICR_CRXOFLW_Msk);
}

/**
  * @brief    Clear receive FIFO underflow interrupt flag
  * @rmtoll   ICR    CRXUFLW    FL_CAN_ClearFlag_RXEmpty
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_RXEmpty(CAN_Type *CANx)
{
    WRITE_REG(CANx->ICR, CAN_ICR_CRXUFLW_Msk);
}

/**
  * @brief    Clear receive OK interrupt flag
  * @rmtoll   ICR    CRXOK    FL_CAN_ClearFlag_RXOK
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_RXOK(CAN_Type *CANx)
{
    WRITE_REG(CANx->ICR, CAN_ICR_CRXOK_Msk);
}

/**
  * @brief    Clear  high priority transmit buffer FULL interrupt flag
  * @rmtoll   ICR    CTXBFLL    FL_CAN_ClearFlag_TXHighPriorBuffFull
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_TXHighPriorBuffFull(CAN_Type *CANx)
{
    WRITE_REG(CANx->ICR, CAN_ICR_CTXBFLL_Msk);
}

/**
  * @brief    Clear transmit FIFO FULL interrupt flag
  * @rmtoll   ICR    CTXFLL    FL_CAN_ClearFlag_TXBuffFull
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_TXBuffFull(CAN_Type *CANx)
{
    WRITE_REG(CANx->ICR, CAN_ICR_CTXFLL_Msk);
}

/**
  * @brief    Clear transmission OK interrupt flag
  * @rmtoll   ICR    CTXOK    FL_CAN_ClearFlag_TXOK
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_TXOK(CAN_Type *CANx)
{
    WRITE_REG(CANx->ICR, CAN_ICR_CTXOK_Msk);
}

/**
  * @brief    Clear arbitration lost interrupt flag
  * @rmtoll   ICR    CARBLST    FL_CAN_ClearFlag_ArbitrationLost
  * @param    CANx CAN instance
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_ClearFlag_ArbitrationLost(CAN_Type *CANx)
{
    WRITE_REG(CANx->ICR, CAN_ICR_CARBLST_Msk);
}

/**
  * @brief    Set TXFIFO message identifier code
  * @rmtoll   TXFIDR    IDR    FL_CAN_WriteTXMessageID
  * @param    CANx CAN instance
  * @param    id
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteTXMessageID(CAN_Type *CANx, uint32_t id)
{
    MODIFY_REG(CANx->TXFIDR, (0xffffffffU << 0U), (id << 0U));
}

/**
  * @brief    Get TXFIFO message identifier code
  * @rmtoll   TXFIDR    IDR    FL_CAN_ReadTXMessageID
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadTXMessageID(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->TXFIDR, 0xffffffffU) >> 0U);
}

/**
  * @brief    Set TXFIFO data length code
  * @rmtoll   TXFDLCR    DLC    FL_CAN_WriteTXMessageLength
  * @param    CANx CAN instance
  * @param    length
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteTXMessageLength(CAN_Type *CANx, uint32_t length)
{
    MODIFY_REG(CANx->TXFDLCR, (0xfU << 0U), (length << 0U));
}

/**
  * @brief    Get TXFIFO data length code
  * @rmtoll   TXFDLCR    DLC    FL_CAN_ReadTXMessageLength
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadTXMessageLength(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->TXFDLCR, 0xfU) >> 0U);
}

/**
  * @brief    Set TXFIFO data word1
  * @rmtoll   TXFDW1R    DB    FL_CAN_WriteTXMessageWord1
  * @param    CANx CAN instance
  * @param    word
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteTXMessageWord1(CAN_Type *CANx, uint32_t word)
{
    MODIFY_REG(CANx->TXFDW1R, (0xffffffffU << 0U), (word << 0U));
}

/**
  * @brief    Get TXFIFO data word1
  * @rmtoll   TXFDW1R    DB    FL_CAN_ReadTXMessageWord1
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadTXMessageWord1(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->TXFDW1R, 0xffffffffU) >> 0U);
}

/**
  * @brief    Set TXFIFO data word2
  * @rmtoll   TXFDW2R    DB    FL_CAN_WriteTXMessageWord2
  * @param    CANx CAN instance
  * @param    word
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteTXMessageWord2(CAN_Type *CANx, uint32_t word)
{
    MODIFY_REG(CANx->TXFDW2R, (0xffffffffU << 0U), (word << 0U));
}

/**
  * @brief    Get TXFIFO data word2
  * @rmtoll   TXFDW2R    DB    FL_CAN_ReadTXMessageWord2
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadTXMessageWord2(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->TXFDW2R, 0xffffffffU) >> 0U);
}

/**
  * @brief    Set HPB identifier code
  * @rmtoll   HPBIDR    IDR    FL_CAN_WriteHighPriorTXMessageID
  * @param    CANx CAN instance
  * @param    id
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteHighPriorTXMessageID(CAN_Type *CANx, uint32_t id)
{
    MODIFY_REG(CANx->HPBIDR, (0xffffffffU << 0U), (id << 0U));
}

/**
  * @brief    Get HPB identifier code
  * @rmtoll   HPBIDR    IDR    FL_CAN_ReadHighPriorTXMessageID
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadHighPriorTXMessageID(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->HPBIDR, 0xffffffffU) >> 0U);
}

/**
  * @brief    Set HPB data length code
  * @rmtoll   HPBDLCR    DLC    FL_CAN_WriteHighPriorMessageLength
  * @param    CANx CAN instance
  * @param    length
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteHighPriorMessageLength(CAN_Type *CANx, uint32_t length)
{
    MODIFY_REG(CANx->HPBDLCR, (0xfU << 0U), (length << 0U));
}

/**
  * @brief    Get HPB data length code
  * @rmtoll   HPBDLCR    DLC    FL_CAN_ReadHighPriorMessageLength
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadHighPriorMessageLength(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->HPBDLCR, 0xfU) >> 0U);
}

/**
  * @brief    Set HPB data word1
  * @rmtoll   HPBDW1R    DB    FL_CAN_WriteHighPriorMessageWord1
  * @param    CANx CAN instance
  * @param    word
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteHighPriorMessageWord1(CAN_Type *CANx, uint32_t word)
{
    MODIFY_REG(CANx->HPBDW1R, (0xffffffffU << 0U), (word << 0U));
}

/**
  * @brief    Get HPB data word1
  * @rmtoll   HPBDW1R    DB    FL_CAN_ReadHighPriorMessageWord1
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadHighPriorMessageWord1(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->HPBDW1R, 0xffffffffU) >> 0U);
}

/**
  * @brief    Set HPB data word2
  * @rmtoll   HPBDW2R    DB    FL_CAN_WriteHighPriorMessageWord2
  * @param    CANx CAN instance
  * @param    word
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteHighPriorMessageWord2(CAN_Type *CANx, uint32_t word)
{
    MODIFY_REG(CANx->HPBDW2R, (0xffffffffU << 0U), (word << 0U));
}

/**
  * @brief    Get HPB data word2
  * @rmtoll   HPBDW2R    DB    FL_CAN_ReadHighPriorMessageWord2
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadHighPriorMessageWord2(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->HPBDW2R, 0xffffffffU) >> 0U);
}

/**
  * @brief    Set RXFIFO message identifier code
  * @rmtoll   RXFIDR    IDR    FL_CAN_WriteRXMessageID
  * @param    CANx CAN instance
  * @param    id
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteRXMessageID(CAN_Type *CANx, uint32_t id)
{
    MODIFY_REG(CANx->RXFIDR, (0xffffffffU << 0U), (id << 0U));
}

/**
  * @brief    Get RXFIFO message identifier code
  * @rmtoll   RXFIDR    IDR    FL_CAN_ReadRXMessageID
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadRXMessageID(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->RXFIDR, 0xffffffffU) >> 0U);
}

/**
  * @brief    Set RXFIFO data length code
  * @rmtoll   RXFDLCR    DLC    FL_CAN_WriteRXMessageLength
  * @param    CANx CAN instance
  * @param    length
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteRXMessageLength(CAN_Type *CANx, uint32_t length)
{
    MODIFY_REG(CANx->RXFDLCR, (0xfU << 0U), (length << 0U));
}

/**
  * @brief    Get RXFIFO data length code
  * @rmtoll   RXFDLCR    DLC    FL_CAN_ReadRXMessageLength
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadRXMessageLength(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->RXFDLCR, 0xfU) >> 0U);
}

/**
  * @brief    Set RXFIFO data word1
  * @rmtoll   RXFDW1R    DB    FL_CAN_WriteRXMessageWord1
  * @param    CANx CAN instance
  * @param    word
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteRXMessageWord1(CAN_Type *CANx, uint32_t word)
{
    MODIFY_REG(CANx->RXFDW1R, (0xffffffffU << 0U), (word << 0U));
}

/**
  * @brief    Get RXFIFO data word1
  * @rmtoll   RXFDW1R    DB    FL_CAN_ReadRXMessageWord1
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadRXMessageWord1(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->RXFDW1R, 0xffffffffU) >> 0U);
}

/**
  * @brief    Set RXFIFO data word2
  * @rmtoll   RXFDW2R    DB    FL_CAN_WriteRXMessageWord2
  * @param    CANx CAN instance
  * @param    word
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_WriteRXMessageWord2(CAN_Type *CANx, uint32_t word)
{
    MODIFY_REG(CANx->RXFDW2R, (0xffffffffU << 0U), (word << 0U));
}

/**
  * @brief    Get RXFIFO data word2
  * @rmtoll   RXFDW2R    DB    FL_CAN_ReadRXMessageWord2
  * @param    CANx CAN instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_ReadRXMessageWord2(CAN_Type *CANx)
{
    return (uint32_t)(READ_BIT(CANx->RXFDW2R, 0xffffffffU) >> 0U);
}

/**
  * @brief    Acceptance filter 4 enable
  * @rmtoll   AFR    UAF    FL_CAN_Filter_Enable
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Filter_Enable(CAN_Type *CANx, uint32_t filterX)
{
    SET_BIT(CANx->AFR, 0x1U << filterX);
}

/**
  * @brief    Get acceptance filter 4 enable status
  * @rmtoll   AFR    UAF    FL_CAN_Filter_IsEnabled
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_Filter_IsEnabled(CAN_Type *CANx, uint32_t filterX)
{
    return (uint32_t)(READ_BIT(CANx->AFR, (((0x1U << filterX) & 0xf) << CAN_AFR_UAF_Pos)) == (((0x1U << filterX) & 0xf) << CAN_AFR_UAF_Pos));
}

/**
  * @brief    Acceptance filter 4 disable
  * @rmtoll   AFR    UAF    FL_CAN_Filter_Disable
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Filter_Disable(CAN_Type *CANx, uint32_t filterX)
{
    CLEAR_BIT(CANx->AFR, (((0x1U << filterX) & 0xf) << CAN_AFR_UAF_Pos));
}

/**
  * @brief    Enable RTR participate filter compare
  * @rmtoll   AFMR    AMRTR    FL_CAN_Filter_EnableRTRCompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Filter_EnableRTRCompare(CAN_Type *CANx, uint32_t filterX)
{
    SET_BIT(*(&(CANx->AFMR0) + 2 * filterX), CAN_AFMR_AMRTR_Msk);
}

/**
  * @brief    Disable RTR participate filter compare
  * @rmtoll   AFMR    AMRTR    FL_CAN_Filter_DisableRTRCompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE void FL_CAN_Filter_DisableRTRCompare(CAN_Type *CANx, uint32_t filterX)
{
    CLEAR_BIT(*(&(CANx->AFMR0) + 2 * filterX), CAN_AFMR_AMRTR_Msk);
}

/**
  * @brief    Get RTR participate filter compare Enable Status
  * @rmtoll   AFMR    AMRTR    FL_CAN_Filter_IsEnabledRTRCompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_Filter_IsEnabledRTRCompare(CAN_Type *CANx, uint32_t filterX)
{
    return (uint32_t)(READ_BIT(*(&(CANx->AFMR0) + 2 * filterX), CAN_AFMR_AMRTR_Msk) == CAN_AFMR_AMRTR_Msk);
}

/**
  * @brief    Set ID low 18bit participate filter compare
  * @rmtoll   AFMR    AMID18    FL_CAN_Filter_WriteEXTIDCompareMask
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Filter_WriteEXTIDCompareMask(CAN_Type *CANx, uint32_t filterX, uint32_t id18)
{
    MODIFY_REG(*(&(CANx->AFMR0) + 2 * filterX), (0x3ffffU << CAN_AFMR_AMID18_Pos), (id18 << CAN_AFMR_AMID18_Pos));
}

/**
  * @brief    Get ID low 18bit participate filter compare
  * @rmtoll   AFMR    AMID18    FL_CAN_Filter_ReadEXTIDCompareMask
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   None
  */
__STATIC_INLINE uint32_t FL_CAN_Filter_ReadEXTIDCompareMask(CAN_Type *CANx, uint32_t filterX)
{
    return (uint32_t)(READ_BIT(*(&(CANx->AFMR0) + 2 * filterX), (0x3ffffU << CAN_AFMR_AMID18_Pos)) >> CAN_AFMR_AMID18_Pos);
}

/**
  * @brief    Enable IDE participate filter compare
  * @rmtoll   AFMR    AMIDE    FL_CAN_Filter_EnableIDECompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Filter_EnableIDECompare(CAN_Type *CANx, uint32_t filterX)
{
    SET_BIT(*(&(CANx->AFMR0) + 2 * filterX), CAN_AFMR_AMIDE_Msk);
}

/**
  * @brief    Disable IDE participate filter compare
  * @rmtoll   AFMR    AMIDE    FL_CAN_Filter_DisableIDECompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE void FL_CAN_Filter_DisableIDECompare(CAN_Type *CANx, uint32_t filterX)
{
    CLEAR_BIT(*(&(CANx->AFMR0) + 2 * filterX), CAN_AFMR_AMIDE_Msk);
}

/**
  * @brief    Get IDE participate filter compare Enable Status
  * @rmtoll   AFMR    AMIDE    FL_CAN_Filter_IsEnabledIDECompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_Filter_IsEnabledIDECompare(CAN_Type *CANx, uint32_t filterX)
{
    return (uint32_t)(READ_BIT(*(&(CANx->AFMR0) + 2 * filterX), CAN_AFMR_AMIDE_Msk) == CAN_AFMR_AMIDE_Msk);
}

/**
  * @brief    Enable SRR participate filter compare
  * @rmtoll   AFMR    AMSRR    FL_CAN_Filter_EnableSRRCompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Filter_EnableSRRCompare(CAN_Type *CANx, uint32_t filterX)
{
    SET_BIT(*(&(CANx->AFMR0) + 2 * filterX), CAN_AFMR_AMSRR_Msk);
}

/**
  * @brief    Disable SRR participate filter compare
  * @rmtoll   AFMR    AMSRR    FL_CAN_Filter_DisableSRRCompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE void FL_CAN_Filter_DisableSRRCompare(CAN_Type *CANx, uint32_t filterX)
{
    CLEAR_BIT(*(&(CANx->AFMR0) + 2 * filterX), CAN_AFMR_AMSRR_Msk);
}

/**
  * @brief    Get SRR participate filter compare Enable Status
  * @rmtoll   AFMR    AMSRR    FL_CAN_Filter_IsEnabledSRRCompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CAN_Filter_IsEnabledSRRCompare(CAN_Type *CANx, uint32_t filterX)
{
    return (uint32_t)(READ_BIT(*(&(CANx->AFMR0) + 2 * filterX), CAN_AFMR_AMSRR_Msk) == CAN_AFMR_AMSRR_Msk);
}

/**
  * @brief    Set ID high 11bit participate filter compare
  * @rmtoll   AFMR    AMID11    FL_CAN_Filter_WriteIDCompareMask
  * @param    CANx CAN instance
  * @param    filterX
  * @param    id11
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Filter_WriteIDCompareMask(CAN_Type *CANx, uint32_t filterX, uint32_t id11)
{
    MODIFY_REG(*((&(CANx->AFMR0)) + 2 * filterX), (0x7ffU << CAN_AFMR_AMID11_Pos), id11 << CAN_AFMR_AMID11_Pos);
}

/**
  * @brief    Get ID high 11bit participate filter compare
  * @rmtoll   AFMR    AMID11    FL_CAN_Filter_ReadIDCompareMask
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_Filter_ReadIDCompareMask(CAN_Type *CANx, uint32_t filterX)
{
    return (uint32_t)(READ_BIT(*((&(CANx->AFMR0)) + 2 * filterX), (0x7ffU << CAN_AFMR_AMID11_Pos)) >> CAN_AFMR_AMID11_Pos);
}

/**
  * @brief    Set filter RTR
  * @rmtoll   AFIR    AIRTR    FL_CAN_Filter_SetRTRCompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @param    rtr This parameter can be one of the following values:
  *           @arg @ref FL_CAN_RTR_BIT_LOW
  *           @arg @ref FL_CAN_RTR_BIT_HIGH
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Filter_SetRTRCompare(CAN_Type *CANx, uint32_t filterX, uint32_t rtr)
{
    MODIFY_REG(*((&(CANx->AFIR0)) + 2 * filterX), CAN_AFIR_AIRTR_Msk, rtr);
}

/**
  * @brief    Get filter RTR
  * @rmtoll   AFIR    AIRTR    FL_CAN_Filter_GetRTRCompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CAN_RTR_BIT_LOW
  *           @arg @ref FL_CAN_RTR_BIT_HIGH
  */
__STATIC_INLINE uint32_t FL_CAN_Filter_GetRTRCompare(CAN_Type *CANx, uint32_t filterX)
{
    return (uint32_t)(READ_BIT(*((&(CANx->AFIR0)) + 2 * filterX), CAN_AFIR_AIRTR_Msk));
}

/**
  * @brief    Set filter ID[17:0]
  * @rmtoll   AFIR    AIID18    FL_CAN_Filter_WriteEXTIDCompare
  * @param    CANx CAN instance
  * @param    filterX
  * @param    id18
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Filter_WriteEXTIDCompare(CAN_Type *CANx, uint32_t filterX, uint32_t id18)
{
    MODIFY_REG(*(&(CANx->AFIR0) + 2 * filterX), (0x3ffffU << CAN_AFIR_AIID18_Pos), (id18 << CAN_AFIR_AIID18_Pos));
}

/**
  * @brief    Get filter ID[17:0]
  * @rmtoll   AFIR    AIID18    FL_CAN_Filter_ReadEXTIDCompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_Filter_ReadEXTIDCompare(CAN_Type *CANx, uint32_t filterX)
{
    return (uint32_t)(READ_BIT(*(&(CANx->AFIR0) + 2 * filterX), (0x3ffffU << CAN_AFIR_AIID18_Pos)) >> CAN_AFIR_AIID18_Pos);
}

/**
  * @brief    Set filter IDE
  * @rmtoll   AFIR    AIIDE    FL_CAN_Filter_SetIDECompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @param    ide This parameter can be one of the following values:
  *           @arg @ref FL_CAN_IDE_BIT_LOW
  *           @arg @ref FL_CAN_IDE_BIT_HIGH
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Filter_SetIDECompare(CAN_Type *CANx, uint32_t filterX, uint32_t ide)
{
    MODIFY_REG(*((&(CANx->AFIR0)) + 2 * filterX), CAN_AFIR_AIIDE_Msk, ide);
}

/**
  * @brief    Get filter IDE
  * @rmtoll   AFIR    AIIDE    FL_CAN_Filter_GetIDECompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CAN_IDE_BIT_LOW
  *           @arg @ref FL_CAN_IDE_BIT_HIGH
  */
__STATIC_INLINE uint32_t FL_CAN_Filter_GetIDECompare(CAN_Type *CANx, uint32_t filterX)
{
    return (uint32_t)(READ_BIT(*((&(CANx->AFIR0)) + 2 * filterX), CAN_AFIR_AIIDE_Msk));
}

/**
  * @brief    Set filter SRR
  * @rmtoll   AFIR    AISRR    FL_CAN_Filter_SetSRRCompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @param    srr This parameter can be one of the following values:
  *           @arg @ref FL_CAN_SRR_BIT_LOW
  *           @arg @ref FL_CAN_SRR_BIT_HIGH
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Filter_SetSRRCompare(CAN_Type *CANx, uint32_t filterX, uint32_t srr)
{
    MODIFY_REG(*((&(CANx->AFIR0)) + 2 * filterX), CAN_AFIR_AISRR_Msk, srr);
}

/**
  * @brief    Get filter SRR
  * @rmtoll   AFIR    AISRR    FL_CAN_Filter_GetSRRCompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CAN_SRR_BIT_LOW
  *           @arg @ref FL_CAN_SRR_BIT_HIGH
  */
__STATIC_INLINE uint32_t FL_CAN_Filter_GetSRRCompare(CAN_Type *CANx, uint32_t filterX)
{
    return (uint32_t)(READ_BIT(*((&(CANx->AFIR0)) + 2 * filterX), CAN_AFIR_AISRR_Msk));
}

/**
  * @brief    Set filterID[28:18]
  * @rmtoll   AFIR    AIID11    FL_CAN_Filter_WriteIDCompare
  * @param    CANx CAN instance
  * @param    filterX
  * @param    id11
  * @retval   None
  */
__STATIC_INLINE void FL_CAN_Filter_WriteIDCompare(CAN_Type *CANx, uint32_t filterX, uint32_t id11)
{
    MODIFY_REG(*((&(CANx->AFIR0)) + 2 * filterX), (0x7ffU << CAN_AFIR_AIID11_Pos), id11 << CAN_AFIR_AIID11_Pos);
}

/**
  * @brief    Get filter ID[28:18]
  * @rmtoll   AFIR    AIID11    FL_CAN_Filter_ReadIDCompare
  * @param    CANx CAN instance
  * @param    filterX This parameter can be one of the following values:
  *           @arg @ref FL_CAN_FILTER1
  *           @arg @ref FL_CAN_FILTER2
  *           @arg @ref FL_CAN_FILTER3
  *           @arg @ref FL_CAN_FILTER4
  * @retval
  */
__STATIC_INLINE uint32_t FL_CAN_Filter_ReadIDCompare(CAN_Type *CANx, uint32_t filterX)
{
    return (uint32_t)(READ_BIT(*((&(CANx->AFIR0)) + 2 * filterX), 0x7ffU) >> CAN_AFIR_AIID11_Pos);
}

/**
  * @}
  */

/** @defgroup CAN_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_CAN_Init(CAN_Type *CANx, FL_CAN_InitTypeDef *CAN_InitStructure);
FL_ErrorStatus FL_CAN_FilterInit(CAN_Type *CANx, FL_CAN_FilterInitTypeDef *CAN_FilterInitStructure, uint32_t filterX);
void FL_CAN_StructInit(FL_CAN_InitTypeDef *CAN_InitStruct);
void FL_CAN_StructFilterInit(FL_CAN_FilterInitTypeDef *CAN_FilterInitStruct);
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

#endif /* __FM33LG0XX_FL_CAN_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-12*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
