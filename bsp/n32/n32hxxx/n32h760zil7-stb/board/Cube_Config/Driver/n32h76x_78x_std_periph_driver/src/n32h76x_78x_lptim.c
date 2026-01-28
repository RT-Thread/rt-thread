/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_lptim.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_lptim.h"

/**
*\*\name    LPTIM_DeInit.
*\*\fun     Set LPTIMx registers to their reset values.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  none
**/
void LPTIM_DeInit(LPTIM_Module* LPTIMx)
{
    if (LPTIMx == LPTIM1)
    {
        /* Reset LPTIM1 */
        RCC_EnableRDPeriphReset1(RCC_RD_PERIPHRST_LPTIM1);
    }
    else if (LPTIMx == LPTIM2)
    {
        /* Reset LPTIM2 */
        RCC_EnableRDPeriphReset1(RCC_RD_PERIPHRST_LPTIM2);
    }
    else if (LPTIMx == LPTIM3)
    {
        /* Reset LPTIM3 */
        RCC_EnableRDPeriphReset1(RCC_RD_PERIPHRST_LPTIM3);
    }
    else if (LPTIMx == LPTIM4)
    {
        /* Reset LPTIM4 */
        RCC_EnableRDPeriphReset1(RCC_RD_PERIPHRST_LPTIM4);
    }
    else if (LPTIMx == LPTIM5)
    {
        /* Reset LPTIM5 */
        RCC_EnableRDPeriphReset1(RCC_RD_PERIPHRST_LPTIM5);
    }
    else
    {

    }
}

/**
*\*\name    LPTIM_StructInit.
*\*\fun     Set each fields of the LPTIM_InitStruct structure to its default value.
*\*\param   LPTIM_InitStruct:
*\*\          - Pointer to the LPTIM_InitType structure which will be initialized.
*\*\return  none
**/
void LPTIM_StructInit(LPTIM_InitType* LPTIM_InitStruct)
{
    /* Set the default configuration */
    LPTIM_InitStruct->ClockSource = LPTIM_CLK_SOURCE_INTERNAL;
    LPTIM_InitStruct->Prescaler   = LPTIM_PRESCALER_DIV1;
    LPTIM_InitStruct->Waveform    = LPTIM_OUTPUT_WAVEFORM_PWM;
    LPTIM_InitStruct->Polarity    = LPTIM_OUTPUT_POLARITY_REGULAR;
}

/**
*\*\name    LPTIM_Init.
*\*\fun     Configure the LPTIMx peripheral according to the specified parameters.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   LPTIM_InitStruct:
*\*\          - Pointer to a LPTIM_InitType structure.
*\*\return  SUCCESS or ERROR.
**/
ErrorStatus LPTIM_Init(LPTIM_Module* LPTIMx, LPTIM_InitType* LPTIM_InitStruct)
{
    ErrorStatus result = SUCCESS;

    /* The LPTIMx_CFG register must only be modified when the LPTIM is disabled
        (ENABLE bit is reset to 0).
    */
    if (LPTIM_IsEnabled(LPTIMx) == 1UL)
    {
        result = ERROR;
    }
    else
    {
        /* Set CLKSEL bitfield according to ClockSource value */
        /* Set CLKPRE bitfield according to Prescaler value */
        /* Set WAVE bitfield according to Waveform value */
        /* Set WAVEPOL bitfield according to Polarity value */
        MODIFY_REG(LPTIMx->CFG,
                   (LPTIM_CFG_CLKSEL | LPTIM_CFG_CLKPRE | LPTIM_CFG_WAVE | LPTIM_CFG_WAVEPOL),
                   LPTIM_InitStruct->ClockSource | \
                   LPTIM_InitStruct->Prescaler | \
                   LPTIM_InitStruct->Waveform | \
                   LPTIM_InitStruct->Polarity);
    }

    return result;
}

/**
*\*\name    LPTIM_Cmd.
*\*\fun     Enables or disables the specified LPTIM instance.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void LPTIM_Cmd(LPTIM_Module* LPTIMx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected LPTIM instance */
        SET_BIT(LPTIMx->CTRL, LPTIM_CTRL_LPTIMEN);
    }
    else
    {
        /* Disable the selected LPTIM instance */
        CLEAR_BIT(LPTIMx->CTRL, LPTIM_CTRL_LPTIMEN);
    }
}

/**
*\*\name    LPTIM_IsEnabled.
*\*\fun     Indicates whether the LPTIM instance is enabled.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  1 or 0
**/
uint32_t LPTIM_IsEnabled(LPTIM_Module* LPTIMx)
{
    uint32_t Temp;

    /* Read the corresponding bit, set 1 to return 1, otherwise, return 0 */
    Temp = (((READ_BIT(LPTIMx->CTRL, LPTIM_CTRL_LPTIMEN) == LPTIM_CTRL_LPTIMEN) ? 1UL : 0UL));

    return Temp;
}

/**
*\*\name    LPTIM_StartCounter.
*\*\fun     Starts the LPTIM counter in the desired mode.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   OperatingMode (The input parameters must be the following values):
*\*\          - LPTIM_OPERATING_MODE_CONTINUOUS
*\*\          - LPTIM_OPERATING_MODE_ONESHOT
*\*\return  none
*\*\note    LPTIM instance must be enabled before starting the counter.
**/
void LPTIM_StartCounter(LPTIM_Module* LPTIMx, uint32_t OperatingMode)
{
    MODIFY_REG(LPTIMx->CTRL, LPTIM_CTRL_TSTCM | LPTIM_CTRL_SNGMST, OperatingMode);
}

/**
*\*\name    LPTIM_SetUpdateMode.
*\*\fun     Set the LPTIM registers update mode (enable/disable register preload).
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   UpdateMode (The input parameters must be the following values):
*\*\          - LPTIM_UPDATE_MODE_IMMEDIATE
*\*\          - LPTIM_UPDATE_MODE_ENDOFPERIOD
*\*\return  none
*\*\note    This function must be called when the LPTIM instance is disabled.
**/
void LPTIM_SetUpdateMode(LPTIM_Module* LPTIMx, uint32_t UpdateMode)
{
    MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_RELOAD, UpdateMode);
}

/**
*\*\name    LPTIM_GetUpdateMode.
*\*\fun     Get the LPTIM registers update mode.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  LPTIM_UPDATE_MODE_IMMEDIATE or LPTIM_UPDATE_MODE_ENDOFPERIOD
**/
uint32_t LPTIM_GetUpdateMode(LPTIM_Module* LPTIMx)
{
    uint32_t Mode;

    /* Read the corresponding bit */
    Mode = (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_RELOAD));

    return Mode;
}

/**
*\*\name    LPTIM_SetAutoReloadValue.
*\*\fun     Set the auto reload value.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   AutoReload:
*\*\          - Value between Min_Data=0x00 and Max_Data=0xFFFF
*\*\return  none
*\*\note    The LPTIMx_ARR register content must only be modified when the LPTIM
*\*\        is enabled.
*\*\note    After a write to the LPTIMx_ARR register a new write operation to the
*\*\        same register can only be performed when the previous write operation
*\*\        is completed. Any successive write before the ARRUPD flag be set, will
*\*\        lead to unpredictable results.
**/
void LPTIM_SetAutoReloadValue(LPTIM_Module* LPTIMx, uint32_t AutoReload)
{
    MODIFY_REG(LPTIMx->ARR, LPTIM_ARR_ARRVAL, AutoReload);
}

/**
*\*\name    LPTIM_GetAutoReloadValue.
*\*\fun     Get actual auto reload value.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  AutoReload Value between Min_Data=0x00 and Max_Data=0xFFFF
**/
uint32_t LPTIM_GetAutoReloadValue(LPTIM_Module* LPTIMx)
{
    uint32_t Value;

    /* Read the corresponding bit */
    Value = (uint32_t)(READ_BIT(LPTIMx->ARR, LPTIM_ARR_ARRVAL));

    return Value;
}

/**
*\*\name    LPTIM_SetCompareValue.
*\*\fun     Set the compare value.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   CompareValue:
*\*\          - Value between Min_Data=0x00 and Max_Data=0xFFFF
*\*\return  none
*\*\note    After a write to the LPTIMx_CMP register a new write operation to the
*\*\        same register can only be performed when the previous write operation
*\*\        is completed. Any successive write before the CMPUPD flag be set, will
*\*\        lead to unpredictable results.
**/
void LPTIM_SetCompareValue(LPTIM_Module* LPTIMx, uint32_t CompareValue)
{
    MODIFY_REG(LPTIMx->CMP, LPTIM_CMP_CMPVAL, CompareValue);
}

/**
*\*\name    LPTIM_GetCompareValue.
*\*\fun     Get actual compare value.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  CompareValue Value between Min_Data=0x00 and Max_Data=0xFFFF
**/
uint32_t LPTIM_GetCompareValue(LPTIM_Module* LPTIMx)
{
    uint32_t Value;

    /* Read the corresponding bit */
    Value = (uint32_t)(READ_BIT(LPTIMx->CMP, LPTIM_CMP_CMPVAL));

    return Value;
}

/**
*\*\name    LPTIM_GetCounterValue.
*\*\fun     Get actual counter value.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  Counter value
*\*\note    When the LPTIM instance is running with an asynchronous clock, reading
*\*\        the LPTIMx_CNT register may return unreliable values. So in this case it
*\*\        is necessary to perform two consecutive read accesses and verify that the
*\*\        two returned values are identical.
**/
uint32_t LPTIM_GetCounterValue(LPTIM_Module* LPTIMx)
{
    uint32_t Value;

    /* Read the corresponding bit */
    Value = (uint32_t)(READ_BIT(LPTIMx->CNT, LPTIM_CNT_CNTVAL));

    return Value;
}

/**
*\*\name    LPTIM_SetCounterMode.
*\*\fun     Set the counter mode (selection of the LPTIM counter clock source).
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   CounterMode (The input parameters must be the following values):
*\*\          - LPTIM_COUNTER_MODE_INTERNAL
*\*\          - LPTIM_COUNTER_MODE_EXTERNAL
*\*\return  none
*\*\note    The counter mode can be set only when the LPTIM instance is disabled.
**/
void LPTIM_SetCounterMode(LPTIM_Module* LPTIMx, uint32_t CounterMode)
{
    MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_CNTMEN, CounterMode);
}

/**
*\*\name    LPTIM_GetCounterMode.
*\*\fun     Get the counter mode.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  LPTIM_COUNTER_MODE_INTERNAL or LPTIM_COUNTER_MODE_EXTERNAL
**/
uint32_t LPTIM_GetCounterMode(LPTIM_Module* LPTIMx)
{
    uint32_t Mode;

    /* Read the corresponding bit */
    Mode = (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_CNTMEN));

    return Mode;
}

/**
*\*\name    LPTIM_ConfigOutput.
*\*\fun     Configure the LPTIM instance output.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   Waveform (The input parameters must be the following values):
*\*\          - LPTIM_OUTPUT_WAVEFORM_PWM
*\*\          - LPTIM_OUTPUT_WAVEFORM_SETONCE
*\*\param   Polarity (The input parameters must be the following values):
*\*\          - LPTIM_OUTPUT_POLARITY_REGULAR
*\*\          - LPTIM_OUTPUT_POLARITY_INVERSE
*\*\return  none
*\*\note    This function must be called when the LPTIM instance is disabled.
*\*\note    Regarding the LPTIM output polarity the change takes effect immediately,
*\*\        so the output default value will change immediately after the polarity
*\*\        is re-configured, even before the timer is enabled.
**/
void LPTIM_ConfigOutput(LPTIM_Module* LPTIMx, uint32_t Waveform, uint32_t Polarity)
{
    MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_WAVE | LPTIM_CFG_WAVEPOL, Waveform | Polarity);
}

/**
*\*\name    LPTIM_SetWaveform.
*\*\fun     Set waveform shape.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   Waveform (The input parameters must be the following values):
*\*\          - LPTIM_OUTPUT_WAVEFORM_PWM
*\*\          - LPTIM_OUTPUT_WAVEFORM_SETONCE
*\*\return  none
**/
void LPTIM_SetWaveform(LPTIM_Module* LPTIMx, uint32_t Waveform)
{
    MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_WAVE, Waveform);
}

/**
*\*\name    LPTIM_GetWaveform.
*\*\fun     Get actual waveform shape.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  LPTIM_OUTPUT_WAVEFORM_PWM or LPTIM_OUTPUT_WAVEFORM_SETONCE
**/
uint32_t LPTIM_GetWaveform(LPTIM_Module* LPTIMx)
{
    uint32_t Waveform;

    /* Read the corresponding bit */
    Waveform = (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_WAVE));

    return Waveform;
}

/**
*\*\name    LPTIM_SetPolarity.
*\*\fun     Set output polarity.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   Polarity (The input parameters must be the following values):
*\*\          - LPTIM_OUTPUT_POLARITY_REGULAR
*\*\          - LPTIM_OUTPUT_POLARITY_INVERSE
*\*\return  none
**/
void LPTIM_SetPolarity(LPTIM_Module* LPTIMx, uint32_t Polarity)
{
    MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_WAVEPOL, Polarity);
}

/**
*\*\name    LPTIM_GetPolarity.
*\*\fun     Get actual output polarity.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  LPTIM_OUTPUT_POLARITY_REGULAR or LPTIM_OUTPUT_POLARITY_INVERSE
**/
uint32_t LPTIM_GetPolarity(LPTIM_Module* LPTIMx)
{
    uint32_t Polarity;

    /* Read the corresponding bit */
    Polarity = (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_WAVEPOL));

    return Polarity;
}

/**
*\*\name    LPTIM_SetPrescaler.
*\*\fun     Set actual prescaler division ratio.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   Prescaler (The input parameters must be the following values):
*\*\          - LPTIM_PRESCALER_DIV1
*\*\          - LPTIM_PRESCALER_DIV2
*\*\          - LPTIM_PRESCALER_DIV4
*\*\          - LPTIM_PRESCALER_DIV8
*\*\          - LPTIM_PRESCALER_DIV16
*\*\          - LPTIM_PRESCALER_DIV32
*\*\          - LPTIM_PRESCALER_DIV64
*\*\          - LPTIM_PRESCALER_DIV128
*\*\return  none
*\*\note    This function must be called when the LPTIM instance is disabled.
*\*\note    When the LPTIM is configured to be clocked by an internal clock
*\*\        source and the LPTIM counter is configured to be updated by active
*\*\        edges detected on the LPTIM external Input1, the internal clock
*\*\        provided to the LPTIM must not be prescaled.
**/
void LPTIM_SetPrescaler(LPTIM_Module* LPTIMx, uint32_t Prescaler)
{
    MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_CLKPRE, Prescaler);
}

/**
*\*\name    LPTIM_GetPrescaler.
*\*\fun     Get actual prescaler division ratio.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  Returned value can be one of the following values:
*\*\          - LPTIM_PRESCALER_DIV1
*\*\          - LPTIM_PRESCALER_DIV2
*\*\          - LPTIM_PRESCALER_DIV4
*\*\          - LPTIM_PRESCALER_DIV8
*\*\          - LPTIM_PRESCALER_DIV16
*\*\          - LPTIM_PRESCALER_DIV32
*\*\          - LPTIM_PRESCALER_DIV64
*\*\          - LPTIM_PRESCALER_DIV128
**/
uint32_t LPTIM_GetPrescaler(LPTIM_Module* LPTIMx)
{
    uint32_t Prescaler;

    /* Read the corresponding bit */
    Prescaler = (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_CLKPRE));

    return Prescaler;
}

/**
*\*\name    LPTIM_TimeoutCmd.
*\*\fun     Enables or disables the LPTIM timeout function.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    This function must be called when the LPTIM instance is disabled.
*\*\note    The first trigger event will start the timer, any successive trigger
*\*\        event will reset the counter and the timer will restart.
*\*\note    The timeout value corresponds to the compare value; if no trigger
*\*\        occurs within the expected time frame, the MCU is waked-up by the
*\*\        compare match event.
*\*\note    A trigger event arriving when the timer is already started will be
*\*\        ignored.
**/
void LPTIM_TimeoutCmd(LPTIM_Module* LPTIMx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the LPTIM timeout function */
        SET_BIT(LPTIMx->CFG, LPTIM_CFG_TIMOUTEN);
    }
    else
    {
        /* Disable the LPTIM timeout function */
        CLEAR_BIT(LPTIMx->CFG, LPTIM_CFG_TIMOUTEN);
    }
}

/**
*\*\name    LPTIM_IsEnabledTimeout.
*\*\fun     Indicate whether the timeout function is enabled.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  1 or 0
**/
uint32_t LPTIM_IsEnabledTimeout(LPTIM_Module* LPTIMx)
{
    uint32_t Temp;

    /* Read the corresponding bit, set 1 to return 1, otherwise, return 0 */
    Temp = (((READ_BIT(LPTIMx->CFG, LPTIM_CFG_TIMOUTEN) == LPTIM_CFG_TIMOUTEN) ? 1UL : 0UL));

    return Temp;
}

/**
*\*\name    LPTIM_SoftwareTrigger.
*\*\fun     Configure the Software trigger.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  none
**/
void LPTIM_SoftwareTrigger(LPTIM_Module* LPTIMx)
{
    CLEAR_BIT(LPTIMx->CFG, LPTIM_CFG_TRGEN);
}

/**
*\*\name    LPTIM_ConfigTrigger.
*\*\fun     Configure the external trigger used as a trigger event for the LPTIM.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   Source (The input parameters must be the following values):
*\*\          - LPTIM_TRIG_SOURCE_GPIO
*\*\          - LPTIM_TRIG_SOURCE_RTCALARMA
*\*\          - LPTIM_TRIG_SOURCE_RTCALARMB
*\*\          - LPTIM_TRIG_SOURCE_RTCTAMP1
*\*\          - LPTIM_TRIG_SOURCE_RTCTAMP2
*\*\          - LPTIM_TRIG_SOURCE_RTCTAMP3
*\*\          - LPTIM_TRIG_SOURCE_COMP1
*\*\          - LPTIM_TRIG_SOURCE_COMP2
*\*\          - LPTIM_TRIG_SOURCE_COMP3
*\*\          - LPTIM_TRIG_SOURCE_COMP4
*\*\param   Filter (The input parameters must be the following values):
*\*\          - LPTIM_TRIG_FILTER_NONE
*\*\          - LPTIM_TRIG_FILTER_2
*\*\          - LPTIM_TRIG_FILTER_4
*\*\          - LPTIM_TRIG_FILTER_8
*\*\param   Polarity (The input parameters must be the following values):
*\*\          - LPTIM_TRIG_POLARITY_RISING
*\*\          - LPTIM_TRIG_POLARITY_FALLING
*\*\          - LPTIM_TRIG_POLARITY_RISING_FALLING
*\*\return  none
*\*\note    This function must be called when the LPTIM instance is disabled.
*\*\note    An internal clock source must be present when a digital filter is
*\*\        required for the trigger.
**/
void LPTIM_ConfigTrigger(LPTIM_Module* LPTIMx, uint32_t Source, uint32_t Filter, uint32_t Polarity)
{
    MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_TRGSEL | LPTIM_CFG_TRIGFLT | LPTIM_CFG_TRGEN, Source | Filter | Polarity);
}

/**
*\*\name    LPTIM_GetTriggerSource.
*\*\fun     Get actual external trigger source.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  Returned value can be one of the following values:
*\*\          - LPTIM_TRIG_SOURCE_GPIO
*\*\          - LPTIM_TRIG_SOURCE_RTCALARMA
*\*\          - LPTIM_TRIG_SOURCE_RTCALARMB
*\*\          - LPTIM_TRIG_SOURCE_RTCTAMP1
*\*\          - LPTIM_TRIG_SOURCE_RTCTAMP2
*\*\          - LPTIM_TRIG_SOURCE_RTCTAMP3
*\*\          - LPTIM_TRIG_SOURCE_COMP1
*\*\          - LPTIM_TRIG_SOURCE_COMP2
*\*\          - LPTIM_TRIG_SOURCE_COMP3
*\*\          - LPTIM_TRIG_SOURCE_COMP4
**/
uint32_t LPTIM_GetTriggerSource(LPTIM_Module* LPTIMx)
{
    uint32_t Source;

    /* Read the corresponding bit */
    Source = (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_TRGSEL));

    return Source;
}

/**
*\*\name    LPTIM_GetTriggerFilter.
*\*\fun     Get actual external trigger filter.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  Returned value can be one of the following values:
*\*\          - LPTIM_TRIG_FILTER_NONE
*\*\          - LPTIM_TRIG_FILTER_2
*\*\          - LPTIM_TRIG_FILTER_4
*\*\          - LPTIM_TRIG_FILTER_8
**/
uint32_t LPTIM_GetTriggerFilter(LPTIM_Module* LPTIMx)
{
    uint32_t Filter;

    /* Read the corresponding bit */
    Filter = (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_TRIGFLT));

    return Filter;
}

/**
*\*\name    LPTIM_GetTriggerPolarity.
*\*\fun     Get actual external trigger polarity.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  Returned value can be one of the following values:
*\*\          - LPTIM_TRIG_POLARITY_RISING
*\*\          - LPTIM_TRIG_POLARITY_FALLING
*\*\          - LPTIM_TRIG_POLARITY_RISING_FALLING
**/
uint32_t LPTIM_GetTriggerPolarity(LPTIM_Module* LPTIMx)
{
    uint32_t Polarity;

    /* Read the corresponding bit */
    Polarity = (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_TRGEN));

    return Polarity;
}

/**
*\*\name    LPTIM_SetClockSource.
*\*\fun     Set the source of the clock used by the LPTIM instance.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   ClockSource (The input parameters must be the following values):
*\*\          - LPTIM_CLK_SOURCE_INTERNAL
*\*\          - LPTIM_CLK_SOURCE_EXTERNAL
*\*\return  none
*\*\note    This function must be called when the LPTIM instance is disabled.
**/
void LPTIM_SetClockSource(LPTIM_Module* LPTIMx, uint32_t ClockSource)
{
    MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_CLKSEL, ClockSource);
}

/**
*\*\name    LPTIM_GetClockSource.
*\*\fun     Get actual LPTIM instance clock source.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  Returned value can be one of the following values:
*\*\          - LPTIM_CLK_SOURCE_INTERNAL
*\*\          - LPTIM_CLK_SOURCE_EXTERNAL
**/
uint32_t LPTIM_GetClockSource(LPTIM_Module* LPTIMx)
{
    uint32_t Source;

    /* Read the corresponding bit */
    Source = (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_CLKSEL));

    return Source;
}

/**
*\*\name    LPTIM_ConfigClock.
*\*\fun     Configure the active edge or edges used by the counter when the
*\*\        LPTIM is clocked by an external clock source.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   ClockFilter (The input parameters must be the following values):
*\*\          - LPTIM_CLK_FILTER_NONE
*\*\          - LPTIM_CLK_FILTER_2
*\*\          - LPTIM_CLK_FILTER_4
*\*\          - LPTIM_CLK_FILTER_8
*\*\param   ClockPolarity (The input parameters must be the following values):
*\*\          - LPTIM_CLK_POLARITY_RISING
*\*\          - LPTIM_CLK_POLARITY_FALLING
*\*\          - LPTIM_CLK_POLARITY_RISING_FALLING
*\*\          - LPTIM_CLK_POLARITY_RISING_FALLING_NO
*\*\return  none
*\*\note    This function must be called when the LPTIM instance is disabled.
*\*\note    When both external clock signal edges are considered active ones,
*\*\        the LPTIM must also be clocked by an internal clock source with a
*\*\        frequency equal to at least four times the external clock frequency.
*\*\note    An internal clock source must be present when a digital filter is
*\*\        required for external clock.
**/
void LPTIM_ConfigClock(LPTIM_Module* LPTIMx, uint32_t ClockFilter, uint32_t ClockPolarity)
{
    MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_CLKFLT | LPTIM_CFG_CLKPOL, ClockFilter | ClockPolarity);
}

/**
*\*\name    LPTIM_GetClockPolarity.
*\*\fun     Get actual clock polarity.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  Returned value can be one of the following values:
*\*\          - LPTIM_CLK_POLARITY_RISING
*\*\          - LPTIM_CLK_POLARITY_FALLING
*\*\          - LPTIM_CLK_POLARITY_RISING_FALLING
*\*\          - LPTIM_CLK_POLARITY_RISING_FALLING_NO
**/
uint32_t LPTIM_GetClockPolarity(LPTIM_Module* LPTIMx)
{
    uint32_t Polarity;

    /* Read the corresponding bit */
    Polarity = (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_CLKPOL));

    return Polarity;
}

/**
*\*\name    LPTIM_GetClockFilter.
*\*\fun     Get actual clock digital filter.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  Returned value can be one of the following values:
*\*\          - LPTIM_CLK_FILTER_NONE
*\*\          - LPTIM_CLK_FILTER_2
*\*\          - LPTIM_CLK_FILTER_4
*\*\          - LPTIM_CLK_FILTER_8
**/
uint32_t LPTIM_GetClockFilter(LPTIM_Module* LPTIMx)
{
    uint32_t Filter;

    /* Read the corresponding bit */
    Filter = (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_CLKFLT));

    return Filter;
}

/**
*\*\name    LPTIM_SetEncoderModeClockPolarity.
*\*\fun     Configure clock polarity in encoder mode.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   ClockPolarity (The input parameters must be the following values):
*\*\          - LPTIM_ENCODER_MODE_RISING
*\*\          - LPTIM_ENCODER_MODE_FALLING
*\*\          - LPTIM_ENCODER_MODE_RISING_FALLING
*\*\return  none
*\*\note    This function must be called when the LPTIM instance is disabled.
**/
void LPTIM_SetEncoderModeClockPolarity(LPTIM_Module* LPTIMx, uint32_t ClockPolarity)
{
    MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_CLKPOL, ClockPolarity);
}

/**
*\*\name    LPTIM_GetEncoderModeClockPolarity.
*\*\fun     Get clock polarity in encoder mode.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  Returned value can be one of the following values:
*\*\          - LPTIM_ENCODER_MODE_RISING
*\*\          - LPTIM_ENCODER_MODE_FALLING
*\*\          - LPTIM_ENCODER_MODE_RISING_FALLING
**/
uint32_t LPTIM_GetEncoderModeClockPolarity(LPTIM_Module* LPTIMx)
{
    uint32_t Mode;

    /* Read the corresponding bit */
    Mode = (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_CLKPOL));

    return Mode;
}

/**
*\*\name    LPTIM_EncoderModeCmd.
*\*\fun     Enables or disables the encoder mode.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    This function must be called when the LPTIM instance is disabled.
*\*\note    In this mode the LPTIM instance must be clocked by an internal clock
*\*\        source. Also, the prescaler division ratio must be equal to 1.
*\*\note    LPTIM instance must be configured in continuous mode prior enabling
*\*\        the encoder mode.
**/
void LPTIM_EncoderModeCmd(LPTIM_Module* LPTIMx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the encoder mode */
        SET_BIT(LPTIMx->CFG, LPTIM_CFG_ENC);
    }
    else
    {
        /* Disable the encoder mode */
        CLEAR_BIT(LPTIMx->CFG, LPTIM_CFG_ENC);
    }
}

/**
*\*\name    LPTIM_NoEncoderModeCmd.
*\*\fun     Enables or disables the Non-encoder mode.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    This function must be called when the LPTIM instance is disabled.
*\*\note    In this mode the LPTIM instance must be clocked by an internal clock
*\*\        source. Also, the prescaler division ratio must be equal to 1.
*\*\note    LPTIM instance must be configured in continuous mode prior enabling
*\*\        the encoder mode.
**/
void LPTIM_NoEncoderModeCmd(LPTIM_Module* LPTIMx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the Non-encoder mode */
        SET_BIT(LPTIMx->CFG, LPTIM_CFG_NENC);
    }
    else
    {
        /* Disable the Non-encoder mode */
        CLEAR_BIT(LPTIMx->CFG, LPTIM_CFG_NENC);
    }
}

/**
*\*\name    LPTIM_IsEnabledEncoderMode.
*\*\fun     Indicates whether the LPTIM operates in encoder mode.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  1 or 0
**/
uint32_t LPTIM_IsEnabledEncoderMode(LPTIM_Module* LPTIMx)
{
    uint32_t Temp;

    /* Read the corresponding bit, set 1 to return 1, otherwise, return 0 */
    Temp = (((READ_BIT(LPTIMx->CFG, LPTIM_CFG_ENC) == LPTIM_CFG_ENC) ? 1UL : 0UL));

    return Temp;
}

/**
*\*\name    LPTIM_IsEnabledNoEncoderMode.
*\*\fun     Indicates whether the LPTIM operates in Non-encoder mode.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\return  1 or 0
**/
uint32_t LPTIM_IsEnabledNoEncoderMode(LPTIM_Module* LPTIMx)
{
    uint32_t Temp;

    /* Read the corresponding bit, set 1 to return 1, otherwise, return 0 */
    Temp = (((READ_BIT(LPTIMx->CFG, LPTIM_CFG_NENC) == LPTIM_CFG_NENC) ? 1UL : 0UL));

    return Temp;
}

/**
*\*\name    LPTIM_ClearIntFlag.
*\*\fun     Clear the specified LPTIM Interrupt status flags.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   IntFlag (The input parameters must be the following values):
*\*\          - LPTIM_COMP_MATCH_FLAG
*\*\          - LPTIM_AUTO_RELOAD_FLAG
*\*\          - LPTIM_EXT_TRIG_EDGE_EVENT_FLAG
*\*\          - LPTIM_COMP_UPDATE_FLAG
*\*\          - LPTIM_AUTO_RELOAD_UPDATE_FLAG
*\*\          - LPTIM_COUNTER_DIR_UP_FLAG
*\*\          - LPTIM_COUNTER_DIR_DOWN_FLAG
*\*\return  none
**/
void LPTIM_ClearIntFlag(LPTIM_Module* LPTIMx, uint32_t IntFlag)
{
    SET_BIT(LPTIMx->INTCLR, IntFlag);
}

/**
*\*\name    LPTIM_IsActiveIntStatus.
*\*\fun     Inform application whether the specified LPTIM interrupt has occurred.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   IntSts (The input parameters must be the following values):
*\*\          - LPTIM_COMP_MATCH_STATUS
*\*\          - LPTIM_AUTO_RELOAD_STATUS
*\*\          - LPTIM_EXT_TRIG_EDGE_EVENT_STATUS
*\*\          - LPTIM_COMP_UPDATE_STATUS
*\*\          - LPTIM_AUTO_RELOAD_UPDATE_STATUS
*\*\          - LPTIM_COUNTER_DIR_UP_STATUS
*\*\          - LPTIM_COUNTER_DIR_DOWN_STATUS
*\*\return  1 or 0
**/
uint32_t LPTIM_IsActiveIntStatus(LPTIM_Module* LPTIMx, uint32_t IntSts)
{
    uint32_t Temp;

    /* Read the corresponding bit, set 1 to return 1, otherwise, return 0 */
    Temp = (((READ_BIT(LPTIMx->INTSTS, IntSts) == IntSts) ? 1UL : 0UL));

    return Temp;
}

/**
*\*\name    LPTIM_ConfigInt.
*\*\fun     Enables or disables the specified LPTIM interrupts.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   Interrupt (The input parameters must be the following values):
*\*\          - LPTIM_COMP_MATCH_INT
*\*\          - LPTIM_AUTO_RELOAD_INT
*\*\          - LPTIM_EXT_TRIG_EDGE_EVENT_INT
*\*\          - LPTIM_COMP_UPDATE_INT
*\*\          - LPTIM_AUTO_RELOAD_UPDATE_INT
*\*\          - LPTIM_COUNTER_DIR_UP_INT
*\*\          - LPTIM_COUNTER_DIR_DOWN_INT
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    This function must be called when the LPTIM instance is disabled.
**/
void LPTIM_ConfigInt(LPTIM_Module* LPTIMx, uint32_t Interrupt, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        SET_BIT(LPTIMx->INTEN, Interrupt);
    }
    else
    {
        CLEAR_BIT(LPTIMx->INTEN, Interrupt);
    }
}

/**
*\*\name    LPTIM_IsEnabledInt.
*\*\fun     Indicates whether the specified LPTIM interrupts is enabled.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   Interrupt (The input parameters must be the following values):
*\*\          - LPTIM_COMP_MATCH_INT
*\*\          - LPTIM_AUTO_RELOAD_INT
*\*\          - LPTIM_EXT_TRIG_EDGE_EVENT_INT
*\*\          - LPTIM_COMP_UPDATE_INT
*\*\          - LPTIM_AUTO_RELOAD_UPDATE_INT
*\*\          - LPTIM_COUNTER_DIR_UP_INT
*\*\          - LPTIM_COUNTER_DIR_DOWN_INT
*\*\return  1 or 0
**/
uint32_t LPTIM_IsEnabledInt(LPTIM_Module* LPTIMx, uint32_t Interrupt)
{
    uint32_t Temp;

    /* Read the corresponding bit, set 1 to return 1, otherwise, return 0 */
    Temp = (((READ_BIT(LPTIMx->INTEN, Interrupt) == Interrupt) ? 1UL : 0UL));

    return Temp;
}

/**
*\*\name    LPTIM_ConfigInput1.
*\*\fun     Select the connection for Input1 of LPTIM.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   ConnectSelect (The input parameters must be the following values):
*\*\          - LPTIM_INPUT1_CONNECT_GPIO
*\*\          - LPTIM_INPUT1_CONNECT_COMP1
*\*\          - LPTIM_INPUT1_CONNECT_COMP2
*\*\          - LPTIM_INPUT1_CONNECT_COMP3
*\*\          - LPTIM_INPUT1_CONNECT_COMP4
*\*\return  none
**/
void LPTIM_ConfigInput1(LPTIM_Module* LPTIMx, uint32_t ConnectSelect)
{
    MODIFY_REG(LPTIMx->OPT, LPTIM_OPT_OPT1, ConnectSelect);
}

/**
*\*\name    LPTIM_ConfigInput2.
*\*\fun     Select the connection for Input2 of LPTIM.
*\*\param   LPTIMx (The input parameters must be the following values):
*\*\          - LPTIM1
*\*\          - LPTIM2
*\*\          - LPTIM3
*\*\          - LPTIM4
*\*\          - LPTIM5
*\*\param   ConnectSelect (The input parameters must be the following values):
*\*\          - LPTIM_INPUT2_CONNECT_GPIO
*\*\          - LPTIM_INPUT2_CONNECT_COMP1
*\*\          - LPTIM_INPUT2_CONNECT_COMP2
*\*\          - LPTIM_INPUT2_CONNECT_COMP3
*\*\          - LPTIM_INPUT2_CONNECT_COMP4
*\*\return  none
**/
void LPTIM_ConfigInput2(LPTIM_Module* LPTIMx, uint32_t ConnectSelect)
{
    MODIFY_REG(LPTIMx->OPT, LPTIM_OPT_OPT2, ConnectSelect);
}



