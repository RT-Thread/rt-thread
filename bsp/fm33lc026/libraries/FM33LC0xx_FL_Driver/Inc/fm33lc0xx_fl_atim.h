/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_atim.h
  * @author  FMSH Application Team
  * @brief   Head file of ATIM FL Module
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
#ifndef __FM33LC0XX_FL_ATIM_H
#define __FM33LC0XX_FL_ATIM_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup ATIM ATIM
  * @brief ATIM FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup ATIM_FL_ES_INIT ATIM Exported Init structures
  * @{
  */

/**
  * @brief ATIM Init Sturcture Definition
  */
typedef struct
{
    /** 时钟源选择 */
    uint32_t clockSource;

    /** 预分频系数 */
    uint32_t prescaler;

    /** 计数模式 */
    uint32_t counterMode;

    /** 自动重装载值 */
    uint32_t autoReload;

    /** 预装载使能 */
    uint32_t autoReloadState;

    /** 定时器分频系数与数字滤波器所使用的采样时钟分频比 */
    uint32_t clockDivision;

    /** 重复计数次数 */
    uint32_t repetitionCounter;

} FL_ATIM_InitTypeDef;

/**
  * @brief ATIM Slave Init Sturcture Definition
  */
typedef struct
{

    /** 外部时钟源模式 */
    uint32_t slaveMode;

    /** 输入触发信号选择 */
    uint32_t triggerSrc;

    /** Trigger 延迟*/
    uint32_t triggerDelay;

} FL_ATIM_SlaveInitTypeDef;

/**
  * @brief ATIM ETR Init Structure Definition
  */
typedef struct
{
    /** 外部触发使能 */
    uint32_t useExternalTrigger;

    /** 外部时钟滤波 */
    uint32_t ETRFilter;

    /** 外部时钟分频 */
    uint32_t ETRClockDivision;

    /** 外部时钟触发极性 */
    uint32_t ETRPolarity;

} FL_ATIM_ETR_InitTypeDef;

/**
  * @brief  TIM Output Compare Init Structure Definition
  */
typedef struct
{
    /** 比较输出模式 */
    uint32_t OCMode;

    /** 比较正向通道输出使能 */
    uint32_t OCState;

    /** 比较互补通道输出使能 */
    uint32_t OCNState;

    /** 比较输出极性 */
    uint32_t OCPolarity;

    /** 比较互补输出极性 */
    uint32_t OCNPolarity;

    /** 比较输出通道快速模式使能 */
    uint32_t OCFastMode;

    /** 输出比较预装载 */
    uint32_t OCPreload;

    /** 通道比较值 */
    uint32_t compareValue;

    /** 输出空闲状态电平 */
    uint32_t OCIdleState;

    /** ETR清0使能 */
    uint32_t OCETRFStatus;

    /** 互补输出空闲状态电平 */
    uint32_t OCNIdleState;

} FL_ATIM_OC_InitTypeDef;

/**
  * @brief  TIM Input Capture Init Structure Definition
  */
typedef struct
{
    /** 输入捕获使能 */
    uint32_t captureState;

    /** 输入捕获极性 */
    uint32_t ICPolarity;

    /** 通道映射激活的输入选择 */
    uint32_t ICActiveInput;

    /** 输入分频 */
    uint32_t ICPrescaler;

    /** 输入滤波 */
    uint32_t ICFilter;

} FL_ATIM_IC_InitTypeDef;

/**
  * @brief  BDTR (Break and Dead Time) Init Structure Definition
  */
typedef struct
{
    /** 运行状态下的输出关闭状态 */
    uint32_t OSSRState;

    /** 空闲状态下的输出关闭状态 */
    uint32_t OSSIState;

    /** 寄存器写保护等级 */
    uint32_t lockLevel;

    /** 死区时间 */
    uint32_t deadTime;

    /** 刹车使能 */
    uint32_t breakState;

    /** 刹车信号滤波 */
    uint32_t breakFilter;

    /** 刹车信号极性 */
    uint32_t breakPolarity;

    /** 刹车后计数器重装后自动输出使能*/
    uint32_t automaticOutput;

    /** 刹车信号1门控 */
    uint32_t gatedBrakeSignal_1;

    /** 刹车信号2门控 */
    uint32_t gatedBrakeSignal_2;

    /** 两路刹车信号控制逻辑 */
    uint32_t brakeSignalCombined;

} FL_ATIM_BDTR_InitTypeDef;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup ATIM_FL_Exported_Constants ATIM Exported Constants
  * @{
  */

#define    ATIM_CR1_CKD_Pos                                       (8U)
#define    ATIM_CR1_CKD_Msk                                       (0x3U << ATIM_CR1_CKD_Pos)
#define    ATIM_CR1_CKD                                           ATIM_CR1_CKD_Msk

#define    ATIM_CR1_ARPE_Pos                                      (7U)
#define    ATIM_CR1_ARPE_Msk                                      (0x1U << ATIM_CR1_ARPE_Pos)
#define    ATIM_CR1_ARPE                                          ATIM_CR1_ARPE_Msk

#define    ATIM_CR1_CMS_Pos                                       (5U)
#define    ATIM_CR1_CMS_Msk                                       (0x3U << ATIM_CR1_CMS_Pos)
#define    ATIM_CR1_CMS                                           ATIM_CR1_CMS_Msk

#define    ATIM_CR1_DIR_Pos                                       (4U)
#define    ATIM_CR1_DIR_Msk                                       (0x1U << ATIM_CR1_DIR_Pos)
#define    ATIM_CR1_DIR                                           ATIM_CR1_DIR_Msk

#define    ATIM_CR1_OPM_Pos                                       (3U)
#define    ATIM_CR1_OPM_Msk                                       (0x1U << ATIM_CR1_OPM_Pos)
#define    ATIM_CR1_OPM                                           ATIM_CR1_OPM_Msk

#define    ATIM_CR1_URS_Pos                                       (2U)
#define    ATIM_CR1_URS_Msk                                       (0x1U << ATIM_CR1_URS_Pos)
#define    ATIM_CR1_URS                                           ATIM_CR1_URS_Msk

#define    ATIM_CR1_UDIS_Pos                                      (1U)
#define    ATIM_CR1_UDIS_Msk                                      (0x1U << ATIM_CR1_UDIS_Pos)
#define    ATIM_CR1_UDIS                                          ATIM_CR1_UDIS_Msk

#define    ATIM_CR1_CEN_Pos                                       (0U)
#define    ATIM_CR1_CEN_Msk                                       (0x1U << ATIM_CR1_CEN_Pos)
#define    ATIM_CR1_CEN                                           ATIM_CR1_CEN_Msk

#define    ATIM_CR2_OISN_Pos                                      (9U)
#define    ATIM_CR2_OISN_Msk                                      (0x1U << ATIM_CR2_OISN_Pos)
#define    ATIM_CR2_OISN                                          ATIM_CR2_OISN_Msk

#define    ATIM_CR2_OIS_Pos                                       (8U)
#define    ATIM_CR2_OIS_Msk                                       (0x1U << ATIM_CR2_OIS_Pos)
#define    ATIM_CR2_OIS                                           ATIM_CR2_OIS_Msk

#define    ATIM_CR2_TI1S_Pos                                      (7U)
#define    ATIM_CR2_TI1S_Msk                                      (0x1U << ATIM_CR2_TI1S_Pos)
#define    ATIM_CR2_TI1S                                          ATIM_CR2_TI1S_Msk

#define    ATIM_CR2_MMS_Pos                                       (4U)
#define    ATIM_CR2_MMS_Msk                                       (0x7U << ATIM_CR2_MMS_Pos)
#define    ATIM_CR2_MMS                                           ATIM_CR2_MMS_Msk

#define    ATIM_CR2_CCDS_Pos                                      (3U)
#define    ATIM_CR2_CCDS_Msk                                      (0x1U << ATIM_CR2_CCDS_Pos)
#define    ATIM_CR2_CCDS                                          ATIM_CR2_CCDS_Msk

#define    ATIM_CR2_CCUS_Pos                                      (2U)
#define    ATIM_CR2_CCUS_Msk                                      (0x1U << ATIM_CR2_CCUS_Pos)
#define    ATIM_CR2_CCUS                                          ATIM_CR2_CCUS_Msk

#define    ATIM_CR2_CCPC_Pos                                      (0U)
#define    ATIM_CR2_CCPC_Msk                                      (0x1U << ATIM_CR2_CCPC_Pos)
#define    ATIM_CR2_CCPC                                          ATIM_CR2_CCPC_Msk

#define    ATIM_SMCR_ETP_Pos                                      (15U)
#define    ATIM_SMCR_ETP_Msk                                      (0x1U << ATIM_SMCR_ETP_Pos)
#define    ATIM_SMCR_ETP                                          ATIM_SMCR_ETP_Msk

#define    ATIM_SMCR_ECE_Pos                                      (14U)
#define    ATIM_SMCR_ECE_Msk                                      (0x1U << ATIM_SMCR_ECE_Pos)
#define    ATIM_SMCR_ECE                                          ATIM_SMCR_ECE_Msk

#define    ATIM_SMCR_ETPS_Pos                                     (12U)
#define    ATIM_SMCR_ETPS_Msk                                     (0x3U << ATIM_SMCR_ETPS_Pos)
#define    ATIM_SMCR_ETPS                                         ATIM_SMCR_ETPS_Msk

#define    ATIM_SMCR_ETF_Pos                                      (8U)
#define    ATIM_SMCR_ETF_Msk                                      (0xfU << ATIM_SMCR_ETF_Pos)
#define    ATIM_SMCR_ETF                                          ATIM_SMCR_ETF_Msk

#define    ATIM_SMCR_MSM_Pos                                      (7U)
#define    ATIM_SMCR_MSM_Msk                                      (0x1U << ATIM_SMCR_MSM_Pos)
#define    ATIM_SMCR_MSM                                          ATIM_SMCR_MSM_Msk

#define    ATIM_SMCR_TS_Pos                                       (4U)
#define    ATIM_SMCR_TS_Msk                                       (0x7U << ATIM_SMCR_TS_Pos)
#define    ATIM_SMCR_TS                                           ATIM_SMCR_TS_Msk

#define    ATIM_SMCR_SMS_Pos                                      (0U)
#define    ATIM_SMCR_SMS_Msk                                      (0x7U << ATIM_SMCR_SMS_Pos)
#define    ATIM_SMCR_SMS                                          ATIM_SMCR_SMS_Msk

#define    ATIM_DIER_CC1BURSTEN_Pos                               (16U)
#define    ATIM_DIER_CC1BURSTEN_Msk                               (0x1U << ATIM_DIER_CC1BURSTEN_Pos)
#define    ATIM_DIER_CC1BURSTEN                                   ATIM_DIER_CC1BURSTEN_Msk

#define    ATIM_DIER_CC2BURSTEN_Pos                               (17U)
#define    ATIM_DIER_CC2BURSTEN_Msk                               (0x1U << ATIM_DIER_CC2BURSTEN_Pos)
#define    ATIM_DIER_CC2BURSTEN                                   ATIM_DIER_CC2BURSTEN_Msk

#define    ATIM_DIER_CC3BURSTEN_Pos                               (18U)
#define    ATIM_DIER_CC3BURSTEN_Msk                               (0x1U << ATIM_DIER_CC3BURSTEN_Pos)
#define    ATIM_DIER_CC3BURSTEN                                   ATIM_DIER_CC3BURSTEN_Msk

#define    ATIM_DIER_CC4BURSTEN_Pos                               (19U)
#define    ATIM_DIER_CC4BURSTEN_Msk                               (0x1U << ATIM_DIER_CC4BURSTEN_Pos)
#define    ATIM_DIER_CC4BURSTEN                                   ATIM_DIER_CC4BURSTEN_Msk

#define    ATIM_DIER_TDE_Pos                                      (14U)
#define    ATIM_DIER_TDE_Msk                                      (0x1U << ATIM_DIER_TDE_Pos)
#define    ATIM_DIER_TDE                                          ATIM_DIER_TDE_Msk

#define    ATIM_DIER_COMDE_Pos                                    (13U)
#define    ATIM_DIER_COMDE_Msk                                    (0x1U << ATIM_DIER_COMDE_Pos)
#define    ATIM_DIER_COMDE                                        ATIM_DIER_COMDE_Msk

#define    ATIM_DIER_CCDE_Pos                                     (9U)
#define    ATIM_DIER_CCDE_Msk                                     (0x1U << ATIM_DIER_CCDE_Pos)
#define    ATIM_DIER_CCDE                                         ATIM_DIER_CCDE_Msk

#define    ATIM_DIER_UDE_Pos                                      (8U)
#define    ATIM_DIER_UDE_Msk                                      (0x1U << ATIM_DIER_UDE_Pos)
#define    ATIM_DIER_UDE                                          ATIM_DIER_UDE_Msk

#define    ATIM_DIER_BIE_Pos                                      (7U)
#define    ATIM_DIER_BIE_Msk                                      (0x1U << ATIM_DIER_BIE_Pos)
#define    ATIM_DIER_BIE                                          ATIM_DIER_BIE_Msk

#define    ATIM_DIER_TIE_Pos                                      (6U)
#define    ATIM_DIER_TIE_Msk                                      (0x1U << ATIM_DIER_TIE_Pos)
#define    ATIM_DIER_TIE                                          ATIM_DIER_TIE_Msk

#define    ATIM_DIER_COMIE_Pos                                    (5U)
#define    ATIM_DIER_COMIE_Msk                                    (0x1U << ATIM_DIER_COMIE_Pos)
#define    ATIM_DIER_COMIE                                        ATIM_DIER_COMIE_Msk

#define    ATIM_DIER_CCIE_Pos                                     (1U)
#define    ATIM_DIER_CCIE_Msk                                     (0x1U << ATIM_DIER_CCIE_Pos)
#define    ATIM_DIER_CCIE                                         ATIM_DIER_CCIE_Msk

#define    ATIM_DIER_UIE_Pos                                      (0U)
#define    ATIM_DIER_UIE_Msk                                      (0x1U << ATIM_DIER_UIE_Pos)
#define    ATIM_DIER_UIE                                          ATIM_DIER_UIE_Msk

#define    ATIM_ISR_CCOF_Pos                                      (9U)
#define    ATIM_ISR_CCOF_Msk                                      (0x1U << ATIM_ISR_CCOF_Pos)
#define    ATIM_ISR_CCOF                                          ATIM_ISR_CCOF_Msk

#define    ATIM_ISR_BIF_Pos                                       (7U)
#define    ATIM_ISR_BIF_Msk                                       (0x1U << ATIM_ISR_BIF_Pos)
#define    ATIM_ISR_BIF                                           ATIM_ISR_BIF_Msk

#define    ATIM_ISR_TIF_Pos                                       (6U)
#define    ATIM_ISR_TIF_Msk                                       (0x1U << ATIM_ISR_TIF_Pos)
#define    ATIM_ISR_TIF                                           ATIM_ISR_TIF_Msk

#define    ATIM_ISR_COMIF_Pos                                     (5U)
#define    ATIM_ISR_COMIF_Msk                                     (0x1U << ATIM_ISR_COMIF_Pos)
#define    ATIM_ISR_COMIF                                         ATIM_ISR_COMIF_Msk

#define    ATIM_ISR_CCIF_Pos                                      (1U)
#define    ATIM_ISR_CCIF_Msk                                      (0x1U << ATIM_ISR_CCIF_Pos)
#define    ATIM_ISR_CCIF                                          ATIM_ISR_CCIF_Msk

#define    ATIM_ISR_UIF_Pos                                       (0U)
#define    ATIM_ISR_UIF_Msk                                       (0x1U << ATIM_ISR_UIF_Pos)
#define    ATIM_ISR_UIF                                           ATIM_ISR_UIF_Msk

#define    ATIM_EGR_BG_Pos                                        (7U)
#define    ATIM_EGR_BG_Msk                                        (0x1U << ATIM_EGR_BG_Pos)
#define    ATIM_EGR_BG                                            ATIM_EGR_BG_Msk

#define    ATIM_EGR_TG_Pos                                        (6U)
#define    ATIM_EGR_TG_Msk                                        (0x1U << ATIM_EGR_TG_Pos)
#define    ATIM_EGR_TG                                            ATIM_EGR_TG_Msk

#define    ATIM_EGR_COMG_Pos                                      (5U)
#define    ATIM_EGR_COMG_Msk                                      (0x1U << ATIM_EGR_COMG_Pos)
#define    ATIM_EGR_COMG                                          ATIM_EGR_COMG_Msk

#define    ATIM_EGR_CCG_Pos                                       (1U)
#define    ATIM_EGR_CCG_Msk                                       (0x1U << ATIM_EGR_CCG_Pos)
#define    ATIM_EGR_CCG                                           ATIM_EGR_CCG_Msk

#define    ATIM_EGR_UG_Pos                                        (0U)
#define    ATIM_EGR_UG_Msk                                        (0x1U << ATIM_EGR_UG_Pos)
#define    ATIM_EGR_UG                                            ATIM_EGR_UG_Msk

#define    ATIM_DCR_DBL_Pos                                       (8U)
#define    ATIM_DCR_DBL_Msk                                       (0x1fU << ATIM_DCR_DBL_Pos)
#define    ATIM_DCR_DBL                                           ATIM_DCR_DBL_Msk

#define    ATIM_DCR_DBA_Pos                                       (0U)
#define    ATIM_DCR_DBA_Msk                                       (0x1fU << ATIM_DCR_DBA_Pos)
#define    ATIM_DCR_DBA                                           ATIM_DCR_DBA_Msk

#define    ATIM_CCMR_OCCE_Pos                                     (7U)
#define    ATIM_CCMR_OCCE_Msk                                     (0x1U << ATIM_CCMR_OCCE_Pos)
#define    ATIM_CCMR_OCCE                                         ATIM_CCMR_OCCE_Msk

#define    ATIM_CCMR_OCM_Pos                                      (4U)
#define    ATIM_CCMR_OCM_Msk                                      (0x7U << ATIM_CCMR_OCM_Pos)
#define    ATIM_CCMR_OCM                                          ATIM_CCMR_OCM_Msk

#define    ATIM_CCMR_OCPE_Pos                                     (3U)
#define    ATIM_CCMR_OCPE_Msk                                     (0x1U << ATIM_CCMR_OCPE_Pos)
#define    ATIM_CCMR_OCPE                                         ATIM_CCMR_OCPE_Msk

#define    ATIM_CCMR_OCFE_Pos                                     (2U)
#define    ATIM_CCMR_OCFE_Msk                                     (0x1U << ATIM_CCMR_OCFE_Pos)
#define    ATIM_CCMR_OCFE                                         ATIM_CCMR_OCFE_Msk

#define    ATIM_CCMR_ICF_Pos                                      (4U)
#define    ATIM_CCMR_ICF_Msk                                      (0xfU << ATIM_CCMR_ICF_Pos)
#define    ATIM_CCMR_ICF                                          ATIM_CCMR_ICF_Msk

#define    ATIM_CCMR_ICPSC_Pos                                    (2U)
#define    ATIM_CCMR_ICPSC_Msk                                    (0x3U << ATIM_CCMR_ICPSC_Pos)
#define    ATIM_CCMR_ICPSC                                        ATIM_CCMR_ICPSC_Msk

#define    ATIM_CCMR_CCS_Pos                                      (0U)
#define    ATIM_CCMR_CCS_Msk                                      (0x3U << ATIM_CCMR_CCS_Pos)
#define    ATIM_CCMR_CCS                                          ATIM_CCMR_CCS_Msk

#define    ATIM_CCER_CCNP_Pos                                     (3U)
#define    ATIM_CCER_CCNP_Msk                                     (0x1U << ATIM_CCER_CCNP_Pos)
#define    ATIM_CCER_CCNP                                         ATIM_CCER_CCNP_Msk

#define    ATIM_CCER_CCNE_Pos                                     (2U)
#define    ATIM_CCER_CCNE_Msk                                     (0x1U << ATIM_CCER_CCNE_Pos)
#define    ATIM_CCER_CCNE                                         ATIM_CCER_CCNE_Msk

#define    ATIM_CCER_CCOP_Pos                                     (1U)
#define    ATIM_CCER_CCOP_Msk                                     (0x1U << ATIM_CCER_CCOP_Pos)
#define    ATIM_CCER_CCOP                                         ATIM_CCER_CCOP_Msk

#define    ATIM_CCER_CCIP_Pos                                     (1U)
#define    ATIM_CCER_CCIP_Msk                                     (0x1U << ATIM_CCER_CCIP_Pos)
#define    ATIM_CCER_CCIP                                         ATIM_CCER_CCIP_Msk

#define    ATIM_CCER_CCOE_Pos                                     (0U)
#define    ATIM_CCER_CCOE_Msk                                     (0x1U << ATIM_CCER_CCOE_Pos)
#define    ATIM_CCER_CCOE                                         ATIM_CCER_CCOE_Msk

#define    ATIM_CCER_CCIE_Pos                                     (0U)
#define    ATIM_CCER_CCIE_Msk                                     (0x1U << ATIM_CCER_CCIE_Pos)
#define    ATIM_CCER_CCIE                                         ATIM_CCER_CCIE_Msk

#define    ATIM_BDTR_MOE_Pos                                      (15U)
#define    ATIM_BDTR_MOE_Msk                                      (0x1U << ATIM_BDTR_MOE_Pos)
#define    ATIM_BDTR_MOE                                          ATIM_BDTR_MOE_Msk

#define    ATIM_BDTR_AOE_Pos                                      (14U)
#define    ATIM_BDTR_AOE_Msk                                      (0x1U << ATIM_BDTR_AOE_Pos)
#define    ATIM_BDTR_AOE                                          ATIM_BDTR_AOE_Msk

#define    ATIM_BDTR_BKP_Pos                                      (13U)
#define    ATIM_BDTR_BKP_Msk                                      (0x1U << ATIM_BDTR_BKP_Pos)
#define    ATIM_BDTR_BKP                                          ATIM_BDTR_BKP_Msk

#define    ATIM_BDTR_BKE_Pos                                      (12U)
#define    ATIM_BDTR_BKE_Msk                                      (0x1U << ATIM_BDTR_BKE_Pos)
#define    ATIM_BDTR_BKE                                          ATIM_BDTR_BKE_Msk

#define    ATIM_BDTR_OSSR_Pos                                     (11U)
#define    ATIM_BDTR_OSSR_Msk                                     (0x1U << ATIM_BDTR_OSSR_Pos)
#define    ATIM_BDTR_OSSR                                         ATIM_BDTR_OSSR_Msk

#define    ATIM_BDTR_OSSI_Pos                                     (10U)
#define    ATIM_BDTR_OSSI_Msk                                     (0x1U << ATIM_BDTR_OSSI_Pos)
#define    ATIM_BDTR_OSSI                                         ATIM_BDTR_OSSI_Msk

#define    ATIM_BDTR_LOCK_Pos                                     (8U)
#define    ATIM_BDTR_LOCK_Msk                                     (0x3U << ATIM_BDTR_LOCK_Pos)
#define    ATIM_BDTR_LOCK                                         ATIM_BDTR_LOCK_Msk

#define    ATIM_BDTR_DTG_Pos                                      (0U)
#define    ATIM_BDTR_DTG_Msk                                      (0xffU << ATIM_BDTR_DTG_Pos)
#define    ATIM_BDTR_DTG                                          ATIM_BDTR_DTG_Msk

#define    ATIM_BKCR_BRK1GATE_Pos                                 (8U)
#define    ATIM_BKCR_BRK1GATE_Msk                                 (0x1U << ATIM_BKCR_BRK1GATE_Pos)
#define    ATIM_BKCR_BRK1GATE                                     ATIM_BKCR_BRK1GATE_Msk

#define    ATIM_BKCR_BRK2GATE_Pos                                 (9U)
#define    ATIM_BKCR_BRK2GATE_Msk                                 (0x1U << ATIM_BKCR_BRK2GATE_Pos)
#define    ATIM_BKCR_BRK2GATE                                     ATIM_BKCR_BRK2GATE_Msk

#define    ATIM_BKCR_BRKF_Pos                                     (4U)
#define    ATIM_BKCR_BRKF_Msk                                     (0xfU << ATIM_BKCR_BRKF_Pos)
#define    ATIM_BKCR_BRKF                                         ATIM_BKCR_BRKF_Msk

#define    ATIM_BKCR_BRKCOMB_Pos                                  (3U)
#define    ATIM_BKCR_BRKCOMB_Msk                                  (0x1U << ATIM_BKCR_BRKCOMB_Pos)
#define    ATIM_BKCR_BRKCOMB                                      ATIM_BKCR_BRKCOMB_Msk

#define    ATIM_BKCR_HFDET_BRKEN_Pos                              (2U)
#define    ATIM_BKCR_HFDET_BRKEN_Msk                              (0x1U << ATIM_BKCR_HFDET_BRKEN_Pos)
#define    ATIM_BKCR_HFDET_BRKEN                                  ATIM_BKCR_HFDET_BRKEN_Msk

#define    ATIM_BKCR_SVD_BRKEN_Pos                                (1U)
#define    ATIM_BKCR_SVD_BRKEN_Msk                                (0x1U << ATIM_BKCR_SVD_BRKEN_Pos)
#define    ATIM_BKCR_SVD_BRKEN                                    ATIM_BKCR_SVD_BRKEN_Msk

#define    ATIM_BKCR_COMP_BRKEN_Pos                               (0U)
#define    ATIM_BKCR_COMP_BRKEN_Msk                               (0x1U << ATIM_BKCR_COMP_BRKEN_Pos)
#define    ATIM_BKCR_COMP_BRKEN                                   ATIM_BKCR_COMP_BRKEN_Msk



#define    FL_ATIM_CHANNEL_1                                      0x0U
#define    FL_ATIM_CHANNEL_2                                      0x1U
#define    FL_ATIM_CHANNEL_3                                      0x2U
#define    FL_ATIM_CHANNEL_4                                      0x3U



#define    FL_ATIM_CLK_DIVISION_DIV1                              (0x0U << ATIM_CR1_CKD_Pos)
#define    FL_ATIM_CLK_DIVISION_DIV2                              (0x1U << ATIM_CR1_CKD_Pos)
#define    FL_ATIM_CLK_DIVISION_DIV4                              (0x2U << ATIM_CR1_CKD_Pos)


#define    FL_ATIM_COUNTER_ALIGNED_EDGE                           (0x0U << ATIM_CR1_CMS_Pos)
#define    FL_ATIM_COUNTER_ALIGNED_CENTER_DOWN                    (0x1U << ATIM_CR1_CMS_Pos)
#define    FL_ATIM_COUNTER_ALIGNED_CENTER_UP                      (0x2U << ATIM_CR1_CMS_Pos)
#define    FL_ATIM_COUNTER_ALIGNED_CENTER_UP_DOWN                 (0x3U << ATIM_CR1_CMS_Pos)


#define    FL_ATIM_COUNTER_DIR_UP                                 (0x0U << ATIM_CR1_DIR_Pos)
#define    FL_ATIM_COUNTER_DIR_DOWN                               (0x1U << ATIM_CR1_DIR_Pos)


#define    FL_ATIM_ONE_PULSE_MODE_CONTINUOUS                      (0x0U << ATIM_CR1_OPM_Pos)
#define    FL_ATIM_ONE_PULSE_MODE_SINGLE                          (0x1U << ATIM_CR1_OPM_Pos)


#define    FL_ATIM_UPDATE_SOURCE_REGULAR                          (0x0U << ATIM_CR1_URS_Pos)
#define    FL_ATIM_UPDATE_SOURCE_COUNTER                          (0x1U << ATIM_CR1_URS_Pos)


#define    FL_ATIM_OCN_IDLE_STATE_LOW                             (0x0U << ATIM_CR2_OISN_Pos)
#define    FL_ATIM_OCN_IDLE_STATE_HIGH                            (0x1U << ATIM_CR2_OISN_Pos)


#define    FL_ATIM_OC_IDLE_STATE_LOW                              (0x0U << ATIM_CR2_OIS_Pos)
#define    FL_ATIM_OC_IDLE_STATE_HIGH                             (0x1U << ATIM_CR2_OIS_Pos)


#define    FL_ATIM_TRGO_RESET                                     (0x0U << ATIM_CR2_MMS_Pos)
#define    FL_ATIM_TRGO_ENABLE                                    (0x1U << ATIM_CR2_MMS_Pos)
#define    FL_ATIM_TRGO_UPDATE                                    (0x2U << ATIM_CR2_MMS_Pos)
#define    FL_ATIM_TRGO_CC1IF                                     (0x3U << ATIM_CR2_MMS_Pos)
#define    FL_ATIM_TRGO_OC1REF                                    (0x4U << ATIM_CR2_MMS_Pos)
#define    FL_ATIM_TRGO_OC2REF                                    (0x5U << ATIM_CR2_MMS_Pos)
#define    FL_ATIM_TRGO_OC3REF                                    (0x6U << ATIM_CR2_MMS_Pos)
#define    FL_ATIM_TRGO_OC4REF                                    (0x7U << ATIM_CR2_MMS_Pos)


#define    FL_ATIM_DMA_REQ_CC                                     (0x0U << ATIM_CR2_CCDS_Pos)
#define    FL_ATIM_DMA_REQ_UPDATE                                 (0x1U << ATIM_CR2_CCDS_Pos)


#define    FL_ATIM_UPDATE_SOURCE_COMG_ONLY                        (0x0U << ATIM_CR2_CCUS_Pos)
#define    FL_ATIM_UPDATE_SOURCE_COMG_AND_TRGI                    (0x1U << ATIM_CR2_CCUS_Pos)


#define    FL_ATIM_ETR_POLARITY_NORMAL                            (0x0U << ATIM_SMCR_ETP_Pos)
#define    FL_ATIM_ETR_POLARITY_INVERT                            (0x1U << ATIM_SMCR_ETP_Pos)


#define    FL_ATIM_ETR_PSC_DIV1                                   (0x0U << ATIM_SMCR_ETPS_Pos)
#define    FL_ATIM_ETR_PSC_DIV2                                   (0x1U << ATIM_SMCR_ETPS_Pos)
#define    FL_ATIM_ETR_PSC_DIV4                                   (0x2U << ATIM_SMCR_ETPS_Pos)
#define    FL_ATIM_ETR_PSC_DIV8                                   (0x3U << ATIM_SMCR_ETPS_Pos)


#define    FL_ATIM_ETR_FILTER_DIV1                                (0x0U << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV1_N2                             (0x1U << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV1_N4                             (0x2U << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV1_N8                             (0x3U << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV2_N6                             (0x4U << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV2_N8                             (0x5U << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV4_N6                             (0x6U << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV4_N8                             (0x7U << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV8_N6                             (0x8U << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV8_N8                             (0x9U << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV16_N5                            (0xaU << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV16_N6                            (0xbU << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV16_N8                            (0xcU << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV32_N5                            (0xdU << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV32_N6                            (0xeU << ATIM_SMCR_ETF_Pos)
#define    FL_ATIM_ETR_FILTER_DIV32_N8                            (0xfU << ATIM_SMCR_ETF_Pos)


#define    FL_ATIM_TRGI_ITR0                                      (0x0U << ATIM_SMCR_TS_Pos)
#define    FL_ATIM_TRGI_ITR1                                      (0x1U << ATIM_SMCR_TS_Pos)
#define    FL_ATIM_TRGI_ITR2                                      (0x2U << ATIM_SMCR_TS_Pos)
#define    FL_ATIM_TRGI_ITR3                                      (0x3U << ATIM_SMCR_TS_Pos)
#define    FL_ATIM_TRGI_TI1F_EDGE                                 (0x4U << ATIM_SMCR_TS_Pos)
#define    FL_ATIM_TRGI_TI1FP1                                    (0x5U << ATIM_SMCR_TS_Pos)
#define    FL_ATIM_TRGI_TI2FP2                                    (0x6U << ATIM_SMCR_TS_Pos)
#define    FL_ATIM_TRGI_ETRF                                      (0x7U << ATIM_SMCR_TS_Pos)


#define    FL_ATIM_SLAVE_MODE_PROHIBITED                          (0x0U << ATIM_SMCR_SMS_Pos)
#define    FL_ATIM_SLAVE_MODE_ENCODER_X2_TI1                      (0x1U << ATIM_SMCR_SMS_Pos)
#define    FL_ATIM_SLAVE_MODE_ENCODER_X2_TI2                      (0x2U << ATIM_SMCR_SMS_Pos)
#define    FL_ATIM_SLAVE_MODE_ENCODER_X4_TI1TI2                   (0x3U << ATIM_SMCR_SMS_Pos)
#define    FL_ATIM_SLAVE_MODE_TRGI_RISE_RST                       (0x4U << ATIM_SMCR_SMS_Pos)
#define    FL_ATIM_SLAVE_MODE_TRGI_HIGH_RUN                       (0x5U << ATIM_SMCR_SMS_Pos)
#define    FL_ATIM_SLAVE_MODE_TRGI_RISE_RUN                       (0x6U << ATIM_SMCR_SMS_Pos)
#define    FL_ATIM_SLAVE_MODE_TRGI_CLK                            (0x7U << ATIM_SMCR_SMS_Pos)


#define    FL_ATIM_DMA_BURST_LENGTH_1                             (0x0U << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_2                             (0x1U << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_3                             (0x2U << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_4                             (0x3U << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_5                             (0x4U << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_6                             (0x5U << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_7                             (0x6U << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_8                             (0x7U << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_9                             (0x8U << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_10                            (0x9U << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_11                            (0xaU << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_12                            (0xbU << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_13                            (0xcU << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_14                            (0xdU << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_15                            (0xeU << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_16                            (0xfU << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_17                            (0x10U << ATIM_DCR_DBL_Pos)
#define    FL_ATIM_DMA_BURST_LENGTH_18                            (0x11U << ATIM_DCR_DBL_Pos)


#define    FL_ATIM_DMA_BURST_ADDR_CR1                             (0x0U << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_CR2                             (0x1U << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_SMCR                            (0x2U << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_DIER                            (0x3U << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_SR                              (0x4U << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_EGR                             (0x5U << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_CCMR1                           (0x6U << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_CCMR2                           (0x7U << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_CCER                            (0x8U << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_CNT                             (0x9U << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_PSC                             (0xaU << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_ARR                             (0xbU << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_RCR                             (0xcU << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_CCR1                            (0xdU << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_CCR2                            (0xeU << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_CCR3                            (0xfU << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_CCR4                            (0x10U << ATIM_DCR_DBA_Pos)
#define    FL_ATIM_DMA_BURST_ADDR_BDTR                            (0x11U << ATIM_DCR_DBA_Pos)


#define    FL_ATIM_OC_MODE_FROZEN                                 (0x0U << ATIM_CCMR_OCM_Pos)
#define    FL_ATIM_OC_MODE_ACTIVE                                 (0x1U << ATIM_CCMR_OCM_Pos)
#define    FL_ATIM_OC_MODE_INACTIVE                               (0x2U << ATIM_CCMR_OCM_Pos)
#define    FL_ATIM_OC_MODE_TOGGLE                                 (0x3U << ATIM_CCMR_OCM_Pos)
#define    FL_ATIM_OC_MODE_FORCED_INACTIVE                        (0x4U << ATIM_CCMR_OCM_Pos)
#define    FL_ATIM_OC_MODE_FORCED_ACTIVE                          (0x5U << ATIM_CCMR_OCM_Pos)
#define    FL_ATIM_OC_MODE_PWM1                                   (0x6U << ATIM_CCMR_OCM_Pos)
#define    FL_ATIM_OC_MODE_PWM2                                   (0x7U << ATIM_CCMR_OCM_Pos)


#define    FL_ATIM_IC_FILTER_DIV1                                 (0x0U << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV1_N2                              (0x1U << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV1_N4                              (0x2U << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV1_N8                              (0x3U << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV2_N6                              (0x4U << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV2_N8                              (0x5U << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV4_N6                              (0x6U << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV4_N8                              (0x7U << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV8_N6                              (0x8U << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV8_N8                              (0x9U << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV16_N5                             (0xaU << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV16_N6                             (0xbU << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV16_N8                             (0xcU << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV32_N5                             (0xdU << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV32_N6                             (0xeU << ATIM_CCMR_ICF_Pos)
#define    FL_ATIM_IC_FILTER_DIV32_N8                             (0xfU << ATIM_CCMR_ICF_Pos)


#define    FL_ATIM_IC_PSC_DIV1                                    (0x0U << ATIM_CCMR_ICPSC_Pos)
#define    FL_ATIM_IC_PSC_DIV2                                    (0x1U << ATIM_CCMR_ICPSC_Pos)
#define    FL_ATIM_IC_PSC_DIV4                                    (0x2U << ATIM_CCMR_ICPSC_Pos)
#define    FL_ATIM_IC_PSC_DIV8                                    (0x3U << ATIM_CCMR_ICPSC_Pos)


#define    FL_ATIM_CHANNEL_MODE_OUTPUT                            (0x0U << ATIM_CCMR_CCS_Pos)
#define    FL_ATIM_CHANNEL_MODE_INPUT_NORMAL                      (0x1U << ATIM_CCMR_CCS_Pos)
#define    FL_ATIM_CHANNEL_MODE_INPUT_CROSSOVER                   (0x2U << ATIM_CCMR_CCS_Pos)
#define    FL_ATIM_CHANNEL_MODE_INPUT_TRC                         (0x3U << ATIM_CCMR_CCS_Pos)


#define    FL_ATIM_OCN_POLARITY_NORMAL                            (0x0U << ATIM_CCER_CCNP_Pos)
#define    FL_ATIM_OCN_POLARITY_INVERT                            (0x1U << ATIM_CCER_CCNP_Pos)


#define    FL_ATIM_OC_POLARITY_NORMAL                             (0x0U << ATIM_CCER_CCOP_Pos)
#define    FL_ATIM_OC_POLARITY_INVERT                             (0x1U << ATIM_CCER_CCOP_Pos)


#define    FL_ATIM_IC_POLARITY_NORMAL                             (0x0U << ATIM_CCER_CCIP_Pos)
#define    FL_ATIM_IC_POLARITY_INVERT                             (0x1U << ATIM_CCER_CCIP_Pos)


#define    FL_ATIM_BREAK_POLARITY_LOW                             (0x0U << ATIM_BDTR_BKP_Pos)
#define    FL_ATIM_BREAK_POLARITY_HIGH                            (0x1U << ATIM_BDTR_BKP_Pos)


#define    FL_ATIM_OSSR_DISABLE                                   (0x0U << ATIM_BDTR_OSSR_Pos)
#define    FL_ATIM_OSSR_ENABLE                                    (0x1U << ATIM_BDTR_OSSR_Pos)


#define    FL_ATIM_OSSI_DISABLE                                   (0x0U << ATIM_BDTR_OSSI_Pos)
#define    FL_ATIM_OSSI_ENABLE                                    (0x1U << ATIM_BDTR_OSSI_Pos)


#define    FL_ATIM_LOCK_LEVEL_OFF                                 (0x0U << ATIM_BDTR_LOCK_Pos)
#define    FL_ATIM_LOCK_LEVEL_1                                   (0x1U << ATIM_BDTR_LOCK_Pos)
#define    FL_ATIM_LOCK_LEVEL_2                                   (0x2U << ATIM_BDTR_LOCK_Pos)
#define    FL_ATIM_LOCK_LEVEL_3                                   (0x3U << ATIM_BDTR_LOCK_Pos)


#define    FL_ATIM_BREAK1_GATE_LOW                                (0x0U << ATIM_BKCR_BRK1GATE_Pos)
#define    FL_ATIM_BREAK1_GATE_AUTO                               (0x1U << ATIM_BKCR_BRK1GATE_Pos)


#define    FL_ATIM_BREAK2_GATE_LOW                                (0x0U << ATIM_BKCR_BRK2GATE_Pos)
#define    FL_ATIM_BREAK2_GATE_AUTO                               (0x1U << ATIM_BKCR_BRK2GATE_Pos)


#define    FL_ATIM_BREAK_FILTER_DIV1                              (0x0U << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV1_N2                           (0x1U << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV1_N4                           (0x2U << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV1_N8                           (0x3U << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV2_N6                           (0x4U << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV2_N8                           (0x5U << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV4_N6                           (0x6U << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV4_N8                           (0x7U << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV8_N6                           (0x8U << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV8_N8                           (0x9U << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV16_N5                          (0xaU << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV16_N6                          (0xbU << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV16_N8                          (0xcU << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV32_N5                          (0xdU << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV32_N6                          (0xeU << ATIM_BKCR_BRKF_Pos)
#define    FL_ATIM_BREAK_FILTER_DIV32_N8                          (0xfU << ATIM_BKCR_BRKF_Pos)


#define    FL_ATIM_BREAK_COMBINATION_OR                           (0x0U << ATIM_BKCR_BRKCOMB_Pos)
#define    FL_ATIM_BREAK_COMBINATION_AND                          (0x1U << ATIM_BKCR_BRKCOMB_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup ATIM_FL_Exported_Functions ATIM Exported Functions
  * @{
  */

/**
  * @brief    设置时钟分频因子
  * @rmtoll   CR1    CKD    FL_ATIM_SetClockDivision
  * @param    TIMx TIM instance
  * @param    div This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CLK_DIVISION_DIV1
  *           @arg @ref FL_ATIM_CLK_DIVISION_DIV2
  *           @arg @ref FL_ATIM_CLK_DIVISION_DIV4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetClockDivision(ATIM_Type *TIMx, uint32_t div)
{
    MODIFY_REG(TIMx->CR1, ATIM_CR1_CKD_Msk, div);
}

/**
  * @brief    读取时钟分频因子
  * @rmtoll   CR1    CKD    FL_ATIM_GetClockDivision
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_CLK_DIVISION_DIV1
  *           @arg @ref FL_ATIM_CLK_DIVISION_DIV2
  *           @arg @ref FL_ATIM_CLK_DIVISION_DIV4
  */
__STATIC_INLINE uint32_t FL_ATIM_GetClockDivision(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, ATIM_CR1_CKD_Msk));
}

/**
  * @brief    自动重装载使能
  * @rmtoll   CR1    ARPE    FL_ATIM_EnableARRPreload
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableARRPreload(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->CR1, ATIM_CR1_ARPE_Msk);
}

/**
  * @brief    获取自动重装载使能状态
  * @rmtoll   CR1    ARPE    FL_ATIM_IsEnabledARRPreload
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledARRPreload(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, ATIM_CR1_ARPE_Msk) == ATIM_CR1_ARPE_Msk);
}

/**
  * @brief    自动重装载禁用
  * @rmtoll   CR1    ARPE    FL_ATIM_DisableARRPreload
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableARRPreload(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->CR1, ATIM_CR1_ARPE_Msk);
}

/**
  * @brief    计数器对齐模式设置
  * @rmtoll   CR1    CMS    FL_ATIM_SetCounterAlignedMode
  * @param    TIMx TIM instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_COUNTER_ALIGNED_EDGE
  *           @arg @ref FL_ATIM_COUNTER_ALIGNED_CENTER_DOWN
  *           @arg @ref FL_ATIM_COUNTER_ALIGNED_CENTER_UP
  *           @arg @ref FL_ATIM_COUNTER_ALIGNED_CENTER_UP_DOWN
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetCounterAlignedMode(ATIM_Type *TIMx, uint32_t mode)
{
    MODIFY_REG(TIMx->CR1, ATIM_CR1_CMS_Msk, mode);
}

/**
  * @brief    读取计数器对齐模式
  * @rmtoll   CR1    CMS    FL_ATIM_GetCounterAlignedMode
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_COUNTER_ALIGNED_EDGE
  *           @arg @ref FL_ATIM_COUNTER_ALIGNED_CENTER_DOWN
  *           @arg @ref FL_ATIM_COUNTER_ALIGNED_CENTER_UP
  *           @arg @ref FL_ATIM_COUNTER_ALIGNED_CENTER_UP_DOWN
  */
__STATIC_INLINE uint32_t FL_ATIM_GetCounterAlignedMode(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, ATIM_CR1_CMS_Msk));
}

/**
  * @brief    设置记数方向
  * @rmtoll   CR1    DIR    FL_ATIM_SetCounterDirection
  * @param    TIMx TIM instance
  * @param    dir This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_COUNTER_DIR_UP
  *           @arg @ref FL_ATIM_COUNTER_DIR_DOWN
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetCounterDirection(ATIM_Type *TIMx, uint32_t dir)
{
    MODIFY_REG(TIMx->CR1, ATIM_CR1_DIR_Msk, dir);
}

/**
  * @brief    读取记数方向
  * @rmtoll   CR1    DIR    FL_ATIM_GetCounterDirection
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_COUNTER_DIR_UP
  *           @arg @ref FL_ATIM_COUNTER_DIR_DOWN
  */
__STATIC_INLINE uint32_t FL_ATIM_GetCounterDirection(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, ATIM_CR1_DIR_Msk));
}

/**
  * @brief    设置单脉冲输出模式
  * @rmtoll   CR1    OPM    FL_ATIM_SetOnePulseMode
  * @param    TIMx TIM instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_ONE_PULSE_MODE_CONTINUOUS
  *           @arg @ref FL_ATIM_ONE_PULSE_MODE_SINGLE
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetOnePulseMode(ATIM_Type *TIMx, uint32_t mode)
{
    MODIFY_REG(TIMx->CR1, ATIM_CR1_OPM_Msk, mode);
}

/**
  * @brief    读取单脉冲输出的模式
  * @rmtoll   CR1    OPM    FL_ATIM_GetOnePulseMode
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_ONE_PULSE_MODE_CONTINUOUS
  *           @arg @ref FL_ATIM_ONE_PULSE_MODE_SINGLE
  */
__STATIC_INLINE uint32_t FL_ATIM_GetOnePulseMode(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, ATIM_CR1_OPM_Msk));
}

/**
  * @brief    设置更新请求源
  * @rmtoll   CR1    URS    FL_ATIM_SetUpdateSource
  * @param    TIMx TIM instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_UPDATE_SOURCE_REGULAR
  *           @arg @ref FL_ATIM_UPDATE_SOURCE_COUNTER
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetUpdateSource(ATIM_Type *TIMx, uint32_t source)
{
    MODIFY_REG(TIMx->CR1, ATIM_CR1_URS_Msk, source);
}

/**
  * @brief    读取更新请求源
  * @rmtoll   CR1    URS    FL_ATIM_GetUpdateSource
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_UPDATE_SOURCE_REGULAR
  *           @arg @ref FL_ATIM_UPDATE_SOURCE_COUNTER
  */
__STATIC_INLINE uint32_t FL_ATIM_GetUpdateSource(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, ATIM_CR1_URS_Msk));
}

/**
  * @brief    使能更新事件
  * @rmtoll   CR1    UDIS    FL_ATIM_EnableUpdateEvent
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableUpdateEvent(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->CR1, ATIM_CR1_UDIS_Msk);
}

/**
  * @brief    读取更新事件状态
  * @rmtoll   CR1    UDIS    FL_ATIM_IsEnabledUpdateEvent
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledUpdateEvent(ATIM_Type *TIMx)
{
    return (uint32_t)!(READ_BIT(TIMx->CR1, ATIM_CR1_UDIS_Msk) == ATIM_CR1_UDIS_Msk);
}

/**
  * @brief    禁用更新事件
  * @rmtoll   CR1    UDIS    FL_ATIM_DisableUpdateEvent
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableUpdateEvent(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->CR1, ATIM_CR1_UDIS_Msk);
}

/**
  * @brief    计数器使能
  * @rmtoll   CR1    CEN    FL_ATIM_Enable
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_Enable(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->CR1, ATIM_CR1_CEN_Msk);
}

/**
  * @brief    读取计数器使能状态
  * @rmtoll   CR1    CEN    FL_ATIM_IsEnabled
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabled(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, ATIM_CR1_CEN_Msk) == ATIM_CR1_CEN_Msk);
}

/**
  * @brief    计数器关闭
  * @rmtoll   CR1    CEN    FL_ATIM_Disable
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_Disable(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->CR1, ATIM_CR1_CEN_Msk);
}

/**
  * @brief    设置OCN的输出空闲状态
  * @note
  * @rmtoll   CR2    OISN    FL_ATIM_OC_SetReverseChannelIdleState
  * @param    TIMx TIM instance
  * @param    OCNIdleState This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_OCN_IDLE_STATE_LOW
  *           @arg @ref FL_ATIM_OCN_IDLE_STATE_HIGH
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_SetReverseChannelIdleState(ATIM_Type *TIMx, uint32_t OCNIdleState, uint32_t channel)
{
    MODIFY_REG(TIMx->CR2, ATIM_CR2_OISN_Msk << (channel * 2), OCNIdleState << (channel * 2));
}

/**
  * @brief    读取OCN的输出空闲状态
  * @note
  * @rmtoll   CR2    OISN    FL_ATIM_OC_GetReverseChannelIdleState
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_OCN_IDLE_STATE_LOW
  *           @arg @ref FL_ATIM_OCN_IDLE_STATE_HIGH
  */
__STATIC_INLINE uint32_t FL_ATIM_OC_GetReverseChannelIdleState(ATIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->CR2, (ATIM_CR2_OISN_Msk << (channel * 2))));
}

/**
  * @brief    设置OC的输出空闲状态
  * @note
  * @rmtoll   CR2    OIS    FL_ATIM_OC_SetChannelIdleState
  * @param    TIMx TIM instance
  * @param    OCIdleState This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_OC_IDLE_STATE_LOW
  *           @arg @ref FL_ATIM_OC_IDLE_STATE_HIGH
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_SetChannelIdleState(ATIM_Type *TIMx, uint32_t OCIdleState, uint32_t channel)
{
    MODIFY_REG(TIMx->CR2, (ATIM_CR2_OIS_Msk << (channel * 2)), OCIdleState << (channel * 2));
}

/**
  * @brief    读取OC的输出空闲状态
  * @note
  * @rmtoll   CR2    OIS    FL_ATIM_OC_GetChannelIdleState
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_OC_IDLE_STATE_LOW
  *           @arg @ref FL_ATIM_OC_IDLE_STATE_HIGH
  */
__STATIC_INLINE uint32_t FL_ATIM_OC_GetChannelIdleState(ATIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->CR2, (ATIM_CR2_OIS_Msk << (channel * 2))));
}

/**
  * @brief    通道1输入源选择
  * @rmtoll   CR2    TI1S    FL_ATIM_IC_EnableXORCombination
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_IC_EnableXORCombination(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->CR2, ATIM_CR2_TI1S_Msk);
}

/**
  * @brief    读取通道1输入源
  * @rmtoll   CR2    TI1S    FL_ATIM_IC_IsEnabledXORCombination
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IC_IsEnabledXORCombination(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR2, ATIM_CR2_TI1S_Msk) == ATIM_CR2_TI1S_Msk);
}

/**
  * @brief    通道1输入源禁用XOR组合
  * @rmtoll   CR2    TI1S    FL_ATIM_IC_DisableXORCombination
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_IC_DisableXORCombination(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->CR2, ATIM_CR2_TI1S_Msk);
}

/**
  * @brief    设置同步触发信号源
  * @rmtoll   CR2    MMS    FL_ATIM_SetTriggerOutput
  * @param    TIMx TIM instance
  * @param    triggerOutput This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_TRGO_RESET
  *           @arg @ref FL_ATIM_TRGO_ENABLE
  *           @arg @ref FL_ATIM_TRGO_UPDATE
  *           @arg @ref FL_ATIM_TRGO_CC1IF
  *           @arg @ref FL_ATIM_TRGO_OC1REF
  *           @arg @ref FL_ATIM_TRGO_OC2REF
  *           @arg @ref FL_ATIM_TRGO_OC3REF
  *           @arg @ref FL_ATIM_TRGO_OC4REF
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetTriggerOutput(ATIM_Type *TIMx, uint32_t triggerOutput)
{
    MODIFY_REG(TIMx->CR2, ATIM_CR2_MMS_Msk, triggerOutput);
}

/**
  * @brief    读取同步触发源
  * @rmtoll   CR2    MMS    FL_ATIM_GetTriggerOutput
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_TRGO_RESET
  *           @arg @ref FL_ATIM_TRGO_ENABLE
  *           @arg @ref FL_ATIM_TRGO_UPDATE
  *           @arg @ref FL_ATIM_TRGO_CC1IF
  *           @arg @ref FL_ATIM_TRGO_OC1REF
  *           @arg @ref FL_ATIM_TRGO_OC2REF
  *           @arg @ref FL_ATIM_TRGO_OC3REF
  *           @arg @ref FL_ATIM_TRGO_OC4REF
  */
__STATIC_INLINE uint32_t FL_ATIM_GetTriggerOutput(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR2, ATIM_CR2_MMS_Msk));
}

/**
  * @brief    设置DMA请求触发
  * @rmtoll   CR2    CCDS    FL_ATIM_CC_SetDMAReqTrigger
  * @param    TIMx TIM instance
  * @param    trigger This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_DMA_REQ_CC
  *           @arg @ref FL_ATIM_DMA_REQ_UPDATE
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_CC_SetDMAReqTrigger(ATIM_Type *TIMx, uint32_t trigger)
{
    MODIFY_REG(TIMx->CR2, ATIM_CR2_CCDS_Msk, trigger);
}

/**
  * @brief    读取DMA请求触发
  * @rmtoll   CR2    CCDS    FL_ATIM_CC_GetDMAReqTrigger
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_DMA_REQ_CC
  *           @arg @ref FL_ATIM_DMA_REQ_UPDATE
  */
__STATIC_INLINE uint32_t FL_ATIM_CC_GetDMAReqTrigger(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR2, ATIM_CR2_CCDS_Msk));
}

/**
  * @brief    设置捕捉比较寄存器更新选择
  * @rmtoll   CR2    CCUS    FL_ATIM_CC_SetUpdateSource
  * @param    TIMx TIM instance
  * @param    updateSource This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_UPDATE_SOURCE_COMG_ONLY
  *           @arg @ref FL_ATIM_UPDATE_SOURCE_COMG_AND_TRGI?
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_CC_SetUpdateSource(ATIM_Type *TIMx, uint32_t updateSource)
{
    MODIFY_REG(TIMx->CR2, ATIM_CR2_CCUS_Msk, updateSource);
}

/**
  * @brief    读取捕捉比较寄存器更新源
  * @rmtoll   CR2    CCUS    FL_ATIM_CC_GetUpdateSource
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_UPDATE_SOURCE_COMG_ONLY
  *           @arg @ref FL_ATIM_UPDATE_SOURCE_COMG_AND_TRGI?
  */
__STATIC_INLINE uint32_t FL_ATIM_CC_GetUpdateSource(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR2, ATIM_CR2_CCUS_Msk));
}

/**
  * @brief    捕捉比较预装载使能
  * @rmtoll   CR2    CCPC    FL_ATIM_CC_EnablePreload
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_CC_EnablePreload(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->CR2, ATIM_CR2_CCPC_Msk);
}

/**
  * @brief    读取捕捉比较预装载使能状态
  * @rmtoll   CR2    CCPC    FL_ATIM_CC_IsEnabledPreload
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_CC_IsEnabledPreload(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR2, ATIM_CR2_CCPC_Msk) == ATIM_CR2_CCPC_Msk);
}

/**
  * @brief    捕捉比较预装载失能
  * @rmtoll   CR2    CCPC    FL_ATIM_CC_DisablePreload
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_CC_DisablePreload(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->CR2, ATIM_CR2_CCPC_Msk);
}

/**
  * @brief    设置外部触发信号极性
  * @rmtoll   SMCR    ETP    FL_ATIM_SetETRPolarity
  * @param    TIMx TIM instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_ETR_POLARITY_NORMAL
  *           @arg @ref FL_ATIM_ETR_POLARITY_INVERT
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetETRPolarity(ATIM_Type *TIMx, uint32_t polarity)
{
    MODIFY_REG(TIMx->SMCR, ATIM_SMCR_ETP_Msk, polarity);
}

/**
  * @brief    读取外部触发信号极性
  * @rmtoll   SMCR    ETP    FL_ATIM_GetETRPolarity
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_ETR_POLARITY_NORMAL
  *           @arg @ref FL_ATIM_ETR_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_ATIM_GetETRPolarity(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, ATIM_SMCR_ETP_Msk));
}

/**
  * @brief    外部时钟使能
  * @rmtoll   SMCR    ECE    FL_ATIM_EnableExternalClock
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableExternalClock(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->SMCR, ATIM_SMCR_ECE_Msk);
}

/**
  * @brief    读取外部时钟使能状态
  * @rmtoll   SMCR    ECE    FL_ATIM_IsEnabledExternalClock
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledExternalClock(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, ATIM_SMCR_ECE_Msk) == ATIM_SMCR_ECE_Msk);
}

/**
  * @brief    外部时钟禁用
  * @rmtoll   SMCR    ECE    FL_ATIM_DisableExternalClock
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableExternalClock(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->SMCR, ATIM_SMCR_ECE_Msk);
}

/**
  * @brief    设置外部触发信号预分频
  * @rmtoll   SMCR    ETPS    FL_ATIM_SetETRPrescaler
  * @param    TIMx TIM instance
  * @param    psc This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_ETR_PSC_DIV1
  *           @arg @ref FL_ATIM_ETR_PSC_DIV2
  *           @arg @ref FL_ATIM_ETR_PSC_DIV4
  *           @arg @ref FL_ATIM_ETR_PSC_DIV8
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetETRPrescaler(ATIM_Type *TIMx, uint32_t psc)
{
    MODIFY_REG(TIMx->SMCR, ATIM_SMCR_ETPS_Msk, psc);
}

/**
  * @brief    读取外部触发信号预分频
  * @rmtoll   SMCR    ETPS    FL_ATIM_GetETRPrescaler
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_ETR_PSC_DIV1
  *           @arg @ref FL_ATIM_ETR_PSC_DIV2
  *           @arg @ref FL_ATIM_ETR_PSC_DIV4
  *           @arg @ref FL_ATIM_ETR_PSC_DIV8
  */
__STATIC_INLINE uint32_t FL_ATIM_GetETRPrescaler(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, ATIM_SMCR_ETPS_Msk));
}

/**
  * @brief    设置外部触发信号滤波时钟和长度
  * @rmtoll   SMCR    ETF    FL_ATIM_SetETRFilter
  * @param    TIMx TIM instance
  * @param    filter This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV1
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV1_N2
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV1_N4
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV1_N8
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV2_N6
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV2_N8
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV4_N6
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV4_N8
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV8_N6
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV8_N8
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV16_N5
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV16_N6
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV16_N8
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV32_N5
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV32_N6
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV32_N8
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetETRFilter(ATIM_Type *TIMx, uint32_t filter)
{
    MODIFY_REG(TIMx->SMCR, ATIM_SMCR_ETF_Msk, filter);
}

/**
  * @brief    读取外部触发信号滤波时钟和长度
  * @rmtoll   SMCR    ETF    FL_ATIM_GetETRFilter
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV1
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV1_N2
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV1_N4
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV1_N8
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV2_N6
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV2_N8
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV4_N6
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV4_N8
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV8_N6
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV8_N8
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV16_N5
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV16_N6
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV16_N8
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV32_N5
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV32_N6
  *           @arg @ref FL_ATIM_ETR_FILTER_DIV32_N8
  */
__STATIC_INLINE uint32_t FL_ATIM_GetETRFilter(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, ATIM_SMCR_ETF_Msk));
}

/**
  * @brief    主/从模式使能
  * @rmtoll   SMCR    MSM    FL_ATIM_EnableMasterSlaveMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableMasterSlaveMode(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->SMCR, ATIM_SMCR_MSM_Msk);
}

/**
  * @brief    读取主/从模式使能状态
  * @rmtoll   SMCR    MSM    FL_ATIM_IsEnabledMasterSlaveMode
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledMasterSlaveMode(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, ATIM_SMCR_MSM_Msk) == ATIM_SMCR_MSM_Msk);
}

/**
  * @brief    定时器主/从模式禁用
  * @rmtoll   SMCR    MSM    FL_ATIM_DisableMasterSlaveMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableMasterSlaveMode(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->SMCR, ATIM_SMCR_MSM_Msk);
}

/**
  * @brief    设置同步计数器触发源
  * @rmtoll   SMCR    TS    FL_ATIM_SetTriggerInput
  * @param    TIMx TIM instance
  * @param    triggerInput This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_TRGI_ITR0
  *           @arg @ref FL_ATIM_TRGI_ITR1
  *           @arg @ref FL_ATIM_TRGI_ITR2
  *           @arg @ref FL_ATIM_TRGI_ITR3
  *           @arg @ref FL_ATIM_TRGI_TI1F_EDGE
  *           @arg @ref FL_ATIM_TRGI_TI1FP1
  *           @arg @ref FL_ATIM_TRGI_TI2FP2
  *           @arg @ref FL_ATIM_TRGI_ETRF
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetTriggerInput(ATIM_Type *TIMx, uint32_t triggerInput)
{
    MODIFY_REG(TIMx->SMCR, ATIM_SMCR_TS_Msk, triggerInput);
}

/**
  * @brief    读取同步计数器的触发源
  * @rmtoll   SMCR    TS    FL_ATIM_GetTriggerInput
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_TRGI_ITR0
  *           @arg @ref FL_ATIM_TRGI_ITR1
  *           @arg @ref FL_ATIM_TRGI_ITR2
  *           @arg @ref FL_ATIM_TRGI_ITR3
  *           @arg @ref FL_ATIM_TRGI_TI1F_EDGE
  *           @arg @ref FL_ATIM_TRGI_TI1FP1
  *           @arg @ref FL_ATIM_TRGI_TI2FP2
  *           @arg @ref FL_ATIM_TRGI_ETRF
  */
__STATIC_INLINE uint32_t FL_ATIM_GetTriggerInput(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, ATIM_SMCR_TS_Msk));
}

/**
  * @brief    从机模式设置
  * @rmtoll   SMCR    SMS    FL_ATIM_SetSlaveMode
  * @param    TIMx TIM instance
  * @param    encoderMode This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_SLAVE_MODE_PROHIBITED
  *           @arg @ref FL_ATIM_SLAVE_MODE_ENCODER_X2_TI1
  *           @arg @ref FL_ATIM_SLAVE_MODE_ENCODER_X2_TI2
  *           @arg @ref FL_ATIM_SLAVE_MODE_ENCODER_X4_TI1TI2
   *          @arg @ref FL_ATIM_SLAVE_MODE_TRGI_RISE_RST
  *           @arg @ref FL_ATIM_SLAVE_MODE_TRGI_HIGH_RUN
  *           @arg @ref FL_ATIM_SLAVE_MODE_TRGI_RISE_RUN
  *           @arg @ref FL_ATIM_SLAVE_MODE_TRGI_CLK
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetSlaveMode(ATIM_Type *TIMx, uint32_t encoderMode)
{
    MODIFY_REG(TIMx->SMCR, ATIM_SMCR_SMS_Msk, encoderMode);
}

/**
  * @brief    读取从机模式
  * @rmtoll   SMCR    SMS    FL_ATIM_GetSlaveMode
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_SLAVE_MODE_PROHIBITED
  *           @arg @ref FL_ATIM_SLAVE_MODE_ENCODER_X2_TI1
  *           @arg @ref FL_ATIM_SLAVE_MODE_ENCODER_X2_TI2
  *           @arg @ref FL_ATIM_SLAVE_MODE_NCODER_X4_TI1TI2
  *           @arg @ref FL_ATIM_SLAVE_MODE_TRGI_RISE_RST
  *           @arg @ref FL_ATIM_SLAVE_MODE_TRGI_HIGH_RUN
  *           @arg @ref FL_ATIM_SLAVE_MODE_TRGI_RISE_RUN
  *           @arg @ref FL_ATIM_SLAVE_MODE_TRGI_CLK
  */
__STATIC_INLINE uint32_t FL_ATIM_GetSlaveMode(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, ATIM_SMCR_SMS_Msk));
}

/**
  * @brief    通道1的模式配置为Burst模式
  * @rmtoll   DIER    CC1BURSTEN    FL_ATIM_EnableCC1DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableCC1DMABurstMode(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, ATIM_DIER_CC1BURSTEN_Msk);
}

/**
  * @brief    读取通道1的模式配置
  * @rmtoll   DIER    CC1BURSTEN    FL_ATIM_IsEnabledCC1DMABurstMode
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledCC1DMABurstMode(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, ATIM_DIER_CC1BURSTEN_Msk) == ATIM_DIER_CC1BURSTEN_Msk);
}

/**
  * @brief    通道1的Burst模式禁用
  * @rmtoll   DIER    CC1BURSTEN    FL_ATIM_DisableCC1DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableCC1DMABurstMode(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, ATIM_DIER_CC1BURSTEN_Msk);
}

/**
  * @brief    通道2的模式配置为Burst模式
  * @rmtoll   DIER    CC2BURSTEN    FL_ATIM_EnableCC2DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableCC2DMABurstMode(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, ATIM_DIER_CC2BURSTEN_Msk);
}

/**
  * @brief    读取通道2的模式配置
  * @rmtoll   DIER    CC2BURSTEN    FL_ATIM_IsEnabledCC2DMABurstMode
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledCC2DMABurstMode(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, ATIM_DIER_CC2BURSTEN_Msk) == ATIM_DIER_CC2BURSTEN_Msk);
}

/**
  * @brief    通道2的Burst模式禁用
  * @rmtoll   DIER    CC2BURSTEN    FL_ATIM_DisableCC2DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableCC2DMABurstMode(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, ATIM_DIER_CC2BURSTEN_Msk);
}

/**
  * @brief    通道3的模式配置为Burst模式
  * @rmtoll   DIER    CC3BURSTEN    FL_ATIM_EnableCC3DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableCC3DMABurstMode(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, ATIM_DIER_CC3BURSTEN_Msk);
}

/**
  * @brief    读取通道3的模式配置
  * @rmtoll   DIER    CC3BURSTEN    FL_ATIM_IsEnabledCC3DMABurstMode
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledCC3DMABurstMode(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, ATIM_DIER_CC3BURSTEN_Msk) == ATIM_DIER_CC3BURSTEN_Msk);
}

/**
  * @brief    通道3的Burst模式禁用
  * @rmtoll   DIER    CC3BURSTEN    FL_ATIM_DisableCC3DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableCC3DMABurstMode(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, ATIM_DIER_CC3BURSTEN_Msk);
}

/**
  * @brief    通道4的模式配置为Burst模式
  * @rmtoll   DIER    CC4BURSTEN    FL_ATIM_EnableCC4DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableCC4DMABurstMode(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, ATIM_DIER_CC4BURSTEN_Msk);
}

/**
  * @brief    读取通道4的模式配置
  * @rmtoll   DIER    CC4BURSTEN    FL_ATIM_IsEnabledCC4DMABurstMode
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledCC4DMABurstMode(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, ATIM_DIER_CC4BURSTEN_Msk) == ATIM_DIER_CC4BURSTEN_Msk);
}

/**
  * @brief    通道4的Burst模式禁用
  * @rmtoll   DIER    CC4BURSTEN    FL_ATIM_DisableCC4DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableCC4DMABurstMode(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, ATIM_DIER_CC4BURSTEN_Msk);
}

/**
  * @brief    外部触发DMA请求使能
  * @rmtoll   DIER    TDE    FL_ATIM_EnableDMAReq_Trigger
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableDMAReq_Trigger(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, ATIM_DIER_TDE_Msk);
}

/**
  * @brief    读取外部触发DMA请求使能状态
  * @rmtoll   DIER    TDE    FL_ATIM_IsEnabledDMAReq_Trigger
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledDMAReq_Trigger(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, ATIM_DIER_TDE_Msk) == ATIM_DIER_TDE_Msk);
}

/**
  * @brief    外部触发DMA请求禁用
  * @rmtoll   DIER    TDE    FL_ATIM_DisableDMAReq_Trigger
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableDMAReq_Trigger(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, ATIM_DIER_TDE_Msk);
}

/**
  * @brief    COM事件DMA请求使能
  * @note
  * @rmtoll   DIER    COMDE    FL_ATIM_EnableDMAReq_COM
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableDMAReq_COM(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, ATIM_DIER_COMDE_Msk);
}

/**
  * @brief    读取COM事件DMA请求使能状态
  * @note
  * @rmtoll   DIER    COMDE    FL_ATIM_IsEnabledDMAReq_COM
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledDMAReq_COM(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, ATIM_DIER_COMDE_Msk) == ATIM_DIER_COMDE_Msk);
}

/**
  * @brief    COM事件DMA请求禁用
  * @note
  * @rmtoll   DIER    COMDE    FL_ATIM_DisableDMAReq_COM
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableDMAReq_COM(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, ATIM_DIER_COMDE_Msk);
}

/**
  * @brief    捕捉比较通道的DMA请求使能
  * @rmtoll   DIER    CCDE    FL_ATIM_EnableDMAReq_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableDMAReq_CC(ATIM_Type *TIMx, uint32_t channel)
{
    SET_BIT(TIMx->DIER, ATIM_DIER_CCDE_Msk << channel);
}

/**
  * @brief    读取捕捉比较通道的DMA请求使能
  * @rmtoll   DIER    CCDE    FL_ATIM_IsEnabledDMAReq_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledDMAReq_CC(ATIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, (ATIM_DIER_CCDE_Msk << channel)) == (ATIM_DIER_CCDE_Msk << channel));
}

/**
  * @brief    捕捉比较通道的DMA请求禁用
  * @rmtoll   DIER    CCDE    FL_ATIM_DisableDMAReq_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableDMAReq_CC(ATIM_Type *TIMx, uint32_t channel)
{
    CLEAR_BIT(TIMx->DIER, ATIM_DIER_CCDE_Msk << channel);
}

/**
  * @brief    更新事件DMA请求使能
  * @rmtoll   DIER    UDE    FL_ATIM_EnableDMAReq_Update
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableDMAReq_Update(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, ATIM_DIER_UDE_Msk);
}

/**
  * @brief    读取更新事件DMA请求使能状态
  * @rmtoll   DIER    UDE    FL_ATIM_IsEnabledDMAReq_Update
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledDMAReq_Update(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, ATIM_DIER_UDE_Msk) == ATIM_DIER_UDE_Msk);
}

/**
  * @brief    更新事件DMA请求禁用
  * @rmtoll   DIER    UDE    FL_ATIM_DisableDMAReq_Update
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableDMAReq_Update(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, ATIM_DIER_UDE_Msk);
}

/**
  * @brief    刹车事件中断使能
  * @note
  * @rmtoll   DIER    BIE    FL_ATIM_EnableIT_Break
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableIT_Break(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, ATIM_DIER_BIE_Msk);
}

/**
  * @brief    读取刹车事件中断使能状态
  * @note
  * @rmtoll   DIER    BIE    FL_ATIM_IsEnabledIT_Break
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledIT_Break(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, ATIM_DIER_BIE_Msk) == ATIM_DIER_BIE_Msk);
}

/**
  * @brief    刹车事件中断禁用
  * @note
  * @rmtoll   DIER    BIE    FL_ATIM_DisableIT_Break
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableIT_Break(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, ATIM_DIER_BIE_Msk);
}

/**
  * @brief    触发事件中断使能
  * @rmtoll   DIER    TIE    FL_ATIM_EnableIT_Trigger
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableIT_Trigger(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, ATIM_DIER_TIE_Msk);
}

/**
  * @brief    读取触发事件中断使能
  * @rmtoll   DIER    TIE    FL_ATIM_IsEnabledIT_Trigger
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledIT_Trigger(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, ATIM_DIER_TIE_Msk) == ATIM_DIER_TIE_Msk);
}

/**
  * @brief    触发事件中断禁用
  * @rmtoll   DIER    TIE    FL_ATIM_DisableIT_Trigger
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableIT_Trigger(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, ATIM_DIER_TIE_Msk);
}

/**
  * @brief    COM事件中断使能
  * @note
  * @rmtoll   DIER    COMIE    FL_ATIM_EnableIT_COM
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableIT_COM(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, ATIM_DIER_COMIE_Msk);
}

/**
  * @brief    读取COM事件中断使能状态
  * @note
  * @rmtoll   DIER    COMIE    FL_ATIM_IsEnabledIT_COM
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledIT_COM(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, ATIM_DIER_COMIE_Msk) == ATIM_DIER_COMIE_Msk);
}

/**
  * @brief    COM事件中断禁用
  * @note
  * @rmtoll   DIER    COMIE    FL_ATIM_DisableIT_COM
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableIT_COM(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, ATIM_DIER_COMIE_Msk);
}

/**
  * @brief    捕捉/比较通道中断使能
  * @rmtoll   DIER    CCIE    FL_ATIM_EnableIT_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableIT_CC(ATIM_Type *TIMx, uint32_t channel)
{
    SET_BIT(TIMx->DIER, ATIM_DIER_CCIE_Msk << channel);
}

/**
  * @brief    读取捕捉/比较通道中断使能状态
  * @rmtoll   DIER    CCIE    FL_ATIM_IsEnabledIT_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledIT_CC(ATIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, (ATIM_DIER_CCIE_Msk << channel)) == (ATIM_DIER_CCIE_Msk << channel));
}

/**
  * @brief    捕捉/比较通道中断禁用
  * @rmtoll   DIER    CCIE    FL_ATIM_DisableIT_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableIT_CC(ATIM_Type *TIMx, uint32_t channel)
{
    CLEAR_BIT(TIMx->DIER, ATIM_DIER_CCIE_Msk << channel);
}

/**
  * @brief    更新事件中断使能
  * @rmtoll   DIER    UIE    FL_ATIM_EnableIT_Update
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableIT_Update(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, ATIM_DIER_UIE_Msk);
}

/**
  * @brief    读取更新事件中断使能状态
  * @rmtoll   DIER    UIE    FL_ATIM_IsEnabledIT_Update
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledIT_Update(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, ATIM_DIER_UIE_Msk) == ATIM_DIER_UIE_Msk);
}

/**
  * @brief    更新事件中断禁用
  * @rmtoll   DIER    UIE    FL_ATIM_DisableIT_Update
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableIT_Update(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, ATIM_DIER_UIE_Msk);
}

/**
  * @brief    捕捉/比较通道的Overcapture中断标志
  * @rmtoll   ISR    CCOF    FL_ATIM_IsActiveFlag_CCOverflow
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsActiveFlag_CCOverflow(ATIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->ISR, (ATIM_ISR_CCOF_Msk << channel)) == (ATIM_ISR_CCOF_Msk << channel));
}

/**
  * @brief    清除Overcapture中断标志
  * @rmtoll   ISR    CCOF    FL_ATIM_ClearFlag_CCOverflow
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_ClearFlag_CCOverflow(ATIM_Type *TIMx, uint32_t channel)
{
    WRITE_REG(TIMx->ISR, (ATIM_ISR_CCOF_Msk << channel));
}

/**
  * @brief    读取刹车事件中断标志
  * @note
  * @rmtoll   ISR    BIF    FL_ATIM_IsActiveFlag_Break
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsActiveFlag_Break(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->ISR, ATIM_ISR_BIF_Msk) == (ATIM_ISR_BIF_Msk));
}

/**
  * @brief    清除刹车事件中断标志
  * @note
  * @rmtoll   ISR    BIF    FL_ATIM_ClearFlag_Break
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_ClearFlag_Break(ATIM_Type *TIMx)
{
    WRITE_REG(TIMx->ISR, ATIM_ISR_BIF_Msk);
}

/**
  * @brief    触发事件中断标志
  * @rmtoll   ISR    TIF    FL_ATIM_IsActiveFlag_Trigger
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsActiveFlag_Trigger(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->ISR, ATIM_ISR_TIF_Msk) == (ATIM_ISR_TIF_Msk));
}

/**
  * @brief    清除触发事件中断标志
  * @rmtoll   ISR    TIF    FL_ATIM_ClearFlag_Trigger
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_ClearFlag_Trigger(ATIM_Type *TIMx)
{
    WRITE_REG(TIMx->ISR, ATIM_ISR_TIF_Msk);
}

/**
  * @brief    读取COM事件中断标志
  * @note
  * @rmtoll   ISR    COMIF    FL_ATIM_IsActiveFlag_COM
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsActiveFlag_COM(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->ISR, ATIM_ISR_COMIF_Msk) == (ATIM_ISR_COMIF_Msk));
}

/**
  * @brief    清除COM事件中断标志
  * @note
  * @rmtoll   ISR    COMIF    FL_ATIM_ClearFlag_COM
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_ClearFlag_COM(ATIM_Type *TIMx)
{
    WRITE_REG(TIMx->ISR, ATIM_ISR_COMIF_Msk);
}

/**
  * @brief    读取捕捉/比较通道中断标志
  * @rmtoll   ISR    CCIF    FL_ATIM_IsActiveFlag_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsActiveFlag_CC(ATIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->ISR, (ATIM_ISR_CCIF_Msk << channel)) == (ATIM_ISR_CCIF_Msk << channel));
}

/**
  * @brief    清除捕捉/比较通道中断标志
  * @rmtoll   ISR    CCIF    FL_ATIM_ClearFlag_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_ClearFlag_CC(ATIM_Type *TIMx, uint32_t channel)
{
    WRITE_REG(TIMx->ISR, (ATIM_ISR_CCIF_Msk << channel));
}

/**
  * @brief    读取更新事件中断标志
  * @rmtoll   ISR    UIF    FL_ATIM_IsActiveFlag_Update
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsActiveFlag_Update(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->ISR, ATIM_ISR_UIF_Msk) == (ATIM_ISR_UIF_Msk));
}

/**
  * @brief    清除更新事件中断标志
  * @rmtoll   ISR    UIF    FL_ATIM_ClearFlag_Update
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_ClearFlag_Update(ATIM_Type *TIMx)
{
    WRITE_REG(TIMx->ISR, ATIM_ISR_UIF_Msk);
}

/**
  * @brief    软件刹车使能
  * @note
  * @rmtoll   EGR    BG    FL_ATIM_GenerateBreakEvent
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_GenerateBreakEvent(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->EGR, ATIM_EGR_BG_Msk);
}

/**
  * @brief    软件触发使能
  * @rmtoll   EGR    TG    FL_ATIM_GenerateTriggerEvent
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_GenerateTriggerEvent(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->EGR, ATIM_EGR_TG_Msk);
}

/**
  * @brief    软件COM事件使能
  * @note
  * @rmtoll   EGR    COMG    FL_ATIM_GenerateCOMEvent
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_GenerateCOMEvent(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->EGR, ATIM_EGR_COMG_Msk);
}

/**
  * @brief    捕捉/比较通道软件触发使能
  * @rmtoll   EGR    CCG    FL_ATIM_GenerateCCEvent
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_GenerateCCEvent(ATIM_Type *TIMx, uint32_t channel)
{
    SET_BIT(TIMx->EGR, ATIM_EGR_CCG_Msk << channel);
}

/**
  * @brief    软件更新事件使能
  * @rmtoll   EGR    UG    FL_ATIM_GenerateUpdateEvent
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_GenerateUpdateEvent(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->EGR, ATIM_EGR_UG_Msk);
}

/**
  * @brief    设置计数器值
  * @rmtoll   CNT        FL_ATIM_WriteCounter
  * @param    TIMx TIM instance
  * @param    counter
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_WriteCounter(ATIM_Type *TIMx, uint32_t counter)
{
    MODIFY_REG(TIMx->CNT, (0xffffU << 0U), (counter << 0U));
}

/**
  * @brief    读取计数器值
  * @rmtoll   CNT        FL_ATIM_ReadCounter
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_ATIM_ReadCounter(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CNT, 0xffffU) >> 0U);
}

/**
  * @brief    设置计数器时钟预分频值
  * @rmtoll   PSC        FL_ATIM_WritePrescaler
  * @param    TIMx TIM instance
  * @param    psc
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_WritePrescaler(ATIM_Type *TIMx, uint32_t psc)
{
    MODIFY_REG(TIMx->PSC, (0xffffU << 0U), (psc << 0U));
}

/**
  * @brief    读取计数器时钟预分频值
  * @rmtoll   PSC        FL_ATIM_ReadPrescaler
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_ATIM_ReadPrescaler(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->PSC, 0xffffU) >> 0U);
}

/**
  * @brief    设置计数溢出时的自动重载值
  * @rmtoll   ARR        FL_ATIM_WriteAutoReload
  * @param    TIMx TIM instance
  * @param    autoReload
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_WriteAutoReload(ATIM_Type *TIMx, uint32_t autoReload)
{
    MODIFY_REG(TIMx->ARR, (0xffffU << 0U), (autoReload << 0U));
}

/**
  * @brief    读取计数溢出时的自动重载值
  * @rmtoll   ARR        FL_ATIM_ReadAutoReload
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_ATIM_ReadAutoReload(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->ARR, 0xffffU) >> 0U);
}

/**
  * @brief    捕捉/比较通道1寄存器配置
  * @rmtoll   CCR1        FL_ATIM_WriteCompareCH1
  * @param    TIMx TIM instance
  * @param    compareValue
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_WriteCompareCH1(ATIM_Type *TIMx, uint32_t compareValue)
{
    MODIFY_REG(TIMx->CCR1, (0xffffU << 0U), (compareValue << 0U));
}

/**
  * @brief    读取捕捉/比较通道1寄存器值
  * @rmtoll   CCR1        FL_ATIM_ReadCompareCH1
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_ATIM_ReadCompareCH1(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CCR1, 0xffffU) >> 0U);
}

/**
  * @brief    捕捉/比较通道2寄存器配置
  * @rmtoll   CCR2        FL_ATIM_WriteCompareCH2
  * @param    TIMx TIM instance
  * @param    compareValue
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_WriteCompareCH2(ATIM_Type *TIMx, uint32_t compareValue)
{
    MODIFY_REG(TIMx->CCR2, (0xffffU << 0U), (compareValue << 0U));
}

/**
  * @brief    读取捕捉/比较通道2寄存器值
  * @rmtoll   CCR2        FL_ATIM_ReadCompareCH2
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_ATIM_ReadCompareCH2(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CCR2, 0xffffU) >> 0U);
}

/**
  * @brief    捕捉/比较通道3寄存器配置
  * @rmtoll   CCR3        FL_ATIM_WriteCompareCH3
  * @param    TIMx TIM instance
  * @param    compareValue
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_WriteCompareCH3(ATIM_Type *TIMx, uint32_t compareValue)
{
    MODIFY_REG(TIMx->CCR3, (0xffffU << 0U), (compareValue << 0U));
}

/**
  * @brief    读取捕捉/比较通道3寄存器值
  * @rmtoll   CCR3        FL_ATIM_ReadCompareCH3
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_ATIM_ReadCompareCH3(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CCR3, 0xffffU) >> 0U);
}

/**
  * @brief    捕捉/比较通道4寄存器配置
  * @rmtoll   CCR4        FL_ATIM_WriteCompareCH4
  * @param    TIMx TIM instance
  * @param    compareValue
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_WriteCompareCH4(ATIM_Type *TIMx, uint32_t compareValue)
{
    MODIFY_REG(TIMx->CCR4, (0xffffU << 0U), (compareValue << 0U));
}

/**
  * @brief    读取捕捉/比较通道4寄存器值
  * @rmtoll   CCR4        FL_ATIM_ReadCompareCH4
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_ATIM_ReadCompareCH4(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CCR4, 0xffffU) >> 0U);
}

/**
  * @brief    设置DMA Burst长度
  * @rmtoll   DCR    DBL    FL_ATIM_SetDMABurstLength
  * @param    TIMx TIM instance
  * @param    length This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_1
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_2
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_3
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_4
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_5
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_6
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_7
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_8
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_9
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_10
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_11
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_12
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_13
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_14
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_15
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_16
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_17
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_18
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetDMABurstLength(ATIM_Type *TIMx, uint32_t length)
{
    MODIFY_REG(TIMx->DCR, ATIM_DCR_DBL_Msk, length);
}

/**
  * @brief    读取DMA Burst长度
  * @rmtoll   DCR    DBL    FL_ATIM_GetDMABurstLength
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_1
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_2
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_3
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_4
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_5
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_6
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_7
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_8
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_9
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_10
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_11
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_12
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_13
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_14
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_15
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_16
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_17
  *           @arg @ref FL_ATIM_DMA_BURST_LENGTH_18
  */
__STATIC_INLINE uint32_t FL_ATIM_GetDMABurstLength(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DCR, ATIM_DCR_DBL_Msk));
}

/**
  * @brief    设置指向DMA寄存器的偏移地址
  * @rmtoll   DCR    DBA    FL_ATIM_SetDMABurstAddress
  * @param    TIMx TIM instance
  * @param    address This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CR1
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CR2
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_SMCR
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_DIER
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_SR
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_EGR
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCMR1
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCMR2
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCER
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CNT
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_PSC
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_ARR
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_RCR
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCR1
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCR2
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCR3
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCR4
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_BDTR
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetDMABurstAddress(ATIM_Type *TIMx, uint32_t address)
{
    MODIFY_REG(TIMx->DCR, ATIM_DCR_DBA_Msk, address);
}

/**
  * @brief    读取指向DMA寄存器的偏移地址
  * @rmtoll   DCR    DBA    FL_ATIM_GetDMABurstAddress
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CR1
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CR2
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_SMCR
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_DIER
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_SR
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_EGR
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCMR1
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCMR2
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCER
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CNT
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_PSC
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_ARR
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_RCR
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCR1
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCR2
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCR3
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_CCR4
  *           @arg @ref FL_ATIM_DMA_BURST_ADDR_BDTR
  */
__STATIC_INLINE uint32_t FL_ATIM_GetDMABurstAddress(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DCR, ATIM_DCR_DBA_Msk));
}

/**
  * @brief    配置DMA burst访问寄存器
  * @rmtoll   DMAR        FL_ATIM_WriteDMAAddress
  * @param    TIMx TIM instance
  * @param    address
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_WriteDMAAddress(ATIM_Type *TIMx, uint32_t address)
{
    MODIFY_REG(TIMx->DMAR, (0xffffU << 0U), (address << 0U));
}

/**
  * @brief    读取DMA burst访问寄存器值
  * @rmtoll   DMAR        FL_ATIM_ReadDMAAddress
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_ATIM_ReadDMAAddress(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DMAR, 0xffffU) >> 0U);
}

/**
  * @brief    输出比较清零使能
  * @rmtoll   CCMR    OCCE    FL_ATIM_OC_EnableClear
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_EnableClear(ATIM_Type *TIMx, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        SET_BIT(TIMx->CCMR1, (ATIM_CCMR_OCCE_Msk << (channel * 8)));
    }
    else
    {
        SET_BIT(TIMx->CCMR2, (ATIM_CCMR_OCCE_Msk << ((channel - 2) * 8)));
    }
}

/**
  * @brief    读取输出比较清零使能状态
  * @rmtoll   CCMR    OCCE    FL_ATIM_OC_IsEnabledClear
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_OC_IsEnabledClear(ATIM_Type *TIMx, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR1, (ATIM_CCMR_OCCE_Msk << (channel * 8))) == (ATIM_CCMR_OCCE_Msk << (channel * 8)));
    }
    else
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR2, (ATIM_CCMR_OCCE_Msk << ((channel - 2) * 8))) == (ATIM_CCMR_OCCE_Msk << ((channel - 2) * 8)));
    }
}

/**
  * @brief    输出比较清零禁用
  * @rmtoll   CCMR    OCCE    FL_ATIM_OC_DisableClear
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_DisableClear(ATIM_Type *TIMx, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        CLEAR_BIT(TIMx->CCMR1, (ATIM_CCMR_OCCE_Msk << (channel * 8)));
    }
    else
    {
        CLEAR_BIT(TIMx->CCMR2, (ATIM_CCMR_OCCE_Msk << ((channel - 2) * 8)));
    }
}

/**
  * @brief    输出比较模式配置
  * @rmtoll   CCMR    OCM    FL_ATIM_OC_SetMode
  * @param    TIMx TIM instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_OC_MODE_FROZEN
  *           @arg @ref FL_ATIM_OC_MODE_ACTIVE
  *           @arg @ref FL_ATIM_OC_MODE_INACTIVE
  *           @arg @ref FL_ATIM_OC_MODE_TOGGLE
  *           @arg @ref FL_ATIM_OC_MODE_FORCED_INACTIVE
  *           @arg @ref FL_ATIM_OC_MODE_FORCED_ACTIVE
  *           @arg @ref FL_ATIM_OC_MODE_PWM1
  *           @arg @ref FL_ATIM_OC_MODE_PWM2
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_SetMode(ATIM_Type *TIMx, uint32_t mode, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        MODIFY_REG(TIMx->CCMR1, (ATIM_CCMR_OCM_Msk << (channel * 8)), (mode << (channel * 8)));
    }
    else
    {
        MODIFY_REG(TIMx->CCMR2, (ATIM_CCMR_OCM_Msk << ((channel - 2) * 8)), (mode << ((channel - 2) * 8)));
    }
}

/**
  * @brief    读取输出比较模式配置值
  * @rmtoll   CCMR    OCM    FL_ATIM_OC_GetMode
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_OC_MODE_FROZEN
  *           @arg @ref FL_ATIM_OC_MODE_ACTIVE
  *           @arg @ref FL_ATIM_OC_MODE_INACTIVE
  *           @arg @ref FL_ATIM_OC_MODE_TOGGLE
  *           @arg @ref FL_ATIM_OC_MODE_FORCED_INACTIVE
  *           @arg @ref FL_ATIM_OC_MODE_FORCED_ACTIVE
  *           @arg @ref FL_ATIM_OC_MODE_PWM1
  *           @arg @ref FL_ATIM_OC_MODE_PWM2
  */
__STATIC_INLINE uint32_t FL_ATIM_OC_GetMode(ATIM_Type *TIMx, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR1, (ATIM_CCMR_OCM_Msk << (channel * 8))));
    }
    else
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR2, (ATIM_CCMR_OCM_Msk << ((channel - 2) * 8))));
    }
}

/**
  * @brief    输出比较预装载使能
  * @rmtoll   CCMR    OCPE    FL_ATIM_OC_EnablePreload
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_EnablePreload(ATIM_Type *TIMx, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        SET_BIT(TIMx->CCMR1, (ATIM_CCMR_OCPE_Msk << (channel * 8)));
    }
    else
    {
        SET_BIT(TIMx->CCMR2, (ATIM_CCMR_OCPE_Msk << ((channel - 2) * 8)));
    }
}

/**
  * @brief    读取输出比较预装载使能状态
  * @rmtoll   CCMR    OCPE    FL_ATIM_OC_IsEnabledPreload
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_OC_IsEnabledPreload(ATIM_Type *TIMx, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR1, (ATIM_CCMR_OCPE_Msk << (channel * 8))) == (ATIM_CCMR_OCPE_Msk << (channel * 8)));
    }
    else
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR2, (ATIM_CCMR_OCPE_Msk << ((channel - 2) * 8))) == (ATIM_CCMR_OCPE_Msk << ((channel - 2) * 8)));
    }
}

/**
  * @brief    输出比较预装载禁用
  * @rmtoll   CCMR    OCPE    FL_ATIM_OC_DisablePreload
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_DisablePreload(ATIM_Type *TIMx, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        CLEAR_BIT(TIMx->CCMR1, (ATIM_CCMR_OCPE_Msk << (channel * 8)));
    }
    else
    {
        CLEAR_BIT(TIMx->CCMR2, (ATIM_CCMR_OCPE_Msk << ((channel - 2) * 8)));
    }
}

/**
  * @brief    输出比较快速使能
  * @rmtoll   CCMR    OCFE    FL_ATIM_OC_EnableFastMode
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_EnableFastMode(ATIM_Type *TIMx, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        SET_BIT(TIMx->CCMR1, (ATIM_CCMR_OCFE_Msk << (channel * 8)));
    }
    else
    {
        SET_BIT(TIMx->CCMR2, (ATIM_CCMR_OCFE_Msk << ((channel - 2) * 8)));
    }
}

/**
  * @brief    获取输出比较快速使能状态
  * @rmtoll   CCMR    OCFE    FL_ATIM_OC_IsEnabledFastMode
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_OC_IsEnabledFastMode(ATIM_Type *TIMx, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR1, (ATIM_CCMR_OCFE_Msk << (channel * 8))) == (ATIM_CCMR_OCFE_Msk << (channel * 8)));
    }
    else
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR2, (ATIM_CCMR_OCFE_Msk << ((channel - 2) * 8))) == (ATIM_CCMR_OCFE_Msk << ((channel - 2) * 8)));
    }
}

/**
  * @brief    输出比较快速禁用
  * @rmtoll   CCMR    OCFE    FL_ATIM_OC_DisableFastMode
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_DisableFastMode(ATIM_Type *TIMx, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        CLEAR_BIT(TIMx->CCMR1, (ATIM_CCMR_OCFE_Msk << (channel * 8)));
    }
    else
    {
        CLEAR_BIT(TIMx->CCMR2, (ATIM_CCMR_OCFE_Msk << ((channel - 2) * 8)));
    }
}

/**
  * @brief    设置输入捕捉滤波器
  * @rmtoll   CCMR    ICF    FL_ATIM_IC_SetFilter
  * @param    TIMx TIM instance
  * @param    filter This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_IC_FILTER_DIV1
  *           @arg @ref FL_ATIM_IC_FILTER_DIV1_N2
  *           @arg @ref FL_ATIM_IC_FILTER_DIV1_N4
  *           @arg @ref FL_ATIM_IC_FILTER_DIV1_N8
  *           @arg @ref FL_ATIM_IC_FILTER_DIV2_N6
  *           @arg @ref FL_ATIM_IC_FILTER_DIV2_N8
  *           @arg @ref FL_ATIM_IC_FILTER_DIV4_N6
  *           @arg @ref FL_ATIM_IC_FILTER_DIV4_N8
  *           @arg @ref FL_ATIM_IC_FILTER_DIV8_N6
  *           @arg @ref FL_ATIM_IC_FILTER_DIV8_N8
  *           @arg @ref FL_ATIM_IC_FILTER_DIV16_N5
  *           @arg @ref FL_ATIM_IC_FILTER_DIV16_N6
  *           @arg @ref FL_ATIM_IC_FILTER_DIV16_N8
  *           @arg @ref FL_ATIM_IC_FILTER_DIV32_N5
  *           @arg @ref FL_ATIM_IC_FILTER_DIV32_N6
  *           @arg @ref FL_ATIM_IC_FILTER_DIV32_N8
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_IC_SetFilter(ATIM_Type *TIMx, uint32_t filter, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        MODIFY_REG(TIMx->CCMR1, (ATIM_CCMR_ICF_Msk << (channel * 8)), (filter << (channel * 8)));
    }
    else
    {
        MODIFY_REG(TIMx->CCMR2, (ATIM_CCMR_ICF_Msk << ((channel - 2) * 8)), (filter << ((channel - 2) * 8)));
    }
}

/**
  * @brief    读取输入滤波器值
  * @rmtoll   CCMR    ICF    FL_ATIM_IC_GetFilter
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_IC_FILTER_DIV1
  *           @arg @ref FL_ATIM_IC_FILTER_DIV1_N2
  *           @arg @ref FL_ATIM_IC_FILTER_DIV1_N4
  *           @arg @ref FL_ATIM_IC_FILTER_DIV1_N8
  *           @arg @ref FL_ATIM_IC_FILTER_DIV2_N6
  *           @arg @ref FL_ATIM_IC_FILTER_DIV2_N8
  *           @arg @ref FL_ATIM_IC_FILTER_DIV4_N6
  *           @arg @ref FL_ATIM_IC_FILTER_DIV4_N8
  *           @arg @ref FL_ATIM_IC_FILTER_DIV8_N6
  *           @arg @ref FL_ATIM_IC_FILTER_DIV8_N8
  *           @arg @ref FL_ATIM_IC_FILTER_DIV16_N5
  *           @arg @ref FL_ATIM_IC_FILTER_DIV16_N6
  *           @arg @ref FL_ATIM_IC_FILTER_DIV16_N8
  *           @arg @ref FL_ATIM_IC_FILTER_DIV32_N5
  *           @arg @ref FL_ATIM_IC_FILTER_DIV32_N6
  *           @arg @ref FL_ATIM_IC_FILTER_DIV32_N8
  */
__STATIC_INLINE uint32_t FL_ATIM_IC_GetFilter(ATIM_Type *TIMx, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR1, (ATIM_CCMR_ICF_Msk << (channel * 8))));
    }
    else
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR2, (ATIM_CCMR_ICF_Msk << ((channel - 2) * 8))));
    }
}

/**
  * @brief    设置输入捕捉预分频
  * @rmtoll   CCMR    ICPSC    FL_ATIM_IC_SetPrescaler
  * @param    TIMx TIM instance
  * @param    psc This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_IC_PSC_DIV1
  *           @arg @ref FL_ATIM_IC_PSC_DIV2
  *           @arg @ref FL_ATIM_IC_PSC_DIV4
  *           @arg @ref FL_ATIM_IC_PSC_DIV8
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_IC_SetPrescaler(ATIM_Type *TIMx, uint32_t psc, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        MODIFY_REG(TIMx->CCMR1, (ATIM_CCMR_ICPSC_Msk << (channel * 8)), (psc << (channel * 8)));
    }
    else
    {
        MODIFY_REG(TIMx->CCMR2, (ATIM_CCMR_ICPSC_Msk << ((channel - 2) * 8)), (psc << ((channel - 2) * 8)));
    }
}

/**
  * @brief    读取输入捕捉预分频值
  * @rmtoll   CCMR    ICPSC    FL_ATIM_IC_GetPrescaler
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_IC_PSC_DIV1
  *           @arg @ref FL_ATIM_IC_PSC_DIV2
  *           @arg @ref FL_ATIM_IC_PSC_DIV4
  *           @arg @ref FL_ATIM_IC_PSC_DIV8
  */
__STATIC_INLINE uint32_t FL_ATIM_IC_GetPrescaler(ATIM_Type *TIMx, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR1, (ATIM_CCMR_ICPSC_Msk << (channel * 8))));
    }
    else
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR2, (ATIM_CCMR_ICPSC_Msk << ((channel - 2) * 8))));
    }
}

/**
  * @brief    捕捉/比较通道选择
  * @rmtoll   CCMR    CCS    FL_ATIM_CC_SetChannelMode
  * @param    TIMx TIM instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_MODE_OUTPUT
  *           @arg @ref FL_ATIM_CHANNEL_MODE_INPUT_NORMAL
  *           @arg @ref FL_ATIM_CHANNEL_MODE_INPUT_CROSSOVER
  *           @arg @ref FL_ATIM_CHANNEL_MODE_INPUT_TRC
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_CC_SetChannelMode(ATIM_Type *TIMx, uint32_t mode, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        MODIFY_REG(TIMx->CCMR1, (ATIM_CCMR_CCS_Msk << (channel * 8)), (mode << (channel * 8)));
    }
    else
    {
        MODIFY_REG(TIMx->CCMR2, (ATIM_CCMR_CCS_Msk << ((channel - 2) * 8)), (mode << ((channel - 2) * 8)));
    }
}

/**
  * @brief    获取捕捉/比较通道
  * @rmtoll   CCMR    CCS    FL_ATIM_CC_GetChannelMode
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_MODE_OUTPUT
  *           @arg @ref FL_ATIM_CHANNEL_MODE_INPUT_NORMAL
  *           @arg @ref FL_ATIM_CHANNEL_MODE_INPUT_CROSSOVER
  *           @arg @ref FL_ATIM_CHANNEL_MODE_INPUT_TRC
  */
__STATIC_INLINE uint32_t FL_ATIM_CC_GetChannelMode(ATIM_Type *TIMx, uint32_t channel)
{
    if(channel < FL_ATIM_CHANNEL_3)
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR1, (ATIM_CCMR_CCS_Msk << (channel * 8))));
    }
    else
    {
        return (uint32_t)(READ_BIT(TIMx->CCMR2, (ATIM_CCMR_CCS_Msk << ((channel - 2) * 8))));
    }
}

/**
  * @brief    设置捕捉/比较互补输出极性
  * @note
  * @rmtoll   CCER    CCNP    FL_ATIM_OC_SetReverseChannelPolarity
  * @param    TIMx TIM instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_OCN_POLARITY_NORMAL
  *           @arg @ref FL_ATIM_OCN_POLARITY_INVERT
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_SetReverseChannelPolarity(ATIM_Type *TIMx, uint32_t polarity, uint32_t channel)
{
    MODIFY_REG(TIMx->CCER, (ATIM_CCER_CCNP_Msk << (channel * 4)), (polarity << (channel * 4)));
}

/**
  * @brief    读取捕捉/比较互补输出极性
  * @note
  * @rmtoll   CCER    CCNP    FL_ATIM_OC_GetReverseChannelPolarty
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_OCN_POLARITY_NORMAL
  *           @arg @ref FL_ATIM_OCN_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_ATIM_OC_GetReverseChannelPolarity(ATIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->CCER, (ATIM_CCER_CCNP_Msk << (channel * 4))));
}

/**
  * @brief    捕捉/比较互补输出使能
  * @note
  * @rmtoll   CCER    CCNE    FL_ATIM_OC_EnableReverseChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_EnableReverseChannel(ATIM_Type *TIMx, uint32_t channel)
{
    SET_BIT(TIMx->CCER, (ATIM_CCER_CCNE_Msk << (channel * 4)));
}

/**
  * @brief    读取捕捉/比较互补输出使能状态
  * @note
  * @rmtoll   CCER    CCNE    FL_ATIM_OC_IsEnabledReverseChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_OC_IsEnabledReverseChannel(ATIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->CCER, (ATIM_CCER_CCNE_Msk << (channel * 4))) == (ATIM_CCER_CCNE_Msk << (channel * 4)));
}

/**
  * @brief    捕捉/比较互补输出禁用
  * @note
  * @rmtoll   CCER    CCNE    FL_ATIM_OC_DisableReverseChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_DisableReverseChannel(ATIM_Type *TIMx, uint32_t channel)
{
    CLEAR_BIT(TIMx->CCER, (ATIM_CCER_CCNE_Msk << (channel * 4)));
}

/**
  * @brief    CC1通道配置为输出时，设置捕捉/比较输出极性
  * @rmtoll   CCER    CCOP    FL_ATIM_OC_SetChannelPolarity
  * @param    TIMx TIM instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_OC_POLARITY_NORMAL
  *           @arg @ref FL_ATIM_OC_POLARITY_INVERT
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_SetChannelPolarity(ATIM_Type *TIMx, uint32_t polarity, uint32_t channel)
{
    MODIFY_REG(TIMx->CCER, (ATIM_CCER_CCOP_Msk << (channel * 4)), (polarity << (channel * 4)));
}

/**
  * @brief    CC1通道配置为输出时，读取捕捉/比较输出极性
  * @rmtoll   CCER    CCOP    FL_ATIM_OC_GetChannelPolarity
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_OC_POLARITY_NORMAL
  *           @arg @ref FL_ATIM_OC_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_ATIM_OC_GetChannelPolarity(ATIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->CCER, (ATIM_CCER_CCOP_Msk << (channel * 4))));
}

/**
  * @brief    CC1通道配置为输入时，设置捕捉/比较输出极性
  * @rmtoll   CCER    CCIP    FL_ATIM_IC_SetChannelPolarity
  * @param    TIMx TIM instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_IC_POLARITY_NORMAL
  *           @arg @ref FL_ATIM_IC_POLARITY_INVERT
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_IC_SetChannelPolarity(ATIM_Type *TIMx, uint32_t polarity, uint32_t channel)
{
    MODIFY_REG(TIMx->CCER, (ATIM_CCER_CCIP_Msk << (channel * 4)), (polarity << (channel * 4)));
}

/**
  * @brief    CC1通道配置为输入时，设置捕捉/比较输出极性
  * @rmtoll   CCER    CCIP    FL_ATIM_IC_GetChannelPolarity
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_IC_POLARITY_NORMAL
  *           @arg @ref FL_ATIM_IC_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_ATIM_IC_GetChannelPolarity(ATIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->CCER, (ATIM_CCER_CCIP_Msk << (channel * 4))));
}

/**
  * @brief    CC1通道配置为输出时，捕捉/比较输出使能
  * @rmtoll   CCER    CCOE    FL_ATIM_OC_EnableChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_EnableChannel(ATIM_Type *TIMx, uint32_t channel)
{
    SET_BIT(TIMx->CCER, (ATIM_CCER_CCOE_Msk << (channel * 4)));
}

/**
  * @brief    CC1通道配置为输出时，读取捕捉/比较输出使能状态
  * @rmtoll   CCER    CCOE    FL_ATIM_OC_IsEnabledChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_OC_IsEnabledChannel(ATIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->CCER, (ATIM_CCER_CCOE_Msk << (channel * 4))) == (ATIM_CCER_CCOE_Msk << (channel * 4)));
}

/**
  * @brief    CC1通道配置为输出时，捕捉/比较输出禁用
  * @rmtoll   CCER    CCOE    FL_ATIM_OC_DisableChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_OC_DisableChannel(ATIM_Type *TIMx, uint32_t channel)
{
    CLEAR_BIT(TIMx->CCER, (ATIM_CCER_CCOE_Msk << (channel * 4)));
}

/**
  * @brief    CC1通道配置为输入时，捕捉/比较输出使能
  * @rmtoll   CCER    CCIE    FL_ATIM_IC_EnableChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_IC_EnableChannel(ATIM_Type *TIMx, uint32_t channel)
{
    SET_BIT(TIMx->CCER, (ATIM_CCER_CCIE_Msk << (channel * 4)));
}

/**
  * @brief    CC1通道配置为输入时，读取捕捉/比较输出使能状态
  * @rmtoll   CCER    CCIE    FL_ATIM_IC_IsEnabledChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IC_IsEnabledChannel(ATIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->CCER, (ATIM_CCER_CCIE_Msk << (channel * 4))) == (ATIM_CCER_CCIE_Msk << (channel * 4)));
}

/**
  * @brief    CC1通道配置为输入时，捕捉/比较输出禁用
  * @rmtoll   CCER    CCIE    FL_ATIM_IC_DisableChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_CHANNEL_1
  *           @arg @ref FL_ATIM_CHANNEL_2
  *           @arg @ref FL_ATIM_CHANNEL_3
  *           @arg @ref FL_ATIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_IC_DisableChannel(ATIM_Type *TIMx, uint32_t channel)
{
    CLEAR_BIT(TIMx->CCER, (ATIM_CCER_CCIE_Msk << (channel * 4)));
}

/**
  * @brief    设置重复计数值
  * @note
  * @rmtoll   RCR        FL_ATIM_WriteRepetitionCounter
  * @param    TIMx TIM instance
  * @param    repeatCounter
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_WriteRepetitionCounter(ATIM_Type *TIMx, uint32_t repeatCounter)
{
    MODIFY_REG(TIMx->RCR, (0xffU << 0U), (repeatCounter << 0U));
}

/**
  * @brief    读取重复计数值
  * @note
  * @rmtoll   RCR        FL_ATIM_ReadRepetitionCounter
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_ATIM_ReadRepetitionCounter(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->RCR, 0xffU) >> 0U);
}

/**
  * @brief    主控输出使能
  * @note
  * @rmtoll   BDTR    MOE    FL_ATIM_EnableALLOutput
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableALLOutput(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->BDTR, ATIM_BDTR_MOE_Msk);
}

/**
  * @brief    读取主控输出使能状态
  * @note
  * @rmtoll   BDTR    MOE    FL_ATIM_IsEnabledALLOutput
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledALLOutput(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BDTR, ATIM_BDTR_MOE_Msk) == ATIM_BDTR_MOE_Msk);
}

/**
  * @brief    主控输出禁用
  * @note
  * @rmtoll   BDTR    MOE    FL_ATIM_DisableALLOutput
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableALLOutput(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->BDTR, ATIM_BDTR_MOE_Msk);
}

/**
  * @brief    自动输出使能
  * @note
  * @rmtoll   BDTR    AOE    FL_ATIM_EnableAutomaticOutput
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableAutomaticOutput(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->BDTR, ATIM_BDTR_AOE_Msk);
}

/**
  * @brief    读取自动输出使能状态
  * @note
  * @rmtoll   BDTR    AOE    FL_ATIM_IsEnabledAutomaticOutput
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledAutomaticOutput(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BDTR, ATIM_BDTR_AOE_Msk) == ATIM_BDTR_AOE_Msk);
}

/**
  * @brief    自动输出禁用
  * @note
  * @rmtoll   BDTR    AOE    FL_ATIM_DisableAutomaticOutput
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableAutomaticOutput(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->BDTR, ATIM_BDTR_AOE_Msk);
}

/**
  * @brief    设置刹车极性
  * @note
  * @rmtoll   BDTR    BKP    FL_ATIM_SetBreakPolarity
  * @param    TIMx TIM instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_BREAK_POLARITY_LOW
  *           @arg @ref FL_ATIM_BREAK_POLARITY_HIGH
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetBreakPolarity(ATIM_Type *TIMx, uint32_t polarity)
{
    MODIFY_REG(TIMx->BDTR, ATIM_BDTR_BKP_Msk, polarity);
}

/**
  * @brief    读取刹车极性
  * @note
  * @rmtoll   BDTR    BKP    FL_ATIM_GetBreakPolarity
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_BREAK_POLARITY_LOW
  *           @arg @ref FL_ATIM_BREAK_POLARITY_HIGH
  */
__STATIC_INLINE uint32_t FL_ATIM_GetBreakPolarity(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BDTR, ATIM_BDTR_BKP_Msk));
}

/**
  * @brief    刹车使能
  * @note
  * @rmtoll   BDTR    BKE    FL_ATIM_EnableBreak
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableBreak(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->BDTR, ATIM_BDTR_BKE_Msk);
}

/**
  * @brief    读取刹车使能状态
  * @note
  * @rmtoll   BDTR    BKE    FL_ATIM_IsEnabledBreak
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledBreak(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BDTR, ATIM_BDTR_BKE_Msk) == ATIM_BDTR_BKE_Msk);
}

/**
  * @brief    刹车禁用
  * @note
  * @rmtoll   BDTR    BKE    FL_ATIM_DisableBreak
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableBreak(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->BDTR, ATIM_BDTR_BKE_Msk);
}

/**
  * @brief    运行状态下的输出关闭状态选择
  * @note
  * @rmtoll   BDTR    OSSR    FL_ATIM_SetOffStateRun
  * @param    TIMx TIM instance
  * @param    state This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_OSSR_DISABLE
  *           @arg @ref FL_ATIM_OSSR_ENABLE
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetOffStateRun(ATIM_Type *TIMx, uint32_t state)
{
    MODIFY_REG(TIMx->BDTR, ATIM_BDTR_OSSR_Msk, state);
}

/**
  * @brief    读取运行状态下的输出关闭状态选择
  * @note
  * @rmtoll   BDTR    OSSR    FL_ATIM_GetOffStateRun
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_OSSR_DISABLE
  *           @arg @ref FL_ATIM_OSSR_ENABLE
  */
__STATIC_INLINE uint32_t FL_ATIM_GetOffStateRun(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BDTR, ATIM_BDTR_OSSR_Msk));
}

/**
  * @brief    IDLE状态下的输出关闭状态选择
  * @note
  * @rmtoll   BDTR    OSSI    FL_ATIM_SetOffStateIdle
  * @param    TIMx TIM instance
  * @param    state This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_OSSI_DISABLE
  *           @arg @ref FL_ATIM_OSSI_ENABLE
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetOffStateIdle(ATIM_Type *TIMx, uint32_t state)
{
    MODIFY_REG(TIMx->BDTR, ATIM_BDTR_OSSI_Msk, state);
}

/**
  * @brief    IDLE状态下的输出关闭状态选择
  * @note
  * @rmtoll   BDTR    OSSI    FL_ATIM_GetOffStateIdle
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_OSSI_DISABLE
  *           @arg @ref FL_ATIM_OSSI_ENABLE
  */
__STATIC_INLINE uint32_t FL_ATIM_GetOffStateIdle(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BDTR, ATIM_BDTR_OSSI_Msk));
}

/**
  * @brief    设置寄存器写保护等级
  * @note
  * @rmtoll   BDTR    LOCK    FL_ATIM_SetLockLevel
  * @param    TIMx TIM instance
  * @param    lockLevel This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_LOCK_LEVEL_OFF
  *           @arg @ref FL_ATIM_LOCK_LEVEL_1
  *           @arg @ref FL_ATIM_LOCK_LEVEL_2
  *           @arg @ref FL_ATIM_LOCK_LEVEL_3
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetLockLevel(ATIM_Type *TIMx, uint32_t lockLevel)
{
    MODIFY_REG(TIMx->BDTR, ATIM_BDTR_LOCK_Msk, lockLevel);
}

/**
  * @brief    读取寄存器写保护配置状态
  * @note
  * @rmtoll   BDTR    LOCK    FL_ATIM_GetLockLevel
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_LOCK_LEVEL_OFF
  *           @arg @ref FL_ATIM_LOCK_LEVEL_1
  *           @arg @ref FL_ATIM_LOCK_LEVEL_2
  *           @arg @ref FL_ATIM_LOCK_LEVEL_3
  */
__STATIC_INLINE uint32_t FL_ATIM_GetLockLevel(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BDTR, ATIM_BDTR_LOCK_Msk));
}

/**
  * @brief    设置死区时间长度
  * @note
  * @rmtoll   BDTR    DTG    FL_ATIM_WriteDeadTime
  * @param    TIMx TIM instance
  * @param    deadTime
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_WriteDeadTime(ATIM_Type *TIMx, uint32_t deadTime)
{
    MODIFY_REG(TIMx->BDTR, (0xffU << 0U), (deadTime << 0U));
}

/**
  * @brief    读取死区时间长度
  * @note
  * @rmtoll   BDTR    DTG    FL_ATIM_ReadDeadTime
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_ATIM_ReadDeadTime(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BDTR, 0xffU) >> 0U);
}

/**
  * @brief    设置ATIM_BRK1引脚输入门控信号
  * @note
  * @rmtoll   BKCR    BRK1GATE    FL_ATIM_SetBreak1GateState
  * @param    TIMx TIM instance
  * @param    state This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_BREAK1_GATE_LOW
  *           @arg @ref FL_ATIM_BREAK1_GATE_AUTO
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetBreak1GateState(ATIM_Type *TIMx, uint32_t state)
{
    MODIFY_REG(TIMx->BKCR, ATIM_BKCR_BRK1GATE_Msk, state);
}

/**
  * @brief    读取ATIM_BRK1引脚输入门控信号
  * @note
  * @rmtoll   BKCR    BRK1GATE    FL_ATIM_GetBreak1GateState
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_BREAK1_GATE_LOW
  *           @arg @ref FL_ATIM_BREAK1_GATE_AUTO
  */
__STATIC_INLINE uint32_t FL_ATIM_GetBreak1GateState(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BKCR, ATIM_BKCR_BRK1GATE_Msk));
}

/**
  * @brief    设置ATIM_BRK2引脚输入门控信号
  * @note
  * @rmtoll   BKCR    BRK2GATE    FL_ATIM_SetBreak2GateState
  * @param    TIMx TIM instance
  * @param    state This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_BREAK2_GATE_LOW
  *           @arg @ref FL_ATIM_BREAK2_GATE_AUTO
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetBreak2GateState(ATIM_Type *TIMx, uint32_t state)
{
    MODIFY_REG(TIMx->BKCR, ATIM_BKCR_BRK2GATE_Msk, state);
}

/**
  * @brief    读取ATIM_BRK2引脚输入门控信号
  * @note
  * @rmtoll   BKCR    BRK2GATE    FL_ATIM_GetBreak2GateState
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_BREAK2_GATE_LOW
  *           @arg @ref FL_ATIM_BREAK2_GATE_AUTO
  */
__STATIC_INLINE uint32_t FL_ATIM_GetBreak2GateState(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BKCR, ATIM_BKCR_BRK2GATE_Msk));
}

/**
  * @brief    设置刹车信号的滤波时钟和长度选择
  * @note
  * @rmtoll   BKCR    BRKF    FL_ATIM_SetBreakFilter
  * @param    TIMx TIM instance
  * @param    filter This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV1
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV1_N2
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV1_N4
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV1_N8
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV2_N6
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV2_N8
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV4_N6
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV4_N8
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV8_N6
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV8_N8
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV16_N5
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV16_N6
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV16_N8
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV32_N5
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV32_N6
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV32_N8
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetBreakFilter(ATIM_Type *TIMx, uint32_t filter)
{
    MODIFY_REG(TIMx->BKCR, ATIM_BKCR_BRKF_Msk, filter);
}

/**
  * @brief    读取刹车信号的滤波时钟和长度选择
  * @note
  * @rmtoll   BKCR    BRKF    FL_ATIM_GetBreakFilter
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV1
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV1_N2
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV1_N4
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV1_N8
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV2_N6
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV2_N8
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV4_N6
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV4_N8
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV8_N6
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV8_N8
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV16_N5
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV16_N6
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV16_N8
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV32_N5
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV32_N6
  *           @arg @ref FL_ATIM_BREAK_FILTER_DIV32_N8
  */
__STATIC_INLINE uint32_t FL_ATIM_GetBreakFilter(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BKCR, ATIM_BKCR_BRKF_Msk));
}

/**
  * @brief    刹车组合控制
  * @note
  * @rmtoll   BKCR    BRKCOMB    FL_ATIM_SetBreakSignalCombination
  * @param    TIMx TIM instance
  * @param    filter This parameter can be one of the following values:
  *           @arg @ref FL_ATIM_BREAK_COMBINATION_OR
  *           @arg @ref FL_ATIM_BREAK_COMBINATION_AND
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_SetBreakSignalCombination(ATIM_Type *TIMx, uint32_t filter)
{
    MODIFY_REG(TIMx->BKCR, ATIM_BKCR_BRKCOMB_Msk, filter);
}

/**
  * @brief    读取刹车组合控制状态
  * @note
  * @rmtoll   BKCR    BRKCOMB    FL_ATIM_GetBreakSignalCombination
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ATIM_BREAK_COMBINATION_OR
  *           @arg @ref FL_ATIM_BREAK_COMBINATION_AND
  */
__STATIC_INLINE uint32_t FL_ATIM_GetBreakSignalCombination(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BKCR, ATIM_BKCR_BRKCOMB_Msk));
}

/**
  * @brief    XTHF停振检测刹车信号使能
  * @note
  * @rmtoll   BKCR    HFDET_BRKEN    FL_ATIM_EnableHFDETBreak
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableHFDETBreak(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->BKCR, ATIM_BKCR_HFDET_BRKEN_Msk);
}

/**
  * @brief    读取XTHF停振检测刹车信号使能状态
  * @note
  * @rmtoll   BKCR    HFDET_BRKEN    FL_ATIM_IsEnabledHFDETBreak
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledHFDETBreak(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BKCR, ATIM_BKCR_HFDET_BRKEN_Msk) == ATIM_BKCR_HFDET_BRKEN_Msk);
}

/**
  * @brief    XTHF停振检测刹车信号禁用
  * @note
  * @rmtoll   BKCR    HFDET_BRKEN    FL_ATIM_DisableHFDETBreak
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableHFDETBreak(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->BKCR, ATIM_BKCR_HFDET_BRKEN_Msk);
}

/**
  * @brief    SVD刹车信号使能
  * @note
  * @rmtoll   BKCR    SVD_BRKEN    FL_ATIM_EnableSVDBreak
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableSVDBreak(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->BKCR, ATIM_BKCR_SVD_BRKEN_Msk);
}

/**
  * @brief    读取SVD刹车信号使能状态
  * @note
  * @rmtoll   BKCR    SVD_BRKEN    FL_ATIM_IsEnabledSVDBreak
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledSVDBreak(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BKCR, ATIM_BKCR_SVD_BRKEN_Msk) == ATIM_BKCR_SVD_BRKEN_Msk);
}

/**
  * @brief    SVD刹车信号禁用
  * @note
  * @rmtoll   BKCR    SVD_BRKEN    FL_ATIM_DisableSVDBreak
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableSVDBreak(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->BKCR, ATIM_BKCR_SVD_BRKEN_Msk);
}

/**
  * @brief    比较器输出刹车信号使能
  * @note
  * @rmtoll   BKCR    COMP_BRKEN    FL_ATIM_EnableCOMPBreak
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_EnableCOMPBreak(ATIM_Type *TIMx)
{
    SET_BIT(TIMx->BKCR, ATIM_BKCR_COMP_BRKEN_Msk);
}

/**
  * @brief    读取比较器输出刹车信号使能状态
  * @note
  * @rmtoll   BKCR    COMP_BRKEN    FL_ATIM_IsEnabledCOMPBreak
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ATIM_IsEnabledCOMPBreak(ATIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->BKCR, ATIM_BKCR_COMP_BRKEN_Msk) == ATIM_BKCR_COMP_BRKEN_Msk);
}

/**
  * @brief    比较器输出刹车信号禁用
  * @note
  * @rmtoll   BKCR    COMP_BRKEN    FL_ATIM_DisableCOMPBreak
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_ATIM_DisableCOMPBreak(ATIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->BKCR, ATIM_BKCR_COMP_BRKEN_Msk);
}

/**
  * @}
  */

/** @defgroup ATIM_FL_EF_Init Initialization and de-initialization functions
  * @{
  */

FL_ErrorStatus FL_ATIM_DeInit(ATIM_Type *TIMx);

void FL_ATIM_StructInit(FL_ATIM_InitTypeDef *TIM_InitStruct);
void FL_ATIM_SlaveModeStructInit(FL_ATIM_SlaveInitTypeDef *TIM_InitStruct);
void FL_ATIM_IC_StructInit(FL_ATIM_IC_InitTypeDef *TIM_ICInitStruct);
void FL_ATIM_OC_StructInit(FL_ATIM_OC_InitTypeDef *TIM_OC_InitStruct);
void FL_ATIM_ETRStructInit(FL_ATIM_ETR_InitTypeDef *TIM_InitStruct);
void FL_ATIM_BDTR_StructInit(FL_ATIM_BDTR_InitTypeDef *TIM_BDTR_InitStruct);

FL_ErrorStatus FL_ATIM_Init(ATIM_Type *TIMx, FL_ATIM_InitTypeDef *TIM_InitStruct);
FL_ErrorStatus FL_ATIM_IC_Init(ATIM_Type *TIMx, uint32_t Channel, FL_ATIM_IC_InitTypeDef *IC_InitStruct);
FL_ErrorStatus FL_ATIM_ETR_Init(ATIM_Type *TIMx, FL_ATIM_ETR_InitTypeDef *TIM_InitStruct);
FL_ErrorStatus FL_ATIM_SlaveMode_Init(ATIM_Type *TIMx, FL_ATIM_SlaveInitTypeDef *TIM_InitStruct);
FL_ErrorStatus FL_ATIM_OC_Init(ATIM_Type *TIMx, uint32_t Channel, FL_ATIM_OC_InitTypeDef *TIM_OC_InitStruct);
FL_ErrorStatus FL_ATIM_BDTR_Init(ATIM_Type *TIMx, FL_ATIM_BDTR_InitTypeDef *TIM_BDTR_InitStruct);

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

#endif /* __FM33LC0XX_FL_ATIM_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-12*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
