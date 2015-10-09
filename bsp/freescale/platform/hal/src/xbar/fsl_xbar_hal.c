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

#include "fsl_xbar_hal.h"
#if FSL_FEATURE_SOC_XBAR_COUNT

/*FUNCTION*********************************************************************
 *
 * Function Name : XBARA_HAL_Init
 * Description   : Reset XBARA's registers to a known state. This state is
 * defined in Reference Manual, which is power on reset value.
 *
 *END*************************************************************************/
void XBARA_HAL_Init(XBARA_Type * baseAddr)
{
    uint32_t i;
    
    for(i = 0; i < FSL_FEATURE_XBARA_MODULE_OUTPUTS; i++)
    {
        XBARA_HAL_SetOutSel(baseAddr, i, 0);
    }
    
    for(i = 0; i < FSL_FEATURE_XBARA_INTERRUPT_COUNT; i++)
    {
        XBARA_HAL_SetDMAOutCmd(baseAddr, i, false);
        XBARA_HAL_SetIntOutCmd(baseAddr, i, false);
        XBARA_HAL_SetOutActiveEdge(baseAddr, i, kXbarEdgeNone);
    }

}

#if !defined FSL_FEATURE_XBAR_HAS_SINGLE_MODULE
 /*FUNCTION*********************************************************************
 *
 * Function Name : XBARB_HAL_Init
 * Description   : Reset XBARB's registers to a known state. This state is
 * defined in Reference Manual, which is power on reset value.
 *
 *END*************************************************************************/
void XBARB_HAL_Init(XBARB_Type * baseAddr)
{
    uint32_t i;
    
    for(i = 0; i < FSL_FEATURE_XBARB_MODULE_OUTPUTS; i++)
    {
        XBARB_HAL_SetOutSel(baseAddr, i, 0);
    }
    
}
#endif
#endif

/*******************************************************************************
 * EOF
 *******************************************************************************/

