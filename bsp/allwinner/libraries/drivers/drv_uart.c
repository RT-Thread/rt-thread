/*
 * Copyright (c) 2019-2020, Xim
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <rthw.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_uart.h"

#include <stdio.h>

#define DBG_TAG "DRV.UART"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#include <hal_clk.h>
#include <hal_reset.h>
#include <hal_gpio.h>

#define UART_DEFAULT_BAUDRATE 500000

#ifdef UART0_TX_USING_GPIOB8
#define UART0_TX GPIOB(8)
#define UART0_TX_FUNCTION 6
#elif defined(UART0_TX_USING_GPIOE2)
#define UART0_TX GPIOE(2)
#define UART0_TX_FUNCTION 6
#elif defined(UART0_TX_USING_GPIOF2)
#define UART0_TX GPIOF(2)
#define UART0_TX_FUNCTION 3
#endif

#ifdef UART0_RX_USING_GPIOB9
#define UART0_RX GPIOB(9)
#define UART0_RX_FUNCTION 6
#elif defined(UART0_RX_USING_GPIOE3)
#define UART0_RX GPIOE(3)
#define UART0_RX_FUNCTION 6
#elif defined(UART0_RX_USING_GPIOF4)
#define UART0_RX GPIOF(4)
#define UART0_RX_FUNCTION 3
#endif

#ifdef UART1_TX_USING_GPIOD21
#define UART1_TX GPIOD(21)
#define UART1_TX_FUNCTION 4
#elif defined(UART1_TX_USING_GPIOE10)
#define UART1_TX GPIOE(10)
#define UART1_TX_FUNCTION 3
#elif defined(UART1_TX_USING_GPIOG6)
#define UART1_TX GPIOG(6)
#define UART1_TX_FUNCTION 3
#elif defined(UART1_TX_USING_GPIOG12)
#define UART1_TX GPIOG(12)
#define UART1_TX_FUNCTION 7
#endif

#ifdef UART1_RX_USING_GPIOD22
#define UART1_RX GPIOD(22)
#define UART1_RX_FUNCTION 4
#elif defined(UART1_RX_USING_GPIOE11)
#define UART1_RX GPIOE(11)
#define UART1_RX_FUNCTION 3
#elif defined(UART1_RX_USING_GPIOG7)
#define UART1_RX GPIOG(7)
#define UART1_RX_FUNCTION 3
#elif defined(UART1_RX_USING_GPIOG13)
#define UART1_RX GPIOG(13)
#define UART1_RX_FUNCTION 7
#endif

#ifdef UART2_TX_USING_GPIOD1
#define UART2_TX GPIOD(1)
#define UART2_TX_FUNCTION 5
#elif defined(UART2_TX_USING_GPIOE2)
#define UART2_TX GPIOE(2)
#define UART2_TX_FUNCTION 3
#endif

#ifdef UART2_RX_USING_GPIOD2
#define UART2_RX GPIOD(2)
#define UART2_RX_FUNCTION 5
#elif defined(UART2_RX_USING_GPIOE3)
#define UART2_RX GPIOE(3)
#define UART2_RX_FUNCTION 3
#endif

#ifdef UART3_TX_USING_GPIOB6
#define UART3_TX GPIOB(6)
#define UART3_TX_FUNCTION 7
#elif defined(UART3_TX_USING_GPIOC6)
#define UART3_TX GPIOC(6)
#define UART3_TX_FUNCTION 4
#elif defined(UART3_TX_USING_GPIOD10)
#define UART3_TX GPIOD(10)
#define UART3_TX_FUNCTION 5
#elif defined(UART3_TX_USING_GPIOE8)
#define UART3_TX GPIOE(8)
#define UART3_TX_FUNCTION 5
#elif defined(UART3_TX_USING_GPIOG0)
#define UART3_TX GPIOG(0)
#define UART3_TX_FUNCTION 3
#elif defined(UART3_TX_USING_GPIOG8)
#define UART3_TX GPIOG(8)
#define UART3_TX_FUNCTION 5
#endif

#ifdef UART3_RX_USING_GPIOB7
#define UART3_RX GPIOB(7)
#define UART3_RX_FUNCTION 7
#elif defined(UART3_RX_USING_GPIOC7)
#define UART3_RX GPIOC(7)
#define UART3_RX_FUNCTION 4
#elif defined(UART3_RX_USING_GPIOD11)
#define UART3_RX GPIOD(11)
#define UART3_RX_FUNCTION 5
#elif defined(UART3_RX_USING_GPIOE9)
#define UART3_RX GPIOE(9)
#define UART3_RX_FUNCTION 5
#elif defined(UART3_RX_USING_GPIOG1)
#define UART3_RX GPIOG(1)
#define UART3_RX_FUNCTION 3
#elif defined(UART3_RX_USING_GPIOG9)
#define UART3_RX GPIOG(9)
#define UART3_RX_FUNCTION 5
#endif

#ifdef UART4_TX_USING_GPIOB2
#define UART4_TX GPIOB(2)
#define UART4_TX_FUNCTION 7
#elif defined(UART4_TX_USING_GPIOD7)
#define UART4_TX GPIOD(7)
#define UART4_TX_FUNCTION 5
#elif defined(UART4_TX_USING_GPIOE4)
#define UART4_TX GPIOE(4)
#define UART4_TX_FUNCTION 3
#elif defined(UART4_TX_USING_GPIOG2)
#define UART4_TX GPIOG(2)
#define UART4_TX_FUNCTION 5
#endif

#ifdef UART4_RX_USING_GPIOB3
#define UART4_RX GPIOB(3)
#define UART4_RX_FUNCTION 7
#elif defined(UART4_RX_USING_GPIOD8)
#define UART4_RX GPIOD(8)
#define UART4_RX_FUNCTION 5
#elif defined(UART4_RX_USING_GPIOE5)
#define UART4_RX GPIOE(5)
#define UART4_RX_FUNCTION 3
#elif defined(UART4_TX_USING_GPIOG3)
#define UART4_RX GPIOG(3)
#define UART4_RX_FUNCTION 5
#endif

#ifdef UART5_TX_USING_GPIOB4
#define UART5_TX GPIOB(4)
#define UART5_TX_FUNCTION 7
#elif defined(UART5_TX_USING_GPIOD5)
#define UART5_TX GPIOD(5)
#define UART5_TX_FUNCTION 5
#elif defined(UART5_TX_USING_GPIOE6)
#define UART5_TX GPIOE(6)
#define UART5_TX_FUNCTION 3
#elif defined(UART5_TX_USING_GPIOG4)
#define UART5_TX GPIOG(4)
#define UART5_TX_FUNCTION 3
#endif

#ifdef UART5_RX_USING_GPIOB5
#define UART5_RX GPIOB(5)
#define UART5_RX_FUNCTION 7
#elif defined(UART5_RX_USING_GPIOD6)
#define UART5_RX GPIOD(6)
#define UART5_RX_FUNCTION 5
#elif defined(UART5_RX_USING_GPIOE7)
#define UART5_RX GPIOE(7)
#define UART5_RX_FUNCTION 3
#elif defined(UART5_RX_USING_GPIOG5)
#define UART5_RX GPIOG(5)
#define UART5_RX_FUNCTION 3
#endif

#define SUNXI_CLK_UART0 CLK_BUS_UART0;
#define SUNXI_RST_UART0 RST_BUS_UART0;

#define SUNXI_CLK_UART1 CLK_BUS_UART1;
#define SUNXI_RST_UART1 RST_BUS_UART1;

#define SUNXI_CLK_UART2 CLK_BUS_UART2;
#define SUNXI_RST_UART2 RST_BUS_UART2;

#define SUNXI_CLK_UART3 CLK_BUS_UART3;
#define SUNXI_RST_UART3 RST_BUS_UART3;

#define SUNXI_CLK_UART4 CLK_BUS_UART4;
#define SUNXI_RST_UART4 RST_BUS_UART4;

#define SUNXI_CLK_UART5 CLK_BUS_UART5;
#define SUNXI_RST_UART5 RST_BUS_UART5;

#define SUNXI_IRQ_UART0 (18)
#define SUNXI_IRQ_UART1 (19)
#define SUNXI_IRQ_UART2 (20)
#define SUNXI_IRQ_UART3 (21)
#define SUNXI_IRQ_UART4 (22)
#define SUNXI_IRQ_UART5 (23)

#define SUNXI_UART0_BASE (0x02500000)
#define SUNXI_UART1_BASE (0x02500400)
#define SUNXI_UART2_BASE (0x02500800)
#define SUNXI_UART3_BASE (0x02500c00)
#define SUNXI_UART4_BASE (0x02501000)
#define SUNXI_UART5_BASE (0x02501400)

/*
 * Register definitions for UART
 */
#define UART_RHB (0x00)
#define UART_RBR (0x00)   /* receive buffer register */
#define UART_THR (0x00)   /* transmit holding register */
#define UART_DLL (0x00)   /* divisor latch low register */
#define UART_DLH (0x04)   /* diviso latch high register */
#define UART_IER (0x04)   /* interrupt enable register */
#define UART_IIR (0x08)   /* interrupt identity register */
#define UART_FCR (0x08)   /* FIFO control register */
#define UART_LCR (0x0c)   /* line control register */
#define UART_MCR (0x10)   /* modem control register */
#define UART_LSR (0x14)   /* line status register */
#define UART_MSR (0x18)   /* modem status register */
#define UART_SCH (0x1c)   /* scratch register */
#define UART_USR (0x7c)   /* status register */
#define UART_TFL (0x80)   /* transmit FIFO level */
#define UART_RFL (0x84)   /* RFL */
#define UART_HALT (0xa4)  /* halt tx register */
#define UART_RS485 (0xc0) /* RS485 control and status register */

/*
 * register bit field define
 */

/* Interrupt Enable Register */
#define UART_IER_MASK (0xff)
#define UART_IER_PTIME (BIT(7))
#define UART_IER_RS485 (BIT(4))
#define UART_IER_MSI (BIT(3))
#define UART_IER_RLSI (BIT(2))
#define UART_IER_THRI (BIT(1))
#define UART_IER_RDI (BIT(0))
/* Interrupt ID Register */
#define UART_IIR_FEFLAG_MASK (BIT(6) | BIT(7))
#define UART_IIR_IID_MASK (BIT(0) | BIT(1) | BIT(2) | BIT(3))
#define UART_IIR_IID_MSTA (0)
#define UART_IIR_IID_NOIRQ (1)
#define UART_IIR_IID_THREMP (2)
#define UART_IIR_IID_RXDVAL (4)
#define UART_IIR_IID_LINESTA (6)
#define UART_IIR_IID_BUSBSY (7)
#define UART_IIR_IID_CHARTO (12)
/* FIFO Control Register */
#define UART_FCR_RXTRG_MASK (BIT(6) | BIT(7))
#define UART_FCR_RXTRG_1CH (0 << 6)
#define UART_FCR_RXTRG_1_4 (1 << 6)
#define UART_FCR_RXTRG_1_2 (2 << 6)
#define UART_FCR_RXTRG_FULL (3 << 6)
#define UART_FCR_TXTRG_MASK (BIT(4) | BIT(5))
#define UART_FCR_TXTRG_EMP (0 << 4)
#define UART_FCR_TXTRG_2CH (1 << 4)
#define UART_FCR_TXTRG_1_4 (2 << 4)
#define UART_FCR_TXTRG_1_2 (3 << 4)
#define UART_FCR_TXFIFO_RST (BIT(2))
#define UART_FCR_RXFIFO_RST (BIT(1))
#define UART_FCR_FIFO_EN (BIT(0))
/* Line Control Register */
#define UART_LCR_DLAB (BIT(7))
#define UART_LCR_SBC (BIT(6))
#define UART_LCR_PARITY_MASK (BIT(5) | BIT(4))
#define UART_LCR_EPAR (1 << 4)
#define UART_LCR_OPAR (0 << 4)
#define UART_LCR_PARITY (BIT(3))
#define UART_LCR_STOP (BIT(2))
#define UART_LCR_DLEN_MASK (BIT(1) | BIT(0))
#define UART_LCR_WLEN5 (0)
#define UART_LCR_WLEN6 (1)
#define UART_LCR_WLEN7 (2)
#define UART_LCR_WLEN8 (3)
/* Modem Control Register */
#define UART_MCR_MODE_MASK (BIT(7) | BIT(6))
#define UART_MCR_MODE_RS485 (2 << 6)
#define UART_MCR_MODE_SIRE (1 << 6)
#define UART_MCR_MODE_UART (0 << 6)
#define UART_MCR_AFE (BIT(5))
#define UART_MCR_LOOP (BIT(4))
#define UART_MCR_RTS (BIT(1))
#define UART_MCR_DTR (BIT(0))
/* Line Status Rigster */
#define UART_LSR_RXFIFOE (BIT(7))
#define UART_LSR_TEMT (BIT(6))
#define UART_LSR_THRE (BIT(5))
#define UART_LSR_BI (BIT(4))
#define UART_LSR_FE (BIT(3))
#define UART_LSR_PE (BIT(2))
#define UART_LSR_OE (BIT(1))
#define UART_LSR_DR (BIT(0))
#define UART_LSR_BRK_ERROR_BITS (0x1E) /* BI, FE, PE, OE bits */
/* Modem Status Register */
#define UART_MSR_DCD (BIT(7))
#define UART_MSR_RI (BIT(6))
#define UART_MSR_DSR (BIT(5))
#define UART_MSR_CTS (BIT(4))
#define UART_MSR_DDCD (BIT(3))
#define UART_MSR_TERI (BIT(2))
#define UART_MSR_DDSR (BIT(1))
#define UART_MSR_DCTS (BIT(0))
#define UART_MSR_ANY_DELTA (0x0F)
#define MSR_SAVE_FLAGS (UART_MSR_ANY_DELTA)
/* Status Register */
#define UART_USR_RFF (BIT(4))
#define UART_USR_RFNE (BIT(3))
#define UART_USR_TFE (BIT(2))
#define UART_USR_TFNF (BIT(1))
#define UART_USR_BUSY (BIT(0))
/* Halt Register */
#define UART_HALT_LCRUP (BIT(2))
#define UART_HALT_FORCECFG (BIT(1))
#define UART_HALT_HTX (BIT(0))
/* RS485 Control and Status Register */
#define UART_RS485_RXBFA (BIT(3))
#define UART_RS485_RXAFA (BIT(2))

typedef enum
{
    UART_0 = 0,
    UART_1,
    UART_2,
    UART_3,
    UART_4,
    UART_5,
    UART_MAX,
} uart_port_t;

/* This enum defines word length of the UART frame. */
typedef enum
{
    UART_WORD_LENGTH_5 = 0,
    UART_WORD_LENGTH_6,
    UART_WORD_LENGTH_7,
    UART_WORD_LENGTH_8,
} uart_word_length_t;

/* This enum defines stop bit of the UART frame. */
typedef enum
{
    UART_STOP_BIT_1 = 0,
    UART_STOP_BIT_2,
} uart_stop_bit_t;

/* This enum defines parity of the UART frame. */
typedef enum
{
    UART_PARITY_NONE = 0,
    UART_PARITY_ODD,
    UART_PARITY_EVEN
} uart_parity_t;

struct sunxi_uart
{
    uart_port_t uart_port;
    uint32_t irqno;

    rt_uint16_t uart_dma_flag;
    struct rt_completion tx_fifo_empty;
};

static const size_t _uart_base[] =
    {
        SUNXI_UART0_BASE, SUNXI_UART1_BASE, SUNXI_UART2_BASE, SUNXI_UART3_BASE, SUNXI_UART4_BASE, SUNXI_UART5_BASE};

static const uint32_t _uart_irqn[] =
    {
        SUNXI_IRQ_UART0, SUNXI_IRQ_UART1, SUNXI_IRQ_UART2, SUNXI_IRQ_UART3, SUNXI_IRQ_UART4, SUNXI_IRQ_UART5};

static rt_err_t _uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t _uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int _uart_putc(struct rt_serial_device *serial, char c);
static int _uart_getc(struct rt_serial_device *serial);
static rt_ssize_t _uart_transmit(struct rt_serial_device *serial,
                                rt_uint8_t *buf, rt_size_t size, rt_uint32_t tx_flag);

const struct rt_uart_ops _uart_ops =
    {
        _uart_configure,
        _uart_control,
        _uart_putc,
        _uart_getc,
        _uart_transmit};

#ifdef BSP_USING_UART0
struct rt_serial_device serial0;
struct sunxi_uart uart0 = {
    .uart_port = UART_0,
    .irqno = SUNXI_IRQ_UART0};
#endif

#ifdef BSP_USING_UART1
struct rt_serial_device serial1;
struct sunxi_uart uart1 = {
    .uart_port = UART_1,
    .irqno = SUNXI_IRQ_UART1};
#endif

#ifdef BSP_USING_UART2
struct rt_serial_device serial2;
struct sunxi_uart uart2 = {
    .uart_port = UART_2,
    .irqno = SUNXI_IRQ_UART2};
#endif

#ifdef BSP_USING_UART3
struct rt_serial_device serial3;
struct sunxi_uart uart3 = {
    .uart_port = UART_3,
    .irqno = SUNXI_IRQ_UART3};
#endif

#ifdef BSP_USING_UART4
struct rt_serial_device serial4;
struct sunxi_uart uart4 = {
    .uart_port = UART_4,
    .irqno = SUNXI_IRQ_UART4};
#endif

#ifdef BSP_USING_UART5
struct rt_serial_device serial5;
struct sunxi_uart uart5 = {
    .uart_port = UART_5,
    .irqno = SUNXI_IRQ_UART5};
#endif

static void uart_set_baudrate(uart_port_t uart_port, uint32_t baudrate)
{
    size_t uart_base;
    uint32_t quot, uart_clk;
    uint8_t lcr;

    uart_base = SUNXI_UART0_BASE + uart_port * 0x400;
    uart_clk = 24000000; /* FIXME: fixed to 24MHz */

    quot = (uart_clk + 8 * baudrate) / (16 * baudrate);

    lcr = hal_readb(uart_base + UART_LCR);

    /* hold tx so that uart will update lcr and baud in the gap of tx */
    hal_writeb(UART_HALT_HTX | UART_HALT_FORCECFG, uart_base + UART_HALT);
    hal_writeb(lcr | UART_LCR_DLAB, uart_base + UART_LCR);
    hal_writeb(quot >> 8, uart_base + UART_DLH);
    hal_writeb(quot & 0xFFu, uart_base + UART_DLL);
    hal_writeb(UART_HALT_HTX | UART_HALT_FORCECFG | UART_HALT_LCRUP, uart_base + UART_HALT);
    /* FIXME: implement timeout */
    while (hal_readb(uart_base + UART_HALT) & UART_HALT_LCRUP)
        ;

    /* In fact there are two DLABs(DLAB and DLAB_BAK) in the hardware implementation.
     * The DLAB_BAK is sellected only when SW_UART_HALT_FORCECFG is set to 1,
     * and this bit can be access no matter uart is busy or not.
     * So we select the DLAB_BAK always by leaving SW_UART_HALT_FORCECFG to be 1. */
    hal_writeb(lcr, uart_base + UART_LCR);
    hal_writeb(UART_HALT_FORCECFG, uart_base + UART_HALT);
}

static void uart_set_format(uart_port_t uart_port, uint8_t data_bits, uint8_t stop_bits, uint8_t parity)
{
    size_t uart_base;
    uint8_t lcr;

    uart_base = SUNXI_UART0_BASE + uart_port * 0x400;

    lcr = hal_readb(uart_base + UART_LCR);

    /* set word length */
    lcr &= ~(UART_LCR_DLEN_MASK);
    switch (data_bits)
    {
    case 5:
        lcr |= UART_LCR_WLEN5;
        break;
    case 6:
        lcr |= UART_LCR_WLEN6;
        break;
    case 7:
        lcr |= UART_LCR_WLEN7;
        break;
    case 8:
    default:
        lcr |= UART_LCR_WLEN8;
        break;
    }

    /* set stop bit */
    switch (stop_bits)
    {
    case 1:
    default:
        lcr &= ~(UART_LCR_STOP);
        break;
    case 2:
        lcr |= UART_LCR_STOP;
        break;
    }

    /* set parity bit */
    lcr &= ~(UART_LCR_PARITY_MASK);
    switch (parity)
    {
    case PARITY_NONE:
        lcr &= ~(UART_LCR_PARITY);
        break;
    case PARITY_ODD:
        lcr |= UART_LCR_PARITY;
        break;
    case PARITY_EVEN:
        lcr |= UART_LCR_PARITY;
        lcr |= UART_LCR_EPAR;
        break;
    }

    hal_writeb(lcr, uart_base + UART_LCR);
}

static void uart_set_fifo(uart_port_t uart_port)
{
    size_t uart_base;
    uint8_t fcr;

    uart_base = SUNXI_UART0_BASE + uart_port * 0x400;

    fcr = UART_FCR_RXTRG_1_2 | UART_FCR_TXTRG_EMP | UART_FCR_FIFO_EN;

    hal_writeb(fcr, uart_base + UART_FCR);
}

static void uart_forcechange(uart_port_t uart_port)
{
    size_t uart_base;
    uint32_t value;

    uart_base = SUNXI_UART0_BASE + uart_port * 0x400;

    value = hal_readb(uart_base + UART_HALT);
    value |= UART_HALT_FORCECFG;
    hal_writeb(value, uart_base + UART_HALT);
}

static void uart_set_isr(uart_port_t uart_port, uint8_t enable, uint32_t irq_type)
{
    size_t uart_base;
    uint32_t value;

    uart_base = SUNXI_UART0_BASE + uart_port * 0x400;

    value = hal_readb(uart_base + UART_IER);

    if (enable)
    {
        value |= irq_type;
    }
    else
    {
        value &= ~irq_type;
    }
    hal_writeb(value, uart_base + UART_IER);
}

/*
 * UART interface
 */
static rt_err_t _uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct sunxi_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    serial->config = *cfg;
    uart = serial->parent.user_data;

    uart_set_format(uart->uart_port, cfg->data_bits, cfg->stop_bits, cfg->parity);
    uart_set_baudrate(uart->uart_port, cfg->baud_rate);
    uart_set_fifo(uart->uart_port);
    uart_forcechange(uart->uart_port);

    return RT_EOK;
}

static rt_err_t _uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct sunxi_uart *uart;
    rt_uint32_t channel = 1;
#ifdef RT_USING_SERIAL_V2
    rt_ubase_t ctrl_flag = 0;
    rt_ubase_t ctrl_arg;
#endif

    uart = serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);
    RT_ASSERT(channel != 3);

#ifdef RT_USING_SERIAL_V2
    ctrl_arg = (rt_ubase_t)arg;

    if (ctrl_arg & (RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING))
    {
        ctrl_flag |= RT_DEVICE_FLAG_INT_RX;
    }
    else if (ctrl_arg & (RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING))
    {
        if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
        {
            ctrl_flag = RT_DEVICE_FLAG_DMA_TX;
        }
        else
        {
            ctrl_flag = RT_DEVICE_FLAG_INT_TX;
        }
    }
#endif

    LOG_D("uart%d control cmd:%x, arg:%x\n", uart->uart_port, cmd, ctrl_arg);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
#ifdef RT_USING_SERIAL_V2
        if (ctrl_flag & RT_DEVICE_FLAG_INT_RX)
#else
        if ((size_t)arg == RT_DEVICE_FLAG_INT_RX)
#endif
        {
            uart_set_isr(uart->uart_port, 0, UART_IER_RDI | UART_IER_RLSI);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
#ifdef RT_USING_SERIAL_V2
        if (ctrl_flag & RT_DEVICE_FLAG_INT_RX)
#else
        if ((size_t)arg == RT_DEVICE_FLAG_INT_RX)
#endif
        {
            uart_set_isr(uart->uart_port, 1, UART_IER_RDI | UART_IER_RLSI);
        }
        break;
#ifdef RT_USING_SERIAL_V2
    case RT_DEVICE_CTRL_CONFIG:
        if (ctrl_flag & RT_DEVICE_FLAG_INT_RX)
        {
            uart_set_isr(uart->uart_port, 1, UART_IER_RDI | UART_IER_RLSI);
        }
        break;

    case RT_DEVICE_CHECK_OPTMODE:
        if (ctrl_flag & RT_DEVICE_FLAG_DMA_TX)
        {
            return RT_SERIAL_TX_BLOCKING_NO_BUFFER;
        }
        else
        {
            return RT_SERIAL_TX_BLOCKING_BUFFER;
        }
#endif /* RT_USING_SERIAL_V2 */
    }

    return (RT_EOK);
}

static int _uart_putc(struct rt_serial_device *serial, char c)
{
    struct sunxi_uart *uart;
    size_t uart_base;

    uart = serial->parent.user_data;

    uart_base = SUNXI_UART0_BASE + uart->uart_port * 0x400;

    /* FIFO status, contain valid data */
    while (!(hal_readl(uart_base + UART_USR) & UART_USR_TFNF))
        ;

    hal_writeb(c, uart_base + UART_THR);

    // wait TX FIFO and the TX shift Register are empty.
    while (!(hal_readl(uart_base + UART_LSR) & UART_LSR_TEMT))
        ;

    return 1;
}

static int _uart_getc(struct rt_serial_device *serial)
{
    struct sunxi_uart *uart;
    size_t uart_base;
    int data = -1;

    uart = serial->parent.user_data;
    uart_base = SUNXI_UART0_BASE + uart->uart_port * 0x400;

    while (!(hal_readl(uart_base + UART_RFL) & 0x1FFu))
        ;

    /* Receive Data Available */
    if (hal_readl(uart_base + UART_USR) & UART_USR_RFNE)
    {
        data = hal_readb(uart_base + UART_RBR);
    }

    return data;
}

static rt_ssize_t _uart_transmit(struct rt_serial_device *serial,
                                rt_uint8_t *buf, rt_size_t size, rt_uint32_t tx_flag)
{
    struct sunxi_uart *uart;
    size_t uart_base;

    uart = serial->parent.user_data;
    uart_base = SUNXI_UART0_BASE + uart->uart_port * 0x400;

    if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        uint32_t remain = size;

        while (remain)
        {
            uint32_t write_count = 0;

            while (remain && (hal_readl(uart_base + UART_USR) & UART_USR_TFNF))
            {
                rt_uint8_t c = *buf++;
                hal_writeb(c, uart_base + UART_THR);
                remain--;
                write_count++;
            }

            while (write_count)
            {
                if (hal_readl(uart_base + UART_LSR) & UART_LSR_TEMT)
                {
                    break;
                }

                rt_completion_init(&(uart->tx_fifo_empty));
                uart_set_isr(uart->uart_port, 1, UART_IER_THRI);

                rt_err_t result = rt_completion_wait(&(uart->tx_fifo_empty), 100); // TODO: timeout calc by baud-rate.
                if (result == RT_EOK)
                {
                    break;
                }
            }
        }

        /* last byte, must wait TEMT(transmitter Empty). TODO: need delay? */
        while (1)
        {
            if (hal_readl(uart_base + UART_LSR) & UART_LSR_TEMT)
            {
                break;
            }
        }

        {
            struct rt_serial_tx_fifo *tx_fifo = RT_NULL;
            tx_fifo = (struct rt_serial_tx_fifo *)serial->serial_tx;
            tx_fifo->activated = RT_FALSE;
            rt_completion_done(&(tx_fifo->tx_cpt));
        }

        return size;
    }

    return 0;
}

/**
 * this function will called when uart interrupt occur!
 */
static void uart_irq_handler(int vector, void *param)
{
    size_t uart_base;
    uint32_t iir, lsr;
    struct rt_serial_device *serial;
    struct sunxi_uart *uart;

    LOG_D("serial3:%p, uart3:%p\n", &serial3, &uart3);
    serial = (struct rt_serial_device *)param;
    uart = (struct sunxi_uart *)serial->parent.user_data;

    LOG_D("isr serial:%p, uart:%p, name:%s\n", serial, uart, serial->parent.parent.name);

    uart_base = SUNXI_UART0_BASE + uart->uart_port * 0x400;
    iir = hal_readb(uart_base + UART_IIR) & UART_IIR_IID_MASK;
    lsr = hal_readb(uart_base + UART_LSR);

    LOG_D("IRQ uart%d lsr is %08x \n", uart->uart_port, lsr);
    if (iir == UART_IIR_IID_BUSBSY)
    {
        (void)hal_readb(uart_base + UART_USR);

        /*
         * Before reseting lcr, we should ensure than uart is not in busy
         * state. Otherwise, a new busy interrupt will be introduced.
         * It is wise to set uart into loopback mode, since it can cut down the
         * serial in, then we should reset fifo(in my test, busy state
         * (UART_USR_BUSY) can't be cleard until the fifo is empty).
         */
        hal_writeb(hal_readb(uart_base + UART_MCR) | UART_MCR_LOOP, uart_base + UART_MCR);

        hal_writeb(UART_FCR_FIFO_EN, uart_base + UART_FCR);
        hal_writeb(UART_FCR_TXFIFO_RST | UART_FCR_RXFIFO_RST | UART_FCR_FIFO_EN, uart_base + UART_FCR);
        hal_writeb(0, uart_base + UART_FCR);

        uart_set_fifo(uart->uart_port);
        (void)hal_readb(uart_base + UART_FCR);

        hal_writeb(hal_readb(uart_base + UART_MCR) & ~UART_MCR_LOOP, uart_base + UART_MCR); /* exit loopback mode. */
    }
    else
    {
        if (lsr & (UART_LSR_DR | UART_LSR_BI))
        {
#ifdef RT_USING_SERIAL_V2
            struct rt_serial_rx_fifo *rx_fifo;
            uint8_t data;

            rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
            RT_ASSERT(rx_fifo != RT_NULL);

            do
            {
                data = hal_readb(uart_base + UART_RBR);
                rt_ringbuffer_putchar(&(rx_fifo->rb), data);
                lsr = hal_readb(uart_base + UART_LSR);
            } while (lsr & UART_LSR_DR);

#endif

            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        }
        else if (iir & UART_IIR_IID_CHARTO)
        /* has charto irq but no dr lsr? just read and ignore */
        {
            hal_readb(uart_base + UART_RBR);
        }

        /* if (lsr & UART_LSR_THRE)
        {
            uart_handle_tx(uart_port);
        }*/
    }

    if (iir == UART_IIR_IID_THREMP)
    {
        uart_set_isr(uart->uart_port, 0, UART_IER_THRI);
        rt_completion_done(&(uart->tx_fifo_empty));
    }
}

static int uart_clk_init(int bus, uint8_t enable)
{
    hal_clk_status_t ret;
    hal_reset_type_t reset_type = HAL_SUNXI_RESET;
    u32 reset_id;
    hal_clk_type_t clk_type = HAL_SUNXI_CCU;
    hal_clk_id_t clk_id;
    hal_clk_t clk;
    struct reset_control *reset;

    switch (bus)
    {
    case 0:
        clk_id = SUNXI_CLK_UART0;
        reset_id = SUNXI_RST_UART0;
        break;
    case 1:
        clk_id = SUNXI_CLK_UART1;
        reset_id = SUNXI_RST_UART1;
        break;
    case 2:
        clk_id = SUNXI_CLK_UART2;
        reset_id = SUNXI_RST_UART2;
        break;
    case 3:
        clk_id = SUNXI_CLK_UART3;
        reset_id = SUNXI_RST_UART3;
        break;
    case 4:
        clk_id = SUNXI_CLK_UART4;
        reset_id = SUNXI_RST_UART4;
        break;
    case 5:
        clk_id = SUNXI_CLK_UART5;
        reset_id = SUNXI_RST_UART5;
        break;
    default:
        LOG_E("uart%d is invalid\n", bus);
        return -1;
    }

    if (enable)
    {
        reset = hal_reset_control_get(reset_type, reset_id);
        hal_reset_control_deassert(reset);
        hal_reset_control_put(reset);

        clk = hal_clock_get(clk_type, clk_id);
        ret = hal_clock_enable(clk);
        if (ret)
        {
            LOG_E("[uart%d] couldn't enable clk!\n", bus);
            return -1;
        }
    }
    else
    {
        clk = hal_clock_get(clk_type, clk_id);
        ret = hal_clock_disable(clk);
        if (ret)
        {
            LOG_E("[uart%d] couldn't disable clk!\n", bus);
            return -1;
        }
    }

    return 0;
}

static void uart_pinctrl_init(uart_port_t uart_port)
{
    switch (uart_port)
    {
#ifdef BSP_USING_UART0
    case UART_0:
        hal_gpio_set_pull(UART0_RX, GPIO_PULL_UP);
        hal_gpio_pinmux_set_function(UART0_TX, UART0_TX_FUNCTION); // TX
        hal_gpio_pinmux_set_function(UART0_RX, UART0_RX_FUNCTION); // RX
        break;
#endif
#ifdef BSP_USING_UART1
    case UART_1:
        hal_gpio_set_pull(UART1_RX, GPIO_PULL_UP);
        hal_gpio_pinmux_set_function(UART1_TX, UART1_TX_FUNCTION); // TX
        hal_gpio_pinmux_set_function(UART1_RX, UART1_RX_FUNCTION); // RX
        break;
#endif
#ifdef BSP_USING_UART2
    case UART_2:
        hal_gpio_set_pull(UART2_RX, GPIO_PULL_UP);
        hal_gpio_pinmux_set_function(UART2_TX, UART2_TX_FUNCTION); // TX
        hal_gpio_pinmux_set_function(UART2_RX, UART2_RX_FUNCTION); // RX
        break;
#endif
#ifdef BSP_USING_UART3
    case UART_3:
        hal_gpio_set_pull(UART3_RX, GPIO_PULL_UP);
        hal_gpio_pinmux_set_function(UART3_TX, UART3_TX_FUNCTION); // TX
        hal_gpio_pinmux_set_function(UART3_RX, UART3_RX_FUNCTION); // RX
        break;
#endif
#ifdef BSP_USING_UART4
    case UART_4:
        hal_gpio_set_pull(UART4_RX, GPIO_PULL_UP);
        hal_gpio_pinmux_set_function(UART4_TX, UART4_TX_FUNCTION); // TX
        hal_gpio_pinmux_set_function(UART4_RX, UART4_RX_FUNCTION); // RX
        break;
#endif
#ifdef BSP_USING_UART5
    case UART_5:
        hal_gpio_set_pull(UART5_RX, GPIO_PULL_UP);
        hal_gpio_pinmux_set_function(UART5_TX, UART5_TX_FUNCTION); // TX
        hal_gpio_pinmux_set_function(UART5_RX, UART5_RX_FUNCTION); // RX
        break;
#endif
    default:
        LOG_E("[uart%d] not support \n", uart_port);
        break;
    }
}

static int uart_init(const char *name, struct sunxi_uart *uart, struct rt_serial_device *serial)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    uart_clk_init(uart->uart_port, 1);
    uart_pinctrl_init(uart->uart_port);

    serial->ops = &_uart_ops;
    serial->config = config;
    serial->config.rx_bufsz = 256;
    serial->config.tx_bufsz = 0;
    serial->config.baud_rate = UART_DEFAULT_BAUDRATE;

    if (strcmp(name, RT_CONSOLE_DEVICE_NAME) == 0)
    {
        uart->uart_dma_flag = 0;
        rt_hw_serial_register(serial, name, RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
    }
    else
    {
        uart->uart_dma_flag = RT_DEVICE_FLAG_DMA_TX;
        rt_hw_serial_register(serial, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
    }

    rt_hw_interrupt_install(uart->irqno, uart_irq_handler, serial, name);
    rt_hw_interrupt_umask(uart->irqno);

    return 0;
}

/*
 * UART Initiation
 */
int rt_hw_uart_init(void)
{
#ifdef BSP_USING_UART0
    uart_init("uart0", &uart0, &serial0);
#endif

#ifdef BSP_USING_UART1
    uart_init("uart1", &uart1, &serial1);
#endif

#ifdef BSP_USING_UART2
    uart_init("uart2", &uart2, &serial2);
#endif

#ifdef BSP_USING_UART3
    uart_init("uart3", &uart3, &serial3);
#endif

#ifdef BSP_USING_UART4
    uart_init("uart4", &uart4, &serial4);
#endif

#ifdef BSP_USING_UART5
    uart_init("uart5", &uart5, &serial5);
#endif

    return 0;
}
