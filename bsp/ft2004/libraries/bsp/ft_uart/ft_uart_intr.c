/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-25 16:49:42
 * @Description:  This files is for uart irq functions
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_uart.h"

extern u32 FUart_SendBuffer(Ft_Uart *UartPtr);
extern u32 FUart_ReceiveBuffer(Ft_Uart *UartPtr);

static void FUart_receiveErrorHandler(Ft_Uart *UartPtr, u32 InterruptStatus);
static void FUart_receiveDataHandler(Ft_Uart *UartPtr);
static void FUart_receiveTimeoutHandler(Ft_Uart *UartPtr);
static void FUart_sendDataHandler(Ft_Uart *UartPtr, u32 InterruptStatus);

/**
 * @name: FUart_GetInterruptMask
 * @msg:  此函数获取所有串口中断的mask。
 * @param {Ft_Uart} *UartPtr
 * @return {u32} mask
 */
u32 FUart_GetInterruptMask(Ft_Uart *UartPtr)
{
    Ft_assertNonvoid(UartPtr != NULL);

    return FT_UART_ReadReg(UartPtr->Config.BaseAddress, UARTIMSC_OFFSET);
}

void FUart_SetInterruptMask(Ft_Uart *UartPtr, u32 Mask)
{
    u32 TempMask = Mask;
    Ft_assertVoid(UartPtr != NULL);

    TempMask &= UARTIMSC_ALLM;

    FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTIMSC_OFFSET, TempMask);
}

/**
 * @name: FUart_SetHandler
 * @msg:  设置中断回调函数
 * @param {*}
 * @return {*}
 */
void FUart_SetHandler(Ft_Uart *UartPtr, FUart_Handler_t FuncPtr,
                      void *Args)
{
    Ft_assertVoid(UartPtr != NULL);
    Ft_assertVoid(FuncPtr != NULL);
    Ft_assertVoid(UartPtr->IsReady == FT_COMPONENT_IS_READLY);

    UartPtr->Handler = FuncPtr;
    UartPtr->Args = Args;
}

/**
 * @name: FUart_InterruptHandler
 * @msg:  串口中断函数入口
 * @param {Ft_Uart} *UartPtr
 * @return {*}
 */
void FUart_InterruptHandler(Ft_Uart *UartPtr)
{
    u32 RegValue = 0;
    Ft_assertVoid(UartPtr != NULL);
    Ft_assertVoid(UartPtr->IsReady == FT_COMPONENT_IS_READLY);
    //Ft_printf("FUart_InterruptHandler %x\r\n", UartPtr);
    RegValue = FT_UART_ReadReg(UartPtr->Config.BaseAddress, UARTIMSC_OFFSET);

    RegValue &= FT_UART_ReadReg(UartPtr->Config.BaseAddress, UARTMIS_OFFSET);

    if ((RegValue & ((u32)UARTMIS_RXMIS)) != (u32)0)
    {
        /* Received data interrupt */
        FUart_receiveDataHandler(UartPtr);
    }

    if ((RegValue & ((u32)UARTMIS_TXMIS)) != (u32)0)
    {
        /* Transmit data interrupt */
        FUart_sendDataHandler(UartPtr, RegValue);
    }

    if (((RegValue) & ((u32)UARTMIS_OEMIS | (u32)UARTMIS_BEMIS | (u32)UARTMIS_PEMIS | (u32)UARTMIS_FEMIS)) != (u32)0)
    {
        /* Received Error Status interrupt */
        FUart_receiveErrorHandler(UartPtr, RegValue);
    }

    if ((RegValue & ((u32)UARTMIS_RTMIS)) != (u32)0)
    {
        /* Received Timeout interrupt */
        FUart_receiveTimeoutHandler(UartPtr);
    }

    if (((RegValue) & ((u32)UARTMIS_DSRMMIS | (u32)UARTMIS_DCDMMIS | (u32)UARTMIS_CTSMMIS | (u32)UARTMIS_RIMMIS)) != (u32)0)
    {
        /* Modem status interrupt */
    }

    /* Clear the interrupt status. */
    FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTICR_OFFSET,
                     RegValue);
}

static void FUart_receiveErrorHandler(Ft_Uart *UartPtr, u32 InterruptStatus)
{
    UartPtr->rxbs_error = 0;

    if (((InterruptStatus) & ((u32)UARTMIS_OEMIS | (u32)UARTMIS_BEMIS | (u32)UARTMIS_PEMIS | (u32)UARTMIS_FEMIS)) != 0)
    {
        UartPtr->rxbs_error = 1;
    }

    (void)FUart_ReceiveBuffer(UartPtr);

    if (0 == UartPtr->rxbs_error)
    {
        if (UartPtr->Handler)
        {
            UartPtr->Handler(UartPtr->Args, FUART_EVENT_RECV_ERROR, UartPtr->ReceiveBuffer.RequestedBytes - UartPtr->ReceiveBuffer.RemainingBytes);
        }
    }
}

static void FUart_receiveDataHandler(Ft_Uart *UartPtr)
{
    if ((u32)0 != UartPtr->ReceiveBuffer.RemainingBytes)
    {
        (void)FUart_ReceiveBuffer(UartPtr);
    }

    if ((u32)0 == UartPtr->ReceiveBuffer.RemainingBytes)
    {
        if (UartPtr->Handler)
        {
            UartPtr->Handler(UartPtr->Args, FUART_EVENT_RECV_DATA, UartPtr->ReceiveBuffer.RequestedBytes - UartPtr->ReceiveBuffer.RemainingBytes);
        }
    }
}

static void FUart_receiveTimeoutHandler(Ft_Uart *UartPtr)
{
    u32 Event;

    if ((u32)0 != UartPtr->ReceiveBuffer.RemainingBytes)
    {
        (void)FUart_ReceiveBuffer(UartPtr);
    }

    if ((u32)0 == UartPtr->ReceiveBuffer.RemainingBytes)
    {
        Event = FUART_EVENT_RECV_TOUT;
    }
    else
    {
        Event = FUART_EVENT_RECV_DATA;
    }

    if (UartPtr->Handler)
    {
        UartPtr->Handler(UartPtr->Args, Event, UartPtr->ReceiveBuffer.RequestedBytes - UartPtr->ReceiveBuffer.RemainingBytes);
    }
}

static void FUart_sendDataHandler(Ft_Uart *UartPtr, u32 InterruptStatus)
{
    u32 RegValue;
    if (UartPtr->SendBuffer.RemainingBytes == (u32)0)
    {
        //<! close send isr
        RegValue = FT_UART_ReadReg(UartPtr->Config.BaseAddress, UARTIMSC_OFFSET);
        RegValue &= ~UARTIMSC_TXIM;
        FT_UART_WriteReg(UartPtr->Config.BaseAddress, UARTIMSC_OFFSET, RegValue);
        if (UartPtr->Handler)
        {
            UartPtr->Handler(UartPtr->Args, FUART_EVENT_RECV_DATA, UartPtr->ReceiveBuffer.RequestedBytes - UartPtr->ReceiveBuffer.RemainingBytes);
        }
    }
    else if (InterruptStatus & UARTMIS_TXMIS)
    {
        FUart_SendBuffer(UartPtr);
    }
    else
    {
    }
}
