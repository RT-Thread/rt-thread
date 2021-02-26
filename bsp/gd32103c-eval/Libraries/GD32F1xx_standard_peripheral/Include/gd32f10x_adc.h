/**
  ******************************************************************************
  * @brief   ADC header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_ADC_H
#define __GD32F10X_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { FALSE = 0, TRUE } BOOL;
/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"
/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/** @defgroup ADC_Exported_Types
  * @{
  */

/**
  * @brief  ADC Init structure definition
  */

typedef struct {
    uint32_t ADC_Trig_External;         /*!< AD conversion of regular channels trigger.  */
    uint8_t ADC_Channel_Number;         /*!< The number of converted ADC channels .
                                             This parameter must range from 1 to 16. */
    uint32_t ADC_Data_Align;            /*!< ADC data alignment,left or right. */

    TypeState ADC_Mode_Scan;            /*!< AD conversion mode,multichannels mode or Single channel mode.
                                             This parameter can be ENABLE or DISABLE */
    uint32_t ADC_Mode;                  /*!< AD operation mode,independent mode or dual mode.
                                             This parameter can be a value of @ref ADC_mode */
    TypeState ADC_Mode_Continuous;      /*!< AD perform mode,continuous mode or single mode.
                                             This parameter can be ENABLE or DISABLE. */
} ADC_InitPara;

/**
  * @}
  */
/** @defgroup ADC_Exported_Constants
  * @{
  */

/** @defgroup ADC_external_trigger
  * @{
  */
#define ADC_EXTERNAL_TRIGGER_MODE_T1_CC1             ((uint32_t)0x00000000) /*!< Only used in ADC1 and ADC2 */
#define ADC_EXTERNAL_TRIGGER_MODE_T1_CC2             ((uint32_t)0x00020000) /*!< Only used in ADC1 and ADC2 */
#define ADC_EXTERNAL_TRIGGER_MODE_T2_CC2             ((uint32_t)0x00060000) /*!< Only used in ADC1 and ADC2 */
#define ADC_EXTERNAL_TRIGGER_MODE_T3_TRGO            ((uint32_t)0x00080000) /*!< Only used in ADC1 and ADC2 */
#define ADC_EXTERNAL_TRIGGER_MODE_T4_CC4             ((uint32_t)0x000A0000) /*!< Only used in ADC1 and ADC2 */
#define ADC_EXTERNAL_TRIGGER_MODE_EXT_IT11_T8_TRGO   ((uint32_t)0x000C0000) /*!< Only used in ADC1 and ADC2 */
#define ADC_EXTERNAL_TRIGGER_MODE_T1_CC3             ((uint32_t)0x00040000) /*!< Used in ADC1,ADC2 and ADC3 */
#define ADC_EXTERNAL_TRIGGER_MODE_NONE               ((uint32_t)0x000E0000) /*!< Used in ADC1,ADC2 and ADC3 */
#define ADC_EXTERNAL_TRIGGER_MODE_T3_CC1             ((uint32_t)0x00000000) /*!< Only used in ADC3 */
#define ADC_EXTERNAL_TRIGGER_MODE_T2_CC3             ((uint32_t)0x00020000) /*!< Only used in ADC3 */
#define ADC_EXTERNAL_TRIGGER_MODE_T8_CC1             ((uint32_t)0x00060000) /*!< Only used in ADC3 */
#define ADC_EXTERNAL_TRIGGER_MODE_T8_TRGO            ((uint32_t)0x00080000) /*!< Only used in ADC3 */
#define ADC_EXTERNAL_TRIGGER_MODE_T5_CC1             ((uint32_t)0x000A0000) /*!< Only used in ADC3 */
#define ADC_EXTERNAL_TRIGGER_MODE_T5_CC3             ((uint32_t)0x000C0000) /*!< Only used in ADC3 */

/**
  * @}
  */

/** @defgroup ADC_channels
  * @{
  */
#define ADC_CHANNEL_0                                ((uint8_t)0x00)
#define ADC_CHANNEL_1                                ((uint8_t)0x01)
#define ADC_CHANNEL_2                                ((uint8_t)0x02)
#define ADC_CHANNEL_3                                ((uint8_t)0x03)
#define ADC_CHANNEL_4                                ((uint8_t)0x04)
#define ADC_CHANNEL_5                                ((uint8_t)0x05)
#define ADC_CHANNEL_6                                ((uint8_t)0x06)
#define ADC_CHANNEL_7                                ((uint8_t)0x07)
#define ADC_CHANNEL_8                                ((uint8_t)0x08)
#define ADC_CHANNEL_9                                ((uint8_t)0x09)
#define ADC_CHANNEL_10                               ((uint8_t)0x0A)
#define ADC_CHANNEL_11                               ((uint8_t)0x0B)
#define ADC_CHANNEL_12                               ((uint8_t)0x0C)
#define ADC_CHANNEL_13                               ((uint8_t)0x0D)
#define ADC_CHANNEL_14                               ((uint8_t)0x0E)
#define ADC_CHANNEL_15                               ((uint8_t)0x0F)
#define ADC_CHANNEL_16                               ((uint8_t)0x10)
#define ADC_CHANNEL_17                               ((uint8_t)0x11)
#define ADC_CHANNEL_TEMPSENSOR                       ((uint8_t)ADC_CHANNEL_16)
#define ADC_CHANNEL_VREFINT                          ((uint8_t)ADC_CHANNEL_17)

/**
  * @}
  */

/** @defgroup ADC_data_align
  * @{
  */
#define ADC_DATAALIGN_RIGHT                          ((uint32_t)0x00000000)
#define ADC_DATAALIGN_LEFT                           ((uint32_t)0x00000800)

/**
  * @}
  */

/** @defgroup ADC_mode
  * @{
  */
#define ADC_MODE_INDEPENDENT                         ((uint32_t)0x00000000)
#define ADC_MODE_REGINSERTSIMULT                     ((uint32_t)0x00010000)
#define ADC_MODE_REGSIMULT_ALTERTRIG                 ((uint32_t)0x00020000)
#define ADC_MODE_INSERTSIMULT_FASTINTERL             ((uint32_t)0x00030000)
#define ADC_MODE_INSERTSIMULT_SLOWINTERL             ((uint32_t)0x00040000)
#define ADC_MODE_INSERTSIMULT                        ((uint32_t)0x00050000)
#define ADC_MODE_REGSIMULT                           ((uint32_t)0x00060000)
#define ADC_MODE_FASTINTERL                          ((uint32_t)0x00070000)
#define ADC_MODE_SLOWINTERL                          ((uint32_t)0x00080000)
#define ADC_MODE_ALTERTRIG                           ((uint32_t)0x00090000)

/**
  * @}
  */

/** @defgroup ADC_sampling_time
  * @{
  */
#define ADC_SAMPLETIME_1POINT5                       ((uint8_t)0x00)
#define ADC_SAMPLETIME_7POINT5                       ((uint8_t)0x01)
#define ADC_SAMPLETIME_13POINT5                      ((uint8_t)0x02)
#define ADC_SAMPLETIME_28POINT5                      ((uint8_t)0x03)
#define ADC_SAMPLETIME_41POINT5                      ((uint8_t)0x04)
#define ADC_SAMPLETIME_55POINT5                      ((uint8_t)0x05)
#define ADC_SAMPLETIME_71POINT5                      ((uint8_t)0x06)
#define ADC_SAMPLETIME_239POINT5                     ((uint8_t)0x07)

/**
  * @}
  */

/** @defgroup ADC_external_trigger_sources_for_inserted_channels_conversion
  * @{
  */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T2_TRGO         ((uint32_t)0x00002000) /*!< Only used in ADC1 and ADC2 */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T2_CC1          ((uint32_t)0x00003000) /*!< Only used in ADC1 and ADC2 */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T3_CC4          ((uint32_t)0x00004000) /*!< Only used in ADC1 and ADC2 */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T4_TRGO         ((uint32_t)0x00005000) /*!< Only used in ADC1 and ADC2 */
#define ADC_EXTERNAL_TRIG_INSERTCONV_EXT_IT15_T8_CC4 ((uint32_t)0x00006000) /*!< Only used in ADC1 and ADC2 */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T1_TRIG         ((uint32_t)0x00000000) /*!< Used in ADC1,ADC2 and ADC3 */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T1_CC4          ((uint32_t)0x00001000) /*!< Used in ADC1,ADC2 and ADC3 */
#define ADC_EXTERNAL_TRIG_INSERTCONV_NONE            ((uint32_t)0x00007000) /*!< Used in ADC1,ADC2 and ADC3 */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T4_CC3          ((uint32_t)0x00002000) /*!< Only used in ADC3 */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T8_CC2          ((uint32_t)0x00003000) /*!< Only used in ADC3 */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T8_CC4          ((uint32_t)0x00004000) /*!< Only used in ADC3 */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T5_TRGO         ((uint32_t)0x00005000) /*!< Only used in ADC3 */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T5_CC4          ((uint32_t)0x00006000) /*!< Only used in ADC3 */

/**
  * @}
  */

/** @defgroup ADC_inserted_channel_selection
  * @{
  */
#define ADC_INSERTEDCHANNEL_1                        ((uint8_t)0x14)
#define ADC_INSERTEDCHANNEL_2                        ((uint8_t)0x18)
#define ADC_INSERTEDCHANNEL_3                        ((uint8_t)0x1C)
#define ADC_INSERTEDCHANNEL_4                        ((uint8_t)0x20)

/**
  * @}
  */

/** @defgroup ADC_analog_watchdog_selection
  * @{
  */
#define ADC_ANALOGWATCHDOG_SINGLEREGENABLE           ((uint32_t)0x00800200)
#define ADC_ANALOGWATCHDOG_SINGLEINSERTENABLE        ((uint32_t)0x00400200)
#define ADC_ANALOGWATCHDOG_SINGLEREGORINSERTENABLE   ((uint32_t)0x00C00200)
#define ADC_ANALOGWATCHDOG_ALLREGENABLE              ((uint32_t)0x00800000)
#define ADC_ANALOGWATCHDOG_ALLINSERTENABLE           ((uint32_t)0x00400000)
#define ADC_ANALOGWATCHDOG_ALLREGALLINSERTENABLE     ((uint32_t)0x00C00000)
#define ADC_ANALOGWATCHDOG_NONE                      ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ADC_interrupts_definition
  * @{
  */
#define ADC_INT_EOC                                  ((uint16_t)0x0220)
#define ADC_INT_AWE                                  ((uint16_t)0x0140)
#define ADC_INT_EOIC                                 ((uint16_t)0x0480)

/**
  * @}
  */

/** @defgroup ADC_flags_definition
  * @{
  */
#define ADC_FLAG_AWE                                 ((uint8_t)0x01)
#define ADC_FLAG_EOC                                 ((uint8_t)0x02)
#define ADC_FLAG_EOIC                                ((uint8_t)0x04)
#define ADC_FLAG_STIC                                ((uint8_t)0x08)
#define ADC_FLAG_STRC                                ((uint8_t)0x10)

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup ADC_Exported_Functions
  * @{
  */
void ADC_DeInit(ADC_TypeDef *ADCx, ADC_InitPara *ADC_InitParaStruct);
void ADC_Init(ADC_TypeDef *ADCx, ADC_InitPara *ADC_InitParaStruct);
void ADC_Enable(ADC_TypeDef *ADCx, TypeState NewValue);
void ADC_DMA_Enable(ADC_TypeDef *ADCx, TypeState NewValue);
void ADC_INTConfig(ADC_TypeDef *ADCx, uint16_t ADC_INT, TypeState NewValue);
void ADC_Calibration(ADC_TypeDef *ADCx);
void ADC_SoftwareStartConv_Enable(ADC_TypeDef *ADCx, TypeState NewValue);
TypeState ADC_GetSoftwareStartConvBitState(ADC_TypeDef *ADCx);
void ADC_DiscModeChannelCount_Config(ADC_TypeDef *ADCx, uint8_t Number);
void ADC_DiscMode_Enable(ADC_TypeDef *ADCx, TypeState NewValue);
void ADC_RegularChannel_Config(ADC_TypeDef *ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_ExternalTrigConv_Enable(ADC_TypeDef *ADCx, TypeState NewValue);
uint16_t ADC_GetConversionValue(ADC_TypeDef *ADCx);
uint32_t ADC_GetDualModeConversionValue(void);
void ADC_AutoInsertedConv_Enable(ADC_TypeDef *ADCx, TypeState NewValue);
void ADC_InsertedDiscMode_Enable(ADC_TypeDef *ADCx, TypeState NewValue);
void ADC_ExternalTrigInsertedConv_Config(ADC_TypeDef *ADCx, uint32_t ADC_ExternalTrigInsertConv);
void ADC_ExternalTrigInsertedConv_Enable(ADC_TypeDef *ADCx, TypeState NewValue);
void ADC_SoftwareStartInsertedConv_Enable(ADC_TypeDef *ADCx, TypeState NewValue);
TypeState ADC_GetSoftwareStartInsertedConvCmdBitState(ADC_TypeDef *ADCx);
void ADC_InsertedChannel_Config(ADC_TypeDef *ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_InsertedSequencerLength_Config(ADC_TypeDef *ADCx, uint8_t Length);
void ADC_SetInsertedOffset(ADC_TypeDef *ADCx, uint8_t ADC_InsertedChannel, uint16_t Offset);
uint16_t ADC_GetInsertedConversionValue(ADC_TypeDef *ADCx, uint8_t ADC_InsertedChannel);
void ADC_AnalogWatchdog_Enable(ADC_TypeDef *ADCx, uint32_t ADC_AnalogWatchdog);
void ADC_AnalogWatchdogThresholds_Config(ADC_TypeDef *ADCx, uint16_t HighThreshold, uint16_t LowThreshold);
void ADC_AnalogWatchdogSingleChannel_Config(ADC_TypeDef *ADCx, uint8_t ADC_Channel);
void ADC_TempSensorVrefint_Enable(TypeState NewValue);
TypeState ADC_GetBitState(ADC_TypeDef *ADCx, uint8_t ADC_FLAG);
void ADC_ClearBitState(ADC_TypeDef *ADCx, uint8_t ADC_FLAG);
TypeState ADC_GetIntState(ADC_TypeDef *ADCx, uint16_t ADC_INT);
void ADC_ClearIntBitState(ADC_TypeDef *ADCx, uint16_t ADC_INT);

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

#endif /*__GD32F10X_ADC_H */
