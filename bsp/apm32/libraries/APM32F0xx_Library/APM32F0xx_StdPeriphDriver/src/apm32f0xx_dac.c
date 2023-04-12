/*!
 * @file        apm32f0xx_dac.c
 *
 * @brief       This file contains all the functions for the DAC peripheral
 *
 * @note        It's only for APM32F051,APM32F072,APM32F091 devices
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "apm32f0xx_dac.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup DAC_Driver
  @{
*/

/** @defgroup DAC_Macros Macros
  @{
*/

/**@} end of group DAC_Macros */

/** @defgroup DAC_Enumerations Enumerations
  @{
*/

/**@} end of group DAC_Enumerations */

/** @defgroup DAC_Structures Structures
  @{
*/

/**@} end of group DAC_Structures */

/** @defgroup DAC_Variables Variables
  @{
*/

/**@} end of group DAC_Variables */

/** @defgroup DAC_Functions Functions
  @{
*/

/*!
 * @brief    Resets the DAC peripheral registers to their default reset values.
 *
 * @param    None
 *
 * @retval   None
 */
void DAC_Reset(void)
{
    RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_DAC);
    RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_DAC);
}

/*!
 * @brief    Initializes the DAC peripheral according to the specified parameters in the dacConfig.
 *
 * @param    channel: the selected DAC channel.
 *                    This parameter can be:
 *                      @arg DAC_Channel_1: DAC Channel1 selected
 *                      @arg DAC_Channel_2: DAC Channel2 selected
 *
 * @param    dacConfig: pointer to a DAC_Config_T structure that contains
 *                      the configuration information for the  specified DAC channel.
 *
 * @retval   None
 *
 * @note     DAC_Channel_2 is only for APM32F072 and APM32F091 devices
 */
void DAC_Config(uint32_t channel, DAC_Config_T* dacConfig)
{
    uint32_t tmp1 = 0, tmp2 = 0;

    tmp1 = DAC->CTRL;

    tmp1 &= ~(((uint32_t)0x00000FFE) << channel);

    tmp2 = ((uint32_t)dacConfig->trigger | \
              (uint32_t)dacConfig->waveGeneration | \
              (uint32_t)dacConfig->maskAmplitudeSelect | \
              (uint32_t)dacConfig->outputBuff);

    tmp1 |= tmp2 << channel;

    DAC->CTRL = tmp1;
}

/*!
 * @brief    Fills each DAC_InitStruct member with its default value.
 *
 * @param    dacConfig: pointer to a DAC_InitTypeDef structure which will
 *           be configed.
 *
 * @retval   None
 */
void DAC_ConfigStructInit(DAC_Config_T* dacConfig)
{
    dacConfig->trigger = DAC_TRIGGER_NONE;
    dacConfig->waveGeneration = DAC_WAVE_GENERATION_NONE;
    dacConfig->maskAmplitudeSelect = DAC_LFSRUNAMASK_BIT0;
    dacConfig->outputBuff = DAC_OUTPUTBUFF_ENABLE;
}

/*!
 * @brief    Enables the specified DAC channel.
 *
 * @param    channel: The selected DAC channel.
 *                    This parameter can be one of the following values:
 *                      @arg DAC_CHANNEL_1: DAC Channel1 selected
 *                      @arg DAC_CHANNEL_2: DAC Channel2 selected
 *
 * @retval   None
 *
 * @note     When the DAC channel is enabled the trigger source can no more be modified.
 *
 * @note     DAC_Channel_2 is only for APM32F072 and APM32F091 devices
 */
void DAC_Enable(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->CTRL_B.ENCH1 = SET;
    }
    else
    {
        DAC->CTRL_B.ENCH2 = SET;
    }
}

/*!
 * @brief    Disables the specified DAC channel.
 *
 * @param    channel: The selected DAC channel.
 *                    This parameter can be one of the following values:
 *                      @arg DAC_CHANNEL_1: DAC Channel1 selected
 *                      @arg DAC_CHANNEL_2: DAC Channel2 selected
 *
 * @retval   None
 *
 * @note     DAC_Channel_2 is only for APM32F072 and APM32F091 devices
 */
void DAC_Disable(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->CTRL_B.ENCH1 = RESET;
    }
    else
    {
        DAC->CTRL_B.ENCH2 = RESET;
    }
}

/*!
 * @brief    Enables the selected DAC channel software trigger.
 *
 * @param    channel: The selected DAC channel.
 *                    This parameter can be one of the following values:
 *                      @arg DAC_CHANNEL_1: DAC Channel1 selected
 *                      @arg DAC_CHANNEL_2: DAC Channel2 selected
 *
 * @retval   None
 *
 * @note     DAC_Channel_2 is only for APM32F072 and APM32F091 devices
 */
void DAC_EnableSoftwareTrigger(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->SWTRG_B.SWTRG1 = SET;
    }
    else
    {
        DAC->SWTRG_B.SWTRG2 = SET;
    }
}

/*!
 * @brief    Disable the selected DAC channel software trigger.
 *
 * @param    channel: The selected DAC channel.
 *                    This parameter can be one of the following values:
 *                      @arg DAC_CHANNEL_1: DAC Channel1 selected
 *                      @arg DAC_CHANNEL_2: DAC Channel2 selected
 *
 * @retval   None
 *
 * @note     DAC_Channel_2 is only for APM32F072 and APM32F091 devices
 */
void DAC_DisableSoftwareTrigger(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->SWTRG_B.SWTRG1 = RESET;
    }
    else
    {
        DAC->SWTRG_B.SWTRG2 = RESET;
    }
}

/*!
 * @brief    Enables simultaneously the two DAC channels software triggers.
 *
 * @param    None
 *
 * @retval   None
 *
 * @note     This function is only for APM32F072 and APM32F091 devices
 */
void DAC_EnableDualSoftwareTrigger(void)
{
    DAC->SWTRG |= DUAL_SWTRIG_SET;
}

/*!
 * @brief    Disables simultaneously the two DAC channels software triggers.
 *
 * @param    None
 *
 * @retval   None
 *
 * @note     This function is only for APM32F072 and APM32F091 devices
 */
void DAC_DisableDualSoftwareTrigger(void)
{
    DAC->SWTRG &= DUAL_SWTRIG_RESET;
}

/*!
 * @brief    Enables the selected DAC channel wave generation.
 *
 * @param    channel: The selected DAC channel.
 *                    This parameter can be:
 *                      @arg DAC_CHANNEL_1: DAC Channel1 selected
 *                      @arg DAC_CHANNEL_2: DAC Channel2 selected
 *
 * @param    wave: specifies the wave type to enable or disable.
 *                 This parameter can be:
 *                   @arg DAC_WAVE_GENERATION_NOISE: noise wave generation
 *                   @arg DAC_WAVE_GENERATION_TRIANGLE: triangle wave generation
 *
 * @retval   None
 *
 * @note     This function is only for APM32F072 and APM32F091 devices
 */
void DAC_EnableWaveGeneration(DAC_CHANNEL_T channel, DAC_WAVE_GENERATION_T wave)
{
    DAC->CTRL |= ((uint32_t)wave) << ((uint32_t)channel);
}

/*!
 * @brief    Disable the selected DAC channel wave generation.
 *
 * @param    channel: The selected DAC channel.
 *                    This parameter can be:
 *                      @arg DAC_CHANNEL_1: DAC Channel1 selected
 *                      @arg DAC_CHANNEL_2: DAC Channel2 selected
 *
 * @param    wave: specifies the wave type to enable or disable.
 *                 This parameter can be:
 *                   @arg DAC_WAVE_GENERATION_NOISE: noise wave generation
 *                   @arg DAC_WAVE_GENERATION_TRIANGLE: triangle wave generation
 *
 * @retval   None
 *
 * @note     This function is only for APM32F072 and APM32F091 devices
 */
void DAC_DisableWaveGeneration(DAC_CHANNEL_T channel, DAC_WAVE_GENERATION_T wave)
{
    DAC->CTRL &= ~((uint32_t)wave) << ((uint32_t)channel);
}

/*!
 * @brief    Sets the specified data holding register value for DAC channel1.
 *
 * @param    dataAlign: Specifies the data alignment for DAC channel1.
 *                      This parameter can be one of the following values:
 *                        @arg DAC_ALIGN_8B_R: 8bit right data alignment selected
 *                        @arg DAC_ALIGN_12B_L: 12bit left data alignment selected
 *                        @arg DAC_ALIGN_12B_R: 12bit right data alignment selected
 *
 * @param    data: Data to be loaded in the selected data holding register.
 *
 * @retval   None
 */
void DAC_ConfigChannel1Data(DAC_DATA_ALIGN_T dataAlign, uint16_t data)
{
    __IO uint32_t tmp = 0;
    tmp = (uint32_t)DAC_BASE;
    tmp += DH12RCH1_OFFSET + dataAlign;
    *(__IO uint32_t*) tmp = data;
}

/*!
 * @brief    Sets the specified data holding register value for DAC channel2.
 *
 * @param    dataAlign: Specifies the data alignment for DAC channel2.
 *                      This parameter can be:
 *                        @arg DAC_ALIGN_8B_R: 8bit right data alignment selected
 *                        @arg DAC_ALIGN_12B_L: 12bit left data alignment selected
 *                        @arg DAC_ALIGN_12B_R: 12bit right data alignment selected
 *
 * @param    data: Data to be loaded in the selected data holding register.
 *
 * @retval   None
 *
 * @note     This function is only for APM32F072 and APM32F091 devices
 */
void DAC_ConfigChannel2Data(DAC_DATA_ALIGN_T dataAlign, uint16_t data)
{
    __IO uint32_t tmp = 0;
    tmp = (uint32_t)DAC_BASE;
    tmp += DH12RCH2_OFFSET + dataAlign;
    *(__IO uint32_t*)tmp = data;
}

/*!
 * @brief    Sets the specified data holding register value for dual channel DAC.
 *
 * @param    dataAlign: Specifies the data alignment for dual channel DAC.
 *                      This parameter can be:
 *                        @arg DAC_ALIGN_8B_R: 8bit right data alignment selected
 *                        @arg DAC_ALIGN_12B_L: 12bit left data alignment selected
 *                        @arg DAC_ALIGN_12B_R: 12bit right data alignment selected
 * @param    data2: Data for DAC Channel2 to be loaded in the selected data holding register.
 * @param    data1: Data for DAC Channel1 to be loaded in the selected data  holding register.
 *
 * @retval   None
 *
 * @note     In dual mode, a unique register access is required to write in both
 *           DAC channels at the same time.
 *
 * @note     This function is only for APM32F072 and APM32F091 devices
 */
void DAC_ConfigDualChannelData(DAC_DATA_ALIGN_T dataAlign, uint16_t data2, uint16_t data1)
{
    uint32_t data = 0, tmp = 0;

    if (dataAlign == DAC_ALIGN_8B_R)
    {
        data = ((uint32_t)data2 << 8) | data1;
    }
    else
    {
        data = ((uint32_t)data2 << 16) | data1;
    }
    tmp = (uint32_t)DAC_BASE;
    tmp += DH12RD_OFFSET + dataAlign;
    *(__IO uint32_t*)tmp = data;
}

/*!
 * @brief    Returns the last data output value of the selected DAC channel.
 *
 * @param    channel: The selected DAC channel.
 *                    This parameter can be one of the following values:
 *                      @arg DAC_CHANNEL_1: DAC Channel1 selected
 *                      @arg DAC_CHANNEL_2: DAC Channel2 selected
 *
 * @retval   The selected DAC channel data output value.
 *
 * @note     DAC_Channel_2 is only for APM32F072 and APM32F091 devices
 */
uint16_t DAC_ReadDataOutputValue(DAC_CHANNEL_T channel)
{
    uint16_t data;
    if (channel == DAC_CHANNEL_1)
    {
        data = DAC->DATAOCH1_B.DATA;
    }
    else
    {
        data = DAC->DATAOCH2_B.DATA;
    }
    return data;
}

/*!
 * @brief    Enables the specified DAC channel DMA request.
 *           When enabled DMA1 is generated when an external trigger (EINT Line9,
 *           TMR2, TMR3, TMR6 or TMR15  but not a software trigger) occurs

 * @param    channel: the selected DAC channel.
 *                    This parameter can be one of the following values:
 *                      @arg DAC_CHANNEL_1: DAC Channel1 selected
 *                      @arg DAC_CHANNEL_2: DAC Channel2 selected
 *
 * @retval   None
 *
 * @note     The DAC channel1 is mapped on DMA1 channel3 which must be already configured.
 *
 * @note     The DAC channel2 is mapped on DMA1 channel4 which must be already configured.
 *
 * @note     DAC_Channel_2 is only for APM32F072 and APM32F091 devices
 */
void DAC_EnableDMA(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->CTRL_B.DMAENCH1 = SET;
    }
    else
    {
        DAC->CTRL_B.DMAENCH2 = SET;
    }
}

/*!
 * @brief    Disable the specified DAC channel DMA request.
 *
 * @param    channel: the selected DAC channel.
 *                    This parameter can be one of the following values:
 *                      @arg DAC_CHANNEL_1: DAC Channel1 selected
 *                      @arg DAC_CHANNEL_2: DAC Channel2 selected
 *
 * @retval   None
 *
 * @note     The DAC channel1 is mapped on DMA1 channel3 which must be already configured.
 *
 * @note     The DAC channel2 is mapped on DMA1 channel4 which must be already configured.
 *
 * @note     DAC_Channel_2 is only for APM32F072 and APM32F091 devices
 */
void DAC_DisableDMA(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->CTRL_B.DMAENCH1 = RESET;
    }
    else
    {
        DAC->CTRL_B.DMAENCH2 = RESET;
    }
}

/*!
 * @brief    Enables the specified DAC interrupts.
 *
 * @param    channel: The selected DAC channel.
 *                    This parameter can be:
 *                      @arg DAC_CHANNEL_1: DAC Channel1 selected
 *                      @arg DAC_CHANNEL_2: DAC Channel2 selected
 *
 * @retval   None
 *
 * @note     The DMA underrun occurs when a second external trigger arrives before the
 *           acknowledgement for the first external trigger is received (first request).
 *
 * @note     DAC_Channel_2 is only for APM32F072 and APM32F091 devices
 */
void DAC_EnableInterrupt(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->CTRL_B.DMAUDRIEN1 = SET;
    }
    else
    {
        DAC->CTRL_B.DMAUDRIEN2 = SET;
    }
}

/*!
 * @brief    Disables the specified DAC interrupts.
 *
 * @param    channel: The selected DAC channel.
 *                    This parameter can be:
 *                      @arg DAC_CHANNEL_1: DAC Channel1 selected
 *                      @arg DAC_CHANNEL_2: DAC Channel2 selected
 *
 * @retval   None
 *
 * @note     The DMA underrun occurs when a second external trigger arrives before the
 *           acknowledgement for the first external trigger is received (first request).
 *
 * @note     DAC_Channel_2 is only for APM32F072 and APM32F091 devices
 */
void DAC_DisableInterrupt(DAC_CHANNEL_T channel)
{
    if (channel == DAC_CHANNEL_1)
    {
        DAC->CTRL_B.DMAUDRIEN1 = RESET;
    }
    else
    {
        DAC->CTRL_B.DMAUDRIEN2 = RESET;
    }
}

/*!
 * @brief    Reads the DAC status flag.
 *
 * @param    flag: specifies the flag to check.
 *                 This parameter can be only of the following value:
 *                    @arg DAC_FLAG_CH1_DMAUDR: DMA Channel1 underrun flag
 *                    @arg DAC_FLAG_CH2_DMAUDR: DMA Channel2 underrun flag, only for APM32F072 and APM32F091 devices
 *
 * @retval   The new state of DAC flag (SET or RESET).
 *
 * @note     The DMA underrun occurs when a second external trigger arrives before the
 *           acknowledgement for the first external trigger is received (first request).
 */
uint8_t DAC_ReadStatusFlag(DAC_FLAG_T flag)
{
    uint16_t status;

    status = (uint16_t)(DAC->STS & flag);
    if (status == flag)
    {
        return SET;
    }
    else
        return RESET;
}
/*!
 * @brief    Clears the DAC status flags.
 *
 * @param    flag: specifies the flag to check.
 *                 This parameter can be only of the following value:
 *                    @arg DAC_FLAG_CH1_DMAUDR: DMA Channel1 underrun flag
 *                    @arg DAC_FLAG_CH2_DMAUDR: DMA Channel2 underrun flag, , only for APM32F072 and APM32F091 devices
 *                    @arg DAC_FLAG_DMAUDR: DMA underrun flag
 *
 * @retval   None
 */
void DAC_ClearStatusFlag(DAC_FLAG_T flag)
{
    DAC->STS &= (uint32_t)~flag;
}

/*!
 * @brief    Reads teh DAC interrupt flag.
 *
 * @param    intFlag: specifies the DAC interrupt source to check.
 *                    This parameter can be the following values:
 *                      @arg DAC_INT_CH1_DMAUDR: DMA Channel1 underrun interrupt mask
 *                      @arg DAC_INT_CH2_DMAUDR: DMA Channel2 underrun interrupt mask, , only for APM32F072 and APM32F091 devices
 *
 * @retval   The new state of DAC interrupt flag (SET or RESET).
 *
 * @note     The DMA underrun occurs when a second external trigger arrives before the
 *           acknowledgement for the first external trigger is received (first request).
 */
uint8_t DAC_ReadIntFlag(DAC_INT_T intFlag)
{
    uint32_t intEnable;
    intEnable = (DAC->CTRL & intFlag);
    if (((DAC->STS & intFlag) != (uint32_t)RESET) && intEnable)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/*!
 * @brief  Clears the DAC channel's interrupt flag.
 *
 * @param  intFlag: specifies the DAC interrupt pending bit to clear.
 *                  This parameter can be the following values:
 *                    @arg DAC_INT_CH1_DMAUDR: DMA Channel1 underrun interrupt mask
 *                    @arg DAC_INT_CH2_DMAUDR: DMA Channel2 underrun interrupt mask, , only for APM32F072 and APM32F091 devices
 *
 * @retval None
 */
void DAC_ClearIntFlag(DAC_INT_T intFlag)
{
    DAC->STS = intFlag;
}

/**@} end of group DAC_Functions */
/**@} end of group DAC_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
