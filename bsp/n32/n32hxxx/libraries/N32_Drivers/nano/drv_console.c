/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#include <board.h>
#include <rtthread.h>
#include <drv_common.h>


static USART_Module* USARTx;

void rt_hw_console_init(void)
{
    USART_InitType USART_InitStructure;

    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_AFIO, ENABLE);

#ifdef USART1
    if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart1") == 0)
    {
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_USART1, ENABLE);
        USARTx = USART1;
    }
#endif /* USART1 */
#ifdef USART2
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart2") == 0)
    {
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_USART2, ENABLE);
        USARTx = USART2;
    }
#endif /* USART2 */
#ifdef USART3
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart3") == 0)
    {
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_USART3, ENABLE);
        USARTx = USART3;
    }
#endif /* USART3 */
#ifdef USART4
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart4") == 0)
    {
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_USART4, ENABLE);
        USARTx = USART4;
    }
#endif /* USART4 */
#ifdef USART5
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart5") == 0)
    {
        RCC_EnableAPB2PeriphClk3(RCC_APB2_PERIPHEN_M7_USART5, ENABLE);
        USARTx = USART5;
    }
#endif /* USART5 */
#ifdef USART6
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart6") == 0)
    {
        RCC_EnableAPB2PeriphClk3(RCC_APB2_PERIPHEN_M7_USART6, ENABLE);
        USARTx = USART6;
    }
#endif /* USART6 */
#ifdef USART7
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart7") == 0)
    {
        RCC_EnableAPB2PeriphClk3(RCC_APB2_PERIPHEN_M7_USART7, ENABLE);
        USARTx = USART7;
    }
#endif /* USART7 */
#ifdef USART8
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart8") == 0)
    {
        RCC_EnableAPB2PeriphClk3(RCC_APB2_PERIPHEN_M7_USART8, ENABLE);
        USARTx = USART8;
    }
#endif /* USART8 */
#ifdef UART9
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart9") == 0)
    {
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_UART9, ENABLE);
        USARTx = UART9;
    }
#endif /* UART9 */
#ifdef UART10
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart10") == 0)
    {
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_UART10, ENABLE);
        USARTx = UART10;
    }
#endif /* UART10 */
#ifdef UART11
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart11") == 0)
    {
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_UART11, ENABLE);
        USARTx = UART11;
    }
#endif /* UART11 */
#ifdef UART12
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart12") == 0)
    {
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_UART12, ENABLE);
        USARTx = UART12;
    }
#endif /* UART12 */
#ifdef UART13
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart13") == 0)
    {
        RCC_EnableAPB2PeriphClk3(RCC_APB2_PERIPHEN_M7_UART13, ENABLE);
        USARTx = UART13;
    }
#endif /* UART13 */
#ifdef UART14
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart14") == 0)
    {
        RCC_EnableAPB2PeriphClk3(RCC_APB2_PERIPHEN_M7_UART14, ENABLE);
        USARTx = UART14;
    }
#endif /* UART14 */
#ifdef UART15
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart15") == 0)
    {
        RCC_EnableAPB2PeriphClk3(RCC_APB2_PERIPHEN_M7_UART15, ENABLE);
        USARTx = UART15;
    }
#endif /* UART15 */
    else
    {
        RT_ASSERT(0);
    }

    USART_DeInit(USARTx);

    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.OverSampling        = USART_16OVER;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;
    USART_Init(USARTx, &USART_InitStructure);
    USART_Enable(USARTx, ENABLE);
}

void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            while (USART_GetFlagStatus(USARTx, USART_FLAG_TXC) == RESET);

            USART_SendData(USARTx, (uint8_t)'\r');
        }

        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXC) == RESET);

        USART_SendData(USARTx, (uint8_t )(*(str + i)));
    }
}

char rt_hw_console_getchar(void)
{
    int ch = -1;

    if (USART_GetFlagStatus(USARTx, USART_FLAG_RXDNE) != SET)
    {
        ch = -1;
        rt_thread_mdelay(10);
    }
    else
    {
        ch = USART_ReceiveData(USARTx);
    }
    return ch;
}
