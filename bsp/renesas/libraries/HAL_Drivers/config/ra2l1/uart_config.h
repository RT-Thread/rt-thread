/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-07-29     KyleChan          first version
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>
#include "hal_data.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_UART0)
#ifndef UART0_CONFIG
#define UART0_CONFIG                                                \
    {                                                               \
        .name = "uart0",                                            \
        .p_api_ctrl = &g_uart0_ctrl,                                \
        .p_cfg = &g_uart0_cfg,                                      \
    }
#endif /* UART0_CONFIG */
#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                                                \
    {                                                               \
        .name = "uart1",                                            \
        .p_api_ctrl = &g_uart1_ctrl,                                \
        .p_cfg = &g_uart1_cfg,                                      \
    }
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG                                                \
    {                                                               \
        .name = "uart2",                                            \
        .p_api_ctrl = &g_uart2_ctrl,                                \
        .p_cfg = &g_uart2_cfg,                                      \
    }
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                                                \
    {                                                               \
        .name = "uart3",                                            \
        .p_api_ctrl = &g_uart3_ctrl,                                \
        .p_cfg = &g_uart3_cfg,                                      \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART9)
#ifndef UART9_CONFIG
#define UART9_CONFIG                                                \
    {                                                               \
        .name = "uart9",                                            \
        .p_api_ctrl = &g_uart9_ctrl,                                \
        .p_cfg = &g_uart9_cfg,                                      \
    }
#endif /* UART9_CONFIG */
#endif /* BSP_USING_UART9 */

#ifdef __cplusplus
}
#endif

#endif
