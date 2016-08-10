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
 * Function Name : CLOCK_HAL_SetUsbfsDiv
 * Description   : Sets USB devider setting.
 * Divider output clock = Divider input clock * [ (USBFRAC+1) / (USBDIV+1) ]
 *
 *END**************************************************************************/
void CLOCK_HAL_SetUsbfsDiv(SIM_Type * base,
                           uint8_t usbdiv,
                           uint8_t usbfrac)
{
    SIM_BWR_CLKDIV2_USBDIV(base, usbdiv);
    SIM_BWR_CLKDIV2_USBFRAC(base, usbfrac);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetUsbfDiv
 * Description   : Gets USB devider setting.
 * Divider output clock = Divider input clock * [ (USBFRAC+1) / (USBDIV+1) ]
 *
 *END**************************************************************************/
void CLOCK_HAL_GetUsbfsDiv(SIM_Type * base,
                           uint8_t *usbdiv,
                           uint8_t *usbfrac)
{
    *usbdiv  = SIM_BRD_CLKDIV2_USBDIV(base);
    *usbfrac = SIM_BRD_CLKDIV2_USBFRAC(base);
}

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
    clkdiv1 |= SIM_CLKDIV1_OUTDIV2(outdiv2);
    clkdiv1 |= SIM_CLKDIV1_OUTDIV3(outdiv3);
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
    *outdiv2 = SIM_BRD_CLKDIV1_OUTDIV2(base);
    *outdiv3 = SIM_BRD_CLKDIV1_OUTDIV3(base);
    *outdiv4 = SIM_BRD_CLKDIV1_OUTDIV4(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetAdcAlternativeTriggerCmd
 * Description   : Set ADCx alternate trigger enable setting
 * This function will enable/disable alternative conversion triggers for ADCx.
 *
 *END**************************************************************************/
void SIM_HAL_SetAdcAlternativeTriggerCmd(SIM_Type * base,
                                         uint32_t instance,
                                         bool enable)
{
    assert(instance < ADC_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        SIM_BWR_SOPT7_ADC0ALTTRGEN(base, enable ? 1 : 0);
        break;
    case 1:
        SIM_BWR_SOPT7_ADC1ALTTRGEN(base, enable ? 1 : 0);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetAdcAlternativeTriggerCmd
 * Description   : Get ADCx alternate trigger enable setting
 * This function will get ADCx alternate trigger enable setting.
 *
 *END**************************************************************************/
bool SIM_HAL_GetAdcAlternativeTriggerCmd(SIM_Type * base, uint32_t instance)
{
    bool retValue = false;

    assert(instance < ADC_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        retValue = SIM_BRD_SOPT7_ADC0ALTTRGEN(base);
        break;
    case 1:
        retValue = SIM_BRD_SOPT7_ADC1ALTTRGEN(base);
        break;
    default:
        retValue = false;
        break;
    }

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
void SIM_HAL_SetAdcPreTriggerMode(SIM_Type * base,
                                  uint32_t instance,
                                  sim_adc_pretrg_sel_t select)
{
    assert(instance < ADC_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        SIM_BWR_SOPT7_ADC0PRETRGSEL(base, select);
        break;
    case 1:
        SIM_BWR_SOPT7_ADC1PRETRGSEL(base, select);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetAdcPreTriggerMode
 * Description   : Get ADCx pre-trigger select setting
 * This function will get ADCx pre-trigger select setting.
 *
 *END**************************************************************************/
sim_adc_pretrg_sel_t SIM_HAL_GetAdcPreTriggerMode(SIM_Type * base,
                                                  uint32_t instance)
{
    sim_adc_pretrg_sel_t retValue = (sim_adc_pretrg_sel_t)0;

    assert(instance < ADC_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        retValue = (sim_adc_pretrg_sel_t)SIM_BRD_SOPT7_ADC0PRETRGSEL(base);
        break;
    case 1:
        retValue = (sim_adc_pretrg_sel_t)SIM_BRD_SOPT7_ADC1PRETRGSEL(base);
        break;
    default:
        break;
    }

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

    switch (instance)
    {
    case 0:
        SIM_BWR_SOPT7_ADC0TRGSEL(base, select);
        break;
    case 1:
        SIM_BWR_SOPT7_ADC1TRGSEL(base, select);
        break;
    default:
        break;
    }
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
    sim_adc_trg_sel_t retValue = (sim_adc_trg_sel_t)0;

    assert(instance < ADC_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        retValue = (sim_adc_trg_sel_t)SIM_BRD_SOPT7_ADC0TRGSEL(base);
        break;
    case 1:
        retValue = (sim_adc_trg_sel_t)SIM_BRD_SOPT7_ADC1TRGSEL(base);
        break;
    default:
        break;
    }

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

    switch (instance)
    {
        case 0:
            SIM_BWR_SOPT7_ADC0ALTTRGEN(base, altTrigEn ? 1 : 0);
            SIM_BWR_SOPT7_ADC0PRETRGSEL(base, preTrigSel);
            break;
        case 1:
            SIM_BWR_SOPT7_ADC1ALTTRGEN(base, altTrigEn ? 1 : 0);
            SIM_BWR_SOPT7_ADC1PRETRGSEL(base, preTrigSel);
            break;
    default:
        break;
    }

    if (altTrigEn)
    {
        switch (instance)
        {
            case 0:
                SIM_BWR_SOPT7_ADC0TRGSEL(base, trigSel);
                break;
            case 1:
                SIM_BWR_SOPT7_ADC1TRGSEL(base, trigSel);
                break;
            default:
                break;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetUartRxSrcMode
 * Description   : Set UARTx receive data source select setting
 * This function will select the source for the UART1 receive data.
 *
 *END**************************************************************************/
void SIM_HAL_SetUartRxSrcMode(SIM_Type * base,
                              uint32_t instance,
                              sim_uart_rxsrc_t select)
{
    assert(instance < FSL_FEATURE_SIM_OPT_UART_COUNT);

    switch (instance)
    {
    case 0:
        SIM_BWR_SOPT5_UART0RXSRC(base, select);
        break;
    case 1:
        SIM_BWR_SOPT5_UART1RXSRC(base, select);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetUartRxSrcMode
 * Description   : Get UARTx receive data source select setting
 * This function will get UARTx receive data source select setting.
 *
 *END**************************************************************************/
sim_uart_rxsrc_t SIM_HAL_GetUartRxSrcMode(SIM_Type * base, uint32_t instance)
{
    sim_uart_rxsrc_t retValue = (sim_uart_rxsrc_t)0;

    assert(instance < FSL_FEATURE_SIM_OPT_UART_COUNT);

    switch (instance)
    {
    case 0:
        retValue = (sim_uart_rxsrc_t)SIM_BRD_SOPT5_UART0RXSRC(base);
        break;
    case 1:
        retValue = (sim_uart_rxsrc_t)SIM_BRD_SOPT5_UART1RXSRC(base);
        break;
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetUartTxSrcMode
 * Description   : Set UARTx transmit data source select setting
 * This function will select the source for the UARTx transmit data.
 *
 *END**************************************************************************/
void SIM_HAL_SetUartTxSrcMode(SIM_Type * base,
                              uint32_t instance,
                              sim_uart_txsrc_t select)
{
    assert(instance < FSL_FEATURE_SIM_OPT_UART_COUNT);

    switch (instance)
    {
    case 0:
        SIM_BWR_SOPT5_UART0TXSRC(base, select);
        break;
    case 1:
        SIM_BWR_SOPT5_UART1TXSRC(base, select);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetUartTxSrcMode
 * Description   : Get UARTx transmit data source select setting
 * This function will get UARTx transmit data source select setting.
 *
 *END**************************************************************************/
sim_uart_txsrc_t SIM_HAL_GetUartTxSrcMode(SIM_Type * base, uint32_t instance)
{
    sim_uart_txsrc_t retValue =(sim_uart_txsrc_t)0;

    assert(instance < FSL_FEATURE_SIM_OPT_UART_COUNT);

    switch (instance)
    {
    case 0:
        retValue = (sim_uart_txsrc_t)SIM_BRD_SOPT5_UART0TXSRC(base);
        break;
    case 1:
        retValue = (sim_uart_txsrc_t)SIM_BRD_SOPT5_UART1TXSRC(base);
        break;
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetFtmTriggerSrcMode
 * Description   : Set FlexTimer x hardware trigger y source select setting
 * This function will select the source of FTMx hardware trigger y.
 *
 *END**************************************************************************/
void SIM_HAL_SetFtmTriggerSrcMode(SIM_Type * base,
                                  uint32_t instance,
                                  uint8_t  trigger,
                                  sim_ftm_trg_src_t select)
{
    assert (instance < FTM_INSTANCE_COUNT);
    assert (trigger < FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT);

    switch (instance)
    {
    case 0:
        switch (trigger)
        {
        case 0:
            SIM_BWR_SOPT4_FTM0TRG0SRC(base, select);
            break;
        case 1:
            SIM_BWR_SOPT4_FTM0TRG1SRC(base, select);
            break;
        default:
            break;
        }
        break;
    case 3:
        switch (trigger)
        {
        case 0:
            SIM_BWR_SOPT4_FTM3TRG0SRC(base, select);
            break;
        case 1:
            SIM_BWR_SOPT4_FTM3TRG1SRC(base, select);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetFtmTriggerSrcMode
 * Description   : Get FlexTimer x hardware trigger y source select setting
 * This function will get FlexTimer x hardware trigger y source select setting.
 *
 *END**************************************************************************/
sim_ftm_trg_src_t SIM_HAL_GetFtmTriggerSrcMode(SIM_Type * base,
                                               uint32_t instance,
                                               uint8_t trigger)
{
    sim_ftm_trg_src_t retValue = (sim_ftm_trg_src_t)0;

    assert (instance < FTM_INSTANCE_COUNT);
    assert (trigger < FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT);

    switch (instance)
    {
    case 0:
        switch (trigger)
        {
        case 0:
            retValue = (sim_ftm_trg_src_t)SIM_BRD_SOPT4_FTM0TRG0SRC(base);
            break;
        case 1:
            retValue = (sim_ftm_trg_src_t)SIM_BRD_SOPT4_FTM0TRG1SRC(base);
            break;
        default:
            break;
        }
        break;
    case 3:
        switch (trigger)
        {
        case 0:
            retValue = (sim_ftm_trg_src_t)SIM_BRD_SOPT4_FTM3TRG0SRC(base);
            break;
        case 1:
            retValue = (sim_ftm_trg_src_t)SIM_BRD_SOPT4_FTM3TRG1SRC(base);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetFtmExternalClkPinMode
 * Description   : Set FlexTimer x external clock pin select setting
 * This function will select the source of FTMx external clock pin select
 *
 *END**************************************************************************/
void SIM_HAL_SetFtmExternalClkPinMode(SIM_Type * base,
                                      uint32_t instance,
                                      sim_ftm_clk_sel_t select)
{
    assert (instance < FTM_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        SIM_BWR_SOPT4_FTM0CLKSEL(base, select);
        break;
    case 1:
        SIM_BWR_SOPT4_FTM1CLKSEL(base, select);
        break;
    case 2:
        SIM_BWR_SOPT4_FTM2CLKSEL(base, select);
        break;
    case 3:
        SIM_BWR_SOPT4_FTM3CLKSEL(base, select);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetFtmExternalClkPinMode
 * Description   : Get FlexTimer x external clock pin select setting
 * This function will get FlexTimer x external clock pin select setting.
 *
 *END**************************************************************************/
sim_ftm_clk_sel_t SIM_HAL_GetFtmExternalClkPinMode(SIM_Type * base,
                                                   uint32_t instance)
{
    sim_ftm_clk_sel_t retValue = (sim_ftm_clk_sel_t)0;

    assert (instance < FTM_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        retValue = (sim_ftm_clk_sel_t)SIM_BRD_SOPT4_FTM0CLKSEL(base);
        break;
    case 1:
        retValue = (sim_ftm_clk_sel_t)SIM_BRD_SOPT4_FTM1CLKSEL(base);
        break;
    case 2:
        retValue = (sim_ftm_clk_sel_t)SIM_BRD_SOPT4_FTM2CLKSEL(base);
        break;
    case 3:
        retValue = (sim_ftm_clk_sel_t)SIM_BRD_SOPT4_FTM3CLKSEL(base);
        break;
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetFtmChSrcMode
 * Description   : FlexTimer x channel y input capture source select setting
 * This function will select FlexTimer x channel y input capture source
 *
 *END**************************************************************************/
void SIM_HAL_SetFtmChSrcMode(SIM_Type * base,
                             uint32_t instance,
                             uint8_t  channel,
                             sim_ftm_ch_src_t select)
{
    assert (instance < FTM_INSTANCE_COUNT);

    switch (instance)
    {
    case 1:
        switch (channel)
        {
        case 0:
            SIM_BWR_SOPT4_FTM1CH0SRC(base, select);
            break;
        default:
            break;
        }
        break;
    case 2:
        switch (channel)
        {
        case 0:
            SIM_BWR_SOPT4_FTM2CH0SRC(base, select);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetFtmChSrcMode
 * Description   : Get FlexTimer x channel y input capture source select setting
 * This function will get FlexTimer x channel y input capture source select
 * setting.
 *
 *END**************************************************************************/
sim_ftm_ch_src_t SIM_HAL_GetFtmChSrcMode(SIM_Type * base,
                                         uint32_t instance,
                                         uint8_t channel)
{
    sim_ftm_ch_src_t retValue = (sim_ftm_ch_src_t)0;

    assert (instance < FTM_INSTANCE_COUNT);

    switch (instance)
    {
    case 1:
        switch (channel)
        {
        case 0:
            retValue = (sim_ftm_ch_src_t)SIM_BRD_SOPT4_FTM1CH0SRC(base);
            break;
        default:
            break;
        }
        break;
    case 2:
        switch (channel)
        {
        case 0:
            retValue = (sim_ftm_ch_src_t)SIM_BRD_SOPT4_FTM2CH0SRC(base);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetFtmFaultSelMode
 * Description   : Set FlexTimer x fault y select setting
 * This function will set the FlexTimer x fault y select setting.
 *
 *END**************************************************************************/
void SIM_HAL_SetFtmFaultSelMode(SIM_Type * base,
                                uint32_t instance,
                                uint8_t  fault,
                                sim_ftm_flt_sel_t select)
{
    assert (instance < FTM_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        switch (fault)
        {
        case 0:
            SIM_BWR_SOPT4_FTM0FLT0(base, select);
            break;
        case 1:
            SIM_BWR_SOPT4_FTM0FLT1(base, select);
            break;
        case 2:
            SIM_BWR_SOPT4_FTM0FLT2(base, select);
            break;
        default:
            break;
        }
        break;
    case 1:
        SIM_BWR_SOPT4_FTM1FLT0(base, select);
        break;
    case 2:
        SIM_BWR_SOPT4_FTM2FLT0(base, select);
        break;
    case 3:
        SIM_BWR_SOPT4_FTM3FLT0(base, select);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetFtmFaultSelMode
 * Description   : Get FlexTimer x fault y select setting
 * This function will get FlexTimer x fault y select setting.
 *
 *END**************************************************************************/
sim_ftm_flt_sel_t SIM_HAL_GetFtmFaultSelMode(SIM_Type * base,
                                             uint32_t instance,
                                             uint8_t fault)
{
    sim_ftm_flt_sel_t retValue = (sim_ftm_flt_sel_t)0;

    assert (instance < FTM_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        switch (fault)
        {
        case 0:
            retValue = (sim_ftm_flt_sel_t)SIM_BRD_SOPT4_FTM0FLT0(base);
            break;
        case 1:
            retValue = (sim_ftm_flt_sel_t)SIM_BRD_SOPT4_FTM0FLT1(base);
            break;
        case 2:
            retValue = (sim_ftm_flt_sel_t)SIM_BRD_SOPT4_FTM0FLT2(base);
            break;
        default:
            break;
        }
        break;
    case 1:
        retValue = (sim_ftm_flt_sel_t)SIM_BRD_SOPT4_FTM1FLT0(base);
        break;
    case 2:
        retValue = (sim_ftm_flt_sel_t)SIM_BRD_SOPT4_FTM2FLT0(base);
        break;
    case 3:
        retValue = (sim_ftm_flt_sel_t)SIM_BRD_SOPT4_FTM3FLT0(base);
        break;
    default:
        break;
    }

    return retValue;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

