/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_dac.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file contains all the functions prototypes for the
*                      DAC firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_DAC_H
#define __STM32F10x_DAC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
/* DAC Init structure definition */
typedef struct
{
  u32 DAC_Trigger;
  u32 DAC_WaveGeneration;
  u32 DAC_LFSRUnmask_TriangleAmplitude;
  u32 DAC_OutputBuffer; 
}DAC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/* DAC trigger selection */
#define DAC_Trigger_None                   ((u32)0x00000000)
#define DAC_Trigger_T6_TRGO                ((u32)0x00000004)
#define DAC_Trigger_T8_TRGO                ((u32)0x0000000C)
#define DAC_Trigger_T7_TRGO                ((u32)0x00000014)
#define DAC_Trigger_T5_TRGO                ((u32)0x0000001C)
#define DAC_Trigger_T2_TRGO                ((u32)0x00000024)
#define DAC_Trigger_T4_TRGO                ((u32)0x0000002C)
#define DAC_Trigger_Ext_IT9                ((u32)0x00000034)
#define DAC_Trigger_Software               ((u32)0x0000003C)

#define IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_Trigger_None) || \
                                 ((TRIGGER) == DAC_Trigger_T6_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_T8_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_T7_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_T5_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_T2_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_T4_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_Ext_IT9) || \
                                 ((TRIGGER) == DAC_Trigger_Software))

/* DAC wave generation */
#define DAC_WaveGeneration_None            ((u32)0x00000000)
#define DAC_WaveGeneration_Noise           ((u32)0x00000040)
#define DAC_WaveGeneration_Triangle        ((u32)0x00000080)

#define IS_DAC_GENERATE_WAVE(WAVE) (((WAVE) == DAC_WaveGeneration_None) || \
                                    ((WAVE) == DAC_WaveGeneration_Noise) || \
                                    ((WAVE) == DAC_WaveGeneration_Triangle))

/* DAC noise wave generation mask / triangle wave generation max amplitude */
#define DAC_LFSRUnmask_Bit0                ((u32)0x00000000)
#define DAC_LFSRUnmask_Bits1_0             ((u32)0x00000100)
#define DAC_LFSRUnmask_Bits2_0             ((u32)0x00000200)
#define DAC_LFSRUnmask_Bits3_0             ((u32)0x00000300)
#define DAC_LFSRUnmask_Bits4_0             ((u32)0x00000400)
#define DAC_LFSRUnmask_Bits5_0             ((u32)0x00000500)
#define DAC_LFSRUnmask_Bits6_0             ((u32)0x00000600)
#define DAC_LFSRUnmask_Bits7_0             ((u32)0x00000700)
#define DAC_LFSRUnmask_Bits8_0             ((u32)0x00000800)
#define DAC_LFSRUnmask_Bits9_0             ((u32)0x00000900)
#define DAC_LFSRUnmask_Bits10_0            ((u32)0x00000A00)
#define DAC_LFSRUnmask_Bits11_0            ((u32)0x00000B00)

#define DAC_TriangleAmplitude_1            ((u32)0x00000000)
#define DAC_TriangleAmplitude_3            ((u32)0x00000100)
#define DAC_TriangleAmplitude_7            ((u32)0x00000200)
#define DAC_TriangleAmplitude_15           ((u32)0x00000300)
#define DAC_TriangleAmplitude_31           ((u32)0x00000400)
#define DAC_TriangleAmplitude_63           ((u32)0x00000500)
#define DAC_TriangleAmplitude_127          ((u32)0x00000600)
#define DAC_TriangleAmplitude_255          ((u32)0x00000700)
#define DAC_TriangleAmplitude_511          ((u32)0x00000800)
#define DAC_TriangleAmplitude_1023         ((u32)0x00000900)
#define DAC_TriangleAmplitude_2047         ((u32)0x00000A00)
#define DAC_TriangleAmplitude_4095         ((u32)0x00000B00)

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

/* DAC output buffer */
#define DAC_OutputBuffer_Enable            ((u32)0x00000000)
#define DAC_OutputBuffer_Disable           ((u32)0x00000002)

#define IS_DAC_OUTPUT_BUFFER_STATE(STATE) (((STATE) == DAC_OutputBuffer_Enable) || \
                                           ((STATE) == DAC_OutputBuffer_Disable))

/* DAC Channel selection */
#define DAC_Channel_1                      ((u32)0x00000000)
#define DAC_Channel_2                      ((u32)0x00000010)

#define IS_DAC_CHANNEL(CHANNEL) (((CHANNEL) == DAC_Channel_1) || \
                                 ((CHANNEL) == DAC_Channel_2))

/* DAC data alignement */
#define DAC_Align_12b_R                    ((u32)0x00000000)
#define DAC_Align_12b_L                    ((u32)0x00000004)
#define DAC_Align_8b_R                     ((u32)0x00000008)

#define IS_DAC_ALIGN(ALIGN) (((ALIGN) == DAC_Align_12b_R) || \
                             ((ALIGN) == DAC_Align_12b_L) || \
                             ((ALIGN) == DAC_Align_8b_R))

/* DAC wave generation */
#define DAC_Wave_Noise                     ((u32)0x00000040)
#define DAC_Wave_Triangle                  ((u32)0x00000080)

#define IS_DAC_WAVE(WAVE) (((WAVE) == DAC_Wave_Noise) || \
                           ((WAVE) == DAC_Wave_Triangle))

/* DAC data ------------------------------------------------------------------*/
#define IS_DAC_DATA(DATA) ((DATA) <= 0xFFF0) 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void DAC_DeInit(void);
void DAC_Init(u32 DAC_Channel, DAC_InitTypeDef* DAC_InitStruct);
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);
void DAC_Cmd(u32 DAC_Channel, FunctionalState NewState);
void DAC_DMACmd(u32 DAC_Channel, FunctionalState NewState);
void DAC_SoftwareTriggerCmd(u32 DAC_Channel, FunctionalState NewState);
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState);
void DAC_WaveGenerationCmd(u32 DAC_Channel, u32 DAC_Wave, FunctionalState NewState);
void DAC_SetChannel1Data(u32 DAC_Align, u16 Data);
void DAC_SetChannel2Data(u32 DAC_Align, u16 Data);
void DAC_SetDualChannelData(u32 DAC_Align, u16 Data2, u16 Data1);
u16 DAC_GetDataOutputValue(u32 DAC_Channel);

#endif /*__STM32F10x_DAC_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
