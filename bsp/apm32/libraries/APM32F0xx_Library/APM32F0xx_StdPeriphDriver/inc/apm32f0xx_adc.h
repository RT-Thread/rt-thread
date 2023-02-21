/*!
 * @file        apm32f0xx_adc.h
 *
 * @brief       This file contains all the functions prototypes for the ADC firmware library
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32F0XX_ADC_H
#define __APM32F0XX_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup ADC_Driver
  @{
*/

/** @defgroup ADC_Macros Macros
  @{
*/

/* ADC_channels */
#define  ADC_Channel_TempSensor   ((uint32_t)ADC_CHANNEL_16)  /*!< ADC TempSensor Channel definition */
#define  ADC_Channel_Vrefint      ((uint32_t)ADC_CHANNEL_17)  /*!< ADC Vrefint Channel definition */
#define  ADC_Channel_Vbat         ((uint32_t)ADC_CHANNEL_18)  /*!< ADC Vbat Channel definition */

/* ADC CFG mask */
#define CFG1_CLEAR_MASK           ((uint32_t)0xFFFFD203)

/* Calibration time out */
#define CALIBRATION_TIMEOUT       ((uint32_t)0x0000F000)

/**@} end of group ADC_Macros */

/** @defgroup ADC_Enumerations Enumerations
  @{
*/

/**
 * @brief   ADC conversion mode
 */
typedef enum
{
    ADC_CONVERSION_SINGLE        = ((uint8_t)0),  /*!< Single conversion mode */
    ADC_CONVERSION_CONTINUOUS    = ((uint8_t)1),  /*!< Continuous conversion mode */
} ADC_CONVERSION_T;

/**
 * @brief    ADC Jitter
 */
typedef enum
{
    ADC_JITTER_PCLKDIV2   = ((uint8_t)0x01),         /*!< ADC clocked by PCLK div2 */
    ADC_JITTER_PCLKDIV4   = ((uint8_t)0x02),         /*!< ADC clocked by PCLK div4 */
} ADC_JITTER_T;

/**
 * @brief    ADC clock mode
 */
typedef enum
{
    ADC_CLOCK_MODE_ASYNCLK      = ((uint8_t)0x00),   /*!< ADC Asynchronous clock mode */
    ADC_CLOCK_MODE_SYNCLKDIV2   = ((uint8_t)0x01),   /*!< Synchronous clock mode divided by 2 */
    ADC_CLOCK_MODE_SYNCLKDIV4   = ((uint8_t)0x02),   /*!< Synchronous clock mode divided by 4 */
} ADC_CLOCK_MODE_T;

/**
 * @brief    ADC data resolution
 */
typedef enum
{
    ADC_RESOLUTION_12B   = ((uint8_t)0x00),     /*!< ADC Resolution is 12 bits */
    ADC_RESOLUTION_10B   = ((uint8_t)0x01),     /*!< ADC Resolution is 10 bits */
    ADC_RESOLUTION_8B    = ((uint8_t)0x02),     /*!< ADC Resolution is 8 bits */
    ADC_RESOLUTION_6B    = ((uint8_t)0x03),     /*!< ADC Resolution is 6 bits */
} ADC_RESOLUTION_T;

/**
 * @brief   ADC data alignment
 */
typedef enum
{
    ADC_DATA_ALIGN_RIGHT    = ((uint8_t)0), /*!< Data alignment right */
    ADC_DATA_ALIGN_LEFT     = ((uint8_t)1), /*!< Data alignment left */
} ADC_DATA_ALIGN_T;

/**
 * @brief   ADC scan sequence direction
 */
typedef enum
{
    ADC_SCAN_DIR_UPWARD     = ((uint8_t)0),     /*!< from CHSEL0 to CHSEL17 */
    ADC_SCAN_DIR_BACKWARD   = ((uint8_t)1),     /*!< from CHSEL17 to CHSEL0 */
} ADC_SCAN_DIR_T;

/**
 * @brief   ADC DMA Mode
 */
typedef enum
{
    ADC_DMA_MODE_ONESHOUT   = ((uint8_t)0),     /*!< ADC DMA Mode Select one shot */
    ADC_DMA_MODE_CIRCULAR   = ((uint8_t)1),     /*!< ADC DMA Mode Select circular */
} ADC_DMA_MODE_T;

/**
 * @brief   ADC external conversion trigger edge selectio
 */
typedef enum
{
    ADC_EXT_TRIG_EDGE_NONE     = ((uint8_t)0x00),   /*!< ADC External Trigger Conversion mode disabled */
    ADC_EXT_TRIG_EDGE_RISING   = ((uint8_t)0x01),   /*!< ADC External Trigger Conversion mode rising edge */
    ADC_EXT_TRIG_EDGE_FALLING  = ((uint8_t)0x02),   /*!< ADC External Trigger Conversion mode falling edge */
    ADC_EXT_TRIG_EDGE_ALL      = ((uint8_t)0x03),   /*!< ADC External Trigger Conversion mode rising and falling edges */
} ADC_EXT_TRIG_EDGE_T;

/**
 * @brief   ADC external trigger sources selection
 */
typedef enum
{
    ADC_EXT_TRIG_CONV_TRG0   = ((uint8_t)0x00),     /*!< ADC External Trigger Conversion timer1 TRG0 */
    ADC_EXT_TRIG_CONV_TRG1   = ((uint8_t)0x01),     /*!< ADC External Trigger Conversion timer1 CC4 */
    ADC_EXT_TRIG_CONV_TRG2   = ((uint8_t)0x02),     /*!< ADC External Trigger Conversion timer2 TRGO */
    ADC_EXT_TRIG_CONV_TRG3   = ((uint8_t)0x03),     /*!< ADC External Trigger Conversion timer3 TRG0 */
    ADC_EXT_TRIG_CONV_TRG4   = ((uint8_t)0x04),     /*!< ADC External Trigger Conversion timer15 TRG0 */
} ADC_EXT_TRIG_CONV_T;

/**
 * @brief   ADC analog watchdog channel selection
 */
typedef enum
{
    ADC_ANALG_WDT_CHANNEL_0    = ((uint8_t)0x00),   /*!< AWD Channel 0 */
    ADC_ANALG_WDT_CHANNEL_1    = ((uint8_t)0x01),   /*!< AWD Channel 1 */
    ADC_ANALG_WDT_CHANNEL_2    = ((uint8_t)0x02),   /*!< AWD Channel 2 */
    ADC_ANALG_WDT_CHANNEL_3    = ((uint8_t)0x03),   /*!< AWD Channel 3 */
    ADC_ANALG_WDT_CHANNEL_4    = ((uint8_t)0x04),   /*!< AWD Channel 4 */
    ADC_ANALG_WDT_CHANNEL_5    = ((uint8_t)0x05),   /*!< AWD Channel 5 */
    ADC_ANALG_WDT_CHANNEL_6    = ((uint8_t)0x06),   /*!< AWD Channel 6 */
    ADC_ANALG_WDT_CHANNEL_7    = ((uint8_t)0x07),   /*!< AWD Channel 7 */
    ADC_ANALG_WDT_CHANNEL_8    = ((uint8_t)0x08),   /*!< AWD Channel 8 */
    ADC_ANALG_WDT_CHANNEL_9    = ((uint8_t)0x09),   /*!< AWD Channel 9 */
    ADC_ANALG_WDT_CHANNEL_10   = ((uint8_t)0x0A),   /*!< AWD Channel 10 */
    ADC_ANALG_WDT_CHANNEL_11   = ((uint8_t)0x0B),   /*!< AWD Channel 11 */
    ADC_ANALG_WDT_CHANNEL_12   = ((uint8_t)0x0C),   /*!< AWD Channel 12 */
    ADC_ANALG_WDT_CHANNEL_13   = ((uint8_t)0x0D),   /*!< AWD Channel 13 */
    ADC_ANALG_WDT_CHANNEL_14   = ((uint8_t)0x0E),   /*!< AWD Channel 14 */
    ADC_ANALG_WDT_CHANNEL_15   = ((uint8_t)0x0F),   /*!< AWD Channel 15 */
    ADC_ANALG_WDT_CHANNEL_16   = ((uint8_t)0x10),   /*!< AWD Channel 16 */
    ADC_ANALG_WDT_CHANNEL_17   = ((uint8_t)0x11),   /*!< AWD Channel 17 */
    ADC_ANALG_WDT_CHANNEL_18   = ((uint8_t)0x12),   /*!< AWD Channel 18 */
} ADC_ANALG_WDT_CHANNEL_T;

/**
 * @brief   ADC sampling times
 */
typedef enum
{
    ADC_SAMPLE_TIME_1_5     = ((uint8_t)0x00),  /*!< 1.5   ADC clock cycles */
    ADC_SAMPLE_TIME_7_5     = ((uint8_t)0x01),  /*!< 7.5   ADC clock cycles */
    ADC_SAMPLE_TIME_13_5    = ((uint8_t)0x02),  /*!< 13.5  ADC clock cycles */
    ADC_SAMPLE_TIME_28_5    = ((uint8_t)0x03),  /*!< 28.5  ADC clock cycles */
    ADC_SAMPLE_TIME_41_5    = ((uint8_t)0x04),  /*!< 41.5  ADC clock cycles */
    ADC_SAMPLE_TIME_55_5    = ((uint8_t)0x05),  /*!< 55.5  ADC clock cycles */
    ADC_SAMPLE_TIME_71_5    = ((uint8_t)0x06),  /*!< 71.5  ADC clock cycles */
    ADC_SAMPLE_TIME_239_5   = ((uint8_t)0x07),  /*!< 239.5 ADC clock cycles */
} ADC_SAMPLE_TIME_T;

/**
 * @brief   ADC channel selection
 */
typedef enum
{
    ADC_CHANNEL_0    = ((uint32_t)0x00000001),  /*!< ADC Channel 0 */
    ADC_CHANNEL_1    = ((uint32_t)0x00000002),  /*!< ADC Channel 1 */
    ADC_CHANNEL_2    = ((uint32_t)0x00000004),  /*!< ADC Channel 2 */
    ADC_CHANNEL_3    = ((uint32_t)0x00000008),  /*!< ADC Channel 3 */
    ADC_CHANNEL_4    = ((uint32_t)0x00000010),  /*!< ADC Channel 4 */
    ADC_CHANNEL_5    = ((uint32_t)0x00000020),  /*!< ADC Channel 5 */
    ADC_CHANNEL_6    = ((uint32_t)0x00000040),  /*!< ADC Channel 6 */
    ADC_CHANNEL_7    = ((uint32_t)0x00000080),  /*!< ADC Channel 7 */
    ADC_CHANNEL_8    = ((uint32_t)0x00000100),  /*!< ADC Channel 8 */
    ADC_CHANNEL_9    = ((uint32_t)0x00000200),  /*!< ADC Channel 9 */
    ADC_CHANNEL_10   = ((uint32_t)0x00000400),  /*!< ADC Channel 10 */
    ADC_CHANNEL_11   = ((uint32_t)0x00000800),  /*!< ADC Channel 11 */
    ADC_CHANNEL_12   = ((uint32_t)0x00001000),  /*!< ADC Channel 12 */
    ADC_CHANNEL_13   = ((uint32_t)0x00002000),  /*!< ADC Channel 13 */
    ADC_CHANNEL_14   = ((uint32_t)0x00004000),  /*!< ADC Channel 14 */
    ADC_CHANNEL_15   = ((uint32_t)0x00008000),  /*!< ADC Channel 15 */
    ADC_CHANNEL_16   = ((uint32_t)0x00010000),  /*!< ADC Channel 16 */
    ADC_CHANNEL_17   = ((uint32_t)0x00020000),  /*!< ADC Channel 17 */
    ADC_CHANNEL_18   = ((uint32_t)0x00040000),  /*!< ADC Channel 18 (Not for APM32F030 devices) */
} ADC_CHANNEL_T;

/**
 * @brief   ADC interrupts definition
 */
typedef enum
{
    ADC_INT_ADRDY    = ((uint8_t)0x01), /*!< ADC ready interrupt */
    ADC_INT_CSMP     = ((uint8_t)0x02), /*!< End of sampling interrupt */
    ADC_INT_CC       = ((uint8_t)0x04), /*!< End of conversion interrupt */
    ADC_INT_CS       = ((uint8_t)0x08), /*!< End of sequence interrupt */
    ADC_INT_OVR      = ((uint8_t)0x10), /*!< ADC overrun interrupt */
    ADC_INT_AWD      = ((uint8_t)0x80), /*!< Analog watchdog interrupt */
} ADC_INT_T;

/**
 * @brief   ADC Interrupt flag
 */
typedef enum
{
    ADC_INT_FLAG_ADRDY    = ((uint8_t)0x01),    /*!< ADC ready interrupt flag */
    ADC_INT_FLAG_CSMP     = ((uint8_t)0x02),    /*!< End of sampling interrupt flag */
    ADC_INT_FLAG_CC       = ((uint8_t)0x04),    /*!< End of conversion interrupt flag */
    ADC_INT_FLAG_CS       = ((uint8_t)0x08),    /*!< End of sequence interrupt flag */
    ADC_INT_FLAG_OVR      = ((uint8_t)0x10),    /*!< ADC overrun interrupt flag */
    ADC_INT_FLAG_AWD      = ((uint8_t)0x80),    /*!< Analog watchdog interrupt flag */
} ADC_INT_FLAG_T;

/**
 * @brief   ADC flag
 */
typedef enum
{
    ADC_FLAG_ADCON   = ((uint32_t)0x01000001),  /*!< ADC enable flag */
    ADC_FLAG_ADCOFF  = ((uint32_t)0x01000002),  /*!< ADC disable flag */
    ADC_FLAG_ADCSTA  = ((uint32_t)0x01000004),  /*!< ADC start conversion flag */
    ADC_FLAG_ADCSTOP = ((uint32_t)0x01000010),  /*!< ADC stop conversion flag */
    ADC_FLAG_ADCCAL  = ((int)     0x81000000),  /*!< ADC calibration flag */
    ADC_FLAG_ADRDY   = ((uint8_t)0x01),         /*!< ADC ready flag */
    ADC_FLAG_CSMP    = ((uint8_t)0x02),         /*!< End of sampling flag */
    ADC_FLAG_CC      = ((uint8_t)0x04),         /*!< End of conversion flag */
    ADC_FLAG_CS      = ((uint8_t)0x08),         /*!< End of sequence flag */
    ADC_FLAG_OVR     = ((uint8_t)0x10),         /*!< ADC overrun flag */
    ADC_FLAG_AWD     = ((uint8_t)0x80),         /*!< Analog watchdog flag */
} ADC_FLAG_T;

/**@} end of group ADC_Enumerations */

/** @defgroup ADC_Structures Structures
  @{
*/

/**
 * @brief   ADC Config struct definition
 */
typedef struct
{
    ADC_RESOLUTION_T    resolution;     /*!< Specifies the ADC data resolution */
    ADC_DATA_ALIGN_T    dataAlign;      /*!< Specifies the data alignment mode */
    ADC_SCAN_DIR_T      scanDir;        /*!< Specifies the scan mode */
    ADC_CONVERSION_T    convMode;       /*!< Specifies the conversion mode */
    ADC_EXT_TRIG_CONV_T extTrigConv;    /*!< Specifies the external trigger sources */
    ADC_EXT_TRIG_EDGE_T extTrigEdge;    /*!< Specifies the external conversion trigger edge */
} ADC_Config_T;

/**@} end of group ADC_Structures */

/** @defgroup ADC_Variables Variables
  @{
  */

/**@} end of group ADC_Variables */

/** @defgroup ADC_Functions Functions
  @{
*/

/* ADC reset and configuration */
void ADC_Reset(void);
void ADC_Config(ADC_Config_T* adcConfig);
void ADC_ConfigStructInit(ADC_Config_T* adcConfig);
void ADC_Enable(void);
void ADC_Disable(void);
void ADC_EnableAutoPowerOff(void);
void ADC_DisableAutoPowerOff(void);
void ADC_EnableWaitMode(void);
void ADC_DisableWaitMode(void);
void ADC_ConfigChannel(uint32_t channel, uint8_t sampleTime);
void ADC_EnableContinuousMode(void);
void ADC_DisableContinuousMode(void);
void ADC_EnableDiscMode(void);
void ADC_DisableDiscMode(void);
void ADC_EnableOverrunMode(void);
void ADC_DisableOverrunMode(void);
void ADC_StopConversion(void);
void ADC_StartConversion(void);
void ADC_DMARequestMode(ADC_DMA_MODE_T DMARequestMode);

/* ADC clock and jitter */
void ADC_ClockMode(ADC_CLOCK_MODE_T clockMode);
void ADC_EnableJitter(ADC_JITTER_T jitter);
void ADC_DisableJitter(ADC_JITTER_T jitter);

/* ADC analog watchdog */
void ADC_EnableAnalogWatchdog(void);
void ADC_DisableAnalogWatchdog(void);
void ADC_AnalogWatchdogLowThreshold(uint16_t lowThreshold);
void ADC_AnalogWatchdogHighThreshold(uint16_t highThreshold);
void ADC_AnalogWatchdogSingleChannel(uint32_t channel);
void ADC_EnableAnalogWatchdogSingleChannel(void);
void ADC_DisableAnalogWatchdogSingleChannel(void);

/* ADC common configuration */
void ADC_EnableTempSensor(void);
void ADC_DisableTempSensor(void);
void ADC_EnableVrefint(void);
void ADC_DisableVrefint(void);
void ADC_EnableVbat(void);  /*!< Not for APM32F030 devices */
void ADC_DisableVbat(void); /*!< Not for APM32F030 devices */

/* Read data  */
uint32_t ADC_ReadCalibrationFactor(void);
uint16_t ADC_ReadConversionValue(void);

/* DMA */
void ADC_EnableDMA(void);
void ADC_DisableDMA(void);

/* Interrupt and flag */
void ADC_EnableInterrupt(uint8_t interrupt);
void ADC_DisableInterrupt(uint8_t interrupt);
uint8_t ADC_ReadStatusFlag(ADC_FLAG_T flag);
void ADC_ClearStatusFlag(uint32_t flag);
uint8_t ADC_ReadIntFlag(ADC_INT_FLAG_T flag);
void ADC_ClearIntFlag(uint32_t flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_ADC_H */

/**@} end of group ADC_Functions */
/**@} end of group ADC_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
