/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
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
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

/* DW apb uart: 16550-compatible registers with 32-bit stride */
#define UART_RHR 0 /* receive holding register (read)  */
#define UART_THR 0 /* transmit holding register (write) */
#define UART_DLL 0 /* divisor latch low (LCR[7]=1) */
#define UART_IER 1 /* interrupt enable register */
#define UART_DLH 1 /* divisor latch high (LCR[7]=1) */
#define UART_IIR 2 /* interrupt identify register (read) */
#define UART_FCR 2 /* fifo control register (write) */
#define UART_LCR 3 /* line control register */
#define UART_MCR 4 /* modem control register */
#define UART_LSR 5 /* line status register */
#define UART_USR 31 /* DW uart status register (0x7c) */

#define UART_IER_RX_ENABLE   (1 << 0)
#define UART_IER_TX_ENABLE   (1 << 1)
#define UART_FCR_FIFO_ENABLE (1 << 0)
#define UART_FCR_FIFO_CLEAR  (3 << 1)
#define UART_LCR_EIGHT_BITS  (3 << 0)
#define UART_LCR_BAUD_LATCH  (1 << 7)
#define UART_LSR_RX_READY    (1 << 0)
#define UART_LSR_TX_IDLE     (1 << 5)

int rt_hw_uart_init(void);

#endif /* __DRV_UART_H__ */
