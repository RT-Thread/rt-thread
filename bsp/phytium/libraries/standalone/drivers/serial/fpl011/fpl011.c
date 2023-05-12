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
 * FilePath: fpl011.c
 * Date: 2021-11-02 14:53:42
 * LastEditTime: 2022-02-18 09:07:24
 * Description:  This file is for uart functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  huanghe 2021/11/2  first commit
 * 1.1  liushengming 2022/02/18  fix bug
 */

/***************************** Include Files ********************************/
#include "fpl011.h"
#include "fio.h"
#include "ferror_code.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

u32 FPl011SendBuffer(FPl011 *uart_p);
u32 FPl011ReceiveBuffer(FPl011 *uart_p);

static void FPl011StubHandler(void *Args, u32 Event,
                              u32 ByteCount);
/*****************************************************************************/


FError FPl011CfgInitialize(FPl011 *uart_p, FPl011Config *config)
{
    u32 reg_value = 0;
    FError ret ;
    FASSERT(uart_p != NULL);
    FASSERT(config != NULL);

    uart_p->config.instance_id = config->instance_id;
    uart_p->config.base_address = config->base_address;
    uart_p->config.ref_clock_hz = config->ref_clock_hz;
    uart_p->config.irq_num = config->irq_num;
    uart_p->config.baudrate = config->baudrate;

    uart_p->handler = FPl011StubHandler;

    uart_p->send_buffer.byte_p = NULL;
    uart_p->send_buffer.requested_bytes = 0;
    uart_p->send_buffer.remaining_bytes = 0;

    uart_p->receive_buffer.byte_p = NULL;
    uart_p->receive_buffer.requested_bytes = 0;
    uart_p->receive_buffer.remaining_bytes = 0;
    uart_p->rxbs_error = 0;

    uart_p->is_ready = FT_COMPONENT_IS_READY;
    ret = FPl011SetBaudRate(uart_p, uart_p->config.baudrate);
    if (ret != FT_SUCCESS)
    {
        uart_p->is_ready = 0U;
    }
    else
    {
        /*
        * Set up the default data format: 8 bit data, 1 stop bit, no
        * parity
        */
        reg_value = ((FPL011_FORMAT_WORDLENGTH_8BIT << 5) & FPL011LCR_H_WLEN); //<! 8bit word length
        reg_value |= (0 << 3) & FPL011LCR_H_STP2;                             //<! 1 stopbit
        reg_value |= (0 << 1) & FPL011LCR_H_PEN;                              //<! no parity
        reg_value |= (1 << 4) & FPL011LCR_H_FEN;                              //<! fifo en
        FUART_WRITEREG32(uart_p->config.base_address, FPL011LCR_H_OFFSET, reg_value);

        /* Set the RX FIFO trigger at 8 data bytes.Tx FIFO trigger is 8 data bytes*/
        reg_value = (1 << 3) | (1 << 0);
        FUART_WRITEREG32(uart_p->config.base_address, FPL011IFLS_OFFSET, reg_value);

        /* Disable all interrupts, polled mode is the default */
        reg_value = 0;
        FUART_WRITEREG32(uart_p->config.base_address, FPL011IMSC_OFFSET, reg_value);
    }

    return FT_SUCCESS;
}


/**
 * @name: FPl011Send
 * @msg: This functions sends the specified buffer using the device in either
 * polled or interrupt driven mode.
 * @return  The number of bytes actually sent.
 * @param uart_p is a pointer to the FPl011 instance.
 * @param byte_p  is pointer to a buffer of data to be sent.
 * @param  length  ontains the number of bytes to be sent. Any data that was already put into the
 *      transmit FIFO will be sent.
 */
u32 FPl011Send(FPl011 *uart_p, u8 *byte_p, u32 length)
{
    u32 sent_count = 0;
    FASSERT(uart_p != NULL);
    FASSERT(byte_p != NULL);
    FASSERT(uart_p->is_ready == FT_COMPONENT_IS_READY);

    uart_p->send_buffer.byte_p = byte_p;
    uart_p->send_buffer.requested_bytes = length;
    uart_p->send_buffer.remaining_bytes = length;
    sent_count = FPl011SendBuffer(uart_p);
    return sent_count;
}



static void FPl011StubHandler(void *args, u32 event,
                              u32 byte_count)
{
    (void)args;
    (void)event;
    (void)byte_count;

    FASSERT(0);
}

/**
 * @name: FPl011SendBuffer
 * @msg: send data buffer through uart,if you close FIFO and open interrupt,recommend use FPl011BlockSend
 * @return {*}
 * @param  uart_p
 */
u32 FPl011SendBuffer(FPl011 *uart_p)
{
    u32 sent_count = 0U;
    u32 isbusy;

    isbusy = (u32)FUART_ISTRANSMITBUSY(uart_p->config.base_address);
    while (isbusy == TRUE)
    {
        isbusy = (u32)FUART_ISTRANSMITBUSY(uart_p->config.base_address);
    }

    /*
     * If the TX FIFO is full, send nothing.
     * Otherwise put bytes into the TX FIFO unil it is full, or all of the
     * data has been put into the FIFO.
     */
    while ((!FUART_ISTRANSMITFULL(uart_p->config.base_address)) && (uart_p->send_buffer.remaining_bytes > 0))
    {
        sent_count = uart_p->send_buffer.requested_bytes - uart_p->send_buffer.remaining_bytes;
        uart_p->send_buffer.remaining_bytes--;

        FUART_WRITEREG32(uart_p->config.base_address, FPL011DR_OFFSET, (u32)uart_p->send_buffer.byte_p[sent_count]);
    }
    return uart_p->send_buffer.requested_bytes - uart_p->send_buffer.remaining_bytes;
}

/**
 * @name: FPl011Receive
 * @msg:  This function attempts to receive a specified number of bytes of data
 * from the device and store it into the specified buffer.
 * @param  uart_p is a pointer to the FPl011 instance
 * @param  byte_p is pointer to buffer for data to be received into
 * @param  length is the number of bytes to be received.
 * @return The number of bytes received.
 */
u32 FPl011Receive(FPl011 *uart_p, u8 *byte_p, u32 length)
{
    u32 received;

    FASSERT(uart_p != NULL);
    FASSERT(byte_p != NULL);
    FASSERT(uart_p->is_ready == FT_COMPONENT_IS_READY);

    uart_p->receive_buffer.byte_p          = byte_p;
    uart_p->receive_buffer.requested_bytes = length;
    uart_p->receive_buffer.remaining_bytes = length;

    received = FPl011ReceiveBuffer(uart_p);

    return received;
}


u32 FPl011ReceiveBuffer(FPl011 *uart_p)
{

    u32 received_count = 0U;
    u32 event;
    u32 event_data;
    u32 byte_value;

    while ((received_count < uart_p->receive_buffer.remaining_bytes) && !FUART_RECEIVEDATAEMPTY(uart_p->config.base_address))
    {
        byte_value = FUART_READREG32(uart_p->config.base_address, FPL011DR_OFFSET);

        if (uart_p->rxbs_error)
        {
            if ((byte_value & FPL011DR_ALLE) != 0)
            {
                event_data = byte_value;
                event = FPL011_EVENT_PARE_FRAME_BRKE;

                if (uart_p->handler)
                {
                    uart_p->handler(uart_p->args, event, event_data);
                }
            }
        }
        uart_p->receive_buffer.byte_p[received_count] = (u8)(byte_value & 0xff);
        received_count++;
    }

    uart_p->rxbs_error = 0;

    if (uart_p->receive_buffer.byte_p != NULL)
    {
        uart_p->receive_buffer.byte_p += received_count;
    }
    uart_p->receive_buffer.remaining_bytes -= received_count;

    return received_count;
}

/**
 * @name: FPl011BlockSend
 * @msg: initiate uart block send
 * @return {*}
 * @param  uart_p
 * @param  byte_p
 * @param  length
 */
void FPl011BlockSend(FPl011 *uart_p, u8 *byte_p, u32 length)
{
    u32 index;

    FASSERT(uart_p != NULL);
    FASSERT(byte_p != NULL);
    FASSERT(uart_p->is_ready == FT_COMPONENT_IS_READY);

    for (index = 0; index < length; index++)
    {
        FPl011SendByte(uart_p->config.base_address, byte_p[index]);
    }
}

/**
 * @name: FPl011BlockReceive
 * @msg: initiate uart block receive
 * @return {*}
 * @param  uart_p
 */
u8 FPl011BlockReceive(FPl011 *uart_p)
{
    FASSERT(uart_p != NULL);
    FASSERT(uart_p->is_ready == FT_COMPONENT_IS_READY);
    return FPl011RecvByte(uart_p->config.base_address);
}

void FPl011IrqClearReciveTimeOut(FPl011 *uart_p)
{
    u32 reg_temp;
    reg_temp = FPl011GetInterruptMask(uart_p);
    reg_temp &= ~FPL011MIS_RTMIS;
    FPl011SetInterruptMask(uart_p, reg_temp);
}

void FPl011IrqEnableReciveTimeOut(FPl011 *uart_p)
{
    u32 reg_temp;
    reg_temp = FPl011GetInterruptMask(uart_p);
    reg_temp |= FPL011MIS_RTMIS;
    FPl011SetInterruptMask(uart_p, reg_temp);
}
