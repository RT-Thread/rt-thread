/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#include "fsl_sim_hal.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * APIs
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_SetOutDiv
 * Description   : Set all clock out dividers setting at the same time
 * This function will set the setting for all clock out dividers.
 *
 *END**************************************************************************/
void CLOCK_HAL_SetOutDiv(SIM_Type * base,
                         uint8_t outdiv1,
                         uint8_t outdiv2, 
                         uint8_t outdiv3,
                         uint8_t outdiv4)
{
    uint32_t clkdiv1 = 0;
    
    clkdiv1 |= SIM_CLKDIV1_OUTDIV1(outdiv1);
    clkdiv1 |= SIM_CLKDIV1_OUTDIV4(outdiv4);
    
    SIM_WR_CLKDIV1(base, clkdiv1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetOutDiv
 * Description   : Get all clock out dividers setting at the same time
 * This function will get the setting for all clock out dividers.
 *
 *END**************************************************************************/
void CLOCK_HAL_GetOutDiv(SIM_Type * base,
                         uint8_t *outdiv1,
                         uint8_t *outdiv2,
                         uint8_t *outdiv3,
                         uint8_t *outdiv4)
{
    *outdiv1 = SIM_BRD_CLKDIV1_OUTDIV1(base);
    *outdiv2 = 0U;
    *outdiv3 = 0U;
    *outdiv4 = SIM_BRD_CLKDIV1_OUTDIV4(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetAdcAlternativeTriggerCmd
 * Description   : Set ADCx alternate trigger enable setting
 * This function will enable/disable alternative conversion triggers for ADCx. 
 * 
 *END**************************************************************************/
void SIM_HAL_SetAdcAlternativeTriggerCmd(SIM_Type * base, uint32_t instance, bool enable)
{
    assert(instance < ADC_INSTANCE_COUNT);

    SIM_BWR_SOPT7_ADC0ALTTRGEN(base, enable ? 1 : 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetAdcAlternativeTriggerCmd
 * Description   : Get ADCx alternate trigger enable settingg
 * This function will get ADCx alternate trigger enable setting. 
 * 
 *END**************************************************************************/
bool SIM_HAL_GetAdcAlternativeTriggerCmd(SIM_Type * base, uint32_t instance)
{
    bool retValue = false;

    assert(instance < ADC_INSTANCE_COUNT);
    retValue = SIM_BRD_SOPT7_ADC0ALTTRGEN(base);

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetAdcPreTriggerMode
 * Description   : Set ADCx pre-trigger select setting
 * This function will select the ADCx pre-trigger source when alternative
 * triggers are enabled through ADCxALTTRGEN
 * 
 *END**************************************************************************/
void SIM_HAL_SetAdcPreTriggerMode(SIM_Type * base, uint32_t instance, sim_adc_pretrg_sel_t select)
{
    assert(instance < ADC_INSTANCE_COUNT);
    SIM_BWR_SOPT7_ADC0PRETRGSEL(base, select);

}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetAdcPreTriggerMode
 * Description   : Get ADCx pre-trigger select setting
 * This function will get ADCx pre-trigger select setting.
 * 
 *END**************************************************************************/
sim_adc_pretrg_sel_t SIM_HAL_GetAdcPreTriggerMode(SIM_Type * base, uint32_t instance)
{
    sim_adc_pretrg_sel_t retValue = (sim_adc_pretrg_sel_t)0;

    assert(instance < ADC_INSTANCE_COUNT);
    retValue = (sim_adc_pretrg_sel_t)SIM_BRD_SOPT7_ADC0PRETRGSEL(base);

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetAdcTriggerMode
 * Description   : Set ADCx trigger select setting
 * This function will select the ADCx trigger source when alternative triggers
 * are enabled through ADCxALTTRGEN
 * 
 *END**************************************************************************/
void SIM_HAL_SetAdcTriggerMode(SIM_Type * base,
                               uint32_t instance,
                               sim_adc_trg_sel_t select)
{
    assert(instance < ADC_INSTANCE_COUNT);
    SIM_BWR_SOPT7_ADC0TRGSEL(base, select);

}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetAdcTriggerMode
 * Description   : Get ADCx trigger select setting 
 * This function will get ADCx trigger select setting.
 * 
 *END**************************************************************************/
sim_adc_trg_sel_t SIM_HAL_GetAdcTriggerMode(SIM_Type * base, uint32_t instance)
{
    sim_adc_trg_sel_t retValue =(sim_adc_trg_sel_t)0;

    assert(instance < ADC_INSTANCE_COUNT);
    retValue = (sim_adc_trg_sel_t)SIM_BRD_SOPT7_ADC0TRGSEL(base);

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetAdcTriggerModeOneStep
 * Description   : Set ADCx trigger setting.
 * This function sets ADC alternate trigger, pre-trigger mode and trigger mode.
 *
 *END**************************************************************************/
void SIM_HAL_SetAdcTriggerModeOneStep(SIM_Type * base,
                                      uint32_t instance,
                                      bool    altTrigEn,
                                      sim_adc_pretrg_sel_t preTrigSel,
                                      sim_adc_trg_sel_t trigSel)
{
    assert(instance < ADC_INSTANCE_COUNT);

    SIM_BWR_SOPT7_ADC0ALTTRGEN(base, altTrigEn ? 1 : 0);
    SIM_BWR_SOPT7_ADC0PRETRGSEL(base, preTrigSel);

    if (altTrigEn)
    {
        SIM_BWR_SOPT7_ADC0TRGSEL(base, trigSel);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetUartOpenDrainCmd
 * Description   : Set UARTx Open Drain Enable setting 
 * This function will enable/disable the UARTx Open Drain.
 * 
 *END**************************************************************************/
void SIM_HAL_SetUartOpenDrainCmd(SIM_Type * base, uint32_t instance, bool enable)
{
    assert(instance < FSL_FEATURE_SIM_OPT_UART_COUNT);

    switch (instance)
    {
    case 1:
        SIM_BWR_SOPT5_UART1ODE(base, enable ? 1 : 0);
        break;
    case 2:
        SIM_BWR_SOPT5_UART2ODE(base, enable ? 1 : 0);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetUartOpenDrainCmd
 * Description   : Get UARTx Open Drain Enable setting 
 * This function will get UARTx Open Drain Enable setting.
 * 
 *END**************************************************************************/
bool SIM_HAL_GetUartOpenDrainCmd(SIM_Type * base, uint32_t instance)
{
    bool retValue = false;

    assert(instance < FSL_FEATURE_SIM_OPT_UART_COUNT);

    switch (instance)
    {
    case 1:
        retValue = SIM_BRD_SOPT5_UART1ODE(base);
        break;
    case 2:
        retValue = SIM_BRD_SOPT5_UART2ODE(base);
        break;
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetTpmExternalClkPinSelMode
 * Description   : Set Timer/PWM x external clock pin select setting 
 * This function will select the source of Timer/PWM x external clock pin select
 * 
 *END**************************************************************************/
void SIM_HAL_SetTpmExternalClkPinSelMode(SIM_Type * base,
                                         uint32_t instance,
                                         sim_tpm_clk_sel_t select)
{
    assert (instance < TPM_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        SIM_BWR_SOPT4_TPM0CLKSEL(base, select);
        break;
    case 1:
        SIM_BWR_SOPT4_TPM1CLKSEL(base, select);
        break;
    case 2:
        SIM_BWR_SOPT4_TPM2CLKSEL(base, select);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetTpmExternalClkPinSelMode
 * Description   : Get Timer/PWM x external clock pin select setting
 * This function will get Timer/PWM x external clock pin select setting.
 * 
 *END**************************************************************************/
sim_tpm_clk_sel_t SIM_HAL_GetTpmExternalClkPinSelMode(SIM_Type * base, uint32_t instance)
{
    sim_tpm_clk_sel_t retValue = (sim_tpm_clk_sel_t)0;

    assert (instance < TPM_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        retValue = (sim_tpm_clk_sel_t)SIM_BRD_SOPT4_TPM0CLKSEL(base);
        break;
    case 1:
        retValue = (sim_tpm_clk_sel_t)SIM_BRD_SOPT4_TPM1CLKSEL(base);
        break;
    case 2:
        retValue = (sim_tpm_clk_sel_t)SIM_BRD_SOPT4_TPM2CLKSEL(base);
        break;
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetTpmChSrcMode
 * Description   : Timer/PWM x channel y input capture source select setting 
 * This function will select Timer/PWM x channel y input capture source
 * 
 *END**************************************************************************/
void SIM_HAL_SetTpmChSrcMode(SIM_Type * base,
                             uint32_t instance,
                             uint8_t channel,
                             sim_tpm_ch_src_t select)
{
    assert (instance < TPM_INSTANCE_COUNT);

    switch (instance)
    {
    case 1:
        SIM_BWR_SOPT4_TPM1CH0SRC(base, select);
        break;
    case 2:
        SIM_BWR_SOPT4_TPM2CH0SRC(base, select);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetTpmChSrcMode
 * Description   : Get Timer/PWM x channel y input capture source select setting
 * This function will get Timer/PWM x channel y input capture source select 
 * setting.
 * 
 *END**************************************************************************/
sim_tpm_ch_src_t SIM_HAL_GetTpmChSrcMode(SIM_Type * base,
                                         uint32_t instance,
                                         uint8_t channel)
{
    sim_tpm_ch_src_t retValue = (sim_tpm_ch_src_t)0;

    assert (instance < TPM_INSTANCE_COUNT);

    switch (instance)
    {
    case 1:
        retValue = (sim_tpm_ch_src_t)SIM_BRD_SOPT4_TPM1CH0SRC(base);
        break;
    case 2:
        retValue = (sim_tpm_ch_src_t)SIM_BRD_SOPT4_TPM2CH0SRC(base);
        break;
    default:
        break;
    }

    return retValue;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

