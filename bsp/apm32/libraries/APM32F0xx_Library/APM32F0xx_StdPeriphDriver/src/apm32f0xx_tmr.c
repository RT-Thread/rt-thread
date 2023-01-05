/*!
 * @file        apm32f0xx_tmr.c
 *
 * @brief       This file contains all the functions for the TMR peripheral
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

#include "apm32f0xx_tmr.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup TMR_Driver  TMR Driver
  @{
*/

/** @defgroup TMR_Marcos Marcos
  @{
  */

/**@} end of group TMR_Marcos */

/** @defgroup TMR_Enumerations Enumerations
  @{
  */

/**@} end of group TMR_Enumerations */

/** @defgroup TMR_Structures Structures
  @{
  */

/**@} end of group TMR_Structures */

/** @defgroup  TMR_Variables Variables
  @{
  */

/**@} end of group TMR_Variables */

/** @defgroup  TMR_Functions Functions
  @{
*/

/*!
 * @brief     Reset the TMR peripheral registers to their default reset values
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @retval    None
 *
 * @note      TMR2 TMR15 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_Reset(TMR_T* TMRx)
{
    if (TMRx == TMR1)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_TMR1);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_TMR1);
    }
    else if (TMRx == TMR2)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_TMR2);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_TMR2);
    }
    else if (TMRx == TMR3)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_TMR3);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_TMR3);
    }
    else if (TMRx == TMR6)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_TMR6);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_TMR6);
    }
    else if (TMRx == TMR7)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_TMR7);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_TMR7);
    }
    else if (TMRx == TMR14)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_TMR14);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_TMR14);
    }
    else if (TMRx == TMR15)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_TMR15);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_TMR15);
    }
    else if (TMRx == TMR16)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_TMR16);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_TMR16);
    }
    else if (TMRx == TMR17)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_TMR17);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_TMR17);
    }
}

/*!
 * @brief     Initializes the TMRx Time Base Unit peripheral according to
 *            the specified parameters in the TMR_ConfigTimeBase
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @param     timeBaseConfig: pointer to a TMR_TimeBase_T structure that contains
 *            the configuration information for the specified TMR peripheral
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_ConfigTimeBase(TMR_T* TMRx, TMR_TimeBase_T* timeBaseConfig)
{
    if ((TMRx == TMR1) || (TMRx == TMR3))
    {
        /** Select the Counter Mode */
        TMRx->CTRL1_B.CNTDIR = timeBaseConfig->counterMode;
        TMRx->CTRL1_B.CAMSEL = (timeBaseConfig->counterMode) >> 1;
    }

    if (TMRx != TMR6)
    {
        /** Set the clock division */
        TMRx->CTRL1_B.CLKDIV = timeBaseConfig->clockDivision;
    }

    /** Set the Autoreload value */
    TMRx->AUTORLD = timeBaseConfig->period ;

    /** Set the Prescaler value */
    TMRx->PSC = timeBaseConfig->div ;

    if ((TMRx == TMR1) || (TMRx == TMR15) || (TMRx == TMR16) || (TMRx == TMR17))
    {
        /** Set the Repetition Counter value */
        TMRx->REPCNT = timeBaseConfig->repetitionCounter;
    }

    /** Enable Update generation */
    TMRx->CEG_B.UEG = BIT_SET;
}

/*!
 * @brief     Fills each TMR_ConfigTimeBaseStruct member with its default value
 *
 * @param     timeBaseConfig: pointer to a TMR_TimeBase_T structure that contains
 *            the configuration information for the specified TMR peripheral
 *
 * @retval    None
 */
void TMR_ConfigTimeBaseStruct(TMR_TimeBase_T* timeBaseConfig)
{
    timeBaseConfig->period = 0xFFFFFFFF;
    timeBaseConfig->div = 0x0000;
    timeBaseConfig->clockDivision = TMR_CKD_DIV1;
    timeBaseConfig->counterMode = TMR_COUNTER_MODE_UP;
    timeBaseConfig->repetitionCounter = 0x0000;
}

/*!
 * @brief     Configures the TMRx Div
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @param     div: specifies the Div Register value
 *
 * @param     mode: specifies the TMR Prescaler Reload mode
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_ConfigDIV(TMR_T* TMRx, uint16_t div, TMR_PRESCALER_RELOAD_T mode)
{
    TMRx->PSC = div;
    TMRx->CEG_B.UEG  = mode;
}

/*!
 * @brief      Specifies the TMRx Counter Mode to be used
 *
 * @param      TMRx: x can be can be 1 or 3 to select Timer
 *
 * @param      mode : specifies the Counter Mode to be used
 *
 * @retval     None
 */
void TMR_ConfigCounterMode(TMR_T* TMRx, TMR_COUNTER_MODE_T mode)
{
    TMRx->CTRL1_B.CNTDIR = mode;
    TMRx->CTRL1_B.CAMSEL = (mode) >> 1;
}

/*!
 * @brief     Sets the TMRx Counter Register value
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @param     counter: specifies the Counter register new value
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_SetCounter(TMR_T* TMRx, uint32_t counter)
{
    TMRx->CNT = counter;
}

/*!
 * @brief     Read the TMRx Counter value
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @retval    Counter Register value
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
uint32_t TMR_ReadCounter(TMR_T* TMRx)
{
    return (uint32_t)TMRx->CNT;
}

/*!
 * @brief     Sets the AutoReload Register value
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @param     autoReload: autoReload register new value
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_SetAutoReload(TMR_T* TMRx, uint32_t autoReload)
{
    TMRx->AUTORLD = autoReload;
}

/*!
 * @brief     Read the TMRx Div value
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @retval    Div Register value
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
uint32_t TMR_ReadDiv(TMR_T* TMRx)
{
    return (uint32_t)TMRx->PSC;
}

/*!
 * @brief     Enable the No update event
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_EnableNGUpdate(TMR_T* TMRx)
{
    TMRx->CTRL1_B.UD = ENABLE;
}

/*!
 * @brief     Enable the No update event
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_DisableNGUpdate(TMR_T* TMRx)
{
    TMRx->CTRL1_B.UD = DISABLE;
}

/*!
 * @brief     Configures the Update Request Interrupt source.
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @param     source: Config the Update source
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_ConfigUPdateRequest(TMR_T* TMRx, TMR_UPDATE_SOURCE_T source)
{
    if (source != TMR_UPDATE_SOURCE_GLOBAL)
    {
        TMRx->CTRL1_B.URSSEL = BIT_SET;
    }
    else
    {
        TMRx->CTRL1_B.URSSEL = BIT_RESET;
    }
}

/*!
 * @brief     Enables peripheral Preload register on AUTORLD
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_EnableAUTOReload(TMR_T* TMRx)
{
    TMRx->CTRL1_B.ARPEN = ENABLE;
}

/*!
 * @brief     Disable peripheral Preload register on AUTORLD
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_DisableAUTOReload(TMR_T* TMRx)
{
    TMRx->CTRL1_B.ARPEN = DISABLE;
}

/*!
 * @brief     Selects the One Pulse Mode
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @param     OPMode:Config OP Mode to be used
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_SelectOnePulseMode(TMR_T* TMRx, TMR_OPMODE_T OPMode)
{
    TMRx->CTRL1_B.SPMEN = OPMode;
}

/*!
 * @brief     Sets the Clock Division value
 *
 * @param     TMRx: x can be can be 1£¬2£¬3, 14, 15, 16 and 17 to select Timer
 *
 * @param     clockDivision: clock division value
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_SetClockDivision(TMR_T* TMRx, TMR_CKD_T clockDivision)
{
    TMRx->CTRL1_B.CLKDIV = clockDivision;
}

/*!
 * @brief     Enable the specified TMR peripheral
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_Enable(TMR_T* TMRx)
{
    TMRx->CTRL1_B.CNTEN = ENABLE;
}

/*!
 * @brief     Disable the specified TMR peripheral
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_Disable(TMR_T* TMRx)
{
    TMRx->CTRL1_B.CNTEN = DISABLE;
}

/*!
 * @brief     Configures the: Break feature, dead time, Lock level, the OSSI
 *
 * @param     TMRx: x can be can be 1, 15, 16 and 17 to select Timer
 *
 * @param     structure: pointer to a TMR_BDTInit_T structure that contains
 *            the BDT Register configuration  information for the TMR peripheral
 *
 * @retval    None
 */
void TMR_ConfigBDT(TMR_T* TMRx, TMR_BDTInit_T* structure)
{
    TMRx->BDT = (uint32_t)(((uint32_t)structure->automaticOutput) << 14) |
                (((uint32_t)structure->breakPolarity) << 13)   |
                (((uint32_t)structure->breakState) << 12)      |
                (((uint32_t)structure->RMOS_State) << 11)      |
                (((uint32_t)structure->IMOS_State) << 10)      |
                (((uint32_t)structure->lockLevel)  << 8)       |
                ((uint32_t)structure->deadTime);
}

/*!
 * @brief     Initialize the BDT timer with its default value.
 *
 * @param     structure: pointer to a TMR_BDTInit_T structure that contains
 *            the BDT Register configuration  information for the TMR peripheral
 *
 * @retval    None
 */
void TMR_ConfigBDTStructInit(TMR_BDTInit_T* structure)
{
    structure->RMOS_State = TMR_RMOS_STATE_DISABLE;
    structure->IMOS_State = TMR_IMOS_STATE_DISABLE;
    structure->lockLevel = TMR_LOCK_LEVEL_OFF;
    structure->deadTime = 0x00;
    structure->breakState = TMR_BREAK_STATE_DISABLE;
    structure->breakPolarity = TMR_BREAK_POLARITY_LOW;
    structure->automaticOutput = TMR_AUTOMATIC_OUTPUT_DISABLE;
}

/*!
 * @brief     Enable TMRx PWM output.
 *
 * @param     TMRx: x can be can be 1, 15, 16 and 17 to select Timer
 *
 * @retval    None
 */
void TMR_EnablePWMOutputs(TMR_T* TMRx)
{
    TMRx->BDT_B.MOEN = ENABLE;
}

/*!
 * @brief     Disable TMRx PWM output.
 *
 * @param     TMRx: x can be can be 1, 15, 16 and 17 to select Timer
 *
 * @retval    None
 */
void TMR_DisablePWMOutputs(TMR_T* TMRx)
{
    TMRx->BDT_B.MOEN = DISABLE;
}

/*!
 * @brief     Configure channel 1 according to parameters
 *
 * @param     TMRx: x can be can be 1, 2, 3, 14, 15, 16 and 17 to select Timer
 *
 * @param     OCcongigStruct: Channel configuration structure
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC1Config(TMR_T* TMRx, TMR_OCConfig_T* OCcongigStruct)
{

    /** Disable the Channel 1: Reset the CC1EN Bit */
    TMRx->CCEN_B.CC1EN = BIT_RESET;

    /** Reset and Select the Output Compare Mode Bits */
    TMRx->CCM1_OUTPUT_B.CC1SEL = BIT_RESET;
    TMRx->CCM1_OUTPUT_B.OC1MOD = OCcongigStruct->OC_Mode;

    /** Reset and Set the Output Polarity level */
    TMRx->CCEN_B.CC1POL = OCcongigStruct->OC_Polarity;

    /** Set the Output State */
    TMRx->CCEN_B.CC1EN = OCcongigStruct->OC_OutputState;

    if ((TMRx == TMR1) || (TMRx == TMR15) || (TMRx == TMR16)
            || (TMRx == TMR17))
    {
        /** Reset and Set the Output N Polarity level */
        TMRx->CCEN_B.CC1NPOL = OCcongigStruct->OC_NPolarity;

        /** Reset and Set the Output N State */
        TMRx->CCEN_B.CC1NEN = OCcongigStruct->OC_OutputNState;

        /** Reset the Output Compare and Output Compare N IDLE State */
        TMRx->CTRL2_B.OC1OIS = BIT_RESET;
        TMRx->CTRL2_B.OC1NOIS = BIT_RESET;

        /** Set the Output Idle state */
        TMRx->CTRL2_B.OC1OIS = OCcongigStruct->OC_Idlestate;
        /** Set the Output N State */
        TMRx->CTRL2_B.OC1NOIS = OCcongigStruct->OC_NIdlestate;
    }

    /** Set the Capture Compare Register value */
    TMRx->CC1 = OCcongigStruct->Pulse;
}

/*!
 * @brief     Configure channel 2 according to parameters
 *
 * @param     TMRx: x can be can be 1£¬2£¬3  and 15 to select Timer
 *
 * @param     OCcongigStruct: Channel configuration structure
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC2Config(TMR_T* TMRx, TMR_OCConfig_T* OCcongigStruct)
{

    /** Disable the Channel 2: Reset the CC2EN Bit */
    TMRx->CCEN_B.CC2EN = BIT_RESET;

    /** Reset and Select the Output Compare Mode Bits */
    TMRx->CCM1_OUTPUT_B.CC2SEL = BIT_RESET;
    TMRx->CCM1_OUTPUT_B.OC2MOD = OCcongigStruct->OC_Mode;

    /** Reset and Set the Output Polarity level */
    TMRx->CCEN_B.CC2POL = BIT_RESET;
    TMRx->CCEN_B.CC2POL = OCcongigStruct->OC_Polarity;

    /** Set the Output State */
    TMRx->CCEN_B.CC2EN = OCcongigStruct->OC_OutputState;

    if (TMRx == TMR1)
    {
        /** Reset and Set the Output N Polarity level */
        TMRx->CCEN_B.CC2NPOL = BIT_RESET;
        TMRx->CCEN_B.CC2NPOL = OCcongigStruct->OC_NPolarity;

        /** Reset and Set the Output N State */
        TMRx->CCEN_B.CC2NEN = BIT_RESET;
        TMRx->CCEN_B.CC2NEN = OCcongigStruct->OC_OutputNState;

        /** Reset the Output Compare and Output Compare N IDLE State */
        TMRx->CTRL2_B.OC2OIS = BIT_RESET;
        TMRx->CTRL2_B.OC2NOIS = BIT_RESET;

        /** Set the Output Idle state */
        TMRx->CTRL2_B.OC2OIS = OCcongigStruct->OC_Idlestate;
        /** Set the Output N State */
        TMRx->CTRL2_B.OC2NOIS = OCcongigStruct->OC_NIdlestate;
    }

    /** Set the Capture Compare Register value */
    TMRx->CC2 = OCcongigStruct->Pulse;
}

/*!
 * @brief     Configure channel 3 according to parameters
 *
 * @param     TMRx: x can be can be 1, 2, 3 to select Timer
 *
 * @param     OCcongigStruct: Channel configuration structure
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC3Config(TMR_T* TMRx, TMR_OCConfig_T* OCcongigStruct)
{

    /** Disable the Channel 3: Reset the CC3EN Bit */
    TMRx->CCEN_B.CC3EN = BIT_RESET;

    /** Reset and Select the Output Compare Mode Bits */
    TMRx->CCM2_OUTPUT_B.CC3SEL = BIT_RESET;
    TMRx->CCM2_OUTPUT_B.OC3MOD = OCcongigStruct->OC_Mode;

    /** Reset and Set the Output Polarity level */
    TMRx->CCEN_B.CC3POL = BIT_RESET;
    TMRx->CCEN_B.CC3POL = OCcongigStruct->OC_Polarity;

    /** Set the Output State */
    TMRx->CCEN_B.CC3EN = OCcongigStruct->OC_OutputState;

    if (TMRx == TMR1)
    {
        /** Reset and Set the Output N Polarity level */
        TMRx->CCEN_B.CC3NPOL = BIT_RESET;
        TMRx->CCEN_B.CC3NPOL = OCcongigStruct->OC_NPolarity;

        /** Reset and Set the Output N State */
        TMRx->CCEN_B.CC3NEN = BIT_RESET;
        TMRx->CCEN_B.CC3NEN = OCcongigStruct->OC_OutputNState;

        /** Reset the Output Compare and Output Compare N IDLE State */
        TMRx->CTRL2_B.OC3OIS = BIT_RESET;
        TMRx->CTRL2_B.OC3NOIS = BIT_RESET;

        /** Set the Output Idle state */
        TMRx->CTRL2_B.OC3OIS = OCcongigStruct->OC_Idlestate;
        /** Set the Output N State */
        TMRx->CTRL2_B.OC3NOIS = OCcongigStruct->OC_NIdlestate;
    }

    /** Set the Capture Compare Register value */
    TMRx->CC3 = OCcongigStruct->Pulse;
}

/*!
 * @brief     Configure channel 4 according to parameters
 *
 * @param     TMRx: x can be can be 1, 2, 3 to select Timer
 *
 * @param     OCcongigStruct: Channel configuration structure
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC4Config(TMR_T* TMRx, TMR_OCConfig_T* OCcongigStruct)
{

    /** Disable the Channel 4: Reset the CC4EN Bit */
    TMRx->CCEN_B.CC4EN = BIT_RESET;

    /** Reset and Select the Output Compare Mode Bits */
    TMRx->CCM2_OUTPUT_B.CC4SEL = BIT_RESET;
    TMRx->CCM2_OUTPUT_B.OC4MOD = OCcongigStruct->OC_Mode;

    /** Reset and Set the Output Polarity level */
    TMRx->CCEN_B.CC4POL = BIT_RESET;
    TMRx->CCEN_B.CC4POL = OCcongigStruct->OC_Polarity;

    /** Set the Output State */
    TMRx->CCEN_B.CC4EN = OCcongigStruct->OC_OutputState;

    if (TMRx == TMR1)
    {
        /** Reset the Output Compare and Output Compare IDLE State */
        TMRx->CTRL2_B.OC4OIS = BIT_RESET;

        /** Set the Output Idle state */
        TMRx->CTRL2_B.OC4OIS = OCcongigStruct->OC_Idlestate;
    }

    /** Set the Capture Compare Register value */
    TMRx->CC4 = OCcongigStruct->Pulse;
}

/*!
 * @brief     Initialize the OC timer with its default value.
 *
 * @param     OCcongigStruct: Channel configuration structure
 *
 * @retval    None
 */
void TMR_OCConfigStructInit(TMR_OCConfig_T* OCcongigStruct)
{
    /** Set the default configuration */
    OCcongigStruct->OC_Mode = TMR_OC_MODE_TMRING;
    OCcongigStruct->OC_OutputState = TMR_OUTPUT_STATE_DISABLE;
    OCcongigStruct->OC_OutputNState = TMR_OUTPUT_NSTATE_DISABLE;
    OCcongigStruct->Pulse = 0x0000;
    OCcongigStruct->OC_Polarity = TMR_OC_POLARITY_HIGH;
    OCcongigStruct->OC_NPolarity = TMR_OC_NPOLARITY_HIGH;
    OCcongigStruct->OC_Idlestate = TMR_OCIDLESTATE_RESET;
    OCcongigStruct->OC_NIdlestate = TMR_OCNIDLESTATE_RESET;
}

/*!
 * @brief     Selects the Output Compare Mode.
 *
 * @param     TMRx: x can be can be 1£¬2£¬3, 14, 15, 16 and 17 to select Timer
 *
 * @param     channel: specifies the TMR Channel
 *                    This parameter can be one of the following values:
 *                     @arg TMR_CHANNEL_1
 *                     @arg TMR_CHANNEL_2
 *                     @arg TMR_CHANNEL_3
 *                     @arg TMR_CHANNEL_4
 *
 * @param     OCMode: specifies the TMR Output Compare Mode
 *                    This parameter can be one of the following values:
 *                     @arg TMR_OC_MODE_TMRING
 *                     @arg TMR_OC_MODE_ACTIVE
 *                     @arg TMR_OC_MODE_INACTIVE
 *                     @arg TMR_OC_MODE_LOWLEVEL
  *                    @arg TMR_OC_MODE_HIGHLEVEL
 *                     @arg TMR_OC_MODE_PWM1
 *                     @arg TMR_OC_MODE_PWM2

 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_SelectOCxMode(TMR_T* TMRx, TMR_CHANNEL_T channel, TMR_OC_MODE_T mode)
{
    TMRx->CCEN &= BIT_RESET << channel;

    if (channel == TMR_CHANNEL_1)
    {
        TMRx->CCM1_OUTPUT_B.OC1MOD = mode;
    }
    else if (channel == TMR_CHANNEL_2)
    {
        TMRx->CCM1_OUTPUT_B.OC2MOD = mode;
    }
    else if (channel == TMR_CHANNEL_3)
    {
        TMRx->CCM2_OUTPUT_B.OC3MOD = mode;
    }
    else if (channel == TMR_CHANNEL_4)
    {
        TMRx->CCM2_OUTPUT_B.OC4MOD = mode;
    }
}

/*!
 * @brief     Sets the Capture Compare1 Register value
 *
 * @param     TMRx: x can be can be 1£¬2£¬3, 14, 15, 16 and 17 to select Timer
 *
 * @param     compare: specifies the Capture Compare1 register new value
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_SetCompare1(TMR_T* TMRx, uint32_t compare)
{
    TMRx->CC1 = compare;
}

/*!
 * @brief     Sets the Capture Compare2 Register value
 *
 * @param     TMRx: x can be can be 1£¬2£¬3 and 15 to select Timer
 *
 * @param     compare: specifies the Capture Compare1 register new value
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_SetCompare2(TMR_T* TMRx, uint32_t compare)
{
    TMRx->CC2 = compare;
}

/*!
 * @brief     Sets the Capture Compare3 Register value
 *
 * @param     TMRx: x can be can be 1, 2, 3 to select Timer
 *
 * @param     compare: specifies the Capture Compare1 register new value
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_SetCompare3(TMR_T* TMRx, uint32_t compare)
{
    TMRx->CC3 = compare;
}

/*!
 * @brief     Sets the Capture Compare4 Register value
 *
 * @param     TMRx: x can be can be 1, 2, 3 to select Timer
 *
 * @param     compare: specifies the Capture Compare1 register new value
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_SetCompare4(TMR_T* TMRx, uint32_t compare)
{
    TMRx->CC4 = compare;
}

/*!
 * @brief     Forces the output 1 waveform to active or inactive level
 *
 * @param     TMRx: x can be can be 1£¬2£¬3, 14, 15, 16 and 17 to select Timer
 *
 * @param     action: forced Action to be set to the output waveform
 *                  This parameter can be one of the following values:
 *                     @arg TMR_FORCEDACTION_INACTIVE
 *                     @arg TMR_FORCEDACTION_ACTIVE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ForcedOC1Config(TMR_T* TMRx, TMR_FORCED_ACTION_T action)
{
    TMRx->CCM1_OUTPUT_B.OC1MOD = action;
}

/*!
 * @brief     Forces the output 2 waveform to active or inactive level
 *
 * @param     TMRx: x can be can be 1£¬2£¬3 and 15 to select Timer
 *
 * @param     action: forced Action to be set to the output waveform
 *                  This parameter can be one of the following values:
 *                     @arg TMR_FORCEDACTION_INACTIVE
 *                     @arg TMR_FORCEDACTION_ACTIVE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ForcedOC2Config(TMR_T* TMRx, TMR_FORCED_ACTION_T action)
{
    TMRx->CCM1_OUTPUT_B.OC2MOD = action;
}

/*!
 * @brief     Forces the output 3 waveform to active or inactive level
 *
 * @param     TMRx: x can be can be 1, 2, 3 to select Timer
 *
 * @param     action: forced Action to be set to the output waveform
 *                  This parameter can be one of the following values:
 *                     @arg TMR_FORCEDACTION_INACTIVE
 *                     @arg TMR_FORCEDACTION_ACTIVE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ForcedOC3Config(TMR_T* TMRx, TMR_FORCED_ACTION_T action)
{
    TMRx->CCM2_OUTPUT_B.OC3MOD = action;
}

/*!
 * @brief     Forces the output 4 waveform to active or inactive level
 *
 * @param     TMRx: x can be can be 1, 2, 3 to select Timer
 *
 * @param     action: forced Action to be set to the output waveform
 *                  This parameter can be one of the following values:
 *                     @arg TMR_FORCEDACTION_INACTIVE
 *                     @arg TMR_FORCEDACTION_ACTIVE
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ForcedOC4Config(TMR_T* TMRx, TMR_FORCED_ACTION_T action)
{
    TMRx->CCM2_OUTPUT_B.OC4MOD = action;
}

/*!
 * @brief     Sets Capture Compare Preload Control bit
 *
 * @param     TMRx: x can be can be 1£¬2£¬3 and 15 to select Timer
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_EnableCCPreload(TMR_T* TMRx)
{
    TMRx->CTRL2_B.CCPEN = ENABLE;
}

/*!
 * @brief     Resets Capture Compare Preload Control bit
 *
 * @param     TMRx: x can be can be 1£¬2£¬3 and 15 to select Timer
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_DisableCCPreload(TMR_T* TMRx)
{
    TMRx->CTRL2_B.CCPEN = DISABLE;
}

/*!
 * @brief     Enables or disables the peripheral Preload register on CC1
 *
 * @param     TMRx: x can be can be 1, 2, 3 ,14, 15, 16 and 17 to select Timer
 *
 * @param     OCPreload: new state of the TMRx peripheral Preload register
 *                  This parameter can be one of the following values:
 *                     @arg TMR_OC_PRELOAD_DISABLE
 *                     @arg TMR_OC_PRELOAD_ENABLE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC1PreloadConfig(TMR_T* TMRx, TMR_OC_PRELOAD_T OCPreload)
{
    TMRx->CCM1_OUTPUT_B.OC1PEN = OCPreload;
}

/*!
 * @brief     Enables or disables the peripheral Preload register on CC2
 *
 * @param     TMRx: x can be can be 1, 2, 3 and 15 to select Timer
 *
 * @param     OCPreload: new state of the TMRx peripheral Preload register
 *                  This parameter can be one of the following values:
 *                     @arg TMR_OC_PRELOAD_DISABLE
 *                     @arg TMR_OC_PRELOAD_ENABLE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC2PreloadConfig(TMR_T* TMRx, TMR_OC_PRELOAD_T OCPreload)
{
    TMRx->CCM1_OUTPUT_B.OC2PEN = OCPreload;
}

/*!
 * @brief     Enables or disables the peripheral Preload register on CC3
 *
 * @param     TMRx: x can be can be 1, 2, 3 to select Timer
 *
 * @param     OCPreload: new state of the TMRx peripheral Preload register
 *                  This parameter can be one of the following values:
 *                     @arg TMR_OC_PRELOAD_DISABLE
 *                     @arg TMR_OC_PRELOAD_ENABLE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC3PreloadConfig(TMR_T* TMRx, TMR_OC_PRELOAD_T OCPreload)
{
    TMRx->CCM2_OUTPUT_B.OC3PEN = OCPreload;
}

/*!
 * @brief     Enables or disables the peripheral Preload register on CC4
 *
 * @param     TMRx: x can be can be 1, 2, 3 to select Timer
 *
 * @param     OCPreload: new state of the TMRx peripheral Preload register
 *                  This parameter can be one of the following values:
 *                     @arg TMR_OC_PRELOAD_DISABLE
 *                     @arg TMR_OC_PRELOAD_ENABLE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC4PreloadConfig(TMR_T* TMRx, TMR_OC_PRELOAD_T OCPreload)
{
    TMRx->CCM2_OUTPUT_B.OC4PEN = OCPreload;
}

/*!
 * @brief     Configures the Output Compare 1 Fast feature
 *
 * @param     TMRx: where x can be 1, 2, 3, 14, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     OCFast: new state of the Output Compare Fast Enable Bit
 *                  This parameter can be one of the following values:
 *                     @arg TMR_OCFAST_DISABLE
 *                     @arg TMR_OCFAST_ENABLE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */

void TMR_OC1FastConfit(TMR_T* TMRx, TMR_OCFAST_T OCFast)
{
    TMRx->CCM1_OUTPUT_B.OC1FEN = OCFast;
}

/*!
 * @brief     Configures the Output Compare 2 Fast feature
 *
 * @param     TMRx: where x can be 1, 2, 3 and 15 to select the TMR peripheral
 *
 * @param     OCFast: new state of the Output Compare Fast Enable Bit
 *                  This parameter can be one of the following values:
 *                     @arg TMR_OCFAST_DISABLE
 *                     @arg TMR_OCFAST_ENABLE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC2FastConfit(TMR_T* TMRx, TMR_OCFAST_T OCFast)
{
    TMRx->CCM1_OUTPUT_B.OC2FEN = OCFast;
}

/*!
 * @brief     Configures the Output Compare 3 Fast feature
 *
 * @param     TMRx: where x can be 1, 2, 3 to select the TMR peripheral
 *
 * @param     OCFast: new state of the Output Compare Fast Enable Bit
 *                  This parameter can be one of the following values:
 *                     @arg TMR_OCFAST_DISABLE
 *                     @arg TMR_OCFAST_ENABLE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC3FastConfit(TMR_T* TMRx, TMR_OCFAST_T OCFast)
{
    TMRx->CCM2_OUTPUT_B.OC3FEN = OCFast;
}

/*!
 * @brief     Configures the Output Compare 4 Fast feature
 *
 * @param     TMRx: where x can be 1, 2, 3 to select the TMR peripheral
 *
 * @param     OCFast: new state of the Output Compare Fast Enable Bit
 *                  This parameter can be one of the following values:
 *                     @arg TMR_OCFAST_DISABLE
 *                     @arg TMR_OCFAST_ENABLE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC4FastConfit(TMR_T* TMRx, TMR_OCFAST_T OCFast)
{
    TMRx->CCM2_OUTPUT_B.OC4FEN = OCFast;
}

/*!
 * @brief     Clears or safeguards the OCREF1 signal on an external event
 *
 * @param     TMRx: where x can be 1, 2, 3, 14, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     OCCler: new state of the Output Compare Clear Enable Bit
 *                  This parameter can be one of the following values:
 *                     @arg TMR_OCCLER_DISABLE
 *                     @arg TMR_OCCLER_ENABLE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ClearOC1Ref(TMR_T* TMRx, TMR_OCCLER_T OCCler)
{
    TMRx->CCM1_OUTPUT_B.OC1CEN = OCCler;
}

/*!
 * @brief     Clears or safeguards the OCREF2 signal on an external event
 *
 * @param     TMRx: where x can be 1, 2, 3 and 15 to select the TMR peripheral
 *
 * @param     OCCler: new state of the Output Compare Clear Enable Bit
 *                  This parameter can be one of the following values:
 *                     @arg TMR_OCCLER_DISABLE
 *                     @arg TMR_OCCLER_ENABLE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ClearOC2Ref(TMR_T* TMRx, TMR_OCCLER_T OCCler)
{
    TMRx->CCM1_OUTPUT_B.OC2CEN = OCCler;
}

/*!
 * @brief     Clears or safeguards the OCREF3 signal on an external event
 *
 * @param     TMRx: where x can be 1, 2, 3  to select the TMR peripheral
 *
 * @param     OCCler: new state of the Output Compare Clear Enable Bit
 *                  This parameter can be one of the following values:
 *                     @arg TMR_OCCLER_DISABLE
 *                     @arg TMR_OCCLER_ENABLE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ClearOC3Ref(TMR_T* TMRx, TMR_OCCLER_T OCCler)
{
    TMRx->CCM2_OUTPUT_B.OC3CEN = OCCler;
}

/*!
 * @brief     Clears or safeguards the OCREF4 signal on an external event
 *
 * @param     TMRx: where x can be 1, 2, 3 to select the TMR peripheral
 *
 * @param     OCCler: new state of the Output Compare Clear Enable Bit
 *                  This parameter can be one of the following values:
 *                     @arg TMR_OCCLER_DISABLE
 *                     @arg TMR_OCCLER_ENABLE
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ClearOC4Ref(TMR_T* TMRx, TMR_OCCLER_T OCCler)
{
    TMRx->CCM2_OUTPUT_B.OC4CEN = OCCler;
}

/*!
 * @brief     Configures the  channel 1 polarity
 *
 * @param     TMRx: where x can be 1, 2, 3, 14, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     OCPolarity: specifies the OC1 Polarity
 *                    This parameter can be one of the following values:
 *                     @arg TMR_OC_POLARITY_HIGH
 *                     @arg TMR_OC_POLARITY_LOW
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC1PolarityConfig(TMR_T* TMRx, TMR_OC_POLARITY_T OCPolarity)
{
    TMRx->CCEN_B.CC1POL = OCPolarity;
}

/*!
 * @brief     Configures the  channel 1N polarity
 *
 * @param     TMRx: where x can be 1, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     OCNPolarity: specifies the OC1 NPolarity
 *                    This parameter can be one of the following values:
 *                     @arg TMR_OC_NPOLARITY_HIGH
 *                     @arg TMR_OC_NPOLARITY_LOW
 * @retval    None
 */
void TMR_OC1NPolarityConfig(TMR_T* TMRx, TMR_OC_NPOLARITY_T OCNPolarity)
{
    TMRx->CCEN_B.CC1NPOL = OCNPolarity;
}

/*!
 * @brief     Configures the  channel 2 polarity
 *
 * @param     TMRx: where x can be 1, 2, 3 and 15 to select the TMR peripheral
 *
 * @param     OCPolarity: specifies the OC2 Polarity
 *                    This parameter can be one of the following values:
 *                     @arg TMR_OC_POLARITY_HIGH
 *                     @arg TMR_OC_POLARITY_LOW
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC2PolarityConfig(TMR_T* TMRx, TMR_OC_POLARITY_T OCPolarity)
{
    TMRx->CCEN_B.CC2POL = OCPolarity;
}

/*!
 * @brief     Configures the  channel 2N polarity
 *
 * @param     TMRx: where x can be 1 to select the TMR peripheral
 *
 * @param     OCNPolarity: specifies the OC2 NPolarity
 *                    This parameter can be one of the following values:
 *                     @arg TMR_OC_NPOLARITY_HIGH
 *                     @arg TMR_OC_NPOLARITY_LOW
 * @retval    None
 */
void TMR_OC2NPolarityConfig(TMR_T* TMRx, TMR_OC_NPOLARITY_T OCNPolarity)
{
    TMRx->CCEN_B.CC2NPOL = OCNPolarity;
}

/*!
 * @brief     Configures the  channel 3 polarity
 *
 * @param     TMRx: where x can be 1, 2, 3 to select the TMR peripheral
 *
 * @param     OCPolarity: specifies the OC3 Polarity
 *                    This parameter can be one of the following values:
 *                     @arg TMR_OC_POLARITY_HIGH
 *                     @arg TMR_OC_POLARITY_LOW
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC3PolarityConfig(TMR_T* TMRx, TMR_OC_POLARITY_T OCPolarity)
{
    TMRx->CCEN_B.CC3POL = OCPolarity;
}

/*!
 * @brief     Configures the  channel 3N polarity
 *
 * @param     TMRx: where x can be 1 to select the TMR peripheral
 *
 * @param     OCNPolarity: specifies the OC3 NPolarity
 *                    This parameter can be one of the following values:
 *                     @arg TMR_OC_NPOLARITY_HIGH
 *                     @arg TMR_OC_NPOLARITY_LOW
 * @retval    None
 */
void TMR_OC3NPolarityConfig(TMR_T* TMRx, TMR_OC_NPOLARITY_T OCNPolarity)
{
    TMRx->CCEN_B.CC3NPOL = OCNPolarity;
}

/*!
 * @brief     Configures the  channel 4 polarity
 *
 * @param     TMRx: where x can be 1, 2, 3 to select the TMR peripheral
 *
 * @param     OCPolarity: specifies the OC4 Polarity
 *                    This parameter can be one of the following values:
 *                     @arg TMR_OC_POLARITY_HIGH
 *                     @arg TMR_OC_POLARITY_LOW
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_OC4PolarityConfig(TMR_T* TMRx, TMR_OC_POLARITY_T OCPolarity)
{
    TMRx->CCEN_B.CC4POL = OCPolarity;
}

/*!
 * @brief     Selects the OCReference Clear source
 *
 * @param     TMRx: x can be  1, 2, 3 to select Timer.
 *
 * @param     OCReferenceClear: specifies the OCReference Clear source
 *                    This parameter can be one of the following values:
 *                     @arg TMR_OCCS_ETRF
 *                     @arg TMR_OCCS_OCREFCLR
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_SelectOCREFClear(TMR_T* TMRx, TMR_OCCSEL_T OCReferenceClear)
{
    TMRx->SMCTRL_B.OCCSEL = OCReferenceClear;
}

/*!
 * @brief     Enables the Capture Compare Channel x
 *
 * @param     TMRx: where x can be 1, 2, 3, 14, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     channel: TMR channel
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_EnableCCxChannel(TMR_T* TMRx, TMR_CHANNEL_T channel)
{
    TMRx->CCEN |= BIT_SET << channel;
}

/*!
 * @brief     Disables the Capture Compare Channel x
 *
 * @param     TMRx: where x can be 1, 2, 3, 14, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     channel: TMR channel
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_DisableCCxChannel(TMR_T* TMRx, TMR_CHANNEL_T channel)
{
    TMRx->CCEN &= ~(BIT_SET << channel);
}

/*!
 * @brief     Enables the Capture Compare Channel xN.
 *
 * @param     TMRx: where x can be 1, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     channel: TMR channel
 *
 * @retval    None
 */
void TMR_EnableCCxNChannel(TMR_T* TMRx, TMR_CHANNEL_T channel)
{
    TMRx->CCEN |= 0x04 << channel;
}

/*!
 * @brief     Disables the Capture Compare Channel xN
 *
 * @param     TMRx: where x can be 1, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     channel: TMR channel
 *
 * @retval    None
 */
void TMR_DisableCCxNChannel(TMR_T* TMRx, TMR_CHANNEL_T channel)
{
    TMRx->CCEN &= ~(0x04 << channel);
}

/*!
 * @brief     Enable Selects the TMR peripheral Commutation event
 *
 * @param     TMRx: where x can be 1, 15, 16 and 17 to select the TMR peripheral
 *
 * @retval    None
 */

void TMR_EnableSelectCOM(TMR_T* TMRx)
{
    TMRx->CTRL2_B.CCUSEL = ENABLE;
}
/*!
 * @brief     Disable Selects the TMR peripheral Commutation event
 *
 * @param     TMRx: where x can be 1, 15, 16 and 17 to select the TMR peripheral
 *
 * @retval    None
 */
void TMR_DisableSelectCOM(TMR_T* TMRx)
{
    TMRx->CTRL2_B.CCUSEL = DISABLE;
}

/*!
 * @brief     Configure the TI1 as Input.
 *
 * @param     TMRx: where x can be 1, 2, 3, 14, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     ICpolarity: The Input Polarity.
 *
 * @param     ICselection: specifies the input to be used.
 *
 * @param     ICfilter: Specifies the Input Capture Filter
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
static void TI1Config(TMR_T* TMRx, uint16_t ICpolarity, uint16_t ICselection, uint16_t ICfilter)
{
    uint16_t tmpchctrl = 0;

    /** Disable the Channel 1: Reset the CC1EN Bit */
    TMRx->CCEN_B.CC1EN = BIT_RESET;

    /** Select the Input and set the filter */
    TMRx->CCM1_INPUT_B.CC1SEL = BIT_RESET;
    TMRx->CCM1_INPUT_B.IC1F = BIT_RESET;
    TMRx->CCM1_INPUT_B.CC1SEL = ICselection;
    TMRx->CCM1_INPUT_B.IC1F = ICfilter;

    /** Select the Polarity */
    tmpchctrl = TMRx->CCEN;
    tmpchctrl &= (uint16_t)~((uint16_t)TMR_IC_POLARITY_BOTHEDGE);
    tmpchctrl |= ICpolarity;
    TMRx->CCEN = tmpchctrl;

    /** Set the CC1EN Bit */
    TMRx->CCEN_B.CC1EN = BIT_SET;
}

/*!
 * @brief     Configure the TI2 as Input
 *
 * @param     TMRx: where x can be 1, 2, 3, 14, 15, 16 and 17 to select the TMR periphera
 *
 * @param     ICpolarity: The Input Polarity.
 *
 * @param     ICselection: specifies the input to be used.
 *
 * @param     ICfilter: Specifies the Input Capture Filter
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
static void TI2Config(TMR_T* TMRx, uint16_t ICpolarity, uint16_t ICselection, uint16_t ICfilter)
{
    uint16_t tmpchctrl = 0;

    /** Disable the Channel 2: Reset the CC2EN Bit */
    TMRx->CCEN_B.CC2EN = BIT_RESET;

    /** Select the Input and set the filter */
    TMRx->CCM1_INPUT_B.CC2SEL = BIT_RESET;
    TMRx->CCM1_INPUT_B.IC2F = BIT_RESET;
    TMRx->CCM1_INPUT_B.CC2SEL = ICselection;
    TMRx->CCM1_INPUT_B.IC2F = ICfilter;

    /** Select the Polarity */
    tmpchctrl = TMRx->CCEN;
    tmpchctrl &= (uint16_t)~((uint16_t)TMR_IC_POLARITY_BOTHEDGE << 4);
    tmpchctrl |= (uint16_t)(ICpolarity << 4);
    TMRx->CCEN = tmpchctrl;

    /** Set the CC2EN Bit */
    TMRx->CCEN_B.CC2EN = BIT_SET;
}

/*!
 * @brief     Configure the TI3 as Input.
 *
 * @param     TMRx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TMR peripheral
 *
 * @param     ICpolarity: The Input Polarity.
 *
 * @param     ICselection: specifies the input to be used.
 *
 * @param     ICfilter: Specifies the Input Capture Filter
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
static void TI3Config(TMR_T* TMRx, uint16_t ICpolarity, uint16_t ICselection, uint16_t ICfilter)
{
    uint16_t tmpchctrl = 0;

    /** Disable the Channel 3: Reset the CC3EN Bit */
    TMRx->CCEN_B.CC3EN = BIT_RESET;

    /** Select the Input and set the filter */
    TMRx->CCM2_INPUT_B.CC3SEL = BIT_RESET;
    TMRx->CCM2_INPUT_B.IC3F = BIT_RESET;
    TMRx->CCM2_INPUT_B.CC3SEL = ICselection;
    TMRx->CCM2_INPUT_B.IC3F = ICfilter;

    /** Select the Polarity */
    tmpchctrl = TMRx->CCEN;
    tmpchctrl &= (uint16_t)~((uint16_t)TMR_IC_POLARITY_BOTHEDGE << 8);
    tmpchctrl |= (uint16_t)(ICpolarity << 8);
    TMRx->CCEN = tmpchctrl;

    /** Set the CC3EN Bit */
    TMRx->CCEN_B.CC3EN = BIT_SET;
}

/*!
 * @brief     Configure the TI4 as Input
 *
 * @param     TMRx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TMR peripheral
 *
 * @param     ICpolarity: The Input Polarity.
 *
 * @param     ICselection: specifies the input to be used.
 *
 * @param     ICfilter: Specifies the Input Capture Filter
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
static void TI4Config(TMR_T* TMRx, uint16_t ICpolarity, uint16_t ICselection, uint16_t ICfilter)
{
    uint16_t tmpchctrl = 0;

    /** Disable the Channel 4: Reset the CC4EN Bit */
    TMRx->CCEN_B.CC4EN = BIT_RESET;

    /** Select the Input and set the filter */
    TMRx->CCM2_INPUT_B.CC4SEL = BIT_RESET;
    TMRx->CCM2_INPUT_B.IC4F = BIT_RESET;
    TMRx->CCM2_INPUT_B.CC4SEL = ICselection;
    TMRx->CCM2_INPUT_B.IC4F = ICfilter;

    /** Select the Polarity */
    tmpchctrl = TMRx->CCEN;
    tmpchctrl &= (uint16_t)~((uint16_t)TMR_IC_POLARITY_BOTHEDGE << 12);
    tmpchctrl |= (uint16_t)(ICpolarity << 12);
    TMRx->CCEN = tmpchctrl;

    /** Set the CC4EN Bit */
    TMRx->CCEN_B.CC4EN = BIT_SET;
}

/*!
 * @brief     Configure Peripheral equipment
 *
 * @param     TMRx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TMR peripheral
 *
 * @param     ICconfigstruct: pointer to a TMR_ICConfig_T structure
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ICConfig(TMR_T* TMRx, TMR_ICConfig_T* ICconfigstruct)
{
    if (ICconfigstruct->channel == TMR_CHANNEL_1)
    {
        /** TI1 Configuration */
        TI1Config(TMRx, ICconfigstruct->ICpolarity, ICconfigstruct->ICselection, ICconfigstruct->ICfilter);
        TMR_SetIC1Prescal(TMRx, ICconfigstruct->ICprescaler);
    }
    else if (ICconfigstruct->channel == TMR_CHANNEL_2)
    {
        /** TI2 Configuration */
        TI2Config(TMRx, ICconfigstruct->ICpolarity, ICconfigstruct->ICselection, ICconfigstruct->ICfilter);
        TMR_SetIC2Prescal(TMRx, ICconfigstruct->ICprescaler);
    }
    else if (ICconfigstruct->channel == TMR_CHANNEL_3)
    {
        /** TI3 Configuration */
        TI3Config(TMRx, ICconfigstruct->ICpolarity, ICconfigstruct->ICselection, ICconfigstruct->ICfilter);
        TMR_SetIC3Prescal(TMRx, ICconfigstruct->ICprescaler);
    }
    else if (ICconfigstruct->channel == TMR_CHANNEL_4)
    {
        /** TI4 Configuration */
        TI4Config(TMRx, ICconfigstruct->ICpolarity, ICconfigstruct->ICselection, ICconfigstruct->ICfilter);
        TMR_SetIC4Prescal(TMRx, ICconfigstruct->ICprescaler);
    }
}

/*!
 * @brief     Initialize the IC timer with its default value.
 *
 * @param     ICconfigstruct: pointer to a TMR_ICConfig_T structure
 *
 * @retval    None
 */
void TMR_ICConfigStructInit(TMR_ICConfig_T* ICconfigstruct)
{
    ICconfigstruct->channel = TMR_CHANNEL_1;
    ICconfigstruct->ICpolarity = TMR_IC_POLARITY_RISING;
    ICconfigstruct->ICselection = TMR_IC_SELECTION_DIRECT_TI;
    ICconfigstruct->ICprescaler = TMR_ICPSC_DIV1;
    ICconfigstruct->ICfilter = 0x00;
}

/*!
 * @brief     Config of PWM output
 *
 * @param     TMRx: where x can be 1, 2, 3 and 15 to select the TMR peripheral
 *
 * @param     ICconfigstruct: pointer to a TMR_ICConfig_T structure
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_PWMConfig(TMR_T* TMRx, TMR_ICConfig_T* ICconfigstruct)
{
    uint16_t icpolarity = TMR_IC_POLARITY_RISING;
    uint16_t icselection = TMR_IC_SELECTION_DIRECT_TI;

    /** Select the Opposite Input Polarity */
    if (ICconfigstruct->ICpolarity == TMR_IC_POLARITY_RISING)
    {
        icpolarity = TMR_IC_POLARITY_FALLING;
    }
    else
    {
        icpolarity = TMR_IC_POLARITY_RISING;
    }

    /** Select the Opposite Input */
    if (ICconfigstruct->ICselection == TMR_IC_SELECTION_DIRECT_TI)
    {
        icselection = TMR_IC_SELECTION_INDIRECT_TI;
    }
    else
    {
        icselection = TMR_IC_SELECTION_DIRECT_TI;
    }

    if (ICconfigstruct->channel == TMR_CHANNEL_1)
    {
        /** TI1 Configuration */
        TI1Config(TMRx, ICconfigstruct->ICpolarity, ICconfigstruct->ICselection, ICconfigstruct->ICfilter);
        /** Set the Input Capture Prescaler value */
        TMR_SetIC1Prescal(TMRx, ICconfigstruct->ICprescaler);
        /** TI2 Configuration */
        TI2Config(TMRx, icpolarity, icselection, ICconfigstruct->ICfilter);
        /** Set the Input Capture Prescaler value */
        TMR_SetIC2Prescal(TMRx, ICconfigstruct->ICprescaler);
    }
    else
    {
        /** TI2 Configuration */
        TI2Config(TMRx, ICconfigstruct->ICpolarity, ICconfigstruct->ICselection, ICconfigstruct->ICfilter);
        /** Set the Input Capture Prescaler value */
        TMR_SetIC2Prescal(TMRx, ICconfigstruct->ICprescaler);
        /** TI1 Configuration */
        TI1Config(TMRx, icpolarity, icselection, ICconfigstruct->ICfilter);
        /** Set the Input Capture Prescaler value */
        TMR_SetIC1Prescal(TMRx, ICconfigstruct->ICprescaler);
    }
}

/*!
 * @brief     Read Input Capture 1 value
 *
 * @param     TMRx: where x can be 1, 2, 3, 14, 15, 16 and 17 to select the TMR peripheral
 *
 * @retval    Capture Compare 1 Register value
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
uint16_t TMR_ReadCaputer1(TMR_T* TMRx)
{
    return TMRx->CC1;
}

/*!
 * @brief     Read Input Capture 2 value
 *
 * @param     TMRx: where x can be 1, 2, 3 and 15 to select the TMR peripheral
 *
 * @retval    Capture Compare 2 Register value
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
uint16_t TMR_ReadCaputer2(TMR_T* TMRx)
{
    return TMRx->CC2;
}

/*!
 * @brief     Read Input Capture 3 value
 *
 * @param     TMRx: where x can be 1, 2, 3 to select the TMR peripheral
 *
 * @retval    Capture Compare 3 Register value
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
uint16_t TMR_ReadCaputer3(TMR_T* TMRx)
{
    return TMRx->CC3;
}

/*!
 * @brief     Read Input Capture 4 value
 *
 * @param     TMRx: where x can be 1, 2, 3 to select the TMR peripheral
 *
 * @retval    Capture Compare 4 Register value
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
uint16_t TMR_ReadCaputer4(TMR_T* TMRx)
{
    return TMRx->CC4;
}

/*!
 * @brief     Sets the TMRx Input Capture 1 prescaler
 *
 * @param     TMRx: where x can be 1, 2, 3, 14, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     prescaler: specifies the Input Capture 1 prescaler new value
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_SetIC1Prescal(TMR_T* TMRx, TMR_IC_PRESCALER_T prescaler)
{
    TMRx->CCM1_INPUT_B.IC1PSC = BIT_RESET;
    TMRx->CCM1_INPUT_B.IC1PSC = prescaler;
}
/*!
 * @brief     Sets the TMRx Input Capture 2 prescaler
 *
 * @param     TMRx: where x can be 1, 2, 3 and 15 to select the TMR peripheral
 *
 * @param     prescaler: specifies the Input Capture 2 prescaler new value
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_SetIC2Prescal(TMR_T* TMRx, TMR_IC_PRESCALER_T prescaler)
{
    TMRx->CCM1_INPUT_B.IC2PSC = BIT_RESET;
    TMRx->CCM1_INPUT_B.IC2PSC = prescaler;
}

/*!
 * @brief     Sets the TMRx Input Capture 3 prescaler
 *
 * @param     TMRx: where x can be 1, 2, 3 to select the TMR peripheral
 *
 * @param     prescaler: specifies the Input Capture 3 prescaler new value
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_SetIC3Prescal(TMR_T* TMRx, TMR_IC_PRESCALER_T prescaler)
{
    TMRx->CCM2_INPUT_B.IC3PSC = BIT_RESET;
    TMRx->CCM2_INPUT_B.IC3PSC = prescaler;
}

/*!
 * @brief     Sets the TMRx Input Capture 4 prescaler
 *
 * @param     TMRx: where x can be 1, 2, 3 to select the TMR peripheral
 *
 * @param     prescaler: specifies the Input Capture 4 prescaler new value
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_SetIC4Prescal(TMR_T* TMRx, TMR_IC_PRESCALER_T prescaler)
{
    TMRx->CCM2_INPUT_B.IC4PSC = BIT_RESET;
    TMRx->CCM2_INPUT_B.IC4PSC = prescaler;
}

/*!
 * @brief     Enable intterupts
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @param     interrupt: specifies the TMR interrupts sources
 *                     The parameter can be any combination of following values:
 *                     @arg TMR_INT_UPDATE: TMR update Interrupt source
 *                     @arg TMR_INT_CH1:    TMR Capture Compare 1 Interrupt source
 *                     @arg TMR_INT_CH2:    TMR Capture Compare 2 Interrupt source
 *                     @arg TMR_INT_CH3:    TMR Capture Compare 3 Interrupt source
 *                     @arg TMR_INT_CH4:    TMR Capture Compare 4 Interrupt source
 *                     @arg TMR_INT_CCU:    TMR Commutation Interrupt source
 *                     @arg TMR_INT_TRG:    TMR Trigger Interrupt source
 *                     @arg TMR_INT_BRK:    TMR Break Interrupt source
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_EnableInterrupt(TMR_T* TMRx, uint16_t interrupt)
{
    TMRx->DIEN |= interrupt;
}

/*!
 * @brief     Disable intterupts
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @param     interrupt: specifies the TMR interrupts sources
 *                     The parameter can be any combination of following values:
 *                     @arg TMR_INT_UPDATE: TMR update Interrupt source
 *                     @arg TMR_INT_CH1:    TMR Capture Compare 1 Interrupt source
 *                     @arg TMR_INT_CH2:    TMR Capture Compare 2 Interrupt source
 *                     @arg TMR_INT_CH3:    TMR Capture Compare 3 Interrupt source
 *                     @arg TMR_INT_CH4:    TMR Capture Compare 4 Interrupt source
 *                     @arg TMR_INT_CCU:    TMR Commutation Interrupt source
 *                     @arg TMR_INT_TRG:    TMR Trigger Interrupt source
 *                     @arg TMR_INT_BRK:    TMR Break Interrupt source
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_DisableInterrupt(TMR_T* TMRx, uint16_t interrupt)
{
    TMRx->DIEN &= ~interrupt;
}

/*!
 * @brief     Configures the TMRx event to be generate by software
 *
 * @param     TMRx: where x can be 1£¬2£¬3, 14, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     event:   specifies the TMR generate event
 *                     The parameter can be any combination of following values:
 *                     @arg TMR_EVENT_UPDATE: TMR update Interrupt source
 *                     @arg TMR_EVENT_CH1:    TMR Capture Compare 1 Interrupt source
 *                     @arg TMR_EVENT_CH2:    TMR Capture Compare 2 Interrupt source
 *                     @arg TMR_EVENT_CH3:    TMR Capture Compare 3 Interrupt source
 *                     @arg TMR_EVENT_CH4:    TMR Capture Compare 4 Interrupt source
 *                     @arg TMR_EVENT_CCU:    TMR Commutation Interrupt source
 *                     @arg TMR_EVENT_TRG:    TMR Trigger Interrupt source
 *                     @arg TMR_EVENT_BRK:    TMR Break Interrupt source
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 *            TMR6 and TMR7 only TMR_EVENT_UPDATE
 *            TMR_EVENT_CCU and TMR_EVENT_BRK are used only with TMR1
 */
void TMR_GenerateEvent(TMR_T* TMRx, uint16_t event)
{
    TMRx->CEG |= event;
}

/*!
 * @brief     Check whether the flag is set or reset
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 *
 * @param     flag: specifies the TMR flag
 *                     The parameter can be one of following values:
 *                     @arg TMR_FLAG_UPDATA:  TMR update Flag
 *                     @arg TMR_FLAG_CH1:     TMR Capture Compare 1 flag
 *                     @arg TMR_FLAG_CH2:     TMR Capture Compare 2 flag
 *                     @arg TMR_FLAG_CH3:     TMR Capture Compare 3 flag
 *                     @arg TMR_FLAG_CH4:     TMR Capture Compare 4 flag
 *                     @arg TMR_FLAG_CCU:     TMR Commutation flag
 *                     @arg TMR_FLAG_TRG:     TMR Trigger flag
 *                     @arg TMR_FLAG_BRK:     TMR Break flag
 *                     @arg TMR_FLAG_CH1OC:   TMR Capture Compare 1 overcapture flag
 *                     @arg TMR_FLAG_CH2OC:   TMR Capture Compare 2 overcapture flag
 *                     @arg TMR_FLAG_CH3OC:   TMR Capture Compare 3 overcapture flag
 *                     @arg TMR_FLAG_CH4OC:   TMR Capture Compare 4 overcapture flag
 *
 * @retval    The new state of the flag is SET or RESET
 *
 * @note      TMR15 can have only TMR_FLAG_UPDATA, TMR_FLAG_CH1, TMR_FLAG_CH2 and TMR_FLAG_TRG
 *            TMR14, TMR16 and TMR17 can have TMR_FLAG_UPDATA and TMR_FLAG_CH1
 *            TMR6, TMR7 only TMR_FLAG_UPDATA
 *            TMR_FLAG_BRK is used only with TMR1 and TMR15.
 *            TMR_FLAG_CCU is used only with TMR1, TMR15, TMR16 and TMR17
 */
uint16_t TMR_ReadStatusFlag(TMR_T* TMRx, TMR_FLAG_T flag)
{
    if ((TMRx->STS & flag) != RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/*!
 * @brief     Clears the TMR's pending flags
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 *
 * @param     flag: specifies the TMR flag
 *                     The parameter can be any combination of following values:
 *                     @arg TMR_FLAG_UPDATA:  TMR update Flag
 *                     @arg TMR_FLAG_CH1:     TMR Capture Compare 1 flag
 *                     @arg TMR_FLAG_CH2:     TMR Capture Compare 2 flag
 *                     @arg TMR_FLAG_CH3:     TMR Capture Compare 3 flag
 *                     @arg TMR_FLAG_CH4:     TMR Capture Compare 4 flag
 *                     @arg TMR_FLAG_CCU:     TMR Commutation flag
 *                     @arg TMR_FLAG_TRG:     TMR Trigger flag
 *                     @arg TMR_FLAG_BRK:     TMR Break flag
 *                     @arg TMR_FLAG_CH1OC:   TMR Capture Compare 1 overcapture flag
 *                     @arg TMR_FLAG_CH2OC:   TMR Capture Compare 2 overcapture flag
 *                     @arg TMR_FLAG_CH3OC:   TMR Capture Compare 3 overcapture flag
 *                     @arg TMR_FLAG_CH4OC:   TMR Capture Compare 4 overcapture flag
 *
 * @retval    None
 */
void TMR_ClearStatusFlag(TMR_T* TMRx, uint16_t flag)
{
    TMRx->STS = ~flag;
}

/*!
 * @brief     Check whether the TMR Interrupt flag is set or reset
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 *
 * @param     flag: specifies the TMR interrupts flag
 *                     The parameter can be one of following values:
 *                     @arg TMR_INT_FLAG_UPDATE: TMR update Interrupt flag
 *                     @arg TMR_INT_FLAG_CH1:    TMR Capture Compare 1 Interrupt flag
 *                     @arg TMR_INT_FLAG_CH2:    TMR Capture Compare 2 Interrupt flag
 *                     @arg TMR_INT_FLAG_CH3:    TMR Capture Compare 3 Interrupt flag
 *                     @arg TMR_INT_FLAG_CH4:    TMR Capture Compare 4 Interrupt flag
 *                     @arg TMR_INT_FLAG_CCU:    TMR Commutation Interrupt flag
 *                     @arg TMR_INT_FLAG_TRG:    TMR Trigger Interrupt flag
 *                     @arg TMR_INT_FLAG_BRK:    TMR Break Interrupt flag
 *
 * @retval    The new state of the INT flag is SET or RESET
 *
 * @note      TMR15 can have only TMR_INT_FLAG_UPDATE, TMR_INT_FLAG_CH1, TMR_INT_FLAG_CH2 and TMR_INT_FLAG_TRG
 *            TMR14, TMR16 and TMR17 can have TMR_INT_FLAG_UPDATE and TMR_INT_FLAG_CH1
 *            TMR6, TMR7 only TMR_INT_FLAG_UPDATE
 *            TMR_INT_FLAG_BRK is used only with TMR1 and TMR15.
 *            TMR_INT_FLAG_CCU is used only with TMR1, TMR15, TMR16 and TMR17
 */
uint16_t TMR_ReadIntFlag(TMR_T* TMRx, TMR_INT_FLAG_T flag)
{
    if (((TMRx->STS & flag) != RESET) && ((TMRx->DIEN & flag) != RESET))
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/*!
 * @brief     Clears the TMR's interrupt pending bits
 *
 * @param     TMRx: x can be can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select Timer
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 *
 * @param     flag: specifies the TMR interrupts flag
 *                     The parameter can be any combination of following values:
 *                     @arg TMR_INT_FLAG_UPDATE: TMR update Interrupt flag
 *                     @arg TMR_INT_FLAG_CH1:    TMR Capture Compare 1 Interrupt flag
 *                     @arg TMR_INT_FLAG_CH2:    TMR Capture Compare 2 Interrupt flag
 *                     @arg TMR_INT_FLAG_CH3:    TMR Capture Compare 3 Interrupt flag
 *                     @arg TMR_INT_FLAG_CH4:    TMR Capture Compare 4 Interrupt flag
 *                     @arg TMR_INT_FLAG_CCU:    TMR Commutation Interrupt flag
 *                     @arg TMR_INT_FLAG_TRG:    TMR Trigger Interrupt flag
 *                     @arg TMR_INT_FLAG_BRK:    TMR Break Interrupt flag
 *
 * @retval    None
 */
void TMR_ClearIntFlag(TMR_T* TMRx, uint16_t flag)
{
    TMRx->STS = ~flag;
}

/*!
 * @brief     Configures the TMRx's DMA interface.
 *
 * @param     TMRx: where x can be 1, 2, 3, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     address: DMA Base address
 *
 * @param     lenght: DMA Burst length
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ConfigDMA(TMR_T* TMRx, TMR_DMA_BASE_ADDERSS_T address, TMR_DMA_BURST_LENGHT_T lenght)
{
    TMRx->DCTRL = (uint32_t)address | (uint32_t)lenght;
}

/*!
 * @brief     Enable TMRx Requests
 *
 * @param     TMRx: where x can be 1, 2, 3, 6, 7, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     souces: specifies the TMR DMA souces
 *                     The parameter can be any combination of following values:
 *                     @arg TMR_DMA_UPDATE: TMR update DMA souces
 *                     @arg TMR_DMA_CH1:    TMR Capture Compare 1 DMA souces
 *                     @arg TMR_DMA_CH2:    TMR Capture Compare 2 DMA souces
 *                     @arg TMR_DMA_CH3:    TMR Capture Compare 3 DMA souces
 *                     @arg TMR_DMA_CH4:    TMR Capture Compare 4 DMA souces
 *                     @arg TMR_DMA_CCU:    TMR Commutation DMA souces
 *                     @arg TMR_DMA_TRG:    TMR Trigger DMA souces
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_EnableDMASoure(TMR_T* TMRx, uint16_t souces)
{
    TMRx->DIEN |= souces;
}

/*!
 * @brief     Disable TMRx Requests
 *
 * @param     TMRx: where x can be 1, 2, 3, 6, 7, 15, 16 and 17 to select the TMR peripheral
 *
 * @param     souces: specifies the TMR DMA souces
 *                     The parameter can be any combination of following values:
 *                     @arg TMR_DMA_UPDATE: TMR update DMA souces
 *                     @arg TMR_DMA_CH1:    TMR Capture Compare 1 DMA souces
 *                     @arg TMR_DMA_CH2:    TMR Capture Compare 2 DMA souces
 *                     @arg TMR_DMA_CH3:    TMR Capture Compare 3 DMA souces
 *                     @arg TMR_DMA_CH4:    TMR Capture Compare 4 DMA souces
 *                     @arg TMR_DMA_CCU:    TMR Commutation DMA souces
 *                     @arg TMR_DMA_TRG:    TMR Trigger DMA souces
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_DisableDMASoure(TMR_T* TMRx, uint16_t souces)
{
    TMRx->DIEN &= ~souces;
}

/*!
 * @brief     Enable Capture Compare DMA source
 *
 * @param     TMRx: where x can be 1, 2, 3, 15, 16 and 17 to select the TMR peripheral
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_EnableCCDMA(TMR_T* TMRx)
{
    TMRx->CTRL2_B.CCDSEL = ENABLE;
}

/*!
 * @brief     Disable Capture Compare DMA source
 *
 * @param     TMRx: where x can be 1, 2, 3, 15, 16 and 17 to select the TMR peripheral
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_DisableCCDMA(TMR_T* TMRx)
{
    TMRx->CTRL2_B.CCDSEL = DISABLE;
}

/*!
 * @brief     Configures the TMRx internal Clock
 *
 * @param     TMRx: where x can be 1, 2, 3, and 15 select the TMR peripheral
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ConfigInternalClock(TMR_T* TMRx)
{
    TMRx->SMCTRL_B.SMFSEL = DISABLE;
}

/*!
 * @brief     Configures the TMRx Internal Trigger as External Clock
 *
 * @param     TMRx: where x can be 1, 2, 3, and 15 select the TMR peripheral
 *
 * @param     input: specifies the TMR trigger souces
 *                     The parameter can be one of following values:
 *                     @arg TMR_TS_ITR0:    TMR Internal Trigger 0
 *                     @arg TMR_TS_ITR1:    TMR Internal Trigger 1
 *                     @arg TMR_TS_ITR2:    TMR Internal Trigger 2
 *                     @arg TMR_TS_ITR3:    TMR Internal Trigger 3
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ConfigITRxExternalClock(TMR_T* TMRx, TMR_INPUT_TRIGGER_SOURCE_T input)
{
    TMR_SelectInputTrigger(TMRx, input);
    TMRx->SMCTRL_B.SMFSEL = 0x07;
}

/*!
 * @brief     Configures the TMRx  Trigger as External Clock
 *
 * @param     TMRx: where x can be 1, 2, 3, and 15 select the TMR peripheral
 *
 * @param     input: specifies the TMR trigger souces
 *                     The parameter can be one of following values:
 *                     @arg TMR_TS_TI1F_ED:  TI1 Edge Detector
 *                     @arg TMR_TS_TI1FP1:   Filtered Timer Input 1
 *                     @arg TMR_TS_TI2FP2:   Filtered Timer Input 2
 *
 * @param     ICpolarity: specifies the TMR IC polarity
 *                     The parameter can be one of following values:
 *                     @arg TMR_IC_POLARITY_RISING:  TMR IC polarity rising
 *                     @arg TMR_IC_POLARITY_FALLING: TMR IC polarity falling
 *
 * @param     ICfilter:specifies the filter value.This parameter must be a value between 0x00 and 0x0F.
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ConfigTIxExternalClock(TMR_T* TMRx, TMR_INPUT_TRIGGER_SOURCE_T input,
                                TMR_IC_POLARITY_T ICpolarity, uint16_t ICfilter)
{
    if (input == TMR_TS_TI2FP2)
    {
        TI2Config(TMRx, ICpolarity, TMR_IC_SELECTION_DIRECT_TI, ICfilter);
    }
    else
    {
        TI1Config(TMRx, ICpolarity, TMR_IC_SELECTION_DIRECT_TI, ICfilter);
    }

    TMR_SelectInputTrigger(TMRx, input);
    TMRx->SMCTRL_B.SMFSEL = 0x07;
}

/*!
 * @brief     Configures the External clock Mode1
 *
 * @param     TMRx: where x can be 1, 2, 3 select the TMR peripheral
 *
 * @param     prescaler: The external Trigger Prescaler.
 *
 * @param     polarity: The external Trigger Polarity.
 *
 * @param     filter: External Trigger Filter.
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ConfigExternalClockMode1(TMR_T* TMRx, TMR_EXTTRG_PRESCALER_T prescaler,
                                  TMR_EXTTRG_POLARITY_T polarity, uint16_t filter)
{
    TMR_ConfigExternalTrigger(TMRx, prescaler, polarity, filter);
    TMRx->SMCTRL_B.SMFSEL = BIT_RESET;
    TMRx->SMCTRL_B.SMFSEL = 0x07;
    TMRx->SMCTRL_B.TRGSEL = 0x07;
}

/*!
 * @brief     Configures the External clock Mode2
 *
 * @param     TMRx: where x can be 1, 2, 3 select the TMR peripheral
 *
 * @param     prescaler: The external Trigger Prescaler
 *
 * @param     polarity: The external Trigger Polarity
 *
 * @param     filter: External Trigger Filter
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ConfigExternalClockMode2(TMR_T* TMRx, TMR_EXTTRG_PRESCALER_T prescaler,
                                  TMR_EXTTRG_POLARITY_T polarity, uint16_t filter)
{
    TMR_ConfigExternalTrigger(TMRx, prescaler, polarity, filter);
    TMRx->SMCTRL_B.ECEN = ENABLE;
}

/*!
 * @brief     Selects the Input Trigger source
 *
 * @param     TMRx: where x can be 1, 2, 3 and 15 select the TMR peripheral
 *
 * @param     input: specifies the TMR trigger souces
 *                     The parameter can be one of following values:
 *                     @arg TMR_TS_ITR0:     TMR Internal Trigger 0
 *                     @arg TMR_TS_ITR1:     TMR Internal Trigger 1
 *                     @arg TMR_TS_ITR2:     TMR Internal Trigger 2
 *                     @arg TMR_TS_ITR3:     TMR Internal Trigger 3
 *                     @arg TMR_TS_TI1F_ED:  TI1 Edge Detector
 *                     @arg TMR_TS_TI1FP1:   Filtered Timer Input 1
 *                     @arg TMR_TS_TI2FP2:   Filtered Timer Input 2
 *                     @arg TMR_TS_ETRF:     External Trigger input
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_SelectInputTrigger(TMR_T* TMRx, TMR_INPUT_TRIGGER_SOURCE_T input)
{
    TMRx->SMCTRL_B.TRGSEL = BIT_RESET;
    TMRx->SMCTRL_B.TRGSEL = input;
}

/*!
 * @brief     Selects the Trigger Output Mode.
 *
 * @param     TMRx: where x can be 1, 2, 3, 6, 7 and 15 select the TMR peripheral
 *
 * @param     source: specifies the TMR trigger souces
 *                    The parameter can be one of following values:
 *                    For all TMR:
 *                        @arg TMR_TRGOSOURCE_RESET
 *                        @arg TMR_TRGOSOURCE_ENABLE
 *                        @arg TMR_TRGOSOURCE_UPDATE
                      For all TMR except TMR6 and TMR7
 *                        @arg TMR_TRGOSOURCE_OC1,
 *                        @arg TMR_TRGOSOURCE_OC1REF
 *                        @arg TMR_TRGOSOURCE_OC2REF
 *                        @arg TMR_TRGOSOURCE_OC3REF
 *                        @arg TMR_TRGOSOURCE_OC4REF
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 *            TMR7 it's only for APM32F072 and APM32F091 devices
 */
void TMR_SelectOutputTrigger(TMR_T* TMRx, TMR_TRGOSOURCE_T source)
{
    TMRx->CTRL2_B.MMSEL = source;
}

/*!
 * @brief     Selects the Slave Mode.
 *
 * @param     TMRx: where x can be 1, 2, 3 and 15 select the TMR peripheral
 *
 * @param     mode: TMR_SLAVEMODE_T
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_SelectSlaveMode(TMR_T* TMRx, TMR_SLAVEMODE_T mode)
{
    TMRx->SMCTRL_B.SMFSEL = mode;
}

/*!
 * @brief     Enable the Master Slave Mode
 *
 * @param     TMRx: where x can be 1, 2, 3 and 15 select the TMR peripheral
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_EnableMasterSlaveMode(TMR_T* TMRx)
{
    TMRx->SMCTRL_B.MSMEN = ENABLE ;
}

/*!
 * @brief     Disable the Master Slave Mode
 *
 * @param     TMRx: where x can be 1, 2, 3 and 15 select the TMR peripheral
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_DisableMasterSlaveMode(TMR_T* TMRx)
{
    TMRx->SMCTRL_B.MSMEN = DISABLE ;
}

/*!
 * @brief     Configures the TMRx External Trigger (ETR)
 *
 * @param     TMRx: where x can be 1, 2, 3 select the TMR peripheral
 *
 * @param     prescaler: The external Trigger Prescaler
 *
 * @param     polarity: The external Trigger Polarity
 *
 * @param     filter: External Trigger Filter
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ConfigExternalTrigger(TMR_T* TMRx, TMR_EXTTRG_PRESCALER_T prescaler,
                               TMR_EXTTRG_POLARITY_T polarity, uint16_t filter)
{
    TMRx->SMCTRL &= 0x00FF;
    TMRx->SMCTRL_B.ETPCFG = prescaler;
    TMRx->SMCTRL_B.ETPOL = polarity;
    TMRx->SMCTRL_B.ETFCFG = filter;
}

/*!
 * @brief     Configures the Encoder Interface
 *
 * @param     TMRx: where x can be 1, 2, 3 select the TMR peripheral
 *
 * @param     encodeMode: specifies the Encoder Mode
 *
 * @param     IC1Polarity: specifies the IC1 Polarity
 *
 * @param     IC2Polarity: specifies the IC2 Polarity
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ConfigEncodeInterface(TMR_T* TMRx, TMR_ENCODER_MODE_T encodeMode, TMR_IC_POLARITY_T IC1Polarity,
                               TMR_IC_POLARITY_T IC2Polarity)
{
    /** Set the encoder Mode */
    TMRx->SMCTRL_B.SMFSEL = BIT_RESET;
    TMRx->SMCTRL_B.SMFSEL = encodeMode;

    /** Select the Capture Compare 1 and the Capture Compare 2 as input */
    TMRx->CCM1_INPUT_B.CC1SEL = BIT_RESET ;
    TMRx->CCM1_INPUT_B.CC2SEL = BIT_RESET ;
    TMRx->CCM1_INPUT_B.CC1SEL = BIT_SET ;
    TMRx->CCM1_INPUT_B.CC2SEL = BIT_SET ;

    /** Set the TI1 and the TI2 Polarities */
    TMRx->CCEN &= ~(TMR_IC_POLARITY_BOTHEDGE) & ~(TMR_IC_POLARITY_BOTHEDGE << 4);
    TMRx->CCEN |= (IC1Polarity | IC2Polarity << 4);
}

/*!
 * @brief     Enables Hall sensor interface.
 *
 * @param     TMRx: where x can be 1, 2, 3 select the TMR peripheral
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_EnableHallSensor(TMR_T* TMRx)
{
    TMRx->CTRL2_B.TI1SEL = ENABLE;
}

/*!
 * @brief     Disable Hall sensor interface.
 *
 * @param     TMRx: where x can be 1, 2, 3 select the TMR peripheral
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_DisableHallSensor(TMR_T* TMRx)
{
    TMRx->CTRL2_B.TI1SEL = DISABLE;
}

/*!
 * @brief     Configures the TMR14 Remapping input Capabilities.
 *
 * @param     TMRx: where x can only for 14 select the TMR peripheral
 *
 * @param     remap: specifies the TMR input reampping source
 *                    The parameter can be one of following values:
 *                        @arg TMR_REMAP_GPIO
 *                        @arg TMR_REMAP_RTC_CLK
 *                        @arg TMR_REMAP_HSEDiv32
 *                        @arg TMR_REMAP_MCO
 *
 * @retval    None
 *
 * @note      TMR2 it's not for APM32F030 devices
 */
void TMR_ConfigRemap(TMR_T* TMRx, TMR_REMAP_T remap)
{
    TMRx->OPT_B.RMPSEL = remap;
}

/**@} end of group TMR_Functions*/
/**@} end of group TMR_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver*/
