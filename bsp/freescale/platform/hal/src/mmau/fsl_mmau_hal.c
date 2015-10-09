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
#include "fsl_mmau_hal.h"

/*FUNCTION*********************************************************************
 * Function Name : MMAU_HAL_Init
 * Description   : Reset MMAU control/status register to a known state. This state is
 * defined in Reference Manual, which is power on reset value. This function must
 * execute in a Supervisor Mode.
 *END*************************************************************************/
void MMAU_HAL_Init(MMAU_Type* base)
{
  MMAU_HAL_SetIntCmd(base, false);
  MMAU_HAL_SetDmaCmd(base, false);
  MMAU_HAL_SetSupervisorOnlyCmd(base, false);
  MMAU_HAL_WriteInstrFlagsCmd(base, false);
  MMAU_HAL_ClearIntStatusFlagsCmd(base, false);  
}

/*FUNCTION*********************************************************************
 * Function Name : MMAU_Config
 * Description   : Configure MMAU.
 *END*************************************************************************/
void MMAU_HAL_Config(MMAU_Type* base,const mmau_user_config_t * configStructPtr)
{
  MMAU_HAL_SetIntCmd(base, configStructPtr->mmauIntReqMask);
  MMAU_HAL_SetDmaCmd(base, configStructPtr->mmauDmaReq);
  MMAU_HAL_SetSupervisorOnlyCmd(base, configStructPtr->mmauAccess); 
}

