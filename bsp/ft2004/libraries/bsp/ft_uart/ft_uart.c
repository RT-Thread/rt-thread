/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-24 10:48:22
 * @Description:  This files is for uart functions
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

/***************************** Include Files ********************************/

#include "ft_status.h"
#include "ft_uart.h"
#include "ft_io.h"
#include "ft_error_code.h"

u32 FUart_SendBuffer(Ft_Uart *UartPtr);
u32 FUart_ReceiveBuffer(Ft_Uart *UartPtr);

static void FUart_StubHandler(void *Args, u32 Event,
                              u32 ByteCount);

/**
 * @name: FUart_CfgInitialize
 * @msg: initalize uart configure
 * @return {*}
 * @param {Ft_Uart} *UartPtr
 * @param {FUart_Config_t} *Config
 */
s32 FUart_CfgInitialize(Ft_Uart *UartPtr, FUart_Config_t *Config)
{
    u32 RegValue = 0;

    Ft_assertNonvoid(UartPtr != NULL);
    Ft_assertNonvoid(Config != NULL);

    UartPtr->Config.InstanceId = Config->InstanceId;
    UartPtr->Config.BaseAddress = Config->BaseAddress;
    UartPtr->Config.RefClockHz = Config->RefClockHz;
    UartPtr->Config.IsrNum = Config->IsrNum;

    UartPtr->Handler = FUart_StubHandler;

    UartPtr->SendBuffer.BytePtr = NULL;
    UartPtr->SendBuffer.RequestedBytes = 0;
    UartPtr->SendBuffer.RemainingBytes = 0;

    UartPtr->ReceiveBuffer.BytePtr = NULL;
    UartPtr->ReceiveBuffer.RequestedBytes = 0;
    UartPtr->ReceiveBuffer.RemainingBytes = 0;
    UartPtr->rxbs_error = 0;
    UartPtr->IsReady = FT_COMPONENT_IS_READLY;
    //<! 设置波特率

    /*
         * Set up the default data format: 8 bit data, 1 stop bit, no
         * parity
         */
    RegValue = ((FUART_FORMAT_WORDLENGTH_8BIT << 5) & UARTLCR_H_WLEN); //<! 8bit word length
    RegValue |= (0 << 3) & UARTLCR_H_STP2;                             //<! 1 stopbit
    RegValue |= (0 << 1) & UARTLCR_H_PEN;                              //<! no parity
    RegValue |= (1 << 4) & UARTLCR_H_FEN;                              //<! fifo en
    FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTLCR_H_OFFSET, RegValue);

    /* Set the RX FIFO trigger at 8 data bytes.Tx FIFO trigger is 8 data bytes*/
    RegValue = (1 << 3) | (1 << 0);
    FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTIFLS_OFFSET, RegValue);

    /* Disable all interrupts, polled mode is the default */
    RegValue = 0;
    FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTIMSC_OFFSET, RegValue);
    return FST_SUCCESS;
}

/**
 * @name: FUart_Send
 * @msg:
 * @param {Ft_Uart} *UartPtr
 * @param {u8} *Buffer
 * @param {u32} Length
 * @return {u32} The Number of bytes actully sent.
 */
u32 FUart_Send(Ft_Uart *UartPtr, u8 *BytePtr, u32 Length)
{
    u32 RegValue = 0;
    u32 SentCount = 0;
    Ft_assertNonvoid(UartPtr != NULL);
    Ft_assertNonvoid(BytePtr != NULL);
    Ft_assertNonvoid(UartPtr->IsReady == FT_COMPONENT_IS_READLY);

    /*
     * Disable the UART transmit interrupts to allow this call to stop a
     * previous operation that may be interrupt driven.
     */
    RegValue = FT_UART_ReadReg(UartPtr->Config.BaseAddress, UARTIMSC_OFFSET);
    RegValue &= ~(UARTIMSC_TXIM);
    FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTIMSC_OFFSET, RegValue);

    UartPtr->SendBuffer.BytePtr = BytePtr;
    UartPtr->SendBuffer.RequestedBytes = Length;
    UartPtr->SendBuffer.RemainingBytes = Length;

    SentCount = FUart_SendBuffer(UartPtr);

    return SentCount;
}

/**
 * @name: FUart_PutChar
 * @msg: send a char through uart
 * @return {*}
 * @param {Ft_Uart} *UartPtr
 * @param {s8} Data
 */
void FUart_PutChar(Ft_Uart *UartPtr, s8 Data)
{
    Ft_assertVoid(UartPtr != NULL);
    Ft_assertVoid(UartPtr->IsReady == FT_COMPONENT_IS_READLY);

    while (!FT_UART_IsTransmitFull(UartPtr->Config.BaseAddress))
    {
        FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTDR_OFFSET, Data);
        break;
    }
}

static void FUart_StubHandler(void *Args, u32 Event,
                              u32 ByteCount)
{
    (void)Args;
    (void)Event;
    (void)ByteCount;

    Ft_assertVoidAlways();
}

/**
 * @name: FUart_SendBuffer
 * @msg: send data buffer through uart
 * @return {*}
 * @param {Ft_Uart} *UartPtr
 */
u32 FUart_SendBuffer(Ft_Uart *UartPtr)
{
    u32 SentCount = 0U;
    u32 RegValue;

    /*
     * If the TX FIFO is full, send nothing.
     * Otherwise put bytes into the TX FIFO unil it is full, or all of the
     * data has been put into the FIFO.
     */
    while ((!FT_UART_IsTransmitFull(UartPtr->Config.BaseAddress)) && (UartPtr->SendBuffer.RemainingBytes > SentCount))
    {
        FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTDR_OFFSET, (u32)UartPtr->SendBuffer.BytePtr[SentCount]);
        SentCount++;
    }

    /* Update the buffer to reflect the bytes that were sent from it */
    UartPtr->SendBuffer.BytePtr += SentCount;
    UartPtr->SendBuffer.RemainingBytes -= SentCount;

    RegValue = FT_UART_ReadReg(UartPtr->Config.BaseAddress, UARTIMSC_OFFSET);
    RegValue |= (UARTIMSC_TXIM);
    FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTIMSC_OFFSET, RegValue);

    return SentCount;
}

/**
 * @name: FUart_Receive
 * @msg: receive data through uart
 * @return {*}
 * @param {Ft_Uart} *UartPtr
 * @param {u8} *BytePtr
 * @param {u32} Length
 */
u32 FUart_Receive(Ft_Uart *UartPtr, u8 *BytePtr, u32 Length)
{
    u32 Received;
    u32 BackRegValue;

    Ft_assertNonvoid(UartPtr != NULL);
    Ft_assertNonvoid(BytePtr != NULL);
    Ft_assertNonvoid(UartPtr->IsReady == FT_COMPONENT_IS_READLY);

    /*
     * Disable all the interrupts.
     * This stops a previous operation that may be interrupt driven
     */
    BackRegValue = FT_UART_ReadReg(UartPtr->Config.BaseAddress, UARTIMSC_OFFSET);
    FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTIMSC_OFFSET, 0);

    UartPtr->ReceiveBuffer.BytePtr = BytePtr;
    UartPtr->ReceiveBuffer.RequestedBytes = Length;
    UartPtr->ReceiveBuffer.RemainingBytes = Length;

    Received = FUart_ReceiveBuffer(UartPtr);
    FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTIMSC_OFFSET, BackRegValue);

    return Received;
}

/**
 * @name: Ft_Uart_ReceiveBuffer
 * @msg: handling uart receive buffer
 * @return {*}
 * @param {Ft_Uart} *UartPtr
 */
u32 FUart_ReceiveBuffer(Ft_Uart *UartPtr)
{

    u32 ReceivedCount = 0U;
    u32 Event;
    u32 EventData;
    u32 ByteValue;

    while ((ReceivedCount < UartPtr->ReceiveBuffer.RemainingBytes) && !FT_UART_IsReceiveData(UartPtr->Config.BaseAddress))
    {
        ByteValue = FT_UART_ReadReg(UartPtr->Config.BaseAddress, UARTDR_OFFSET);

        if (UartPtr->rxbs_error)
        {
            if ((ByteValue & UARTDR_ALLE) != 0)
            {
                EventData = ByteValue;
                Event = FUART_EVENT_PARE_FRAME_BRKE;

                if (UartPtr->Handler)
                {
                    UartPtr->Handler(UartPtr->Args, Event, EventData);
                }
            }
        }
        UartPtr->ReceiveBuffer.BytePtr[ReceivedCount] = (u8)(ByteValue & 0xff);
        ReceivedCount++;
    }

    UartPtr->rxbs_error = 0;

    if (UartPtr->ReceiveBuffer.BytePtr != NULL)
    {
        UartPtr->ReceiveBuffer.BytePtr += ReceivedCount;
    }
    UartPtr->ReceiveBuffer.RemainingBytes -= ReceivedCount;

    return ReceivedCount;
}

/**
 * @name: FUart_BlockSend
 * @msg: initiate uart block send
 * @return {*}
 * @param {Ft_Uart} *UartPtr
 * @param {u8} *BytePtr
 * @param {u32} Length
 */
void FUart_BlockSend(Ft_Uart *UartPtr, u8 *BytePtr, u32 Length)
{
    u32 index;

    Ft_assertVoid(UartPtr != NULL);
    Ft_assertVoid(BytePtr != NULL);
    Ft_assertVoid(UartPtr->IsReady == FT_COMPONENT_IS_READLY);

    for (index = 0; index < Length; index++)
    {
        FUart_SendByte(UartPtr->Config.BaseAddress, BytePtr[index]);
    }
}

/**
 * @name: FUart_BlockReceive
 * @msg: initiate uart block receive
 * @return {*}
 * @param {Ft_Uart} *UartPtr
 */
u8 FUart_BlockReceive(Ft_Uart *UartPtr)
{
    Ft_assertNonvoid(UartPtr != NULL);
    Ft_assertNonvoid(UartPtr->IsReady == FT_COMPONENT_IS_READLY);
    return FUart_RecvByte(UartPtr->Config.BaseAddress);
}

/**
 * @name: FUart_SetBaudRate
 * @msg: set baudrate of UART trans
 * @return {*}
 * @param {Ft_Uart} *UartPtr
 * @param {u32} BaudRate
 */
u32 FUart_SetBaudRate(Ft_Uart *UartPtr, u32 BaudRate)
{
    u32 temp;
    u32 divider;
    u32 remainder;
    u32 fraction;

    Ft_assertNonvoid(NULL != UartPtr);
    if ((BaudRate * 2) > UartPtr->Config.RefClockHz)
    {
        return ERR_INPUT_BAUD_NO_SUPPORT;
    }

    /* calculate baud rate divisor */
    temp = 16 * BaudRate;
    divider = UartPtr->Config.RefClockHz / temp;
    remainder = UartPtr->Config.RefClockHz % temp;
    temp = (128 * remainder) / temp;
    fraction = temp / 2;

    if (0 != (temp & 1))
    {
        fraction++;
    }

    FUart_ClearSpecificOptions(UartPtr, FUART_OPTION_RXEN | FUART_OPTION_TXEN);
    /* set baud register */
    FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTIBRD_OFFSET, divider);
    FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTFBRD_OFFSET, fraction);
    FUart_SetSpecificOptions(UartPtr, FUART_OPTION_RXEN | FUART_OPTION_TXEN);

    return ERR_SUCCESS;
}
