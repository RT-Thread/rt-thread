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
 * FilePath: fpl011_hw.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:05:56
 * Description:  This files is for uart register function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

/***************************** Include Files *********************************/

#include "fpl011_hw.h"


/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/**
 * @name: FPl011SendByte
 * @msg:  This function sends one byte using the device.This function operates in polled mode and  blocks
 *          until the data has been put into the TX FIFO register.
 * @param  addr contains the base address of the device.
 * @param  Byte contains the byte to be sent.
 */
void FPl011SendByte(u32 addr, u8 byte)
{

    while (FUART_ISTRANSMITFULL(addr))
    {
        ;
    }
    FUART_WRITEREG32(addr, FPL011DR_OFFSET, (u32)byte);
}

/**
 * @name: FPl011RecvByte
 * @msg:  This function receives a byte from the device. It operates in polled mode
 * and blocks until a byte has received.
 * @param  addr contains the base address of the device.
 */
u8 FPl011RecvByte(u32 addr)
{
    u32 recieved_byte;

    while (FUART_ISRECEIVEDATA(addr))
    {
        ;
    }
    recieved_byte = FUART_READREG32(addr, FPL011DR_OFFSET);
    return recieved_byte;
}

