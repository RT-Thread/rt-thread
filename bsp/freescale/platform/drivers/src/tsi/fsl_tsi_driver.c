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
#include <string.h>
#include "fsl_tsi_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_TSI_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/
extern IRQn_Type tsi_irq_ids[TSI_INSTANCE_COUNT];
extern void TSI_DRV_IRQHandler0(void);
extern const tsi_parameter_limits_t * g_tsiParamLimits[tsi_OpModeCnt];

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_Init
* Description   : Initialize whole the TSI peripheral to be ready to read capacitance changes
* To initialize the TSI driver, the configuration structure should be handled.
*
*END**************************************************************************/
tsi_status_t TSI_DRV_Init(uint32_t instance, tsi_state_t * tsiState, const tsi_user_config_t * tsiUserConfig)
{
    assert(instance < TSI_INSTANCE_COUNT);

    TSI_Type * base = g_tsiBase[instance];
    tsi_state_t * tsiSt = g_tsiStatePtr[instance];

    /* Critical section. */
    OSA_EnterCritical(kCriticalDisableInt);

    /* Exit if current instance is already initialized. */
    if(tsiSt)
    {
        /* End of critical section. */
        OSA_ExitCritical(kCriticalDisableInt);
        return kStatus_TSI_Initialized;
    }
    /* Save runtime structure pointer.*/
    tsiSt = g_tsiStatePtr[instance] = tsiState;

    /* Clear the state structure for this instance. */
    memset(tsiSt, 0, sizeof(tsi_state_t));

    /* Create the mutex used by whole driver. */
    OSA_MutexCreate(&tsiSt->lock);
    /* Create the mutex used by change mode function. */
    OSA_MutexCreate(&tsiSt->lockChangeMode);
    
    /* Critical section. Access to global variable */
    if (kStatus_OSA_Success != OSA_MutexLock(&tsiSt->lock, OSA_WAIT_FOREVER))
    {
        /* End of critical section. */
        OSA_ExitCritical(kCriticalDisableInt);  
        return kStatus_TSI_Error;
    }

    /* End of critical section. */
    OSA_ExitCritical(kCriticalDisableInt);

    tsiSt->opMode = tsi_OpModeNormal;

    tsiSt->opModesData[tsiSt->opMode].config = *tsiUserConfig->config; /* Store the hardware configuration. */

    tsiSt->pCallBackFunc = tsiUserConfig->pCallBackFunc;
    tsiSt->usrData = tsiUserConfig->usrData;
    tsiSt->isBlockingMeasure = false;
    /* Un-gate TSI module clock */
    CLOCK_SYS_EnableTsiClock(instance);

    /* Initialize the interrupt sync object. */
    OSA_SemaCreate(&tsiSt->irqSync, 0);

    TSI_HAL_Init(base);
    TSI_HAL_SetConfiguration(base, &tsiSt->opModesData[tsiSt->opMode].config);
    TSI_HAL_EnableInterrupt(base);
    TSI_HAL_EnableEndOfScanInterrupt(base);
    TSI_HAL_EnableSoftwareTriggerScan(base);

    /* Disable all electrodes */
    tsiState->opModesData[tsiState->opMode].enabledElectrodes = 0;

    /* Enable TSI interrupt on NVIC level. */
    INT_SYS_EnableIRQ(g_tsiIrqId[instance]);

    tsiSt->status = kStatus_TSI_Initialized;

    /* End of critical section. */
    OSA_MutexUnlock(&tsiSt->lock);

    return kStatus_TSI_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_DeInit
* Description   : De initialize whole the TSI peripheral and driver to be ready
* for any future use and don't load the system.
*
*END**************************************************************************/
tsi_status_t TSI_DRV_DeInit(uint32_t instance)
{
    assert(instance < TSI_INSTANCE_COUNT);

    TSI_Type * base = g_tsiBase[instance];
    tsi_state_t * tsiState = g_tsiStatePtr[instance];

    if (tsiState == NULL)
    {
        return kStatus_TSI_Error;
    }

    TSI_HAL_DisableInterrupt(base);
    tsiState->opModesData[tsiState->opMode].enabledElectrodes = 0;
    TSI_HAL_ClearOutOfRangeFlag(base);
    TSI_HAL_ClearEndOfScanFlag(base);
    TSI_HAL_DisableModule(base);

    /* Disable the interrupt */
    INT_SYS_DisableIRQ(g_tsiIrqId[instance]);

    /* Destroy the interrupt synch object*/
    OSA_SemaDestroy(&tsiState->irqSync);

    /* Clear runtime structure pointer.*/
    tsiState = NULL;

    /* Gate TSI module clock */
    CLOCK_SYS_DisableTsiClock(instance);

    return kStatus_TSI_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_SetCallBackFunc
* Description   : Set the TSI call back function pointer for non blocking measurement
*
*
*END**************************************************************************/
tsi_status_t TSI_DRV_SetCallBackFunc(uint32_t instance, const tsi_callback_t pFuncCallBack, void * usrData)
{
    assert(instance < TSI_INSTANCE_COUNT);
    tsi_state_t * tsiState = g_tsiStatePtr[instance];

    /* Critical section. Access to global variable */
    if (kStatus_OSA_Success != OSA_MutexLock(&tsiState->lock, OSA_WAIT_FOREVER))
    {
        return kStatus_TSI_Error;
    }

    if (g_tsiStatePtr[instance]->status != kStatus_TSI_Initialized)
    {
        /* End of critical section. */
        OSA_MutexUnlock(&tsiState->lock);

        return g_tsiStatePtr[instance]->status;
    }

    g_tsiStatePtr[instance]->pCallBackFunc = pFuncCallBack;
    g_tsiStatePtr[instance]->usrData = usrData;

    /* End of critical section. */
    OSA_MutexUnlock(&tsiState->lock);

    return kStatus_TSI_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_GetEnabledElectrodes
* Description   : Get Enables electrodes for measuring.
*
*END**************************************************************************/
uint32_t TSI_DRV_GetEnabledElectrodes(uint32_t instance)
{
    assert(instance < TSI_INSTANCE_COUNT);

    tsi_state_t * tsiState = g_tsiStatePtr[instance];

    return tsiState->opModesData[tsiState->opMode].enabledElectrodes;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_MeasureBlocking
* Description   : This function gets (measure) capacitance of enabled electrodes
*               from the TSI module using a blocking method.
*
*END**************************************************************************/
tsi_status_t TSI_DRV_MeasureBlocking(uint32_t instance)
{
    assert(instance < TSI_INSTANCE_COUNT);
    osa_status_t syncStatus;
    tsi_status_t status;
    tsi_state_t * tsiState = g_tsiStatePtr[instance];

    /* Start the measurement process */
    if ((status = TSI_DRV_Measure(instance)) != kStatus_TSI_Success)
    {
        return status;
    }

    tsiState->isBlockingMeasure = true;

    do
    {
        syncStatus = OSA_SemaWait(&tsiState->irqSync, 1000); /* 1 second timeout. */
    }while(syncStatus == kStatus_OSA_Idle);

    if (syncStatus != kStatus_OSA_Success)
    {
        /* Abort the measurement so it doesn't continue unexpectedly.*/
        TSI_DRV_AbortMeasure(instance);
        return kStatus_TSI_Error;
    }

    return kStatus_TSI_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_AbortMeasure
* Description   : This function aborts possible measure cycle.
*
*END**************************************************************************/
tsi_status_t TSI_DRV_AbortMeasure(uint32_t instance)
{
    assert(instance < TSI_INSTANCE_COUNT);

    TSI_Type * base = g_tsiBase[instance];
    tsi_status_t  status = kStatus_TSI_Success;
    tsi_state_t * tsiState = g_tsiStatePtr[instance];

    /* Critical section. Access to global variable */
    if (kStatus_OSA_Success != OSA_MutexLock(&tsiState->lock, OSA_WAIT_FOREVER))
    {
        return kStatus_TSI_Error;
    }

    if(tsiState->status == kStatus_TSI_Recalibration)
    {
       status = kStatus_TSI_Recalibration;
    }
    else if(tsiState->status != kStatus_TSI_Initialized)
    {
        TSI_HAL_ClearOutOfRangeFlag(base);
        TSI_HAL_ClearEndOfScanFlag(base);
        TSI_HAL_DisableModule(base);

        if(tsiState->isBlockingMeasure)
        {
            /* Signal the synchronous completion object. */
            OSA_SemaPost(&tsiState->irqSync);
            tsiState->isBlockingMeasure = false;
        }

        /* Return status of the driver to initialized state */
        tsiState->status = kStatus_TSI_Initialized;
    }

    /* End of critical section. */
    OSA_MutexUnlock(&tsiState->lock);

    return status;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_IsBusy
* Description   : Function returns the busy state of the driver
*
*END**************************************************************************/
tsi_status_t TSI_DRV_GetStatus(uint32_t instance)
{
    assert(instance < TSI_INSTANCE_COUNT);

    return g_tsiStatePtr[instance]->status;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_Recalibrate
* Description   : The function force the recalibration process of TSI parameters.
*
*END**************************************************************************/
tsi_status_t TSI_DRV_Recalibrate(uint32_t instance, uint32_t * lowestSignal)
{
    assert(instance < TSI_INSTANCE_COUNT);

    TSI_Type * base = g_tsiBase[instance];
    tsi_state_t * tsiState = g_tsiStatePtr[instance];
    
    /* Critical section. Access to global variable */
    if (kStatus_OSA_Success != OSA_MutexLock(&tsiState->lock, OSA_WAIT_FOREVER))
    {
        return kStatus_TSI_Error;
    }

    if (tsiState->status != kStatus_TSI_Initialized)
    {
        /* End of critical section. */
        OSA_MutexUnlock(&tsiState->lock);
        return tsiState->status;
    }

    tsiState->status = kStatus_TSI_Recalibration;

    *lowestSignal = TSI_HAL_Recalibrate(base, &(tsiState->opModesData[tsiState->opMode].config),
                                       tsiState->opModesData[tsiState->opMode].enabledElectrodes,
                                       g_tsiParamLimits[tsiState->opMode]);

    tsiState->status = kStatus_TSI_Initialized;

    /* End of critical section. */
    OSA_MutexUnlock(&tsiState->lock);

    if(*lowestSignal == 0)
    {
      return kStatus_TSI_Error;
    }
    else
    {
      return kStatus_TSI_Success;
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_DisableLowPower
* Description   : Enables/Disables the low power module.
*
*END**************************************************************************/
tsi_status_t TSI_DRV_DisableLowPower(uint32_t instance, const tsi_modes_t mode)
{
    assert(instance < TSI_INSTANCE_COUNT);

    TSI_Type * base = g_tsiBase[instance];
    tsi_state_t * tsiState = g_tsiStatePtr[instance];
    tsi_status_t status;

    /* Critical section. Access to global variable */
    if (kStatus_OSA_Success != OSA_MutexLock(&tsiState->lock, OSA_WAIT_FOREVER))
    {
        return kStatus_TSI_Error;
    }

    if (tsiState->status != kStatus_TSI_LowPower)
    {
        /* End of critical section. */
        OSA_MutexUnlock(&tsiState->lock);

        return tsiState->status;
    }

    TSI_HAL_DisableLowPower(base);
    TSI_HAL_EnableInterrupt(base);
    TSI_HAL_EnableEndOfScanInterrupt(base);
    TSI_HAL_EnableSoftwareTriggerScan(base);

    tsiState->status = kStatus_TSI_Initialized;

    /* End of critical section. */
    OSA_MutexUnlock(&tsiState->lock);

    status = TSI_DRV_ChangeMode(instance, mode);

    return status;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_GetMode
* Description   : Function returns the current mode of the driver
*
*END**************************************************************************/
tsi_modes_t TSI_DRV_GetMode(uint32_t instance)
{
    assert(instance < TSI_INSTANCE_COUNT);

    return g_tsiStatePtr[instance]->opMode;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_SaveConfiguration
* Description   : The function save the configuration for one mode of operation.
*
*END**************************************************************************/
tsi_status_t TSI_DRV_SaveConfiguration(uint32_t instance, const tsi_modes_t mode, tsi_operation_mode_t * operationMode)
{
    assert(instance < TSI_INSTANCE_COUNT);
    assert(operationMode);
    tsi_state_t * tsiState = g_tsiStatePtr[instance];
    
    if(mode >= tsi_OpModeCnt)
    {
        return kStatus_TSI_InvalidMode;
    }

    /* Critical section. Access to global variable */
    if (kStatus_OSA_Success != OSA_MutexLock(&tsiState->lock, OSA_WAIT_FOREVER))
    {
        return kStatus_TSI_Error;
    }

    *operationMode =  tsiState->opModesData[mode];

    /* End of critical section. */
    OSA_MutexUnlock(&tsiState->lock);

    return  kStatus_TSI_Success;
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

