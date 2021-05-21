/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 17:54:21
 * @Description:  This files is for uart register function
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#include "ft_uart_hw.h"

/**
 * @name: FUart_SendByte
 * @msg: 
 * @return {*}
 * @param {u32} BaseAddress
 * @param {u8} Byte
 */
void FUart_SendByte(u32 BaseAddress, u8 Byte)
{
    while (FT_UART_IsTransmitFull(BaseAddress))
    {
        ;
    }
    FT_UART_WriteReg(BaseAddress, UARTDR_OFFSET, (u32)Byte);
}

/**
 * @name: FUart_RecvByte
 * @msg: 
 * @return {*}
 * @param {u32} BaseAddress
 */
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

/**
 * @name: FUart_GetChar
 * @msg: 
 * @return {*}
 * @param {u32} BaseAddress
 */
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
