/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-01     THEWON       first version for serialX
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include "NuMicro.h"
#include <drv_sys.h>

typedef void(*uart_isr_cb)(int, void*);

/* Private typedef --------------------------------------------------------------*/
struct nu_uart
{
    struct rt_serial_device dev;
    char *name;
    UART_T *uart_base;
    IRQn_Type irqn;
    E_SYS_IPRST rstidx;
    E_SYS_IPCLK clkidx;

#if defined(RT_SERIAL_USING_DMA)
    uint32_t dma_flag;
    int16_t pdma_perp_tx;
    int8_t  pdma_chanid_tx;

    int16_t pdma_perp_rx;
    int8_t  pdma_chanid_rx;
    int32_t rx_write_offset;
    int32_t rxdma_trigger_len;

    nu_pdma_desc_t pdma_rx_desc;
#endif

};
typedef struct nu_uart *nu_uart_t;

#if defined(BSP_USING_UART0)
#ifndef UART0_CONFIG
#define UART0_CONFIG                                                \
    {                                                               \
        .name = "uart0",                                            \
        .uart_base = UART0,                                         \
        .irqn = IRQ_UART0,                                          \
        .rstidx = UART0RST,                                         \
        .clkidx = UART0CKEN,                                        \
    }
#endif /* UART0_CONFIG */

#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                                                \
    {                                                               \
        .name = "uart1",                                            \
        .uart_base = UART1,                                         \
        .irqn = IRQ_UART1,                                          \
        .rstidx = UART1RST,                                         \
        .clkidx = UART1CKEN,                                        \
    }
#endif /* UART1_CONFIG */

#endif /* BSP_USING_UART1 */

int rt_hw_uart_init(void);

#endif  /* __DRV_UART_H__ */
