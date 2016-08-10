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

/***********************************************************************
*
*  Function Name    : FlashCheckSum.c
*  Description      : This function is used to calculate checksum value
*                     for the specified flash range.
*  Arguments        : PFLASH_SSD_CONFIG,uint32_t ,uint32_t ,uint32_t*
*  Return Value     : uint32_t
*
************************************************************************/

/* Enable size optimization */
#if(ARM_CORTEX_M != CPU_CORE)
#pragma optimize_for_size on
#pragma optimization_level 4
#endif /* End of CPU_CORE */

uint32_t SIZE_OPTIMIZATION FlashCheckSum(PFLASH_SSD_CONFIG pSSDConfig, \
                                uint32_t dest, \
                                uint32_t size, \
                                uint32_t* pSum)
{
    uint32_t counter;          /* Counter for callback operation */
    uint32_t data;             /* Data read from Flash address */
    uint32_t ret = FTFx_OK;       /* Return code variable */
    uint32_t endAddress;       /* P Flash end address */

    counter = 0x0U;
    /* convert to byte address */
    dest = WORD2BYTE(dest);
    /* calculating Flash end address */
    endAddress = dest + size;

    /* check for valid range of the target addresses */
    if ((dest < WORD2BYTE(pSSDConfig->PFlashBase)) ||
        (endAddress > (WORD2BYTE(pSSDConfig->PFlashBase) + pSSDConfig->PFlashSize)))
    {
#if(DEBLOCK_SIZE)
        if ((dest < WORD2BYTE(pSSDConfig->DFlashBase)) ||
        (endAddress > (WORD2BYTE(pSSDConfig->DFlashBase) + pSSDConfig->DFlashSize)))
        {
#endif /* End of if(DEBLOCK_SIZE) */
            /* return an error code FTFx_ERR_RANGE */
            ret = FTFx_ERR_RANGE;
            size = 0x0U;
#if(DEBLOCK_SIZE)
        }

#endif /* End of if(DEBLOCK_SIZE) */
    }
    *pSum = 0x0U;
    /* doing sum operation */
    while(size > 0x0U)
    {
        data = READ8(dest);
        *pSum += (uint32_t)data;
        dest += 0x01U;
        size -= 0x01U;

        /* Check if need to serve callback function */
        if((++counter) >= FLASH_CALLBACK_CS)
        {
            /* serve callback function if counter reaches limitation */
            if(NULL_CALLBACK != pSSDConfig->CallBack)
            {
                (pSSDConfig->CallBack)();
            }
            /* Reset counter */
            counter = 0x0U;
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
/* End of file */
