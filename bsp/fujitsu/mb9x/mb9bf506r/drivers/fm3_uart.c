/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-05-15     lgnq         first  version.
 * 2012-05-28     heyuanjie87  change interfaces
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "fm3_uart.h"

#if (defined(RT_USING_UART0_0) || defined(RT_USING_UART0_1))
/* UART0 device driver structure */
struct uart03_device uart0 =
{
    FM3_MFS0_UART,
    MFS0RX_IRQn,
    MFS0TX_IRQn,
};
struct rt_serial_device serial0;

void MFS0RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if (defined(RT_USING_UART1_0) || defined(RT_USING_UART1_1))
/* UART1 device driver structure */
struct uart03_device uart1 =
{
    FM3_MFS1_UART,
    MFS1RX_IRQn,
    MFS1TX_IRQn,
};
struct rt_serial_device serial1;

void MFS1RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if (defined(RT_USING_UART2_0) || defined(RT_USING_UART2_1) || defined(RT_USING_UART2_2))
/* UART2 device driver structure */
struct uart03_device uart2 =
{
    FM3_MFS2_UART,
    MFS2RX_IRQn,
    MFS2TX_IRQn,
};
struct rt_serial_device serial2;

void MFS2RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if (defined(RT_USING_UART3_0) || defined(RT_USING_UART3_1) || defined(RT_USING_UART3_2))
/* UART3 device driver structure */
struct uart03_device uart3 =
{
    FM3_MFS3_UART,
    MFS3RX_IRQn,
    MFS3TX_IRQn,
};
struct rt_serial_device serial3;

void MFS3RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_RX_IND);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if (defined(RT_USING_UART4_0) || defined(RT_USING_UART4_1) || defined(RT_USING_UART4_2))
/* UART4 device driver structure */
struct uart47_device uart4 =
{
    FM3_MFS4_UART,
    MFS4RX_IRQn,
    MFS4TX_IRQn,
    FIFO_SIZE,
};
struct rt_serial_device serial4;

void MFS4RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_serial_isr(&serial4, RT_SERIAL_EVENT_RX_IND);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if (defined(RT_USING_UART5_0) || defined(RT_USING_UART5_1) || defined(RT_USING_UART5_2))
/* UART5 device driver structure */
struct uart47_device uart5 =
{
    FM3_MFS5_UART,
    MFS5RX_IRQn,
    MFS5TX_IRQn,
    FIFO_SIZE,
};
struct rt_serial_device serial5;

void MFS5RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_serial_isr(&serial5, RT_SERIAL_EVENT_RX_IND);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if (defined(RT_USING_UART6_0) || defined(RT_USING_UART6_1))
/* UART6 device driver structure */
struct uart47_device uart6 =
{
    FM3_MFS6_UART,
    MFS6RX_IRQn,
    MFS6TX_IRQn,
    FIFO_SIZE,
};
struct rt_serial_device serial6;

void MFS6RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_serial_isr(&serial6, RT_SERIAL_EVENT_RX_IND);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if (defined(RT_USING_UART7_0) || defined(RT_USING_UART7_1))
/* UART7 device driver structure */
struct uart47_device uart7 =
{
    FM3_MFS7_UART,
    MFS7RX_IRQn,
    MFS7TX_IRQn,
    FIFO_SIZE,
};
struct rt_serial_device serial7;

void MFS7RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_serial_isr(&serial7, RT_SERIAL_EVENT_RX_IND);
    /* leave interrupt */
    rt_interrupt_leave();
}

#endif

void uart_pin_setup(void)
{
#if defined(RT_USING_UART0_0)
    /* Set UART Ch0 Port, SIN0_0(P21), SOT0_0(P22) */
    FM3_GPIO->PFR2_f.P1 = 1;
    FM3_GPIO->PFR2_f.P2 = 1;
    FM3_GPIO->EPFR07_f.SIN0S0 = 1;
    FM3_GPIO->EPFR07_f.SIN0S1 = 0;
    FM3_GPIO->EPFR07_f.SOT0B0 = 1;
    FM3_GPIO->EPFR07_f.SOT0B1 = 0;
#elif defined(RT_USING_UART0_1)
    /* Set UART Ch0 Port, SIN0_1(P14), SOT0_1(P15) */
    FM3_GPIO->PFR1_f.P4 = 1;
    FM3_GPIO->PFR1_f.P5 = 1;
    FM3_GPIO->EPFR07_f.SIN0S0 = 0;
    FM3_GPIO->EPFR07_f.SIN0S1 = 1;
    FM3_GPIO->EPFR07_f.SOT0B0 = 0;
    FM3_GPIO->EPFR07_f.SOT0B1 = 1;
#endif

#if defined(RT_USING_UART1_0)
    /* Set UART Ch1 Port, SIN1_0(P56), SOT1_0(P57) */
    FM3_GPIO->PFR5_f.P6 = 1;
    FM3_GPIO->PFR5_f.P7 = 1;
    FM3_GPIO->EPFR07_f.SIN1S0 = 1;
    FM3_GPIO->EPFR07_f.SIN1S1 = 0;
    FM3_GPIO->EPFR07_f.SOT1B0 = 1;
    FM3_GPIO->EPFR07_f.SOT1B1 = 0;
#elif defined(RT_USING_UART1_1)
    /* Set UART Ch1 Port, SIN1_1(P11), SOT1_1(P12) */
    FM3_GPIO->PFR1_f.P1 = 1;
    FM3_GPIO->PFR1_f.P2 = 1;
    FM3_GPIO->EPFR07_f.SIN1S0 = 0;
    FM3_GPIO->EPFR07_f.SIN1S1 = 1;
    FM3_GPIO->EPFR07_f.SOT1B0 = 0;
    FM3_GPIO->EPFR07_f.SOT1B1 = 1;
#endif

#if defined(RT_USING_UART2_0)
    /* Set UART Ch2 Port, SIN2_0(P72), SOT2_0(P73) */
    FM3_GPIO->PFR7_f.P2 = 1;
    FM3_GPIO->PFR7_f.P3 = 1;
    FM3_GPIO->EPFR07_f.SIN2S0 = 1;
    FM3_GPIO->EPFR07_f.SIN2S1 = 0;
    FM3_GPIO->EPFR07_f.SOT2B0 = 1;
    FM3_GPIO->EPFR07_f.SOT2B1 = 0;
#elif defined(RT_USING_UART2_1)
    /* Set UART Ch2 Port, SIN2_1(P24), SOT2_1(P25) */
    FM3_GPIO->PFR2_f.P4 = 1;
    FM3_GPIO->PFR2_f.P5 = 1;
    FM3_GPIO->EPFR07_f.SIN2S0 = 0;
    FM3_GPIO->EPFR07_f.SIN2S1 = 1;
    FM3_GPIO->EPFR07_f.SOT2B0 = 0;
    FM3_GPIO->EPFR07_f.SOT2B1 = 1;
#elif defined(RT_USING_UART2_2)
    /* Set UART Ch2 Port, SIN2_2(P17), SOT2_2(P18) */
    FM3_GPIO->PFR1_f.P7 = 1;
    FM3_GPIO->PFR1_f.P8 = 1;
    FM3_GPIO->EPFR07_f.SIN2S0 = 1;
    FM3_GPIO->EPFR07_f.SIN2S1 = 1;
    FM3_GPIO->EPFR07_f.SOT2B0 = 1;
    FM3_GPIO->EPFR07_f.SOT2B1 = 1;
#endif

#if defined(RT_USING_UART3_0)
    /* Set UART Ch3 Port, SIN3_0(P66), SOT3_0(P67) */
    FM3_GPIO->PFR6_f.P6 = 1;
    FM3_GPIO->PFR6_f.P7 = 1;
    FM3_GPIO->EPFR07_f.SIN3S0 = 1;
    FM3_GPIO->EPFR07_f.SIN3S1 = 0;
    FM3_GPIO->EPFR07_f.SOT3B0 = 1;
    FM3_GPIO->EPFR07_f.SOT3B1 = 0;
#elif defined(RT_USING_UART3_1)
    /* Set UART Ch3 Port, SIN3_1(P50), SOT3_1(P51) */
    FM3_GPIO->PFR5_f.P0 = 1;
    FM3_GPIO->PFR5_f.P1 = 1;
    FM3_GPIO->EPFR07_f.SIN3S0 = 0;
    FM3_GPIO->EPFR07_f.SIN3S1 = 1;
    FM3_GPIO->EPFR07_f.SOT3B0 = 0;
    FM3_GPIO->EPFR07_f.SOT3B1 = 1;
#elif defined(RT_USING_UART3_2)
    /* Set UART Ch3 Port, SIN3_2(P48), SOT3_2(P49) */
    FM3_GPIO->PFR4_f.P8 = 1;
    FM3_GPIO->PFR4_f.P9 = 1;
    FM3_GPIO->EPFR07_f.SIN3S0 = 1;
    FM3_GPIO->EPFR07_f.SIN3S1 = 1;
    FM3_GPIO->EPFR07_f.SOT3B0 = 1;
    FM3_GPIO->EPFR07_f.SOT3B1 = 1;
#endif

#if defined(RT_USING_UART4_0)
    /* Set UART Ch4 Port, SIN4_0(P0A), SOT4_0(P0B), CTS4_0(P0E), RTS4_0(P0D) */
    FM3_GPIO->PFR0_f.PA = 1;
    FM3_GPIO->PFR0_f.PB = 1;
    FM3_GPIO->PFR0_f.PD = 1;
    FM3_GPIO->PFR0_f.PE = 1;
    FM3_GPIO->EPFR08_f.SIN4S0 = 1;
    FM3_GPIO->EPFR08_f.SIN4S1 = 0;
    FM3_GPIO->EPFR08_f.SOT4B0 = 1;
    FM3_GPIO->EPFR08_f.SOT4B1 = 0;
    FM3_GPIO->EPFR08_f.CTS4S0 = 1;
    FM3_GPIO->EPFR08_f.CTS4S1 = 0;
    FM3_GPIO->EPFR08_f.RTS4E0 = 1;
    FM3_GPIO->EPFR08_f.RTS4E1 = 0;
#elif defined(RT_USING_UART4_1)
    /* Set UART Ch4 Port, SIN4_1(P1A), SOT4_1(P1B), CTS4_1(P1D), RTS4_1(P1E) */
    FM3_GPIO->PFR1_f.PA = 1;
    FM3_GPIO->PFR1_f.PB = 1;
    FM3_GPIO->PFR1_f.PD = 1;
    FM3_GPIO->PFR1_f.PE = 1;
    FM3_GPIO->EPFR08_f.SIN4S0 = 0;
    FM3_GPIO->EPFR08_f.SIN4S1 = 1;
    FM3_GPIO->EPFR08_f.SOT4B0 = 0;
    FM3_GPIO->EPFR08_f.SOT4B1 = 1;
    FM3_GPIO->EPFR08_f.CTS4S0 = 0;
    FM3_GPIO->EPFR08_f.CTS4S1 = 1;
    FM3_GPIO->EPFR08_f.RTS4E0 = 0;
    FM3_GPIO->EPFR08_f.RTS4E1 = 1;
#elif defined(RT_USING_UART4_2)
    /* Set UART Ch4 Port, SIN4_2(P05), SOT4_2(P06), CTS4_2(P08), RTS4_2(P09)*/
    FM3_GPIO->PFR0_f.P5 = 1;
    FM3_GPIO->PFR0_f.P6 = 1;
    FM3_GPIO->PFR0_f.P8 = 1;
    FM3_GPIO->PFR0_f.P9 = 1;
    FM3_GPIO->EPFR08_f.SIN4S0 = 1;
    FM3_GPIO->EPFR08_f.SIN4S1 = 1;
    FM3_GPIO->EPFR08_f.SOT4B0 = 1;
    FM3_GPIO->EPFR08_f.SOT4B1 = 1;
    FM3_GPIO->EPFR08_f.CTS4S0 = 1;
    FM3_GPIO->EPFR08_f.CTS4S1 = 1;
    FM3_GPIO->EPFR08_f.RTS4E0 = 1;
    FM3_GPIO->EPFR08_f.RTS4E1 = 1;
#endif

#if defined(RT_USING_UART5_0)
    /* Set UART Ch5 Port, SIN5_0(P60), SOT5_0(P61) */
    FM3_GPIO->PFR6_f.P0 = 1;
    FM3_GPIO->PFR6_f.P1 = 1;
    FM3_GPIO->EPFR08_f.SIN5S0 = 1;
    FM3_GPIO->EPFR08_f.SIN5S1 = 0;
    FM3_GPIO->EPFR08_f.SOT5B0 = 1;
    FM3_GPIO->EPFR08_f.SOT5B1 = 0;
#elif defined(RT_USING_UART5_1)
    /* Set UART Ch5 Port, SIN5_1(P63), SOT5_1(P64) */
    FM3_GPIO->PFR6_f.P3 = 1;
    FM3_GPIO->PFR6_f.P4 = 1;
    FM3_GPIO->EPFR08_f.SIN5S0 = 0;
    FM3_GPIO->EPFR08_f.SIN5S1 = 1;
    FM3_GPIO->EPFR08_f.SOT5B0 = 0;
    FM3_GPIO->EPFR08_f.SOT5B1 = 1;
#elif defined(RT_USING_UART5_2)
    /* Set UART Ch5 Port, SIN5_2(P36), SOT5_2(P37) */
    FM3_GPIO->PFR3_f.P6 = 1;
    FM3_GPIO->PFR3_f.P7 = 1;
    FM3_GPIO->EPFR08_f.SIN5S0 = 1;
    FM3_GPIO->EPFR08_f.SIN5S1 = 1;
    FM3_GPIO->EPFR08_f.SOT5B0 = 1;
    FM3_GPIO->EPFR08_f.SOT5B1 = 1;
#endif

#if defined(RT_USING_UART6_0)
    /* Set UART Ch6 Port, SIN6_0(P53), SOT6_0(P54) */
    FM3_GPIO->PFR5_f.P3 = 1;
    FM3_GPIO->PFR5_f.P4 = 1;
    FM3_GPIO->EPFR08_f.SIN6S0 = 1;
    FM3_GPIO->EPFR08_f.SIN6S1 = 0;
    FM3_GPIO->EPFR08_f.SOT6B0 = 1;
    FM3_GPIO->EPFR08_f.SOT6B1 = 0;
#elif defined(RT_USING_UART6_1)
    /* Set UART Ch6 Port, SIN6_1(P33), SOT6_1(P32) */
    FM3_GPIO->PFR3_f.P2 = 1;
    FM3_GPIO->PFR3_f.P3 = 1;
    FM3_GPIO->EPFR08_f.SIN6S0 = 0;
    FM3_GPIO->EPFR08_f.SIN6S1 = 1;
    FM3_GPIO->EPFR08_f.SOT6B0 = 0;
    FM3_GPIO->EPFR08_f.SOT6B1 = 1;
#endif

#if defined(RT_USING_UART7_0)
    /* Set UART Ch7 Port, SIN7_0(P59), SOT7_0(P5A) */
    FM3_GPIO->PFR5_f.P9 = 1;
    FM3_GPIO->PFR5_f.PA = 1;
    FM3_GPIO->EPFR08_f.SIN7S0 = 1;
    FM3_GPIO->EPFR08_f.SIN7S1 = 0;
    FM3_GPIO->EPFR08_f.SOT7B0 = 1;
    FM3_GPIO->EPFR08_f.SOT7B1 = 0;
#elif defined(RT_USING_UART7_1)
    /* Set UART Ch7 Port, SIN7_1(P4E), SOT7_1(P4D) */
    FM3_GPIO->PFR4_f.PD = 1;
    FM3_GPIO->PFR4_f.PE = 1;
    FM3_GPIO->EPFR08_f.SIN7S0 = 0;
    FM3_GPIO->EPFR08_f.SIN7S1 = 1;
    FM3_GPIO->EPFR08_f.SOT7B0 = 0;
    FM3_GPIO->EPFR08_f.SOT7B1 = 1;
#endif
}

static rt_err_t uart03_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct uart03_device *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct uart03_device *)serial->parent.user_data;

    uart->uart_regs->SMR = SMR_MD_UART | SMR_SOE;

    /* set baudreate */
    uart->uart_regs->BGR = (40000000UL + (cfg->baud_rate/2))/cfg->baud_rate - 1;

    /* set stop bits */
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->uart_regs->SMR_f.SBL = 0;
        uart->uart_regs->ESCR_f.ESBL = 0;
        break;
    case STOP_BITS_2:
        uart->uart_regs->SMR_f.SBL = 1;
        uart->uart_regs->ESCR_f.ESBL = 0;
        break;
    case STOP_BITS_3:
        uart->uart_regs->SMR_f.SBL = 0;
        uart->uart_regs->ESCR_f.ESBL = 1;
        break;
    case STOP_BITS_4:
        uart->uart_regs->SMR_f.SBL = 1;
        uart->uart_regs->ESCR_f.ESBL = 1;
        break;
    default:
        return -RT_ERROR;
    }

    /* set data bits */
    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        uart->uart_regs->ESCR_f.L0 = 1;
        uart->uart_regs->ESCR_f.L1 = 0;
        uart->uart_regs->ESCR_f.L2 = 0;
        break;
    case DATA_BITS_6:
        uart->uart_regs->ESCR_f.L0 = 0;
        uart->uart_regs->ESCR_f.L1 = 1;
        uart->uart_regs->ESCR_f.L2 = 0;
        break;
    case DATA_BITS_7:
        uart->uart_regs->ESCR_f.L0 = 1;
        uart->uart_regs->ESCR_f.L1 = 1;
        uart->uart_regs->ESCR_f.L2 = 0;
        break;
    case DATA_BITS_8:
        uart->uart_regs->ESCR_f.L0 = 0;
        uart->uart_regs->ESCR_f.L1 = 0;
        uart->uart_regs->ESCR_f.L2 = 0;
        break;
    case DATA_BITS_9:
        uart->uart_regs->ESCR_f.L0 = 0;
        uart->uart_regs->ESCR_f.L1 = 0;
        uart->uart_regs->ESCR_f.L2 = 1;
        break;
    default:
        return -RT_ERROR;
    }

    /* set parity */
    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart->uart_regs->ESCR_f.PEN = 0;
        break;
    case PARITY_EVEN:
        uart->uart_regs->ESCR_f.PEN = 1;
        uart->uart_regs->ESCR_f.P   = 0;
        break;
    case PARITY_ODD:
        uart->uart_regs->ESCR_f.PEN = 1;
        uart->uart_regs->ESCR_f.P   = 1;
        break;
    default:
        return -RT_ERROR;
    }

    /* set bit order */
    switch (cfg->bit_order)
    {
    case BIT_ORDER_LSB:
        uart->uart_regs->SMR_f.BDS = 0;
        break;
    case BIT_ORDER_MSB:
        uart->uart_regs->SMR_f.BDS = 1;
        break;
    default:
        return -RT_ERROR;
    }

    /* set NRZ mode */
    switch (cfg->invert)
    {
    case NRZ_NORMAL:
        uart->uart_regs->ESCR_f.INV = 0;
        break;
    case NRZ_INVERTED:
        uart->uart_regs->ESCR_f.INV = 1;
        break;
    default:
        return -RT_ERROR;
    }

    uart->uart_regs->SCR = SCR_RXE | SCR_TXE | SCR_RIE;

    return RT_EOK;
}

static rt_err_t uart03_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct uart03_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct uart03_device *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        UART_DISABLE_IRQ(uart->rx_irq);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        UART_ENABLE_IRQ(uart->rx_irq);
        break;
    }

    return (RT_EOK);
}

static int uart03_putc(struct rt_serial_device *serial, char c)
{
    struct uart03_device *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct uart03_device *)serial->parent.user_data;
    /* while send buffer is empty */
    while (!(uart->uart_regs->SSR & SSR_TDRE));
    /* write to send buffer */
    uart->uart_regs->TDR = c;

    return (1);
}

static int uart03_getc(struct rt_serial_device *serial)
{
    struct uart03_device *uart;
    int ch;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct uart03_device *)serial->parent.user_data;
    /* receive buffer is full */
    if (uart->uart_regs->SSR & SSR_RDRF)
    {
        ch = uart->uart_regs->RDR & 0xff;
        return (ch);
    }
    else
        return (-1);
}

static struct rt_uart_ops uart03_ops =
{
    uart03_configure,
    uart03_control,
    uart03_putc,
    uart03_getc,
};

static rt_err_t uart47_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct uart47_device *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct uart47_device *)serial->parent.user_data;

    uart->uart_regs->SMR = SMR_MD_UART | SMR_SOE;

    /* set baudreate */
    uart->uart_regs->BGR = (40000000UL + (cfg->baud_rate/2))/cfg->baud_rate - 1;

    /* set stop bits */
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->uart_regs->SMR_f.SBL = 0;
        uart->uart_regs->ESCR_f.ESBL = 0;
        break;
    case STOP_BITS_2:
        uart->uart_regs->SMR_f.SBL = 1;
        uart->uart_regs->ESCR_f.ESBL = 0;
        break;
    case STOP_BITS_3:
        uart->uart_regs->SMR_f.SBL = 0;
        uart->uart_regs->ESCR_f.ESBL = 1;
        break;
    case STOP_BITS_4:
        uart->uart_regs->SMR_f.SBL = 1;
        uart->uart_regs->ESCR_f.ESBL = 1;
        break;
    default:
        return -RT_ERROR;
    }

    /* set data bits */
    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        uart->uart_regs->ESCR_f.L0 = 1;
        uart->uart_regs->ESCR_f.L1 = 0;
        uart->uart_regs->ESCR_f.L2 = 0;
        break;
    case DATA_BITS_6:
        uart->uart_regs->ESCR_f.L0 = 0;
        uart->uart_regs->ESCR_f.L1 = 1;
        uart->uart_regs->ESCR_f.L2 = 0;
        break;
    case DATA_BITS_7:
        uart->uart_regs->ESCR_f.L0 = 1;
        uart->uart_regs->ESCR_f.L1 = 1;
        uart->uart_regs->ESCR_f.L2 = 0;
        break;
    case DATA_BITS_8:
        uart->uart_regs->ESCR_f.L0 = 0;
        uart->uart_regs->ESCR_f.L1 = 0;
        uart->uart_regs->ESCR_f.L2 = 0;
        break;
    case DATA_BITS_9:
        uart->uart_regs->ESCR_f.L0 = 0;
        uart->uart_regs->ESCR_f.L1 = 0;
        uart->uart_regs->ESCR_f.L2 = 1;
        break;
    default:
        return -RT_ERROR;
    }

    /* set parity */
    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart->uart_regs->ESCR_f.PEN = 0;
        break;
    case PARITY_EVEN:
        uart->uart_regs->ESCR_f.PEN = 1;
        uart->uart_regs->ESCR_f.P   = 0;
        break;
    case PARITY_ODD:
        uart->uart_regs->ESCR_f.PEN = 1;
        uart->uart_regs->ESCR_f.P   = 1;
        break;
    default:
        return -RT_ERROR;
    }

    /* set bit order */
    switch (cfg->bit_order)
    {
    case BIT_ORDER_LSB:
        uart->uart_regs->SMR_f.BDS = 0;
        break;
    case BIT_ORDER_MSB:
        uart->uart_regs->SMR_f.BDS = 1;
        break;
    default:
        return -RT_ERROR;
    }

    /* set NRZ mode */
    switch (cfg->invert)
    {
    case NRZ_NORMAL:
        uart->uart_regs->ESCR_f.INV = 0;
        break;
    case NRZ_INVERTED:
        uart->uart_regs->ESCR_f.INV = 1;
        break;
    default:
        return -RT_ERROR;
    }

    /* configure fifo */
    /* Disable the Data Lost detection */
    uart->uart_regs->FCR1_f.FLSTE = 0;
    /* Enable the received FIFO idle detection */
    uart->uart_regs->FCR1_f.FRIE  = 1;
    /* Requests for the transmit FIFO data */
    uart->uart_regs->FCR1_f.FDRQ  = 1;
    /* Disable the transmit FIFO interrupt */
    uart->uart_regs->FCR1_f.FTIE  = 0;
    /* Transmit FIFO:FIFO1; Received FIFO:FIFO2 */
    uart->uart_regs->FCR1_f.FSEL  = 0;

    /* Transfer data count */
    uart->uart_regs->FBYTE1 = 0;
    /* Set the data count to generate a received interrupt */
    uart->uart_regs->FBYTE2 = uart->fifo_size;

    /* FIFO pointer Not reloaded */
    uart->uart_regs->FCR0_f.FLD  = 0;
    /* FIFO pointer Not saved */
    uart->uart_regs->FCR0_f.FSET = 0;
    /* FIFO2 is reset */
    uart->uart_regs->FCR0_f.FCL2 = 1;
    /* FIFO1 is reset */
    uart->uart_regs->FCR0_f.FCL1 = 1;
    /* Enables the FIFO2 operation */
    uart->uart_regs->FCR0_f.FE2  = 1;
    /* Enables the FIFO1 operation */
    uart->uart_regs->FCR0_f.FE1  = 1;

    /* enable receive and send */
    uart->uart_regs->SCR = SCR_RXE | SCR_TXE | SCR_RIE;

    return RT_EOK;
}

static rt_err_t uart47_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct uart47_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct uart47_device *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        UART_DISABLE_IRQ(uart->rx_irq);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        UART_ENABLE_IRQ(uart->rx_irq);
        break;
    }

    return (RT_EOK);
}

static int uart47_putc(struct rt_serial_device *serial, char c)
{
    struct uart47_device *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct uart47_device *)serial->parent.user_data;

    /* while send fifo is empty */
    while (!(uart->uart_regs->SSR & SSR_TDRE));
    /* write to fifo */
    uart->uart_regs->TDR = c;

    return (1);
}

static int uart47_getc(struct rt_serial_device *serial)
{
    int ch;
    struct uart47_device *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct uart47_device *)serial->parent.user_data;

    /* receive is disabled */
    if (!(uart->uart_regs->SCR & SCR_RXE))
        return (-1);
    /* receive fifo is not full */
    if ((uart->uart_regs->SSR & SSR_RDRF) == 0)
        return (-1);
    /* read char */
    ch = uart->uart_regs->RDR & 0xff;

    return (ch);
}

static struct rt_uart_ops uart47_ops =
{
    uart47_configure,
    uart47_control,
    uart47_putc,
    uart47_getc,
};

void rt_hw_serial_init(void)
{
    struct serial_configure config;

    uart_pin_setup();

#if (defined(RT_USING_UART0_0) || defined(RT_USING_UART0_1))
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    serial0.ops    = &uart03_ops;
    serial0.config = config;

    /* register UART0 device */
    rt_hw_serial_register(&serial0, "uart0",
        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
        &uart0);
#endif

#if (defined(RT_USING_UART1_0) || defined(RT_USING_UART1_1))
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    serial1.ops    = &uart03_ops;
    serial1.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&serial1,
        "uart1",
        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
        &uart1);
#endif

#if (defined(RT_USING_UART2_0) || defined(RT_USING_UART2_1) || defined(RT_USING_UART2_2))
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    serial2.ops    = &uart03_ops;
    serial2.config = config;

    /* register UART2 device */
    rt_hw_serial_register(&serial2,
        "uart2",
        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
        &uart2);
#endif

#if (defined(RT_USING_UART3_0) || defined(RT_USING_UART3_1) || defined(RT_USING_UART3_2))
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    serial3.ops    = &uart03_ops;
    serial3.config = config;

    /* register UART3 device */
    rt_hw_serial_register(&serial3,
        "uart3",
        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
        &uart3);
#endif

#if (defined(RT_USING_UART4_0) || defined(RT_USING_UART4_1) || defined(RT_USING_UART4_2))
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    serial4.ops    = &uart47_ops;
    serial4.config = config;

    /* register UART4 device */
    rt_hw_serial_register(&serial4,
        "uart4",
        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
        &uart4);
#endif

#if (defined(RT_USING_UART5_0) || defined(RT_USING_UART5_1) || defined(RT_USING_UART5_2))
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    serial5.ops    = &uart47_ops;
    serial5.config = config;

    /* register UART5 device */
    rt_hw_serial_register(&serial5,
        "uart5",
        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
        &uart5);
#endif

#if (defined(RT_USING_UART6_0) || defined(RT_USING_UART6_1))
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    serial6.ops    = &uart47_ops;
    serial6.config = config;

    /* register UART6 device */
    rt_hw_serial_register(&serial6,
        "uart6",
        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
        &uart6);
#endif

#if (defined(RT_USING_UART7_0) || defined(RT_USING_UART7_1))
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    serial7.ops    = &uart47_ops;
    serial7.config = config;

    /* register UART7 device */
    rt_hw_serial_register(&serial7,
        "uart7",
        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
        &uart7);
#endif
}
