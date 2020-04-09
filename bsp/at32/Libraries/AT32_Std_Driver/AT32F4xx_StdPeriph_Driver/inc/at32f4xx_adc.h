/**
 **************************************************************************
 * File Name    : at32f4xx_adc.h
 * Description  : at32f4xx ADC header file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_ADC_H
#define __AT32F4xx_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
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

typedef struct
{
    uint32_t ADC_Mode;                      /*!< Configures the ADC to operate in independent or
                                               dual mode.
                                               This parameter can be a value of @ref ADC_mode */

    FunctionalState ADC_ScanMode;           /*!< Specifies whether the conversion is performed in
                                                   Scan (multichannels) or Single (one channel) mode.
                                                   This parameter can be set to ENABLE or DISABLE */

    FunctionalState ADC_ContinuousMode;     /*!< Specifies whether the conversion is performed in
                                                   Continuous or Single mode.
                                                   This parameter can be set to ENABLE or DISABLE. */

    uint32_t ADC_ExternalTrig;              /*!< Defines the external trigger used to start the analog
                                                   to digital conversion of regular channels. This parameter
                                                   can be a value of @ref ADC_external_trigger_sources_for_regular_channels_conversion */

    uint32_t ADC_DataAlign;                 /*!< Specifies whether the ADC data alignment is left or right.
                                               This parameter can be a value of @ref ADC_data_align */

    uint8_t ADC_NumOfChannel;               /*!< Specifies the number of ADC channels that will be converted
                                               using the sequencer for regular channel group.
                                               This parameter must range from 1 to 16. */
} ADC_InitType;
/**
  * @}
  */

/** @defgroup ADC_Exported_Constants
  * @{
  */


#if defined (AT32F403xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)
#define IS_ADC_ALL_PERIPH(PERIPH)           (((PERIPH) == ADC1) || \
                                             ((PERIPH) == ADC2) || \
                                             ((PERIPH) == ADC3))
#elif defined (AT32F413xx)
#define IS_ADC_ALL_PERIPH(PERIPH)           (((PERIPH) == ADC1) || \
                                             ((PERIPH) == ADC2))
#elif defined (AT32F415xx)
#define IS_ADC_ALL_PERIPH(PERIPH)           (((PERIPH) == ADC1))
#endif


#if defined (AT32F403xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)
#define IS_ADC_DMA_PERIPH(PERIPH)           (((PERIPH) == ADC1) || \
                                             ((PERIPH) == ADC3))
#elif defined (AT32F413xx) || defined (AT32F415xx)
#define IS_ADC_DMA_PERIPH(PERIPH)           (((PERIPH) == ADC1))
#endif


/** @defgroup ADC_mode
  * @{
  */

#define ADC_Mode_Independent                ((uint32_t)0x00000000)
#define ADC_Mode_RegInjecSimult             ((uint32_t)0x00010000)
#define ADC_Mode_RegSimult_AlterTrig        ((uint32_t)0x00020000)
#define ADC_Mode_InjecSimult_FastInterl     ((uint32_t)0x00030000)
#define ADC_Mode_InjecSimult_SlowInterl     ((uint32_t)0x00040000)
#define ADC_Mode_InjecSimult                ((uint32_t)0x00050000)
#define ADC_Mode_RegSimult                  ((uint32_t)0x00060000)
#define ADC_Mode_FastInterl                 ((uint32_t)0x00070000)
#define ADC_Mode_SlowInterl                 ((uint32_t)0x00080000)
#define ADC_Mode_AlterTrig                  ((uint32_t)0x00090000)

#define IS_ADC_MODE(MODE)                   (((MODE) == ADC_Mode_Independent) || \
                                             ((MODE) == ADC_Mode_RegInjecSimult) || \
                                             ((MODE) == ADC_Mode_RegSimult_AlterTrig) || \
                                             ((MODE) == ADC_Mode_InjecSimult_FastInterl) || \
                                             ((MODE) == ADC_Mode_InjecSimult_SlowInterl) || \
                                             ((MODE) == ADC_Mode_InjecSimult) || \
                                             ((MODE) == ADC_Mode_RegSimult) || \
                                             ((MODE) == ADC_Mode_FastInterl) || \
                                             ((MODE) == ADC_Mode_SlowInterl) || \
                                             ((MODE) == ADC_Mode_AlterTrig))
/**
  * @}
  */

/** @defgroup ADC_external_trigger_sources_for_regular_channels_conversion
  * @{
  */

#define ADC_ExternalTrig_TMR1_CC1_ADC12             ((uint32_t)0x00000000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrig_TMR1_CC2_ADC12             ((uint32_t)0x00020000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrig_TMR2_CC2_ADC12             ((uint32_t)0x00060000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrig_TMR3_TRGO_ADC12            ((uint32_t)0x00080000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrig_TMR4_CC4_ADC12             ((uint32_t)0x000A0000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrig_Ext_INT11_TMR8_TRGO_ADC12  ((uint32_t)0x000C0000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrig_TMR8_CC1_ADC12             ((uint32_t)0x020C0000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrig_TMR8_CC2_ADC12             ((uint32_t)0x020E0000) /*!< For ADC1 and ADC2 */
                                                    
#define ADC_ExternalTrig_TMR1_CC3                   ((uint32_t)0x00040000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrig_None                       ((uint32_t)0x000E0000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrig_TMR15_CC1                  ((uint32_t)0x02000000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrig_TMR15_CC2                  ((uint32_t)0x02020000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrig_TMR15_CC3                  ((uint32_t)0x02040000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrig_TMR15_CC4                  ((uint32_t)0x02060000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrig_TMR15_TRGO                 ((uint32_t)0x02080000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrig_TMR1_TRGO                  ((uint32_t)0x020A0000) /*!< For ADC1, ADC2 and ADC3 */
                                                    
#define ADC_ExternalTrig_TMR3_CC1_ADC3              ((uint32_t)0x00000000) /*!< For ADC3 only */
#define ADC_ExternalTrig_TMR2_CC3_ADC3              ((uint32_t)0x00020000) /*!< For ADC3 only */
#define ADC_ExternalTrig_TMR8_CC1_ADC3              ((uint32_t)0x00060000) /*!< For ADC3 only */
#define ADC_ExternalTrig_TMR8_TRGO_ADC3             ((uint32_t)0x00080000) /*!< For ADC3 only */
#define ADC_ExternalTrig_TMR5_CC1_ADC3              ((uint32_t)0x000A0000) /*!< For ADC3 only */
#define ADC_ExternalTrig_TMR5_CC3_ADC3              ((uint32_t)0x000C0000) /*!< For ADC3 only */
#define ADC_ExternalTrig_TMR1_CC1_ADC3              ((uint32_t)0x020C0000) /*!< For ADC3 only */
#define ADC_ExternalTrig_TMR8_CC3_ADC3              ((uint32_t)0x020E0000) /*!< For ADC3 only */

#define IS_ADC_EXT_TRIG(REGTRIG)                    (((REGTRIG) == ADC_ExternalTrig_TMR1_CC1_ADC12) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR1_CC2_ADC12) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR2_CC2_ADC12) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR3_TRGO_ADC12) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR4_CC4_ADC12) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_Ext_INT11_TMR8_TRGO_ADC12) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR8_CC1_ADC12) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR8_CC2_ADC12) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR1_CC3) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_None) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR15_CC1) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR15_CC2) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR15_CC3) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR15_CC4) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR15_TRGO) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR1_TRGO) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR3_CC1_ADC3) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR2_CC3_ADC3) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR8_CC1_ADC3) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR8_TRGO_ADC3) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR5_CC1_ADC3) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR5_CC3_ADC3) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR1_CC1_ADC3) || \
                                                     ((REGTRIG) == ADC_ExternalTrig_TMR8_CC3_ADC3))
/**
  * @}
  */

/** @defgroup ADC_data_align
  * @{
  */

#define ADC_DataAlign_Right                         ((uint32_t)0x00000000)
#define ADC_DataAlign_Left                          ((uint32_t)0x00000800)
#define IS_ADC_DATA_ALIGN(ALIGN)                    (((ALIGN) == ADC_DataAlign_Right) || \
                                                     ((ALIGN) == ADC_DataAlign_Left))
/**
  * @}
  */

/** @defgroup ADC_channels
  * @{
  */

#define ADC_Channel_0                               ((uint8_t)0x00)
#define ADC_Channel_1                               ((uint8_t)0x01)
#define ADC_Channel_2                               ((uint8_t)0x02)
#define ADC_Channel_3                               ((uint8_t)0x03)
#define ADC_Channel_4                               ((uint8_t)0x04)
#define ADC_Channel_5                               ((uint8_t)0x05)
#define ADC_Channel_6                               ((uint8_t)0x06)
#define ADC_Channel_7                               ((uint8_t)0x07)
#define ADC_Channel_8                               ((uint8_t)0x08)
#define ADC_Channel_9                               ((uint8_t)0x09)
#define ADC_Channel_10                              ((uint8_t)0x0A)
#define ADC_Channel_11                              ((uint8_t)0x0B)
#define ADC_Channel_12                              ((uint8_t)0x0C)
#define ADC_Channel_13                              ((uint8_t)0x0D)
#define ADC_Channel_14                              ((uint8_t)0x0E)
#define ADC_Channel_15                              ((uint8_t)0x0F)
#define ADC_Channel_16                              ((uint8_t)0x10)
#define ADC_Channel_17                              ((uint8_t)0x11)
                                                    
#define ADC_Channel_TempSensor                      ((uint8_t)ADC_Channel_16)
#define ADC_Channel_Vrefint                         ((uint8_t)ADC_Channel_17)
                                                    
#define IS_ADC_CHANNEL(CHANNEL)                     (((CHANNEL) == ADC_Channel_0)  || ((CHANNEL) == ADC_Channel_1) || \
                                                     ((CHANNEL) == ADC_Channel_2)  || ((CHANNEL) == ADC_Channel_3) || \
                                                     ((CHANNEL) == ADC_Channel_4)  || ((CHANNEL) == ADC_Channel_5) || \
                                                     ((CHANNEL) == ADC_Channel_6)  || ((CHANNEL) == ADC_Channel_7) || \
                                                     ((CHANNEL) == ADC_Channel_8)  || ((CHANNEL) == ADC_Channel_9) || \
                                                     ((CHANNEL) == ADC_Channel_10) || ((CHANNEL) == ADC_Channel_11) || \
                                                     ((CHANNEL) == ADC_Channel_12) || ((CHANNEL) == ADC_Channel_13) || \
                                                     ((CHANNEL) == ADC_Channel_14) || ((CHANNEL) == ADC_Channel_15) || \
                                                     ((CHANNEL) == ADC_Channel_16) || ((CHANNEL) == ADC_Channel_17))
/**
  * @}
  */

/** @defgroup ADC_sampling_time
  * @{
  */

#define ADC_SampleTime_1_5                          ((uint8_t)0x00)
#define ADC_SampleTime_7_5                          ((uint8_t)0x01)
#define ADC_SampleTime_13_5                         ((uint8_t)0x02)
#define ADC_SampleTime_28_5                         ((uint8_t)0x03)
#define ADC_SampleTime_41_5                         ((uint8_t)0x04)
#define ADC_SampleTime_55_5                         ((uint8_t)0x05)
#define ADC_SampleTime_71_5                         ((uint8_t)0x06)
#define ADC_SampleTime_239_5                        ((uint8_t)0x07)
#define IS_ADC_SAMPLE_TIME(TIME)                    (((TIME) == ADC_SampleTime_1_5) || \
                                                     ((TIME) == ADC_SampleTime_7_5) || \
                                                     ((TIME) == ADC_SampleTime_13_5) || \
                                                     ((TIME) == ADC_SampleTime_28_5) || \
                                                     ((TIME) == ADC_SampleTime_41_5) || \
                                                     ((TIME) == ADC_SampleTime_55_5) || \
                                                     ((TIME) == ADC_SampleTime_71_5) || \
                                                     ((TIME) == ADC_SampleTime_239_5))
/**
  * @}
  */

/** @defgroup ADC_external_trigger_sources_for_injected_channels_conversion
  * @{
  */

#define ADC_ExternalTrigInjec_TMR2_TRGO_ADC12             ((uint32_t)0x00002000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigInjec_TMR2_CC1_ADC12              ((uint32_t)0x00003000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigInjec_TMR3_CC4_ADC12              ((uint32_t)0x00004000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigInjec_TMR4_TRGO_ADC12             ((uint32_t)0x00005000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigInjec_Ext_INT15_TMR8_CC4_ADC12    ((uint32_t)0x00006000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigInjec_TMR8_CC1_ADC12              ((uint32_t)0x01006000) /*!< For ADC1 and ADC2 */
                                                    
#define ADC_ExternalTrigInjec_TMR1_TRGO                   ((uint32_t)0x00000000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrigInjec_TMR1_CC4                    ((uint32_t)0x00001000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrigInjec_None                        ((uint32_t)0x00007000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrigInjec_TMR15_CC1                   ((uint32_t)0x01000000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrigInjec_TMR15_CC2                   ((uint32_t)0x01001000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrigInjec_TMR15_CC3                   ((uint32_t)0x01002000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrigInjec_TMR15_CC4                   ((uint32_t)0x01003000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrigInjec_TMR15_TRGO                  ((uint32_t)0x01004000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrigInjec_TMR1_CC1                    ((uint32_t)0x01005000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrigInjec_TMR8_TRGO                   ((uint32_t)0x01007000) /*!< For ADC1, ADC2 and ADC3 */
                                                    
#define ADC_ExternalTrigInjec_TMR4_CC3_ADC3               ((uint32_t)0x00002000) /*!< For ADC3 only */
#define ADC_ExternalTrigInjec_TMR8_CC2_ADC3               ((uint32_t)0x00003000) /*!< For ADC3 only */
#define ADC_ExternalTrigInjec_TMR8_CC4_ADC3               ((uint32_t)0x00004000) /*!< For ADC3 only */
#define ADC_ExternalTrigInjec_TMR5_TRGO_ADC3              ((uint32_t)0x00005000) /*!< For ADC3 only */
#define ADC_ExternalTrigInjec_TMR5_CC4_ADC3               ((uint32_t)0x00006000) /*!< For ADC3 only */
#define ADC_ExternalTrigInjec_TMR1_CC2_ADC3               ((uint32_t)0x01006000) /*!< For ADC3 only */

#define IS_ADC_EXT_INJEC_TRIG(INJTRIG)              (((INJTRIG) == ADC_ExternalTrigInjec_TMR2_TRGO_ADC12) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR2_CC1_ADC12) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR3_CC4_ADC12) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR4_TRGO_ADC12) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_Ext_INT15_TMR8_CC4_ADC12) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR8_CC1_ADC12) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR1_TRGO) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR1_CC4) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_None) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR15_CC1) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR15_CC2) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR15_CC3) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR15_CC4) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR15_TRGO) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR1_CC1) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR8_TRGO) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR4_CC3_ADC3) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR8_CC2_ADC3) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR8_CC4_ADC3) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR5_TRGO_ADC3) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR5_CC4_ADC3) || \
                                                     ((INJTRIG) == ADC_ExternalTrigInjec_TMR1_CC2_ADC3))
                                        
/**
  * @}
  */

/** @defgroup ADC_injected_channel_selection
  * @{
  */

#define ADC_InjectedChannel_1                       ((uint8_t)0x14)
#define ADC_InjectedChannel_2                       ((uint8_t)0x18)
#define ADC_InjectedChannel_3                       ((uint8_t)0x1C)
#define ADC_InjectedChannel_4                       ((uint8_t)0x20)
#define IS_ADC_INJECTED_CHANNEL(CHANNEL)            (((CHANNEL) == ADC_InjectedChannel_1) || \
                                                     ((CHANNEL) == ADC_InjectedChannel_2) || \
                                                     ((CHANNEL) == ADC_InjectedChannel_3) || \
                                                     ((CHANNEL) == ADC_InjectedChannel_4))
/**
  * @}
  */

/** @defgroup ADC_analog_watchdog_selection
  * @{
  */

#define ADC_AnalogWDG_SingleRegEnable               ((uint32_t)0x00800200)
#define ADC_AnalogWDG_SingleInjecEnable             ((uint32_t)0x00400200)
#define ADC_AnalogWDG_SingleRegOrInjecEnable        ((uint32_t)0x00C00200)
#define ADC_AnalogWDG_AllRegEnable                  ((uint32_t)0x00800000)
#define ADC_AnalogWDG_AllInjecEnable                ((uint32_t)0x00400000)
#define ADC_AnalogWDG_AllRegAllInjecEnable          ((uint32_t)0x00C00000)
#define ADC_AnalogWDG_None                          ((uint32_t)0x00000000)

#define IS_ADC_ANALOG_WDG(WDG)                      (((WDG) == ADC_AnalogWDG_SingleRegEnable) || \
                                                     ((WDG) == ADC_AnalogWDG_SingleInjecEnable) || \
                                                     ((WDG) == ADC_AnalogWDG_SingleRegOrInjecEnable) || \
                                                     ((WDG) == ADC_AnalogWDG_AllRegEnable) || \
                                                     ((WDG) == ADC_AnalogWDG_AllInjecEnable) || \
                                                     ((WDG) == ADC_AnalogWDG_AllRegAllInjecEnable) || \
                                                     ((WDG) == ADC_AnalogWDG_None))
/**                                                 
  * @}
  */

/** @defgroup ADC_interrupts_definition
  * @{
  */

#define ADC_INT_EC                                  ((uint16_t)0x0220)
#define ADC_INT_AWD                                 ((uint16_t)0x0140)
#define ADC_INT_JEC                                 ((uint16_t)0x0480)

#define IS_ADC_INT(INT)                             ((((INT) & (uint16_t)0xF81F) == 0x00) && ((INT) != 0x00))

#define IS_ADC_GET_INT(INT)                         (((INT) == ADC_INT_EC) || ((INT) == ADC_INT_AWD) || \
                                                     ((INT) == ADC_INT_JEC))
/**
  * @}
  */

/** @defgroup ADC_flags_definition
  * @{
  */

#define ADC_FLAG_AWD                                ((uint8_t)0x01)
#define ADC_FLAG_EC                                 ((uint8_t)0x02)
#define ADC_FLAG_JEC                                ((uint8_t)0x04)
#define ADC_FLAG_JSTR                               ((uint8_t)0x08)
#define ADC_FLAG_RSTR                               ((uint8_t)0x10)
#define IS_ADC_CLEAR_FLAG(FLAG)                     ((((FLAG) & (uint8_t)0xE0) == 0x00) && ((FLAG) != 0x00))
#define IS_ADC_GET_FLAG(FLAG)                       (((FLAG) == ADC_FLAG_AWD) || ((FLAG) == ADC_FLAG_EC) || \
                                                     ((FLAG) == ADC_FLAG_JEC) || ((FLAG)== ADC_FLAG_JSTR) || \
                                                     ((FLAG) == ADC_FLAG_RSTR))
/**
  * @}
  */

/** @defgroup ADC_thresholds
  * @{
  */

#define IS_ADC_THRESHOLD(THRESHOLD)                 ((THRESHOLD) <= 0xFFF)

/**
  * @}
  */

/** @defgroup ADC_injected_offset
  * @{
  */

#define IS_ADC_OFFSET(OFFSET)                       ((OFFSET) <= 0xFFF)

/**
  * @}
  */

/** @defgroup ADC_injected_length
  * @{
  */

#define IS_ADC_INJECTED_LENGTH(LENGTH)              (((LENGTH) >= 0x1) && ((LENGTH) <= 0x4))

/**
  * @}
  */

/** @defgroup ADC_injected_rank
  * @{
  */

#define IS_ADC_INJECTED_RANK(RANK)                  (((RANK) >= 0x1) && ((RANK) <= 0x4))

/**
  * @}
  */


/** @defgroup ADC_regular_length
  * @{
  */

#define IS_ADC_REGULAR_LENGTH(LENGTH)               (((LENGTH) >= 0x1) && ((LENGTH) <= 0x10))
/**
  * @}
  */

/** @defgroup ADC_regular_rank
  * @{
  */

#define IS_ADC_REGULAR_RANK(RANK)                   (((RANK) >= 0x1) && ((RANK) <= 0x10))

/**
  * @}
  */

/** @defgroup ADC_regular_discontinuous_mode_number
  * @{
  */

#define IS_ADC_REGULAR_DISC_NUMBER(NUMBER)          (((NUMBER) >= 0x1) && ((NUMBER) <= 0x8))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup ADC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions
  * @{
  */

void ADC_Reset(ADC_Type* ADCx);
void ADC_Init(ADC_Type* ADCx, ADC_InitType* ADC_InitStruct);
void ADC_StructInit(ADC_InitType* ADC_InitStruct);
void ADC_Ctrl(ADC_Type* ADCx, FunctionalState NewState);
void ADC_DMACtrl(ADC_Type* ADCx, FunctionalState NewState);
void ADC_INTConfig(ADC_Type* ADCx, uint16_t ADC_INT, FunctionalState NewState);
void ADC_RstCalibration(ADC_Type* ADCx);
FlagStatus ADC_GetResetCalibrationStatus(ADC_Type* ADCx);
void ADC_StartCalibration(ADC_Type* ADCx);
FlagStatus ADC_GetCalibrationStatus(ADC_Type* ADCx);
void ADC_SoftwareStartConvCtrl(ADC_Type* ADCx, FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_Type* ADCx);
void ADC_DiscModeChannelCountConfig(ADC_Type* ADCx, uint8_t Number);
void ADC_DiscModeCtrl(ADC_Type* ADCx, FunctionalState NewState);
void ADC_RegularChannelConfig(ADC_Type* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_ExternalTrigConvCtrl(ADC_Type* ADCx, FunctionalState NewState);
uint16_t ADC_GetConversionValue(ADC_Type* ADCx);
uint32_t ADC_GetDualModeConversionValue(void);
void ADC_AutoInjectedConvCtrl(ADC_Type* ADCx, FunctionalState NewState);
void ADC_InjectedDiscModeCtrl(ADC_Type* ADCx, FunctionalState NewState);
void ADC_ExternalTrigInjectedConvConfig(ADC_Type* ADCx, uint32_t ADC_ExternalTrigInjecConv);
void ADC_ExternalTrigInjectedConvCtrl(ADC_Type* ADCx, FunctionalState NewState);
void ADC_SoftwareStartInjectedConvCtrl(ADC_Type* ADCx, FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartInjectedConvCtrlStatus(ADC_Type* ADCx);
void ADC_InjectedChannelConfig(ADC_Type* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_InjectedSequencerLengthConfig(ADC_Type* ADCx, uint8_t Length);
void ADC_SetInjectedOffset(ADC_Type* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset);
uint16_t ADC_GetInjectedConversionValue(ADC_Type* ADCx, uint8_t ADC_InjectedChannel);
void ADC_AnalogWDGCtrl(ADC_Type* ADCx, uint32_t ADC_AnalogWatchdog);
void ADC_AnalogWDGThresholdsConfig(ADC_Type* ADCx, uint16_t HighThreshold, uint16_t LowThreshold);
void ADC_AnalogWDGSingleChannelConfig(ADC_Type* ADCx, uint8_t ADC_Channel);
void ADC_TempSensorVrefintCtrl(FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_Type* ADCx, uint8_t ADC_FLAG);
void ADC_ClearFlag(ADC_Type* ADCx, uint8_t ADC_FLAG);
ITStatus ADC_GetINTStatus(ADC_Type* ADCx, uint16_t ADC_INT);
void ADC_ClearINTPendingBit(ADC_Type* ADCx, uint16_t ADC_INT);

#ifdef __cplusplus
}
#endif

#endif /*__AT32F4xx_ADC_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


