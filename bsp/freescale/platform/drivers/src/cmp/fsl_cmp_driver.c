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

#include "assert.h"
#include "fsl_cmp_driver.h"
#include "fsl_cmp_hal.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_CMP_COUNT

/*! @brief Table of pointers to internal state structure for CMP instances. */
static cmp_state_t * volatile g_cmpStatePtr[CMP_INSTANCE_COUNT];

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_DRV_StructInitUserConfigDefault
 * Description   :  Fill initial user configuration for default setting. 
 * The default setting will make the CMP module at least to be an comparator.
 * It includes the setting of :
 *     .hystersisMode = kCmpHystersisOfLevel0
 *     .pinoutEnable = true
 *     .pinoutUnfilteredEnable = true
 *     .invertEnable = false
 *     .highSpeedEnable = false
 *     .dmaEnable = false
 *     .risingIntEnable = false
 *     .fallingIntEnable = false
 *     .triggerEnable = false
 * However, it is still recommended to fill some fields of structure such as
 * channel mux according to application. Note that this API will not set the
 * configuration to hardware.
 *
 *END*************************************************************************/
cmp_status_t CMP_DRV_StructInitUserConfigDefault(cmp_comparator_config_t *userConfigPtr,
    cmp_chn_mux_mode_t plusInput, cmp_chn_mux_mode_t minusInput)
{
    if (!userConfigPtr)
    {
        return kStatus_CMP_InvalidArgument;
    }

    userConfigPtr->hystersisMode = kCmpHystersisOfLevel0;
    userConfigPtr->pinoutEnable = true;
    userConfigPtr->pinoutUnfilteredEnable = false;
    userConfigPtr->invertEnable = false;
    userConfigPtr->highSpeedEnable = false;
#if FSL_FEATURE_CMP_HAS_DMA
    userConfigPtr->dmaEnable = false;
#endif /* FSL_FEATURE_CMP_HAS_DMA */
    userConfigPtr->risingIntEnable = false;
    userConfigPtr->fallingIntEnable = false;
    userConfigPtr->plusChnMux = plusInput;
    userConfigPtr->minusChnMux = minusInput;
#if FSL_FEATURE_CMP_HAS_TRIGGER_MODE
    userConfigPtr->triggerEnable = false;
#endif /* FSL_FEATURE_CMP_HAS_TRIGGER_MODE */

    return kStatus_CMP_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_DRV_Init
 * Description   : Initialize the CMP module. It will enable the clock and
 * set the interrupt switcher for CMP module. And the CMP module will be
 * configured for the basic comparator.
 *
 *END*************************************************************************/
cmp_status_t CMP_DRV_Init(uint32_t instance, cmp_state_t *userStatePtr,
    const cmp_comparator_config_t *userConfigPtr)
{

    assert(instance < CMP_INSTANCE_COUNT);
    CMP_Type * base = g_cmpBase[instance];

    if ( (!userConfigPtr) || (!userStatePtr) )
    {
        return kStatus_CMP_InvalidArgument;
    }

    /* Enable clock for CMP. */
    if (!CLOCK_SYS_GetCmpGateCmd(instance) )
    {
        CLOCK_SYS_EnableCmpClock(instance);
    }

    /* Reset all the registers. */
    CMP_HAL_Init(base);
    CMP_HAL_ConfigComparator(base, userConfigPtr);

    /* Configure the NVIC. */
    if ( (userConfigPtr->risingIntEnable) || (userConfigPtr->fallingIntEnable) )
    {
        /* Enable the CMP interrupt in NVIC. */
        INT_SYS_EnableIRQ(g_cmpIrqId[instance] );
    }
    else
    {
        /* Disable the CMP interrupt in NVIC. */
        INT_SYS_DisableIRQ(g_cmpIrqId[instance] );
    }

    userStatePtr->isInUsed = true; /* Mark it as in used. */
    g_cmpStatePtr[instance] = userStatePtr; /* Linked the user-provided memory into context record. */

    return kStatus_CMP_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_DRV_Deinit
 * Description   : De-initialize the CMP module. It will shutdown the CMP's
 * clock and disable the interrupt. This API should be called when CMP is no
 * longer used in application and it will help to reduce the power consumption.
 *
 *END*************************************************************************/
cmp_status_t CMP_DRV_Deinit(uint32_t instance)
{
    assert(instance < CMP_INSTANCE_COUNT);

    uint32_t i;
    CMP_Type * base = g_cmpBase[instance];

    /* Be sure to disable the CMP module. */
    CMP_HAL_Disable(base);
    CMP_HAL_Init(base);

    /* Disable the CMP interrupt in NVIC. */
    INT_SYS_DisableIRQ(g_cmpIrqId[instance] );

    /* Unmask the CMP not in use. */
    g_cmpStatePtr[instance]->isInUsed = false;

    /* Disable the clock if necessary. */
    for (i = 0U; i < CMP_INSTANCE_COUNT; i++)
    {
        if ( (g_cmpStatePtr[i]) && (g_cmpStatePtr[i]->isInUsed) )
        {
            /* There are still some CMP instances in used. */
            break;
        }
    }
    if (i == CMP_INSTANCE_COUNT)
    {
        /* Disable the shared clock. */
        CLOCK_SYS_DisableCmpClock(instance);
    }
    
    g_cmpStatePtr[instance] = NULL;

    return kStatus_CMP_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_DRV_Start
 * Description   : Start the CMP module. The configuration would not take
 * effect until the module is started.
 *
 *END*************************************************************************/
void CMP_DRV_Start(uint32_t instance)
{
    assert(instance < CMP_INSTANCE_COUNT);
    
    CMP_Type * base = g_cmpBase[instance];
    CMP_HAL_Enable(base);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_DRV_Stop
 * Description   : Stop the CMP module. Note that this API would shutdown
 * the module, but only pauses the features tenderly.
 *
 *END*************************************************************************/
void CMP_DRV_Stop(uint32_t instance)
{
    assert(instance < CMP_INSTANCE_COUNT);
    
    CMP_Type * base = g_cmpBase[instance];
    CMP_HAL_Disable(base);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_DRV_ConfigDacChn
 * Description   : Enable the internal DAC in CMP module. It will take
 * effect actually only when internal DAC has been chosen as one of input
 * channel for comparator. Then the DAC channel can be programmed to provide
 * a reference voltage level.
 *
 *END*************************************************************************/
cmp_status_t CMP_DRV_ConfigDacChn(uint32_t instance, const cmp_dac_config_t *dacConfigPtr)
{
    assert(instance < CMP_INSTANCE_COUNT);
    CMP_Type * base = g_cmpBase[instance];

    if (!dacConfigPtr)
    {
        return kStatus_CMP_InvalidArgument;
    }
    /* Configure the DAC Control Register. */
    CMP_HAL_ConfigDacChn(base, dacConfigPtr);

    return kStatus_CMP_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_DRV_ConfigSampleFilter
 * Description   : Configure the CMP working in Sample\Filter modes. These
 * modes are some advanced features beside the basic comparator. They may
 * be about Windowed Mode, Filter Mode and so on. See to 
 * "cmp_sample_filter_config_t" for detailed description.
 *
 *END*************************************************************************/
cmp_status_t CMP_DRV_ConfigSampleFilter(uint32_t instance, const cmp_sample_filter_config_t *configPtr)
{
    assert(instance < CMP_INSTANCE_COUNT);
    CMP_Type * base = g_cmpBase[instance];
    
    if (!configPtr)
    {
        return kStatus_CMP_InvalidArgument;
    }
    CMP_HAL_ConfigSampleFilter(base, configPtr);

    return kStatus_CMP_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_DRV_GetOutputLogic
 * Description   : Get the output of CMP module.
 * The output source depends on the configuration when initializing the comparator.
 * When cmp_user_config_t.pinoutUnfilteredEnable = false, the output will be
 * processed by filter. Otherwise, the output would be the signal did not pass
 * the filter.
 *
 *END*************************************************************************/
bool CMP_DRV_GetOutputLogic(uint32_t instance)
{
    assert(instance < CMP_INSTANCE_COUNT);
    CMP_Type * base = g_cmpBase[instance];
    
    return CMP_HAL_GetOutputLogic(base);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_DRV_GetFlag
 * Description   : Get the state of CMP module. It will return if indicated
 * event has been detected.
 *
 *END*************************************************************************/
bool CMP_DRV_GetFlag(uint32_t instance, cmp_flag_t flag)
{
    assert(instance < CMP_INSTANCE_COUNT);

    bool bRet;
    CMP_Type * base = g_cmpBase[instance];

    switch(flag)
    {
    case kCmpFlagOfCoutRising:
        bRet = CMP_HAL_GetOutputRisingFlag(base);
        break;
    case kCmpFlagOfCoutFalling:
        bRet = CMP_HAL_GetOutputFallingFlag(base);
        break;
    default:
        bRet = false;
        break;
    }
    return bRet;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_DRV_ClearFlag
 * Description   : Clear event record of CMP module. 
 *
 *END*************************************************************************/
void CMP_DRV_ClearFlag(uint32_t instance, cmp_flag_t flag)
{
    assert(instance < CMP_INSTANCE_COUNT);

    CMP_Type * base = g_cmpBase[instance];

    switch(flag)
    {
    case kCmpFlagOfCoutRising:
        CMP_HAL_ClearOutputRisingFlag(base);
        break;
    case kCmpFlagOfCoutFalling:
        CMP_HAL_ClearOutputFallingFlag(base);
        break;
    default:
        break;
    }
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

