////////////////////////////////////////////////////////////////////////////////
/// @file     hal_dac.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE DAC FIRMWARE FUNCTIONS.
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
#define _HAL_DAC_C_

// Files includes
#include "hal_dac.h"
#include "hal_rcc.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup DAC_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup DAC_Exported_Functions
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the DAC peripheral registers to their default reset values.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DAC_DeInit(void)
{
    exRCC_APB1PeriphReset(RCC_APB1ENR_DAC);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes the DAC peripheral according to the specified parameters in the DAC_InitStruct.
/// @param channel: the selected DAC channel.
/// @param DAC_InitStruct: pointer to a DAC_InitTypeDef structure that contains the configuration information for the specified
/// DAC channel.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DAC_Init(emDACCH_TypeDef channel, DAC_InitTypeDef* init_struct)
{
    DAC->CR &= ~((DAC_CR_BOFF1 | DAC_CR_TEN1 | DAC_CR_TSEL1 | DAC_CR_WAVE1 | DAC_CR_MAMP1) << channel);
    DAC->CR |= (((u32)(init_struct->DAC_Trigger) | (u32)(init_struct->DAC_WaveGeneration) |
                 (u32)(init_struct->DAC_LFSRUnmask_TriangleAmplitude) | (u32)(init_struct->DAC_OutputBuffer))
                << channel);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Fills each DAC_InitStruct member with its default value.
/// @param DAC_InitStruct : pointer to a DAC_InitTypeDef structure which will be initialized.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DAC_StructInit(DAC_InitTypeDef* init_struct)
{
    init_struct->DAC_Trigger                      = DAC_Trigger_None;
    init_struct->DAC_WaveGeneration               = DAC_WaveGeneration_None;
    init_struct->DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1;
    init_struct->DAC_OutputBuffer                 = DAC_OutputBuffer_Enable;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified DAC channel.
/// @param channel: the selected DAC channel.
/// @param state: new state of the DAC channel.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DAC_Cmd(emDACCH_TypeDef channel, FunctionalState state)
{
    (state) ? (DAC->CR |= DAC_CR_EN1 << channel) : (DAC->CR &= ~(DAC_CR_EN1 << channel));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified DAC channel DMA request.
/// @param channel: the selected DAC channel.
/// @param state: new state of the selected DAC channel DMA request.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DAC_DMACmd(emDACCH_TypeDef channel, FunctionalState state)
{
    (state) ? (DAC->CR |= DAC_CR_DMAEN1 << channel) : (DAC->CR &= ~(DAC_CR_DMAEN1 << channel));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the selected DAC channel software trigger.
/// @param channel: the selected DAC channel.
/// @param state: new state of the selected DAC channel software trigger.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DAC_SoftwareTriggerCmd(emDACCH_TypeDef channel, FunctionalState state)
{
    (state) ? (DAC->SWTRIGR |= (DAC_SWTRIGR_SWTRIG1 << (channel >> 4)))
    : (DAC->SWTRIGR &= ~(DAC_SWTRIGR_SWTRIG1 << (channel >> 4)));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables simultaneously the two DAC channels software triggers.
/// @param state: new state of the DAC channels software triggers.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DAC_DualSoftwareTriggerCmd(FunctionalState state)
{
    (state) ? (DAC->SWTRIGR |= (DAC_SWTRIGR_SWTRIG1 | DAC_SWTRIGR_SWTRIG2))
    : (DAC->SWTRIGR &= ~(DAC_SWTRIGR_SWTRIG1 | DAC_SWTRIGR_SWTRIG2));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the selected DAC channel wave generation.
/// @param channel: the selected DAC channel.
/// @param wave: Specifies the wave type to enable or disable.
/// @param state: new state of the selected DAC channel wave generation.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DAC_WaveGenerationCmd(emDACCH_TypeDef channel, emDACWAVE_TypeDef wave, FunctionalState state)
{
    (state) ? (DAC->CR |= wave << channel) : (DAC->CR &= ~(wave << channel));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the specified data holding register value for DAC channel1.
/// @param alignement: Specifies the data alignement for DAC channel1.
/// @param data : data to be loaded in the selected data holding register.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DAC_SetChannel1Data(emDACALIGN_TypeDef alignement, u16 data)
{
    *((u32*)(DAC_BASE + DHR12R1_Offset + alignement)) = data;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the specified data holding register value for DAC channel2.
/// @param alignement: Specifies the data alignement for DAC channel2.
/// @param data : data to be loaded in the selected data holding
///   register.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DAC_SetChannel2Data(emDACALIGN_TypeDef alignement, u16 data)
{
    *((u32*)(DAC_BASE + DHR12R2_Offset + alignement)) = data;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the specified data holding register value for dual channel DAC.
/// @param alignement: Specifies the data alignement for dual channel DAC.
/// @param data2: data for DAC Channel2 to be loaded in the selected data holding register.
/// @param data1: data for DAC Channel1 to be loaded in the selected data holding register.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DAC_SetDualChannelData(emDACALIGN_TypeDef alignement, u16 data2, u16 data1)
{
    u32 data = ((alignement == DAC_Align_8b_R) ? ((data2 << 8) | data1) : ((data2 << 16) | data1));
    *((u32*)(DAC_BASE + DHR12RD_Offset + alignement)) = data;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the last data output value of the selected DAC cahnnel.
/// @param channel: the selected DAC channel.
/// @retval  The selected DAC channel data output value.
////////////////////////////////////////////////////////////////////////////////
u16 DAC_GetDataOutputValue(emDACCH_TypeDef channel)
{
    return (*(vu32*)(DAC_BASE + DOR_Offset + (channel >> 2)));
}
/// @}

/// @}

/// @}


