//*****************************************************************************
//
// bl_uart.h - Definitions for the UART transport functions.
//
// Copyright (c) 2006-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#ifndef __BL_UART_H__
#define __BL_UART_H__

//*****************************************************************************
//
// This section maps the defines to default for UART Boot Loader for legacy
// projects
//
//*****************************************************************************
#ifndef UART_CLOCK_ENABLE
#define UART_CLOCK_ENABLE       SYSCTL_RCGCUART_R0
#endif

#ifndef UARTx
#define UARTx                   UART0
#endif

#ifndef UART_RXPIN_CLOCK_ENABLE
#define UART_RXPIN_CLOCK_ENABLE SYSCTL_RCGCGPIO_R0
#endif

#ifndef UART_RXPIN_BASE
#define UART_RXPIN_BASE         GPIOA
#endif

#ifndef UART_RXPIN_PCTL
#define UART_RXPIN_PCTL         0x1
#endif

#ifndef UART_RXPIN_POS
#define UART_RXPIN_POS          0
#endif

#ifndef UART_TXPIN_CLOCK_ENABLE
#define UART_TXPIN_CLOCK_ENABLE SYSCTL_RCGCGPIO_R0
#endif

#ifndef UART_TXPIN_BASE
#define UART_TXPIN_BASE         GPIOA
#endif

#ifndef UART_TXPIN_PCTL
#define UART_TXPIN_PCTL         0x1
#endif

#ifndef UART_TXPIN_POS
#define UART_TXPIN_POS          1
#endif

//*****************************************************************************
//
// This macro is used to generate a constant to represent the UART baud rate to
// processor clock rate ratio.  This prevents the need for run-time calculation
// of the ratio of baud rate to processor clock rate ratio.
//
//*****************************************************************************
#define UART_BAUD_RATIO(ui32Baud)                                             \
                                ((((CRYSTAL_FREQ * 8) / ui32Baud) + 1) / 2)

//*****************************************************************************
//
// This defines the UART receive pin that is being used by the boot loader.
//
//*****************************************************************************
#define UART_RX                 (1 << UART_RXPIN_POS)
#define UART_RX_PCTL            (UART_RXPIN_PCTL << (4 * UART_RXPIN_POS))

//*****************************************************************************
//
// This defines the UART transmit pin that is being used by the boot loader.
//
//*****************************************************************************
#define UART_TX                 (1 << UART_TXPIN_POS)
#define UART_TX_PCTL            (UART_TXPIN_PCTL << (4 * UART_TXPIN_POS))

//*****************************************************************************
//
// UART Transport APIs
//
//*****************************************************************************
extern void UARTSend(const uint8_t *pui8Data, uint32_t ui32Size);
extern void UARTReceive(uint8_t *pui8Data, uint32_t ui32Size);
extern void UARTFlush(void);
extern int UARTAutoBaud(uint32_t *pui32Ratio);

//*****************************************************************************
//
// Define the transport functions if the UART is being used.
//
//*****************************************************************************
#ifdef UART_ENABLE_UPDATE
#define SendData                UARTSend
#define FlushData               UARTFlush
#define ReceiveData             UARTReceive
#endif

#endif // __BL_UART_H__
