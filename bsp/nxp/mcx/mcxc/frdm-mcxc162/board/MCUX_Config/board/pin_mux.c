/*
 * Copyright 2026 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"

#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_reset.h"
#include "rtconfig.h"

static void configure_pin(PORT_Type *port, uint32_t pin, port_mux_t mux,
                          uint16_t pull, uint16_t drive)
{
    const port_pin_config_t config = {
        .pullSelect = pull,
        .pullValueSelect = kPORT_LowPullResistor,
        .slewRate = kPORT_FastSlewRate,
        .passiveFilterEnable = kPORT_PassiveFilterDisable,
        .openDrainEnable = kPORT_OpenDrainDisable,
        .driveStrength = drive,
        .driveStrength1 = kPORT_NormalDriveStrength,
        .mux = mux,
        .inputBuffer = kPORT_InputBufferEnable,
        .invertInput = kPORT_InputNormal,
        .lockRegister = kPORT_UnlockRegister,
    };

    PORT_SetPinConfig(port, pin, &config);
}

#ifdef BSP_USING_UART0
static void init_uart0_pins(void)
{
    CLOCK_EnableClock(kCLOCK_GatePORT0);
    RESET_ReleasePeripheralReset(kPORT0_RST_SHIFT_RSTn);
    RESET_ReleasePeripheralReset(kLPUART0_RST_SHIFT_RSTn);

    configure_pin(PORT0, 2U, kPORT_MuxAlt2, kPORT_PullDisable, kPORT_HighDriveStrength);
    configure_pin(PORT0, 3U, kPORT_MuxAlt2, kPORT_PullUp, kPORT_LowDriveStrength);
}
#endif

#ifdef BSP_USING_UART1
static void init_uart1_pins(void)
{
    CLOCK_EnableClock(kCLOCK_GatePORT2);
    RESET_ReleasePeripheralReset(kPORT2_RST_SHIFT_RSTn);
    RESET_ReleasePeripheralReset(kLPUART1_RST_SHIFT_RSTn);

    configure_pin(PORT2, 12U, kPORT_MuxAlt3, kPORT_PullDisable, kPORT_LowDriveStrength);
    configure_pin(PORT2, 13U, kPORT_MuxAlt3, kPORT_PullDisable, kPORT_LowDriveStrength);
}
#endif

#ifdef BSP_USING_UART2
static void init_uart2_pins(void)
{
    CLOCK_EnableClock(kCLOCK_GatePORT3);
    RESET_ReleasePeripheralReset(kPORT3_RST_SHIFT_RSTn);
    RESET_ReleasePeripheralReset(kLPUART2_RST_SHIFT_RSTn);

    configure_pin(PORT3, 12U, kPORT_MuxAlt3, kPORT_PullDisable, kPORT_LowDriveStrength);
    configure_pin(PORT3, 13U, kPORT_MuxAlt3, kPORT_PullDisable, kPORT_LowDriveStrength);
}
#endif

#ifdef BSP_USING_I2C0
static void init_i2c0_pins(void)
{
    CLOCK_EnableClock(kCLOCK_GatePORT3);
    RESET_ReleasePeripheralReset(kPORT3_RST_SHIFT_RSTn);
    RESET_ReleasePeripheralReset(kLPI2C0_RST_SHIFT_RSTn);

    configure_pin(PORT3, 27U, kPORT_MuxAlt2, kPORT_PullDisable, kPORT_LowDriveStrength);
    configure_pin(PORT3, 28U, kPORT_MuxAlt2, kPORT_PullDisable, kPORT_LowDriveStrength);
}
#endif

#ifdef BSP_USING_SPI0
static void init_spi0_pins(void)
{
    const gpio_pin_config_t cs_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U,
    };

    CLOCK_EnableClock(kCLOCK_GatePORT3);
    RESET_ReleasePeripheralReset(kPORT3_RST_SHIFT_RSTn);
    RESET_ReleasePeripheralReset(kLPSPI0_RST_SHIFT_RSTn);

    configure_pin(PORT3, 8U, kPORT_MuxAlt2, kPORT_PullDisable, kPORT_LowDriveStrength);
    configure_pin(PORT3, 9U, kPORT_MuxAlt2, kPORT_PullDisable, kPORT_LowDriveStrength);
    configure_pin(PORT3, 10U, kPORT_MuxAlt2, kPORT_PullDisable, kPORT_LowDriveStrength);
    configure_pin(PORT3, 11U, kPORT_MuxAsGpio, kPORT_PullDisable, kPORT_LowDriveStrength);
    GPIO_PinInit(GPIO3, 11U, &cs_config);
}
#endif

#ifdef BSP_USING_PWM0
static void init_pwm0_pins(void)
{
    CLOCK_EnableClock(kCLOCK_GatePORT3);
    RESET_ReleasePeripheralReset(kPORT3_RST_SHIFT_RSTn);
    RESET_ReleasePeripheralReset(kFLEXPWM0_RST_SHIFT_RSTn);

    configure_pin(PORT3, 0U, kPORT_MuxAlt5, kPORT_PullDisable, kPORT_LowDriveStrength);
    configure_pin(PORT3, 1U, kPORT_MuxAlt5, kPORT_PullDisable, kPORT_LowDriveStrength);
}
#endif

void BOARD_InitBootPins(void)
{
#ifdef BSP_USING_UART0
    init_uart0_pins();
#endif
#ifdef BSP_USING_UART1
    init_uart1_pins();
#endif
#ifdef BSP_USING_UART2
    init_uart2_pins();
#endif
#ifdef BSP_USING_I2C0
    init_i2c0_pins();
#endif
#ifdef BSP_USING_SPI0
    init_spi0_pins();
#endif
#ifdef BSP_USING_PWM0
    init_pwm0_pins();
#endif
}
