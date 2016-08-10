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
   
#include <assert.h>
#include <string.h>
#include "fsl_mmau_driver.h"
#include "fsl_interrupt_manager.h"


/*FUNCTION********************************************************************* 
 *
 * Function Name : MMAU_DRV_Init
 * Description   : Initialize the MMAU module according to the userConfig 
 * structure. This API should be called before any operation of the MMAU module. 
 *
 *END*************************************************************************/
mmau_status_t MMAU_DRV_Init(mmau_user_config_t * userConfigPtr)
{       
    MMAU_HAL_Init(MMAU);
    
    MMAU_HAL_Config(MMAU, userConfigPtr);
      
    /* Enable MMAU interrupt on NVIC level. */
    INT_SYS_EnableIRQ(g_mmauIrqId[0]);
    
    return kStatus_MMAU_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MMAU_DRV_Deinit
 * Description   : Deinitilize the MMAU module
 *
 *END**************************************************************************/
mmau_status_t MMAU_DRV_Deinit(void){
    
    MMAU_HAL_Init(MMAU);
    
    /* Enable MMAU interrupt on NVIC level. */
    INT_SYS_DisableIRQ(g_mmauIrqId[0]);
    
    return kStatus_MMAU_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MMAU_DRV_IRQHandler
 * Description   : Driver-defined ISR in MMAU module. 
 * This is not a public API as it is called whenever an interrupt occurs.
 *
 *END**************************************************************************/
void MMAU_DRV_IRQHandler(void)
{   
    uint32_t status = MMAU_HAL_GetStateCmd(MMAU);
    MMAU_HAL_ConfigStateCmd(MMAU, status);   
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

