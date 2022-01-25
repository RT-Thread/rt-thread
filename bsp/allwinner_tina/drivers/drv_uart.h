/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */


#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#define UART0_BASE_ADDR (0x01C25000)
#define UART1_BASE_ADDR (0x01C25400)
#define UART2_BASE_ADDR (0x01C25800)

#define UART_THR        (0X00)
#define UART_RHB        (0X00)
#define UART_DLL        (0X00)
#define UART_DLH        (0X04)
#define UART_IER        (0X04)
#define UART_IIR        (0X08)
#define UART_FCR        (0X08)
#define UART_LCR        (0X0C)
#define UART_MCR        (0X10)
#define UART_LSR        (0X14)
#define UART_MSR        (0X18)
#define UART_SCH        (0X1C)
#define UART_USR        (0X7C)
#define UART_TFL        (0X80)
#define UART_RFL        (0X84)
#define UART_HSK        (0X88)
#define UART_HALT       (0XA4)
#define UART_DBG_DLL    (0XB0)
#define UART_DBG_DLH    (0XB4)

struct tina_uart
{
    volatile rt_uint32_t rx_tx_dll;          /* 0x00 */
    volatile rt_uint32_t dlh_ier;           /* 0x04 */
    volatile rt_uint32_t iir_fcr;           /* 0x08 */
    volatile rt_uint32_t lcr;               /* 0x0C */
    volatile rt_uint32_t mcr;               /* 0x10 */
    volatile rt_uint32_t lsr;               /* 0x14 */
    volatile rt_uint32_t msr;               /* 0x18 */
    volatile rt_uint32_t sch;               /* 0x1C */
    volatile rt_uint32_t reserved0[23];
    volatile rt_uint32_t usr;               /* 0x7c */
    volatile rt_uint32_t tfl;               /* 0x80 */
    volatile rt_uint32_t rfl;               /* 0x84 */
    volatile rt_uint32_t hsk;               /* 0x88 */
    volatile rt_uint32_t reserved1[6];
    volatile rt_uint32_t halt;              /* 0xa4 */
    volatile rt_uint32_t reserved2[2];
    volatile rt_uint32_t dbg_dll;           /* 0xb0 */
    volatile rt_uint32_t dbg_dlh;           /* 0xb4 */
};

typedef struct tina_uart *tina_uart_t;

#define UART0 ((tina_uart_t)UART0_BASE_ADDR)
#define UART1 ((tina_uart_t)UART1_BASE_ADDR)
#define UART2 ((tina_uart_t)UART2_BASE_ADDR)

int rt_hw_uart_init(void);

#endif /* __DRV_UART_H__ */
