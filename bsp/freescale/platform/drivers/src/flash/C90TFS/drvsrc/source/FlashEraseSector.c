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


/****************************************************************************
*
*  Function Name    : FlashEraseSector
*  Description      : Perform erase operation on Flash
*  Arguments        : PFLASH_SSD_CONFIG, uint32_t, uint32_t, pFLASHCOMMANDSEQUENCE
*  Return Value     : uint32_t
*
*****************************************************************************/

/* Enable size optimization */
#if(ARM_CORTEX_M != CPU_CORE)
#pragma optimize_for_size on
#pragma optimization_level 4
#endif /* End of CPU_CORE */

uint32_t SIZE_OPTIMIZATION FlashEraseSector(PFLASH_SSD_CONFIG pSSDConfig, \
                                  uint32_t dest, \
                                  uint32_t size, \
                                  pFLASHCOMMANDSEQUENCE pFlashCommandSequence)
{

    uint32_t ret = FTFx_OK;     /* return code variable */
    uint32_t sectorSize;        /* size of one sector */
    uint32_t temp;              /* temporary variable */


    /* convert to byte address */
    dest = WORD2BYTE(dest);

#if (DEBLOCK_SIZE)
    temp = WORD2BYTE(pSSDConfig->DFlashBase);
    if((dest >= temp) && (dest < (temp + pSSDConfig->DFlashSize)))
    {
        dest = dest - temp + 0x800000U;
        sectorSize = FTFx_DSECTOR_SIZE;
    }
    else
#endif
    {
        temp = WORD2BYTE(pSSDConfig->PFlashBase);
        if((dest >= temp) && (dest < (temp + pSSDConfig->PFlashSize)))
        {
            dest -= temp;
            sectorSize = FTFx_PSECTOR_SIZE;
        }
        else
        {
            ret = FTFx_ERR_ACCERR;
            size = 0x0U;
        }
    }

    /* check if the size is sector alignment or not */
    if(size & (sectorSize - 0x01U))
    {
        /* return an error code FTFx_ERR_SIZE */
        ret = FTFx_ERR_SIZE;
    }

    while((size > 0x0U) && (FTFx_OK == ret))
    {
        /* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register. Write 1 to clear*/
        temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET;
        REG_WRITE(temp, FTFx_SSD_FSTAT_ERROR_BITS);

        /* passing parameter to the command */
        temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB0_OFFSET;
        REG_WRITE(temp, FTFx_ERASE_SECTOR);

        temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB1_OFFSET;
        REG_WRITE(temp, GET_BIT_16_23(dest));

        temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB2_OFFSET;
        REG_WRITE(temp, GET_BIT_8_15(dest));

        temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB3_OFFSET;
        REG_WRITE(temp, GET_BIT_0_7(dest));

        /* calling flash command sequence function to execute the command */
        ret = pFlashCommandSequence(pSSDConfig);

        /* update size and destination address */
        size -= sectorSize;
        dest += sectorSize;

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

