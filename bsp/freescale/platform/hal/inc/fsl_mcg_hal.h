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

#if !defined(__FSL_MCG_HAL_H__)
#define __FSL_MCG_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_MCG_COUNT

/*! @addtogroup mcg_hal*/
/*! @{*/

/*! @file fsl_mcg_hal.h */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief MCG constant definitions*/
enum _mcg_constant
{
   kMcgConstant0         = (0u),
   kMcgConstant31250     = (31250u),
   kMcgConstant32768     = (32768u),
   kMcgConstant39063     = (39063u),
   kMcgConstant8000000   = (8000000u),
   kMcgConstant16000000  = (16000000u),
};

/*! @brief MCG internal reference clock source select */
typedef enum _mcg_fll_src
{
    kMcgFllSrcExternal,    /*!< External reference clock is selected */
    kMcgFllSrcInternal     /*!< The slow internal reference clock is selected */
} mcg_fll_src_t;

/*! @brief MCG OSC frequency range select */
typedef enum _osc_range
{
    kOscRangeLow,         /*!< Low frequency range selected for the crystal OSC */
    kOscRangeHigh,        /*!< High frequency range selected for the crystal OSC */
    kOscRangeVeryHigh,    /*!< Very High frequency range selected for the crystal OSC */
    kOscRangeVeryHigh1    /*!< Very High frequency range selected for the crystal OSC */
} osc_range_t;

/*! @brief MCG high gain oscillator select */
typedef enum _osc_gain
{
    kOscGainLow,          /*!< Configure crystal oscillator for low-power operation */
    kOscGainHigh          /*!< Configure crystal oscillator for high-gain operation */
} osc_gain_t;

/*! @brief MCG external reference clock select */
typedef enum _osc_src
{
    kOscSrcExt,    /*!< External reference clock requested */
    kOscSrcOsc     /*!< Oscillator requested */
} osc_src_t;

/*! @brief MCG internal reference clock select */
typedef enum _mcg_irc_mode
{
    kMcgIrcSlow,        /*!< Slow internal reference clock selected */
    kMcgIrcFast         /*!< Fast internal reference clock selected */
} mcg_irc_mode_t;

/*! @brief MCG DCO Maximum Frequency with 32.768 kHz Reference */
typedef enum _mcg_dmx32_select
{
    kMcgDmx32Default, /*!< DCO has a default range of 25% */
    kMcgDmx32Fine     /*!< DCO is fine-tuned for maximum frequency with 32.768 kHz reference */
} mcg_dmx32_select_t;

/*! @brief MCG DCO range select */
typedef enum _mcg_dco_range_select
{
    kMcgDcoRangeSelLow,          /*!< Low frequency range */
    kMcgDcoRangeSelMid,          /*!< Mid frequency range*/
    kMcgDcoRangeSelMidHigh,      /*!< Mid-High frequency range */
    kMcgDcoRangeSelHigh          /*!< High frequency range */
} mcg_dco_range_select_t;

/*! @brief MCG PLL external reference clock select */
typedef enum _mcg_pll_ref_mode
{
    kMcgPllRefOsc0,    /*!< Selects OSC0 clock source as its external reference clock */
    kMcgPllRefOsc1     /*!< Selects OSC1 clock source as its external reference clock */
} mcg_pll_ref_mode_t;

/*! @brief MCGOUT clock source. */
typedef enum _mcg_clkout_src
{
    kMcgClkOutSrcOut,                   /*!< Output of the FLL is selected (reset default) */
    kMcgClkOutSrcInternal,              /*!< Internal reference clock is selected */
    kMcgClkOutSrcExternal,              /*!< External reference clock is selected */
} mcg_clkout_src_t;

#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
/*! @brief MCG PLL reference clock source select MCG_C7[PLL32KREFSEL]*/
typedef enum _mcg_pll_ref_clock_source
{
    kMcgPllRefClkSrcRtc       = 0U,  /* External RTC OSC reference clock is selected  */
    kMcgPllRefClkSrcSlowIrc   = 1U,  /* The slow internal reference clock is selected */
    kMcgPllRefClkSrcFllExtRef = 2U   /* The FLL FRDIV output clock is selected        */
} mcg_pll_ref_clock_source_t;
#endif

/*! @brief MCG clock mode status */
typedef enum _mcg_clkout_stat
{
    kMcgClkOutStatFll,                   /*!< Output of the FLL is selected (reset default) */
    kMcgClkOutStatInternal,              /*!< Internal reference clock is selected */
    kMcgClkOutStatExternal,              /*!< External reference clock is selected */
    kMcgClkOutStatPll                    /*!< Output of the PLL is selected */
} mcg_clkout_stat_t;

/*! @brief MCG Automatic Trim Machine Select */
typedef enum _mcg_atm_select
{
    kMcgAtmSel32k,   /*!< 32 kHz Internal Reference Clock selected */
    kMcgAtmSel4m     /*!< 4 MHz Internal Reference Clock selected */
} mcg_atm_select_t;

/*! @brief MCG OSC Clock Select */
typedef enum _mcg_oscsel_select
{
    kMcgOscselOsc,                  /*!< Selects System Oscillator (OSCCLK) */
    kMcgOscselRtc,                  /*!< Selects 32 kHz RTC Oscillator */
#if FSL_FEATURE_MCG_HAS_IRC_48M
    kMcgOscselIrc                   /*!< Selects 48 MHz IRC Oscillator */
#endif
} mcg_oscsel_select_t;

/*! @brief MCG OSC monitor mode */
typedef enum _mcg_osc_monitor_mode
{
    kMcgOscMonitorInt,     /*!< Generate interrupt when clock lost. */
    kMcgOscMonitorReset    /*!< Generate reset when clock lost.     */
} mcg_osc_monitor_mode_t;

/*! @brief MCG PLLCS select */
typedef enum _mcg_pll_clk_select
{
    kMcgPllClkSelPll0,            /*!< PLL0 output clock is selected */
#if FSL_FEATURE_MCG_HAS_EXTERNAL_PLL    
    kMcgPllClkSelExtPll,          /* External PLL clock is selected */
#else
    kMcgPllClkSelPll1,            /* PLL1 output clock is selected */
#endif
} mcg_pll_clk_select_t;

/*! @brief MCG auto trim machine error code. */
typedef enum _mcg_atm_error
{
    kMcgAtmErrorNone,               /*!< No error. */
    kMcgAtmErrorBusClockRange,      /*!< Bus clock frequency is not in 8MHz to 16 MHz. */
    kMcgAtmErrorDesireFreqRange,    /*!< Desired frequency is out of range. */
    kMcgAtmErrorIrcUsed,            /*!< IRC clock is used to generate system clock.  */
    kMcgAtmErrorTrimValueInvalid,   /*!< The auto trim compare value ACT is invalid. */
    kMcgAtmErrorHardwareFail        /*!< ATC[ATMF] fail flag asserts. */
} mcg_atm_error_t;

/*! @brief MCG status. */
typedef enum _mcg_status
{
    kStatus_MCG_Success = 0U, /*!< Success.          */
    kStatus_MCG_Fail    = 1U, /*!< Execution failed. */
} mcg_status_t;

extern uint32_t g_xtal0ClkFreq;           /* EXTAL0 clock */
#if FSL_FEATURE_MCG_HAS_OSC1
extern uint32_t g_xtal1ClkFreq;           /* EXTAL1 clock */
#endif
#if FSL_FEATURE_MCG_HAS_EXTERNAL_PLL
extern uint32_t g_extPllClkFreq;          /* External PLL clock */
#endif
extern uint32_t g_xtalRtcClkFreq;         /* EXTAL RTC clock */

extern uint32_t g_fastInternalRefClkFreq;  /* Fast IRC clock */
extern uint32_t g_slowInternalRefClkFreq;  /* Slow IRC clock */

#if FSL_FEATURE_MCG_HAS_IRC_48M
#define CPU_INTERNAL_IRC_48M 48000000U
#endif

#if defined(MCG_BWR_C6_CME)
#define MCG_BWR_C6_CME0 MCG_BWR_C6_CME
#endif

#if defined(MCG_BRD_C6_CME)
#define MCG_BRD_C6_CME0 MCG_BRD_C6_CME
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name MCG out clock access API*/
/*@{*/

/*!
 * @brief Tests the external clock frequency.
 *
 * This function tests the external clock frequency, including OSC, RTC and IRC48M.
 * If the OSC is not initialized, this function returns 0.
 *
 * @param base  Base address for current MCG instance.
 * @param oscselVal    External OSC selection.
 * @return MCG external reference clock frequency.
 */
uint32_t CLOCK_HAL_TestOscFreq(MCG_Type * base, mcg_oscsel_select_t oscselVal);

/*!
 * @brief Tests the FLL external reference frequency based on the input parameters.
 *
 * This function calculates the MCG FLL external reference clock value in
 * frequency(Hertz) based on the input parameters.
 *
 * @param base  Base address for current MCG instance.
 * @param extFreq   External OSC frequency.
 * @param frdivVal  FLL external reference divider value (FRDIV).
 * @param range0    OSC0 frequency range selection.
 * @param oscsel    External OSC selection.
 * @return MCG FLL external reference clock frequency.
 */
uint32_t CLOCK_HAL_TestFllExternalRefFreq(MCG_Type * base,
                                          uint32_t extFreq,
                                          uint8_t  frdivVal,
                                          osc_range_t range0,
                                          mcg_oscsel_select_t oscsel);
/*!
 * @brief Gets the current MCG FLL clock.
 *
 * This function returns the FLL reference clock frequency based on the
 * current MCG configurations and settings. FLL should be properly configured
 * in order to get the valid value.
 *
 * @param base  Base address for current MCG instance.
 * @return Frequency value in Hertz of FLL reference clock.
 */
uint32_t CLOCK_HAL_GetFllRefClk(MCG_Type * base);

/*!
 * @brief Calculates the FLL frequency based on the input parameters.
 *
 * This function calculates the FLL frequency based on input parameters.
 *
 * @param base  Base address for current MCG instance.
 * @param fllRef    FLL reference clock frequency.
 * @param dmx32     DCO max 32K setting.
 * @param drs       DCO range seletion.
 * @return Frequency value in Hertz of the mcgfllclk.
 */
uint32_t CLOCK_HAL_TestFllFreq(MCG_Type * base,
                               uint32_t fllRef,
                               mcg_dmx32_select_t dmx32,
                               mcg_dco_range_select_t drs);

/*!
 * @brief Gets the current MCG FLL clock.
 *
 * This function  returns the mcgfllclk value in frequency(Hertz) based on the
 * current MCG configurations and settings. FLL should be properly configured
 * get the valid value.
 *
 * @param base  Base address for current MCG instance.
 * @return Frequency value in Hertz of the mcgpllclk.
 */
uint32_t CLOCK_HAL_GetFllClk(MCG_Type * base);

#if FSL_FEATURE_MCG_HAS_PLL
#if (FSL_FEATURE_MCG_HAS_PLL_PRDIV ) && ( FSL_FEATURE_MCG_HAS_PLL_VDIV )
/*!
 * @brief Calculates the PLL PRDIV and VDIV.
 *
 * This function calculates the proper PRDIV and VDIV to generate desired PLL
 * output frequency with input reference clock frequency. It returns the closest
 * frequency PLL could generate, the corresponding PRDIV/VDIV are returned from
 * parameters. If desire frequency is not valid, this function returns 0.
 *
 * @param refFreq PLL reference frequency.
 * @param desireFreq Desired PLL output frequency.
 * @param prdiv   PRDIV value to generate desired PLL frequency.
 * @param vdiv    VDIV value to generate desired PLL frequency.
 * @return Closest frequency PLL could generate.
 */
uint32_t CLOCK_HAL_CalculatePllDiv(uint32_t refFreq,
                                   uint32_t desireFreq,
                                   uint8_t *prdiv,
                                   uint8_t *vdiv);
#endif

/*!
 * @brief Gets the current MCG PLL/PLL0 clock.
 *
 * This function  returns the mcgpllclk/mcgpll0 value in frequency(Hertz) based
 * on the current MCG configurations and settings. PLL/PLL0 should be properly 
 * configured in order to get the valid value.
 *
 * @param base  Base address for current MCG instance.
 * @return Frequency value in Hertz of the mcgpllclk or the mcgpll0clk.
 */
uint32_t CLOCK_HAL_GetPll0Clk(MCG_Type * base);
#endif

#if FSL_FEATURE_MCG_HAS_PLL1
/*!
 * @brief Gets the current MCG PLL1 clock.
 *
 * This function  returns the mcgpll1clk value in frequency (Hertz) based
 * on the current MCG configurations and settings. PLL1 should be properly configured
 * in order to get the valid value.
 *
 * @param base  Base address for current MCG instance.
 * @return Frequency value in Hertz of mcgpll1clk.
 */
uint32_t CLOCK_HAL_GetPll1Clk(MCG_Type * base);
#endif

#if FSL_FEATURE_MCG_HAS_EXTERNAL_PLL
/*!
 * @brief Gets the current external PLL clock.
 *
 * This function  returns the extpllclk value in frequency (Hertz). The external PLL
 * is configured outside of the MCG module.
 *
 * @param base  Base address for current MCG instance.
 * @return value Frequency value in Hertz of mcgpll1clk.
 */
uint32_t CLOCK_HAL_GetExtPllClk(MCG_Type * base);
#endif

/*!
 * @brief Gets the current MCG internal reference clock(MCGIRCLK).
 *
 * This function  returns the MCGIRCLK value in frequency (Hertz) based
 * on the current MCG configurations and settings. It does not check if the
 * MCGIRCLK is enabled or not, just calculate and return the value.
 *
 * @param base  Base address for current MCG instance.
 * @return Frequency value in Hertz of the MCGIRCLK.
 */
uint32_t CLOCK_HAL_GetInternalRefClk(MCG_Type * base);

/*!
 * @brief Gets the current MCG fixed frequency clock(MCGFFCLK).
 *
 * This function get the MCGFFCLK, it is only valid when its frequency is not
 * more than MCGOUTCLK/8. If MCGFFCLK is invalid, this function returns 0.
 *
 * @param base  Base address for current MCG instance.
 * @return Frequency value in Hertz of MCGFFCLK.
 */
uint32_t CLOCK_HAL_GetFixedFreqClk(MCG_Type * base);

/*!
 * @brief Gets the current MCG out clock.
 *
 * This function  returns the mcgoutclk value in frequency (Hertz) based on the
 * current MCG configurations and settings. The configuration should be
 * properly done in order to get the valid value.
 *
 * @param base  Base address for current MCG instance.
 * @return Frequency value in Hertz of mcgoutclk.
 */
uint32_t CLOCK_HAL_GetOutClk(MCG_Type * base);

/*@}*/

/*! @name MCG control register access API*/
/*@{*/

/*!
 * @brief Sets the Clock Source Select
 *
 * This function  selects the clock source for the MCGOUTCLK.
 *
 * @param base  Base address for current MCG instance.
 * @param select    Clock source selection
 *                  - 00: Output of FLL or PLLCS is selected(depends on PLLS control bit)
 *                  - 01: Internal reference clock is selected.
 *                  - 10: External reference clock is selected.
 *                  - 11: Reserved.
 */
static inline void CLOCK_HAL_SetClkOutSrc(MCG_Type * base, mcg_clkout_src_t select)
{
    MCG_BWR_C1_CLKS(base, select);
}

/*!
 * @brief Sets the CLKS, FRDIV, IREFS at the same time.
 *
 * This function set the MCG_C1[CLKS], MCG_C1[FRDIV] and MCG_C1[IREFS] at the
 * same time, in order keep the integrity of the clock switching.
 *
 * @param base  Base address for current MCG instance.
 * @param clks  MCG_C1[CLKS].
 * @param frdiv MCG_C1[FRDIV].
 * @param irefs MCG_C1[IREFS].
 */
static inline void CLOCK_HAL_SetClksFrdivIrefs(MCG_Type * base,
                                               mcg_clkout_src_t clks,
                                               uint8_t frdiv,
                                               mcg_fll_src_t irefs)
{
    MCG_WR_C1(base, (MCG_RD_C1(base)
                 & ~(MCG_C1_CLKS_MASK  |
                     MCG_C1_FRDIV_MASK |
                     MCG_C1_IREFS_MASK))
                 |  (MCG_C1_CLKS(clks)    |
                     MCG_C1_FRDIV(frdiv)  |
                     MCG_C1_IREFS(irefs)));
}

/*!
 * @brief Gets the Clock Mode Status.
 *
 * This function  gets the Clock Mode Status. These bits indicate the current clock mode.
 * The CLKST bits do not update immediately after a write to the CLKS bits due to
 * internal synchronization between clock domains.
 *
 * @param base  Base address for current MCG instance.
 * @return Clock Mode Status
 *                 - 00: Output of the FLL is selected (reset default).
 *                 - 01: Internal reference clock is selected.
 *                 - 10: External reference clock is selected.
 *                 - 11: Output of the PLL is selected.
 */
static inline mcg_clkout_stat_t CLOCK_HAL_GetClkOutStat(MCG_Type * base)
{
    return (mcg_clkout_stat_t)MCG_BRD_S_CLKST(base);
}

/*!
 * @brief Sets the Low Power Select.
 *
 * This function  controls whether the FLL (or PLL) is disabled in the BLPI and the
 * BLPE modes. In the FBE or the PBE modes, setting this bit to 1  transitions the MCG
 * into the BLPE mode. In the FBI mode, setting this bit to 1  transitions the MCG into
 * the BLPI mode. In any other MCG mode, the LP bit has no effect.
 *
 * @param base  Base address for current MCG instance.
 * @param enable   Enable low power or not:
 *                 - true: FLL (or PLL) is not disabled in bypass modes
 *                 - false: FLL (or PLL) is disabled in bypass modes (lower power)
 */
static inline void CLOCK_HAL_SetLowPowerModeCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_C2_LP(base, enable);
}

#if FSL_FEATURE_MCG_USE_OSCSEL
/*!
 * @brief Sets the MCG OSC Clock Select Setting.
 *
 * This function selects the MCG external reference clock.
 *
 * @param base  Base address for current MCG instance.
 * @param setting  MCG OSC Clock Select Setting
 *                  - 0: Selects System Oscillator (OSCCLK).
 *                  - 1: Selects 32 kHz RTC Oscillator.
 */
static inline void CLOCK_HAL_SetOscselMode(MCG_Type * base, mcg_oscsel_select_t setting)
{
    MCG_WR_C7_OSCSEL(base, setting);
}
#endif

/*!
 * @brief Prepare the OSC external clock.
 *
 * This function set the OSCSEL, if external oscillator is used, it wait until
 * it is stable. This function could be used to prepare the external clock source
 * before switch to use.
 *
 * @param base    Base address for current MCG instance.
 * @param setting MCG OSC Clock Select Setting
 */
void CLOCK_HAL_PrepareOsc(MCG_Type * base, mcg_oscsel_select_t setting);

/*@}*/

/*! @name MCG FLL API */
/*@{*/

/*!
 * @brief Gets the FLL source status.
 *
 * This function  gets the Internal Reference Status. This bit indicates the current
 * source for the FLL reference clock. The IREFST bit does not update immediately
 * after a write to the IREFS bit due to internal synchronization between the clock
 * domains.
 *
 * @param base  Base address for current MCG instance.
 * @return Internal Reference Status
 *                 - 0: Source of FLL reference clock is the external reference clock.
 *                 - 1: Source of FLL reference clock is the internal reference clock.
 */
static inline mcg_fll_src_t CLOCK_HAL_GetFllSrc(MCG_Type * base)
{
    return (mcg_fll_src_t)MCG_BRD_S_IREFST(base);
}

/*!
 * @brief Sets the FLL Filter Preserve Enable Setting.
 *
 * This function  sets the FLL Filter Preserve Enable. This bit  prevents the
 * FLL filter values from resetting allowing the FLL output frequency to remain the
 * same during the clock mode changes where the FLL/DCO output is still valid. 
 * (Note: This requires that the FLL reference frequency  remain the same as 
 *  the value prior to the new clock mode switch. Otherwise, the FLL filter and the frequency 
 * values  change.)
 *
 * @param base  Base address for current MCG instance.
 * @param enable  FLL Filter Preserve Enable Setting
 *                 - true: FLL filter and FLL frequency retain their previous values 
 *                       during new clock mode change
 *                 - false: FLL filter and FLL frequency will reset on changes to correct 
 *                       clock mode
 */
static inline void CLOCK_HAL_SetFllFilterPreserveCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_SC_FLTPRSRV(base, enable);
}

/*!
 * @brief Calculates the proper FRDIV setting.
 *
 * This function calculates the proper FRDIV setting according to the FLL
 * reference clock. FLL reference clock frequency after FRDIV must be in the
 * range of 31.25 kHz to 39.0625 kHz.
 *
 * @param range0 RANGE0 setting.
 * @param oscsel OSCSEL setting.
 * @param inputFreq The reference clock frequency before FRDIV.
 * @param frdiv FRDIV result.
 * @return Method return status.
 * @retval kStatus_MCG_Success Proper FRDIV is got.
 * @retval kStatus_MCG_Fail Could not get proper FRDIV.
 */
mcg_status_t CLOCK_HAL_GetAvailableFrdiv(osc_range_t range0,
                                    mcg_oscsel_select_t oscsel,
                                    uint32_t inputFreq,
                                    uint8_t  *frdiv);

/*@}*/

/*! @name MCG internal reference clock APIs */
/*@{*/

/*!
 * @brief Sets the internal reference clock enable or not.
 *
 * This function  enables/disables the internal reference clock to use as the MCGIRCLK.
 *
 * @param base  Base address for current MCG instance.
 * @param enable Enable or disable internal reference clock.
 *                 - true: MCGIRCLK active
 *                 - false: MCGIRCLK inactive
 */
static inline void CLOCK_HAL_SetInternalRefClkEnableCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_C1_IRCLKEN(base, enable);
}

/*!
 * @brief Sets the internal reference clock enable or nor in stop mode.
 *
 * This function  controls whether or not the internal reference clock remains 
 * enabled when the MCG enters Stop mode.
 *
 * @param base  Base address for current MCG instance.
 * @param enable Enable or disable the internal reference clock stop setting.
 *                 - true: Internal reference clock is enabled in Stop mode if IRCLKEN is set
 *                         or if MCG is in FEI, FBI, or BLPI modes before entering Stop mode.
 *                 - false: Internal reference clock is disabled in Stop mode
 */
static inline void CLOCK_HAL_SetInternalRefClkEnableInStopCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_C1_IREFSTEN(base, enable);
}

/*!
 * @brief Sets the Internal Reference Clock Select.
 *
 * This function  selects between the fast or slow internal reference clock source.
 *
 * @param base  Base address for current MCG instance.
 * @param mode  Internal reference clock source.
 *                 - 0: Slow internal reference clock selected.
 *                 - 1: Fast internal reference clock selected.
 */
static inline void CLOCK_HAL_SetInternalRefClkMode(MCG_Type * base,
                                                   mcg_irc_mode_t mode)
{
    MCG_BWR_C2_IRCS(base, mode);
}

/*!
 * @brief Gets the Internal Reference Clock Status.
 *
 * This function  gets the Internal Reference Clock Status. The IRCST bit indicates the
 * current source for the internal reference clock select clock (IRCSCLK). The IRCST bit
 * does not update immediately after a write to the IRCS bit due to the internal 
 * synchronization between clock domains. The IRCST bit is only  updated if the 
 * internal reference clock is enabled, either by the MCG being in a mode that uses the
 * IRC or by setting the C1[IRCLKEN] bit.
 *
 * @param base  Base address for current MCG instance.
 * @return Internal Reference Clock Status
 *                 - 0: Source of internal reference clock is the slow clock (32 kHz IRC).
 *                 - 1: Source of internal reference clock is the fast clock (2 MHz IRC).
 */
static inline mcg_irc_mode_t CLOCK_HAL_GetInternalRefClkMode(MCG_Type * base)
{
    return (mcg_irc_mode_t)MCG_BRD_S_IRCST(base);
}

/*!
 * @brief Updates the Fast Clock Internal Reference Divider Setting.
 *
 * This function sets FCRDIV to a new value. FCRDIV cannot be
 * changed when fast internal reference is enabled. 
 * If it is enabled, disable it , then set FCRDIV, and finally re enable
 * it.
 *
 * @param base  Base address for current MCG instance.
 * @param fcrdiv  Fast Clock Internal Reference Divider Setting
 */
void CLOCK_HAL_UpdateFastClkInternalRefDiv(MCG_Type * base, uint8_t fcrdiv);

/*!
 * @brief Updates the Internal Reference clock (MCGIRCLK)
 *
 * This function setups the MCGIRCLK base on parameters. It selects the IRC
 * source, if fast IRC is used, this function also sets the fast IRC divider.
 * This function also sets whether enable MCGIRCLK in stop mode.
 *
 * @param base  Base address for current MCG instance.
 * @param ircs  MCGIRCLK clock source, choose fast or slow.
 * @param fcrdiv  Fast Clock Internal Reference Divider Setting.
 * @param enableInStop MCGIRCLK enable in stop mode or not.
 */
void CLOCK_HAL_UpdateInternalRefClk(MCG_Type      *base,
                                    mcg_irc_mode_t ircs,
                                    uint8_t        fcrdiv,
                                    bool           enableInStop);

/*@}*/

/*! @name MCG PLL APIs */
/*@{*/

#if FSL_FEATURE_MCG_HAS_PLL
/*!
 * @brief Sets the PLL Clock Enable Setting.
 *
 * This function  enables/disables the PLL0 independent of the PLLS and enables the PLL0
 * clock to use as the MCGPLL0CLK and the MCGPLL0CLK2X. (PRDIV0 needs to be programmed to
 * the correct divider to generate a PLL1 reference clock in a valid reference range
 * prior to setting the PLLCLKEN0 bit). Setting PLLCLKEN0  enables the external 
 * oscillator selected by REFSEL if not already enabled. Whenever the PLL0 is being
 * enabled with the PLLCLKEN0 bit, and the external oscillator is being used
 * as the reference clock, the OSCINIT 0 bit should be checked to make sure it is set.
 *
 * @param base  Base address for current MCG instance.
 * @param enable  PLL Clock Enable Setting
 *                 - true: MCGPLL0CLK and MCGPLL0CLK2X are active
 *                 - false: MCGPLL0CLK and MCGPLL0CLK2X are inactive
 */
static inline void CLOCK_HAL_SetPll0EnableCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_C5_PLLCLKEN0(base, enable);
}

/*!
 * @brief Sets the PLL0 enable or not in STOP mode.
 *
 * This function  enables/disables the PLL0 Clock during a Normal Stop (In Low
 * Power Stop mode, the PLL0 clock gets disabled even if PLLSTEN0=1). In all other
 * power modes, the PLLSTEN0 bit has no affect and does not enable the PLL0 Clock 
 * to run if it is written to 1.
 *
 * @param base  Base address for current MCG instance.
 * @param enable   PLL0 Stop Enable Setting
 *                  - true: MCGPLL0CLK and MCGPLL0CLK2X are enabled if system is in
 *                       Normal Stop mode.
 *                  - false: MCGPLL0CLK and MCGPLL0CLK2X are disabled in any of the 
 *                       Stop modes.
 */
static inline void CLOCK_HAL_SetPll0EnableInStopCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_C5_PLLSTEN0(base, enable);
}

/*!
 * @brief Gets the Loss of the Lock Status.
 *
 * This function  gets the Loss of Lock Status. This bit is a sticky bit indicating
 * the lock status for the PLL. LOLS 0 is set if after acquiring lock, the PLL 
 * output frequency has fallen outside the lock exit frequency tolerance.
 *
 * @param base  Base address for current MCG instance.
 * @return True if PLL0 has lost lock since LOLS 0 was last cleared.
 */
static inline bool CLOCK_HAL_IsPll0LostLock(MCG_Type * base)
{
    return (bool)MCG_BRD_S_LOLS0(base);
}

/*!
 * @brief Clears the PLL0 lost lock status.
 *
 * This function clears the Loss of Lock Status.
 *
 * @param base  Base address for current MCG instance.
 */
static inline void CLOCK_HAL_ClearPll0LostLock(MCG_Type * base)
{
    MCG_BWR_S_LOLS0(base, 1U);
}

/*!
 * @brief Sets the loss of lock interrupt enable setting.
 *
 * This function determines whether an interrupt request is made following a loss
 * of lock indication. This bit only has an effect when LOLS 0 is set.
 *
 * @param base  Base address for current MCG instance.
 * @param enable  Loss of Lock Interrupt Enable Setting
 *                 - true: Generate an interrupt request on loss of lock.
 *                 - false: No interrupt request is generated on loss of lock.
 */
static inline void CLOCK_HAL_SetPll0LostLockIntCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_C6_LOLIE0(base, enable);
}

#if FSL_FEATURE_MCG_HAS_LOLRE
/*!
 * @brief Sets the PLL Loss of Lock Reset Enable Setting.
 *
 * This function  determines whether an interrupt or a reset request is made
 * following a PLL loss of lock.
 *
 * @param base  Base address for current MCG instance.
 * @param enable   PLL Loss of Lock Reset Enable Setting
 *                  - true: Generate a reset request on a PLL loss of lock indication.
 *                  - false: Interrupt request is generated on a PLL loss of lock
 *                       indication. The PLL loss of lock interrupt enable bit
 *                       must also be set to generate the interrupt request.
 */
static inline void CLOCK_HAL_SetPllLostLockResetCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_C8_LOLRE(base, enable);
}
#endif /* FSL_FEATURE_MCG_HAS_LOLRE */

/*!
 * @brief Gets the Lock Status.
 *
 * This function  gets the Lock Status. This bit indicates whether the PLL0 has 
 * acquired the lock. Lock detection is disabled when not operating in either the PBE or the
 * PEE mode unless PLLCLKEN0=1 and the MCG is not configured in the BLPI or the BLPE mode.
 * While the PLL0 clock is locking to the desired frequency, MCGPLL0CLK and 
 * MCGPLL0CLK2X are  gated off until the LOCK0 bit gets asserted. If the lock
 * status bit is set, changing the value of the PRDIV0[2:0] bits in the C5 register
 * or the VDIV0[4:0] bits in the C6 register causes the lock status bit to clear 
 * and stay cleared until the PLL0 has reacquired the lock. The loss of the PLL0 reference 
 * clock  also causes the LOCK0 bit to clear until the PLL0 has an entry into the LLS, 
 * VLPS, or a regular Stop with PLLSTEN0=0 also causes the lock status bit to clear
 * and stay cleared until the stop mode is exited and the PLL0 has reacquired the lock.
 * Any time the PLL0 is enabled and the LOCK0 bit is cleared, the MCGPLL0CLK and
 * MCGPLL0CLK2X are  gated off until the LOCK0 bit is reasserted.
 *
 * @param base  Base address for current MCG instance.
 * @return True if PLL0 is locked.
 */
static inline bool CLOCK_HAL_IsPll0Locked(MCG_Type * base)
{
    return (bool)MCG_BRD_S_LOCK0(base);
}

/*!
 * @brief Selects the PLL output or FLL output as the source of the MCGOUT.
 *
 * This function selects the PLL output or FLL output as the source of the
 * MCGOUT. When this is  set, use the CLOCK_HAL_IsPllSelected to check the status
 * update.
 *
 * @param base  Base address for current MCG instance.
 * @param select True to select PLL, false to select FLL.
 */
static inline void CLOCK_HAL_SetPllSelectCmd(MCG_Type * base, bool select)
{
    MCG_BWR_C6_PLLS(base, select);
}

/*!
 * @brief Gets the PLL Select Status.
 *
 * This function  gets the PLL Select Status. This bit indicates the clock source
 * selected by PLLS . The PLLST bit does not update immediately after a write to
 * the PLLS bit due to the internal synchronization between the clock domains.
 *
 * @param base  Base address for current MCG instance.
 * @return True if PLL output is selected to MCGOUT, false if FLL output is selected.
 */
static inline bool CLOCK_HAL_IsPllSelected(MCG_Type * base)
{
    return (bool)MCG_BRD_S_PLLST(base);
}

#if (FSL_FEATURE_MCG_HAS_PLL_PRDIV ) && ( FSL_FEATURE_MCG_HAS_PLL_VDIV )
/*!
 * @brief Enables the PLL0 not in PLL mode.
 *
 * This function enables the PLL0 when MCG is not in the PLL mode, for example,
 * when the MCG is in FEI mode. This function only sets up the PLL dividers and makes
 * sure the PLL is locked. Ensure the PLL reference clock is enabled
 * before calling this function. The function CLOCK_HAL_CalculatePllDiv can help to
 * get the proper PLL divider values.
 *
 * @param base  Base address for current MCG instance.
 * @param prdiv PLL reference divider.
 * @param vdiv  PLL VCO divider.
 * @param enableInStop  PLL enable or not in STOP mode.
 */
void CLOCK_HAL_EnablePll0InFllMode(MCG_Type * base,
                                   uint8_t prdiv,
                                   uint8_t vdiv,
                                   bool enableInStop);
#else
/*!
 * @brief Enables the PLL0 not in the PLL mode.
 *
 * This function enables the PLL0 when the MCG is not in the PLL modes. For example,
 * when the MCG is in the FEI mode. This function only sets up the PLL dividers and makes
 * sure PLL is locked. Ensure that the PLL reference clock is enabled
 * before calling this function.
 *
 * @param base  Base address for current MCG instance.
 * @param enableInStop  PLL enable or not in STOP mode.
 */
void CLOCK_HAL_EnablePll0InFllMode(MCG_Type * base,
                                   bool enableInStop);
#endif
#endif

#if FSL_FEATURE_MCG_HAS_PLL1
/*!
 * @brief Sets the PLL1 Clock Enable Setting.
 *
 * This function  enables/disables the PLL1 independent of PLLS and enables the
 * PLL clocks for use as MCGPLL1CLK, MCGPLL1CLK2X, and MCGDDRCLK2X. (PRDIV1 needs 
 * to be programmed to the correct divider to generate a PLL1 reference clock in a
 * valid reference range prior to setting the PLLCLKEN1 bit.) Setting PLLCLKEN1 
 *  enables the PLL1 selected external oscillator if not already enabled. 
 * Whenever the PLL1 is  enabled with the PLLCLKEN1 bit, and the 
 * external oscillator is  used as the reference clock, the OSCINIT1 bit should
 * be checked to make sure it is set.
 *
 * @param base  Base address for current MCG instance.
 * @param enable   PLL1 Clock Enable Setting
 *                  - true: MCGPLL1CLK, MCGPLL1CLK2X, and MCGDDRCLK2X are active unless
 *                       MCG is in a bypass mode with LP=1 (BLPI or BLPE).
 *                  - false: MCGPLL1CLK, MCGPLL1CLK2X, and MCGDDRCLK2X are inactive.
 */
static inline void CLOCK_HAL_SetPll1EnableCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_C11_PLLCLKEN1(base, enable);
}

/*!
 * @brief Sets the PLL1 enable or not in STOP mode.
 *
 * This function  enables/disables the PLL1 Clock during the Normal Stop (In Low
 * Power Stop modes, the PLL1 clock gets disabled even if PLLSTEN1=1. In all other 
 * power modes, PLLSTEN1 bit has no affect and does not enable the PLL1 Clock to
 * run if it is written to 1.
 *
 * @param base  Base address for current MCG instance.
 * @param enable   PLL1 Stop Enable Setting
 *                  - true: PLL1 and its clocks (MCGPLL1CLK, MCGPLL1CLK2X, and 
 *                       MCGDDRCLK2X) are enabled if system is in Normal Stop mode.
 *                  - false: PLL1 clocks (MCGPLL1CLK, MCGPLL1CLK2X, and MCGDDRCLK2X) 
 *                       are disabled in any of the Stop modes.
 */
static inline void CLOCK_HAL_SetPll1EnableInStopCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_C11_PLLSTEN1(base, enable);
}

/*!
 * @brief Sets the PLL1 Loss of Lock Interrupt Enable Setting.
 *
 * This function  determines whether an interrupt request is made following a 
 * loss of lock indication for PLL1. This bit only has an affect when LOLS1 is set.
 *
 * @param base  Base address for current MCG instance.
 * @param enable   PLL1 Loss of Lock Interrupt Enable Setting
 *                  - true: Generate an interrupt request on loss of lock on PLL1.
 *                  - false: No interrupt request is generated on loss of lock on PLL1.
 */
static inline void CLOCK_HAL_SetPll1LostLockIntCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_C12_LOLIE1(base, enable);
}

/*!
 * @brief Gets the Loss of the Lock2 Status.
 *
 * This function  gets the Loss of the Lock2 Status. This bit  indicates
 * the lock status for the PLL1. LOLS1 is set if after acquiring lock, the PLL1 
 * output frequency has fallen outside the lock exit frequency tolerance, D unl. 
 * LOLIE1 determines whether an interrupt request is made when LOLS1 is set. This
 * bit is cleared by reset or by writing a logic 1 to it when set. Writing a logic 0
 * to this bit has no effect.
 *
 * @param base  Base address for current MCG instance.
 * @return True if PLL1 has lost lock since LOLS 1 was last cleared.
 */
static inline bool CLOCK_HAL_IsPll1LostLock(MCG_Type * base)
{
    return (bool)MCG_BRD_S2_LOLS1(base);
}

/*!
 * @brief Clears the PLL1 lost lock status.
 *
 * This function clears the Loss of Lock Status.
 *
 * @param base  Base address for current MCG instance.
 */
static inline void CLOCK_HAL_ClearPll1LostLock(MCG_Type * base)
{
    MCG_BWR_S2_LOLS1(base, 1U);
}

/*!
 * @brief Gets the Lock1 Status.
 *
 * This function  gets the Lock1 Status. This bit indicates whether PLL1 has 
 * acquired the lock. PLL1 Lock detection is disabled when not operating in either
 * PBE or PEE mode unless the PLLCLKEN1=1 and the the MCG is not configured in the BLPI or the
 * BLPE mode. While the PLL1 clock is locking to the desired frequency, MCGPLL1CLK,
 * MCGPLL1CLK2X, and MCGDDRCLK2X  are gated off until the LOCK1 bit gets 
 * asserted. If the lock status bit is set, changing the value of the PRDIV1[2:0] 
 * bits in the C8 register or the VDIV2[4:0] bits in the C9 register causes the
 * lock status bit to clear and stay cleared until the PLL1 has reacquired lock. 
 * Loss of PLL1 reference clock also causes the LOCK1 bit to clear until the PLL1 
 * has reacquired the lock. Entry into the LLS, VLPS, or a regular Stop with the PLLSTEN1=0 also
 * causes the lock status bit to clear and stay cleared until the Stop mode is exited
 * and the PLL1 has reacquired the lock. Any time the PLL1 is enabled and the LOCK1 bit
 * is cleared, the MCGPLL1CLK, MCGPLL1CLK2X, and MCGDDRCLK2X  are gated off 
 * until the LOCK1 bit is asserted again.
 *
 * @param base  Base address for current MCG instance.
 * @return True if PLL1 is locked.
 */
static inline bool CLOCK_HAL_IsPll1Locked(MCG_Type * base)
{
    return (bool)MCG_BRD_S2_LOCK1(base);
}
#endif /* FSL_FEATURE_MCG_HAS_PLL1 */

#if (FSL_FEATURE_MCG_HAS_PLL1 || FSL_FEATURE_MCG_HAS_EXTERNAL_PLL)
/*!
 * @brief Sets the PLL Clock Select Setting.
 *
 * This function  controls  whether the PLL0 or PLL1/ExtPLL output is selected as the
 * MCG source when CLKS are programmed in PLL Engaged External (PEE) mode 
 * (CLKS[1:0]=00 and IREFS=0 and PLLS=1).
 *
 * @param base  Base address for current MCG instance.
 * @param setting  PLL Clock Select Setting
 *                  - 0: PLL0 output clock is selected.
 *                  - 1: PLL1/ExtPLL output clock is selected.
 */
static inline void CLOCK_HAL_SetPllClkSelMode(MCG_Type * base, mcg_pll_clk_select_t setting)
{
    MCG_BWR_C11_PLLCS(base, setting);
}

/*!
 * @brief Gets the PLL Clock Select Status.
 *
 * This function  gets the PLL Clock Select Status. The PLLCST indicates the PLL
 * clock selected by PLLCS. The PLLCST bit is not updated immediately after a
 * write to the PLLCS bit due internal synchronization between clock domains.
 *
 * @param base  Base address for current MCG instance.
 * @return PLL Clock Select Status
 *                 - 0: Source of PLLCS is PLL0 clock.
 *                 - 1: Source of PLLCS is PLL1/ExtPLL clock.
 */
static inline mcg_pll_clk_select_t CLOCK_HAL_GetPllClkSelMode(MCG_Type * base)
{
    return (mcg_pll_clk_select_t)MCG_BRD_S2_PLLCST(base);
}
#endif /* FSL_FEATURE_MCG_HAS_PLL1 || FSL_FEATURE_MCG_HAS_EXTERNAL_PLL */

#if FSL_FEATURE_MCG_HAS_PLL1
/*!
 * @brief Enables the PLL1 not in PLL mode.
 *
 * This function enables the PLL1 when MCG is not in PLL modes, for example,
 * when MCG is in FEI mode. This function only sets up the PLL dividers and makes
 * sure PLL is locked. Ensure the PLL reference clock is enabled
 * before this function. The function CLOCK_HAL_CalculatePllDiv  helps to
 * get the proper PLL divider values.
 *
 * @param base  Base address for current MCG instance.
 * @param prdiv PLL reference divider.
 * @param vdiv  PLL VCO divider.
 * @param enbleInStop  PLL enable or not in STOP mode.
 */
void CLOCK_HAL_EnablePll1InFllMode(MCG_Type * base,
                                   uint8_t prdiv,
                                   uint8_t vdiv,
                                   bool enableInStop);

#if FSL_FEATURE_MCG_USE_PLLREFSEL
/*!
 * @brief Sets the PLL0 External Reference Select Setting.
 *
 * This function  selects the PLL0 external reference clock source.
 *
 * @param base Base address for current MCG instance.
 * @param setting  PLL0 External Reference Select Setting
 *                  - 0: Selects OSC0 clock source as its external reference clock
 *                  - 1: Selects OSC1 clock source as its external reference clock
 */
static inline void CLOCK_HAL_SetPll0RefMode(MCG_Type * base,
                                            mcg_pll_ref_mode_t setting)
{
    BW_MCG_C5_PLLREFSEL0(base, setting);
}

/*!
 * @brief Sets the PLL1 External Reference Select Setting.
 *
 * This function  selects the PLL1 external reference clock source.
 *
 * @param base Base address for current MCG instance.
 * @param setting  PLL1 External Reference Select Setting
 *                  - 0: Selects OSC0 clock source as its external reference clock.
 *                  - 1: Selects OSC1 clock source as its external reference clock.
 */
static inline void CLOCK_HAL_SetPll1RefMode(MCG_Type * base,
                                            mcg_pll_ref_mode_t setting)
{
    BW_MCG_C11_PLLREFSEL1(base, setting);
}
#endif /* FSL_FEATURE_MCG_USE_PLLREFSEL */

#endif /* FSL_FEATURE_MCG_HAS_PLL1 */

/*@}*/

/*! @name MCG OSC APIs */
/*@{*/

/*!
 * @brief Sets the OSC0 work mode.
 *
 * This function sets the OSC0 work mode, include frequency range select, high gain
 * oscillator select, and external reference select.
 *
 * @param base  Base address for current MCG instance.
 * @param range     Frequency range select.
 * @param hgo       High gain oscillator select.
 * @param erefs     External reference select.
 */
void CLOCK_HAL_SetOsc0Mode(MCG_Type * base,
                           osc_range_t range,
                           osc_gain_t hgo,
                           osc_src_t erefs);

#if FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE
/*!
 * @brief Sets the PLL0 32 kHz Reference Select Setting.
 *
 * This function  selects the PLL0 reference clock source.
 *
 * @param base  Base address for current MCG instance.
 * @param setting  PLL0 32 kHz Reference Select Setting
 *                  - 0: Selects 32 kHz RTC clock source as its reference clock
 *                  - 1: Selects 32 kHz IRC clock source as its reference clock
 *                  - 2: Selects FLL external ref clock source as its ref clock
 */
static inline void CLOCK_HAL_SetPllRefSel0Mode(MCG_Type * base,
                                                mcg_pll_ref_clock_source_t setting)
{
    MCG_WR_C7_PLL32KREFSEL(base, setting);
}
#endif

/*!
 * @brief Gets the OSC initialization status.
 *
 * This function  gets the OSC Initialization Status. This bit, which resets to 0, is set
 * to 1 after the initialization cycles of the crystal oscillator clock have completed.
 * After being set, the bit is cleared to 0 if the OSC is subsequently disabled. See the
 * OSC module's detailed description for more information.
 *
 * @param base  Base address for current MCG instance.
 * @return True if OSC0 is stable.
 */
static inline bool CLOCK_HAL_IsOsc0Stable(MCG_Type * base)
{
    return (bool)MCG_BRD_S_OSCINIT0(base);
}

/*!
 * @brief Enables the OSC0 external clock monitor.
 *
 * This function enables the loss of clock monitoring circuit for the OSC0
 * external reference mux select. The monitor mode determines whether an
 * interrupt or a reset request is generated following a loss of the OSC0 indication.
 * External clock monitor should only be enabled when the MCG is in an operational
 * mode that uses the external clock (FEE, FBE, PEE, PBE, or BLPE). Whenever the
 * monitor is enabled, the value of the RANGE0 bits in the C2 register
 * should not be changed. External clock monitor should be disabled before the MCG
 * enters any Stop mode. Otherwise, a reset request may occur while in Stop mode.
 * External clock monitor should also be disabled before entering VLPR or VLPW
 * power modes if the MCG is in BLPE mode.
 *
 * @param base  Base address for current MCG instance.
 * @param mode Generate interrupt or reset when OSC loss detected.
 */
void CLOCK_HAL_EnableOsc0Monitor(MCG_Type * base, mcg_osc_monitor_mode_t mode);

/*!
 * @brief Disables the OSC0 external clock monitor.
 *
 * This function disables the loss of clock monitoring circuit for the OSC0
 * external reference mux select.
 *
 * @param base  Base address for current MCG instance.
 */
static inline void CLOCK_HAL_DisableOsc0Monitor(MCG_Type * base)
{
    MCG_BWR_C6_CME0(base, 0U);
}

/*!
 * @brief Checks the OSC0 external clock monitor is enabled or not.
 *
 * This function checks whether the loss of clock monitoring circuit for the OSC0
 * external reference mux select is enabled or not.
 *
 * @param base  Base address for current MCG instance.
 * @return True if monitor is enabled.
 */
static inline bool CLOCK_HAL_IsOsc0MonitorEnabled(MCG_Type * base)
{
    return (bool)MCG_BRD_C6_CME0(base);
}

/*!
 * @brief Gets the OSC0 Loss of Clock Status.
 *
 * This function  gets the OSC0 Loss of Clock Status. The LOCS0 indicates when a loss of
 * OSC0 reference clock has occurred. The LOCS0 bit only has an effect when CME0 is set.
 *
 * @param base  Base address for current MCG instance.
 * @return True if loss of OSC0 has occurred.
 */
static inline bool CLOCK_HAL_IsOsc0LostLock(MCG_Type * base)
{
    return (bool)MCG_BRD_SC_LOCS0(base);
}

/*!
 * @brief Clears the OSC0 Loss of Clock Status.
 *
 * This function clears the OSC0 Loss of Clock Status.
 *
 * @param base  Base address for current MCG instance.
 */
static inline void CLOCK_HAL_ClearOsc0LostLock(MCG_Type * base)
{
    MCG_BWR_SC_LOCS0(base, 1U);
}

#if FSL_FEATURE_MCG_HAS_RTC_32K
/*!
 * @brief Enables the RTC OSC external clock monitor.
 *
 * This function enables the loss of the clock monitoring circuit for the
 * output of the RTC external reference clock. The LOCRE1 bit  determines whether an
 * interrupt or a reset request is generated following a loss of the RTC clock indication.
 * The monitor should only be enabled when the MCG is in an operational mode
 * that uses the external clock (FEE, FBE, PEE, PBE, or BLPE). Monitor must be disabled
 * before the MCG enters any Stop mode. Otherwise, a reset request may occur
 * while in Stop mode. The monitor should also be disabled before entering VLPR or
 * VLPW power modes if the MCG is in BLPE mode.
 *
 * @param base  Base address for current MCG instance.
 * @param mode Generate interrupt or reset when RTC OSC loss detected.
 */
void CLOCK_HAL_EnableRtcOscMonitor(MCG_Type * base, mcg_osc_monitor_mode_t mode);

/*!
 * @brief Disables the RTC OSC external clock monitor.
 *
 * This function disables the loss of clock monitoring circuit for the RTC OSC
 * external reference mux select.
 *
 * @param base  Base address for current MCG instance.
 */
static inline void CLOCK_HAL_DisableRTCOscMonitor(MCG_Type * base)
{
    MCG_BWR_C8_CME1(base, 0U);
}

/*!
 * @brief Checks the OSC RTC external clock monitor is enabled or not.
 *
 * This function checks whether the loss of clock monitoring circuit for the OSC
 * RTC external reference mux select is enabled or not.
 *
 * @param base  Base address for current MCG instance.
 * @return True if monitor is enabled.
 */
static inline bool CLOCK_HAL_IsRtcOscMonitorEnabled(MCG_Type * base)
{
    return (bool)MCG_BRD_C8_CME1(base);
}

/*!
 * @brief Gets the RTC Loss of Clock Status.
 *
 * This function  gets the RTC Loss of Clock Status. This bit indicates when a loss
 * of clock has occurred. This bit is cleared by writing a logic 1 to it when set.
 *
 * @param base  Base address for current MCG instance.
 * @return True if loss of RTC has occurred
 */
static inline bool CLOCK_HAL_IsRtcOscLostLock(MCG_Type * base)
{
    return (bool)MCG_BRD_C8_LOCS1(base);
}

/*!
 * @brief Clears the RTC Loss of Clock Status.
 *
 * This function clears the RTC Loss of Clock Status.
 *
 * @param base  Base address for current MCG instance.
 */
static inline void CLOCK_HAL_ClearRtcOscLostLock(MCG_Type * base)
{
    MCG_BWR_C8_LOCS1(base, 1U);
}
#endif /* FSL_FEATURE_MCG_HAS_RTC_32K */

#if FSL_FEATURE_MCG_HAS_OSC1
/*!
 * @brief Sets the OSC0 work mode.
 *
 * This function sets the OSC0 work mode, includes the frequency range select, high gain
 * oscillator select and external reference select.
 *
 * @param base  Base address for current MCG instance.
 * @param range     Frequency range select.
 * @param hgo       High gain oscillator select.
 * @param erefs     External reference select.
 */
void CLOCK_HAL_SetOsc1Mode(MCG_Type * base,
                           osc_range_t range,
                           osc_gain_t hgo,
                           osc_src_t erefs);

/*!
 * @brief Gets the OSC1 Initialization Status.
 *
 * This function  gets the OSC1 Initialization Status. This bit is set after the
 * initialization cycles of the 2nd crystal oscillator clock have completed. See
 * the Oscillator block guide for more details.
 *
 * @param base  Base address for current MCG instance.
 * @return True is OSC1 is stable.
 */
static inline bool CLOCK_HAL_IsOsc1Stable(MCG_Type * base)
{
    return (bool)MCG_BRD_S2_OSCINIT1(base);
}

/*!
 * @brief Enables the OSC1 external clock monitor.
 *
 * This function enables the loss of the clock monitor for the OSC1 external
 * reference clock. The monitor mode determines whether a reset or interrupt
 * request is generated following a loss of OSC1 external reference clock.
 * The monitor should only be enabled when the MCG is in an operational mode
 * that uses the external clock (PEE or PBE). Whenever the monitor is enabled,
 * the value of the RANGE1 bits in the C10 register should not be changed.
 * The monitor should be disabled before the MCG enters any Stop mode.
 * Otherwise, a reset request may occur while in stop mode.
 *
 * @param base  Base address for current MCG instance.
 * @param mode Generate interrupt or reset when OSC loss detected.
 */
void CLOCK_HAL_EnableOsc1Monitor(MCG_Type * base, mcg_osc_monitor_mode_t mode);

/*!
 * @brief Disables the OSC1 external clock monitor.
 *
 * This function disables the loss of clock monitoring circuit for the OSC1
 * external reference mux select.
 *
 * @param base  Base address for current MCG instance.
 */
static inline void CLOCK_HAL_DisableOsc1Monitor(MCG_Type * base)
{
    MCG_BWR_C12_CME2(base, 0U);
}

/*!
 * @brief Checks the OSC1 external clock monitor is enabled or not.
 *
 * This function checks whether the loss of clock monitoring circuit for the OSC1
 * external reference mux select is enabled or not.
 *
 * @param base  Base address for current MCG instance.
 * @return True if monitor is enabled.
 */
static inline bool CLOCK_HAL_IsOsc1MonitorEnabled(MCG_Type * base)
{
    return (bool)MCG_BRD_C12_CME2(base);
}


/*!
 * @brief Gets the OSC1 Loss of Clock Status.
 *
 * This function gets the OSC1 Loss of Clock Status. This bit indicates when a loss
 * of the OSC1 external reference clock has occurred.
 *
 * @param base Base address for current MCG instance.
 * @return True if loss of OSC1 external reference clock has occurred.
 */
static inline bool CLOCK_HAL_IsOsc1LostLock(MCG_Type * base)
{
    return (bool)MCG_BRD_S2_LOCS2(base);
}

/*!
 * @brief Clears the OSC1 Loss of Clock Status.
 *
 * This function clears the OSC1 Loss of Clock Status.
 *
 * @param base Base address for current MCG instance.
 */
static inline void CLOCK_HAL_ClearOsc1LostLock(MCG_Type * base)
{
    MCG_BWR_S2_LOCS2(base, 1U);
}
#endif

#if FSL_FEATURE_MCG_HAS_EXTERNAL_PLL
/*!
 * @brief Enables the External PLL Clock monitor.
 *
 * This function enables the loss of the clock monitor for the External PLL
 * clock. The monitor mode determines whether a reset or interrupt
 * request is generated following a loss of EXT_PLL clock.
 * The monitor should only be enabled when the MCG is in an operational mode
 * that uses the EXT_PLL clock as CLKS source (PEE or PBE).
 *
 * @param base  Base address for current MCG instance.
 * @param mode Generate interrupt or reset when OSC loss detected.
 */
void CLOCK_HAL_EnableExtPllMonitor(MCG_Type * base, mcg_osc_monitor_mode_t mode);

/*!
 * @brief Disables the External PLL clock monitor.
 *
 * This function disables the loss of clock monitoring circuit for the External PLL
 * external reference mux select.
 *
 * @param base  Base address for current MCG instance.
 */
static inline void CLOCK_HAL_DisableExtPllMonitor(MCG_Type * base)
{
    MCG_BWR_C9_PLL_CME(base, 0U);
}

/*!
 * @brief Checks the External PLL clock monitor is enabled or not.
 *
 * This function checks whether the loss of clock monitoring circuit for the External PLL
 * clock is enabled or not.
 *
 * @param base  Base address for current MCG instance.
 * @return True if monitor is enabled.
 */
static inline bool CLOCK_HAL_IsExtPllMonitorEnabled(MCG_Type * base)
{
    return (bool)MCG_BRD_C9_PLL_CME(base);
}


/*!
 * @brief Gets the External PLL Loss of Clock Status.
 *
 * This function gets the External PLL Loss of Clock Status. This bit indicates when a loss
 * of the External PLL clock has occurred.
 *
 * @param base Base address for current MCG instance.
 * @return True if loss of External PLL clock has occurred.
 */
static inline bool CLOCK_HAL_IsExtPllLostLock(MCG_Type * base)
{
    return (bool)MCG_BRD_C9_EXT_PLL_LOCS(base);
}

/*!
 * @brief Clears the External PLL Loss of Clock Status.
 *
 * This function clears the External PLL Loss of Clock Status.
 *
 * @param base Base address for current MCG instance.
 */
static inline void CLOCK_HAL_ClearExtPllLostLock(MCG_Type * base)
{
    MCG_BWR_C9_EXT_PLL_LOCS(base, 1U);
}
#endif
/*@}*/

/*! @name MCG Auto Trim Machine (ATM) */
/*@{*/

/*!
 * @brief Auto trims the internal reference clock.
 *
 * This function trims the internal reference clock using external clock. If
 * successful, it returns the kMcgAtmErrorNone and the frequency after trimming is received
 * in the parameter actualFreq. If an error occurs, the error code is returned.
 *
 * @param base     Base address for current MCG instance.
 * @param extFreq      External clock frequency, should be bus clock.
 * @param desireFreq   Frequency want to trim to.
 * @param actualFreq   Actual frequency after trim.
 * @param atms         Trim fast or slow internal reference clock.
 * @return  Return kMcgAtmErrorNone if success, otherwise return error code.
 */
mcg_atm_error_t CLOCK_HAL_TrimInternalRefClk(MCG_Type* base,
                                             uint32_t  extFreq,
                                             uint32_t  desireFreq,
                                             uint32_t* actualFreq,
                                             mcg_atm_select_t atms);

/*!
 * @brief Gets the Automatic Trim machine Fail Flag.
 *
 * This function  gets the Automatic Trim machine Fail Flag. This bit asserts when the 
 * Automatic Trim Machine is
 * enabled (ATME=1) and a write to the C1, C3, C4, and SC registers is detected or the MCG
 * enters into a Stop mode. Writing to ATMF clears the flag.
 *
 * @param base  Base address for current MCG instance.
 * @return True if ATM failed.
 */
static inline bool CLOCK_HAL_IsAutoTrimMachineFailed(MCG_Type * base)
{
    return (bool)MCG_BRD_SC_ATMF(base);
}

/*!
 * @brief Clears the Automatic Trim machine Fail Flag.
 *
 * This function clears the Automatic Trim machine Fail Flag.
 *
 * @param base  Base address for current MCG instance.
 */
static inline void CLOCK_HAL_ClearAutoTrimMachineFailed(MCG_Type * base)
{
    MCG_BWR_SC_ATMF(base, 1U);
}

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif
#endif /* __FSL_MCG_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

