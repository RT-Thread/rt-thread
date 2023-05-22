/*!
 * @file        apm32s10x_tmr.c
 *
 * @brief       This file provides all the TMR firmware functions.
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
#include "apm32s10x_tmr.h"
#include "apm32s10x_rcm.h"

/** @addtogroup APM32S10x_StdPeriphDriver
  @{
*/

/** @addtogroup TMR_Driver  TMR Driver
  @{
*/

/** @defgroup  TMR_Functions Functions
  @{
*/

static void TI1Config(TMR_T* tmr, uint16_t ICpolarity, uint16_t ICselection, uint16_t ICfilter);
static void TI2Config(TMR_T* tmr, uint16_t ICpolarity, uint16_t ICselection, uint16_t ICfilter);
static void TI3Config(TMR_T* tmr, uint16_t ICpolarity, uint16_t ICselection, uint16_t ICfilter);
static void TI4Config(TMR_T* tmr, uint16_t ICpolarity, uint16_t ICselection, uint16_t ICfilter);

/*!
 * @brief     Deinitialize the TMRx peripheral registers to their default reset values.
 *
 * @param     tmr: Select TMRx peripheral, The x can be 1 to 8
 *
 * @retval    None
 */
void TMR_Reset(TMR_T* tmr)
{
    if (tmr == TMR1)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_TMR1);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_TMR1);
    }
    else if (tmr == TMR2)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_TMR2);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_TMR2);
    }
    else if (tmr == TMR3)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_TMR3);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_TMR3);
    }
    else if (tmr == TMR4)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_TMR4);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_TMR4);
    }
}

/*!
 * @brief     Initialize the base timer through the structure
 *
 * @param     tmr: Select TMRx peripheral, The x can be 1 to 4
 *
 * @param     baseConfig: Pointer to a TMR_BaseConfig_T structure
 *
 * @retval    None
 */
void TMR_ConfigTimeBase(TMR_T* tmr, TMR_BaseConfig_T* baseConfig)
{
    uint16_t temp;

    if ((tmr == TMR1) || (tmr == TMR2) || (tmr == TMR3) || (tmr == TMR4))
    {
        temp = tmr->CTRL1;
        temp &= 0x038F;
        temp |= baseConfig->countMode;
        tmr->CTRL1 = temp;
    }

    tmr->AUTORLD = baseConfig->period;
    tmr->PSC = baseConfig->division;

    if (tmr == TMR1)
    {
        tmr->REPCNT = baseConfig->repetitionCounter;
    }
    tmr->CEG_B.UEG = 0x01;
}

/*!
 * @brief     Configure channel 1 according to parameters
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCConfig: Pointer to a TMR_OCConfig_T structure
 *
 * @retval    None
 */
void TMR_ConfigOC1(TMR_T* tmr, TMR_OCConfig_T* OCConfig)
{
    tmr->CCEN_B.CC1EN = BIT_RESET;

    tmr->CCM1_COMPARE_B.CC1SEL = BIT_RESET;
    tmr->CCM1_COMPARE_B.OC1MOD = OCConfig->mode;

    tmr->CCEN_B.CC1POL = OCConfig->polarity;
    tmr->CCEN_B.CC1EN = OCConfig->outputState;

    if (tmr == TMR1)
    {
        tmr->CCEN_B.CC1NPOL = OCConfig->nPolarity;
        tmr->CCEN_B.CC1NEN = OCConfig->outputNState;

        tmr->CTRL2_B.OC1OIS = BIT_RESET;
        tmr->CTRL2_B.OC1NOIS = BIT_RESET;
        tmr->CTRL2_B.OC1OIS = OCConfig->idleState;
        tmr->CTRL2_B.OC1NOIS = OCConfig->nIdleState;
    }
    tmr->CC1 = OCConfig->pulse;
}

/*!
 * @brief     Configure channel 2 according to parameters
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCConfig: Pointer to a TMR_OCConfig_T structure
 *
 * @retval    None
 */
void TMR_ConfigOC2(TMR_T* tmr, TMR_OCConfig_T* OCConfig)
{
    tmr->CCEN_B.CC2EN = BIT_RESET;

    tmr->CCM1_COMPARE_B.OC2MOD = BIT_RESET;
    tmr->CCM1_COMPARE_B.CC2SEL = BIT_RESET;
    tmr->CCM1_COMPARE_B.OC2MOD = OCConfig->mode;

    tmr->CCEN_B.CC2POL = BIT_RESET;
    tmr->CCEN_B.CC2POL = OCConfig->polarity;
    tmr->CCEN_B.CC2EN = OCConfig->outputState;

    if (tmr == TMR1)
    {
        tmr->CCEN_B.CC2NPOL = BIT_RESET;
        tmr->CCEN_B.CC2NPOL = OCConfig->nPolarity;

        tmr->CCEN_B.CC2NEN = BIT_RESET;
        tmr->CCEN_B.CC2NEN = OCConfig->outputNState;

        tmr->CTRL2_B.OC2OIS = BIT_RESET;
        tmr->CTRL2_B.OC2NOIS = BIT_RESET;
        tmr->CTRL2_B.OC2OIS = OCConfig->idleState;
        tmr->CTRL2_B.OC2NOIS = OCConfig->nIdleState;
    }
    tmr->CC2 = OCConfig->pulse;
}

/*!
 * @brief     Configure channel 3 according to parameters
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCConfig: Pointer to a TMR_OCConfig_T structure
 *
 * @retval    None
 */
void TMR_ConfigOC3(TMR_T* tmr, TMR_OCConfig_T* OCConfig)
{
    tmr->CCEN_B.CC3EN = BIT_RESET;

    tmr->CCM2_COMPARE_B.OC3MOD = BIT_RESET;
    tmr->CCM2_COMPARE_B.CC3SEL = BIT_RESET;
    tmr->CCM2_COMPARE_B.OC3MOD = OCConfig->mode;

    tmr->CCEN_B.CC3POL = BIT_RESET;
    tmr->CCEN_B.CC3POL = OCConfig->polarity;
    tmr->CCEN_B.CC3EN = OCConfig->outputState;

    if (tmr == TMR1)
    {
        tmr->CCEN_B.CC3NPOL = BIT_RESET;
        tmr->CCEN_B.CC3NPOL = OCConfig->nPolarity;
        tmr->CCEN_B.CC3NEN = BIT_RESET;
        tmr->CCEN_B.CC3NEN = OCConfig->outputNState;

        tmr->CTRL2_B.OC3OIS = BIT_RESET;
        tmr->CTRL2_B.OC3NOIS = BIT_RESET;
        tmr->CTRL2_B.OC3OIS = OCConfig->idleState;
        tmr->CTRL2_B.OC3NOIS = OCConfig->nIdleState;
    }
    tmr->CC3 = OCConfig->pulse;
}

/*!
 * @brief     Configure channel 4 according to parameters
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCConfig: Pointer to a TMR_OCConfig_T structure
 *
 * @retval    None
 */
void TMR_ConfigOC4(TMR_T* tmr, TMR_OCConfig_T* OCConfig)
{
    tmr->CCEN_B.CC4EN = BIT_RESET;

    tmr->CCM2_COMPARE_B.OC4MOD = BIT_RESET;
    tmr->CCM2_COMPARE_B.CC4SEL = BIT_RESET;
    tmr->CCM2_COMPARE_B.OC4MOD = OCConfig->mode;

    tmr->CCEN_B.CC4POL = BIT_RESET;
    tmr->CCEN_B.CC4POL = OCConfig->polarity;
    tmr->CCEN_B.CC4EN = OCConfig->outputState;

    if (tmr == TMR1)
    {
        tmr->CTRL2_B.OC4OIS = BIT_RESET;
        tmr->CTRL2_B.OC4OIS = OCConfig->idleState;
    }
    tmr->CC4 = OCConfig->pulse;
}

/*!
 * @brief     Configure Peripheral equipment
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     ICConfig: Pointer to a TMR_ICConfig_T structure
 *
 * @retval    None
 */
void TMR_ConfigIC(TMR_T* tmr, TMR_ICConfig_T* ICConfig)
{
    if (ICConfig->channel == TMR_CHANNEL_1)
    {
        TI1Config(tmr, ICConfig->polarity, ICConfig->selection, ICConfig->filter);
        TMR_ConfigIC1Prescal(tmr, ICConfig->prescaler);
    }
    else if (ICConfig->channel == TMR_CHANNEL_2)
    {
        TI2Config(tmr, ICConfig->polarity, ICConfig->selection, ICConfig->filter);
        TMR_ConfigIC2Prescal(tmr, ICConfig->prescaler);
    }
    else if (ICConfig->channel == TMR_CHANNEL_3)
    {
        TI3Config(tmr, ICConfig->polarity, ICConfig->selection, ICConfig->filter);
        TMR_ConfigIC3Prescal(tmr, ICConfig->prescaler);
    }
    else if (ICConfig->channel == TMR_CHANNEL_4)
    {
        TI4Config(tmr, ICConfig->polarity, ICConfig->selection, ICConfig->filter);
        TMR_ConfigIC4Prescal(tmr, ICConfig->prescaler);
    }
}

/*!
 * @brief     Configure the Break feature, dead time, Lock level, the IMOS
 *
 * @param     tmr: The TMRx it can be TMR1
 *
 * @param     BDTConfig: Pointer to a TMR_BDTConfig_T structure
 *
 * @retval    None
 */
void TMR_ConfigBDT(TMR_T* tmr, TMR_BDTConfig_T* BDTConfig)
{
    tmr->BDT = (BDTConfig->IMOS) << 10 | \
               (BDTConfig->RMOS) << 11 | \
               (BDTConfig->lockLevel) << 8 | \
               (BDTConfig->deadTime) | \
               (BDTConfig->BRKState) << 12 | \
               (BDTConfig->BRKPolarity) << 13 | \
               (BDTConfig->automaticOutput) << 14;
}

/*!
 * @brief     Initialize the Base timer with its default value.
 *
 * @param     baseConfig: pointer to a TMR_BaseConfig_T
 *
 * @retval    None
 */
void TMR_ConfigTimeBaseStructInit(TMR_BaseConfig_T* baseConfig)
{
    baseConfig->period = 0xFFFF;
    baseConfig->division = 0x0000;
    baseConfig->clockDivision = TMR_CLOCK_DIV_1;
    baseConfig->countMode = TMR_COUNTER_MODE_UP;
    baseConfig->repetitionCounter = 0x0000;
}

/*!
 * @brief     Initialize the OC timer with its default value.
 *
 * @param     OCConfig: pointer to a TMR_OCConfig_T
 *
 * @retval    None
 */
void TMR_ConfigOCStructInit(TMR_OCConfig_T* OCConfig)
{
    OCConfig->mode = TMR_OC_MODE_TMRING;
    OCConfig->outputState = TMR_OC_STATE_DISABLE;
    OCConfig->outputNState = TMR_OC_NSTATE_DISABLE;
    OCConfig->pulse = 0x0000;
    OCConfig->polarity = TMR_OC_POLARITY_HIGH;
    OCConfig->nPolarity = TMR_OC_NPOLARITY_HIGH;
    OCConfig->idleState = TMR_OC_IDLE_STATE_RESET;
    OCConfig->nIdleState = TMR_OC_NIDLE_STATE_RESET;
}

/*!
 * @brief     Initialize the IC timer with its default value.
 *
 * @param     ICConfig: pointer to a TMR_ICConfig_T
 *
 * @retval    None
 */
void TMR_ConfigICStructInit(TMR_ICConfig_T* ICConfig)
{
    ICConfig->channel = TMR_CHANNEL_1;
    ICConfig->polarity = TMR_IC_POLARITY_RISING;
    ICConfig->selection = TMR_IC_SELECTION_DIRECT_TI;
    ICConfig->prescaler = TMR_IC_PSC_1;
    ICConfig->filter = 0x00;
}

/*!
 * @brief     Initialize the BDT timer with its default value.
 *
 * @param     BDTConfig: pointer to a TMR_BDTConfig_T
 *
 * @retval    None
 */
void TMR_ConfigBDTStructInit(TMR_BDTConfig_T* BDTConfig)
{
    BDTConfig->RMOS = TMR_RMOS_STATE_DISABLE;
    BDTConfig->IMOS = TMR_IMOS_STATE_DISABLE;
    BDTConfig->lockLevel = TMR_LOCK_LEVEL_OFF;
    BDTConfig->deadTime = 0x00;
    BDTConfig->BRKState = TMR_BRK_STATE_DISABLE;
    BDTConfig->BRKPolarity = TMR_BRK_POLARITY_LOW;
    BDTConfig->automaticOutput = TMR_AUTOMATIC_OUTPUT_DISABLE;
}

/*!
 * @brief     Enable the specified TMR peripheral
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    None
 */
void TMR_Enable(TMR_T* tmr)
{
    tmr->CTRL1_B.CNTEN = ENABLE;
}

/*!
 * @brief     Disable the specified TMR peripheral
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    None
 */
void TMR_Disable(TMR_T* tmr)
{
    tmr->CTRL1_B.CNTEN = DISABLE;
}

/*!
 * @brief     Configure of TMR to PWM
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     PWMConfig: pointer to a TMR_ICConfig_T
 *
 * @retval    None
 */
void TMR_ConfigPWM(TMR_T* tmr, TMR_ICConfig_T* PWMConfig)
{
    uint16_t icpolarity = TMR_IC_POLARITY_RISING;
    uint16_t icselection = TMR_IC_SELECTION_DIRECT_TI;

    if (PWMConfig->polarity == TMR_IC_POLARITY_RISING)
    {
        icpolarity = TMR_IC_POLARITY_FALLING;
    }
    else
    {
        icpolarity = TMR_IC_POLARITY_RISING;
    }

    if (PWMConfig->selection == TMR_IC_SELECTION_DIRECT_TI)
    {
        icselection = TMR_IC_SELECTION_INDIRECT_TI;
    }
    else
    {
        icselection = TMR_IC_SELECTION_DIRECT_TI;
    }

    if (PWMConfig->channel == TMR_CHANNEL_1)
    {
        TI1Config(tmr, PWMConfig->polarity, PWMConfig->selection, PWMConfig->filter);
        TMR_ConfigIC1Prescal(tmr, PWMConfig->prescaler);
        TI2Config(tmr, icpolarity, icselection, PWMConfig->filter);
        TMR_ConfigIC2Prescal(tmr, PWMConfig->prescaler);
    }
    else
    {
        TI2Config(tmr, PWMConfig->polarity, PWMConfig->selection, PWMConfig->filter);
        TMR_ConfigIC2Prescal(tmr, PWMConfig->prescaler);
        TI1Config(tmr, icpolarity, icselection, PWMConfig->filter);
        TMR_ConfigIC1Prescal(tmr, PWMConfig->prescaler);
    }
}

/*!
 * @brief     Enable TMRx PWM output
 *
 * @param     tmr: The TMRx it can be TMR1
 *
 * @retval    None
 */
void TMR_EnablePWMOutputs(TMR_T* tmr)
{
    tmr->BDT_B.MOEN = ENABLE;
}

/*!
 * @brief     Disable TMRx PWM output.
 *
 * @param     tmr: The TMRx it can be TMR1
 *
 * @retval    None
 */
void TMR_DisablePWMOutputs(TMR_T* tmr)
{
    tmr->BDT_B.MOEN = DISABLE;
}

/*!
 * @brief     Configure the TMRx's DMA interface.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     baseAddress: pointer to a TMR_DMA_BASE_T
 *
 * @param     burstLength: pointer to a TMR_DMA_BURSTLENGTH_T
 *
 * @retval    None
 */
void TMR_ConfigDMA(TMR_T* tmr, TMR_DMA_BASE_T baseAddress, TMR_DMA_BURSTLENGTH_T burstLength)
{
    tmr->DCTRL = (uint32_t)baseAddress | (uint32_t)burstLength;
}

/*!
 * @brief     Enable TMRx Requests.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     souces: specify the TMR DMA souces
 *              The parameter can be any combination of following values:
 *              @arg TMR_DMA_SOURCE_UPDATE: TMR update DMA souces
 *              @arg TMR_DMA_SOURCE_CC1:    TMR Capture Compare 1 DMA souces
 *              @arg TMR_DMA_SOURCE_CC2:    TMR Capture Compare 2 DMA souces
 *              @arg TMR_DMA_SOURCE_CC3:    TMR Capture Compare 3 DMA souces
 *              @arg TMR_DMA_SOURCE_CC4:    TMR Capture Compare 4 DMA souces
 *              @arg TMR_DMA_SOURCE_COM:    TMR Commutation DMA souces
 *              @arg TMR_DMA_SOURCE_TRG:    TMR Trigger DMA souces
 *
 * @retval    None
 *
 */
void TMR_EnableDMASoure(TMR_T* tmr, uint16_t dmaSource)
{
    tmr->DIEN |= dmaSource;
}

/*!
 * @brief     Disable TMRx Requests.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     souces: specify the TMR DMA souces
 *              The parameter can be any combination of following values:
 *              @arg TMR_DMA_SOURCE_UPDATE: TMR update DMA souces
 *              @arg TMR_DMA_SOURCE_CC1:    TMR Capture Compare 1 DMA souces
 *              @arg TMR_DMA_SOURCE_CC2:    TMR Capture Compare 2 DMA souces
 *              @arg TMR_DMA_SOURCE_CC3:    TMR Capture Compare 3 DMA souces
 *              @arg TMR_DMA_SOURCE_CC4:    TMR Capture Compare 4 DMA souces
 *              @arg TMR_DMA_SOURCE_COM:    TMR Commutation DMA souces
 *              @arg TMR_DMA_SOURCE_TRG:    TMR Trigger DMA souces
 *
 * @retval    None
 *
 */
void TMR_DisableDMASoure(TMR_T* tmr, uint16_t dmaSource)
{
    tmr->DIEN &= ~dmaSource;
}

/*!
 * @brief     Configure the TMRx internal Clock
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    None
 */
void TMR_ConfigInternalClock(TMR_T* tmr)
{
    tmr->SMCTRL_B.SMFSEL = DISABLE;
}

/*!
 * @brief     Configure the TMRx Internal Trigger as External Clock
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     triggerSource: specify the TMR trigger souces
 *              The parameter can be one of following values:
 *              @arg TMR_TRIGGER_SOURCE_ITR0: TMR Internal Trigger 0
 *              @arg TMR_TRIGGER_SOURCE_ITR1: TMR Internal Trigger 1
 *              @arg TMR_TRIGGER_SOURCE_ITR2: TMR Internal Trigger 2
 *              @arg TMR_TRIGGER_SOURCE_ITR3: TMR Internal Trigger 3
 *
 * @retval    None
 */
void TMR_ConfigIntTrigExternalClock(TMR_T* tmr, TMR_TRIGGER_SOURCE_T triggerSource)
{
    TMR_SelectInputTrigger(tmr, triggerSource);
    tmr->SMCTRL_B.SMFSEL = 0x07;
}

/*!
 * @brief     Configure the TMRx Trigger as External Clock
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     triggerSource: specify the TMR trigger souces
 *              The parameter can be one of following values:
 *              @arg TMR_TRIGGER_SOURCE_TI1F_ED: TI1 Edge Detector
 *              @arg TMR_TRIGGER_SOURCE_TI1FP1:  Filtered Timer Input 1
 *              @arg TMR_TRIGGER_SOURCE_TI2FP2:  Filtered Timer Input 2
 *
 * @param     ICpolarity: specify the TMR IC polarity
 *              The parameter can be one of following values:
 *              @arg TMR_IC_POLARITY_RISING:  TMR IC polarity rising
 *              @arg TMR_IC_POLARITY_FALLING: TMR IC polarity falling
 *
 * @param     ICfilter: This parameter must be a value between 0x00 and 0x0F.
 *
 * @retval    None
 */
void TMR_ConfigTrigExternalClock(TMR_T* tmr, TMR_TRIGGER_SOURCE_T triggerSource,
                                 TMR_IC_POLARITY_T ICpolarity, uint16_t ICfilter)
{
    if (triggerSource == 0x06)
    {
        TI2Config(tmr, ICpolarity, TMR_IC_SELECTION_DIRECT_TI, ICfilter);
    }
    else
    {
        TI1Config(tmr, ICpolarity, TMR_IC_SELECTION_DIRECT_TI, ICfilter);
    }

    TMR_SelectInputTrigger(tmr, triggerSource);
    tmr->SMCTRL_B.SMFSEL = 0x07;
}

/*!
 * @brief     Configure the External clock Mode1
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     prescaler: specify the external Trigger Prescaler
 *              The parameter can be one of following values:
 *              @arg TMR_EXTTRG_PSC_OFF:  ETRP Prescaler OFF
 *              @arg TMR_EXTTRG_PSC_DIV2: ETRP frequency divided by 2
 *              @arg TMR_EXTTRG_PSC_DIV4: ETRP frequency divided by 4
 *              @arg TMR_EXTTRG_PSC_DIV8: ETRP frequency divided by 8
 *
 * @param     polarity: specify the TMR IC polarity
 *              The parameter can be one of following values:
 *              @arg TMR_EXTTRG_POL_INVERTED:    Active low or falling edge active
 *              @arg TMR_EXTTGR_POL_NONINVERTED: Active high or rising edge active
 *
 * @param     filter: This parameter must be a value between 0x00 and 0x0F.
 *
 * @retval    None
 */
void TMR_ConfigETRClockMode1(TMR_T* tmr, TMR_EXTTRG_PSC_T prescaler,
                             TMR_EXTTRG_POL_T polarity, uint16_t filter)
{
    TMR_ConfigETR(tmr, prescaler, polarity, filter);
    tmr->SMCTRL_B.SMFSEL = BIT_RESET;
    tmr->SMCTRL_B.SMFSEL = 0x07;
    tmr->SMCTRL_B.TRGSEL = 0x07;
}

/*!
 * @brief     Configure the External clock Mode2
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     prescaler: specify the external Trigger Prescaler
 *              The parameter can be one of following values:
 *              @arg TMR_EXTTRG_PSC_OFF:  ETRP Prescaler OFF
 *              @arg TMR_EXTTRG_PSC_DIV2: ETRP frequency divided by 2
 *              @arg TMR_EXTTRG_PSC_DIV4: ETRP frequency divided by 4
 *              @arg TMR_EXTTRG_PSC_DIV8: ETRP frequency divided by 8
 *
 * @param     polarity: specify the TMR IC polarity
 *              The parameter can be one of following values:
 *              @arg TMR_EXTTRG_POL_INVERTED:    Active low or falling edge active
 *              @arg TMR_EXTTGR_POL_NONINVERTED: Active high or rising edge active
 *
 * @param     filter: This parameter must be a value between 0x00 and 0x0F.
 *
 * @retval    None
 */
void TMR_ConfigETRClockMode2(TMR_T* tmr, TMR_EXTTRG_PSC_T prescaler,
                             TMR_EXTTRG_POL_T polarity, uint16_t filter)
{
    TMR_ConfigETR(tmr, prescaler, polarity, filter);
    tmr->SMCTRL_B.ECEN = ENABLE;
}
/*!
 * @brief     Configure the TMRx External Trigger (ETR).
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     prescaler: specify the external Trigger Prescaler
 *              The parameter can be one of following values:
 *              @arg TMR_EXTTRG_PSC_OFF:  ETRP Prescaler OFF
 *              @arg TMR_EXTTRG_PSC_DIV2: ETRP frequency divided by 2
 *              @arg TMR_EXTTRG_PSC_DIV4: ETRP frequency divided by 4
 *              @arg TMR_EXTTRG_PSC_DIV8: ETRP frequency divided by 8
 *
 * @param     polarity: specify the TMR IC polarity
 *              The parameter can be one of following values:
 *              @arg TMR_EXTTRG_POL_INVERTED:    Active low or falling edge active
 *              @arg TMR_EXTTGR_POL_NONINVERTED: Active high or rising edge active
 *
 * @param     filter: This parameter must be a value between 0x00 and 0x0F.
 *
 * @retval    None
 */
void TMR_ConfigETR(TMR_T* tmr, TMR_EXTTRG_PSC_T prescaler,
                   TMR_EXTTRG_POL_T polarity, uint16_t filter)
{
    tmr->SMCTRL &= 0x00FF;
    tmr->SMCTRL_B.ETPCFG = prescaler;
    tmr->SMCTRL_B.ETPOL = polarity;
    tmr->SMCTRL_B.ETFCFG = filter;
}

/*!
 * @brief     Configure the TMRx prescaler.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     prescaler: specify the prescaler Register value
 *
 * @param     pscReloadMode: specify the TMR prescaler Reload mode
 *              The parameter can be one of following values:
 *              @arg TMR_PSC_RELOAD_UPDATE:    The Prescaler is loaded at the update event
 *              @arg TMR_PSC_RELOAD_IMMEDIATE: The Prescaler is loaded immediately
 *
 * @retval    None
 */
void TMR_ConfigPrescaler(TMR_T* tmr, uint16_t prescaler, TMR_PSC_RELOAD_T pscReloadMode)
{
    tmr->PSC = prescaler;
    tmr->CEG_B.UEG = pscReloadMode;
}

/*!
 * @brief     Configure counter mode
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     countMode:specify the Counter Mode to be used
 *                     The parameter can be one of following values:
 *                     @arg TMR_COUNTER_MODE_UP:   Timer Up Counting Mode
 *                     @arg TMR_COUNTER_MODE_DOWN: Timer Down Counting Mode
 *                     @arg TMR_COUNTER_MODE_CENTERALIGNED1: Timer Center Aligned Mode1
 *                     @arg TMR_COUNTER_MODE_CENTERALIGNED2: Timer Center Aligned Mode2
 *                     @arg TMR_COUNTER_MODE_CENTERALIGNED3: Timer Center Aligned Mode3
 *
 * @retval   None
 */
void TMR_ConfigCounterMode(TMR_T* tmr, TMR_COUNTER_MODE_T countMode)
{
    tmr->CTRL1_B.CNTDIR = BIT_RESET;
    tmr->CTRL1_B.CAMSEL = BIT_RESET;
    tmr->CTRL1 |= countMode;
}

/*!
 * @brief     Select the Input Trigger source
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     triggerSource: specify the Input Trigger source
 *                     The parameter can be one of following values:
 *                     @arg TMR_TRIGGER_SOURCE_ITR0: Internal Trigger 0
 *                     @arg TMR_TRIGGER_SOURCE_ITR1: Internal Trigger 1
 *                     @arg TMR_TRIGGER_SOURCE_ITR2: Internal Trigger 2
 *                     @arg TMR_TRIGGER_SOURCE_ITR3: Internal Trigger 3
 *                     @arg TMR_TRIGGER_SOURCE_TI1F_ED: TI1 Edge Detector
 *                     @arg TMR_TRIGGER_SOURCE_TI1FP1: Filtered Timer Input 1
 *                     @arg TMR_TRIGGER_SOURCE_TI2FP2: Filtered Timer Input 2
 *                     @arg TMR_TRIGGER_SOURCE_ETRF: External Trigger input
 *
 * @retval    None
 */
void TMR_SelectInputTrigger(TMR_T* tmr, TMR_TRIGGER_SOURCE_T triggerSource)
{
    tmr->SMCTRL_B.TRGSEL = BIT_RESET;
    tmr->SMCTRL_B.TRGSEL = triggerSource;
}

/*!
 * @brief     Configure the Encoder Interface.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     encodeMode: specify the Encoder Mode
 *              The parameter can be one of following values:
 *              @arg TMR_ENCODER_MODE_TI1:  Counter counts on TI1FP1 edge depending on TI2FP2 level
 *              @arg TMR_ENCODER_MODE_TI2:  Counter counts on TI2FP2 edge depending on TI1FP1 level
 *              @arg TMR_ENCODER_MODE_TI12: Counter counts on both TI1FP1 and TI2FP2 edges depending
 *                                          on the level of the other input
 *
 * @param     IC1Polarity: specify the TMR IC1 polarity
 *              The parameter can be one of following values:
 *              @arg TMR_IC_POLARITY_RISING:  TMR IC polarity rising
 *              @arg TMR_IC_POLARITY_FALLING: TMR IC polarity falling
 *
 * @param     IC2Polarity: specify the TMR IC2 polarity
 *              The parameter can be one of following values:
 *              @arg TMR_IC_POLARITY_RISING:  TMR IC polarity rising
 *              @arg TMR_IC_POLARITY_FALLING: TMR IC polarity falling
 *
 * @retval    None
 */
void TMR_ConfigEncodeInterface(TMR_T* tmr, TMR_ENCODER_MODE_T encodeMode, TMR_IC_POLARITY_T IC1Polarity,
                               TMR_IC_POLARITY_T IC2Polarity)
{
    tmr->SMCTRL_B.SMFSEL = BIT_RESET;
    tmr->SMCTRL_B.SMFSEL = encodeMode;

    tmr->CCM1_CAPTURE_B.CC1SEL = BIT_RESET ;
    tmr->CCM1_CAPTURE_B.CC2SEL = BIT_RESET ;
    tmr->CCM1_CAPTURE_B.CC1SEL = 0x01 ;
    tmr->CCM1_CAPTURE_B.CC2SEL = 0x01 ;

    tmr->CCEN_B.CC1POL = BIT_RESET;
    tmr->CCEN_B.CC2POL = BIT_RESET;
    tmr->CCEN |= ((IC1Polarity | (IC2Polarity << 4)));
}

/*!
 * @brief     Force the output 1 waveform to active or inactive level.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     forcesAction: specify the forced Action to be set to the output waveform
 *              The parameter can be one of following values:
 *              @arg TMR_FORCED_ACTION_ACTIVE:   Force active level on OC1REF
 *              @arg TMR_FORCED_ACTION_INACTIVE: Force inactive level on OC1REF
 *
 * @retval    None
 */
void TMR_ConfigForcedOC1(TMR_T* tmr, TMR_FORCED_ACTION_T forcesAction)
{
    tmr->CCM1_COMPARE_B.OC1MOD = BIT_RESET;
    tmr->CCM1_COMPARE_B.OC1MOD = forcesAction;
}

/*!
 * @brief     Force the output 2 waveform to active or inactive level.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     forcesAction: specify the forced Action to be set to the output waveform
 *              The parameter can be one of following values:
 *              @arg TMR_FORCED_ACTION_ACTIVE:   Force active level on OC1REF
 *              @arg TMR_FORCED_ACTION_INACTIVE: Force inactive level on OC1REF
 *
 * @retval    None
 */
void TMR_ConfigForcedOC2(TMR_T* tmr, TMR_FORCED_ACTION_T forcesAction)
{
    tmr->CCM1_COMPARE_B.OC2MOD = BIT_RESET;
    tmr->CCM1_COMPARE_B.OC2MOD = forcesAction;
}

/*!
 * @brief     Force the output 3 waveform to active or inactive level.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     forcesAction: specify the forced Action to be set to the output waveform
 *              The parameter can be one of following values:
 *              @arg TMR_FORCED_ACTION_ACTIVE:   Force active level on OC1REF
 *              @arg TMR_FORCED_ACTION_INACTIVE: Force inactive level on OC1REF
 *
 * @retval    None
 */
void TMR_ConfigForcedOC3(TMR_T* tmr, TMR_FORCED_ACTION_T forcesAction)
{
    tmr->CCM2_COMPARE_B.OC3MOD = BIT_RESET;
    tmr->CCM2_COMPARE_B.OC3MOD = forcesAction;
}

/*!
 * @brief     Force the output 4 waveform to active or inactive level.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     forcesAction: specify the forced Action to be set to the output waveform
 *              The parameter can be one of following values:
 *              @arg TMR_FORCED_ACTION_ACTIVE:   Force active level on OC1REF
 *              @arg TMR_FORCED_ACTION_INACTIVE: Force inactive level on OC1REF
 *
 * @retval    None
 */
void TMR_ConfigForcedOC4(TMR_T* tmr, TMR_FORCED_ACTION_T forcesAction)
{
    tmr->CCM2_COMPARE_B.OC4MOD = BIT_RESET;
    tmr->CCM2_COMPARE_B.OC4MOD = forcesAction;
}

/*!
 * @brief     Enable peripheral Preload register on AUTORLD.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    None
 */
void TMR_EnableAutoReload(TMR_T* tmr)
{
    tmr->CTRL1_B.ARPEN = ENABLE;
}

/*!
 * @brief     Disable peripheral Preload register on AUTORLD.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    None
 */
void TMR_DisableAutoReload(TMR_T* tmr)
{
    tmr->CTRL1_B.ARPEN = DISABLE;
}

/*!
 * @brief     Enable the specified TMR peripheral Commutation event.
 *
 * @param     tmr: The TMRx it can be TMR1
 *
 * @retval    None
 */
void TMR_EnableSelectCOM(TMR_T* tmr)
{
    tmr->CTRL2_B.CCUSEL = ENABLE;
}
/*!
 * @brief     Disable the specified TMR peripheral Commutation event.
 *
 * @param     tmr: The TMRx it can be TMR1
 *
 * @retval    None
 */
void TMR_DisableSelectCOM(TMR_T* tmr)
{
    tmr->CTRL2_B.CCUSEL = DISABLE;
}

/*!
 * @brief     Enable the Capture Compare DMA source.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    None
 */
void TMR_EnableCCDMA(TMR_T* tmr)
{
    tmr->CTRL2_B.CCDSEL = ENABLE;
}

/*!
 * @brief     Disable the Capture Compare DMA source.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    None
 */
void TMR_DisableCCDMA(TMR_T* tmr)
{
    tmr->CTRL2_B.CCDSEL = DISABLE;
}

/*!
 * @brief     Enable the Capture Compare Preload Control bit.
 *
 * @param     tmr: The TMRx it can be TMR1
 *
 * @retval    None
 */
void TMR_EnableCCPreload(TMR_T* tmr)
{
    tmr->CTRL2_B.CCPEN = ENABLE;
}

/*!
 * @brief     Disable the Capture Compare Preload Control bit.
 *
 * @param     tmr: The TMRx it can be TMR1
 *
 * @retval    None
 */
void TMR_DisableCCPreload(TMR_T* tmr)
{
    tmr->CTRL2_B.CCPEN = DISABLE;
}

/*!
 * @brief     Enable or disable the peripheral Preload register on CCM1.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCPreload: specify the Output Compare Channel Preload
 *              The parameter can be one of following values:
 *              @arg TMR_OC_PRELOAD_DISABLE
 *              @arg TMR_OC_PRELOAD_ENABLE
 *
 * @retval    None
 */
void TMR_ConfigOC1Preload(TMR_T* tmr, TMR_OC_PRELOAD_T OCPreload)
{
    tmr->CCM1_COMPARE_B.OC1PEN = OCPreload;
}

/*!
 * @brief     Enable or disable the peripheral Preload register on CCM2.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCPreload: specify the Output Compare Channel Preload
 *              The parameter can be one of following values:
 *              @arg TMR_OC_PRELOAD_DISABLE
 *              @arg TMR_OC_PRELOAD_ENABLE
 *
 * @retval    None
 */
void TMR_ConfigOC2Preload(TMR_T* tmr, TMR_OC_PRELOAD_T OCPreload)
{
    tmr->CCM1_COMPARE_B.OC2PEN = OCPreload;
}

/*!
 * @brief     Enable or disable the peripheral Preload register on CCM3.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCPreload: specify the Output Compare Channel Preload
 *              The parameter can be one of following values:
 *              @arg TMR_OC_PRELOAD_DISABLE
 *              @arg TMR_OC_PRELOAD_ENABLE
 *
 * @retval    None
 */
void TMR_ConfigOC3Preload(TMR_T* tmr, TMR_OC_PRELOAD_T OCPreload)
{
    tmr->CCM2_COMPARE_B.OC3PEN = OCPreload;
}

/*!
 * @brief     Enable or disable the peripheral Preload register on CCM4.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCPreload: specify the Output Compare Channel Preload
 *              The parameter can be one of following values:
 *              @arg TMR_OC_PRELOAD_DISABLE
 *              @arg TMR_OC_PRELOAD_ENABLE
 *
 * @retval    Nonee
 */
void TMR_ConfigOC4Preload(TMR_T* tmr, TMR_OC_PRELOAD_T OCPreload)
{
    tmr->CCM2_COMPARE_B.OC4PEN = OCPreload;
}

/*!
 * @brief     Configure the Output Compare 1 Fast feature.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCFast: specify the Output Compare Channel Fast
 *              The parameter can be one of following values:
 *              @arg TMR_OC_FAST_DISABLE
 *              @arg TMR_OC_FAST_ENABLE
 *
 * @retval    None
 */
void TMR_ConfigOC1Fast(TMR_T* tmr, TMR_OC_FAST_T OCFast)
{
    tmr->CCM1_COMPARE_B.OC1FEN = OCFast;
}

/*!
 * @brief     Configure the Output Compare 2 Fast feature.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCFast: specify the Output Compare Channel Fast
 *              The parameter can be one of following values:
 *              @arg TMR_OC_FAST_DISABLE
 *              @arg TMR_OC_FAST_ENABLE
 *
 * @retval    None
 */
void TMR_ConfigOC2Fast(TMR_T* tmr, TMR_OC_FAST_T OCFast)
{
    tmr->CCM1_COMPARE_B.OC2FEN = OCFast;
}

/*!
 * @brief     Configure the Output Compare 2 Fast feature.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCFast: specify the Output Compare Channel Fast
 *              The parameter can be one of following values:
 *              @arg TMR_OC_FAST_DISABLE
 *              @arg TMR_OC_FAST_ENABLE
 *
 * @retval    None
 */
void TMR_ConfigOC3Fast(TMR_T* tmr, TMR_OC_FAST_T OCFast)
{
    tmr->CCM2_COMPARE_B.OC3FEN = OCFast;
}

/*!
 * @brief     Configure the Output Compare 4 Fast feature.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCFast: specify the Output Compare Channel Fast
 *              The parameter can be one of following values:
 *              @arg TMR_OC_FAST_DISABLE
 *              @arg TMR_OC_FAST_ENABLE
 *
 * @retval    None
 */
void TMR_ConfigOC4Fast(TMR_T* tmr, TMR_OC_FAST_T OCFast)
{
    tmr->CCM2_COMPARE_B.OC4FEN = OCFast;
}

/*!
 * @brief     Clear or safeguard the OCREF1 signal on an external event
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCClear: specify the Output Compare Channel1 Clear
 *              The parameter can be one of following values:
 *              @arg TMR_OC_CLEAR_DISABLE
 *              @arg TMR_OC_CLEAR_ENABLE
 *
 * @retval    None
 */
void TMR_ClearOC1Ref(TMR_T* tmr, TMR_OC_CLEAR_T OCClear)
{
    tmr->CCM1_COMPARE_B.OC1CEN = OCClear;
}

/*!
 * @brief     Clear or safeguard the OCREF2 signal on an external event
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCClear: specify the Output Compare Channel1 Clear
 *              The parameter can be one of following values:
 *              @arg TMR_OC_CLEAR_DISABLE
 *              @arg TMR_OC_CLEAR_ENABLE
 *
 * @retval    None
 */
void TMR_ClearOC2Ref(TMR_T* tmr, TMR_OC_CLEAR_T OCClear)
{
    tmr->CCM1_COMPARE_B.OC2CEN = OCClear;
}

/*!
 * @brief     Clear or safeguard the OCREF3 signal on an external event
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCClear: specify the Output Compare Channel1 Clear
 *              The parameter can be one of following values:
 *              @arg TMR_OC_CLEAR_DISABLE
 *              @arg TMR_OC_CLEAR_ENABLE
 *
 * @retval    None
 */
void TMR_ClearOC3Ref(TMR_T* tmr, TMR_OC_CLEAR_T OCClear)
{
    tmr->CCM2_COMPARE_B.OC3CEN = OCClear;
}

/*!
 * @brief     Clear or safeguard the OCREF4 signal on an external event
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     OCClear: specify the Output Compare Channel1 Clear
 *              The parameter can be one of following values:
 *              @arg TMR_OC_CLEAR_DISABLE
 *              @arg TMR_OC_CLEAR_ENABLE
 *
 * @retval    None
 */
void TMR_ClearOC4Ref(TMR_T* tmr, TMR_OC_CLEAR_T OCClear)
{
    tmr->CCM2_COMPARE_B.OC4CEN = OCClear;
}

/*!
 * @brief     Configure the channel 1 polarity.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     polarity: specify the OC1 Polarity
 *              The parameter can be one of following values:
 *              @arg TMR_OC_POLARITY_HIGH: Output Compare active high
 *              @arg TMR_OC_POLARITY_LOW:  Output Compare active low
 *
 * @retval    Nonee
 */
void TMR_ConfigOC1Polarity(TMR_T* tmr, TMR_OC_POLARITY_T polarity)
{
    tmr->CCEN_B.CC1POL = polarity;
}

/*!
 * @brief     Configure the  channel 1 nPolarity.
 *
 * @param     tmr: The TMRx it can be TMR1
 *
 * @param     nPolarity: specify the OC1 nPolarity
 *              The parameter can be one of following values:
 *              @arg TMR_OC_NPOLARITY_HIGH: Output Compare active high
 *              @arg TMR_OC_NPOLARITY_LOW:  Output Compare active low
 *
 * @retval    None
 */
void TMR_ConfigOC1NPolarity(TMR_T* tmr, TMR_OC_NPOLARITY_T nPolarity)
{
    tmr->CCEN_B.CC1NPOL = nPolarity;
}

/*!
 * @brief     Configure the channel 2 polarity.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     polarity: specify the OC2 Polarity
 *              The parameter can be one of following values:
 *              @arg TMR_OC_POLARITY_HIGH: Output Compare active high
 *              @arg TMR_OC_POLARITY_LOW:  Output Compare active low
 *
 * @retval    None
 */
void TMR_ConfigOC2Polarity(TMR_T* tmr, TMR_OC_POLARITY_T polarity)
{
    tmr->CCEN_B.CC2POL = polarity;
}

/*!
 * @brief     Configure the  channel 2 nPolarity.
 *
 * @param     tmr: The TMRx it can be TMR1
 *
 * @param     nPolarity: specify the OC2 nPolarity
 *              The parameter can be one of following values:
 *              @arg TMR_OC_NPOLARITY_HIGH: Output Compare active high
 *              @arg TMR_OC_NPOLARITY_LOW:  Output Compare active low
 *
 * @retval    None
 */
void TMR_ConfigOC2NPolarity(TMR_T* tmr, TMR_OC_NPOLARITY_T nPolarity)
{
    tmr->CCEN_B.CC2NPOL = nPolarity;
}

/*!
 * @brief     Configure the channel 3 polarity.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     polarity: specify the OC3 Polarity
 *              The parameter can be one of following values:
 *              @arg TMR_OC_POLARITY_HIGH: Output Compare active high
 *              @arg TMR_OC_POLARITY_LOW:  Output Compare active low
 *
 * @retval    None
 */
void TMR_ConfigOC3Polarity(TMR_T* tmr, TMR_OC_POLARITY_T polarity)
{
    tmr->CCEN_B.CC3POL = polarity;
}

/*!
 * @brief     Configure the  channel 3 nPolarity.
 *
 * @param     tmr: The TMRx it can be TMR1
 *
 * @param     nPolarity: specify the OC3 nPolarity
 *              The parameter can be one of following values:
 *              @arg TMR_OC_NPOLARITY_HIGH: Output Compare active high
 *              @arg TMR_OC_NPOLARITY_LOW:  Output Compare active low
 *
 * @retval    None
 */
void TMR_ConfigOC3NPolarity(TMR_T* tmr, TMR_OC_NPOLARITY_T nPolarity)
{
    tmr->CCEN_B.CC3NPOL = nPolarity;
}

/*!
 * @brief     Configure the channel 4 polarity.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     polarity: specify the OC4 Polarity
 *              The parameter can be one of following values:
 *              @arg TMR_OC_POLARITY_HIGH: Output Compare active high
 *              @arg TMR_OC_POLARITY_LOW:  Output Compare active low
 *
 * @retval    None
 */
void TMR_ConfigOC4Polarity(TMR_T* tmr, TMR_OC_POLARITY_T polarity)
{
    tmr->CCEN_B.CC4POL = polarity;
}

/*!
 * @brief     Enable the Capture Compare Channel x.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     channel: specify the Channel
 *              The parameter can be one of following values:
 *              @arg TMR_CHANNEL_1: Timer Channel 1
 *              @arg TMR_CHANNEL_2: Timer Channel 2
 *              @arg TMR_CHANNEL_3: Timer Channel 3
 *              @arg TMR_CHANNEL_4: Timer Channel 4
 *
 * @retval    None
 */
void TMR_EnableCCxChannel(TMR_T* tmr, TMR_CHANNEL_T channel)
{
    tmr->CCEN |= BIT_SET << channel;
}

/*!
 * @brief     Disable the Capture Compare Channel x.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     channel: specify the Channel
 *              The parameter can be one of following values:
 *              @arg TMR_CHANNEL_1: Timer Channel 1
 *              @arg TMR_CHANNEL_2: Timer Channel 2
 *              @arg TMR_CHANNEL_3: Timer Channel 3
 *              @arg TMR_CHANNEL_4: Timer Channel 4
 * @retval    None
 */
void TMR_DisableCCxChannel(TMR_T* tmr, TMR_CHANNEL_T channel)
{
    tmr->CCEN &= ~(BIT_SET << channel);
}

/*!
 * @brief     Enable the Capture Compare Channelx N.
 *
 * @param     tmr: The TMRx it can be TMR1
 *
 * @param     channel: specify the Channel
 *              The parameter can be one of following values:
 *              @arg TMR_CHANNEL_1: Timer Channel 1
 *              @arg TMR_CHANNEL_2: Timer Channel 2
 *              @arg TMR_CHANNEL_3: Timer Channel 3
 *
 * @retval    None
 */
void TMR_EnableCCxNChannel(TMR_T* tmr, TMR_CHANNEL_T channel)
{
    tmr->CCEN |= 0x04 << channel;
}

/*!
 * @brief     Disable the Capture Compare Channelx N.
 *
 * @param     tmr: The TMRx it can be TMR1
 *
 * @param     channel: specify the Channel
 *              The parameter can be one of following values:
 *              @arg TMR_CHANNEL_1: Timer Channel 1
 *              @arg TMR_CHANNEL_2: Timer Channel 2
 *              @arg TMR_CHANNEL_3: Timer Channel 3
 *
 * @retval    None
 */
void TMR_DisableCCxNChannel(TMR_T* tmr, TMR_CHANNEL_T channel)
{
    tmr->CCEN &= ~(0x04 << channel);
}

/*!
 * @brief     Select the Output Compare Mode.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     channel: specify the Channel
 *              The parameter can be one of following values:
 *              @arg TMR_CHANNEL_1: Timer Channel 1
 *              @arg TMR_CHANNEL_2: Timer Channel 2
 *              @arg TMR_CHANNEL_3: Timer Channel 3
 *              @arg TMR_CHANNEL_4: Timer Channel 4
 *
 * @param     mode: specify the Output Compare Mode
 *              The parameter can be one of following values:
 *              @arg TMR_OC_MODE_TMRING
 *              @arg TMR_OC_MODE_ACTIVE
 *              @arg TMR_OC_MODE_INACTIVE
 *              @arg TMR_OC_MODE_TOGGEL
 *              @arg TMR_OC_MODE_LOWLEVEL
 *              @arg TMR_OC_MODE_HIGHLEVEL
 *              @arg TMR_OC_MODE_PWM1
 *              @arg TMR_OC_MODE_PWM2
 *
 * @retval    None
 */
void TMR_SelectOCxMode(TMR_T* tmr, TMR_CHANNEL_T channel, TMR_OC_MODE_T mode)
{
    tmr->CCEN &= BIT_RESET << channel;

    if (channel == TMR_CHANNEL_1)
    {
        tmr->CCM1_COMPARE_B.OC1MOD = mode;
    }
    else if (channel == TMR_CHANNEL_2)
    {
        tmr->CCM1_COMPARE_B.OC2MOD = mode;
    }
    else if (channel == TMR_CHANNEL_3)
    {
        tmr->CCM2_COMPARE_B.OC3MOD = mode;
    }
    else if (channel == TMR_CHANNEL_4)
    {
        tmr->CCM2_COMPARE_B.OC4MOD = mode;
    }
}

/*!
 * @brief     Enable the TMRx update event
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    None
 */
void TMR_EnableUpdate(TMR_T* tmr)
{
    tmr->CTRL1_B.UD = DISABLE;
}

/*!
 * @brief     Disable the TMRx update event
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    None
 */
void TMR_DisableUpdate(TMR_T* tmr)
{
    tmr->CTRL1_B.UD = ENABLE;
}

/*!
 * @brief     Configure the Update Request Interrupt source
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     updateSource: Config the Update source
 *              The parameter can be one of following values:
 *              @arg TMR_UPDATE_SOURCE_GLOBAL
 *              @arg TMR_UPDATE_SOURCE_REGULAR
 *
 * @retval    None
 */
void TMR_ConfigUpdateRequest(TMR_T* tmr, TMR_UPDATE_SOURCE_T updateSource)
{
    if (updateSource != TMR_UPDATE_SOURCE_GLOBAL)
    {
        tmr->CTRL1_B.URSSEL = BIT_SET;
    }
    else
    {
        tmr->CTRL1_B.URSSEL = BIT_RESET;
    }
}

/*!
 * @brief     Enable Hall sensor interface.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    None
 */
void TMR_EnableHallSensor(TMR_T* tmr)
{
    tmr->CTRL2_B.TI1SEL = ENABLE;
}

/*!
 * @brief     Disable Hall sensor interface.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    None
 */
void TMR_DisableHallSensor(TMR_T* tmr)
{
    tmr->CTRL2_B.TI1SEL = DISABLE;
}

/*!
 * @brief     Configure the Sing pulse Mode.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     singlePulseMode: specify the Single Pulse Mode
 *              The parameter can be one of following values:
 *              @arg TMR_SPM_REPETITIVE
 *              @arg TMR_SPM_SINGLE
 *
 * @retval    None
 */
void TMR_ConfigSinglePulseMode(TMR_T* tmr, TMR_SPM_T singlePulseMode)
{
    tmr->CTRL1_B.SPMEN = singlePulseMode;
}

/*!
 * @brief     Select the Trigger Output Mode.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     TRGOSource: specify the Trigger Output source
 *              The parameter can be one of following values:
 *              @arg TMR_TRGO_SOURCE_RESET
 *              @arg TMR_TRGO_SOURCE_ENABLE
 *              @arg TMR_TRGO_SOURCE_UPDATE
 *              @arg TMR_TRGO_SOURCE_OC1
 *              @arg TMR_TRGO_SOURCE_OC1REF
 *              @arg TMR_TRGO_SOURCE_OC2REF
 *              @arg TMR_TRGO_SOURCE_OC3REF
 *              @arg TMR_TRGO_SOURCE_OC4REF
 *
 * @retval    None
 */
void TMR_SelectOutputTrigger(TMR_T* tmr, TMR_TRGO_SOURCE_T TRGOSource)
{
    tmr->CTRL2_B.MMSEL = TRGOSource;
}

/*!
 * @brief     Select the Slave Mode.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     slaveMode: specify the Timer Slave Mode.
 *              The parameter can be one of following values:
 *              @arg TMR_SLAVE_MODE_RESET
 *              @arg TMR_SLAVE_MODE_GATED
 *              @arg TMR_SLAVE_MODE_TRIGGER
 *              @arg TMR_SLAVE_MODE_EXTERNAL1
 *
 * @retval    None
 */
void TMR_SelectSlaveMode(TMR_T* tmr, TMR_SLAVE_MODE_T slaveMode)
{
    tmr->SMCTRL_B.SMFSEL = slaveMode;
}

/*!
 * @brief     Enable the Master Slave Mode
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    None
 */
void TMR_EnableMasterSlaveMode(TMR_T* tmr)
{
    tmr->SMCTRL_B.MSMEN = ENABLE;
}

/*!
 * @brief     Disable the Master Slave Mode
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    None
 */
void TMR_DisableMasterSlaveMode(TMR_T* tmr)
{
    tmr->SMCTRL_B.MSMEN = DISABLE;
}

/*!
 * @brief     Configure the Counter Register value
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     counter: Counter register new value
 *
 * @retval    None
 */
void TMR_ConfigCounter(TMR_T* tmr, uint16_t counter)
{
    tmr->CNT = counter;
}

/*!
 * @brief     Configure the AutoReload Register value
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     autoReload: autoReload register new value
 *
 * @retval    None
 */
void TMR_ConfigAutoreload(TMR_T* tmr, uint16_t autoReload)
{
    tmr->AUTORLD = autoReload;
}

/*!
 * @brief     Configure the Capture Compare1 Register value
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     compare1: specify the Capture Compare1 value.
 *
 * @retval    None
 */
void TMR_ConfigCompare1(TMR_T* tmr, uint16_t compare1)
{
    tmr->CC1 = compare1;
}

/*!
 * @brief     Configure the Capture Compare2 Register value
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     compare2: specify the Capture Compare1 value.
 *
 * @retval    None
 */
void TMR_ConfigCompare2(TMR_T* tmr, uint16_t compare2)
{
    tmr->CC2 = compare2;
}

/*!
 * @brief     Configure the Capture Compare3 Register value
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     compare3: specify the Capture Compare1 value.
 *
 * @retval    None
 */
void TMR_ConfigCompare3(TMR_T* tmr, uint16_t compare3)
{
    tmr->CC3 = compare3;
}

/*!
 * @brief     Configure the Capture Compare4 Register value
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     compare4: specify the Capture Compare1 value.
 *
 * @retval    None
 */
void TMR_ConfigCompare4(TMR_T* tmr, uint16_t compare4)
{
    tmr->CC4 = compare4;
}

/*!
 * @brief     Configure the TMRx Input Capture 1 prescaler.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     prescaler: specify the Input Capture Channel1 Perscaler
 *              The parameter can be one of following values:
 *              @arg TMR_IC_PSC_1: no prescaler
 *              @arg TMR_IC_PSC_2: capture is done once every 2 events
 *              @arg TMR_IC_PSC_4: capture is done once every 4 events
 *              @arg TMR_IC_PSC_8: capture is done once every 8 events
 *
 * @retval    None
 */
void TMR_ConfigIC1Prescal(TMR_T* tmr, TMR_IC_PSC_T prescaler)
{
    tmr->CCM1_CAPTURE_B.IC1PSC = BIT_RESET;
    tmr->CCM1_CAPTURE_B.IC1PSC = prescaler;
}
/*!
 * @brief     Sets the TMRx Input Capture 2 prescaler.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     prescaler: specify the Input Capture Channel2 Perscaler
 *              The parameter can be one of following values:
 *              @arg TMR_IC_PSC_1: no prescaler
 *              @arg TMR_IC_PSC_2: capture is done once every 2 events
 *              @arg TMR_IC_PSC_4: capture is done once every 4 events
 *              @arg TMR_IC_PSC_8: capture is done once every 8 events
 *
 * @retval    None
 */
void TMR_ConfigIC2Prescal(TMR_T* tmr, TMR_IC_PSC_T prescaler)
{
    tmr->CCM1_CAPTURE_B.IC2PSC = BIT_RESET;
    tmr->CCM1_CAPTURE_B.IC2PSC = prescaler;
}

/*!
 * @brief     Configure the TMRx Input Capture 3 prescaler.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     prescaler: specify the Input Capture Channel3 Perscaler
 *              The parameter can be one of following values:
 *              @arg TMR_IC_PSC_1: no prescaler
 *              @arg TMR_IC_PSC_2: capture is done once every 2 events
 *              @arg TMR_IC_PSC_4: capture is done once every 4 events
 *              @arg TMR_IC_PSC_8: capture is done once every 8 events
 *
 * @retval    None
 */
void TMR_ConfigIC3Prescal(TMR_T* tmr, TMR_IC_PSC_T prescaler)
{
    tmr->CCM2_CAPTURE_B.IC3PSC = BIT_RESET;
    tmr->CCM2_CAPTURE_B.IC3PSC = prescaler;
}

/*!
 * @brief     Configure the TMRx Input Capture 4 prescaler.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     prescaler: specify the Input Capture Channel4 Perscaler
 *              The parameter can be one of following values:
 *              @arg TMR_IC_PSC_1: no prescaler
 *              @arg TMR_IC_PSC_2: capture is done once every 2 events
 *              @arg TMR_IC_PSC_4: capture is done once every 4 events
 *              @arg TMR_IC_PSC_8: capture is done once every 8 events
 *
 * @retval    None
 */
void TMR_ConfigIC4Prescal(TMR_T* tmr, TMR_IC_PSC_T prescaler)
{
    tmr->CCM2_CAPTURE_B.IC4PSC = BIT_RESET;
    tmr->CCM2_CAPTURE_B.IC4PSC = prescaler;
}

/*!
 * @brief     Configure the Clock Division value
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     clockDivision: specify the clock division value.
 *              The parameter can be one of following values:
 *              @arg TMR_CLOCK_DIV_1: TDTS = Tck_tim
 *              @arg TMR_CLOCK_DIV_2: TDTS = 2*Tck_tim
 *              @arg TMR_CLOCK_DIV_4: TDTS = 4*Tck_tim
 *
 * @retval    None
 */
void TMR_ConfigClockDivision(TMR_T* tmr, TMR_CLOCK_DIV_T clockDivision)
{
    tmr->CTRL1_B.CLKDIV = clockDivision;
}

/*!
 * @brief     Read Input Capture 1 value.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    Capture Compare 1 Register value.
 */
uint16_t TMR_ReadCaputer1(TMR_T* tmr)
{
    return tmr->CC1;
}

/*!
 * @brief     Read Input Capture 2 value.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    Capture Compare 2 Register value.
 */
uint16_t TMR_ReadCaputer2(TMR_T* tmr)
{
    return tmr->CC2;
}

/*!
 * @brief     Read Input Capture 3 value.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    Capture Compare 3 Register value.
 */
uint16_t TMR_ReadCaputer3(TMR_T* tmr)
{
    return tmr->CC3;
}

/*!
 * @brief     Read Input Capture 4 value.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    Capture Compare 4 Register value.
 */
uint16_t TMR_ReadCaputer4(TMR_T* tmr)
{
    return tmr->CC4;
}

/*!
 * @brief     Read the TMRx Counter value.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    Counter Register value.
 */
uint16_t TMR_ReadCounter(TMR_T* tmr)
{
    return tmr->CNT;
}

/*!
 * @brief     Read the TMRx  Prescaler value.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @retval    Prescaler Register value.
 */
uint16_t TMR_ReadPrescaler(TMR_T* tmr)
{
    return tmr->PSC;
}

/*!
 * @brief     Enable intterupts
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     interrupt: specify the TMR interrupts sources
 *              The parameter can be any combination of following values:
 *              @arg TMR_INT_UPDATE: Timer update Interrupt source
 *              @arg TMR_INT_CC1: Timer Capture Compare 1 Interrupt source
 *              @arg TMR_INT_CC2: Timer Capture Compare 1 Interrupt source
 *              @arg TMR_INT_CC3: Timer Capture Compare 3 Interrupt source
 *              @arg TMR_INT_CC4: Timer Capture Compare 4 Interrupt source
 *              @arg TMR_INT_COM: Timer Commutation Interrupt source (Only for TMR1)
 *              @arg TMR_INT_TRG: Timer Trigger Interrupt source
 *              @arg TMR_INT_BRK: Timer Break Interrupt source (Only for TMR1)
 *
 * @retval    None
 */
void TMR_EnableInterrupt(TMR_T* tmr, uint16_t interrupt)
{
    tmr->DIEN |= interrupt;
}

/*!
 * @brief     Disable intterupts
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     interrupt: specify the TMR interrupts sources
 *              The parameter can be any combination of following values:
 *              @arg TMR_INT_UPDATE: Timer update Interrupt source
 *              @arg TMR_INT_CC1: Timer Capture Compare 1 Interrupt source
 *              @arg TMR_INT_CC2: Timer Capture Compare 1 Interrupt source
 *              @arg TMR_INT_CC3: Timer Capture Compare 3 Interrupt source
 *              @arg TMR_INT_CC4: Timer Capture Compare 4 Interrupt source
 *              @arg TMR_INT_COM: Timer Commutation Interrupt source (Only for TMR1)
 *              @arg TMR_INT_TRG: Timer Trigger Interrupt source
 *              @arg TMR_INT_BRK: Timer Break Interrupt source (Only for TMR1)
 *
 * @retval    None
 */
void TMR_DisableInterrupt(TMR_T* tmr, uint16_t interrupt)
{
    tmr->DIEN &= ~interrupt;
}

/*!
 * @brief     Configure the TMRx event to be generate by software.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     eventSources: specify the TMR event sources
 *              The parameter can be any combination of following values:
 *              @arg TMR_EVENT_UPDATE: Timer update Interrupt source
 *              @arg TMR_EVENT_CC1: Timer Capture Compare 1 Event source
 *              @arg TMR_EVENT_CC2: Timer Capture Compare 1 Event source
 *              @arg TMR_EVENT_CC3: Timer Capture Compare 3 Event source
 *              @arg TMR_EVENT_CC4: Timer Capture Compare 4 Event source
 *              @arg TMR_EVENT_COM: Timer Commutation Event source (Only for TMR1)
 *              @arg TMR_EVENT_TRG: Timer Trigger Event source
 *              @arg TMR_EVENT_BRK: Timer Break Event source (Only for TMR1)
 *
 * @retval    None
 */
void TMR_GenerateEvent(TMR_T* tmr, uint16_t eventSources)
{
    tmr->CEG = eventSources;
}

/*!
 * @brief     Check whether the flag is set or reset
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     interrupt: specify the TMR interrupts sources
 *                     The parameter can be any combination of following values:
 *                     @arg TMR_FLAG_UPDATE: Timer update Flag
 *                     @arg TMR_FLAG_CC1: Timer Capture Compare 1 Flag
 *                     @arg TMR_FLAG_CC2: Timer Capture Compare 2 Flag
 *                     @arg TMR_FLAG_CC3: Timer Capture Compare 3 Flag
 *                     @arg TMR_FLAG_CC4: Timer Capture Compare 4 Flag
 *                     @arg TMR_FLAG_COM: Timer Commutation Flag (Only for TMR1)
 *                     @arg TMR_FLAG_TRG: Timer Trigger Flag
 *                     @arg TMR_FLAG_BRK: Timer Break Flag (Only for TMR1)
 *                     @arg TMR_FLAG_CC1RC: Timer Capture Compare 1 Repetition Flag
 *                     @arg TMR_FLAG_CC2RC: Timer Capture Compare 2 Repetition Flag
 *                     @arg TMR_FLAG_CC3RC: Timer Capture Compare 3 Repetition Flag
 *                     @arg TMR_FLAG_CC4RC: Timer Capture Compare 4 Repetition Flag
 *
 * @retval    None
 */
uint16_t TMR_ReadStatusFlag(TMR_T* tmr, TMR_FLAG_T flag)
{
    return (tmr->STS & flag) ? SET : RESET;
}

/*!
 * @brief     Clears the TMR's pending flags.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     interrupt: specify the TMR interrupts sources
 *                     The parameter can be any combination of following values:
 *                     @arg TMR_FLAG_UPDATE: Timer update Flag
 *                     @arg TMR_FLAG_CC1: Timer Capture Compare 1 Flag
 *                     @arg TMR_FLAG_CC2: Timer Capture Compare 2 Flag
 *                     @arg TMR_FLAG_CC3: Timer Capture Compare 3 Flag
 *                     @arg TMR_FLAG_CC4: Timer Capture Compare 4 Flag
 *                     @arg TMR_FLAG_COM: Timer Commutation Flag (Only for TMR1)
 *                     @arg TMR_FLAG_TRG: Timer Trigger Flag
 *                     @arg TMR_FLAG_BRK: Timer Break Flag (Only for TMR1)
 *                     @arg TMR_FLAG_CC1RC: Timer Capture Compare 1 Repetition Flag
 *                     @arg TMR_FLAG_CC2RC: Timer Capture Compare 2 Repetition Flag
 *                     @arg TMR_FLAG_CC3RC: Timer Capture Compare 3 Repetition Flag
 *                     @arg TMR_FLAG_CC4RC: Timer Capture Compare 4 Repetition Flag
 *
 * @retval    None
 */
void TMR_ClearStatusFlag(TMR_T* tmr, uint16_t flag)
{
    tmr->STS = ~flag;
}

/*!
 * @brief     Check whether the ITflag is set or reset
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     interrupt: specify the TMR interrupts sources
 *                     The parameter can be one of following values:
 *                     @arg TMR_INT_UPDATE: Timer update Interrupt source
 *                     @arg TMR_INT_CC1: Timer Capture Compare 1 Interrupt source
 *                     @arg TMR_INT_CC2: Timer Capture Compare 1 Interrupt source
 *                     @arg TMR_INT_CC3: Timer Capture Compare 3 Interrupt source
 *                     @arg TMR_INT_CC4: Timer Capture Compare 4 Interrupt source
 *                     @arg TMR_INT_COM: Timer Commutation Interrupt source (Only for TMR1)
 *                     @arg TMR_INT_TRG: Timer Trigger Interrupt source
 *                     @arg TMR_INT_BRK: Timer Break Interrupt source (Only for TMR1)
 *
 * @retval    None
 */
uint16_t TMR_ReadIntFlag(TMR_T* tmr, TMR_INT_T flag)
{
    if (((tmr->STS & flag) != RESET) && ((tmr->DIEN & flag) != RESET))
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/*!
 * @brief     Clears the TMR's interrupt pending bits.
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     interrupt: specify the TMR interrupts sources
 *                     The parameter can be any combination following values:
 *                     @arg TMR_INT_UPDATE: Timer update Interrupt source
 *                     @arg TMR_INT_CC1: Timer Capture Compare 1 Interrupt source
 *                     @arg TMR_INT_CC2: Timer Capture Compare 1 Interrupt source
 *                     @arg TMR_INT_CC3: Timer Capture Compare 3 Interrupt source
 *                     @arg TMR_INT_CC4: Timer Capture Compare 4 Interrupt source
 *                     @arg TMR_INT_COM: Timer Commutation Interrupt source (Only for TMR1)
 *                     @arg TMR_INT_TRG: Timer Trigger Interrupt source
 *                     @arg TMR_INT_BRK: Timer Break Interrupt source (Only for TMR1)
 *
 * @retval    None
 */
void TMR_ClearIntFlag(TMR_T* tmr,  uint16_t flag)
{
    tmr->STS = ~flag;
}

/*!
 * @brief     Configure the TI1 as Input
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     ICpolarity: pointer to a TMR_IC_POLARITY_T
 *
 * @param     ICselection: pointer to a TMR_IC_SELECTION_T
 *
 * @param     ICfilter: This parameter must be a value between 0x00 and 0x0F
 *
 * @retval    None
 */
static void TI1Config(TMR_T* tmr, uint16_t ICpolarity, uint16_t ICselection, uint16_t ICfilter)
{
    uint16_t tmpchctrl = 0;

    tmr->CCEN_B.CC1EN = BIT_RESET;

    tmr->CCM1_CAPTURE_B.CC1SEL = BIT_RESET;
    tmr->CCM1_CAPTURE_B.IC1F   = BIT_RESET;
    tmr->CCM1_CAPTURE_B.CC1SEL = ICselection;
    tmr->CCM1_CAPTURE_B.IC1F   = ICfilter;

    if ((tmr == TMR1) || (tmr == TMR2) || (tmr == TMR3) || (tmr == TMR4))
    {
        tmr->CCEN_B.CC1POL = BIT_RESET;
        tmr->CCEN_B.CC1EN  = BIT_SET;
        tmpchctrl = tmr->CCEN;
        tmpchctrl |= ICpolarity;
        tmr->CCEN = tmpchctrl;
    }
    else
    {
        tmr->CCEN_B.CC1POL  = BIT_RESET;
        tmr->CCEN_B.CC1NPOL = BIT_RESET;
        tmr->CCEN_B.CC1EN   = BIT_SET;
        tmpchctrl = tmr->CCEN;
        tmpchctrl |= ICpolarity;
        tmr->CCEN = tmpchctrl;
    }
}

/*!
 * @brief     Configure the TI2 as Input
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     ICpolarity: pointer to a TMR_IC_POLARITY_T
 *
 * @param     ICselection: pointer to a TMR_IC_SELECTION_T
 *
 * @param     ICfilter: This parameter must be a value between 0x00 and 0x0F
 *
 * @retval    None
 */
static void TI2Config(TMR_T* tmr, uint16_t ICpolarity, uint16_t ICselection, uint16_t ICfilter)
{
    uint16_t tmpchctrl = 0;

    tmr->CCEN_B.CC2EN = BIT_RESET;

    tmr->CCM1_CAPTURE_B.CC2SEL = BIT_RESET;
    tmr->CCM1_CAPTURE_B.IC2F   = BIT_RESET;
    tmr->CCM1_CAPTURE_B.CC2SEL = ICselection;
    tmr->CCM1_CAPTURE_B.IC2F   = ICfilter;

    if ((tmr == TMR1) || (tmr == TMR2) || (tmr == TMR3) || (tmr == TMR4))
    {
        tmr->CCEN_B.CC2POL = BIT_RESET;
        tmr->CCEN_B.CC2EN  = BIT_SET;
        tmpchctrl = tmr->CCEN;
        tmpchctrl |= (ICpolarity << 4);
        tmr->CCEN = tmpchctrl;
    }
    else
    {
        tmr->CCEN_B.CC2POL  = BIT_RESET;
        tmr->CCEN_B.CC2NPOL = BIT_RESET;
        tmr->CCEN_B.CC2EN   = BIT_SET;
        tmpchctrl = tmr->CCEN;
        tmpchctrl |= (ICpolarity << 4);
        tmr->CCEN = tmpchctrl;
    }
}

/*!
 * @brief     Configure the TI3 as Input
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     ICpolarity: pointer to a TMR_IC_POLARITY_T
 *
 * @param     ICselection: pointer to a TMR_IC_SELECTION_T
 *
 * @param     ICfilter: This parameter must be a value between 0x00 and 0x0F
 *
 * @retval    None
 */
static void TI3Config(TMR_T* tmr, uint16_t ICpolarity, uint16_t ICselection, uint16_t ICfilter)
{
    uint16_t tmpchctrl = 0;

    tmr->CCEN_B.CC3EN = BIT_RESET;

    tmr->CCM2_CAPTURE_B.CC3SEL = BIT_RESET;
    tmr->CCM2_CAPTURE_B.IC3F   = BIT_RESET;
    tmr->CCM2_CAPTURE_B.CC3SEL = ICselection;
    tmr->CCM2_CAPTURE_B.IC3F   = ICfilter;

    if ((tmr == TMR1) || (tmr == TMR2) || (tmr == TMR3) || (tmr == TMR4))
    {
        tmr->CCEN_B.CC3POL = BIT_RESET;
        tmr->CCEN_B.CC3EN  = BIT_SET;
        tmpchctrl = tmr->CCEN;
        tmpchctrl |= (ICpolarity << 8);
        tmr->CCEN = tmpchctrl;
    }
    else
    {
        tmr->CCEN_B.CC3POL  = BIT_RESET;
        tmr->CCEN_B.CC3NPOL = BIT_RESET;
        tmr->CCEN_B.CC3EN   = BIT_SET;
        tmpchctrl = tmr->CCEN;
        tmpchctrl |= (ICpolarity << 8);
        tmr->CCEN = tmpchctrl;
    }
}

/*!
 * @brief     Configure the TI4 as Input
 *
 * @param     tmr: The TMRx can be 1 to 4
 *
 * @param     ICpolarity: pointer to a TMR_IC_POLARITY_T
 *
 * @param     ICselection: pointer to a TMR_IC_SELECTION_T
 *
 * @param     ICfilter: This parameter must be a value between 0x00 and 0x0F
 *
 * @retval    None
 */
static void TI4Config(TMR_T* tmr, uint16_t ICpolarity, uint16_t ICselection, uint16_t ICfilter)
{
    uint16_t tmpchctrl = 0;

    tmr->CCEN_B.CC4EN = BIT_RESET;

    tmr->CCM2_CAPTURE_B.CC4SEL = BIT_RESET;
    tmr->CCM2_CAPTURE_B.IC4F   = BIT_RESET;
    tmr->CCM2_CAPTURE_B.CC4SEL = ICselection;
    tmr->CCM2_CAPTURE_B.IC4F   = ICfilter;

    tmr->CCEN_B.CC4POL = BIT_RESET;
    tmr->CCEN_B.CC4EN  = BIT_SET;
    tmpchctrl = tmr->CCEN;
    tmpchctrl |= (ICpolarity << 12);
    tmr->CCEN = tmpchctrl;
}

/**@} end of group TMR_Functions */
/**@} end of group TMR_Driver */
/**@} end of group APM32S10x_StdPeriphDriver */
