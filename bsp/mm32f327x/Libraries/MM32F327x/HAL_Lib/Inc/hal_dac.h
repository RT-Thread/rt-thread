////////////////////////////////////////////////////////////////////////////////
/// @file     hal_dac.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE DAC
///           FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#ifndef __HAL_DAC_H
#define __HAL_DAC_H

// Files includes
#include "types.h"
#include "reg_dac.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup DAC_HAL
/// @brief DAC HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup DAC_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_Trigger_Selection
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DAC_Trigger_None     = 0x00000000,
    DAC_Trigger_T1_TRIG  = (DAC_CR_TSEL1_TIM1_TRIG | DAC_CR_TEN1),
    DAC_Trigger_T3_TRIG  = (DAC_CR_TSEL1_TIM3_TRIG | DAC_CR_TEN1),
    DAC_Trigger_T2_TRIG  = (DAC_CR_TSEL1_TIM2_TRIG | DAC_CR_TEN1),
    DAC_Trigger_T4_TRIG  = (DAC_CR_TSEL1_TIM4_TRIG | DAC_CR_TEN1),
    DAC_Trigger_Ext_IT9  = (DAC_CR_TSEL1_EXTI9 | DAC_CR_TEN1),
    DAC_Trigger_Software = (DAC_CR_TSEL1_SOFTWARE)
} emDACTRIG_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_Wave_Generation
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DAC_WaveGeneration_None     = DAC_CR_WAVE1_NONE,
    DAC_WaveGeneration_Noise    = DAC_CR_WAVE1_NOISE,
    DAC_WaveGeneration_Triangle = DAC_CR_WAVE1_TRIANGLE
} emDACWAVE_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_Mask_Amplitude
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DAC_TriangleAmplitude_1    = DAC_CR_MAMP1_1,
    DAC_TriangleAmplitude_3    = DAC_CR_MAMP1_3,
    DAC_TriangleAmplitude_7    = DAC_CR_MAMP1_7,
    DAC_TriangleAmplitude_15   = DAC_CR_MAMP1_15,
    DAC_TriangleAmplitude_31   = DAC_CR_MAMP1_31,
    DAC_TriangleAmplitude_63   = DAC_CR_MAMP1_63,
    DAC_TriangleAmplitude_127  = DAC_CR_MAMP1_127,
    DAC_TriangleAmplitude_255  = DAC_CR_MAMP1_255,
    DAC_TriangleAmplitude_511  = DAC_CR_MAMP1_511,
    DAC_TriangleAmplitude_1023 = DAC_CR_MAMP1_1023,
    DAC_TriangleAmplitude_2047 = DAC_CR_MAMP1_2047,
    DAC_TriangleAmplitude_4095 = DAC_CR_MAMP1_4095
} emDACAMP_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief channel
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DAC_Channel_1,                                                              ///< DAC channel 1
    DAC_Channel_2 = (u32)0x00000010                                             ///< DAC Channel 2
} emDACCH_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_Data_Alignement
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DAC_Align_12b_R = ((u32)0x00000000),
    DAC_Align_12b_L = ((u32)0x00000004),
    DAC_Align_8b_R  = ((u32)0x00000008)
} emDACALIGN_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_Output_Buffer
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DAC_OutputBuffer_Enable  = 0x00000000,                                      ///< DAC output buffer enable
    DAC_OutputBuffer_Disable = DAC_CR_BOFF1                                     ///< DAC output buffer disable
} emDACBOFF_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  DAC Init structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    emDACTRIG_TypeDef DAC_Trigger;
    emDACWAVE_TypeDef DAC_WaveGeneration;
    emDACAMP_TypeDef  DAC_LFSRUnmask_TriangleAmplitude;
    emDACBOFF_TypeDef DAC_OutputBuffer;
} DAC_InitTypeDef;

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup DAC_Exported_Constants
/// @{
#define DHR12R1_Offset  ((u32)0x00000008)
#define DHR12R2_Offset  ((u32)0x00000014)
#define DHR12RD_Offset  ((u32)0x00000020)
#define DOR_Offset      ((u32)0x0000002C)

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup DAC_Exported_Variables
/// @{
#ifdef _HAL_DAC_C_
#define GLOBAL

#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup DAC_Exported_Functions
/// @{
void DAC_DeInit(void);
void DAC_Init(emDACCH_TypeDef channel, DAC_InitTypeDef* init_struct);
void DAC_StructInit(DAC_InitTypeDef* init_struct);
void DAC_Cmd(emDACCH_TypeDef channel, FunctionalState state);
void DAC_DMACmd(emDACCH_TypeDef channel, FunctionalState state);
void DAC_SoftwareTriggerCmd(emDACCH_TypeDef channel, FunctionalState state);
void DAC_DualSoftwareTriggerCmd(FunctionalState state);
void DAC_WaveGenerationCmd(emDACCH_TypeDef channel, emDACWAVE_TypeDef wave, FunctionalState state);
void DAC_SetChannel1Data(emDACALIGN_TypeDef alignement, u16 data);
void DAC_SetChannel2Data(emDACALIGN_TypeDef alignement, u16 data);
void DAC_SetDualChannelData(emDACALIGN_TypeDef alignement, u16 data2, u16 data1);

u16 DAC_GetDataOutputValue(emDACCH_TypeDef channel);

/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif // __HAL_DAC_H
////////////////////////////////////////////////////////////////////////////////

