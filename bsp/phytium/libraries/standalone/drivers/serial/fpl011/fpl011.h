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
 * FilePath: fpl011.h
 * Date: 2021-11-02 14:53:42
 * LastEditTime: 2022-02-18 09:07:38
 * Description:  This file is for uart functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  huanghe 2021/11/2  first commit
 * 1.1  liushengming 2022/02/18  fix bug
 */

#ifndef FPL011_H
#define FPL011_H

#include "ftypes.h"
#include "fassert.h"
#include "fpl011_hw.h"
#include "sdkconfig.h"


#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

#define FPL011_ERROR_PARAM FT_CODE_ERR(ErrModBsp, ErrBspUart, 0x1u)

#define FPL011_BAUDRATE 115200U

/* Config options */
#define FPL011_OPTION_UARTEN 0x1U
#define FPL011_OPTION_RXEN 0x2U
#define FPL011_OPTION_TXEN 0x4U
#define FPL011_OPTION_FIFOEN 0x8U
#define FPL011_OPTION_CTS 0x10U
#define FPL011_OPTION_RTS 0x20U
#define FPL011_OPTION_DTR 0x40U
#define FPL011_OPTION_RTSEN 0x80U
#define FPL011_OPTION_CTSEN 0x100U
#define FPL011_OPTION_TXDMAEN 0x200U
#define FPL011_OPTION_RXDMAEN 0x400U

/* Channel Operational Mode */
#define FPL011_OPER_MODE_NORMAL     (u8)0x00U       /* Normal Mode */
#define FPL011_OPER_MODE_LOCAL_LOOP (u8)0x01U   /* Local Loop back Mode */


/* Data format values */
#define FPL011_FORMAT_WORDLENGTH_8BIT 0x3
#define FPL011_FORMAT_WORDLENGTH_7BIT 0x2
#define FPL011_FORMAT_WORDLENGTH_6BIT 0x1
#define FPL011_FORMAT_WORDLENGTH_5BIT 0x0

#define FPL011_FORMAT_NO_PARITY     0U  /* No parity */
#define FPL011_FORMAT_EN_PARITY     1U  /* Enable parity */
#define FPL011_FORMAT_EVEN_PARITY   2U  /* Even parity */
#define FPL011_FORMAT_ODD_PARITY    0U  /* Odd parity */
#define FPL011_FORMAT_EN_STICK_PARITY   4U  /* Stick parity */
#define FPL011_FORMAT_NO_STICK_PARITY   0U  /* Stick parity */

#define FPL011_FORMAT_PARITY_MASK   7U  /* Format parity mask */

#define FPL011_FORMAT_EVEN_PARITY_SHIFT 1U /* Even parity shift */
#define FPL011_FORMAT_EN_STICK_PARITY_SHIFT 5U /* Stick parity shift */

#define FPL011_FORMAT_2_STOP_BIT 1U
#define FPL011_FORMAT_1_STOP_BIT 0U


/* Callback events  */
#define FPL011_EVENT_RECV_DATA 1U       /* Data receiving done */
#define FPL011_EVENT_RECV_TOUT 2U       /* A receive timeout occurred */
#define FPL011_EVENT_SENT_DATA 3U       /* Data transmission done */
#define FPL011_EVENT_RECV_ERROR 4U      /* A receive error detected */
#define FPL011_EVENT_MODEM 5U           /* Modem status changed */
#define FPL011_EVENT_PARE_FRAME_BRKE 6U /* A receive parity, frame, break \
*   error detected */
#define FPL011_EVENT_RECV_ORERR 7U      /* A receive overrun error detected */


/**************************** Type Definitions ******************************/

/**
 * Keep track of data format setting of a device.
 */
typedef struct
{
    u32 baudrate ;      /* In bps, ie 1200 */
    u32 data_bits ;     /* Number of data bits */
    u32 parity ;        /* Parity */
    u8  stopbits ;      /* Number of stop bits */
} FPl011Format ;


typedef struct
{
    u32 instance_id; /* Id of device*/
    uintptr base_address;
    u32 ref_clock_hz;
    u32 irq_num;
    u32 baudrate;
} FPl011Config;

typedef struct
{
    u8 *byte_p;
    u32 requested_bytes;
    u32 remaining_bytes;
} FPl011Buffer;

typedef void (*FPl011EventHandler)(void *args, u32 event, u32 event_data);

typedef struct
{
    FPl011Config config; /* Configuration data structure  */
    u32 is_ready;       /* Device is ininitialized and ready*/

    FPl011Buffer send_buffer;
    FPl011Buffer receive_buffer;

    FPl011EventHandler handler;
    void *args;
    uint8_t rxbs_error; /* An error occurs during receiving. 0 has no error and 1 has an error */

} FPl011;


/************************** Function Prototypes ******************************/

/* FPl011_uart_sinit.c */
const FPl011Config *FPl011LookupConfig(u32 instance_id);
/* FPl011_uart.c */
FError FPl011CfgInitialize(FPl011 *uart_p, FPl011Config *config);
void FPl011BlockSend(FPl011 *uart_p, u8 *byte_p, u32 length);
u32 FPl011Send(FPl011 *uart_p, u8 *byte_p, u32 length);
u32 FPl011Receive(FPl011 *uart_p, u8 *byte_p, u32 length);
u8 FPl011BlockReceive(FPl011 *uart_p);
void FPl011ProgramCtlReg(FPl011 *uart_p, u32 ctrl_reg);

/* FPl011_uart_options.c */
void FPl011SetOperMode(FPl011 *uart_p, u8 operation_mode);
void FPl011SetOptions(FPl011 *uart_p, u32 options);
void FPl011SetSpecificOptions(FPl011 *uart_p, u32 options);
void FPl011ClearSpecificOptions(FPl011 *uart_p, u32 options);
FError FPl011SetBaudRate(FPl011 *uart_p, u32 baudrate) ;
void FPl011GetDataFormat(FPl011 *uart_p, FPl011Format *format_p) ;
FError FPl011SetDataFormat(FPl011 *uart_p, FPl011Format *format_p) ;
void FPl011SetTxFifoThreadHold(FPl011 *uart_p, u8 trigger_level) ;
void FPl011SetRxFifoThreadhold(FPl011 *uart_p, u8 trigger_level) ;

/* FPl011_uart_intr.c */
u32 FPl011GetInterruptMask(FPl011 *uart_p) ;
void FPl011InterruptHandler(s32 vector, void *param);
void FPl011SetHandler(FPl011 *uart_p, FPl011EventHandler fun_p, void *args);
void FPl011SetInterruptMask(FPl011 *uart_p, u32 mask);
void FPl011InterruptClearAll(FPl011 *uart_p);



#ifdef __cplusplus
}
#endif

#endif // !
