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
#include "fsl_aoi_hal.h"

#if FSL_FEATURE_SOC_AOI_COUNT

/*FUNCTION**********************************************************************
 *
 * Function Name : AOI_HAL_Init
 * Description   : This function initializes the module to the reset state.
 * This state is defined in Reference Manual, which is the power on reset value.
 *
 *END**************************************************************************/
void AOI_HAL_Init(AOI_Type* base)
{
    uint32_t i;

    for (i = 0; i < FSL_FEATURE_AOI_EVENT_COUNT; i++)
    {
       /* clear the AOI_BFCRT01n and AOI_BFCRT23n registers for all events */
        AOI_CLR_BFCRT01(base, i, 0xFFFFU);
        AOI_CLR_BFCRT23(base, i, 0xFFFFU);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : AOI_HAL_Reset
 * Description   : This function resets all product term inputs in selected event
 * to a known state. This state is defined in Reference Manual, which is the power on
 * reset value.
 *
 *END**************************************************************************/
void AOI_HAL_Reset(AOI_Type* base, aoi_event_index_t event)
{
    assert(event < FSL_FEATURE_AOI_EVENT_COUNT);

    /* clear the AOI_BFCRT01n and AOI_BFCRT23n registers of desired event */
    AOI_CLR_BFCRT01(base, event, 0xFFFFU);
    AOI_CLR_BFCRT23(base, event, 0xFFFFU);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : AOI_HAL_SetSignalLogicUnit
 * Description   : Defines the Boolean evaluation associated with the selected input in the
 *                 selected product term of the desired event.
 *
 * This function defines the Boolean evaluation associated with the selected input in the selected
 * product term of the desired event.
 *
 *END**************************************************************************/
void AOI_HAL_SetSignalLogicUnit(AOI_Type* base,
                                aoi_event_index_t event,
                                aoi_product_term_t productTerm,
                                aoi_input_signal_index_t input,
                                aoi_input_config_t config)
{
    assert(event < FSL_FEATURE_AOI_EVENT_COUNT);

    uint16_t value;

    /* First, decide if we are programming term 0 and 1 or term 2 and 3 */
    if ((productTerm == kAoiTerm0) || (productTerm == kAoiTerm1))
    {
        /* Program the value for desired input (A, B, C  or C) and term (0 or 1) */
        value = ((AOI_RD_BFCRT01(base, event) & ~(3U << (2U*(3U-input) + 8U*((productTerm+1U)%2U)))) |
                (config << (2U*(3U-input) + 8U*((productTerm+1U)%2U))));

        AOI_WR_BFCRT01(base, event, value);
    }
    else
    {
        /* Program the value for desired input (A, B, C  or C) and term (2 or 3) */
        value = ((AOI_RD_BFCRT23(base, event) & ~(3U << (2U*(3U-input) + 8U*((productTerm+1U)%2U)))) |
                (config << (2U*(3U-input) + 8U*((productTerm+1U)%2U))));

        AOI_WR_BFCRT23(base, event, value);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : AOI_HAL_GetSignalLogicUnit
 * Description   : Gets the Boolean evaluation associated with the selected input in the selected
 *                 product term of the desired event
 *
 * This function returns the Boolean evaluation associated with the selected input in the selected
 * product term of the desired event.
 *
 *END**************************************************************************/
aoi_input_config_t AOI_HAL_GetSignalLogicUnit(AOI_Type* base,
                                              aoi_event_index_t event,
                                              aoi_product_term_t productTerm,
                                              aoi_input_signal_index_t input)
{
    assert(event < FSL_FEATURE_AOI_EVENT_COUNT);

    uint16_t value;

    /* First, decide if we are reading from term 0 and 1 or term 2 and 3 */
    if ((productTerm == kAoiTerm0) || (productTerm == kAoiTerm1))
    {

        value = (AOI_RD_BFCRT01(base, event) >> (2U*(3U-input) + 8U*((productTerm+1U)%2U))) & 3U;
    }
    else
    {
        value = (AOI_RD_BFCRT23(base, event) >> (2U*(3U-input) + 8U*((productTerm+1U)%2U))) & 3U;
    }

    return (aoi_input_config_t)(value);
}


#endif /* FSL_FEATURE_SOC_AOI_COUNT */
/*******************************************************************************
 * EOF
 *******************************************************************************/

