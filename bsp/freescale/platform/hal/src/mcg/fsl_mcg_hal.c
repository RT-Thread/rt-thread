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

#include "fsl_mcg_hal.h"
#if FSL_FEATURE_SOC_MCG_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

/* This frequency values should be set by different boards. */
uint32_t g_xtal0ClkFreq;           /* EXTAL0 clock */
#if FSL_FEATURE_MCG_HAS_OSC1
uint32_t g_xtal1ClkFreq;           /* EXTAL1 clock */
#endif
#if FSL_FEATURE_MCG_HAS_EXTERNAL_PLL
uint32_t g_extPllClkFreq;          /* External PLL clock */
#endif
uint32_t g_xtalRtcClkFreq;         /* EXTAL RTC clock */

uint32_t g_fastInternalRefClkFreq = 4000000U;
uint32_t g_slowInternalRefClkFreq = 32768U;


/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_TestOscFreq
 * Description   : This function checks MCG external OSC clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_TestOscFreq(MCG_Type * base, mcg_oscsel_select_t oscselVal)
{
    uint32_t extFreq;

#if FSL_FEATURE_MCG_USE_OSCSEL
    switch (oscselVal)
    {
        case kMcgOscselOsc:         /* Selects System Oscillator (OSCCLK) */
            extFreq = g_xtal0ClkFreq;
            break;
#if FSL_FEATURE_MCG_HAS_RTC_32K
        case kMcgOscselRtc:         /* Selects 32 kHz RTC Oscillator */
            extFreq = g_xtalRtcClkFreq;
            break;
#endif
#if FSL_FEATURE_MCG_HAS_IRC_48M
        case kMcgOscselIrc:         /* Selects 48 MHz IRC Oscillator */
            extFreq = CPU_INTERNAL_IRC_48M;
            break;
#endif
        default:
            extFreq = 0U;
            break;
    }
#else
    extFreq = g_xtal0ClkFreq;
#endif
    return extFreq;
}

/*FUNCTION******************************************************************************
 *
 * Function name : CLOCK_HAL_PrepareOsc
 * Description  : This function selects the OSC as clock source, and wait for it
 * is stable.
 *
 *END***********************************************************************************/
void CLOCK_HAL_PrepareOsc(MCG_Type * base, mcg_oscsel_select_t setting)
{
#if FSL_FEATURE_MCG_USE_OSCSEL
    MCG_BWR_C7_OSCSEL(base, setting);
    if (kMcgOscselOsc == setting)
#endif
    {
#if FSL_FEATURE_SOC_OSC_COUNT 
        if (MCG_BRD_C2_EREFS(base))
        {
            while(!CLOCK_HAL_IsOsc0Stable(base)){}
        }
#endif        
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetMcgExternalClkFreq
 * Description   : This is an internal function to get the MCG external clock
 * frequency. MCG external clock could be OSC0, RTC or IRC48M, choosed by
 * register OSCSEL.
 *
 *END**************************************************************************/
static uint32_t CLOCK_HAL_GetMcgExternalClkFreq(MCG_Type * base)
{
#if FSL_FEATURE_MCG_USE_OSCSEL
    /* OSC frequency selected by OSCSEL. */
    return CLOCK_HAL_TestOscFreq(base, (mcg_oscsel_select_t)MCG_BRD_C7_OSCSEL(base));
#else
    /* Use default osc0*/
    return g_xtal0ClkFreq;
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_TestFllExternalRefFreq
 * Description   : Calculates the Fll external reference clock frequency based
 * on input parameters.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_TestFllExternalRefFreq(MCG_Type * base,
                                          uint32_t extFreq,
                                          uint8_t  frdivVal,
                                          osc_range_t range0,
                                          mcg_oscsel_select_t oscsel)
{
    extFreq >>= frdivVal;

    if ((kOscRangeLow != range0)
#if FSL_FEATURE_MCG_USE_OSCSEL
      && (kMcgOscselRtc != oscsel)
#endif
        )
    {
        switch (frdivVal)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                extFreq >>= 5U;
                break;
#if FSL_FEATURE_MCG_FRDIV_SUPPORT_1280
            case 6:
                extFreq /= 20U; /* 64*20=1280 */
                break;
#endif
#if FSL_FEATURE_MCG_FRDIV_SUPPORT_1536
            case 7:
                extFreq /= 12U; /* 128*12=1536 */
                break;
#endif
            default:
                extFreq = 0U; /* Reserved. */
                break;
        }
    }
    return extFreq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetFllRefclk
 * Description   : Internal function to find the fll reference clock
 * This is an internal function to get the fll reference clock. The returned
 * value will be used for other APIs to calculate teh fll and other clock value.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetFllRefClk(MCG_Type * base)
{
    uint32_t mcgffclk;
    uint8_t frdiv;
    osc_range_t range;
    mcg_oscsel_select_t oscsel;

    if (MCG_BRD_C1_IREFS(base) == kMcgFllSrcExternal)
    {
        /* External reference clock is selected */
        mcgffclk = CLOCK_HAL_GetMcgExternalClkFreq(base);
        frdiv = MCG_BRD_C1_FRDIV(base);
        range = (osc_range_t)MCG_BRD_C2_RANGE(base);
#if FSL_FEATURE_MCG_USE_OSCSEL
        oscsel = (mcg_oscsel_select_t)MCG_BRD_C7_OSCSEL(base);
#else
        oscsel = kMcgOscselOsc;
#endif

        mcgffclk = CLOCK_HAL_TestFllExternalRefFreq(base, mcgffclk, frdiv, range, oscsel);
    }
    else
    {
        /* The slow internal reference clock is selected */
        mcgffclk = g_slowInternalRefClkFreq;
    }
    return mcgffclk;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_TestFllFreq
 * Description   : Calculate the Fll frequency based on input parameters.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_TestFllFreq(MCG_Type * base,
                               uint32_t fllRef,
                               mcg_dmx32_select_t dmx32,
                               mcg_dco_range_select_t drs)
{
    static const uint16_t fllFactorTable[4][2] = {
        {640,  732},
        {1280, 1464},
        {1920, 2197},
        {2560, 2929}
    };

    /* if DMX32 set */
    if (dmx32)
    {
        if (fllRef > kMcgConstant32768)
        {
            return 0U;
        }
    }
    else
    {
        if ((fllRef < kMcgConstant31250) || (fllRef > kMcgConstant39063))
        {
            return 0U;
        }
    }

    return fllRef * fllFactorTable[drs][dmx32];
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetFllclk
 * Description   : Get the current mcg fll clock
 * This function will return the mcgfllclk value in frequency(hz) based on
 * current mcg configurations and settings. Fll should be properly configured
 * in order to get the valid value.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetFllClk(MCG_Type * base)
{
    uint32_t mcgfllclk;
    mcg_dmx32_select_t dmx32;
    mcg_dco_range_select_t drs;

#if FSL_FEATURE_MCG_HAS_PLL
    /* If FLL is not enabled, return 0. */
    if (CLOCK_HAL_IsPllSelected(base))
    {
        return 0U;
    }
#endif

    mcgfllclk = CLOCK_HAL_GetFllRefClk(base);

    if (0U == mcgfllclk)
    {
        return 0U;
    }

    dmx32 = (mcg_dmx32_select_t)MCG_BRD_C4_DMX32(base);
    drs   = (mcg_dco_range_select_t)MCG_BRD_C4_DRST_DRS(base);


    mcgfllclk = CLOCK_HAL_TestFllFreq(base, mcgfllclk, dmx32, drs);

    return mcgfllclk;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_UpdateFastClkInternalRefDiv
 * Description   : This fucntion sets FCRDIV to a new value. FCRDIV can not be
 * changed when fast internal reference is enabled, this function checks the
 * status, if it is enabled, disable it first, then set FCRDIV, at last reenable
 * it. If you can make sure fast internal reference is not enabled, call
 * MCG_WR_SC_FCRDIV() will be more effective.
 *
 *END**************************************************************************/
void CLOCK_HAL_UpdateFastClkInternalRefDiv(MCG_Type * base, uint8_t fcrdiv)
{
    /* If new value equals current value, do not update. */
    if (MCG_BRD_SC_FCRDIV(base) != fcrdiv)
    {
        /* If fast internal reference clock is not used, change directly. */
        if (kMcgIrcSlow == MCG_BRD_C2_IRCS(base))
        {
            MCG_WR_SC_FCRDIV(base, fcrdiv);
        }
        else /* If it is used, swith to slow IRC, then change FCRDIV. */
        {
            /* Switch to slow IRC. */
            CLOCK_HAL_SetInternalRefClkMode(base, kMcgIrcSlow);
            while (kMcgIrcSlow != CLOCK_HAL_GetInternalRefClkMode(base)) {}
            /* Set new value. */
            MCG_WR_SC_FCRDIV(base, fcrdiv);
            /* Switch to fast IRC. */
            CLOCK_HAL_SetInternalRefClkMode(base, kMcgIrcFast);
            while (kMcgIrcFast != CLOCK_HAL_GetInternalRefClkMode(base)) {}
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_UpdateInternalRefClk
 * Description   : This function setup the MCGIRCLK.
 *
 *END**************************************************************************/
void CLOCK_HAL_UpdateInternalRefClk(MCG_Type      *base,
                                    mcg_irc_mode_t ircs,
                                    uint8_t        fcrdiv,
                                    bool           enableInStop)
{
    if (kMcgIrcFast == ircs)
    {
        CLOCK_HAL_UpdateFastClkInternalRefDiv(base, fcrdiv);
        /* Switch to fast IRC. */
        CLOCK_HAL_SetInternalRefClkMode(base, kMcgIrcFast);
        while (kMcgIrcFast != CLOCK_HAL_GetInternalRefClkMode(base)) {}
    }
    else
    {
        /* Switch to slow IRC. */
        CLOCK_HAL_SetInternalRefClkMode(base, kMcgIrcSlow);
        while (kMcgIrcSlow != CLOCK_HAL_GetInternalRefClkMode(base)) {}
    }

    // Enable MCGIRCLK.
    MCG_WR_C1(base, (MCG_RD_C1(base) & ~MCG_C1_IREFSTEN_MASK)
                                     |  MCG_C1_IRCLKEN_MASK
                                     |  MCG_C1_IREFSTEN(enableInStop));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetAvailableFrdiv
 * Description   : This fucntion calculates the proper FRDIV setting according
 * to FLL reference clock.
 *
 *END**************************************************************************/
mcg_status_t CLOCK_HAL_GetAvailableFrdiv(osc_range_t range0,
                                    mcg_oscsel_select_t oscsel,
                                    uint32_t inputFreq,
                                    uint8_t  *frdiv)
{
    *frdiv = 0U;
    static const uint16_t freq_kHz[] = {
        1250U, 2500U, 5000U, 10000U, 20000U, 40000U,
#if FSL_FEATURE_MCG_FRDIV_SUPPORT_1280
        50000U,
#endif
#if FSL_FEATURE_MCG_FRDIV_SUPPORT_1536
        60000U
#endif
    };

    static const uint16_t freqLow_kHz[] = {
        1000U, 2000U, 4000U, 8000U, 16000U, 32000U,
#if FSL_FEATURE_MCG_FRDIV_SUPPORT_1280
        40000U,
#endif
#if FSL_FEATURE_MCG_FRDIV_SUPPORT_1536
        48000U
#endif
    };

    if ((kOscRangeLow != range0)
#if FSL_FEATURE_MCG_USE_OSCSEL
        && (kMcgOscselRtc != oscsel)
#endif
       )
    {
        inputFreq /= 1000U;
        while (*frdiv < (sizeof(freq_kHz)/sizeof(freq_kHz[0])))
        {
            if (inputFreq <= freq_kHz[*frdiv])
            {
                if (inputFreq >= freqLow_kHz[*frdiv])
                {
                    return kStatus_MCG_Success;
                }
                else
                {
                    return kStatus_MCG_Fail;
                }
            }
            (*frdiv)++;
        }
    }
    else
    {
        while (inputFreq > 39063U)
        {
            inputFreq >>= 1U;
            (*frdiv)++;
        }
        if (((*frdiv) < 8U) && (inputFreq >= 31250U))
        {
            return kStatus_MCG_Success;
        }
    }
    return kStatus_MCG_Fail;
}

#if FSL_FEATURE_MCG_HAS_PLL
#if (FSL_FEATURE_MCG_HAS_PLL_PRDIV ) && ( FSL_FEATURE_MCG_HAS_PLL_VDIV )
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_CalculatePllDiv
 * Description   : Calculates the PLL PRVID and VDIV.
 * This function calculates the proper PRDIV and VDIV to generate desired PLL
 * output frequency with input reference clock frequency. It returns the closest
 * frequency PLL could generate, the corresponding PRDIV/VDIV are returned from
 * parameters. If desire frequency is not valid, this funtion returns 0.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_CalculatePllDiv(uint32_t refFreq,
                                   uint32_t desireFreq,
                                   uint8_t *prdiv,
                                   uint8_t *vdiv)
{
    uint8_t ret_prdiv, ret_vdiv;
    uint8_t prdiv_min, prdiv_max, prdiv_cur;
    uint8_t vdiv_cur;
    uint32_t ret_freq = 0U;
    uint32_t diff = 0xFFFFFFFFU; // Difference between desireFreq and return frequency.
    uint32_t ref_div; // Reference frequency after PRDIV.

    /* Reference frequency is out of range. */
    if ((refFreq < FSL_FEATURE_MCG_PLL_REF_MIN) ||
        (refFreq > (FSL_FEATURE_MCG_PLL_REF_MAX *
                   (FSL_FEATURE_MCG_PLL_PRDIV_MAX + FSL_FEATURE_MCG_PLL_PRDIV_BASE))))
    {
        return 0U;
    }

    /* refFreq/PRDIV must in a range. First get the allowed PRDIV range. */
    prdiv_max = refFreq / FSL_FEATURE_MCG_PLL_REF_MIN;
    prdiv_min = (refFreq + FSL_FEATURE_MCG_PLL_REF_MAX - 1U) / FSL_FEATURE_MCG_PLL_REF_MAX;

#if FSL_FEATURE_MCG_HAS_PLL_INTERNAL_DIV
    desireFreq *= 2U;
#endif

    /* PRDIV traversal. */
    for (prdiv_cur=prdiv_max; prdiv_cur>=prdiv_min; prdiv_cur--)
    {
        // Reference frequency after PRDIV.
        ref_div = refFreq / prdiv_cur;

        vdiv_cur = desireFreq / ref_div;

        if ((vdiv_cur < FSL_FEATURE_MCG_PLL_VDIV_BASE-1U) ||
            (vdiv_cur > FSL_FEATURE_MCG_PLL_VDIV_BASE+31U))
        {
            /* No VDIV is available with this PRDIV. */
            continue;
        }

        ret_freq = vdiv_cur * ref_div;

        if (vdiv_cur >= FSL_FEATURE_MCG_PLL_VDIV_BASE)
        {
            if (ret_freq == desireFreq) // If desire frequency is got.
            {
                *prdiv = prdiv_cur  - FSL_FEATURE_MCG_PLL_PRDIV_BASE;
                *vdiv  = vdiv_cur   - FSL_FEATURE_MCG_PLL_VDIV_BASE;
#if FSL_FEATURE_MCG_HAS_PLL_INTERNAL_DIV
                return ret_freq / 2U;
#else
                return ret_freq;
#endif
            }
            if (diff > desireFreq - ret_freq) // New PRDIV/VDIV is closer.
            {
                diff = desireFreq - ret_freq;
                ret_prdiv = prdiv_cur;
                ret_vdiv  = vdiv_cur;
            }
        }
        vdiv_cur ++;
        if (vdiv_cur <= (FSL_FEATURE_MCG_PLL_VDIV_BASE+31U))
        {
            ret_freq += ref_div;
            if (diff > ret_freq - desireFreq) // New PRDIV/VDIV is closer.
            {
                diff = ret_freq - desireFreq;
                ret_prdiv = prdiv_cur;
                ret_vdiv  = vdiv_cur;
            }
        }
    }

    if (0xFFFFFFFFU != diff)
    {
        /* PRDIV/VDIV found. */
        *prdiv = ret_prdiv - FSL_FEATURE_MCG_PLL_PRDIV_BASE;
        *vdiv  = ret_vdiv  - FSL_FEATURE_MCG_PLL_VDIV_BASE;
        ret_freq = (refFreq / ret_prdiv) * ret_vdiv;
#if FSL_FEATURE_MCG_HAS_PLL_INTERNAL_DIV
        return ret_freq / 2U;
#else
        return ret_freq;
#endif
    }
    else
    {
        return 0U; // No proper PRDIV/VDIV found.
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetPll0RefFreq
 * Description   : Get PLL0 external reference clock frequency, it could be
 * selected by OSCSEL or PLLREFSEL, according to chip design.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetPll0RefFreq(MCG_Type * base)
{
#if FSL_FEATURE_MCG_HAS_PLL1
    /* Use dedicate source. */
    if (kMcgPllExternalRefClkSelOsc0 == CLOCK_HAL_GetPllRefSel0Mode(base))
    {
        return g_xtal0ClkFreq;
    }
    else
    {
        return g_xtal1ClkFreq;
    }
#else
    /* Use OSCSEL frequency. */
    return CLOCK_HAL_GetMcgExternalClkFreq(base);
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetPll0clk
 * Description   : Get the current mcg pll/pll0 clock
 * This function will return the mcgpllclk/mcgpll0 value in frequency(hz) based
 * on current mcg configurations and settings. PLL/PLL0 should be properly
 * configured in order to get the valid value.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetPll0Clk(MCG_Type * base)
{
    uint32_t mcgpll0clk;
    uint8_t  divider;

    /* If PLL0 is not enabled, return 0. */
    if (!(MCG_BRD_S_PLLST(base) || MCG_BRD_C5_PLLCLKEN0(base)))
    {
        return 0U;
    }

    mcgpll0clk = CLOCK_HAL_GetPll0RefFreq(base);

    divider = (FSL_FEATURE_MCG_PLL_PRDIV_BASE + MCG_BRD_C5_PRDIV0(base));

    /* Calculate the PLL reference clock*/
    mcgpll0clk /= divider;
    divider = (MCG_BRD_C6_VDIV0(base) + FSL_FEATURE_MCG_PLL_VDIV_BASE);

    /* Calculate the MCG output clock*/
    mcgpll0clk = (mcgpll0clk * divider);

#if FSL_FEATURE_MCG_HAS_PLL_INTERNAL_DIV
    mcgpll0clk >>= 1U;
#endif
    return mcgpll0clk;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_EnablePll0InFllMode
 * Description   : Enable PLL0 when MCG is in FLL mode.
 *
 *END**************************************************************************/
void CLOCK_HAL_EnablePll0InFllMode(MCG_Type * base,
                                   uint8_t prdiv,
                                   uint8_t vdiv,
                                   bool enableInStop)
{
    MCG_WR_C6_VDIV0(base, vdiv);
    MCG_WR_C5(base, (MCG_RD_C5(base)
                 & ~(MCG_C5_PLLSTEN0_MASK | MCG_C5_PRDIV0_MASK))
                 |   MCG_C5_PLLCLKEN0_MASK
                 |   MCG_C5_PLLSTEN0(enableInStop)
                 |   MCG_C5_PRDIV0(prdiv));
    while(!CLOCK_HAL_IsPll0Locked(base)) {} // Wait until locked.
}

#else
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetPll0RefFreq
 * Description   : Get PLL0 external reference clock frequency, it is
 * selected by PLL32KREFSEL, for kinetis M series.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetPll0RefFreq(MCG_Type * base)
{
    uint32_t pll0RefFreq;
    mcg_pll_ref_clock_source_t pll0RefSrc;

    pll0RefSrc = (mcg_pll_ref_clock_source_t)MCG_RD_C7_PLL32KREFSEL(base);

    switch(pll0RefSrc)
    {
    case kMcgPllRefClkSrcRtc:
          pll0RefFreq = g_xtalRtcClkFreq;
          break;
    case kMcgPllRefClkSrcSlowIrc:
          pll0RefFreq = g_xtalRtcClkFreq;
          break;
    case kMcgPllRefClkSrcFllExtRef:
          /* Note: Before enter PEE or PBE mode, the IREFS shall be set to 0 */
          pll0RefFreq = CLOCK_HAL_GetFllRefClk(base); /* SELECT EXT REF FOR FLL */
          break;
    default:
          pll0RefFreq = 0;
          break;
    }

    if((pll0RefFreq < kMcgConstant31250) || (pll0RefFreq > kMcgConstant39063))
    {
        return 0;
    }
    else
    {
        return pll0RefFreq;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetPll0clk
 * Description   : Get the current mcg pll/pll0 clock
 * This function will return the mcgpllclk/mcgpll0 value in frequency(hz) based
 * on current mcg configurations and settings. PLL/PLL0 should be properly
 * configured in order to get the valid value.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetPll0Clk(MCG_Type * base)
{
    uint32_t mcgpll0clk;

    mcgpll0clk = CLOCK_HAL_GetPll0RefFreq(base);
    mcgpll0clk *= 375U;

#if FSL_FEATURE_MCG_HAS_PLL_INTERNAL_DIV
    mcgpll0clk >>= 1U;
#endif
    return mcgpll0clk;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_EnablePll0InFllMode
 * Description   : Enable PLL0 when MCG is in FLL mode.
 *
 *END**************************************************************************/
void CLOCK_HAL_EnablePll0InFllMode(MCG_Type * base,
                                   bool enableInStop)
{
    MCG_WR_C5(base, (MCG_RD_C5(base)
                 & ~(MCG_C5_PLLSTEN0_MASK))
                 |   MCG_C5_PLLCLKEN0_MASK
                 |   MCG_C5_PLLSTEN0(enableInStop)
              );
    while(!CLOCK_HAL_IsPll0Locked(base)) {} // Wait until locked.
}
#endif
#endif

#if FSL_FEATURE_MCG_HAS_PLL1
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetPll1RefFreq
 * Description   : Get PLL1 external reference clock frequency, it is
 * selected by PLLREFSEL.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetPll1RefFreq(MCG_Type * base)
{
    if (kMcgPllExternalRefClkSelOsc0 == CLOCK_HAL_GetPllRefSel1Mode(base))
    {
        return g_xtal0ClkFreq;
    }
    else
    {
        return g_xtal1ClkFreq;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetPll1Clk
 * Description   : Get the current mcg pll1 clock
 * This function will return the mcgpll1clk value in frequency(hz) based
 * on current mcg configurations and settings. PLL1 should be properly configured
 * in order to get the valid value.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetPll1Clk(MCG_Type * base)
{
    uint32_t mcgpll1clk;
    uint8_t  divider;

    /* If PLL1 is not enabled, return 0. */
    if (!(MCG_BRD_S_PLLST(base) || MCG_BRD_C11_PLLCLKEN1(base)))
    {
        return 0U;
    }

    mcgpll1clk = CLOCK_HAL_GetPll1RefFreq(base);

    divider = (FSL_FEATURE_MCG_PLL_PRDIV_BASE + MCG_BRD_C11_PRDIV1(base));

    /* Calculate the PLL reference clock*/
    mcgpll1clk /= divider;
    divider = (MCG_BRD_C12_VDIV1(base) + FSL_FEATURE_MCG_PLL_VDIV_BASE);

    /* Calculate the MCG output clock*/
    mcgpll1clk = (mcgpll1clk * divider); /* divided by 2*/
#if FSL_FEATURE_MCG_HAS_PLL_INTERNAL_DIV
    mcgpll1clk >>= 1U;
#endif
    return mcgpll1clk;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_EnablePll1InFllMode
 * Description   : Enable PLL1 when MCG is in FLL mode.
 *
 *END**************************************************************************/
void CLOCK_HAL_EnablePll1InFllMode(MCG_Type * base,
                                   uint8_t prdiv,
                                   uint8_t vdiv,
                                   bool enableInStop)
{
    MCG_WR_C12_VDIV1(base, vdiv);
    MCG_WR_C11(base, (MCG_RD_C11(base)
                  & ~(MCG_C11_PLLSTEN1_MASK | MCG_C11_PRDIV1_MASK))
                  |   MCG_C11_PLLCLKEN1_MASK
                  |   MCG_C11_PLLSTEN1(enableInStop)
                  |   MCG_C11_PRDIV1(prdiv));
    while(!CLOCK_HAL_IsPll1Locked(base)) {} // Wait until locked.
}
#endif

#if FSL_FEATURE_MCG_HAS_EXTERNAL_PLL
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetExtPllClk
 * Description   : Get the current external pll clock.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetExtPllClk(MCG_Type * base)
{
    return g_extPllClkFreq;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetInternalRefClk
 * Description   : Get the current mcg internal reference clock (MCGIRCLK)
 * This function will return the mcgirclk value in frequency(hz) based
 * on current mcg configurations and settings. It will not check if the
 * mcgirclk is enabled or not, just calculate and return the value.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetInternalRefClk(MCG_Type * base)
{
    uint32_t mcgirclk;

    if (!MCG_BRD_C1_IRCLKEN(base))
    {
        return 0U;
    }

    if (MCG_BRD_C2_IRCS(base) == kMcgIrcSlow)
    {
        /* Slow internal reference clock selected*/
        mcgirclk = g_slowInternalRefClkFreq;
    }
    else
    {
        mcgirclk = g_fastInternalRefClkFreq >> MCG_BRD_SC_FCRDIV(base);
    }
    return mcgirclk;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetFixedFreqClk
 * Description   : Get the MCGFFCLK frequency.
 * This function get the MCGFFCLK, it is only valid when its frequency is not
 * more than MCGOUTCLK/8. If MCGFFCLK is invalid, this function returns 0.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetFixedFreqClk(MCG_Type * base)
{
    uint32_t freq = CLOCK_HAL_GetFllRefClk(base);

    /* MCGFFCLK must be no more than MCGOUTCLK/8. */
    if ((freq) && (freq <= (CLOCK_HAL_GetOutClk(base)/8U)))
    {
        return freq;
    }
    else
    {
        return 0U;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetOutclk
 * Description   : Get the current mcg out clock
 * This function will return the mcgoutclk value in frequency(hz) based on
 * current mcg configurations and settings. The configuration should be
 * properly done in order to get the valid value.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetOutClk(MCG_Type * base)
{
    uint32_t mcgoutclk;
    mcg_clkout_stat_t src = CLOCK_HAL_GetClkOutStat(base);

    switch (src)
    {
#if FSL_FEATURE_MCG_HAS_PLL
        case kMcgClkOutStatPll:
#if FSL_FEATURE_MCG_HAS_PLL1
            if (CLOCK_HAL_GetPllClkSelMode(base) == kMcgPllClkSelPll1)
            {
                mcgoutclk = CLOCK_HAL_GetPll1Clk(base);
            }
            else
#endif
#if FSL_FEATURE_MCG_HAS_EXTERNAL_PLL
            if (CLOCK_HAL_GetPllClkSelMode(base) == kMcgPllClkSelExtPll)
            {
                mcgoutclk = CLOCK_HAL_GetExtPllClk(base);
            }
            else
#endif
            {
                mcgoutclk = CLOCK_HAL_GetPll0Clk(base);
            }
            break;
#endif                                
        case kMcgClkOutStatFll:
            mcgoutclk = CLOCK_HAL_GetFllClk(base);
            break;
        case kMcgClkOutStatInternal:  /* Internal clock. */
            mcgoutclk = CLOCK_HAL_GetInternalRefClk(base);
            break;
        case kMcgClkOutStatExternal:  /* External clock. */
            mcgoutclk = CLOCK_HAL_GetMcgExternalClkFreq(base);
            break;
        default:
            mcgoutclk = 0U;
            break;
    }
    return mcgoutclk;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_SetOsc0Mode
 * Description   : Set the OSC0 work mode.
 * This function set OSC0 work mode, include frequency range select, high gain
 * oscillator select and external reference select.
 *
 *END**************************************************************************/
void CLOCK_HAL_SetOsc0Mode(MCG_Type * base,
                           osc_range_t range,
                           osc_gain_t hgo,
                           osc_src_t erefs)
{
    MCG_WR_C2(base, (MCG_RD_C2(base)
                  & ~(MCG_C2_RANGE_MASK  |
                      MCG_C2_HGO_MASK    |
                      MCG_C2_EREFS_MASK))
                  |  (MCG_C2_RANGE(range)|
                      MCG_C2_HGO(hgo)    |
                      MCG_C2_EREFS(erefs)));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_EnableOsc0Monitor
 * Description   : Enable the OSC0 external clock monitor.
 *
 *END**************************************************************************/
void CLOCK_HAL_EnableOsc0Monitor(MCG_Type * base, mcg_osc_monitor_mode_t mode)
{
    MCG_BWR_C2_LOCRE0(base, mode);
    MCG_BWR_C6_CME0(base, 1U);
}

#if FSL_FEATURE_MCG_HAS_RTC_32K
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_EnableRtcOscMonitor
 * Description   : Enable the RTC OSC external clock monitor.
 *
 *END**************************************************************************/
void CLOCK_HAL_EnableRtcOscMonitor(MCG_Type * base, mcg_osc_monitor_mode_t mode)
{
    MCG_BWR_C8_LOCRE1(base, mode);
    MCG_BWR_C8_CME1(base, 1U);
}
#endif

#if FSL_FEATURE_MCG_HAS_OSC1
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_SetOsc1Mode
 * Description   : Set the OSC1 work mode.
 * This function set OSC1 work mode, include frequency range select, high gain
 * oscillator select and external reference select.
 *
 *END**************************************************************************/
void CLOCK_HAL_SetOsc1Mode(MCG_Type * base,
                           osc_range_t range,
                           osc_gain_t hgo,
                           osc_src_t erefs)
{
    MCG_WR_C10(base, (MCG_RD_C10(base)
                  & ~(MCG_C10_RANGE1_MASK  |
                      MCG_C10_HGO1_MASK    |
                      MCG_C10_EREFS1_MASK))
                  |  (MCG_C10_RANGE1(range)|
                      MCG_C10_HGO1(hgo)    |
                      MCG_C10_EREFS1(erefs)));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_EnableOsc1Monitor
 * Description   : Enable the OSC1 external clock monitor.
 *
 *END**************************************************************************/
void CLOCK_HAL_EnableOsc1Monitor(MCG_Type * base, mcg_osc_monitor_mode_t mode)
{
    MCG_BWR_C10_LOCRE2(base, mode);
    MCG_BWR_C12_CME2(base, 1U);
}
#endif

#if FSL_FEATURE_MCG_HAS_EXTERNAL_PLL
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_EnableExtPllMonitor
 * Description   : Enable the External PLL clock monitor.
 *
 *END**************************************************************************/
void CLOCK_HAL_EnableExtPllMonitor(MCG_Type * base, mcg_osc_monitor_mode_t mode)
{
    MCG_BWR_C9_PLL_LOCRE(base, mode);
    MCG_BWR_C9_PLL_CME(base, 1U);
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_TrimInternalRefClk
 * Description   : Trim internal reference clock to a desire frequency.
 * The external frequency is the BUS clock frequency and must be in the range
 * of 8MHz to 16MHz.
 *
 *END**************************************************************************/
mcg_atm_error_t CLOCK_HAL_TrimInternalRefClk(MCG_Type* base,
                                             uint32_t  extFreq,
                                             uint32_t  desireFreq,
                                             uint32_t* actualFreq,
                                             mcg_atm_select_t atms)
{
    uint32_t multi;    /* extFreq / desireFreq */
    uint32_t actv;     /* Auto trim value. */

    if ((extFreq > kMcgConstant16000000) ||
        (extFreq < kMcgConstant8000000))
    {
        return kMcgAtmErrorBusClockRange;
    }

    /* Check desired frequency range. */
    if (kMcgAtmSel4m == atms)
    {
        if ((desireFreq < 3000000U) || (desireFreq > 5000000U))
        {
            return kMcgAtmErrorDesireFreqRange;
        }
    }
    else
    {
        if ((desireFreq < 31250U) || (desireFreq > 39063U))
        {
            return kMcgAtmErrorDesireFreqRange;
        }
    }

    /*
     * Make sure internal reference clock is not used to generate bus clock.
     * Just need to check C1[IREFS].
     */
    if (kMcgFllSrcInternal == MCG_BRD_C1_IREFS(base))
    {
        return kMcgAtmErrorIrcUsed;
    }

    multi  = extFreq / desireFreq;
    actv = multi * 21U;

    if (kMcgAtmSel4m == atms)
    {
        actv *= 128U;
    }

    /* Now begin to start trim. */
    MCG_WR_ATCVL(base, (actv & 0xFFU));
    MCG_WR_ATCVH(base, ((actv >> 8U) & 0xFFU));

    MCG_BWR_SC_ATMS(base, atms);

    MCG_BWR_SC_ATME(base, 1U);

    while (MCG_BRD_SC_ATME(base)) {}

    /* Error occurs? */
    if (CLOCK_HAL_IsAutoTrimMachineFailed(base))
    {
        return kMcgAtmErrorHardwareFail;
    }

    *actualFreq = extFreq / multi;

    if (kMcgAtmSel4m == atms)
    {
        g_fastInternalRefClkFreq = *actualFreq;
    }
    else
    {
        g_slowInternalRefClkFreq = *actualFreq;
    }

    return kMcgAtmErrorNone;
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

