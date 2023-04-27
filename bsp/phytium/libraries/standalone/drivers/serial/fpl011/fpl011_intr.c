/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fpl011_intr.c
 * Date: 2021-11-02 14:53:42
 * LastEditTime: 2022-02-18 09:06:30
 * Description:  This file is for uart irq functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  huanghe 2021/11/2  first commit
 * 1.1  liushengming 2022/02/18  fix bugs
 */


/***************************** Include Files *********************************/

#include "fpl011.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/
/*****************************************************************************/

extern u32 FPl011SendBuffer(FPl011 *uart_p);
extern u32 FPl011ReceiveBuffer(FPl011 *uart_p);

static void FPl011ReceiveErrorHandler(FPl011 *uart_p, u32 InterruptStatus);
static void FPl011ReceiveDataHandler(FPl011 *uart_p);
static void FPl011ReceiveTimeoutHandler(FPl011 *uart_p);
static void FPl011SendDataHandler(FPl011 *uart_p, u32 InterruptStatus);

/**
 * @name: FPl011GetInterruptMask
 * @msg:  此函数获取所有串口中断的mask。
 * @param  uart_p
 * @return  mask
 */
/**
 * @name: FPl011GetInterruptMask
 * @msg:  This function gets the interrupt mask.
 * @param uart_p is a pointer to the uart instance
 * @return {*}
 */
u32 FPl011GetInterruptMask(FPl011 *uart_p)
{
    FASSERT(uart_p != NULL);
    return FUART_READREG32(uart_p->config.base_address, FPL011IMSC_OFFSET);
}


/**
 * @name: FPl011SetInterruptMask
 * @msg:  This function sets the interrupt mask.
 * @param uart_p is a pointer to the uart instance
 * @param mask contains the interrupts to be enabled or disabled.
 *      A '1' enables an interrupt, and a '0' disables.
 */
void FPl011SetInterruptMask(FPl011 *uart_p, u32 mask)
{
    u32 temp_mask = mask;
    FASSERT(uart_p != NULL);

    temp_mask &= FPL011IMSC_ALLM;

    FUART_WRITEREG32(uart_p->config.base_address, FPL011IMSC_OFFSET, temp_mask);
}

/**
 * @name: FPl011SetHandler
 * @msg:  This function sets the handler that will be called when an event (interrupt)
 * occurs that needs application's attention.
 * @param uart_p is a pointer to the uart instance
 * @param fun_p is the pointer to the callback function.
 * @param args is the upper layer callback reference passed back
 *      when the callback function is invoked.
 * @return {*}
 */
void FPl011SetHandler(FPl011 *uart_p, FPl011EventHandler fun_p, void *args)
{
    FASSERT(uart_p != NULL);
    FASSERT(fun_p != NULL);
    FASSERT(uart_p->is_ready == FT_COMPONENT_IS_READY);

    uart_p->handler = fun_p;
    uart_p->args = args;
}


/**
 * @name: FPl011InterruptHandler
 * @msg:  This function is the interrupt handler for the driver.
 *          It must be connected to an interrupt system by the application such that it
 *          can be called when an interrupt occurs.
 * @param vector Irq num ,Don't need attention .
 * @param param  contains a pointer to the driver instance
 */
void FPl011InterruptHandler(s32 vector, void *param)
{
    FPl011 *uart_p = (FPl011 *)param;
    u32 reg_value = 0;
    FASSERT(uart_p != NULL);
    FASSERT(uart_p->is_ready == FT_COMPONENT_IS_READY);

    reg_value = FUART_READREG32(uart_p->config.base_address, FPL011IMSC_OFFSET);
    reg_value &= FUART_READREG32(uart_p->config.base_address, FPL011MIS_OFFSET);

    if ((reg_value & ((u32)FPL011MIS_RXMIS)) != (u32)0)
    {
        /* Received data interrupt */
        FPl011ReceiveDataHandler(uart_p);
    }

    if ((reg_value & ((u32)FPL011MIS_TXMIS)) != (u32)0)
    {
        /* Transmit data interrupt */
        FPl011SendDataHandler(uart_p, reg_value);
    }

    if (((reg_value) & ((u32)FPL011MIS_OEMIS | (u32)FPL011MIS_BEMIS | (u32)FPL011MIS_PEMIS | (u32)FPL011MIS_FEMIS)) != (u32)0)
    {
        /* Received Error Status interrupt */
        FPl011ReceiveErrorHandler(uart_p, reg_value);
    }

    if ((reg_value & ((u32)FPL011MIS_RTMIS)) != (u32)0)
    {
        /* Received Timeout interrupt */
        FPl011ReceiveTimeoutHandler(uart_p);
    }

    if (((reg_value) & ((u32)FPL011MIS_DSRMMIS | (u32)FPL011MIS_DCDMMIS | (u32)FPL011MIS_CTSMMIS | (u32)FPL011MIS_RIMMIS)) != (u32)0)
    {
        /* Modem status interrupt */
    }

    /* Clear the interrupt status. */
    FUART_WRITEREG32(uart_p->config.base_address, FPL011ICR_OFFSET,
                     reg_value);

}

static void FPl011ReceiveErrorHandler(FPl011 *uart_p, u32 InterruptStatus)
{
    uart_p->rxbs_error = 0;

    if (((InterruptStatus) & ((u32)FPL011MIS_OEMIS | (u32)FPL011MIS_BEMIS | (u32)FPL011MIS_PEMIS | (u32)FPL011MIS_FEMIS)) != 0)
    {
        uart_p->rxbs_error = 1;
    }

    (void)FPl011ReceiveBuffer(uart_p);

    if (0 == uart_p->rxbs_error)
    {
        if (uart_p->handler)
        {
            uart_p->handler(uart_p->args, FPL011_EVENT_RECV_ERROR, uart_p->receive_buffer.requested_bytes - uart_p->receive_buffer.remaining_bytes);
        }
    }
}

/**
 * @name: FPl011ReceiveDataHandler
 * @msg:
 * @param {*}
 * @return {*}
 */
static void FPl011ReceiveDataHandler(FPl011 *uart_p)
{
    if ((u32)0 != uart_p->receive_buffer.remaining_bytes)
    {
        (void)FPl011ReceiveBuffer(uart_p);
    }
    if ((u32)0 == uart_p->receive_buffer.remaining_bytes)
    {
        if (uart_p->handler)
        {
            uart_p->handler(uart_p->args, FPL011_EVENT_RECV_DATA, uart_p->receive_buffer.requested_bytes - uart_p->receive_buffer.remaining_bytes);
        }
    }
}

static void FPl011ReceiveTimeoutHandler(FPl011 *uart_p)
{
    u32 event;

    if ((u32)0 != uart_p->receive_buffer.remaining_bytes)
    {
        (void)FPl011ReceiveBuffer(uart_p);
    }
    if ((u32)0 == uart_p->receive_buffer.remaining_bytes)
    {
        event = FPL011_EVENT_RECV_TOUT;
    }
    else
    {
        event = FPL011_EVENT_RECV_DATA;
    }

    if (uart_p->handler)
    {
        uart_p->handler(uart_p->args, event, uart_p->receive_buffer.requested_bytes - uart_p->receive_buffer.remaining_bytes);
    }
}

static void FPl011SendDataHandler(FPl011 *uart_p, u32 InterruptStatus)
{
    FPl011SendBuffer(uart_p);
    if (uart_p->send_buffer.remaining_bytes == (u32)0)
    {
        if (uart_p->handler)
        {
            uart_p->handler(uart_p->args, FPL011_EVENT_SENT_DATA, uart_p->send_buffer.requested_bytes);
        }
    }
}
