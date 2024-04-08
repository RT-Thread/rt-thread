/*
 * Copyright 2017 - 2021 , NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_clock.h"
#include "fsl_power.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif
#define NVALMAX (0x100U)
#define PVALMAX (0x20U)
#define MVALMAX (0x10000U)

#define PLL_MAX_N_DIV 0x100U

/*--------------------------------------------------------------------------
!!! If required these #defines can be moved to chip library file
----------------------------------------------------------------------------*/

#define PLL_SSCG1_MDEC_VAL_P (10U) /* MDEC is in bits  25 downto 10 */
#define PLL_SSCG1_MDEC_VAL_M (0xFFFFULL << PLL_SSCG1_MDEC_VAL_P)
#define PLL_NDEC_VAL_P       (0U) /* NDEC is in bits  9:0 */
#define PLL_NDEC_VAL_M       (0xFFUL << PLL_NDEC_VAL_P)
#define PLL_PDEC_VAL_P       (0U) /*!<  PDEC is in bits 6:0 */
#define PLL_PDEC_VAL_M       (0x1FUL << PLL_PDEC_VAL_P)

#define PLL_MIN_CCO_FREQ_MHZ (275000000U)
#define PLL_MAX_CCO_FREQ_MHZ (550000000U)
#define PLL_LOWER_IN_LIMIT   (2000U)     /*!<  Minimum PLL input rate */
#define PLL_HIGHER_IN_LIMIT  (96000000U) /*!<  Maximum PLL input rate */
#define PLL_MIN_IN_SSMODE    (3000000U)
#define PLL_MAX_IN_SSMODE \
    (100000000U) /*!<  Not find the value in UM, Just use the maximum frequency which device support */

/* PLL NDEC reg */
#define PLL_NDEC_VAL_SET(value) (((unsigned long)(value) << PLL_NDEC_VAL_P) & PLL_NDEC_VAL_M)
/* PLL PDEC reg */
#define PLL_PDEC_VAL_SET(value) (((unsigned long)(value) << PLL_PDEC_VAL_P) & PLL_PDEC_VAL_M)
/* SSCG control1 */
#define PLL_SSCG1_MDEC_VAL_SET(value) (((uint64_t)(value) << PLL_SSCG1_MDEC_VAL_P) & PLL_SSCG1_MDEC_VAL_M)

/* PLL0 SSCG control1 */
#define PLL0_SSCG_MD_FRACT_P 0U
#define PLL0_SSCG_MD_INT_P   25U
#define PLL0_SSCG_MD_FRACT_M (0x1FFFFFFUL << PLL0_SSCG_MD_FRACT_P)
#define PLL0_SSCG_MD_INT_M   ((uint64_t)0xFFUL << PLL0_SSCG_MD_INT_P)

#define PLL0_SSCG_MD_FRACT_SET(value) (((uint64_t)(value) << PLL0_SSCG_MD_FRACT_P) & PLL0_SSCG_MD_FRACT_M)
#define PLL0_SSCG_MD_INT_SET(value)   (((uint64_t)(value) << PLL0_SSCG_MD_INT_P) & PLL0_SSCG_MD_INT_M)

/* Saved value of PLL output rate, computed whenever needed to save run-time
   computation on each call to retrive the PLL rate. */
static uint32_t s_Pll0_Freq;
static uint32_t s_Pll1_Freq;

/** External clock rate on the CLKIN pin in Hz. If not used,
    set this to 0. Otherwise, set it to the exact rate in Hz this pin is
    being driven at. */
static uint32_t s_Ext_Clk_Freq   = 16000000U;
static uint32_t s_I2S_Mclk_Freq  = 0U;
static uint32_t s_PLU_ClkIn_Freq = 0U;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* Find SELP, SELI, and SELR values for raw M value, max M = MVALMAX */
static void pllFindSel(uint32_t M, uint32_t *pSelP, uint32_t *pSelI, uint32_t *pSelR);
/* Get predivider (N) from PLL0 NDEC setting */
static uint32_t findPll0PreDiv(void);
/* Get predivider (N) from PLL1 NDEC setting */
static uint32_t findPll1PreDiv(void);
/* Get postdivider (P) from PLL0 PDEC setting */
static uint32_t findPll0PostDiv(void);
/* Get postdivider (P) from PLL1 PDEC setting. */
static uint32_t findPll1PostDiv(void);
/* Get multiplier (M) from PLL0 MDEC and SSCG settings */
static float findPll0MMult(void);
/* Get multiplier (M) from PLL1 MDEC. */
static uint32_t findPll1MMult(void);
/* Get the greatest common divisor */
static uint32_t FindGreatestCommonDivisor(uint32_t m, uint32_t n);
/* Set PLL output based on desired output rate */
static pll_error_t CLOCK_GetPll0Config(uint32_t finHz, uint32_t foutHz, pll_setup_t *pSetup, bool useSS);
/* Update local PLL rate variable */
static void CLOCK_GetPLL0OutFromSetupUpdate(pll_setup_t *pSetup);
/* Update local PLL1 rate variable */
static void CLOCK_GetPLL1OutFromSetupUpdate(pll_setup_t *pSetup);

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Clock Selection for IP */
/**
 * brief   Configure the clock selection muxes.
 * param   connection  : Clock to be configured.
 * return  Nothing
 */
void CLOCK_AttachClk(clock_attach_id_t connection)
{
    uint8_t mux;
    uint8_t sel;
    uint16_t item;
    uint32_t tmp32 = (uint32_t)connection;
    uint32_t i;
    volatile uint32_t *pClkSel;

    pClkSel = &(SYSCON->SYSTICKCLKSELX[0]);

    if (kNONE_to_NONE != connection)
    {
        for (i = 0U; i < 2U; i++)
        {
            if (tmp32 == 0U)
            {
                break;
            }
            item = (uint16_t)GET_ID_ITEM(tmp32);
            if (item != 0U)
            {
                mux = (uint8_t)GET_ID_ITEM_MUX(item);
                sel = (uint8_t)GET_ID_ITEM_SEL(item);
                if (mux == CM_RTCOSC32KCLKSEL)
                {
                    PMC->RTCOSC32K = (PMC->RTCOSC32K & ~PMC_RTCOSC32K_SEL_MASK) | PMC_RTCOSC32K_SEL(sel);
                }
                else if (mux == CM_OSTIMERCLKSEL)
                {
                    PMC->OSTIMERr = (PMC->OSTIMERr & ~PMC_OSTIMER_OSTIMERCLKSEL_MASK) | PMC_OSTIMER_OSTIMERCLKSEL(sel);
                }
                else
                {
                    pClkSel[mux] = sel;
                }
            }
            tmp32 = GET_ID_NEXT_ITEM(tmp32); /* pick up next descriptor */
        }
    }
}

/* Return the actual clock attach id */
/**
 * brief   Get the actual clock attach id.
 * This fuction uses the offset in input attach id, then it reads the actual source value in
 * the register and combine the offset to obtain an actual attach id.
 * param   attachId  : Clock attach id to get.
 * return  Clock source value.
 */
clock_attach_id_t CLOCK_GetClockAttachId(clock_attach_id_t attachId)
{
    uint8_t mux;
    uint32_t actualSel;
    uint32_t tmp32 = (uint32_t)attachId;
    uint32_t i;
    uint32_t actualAttachId = 0U;
    uint32_t selector       = GET_ID_SELECTOR(tmp32);
    volatile uint32_t *pClkSel;

    pClkSel = &(SYSCON->SYSTICKCLKSELX[0]);

    if (kNONE_to_NONE == attachId)
    {
        return kNONE_to_NONE;
    }

    for (i = 0U; i < 2U; i++)
    {
        mux = (uint8_t)GET_ID_ITEM_MUX(tmp32);
        if (tmp32 != 0UL)
        {
            if (mux == CM_RTCOSC32KCLKSEL)
            {
                actualSel = ((PMC->RTCOSC32K) & PMC_RTCOSC32K_SEL_MASK) >> PMC_RTCOSC32K_SEL_SHIFT;
            }
            else if (mux == CM_OSTIMERCLKSEL)
            {
                actualSel = ((PMC->OSTIMERr) & PMC_OSTIMER_OSTIMERCLKSEL_MASK) >> PMC_OSTIMER_OSTIMERCLKSEL_SHIFT;
            }
            else
            {
                actualSel = pClkSel[mux];
            }

            /* Consider the combination of two registers */
            actualAttachId |= CLK_ATTACH_ID(mux, actualSel, i);
        }
        tmp32 = GET_ID_NEXT_ITEM(tmp32); /*!<  pick up next descriptor */
    }

    actualAttachId |= selector;

    return (clock_attach_id_t)actualAttachId;
}

/* Set IP Clock Divider */
/**
 * brief   Setup peripheral clock dividers.
 * param   div_name    : Clock divider name
 * param divided_by_value: Value to be divided
 * param reset :  Whether to reset the divider counter.
 * return  Nothing
 */
void CLOCK_SetClkDiv(clock_div_name_t div_name, uint32_t divided_by_value, bool reset)
{
    volatile uint32_t *pClkDiv;

    pClkDiv = &(SYSCON->SYSTICKCLKDIV0);

    if ((div_name >= kCLOCK_DivFlexFrg0) && (div_name <= kCLOCK_DivFlexFrg7))
    {
        /*!<  Flexcomm Interface function clock = (clock selected via FCCLKSEL) / (1+ MULT /DIV), DIV = 0xFF */
        ((volatile uint32_t *)pClkDiv)[(uint8_t)div_name] =
            SYSCON_FLEXFRG0CTRL_DIV_MASK | SYSCON_FLEXFRG0CTRL_MULT(divided_by_value);
    }
    else
    {
        if (reset)
        {
            ((volatile uint32_t *)pClkDiv)[(uint8_t)div_name] = 1UL << 29U;
        }
        if (divided_by_value == 0U) /*!<  halt */
        {
            ((volatile uint32_t *)pClkDiv)[(uint8_t)div_name] = 1UL << 30U;
        }
        else
        {
            ((volatile uint32_t *)pClkDiv)[(uint8_t)div_name] = (divided_by_value - 1U);
        }
    }
}

/* Set RTC 1KHz Clock Divider */
/**
 * brief   Setup rtc 1khz clock divider.
 * param divided_by_value: Value to be divided
 * return  Nothing
 */
void CLOCK_SetRtc1khzClkDiv(uint32_t divided_by_value)
{
    PMC->RTCOSC32K =
        (PMC->RTCOSC32K & ~PMC_RTCOSC32K_CLK1KHZDIV_MASK) | PMC_RTCOSC32K_CLK1KHZDIV(divided_by_value - 28U);
}

/* Set RTC 1KHz Clock Divider */
/**
 * brief   Setup rtc 1hz clock divider.
 * param divided_by_value: Value to be divided
 * return  Nothing
 */
void CLOCK_SetRtc1hzClkDiv(uint32_t divided_by_value)
{
    if (divided_by_value == 0U) /*!<  halt */
    {
        PMC->RTCOSC32K |= (1UL << PMC_RTCOSC32K_CLK1HZDIVHALT_SHIFT);
    }
    else
    {
        PMC->RTCOSC32K =
            (PMC->RTCOSC32K & ~PMC_RTCOSC32K_CLK1HZDIV_MASK) | PMC_RTCOSC32K_CLK1HZDIV(divided_by_value - 31744U);
    }
}

/* Set FRO Clocking */
/**
 * brief   Initialize the Core clock to given frequency (12, 48 or 96 MHz).
 * Turns on FRO and uses default CCO, if freq is 12000000, then high speed output is off, else high speed output is
 * enabled.
 * param   iFreq   : Desired frequency (must be one of #CLK_FRO_12MHZ or #CLK_FRO_48MHZ or #CLK_FRO_96MHZ)
 * return  returns success or fail status.
 */
status_t CLOCK_SetupFROClocking(uint32_t iFreq)
{
    if ((iFreq != 12000000U) && (iFreq != 96000000U))
    {
        return kStatus_Fail;
    }
    /* Enable Analog Control module */
    SYSCON->PRESETCTRLCLR[2] = (1UL << SYSCON_PRESETCTRL2_ANALOG_CTRL_RST_SHIFT);
    SYSCON->AHBCLKCTRLSET[2] = SYSCON_AHBCLKCTRL2_ANALOG_CTRL_MASK;
    /* Power up the FRO192M */
    POWER_DisablePD(kPDRUNCFG_PD_FRO192M);

    if (iFreq == 96000000U)
    {
        ANACTRL->FRO192M_CTRL |= ANACTRL_FRO192M_CTRL_ENA_96MHZCLK(1);
    }
    /* always enable
    else if (iFreq == 48000000U)
    {
        ANACTRL->FRO192M_CTRL |= ANACTRL_FRO192M_CTRL_ENA_48MHZCLK(1);
    }*/
    else
    {
        ANACTRL->FRO192M_CTRL |= ANACTRL_FRO192M_CTRL_ENA_12MHZCLK(1);
    }
    return kStatus_Success;
}

/* Set the FLASH wait states for the passed frequency */
/**
 * brief    Set the flash wait states for the input freuqency.
 * param    iFreq: Input frequency
 * return    Nothing
 */
typedef struct
{
    uint32_t waitstate;
    uint32_t freqMax;
} WaitStateInterval_t;

/* clang-format off */
/* Wait state if frequency is inferior to the one specified */
static const WaitStateInterval_t IntervalList[] = {
    {0, 11000000},
    {1, 22000000},
    {2, 33000000},
    {3, 44000000},
    {4, 55000000},
    {5, 66000000},
    {6, 84000000},
    {7, 96000000} /* Maximum allowed frequency (96 MHz) */
};
/* clang-format on */

void CLOCK_SetFLASHAccessCyclesForFreq(uint32_t system_freq_hz)
{
    /* Flash Controller & FMC internal number of Wait States (minus 1) */
    uint32_t num_wait_states = 15UL; /* Default to the maximum number of wait states */

    for (size_t cnt = 0; cnt < (sizeof(IntervalList) / sizeof(WaitStateInterval_t)); cnt++)
    {
        if (system_freq_hz <= IntervalList[cnt].freqMax)
        {
            num_wait_states = IntervalList[cnt].waitstate;
            break;
        }
    }

    FLASH->INT_CLR_STATUS = 0x1F; /* Clear all status flags */

    FLASH->DATAW[0] = (FLASH->DATAW[0] & 0xFFFFFFF0UL) |
                      (num_wait_states & (SYSCON_FMCCR_FLASHTIM_MASK >> SYSCON_FMCCR_FLASHTIM_SHIFT));

    FLASH->CMD = 0x2; /* CMD_SET_READ_MODE */

    /* Wait until the cmd is completed (without error) */
    while ((FLASH->INT_STATUS & FLASH_INT_STATUS_DONE_MASK) == 0UL)
    {
    }

    /* Adjust FMC waiting time cycles (num_wait_states) */
    SYSCON->FMCCR = (SYSCON->FMCCR & ~SYSCON_FMCCR_FLASHTIM_MASK) |
                    ((num_wait_states << SYSCON_FMCCR_FLASHTIM_SHIFT) & SYSCON_FMCCR_FLASHTIM_MASK);
}

/* Set EXT OSC Clk */
/**
 * brief   Initialize the external osc clock to given frequency.
 * Crystal oscillator with an operating frequency of 12 MHz to 32 MHz.
 * Option for external clock input (bypass mode) for clock frequencies of up to 25 MHz.
 * param   iFreq   : Desired frequency (must be equal to exact rate in Hz)
 * return  returns success or fail status.
 */
status_t CLOCK_SetupExtClocking(uint32_t iFreq)
{
    if (iFreq > 32000000U)
    {
        return kStatus_Fail;
    }
    /* Turn on power for crystal 32 MHz */
    POWER_DisablePD(kPDRUNCFG_PD_XTAL32M);
    POWER_DisablePD(kPDRUNCFG_PD_LDOXO32M);
    /* Enable clock_in clock for clock module. */
    SYSCON->CLOCK_CTRL |= SYSCON_CLOCK_CTRL_CLKIN_ENA_MASK;

    s_Ext_Clk_Freq = iFreq;
    return kStatus_Success;
}

/* Set I2S MCLK Clk */
/**
 * brief   Initialize the I2S MCLK clock to given frequency.
 * param   iFreq   : Desired frequency (must be equal to exact rate in Hz)
 * return  returns success or fail status.
 */
status_t CLOCK_SetupI2SMClkClocking(uint32_t iFreq)
{
    s_I2S_Mclk_Freq = iFreq;
    return kStatus_Success;
}

/* Set PLU CLKIN Clk */
/**
 * brief   Initialize the PLU CLKIN clock to given frequency.
 * param   iFreq   : Desired frequency (must be equal to exact rate in Hz)
 * return  returns success or fail status.
 */
status_t CLOCK_SetupPLUClkInClocking(uint32_t iFreq)
{
    s_PLU_ClkIn_Freq = iFreq;
    return kStatus_Success;
}

/* Get CLOCK OUT Clk */
/*! brief  Return Frequency of ClockOut
 *  return Frequency of ClockOut
 */
uint32_t CLOCK_GetClockOutClkFreq(void)
{
    uint32_t freq = 0U;

    switch (SYSCON->CLKOUTSEL)
    {
        case 0U:
            freq = CLOCK_GetCoreSysClkFreq();
            break;

        case 1U:
            freq = CLOCK_GetPll0OutFreq();
            break;

        case 2U:
            freq = CLOCK_GetExtClkFreq();
            break;

        case 3U:
            freq = CLOCK_GetFroHfFreq();
            break;

        case 4U:
            freq = CLOCK_GetFro1MFreq();
            break;

        case 5U:
            freq = CLOCK_GetPll1OutFreq();
            break;

        case 6U:
            freq = CLOCK_GetOsc32KFreq();
            break;

        case 7U:
            freq = 0U;
            break;

        default:
            freq = 0U;
            break;
    }
    return freq / ((SYSCON->CLKOUTDIV & 0xffU) + 1U);
}

/* Get CAN Clk */
/*! brief  Return Frequency of Can Clock
 *  return Frequency of Can.
 */
uint32_t CLOCK_GetMCanClkFreq(void)
{
    uint32_t freq = 0U;

    switch (SYSCON->CANCLKSEL)
    {
        case 0U:
            freq = CLOCK_GetCoreSysClkFreq() / ((SYSCON->CANCLKDIV & SYSCON_CANCLKDIV_DIV_MASK) + 1U);
            break;
        case 1U:
            freq = CLOCK_GetFro1MFreq();
            break;
        case 2U:
            freq = CLOCK_GetOsc32KFreq();
            break;
        case 7U:
            freq = 0U;
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}

/* Get ADC Clk */
/*! brief  Return Frequency of Adc Clock
 *  return Frequency of Adc.
 */
uint32_t CLOCK_GetAdcClkFreq(void)
{
    uint32_t freq = 0U;

    switch (SYSCON->ADCCLKSEL)
    {
        case 0U:
            freq = CLOCK_GetCoreSysClkFreq();
            break;
        case 1U:
            freq = CLOCK_GetPll0OutFreq();
            break;
        case 2U:
            freq = CLOCK_GetFroHfFreq();
            break;
        case 7U:
            freq = 0U;
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((SYSCON->ADCCLKDIV & SYSCON_ADCCLKDIV_DIV_MASK) + 1U);
}

/* Get MCLK Clk */
/*! brief  Return Frequency of MClk Clock
 *  return Frequency of MClk Clock.
 */
uint32_t CLOCK_GetMclkClkFreq(void)
{
    uint32_t freq = 0U;

    switch (SYSCON->MCLKCLKSEL)
    {
        case 0U:
            freq = CLOCK_GetFroHfFreq();
            break;
        case 1U:
            freq = CLOCK_GetPll0OutFreq();
            break;
        case 7U:
            freq = 0U;
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((SYSCON->MCLKDIV & 0xffU) + 1U);
}

/* Get SCTIMER Clk */
/*! brief  Return Frequency of SCTimer Clock
 *  return Frequency of SCTimer Clock.
 */
uint32_t CLOCK_GetSctClkFreq(void)
{
    uint32_t freq = 0U;

    switch (SYSCON->SCTCLKSEL)
    {
        case 0U:
            freq = CLOCK_GetCoreSysClkFreq();
            break;
        case 1U:
            freq = CLOCK_GetPll0OutFreq();
            break;
        case 2U:
            freq = CLOCK_GetExtClkFreq();
            break;
        case 3U:
            freq = CLOCK_GetFroHfFreq();
            break;
        case 5U:
            freq = CLOCK_GetI2SMClkFreq();
            break;
        case 7U:
            freq = 0U;
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((SYSCON->SCTCLKDIV & 0xffU) + 1U);
}

/* Get FRO 12M Clk */
/*! brief  Return Frequency of FRO 12MHz
 *  return Frequency of FRO 12MHz
 */
uint32_t CLOCK_GetFro12MFreq(void)
{
    return ((ANACTRL->FRO192M_CTRL & ANACTRL_FRO192M_CTRL_ENA_12MHZCLK_MASK) != 0UL) ? 12000000U : 0U;
}

/* Get FRO 1M Clk */
/*! brief  Return Frequency of FRO 1MHz
 *  return Frequency of FRO 1MHz
 */
uint32_t CLOCK_GetFro1MFreq(void)
{
    return ((SYSCON->CLOCK_CTRL & SYSCON_CLOCK_CTRL_FRO1MHZ_CLK_ENA_MASK) != 0UL) ? 1000000U : 0U;
}

/* Get EXT OSC Clk */
/*! brief  Return Frequency of External Clock
 *  return Frequency of External Clock. If no external clock is used returns 0.
 */
uint32_t CLOCK_GetExtClkFreq(void)
{
    return ((ANACTRL->XO32M_CTRL & ANACTRL_XO32M_CTRL_ENABLE_SYSTEM_CLK_OUT_MASK) != 0UL) ? s_Ext_Clk_Freq : 0U;
}

/* Get WATCH DOG Clk */
/*! brief  Return Frequency of Watchdog
 *  return Frequency of Watchdog
 */
uint32_t CLOCK_GetWdtClkFreq(void)
{
    return CLOCK_GetFro1MFreq() / ((SYSCON->WDTCLKDIV & SYSCON_WDTCLKDIV_DIV_MASK) + 1U);
}

/* Get HF FRO Clk */
/*! brief  Return Frequency of High-Freq output of FRO
 *  return Frequency of High-Freq output of FRO
 */
uint32_t CLOCK_GetFroHfFreq(void)
{
    return ((ANACTRL->FRO192M_CTRL & ANACTRL_FRO192M_CTRL_ENA_96MHZCLK_MASK) != 0UL) ? 96000000U : 0U;
}

/* Get SYSTEM PLL Clk */
/*! brief  Return Frequency of PLL
 *  return Frequency of PLL
 */
uint32_t CLOCK_GetPll0OutFreq(void)
{
    return s_Pll0_Freq;
}

/* Get USB PLL Clk */
/*! brief  Return Frequency of USB PLL
 *  return Frequency of PLL
 */
uint32_t CLOCK_GetPll1OutFreq(void)
{
    return s_Pll1_Freq;
}

/* Get RTC OSC Clk */
/*! brief  Return Frequency of 32kHz osc
 *  return Frequency of 32kHz osc
 */
uint32_t CLOCK_GetOsc32KFreq(void)
{
    return ((0UL == (PMC->PDRUNCFG0 & PMC_PDRUNCFG0_PDEN_FRO32K_MASK)) &&
            (0UL == (PMC->RTCOSC32K & PMC_RTCOSC32K_SEL_MASK))) ?
               CLK_RTC_32K_CLK :
               ((0UL == (PMC->PDRUNCFG0 & PMC_PDRUNCFG0_PDEN_XTAL32K_MASK)) &&
                ((PMC->RTCOSC32K & PMC_RTCOSC32K_SEL_MASK) != 0UL)) ?
               CLK_RTC_32K_CLK :
               0UL;
}

/* Get MAIN Clk */
/*! brief  Return Frequency of Core System
 *  return Frequency of Core System
 */
uint32_t CLOCK_GetCoreSysClkFreq(void)
{
    uint32_t freq = 0U;

    switch (SYSCON->MAINCLKSELB)
    {
        case 0U:
            if (SYSCON->MAINCLKSELA == 0U)
            {
                freq = CLOCK_GetFro12MFreq();
            }
            else if (SYSCON->MAINCLKSELA == 1U)
            {
                freq = CLOCK_GetExtClkFreq();
            }
            else if (SYSCON->MAINCLKSELA == 2U)
            {
                freq = CLOCK_GetFro1MFreq();
            }
            else if (SYSCON->MAINCLKSELA == 3U)
            {
                freq = CLOCK_GetFroHfFreq();
            }
            else
            {
                /* Added comments to avoid the violation of MISRA C-2012 rule 15.7 */
            }
            break;
        case 1U:
            freq = CLOCK_GetPll0OutFreq();
            break;
        case 2U:
            freq = CLOCK_GetPll1OutFreq();
            break;

        case 3U:
            freq = CLOCK_GetOsc32KFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}

/* Get I2S MCLK Clk */
/*! brief  Return Frequency of I2S MCLK Clock
 *  return Frequency of I2S MCLK Clock
 */
uint32_t CLOCK_GetI2SMClkFreq(void)
{
    return s_I2S_Mclk_Freq;
}

/* Get PLU CLKIN Clk */
/*! brief  Return Frequency of PLU CLKIN Clock
 *  return Frequency of PLU CLKIN Clock
 */
uint32_t CLOCK_GetPLUClkInFreq(void)
{
    return s_PLU_ClkIn_Freq;
}

/* Get FLEXCOMM input clock */
/*! brief  Return Frequency of flexcomm input clock
 *  param  id     : flexcomm instance id
 *  return Frequency value
 */
uint32_t CLOCK_GetFlexCommInputClock(uint32_t id)
{
    uint32_t freq = 0U;

    switch (SYSCON->FCCLKSELX[id])
    {
        case 0U:
            freq = CLOCK_GetCoreSysClkFreq();
            break;
        case 1U:
            freq = CLOCK_GetPll0OutFreq() / ((SYSCON->PLL0CLKDIV & 0xffU) + 1U);
            break;
        case 2U:
            freq = CLOCK_GetFro12MFreq();
            break;
        case 3U:
            freq = CLOCK_GetFroHfFreq() / ((SYSCON->FROHFDIV & 0xffU) + 1U);
            break;
        case 4U:
            freq = CLOCK_GetFro1MFreq();
            break;
        case 5U:
            freq = CLOCK_GetI2SMClkFreq();
            break;
        case 6U:
            freq = CLOCK_GetOsc32KFreq();
            break;
        case 7U:
            freq = 0U;
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}

/* Get FLEXCOMM Clk */
uint32_t CLOCK_GetFlexCommClkFreq(uint32_t id)
{
    uint32_t freq   = 0U;
    uint32_t frgMul = 0U;
    uint32_t frgDiv = 0U;

    freq   = CLOCK_GetFlexCommInputClock(id);
    frgMul = (SYSCON->FLEXFRGXCTRL[id] & SYSCON_FLEXFRG0CTRL_MULT_MASK) >> 8U;
    frgDiv = SYSCON->FLEXFRGXCTRL[id] & SYSCON_FLEXFRG0CTRL_DIV_MASK;
    return (uint32_t)(((uint64_t)freq * ((uint64_t)frgDiv + 1ULL)) / (frgMul + frgDiv + 1UL));
}

/* Get HS_LPSI Clk */
uint32_t CLOCK_GetHsLspiClkFreq(void)
{
    uint32_t freq = 0U;

    switch (SYSCON->HSLSPICLKSEL)
    {
        case 0U:
            freq = CLOCK_GetCoreSysClkFreq();
            break;
        case 1U:
            freq = CLOCK_GetPll0OutFreq() / ((SYSCON->PLL0CLKDIV & 0xffU) + 1U);
            break;
        case 2U:
            freq = CLOCK_GetFro12MFreq();
            break;
        case 3U:
            freq = CLOCK_GetFroHfFreq() / ((SYSCON->FROHFDIV & 0xffU) + 1U);
            break;
        case 4U:
            freq = CLOCK_GetFro1MFreq();
            break;
        case 6U:
            freq = CLOCK_GetOsc32KFreq();
            break;
        case 7U:
            freq = 0U;
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}

/* Get CTimer Clk */
/*! brief  Return Frequency of CTimer functional Clock
 *  return Frequency of CTimer functional Clock
 */
uint32_t CLOCK_GetCTimerClkFreq(uint32_t id)
{
    uint32_t freq = 0U;

    switch (SYSCON->CTIMERCLKSELX[id])
    {
        case 0U:
            freq = CLOCK_GetCoreSysClkFreq();
            break;
        case 1U:
            freq = CLOCK_GetPll0OutFreq();
            break;
        case 3U:
            freq = CLOCK_GetFroHfFreq();
            break;
        case 4U:
            freq = CLOCK_GetFro1MFreq();
            break;
        case 5U:
            freq = CLOCK_GetI2SMClkFreq();
            break;
        case 6U:
            freq = CLOCK_GetOsc32KFreq();
            break;
        case 7U:
            freq = 0U;
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}

/* Get Systick Clk */
/*! brief  Return Frequency of SystickClock
 *  return Frequency of Systick Clock
 */
uint32_t CLOCK_GetSystickClkFreq(uint32_t id)
{
    uint32_t freq = 0U;

    switch (SYSCON->SYSTICKCLKSELX[id])
    {
        case 0U:
            /*Niobe4mini just has one SYSTICKSEL and SYSTICKDIV register, Fix coverity problem in this way temporarily
             */
            freq = CLOCK_GetCoreSysClkFreq() / (((SYSCON->SYSTICKCLKDIV0) & 0xffU) + 1U);
            break;
        case 1U:
            freq = CLOCK_GetFro1MFreq();
            break;
        case 2U:
            freq = CLOCK_GetOsc32KFreq();
            break;
        case 7U:
            freq = 0U;
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}

/* Set FlexComm Clock */
/**
 * brief   Set the flexcomm output frequency.
 * param   id      : flexcomm instance id
 *          freq    : output frequency
 * return  0   : the frequency range is out of range.
 *          1   : switch successfully.
 */
uint32_t CLOCK_SetFlexCommClock(uint32_t id, uint32_t freq)
{
    uint32_t input = CLOCK_GetFlexCommClkFreq(id);
    uint32_t mul;

    if ((freq > 48000000UL) || (freq > input) || (input / freq >= 2UL))
    {
        /* FRG output frequency should be less than equal to 48MHz */
        return 0UL;
    }
    else
    {
        mul                      = (uint32_t)((((uint64_t)input - freq) * 256ULL) / ((uint64_t)freq));
        SYSCON->FLEXFRGXCTRL[id] = (mul << 8U) | 0xFFU;
        return 1UL;
    }
}

/* Get IP Clk */
/*! brief  Return Frequency of selected clock
 *  return Frequency of selected clock
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName)
{
    uint32_t freq;
    switch (clockName)
    {
        case kCLOCK_CoreSysClk:
            freq = CLOCK_GetCoreSysClkFreq();
            break;
        case kCLOCK_BusClk:
            freq = CLOCK_GetCoreSysClkFreq() / ((SYSCON->AHBCLKDIV & 0xffU) + 1U);
            break;
        case kCLOCK_ClockOut:
            freq = CLOCK_GetClockOutClkFreq();
            break;
        case kCLOCK_Pll1Out:
            freq = CLOCK_GetPll1OutFreq();
            break;
        case kCLOCK_Mclk:
            freq = CLOCK_GetMclkClkFreq();
            break;
        case kCLOCK_FroHf:
            freq = CLOCK_GetFroHfFreq();
            break;
        case kCLOCK_Fro12M:
            freq = CLOCK_GetFro12MFreq();
            break;
        case kCLOCK_Fro1M:
            freq = CLOCK_GetFro1MFreq();
            break;
        case kCLOCK_ExtClk:
            freq = CLOCK_GetExtClkFreq();
            break;
        case kCLOCK_Pll0Out:
            freq = CLOCK_GetPll0OutFreq();
            break;
        case kCLOCK_FlexI2S:
            freq = CLOCK_GetI2SMClkFreq();
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/* Find SELP, SELI, and SELR values for raw M value, max M = MVALMAX */
static void pllFindSel(uint32_t M, uint32_t *pSelP, uint32_t *pSelI, uint32_t *pSelR)
{
    uint32_t seli, selp;
    /* bandwidth: compute selP from Multiplier */
    if ((SYSCON->PLL0SSCG1 & SYSCON_PLL0SSCG1_MDIV_EXT_MASK) != 0UL) /* normal mode */
    {
        selp = (M >> 2U) + 1U;
        if (selp >= 31U)
        {
            selp = 31U;
        }
        *pSelP = selp;

        if (M >= 8000UL)
        {
            seli = 1UL;
        }
        else if (M >= 122UL)
        {
            seli = (uint32_t)(8000UL / M); /*floor(8000/M) */
        }
        else
        {
            seli = 2UL * ((uint32_t)(M / 4UL)) + 3UL; /* 2*floor(M/4) + 3 */
        }

        if (seli >= 63UL)
        {
            seli = 63UL;
        }
        *pSelI = seli;

        *pSelR = 0UL;
    }
    else
    {
        /* Note: If the spread spectrum mode, choose N to ensure 3 MHz < Fin/N < 5 MHz */
        *pSelP = 3U;
        *pSelI = 4U;
        *pSelR = 4U;
    }
}

/* Get predivider (N) from PLL0 NDEC setting */
static uint32_t findPll0PreDiv(void)
{
    uint32_t preDiv = 1UL;

    /* Direct input is not used? */
    if ((SYSCON->PLL0CTRL & SYSCON_PLL0CTRL_BYPASSPREDIV_MASK) == 0UL)
    {
        preDiv = SYSCON->PLL0NDEC & SYSCON_PLL0NDEC_NDIV_MASK;
        if (preDiv == 0UL)
        {
            preDiv = 1UL;
        }
    }
    return preDiv;
}

/* Get predivider (N) from PLL1 NDEC setting */
static uint32_t findPll1PreDiv(void)
{
    uint32_t preDiv = 1UL;

    /* Direct input is not used? */
    if ((SYSCON->PLL1CTRL & SYSCON_PLL1CTRL_BYPASSPREDIV_MASK) == 0UL)
    {
        preDiv = SYSCON->PLL1NDEC & SYSCON_PLL1NDEC_NDIV_MASK;
        if (preDiv == 0UL)
        {
            preDiv = 1UL;
        }
    }
    return preDiv;
}

/* Get postdivider (P) from PLL0 PDEC setting */
static uint32_t findPll0PostDiv(void)
{
    uint32_t postDiv = 1UL;

    if ((SYSCON->PLL0CTRL & SYSCON_PLL0CTRL_BYPASSPOSTDIV_MASK) == 0UL)
    {
        if ((SYSCON->PLL0CTRL & SYSCON_PLL0CTRL_BYPASSPOSTDIV2_MASK) != 0UL)
        {
            postDiv = SYSCON->PLL0PDEC & SYSCON_PLL0PDEC_PDIV_MASK;
        }
        else
        {
            postDiv = 2UL * (SYSCON->PLL0PDEC & SYSCON_PLL0PDEC_PDIV_MASK);
        }
        if (postDiv == 0UL)
        {
            postDiv = 2UL;
        }
    }
    return postDiv;
}

/* Get postdivider (P) from PLL1 PDEC setting. */
static uint32_t findPll1PostDiv(void)
{
    uint32_t postDiv = 1UL;

    if ((SYSCON->PLL1CTRL & SYSCON_PLL1CTRL_BYPASSPOSTDIV_MASK) == 0UL)
    {
        if ((SYSCON->PLL1CTRL & SYSCON_PLL1CTRL_BYPASSPOSTDIV2_MASK) != 0UL)
        {
            postDiv = SYSCON->PLL1PDEC & SYSCON_PLL1PDEC_PDIV_MASK;
        }
        else
        {
            postDiv = 2UL * (SYSCON->PLL1PDEC & SYSCON_PLL1PDEC_PDIV_MASK);
        }
        if (postDiv == 0UL)
        {
            postDiv = 2UL;
        }
    }

    return postDiv;
}

/* Get multiplier (M) from PLL0 SSCG and SEL_EXT settings */
static float findPll0MMult(void)
{
    float mMult = 1.0F;
    float mMult_fract;
    uint32_t mMult_int;

    if ((SYSCON->PLL0SSCG1 & SYSCON_PLL0SSCG1_SEL_EXT_MASK) != 0UL)
    {
        mMult =
            (float)(uint32_t)((SYSCON->PLL0SSCG1 & SYSCON_PLL0SSCG1_MDIV_EXT_MASK) >> SYSCON_PLL0SSCG1_MDIV_EXT_SHIFT);
    }
    else
    {
        mMult_int   = ((SYSCON->PLL0SSCG1 & SYSCON_PLL0SSCG1_MD_MBS_MASK) << 7U);
        mMult_int   = mMult_int | ((SYSCON->PLL0SSCG0) >> PLL0_SSCG_MD_INT_P);
        mMult_fract = ((float)(uint32_t)((SYSCON->PLL0SSCG0) & PLL0_SSCG_MD_FRACT_M) /
                       (float)(uint32_t)(1UL << PLL0_SSCG_MD_INT_P));
        mMult       = (float)mMult_int + mMult_fract;
    }
    if(0ULL == ((uint64_t)mMult))
    {
        mMult = 1.0F;
    }
    return mMult;
}

/* Get multiplier (M) from PLL1 MDEC. */
static uint32_t findPll1MMult(void)
{
    uint32_t mMult = 1UL;

    mMult = SYSCON->PLL1MDEC & SYSCON_PLL1MDEC_MDIV_MASK;

    if (mMult == 0UL)
    {
        mMult = 1UL;
    }

    return mMult;
}

/* Find greatest common divisor between m and n */
static uint32_t FindGreatestCommonDivisor(uint32_t m, uint32_t n)
{
    uint32_t tmp;

    while (n != 0U)
    {
        tmp = n;
        n   = m % n;
        m   = tmp;
    }

    return m;
}

/*
 * Set PLL0 output based on desired output rate.
 * In this function, the it calculates the PLL0 setting for output frequency from input clock
 * frequency. The calculation would cost a few time. So it is not recommaned to use it frequently.
 * the "pllctrl", "pllndec", "pllpdec", "pllmdec" would updated in this function.
 */
static pll_error_t CLOCK_GetPll0ConfigInternal(uint32_t finHz, uint32_t foutHz, pll_setup_t *pSetup, bool useSS)
{
    uint32_t nDivOutHz, fccoHz;
    uint32_t pllPreDivider, pllMultiplier, pllPostDivider;
    uint32_t pllDirectInput, pllDirectOutput;
    uint32_t pllSelP, pllSelI, pllSelR, uplimoff;

    /* Baseline parameters (no input or output dividers) */
    pllPreDivider   = 1U; /* 1 implies pre-divider will be disabled */
    pllPostDivider  = 1U; /* 1 implies post-divider will be disabled */
    pllDirectOutput = 1U;

    /* Verify output rate parameter */
    if (foutHz > PLL_MAX_CCO_FREQ_MHZ)
    {
        /* Maximum PLL output with post divider=1 cannot go above this frequency */
        return kStatus_PLL_OutputTooHigh;
    }
    if (foutHz < (PLL_MIN_CCO_FREQ_MHZ / (PVALMAX << 1U)))
    {
        /* Minmum PLL output with maximum post divider cannot go below this frequency */
        return kStatus_PLL_OutputTooLow;
    }

    /* If using SS mode, input clock needs to be between 3MHz and 20MHz */
    if (useSS)
    {
        /* Verify input rate parameter */
        if (finHz < PLL_MIN_IN_SSMODE)
        {
            /* Input clock into the PLL cannot be lower than this */
            return kStatus_PLL_InputTooLow;
        }
        /* PLL input in SS mode must be under 20MHz */
        if (finHz > (PLL_MAX_IN_SSMODE * NVALMAX))
        {
            return kStatus_PLL_InputTooHigh;
        }
    }
    else
    {
        /* Verify input rate parameter */
        if (finHz < PLL_LOWER_IN_LIMIT)
        {
            /* Input clock into the PLL cannot be lower than this */
            return kStatus_PLL_InputTooLow;
        }
        if (finHz > PLL_HIGHER_IN_LIMIT)
        {
            /* Input clock into the PLL cannot be higher than this */
            return kStatus_PLL_InputTooHigh;
        }
    }

    /* Find the optimal CCO frequency for the output and input that
       will keep it inside the PLL CCO range. This may require
       tweaking the post-divider for the PLL. */
    fccoHz = foutHz;
    while (fccoHz < PLL_MIN_CCO_FREQ_MHZ)
    {
        /* CCO output is less than minimum CCO range, so the CCO output
           needs to be bumped up and the post-divider is used to bring
           the PLL output back down. */
        pllPostDivider++;
        if (pllPostDivider > PVALMAX)
        {
            return kStatus_PLL_OutsideIntLimit;
        }

        /* Target CCO goes up, PLL output goes down */
        /* divide-by-2 divider in the post-divider is always work*/
        fccoHz          = foutHz * (pllPostDivider * 2U);
        pllDirectOutput = 0U;
    }

    /* Determine if a pre-divider is needed to get the best frequency */
    if ((finHz > PLL_LOWER_IN_LIMIT) && (fccoHz >= finHz) && (useSS == false))
    {
        uint32_t a = FindGreatestCommonDivisor(fccoHz, finHz);

        if (a > PLL_LOWER_IN_LIMIT)
        {
            a = finHz / a;
            if ((a != 0U) && (a < PLL_MAX_N_DIV))
            {
                pllPreDivider = a;
            }
        }
    }

    /* Bypass pre-divider hardware if pre-divider is 1 */
    if (pllPreDivider > 1U)
    {
        pllDirectInput = 0U;
    }
    else
    {
        pllDirectInput = 1U;
    }

    /* Determine PLL multipler */
    nDivOutHz     = (finHz / pllPreDivider);
    pllMultiplier = (fccoHz / nDivOutHz);

    /* Find optimal values for filter */
    if (useSS == false)
    {
        /* Will bumping up M by 1 get us closer to the desired CCO frequency? */
        if ((nDivOutHz * ((pllMultiplier * 2U) + 1U)) < (fccoHz * 2U))
        {
            pllMultiplier++;
        }

        /* Setup filtering */
        pllFindSel(pllMultiplier, &pllSelP, &pllSelI, &pllSelR);
        uplimoff = 0U;

        /* Get encoded value for M (mult) and use manual filter, disable SS mode */
        pSetup->pllsscg[1] =
            (uint32_t)((PLL_SSCG1_MDEC_VAL_SET(pllMultiplier)) | (1UL << SYSCON_PLL0SSCG1_SEL_EXT_SHIFT));
    }
    else
    {
        uint64_t fc;

        /* Filtering will be handled by SSC */
        pllSelR  = 0UL;
        pllSelI  = 0UL;
        pllSelP  = 0UL;
        uplimoff = 1U;

        /* The PLL multiplier will get very close and slightly under the
           desired target frequency. A small fractional component can be
           added to fine tune the frequency upwards to the target. */
        fc = ((uint64_t)(uint32_t)(fccoHz % nDivOutHz) << 25UL) / nDivOutHz;

        /* Set multiplier */
        pSetup->pllsscg[0] = (uint32_t)(PLL0_SSCG_MD_INT_SET(pllMultiplier) | PLL0_SSCG_MD_FRACT_SET((uint32_t)fc));
        pSetup->pllsscg[1] = (uint32_t)(PLL0_SSCG_MD_INT_SET(pllMultiplier) >> 32U);
    }

    /* Get encoded values for N (prediv) and P (postdiv) */
    pSetup->pllndec = PLL_NDEC_VAL_SET(pllPreDivider);
    pSetup->pllpdec = PLL_PDEC_VAL_SET(pllPostDivider);

    /* PLL control */
    pSetup->pllctrl = (pllSelR << SYSCON_PLL0CTRL_SELR_SHIFT) |                  /* Filter coefficient */
                      (pllSelI << SYSCON_PLL0CTRL_SELI_SHIFT) |                  /* Filter coefficient */
                      (pllSelP << SYSCON_PLL0CTRL_SELP_SHIFT) |                  /* Filter coefficient */
                      (0UL << SYSCON_PLL0CTRL_BYPASSPLL_SHIFT) |                 /* PLL bypass mode disabled */
                      (uplimoff << SYSCON_PLL0CTRL_LIMUPOFF_SHIFT) |             /* SS/fractional mode disabled */
                      (pllDirectInput << SYSCON_PLL0CTRL_BYPASSPREDIV_SHIFT) |   /* Bypass pre-divider? */
                      (pllDirectOutput << SYSCON_PLL0CTRL_BYPASSPOSTDIV_SHIFT) | /* Bypass post-divider? */
                      (1UL << SYSCON_PLL0CTRL_CLKEN_SHIFT);                      /* Ensure the PLL clock output */

    return kStatus_PLL_Success;
}

#if (defined(CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT) && CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT)
/* Alloct the static buffer for cache. */
static pll_setup_t s_PllSetupCacheStruct[CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT];
static uint32_t s_FinHzCache[CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT]  = {0};
static uint32_t s_FoutHzCache[CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT] = {0};
static bool s_UseSSCache[CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT]      = {false};
static uint32_t s_PllSetupCacheIdx                                  = 0U;
#endif /* CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT */

/*
 * Calculate the PLL setting values from input clock freq to output freq.
 */
static pll_error_t CLOCK_GetPll0Config(uint32_t finHz, uint32_t foutHz, pll_setup_t *pSetup, bool useSS)
{
    pll_error_t retErr;
#if (defined(CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT) && CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT)
    uint32_t i;

    for (i = 0U; i < CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT; i++)
    {
        if ((finHz == s_FinHzCache[i]) && (foutHz == s_FoutHzCache[i]) && (useSS == s_UseSSCache[i]))
        {
            /* Hit the target in cache buffer. */
            pSetup->pllctrl    = s_PllSetupCacheStruct[i].pllctrl;
            pSetup->pllndec    = s_PllSetupCacheStruct[i].pllndec;
            pSetup->pllpdec    = s_PllSetupCacheStruct[i].pllpdec;
            pSetup->pllsscg[0] = s_PllSetupCacheStruct[i].pllsscg[0];
            pSetup->pllsscg[1] = s_PllSetupCacheStruct[i].pllsscg[1];
            retErr             = kStatus_PLL_Success;
            break;
        }
    }

    if (i < CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT)
    {
        return retErr;
    }
#endif /* CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT */

    retErr = CLOCK_GetPll0ConfigInternal(finHz, foutHz, pSetup, useSS);

#if (defined(CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT) && CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT)
    /* Cache the most recent calulation result into buffer. */
    s_FinHzCache[s_PllSetupCacheIdx]  = finHz;
    s_FoutHzCache[s_PllSetupCacheIdx] = foutHz;
    s_UseSSCache[s_PllSetupCacheIdx]  = useSS;

    s_PllSetupCacheStruct[s_PllSetupCacheIdx].pllctrl    = pSetup->pllctrl;
    s_PllSetupCacheStruct[s_PllSetupCacheIdx].pllndec    = pSetup->pllndec;
    s_PllSetupCacheStruct[s_PllSetupCacheIdx].pllpdec    = pSetup->pllpdec;
    s_PllSetupCacheStruct[s_PllSetupCacheIdx].pllsscg[0] = pSetup->pllsscg[0];
    s_PllSetupCacheStruct[s_PllSetupCacheIdx].pllsscg[1] = pSetup->pllsscg[1];
    /* Update the index for next available buffer. */
    s_PllSetupCacheIdx = (s_PllSetupCacheIdx + 1U) % CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT;
#endif /* CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT */

    return retErr;
}

/* Update local PLL rate variable */
static void CLOCK_GetPLL0OutFromSetupUpdate(pll_setup_t *pSetup)
{
    s_Pll0_Freq = CLOCK_GetPLL0OutFromSetup(pSetup);
}

/* Update local PLL1 rate variable */
static void CLOCK_GetPLL1OutFromSetupUpdate(pll_setup_t *pSetup)
{
    s_Pll1_Freq = CLOCK_GetPLL1OutFromSetup(pSetup);
}

/* Return System PLL input clock rate */
/*! brief    Return  PLL0 input clock rate
 *  return    PLL0 input clock rate
 */
uint32_t CLOCK_GetPLL0InClockRate(void)
{
    uint32_t clkRate = 0U;

    switch ((SYSCON->PLL0CLKSEL & SYSCON_PLL0CLKSEL_SEL_MASK))
    {
        case 0x00U:
            clkRate = CLK_FRO_12MHZ;
            break;

        case 0x01U:
            clkRate = CLOCK_GetExtClkFreq();
            break;

        case 0x02U:
            clkRate = CLOCK_GetFro1MFreq();
            break;

        case 0x03U:
            clkRate = CLOCK_GetOsc32KFreq();
            break;

        default:
            clkRate = 0U;
            break;
    }

    return clkRate;
}

/* Return PLL1 input clock rate */
uint32_t CLOCK_GetPLL1InClockRate(void)
{
    uint32_t clkRate = 0U;

    switch ((SYSCON->PLL1CLKSEL & SYSCON_PLL1CLKSEL_SEL_MASK))
    {
        case 0x00U:
            clkRate = CLK_FRO_12MHZ;
            break;

        case 0x01U:
            clkRate = CLOCK_GetExtClkFreq();
            break;

        case 0x02U:
            clkRate = CLOCK_GetFro1MFreq();
            break;

        case 0x03U:
            clkRate = CLOCK_GetOsc32KFreq();
            break;

        default:
            clkRate = 0U;
            break;
    }

    return clkRate;
}

/* Return PLL0 output clock rate from setup structure */
/*! brief    Return PLL0 output clock rate from setup structure
 *  param    pSetup : Pointer to a PLL setup structure
 *  return   PLL0 output clock rate the setup structure will generate
 */
uint32_t CLOCK_GetPLL0OutFromSetup(pll_setup_t *pSetup)
{
    uint32_t clkRate = 0;
    uint32_t prediv, postdiv;
    float workRate = 0.0F;

    /* Get the input clock frequency of PLL. */
    clkRate = CLOCK_GetPLL0InClockRate();

    if (((pSetup->pllctrl & SYSCON_PLL0CTRL_BYPASSPLL_MASK) == 0UL) &&
        ((pSetup->pllctrl & SYSCON_PLL0CTRL_CLKEN_MASK) != 0UL) &&
        ((PMC->PDRUNCFG0 & PMC_PDRUNCFG0_PDEN_PLL0_MASK) == 0UL) &&
        ((PMC->PDRUNCFG0 & PMC_PDRUNCFG0_PDEN_PLL0_SSCG_MASK) == 0UL))
    {
        prediv  = findPll0PreDiv();
        postdiv = findPll0PostDiv();
        /* Adjust input clock */
        clkRate = clkRate / prediv;
        /* MDEC used for rate */
        workRate = (float)clkRate * (float)findPll0MMult();
        workRate /= (float)postdiv;
    }

    return (uint32_t)workRate;
}

/* Return PLL1 output clock rate from setup structure */
/*! brief    Return PLL1 output clock rate from setup structure
 *  param    pSetup : Pointer to a PLL setup structure
 *  return   PLL0 output clock rate the setup structure will generate
 */
uint32_t CLOCK_GetPLL1OutFromSetup(pll_setup_t *pSetup)
{
    uint32_t clkRate = 0;
    uint32_t prediv, postdiv;
    uint32_t workRate = 0UL;

    /* Get the input clock frequency of PLL. */
    clkRate = CLOCK_GetPLL1InClockRate();

    if (((pSetup->pllctrl & SYSCON_PLL1CTRL_BYPASSPLL_MASK) == 0UL) &&
        ((pSetup->pllctrl & SYSCON_PLL1CTRL_CLKEN_MASK) != 0UL) &&
        ((PMC->PDRUNCFG0 & PMC_PDRUNCFG0_PDEN_PLL1_MASK) == 0UL))
    {
        prediv  = findPll1PreDiv();
        postdiv = findPll1PostDiv();
        /* Adjust input clock */
        clkRate = clkRate / prediv;
        /* MDEC used for rate */
        workRate = clkRate * findPll1MMult();
        workRate /= postdiv;
    }

    return workRate;
}

/* Set the current PLL0 Rate */
/*! brief Store the current PLL rate
 *  param    rate: Current rate of the PLL
 *  return   Nothing
 **/
void CLOCK_SetStoredPLL0ClockRate(uint32_t rate)
{
    s_Pll0_Freq = rate;
}

/* Return PLL0 output clock rate */
/*! brief    Return  PLL0 output clock rate
 *  param    recompute   : Forces a PLL rate recomputation if true
 *  return    PLL0 output clock rate
 *  note The PLL rate is cached in the driver in a variable as
 *  the rate computation function can take some time to perform. It
 *  is recommended to use 'false' with the 'recompute' parameter.
 */
uint32_t CLOCK_GetPLL0OutClockRate(bool recompute)
{
    pll_setup_t Setup;
    uint32_t rate;

    if ((recompute) || (s_Pll0_Freq == 0U))
    {
        Setup.pllctrl    = SYSCON->PLL0CTRL;
        Setup.pllndec    = SYSCON->PLL0NDEC;
        Setup.pllpdec    = SYSCON->PLL0PDEC;
        Setup.pllsscg[0] = SYSCON->PLL0SSCG0;
        Setup.pllsscg[1] = SYSCON->PLL0SSCG1;

        CLOCK_GetPLL0OutFromSetupUpdate(&Setup);
    }

    rate = s_Pll0_Freq;

    return rate;
}

/*! brief    Return  PLL1 output clock rate
 *  param    recompute   : Forces a PLL rate recomputation if true
 *  return    PLL1 output clock rate
 *  note The PLL rate is cached in the driver in a variable as
 *  the rate computation function can take some time to perform. It
 *  is recommended to use 'false' with the 'recompute' parameter.
 */
uint32_t CLOCK_GetPLL1OutClockRate(bool recompute)
{
    pll_setup_t Setup;
    uint32_t rate;

    if ((recompute) || (s_Pll1_Freq == 0U))
    {
        Setup.pllctrl = SYSCON->PLL1CTRL;
        Setup.pllndec = SYSCON->PLL1NDEC;
        Setup.pllpdec = SYSCON->PLL1PDEC;
        Setup.pllmdec = SYSCON->PLL1MDEC;
        CLOCK_GetPLL1OutFromSetupUpdate(&Setup);
    }

    rate = s_Pll1_Freq;

    return rate;
}

/* Set PLL0 output based on the passed PLL setup data */
/*! brief    Set PLL output based on the passed PLL setup data
 *  param    pControl    : Pointer to populated PLL control structure to generate setup with
 *  param    pSetup      : Pointer to PLL setup structure to be filled
 *  return   PLL_ERROR_SUCCESS on success, or PLL setup error code
 *  note Actual frequency for setup may vary from the desired frequency based on the
 *  accuracy of input clocks, rounding, non-fractional PLL mode, etc.
 */
pll_error_t CLOCK_SetupPLL0Data(pll_config_t *pControl, pll_setup_t *pSetup)
{
    uint32_t inRate;
    bool useSS = (bool)((pControl->flags & PLL_CONFIGFLAG_FORCENOFRACT) == 0UL);

    pll_error_t pllError;

    /* Determine input rate for the PLL */
    if ((pControl->flags & PLL_CONFIGFLAG_USEINRATE) != 0UL)
    {
        inRate = pControl->inputRate;
    }
    else
    {
        inRate = CLOCK_GetPLL0InClockRate();
    }

    /* PLL flag options */
    pllError = CLOCK_GetPll0Config(inRate, pControl->desiredRate, pSetup, useSS);
    if ((useSS) && (pllError == kStatus_PLL_Success))
    {
        /* If using SS mode, then some tweaks are made to the generated setup */
        pSetup->pllsscg[1] |= (uint32_t)pControl->ss_mf | (uint32_t)pControl->ss_mr | (uint32_t)pControl->ss_mc;
        if (pControl->mfDither)
        {
            pSetup->pllsscg[1] |= (1UL << SYSCON_PLL0SSCG1_DITHER_SHIFT);
        }
    }

    return pllError;
}

/* Set PLL0 output from PLL setup structure */
/*! brief    Set PLL output from PLL setup structure (precise frequency)
 * param pSetup  : Pointer to populated PLL setup structure
 * param flagcfg : Flag configuration for PLL config structure
 * return    PLL_ERROR_SUCCESS on success, or PLL setup error code
 * note  This function will power off the PLL, setup the PLL with the
 * new setup data, and then optionally powerup the PLL, wait for PLL lock,
 * and adjust system voltages to the new PLL rate. The function will not
 * alter any source clocks (ie, main systen clock) that may use the PLL,
 * so these should be setup prior to and after exiting the function.
 */
pll_error_t CLOCK_SetupPLL0Prec(pll_setup_t *pSetup, uint32_t flagcfg)
{
    uint32_t inRate, clkRate, prediv;

    /* Power off PLL during setup changes */
    POWER_EnablePD(kPDRUNCFG_PD_PLL0);
    POWER_EnablePD(kPDRUNCFG_PD_PLL0_SSCG);

    pSetup->flags = flagcfg;

    /* Write PLL setup data */
    SYSCON->PLL0CTRL  = pSetup->pllctrl;
    SYSCON->PLL0NDEC  = pSetup->pllndec;
    SYSCON->PLL0NDEC  = pSetup->pllndec | (1UL << SYSCON_PLL0NDEC_NREQ_SHIFT); /* latch */
    SYSCON->PLL0PDEC  = pSetup->pllpdec;
    SYSCON->PLL0PDEC  = pSetup->pllpdec | (1UL << SYSCON_PLL0PDEC_PREQ_SHIFT); /* latch */
    SYSCON->PLL0SSCG0 = pSetup->pllsscg[0];
    SYSCON->PLL0SSCG1 = pSetup->pllsscg[1];
    SYSCON->PLL0SSCG1 =
        pSetup->pllsscg[1] | (1UL << SYSCON_PLL0SSCG1_MREQ_SHIFT) | (1UL << SYSCON_PLL0SSCG1_MD_REQ_SHIFT); /* latch */

    POWER_DisablePD(kPDRUNCFG_PD_PLL0);
    POWER_DisablePD(kPDRUNCFG_PD_PLL0_SSCG);

    if ((pSetup->flags & PLL_SETUPFLAG_WAITLOCK) != 0UL)
    {
        if ((SYSCON->PLL0SSCG1 & SYSCON_PLL0SSCG1_MDIV_EXT_MASK) != 0UL) /* normal mode */
        {
            inRate = CLOCK_GetPLL0InClockRate();
            prediv = findPll0PreDiv();
            /* Adjust input clock */
            clkRate = inRate / prediv;
            /* The lock signal is only reliable between fref[2] :100 kHz to 20 MHz. */
            if ((clkRate >= 100000UL) && (clkRate <= 20000000UL))
            {
                while (CLOCK_IsPLL0Locked() == false)
                {
                }
            }
            else
            {
                SDK_DelayAtLeastUs(6000U,
                                   SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY); /* software should use a 6 ms time interval
                                                                               to insure the PLL will be stable */
            }
        }
        else /* spread spectrum mode */
        {
            SDK_DelayAtLeastUs(6000U,
                               SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY); /* software should use a 6 ms time interval to
                                                                           insure the PLL will be stable */
        }
    }

    /* Update current programmed PLL rate var */
    CLOCK_GetPLL0OutFromSetupUpdate(pSetup);

    /* System voltage adjustment, occurs prior to setting main system clock */
    if ((pSetup->flags & PLL_SETUPFLAG_ADGVOLT) != 0UL)
    {
        POWER_SetVoltageForFreq(s_Pll0_Freq);
    }

    return kStatus_PLL_Success;
}

/* Setup PLL Frequency from pre-calculated value */
/**
 * brief Set PLL0 output from PLL setup structure (precise frequency)
 * param pSetup  : Pointer to populated PLL setup structure
 * return    kStatus_PLL_Success on success, or PLL setup error code
 * note  This function will power off the PLL, setup the PLL with the
 * new setup data, and then optionally powerup the PLL, wait for PLL lock,
 * and adjust system voltages to the new PLL rate. The function will not
 * alter any source clocks (ie, main systen clock) that may use the PLL,
 * so these should be setup prior to and after exiting the function.
 */
pll_error_t CLOCK_SetPLL0Freq(const pll_setup_t *pSetup)
{
    uint32_t inRate, clkRate, prediv;
    /* Power off PLL during setup changes */
    POWER_EnablePD(kPDRUNCFG_PD_PLL0);
    POWER_EnablePD(kPDRUNCFG_PD_PLL0_SSCG);

    /* Write PLL setup data */
    SYSCON->PLL0CTRL  = pSetup->pllctrl;
    SYSCON->PLL0NDEC  = pSetup->pllndec;
    SYSCON->PLL0NDEC  = pSetup->pllndec | (1UL << SYSCON_PLL0NDEC_NREQ_SHIFT); /* latch */
    SYSCON->PLL0PDEC  = pSetup->pllpdec;
    SYSCON->PLL0PDEC  = pSetup->pllpdec | (1UL << SYSCON_PLL0PDEC_PREQ_SHIFT); /* latch */
    SYSCON->PLL0SSCG0 = pSetup->pllsscg[0];
    SYSCON->PLL0SSCG1 = pSetup->pllsscg[1];
    SYSCON->PLL0SSCG1 =
        pSetup->pllsscg[1] | (1UL << SYSCON_PLL0SSCG1_MD_REQ_SHIFT) | (1UL << SYSCON_PLL0SSCG1_MREQ_SHIFT); /* latch */

    POWER_DisablePD(kPDRUNCFG_PD_PLL0);
    POWER_DisablePD(kPDRUNCFG_PD_PLL0_SSCG);

    if ((pSetup->flags & PLL_SETUPFLAG_WAITLOCK) != 0UL)
    {
        if ((SYSCON->PLL0SSCG1 & SYSCON_PLL0SSCG1_MDIV_EXT_MASK) != 0UL) /* normal mode */
        {
            inRate = CLOCK_GetPLL0InClockRate();
            prediv = findPll0PreDiv();
            /* Adjust input clock */
            clkRate = inRate / prediv;
            /* The lock signal is only reliable between fref[2] :100 kHz to 20 MHz. */
            if ((clkRate >= 100000UL) && (clkRate <= 20000000UL))
            {
                while (CLOCK_IsPLL0Locked() == false)
                {
                }
            }
            else
            {
                SDK_DelayAtLeastUs(6000U,
                                   SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY); /* software should use a 6 ms time interval
                                                                               to insure the PLL will be stable */
            }
        }
        else /* spread spectrum mode */
        {
            SDK_DelayAtLeastUs(6000U,
                               SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY); /* software should use a 6 ms time interval to
                                                                           insure the PLL will be stable */
        }
    }

    /* Update current programmed PLL rate var */
    s_Pll0_Freq = pSetup->pllRate;

    return kStatus_PLL_Success;
}

/* Setup PLL1 Frequency from pre-calculated value */
/**
 * brief Set PLL1 output from PLL setup structure (precise frequency)
 * param pSetup  : Pointer to populated PLL setup structure
 * return    kStatus_PLL_Success on success, or PLL setup error code
 * note  This function will power off the PLL, setup the PLL with the
 * new setup data, and then optionally powerup the PLL, wait for PLL lock,
 * and adjust system voltages to the new PLL rate. The function will not
 * alter any source clocks (ie, main systen clock) that may use the PLL,
 * so these should be setup prior to and after exiting the function.
 */
pll_error_t CLOCK_SetPLL1Freq(const pll_setup_t *pSetup)
{
    uint32_t inRate, clkRate, prediv;
    /* Power off PLL during setup changes */
    POWER_EnablePD(kPDRUNCFG_PD_PLL1);

    /* Write PLL setup data */
    SYSCON->PLL1CTRL = pSetup->pllctrl;
    SYSCON->PLL1NDEC = pSetup->pllndec;
    SYSCON->PLL1NDEC = pSetup->pllndec | (1UL << SYSCON_PLL1NDEC_NREQ_SHIFT); /* latch */
    SYSCON->PLL1PDEC = pSetup->pllpdec;
    SYSCON->PLL1PDEC = pSetup->pllpdec | (1UL << SYSCON_PLL1PDEC_PREQ_SHIFT); /* latch */
    SYSCON->PLL1MDEC = pSetup->pllmdec;
    SYSCON->PLL1MDEC = pSetup->pllmdec | (1UL << SYSCON_PLL1MDEC_MREQ_SHIFT); /* latch */

    POWER_DisablePD(kPDRUNCFG_PD_PLL1);

    if ((pSetup->flags & PLL_SETUPFLAG_WAITLOCK) != 0UL)
    {
        inRate = CLOCK_GetPLL1InClockRate();
        prediv = findPll1PreDiv();
        /* Adjust input clock */
        clkRate = inRate / prediv;
        /* The lock signal is only reliable between fref[2] :100 kHz to 20 MHz. */
        if ((clkRate >= 100000UL) && (clkRate <= 20000000UL))
        {
            while (CLOCK_IsPLL1Locked() == false)
            {
            }
        }
        else
        {
            SDK_DelayAtLeastUs(6000U,
                               SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY); /* software should use a 6 ms time interval to
                                                                           insure the PLL will be stable */
        }
    }

    /* Update current programmed PLL rate var */
    s_Pll1_Freq = pSetup->pllRate;

    return kStatus_PLL_Success;
}

/* Set PLL0 clock based on the input frequency and multiplier */
/*! brief    Set PLL0 output based on the multiplier and input frequency
 * param multiply_by : multiplier
 * param input_freq  : Clock input frequency of the PLL
 * return    Nothing
 * note  Unlike the Chip_Clock_SetupSystemPLLPrec() function, this
 * function does not disable or enable PLL power, wait for PLL lock,
 * or adjust system voltages. These must be done in the application.
 * The function will not alter any source clocks (ie, main systen clock)
 * that may use the PLL, so these should be setup prior to and after
 * exiting the function.
 */
void CLOCK_SetupPLL0Mult(uint32_t multiply_by, uint32_t input_freq)
{
    uint32_t cco_freq = input_freq * multiply_by;
    uint32_t pdec     = 1U;
    uint32_t selr;
    uint32_t seli;
    uint32_t selp;
    uint32_t mdec, ndec;

    while (cco_freq < 275000000U)
    {
        multiply_by <<= 1U; /* double value in each iteration */
        pdec <<= 1U;        /* correspondingly double pdec to cancel effect of double msel */
        cco_freq = input_freq * multiply_by;
    }

    selr = 0U;

    if (multiply_by >= 8000UL)
    {
        seli = 1UL;
    }
    else if (multiply_by >= 122UL)
    {
        seli = (uint32_t)(8000UL / multiply_by); /*floor(8000/M) */
    }
    else
    {
        seli = 2UL * ((uint32_t)(multiply_by / 4UL)) + 3UL; /* 2*floor(M/4) + 3 */
    }

    if (seli >= 63U)
    {
        seli = 63U;
    }

    {
        selp = 31U;
    }

    if (pdec > 1U)
    {
        pdec = pdec / 2U; /* Account for minus 1 encoding */
                          /* Translate P value */
    }

    mdec = (uint32_t)PLL_SSCG1_MDEC_VAL_SET(multiply_by);
    ndec = 0x1U; /* pre divide by 1 (hardcoded) */

    SYSCON->PLL0CTRL = SYSCON_PLL0CTRL_CLKEN_MASK | SYSCON_PLL0CTRL_BYPASSPOSTDIV(0) |
                       SYSCON_PLL0CTRL_BYPASSPOSTDIV2(0) | (selr << SYSCON_PLL0CTRL_SELR_SHIFT) |
                       (seli << SYSCON_PLL0CTRL_SELI_SHIFT) | (selp << SYSCON_PLL0CTRL_SELP_SHIFT);
    SYSCON->PLL0PDEC = pdec | (1UL << SYSCON_PLL0PDEC_PREQ_SHIFT); /* set Pdec value and assert preq */
    SYSCON->PLL0NDEC = ndec | (1UL << SYSCON_PLL0NDEC_NREQ_SHIFT); /* set Pdec value and assert preq */
    SYSCON->PLL0SSCG1 =
        mdec | (1UL << SYSCON_PLL0SSCG1_MREQ_SHIFT); /* select non sscg MDEC value, assert mreq and select mdec value */
}

/*! @brief Enable the OSTIMER 32k clock.
 *  @return  Nothing
 */
void CLOCK_EnableOstimer32kClock(void)
{
    PMC->OSTIMERr |= PMC_OSTIMER_CLOCKENABLE_MASK;
}
