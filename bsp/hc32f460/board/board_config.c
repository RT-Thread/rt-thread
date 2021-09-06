/*
 * Copyright (C) 2021, lizhengyang
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2021-09-02      lizhengyang     first version
 */
#include <rtdevice.h>
#include "board_config.h"

/**
 * The below functions will initialize HC32 board.
 */

#if defined RT_USING_SERIAL
rt_err_t rt_hw_board_uart_init(M4_USART_TypeDef *USARTx)
{
    rt_err_t result = RT_EOK;

    switch ((rt_uint32_t)USARTx)
    {
#if defined(BSP_USING_UART1)
    case (rt_uint32_t)M4_USART1:
        /* Configure USART1 RX/TX pin. */
        PORT_SetFunc(USART1_RX_PORT, USART1_RX_PIN, Func_Usart1_Rx, Disable);
        PORT_SetFunc(USART1_TX_PORT, USART1_TX_PIN, Func_Usart1_Tx, Disable);
        break;
#endif
#if defined(BSP_USING_UART2)
    case (rt_uint32_t)M4_USART2:
        /* Configure USART2 RX/TX pin. */
        PORT_SetFunc(USART2_RX_PORT, USART2_RX_PIN, Func_Usart2_Rx, Disable);
        PORT_SetFunc(USART2_TX_PORT, USART2_TX_PIN, Func_Usart2_Tx, Disable);
        break;
#endif
#if defined(BSP_USING_UART3)
    case (rt_uint32_t)M4_USART3:
        /* Configure USART3 RX/TX pin. */
        PORT_SetFunc(USART3_RX_PORT, USART3_RX_PIN, Func_Usart3_Rx, Disable);
        PORT_SetFunc(USART3_TX_PORT, USART3_TX_PIN, Func_Usart3_Tx, Disable);
        break;
#endif
#if defined(BSP_USING_UART4)
    case (rt_uint32_t)M4_USART4:
        /* Configure USART4 RX/TX pin. */
        PORT_SetFunc(USART4_RX_PORT, USART4_RX_PIN, Func_Usart4_Rx, Disable);
        PORT_SetFunc(USART4_TX_PORT, USART4_TX_PIN, Func_Usart4_Tx, Disable);
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}
#endif

