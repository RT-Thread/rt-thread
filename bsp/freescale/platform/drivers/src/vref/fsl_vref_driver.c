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

#include <assert.h>
#include "fsl_vref_driver.h"
#include "fsl_vref_hal.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_VREF_COUNT

/*FUNCTION*********************************************************************
 *
 * Function Name : VREF_DRV_Init
 * Description   : Initialize the comparator in VREF module.
 *
 *END*************************************************************************/
vref_status_t VREF_DRV_Init(uint32_t instance, const vref_user_config_t *userConfigPtr)
{
    assert(instance < VREF_INSTANCE_COUNT);
    VREF_Type * base = (VREF_Type *)g_vrefBase[instance];

    if (!userConfigPtr)
    {
        return kStatus_VREF_InvalidArgument;
    }

    /* Enable clock for VREF. */
    CLOCK_SYS_EnableVrefClock(instance);

    /* Reset all the register to default state. */
    VREF_HAL_Init(base);
    /* Configure VREF to a known state*/
    VREF_HAL_Configure(base, userConfigPtr);

    VREF_HAL_WaitVoltageStable(base);

    return kStatus_VREF_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : VREF_DRV_Deinit
 * Description   : De-initialize the comparator in VREF module. It will gate
 * the clock to VREF module. When VREF is no long used in application, calling
 * this API will shut down the device to reduce power consumption.
 *
 *END*************************************************************************/
vref_status_t VREF_DRV_Deinit(uint32_t instance)
{
    assert(instance < VREF_INSTANCE_COUNT);
    VREF_Type * base = (VREF_Type *)g_vrefBase[instance];

    VREF_HAL_Disable(base);

    /* Disable clock for ADC. */
    CLOCK_SYS_DisableVrefClock(instance);

    return kStatus_VREF_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : VREF_DRV_SetTrimValue
 * Description   : Set TRIM bits value
 *
 *END*************************************************************************/
vref_status_t VREF_DRV_SetTrimValue(uint32_t instance, uint8_t trimValue)
{
    assert(instance < VREF_INSTANCE_COUNT);
    VREF_Type * base = (VREF_Type *)g_vrefBase[instance];

    VREF_HAL_SetTrimVal(base, trimValue);

    VREF_HAL_WaitVoltageStable(base);

    return kStatus_VREF_Success;
}

#if FSL_FEATURE_VREF_HAS_LOW_REFERENCE
/*FUNCTION*********************************************************************
 *
 * Function Name : VREF_DRV_SetTrimValue
 * Description   : Set TRIM bits value
 *
 *END*************************************************************************/
vref_status_t VREF_DRV_SetLowReferenceTrimVal(uint32_t instance, uint8_t trimValue)
{
    assert(instance < VREF_INSTANCE_COUNT);
    VREF_Type * base = (VREF_Type *)g_vrefBase[instance];

    VREF_HAL_SetLowReferenceTrimVal(base, trimValue);

    VREF_HAL_WaitVoltageStable(base);

    return kStatus_VREF_Success;
}
#endif
#endif

/******************************************************************************
 * EOF
 *****************************************************************************/

