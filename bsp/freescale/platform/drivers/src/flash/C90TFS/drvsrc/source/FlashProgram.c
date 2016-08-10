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
*  Function Name    : FlashProgram.c
*  Description      : Program data into Flash
*  Arguments        : PFLASH_SSD_CONFIG, uint32_t, uint32_t, uint32_t,
*                     pFLASHCOMMANDSEQUENCE
*  Return Value     : uint32_t
*
*************************************************************************/

/* Enable size optimization */
#if(ARM_CORTEX_M != CPU_CORE)
#pragma optimize_for_size on
#pragma optimization_level 4
#endif /* End of CPU_CORE */

uint32_t SIZE_OPTIMIZATION FlashProgram(PFLASH_SSD_CONFIG pSSDConfig, \
                                   uint32_t dest, \
                                   uint32_t size, \
                                   uint8_t* pData, \
                                   pFLASHCOMMANDSEQUENCE pFlashCommandSequence)
{
    uint32_t ret = FTFx_OK;      /* return code variable */
    uint8_t i;
    uint32_t temp;

    if (size & (PGM_SIZE_BYTE - 0x01U))
    {
       ret = FTFx_ERR_SIZE;
    }
    else
    {
        /* convert to byte address */
        dest = WORD2BYTE(dest);
#if (DEBLOCK_SIZE)
        temp = WORD2BYTE(pSSDConfig->DFlashBase);
        if((dest >= temp) && (dest < (temp + pSSDConfig->DFlashSize)))
        {
            dest = dest - temp + 0x800000U;
        }
        else
#endif
        {
            temp = WORD2BYTE(pSSDConfig->PFlashBase);
            if((dest >= temp) && (dest < (temp + pSSDConfig->PFlashSize)))
            {
                dest -= temp;
            }
            else
            {
                ret = FTFx_ERR_ACCERR;
            }
        }
        while((size > 0x0U) && (FTFx_OK == ret))
        {
            /* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register. Write 1 to clear*/
            temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET;
            REG_WRITE(temp, FTFx_SSD_FSTAT_ERROR_BITS);
            /* passing parameter to the command */
#if (PGM_SIZE_BYTE == FTFx_PHRASE_SIZE)
            temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB0_OFFSET;
            REG_WRITE(temp, FTFx_PROGRAM_PHRASE);
#else
            temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB0_OFFSET;
            REG_WRITE(temp, FTFx_PROGRAM_LONGWORD);
#endif
            temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB1_OFFSET;
            REG_WRITE(temp, GET_BIT_16_23(dest));
            temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB2_OFFSET;
            REG_WRITE(temp, GET_BIT_8_15(dest));
            temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB3_OFFSET;
            REG_WRITE(temp, GET_BIT_0_7(dest));

            for (i = 0x0U; i <  PGM_SIZE_BYTE; i++)
            {
                temp = pSSDConfig->ftfxRegBase + i + 0x08U;
                REG_WRITE(temp, *(pData + i));
            }

            /* calling flash command sequence function to execute the command */
            ret = pFlashCommandSequence(pSSDConfig);

            /* update destination address for next iteration */
            dest += PGM_SIZE_BYTE;
            /* update size for next iteration */
            size -= PGM_SIZE_BYTE;
                            /* increment the source address by 1 */
            pData += PGM_SIZE_BYTE;
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
/* end of file */


