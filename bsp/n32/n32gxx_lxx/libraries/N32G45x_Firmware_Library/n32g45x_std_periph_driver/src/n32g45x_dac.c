/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_dac.c
 * @author Nations
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x_dac.h"
#include "n32g45x_rcc.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup DAC
 * @brief DAC driver modules
 * @{
 */

/** @addtogroup DAC_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup DAC_Private_Defines
 * @{
 */

/* CTRL register Mask */
#define CTRL_CLEAR_MASK ((uint32_t)0x00000FFE)

/* DAC Dual Channels SWTRIG masks */
#define DUAL_SWTRIG_SET   ((uint32_t)0x00000003)
#define DUAL_SWTRIG_RESET ((uint32_t)0xFFFFFFFC)

/* DCH registers offsets */
#define DR12CH1_OFFSET ((uint32_t)0x00000008)
#define DR12CH2_OFFSET ((uint32_t)0x00000014)
#define DR12DCH_OFFSET ((uint32_t)0x00000020)

/* DATO register offset */
#define DATO1_OFFSET ((uint32_t)0x0000002C)
/**
 * @}
 */

/** @addtogroup DAC_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup DAC_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup DAC_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup DAC_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the DAC peripheral registers to their default reset values.
 */
void DAC_DeInit(void)
{
    /* Enable DAC reset state */
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_DAC, ENABLE);
    /* Release DAC from reset state */
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_DAC, DISABLE);
}

/**
 * @brief  Initializes the DAC peripheral according to the specified
 *         parameters in the DAC_InitStruct.
 * @param DAC_Channel the selected DAC channel.
 *   This parameter can be one of the following values:
 *     @arg DAC_CHANNEL_1 DAC Channel1 selected
 *     @arg DAC_CHANNEL_2 DAC Channel2 selected
 * @param DAC_InitStruct pointer to a DAC_InitType structure that
 *        contains the configuration information for the specified DAC channel.
 */
void DAC_Init(uint32_t DAC_Channel, DAC_InitType* DAC_InitStruct)
{
    uint32_t tmpreg1 = 0, tmpreg2 = 0;
    /* Check the DAC parameters */
    assert_param(IS_DAC_TRIGGER(DAC_InitStruct->Trigger));
    assert_param(IS_DAC_GENERATE_WAVE(DAC_InitStruct->WaveGen));
    assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(DAC_InitStruct->LfsrUnMaskTriAmp));
    assert_param(IS_DAC_OUTPUT_BUFFER_STATE(DAC_InitStruct->BufferOutput));
    /*---------------------------- DAC CTRL Configuration --------------------------*/
    /* Get the DAC CTRL value */
    tmpreg1 = DAC->CTRL;
    /* Clear BOFFx, TENx, TSELx, WAVEx and MAMPx bits */
    tmpreg1 &= ~(CTRL_CLEAR_MASK << DAC_Channel);
    /* Configure for the selected DAC channel: buffer output, trigger, wave generation,
       mask/amplitude for wave generation */
    /* Set TSELx and TENx bits according to Trigger value */
    /* Set WAVEx bits according to WaveGen value */
    /* Set MAMPx bits according to LfsrUnMaskTriAmp value */
    /* Set BOFFx bit according to BufferOutput value */
    tmpreg2 = (DAC_InitStruct->Trigger | DAC_InitStruct->WaveGen | DAC_InitStruct->LfsrUnMaskTriAmp
               | DAC_InitStruct->BufferOutput);
    /* Calculate CTRL register value depending on DAC_Channel */
    tmpreg1 |= tmpreg2 << DAC_Channel;
    /* Write to DAC CTRL */
    DAC->CTRL = tmpreg1;
}

/**
 * @brief  Fills each DAC_InitStruct member with its default value.
 * @param DAC_InitStruct pointer to a DAC_InitType structure which will
 *         be initialized.
 */
void DAC_ClearStruct(DAC_InitType* DAC_InitStruct)
{
    /*--------------- Reset DAC init structure parameters values -----------------*/
    /* Initialize the Trigger member */
    DAC_InitStruct->Trigger = DAC_TRG_NONE;
    /* Initialize the WaveGen member */
    DAC_InitStruct->WaveGen = DAC_WAVEGEN_NONE;
    /* Initialize the LfsrUnMaskTriAmp member */
    DAC_InitStruct->LfsrUnMaskTriAmp = DAC_UNMASK_LFSRBIT0;
    /* Initialize the BufferOutput member */
    DAC_InitStruct->BufferOutput = DAC_BUFFOUTPUT_ENABLE;
}

/**
 * @brief  Enables or disables the specified DAC channel.
 * @param DAC_Channel the selected DAC channel.
 *   This parameter can be one of the following values:
 *     @arg DAC_CHANNEL_1 DAC Channel1 selected
 *     @arg DAC_CHANNEL_2 DAC Channel2 selected
 * @param Cmd new state of the DAC channel.
 *   This parameter can be: ENABLE or DISABLE.
 */
void DAC_Enable(uint32_t DAC_Channel, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected DAC channel */
        DAC->CTRL |= (DAC_CTRL_CH1EN << DAC_Channel);
    }
    else
    {
        /* Disable the selected DAC channel */
        DAC->CTRL &= ~(DAC_CTRL_CH1EN << DAC_Channel);
    }
}

/**
 * @brief  Enables or disables the specified DAC channel DMA request.
 * @param DAC_Channel the selected DAC channel.
 *   This parameter can be one of the following values:
 *     @arg DAC_CHANNEL_1 DAC Channel1 selected
 *     @arg DAC_CHANNEL_2 DAC Channel2 selected
 * @param Cmd new state of the selected DAC channel DMA request.
 *   This parameter can be: ENABLE or DISABLE.
 */
void DAC_DmaEnable(uint32_t DAC_Channel, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected DAC channel DMA request */
        DAC->CTRL |= (DAC_CTRL_DMA1EN << DAC_Channel);
    }
    else
    {
        /* Disable the selected DAC channel DMA request */
        DAC->CTRL &= ~(DAC_CTRL_DMA1EN << DAC_Channel);
    }
}

/**
 * @brief  Enables or disables the selected DAC channel software trigger.
 * @param DAC_Channel the selected DAC channel.
 *   This parameter can be one of the following values:
 *     @arg DAC_CHANNEL_1 DAC Channel1 selected
 *     @arg DAC_CHANNEL_2 DAC Channel2 selected
 * @param Cmd new state of the selected DAC channel software trigger.
 *   This parameter can be: ENABLE or DISABLE.
 */
void DAC_SoftTrgEnable(uint32_t DAC_Channel, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable software trigger for the selected DAC channel */
        DAC->SOTTR |= (uint32_t)DAC_SOTTR_TR1EN << (DAC_Channel >> 4);
    }
    else
    {
        /* Disable software trigger for the selected DAC channel */
        DAC->SOTTR &= ~((uint32_t)DAC_SOTTR_TR1EN << (DAC_Channel >> 4));
    }
}

/**
 * @brief  Enables or disables simultaneously the two DAC channels software
 *   triggers.
 * @param Cmd new state of the DAC channels software triggers.
 *   This parameter can be: ENABLE or DISABLE.
 */
void DAC_DualSoftwareTrgEnable(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable software trigger for both DAC channels */
        DAC->SOTTR |= DUAL_SWTRIG_SET;
    }
    else
    {
        /* Disable software trigger for both DAC channels */
        DAC->SOTTR &= DUAL_SWTRIG_RESET;
    }
}

/**
 * @brief  Enables or disables the selected DAC channel wave generation.
 * @param DAC_Channel the selected DAC channel.
 *   This parameter can be one of the following values:
 *     @arg DAC_CHANNEL_1 DAC Channel1 selected
 *     @arg DAC_CHANNEL_2 DAC Channel2 selected
 * @param DAC_Wave Specifies the wave type to enable or disable.
 *   This parameter can be one of the following values:
 *     @arg DAC_WAVE_NOISE noise wave generation
 *     @arg DAC_WAVE_TRIANGLE triangle wave generation
 * @param Cmd new state of the selected DAC channel wave generation.
 *   This parameter can be: ENABLE or DISABLE.
 */
void DAC_WaveGenerationEnable(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState Cmd)
{
    /* Check the parameters */
    __IO uint32_t tmp = 0;
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_DAC_WAVE(DAC_Wave));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    tmp=DAC->CTRL;
    tmp&=~(3<<(DAC_Channel+6));
    if (Cmd != DISABLE)
    {
        /* Enable the selected wave generation for the selected DAC channel */
        tmp |= DAC_Wave << DAC_Channel;
    }
    else
    {
        /* Disable the selected wave generation for the selected DAC channel */
        tmp &=~(3<<(DAC_Channel+6));
    }
    DAC->CTRL = tmp;
}

/**
 * @brief  Set the specified data holding register value for DAC channel1.
 * @param DAC_Align Specifies the data alignment for DAC channel1.
 *   This parameter can be one of the following values:
 *     @arg DAC_ALIGN_R_8BIT 8bit right data alignment selected
 *     @arg DAC_ALIGN_L_12BIT 12bit left data alignment selected
 *     @arg DAC_ALIGN_R_12BIT 12bit right data alignment selected
 * @param Data Data to be loaded in the selected data holding register.
 */
void DAC_SetCh1Data(uint32_t DAC_Align, uint16_t Data)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_DAC_ALIGN(DAC_Align));
    assert_param(IS_DAC_DATA(Data));

    tmp = (uint32_t)DAC_BASE;
    tmp += DR12CH1_OFFSET + DAC_Align;

    /* Set the DAC channel1 selected data holding register */
    *(__IO uint32_t*)tmp = Data;
}

/**
 * @brief  Set the specified data holding register value for DAC channel2.
 * @param DAC_Align Specifies the data alignment for DAC channel2.
 *   This parameter can be one of the following values:
 *     @arg DAC_ALIGN_R_8BIT 8bit right data alignment selected
 *     @arg DAC_ALIGN_L_12BIT 12bit left data alignment selected
 *     @arg DAC_ALIGN_R_12BIT 12bit right data alignment selected
 * @param Data Data to be loaded in the selected data holding register.
 */
void DAC_SetCh2Data(uint32_t DAC_Align, uint16_t Data)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_DAC_ALIGN(DAC_Align));
    assert_param(IS_DAC_DATA(Data));

    tmp = (uint32_t)DAC_BASE;
    tmp += DR12CH2_OFFSET + DAC_Align;

    /* Set the DAC channel2 selected data holding register */
    *(__IO uint32_t*)tmp = Data;
}

/**
 * @brief  Set the specified data holding register value for dual channel
 *   DAC.
 * @param DAC_Align Specifies the data alignment for dual channel DAC.
 *   This parameter can be one of the following values:
 *     @arg DAC_ALIGN_R_8BIT 8bit right data alignment selected
 *     @arg DAC_ALIGN_L_12BIT 12bit left data alignment selected
 *     @arg DAC_ALIGN_R_12BIT 12bit right data alignment selected
 * @param Data2 Data for DAC Channel2 to be loaded in the selected data
 *   holding register.
 * @param Data1 Data for DAC Channel1 to be loaded in the selected data
 *   holding register.
 */
void DAC_SetDualChData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1)
{
    uint32_t data = 0, tmp = 0;

    /* Check the parameters */
    assert_param(IS_DAC_ALIGN(DAC_Align));
    assert_param(IS_DAC_DATA(Data1));
    assert_param(IS_DAC_DATA(Data2));

    /* Calculate and set dual DAC data holding register value */
    if (DAC_Align == DAC_ALIGN_R_8BIT)
    {
        data = ((uint32_t)Data2 << 8) | Data1;
    }
    else
    {
        data = ((uint32_t)Data2 << 16) | Data1;
    }

    tmp = (uint32_t)DAC_BASE;
    tmp += DR12DCH_OFFSET + DAC_Align;

    /* Set the dual DAC selected data holding register */
    *(__IO uint32_t*)tmp = data;
}

/**
 * @brief  Returns the last data output value of the selected DAC channel.
 * @param DAC_Channel the selected DAC channel.
 *   This parameter can be one of the following values:
 *     @arg DAC_CHANNEL_1 DAC Channel1 selected
 *     @arg DAC_CHANNEL_2 DAC Channel2 selected
 * @return The selected DAC channel data output value.
 */
uint16_t DAC_GetOutputDataVal(uint32_t DAC_Channel)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));

    tmp = (uint32_t)DAC_BASE;
    tmp += DATO1_OFFSET + ((uint32_t)DAC_Channel >> 2);

    /* Returns the DAC channel data output register value */
    return (uint16_t)(*(__IO uint32_t*)tmp);
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
