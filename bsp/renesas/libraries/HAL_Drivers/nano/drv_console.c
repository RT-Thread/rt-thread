/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-20     kurisaw      First version
 */

#include <rtthread.h>
#include <rthw.h>
#include <hal_data.h>

#if defined(RT_USING_CONSOLE) && defined(RT_USING_SEMAPHORE)

struct rt_semaphore console_sem;

#if defined(RT_NANO_CONSOLE_UART0)
#define renesas_uart_ctrl       g_uart0_ctrl
#define renesas_uart_cfg        g_uart0_cfg
#define renesas_uart_callback   user_uart0_callback
#elif defined(RT_NANO_CONSOLE_UART1)
#define renesas_uart_ctrl       g_uart1_ctrl
#define renesas_uart_cfg        g_uart1_cfg
#define renesas_uart_callback   user_uart1_callback
#elif defined(RT_NANO_CONSOLE_UART2)
#define renesas_uart_ctrl       g_uart2_ctrl
#define renesas_uart_cfg        g_uart2_cfg
#define renesas_uart_callback   user_uart2_callback
#elif defined(RT_NANO_CONSOLE_UART3)
#define renesas_uart_ctrl       g_uart3_ctrl
#define renesas_uart_cfg        g_uart3_cfg
#define renesas_uart_callback   user_uart3_callback
#elif defined(RT_NANO_CONSOLE_UART4)
#define renesas_uart_ctrl       g_uart4_ctrl
#define renesas_uart_cfg        g_uart4_cfg
#define renesas_uart_callback   user_uart4_callback
#elif defined(RT_NANO_CONSOLE_UART5)
#define renesas_uart_ctrl       g_uart5_ctrl
#define renesas_uart_cfg        g_uart5_cfg
#define renesas_uart_callback   user_uart5_callback
#elif defined(RT_NANO_CONSOLE_UART6)
#define renesas_uart_ctrl       g_uart6_ctrl
#define renesas_uart_cfg        g_uart6_cfg
#define renesas_uart_callback   user_uart6_callback
#elif defined(RT_NANO_CONSOLE_UART7)
#define renesas_uart_ctrl       g_uart7_ctrl
#define renesas_uart_cfg        g_uart7_cfg
#define renesas_uart_callback   user_uart7_callback
#elif defined(RT_NANO_CONSOLE_UART8)
#define renesas_uart_ctrl       g_uart8_ctrl
#define renesas_uart_cfg        g_uart8_cfg
#define renesas_uart_callback   user_uart8_callback
#elif defined(RT_NANO_CONSOLE_UART9)
#define renesas_uart_ctrl       g_uart9_ctrl
#define renesas_uart_cfg        g_uart9_cfg
#define renesas_uart_callback   user_uart9_callback
#endif

void rt_hw_console_init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    rt_err_t res = RT_EOK;

    res = rt_sem_init(&console_sem, "console", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(res == RT_EOK);

    /* Initialize UART using FSP */
#ifdef SOC_SERIES_R7FA8M85
    err = R_SCI_B_UART_Open(&renesas_uart_ctrl, &renesas_uart_cfg);
#else
    err = R_SCI_UART_Open(&renesas_uart_ctrl, &renesas_uart_cfg);
#endif
    if (FSP_SUCCESS != err)
    {
        while (1); /* Trap on failure */
    }
    return;
}

void console_send_byte(uint8_t ch)
{
    renesas_uart_ctrl.p_reg->TDR = ch;
#if defined(SOC_SERIES_R7FA8M85) || defined(SOC_SERIES_R9A07G0)
    while ((renesas_uart_ctrl.p_reg->CSR_b.TEND) == 0);
#else
    while ((renesas_uart_ctrl.p_reg->SSR_b.TEND) == 0);
#endif
}

void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    size = rt_strlen(str);

    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            console_send_byte((uint8_t) a);
        }
        console_send_byte(*(str + i));
    }
}

void renesas_uart_callback(uart_callback_args_t *p_args)
{
    /* Handle the UART event */
    switch (p_args->event)
    {
        /* Received a character or receive completed */
        case UART_EVENT_RX_CHAR:
        case UART_EVENT_RX_COMPLETE:
            rt_sem_release(&console_sem);
            break;

        default:
            break;
    }
}

char rt_hw_console_getchar(void)
{
    int ch = -1;
    rt_sem_take(&console_sem, RT_WAITING_FOREVER);
#ifdef SOC_SERIES_R7FA8M85
    fsp_err_t ret = R_SCI_B_UART_Read(&renesas_uart_ctrl, (uint8_t *)&ch, 1);
#else
    fsp_err_t ret = R_SCI_UART_Read(&renesas_uart_ctrl, (uint8_t *)&ch, 1);
#endif
    if(ret != FSP_SUCCESS)
    {
        ch = -1;
        rt_thread_mdelay(10);
    }
    return ch;
}
#endif
