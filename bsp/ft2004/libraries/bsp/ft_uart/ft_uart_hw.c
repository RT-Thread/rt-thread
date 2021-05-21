/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-25 16:49:30
 * @Description:  This files is for uart register function
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_uart_hw.h"

void FUart_SendByte(u32 BaseAddress, u8 Byte)
{
    while (FT_UART_IsTransmitFull(BaseAddress))
    {
        ;
    }
    FT_UART_WriteReg(BaseAddress, UARTDR_OFFSET, (u32)Byte);
}

u8 FUart_RecvByte(u32 BaseAddress)
{
    u32 RecievedByte;
    while (FT_UART_IsReceiveData(BaseAddress))
    {
        ;
    }
    RecievedByte = FT_UART_ReadReg(BaseAddress, UARTDR_OFFSET);
    return RecievedByte;
}

u8 FUart_GetChar(u32 BaseAddress)
{
    u32 RecievedByte;
    if (FT_UART_IsReceiveData(BaseAddress))
    {
        return 0xff;
    }
    RecievedByte = FT_UART_ReadReg(BaseAddress, UARTDR_OFFSET);
    return RecievedByte;
}
