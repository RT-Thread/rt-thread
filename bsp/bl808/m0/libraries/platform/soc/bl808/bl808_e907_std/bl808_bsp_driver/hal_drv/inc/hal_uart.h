/**
 * @file hal_uart.h
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#ifndef __HAL_UART__H__
#define __HAL_UART__H__

#include "hal_common.h"
#include "drv_device.h"
#include "bl808_config.h"

#define UART_FIFO_LEN 32

#define DEVICE_CTRL_UART_GET_TX_FIFO 0x10
#define DEVICE_CTRL_UART_GET_RX_FIFO 0x11

enum uart_index_type {
#ifdef BSP_USING_UART0
    UART0_INDEX,
#endif
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
#ifdef BSP_USING_UART3
    UART3_INDEX,
#endif
    UART_MAX_INDEX
};

/*!
 *  @brief    UART data length settings
 *
 *  This enumeration defines the UART data lengths.
 */
typedef enum {
    UART_DATA_LEN_5 = 0, /*!< Data length is 5 bits */
    UART_DATA_LEN_6 = 1, /*!< Data length is 6 bits */
    UART_DATA_LEN_7 = 2, /*!< Data length is 7 bits */
    UART_DATA_LEN_8 = 3  /*!< Data length is 8 bits */
} uart_databits_t;

/*!
 *  @brief    UART stop bit settings
 *
 *  This enumeration defines the UART stop bits.
 */
typedef enum {
    UART_STOP_ZERO_D_FIVE = 0, /*!< 0.5 stop bit */
    UART_STOP_ONE = 1,         /*!< 1 stop bit */
    UART_STOP_ONE_D_FIVE = 2,  /*!< 1.5 stop bit */
    UART_STOP_TWO = 3          /*!< 2 stop bits */
} uart_stopbits_t;

/*!
 *  @brief    UART parity type settings
 *
 *  This enumeration defines the UART parity types.
 */
typedef enum {
    UART_PAR_NONE = 0, /*!< No parity */
    UART_PAR_ODD = 1,  /*!< Parity bit is odd */
    UART_PAR_EVEN = 2, /*!< Parity bit is even */
} uart_parity_t;

enum uart_event_type {
    UART_EVENT_TX_END,
    UART_EVENT_TX_FIFO,
    UART_EVENT_RX_END,
    UART_EVENT_RX_FIFO,
    UART_EVENT_RTO,
    UART_EVENT_UNKNOWN
};

enum uart_it_type {
    UART_TX_END_IT = 1 << 0,
    UART_RX_END_IT = 1 << 1,
    UART_TX_FIFO_IT = 1 << 2,
    UART_RX_FIFO_IT = 1 << 3,
    UART_RTO_IT = 1 << 4,
    UART_PCE_IT = 1 << 5,
    UART_TX_FER_IT = 1 << 6,
    UART_RX_FER_IT = 1 << 7,
    UART_ALL_IT = 1 << 8
};

typedef struct
{
    uint32_t baudrate;
    uart_databits_t databits;
    uart_stopbits_t stopbits;
    uart_parity_t parity;
} uart_param_cfg_t;

typedef struct uart_device {
    struct device parent;
    uint8_t id;
    uint32_t baudrate;
    uart_databits_t databits;
    uart_stopbits_t stopbits;
    uart_parity_t parity;
    uint8_t fifo_threshold;
    void *tx_dma;
    void *rx_dma;
} uart_device_t;

#define UART_DEV(dev) ((uart_device_t *)dev)

int uart_register(enum uart_index_type index, const char *name);

#endif