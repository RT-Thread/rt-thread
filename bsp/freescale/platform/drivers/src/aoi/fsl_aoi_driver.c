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
#include "fsl_aoi_driver.h"
#include "fsl_clock_manager.h"

#if FSL_FEATURE_SOC_AOI_COUNT

/*FUNCTION*********************************************************************
 *
 * Function Name : AOI_DRV_Init
 * Description   : Initialize the AOI module to the reset state.
 * This API should be called before any operation of the AOI module.
 *
 *END*************************************************************************/
aoi_status_t AOI_DRV_Init(uint32_t instance)
{
    AOI_Type* base = g_aoiBase[instance];

    /* Enable the clock gate from clock manager. */
    bool mEnable = CLOCK_SYS_GetAoiGateCmd(0);
    if (!mEnable)
    {
        CLOCK_SYS_EnableAoiClock(0);
    }

    /* Init registers of the AOI module to the reset state. */
    AOI_HAL_Init(base);

    return kStatus_AOI_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AOI_DRV_Deinit
 * Description   : De-initialize the AOI module. It shuts down the AOI module
 * clock to reduce the power consumption and resets the registers configuration.
 *
 *END*************************************************************************/
aoi_status_t AOI_DRV_Deinit(uint32_t instance)
{
    AOI_Type* base = g_aoiBase[instance];

    /*Get module to the reset state - clears all configurations*/
    AOI_HAL_Init(base);

    /*Disable clock to the AOI module*/
    CLOCK_SYS_DisableAoiClock(0);

    return kStatus_AOI_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AOI_DRV_ConfigEventLogic
 * Description   : Configures selected event output of the AOI module. It will configure
 * the event output of the AOI module itself according the eventConfig structure.
 * This function configures all of the inputs (A, B, C, and D)
 * of all of the product terms (0, 1, 2, and 3) of a desired event.
 *
 *END*************************************************************************/
aoi_status_t AOI_DRV_ConfigEventLogic(uint32_t instance,
                                      aoi_event_index_t event,
                                      const aoi_event_config_t * eventConfigPtr)
{
    AOI_Type* base = g_aoiBase[instance];

    if(!eventConfigPtr)
    {
        return kStatus_AOI_InvalidArgument;
    }

    /* Set the selected AOI module event registers according eventConfigPtr target structure */
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm0, kAoiInputA, eventConfigPtr->PT0AC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm0, kAoiInputB, eventConfigPtr->PT0BC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm0, kAoiInputC, eventConfigPtr->PT0CC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm0, kAoiInputD, eventConfigPtr->PT0DC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm1, kAoiInputA, eventConfigPtr->PT1AC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm1, kAoiInputB, eventConfigPtr->PT1BC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm1, kAoiInputC, eventConfigPtr->PT1CC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm1, kAoiInputD, eventConfigPtr->PT1DC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm2, kAoiInputA, eventConfigPtr->PT2AC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm2, kAoiInputB, eventConfigPtr->PT2BC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm2, kAoiInputC, eventConfigPtr->PT2CC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm2, kAoiInputD, eventConfigPtr->PT2DC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm3, kAoiInputA, eventConfigPtr->PT3AC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm3, kAoiInputB, eventConfigPtr->PT3BC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm3, kAoiInputC, eventConfigPtr->PT3CC);
    AOI_HAL_SetSignalLogicUnit(base, event, kAoiTerm3, kAoiInputD, eventConfigPtr->PT3DC);

    return kStatus_AOI_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AOI_DRV_ConfigProductTermLogic
 * Description   : Configuration of one of the AOI module product term in a specific event.
 * This function configures one of the AOI module product terms for a specific event. The user has
 * to select the event and the product term which will be configured and fill the
 * AoiProductTermConfig configuration structure.
 *
 *END*************************************************************************/
aoi_status_t AOI_DRV_ConfigProductTermLogic(uint32_t instance,
                                            aoi_event_index_t event,
                                            aoi_product_term_t productTerm,
                                            const aoi_product_term_config_t * productTermConfigPtr)
{
    AOI_Type* base = g_aoiBase[instance];

    if(!productTermConfigPtr)
    {
        return kStatus_AOI_InvalidArgument;
    }

    /* Set the selected AOI module event product term registers according eventConfigPtr target
     * structure
     */
    AOI_HAL_SetSignalLogicUnit(base, event, productTerm, kAoiInputA, productTermConfigPtr->PTAC);
    AOI_HAL_SetSignalLogicUnit(base, event, productTerm, kAoiInputB, productTermConfigPtr->PTBC);
    AOI_HAL_SetSignalLogicUnit(base, event, productTerm, kAoiInputC, productTermConfigPtr->PTCC);
    AOI_HAL_SetSignalLogicUnit(base, event, productTerm, kAoiInputD, productTermConfigPtr->PTDC);

    return kStatus_AOI_Success;
}

#endif /* FSL_FEATURE_SOC_AOI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

