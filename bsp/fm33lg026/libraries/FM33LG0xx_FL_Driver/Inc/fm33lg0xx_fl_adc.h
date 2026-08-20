/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_adc.h
  * @author  FMSH Application Team
  * @brief   Head file of ADC FL Module
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
#ifndef __FM33LG0XX_FL_ADC_H
#define __FM33LG0XX_FL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup ADC ADC
 * @brief ADC FL driver
 * @{
 */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup ADC_FL_ES_INIT ADC Exported Init structures
  * @{
  */
#define ADC_VREF    (*((uint16_t *)(0x1FFFFB08)))    /*  vref122定标值 */
#define ADC_TS      (*((uint16_t *)(0x1FFFFB12)))    /*  PTAT定标值 */

/**
  * @brief FL ADC Init Sturcture definition
  */
typedef struct
{
    /** ADC工作时钟源选择 */
    uint32_t clockSource;
    /** ADCCLK预分频配置 */
    uint32_t clockPrescaler;
    /** ADC基准源选择 */
    uint32_t referenceSource;
    /** ADC数据位选择 */
    uint32_t bitWidth;

} FL_ADC_CommonInitTypeDef;

typedef struct
{
    /** 连续转换模式配置 */
    uint32_t conversionMode;
    /** 单次自动转换模式配置 */
    uint32_t autoMode;
    /** 等待模式配置 */
    FL_FunState waitMode;
    /** 覆盖模式配置 */
    FL_FunState overrunMode;
    /** 通道扫描顺序配置 */
    uint32_t scanDirection;
    /** 触发信号使能配置 */
    uint32_t externalTrigConv;
    /** 触发源选择 */
    uint32_t triggerSource;
    /** 快速通道采样时间配置 */
    uint32_t fastChannelTime;
    /** 慢速通道采样时间配置 */
    uint32_t lowChannelTime;
    /** 过采样使能配置 */
    FL_FunState oversamplingMode;
    /** 过采样率配置 */
    uint32_t overSampingMultiplier;
    /** 过采样移位配置 */
    uint32_t oversamplingShift;

} FL_ADC_InitTypeDef;
/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup ADC_FL_Exported_Constants ADC Exported Constants
  * @{
  */

#define    ADC_ISR_EOC_Pos                                        (0U)
#define    ADC_ISR_EOC_Msk                                        (0x1U << ADC_ISR_EOC_Pos)
#define    ADC_ISR_EOC                                            ADC_ISR_EOC_Msk

#define    ADC_ISR_EOS_Pos                                        (1U)
#define    ADC_ISR_EOS_Msk                                        (0x1U << ADC_ISR_EOS_Pos)
#define    ADC_ISR_EOS                                            ADC_ISR_EOS_Msk

#define    ADC_ISR_OVR_Pos                                        (2U)
#define    ADC_ISR_OVR_Msk                                        (0x1U << ADC_ISR_OVR_Pos)
#define    ADC_ISR_OVR                                            ADC_ISR_OVR_Msk

#define    ADC_ISR_BUSY_Pos                                       (3U)
#define    ADC_ISR_BUSY_Msk                                       (0x1U << ADC_ISR_BUSY_Pos)
#define    ADC_ISR_BUSY                                           ADC_ISR_BUSY_Msk

#define    ADC_ISR_EOCAL_Pos                                      (4U)
#define    ADC_ISR_EOCAL_Msk                                      (0x1U << ADC_ISR_EOCAL_Pos)
#define    ADC_ISR_EOCAL                                          ADC_ISR_EOCAL_Msk

#define    ADC_ISR_AWD_UL_Pos                                     (5U)
#define    ADC_ISR_AWD_UL_Msk                                     (0x1U << ADC_ISR_AWD_UL_Pos)
#define    ADC_ISR_AWD_UL                                         ADC_ISR_AWD_UL_Msk

#define    ADC_ISR_AWD_AH_Pos                                     (6U)
#define    ADC_ISR_AWD_AH_Msk                                     (0x1U << ADC_ISR_AWD_AH_Pos)
#define    ADC_ISR_AWD_AH                                         ADC_ISR_AWD_AH_Msk

#define    ADC_IER_EOCIE_Pos                                      (0U)
#define    ADC_IER_EOCIE_Msk                                      (0x1U << ADC_IER_EOCIE_Pos)
#define    ADC_IER_EOCIE                                          ADC_IER_EOCIE_Msk

#define    ADC_IER_EOSIE_Pos                                      (1U)
#define    ADC_IER_EOSIE_Msk                                      (0x1U << ADC_IER_EOSIE_Pos)
#define    ADC_IER_EOSIE                                          ADC_IER_EOSIE_Msk

#define    ADC_IER_OVRIE_Pos                                      (2U)
#define    ADC_IER_OVRIE_Msk                                      (0x1U << ADC_IER_OVRIE_Pos)
#define    ADC_IER_OVRIE                                          ADC_IER_OVRIE_Msk

#define    ADC_IER_EOCALIE_Pos                                    (4U)
#define    ADC_IER_EOCALIE_Msk                                    (0x1U << ADC_IER_EOCALIE_Pos)
#define    ADC_IER_EOCALIE                                        ADC_IER_EOCALIE_Msk

#define    ADC_IER_AWD_ULIE_Pos                                   (5U)
#define    ADC_IER_AWD_ULIE_Msk                                   (0x1U << ADC_IER_AWD_ULIE_Pos)
#define    ADC_IER_AWD_ULIE                                       ADC_IER_AWD_ULIE_Msk

#define    ADC_IER_AWD_AHIE_Pos                                   (6U)
#define    ADC_IER_AWD_AHIE_Msk                                   (0x1U << ADC_IER_AWD_AHIE_Pos)
#define    ADC_IER_AWD_AHIE                                       ADC_IER_AWD_AHIE_Msk

#define    ADC_CR1_ADEN_Pos                                       (0U)
#define    ADC_CR1_ADEN_Msk                                       (0x1U << ADC_CR1_ADEN_Pos)
#define    ADC_CR1_ADEN                                           ADC_CR1_ADEN_Msk

#define    ADC_CR1_SWTRIG_Pos                                     (1U)
#define    ADC_CR1_SWTRIG_Msk                                     (0x1U << ADC_CR1_SWTRIG_Pos)
#define    ADC_CR1_SWTRIG                                         ADC_CR1_SWTRIG_Msk

#define    ADC_CR2_TRGCFG_Pos                                     (0U)
#define    ADC_CR2_TRGCFG_Msk                                     (0x3U << ADC_CR2_TRGCFG_Pos)
#define    ADC_CR2_TRGCFG                                         ADC_CR2_TRGCFG_Msk

#define    ADC_CALR_CALEN_Pos                                     (0U)
#define    ADC_CALR_CALEN_Msk                                     (0x1U << ADC_CALR_CALEN_Pos)
#define    ADC_CALR_CALEN                                         ADC_CALR_CALEN_Msk

#define    ADC_CFGR1_PEFSEL_Pos                                   (0U)
#define    ADC_CFGR1_PEFSEL_Msk                                   (0x3U << ADC_CFGR1_PEFSEL_Pos)
#define    ADC_CFGR1_PEFSEL                                       ADC_CFGR1_PEFSEL_Msk

#define    ADC_CFGR1_CLKSEL_Pos                                   (2U)
#define    ADC_CFGR1_CLKSEL_Msk                                   (0x1U << ADC_CFGR1_CLKSEL_Pos)
#define    ADC_CFGR1_CLKSEL                                       ADC_CFGR1_CLKSEL_Msk

#define    ADC_CFGR1_BITSEL_Pos                                   (3U)
#define    ADC_CFGR1_BITSEL_Msk                                   (0x3U << ADC_CFGR1_BITSEL_Pos)
#define    ADC_CFGR1_BITSEL                                       ADC_CFGR1_BITSEL_Msk

#define    ADC_CFGR1_EXSOC_Pos                                    (5U)
#define    ADC_CFGR1_EXSOC_Msk                                    (0x1U << ADC_CFGR1_EXSOC_Pos)
#define    ADC_CFGR1_EXSOC                                        ADC_CFGR1_EXSOC_Msk

#define    ADC_CFGR1_APBCLK_PSC_Pos                               (6U)
#define    ADC_CFGR1_APBCLK_PSC_Msk                               (0x3U << ADC_CFGR1_APBCLK_PSC_Pos)
#define    ADC_CFGR1_APBCLK_PSC                                   ADC_CFGR1_APBCLK_PSC_Msk

#define    ADC_CFGR1_BUFEN_Pos                                    (8U)
#define    ADC_CFGR1_BUFEN_Msk                                    (0x1U << ADC_CFGR1_BUFEN_Pos)
#define    ADC_CFGR1_BUFEN                                        ADC_CFGR1_BUFEN_Msk

#define    ADC_CFGR1_BUFMOD_Pos                                   (9U)
#define    ADC_CFGR1_BUFMOD_Msk                                   (0x1U << ADC_CFGR1_BUFMOD_Pos)
#define    ADC_CFGR1_BUFMOD                                       ADC_CFGR1_BUFMOD_Msk

#define    ADC_CFGR1_BUFLPF_Pos                                   (10U)
#define    ADC_CFGR1_BUFLPF_Msk                                   (0x1U << ADC_CFGR1_BUFLPF_Pos)
#define    ADC_CFGR1_BUFLPF                                       ADC_CFGR1_BUFLPF_Msk

#define    ADC_CFGR1_BUFCHP_EN_Pos                                (11U)
#define    ADC_CFGR1_BUFCHP_EN_Msk                                (0x1U << ADC_CFGR1_BUFCHP_EN_Pos)
#define    ADC_CFGR1_BUFCHP_EN                                    ADC_CFGR1_BUFCHP_EN_Msk

#define    ADC_CFGR2_DMAEN_Pos                                    (0U)
#define    ADC_CFGR2_DMAEN_Msk                                    (0x1U << ADC_CFGR2_DMAEN_Pos)
#define    ADC_CFGR2_DMAEN                                        ADC_CFGR2_DMAEN_Msk

#define    ADC_CFGR2_SCANDIR_Pos                                  (2U)
#define    ADC_CFGR2_SCANDIR_Msk                                  (0x1U << ADC_CFGR2_SCANDIR_Pos)
#define    ADC_CFGR2_SCANDIR                                      ADC_CFGR2_SCANDIR_Msk

#define    ADC_CFGR2_EXTS_Pos                                     (4U)
#define    ADC_CFGR2_EXTS_Msk                                     (0xfU << ADC_CFGR2_EXTS_Pos)
#define    ADC_CFGR2_EXTS                                         ADC_CFGR2_EXTS_Msk

#define    ADC_CFGR2_OVRM_Pos                                     (8U)
#define    ADC_CFGR2_OVRM_Msk                                     (0x1U << ADC_CFGR2_OVRM_Pos)
#define    ADC_CFGR2_OVRM                                         ADC_CFGR2_OVRM_Msk

#define    ADC_CFGR2_CONT_Pos                                     (9U)
#define    ADC_CFGR2_CONT_Msk                                     (0x1U << ADC_CFGR2_CONT_Pos)
#define    ADC_CFGR2_CONT                                         ADC_CFGR2_CONT_Msk

#define    ADC_CFGR2_WAIT_Pos                                     (10U)
#define    ADC_CFGR2_WAIT_Msk                                     (0x1U << ADC_CFGR2_WAIT_Pos)
#define    ADC_CFGR2_WAIT                                         ADC_CFGR2_WAIT_Msk

#define    ADC_CFGR2_SEMI_Pos                                     (11U)
#define    ADC_CFGR2_SEMI_Msk                                     (0x1U << ADC_CFGR2_SEMI_Pos)
#define    ADC_CFGR2_SEMI                                         ADC_CFGR2_SEMI_Msk

#define    ADC_CFGR2_IOTRFEN_Pos                                  (14U)
#define    ADC_CFGR2_IOTRFEN_Msk                                  (0x1U << ADC_CFGR2_IOTRFEN_Pos)
#define    ADC_CFGR2_IOTRFEN                                      ADC_CFGR2_IOTRFEN_Msk

#define    ADC_CFGR2_OVSEN_Pos                                    (16U)
#define    ADC_CFGR2_OVSEN_Msk                                    (0x1U << ADC_CFGR2_OVSEN_Pos)
#define    ADC_CFGR2_OVSEN                                        ADC_CFGR2_OVSEN_Msk

#define    ADC_CFGR2_OVSR_Pos                                     (17U)
#define    ADC_CFGR2_OVSR_Msk                                     (0x7U << ADC_CFGR2_OVSR_Pos)
#define    ADC_CFGR2_OVSR                                         ADC_CFGR2_OVSR_Msk

#define    ADC_CFGR2_OVSS_Pos                                     (20U)
#define    ADC_CFGR2_OVSS_Msk                                     (0xfU << ADC_CFGR2_OVSS_Pos)
#define    ADC_CFGR2_OVSS                                         ADC_CFGR2_OVSS_Msk

#define    ADC_CFGR2_AWDEN_Pos                                    (24U)
#define    ADC_CFGR2_AWDEN_Msk                                    (0x1U << ADC_CFGR2_AWDEN_Pos)
#define    ADC_CFGR2_AWDEN                                        ADC_CFGR2_AWDEN_Msk

#define    ADC_CFGR2_AWDSC_Pos                                    (25U)
#define    ADC_CFGR2_AWDSC_Msk                                    (0x1U << ADC_CFGR2_AWDSC_Pos)
#define    ADC_CFGR2_AWDSC                                        ADC_CFGR2_AWDSC_Msk

#define    ADC_CFGR2_AWDCH_Pos                                    (26U)
#define    ADC_CFGR2_AWDCH_Msk                                    (0x1fU << ADC_CFGR2_AWDCH_Pos)
#define    ADC_CFGR2_AWDCH                                        ADC_CFGR2_AWDCH_Msk

#define    ADC_SMTR_SMTS1_Pos                                     (0U)
#define    ADC_SMTR_SMTS1_Msk                                     (0xfU << ADC_SMTR_SMTS1_Pos)
#define    ADC_SMTR_SMTS1                                         ADC_SMTR_SMTS1_Msk

#define    ADC_SMTR_SMTS2_Pos                                     (4U)
#define    ADC_SMTR_SMTS2_Msk                                     (0xfU << ADC_SMTR_SMTS2_Pos)
#define    ADC_SMTR_SMTS2                                         ADC_SMTR_SMTS2_Msk

#define    ADC_DR_DATA_Pos                                        (0U)
#define    ADC_DR_DATA_Msk                                        (0xffffU << ADC_DR_DATA_Pos)
#define    ADC_DR_DATA                                            ADC_DR_DATA_Msk

#define    ADC_HLTR_AWD_LT_Pos                                    (0U)
#define    ADC_HLTR_AWD_LT_Msk                                    (0xffffU << ADC_HLTR_AWD_LT_Pos)
#define    ADC_HLTR_AWD_LT                                        ADC_HLTR_AWD_LT_Msk

#define    ADC_HLTR_AWD_HT_Pos                                    (16U)
#define    ADC_HLTR_AWD_HT_Msk                                    (0xffffU << ADC_HLTR_AWD_HT_Pos)
#define    ADC_HLTR_AWD_HT                                        ADC_HLTR_AWD_HT_Msk



#define    FL_ADC_EXTERNAL_CH0                                    (0x1U << 0U)
#define    FL_ADC_EXTERNAL_CH1                                    (0x1U << 1U)
#define    FL_ADC_EXTERNAL_CH2                                    (0x1U << 2U)
#define    FL_ADC_EXTERNAL_CH3                                    (0x1U << 3U)
#define    FL_ADC_EXTERNAL_CH4                                    (0x1U << 4U)
#define    FL_ADC_EXTERNAL_CH5                                    (0x1U << 5U)
#define    FL_ADC_EXTERNAL_CH6                                    (0x1U << 6U)
#define    FL_ADC_EXTERNAL_CH7                                    (0x1U << 7U)
#define    FL_ADC_EXTERNAL_CH8                                    (0x1U << 8U)
#define    FL_ADC_EXTERNAL_CH9                                    (0x1U << 9U)
#define    FL_ADC_EXTERNAL_CH10                                   (0x1U << 10U)
#define    FL_ADC_EXTERNAL_CH11                                   (0x1U << 11U)
#define    FL_ADC_EXTERNAL_CH12                                   (0x1U << 12U)
#define    FL_ADC_EXTERNAL_CH13                                   (0x1U << 13U)
#define    FL_ADC_EXTERNAL_CH14                                   (0x1U << 14U)
#define    FL_ADC_EXTERNAL_CH15                                   (0x1U << 15U)
#define    FL_ADC_EXTERNAL_CH16                                   (0x1U << 16U)
#define    FL_ADC_EXTERNAL_CH17                                   (0x1U << 17U)
#define    FL_ADC_EXTERNAL_CH18                                   (0x1U << 18U)
#define    FL_ADC_EXTERNAL_CH19                                   (0x1U << 19U)
#define    FL_ADC_INTERNAL_VREF1P2                                (0x1U << 24U)
#define    FL_ADC_INTERNAL_TS                                     (0x1U << 25U)
#define    FL_ADC_INTERNAL_AVREF                                  (0x1U << 26U)
#define    FL_ADC_INTERNAL_VBAT_DIV3                              (0x1U << 27U)
#define    FL_ADC_INTERNAL_VDD_DIV3                               (0x1U << 28U)
#define    FL_ADC_INTERNAL_DAC                                    (0x1U << 29U)
#define    FL_ADC_INTERNAL_OPA                                    (0x1U << 30U)
#define    FL_ADC_ALL_CHANNEL                                     (0xfffffU << 0U)


#define    FL_ADC_DIFFERENTIAL_GROUP0                             (0x1U << 0U)
#define    FL_ADC_DIFFERENTIAL_GROUP1                             (0x1U << 1U)
#define    FL_ADC_DIFFERENTIAL_GROUP2                             (0x1U << 2U)
#define    FL_ADC_DIFFERENTIAL_GROUP3                             (0x1U << 3U)
#define    FL_ADC_DIFFERENTIAL_GROUP4                             (0x1U << 4U)
#define    FL_ADC_DIFFERENTIAL_GROUP5                             (0x1U << 5U)
#define    FL_ADC_DIFFERENTIAL_GROUP6                             (0x1U << 6U)
#define    FL_ADC_CLK_PSC_DIV1                                    (0x0U << 0U)
#define    FL_ADC_CLK_PSC_DIV2                                    (0x1U << 0U)
#define    FL_ADC_CLK_PSC_DIV4                                    (0x2U << 0U)
#define    FL_ADC_CLK_PSC_DIV8                                    (0x3U << 0U)
#define    FL_ADC_CLK_PSC_DIV16                                   (0x4U << 0U)
#define    FL_ADC_CLK_PSC_DIV32                                   (0x5U << 0U)



#define    FL_ADC_TRIGGER_EDGE_NONE                               (0x0U << ADC_CR2_TRGCFG_Pos)
#define    FL_ADC_TRIGGER_EDGE_RISING                             (0x1U << ADC_CR2_TRGCFG_Pos)
#define    FL_ADC_TRIGGER_EDGE_FALLING                            (0x2U << ADC_CR2_TRGCFG_Pos)
#define    FL_ADC_TRIGGER_EDGE_BOTH                               (0x3U << ADC_CR2_TRGCFG_Pos)


#define    FL_ADC_REF_SOURCE_VDDA                                 (0x0U << ADC_CFGR1_PEFSEL_Pos)
#define    FL_ADC_REF_SOURCE_VREFP                                (0x1U << ADC_CFGR1_PEFSEL_Pos)
#define    FL_ADC_REF_SOURCE_VDD15                                (0x2U << ADC_CFGR1_PEFSEL_Pos)


#define    FL_ADC_CLK_SOURCE_ADCCLK                               (0x0U << ADC_CFGR1_CLKSEL_Pos)
#define    FL_ADC_CLK_SOURCE_APBCLK                               (0x1U << ADC_CFGR1_CLKSEL_Pos)


#define    FL_ADC_BIT_WIDTH_12B                                   (0x0U << ADC_CFGR1_BITSEL_Pos)
#define    FL_ADC_BIT_WIDTH_10B                                   (0x1U << ADC_CFGR1_BITSEL_Pos)
#define    FL_ADC_BIT_WIDTH_8B                                    (0x2U << ADC_CFGR1_BITSEL_Pos)
#define    FL_ADC_BIT_WIDTH_6B                                    (0x3U << ADC_CFGR1_BITSEL_Pos)


#define    FL_ADC_APBCLK_PSC_DIV1                                 (0x0U << ADC_CFGR1_APBCLK_PSC_Pos)
#define    FL_ADC_APBCLK_PSC_DIV2                                 (0x1U << ADC_CFGR1_APBCLK_PSC_Pos)
#define    FL_ADC_APBCLK_PSC_DIV4                                 (0x2U << ADC_CFGR1_APBCLK_PSC_Pos)
#define    FL_ADC_APBCLK_PSC_DIV8                                 (0x3U << ADC_CFGR1_APBCLK_PSC_Pos)


#define    FL_ADC_BUFF_POWER_MODE_NORMAL                          (0x0U << ADC_CFGR1_BUFMOD_Pos)
#define    FL_ADC_BUFF_POWER_MODE_LOW                             (0x1U << ADC_CFGR1_BUFMOD_Pos)


#define    FL_ADC_BUFF_FILTER_MODE_NORMAL                         (0x0U << ADC_CFGR1_BUFLPF_Pos)
#define    FL_ADC_BUFF_FILTER_MODE_LOWPASS                        (0x1U << ADC_CFGR1_BUFLPF_Pos)


#define    FL_ADC_SEQ_SCAN_DIR_FORWARD                            (0x0U << ADC_CFGR2_SCANDIR_Pos)
#define    FL_ADC_SEQ_SCAN_DIR_BACKWARD                           (0x1U << ADC_CFGR2_SCANDIR_Pos)


#define    FL_ADC_TRGI_LUT0                                       (0x0U << ADC_CFGR2_EXTS_Pos)
#define    FL_ADC_TRGI_LUT1                                       (0x1U << ADC_CFGR2_EXTS_Pos)
#define    FL_ADC_TRGI_LUT2                                       (0x2U << ADC_CFGR2_EXTS_Pos)
#define    FL_ADC_TRGI_ATIM                                       (0x3U << ADC_CFGR2_EXTS_Pos)
#define    FL_ADC_TRGI_GPTIM1                                     (0x4U << ADC_CFGR2_EXTS_Pos)
#define    FL_ADC_TRGI_GPTIM2                                     (0x5U << ADC_CFGR2_EXTS_Pos)
#define    FL_ADC_TRGI_BSTIM16                                    (0x6U << ADC_CFGR2_EXTS_Pos)
#define    FL_ADC_TRGI_LPTIM16                                    (0x7U << ADC_CFGR2_EXTS_Pos)
#define    FL_ADC_TRGI_COMP1                                      (0x8U << ADC_CFGR2_EXTS_Pos)
#define    FL_ADC_TRGI_COMP2                                      (0x9U << ADC_CFGR2_EXTS_Pos)
#define    FL_ADC_TRGI_RTCA                                       (0xaU << ADC_CFGR2_EXTS_Pos)
#define    FL_ADC_TRGI_LUT3                                       (0xbU << ADC_CFGR2_EXTS_Pos)
#define    FL_ADC_TRGI_GPTIM0                                     (0xcU << ADC_CFGR2_EXTS_Pos)
#define    FL_ADC_TRGI_COMP3                                      (0xdU << ADC_CFGR2_EXTS_Pos)


#define    FL_ADC_CONV_MODE_SINGLE                                (0x0U << ADC_CFGR2_CONT_Pos)
#define    FL_ADC_CONV_MODE_CONTINUOUS                            (0x1U << ADC_CFGR2_CONT_Pos)


#define    FL_ADC_SINGLE_CONV_MODE_AUTO                           (0x0U << ADC_CFGR2_SEMI_Pos)
#define    FL_ADC_SINGLE_CONV_MODE_SEMIAUTO                       (0x1U << ADC_CFGR2_SEMI_Pos)


#define    FL_ADC_OVERSAMPLING_MUL_2X                             (0x0U << ADC_CFGR2_OVSR_Pos)
#define    FL_ADC_OVERSAMPLING_MUL_4X                             (0x1U << ADC_CFGR2_OVSR_Pos)
#define    FL_ADC_OVERSAMPLING_MUL_8X                             (0x2U << ADC_CFGR2_OVSR_Pos)
#define    FL_ADC_OVERSAMPLING_MUL_16X                            (0x3U << ADC_CFGR2_OVSR_Pos)
#define    FL_ADC_OVERSAMPLING_MUL_32X                            (0x4U << ADC_CFGR2_OVSR_Pos)
#define    FL_ADC_OVERSAMPLING_MUL_64X                            (0x5U << ADC_CFGR2_OVSR_Pos)
#define    FL_ADC_OVERSAMPLING_MUL_128X                           (0x6U << ADC_CFGR2_OVSR_Pos)
#define    FL_ADC_OVERSAMPLING_MUL_256X                           (0x7U << ADC_CFGR2_OVSR_Pos)


#define    FL_ADC_OVERSAMPLING_SHIFT_0B                           (0x0U << ADC_CFGR2_OVSS_Pos)
#define    FL_ADC_OVERSAMPLING_SHIFT_1B                           (0x1U << ADC_CFGR2_OVSS_Pos)
#define    FL_ADC_OVERSAMPLING_SHIFT_2B                           (0x2U << ADC_CFGR2_OVSS_Pos)
#define    FL_ADC_OVERSAMPLING_SHIFT_3B                           (0x3U << ADC_CFGR2_OVSS_Pos)
#define    FL_ADC_OVERSAMPLING_SHIFT_4B                           (0x4U << ADC_CFGR2_OVSS_Pos)
#define    FL_ADC_OVERSAMPLING_SHIFT_5B                           (0x5U << ADC_CFGR2_OVSS_Pos)
#define    FL_ADC_OVERSAMPLING_SHIFT_6B                           (0x6U << ADC_CFGR2_OVSS_Pos)
#define    FL_ADC_OVERSAMPLING_SHIFT_7B                           (0x7U << ADC_CFGR2_OVSS_Pos)
#define    FL_ADC_OVERSAMPLING_SHIFT_8B                           (0x8U << ADC_CFGR2_OVSS_Pos)


#define    FL_ADC_AWDG_ALL_CHANNEL                                (0x0U << ADC_CFGR2_AWDSC_Pos)
#define    FL_ADC_AWDG_SINGLE_CHANNEL                             (0x1U << ADC_CFGR2_AWDSC_Pos)


#define    FL_ADC_AWDG_CH0                                        (0x0U << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH1                                        (0x1U << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH2                                        (0x2U << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH3                                        (0x3U << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH4                                        (0x4U << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH5                                        (0x5U << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH6                                        (0x6U << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH7                                        (0x7U << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH8                                        (0x8U << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH9                                        (0x9U << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH10                                       (0xaU << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH11                                       (0xbU << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH12                                       (0xcU << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH13                                       (0xdU << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH14                                       (0xeU << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH15                                       (0xfU << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH16                                       (0x10U << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH17                                       (0x11U << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH18                                       (0x12U << ADC_CFGR2_AWDCH_Pos)
#define    FL_ADC_AWDG_CH19                                       (0x13U << ADC_CFGR2_AWDCH_Pos)


#define    FL_ADC_SLOW_CH_SAMPLING_TIME_2_ADCCLK                  (0x0U << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_4_ADCCLK                  (0x1U << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_8_ADCCLK                  (0x2U << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_12_ADCCLK                 (0x3U << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_16_ADCCLK                 (0x4U << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_32_ADCCLK                 (0x5U << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_64_ADCCLK                 (0x6U << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_80_ADCCLK                 (0x7U << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_96_ADCCLK                 (0x8U << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_128_ADCCLK                (0x9U << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_160_ADCCLK                (0xaU << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_192_ADCCLK                (0xbU << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_256_ADCCLK                (0xcU << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_320_ADCCLK                (0xdU << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_384_ADCCLK                (0xeU << ADC_SMTR_SMTS1_Pos)
#define    FL_ADC_SLOW_CH_SAMPLING_TIME_512_ADCCLK                (0xfU << ADC_SMTR_SMTS1_Pos)


#define    FL_ADC_FAST_CH_SAMPLING_TIME_2_ADCCLK                  (0x0U << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_4_ADCCLK                  (0x1U << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_8_ADCCLK                  (0x2U << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_12_ADCCLK                 (0x3U << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_16_ADCCLK                 (0x4U << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_32_ADCCLK                 (0x5U << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_64_ADCCLK                 (0x6U << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_80_ADCCLK                 (0x7U << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_96_ADCCLK                 (0x8U << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_128_ADCCLK                (0x9U << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_160_ADCCLK                (0xaU << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_192_ADCCLK                (0xbU << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_256_ADCCLK                (0xcU << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_320_ADCCLK                (0xdU << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_384_ADCCLK                (0xeU << ADC_SMTR_SMTS2_Pos)
#define    FL_ADC_FAST_CH_SAMPLING_TIME_512_ADCCLK                (0xfU << ADC_SMTR_SMTS2_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup ADC_FL_Exported_Functions ADC Exported Functions
  * @{
  */

/**
  * @brief    Get ADC End Of Conversion Flag
  * @rmtoll   ISR    EOC    FL_ADC_IsActiveFlag_EndOfConversion
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsActiveFlag_EndOfConversion(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->ISR, ADC_ISR_EOC_Msk) == (ADC_ISR_EOC_Msk));
}

/**
  * @brief    Clear ADC End Of Conversion Flag
  * @rmtoll   ISR    EOC    FL_ADC_ClearFlag_EndOfConversion
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_ClearFlag_EndOfConversion(ADC_Type *ADCx)
{
    WRITE_REG(ADCx->ISR, ADC_ISR_EOC_Msk);
}

/**
  * @brief    Get ADC End Of Sequence Flag
  * @rmtoll   ISR    EOS    FL_ADC_IsActiveFlag_EndOfSequence
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsActiveFlag_EndOfSequence(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->ISR, ADC_ISR_EOS_Msk) == (ADC_ISR_EOS_Msk));
}

/**
  * @brief    Clear ADC End Of Sequence Flag
  * @rmtoll   ISR    EOS    FL_ADC_ClearFlag_EndOfSequence
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_ClearFlag_EndOfSequence(ADC_Type *ADCx)
{
    WRITE_REG(ADCx->ISR, ADC_ISR_EOS_Msk);
}

/**
  * @brief    Get ADC Data Overrun Flag
  * @rmtoll   ISR    OVR    FL_ADC_IsActiveFlag_Overrun
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsActiveFlag_Overrun(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->ISR, ADC_ISR_OVR_Msk) == (ADC_ISR_OVR_Msk));
}

/**
  * @brief    Clear ADC  Data Overrun Flag
  * @rmtoll   ISR    OVR    FL_ADC_ClearFlag_Overrun
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_ClearFlag_Overrun(ADC_Type *ADCx)
{
    WRITE_REG(ADCx->ISR, ADC_ISR_OVR_Msk);
}

/**
  * @brief    Get ADC Busy Flag
  * @rmtoll   ISR    BUSY    FL_ADC_IsActiveFlag_Busy
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsActiveFlag_Busy(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->ISR, ADC_ISR_BUSY_Msk) == (ADC_ISR_BUSY_Msk));
}

/**
  * @brief    Get ADC End Of Calibration Flag
  * @rmtoll   ISR    EOCAL    FL_ADC_IsActiveFlag_EndOfCalibration
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsActiveFlag_EndOfCalibration(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->ISR, ADC_ISR_EOCAL_Msk) == (ADC_ISR_EOCAL_Msk));
}

/**
  * @brief    Clear ADC End Of Calibration Flag
  * @rmtoll   ISR    EOCAL    FL_ADC_ClearFlag_EndOfCalibration
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_ClearFlag_EndOfCalibration(ADC_Type *ADCx)
{
    WRITE_REG(ADCx->ISR, ADC_ISR_EOCAL_Msk);
}

/**
  * @brief    Get ADC Analog Watchdog Under Low
  * @rmtoll   ISR    AWD_UL    FL_ADC_IsActiveFlag_AnalogWDGUnderLow
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsActiveFlag_AnalogWDGUnderLow(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->ISR, ADC_ISR_AWD_UL_Msk) == (ADC_ISR_AWD_UL_Msk));
}

/**
  * @brief    Clear ADC Analog Watchdog Under Low
  * @rmtoll   ISR    AWD_UL    FL_ADC_ClearFlag_AnalogWDGUnderLow
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_ClearFlag_AnalogWDGUnderLow(ADC_Type *ADCx)
{
    WRITE_REG(ADCx->ISR, ADC_ISR_AWD_UL_Msk);
}

/**
  * @brief    Get ADC Analog Watchdog Above High
  * @rmtoll   ISR    AWD_AH    FL_ADC_IsActiveFlag_AnalogWDGAboveHigh
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsActiveFlag_AnalogWDGAboveHigh(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->ISR, ADC_ISR_AWD_AH_Msk) == (ADC_ISR_AWD_AH_Msk));
}

/**
  * @brief    Clear ADC Analog Watchdog Above High
  * @rmtoll   ISR    AWD_AH    FL_ADC_ClearFlag_AnalogWDGAboveHigh
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_ClearFlag_AnalogWDGAboveHigh(ADC_Type *ADCx)
{
    WRITE_REG(ADCx->ISR, ADC_ISR_AWD_AH_Msk);
}

/**
  * @brief    Enable ADC End 0f Conversion interrupt
  * @rmtoll   IER    EOCIE    FL_ADC_EnableIT_EndOfConversion
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableIT_EndOfConversion(ADC_Type *ADCx)
{
    SET_BIT(ADCx->IER, ADC_IER_EOCIE_Msk);
}

/**
  * @brief    Disable ADC End 0f Conversion interrupt
  * @rmtoll   IER    EOCIE    FL_ADC_DisableIT_EndOfConversion
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableIT_EndOfConversion(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->IER, ADC_IER_EOCIE_Msk);
}

/**
  * @brief    Get ADC End 0f Conversion interrupt Enable Status
  * @rmtoll   IER    EOCIE    FL_ADC_IsEnabledIT_EndOfConversion
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledIT_EndOfConversion(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->IER, ADC_IER_EOCIE_Msk) == ADC_IER_EOCIE_Msk);
}

/**
  * @brief    Enable ADC End Of Sequence interrupt
  * @rmtoll   IER    EOSIE    FL_ADC_EnableIT_EndOfSequence
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableIT_EndOfSequence(ADC_Type *ADCx)
{
    SET_BIT(ADCx->IER, ADC_IER_EOSIE_Msk);
}

/**
  * @brief    Disable ADC End Of Sequence interrupt
  * @rmtoll   IER    EOSIE    FL_ADC_DisableIT_EndOfSequence
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableIT_EndOfSequence(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->IER, ADC_IER_EOSIE_Msk);
}

/**
  * @brief    Get ADC End Of Sequence interrupt Enable Status
  * @rmtoll   IER    EOSIE    FL_ADC_IsEnabledIT_EndOfSequence
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledIT_EndOfSequence(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->IER, ADC_IER_EOSIE_Msk) == ADC_IER_EOSIE_Msk);
}

/**
  * @brief    Enable ADC Data Overrun interrupt
  * @rmtoll   IER    OVRIE    FL_ADC_EnableIT_Overrun
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableIT_Overrun(ADC_Type *ADCx)
{
    SET_BIT(ADCx->IER, ADC_IER_OVRIE_Msk);
}

/**
  * @brief    Disable ADC Data Overrun interrupt
  * @rmtoll   IER    OVRIE    FL_ADC_DisableIT_Overrun
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableIT_Overrun(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->IER, ADC_IER_OVRIE_Msk);
}

/**
  * @brief    Get ADC Data Overrun interrupt Enable Status
  * @rmtoll   IER    OVRIE    FL_ADC_IsEnabledIT_Overrun
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledIT_Overrun(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->IER, ADC_IER_OVRIE_Msk) == ADC_IER_OVRIE_Msk);
}

/**
  * @brief    Enable ADC End Of Calibration interrupt
  * @rmtoll   IER    EOCALIE    FL_ADC_EnableIT_EndOfCalibration
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableIT_EndOfCalibration(ADC_Type *ADCx)
{
    SET_BIT(ADCx->IER, ADC_IER_EOCALIE_Msk);
}

/**
  * @brief    Disable ADC End Of Calibration interrupt
  * @rmtoll   IER    EOCALIE    FL_ADC_DisableIT_EndOfCalibration
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableIT_EndOfCalibration(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->IER, ADC_IER_EOCALIE_Msk);
}

/**
  * @brief    Get ADC End Of Calibration interrupt Enable Status
  * @rmtoll   IER    EOCALIE    FL_ADC_IsEnabledIT_EndOfCalibration
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledIT_EndOfCalibration(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->IER, ADC_IER_EOCALIE_Msk) == ADC_IER_EOCALIE_Msk);
}

/**
  * @brief    Enable ADC Analog Watchdog Under Low interrupt
  * @rmtoll   IER    AWD_ULIE    FL_ADC_EnableIT_AnalogWDGUnderLow
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableIT_AnalogWDGUnderLow(ADC_Type *ADCx)
{
    SET_BIT(ADCx->IER, ADC_IER_AWD_ULIE_Msk);
}

/**
  * @brief    Disable ADC Analog Watchdog Under Low interrupt
  * @rmtoll   IER    AWD_ULIE    FL_ADC_DisableIT_AnalogWDGUnderLow
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableIT_AnalogWDGUnderLow(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->IER, ADC_IER_AWD_ULIE_Msk);
}

/**
  * @brief    Get ADC Analog Watchdog Under Low interrupt Enable Status
  * @rmtoll   IER    AWD_ULIE    FL_ADC_IsEnabledIT_AnalogWDGUnderLow
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledIT_AnalogWDGUnderLow(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->IER, ADC_IER_AWD_ULIE_Msk) == ADC_IER_AWD_ULIE_Msk);
}

/**
  * @brief    Enable ADC Analog Watchdog Above High interrupt
  * @rmtoll   IER    AWD_AHIE    FL_ADC_EnableIT_AnalogWDGAboveHigh
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableIT_AnalogWDGAboveHigh(ADC_Type *ADCx)
{
    SET_BIT(ADCx->IER, ADC_IER_AWD_AHIE_Msk);
}

/**
  * @brief    Disable ADC Analog Watchdog Above High interrupt
  * @rmtoll   IER    AWD_AHIE    FL_ADC_DisableIT_AnalogWDGAboveHigh
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableIT_AnalogWDGAboveHigh(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->IER, ADC_IER_AWD_AHIE_Msk);
}

/**
  * @brief    Get ADC Analog Watchdog Above High interrupt Enable Status
  * @rmtoll   IER    AWD_AHIE    FL_ADC_IsEnabledIT_AnalogWDGAboveHigh
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledIT_AnalogWDGAboveHigh(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->IER, ADC_IER_AWD_AHIE_Msk) == ADC_IER_AWD_AHIE_Msk);
}

/**
  * @brief    Enable ADC
  * @rmtoll   CR1    ADEN    FL_ADC_Enable
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_Enable(ADC_Type *ADCx)
{
    SET_BIT(ADCx->CR1, ADC_CR1_ADEN_Msk);
}

/**
  * @brief    Disable ADC
  * @rmtoll   CR1    ADEN    FL_ADC_Disable
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_Disable(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->CR1, ADC_CR1_ADEN_Msk);
}

/**
  * @brief    Get ADC Enable Status
  * @rmtoll   CR1    ADEN    FL_ADC_IsEnabled
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabled(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CR1, ADC_CR1_ADEN_Msk) == ADC_CR1_ADEN_Msk);
}

/**
  * @brief    Enable ADC Sofeware Triggered Conversion
  * @rmtoll   CR1    SWTRIG    FL_ADC_EnableSWConversion
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableSWConversion(ADC_Type *ADCx)
{
    SET_BIT(ADCx->CR1, ADC_CR1_SWTRIG_Msk);
}

/**
  * @brief    Set ADC Trigger Edge
  * @rmtoll   CR2    TRGCFG    FL_ADC_SetTriggerEdge
  * @param    ADCx ADC instance
  * @param    edge This parameter can be one of the following values:
  *           @arg @ref FL_ADC_TRIGGER_EDGE_NONE
  *           @arg @ref FL_ADC_TRIGGER_EDGE_RISING
  *           @arg @ref FL_ADC_TRIGGER_EDGE_FALLING
  *           @arg @ref FL_ADC_TRIGGER_EDGE_BOTH
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetTriggerEdge(ADC_Type *ADCx, uint32_t edge)
{
    MODIFY_REG(ADCx->CR2, ADC_CR2_TRGCFG_Msk, edge);
}

/**
  * @brief    Read ADC Trigger Edge
  * @rmtoll   CR2    TRGCFG    FL_ADC_GetTriggerEdge
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_TRIGGER_EDGE_NONE
  *           @arg @ref FL_ADC_TRIGGER_EDGE_RISING
  *           @arg @ref FL_ADC_TRIGGER_EDGE_FALLING
  *           @arg @ref FL_ADC_TRIGGER_EDGE_BOTH
  */
__STATIC_INLINE uint32_t FL_ADC_GetTriggerEdge(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CR2, ADC_CR2_TRGCFG_Msk));
}

/**
  * @brief    Enable ADC Calibration
  * @rmtoll   CALR    CALEN    FL_ADC_EnableCalibration
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableCalibration(ADC_Type *ADCx)
{
    SET_BIT(ADCx->CALR, ADC_CALR_CALEN_Msk);
}

/**
  * @brief    Disable ADC Calibration
  * @rmtoll   CALR    CALEN    FL_ADC_DisableCalibration
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableCalibration(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->CALR, ADC_CALR_CALEN_Msk);
}

/**
  * @brief    Get ADC Calibration Enable Status
  * @rmtoll   CALR    CALEN    FL_ADC_IsEnabledCalibration
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledCalibration(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CALR, ADC_CALR_CALEN_Msk) == ADC_CALR_CALEN_Msk);
}

/**
  * @brief    Set ADC Reference Source
  * @rmtoll   CFGR1    PEFSEL    FL_ADC_SetReferenceSource
  * @param    ADCx ADC instance
  * @param    ref This parameter can be one of the following values:
  *           @arg @ref FL_ADC_REF_SOURCE_VDDA
  *           @arg @ref FL_ADC_REF_SOURCE_VREFP
  *           @arg @ref FL_ADC_REF_SOURCE_VDD15
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetReferenceSource(ADC_Type *ADCx, uint32_t ref)
{
    MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_PEFSEL_Msk, ref);
}

/**
  * @brief    Read ADC Reference Source
  * @rmtoll   CFGR1    PEFSEL    FL_ADC_GetReferenceSource
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_REF_SOURCE_VDDA
  *           @arg @ref FL_ADC_REF_SOURCE_VREFP
  *           @arg @ref FL_ADC_REF_SOURCE_VDD15
  */
__STATIC_INLINE uint32_t FL_ADC_GetReferenceSource(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_PEFSEL_Msk));
}

/**
  * @brief    Set ADC Working Clock
  * @rmtoll   CFGR1    CLKSEL    FL_ADC_SetClockSource
  * @param    ADCx ADC instance
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_ADC_CLK_SOURCE_ADCCLK
  *           @arg @ref FL_ADC_CLK_SOURCE_APBCLK
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetClockSource(ADC_Type *ADCx, uint32_t clock)
{
    MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_CLKSEL_Msk, clock);
}

/**
  * @brief    Read ADC Working Clock
  * @rmtoll   CFGR1    CLKSEL    FL_ADC_GetClockSource
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_CLK_SOURCE_ADCCLK
  *           @arg @ref FL_ADC_CLK_SOURCE_APBCLK
  */
__STATIC_INLINE uint32_t FL_ADC_GetClockSource(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_CLKSEL_Msk));
}

/**
  * @brief    Set ADC Output Bit Width
  * @rmtoll   CFGR1    BITSEL    FL_ADC_SetBitWidth
  * @param    ADCx ADC instance
  * @param    bitWidth This parameter can be one of the following values:
  *           @arg @ref FL_ADC_BIT_WIDTH_12B
  *           @arg @ref FL_ADC_BIT_WIDTH_10B
  *           @arg @ref FL_ADC_BIT_WIDTH_8B
  *           @arg @ref FL_ADC_BIT_WIDTH_6B
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetBitWidth(ADC_Type *ADCx, uint32_t bitWidth)
{
    MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_BITSEL_Msk, bitWidth);
}

/**
  * @brief    Read ADC Output Bit Width
  * @rmtoll   CFGR1    BITSEL    FL_ADC_GetBitWidth
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_BIT_WIDTH_12B
  *           @arg @ref FL_ADC_BIT_WIDTH_10B
  *           @arg @ref FL_ADC_BIT_WIDTH_8B
  *           @arg @ref FL_ADC_BIT_WIDTH_6B
  */
__STATIC_INLINE uint32_t FL_ADC_GetBitWidth(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_BITSEL_Msk));
}

/**
  * @brief    Enable ADC External Conversion
  * @rmtoll   CFGR1    EXSOC    FL_ADC_EnableExternalConversion
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableExternalConversion(ADC_Type *ADCx)
{
    SET_BIT(ADCx->CFGR1, ADC_CFGR1_EXSOC_Msk);
}

/**
  * @brief    Disable ADC External Conversion
  * @rmtoll   CFGR1    EXSOC    FL_ADC_DisableExternalConversion
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableExternalConversion(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->CFGR1, ADC_CFGR1_EXSOC_Msk);
}

/**
  * @brief    Get ADC External Conversion Enable Status
  * @rmtoll   CFGR1    EXSOC    FL_ADC_IsEnabledExternalConversion
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledExternalConversion(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_EXSOC_Msk) == ADC_CFGR1_EXSOC_Msk);
}

/**
  * @brief    Set ADC APBCLK Prescaler
  * @rmtoll   CFGR1    APBCLK_PSC    FL_ADC_SetAPBPrescaler
  * @param    ADCx ADC instance
  * @param    psc This parameter can be one of the following values:
  *           @arg @ref FL_ADC_APBCLK_PSC_DIV1
  *           @arg @ref FL_ADC_APBCLK_PSC_DIV2
  *           @arg @ref FL_ADC_APBCLK_PSC_DIV4
  *           @arg @ref FL_ADC_APBCLK_PSC_DIV8
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetAPBPrescaler(ADC_Type *ADCx, uint32_t psc)
{
    MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_APBCLK_PSC_Msk, psc);
}

/**
  * @brief    Read ADC APBCLK Prescaler
  * @rmtoll   CFGR1    APBCLK_PSC    FL_ADC_GetAPBPrescaler
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_APBCLK_PSC_DIV1
  *           @arg @ref FL_ADC_APBCLK_PSC_DIV2
  *           @arg @ref FL_ADC_APBCLK_PSC_DIV4
  *           @arg @ref FL_ADC_APBCLK_PSC_DIV8
  */
__STATIC_INLINE uint32_t FL_ADC_GetAPBPrescaler(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_APBCLK_PSC_Msk));
}

/**
  * @brief    Enable ADC Buffer
  * @rmtoll   CFGR1    BUFEN    FL_ADC_EnableBuffer
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableBuffer(ADC_Type *ADCx)
{
    SET_BIT(ADCx->CFGR1, ADC_CFGR1_BUFEN_Msk);
}

/**
  * @brief    Disable ADC Buffer
  * @rmtoll   CFGR1    BUFEN    FL_ADC_DisableBuffer
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableBuffer(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->CFGR1, ADC_CFGR1_BUFEN_Msk);
}

/**
  * @brief    Get ADC Buffer Enable Status
  * @rmtoll   CFGR1    BUFEN    FL_ADC_IsEnabledBuffer
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledBuffer(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_BUFEN_Msk) == ADC_CFGR1_BUFEN_Msk);
}

/**
  * @brief    Set ADC Buffer Power Mode
  * @rmtoll   CFGR1    BUFMOD    FL_ADC_SetBufferPowerMode
  * @param    ADCx ADC instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_ADC_BUFF_POWER_MODE_NORMAL
  *           @arg @ref FL_ADC_BUFF_POWER_MODE_LOW
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetBufferPowerMode(ADC_Type *ADCx, uint32_t mode)
{
    MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_BUFMOD_Msk, mode);
}

/**
  * @brief    Read ADC Buffer Power Mode
  * @rmtoll   CFGR1    BUFMOD    FL_ADC_GetBufferPowerMode
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_BUFF_POWER_MODE_NORMAL
  *           @arg @ref FL_ADC_BUFF_POWER_MODE_LOW
  */
__STATIC_INLINE uint32_t FL_ADC_GetBufferPowerMode(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_BUFMOD_Msk));
}

/**
  * @brief    Set ADC Buffer Filter Mode
  * @rmtoll   CFGR1    BUFLPF    FL_ADC_SetBufferFilterMode
  * @param    ADCx ADC instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_ADC_BUFF_FILTER_MODE_NORMAL
  *           @arg @ref FL_ADC_BUFF_FILTER_MODE_LOWPASS
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetBufferFilterMode(ADC_Type *ADCx, uint32_t mode)
{
    MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_BUFLPF_Msk, mode);
}

/**
  * @brief    Read ADC Buffer Filter Mode
  * @rmtoll   CFGR1    BUFLPF    FL_ADC_GetBufferFilterMode
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_BUFF_FILTER_MODE_NORMAL
  *           @arg @ref FL_ADC_BUFF_FILTER_MODE_LOWPASS
  */
__STATIC_INLINE uint32_t FL_ADC_GetBufferFilterMode(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_BUFLPF_Msk));
}

/**
  * @brief    Enable ADC Buffer Chopper
  * @rmtoll   CFGR1    BUFCHP_EN    FL_ADC_EnableBufferChopper
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableBufferChopper(ADC_Type *ADCx)
{
    SET_BIT(ADCx->CFGR1, ADC_CFGR1_BUFCHP_EN_Msk);
}

/**
  * @brief    Disable ADC Buffer Chopper
  * @rmtoll   CFGR1    BUFCHP_EN    FL_ADC_DisableBufferChopper
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableBufferChopper(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->CFGR1, ADC_CFGR1_BUFCHP_EN_Msk);
}

/**
  * @brief    Get ADC Buffer Chopper Enable Status
  * @rmtoll   CFGR1    BUFCHP_EN    FL_ADC_IsEnabledBufferChopper
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledBufferChopper(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_BUFCHP_EN_Msk) == ADC_CFGR1_BUFCHP_EN_Msk);
}

/**
  * @brief    Enable ADC DMA
  * @rmtoll   CFGR2    DMAEN    FL_ADC_EnableDMAReq
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableDMAReq(ADC_Type *ADCx)
{
    SET_BIT(ADCx->CFGR2, ADC_CFGR2_DMAEN_Msk);
}

/**
  * @brief    Disable ADC DMA
  * @rmtoll   CFGR2    DMAEN    FL_ADC_DisableDMAReq
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableDMAReq(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->CFGR2, ADC_CFGR2_DMAEN_Msk);
}

/**
  * @brief    Get ADC DMA Enable Status
  * @rmtoll   CFGR2    DMAEN    FL_ADC_IsEnabledDMAReq
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledDMAReq(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_DMAEN_Msk) == ADC_CFGR2_DMAEN_Msk);
}

/**
  * @brief    Set ADC Channel Scan Direction
  * @rmtoll   CFGR2    SCANDIR    FL_ADC_SetSequenceScanDirection
  * @param    ADCx ADC instance
  * @param    dir This parameter can be one of the following values:
  *           @arg @ref FL_ADC_SEQ_SCAN_DIR_FORWARD
  *           @arg @ref FL_ADC_SEQ_SCAN_DIR_BACKWARD
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetSequenceScanDirection(ADC_Type *ADCx, uint32_t dir)
{
    MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_SCANDIR_Msk, dir);
}

/**
  * @brief    Get ADC Channel Scan Direction
  * @rmtoll   CFGR2    SCANDIR    FL_ADC_GetSequenceScanDirection
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_SEQ_SCAN_DIR_FORWARD
  *           @arg @ref FL_ADC_SEQ_SCAN_DIR_BACKWARD
  */
__STATIC_INLINE uint32_t FL_ADC_GetSequenceScanDirection(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_SCANDIR_Msk));
}

/**
  * @brief    Set ADC Trigger Source
  * @rmtoll   CFGR2    EXTS    FL_ADC_SetTriggerSource
  * @param    ADCx ADC instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_ADC_TRGI_LUT0
  *           @arg @ref FL_ADC_TRGI_LUT1
  *           @arg @ref FL_ADC_TRGI_LUT2
  *           @arg @ref FL_ADC_TRGI_ATIM
  *           @arg @ref FL_ADC_TRGI_GPTIM1
  *           @arg @ref FL_ADC_TRGI_GPTIM2
  *           @arg @ref FL_ADC_TRGI_BSTIM16
  *           @arg @ref FL_ADC_TRGI_LPTIM16
  *           @arg @ref FL_ADC_TRGI_COMP1
  *           @arg @ref FL_ADC_TRGI_COMP2
  *           @arg @ref FL_ADC_TRGI_RTCA
  *           @arg @ref FL_ADC_TRGI_LUT3
  *           @arg @ref FL_ADC_TRGI_GPTIM0
  *           @arg @ref FL_ADC_TRGI_COMP3
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetTriggerSource(ADC_Type *ADCx, uint32_t source)
{
    MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_EXTS_Msk, source);
}

/**
  * @brief    Get ADC Trigger Source
  * @rmtoll   CFGR2    EXTS    FL_ADC_GetTriggerSource
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_TRGI_LUT0
  *           @arg @ref FL_ADC_TRGI_LUT1
  *           @arg @ref FL_ADC_TRGI_LUT2
  *           @arg @ref FL_ADC_TRGI_ATIM
  *           @arg @ref FL_ADC_TRGI_GPTIM1
  *           @arg @ref FL_ADC_TRGI_GPTIM2
  *           @arg @ref FL_ADC_TRGI_BSTIM16
  *           @arg @ref FL_ADC_TRGI_LPTIM16
  *           @arg @ref FL_ADC_TRGI_COMP1
  *           @arg @ref FL_ADC_TRGI_COMP2
  *           @arg @ref FL_ADC_TRGI_RTCA
  *           @arg @ref FL_ADC_TRGI_LUT3
  *           @arg @ref FL_ADC_TRGI_GPTIM0
  *           @arg @ref FL_ADC_TRGI_COMP3
  */
__STATIC_INLINE uint32_t FL_ADC_GetTriggerSource(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_EXTS_Msk));
}

/**
  * @brief    Enable ADC Overrun Mode
  * @rmtoll   CFGR2    OVRM    FL_ADC_EnableOverrunMode
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableOverrunMode(ADC_Type *ADCx)
{
    SET_BIT(ADCx->CFGR2, ADC_CFGR2_OVRM_Msk);
}

/**
  * @brief    Disable ADC Overrun Mode
  * @rmtoll   CFGR2    OVRM    FL_ADC_DisableOverrunMode
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableOverrunMode(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->CFGR2, ADC_CFGR2_OVRM_Msk);
}

/**
  * @brief    Get ADC Overrun Mode Enable Status
  * @rmtoll   CFGR2    OVRM    FL_ADC_IsEnabledOverrunMode
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledOverrunMode(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_OVRM_Msk) == ADC_CFGR2_OVRM_Msk);
}

/**
  * @brief    Set ADC Conversion Mode
  * @rmtoll   CFGR2    CONT    FL_ADC_SetConversionMode
  * @param    ADCx ADC instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_ADC_CONV_MODE_SINGLE
  *           @arg @ref FL_ADC_CONV_MODE_CONTINUOUS
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetConversionMode(ADC_Type *ADCx, uint32_t mode)
{
    MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_CONT_Msk, mode);
}

/**
  * @brief    Get ADC Conversion Mode
  * @rmtoll   CFGR2    CONT    FL_ADC_GetConversionMode
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_CONV_MODE_SINGLE
  *           @arg @ref FL_ADC_CONV_MODE_CONTINUOUS
  */
__STATIC_INLINE uint32_t FL_ADC_GetConversionMode(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_CONT_Msk));
}

/**
  * @brief    Enable ADC Wait Mode
  * @rmtoll   CFGR2    WAIT    FL_ADC_EnableWaitMode
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableWaitMode(ADC_Type *ADCx)
{
    SET_BIT(ADCx->CFGR2, ADC_CFGR2_WAIT_Msk);
}

/**
  * @brief    Disable ADC Wait Mode
  * @rmtoll   CFGR2    WAIT    FL_ADC_DisableWaitMode
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableWaitMode(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->CFGR2, ADC_CFGR2_WAIT_Msk);
}

/**
  * @brief    Get ADC Wait Mode Enable Status
  * @rmtoll   CFGR2    WAIT    FL_ADC_IsEnabledWaitMode
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledWaitMode(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_WAIT_Msk) == ADC_CFGR2_WAIT_Msk);
}

/**
  * @brief    Set ADC Single Conversion Mode
  * @rmtoll   CFGR2    SEMI    FL_ADC_SetSingleConversionAutoMode
  * @param    ADCx ADC instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_ADC_SINGLE_CONV_MODE_AUTO
  *           @arg @ref FL_ADC_SINGLE_CONV_MODE_SEMIAUTO
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetSingleConversionAutoMode(ADC_Type *ADCx, uint32_t mode)
{
    MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_SEMI_Msk, mode);
}

/**
  * @brief    Get ADC Single Conversion Mode
  * @rmtoll   CFGR2    SEMI    FL_ADC_GetSingleConversionAutoMode
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_SINGLE_CONV_MODE_AUTO
  *           @arg @ref FL_ADC_SINGLE_CONV_MODE_SEMIAUTO
  */
__STATIC_INLINE uint32_t FL_ADC_GetSingleConversionAutoMode(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_SEMI_Msk));
}

/**
  * @brief    Enable ADC Trigger Filter
  * @rmtoll   CFGR2    IOTRFEN    FL_ADC_EnableTriggerFilter
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableTriggerFilter(ADC_Type *ADCx)
{
    SET_BIT(ADCx->CFGR2, ADC_CFGR2_IOTRFEN_Msk);
}

/**
  * @brief    Disable ADC Trigger Filter
  * @rmtoll   CFGR2    IOTRFEN    FL_ADC_DisableTriggerFilter
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableTriggerFilter(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->CFGR2, ADC_CFGR2_IOTRFEN_Msk);
}

/**
  * @brief    Get ADC Trigger Filter Enable Status
  * @rmtoll   CFGR2    IOTRFEN    FL_ADC_IsEnabledTriggerFilter
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledTriggerFilter(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_IOTRFEN_Msk) == ADC_CFGR2_IOTRFEN_Msk);
}

/**
  * @brief    Enable ADC OverSampling
  * @rmtoll   CFGR2    OVSEN    FL_ADC_EnableOverSampling
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableOverSampling(ADC_Type *ADCx)
{
    SET_BIT(ADCx->CFGR2, ADC_CFGR2_OVSEN_Msk);
}

/**
  * @brief    Disable ADC OverSampling
  * @rmtoll   CFGR2    OVSEN    FL_ADC_DisableOverSampling
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableOverSampling(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->CFGR2, ADC_CFGR2_OVSEN_Msk);
}

/**
  * @brief    Get ADC OverSampling Enable Status
  * @rmtoll   CFGR2    OVSEN    FL_ADC_IsEnabledOverSampling
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledOverSampling(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_OVSEN_Msk) == ADC_CFGR2_OVSEN_Msk);
}

/**
  * @brief    Set ADC OverSampling Multiplier
  * @rmtoll   CFGR2    OVSR    FL_ADC_SetOverSamplingMultiplier
  * @param    ADCx ADC instance
  * @param    mul This parameter can be one of the following values:
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_2X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_4X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_8X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_16X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_32X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_64X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_128X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_256X
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetOverSamplingMultiplier(ADC_Type *ADCx, uint32_t mul)
{
    MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_OVSR_Msk, mul);
}

/**
  * @brief    Read ADC OverSampling Multiplier
  * @rmtoll   CFGR2    OVSR    FL_ADC_GetOverSamplingMultiplier
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_2X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_4X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_8X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_16X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_32X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_64X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_128X
  *           @arg @ref FL_ADC_OVERSAMPLING_MUL_256X
  */
__STATIC_INLINE uint32_t FL_ADC_GetOverSamplingMultiplier(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_OVSR_Msk));
}

/**
  * @brief    Set ADC OverSampling Shift
  * @rmtoll   CFGR2    OVSS    FL_ADC_SetOverSamplingShift
  * @param    ADCx ADC instance
  * @param    shift This parameter can be one of the following values:
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_0B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_1B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_2B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_3B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_4B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_5B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_6B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_7B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_8B
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetOverSamplingShift(ADC_Type *ADCx, uint32_t shift)
{
    MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_OVSS_Msk, shift);
}

/**
  * @brief    Read ADC OverSampling Shift
  * @rmtoll   CFGR2    OVSS    FL_ADC_GetOverSamplingShift
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_0B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_1B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_2B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_3B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_4B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_5B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_6B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_7B
  *           @arg @ref FL_ADC_OVERSAMPLING_SHIFT_8B
  */
__STATIC_INLINE uint32_t FL_ADC_GetOverSamplingShift(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_OVSS_Msk));
}

/**
  * @brief    Enable ADC Analog WDG
  * @rmtoll   CFGR2    AWDEN    FL_ADC_EnableAnalogWDG
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableAnalogWDG(ADC_Type *ADCx)
{
    SET_BIT(ADCx->CFGR2, ADC_CFGR2_AWDEN_Msk);
}

/**
  * @brief    Disable ADC Analog WDG
  * @rmtoll   CFGR2    AWDEN    FL_ADC_DisableAnalogWDG
  * @param    ADCx ADC instance
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableAnalogWDG(ADC_Type *ADCx)
{
    CLEAR_BIT(ADCx->CFGR2, ADC_CFGR2_AWDEN_Msk);
}

/**
  * @brief    Get ADC Analog WDG Enable Status
  * @rmtoll   CFGR2    AWDEN    FL_ADC_IsEnabledAnalogWDG
  * @param    ADCx ADC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledAnalogWDG(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_AWDEN_Msk) == ADC_CFGR2_AWDEN_Msk);
}

/**
  * @brief    Set ADC Analog WDG Monitor Mode
  * @rmtoll   CFGR2    AWDSC    FL_ADC_SetAnalogWDGMonitorMode
  * @param    ADCx ADC instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_ADC_AWDG_ALL_CHANNEL
  *           @arg @ref FL_ADC_AWDG_SINGLE_CHANNEL
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetAnalogWDGMonitorMode(ADC_Type *ADCx, uint32_t mode)
{
    MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_AWDSC_Msk, mode);
}

/**
  * @brief    Read ADC Analog WDG Monitor Mode
  * @rmtoll   CFGR2    AWDSC    FL_ADC_GetAnalogWDGMonitorMode
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_AWDG_ALL_CHANNEL
  *           @arg @ref FL_ADC_AWDG_SINGLE_CHANNEL
  */
__STATIC_INLINE uint32_t FL_ADC_GetAnalogWDGMonitorMode(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_AWDSC_Msk));
}

/**
  * @brief    Set ADC Analog WDG Monitor Channel
  * @rmtoll   CFGR2    AWDCH    FL_ADC_SetAnalogWDGMonitorChannel
  * @param    ADCx ADC instance
  * @param    monitorChannel This parameter can be one of the following values:
  *           @arg @ref FL_ADC_AWDG_CH0
  *           @arg @ref FL_ADC_AWDG_CH1
  *           @arg @ref FL_ADC_AWDG_CH2
  *           @arg @ref FL_ADC_AWDG_CH3
  *           @arg @ref FL_ADC_AWDG_CH4
  *           @arg @ref FL_ADC_AWDG_CH5
  *           @arg @ref FL_ADC_AWDG_CH6
  *           @arg @ref FL_ADC_AWDG_CH7
  *           @arg @ref FL_ADC_AWDG_CH8
  *           @arg @ref FL_ADC_AWDG_CH9
  *           @arg @ref FL_ADC_AWDG_CH10
  *           @arg @ref FL_ADC_AWDG_CH11
  *           @arg @ref FL_ADC_AWDG_CH12
  *           @arg @ref FL_ADC_AWDG_CH13
  *           @arg @ref FL_ADC_AWDG_CH14
  *           @arg @ref FL_ADC_AWDG_CH15
  *           @arg @ref FL_ADC_AWDG_CH16
  *           @arg @ref FL_ADC_AWDG_CH17
  *           @arg @ref FL_ADC_AWDG_CH18
  *           @arg @ref FL_ADC_AWDG_CH19
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetAnalogWDGMonitorChannel(ADC_Type *ADCx, uint32_t monitorChannel)
{
    MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_AWDCH_Msk, monitorChannel);
}

/**
  * @brief    Read ADC Analog WDG Monitor Channel
  * @rmtoll   CFGR2    AWDCH    FL_ADC_GetAnalogWDGMonitorChannel
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_AWDG_CH0
  *           @arg @ref FL_ADC_AWDG_CH1
  *           @arg @ref FL_ADC_AWDG_CH2
  *           @arg @ref FL_ADC_AWDG_CH3
  *           @arg @ref FL_ADC_AWDG_CH4
  *           @arg @ref FL_ADC_AWDG_CH5
  *           @arg @ref FL_ADC_AWDG_CH6
  *           @arg @ref FL_ADC_AWDG_CH7
  *           @arg @ref FL_ADC_AWDG_CH8
  *           @arg @ref FL_ADC_AWDG_CH9
  *           @arg @ref FL_ADC_AWDG_CH10
  *           @arg @ref FL_ADC_AWDG_CH11
  *           @arg @ref FL_ADC_AWDG_CH12
  *           @arg @ref FL_ADC_AWDG_CH13
  *           @arg @ref FL_ADC_AWDG_CH14
  *           @arg @ref FL_ADC_AWDG_CH15
  *           @arg @ref FL_ADC_AWDG_CH16
  *           @arg @ref FL_ADC_AWDG_CH17
  *           @arg @ref FL_ADC_AWDG_CH18
  *           @arg @ref FL_ADC_AWDG_CH19
  */
__STATIC_INLINE uint32_t FL_ADC_GetAnalogWDGMonitorChannel(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_AWDCH_Msk));
}

/**
  * @brief    Set ADC Slow Channel Sampling Time
  * @rmtoll   SMTR    SMTS1    FL_ADC_SetSlowChannelSamplingTime
  * @param    ADCx ADC instance
  * @param    time This parameter can be one of the following values:
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_2_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_4_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_8_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_12_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_16_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_32_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_64_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_80_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_96_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_128_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_160_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_192_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_256_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_320_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_384_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_512_ADCCLK
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetSlowChannelSamplingTime(ADC_Type *ADCx, uint32_t time)
{
    MODIFY_REG(ADCx->SMTR, ADC_SMTR_SMTS1_Msk, time);
}

/**
  * @brief    Read ADC Slow Channel Sampling Time
  * @rmtoll   SMTR    SMTS1    FL_ADC_GetSlowChannelSamplingTime
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_2_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_4_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_8_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_12_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_16_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_32_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_64_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_80_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_96_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_128_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_160_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_192_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_256_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_320_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_384_ADCCLK
  *           @arg @ref FL_ADC_SLOW_CH_SAMPLING_TIME_512_ADCCLK
  */
__STATIC_INLINE uint32_t FL_ADC_GetSlowChannelSamplingTime(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->SMTR, ADC_SMTR_SMTS1_Msk));
}

/**
  * @brief    Set ADC Fast Channel Sampling Time
  * @rmtoll   SMTR    SMTS2    FL_ADC_SetFastChannelSamplingTime
  * @param    ADCx ADC instance
  * @param    time This parameter can be one of the following values:
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_2_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_4_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_8_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_12_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_16_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_32_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_64_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_80_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_96_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_128_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_160_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_192_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_256_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_320_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_384_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_512_ADCCLK
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_SetFastChannelSamplingTime(ADC_Type *ADCx, uint32_t time)
{
    MODIFY_REG(ADCx->SMTR, ADC_SMTR_SMTS2_Msk, time);
}

/**
  * @brief    Read ADC Fast Channel Sampling Time
  * @rmtoll   SMTR    SMTS2    FL_ADC_GetFastChannelSamplingTime
  * @param    ADCx ADC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_2_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_4_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_8_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_12_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_16_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_32_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_64_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_80_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_96_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_128_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_160_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_192_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_256_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_320_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_384_ADCCLK
  *           @arg @ref FL_ADC_FAST_CH_SAMPLING_TIME_512_ADCCLK
  */
__STATIC_INLINE uint32_t FL_ADC_GetFastChannelSamplingTime(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->SMTR, ADC_SMTR_SMTS2_Msk));
}

/**
  * @brief    Enable ADC Channel
  * @rmtoll   CHER        FL_ADC_EnableSequencerChannel
  * @param    ADCx ADC instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ADC_EXTERNAL_CH0
  *           @arg @ref FL_ADC_EXTERNAL_CH1
  *           @arg @ref FL_ADC_EXTERNAL_CH2
  *           @arg @ref FL_ADC_EXTERNAL_CH3
  *           @arg @ref FL_ADC_EXTERNAL_CH4
  *           @arg @ref FL_ADC_EXTERNAL_CH5
  *           @arg @ref FL_ADC_EXTERNAL_CH6
  *           @arg @ref FL_ADC_EXTERNAL_CH7
  *           @arg @ref FL_ADC_EXTERNAL_CH8
  *           @arg @ref FL_ADC_EXTERNAL_CH9
  *           @arg @ref FL_ADC_EXTERNAL_CH10
  *           @arg @ref FL_ADC_EXTERNAL_CH11
  *           @arg @ref FL_ADC_EXTERNAL_CH12
  *           @arg @ref FL_ADC_EXTERNAL_CH13
  *           @arg @ref FL_ADC_EXTERNAL_CH14
  *           @arg @ref FL_ADC_EXTERNAL_CH15
  *           @arg @ref FL_ADC_EXTERNAL_CH16
  *           @arg @ref FL_ADC_EXTERNAL_CH17
  *           @arg @ref FL_ADC_EXTERNAL_CH18
  *           @arg @ref FL_ADC_EXTERNAL_CH19
  *           @arg @ref FL_ADC_INTERNAL_VREF1P2
  *           @arg @ref FL_ADC_INTERNAL_TS
  *           @arg @ref FL_ADC_INTERNAL_AVREF
  *           @arg @ref FL_ADC_INTERNAL_VBAT_DIV3
  *           @arg @ref FL_ADC_INTERNAL_VDD_DIV3
  *           @arg @ref FL_ADC_INTERNAL_DAC
  *           @arg @ref FL_ADC_INTERNAL_OPA
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableSequencerChannel(ADC_Type *ADCx, uint32_t channel)
{
    SET_BIT(ADCx->CHER, ((channel & 0x7fffffff) << 0x0U));
}

/**
  * @brief    Disable ADC Channel
  * @rmtoll   CHER        FL_ADC_DisableSequencerChannel
  * @param    ADCx ADC instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ADC_EXTERNAL_CH0
  *           @arg @ref FL_ADC_EXTERNAL_CH1
  *           @arg @ref FL_ADC_EXTERNAL_CH2
  *           @arg @ref FL_ADC_EXTERNAL_CH3
  *           @arg @ref FL_ADC_EXTERNAL_CH4
  *           @arg @ref FL_ADC_EXTERNAL_CH5
  *           @arg @ref FL_ADC_EXTERNAL_CH6
  *           @arg @ref FL_ADC_EXTERNAL_CH7
  *           @arg @ref FL_ADC_EXTERNAL_CH8
  *           @arg @ref FL_ADC_EXTERNAL_CH9
  *           @arg @ref FL_ADC_EXTERNAL_CH10
  *           @arg @ref FL_ADC_EXTERNAL_CH11
  *           @arg @ref FL_ADC_EXTERNAL_CH12
  *           @arg @ref FL_ADC_EXTERNAL_CH13
  *           @arg @ref FL_ADC_EXTERNAL_CH14
  *           @arg @ref FL_ADC_EXTERNAL_CH15
  *           @arg @ref FL_ADC_EXTERNAL_CH16
  *           @arg @ref FL_ADC_EXTERNAL_CH17
  *           @arg @ref FL_ADC_EXTERNAL_CH18
  *           @arg @ref FL_ADC_EXTERNAL_CH19
  *           @arg @ref FL_ADC_INTERNAL_VREF1P2
  *           @arg @ref FL_ADC_INTERNAL_TS
  *           @arg @ref FL_ADC_INTERNAL_AVREF
  *           @arg @ref FL_ADC_INTERNAL_VBAT_DIV3
  *           @arg @ref FL_ADC_INTERNAL_VDD_DIV3
  *           @arg @ref FL_ADC_INTERNAL_DAC
  *           @arg @ref FL_ADC_INTERNAL_OPA
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableSequencerChannel(ADC_Type *ADCx, uint32_t channel)
{
    CLEAR_BIT(ADCx->CHER, ((channel & 0x7fffffff) << 0x0U));
}

/**
  * @brief    Get ADC Channel Enable Status
  * @rmtoll   CHER        FL_ADC_IsEnabledSequencerChannel
  * @param    ADCx ADC instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ADC_EXTERNAL_CH0
  *           @arg @ref FL_ADC_EXTERNAL_CH1
  *           @arg @ref FL_ADC_EXTERNAL_CH2
  *           @arg @ref FL_ADC_EXTERNAL_CH3
  *           @arg @ref FL_ADC_EXTERNAL_CH4
  *           @arg @ref FL_ADC_EXTERNAL_CH5
  *           @arg @ref FL_ADC_EXTERNAL_CH6
  *           @arg @ref FL_ADC_EXTERNAL_CH7
  *           @arg @ref FL_ADC_EXTERNAL_CH8
  *           @arg @ref FL_ADC_EXTERNAL_CH9
  *           @arg @ref FL_ADC_EXTERNAL_CH10
  *           @arg @ref FL_ADC_EXTERNAL_CH11
  *           @arg @ref FL_ADC_EXTERNAL_CH12
  *           @arg @ref FL_ADC_EXTERNAL_CH13
  *           @arg @ref FL_ADC_EXTERNAL_CH14
  *           @arg @ref FL_ADC_EXTERNAL_CH15
  *           @arg @ref FL_ADC_EXTERNAL_CH16
  *           @arg @ref FL_ADC_EXTERNAL_CH17
  *           @arg @ref FL_ADC_EXTERNAL_CH18
  *           @arg @ref FL_ADC_EXTERNAL_CH19
  *           @arg @ref FL_ADC_INTERNAL_VREF1P2
  *           @arg @ref FL_ADC_INTERNAL_TS
  *           @arg @ref FL_ADC_INTERNAL_AVREF
  *           @arg @ref FL_ADC_INTERNAL_VBAT_DIV3
  *           @arg @ref FL_ADC_INTERNAL_VDD_DIV3
  *           @arg @ref FL_ADC_INTERNAL_DAC
  *           @arg @ref FL_ADC_INTERNAL_OPA
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledSequencerChannel(ADC_Type *ADCx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(ADCx->CHER, ((channel & 0x7fffffff) << 0x0U)) == ((channel & 0x7fffffff) << 0x0U));
}

/**
  * @brief    Enable ADC Differential Channel
  * @rmtoll   DCR        FL_ADC_EnableDifferentialChannel
  * @param    ADCx ADC instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP0
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP1
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP2
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP3
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP4
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP5
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP6
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_EnableDifferentialChannel(ADC_Type *ADCx, uint32_t channel)
{
    SET_BIT(ADCx->DCR, ((channel & 0x7f) << 0x0U));
}

/**
  * @brief    Disable ADC Differential Channel
  * @rmtoll   DCR        FL_ADC_DisableDifferentialChannel
  * @param    ADCx ADC instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP0
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP1
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP2
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP3
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP4
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP5
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP6
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_DisableDifferentialChannel(ADC_Type *ADCx, uint32_t channel)
{
    CLEAR_BIT(ADCx->DCR, ((channel & 0x7f) << 0x0U));
}

/**
  * @brief    Get ADC Differential Channel Enable Status
  * @rmtoll   DCR        FL_ADC_IsEnabledDifferentialChannel
  * @param    ADCx ADC instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP0
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP1
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP2
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP3
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP4
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP5
  *           @arg @ref FL_ADC_DIFFERENTIAL_GROUP6
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_ADC_IsEnabledDifferentialChannel(ADC_Type *ADCx, uint32_t channel)
{
    return (uint32_t)(READ_BIT(ADCx->DCR, ((channel & 0x7f) << 0x0U)) == ((channel & 0x7f) << 0x0U));
}

/**
  * @brief    Get ADC Conversion Data
  * @rmtoll   DR    DATA    FL_ADC_ReadConversionData
  * @param    ADCx ADC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_ADC_ReadConversionData(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->DR, (0xffffU << 0U)) >> 0U);
}

/**
  * @brief    Write ADC Analog Watchdog Under Low
  * @rmtoll   HLTR    AWD_LT    FL_ADC_WriteAnalogWDGLowThreshold
  * @param    ADCx ADC instance
  * @param    threshold
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_WriteAnalogWDGLowThreshold(ADC_Type *ADCx, uint32_t threshold)
{
    MODIFY_REG(ADCx->HLTR, (0xffffU << 0U), (threshold << 0U));
}

/**
  * @brief    Read ADC Analog Watchdog Under Low
  * @rmtoll   HLTR    AWD_LT    FL_ADC_ReadAnalogWDGLowThreshold
  * @param    ADCx ADC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_ADC_ReadAnalogWDGLowThreshold(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->HLTR, (0xffffU << 0U)) >> 0U);
}

/**
  * @brief    Write ADC Analog Watchdog Above High
  * @rmtoll   HLTR    AWD_HT    FL_ADC_WriteAnalogWDGHighThreshold
  * @param    ADCx ADC instance
  * @param    threshold
  * @retval   None
  */
__STATIC_INLINE void FL_ADC_WriteAnalogWDGHighThreshold(ADC_Type *ADCx, uint32_t threshold)
{
    MODIFY_REG(ADCx->HLTR, (0xffffU << 16U), (threshold << 16U));
}

/**
  * @brief    Read ADC Analog Watchdog Above High
  * @rmtoll   HLTR    AWD_HT    FL_ADC_ReadAnalogWDGHighThreshold
  * @param    ADCx ADC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_ADC_ReadAnalogWDGHighThreshold(ADC_Type *ADCx)
{
    return (uint32_t)(READ_BIT(ADCx->HLTR, (0xffffU << 16U)) >> 16U);
}

/**
  * @}
  */

/** @defgroup ADC_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_ADC_CommonDeInit(void);
FL_ErrorStatus  FL_ADC_DeInit(ADC_Type *ADCx);
uint32_t GetActualVddaVoltage(ADC_Type *ADCx);
void FL_ADC_StructInit(FL_ADC_InitTypeDef *ADC_InitStruct);
FL_ErrorStatus FL_ADC_Init(ADC_Type *ADCx, FL_ADC_InitTypeDef  *ADC_InitStruct);
void FL_ADC_CommonStructInit(FL_ADC_CommonInitTypeDef *ADC_CommonInitStruct);
FL_ErrorStatus FL_ADC_CommonInit(FL_ADC_CommonInitTypeDef *ADC_CommonInitStruct);

/**
  * @}
  */


/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __FM33LG0XX_FL_ADC_H*/

/*************************Py_Code_Generator Version: 0.1-0.14-0.1 @ 2022-05-09*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
