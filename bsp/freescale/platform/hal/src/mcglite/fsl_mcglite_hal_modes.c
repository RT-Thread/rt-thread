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
#include "fsl_mcglite_hal_modes.h"
#if FSL_FEATURE_SOC_MCGLITE_COUNT
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

/*****************************************************************
 * MCG clock mode
 *
 *   HIRC
 *   LIRC8M
 *   LIRC2M
 *   EXT
 *
 *****************************************************************/
/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_GetMode
 * Description  : This function checks the MCG_Lite registers and determine
 * the current MCG_Lite mode
 *
 * Return value : Current MCG_Lite mode.
 *END***********************************************************************************/
mcglite_mode_t CLOCK_HAL_GetMode(MCG_Type * base)
{
    mcglite_mode_t mode = kMcgliteModeError;

    /* Which source is using now. */
    mcglite_mcgoutclk_source_t clkSrc = CLOCK_HAL_GetClkSrcStat(base);

    switch (clkSrc)
    {
        case kMcgliteClkSrcHirc:
            mode = kMcgliteModeHirc48M;
            break;
        case kMcgliteClkSrcLirc:
            if (MCG_BRD_C2_IRCS(base) == kMcgliteLircSel2M)
            {
                mode = kMcgliteModeLirc2M;
            }
            else
            {
                mode = kMcgliteModeLirc8M;
            }
            break;
        case kMcgliteClkSrcExt:
            mode = kMcgliteModeExt;
            break;
        default:
            mode = kMcgliteModeError;
            break;
    }

    return mode;
} /* CLOCK_HAL_GetMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetHircMode
 * Description  : Set MCG_Lite HIRC mode
 *
 * This function sets MCG_Lite to HIRC 48MHz mode.
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
mcglite_mode_error_t CLOCK_HAL_SetHircMode(MCG_Type * base)
{
    /* Enable HIRC. */
    CLOCK_HAL_SetHircCmd(base, true);

    /* Select HIRC mode. */
    MCG_BWR_C1_CLKS(base, kMcgliteClkSrcHirc);

    /* Wait to check status. */
    while (CLOCK_HAL_GetClkSrcStat(base) != kMcgliteClkSrcHirc)
    {
    }
    return kMcgliteModeErrNone;
}

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetLircMode
 * Description  : Set MCG_Lite LIRC 8M or 2M mode
 * This function transitions the MCG_lite to LIRC mode.
 *
 * Parameters: lirc    - LIRC8M or LIRC2M clock source
 *             div1    - LIRC divider1 (FCRDIV)
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
mcglite_mode_error_t CLOCK_HAL_SetLircMode(MCG_Type * base,
                               mcglite_lirc_select_t lirc,
                               mcglite_lirc_div_t div1)
{
    /* Could not switch between LIRC8M and LIRC2M, so check current mode first. */
    mcglite_mode_t curMode = CLOCK_HAL_GetMode(base);

    if ( ((kMcgliteModeLirc8M==curMode) && (kMcgliteLircSel2M==lirc)) ||
         ((kMcgliteModeLirc2M==curMode) && (kMcgliteLircSel8M==lirc)))
    {
        /* Change to HIRC mode if can not switch directly. */
        CLOCK_HAL_SetHircMode(base);
    }

    /* Select LIRC mode 2M or 8M. */
    MCG_BWR_C2_IRCS(base, lirc);

    /* Enable LIRC clock. */
    CLOCK_HAL_SetLircCmd(base, true);

    /* Set FCRDIV. */
    MCG_BWR_SC_FCRDIV(base, div1);

    /* Set LIRC mode. */
    MCG_BWR_C1_CLKS(base, kMcgliteClkSrcLirc);

    /* Wait to check the status. */
    while (CLOCK_HAL_GetClkSrcStat(base) != kMcgliteClkSrcLirc)
    {
    }

    return kMcgliteModeErrNone;
}

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetExtMode
 * Description  : Set MCG_Lite externalc clock mode
 * This function transitions the MCG_lite to EXT mode.
 *
 * Parameters: base - MCG_Lite register base address.
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
mcglite_mode_error_t CLOCK_HAL_SetExtMode(MCG_Type * base)
{
    if (0U == g_xtal0ClkFreq)
    {
        return kMcgliteModeErrExt;
    }
    /* Change to use external source. */
    MCG_BWR_C1_CLKS(base, kMcgliteClkSrcExt);

    /* If oscillator is used, wait for stable. */
    if (kOscSrcOsc == MCG_BRD_C2_EREFS0(base))
    {
        while (!CLOCK_HAL_IsOscStable(base)) { }
    }

    /* Wait for clock status bits to update */
    while (CLOCK_HAL_GetClkSrcStat(base) != kMcgliteClkSrcExt)
    {
    }

    return kMcgliteModeErrNone;
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

