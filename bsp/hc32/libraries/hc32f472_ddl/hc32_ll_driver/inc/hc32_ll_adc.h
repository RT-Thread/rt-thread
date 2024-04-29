/**
 *******************************************************************************
 * @file  hc32_ll_adc.h
 * @brief This file contains all the functions prototypes of the ADC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Modify typo
                                    API fixed: ADC_DeInit()
   2023-12-15       CDT             Add declaration of API ADC_MxChCmd(), ADC_ConvDataAverageMxChCmd(), and add defgroup ADC_Mx_Channel
                                    Add declaration of API ADC_GetResolution()
                                    Add note for group ADC_PGA_VSS
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_ADC_H__
#define __HC32_LL_ADC_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_ADC
 * @{
 */

#if (LL_ADC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ADC_Global_Types ADC Global Types
 * @{
 */
/**
 * @brief Structure definition of analog watchdog(AWD) configuration.
 */
typedef struct {
    uint16_t u16WatchdogMode;           /*!< Specifies the ADC analog watchdog mode.
                                             This parameter can be a value of @ref ADC_AWD_Mode */
    uint16_t u16LowThreshold;           /*!< Specifies the ADC analog watchdog Low threshold value. */
    uint16_t u16HighThreshold;          /*!< Specifies the ADC analog watchdog High threshold value. */
} stc_adc_awd_config_t;

/**
 * @brief Structure definition of ADC initialization.
 */
typedef struct {
    uint16_t u16ScanMode;               /*!< Specifies the ADC scan convert mode.
                                             This parameter can be a value of @ref ADC_Scan_Mode */
    uint16_t u16Resolution;             /*!< Specifies the ADC resolution.
                                             This parameter can be a value of @ref ADC_Resolution */
    uint16_t u16DataAlign;              /*!< Specifies ADC data alignment.
                                             This parameter can be a value of @ref ADC_Data_Align */
} stc_adc_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ADC_Global_Macros ADC Global Macros
 * @{
 */

/**
 * @defgroup ADC_Sequence ADC Sequence
 * @{
 */
#define ADC_SEQ_A                       (0U)                /*!< ADC sequence A. */
#define ADC_SEQ_B                       (1U)                /*!< ADC sequence B. */
/**
 * @}
 */

/**
 * @defgroup ADC_Channel ADC Channel
 * @{
 */
/**
 * @note HC32F472JCTI/HC32F472JETI/HC32F472PCTI/HC32F472PETI: ADC1 can NOT use PB2, PB12, PB13, PB14
 *                                                            ADC2 can NOT use PB12, PB13, PB14, PB15
 *                                                            ADC3 can NOT use PB0, PB1, PC4, PC5, PB2
 */
#define ADC_CH0                         (0U)        /*!< Default input pin: PA0 for ADC1, ADC2 and ADC3. */
#define ADC_CH1                         (1U)        /*!< Default input pin: PA1 for ADC1, ADC2 and ADC3. */
#define ADC_CH2                         (2U)        /*!< Default input pin: PA2 for ADC1, ADC2 and ADC3. */
#define ADC_CH3                         (3U)        /*!< Default input pin: PA3 for ADC1, ADC2 and ADC3. */
#define ADC_CH4                         (4U)        /*!< Default input pin: PA4 for ADC1 and ADC2, PA8 for ADC3. */
#define ADC_CH5                         (5U)        /*!< Default input pin: PA5 for ADC1 and ADC2, PA9 for ADC3. */
#define ADC_CH6                         (6U)        /*!< Default input pin: PA6 for ADC1 and ADC2, PA10 for ADC3. */
#define ADC_CH7                         (7U)        /*!< Default input pin: PA7 for ADC1 and ADC2, PA11 for ADC3. */
#define ADC_CH8                         (8U)        /*!< Default input pin: PB0 for ADC1, ADC2 and ADC3. */
#define ADC_CH9                         (9U)        /*!< Default input pin: PB1 for ADC1, ADC2 and ADC3. */
#define ADC_CH10                        (10U)       /*!< Default input pin: PC0 for ADC1, ADC2 and ADC3. */
#define ADC_CH11                        (11U)       /*!< Default input pin: PC1 for ADC1, ADC2 and ADC3. */
#define ADC_CH12                        (12U)       /*!< Default input pin: PC2 for ADC1, ADC2 and ADC3. */
#define ADC_CH13                        (13U)       /*!< Default input pin: PC3 for ADC1, ADC2 and ADC3. */
#define ADC_CH14                        (14U)       /*!< Default input pin: PC4 for ADC1 and ADC2, PF4 for ADC3. */
#define ADC_CH15                        (15U)       /*!< Default input pin: PC5 for ADC1 and ADC2, PF5 for ADC3. */
#define ADC_CH16                        (16U)       /*!< Input pin: PB2 for ADC1, ADC2 and ADC3. */
#define ADC_CH17                        (17U)       /*!< Input pin: PB12 for ADC1 and ADC2, PA12 for ADC3. */
#define ADC_CH18                        (18U)       /*!< Input pin: PB13 for ADC1 and ADC2, PA15 for ADC3. */
#define ADC_CH19                        (19U)       /*!< Input pin: PB14 for ADC1 and ADC2, PB3 for ADC3. */
#define ADC_CH20                        (20U)       /*!< Input pin: PB15 for ADC1 and ADC2, PB4 for ADC3. */
#define ADC_CH21                        (21U)       /*!< Input analog source:
                                                         ADC1: Internal reference voltage(ADVREF).
                                                         ADC2: Internal reference voltage(ADVREF).
                                                         ADC3: PB5. */
#define ADC_CH22                        (22U)       /*!< Input analog source:
                                                         ADC1: CMP reference voltage(VREFINT).
                                                         ADC2: CMP reference voltage(VREFINT).
                                                         ADC3: Internal reference voltage(ADVREF). */
#define ADC_CH23                        (23U)       /*!< Input analog source:
                                                         ADC1: Divided voltage of AVCC(AVCCDIVMON).
                                                         ADC2: Divided voltage of AVCC(AVCCDIVMON).
                                                         ADC3: CMP reference voltage(VREFINT). */
#define ADC_CH24                        (24U)       /*!< Input analog source:
                                                         ADC1: NOT supported.
                                                         ADC2: NOT supported.
                                                         ADC3: Divider of AVCC(AVCCDIVMON). */
#define ADC1_CH_ADVREF                  ADC_CH21
#define ADC2_CH_ADVREF                  ADC_CH21
#define ADC3_CH_ADVREF                  ADC_CH22

#define ADC1_CH_VREFINT                 ADC_CH22
#define ADC2_CH_VREFINT                 ADC_CH22
#define ADC3_CH_VREFINT                 ADC_CH23

#define ADC1_CH_AVCCDIV                 ADC_CH23
#define ADC2_CH_AVCCDIV                 ADC_CH23
#define ADC3_CH_AVCCDIV                 ADC_CH24
/**
 * @}
 */

/**
 * @defgroup ADC_Mx_Channel ADC Channel
 * @{
 */
#define ADC_MX_CH0                      (1U << 0U)          /*!< ADC channel 0 position  */
#define ADC_MX_CH1                      (1U << 1U)          /*!< ADC channel 1 position  */
#define ADC_MX_CH2                      (1U << 2U)          /*!< ADC channel 2 position  */
#define ADC_MX_CH3                      (1U << 3U)          /*!< ADC channel 3 position  */
#define ADC_MX_CH4                      (1U << 4U)          /*!< ADC channel 4 position  */
#define ADC_MX_CH5                      (1U << 5U)          /*!< ADC channel 5 position  */
#define ADC_MX_CH6                      (1U << 6U)          /*!< ADC channel 6 position  */
#define ADC_MX_CH7                      (1U << 7U)          /*!< ADC channel 7 position  */
#define ADC_MX_CH8                      (1U << 8U)          /*!< ADC channel 8 position  */
#define ADC_MX_CH9                      (1U << 9U)          /*!< ADC channel 9 position  */
#define ADC_MX_CH10                     (1U << 10U)         /*!< ADC channel 10 position */
#define ADC_MX_CH11                     (1U << 11U)         /*!< ADC channel 11 position */
#define ADC_MX_CH12                     (1U << 12U)         /*!< ADC channel 12 position */
#define ADC_MX_CH13                     (1U << 13U)         /*!< ADC channel 13 position */
#define ADC_MX_CH14                     (1U << 14U)         /*!< ADC channel 14 position */
#define ADC_MX_CH15                     (1U << 15U)         /*!< ADC channel 15 position */
#define ADC_MX_CH16                     (1U << 16U)         /*!< ADC channel 16 position */
#define ADC_MX_CH17                     (1U << 17U)         /*!< ADC channel 17 position */
#define ADC_MX_CH18                     (1U << 18U)         /*!< ADC channel 18 position */
#define ADC_MX_CH19                     (1U << 19U)         /*!< ADC channel 19 position */
#define ADC_MX_CH20                     (1U << 20U)         /*!< ADC channel 20 position */
#define ADC_MX_CH21                     (1U << 21U)         /*!< ADC channel 21 position */
#define ADC_MX_CH22                     (1U << 22U)         /*!< ADC channel 22 position */
#define ADC_MX_CH23                     (1U << 23U)         /*!< ADC channel 23 position */
#define ADC_MX_CH24                     (1U << 24U)         /*!< ADC channel 24 position */

#define ADC1_MX_CH_ALL                  (0xFFFFFFUL)        /*!< ADC1 Channel mask position */
#define ADC2_MX_CH_ALL                  (0xFFFFFFUL)        /*!< ADC2 Channel mask position */
#define ADC3_MX_CH_ALL                  (0x1FFFFFFUL)       /*!< ADC3 Channel mask position */
/**
 * @}
 */

/**
 * @defgroup ADC_Scan_Mode ADC Scan Convert Mode
 * @{
 */
#define ADC_MD_SEQA_SINGLESHOT              (0x0U)                      /*!< Sequence A single shot. Sequence B is disabled. */
#define ADC_MD_SEQA_CONT                    (0x1U << ADC_CR0_MS_POS)    /*!< Sequence A continuous. Sequence B is disabled. */
#define ADC_MD_SEQA_SEQB_SINGLESHOT         (0x2U << ADC_CR0_MS_POS)    /*!< Sequence A and B both single shot. */
#define ADC_MD_SEQA_CONT_SEQB_SINGLESHOT    (0x3U << ADC_CR0_MS_POS)    /*!< Sequence A continuous and sequence B single shot. */
/**
 * @}
 */

/**
 * @defgroup ADC_Resolution ADC Resolution
 * @{
 */
#define ADC_RESOLUTION_12BIT            (0x0U)              /*!< Resolution is 12 bit. */
#define ADC_RESOLUTION_10BIT            (ADC_CR0_ACCSEL_0)  /*!< Resolution is 10 bit. */
#define ADC_RESOLUTION_8BIT             (ADC_CR0_ACCSEL_1)  /*!< Resolution is 8 bit. */
/**
 * @}
 */

/**
 * @defgroup ADC_Data_Align ADC Data Align
 * @{
 */
#define ADC_DATAALIGN_RIGHT             (0x0U)              /*!< Right alignment of converted data. */
#define ADC_DATAALIGN_LEFT              (ADC_CR0_DFMT)      /*!< Left alignment of converted data. */
/**
 * @}
 */

/**
 * @defgroup ADC_Average_Count ADC Average Count
 * @{
 */
#define ADC_AVG_CNT2                    (0x0U)                      /*!< 2 consecutive average conversions. */
#define ADC_AVG_CNT4                    (0x1U << ADC_CR0_AVCNT_POS) /*!< 4 consecutive average conversions. */
#define ADC_AVG_CNT8                    (0x2U << ADC_CR0_AVCNT_POS) /*!< 8 consecutive average conversions. */
#define ADC_AVG_CNT16                   (0x3U << ADC_CR0_AVCNT_POS) /*!< 16 consecutive average conversions. */
#define ADC_AVG_CNT32                   (0x4U << ADC_CR0_AVCNT_POS) /*!< 32 consecutive average conversions. */
#define ADC_AVG_CNT64                   (0x5U << ADC_CR0_AVCNT_POS) /*!< 64 consecutive average conversions. */
#define ADC_AVG_CNT128                  (0x6U << ADC_CR0_AVCNT_POS) /*!< 128 consecutive average conversions. */
#define ADC_AVG_CNT256                  (0x7U << ADC_CR0_AVCNT_POS) /*!< 256 consecutive average conversions. */
/**
 * @}
 */

/**
 * @defgroup ADC_SeqA_Resume_Mode ADC Sequence A Resume Mode
 * @brief After interrupted by sequence B, sequence A continues to scan from the interrupt channel or the first channel.
 * @{
 */
#define ADC_SEQA_RESUME_SCAN_CONT       (0U)                /*!< Scanning will continue from the interrupted channel. */
#define ADC_SEQA_RESUME_SCAN_RESTART    (ADC_CR1_RSCHSEL)   /*!< Scanning will start from the first channel. */
/**
 * @}
 */

/**
 * @defgroup ADC_Hard_Trigger_Sel ADC Hard Trigger Selection
 * @{
 */
#define ADC_HARDTRIG_ADTRG_PIN          (0x0U)                      /*!< Selects the following edge of pin ADTRG as the trigger of ADC sequence. */
#define ADC_HARDTRIG_EVT0               (ADC_TRGSR_TRGSELA_0)       /*!< Selects an internal event as the trigger of ADC sequence.
                                                                         This event is specified by register ADCx_TRGSEL0(x=(null), 1, 2, 3). */
#define ADC_HARDTRIG_EVT1               (ADC_TRGSR_TRGSELA_1)       /*!< Selects an internal event as the trigger of ADC sequence.
                                                                         This event is specified by register ADCx_TRGSEL1(x=(null), 1, 2, 3). */
#define ADC_HARDTRIG_EVT0_EVT1          (ADC_TRGSR_TRGSELA)         /*!< Selects two internal events as the trigger of ADC sequence.
                                                                         The two events are specified by register ADCx_TRGSEL0 and register ADCx_TRGSEL1. */
/**
 * @}
 */

/**
 * @defgroup ADC_Int_Type ADC Interrupt Type
 * @{
 */
#define ADC_INT_EOCA                    (ADC_ICR_EOCAIEN)           /*!< Interrupt of the end of conversion of sequence A. */
#define ADC_INT_EOCB                    (ADC_ICR_EOCBIEN)           /*!< Interrupt of the end of conversion of sequence B. */
#define ADC_INT_ALL                     (ADC_INT_EOCA | ADC_INT_EOCB)
/**
 * @}
 */

/**
 * @defgroup ADC_Status_Flag ADC Status Flag
 * @{
 */
#define ADC_FLAG_EOCA                   (ADC_ISR_EOCAF)             /*!< Status flag of the end of conversion of sequence A. */
#define ADC_FLAG_EOCB                   (ADC_ISR_EOCBF)             /*!< Status flag of the end of conversion of sequence B. */
#define ADC_FLAG_NESTED                 (ADC_ISR_SASTPDF)           /*!< Status flag of sequence A was interrupted by sequence B. */
#define ADC_FLAG_ALL                    (ADC_FLAG_EOCA | ADC_FLAG_EOCB | ADC_FLAG_NESTED)
/**
 * @}
 */

/**
 * @defgroup ADC_Sync_Unit ADC Synchronous Unit
 * @{
 */
#define ADC_SYNC_ADC1_ADC2              (0U)                                /*!< ADC1 and ADC2 work synchronously. */
#define ADC_SYNC_ADC1_ADC2_ADC3         (0x1U << ADC_SYNCCR_SYNCMD_POS)     /*!< ADC1, ADC2 and ADC3 work synchronously. */
/**
 * @}
 */

/**
 * @defgroup ADC_Sync_Mode ADC Synchronous Mode
 * @{
 */
#define ADC_SYNC_SINGLE_DELAY_TRIG      (0U)                            /*!< Single shot delayed trigger mode.
                                                                             When the trigger condition occurs, ADC1 starts first, then ADC2, last ADC3(if has).
                                                                             All ADCs scan once. */
#define ADC_SYNC_SINGLE_PARALLEL_TRIG   (0x2U << ADC_SYNCCR_SYNCMD_POS) /*!< Single shot parallel trigger mode.
                                                                             When the trigger condition occurs, all ADCs start at the same time.
                                                                             All ADCs scan once. */
#define ADC_SYNC_CYCLIC_DELAY_TRIG      (0x4U << ADC_SYNCCR_SYNCMD_POS) /*!< Cyclic delayed trigger mode.
                                                                             When the trigger condition occurs, ADC1 starts first, then ADC2, last ADC3(if has).
                                                                             All ADCs scan cyclicly(keep scanning till you stop them). */
#define ADC_SYNC_CYCLIC_PARALLEL_TRIG   (0x6U << ADC_SYNCCR_SYNCMD_POS) /*!< Single shot parallel trigger mode.
                                                                             When the trigger condition occurs, all ADCs start at the same time.
                                                                             All ADCs scan cyclicly(keep scanning till you stop them). */
/**
 * @}
 */

/**
 * @defgroup ADC_AWD_Unit ADC Analog Watchdog Unit
 * @{
 */
#define ADC_AWD0                        (0U)    /*!< ADC analog watchdog 0. */
#define ADC_AWD1                        (1U)    /*!< ADC analog watchdog 1. */
/**
 * @}
 */

/**
 * @defgroup ADC_AWD_Int_Type ADC AWD Interrupt Type
 * @{
 */
#define ADC_AWD_INT_AWD0                (ADC_AWDCR_AWD0IEN)     /*!< Interrupt of AWD0. */
#define ADC_AWD_INT_AWD1                (ADC_AWDCR_AWD1IEN)     /*!< Interrupt of AWD1. */
#define ADC_AWD_INT_ALL                 (ADC_AWD_INT_AWD0 | ADC_AWD_INT_AWD1)
/**
 * @}
 */

/**
 * @defgroup ADC_AWD_Mode ADC Analog Watchdog Mode
 * @{
 */
#define ADC_AWD_MD_CMP_OUT              (0x0U)  /*!< ADCValue > HighThreshold or ADCValue < LowThreshold */
#define ADC_AWD_MD_CMP_IN               (0x1U)  /*!< LowThreshold < ADCValue < HighThreshold */
/**
 * @}
 */

/**
 * @defgroup ADC_AWD_Comb_Mode ADC AWD(Analog Watchdog) Combination Mode
 * @note If combination mode is valid(ADC_AWD_COMB_OR/ADC_AWD_COMB_AND/ADC_AWD_COMB_XOR) and
 *       the Channels selected by the AWD0 and AWD1 are deferent, make sure that the channel
 *       of AWD1 is converted after the channel conversion of AWD0 ends.
 * @{
 */
#define ADC_AWD_COMB_INVD               (0U)                /*!< Combination mode is invalid. */
#define ADC_AWD_COMB_OR                 (ADC_AWDCR_AWDCM_0) /*!< The status of AWD0 is set or the status of AWD1 is set, the status of combination mode is set. */
#define ADC_AWD_COMB_AND                (ADC_AWDCR_AWDCM_1) /*!< The status of AWD0 is set and the status of AWD1 is set, the status of combination mode is set. */
#define ADC_AWD_COMB_XOR                (ADC_AWDCR_AWDCM)   /*!< Only one of the status of AWD0 and AWD1 is set, the status of combination mode is set. */
/**
 * @}
 */

/**
 * @defgroup ADC_AWD_Status_Flag ADC AWD Status Flag
 * @{
 */
#define ADC_AWD_FLAG_AWD0               (ADC_AWDSR_AWD0F)   /*!< Flag of AWD0. */
#define ADC_AWD_FLAG_AWD1               (ADC_AWDSR_AWD1F)   /*!< Flag of AWD1. */
#define ADC_AWD_FLAG_COMB               (ADC_AWDSR_AWDCMF)  /*!< Flag of combination of mode. */
#define ADC_AWD_FLAG_ALL                (ADC_AWD_FLAG_AWD0 | ADC_AWD_FLAG_AWD1 | ADC_AWD_FLAG_COMB)
/**
 * @}
 */

/**
 * @defgroup ADC_PGA_Unit ADC PGA Unit
 * @{
 */
#define ADC_PGA1                        (0U)    /*!< PGA1, belongs to ADC1. Input pin is ADC12_IN7(PA7). */
#define ADC_PGA2                        (1U)    /*!< PGA2, belongs to ADC2. Input pin is ADC123_IN8(PB0). */
/**
 * @}
 */

/**
 * @defgroup ADC_PGA_Gain ADC PGA Gain Factor
 * @{
 */
#define ADC_PGA_GAIN_2                  (0x0U)  /*!< PGA gain factor is 2. */
#define ADC_PGA_GAIN_2P133              (0x1U)  /*!< PGA gain factor is 2.133. */
#define ADC_PGA_GAIN_2P286              (0x2U)  /*!< PGA gain factor is 2.286. */
#define ADC_PGA_GAIN_2P667              (0x3U)  /*!< PGA gain factor is 2.667. */
#define ADC_PGA_GAIN_2P909              (0x4U)  /*!< PGA gain factor is 2.909. */
#define ADC_PGA_GAIN_3P2                (0x5U)  /*!< PGA gain factor is 3.2. */
#define ADC_PGA_GAIN_3P556              (0x6U)  /*!< PGA gain factor is 2.556. */
#define ADC_PGA_GAIN_4                  (0x7U)  /*!< PGA gain factor is 4. */
#define ADC_PGA_GAIN_4P571              (0x8U)  /*!< PGA gain factor is 4.571. */
#define ADC_PGA_GAIN_5P333              (0x9U)  /*!< PGA gain factor is 5.333. */
#define ADC_PGA_GAIN_6P4                (0xAU)  /*!< PGA gain factor is 6.4. */
#define ADC_PGA_GAIN_8                  (0xBU)  /*!< PGA gain factor is 8. */
#define ADC_PGA_GAIN_10P667             (0xCU)  /*!< PGA gain factor is 10.667. */
#define ADC_PGA_GAIN_16                 (0xDU)  /*!< PGA gain factor is 16. */
#define ADC_PGA_GAIN_32                 (0xEU)  /*!< PGA gain factor is 32. */
/**
 * @}
 */

/**
 * @defgroup ADC_PGA_VSS ADC PGA VSS
 * @note HC32F472JCTI/HC32F472JETI/HC32F472PCTI/HC32F472PETI do NOT have pin PGAx_VSS
 * @{
 */
#define ADC_PGA_VSS_PGAVSS              (0U)    /*!< Use pin PGAx_VSS as the reference GND of PGAx. */
#define ADC_PGA_VSS_AVSS                (1U)    /*!< Use AVSS as the reference GND of PGAx. */
/**
 * @}
 */

/**
 * @defgroup ADC_Remap_Pin ADC Remap Pin
 * @{
 */
#define ADC12_PIN_PA0                   (0U)    /*!< ADC123_IN0(PA0): default channel is ADC_CH0 of ADC1 and ADC2 */
#define ADC12_PIN_PA1                   (1U)    /*!< ADC123_IN1(PA1): default channel is ADC_CH1 of ADC1 and ADC2 */
#define ADC12_PIN_PA2                   (2U)    /*!< ADC123_IN2(PA2): default channel is ADC_CH2 of ADC1 and ADC2 */
#define ADC12_PIN_PA3                   (3U)    /*!< ADC123_IN3(PA3): default channel is ADC_CH3 of ADC1 and ADC2 */
#define ADC12_PIN_PA4                   (4U)    /*!< ADC12_IN4(PA4): default channel is ADC_CH4 of ADC1 and ADC2 */
#define ADC12_PIN_PA5                   (5U)    /*!< ADC12_IN5(PA5): default channel is ADC_CH5 of ADC1 and ADC2 */
#define ADC12_PIN_PA6                   (6U)    /*!< ADC12_IN6(PA6): default channel is ADC_CH6 of ADC1 and ADC2 */
#define ADC12_PIN_PA7                   (7U)    /*!< ADC12_IN7(PA7): default channel is ADC_CH7 of ADC1 and ADC2 */
#define ADC12_PIN_PB0                   (8U)    /*!< ADC123_IN8(PB0): default channel is ADC_CH8 of ADC1 and ADC2 */
#define ADC12_PIN_PB1                   (9U)    /*!< ADC123_IN9(PB1): default channel is ADC_CH9 of ADC1 and ADC2 */
#define ADC12_PIN_PC0                   (10U)   /*!< ADC123_IN10(PC0): default channel is ADC_CH10 of ADC1 and ADC2 */
#define ADC12_PIN_PC1                   (11U)   /*!< ADC123_IN11(PC1): default channel is ADC_CH11 of ADC1 and ADC2 */
#define ADC12_PIN_PC2                   (12U)   /*!< ADC123_IN12(PC2): default channel is ADC_CH12 of ADC1 and ADC2 */
#define ADC12_PIN_PC3                   (13U)   /*!< ADC123_IN13(PC3): default channel is ADC_CH13 of ADC1 and ADC2 */
#define ADC12_PIN_PC4                   (14U)   /*!< ADC12_IN14(PC4): default channel is ADC_CH14 of ADC1 and ADC2 */
#define ADC12_PIN_PC5                   (15U)   /*!< ADC12_IN15(PC5): default channel is ADC_CH15 of ADC1 and ADC2 */

#define ADC3_PIN_PA0                    (0U)    /*!< ADC123_IN0(PA0): default channel is ADC_CH0 of ADC3 */
#define ADC3_PIN_PA1                    (1U)    /*!< ADC123_IN1(PA1): default channel is ADC_CH1 of ADC3 */
#define ADC3_PIN_PA2                    (2U)    /*!< ADC123_IN2(PA2): default channel is ADC_CH2 of ADC3 */
#define ADC3_PIN_PA3                    (3U)    /*!< ADC123_IN3(PA3): default channel is ADC_CH3 of ADC3 */
#define ADC3_PIN_PA8                    (4U)    /*!< ADC3_IN4(PA8): default channel is ADC_CH4 of ADC3 */
#define ADC3_PIN_PA9                    (5U)    /*!< ADC3_IN5(PA9): default channel is ADC_CH5 of ADC3 */
#define ADC3_PIN_PA10                   (6U)    /*!< ADC3_IN6(PA10): default channel is ADC_CH6 of ADC3 */
#define ADC3_PIN_PA11                   (7U)    /*!< ADC3_IN7(PA11): default channel is ADC_CH7 of ADC3 */
#define ADC3_PIN_PB0                    (8U)    /*!< ADC123_IN8(PB0): default channel is ADC_CH8 of ADC3 */
#define ADC3_PIN_PB1                    (9U)    /*!< ADC123_IN9(PB1): default channel is ADC_CH9 of ADC3 */
#define ADC3_PIN_PC0                    (10U)   /*!< ADC123_IN10(PC0): default channel is ADC_CH10 of ADC3 */
#define ADC3_PIN_PC1                    (11U)   /*!< ADC123_IN11(PC1): default channel is ADC_CH11 of ADC3 */
#define ADC3_PIN_PC2                    (12U)   /*!< ADC123_IN12(PC2): default channel is ADC_CH12 of ADC3 */
#define ADC3_PIN_PC3                    (13U)   /*!< ADC123_IN13(PC3): default channel is ADC_CH13 of ADC3 */
#define ADC3_PIN_PF4                    (14U)   /*!< ADC3_IN14(PF4): default channel is ADC_CH14 of ADC3 */
#define ADC3_PIN_PF5                    (15U)   /*!< ADC3_IN15(PF5): default channel is ADC_CH15 of ADC3 */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup ADC_Global_Functions
 * @{
 */
/*******************************************************************************
  Basic features
 ******************************************************************************/
int32_t ADC_Init(CM_ADC_TypeDef *ADCx, const stc_adc_init_t *pstcAdcInit);
int32_t ADC_DeInit(CM_ADC_TypeDef *ADCx);
int32_t ADC_StructInit(stc_adc_init_t *pstcAdcInit);
void ADC_ChCmd(CM_ADC_TypeDef *ADCx, uint8_t u8Seq, uint8_t u8Ch, en_functional_state_t enNewState);
void ADC_MxChCmd(CM_ADC_TypeDef *ADCx, uint8_t u8Seq, uint32_t u32MxCh, en_functional_state_t enNewState);
void ADC_SetSampleTime(CM_ADC_TypeDef *ADCx, uint8_t u8Ch, uint8_t u8SampleTime);

/* Conversion data average calculation function. */
void ADC_ConvDataAverageConfig(CM_ADC_TypeDef *ADCx, uint16_t u16AverageCount);
void ADC_ConvDataAverageChCmd(CM_ADC_TypeDef *ADCx, uint8_t u8Ch, en_functional_state_t enNewState);
void ADC_ConvDataAverageMxChCmd(CM_ADC_TypeDef *ADCx, uint32_t u32MxCh, en_functional_state_t enNewState);

void ADC_TriggerConfig(CM_ADC_TypeDef *ADCx, uint8_t u8Seq, uint16_t u16TriggerSel);
void ADC_TriggerCmd(CM_ADC_TypeDef *ADCx, uint8_t u8Seq, en_functional_state_t enNewState);
void ADC_IntCmd(CM_ADC_TypeDef *ADCx, uint8_t u8IntType, en_functional_state_t enNewState);
int32_t ADC_Start(CM_ADC_TypeDef *ADCx);
void ADC_Stop(CM_ADC_TypeDef *ADCx);
uint16_t ADC_GetValue(const CM_ADC_TypeDef *ADCx, uint8_t u8Ch);
uint16_t ADC_GetResolution(const CM_ADC_TypeDef *ADCx);
en_flag_status_t ADC_GetStatus(const CM_ADC_TypeDef *ADCx, uint8_t u8Flag);
void ADC_ClearStatus(CM_ADC_TypeDef *ADCx, uint8_t u8Flag);
/*******************************************************************************
  Advanced features
 ******************************************************************************/
/* Channel remap. */
void ADC_ChRemap(CM_ADC_TypeDef *ADCx, uint8_t u8Ch, uint8_t u8AdcPin);
uint8_t ADC_GetChPin(const CM_ADC_TypeDef *ADCx, uint8_t u8Ch);
void ADC_ResetChMapping(CM_ADC_TypeDef *ADCx);

/* Sync mode. */
void ADC_SyncModeConfig(uint16_t u16SyncUnit, uint16_t u16SyncMode, uint8_t u8TriggerDelay);
void ADC_SyncModeCmd(en_functional_state_t enNewState);

/* Analog watchdog */
int32_t ADC_AWD_Config(CM_ADC_TypeDef *ADCx, uint8_t u8AwdUnit, uint8_t u8Ch, const stc_adc_awd_config_t *pstcAwd);
/* Combination mode. */
void ADC_AWD_SetCombMode(CM_ADC_TypeDef *ADCx, uint16_t u16CombMode);
void ADC_AWD_SetMode(CM_ADC_TypeDef *ADCx, uint8_t u8AwdUnit, uint16_t u16WatchdogMode);
uint16_t ADC_AWD_GetMode(CM_ADC_TypeDef *ADCx, uint8_t u8AwdUnit);
void ADC_AWD_SetThreshold(CM_ADC_TypeDef *ADCx, uint8_t u8AwdUnit, uint16_t u16LowThreshold, uint16_t u16HighThreshold);
void ADC_AWD_SelectCh(CM_ADC_TypeDef *ADCx, uint8_t u8AwdUnit, uint8_t u8Ch);
void ADC_AWD_Cmd(CM_ADC_TypeDef *ADCx, uint8_t u8AwdUnit, en_functional_state_t enNewState);
void ADC_AWD_IntCmd(CM_ADC_TypeDef *ADCx, uint16_t u16IntType, en_functional_state_t enNewState);
en_flag_status_t ADC_AWD_GetStatus(const CM_ADC_TypeDef *ADCx, uint32_t u32Flag);
void ADC_AWD_ClearStatus(CM_ADC_TypeDef *ADCx, uint32_t u32Flag);

/* PGA */
void ADC_PGA_Config(CM_ADC_TypeDef *ADCx, uint8_t u8PgaUnit, uint8_t u8Gain, uint8_t u8PgaVss);
void ADC_PGA_Cmd(CM_ADC_TypeDef *ADCx, uint8_t u8PgaUnit, en_functional_state_t enNewState);

void ADC_DataRegAutoClearCmd(CM_ADC_TypeDef *ADCx, en_functional_state_t enNewState);
void ADC_SetSeqAResumeMode(CM_ADC_TypeDef *ADCx, uint16_t u16SeqAResumeMode);
/**
 * @}
 */

#endif /* LL_ADC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_ADC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
