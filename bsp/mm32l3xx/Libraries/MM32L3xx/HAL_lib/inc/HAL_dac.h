/**
******************************************************************************
* @file    HAL_dac.h
* @author  AE Team
* @version V1.0.0
* @date    28/7/2017
* @brief   This file contains all the functions prototypes for the DAC firmware 
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
* <h2><center>&copy; COPYRIGHT 2017 MindMotion</center></h2>
*/ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_DAC_H
#define __HAL_DAC_H

/* Includes ------------------------------------------------------------------*/
#include "HAL_device.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @addtogroup DAC
* @{
*/

/** @defgroup DAC_Exported_Types
* @{
*/

/** 
* @brief  DAC Init structure definition
*/

typedef struct
{
  uint32_t DAC_Trigger;
  uint32_t DAC_WaveGeneration;
  uint32_t DAC_LFSRUnmask_TriangleAmplitude;
  uint32_t DAC_OutputBuffer; 
}DAC_InitTypeDef;

/**
* @}
*/

/** @defgroup DAC_Exported_Constants
* @{
*/

/** @defgroup DAC_trigger_selection 
* @{
*/

#define DAC_Trigger_None                   ((uint32_t)0x00000000)
#define DAC_Trigger_T1_TRGO                ((uint32_t)0x00000004)
#define DAC_Trigger_T3_TRGO                ((uint32_t)0x0000000C)
#define DAC_Trigger_T2_TRGO                ((uint32_t)0x00000024)
#define DAC_Trigger_T4_TRGO                ((uint32_t)0x0000002C)
#define DAC_Trigger_Ext_IT9                ((uint32_t)0x00000034)
#define DAC_Trigger_Software               ((uint32_t)0x0000003C)

#define IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_Trigger_None) || \
((TRIGGER) == DAC_Trigger_T1_TRGO) || \
  ((TRIGGER) == DAC_Trigger_T3_TRGO) || \
    ((TRIGGER) == DAC_Trigger_T2_TRGO) || \
      ((TRIGGER) == DAC_Trigger_T4_TRGO) || \
        ((TRIGGER) == DAC_Trigger_Ext_IT9) || \
          ((TRIGGER) == DAC_Trigger_Software))

/**
* @}
*/

/** @defgroup DAC_wave_generation 
* @{
*/

#define DAC_WaveGeneration_None            ((uint32_t)0x00000000)
#define DAC_WaveGeneration_Noise           ((uint32_t)0x00000040)
#define DAC_WaveGeneration_Triangle        ((uint32_t)0x00000080)
#define IS_DAC_GENERATE_WAVE(WAVE) (((WAVE) == DAC_WaveGeneration_None) || \
((WAVE) == DAC_WaveGeneration_Noise) || \
  ((WAVE) == DAC_WaveGeneration_Triangle))
/**
* @}
*/

/** @defgroup DAC_noise_wave_generation_mask_triangle_wave_generation_max_amplitude 
* @{
*/

#define DAC_LFSRUnmask_Bit0                ((uint32_t)0x00000000)
#define DAC_LFSRUnmask_Bits1_0             ((uint32_t)0x00000100)
#define DAC_LFSRUnmask_Bits2_0             ((uint32_t)0x00000200)
#define DAC_LFSRUnmask_Bits3_0             ((uint32_t)0x00000300)
#define DAC_LFSRUnmask_Bits4_0             ((uint32_t)0x00000400)
#define DAC_LFSRUnmask_Bits5_0             ((uint32_t)0x00000500)
#define DAC_LFSRUnmask_Bits6_0             ((uint32_t)0x00000600)
#define DAC_LFSRUnmask_Bits7_0             ((uint32_t)0x00000700)
#define DAC_LFSRUnmask_Bits8_0             ((uint32_t)0x00000800)
#define DAC_LFSRUnmask_Bits9_0             ((uint32_t)0x00000900)
#define DAC_LFSRUnmask_Bits10_0            ((uint32_t)0x00000A00)
#define DAC_LFSRUnmask_Bits11_0            ((uint32_t)0x00000B00)
#define DAC_TriangleAmplitude_1            ((uint32_t)0x00000000)
#define DAC_TriangleAmplitude_3            ((uint32_t)0x00000100)
#define DAC_TriangleAmplitude_7            ((uint32_t)0x00000200)
#define DAC_TriangleAmplitude_15           ((uint32_t)0x00000300)
#define DAC_TriangleAmplitude_31           ((uint32_t)0x00000400)
#define DAC_TriangleAmplitude_63           ((uint32_t)0x00000500)
#define DAC_TriangleAmplitude_127          ((uint32_t)0x00000600)
#define DAC_TriangleAmplitude_255          ((uint32_t)0x00000700)
#define DAC_TriangleAmplitude_511          ((uint32_t)0x00000800)
#define DAC_TriangleAmplitude_1023         ((uint32_t)0x00000900)
#define DAC_TriangleAmplitude_2047         ((uint32_t)0x00000A00)
#define DAC_TriangleAmplitude_4095         ((uint32_t)0x00000B00)

#define IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(VALUE) (((VALUE) == DAC_LFSRUnmask_Bit0) || \
((VALUE) == DAC_LFSRUnmask_Bits1_0) || \
  ((VALUE) == DAC_LFSRUnmask_Bits2_0) || \
    ((VALUE) == DAC_LFSRUnmask_Bits3_0) || \
      ((VALUE) == DAC_LFSRUnmask_Bits4_0) || \
        ((VALUE) == DAC_LFSRUnmask_Bits5_0) || \
          ((VALUE) == DAC_LFSRUnmask_Bits6_0) || \
            ((VALUE) == DAC_LFSRUnmask_Bits7_0) || \
              ((VALUE) == DAC_LFSRUnmask_Bits8_0) || \
                ((VALUE) == DAC_LFSRUnmask_Bits9_0) || \
                  ((VALUE) == DAC_LFSRUnmask_Bits10_0) || \
                    ((VALUE) == DAC_LFSRUnmask_Bits11_0) || \
                      ((VALUE) == DAC_TriangleAmplitude_1) || \
                        ((VALUE) == DAC_TriangleAmplitude_3) || \
                          ((VALUE) == DAC_TriangleAmplitude_7) || \
                            ((VALUE) == DAC_TriangleAmplitude_15) || \
                              ((VALUE) == DAC_TriangleAmplitude_31) || \
                                ((VALUE) == DAC_TriangleAmplitude_63) || \
                                  ((VALUE) == DAC_TriangleAmplitude_127) || \
                                    ((VALUE) == DAC_TriangleAmplitude_255) || \
                                      ((VALUE) == DAC_TriangleAmplitude_511) || \
                                        ((VALUE) == DAC_TriangleAmplitude_1023) || \
                                          ((VALUE) == DAC_TriangleAmplitude_2047) || \
                                            ((VALUE) == DAC_TriangleAmplitude_4095))
/**
* @}
*/

/** @defgroup DAC_output_buffer 
* @{
*/

#define DAC_OutputBuffer_Enable            ((uint32_t)0x00000000)
#define DAC_OutputBuffer_Disable           ((uint32_t)0x00000002)
#define IS_DAC_OUTPUT_BUFFER_STATE(STATE) (((STATE) == DAC_OutputBuffer_Enable) || \
((STATE) == DAC_OutputBuffer_Disable))
/**
* @}
*/

/** @defgroup DAC_Channel_selection 
* @{
*/

#define DAC_Channel_1                      ((uint32_t)0x00000000)
#define DAC_Channel_2                      ((uint32_t)0x00000010)
#define IS_DAC_CHANNEL(CHANNEL) (((CHANNEL) == DAC_Channel_1) || \
((CHANNEL) == DAC_Channel_2))
/**
* @}
*/

/** @defgroup DAC_data_alignement 
* @{
*/

#define DAC_Align_12b_R                    ((uint32_t)0x00000000)
#define DAC_Align_12b_L                    ((uint32_t)0x00000004)
#define DAC_Align_8b_R                     ((uint32_t)0x00000008)
#define IS_DAC_ALIGN(ALIGN) (((ALIGN) == DAC_Align_12b_R) || \
((ALIGN) == DAC_Align_12b_L) || \
  ((ALIGN) == DAC_Align_8b_R))
/**
* @}
*/

/** @defgroup DAC_wave_generation 
* @{
*/

#define DAC_Wave_Noise                     ((uint32_t)0x00000040)
#define DAC_Wave_Triangle                  ((uint32_t)0x00000080)
#define IS_DAC_WAVE(WAVE) (((WAVE) == DAC_Wave_Noise) || \
((WAVE) == DAC_Wave_Triangle))
/**
* @}
*/

/** @defgroup DAC_data 
* @{
*/

#define IS_DAC_DATA(DATA) ((DATA) <= 0xFFF0) 
/**
* @}
*/

/**
* @}
*/

/** @defgroup DAC_Exported_Macros
* @{
*/

/**
* @}
*/

/** @defgroup DAC_Exported_Functions
* @{
*/

void DAC_DeInit(void);
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct);
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState);
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState);
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1);
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel);

#endif /*__HAL_DAC_H */
/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2017 MindMotion ----------------------*/
