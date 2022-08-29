/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_gptim.h
  * @author  FMSH Application Team
  * @brief   Head file of GPTIM FL Module
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
#ifndef __FM33LC0XX_FL_GPTIM_H
#define __FM33LC0XX_FL_GPTIM_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup GPTIM GPTIM
  * @brief GPTIM FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup GPTIM_FL_ES_INIT GPTIM Exported Init structures
  * @{
  */

/**
  * @brief GPTIM Init Sturcture Definition
  */
typedef struct
{
    /** 预分频系数 */
    uint32_t prescaler;

    /** 计数模式 */
    uint32_t counterMode;

    /** 自动重装载值 */
    uint32_t autoReload;

    /** 预装载使能 */
    uint32_t autoReloadState;

    /** 定时器分频系数与数字滤波器所使用的采样时钟分频比*/
    uint32_t clockDivision;

} FL_GPTIM_InitTypeDef;

/**
  * @brief GPTIM SlaveMode Init Sturcture Definition
  */
typedef struct
{
    /** ITRx 源*/
    uint32_t ITRSourceGroup;

    /** 外部时钟源模式 */
    uint32_t slaveMode;

    /** 输入触发信号选择 */
    uint32_t triggerSrc;

    /** Trigger 延迟*/
    uint32_t triggerDelay;

} FL_GPTIM_SlaveInitTypeDef;

/**
  * @brief  GPTIM Input Capture Init Structure Definition
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

} FL_GPTIM_IC_InitTypeDef;

/**
  * @brief  GPTIM ETR Init Structure Definition
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

} FL_GPTIM_ETR_InitTypeDef;

/**
  * @brief  GPTIM Output Compare Init Structure Definition
  */
typedef struct
{
    /** 比较输出模式 */
    uint32_t OCMode;

    /** 比较输出通道快速模式使能 */
    uint32_t OCFastMode;

    /** 输出比较预装载 */
    uint32_t OCPreload;

    /** 通道比较值 */
    uint32_t compareValue;

    /** 比较输出极性 */
    uint32_t OCPolarity;

    /** ETR清0使能 */
    uint32_t OCETRFStatus;

} FL_GPTIM_OC_InitTypeDef;

/**
  * @}
  */

/**
  * GPTIM0~GPTIM2 ITRSEL_Group 映射表
  *
  * ===================== GPTIM0 ======================
  * ---------------------------------------------------
  * ITRx   | Group  | Function Name | Function Type
  * ---------------------------------------------------
  * ITR0   | 0      | ATIM_TRGO     | 计数触发
  *        | 1      | UART0_RX      | 宽度捕捉
  *        | 2      | UART1_RX      | 宽度捕捉
  *        | 3      | UART3_RX      | 宽度捕捉
  * ---------------------------------------------------
  * ITR1   | 0      | GPTIM2_TRGO   | 计数触发
  *        | 1      | XTHF          | 周期捕捉
  *        | 2      | RCHF          | 周期捕捉
  *        | 3      | LPUART1_RX    | 周期捕捉
  * ---------------------------------------------------
  * ITR2   | 0      | BSTIM32_TRGO  | 计数触发
  *        | 1      | LPUART2_RX    | 宽度捕捉
  *        | 2      | LPOSC         | 周期捕捉
  *        | 3      | XTLF          | 周期捕捉
  * ---------------------------------------------------
  * ITR3   | 0      | COMP1_TRGO    | 计数触发
  *        | 1      | RCLF          | 周期捕捉
  *        | 2      | COMP2_TRGO    | 计数触发
  *        | 3      | LPT32_TRGO    | 计数触发
  * ---------------------------------------------------
  *
  * ===================== GPTIM1 ======================
  * ---------------------------------------------------
  * ITRx   | Group  | Function Name | Function Type
  * ---------------------------------------------------
  * ITR0   | 0      | ATIM_TRGO     | 计数触发
  *        | 1      | UART0_RX      | 宽度捕捉
  *        | 2      | UART1_RX      | 宽度捕捉
  *        | 3      | UART3_RX      | 宽度捕捉
  * ---------------------------------------------------
  * ITR1   | 0      | GPTIM0_TRGO   | 计数触发
  *        | 1      | LUT1_TRGO     | 周期捕捉
  *        | 2      | RCHF          | 周期捕捉
  *        | 3      | ADC_EOC_TRGO  | 计数触发
  * ---------------------------------------------------
  * ITR2   | 0      | BSTIM32_TRGO  | 计数触发
  *        | 1      | LSCLK         | 周期捕捉
  *        | 2      | LPOSC         | 周期捕捉
  *        | 3      | XTLF          | 周期捕捉
  * ---------------------------------------------------
  * ITR3   | 0      | COMP1_TRGO    | 计数触发
  *        | 1      | LUT3_TRGO     | 周期捕捉
  *        | 2      | COMP2_TRGO    | 计数触发
  *        | 3      | LPT32_TRGO    | 计数触发
  * ---------------------------------------------------
  *
  */

/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup GPTIM_FL_Exported_Constants GPTIM Exported Constants
  * @{
  */

#define    GPTIM_CR1_CKD_Pos                                      (8U)
#define    GPTIM_CR1_CKD_Msk                                      (0x3U << GPTIM_CR1_CKD_Pos)
#define    GPTIM_CR1_CKD                                          GPTIM_CR1_CKD_Msk

#define    GPTIM_CR1_ARPE_Pos                                     (7U)
#define    GPTIM_CR1_ARPE_Msk                                     (0x1U << GPTIM_CR1_ARPE_Pos)
#define    GPTIM_CR1_ARPE                                         GPTIM_CR1_ARPE_Msk

#define    GPTIM_CR1_CMS_Pos                                      (5U)
#define    GPTIM_CR1_CMS_Msk                                      (0x3U << GPTIM_CR1_CMS_Pos)
#define    GPTIM_CR1_CMS                                          GPTIM_CR1_CMS_Msk

#define    GPTIM_CR1_DIR_Pos                                      (4U)
#define    GPTIM_CR1_DIR_Msk                                      (0x1U << GPTIM_CR1_DIR_Pos)
#define    GPTIM_CR1_DIR                                          GPTIM_CR1_DIR_Msk

#define    GPTIM_CR1_OPM_Pos                                      (3U)
#define    GPTIM_CR1_OPM_Msk                                      (0x1U << GPTIM_CR1_OPM_Pos)
#define    GPTIM_CR1_OPM                                          GPTIM_CR1_OPM_Msk

#define    GPTIM_CR1_URS_Pos                                      (2U)
#define    GPTIM_CR1_URS_Msk                                      (0x1U << GPTIM_CR1_URS_Pos)
#define    GPTIM_CR1_URS                                          GPTIM_CR1_URS_Msk

#define    GPTIM_CR1_UDIS_Pos                                     (1U)
#define    GPTIM_CR1_UDIS_Msk                                     (0x1U << GPTIM_CR1_UDIS_Pos)
#define    GPTIM_CR1_UDIS                                         GPTIM_CR1_UDIS_Msk

#define    GPTIM_CR1_CEN_Pos                                      (0U)
#define    GPTIM_CR1_CEN_Msk                                      (0x1U << GPTIM_CR1_CEN_Pos)
#define    GPTIM_CR1_CEN                                          GPTIM_CR1_CEN_Msk

#define    GPTIM_CR2_TI1S_Pos                                     (7U)
#define    GPTIM_CR2_TI1S_Msk                                     (0x1U << GPTIM_CR2_TI1S_Pos)
#define    GPTIM_CR2_TI1S                                         GPTIM_CR2_TI1S_Msk

#define    GPTIM_CR2_MMS_Pos                                      (4U)
#define    GPTIM_CR2_MMS_Msk                                      (0x7U << GPTIM_CR2_MMS_Pos)
#define    GPTIM_CR2_MMS                                          GPTIM_CR2_MMS_Msk

#define    GPTIM_CR2_CCDS_Pos                                     (3U)
#define    GPTIM_CR2_CCDS_Msk                                     (0x1U << GPTIM_CR2_CCDS_Pos)
#define    GPTIM_CR2_CCDS                                         GPTIM_CR2_CCDS_Msk

#define    GPTIM_SMCR_ETP_Pos                                     (15U)
#define    GPTIM_SMCR_ETP_Msk                                     (0x1U << GPTIM_SMCR_ETP_Pos)
#define    GPTIM_SMCR_ETP                                         GPTIM_SMCR_ETP_Msk

#define    GPTIM_SMCR_ECE_Pos                                     (14U)
#define    GPTIM_SMCR_ECE_Msk                                     (0x1U << GPTIM_SMCR_ECE_Pos)
#define    GPTIM_SMCR_ECE                                         GPTIM_SMCR_ECE_Msk

#define    GPTIM_SMCR_ETPS_Pos                                    (12U)
#define    GPTIM_SMCR_ETPS_Msk                                    (0x3U << GPTIM_SMCR_ETPS_Pos)
#define    GPTIM_SMCR_ETPS                                        GPTIM_SMCR_ETPS_Msk

#define    GPTIM_SMCR_ETF_Pos                                     (8U)
#define    GPTIM_SMCR_ETF_Msk                                     (0xfU << GPTIM_SMCR_ETF_Pos)
#define    GPTIM_SMCR_ETF                                         GPTIM_SMCR_ETF_Msk

#define    GPTIM_SMCR_MSM_Pos                                     (7U)
#define    GPTIM_SMCR_MSM_Msk                                     (0x1U << GPTIM_SMCR_MSM_Pos)
#define    GPTIM_SMCR_MSM                                         GPTIM_SMCR_MSM_Msk

#define    GPTIM_SMCR_TS_Pos                                      (4U)
#define    GPTIM_SMCR_TS_Msk                                      (0x7U << GPTIM_SMCR_TS_Pos)
#define    GPTIM_SMCR_TS                                          GPTIM_SMCR_TS_Msk

#define    GPTIM_SMCR_SMS_Pos                                     (0U)
#define    GPTIM_SMCR_SMS_Msk                                     (0x7U << GPTIM_SMCR_SMS_Pos)
#define    GPTIM_SMCR_SMS                                         GPTIM_SMCR_SMS_Msk

#define    GPTIM_DIER_CC1BURSTEN_Pos                              (16U)
#define    GPTIM_DIER_CC1BURSTEN_Msk                              (0x1U << GPTIM_DIER_CC1BURSTEN_Pos)
#define    GPTIM_DIER_CC1BURSTEN                                  GPTIM_DIER_CC1BURSTEN_Msk

#define    GPTIM_DIER_CC2BURSTEN_Pos                              (17U)
#define    GPTIM_DIER_CC2BURSTEN_Msk                              (0x1U << GPTIM_DIER_CC2BURSTEN_Pos)
#define    GPTIM_DIER_CC2BURSTEN                                  GPTIM_DIER_CC2BURSTEN_Msk

#define    GPTIM_DIER_CC3BURSTEN_Pos                              (18U)
#define    GPTIM_DIER_CC3BURSTEN_Msk                              (0x1U << GPTIM_DIER_CC3BURSTEN_Pos)
#define    GPTIM_DIER_CC3BURSTEN                                  GPTIM_DIER_CC3BURSTEN_Msk

#define    GPTIM_DIER_CC4BURSTEN_Pos                              (19U)
#define    GPTIM_DIER_CC4BURSTEN_Msk                              (0x1U << GPTIM_DIER_CC4BURSTEN_Pos)
#define    GPTIM_DIER_CC4BURSTEN                                  GPTIM_DIER_CC4BURSTEN_Msk

#define    GPTIM_DIER_TDE_Pos                                     (14U)
#define    GPTIM_DIER_TDE_Msk                                     (0x1U << GPTIM_DIER_TDE_Pos)
#define    GPTIM_DIER_TDE                                         GPTIM_DIER_TDE_Msk

#define    GPTIM_DIER_CCDE_Pos                                    (9U)
#define    GPTIM_DIER_CCDE_Msk                                    (0x1U << GPTIM_DIER_CCDE_Pos)
#define    GPTIM_DIER_CCDE                                        GPTIM_DIER_CCDE_Msk

#define    GPTIM_DIER_UDE_Pos                                     (8U)
#define    GPTIM_DIER_UDE_Msk                                     (0x1U << GPTIM_DIER_UDE_Pos)
#define    GPTIM_DIER_UDE                                         GPTIM_DIER_UDE_Msk

#define    GPTIM_DIER_TIE_Pos                                     (6U)
#define    GPTIM_DIER_TIE_Msk                                     (0x1U << GPTIM_DIER_TIE_Pos)
#define    GPTIM_DIER_TIE                                         GPTIM_DIER_TIE_Msk

#define    GPTIM_DIER_CCIE_Pos                                    (1U)
#define    GPTIM_DIER_CCIE_Msk                                    (0x1U << GPTIM_DIER_CCIE_Pos)
#define    GPTIM_DIER_CCIE                                        GPTIM_DIER_CCIE_Msk

#define    GPTIM_DIER_UIE_Pos                                     (0U)
#define    GPTIM_DIER_UIE_Msk                                     (0x1U << GPTIM_DIER_UIE_Pos)
#define    GPTIM_DIER_UIE                                         GPTIM_DIER_UIE_Msk

#define    GPTIM_ISR_CCOF_Pos                                     (9U)
#define    GPTIM_ISR_CCOF_Msk                                     (0x1U << GPTIM_ISR_CCOF_Pos)
#define    GPTIM_ISR_CCOF                                         GPTIM_ISR_CCOF_Msk

#define    GPTIM_ISR_TIF_Pos                                      (6U)
#define    GPTIM_ISR_TIF_Msk                                      (0x1U << GPTIM_ISR_TIF_Pos)
#define    GPTIM_ISR_TIF                                          GPTIM_ISR_TIF_Msk

#define    GPTIM_ISR_CCIF_Pos                                     (1U)
#define    GPTIM_ISR_CCIF_Msk                                     (0x1U << GPTIM_ISR_CCIF_Pos)
#define    GPTIM_ISR_CCIF                                         GPTIM_ISR_CCIF_Msk

#define    GPTIM_ISR_UIF_Pos                                      (0U)
#define    GPTIM_ISR_UIF_Msk                                      (0x1U << GPTIM_ISR_UIF_Pos)
#define    GPTIM_ISR_UIF                                          GPTIM_ISR_UIF_Msk

#define    GPTIM_EGR_TG_Pos                                       (6U)
#define    GPTIM_EGR_TG_Msk                                       (0x1U << GPTIM_EGR_TG_Pos)
#define    GPTIM_EGR_TG                                           GPTIM_EGR_TG_Msk

#define    GPTIM_EGR_CCG_Pos                                      (1U)
#define    GPTIM_EGR_CCG_Msk                                      (0x1U << GPTIM_EGR_CCG_Pos)
#define    GPTIM_EGR_CCG                                          GPTIM_EGR_CCG_Msk

#define    GPTIM_EGR_UG_Pos                                       (0U)
#define    GPTIM_EGR_UG_Msk                                       (0x1U << GPTIM_EGR_UG_Pos)
#define    GPTIM_EGR_UG                                           GPTIM_EGR_UG_Msk

#define    GPTIM_DCR_DBL_Pos                                      (8U)
#define    GPTIM_DCR_DBL_Msk                                      (0x1fU << GPTIM_DCR_DBL_Pos)
#define    GPTIM_DCR_DBL                                          GPTIM_DCR_DBL_Msk

#define    GPTIM_DCR_DBA_Pos                                      (0U)
#define    GPTIM_DCR_DBA_Msk                                      (0x1fU << GPTIM_DCR_DBA_Pos)
#define    GPTIM_DCR_DBA                                          GPTIM_DCR_DBA_Msk

#define    GPTIM_ITRSEL_Pos                                       (0U)
#define    GPTIM_ITRSEL_Msk                                       (0x3U << GPTIM_ITRSEL_Pos)
#define    GPTIM_ITRSEL                                           GPTIM_ITRSEL_Msk

#define    GPTIM_CCMR_OCCE_Pos                                    (7U)
#define    GPTIM_CCMR_OCCE_Msk                                    (0x1U << GPTIM_CCMR_OCCE_Pos)
#define    GPTIM_CCMR_OCCE                                        GPTIM_CCMR_OCCE_Msk

#define    GPTIM_CCMR_OCM_Pos                                     (4U)
#define    GPTIM_CCMR_OCM_Msk                                     (0x7U << GPTIM_CCMR_OCM_Pos)
#define    GPTIM_CCMR_OCM                                         GPTIM_CCMR_OCM_Msk

#define    GPTIM_CCMR_OCPE_Pos                                    (3U)
#define    GPTIM_CCMR_OCPE_Msk                                    (0x1U << GPTIM_CCMR_OCPE_Pos)
#define    GPTIM_CCMR_OCPE                                        GPTIM_CCMR_OCPE_Msk

#define    GPTIM_CCMR_OCFE_Pos                                    (2U)
#define    GPTIM_CCMR_OCFE_Msk                                    (0x1U << GPTIM_CCMR_OCFE_Pos)
#define    GPTIM_CCMR_OCFE                                        GPTIM_CCMR_OCFE_Msk

#define    GPTIM_CCMR_ICF_Pos                                     (4U)
#define    GPTIM_CCMR_ICF_Msk                                     (0xfU << GPTIM_CCMR_ICF_Pos)
#define    GPTIM_CCMR_ICF                                         GPTIM_CCMR_ICF_Msk

#define    GPTIM_CCMR_ICPSC_Pos                                   (2U)
#define    GPTIM_CCMR_ICPSC_Msk                                   (0x3U << GPTIM_CCMR_ICPSC_Pos)
#define    GPTIM_CCMR_ICPSC                                       GPTIM_CCMR_ICPSC_Msk

#define    GPTIM_CCMR_CCS_Pos                                     (0U)
#define    GPTIM_CCMR_CCS_Msk                                     (0x3U << GPTIM_CCMR_CCS_Pos)
#define    GPTIM_CCMR_CCS                                         GPTIM_CCMR_CCS_Msk

#define    GPTIM_CCER_CCOP_Pos                                    (1U)
#define    GPTIM_CCER_CCOP_Msk                                    (0x1U << GPTIM_CCER_CCOP_Pos)
#define    GPTIM_CCER_CCOP                                        GPTIM_CCER_CCOP_Msk

#define    GPTIM_CCER_CCIP_Pos                                    (1U)
#define    GPTIM_CCER_CCIP_Msk                                    (0x1U << GPTIM_CCER_CCIP_Pos)
#define    GPTIM_CCER_CCIP                                        GPTIM_CCER_CCIP_Msk

#define    GPTIM_CCER_CCE_Pos                                     (0U)
#define    GPTIM_CCER_CCE_Msk                                     (0x1U << GPTIM_CCER_CCE_Pos)
#define    GPTIM_CCER_CCE                                         GPTIM_CCER_CCE_Msk



#define    FL_GPTIM_CHANNEL_1                                     (0x1U << 0U)
#define    FL_GPTIM_CHANNEL_2                                     (0x1U << 1U)
#define    FL_GPTIM_CHANNEL_3                                     (0x1U << 2U)
#define    FL_GPTIM_CHANNEL_4                                     (0x1U << 3U)
#define    FL_GPTIM_ITR0                                          (0x1U << 0U)
#define    FL_GPTIM_ITR1                                          (0x1U << 1U)
#define    FL_GPTIM_ITR2                                          (0x1U << 2U)
#define    FL_GPTIM_ITR3                                          (0x1U << 3U)



#define    FL_GPTIM_CLK_DIVISION_DIV1                             (0x0U << GPTIM_CR1_CKD_Pos)
#define    FL_GPTIM_CLK_DIVISION_DIV2                             (0x1U << GPTIM_CR1_CKD_Pos)
#define    FL_GPTIM_CLK_DIVISION_DIV4                             (0x2U << GPTIM_CR1_CKD_Pos)


#define    FL_GPTIM_COUNTER_ALIGNED_EDGE                          (0x0U << GPTIM_CR1_CMS_Pos)
#define    FL_GPTIM_COUNTER_ALIGNED_CENTER_DOWN                   (0x1U << GPTIM_CR1_CMS_Pos)
#define    FL_GPTIM_COUNTER_ALIGNED_CENTER_UP                     (0x2U << GPTIM_CR1_CMS_Pos)
#define    FL_GPTIM_COUNTER_ALIGNED_CENTER_UP_DOWN                (0x3U << GPTIM_CR1_CMS_Pos)


#define    FL_GPTIM_COUNTER_DIR_UP                                (0x0U << GPTIM_CR1_DIR_Pos)
#define    FL_GPTIM_COUNTER_DIR_DOWN                              (0x1U << GPTIM_CR1_DIR_Pos)


#define    FL_GPTIM_ONE_PULSE_MODE_CONTINUOUS                     (0x0U << GPTIM_CR1_OPM_Pos)
#define    FL_GPTIM_ONE_PULSE_MODE_SINGLE                         (0x1U << GPTIM_CR1_OPM_Pos)


#define    FL_GPTIM_UPDATE_SOURCE_REGULAR                         (0x0U << GPTIM_CR1_URS_Pos)
#define    FL_GPTIM_UPDATE_SOURCE_COUNTER                         (0x1U << GPTIM_CR1_URS_Pos)


#define    FL_GPTIM_TRGO_RESET                                    (0x0U << GPTIM_CR2_MMS_Pos)
#define    FL_GPTIM_TRGO_ENABLE                                   (0x1U << GPTIM_CR2_MMS_Pos)
#define    FL_GPTIM_TRGO_UPDATE                                   (0x2U << GPTIM_CR2_MMS_Pos)
#define    FL_GPTIM_TRGO_CC1IF                                    (0x3U << GPTIM_CR2_MMS_Pos)
#define    FL_GPTIM_TRGO_OC1REF                                   (0x4U << GPTIM_CR2_MMS_Pos)
#define    FL_GPTIM_TRGO_OC2REF                                   (0x5U << GPTIM_CR2_MMS_Pos)
#define    FL_GPTIM_TRGO_OC3REF                                   (0x6U << GPTIM_CR2_MMS_Pos)
#define    FL_GPTIM_TRGO_OC4REF                                   (0x7U << GPTIM_CR2_MMS_Pos)


#define    FL_GPTIM_DMA_REQ_CC                                    (0x0U << GPTIM_CR2_CCDS_Pos)
#define    FL_GPTIM_DMA_REQ_UPDATE                                (0x1U << GPTIM_CR2_CCDS_Pos)


#define    FL_GPTIM_ETR_POLARITY_NORMAL                           (0x0U << GPTIM_SMCR_ETP_Pos)
#define    FL_GPTIM_ETR_POLARITY_INVERT                           (0x1U << GPTIM_SMCR_ETP_Pos)


#define    FL_GPTIM_ETR_PSC_DIV1                                  (0x0U << GPTIM_SMCR_ETPS_Pos)
#define    FL_GPTIM_ETR_PSC_DIV2                                  (0x1U << GPTIM_SMCR_ETPS_Pos)
#define    FL_GPTIM_ETR_PSC_DIV4                                  (0x2U << GPTIM_SMCR_ETPS_Pos)
#define    FL_GPTIM_ETR_PSC_DIV8                                  (0x3U << GPTIM_SMCR_ETPS_Pos)


#define    FL_GPTIM_ETR_FILTER_DIV1                               (0x0U << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV1_N2                            (0x1U << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV1_N4                            (0x2U << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV1_N8                            (0x3U << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV2_N6                            (0x4U << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV2_N8                            (0x5U << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV4_N6                            (0x6U << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV4_N8                            (0x7U << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV8_N6                            (0x8U << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV8_N8                            (0x9U << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV16_N5                           (0xaU << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV16_N6                           (0xbU << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV16_N8                           (0xcU << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV32_N5                           (0xdU << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV32_N6                           (0xeU << GPTIM_SMCR_ETF_Pos)
#define    FL_GPTIM_ETR_FILTER_DIV32_N8                           (0xfU << GPTIM_SMCR_ETF_Pos)


#define    FL_GPTIM_TIM_TS_ITR0                                   (0x0U << GPTIM_SMCR_TS_Pos)
#define    FL_GPTIM_TIM_TS_ITR1                                   (0x1U << GPTIM_SMCR_TS_Pos)
#define    FL_GPTIM_TIM_TS_ITR2                                   (0x2U << GPTIM_SMCR_TS_Pos)
#define    FL_GPTIM_TIM_TS_ITR3                                   (0x3U << GPTIM_SMCR_TS_Pos)
#define    FL_GPTIM_TIM_TS_TI1F_ED                                (0x4U << GPTIM_SMCR_TS_Pos)
#define    FL_GPTIM_TIM_TS_TI1FP1                                 (0x5U << GPTIM_SMCR_TS_Pos)
#define    FL_GPTIM_TIM_TS_TI2FP2                                 (0x6U << GPTIM_SMCR_TS_Pos)
#define    FL_GPTIM_TIM_TS_ETRF                                   (0x7U << GPTIM_SMCR_TS_Pos)


#define    FL_GPTIM_SLAVE_MODE_PROHIBITED                         (0x0U << GPTIM_SMCR_SMS_Pos)
#define    FL_GPTIM_SLAVE_MODE_ENCODER_X2_TI1                     (0x1U << GPTIM_SMCR_SMS_Pos)
#define    FL_GPTIM_SLAVE_MODE_ENCODER_X2_TI2                     (0x2U << GPTIM_SMCR_SMS_Pos)
#define    FL_GPTIM_SLAVE_MODE_ENCODER_X4_TI1TI2                  (0x3U << GPTIM_SMCR_SMS_Pos)
#define    FL_GPTIM_SLAVE_MODE_TRGI_RISE_RST                      (0x4U << GPTIM_SMCR_SMS_Pos)
#define    FL_GPTIM_SLAVE_MODE_TRGI_HIGH_RUN                      (0x5U << GPTIM_SMCR_SMS_Pos)
#define    FL_GPTIM_SLAVE_MODE_TRGI_RISE_RUN                      (0x6U << GPTIM_SMCR_SMS_Pos)
#define    FL_GPTIM_SLAVE_MODE_TRGI_CLK                           (0x7U << GPTIM_SMCR_SMS_Pos)


#define    FL_GPTIM_DMA_BURST_LENGTH_1                            (0x0U << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_2                            (0x1U << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_3                            (0x2U << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_4                            (0x3U << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_5                            (0x4U << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_6                            (0x5U << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_7                            (0x6U << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_8                            (0x7U << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_9                            (0x8U << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_10                           (0x9U << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_11                           (0xaU << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_12                           (0xbU << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_13                           (0xcU << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_14                           (0xdU << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_15                           (0xeU << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_16                           (0xfU << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_17                           (0x10U << GPTIM_DCR_DBL_Pos)
#define    FL_GPTIM_DMA_BURST_LENGTH_18                           (0x11U << GPTIM_DCR_DBL_Pos)


#define    FL_GPTIM_DMA_BURST_ADDR_CR1                            (0x0U << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_CR2                            (0x1U << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_SMCR                           (0x2U << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_DIER                           (0x3U << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_SR                             (0x4U << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_EGR                            (0x5U << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_CCMR1                          (0x6U << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_CCMR2                          (0x7U << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_CCER                           (0x8U << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_CNT                            (0x9U << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_PSC                            (0xaU << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_ARR                            (0xbU << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_RCR                            (0xcU << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_CCR1                           (0xdU << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_CCR2                           (0xeU << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_CCR3                           (0xfU << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_CCR4                           (0x10U << GPTIM_DCR_DBA_Pos)
#define    FL_GPTIM_DMA_BURST_ADDR_BDTR                           (0x11U << GPTIM_DCR_DBA_Pos)


#define    FL_GPTIM_ITRSEL_GROUP0                                 (0x0U << GPTIM_ITRSEL_Pos)
#define    FL_GPTIM_ITRSEL_GROUP1                                 (0x1U << GPTIM_ITRSEL_Pos)
#define    FL_GPTIM_ITRSEL_GROUP2                                 (0x2U << GPTIM_ITRSEL_Pos)
#define    FL_GPTIM_ITRSEL_GROUP3                                 (0x3U << GPTIM_ITRSEL_Pos)


#define    FL_GPTIM_OC_MODE_FROZEN                                (0x0U << GPTIM_CCMR_OCM_Pos)
#define    FL_GPTIM_OC_MODE_ACTIVE                                (0x1U << GPTIM_CCMR_OCM_Pos)
#define    FL_GPTIM_OC_MODE_INACTIVE                              (0x2U << GPTIM_CCMR_OCM_Pos)
#define    FL_GPTIM_OC_MODE_TOGGLE                                (0x3U << GPTIM_CCMR_OCM_Pos)
#define    FL_GPTIM_OC_MODE_FORCED_INACTIVE                       (0x4U << GPTIM_CCMR_OCM_Pos)
#define    FL_GPTIM_OC_MODE_FORCED_ACTIVE                         (0x5U << GPTIM_CCMR_OCM_Pos)
#define    FL_GPTIM_OC_MODE_PWM1                                  (0x6U << GPTIM_CCMR_OCM_Pos)
#define    FL_GPTIM_OC_MODE_PWM2                                  (0x7U << GPTIM_CCMR_OCM_Pos)


#define    FL_GPTIM_IC_FILTER_DIV1                                (0x0U << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV1_N2                             (0x1U << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV1_N4                             (0x2U << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV1_N8                             (0x3U << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV2_N6                             (0x4U << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV2_N8                             (0x5U << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV4_N6                             (0x6U << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV4_N8                             (0x7U << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV8_N6                             (0x8U << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV8_N8                             (0x9U << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV16_N5                            (0xaU << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV16_N6                            (0xbU << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV16_N8                            (0xcU << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV32_N5                            (0xdU << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV32_N6                            (0xeU << GPTIM_CCMR_ICF_Pos)
#define    FL_GPTIM_IC_FILTER_DIV32_N8                            (0xfU << GPTIM_CCMR_ICF_Pos)


#define    FL_GPTIM_IC_PSC_DIV1                                   (0x0U << GPTIM_CCMR_ICPSC_Pos)
#define    FL_GPTIM_IC_PSC_DIV2                                   (0x1U << GPTIM_CCMR_ICPSC_Pos)
#define    FL_GPTIM_IC_PSC_DIV4                                   (0x2U << GPTIM_CCMR_ICPSC_Pos)
#define    FL_GPTIM_IC_PSC_DIV8                                   (0x3U << GPTIM_CCMR_ICPSC_Pos)


#define    FL_GPTIM_CHANNEL_MODE_OUTPUT                           (0x0U << GPTIM_CCMR_CCS_Pos)
#define    FL_GPTIM_CHANNEL_MODE_INPUT_NORMAL                     (0x1U << GPTIM_CCMR_CCS_Pos)
#define    FL_GPTIM_CHANNEL_MODE_INPUT_CROSSOVER                  (0x2U << GPTIM_CCMR_CCS_Pos)
#define    FL_GPTIM_CHANNEL_MODE_INPUT_TRC                        (0x3U << GPTIM_CCMR_CCS_Pos)


#define    FL_GPTIM_OC_POLARITY_NORMAL                            (0x0U << GPTIM_CCER_CCOP_Pos)
#define    FL_GPTIM_OC_POLARITY_INVERT                            (0x1U << GPTIM_CCER_CCOP_Pos)


#define    FL_GPTIM_IC_POLARITY_NORMAL                            (0x0U << GPTIM_CCER_CCIP_Pos)
#define    FL_GPTIM_IC_POLARITY_INVERT                            (0x1U << GPTIM_CCER_CCIP_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup GPTIM_FL_Exported_Functions GPTIM Exported Functions
  * @{
  */

/**
  * @brief
  * @rmtoll   CR1    CKD    FL_GPTIM_SetClockDivision
  * @param    TIMx TIM instance
  * @param    div This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CLK_DIVISION_DIV1
  *           @arg @ref FL_GPTIM_CLK_DIVISION_DIV2
  *           @arg @ref FL_GPTIM_CLK_DIVISION_DIV4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetClockDivision(GPTIM_Type *TIMx, uint32_t div)
{
    MODIFY_REG(TIMx->CR1, GPTIM_CR1_CKD_Msk, div);
}

/**
  * @brief
  * @rmtoll   CR1    CKD    FL_GPTIM_GetClockDivision
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_CLK_DIVISION_DIV1
  *           @arg @ref FL_GPTIM_CLK_DIVISION_DIV2
  *           @arg @ref FL_GPTIM_CLK_DIVISION_DIV4
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetClockDivision(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, GPTIM_CR1_CKD_Msk));
}

/**
  * @brief
  * @rmtoll   CR1    ARPE    FL_GPTIM_EnableARRPreload
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableARRPreload(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->CR1, GPTIM_CR1_ARPE_Msk);
}

/**
  * @brief
  * @rmtoll   CR1    ARPE    FL_GPTIM_IsEnabledARRPreload
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledARRPreload(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, GPTIM_CR1_ARPE_Msk) == GPTIM_CR1_ARPE_Msk);
}

/**
  * @brief
  * @rmtoll   CR1    ARPE    FL_GPTIM_DisableARRPreload
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableARRPreload(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->CR1, GPTIM_CR1_ARPE_Msk);
}

/**
  * @brief
  * @rmtoll   CR1    CMS    FL_GPTIM_SetCounterAlignedMode
  * @param    TIMx TIM instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_COUNTER_ALIGNED_EDGE
  *           @arg @ref FL_GPTIM_COUNTER_ALIGNED_CENTER_DOWN
  *           @arg @ref FL_GPTIM_COUNTER_ALIGNED_CENTER_UP
  *           @arg @ref FL_GPTIM_COUNTER_ALIGNED_CENTER_UP_DOWN
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetCounterAlignedMode(GPTIM_Type *TIMx, uint32_t mode)
{
    MODIFY_REG(TIMx->CR1, GPTIM_CR1_CMS_Msk, mode);
}

/**
  * @brief
  * @rmtoll   CR1    CMS    FL_GPTIM_GetCounterAlignedMode
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_COUNTER_ALIGNED_EDGE
  *           @arg @ref FL_GPTIM_COUNTER_ALIGNED_CENTER_DOWN
  *           @arg @ref FL_GPTIM_COUNTER_ALIGNED_CENTER_UP
  *           @arg @ref FL_GPTIM_COUNTER_ALIGNED_CENTER_UP_DOWN
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetCounterAlignedMode(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, GPTIM_CR1_CMS_Msk));
}

/**
  * @brief
  * @rmtoll   CR1    DIR    FL_GPTIM_SetCounterDirection
  * @param    TIMx TIM instance
  * @param    dir This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_COUNTER_DIR_UP
  *           @arg @ref FL_GPTIM_COUNTER_DIR_DOWN
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetCounterDirection(GPTIM_Type *TIMx, uint32_t dir)
{
    MODIFY_REG(TIMx->CR1, GPTIM_CR1_DIR_Msk, dir);
}

/**
  * @brief
  * @rmtoll   CR1    DIR    FL_GPTIM_GetCounterDirection
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_COUNTER_DIR_UP
  *           @arg @ref FL_GPTIM_COUNTER_DIR_DOWN
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetCounterDirection(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, GPTIM_CR1_DIR_Msk));
}

/**
  * @brief
  * @rmtoll   CR1    OPM    FL_GPTIM_SetOnePulseMode
  * @param    TIMx TIM instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_ONE_PULSE_MODE_CONTINUOUS
  *           @arg @ref FL_GPTIM_ONE_PULSE_MODE_SINGLE
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetOnePulseMode(GPTIM_Type *TIMx, uint32_t mode)
{
    MODIFY_REG(TIMx->CR1, GPTIM_CR1_OPM_Msk, mode);
}

/**
  * @brief
  * @rmtoll   CR1    OPM    FL_GPTIM_GetOnePulseMode
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_ONE_PULSE_MODE_CONTINUOUS
  *           @arg @ref FL_GPTIM_ONE_PULSE_MODE_SINGLE
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetOnePulseMode(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, GPTIM_CR1_OPM_Msk));
}

/**
  * @brief
  * @rmtoll   CR1    URS    FL_GPTIM_SetUpdateSource
  * @param    TIMx TIM instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_UPDATE_SOURCE_REGULAR
  *           @arg @ref FL_GPTIM_UPDATE_SOURCE_COUNTER
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetUpdateSource(GPTIM_Type *TIMx, uint32_t source)
{
    MODIFY_REG(TIMx->CR1, GPTIM_CR1_URS_Msk, source);
}

/**
  * @brief
  * @rmtoll   CR1    URS    FL_GPTIM_GetUpdateSource
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_UPDATE_SOURCE_REGULAR
  *           @arg @ref FL_GPTIM_UPDATE_SOURCE_COUNTER
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetUpdateSource(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, GPTIM_CR1_URS_Msk));
}

/**
  * @brief
  * @rmtoll   CR1    UDIS    FL_GPTIM_EnableUpdateEvent
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableUpdateEvent(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->CR1, GPTIM_CR1_UDIS_Msk);
}

/**
  * @brief
  * @rmtoll   CR1    UDIS    FL_GPTIM_IsEnabledUpdateEvent
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledUpdateEvent(GPTIM_Type *TIMx)
{
    return (uint32_t)!(READ_BIT(TIMx->CR1, GPTIM_CR1_UDIS_Msk) == GPTIM_CR1_UDIS_Msk);
}

/**
  * @brief
  * @rmtoll   CR1    UDIS    FL_GPTIM_DisableUpdateEvent
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableUpdateEvent(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->CR1, GPTIM_CR1_UDIS_Msk);
}

/**
  * @brief
  * @rmtoll   CR1    CEN    FL_GPTIM_Enable
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_Enable(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->CR1, GPTIM_CR1_CEN_Msk);
}

/**
  * @brief
  * @rmtoll   CR1    CEN    FL_GPTIM_IsEnabled
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabled(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR1, GPTIM_CR1_CEN_Msk) == GPTIM_CR1_CEN_Msk);
}

/**
  * @brief
  * @rmtoll   CR1    CEN    FL_GPTIM_Disable
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_Disable(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->CR1, GPTIM_CR1_CEN_Msk);
}

/**
  * @brief
  * @rmtoll   CR2    TI1S    FL_GPTIM_IC_EnableXORCombination
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_IC_EnableXORCombination(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->CR2, GPTIM_CR2_TI1S_Msk);
}

/**
  * @brief
  * @rmtoll   CR2    TI1S    FL_GPTIM_IC_IsEnabledXORCombination
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IC_IsEnabledXORCombination(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR2, GPTIM_CR2_TI1S_Msk) == GPTIM_CR2_TI1S_Msk);
}

/**
  * @brief
  * @rmtoll   CR2    TI1S    FL_GPTIM_IC_DisableXORCombination
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_IC_DisableXORCombination(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->CR2, GPTIM_CR2_TI1S_Msk);
}

/**
  * @brief
  * @rmtoll   CR2    MMS    FL_GPTIM_SetTriggerOutput
  * @param    TIMx TIM instance
  * @param    triggerOutput This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_TRGO_RESET
  *           @arg @ref FL_GPTIM_TRGO_ENABLE
  *           @arg @ref FL_GPTIM_TRGO_UPDATE
  *           @arg @ref FL_GPTIM_TRGO_CC1IF
  *           @arg @ref FL_GPTIM_TRGO_OC1REF
  *           @arg @ref FL_GPTIM_TRGO_OC2REF
  *           @arg @ref FL_GPTIM_TRGO_OC3REF
  *           @arg @ref FL_GPTIM_TRGO_OC4REF
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetTriggerOutput(GPTIM_Type *TIMx, uint32_t triggerOutput)
{
    MODIFY_REG(TIMx->CR2, GPTIM_CR2_MMS_Msk, triggerOutput);
}

/**
  * @brief
  * @rmtoll   CR2    MMS    FL_GPTIM_GetTriggerOutput
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_TRGO_RESET
  *           @arg @ref FL_GPTIM_TRGO_ENABLE
  *           @arg @ref FL_GPTIM_TRGO_UPDATE
  *           @arg @ref FL_GPTIM_TRGO_CC1IF
  *           @arg @ref FL_GPTIM_TRGO_OC1REF
  *           @arg @ref FL_GPTIM_TRGO_OC2REF
  *           @arg @ref FL_GPTIM_TRGO_OC3REF
  *           @arg @ref FL_GPTIM_TRGO_OC4REF
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetTriggerOutput(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR2, GPTIM_CR2_MMS_Msk));
}

/**
  * @brief
  * @rmtoll   CR2    CCDS    FL_GPTIM_CC_SetDMAReqTrigger
  * @param    TIMx TIM instance
  * @param    trigger This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_DMA_REQ_CC
  *           @arg @ref FL_GPTIM_DMA_REQ_UPDATE
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_CC_SetDMAReqTrigger(GPTIM_Type *TIMx, uint32_t trigger)
{
    MODIFY_REG(TIMx->CR2, GPTIM_CR2_CCDS_Msk, trigger);
}

/**
  * @brief
  * @rmtoll   CR2    CCDS    FL_GPTIM_CC_GetDMAReqTrigger
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_DMA_REQ_CC
  *           @arg @ref FL_GPTIM_DMA_REQ_UPDATE
  */
__STATIC_INLINE uint32_t FL_GPTIM_CC_GetDMAReqTrigger(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CR2, GPTIM_CR2_CCDS_Msk));
}

/**
  * @brief
  * @rmtoll   SMCR    ETP    FL_GPTIM_SetETRPolarity
  * @param    TIMx TIM instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_ETR_POLARITY_NORMAL
  *           @arg @ref FL_GPTIM_ETR_POLARITY_INVERT
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetETRPolarity(GPTIM_Type *TIMx, uint32_t polarity)
{
    MODIFY_REG(TIMx->SMCR, GPTIM_SMCR_ETP_Msk, polarity);
}

/**
  * @brief
  * @rmtoll   SMCR    ETP    FL_GPTIM_GetETRPolarity
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_ETR_POLARITY_NORMAL
  *           @arg @ref FL_GPTIM_ETR_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetETRPolarity(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, GPTIM_SMCR_ETP_Msk));
}

/**
  * @brief
  * @rmtoll   SMCR    ECE    FL_GPTIM_EnableExternalClock
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableExternalClock(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->SMCR, GPTIM_SMCR_ECE_Msk);
}

/**
  * @brief
  * @rmtoll   SMCR    ECE    FL_GPTIM_IsEnabledExternalClock
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledExternalClock(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, GPTIM_SMCR_ECE_Msk) == GPTIM_SMCR_ECE_Msk);
}

/**
  * @brief
  * @rmtoll   SMCR    ECE    FL_GPTIM_DisableExternalClock
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableExternalClock(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->SMCR, GPTIM_SMCR_ECE_Msk);
}

/**
  * @brief
  * @rmtoll   SMCR    ETPS    FL_GPTIM_SetETRPrescaler
  * @param    TIMx TIM instance
  * @param    psc This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_ETR_PSC_DIV1
  *           @arg @ref FL_GPTIM_ETR_PSC_DIV2
  *           @arg @ref FL_GPTIM_ETR_PSC_DIV4
  *           @arg @ref FL_GPTIM_ETR_PSC_DIV8
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetETRPrescaler(GPTIM_Type *TIMx, uint32_t psc)
{
    MODIFY_REG(TIMx->SMCR, GPTIM_SMCR_ETPS_Msk, psc);
}

/**
  * @brief
  * @rmtoll   SMCR    ETPS    FL_GPTIM_GetETRPrescaler
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_ETR_PSC_DIV1
  *           @arg @ref FL_GPTIM_ETR_PSC_DIV2
  *           @arg @ref FL_GPTIM_ETR_PSC_DIV4
  *           @arg @ref FL_GPTIM_ETR_PSC_DIV8
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetETRPrescaler(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, GPTIM_SMCR_ETPS_Msk));
}

/**
  * @brief
  * @rmtoll   SMCR    ETF    FL_GPTIM_SetETRFilter
  * @param    TIMx TIM instance
  * @param    filter This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV1
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV1_N2
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV1_N4
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV1_N8
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV2_N6
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV2_N8
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV4_N6
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV4_N8
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV8_N6
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV8_N8
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV16_N5
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV16_N6
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV16_N8
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV32_N5
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV32_N6
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV32_N8
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetETRFilter(GPTIM_Type *TIMx, uint32_t filter)
{
    MODIFY_REG(TIMx->SMCR, GPTIM_SMCR_ETF_Msk, filter);
}

/**
  * @brief
  * @rmtoll   SMCR    ETF    FL_GPTIM_GetETRFilter
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV1
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV1_N2
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV1_N4
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV1_N8
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV2_N6
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV2_N8
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV4_N6
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV4_N8
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV8_N6
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV8_N8
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV16_N5
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV16_N6
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV16_N8
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV32_N5
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV32_N6
  *           @arg @ref FL_GPTIM_ETR_FILTER_DIV32_N8
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetETRFilter(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, GPTIM_SMCR_ETF_Msk));
}

/**
  * @brief
  * @rmtoll   SMCR    MSM    FL_GPTIM_EnableMasterSlaveMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableMasterSlaveMode(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->SMCR, GPTIM_SMCR_MSM_Msk);
}

/**
  * @brief
  * @rmtoll   SMCR    MSM    FL_GPTIM_IsEnabledMasterSlaveMode
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledMasterSlaveMode(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, GPTIM_SMCR_MSM_Msk) == GPTIM_SMCR_MSM_Msk);
}

/**
  * @brief
  * @rmtoll   SMCR    MSM    FL_GPTIM_DisableMasterSlaveMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableMasterSlaveMode(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->SMCR, GPTIM_SMCR_MSM_Msk);
}

/**
  * @brief
  * @rmtoll   SMCR    TS    FL_GPTIM_SetTriggerInput
  * @param    TIMx TIM instance
  * @param    triggerInput This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_TIM_TS_ITR0
  *           @arg @ref FL_GPTIM_TIM_TS_ITR1
  *           @arg @ref FL_GPTIM_TIM_TS_ITR2
  *           @arg @ref FL_GPTIM_TIM_TS_ITR3
  *           @arg @ref FL_GPTIM_TIM_TS_TI1F_ED
  *           @arg @ref FL_GPTIM_TIM_TS_TI1FP1
  *           @arg @ref FL_GPTIM_TIM_TS_TI2FP2
  *           @arg @ref FL_GPTIM_TIM_TS_ETRF
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetTriggerInput(GPTIM_Type *TIMx, uint32_t triggerInput)
{
    MODIFY_REG(TIMx->SMCR, GPTIM_SMCR_TS_Msk, triggerInput);
}

/**
  * @brief
  * @rmtoll   SMCR    TS    FL_GPTIM_GetTriggerInput
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_TIM_TS_ITR0
  *           @arg @ref FL_GPTIM_TIM_TS_ITR1
  *           @arg @ref FL_GPTIM_TIM_TS_ITR2
  *           @arg @ref FL_GPTIM_TIM_TS_ITR3
  *           @arg @ref FL_GPTIM_TIM_TS_TI1F_ED
  *           @arg @ref FL_GPTIM_TIM_TS_TI1FP1
  *           @arg @ref FL_GPTIM_TIM_TS_TI2FP2
  *           @arg @ref FL_GPTIM_TIM_TS_ETRF
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetTriggerInput(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, GPTIM_SMCR_TS_Msk));
}

/**
  * @brief
  * @rmtoll   SMCR    SMS    FL_GPTIM_SetSlaveMode
  * @param    TIMx TIM instance
  * @param    encoderMode This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_SLAVE_MODE_PROHIBITED
  *           @arg @ref FL_GPTIM_SLAVE_MODE_ENCODER_X2_TI1
  *           @arg @ref FL_GPTIM_SLAVE_MODE_ENCODER_X2_TI2
  *           @arg @ref FL_GPTIM_SLAVE_MODE_ENCODER_X4_TI1TI2
  *           @arg @ref FL_GPTIM_SLAVE_MODE_TRGI_RISE_RST
  *           @arg @ref FL_GPTIM_SLAVE_MODE_TRGI_HIGH_RUN
  *           @arg @ref FL_GPTIM_SLAVE_MODE_TRGI_RISE_RUN
  *           @arg @ref FL_GPTIM_SLAVE_MODE_TRGI_CLK
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetSlaveMode(GPTIM_Type *TIMx, uint32_t encoderMode)
{
    MODIFY_REG(TIMx->SMCR, GPTIM_SMCR_SMS_Msk, encoderMode);
}

/**
  * @brief
  * @rmtoll   SMCR    SMS    FL_GPTIM_GetSlaveMode
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_SLAVE_MODE_PROHIBITED
  *           @arg @ref FL_GPTIM_SLAVE_MODE_ENCODER_X2_TI1
  *           @arg @ref FL_GPTIM_SLAVE_MODE_ENCODER_X2_TI2
  *           @arg @ref FL_GPTIM_SLAVE_MODE_ENCODER_X4_TI1TI2
  *           @arg @ref FL_GPTIM_SLAVE_MODE_TRGI_RISE_RST
  *           @arg @ref FL_GPTIM_SLAVE_MODE_TRGI_HIGH_RUN
  *           @arg @ref FL_GPTIM_SLAVE_MODE_TRGI_RISE_RUN
  *           @arg @ref FL_GPTIM_SLAVE_MODE_TRGI_CLK
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetSlaveMode(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->SMCR, GPTIM_SMCR_SMS_Msk));
}

/**
  * @brief
  * @rmtoll   DIER    CC1BURSTEN    FL_GPTIM_EnableCC1DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableCC1DMABurstMode(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, GPTIM_DIER_CC1BURSTEN_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    CC1BURSTEN    FL_GPTIM_IsEnabledCC1DMABurstMode
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledCC1DMABurstMode(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, GPTIM_DIER_CC1BURSTEN_Msk) == GPTIM_DIER_CC1BURSTEN_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    CC1BURSTEN    FL_GPTIM_DisableCC1DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableCC1DMABurstMode(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, GPTIM_DIER_CC1BURSTEN_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    CC2BURSTEN    FL_GPTIM_EnableCC2DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableCC2DMABurstMode(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, GPTIM_DIER_CC2BURSTEN_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    CC2BURSTEN    FL_GPTIM_IsEnabledCC2DMABurstMode
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledCC2DMABurstMode(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, GPTIM_DIER_CC2BURSTEN_Msk) == GPTIM_DIER_CC2BURSTEN_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    CC2BURSTEN    FL_GPTIM_DisableCC2DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableCC2DMABurstMode(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, GPTIM_DIER_CC2BURSTEN_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    CC3BURSTEN    FL_GPTIM_EnableCC3DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableCC3DMABurstMode(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, GPTIM_DIER_CC3BURSTEN_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    CC3BURSTEN    FL_GPTIM_IsEnabledCC3DMABurstMode
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledCC3DMABurstMode(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, GPTIM_DIER_CC3BURSTEN_Msk) == GPTIM_DIER_CC3BURSTEN_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    CC3BURSTEN    FL_GPTIM_DisableCC3DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableCC3DMABurstMode(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, GPTIM_DIER_CC3BURSTEN_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    CC4BURSTEN    FL_GPTIM_EnableCC4DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableCC4DMABurstMode(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, GPTIM_DIER_CC4BURSTEN_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    CC4BURSTEN    FL_GPTIM_IsEnabledCC4DMABurstMode
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledCC4DMABurstMode(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, GPTIM_DIER_CC4BURSTEN_Msk) == GPTIM_DIER_CC4BURSTEN_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    CC4BURSTEN    FL_GPTIM_DisableCC4DMABurstMode
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableCC4DMABurstMode(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, GPTIM_DIER_CC4BURSTEN_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    TDE    FL_GPTIM_EnableDMAReq_Trigger
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableDMAReq_Trigger(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, GPTIM_DIER_TDE_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    TDE    FL_GPTIM_IsEnabledDMAReq_Trigger
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledDMAReq_Trigger(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, GPTIM_DIER_TDE_Msk) == GPTIM_DIER_TDE_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    TDE    FL_GPTIM_DisableDMAReq_Trigger
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableDMAReq_Trigger(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, GPTIM_DIER_TDE_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    CCDE    FL_GPTIM_EnableDMAReq_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableDMAReq_CC(GPTIM_Type *TIMx, uint32_t channel)
{
    SET_BIT(TIMx->DIER, ((channel & 0xf) << 0x9U));
}

/**
  * @brief
  * @rmtoll   DIER    CCDE    FL_GPTIM_IsEnabledDMAReq_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledDMAReq_CC(GPTIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, ((channel & 0xf) << 0x9U)) == ((channel & 0xf) << 0x9U));
}

/**
  * @brief
  * @rmtoll   DIER    CCDE    FL_GPTIM_DisableDMAReq_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableDMAReq_CC(GPTIM_Type *TIMx, uint32_t channel)
{
    CLEAR_BIT(TIMx->DIER, ((channel & 0xf) << 0x9U));
}

/**
  * @brief
  * @rmtoll   DIER    UDE    FL_GPTIM_EnableDMAReq_Update
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableDMAReq_Update(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, GPTIM_DIER_UDE_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    UDE    FL_GPTIM_IsEnabledDMAReq_Update
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledDMAReq_Update(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, GPTIM_DIER_UDE_Msk) == GPTIM_DIER_UDE_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    UDE    FL_GPTIM_DisableDMAReq_Update
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableDMAReq_Update(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, GPTIM_DIER_UDE_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    TIE    FL_GPTIM_EnableIT_Trigger
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableIT_Trigger(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, GPTIM_DIER_TIE_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    TIE    FL_GPTIM_IsEnabledIT_Trigger
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledIT_Trigger(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, GPTIM_DIER_TIE_Msk) == GPTIM_DIER_TIE_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    TIE    FL_GPTIM_DisableIT_Trigger
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableIT_Trigger(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, GPTIM_DIER_TIE_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    CCIE    FL_GPTIM_EnableIT_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableIT_CC(GPTIM_Type *TIMx, uint32_t channel)
{
    SET_BIT(TIMx->DIER, ((channel & 0xf) << 0x1U));
}

/**
  * @brief
  * @rmtoll   DIER    CCIE    FL_GPTIM_IsEnabledIT_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledIT_CC(GPTIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, ((channel & 0xf) << 0x1U)) == ((channel & 0xf) << 0x1U));
}

/**
  * @brief
  * @rmtoll   DIER    CCIE    FL_GPTIM_DisableIT_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableIT_CC(GPTIM_Type *TIMx, uint32_t channel)
{
    CLEAR_BIT(TIMx->DIER, ((channel & 0xf) << 0x1U));
}

/**
  * @brief
  * @rmtoll   DIER    UIE    FL_GPTIM_EnableIT_Update
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_EnableIT_Update(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->DIER, GPTIM_DIER_UIE_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    UIE    FL_GPTIM_IsEnabledIT_Update
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsEnabledIT_Update(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DIER, GPTIM_DIER_UIE_Msk) == GPTIM_DIER_UIE_Msk);
}

/**
  * @brief
  * @rmtoll   DIER    UIE    FL_GPTIM_DisableIT_Update
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_DisableIT_Update(GPTIM_Type *TIMx)
{
    CLEAR_BIT(TIMx->DIER, GPTIM_DIER_UIE_Msk);
}

/**
  * @brief
  * @rmtoll   ISR    CCOF    FL_GPTIM_IsActiveFlag_CCOverflow
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsActiveFlag_CCOverflow(GPTIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->ISR, ((channel & 0xf) << 0x9U)) == ((channel & 0xf) << 0x9U));
}

/**
  * @brief
  * @rmtoll   ISR    CCOF    FL_GPTIM_ClearFlag_CCOverflow
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_ClearFlag_CCOverflow(GPTIM_Type *TIMx, uint32_t channel)
{
    WRITE_REG(TIMx->ISR, ((channel & 0xf) << 0x9U));
}

/**
  * @brief
  * @rmtoll   ISR    TIF    FL_GPTIM_IsActiveFlag_Trigger
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsActiveFlag_Trigger(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->ISR, GPTIM_ISR_TIF_Msk) == (GPTIM_ISR_TIF_Msk));
}

/**
  * @brief
  * @rmtoll   ISR    TIF    FL_GPTIM_ClearFlag_Trigger
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_ClearFlag_Trigger(GPTIM_Type *TIMx)
{
    WRITE_REG(TIMx->ISR, GPTIM_ISR_TIF_Msk);
}

/**
  * @brief
  * @rmtoll   ISR    CCIF    FL_GPTIM_IsActiveFlag_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsActiveFlag_CC(GPTIM_Type *TIMx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(TIMx->ISR, ((channel & 0xf) << 0x1U)) == ((channel & 0xf) << 0x1U));
}

/**
  * @brief
  * @rmtoll   ISR    CCIF    FL_GPTIM_ClearFlag_CC
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_ClearFlag_CC(GPTIM_Type *TIMx, uint32_t channel)
{
    WRITE_REG(TIMx->ISR, ((channel & 0xf) << 0x1U));
}

/**
  * @brief
  * @rmtoll   ISR    UIF    FL_GPTIM_IsActiveFlag_Update
  * @param    TIMx TIM instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IsActiveFlag_Update(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->ISR, GPTIM_ISR_UIF_Msk) == (GPTIM_ISR_UIF_Msk));
}

/**
  * @brief
  * @rmtoll   ISR    UIF    FL_GPTIM_ClearFlag_Update
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_ClearFlag_Update(GPTIM_Type *TIMx)
{
    WRITE_REG(TIMx->ISR, GPTIM_ISR_UIF_Msk);
}

/**
  * @brief
  * @rmtoll   EGR    TG    FL_GPTIM_GenerateTriggerEvent
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_GenerateTriggerEvent(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->EGR, GPTIM_EGR_TG_Msk);
}

/**
  * @brief
  * @rmtoll   EGR    CCG    FL_GPTIM_GenerateCCEvent
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_GenerateCCEvent(GPTIM_Type *TIMx, uint32_t channel)
{
    SET_BIT(TIMx->EGR, ((channel & 0x3) << 0x1U));
}

/**
  * @brief
  * @rmtoll   EGR    UG    FL_GPTIM_GenerateUpdateEvent
  * @param    TIMx TIM instance
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_GenerateUpdateEvent(GPTIM_Type *TIMx)
{
    SET_BIT(TIMx->EGR, GPTIM_EGR_UG_Msk);
}

/**
  * @brief
  * @rmtoll   CNT        FL_GPTIM_WriteCounter
  * @param    TIMx TIM instance
  * @param    counter
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_WriteCounter(GPTIM_Type *TIMx, uint32_t counter)
{
    MODIFY_REG(TIMx->CNT, (0xffffU << 0U), (counter << 0U));
}

/**
  * @brief
  * @rmtoll   CNT        FL_GPTIM_ReadCounter
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_GPTIM_ReadCounter(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CNT, 0xffffU) >> 0U);
}

/**
  * @brief
  * @rmtoll   PSC        FL_GPTIM_WritePrescaler
  * @param    TIMx TIM instance
  * @param    psc
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_WritePrescaler(GPTIM_Type *TIMx, uint32_t psc)
{
    MODIFY_REG(TIMx->PSC, (0xffffU << 0U), (psc << 0U));
}

/**
  * @brief
  * @rmtoll   PSC        FL_GPTIM_ReadPrescaler
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_GPTIM_ReadPrescaler(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->PSC, 0xffffU) >> 0U);
}

/**
  * @brief
  * @rmtoll   ARR        FL_GPTIM_WriteAutoReload
  * @param    TIMx TIM instance
  * @param    autoReload
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_WriteAutoReload(GPTIM_Type *TIMx, uint32_t autoReload)
{
    MODIFY_REG(TIMx->ARR, (0xffffU << 0U), (autoReload << 0U));
}

/**
  * @brief
  * @rmtoll   ARR        FL_GPTIM_ReadAutoReload
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_GPTIM_ReadAutoReload(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->ARR, 0xffffU) >> 0U);
}

/**
  * @brief
  * @rmtoll   CCR1        FL_GPTIM_WriteCompareCH1
  * @param    TIMx TIM instance
  * @param    compareValue
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_WriteCompareCH1(GPTIM_Type *TIMx, uint32_t compareValue)
{
    MODIFY_REG(TIMx->CCR1, (0xffffU << 0U), (compareValue << 0U));
}

/**
  * @brief
  * @rmtoll   CCR1        FL_GPTIM_ReadCompareCH1
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_GPTIM_ReadCompareCH1(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CCR1, 0xffffU) >> 0U);
}

/**
  * @brief
  * @rmtoll   CCR2        FL_GPTIM_WriteCompareCH2
  * @param    TIMx TIM instance
  * @param    compareValue
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_WriteCompareCH2(GPTIM_Type *TIMx, uint32_t compareValue)
{
    MODIFY_REG(TIMx->CCR2, (0xffffU << 0U), (compareValue << 0U));
}

/**
  * @brief
  * @rmtoll   CCR2        FL_GPTIM_ReadCompareCH2
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_GPTIM_ReadCompareCH2(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CCR2, 0xffffU) >> 0U);
}

/**
  * @brief
  * @rmtoll   CCR3        FL_GPTIM_WriteCompareCH3
  * @param    TIMx TIM instance
  * @param    compareValue
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_WriteCompareCH3(GPTIM_Type *TIMx, uint32_t compareValue)
{
    MODIFY_REG(TIMx->CCR3, (0xffffU << 0U), (compareValue << 0U));
}

/**
  * @brief
  * @rmtoll   CCR3        FL_GPTIM_ReadCompareCH3
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_GPTIM_ReadCompareCH3(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CCR3, 0xffffU) >> 0U);
}

/**
  * @brief
  * @rmtoll   CCR4        FL_GPTIM_WriteCompareCH4
  * @param    TIMx TIM instance
  * @param    compareValue
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_WriteCompareCH4(GPTIM_Type *TIMx, uint32_t compareValue)
{
    MODIFY_REG(TIMx->CCR4, (0xffffU << 0U), (compareValue << 0U));
}

/**
  * @brief
  * @rmtoll   CCR4        FL_GPTIM_ReadCompareCH4
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_GPTIM_ReadCompareCH4(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->CCR4, 0xffffU) >> 0U);
}

/**
  * @brief
  * @rmtoll   DCR    DBL    FL_GPTIM_SetDMABurstLength
  * @param    TIMx TIM instance
  * @param    length This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_1
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_2
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_3
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_4
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_5
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_6
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_7
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_8
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_9
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_10
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_11
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_12
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_13
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_14
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_15
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_16
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_17
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_18
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetDMABurstLength(GPTIM_Type *TIMx, uint32_t length)
{
    MODIFY_REG(TIMx->DCR, GPTIM_DCR_DBL_Msk, length);
}

/**
  * @brief
  * @rmtoll   DCR    DBL    FL_GPTIM_GetDMABurstLength
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_1
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_2
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_3
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_4
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_5
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_6
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_7
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_8
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_9
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_10
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_11
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_12
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_13
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_14
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_15
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_16
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_17
  *           @arg @ref FL_GPTIM_DMA_BURST_LENGTH_18
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetDMABurstLength(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DCR, GPTIM_DCR_DBL_Msk));
}

/**
  * @brief
  * @rmtoll   DCR    DBA    FL_GPTIM_SetDMABurstAddress
  * @param    TIMx TIM instance
  * @param    address This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CR1
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CR2
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_SMCR
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_DIER
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_SR
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_EGR
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCMR1
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCMR2
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCER
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CNT
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_PSC
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_ARR
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_RCR
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCR1
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCR2
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCR3
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCR4
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_BDTR
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetDMABurstAddress(GPTIM_Type *TIMx, uint32_t address)
{
    MODIFY_REG(TIMx->DCR, GPTIM_DCR_DBA_Msk, address);
}

/**
  * @brief
  * @rmtoll   DCR    DBA    FL_GPTIM_GetDMABurstAddress
  * @param    TIMx TIM instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CR1
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CR2
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_SMCR
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_DIER
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_SR
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_EGR
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCMR1
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCMR2
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCER
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CNT
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_PSC
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_ARR
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_RCR
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCR1
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCR2
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCR3
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_CCR4
  *           @arg @ref FL_GPTIM_DMA_BURST_ADDR_BDTR
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetDMABurstAddress(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DCR, GPTIM_DCR_DBA_Msk));
}

/**
  * @brief
  * @rmtoll   DMAR        FL_GPTIM_WriteDMAAddress
  * @param    TIMx TIM instance
  * @param    address
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_WriteDMAAddress(GPTIM_Type *TIMx, uint32_t address)
{
    MODIFY_REG(TIMx->DMAR, (0xffffU << 0U), (address << 0U));
}

/**
  * @brief
  * @rmtoll   DMAR        FL_GPTIM_ReadDMAAddress
  * @param    TIMx TIM instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_GPTIM_ReadDMAAddress(GPTIM_Type *TIMx)
{
    return (uint32_t)(READ_BIT(TIMx->DMAR, 0xffffU) >> 0U);
}

/**
  * @brief
  * @rmtoll   ITRSEL        FL_GPTIM_SetITRInput
  * @param    TIMx TIM instance
  * @param    ITRx This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_ITR0
  *           @arg @ref FL_GPTIM_ITR1
  *           @arg @ref FL_GPTIM_ITR2
  *           @arg @ref FL_GPTIM_ITR3
  * @param    input This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_ITRSEL_GROUP0
  *           @arg @ref FL_GPTIM_ITRSEL_GROUP1
  *           @arg @ref FL_GPTIM_ITRSEL_GROUP2
  *           @arg @ref FL_GPTIM_ITRSEL_GROUP3
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_SetITRInput(GPTIM_Type *TIMx, uint32_t ITRx, uint32_t input)
{
    MODIFY_REG(TIMx->ITRSEL, ((ITRx * ITRx) * GPTIM_ITRSEL), ((ITRx * ITRx) * input));
}

/**
  * @brief
  * @rmtoll   ITRSEL        FL_GPTIM_GetITRInput
  * @param    TIMx TIM instance
  * @param    ITRx This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_ITR0
  *           @arg @ref FL_GPTIM_ITR1
  *           @arg @ref FL_GPTIM_ITR2
  *           @arg @ref FL_GPTIM_ITR3
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_ITRSEL_GROUP0
  *           @arg @ref FL_GPTIM_ITRSEL_GROUP1
  *           @arg @ref FL_GPTIM_ITRSEL_GROUP2
  *           @arg @ref FL_GPTIM_ITRSEL_GROUP3
  */
__STATIC_INLINE uint32_t FL_GPTIM_GetITRInput(GPTIM_Type *TIMx, uint32_t ITRx)
{
    return (uint32_t)(READ_BIT(TIMx->ITRSEL, ((ITRx * ITRx) * GPTIM_ITRSEL)) / (ITRx * ITRx));
}

/**
  * @brief    OCx clear enable
  * @rmtoll   CCMR    OCCE    FL_GPTIM_OC_EnableClear
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_OC_EnableClear(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            MODIFY_REG(TIMx->CCMR1, (0x1U << 7U), (0x1U << 7U));
            break;
        case FL_GPTIM_CHANNEL_2:
            MODIFY_REG(TIMx->CCMR1, (0x1U << 15U), (0x1U << 15U));
            break;
        case FL_GPTIM_CHANNEL_3:
            MODIFY_REG(TIMx->CCMR2, (0x1U << 7U), (0x1U << 7U));
            break;
        case FL_GPTIM_CHANNEL_4:
            MODIFY_REG(TIMx->CCMR2, (0x1U << 15U), (0x1U << 15U));
            break;
    }
}

/**
  * @brief    Get OCx Clear enable status
  * @rmtoll   CCMR    OCCE    FL_GPTIM_OC_IsEnabledClear
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_OC_IsEnabledClear(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0x1U << 7U)) >> 7U);
        case FL_GPTIM_CHANNEL_2:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0x1U << 15U)) >> 15U);
        case FL_GPTIM_CHANNEL_3:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0x1U << 7U)) >> 7U);
        case FL_GPTIM_CHANNEL_4:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0x1U << 15U)) >> 15U);
        default:
            return 0;
    }
}

/**
  * @brief    OCx clear disable
  * @rmtoll   CCMR    OCCE    FL_GPTIM_OC_DisableClear
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_OC_DisableClear(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            CLEAR_BIT(TIMx->CCMR1, (0x1U << 7U));
            break;
        case FL_GPTIM_CHANNEL_2:
            CLEAR_BIT(TIMx->CCMR1, (0x1U << 15U));
            break;
        case FL_GPTIM_CHANNEL_3:
            CLEAR_BIT(TIMx->CCMR2, (0x1U << 7U));
            break;
        case FL_GPTIM_CHANNEL_4:
            CLEAR_BIT(TIMx->CCMR2, (0x1U << 15U));
            break;
    }
}

/**
  * @brief    Set OCx mode
  * @rmtoll   CCMR    OCM    FL_GPTIM_OC_SetMode
  * @param    TIMx TIM instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_OC_MODE_FROZEN
  *           @arg @ref FL_GPTIM_OC_MODE_ACTIVE
  *           @arg @ref FL_GPTIM_OC_MODE_INACTIVE
  *           @arg @ref FL_GPTIM_OC_MODE_TOGGLE
  *           @arg @ref FL_GPTIM_OC_MODE_FORCED_INACTIVE
  *           @arg @ref FL_GPTIM_OC_MODE_FORCED_ACTIVE
  *           @arg @ref FL_GPTIM_OC_MODE_PWM1
  *           @arg @ref FL_GPTIM_OC_MODE_PWM2
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_OC_SetMode(GPTIM_Type *TIMx, uint32_t mode, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            MODIFY_REG(TIMx->CCMR1, (0x7U << 4U), (mode));
            break;
        case FL_GPTIM_CHANNEL_2:
            MODIFY_REG(TIMx->CCMR1, (0x7U << 12U), (mode << 8U));
            break;
        case FL_GPTIM_CHANNEL_3:
            MODIFY_REG(TIMx->CCMR2, (0x7U << 4U), (mode));
            break;
        case FL_GPTIM_CHANNEL_4:
            MODIFY_REG(TIMx->CCMR2, (0x7U << 12U), (mode << 8U));
            break;
    }
}

/**
  * @brief    Get OCx mode value
  * @rmtoll   CCMR    OCM    FL_GPTIM_OC_GetMode
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_OC_MODE_FROZEN
  *           @arg @ref FL_GPTIM_OC_MODE_ACTIVE
  *           @arg @ref FL_GPTIM_OC_MODE_INACTIVE
  *           @arg @ref FL_GPTIM_OC_MODE_TOGGLE
  *           @arg @ref FL_GPTIM_OC_MODE_FORCED_INACTIVE
  *           @arg @ref FL_GPTIM_OC_MODE_FORCED_ACTIVE
  *           @arg @ref FL_GPTIM_OC_MODE_PWM1
  *           @arg @ref FL_GPTIM_OC_MODE_PWM2
  */
__STATIC_INLINE uint32_t FL_GPTIM_OC_GetMode(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0x7U << 4U)) >> 0U);
        case FL_GPTIM_CHANNEL_2:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0x7U << 12U)) >> 8U);
        case FL_GPTIM_CHANNEL_3:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0x7U << 4U)) >> 0U);
        case FL_GPTIM_CHANNEL_4:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0x7U << 12U)) >> 8U);
        default:
            return 0;
    }
}

/**
  * @brief
  * @rmtoll   CCMR    OCPE    FL_GPTIM_OC_EnablePreload
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_OC_EnablePreload(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            SET_BIT(TIMx->CCMR1, (0x1U << 3U));
            break;
        case FL_GPTIM_CHANNEL_2:
            SET_BIT(TIMx->CCMR1, (0x1U << 11U));
            break;
        case FL_GPTIM_CHANNEL_3:
            SET_BIT(TIMx->CCMR2, (0x1U << 3U));
            break;
        case FL_GPTIM_CHANNEL_4:
            SET_BIT(TIMx->CCMR2, (0x1U << 11U));
            break;
    }
}

/**
  * @brief
  * @rmtoll   CCMR    OCPE    FL_GPTIM_OC_IsEnabledPreload
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_OC_IsEnabledPreload(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0x1U << 3U)) >> 3U);
        case FL_GPTIM_CHANNEL_2:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0x1U << 11U)) >> 11U);
        case FL_GPTIM_CHANNEL_3:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0x1U << 3U)) >> 3U);
        case FL_GPTIM_CHANNEL_4:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0x1U << 11U)) >> 11U);
        default:
            return 0;
    }
}

/**
  * @brief
  * @rmtoll   CCMR    OCPE    FL_GPTIM_OC_DisablePreload
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_OC_DisablePreload(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            CLEAR_BIT(TIMx->CCMR1, (0x1U << 3U));
            break;
        case FL_GPTIM_CHANNEL_2:
            CLEAR_BIT(TIMx->CCMR1, (0x1U << 11U));
            break;
        case FL_GPTIM_CHANNEL_3:
            CLEAR_BIT(TIMx->CCMR2, (0x1U << 3U));
            break;
        case FL_GPTIM_CHANNEL_4:
            CLEAR_BIT(TIMx->CCMR2, (0x1U << 11U));
            break;
    }
}

/**
  * @brief
  * @rmtoll   CCMR    OCFE    FL_GPTIM_OC_EnableFastMode
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_OC_EnableFastMode(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            SET_BIT(TIMx->CCMR1, (0x1U << 2U));
            break;
        case FL_GPTIM_CHANNEL_2:
            SET_BIT(TIMx->CCMR1, (0x1U << 10U));
            break;
        case FL_GPTIM_CHANNEL_3:
            SET_BIT(TIMx->CCMR2, (0x1U << 2U));
            break;
        case FL_GPTIM_CHANNEL_4:
            SET_BIT(TIMx->CCMR2, (0x1U << 10U));
            break;
    }
}

/**
  * @brief
  * @rmtoll   CCMR    OCFE    FL_GPTIM_OC_IsEnabledFastMode
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_OC_IsEnabledFastMode(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0x1U << 2U)) >> 2U);
        case FL_GPTIM_CHANNEL_2:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0x1U << 10U)) >> 10U);
        case FL_GPTIM_CHANNEL_3:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0x1U << 2U)) >> 2U);
        case FL_GPTIM_CHANNEL_4:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0x1U << 10U)) >> 10U);
        default:
            return 0;
    }
}

/**
  * @brief
  * @rmtoll   CCMR    OCFE    FL_GPTIM_OC_DisableFastMode
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_OC_DisableFastMode(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            CLEAR_BIT(TIMx->CCMR1, (0x1U << 2U));
            break;
        case FL_GPTIM_CHANNEL_2:
            CLEAR_BIT(TIMx->CCMR1, (0x1U << 10U));
            break;
        case FL_GPTIM_CHANNEL_3:
            CLEAR_BIT(TIMx->CCMR2, (0x1U << 2U));
            break;
        case FL_GPTIM_CHANNEL_4:
            CLEAR_BIT(TIMx->CCMR2, (0x1U << 10U));
            break;
    }
}

/**
  * @brief
  * @rmtoll   CCMR    ICF    FL_GPTIM_IC_SetFilter
  * @param    TIMx TIM instance
  * @param    filter This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV1
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV1_N2
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV1_N4
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV1_N8
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV2_N6
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV2_N8
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV4_N6
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV4_N8
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV8_N6
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV8_N8
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV16_N5
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV16_N6
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV16_N8
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV32_N5
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV32_N6
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV32_N8
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_IC_SetFilter(GPTIM_Type *TIMx, uint32_t filter, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            MODIFY_REG(TIMx->CCMR1, (0xFU << 4U), (filter));
            break;
        case FL_GPTIM_CHANNEL_2:
            MODIFY_REG(TIMx->CCMR1, (0xFU << 12U), (filter << 8U));
            break;
        case FL_GPTIM_CHANNEL_3:
            MODIFY_REG(TIMx->CCMR2, (0xFU << 4U), (filter));
            break;
        case FL_GPTIM_CHANNEL_4:
            MODIFY_REG(TIMx->CCMR2, (0xFU << 12U), (filter << 8U));
            break;
    }
}

/**
  * @brief
  * @rmtoll   CCMR    ICF    FL_GPTIM_IC_GetFilter
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV1
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV1_N2
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV1_N4
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV1_N8
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV2_N6
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV2_N8
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV4_N6
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV4_N8
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV8_N6
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV8_N8
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV16_N5
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV16_N6
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV16_N8
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV32_N5
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV32_N6
  *           @arg @ref FL_GPTIM_IC_FILTER_DIV32_N8
  */
__STATIC_INLINE uint32_t FL_GPTIM_IC_GetFilter(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0xFU << 4U)) >> 0U);
        case FL_GPTIM_CHANNEL_2:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0xFU << 12U)) >> 8U);
        case FL_GPTIM_CHANNEL_3:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0xFU << 4U)) >> 0U);
        case FL_GPTIM_CHANNEL_4:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0xFU << 12U)) >> 8U);
        default:
            return 0;
    }
}

/**
  * @brief
  * @rmtoll   CCMR    ICPSC    FL_GPTIM_IC_SetPrescaler
  * @param    TIMx TIM instance
  * @param    psc This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_IC_PSC_DIV1
  *           @arg @ref FL_GPTIM_IC_PSC_DIV2
  *           @arg @ref FL_GPTIM_IC_PSC_DIV4
  *           @arg @ref FL_GPTIM_IC_PSC_DIV8
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_IC_SetPrescaler(GPTIM_Type *TIMx, uint32_t psc, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            MODIFY_REG(TIMx->CCMR1, (0x3U << 2U), (psc));
            break;
        case FL_GPTIM_CHANNEL_2:
            MODIFY_REG(TIMx->CCMR1, (0x3U << 10U), (psc << 8U));
            break;
        case FL_GPTIM_CHANNEL_3:
            MODIFY_REG(TIMx->CCMR2, (0x3U << 2U), (psc));
            break;
        case FL_GPTIM_CHANNEL_4:
            MODIFY_REG(TIMx->CCMR2, (0x3U << 10U), (psc << 8U));
            break;
    }
}

/**
  * @brief
  * @rmtoll   CCMR    ICPSC    FL_GPTIM_IC_GetPrescaler
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_IC_PSC_DIV1
  *           @arg @ref FL_GPTIM_IC_PSC_DIV2
  *           @arg @ref FL_GPTIM_IC_PSC_DIV4
  *           @arg @ref FL_GPTIM_IC_PSC_DIV8
  */
__STATIC_INLINE uint32_t FL_GPTIM_IC_GetPrescaler(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0x3U << 2U)) >> 0U);
        case FL_GPTIM_CHANNEL_2:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0x3U << 10U)) >> 8U);
        case FL_GPTIM_CHANNEL_3:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0x3U << 2U)) >> 0U);
        case FL_GPTIM_CHANNEL_4:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0x3U << 10U)) >> 8U);
        default:
            return 0;
    }
}

/**
  * @brief
  * @rmtoll   CCMR    CCS    FL_GPTIM_CC_SetChannelMode
  * @param    TIMx TIM instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_MODE_OUTPUT
  *           @arg @ref FL_GPTIM_CHANNEL_MODE_INPUT_NORMAL
  *           @arg @ref FL_GPTIM_CHANNEL_MODE_INPUT_CROSSOVER
  *           @arg @ref FL_GPTIM_CHANNEL_MODE_INPUT_TRC
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_CC_SetChannelMode(GPTIM_Type *TIMx, uint32_t mode, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            MODIFY_REG(TIMx->CCMR1, (0x3U << 0U), (mode));
            break;
        case FL_GPTIM_CHANNEL_2:
            MODIFY_REG(TIMx->CCMR1, (0x3U << 8U), (mode << 8U));
            break;
        case FL_GPTIM_CHANNEL_3:
            MODIFY_REG(TIMx->CCMR2, (0x3U << 0U), (mode));
            break;
        case FL_GPTIM_CHANNEL_4:
            MODIFY_REG(TIMx->CCMR2, (0x3U << 8U), (mode << 8U));
            break;
    }
}

/**
  * @brief
  * @rmtoll   CCMR    CCS    FL_GPTIM_CC_GetChannelMode
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_MODE_OUTPUT
  *           @arg @ref FL_GPTIM_CHANNEL_MODE_INPUT_NORMAL
  *           @arg @ref FL_GPTIM_CHANNEL_MODE_INPUT_CROSSOVER
  *           @arg @ref FL_GPTIM_CHANNEL_MODE_INPUT_TRC
  */
__STATIC_INLINE uint32_t FL_GPTIM_CC_GetChannelMode(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0x3U << 0U)) >> 0U);
        case FL_GPTIM_CHANNEL_2:
            return (uint32_t)(READ_BIT(TIMx->CCMR1, (0x3U << 8U)) >> 8U);
        case FL_GPTIM_CHANNEL_3:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0x3U << 0U)) >> 0U);
        case FL_GPTIM_CHANNEL_4:
            return (uint32_t)(READ_BIT(TIMx->CCMR2, (0x3U << 8U)) >> 8U);
        default:
            return 0;
    }
}

/**
  * @brief
  * @rmtoll   CCER    CCOP    FL_GPTIM_OC_SetChannelPolarity
  * @param    TIMx TIM instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_OC_POLARITY_NORMAL
  *           @arg @ref FL_GPTIM_OC_POLARITY_INVERT
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_OC_SetChannelPolarity(GPTIM_Type *TIMx, uint32_t polarity, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            MODIFY_REG(TIMx->CCER, (0x1U << 1U), (polarity));
            break;
        case FL_GPTIM_CHANNEL_2:
            MODIFY_REG(TIMx->CCER, (0x1U << 5U), (polarity << 4U));
            break;
        case FL_GPTIM_CHANNEL_3:
            MODIFY_REG(TIMx->CCER, (0x1U << 9U), (polarity << 8U));
            break;
        case FL_GPTIM_CHANNEL_4:
            MODIFY_REG(TIMx->CCER, (0x1U << 13U), (polarity << 12U));
            break;
    }
}

/**
  * @brief
  * @rmtoll   CCER    CCOP    FL_GPTIM_OC_GetChannelPolarity
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_OC_POLARITY_NORMAL
  *           @arg @ref FL_GPTIM_OC_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_GPTIM_OC_GetChannelPolarity(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 1U)) >> 0U);
        case FL_GPTIM_CHANNEL_2:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 5U)) >> 4U);
        case FL_GPTIM_CHANNEL_3:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 9U)) >> 8U);
        case FL_GPTIM_CHANNEL_4:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 13U)) >> 12U);
        default:
            return 0;
    }
}

/**
  * @brief
  * @rmtoll   CCER    CCIP    FL_GPTIM_IC_SetChannelPolarity
  * @param    TIMx TIM instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_IC_POLARITY_NORMAL
  *           @arg @ref FL_GPTIM_IC_POLARITY_INVERT
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_IC_SetChannelPolarity(GPTIM_Type *TIMx, uint32_t polarity, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            MODIFY_REG(TIMx->CCER, (0x1U << 1U), (polarity));
            break;
        case FL_GPTIM_CHANNEL_2:
            MODIFY_REG(TIMx->CCER, (0x1U << 5U), (polarity << 4U));
            break;
        case FL_GPTIM_CHANNEL_3:
            MODIFY_REG(TIMx->CCER, (0x1U << 9U), (polarity << 8U));
            break;
        case FL_GPTIM_CHANNEL_4:
            MODIFY_REG(TIMx->CCER, (0x1U << 13U), (polarity << 12U));
            break;
    }
}

/**
  * @brief
  * @rmtoll   CCER    CCIP    FL_GPTIM_IC_GetChannelPolarity
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPTIM_IC_POLARITY_NORMAL
  *           @arg @ref FL_GPTIM_IC_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_GPTIM_IC_GetChannelPolarity(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 1U)) >> 0U);
        case FL_GPTIM_CHANNEL_2:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 5U)) >> 4U);
        case FL_GPTIM_CHANNEL_3:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 9U)) >> 8U);
        case FL_GPTIM_CHANNEL_4:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 13U)) >> 12U);
        default:
            return 0;
    }
}

/**
  * @brief
  * @rmtoll   CCER    CCE    FL_GPTIM_OC_EnableChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_OC_EnableChannel(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            SET_BIT(TIMx->CCER, (0x1U << 0U));
            break;
        case FL_GPTIM_CHANNEL_2:
            SET_BIT(TIMx->CCER, (0x1U << 4U));
            break;
        case FL_GPTIM_CHANNEL_3:
            SET_BIT(TIMx->CCER, (0x1U << 8U));
            break;
        case FL_GPTIM_CHANNEL_4:
            SET_BIT(TIMx->CCER, (0x1U << 12U));
            break;
    }
}

/**
  * @brief
  * @rmtoll   CCER    CCE    FL_GPTIM_OC_IsEnabledChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_OC_IsEnabledChannel(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 0U)) >> 0U);
        case FL_GPTIM_CHANNEL_2:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 4U)) >> 4U);
        case FL_GPTIM_CHANNEL_3:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 8U)) >> 8U);
        case FL_GPTIM_CHANNEL_4:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 12U)) >> 12U);
        default:
            return 0;
    }
}

/**
  * @brief
  * @rmtoll   CCER    CCE    FL_GPTIM_OC_DisableChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_OC_DisableChannel(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            CLEAR_BIT(TIMx->CCER, (0x1U << 0U));
            break;
        case FL_GPTIM_CHANNEL_2:
            CLEAR_BIT(TIMx->CCER, (0x1U << 4U));
            break;
        case FL_GPTIM_CHANNEL_3:
            CLEAR_BIT(TIMx->CCER, (0x1U << 8U));
            break;
        case FL_GPTIM_CHANNEL_4:
            CLEAR_BIT(TIMx->CCER, (0x1U << 12U));
            break;
    }
}

/**
  * @brief
  * @rmtoll   CCER    CCE    FL_GPTIM_IC_EnableChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_IC_EnableChannel(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            SET_BIT(TIMx->CCER, (0x1U << 0U));
            break;
        case FL_GPTIM_CHANNEL_2:
            SET_BIT(TIMx->CCER, (0x1U << 4U));
            break;
        case FL_GPTIM_CHANNEL_3:
            SET_BIT(TIMx->CCER, (0x1U << 8U));
            break;
        case FL_GPTIM_CHANNEL_4:
            SET_BIT(TIMx->CCER, (0x1U << 12U));
            break;
    }
}

/**
  * @brief
  * @rmtoll   CCER    CCE    FL_GPTIM_IC_IsEnabledChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPTIM_IC_IsEnabledChannel(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 0U)) >> 0U);
        case FL_GPTIM_CHANNEL_2:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 4U)) >> 4U);
        case FL_GPTIM_CHANNEL_3:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 8U)) >> 8U);
        case FL_GPTIM_CHANNEL_4:
            return (uint32_t)(READ_BIT(TIMx->CCER, (0x1U << 12U)) >> 12U);
        default:
            return 0;
    }
}

/**
  * @brief
  * @rmtoll   CCER    CCE    FL_GPTIM_IC_DisableChannel
  * @param    TIMx TIM instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_GPTIM_CHANNEL_1
  *           @arg @ref FL_GPTIM_CHANNEL_2
  *           @arg @ref FL_GPTIM_CHANNEL_3
  *           @arg @ref FL_GPTIM_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_GPTIM_IC_DisableChannel(GPTIM_Type *TIMx, uint32_t channel)
{
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            CLEAR_BIT(TIMx->CCER, (0x1U << 0U));
            break;
        case FL_GPTIM_CHANNEL_2:
            CLEAR_BIT(TIMx->CCER, (0x1U << 4U));
            break;
        case FL_GPTIM_CHANNEL_3:
            CLEAR_BIT(TIMx->CCER, (0x1U << 8U));
            break;
        case FL_GPTIM_CHANNEL_4:
            CLEAR_BIT(TIMx->CCER, (0x1U << 12U));
            break;
    }
}

/**
  * @}
  */

/** @defgroup GPTIM_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_GPTIM_DeInit(GPTIM_Type *TIMx);

void FL_GPTIM_StructInit(FL_GPTIM_InitTypeDef *init);
void FL_GPTIM_SlaveMode_StructInit(FL_GPTIM_SlaveInitTypeDef *slave_init);
void FL_GPTIM_OC_StructInit(FL_GPTIM_OC_InitTypeDef *oc_init);
void FL_GPTIM_IC_StructInit(FL_GPTIM_IC_InitTypeDef *ic_init);
void FL_GPTIM_ETR_StructInit(FL_GPTIM_ETR_InitTypeDef *etr_init);

FL_ErrorStatus FL_GPTIM_Init(GPTIM_Type *TIMx, FL_GPTIM_InitTypeDef *init);
FL_ErrorStatus FL_GPTIM_SlaveMode_Init(GPTIM_Type *TIMx, FL_GPTIM_SlaveInitTypeDef *slave_init);
FL_ErrorStatus FL_GPTIM_OC_Init(GPTIM_Type *TIMx, uint32_t channel, FL_GPTIM_OC_InitTypeDef *oc_init);
FL_ErrorStatus FL_GPTIM_IC_Init(GPTIM_Type *TIMx, uint32_t channel, FL_GPTIM_IC_InitTypeDef *ic_init);
FL_ErrorStatus FL_GPTIM_ETR_Init(GPTIM_Type *TIMx, FL_GPTIM_ETR_InitTypeDef *etr_init);

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

#endif /* __FM33LC0XX_FL_GPTIM_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-23*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
