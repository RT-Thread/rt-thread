/*****************************************************************************
 (c) Copyright 2015 Freescale Semiconductor, Inc.
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
* DATE          :  Jun 15, 2015                                             *
*                                                                           *
* AUTHOR        :  ROM Team                                                 *
* E-mail        :  b46522@freescale.com                                     *
*                                                                           *
*****************************************************************************/

/************************** CHANGES *************************************
1.3.GA      06.23.2015      ROM Team      First version of  PFlashFacGetXAProtection()

*************************************************************************/

/* include the header files */
#include "SSD_FTFx.h"

/************************************************************************
*
*  Function Name    : PFlashFacGetXAProtection.c
*  Description      : This API retrieves the current P-Flash FAC Exeucte Access protection status.
*  Arguments        : PFLASH_SSD_CONFIG, protectStatus
*  Return Value     : uint32_t
*
*************************************************************************/

/* Enable size optimization */
#if(ARM_CORTEX_M != CPU_CORE)
#pragma optimize_for_size on
#pragma optimization_level 4
#endif /* End of CPU_CORE */

uint32_t SIZE_OPTIMIZATION PFlashFacGetXAProtection (PFLASH_SSD_CONFIG pSSDConfig, \
                       uint8_t *protectStatus,\
                       uint8_t *numberOfSegments,\
                       uint32_t *segmentSize)
{
#if PFLASH_FAC_PRESENCE
    uint8_t reg[8];
    uint32_t temp;        /* temporary variable */

    // Get Number of Segments for P-Flash
    temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FACSN_OFFSET;
    *numberOfSegments = REG_READ(temp);

    // Get Segment size
    temp = pSSDConfig->ftfxRegBase + FTFx_SSD_FACSS_OFFSET;
    *segmentSize = 256ul << REG_READ(temp);

    // Get Protect status
    temp = pSSDConfig->ftfxRegBase + FTFx_SSD_XACCL0_OFFSET;
    reg[0] = REG_READ(temp);
    temp = pSSDConfig->ftfxRegBase + FTFx_SSD_XACCL1_OFFSET;
    reg[1] = REG_READ(temp);
    temp = pSSDConfig->ftfxRegBase + FTFx_SSD_XACCL2_OFFSET;
    reg[2] = REG_READ(temp);
    temp = pSSDConfig->ftfxRegBase + FTFx_SSD_XACCL3_OFFSET;
    reg[3] = REG_READ(temp);
    temp = pSSDConfig->ftfxRegBase + FTFx_SSD_XACCH0_OFFSET;
    reg[4] = REG_READ(temp);
    temp = pSSDConfig->ftfxRegBase + FTFx_SSD_XACCH1_OFFSET;
    reg[5] = REG_READ(temp);
    temp = pSSDConfig->ftfxRegBase + FTFx_SSD_XACCH2_OFFSET;
    reg[6] = REG_READ(temp);
    temp = pSSDConfig->ftfxRegBase + FTFx_SSD_XACCH3_OFFSET;
    reg[7] = REG_READ(temp);

    for(temp = 0; temp < 8; temp++)
    {
        protectStatus[temp] = reg[temp];
    }

#if C90TFS_ENABLE_DEBUG
    /* Enter Debug state if enabled */
    if (TRUE == (pSSDConfig->DebugEnable))
    {
        ENTER_DEBUG_MODE;
    }
#endif

    return(FTFx_OK);
#else
    return (FTFx_ERR_NOFAC);
#endif // PFLASH_FAC_PRESENCE
}

/* End of file */
