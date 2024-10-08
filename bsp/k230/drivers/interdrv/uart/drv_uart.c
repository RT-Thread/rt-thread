/*
 * Copyright (c) 2019-2020
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <rthw.h>
#include <rtdevice.h>
#include <lwp_user_mm.h>
#include <ioremap.h>

#include "board.h"
#include "drv_uart.h"
#include "riscv_io.h"
#include "board.h"

#define UART_DEFAULT_BAUDRATE       115200
#define UART_CLK                    50000000
#define UART_ADDR 0x91403000UL
#define UART_IRQ 0x13


#define UART_RBR (0x00)       /* receive buffer register */
#define UART_THR (0x00)       /* transmit holding register */
#define UART_DLL (0x00)       /* divisor latch low register */
#define UART_DLH (0x04)       /* diviso latch high register */
#define UART_IER (0x04)       /* interrupt enable register */
#define UART_IIR (0x08)       /* interrupt identity register */
#define UART_FCR (0x08)       /* FIFO control register */
#define UART_LCR (0x0c)       /* line control register */
#define UART_MCR (0x10)       /* modem control register */
#define UART_LSR (0x14)       /* line status register */
#define UART_MSR (0x18)       /* modem status register */
#define UART_SCH (0x1c)       /* scratch register */
#define UART_USR (0x7c)       /* status register */
#define UART_TFL (0x80)       /* transmit FIFO level */
#define UART_RFL (0x84)       /* RFL */
#define UART_HALT (0xa4)      /* halt tx register */
#define UART_DLF (0xc0)       /* Divisor Latch Fraction Register */

#define BIT(x) (1 << x)

/* Line Status Rigster */
#define UART_LSR_RXFIFOE    (BIT(7))
#define UART_LSR_TEMT       (BIT(6))
#define UART_LSR_THRE       (BIT(5))
#define UART_LSR_BI         (BIT(4))
#define UART_LSR_FE         (BIT(3))
#define UART_LSR_PE         (BIT(2))
#define UART_LSR_OE         (BIT(1))
#define UART_LSR_DR         (BIT(0))
#define UART_LSR_BRK_ERROR_BITS 0x1E /* BI, FE, PE, OE bits */

/* Line Control Register */
#define UART_LCR_DLAB       (BIT(7))
#define UART_LCR_SBC        (BIT(6))
#define UART_LCR_PARITY_MASK    (BIT(5)|BIT(4))
#define UART_LCR_EPAR       (1 << 4)
#define UART_LCR_OPAR       (0 << 4)
#define UART_LCR_PARITY     (BIT(3))
#define UART_LCR_STOP       (BIT(2))
#define UART_LCR_DLEN_MASK  (BIT(1)|BIT(0))
#define UART_LCR_WLEN5      (0)
#define UART_LCR_WLEN6      (1)
#define UART_LCR_WLEN7      (2)
#define UART_LCR_WLEN8      (3)

/* Halt Register */
#define UART_HALT_LCRUP     (BIT(2))
#define UART_HALT_FORCECFG  (BIT(1))
#define UART_HALT_HTX       (BIT(0))

/* Interrupt Enable Register */
#define UART_IER_MASK       (0xff)
#define UART_IER_PTIME      (BIT(7))
#define UART_IER_RS485      (BIT(4))
#define UART_IER_MSI        (BIT(3))
#define UART_IER_RLSI       (BIT(2))
#define UART_IER_THRI       (BIT(1))
#define UART_IER_RDI        (BIT(0))

/* Interrupt ID Register */
#define UART_IIR_FEFLAG_MASK    (BIT(6)|BIT(7))
#define UART_IIR_IID_MASK   (BIT(0)|BIT(1)|BIT(2)|BIT(3))
#define UART_IIR_IID_MSTA   (0)
#define UART_IIR_IID_NOIRQ  (1)
#define UART_IIR_IID_THREMP (2)
#define UART_IIR_IID_RXDVAL (4)
#define UART_IIR_IID_LINESTA    (6)
#define UART_IIR_IID_BUSBSY (7)
#define UART_IIR_IID_CHARTO (12)

struct device_uart
{
    rt_ubase_t  hw_base;
    rt_uint32_t irqno;
};

static rt_err_t  rt_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t  uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int       drv_uart_putc(struct rt_serial_device *serial, char c);
static int       drv_uart_getc(struct rt_serial_device *serial);

const struct rt_uart_ops _uart_ops =
{
    rt_uart_configure,
    uart_control,
    drv_uart_putc,
    drv_uart_getc,
    //TODO: add DMA support
    RT_NULL
};

struct rt_serial_device  serial1;
struct device_uart       uart1;

#define write32(addr, val) writel(val, (void*)(addr))
#define read32(addr) readl((void*)(addr))

static void _uart_init(void *uart_base)
{
    uint32_t bdiv;
    uint32_t dlf;
    uint32_t dlh;
    uint32_t dll;

    bdiv = UART_CLK / UART_DEFAULT_BAUDRATE;
    dlh = bdiv >> 12;
    dll = (bdiv - (dlh << 12)) / 16;
    dlf = bdiv - (dlh << 12)  - dll * 16;
    if(dlh == 0 && dll == 0)
    {
        dll = 1;
        dlf = 0;
    }

    write32(uart_base + UART_LCR, 0x00);
    /* Disable all interrupts */
    write32(uart_base + UART_IER, 0x00);
    /* Enable DLAB */
    write32(uart_base + UART_LCR, 0x80);
    if (bdiv) {
        /* Set divisor low byte */
        write32(uart_base + UART_DLL, dll);
        /* Set divisor high byte */
        write32(uart_base + UART_DLH, dlh);
        /* Set divisor fraction byte*/
        write32(uart_base + UART_DLF, dlf);
    }
    /* 8 bits, no parity, one stop bit */
    write32(uart_base + UART_LCR, 0x03);
    /* Enable FIFO */
    write32(uart_base + UART_FCR, 0x01);
    /* No modem control DTR RTS */
    write32(uart_base + UART_MCR, 0x00);
    /* Clear line status */
    read32(uart_base + UART_LSR);
    /* Read receive buffer */
    read32(uart_base + UART_RBR);
    read32(uart_base + UART_USR);
    read32(uart_base + UART_FCR);
    /* Set scratchpad */
    write32(uart_base + UART_SCH, 0x00);
    //enable uart rx irq
    // write32(uart_base + UART_IER, 0x01);
}

static void uart_set_isr(void *uart_base, uint8_t enable, uint32_t irq_type)
{
    uint32_t value;

    value = read32(uart_base + UART_IER);

    if (enable)
    {
        value |= irq_type;
    }
    else
    {
        value &= ~irq_type;
    }
    write32(uart_base + UART_IER, value);
}

/*
 * UART interface
 */
static rt_err_t rt_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    return (RT_EOK);
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct device_uart *uart = (struct device_uart*)serial->parent.user_data;

#ifdef RT_USING_SERIAL_V2
    rt_ubase_t ctrl_flag = 0;
    rt_ubase_t ctrl_arg;
#endif

#ifdef RT_USING_SERIAL_V2
    ctrl_arg = (rt_ubase_t)arg;

    if (ctrl_arg & (RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING))
    {
        ctrl_flag |= RT_DEVICE_FLAG_INT_RX;
    }
#endif

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
#ifdef RT_USING_SERIAL_V2
        if (ctrl_flag & RT_DEVICE_FLAG_INT_RX)
#else
        if ((size_t)arg == RT_DEVICE_FLAG_INT_RX)
#endif
        {
            uart_set_isr((void*)(uart->hw_base), 0, UART_IER_RDI);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
#ifdef RT_USING_SERIAL_V2
        if (ctrl_flag & RT_DEVICE_FLAG_INT_RX)
#else
        if ((size_t)arg == RT_DEVICE_FLAG_INT_RX)
#endif
        {
            uart_set_isr((void*)(uart->hw_base), 1, UART_IER_RDI);
        }
        break;
#ifdef RT_USING_SERIAL_V2
    case RT_DEVICE_CTRL_CONFIG:
        if (ctrl_flag & RT_DEVICE_FLAG_INT_RX)
        {
            uart_set_isr((void*)(uart->hw_base), 1, UART_IER_RDI);
        }
        break;
#endif

    case RT_FIOMMAP2:
    {
        struct dfs_mmap2_args *mmap2 = (struct dfs_mmap2_args *)arg;
        if (mmap2)
        {
            if (mmap2->length > 0x400)
            {
                return -RT_ENOMEM;
            }

            mmap2->ret = lwp_map_user_phy(lwp_self(), RT_NULL, (void*)(uart->hw_base), mmap2->length, 0);
        }
        break;
    }
    }

    return (RT_EOK);
}

static int drv_uart_putc(struct rt_serial_device *serial, char c)
{
    volatile uint32_t *sed_buf;
    volatile uint32_t *sta;
    struct device_uart *uart = (struct device_uart*)serial->parent.user_data;

    sed_buf = (uint32_t *)(uart->hw_base + UART_THR);
    sta = (uint32_t *)(uart->hw_base + UART_USR);

    /* FIFO status, contain valid data */
    // while (!(*sta & 0x02));
    while (!(read32(uart->hw_base + UART_LSR) & 0x20));

    *sed_buf = c;

    return (1);
}

static int drv_uart_getc(struct rt_serial_device *serial)
{
    struct device_uart *uart = (struct device_uart*)serial->parent.user_data;
    volatile uint32_t *lsr = (uint32_t *)(uart->hw_base + UART_LSR);
    volatile uint32_t *rbr = (uint32_t *)(uart->hw_base + UART_RBR);

    if (!(*lsr & UART_LSR_DR))
    {
        return -1;
    }
    return (int)*rbr;
}

static void rt_hw_uart_isr(int irq, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device*)param;
    struct device_uart *uart;
    size_t uart_base;
    uint32_t iir, lsr;

    uart = (struct device_uart*)serial->parent.user_data;
    uart_base = uart->hw_base;

    iir = readb((void*)(uart_base + UART_IIR)) & UART_IIR_IID_MASK;
    lsr = readb((void*)(uart_base + UART_LSR));
    // rt_kprintf("uart isr iir:%x lsr:%x\r\n", iir, lsr);

    if (iir == UART_IIR_IID_BUSBSY)
    {
        (void)readb((void*)(uart_base + UART_USR));
    }
    else if (lsr & (UART_LSR_DR | UART_LSR_BI))
    {
    #ifdef RT_USING_SERIAL_V2
        struct rt_serial_rx_fifo *rx_fifo;
        uint8_t data;

        rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
        RT_ASSERT(rx_fifo != RT_NULL);

        do {
            data = readb((void*)(uart_base + UART_RBR));
            rt_ringbuffer_putchar(&(rx_fifo->rb), data);
            lsr = readb((void*)(uart_base + UART_LSR));
        } while(lsr & UART_LSR_DR);

    #endif

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    else if (iir & UART_IIR_IID_CHARTO)
        /* has charto irq but no dr lsr? just read and ignore */
    {
        readb((void*)(uart_base + UART_RBR));
    }
}

/*
 * UART Initiation
 */
int rt_hw_uart_init(void)
{
    struct rt_serial_device *serial;
    struct device_uart      *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    {
        serial  = &serial1;
        uart    = &uart1;

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = UART_DEFAULT_BAUDRATE;

        uart->hw_base = (rt_base_t)rt_ioremap((void *)UART_ADDR, 0x1000);
        uart->irqno     = UART_IRQ;

        _uart_init((void*)(uart->hw_base));

        rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, serial, "uart1");
        rt_hw_interrupt_umask(uart->irqno);

        rt_hw_serial_register(serial,
                              RT_CONSOLE_DEVICE_NAME,
                              RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }

    return 0;
}
