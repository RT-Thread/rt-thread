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
*  Function Name    : EEEWrite.c
*  Description      : This function is used to write data to EERAM
*                     when it is used as EEPROM emulator
*  Arguments        : PFLASH_SSD_CONFIG, uint32_t, uint32_t, uint8_t, uint32_t
*  Return Value     : uint32_t
*
************************************************************************/
#if (DEBLOCK_SIZE != 0x0U)

/* declare prototype */
uint32_t WaitEEWriteToFinish(PFLASH_SSD_CONFIG pSSDConfig, uint32_t* dest,\
                             uint32_t* size, uint8_t** pData, uint8_t step);

/* Enable size optimization */
#if(ARM_CORTEX_M != CPU_CORE)
#pragma optimize_for_size on
#pragma optimization_level 4
#endif /* End of CPU_CORE */

uint32_t SIZE_OPTIMIZATION WaitEEWriteToFinish(PFLASH_SSD_CONFIG pSSDConfig, uint32_t* dest,\
                             uint32_t* size, uint8_t** pData, uint8_t step)
{
    uint32_t ret;           /* return code variable */
    uint32_t temp;          /* temporary variable */

    if (0x01U == step)
    {
        WRITE8(*dest, READ8(*pData));
    }
    if (0x02U == step)
    {
#if(BIG_ENDIAN == ENDIANNESS)
        temp = (uint32_t)READ8(*pData) << 8;
        temp |= (uint32_t)(READ8(*pData + 1));
#else
        temp = (uint32_t)READ8(*pData + 1) << 8;
        temp |= (uint32_t)(READ8(*pData));
#endif
        WRITE16(BYTE2WORD(*dest), (uint16_t)temp);
    }
    if (0x04U == step)
    {
#if(BIG_ENDIAN == ENDIANNESS)
        temp = (uint32_t)READ8(*pData) << 24;
        temp |= (uint32_t)(READ8(*pData + 1)) << 16;
        temp |= (uint32_t)(READ8(*pData + 2)) << 8;
        temp |= (uint32_t)(READ8(*pData + 3));
#else
        temp = (uint32_t)READ8(*pData + 3) << 24;
        temp |= (uint32_t)(READ8(*pData + 2)) << 16;
        temp |= (uint32_t)(READ8(*pData + 1)) << 8;
        temp |= (uint32_t)READ8(*pData);
#endif
        WRITE32(BYTE2WORD(*dest), (uint32_t)temp);
    }

    temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FCNFG_OFFSET;
    while(0x0U == REG_BIT_GET(temp, FTFx_SSD_FCNFG_EEERDY))
    {
       /* wait till EEERDY bit is set */
    }
    /* Check for protection violation error */
    temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET;
    ret = (uint32_t)REG_READ(temp) & FTFx_SSD_FSTAT_FPVIOL;

    *dest += step;
    *size -= step;
    *pData += step;

    return ret;
}

uint32_t SIZE_OPTIMIZATION EEEWrite(PFLASH_SSD_CONFIG pSSDConfig, \
                           uint32_t dest, \
                           uint32_t size, \
                           uint8_t* pData)
{
    uint32_t ret = FTFx_OK;           /* Return code variable */
    uint32_t temp;                    /* variable temp */
    /* convert to byte address */
    dest = WORD2BYTE(dest);
    /* Check if EEE is enabled */
    temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FCNFG_OFFSET;
    if(REG_READ(temp) & FTFx_SSD_FCNFG_EEERDY)
    {
        /* check range */
       if((dest < WORD2BYTE(pSSDConfig->EERAMBase)) || \
          ((dest + size) > (WORD2BYTE(pSSDConfig->EERAMBase) + pSSDConfig->EEESize)))
        {
            ret = FTFx_ERR_RANGE;
        }

        while ((size > 0x0U) && (ret == FTFx_OK))
        {

            /* dest is 32bit-aligned and size is not less than 4 */
            if ((!(dest & 0x03U)) && (size >= 0x04U))
            {
                ret = WaitEEWriteToFinish(pSSDConfig, &dest, &size, &pData, 0x04U);
            }
            else  if ((!(dest & 0x1U)) && (size >= 0x02U))
            {
                ret = WaitEEWriteToFinish(pSSDConfig, &dest, &size, &pData, 0x02U);
            }
            else
            {
                ret = WaitEEWriteToFinish(pSSDConfig, &dest, &size, &pData, 0x01U);
            }
        }
    }
    else
    {
        ret = FTFx_ERR_NOEEE;
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
#endif /* of DEBLOCK_SIZE */
/* end of file */
