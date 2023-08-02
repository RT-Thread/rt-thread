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
 * FilePath: fearly_uart.h
 * Date: 2022-02-11 13:33:28
 * LastEditTime: 2022-02-17 18:00:16
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   rtos       2022/6/25    init commit
 * 1.1   zhangyan   2023/7/11    reconstruct
 */
#ifndef  BOARD_COMMON_EARLY_UART_H
#define  BOARD_COMMON_EARLY_UART_H

#ifdef __cplusplus
extern "C"
{
#endif

/***************************** Include Files *********************************/
#include "ftypes.h"
#include "fio.h"
#include "fparameters.h"
#include "sdkconfig.h"

/**************************** Type Definitions *******************************/

/************************** Constant Definitions *****************************/
#if defined(CONFIG_DEFAULT_DEBUG_PRINT_UART2)
#define EARLY_UART_CTRL_ID FUART2_ID
#elif defined(CONFIG_DEFAULT_DEBUG_PRINT_UART0)
#define EARLY_UART_CTRL_ID FUART0_ID
#else
#define EARLY_UART_CTRL_ID FUART1_ID
#endif

#define STDOUT_BASEADDRESS
/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/*****************************************************************************/
void FEarlyUartProbe(void);
void OutByte(s8 byte);
char GetByte(void);

#ifdef __cplusplus
}
#endif

#endif