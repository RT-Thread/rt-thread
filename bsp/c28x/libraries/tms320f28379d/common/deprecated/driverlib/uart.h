//###########################################################################
//
// FILE:   uart.h
//
// TITLE:  Stellaris style wrapper driver for C28x SCI peripheral.
//
//###########################################################################
// $TI Release: F2837xD Support Library v3.05.00.00 $
// $Release Date: Tue Jun 26 03:15:23 CDT 2018 $
// $Copyright:
// Copyright (C) 2013-2018 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef __UART_H__
#define __UART_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Values that can be passed to UARTIntEnable, UARTIntDisable, and UARTIntClear
// as the ui32IntFlags parameter, and returned from UARTIntStatus.
//
//*****************************************************************************
#define UART_INT_RXERR          0x01
#define UART_INT_RXRDY_BRKDT    0x02
#define UART_INT_TXRDY          0x04
#define UART_INT_TXFF           0x08
#define UART_INT_RXFF           0x10

//*****************************************************************************
//
// Values that can be passed to UARTConfigSetExpClk as the ui32Config parameter
// and returned by UARTConfigGetExpClk in the pui32Config parameter.
// Additionally, the UART_CONFIG_PAR_* subset can be passed to
// UARTParityModeSet as the ui32Parity parameter, and are returned by
// UARTParityModeGet.
//
//*****************************************************************************
#define UART_CONFIG_WLEN_MASK   0x00000007  // Mask for extracting word length
#define UART_CONFIG_WLEN_8      0x00000007  // 8 bit data
#define UART_CONFIG_WLEN_7      0x00000006  // 7 bit data
#define UART_CONFIG_WLEN_6      0x00000005  // 6 bit data
#define UART_CONFIG_WLEN_5      0x00000004  // 5 bit data
#define UART_CONFIG_STOP_MASK   0x00000080  // Mask for extracting stop bits
#define UART_CONFIG_STOP_ONE    0x00000000  // One stop bit
#define UART_CONFIG_STOP_TWO    0x00000080  // Two stop bits
#define UART_CONFIG_PAR_MASK    0x00000060  // Parity Mask
#define UART_CONFIG_PAR_NONE    0x00000000  // No parity
#define UART_CONFIG_PAR_EVEN    0x00000060  // Even parity
#define UART_CONFIG_PAR_ODD     0x00000020  // Odd parity
#define UART_CONFIG_PAR_ONE     0x00000020  // Parity bit is one
#define UART_CONFIG_PAR_ZERO    0x00000060  // Parity bit is zero

//*****************************************************************************
//
// Values that can be passed to UARTFIFOLevelSet as the ui32TxLevel parameter and
// returned by UARTFIFOLevelGet in the pui32TxLevel.
//
//*****************************************************************************
#define UART_FIFO_TX1_8         0x00000001  // Transmit interrupt at 1/4 Full
#define UART_FIFO_TX2_8         0x00000002  // Transmit interrupt at 1/2 Full
#define UART_FIFO_TX4_8         0x00000003  // Transmit interrupt at 3/4 Full
#define UART_FIFO_TX6_8         0x00000004  // Transmit interrupt Full

//*****************************************************************************
//
// Values that can be passed to UARTFIFOLevelSet as the ui32RxLevel parameter and
// returned by UARTFIFOLevelGet in the pui32RxLevel.
//
//*****************************************************************************
#define UART_FIFO_RX1_8         0x00000001  // Receive interrupt at 1/4 Full
#define UART_FIFO_RX2_8         0x00000002  // Receive interrupt at 1/2 Full
#define UART_FIFO_RX4_8         0x00000003  // Receive interrupt at 3/4 Full
#define UART_FIFO_RX6_8         0x00000004  // Receive interrupt at Full

//*****************************************************************************
//
// Values that can be passed to UARTDMAEnable() and UARTDMADisable().
//
//*****************************************************************************
#define UART_DMA_ERR_RXSTOP     0x00000004  // Stop DMA receive if UART error
#define UART_DMA_TX             0x00000002  // Enable DMA for transmit
#define UART_DMA_RX             0x00000001  // Enable DMA for receive

//*****************************************************************************
//
// Values returned from UARTRxErrorGet().
//
//*****************************************************************************
#define UART_RXERROR_OVERRUN    0x00000008
#define UART_RXERROR_BREAK      0x00000020
#define UART_RXERROR_PARITY     0x00000004
#define UART_RXERROR_FRAMING    0x00000010

//*****************************************************************************
//
// Values that can be passed to UARTHandshakeOutputsSet() or returned from
// UARTHandshakeOutputGet().
//
//*****************************************************************************
#define UART_OUTPUT_RTS         0x00000800
#define UART_OUTPUT_DTR         0x00000400

//*****************************************************************************
//
// Values that can be returned from UARTHandshakeInputsGet().
//
//*****************************************************************************
#define UART_INPUT_RI           0x00000100
#define UART_INPUT_DCD          0x00000004
#define UART_INPUT_DSR          0x00000002
#define UART_INPUT_CTS          0x00000001

//*****************************************************************************
//
// Values that can be passed to UARTTxIntModeSet() or returned from
// UARTTxIntModeGet().
//
//*****************************************************************************
#define UART_TXINT_MODE_FIFO_M  0x0000001F
#define UART_TXINT_MODE_EOT     0x00000000

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
extern void UARTParityModeSet(uint32_t ui32Base, uint32_t ui32Parity);
extern uint32_t UARTParityModeGet(uint32_t ui32Base);
extern void UARTFIFOIntLevelSet(uint32_t ui32Base, uint32_t ui32TxLevel,
                             uint32_t ui32RxLevel);
extern void UARTFIFOIntLevelGet(uint32_t ui32Base, uint32_t *pui32TxLevel,
                             uint32_t *pui32RxLevel);
extern void UARTFIFOLevelGet(uint32_t ui32Base, uint32_t *pui32TxLevel,
                             uint32_t *pui32RxLevel);
extern void UARTConfigSetExpClk(uint32_t ui32Base, uint32_t ui32UARTClk,
                                uint32_t ui32Baud, uint32_t ui32Config);
extern void UARTConfigGetExpClk(uint32_t ui32Base, uint32_t ui32UARTClk,
                                uint32_t *pui32Baud, uint32_t *pui32Config);
extern void UARTEnable(uint32_t ui32Base);
extern void UARTDisable(uint32_t ui32Base);
extern void UARTsetLoopBack(uint32_t ui32Base, bool enable);
extern void UARTFIFOEnable(uint32_t ui32Base);
extern void UARTFIFODisable(uint32_t ui32Base);
extern bool UARTCharsAvail(uint32_t ui32Base);
extern bool UARTSpaceAvail(uint32_t ui32Base);
extern int32_t UARTCharGetNonBlocking(uint32_t ui32Base);
extern int32_t UARTCharGet(uint32_t ui32Base);
extern bool UARTCharPutNonBlocking(uint32_t ui32Base, unsigned char ucData);
extern void UARTCharPut(uint32_t ui32Base, unsigned char ucData);
extern bool UARTBusy(uint32_t ui32Base);
extern void UARTRXIntRegister(uint32_t ui32Base, void(*pfnHandler)(void));
extern void UARTTXIntRegister(uint32_t ui32Base, void(*pfnHandler)(void));
extern void UARTRXIntUnregister(uint32_t ui32Base);
extern void UARTTXIntUnregister(uint32_t ui32Base);
extern void UARTIntEnable(uint32_t ui32Base, uint32_t ui32IntFlags);
extern void UARTIntDisable(uint32_t ui32Base, uint32_t ui32IntFlags);
extern uint32_t UARTIntStatus(uint32_t ui32Base, bool bMasked);
extern void UARTIntClear(uint32_t ui32Base, uint32_t ui32IntFlags);
extern uint32_t UARTRxErrorGet(uint32_t ui32Base);
extern void UARTRxErrorClear(uint32_t ui32Base);
extern void UARTTxIntModeSet(uint32_t ui32Base, uint32_t ui32Mode);
extern uint32_t UARTTxIntModeGet(uint32_t ui32Base);


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  __UART_H__
