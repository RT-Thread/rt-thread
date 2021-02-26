/**
  ******************************************************************************
  * @brief   DAC functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_dac.h"
#include "gd32f10x_rcc.h"
/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup DAC
  * @brief DAC driver modules
  * @{
  */

/** @defgroup DAC_Private_Defines
  * @{
  */
/* CTLR register bits mask */
#define CTLR_BITS_CLEAR                 ((uint32_t)0x00000FFE)
/* DAC Dual Channels SWTRIG masks */
#define DUAL_SWTRIG_SET                 ((uint32_t)0x00000003)
/* DHR registers offsets */
#define DHR12R1_OFFSET                  ((uint32_t)0x00000008)
#define DHR12R2_OFFSET                  ((uint32_t)0x00000014)
#define DHR12RD_OFFSET                  ((uint32_t)0x00000020)
/* DOR register offset */
#define DOR_OFFSET                      ((uint32_t)0x0000002C)

/**
  * @}
  */

/** @defgroup DAC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the DAC peripheral registers.
  * @param  DAC_InitParaStruct: DAC_InitPara structure that contains the
  *   configuration information for the selected DAC channel.
  * @retval None
  */
void DAC_DeInit(DAC_InitPara *DAC_InitParaStruct)
{
    /* Enable DAC reset state */
    RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_DACRST, ENABLE);
    /* Release DAC from reset state */
    RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_DACRST, DISABLE);
    /* Initialize the DAC_Trigger */
    DAC_InitParaStruct->DAC_Trigger = DAC_TRIGGER_NONE;
    /* Initialize the DAC_WaveGeneration */
    DAC_InitParaStruct->DAC_WaveType = DAC_WAVEGENE_NONE;
    /* Initialize the DAC_LFSRUnmask_TriangleAmplitude */
    DAC_InitParaStruct->DAC_LFSRNoise_AmplitudeTriangle = DAC_LFSR_BIT0;
    /* Initialize the DAC_OutputBuffer */
    DAC_InitParaStruct->DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
}

/**
  * @brief  Initialize the DAC peripheral.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: select DAC Channel1
  *     @arg DAC_Channel_2: select DAC Channel2
  * @param  DAC_InitStruct: DAC_InitTypeDef structure .
  * @retval None
  */
void DAC_Init(uint32_t DAC_Channel, DAC_InitPara *DAC_InitParaStruct)
{
    uint32_t temp1 = 0, temp2 = 0;

    /* DAC CTLR Configuration */
    /* Get the DAC CTLR value */
    temp1 = DAC->CTLR;

    /* Clear BOFF, TEN, TSEL, WAVE and MAMP bits */
    temp1 &= ~(CTLR_BITS_CLEAR << DAC_Channel);

    /* Configure for the DAC channel: buffer output, trigger, wave generation,
       mask/amplitude for wave generation */
    /* Set TSEL and TEN bits according to DAC_Trigger */
    /* Set WAVE bits according to DAC_WaveType */
    /* Set MAMP bits according to DAC_LFSRNoise_AmplitudeTriangle */
    /* Set BOFF bit according to DAC_OutputBuffer */
    temp2 = (DAC_InitParaStruct->DAC_Trigger | DAC_InitParaStruct->DAC_OutputBuffer |
             DAC_InitParaStruct->DAC_WaveType | DAC_InitParaStruct->DAC_LFSRNoise_AmplitudeTriangle);
    /* Calculate CTLR register value */
    temp1 |= temp2 << DAC_Channel;

    /* Write to DAC CTLR */
    DAC->CTLR = temp1;
}

/**
  * @brief  Enable or disable the DAC channel.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: select DAC Channel1.
  *     @arg DAC_Channel_2: select DAC Channel2.
  * @param  NewValue: New value of the DAC channel.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_Enable(uint32_t DAC_Channel, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the selected DAC channel */
        DAC->CTLR |= (DAC_CTLR_DEN1 << DAC_Channel) ;
    } else {
        /* Disable the selected DAC channel */
        DAC->CTLR &= ~(DAC_CTLR_DEN1 << DAC_Channel);
    }
}

/**
  * @brief  Enable or disable the selected DAC channel software trigger.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: select DAC Channel1
  *     @arg DAC_Channel_2: select DAC Channel2
  * @param  NewValue: New value of the selected DAC channel software trigger.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_SoftwareTrigger_Enable(uint32_t DAC_Channel, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable software trigger for DAC channel1 */
        DAC->SWTR |= (uint32_t)DAC_SWTR_SWTR1 << (DAC_Channel >> 4);
    } else {
        /* Disable software trigger for DAC channel1 */
        DAC->SWTR &= ~((uint32_t)DAC_SWTR_SWTR1 << (DAC_Channel >> 4));
    }
}

/**
  * @brief  Enable or disable simultaneously the two DAC channels software
  *   triggers.
  * @param  NewValue: new value of the DAC channels software triggers.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_DualSoftwareTrigger_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable software trigger */
        DAC->SWTR |= DUAL_SWTRIG_SET ;
    } else {
        /* Disable software trigger */
        DAC->SWTR &= ~DUAL_SWTRIG_SET;
    }
}

/**
  * @brief  Enable or disable the selected DAC channel wave generation.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: select DAC Channel1
  *     @arg DAC_Channel_2: select DAC Channel2
  * @param  DAC_Wave: the wave type to enable or disable.
  *   This parameter can be one of the following values:
  *     @arg DAC_WAVE_NOISE: noise wave generation
  *     @arg DAC_WAVE_TRIANGLE: triangle wave generation
  * @param  NewValue: new value of the selected DAC channel wave generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_WaveGeneration_Enable(uint32_t DAC_Channel, uint32_t DAC_Wave, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the selected DAC channel wave generation */
        DAC->CTLR |= DAC_Wave << DAC_Channel;
    } else {
        /* Disable the selected DAC channel wave generation */
        DAC->CTLR &= ~(DAC_Wave << DAC_Channel);
    }
}

/**
  * @brief  Set the specified data holding register value for DAC channel1.
  * @param  DAC_Align: the data alignment for DAC channel1.
  *   This parameter can be one of the following values:
  *     @arg DAC_ALIGN_8B_R: select 8bit right data alignment
  *     @arg DAC_ALIGN_12B_L: select 12bit left data alignment
  *     @arg DAC_ALIGN_12B_R: select 12bit right data alignment
  * @param  Data: Data to be loaded.
  * @retval None
  */
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data)
{
    __IO uint32_t temp = 0;

    temp = (uint32_t)DAC_BASE;
    temp += DHR12R1_OFFSET + DAC_Align;

    /* Set the DAC channel1 */
    *(__IO uint32_t *) temp = Data;
}

/**
  * @brief  Set the specified data holding register value for DAC channel2.
  * @param  DAC_Align: the data alignment for DAC channel2.
  *   This parameter can be one of the following values:
  *     @arg DAC_ALIGN_8B_R: select 8bit right data alignment
  *     @arg DAC_ALIGN_12B_L: select 12bit left data alignment
  *     @arg DAC_ALIGN_12B_R: select 12bit right data alignment
  * @param  Data: Data to be loaded.
  * @retval None
  */
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data)
{
    __IO uint32_t temp = 0;

    temp = (uint32_t)DAC_BASE;
    temp += DHR12R2_OFFSET + DAC_Align;

    /* Set the DAC channel2 */
    *(__IO uint32_t *) temp = Data;
}

/**
  * @brief  Set the specified data for dual channel
  * @param  DAC_Align: the data alignment for dual channel DAC.
  *   This parameter can be one of the following values:
  *     @arg DAC_Align_8b_R: select 8bit right data alignment
  *     @arg DAC_Align_12b_L: select 12bit left data alignment
  *     @arg DAC_Align_12b_R: select 12bit right data alignment
  * @param  Data2: Data for DAC Channel2.
  * @param  Data1: Data for DAC Channel1.
  * @retval None
  */
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1)
{
    uint32_t data = 0, temp = 0;

    /* set dual DAC data holding register value */
    if (DAC_Align == DAC_ALIGN_8B_R) {
        data = ((uint32_t)Data2 << 8) | Data1;
    } else {
        data = ((uint32_t)Data2 << 16) | Data1;
    }

    temp = (uint32_t)DAC_BASE;
    temp += DHR12RD_OFFSET + DAC_Align;

    /* Set the dual DAC selected data holding register */
    *(__IO uint32_t *)temp = data;
}

/**
  * @brief  Return the last data output value.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: select DAC Channel1
  *     @arg DAC_Channel_2: select DAC Channel2
  * @retval The DAC channel1 data output value.
  */
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel)
{
    __IO uint32_t temp = 0;

    temp = (uint32_t) DAC_BASE;
    temp += DOR_OFFSET + ((uint32_t)DAC_Channel >> 2);

    /* Returns the DAC channel data */
    return (uint16_t)(*(__IO uint32_t *) temp);
}

/**
  * @brief  Enable or disable DMA request.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: select DAC Channel1
  *     @arg DAC_Channel_2: select DAC Channel2
  * @param  NewValue: New value of the selected DAC channel DMA request.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_DMA_Enable(uint32_t DAC_Channel, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable DMA request */
        DAC->CTLR |= (DAC_CTLR_DDMAEN1 << DAC_Channel);
    } else {
        /* Disable DMA request */
        DAC->CTLR &= ~(DAC_CTLR_DDMAEN1 << DAC_Channel);
    }
}

/**
  * @brief  Enable or disable the specified DAC interrupts.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: DAC Channel1 selected
  *     @arg DAC_Channel_2: DAC Channel2 selected
  * @param  NewValue: Alternative state of the specified DAC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_INTConfig(uint32_t DAC_Channel, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the DAC DMAUDR interrupts */
        DAC->CTLR |= (DAC_INT_DMAUDR << DAC_Channel);
    } else {
        /* Disable the DAC DMAUDR interrupts */
        DAC->CTLR &= (~(uint32_t)(DAC_INT_DMAUDR << DAC_Channel));
    }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

