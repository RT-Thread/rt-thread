////////////////////////////////////////////////////////////////////////////////
/// @file     hal_adc.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE ADC
///           FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#ifndef __HAL_ADC_H
#define __HAL_ADC_H

// Files includes
#include "types.h"
#include "reg_adc.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup ADC_HAL
/// @brief ADC HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup ADC_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Channels
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_Channel_0                       = 0x00,                   ///< ADC Channel 0
    ADC_Channel_1                       = 0x01,                   ///< ADC Channel 1
    ADC_Channel_2                       = 0x02,                   ///< ADC Channel 2
    ADC_Channel_3                       = 0x03,                   ///< ADC Channel 3
    ADC_Channel_4                       = 0x04,                   ///< ADC Channel 4
    ADC_Channel_5                       = 0x05,                   ///< ADC Channel 5
    ADC_Channel_6                       = 0x06,                   ///< ADC Channel 6
    ADC_Channel_7                       = 0x07,                   ///< ADC Channel 7

    ADC_Channel_8               = 0x08,     ///< ADC Channel 8
    ADC_Channel_9               = 0x09,     ///< ADC Channel 9
    ADC_Channel_10              = 0x0A,     ///< ADC Channel 10
    ADC_Channel_11              = 0x0B,     ///< ADC Channel 11
    ADC_Channel_12              = 0x0C,     ///< ADC Channel 12
    ADC_Channel_13              = 0x0D,     ///< ADC Channel 13
    ADC_Channel_14              = 0x0E,     ///< ADC Channel 14
    ADC_Channel_15              = 0x0F,     ///< ADC Channel 15
    ADC_Channel_TempSensor      = 0x0E,     ///< Temperature sensor channel(ADC1)
    ADC_Channel_VoltReference   = 0x0F,     ///< Internal reference voltage channel(ADC1)
    ADC_Channel_Vrefint         = 0x0F,     ///< Internal reference voltage channel(ADC1)

} ADCCHANNEL_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Sampling_Times
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_Samctl_1_5   = ADC_SMPR1_SAMCTL0_2_5,   ///< ADC sample time select 1.5t
    ADC_Samctl_2_5   = ADC_SMPR1_SAMCTL0_2_5,   ///< ADC sample time select 2.5t
    ADC_Samctl_3_5   = ADC_SMPR1_SAMCTL0_3_5,   ///< ADC sample time select 3.5t
    ADC_Samctl_4_5   = ADC_SMPR1_SAMCTL0_4_5,   ///< ADC sample time select 4.5t
    ADC_Samctl_5_5   = ADC_SMPR1_SAMCTL0_5_5,   ///< ADC sample time select 5.5t
    ADC_Samctl_6_5   = ADC_SMPR1_SAMCTL0_6_5,   ///< ADC sample time select 6.5t
    ADC_Samctl_7_5   = ADC_SMPR1_SAMCTL0_7_5,   ///< ADC sample time select 7.5t
    ADC_Samctl_8_5   = ADC_SMPR1_SAMCTL0_8_5,   ///< ADC sample time select 7.5t
    ADC_Samctl_13_5  = ADC_SMPR1_SAMCTL0_14_5,  ///< ADC sample time select 13.5t
    ADC_Samctl_14_5  = ADC_SMPR1_SAMCTL0_14_5,  ///< ADC sample time select 14.5t
    ADC_Samctl_28_5  = ADC_SMPR1_SAMCTL0_29_5,  ///< ADC sample time select 28.5t
    ADC_Samctl_29_5  = ADC_SMPR1_SAMCTL0_29_5,  ///< ADC sample time select 29.5t
    ADC_Samctl_41_5  = ADC_SMPR1_SAMCTL0_42_5,  ///< ADC sample time select 41.5t
    ADC_Samctl_42_5  = ADC_SMPR1_SAMCTL0_42_5,  ///< ADC sample time select 42.5t
    ADC_Samctl_55_5  = ADC_SMPR1_SAMCTL0_56_5,  ///< ADC sample time select 55.5t
    ADC_Samctl_56_5  = ADC_SMPR1_SAMCTL0_56_5,  ///< ADC sample time select 56.5t
    ADC_Samctl_71_5  = ADC_SMPR1_SAMCTL0_72_5,  ///< ADC sample time select 71.5t
    ADC_Samctl_72_5  = ADC_SMPR1_SAMCTL0_72_5,  ///< ADC sample time select 72.5t
    ADC_Samctl_239_5 = ADC_SMPR1_SAMCTL0_240_5, ///< ADC sample time select 239.5t
    ADC_Samctl_240_5 = ADC_SMPR1_SAMCTL0_240_5  ///< ADC sample time select 240.5t
} ADCSAM_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Resolution
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_Resolution_12b = ADC_CFGR_RSLTCTL_12,  ///< ADC resolution select 12bit
    ADC_Resolution_11b = ADC_CFGR_RSLTCTL_11,  ///< ADC resolution select 11bit
    ADC_Resolution_10b = ADC_CFGR_RSLTCTL_10,  ///< ADC resolution select 10bit
    ADC_Resolution_9b  = ADC_CFGR_RSLTCTL_9,   ///< ADC resolution select 9bit
    ADC_Resolution_8b  = ADC_CFGR_RSLTCTL_8    ///< ADC resolution select 8bit
} ADCRSL_TypeDef;
/// @brief ADC_Prescare
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_PCLK2_PRESCARE_3  = ADC_CFGR_PRE_3,   ///< ADC preclk 3
    ADC_PCLK2_PRESCARE_5  = ADC_CFGR_PRE_5,   ///< ADC preclk 5
    ADC_PCLK2_PRESCARE_7  = ADC_CFGR_PRE_7,   ///< ADC preclk 7
    ADC_PCLK2_PRESCARE_9  = ADC_CFGR_PRE_9,   ///< ADC preclk 9
    ADC_PCLK2_PRESCARE_11 = ADC_CFGR_PRE_11,  ///< ADC preclk 11
    ADC_PCLK2_PRESCARE_13 = ADC_CFGR_PRE_13,  ///< ADC preclk 13
    ADC_PCLK2_PRESCARE_15 = ADC_CFGR_PRE_15,  ///< ADC preclk 15
    ADC_PCLK2_PRESCARE_17 = ADC_CFGR_PRE_17,  ///< ADC preclk 17

    ADC_PCLK2_PRESCARE_2  = ADC_CFGR_PRE_2,   ///< ADC preclk 2
    ADC_PCLK2_PRESCARE_4  = ADC_CFGR_PRE_4,   ///< ADC preclk 4
    ADC_PCLK2_PRESCARE_6  = ADC_CFGR_PRE_6,   ///< ADC preclk 6
    ADC_PCLK2_PRESCARE_8  = ADC_CFGR_PRE_8,   ///< ADC preclk 8
    ADC_PCLK2_PRESCARE_10 = ADC_CFGR_PRE_10,  ///< ADC preclk 10
    ADC_PCLK2_PRESCARE_12 = ADC_CFGR_PRE_12,  ///< ADC preclk 12
    ADC_PCLK2_PRESCARE_14 = ADC_CFGR_PRE_14,  ///< ADC preclk 14
    ADC_PCLK2_PRESCARE_16 = ADC_CFGR_PRE_16   ///< ADC preclk 16
} ADCPRE_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Conversion_Mode
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_Mode_Imm        = ADC_CR_IMM,       ///< ADC single convert mode
    ADC_Mode_Scan       = ADC_CR_SCAN,      ///< ADC single period convert mode
    ADC_Mode_Continue   = ADC_CR_CONTINUE   ///< ADC continue scan convert mode
} ADCMODE_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Extrenal_Trigger_Sources_For_Regular_Channels_Conversion
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC1_ExternalTrigConv_T1_CC1        = ADC_CR_T1_CC1,
    ADC1_ExternalTrigConv_T1_CC2        = ADC_CR_T1_CC2,
    ADC1_ExternalTrigConv_T1_CC3        = ADC_CR_T1_CC3,
    ADC1_ExternalTrigConv_T2_CC2        = ADC_CR_T2_CC2,
    ADC1_ExternalTrigConv_T3_TRIG       = ADC_CR_T3_TRIG,
    ADC1_ExternalTrigConv_T3_CC1        = ADC_CR_T3_CC1,
    ADC1_ExternalTrigConv_EXTI_11       = ADC_CR_EXTI_11,
    ADC1_ExternalTrigConv_T1_CC4_CC5    = ADC_CR_T1_CC4_CC5,
    ADC1_ExternalTrigConv_T1_TRIG       = ADC_CR_T1_TRIG,
    ADC1_ExternalTrigConv_T8_CC4        = ADC_CR_T8_CC4,
    ADC1_ExternalTrigConv_T8_CC4_CC5    = ADC_CR_T8_CC4_CC5,
    ADC1_ExternalTrigConv_T2_CC1        = ADC_CR_T2_CC1,
    ADC1_ExternalTrigConv_T3_CC4        = ADC_CR_T3_CC4,
    ADC1_ExternalTrigConv_T2_TRIG       = ADC_CR_T2_TRIG,
    ADC1_ExternalTrigConv_T8_CC5        = ADC_CR_T8_CC5,
    ADC1_ExternalTrigConv_EXTI_15       = ADC_CR_EXTI_15,
    ADC1_ExternalTrigConv_T1_CC4        = ADC_CR_TIM1_CC4,
    ADC1_ExternalTrigConv_T1_CC5        = ADC_CR_TIM1_CC5
} EXTERTRIG_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Data_Align
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_DataAlign_Right = ADC_CR_RIGHT,     ///< ADC data left align
    ADC_DataAlign_Left  = ADC_CR_LEFT       ///< ADC data right align
} ADCDATAALI_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Flags_Definition
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_IT_EOC = 1,                            ///< ADC conversion flag
    ADC_FLAG_EOC = 1,
    ADC_IT_AWD = 2,                            ///< ADC window comparator flag
    ADC_FLAG_AWD = 2
} ADCFLAG_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Trig_Edge
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_ADC_Trig_Edge_Dual              = ADC_CR_TRG_EDGE_DUAL,                 ///< ADC trig edge dual mode down and up
    ADC_ADC_Trig_Edge_Down              = ADC_CR_TRG_EDGE_DOWN,                 ///< ADC trig edge single mode down
    ADC_ADC_Trig_Edge_Up                = ADC_CR_TRG_EDGE_UP,                   ///< ADC trig edge single mode up
    ADC_ADC_Trig_Edge_Mask              = ADC_CR_TRG_EDGE_MASK                  ///< ADC trig edge is mask, not allowed
} ADCTRIGEDGE_TypeDef;


////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Scan_Direct
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_Scan_Direct_Up                  = ADC_CR_SCANDIR,                       ///< ADC scan from low channel to high channel
    ADC_Scan_Direct_Down                = 0                                     ///< ADC scan from High channel to low channel
} ADCSCANDIRECT_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Trig_Shift
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_ADC_Trig_Shift_0                = ADC_CR_TRGSHIFT_0,                    ///< ADC trig shift bit is 0
    ADC_ADC_Trig_Shift_4                = ADC_CR_TRGSHIFT_4,                    ///< ADC trig shift bit is 4
    ADC_ADC_Trig_Shift_16               = ADC_CR_TRGSHIFT_16,                   ///< ADC trig shift bit is 16
    ADC_ADC_Trig_Shift_32               = ADC_CR_TRGSHIFT_32,                   ///< ADC trig shift bit is 32
    ADC_ADC_Trig_Shift_64               = ADC_CR_TRGSHIFT_64,                   ///< ADC trig shift bit is 64
    ADC_ADC_Trig_Shift_128              = ADC_CR_TRGSHIFT_128,                  ///< ADC trig shift bit is 128
    ADC_ADC_Trig_Shift_256              = ADC_CR_TRGSHIFT_256,                  ///< ADC trig shift bit is 256
    ADC_ADC_Trig_Shift_512              = ADC_CR_TRGSHIFT_512,                  ///< ADC trig shift bit is 512
} ADCTRIGSHIFT_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Inject_Sequence_Length the sequencer length for injected channels
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_Inject_Seqen_Len1               = 0,                                    ///< ADC Injected Seqence length is 1
    ADC_Inject_Seqen_Len2               = 1,                                    ///< ADC Injected Seqence length is 2
    ADC_Inject_Seqen_Len3               = 2,                                    ///< ADC Injected Seqence length is 3
    ADC_Inject_Seqen_Len4               = 3,                                    ///< ADC Injected Seqence length is 4
} ADC_INJ_SEQ_LEN_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Inject_Sequence_Length the sequencer length for injected channels
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_InjectedChannel_1 = 0x00,
    ADC_InjectedChannel_2 = 0x04,
    ADC_InjectedChannel_3 = 0x08,
    ADC_InjectedChannel_4 = 0x0c,
} ADC_INJ_SEQ_Channel_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Extrenal_Trigger_Sources_For_Regular_Channels_Conversion
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC1_InjectExtTrigSrc_T1_TRGO       = ADC_ANY_CR_JTRGSEL_TIM1_TRGO,         ///< TIM1 TRGO
    ADC1_InjectExtTrigSrc_T1_CC4        = ADC_ANY_CR_JTRGSEL_TIM1_CC4,          ///< TIM1 CC4
    ADC1_InjectExtTrigSrc_T1_CC4_CC5    = ADC_ANY_CR_JTRGSEL_TIM1_CC4_CC5,      ///< TIM1 CC4 and CC5
    ADC1_InjectExtTrigSrc_T2_CC1        = ADC_ANY_CR_JTRGSEL_TIM2_TIM4CC1,      ///< TIM2 CC1
    ADC1_InjectExtTrigSrc_T3_CC4        = ADC_ANY_CR_JTRGSEL_TIM3_TIM5CC4,      ///< TIM3 CC4
    ADC1_InjectExtTrigSrc_T8_CC4        = ADC_ANY_CR_JTRGSEL_TIM8_CC4,          ///< TIM8 CC4
    ADC1_InjectExtTrigSrc_T8_CC4_CC5    = ADC_ANY_CR_JTRGSEL_TIM8_CC4_CC5,      ///< TIM8 CC4 and CC5
    ADC1_InjectExtTrigSrc_EXTI_12       = ADC_ANY_CR_JTRGSEL_EXTI12,            ///< EXTI12

    ADC2_InjectExtTrigSrc_T1_TRGO       = ADC_ANY_CR_JTRGSEL_TIM1_TRGO,         ///< TIM1 TRGO
    ADC2_InjectExtTrigSrc_T1_CC4        = ADC_ANY_CR_JTRGSEL_TIM1_CC4,          ///< TIM1 CC4
    ADC2_InjectExtTrigSrc_T1_CC4_CC5    = ADC_ANY_CR_JTRGSEL_TIM1_CC4_CC5,      ///< TIM1 CC4 and CC5
    ADC2_InjectExtTrigSrc_T2_CC1        = ADC_ANY_CR_JTRGSEL_TIM2_TIM4CC1,      ///< TIM2 CC1
    ADC2_InjectExtTrigSrc_T3_CC4        = ADC_ANY_CR_JTRGSEL_TIM3_TIM5CC4,      ///< TIM3 CC4
    ADC2_InjectExtTrigSrc_T8_CC4        = ADC_ANY_CR_JTRGSEL_TIM8_CC4,          ///< TIM8 CC4
    ADC2_InjectExtTrigSrc_T8_CC4_CC5    = ADC_ANY_CR_JTRGSEL_TIM8_CC4_CC5,      ///< TIM8 CC4 and CC5

    ADC2_InjectExtTrigSrc_EXTI_12       = ADC_ANY_CR_JTRGSEL_EXTI12,            ///< EXTI12
    ADC3_InjectExtTrigSrc_T1_TRGO       = ADC_ANY_CR_JTRGSEL_TIM1_TRGO,         ///< TIM1 TRGO
    ADC3_InjectExtTrigSrc_T1_CC4        = ADC_ANY_CR_JTRGSEL_TIM1_CC4,          ///< TIM1 CC4
    ADC3_InjectExtTrigSrc_T1_CC4_CC5    = ADC_ANY_CR_JTRGSEL_TIM1_CC4_CC5,      ///< TIM1 CC4 and CC5
    ADC3_InjectExtTrigSrc_T4_CC1        = ADC_ANY_CR_JTRGSEL_TIM2_TIM4CC1,      ///< TIM4 CC1
    ADC3_InjectExtTrigSrc_T5_CC4        = ADC_ANY_CR_JTRGSEL_TIM3_TIM5CC4,      ///< TIM5 CC4
    ADC3_InjectExtTrigSrc_T8_CC4        = ADC_ANY_CR_JTRGSEL_TIM8_CC4,          ///< TIM8 CC4
    ADC3_InjectExtTrigSrc_T8_CC4_CC5    = ADC_ANY_CR_JTRGSEL_TIM8_CC4_CC5,      ///< TIM8 CC4 and CC5
    ADC3_InjectExtTrigSrc_EXTI_12       = ADC_ANY_CR_JTRGSEL_EXTI12,            ///< EXTI12
} EXTER_INJ_TRIG_TypeDef;


////////////////////////////////////////////////////////////////////////////////
/// @brief ADC Init Structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    u32                                 ADC_Resolution;                         ///< Convert data resolution
    u32                                 ADC_PRESCARE;                           ///< Clock prescaler
    u32                                 ADC_Mode;                               ///< ADC conversion mode
    FunctionalState                     ADC_ContinuousConvMode;                 ///< Useless just for compatibility
    u32                                 ADC_ExternalTrigConv;                   ///< External trigger source selection
    u32                                 ADC_DataAlign;                          ///< Data alignmentn
} ADC_InitTypeDef;

/// @}






////////////////////////////////////////////////////////////////////////////////
/// @defgroup ADC_Exported_Variables
/// @{
#ifdef _HAL_ADC_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup ADC_Exported_Functions
/// @{
void ADC_DeInit(ADC_TypeDef* adc);
void ADC_Init(ADC_TypeDef* adc, ADC_InitTypeDef* init_struct);
void ADC_StructInit(ADC_InitTypeDef* init_struct);
void ADC_Cmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_DMACmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_ITConfig(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_interrupt, FunctionalState state);
void ADC_SoftwareStartConvCmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_RegularChannelConfig(ADC_TypeDef* adc, u32 channel, u8 rank, u32 sample_time);//ADCSAM_TypeDef
void ADC_ExternalTrigConvCmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_ExternalTrigConvConfig(ADC_TypeDef* adc, EXTERTRIG_TypeDef adc_external_trig_source);
#define ADC_ExternalTrigInjectedConvConfig ADC_ExternalTrigConvConfig
void ADC_AnalogWatchdogCmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* adc, u16 high_threshold, u16 low_threshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* adc, ADCCHANNEL_TypeDef channel);
void ADC_TempSensorVrefintCmd(FunctionalState state);
void ADC_ClearITPendingBit(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_interrupt);
void ADC_ClearFlag(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_flag);

u16 ADC_GetConversionValue(ADC_TypeDef* adc);

FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* adc);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_flag);
ITStatus   ADC_GetITStatus(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_interrupt);
void ADC_TempSensorCmd(FunctionalState state);
void ADC_VrefintCmd(FunctionalState state);
void exADC_TempSensorVrefintCmd(u32 chs, FunctionalState state);
void ADC_ANY_CH_Config(ADC_TypeDef* adc, u8 rank, ADCCHANNEL_TypeDef adc_channel);
void ADC_ANY_NUM_Config(ADC_TypeDef* adc, u8 num);
void ADC_ANY_Cmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_AutoInjectedConvCmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_ExternalTrigInjectedConvertConfig(ADC_TypeDef* adc, EXTER_INJ_TRIG_TypeDef ADC_ExtInjTrigSource);
void ADC_InjectedConvCmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_ExternalTrigInjectedConvCmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_InjectedSequencerConfig(ADC_TypeDef* adc, u32 event, u32 sample_time);
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* adc, ADC_INJ_SEQ_LEN_TypeDef Length);
void ADC_InjectedSequencerChannelConfig(ADC_TypeDef* adc, ADC_INJ_SEQ_Channel_TypeDef off_addr, ADCCHANNEL_TypeDef channel);
u16 ADC_GetInjectedConversionValue(ADC_TypeDef* adc, ADC_INJ_SEQ_Channel_TypeDef off_addr);
u16 ADC_GetInjectedCurrentConvertedValue(ADC_TypeDef* adc);
void ADC_SetInjectedOffset(ADC_TypeDef* adc, ADC_INJ_SEQ_Channel_TypeDef off_addr, u16 value);
u16 ADC_GetChannelConvertedValue(ADC_TypeDef* adc, ADCCHANNEL_TypeDef channel);
/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

