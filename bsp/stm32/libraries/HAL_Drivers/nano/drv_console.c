/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-30     Meco Man     First version
 */

#include <board.h>
#include <rtthread.h>
#include <drv_common.h>

static UART_HandleTypeDef console_uart;

void rt_hw_console_init(void)
{
    HAL_UART_DeInit(&console_uart);
#ifdef USART1
    if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart1") == 0)
    {
        console_uart.Instance = USART1;
    }
#endif /* USART1 */
#ifdef USART2
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart2") == 0)
    {
        console_uart.Instance = USART2;
    }
#endif /* USART2 */
#ifdef USART3
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart3") == 0)
    {
        console_uart.Instance = USART3;
    }
#endif /* USART3 */
#ifdef USART4
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart4") == 0)
    {
        console_uart.Instance = USART4;
    }
#endif /* USART4 */
#ifdef USART5
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart5") == 0)
    {
        console_uart.Instance = USART5;
    }
#endif /* USART5 */
#ifdef USART6
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart6") == 0)
    {
        console_uart.Instance = USART6;
    }
#endif /* USART6 */
#ifdef USART7
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart7") == 0)
    {
        console_uart.Instance = USART7;
    }
#endif /* USART7 */
    else
    {
        RT_ASSERT(0);
    }
    console_uart.Init.BaudRate = 115200;
    console_uart.Init.WordLength = UART_WORDLENGTH_8B;
    console_uart.Init.StopBits = UART_STOPBITS_1;
    console_uart.Init.Parity = UART_PARITY_NONE;
    console_uart.Init.Mode = UART_MODE_TX_RX;
    console_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    if (HAL_UART_Init(&console_uart) != HAL_OK)
    {
        Error_Handler();
    }
}

void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    __HAL_UNLOCK(&console_uart);

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            HAL_UART_Transmit(&console_uart, (uint8_t *)&a, 1, 1);
        }
        HAL_UART_Transmit(&console_uart, (uint8_t *)(str + i), 1, 1);
    }
}

char rt_hw_console_getchar(void)
{
    int ch = -1;

    if (HAL_UART_Receive(&console_uart, (uint8_t *)&ch, 1, 0) != HAL_OK)
    {
        ch = -1;
        rt_thread_mdelay(10);
    }
    return ch;
}
