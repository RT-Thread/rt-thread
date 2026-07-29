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

static USART_Module *USARTx;

void rt_hw_console_init(void)
{
    USART_InitType USART_InitStructure;

#if defined(SOC_SERIES_N32H7xx)
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_AFIO, ENABLE);
#elif defined(SOC_SERIES_N32H49x)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_AFIO, ENABLE);
#elif defined(SOC_SERIES_N32H47x_48x)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
#endif

#ifdef USART1
    if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart1") == 0)
    {
#if defined(SOC_SERIES_N32H7xx)
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_USART1, ENABLE);
#elif defined(SOC_SERIES_N32H49x)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_USART1, ENABLE);
#elif defined(SOC_SERIES_N32H47x_48x)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_USART1, ENABLE);
#endif
        USARTx = USART1;
    }
#endif /* USART1 */
#ifdef USART2
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart2") == 0)
    {
#if defined(SOC_SERIES_N32H7xx)
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_USART2, ENABLE);
#elif defined(SOC_SERIES_N32H49x)
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_USART2, ENABLE);
#elif defined(SOC_SERIES_N32H47x_48x)
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART2, ENABLE);
#endif
        USARTx = USART2;
    }
#endif /* USART2 */
#ifdef USART3
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart3") == 0)
    {
#if defined(SOC_SERIES_N32H7xx)
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_USART3, ENABLE);
#elif defined(SOC_SERIES_N32H49x)
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_USART3, ENABLE);
#elif defined(SOC_SERIES_N32H47x_48x)
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART3, ENABLE);
#endif
        USARTx = USART3;
    }
#endif /* USART3 */
#ifdef USART4
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart4") == 0)
    {
#if defined(SOC_SERIES_N32H7xx)
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_USART4, ENABLE);
#elif defined(SOC_SERIES_N32H49x)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_USART4, ENABLE);
#elif defined(SOC_SERIES_N32H47x_48x)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_USART4, ENABLE);
#endif
        USARTx = USART4;
    }
#endif /* USART4 */
#if defined(USART5) || defined(UART5)
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart5") == 0)
    {
#if defined(SOC_SERIES_N32H7xx)
        RCC_EnableAPB2PeriphClk3(RCC_APB2_PERIPHEN_M7_USART5, ENABLE);
        USARTx = USART5;
#elif defined(SOC_SERIES_N32H49x)
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_UART5, ENABLE);
        USARTx = UART5;
#elif defined(SOC_SERIES_N32H47x_48x)
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART5, ENABLE);
        USARTx = UART5;
#endif
    }
#endif /* defined(USART5) || defined(UART5) */
#if defined(USART6) || defined(UART6)
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart6") == 0)
    {
#if defined(SOC_SERIES_N32H7xx)
        RCC_EnableAPB2PeriphClk3(RCC_APB2_PERIPHEN_M7_USART6, ENABLE);
        USARTx = USART6;
#elif defined(SOC_SERIES_N32H49x)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_UART6, ENABLE);
        USARTx = UART6;
#elif defined(SOC_SERIES_N32H47x_48x)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_UART6, ENABLE);
        USARTx = UART6;
#endif
    }
#endif /* defined(USART6) || defined(UART6) */
#if defined(USART7) || defined(UART7)
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart7") == 0)
    {
#if defined(SOC_SERIES_N32H7xx)
        RCC_EnableAPB2PeriphClk3(RCC_APB2_PERIPHEN_M7_USART7, ENABLE);
        USARTx = USART7;
#elif defined(SOC_SERIES_N32H49x)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_UART7, ENABLE);
        USARTx = UART7;
#elif defined(SOC_SERIES_N32H47x_48x)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_UART7, ENABLE);
        USARTx = UART7;
#endif
    }
#endif /* defined(USART7) || defined(UART7) */
#if defined(USART8) || defined(UART8)
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart8") == 0)
    {
#if defined(SOC_SERIES_N32H7xx)
        RCC_EnableAPB2PeriphClk3(RCC_APB2_PERIPHEN_M7_USART8, ENABLE);
        USARTx = USART8;
#elif defined(SOC_SERIES_N32H49x)
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_UART8, ENABLE);
        USARTx = UART8;
#elif defined(SOC_SERIES_N32H47x_48x)
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART8, ENABLE);
        USARTx = UART8;
#endif
    }
#endif /* defined(USART8) || defined(UART8) */
#if defined(USART9) || defined(UART9)
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart9") == 0)
    {
#if defined(SOC_SERIES_N32H7xx)
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_UART9, ENABLE);
        USARTx = UART9;
#elif defined(SOC_SERIES_N32H49x)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_USART9, ENABLE);
        USARTx = USART9;
#endif
    }
#endif /* defined(USART9) || defined(UART9) */
#ifdef UART10
    else if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, "uart10") == 0)
    {
#if defined(SOC_SERIES_N32H7xx)
        RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_UART10, ENABLE);
#elif defined(SOC_SERIES_N32H49x)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_UART10, ENABLE);
#endif
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

        USART_SendData(USARTx, (uint8_t)(*(str + i)));
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
