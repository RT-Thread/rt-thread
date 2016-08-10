/**HEADER********************************************************************
 Copyright (c) 2010-2014 Freescale Semiconductor, Inc.
 ALL RIGHTS RESERVED.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Freescale Semiconductor, Inc. nor the
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
*****************************************************************************
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

#ifdef SWAP_M
/************************************************************************
*
*  Function Name    : PFlashSwap.c
*  Description      : Perform a swap between P-Flash block 0 and
*                     P-Flash block 1
*
*
*  Arguments        : PFLASH_SSD_CONFIG, uint32_t, pFLASHCOMMANDSEQUENCE,
*                     PSWAP_CALLBACK
*
*  Return Value     : uint32_t
*
*************************************************************************/

/* Enable size optimization */
#if(ARM_CORTEX_M != CPU_CORE)
#pragma optimize_for_size on
#pragma optimization_level 4
#endif /* End of CPU_CORE */

uint32_t SIZE_OPTIMIZATION PFlashSwap(PFLASH_SSD_CONFIG pSSDConfig, \
                  uint32_t addr, \
                  PFLASH_SWAP_CALLBACK pSwapCallback, \
                  pFLASHCOMMANDSEQUENCE pFlashCommandSequence)
{
    uint32_t ret = FTFx_OK;      /* Return code */
    uint8_t currentSwapMode , currentSwapBlockStatus , nextSwapBlockStatus;
    bool swapContinue;

    currentSwapMode = currentSwapBlockStatus = nextSwapBlockStatus = 0xFFU;
    swapContinue = FALSE;

    /* Report current swap state */
    ret = PFlashSwapCtl(pSSDConfig,addr,FTFx_SWAP_REPORT_STATUS,&currentSwapMode, \
    &currentSwapBlockStatus, &nextSwapBlockStatus ,pFlashCommandSequence);

    if (FTFx_OK == ret)
    {
        if ((FTFx_SWAP_UNINIT == currentSwapMode) || (FTFx_SWAP_READY == currentSwapMode) || \
            (FTFx_SWAP_UPDATE == currentSwapMode))
        {
            /* If current swap mode is Uninitialized */
            if (FTFx_SWAP_UNINIT == currentSwapMode)
            {
                /* Initialize Swap to Initialized/READY state */
                ret = PFlashSwapCtl(pSSDConfig, addr, FTFx_SWAP_SET_INDICATOR_ADDR,&currentSwapMode, \
                &currentSwapBlockStatus, &nextSwapBlockStatus , pFlashCommandSequence);
            }
                /* If current swap mode is Initialized/Ready */
            else if (FTFx_SWAP_READY == currentSwapMode)
            {
                /* Initialize Swap to UPDATE state */
                ret = PFlashSwapCtl(pSSDConfig, addr, FTFx_SWAP_SET_IN_PREPARE,&currentSwapMode, \
                &currentSwapBlockStatus, &nextSwapBlockStatus , pFlashCommandSequence);
            }
            else if (FTFx_SWAP_UPDATE == currentSwapMode){}

            /* Check for the success of command execution */
            /* Report the current swap state to user via callback */
            if ((NULL_SWAP_CALLBACK != pSwapCallback) && (FTFx_OK == ret))
            {
                swapContinue = pSwapCallback(currentSwapMode);

                if (swapContinue)
                {
                    /* Report current swap state */
                    ret = PFlashSwapCtl(pSSDConfig,addr,FTFx_SWAP_REPORT_STATUS,&currentSwapMode, \
                                        &currentSwapBlockStatus, &nextSwapBlockStatus , pFlashCommandSequence);
                }
            }
        }
        if ((NULL_SWAP_CALLBACK == pSwapCallback)&&(FTFx_SWAP_UPDATE == currentSwapMode))
        {
            /* Erase indicator sector in non active block to proceed swap system to update-erased state */
            ret = FlashEraseSector(pSSDConfig, addr + (pSSDConfig->PFlashSize >> 1), FTFx_PSECTOR_SIZE, \
                                    pFlashCommandSequence);
            if (FTFx_OK == ret)
            {
                /* Now the swap state must be Update-Erased, so report current swap state */
                ret = PFlashSwapCtl(pSSDConfig,addr,FTFx_SWAP_REPORT_STATUS,&currentSwapMode, \
                                    &currentSwapBlockStatus, &nextSwapBlockStatus , pFlashCommandSequence);
            }
        }
        /* If current swap mode is Update or Update-Erased */
        if  (FTFx_SWAP_UPDATE_ERASED == currentSwapMode)
        {
            if (NULL_SWAP_CALLBACK == pSwapCallback)
            {
                swapContinue = TRUE;
            }
            else
            {
                swapContinue = pSwapCallback(currentSwapMode);
            }

            if (swapContinue)
            {
                /* Progress Swap to COMPLETE State */
                ret = PFlashSwapCtl(pSSDConfig,addr,FTFx_SWAP_SET_IN_COMPLETE,&currentSwapMode, \
                &currentSwapBlockStatus, &nextSwapBlockStatus , pFlashCommandSequence);
            }
        }
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
#endif /* End of SWAP_M */
/* End of file */
