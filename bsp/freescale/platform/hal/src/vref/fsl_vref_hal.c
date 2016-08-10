/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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
#include "fsl_vref_hal.h"
#if FSL_FEATURE_SOC_VREF_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : VREF_HAL_Init
 * Description   : This function initializes the module to a default state.
 *
 *END**************************************************************************/
void VREF_HAL_Init(VREF_Type * base)
{
    VREF_BWR_SC_VREFEN(base, true);
    VREF_BWR_SC_REGEN(base, true);
    VREF_BWR_TRM_TRIM(base, 0x00);
    VREF_BWR_SC_MODE_LV(base, kVrefModeBandgapOnly);

#if FSL_FEATURE_VREF_HAS_COMPENSATION
    VREF_BWR_SC_ICOMPEN(base, true);
#endif

#if FSL_FEATURE_VREF_HAS_CHOP_OSC
    VREF_BWR_TRM_CHOPEN(base, true);
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : VREF_HAL_Configure
 * Description   : This function configures the module to a known state.
 *
 *END**************************************************************************/
void VREF_HAL_Configure(VREF_Type * base, const vref_user_config_t *userConfigPtr)
{
#if FSL_FEATURE_VREF_MODE_LV_TYPE
    assert(userConfigPtr->bufferMode <= kVrefModeLowPowerBuffer);
#else
    assert(userConfigPtr->bufferMode <= kVrefModeTightRegulationBuffer);
#endif
    assert(userConfigPtr->trimValue <= 0x3F);

#if FSL_FEATURE_VREF_HAS_CHOP_OSC
    VREF_BWR_TRM_CHOPEN(base, userConfigPtr->chopOscEnable);
#endif
    VREF_BWR_SC_REGEN(base, userConfigPtr->regulatorEnable);
#if FSL_FEATURE_VREF_HAS_COMPENSATION
    VREF_BWR_SC_ICOMPEN(base, userConfigPtr->soccEnable);
#endif
    VREF_BWR_SC_MODE_LV(base, userConfigPtr->bufferMode);
    VREF_BWR_TRM_TRIM(base, userConfigPtr->trimValue);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
