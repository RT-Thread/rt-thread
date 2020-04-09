/**
 **************************************************************************
 * File Name    : at32f4xx_dac.c
 * Description  : at32f4xx DAC source file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_dac.h"
#include "at32f4xx_rcc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup DAC
  * @brief DAC driver modules
  * @{
  */
#if defined (AT32F403xx) || defined (AT32F403Axx) || defined (AT32F407xx)

/** @defgroup DAC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup DAC_Private_Defines
  * @{
  */

/* CTRL register Mask */
#define CTRL_CLEAR_MSK                  ((uint32_t)0x00000FFE)

/* DAC Dual Channels SWTRIG masks */
#define DUAL_SWTRIG_SET                 ((uint32_t)0x00000003)
#define DUAL_SWTRIG_RST                 ((uint32_t)0xFFFFFFFC)

/* DHR registers offsets */
#define DHR12R1_OFFSET                  ((uint32_t)0x00000008)
#define DHR12R2_OFFSET                  ((uint32_t)0x00000014)
#define DHR12RD_OFFSET                  ((uint32_t)0x00000020)

/* DOR register offset */
#define ODT_OFFSET                      ((uint32_t)0x0000002C)
/**
  * @}
  */

/** @defgroup DAC_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup DAC_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup DAC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup DAC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the DAC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void DAC_Reset(void)
{
  /* Enable DAC reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_DAC, ENABLE);
  /* Release DAC from reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_DAC, DISABLE);
}

/**
  * @brief  Initializes the DAC peripheral according to the specified
  *         parameters in the DAC_InitStruct.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: DAC Channel1 selected
  *     @arg DAC_Channel_2: DAC Channel2 selected
  * @param  DAC_InitStruct: pointer to a DAC_InitType structure that
  *        contains the configuration information for the specified DAC channel.
  * @retval None
  */
void DAC_Init(uint32_t DAC_Channel, DAC_InitType* DAC_InitStruct)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;
  /* Check the DAC parameters */
  assert_param(IS_DAC_TRIGGER(DAC_InitStruct->DAC_Trigger));
  assert_param(IS_DAC_GENERATE_WAVE(DAC_InitStruct->DAC_WaveGeneration));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude));
  assert_param(IS_DAC_OUTPUT_BUFFER_STATE(DAC_InitStruct->DAC_OutputBuffer));
  /*---------------------------- DAC CTRL Configuration --------------------------*/
  /* Get the DAC CTRL value */
  tmpreg1 = DAC->CTRL;
  /* Clear BOFFx, TENx, TSELx, WAVEx and MAMPx bits */
  tmpreg1 &= ~(CTRL_CLEAR_MSK << DAC_Channel);
  /* Configure for the selected DAC channel: buffer output, trigger, wave generation,
     mask/amplitude for wave generation */
  /* Set TSELx and TENx bits according to DAC_Trigger value */
  /* Set WAVEx bits according to DAC_WaveGeneration value */
  /* Set MAMPx bits according to DAC_LFSRUnmask_TriangleAmplitude value */
  /* Set BOFFx bit according to DAC_OutputBuffer value */
  tmpreg2 = (DAC_InitStruct->DAC_Trigger | DAC_InitStruct->DAC_WaveGeneration |
             DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude | DAC_InitStruct->DAC_OutputBuffer);
  /* Calculate CTRL register value depending on DAC_Channel */
  tmpreg1 |= tmpreg2 << DAC_Channel;
  /* Write to DAC CTRL */
  DAC->CTRL = tmpreg1;
}

/**
  * @brief  Fills each DAC_InitStruct member with its default value.
  * @param  DAC_InitStruct : pointer to a DAC_InitType structure which will
  *         be initialized.
  * @retval None
  */
void DAC_StructInit(DAC_InitType* DAC_InitStruct)
{
  /*--------------- Reset DAC init structure parameters values -----------------*/
  /* Initialize the DAC_Trigger member */
  DAC_InitStruct->DAC_Trigger = DAC_Trigger_None;
  /* Initialize the DAC_WaveGeneration member */
  DAC_InitStruct->DAC_WaveGeneration = DAC_WaveGeneration_None;
  /* Initialize the DAC_LFSRUnmask_TriangleAmplitude member */
  DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmsk_Bit0;
  /* Initialize the DAC_OutputBuffer member */
  DAC_InitStruct->DAC_OutputBuffer = DAC_OutputBuffer_Enable;
}

/**
  * @brief  Enables or disables the specified DAC channel.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: DAC Channel1 selected
  *     @arg DAC_Channel_2: DAC Channel2 selected
  * @param  NewState: new state of the DAC channel.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_Ctrl(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel */
    DAC->CTRL |= (DAC_CTRL_EN1 << DAC_Channel);
  }
  else
  {
    /* Disable the selected DAC channel */
    DAC->CTRL &= ~(DAC_CTRL_EN1 << DAC_Channel);
  }
}

/**
  * @brief  Enables or disables the specified DAC channel DMA request.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: DAC Channel1 selected
  *     @arg DAC_Channel_2: DAC Channel2 selected
  * @param  NewState: new state of the selected DAC channel DMA request.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_DMACtrl(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel DMA request */
    DAC->CTRL |= (DAC_CTRL_DMAEN1 << DAC_Channel);
  }
  else
  {
    /* Disable the selected DAC channel DMA request */
    DAC->CTRL &= ~(DAC_CTRL_DMAEN1 << DAC_Channel);
  }
}

/**
  * @brief  Enables or disables the selected DAC channel software trigger.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: DAC Channel1 selected
  *     @arg DAC_Channel_2: DAC Channel2 selected
  * @param  NewState: new state of the selected DAC channel software trigger.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_SoftwareTriggerCtrl(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable software trigger for the selected DAC channel */
    DAC->SWTRG |= (uint32_t)DAC_SWTRG_SWTRG1 << (DAC_Channel >> 4);
  }
  else
  {
    /* Disable software trigger for the selected DAC channel */
    DAC->SWTRG &= ~((uint32_t)DAC_SWTRG_SWTRG1 << (DAC_Channel >> 4));
  }
}

/**
  * @brief  Enables or disables simultaneously the two DAC channels software
  *   triggers.
  * @param  NewState: new state of the DAC channels software triggers.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_DualSoftwareTriggerCtrl(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable software trigger for both DAC channels */
    DAC->SWTRG |= DUAL_SWTRIG_SET ;
  }
  else
  {
    /* Disable software trigger for both DAC channels */
    DAC->SWTRG &= DUAL_SWTRIG_RST;
  }
}

/**
  * @brief  Enables or disables the selected DAC channel wave generation.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: DAC Channel1 selected
  *     @arg DAC_Channel_2: DAC Channel2 selected
  * @param  DAC_Wave: Specifies the wave type to enable or disable.
  *   This parameter can be one of the following values:
  *     @arg DAC_Wave_Noise: noise wave generation
  *     @arg DAC_Wave_Triangle: triangle wave generation
  * @param  NewState: new state of the selected DAC channel wave generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_WaveGenerationCtrl(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_WAVE(DAC_Wave));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected wave generation for the selected DAC channel */
    DAC->CTRL |= DAC_Wave << DAC_Channel;
  }
  else
  {
    /* Disable the selected wave generation for the selected DAC channel */
    DAC->CTRL &= ~(DAC_Wave << DAC_Channel);
  }
}

/**
  * @brief  Set the specified data holding register value for DAC channel1.
  * @param  DAC_Align: Specifies the data alignment for DAC channel1.
  *   This parameter can be one of the following values:
  *     @arg DAC_Align_8b_Right: 8bit right data alignment selected
  *     @arg DAC_Align_12b_Left: 12bit left data alignment selected
  *     @arg DAC_Align_12b_Right: 12bit right data alignment selected
  * @param  Data : Data to be loaded in the selected data holding register.
  * @retval None
  */
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data));

  tmp = (uint32_t)DAC_BASE;
  tmp += DHR12R1_OFFSET + DAC_Align;

  /* Set the DAC channel1 selected data holding register */
  *(__IO uint32_t *) tmp = Data;
}

/**
  * @brief  Set the specified data holding register value for DAC channel2.
  * @param  DAC_Align: Specifies the data alignment for DAC channel2.
  *   This parameter can be one of the following values:
  *     @arg DAC_Align_8b_Right: 8bit right data alignment selected
  *     @arg DAC_Align_12b_Left: 12bit left data alignment selected
  *     @arg DAC_Align_12b_Right: 12bit right data alignment selected
  * @param  Data : Data to be loaded in the selected data holding register.
  * @retval None
  */
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data));

  tmp = (uint32_t)DAC_BASE;
  tmp += DHR12R2_OFFSET + DAC_Align;

  /* Set the DAC channel2 selected data holding register */
  *(__IO uint32_t *)tmp = Data;
}

/**
  * @brief  Set the specified data holding register value for dual channel
  *   DAC.
  * @param  DAC_Align: Specifies the data alignment for dual channel DAC.
  *   This parameter can be one of the following values:
  *     @arg DAC_Align_8b_Right: 8bit right data alignment selected
  *     @arg DAC_Align_12b_Left: 12bit left data alignment selected
  *     @arg DAC_Align_12b_Right: 12bit right data alignment selected
  * @param  Data2: Data for DAC Channel2 to be loaded in the selected data
  *   holding register.
  * @param  Data1: Data for DAC Channel1 to be loaded in the selected data
  *   holding register.
  * @retval None
  */
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1)
{
  uint32_t data = 0, tmp = 0;

  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data1));
  assert_param(IS_DAC_DATA(Data2));

  /* Calculate and set dual DAC data holding register value */
  if (DAC_Align == DAC_Align_8b_Right)
  {
    data = ((uint32_t)Data2 << 8) | Data1;
  }
  else
  {
    data = ((uint32_t)Data2 << 16) | Data1;
  }

  tmp = (uint32_t)DAC_BASE;
  tmp += DHR12RD_OFFSET + DAC_Align;

  /* Set the dual DAC selected data holding register */
  *(__IO uint32_t *)tmp = data;
}

/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: DAC Channel1 selected
  *     @arg DAC_Channel_2: DAC Channel2 selected
  * @retval The selected DAC channel data output value.
  */
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));

  tmp = (uint32_t) DAC_BASE ;
  tmp += ODT_OFFSET + ((uint32_t)DAC_Channel >> 2);

  /* Returns the DAC channel data output register value */
  return (uint16_t) (*(__IO uint32_t*) tmp);
}

/**
  * @}
  */

#endif /* AT32F403xx || AT32F403Axx || AT32F407xx */

/**
  * @}
  */

/**
  * @}
  */


