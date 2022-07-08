/**
  * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    drv_uart.h
  * @author  Huibin Hong
  * @version V0.5
  * @date    10-Dec-2018
  * @brief   serial driver
  *
  ******************************************************************************
  */

#ifndef __ARCH_ARM_SRC_ROCKCHIP_RK_SERIAL_H
#define __ARCH_ARM_SRC_ROCKCHIP_RK_SERIAL_H

/*******************************************************************************
 * Included Files
 ******************************************************************************/
#include "hal_def.h"

/*******************************************************************************
 * Pre-processor Definitions
 ******************************************************************************/
#define ROCKCHIP_UART_SUPPORT_FLAG_DEFAULT  \
        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX
#define ROCKCHIP_UART_BAUD_RATE_DEFAULT UART_BR_115200

/*******************************************************************************
 * Public Types
 ******************************************************************************/

/* uart_board includes information on a board */
struct uart_board
{
    rt_uint32_t baud_rate;      /* for example 115200 */
    rt_uint32_t dev_flag;       /* for example RT_DEVICE_FLAG_INT_RX */
    rt_uint32_t bufer_size;     /* uart buffer size */
    rt_bool_t en_irq_wake;      /* enable uart irq wake up */
    char        name[8];        /* device name: /dev/xxxx */
};

/*******************************************************************************
 * Public Data
 ******************************************************************************/

#if defined(RT_USING_UART0)
extern const struct uart_board g_uart0_board;
#endif /* RT_USING_UART0 */

#if defined(RT_USING_UART1)
extern const struct uart_board g_uart1_board;
#endif /* RT_USING_UART1 */

#if defined(RT_USING_UART2)
extern const struct uart_board g_uart2_board;
#endif /* RT_USING_UART2 */

#if defined(RT_USING_UART3)
extern const struct uart_board g_uart3_board;
#endif /* RT_USING_UART3 */

#if defined(RT_USING_UART4)
extern const struct uart_board g_uart4_board;
#endif /* RT_USING_UART4 */

#if defined(RT_USING_UART5)
extern const struct uart_board g_uart5_board;
#endif /* RT_USING_UART5 */

#if defined(RT_USING_UART6)
extern const struct uart_board g_uart6_board;
#endif /* RT_USING_UART6 */

#if defined(RT_USING_UART7)
extern const struct uart_board g_uart7_board;
#endif /* RT_USING_UART7 */

#if defined(RT_USING_UART8)
extern const struct uart_board g_uart8_board;
#endif /* RT_USING_UART8 */

#if defined(RT_USING_UART9)
extern const struct uart_board g_uart9_board;
#endif /* RT_USING_UART9 */

/*******************************************************************************
 * Inline Functions
 ******************************************************************************/

/*******************************************************************************
 * Public Functions
 ******************************************************************************/

void rt_hw_usart_init(void);
int rt_hw_console_channel(void);

#endif /* __ARCH_ARM_SRC_ROCKCHIP_RK_SERIAL_H */
