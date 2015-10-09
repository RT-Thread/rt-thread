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
#include "fsl_spi_master_driver.h"

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

        .pll0EnableInFllMode        = false,  // PLL0 disable
        .pll0EnableInStop  = false,  // PLL0 disalbe in STOP mode
        .prdiv0            = 0U,
        .vdiv0             = 0U,
    },
    .simConfig =
    {
        .pllFllSel = kClockPllFllSelFll, // PLLFLLSEL select FLL.
        .er32kSrc  = kClockEr32kSrcLpo,     // ERCLK32K selection, use LPO.
        .outdiv1   = 0U,
        .outdiv4   = 4U,
    },
    .oscerConfig =
    {
        .enable       = true,  // OSCERCLK enable.
        .enableInStop = false, // OSCERCLK disable in STOP mode.
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

        .frdiv   = 0U,
        .drs     = kMcgDcoRangeSelLow,  // Low frequency range
        .dmx32   = kMcgDmx32Default,    // DCO has a default range of 25%

        .pll0EnableInFllMode        = false,  // PLL0 disable
        .pll0EnableInStop  = false,  // PLL0 disable in STOP mode
#ifdef MRB_KW01_9030JA    /* Define this symbol for MRB-KW01-9030JA version of the board, which have 30MHz oscillator */
        .prdiv0            = 0x0EU,
#else
        .prdiv0            = 0x0FU,
#endif
        .vdiv0             = 0x0U,
    },
    .simConfig =
    {
        .pllFllSel = kClockPllFllSelPll,    // PLLFLLSEL select PLL.
        .er32kSrc  = kClockEr32kSrcLpo,     // ERCLK32K selection, use LPO.
        .outdiv1   = 0U,
        .outdiv4   = 1U,
    },
    .oscerConfig =
    {
        .enable       = true,  // OSCERCLK enable.
        .enableInStop = false, // OSCERCLK disable in STOP mode.
    }
};

/* Clock configuration with external crystal 32.768kHz. Core clock = 48MHz. */
const clock_manager_user_config_t g_xtalClockConfig =
{
    .mcgConfig =
    {
        .mcg_mode           = kMcgModeFEE,   // Work in FEE mode.
        .irclkEnable        = true,  // MCGIRCLK enable.
        .irclkEnableInStop  = false, // MCGIRCLK disable in STOP mode.
        .ircs               = kMcgIrcSlow, // Select IRC32k.
        .fcrdiv             = 0U,    // FCRDIV is 0.

        .frdiv   = 0U,
        .drs     = kMcgDcoRangeSelMid,  // Mid frequency range
        .dmx32   = kMcgDmx32Fine,    // DCO has a fine range

        .pll0EnableInFllMode        = false,  // PLL0 disable
        .pll0EnableInStop  = false,  // PLL0 disalbe in STOP mode
        .prdiv0            = 0x0U,
        .vdiv0             = 0x0U,
    },
    .simConfig =
    {
        .pllFllSel = kClockPllFllSelFll,    // PLLFLLSEL select FLL.
        .er32kSrc  = kClockEr32kSrcOsc0,    // ERCLK32K selection, use OSC0.
        .outdiv1   = 0U,
        .outdiv4   = 1U,
    },
    .oscerConfig =
    {
        .enable       = true,  // OSCERCLK enable.
        .enableInStop = false, // OSCERCLK disable in STOP mode.
    }
};

/* Table of SPI FIFO sizes per instance. */
extern const uint32_t g_spiFifoSize[SPI_INSTANCE_COUNT];

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

}

/* Function to initialize wireless modem. */
uint8_t ExtClk_Setup_HookUp(uint32_t clk_out_value)
{
    spi_master_user_config_t userConfig;
    uint32_t spiSourceClock;
    uint8_t instance = 0;
    uint8_t result = 0;
    uint32_t sppr = 0;
    uint32_t spr = 1u;
    switch (clk_out_value)
    {
    case 1000000U:
      /* No initialization, modem is in the default state */
      result =  1U;  /*  The output was set successfully */
      break;
#if defined(MODEM_CLK_OUT_CTRL_VALUE)
    case 30000000U:    /*  For the japanese version of the board with 30MHz external crystal */
    case 32000000U:    /*  For the european and american version of the board */

    CLOCK_SYS_EnablePortClock(PORTE_IDX); /* Enabled clockgate for PORTE */
    PORT_HAL_SetMuxMode(PORTE, 30, kPortMuxAsGpio);
    GPIO_HAL_SetPinDir(GPIOE_BASE_PTR, 30, kGpioDigitalOutput); /* Set PTE30 as output */
    GPIO_HAL_SetPinOutput(GPIOE_BASE_PTR, 30); /* Set PTE30 output to 1 */
    GPIO_HAL_SetPinDir(GPIOE_BASE_PTR, 30, kGpioDigitalOutput); /* Set PTE30 as output */
    GPIO_HAL_ClearPinOutput(GPIOE_BASE_PTR, 30);  /* Release RESET pin */

    /* SPI0 pins routing */
    CLOCK_SYS_EnablePortClock(PORTC_IDX); /* Enabled clockgate for PORTC */
    CLOCK_SYS_EnablePortClock(PORTD_IDX); /* Enabled clockgate for PORTD */
    configure_spi_pins_for_modem(instance);

    /* Initialize SPI0 */
    /* Enable clock for SPI*/
    CLOCK_SYS_EnableSpiClock(instance);
    /* Reset the SPI module to it's default state, which includes SPI disabled */
    SPI_HAL_Init(g_spiBase[instance]);
    /* Set SPI to master mode */
    SPI_HAL_SetMasterSlave(g_spiBase[instance], kSpiMaster);
    /* Set slave select to automatic output mode */
    SPI_HAL_SetSlaveSelectOutputMode(g_spiBase[instance], kSpiSlaveSelect_AutomaticOutput);
    /* Set the SPI pin mode to normal mode */
    SPI_HAL_SetPinMode(g_spiBase[instance], kSpiPinMode_Normal);
#if FSL_FEATURE_SPI_FIFO_SIZE
    if (g_spiFifoSize[instance] != 0)
    {
        /* If SPI module contains a FIFO, enable it and set watermarks to half full/empty */
        SPI_HAL_SetFifoMode(g_spiBase[instance], true, kSpiTxFifoOneHalfEmpty, kSpiRxFifoOneHalfFull);
    }
#endif
    /* Save runtime structure pointers to irq handler can point to the correct state structure*/
    /* SPI system Enable*/
    SPI_HAL_Enable(g_spiBase[instance]);

    userConfig.bitCount = kSpi16BitMode;
    userConfig.polarity = kSpiClockPolarity_ActiveHigh;
    userConfig.phase = kSpiClockPhase_FirstEdge;
    userConfig.direction = kSpiMsbFirst;
    spiSourceClock = CLOCK_SYS_GetSpiFreq(instance);
    userConfig.bitsPerSec = spiSourceClock/(spr * (8 - sppr));

    /* Configure the bus to access the provided device.*/
    SPI_HAL_SetBaud(g_spiBase[instance], userConfig.bitsPerSec, spiSourceClock);
    SPI_HAL_SetDataFormat(g_spiBase[instance], userConfig.polarity, userConfig.phase, userConfig.direction);
#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    SPI_HAL_Set8or16BitMode(g_spiBase[instance], userConfig.bitCount);
#endif

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    SPI_HAL_WriteDataBlocking(g_spiBase[instance], kSpi16BitMode, MODEM_CLK_OUT_CTRL_ADDRESS, MODEM_CLK_OUT_CTRL_VALUE);
#endif
    while (!SPI_HAL_IsReadBuffFullPending(g_spiBase[instance])) {}

    /* Restore the module to defaults which includes disabling the SPI then power it down.*/
    SPI_HAL_Init(g_spiBase[instance]);
    /* Gate the clock for SPI.*/
    CLOCK_SYS_DisableSpiClock(instance);

    result = 1U;  /*  The output was set successfully */
    break;
#endif
    case 0U:
        /* No initialization, modem remains in the reset state */
        result = 1U;  /*  The output was set successfully */
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
#elif(CLOCK_INIT_CONFIG == CLOCK_RUN)
    CLOCK_SYS_BootToPee(&config->mcgConfig);
#else
    CLOCK_SYS_BootToFee(&config->mcgConfig);
#endif

    SystemCoreClock = CORE_CLOCK_FREQ;
}

/* Initialize clock. */
void BOARD_ClockInit(void)
{

#if (defined(OSC0_XTAL_FREQ) && (CLOCK_INIT_CONFIG != CLOCK_XTAL))
    /* Perform initialization of the wireless modem clock output */
    if (ExtClk_Setup_HookUp (OSC0_XTAL_FREQ) != 1U) {
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
    PORT_HAL_SetMuxMode(XTAL0_PORT, XTAL0_PIN, XTAL0_PINMUX);
    BOARD_InitOsc0();

    /* Set system clock configuration. */
#if (CLOCK_INIT_CONFIG == CLOCK_XTAL)
    CLOCK_SetBootConfig(&g_xtalClockConfig);
#elif (CLOCK_INIT_CONFIG == CLOCK_VLPR)
    CLOCK_SetBootConfig(&g_defaultClockConfigVlpr);
#else
    CLOCK_SetBootConfig(&g_defaultClockConfigRun);
#endif
}

void dbg_uart_init(void)
{
    configure_lpsci_pins(BOARD_DEBUG_UART_INSTANCE);

    // Select different clock source for LPSCI. */
#if (CLOCK_INIT_CONFIG == CLOCK_VLPR)
    CLOCK_SYS_SetLpsciSrc(BOARD_DEBUG_UART_INSTANCE, kClockLpsciSrcMcgIrClk);
#else
    CLOCK_SYS_SetLpsciSrc(BOARD_DEBUG_UART_INSTANCE, kClockLpsciSrcPllFllSel);
#endif

    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUD, kDebugConsoleLPSCI);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/


