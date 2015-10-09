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

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#include "fsl_mcg_hal.h"
#include "fsl_sim_hal.h"
#include "fsl_clock_manager.h"

/*
 * README:
 * This file should provide these APIs:
 * 1. APIs to get the frequency of output clocks in Reference Manual ->
 * Chapter Clock Distribution -> Figure Clocking diagram.
 * 2. APIs for IP modules listed in Reference Manual -> Chapter Clock Distribution
 * -> Module clocks.
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
uint32_t g_sdhcClkInFreq[SDHC_EXT_CLK_COUNT];      /* SDHC_CLKIN       */
uint32_t g_usbClkInFreq[USB_EXT_CLK_COUNT];        /* USB_CLKIN        */
uint32_t g_ftmClkFreq[FTM_EXT_CLK_COUNT];          /* FTM_CLK0         */
uint32_t g_tpmClkFreq[TPM_EXT_CLK_COUNT];          /* TPM_CLK          */

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_SetSimConfigration
 * Description   : This funtion sets the SIM registers for clock transitiom.
 *
 *END**************************************************************************/
void CLOCK_SYS_SetSimConfigration(sim_config_t const *simConfig)
{
    CLOCK_HAL_SetOutDiv(SIM,
                        simConfig->outdiv1,
                        simConfig->outdiv2,
                        simConfig->outdiv3,
                        simConfig->outdiv4);

    CLOCK_HAL_SetPllfllSel(SIM, simConfig->pllFllSel);
    CLOCK_HAL_SetPllFllDiv(SIM, simConfig->pllflldiv, simConfig->pllfllfrac);

    CLOCK_HAL_SetExternalRefClock32kSrc(SIM, simConfig->er32kSrc);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_SetConfiguration
 * Description   : This funtion sets the system to target configuration, it
 * only sets the clock modules registers for clock mode change, but not send
 * notifications to drivers.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_SetConfiguration(clock_manager_user_config_t const* config)
{
    assert(NULL != config);

    /* Set outdiv for safe output clock frequency. */
    CLOCK_HAL_SetOutDiv(SIM, 0U, 3U, 7U, 7U);

    /* Set MCG mode. */
    CLOCK_SYS_SetMcgMode(&config->mcgConfig);

    /* Set SIM setting. */
    CLOCK_SYS_SetSimConfigration(&config->simConfig);

    /* Set OSCERCLK setting. */
    CLOCK_SYS_SetOscerConfigration(0, &config->oscerConfig);
    SystemCoreClock = CLOCK_SYS_GetCoreClockFreq();

    return kClockManagerSuccess;
}

clock_manager_error_code_t CLOCK_SYS_GetFreq(clock_names_t clockName,
                                                 uint32_t *frequency)
{
    clock_manager_error_code_t returnCode = kClockManagerSuccess;

    switch (clockName)
    {
        case kCoreClock:
        case kSystemClock:
            *frequency = CLOCK_SYS_GetCoreClockFreq();
            break;
        case kPlatformClock:
            *frequency = CLOCK_SYS_GetSystemClockFreq();
            break;
        case kBusClock:
            *frequency = CLOCK_SYS_GetBusClockFreq();
            break;
        case kFlexBusClock:
            *frequency = CLOCK_SYS_GetFlexbusFreq();
            break;
        case kFlashClock:
            *frequency = CLOCK_SYS_GetFlashClockFreq();
            break;
        case kOsc32kClock:
            *frequency = CLOCK_SYS_GetExternalRefClock32kFreq();
            break;
        case kOsc0ErClock:
            *frequency = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
            break;
        case kRtcoutClock:
            *frequency = CLOCK_SYS_GetRtcOutFreq();
            break;
        case kMcgFfClock:
            *frequency = CLOCK_SYS_GetFixedFreqClockFreq();
            break;
        case kMcgFllClock:
            *frequency = CLOCK_HAL_GetFllClk(MCG);
            break;
        case kMcgPll0Clock:
            *frequency = CLOCK_HAL_GetPll0Clk(MCG);
            break;
        case kMcgOutClock:
            *frequency = CLOCK_HAL_GetOutClk(MCG);
            break;
        case kMcgIrClock:
            *frequency = CLOCK_HAL_GetInternalRefClk(MCG);
            break;
        case kIrc48mClock:
            *frequency = CPU_INTERNAL_IRC_48M; 
            break;
        case kLpoClock:
            *frequency = CLOCK_SYS_GetLpoClockFreq();
            break;
        default:
            *frequency = 0U;
            returnCode = kClockManagerNoSuchClockName;
            break;
    }

    return returnCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetCoreClockFreq
 * Description   : Gets the core clock frequency.
 * This function gets the core clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetCoreClockFreq(void)
{
    return CLOCK_HAL_GetOutClk(MCG) / (CLOCK_HAL_GetOutDiv1(SIM) + 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetSystemClockFreq
 * Description   : Gets the system clock frequency.
 * This function gets the system clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetSystemClockFreq(void)
{
    return CLOCK_HAL_GetOutClk(MCG) / (CLOCK_HAL_GetOutDiv1(SIM) + 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetBusClockFreq
 * Description   : Gets the bus clock frequency.
 * This function gets the bus clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetBusClockFreq(void)
{
    return CLOCK_HAL_GetOutClk(MCG) / (CLOCK_HAL_GetOutDiv2(SIM) + 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetFlexbusFreq
 * Description   : Gets the clock frequency for FLEXBUS module
 * This function gets the clock frequency for FLEXBUS module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetFlexbusFreq(void)
{
    return CLOCK_HAL_GetOutClk(MCG) / (CLOCK_HAL_GetOutDiv3(SIM) + 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetFlashClockFreq
 * Description   : Gets the flash clock frequency.
 * This function gets the flash clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetFlashClockFreq(void)
{
    return CLOCK_HAL_GetOutClk(MCG) / (CLOCK_HAL_GetOutDiv4(SIM) + 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetPllFllClockFreq
 * Description   : Gets the MCGPLLCLK/MCGFLLCLK/IRC48MCLK.
 * This function gets the frequency of the MCGPLLCLK/MCGFLLCLK/IRC48MCLK.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetPllFllClockFreq(void)
{
    uint32_t freq;
    clock_pllfll_sel_t src;

    src = CLOCK_HAL_GetPllfllSel(SIM);

    switch (src)
    {
        case kClockPllFllSelFll:
            freq = CLOCK_HAL_GetFllClk(MCG);
            break;
        case kClockPllFllSelPll:
            freq = CLOCK_HAL_GetPll0Clk(MCG);
            break;
        case kClockPllFllSelIrc48M:
            freq = CPU_INTERNAL_IRC_48M;
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetPllFllDivClockFreq
 * Description   : Gets the PLL/FLL clock divided by the fractional divider.
 * This function gets the frequency of the PLL/FLL clock divided 
 * by the fractional divider configured by SIM_CLKDIV3[PLLFLLFRAC, PLLFLLDIV].
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetPllFllDivClockFreq(void)
{
    uint32_t freq;
    uint8_t pllflldiv, pllfllfrac;

    freq = CLOCK_SYS_GetPllFllClockFreq();

    CLOCK_HAL_GetPllFllDiv(SIM, &pllflldiv, &pllfllfrac);
    return freq * (pllfllfrac + 1) / (pllflldiv + 1);   
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetRtcOutFreq
 * Description   : Gets the RTC_CLKOUT frequency.
 * This function gets RTC_CLKOUT  clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetRtcOutFreq(void)
{
    if (kClockRtcoutSrc1Hz == CLOCK_SYS_GetRtcOutSrc())
    {
        return g_xtalRtcClkFreq >> 15U;
    }
    else
    {
        return g_xtalRtcClkFreq;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetExternalRefClockFreq
 * Description   : Gets the ERCLK32K clock frequency.
 * This function gets the external reference (ERCLK32K) clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetExternalRefClock32kFreq(void)
{
    clock_er32k_src_t src;
    uint32_t freq;

    src = CLOCK_HAL_GetExternalRefClock32kSrc(SIM);

    switch (src)
    {
        case kClockEr32kSrcOsc0:      /* OSC 32k clock  */
            freq = (32768U == g_xtal0ClkFreq) ? 32768U : 0U;
            break;
        case kClockEr32kSrcRtc:      /* RTC 32k clock  */
            freq = g_xtalRtcClkFreq;
            break;
        case kClockEr32kSrcLpo:         /* LPO clock      */
            freq = CLOCK_SYS_GetLpoClockFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetOsc0ExternalRefClockFreq
 * Description   : Gets OSC0ERCLK.
 * This function gets the OSC0 external reference frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetOsc0ExternalRefClockFreq(void)
{
    if (OSC_HAL_GetExternalRefClkCmd(g_oscBase[0]))
    {
        return g_xtal0ClkFreq;
    }
    else
    {
        return 0U;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetWdogFreq
 * Description   : Gets watch dog clock frequency.
 * This function gets the watch dog clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetWdogFreq(uint32_t instance, clock_wdog_src_t wdogSrc)
{
    if (kClockWdogSrcLpoClk == wdogSrc)
    {
        return CLOCK_SYS_GetLpoClockFreq();
    }
    else
    {
        return CLOCK_SYS_GetBusClockFreq();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetTraceFreq
 * Description   : Gets debug trace clock frequency.
 * This function gets the debug trace clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetTraceFreq(uint32_t instance)
{
    clock_trace_src_t src = CLOCK_HAL_GetTraceClkSrc(SIM);
    uint32_t freq;
    uint8_t tracediv, tracefrac;

    if (kClockTraceSrcMcgoutClkDiv == src)
    {
        freq = CLOCK_HAL_GetOutClk(MCG);
        CLOCK_HAL_GetTraceDiv(SIM, &tracediv, &tracefrac);
        return freq * (tracefrac + 1) / (tracediv + 1);   
    }
    else
    {
        freq = CLOCK_SYS_GetCoreClockFreq();
    }
    return freq / 2U;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetPortFilterFreq
 * Description   : Gets PORTx digital input filter clock frequency.
 * This function gets the PORTx digital input filter clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetPortFilterFreq(uint32_t instance, clock_port_filter_src_t src)
{
    if (kClockPortFilterSrcBusClk == src)
    {
        return CLOCK_SYS_GetBusClockFreq();
    }
    else
    {
        return CLOCK_SYS_GetLpoClockFreq();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetLptmrFreq
 * Description   : Gets LPTMRx pre-scaler/glitch filter clock frequency.
 * This function gets the LPTMRx pre-scaler/glitch filter clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetLptmrFreq(uint32_t instance, clock_lptmr_src_t lptmrSrc)
{
    uint32_t freq;

    switch (lptmrSrc)
    {
        case kClockLptmrSrcMcgIrClk:        /* MCG out clock  */
            freq = CLOCK_HAL_GetInternalRefClk(MCG);
            break;
        case kClockLptmrSrcLpoClk:             /* LPO clock     */
            freq = CLOCK_SYS_GetLpoClockFreq();
            break;
        case kClockLptmrSrcEr32kClk:        /* ERCLK32K clock */
            freq = CLOCK_SYS_GetExternalRefClock32kFreq();
            break;
        case kClockLptmrSrcOsc0erClk:  /* OSC0ERCLK clock */
            freq = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetTpmfFreq
 * Description   : Gets the clock frequency for TPM module.
 * This function gets the clock frequency for TPM moudle.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetTpmFreq(uint32_t instance)
{
    uint32_t freq;
    clock_tpm_src_t src;

    src = CLOCK_HAL_GetTpmSrc(SIM, instance);

    switch(src)
    {
        case kClockTpmSrcPllFllSelDiv:   /* FLL/PLL */
            freq = CLOCK_SYS_GetPllFllDivClockFreq();
            break;
        case kClockTpmSrcOsc0erClk:  /* OSCERCLK */
            freq = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
            break;
        case kClockTpmSrcMcgIrClk:   /* MCGIRCLK. */
            freq = CLOCK_HAL_GetInternalRefClk(MCG);
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetTpmExternalFreq
 * Description   : Gets the external clock frequency for TPM module.
 * This function gets the external clock frequency for TPM moudle.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetTpmExternalFreq(uint32_t instance)
{
    sim_tpm_clk_sel_t src = CLOCK_SYS_GetTpmExternalSrc(instance);

    if (kSimTpmClkSel0 == src)
    {
        return g_tpmClkFreq[0];
    }
    else
    {
        return g_tpmClkFreq[1];
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetEmvsimFreq
 * Description   : Gets the clock frequency for EMVSIM module.
 * This function gets the clock frequency for EMVSIM moudle.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetEmvsimFreq(uint32_t instance)
{
    clock_emvsim_src_t src;
    uint32_t freq;

    src = CLOCK_HAL_GetEmvsimSrc(SIM, instance);
    switch (src)
    {
        case kClockEmvsimSrcPllFllSel:
            freq = CLOCK_SYS_GetPllFllDivClockFreq();
            break;
        case kClockLpuartSrcOsc0erClk:
            freq = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
            break;
        case kClockLpuartSrcMcgIrClk:
            freq = CLOCK_HAL_GetInternalRefClk(MCG);
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetLpuartFreq
 * Description   : Gets the clock frequency for LPUART module.
 * This function gets the clock frequency for LPUART moudle.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetLpuartFreq(uint32_t instance)
{
    clock_lpuart_src_t src;
    uint32_t freq;

    src = CLOCK_HAL_GetLpuartSrc(SIM, instance);
    switch (src)
    {
        case kClockLpuartSrcPllFllSel:
            freq = CLOCK_SYS_GetPllFllDivClockFreq();
            break;
        case kClockLpuartSrcOsc0erClk:
            freq = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
            break;
        case kClockLpuartSrcMcgIrClk:
            freq = CLOCK_HAL_GetInternalRefClk(MCG);
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetFlexioFreq
 * Description   : Gets the clock frequency for FLEXIO.
 * This function gets the clock frequency for FLEXIO.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetFlexioFreq(uint32_t instance)
{
    uint32_t freq;
    clock_flexio_src_t src = CLOCK_HAL_GetFlexioSrc(SIM, instance);

    switch (src)
    {
        case kClockLpuartSrcPllFllSel:
            freq = CLOCK_SYS_GetPllFllDivClockFreq();
            break;
        case kClockFlexioSrcOsc0erClk:
            freq = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
            break;
        case kClockFlexioSrcMcgIrClk:
            freq = CLOCK_HAL_GetInternalRefClk(MCG);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetUsbfFreq
 * Description   : Gets the clock frequency for USB FS OTG module.
 * This function gets the clock frequency for USB FS OTG moudle.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetUsbfsFreq(uint32_t instance)
{
    uint8_t usbdiv, usbfrac;
    uint32_t freq;
    clock_usbfs_src_t src;

    src = CLOCK_HAL_GetUsbfsSrc(SIM, instance);

    if (kClockUsbfsSrcExt == src)
    {
        return g_usbClkInFreq[0];       /* USB_CLKIN */
    }
    else
    {
        freq = CLOCK_SYS_GetPllFllClockFreq();

        CLOCK_HAL_GetUsbfsDiv(SIM, &usbdiv, &usbfrac);
        return freq * (usbfrac + 1) / (usbdiv + 1);
    }
}


/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetSdhcFreq
 * Description   : Gets the clock frequency for SDHC module
 * This function gets the clock frequency for SDHC moudle
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetSdhcFreq(uint32_t instance)
{
    uint32_t freq;
    clock_sdhc_src_t src;

    src = CLOCK_HAL_GetSdhcSrc(SIM, instance);

    switch (src)
    {
        case kClockSdhcSrcCoreSysClk:  /* Core/system clock */
            freq = CLOCK_SYS_GetCoreClockFreq();
            break;
        case kClockSdhcSrcPllFllSel:   /* Clock selected by SOPT2[PLLFLLSEL]. */
            freq = CLOCK_SYS_GetPllFllClockFreq();
            break;
        case kClockSdhcSrcOsc0erClk:    /* OSCERCLK clock */
            freq = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
            break;
        case kClockSdhcSrcExt:         /* External bypass clock (SDHC0_CLKIN) */
            freq = g_sdhcClkInFreq[0];
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetSaiFreq
 * Description   : Gets the clock frequency for SAI module
 * This function gets the clock frequency for SAI moudle.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetSaiFreq(uint32_t instance, clock_sai_src_t saiSrc)
{
    uint32_t freq;
    switch (saiSrc)
    {
        case kClockSaiSrcPllFllSel:
            freq = CLOCK_HAL_GetPll0Clk(MCG);
            break;
        case kClockSaiSrcOsc0erClk:
            freq = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
            break;
        case kClockSaiSrcSysClk:
            freq = CLOCK_SYS_GetSystemClockFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetFtmExternalFreq
 * Description   : Gets FTM external clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetFtmExternalFreq(uint32_t instance)
{
    sim_ftm_clk_sel_t sel = SIM_HAL_GetFtmExternalClkPinMode(SIM, instance);

    if (kSimFtmClkSel0 == sel)
    {
        return g_ftmClkFreq[0];
    }
    else
    {
        return g_ftmClkFreq[1];
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetQspiFreq
 * Description   : Gets the clock frequency for QSPI module
 * This function gets the clock frequency for QSPI moudle.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetQspiFreq(uint32_t instance, clock_qspi_src_t qspiSrc)
{
    uint32_t freq;
    
    switch (qspiSrc)
    {
        case kClockQspiSrcSysClk:
            freq = CLOCK_SYS_GetSystemClockFreq();
            break;
        case kClockQspiSrcFllClk:
            freq = CLOCK_HAL_GetFllClk(MCG);
            break;
        case kClockQspiSrcPllClk:
            freq = CLOCK_HAL_GetPll0Clk(MCG);
            break;
        case kClockQspiSrcPll2xClk:
            freq = 2 * CLOCK_HAL_GetPll0Clk(MCG);
            break;
        case kClockQspiSrcIrc48M:
            freq = CPU_INTERNAL_IRC_48M;
            break;
        case kClockQspiSrcOsc0erClk:
            freq = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
            break;
        case kClockQspiSrcMcgIrClk:
            freq = CLOCK_HAL_GetInternalRefClk(MCG);
            break;       
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/* PORT instance table. */
static const sim_clock_gate_name_t portGateTable[] =
{
    kSimClockGatePortA,
    kSimClockGatePortB,
    kSimClockGatePortC,
    kSimClockGatePortD,
    kSimClockGatePortE
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnablePortClock
 * Description   : Enable the clock for PORT module
 * This function enables the clock for PORT moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_EnablePortClock(uint32_t instance)
{
    assert(instance < sizeof(portGateTable)/sizeof(portGateTable[0]));

    SIM_HAL_EnableClock(SIM, portGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisablePortClock
 * Description   : Disable the clock for PORT module
 * This function disables the clock for PORT moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_DisablePortClock(uint32_t instance)
{
    assert(instance < sizeof(portGateTable)/sizeof(portGateTable[0]));

    SIM_HAL_DisableClock(SIM, portGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetPortGateCmd
 * Description   : Get the the clock gate state for PORT module
 * This function will get the clock gate state for PORT moudle.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetPortGateCmd(uint32_t instance)
{
    assert(instance < sizeof(portGateTable)/sizeof(portGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, portGateTable[instance]);
}

/* FTM instance table. */
static const sim_clock_gate_name_t ftmGateTable[] =
{
    kSimClockGateFtm0,
    kSimClockGateFtm1,
    kSimClockGateFtm2,
    kSimClockGateFtm3
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableFtmClock
 * Description   : Enable the clock for FTM module
 * This function enables the clock for FTM moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_EnableFtmClock(uint32_t instance)
{
    assert(instance < sizeof(ftmGateTable)/sizeof(ftmGateTable[0]));

    SIM_HAL_EnableClock(SIM, ftmGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisableFtmClock
 * Description   : Disable the clock for FTM module
 * This function disables the clock for FTM moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_DisableFtmClock(uint32_t instance)
{
    assert(instance < sizeof(ftmGateTable)/sizeof(ftmGateTable[0]));

    SIM_HAL_DisableClock(SIM, ftmGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetFtmGateCmd
 * Description   : Get the the clock gate state for FTM module
 * This function will get the clock gate state for FTM moudle.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetFtmGateCmd(uint32_t instance)
{
    assert(instance < sizeof(ftmGateTable)/sizeof(ftmGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, ftmGateTable[instance]);
}

/* SPI instance table. */
static const sim_clock_gate_name_t spiGateTable[] =
{
    kSimClockGateSpi0,
    kSimClockGateSpi1,
    kSimClockGateSpi2
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableSpiClock
 * Description   : Enable the clock for SPI module
 * This function enables the clock for SPI moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_EnableSpiClock(uint32_t instance)
{
    assert(instance < sizeof(spiGateTable)/sizeof(spiGateTable[0]));

    SIM_HAL_EnableClock(SIM, spiGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisableSpiClock
 * Description   : Disable the clock for SPI module
 * This function disables the clock for SPI moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_DisableSpiClock(uint32_t instance)
{
    assert(instance < sizeof(spiGateTable)/sizeof(spiGateTable[0]));

    SIM_HAL_DisableClock(SIM, spiGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetSpiGateCmd
 * Description   : Get the the clock gate state for SPI module
 * This function will get the clock gate state for SPI moudle.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetSpiGateCmd(uint32_t instance)
{
    assert(instance < sizeof(spiGateTable)/sizeof(spiGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, spiGateTable[instance]);
}

/* I2C instance table. */
static const sim_clock_gate_name_t i2cGateTable[] =
{
    kSimClockGateI2c0,
    kSimClockGateI2c1,
    kSimClockGateI2c2,
    kSimClockGateI2c3,
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableI2cClock
 * Description   : Enable the clock for I2C module
 * This function enables the clock for I2C moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_EnableI2cClock(uint32_t instance)
{
    assert(instance < sizeof(i2cGateTable)/sizeof(i2cGateTable[0]));

    SIM_HAL_EnableClock(SIM, i2cGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisableI2cClock
 * Description   : Disable the clock for I2C module
 * This function disables the clock for I2C moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_DisableI2cClock(uint32_t instance)
{
    assert(instance < sizeof(i2cGateTable)/sizeof(i2cGateTable[0]));

    SIM_HAL_DisableClock(SIM, i2cGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetI2cGateCmd
 * Description   : Get the the clock gate state for I2C module
 * This function will get the clock gate state for I2C moudle.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetI2cGateCmd(uint32_t instance)
{
    assert(instance < sizeof(i2cGateTable)/sizeof(i2cGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, i2cGateTable[instance]);
}

/* Lpuart instance table. */
static const sim_clock_gate_name_t lpuartGateTable[] =
{
    kSimClockGateLpuart0,
    kSimClockGateLpuart1,
    kSimClockGateLpuart2,
    kSimClockGateLpuart3,
    kSimClockGateLpuart4
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableLpuartClock
 * Description   : Enable the clock for LPUART module
 * This function enables the clock for LPUART moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_EnableLpuartClock(uint32_t instance)
{
    assert(instance < sizeof(lpuartGateTable)/sizeof(lpuartGateTable[0]));

    SIM_HAL_EnableClock(SIM, lpuartGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisableLpuartClock
 * Description   : Disable the clock for LPUART module
 * This function enables the clock for LPUART moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_DisableLpuartClock(uint32_t instance)
{
    assert(instance < sizeof(lpuartGateTable)/sizeof(lpuartGateTable[0]));

    SIM_HAL_DisableClock(SIM, lpuartGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetLpuartGateCmd
 * Description   : Get the the clock gate state for LPUART module
 * This function will get the clock gate state for LPUART moudle.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetLpuartGateCmd(uint32_t instance)
{
    assert(instance < sizeof(lpuartGateTable)/sizeof(lpuartGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, lpuartGateTable[instance]);
}

/* Emvsim instance table. */
static const sim_clock_gate_name_t emvsimGateTable[] =
{
    kSimClockGateEmvsim0,
    kSimClockGateEmvsim1
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableEmvsimClock
 * Description   : Enable the clock for EMVSIM module
 * This function enables the clock for EMVSIM moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_EnableEmvsimClock(uint32_t instance)
{
    assert(instance < sizeof(emvsimGateTable)/sizeof(emvsimGateTable[0]));

    SIM_HAL_EnableClock(SIM, emvsimGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisableEmvsimClock
 * Description   : Disable the clock for EMVSIM module
 * This function enables the clock for EMVSIM moudule
 *
 *END**************************************************************************/
void CLOCK_SYS_DisableEmvsimClock(uint32_t instance)
{
    assert(instance < sizeof(emvsimGateTable)/sizeof(emvsimGateTable[0]));

    SIM_HAL_DisableClock(SIM, emvsimGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetEmvsimGateCmd
 * Description   : Get the the clock gate state for EMVSIM module
 * This function will get the clock gate state for EMVSIM moudle.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetEmvsimGateCmd(uint32_t instance)
{
    assert(instance < sizeof(emvsimGateTable)/sizeof(emvsimGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, emvsimGateTable[instance]);
}


/* TPM instance table. */
static const sim_clock_gate_name_t tpmGateTable[] =
{
    kSimClockGateTpm1,
    kSimClockGateTpm2
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableTpmClock
 * Description   : Enable the clock for TPM module
 * This function enables the clock for TPM moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_EnableTpmClock(uint32_t instance)
{
    assert(instance < sizeof(tpmGateTable)/sizeof(tpmGateTable[0]));

    SIM_HAL_EnableClock(SIM, tpmGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisableTpmClock
 * Description   : Disable the clock for TPM module
 * This function disables the clock for TPM moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_DisableTpmClock(uint32_t instance)
{
    assert(instance < sizeof(tpmGateTable)/sizeof(tpmGateTable[0]));

    SIM_HAL_DisableClock(SIM, tpmGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetTpmGateCmd
 * Description   : Get the the clock gate state for TPM module
 * This function will get the clock gate state for TPM moudle.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetTpmGateCmd(uint32_t instance)
{
    assert(instance < sizeof(tpmGateTable)/sizeof(tpmGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, tpmGateTable[instance]);
}

/* Lptmr instance table. */
static const sim_clock_gate_name_t lptmrGateTable[] =
{
    kSimClockGateLptmr0,
    kSimClockGateLptmr1
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableLptmrClock
 * Description   : Enable the clock for LPTMR module
 * This function enables the clock for LPTMR moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_EnableLptmrClock(uint32_t instance)
{
    assert(instance < sizeof(lptmrGateTable)/sizeof(lptmrGateTable[0]));

    SIM_HAL_EnableClock(SIM, lptmrGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisableLptmrClock
 * Description   : Disable the clock for LPTMR module
 * This function enables the clock for LPTMR moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_DisableLptmrClock(uint32_t instance)
{
    assert(instance < sizeof(lptmrGateTable)/sizeof(lptmrGateTable[0]));

    SIM_HAL_DisableClock(SIM, lptmrGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetLptmrGateCmd
 * Description   : Get the the clock gate state for LPTMR module
 * This function will get the clock gate state for LPTMR moudle.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetLptmrGateCmd(uint32_t instance)
{
    assert(instance < sizeof(lptmrGateTable)/sizeof(lptmrGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, lptmrGateTable[instance]);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
