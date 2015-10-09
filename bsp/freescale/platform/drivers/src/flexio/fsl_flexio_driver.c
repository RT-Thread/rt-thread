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

#include "fsl_flexio_driver.h"
#include "fsl_flexio_hal.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_FLEXIO_COUNT
/*******************************************************************************
 * Variables
 ******************************************************************************/
flexio_shifter_callback_t shifterIntCallback[FLEXIO_INSTANCE_COUNT][FLEXIO_SHIFTBUF_COUNT];
/*FUNCTION*********************************************************************
 *
 * Function Name : FLEXIO_DRV_Init
 * Description   : Initialize the flexio module before using flexio module.
 *
 *END*************************************************************************/
flexio_status_t FLEXIO_DRV_Init(uint32_t instance, const flexio_user_config_t *userConfigPtr)
{
    FLEXIO_Type* base = g_flexioBase[instance];
    if (!userConfigPtr)
    {
        return kStatus_FLEXIO_InvalidArgument;
    }

    /* Enable the clock gate for FlexIO. */
    CLOCK_SYS_EnableFlexioClock(instance);
    
    /* Reset the FlexIO hardware. */
    FLEXIO_HAL_Init(g_flexioBase[instance]);
    
    /* Disable the FlexIO mode during configure. */
    FLEXIO_DRV_Pause(instance);

    /* Configure the FlexIO's work mode. */
    FLEXIO_HAL_SetDozeModeCmd(base, userConfigPtr->onDozeEnable);
    FLEXIO_HAL_SetDebugModeCmd(base, userConfigPtr->onDebugEnable);
    FLEXIO_HAL_SetFastAccessCmd(base, userConfigPtr->fastAccessEnable);
    
    /* Switch on/off the interrupt in NVIC. */
    if (userConfigPtr->useInt)
    {
        /* Enable the NVIC for FlexIO. */
        INT_SYS_EnableIRQ(g_flexioIrqId[instance]);
    }
    else
    {
        /* Disable the NVIC for FlexIO. */
        INT_SYS_DisableIRQ(g_flexioIrqId[instance]);
    }
    
    return kStatus_FLEXIO_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : FLEXIO_DRV_Start
 * Description   : Enable the flexio's working after configuring the flexio devices. 
 *
 *END*************************************************************************/
void FLEXIO_DRV_Start(uint32_t instance)
{
    FLEXIO_Type* base = g_flexioBase[instance];
    FLEXIO_HAL_SetFlexioEnableCmd(base, true);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : FLEXIO_DRV_Pause
 * Description   : Disable the flexio's work during configuring the flexio devices.
 *
 *END*************************************************************************/
void FLEXIO_DRV_Pause(uint32_t instance)
{
    FLEXIO_Type* base = g_flexioBase[instance];
    FLEXIO_HAL_SetFlexioEnableCmd(base, false);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : FLEXIO_DRV_RegisterCallback
 * Description   : Register the callback function into shifter interrupt.
 *
 *END*************************************************************************/
void FLEXIO_DRV_RegisterCallback(uint32_t instance, uint32_t shifterId,
                           flexio_shifter_int_handler_t shifterIntHandler,
                           void *param)
{
    shifterIntCallback[instance][shifterId].shifterIntHandler = shifterIntHandler;
    shifterIntCallback[instance][shifterId].param = param;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : FLEXIO_DRV_Deinit
 * Description   : Deinitialize the flexio module.
 *
 *END*************************************************************************/
flexio_status_t FLEXIO_DRV_Deinit(uint32_t instance)
{
    /* Switch off the interrupt in NVIC. */
    INT_SYS_DisableIRQ(g_flexioIrqId[instance]);
    /* Disable the clock gate for FlexIO. */
    CLOCK_SYS_DisableFlexioClock(instance);

    return kStatus_FLEXIO_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_DRV_IRQHandler
 * Description   : Interrupt handler for FLEXIO.
 * This handler polls the shifter status and call the corresponding handler to
 * handle the shifter status.
 *
 *END**************************************************************************/
void FLEXIO_DRV_IRQHandler(uint32_t instance)
{
    uint32_t shifterMask,shifterNum,shifterStatus,shifterErr,tmp,shifterInt;
    shifterNum = FLEXIO_HAL_GetShifterNumber(g_flexioBase[instance]);
    shifterStatus = FLEXIO_HAL_GetShifterStatusFlags(g_flexioBase[instance]);
    shifterErr = FLEXIO_HAL_GetShifterErrorFlags(g_flexioBase[instance]);
    shifterInt = FLEXIO_HAL_GetShifterStatusIntCmd(g_flexioBase[instance]);
    if(shifterStatus)
    {
        for(shifterMask = 0; shifterMask < shifterNum; shifterMask++)
        {
            tmp = 1<<shifterMask;
            if(shifterStatus&tmp)
            {
                if(shifterInt&tmp)
                {
                shifterIntCallback[instance][shifterMask].shifterIntHandler(shifterIntCallback[instance][shifterMask].param);
                break;
                }
            }
        }
    }
    if(shifterErr)
    {
        for(shifterMask = 0; shifterMask < shifterNum; shifterMask++)
        {
            tmp = 1<<shifterMask;
            if(shifterErr&tmp)
            {
                FLEXIO_HAL_ClearShifterErrorFlags(g_flexioBase[instance],1<<shifterMask);
            }
        }
    }
}

#endif

/******************************************************************************
 * EOF
 *****************************************************************************/

