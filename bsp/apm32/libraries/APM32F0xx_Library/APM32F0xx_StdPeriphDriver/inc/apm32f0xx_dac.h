/*!
 * @file        apm32f0xx_dac.h
 *
 * @brief       This file contains all the functions prototypes for the DAC firmware library
 *
 * @note        It's only for APM32F051,APM32F072,APM32F091 devices
 *
 * @version     V1.0.3
 *
 * @date        2022-02-21
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
#ifndef __APM32F0XX_DAC_H
#define __APM32F0XX_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup DAC_Driver DAC Driver
  @{
*/

/** @defgroup DAC_Macros Macros
  @{
*/

/* Macros description */
#define CTRL_CLEAR_MASK         ((uint32_t)0x00000FFE)  /*!< DAC CTRL register clear mask */
#define DUAL_SWTRIG_SET         ((uint32_t)0x00000003)  /*!< Enable software trigger for DAC's Channel1 and Channel2 */
#define DUAL_SWTRIG_RESET       ((uint32_t)0xFFFFFFFC)  /*!< Disable software trigger for DAC's Channel1 and Channel2 */
#define DH12RCH1_OFFSET         ((uint32_t)0x00000008)  /*!< DAC channel1 data  holding register address offset */
#define DH12RCH2_OFFSET         ((uint32_t)0x00000014)  /*!< DAC channel2 data holding register address offset */
#define DH12RD_OFFSET           ((uint32_t)0x00000020)  /*!< DAC dual channel data holding register address offset */
#define DATOUT_OFFSET           ((uint32_t)0x0000002C)  /*!< DAC data output register address offset */

/**@} end of group DAC_Macros*/

/** @defgroup DAC_Enumerations Enumerations
  @{
*/

/**
 * @brief    DAC_Trigger
 */
typedef enum
{
    DAC_TRIGGER_NONE     = ((uint32_t)0x00000000),      /*!< None DAC Trigger */
    DAC_TRIGGER_T2_TRGO  = ((uint32_t)0x00000024),      /*!< Timer 2 TRGO event */
    DAC_TRIGGER_T3_TRGO  = ((uint32_t)0x0000000C),      /*!< Timer 3 TRGO event */
    DAC_TRIGGER_T6_TRGO  = ((uint32_t)0x00000004),      /*!< Timer 6 TRGO event */
    DAC_TRIGGER_T7_TRGO  = ((uint32_t)0x00000014),      /*!< Timer 7 TRGO event, applicable only for APM32F072 devices */
    DAC_TRIGGER_T15_TRGO = ((uint32_t)0x0000001C),      /*!< Timer 15 TRGO event */
    DAC_TRIGGER_EINT_IT9 = ((uint32_t)0x00000034),      /*!< EINT line9 */
    DAC_TRIGGER_SOFTWARE = ((uint32_t)0x0000003C)       /*!< Software trigger */
} DAC_TRIGGER_T;

/**
 * @brief    DAC_wave_generation, only applicable for APM32F072 devices
 */

typedef enum
{
    DAC_WAVE_GENERATION_NONE     = ((uint32_t)0x00000000),      /*!< Wave generation disabled */
    DAC_WAVE_GENERATION_NOISE    = ((uint32_t)0x00000040),      /*!< Noise wave generation enabled */
    DAC_WAVE_GENERATION_TRIANGLE = ((uint32_t)0x00000080)       /*!< Triangle wave generation enabled */
} DAC_WAVE_GENERATION_T;

/**
 * @brief    DAC channelx mask/amplitude selector, only applicable for APM32F072 devices
 */
typedef enum
{
    DAC_LFSRUNAMASK_BIT0        = ((uint32_t)0x00000000),       /*!< Unmask bit0 of LFSR/ triangle amplitude equal to 1 */
    DAC_LFSRUNAMASK_BITS1_0     = ((uint32_t)0x00000100),       /*!< Unmask bits[1:0] of LFSR to 3 */
    DAC_LFSRUNAMASK_BITS2_0     = ((uint32_t)0x00000200),       /*!< Unmask bits[2:0] of LFSR to 7 */
    DAC_LFSRUNAMASK_BITS3_0     = ((uint32_t)0x00000300),       /*!< Unmask bits[3:0] of LFSR to 15 */
    DAC_LFSRUNAMASK_BITS4_0     = ((uint32_t)0x00000400),       /*!< Unmask bits[4:0] of LFSR to 31 */
    DAC_LFSRUNAMASK_BITS5_0     = ((uint32_t)0x00000500),       /*!< Unmask bits[5:0] of LFSR to 63 */
    DAC_LFSRUNAMASK_BITS6_0     = ((uint32_t)0x00000600),       /*!< Unmask bits[6:0] of LFSR to 127 */
    DAC_LFSRUNAMASK_BITS7_0     = ((uint32_t)0x00000700),       /*!< Unmask bits[7:0] of LFSR to 255 */
    DAC_LFSRUNAMASK_BITS8_0     = ((uint32_t)0x00000800),       /*!< Unmask bits[8:0] of LFSR to 511 */
    DAC_LFSRUNAMASK_BITS9_0     = ((uint32_t)0x00000900),       /*!< Unmask bits[9:0] of LFSR to 1023 */
    DAC_LFSRUNAMASK_BITS10_0    = ((uint32_t)0x00000A00),       /*!< Unmask bits[10:0] of LFS to 2047 */
    DAC_LFSRUNAMASK_BITS11_0    = ((uint32_t)0x00000B00),       /*!< Unmask bits[11:0] of LFS to 4095 */
    DAC_TRIANGLEAMPLITUDE_1     = ((uint32_t)0x00000000),       /*!< Select max triangle amplitude of 1 */
    DAC_TRIANGLEAMPLITUDE_3     = ((uint32_t)0x00000100),       /*!< Select max triangle amplitude of 3 */
    DAC_TRIANGLEAMPLITUDE_7     = ((uint32_t)0x00000200),       /*!< Select max triangle amplitude of 7 */
    DAC_TRIANGLEAMPLITUDE_15    = ((uint32_t)0x00000300),       /*!< Select max triangle amplitude of 15 */
    DAC_TRIANGLEAMPLITUDE_31    = ((uint32_t)0x00000400),       /*!< Select max triangle amplitude of 31 */
    DAC_TRIANGLEAMPLITUDE_63    = ((uint32_t)0x00000500),       /*!< Select max triangle amplitude of 63 */
    DAC_TRIANGLEAMPLITUDE_127   = ((uint32_t)0x00000600),       /*!< Select max triangle amplitude of 127 */
    DAC_TRIANGLEAMPLITUDE_255   = ((uint32_t)0x00000700),       /*!< Select max triangle amplitude of 255 */
    DAC_TRIANGLEAMPLITUDE_511   = ((uint32_t)0x00000800),       /*!< Select max triangle amplitude of 511 */
    DAC_TRIANGLEAMPLITUDE_1023  = ((uint32_t)0x00000900),       /*!< Select max triangle amplitude of 1023 */
    DAC_TRIANGLEAMPLITUDE_2047  = ((uint32_t)0x00000A00),       /*!< Select max triangle amplitude of 2047 */
    DAC_TRIANGLEAMPLITUDE_4095  = ((uint32_t)0x00000B00)        /*!< Select max triangle amplitude of 4095 */
} DAC_MASK_AMPLITUDE_SEL_T;

/**
 * @brief    DAC_OutputBuffer
 */
typedef enum
{
    DAC_OUTPUTBUFF_ENABLE  = ((uint32_t)0x00000000), /*!< DAC channel1 output buffer enabledDAC channel1 output buffer disabled */
    DAC_OUTPUTBUFF_DISABLE = ((uint32_t)0x00000002)  /*!< DAC channel1 output buffer enabledDAC channel1 output buffer disabled */
} DAC_OUTPUTBUFF_T;

/**
 * @brief    DAC_Channel_selection
 */
typedef enum
{
    DAC_CHANNEL_1  = ((uint32_t)0x00000000),    /*!< DAC channel1 */
    DAC_CHANNEL_2  = ((uint32_t)0x00000010)     /*!< DAC channel2 */
} DAC_CHANNEL_T;

/**
 * @brief    DAC_data_alignment
 */
typedef enum
{
    DAC_ALIGN_12B_R = ((uint32_t)0x00000000),   /*!< DAC 12-bit right-aligned data */
    DAC_ALIGN_12B_L = ((uint32_t)0x00000004),   /*!< DAC 12-bit left-aligned data */
    DAC_ALIGN_8B_R  = ((uint32_t)0x00000008)    /*!< DAC 8-bit right-aligned data */
} DAC_DATA_ALIGN_T;

/**
 * @brief    DAC_interrupts_definition
 */
typedef enum
{
    DAC_INT_CH1_DMAUDR = ((uint32_t)0x00002000),    /*!< DAC channel1 DMA Underrun Interrupt */
    DAC_INT_CH2_DMAUDR = ((uint32_t)0x20000000)     /*!< DAC channel2 DMA Underrun Interrupt */
} DAC_INT_T;

/**
 * @brief    DAC_flags_definition
 */
typedef enum
{
    DAC_FLAG_CH1_DMAUDR = ((uint32_t)0x00002000),     /*!< DAC channel1 DMA Underrun Flag */
    DAC_FLAG_CH2_DMAUDR = ((uint32_t)0x20000000)      /*!< DAC channel2 DMA Underrun Flag */
} DAC_FLAG_T;

/**@} end of group DAC_Enumerations */

/** @defgroup DAC_Structures Structures
  @{
*/

/**
 * @brief    DAC Config structure definition
 */
typedef struct
{
    DAC_TRIGGER_T     trigger;                     /*!< DAC trigger selection */
    DAC_OUTPUTBUFF_T  outputBuff;                  /*!< DAC output buffer disable */
    DAC_WAVE_GENERATION_T     waveGeneration;      /*!< DAC noise/triangle wave generation selection */
    DAC_MASK_AMPLITUDE_SEL_T  maskAmplitudeSelect; /*!< DAC mask/amplitude selector */
} DAC_Config_T;

/**@} end of group DAC_Structures */

/** @defgroup DAC_Variables Variables
  @{
*/

/**@} end of group DAC_Variables */

/** @defgroup DAC_Functions Functions
  @{
*/

/* DAC reset and configuration */
void DAC_Reset(void);
void DAC_Config(uint32_t channel, DAC_Config_T* dacConfig);
void DAC_ConfigStructInit(DAC_Config_T* dacConfig);
void DAC_Enable(DAC_CHANNEL_T channel);
void DAC_Disable(DAC_CHANNEL_T channel);
void DAC_EnableSoftwareTrigger(DAC_CHANNEL_T channel);
void DAC_DisableSoftwareTrigger(DAC_CHANNEL_T channel);
void DAC_EnableDualSoftwareTrigger(void); /*!< Only for APM32F072 and APM32F091 devices */
void DAC_DisableDualSoftwareTrigger(void); /*!< Only for APM32F072 and APM32F091 devices */
void DAC_EnableWaveGeneration(DAC_CHANNEL_T channel, DAC_WAVE_GENERATION_T wave); /*!< Only for APM32F072 and APM32F091 devices */
void DAC_DisableWaveGeneration(DAC_CHANNEL_T channel, DAC_WAVE_GENERATION_T wave); /*!< Only for APM32F072 and APM32F091 devices */

/* Read data */
void DAC_ConfigChannel1Data(DAC_DATA_ALIGN_T dataAlign, uint16_t data);
void DAC_ConfigChannel2Data(DAC_DATA_ALIGN_T dataAlign, uint16_t data); /*!< Only for APM32F072 and APM32F091 devices */
void DAC_ConfigDualChannelData(DAC_DATA_ALIGN_T dataAlign, uint16_t data2, uint16_t data1); /*!< Only for APM32F072 and APM32F091 devices */
uint16_t DAC_ReadDataOutputValue(DAC_CHANNEL_T channel);

/* DMA */
void DAC_EnableDMA(DAC_CHANNEL_T channel);
void DAC_DisableDMA(DAC_CHANNEL_T channel);

/* Interrupt and flag */
void DAC_EnableInterrupt(DAC_CHANNEL_T channel);
void DAC_DisableInterrupt(DAC_CHANNEL_T channel);
uint8_t DAC_ReadStatusFlag(DAC_FLAG_T flag);
void DAC_ClearStatusFlag(DAC_FLAG_T flag);
uint8_t DAC_ReadIntFlag(DAC_INT_T intFlag);
void DAC_ClearIntFlag(DAC_INT_T intFlag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_DAC_H */

/**@} end of group DAC_Functions */
/**@} end of group DAC_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
