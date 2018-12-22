/*
** ###################################################################
**     Processors:          LPC54608J512BD208
**                          LPC54608J512ET180
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          MCUXpresso Compiler
**
**     Reference manual:    LPC54S60x/LPC5460x User manual Rev.0.9  7 Nov 2016
**     Version:             rev. 1.1, 2016-11-25
**     Build:               b170214
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of the copyright holder nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2016-08-12)
**         Initial version.
**     - rev. 1.1 (2016-11-25)
**         Update CANFD and Classic CAN register.
**         Add MAC TIMERSTAMP registers.
**
** ###################################################################
*/

/*!
 * @file LPC54608
 * @version 1.1
 * @date 2016-11-25
 * @brief Device specific configuration file for LPC54608 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"

#define NVALMAX (0x100)
#define PVALMAX (0x20)
#define MVALMAX (0x8000)
#define PLL_MDEC_VAL_P (0)                                       /* MDEC is in bits  16:0 */
#define PLL_MDEC_VAL_M (0x1FFFFUL << PLL_MDEC_VAL_P)
#define PLL_NDEC_VAL_P (0)                                       /* NDEC is in bits  9:0 */
#define PLL_NDEC_VAL_M (0x3FFUL << PLL_NDEC_VAL_P)
#define PLL_PDEC_VAL_P (0)                                       /* PDEC is in bits  6:0 */
#define PLL_PDEC_VAL_M (0x7FUL << PLL_PDEC_VAL_P)

extern void *__Vectors;

static const uint8_t wdtFreqLookup[32] = {0, 8, 12, 15, 18, 20, 24, 26, 28, 30, 32, 34, 36, 38, 40, 41, 42, 44, 45, 46,
                                            48, 49, 50, 52, 53, 54, 56, 57, 58, 59, 60, 61};
/* Get WATCH DOG Clk */
static uint32_t getWdtOscFreq(void)
{
    uint8_t freq_sel, div_sel;
    if (SYSCON->PDRUNCFG[0] & SYSCON_PDRUNCFG_PDEN_WDT_OSC_MASK)
    {
        return 0U;
    }
    else
    {
        div_sel = ((SYSCON->WDTOSCCTRL & 0x1f) + 1) << 1;
        freq_sel = wdtFreqLookup[((SYSCON->WDTOSCCTRL & SYSCON_WDTOSCCTRL_FREQSEL_MASK) >> SYSCON_WDTOSCCTRL_FREQSEL_SHIFT)];
        return ((uint32_t) freq_sel * 50000U)/((uint32_t)div_sel);
    }
}
/* Find decoded N value for raw NDEC value */
static uint32_t pllDecodeN(uint32_t NDEC)
{
    uint32_t n, x, i;

    /* Find NDec */
    switch (NDEC)
    {
        case 0x3FF:
            n = 0;
            break;
        case 0x302:
            n = 1;
            break;
        case 0x202:
            n = 2;
            break;
        default:
            x = 0x080;
            n = 0xFFFFFFFFU;
            for (i = NVALMAX; ((i >= 3) && (n == 0xFFFFFFFFU)); i--)
            {
                x = (((x ^ (x >> 2) ^ (x >> 3) ^ (x >> 4)) & 1) << 7) | ((x >> 1) & 0x7F);
                if ((x & (PLL_NDEC_VAL_M >> PLL_NDEC_VAL_P)) == NDEC)
                {
                    /* Decoded value of NDEC */
                    n = i;
                }
            }
            break;
    }
    return n;
}

/* Find decoded P value for raw PDEC value */
static uint32_t pllDecodeP(uint32_t PDEC)
{
    uint32_t p, x, i;
    /* Find PDec */
    switch (PDEC)
    {
        case 0x7F:
            p = 0;
            break;
        case 0x62:
            p = 1;
            break;
        case 0x42:
            p = 2;
            break;
        default:
            x = 0x10;
            p = 0xFFFFFFFFU;
            for (i = PVALMAX; ((i >= 3) && (p == 0xFFFFFFFFU)); i--)
            {
                x = (((x ^ (x >> 2)) & 1) << 4) | ((x >> 1) & 0xFU);
                if ((x & (PLL_PDEC_VAL_M >> PLL_PDEC_VAL_P)) == PDEC)
                {
                    /* Decoded value of PDEC */
                    p = i;
                }
            }
            break;
    }
    return p;
}

/* Find decoded M value for raw MDEC value */
static uint32_t pllDecodeM(uint32_t MDEC)
{
    uint32_t m, i, x;

    /* Find MDec */
    switch (MDEC)
    {
        case 0x1FFFF:
            m = 0;
            break;
        case 0x18003:
            m = 1;
            break;
        case 0x10003:
            m = 2;
            break;
        default:
            x = 0x04000;
            m = 0xFFFFFFFFU;
            for (i = MVALMAX; ((i >= 3) && (m == 0xFFFFFFFFU)); i--)
            {
                x = (((x ^ (x >> 1)) & 1) << 14) | ((x >> 1) & 0x3FFFU);
                if ((x & (PLL_MDEC_VAL_M >> PLL_MDEC_VAL_P)) == MDEC)
                {
                    /* Decoded value of MDEC */
                    m = i;
                }
            }
            break;
    }
    return m;
}

/* Get predivider (N) from PLL NDEC setting */
static uint32_t findPllPreDiv(uint32_t ctrlReg, uint32_t nDecReg)
{
    uint32_t preDiv = 1;

    /* Direct input is not used? */
    if ((ctrlReg & SYSCON_SYSPLLCTRL_DIRECTI_MASK) == 0)
    {
        /* Decode NDEC value to get (N) pre divider */
        preDiv = pllDecodeN(nDecReg & 0x3FF);
        if (preDiv == 0)
        {
            preDiv = 1;
        }
    }
    /* Adjusted by 1, directi is used to bypass */
    return preDiv;
}

/* Get postdivider (P) from PLL PDEC setting */
static uint32_t findPllPostDiv(uint32_t ctrlReg, uint32_t pDecReg)
{
    uint32_t postDiv = 1;

    /* Direct input is not used? */
    if ((ctrlReg & SYSCON_SYSPLLCTRL_DIRECTO_MASK) == 0)
    {
        /* Decode PDEC value to get (P) post divider */
        postDiv = 2 * pllDecodeP(pDecReg & 0x7F);
        if (postDiv == 0)
        {
            postDiv = 2;
        }
    }
    /* Adjusted by 1, directo is used to bypass */
    return postDiv;
}

/* Get multiplier (M) from PLL MDEC and BYPASS_FBDIV2 settings */
static uint32_t findPllMMult(uint32_t ctrlReg, uint32_t mDecReg)
{
    uint32_t mMult = 1;

    /* Decode MDEC value to get (M) multiplier */
    mMult = pllDecodeM(mDecReg & 0x1FFFF);
    if (mMult == 0)
    {
        mMult = 1;
    }
    return mMult;
}



/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

#if defined(__MCUXPRESSO)
    extern void(*const g_pfnVectors[]) (void);
    SCB->VTOR = (uint32_t) &g_pfnVectors;
#else
    extern void *__Vectors;
    SCB->VTOR = (uint32_t) &__Vectors;
#endif
    SYSCON->ARMTRACECLKDIV = 0;
/* Optionally enable RAM banks that may be off by default at reset */
#if !defined(DONT_ENABLE_DISABLED_RAMBANKS)
  SYSCON->AHBCLKCTRLSET[0] = SYSCON_AHBCLKCTRL_SRAM1_MASK | SYSCON_AHBCLKCTRL_SRAM2_MASK | SYSCON_AHBCLKCTRL_SRAM3_MASK;
#endif
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {
uint32_t clkRate = 0;
    uint32_t prediv, postdiv;
    uint64_t workRate;

    switch (SYSCON->MAINCLKSELB & SYSCON_MAINCLKSELB_SEL_MASK)
    {
        case 0x00: /* MAINCLKSELA clock (main_clk_a)*/
            switch (SYSCON->MAINCLKSELA & SYSCON_MAINCLKSELA_SEL_MASK)
            {
                case 0x00: /* FRO 12 MHz (fro_12m) */
                    clkRate = CLK_FRO_12MHZ;
                    break;
                case 0x01: /* CLKIN (clk_in) */
                    clkRate = CLK_CLK_IN;
                    break;
                case 0x02: /* Watchdog oscillator (wdt_clk) */
                    clkRate = getWdtOscFreq();
                    break;
                default: /* = 0x03 = FRO 96 or 48 MHz (fro_hf) */
                    if (SYSCON->FROCTRL & SYSCON_FROCTRL_SEL_MASK)
                    {
                        clkRate = CLK_FRO_96MHZ;
                    }
                    else
                    {
                        clkRate = CLK_FRO_48MHZ;
                    }
                    break;
            }
            break;
        case 0x02: /* System PLL clock (pll_clk)*/
            switch (SYSCON->SYSPLLCLKSEL & SYSCON_SYSPLLCLKSEL_SEL_MASK)
            {
                case 0x00: /* FRO 12 MHz (fro_12m) */
                    clkRate = CLK_FRO_12MHZ;
                    break;
                case 0x01: /* CLKIN (clk_in) */
                    clkRate = CLK_CLK_IN;
                    break;
                case 0x02: /* Watchdog oscillator (wdt_clk) */
                    clkRate = getWdtOscFreq();
                    break;
                case 0x03: /* RTC oscillator 32 kHz output (32k_clk) */
                    clkRate = CLK_RTC_32K_CLK;
                    break;
                default:
                    break;
            }
            if ((SYSCON->SYSPLLCTRL & SYSCON_SYSPLLCTRL_BYPASS_MASK) == 0)
            {
                /* PLL is not in bypass mode, get pre-divider, post-divider, and M divider */
                prediv = findPllPreDiv(SYSCON->SYSPLLCTRL, SYSCON->SYSPLLNDEC);
                postdiv = findPllPostDiv(SYSCON->SYSPLLCTRL, SYSCON->SYSPLLPDEC);
                /* Adjust input clock */
                clkRate = clkRate / prediv;

                /* MDEC used for rate */
                workRate = (uint64_t)clkRate * (uint64_t)findPllMMult(SYSCON->SYSPLLCTRL, SYSCON->SYSPLLMDEC);
                clkRate = workRate / ((uint64_t)postdiv);
                clkRate = workRate * 2; /* PLL CCO output is divided by 2 before to M-Divider */
            }
            break;
        case 0x03: /* RTC oscillator 32 kHz output (32k_clk) */
            clkRate = CLK_RTC_32K_CLK;
            break;
        default:
            break;
    }
    SystemCoreClock = clkRate / ((SYSCON->AHBCLKDIV & 0xFF) + 1);
}
