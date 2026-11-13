/*
 * Copyright (c) 2021-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef DRV_UART_V2_H
#define DRV_UART_V2_H

#include "rtconfig.h"

/* ============================================================================
 * UART IRQ Priority Configuration Macros
 * ============================================================================
 * 
 * These macros handle the configuration of interrupt priorities for each UART controller.
 * If a specific priority is defined in the board configuration (BSP_UARTx_IRQ_PRIORITY),
 * it will be used; otherwise, a default priority of 1 is applied.
 * 
 * The macros follow a consistent pattern:
 * - Check if BSP_UARTx_IRQ_PRIORITY is defined
 * - Use the configured value if available
 * - Fall back to default priority of 1
 * 
 * Usage: UART_IRQ_PRI_VAL(n) where n is the UART number (0-15)
 */

#ifdef BSP_UART0_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_0 BSP_UART0_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_0 1
#endif

#ifdef BSP_UART1_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_1 BSP_UART1_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_1 1
#endif

#ifdef BSP_UART2_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_2 BSP_UART2_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_2 1
#endif

#ifdef BSP_UART3_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_3 BSP_UART3_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_3 1
#endif

#ifdef BSP_UART4_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_4 BSP_UART4_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_4 1
#endif

#ifdef BSP_UART5_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_5 BSP_UART5_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_5 1
#endif

#ifdef BSP_UART6_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_6 BSP_UART6_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_6 1
#endif

#ifdef BSP_UART7_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_7 BSP_UART7_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_7 1
#endif

#ifdef BSP_UART8_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_8 BSP_UART8_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_8 1
#endif

#ifdef BSP_UART9_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_9 BSP_UART9_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_9 1
#endif

#ifdef BSP_UART10_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_10 BSP_UART10_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_10 1
#endif

#ifdef BSP_UART11_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_11 BSP_UART11_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_11 1
#endif

#ifdef BSP_UART12_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_12 BSP_UART12_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_12 1
#endif

#ifdef BSP_UART13_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_13 BSP_UART13_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_13 1
#endif

#ifdef BSP_UART14_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_14 BSP_UART14_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_14 1
#endif

#ifdef BSP_UART15_IRQ_PRIORITY
#define UART_IRQ_PRI_VAL_15 BSP_UART15_IRQ_PRIORITY
#else
#define UART_IRQ_PRI_VAL_15 1
#endif

#define UART_IRQ_PRI_VAL(n) UART_IRQ_PRI_VAL_##n

/* ============================================================================
* UART DMA Configuration Macros
* ============================================================================
* 
* These macros handle the configuration of DMA usage for each UART controller.
* They check if DMA is enabled for TX and/or RX operations and set appropriate
* boolean values for the UART device structure.
* 
* Configuration options:
* - BSP_UARTx_RX_USING_DMA: Enable DMA for receive operations
* - BSP_UARTx_TX_USING_DMA: Enable DMA for transmit operations
* 
* The macros follow a consistent pattern:
* - Check if BSP_UARTx_RX_USING_DMA is defined
* - Set to true if defined, false otherwise
* - Similar pattern for TX DMA configuration
* 
* Usage: 
* - UART_RX_USING_DMA_VAL(n) for RX DMA configuration
* - UART_TX_USING_DMA_VAL(n) for TX DMA configuration
* where n is the UART number (0-15)
*/
#ifdef BSP_UART0_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_0 true
#else
#define UART_RX_USING_DMA_VAL_0 false
#endif

#ifdef BSP_UART1_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_1 true
#else
#define UART_RX_USING_DMA_VAL_1 false
#endif

#ifdef BSP_UART2_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_2 true
#else
#define UART_RX_USING_DMA_VAL_2 false
#endif

#ifdef BSP_UART3_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_3 true
#else
#define UART_RX_USING_DMA_VAL_3 false
#endif

#ifdef BSP_UART4_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_4 true
#else
#define UART_RX_USING_DMA_VAL_4 false
#endif

#ifdef BSP_UART5_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_5 true
#else
#define UART_RX_USING_DMA_VAL_5 false
#endif

#ifdef BSP_UART6_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_6 true
#else
#define UART_RX_USING_DMA_VAL_6 false
#endif

#ifdef BSP_UART7_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_7 true
#else
#define UART_RX_USING_DMA_VAL_7 false
#endif

#ifdef BSP_UART8_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_8 true
#else
#define UART_RX_USING_DMA_VAL_8 false
#endif

#ifdef BSP_UART9_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_9 true
#else
#define UART_RX_USING_DMA_VAL_9 false
#endif

#ifdef BSP_UART10_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_10 true
#else
#define UART_RX_USING_DMA_VAL_10 false
#endif

#ifdef BSP_UART11_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_11 true
#else
#define UART_RX_USING_DMA_VAL_11 false
#endif

#ifdef BSP_UART12_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_12 true
#else
#define UART_RX_USING_DMA_VAL_12 false
#endif

#ifdef BSP_UART13_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_13 true
#else
#define UART_RX_USING_DMA_VAL_13 false
#endif

#ifdef BSP_UART14_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_14 true
#else
#define UART_RX_USING_DMA_VAL_14 false
#endif

#ifdef BSP_UART15_RX_USING_DMA
#define UART_RX_USING_DMA_VAL_15 true
#else
#define UART_RX_USING_DMA_VAL_15 false
#endif

#define UART_RX_USING_DMA_VAL(n) UART_RX_USING_DMA_VAL_##n

#ifdef BSP_UART0_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_0 true
#else
#define UART_TX_USING_DMA_VAL_0 false
#endif

#ifdef BSP_UART1_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_1 true
#else
#define UART_TX_USING_DMA_VAL_1 false
#endif

#ifdef BSP_UART2_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_2 true
#else
#define UART_TX_USING_DMA_VAL_2 false
#endif

#ifdef BSP_UART3_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_3 true
#else
#define UART_TX_USING_DMA_VAL_3 false
#endif

#ifdef BSP_UART4_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_4 true
#else
#define UART_TX_USING_DMA_VAL_4 false
#endif

#ifdef BSP_UART5_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_5 true
#else
#define UART_TX_USING_DMA_VAL_5 false
#endif

#ifdef BSP_UART6_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_6 true
#else
#define UART_TX_USING_DMA_VAL_6 false
#endif

#ifdef BSP_UART7_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_7 true
#else
#define UART_TX_USING_DMA_VAL_7 false
#endif

#ifdef BSP_UART8_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_8 true
#else
#define UART_TX_USING_DMA_VAL_8 false
#endif

#ifdef BSP_UART9_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_9 true
#else
#define UART_TX_USING_DMA_VAL_9 false
#endif

#ifdef BSP_UART10_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_10 true
#else
#define UART_TX_USING_DMA_VAL_10 false
#endif

#ifdef BSP_UART11_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_11 true
#else
#define UART_TX_USING_DMA_VAL_11 false
#endif

#ifdef BSP_UART12_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_12 true
#else
#define UART_TX_USING_DMA_VAL_12 false
#endif

#ifdef BSP_UART13_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_13 true
#else
#define UART_TX_USING_DMA_VAL_13 false
#endif

#ifdef BSP_UART14_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_14 true
#else
#define UART_TX_USING_DMA_VAL_14 false
#endif

#ifdef BSP_UART15_TX_USING_DMA
#define UART_TX_USING_DMA_VAL_15 true
#else
#define UART_TX_USING_DMA_VAL_15 false
#endif

#define UART_TX_USING_DMA_VAL(n) UART_TX_USING_DMA_VAL_##n

#ifndef BSP_UART0_DMA_PINGPONG_BUFSIZE
#define BSP_UART0_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART1_DMA_PINGPONG_BUFSIZE
#define BSP_UART1_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART2_DMA_PINGPONG_BUFSIZE
#define BSP_UART2_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART3_DMA_PINGPONG_BUFSIZE
#define BSP_UART3_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART4_DMA_PINGPONG_BUFSIZE
#define BSP_UART4_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART5_DMA_PINGPONG_BUFSIZE
#define BSP_UART5_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART6_DMA_PINGPONG_BUFSIZE
#define BSP_UART6_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART7_DMA_PINGPONG_BUFSIZE
#define BSP_UART7_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART8_DMA_PINGPONG_BUFSIZE
#define BSP_UART8_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART9_DMA_PINGPONG_BUFSIZE
#define BSP_UART9_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART10_DMA_PINGPONG_BUFSIZE
#define BSP_UART10_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART11_DMA_PINGPONG_BUFSIZE
#define BSP_UART11_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART12_DMA_PINGPONG_BUFSIZE
#define BSP_UART12_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART13_DMA_PINGPONG_BUFSIZE
#define BSP_UART13_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART14_DMA_PINGPONG_BUFSIZE
#define BSP_UART14_DMA_PINGPONG_BUFSIZE 0
#endif
#ifndef BSP_UART15_DMA_PINGPONG_BUFSIZE
#define BSP_UART15_DMA_PINGPONG_BUFSIZE 0
#endif

#define UART_RX_DMA_IT_IDLE_FLAG        0x00
#define UART_RX_DMA_IT_HT_FLAG          0x01
#define UART_RX_DMA_IT_TC_FLAG          0x02

int rt_hw_uart_init(void);



#endif /* DRV_UART_H */
