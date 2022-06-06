/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#include <rtdevice.h>
#include "board_config.h"

/**
 * The below functions will initialize HC32 board.
 */

#if defined RT_USING_SERIAL
rt_err_t rt_hw_board_uart_init(CM_USART_TypeDef *USARTx)
{
    rt_err_t result = RT_EOK;

    switch ((rt_uint32_t)USARTx)
    {
#if defined(BSP_USING_UART4)
    case (rt_uint32_t)CM_USART4:
        /* Configure USART RX/TX pin. */
        GPIO_SetFunc(USART4_RX_PORT, USART4_RX_PIN, GPIO_FUNC_37);
        GPIO_SetFunc(USART4_TX_PORT, USART4_TX_PIN, GPIO_FUNC_36);
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}
#endif

