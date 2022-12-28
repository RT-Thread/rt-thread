/*!
 * @file        apm32f10x_adc.h
 *
 * @brief       This file contains all the functions prototypes for the ADC firmware library
 *
 * @version     V1.0.4
 *
 * @date        2022-12-01
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
#ifndef __APM32F10X_ADC_H
#define __APM32F10X_ADC_H

/* Includes */
#include "apm32f10x.h"
#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup ADC_Driver ADC Driver
  @{
*/


/** @defgroup ADC_Macros
  @{
*/

/* ADC_IJD Offset */
#define INJDATA_OFFSET          ((uint8_t)0x28)

/* ADC_RDG register address */
#define RDG_ADDRESS             ((uint32_t)0x4001244C)

/* INJSEQ register config */
#define INJSEQ_SET_INJSEQC      ((uint32_t)0x0000001F)
#define INJSEQ_SET_INJSEQLEN    ((uint32_t)0x00300000)

/* SMPTIM register SET */
#define SMPCYCCFG_SET_SMPTIM1   ((uint32_t)0x00000007)
#define SMPCYCCFG_SET_SMPTIM2   ((uint32_t)0x00000007)

/* REGSEQ register SET  */
#define REGSEQC_SET_REGSEQ3     ((uint32_t)0x0000001F)
#define REGSEQC_SET_REGSEQ2     ((uint32_t)0x0000001F)
#define REGSEQC_SET_REGSEQ1     ((uint32_t)0x0000001F)

/**@} end of group ADC_Macros*/

/** @defgroup ADC_Enumerations
  @{
*/

/**
 * @brief    ADC configuration Mode
 */
typedef enum
{
    ADC_MODE_INDEPENDENT              = ((uint32_t)0x00000000), /*!< Independent mode */
    ADC_MODE_REG_INJEC_SIMULT         = ((uint32_t)0x00010000), /*!< Combined regular simultaneous and injected simultaneous mode */
    ADC_MODE_REG_SIMULT_ALTER_TRIG    = ((uint32_t)0x00020000), /*!< Combined regular simultaneous and alternate trigger mode */
    ADC_MODE_INJEC_SIMULT_FAST_TNTERL = ((uint32_t)0x00030000), /*!< Combined injected simultaneous and fast interleaved mode */
    ADC_MODE_INJEC_SIMULT_SLOW_INTERL = ((uint32_t)0x00040000), /*!< Combined injected simultaneous and slow interleaved mode */
    ADC_MODE_INJEC_SIMULT             = ((uint32_t)0x00050000), /*!< Injected simultaneous mode */
    ADC_MODE_REG_SIMULT               = ((uint32_t)0x00060000), /*!< Regular simultaneous mode */
    ADC_MODE_FAST_INTERL              = ((uint32_t)0x00070000), /*!< Fast interleaved mode */
    ADC_MODE_SLOW_INTERL              = ((uint32_t)0x00080000), /*!< Slow interleaved mode */
    ADC_MODE_ALTER_TRIG               = ((uint32_t)0x00090000)  /*!< Alternate trigger mode */
} ADC_MODE_T;

/**
 * @brief    ADC external trigger sources for regular channels conversion enumeration
 */
typedef enum
{
    ADC_EXT_TRIG_CONV_TMR1_CC1        = ((uint32_t)0x00000000),
    ADC_EXT_TRIG_CONV_TMR1_CC2        = ((uint32_t)0x00020000),
    ADC_EXT_TRIG_CONV_TMR2_CC2        = ((uint32_t)0x00060000),
    ADC_EXT_TRIG_CONV_TMR3_TRGO       = ((uint32_t)0x00080000),
    ADC_EXT_TRIG_CONV_TMR4_CC4        = ((uint32_t)0x000A0000),
    ADC_EXT_TRIG_CONV_EINT11_T8_TRGO  = ((uint32_t)0x000C0000),
    ADC_EXT_TRIG_CONV_TMR1_CC3        = ((uint32_t)0x00040000),
    ADC_EXT_TRIG_CONV_None            = ((uint32_t)0x000E0000),

    ADC_EXT_TRIG_CONV_TMR3_CC1        = ((uint32_t)0x00000000),
    ADC_EXT_TRIG_CONV_TMR2_CC3        = ((uint32_t)0x00020000),
    ADC_EXT_TRIG_CONV_TMR8_CC1        = ((uint32_t)0x00060000),
    ADC_EXT_TRIG_CONV_TMR8_TRGO       = ((uint32_t)0x00080000),
    ADC_EXT_TRIG_CONV_TMR5_CC1        = ((uint32_t)0x000A0000),
    ADC_EXT_TRIG_CONV_TMR5_CC3        = ((uint32_t)0x000C0000)
} ADC_EXT_TRIG_CONV_T;

/**
 * @brief    ADC Data Align
 */
typedef enum
{
    ADC_DATA_ALIGN_RIGHT = 0x00000000,
    ADC_DATA_ALIGN_LEFT  = 0x00000800
} ADC_DATA_ALIGN_T;

/**
 * @brief    ADC Channels
 */
typedef enum
{
    ADC_CHANNEL_0           = ((uint8_t)0x00),
    ADC_CHANNEL_1           = ((uint8_t)0x01),
    ADC_CHANNEL_2           = ((uint8_t)0x02),
    ADC_CHANNEL_3           = ((uint8_t)0x03),
    ADC_CHANNEL_4           = ((uint8_t)0x04),
    ADC_CHANNEL_5           = ((uint8_t)0x05),
    ADC_CHANNEL_6           = ((uint8_t)0x06),
    ADC_CHANNEL_7           = ((uint8_t)0x07),
    ADC_CHANNEL_8           = ((uint8_t)0x08),
    ADC_CHANNEL_9           = ((uint8_t)0x09),
    ADC_CHANNEL_10          = ((uint8_t)0x0A),
    ADC_CHANNEL_11          = ((uint8_t)0x0B),
    ADC_CHANNEL_12          = ((uint8_t)0x0C),
    ADC_CHANNEL_13          = ((uint8_t)0x0D),
    ADC_CHANNEL_14          = ((uint8_t)0x0E),
    ADC_CHANNEL_15          = ((uint8_t)0x0F),
    ADC_CHANNEL_16          = ((uint8_t)0x10),
    ADC_CHANNEL_TEMP_SENSOR = ((uint8_t)0x10),
    ADC_CHANNEL_17          = ((uint8_t)0x11),
    ADC_CHANNEL_V_REFINT    = ((uint8_t)0x11)
} ADC_CHANNEL_T;

/**
 * @brief    ADC Sampling Time
 */
typedef enum
{
    ADC_SAMPLETIME_1CYCLES5   = ((uint8_t)0x00),
    ADC_SAMPLETIME_7CYCLES5   = ((uint8_t)0x01),
    ADC_SAMPLETIME_13CYCLES5  = ((uint8_t)0x02),
    ADC_SAMPLETIME_28CYCLES5  = ((uint8_t)0x03),
    ADC_SAMPLETIME_41CYCLES5  = ((uint8_t)0x04),
    ADC_SAMPLETIME_55CYCLES5  = ((uint8_t)0x05),
    ADC_SAMPLETIME_71CYCLES5  = ((uint8_t)0x06),
    ADC_SAMPLETIME_239CYCLES5 = ((uint8_t)0x07)
} ADC_SAMPLETIME_T;

/**
 * @brief    ADC external trigger sources for injected channels conversion
 */
typedef enum
{
    /* for ADC1 and ADC2 */
    ADC_EXT_TRIG_INJEC_CONV_TMR2_TRGO       = ((uint8_t)0x02),
    ADC_EXT_TRIG_INJEC_CONV_TMR2_CC1        = ((uint8_t)0x03),
    ADC_EXT_TRIG_INJEC_CONV_TMR3_CC4        = ((uint8_t)0x04),
    ADC_EXT_TRIG_INJEC_CONV_TMR4_TRGO       = ((uint8_t)0x05),
    ADC_EXT_TRIG_INJEC_CONV_EINT15_T8_CC4   = ((uint8_t)0x06),

    /* for ADC1, ADC2 and ADC3 */
    ADC_EXT_TRIG_INJEC_CONV_TMR1_TRGO       = ((uint8_t)0x00),
    ADC_EXT_TRIG_INJEC_CONV_TMR1_CC4        = ((uint8_t)0x01),
    ADC_EXT_TRIG_INJEC_CONV_NONE            = ((uint8_t)0x07),

    /* for ADC3 only */
    ADC_EXT_TRIG_INJEC_CONV_TMR4_CC3        = ((uint8_t)0x02),
    ADC_EXT_TRIG_INJEC_CONV_TMR8_CC2        = ((uint8_t)0x03),
    ADC_EXT_TRIG_INJEC_CONV_TMR8_CC4        = ((uint8_t)0x04),
    ADC_EXT_TRIG_INJEC_CONV_TMR5_TRGO       = ((uint8_t)0x05),
    ADC_EXT_TRIG_INJEC_CONV_TMR5_CC4        = ((uint8_t)0x06)
} ADC_EXT_TRIG_INJEC_CONV_T;

/**
 * @brief    ADC Injected channels
 */
typedef enum
{
    ADC_INJEC_CHANNEL_1 = ((uint8_t)0x14),
    ADC_INJEC_CHANNEL_2 = ((uint8_t)0x18),
    ADC_INJEC_CHANNEL_3 = ((uint8_t)0x1C),
    ADC_INJEC_CHANNEL_4 = ((uint8_t)0x20)
} ADC_INJEC_CHANNEL_T;

/**
 * @brief    ADC Analog Watchdog Selection
 */
typedef enum
{
    ADC_ANALOG_WATCHDOG_SINGLE_REG        = ((uint32_t)0x00800200),
    ADC_ANALOG_WATCHDOG_SINGLE_INJEC      = ((uint32_t)0x00400200),
    ADC_ANALOG_WATCHDOG_SINGLE_REG_INJEC  = ((uint32_t)0x00C00200),
    ADC_ANALOG_WATCHDOG_ALL_REG           = ((uint32_t)0x00800000),
    ADC_ANALOG_WATCHDOG_ALL_INJEC         = ((uint32_t)0x00400000),
    ADC_ANALOG_WATCHDOG_ALL_REG_ALL_INJEC = ((uint32_t)0x00C00000),
    ADC_ANALOG_WATCHDOG_NONE              = ((uint32_t)0x00000000)
} ADC_ANALOG_WATCHDOG_T;

/**
 * @brief    ADC Interrupt definition
 */
typedef enum
{
    ADC_INT_AWD    = ((uint16_t)0x0140), /*!<  Analog Watchdog interrupt */
    ADC_INT_EOC    = ((uint16_t)0x0220), /*!<  End Of Conversion interrupt */
    ADC_INT_INJEOC = ((uint16_t)0x0480)  /*!<  Injected Channel End Of Conversion interrupt */
} ADC_INT_T;

/**
 * @brief    ADC Flag
 */
typedef enum
{
    ADC_FLAG_AWD    = ((uint8_t)0x01), /*!<  Analog Watchdog event occur flag */
    ADC_FLAG_EOC    = ((uint8_t)0x02), /*!<  End Of Conversion flag */
    ADC_FLAG_INJEOC = ((uint8_t)0x04), /*!<  Injected Channel End Of Conversion flag */
    ADC_FLAG_INJCS  = ((uint8_t)0x08), /*!<  Injected Channel Conversion Start flag */
    ADC_FLAG_REGCS  = ((uint8_t)0x10)  /*!<  Regular Channel Conversion Start flag */
} ADC_FLAG_T;

/**@} end of group ADC_Enumerations*/

/** @defgroup ADC_Structures Structures
  @{
*/

/**
 * @brief    ADC Config structure definition
 */
typedef struct
{
    ADC_MODE_T          mode;
    uint8_t             scanConvMode;       /*!< This parameter can be ENABLE or DISABLE. */
    uint8_t             continuosConvMode;  /*!< This parameter can be ENABLE or DISABLE. */
    ADC_EXT_TRIG_CONV_T externalTrigConv;
    ADC_DATA_ALIGN_T    dataAlign;
    uint8_t             nbrOfChannel;       /*!< This parameter must range from 1 to 16. */
} ADC_Config_T;

/**@} end of group ADC_Structures*/


/** @defgroup ADC_Functions Functions
  @{
*/

/* ADC reset and common configuration */
void ADC_Reset(ADC_T* adc);
void ADC_Config(ADC_T* adc, ADC_Config_T* adcConfig);
void ADC_ConfigStructInit(ADC_Config_T* adcConfig);
void ADC_ConfigRegularChannel(ADC_T* adc, uint8_t channel, uint8_t rank, uint8_t sampleTime);
void ADC_Enable(ADC_T* adc);
void ADC_Disable(ADC_T* adc);

/* ADC for DMA */
void ADC_EnableDMA(ADC_T* adc);
void ADC_DisableDMA(ADC_T* adc);

/* ADC Calibration */
void ADC_ResetCalibration(ADC_T* adc);
uint8_t ADC_ReadResetCalibrationStatus(ADC_T* adc);
void ADC_StartCalibration(ADC_T* adc);
uint8_t ADC_ReadCalibrationStartFlag(ADC_T* adc);

/* ADC software start conversion */
void ADC_EnableSoftwareStartConv(ADC_T* adc);
void ADC_DisableSoftwareStartConv(ADC_T* adc);
uint8_t ADC_ReadSoftwareStartConvStatus(ADC_T* adc);

/* ADC Discontinuous mode */
void ADC_ConfigDiscMode(ADC_T* adc, uint8_t number);
void ADC_EnableDiscMode(ADC_T* adc);
void ADC_DisableDiscMode(ADC_T* adc);

/* ADC External trigger conversion */
void ADC_EnableExternalTrigConv(ADC_T* adc);
void ADC_DisableExternalTrigConv(ADC_T* adc);

/* ADC Conversion result */
uint16_t ADC_ReadConversionValue(ADC_T* adc);
uint32_t ADC_ReadDualModeConversionValue(ADC_T* adc);

/* ADC Automatic injected group */
void ADC_EnableAutoInjectedConv(ADC_T* adc);
void ADC_DisableAutoInjectedConv(ADC_T* adc);
void ADC_EnableInjectedDiscMode(ADC_T* adc);
void ADC_DisableInjectedDiscMode(ADC_T* adc);

/* ADC External trigger for injected channels conversion */
void ADC_ConfigExternalTrigInjectedConv(ADC_T* adc, ADC_EXT_TRIG_INJEC_CONV_T extTrigInjecConv);
void ADC_EnableExternalTrigInjectedConv(ADC_T* adc);
void ADC_DisableExternalTrigInjectedConv(ADC_T* adc);

/* ADC Start of the injected channels conversion */
void ADC_EnableSoftwareStartInjectedConv(ADC_T* adc);
void ADC_DisableSoftwareStartInjectedConv(ADC_T* adc);
uint8_t ADC_ReadSoftwareStartInjectedConvStatus(ADC_T* adc);

/* ADC injected channel */
void ADC_ConfigInjectedChannel(ADC_T* adc, uint8_t channel, uint8_t rank, uint8_t sampleTime);
void ADC_ConfigInjectedSequencerLength(ADC_T* adc, uint8_t length);
void ADC_ConfigInjectedOffset(ADC_T* adc, ADC_INJEC_CHANNEL_T channel, uint16_t offSet);
uint16_t ADC_ReadInjectedConversionValue(ADC_T* adc, ADC_INJEC_CHANNEL_T channel);

/* ADC analog watchdog */
void ADC_EnableAnalogWatchdog(ADC_T* adc, uint32_t analogWatchdog);
void ADC_DisableAnalogWatchdog(ADC_T* adc);
void ADC_ConfigAnalogWatchdogThresholds(ADC_T* adc, uint16_t highThreshold, uint16_t lowThreshold);
void ADC_ConfigAnalogWatchdogSingleChannel(ADC_T* adc, uint8_t channel);

/* ADC temperature sensor */
void ADC_EnableTempSensorVrefint(ADC_T* adc);
void ADC_DisableTempSensorVrefint(ADC_T* adc);

/* Interrupt and flag */
void ADC_EnableInterrupt(ADC_T* adc, uint16_t interrupt);
void ADC_DisableInterrupt(ADC_T* adc, uint16_t interrupt);
uint8_t ADC_ReadStatusFlag(ADC_T* adc, ADC_FLAG_T flag);
void ADC_ClearStatusFlag(ADC_T* adc, uint8_t flag);
uint8_t ADC_ReadIntFlag(ADC_T* adc, ADC_INT_T flag);
void ADC_ClearIntFlag(ADC_T* adc, uint16_t flag);



#ifdef __cplusplus
}

/**@} end of group ADC_Functions*/
/**@} end of group ADC_Driver*/
/**@} end of group APM32F10x_StdPeriphDriver */
#endif

#endif /* __APM32F10X_ADC_H */
