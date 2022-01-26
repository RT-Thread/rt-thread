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

#if defined(BSP_USING_UART6)
#ifndef UART6_CONFIG
#define UART6_CONFIG                                                \
    {                                                               \
        .name = "uart6",                                            \
        .p_api_ctrl = &g_uart6_ctrl,                                \
        .p_cfg = &g_uart6_cfg,                                      \
    }
#endif /* UART6_CONFIG */
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
#ifndef UART7_CONFIG
#define UART7_CONFIG                                                \
    {                                                               \
        .name = "uart7",                                            \
        .p_api_ctrl = &g_uart7_ctrl,                                \
        .p_cfg = &g_uart7_cfg,                                      \
    }
#endif /* UART7_CONFIG */
#endif /* BSP_USING_UART7 */

#ifdef __cplusplus
}
#endif

#endif
