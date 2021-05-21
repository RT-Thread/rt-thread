/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 15:40:07
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_os_uart.h"
#include "ft_uart.h"
#include "ft_printf.h"
#include "system_gic.h"
#include "ft_types.h"
#include "ft_status.h"

extern u32 FUart_GetInterruptMask(Ft_Uart *UartPtr);
extern void FUart_SetInterruptMask(Ft_Uart *UartPtr, u32 Mask);

/* Callback events  */

static void Ft_Os_Uart_Callback(void *Args, u32 Event, u32 EventData)
{
    Ft_Os_Uart *OsUartPtr = (Ft_Os_Uart *)Args;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t xResult = pdFALSE;
    u32 RegTemp;
    if (FUART_EVENT_RECV_DATA == Event || FUART_EVENT_RECV_TOUT == Event)
    {
        xResult = xEventGroupSetBitsFromISR(OsUartPtr->rxEvent, RTOS_UART_COMPLETE, &xHigherPriorityTaskWoken);
    }
    else if (FUART_EVENT_RECV_ERROR == Event)
    {
        xResult = xEventGroupSetBitsFromISR(OsUartPtr->rxEvent, RTOS_UART_RECV_ERROR, &xHigherPriorityTaskWoken);
    }
    else if (FUART_EVENT_SENT_DATA == Event)
    {

        xResult = xEventGroupSetBitsFromISR(OsUartPtr->txEvent, RTOS_UART_RECV_ERROR, &xHigherPriorityTaskWoken);
    }
    else if (FUART_EVENT_PARE_FRAME_BRKE == Event)
    {
        xResult = xEventGroupSetBitsFromISR(OsUartPtr->rxEvent, RTOS_UART_RECV_ERROR, &xHigherPriorityTaskWoken);
    }
    else if (FUART_EVENT_RECV_ORERR == Event)
    {
    }

    if (FUART_EVENT_SENT_DATA == Event)
    {
    }
    else
    {
        //<! 关闭接收中断
        RegTemp = FUart_GetInterruptMask(&OsUartPtr->UartObj);
        RegTemp &= ~UARTMIS_RTMIS;
        FUart_SetInterruptMask(&OsUartPtr->UartObj, RegTemp);
    }

    if (xResult != pdFAIL)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void Ft_Os_UartInit(Ft_Os_Uart *OsUartPtr, Ft_Os_Uart_Config *Config)
{
    Ft_Uart *UartPtr = NULL;
    Ft_assertVoid(OsUartPtr != NULL);
    Ft_assertVoid(Config != NULL);
    UartPtr = &OsUartPtr->UartObj;
    Ft_printf("OsUartPtr %x", OsUartPtr);
    Ft_assertVoid(FUart_CfgInitialize(UartPtr, FUart_LookupConfig(Config->Uart_Instance)) == FST_SUCCESS);
    FUart_SetHandler(UartPtr, Ft_Os_Uart_Callback, OsUartPtr);
    Ft_assertVoid((OsUartPtr->rxSemaphore = xSemaphoreCreateMutex()) != NULL);
    Ft_assertVoid((OsUartPtr->txSemaphore = xSemaphoreCreateMutex()) != NULL);
    Ft_assertVoid((OsUartPtr->txEvent = xEventGroupCreate()) != NULL);
    Ft_assertVoid((OsUartPtr->rxEvent = xEventGroupCreate()) != NULL);
    System_Gic_Enable(OsUartPtr->UartObj.Config.IsrNum, (FGicv3_InterruptHandler_t)FUart_InterruptHandler, Config->Isr_Priority, UartPtr);
    FUart_SetOptions(UartPtr, FUART_OPTION_UARTEN | FUART_OPTION_RXEN | FUART_OPTION_TXEN | FUART_OPTION_FIFOEN);
}

/**
 * @name: Ft_Os_ReceiveBuffer
 * @msg: 
 * @param {Ft_Os_Uart} *OsUartPtr
 * @param {u8} *buffer
 * @param {u32} length
 * @param {u32} *Received
 * @return {*}
 */
s32 Ft_Os_UartReceiveBuffer(Ft_Os_Uart *OsUartPtr, u8 *buffer, u32 length, u32 *Received)
{
    u32 GetLength;
    Ft_Uart *UartPtr;
    EventBits_t ev;
    s32 ret;
    if (NULL == OsUartPtr)
    {
        return FST_INSTANCE_NOT_FOUND;
    }

    if (NULL == buffer)
    {
        return FST_FAILURE;
    }

    if (NULL == Received)
    {
        return FST_FAILURE;
    }

    if (0 == length)
    {
        *Received = 0;
        return FST_SUCCESS;
    }

    UartPtr = &OsUartPtr->UartObj;

    /* New transfer can be performed only after current one is finished */
    if (pdFALSE == xSemaphoreTake(OsUartPtr->rxSemaphore, portMAX_DELAY))
    {
        /* We could not take the semaphore, exit with 0 data received */
        ret = FST_FAILURE;
    }

    GetLength = FUart_Receive(UartPtr, buffer, length);
    if (GetLength > 0)
    {
        *Received = GetLength;
        ret = FST_SUCCESS;
    }
    else
    {
        u32 RegTemp;

        RegTemp = FUart_GetInterruptMask(UartPtr);
        RegTemp |= UARTMIS_RTMIS;
        FUart_SetInterruptMask(UartPtr, RegTemp);

        ev = xEventGroupWaitBits(OsUartPtr->rxEvent,
                                 RTOS_UART_COMPLETE | RTOS_UART_HARDWARE_BUFFER_OVERRUN | RTOS_UART_RECV_ERROR,
                                 pdTRUE, pdFALSE, portMAX_DELAY);

        if (ev & RTOS_UART_HARDWARE_BUFFER_OVERRUN)
        {
            ret = FST_FIFO_ERROR;
            *Received = 0;
        }
        else if (ev & RTOS_UART_COMPLETE)
        {
            ret = FST_SUCCESS;
            *Received = UartPtr->ReceiveBuffer.RequestedBytes - UartPtr->ReceiveBuffer.RemainingBytes;
        }
        else if (ev & RTOS_UART_RECV_ERROR)
        {
            ret = FST_RECV_ERROR;
            *Received = 0;
        }
        else
        {
            ret = FST_INVALID_PARAM;
            *Received = 0;
        }
    }

    /* Enable next transfer. Current one is finished */
    if (pdFALSE == xSemaphoreGive(OsUartPtr->rxSemaphore))
    {
        /* We could not post the semaphore, exit with error */
        Ft_printf("FST_FAILURE xSemaphoreGive \r\n");
        ret = FST_FAILURE;
    }

    return ret;
}

/**
 * @name: 
 * @msg: 
 * @param {Ft_Os_Uart} *OsUartPtr
 * @param {u8} *buffer
 * @param {u32} length
 * @return {*}
 */
s32 Ft_Os_UartBlockingSend(Ft_Os_Uart *OsUartPtr, u8 *buffer, u32 length)
{
    s32 ret = FST_SUCCESS;
    Ft_Uart *UartPtr;
    EventBits_t ev;
    if (NULL == OsUartPtr)
    {
        return FST_INSTANCE_NOT_FOUND;
    }

    if (NULL == buffer)
    {
        return FST_FAILURE;
    }

    UartPtr = &OsUartPtr->UartObj;

    if (pdFALSE == xSemaphoreTake(OsUartPtr->txSemaphore, portMAX_DELAY))
    {
        return FST_FAILURE;
    }

    FUart_Send(UartPtr, buffer, length);

    ev = xEventGroupWaitBits(OsUartPtr->txEvent, RTOS_UART_COMPLETE, pdTRUE, pdFALSE, portMAX_DELAY);
    if (!(ev & RTOS_UART_COMPLETE))
    {
        ret = FST_FAILURE;
    }

    if (pdFALSE == xSemaphoreGive(OsUartPtr->txSemaphore))
    {
        /* We could not post the semaphore, exit with error */
        ret = FST_FAILURE;
    }

    return ret;
}