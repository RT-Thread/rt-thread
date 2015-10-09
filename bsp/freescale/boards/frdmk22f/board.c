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
        .pll0EnableInStop           = false,  // PLL0 disalbe in STOP mode
        .prdiv0                     = 0U,
        .vdiv0                      = 0U,
    },
    .simConfig =
    {
        .pllFllSel = kClockPllFllSelIrc48M, // PLLFLLSEL select IRC48MCLK.
        .er32kSrc  = kClockEr32kSrcRtc,     // ERCLK32K selection, use RTC.
        .outdiv1   = 0U,
        .outdiv2   = 0U,
        .outdiv3   = 0U,
        .outdiv4   = 4U,
    },
    .oscerConfig =
    {
        .enable       = true,  // OSCERCLK enable.
        .enableInStop = false, // OSCERCLK disable in STOP mode.
        .erclkDiv     = 0U,    // OSCERCLK divider setting.
    }
};

/* Configuration for enter RUN mode. Core clock = 80MHz. */
const clock_manager_user_config_t g_defaultClockConfigRun =
{
    .mcgConfig =
    {
        .mcg_mode           = kMcgModePEE,   // Work in PEE mode.
        .irclkEnable        = true,  // MCGIRCLK enable.
        .irclkEnableInStop  = false, // MCGIRCLK disable in STOP mode.
        .ircs               = kMcgIrcSlow, // Select IRC32k.
        .fcrdiv             = 0U,    // FCRDIV is 0.

        .frdiv   = 3U,
        .drs     = kMcgDcoRangeSelLow,  // Low frequency range
        .dmx32   = kMcgDmx32Default,    // DCO has a default range of 25%
        .oscsel  = kMcgOscselOsc,       // Select OSC

        .pll0EnableInFllMode        = false,  // PLL0 disable
        .pll0EnableInStop           = false,  // PLL0 disalbe in STOP mode
        .prdiv0                     = 0x3U,
        .vdiv0                      = 0x10U,
    },
    .simConfig =
    {
        .pllFllSel = kClockPllFllSelPll,    // PLLFLLSEL select PLL.
        .er32kSrc  = kClockEr32kSrcRtc,     // ERCLK32K selection, use RTC.
        .outdiv1   = 0U,
        .outdiv2   = 1U,
        .outdiv3   = 2U,
        .outdiv4   = 3U,
    },
    .oscerConfig =
    {
        .enable       = true,  // OSCERCLK enable.
        .enableInStop = false, // OSCERCLK disable in STOP mode.
        .erclkDiv     = 0U,    // OSCERCLK divider setting.
    }
};

/* Configuration for HSRUN mode. Core clock = 120MHz. */
const clock_manager_user_config_t g_defaultClockConfigHsrun =
{
    .mcgConfig =
    {
        .mcg_mode           = kMcgModePEE,   // Work in PEE mode.
        .irclkEnable        = true,  // MCGIRCLK enable.
        .irclkEnableInStop  = false, // MCGIRCLK disable in STOP mode.
        .ircs               = kMcgIrcSlow, // Select IRC32k.
        .fcrdiv             = 0U,    // FCRDIV is 0.

        .frdiv   = 3U,
        .drs     = kMcgDcoRangeSelLow,  // Low frequency range
        .dmx32   = kMcgDmx32Default,    // DCO has a default range of 25%
        .oscsel  = kMcgOscselOsc,       // Select OSC

        .pll0EnableInFllMode        = false,  // PLL0 disable
        .pll0EnableInStop           = false,  // PLL0 disalbe in STOP mode
        .prdiv0                     = 0x1U,
        .vdiv0                      = 0x6U,
    },
    .simConfig =
    {
        .pllFllSel = kClockPllFllSelPll,    // PLLFLLSEL select PLL.
        .er32kSrc  = kClockEr32kSrcRtc,     // ERCLK32K selection, use RTC.
        .outdiv1   = 0U,
        .outdiv2   = 1U,
        .outdiv3   = 3U,
        .outdiv4   = 4U,
    },
    .oscerConfig =
    {
        .enable       = true,  // OSCERCLK enable.
        .enableInStop = false, // OSCERCLK disable in STOP mode.
        .erclkDiv     = 0U,    // OSCERCLK divider setting.
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
    /* Set allowed power mode, allow all. */
    SMC_HAL_SetProtection(SMC, kAllowPowerModeAll);
#if (CLOCK_INIT_CONFIG == CLOCK_HSRUN)
    smc_power_mode_config_t powerModeConfig = {
        .powerModeName = kPowerModeHsrun,
    };
#endif

    /* Setup board clock source. */
    // Setup OSC0 if used.
    // Configure OSC0 pin mux.
    PORT_HAL_SetMuxMode(EXTAL0_PORT, EXTAL0_PIN, EXTAL0_PINMUX);
    PORT_HAL_SetMuxMode(XTAL0_PORT, XTAL0_PIN, XTAL0_PINMUX);
    BOARD_InitOsc0();

    // Setup RTC external clock if used.
    BOARD_InitRtcOsc();

    /* Set system clock configuration. */
#if (CLOCK_INIT_CONFIG == CLOCK_VLPR)
    CLOCK_SetBootConfig(&g_defaultClockConfigVlpr);
#elif (CLOCK_INIT_CONFIG == CLOCK_HSRUN)
    SMC_HAL_SetMode(SMC, &powerModeConfig);
    CLOCK_SetBootConfig(&g_defaultClockConfigHsrun);
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
 *                                    "0" stands for USB_CONTROLLER_KHCI_0
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
#ifdef USBCFG_HOST_PORT_NATIVE
#define kGpioUsbVbus                     GPIO_MAKE_PIN(GPIOC_IDX, 9U)
/* Declare usb vbus gpio enable pin usb otg demo and host demo*/
const gpio_output_pin_user_config_t usbvbusenablePin[] =
{
    {
        .pinName = kGpioUsbVbus,
        .config.outputLogic = 1,
        .config.slewRate = kPortSlowSlewRate,
        .config.isOpenDrainEnabled = false,
        .config.driveStrength = kPortLowDriveStrength,
    },
    {
        .pinName = GPIO_PINS_OUT_OF_RANGE,
    }
};
#endif

/******************************************************************************
 *
 *   @name        usb_host_board_init
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
uint8_t usb_host_board_init(uint8_t controller_id)
{
    int8_t ret = 0;
    /*"0" stands for USB_CONTROLLER_KHCI_0 */
    if (0 == controller_id)
    {
#ifdef USBCFG_HOST_PORT_NATIVE
        /* Enable clock gating to all ports C*/
        CLOCK_SYS_EnablePortClock(2);
        GPIO_DRV_Init(NULL, usbvbusenablePin);
        GPIO_DRV_WritePinOutput(kGpioUsbVbus, 1);
#endif
    }
    else
    {
       ret = 1;
    }

    return ret;


}

/*******************************************************************************
 * EOF
 ******************************************************************************/

