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

#include <assert.h>
#include "fsl_pdb_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_PDB_COUNT

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_Init
 * Description   : Initialize the PDB counter and trigger input for PDB module.
 * It resets PDB registers and enables the clock for PDB. So it should be 
 * called before any operation to PDB module. After initialized, the PDB can
 * ack as a triggered timer, which lays the foundation for other features in
 * PDB module.
 *
 *END*************************************************************************/
pdb_status_t PDB_DRV_Init(uint32_t instance, const pdb_timer_config_t *userConfigPtr)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];

    if (!userConfigPtr)
    {
        return kStatus_PDB_InvalidArgument;
    }
    /* Enable the clock gate from clock manager. */
    CLOCK_SYS_EnablePdbClock(instance);

    /* Reset the registers for PDB module to reset state. */
    PDB_HAL_Init(base);
    PDB_HAL_Enable(base);
    PDB_HAL_ConfigTimer(base, userConfigPtr);

    /* Configure NVIC. */
    if (userConfigPtr->intEnable)
    {
        INT_SYS_EnableIRQ(g_pdbIrqId[instance] );/* Enable PDB interrupt in NVIC level.*/
    }
    else
    {
        INT_SYS_DisableIRQ(g_pdbIrqId[instance] );/* Disable PDB interrupt in NVIC level.*/
    }

    return kStatus_PDB_Success;
}


/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_Deinit
 * Description   : De-initialize the PDB module.
 * When the PDB module is not used. Calling this function would shutdown the 
 * PDB module and reduce the power consumption.
 *
 *END*************************************************************************/
pdb_status_t PDB_DRV_Deinit(uint32_t instance)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];

    INT_SYS_DisableIRQ( g_pdbIrqId[instance] );
    PDB_HAL_Disable(base);
    CLOCK_SYS_DisablePdbClock(instance);

    return kStatus_PDB_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_SoftTriggerCmd
 * Description   : Trigger PDB by software trigger. 
 * When the PDB is set to use software trigger as input, Calling this function
 * would trigger the PDB.
 *
 *END*************************************************************************/
void PDB_DRV_SoftTriggerCmd(uint32_t instance)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];

    PDB_HAL_SetSoftTriggerCmd(base);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_GetTimerValue
 * Description   : Get the current counter value in PDB module.
 *
 *END*************************************************************************/
uint32_t PDB_DRV_GetTimerValue(uint32_t instance)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];

    return PDB_HAL_GetTimerValue(base);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_GetTimerIntFlag
 * Description   : Get the interrupt flag for PDB module. It will be
 * asserted if the PDB interrupt occurs.
 *
 *END*************************************************************************/
bool PDB_DRV_GetTimerIntFlag(uint32_t instance)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];

    return PDB_HAL_GetTimerIntFlag(base);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_ClearTimerIntFlag
 * Description   : Clear the interrupt flag for PDB module.
 *
 *END*************************************************************************/
void PDB_DRV_ClearTimerIntFlag(uint32_t instance)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];

    PDB_HAL_ClearTimerIntFlag(base);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_LoadValuesCmd
 * Description   : Execute the command of loading values.
 *
 *END*************************************************************************/
void PDB_DRV_LoadValuesCmd(uint32_t instance)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];

    PDB_HAL_SetLoadValuesCmd(base);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_SetTimerModulusValue
 * Description   : Set the value of timer modulus.
 *
 *END*************************************************************************/
void PDB_DRV_SetTimerModulusValue(uint32_t instance, uint32_t value)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];
    
    PDB_HAL_SetTimerModulusValue(base, value);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_SetValueForTimerInterrupt
 * Description   : Set the value for the timer interrupt.
 *
 *END*************************************************************************/
void PDB_DRV_SetValueForTimerInterrupt(uint32_t instance, uint32_t value)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];
    
    PDB_HAL_SetValueForTimerInterrupt(base, value);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_ConfigAdcPreTrigger
 * Description   : Configure the ADC pre_trigger in the PDB module.
 *
 *END*************************************************************************/
pdb_status_t PDB_DRV_ConfigAdcPreTrigger(uint32_t instance, uint32_t chn, const pdb_adc_pretrigger_config_t *configPtr)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];
    
    if (!configPtr)
    {
        return kStatus_PDB_InvalidArgument; 
    }
    
    PDB_HAL_SetAdcPreTriggerEnable(base, chn, 1U << (configPtr->adcPreTriggerIdx), configPtr->preTriggerEnable);
    PDB_HAL_SetAdcPreTriggerOutputEnable(base, chn, 1U << (configPtr->adcPreTriggerIdx), configPtr->preTriggerOutputEnable);
    PDB_HAL_SetAdcPreTriggerBackToBackEnable(base, chn, 1U << (configPtr->adcPreTriggerIdx), configPtr->preTriggerBackToBackEnable);
    
    return kStatus_PDB_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_GetAdcPreTriggerFlags
 * Description   : Get the ADC pre_trigger flag in the PDB module.
 *
 *END*************************************************************************/
uint32_t PDB_DRV_GetAdcPreTriggerFlags(uint32_t instance, uint32_t chn, uint32_t preChnMask)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];
    
    return PDB_HAL_GetAdcPreTriggerFlags(base, chn, preChnMask);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_ClearAdcPreTriggerFlags
 * Description   : Clear the ADC pre_trigger flag in the PDB module.
 *
 *END*************************************************************************/
void PDB_DRV_ClearAdcPreTriggerFlags(uint32_t instance, uint32_t chn, uint32_t preChnMask)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];
    
    PDB_HAL_ClearAdcPreTriggerFlags(base, chn, preChnMask);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_GetAdcPreTriggerSeqErrFlags
 * Description   : Get the ADC pre_trigger flag in the PDB module.
 *
 *END*************************************************************************/
uint32_t PDB_DRV_GetAdcPreTriggerSeqErrFlags(uint32_t instance, uint32_t chn, uint32_t preChnMask)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];
    
    return PDB_HAL_GetAdcPreTriggerSeqErrFlags(base, chn, preChnMask);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_ClearAdcPreTriggerSeqErrFlags
 * Description   : Clear the ADC pre_trigger flag in the PDB module.
 *
 *END*************************************************************************/
void PDB_DRV_ClearAdcPreTriggerSeqErrFlags(uint32_t instance, uint32_t chn, uint32_t preChnMask)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];

    PDB_HAL_ClearAdcPreTriggerSeqErrFlags(base, chn, preChnMask);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_SetAdcPreTriggerDelayValue
 * Description   : Set the ADC pre_trigger delay value in the PDB module.
 *
 *END*************************************************************************/
void PDB_DRV_SetAdcPreTriggerDelayValue(uint32_t instance, uint32_t chn, uint32_t preChn, uint32_t value)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];
    
    PDB_HAL_SetAdcPreTriggerDelayValue(base, chn, preChn, value);
}

#if FSL_FEATURE_PDB_HAS_DAC
/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_ConfigDacInterval
 * Description   : Configure the DAC interval in the PDB module.
 *
 *END*************************************************************************/
pdb_status_t PDB_DRV_ConfigDacInterval(uint32_t instance, uint32_t dacChn, const pdb_dac_interval_config_t *configPtr)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];
    
    if (!configPtr)
    {
        return kStatus_PDB_InvalidArgument; 
    }
    
    PDB_HAL_SetDacIntervalTriggerEnable(base, dacChn, configPtr->intervalTriggerEnable);
    PDB_HAL_SetDacExtTriggerInputEnable(base, dacChn, configPtr->extTriggerInputEnable);
    
    return kStatus_PDB_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_SetDacIntervalValue
 * Description   : Set the DAC interval value in the PDB module.
 *
 *END*************************************************************************/
void PDB_DRV_SetDacIntervalValue(uint32_t instance, uint32_t dacChn, uint32_t value)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];
    
    PDB_HAL_SetDacIntervalValue(base, dacChn, value);
}

#endif

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_SetCmpPulseOutEnable
 * Description   : Switch on/off the CMP pulse out in the PDB module.
 *
 *END*************************************************************************/
void PDB_DRV_SetCmpPulseOutEnable(uint32_t instance, uint32_t pulseChnMask, bool enable)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];
    
    PDB_HAL_SetCmpPulseOutEnable(base, pulseChnMask, enable);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_SetCmpPulseOutDelayForHigh
 * Description   : Set the CMP pulse out delay value for high in the PDB module.
 *
 *END*************************************************************************/
void PDB_DRV_SetCmpPulseOutDelayForHigh(uint32_t instance, uint32_t pulseChn, uint32_t value)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];
    
    PDB_HAL_SetCmpPulseOutDelayForHigh(base, pulseChn, value);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_DRV_SetCmpPulseOutDelayForLow
 * Description   : Set the CMP pulse out delay value for low in the PDB module.
 *
 *END*************************************************************************/
void PDB_DRV_SetCmpPulseOutDelayForLow(uint32_t instance, uint32_t pulseChn, uint32_t value)
{
    assert(instance < PDB_INSTANCE_COUNT);
    PDB_Type * base = g_pdbBase[instance];
    
    PDB_HAL_SetCmpPulseOutDelayForLow(base, pulseChn, value);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
