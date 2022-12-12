/*
 *  Change Logs:
 *  Date            Author          Notes
 *  2021-04-20      liuhy          the first version
 *
 * Copyright (C) 2021 Shanghai Eastsoft Microelectronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __ES_CONF_INFO_UART_H__
#define __ES_CONF_INFO_UART_H__

#include "es_conf_info_map.h"
#include <ald_gpio.h>
#include <ald_uart.h>
#include <ald_usart.h>
#include <ald_cmu.h>



#define ES_C_UART_PARITY_NONE        PARITY_NONE
#define ES_C_UART_PARITY_ODD         PARITY_ODD
#define ES_C_UART_PARITY_EVEN        PARITY_EVEN

#define ES_C_UART_STOP_1          STOP_BITS_1
#define ES_C_UART_STOP_2          STOP_BITS_2


/* UART 配置 */

/* codes_main */



#ifndef  ES_DEVICE_NAME_UART0
#define  ES_DEVICE_NAME_UART0     "uart0"
#endif
#ifndef  ES_DEVICE_NAME_UART1
#define  ES_DEVICE_NAME_UART1     "uart1"
#endif
#ifndef  ES_DEVICE_NAME_UART2
#define  ES_DEVICE_NAME_UART2     "uart2"
#endif
#ifndef  ES_DEVICE_NAME_UART3
#define  ES_DEVICE_NAME_UART3     "uart3"
#endif
#ifndef  ES_DEVICE_NAME_USART0
#define  ES_DEVICE_NAME_USART0     "usart0"
#endif
#ifndef  ES_DEVICE_NAME_USART1
#define  ES_DEVICE_NAME_USART1     "usart1"
#endif

#ifndef ES_CONF_UART0_BAUD_RATE
#define ES_CONF_UART0_BAUD_RATE         115200
#endif
#ifndef ES_CONF_UART0_PARITY
#define ES_CONF_UART0_PARITY         ES_C_UART_PARITY_NONE
#endif
#ifndef ES_CONF_UART0_STOP_BITS
#define ES_CONF_UART0_STOP_BITS        ES_C_UART_STOP_1
#endif

#ifndef ES_CONF_UART1_BAUD_RATE
#define ES_CONF_UART1_BAUD_RATE         115200
#endif
#ifndef ES_CONF_UART1_PARITY
#define ES_CONF_UART1_PARITY         ES_C_UART_PARITY_NONE
#endif
#ifndef ES_CONF_UART1_STOP_BITS
#define ES_CONF_UART1_STOP_BITS        ES_C_UART_STOP_1
#endif

#ifndef ES_CONF_UART2_BAUD_RATE
#define ES_CONF_UART2_BAUD_RATE         115200
#endif
#ifndef ES_CONF_UART2_PARITY
#define ES_CONF_UART2_PARITY         ES_C_UART_PARITY_NONE
#endif
#ifndef ES_CONF_UART2_STOP_BITS
#define ES_CONF_UART2_STOP_BITS        ES_C_UART_STOP_1
#endif

#ifndef ES_CONF_UART3_BAUD_RATE
#define ES_CONF_UART3_BAUD_RATE         115200
#endif
#ifndef ES_CONF_UART3_PARITY
#define ES_CONF_UART3_PARITY         ES_C_UART_PARITY_NONE
#endif
#ifndef ES_CONF_UART3_STOP_BITS
#define ES_CONF_UART3_STOP_BITS        ES_C_UART_STOP_1
#endif

#ifndef ES_CONF_USART0_BAUD_RATE
#define ES_CONF_USART0_BAUD_RATE         115200
#endif
#ifndef ES_CONF_USART0_PARITY
#define ES_CONF_USART0_PARITY         ES_C_UART_PARITY_NONE
#endif
#ifndef ES_CONF_USART0_STOP_BITS
#define ES_CONF_USART0_STOP_BITS        ES_C_UART_STOP_1
#endif

#ifndef ES_CONF_USART1_BAUD_RATE
#define ES_CONF_USART1_BAUD_RATE         115200
#endif
#ifndef ES_CONF_USART1_PARITY
#define ES_CONF_USART1_PARITY         ES_C_UART_PARITY_NONE
#endif
#ifndef ES_CONF_USART1_STOP_BITS
#define ES_CONF_USART1_STOP_BITS        ES_C_UART_STOP_1
#endif


#define ES_UART0_CONFIG                         \
{                                               \
    ES_CONF_UART0_BAUD_RATE,                           \
    DATA_BITS_8,                                \
    ES_CONF_UART0_STOP_BITS,                                \
    ES_CONF_UART0_PARITY,                                \
    BIT_ORDER_LSB,                              \
    NRZ_NORMAL,                                 \
    RT_SERIAL_RB_BUFSZ,                         \
    0                                           \
}


#define ES_UART1_CONFIG                         \
{                                               \
    ES_CONF_UART1_BAUD_RATE,                           \
    DATA_BITS_8,                                \
    ES_CONF_UART1_STOP_BITS,                                \
    ES_CONF_UART1_PARITY,                                \
    BIT_ORDER_LSB,                              \
    NRZ_NORMAL,                                 \
    RT_SERIAL_RB_BUFSZ,                         \
    0                                           \
}


#define ES_UART2_CONFIG                         \
{                                               \
    ES_CONF_UART2_BAUD_RATE,                           \
    DATA_BITS_8,                                \
    ES_CONF_UART2_STOP_BITS,                                \
    ES_CONF_UART2_PARITY,                                \
    BIT_ORDER_LSB,                              \
    NRZ_NORMAL,                                 \
    RT_SERIAL_RB_BUFSZ,                         \
    0                                           \
}


#define ES_UART3_CONFIG                         \
{                                               \
    ES_CONF_UART3_BAUD_RATE,                           \
    DATA_BITS_8,                                \
    ES_CONF_UART3_STOP_BITS,                                \
    ES_CONF_UART3_PARITY,                                \
    BIT_ORDER_LSB,                              \
    NRZ_NORMAL,                                 \
    RT_SERIAL_RB_BUFSZ,                         \
    0                                           \
}


#define ES_USART0_CONFIG                         \
{                                               \
    ES_CONF_USART0_BAUD_RATE,                           \
    DATA_BITS_8,                                \
    ES_CONF_USART0_STOP_BITS,                                \
    ES_CONF_USART0_PARITY,                                \
    BIT_ORDER_LSB,                              \
    NRZ_NORMAL,                                 \
    RT_SERIAL_RB_BUFSZ,                         \
    0                                           \
}


#define ES_USART1_CONFIG                         \
{                                               \
    ES_CONF_USART1_BAUD_RATE,                           \
    DATA_BITS_8,                                \
    ES_CONF_USART1_STOP_BITS,                                \
    ES_CONF_USART1_PARITY,                                \
    BIT_ORDER_LSB,                              \
    NRZ_NORMAL,                                 \
    RT_SERIAL_RB_BUFSZ,                         \
    0                                           \
}

#endif
