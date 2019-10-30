/*
 * Copyright 2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: RV32M1
package_id: RV32M1
mcu_data: ksdk2_0
processor_version: 0.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/*FUNCTION**********************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 *END**************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}

#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */
#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */
#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */
#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port */
#define PIN11_IDX                       11u   /*!< Pin number for pin 11 in a port */
#define PIN22_IDX                       22u   /*!< Pin number for pin 22 in a port */
#define PIN23_IDX                       23u   /*!< Pin number for pin 23 in a port */
#define PIN24_IDX                       24u   /*!< Pin number for pin 24 in a port */
#define PIN25_IDX                       25u   /*!< Pin number for pin 25 in a port */
#define PIN26_IDX                       26u   /*!< Pin number for pin 26 in a port */
#define PIN27_IDX                       27u   /*!< Pin number for pin 27 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: N2, peripheral: LPUART0, signal: RX, pin_signal: LPCMP0_IN0/PTC7/LLWU_P15/LPSPI0_PCS3/LPUART0_RX/LPI2C1_HREQ/TPM0_CH0/LPTMR1_ALT1}
  - {pin_num: P3, peripheral: LPUART0, signal: TX, pin_signal: LPCMP0_IN1/PTC8/LPSPI0_SCK/LPUART0_TX/LPI2C0_HREQ/TPM0_CH1}
  - {pin_num: B5, peripheral: LPUART1, signal: RX, pin_signal: PTA25/LPUART1_RX/LPSPI3_SOUT/LPI2C2_SDAS/FB_AD31}
  - {pin_num: A5, peripheral: LPUART1, signal: TX, pin_signal: PTA26/LPUART1_TX/LPSPI3_PCS2/LPI2C2_SCLS/FB_AD30}
  - {pin_num: U11, peripheral: SDHC0, signal: CMD, pin_signal: ADC0_SE12/PTD9/SDHC0_CMD/LPSPI2_SIN/LPI2C1_SCLS/TRACE_DATA0/TPM2_CH2/FXIO0_D29, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: up, pull_enable: enable}
  - {pin_num: P10, peripheral: SDHC0, signal: 'DATA, 0', pin_signal: ADC0_SE10/PTD7/SDHC0_D0/LPSPI2_SOUT/EMVSIM0_PD/TRACE_DATA2/TPM2_CH4/FXIO0_D27, slew_rate: fast,
    open_drain: disable, pull_select: up, pull_enable: enable}
  - {pin_num: U9, peripheral: SDHC0, signal: 'DATA, 1', pin_signal: ADC0_SE9/PTD6/SDHC0_D1/LPSPI2_SCK/EMVSIM0_IO/TRACE_DATA3/TPM2_CH5/FXIO0_D26, slew_rate: fast,
    open_drain: disable, pull_select: up, pull_enable: enable}
  - {pin_num: R11, peripheral: SDHC0, signal: 'DATA, 2', pin_signal: ADC0_SE14/PTD11/SDHC0_D2/USB0_SOF_OUT/LPI2C1_SCL/CLKOUT/TPM2_CH0/FXIO0_D31, slew_rate: fast,
    open_drain: disable, drive_strength: low, pull_select: up, pull_enable: enable}
  - {pin_num: P11, peripheral: SDHC0, signal: 'DATA, 3', pin_signal: ADC0_SE13/PTD10/LLWU_P20/SDHC0_D3/LPSPI2_PCS0/LPI2C1_SDA/TRACE_CLK_OUT/TPM2_CH1/FXIO0_D30, slew_rate: fast,
    open_drain: disable, drive_strength: low, pull_select: up, pull_enable: enable}
  - {pin_num: T9, peripheral: SDHC0, signal: DCLK, pin_signal: ADC0_SE11/PTD8/LLWU_P19/SDHC0_DCLK/LPSPI2_PCS2/LPI2C1_SDAS/TRACE_DATA1/TPM2_CH3/FXIO0_D28, slew_rate: fast,
    open_drain: disable, drive_strength: low, pull_select: up, pull_enable: enable}
  - {pin_num: P6, peripheral: GPIOC, signal: 'GPIO, 27', pin_signal: PTC27/TPM0_CH4, slew_rate: fast, open_drain: disable, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Clock Gate Control: 0x01u */
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Gate Control: 0x01u */
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Clock Gate Control: 0x01u */

  const port_pin_config_t portc27_pinP6_config = {
    kPORT_PullDisable,                                       /* Internal pull-up/down resistor is disabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTC27 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTC, PIN27_IDX, &portc27_pinP6_config); /* PORTC27 (pin P6) is configured as PTC27 */
  PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_MuxAlt3);            /* PORTC7 (pin N2) is configured as LPUART0_RX */
  PORT_SetPinMux(PORTC, PIN8_IDX, kPORT_MuxAlt3);            /* PORTC8 (pin P3) is configured as LPUART0_TX */

  const port_pin_config_t portd10_pinP11_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt2,                                           /* Pin is configured as SDHC0_D3 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTD, PIN10_IDX, &portd10_pinP11_config); /* PORTD10 (pin P11) is configured as SDHC0_D3 */
  const port_pin_config_t portd11_pinR11_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt2,                                           /* Pin is configured as SDHC0_D2 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTD, PIN11_IDX, &portd11_pinR11_config); /* PORTD11 (pin R11) is configured as SDHC0_D2 */
  const port_pin_config_t portd6_pinU9_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt2,                                           /* Pin is configured as SDHC0_D1 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTD, PIN6_IDX, &portd6_pinU9_config);  /* PORTD6 (pin U9) is configured as SDHC0_D1 */
  const port_pin_config_t portd7_pinP10_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt2,                                           /* Pin is configured as SDHC0_D0 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTD, PIN7_IDX, &portd7_pinP10_config); /* PORTD7 (pin P10) is configured as SDHC0_D0 */
  const port_pin_config_t portd8_pinT9_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt2,                                           /* Pin is configured as SDHC0_DCLK */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTD, PIN8_IDX, &portd8_pinT9_config);  /* PORTD8 (pin T9) is configured as SDHC0_DCLK */
  const port_pin_config_t portd9_pinU11_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt2,                                           /* Pin is configured as SDHC0_CMD */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTD, PIN9_IDX, &portd9_pinU11_config); /* PORTD9 (pin U11) is configured as SDHC0_CMD */

  PORT_SetPinMux(PORTA, PIN22_IDX, kPORT_MuxAsGpio);         /* PORTA22 (pin D6) is configured as PTA24 */
  PORT_SetPinMux(PORTA, PIN23_IDX, kPORT_MuxAsGpio);         /* PORTA23 (pin D6) is configured as PTA24 */
  PORT_SetPinMux(PORTA, PIN24_IDX, kPORT_MuxAsGpio);         /* PORTA24 (pin D6) is configured as PTA24 */
  PORT_SetPinMux(PORTA, PIN25_IDX, kPORT_MuxAlt2);            /* PORTA25 (pin B5) is configured as LPUART1_RX */
  PORT_SetPinMux(PORTA, PIN26_IDX, kPORT_MuxAlt2);            /* PORTA26 (pin A5) is configured as LPUART1_TX */
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
