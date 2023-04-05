/*!
 * @file        apm32s10x_adc.c
 *
 * @brief       This file provides all the ADC firmware functions
 *
 * @version     V1.0.1
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2022-2023 Geehy Semiconductor
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

/* Includes */
#include "apm32s10x_adc.h"
#include "apm32s10x_rcm.h"

/** @addtogroup APM32S10x_StdPeriphDriver
  @{
*/

/** @addtogroup ADC_Driver ADC Driver
  @{
*/

/** @defgroup ADC_Functions Functions
  @{
*/

/*!
 * @brief       Reset ADC peripheral registers to their default reset values.
 *
 * @param       adc: Select ADC peripheral.
 *
 * @retval      None
 *
 * @note        adc can be ADC1, ADC2.
 */
void ADC_Reset(ADC_T* adc)
{
    if (adc == ADC1)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_ADC1);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_ADC1);
    }
    else if (adc == ADC2)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_ADC2);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_ADC2);
    }
}

/*!
 * @brief       Config the ADC peripheral according to the specified parameters in the adcConfig.
 *
 * @param       adc: Select ADC peripheral.
 *
 * @param       adcConfig: pointer to a ADC_Config_T structure.
 *
 * @retval      None
 *
 * @note        adc can be ADC1, ADC2.
 */
void ADC_Config(ADC_T* adc, ADC_Config_T* adcConfig)
{
    uint32_t reg;

    reg = adc->CTRL1;
    reg &= 0xFFF0FEFF;
    reg |= (uint32_t)((adcConfig->mode) | ((uint32_t)adcConfig->scanConvMode << 8));
    adc->CTRL1 = reg;

    reg = adc->CTRL2;
    reg &= 0xFFF1F7FD;
    reg |= (uint32_t)adcConfig->dataAlign | \
           (uint32_t)adcConfig->externalTrigConv | \
           ((uint32_t)adcConfig->continuosConvMode << 1);

    adc->CTRL2 = reg;

    reg = adc->REGSEQ1;
    reg &= 0xFF0FFFFF;
    reg |= (uint32_t)((adcConfig->nbrOfChannel - (uint8_t)1) << 20);
    adc->REGSEQ1 = reg;
}

/*!
 * @brief       Fills each ADC_Config_T member with its default value.
 *
 * @param       adcConfig: pointer to a ADC_Config_T structure which will be initialized.
 *
 * @retval      None
 */
void ADC_ConfigStructInit(ADC_Config_T* adcConfig)
{
    adcConfig->mode = ADC_MODE_INDEPENDENT;
    adcConfig->scanConvMode = DISABLE;
    adcConfig->continuosConvMode = DISABLE;
    adcConfig->externalTrigConv = ADC_EXT_TRIG_CONV_TMR1_CC1;
    adcConfig->dataAlign = ADC_DATA_ALIGN_RIGHT;
    adcConfig->nbrOfChannel = 1;
}

/*!
 * @brief       Enables the specified ADC peripheral.
 *
 * @param       adc: Select the ADC peripheral.
 *
 * @retval      None
 *
 * @note        adc can be ADC1, ADC2.
 */
void ADC_Enable(ADC_T* adc)
{
    adc->CTRL2_B.ADCEN = BIT_SET;
}

/*!
 * @brief        Disable the specified ADC peripheral.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_Disable(ADC_T* adc)
{
    adc->CTRL2_B.ADCEN = BIT_RESET;
}

/*!
 * @brief        Disable the specified ADC DMA request.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_EnableDMA(ADC_T* adc)
{
    adc->CTRL2_B.DMAEN = BIT_SET;
}

/*!
 * @brief        Disable the specified ADC DMA request.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_DisableDMA(ADC_T* adc)
{
    adc->CTRL2_B.DMAEN = BIT_RESET;
}

/*!
 * @brief        Reset the specified ADC calibration registers.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_ResetCalibration(ADC_T* adc)
{
    adc->CTRL2_B.CALRST = BIT_SET;
}

/*!
 * @brief        Reads the specified ADC calibration reset status.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       The status of ADC calibration reset.
 *
 * @note         adc can be ADC1, ADC2.
 */
uint8_t ADC_ReadResetCalibrationStatus(ADC_T* adc)
{
    uint8_t ret;
    ret = (adc->CTRL2_B.CALRST) ? BIT_SET : BIT_RESET;
    return ret;
}

/*!
 * @brief        Starts the specified ADC calibration.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_StartCalibration(ADC_T* adc)
{
    adc->CTRL2_B.CAL = BIT_SET;
}

/*!
 * @brief        Reads the specified ADC calibration start flag.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       The status of ADC calibration start.
 *
 * @note         adc can be ADC1, ADC2.
 */
uint8_t ADC_ReadCalibrationStartFlag(ADC_T* adc)
{
    uint8_t ret;
    ret = (adc->CTRL2_B.CAL) ? BIT_SET : BIT_RESET;
    return ret;
}

/*!
 * @brief        Enables the specified ADC software start conversion.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_EnableSoftwareStartConv(ADC_T* adc)
{
    adc->CTRL2 |= 0x00500000;
}

/*!
 * @brief        Disable the specified ADC software start conversion.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_DisableSoftwareStartConv(ADC_T* adc)
{
    adc->CTRL2 &= 0xFFAFFFFF;
}

/*!
 * @brief        Reads the specified ADC Software start conversion Status.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       The status of ADC Software start conversion registers.
 *
 * @note         adc can be ADC1, ADC2.
 */
uint8_t ADC_ReadSoftwareStartConvStatus(ADC_T* adc)
{
    uint8_t ret;
    ret = (adc->CTRL2_B.REGSWSC) ? BIT_SET : BIT_RESET;
    return ret;
}

/*!
 * @brief        Configures the specified ADC regular discontinuous mode.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @param        number: The number of the discontinuous mode regular channels.
 *                       This parameter can be between 1 and 8.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_ConfigDiscMode(ADC_T* adc, uint8_t number)
{
    adc->CTRL1_B.DISCNUMCFG |= number - 1;
}

/*!
 * @brief        Enable the specified ADC regular discontinuous mode.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_EnableDiscMode(ADC_T* adc)
{
    adc->CTRL1_B.REGDISCEN = BIT_SET;
}

/*!
 * @brief        Disable the specified ADC regular discontinuous mode.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_DisableDiscMode(ADC_T* adc)
{
    adc->CTRL1_B.REGDISCEN = BIT_RESET;
}

/*!
 * @brief        Configures the specified ADC regular channel.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @param        channel: Select the ADC channel.
 *                        This parameter can be one of the following values:
 *                        @arg ADC_CHANNEL_0:  ADC channel 0
 *                        @arg ADC_CHANNEL_1:  ADC channel 1
 *                        @arg ADC_CHANNEL_2:  ADC channel 2
 *                        @arg ADC_CHANNEL_3:  ADC channel 3
 *                        @arg ADC_CHANNEL_4:  ADC channel 4
 *                        @arg ADC_CHANNEL_5:  ADC channel 5
 *                        @arg ADC_CHANNEL_6:  ADC channel 6
 *                        @arg ADC_CHANNEL_7:  ADC channel 7
 *                        @arg ADC_CHANNEL_8:  ADC channel 8
 *                        @arg ADC_CHANNEL_9:  ADC channel 9
 *                        @arg ADC_CHANNEL_10: ADC channel 10
 *                        @arg ADC_CHANNEL_11: ADC channel 11
 *                        @arg ADC_CHANNEL_12: ADC channel 12
 *                        @arg ADC_CHANNEL_13: ADC channel 13
 *                        @arg ADC_CHANNEL_14: ADC channel 14
 *                        @arg ADC_CHANNEL_15: ADC channel 15
 *                        @arg ADC_CHANNEL_16: ADC channel 16 which is connected to TempSensor
 *                        @arg ADC_CHANNEL_17: ADC channel 17 which is connected to Vrefint
 *
 * @param        rank: The rank in the regular group sequencer
 *                     This parameter must be between 1 to 16.
 *
 * @param        sampleTime: the specified ADC channel SampleTime
 *                           The parameter can be one of following values:
 *                           @arg ADC_SAMPLETIME_1CYCLES5:   ADC 1.5 clock cycles
 *                           @arg ADC_SAMPLETIME_7CYCLES5:   ADC 7.5 clock cycles
 *                           @arg ADC_SAMPLETIME_13CYCLES5:  ADC 13.5 clock cycles
 *                           @arg ADC_SAMPLETIME_28CYCLES5:  ADC 28.5 clock cycles
 *                           @arg ADC_SAMPLETIME_41CYCLES5:  ADC 41.5 clock cycles
 *                           @arg ADC_SAMPLETIME_55CYCLES5:  ADC 55.5 clock cycles
 *                           @arg ADC_SAMPLETIME_71CYCLES5:  ADC 71.5 clock cycles
 *                           @arg ADC_SAMPLETIME_239CYCLES5: ADC 239.5 clock cycles
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_ConfigRegularChannel(ADC_T* adc, uint8_t channel, uint8_t rank, uint8_t sampleTime)
{
    uint32_t temp1 = 0;
    uint32_t temp2 = 0;
    if (channel > ADC_CHANNEL_9)
    {
        temp1 = adc->SMPTIM1;
        temp2 = SMPCYCCFG_SET_SMPTIM1 << (3 * (channel - 10));
        temp1 &= ~temp2;
        temp2 = (uint32_t)sampleTime << (3 * (channel - 10));
        temp1 |= temp2;
        adc->SMPTIM1 = temp1;
    }
    else
    {
        temp1 = adc->SMPTIM2;
        temp2 = SMPCYCCFG_SET_SMPTIM2 << (3 * channel);
        temp1 &= ~temp2;
        temp2 = (uint32_t)sampleTime << (3 * channel);
        temp1 |= temp2;
        adc->SMPTIM2 = temp1;
    }

    if (rank < 7)
    {
        temp1 = adc->REGSEQ3;
        temp2 = REGSEQC_SET_REGSEQ3 << (5 * (rank - 1));
        temp1 &= ~temp2;
        temp2 = (uint32_t)channel << (5 * (rank - 1));
        temp1 |= temp2;
        adc->REGSEQ3 = temp1;
    }
    else if (rank < 13)
    {
        temp1 = adc->REGSEQ2;
        temp2 = REGSEQC_SET_REGSEQ2 << (5 * (rank - 7));
        temp1 &= ~temp2;
        temp2 = (uint32_t)channel << (5 * (rank - 7));
        temp1 |= temp2;
        adc->REGSEQ2 = temp1;
    }
    else
    {
        temp1 = adc->REGSEQ1;
        temp2 = REGSEQC_SET_REGSEQ1 << (5 * (rank - 13));
        temp1 &= ~temp2;
        temp2 = (uint32_t)channel << (5 * (rank - 13));
        temp1 |= temp2;
        adc->REGSEQ1 = temp1;
    }
}

/*!
 * @brief        Enable the specified ADC regular channel external trigger.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_EnableExternalTrigConv(ADC_T* adc)
{
    adc->CTRL2_B.REGEXTTRGEN = BIT_SET;
}

/*!
 * @brief        Disable the specified ADC regular channel external trigger.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_DisableExternalTrigConv(ADC_T* adc)
{
    adc->CTRL2_B.REGEXTTRGEN = BIT_RESET;
}

/*!
 * @brief        Reads the specified ADC conversion result data.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       The Data conversion value.
 *
 * @note         adc can be ADC1, ADC2.
 */
uint16_t ADC_ReadConversionValue(ADC_T* adc)
{
    return (uint16_t) adc->REGDATA;
}

/*!
 * @brief        Reads the specified ADC conversion result data in dual mode.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       The Data conversion value.
 *
 * @note         adc can be ADC1, ADC2.
 */
uint32_t ADC_ReadDualModeConversionValue(ADC_T* adc)
{
    return (*(__IOM uint32_t*) RDG_ADDRESS);
}

/*!
 * @brief        Enable the specified ADC automatic injected group.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_EnableAutoInjectedConv(ADC_T* adc)
{
    adc->CTRL1_B.INJGACEN = BIT_SET;
}

/*!
 * @brief        Disable the specified ADC automatic injected group.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_DisableAutoInjectedConv(ADC_T* adc)
{
    adc->CTRL1_B.INJGACEN = BIT_RESET;
}

/*!
 * @brief        Enable the specified ADC discontinuous mode for injected group.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_EnableInjectedDiscMode(ADC_T* adc)
{
    adc->CTRL1_B.INJDISCEN = BIT_SET;
}

/*!
 * @brief        Disable the specified ADC discontinuous mode for injected group.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_DisableInjectedDiscMode(ADC_T* adc)
{
    adc->CTRL1_B.INJDISCEN = BIT_RESET;
}

/*!
 * @brief   Configures the specified ADC external trigger for injected channels conversion
 *
 * @param   adc: Select the ADC peripheral
 *
 * @param   extTrigInjecConv: Select the ADC trigger to start injected conversion
 *             This parameter can be one of the following values:
 *               @arg ADC_EXT_TRIG_INJEC_CONV_TMR1_TRGO : Select Timer1 TRGO event
 *               @arg ADC_EXT_TRIG_INJEC_CONV_TMR1_CC4  : Select Timer1 capture compare4
 *               @arg ADC_EXT_TRIG_INJEC_CONV_TMR2_TRGO : Select Timer2 TRGO event
 *               @arg ADC_EXT_TRIG_INJEC_CONV_TMR2_CC1  : Select Timer2 capture compare1
 *               @arg ADC_EXT_TRIG_INJEC_CONV_TMR3_CC4  : Select Timer3 capture compare4
 *               @arg ADC_EXT_TRIG_INJEC_CONV_TMR4_TRGO : Select Timer4 TRGO event selected
 *               @arg ADC_EXT_TRIG_INJEC_CONV_EINT15    : External interrupt line 15
 *               @arg ADC_EXT_TRIG_INJEC_CONV_NONE      : Injected conversion started by software instead of external trigger
 *
 * @retval  None
 *
 * @note    adc can be ADC1, ADC2.
 */
void ADC_ConfigExternalTrigInjectedConv(ADC_T* adc, ADC_EXT_TRIG_INJEC_CONV_T extTrigInjecConv)
{
    adc->CTRL2_B.INJGEXTTRGSEL = RESET;
    adc->CTRL2_B.INJGEXTTRGSEL |= extTrigInjecConv;
}

/*!
 * @brief        Ensable the specified ADC injected channels conversion through
 *
 * @param        adc: Select the ADC peripheral
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_EnableExternalTrigInjectedConv(ADC_T* adc)
{
    adc->CTRL2_B.INJEXTTRGEN = BIT_SET;
}

/*!
 * @brief        Disable the specified ADC injected channels conversion through
 *
 * @param        adc: Select the ADC peripheral
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_DisableExternalTrigInjectedConv(ADC_T* adc)
{
    adc->CTRL2_B.INJEXTTRGEN = BIT_RESET;
}

/*!
 * @brief        Enable the specified ADC start of the injected
 *
 * @param        adc: Select the ADC peripheral
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_EnableSoftwareStartInjectedConv(ADC_T* adc)
{
    adc->CTRL2_B.INJEXTTRGEN = BIT_SET;
    adc->CTRL2_B.INJSWSC = BIT_SET;
}

/*!
 * @brief        Disable the specified ADC start of the injected
 *
 * @param        adc: Select the ADC peripheral
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_DisableSoftwareStartInjectedConv(ADC_T* adc)
{
    adc->CTRL2_B.INJEXTTRGEN = BIT_RESET;
    adc->CTRL2_B.INJSWSC = BIT_RESET;
}

/*!
 * @brief        Reads the specified ADC Software start injected conversion Status
 *
 * @param        adc: Select the ADC peripheral
 *
 * @retval       The status of ADC Software start injected conversion
 *
 * @note         adc can be ADC1, ADC2.
 */
uint8_t ADC_ReadSoftwareStartInjectedConvStatus(ADC_T* adc)
{
    uint8_t ret;
    ret = (adc->CTRL2_B.INJSWSC) ? BIT_SET : BIT_RESET;
    return ret;
}

/*!
 * @brief        Configures the specified ADC injected channel.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @param        channel: Select the ADC injected channel.
 *                        This parameter can be one of the following values:
 *                        @arg ADC_CHANNEL_0:  ADC channel 0
 *                        @arg ADC_CHANNEL_1:  ADC channel 1
 *                        @arg ADC_CHANNEL_2:  ADC channel 2
 *                        @arg ADC_CHANNEL_3:  ADC channel 3
 *                        @arg ADC_CHANNEL_4:  ADC channel 4
 *                        @arg ADC_CHANNEL_5:  ADC channel 5
 *                        @arg ADC_CHANNEL_6:  ADC channel 6
 *                        @arg ADC_CHANNEL_7:  ADC channel 7
 *                        @arg ADC_CHANNEL_8:  ADC channel 8
 *                        @arg ADC_CHANNEL_9:  ADC channel 9
 *                        @arg ADC_CHANNEL_10: ADC channel 10
 *                        @arg ADC_CHANNEL_11: ADC channel 11
 *                        @arg ADC_CHANNEL_12: ADC channel 12
 *                        @arg ADC_CHANNEL_13: ADC channel 13
 *                        @arg ADC_CHANNEL_14: ADC channel 14
 *                        @arg ADC_CHANNEL_15: ADC channel 15
 *                        @arg ADC_CHANNEL_16: ADC channel 16 which is connected to TempSensor
 *                        @arg ADC_CHANNEL_17: ADC channel 17 which is connected to Vrefint
 *
 * @param        rank: The rank in the injected group sequencer.
 *                     This parameter must be between 1 to 4.
 *
 * @param        sampleTime: the specified ADC channel SampleTime
 *                           The parameter can be one of following values:
 *                           @arg ADC_SAMPLETIME_1CYCLES5:   ADC 1.5 clock cycles
 *                           @arg ADC_SAMPLETIME_7CYCLES5:   ADC 7.5 clock cycles
 *                           @arg ADC_SAMPLETIME_13CYCLES5:  ADC 13.5 clock cycles
 *                           @arg ADC_SAMPLETIME_28CYCLES5:  ADC 28.5 clock cycles
 *                           @arg ADC_SAMPLETIME_41CYCLES5:  ADC 41.5 clock cycles
 *                           @arg ADC_SAMPLETIME_55CYCLES5:  ADC 55.5 clock cycles
 *                           @arg ADC_SAMPLETIME_71CYCLES5:  ADC 71.5 clock cycles
 *                           @arg ADC_SAMPLETIME_239CYCLES5: ADC 239.5 clock cycles
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_ConfigInjectedChannel(ADC_T* adc, uint8_t channel, uint8_t rank, uint8_t sampleTime)
{
    uint32_t temp1 = 0;
    uint32_t temp2 = 0;
    uint32_t temp3 = 0;
    if (channel > ADC_CHANNEL_9)
    {
        temp1 = adc->SMPTIM1;
        temp2 = SMPCYCCFG_SET_SMPTIM1 << (3 * (channel - 10));
        temp1 &= ~temp2;
        temp2 = (uint32_t)sampleTime << (3 * (channel - 10));
        temp1 |= temp2;
        adc->SMPTIM1 = temp1;
    }
    else
    {
        temp1 = adc->SMPTIM2;
        temp2 = SMPCYCCFG_SET_SMPTIM2 << (3 * channel);
        temp1 &= ~temp2;
        temp2 = (uint32_t)sampleTime << (3 * channel);
        temp1 |= temp2;
        adc->SMPTIM2 = temp1;
    }
    temp1 = adc->INJSEQ;
    temp3 = (temp1 & INJSEQ_SET_INJSEQLEN) >> 20;
    temp2 = INJSEQ_SET_INJSEQC << (5 * (uint8_t)((rank + 3) - (temp3 + 1)));
    temp1 &= ~temp2;
    temp2 = (uint32_t)channel << (5 * (uint8_t)((rank + 3) - (temp3 + 1)));
    temp1 |= temp2;
    adc->INJSEQ = temp1;
}

/*!
 * @brief    Configures the specified ADC injected channel.
 *
 * @param    adc: Select the ADC peripheral.
 *
 * @param    length: The sequencer length.
 *                   This parameter must be a number between 1 to 4.
 *
 * @retval   None
 *
 * @note     adc can be ADC1, ADC2.
 */
void ADC_ConfigInjectedSequencerLength(ADC_T* adc, uint8_t length)
{
    adc->INJSEQ_B.INJSEQLEN = RESET;
    adc->INJSEQ_B.INJSEQLEN |= length - 1;
}

/*!
 * @brief     Configures the specified ADC injected channel conversion value offset.
 *
 * @param     adc: Select the ADC peripheral.
 *
 * @param     channel: Select the ADC injected channel.
 *                     This parameter can be one of the following values:
 *                     @arg ADC_INJEC_CHANNEL_1: select Injected Channel 1
 *                     @arg ADC_INJEC_CHANNEL_2: select Injected Channel 2
 *                     @arg ADC_INJEC_CHANNEL_3: select Injected Channel 3
 *                     @arg ADC_INJEC_CHANNEL_4: select Injected Channel 4
 *
 * @param     offSet: The specified ADC injected channel offset.
 *                    This parameter must be a 12bit value.
 *
 * @retval    None
 *
 * @note      adc can be ADC1, ADC2.
 */
void ADC_ConfigInjectedOffset(ADC_T* adc, ADC_INJEC_CHANNEL_T channel, uint16_t offSet)
{
    __IOM uint32_t tmp = 0;

    tmp = (uint32_t)adc;
    tmp += channel;

    *(__IOM uint32_t*) tmp = (uint32_t)offSet;
}

/*!
 * @brief     Reads the ADC injected channel conversion value.
 *
 * @param     adc: Select the ADC peripheral.
 *
 * @param     channel: Select the ADC injected channel.
 *                     This parameter can be one of the following values:
 *                     @arg ADC_INJEC_CHANNEL_1: select Injected Channel 1
 *                     @arg ADC_INJEC_CHANNEL_2: select Injected Channel 2
 *                     @arg ADC_INJEC_CHANNEL_3: select Injected Channel 3
 *                     @arg ADC_INJEC_CHANNEL_4: select Injected Channel 4
 *
 * @retval    The Data of conversion value.
 *
 * @note      adc can be ADC1, ADC2.
 */
uint16_t ADC_ReadInjectedConversionValue(ADC_T* adc, ADC_INJEC_CHANNEL_T channel)
{
    __IOM uint32_t temp = 0;

    temp = (uint32_t)adc;
    temp += channel + INJDATA_OFFSET;

    return (uint16_t)(*(__IOM uint32_t*)  temp);
}

/*!
 * @brief        Enable the specified ADC analog watchdog.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @param        analogWatchdog: The ADC analog watchdog configuration
 *                  This parameter can be one of the following values:
 *                  @arg ADC_ANALOG_WATCHDOG_SINGLE_REG        : Analog watchdog on a single regular channel
 *                  @arg ADC_ANALOG_WATCHDOG_SINGLE_INJEC      : Analog watchdog on a single injected channel
 *                  @arg ADC_ANALOG_WATCHDOG_SINGLE_REG_INJEC  : Analog watchdog on a single regular or injected channel
 *                  @arg ADC_ANALOG_WATCHDOG_ALL_REG           : Analog watchdog on  all regular channel
 *                  @arg ADC_ANALOG_WATCHDOG_ALL_INJEC         : Analog watchdog on  all injected channel
 *                  @arg ADC_ANALOG_WATCHDOG_ALL_REG_ALL_INJEC : Analog watchdog on all regular and injected channels
 *                  @arg ADC_ANALOG_WATCHDOG_NONE              : No channel guarded by the analog watchdog
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_EnableAnalogWatchdog(ADC_T* adc, uint32_t analogWatchdog)
{
    adc->CTRL1 &= 0xFF3FFDFF;
    adc->CTRL1 |= analogWatchdog;
}

/*!
 * @brief        Disable the specified ADC analog watchdog.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_DisableAnalogWatchdog(ADC_T* adc)
{
    adc->CTRL1 &= 0xFF3FFDFF;
}

/*!
 * @brief        Configures the specified ADC high and low thresholds of the analog watchdog.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @param        highThreshold: The ADC analog watchdog High threshold value.
 *                              This parameter must be a 12bit value.
 *
 * @param        lowThreshold: The ADC analog watchdog Low threshold value.
 *                             This parameter must be a 12bit value.
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_ConfigAnalogWatchdogThresholds(ADC_T* adc, uint16_t highThreshold, uint16_t lowThreshold)
{
    adc->AWDHT = highThreshold;
    adc->AWDLT = lowThreshold;
}

/*!
 * @brief      Configures the specified ADC analog watchdog guarded single channel
 *
 * @param      adc: Select the ADC peripheral
 *
 * @param      channel: Select the ADC channel
 *                      This parameter can be one of the following values:
 *                        @arg ADC_Channel_0:  Select ADC Channel 0
 *                        @arg ADC_Channel_1:  Select ADC Channel 1
 *                        @arg ADC_Channel_2:  Select ADC Channel 2
 *                        @arg ADC_Channel_3:  Select ADC Channel 3
 *                        @arg ADC_Channel_4:  Select ADC Channel 4
 *                        @arg ADC_Channel_5:  Select ADC Channel 5
 *                        @arg ADC_Channel_6:  Select ADC Channel 6
 *                        @arg ADC_Channel_7:  Select ADC Channel 7
 *                        @arg ADC_Channel_8:  Select ADC Channel 8
 *                        @arg ADC_Channel_9:  Select ADC Channel 9
 *                        @arg ADC_Channel_10: Select ADC Channel 10
 *                        @arg ADC_Channel_11: Select ADC Channel 11
 *                        @arg ADC_Channel_12: Select ADC Channel 12
 *                        @arg ADC_Channel_13: Select ADC Channel 13
 *                        @arg ADC_Channel_14: Select ADC Channel 14
 *                        @arg ADC_Channel_15: Select ADC Channel 15
 *                        @arg ADC_Channel_16: Select ADC Channel 16 which is connected to TempSensor
 *                        @arg ADC_Channel_17: Select ADC Channel 17 which is connected to Vrefint
 *
 * @retval     None
 *
 * @note       adc can be ADC1, ADC2.
 */
void ADC_ConfigAnalogWatchdogSingleChannel(ADC_T* adc, uint8_t channel)
{
    adc->CTRL1_B.AWDCHSEL = BIT_RESET;
    adc->CTRL1 |= channel;
}

/*!
 * @brief      Enable the specified ADC temperature sensor and Vrefint channel.
 *
 * @param      adc: Select the ADC peripheral.
 *
 * @retval     None
 *
 * @note       adc can be ADC1, ADC2.
 */
void ADC_EnableTempSensorVrefint(ADC_T* adc)
{
    adc->CTRL2_B.TSVREFEN = BIT_SET;
}

/*!
 * @brief      Disable the specified ADC temperature sensor and Vrefint channel.
 *
 * @param      adc: Select the ADC peripheral
 *
 * @retval     None
 *
 * @note       adc can be ADC1, ADC2.
 */
void ADC_DisableTempSensorVrefint(ADC_T* adc)
{
    adc->CTRL2_B.TSVREFEN = BIT_RESET;
}

/*!
 * @brief      Enable the specified ADC interrupt.
 *
 * @param      adc: Select the ADC peripheral.
 *
 * @param      interrupt: Select the ADC interrupt sources
 *                        This parameter can be any combination of the following values:
 *                        @arg ADC_INT_AWD    : Enable Analog watchdog interrupt
 *                        @arg ADC_INT_EOC    : Enable End of conversion interrupt
 *                        @arg ADC_INT_INJEOC : Enable End of injected conversion interrupt
 *
 * @retval     None
 *
 * @note       adc can be ADC1, ADC2.
 */
void ADC_EnableInterrupt(ADC_T* adc, uint16_t interrupt)
{
    uint8_t mask;

    mask = (uint8_t)interrupt;
    adc->CTRL1 |= (uint8_t)mask;
}

/*!
 * @brief      Disable the specified ADC interrupt.
 *
 * @param      adc: Select the ADC peripheral.
 *
 * @param      interrupt: Select the ADC interrupt sources
 *                        This parameter can be any combination of the following values:
 *                        @arg ADC_INT_AWD    : Disable Analog watchdog interrupt
 *                        @arg ADC_INT_EOC    : Disable End of conversion interrupt
 *                        @arg ADC_INT_INJEOC : Disable End of injected conversion interrupt
 *
 * @retval     None
 *
 * @note       adc can be ADC1, ADC2.
 */
void ADC_DisableInterrupt(ADC_T* adc, uint16_t interrupt)
{
    uint8_t mask;

    mask = (uint8_t)interrupt;
    adc->CTRL1 &= (~(uint32_t)mask);
}

/*!
 * @brief     Reads the specified ADC flag
 *
 * @param     adc: Select the ADC peripheral
 *
 * @param     flag: Select the flag to check
 *                  This parameter can be one of the following values:
 *                  @arg ADC_FLAG_AWD   : Analog watchdog flag
 *                  @arg ADC_FLAG_EOC   : End of conversion flag
 *                  @arg ADC_FLAG_INJEOC: End of injected group conversion flag
 *                  @arg ADC_FLAG_INJCS : Injected group conversion Start flag
 *                  @arg ADC_FLAG_REGCS : Regular group conversion Start flag
 *
 * @retval    The status of ADC flag
 *
 * @note      adc can be ADC1, ADC2.
 */
uint8_t ADC_ReadStatusFlag(ADC_T* adc, ADC_FLAG_T flag)
{
    return (adc->STS & flag) ? SET : RESET;
}

/*!
 * @brief     Clears the specified ADC flag
 *
 * @param     adc: Select the ADC peripheral
 *
 * @param     flag: Select the flag to clear
 *                  This parameter can be any combination of the following values:
 *                  @arg ADC_FLAG_AWD   : Analog watchdog flag
 *                  @arg ADC_FLAG_EOC   : End of conversion flag
 *                  @arg ADC_FLAG_INJEOC: End of injected group conversion flag
 *                  @arg ADC_FLAG_INJCS : Injected group conversion Start flag
 *                  @arg ADC_FLAG_REGCS : Regular group conversion Start flag
 *
 * @retval    None
 *
 * @note      adc can be ADC1, ADC2.
 */
void ADC_ClearStatusFlag(ADC_T* adc, uint8_t flag)
{
    adc->STS = ~(uint32_t)flag;
}

/*!
 * @brief        Reads the specified ADC Interrupt flag.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @param        interrupt: Select the ADC interrupt source.
 *                          This parameter can be one of the following values:
 *                          @arg ADC_INT_AWD    : Enable Analog watchdog interrupt
 *                          @arg ADC_INT_EOC    : Enable End of conversion interrupt
 *                          @arg ADC_INT_INJEOC : Enable End of injected conversion interrupt
 *
 * @retval       The status of ADC interrupt
 *
 * @note         adc can be ADC1, ADC2.
 */
uint8_t ADC_ReadIntFlag(ADC_T* adc, ADC_INT_T flag)
{
    uint8_t bitStatus = RESET;
    uint32_t itmask = 0;
    uint32_t enableStatus = 0;

    itmask = flag >> 8;
    enableStatus = (adc->CTRL1 & (uint8_t)flag);

    if (((adc->STS & itmask) != (uint32_t)RESET) && enableStatus)
    {
        bitStatus = SET;
    }
    else
    {
        bitStatus = RESET;
    }
    return  bitStatus;
}

/*!
 * @brief        Clears the specified ADC Interrupt pending bits.
 *
 * @param        adc: Select the ADC peripheral.
 *
 * @param        interrupt: Select the ADC interrupt source.
 *                          This parameter can be any combination of the following values:
 *                          @arg ADC_INT_AWD    : Enable Analog watchdog interrupt
 *                          @arg ADC_INT_EOC    : Enable End of conversion interrupt
 *                          @arg ADC_INT_INJEOC : Enable End of injected conversion interrupt
 *
 * @retval       None
 *
 * @note         adc can be ADC1, ADC2.
 */
void ADC_ClearIntFlag(ADC_T* adc, uint16_t flag)
{
    uint8_t mask = 0;

    mask = (uint8_t)(flag >> 8);
    adc->STS = ~(uint32_t)mask;
}

/**@} end of group ADC_Functions */
/**@} end of group ADC_Driver */
/**@} end of group APM32S10x_StdPeriphDriver */
