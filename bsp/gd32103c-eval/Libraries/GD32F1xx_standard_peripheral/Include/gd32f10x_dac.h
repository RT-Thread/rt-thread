/**
  ******************************************************************************
  * @brief   DAC header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_DAC_H
#define __GD32F10X_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
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
typedef struct {
    uint32_t DAC_Trigger;                      /*!< External trigger of the selected DAC channel.
                                                    This parameter can be a value of @ref DAC_Trigger */
    uint32_t DAC_WaveType;                     /*!< Wave type of the DAC channel, noise waves or triangle waves.
                                                    This parameter can be a value of @ref DAC_wave_type */
    uint32_t DAC_LFSRNoise_AmplitudeTriangle;  /*!< The LFSR mask for noise wave generation or
                                                    the maximum amplitude triangle generation for the DAC channel.
                                                    This parameter can be a value of @ref DAC_lfsrnoise_amplitudetriangle */
    uint32_t DAC_OutputBuffer;                 /*!< whether the DAC channel output buffer is enabled or disabled.
                                                    This parameter can be a value of @ref DAC_OutputBuffer */
} DAC_InitPara;

/**
  * @}
  */

/** @defgroup DAC_Exported_Constants
  * @{
  */

/** @defgroup DAC_Trigger
  * @{
  */
#define DAC_TRIGGER_NONE                ((uint32_t)0x00000000) /*!< no trigger */
#define DAC_TRIGGER_T2_TRIG             ((uint32_t)0x00000024) /*!< TIMER2 TRIG */
#define DAC_TRIGGER_T3_TRIG             ((uint32_t)0x0000000C) /*!< TIMER3 TRIG */
#define DAC_TRIGGER_T4_TRIG             ((uint32_t)0x0000002C) /*!< TIMER4 TRIG */
#define DAC_TRIGGER_T5_TRIG             ((uint32_t)0x0000001C) /*!< TIMER5 TRIG */
#define DAC_TRIGGER_T6_TRIG             ((uint32_t)0x00000004) /*!< TIMER6 TRIG */
#define DAC_TRIGGER_T7_TRIG             ((uint32_t)0x00000014) /*!< TIMER7 TRIG */
#define DAC_TRIGGER_T8_TRIG             ((uint32_t)0x0000000C) /*!< TIMER8 TRIG */
#define DAC_TRIGGER_T15_TRIG            ((uint32_t)0x0000001C) /*!< TIMER15 TRIG */
#define DAC_TRIGGER_EXTI_LINE9          ((uint32_t)0x00000034) /*!< EXTI Line9 event */
#define DAC_TRIGGER_SOFTWARE            ((uint32_t)0x0000003C) /*!< software trigger */

/**
  * @}
  */

/** @defgroup DAC_wave_type
  * @{
  */
#define DAC_WAVEGENE_NONE               ((uint32_t)0x00000000)
#define DAC_WAVEGENE_NOISE              ((uint32_t)0x00000040)
#define DAC_WAVEGENE_TRIANGLE           ((uint32_t)0x00000080)

/**
  * @}
  */

/** @defgroup DAC_lfsrnoise_amplitudetriangle
  * @{
  */
#define DAC_LFSR_BIT0                   ((uint32_t)0x00000000) /*!< LFSR bit0 for noise wave generation */
#define DAC_LFSR_BITS1_0                ((uint32_t)0x00000100) /*!< LFSR bit[1:0] for noise wave generation */
#define DAC_LFSR_BITS2_0                ((uint32_t)0x00000200) /*!< LFSR bit[2:0] for noise wave generation */
#define DAC_LFSR_BITS3_0                ((uint32_t)0x00000300) /*!< LFSR bit[3:0] for noise wave generation */
#define DAC_LFSR_BITS4_0                ((uint32_t)0x00000400) /*!< LFSR bit[4:0] for noise wave generation */
#define DAC_LFSR_BITS5_0                ((uint32_t)0x00000500) /*!< LFSR bit[5:0] for noise wave generation */
#define DAC_LFSR_BITS6_0                ((uint32_t)0x00000600) /*!< LFSR bit[6:0] for noise wave generation */
#define DAC_LFSR_BITS7_0                ((uint32_t)0x00000700) /*!< LFSR bit[7:0] for noise wave generation */
#define DAC_LFSR_BITS8_0                ((uint32_t)0x00000800) /*!< LFSR bit[8:0] for noise wave generation */
#define DAC_LFSR_BITS9_0                ((uint32_t)0x00000900) /*!< LFSR bit[9:0] for noise wave generation */
#define DAC_LFSR_BITS10_0               ((uint32_t)0x00000A00) /*!< LFSR bit[10:0] for noise wave generation */
#define DAC_LFSR_BITS11_0               ((uint32_t)0x00000B00) /*!< LFSR bit[11:0] for noise wave generation */
#define DAC_AMPLITUDETRIANGLE_1         ((uint32_t)0x00000000) /*!< max triangle amplitude: 1 */
#define DAC_AMPLITUDETRIANGLE_3         ((uint32_t)0x00000100) /*!< max triangle amplitude: 3 */
#define DAC_AMPLITUDETRIANGLE_7         ((uint32_t)0x00000200) /*!< max triangle amplitude: 7 */
#define DAC_AMPLITUDETRIANGLE_15        ((uint32_t)0x00000300) /*!< max triangle amplitude: 15 */
#define DAC_AMPLITUDETRIANGLE_31        ((uint32_t)0x00000400) /*!< max triangle amplitude: 31 */
#define DAC_AMPLITUDETRIANGLE_63        ((uint32_t)0x00000500) /*!< max triangle amplitude: 63 */
#define DAC_AMPLITUDETRIANGLE_127       ((uint32_t)0x00000600) /*!< max triangle amplitude: 127 */
#define DAC_AMPLITUDETRIANGLE_255       ((uint32_t)0x00000700) /*!< max triangle amplitude: 255 */
#define DAC_AMPLITUDETRIANGLE_511       ((uint32_t)0x00000800) /*!< max triangle amplitude: 511 */
#define DAC_AMPLITUDETRIANGLE_1023      ((uint32_t)0x00000900) /*!< max triangle amplitude: 1023 */
#define DAC_AMPLITUDETRIANGLE_2047      ((uint32_t)0x00000A00) /*!< max triangle amplitude: 2047 */
#define DAC_AMPLITUDETRIANGLE_4095      ((uint32_t)0x00000B00) /*!< max triangle amplitude: 4095 */

/**
  * @}
  */
/** @defgroup DAC_OutputBuffer
  * @{
  */
#define DAC_OUTPUTBUFFER_ENABLE         ((uint32_t)0x00000000)
#define DAC_OUTPUTBUFFER_DISABLE        ((uint32_t)0x00000002)

/**
  * @}
  */

/** @defgroup DAC_Channel_selection
  * @{
  */
#define DAC_CHANNEL_1                   ((uint32_t)0x00000000)
#define DAC_CHANNEL_2                   ((uint32_t)0x00000010)

/**
  * @}
  */

/** @defgroup DAC_data_alignment
  * @{
  */
#define DAC_ALIGN_12B_R                 ((uint32_t)0x00000000)
#define DAC_ALIGN_12B_L                 ((uint32_t)0x00000004)
#define DAC_ALIGN_8B_R                  ((uint32_t)0x00000008)

/**
  * @}
  */

/** @defgroup DAC_wave_generation
  * @{
  */
#define DAC_WAVE_NOISE                  ((uint32_t)0x00000040)
#define DAC_WAVE_TRIANGLE               ((uint32_t)0x00000080)

/**
  * @}
  */

/** @defgroup DAC_interrupts_definition
  * @{
  */
#define DAC_INT_DMAUDR                  ((uint32_t)0x00002000)

/**
  * @}
  */

/** @defgroup DAC_flags_definition
  * @{
  */
#define DAC_FLAG_DMAUDR                 ((uint32_t)0x00002000)

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup DAC_Exported_Functions
  * @{
  */
void DAC_DeInit(DAC_InitPara *DAC_InitParaStruct);
void DAC_Init(uint32_t DAC_Channel, DAC_InitPara *DAC_InitParaStruct);
void DAC_Enable(uint32_t DAC_Channel, TypeState NewValue);
void DAC_IntConfig(uint32_t DAC_Channel, TypeState NewValue);
void DAC_SoftwareTrigger_Enable(uint32_t DAC_Channel, TypeState NewValue);
void DAC_DualSoftwareTrigger_Enable(TypeState NewValue);
void DAC_WaveGeneration_Enable(uint32_t DAC_Channel, uint32_t DAC_Wave, TypeState NewValue);
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1);
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel);
void DAC_DMA_Enable(uint32_t DAC_Channel, TypeState NewValue);
#ifdef __cplusplus
}
#endif

#endif /*__GD32F10X_DAC_H */

/**
  * @}
  */

/**
  * @}
  */
/**
  * @}
  */
