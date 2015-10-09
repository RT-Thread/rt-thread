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

#include "fsl_ewm_driver.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_EWM_COUNT

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 *******************************************************************************/

/*FUNCTION****************************************************************
 *
 * Function Name : EWM_DRV_Init
 * Description   : Initialize EWM
 * This function is used to initialize the EWM, after called, the EWM 
 * will run immediately according to the configure.
 *
 *END*********************************************************************/
ewm_status_t EWM_DRV_Init(uint32_t instance, const ewm_config_t* ConfigPtr)
{
    assert(instance < EWM_INSTANCE_COUNT);
    EWM_Type * base;
    base = g_ewmBase[instance];
    if(!ConfigPtr)
    {
	return kStatus_EWM_NullArgument;
    }
    if(ConfigPtr->intEnable)
    {
        INT_SYS_EnableIRQ(g_ewmIrqId[instance]);    /*!< Enable EWM interrupt in NVIC level  */
    }
    else
    {
        INT_SYS_DisableIRQ(g_ewmIrqId[instance]);   /*!< Disable EWM interrupt in NVIC level */
    }
    CLOCK_SYS_EnableEwmClock(instance);             /*!< Enable ewm clock 					 */
    EWM_HAL_SetConfig(base, ConfigPtr);
    
    return kStatus_EWM_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name : EWM_DRV_Deinit
 * Description   : Shutdown EWM clock
 * This function is used to shut down the EWM.
 *
 *END*********************************************************************/
void EWM_DRV_Deinit(uint32_t instance)
{
    assert(instance < EWM_INSTANCE_COUNT);
    EWM_Type * base = g_ewmBase[instance];
    EWM_HAL_SetIntCmd(base, false);
    CLOCK_SYS_DisableEwmClock(instance);
}

/*FUNCTION****************************************************************
 *
 * Function Name : EWM_DRV_IsRunning
 * Description   : Get EWM running status
 * This function is used to get the EWM running status.
 *
 *END*********************************************************************/
bool EWM_DRV_IsRunning(uint32_t instance)
{
    assert(instance < EWM_INSTANCE_COUNT);
    EWM_Type * base = g_ewmBase[instance];
    return EWM_HAL_IsEnable(base);
}

/*FUNCTION****************************************************************
 *
 * Function Name : EWM_DRV_Refresh
 * Description   : Refresh EWM counter.
 * This function is used to feed the EWM, it will set the EWM timer count to zero and 
 * should be called before EWM timer is timeout, otherwise a EWM_out output signal will assert.
 *
  *END*********************************************************************/
void EWM_DRV_Refresh(uint32_t instance)
{
    assert(instance < EWM_INSTANCE_COUNT);
    EWM_Type * base;
    base = g_ewmBase[instance];
    INT_SYS_DisableIRQGlobal();
    EWM_HAL_Refresh(base);
    INT_SYS_EnableIRQGlobal();
}

/*FUNCTION*********************************************************************
 *
 * Function Name : EWM_DRV_SetIntCmd
 * Description   : Enables/disables EWM interrupt
 *END*************************************************************************/
void EWM_DRV_SetIntCmd(uint32_t instance, bool enable)
{
    EWM_Type * base;
    base = g_ewmBase[instance];
    EWM_HAL_SetIntCmd(base, enable);
}

#endif
/*******************************************************************************
 * EOF
 *******************************************************************************/

