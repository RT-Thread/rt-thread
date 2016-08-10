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

#include "fsl_ftm_hal.h"

#if FSL_FEATURE_SOC_FTM_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_Init
 * Description   : Initializes the FTM.
 *
 *END**************************************************************************/
void FTM_HAL_Init(FTM_Type *ftmBase)
{
    /* Use FTM mode */
    FTM_HAL_Enable(ftmBase, true);
    FTM_HAL_SetClockPs(ftmBase, kFtmDividedBy2);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_SetSyncMode
 * Description   : Sets the FTM register synchronization method.
 * This function will set the necessary bits for the synchronization mode that user wishes to use.
 *
 *END**************************************************************************/
void FTM_HAL_SetSyncMode(FTM_Type *ftmBase, uint32_t syncMethod)
{
    assert(syncMethod & (FTM_SYNC_TRIG0_MASK | FTM_SYNC_TRIG1_MASK | FTM_SYNC_TRIG2_MASK | FTM_SYNC_SWSYNC_MASK));

    uint32_t channel = 0;

    /* Use the Enhanced PWM synchronization method */
    FTM_HAL_SetPwmSyncModeCmd(ftmBase, true);

    FTM_HAL_SetCntinPwmSyncModeCmd(ftmBase, true);
    FTM_HAL_SetInvctrlPwmSyncModeCmd(ftmBase, true);
    FTM_HAL_SetSwoctrlPwmSyncModeCmd(ftmBase, true);
    FTM_HAL_SetOutmaskPwmSyncModeCmd(ftmBase, true);

    for (channel = 0; channel < (FSL_FEATURE_FTM_CHANNEL_COUNT / 2); channel++)
    {
        FTM_HAL_SetDualChnPwmSyncCmd(ftmBase, channel, true);
    }
    if (syncMethod & FTM_SYNC_SWSYNC_MASK)
    {
        /* Enable needed bits for software trigger to update registers with its buffer value */
        FTM_HAL_SetCounterSoftwareSyncModeCmd(ftmBase, true);
        FTM_HAL_SetModCntinCvSoftwareSyncModeCmd(ftmBase, true);
        FTM_HAL_SetInvctrlSoftwareSyncModeCmd(ftmBase, true);
        FTM_HAL_SetSwoctrlSoftwareSyncModeCmd(ftmBase, true);
        FTM_HAL_SetOutmaskSoftwareSyncModeCmd(ftmBase, true);
    }
    if (syncMethod & (FTM_SYNC_TRIG0_MASK | FTM_SYNC_TRIG1_MASK | FTM_SYNC_TRIG2_MASK))
    {
        /* Enable needed bits for hardware trigger to update registers with its buffer value */
        FTM_HAL_SetCounterHardwareSyncModeCmd(ftmBase, true);
        FTM_HAL_SetModCntinCvHardwareSyncModeCmd(ftmBase, true);
        FTM_HAL_SetInvctrlHardwareSyncModeCmd(ftmBase, true);
        FTM_HAL_SetSwoctrlHardwareSyncModeCmd(ftmBase, true);
        FTM_HAL_SetOutmaskHardwareSyncModeCmd(ftmBase, true);
        if (syncMethod & FTM_SYNC_TRIG0_MASK)
        {
            FTM_BWR_SYNC_TRIG0(ftmBase, 1);
        }

        if (syncMethod & FTM_SYNC_TRIG1_MASK)
        {
            FTM_BWR_SYNC_TRIG1(ftmBase, 1);
        }
        if (syncMethod & FTM_SYNC_TRIG2_MASK)
        {
            FTM_BWR_SYNC_TRIG2(ftmBase, 1);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_EnablePwmMode
 * Description   : Enables the FTM timer when it is PWM output mode
 *
 *END**************************************************************************/
void FTM_HAL_EnablePwmMode(FTM_Type *ftmBase, ftm_pwm_param_t *config, uint8_t channel)
{
    uint8_t chnlPairnum = FTM_HAL_GetChnPairIndex(channel);

    FTM_HAL_SetDualEdgeCaptureCmd(ftmBase, chnlPairnum, false);
    FTM_HAL_SetChnEdgeLevel(ftmBase, channel, config->edgeMode ? 1 : 2);
    switch(config->mode)
    {
        case kFtmEdgeAlignedPWM:
            FTM_HAL_SetDualChnCombineCmd(ftmBase, chnlPairnum, false);
            FTM_HAL_SetCpwms(ftmBase, 0);
            FTM_HAL_SetChnMSnBAMode(ftmBase, channel, 2);
            break;
        case kFtmCenterAlignedPWM:
            FTM_HAL_SetDualChnCombineCmd(ftmBase, chnlPairnum, false);
            FTM_HAL_SetCpwms(ftmBase, 1);
            break;
        case kFtmCombinedPWM:
            FTM_HAL_SetCpwms(ftmBase, 0);
            FTM_HAL_SetDualChnCombineCmd(ftmBase, chnlPairnum, true);
            break;
        default:
            assert(0);
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_DisablePwmMode
 * Description   : Disables the PWM output mode.
 *
 *END**************************************************************************/
void FTM_HAL_DisablePwmMode(FTM_Type *ftmBase, ftm_pwm_param_t *config, uint8_t channel)
{
    uint8_t chnlPairnum = FTM_HAL_GetChnPairIndex(channel);

    FTM_HAL_SetChnCountVal(ftmBase, channel, 0);
    FTM_HAL_SetChnEdgeLevel(ftmBase, channel, 0);
    FTM_HAL_SetChnMSnBAMode(ftmBase, channel, 0);
    FTM_HAL_SetCpwms(ftmBase, 0);
    FTM_HAL_SetDualChnCombineCmd(ftmBase, chnlPairnum, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_Reset
 * Description   : Resets the FTM registers
 *
 *END**************************************************************************/
void FTM_HAL_Reset(FTM_Type *ftmBase)
{
    FTM_WR_SC(ftmBase, 0);
    FTM_WR_CNT(ftmBase, 0);
    FTM_WR_MOD(ftmBase, 0);

    FTM_WR_CNTIN(ftmBase, 0);
    FTM_WR_STATUS(ftmBase, 0);
    FTM_WR_MODE(ftmBase, 0x00000004);
    FTM_WR_SYNC(ftmBase, 0);
    FTM_WR_OUTINIT(ftmBase, 0);
    FTM_WR_OUTMASK(ftmBase, 0);
    FTM_WR_COMBINE(ftmBase, 0);
    FTM_WR_DEADTIME(ftmBase, 0);
    FTM_WR_EXTTRIG(ftmBase, 0);
    FTM_WR_POL(ftmBase, 0);
    FTM_WR_FMS(ftmBase, 0);
    FTM_WR_FILTER(ftmBase, 0);
    FTM_WR_FLTCTRL(ftmBase, 0);
    FTM_WR_CONF(ftmBase, 0);
    FTM_WR_FLTPOL(ftmBase, 0);
    FTM_WR_SYNCONF(ftmBase, 0);
    FTM_WR_INVCTRL(ftmBase, 0);
    FTM_WR_SWOCTRL(ftmBase, 0);
    FTM_WR_PWMLOAD(ftmBase, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_SetHardwareSyncTriggerSrc
 * Description   : Sets the FTM peripheral timer hardware trigger.
 *
 *END**************************************************************************/
void FTM_HAL_SetHardwareSyncTriggerSrc(FTM_Type *ftmBase, uint32_t trigger_num, bool enable)
{
    switch(trigger_num)
    {
        case 0:
            FTM_BWR_SYNC_TRIG0(ftmBase, enable ? 1 : 0);
            break;
        case 1:
            FTM_BWR_SYNC_TRIG1(ftmBase, enable ? 1 : 0);
            break;
        case 2:
            FTM_BWR_SYNC_TRIG2(ftmBase, enable ? 1 : 0);
            break;
        default:
            assert(0);
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_SetChnTriggerCmd
 * Description   : Enables or disables the generation of the FTM peripheral timer channel trigger.
 * Enables or disables the generation of the FTM peripheral timer channel trigger when the
 * FTM counter is equal to its initial value. Channels 6 and 7 cannot be used as triggers.
 *
 *END**************************************************************************/
void FTM_HAL_SetChnTriggerCmd(FTM_Type *ftmBase, uint8_t channel, bool val)
{
    assert(channel < CHAN6_IDX);

    uint8_t bit = val ? 1 : 0;
    uint32_t value = (channel > 1U) ? (uint8_t)(bit << (channel - 2U)) : (uint8_t)(bit << (channel + 4U));

    val ? FTM_SET_EXTTRIG(ftmBase, value) : FTM_CLR_EXTTRIG(ftmBase, value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_SetChnInputCaptureFilter
 * Description   : Sets the FTM peripheral timer channel input capture filter value.
 *
 *END**************************************************************************/
void FTM_HAL_SetChnInputCaptureFilter(FTM_Type *ftmBase, uint8_t channel, uint8_t val)
{
    assert(channel < CHAN4_IDX);

    switch(channel)
    {
        case CHAN0_IDX:
            FTM_BWR_FILTER_CH0FVAL(ftmBase, val);
            break;
        case CHAN1_IDX:
            FTM_BWR_FILTER_CH1FVAL(ftmBase, val);
            break;
        case CHAN2_IDX:
            FTM_BWR_FILTER_CH2FVAL(ftmBase, val);
            break;
        case CHAN3_IDX:
            FTM_BWR_FILTER_CH3FVAL(ftmBase, val);
            break;
        default:
            assert(0);
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FTM_HAL_GetChnPairIndex
 * Description   : Combines the channel control.
 * Returns an index for each channel pair.
 *
 *END**************************************************************************/
uint32_t FTM_HAL_GetChnPairIndex(uint8_t channel)
{
    if((channel == CHAN0_IDX) || (channel == CHAN1_IDX))
    {
        return 0;
    }
    else if((channel == CHAN2_IDX) || (channel == CHAN3_IDX))
    {
        return 1;
    }
    else if((channel == CHAN4_IDX) || (channel == CHAN5_IDX))
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

#endif /* FSL_FEATURE_SOC_FTM_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

