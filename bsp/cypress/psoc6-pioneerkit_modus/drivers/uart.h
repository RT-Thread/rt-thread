
#ifndef __UART_H__
#define __UART_H__

#include <rthw.h>
#include <rtthread.h>
#include "cy_device_headers.h"
#include "board.h"
#include "cy_pdl.h"

#define UART_RX_BUFFER_SIZE         128u
#define UART_TX_BUFFER_SIZE         128u

#define UART_ENABLE_IRQ(n)          NVIC_EnableIRQ((n))
#define UART_DISABLE_IRQ(n)         NVIC_DisableIRQ((n))

struct uart_int_rx
{
    rt_uint8_t  rx_buffer[UART_RX_BUFFER_SIZE];
    rt_uint32_t read_index, save_index;
};

struct uart_int_tx
{
    rt_uint8_t  tx_buffer[UART_TX_BUFFER_SIZE];
    rt_uint32_t write_index, save_index;
};

struct uart_device
{
    CySCB_Type* scb_device;
    /* uart config */
    cy_stc_scb_uart_config_t const *uart_config;
    /* uart context */
    cy_stc_scb_uart_context_t *uart_context;
    /* uart interrupt */
    const cy_stc_sysint_t *uart_int;
    /* irq number */
    IRQn_Type rx_irq;
    IRQn_Type tx_irq;

    /* rx structure */
    struct uart_int_rx* int_rx;
    /* tx structure */
    struct uart_int_tx* int_tx;
};

void rt_hw_uart_init(void);

#endif
