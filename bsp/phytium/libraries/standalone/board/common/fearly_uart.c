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
 * FilePath: early_uart.c
 * Date: 2022-02-11 13:33:28
 * LastEditTime: 2022-02-17 17:59:26
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

/***************************** Include Files *********************************/
#include "fkernel.h"
#include "fio.h"
#include "fparameters.h"
#include "fearly_uart.h"

/**************************** Type Definitions *******************************/

/************************** Constant Definitions *****************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/*****************************************************************************/
void OutByte(s8 byte)
{
    /* wait until tx fifo is not full */
    while ((FtIn32(EARLY_UART_UARTFR) & EARLY_UART_TXFF) == EARLY_UART_TXFF)
    {

    }

    FtOut32(EARLY_UART_UARTDR, (((u32)byte) & EARLY_UART_DATA_MASK));
}

char GetByte(void)
{
    /* wait until rx fifo is not empty */
    while ((FtIn32(EARLY_UART_UARTFR) & EARLY_UART_RXFE) == EARLY_UART_RXFE)
    {

    }

    return (char)(EARLY_UART_DATA_MASK & FtIn32(EARLY_UART_UARTDR));
}