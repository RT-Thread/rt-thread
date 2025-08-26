/*
 * Copyright 2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* RT-Thread Configuration */
#include "rtconfig.h"

/* SDK drivers */
#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

static void BOARD_InitUARTPins(void);
static void BOARD_InitI2CPins(void);
static void BOARD_InitSPIPins(void);

void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
    BOARD_InitUARTPins();
    BOARD_InitI2CPins();
    BOARD_InitSPIPins();
}

static void BOARD_InitUARTPins(void)
{
#if defined(BSP_USING_UART0)
    BOARD_InitUART0Pins();
#endif

#if defined(BSP_USING_UART1)
    BOARD_InitUART1Pins();
#endif

#if defined(BSP_USING_UART2)
    BOARD_InitUART2Pins();
#endif
}

static void BOARD_InitI2CPins(void)
{
#if defined(BSP_USING_I2C0)
    BOARD_InitI2C0Pins();
#endif

#if defined(BSP_USING_I2C1)
    BOARD_InitI2C1Pins();
#endif
}

static void BOARD_InitSPIPins(void)
{
#if defined(BSP_USING_SPI0)
    BOARD_InitSPI0Pins();
#endif

#if defined(BSP_USING_SPI1)
    BOARD_InitSPI1Pins();
#endif

#if defined(BSP_USING_SPI2)
    BOARD_InitSPI2Pins();
#endif
}

void BOARD_InitPins(void)
{
    CLOCK_EnableClock(kCLOCK_PortA);
    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortD);
    CLOCK_EnableClock(kCLOCK_PortE);
}

void BOARD_InitUART0Pins(void)
{
    /* UART 0 pins are not used on this board. */
}

void BOARD_InitUART1Pins(void)
{
    PORT_SetPinMux(PORTC, 8U, kPORT_MuxAlt2); /* Default route to UART TX/RX pins on MikroBUS */
    PORT_SetPinMux(PORTC, 9U, kPORT_MuxAlt2); /* Default route to UART TX/RX pins on MikroBUS */
}

void BOARD_InitUART2Pins(void)
{
    PORT_SetPinMux(PORTD, 17U, kPORT_MuxAlt3); /* Default route to Arduino D0/D1 and MCU-Link Virtual COM Port */
    PORT_SetPinMux(PORTE, 12U, kPORT_MuxAlt3); /* Default route to Arduino D0/D1 and MCU-Link Virtual COM Port */
}

void BOARD_InitI2C0Pins(void)
{
    PORT_SetPinMux(PORTA, 2U, kPORT_MuxAlt3); /* Default route to I2C SCL/SDA pins on MikroBUS */
    PORT_SetPinMux(PORTA, 3U, kPORT_MuxAlt3); /* Default route to I2C SCL/SDA pins on MikroBUS */
}

void BOARD_InitI2C1Pins(void)
{
    PORT_SetPinMux(PORTD, 8U, kPORT_MuxAlt2); /* Default route to Arduino D18/D19 */
    PORT_SetPinMux(PORTD, 9U, kPORT_MuxAlt2); /* Default route to Arduino D18/D19 */
}

void BOARD_InitSPI0Pins(void)
{
    PORT_SetPinMux(PORTB, 3U, kPORT_MuxAlt3); /* Default route to SPI SCK/SIN/SOUT pins on MikroBUS */
    PORT_SetPinMux(PORTE, 0U, kPORT_MuxAlt2); /* Default route to SPI SCK/SIN/SOUT pins on MikroBUS */
    PORT_SetPinMux(PORTE, 2U, kPORT_MuxAlt2); /* Default route to SPI SCK/SIN/SOUT pins on MikroBUS */
}

void BOARD_InitSPI1Pins(void)
{
    PORT_SetPinMux(PORTB, 14U, kPORT_MuxAlt3); /* Default route to Arduino D11/D12/D13 */
    PORT_SetPinMux(PORTB, 15U, kPORT_MuxAlt3); /* Default route to Arduino D11/D12/D13 */
    PORT_SetPinMux(PORTD, 2U, kPORT_MuxAlt3);  /* Default route to Arduino D11/D12/D13 */
}

void BOARD_InitSPI2Pins(void)
{
    PORT_SetPinMux(PORTA, 8U, kPORT_MuxAlt3);  /* Default route to SPI SCK/SIN/SOUT pins on PMOD (DNP by default) */
    PORT_SetPinMux(PORTC, 15U, kPORT_MuxAlt3); /* Default route to SPI SCK/SIN/SOUT pins on PMOD (DNP by default) */
    PORT_SetPinMux(PORTE, 16U, kPORT_MuxAlt3); /* Default route to SPI SCK/SIN/SOUT pins on PMOD (DNP by default) */
}
