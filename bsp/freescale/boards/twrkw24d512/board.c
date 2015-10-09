/*
 * Copyright (c) 2013-2014, Freescale Semiconductor, Inc.
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

#include "board.h"
#include "fsl_clock_manager.h"
#include "fsl_smc_hal.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"

/* Configuration for enter VLPR mode. Core clock = 4MHz. */
const clock_manager_user_config_t g_defaultClockConfigVlpr =
{
    .mcgConfig =
    {
        .mcg_mode           = kMcgModeBLPI,   // Work in BLPI mode.
        .irclkEnable        = true,  // MCGIRCLK enable.
        .irclkEnableInStop  = false, // MCGIRCLK disable in STOP mode.
        .ircs               = kMcgIrcFast, // Select IRC4M.
        .fcrdiv             = 0U,    // FCRDIV is 0.

        .frdiv   = 0U,
        .drs     = kMcgDcoRangeSelLow,  // Low frequency range
        .dmx32   = kMcgDmx32Default,    // DCO has a default range of 25%
        .oscsel  = kMcgOscselOsc,       // Select OSC

        .pll0EnableInFllMode        = false,  // PLL0 disable
        .pll0EnableInStop  = false,  // PLL0 disalbe in STOP mode
        .prdiv0            = 0U,
        .vdiv0             = 0U,
    },
    .simConfig =
    {
        .pllFllSel = kClockPllFllSelFll, // PLLFLLSEL select FLL.
        .er32kSrc  = kClockEr32kSrcRtc,     // ERCLK32K selection, use RTC.
        .outdiv1   = 0U,
        .outdiv2   = 0U,
        .outdiv3   = 0U,
        .outdiv4   = 3U,
    },
    .oscerConfig =
    {
        .enable       = true,  // OSCERCLK enable.
        .enableInStop = true,  // OSCERCLK enable in STOP mode.
    }
};

/* Configuration for enter RUN mode. Core clock = 48MHz. */
const clock_manager_user_config_t g_defaultClockConfigRun =
{
    .mcgConfig =
    {
        .mcg_mode           = kMcgModePEE,   // Work in PEE mode.
        .irclkEnable        = true,  // MCGIRCLK enable.
        .irclkEnableInStop  = false, // MCGIRCLK disable in STOP mode.
        .ircs               = kMcgIrcSlow, // Select IRC32k.
        .fcrdiv             = 0U,    // FCRDIV is 0.

        .frdiv   = 2U,
        .drs     = kMcgDcoRangeSelLow,  // Low frequency range
        .dmx32   = kMcgDmx32Default,    // DCO has a default range of 25%
        .oscsel  = kMcgOscselOsc,       // Select OSC

        .pll0EnableInFllMode        = false,  // PLL0 disable
        .pll0EnableInStop  = false,  // PLL0 disalbe in STOP mode
        .prdiv0            = 0x01U,
        .vdiv0             = 0x00U,
    },
    .simConfig =
    {
        .pllFllSel = kClockPllFllSelPll,    // PLLFLLSEL select PLL.
        .er32kSrc  = kClockEr32kSrcRtc,     // ERCLK32K selection, use RTC.
        .outdiv1   = 0U,
        .outdiv2   = 0U,
        .outdiv4   = 1U,
    },
    .oscerConfig =
    {
        .enable       = true,  // OSCERCLK enable.
        .enableInStop = true,  // OSCERCLK enable in STOP mode.
    }
};

/* Function to initialize OSC0 base on board configuration. */
void BOARD_InitOsc0(void)
{
    // OSC0 configuration.
    osc_user_config_t osc0Config =
    {
        .freq                = OSC0_XTAL_FREQ,
        .hgo                 = MCG_HGO0,
        .range               = MCG_RANGE0,
        .erefs               = MCG_EREFS0,
        .enableCapacitor2p   = OSC0_SC2P_ENABLE_CONFIG,
        .enableCapacitor4p   = OSC0_SC4P_ENABLE_CONFIG,
        .enableCapacitor8p   = OSC0_SC8P_ENABLE_CONFIG,
        .enableCapacitor16p  = OSC0_SC16P_ENABLE_CONFIG,
    };

    CLOCK_SYS_OscInit(0U, &osc0Config);
}

/* Function to initialize RTC external clock base on board configuration. */
void BOARD_InitRtcOsc(void)
{
    rtc_osc_user_config_t rtcOscConfig =
    {
        .freq                = RTC_XTAL_FREQ,
        .enableCapacitor2p   = RTC_SC2P_ENABLE_CONFIG,
        .enableCapacitor4p   = RTC_SC4P_ENABLE_CONFIG,
        .enableCapacitor8p   = RTC_SC8P_ENABLE_CONFIG,
        .enableCapacitor16p  = RTC_SC16P_ENABLE_CONFIG,
        .enableOsc           = RTC_OSC_ENABLE_CONFIG,
    };

    CLOCK_SYS_RtcOscInit(0U, &rtcOscConfig);
}

static uint8_t BOARD_ExtClk_Setup_HookUp(uint32_t clk_out_value)
{
    uint8_t result = 0;

    switch (clk_out_value) {
        case 4000000U:
            /* Start XCVR clock in order to derive MCGOUTCLK */
            SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK; /* Ungate PORTB and PORTC clock*/
            GPIOB->PDDR |= 0x00080000u; /* Set PORTB.19 as output - XCVR RESET pin */
            GPIOC->PDDR |= 0x00000001u; /* Set PORTC.0 as output - XCVR GPIO5 pin */
            PORTB->PCR[19] = (PORTB_PCR19 & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(0x01u); /* PORTB.19 as GPIO */
            PORTC->PCR[0]  = (PORTC_PCR0 & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(0x01u); /* PORTC.0 as GPIO*/
            GPIOC->PCOR = 0x00000001u; /* Clear XCVR GPIO5 pin*/
            GPIOB->PCOR = 0x00080000u; /* Clear XCVR RESET pin*/
            GPIOB->PSOR = 0x00080000u; /* Set XCVR RESET pin*/
            result =  1U;  /*  The output was set successfully */
            break;
        case 0U:
            /* No initialization, modem remains in the reset state */
            result =  1U;  /*  The output was set successfully */
            break;
        default:
            result = 0U; /* Requested value cannot be set */
            break;
    }
    return result;
}

static void CLOCK_SetBootConfig(clock_manager_user_config_t const* config)
{
    CLOCK_SYS_SetSimConfigration(&config->simConfig);

    CLOCK_SYS_SetOscerConfigration(0, &config->oscerConfig);

#if (CLOCK_INIT_CONFIG == CLOCK_VLPR)
    CLOCK_SYS_BootToBlpi(&config->mcgConfig);
 #else
    CLOCK_SYS_BootToPee(&config->mcgConfig);
 #endif

    SystemCoreClock = CORE_CLOCK_FREQ;
}

/* Initialize clock. */
void BOARD_ClockInit(void)
{
#if defined(OSC0_XTAL_FREQ)
    /* Perform initialization of the wireless modem clock output */
    if (BOARD_ExtClk_Setup_HookUp (OSC0_XTAL_FREQ) != 1U) {
        /* If the initialization was not sucesfull, do not continue with clock setup */
        return;
    }
#endif
    /* Set allowed power mode, allow all. */
    SMC_HAL_SetProtection(SMC, kAllowPowerModeAll);

    /* Setup board clock source. */
    // Setup OSC0 if used.
    // Configure OSC0 pin mux.
    PORT_HAL_SetMuxMode(EXTAL0_PORT, EXTAL0_PIN, EXTAL0_PINMUX);
    BOARD_InitOsc0();

    // Setup RTC external clock if used.
    BOARD_InitRtcOsc();

    /* Set system clock configuration. */
#if (CLOCK_INIT_CONFIG == CLOCK_VLPR)
    CLOCK_SetBootConfig(&g_defaultClockConfigVlpr);
#else
    CLOCK_SetBootConfig(&g_defaultClockConfigRun);
#endif
}

void dbg_uart_init(void)
{
    configure_uart_pins(BOARD_DEBUG_UART_INSTANCE);

    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUD, kDebugConsoleUART);
}
/******************************************************************************
 *
 *   @name      usb_device_board_init
 *
 *   @brief     This function is to handle board-specified initialization
 *
 *   @param     controller_id:        refer to CONTROLLER_INDEX defined in usb_misc.h
 *                                    "0" stands for USB_CONTROLLER_KHCI_0.
 *   @return    status
 *                                    0 : successful
 *                                    1 : failed
 **
 *****************************************************************************/
uint8_t usb_device_board_init(uint8_t controller_id)
{
    int8_t ret = 0;

    if (0 == controller_id)
    {
        /* TO DO */
        /*add board initialization code if have*/
    }
    else
    {
        ret = 1;
    }

    return ret;

}

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.10]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
