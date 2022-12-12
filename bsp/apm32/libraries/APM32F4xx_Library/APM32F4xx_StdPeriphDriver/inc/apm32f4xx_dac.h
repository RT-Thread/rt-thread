/*!
 * @file        apm32f4xx_dac.h
 *
 * @brief       This file contains all the functions prototypes for the DAC firmware library
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
#ifndef __APM32F4XX_DAC_H
#define __APM32F4XX_DAC_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup DAC_Driver
  @{
*/

/** @defgroup DAC_Enumerations
  @{
*/

/**
 * @brief DAC Channel selection
 */
typedef enum
{
    DAC_CHANNEL_1 = 0x00000000, /*!< DAC channel 1 */
    DAC_CHANNEL_2 = 0x00000010  /*!< DAC channel 2 */
} DAC_CHANNEL_T;

/**
 * @brief DAC trigger selection
 */
typedef enum
{
    DAC_TRIGGER_NONE       = 0x00000000,    /*!< DAC channel trigger disable */
    DAC_TRIGGER_TMR6_TRGO  = 0x00000004,    /*!< Enable trigger and select TMR6 TRGO event to trigger */
    DAC_TRIGGER_TMR8_TRGO  = 0x0000000C,    /*!< Enable trigger and select TMR8 TRGO event to trigger */
    DAC_TRIGGER_TMR7_TRGO  = 0x00000014,    /*!< Enable trigger and select TMR7 TRGO event to trigger */
    DAC_TRIGGER_TMR5_TRGO  = 0x0000001C,    /*!< Enable trigger and select TMR5 TRGO event to trigger */
    DAC_TRIGGER_TMR2_TRGO  = 0x00000024,    /*!< Enable trigger and select TMR2 TRGO event to trigger */
    DAC_TRIGGER_TMR4_TRGO  = 0x0000002C,    /*!< Enable trigger and select TMR4 TRGO event to trigger */
    DAC_TRIGGER_EINT9      = 0x00000034,    /*!< Enable trigger and select EINT9 to trigger */
    DAC_TRIGGER_SOFT       = 0x0000003C     /*!< Enable trigger and select software to trigger */
} DAC_TRIGGER_T;

/**
 * @brief DAC wave generation
 */
typedef enum
{
    DAC_WAVE_GENERATION_NONE     = 0x00000000,  /*!< Disable wave generation */
    DAC_WAVE_GENERATION_NOISE    = 0x00000040,  /*!< Enable generate noise wave */
    DAC_WAVE_GENERATION_TRIANGLE = 0x00000080   /*!< Enable generate triangle wave */
} DAC_WAVE_GENERATION_T;

/**
 * @brief DAC channelx mask/amplitude selector
 */
typedef enum
{
    DAC_LFSR_MASK_BIT11_1  = 0x00000000, /*!< Mask bit[11:1] of LFSR for noise wave generation */
    DAC_LFSR_MASK_BIT11_2  = 0x00000100, /*!< Mask bit[11:2] of LFSR for noise wave generation */
    DAC_LFSR_MASK_BIT11_3  = 0x00000200, /*!< Mask bit[11:3] of LFSR for noise wave generation */
    DAC_LFSR_MASK_BIT11_4  = 0x00000300, /*!< Mask bit[11:4] of LFSR for noise wave generation */
    DAC_LFSR_MASK_BIT11_5  = 0x00000400, /*!< Mask bit[11:5] of LFSR for noise wave generation */
    DAC_LFSR_MASK_BIT11_6  = 0x00000500, /*!< Mask bit[11:6] of LFSR for noise wave generation */
    DAC_LFSR_MASK_BIT11_7  = 0x00000600, /*!< Mask bit[11:7] of LFSR for noise wave generation */
    DAC_LFSR_MASK_BIT11_8  = 0x00000700, /*!< Mask bit[11:8] of LFSR for noise wave generation */
    DAC_LFSR_MASK_BIT11_9  = 0x00000800, /*!< Mask bit[11:9] of LFSR for noise wave generation */
    DAC_LFSR_MASK_BIT11_10 = 0x00000900, /*!< Mask bit[11:10] of LFSR for noise wave generation */
    DAC_LFSR_MASK_BIT11    = 0x00000A00, /*!< Mask bit11 of LFSR for noise wave generation */
    DAC_LFSR_MASK_NONE     = 0x00000B00, /*!< Mask none bit of LFSR for noise wave generation */

    DAC_TRIANGLE_AMPLITUDE_1    = 0x00000000, /*!< Triangle amplitude equal to 1 */
    DAC_TRIANGLE_AMPLITUDE_3    = 0x00000100, /*!< Triangle amplitude equal to 3 */
    DAC_TRIANGLE_AMPLITUDE_7    = 0x00000200, /*!< Triangle amplitude equal to 7 */
    DAC_TRIANGLE_AMPLITUDE_15   = 0x00000300, /*!< Triangle amplitude equal to 15 */
    DAC_TRIANGLE_AMPLITUDE_31   = 0x00000400, /*!< Triangle amplitude equal to 31 */
    DAC_TRIANGLE_AMPLITUDE_63   = 0x00000500, /*!< Triangle amplitude equal to 63 */
    DAC_TRIANGLE_AMPLITUDE_127  = 0x00000600, /*!< Triangle amplitude equal to 127 */
    DAC_TRIANGLE_AMPLITUDE_255  = 0x00000700, /*!< Triangle amplitude equal to 255 */
    DAC_TRIANGLE_AMPLITUDE_511  = 0x00000800, /*!< Triangle amplitude equal to 511 */
    DAC_TRIANGLE_AMPLITUDE_1023 = 0x00000900, /*!< Triangle amplitude equal to 1023 */
    DAC_TRIANGLE_AMPLITUDE_2047 = 0x00000A00, /*!< Triangle amplitude equal to 2047 */
    DAC_TRIANGLE_AMPLITUDE_4095 = 0x00000B00  /*!< Triangle amplitude equal to 4095 */
} DAC_MASK_AMPLITUDE_SEL_T;

/**
 * @brief DAC output buffer
 */
typedef enum
{
    DAC_OUTPUT_BUFFER_ENBALE  = 0x00000000, /*!< DAC Channel Output Buffer Enable */
    DAC_OUTPUT_BUFFER_DISABLE = 0x00000002  /*!< DAC Channel1 Output Buffer Disable */
} DAC_OUTPUT_BUFFER_T;

/**
 * @brief DAC data align
 */
typedef enum
{
    DAC_ALIGN_12BIT_R = 0x00000000, /*!< 12-bit right-aligned data */
    DAC_ALIGN_12BIT_L = 0x00000004, /*!< 12-bit left-aligned data */
    DAC_ALIGN_8BIT_R  = 0x00000008  /*!< 8-bit right-aligned data */
} DAC_ALIGN_T;

/**@} end of group DAC_Enumerations*/

/** @addtogroup DAC_Structure Data Structure
  @{
*/

/**
 * @brief DAC Config structure definition
 */
typedef struct
{
    DAC_TRIGGER_T               trigger;                /*!< DAC trigger selection */
    DAC_OUTPUT_BUFFER_T         outputBuffer;           /*!< DAC output buffer configuration */
    DAC_WAVE_GENERATION_T       waveGeneration;         /*!< DAC wave generation configuration*/
    DAC_MASK_AMPLITUDE_SEL_T    maskAmplitudeSelect;    /*!< DAC channelx mask/amplitude selector */
} DAC_Config_T;

/**@} end of group DAC_Structure*/

/** @defgroup DAC_Functions
  @{
*/

/* DAC Reset and Configuration */
void DAC_Reset(void);
void DAC_Config(uint32_t channel, DAC_Config_T* dacConfig);
void DAC_ConfigStructInit(DAC_Config_T* dacConfig);
void DAC_Enable(DAC_CHANNEL_T channel);
void DAC_Disable(DAC_CHANNEL_T channel);

/* DAC channel for DAM */
void DAC_DMA_Enable(DAC_CHANNEL_T channel);
void DAC_DMA_Disable(DAC_CHANNEL_T channel);

/* DAC channel software trigger */
void DAC_EnableSoftwareTrigger(DAC_CHANNEL_T channel);
void DAC_DisableSoftwareTrigger(DAC_CHANNEL_T channel);
void DAC_EnableDualSoftwareTrigger(void);
void DAC_DisableDualSoftwareTrigger(void);

/* DAC channel wave generation */
void DAC_EnableWaveGeneration(DAC_CHANNEL_T channel, DAC_WAVE_GENERATION_T wave);
void DAC_DisableWaveGeneration(DAC_CHANNEL_T channel, DAC_WAVE_GENERATION_T wave);

/* DAC set channel data */
void DAC_ConfigChannel1Data(DAC_ALIGN_T align, uint16_t data);
void DAC_ConfigChannel2Data(DAC_ALIGN_T align, uint16_t data);
void DAC_ConfigDualChannelData(DAC_ALIGN_T align, uint16_t data2, uint16_t data1);

/* DAC read data output value */
uint16_t DAC_ReadDataOutputValue(DAC_CHANNEL_T channel);

/* DAC Interrupts and flag */
void DAC_EnableInterrupt(DAC_CHANNEL_T channel);
void DAC_DisableInterrupt(DAC_CHANNEL_T channel);
uint8_t DAC_ReadStatusFlag(DAC_CHANNEL_T channel);
void DAC_ClearStatusFlag(DAC_CHANNEL_T channel);
uint8_t DAC_ReadIntFlag(DAC_CHANNEL_T channel);
void DAC_ClearIntFlag(DAC_CHANNEL_T channel);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_DAC_H */

/**@} end of group DAC_Enumerations */
/**@} end of group DAC_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
