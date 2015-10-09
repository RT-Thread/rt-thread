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

#include "fsl_ftm_driver.h"
#include "fsl_clock_manager.h"

#if FSL_FEATURE_SOC_FTM_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Table of number of channels for each FTM instance */
const int32_t g_ftmChannelCount[FTM_INSTANCE_COUNT] = FSL_FEATURE_FTM_CHANNEL_COUNTx;
/*! Stores FTM clock source setting */
static ftm_clock_source_t s_ftmClockSource = kClock_source_FTM_None;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_Init
 * Description   : Initializes the FTM driver.
 *
 *END**************************************************************************/
ftm_status_t FTM_DRV_Init(uint32_t instance, const ftm_user_config_t * info)
{
    assert(instance < FTM_INSTANCE_COUNT);
    assert(g_ftmBase[instance] != NULL);

    FTM_Type *ftmBase = g_ftmBase[instance];
    uint8_t chan = g_ftmChannelCount[instance];

    /* clock setting initialization*/
    CLOCK_SYS_EnableFtmClock(instance);

    FTM_HAL_Reset(ftmBase);
    /* Reset the channel registers */
    for(int i = 0; i < chan; i++)
    {
        FTM_WR_CnSC(ftmBase, i, 0);
        FTM_WR_CnV(ftmBase, i, 0);
    }

    FTM_HAL_Init(ftmBase);

    FTM_HAL_SetSyncMode(ftmBase, info->syncMethod);

    FTM_HAL_SetTofFreq(ftmBase, info->tofFrequency);
    FTM_HAL_SetWriteProtectionCmd(ftmBase, info->isWriteProtection);
    FTM_HAL_SetBdmMode(ftmBase,info->BDMMode);

    NVIC_ClearPendingIRQ(g_ftmIrqId[instance]);
    INT_SYS_EnableIRQ(g_ftmIrqId[instance]);

    return kStatusFtmSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_Deinit
 * Description   : Shuts down the FTM driver.
 *
 *END**************************************************************************/
void FTM_DRV_Deinit(uint32_t instance)
{
    assert(instance < FTM_INSTANCE_COUNT);

    /* disable clock for FTM.*/
    CLOCK_SYS_DisableFtmClock(instance);

    INT_SYS_DisableIRQ(g_ftmIrqId[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_SetFaultIntCmd
 * Description   : Enables or disables the fault interrupt.
 *
 *END**************************************************************************/
void FTM_DRV_SetFaultIntCmd(uint32_t instance, bool faultEnable)
{
    if (faultEnable)
    {
        FTM_HAL_EnableFaultInt(g_ftmBase[instance]);
    }
    else
    {
        FTM_HAL_DisableFaultInt(g_ftmBase[instance]);
    }

}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_SetTimeOverflowIntCmd
 * Description   : Enables or disables the timer overflow interrupt.
 *
 *END**************************************************************************/
void FTM_DRV_SetTimeOverflowIntCmd(uint32_t instance, bool overflowEnable)
{
    if (overflowEnable)
    {
        FTM_HAL_EnableTimerOverflowInt(g_ftmBase[instance]);
    }
    else
    {
        FTM_HAL_DisableTimerOverflowInt(g_ftmBase[instance]);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_QuadDecodeStart
 * Description   : Configures the parameters needed and activates quadrature
 * decode mode.
 *
 *END**************************************************************************/
void FTM_DRV_QuadDecodeStart(uint32_t instance, ftm_phase_params_t *phaseAParams,
                                      ftm_phase_params_t *phaseBParams, ftm_quad_decode_mode_t quadMode)
{
    assert(instance < FTM_INSTANCE_COUNT);
    assert(phaseAParams);
    assert(phaseBParams);

    FTM_Type *ftmBase = g_ftmBase[instance];

    FTM_HAL_SetQuadMode(ftmBase, quadMode);
    FTM_HAL_SetQuadPhaseAFilterCmd(ftmBase, phaseAParams->kFtmPhaseInputFilter);
    if (phaseAParams->kFtmPhaseInputFilter)
    {
        /* Set Phase A filter value if phase filter is enabled */
        FTM_HAL_SetChnInputCaptureFilter(ftmBase, CHAN0_IDX, phaseAParams->kFtmPhaseFilterVal);
    }
    FTM_HAL_SetQuadPhaseBFilterCmd(ftmBase, phaseBParams->kFtmPhaseInputFilter);
    if (phaseBParams->kFtmPhaseInputFilter)
    {
        /* Set Phase B filter value if phase filter is enabled */
        FTM_HAL_SetChnInputCaptureFilter(ftmBase, CHAN1_IDX, phaseBParams->kFtmPhaseFilterVal);
    }
    FTM_HAL_SetQuadPhaseAPolarity(ftmBase, phaseAParams->kFtmPhasePolarity);
    FTM_HAL_SetQuadPhaseBPolarity(ftmBase, phaseBParams->kFtmPhasePolarity);

    FTM_HAL_SetQuadDecoderCmd(ftmBase, true);

    /* Set clock source to start the counter */
    FTM_HAL_SetClockSource(ftmBase, s_ftmClockSource);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_QuadDecodeStop
 * Description   : De-activates quadrature decode mode.
 * This function will initialize the Real Time Clock module.
 *
 *END**************************************************************************/
void FTM_DRV_QuadDecodeStop(uint32_t instance)
{
    /* Stop the FTM counter */
    FTM_HAL_SetClockSource(g_ftmBase[instance], kClock_source_FTM_None);

    FTM_HAL_SetQuadDecoderCmd(g_ftmBase[instance], false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_CounterStart
 * Description   : Starts the FTM counter. This function provides access to the
 * FTM counter. The counter can be run in Up-counting and Up-down counting modes.
 * To run the counter in Free running mode, choose Up-counting option and provide
 * 0x0 for the countStartVal and 0xFFFF for countFinalVal.
 *
 *END**************************************************************************/
void FTM_DRV_CounterStart(uint32_t instance, ftm_counting_mode_t countMode, uint32_t countStartVal,
                                 uint32_t countFinalVal, bool enableOverflowInt)
{
    assert(instance < FTM_INSTANCE_COUNT);

    FTM_Type *ftmBase = g_ftmBase[instance];
    uint32_t channel = 0;

    /* Clear the overflow flag */
    FTM_HAL_ClearTimerOverflow(ftmBase);
    FTM_HAL_SetCounterInitVal(ftmBase, countStartVal);
    FTM_HAL_SetMod(ftmBase, countFinalVal);
    FTM_HAL_SetCounter(ftmBase, 0);

    /* Use FTM as counter, disable all the channels */
    for (channel = 0; channel < g_ftmChannelCount[instance]; channel++)
    {
        FTM_HAL_SetChnEdgeLevel(ftmBase, channel, 0);
    }

    if (countMode == kCounting_FTM_UP)
    {
        FTM_HAL_SetQuadDecoderCmd(ftmBase, false);
        FTM_HAL_SetCpwms(ftmBase, 0);
    }
    else if (countMode == kCounting_FTM_UpDown)
    {
        FTM_HAL_SetQuadDecoderCmd(ftmBase, false);
        FTM_HAL_SetCpwms(ftmBase, 1);
    }

    /* Activate interrupts if required */
    FTM_DRV_SetTimeOverflowIntCmd(instance, enableOverflowInt);

    /* Set clock source to start the counter */
    FTM_HAL_SetClockSource(ftmBase, s_ftmClockSource);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_CounterStop
 * Description   : Stops the FTM counter.
 *
 *END**************************************************************************/
void FTM_DRV_CounterStop(uint32_t instance)
{
    /* Stop the FTM counter */
    FTM_HAL_SetClockSource(g_ftmBase[instance], kClock_source_FTM_None);

    FTM_HAL_SetCpwms(g_ftmBase[instance], 0);

    /* Disable the overflow interrupt */
    FTM_DRV_SetTimeOverflowIntCmd(instance, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_CounterRead
 * Description   : Reads back the current value of the FTM counter.
 *
 *END**************************************************************************/
uint32_t FTM_DRV_CounterRead(uint32_t instance)
{
    assert(instance < FTM_INSTANCE_COUNT);

    return FTM_HAL_GetCounter(g_ftmBase[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_SetClock
 * Description   : Set FTM clock source.
 * This function will save the users clock source selection in the driver and
 * uses this to set the clock source whenever the user decides to use features provided
 * by this driver like counter, PWM generation etc. It will also set the clock divider.
 *
 *END**************************************************************************/
void FTM_DRV_SetClock(uint8_t instance, ftm_clock_source_t clock, ftm_clock_ps_t clockPs)
{
    assert(instance < FTM_INSTANCE_COUNT);
    assert(clock != kClock_source_FTM_None);

    /*Clock prescaler*/
    FTM_HAL_SetClockPs(g_ftmBase[instance], clockPs);
    s_ftmClockSource = clock;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_GetClock
 * Description   : Retrieves the frequency of the clock source feeding the FTM counter.
 * Function will return a 0 if no clock source is selected and the FTM counter is disabled
 *
 *END**************************************************************************/
uint32_t FTM_DRV_GetClock(uint8_t instance)
{
    assert(instance < FTM_INSTANCE_COUNT);

    FTM_Type *ftmBase = g_ftmBase[instance];
    uint8_t clkPs;
    uint32_t freq = 0;

    clkPs = (1 << FTM_HAL_GetClockPs(ftmBase));

    switch(s_ftmClockSource)
    {
        case kClock_source_FTM_ExternalClk:
            freq = CLOCK_SYS_GetFtmExternalFreq(instance) / clkPs;
            break;
        case kClock_source_FTM_FixedClk:
            freq = CLOCK_SYS_GetFtmFixedFreq(instance) / clkPs;
            break;
        case kClock_source_FTM_SystemClk:
            freq = CLOCK_SYS_GetFtmSystemClockFreq(instance) / clkPs;
            break;
        default:
            break;
    }

    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_PwmStop
 * Description   : Stops channel PWM.
 *
 *END**************************************************************************/
void FTM_DRV_PwmStop(uint32_t instance, ftm_pwm_param_t *param, uint8_t channel)
{
    assert((param->mode == kFtmEdgeAlignedPWM) || (param->mode == kFtmCenterAlignedPWM) ||
           (param->mode == kFtmCombinedPWM));
    assert(instance < FTM_INSTANCE_COUNT);
    assert(channel < g_ftmChannelCount[instance]);

    FTM_Type *ftmBase = g_ftmBase[instance];

    /* Stop the FTM counter */
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None);

    FTM_HAL_DisablePwmMode(ftmBase, param, channel);

    /* Clear out the registers */
    FTM_HAL_SetMod(ftmBase, 0);
    FTM_HAL_SetCounter(ftmBase, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_PwmStart
 * Description   : Configures duty cycle and frequency and starts outputting
 * PWM on specified channel .
 *
 *END**************************************************************************/
ftm_status_t FTM_DRV_PwmStart(uint32_t instance, ftm_pwm_param_t *param, uint8_t channel)
{
    uint32_t uFTMhz;
    uint16_t uMod, uCnv, uCnvFirstEdge = 0;

    assert(instance < FTM_INSTANCE_COUNT);
    assert(param->uDutyCyclePercent <= 100);
    assert(channel < g_ftmChannelCount[instance]);

    FTM_Type *ftmBase = g_ftmBase[instance];

    /* Clear the overflow flag */
    FTM_HAL_ClearTimerOverflow(ftmBase);

    FTM_HAL_EnablePwmMode(ftmBase, param, channel);

    if (s_ftmClockSource == kClock_source_FTM_None)
    {
        return kStatusFtmError;
    }

    uFTMhz = FTM_DRV_GetClock(instance);

    /* Based on Ref manual, in PWM mode CNTIN is to be set 0*/
    FTM_HAL_SetCounterInitVal(ftmBase, 0);

    switch(param->mode)
    {
        case kFtmEdgeAlignedPWM:
            uMod = uFTMhz / (param->uFrequencyHZ) - 1;
            uCnv = uMod * param->uDutyCyclePercent / 100;
            /* For 100% duty cycle */
            if(uCnv >= uMod)
            {
                uCnv = uMod + 1;
            }
            FTM_HAL_SetMod(ftmBase, uMod);
            FTM_HAL_SetChnCountVal(ftmBase, channel, uCnv);
            break;
        case kFtmCenterAlignedPWM:
            uMod = uFTMhz / (param->uFrequencyHZ * 2);
            uCnv = uMod * param->uDutyCyclePercent / 100;
            /* For 100% duty cycle */
            if(uCnv >= uMod)
            {
                uCnv = uMod + 1;
            }
            FTM_HAL_SetMod(ftmBase, uMod);
            FTM_HAL_SetChnCountVal(ftmBase, channel, uCnv);
            break;
        case kFtmCombinedPWM:
            uMod = uFTMhz / (param->uFrequencyHZ) - 1;
            uCnv = uMod * param->uDutyCyclePercent / 100;
            uCnvFirstEdge = uMod * param->uFirstEdgeDelayPercent / 100;
            /* For 100% duty cycle */
            if(uCnv >= uMod)
            {
                uCnv = uMod + 1;
            }
            FTM_HAL_SetMod(ftmBase, uMod);
            FTM_HAL_SetChnCountVal(ftmBase, FTM_HAL_GetChnPairIndex(channel) * 2,
                                   uCnvFirstEdge);
            FTM_HAL_SetChnCountVal(ftmBase, FTM_HAL_GetChnPairIndex(channel) * 2 + 1,
                                   uCnv + uCnvFirstEdge);
            break;
        default:
            assert(0);
            break;
    }

    /* Set clock source to start counter */
    FTM_HAL_SetClockSource(ftmBase, s_ftmClockSource);
    return kStatusFtmSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_SetupChnInputCapture
 * Description   : Enables capture of an input signal on the channel using the
 * paramters specified to this function. When the edge specified in the captureMode
 * argument occurs on the channel the FTM counter is captured into the CnV register.
 * The user will have to read the CnV register separately to get this value. The filter
 * function is disabled if the filterVal argument passed in is 0. The filter function
 * is available only on channels 0,1,2,3.
 *
 *END**************************************************************************/
void FTM_DRV_SetupChnInputCapture(uint32_t instance, ftm_input_capture_edge_mode_t captureMode,
                                            uint8_t channel, uint8_t filterVal)
{
    assert(instance < FTM_INSTANCE_COUNT);
    assert(channel < g_ftmChannelCount[instance]);

    FTM_Type *ftmBase = g_ftmBase[instance];
    uint32_t chnlPairnum = FTM_HAL_GetChnPairIndex(channel);

    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None);

    FTM_HAL_SetCounterInitVal(ftmBase, 0);
    FTM_HAL_SetMod(ftmBase, 0xFFFF);
    FTM_HAL_SetCpwms(ftmBase, 0);
    FTM_HAL_SetDualChnCombineCmd(ftmBase, chnlPairnum, false);
    FTM_HAL_SetDualEdgeCaptureCmd(ftmBase, chnlPairnum, false);
    FTM_HAL_SetChnEdgeLevel(ftmBase, channel, captureMode);

    if (channel < CHAN4_IDX)
    {
        FTM_HAL_SetChnInputCaptureFilter(ftmBase, channel, filterVal);
    }

    FTM_HAL_SetChnMSnBAMode(ftmBase, channel, 0);

    /* Set clock source to start the counter */
    FTM_HAL_SetClockSource(ftmBase, s_ftmClockSource);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_SetupChnOutputCompare
 * Description   : Configures the FTM to generate timed pulses
 * When the FTM counter matches the value of compareVal argument (this is
 * written into CnV reg), the channel output is changed based on what is specified
 * in the compareMode argument.
 *
 *END**************************************************************************/
void FTM_DRV_SetupChnOutputCompare(uint32_t instance, ftm_output_compare_edge_mode_t compareMode,
                                               uint8_t channel, uint32_t compareVal)
{
    assert(instance < FTM_INSTANCE_COUNT);
    assert(channel < g_ftmChannelCount[instance]);

    FTM_Type *ftmBase = g_ftmBase[instance];
    uint32_t chnlPairnum = FTM_HAL_GetChnPairIndex(channel);

    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None);

    FTM_HAL_SetCounterInitVal(ftmBase, 0);
    FTM_HAL_SetMod(ftmBase, 0xFFFF);
    FTM_HAL_SetCpwms(ftmBase, 0);
    FTM_HAL_SetDualChnCombineCmd(ftmBase, chnlPairnum, false);
    FTM_HAL_SetDualEdgeCaptureCmd(ftmBase, chnlPairnum, false);
    FTM_HAL_SetChnEdgeLevel(ftmBase, channel, compareMode);
    FTM_HAL_SetChnMSnBAMode(ftmBase, channel, 1);
    FTM_HAL_SetChnCountVal(ftmBase, channel, compareVal);

    /* Set clock source to start the counter */
    FTM_HAL_SetClockSource(ftmBase, s_ftmClockSource);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_SetupChnDualEdgeCapture
 * Description   : Configures the Dual Edge Capture mode of the FTM
 * This function sets up the dual edge capture mode on a channel pair.
 * The capture edge for the channel pair and the capture mode (one-shot or continuous)
 * is specified in the param argument. The filter function is disabled if the
 * filterVal argument passed in is 0. The filter function is available only on
 * channels 0 and 2. The user will have to read the channel CnV registers separately
 * to get the capture values.
 *
 *END**************************************************************************/
void FTM_DRV_SetupChnDualEdgeCapture(uint32_t instance, ftm_dual_edge_capture_param_t *param,
                                                 uint8_t channel, uint8_t filterVal)
{
    assert(instance < FTM_INSTANCE_COUNT);
    assert(channel < g_ftmChannelCount[instance]);

    FTM_Type *ftmBase = g_ftmBase[instance];
    uint32_t chnlPairnum = FTM_HAL_GetChnPairIndex(channel);

    /* Stop the counter */
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None);

    FTM_HAL_SetCounterInitVal(ftmBase, 0);
    FTM_HAL_SetMod(ftmBase, 0xFFFF);
    FTM_HAL_SetCpwms(ftmBase, 0);
    FTM_HAL_SetDualChnCombineCmd(ftmBase, chnlPairnum, false);
    /* Enable the DECAPEN bit */
    FTM_HAL_SetDualEdgeCaptureCmd(ftmBase, chnlPairnum, true);
    /* Setup the edge detection from channel n and n + 1 */
    FTM_HAL_SetChnEdgeLevel(ftmBase, chnlPairnum * 2, param->currChanEdgeMode);
    FTM_HAL_SetChnEdgeLevel(ftmBase, (chnlPairnum * 2) + 1, param->nextChanEdgeMode);

    FTM_HAL_ClearChnEventFlag(ftmBase, channel);
    FTM_HAL_ClearChnEventFlag(ftmBase, channel + 1);
    FTM_HAL_SetDualChnDecapCmd(ftmBase, chnlPairnum, true);
    FTM_HAL_SetChnMSnBAMode(ftmBase, chnlPairnum * 2, param->mode);

    if (channel < CHAN4_IDX)
    {
        FTM_HAL_SetChnInputCaptureFilter(ftmBase, channel, filterVal);
    }

    /* Set clock source to start the counter */
    FTM_HAL_SetClockSource(ftmBase, s_ftmClockSource);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_DRV_IRQHandler
 * Description   : Initializes the Real Time Clock module
 * This function will initialize the Real Time Clock module.
 *
 *END**************************************************************************/
void FTM_DRV_IRQHandler(uint32_t instance)
{
    FTM_Type *ftmBase = g_ftmBase[instance];
    uint16_t channel;

    /* Clear the Status flag if the interrupt is enabled */
    if (FTM_HAL_IsOverflowIntEnabled(ftmBase))
    {
        FTM_HAL_ClearTimerOverflow(ftmBase);
    }

    for (channel = 0; channel < g_ftmChannelCount[instance]; channel++)
    {
        if (FTM_HAL_IsChnIntEnabled(ftmBase, channel))
        {
            FTM_HAL_ClearChnEventStatus(ftmBase, channel);
        }
    }
}

#endif /* FSL_FEATURE_SOC_FTM_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

