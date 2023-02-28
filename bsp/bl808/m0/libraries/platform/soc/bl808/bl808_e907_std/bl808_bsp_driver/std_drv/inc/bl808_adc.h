/**
  ******************************************************************************
  * @file    bl808_adc.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL808_ADC_H__
#define __BL808_ADC_H__

#include "aon_reg.h"
#include "gpip_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  ADC
 *  @{
 */

/** @defgroup  ADC_Public_Types
 *  @{
 */

/**
 *  @brief ADC channel type definition
 */
typedef enum {
    ADC_CHAN0,          /*!< ADC channel 0 */
    ADC_CHAN1,          /*!< ADC channel 1 */
    ADC_CHAN2,          /*!< ADC channel 2 */
    ADC_CHAN3,          /*!< ADC channel 3 */
    ADC_CHAN4,          /*!< ADC channel 4 */
    ADC_CHAN5,          /*!< ADC channel 5 */
    ADC_CHAN6,          /*!< ADC channel 6 */
    ADC_CHAN7,          /*!< ADC channel 7 */
    ADC_CHAN8,          /*!< ADC channel 8 */
    ADC_CHAN9,          /*!< ADC channel 9 */
    ADC_CHAN10,         /*!< ADC channel 10 */
    ADC_CHAN11,         /*!< ADC channel 11 */
    ADC_CHAN_DAC_OUTA,  /*!< DACA, ADC channel 12 */
    ADC_CHAN_DAC_OUTB,  /*!< DACB, ADC channel 13 */
    ADC_CHAN_TSEN_P,    /*!< TSenp, ADC channel 14 */
    ADC_CHAN_TSEN_N,    /*!< TSenn, ADC channel 15 */
    ADC_CHAN_VREF,      /*!< Vref, ADC channel 16 */
    ADC_CHAN_DCTEST,    /*!< DCTest, ADC channel 17 */
    ADC_CHAN_VABT_HALF, /*!< VBAT/2, ADC channel 18 */
    ADC_CHAN_SENP3,     /*!< SenVP3, ADC channel 19 */
    ADC_CHAN_SENP2,     /*!< SenVP2, ADC channel 20 */
    ADC_CHAN_SENP1,     /*!< SenVP1, ADC channel 21 */
    ADC_CHAN_SENP0,     /*!< SenVP0, ADC channel 22 */
    ADC_CHAN_GND,       /*!< GND, ADC channel 23 */
} ADC_Chan_Type;

/**
 *  @brief ADC V18 selection type definition
 */
typedef enum {
    ADC_V18_SEL_1P62V, /*!< V18 select 1.62V */
    ADC_V18_SEL_1P72V, /*!< V18 select 1.72V */
    ADC_V18_SEL_1P82V, /*!< V18 select 1.82V */
    ADC_V18_SEL_1P92V, /*!< V18 select 1.92V */
} ADC_V18_SEL_Type;

/**
 *  @brief ADC V11 selection type definition
 */
typedef enum {
    ADC_V11_SEL_1P0V,  /*!< V11 select 1.0V */
    ADC_V11_SEL_1P1V,  /*!< V11 select 1.1V */
    ADC_V11_SEL_1P18V, /*!< V11 select 1.18V */
    ADC_V11_SEL_1P26V, /*!< V11 select 1.26V */
} ADC_V11_SEL_Type;

/**
 *  @brief ADC clock type definition
 */
typedef enum {
    ADC_CLK_DIV_1,  /*!< ADC clock:on 32M clock is 32M */
    ADC_CLK_DIV_4,  /*!< ADC clock:on 32M clock is 8M */
    ADC_CLK_DIV_8,  /*!< ADC clock:on 32M clock is 4M */
    ADC_CLK_DIV_12, /*!< ADC clock:on 32M clock is 2.666M */
    ADC_CLK_DIV_16, /*!< ADC clock:on 32M clock is 2M */
    ADC_CLK_DIV_20, /*!< ADC clock:on 32M clock is 1.6M */
    ADC_CLK_DIV_24, /*!< ADC clock:on 32M clock is 1.333M */
    ADC_CLK_DIV_32, /*!< ADC clock:on 32M clock is 1M */
} ADC_CLK_Type;

/**
 *  @brief ADC conversion speed type definition
 */
typedef enum {
    ADC_DELAY_SEL_0, /*!< Select delay 0 */
    ADC_DELAY_SEL_1, /*!< Select delay 1 */
    ADC_DELAY_SEL_2, /*!< Select delay 2 */
    ADC_DELAY_SEL_3, /*!< Select delay 3 */
    ADC_DELAY_SEL_4, /*!< Select delay 4, not recommend */
    ADC_DELAY_SEL_5, /*!< Select delay 5, not recommend */
    ADC_DELAY_SEL_6, /*!< Select delay 6, not recommend */
    ADC_DELAY_SEL_7, /*!< Select delay 7, not recommend */
} ADC_DELAY_SEL_Type;

/**
 *  @brief ADC PGA gain type definition
 */
typedef enum {
    ADC_PGA_GAIN_NONE, /*!< No PGA gain */
    ADC_PGA_GAIN_1,    /*!< PGA gain 1 */
    ADC_PGA_GAIN_2,    /*!< PGA gain 2 */
    ADC_PGA_GAIN_4,    /*!< PGA gain 4 */
    ADC_PGA_GAIN_8,    /*!< PGA gain 8 */
    ADC_PGA_GAIN_16,   /*!< PGA gain 16 */
    ADC_PGA_GAIN_32,   /*!< PGA gain 32 */
} ADC_PGA_GAIN_Type;

/**
 *  @brief ADC analog portion low power mode selection type definition
 */
typedef enum {
    ADC_BIAS_SEL_MAIN_BANDGAP, /*!< ADC current from main bandgap */
    ADC_BIAS_SEL_AON_BANDGAP,  /*!< ADC current from aon bandgap for HBN mode */
} ADC_BIAS_SEL_Type;

/**
 *  @brief ADC chop mode type definition
 */
typedef enum {
    ADC_CHOP_MOD_ALL_OFF,       /*!< all off */
    ADC_CHOP_MOD_AZ_ON,         /*!< Vref AZ on */
    ADC_CHOP_MOD_AZ_PGA_ON,     /*!< Vref AZ and PGA chop on */
    ADC_CHOP_MOD_AZ_PGA_RPC_ON, /*!< Vref AZ and PGA chop+RPC on */
} ADC_CHOP_MOD_Type;

/**
 *  @brief ADC audio PGA output common mode control type definition
 */
typedef enum {
    ADC_PGA_VCM_1V,   /*!< ADC VCM=1V */
    ADC_PGA_VCM_1P2V, /*!< ADC VCM=1.2V */
    ADC_PGA_VCM_1P4V, /*!< ADC VCM=1.4V */
    ADC_PGA_VCM_1P6V, /*!< ADC VCM=1.6V */
} ADC_PGA_VCM_Type;

/**
 *  @brief ADC tsen diode mode type definition
 */
typedef enum {
    ADC_TSEN_MOD_INTERNAL_DIODE, /*!< Internal diode mode */
    ADC_TSEN_MOD_EXTERNAL_DIODE, /*!< External diode mode */
} ADC_TSEN_MOD_Type;

/**
 *  @brief ADC voltage reference type definition
 */
typedef enum {
    ADC_VREF_3P2V, /*!< ADC select 3.2V as reference voltage */
    ADC_VREF_2P0V, /*!< ADC select 2V as reference voltage */
} ADC_VREF_Type;

/**
 *  @brief ADC signal input type definition
 */
typedef enum {
    ADC_INPUT_SINGLE_END, /*!< ADC signal is single end */
    ADC_INPUT_DIFF,       /*!< ADC signal is differential */
} ADC_SIG_INPUT_Type;

/**
 *  @brief ADC data width type definition
 */
typedef enum {
    ADC_DATA_WIDTH_12,                  /*!< ADC 12 bits */
    ADC_DATA_WIDTH_14_WITH_16_AVERAGE,  /*!< ADC 14 bits,and the value is average of 16 converts */
    ADC_DATA_WIDTH_14_WITH_64_AVERAGE,  /*!< ADC 14 bits,and the value is average of 64 converts */
    ADC_DATA_WIDTH_16_WITH_128_AVERAGE, /*!< ADC 16 bits,and the value is average of 128 converts */
    ADC_DATA_WIDTH_16_WITH_256_AVERAGE, /*!< ADC 16 bits,and the value is average of 256 converts */
} ADC_Data_Width_Type;

/**
 *  @brief ADC micboost 32db type definition
 */
typedef enum {
    ADC_MICBOOST_DB_16DB, /*!< MIC boost 16db */
    ADC_MICBOOST_DB_32DB, /*!< MIC boost 32db */
} ADC_MICBOOST_DB_Type;

/**
 *  @brief ADC pga2 gain type definition
 */
typedef enum {
    ADC_PGA2_GAIN_0DB,  /*!< MIC pga2 gain 0db */
    ADC_PGA2_GAIN_6DB,  /*!< MIC pga2 gain 6db */
    ADC_PGA2_GAIN_N6DB, /*!< MIC pga2 gain -6db */
    ADC_PGA2_GAIN_12DB, /*!< MIC pga2 gain 12db */
} ADC_PGA2_GAIN_Type;

/**
 *  @brief ADC mic mode type definition
 */
typedef enum {
    ADC_MIC_MODE_SINGLE, /*!< MIC single mode */
    ADC_MIC_MODE_DIFF,   /*!< MIC diff mode */
} ADC_MIC_MODE_Type;

/**
 *  @brief ADC mic type definition
 */
typedef struct
{
    ADC_MICBOOST_DB_Type micboostDb; /*!< MIC boost db */
    ADC_PGA2_GAIN_Type micPga2Gain;  /*!< MIC pga2 gain */
    ADC_MIC_MODE_Type mic1Mode;      /*!< MIC1 single or diff */
    ADC_MIC_MODE_Type mic2Mode;      /*!< MIC2 single or diff */
    BL_Fun_Type dwaEn;               /*!< Improve dynamic performance */
    BL_Fun_Type micboostBypassEn;    /*!< MIC boost amp bypass enable or disable */
    BL_Fun_Type micPgaEn;            /*!< MIC pga enable or disable */
    BL_Fun_Type micBiasEn;           /*!< MIC bias enable or disable */
} ADC_MIC_Type;

/**
 *  @brief ADC configuration type definition
 */
typedef struct
{
    ADC_V18_SEL_Type v18Sel;      /*!< ADC 1.8V select */
    ADC_V11_SEL_Type v11Sel;      /*!< ADC 1.1V select */
    ADC_CLK_Type clkDiv;          /*!< Clock divider */
    ADC_PGA_GAIN_Type gain1;      /*!< PGA gain 1 */
    ADC_PGA_GAIN_Type gain2;      /*!< PGA gain 2 */
    ADC_CHOP_MOD_Type chopMode;   /*!< ADC chop mode select */
    ADC_BIAS_SEL_Type biasSel;    /*!< ADC current form main bandgap or aon bandgap */
    ADC_PGA_VCM_Type vcm;         /*!< ADC VCM value */
    ADC_VREF_Type vref;           /*!< ADC voltage reference */
    ADC_SIG_INPUT_Type inputMode; /*!< ADC input signal type */
    ADC_Data_Width_Type resWidth; /*!< ADC resolution and oversample rate */
    BL_Fun_Type offsetCalibEn;    /*!< Offset calibration enable */
    int16_t offsetCalibVal;       /*!< Offset calibration value */
} ADC_CFG_Type;

/**
 *  @brief ADC configuration type definition
 */
typedef struct
{
    int8_t posChan; /*!< Positive channel */
    int8_t negChan; /*!< Negative channel */
    uint16_t value; /*!< ADC value */
    float volt;     /*!< ADC voltage result */
} ADC_Result_Type;

/**
 *  @brief ADC FIFO threshold type definition
 */
typedef enum {
    ADC_FIFO_THRESHOLD_1,  /*!< ADC FIFO threshold is 1 */
    ADC_FIFO_THRESHOLD_4,  /*!< ADC FIFO threshold is 4 */
    ADC_FIFO_THRESHOLD_8,  /*!< ADC FIFO threshold is 8 */
    ADC_FIFO_THRESHOLD_16, /*!< ADC FIFO threshold is 16 */
} ADC_FIFO_Threshold_Type;

/**
 *  @brief ADC interrupt type definition
 */
typedef enum {
    ADC_INT_POS_SATURATION, /*!< ADC positive channel saturation */
    ADC_INT_NEG_SATURATION, /*!< ADC negative channel saturation */
    ADC_INT_FIFO_UNDERRUN,  /*!< ADC FIFO underrun interrupt */
    ADC_INT_FIFO_OVERRUN,   /*!< ADC FIFO overrun interrupt */
    ADC_INT_ADC_READY,      /*!< ADC data ready interrupt */
    ADC_INT_ALL,            /*!< ADC all the interrupt */
} ADC_INT_Type;

/**
 *  @brief ADC FIFO configuration structure type definition
 */
typedef struct
{
    ADC_FIFO_Threshold_Type fifoThreshold; /*!< ADC FIFO threshold */
    BL_Fun_Type dmaEn;                     /*!< ADC DMA enable */
} ADC_FIFO_Cfg_Type;

/**
 *  @brief ADC REG GAIN CAL
 */
typedef struct
{
    BL_Fun_Type adcGainCoeffEnable; /*!< ADC_Gain_Coeff enable */
    uint16_t adcgainCoeffVal;       /*!< ADC_Gain_Coeff value */
    float coe;                      /*!< ADC_Gain_Coeff result */
} ADC_Gain_Coeff_Type;

/*@} end of group ADC_Public_Types */

/** @defgroup  ADC_Public_Constants
 *  @{
 */

/** @defgroup  ADC_CHAN_TYPE
 *  @{
 */
#define IS_ADC_CHAN_TYPE(type) (((type) == ADC_CHAN0) ||          \
                                ((type) == ADC_CHAN1) ||          \
                                ((type) == ADC_CHAN2) ||          \
                                ((type) == ADC_CHAN3) ||          \
                                ((type) == ADC_CHAN4) ||          \
                                ((type) == ADC_CHAN5) ||          \
                                ((type) == ADC_CHAN6) ||          \
                                ((type) == ADC_CHAN7) ||          \
                                ((type) == ADC_CHAN8) ||          \
                                ((type) == ADC_CHAN9) ||          \
                                ((type) == ADC_CHAN10) ||         \
                                ((type) == ADC_CHAN11) ||         \
                                ((type) == ADC_CHAN_DAC_OUTA) ||  \
                                ((type) == ADC_CHAN_DAC_OUTB) ||  \
                                ((type) == ADC_CHAN_TSEN_P) ||    \
                                ((type) == ADC_CHAN_TSEN_N) ||    \
                                ((type) == ADC_CHAN_VREF) ||      \
                                ((type) == ADC_CHAN_DCTEST) ||    \
                                ((type) == ADC_CHAN_VABT_HALF) || \
                                ((type) == ADC_CHAN_SENP3) ||     \
                                ((type) == ADC_CHAN_SENP2) ||     \
                                ((type) == ADC_CHAN_SENP1) ||     \
                                ((type) == ADC_CHAN_SENP0) ||     \
                                ((type) == ADC_CHAN_GND))

/** @defgroup  ADC_V18_SEL_TYPE
 *  @{
 */
#define IS_ADC_V18_SEL_TYPE(type) (((type) == ADC_V18_SEL_1P62V) || \
                                   ((type) == ADC_V18_SEL_1P72V) || \
                                   ((type) == ADC_V18_SEL_1P82V) || \
                                   ((type) == ADC_V18_SEL_1P92V))

/** @defgroup  ADC_V11_SEL_TYPE
 *  @{
 */
#define IS_ADC_V11_SEL_TYPE(type) (((type) == ADC_V11_SEL_1P0V) ||  \
                                   ((type) == ADC_V11_SEL_1P1V) ||  \
                                   ((type) == ADC_V11_SEL_1P18V) || \
                                   ((type) == ADC_V11_SEL_1P26V))

/** @defgroup  ADC_CLK_TYPE
 *  @{
 */
#define IS_ADC_CLK_TYPE(type) (((type) == ADC_CLK_DIV_1) ||  \
                               ((type) == ADC_CLK_DIV_4) ||  \
                               ((type) == ADC_CLK_DIV_8) ||  \
                               ((type) == ADC_CLK_DIV_12) || \
                               ((type) == ADC_CLK_DIV_16) || \
                               ((type) == ADC_CLK_DIV_20) || \
                               ((type) == ADC_CLK_DIV_24) || \
                               ((type) == ADC_CLK_DIV_32))

/** @defgroup  ADC_DELAY_SEL_TYPE
 *  @{
 */
#define IS_ADC_DELAY_SEL_TYPE(type) (((type) == ADC_DELAY_SEL_0) || \
                                     ((type) == ADC_DELAY_SEL_1) || \
                                     ((type) == ADC_DELAY_SEL_2) || \
                                     ((type) == ADC_DELAY_SEL_3) || \
                                     ((type) == ADC_DELAY_SEL_4) || \
                                     ((type) == ADC_DELAY_SEL_5) || \
                                     ((type) == ADC_DELAY_SEL_6) || \
                                     ((type) == ADC_DELAY_SEL_7))

/** @defgroup  ADC_PGA_GAIN_TYPE
 *  @{
 */
#define IS_ADC_PGA_GAIN_TYPE(type) (((type) == ADC_PGA_GAIN_NONE) || \
                                    ((type) == ADC_PGA_GAIN_1) ||    \
                                    ((type) == ADC_PGA_GAIN_2) ||    \
                                    ((type) == ADC_PGA_GAIN_4) ||    \
                                    ((type) == ADC_PGA_GAIN_8) ||    \
                                    ((type) == ADC_PGA_GAIN_16) ||   \
                                    ((type) == ADC_PGA_GAIN_32))

/** @defgroup  ADC_BIAS_SEL_TYPE
 *  @{
 */
#define IS_ADC_BIAS_SEL_TYPE(type) (((type) == ADC_BIAS_SEL_MAIN_BANDGAP) || \
                                    ((type) == ADC_BIAS_SEL_AON_BANDGAP))

/** @defgroup  ADC_CHOP_MOD_TYPE
 *  @{
 */
#define IS_ADC_CHOP_MOD_TYPE(type) (((type) == ADC_CHOP_MOD_ALL_OFF) ||   \
                                    ((type) == ADC_CHOP_MOD_AZ_ON) ||     \
                                    ((type) == ADC_CHOP_MOD_AZ_PGA_ON) || \
                                    ((type) == ADC_CHOP_MOD_AZ_PGA_RPC_ON))

/** @defgroup  ADC_PGA_VCM_TYPE
 *  @{
 */
#define IS_ADC_PGA_VCM_TYPE(type) (((type) == ADC_PGA_VCM_1V) ||   \
                                   ((type) == ADC_PGA_VCM_1P2V) || \
                                   ((type) == ADC_PGA_VCM_1P4V) || \
                                   ((type) == ADC_PGA_VCM_1P6V))

/** @defgroup  ADC_TSEN_MOD_TYPE
 *  @{
 */
#define IS_ADC_TSEN_MOD_TYPE(type) (((type) == ADC_TSEN_MOD_INTERNAL_DIODE) || \
                                    ((type) == ADC_TSEN_MOD_EXTERNAL_DIODE))

/** @defgroup  ADC_VREF_TYPE
 *  @{
 */
#define IS_ADC_VREF_TYPE(type) (((type) == ADC_VREF_3P3V) || \
                                ((type) == ADC_VREF_2V))

/** @defgroup  ADC_SIG_INPUT_TYPE
 *  @{
 */
#define IS_ADC_SIG_INPUT_TYPE(type) (((type) == ADC_INPUT_SINGLE_END) || \
                                     ((type) == ADC_INPUT_DIFF))

/** @defgroup  ADC_DATA_WIDTH_TYPE
 *  @{
 */
#define IS_ADC_DATA_WIDTH_TYPE(type) (((type) == ADC_DATA_WIDTH_12) ||                  \
                                      ((type) == ADC_DATA_WIDTH_14_WITH_16_AVERAGE) ||  \
                                      ((type) == ADC_DATA_WIDTH_14_WITH_64_AVERAGE) ||  \
                                      ((type) == ADC_DATA_WIDTH_16_WITH_128_AVERAGE) || \
                                      ((type) == ADC_DATA_WIDTH_16_WITH_256_AVERAGE))

/** @defgroup  ADC_MICBOOST_DB_TYPE
 *  @{
 */
#define IS_ADC_MICBOOST_DB_TYPE(type) (((type) == ADC_MICBOOST_DB_16DB) || \
                                       ((type) == ADC_MICBOOST_DB_32DB))

/** @defgroup  ADC_PGA2_GAIN_TYPE
 *  @{
 */
#define IS_ADC_PGA2_GAIN_TYPE(type) (((type) == ADC_PGA2_GAIN_0DB) ||  \
                                     ((type) == ADC_PGA2_GAIN_6DB) ||  \
                                     ((type) == ADC_PGA2_GAIN_N6DB) || \
                                     ((type) == ADC_PGA2_GAIN_12DB))

/** @defgroup  ADC_MIC_MODE_TYPE
 *  @{
 */
#define IS_ADC_MIC_MODE_TYPE(type) (((type) == ADC_MIC_MODE_SINGLE) || \
                                    ((type) == ADC_MIC_MODE_DIFF))

/** @defgroup  ADC_FIFO_THRESHOLD_TYPE
 *  @{
 */
#define IS_ADC_FIFO_THRESHOLD_TYPE(type) (((type) == ADC_FIFO_THRESHOLD_1) || \
                                          ((type) == ADC_FIFO_THRESHOLD_4) || \
                                          ((type) == ADC_FIFO_THRESHOLD_8) || \
                                          ((type) == ADC_FIFO_THRESHOLD_16))

/** @defgroup  ADC_INT_TYPE
 *  @{
 */
#define IS_ADC_INT_TYPE(type) (((type) == ADC_INT_POS_SATURATION) || \
                               ((type) == ADC_INT_NEG_SATURATION) || \
                               ((type) == ADC_INT_FIFO_UNDERRUN) ||  \
                               ((type) == ADC_INT_FIFO_OVERRUN) ||   \
                               ((type) == ADC_INT_ADC_READY) ||      \
                               ((type) == ADC_INT_ALL))

/*@} end of group ADC_Public_Constants */

/** @defgroup  ADC_Public_Macros
 *  @{
 */

/*@} end of group ADC_Public_Macros */

/** @defgroup  ADC_Public_Functions
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
void GPADC_DMA_IRQHandler(void);
#endif
void ADC_Vbat_Enable(void);
void ADC_Vbat_Disable(void);
void ADC_Reset(void);
void ADC_Enable(void);
void ADC_Disable(void);
void ADC_Init(ADC_CFG_Type *cfg);
void ADC_Channel_Config(ADC_Chan_Type posCh, ADC_Chan_Type negCh, BL_Fun_Type contEn);
void ADC_Scan_Channel_Config(ADC_Chan_Type posChList[], ADC_Chan_Type negChList[], uint8_t scanLength, BL_Fun_Type contEn);
void ADC_Start(void);
void ADC_Stop(void);
void ADC_FIFO_Cfg(ADC_FIFO_Cfg_Type *fifoCfg);
uint8_t ADC_Get_FIFO_Count(void);
BL_Sts_Type ADC_FIFO_Is_Empty(void);
BL_Sts_Type ADC_FIFO_Is_Full(void);
void ADC_FIFO_Clear(void);
uint32_t ADC_Read_FIFO(void);
void ADC_Parse_Result(uint32_t *orgVal, uint32_t len, ADC_Result_Type *result);
void ADC_IntClr(ADC_INT_Type intType);
BL_Mask_Type ADC_IntGetMask(ADC_INT_Type intType);
BL_Sts_Type ADC_GetIntStatus(ADC_INT_Type intType);
void ADC_Int_Callback_Install(ADC_INT_Type intType, intCallback_Type *cbFun);
void ADC_IntMask(ADC_INT_Type intType, BL_Mask_Type intMask);
void ADC_SET_TSVBE_LOW(void);
void ADC_SET_TSVBE_HIGH(void);
void ADC_Tsen_Init(ADC_TSEN_MOD_Type tsenMod);
void ADC_Tsen_Enable(void);
void ADC_Tsen_Disable(void);
void ADC_PGA_Config(uint8_t pga_vcmi_enable, uint8_t pga_os_cal);
BL_Err_Type ADC_Mic_Init(ADC_MIC_Type *adc_mic_config);
void ADC_MIC_Bias_Disable(void);
void ADC_MIC_Bias_Enable(void);
BL_Err_Type ADC_Trim_TSEN(uint16_t *tsen_offset);
BL_Err_Type ADC_Gain_Trim(void);
uint32_t ADC_Cal_Reg_Coeff_Value(uint32_t raw_reg);
float TSEN_Get_Temp(uint32_t tsen_offset);

/*@} end of group ADC_Public_Functions */

/*@} end of group ADC */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_ADC_H__ */
