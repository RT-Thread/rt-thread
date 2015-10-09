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
#include "fsl_tpm_hal.h"

#if FSL_FEATURE_SOC_TPM_COUNT

/* Table of number of channels for each TPM instance */
const uint32_t g_tpmChannelCount[TPM_INSTANCE_COUNT] = FSL_FEATURE_TPM_CHANNEL_COUNTx;

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : TPM_HAL_EnablePwmMode
 * Description   : Enables the TPM PWM output mode.
 *
 *END**************************************************************************/
void TPM_HAL_EnablePwmMode(TPM_Type *base, tpm_pwm_param_t *config, uint8_t channel)
{
    uint32_t val;
    tpm_clock_mode_t clkSrc;

    /*
     * Update bit only if change in PWM mode. This code is conditionalized as it requires disabling
     * the counter
     */
    if (TPM_HAL_GetCpwms(base) != (bool)config->mode)
    {
        clkSrc = TPM_HAL_GetClockMode(base);
        /* Disable counter when switching modes */
        TPM_HAL_SetClockMode(base, kTpmClockSourceNoneClk);

        TPM_HAL_SetCpwms(base, config->mode);
        /* Restore the clock source */
        TPM_HAL_SetClockMode(base, clkSrc);
    }

    val = ((uint32_t)(config->edgeMode ? 1 : 2)) << TPM_CnSC_ELSA_SHIFT;
    val |= (2 << TPM_CnSC_MSA_SHIFT);
    TPM_HAL_SetChnMsnbaElsnbaVal(base, channel, val);

    /* Wait till mode change is acknowledged */
    while (!(TPM_HAL_GetChnMsnbaVal(base, channel))) { }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : TPM_HAL_DisableChn
 * Description   : Disables the TPM channel.
 *
 *END**************************************************************************/
void TPM_HAL_DisableChn(TPM_Type *base, uint8_t channel)
{

    TPM_HAL_SetChnMsnbaElsnbaVal(base, channel, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : TPM_HAL_SetClockMode
 * Description   : Set TPM clock mode.
 * When disabling the TPM counter, the function will wait till it receives an
 * acknowledge from the TPM clock domain
 *
 *END**************************************************************************/
void TPM_HAL_SetClockMode(TPM_Type *base, tpm_clock_mode_t mode)
{
    TPM_BWR_SC_CMOD(base, mode);
    if (mode == kTpmClockSourceNoneClk)
    {
        /* Wait till this reads as zero acknowledging the counter is disabled */
        while (TPM_BRD_SC_CMOD(base)) { }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : TPM_HAL_Reset
 * Description   : Reset TPM registers
 *
 *END**************************************************************************/
void TPM_HAL_Reset(TPM_Type *base, uint32_t instance)
{
    uint8_t chan = g_tpmChannelCount[instance];
    int i;

    TPM_WR_SC(base, 0);

    /*instance 1 and 2 only has two channels,0 and 1*/
    for(i = 0; i < chan; i++)
    {
        TPM_WR_CnSC(base, i, 0);
    }

    TPM_WR_STATUS(base, TPM_STATUS_CH0F_MASK | TPM_STATUS_CH1F_MASK | TPM_STATUS_TOF_MASK);
    TPM_WR_CONF(base, 0);
}

#endif /* FSL_FEATURE_SOC_TPM_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

