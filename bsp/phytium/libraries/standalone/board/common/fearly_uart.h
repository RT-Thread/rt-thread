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
#define EARLY_UART_BASE FUART2_BASE_ADDR
#define EARLY_UART_IRQ_NUM FUART2_IRQ_NUM
#elif defined(CONFIG_DEFAULT_DEBUG_PRINT_UART0)
#define EARLY_UART_BASE FUART0_BASE_ADDR
#define EARLY_UART_IRQ_NUM FUART0_IRQ_NUM
#else
#define EARLY_UART_BASE FUART1_BASE_ADDR
#define EARLY_UART_IRQ_NUM FUART1_IRQ_NUM
#endif

#define EARLY_UART_UARTDR (EARLY_UART_BASE + 0x0)  /* UART 数据寄存器地址 */
#define EARLY_UART_UARTFR (EARLY_UART_BASE + 0x18) /* UART 状态寄存器地址 */
#define EARLY_UART_UARTCR (EARLY_UART_BASE + 0x30)
#define EARLY_UART_UARTCR_UARTEN BIT(0)
#define EARLY_UART_UARTCR_TXE BIT(8)
#define EARLY_UART_UARTCR_RXE BIT(9)
#define EARLY_UART_UARTCR_INIT (EARLY_UART_UARTCR_UARTEN | EARLY_UART_UARTCR_TXE | \
                                EARLY_UART_UARTCR_RXE)
#define EARLY_UART_UARTIMSC (EARLY_UART_BASE + 0x38)
#define EARLY_UART_UARTIMSC_RXIM BIT(4)
#define EARLY_UART_UARTIMSC_RTIM BIT(6)
#define EARLY_UART_UARTMIS (EARLY_UART_BASE + 0x40)
#define EARLY_UART_UARTICR (EARLY_UART_BASE + 0x44)
#define EARLY_UART_TXFF BIT(5) /* 发送 FIFO 已满标志位 */
#define EARLY_UART_RXFE BIT(4) /* 接收 FIFO 为空标志位 */
#define EARLY_UART_DATA_MASK GENMASK(7, 0)
#define EARLY_UART_RXI_MASK BIT(4)

#define STDOUT_BASEADDRESS
/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/*****************************************************************************/
void OutByte(s8 byte);
char GetByte(void);

#ifdef __cplusplus
}
#endif

#endif