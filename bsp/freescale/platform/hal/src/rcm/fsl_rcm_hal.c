/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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

#include "fsl_rcm_hal.h"
#if FSL_FEATURE_SOC_RCM_COUNT


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : RCM_HAL_GetSrcStatusCmd
 * Description   : Get the reset source status
 * 
 * This function will get the current reset source status for specified source
 *
 *END**************************************************************************/
uint32_t RCM_HAL_GetSrcStatus(RCM_Type * base, uint32_t statusMask)
{
    uint32_t regStatus = 0U;  // RCM_SRS register status.

    /* There are only SRS0 and SRS1. */
    regStatus  = ((uint32_t)RCM_RD_SRS0(base));
    regStatus |= ((uint32_t)RCM_RD_SRS1(base) << 8U);

    if (kRcmSrcAll == statusMask)
    {
        return regStatus;
    }
    else
    {
        return regStatus & statusMask;
    }
}

#if FSL_FEATURE_RCM_HAS_SSRS
/*FUNCTION**********************************************************************
 *
 * Function Name : RCM_HAL_GetStickySrcStatus
 * Description   : Get the sticy reset source status
 *
 * This function gets the current reset source status that have not been cleared
 * by software for a specified source.
 *
 *END**************************************************************************/
uint32_t RCM_HAL_GetStickySrcStatus(RCM_Type * base, uint32_t statusMask)
{
    uint32_t regStatus = 0U;  // RCM_SRS register status.

    /* There are only SRS0 and SRS1. */
    regStatus  = ((uint32_t)RCM_RD_SSRS0(base));
    regStatus |= ((uint32_t)RCM_RD_SSRS1(base) << 8U);

    if (kRcmSrcAll == statusMask)
    {
        return regStatus;
    }
    else
    {
        return regStatus & statusMask;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : RCM_HAL_ClearStickySrcStatus
 * Description   : Clear the sticy reset source status
 *
 * This function clears all the sticky system reset flags.
 *
 *END**************************************************************************/
void RCM_HAL_ClearStickySrcStatus(RCM_Type * base)
{
    uint8_t status;

    status = RCM_RD_SSRS0(base);
    RCM_WR_SSRS0(base, status);
    status = RCM_RD_SSRS1(base);
    RCM_WR_SSRS1(base, status);
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : RCM_HAL_SetResetPinFilterConfig
 * Description   : Sets the reset pin filter.
 *
 *END**************************************************************************/
void RCM_HAL_SetResetPinFilterConfig(RCM_Type * base, rcm_reset_pin_filter_config_t *config)
{
    // Set filter in stop mode.
    RCM_BWR_RPFC_RSTFLTSS(base, config->filterInStop);

    // Set filter width if bus clock is used as filter.
    if (kRcmFilterBusClk == config->filterInRunWait)
    {
        RCM_BWR_RPFW_RSTFLTSEL(base, config->busClockFilterCount);
    }

    // Set filter in run and wait mode.
    RCM_BWR_RPFC_RSTFLTSRW(base, config->filterInRunWait);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

