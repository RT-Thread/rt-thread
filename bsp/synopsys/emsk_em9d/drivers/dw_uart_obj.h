/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _DW_UART_OBJ_H_
#define _DW_UART_OBJ_H_

#include "device/device_hal/inc/dev_uart.h"

/**
 * \name    DesignWare UART Object Number
 * @{
 */
#define DW_UART_NUM (2) /*!< DesignWare UART valid number */
/** @} end of name */

/**
 * \name    Designware UART Object ID Macros
 * @{
 */
#define DW_UART_0_ID    0   /*!< uart 0 id macro */
#define DW_UART_1_ID    1   /*!< uart 1 id macro */
/** @} end of name */

/**
 * \name    Designware UART Object Control Macros
 * @{
 */
#define USE_DW_UART_0   1   /*!< enable use designware uart 0 */
#define USE_DW_UART_1   1   /*!< enable use designware uart 1 */
/** @} end of name */

/**
 * \name    Designware UART Ringbuffer Size Control Macros
 * @{
 */
#define MAX_SNDBUF_SIZE 256 /*!< max size of uart send buffer */
#define MAX_RCVBUF_SIZE 10  /*!< max size of uart recv buffer */
/** @} end of name */

#ifdef __cplusplus
extern "C" {
#endif

extern void dw_uart_all_install(void);

#ifdef __cplusplus
}
#endif

#endif /* _DW_UART_OBJ_H_ */
