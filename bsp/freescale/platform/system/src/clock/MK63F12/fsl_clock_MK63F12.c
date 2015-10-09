/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
uint32_t g_enet1588ClkInFreq[ENET_EXT_CLK_COUNT];  /* ENET_1588_CLKIN  */
uint32_t g_sdhcClkInFreq[SDHC_EXT_CLK_COUNT];      /* SDHC_CLKIN       */
uint32_t g_usbClkInFreq[USB_EXT_CLK_COUNT];        /* USB_CLKIN        */
uint32_t g_ftmClkFreq[FTM_EXT_CLK_COUNT];          /* FTM_CLK0         */

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
    CLOCK_HAL_SetOutDiv(SIM, 0U, 1U, 2U, 4U);

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
        case kSystickClock:
            *frequency = CLOCK_SYS_GetSystickFreq();
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
 * Description   : Gets the systen clock frequency.
 * This function gets the systen clock frequency.
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
 * This function gets the clock frequency for FLEXBUS moudle.
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

    if (kClockTraceSrcMcgoutClk == src)
    {
        return CLOCK_HAL_GetOutClk(MCG) / 2U;
    }
    else
    {
        return CLOCK_SYS_GetCoreClockFreq() / 2U;
    }
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
 * Description   : Gets LPTMRx prescaler/glitch filter clock frequency.
 * This function gets the LPTMRx prescaler/glitch filter clock frequency.
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
        case kClockLptmrSrcOsc0erClk:        /* OSCERCLK clock */
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
 * Function Name : CLOCK_SYS_GetEnetRmiiFreq
 * Description   : Gets the clock frequency for ENET module RMII clock.
 * This function gets the clock frequency for ENET moudle RMII clock.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetEnetRmiiFreq(uint32_t instance)
{
    /* get the sim clock source setting*/
    if (CLOCK_HAL_GetRmiiSrc(SIM, instance) == kClockRmiiSrcExtalClk)
    {
        return CLOCK_SYS_GetOsc0ExternalRefClockFreq();   /* OSCERCLK */
    }
    else
    {
        return g_enet1588ClkInFreq[0];      /* ENET_1588_CLKIN */
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetEnetTimeStampFreq
 * Description   : Gets the clock frequency for ENET module TIME clock.
 * This function gets the clock frequency for ENET moudle TIME clock.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetEnetTimeStampFreq(uint32_t instance)
{
    uint32_t freq;
    clock_time_src_t src;

    src = CLOCK_HAL_GetTimeSrc(SIM, instance);

    switch(src)
    {
        case kClockTimeSrcCoreSysClk: /* Core/System clock. */
            freq = CLOCK_SYS_GetCoreClockFreq();
            break;
        case kClockTimeSrcPllFllSel:  /* FLL/PLL/IRC48M. */
            freq = CLOCK_SYS_GetPllFllClockFreq();
            break;
        case kClockTimeSrcOsc0erClk:   /* OSCERCLK. */
            freq = CLOCK_SYS_GetOsc0ExternalRefClockFreq();
            break;
        case kClockTimeSrcExt:        /* ENET 1588 clock in. */
            freq = g_enet1588ClkInFreq[0];
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
 * Function Name : CLOCK_SYS_GetFlexcanFreq
 * Description   : Gets FLEXCAN clock frequency.
 * This function gets the FLEXCAN clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetFlexcanFreq(uint32_t instance, clock_flexcan_src_t flexcanSrc)
{
    if (kClockFlexcanSrcOsc0erClk == flexcanSrc)
    {
        return CLOCK_SYS_GetOsc0ExternalRefClockFreq();
    }
    else
    {
        return CLOCK_SYS_GetBusClockFreq();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetUartFreq
 * Description   : Gets the clock frequency for UART module.
 * This function gets the clock frequency for UART moudle.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetUartFreq(uint32_t instance)
{
    uint32_t freq;

    switch (instance)
    {
        case 0:
        case 1:
            freq = CLOCK_SYS_GetSystemClockFreq();
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            freq = CLOCK_SYS_GetBusClockFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
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
        case kClockSaiSrcPllClk:
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

/* ADC instance table. */
static const sim_clock_gate_name_t adcGateTable[] =
{
    kSimClockGateAdc0,
    kSimClockGateAdc1
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableAdcClock
 * Description   : Enable the clock for ADC module
 * This function enables the clock for ADC moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_EnableAdcClock(uint32_t instance)
{
    assert(instance < sizeof(adcGateTable)/sizeof(adcGateTable[0]));

    SIM_HAL_EnableClock(SIM, adcGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisableAdcClock
 * Description   : Disable the clock for ADC module
 * This function disables the clock for ADC moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_DisableAdcClock(uint32_t instance)
{
    assert(instance < sizeof(adcGateTable)/sizeof(adcGateTable[0]));

    SIM_HAL_DisableClock(SIM, adcGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetAdcGateCmd
 * Description   : Get the the clock gate state for ADC module
 * This function will get the clock gate state for ADC moudle.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetAdcGateCmd(uint32_t instance)
{
    assert(instance < sizeof(adcGateTable)/sizeof(adcGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, adcGateTable[instance]);
}

/* DAC instance table. */
static const sim_clock_gate_name_t dacGateTable[] =
{
    kSimClockGateDac0,
    kSimClockGateDac1
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableDacClock
 * Description   : Enable the clock for DAC module
 * This function enables the clock for DAC moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_EnableDacClock(uint32_t instance)
{
    assert(instance < sizeof(dacGateTable)/sizeof(dacGateTable[0]));

    SIM_HAL_EnableClock(SIM, dacGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisableDacClock
 * Description   : Disable the clock for DAC module
 * This function disables the clock for DAC moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_DisableDacClock(uint32_t instance)
{
    assert(instance < sizeof(dacGateTable)/sizeof(dacGateTable[0]));

    SIM_HAL_DisableClock(SIM, dacGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetDacGateCmd
 * Description   : Get the the clock gate state for DAC module
 * This function will get the clock gate state for DAC moudle.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetDacGateCmd(uint32_t instance)
{
    assert(instance < sizeof(dacGateTable)/sizeof(dacGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, dacGateTable[instance]);
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
    kSimClockGateI2c2
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

/* Uart instance table. */
static const sim_clock_gate_name_t uartGateTable[] =
{
    kSimClockGateUart0,
    kSimClockGateUart1,
    kSimClockGateUart2,
    kSimClockGateUart3,
    kSimClockGateUart4,
    kSimClockGateUart5
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableUartClock
 * Description   : Enable the clock for UART module
 * This function enables the clock for UART moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_EnableUartClock(uint32_t instance)
{
    assert(instance < sizeof(uartGateTable)/sizeof(uartGateTable[0]));

    SIM_HAL_EnableClock(SIM, uartGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisableUartClock
 * Description   : Disable the clock for UART module
 * This function enables the clock for UART moudle
 *
 *END**************************************************************************/
void CLOCK_SYS_DisableUartClock(uint32_t instance)
{
    assert(instance < sizeof(uartGateTable)/sizeof(uartGateTable[0]));

    SIM_HAL_DisableClock(SIM, uartGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetUartGateCmd
 * Description   : Get the the clock gate state for UART module
 * This function will get the clock gate state for UART moudle.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetUartGateCmd(uint32_t instance)
{
    assert(instance < sizeof(uartGateTable)/sizeof(uartGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, uartGateTable[instance]);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
