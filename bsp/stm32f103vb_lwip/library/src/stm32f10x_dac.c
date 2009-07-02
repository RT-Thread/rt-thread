/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_dac.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the DAC firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_dac.h"
#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* DAC EN mask */
#define CR_EN_Set                  ((u32)0x00000001)

/* DAC DMAEN mask */
#define CR_DMAEN_Set               ((u32)0x00001000)

/* CR register Mask */
#define CR_CLEAR_Mask              ((u32)0x00000FFE)

/* DAC SWTRIG mask */
#define SWTRIGR_SWTRIG_Set         ((u32)0x00000001)

/* DAC Dual Channels SWTRIG masks */
#define DUAL_SWTRIG_Set            ((u32)0x00000003)
#define DUAL_SWTRIG_Reset          ((u32)0xFFFFFFFC)

/* DHR registers offsets */
#define DHR12R1_Offset             ((u32)0x00000008)
#define DHR12R2_Offset             ((u32)0x00000014)
#define DHR12RD_Offset             ((u32)0x00000020)

/* DOR register offset */
#define DOR_Offset                 ((u32)0x0000002C)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : DAC_DeInit
* Description    : Deinitializes the DAC peripheral registers to their default
*                  reset values.
* Input          : None.
* Output         : None
* Return         : None
*******************************************************************************/
void DAC_DeInit(void)
{
  /* Enable DAC reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, ENABLE);
  /* Release DAC from reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, DISABLE);
}

/*******************************************************************************
* Function Name  : DAC_Init
* Description    : Initializes the DAC peripheral according to the specified 
*                  parameters in the DAC_InitStruct.
* Input          : - DAC_Channel: the selected DAC channel. 
*                    This parameter can be one of the following values:
*                       - DAC_Channel_1: DAC Channel1 selected
*                       - DAC_Channel_2: DAC Channel2 selected
*                  - DAC_InitStruct: pointer to a DAC_InitTypeDef structure that
*                    contains the configuration information for the specified
*                    DAC channel.
* Output         : None
* Return         : None
*******************************************************************************/
void DAC_Init(u32 DAC_Channel, DAC_InitTypeDef* DAC_InitStruct)
{
  u32 tmpreg1 = 0, tmpreg2 = 0;

  /* Check the DAC parameters */
  assert_param(IS_DAC_TRIGGER(DAC_InitStruct->DAC_Trigger));
  assert_param(IS_DAC_GENERATE_WAVE(DAC_InitStruct->DAC_WaveGeneration));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude));
  assert_param(IS_DAC_OUTPUT_BUFFER_STATE(DAC_InitStruct->DAC_OutputBuffer));

/*---------------------------- DAC CR Configuration --------------------------*/
  /* Get the DAC CR value */
  tmpreg1 = DAC->CR;
  /* Clear BOFFx, TENx, TSELx, WAVEx and MAMPx bits */
  tmpreg1 &= ~(CR_CLEAR_Mask << DAC_Channel);
  /* Configure for the selected DAC channel: buffer output, trigger, wave genration,
     mask/amplitude for wave genration */
  /* Set TSELx and TENx bits according to DAC_Trigger value */
  /* Set WAVEx bits according to DAC_WaveGeneration value */
  /* Set MAMPx bits according to DAC_LFSRUnmask_TriangleAmplitude value */ 
  /* Set BOFFx bit according to DAC_OutputBuffer value */   
  tmpreg2 = (DAC_InitStruct->DAC_Trigger | DAC_InitStruct->DAC_WaveGeneration |
             DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude | DAC_InitStruct->DAC_OutputBuffer);
  /* Calculate CR register value depending on DAC_Channel */
  tmpreg1 |= tmpreg2 << DAC_Channel;
  /* Write to DAC CR */
  DAC->CR = tmpreg1;
}

/*******************************************************************************
* Function Name  : DAC_StructInit
* Description    : Fills each DAC_InitStruct member with its default value.
* Input          : - DAC_InitStruct : pointer to a DAC_InitTypeDef structure
*                    which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
{
/*--------------- Reset DAC init structure parameters values -----------------*/
  /* Initialize the DAC_Trigger member */
  DAC_InitStruct->DAC_Trigger = DAC_Trigger_None;

  /* Initialize the DAC_WaveGeneration member */
  DAC_InitStruct->DAC_WaveGeneration = DAC_WaveGeneration_None;

  /* Initialize the DAC_LFSRUnmask_TriangleAmplitude member */
  DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;

  /* Initialize the DAC_OutputBuffer member */
  DAC_InitStruct->DAC_OutputBuffer = DAC_OutputBuffer_Enable;
}

/*******************************************************************************
* Function Name  : DAC_Cmd
* Description    : Enables or disables the specified DAC channel.
* Input            - DAC_Channel: the selected DAC channel. 
*                    This parameter can be one of the following values:
*                       - DAC_Channel_1: DAC Channel1 selected
*                       - DAC_Channel_2: DAC Channel2 selected
*                  - NewState: new state of the DAC channel. 
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void DAC_Cmd(u32 DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel */
    DAC->CR |= CR_EN_Set << DAC_Channel;
  }
  else
  {
    /* Disable the selected DAC channel */
    DAC->CR &= ~(CR_EN_Set << DAC_Channel);
  }
}

/*******************************************************************************
* Function Name  : DAC_DMACmd
* Description    : Enables or disables the specified DAC channel DMA request.
* Input            - DAC_Channel: the selected DAC channel. 
*                    This parameter can be one of the following values:
*                       - DAC_Channel_1: DAC Channel1 selected
*                       - DAC_Channel_2: DAC Channel2 selected
*                  - NewState: new state of the selected DAC channel DMA request.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void DAC_DMACmd(u32 DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel DMA request */
    DAC->CR |= CR_DMAEN_Set << DAC_Channel;
  }
  else
  {
    /* Disable the selected DAC channel DMA request */
    DAC->CR &= ~(CR_DMAEN_Set << DAC_Channel);
  }
}

/*******************************************************************************
* Function Name  : DAC_SoftwareTriggerCmd
* Description    : Enables or disables the selected DAC channel software trigger.
* Input            - DAC_Channel: the selected DAC channel. 
*                    This parameter can be one of the following values:
*                       - DAC_Channel_1: DAC Channel1 selected
*                       - DAC_Channel_2: DAC Channel2 selected
*                  - NewState: new state of the selected DAC channel software trigger.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void DAC_SoftwareTriggerCmd(u32 DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable software trigger for the selected DAC channel */
    DAC->SWTRIGR |= SWTRIGR_SWTRIG_Set << (DAC_Channel >> 4);
  }
  else
  {
    /* Disable software trigger for the selected DAC channel */
    DAC->SWTRIGR &= ~(SWTRIGR_SWTRIG_Set << (DAC_Channel >> 4));
  }
}

/*******************************************************************************
* Function Name  : DAC_DualSoftwareTriggerCmd
* Description    : Enables or disables simultaneously the two DAC channels software
*                  triggers.
* Input            - NewState: new state of the DAC channels software triggers.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable software trigger for both DAC channels */
    DAC->SWTRIGR |= DUAL_SWTRIG_Set ;
  }
  else
  {
    /* Disable software trigger for both DAC channels */
    DAC->SWTRIGR &= DUAL_SWTRIG_Reset;
  }
}

/*******************************************************************************
* Function Name  : DAC_WaveGenerationCmd
* Description    : Enables or disables the selected DAC channel wave generation.
* Input            - DAC_Channel: the selected DAC channel. 
*                    This parameter can be one of the following values:
*                       - DAC_Channel_1: DAC Channel1 selected
*                       - DAC_Channel_2: DAC Channel2 selected
*                  - DAC_Wave: Specifies the wave type to enable or disable.
*                    This parameter can be one of the following values:
*                       - DAC_Wave_Noise: noise wave generation
*                       - DAC_Wave_Triangle: triangle wave generation
*                  - NewState: new state of the selected DAC channel wave generation.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void DAC_WaveGenerationCmd(u32 DAC_Channel, u32 DAC_Wave, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_WAVE(DAC_Wave)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected wave generation for the selected DAC channel */
    DAC->CR |= DAC_Wave << DAC_Channel;
  }
  else
  {
    /* Disable the selected wave generation for the selected DAC channel */
    DAC->CR &= ~(DAC_Wave << DAC_Channel);
  }
}

/*******************************************************************************
* Function Name  : DAC_SetChannel1Data
* Description    : Set the specified data holding register value for DAC channel1.
* Input          : - DAC_Align: Specifies the data alignement for DAC channel1.
*                    This parameter can be one of the following values:
*                       - DAC_Align_8b_R: 8bit right data alignement selected
*                       - DAC_Align_12b_L: 12bit left data alignement selected
*                       - DAC_Align_12b_R: 12bit right data alignement selected
*                  - Data : Data to be loaded in the selected data holding 
*                    register.
* Output         : None
* Return         : None
*******************************************************************************/
void DAC_SetChannel1Data(u32 DAC_Align, u16 Data)
{
  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data));

  /* Set the DAC channel1 selected data holding register */
  *((vu32 *)(DAC_BASE + DHR12R1_Offset + DAC_Align)) = (u32)Data;
}

/*******************************************************************************
* Function Name  : DAC_SetChannel2Data
* Description    : Set the specified data holding register value for DAC channel2.
* Input          : - DAC_Align: Specifies the data alignement for DAC channel2.
*                    This parameter can be one of the following values:
*                       - DAC_Align_8b_R: 8bit right data alignement selected
*                       - DAC_Align_12b_L: 12bit left data alignement selected
*                       - DAC_Align_12b_R: 12bit right data alignement selected
*                  - Data : Data to be loaded in the selected data holding 
*                    register.
* Output         : None
* Return         : None
*******************************************************************************/
void DAC_SetChannel2Data(u32 DAC_Align, u16 Data)
{
  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data));

  /* Set the DAC channel2 selected data holding register */
  *((vu32 *)(DAC_BASE + DHR12R2_Offset + DAC_Align)) = (u32)Data;
}

/*******************************************************************************
* Function Name  : DAC_SetDualChannelData
* Description    : Set the specified data holding register value for dual channel
*                  DAC.
* Input          : - DAC_Align: Specifies the data alignement for dual channel DAC.
*                    This parameter can be one of the following values:
*                       - DAC_Align_8b_R: 8bit right data alignement selected
*                       - DAC_Align_12b_L: 12bit left data alignement selected
*                       - DAC_Align_12b_R: 12bit right data alignement selected
*                  - Data2: Data for DAC Channel2 to be loaded in the selected data 
*                    holding register.
*                  - Data1: Data for DAC Channel1 to be loaded in the selected data 
*                    holding register.
* Output         : None
* Return         : None
*******************************************************************************/
void DAC_SetDualChannelData(u32 DAC_Align, u16 Data2, u16 Data1)
{
  u32 data = 0;

  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data1));
  assert_param(IS_DAC_DATA(Data2));
  
  /* Calculate and set dual DAC data holding register value */
  if (DAC_Align == DAC_Align_8b_R)
  {
    data = ((u32)Data2 << 8) | Data1; 
  }
  else
  {
    data = ((u32)Data2 << 16) | Data1;
  }

  /* Set the dual DAC selected data holding register */
  *((vu32 *)(DAC_BASE + DHR12RD_Offset + DAC_Align)) = data;
}

/*******************************************************************************
* Function Name  : DAC_GetDataOutputValue
* Description    : Returns the last data output value of the selected DAC cahnnel.
* Input            - DAC_Channel: the selected DAC channel. 
*                    This parameter can be one of the following values:
*                       - DAC_Channel_1: DAC Channel1 selected
*                       - DAC_Channel_2: DAC Channel2 selected
* Output         : None
* Return         : The selected DAC channel data output value.
*******************************************************************************/
u16 DAC_GetDataOutputValue(u32 DAC_Channel)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));

  /* Returns the DAC channel data output register value */
  return (u16) (*(vu32*)(DAC_BASE + DOR_Offset + ((u32)DAC_Channel >> 2)));
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
