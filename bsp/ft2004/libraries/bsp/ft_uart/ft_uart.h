/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-24 10:13:51
 * @Description:  This files is for uart functions
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FT_UART_H
#define FT_UART_H

#include "ft_types.h"
#include "ft_assert.h"
#include "ft_status.h"
#include "ft_uart_hw.h"

#define FUART_BAUDRATE 115200U

/* Config options */
#define FUART_OPTION_UARTEN 0x1U
#define FUART_OPTION_RXEN 0x2U
#define FUART_OPTION_TXEN 0x4U
#define FUART_OPTION_FIFOEN 0x8U

/* Data format values  */
#define FUART_FORMAT_WORDLENGTH_8BIT 0x3
#define FUART_FORMAT_WORDLENGTH_7BIT 0x2
#define FUART_FORMAT_WORDLENGTH_6BIT 0x1
#define FUART_FORMAT_WORDLENGTH_5BIT 0x0

#define FUART_FORMAT_NO_PARITY 0U
#define FUART_FORMAT_MARK_PARITY 1U
#define FUART_FORMAT_SPACE_PARITY 2U
#define FUART_FORMAT_ODD_PARTY 3U
#define FUART_FORMAT_EVEN_PARITY 4U

#define FUART_FORMAT_2_STOP_BIT 0U
#define FUART_FORMAT_1_STOP_BIT 1U

/* Callback events  */

#define FUART_EVENT_RECV_DATA 1U       /**< Data receiving done */
#define FUART_EVENT_RECV_TOUT 2U       /**< A receive timeout occurred */
#define FUART_EVENT_SENT_DATA 3U       /**< Data transmission done */
#define FUART_EVENT_RECV_ERROR 4U      /**< A receive error detected */
#define FUART_EVENT_MODEM 5U           /**< Modem status changed */
#define FUART_EVENT_PARE_FRAME_BRKE 6U /**< A receive parity, frame, break \
                                        *   error detected */
#define FUART_EVENT_RECV_ORERR 7U      /**< A receive overrun error detected */

/**************************** Type Definitions ******************************/
typedef struct
{
    u32 InstanceId; /* Id of device*/
    u32 BaseAddress;
    u32 RefClockHz;
    u32 IsrNum;
} FUart_Config_t;

typedef struct
{
    u8 *BytePtr;
    u32 RequestedBytes;
    u32 RemainingBytes;
} FUart_Buffer_t;

typedef struct
{
    u32 BaudRate; /**< In bps, ie 1200 */
    u32 DataBits; /**< Number of data bits */
    u32 Parity;   /**< Parity */
    u8 StopBits;  /**< Number of stop bits */
} FUart_Format_t;

typedef void (*FUart_Handler_t)(void *Args, u32 Event, u32 EventData);

typedef struct
{
    FUart_Config_t Config; /* Configuration data structure  */
    u32 InputClockHz;
    u32 IsReady; /* Device is ininitialized and ready*/
    u32 BaudRate;

    FUart_Buffer_t SendBuffer;
    FUart_Buffer_t ReceiveBuffer;

    FUart_Handler_t Handler;
    void *Args;
    uint8_t rxbs_error; /* 接收过程中出现错误 ，0 无错误，1 存在错误*/

} Ft_Uart;

/* define SD MMC error code */
typedef enum
{
    ERR_SUB_MODE_UART_GENERAL = 0
} FT_UART_ERR_SUB_MODE;

#define ERR_INPUT_BAUD_NO_SUPPORT FT_CODE_ERR(ERR_MODE_UART, ERR_SUB_MODE_UART_GENERAL, 0x1)

void FUart_PutChar(Ft_Uart *UartPtr, s8 Data);
u32 FUart_Send(Ft_Uart *UartPtr, u8 *Buffer, u32 Length);
u32 FUart_Receive(Ft_Uart *UartPtr, u8 *BytePtr, u32 Length);
s32 FUart_CfgInitialize(Ft_Uart *UartPtr, FUart_Config_t *Config);
FUart_Config_t *FUart_LookupConfig(u32 InstanceId);
void FUart_SetOptions(Ft_Uart *UartPtr, u32 Options);
void FUart_SetSpecificOptions(Ft_Uart *UartPtr, u32 Options);
void FUart_ClearSpecificOptions(Ft_Uart *UartPtr, u32 Options);
void FUart_InterruptHandler(Ft_Uart *UartPtr);
void FUart_SetHandler(Ft_Uart *UartPtr, FUart_Handler_t FuncPtr,
                      void *Args);
void FUart_SetInterruptMask(Ft_Uart *UartPtr, u32 Mask);
u32 FUart_SetBaudRate(Ft_Uart *UartPtr, u32 BaudRate);
#endif // !
