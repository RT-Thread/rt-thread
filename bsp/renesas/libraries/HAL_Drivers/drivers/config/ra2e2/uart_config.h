/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
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
