/**
 **************************************************************************
 * File Name    : at32f4xx_dac.h
 * Description  : at32f4xx DAC header file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_DAC_H
#define __AT32F4xx_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
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
    uint32_t DAC_Trigger;                           /*!< Specifies the external trigger for the selected DAC channel.
                                                       This parameter can be a value of @ref DAC_trigger_selection */
                                                    
    uint32_t DAC_WaveGeneration;                    /*!< Specifies whether DAC channel noise waves or triangle waves
                                                       are generated, or whether no wave is generated.
                                                       This parameter can be a value of @ref DAC_wave_generation */
                                                    
    uint32_t DAC_LFSRUnmask_TriangleAmplitude;      /*!< Specifies the LFSR mask for noise wave generation or
                                                       the maximum amplitude triangle generation for the DAC channel.
                                                       This parameter can be a value of @ref DAC_lfsrunmask_triangleamplitude */
                                                    
    uint32_t DAC_OutputBuffer;                      /*!< Specifies whether the DAC channel output buffer is enabled or disabled.
                                                       This parameter can be a value of @ref DAC_output_buffer */
} DAC_InitType;

/**
  * @}
  */

/** @defgroup DAC_Exported_Constants
  * @{
  */

/** @defgroup DAC_trigger_selection
  * @{
  */

#define DAC_Trigger_None                    ((uint32_t)0x00000000) /*!< Conversion is automatic once the DAC1_DHRxxxx register 
                                                                       has been loaded, and not by external trigger */
#define DAC_Trigger_TMR6_TRGO               ((uint32_t)0x00000004) /*!< TMR6 TRGO selected as external conversion trigger for DAC channel */
#define DAC_Trigger_TMR8_TRGO               ((uint32_t)0x0000000C) /*!< TMR8 TRGO selected as external conversion trigger for DAC channel
                                                                      only in High-density devices*/
#define DAC_Trigger_TMR7_TRGO               ((uint32_t)0x00000014) /*!< TMR7 TRGO selected as external conversion trigger for DAC channel */
#define DAC_Trigger_TMR5_TRGO               ((uint32_t)0x0000001C) /*!< TMR5 TRGO selected as external conversion trigger for DAC channel */
#define DAC_Trigger_TMR2_TRGO               ((uint32_t)0x00000024) /*!< TMR2 TRGO selected as external conversion trigger for DAC channel */
#define DAC_Trigger_TMR4_TRGO               ((uint32_t)0x0000002C) /*!< TMR4 TRGO selected as external conversion trigger for DAC channel */
#define DAC_Trigger_Ext_INT9                ((uint32_t)0x00000034) /*!< EXTI Line9 event selected as external conversion trigger for DAC channel */
#define DAC_Trigger_Software                ((uint32_t)0x0000003C) /*!< Conversion started by software trigger for DAC channel */

#define IS_DAC_TRIGGER(TRIGGER)             (((TRIGGER) == DAC_Trigger_None) || \
                                             ((TRIGGER) == DAC_Trigger_TMR6_TRGO) || \
                                             ((TRIGGER) == DAC_Trigger_TMR8_TRGO) || \
                                             ((TRIGGER) == DAC_Trigger_TMR7_TRGO) || \
                                             ((TRIGGER) == DAC_Trigger_TMR5_TRGO) || \
                                             ((TRIGGER) == DAC_Trigger_TMR2_TRGO) || \
                                             ((TRIGGER) == DAC_Trigger_TMR4_TRGO) || \
                                             ((TRIGGER) == DAC_Trigger_Ext_INT9) || \
                                             ((TRIGGER) == DAC_Trigger_Software))

/**
  * @}
  */

/** @defgroup DAC_wave_generation
  * @{
  */

#define DAC_WaveGeneration_None             ((uint32_t)0x00000000)
#define DAC_WaveGeneration_Noise            ((uint32_t)0x00000040)
#define DAC_WaveGeneration_Triangle         ((uint32_t)0x00000080)
#define IS_DAC_GENERATE_WAVE(WAVE)          (((WAVE) == DAC_WaveGeneration_None) || \
                                             ((WAVE) == DAC_WaveGeneration_Noise) || \
                                             ((WAVE) == DAC_WaveGeneration_Triangle))
/**
  * @}
  */

/** @defgroup DAC_lfsrunmask_triangleamplitude
  * @{
  */

#define DAC_LFSRUnmsk_Bit0                  ((uint32_t)0x00000000) /*!< Unmask DAC channel LFSR bit0 for noise wave generation */
#define DAC_LFSRUnmsk_Bits1_0               ((uint32_t)0x00000100) /*!< Unmask DAC channel LFSR bit[1:0] for noise wave generation */
#define DAC_LFSRUnmsk_Bits2_0               ((uint32_t)0x00000200) /*!< Unmask DAC channel LFSR bit[2:0] for noise wave generation */
#define DAC_LFSRUnmsk_Bits3_0               ((uint32_t)0x00000300) /*!< Unmask DAC channel LFSR bit[3:0] for noise wave generation */
#define DAC_LFSRUnmsk_Bits4_0               ((uint32_t)0x00000400) /*!< Unmask DAC channel LFSR bit[4:0] for noise wave generation */
#define DAC_LFSRUnmsk_Bits5_0               ((uint32_t)0x00000500) /*!< Unmask DAC channel LFSR bit[5:0] for noise wave generation */
#define DAC_LFSRUnmsk_Bits6_0               ((uint32_t)0x00000600) /*!< Unmask DAC channel LFSR bit[6:0] for noise wave generation */
#define DAC_LFSRUnmsk_Bits7_0               ((uint32_t)0x00000700) /*!< Unmask DAC channel LFSR bit[7:0] for noise wave generation */
#define DAC_LFSRUnmsk_Bits8_0               ((uint32_t)0x00000800) /*!< Unmask DAC channel LFSR bit[8:0] for noise wave generation */
#define DAC_LFSRUnmsk_Bits9_0               ((uint32_t)0x00000900) /*!< Unmask DAC channel LFSR bit[9:0] for noise wave generation */
#define DAC_LFSRUnmsk_Bits10_0              ((uint32_t)0x00000A00) /*!< Unmask DAC channel LFSR bit[10:0] for noise wave generation */
#define DAC_LFSRUnmsk_Bits11_0              ((uint32_t)0x00000B00) /*!< Unmask DAC channel LFSR bit[11:0] for noise wave generation */
#define DAC_TriangleAmp_1                   ((uint32_t)0x00000000) /*!< Select max triangle amplitude of 1 */
#define DAC_TriangleAmp_3                   ((uint32_t)0x00000100) /*!< Select max triangle amplitude of 3 */
#define DAC_TriangleAmp_7                   ((uint32_t)0x00000200) /*!< Select max triangle amplitude of 7 */
#define DAC_TriangleAmp_15                  ((uint32_t)0x00000300) /*!< Select max triangle amplitude of 15 */
#define DAC_TriangleAmp_31                  ((uint32_t)0x00000400) /*!< Select max triangle amplitude of 31 */
#define DAC_TriangleAmp_63                  ((uint32_t)0x00000500) /*!< Select max triangle amplitude of 63 */
#define DAC_TriangleAmp_127                 ((uint32_t)0x00000600) /*!< Select max triangle amplitude of 127 */
#define DAC_TriangleAmp_255                 ((uint32_t)0x00000700) /*!< Select max triangle amplitude of 255 */
#define DAC_TriangleAmp_511                 ((uint32_t)0x00000800) /*!< Select max triangle amplitude of 511 */
#define DAC_TriangleAmp_1023                ((uint32_t)0x00000900) /*!< Select max triangle amplitude of 1023 */
#define DAC_TriangleAmp_2047                ((uint32_t)0x00000A00) /*!< Select max triangle amplitude of 2047 */
#define DAC_TriangleAmp_4095                ((uint32_t)0x00000B00) /*!< Select max triangle amplitude of 4095 */

#define IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(VALUE)    (((VALUE) == DAC_LFSRUnmsk_Bit0) || \
                                                         ((VALUE) == DAC_LFSRUnmsk_Bits1_0) || \
                                                         ((VALUE) == DAC_LFSRUnmsk_Bits2_0) || \
                                                         ((VALUE) == DAC_LFSRUnmsk_Bits3_0) || \
                                                         ((VALUE) == DAC_LFSRUnmsk_Bits4_0) || \
                                                         ((VALUE) == DAC_LFSRUnmsk_Bits5_0) || \
                                                         ((VALUE) == DAC_LFSRUnmsk_Bits6_0) || \
                                                         ((VALUE) == DAC_LFSRUnmsk_Bits7_0) || \
                                                         ((VALUE) == DAC_LFSRUnmsk_Bits8_0) || \
                                                         ((VALUE) == DAC_LFSRUnmsk_Bits9_0) || \
                                                         ((VALUE) == DAC_LFSRUnmsk_Bits10_0) || \
                                                         ((VALUE) == DAC_LFSRUnmsk_Bits11_0) || \
                                                         ((VALUE) == DAC_TriangleAmp_1) || \
                                                         ((VALUE) == DAC_TriangleAmp_3) || \
                                                         ((VALUE) == DAC_TriangleAmp_7) || \
                                                         ((VALUE) == DAC_TriangleAmp_15) || \
                                                         ((VALUE) == DAC_TriangleAmp_31) || \
                                                         ((VALUE) == DAC_TriangleAmp_63) || \
                                                         ((VALUE) == DAC_TriangleAmp_127) || \
                                                         ((VALUE) == DAC_TriangleAmp_255) || \
                                                         ((VALUE) == DAC_TriangleAmp_511) || \
                                                         ((VALUE) == DAC_TriangleAmp_1023) || \
                                                         ((VALUE) == DAC_TriangleAmp_2047) || \
                                                         ((VALUE) == DAC_TriangleAmp_4095))
/**
  * @}
  */

/** @defgroup DAC_output_buffer
  * @{
  */

#define DAC_OutputBuffer_Enable             ((uint32_t)0x00000000)
#define DAC_OutputBuffer_Disable            ((uint32_t)0x00000002)
#define IS_DAC_OUTPUT_BUFFER_STATE(STATE)   (((STATE) == DAC_OutputBuffer_Enable) || \
                                             ((STATE) == DAC_OutputBuffer_Disable))
/**
  * @}
  */

/** @defgroup DAC_Channel_selection
  * @{
  */

#define DAC_Channel_1                       ((uint32_t)0x00000000)
#define DAC_Channel_2                       ((uint32_t)0x00000010)
#define IS_DAC_CHANNEL(CHANNEL)             (((CHANNEL) == DAC_Channel_1) || \
                                             ((CHANNEL) == DAC_Channel_2))
/**
  * @}
  */

/** @defgroup DAC_data_alignment
  * @{
  */

#define DAC_Align_12b_Right                 ((uint32_t)0x00000000)
#define DAC_Align_12b_Left                  ((uint32_t)0x00000004)
#define DAC_Align_8b_Right                  ((uint32_t)0x00000008)
#define IS_DAC_ALIGN(ALIGN)                 (((ALIGN) == DAC_Align_12b_Right) || \
                                             ((ALIGN) == DAC_Align_12b_Left) || \
                                             ((ALIGN) == DAC_Align_8b_Right))
/**
  * @}
  */

/** @defgroup DAC_wave_generation
  * @{
  */

#define DAC_Wave_Noise                      ((uint32_t)0x00000040)
#define DAC_Wave_Triangle                   ((uint32_t)0x00000080)
#define IS_DAC_WAVE(WAVE)                   (((WAVE) == DAC_Wave_Noise) || \
                                             ((WAVE) == DAC_Wave_Triangle))
/**
  * @}
  */

/** @defgroup DAC_data
  * @{
  */

#define IS_DAC_DATA(DATA)                   ((DATA) <= 0xFFF0)
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

void DAC_Reset(void);
void DAC_Init(uint32_t DAC_Channel, DAC_InitType* DAC_InitStruct);
void DAC_StructInit(DAC_InitType* DAC_InitStruct);
void DAC_Ctrl(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_DMACtrl(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_SoftwareTriggerCtrl(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_DualSoftwareTriggerCtrl(FunctionalState NewState);
void DAC_WaveGenerationCtrl(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState);
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1);
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel);

#ifdef __cplusplus
}
#endif

#endif /*__AT32F4xx_DAC_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


