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

/*******************************************************************************
 * Variables
 ******************************************************************************/

const tsi_parameter_limits_t g_tsiParamLimits[tsi_OpModeCnt] =
{
    /* Normal operation mode. */
    {
        /* consNumberOfScan */
        {
            /* upper */
            kTsiConsecutiveScansNumber_32time,
            /* lower */
            kTsiConsecutiveScansNumber_1time
        },
        /* refOscChargeCurrent */
        {
            /* upper */
            kTsiRefOscChargeCurrent_32uA,
            /* lower */
            kTsiRefOscChargeCurrent_2uA
        },
        /* extOscChargeCurrent */
        {
            /* upper */
            kTsiExtOscChargeCurrent_32uA,
            /* lower */
            kTsiExtOscChargeCurrent_2uA
        },
        /* activeModePrescaler */
        {
            /* upper */
            kTsiActiveModePrescaler_1div,
            /* lower */
            kTsiActiveModePrescaler_128div
        }
    },
    /* Proximity operation mode. */
    {
        /* consNumberOfScan */
        {
            /* upper */
            kTsiConsecutiveScansNumber_32time,
            /* lower */
            kTsiConsecutiveScansNumber_1time
        },
        /* refOscChargeCurrent */
        {
            /* upper */
            kTsiRefOscChargeCurrent_32uA,
            /* lower */
            kTsiRefOscChargeCurrent_2uA
        },
        /* extOscChargeCurrent */
        {
            /* upper */
            kTsiExtOscChargeCurrent_32uA,
            /* lower */
            kTsiExtOscChargeCurrent_2uA
        },
        /* activeModePrescaler */
        {
            /* upper */
            kTsiActiveModePrescaler_1div,
            /* lower */
            kTsiActiveModePrescaler_128div
        }
    },
    /* Low Power operation mode. */
    {
        /* consNumberOfScan */
        {
            /* upper */
            kTsiConsecutiveScansNumber_32time,
            /* lower */
            kTsiConsecutiveScansNumber_1time
        },
        /* refOscChargeCurrent */
        {
            /* upper */
            kTsiRefOscChargeCurrent_32uA,
            /* lower */
            kTsiRefOscChargeCurrent_2uA
        },
        /*extOscChargeCurrent */
        {
            /* upper */
            kTsiExtOscChargeCurrent_32uA,
            /* lower */
            kTsiExtOscChargeCurrent_2uA
        },
        /* activeModePrescaler */
        {
            /* upper */
            kTsiActiveModePrescaler_1div,
            /* lower */
            kTsiActiveModePrescaler_128div
        }
    }
};

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_EnableElectrode
* Description   : Enables/Disables the electrode for measuring.
*
*END**************************************************************************/
tsi_status_t TSI_DRV_EnableElectrode(uint32_t instance, const uint32_t channel, const bool enable)
{
    assert(instance < TSI_INSTANCE_COUNT);
    assert(channel < FSL_FEATURE_TSI_CHANNEL_COUNT);

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

    /* Check the condition for low power mode. */
    if((tsiState->opMode == tsi_OpModeLowPower) || (tsiState->opMode == tsi_OpModeProximity))
    {
      if(tsiState->opModesData[tsi_OpModeLowPower].enabledElectrodes != 0)
      {
          /* Only one elctrode can be enabled in low power mode and proximity. */

          /* Disable al previous enabled. */
          TSI_HAL_DisableChannels(base, 0xffffffff);
      }
    }

    if(enable)
    {
        tsiState->opModesData[tsiState->opMode].enabledElectrodes |= (1U << channel);
        TSI_HAL_EnableChannel(base, channel);
    }
    else
    {
        tsiState->opModesData[tsiState->opMode].enabledElectrodes &= ~(1U << channel);
        TSI_HAL_DisableChannel(base, channel);
    }

    /* End of critical section. */
    OSA_MutexUnlock(&tsiState->lock);

    return kStatus_TSI_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_GetCounter
* Description   : Function returns the counter value of selected channel
*
*END**************************************************************************/
tsi_status_t TSI_DRV_GetCounter(uint32_t instance, const uint32_t channel, uint16_t * counter)
{
    assert(instance < TSI_INSTANCE_COUNT);
    assert(channel < FSL_FEATURE_TSI_CHANNEL_COUNT);
    assert(counter);

    TSI_Type * base = g_tsiBase[instance];
    tsi_state_t * tsiState = g_tsiStatePtr[instance];

    if(!TSI_HAL_GetEnabledChannel(base, channel))
    {
        return kStatus_TSI_InvalidChannel;
    }

    *counter = tsiState->counters[channel];

    return kStatus_TSI_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_Measure
* Description   : This function gets (measure) capacitance of enabled electrodes
*               from the TSI module using a non-blocking method.
*
*END**************************************************************************/
tsi_status_t TSI_DRV_Measure(uint32_t instance)
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

    tsiState->status = kStatus_TSI_Busy;

    /* End of critical section. */
    OSA_MutexUnlock(&tsiState->lock);

    TSI_HAL_DisableModule(base);
    TSI_HAL_EnableSoftwareTriggerScan(base);
    TSI_HAL_EnableModule(base);
    TSI_HAL_StartSoftwareTrigger(base);

    return kStatus_TSI_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_EnableLowPower
* Description   : Enables/Disables the low power module.
*
*END**************************************************************************/
tsi_status_t TSI_DRV_EnableLowPower(uint32_t instance)
{
    assert(instance < TSI_INSTANCE_COUNT);

    TSI_Type * base = g_tsiBase[instance];
    tsi_state_t * tsiState = g_tsiStatePtr[instance];
    tsi_status_t status;
    uint32_t i;
    int32_t channel = -1;

    /* Critical section. Access to global variable */
    if (kStatus_OSA_Success != OSA_MutexLock(&tsiState->lock, OSA_WAIT_FOREVER))
    {
        return kStatus_TSI_Error;
    }

   if((tsiState->opModesData[tsiState->opMode].config.thresl == 0) || (tsiState->opModesData[tsiState->opMode].config.thresh == 0))
    {
        /* End of critical section. */
        OSA_MutexUnlock(&tsiState->lock);

        return kStatus_TSI_Error;
    }

    if ((status = TSI_DRV_ChangeMode(instance, tsi_OpModeLowPower)) != kStatus_TSI_Success)
    {
        /* End of critical section. */
        OSA_MutexUnlock(&tsiState->lock);

        return status;
    }

    if(tsiState->opModesData[tsiState->opMode].enabledElectrodes == 0)
    {
        /* End of critical section. */
        OSA_MutexUnlock(&tsiState->lock);

        return kStatus_TSI_InvalidChannel;
    }

    for(i = 0; i < FSL_FEATURE_TSI_CHANNEL_COUNT; i++)
    {
        if((uint32_t)(1 << i) & tsiState->opModesData[tsiState->opMode].enabledElectrodes)
        {
            channel = i;
            break;
        }
    }
    
    if(channel == -1)
    {
        /* End of critical section. */
        OSA_MutexUnlock(&tsiState->lock);

        return kStatus_TSI_InvalidChannel;  
    }
    
    tsiState->status = kStatus_TSI_LowPower;
    
    /* Configurate the peripheral for next use */
    TSI_HAL_EnableOutOfRangeInterrupt(base);
    TSI_HAL_EnablePeriodicalScan(base);
    TSI_HAL_SetLowPowerChannel(base, channel);
    TSI_HAL_EnableLowPower(base);
    TSI_HAL_EnableInterrupt(base);
    TSI_HAL_EnableModule(base);

    /* End of critical section. */
    OSA_MutexUnlock(&tsiState->lock);

    return kStatus_TSI_Success;
}


/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_ChangeMode
* Description   : The function change the current mode.
*
*END**************************************************************************/
tsi_status_t TSI_DRV_ChangeMode(uint32_t instance, const tsi_modes_t mode)
{
    assert(instance < TSI_INSTANCE_COUNT);

    TSI_Type * base = g_tsiBase[instance];
    tsi_state_t * tsiState = g_tsiStatePtr[instance];

    if((mode == tsiState->opMode) || (mode == tsi_OpModeNoChange))
    {
        return  kStatus_TSI_Success;
    }

    if(mode >= tsi_OpModeNoise) /* Neither the noise mode is not supported in TSIv1&2 revision. */
    {
        return kStatus_TSI_InvalidMode;
    }

    /* Critical section. Access to global variable */
    if (kStatus_OSA_Success != OSA_MutexLock(&tsiState->lockChangeMode, OSA_WAIT_FOREVER))
    {
        return kStatus_TSI_Error;
    }

    if (tsiState->status != kStatus_TSI_Initialized)
    {
        /* End of critical section. */
        OSA_MutexUnlock(&tsiState->lockChangeMode);
        return tsiState->status;
    }

    tsiState->opMode = mode;

    TSI_HAL_SetConfiguration(base, &tsiState->opModesData[mode].config);

    /* Disable all electrodes */
    TSI_HAL_DisableChannels(base, 0xffff);

    /* Enable the set electrodes for current operation mode */
    TSI_HAL_EnableChannels(base, tsiState->opModesData[mode].enabledElectrodes);

    /* End of critical section. */
    OSA_MutexUnlock(&tsiState->lockChangeMode);

    return  kStatus_TSI_Success;
}


/*FUNCTION**********************************************************************
*
* Function Name : TSI_DRV_LoadConfiguration
* Description   : The function load the configuration for one mode of operation.
*
*END**************************************************************************/
tsi_status_t TSI_DRV_LoadConfiguration(uint32_t instance, const tsi_modes_t mode, const tsi_operation_mode_t * operationMode)
{
    assert(instance < TSI_INSTANCE_COUNT);
    assert(operationMode);
    TSI_Type * base;
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

    tsiState->opModesData[mode] = *operationMode;

    /* In case that the loaded configuration is active one, update the HW also. */
    if(mode == tsiState->opMode)
    {
        base = g_tsiBase[instance];

        TSI_HAL_SetConfiguration(base, &tsiState->opModesData[mode].config);

        /* Disable all electrodes */
        TSI_HAL_DisableChannels(base, 0xffff);

        /* Enable the set electrodes for current operation mode */
        TSI_HAL_EnableChannels(base, tsiState->opModesData[mode].enabledElectrodes);

        TSI_HAL_EnableInterrupt(base);
        TSI_HAL_EnableEndOfScanInterrupt(base);
    }

    /* End of critical section. */
    OSA_MutexUnlock(&tsiState->lock);

    return  kStatus_TSI_Success;
}

/*!
 * @brief Interrupt handler for TSI.
 * This handler uses the tsi State structure to handle the instance depend data.
 * This is not a public API as it is called whenever an interrupt occurs.
 */
void TSI_DRV_IRQHandler(uint32_t instance)
{
    TSI_Type * base = g_tsiBase[instance];
    uint32_t channels = TSI_HAL_GetEnabledChannels(base);
    uint32_t i;
    tsi_state_t * tsiState = g_tsiStatePtr[instance];
    /* Check if a measure is running and wanted. */

    if(tsiState->status != kStatus_TSI_Busy)
    {
        return;
    }

    TSI_HAL_ClearOutOfRangeFlag(base);
    TSI_HAL_ClearEndOfScanFlag(base);

    for(i = 0; i < FSL_FEATURE_TSI_CHANNEL_COUNT; i++)
    {
        if((uint32_t)(1 << i) & channels)
        {
            tsiState->counters[i] = TSI_HAL_GetCounter(base, i);
        }
    }


    if(tsiState->isBlockingMeasure)
    {
        /* Signal the synchronous completion object. */
        OSA_SemaPost(&tsiState->irqSync);
        tsiState->isBlockingMeasure = false;
    }
    else if(tsiState->pCallBackFunc)
    {
        tsiState->pCallBackFunc(instance, tsiState->usrData);
    }

    if(tsiState->status != kStatus_TSI_LowPower)
    {
        /* Return status of the driver to initialized state */
        tsiState->status = kStatus_TSI_Initialized;
    }
}

#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

