/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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
 
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#include "fsl_cmt_driver.h"

#if FSL_FEATURE_SOC_CMT_COUNT
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Define global value for CMT data modulation*/
//cmt_modulate_data_t  *cmtDataSend[CMT_INSTANCE_COUNT] = {NULL};

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_Init
 * Description   : Initialize CMT module.
 * This function must be called before calling all the other CMT driver functions.
 * This function un-gates the CMT clock, setting the CMT clock, interrupt 
 * and output signal for CMT module. 
 *
 *END**************************************************************************/
cmt_status_t CMT_DRV_Init(uint32_t instance, const cmt_base_config_t * config)
{
    uint32_t clkDiv;

    assert(instance < CMT_INSTANCE_COUNT);

    CMT_Type * base = g_cmtBase[instance];

    /* Un-gate cmt clock*/
    CLOCK_SYS_EnableCmtClock(instance);

    /* Reset the CMT module*/
    CMT_HAL_Init(base); 
    
    /* Configure NVIC*/
    if (config->isInterruptEnabled)
    {
        /* Enable CMT interrupt.*/
        INT_SYS_EnableIRQ(g_cmtIrqId[instance]);
    }
    
    /* Gets the clock primary divider to generate the clock approximately to 8MHZ*/
    clkDiv = CLOCK_SYS_GetCmtFreq(instance)/CMT_INTERMEDIATEFREQUENCY_8MHZ;
    if(!clkDiv)
    {
        return kStatus_CMT_Fail;
    }

    /* Sets clock divider*/
    CMT_HAL_SetClkByDiv(base, (cmt_primary_clkdiv_t)(clkDiv - 1), config->cmtDivider);

    /* Enable or disable interrupt.*/
    CMT_HAL_SetIntCmd(base, config->isInterruptEnabled);

    /* Control the IRO signal*/
    CMT_HAL_SetIroCmd(base,  config->isIroEnabled);
    CMT_HAL_SetIroPol(base, config->iroPolarity);

    return kStatus_CMT_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_Deinit 
 * Description   : Disable CMT module and gate control
 * This function will disable all CMT interrupts and CMT module. 
 * CMT_DRV_Init must be called in order to use CMT again.
 * 
 *END**************************************************************************/
cmt_status_t CMT_DRV_Deinit(uint32_t instance)
{
    assert(instance < CMT_INSTANCE_COUNT);

    CMT_Type * base = g_cmtBase[instance];

    /* Disable all CMT interrupts. */
    CMT_HAL_SetIntCmd(base, false);
    INT_SYS_DisableIRQ(g_cmtIrqId[instance]);

    /* Disable CMT carrier generator and modulator*/
    CMT_DRV_SetMode(instance, kCMTDirectIROCtl);

    /* Gate CMT clock control*/
    CLOCK_SYS_DisableCmtClock(instance);

    return kStatus_CMT_Success;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_StartCarrierModulate 
 * Description   : Enables and Starts the modulator and carrier generator. 
 * CMT_DRV_Init should be called before this function. 
 * 
 *END**************************************************************************/
void CMT_DRV_StartCarrierModulate(uint32_t instance, cmt_modulate_config_t *modulateConfig, 
                              cmt_modulate_data_t *cmtData, bool isMsbMode)
{
    assert(instance < CMT_INSTANCE_COUNT);
    assert(modulateConfig->mode > kCMTDirectIROCtl);

    CMT_Type * base = g_cmtBase[instance];

    /* Sets the carrier generator counter*/
    CMT_HAL_SetCGCountOne(base,  modulateConfig->highCount1,  modulateConfig->lowCount1);

    /* The second carrier generator counter is used for FSK mode*/
    if( kCMTFSKMode == modulateConfig->mode)
    {
      CMT_HAL_SetCGCountTwo(base,  modulateConfig->highCount2,  modulateConfig->lowCount2);    
    }

    /* Sets the Modulator mark and space time*/
    CMT_HAL_SetModulateMarkCount(base,  modulateConfig->markCount);
    CMT_HAL_SetModulateSpaceCount(base, modulateConfig->spaceCount);

    if(cmtData)
    /* cover the Modulator mark and space counter with the first transmitted data*/
    {
      CMT_DRV_ModulateDataByBit(instance, cmtData, isMsbMode);   
    }

    /* Configures the CMT mode*/
    CMT_HAL_SetMode(base, modulateConfig->mode);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_StopCarrierModulate 
 * Description   : Stops the CMT carrier generator and modulator
 * This function stops and disables the CMT carrier generator and modulator.
 * When the CMT carrier generator and modulator is disabled, the IRO signal
 * can be controlled directly by calling CMT_DRV_SetIroCtl.
 * 
 *END**************************************************************************/
void CMT_DRV_StopCarrierModulate(uint32_t instance)
{
    CMT_DRV_SetMode(instance, kCMTDirectIROCtl);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_ModulateDataByBit 
 * Description   : CMT data modulation by one bit. This can be called by the  
 * CMT ISR handler to do data modulation. Reload the new mark and space time period
 * to modulator data registers, according to the one data bit "1" or bit "0" at the 
 * end of the current modulation cycle by CMT end-of-cycle ISR handler.
 * 
 *END**************************************************************************/
cmt_status_t CMT_DRV_ModulateDataByBit(uint32_t instance, cmt_modulate_data_t *cmtData, bool isMsbMode)
{
    assert(instance < CMT_INSTANCE_COUNT);

    CMT_Type * base = g_cmtBase[instance];   

    if(cmtData->len)
    {
        if(isMsbMode)
        {
            if(* (cmtData->data)  & 0x80)
            {
                CMT_HAL_SetModulateMarkCount(base,  cmtData->markOne);
                CMT_HAL_SetModulateSpaceCount(base, cmtData->spaceOne);    
            }
            else
            {
                CMT_HAL_SetModulateMarkCount(base,  cmtData->markZero);
                CMT_HAL_SetModulateSpaceCount(base, cmtData->spaceZero);  
            }

            /* Data updates*/
            *(cmtData->data) = *(cmtData->data) << 1;
            cmtData->len --;
            cmtData->lenDone ++;
            if(!(cmtData->lenDone % CMT_MODULATEUNIT8BITS))
            {
              cmtData->data ++; 
            }
        }
        else
        {
            if(* (cmtData->data)  & 0x1)
            {
                CMT_HAL_SetModulateMarkCount(base,  cmtData->markOne);
                CMT_HAL_SetModulateSpaceCount(base, cmtData->spaceOne);    
            }
            else
            {
                CMT_HAL_SetModulateMarkCount(base,  cmtData->markZero);
                CMT_HAL_SetModulateSpaceCount(base, cmtData->spaceZero);  
            }

            /* Data updates*/
            *(cmtData->data) = *(cmtData->data) >> 1;
            cmtData->len --;
            cmtData->lenDone ++;
            if(!(cmtData->lenDone % CMT_MODULATEUNIT8BITS))
            {
              cmtData->data ++; 
            }      
        }

        return kStatus_CMT_Process;
    }
    else
    {
        return kStatus_CMT_Done;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_SetMode 
 * Description   : Selects the mode for CMT module.
 * 
 *END**************************************************************************/
void CMT_DRV_SetMode(uint32_t instance, cmt_mode_t mode)
{    
    assert(instance < CMT_INSTANCE_COUNT);

    CMT_Type * base = g_cmtBase[instance]; 

    CMT_HAL_SetMode(base, mode);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_GetMode 
 * Description   : Gets the mode of CMT module
 * This function returns the mode of the CMT module.
 * 
 *END**************************************************************************/
cmt_mode_t CMT_DRV_GetMode(uint32_t instance)
{
    assert(instance < CMT_INSTANCE_COUNT);

    CMT_Type * base = g_cmtBase[instance]; 
 
    return CMT_HAL_GetMode(base);
} 


/*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_SetClockDiv
 * Description   : Sets CMT clock divider.
 * 
 *END**************************************************************************/
void CMT_DRV_SetClockDiv(uint32_t instance, cmt_second_clkdiv_t spsDiv)
{
    assert(instance < CMT_INSTANCE_COUNT);

    CMT_Type * base = g_cmtBase[instance];
    uint32_t ppsDiv;

    /* Calculates the primary prescaler divider*/
    ppsDiv = CLOCK_SYS_GetCmtFreq(instance)/CMT_INTERMEDIATEFREQUENCY_8MHZ;
    /* Sets the CMT Clock dividers*/
    CMT_HAL_SetClkByDiv(base, (cmt_primary_clkdiv_t)(ppsDiv - 1), spsDiv);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_GetCmtIFClock
 * Description   : Gets CMT intermediate frequency.
 * 
 *END**************************************************************************/
uint32_t CMT_DRV_GetCmtIFClock(uint32_t instance)
{
    assert(instance < CMT_INSTANCE_COUNT);

    CMT_Type * base = g_cmtBase[instance];

    return CLOCK_SYS_GetCmtFreq(instance)/(CMT_HAL_GetPriClkDiv(base) + 1);
}

 /*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_IsEndofCycle
 * Description   : Reads the current End of cycle flag
 * 
 *END**************************************************************************/
bool CMT_DRV_IsEndofCycle(uint32_t instance)
{
    assert(instance < CMT_INSTANCE_COUNT);

    CMT_Type *base = g_cmtBase[instance];

    return CMT_HAL_IsEndofCycle(base);
}

 /*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_ClearEndofCycleFlag
 * Description   : Clears the end of cycle status flag by reading the MSC followed by
 * and access of the lower eight bit of the modulator mark counter or space counter.
 * 
 *END**************************************************************************/
void CMT_DRV_ClearEndofCycleFlag(uint32_t instance, uint32_t markCount)
{
    assert(instance < CMT_INSTANCE_COUNT);

    CMT_Type * base = g_cmtBase[instance];

    CMT_HAL_IsEndofCycle(base);
    CMT_HAL_SetModulateMarkCount(base, markCount);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_SetModulateMarkCount
 * Description   : Sets the modulator mark period counter.
 *
 *END**************************************************************************/
void CMT_DRV_SetModulateMarkCount(uint32_t instance, uint32_t markCount)
{
    assert(instance < CMT_INSTANCE_COUNT);

    CMT_Type * base = g_cmtBase[instance];
    CMT_HAL_SetModulateMarkCount(base, markCount);  
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_SetModulateSpaceCount
 * Description   : Sets the modulator space period counter.
 *
 *END**************************************************************************/
void CMT_DRV_SetModulateSpaceCount(uint32_t instance, uint32_t spaceCount)
{
    assert(instance < CMT_INSTANCE_COUNT);

    CMT_Type * base = g_cmtBase[instance];

    CMT_HAL_SetModulateSpaceCount(base, spaceCount);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_SetIroCtl
 * Description   : Sets the states of the IRO signal. This function is valid only  
 * when the kCMTDirectIROMode mode is set and the IRO signal is enabled.
 *
 *END**************************************************************************/

void CMT_DRV_SetIroCtl(uint32_t instance, cmt_iro_ctl_t ctlVal)
{
    assert(instance < CMT_INSTANCE_COUNT);

    CMT_Type * base = g_cmtBase[instance];

    CMT_HAL_SetIroCtl(base, ctlVal);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CMT_DRV_GetIrolatchState
 * Description   : Gets the states of the IRO signal.
 *
 *END**************************************************************************/
bool CMT_DRV_GetIrolatchState(uint32_t instance)
{
    assert(instance < CMT_INSTANCE_COUNT);

    CMT_Type * base = g_cmtBase[instance];

    return CMT_HAL_GetIrolatchState(base);

}

#endif /* FSL_FEATURE_SOC_CMT_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

