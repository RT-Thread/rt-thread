/********************************** (C) COPYRIGHT  *******************************
* File Name          : ch32f20x_dac.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : This file provides all the DAC firmware functions.
****************************************************************************************/
#include "ch32f20x_dac.h"
#include "ch32f20x_rcc.h"

/* CTLR register Mask */
#define CTLR_CLEAR_MASK            ((uint32_t)0x00000FFE)

/* DAC Dual Channels SWTR masks */
#define DUAL_SWTR_SET              ((uint32_t)0x00000003)
#define DUAL_SWTR_RESET            ((uint32_t)0xFFFFFFFC)

/* DHR registers offsets */
#define DHR12R1_OFFSET             ((uint32_t)0x00000008)
#define DHR12R2_OFFSET             ((uint32_t)0x00000014)
#define DHR12RD_OFFSET             ((uint32_t)0x00000020)

/* DOR register offset */
#define DOR_OFFSET                 ((uint32_t)0x0000002C)

	
/******************************************************************************************
* Function Name  : DAC_DeInit
* Description    : Deinitializes the DAC peripheral registers to their default reset values.
* Input          : None
* Return         : None
*******************************************************************************************/	
void DAC_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, DISABLE);
}

/******************************************************************************************
* Function Name  : DAC_Init
* Description    : Initializes the DAC peripheral according to the specified parameters in 
*                  the DAC_InitStruct.
* Input          : DAC_Channel:the selected DAC channel.
*                     DAC_Channel_1: DAC Channel1 selected
*                     DAC_Channel_2: DAC Channel2 selected
*                  DAC_InitStruct:pointer to a DAC_InitTypeDef structure.
* Return         : None
*******************************************************************************************/
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;

  tmpreg1 = DAC->CTLR;
  tmpreg1 &= ~(CTLR_CLEAR_MASK << DAC_Channel);   
  tmpreg2 = (DAC_InitStruct->DAC_Trigger | DAC_InitStruct->DAC_WaveGeneration |
             DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude | DAC_InitStruct->DAC_OutputBuffer);
  tmpreg1 |= tmpreg2 << DAC_Channel;
  DAC->CTLR = tmpreg1;
}

/******************************************************************************************
* Function Name  : DAC_StructInit
* Description    : Fills each DAC_InitStruct member with its default value.
* Input          : DAC_InitStruct:pointer to a DAC_InitTypeDef structure which will be initialized.
* Return         : None
*******************************************************************************************/
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
{
  DAC_InitStruct->DAC_Trigger = DAC_Trigger_None;
  DAC_InitStruct->DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
  DAC_InitStruct->DAC_OutputBuffer = DAC_OutputBuffer_Enable;
}

/******************************************************************************************
* Function Name  : DAC_Cmd
* Description    : Enables or disables the specified DAC channel.
* Input          : DAC_Channel: the selected DAC channel.
*                    DAC_Channel_1: DAC Channel1 selected
*                    DAC_Channel_2: DAC Channel2 selected
*                  NewState:new state of the DAC channel(ENABLE or DISABLE). 
* Return         : None
*******************************************************************************************/
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DAC->CTLR |= (DAC_EN1 << DAC_Channel);
  }
  else
  {
    DAC->CTLR &= ~(DAC_EN1 << DAC_Channel);
  }
}

/******************************************************************************************
* Function Name  : DAC_DMACmd
* Description    : Enables or disables the specified DAC channel DMA request.
* Input          : DAC_Channel: the selected DAC channel.
*                    DAC_Channel_1: DAC Channel1 selected
*                    DAC_Channel_2: DAC Channel2 selected
*                  NewState:new state of the DAC channel(ENABLE or DISABLE). 
* Return         : None
*******************************************************************************************/
void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DAC->CTLR |= (DAC_DMAEN1 << DAC_Channel);
  }
  else
  {
    DAC->CTLR &= ~(DAC_DMAEN1 << DAC_Channel);
  }
}

/******************************************************************************************
* Function Name  : DAC_SoftwareTriggerCmd
* Description    : Enables or disables the selected DAC channel software trigger.
* Input          : DAC_Channel: the selected DAC channel.
*                    DAC_Channel_1: DAC Channel1 selected
*                    DAC_Channel_2: DAC Channel2 selected
*                  NewState:new state of the DAC channel(ENABLE or DISABLE). 
* Return         : None
*******************************************************************************************/
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DAC->SWTR |= (uint32_t)DAC_SWTRIG1 << (DAC_Channel >> 4);
  }
  else
  {
    DAC->SWTR &= ~((uint32_t)DAC_SWTRIG1 << (DAC_Channel >> 4));
  }
}

/******************************************************************************************
* Function Name  : DAC_DualSoftwareTriggerCmd
* Description    : Enables or disables the two DAC channel software trigger.
* Input          : NewState:new state of the DAC channel(ENABLE or DISABLE).
* Return         : None
*******************************************************************************************/
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DAC->SWTR |= DUAL_SWTR_SET ;
  }
  else
  {
    DAC->SWTR &= DUAL_SWTR_RESET;
  }
}

/******************************************************************************************
* Function Name  : DAC_WaveGenerationCmd
* Description    : Enables or disables the selected DAC channel wave generation.
* Input          : DAC_Channel: the selected DAC channel.
*                    DAC_Channel_1: DAC Channel1 selected
*                    DAC_Channel_2: DAC Channel2 selected
*                  DAC_Wave: Specifies the wave type to enable or disable.
*                    DAC_Wave_Noise: noise wave generation
*                    DAC_Wave_Triangle: triangle wave generation
*                  NewState:new state of the DAC channel(ENABLE or DISABLE). 
* Return         : None
*******************************************************************************************/
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DAC->CTLR |= DAC_Wave << DAC_Channel;
  }
  else
  {
    DAC->CTLR &= ~(DAC_Wave << DAC_Channel);
  }
}

/******************************************************************************************
* Function Name  : DAC_SetChannel1Data
* Description    : Set the specified data holding register value for DAC channel1.
* Input          : DAC_Align: Specifies the data alignment for DAC channel1.
*                    DAC_Align_8b_R: 8bit right data alignment selected
*                    DAC_Align_12b_L: 12bit left data alignment selected
*                    DAC_Align_12b_R: 12bit right data alignment selected
*                  Data : Data to be loaded in the selected data holding register. 
* Return         : None
*******************************************************************************************/
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data)
{  
  __IO uint32_t tmp = 0;
    
  tmp = (uint32_t)DAC_BASE; 
  tmp += DHR12R1_OFFSET + DAC_Align;

  *(__IO uint32_t *) tmp = Data;
}

/******************************************************************************************
* Function Name  : DAC_SetChannel2Data
* Description    : Set the specified data holding register value for DAC channel2.
* Input          : DAC_Align: Specifies the data alignment for DAC channel1.
*                    DAC_Align_8b_R: 8bit right data alignment selected
*                    DAC_Align_12b_L: 12bit left data alignment selected
*                    DAC_Align_12b_R: 12bit right data alignment selected
*                  Data : Data to be loaded in the selected data holding register. 
* Return         : None
*******************************************************************************************/
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data)
{
  __IO uint32_t tmp = 0;

  tmp = (uint32_t)DAC_BASE;
  tmp += DHR12R2_OFFSET + DAC_Align;

  *(__IO uint32_t *)tmp = Data;
}

/******************************************************************************************
* Function Name  : DAC_SetDualChannelData
* Description    : Set the specified data holding register value for two DAC.
* Input          : DAC_Align: Specifies the data alignment for DAC channel1.
*                    DAC_Align_8b_R: 8bit right data alignment selected
*                    DAC_Align_12b_L: 12bit left data alignment selected
*                    DAC_Align_12b_R: 12bit right data alignment selected
*                  Data1 : Data for DAC Channel1.
*                  Data2 : Data for DAC Channel2
* Return         : None
*******************************************************************************************/
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1)
{
  uint32_t data = 0, tmp = 0;

  if (DAC_Align == DAC_Align_8b_R)
  {
    data = ((uint32_t)Data2 << 8) | Data1;
  }
  else
  {
    data = ((uint32_t)Data2 << 16) | Data1;
  }

  tmp = (uint32_t)DAC_BASE;
  tmp += DHR12RD_OFFSET + DAC_Align;

  *(__IO uint32_t *)tmp = data;
}

/******************************************************************************************
* Function Name  : DAC_GetDataOutputValue
* Description    : Returns the last data output value of the selected DAC channel.
* Input          : DAC_Channel: the selected DAC channel.
*                    DAC_Channel_1: DAC Channel1 selected
*                    DAC_Channel_2: DAC Channel2 selected
* Return         : None
*******************************************************************************************/
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel)
{
  __IO uint32_t tmp = 0;
  
  tmp = (uint32_t) DAC_BASE ;
  tmp += DOR_OFFSET + ((uint32_t)DAC_Channel >> 2);
  
  return (uint16_t) (*(__IO uint32_t*) tmp);
}



