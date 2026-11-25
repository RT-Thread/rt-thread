/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-02-17     yeml    first version
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(BSP_USING_UART0)
#ifndef UART0_CONFIG
#define UART0_CONFIG            \
    {                           \
        .name = "uart0",        \
        .irq_type = UART0_IRQn, \
    }
#endif /* UART0_CONFIG */
#endif /* BSP_USING_UART0 */	

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG            \
    {                           \
        .name = "uart1",        \
        .irq_type = UART1_IRQn, \
    }
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1 */	

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG            \
    {                           \
        .name = "uart2",        \
        .irq_type = UART2_IRQn, \
    }
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2 */	

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG            \
    {                           \
        .name = "uart3",        \
        .irq_type = UART3_IRQn, \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */	

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG            \
    {                           \
        .name = "uart4",        \
        .irq_type = UART4_IRQn, \
    }
#endif /* UART4_CONFIG */
#endif /* BSP_USING_UART4 */	


#ifdef __cplusplus
}
#endif

#endif
