/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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

#include "fsl_mcg_hal_modes.h"
#if FSL_FEATURE_SOC_MCG_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*****************************************************************
 * MCG clock mode transition functions
 *
 *   FEI -> FEE
 *   FEI -> FBI
 *   FEI -> FBE
 *
 *   FEE -> FEI
 *   FEE -> FBI
 *   FEE -> FBE
 *
 *   FBI -> FEI
 *   FBI -> FEE
 *   FBI -> FBE
 *   FBI -> BLPI
 *   FBI -> PBI
 *
 *   BLPI -> FBI
 *   BLPI -> PBI
 *
 *   PBI -> FBI
 *   PBI -> BLPI
 *   PBI -> PEI
 *
 *   PEI -> PBI
 *
 *   FBE -> FEE
 *   FBE -> FEI
 *   FBE -> FBI
 *   FBE -> PBE
 *   FBE -> BLPE
 *
 *   PBE -> FBE
 *   PBE -> PEE
 *   PBE -> BLPE
 *
 *   BLPE -> FBE
 *   BLPE -> PBE
 *
 *   PEE -> PBE
 *
 *****************************************************************/

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_GetMcgMode
 * Description  : This function will check the mcg registers and determine
 * current MCG mode.
 *
 * Return value : mcgMode or error code mcg_modes_t defined in fsl_mcg_hal_modes.h
 *END***********************************************************************************/
mcg_modes_t CLOCK_HAL_GetMcgMode(MCG_Type * base)
{
    mcg_modes_t               mode   = kMcgModeError;
    mcg_clkout_stat_t         clkst  = CLOCK_HAL_GetClkOutStat(base);
    mcg_fll_src_t             irefst = CLOCK_HAL_GetFllSrc(base);
    uint8_t                   lp     = MCG_BRD_C2_LP(base);
#if FSL_FEATURE_MCG_HAS_PLL
    bool                      pllst  = CLOCK_HAL_IsPllSelected(base);
#endif

    /***********************************************************************
                           Mode and Registers
    ____________________________________________________________________

      Mode   |   CLKST    |   IREFST   |   PLLST   |      LP
    ____________________________________________________________________

      FEI    |  00(FLL)   |   1(INT)   |   0(FLL)  |      X
    ____________________________________________________________________

      FEE    |  00(FLL)   |   0(EXT)   |   0(FLL)  |      X
    ____________________________________________________________________

      FBE    |  10(EXT)   |   0(EXT)   |   0(FLL)  |   0(NORMAL)
    ____________________________________________________________________

      FBI    |  01(INT)   |   1(INT)   |   0(FLL)  |   0(NORMAL)
    ____________________________________________________________________

      BLPI   |  01(INT)   |   1(INT)   |   0(FLL)  |   1(LOW POWER)
    ____________________________________________________________________

      BLPE   |  10(EXT)   |   0(EXT)   |     X     |   1(LOW POWER)
    ____________________________________________________________________

      PEE    |  11(PLL)   |   0(EXT)   |   1(PLL)  |      X
    ____________________________________________________________________

      PBE    |  10(EXT)   |   0(EXT)   |   1(PLL)  |   O(NORMAL)
    ____________________________________________________________________

      PBI    |  01(INT)   |   1(INT)   |   1(PLL)  |   0(NORMAL)
    ____________________________________________________________________

      PEI    |  11(PLL)   |   1(INT)   |   1(PLL)  |      X
    ____________________________________________________________________

    ***********************************************************************/

    switch (clkst)
    {
        case kMcgClkOutStatFll:
#if FSL_FEATURE_MCG_HAS_PLL
        if (!pllst)
#endif
        {

            if (kMcgFllSrcExternal == irefst)
            {
                mode = kMcgModeFEE;
            }
            else
            {
                mode = kMcgModeFEI;
            }
        }
        break;
        case kMcgClkOutStatInternal:
#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
 		if (0U == lp)
            {
                if (pllst)
                {
                    mode = kMcgModePBI;
                }
                else
                {
                    mode = kMcgModeFBI;
                }
            }
            else
            {
                mode = kMcgModeBLPI;
            }
#else
        if ((kMcgFllSrcInternal == irefst)
#if FSL_FEATURE_MCG_HAS_PLL
            && (!pllst)
#endif
           )
        {
            if (0U == lp)
            {
		
                mode = kMcgModeFBI;
            }
            else
            {
                mode = kMcgModeBLPI;
            }
        }
#endif //FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE
        break;
        case kMcgClkOutStatExternal:
        if (kMcgFllSrcExternal == irefst)
        {
            if (0U == lp)
            {
#if FSL_FEATURE_MCG_HAS_PLL
                if (pllst)
                {
                    mode = kMcgModePBE;
                }
                else
#endif
                {
                    mode = kMcgModeFBE;
                }
            }
            else
            {
                mode = kMcgModeBLPE;
            }
        }
        break;
#if FSL_FEATURE_MCG_HAS_PLL
        case kMcgClkOutStatPll:
#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
            if (kMcgPllRefClkSrcSlowIrc == MCG_RD_C7_PLL32KREFSEL(base))
            {
                mode = kMcgModePEI;
            }
            else
#else
	if ((kMcgFllSrcExternal == irefst) && pllst)
#endif //FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE
            {
                mode = kMcgModePEE;
            }
            break;
#endif
        default:
        break;
    }

    return mode;
}   /* CLOCK_HAL_GetMcgMode */

/*FUNCTION******************************************************************************
 *
 * Function name : CLOCK_HAL_SetFeiMode
 * Description  : This function sets MCG to FEI mode.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_HAL_SetFeiMode(MCG_Type * base,
                              mcg_dco_range_select_t drs,
                              void (* fllStableDelay)(void))
{
    uint8_t mcg_c4;
    bool change_drs = false;

#if MCG_MODE_CHECK_PARAM
    uint32_t mcgOut;
    mcg_modes_t mode = CLOCK_HAL_GetMcgMode(base);
    if (!((kMcgModeFEI | kMcgModeFBI | kMcgModeFBE | kMcgModeFEE) & (uint32_t)mode))
    {
        return kMcgModeErrModeUnreachable;
    }

    /* Internal slow clock is used for FLL in FEI mode. */
    /* DMX32 is recommended to be 0 in FEI mode. */
    mcgOut = CLOCK_HAL_TestFllFreq(base,
                                   g_slowInternalRefClkFreq,
                                   kMcgDmx32Default,
                                   drs);
    if (0U == mcgOut)
    {
        return kMcgModeErrFllRefRange;
    }
#endif

    /* Set DMX32. DMX32 is recommended to be 0 in FEI mode. */
    MCG_BWR_C4_DMX32(base, kMcgDmx32Default);

    /*
     * Errata: ERR007993
     * Workaround: Invert MCG_C4[DMX32] or change MCG_C4[DRST_DRS] before
     * reference clock source changes, then reset to previous value after
     * reference clock changes.
     */
    if (kMcgFllSrcExternal == CLOCK_HAL_GetFllSrc(base))
    {
        mcg_c4 = MCG_RD_C4(base);
        // Change the LSB of DRST_DRS.
        MCG_WR_C4(base, mcg_c4 ^ (1U << MCG_C4_DRST_DRS_SHIFT));
        change_drs = true;
    }

    /* Set CLKS and IREFS. */
    MCG_WR_C1(base, ((MCG_RD_C1(base) & ~(MCG_C1_CLKS_MASK | MCG_C1_IREFS_MASK)))
                  | (MCG_C1_CLKS(kMcgClkOutSrcOut)  /* CLKS = 0 */
                  | MCG_C1_IREFS(kMcgFllSrcInternal))); /* IREFS = 1 */

    /* Wait and check status. */
    while (CLOCK_HAL_GetFllSrc(base) != kMcgFllSrcInternal) {}

    /* Errata: ERR007993 */
    if (change_drs)
    {
        MCG_WR_C4(base, mcg_c4);
    }

    while (CLOCK_HAL_GetClkOutStat(base) != kMcgClkOutStatFll) {}
    /* Set DRS. */
    MCG_WR_C4_DRST_DRS(base, drs);

    /* Wait for DRS to be set. */
    while (MCG_BRD_C4_DRST_DRS(base) != drs) {}

    /* Wait for FLL stable time. */
    if (fllStableDelay)
    {
        fllStableDelay();
    }

    return kMcgModeErrNone;
}

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFeeMode
 * Description  : This function sets MCG to FEE mode.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_HAL_SetFeeMode(MCG_Type * base,
                              mcg_oscsel_select_t oscselVal,
                              uint8_t frdivVal,
                              mcg_dmx32_select_t dmx32,
                              mcg_dco_range_select_t drs,
                              void (* fllStableDelay)(void))
{
    uint8_t mcg_c4;
    bool change_drs = false;

#if MCG_MODE_CHECK_PARAM
    uint32_t mcgOut, extFreq;

    mcg_modes_t mode = CLOCK_HAL_GetMcgMode(base);
    if (!((kMcgModeFEE | kMcgModeFBI | kMcgModeFBE | kMcgModeFEI) & (uint32_t)mode))
    {
        return kMcgModeErrModeUnreachable;
    }

    extFreq = CLOCK_HAL_TestOscFreq(base, oscselVal);

    if (0U == extFreq)
    {
        return kMcgModeErrOscFreqRange;
    }

    /* Check whether FRDIV value is OK for current MCG setting. */
    extFreq = CLOCK_HAL_TestFllExternalRefFreq(base,
                                               extFreq,
                                               frdivVal,
                                               (osc_range_t)MCG_BRD_C2_RANGE(base),
                                               oscselVal);
    if ((extFreq < kMcgConstant31250) || (extFreq > kMcgConstant39063))
    {
        return kMcgModeErrFllFrdivRange;
    }

    /* Check resulting FLL frequency  */
    mcgOut = CLOCK_HAL_TestFllFreq(base, extFreq, dmx32, drs);
    if (0U == mcgOut)
    {
        return kMcgModeErrFllRefRange;
    }
#endif

    /* Set OSCSEL */
#if FSL_FEATURE_MCG_USE_OSCSEL
    MCG_BWR_C7_OSCSEL(base, oscselVal);
#endif

    /*
     * Errata: ERR007993
     * Workaround: Invert MCG_C4[DMX32] or change MCG_C4[DRST_DRS] before
     * reference clock source changes, then reset to previous value after
     * reference clock changes.
     */
    if (kMcgFllSrcInternal == CLOCK_HAL_GetFllSrc(base))
    {
        mcg_c4 = MCG_RD_C4(base);
        // Change the LSB of DRST_DRS.
        MCG_WR_C4(base, mcg_c4 ^ (1U << MCG_C4_DRST_DRS_SHIFT));
        change_drs = true;
    }

    /* Set CLKS and IREFS. */
    MCG_WR_C1(base, (MCG_RD_C1(base) & ~(MCG_C1_CLKS_MASK | MCG_C1_FRDIV_MASK | MCG_C1_IREFS_MASK))
                  | (MCG_C1_CLKS(kMcgClkOutSrcOut)  /* CLKS = 0 */
                  | MCG_C1_FRDIV(frdivVal)  /* FRDIV */
                  | MCG_C1_IREFS(kMcgFllSrcExternal))); /* IREFS = 0 */
#if FSL_FEATURE_MCG_USE_OSCSEL
    if (kMcgOscselOsc == oscselVal)
#endif
    {
        if (MCG_BRD_C2_EREFS(base))
        {
            while(!CLOCK_HAL_IsOsc0Stable(base)){}
        }
    }

    /* Wait and check status. */
    while (CLOCK_HAL_GetFllSrc(base) != kMcgFllSrcExternal) {}

    /* Errata: ERR007993 */
    if (change_drs)
    {
        MCG_WR_C4(base, mcg_c4);
    }

    /* Set DRS and DMX32. */
    MCG_WR_C4(base, (MCG_RD_C4(base)
                 & ~(MCG_C4_DMX32_MASK |
                     MCG_C4_DRST_DRS_MASK))
                 |  (MCG_C4_DMX32(dmx32) |
                     MCG_C4_DRST_DRS(drs)));

    /* Wait for DRS to be set. */
    while (MCG_BRD_C4_DRST_DRS(base) != drs) {}

    /* Check MCG_S[CLKST] */
    while (CLOCK_HAL_GetClkOutStat(base) != kMcgClkOutStatFll) {}

    /* Wait for FLL stable time. */
    if (fllStableDelay)
    {
        fllStableDelay();
    }

    return kMcgModeErrNone;
}

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFbiMode
 * Description  : This function sets MCG to FBI mode.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_HAL_SetFbiMode(MCG_Type * base,
                              mcg_dco_range_select_t drs,
                              mcg_irc_mode_t ircSelect,
                              uint8_t fcrdivVal,
                              void (* fllStableDelay)(void))
{
    uint8_t mcg_c4;
    bool change_drs = false;

#if MCG_MODE_CHECK_PARAM
    mcg_modes_t mode = CLOCK_HAL_GetMcgMode(base);

    if (!((kMcgModeFBI |
           kMcgModeFEI |
           kMcgModeFBE |
           kMcgModeFEE |
#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
           kMcgModePBI |
#endif
           kMcgModeBLPI) & (uint32_t)mode))
    {
        return kMcgModeErrModeUnreachable;
    }
#endif

    /* In FBI and FEI modes, setting C4[DMX32] bit is not recommended. */
    MCG_BWR_C4_DMX32(base, kMcgDmx32Default);

    /*
     * Errata: ERR007993
     * Workaround: Invert MCG_C4[DMX32] or change MCG_C4[DRST_DRS] before
     * reference clock source changes, then reset to previous value after
     * reference clock changes.
     */
    if (kMcgFllSrcExternal == CLOCK_HAL_GetFllSrc(base))
    {
        mcg_c4 = MCG_RD_C4(base);
        // Change the LSB of DRST_DRS.
        MCG_WR_C4(base, mcg_c4 ^ (1U << MCG_C4_DRST_DRS_SHIFT));
        change_drs = true;
    }

    /* Set CLKS and IREFS. */
    MCG_WR_C1(base, (MCG_RD_C1(base) & ~(MCG_C1_CLKS_MASK | MCG_C1_IREFS_MASK))
                  | (MCG_C1_CLKS(kMcgClkOutSrcInternal)  /* CLKS = 1 */
                  | MCG_C1_IREFS(kMcgFllSrcInternal))); /* IREFS = 1 */

    /* Wait for state change. */
    while (CLOCK_HAL_GetFllSrc(base) != kMcgFllSrcInternal) {}

    /* Errata: ERR007993 */
    if (change_drs)
    {
        MCG_WR_C4(base, mcg_c4);
    }

    if (kMcgIrcFast == ircSelect)
    {
        /* Update FCRDIV if necessary. */
        CLOCK_HAL_UpdateFastClkInternalRefDiv(base, fcrdivVal);
    }
    /* Set LP and IRCS. */
    MCG_WR_C2(base, (MCG_RD_C2(base) & ~(MCG_C2_LP_MASK | MCG_C2_IRCS_MASK))
                                       | MCG_C2_IRCS(ircSelect));

    while (CLOCK_HAL_GetInternalRefClkMode(base) != ircSelect){}

    MCG_WR_C4_DRST_DRS(base, drs);

    /* Wait for DRS to be set. */
    while (MCG_BRD_C4_DRST_DRS(base) != drs) {}

    while (CLOCK_HAL_GetClkOutStat(base) != kMcgClkOutStatInternal){}

    /* Wait for FLL stable time. */
    if (fllStableDelay)
    {
        fllStableDelay();
    }

    return kMcgModeErrNone;
}

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFbeMode
 * Description  : This function sets MCG to FBE mode.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_HAL_SetFbeMode(MCG_Type * base,
                             mcg_oscsel_select_t oscselVal,
                             uint8_t frdivVal,
                             mcg_dmx32_select_t dmx32,
                             mcg_dco_range_select_t drs,
                             void (* fllStableDelay)(void))
{
    uint8_t mcg_c4;
    bool change_drs = false;

#if MCG_MODE_CHECK_PARAM
    uint32_t extFreq;

    mcg_modes_t mode = CLOCK_HAL_GetMcgMode(base);
    if (!((kMcgModeFBI
         | kMcgModeFEI
         | kMcgModeFBE
         | kMcgModeFEE
         | kMcgModeBLPE
#if FSL_FEATURE_MCG_HAS_PLL
         | kMcgModePBE
#endif
          ) & (uint32_t)mode))
    {
        return kMcgModeErrModeUnreachable;
    }

    extFreq = CLOCK_HAL_TestOscFreq(base, oscselVal);

    if (0U == extFreq)
    {
        return kMcgModeErrOscFreqRange;
    }
#endif

#if FSL_FEATURE_MCG_HAS_PLL
    /* Set PLLS. */
    MCG_BWR_C6_PLLS(base, 0U);
    while ((CLOCK_HAL_IsPllSelected(base) != false)) {}
#endif

    /* Set LP bit to enable the FLL */
    MCG_BWR_C2_LP(base, 0U);

#if FSL_FEATURE_MCG_USE_OSCSEL
    MCG_BWR_C7_OSCSEL(base, oscselVal);
#endif

    /*
     * Errata: ERR007993
     * Workaround: Invert MCG_C4[DMX32] or change MCG_C4[DRST_DRS] before
     * reference clock source changes, then reset to previous value after
     * reference clock changes.
     */
    if (kMcgFllSrcInternal == CLOCK_HAL_GetFllSrc(base))
    {
        mcg_c4 = MCG_RD_C4(base);
        // Change the LSB of DRST_DRS.
        MCG_WR_C4(base, mcg_c4 ^ (1U << MCG_C4_DRST_DRS_SHIFT));
        change_drs = true;
    }

    /* Set CLKS and IREFS. */
    MCG_WR_C1(base, (MCG_RD_C1(base) & ~(MCG_C1_CLKS_MASK | MCG_C1_FRDIV_MASK | MCG_C1_IREFS_MASK))
                  | (MCG_C1_CLKS(kMcgClkOutSrcExternal)  /* CLKS = 2 */
                  | MCG_C1_FRDIV(frdivVal)            /* FRDIV = frdivVal */
                  | MCG_C1_IREFS(kMcgFllSrcExternal))); /* IREFS = 0 */

    /* Wait for Reference clock Status bit to clear */
    while (kMcgFllSrcExternal != CLOCK_HAL_GetFllSrc(base)) {}

    /* Errata: ERR007993 */
    if (change_drs)
    {
        MCG_WR_C4(base, mcg_c4);
    }

#if FSL_FEATURE_MCG_USE_OSCSEL
    if (kMcgOscselOsc == oscselVal)
#endif
    {
        if (MCG_BRD_C2_EREFS(base))
        {
            while(!CLOCK_HAL_IsOsc0Stable(base)){}
        }
    }

    /* Set DRST_DRS and DMX32. */
    MCG_WR_C4(base, (MCG_RD_C4(base)
                 & ~(MCG_C4_DMX32_MASK |
                     MCG_C4_DRST_DRS_MASK))
                 |  (MCG_C4_DMX32(dmx32) |
                     MCG_C4_DRST_DRS(drs)));

    /* Wait for DRS to be set. */
    while (MCG_BRD_C4_DRST_DRS(base) != drs) {}

    /* Wait for clock status bits to show clock source is ext ref clk */
    while (CLOCK_HAL_GetClkOutStat(base) != kMcgClkOutStatExternal) {}

    /* Wait for fll stable time. */
    if (fllStableDelay)
    {
        fllStableDelay();
    }

    return kMcgModeErrNone;
}

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetBlpiMode
 * Description  : This function sets MCG to BLPI mode.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_HAL_SetBlpiMode(MCG_Type * base,
                               uint8_t fcrdivVal,
                               mcg_irc_mode_t ircSelect)
{
#if MCG_MODE_CHECK_PARAM
    mcg_modes_t mode = CLOCK_HAL_GetMcgMode(base);
#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
    if (!((kMcgModeBLPI | kMcgModeFBI | kMcgModePBI) & (uint32_t)mode))
#else
    if (!((kMcgModeBLPI | kMcgModeFBI) & (uint32_t)mode))
#endif
    {
        return kMcgModeErrModeUnreachable;
    }
#endif

    if (kMcgIrcFast == ircSelect)
    {
        /* Update FCRDIV if necessary. */
        CLOCK_HAL_UpdateFastClkInternalRefDiv(base, fcrdivVal);
    }

    /* Set LP ans IRCS. */
    MCG_WR_C2(base, (MCG_RD_C2(base) & ~MCG_C2_IRCS_MASK)
                                       | MCG_C2_IRCS(ircSelect)
                                       | MCG_C2_LP_MASK);

    while (CLOCK_HAL_GetInternalRefClkMode(base) != ircSelect){}

    return kMcgModeErrNone;
}

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetBlpeMode
 * Description  : This function sets MCG to BLPE mode.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_HAL_SetBlpeMode(MCG_Type * base,
                               mcg_oscsel_select_t oscselVal)
{
#if MCG_MODE_CHECK_PARAM
    uint32_t extFreq;

    mcg_modes_t mode = CLOCK_HAL_GetMcgMode(base);
    if (!((kMcgModeFBE
         | kMcgModeBLPE
#if FSL_FEATURE_MCG_HAS_PLL
         | kMcgModePBE
#endif
          ) & (uint32_t)mode))
    {
        return kMcgModeErrModeUnreachable;
    }

    /* External OSC must be initialized before this function. */
    extFreq = CLOCK_HAL_TestOscFreq(base, oscselVal);

    if (0U == extFreq)
    {
        return kMcgModeErrOscFreqRange;
    }
#endif

    /* Set LP bit to enter BLPE mode. */
    MCG_BWR_C2_LP(base, 1U);

    CLOCK_HAL_PrepareOsc(base, oscselVal);

    return kMcgModeErrNone;
}

#if FSL_FEATURE_MCG_HAS_PLL
/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetPbeMode
 * Description  : This function sets MCG to PBE mode.
 *
 *END***********************************************************************************/
#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
mcg_mode_error_t CLOCK_HAL_SetPbeMode(MCG_Type * base,
                              mcg_oscsel_select_t oscselVal,
                              mcg_pll_ref_clock_source_t pll32kRef,
                              uint8_t frdivVal)
{
#if MCG_MODE_CHECK_PARAM
    mcg_modes_t mode = CLOCK_HAL_GetMcgMode(base);
    if (!((kMcgModeFBE | kMcgModePEE | kMcgModeBLPE) & (uint32_t)mode))
    {
        return kMcgModeErrModeUnreachable;
    }
#endif

    /* Clear LP */
    MCG_BWR_C2_LP(base, 0U);

    /* Set CLKS and IREFS. */
    MCG_WR_C1(base, (MCG_RD_C1(base) & ~(MCG_C1_CLKS_MASK | MCG_C1_FRDIV_MASK))
                  | (MCG_C1_CLKS(kMcgClkOutSrcExternal)  /* CLKS = 2 */
                  | MCG_C1_FRDIV(frdivVal)));            /* FRDIV = frdivVal */

    /* Wait for CLKST clock status bits to show clock source is ext ref clk */
    while (CLOCK_HAL_GetClkOutStat(base) != kMcgClkOutStatExternal) {}

    CLOCK_HAL_PrepareOsc(base, oscselVal);

    /* Set MCG_C7[PLL32KREFSEL] to select PLL reference clock source */
    CLOCK_HAL_SetPllRefSel0Mode(base, pll32kRef);

    /* Enable PLL. */
    MCG_BWR_C6_PLLS(base, 1U);

    /* wait for PLLST status bit to set */
    while ((CLOCK_HAL_IsPllSelected(base) != true)) {}

    /* Wait for LOCK bit to set */
    while (!CLOCK_HAL_IsPll0Locked(base)) {}

    return kMcgModeErrNone;
}
#else
mcg_mode_error_t CLOCK_HAL_SetPbeMode(MCG_Type * base,
                              mcg_oscsel_select_t oscselVal,
                              mcg_pll_clk_select_t pllcsSelect,
                              uint8_t prdivVal,
                              uint8_t vdivVal)
#if FSL_FEATURE_MCG_HAS_PLL1
{
#if MCG_MODE_CHECK_PARAM
    uint32_t extFreq, pllFreq;

    mcg_modes_t mode = CLOCK_HAL_GetMcgMode(base);
    if (!((kMcgModeFBE |
           kMcgModePEE |
           kMcgModePBE |
           kMcgModeBLPE) & (uint32_t)mode))
    {
        return kMcgModeErrModeUnreachable;
    }

    /* External OSC must be initialized before this function. */
    extFreq = CLOCK_HAL_TestOscFreq(base, oscselVal);

    if (0U == extFreq)
    {
        return kMcgModeErrOscFreqRange;
    }

    if (pllcsSelect == kMcgPllcsSelectPll1)
    {
        pllFreq = CLOCK_HAL_GetPll1RefFreq(base);
    }
    else
    {
        pllFreq = CLOCK_HAL_GetPll0RefFreq(base);
    }

    pllFreq = pllFreq / (prdivVal + FSL_FEATURE_MCG_PLL_PRDIV_BASE);

    if ((pllFreq < FSL_FEATURE_MCG_PLL_REF_MIN) ||
        (pllFreq > FSL_FEATURE_MCG_PLL_REF_MAX))
    {
        return kMcgModeErrPllPrdivRange;
    }
#endif

    /* Set LP bit to enable the PLL */
    MCG_BWR_C2_LP(base, 0U);

    /* Change to use external clock first. */
    MCG_BWR_C1_CLKS(base, kMcgClkOutSrcExternal);

    /* Wait for clock status bits to update */
    while (CLOCK_HAL_GetClkOutStat(base) != kMcgClkOutStatExternal) {}

    CLOCK_HAL_PrepareOsc(base, oscselVal);

    /* Set PLLS to select FLL. */
    MCG_BWR_C6_PLLS(base, 0U);
    // wait for PLLST status bit to clear.
    while ((CLOCK_HAL_IsPllSelected(base) != false)) {}

    /* Set PRDIV and VDIV. */
    if (pllcsSelect == kMcgPllcsSelectPll1)
    {
        MCG_BWR_C11_PLLCLKEN1(base, 0U);
        MCG_WR_C11_PRDIV1(base, prdivVal);
        MCG_WR_C12_VDIV1(base, vdivVal);
    }
    else
    {
        MCG_BWR_C5_PLLCLKEN0(base, 0U);
        MCG_WR_C5_PRDIV0(base, prdivVal);
        MCG_WR_C6_VDIV0(base, vdivVal);
    }

    CLOCK_HAL_SetPllcs(pllcsSelect);
    while (pllcsSelect != CLOCK_HAL_GetPllClkSelStatMode(base)) {}

    /* Set PLLS to select PLL. */
    MCG_BWR_C6_PLLS(base, 1U);
    // wait for PLLST status bit to set
    while ((CLOCK_HAL_IsPllSelected(base) != true)) {}

    /* Check lock. */
    if (pllcsSelect == kMcgPllcsSelectPll1)
    {
        while (!CLOCK_HAL_IsPll1Locked(base)) {}
    }
    else
    {
        while (!CLOCK_HAL_IsPll0Locked(base)) {}
    }

    return kMcgModeErrNone;
}
#else
{
#if MCG_MODE_CHECK_PARAM
    uint32_t extFreq, pllRefFreq;

    mcg_modes_t mode = CLOCK_HAL_GetMcgMode(base);
    if (!((kMcgModeFBE | kMcgModePEE | kMcgModeBLPE) & (uint32_t)mode))
    {
        return kMcgModeErrModeUnreachable;
    }

    /* External OSC must be initialized before this function. */
    extFreq = CLOCK_HAL_TestOscFreq(base, oscselVal);

    if (0U == extFreq)
    {
        return kMcgModeErrOscFreqRange;
    }
#endif

#if FSL_FEATURE_MCG_HAS_EXTERNAL_PLL
    /* Set PLLCS to select PLL. */
    CLOCK_HAL_SetPllClkSelMode(base, pllcsSelect);
    while (pllcsSelect != CLOCK_HAL_GetPllClkSelMode(base)) {}

    if (pllcsSelect == kMcgPllClkSelPll0)
    {
#endif    
#if MCG_MODE_CHECK_PARAM
        /* Check whether PRDIV value is OK. */
        pllRefFreq = extFreq / (prdivVal + FSL_FEATURE_MCG_PLL_PRDIV_BASE);

        if ((pllRefFreq < FSL_FEATURE_MCG_PLL_REF_MIN) ||
            (pllRefFreq > FSL_FEATURE_MCG_PLL_REF_MAX))
        {
            return kMcgModeErrPllPrdivRange;
        }
#endif
#if FSL_FEATURE_MCG_HAS_EXTERNAL_PLL
    }
#endif
    /* Set LP bit to enable the FLL */
    MCG_BWR_C2_LP(base, 0U);

    /* Change to use external clock first. */
    MCG_BWR_C1_CLKS(base, kMcgClkOutSrcExternal);

    /* Wait for clock status bits to update */
    while (CLOCK_HAL_GetClkOutStat(base) != kMcgClkOutStatExternal) {}

    CLOCK_HAL_PrepareOsc(base, oscselVal);

    // Disable PLL first, then configure PLL.
    CLOCK_HAL_SetPll0EnableCmd(base, false);
    MCG_BWR_C6_PLLS(base, 0U);

    // wait for PLLST status bit to clear.
    while ((CLOCK_HAL_IsPllSelected(base) != false)) {}
#if FSL_FEATURE_MCG_HAS_EXTERNAL_PLL
    if (pllcsSelect == kMcgPllClkSelPll0)
    {
#endif    
        MCG_WR_C5_PRDIV0(base, prdivVal);

        MCG_WR_C6_VDIV0(base, vdivVal);

        // Enable PLL.
        MCG_BWR_C6_PLLS(base, 1U);

        // wait for PLLST status bit to set
        while ((CLOCK_HAL_IsPllSelected(base) != true)) {}

        /* Wait for LOCK bit to set */
        while (!CLOCK_HAL_IsPll0Locked(base)) {}
#if FSL_FEATURE_MCG_HAS_EXTERNAL_PLL
    }
    else
    {
        // Enable PLL.
        MCG_BWR_C6_PLLS(base, 1U);

        // wait for PLLST status bit to set
        while ((CLOCK_HAL_IsPllSelected(base) != true)) {}
    }
#endif   
    return kMcgModeErrNone;
}
#endif // FSL_FEATURE_MCG_HAS_PLL1
#endif // FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetPeeMode
 * Description  : This function sets MCG to PEE mode.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_HAL_SetPeeMode(MCG_Type * base)
{
#if MCG_MODE_CHECK_PARAM
    mcg_modes_t mode = CLOCK_HAL_GetMcgMode(base);
    if (kMcgModePBE != mode)
    {
        return kMcgModeErrModeUnreachable;
    }
#endif

    /* Change to use PLL/FLL output clock first. */
    MCG_BWR_C1_CLKS(base, kMcgClkOutSrcOut);

    /* Wait for clock status bits to update */
    while (CLOCK_HAL_GetClkOutStat(base) != kMcgClkOutStatPll) {}

    return kMcgModeErrNone;
}

#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
/*FUNCTION******************************************************************************
 *
 * Function name : CLOCK_HAL_SetPbiMode
 * Description  : This function sets MCG to PBI mode.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_HAL_SetPbiMode(MCG_Type * base,
                                      mcg_irc_mode_t ircSelect,
                                      uint8_t fcrdivVal)
{
#if MCG_MODE_CHECK_PARAM
    mcg_modes_t mode = CLOCK_HAL_GetMcgMode(base);

    if (!((kMcgModeFBI | kMcgModePEI | kMcgModeBLPI | kMcgModePBI) & (uint32_t)mode))
    {
        return kMcgModeErrModeUnreachable;
    }
#endif

    if (kMcgIrcFast == ircSelect)
    {
        /* Update FCRDIV if necessary. */
        CLOCK_HAL_UpdateFastClkInternalRefDiv(base, fcrdivVal);
    }
    /* Set LP and IRCS. */
    MCG_WR_C2(base, (MCG_RD_C2(base) & ~(MCG_C2_LP_MASK | MCG_C2_IRCS_MASK))
                                       | MCG_C2_IRCS(ircSelect));

    while (CLOCK_HAL_GetInternalRefClkMode(base) != ircSelect){}

    /* Set MCG_C7[PLL32KREFSEL] to select slow IRC clock source */
    CLOCK_HAL_SetPllRefSel0Mode(base, kMcgPllRefClkSrcSlowIrc);

    /* Set CLKS and IREFS. */
    MCG_WR_C1(base, (MCG_RD_C1(base) & ~(MCG_C1_CLKS_MASK | MCG_C1_IREFS_MASK))
                  | (MCG_C1_CLKS(kMcgClkOutSrcInternal) /* CLKS = 1  */
                  | MCG_C1_IREFS(kMcgFllSrcInternal))); /* IREFS = 1 */

    /* Wait for CLKST, IREFST state change. */
    while (CLOCK_HAL_GetFllSrc(base) != kMcgFllSrcInternal) {}

    while (CLOCK_HAL_GetClkOutStat(base) != kMcgClkOutStatInternal){}

    /* set PLLS to select PLL */
    MCG_BWR_C6_PLLS(base, 1U);
    /* wait for PLLST status bit to set */
    while ((CLOCK_HAL_IsPllSelected(base) != true)) {}

    return kMcgModeErrNone;
}

/*FUNCTION******************************************************************************
 *
 * Function name : CLOCK_HAL_SetPeiMode
 * Description  : This function sets MCG to PEI mode.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_HAL_SetPeiMode(MCG_Type * base)
{

#if MCG_MODE_CHECK_PARAM
    mcg_modes_t mode = CLOCK_HAL_GetMcgMode(base);
    if (kMcgModePBI != mode)
    {
        return kMcgModeErrModeUnreachable;
    }
#endif

    /* Change to use PLL/FLL output clock first. */
    MCG_BWR_C1_CLKS(base, kMcgClkOutSrcOut);

    /* Wait for clock status bits to update */
    while (CLOCK_HAL_GetClkOutStat(base) != kMcgClkOutStatPll) {}

    return kMcgModeErrNone;
}
#endif // FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE

#endif // FSL_FEATURE_MCG_HAS_PLL

#endif // FSL_FEATURE_SOC_MCG_COUNT
