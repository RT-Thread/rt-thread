/*!
 * @file        apm32f4xx_dac.c
 *
 * @brief       This file contains all the functions prototypes for the DAC firmware library
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f4xx_dac.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup DAC_Driver
  * @brief DAC driver modules
  @{
*/

/** @defgroup DAC_Functions
  @{
*/

/*!
 * @brief     Reset dac peripheral registers to their default reset values.
 *
 * @param     None
 *
 * @retval    None
 */
void DAC_Reset(void)
{
    RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_DAC);
    RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_DAC);
}

/*!
 * @brief     Config the DAC peripheral according to the specified parameters in the dacConfig
 *
 * @param     channel: Select the DAC channel.
 *                        This parameter can be one of the following values:
 *                        @arg DAC_CHANNEL_1 : DAC channel 1
 *                        @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @param     dacConfig: pointer to a DAC_Config_T structure
 *
 * @retval    None
 */
void DAC_Config(uint32_t channel, DAC_Config_T *dacConfig)
{
    uint32_t temp1 = 0, temp2 = 0;

    temp1 = DAC->CTRL;

    temp1 &= ~(((uint32_t)0x00000FFE) << channel);

    temp2 = ((uint32_t)dacConfig->trigger | \
             (uint32_t)dacConfig->waveGeneration | \
             (uint32_t)dacConfig->maskAmplitudeSelect | \
             (uint32_t)dacConfig->outputBuffer);

    temp1 |= temp2 << channel;

    DAC->CTRL = temp1;
}

/*!
 * @brief     Fills each DAC_Config_T member with its default value
 *
 * @param     dacConfig: pointer to a DAC_Config_T structure which will be initialized
 *
 * @retval    None
 */
void DAC_ConfigStructInit(DAC_Config_T *dacConfig)
{
    dacConfig->trigger = DAC_TRIGGER_NONE;
    dacConfig->waveGeneration = DAC_WAVE_GENERATION_NONE;
    dacConfig->maskAmplitudeSelect = DAC_LFSR_MASK_BIT11_1;
    dacConfig->outputBuffer = DAC_OUTPUT_BUFFER_ENBALE;
}

/*!
 * @brief     Enables the specified DAC peripheral
 *
 * @param     channel: Select the DAC channel.
 *                     This parameter can be one of the following values:
 *                        @arg DAC_CHANNEL_1 : DAC channel 1
 *                        @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @retval    None
 */
void DAC_Enable(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->CTRL_B.ENCH1 = BIT_SET;
    }
    else if (channel == DAC_CHANNEL_2)
    {
        DAC->CTRL_B.ENCH2 = BIT_SET;
    }
}

/*!
 * @brief     Disables the specified DAC peripheral
 *
 * @param     channel: Select the DAC channel.
 *                     This parameter can be one of the following values:
 *                        @arg DAC_CHANNEL_1 : DAC channel 1
 *                        @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @retval    None
 */
void DAC_Disable(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->CTRL_B.ENCH1 = BIT_RESET;
    }
    else if (channel == DAC_CHANNEL_2)
    {
        DAC->CTRL_B.ENCH2 = BIT_RESET;
    }
}

/*!
 * @brief     Enables the specified DAC channel DMA request
 *
 * @param     channel: Select the DAC channel.
 *                        This parameter can be one of the following values:
 *                        @arg DAC_CHANNEL_1 : DAC channel 1
 *                        @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @retval    None
 */
void DAC_DMA_Enable(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->CTRL_B.DMAENCH1 = BIT_SET;
    }
    else if (channel == DAC_CHANNEL_2)
    {
        DAC->CTRL_B.DMAENCH2 = BIT_SET;
    }
}

/*!
 * @brief     Disables the specified DAC channel DMA request
 *
 * @param     channel: Select the DAC channel.
 *                     This parameter can be one of the following values:
 *                        @arg DAC_CHANNEL_1 : DAC channel 1
 *                        @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @retval    None
 */
void DAC_DMA_Disable(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->CTRL_B.DMAENCH1 = BIT_RESET;
    }
    else if (channel == DAC_CHANNEL_2)
    {
        DAC->CTRL_B.DMAENCH2 = BIT_RESET;
    }
}

/*!
 * @brief     Enables the selected DAC channel software trigger
 *
 * @param     channel: Select the DAC channel.
 *                     This parameter can be one of the following values:
 *                        @arg DAC_CHANNEL_1 : DAC channel 1
 *                        @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @retval    None
 */
void DAC_EnableSoftwareTrigger(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->SWTRG_B.SWTRG1 = BIT_SET;
    }
    else if (channel == DAC_CHANNEL_2)
    {
        DAC->SWTRG_B.SWTRG2 = BIT_SET;
    }
}

/*!
 * @brief     Disable the selected DAC channel software trigger
 *
 * @param     channel: Select the DAC channel.
 *                     This parameter can be one of the following values:
 *                        @arg DAC_CHANNEL_1 : DAC channel 1
 *                        @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @retval    None
 */
void DAC_DisableSoftwareTrigger(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->SWTRG_B.SWTRG1 = BIT_RESET;
    }
    else if (channel == DAC_CHANNEL_2)
    {
        DAC->SWTRG_B.SWTRG2 = BIT_RESET;
    }
}

/*!
 * @brief     Enables simultaneously the two DAC channels software
 *
 * @param     None
 *
 * @retval    None
 */
void DAC_EnableDualSoftwareTrigger(void)
{
    DAC->SWTRG_B.SWTRG1 = BIT_SET;
    DAC->SWTRG_B.SWTRG2 = BIT_SET;
}

/*!
 * @brief     Disables simultaneously the two DAC channels software
 *
 * @param     None
 *
 * @retval    None
 */
void DAC_DisableDualSoftwareTrigger(void)
{
    DAC->SWTRG_B.SWTRG1 = BIT_RESET;
    DAC->SWTRG_B.SWTRG2 = BIT_RESET;
}

/*!
 * @brief     Enables the selected DAC channel wave generation
 *
 * @param     channel: Select the DAC channel.
 *                     This parameter can be one of the following values:
 *                     @arg DAC_CHANNEL_1 : DAC channel 1
 *                     @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @param     wave: Select the wave
 *                     This parameter can be one of the following values:
 *                     @arg DAC_WAVE_GENERATION_NOISE    : Noise wave generation
 *                     @arg DAC_WAVE_GENERATION_TRIANGLE : Triangle wave generation
 *
 * @retval    None
 */
void DAC_EnableWaveGeneration(DAC_CHANNEL_T channel, DAC_WAVE_GENERATION_T wave)
{
    DAC->CTRL &= 0xFF3FFF3F;
    DAC->CTRL |= wave << channel;
}

/*!
 * @brief     Disables the selected DAC channel wave generation
 *
 * @param     channel: Select the DAC channel.
 *                     This parameter can be one of the following values:
 *                     @arg DAC_CHANNEL_1 : DAC channel 1
 *                     @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @param     wave: Select the wave
 *                     This parameter can be one of the following values:
 *                     @arg DAC_WAVE_GENERATION_NOISE    : Noise wave generation
 *                     @arg DAC_WAVE_GENERATION_TRIANGLE : Triangle wave generation
 *
 * @retval    None
 */
void DAC_DisableWaveGeneration(DAC_CHANNEL_T channel, DAC_WAVE_GENERATION_T wave)
{
    DAC->CTRL &= ~(wave << channel);
}

/*!
 * @brief     Set the specified data holding register value for DAC channel 1
 *
 * @param     align: DAC channel 1 data alignment
 *                   This parameter can be one of the following values:
 *                      @arg DAC_ALIGN_12BIT_R : 12-bit right-aligned data
 *                      @arg DAC_ALIGN_12BIT_L : 12-bit left-aligned data
 *                      @arg DAC_ALIGN_8BIT_R  : 8-bit right-aligned data
 *
 * @param     data: The data to be loaded in the selected data register.
 *
 * @retval    None
 */
void DAC_ConfigChannel1Data(DAC_ALIGN_T align, uint16_t data)
{
    __IO uint32_t temp = 0;

    temp = (uint32_t)DAC_BASE;
    temp += 0x00000008 + align;

    /* Set the DAC channel1 selected data holding register */
    *(__IO uint32_t *) temp = data;
}

/*!
 * @brief     Set the specified data holding register value for DAC channel 2
 *
 * @param     align: DAC channel 2 data alignment
 *                      This parameter can be one of the following values:
 *                      @arg DAC_ALIGN_12BIT_R : 12-bit right-aligned data
 *                      @arg DAC_ALIGN_12BIT_L : 12-bit left-aligned data
 *                      @arg DAC_ALIGN_8BIT_R  : 8-bit right-aligned data
 *
 * @param     data: The data to be loaded in the selected data register.
 *
 * @retval    None
 */
void DAC_ConfigChannel2Data(DAC_ALIGN_T align, uint16_t data)
{
    __IO uint32_t temp = 0;

    temp = (uint32_t)DAC_BASE;
    temp += 0x00000014 + align;

    /* Set the DAC channel1 selected data holding register */
    *(__IO uint32_t *) temp = data;
}

/*!
 * @brief     Set the specified data holding register value for dual DAC channel
 *
 * @param     align: Dual DAC channel data alignment
 *                   This parameter can be one of the following values:
 *                      @arg DAC_ALIGN_12BIT_R : 12-bit right-aligned data
 *                      @arg DAC_ALIGN_12BIT_L : 12-bit left-aligned data
 *                      @arg DAC_ALIGN_8BIT_R  : 8-bit right-aligned data
 *
 * @param     data2: Data for channel2 to be loaded in the selected data register.
 *
 * @param     data1: Data for channel1 to be loaded in the selected data register.
 *
 * @retval    None
 */
void DAC_ConfigDualChannelData(DAC_ALIGN_T align, uint16_t data2, uint16_t data1)
{
    uint32_t data = 0, temp = 0;

    /* Calculate and set dual DAC data holding register value */
    if (align == DAC_ALIGN_8BIT_R)
    {
        data = ((uint32_t)data2 << 8) | data1;
    }
    else
    {
        data = ((uint32_t)data2 << 16) | data1;
    }

    temp = (uint32_t)DAC_BASE;
    temp += 0x00000020 + align;

    /* Set the dual DAC selected data holding register */
    *(__IO uint32_t *)temp = data;
}

/*!
 * @brief     Reads the specified DAC channel data output value.
 *
 * @param     channel: Select the DAC channel.
 *                     This parameter can be one of the following values:
 *                       @arg DAC_CHANNEL_1 : DAC channel 1
 *                       @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @retval    The data output value of the specified DAC channel.
 */
uint16_t DAC_ReadDataOutputValue(DAC_CHANNEL_T channel)
{
    __IO uint32_t temp = 0;

    temp = (uint32_t) DAC_BASE ;
    temp += 0x0000002C + ((uint32_t)channel >> 2);

    /* Returns the DAC channel data output register value */
    return (uint16_t)(*(__IO uint32_t *) temp);
}

/*!
 * @brief     Enable the specified DAC underrun interrupt.
 *
 * @param     channel: The selected DAC channel.
 *                        This parameter can be one of the following values:
 *                        @arg DAC_CHANNEL_1 : DAC channel 1
 *                        @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @retval    None
 */
void DAC_EnableInterrupt(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->CTRL_B.DMAUDIEN1 = BIT_SET;
    }
    else if (channel == DAC_CHANNEL_2)
    {
        DAC->CTRL_B.DMAUDIEN2 = BIT_SET;
    }
}

/*!
 * @brief     Disable the specified DAC underrun interrupt.
 *
 * @param     channel: The selected DAC channel.
 *                     This parameter can be one of the following values:
 *                        @arg DAC_CHANNEL_1 : DAC channel 1
 *                        @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @retval    None
 */
void DAC_DisableInterrupt(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->CTRL_B.DMAUDIEN1 = BIT_RESET;
    }
    else if (channel == DAC_CHANNEL_2)
    {
        DAC->CTRL_B.DMAUDIEN2 = BIT_RESET;
    }
}

/*!
 * @brief     Reads the specified DAC underrun flag
 *
 * @param     channel: The selected DAC channel.
 *                        This parameter can be one of the following values:
 *                        @arg DAC_CHANNEL_1 : DAC channel 1
 *                        @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @retval    The new state of DAC_FLAG (SET or RESET).
 */
uint8_t DAC_ReadStatusFlag(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        return  DAC->STS_B.DMAUDFLG1;
    }
    else
    {
        return  DAC->STS_B.DMAUDFLG2;
    }
}

/*!
 * @brief     Clears the DAC channel's status flags.
 *
 * @param     channel: The selected DAC channel.
 *                     This parameter can be one of the following values:
 *                        @arg DAC_Channel_1: DAC Channel1 selected
 *                        @arg DAC_Channel_2: DAC Channel2 selected
 *
 * @retval    None
 */
void DAC_ClearStatusFlag(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->STS_B.DMAUDFLG1 = SET;
    }
    else
    {
        DAC->STS_B.DMAUDFLG2 = SET;
    }
}

/*!
 * @brief     Reads the specified DAC Interrupt flag.
 *
 * @param     DAC_Channel: The selected DAC channel.
 *                         This parameter can be one of the following values:
 *                            @arg DAC_CHANNEL_1 : DAC channel 1
 *                            @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @retval    The new state of DAC_IT (SET or RESET).
 */
uint8_t DAC_ReadIntFlag(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        return (DAC->CTRL_B.DMAUDIEN1 && DAC->STS_B.DMAUDFLG1);
    }
    else
    {
        return (DAC->CTRL_B.DMAUDIEN2 && DAC->STS_B.DMAUDFLG2);
    }
}

/*!
 * @brief     Clears the DAC channel's interrupt flag.
 *
 * @param     channel: The selected DAC channel.
 *                     This parameter can be one of the following values:
 *                  @arg DAC_CHANNEL_1 : DAC channel 1
 *                  @arg DAC_CHANNEL_2 : DAC channel 2
 *
 * @retval    None
 */
void DAC_ClearIntFlag(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->STS_B.DMAUDFLG1 = SET;
    }
    else
    {
        DAC->STS_B.DMAUDFLG2 = SET;
    }
}

/**@} end of group DAC_Functions */
/**@} end of group DAC_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
