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
#include <string.h>
#include "fsl_xbar_driver.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_XBAR_COUNT

/*! @brief Pointers to internal state structure for XBAR module. */
static xbar_state_t * volatile g_xbarState;

/*FUNCTION********************************************************************* 
 *
 * Function Name : XBAR_DRV_Init
 * Description   : Initialize the XBAR module to the reset state. This API 
 * should be called before any operation of the XBAR module. 
 *
 *END*************************************************************************/
xbar_status_t XBAR_DRV_Init(xbar_state_t * xbarStatePtr)
{     
    XBARA_Type * xbara_base = g_xbaraBase[0];
    
    g_xbarState = xbarStatePtr;
    
    /* Clear the state structure. */
    memset(xbarStatePtr, 0, sizeof(xbar_state_t));
    
    CLOCK_SYS_EnableXbarClock(XBARA_MODULE);     

    XBARA_HAL_Init(xbara_base);
    
#if !defined(FSL_FEATURE_XBAR_HAS_SINGLE_MODULE)
    XBARB_Type * xbarb_base = g_xbarbBase[0];
    CLOCK_SYS_EnableXbarClock(XBARB_MODULE);
    
    XBARB_HAL_Init(xbarb_base);
#endif /* FSL_FEATURE_XBAR_HAS_SINGLE_MODULE */       
        
    /* Enable XBAR interrupt on NVIC level. */
    INT_SYS_EnableIRQ(g_xbarIrqId[XBARA_MODULE]);
    
    return kStatus_XBAR_Success;
}

/*FUNCTION********************************************************************* 
 *
 * Function Name : XBAR_DRV_Control_Config
 * Description   : This function configures the XBAR module control register 
 * of selected XBAR_OUT output. Control fields provide the ability to perform 
 * edge detection on the corresponding XBAR_OUT output. Edge detection in turn
 * can optionally be used to trigger an interrupt or DMA request. The intention 
 * is that, by detecting specified edges on signals propagating through the 
 * Crossbar, interrupts or DMA requests can be triggered to perform data 
 * transfers to or from other system components. DENn and IENn should not be set
 * to 1 at the same time for the same output XBAR_OUT[n].  
 *
 *END*************************************************************************/
xbar_status_t XBAR_DRV_ConfigOutControl(uint32_t outIndex, const xbar_control_config_t * controlConfigPtr)
{
    XBARA_Type * xbara_base = g_xbaraBase[0];
    
    /* Set active edge for edge detection. */
    XBARA_HAL_SetOutActiveEdge(xbara_base, outIndex, controlConfigPtr->activeEdge);
     
    /* Set interrupt or DMA function. */
    if(controlConfigPtr->intDmaReq == kXbarReqIen)
    {
        XBARA_HAL_SetDMAOutCmd(xbara_base, outIndex, false); 
        XBARA_HAL_SetIntOutCmd(xbara_base, outIndex, true); 
    }
    else if(controlConfigPtr->intDmaReq == kXbarReqDen)
    {
        XBARA_HAL_SetIntOutCmd(xbara_base, outIndex, false);
        XBARA_HAL_SetDMAOutCmd(xbara_base, outIndex, true);  
    }
    else
    {
        XBARA_HAL_SetIntOutCmd(xbara_base, outIndex, false);
        XBARA_HAL_SetDMAOutCmd(xbara_base, outIndex, false);
    }
    
    return kStatus_XBAR_Success;
}

/*FUNCTION********************************************************************* 
 *
 * Function Name : XBAR_DRV_Deinit
 * Description   : De-initialize the XBAR module. It shuts down XBAR module 
 * clock to reduce the power consumption and resets XBAR's registers to a known 
 * state. 
 *
 *END*************************************************************************/
void XBAR_DRV_Deinit(void)
{
    XBARA_Type * xbara_base = g_xbaraBase[0];
    
    /* Cleared state pointer. */ 
    g_xbarState = NULL; 
    
    /* Disable XBAR interrupt on NVIC level. */
    INT_SYS_DisableIRQ(g_xbarIrqId[0]);
          
    /*Initialize module to reset state - clears all configurations*/
     XBARA_HAL_Init(xbara_base);

     /* Disable XBARB module clock */
     CLOCK_SYS_DisableXbarClock(XBARA_MODULE);
     
#if !defined(FSL_FEATURE_XBAR_HAS_SINGLE_MODULE) 
  
     XBARB_Type * xbarb_base = g_xbarbBase[0];
          
     /*Initialize module to reset state - clears all configurations*/
     XBARB_HAL_Init(xbarb_base);
         
     /* Disable XBARB module clock */
     CLOCK_SYS_DisableXbarClock(XBARB_MODULE);   
#endif /* FSL_FEATURE_XBAR_HAS_SINGLE_MODULE */
}

/*FUNCTION********************************************************************* 
 *
 * Function Name : XBAR_DRV_ConfigSignalConnection
 * Description   : This function configures connections between XBAR_IN[*]
 * and XBAR_OUT[*] signals. 
 *
 *END*************************************************************************/
xbar_status_t XBAR_DRV_ConfigSignalConnection(xbar_input_signal_t input, xbar_output_signal_t output)
{   
 
    if(((uint32_t)input & (1U<<8U)) && ((uint32_t)output & (1U<<8U)))
    {
        XBARA_Type * xbara_base = g_xbaraBase[0];
        uint32_t outputA = ((uint32_t)output & ~(1U<<8U));
        uint32_t inputA = ((uint32_t)input & ~(1U<<8U));
        XBARA_HAL_SetOutSel(xbara_base, outputA, inputA);
        return kStatus_XBAR_Success;
    }

#if !defined(FSL_FEATURE_XBAR_HAS_SINGLE_MODULE) 
    else if(((uint32_t)input & (1U<<9U)) && ((uint32_t)output & (1U<<9U)))
    {
        XBARB_Type * xbarb_base = g_xbarbBase[0];
        uint32_t outputB = ((uint32_t)output & ~(1U<<9U));
        uint32_t inputB = ((uint32_t)input & ~(1U<<9U));
        XBARB_HAL_SetOutSel(xbarb_base, outputB, inputB);
        return kStatus_XBAR_Success;
    }
#endif /* FSL_FEATURE_XBAR_HAS_SINGLE_MODULE */    
    else
    {
        return kStatus_XBAR_InvalidArgument;
    }  
}

/*FUNCTION*********************************************************************
 *
 * Function Name : XBAR_DRV_GetEdgeDetectionStatus
 * Description   : Get the active edge detection status of selected output.
 * If the active edge occurs, the return value will be asserted. When interrupt
 * or DMA functionality is enabled for XBAR_OUTx, this field is 1 when the 
 * interrupt or DMA request is asserted and 0 when the interrupt or DMA request
 * has been cleared.
 *
 *END*************************************************************************/
bool XBAR_DRV_GetEdgeDetectionStatus(uint32_t outIndex)
{
    XBARA_Type * xbara_base = g_xbaraBase[0];

    return XBARA_HAL_GetEdgeDetectionStatus(xbara_base, outIndex);
   
}

/*FUNCTION*********************************************************************
 *
 * Function Name : XBAR_DRV_ClearEdgeDetectionStatus
 * Description   : Clear the edge detection status of selected output.
 * This field is cleared by this function or by DMA_ACKx reception when DENx
 * is set.
 *
 *END*************************************************************************/
xbar_status_t XBAR_DRV_ClearEdgeDetectionStatus(uint32_t outIndex)
{
    XBARA_Type * xbara_base = g_xbaraBase[0];
  
    XBARA_HAL_ClearEdgeDetectionStatus(xbara_base, outIndex);
    
    return kStatus_XBAR_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : XBAR_DRV_InstallCallback
 * Description   : Install the user-defined callback in XBAR module.
 * When an XBAR interrupt request is served, the callback will be executed 
 * inside the ISR.
 *
 *END*************************************************************************/
xbar_status_t XBAR_DRV_InstallCallback(uint32_t outIndex, xbar_callback_t userCallback, void * callbackParam)
{
    if(outIndex >= FSL_FEATURE_XBARA_INTERRUPT_COUNT)
    {
        return kStatus_XBAR_InvalidArgument;
    }
    
    xbar_state_t * xbarState = (xbar_state_t *)g_xbarState; 
    xbarState->userCallbackFunct[outIndex] = userCallback;
    xbarState->xbarCallbackParam[outIndex] = callbackParam;
    
    return kStatus_XBAR_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : XBAR_DRV_IRQHandler
 * Description   : Driver-defined ISR in XBAR module. 
 * This is not a public API as it is called whenever an interrupt occurs.
 *
 *END**************************************************************************/
void XBAR_DRV_IRQHandler(void)
{
    XBARA_Type * xbara_base = g_xbaraBase[0];
    xbar_state_t* stateOutput = g_xbarState;
    
    uint32_t outIndex;
    
    for(outIndex = 0; outIndex < FSL_FEATURE_XBARA_INTERRUPT_COUNT; outIndex++)
    {  
        if(XBARA_HAL_GetIntOutCmd(xbara_base, outIndex))
        {
            if(XBARA_HAL_GetEdgeDetectionStatus(xbara_base, outIndex))
            {
                /* Execute the user-defined callback function. */
                if (stateOutput->userCallbackFunct[outIndex])
                {
                    (*(stateOutput->userCallbackFunct[outIndex]))(stateOutput->xbarCallbackParam[outIndex]);
                }
        
                /* Make sure the flags are cleared. */
                XBARA_HAL_ClearEdgeDetectionStatus(xbara_base, outIndex);
            }
        }
    }
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

