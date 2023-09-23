/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-15     Emuzit            first version
 */
#include <rthw.h>
#include <ipc/completion.h>
#include <ipc/dataqueue.h>
#ifdef RT_USING_SERIAL_V2
    #include <drivers/serial_v2.h>
#else
    #include <drivers/serial.h>
#endif
#include <drivers/pin.h>
#include "ch56x_sys.h"
#include "ch56x_uart.h"
#include "isr_sp.h"

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3)
    #error "Please define at least one UARTx"
#endif

/* Type of irqn/rxd_pin/txd_pin are per uart driver perspective
 * to save some space, still compatible to RT api call, anyway.
*/
struct serial_device
{
    struct rt_serial_device parent;
    volatile struct uart_registers *reg_base;
    uint8_t irqn;
    uint8_t resv;
    uint8_t rxd_pin;
    uint8_t txd_pin;
    char *name;
};

#ifdef BSP_USING_UART0
static struct serial_device serial_device_0 =
{
    .reg_base = (struct uart_registers *)UART0_REG_BASE,
    .irqn = UART0_IRQn,
#ifndef BSP_USING_UART0_PIN_ALT
    .rxd_pin = UART_RXD0_PIN,
    .txd_pin = UART_TXD0_PIN,
#else
    .rxd_pin = UART_RXD0_ALT,
    .txd_pin = UART_TXD0_ALT,
#endif
    .name = "uart0",
};
#endif

#ifdef BSP_USING_UART1
static struct serial_device serial_device_1 =
{
    .reg_base = (struct uart_registers *)UART1_REG_BASE,
    .irqn = UART1_IRQn,
    .rxd_pin = UART_RXD1_PIN,
    .txd_pin = UART_TXD1_PIN,
    .name = "uart1",
};
#endif

#ifdef BSP_USING_UART2
static struct serial_device serial_device_2 =
{
    .reg_base = (struct uart_registers *)UART2_REG_BASE,
    .irqn = UART2_IRQn,
    .rxd_pin = UART_RXD2_PIN,
    .txd_pin = UART_TXD2_PIN,
    .name = "uart2",
};
#endif

#ifdef BSP_USING_UART3
static struct serial_device serial_device_3 =
{
    .reg_base = (struct uart_registers *)UART3_REG_BASE,
    .irqn = UART3_IRQn,
    .rxd_pin = UART_RXD3_PIN,
    .txd_pin = UART_TXD3_PIN,
    .name = "uart3",
};
#endif

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct serial_device *serial_device = (struct serial_device *)serial;
    volatile struct uart_registers *uxreg = serial_device->reg_base;

    union _uart_fcr fcr;
    union _uart_lcr lcr;
    uint32_t x;

    x = 10 * sys_hclk_get() / 8 / cfg->baud_rate;
    x = (x + 5) / 10;
    uxreg->DL = x;
    uxreg->DIV = 1;

    lcr.reg = 0;
    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        lcr.word_sz = LCR_DATA_BITS_5;
        break;
    case DATA_BITS_6:
        lcr.word_sz = LCR_DATA_BITS_6;
        break;
    case DATA_BITS_7:
        lcr.word_sz = LCR_DATA_BITS_7;
        break;
    case DATA_BITS_8:
    default:
        lcr.word_sz = LCR_DATA_BITS_8;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        lcr.stop_bit = LCR_STOP_BITS_2;
        break;
    case STOP_BITS_1:
    default:
        lcr.stop_bit = LCR_STOP_BITS_1;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        lcr.par_mod = LCR_PARITY_ODD;
        lcr.par_en = 1;
        break;
    case PARITY_EVEN:
        lcr.par_mod = LCR_PARITY_EVEN;
        lcr.par_en = 1;
        break;
    case PARITY_NONE:
    default:
        lcr.par_en = 0;
        break;
    }
    uxreg->LCR.reg = lcr.reg;

    fcr.reg = RB_FCR_FIFO_EN | RB_FCR_RX_FIFO_CLR | RB_FCR_TX_FIFO_CLR;
    fcr.fifo_trig = UART_1BYTE_TRIG;
    uxreg->FCR.reg = fcr.reg;

    /* TXD pin output enable */
    uxreg->IER.txd_en = 1;

    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *args)
{
    struct serial_device *serial_device = (struct serial_device *)serial;
    volatile struct uart_registers *uxreg = serial_device->reg_base;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        uxreg->IER.recv_rdy = 0;
        uxreg->IER.line_stat = 0;
        uxreg->IER.thr_empty = 0;
        rt_hw_interrupt_mask(serial_device->irqn);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        uxreg->FCR.fifo_trig = UART_1BYTE_TRIG;
        uxreg->MCR.int_oe = 1;
        uxreg->IER.recv_rdy = 1;
        uxreg->IER.line_stat = 1;
        if (serial->parent.open_flag & RT_DEVICE_FLAG_INT_TX)
        {
            uxreg->IER.thr_empty = 1;
        }
        rt_hw_interrupt_umask(serial_device->irqn);
        break;
    default:
        break;
    }

    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char ch)
{
    struct serial_device *serial_device = (struct serial_device *)serial;
    volatile struct uart_registers *uxreg = serial_device->reg_base;

    if (serial->parent.open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        if (uxreg->TFC >= UART_FIFO_SIZE)
            return -1;
    }
    else
    {
        while (uxreg->TFC >= UART_FIFO_SIZE)
        {
            if (rt_thread_self() && rt_interrupt_get_nest() == 0)
                rt_thread_yield();
        }
    }
    uxreg->THR = ch;

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    struct serial_device *serial_device = (struct serial_device *)serial;
    volatile struct uart_registers *uxreg = serial_device->reg_base;

    /* UART_II_RECV_RDY is cleared by reading RBR */
    return (uxreg->RFC > 0) ? uxreg->RBR : -1;
}

static const struct rt_uart_ops uart_ops =
{
    .configure = uart_configure,
    .control = uart_control,
    .putc = uart_putc,
    .getc = uart_getc,
    .dma_transmit = RT_NULL,
};

int rt_hw_uart_init(void)
{
    struct serial_device *devices[4];

    /* Note: HCLK should be at least 8MHz for default 115200 baud to work */
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    int n = 0;

#ifdef BSP_USING_UART3
    devices[n++] = &serial_device_3;
#endif
#ifdef BSP_USING_UART2
    devices[n++] = &serial_device_2;
#endif
#ifdef BSP_USING_UART1
    devices[n++] = &serial_device_1;
#endif
#ifdef BSP_USING_UART0
    devices[n++] = &serial_device_0;
#endif

    while (--n >= 0)
    {
        uint32_t flag;
        struct serial_device *serial = devices[n];
        serial->parent.ops = &uart_ops;
        serial->parent.config = config;

        rt_pin_mode(serial->txd_pin, PIN_MODE_OUTPUT);
        rt_pin_mode(serial->rxd_pin, PIN_MODE_INPUT_PULLUP);

        sys_clk_off_by_irqn(serial->irqn, SYS_SLP_CLK_ON);

        flag = RT_DEVICE_FLAG_RDWR   |
               RT_DEVICE_FLAG_STREAM |  // for converting '\n'
               RT_DEVICE_FLAG_INT_TX |
               RT_DEVICE_FLAG_INT_RX ;
        rt_hw_serial_register(&serial->parent, serial->name, flag, RT_NULL);

        /* rt_serial_open => uart_control with RT_DEVICE_CTRL_SET_INT */
    }

    return 0;
}

static void _uart_isr_common(struct serial_device *serial_device)
{
    struct rt_serial_device *serial = &serial_device->parent;
    volatile struct uart_registers *uxreg = serial_device->reg_base;

    switch (uxreg->IIR.int_mask)
    {
    case UART_II_RECV_TOUT:
        /* FIXME: It's a bad idea to read RBR to clear UART_II_RECV_TOUT.
         * Race condition may happen that actual rx data is dropped.
        */
        if (uxreg->RFC == 0)
        {
            uxreg->RBR;
            //rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_TIMEOUT);
            break;
        }
        /* pass through as if UART_II_RECV_RDY */
    case UART_II_RECV_RDY:
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        break;
    case UART_II_THR_EMPTY:
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
        break;
    case UART_II_LINE_STAT:
        uxreg->LSR;
        break;
    case UART_II_MODEM_CHG:
        uxreg->MSR;
        break;
    case UART_II_SLV_ADDR:
        uxreg->IIR;
        break;
    default:
        break;
    }
}

#ifdef BSP_USING_UART0
void uart0_irq_handler(void) __attribute__((interrupt()));
void uart0_irq_handler(void)
{
    isr_sp_enter();
    rt_interrupt_enter();
    _uart_isr_common(&serial_device_0);
    rt_interrupt_leave();
    isr_sp_leave();
}
#endif

#ifdef BSP_USING_UART1
void uart1_irq_handler(void) __attribute__((interrupt()));
void uart1_irq_handler(void)
{
    isr_sp_enter();
    rt_interrupt_enter();
    _uart_isr_common(&serial_device_1);
    rt_interrupt_leave();
    isr_sp_leave();
}
#endif

#ifdef BSP_USING_UART2
void uart2_irq_handler(void) __attribute__((interrupt()));
void uart2_irq_handler(void)
{
    isr_sp_enter();
    rt_interrupt_enter();
    _uart_isr_common(&serial_device_2);
    rt_interrupt_leave();
    isr_sp_leave();
}
#endif

#ifdef BSP_USING_UART3
void uart3_irq_handler(void) __attribute__((interrupt()));
void uart3_irq_handler(void)
{
    isr_sp_enter();
    rt_interrupt_enter();
    _uart_isr_common(&serial_device_3);
    rt_interrupt_leave();
    isr_sp_leave();
}
#endif
