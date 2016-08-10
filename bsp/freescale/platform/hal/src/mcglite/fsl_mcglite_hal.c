/*
* Copyright (c) 2014-2015, Freescale Semiconductor, Inc.
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
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_mcglite_hal.h"
#if FSL_FEATURE_SOC_MCGLITE_COUNT
/*******************************************************************************
* Definitions
******************************************************************************/

/* This frequency values should be set by different boards. */
uint32_t g_xtal0ClkFreq;           /* EXTAL0 clock */

uint32_t g_xtalRtcClkFreq;		   /* EXTAL RTC clock */  


/*******************************************************************************
* Code
******************************************************************************/

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_HAL_GetPeripheralClk
* Description   : Get the current mcg_lite MCGPCLK clock
* This function will return the lirc_clk value in frequency(Hz) based
* on current mcg_lite configurations and settings.
*
*END**************************************************************************/
uint32_t CLOCK_HAL_GetPeripheralClk(MCG_Type * base)
{
    /* Check whether the HIRC is enabled. */
    if ((0U != MCG_BRD_MC_HIRCEN(base)) ||
        (kMcgliteClkSrcHirc == CLOCK_HAL_GetClkSrcStat(base)))
    {
        return kMcgliteConst48M;
    }
    else
    {
        return kMcgliteConst0;
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_HAL_GetLircClk
* Description   : Get the current mcg_lite lirc_clk clock
* This function will return the lirc_clk value in frequency(Hz) based
* on current mcg_lite configurations and settings. If the LIRC is not enabled,
* this function returns 0.
*
*END**************************************************************************/
uint32_t CLOCK_HAL_GetLircClk(MCG_Type * base)
{
    /* Check whether the LIRC is enabled. */
    if ((0U != MCG_BRD_C1_IRCLKEN(base)) ||
        (kMcgliteClkSrcLirc == CLOCK_HAL_GetClkSrcStat(base)))
    {
        if (MCG_BRD_C2_IRCS(base) == kMcgliteLircSel8M)
        {
            /* LIRC8M internal reference clock is selected*/
            return kMcgliteConst8M;
        }
        else
        {
            return kMcgliteConst2M;
        }
    }
    else
    {
        return kMcgliteConst0;
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_HAL_GetLircDiv1Clk
* Description   : Get the current mcg_lite LIRC_DIV1_CLK frequency.
* This function will return the LIRC_DIV1_CLK value in frequency(Hz) based
* on current mcg_lite configurations and settings. It will not check if the
* mcg_lite irclk is enabled or not, just calculate and return the value.
*
*END**************************************************************************/
uint32_t CLOCK_HAL_GetLircDiv1Clk(MCG_Type * base)
{
    return CLOCK_HAL_GetLircClk(base) >> MCG_BRD_SC_FCRDIV(base);
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_HAL_GetInternalRefClk
* Description   : Get the current mcg_lite ir clock
* This function will return the mcg_liteirclk value in frequency(hz) based
* on current mcg_lite configurations and settings.
*
*END**************************************************************************/
uint32_t CLOCK_HAL_GetInternalRefClk(MCG_Type * base)
{
    uint8_t divider1 = MCG_BRD_SC_FCRDIV(base);
    uint8_t divider2 = MCG_BRD_MC_LIRC_DIV2(base);
    /* LIRC internal reference clock is selected*/
    return CLOCK_HAL_GetLircClk(base) >> (divider1 + divider2);
}

/*FUNCTION**********************************************************************
*
* Function Name : CLOCK_HAL_GetOutClk
* Description   : Get the current mcgoutclk clock
* This function will return the mcg_liteoutclk value in frequency(hz) based on
* current mcg_lite configurations and settings. The configuration should be
* properly done in order to get the valid value.
*
*END**************************************************************************/
uint32_t CLOCK_HAL_GetOutClk(MCG_Type * base)
{
    mcglite_mcgoutclk_source_t clkSrc = CLOCK_HAL_GetClkSrcStat(base);

    if (clkSrc == kMcgliteClkSrcHirc)
    {
        /*  HIRC 48MHz is selected*/
        return kMcgliteConst48M;
    }
    else if (clkSrc == kMcgliteClkSrcLirc)
    {
        return CLOCK_HAL_GetLircClk(base) >> MCG_BRD_SC_FCRDIV(base);
    }
    else if (clkSrc == kMcgliteClkSrcExt)
    {
        /*  external clock is selected*/
        return g_xtal0ClkFreq;
    }
    else
    {
        /* Reserved value*/
        return kMcgliteConst0;
    }
}
#endif

/*******************************************************************************
* EOF
******************************************************************************/

