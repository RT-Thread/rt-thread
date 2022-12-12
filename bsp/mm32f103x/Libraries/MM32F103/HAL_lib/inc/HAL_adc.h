/**
******************************************************************************
* @file    HAL_adc.h
* @author  AE Team
* @version V1.1.0
* @date    28/08/2019
* @brief   This file contains all the functions prototypes for the ADC firmware
*          library.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2019 MindMotion</center></h2>
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_ADC_H
#define __HAL_ADC_H

/* Includes ------------------------------------------------------------------*/
#include "HAL_device.h"

/** @addtogroup StdPeriph_Driver
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

/*
typedef struct
{
uint32_t ADC_Mode;
FunctionalState ADC_ScanConvMode;
FunctionalState ADC_ContinuousConvMode;
uint32_t ADC_ExternalTrigConv;
uint32_t ADC_DataAlign;
uint8_t ADC_NbrOfChannel;
}ADC_InitTypeDef;
*/
typedef struct
{
    uint32_t ADC_Resolution;
    uint32_t ADC_PRESCARE;
    uint32_t ADC_Mode;
    FunctionalState ADC_ContinuousConvMode;
    uint32_t ADC_ExternalTrigConv;
    uint32_t ADC_DataAlign;
} ADC_InitTypeDef;
/**
* @}
*/

/** @defgroup ADC_Exported_Constants
* @{
*/

#define IS_ADC_ALL_PERIPH(PERIPH) (((*(uint32_t*)&(PERIPH)) == ADC1_BASE) || \
                                   ((*(uint32_t*)&(PERIPH)) == ADC2_BASE))

#define IS_ADC_DMA_PERIPH(PERIPH) (((*(uint32_t*)&(PERIPH)) == ADC1_BASE) || \
                                   ((*(uint32_t*)&(PERIPH)) == ADC2_BASE))

/** @defgroup ADC_Resolution
* @{
*/
#define ADC_Resolution_12b                         ((uint32_t)0x00000000)
#define ADC_Resolution_11b                         ((uint32_t)0x00000080)
#define ADC_Resolution_10b                         ((uint32_t)0x00000100)
#define ADC_Resolution_9b                          ((uint32_t)0x00000180)
#define ADC_Resolution_8b                          ((uint32_t)0x00000200)
/**
* @brief  for ADC1, ADC2
*/

#define ADC_PCLK2_PRESCARE_2                       ((uint32_t)0x00000000)
#define ADC_PCLK2_PRESCARE_4                       ((uint32_t)0x00000010)
#define ADC_PCLK2_PRESCARE_6                       ((uint32_t)0x00000020)
#define ADC_PCLK2_PRESCARE_8                       ((uint32_t)0x00000030)
#define ADC_PCLK2_PRESCARE_10                      ((uint32_t)0x00000040)
#define ADC_PCLK2_PRESCARE_12                      ((uint32_t)0x00000050)
#define ADC_PCLK2_PRESCARE_14                      ((uint32_t)0x00000060)
#define ADC_PCLK2_PRESCARE_16                      ((uint32_t)0x00000070)


/** @defgroup ADC_dual_mode
* @{
*/

#define ADC_Mode_Single                   	((uint32_t)0x00000000)
#define ADC_Mode_Single_Period              ((uint32_t)0x00000200)
#define ADC_Mode_Continuous_Scan            ((uint32_t)0x00000400)


#define IS_ADC_MODE(MODE) (((MODE) == ADC_Mode_Single) || \
                           ((MODE) == ADC_Mode_Single_Period) || \
                           ((MODE) == ADC_Mode_Continuous_Scan))
/**
* @}
*/



/** @defgroup ADC_extrenal_trigger_sources_for_regular_channels_conversion
* @{
*/

/**
* @brief  for ADC1
*/

#define ADC_ExternalTrigConv_T1_CC1         	((uint32_t)0x00000000)
#define ADC_ExternalTrigConv_T1_CC2   			  ((uint32_t)0x00000010)
#define ADC_ExternalTrigConv_T1_CC3     		  ((uint32_t)0x00000020)
#define ADC_ExternalTrigConv_T2_CC2  			  ((uint32_t)0x00000030)
#define ADC_ExternalTrigConv_T3_TRGO      		((uint32_t)0x00000040)
#define ADC_ExternalTrigConv_T4_CC4      		((uint32_t)0x00000050)
#define ADC_ExternalTrigConv_T3_CC1      		((uint32_t)0x00000060)
#define ADC_ExternalTrigConv_EXTI_11     	  ((uint32_t)0x00000070)

/**
* @brief  for ADC2
*/

#define ADC_ExternalTrigConv_T1_TRGO          ((uint32_t)0x00000000)
#define ADC_ExternalTrigConv_T1_CC4           ((uint32_t)0x00000010)
#define ADC_ExternalTrigConv_T2_TRGO          ((uint32_t)0x00000020)
#define ADC_ExternalTrigConv_T2_CC1           ((uint32_t)0x00000030)
#define ADC_ExternalTrigConv_T3_CC4           ((uint32_t)0x00000040)
#define ADC_ExternalTrigConv_T4_TRGO          ((uint32_t)0x00000050)
#define ADC_ExternalTrigConv_T3_CC1           ((uint32_t)0x00000060)
#define ADC_ExternalTrigConv_EXTI_15          ((uint32_t)0x00000070)



#define IS_ADC_EXT_TRIG(REGTRIG) (((REGTRIG) == ADC_ExternalTrigConv_T1_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T1_CC2) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T1_CC3) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T2_CC2) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T3_TRGO) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T4_CC4) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T3_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_EXTI_11) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T1_TRGO) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T1_CC4) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T2_TRGO) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T2_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T3_CC4) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T4_TRGO) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T3_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_EXTI_15))
/**
* @}
*/

/** @defgroup ADC_data_align
* @{
*/

#define ADC_DataAlign_Right                        ((uint32_t)0x00000000)
#define ADC_DataAlign_Left                         ((uint32_t)0x00000800)
#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DataAlign_Right) || \
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
#define ADC_Channel_All															((uint8_t)0x0f)


#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_Channel_0) || ((CHANNEL) == ADC_Channel_1) || \
                                 ((CHANNEL) == ADC_Channel_2) || ((CHANNEL) == ADC_Channel_3) || \
                                 ((CHANNEL) == ADC_Channel_4) || ((CHANNEL) == ADC_Channel_5) || \
                                 ((CHANNEL) == ADC_Channel_6) || ((CHANNEL) == ADC_Channel_7) || \
                                 ((CHANNEL) == ADC_Channel_8) || ((CHANNEL) == ADC_Channel_All))
/**
* @}
*/

#define  ADC_SMPR_SMP                      ((uint32_t)0x00000007)        /*!< SMP[2:0] bits (Sampling time selection) */
#define  ADC_SMPR_SMP_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  ADC_SMPR_SMP_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  ADC_SMPR_SMP_2                    ((uint32_t)0x00000004)        /*!< Bit 2 */
/** @defgroup ADC_sampling_times
* @{
*/

#define ADC_SampleTime_1_5Cycles                     ((uint32_t)0x00000000)
#define ADC_SampleTime_7_5Cycles                     ((uint32_t)0x00000001)
#define ADC_SampleTime_13_5Cycles                    ((uint32_t)0x00000002)
#define ADC_SampleTime_28_5Cycles                    ((uint32_t)0x00000003)
#define ADC_SampleTime_41_5Cycles                    ((uint32_t)0x00000004)
#define ADC_SampleTime_55_5Cycles                    ((uint32_t)0x00000005)
#define ADC_SampleTime_71_5Cycles                    ((uint32_t)0x00000006)
#define ADC_SampleTime_239_5Cycles                   ((uint32_t)0x00000007)

/** @defgroup ADC_injected_channel_selection
* @{
*/

#define ADC_InjectedChannel_0                       ((uint8_t)0x18)
#define ADC_InjectedChannel_1                       ((uint8_t)0x1C)
#define ADC_InjectedChannel_2                       ((uint8_t)0x20)
#define ADC_InjectedChannel_3                       ((uint8_t)0x24)
#define ADC_InjectedChannel_4                       ((uint8_t)0x28)
#define ADC_InjectedChannel_5                       ((uint8_t)0x2C)
#define ADC_InjectedChannel_6                       ((uint8_t)0x30)
#define ADC_InjectedChannel_7                       ((uint8_t)0x34)
#define ADC_InjectedChannel_8                       ((uint8_t)0x38)
#define IS_ADC_INJECTED_CHANNEL(CHANNEL) (((CHANNEL) == ADC_InjectedChannel_1) || \
        ((CHANNEL) == ADC_InjectedChannel_2) || \
        ((CHANNEL) == ADC_InjectedChannel_3) || \
        ((CHANNEL) == ADC_InjectedChannel_4) || \
        ((CHANNEL) == ADC_InjectedChannel_5) || \
        ((CHANNEL) == ADC_InjectedChannel_6) || \
        ((CHANNEL) == ADC_InjectedChannel_7) || \
        ((CHANNEL) == ADC_InjectedChannel_8))
/**
* @}
*/

/** @defgroup ADC_analog_watchdog_selection
* @{
*/

#define ADC_AnalogWatchdog_SingleRegEnable         ((uint32_t)0x00000002)
#define ADC_AnalogWatchdog_None                    ((uint32_t)0x00000000)

#define IS_ADC_ANALOG_WATCHDOG(WATCHDOG) (((WATCHDOG) == ADC_AnalogWatchdog_SingleRegEnable) || \
        ((WATCHDOG) == ADC_AnalogWatchdog_None))
/**
* @}
*/

/** @defgroup ADC_interrupts_definition
* @{
*/

#define ADC_IT_EOC                                 ((uint16_t)0x0001)
#define ADC_IT_AWD                                 ((uint16_t)0x0002)

#define IS_ADC_IT(IT) ((((IT) & (uint16_t)0xFFFC) == 0x00) && ((IT) != 0x00))

#define IS_ADC_GET_IT(IT) (((IT) == ADC_IT_EOC) || ((IT) == ADC_IT_AWD))

/**
* @}
*/

/** @defgroup ADC_flags_definition
* @{
*/

#define ADC_FLAG_AWD                               ((uint8_t)0x02)
#define ADC_FLAG_EOC                               ((uint8_t)0x01)
#define IS_ADC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint8_t)0xF0) == 0x00) && ((FLAG) != 0x00))
#define IS_ADC_GET_FLAG(FLAG) (((FLAG) == ADC_FLAG_AWD) || ((FLAG) == ADC_FLAG_EOC))

/**
* @}
*/

/** @defgroup ADC_thresholds
* @{
*/

#define IS_ADC_THRESHOLD(THRESHOLD) ((THRESHOLD) <= 0xFFF)

/**
* @}
*/

/** @defgroup ADC_injected_offset
* @{
*/

#define IS_ADC_OFFSET(OFFSET) ((OFFSET) <= 0xFFF)

/**
* @}
*/

/** @defgroup ADC_injected_length
* @{
*/

#define IS_ADC_INJECTED_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x4))

/**
* @}
*/

/** @defgroup ADC_injected_rank
* @{
*/

#define IS_ADC_INJECTED_RANK(RANK) (((RANK) >= 0x1) && ((RANK) <= 0x4))

/**
* @}
*/


/** @defgroup ADC_regular_length
* @{
*/

#define IS_ADC_REGULAR_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x10))
/**
* @}
*/

/** @defgroup ADC_regular_rank
* @{
*/

#define IS_ADC_REGULAR_RANK(RANK) (((RANK) >= 0x1) && ((RANK) <= 0x10))

/**
* @}
*/

/** @defgroup ADC_regular_discontinuous_mode_number
* @{
*/

#define IS_ADC_REGULAR_DISC_NUMBER(NUMBER) (((NUMBER) >= 0x1) && ((NUMBER) <= 0x8))

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

void ADC_DeInit(ADC_TypeDef* ADCx);
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState);
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx);
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_ExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);

void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog);
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold, uint16_t LowThreshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel);
void ADC_TempSensorVrefintCmd(FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT);

#endif /*__HAL_ADC_H */

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/
