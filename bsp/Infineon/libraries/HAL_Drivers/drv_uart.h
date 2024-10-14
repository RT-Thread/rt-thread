/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-29     Rbb666       first version
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include <rthw.h>
#include <rtdevice.h>

#include "board.h"

#define  uart_isr_callback(name) name##_isr_callback

struct ifx_uart_config
{
    cyhal_uart_t *uart_obj;

    const char *name;
    rt_uint32_t tx_pin;
    rt_uint32_t rx_pin;
    CySCB_Type *usart_x;
#if defined(SOC_SERIES_IFX_XMC)
    rt_uint32_t intrSrc;
#else
    IRQn_Type intrSrc;
#endif
    cy_israddress userIsr;
    cy_stc_sysint_t *UART_SCB_IRQ_cfg;
};

struct ifx_uart
{
    struct ifx_uart_config *config;
    struct rt_serial_device serial;
};

void rt_hw_uart_init(void);

#endif
