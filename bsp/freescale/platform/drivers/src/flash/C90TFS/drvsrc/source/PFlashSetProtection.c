/*****************************************************************************
 (c) Copyright 2010-2014 Freescale Semiconductor, Inc.
 ALL RIGHTS RESERVED.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************

*****************************************************************************
*                                                                           *
*        Standard Software Flash Driver For FTFx                            *
*                                                                           *
* FILE NAME     :  SSD_FTFx.h                                               *
* DATE          :  Sep 25, 2014                                           *
*                                                                           *
* AUTHOR        :  FPT Team                                                 *
* E-mail        :  r56611@freescale.com                                     *
*                                                                           *
*****************************************************************************/

/************************** CHANGES *************************************
1.1.GA      09.25.2014      FPT Team      First version of SDK C90TFS flash driver
                                          inherited from BM C90TFS flash driver v1.02
                                          (08.04.2014, FPT Team)
*************************************************************************/
/* include the header files */
#include "SSD_FTFx.h"

/************************************************************************
*
*  Function Name    : PFlashSetProtection.c
*  Description      : This function sets the P-Flash protection to the
*                     intended protection status
*  Arguments        : PFLASH_SSD_CONFIG, uint32_t
*  Return Value     : uint32_t
*
*************************************************************************/

/* Enable size optimization */
#if(ARM_CORTEX_M != CPU_CORE)
#pragma optimize_for_size on
#pragma optimization_level 4
#endif /* End of CPU_CORE */

uint32_t SIZE_OPTIMIZATION PFlashSetProtection(PFLASH_SSD_CONFIG pSSDConfig, \
                                      uint32_t protectStatus)
{
    uint32_t ret = FTFx_OK;
    uint32_t addr;
    uint32_t temp0, temp1, temp2, temp3;
    uint8_t reg0, reg1, reg2, reg3;

    reg0 = GET_BIT_24_31(protectStatus);
    reg1 = GET_BIT_16_23(protectStatus);
    reg2 = GET_BIT_8_15(protectStatus);
    reg3 = GET_BIT_0_7(protectStatus);

    addr = pSSDConfig->ftfxRegBase + FTFx_SSD_FPROT0_OFFSET;
    REG_WRITE(addr, reg0);
    temp0 = REG_READ(addr);
    addr = pSSDConfig->ftfxRegBase + FTFx_SSD_FPROT1_OFFSET;
    REG_WRITE(addr, reg1);
    temp1 = REG_READ(addr);
    addr = pSSDConfig->ftfxRegBase + FTFx_SSD_FPROT2_OFFSET;
    REG_WRITE(addr, reg2);
    temp2 = REG_READ(addr);
    addr = pSSDConfig->ftfxRegBase + FTFx_SSD_FPROT3_OFFSET;
    REG_WRITE(addr, reg3);
    temp3 = REG_READ(addr);

    /* Read the value of FPPROT registers */
    if ((temp0 != reg0) || (temp1 != reg1) || (temp2 != reg2) || (temp3 != reg3))
    {
        ret = FTFx_ERR_CHANGEPROT;
    }

#if C90TFS_ENABLE_DEBUG
    /* Enter Debug state if enabled */
    if (TRUE == (pSSDConfig->DebugEnable))
    {
        ENTER_DEBUG_MODE;
    }
#endif

    return(ret);
}
/* End of file */
