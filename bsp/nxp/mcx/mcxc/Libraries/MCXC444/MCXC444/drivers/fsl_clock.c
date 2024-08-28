/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif

#if (defined(OSC) && !(defined(OSC0)))
#define OSC0 OSC
#endif

#define MCG_HIRC_FREQ (48000000U)
#define MCG_LIRC_FREQ1 (2000000U)
#define MCG_LIRC_FREQ2 (8000000U)

#define MCG_S_CLKST_VAL ((MCG->S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT)
#define MCG_SC_FCRDIV_VAL ((MCG->SC & MCG_SC_FCRDIV_MASK) >> MCG_SC_FCRDIV_SHIFT)
#define MCG_MC_LIRC_DIV2_VAL ((MCG->MC & MCG_MC_LIRC_DIV2_MASK) >> MCG_MC_LIRC_DIV2_SHIFT)
#define MCG_C2_IRCS_VAL ((MCG->C2 & MCG_C2_IRCS_MASK) >> MCG_C2_IRCS_SHIFT)

#define SIM_CLKDIV1_OUTDIV1_VAL ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)
#define SIM_CLKDIV1_OUTDIV4_VAL ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT)
#define SIM_SOPT1_OSC32KSEL_VAL ((SIM->SOPT1 & SIM_SOPT1_OSC32KSEL_MASK) >> SIM_SOPT1_OSC32KSEL_SHIFT)

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* External XTAL0 (OSC0) clock frequency. */
volatile uint32_t g_xtal0Freq;
/* External XTAL32K clock frequency. */
volatile uint32_t g_xtal32Freq;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the current MCG_Lite LIRC_CLK frequency in Hz.
 *
 * This function will return the LIRC_CLK value in frequency(Hz) based
 * on current MCG_Lite configurations and settings. It is an internal function.
 *
 * @return MCG_Lite LIRC_CLK frequency.
 */
static uint32_t CLOCK_GetLircClkFreq(void);

/*!
 * @brief Get RANGE value based on OSC frequency.
 *
 * To setup external crystal oscillator, must set the register bits RANGE base
 * on the crystal frequency. This function returns the RANGE base on the input
 * frequency. This is an internal function.
 *
 * @return RANGE value.
 */
static uint8_t CLOCK_GetOscRangeFromFreq(uint32_t freq);

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t CLOCK_GetLircClkFreq(void)
{
    static const uint32_t lircFreqs[] = {MCG_LIRC_FREQ1, MCG_LIRC_FREQ2};
    uint32_t freq;

    /* Check whether the LIRC is enabled. */
    if (((MCG->C1 & MCG_C1_IRCLKEN_MASK) != 0U) || ((uint8_t)kMCGLITE_ClkSrcLirc == MCG_S_CLKST_VAL))
    {
        freq = lircFreqs[MCG_C2_IRCS_VAL];
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

static uint8_t CLOCK_GetOscRangeFromFreq(uint32_t freq)
{
    uint8_t range;

    if (freq <= 39063U)
    {
        range = 0U;
    }
    else if (freq <= 8000000U)
    {
        range = 1U;
    }
    else
    {
        range = 2U;
    }

    return range;
}

/*!
 * brief Get the OSC0 external reference clock frequency (OSC0ERCLK).
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetOsc0ErClkFreq(void)
{
    uint32_t freq;

    if ((OSC0->CR & OSC_CR_ERCLKEN_MASK) != 0U)
    {
        /* Please call CLOCK_SetXtal0Freq base on board setting before using OSC0 clock. */
        assert(g_xtal0Freq);
        freq = g_xtal0Freq;
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Get the external reference 32K clock frequency (ERCLK32K).
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetEr32kClkFreq(void)
{
    uint32_t freq;

    switch (SIM_SOPT1_OSC32KSEL_VAL)
    {
        case 0U: /* OSC 32k clock  */
            freq = (CLOCK_GetOsc0ErClkFreq() == 32768U) ? 32768U : 0U;
            break;
        case 2U: /* RTC 32k clock  */
            /* Please call CLOCK_SetXtal32Freq base on board setting before using XTAL32K/RTC_CLKIN clock. */
            assert(g_xtal32Freq);
            freq = g_xtal32Freq;
            break;
        case 3U: /* LPO clock      */
            freq = LPO_CLK_FREQ;
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/*!
 * brief Get the platform clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetPlatClkFreq(void)
{
    return CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV1_VAL + 1U);
}

/*!
 * brief Get the flash clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetFlashClkFreq(void)
{
    uint32_t freq;

    freq = CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV1_VAL + 1U);
    freq /= (SIM_CLKDIV1_OUTDIV4_VAL + 1U);

    return freq;
}

/*!
 * brief Get the bus clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetBusClkFreq(void)
{
    uint32_t freq;

    freq = CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV1_VAL + 1U);
    freq /= (SIM_CLKDIV1_OUTDIV4_VAL + 1U);

    return freq;
}

/*!
 * brief Get the core clock or system clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetCoreSysClkFreq(void)
{
    return CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV1_VAL + 1U);
}

/*!
 * brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_name_t.
 * The MCG must be properly configured before using this function.
 *
 * param clockName Clock names defined in clock_name_t
 * return Clock frequency value in Hertz
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName)
{
    uint32_t freq;

    switch (clockName)
    {
        case kCLOCK_CoreSysClk:
        case kCLOCK_PlatClk:
            freq = CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV1_VAL + 1U);
            break;
        case kCLOCK_BusClk:
        case kCLOCK_FlashClk:
            freq = CLOCK_GetOutClkFreq() / (SIM_CLKDIV1_OUTDIV1_VAL + 1U);
            freq /= (SIM_CLKDIV1_OUTDIV4_VAL + 1U);
            break;
        case kCLOCK_Er32kClk:
            freq = CLOCK_GetEr32kClkFreq();
            break;
        case kCLOCK_Osc0ErClk:
            freq = CLOCK_GetOsc0ErClkFreq();
            break;
        case kCLOCK_McgInternalRefClk:
            freq = CLOCK_GetInternalRefClkFreq();
            break;
        case kCLOCK_McgPeriphClk:
        case kCLOCK_McgIrc48MClk:
            freq = CLOCK_GetPeriphClkFreq();
            break;
        case kCLOCK_LpoClk:
            freq = LPO_CLK_FREQ;
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*!
 * brief Set the clock configure in SIM module.
 *
 * This function sets system layer clock settings in SIM module.
 *
 * param config Pointer to the configure structure.
 */
void CLOCK_SetSimConfig(sim_clock_config_t const *config)
{
    SIM->CLKDIV1 = config->clkdiv1;
    CLOCK_SetEr32kClock(config->er32kSrc);
}

/*! brief Enable USB FS clock.
 *
 * param src  USB FS clock source.
 * param freq The frequency specified by src.
 * retval true The clock is set successfully.
 * retval false The clock source is invalid to get proper USB FS clock.
 */
bool CLOCK_EnableUsbfs0Clock(clock_usb_src_t src, uint32_t freq)
{
    bool ret = true;

    CLOCK_DisableClock(kCLOCK_Usbfs0);

    if (kCLOCK_UsbSrcExt == src)
    {
        SIM->SOPT2 &= ~SIM_SOPT2_USBSRC_MASK;
    }
    else
    {
        SIM->SOPT2 |= SIM_SOPT2_USBSRC_MASK;
    }

    CLOCK_EnableClock(kCLOCK_Usbfs0);

    if (kCLOCK_UsbSrcIrc48M == src)
    {
        USB0->CLK_RECOVER_IRC_EN = 0x03U;
        USB0->CLK_RECOVER_CTRL |= USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK;
    }

    return ret;
}

/*!
 * brief Gets the MCG internal reference clock (MCGIRCLK) frequency.
 *
 * This function gets the MCG_Lite internal reference clock frequency in Hz based
 * on the current MCG register value.
 *
 * return The frequency of MCGIRCLK.
 */
uint32_t CLOCK_GetInternalRefClkFreq(void)
{
    uint8_t divider1 = MCG_SC_FCRDIV_VAL;
    uint8_t divider2 = MCG_MC_LIRC_DIV2_VAL;
    /* LIRC internal reference clock is selected*/
    return CLOCK_GetLircClkFreq() >> (divider1 + divider2);
}

/*
 * brief Gets the current MCGPCLK frequency.
 *
 * This function gets the MCGPCLK frequency in Hz based on the current MCG_Lite
 * register settings.
 *
 * return The frequency of MCGPCLK.
 */
uint32_t CLOCK_GetPeriphClkFreq(void)
{
    uint32_t freq;

    /* Check whether the HIRC is enabled. */
    if (((MCG->MC & MCG_MC_HIRCEN_MASK) != 0U) || ((uint8_t)kMCGLITE_ClkSrcHirc == MCG_S_CLKST_VAL))
    {
        freq = MCG_HIRC_FREQ;
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the MCG_Lite output clock (MCGOUTCLK) frequency.
 *
 * This function gets the MCG_Lite output clock frequency in Hz based on the current
 * MCG_Lite register value.
 *
 * return The frequency of MCGOUTCLK.
 */
uint32_t CLOCK_GetOutClkFreq(void)
{
    uint32_t freq;

    switch (MCG_S_CLKST_VAL)
    {
        case (uint8_t)kMCGLITE_ClkSrcHirc:
            freq = MCG_HIRC_FREQ;
            break;
        case (uint8_t)kMCGLITE_ClkSrcLirc:
            freq = CLOCK_GetLircClkFreq() >> MCG_SC_FCRDIV_VAL;
            break;
        case (uint8_t)kMCGLITE_ClkSrcExt:
            /* Please call CLOCK_SetXtal0Freq base on board setting before using OSC0 clock. */
            assert(g_xtal0Freq);
            freq = g_xtal0Freq;
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*!
 * brief Gets the current MCG_Lite mode.
 *
 * This function checks the MCG_Lite registers and determines the current MCG_Lite mode.
 *
 * return The current MCG_Lite mode or error code.
 */
mcglite_mode_t CLOCK_GetMode(void)
{
    mcglite_mode_t mode;

    switch (MCG_S_CLKST_VAL)
    {
        case (uint8_t)kMCGLITE_ClkSrcHirc: /* HIRC */
            mode = kMCGLITE_ModeHirc48M;
            break;
        case (uint8_t)kMCGLITE_ClkSrcLirc: /* LIRC */
            if ((uint8_t)kMCGLITE_Lirc2M == MCG_C2_IRCS_VAL)
            {
                mode = kMCGLITE_ModeLirc2M;
            }
            else
            {
                mode = kMCGLITE_ModeLirc8M;
            }
            break;
        case (uint8_t)kMCGLITE_ClkSrcExt: /* EXT  */
            mode = kMCGLITE_ModeExt;
            break;
        default:
            mode = kMCGLITE_ModeError;
            break;
    }

    return mode;
}

/*!
 * brief Sets the MCG_Lite configuration.
 *
 * This function configures the MCG_Lite, includes the output clock source, MCGIRCLK
 * settings, HIRC settings, and so on. See ref mcglite_config_t for details.
 *
 * param  targetConfig Pointer to the target MCG_Lite mode configuration structure.
 * return Error code.
 */
status_t CLOCK_SetMcgliteConfig(mcglite_config_t const *targetConfig)
{
    assert(targetConfig);

    /*
     * If switch between LIRC8M and LIRC2M, need to switch to HIRC mode first,
     * because could not switch directly.
     */
    if (((uint8_t)kMCGLITE_ClkSrcLirc == MCG_S_CLKST_VAL) && (kMCGLITE_ClkSrcLirc == targetConfig->outSrc) &&
        (MCG_C2_IRCS_VAL != (uint8_t)(targetConfig->ircs)))
    {
        MCG->C1 = (uint8_t)((MCG->C1 & ~MCG_C1_CLKS_MASK) | MCG_C1_CLKS(kMCGLITE_ClkSrcHirc));
        while ((uint8_t)kMCGLITE_ClkSrcHirc != MCG_S_CLKST_VAL)
        {
        }
    }

    /* Set configuration now. */
    MCG->SC = MCG_SC_FCRDIV(targetConfig->fcrdiv);
    MCG->MC = MCG_MC_HIRCEN(targetConfig->hircEnableInNotHircMode) | MCG_MC_LIRC_DIV2(targetConfig->lircDiv2);
    MCG->C2 = (uint8_t)((MCG->C2 & ~MCG_C2_IRCS_MASK) | MCG_C2_IRCS(targetConfig->ircs));
    MCG->C1 = MCG_C1_CLKS(targetConfig->outSrc) | targetConfig->irclkEnableMode;

    /*
     * If external oscillator used and MCG_Lite is set to EXT mode, need to
     * wait for the OSC stable.
     */
    if (((MCG->C2 & MCG_C2_EREFS0_MASK) != 0U) && (kMCGLITE_ClkSrcExt == targetConfig->outSrc))
    {
        while (0U == (MCG->S & MCG_S_OSCINIT0_MASK))
        {
        }
    }

    /* Wait for clock source change completed. */
    while ((uint8_t)targetConfig->outSrc != MCG_S_CLKST_VAL)
    {
    }

    return kStatus_Success;
}

/*!
 * brief Initializes the OSC0.
 *
 * This function initializes the OSC0 according to the board configuration.
 *
 * param  config Pointer to the OSC0 configuration structure.
 */
void CLOCK_InitOsc0(osc_config_t const *config)
{
    uint8_t range = CLOCK_GetOscRangeFromFreq(config->freq);

    OSC_SetCapLoad(OSC0, config->capLoad);
    OSC_SetExtRefClkConfig(OSC0, &config->oscerConfig);

    MCG->C2 = ((MCG->C2 & MCG_C2_IRCS_MASK) | MCG_C2_RANGE0(range) | (uint8_t)config->workMode);

    if ((kOSC_ModeExt != config->workMode) && ((OSC0->CR & OSC_CR_ERCLKEN_MASK) != 0U))
    {
        /* Wait for stable. */
        while (0U == (MCG->S & MCG_S_OSCINIT0_MASK))
        {
        }
    }
}

/*!
 * brief Deinitializes the OSC0.
 *
 * This function deinitializes the OSC0.
 */
void CLOCK_DeinitOsc0(void)
{
    OSC0->CR = 0U;
    MCG->C2 &= MCG_C2_IRCS_MASK;
}
