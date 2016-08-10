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
#include "fsl_device_registers.h"
#include "fsl_sim_hal.h"
#include "fsl_mcg_hal.h"
#include "fsl_clock_manager.h"
#include "fsl_os_abstraction.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief AFE_CLK    */
uint32_t g_afeClkFreq[AFE_EXT_CLK_COUNT];

extern RTC_Type * const g_irtcBase[RTC_INSTANCE_COUNT];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_SetSimConfigration
 * Description   : This function sets the SIM registers for clock transition.
 *
 *END**************************************************************************/
void CLOCK_SYS_SetSimConfigration(sim_config_t const *simConfig)
{
    CLOCK_HAL_SetSysDiv(SIM, simConfig->sysdiv);
    CLOCK_HAL_SetBusDiv(SIM, simConfig->busdiv);
    CLOCK_HAL_SetFlashClkMode(SIM, simConfig->flashclkmode);

    CLOCK_HAL_SetPllfllSel(SIM, simConfig->pllFllSel);

    CLOCK_HAL_SetExternalRefClock32kSrc(SIM, simConfig->er32kSrc);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_SetConfiguration
 * Description   : This function sets the system to target configuration, it
 * only sets the clock modules registers for clock mode change, but not send
 * notifications to drivers.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_SetConfiguration(clock_manager_user_config_t const* config)
{
    assert(NULL != config);

    /* Set outdiv for safe output clock frequency. */
    CLOCK_SYS_SetSysDiv(0);
    CLOCK_SYS_SetBusDiv(3);
    CLOCK_SYS_SetFlashClockMode(0);

    /* Set MCG mode. */
    CLOCK_SYS_SetMcgMode(&config->mcgConfig);

    /* Set SIM setting. */
    CLOCK_SYS_SetSimConfigration(&config->simConfig);

    /* Set OSCERCLK setting. */
    CLOCK_SYS_SetOscerConfigration(0, &config->oscerConfig);
    SystemCoreClock = CLOCK_SYS_GetCoreClockFreq();
	
    return kClockManagerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetFreq
 * Description   : This function gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_names_t.
 *
 * The MCG must be properly configured before using this function. See
 * the reference manual for supported clock names for different chip families.
 * The returned value is in Hertz. If it cannot find the clock name
 * or the name is not supported for a specific chip family, it returns an
 * error.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_GetFreq(clock_names_t clockName,
                                                  uint32_t *frequency)
{
    clock_manager_error_code_t returnCode = kClockManagerSuccess;

    switch (clockName)
    {
        case kCoreClock:
        case kSystemClock:
        case kPlatformClock:
            *frequency = CLOCK_SYS_GetSystemClockFreq();
            break;
        case kBusClock:
            *frequency = CLOCK_SYS_GetBusClockFreq();
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
    return CLOCK_HAL_GetOutClk(MCG) / (CLOCK_HAL_GetSysDiv(SIM) + 1);
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
    return CLOCK_HAL_GetOutClk(MCG) / (CLOCK_HAL_GetSysDiv(SIM) + 1);
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
    return CLOCK_HAL_GetOutClk(MCG) / ((CLOCK_HAL_GetSysDiv(SIM) + 1) \
                                        * (CLOCK_HAL_GetBusDiv(SIM) + 1));
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
    return CLOCK_SYS_GetSystemClockFreq() / ((CLOCK_HAL_GetBusDiv(SIM) + 1) \
                                        * (CLOCK_HAL_GetFlashClkMode(SIM) + 1));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetRtcOutFreq
 * Description   : Gets the RTC_CLK frequency.
 * This function gets RTC_CLK  clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetRtcOutFreq(void)
{
    if (kClockRtcSrcRtcOsc32kClk == CLOCK_SYS_GetRtcOutSrc())
    {
        return g_xtalRtcClkFreq;
    }
    else
    {
        return CLOCK_HAL_GetInternalRefClk(MCG);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetExternalRefClockFreq
 * Description   : Gets the external clock frequency.
 * This function gets the external reference clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetExternalRefClock32kFreq(void)
{
    clock_er32k_src_t src;
    uint32_t freq;

    src = CLOCK_HAL_GetExternalRefClock32kSrc(SIM);

    switch (src)
    {
        case kClockEr32kSrcOsc32kClk:        /* OSC 32k clock  */
            freq = g_xtalRtcClkFreq;
            break;
        case kClockEr32kSrcEr32kClk:         /* ERCLK32K clock  */
            freq = (32768U == g_xtal0ClkFreq) ? 32768U : 0U;
            break;
        case kClockEr32kSrcMcgIrClk:         /* MCGIRCLK clock  */
            freq = CLOCK_HAL_GetInternalRefClk(MCG);
            break;
        case kClockEr32kSrcLpo:              /* LPO clock      */
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
 * Function Name : CLOCK_SYS_GetAfeFreq
 * Description   : Gets AFE module clock frequency.
 * This function gets the AFE module clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetAfeFreq(uint32_t instance, clock_afe_src_t afeSrc)
{
    if (kClockAfeSrcPllClk == afeSrc)
    {
        return CLOCK_HAL_GetPll0Clk(MCG);
    }
	else if(kClockAfeSrcFllClk == afeSrc)
    {
        return CLOCK_HAL_GetFllClk(MCG);
    }
    else if(kClockAfeSrcOscClk == afeSrc)
    {
        return CLOCK_SYS_GetOsc0ExternalRefClockFreq();
    }
    else
    {
        return g_afeClkFreq[0];
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
        return CLOCK_SYS_GetLpoClockFreq();               /* LPO       clock  */
    }
    else if(kClockWdogSrcOsc32kClk == wdogSrc)
    {
        return CLOCK_SYS_GetOsc0ExternalRefClockFreq();   /* OSC32K    clock  */
    }
    else if(kClockWdogSrcMcgIrClk == wdogSrc)
    {
        return CLOCK_HAL_GetInternalRefClk(MCG);     /* MCGIRCLK  clock  */
    }
    else
    {
        return CLOCK_SYS_GetExternalRefClock32kFreq();    /* ERCLK32K  clock  */
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
        case kClockLptmrSrcMcgIrClk:                      /* MCGIRCLK  clock */
            freq = CLOCK_HAL_GetInternalRefClk(MCG);
            break;
        case kClockLptmrSrcLpoClk:                        /* LPO       clock */
            freq = CLOCK_SYS_GetLpoClockFreq();
            break;
        case kClockLptmrSrcEr32kClk:                     /* ERCLK32K clock */
            freq = CLOCK_SYS_GetExternalRefClock32kFreq();
            break;
        case kClockLptmrSrcOsc0erClk:                     /* OSCERCLK  clock */
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
 * Function Name : CLOCK_SYS_GetSLcdFreq
 * Description   : Gets the Segment LCD clock frequency.
 * This function gets the Segment LCD clock frequency.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetSlcdFreq(uint32_t instance, clock_slcd_src_t slcdSrc)
{
    uint32_t freq;

    switch (slcdSrc)
    {
        case kClockSLcdSrcMcgIrClk:                      /* MCGIRCLK  clock */
            freq = CLOCK_HAL_GetInternalRefClk(MCG);
            break;
        case kClockSLcdSrcOsc32kClk:                     /* ERCLK32K clock */
            freq = CLOCK_SYS_GetExternalRefClock32kFreq();
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetUartFreq
 * Description   : Gets the clock frequency for UART module.
 * This function gets the clock frequency for UART module.
 *
 *END**************************************************************************/
uint32_t CLOCK_SYS_GetUartFreq(uint32_t instance)
{
    uint32_t freq = 0;

    switch (instance)
    {
    case 0:
    case 2:
        freq = CLOCK_SYS_GetBusClockFreq();
        break;
    case 1:
    case 3:
        freq = CLOCK_SYS_GetSystemClockFreq();
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
    kSimClockGatePortE,
    kSimClockGatePortF,
    kSimClockGatePortG,
    kSimClockGatePortH,
    kSimClockGatePortI,
    kSimClockGatePortJ,
    kSimClockGatePortK,
    kSimClockGatePortL,
    kSimClockGatePortM
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnablePortClock
 * Description   : Enable the clock for PORT module
 * This function enables the clock for PORT module
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
 * This function disables the clock for PORT module
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
 * This function will get the clock gate state for PORT module.
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
    kSimClockGateAdc0
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableAdcClock
 * Description   : Enable the clock for ADC module
 * This function enables the clock for ADC module
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
 * This function disables the clock for ADC module
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
 * This function will get the clock gate state for ADC module.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetAdcGateCmd(uint32_t instance)
{
    assert(instance < sizeof(adcGateTable)/sizeof(adcGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, adcGateTable[instance]);
}

/* PIT instance table. */
static const sim_clock_gate_name_t pitGateTable[] =
{
    kSimClockGatePit0,
    kSimClockGatePit1
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnablePitClock
 * Description   : Enable the clock for PIT module
 * This function enables the clock for PIT module
 *
 *END**************************************************************************/
void CLOCK_SYS_EnablePitClock(uint32_t instance)
{
    assert(instance < sizeof(pitGateTable)/sizeof(pitGateTable[0]));

    SIM_HAL_EnableClock(SIM, pitGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisablePitClock
 * Description   : Disable the clock for PIT module
 * This function disables the clock for PIT module
 *
 *END**************************************************************************/
void CLOCK_SYS_DisablePitClock(uint32_t instance)
{
    assert(instance < sizeof(pitGateTable)/sizeof(pitGateTable[0]));

    SIM_HAL_DisableClock(SIM, pitGateTable[instance]);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetPitGateCmd
 * Description   : Get the the clock gate state for PIT module
 * This function will get the clock gate state for PIT module.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetPitGateCmd(uint32_t instance)
{
    assert(instance < sizeof(pitGateTable)/sizeof(pitGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, pitGateTable[instance]);
}

/* SPI instance table. */
static const sim_clock_gate_name_t spiGateTable[] =
{
    kSimClockGateSpi0,
    kSimClockGateSpi1
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableSpiClock
 * Description   : Enable the clock for SPI module
 * This function enables the clock for SPI module
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
 * This function disables the clock for SPI module
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
 * This function will get the clock gate state for SPI module.
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
    kSimClockGateI2c1
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableI2cClock
 * Description   : Enable the clock for I2C module
 * This function enables the clock for I2C module
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
 * This function disables the clock for I2C module
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
 * This function will get the clock gate state for I2C module.
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
    kSimClockGateUart3
};

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableUartClock
 * Description   : Enable the clock for UART module
 * This function enables the clock for UART module
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
 * This function enables the clock for UART module
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
 * This function will get the clock gate state for UART module.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetUartGateCmd(uint32_t instance)
{
    assert(instance < sizeof(uartGateTable)/sizeof(uartGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, uartGateTable[instance]);
}

/* Quad Timer instance table. */
static const sim_clock_gate_name_t quadtmrGateTable[] =
{
    kSimClockGateQuadTmr0,
    kSimClockGateQuadTmr1,
    kSimClockGateQuadTmr2,
    kSimClockGateQuadTmr3
};

 /*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_EnableQuadTmrClock
 * Description   : Enable the clock for Quad Timer module.
 * This function enables the clock for Quad Timer module.
 *
 *END**************************************************************************/
void CLOCK_SYS_EnableQuadTmrClock(uint32_t instance)
{
    assert(instance < sizeof(quadtmrGateTable)/sizeof(quadtmrGateTable[0]));

    SIM_HAL_EnableClock(SIM, quadtmrGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_DisableQuadTmrClock
 * Description   : Disable the clock for Quad Timer module.
 * This function disables the clock for Quad Timer module.
 *
 *END**************************************************************************/
void CLOCK_SYS_DisableQuadTmrClock(uint32_t instance)
{
    assert(instance < sizeof(quadtmrGateTable)/sizeof(quadtmrGateTable[0]));

    SIM_HAL_DisableClock(SIM, quadtmrGateTable[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetQuadTmrGateCmd
 * Description   : Get the the clock gate state for Quad Timer module.
 * This function will get the clock gate state for Quad Timer module.
 *
 *END**************************************************************************/
bool CLOCK_SYS_GetQuadTmrGateCmd(uint32_t instance)
{
    assert(instance < sizeof(quadtmrGateTable)/sizeof(quadtmrGateTable[0]));

    return SIM_HAL_GetGateCmd(SIM, quadtmrGateTable[instance]);
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

    src = CLOCK_HAL_GetLpuartClkSel(SIM);
    switch (src)
    {
        case kClockLpuartSrcPllFllSel:
            freq = CLOCK_SYS_GetPllFllClockFreq();
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
 * Function Name : CLOCK_SYS_GetPllFllClockFreq
 * Description   : Get the MCGPLLCLK/MCGFLLCLK/BUS/RTC_OSC clock frequency
 *                 selected by PLLFLL register bit.
 * This function gets the frequency of the MCGPLLCLK/MCGFLLCLK/BUS/RTC_OSC.
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
       case kClockPllFllSelBus:
           freq = CLOCK_SYS_GetBusClockFreq();
           break;
       case kClockPllFllSelOsc32k:
           freq = g_xtalRtcClkFreq;
           break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/


