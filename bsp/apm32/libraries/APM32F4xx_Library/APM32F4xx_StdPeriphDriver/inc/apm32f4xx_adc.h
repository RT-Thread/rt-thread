/*!
 * @file        apm32f4xx_adc.h
 *
 * @brief       This file contains all the functions prototypes for the ADC firmware library
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32F4XX_ADC_H
#define __APM32F4XX_ADC_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup ADC_Driver
  @{
*/

/** @defgroup ADC_Enumerations
  @{
*/

/**
 * @brief ADC Common mode
 */
typedef enum
{
    /* All the ADCs independent */
    ADC_MODE_INDEPENDENT                  = (uint8_t)0x00, /*!< Independent mode */

    /* ADC1 and ADC2 working together but ADC3 is independent */
    ADC_MODE_DUAL_REGSIMULT_INJECSIMULT = (uint8_t)0x01, /*!< regular simultaneous + injected simultaneous */
    ADC_MODE_DUAL_REGSIMULT_ALTERTRIG   = (uint8_t)0x02, /*!< regular simultaneous + alternate trigger */
    ADC_MODE_DUAL_INJECSIMULT           = (uint8_t)0x05, /*!< Injected simultaneous mode only */
    ADC_MODE_DUAL_REGSIMULT             = (uint8_t)0x06, /*!< Regular simultaneous mode only */
    ADC_MODE_DUAL_INTERL                = (uint8_t)0x07, /*!< Interleaved mode only */
    ADC_MODE_DUAL_ALTERTRIG             = (uint8_t)0x09, /*!< Alternate trigger mode only */

    /* ADC1, ADC2 and ADC3 working together */
    ADC_MODE_TRIPLE_REGSIMULT_INJECSIMULT = (uint8_t)0x11, /*!< regular simultaneous + injected simultaneous */
    ADC_MODE_TRIPLE_REGSIMULT_ALTERTRIG   = (uint8_t)0x12, /*!< regular simultaneous + alternate trigger */
    ADC_MODE_TRIPLE_INJECSIMULT           = (uint8_t)0x15, /*!< Injected simultaneous mode only */
    ADC_MODE_TRIPLE_REGSIMULT             = (uint8_t)0x16, /*!< Regular simultaneous mode only */
    ADC_MODE_TRIPLE_INTERL                = (uint8_t)0x17, /*!< Interleaved mode only */
    ADC_MODE_TRIPLE_ALTERTRIG             = (uint8_t)0x19  /*!< Alternate trigger mode only */
} ADC_MODE_T;

/**
 * @brief ADC Prescaler
 */
typedef enum
{
    ADC_PRESCALER_DIV2, /*!< PCLK2 2 divided frequency */
    ADC_PRESCALER_DIV4, /*!< PCLK2 4 divided frequency */
    ADC_PRESCALER_DIV6, /*!< PCLK2 6 divided frequency */
    ADC_PRESCALER_DIV8  /*!< PCLK2 8 divided frequency */
} ADC_PRESCALER_T;

/**
 * @brief ADC Direct memory access mode for multi mode
 */
typedef enum
{
    ADC_ACCESS_MODE_DISABLED, /*!< DMA mode disabled */
    ADC_ACCESS_MODE_1,        /*!< DMA mode 1 enabled (2/3 half-words one by one - 1 then 2 then 3) */
    ADC_ACCESS_MODE_2,        /*!< DMA mode 2 enabled (2/3 half-words by pairs - 2&1 then 1&3 then 3&2) */
    ADC_ACCESS_MODE_3         /*!< DMA mode 3 enabled (2/3 bytes by pairs - 2&1 then 1&3 then 3&2) */
} ADC_ACCESS_MODE_T;

/**
 * @brief ADC Delay between 2 sampling phases
 */
typedef enum
{
    ADC_TWO_SAMPLING_5CYCLES,  /*!< 5*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_6CYCLES,  /*!< 6*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_7CYCLES,  /*!< 7*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_8CYCLES,  /*!< 8*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_9CYCLES,  /*!< 9*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_10CYCLES, /*!< 10*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_11CYCLES, /*!< 11*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_12CYCLES, /*!< 12*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_13CYCLES, /*!< 13*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_14CYCLES, /*!< 14*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_15CYCLES, /*!< 15*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_16CYCLES, /*!< 16*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_17CYCLES, /*!< 17*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_18CYCLES, /*!< 18*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_19CYCLES, /*!< 19*Tadcclk delay between 2 sampling phases */
    ADC_TWO_SAMPLING_20CYCLES  /*!< 20*Tadcclk delay between 2 sampling phases */
} ADC_TWO_SAMPLING_T;

/**
 * @brief ADC_resolution
 */
typedef enum
{
    ADC_RESOLUTION_12BIT, /*!< ADC Resolution is 12 bits */
    ADC_RESOLUTION_10BIT, /*!< ADC Resolution is 10 bits */
    ADC_RESOLUTION_8BIT,  /*!< ADC Resolution is 8 bits */
    ADC_RESOLUTION_6BIT   /*!< ADC Resolution is 6 bits */
} ADC_RESOLUTION_T;

/**
 * @brief ADC External trigger edge for regular channels conversion
 */
typedef enum
{
    ADC_EXT_TRIG_EDGE_NONE,             /*!<Trigger detection is disabled */
    ADC_EXT_TRIG_EDGE_RISING,           /*!<Trigger detection on rising edge */
    ADC_EXT_TRIG_EDGE_FALLING,          /*!<Trigger detection on falling edge */
    ADC_EXT_TRIG_EDGE_RISING_FALLING,   /*!<Trigger detection on rising edge and falling edge */
} ADC_EXT_TRIG_EDGE_T;

/**
 * @brief ADC External event trigger select for regular group
 */
typedef enum
{
    ADC_EXT_TRIG_CONV_TMR1_CC1,     /*!<Timer1 capture compare1 selected */
    ADC_EXT_TRIG_CONV_TMR1_CC2,     /*!<Timer1 capture compare2 selected */
    ADC_EXT_TRIG_CONV_TMR1_CC3,     /*!<Timer1 capture compare3 selected */
    ADC_EXT_TRIG_CONV_TMR2_CC2,     /*!<Timer2 capture compare2 selected */
    ADC_EXT_TRIG_CONV_TMR2_CC3,     /*!<Timer2 capture compare3 selected */
    ADC_EXT_TRIG_CONV_TMR2_CC4,     /*!<Timer2 capture compare4 selected */
    ADC_EXT_TRIG_CONV_TMR2_TRGO,    /*!<Timer2 TRGO event selected */
    ADC_EXT_TRIG_CONV_TMR3_CC1,     /*!<Timer3 capture compare1 selected */
    ADC_EXT_TRIG_CONV_TMR3_TRGO,    /*!<Timer3 TRGO event selected */
    ADC_EXT_TRIG_CONV_TMR4_CC4,     /*!<Timer4 capture compare4 selected */
    ADC_EXT_TRIG_CONV_TMR5_CC1,     /*!<Timer5 capture compare1 selected */
    ADC_EXT_TRIG_CONV_TMR5_CC2,     /*!<Timer5 capture compare2 selected */
    ADC_EXT_TRIG_CONV_TMR5_CC3,     /*!<Timer5 capture compare3 selected */
    ADC_EXT_TRIG_CONV_TMR8_CC1,     /*!<Timer8 capture compare1 selected */
    ADC_EXT_TRIG_CONV_TMR8_TRGO,    /*!<Timer8 TRGO event selected */
    ADC_EXT_TRIG_CONV_EINT_11       /*!<External interrupt line 11 event selected */
} ADC_EXT_TRIG_CONV_T;

/**
 * @brief ADC Data align
 */
typedef enum
{
    ADC_DATA_ALIGN_RIGHT,   /*!<Right alignment */
    ADC_DATA_ALIGN_LEFT     /*!<Left alignment */
} ADC_DATA_ALIGN_T;

/**
 * @brief ADC Channel number
 */
typedef enum
{
    ADC_CHANNEL_0,  /*!< ADC Channel 0 */
    ADC_CHANNEL_1,  /*!< ADC Channel 1 */
    ADC_CHANNEL_2,  /*!< ADC Channel 2 */
    ADC_CHANNEL_3,  /*!< ADC Channel 3 */
    ADC_CHANNEL_4,  /*!< ADC Channel 4 */
    ADC_CHANNEL_5,  /*!< ADC Channel 5 */
    ADC_CHANNEL_6,  /*!< ADC Channel 6 */
    ADC_CHANNEL_7,  /*!< ADC Channel 7 */
    ADC_CHANNEL_8,  /*!< ADC Channel 8 */
    ADC_CHANNEL_9,  /*!< ADC Channel 9 */
    ADC_CHANNEL_10, /*!< ADC Channel 10 */
    ADC_CHANNEL_11, /*!< ADC Channel 11 */
    ADC_CHANNEL_12, /*!< ADC Channel 12 */
    ADC_CHANNEL_13, /*!< ADC Channel 13 */
    ADC_CHANNEL_14, /*!< ADC Channel 14 */
    ADC_CHANNEL_15, /*!< ADC Channel 15 */
    ADC_CHANNEL_16, /*!< ADC Channel 16 */
    ADC_CHANNEL_17, /*!< ADC Channel 17 */
    ADC_CHANNEL_18, /*!< ADC Channel 18 */
} ADC_CHANNEL_T;

/**
 * @brief ADC_sampling_times
 */
typedef enum
{
    ADC_SAMPLETIME_3CYCLES,     /*!< Config the channel as 3 sample cyscles */
    ADC_SAMPLETIME_15CYCLES,    /*!< Config the channel as 15 sample cyscles */
    ADC_SAMPLETIME_28CYCLES,    /*!< Config the channel as 28 sample cyscles */
    ADC_SAMPLETIME_56CYCLES,    /*!< Config the channel as 56 sample cyscles */
    ADC_SAMPLETIME_84CYCLES,    /*!< Config the channel as 84 sample cyscles */
    ADC_SAMPLETIME_112CYCLES,   /*!< Config the channel as 112 sample cyscles */
    ADC_SAMPLETIME_144CYCLES,   /*!< Config the channel as 144 sample cyscles */
    ADC_SAMPLETIME_480CYCLES    /*!< Config the channel as 480 sample cyscles */
} ADC_SAMPLETIME_T;

/**
 * @brief ADC external trigger edge for injected channels conversion
 */
typedef enum
{
    ADC_EXT_TRIG_INJEC_EDGE_NONE,           /*!< Disable the external trigger for injected channels */
    ADC_EXT_TRIG_INJEC_EDGE_RISING,         /*!< Trigger detection on rising edge */
    ADC_EXT_TRIG_INJEC_EDGE_FALLING,        /*!< Trigger detection on rising edge */
    ADC_EXT_TRIG_INJEC_EDGE_RISING_FALLING  /*!< Trigger detection on rising edge and falling edge */
} ADC_EXT_TRIG_INJEC_EDGE_T;

/**
 * @brief ADC extrenal trigger sources for injected channels conversion
 */
typedef enum
{
    ADC_EXT_TRIG_INJEC_CONV_TMR1_CC4,   /*!< Timer1 capture compare 4 selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR1_TRGO,  /*!< Timer1 TRGO event selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR2_CC1,   /*!< Timer2 capture compare 1 selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR2_TRGO,  /*!< Timer2 TRGO event selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR3_CC2,   /*!< Timer3 capture compare 2 selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR3_CC4,   /*!< Timer3 capture compare 4 selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR4_CC1,   /*!< Timer4 capture compare 1 selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR4_CC2,   /*!< Timer4 capture compare 2 selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR4_CC3,   /*!< Timer4 capture compare 3 selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR4_TRGO,  /*!< Timer4 TRGO event selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR5_CC4,   /*!< Timer5 capture compare 4 selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR5_TRGO,  /*!< Timer5 TRGO event selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR8_CC2,   /*!< Timer8 capture compare 2 selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR8_CC3,   /*!< Timer8 capture compare 3 selected */
    ADC_EXT_TRIG_INJEC_CONV_TMR8_CC4,   /*!< Timer8 capture compare 4 selected */
    ADC_EXT_TRIG_INJEC_CONV_EINT15      /*!< External interrupt line 15 event selected */
} ADC_EXT_TRIG_INJEC_CONV_T;

/**
 * @brief ADC injected channel selection
 */
typedef enum
{
    ADC_INJEC_CHANNEL_1 = (uint8_t)0x01,    /*!< Channel injected conversion Data */
    ADC_INJEC_CHANNEL_2 = (uint8_t)0x02,    /*!< Channe2 injected conversion Data */
    ADC_INJEC_CHANNEL_3 = (uint8_t)0x03,    /*!< Channe3 injected conversion Data */
    ADC_INJEC_CHANNEL_4 = (uint8_t)0x04     /*!< Channe4 injected conversion Data */
} ADC_INJEC_CHANNEL_T;

/**
 * @brief ADC analog watchdog selection
 */
typedef enum
{
    ADC_ANALOG_WATCHDOG_SINGLE_INJEC      = (uint8_t)0x11, /*!< Analog watchdog on a single injected channel */
    ADC_ANALOG_WATCHDOG_SINGLE_REG        = (uint8_t)0x12, /*!< Analog watchdog on a single regular channel */
    ADC_ANALOG_WATCHDOG_SINGLE_REG_INJEC  = (uint8_t)0x13, /*!< Analog watchdog on a single regular or injected channel */
    ADC_ANALOG_WATCHDOG_ALL_INJEC         = (uint8_t)0x01, /*!< Analog watchdog on  all injected channel */
    ADC_ANALOG_WATCHDOG_ALL_REG           = (uint8_t)0x02, /*!< Analog watchdog on  all regular channel */
    ADC_ANALOG_WATCHDOG_ALL_REG_ALL_INJEC = (uint8_t)0x03, /*!< Analog watchdog on all regular and injected channels */
    ADC_ANALOG_WATCHDOG_NONE              = (uint8_t)0x00  /*!< No Analog watchdog */
} ADC_ANALOG_WATCHDOG_T;

/**
 * @brief ADC interrupts
 */
typedef enum
{
    ADC_INT_EOC         = BIT5,     /*!< End of conversion interrupt mask */
    ADC_INT_AWD         = BIT6,     /*!< Analog watchdog interrupt mask */
    ADC_INT_INJEOC      = BIT7,     /*!< End of injected conversion interrupt mask */
    ADC_INT_OVR         = BIT26     /*!< Overrun interrupt enable */
} ADC_INT_T;

/**
 * @brief ADC interrupt flags
 */
typedef enum
{
    ADC_INT_FLAG_AWD    = 0x0501,   /*!< Analog watchdog interrupt flag */
    ADC_INT_FLAG_EOC    = 0x0602,   /*!< End of conversion interrupt flag */
    ADC_INT_FLAG_INJEOC = 0x0704,   /*!< End of injected conversion interrupt flag */
    ADC_INT_FLAG_OVR    = 0x1A20    /*!< Overrun interrupt flag */
} ADC_INT_FLAG_T;

/**
 * @brief ADC status flags
 */
typedef enum
{
    ADC_FLAG_AWD        = BIT0, /*!< Analog watchdog flag */
    ADC_FLAG_EOC        = BIT1, /*!< End of conversion flag */
    ADC_FLAG_INJEOC     = BIT2, /*!< End of injected group conversion flag */
    ADC_FLAG_INJCS      = BIT3, /*!< Start of injected group conversion flag */
    ADC_FLAG_REGCS      = BIT4, /*!< Start of regular group conversion flag */
    ADC_FLAG_OVR        = BIT5  /*!< Overrun flag */
} ADC_FLAG_T;

/**@} end of group ADC_Enumerations*/

/** @defgroup ADC_Structure
  @{
*/

/**
 * @brief ADC configuration Mode
 */
typedef struct
{
    ADC_RESOLUTION_T    resolution; /*!< Configures the ADC resolution dual mode.
                                         This parameter can be a value of @ref ADC_RESOLUTION_T */
    uint8_t             scanConvMode;       /*!< This value can be ENABLE or DISABLE */
    uint8_t             continuousConvMode; /*!< This value can be ENABLE or DISABLE */
    ADC_EXT_TRIG_EDGE_T extTrigEdge;        /*!< Enable the External Trigger for Regular Channels */
    ADC_EXT_TRIG_CONV_T extTrigConv;        /*!< Select the External Trigger Event to Start the
                                                 Regular Group Conversion */
    ADC_DATA_ALIGN_T    dataAlign;          /*!< Data Alignment Mode Configure */
    uint8_t             nbrOfChannel; /*!< regular channel sequence length can be from 1 to 16 */
} ADC_Config_T;

/**
 * @brief ADC Common Init structure definition
 */
typedef struct
{
    ADC_MODE_T         mode;        /*!< ADC mode selection */
    ADC_PRESCALER_T    prescaler;   /*!< ADC Prescaler */
    ADC_ACCESS_MODE_T  accessMode;  /*!< DMA Mode */
    ADC_TWO_SAMPLING_T twoSampling; /*!< Delay Between 2 Sampling Phases */
} ADC_CommonConfig_T;

/**@} end of group ADC_Structure*/

/** @defgroup ADC_Functions
  @{
*/

/* ADC Reset */
void ADC_Reset(void);

/* Configuration */
void ADC_Config(ADC_T* adc, ADC_Config_T* adcConfig);
void ADC_ConfigStructInit(ADC_Config_T* adcConfig);
void ADC_CommonConfig(ADC_CommonConfig_T* adcCommonConfig);
void ADC_CommonConfigStructInit(ADC_CommonConfig_T* adcCommonConfig);
void ADC_Enable(ADC_T* adc);
void ADC_Disable(ADC_T* adc);

/* Analog Watchdog */
void ADC_EnableAnalogWatchdog(ADC_T* adc, ADC_ANALOG_WATCHDOG_T analogWatchdog);
void ADC_DisableAnalogWatchdog(ADC_T* adc);
void ADC_ConfigAnalogWatchdogThresholds(ADC_T* adc, uint16_t highThreshold, uint16_t lowThreshold);
void ADC_ConfigAnalogWatchdogSingleChannel(ADC_T* adc, uint8_t channel);

/* Temperature Sensor, Vrefint and VBAT management **/
void ADC_EnableTempSensorVrefint(void);
void ADC_DisableTempSensorVrefint(void);
void ADC_EnableVbat(void);
void ADC_DisableVbat(void);

/* Regular Channels Configuration */
void ADC_ConfigRegularChannel(ADC_T* adc, uint8_t channel,
                              uint8_t rank, uint8_t sampleTime);
void ADC_SoftwareStartConv(ADC_T* adc);
uint8_t ADC_ReadSoftwareStartConvStatus(ADC_T* adc);

void ADC_EnableEOCOnEachChannel(ADC_T* adc);
void ADC_DisableEOCOnEachChannel(ADC_T* adc);

/* Continuous Mode */
void ADC_EnableContinuousMode(ADC_T* adc);
void ADC_DisableContinuousMode(ADC_T* adc);

/* Discontinuous Mode */
void ADC_ConfigDiscMode(ADC_T* adc, uint8_t number);
void ADC_EnableDiscMode(ADC_T* adc);
void ADC_DisableDiscMode(ADC_T* adc);

uint16_t ADC_ReadConversionValue(ADC_T* adc);
uint32_t ADC_ReadMultiValue(void);

/* Regular Channels DMA */
void ADC_EnableDMA(ADC_T* adc);
void ADC_DisableDMA(ADC_T* adc);

void ADC_EnableDMARequest(ADC_T* adc);
void ADC_DisableDMARequest(ADC_T* adc);

void ADC_EnableMultiModeDMARequest(void);
void ADC_DisableMultiModeDMARequest(void);

/* Injected channels Configuration functions */
void ADC_ConfigInjectedChannel(ADC_T* adc, uint8_t channel, uint8_t rank,
                               uint8_t sampleTime);
void ADC_ConfigInjectedSequencerLength(ADC_T* adc, uint8_t length);
void ADC_ConfigInjectedOffset(ADC_T* adc, ADC_INJEC_CHANNEL_T channel, uint16_t offset);
void ADC_ConfigExternalTrigInjectedConv(ADC_T* adc, ADC_EXT_TRIG_INJEC_CONV_T extTrigInjecConv);
void ADC_ConfigExternalTrigInjectedConvEdge(ADC_T* adc, ADC_EXT_TRIG_INJEC_EDGE_T extTrigInjecConvEdge);
void ADC_EnableSoftwareStartInjectedConv(ADC_T* adc);
uint8_t ADC_ReadSoftwareStartInjectedConvStatus(ADC_T* adc);
void ADC_EnableAutoInjectedConv(ADC_T* adc);
void ADC_DisableAutoInjectedConv(ADC_T* adc);
void ADC_EnableInjectedDiscMode(ADC_T* adc);
void ADC_DisableInjectedDiscMode(ADC_T* adc);
uint16_t ADC_ReadInjectedConversionValue(ADC_T* adc, ADC_INJEC_CHANNEL_T channel);

/* Interrupts and flags */
void ADC_EnableInterrupt(ADC_T* adc, uint32_t interrupt);
void ADC_DisableInterrupt(ADC_T* adc, uint32_t interrupt);
uint8_t ADC_ReadStatusFlag(ADC_T* adc,  ADC_FLAG_T flag);
void ADC_ClearStatusFlag(ADC_T* adc, uint32_t flag);
uint16_t ADC_ReadIntFlag(ADC_T* adc, ADC_INT_FLAG_T flag);
void ADC_ClearIntFlag(ADC_T* adc, uint32_t flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_ADC_H */

/**@} end of group ADC_Functions */
/**@} end of group ADC_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
