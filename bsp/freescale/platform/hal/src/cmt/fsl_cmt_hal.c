/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#include "fsl_cmt_hal.h"

#if FSL_FEATURE_SOC_CMT_COUNT
/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION*********************************************************************
 *
 * Function Name : CMT_HAL_Init
 * Description   : Reset all the configurable registers to be reset state for CMT.
 * It should be called before configuring the CMT module.
 *
 *END*************************************************************************/
void CMT_HAL_Init(CMT_Type * base)
{
    uint8_t moduleCtl = 0;  /* For building warning*/
    /*Clear all carrier generator counters*/
    CMT_WR_CGH1(base, 0);
    CMT_WR_CGL1(base, 0);
    CMT_WR_CGH2(base, 0);
    CMT_WR_CGL2(base, 0);

    /*clear End-of-cycle interrupt needs read*/
    moduleCtl = CMT_RD_MSC(base);
    moduleCtl = moduleCtl;	/* For building warning*/
    /*Clear all carrier modulator counters*/
    CMT_WR_CMD1(base, 0);
    CMT_WR_CMD2(base, 0);
    CMT_WR_CMD3(base, 0);
    CMT_WR_CMD4(base, 0);

    /*Clear Modulator status and control */
    CMT_WR_OC(base, 0);
    CMT_WR_DMA(base, 0);
    CMT_WR_MSC(base, 0);

   /*Clear primary prescaler*/
    CMT_WR_PPS(base, 0);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : CMT_HAL_GetMode
 * Description   : Get the current mode of the CMT module
 *
 *END*************************************************************************/
cmt_mode_t CMT_HAL_GetMode(CMT_Type * base)
{
    uint8_t mode;

    mode = CMT_RD_MSC(base);

    if(! mode & CMT_MSC_MCGEN_MASK) 
    { /* Carrier modulator disabled and the IRO signal is in direct software control. */
        return  kCMTDirectIROCtl;  
    }
    else /* Carrier modulator is enabled */
    {
       if(mode & CMT_MSC_BASE_MASK)
       {
          return kCMTBasebandMode;         
       }
       else if(mode & CMT_MSC_FSK_MASK)
       {
          return kCMTFSKMode;
       }

       return kCMTTimeMode;     
    }
}

#endif /* FSL_FEATURE_SOC_CMT_COUNT */
/******************************************************************************
 * EOF
 ******************************************************************************/

