/**
 *******************************************************************************
 * @file  hc32f4a0_adc.h
 * @brief This file contains all the functions prototypes of the ADC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Wuze            First version
   2020-12-15       Wuze            ADC_ComTriggerCmd() refine.
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_ADC_H__
#define __HC32F4A0_ADC_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_ADC
 * @{
 */

#if (DDL_ADC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ADC_Global_Types ADC Global Types
 * @{
 */

/**
 * @brief Structure definition of ADC initialization.
 */
typedef struct
{
    uint16_t u16ScanMode;       /*!< Configures the scan convert mode of ADC.
                                     This parameter can be a value of @ref ADC_Scan_Convert_Mode */
    uint16_t u16Resolution;     /*!< Configures the ADC resolution.
                                     This parameter can be a value of @ref ADC_Resolution */
    uint16_t u16AutoClrCmd;     /*!< Configures whether the ADC data register is
                                     automatically cleared after the data is read.
                                     This parameter can be a value of @ref ADC_Data_Auto_Clear_Cmd */
    uint16_t u16DataAlign;      /*!< Specifies ADC data alignment to right or to left.
                                     This parameter can be a value of @ref ADC_Data_Alignment */
    uint16_t u16SAResumePos;    /*!< Specifies the resume channel position of sequence A.
                                     Sequence A can be interrupted by sequence B. After the
                                     the ending of sequence B, sequence A resumes from the
                                     specified channel position.
                                     This parameter can be a value of @ref ADC_Sequence_A_Resume_Channel_Position */
} stc_adc_init_t;

/**
 * @brief Structure definition of ADC trigger source configuration.
 */
typedef struct
{
    uint16_t u16TrigSrc;        /*!< Specifies the trigger source type for the specified sequence.
                                     This parameter can be a value of @ref ADC_Trigger_Source_Type */
    en_event_src_t enEvent0;    /*!< An @ref en_event_src_t enumeration value. */
    en_event_src_t enEvent1;    /*!< An @ref en_event_src_t enumeration value. */
} stc_adc_trig_cfg_t;

/**
 * @brief Structure definition of AWD(analog watchdog) configuration.
 */
typedef struct
{
    uint8_t u8ChNum;            /*!< The number of the ADC channel which to be configured as an AWD channel.
                                     This parameter can be a value of range [ADC_CH_NUM_0, ADC_CH_NUM_15] of @ref ADC_Channel_Number */
    uint16_t u16CmpMode;        /*!< The comparison mode of AWD.
                                     This parameter can be a value of @ref ADC_AWD_Comparison_Mode */
    uint16_t u16LowerLimit;     /*!< Threshold lower limit value(to register ADC_AWDxDR0). */
    uint16_t u16UpperLimit;     /*!< Threshold upper limit value(to register ADC_AWDxDR1). */
} stc_adc_awd_cfg_t;

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
#define ADC_SEQ_A                       (0U)
#define ADC_SEQ_B                       (1U)
/**
 * @}
 */

/**
 * @defgroup ADC_AWD_Unit ADC Analog Watchdog Unit
 * @{
 */
#define ADC_AWD_0                       (0U)
#define ADC_AWD_1                       (1U)
/**
 * @}
 */

/**
 * @defgroup ADC_Scan_Convert_Mode ADC Scan Convert Mode
 * @{
 */
#define ADC_MODE_SA_SSHOT               (0x0U)              /*!< Sequence A single shot. */
#define ADC_MODE_SA_CONT                (ADC_CR0_MS_0)      /*!< Sequence A continuous. */
#define ADC_MODE_SA_SB_SSHOT            (ADC_CR0_MS_1)      /*!< Sequence A and B both single shot. */
#define ADC_MODE_SA_CONT_SB_SSHOT       (ADC_CR0_MS_1 | \
                                         ADC_CR0_MS_0)      /*!< Sequence A continuous and sequence B single shot. */
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
 * @defgroup ADC_Data_Auto_Clear_Cmd ADC Data Auto Clear Cmd
 * @{
 */
#define ADC_AUTO_CLR_DISABLE            (0x0U)
#define ADC_AUTO_CLR_ENABLE             (ADC_CR0_CLREN)     /*!< ADC data register is automatically cleared after the data is read. */
/**
 * @}
 */

/**
 * @defgroup ADC_Data_Alignment ADC Data Alignment
 * @{
 */
#define ADC_DATA_ALIGN_RIGHT            (0x0U)
#define ADC_DATA_ALIGN_LEFT             (ADC_CR0_DFMT)
/**
 * @}
 */

/**
 * @defgroup ADC_Average_Count ADC Average Count
 * @{
 */
#define ADC_AVG_CNT_2                   (0x0U)
#define ADC_AVG_CNT_4                   (ADC_CR0_AVCNT_0)
#define ADC_AVG_CNT_8                   (ADC_CR0_AVCNT_1)
#define ADC_AVG_CNT_16                  (ADC_CR0_AVCNT_1 | ADC_CR0_AVCNT_0)
#define ADC_AVG_CNT_32                  (ADC_CR0_AVCNT_2)
#define ADC_AVG_CNT_64                  (ADC_CR0_AVCNT_2 | ADC_CR0_AVCNT_0)
#define ADC_AVG_CNT_128                 (ADC_CR0_AVCNT_2 | ADC_CR0_AVCNT_1)
#define ADC_AVG_CNT_256                 (ADC_CR0_AVCNT_2 | ADC_CR0_AVCNT_1 | ADC_CR0_AVCNT_0)
/**
 * @}
 */

/**
 * @defgroup ADC_Sequence_A_Resume_Channel_Position ADC Sequence A Resume Channel Position
 * @{
 */
#define ADC_SA_RESUME_POS_INT_CH        (0x0U)                      /*!< Resumes from the interrupt channel of the sequence. */
#define ADC_SA_RESUME_POS_FIRST_CH      (ADC_CR1_RSCHSEL)           /*!< Resumes from the first channel of the sequence. */
/**
 * @}
 */

/**
 * @defgroup ADC_Trigger_Source_Type ADC Trigger Source Type
 * @{
 */
#define ADC_TRIG_SRC_ADTRG              (0x0U)                      /*!< The trigger source is the falling edge(the low level of the should \
                                                                         hold at least 1.5*PCLK cycle) of external pin ADTRGx(x=1, 2, 3). */
#define ADC_TRIG_SRC_EVENT0             (ADC_TRGSR_TRGSELA_0)       /*!< The trigger source is a internal event from other peripheral. \
                                                                         Only one event can be configured to trigger ADC. */
#define ADC_TRIG_SRC_EVENT1             (ADC_TRGSR_TRGSELA_1)       /*!< The trigger source is a internal event from other peripheral. \
                                                                         Only one event can be configured to trigger ADC. */
#define ADC_TRIG_SRC_EVENT0_EVENT1      (ADC_TRGSR_TRGSELA_0 | \
                                         ADC_TRGSR_TRGSELA_1)       /*!< The trigger source are two internal events from other peripheral(s). \
                                                                         Two events can be configured to trigger ADC and one of which can trigger the ADC. */
/**
 * @}
 */

/**
 * @defgroup ADC_Channel_Number ADC Channel Number
 * @{
 */
#define ADC_CH_NUM_0                (0U)
#define ADC_CH_NUM_1                (1U)
#define ADC_CH_NUM_2                (2U)
#define ADC_CH_NUM_3                (3U)
#define ADC_CH_NUM_4                (4U)
#define ADC_CH_NUM_5                (5U)
#define ADC_CH_NUM_6                (6U)
#define ADC_CH_NUM_7                (7U)
#define ADC_CH_NUM_8                (8U)
#define ADC_CH_NUM_9                (9U)
#define ADC_CH_NUM_10               (10U)
#define ADC_CH_NUM_11               (11U)
#define ADC_CH_NUM_12               (12U)
#define ADC_CH_NUM_13               (13U)
#define ADC_CH_NUM_14               (14U)
#define ADC_CH_NUM_15               (15U)
#define ADC_CH_NUM_16               (16U)
#define ADC_CH_NUM_17               (17U)
#define ADC_CH_NUM_18               (18U)
#define ADC_CH_NUM_19               (19U)
/**
 * @}
 */

/**
 * @defgroup ADC_Channel ADC Channel
 * @{
 */
#define ADC_CH0                     (0x1UL << ADC_CH_NUM_0)
#define ADC_CH1                     (0x1UL << ADC_CH_NUM_1)
#define ADC_CH2                     (0x1UL << ADC_CH_NUM_2)
#define ADC_CH3                     (0x1UL << ADC_CH_NUM_3)
#define ADC_CH4                     (0x1UL << ADC_CH_NUM_4)
#define ADC_CH5                     (0x1UL << ADC_CH_NUM_5)
#define ADC_CH6                     (0x1UL << ADC_CH_NUM_6)
#define ADC_CH7                     (0x1UL << ADC_CH_NUM_7)
#define ADC_CH8                     (0x1UL << ADC_CH_NUM_8)
#define ADC_CH9                     (0x1UL << ADC_CH_NUM_9)
#define ADC_CH10                    (0x1UL << ADC_CH_NUM_10)
#define ADC_CH11                    (0x1UL << ADC_CH_NUM_11)
#define ADC_CH12                    (0x1UL << ADC_CH_NUM_12)
#define ADC_CH13                    (0x1UL << ADC_CH_NUM_13)
#define ADC_CH14                    (0x1UL << ADC_CH_NUM_14)
#define ADC_CH15                    (0x1UL << ADC_CH_NUM_15)
#define ADC_CH16                    (0x1UL << ADC_CH_NUM_16)
#define ADC_CH17                    (0x1UL << ADC_CH_NUM_17)
#define ADC_CH18                    (0x1UL << ADC_CH_NUM_18)
#define ADC_CH19                    (0x1UL << ADC_CH_NUM_19)
#define ADC_EXT_CH                  (ADC_CH15)
/**
 * @}
 */

/**
 * @defgroup ADC_Pin_Number ADC Pin Number
 * @{
 */
#define ADC123_IN0                  (0U)                        /*!< PA0 */
#define ADC123_IN1                  (1U)                        /*!< PA1 */
#define ADC123_IN2                  (2U)                        /*!< PA2 */
#define ADC123_IN3                  (3U)                        /*!< PA3 */
#define ADC12_IN4                   (4U)                        /*!< PA4 */
#define ADC12_IN5                   (5U)                        /*!< PA5 */
#define ADC12_IN6                   (6U)                        /*!< PA6 */
#define ADC12_IN7                   (7U)                        /*!< PA7 */
#define ADC12_IN8                   (8U)                        /*!< PB0 */
#define ADC12_IN9                   (9U)                        /*!< PB1 */
#define ADC123_IN10                 (10U)                       /*!< PC0 */
#define ADC123_IN11                 (11U)                       /*!< PC1 */
#define ADC123_IN12                 (12U)                       /*!< PC2 */
#define ADC123_IN13                 (13U)                       /*!< PC3 */
#define ADC12_IN14                  (14U)                       /*!< PC4 */
#define ADC12_IN15                  (15U)                       /*!< PC5 */

#define ADC3_IN4                    (4U)                        /*!< PF6 */
#define ADC3_IN5                    (5U)                        /*!< PF7 */
#define ADC3_IN6                    (6U)                        /*!< PF8 */
#define ADC3_IN7                    (7U)                        /*!< PF9 */
#define ADC3_IN8                    (8U)                        /*!< PF10 */
#define ADC3_IN9                    (9U)                        /*!< PF3 */
#define ADC3_IN14                   (14U)                       /*!< PF4 */
#define ADC3_IN15                   (15U)                       /*!< PF5 */
#define ADC3_IN16                   (16U)                       /*!< PH2 */
#define ADC3_IN17                   (17U)                       /*!< PH3 */
#define ADC3_IN18                   (18U)                       /*!< PH4 */
#define ADC3_IN19                   (19U)                       /*!< PH5 */
/**
 * @}
 */

/**
 * @defgroup ADC_All_Channels_Mask ADC All Channels Mask
 * @{
 */
#define ADC1_CH_ALL                 (0xFFFFUL)
#define ADC2_CH_ALL                 (0xFFFFUL)
#define ADC3_CH_ALL                 (0xFFFFFUL)
#define ADC_CH_REMAP_ALL            (0xFFFFUL)
/**
 * @}
 */

/**
 * @defgroup ADC_Channel_Count ADC Channel Count
 * @{
 */
#define ADC1_CH_COUNT               (16U)
#define ADC2_CH_COUNT               (16U)
#define ADC3_CH_COUNT               (20U)
/**
 * @}
 */

/**
 * @defgroup ADC_Invalid_Value ADC Invalid Value
 * @{
 */
#define ADC_INVALID_VAL             (0xFFFFU)
/**
 * @}
 */

/**
 * @defgroup ADC_Extend_Channel_Source ADC Extend Channel Source
 * @{
 */
#define ADC_EXCH_SRC_ADC_PIN        (0x0U)                      /*!< The input source of the extended channel is analog input pin. */
#define ADC_EXCH_SRC_INTERNAL       (ADC_EXCHSELR_EXCHSEL)      /*!< The input source of the extended channel is internal analog signal. */
/**
 * @}
 */

/**
 * @defgroup ADC_Sequence_Status_Flag ADC Sequence Status Flag
 * @{
 */
#define ADC_SEQ_FLAG_EOCA           (ADC_ISR_EOCAF)             /*!< Status flag of the end of conversion of sequence A. */
#define ADC_SEQ_FLAG_EOCB           (ADC_ISR_EOCBF)             /*!< Status flag of the end of conversion of sequence B. */
#define ADC_SEQ_FLAG_NESTED         (ADC_ISR_SASTPDF)           /*!< Status flag of sequence A was interrupted by sequence B. */

#define ADC_SEQ_FLAG_ALL            (ADC_SEQ_FLAG_EOCA | \
                                     ADC_SEQ_FLAG_EOCB | \
                                     ADC_SEQ_FLAG_NESTED)
/**
 * @}
 */

/**
 * @defgroup ADC_Synchronous_Unit ADC Synchronous Unit
 * @{
 */
#define ADC_SYNC_ADC1_ADC2          (0U)                        /*!< ADC1 and ADC2 work synchronously. */
#define ADC_SYNC_ADC1_ADC2_ADC3     (ADC_SYNCCR_SYNCMD_0)       /*!< ADC1, ADC2 and ADC3 work synchronously. */
/**
 * @}
 */

/**
 * @defgroup ADC_Synchronous_Mode ADC Synchronous Mode
 * @{
 */
#define ADC_SYNC_SSHOT_SEQUENTIAL   (0U)                        /*!< Single shot trigger, sequentially trigger. \
                                                                     When the trigger condition occurs, ADC1 starts before ADC2, \
                                                                     and ADC1 and ADC2 only perform one sample conversion. */
#define ADC_SYNC_SSHOT_SIMULTANEOUS (ADC_SYNCCR_SYNCMD_1)       /*!< Single shot trigger, simultaneously trigger. \
                                                                     When the trigger condition occurs, ADC1 and ADC2 start at the same time, \
                                                                     and ADC1 and ADC2 only perform one sample conversion. */
#define ADC_SYNC_CONT_SEQUENTIAL    (ADC_SYNCCR_SYNCMD_2)       /*!< Continuously trigger, sequentially trigger. \
                                                                     When the trigger condition occurs, ADC1 starts before ADC2, \
                                                                     and ADC1 and ADC2 will continue to sample conversion until stoped by software. */
#define ADC_SYNC_CONT_SIMULTANEOUS  (ADC_SYNCCR_SYNCMD_2 | \
                                     ADC_SYNCCR_SYNCMD_1)       /*!< Continuously trigger, simultaneously trigger. \
                                                                     When the trigger condition occurs, ADC1 and ADC2 start at the same time, \
                                                                     and ADC1 and ADC2 will continue to sample conversion until stoped by software. */
/**
 * @}
 */

/**
 * @defgroup ADC_AWD_Comparison_Mode ADC AWD(Analog Watchdog) Comparison Mode
 * @{
 */
#define ADC_AWD_CMP_OUT_RANGE       (0x0U)                      /*!< ADCVal > UpperLimit or ADCVal < LowerLimit */
#define ADC_AWD_CMP_IN_RANGE        (0x1U)                      /*!< LowerLimit < ADCVal < UpperLimit */
/**
 * @}
 */

/**
 * @defgroup ADC_AWD_Combination_Mode ADC AWD(Analog Watchdog) Combination Mode
 * @note If combination mode is valid(ADC_AWD_COMB_OR/ADC_AWD_COMB_AND/ADC_AWD_COMB_XOR) and
         the Channels selected by the AWD0 and AWD1 are deferent, make sure that the channel
         of AWD1 is converted after the channel conversion of AWD0 ends.
 * @{
 */
#define ADC_AWD_COMB_OR             (ADC_AWDCR_AWDCM_0)         /*!< The status of AWD0 is set or the status of AWD1 is set, the status of combination mode is set. */
#define ADC_AWD_COMB_AND            (ADC_AWDCR_AWDCM_1)         /*!< The status of AWD0 is set and the status of AWD1 is set, the status of combination mode is set. */
#define ADC_AWD_COMB_XOR            (ADC_AWDCR_AWDCM_1 | \
                                     ADC_AWDCR_AWDCM_0)         /*!< Only one of the status of AWD0 and AWD1 is set, the status of combination mode is set. */
/**
 * @}
 */

/**
 * @defgroup ADC_AWD_Status_Flag ADC AWD Status Flag
 * @{
 */
#define ADC_AWD_FLAG_AWD0           (ADC_AWDSR_AWD0F)        /*!< Flag of AWD0. */
#define ADC_AWD_FLAG_AWD1           (ADC_AWDSR_AWD1F)           /*!< Flag of AWD1. */
#define ADC_AWD_FLAG_COMB           (ADC_AWDSR_AWDCMF)          /*!< Flag of combination of mode. */

#define ADC_AWD_FLAG_ALL            (ADC_AWD_FLAG_AWD0 | \
                                     ADC_AWD_FLAG_AWD1 | \
                                     ADC_AWD_FLAG_COMB)
/**
 * @}
 */

/**
 * @defgroup ADC_PGA_Gain_Factor ADC PGA Gain Factor
 * @{
 */
#define ADC_PGA_GAIN_2              (0U)                        /*!< PGA gain factor is 2. */
#define ADC_PGA_GAIN_2P133          (ADC_PGACR3_PGAGAIN_0)      /*!< PGA gain factor is 2.133. */
#define ADC_PGA_GAIN_2P286          (ADC_PGACR3_PGAGAIN_1)      /*!< PGA gain factor is 2.286. */
#define ADC_PGA_GAIN_2P667          (ADC_PGACR3_PGAGAIN_1 | \
                                     ADC_PGACR3_PGAGAIN_0)      /*!< PGA gain factor is 2.667. */
#define ADC_PGA_GAIN_2P909          (ADC_PGACR3_PGAGAIN_2)      /*!< PGA gain factor is 2.909. */
#define ADC_PGA_GAIN_3P2            (ADC_PGACR3_PGAGAIN_2 | \
                                     ADC_PGACR3_PGAGAIN_0)      /*!< PGA gain factor is 3.2. */
#define ADC_PGA_GAIN_3P556          (ADC_PGACR3_PGAGAIN_2 | \
                                     ADC_PGACR3_PGAGAIN_1)      /*!< PGA gain factor is 2.556. */
#define ADC_PGA_GAIN_4              (ADC_PGACR3_PGAGAIN_2 | \
                                     ADC_PGACR3_PGAGAIN_1 | \
                                     ADC_PGACR3_PGAGAIN_0)      /*!< PGA gain factor is 4. */
#define ADC_PGA_GAIN_4P571          (ADC_PGACR3_PGAGAIN_3)      /*!< PGA gain factor is 4.571. */
#define ADC_PGA_GAIN_5P333          (ADC_PGACR3_PGAGAIN_3 | \
                                     ADC_PGACR3_PGAGAIN_0)      /*!< PGA gain factor is 5.333. */
#define ADC_PGA_GAIN_6P4            (ADC_PGACR3_PGAGAIN_3 | \
                                     ADC_PGACR3_PGAGAIN_1)      /*!< PGA gain factor is 6.4. */
#define ADC_PGA_GAIN_8              (ADC_PGACR3_PGAGAIN_3 | \
                                     ADC_PGACR3_PGAGAIN_1 | \
                                     ADC_PGACR3_PGAGAIN_0)      /*!< PGA gain factor is 8. */
#define ADC_PGA_GAIN_10P667         (ADC_PGACR3_PGAGAIN_3 | \
                                     ADC_PGACR3_PGAGAIN_2)      /*!< PGA gain factor is 10.667. */
#define ADC_PGA_GAIN_16             (ADC_PGACR3_PGAGAIN_3 | \
                                     ADC_PGACR3_PGAGAIN_2 | \
                                     ADC_PGACR3_PGAGAIN_0)      /*!< PGA gain factor is 16. */
#define ADC_PGA_GAIN_32             (ADC_PGACR3_PGAGAIN_3 | \
                                     ADC_PGACR3_PGAGAIN_2 | \
                                     ADC_PGACR3_PGAGAIN_1)      /*!< PGA gain factor is 32. */
/**
 * @}
 */

/**
 * @defgroup ADC_PGA_VSS ADC PGA VSS
 * @{
 */
#define ADC_PGA_VSS_PGAVSS          (0U)                        /*!< Use pin PGAx_VSS as the reference GND of PGAx */
#define ADC_PGA_VSS_AVSS            (1U)                        /*!< Use AVSS as the reference GND of PGAx. */
/**
 * @}
 */

/**
 * @defgroup ADC_PGA_Unit ADC PGA Unit
 * @{
 */
#define ADC_PGA_1                   (0U)                        /*!< PGA1, belongs to ADC1. Input pin is ADC123_IN0. */
#define ADC_PGA_2                   (1U)                        /*!< PGA2, belongs to ADC1. Input pin is ADC123_IN1. */
#define ADC_PGA_3                   (2U)                        /*!< PGA3, belongs to ADC1. Input pin is ADC123_IN2. */
#define ADC_PGA_4                   (3U)                        /*!< PGA4, belongs to ADC2. Input pin is ADC12_IN6. */
/**
 * @}
 */

/**
 * @defgroup ADC_Common_Trigger_Sel ADC Common Trigger Source Select
 * @{
 */
#define ADC_COM_TRIG1               (AOS_ADC_1_ITRGSELR_COMTRG_EN_0)
#define ADC_COM_TRIG2               (AOS_ADC_1_ITRGSELR_COMTRG_EN_1)
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
en_result_t ADC_Init(M4_ADC_TypeDef *ADCx, const stc_adc_init_t *pstcInit);
void ADC_DeInit(M4_ADC_TypeDef *ADCx);

en_result_t ADC_StructInit(stc_adc_init_t *pstcInit);

void ADC_SetScanMode(M4_ADC_TypeDef *ADCx, uint16_t u16Mode);
en_result_t ADC_ChannelCmd(M4_ADC_TypeDef *ADCx, uint8_t u8Seq, \
                           uint32_t u32AdcCh, const uint8_t pu8SplTime[], \
                           en_functional_state_t enNewState);

void ADC_AvgChannelConfig(M4_ADC_TypeDef *ADCx, uint16_t u16AvgCnt);
void ADC_AvgChannelCmd(M4_ADC_TypeDef *ADCx, uint32_t u32AdcCh, en_functional_state_t enNewState);
void ADC_SetExChannelSrc(M4_ADC_TypeDef *ADCx, uint8_t u8ExChSrc);

en_result_t ADC_TrigSrcStructInit(stc_adc_trig_cfg_t *pstcCfg);
en_result_t ADC_TrigSrcConfig(M4_ADC_TypeDef *ADCx, uint8_t u8Seq, const stc_adc_trig_cfg_t *pstcCfg);
void ADC_TrigSrcCmd(M4_ADC_TypeDef *ADCx, uint8_t u8Seq, en_functional_state_t enNewState);
void ADC_ComTriggerCmd(M4_ADC_TypeDef *ADCx, uint16_t u16TrigSrc, \
                       uint32_t u32ComTrig, en_functional_state_t enNewState);

void ADC_SeqIntCmd(M4_ADC_TypeDef *ADCx, uint8_t u8Seq, en_functional_state_t enNewState);
en_flag_status_t ADC_SeqGetStatus(const M4_ADC_TypeDef *ADCx, uint8_t u8Flag);
void ADC_SeqClrStatus(M4_ADC_TypeDef *ADCx, uint8_t u8Flag);

en_result_t ADC_AWD_Config(M4_ADC_TypeDef *ADCx, uint8_t u8AWDx, const stc_adc_awd_cfg_t *pstcCfg);
void ADC_AWD_CombModeCmd(M4_ADC_TypeDef *ADCx, uint16_t u16CombMode, en_functional_state_t enNewState);
void ADC_AWD_Cmd(M4_ADC_TypeDef *ADCx, uint8_t u8AWDx, en_functional_state_t enNewState);
void ADC_AWD_IntCmd(M4_ADC_TypeDef *ADCx, uint8_t u8AWDx, en_functional_state_t enNewState);
en_flag_status_t ADC_AWD_GetStatus(const M4_ADC_TypeDef *ADCx, uint8_t u8Flag);
void ADC_AWD_ClrStatus(M4_ADC_TypeDef *ADCx, uint8_t u8Flag);

void ADC_PGA_Config(uint8_t u8PGAx, uint8_t u8GainFactor, uint8_t u8PgaVss);
void ADC_PGA_Cmd(uint8_t u8PGAx, en_functional_state_t enNewState);

void ADC_SYNC_Config(uint16_t u16SyncUnit, uint16_t u16SyncMode, uint8_t u8TrigDelay);
void ADC_SYNC_Cmd(en_functional_state_t enNewState);

void ADC_SH_Config(uint8_t u8SplTime);
void ADC_SH_ChannelCmd(uint32_t u32AdcCh, en_functional_state_t enNewState);

void ADC_ChannelRemap(M4_ADC_TypeDef *ADCx, uint32_t u32AdcCh, uint8_t u8AdcPinNum);
uint8_t ADC_GetChannelPinNum(const M4_ADC_TypeDef *ADCx, uint32_t u32AdcCh);

en_result_t ADC_PollingSA(M4_ADC_TypeDef *ADCx, uint16_t pu16AdcVal[], uint8_t u8Length, uint32_t u32Timeout);

void ADC_Start(M4_ADC_TypeDef *ADCx);
void ADC_Stop(M4_ADC_TypeDef *ADCx);
en_result_t ADC_GetAllData(const M4_ADC_TypeDef *ADCx, uint16_t pu16AdcVal[], uint8_t u8Length);
en_result_t ADC_GetChannelData(const M4_ADC_TypeDef *ADCx, uint32_t u32TargetCh, \
                               uint16_t pu16AdcVal[], uint8_t u8Length);
uint16_t ADC_GetValue(const M4_ADC_TypeDef *ADCx, uint8_t u8ChNum);

/**
 * @}
 */

#endif /* DDL_ADC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_ADC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
