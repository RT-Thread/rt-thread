/*!
 * @file        apm32f10x_dac.h
 *
 * @brief       This file contains all the functions prototypes for the DAC firmware library
 *
 * @version     V1.0.1
 *
 * @date        2021-03-23
 *
 */

#ifndef __APM32F10X_DAC_H
#define __APM32F10X_DAC_H

#include "apm32f10x.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup DAC_Driver DAC Driver
  @{
*/

/** @addtogroup DAC_Enumerations Enumerations
  @{
*/

/**
 * @brief    DAC Channel selection
 */
typedef enum
{
    DAC_CHANNEL_1 = 0x00000000,
    DAC_CHANNEL_2 = 0x00000010
}DAC_CHANNEL_T;

/**
 * @brief    DAC trigger selection
 */
typedef enum
{
    DAC_TRIGGER_NONE       = 0x00000000,
    DAC_TRIGGER_TMR6_TRGO  = 0x00000004,
    DAC_TRIGGER_TMR8_TRGO  = 0x0000000C,
    DAC_TRIGGER_TMR7_TRGO  = 0x00000014,
    DAC_TRIGGER_TMR5_TRGO  = 0x0000001C,
    DAC_TRIGGER_TMR2_TRGO  = 0x00000024,
    DAC_TRIGGER_TMR4_TRGO  = 0x0000002C,
    DAC_TRIGGER_EINT9      = 0x00000034,
    DAC_TRIGGER_SOFT       = 0x0000003C
}DAC_TRIGGER_T;

/**
 * @brief    DAC wave generation
 */
typedef enum
{
    DAC_WAVE_GENERATION_NONE     = 0x00000000,
    DAC_WAVE_GENERATION_NOISE    = 0x00000040,
    DAC_WAVE_GENERATION_TRIANGLE = 0x00000080
}DAC_WAVE_GENERATION_T;

/**
 * @brief    DAC channelx mask/amplitude selector
 */
typedef enum
{
    DAC_LFSR_MASK_BIT11_1  = 0x00000000, //!< Mask bit[11:1] of LFSR for noise wave generation
    DAC_LFSR_MASK_BIT11_2  = 0x00001000, //!< Mask bit[11:2] of LFSR for noise wave generation
    DAC_LFSR_MASK_BIT11_3  = 0x00002000, //!< Mask bit[11:3] of LFSR for noise wave generation
    DAC_LFSR_MASK_BIT11_4  = 0x00003000, //!< Mask bit[11:4] of LFSR for noise wave generation
    DAC_LFSR_MASK_BIT11_5  = 0x00004000, //!< Mask bit[11:5] of LFSR for noise wave generation
    DAC_LFSR_MASK_BIT11_6  = 0x00005000, //!< Mask bit[11:6] of LFSR for noise wave generation
    DAC_LFSR_MASK_BIT11_7  = 0x00006000, //!< Mask bit[11:7] of LFSR for noise wave generation
    DAC_LFSR_MASK_BIT11_8  = 0x00007000, //!< Mask bit[11:8] of LFSR for noise wave generation
    DAC_LFSR_MASK_BIT11_9  = 0x00008000, //!< Mask bit[11:9] of LFSR for noise wave generation
    DAC_LFSR_MASK_BIT11_10 = 0x00009000, //!< Mask bit[11:10] of LFSR for noise wave generation
    DAC_LFSR_MASK_BIT11    = 0x0000A000, //!< Mask bit11 of LFSR for noise wave generation
    DAC_LFSR_MASK_NONE     = 0x0000B000, //!< Mask none bit of LFSR for noise wave generation

    DAC_TRIANGLE_AMPLITUDE_1    = 0x00000000, //!< Triangle amplitude equal to 1
    DAC_TRIANGLE_AMPLITUDE_3    = 0x00001000, //!< Triangle amplitude equal to 3
    DAC_TRIANGLE_AMPLITUDE_7    = 0x00002000, //!< Triangle amplitude equal to 7
    DAC_TRIANGLE_AMPLITUDE_15   = 0x00003000, //!< Triangle amplitude equal to 15
    DAC_TRIANGLE_AMPLITUDE_31   = 0x00004000, //!< Triangle amplitude equal to 31
    DAC_TRIANGLE_AMPLITUDE_63   = 0x00005000, //!< Triangle amplitude equal to 63
    DAC_TRIANGLE_AMPLITUDE_127  = 0x00006000, //!< Triangle amplitude equal to 127
    DAC_TRIANGLE_AMPLITUDE_255  = 0x00007000, //!< Triangle amplitude equal to 255
    DAC_TRIANGLE_AMPLITUDE_511  = 0x00008000, //!< Triangle amplitude equal to 511
    DAC_TRIANGLE_AMPLITUDE_1023 = 0x00009000, //!< Triangle amplitude equal to 1023
    DAC_TRIANGLE_AMPLITUDE_2047 = 0x0000A000, //!< Triangle amplitude equal to 2047
    DAC_TRIANGLE_AMPLITUDE_4095 = 0x0000B000  //!< Triangle amplitude equal to 4095
}DAC_MASK_AMPLITUDE_SEL_T;

/**
 * @brief    DAC output buffer
 */
typedef enum
{
    DAC_OUTPUT_BUFFER_ENBALE  = 0x00000000,
    DAC_OUTPUT_BUFFER_DISABLE = 0x00000002
}DAC_OUTPUT_BUFFER_T;

/**
 * @brief    DAC data align
 */
typedef enum
{
    DAC_ALIGN_12BIT_R = 0x00000000,
    DAC_ALIGN_12BIT_L = 0x00000004,
    DAC_ALIGN_8BIT_R  = 0x00000008
}DAC_ALIGN_T;

/**@} end of group DAC_Enumerations*/


/** @addtogroup DAC_Structure Data Structure
  @{
*/

/**
 * @brief    DAC Config structure definition
 */
typedef struct
{
    DAC_TRIGGER_T               trigger;
    DAC_OUTPUT_BUFFER_T         outputBuffer;
    DAC_WAVE_GENERATION_T       waveGeneration;
    DAC_MASK_AMPLITUDE_SEL_T    maskAmplitudeSelect;
}DAC_ConfigStruct_T;

/**@} end of group DAC_Structure*/


/** @addtogroup DAC_Fuctions Fuctions
  @{
*/

/** DAC Reset and Configuration */
void DAC_Reset(void);
void DAC_Config(uint32_t channel, DAC_ConfigStruct_T* configStruct);
void DAC_ConfigStructInit(DAC_ConfigStruct_T* configStruct);
void DAC_Enable(DAC_CHANNEL_T channel);
void DAC_Disable(DAC_CHANNEL_T channel);

/** DAC channel for DAM */
void DAC_DMA_Enable(DAC_CHANNEL_T channel);
void DAC_DMA_Disable(DAC_CHANNEL_T channel);

/** DAC channel software trigger */
void DAC_EnableSoftwareTrigger(DAC_CHANNEL_T channel);
void DAC_DisableSoftwareTrigger(DAC_CHANNEL_T channel);
void DAC_EnableDualSoftwareTrigger(void);
void DAC_DisableDualSoftwareTrigger(void);

/** DAC channel wave generation */
void DAC_EnableWaveGeneration(DAC_CHANNEL_T channel, DAC_WAVE_GENERATION_T wave);
void DAC_DisableWaveGeneration(DAC_CHANNEL_T channel, DAC_WAVE_GENERATION_T wave);

/** DAC set channel data */
void DAC_ConfigChannel1Data(DAC_ALIGN_T align, uint16_t data);
void DAC_ConfigChannel2Data(DAC_ALIGN_T align, uint16_t data);
void DAC_ConfigDualChannelData(DAC_ALIGN_T align, uint16_t data2, uint16_t data1);

/** DAC read data output value */
uint16_t DAC_ReadDataOutputValue(DAC_CHANNEL_T channel);

/**@} end of group DAC_Fuctions*/
/**@} end of group DAC_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F10X_DAC_H */
