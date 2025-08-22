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
#include <rtdbg.h>
#include "board.h"
#include "drv_pdma.h"
#include <mmu.h>
#include "drv_uart.h"
#include "riscv_io.h"

typedef enum
{
    TEST_PDMA_EVENT_NONE,
    TEST_PDMA_EVENT_COMPLETE,
    TEST_PDMA_EVENT_TIMEOUT
} test_pdma_event_t;

static rt_event_t uart_pdma_event = RT_NULL;

void uart_pdma_call_back(rt_uint8_t ch, rt_bool_t is_done)
{
    /* Send completion or timeout event based on callback status */
    test_pdma_event_t event_type = is_done ? TEST_PDMA_EVENT_COMPLETE : TEST_PDMA_EVENT_TIMEOUT;
    rt_event_send(uart_pdma_event, event_type);
}

#define UART_DEFAULT_BAUDRATE       115200
#define UART_CLK                    50000000
#define UART0_IRQ                   K230_IRQ_UART0
#define UART1_IRQ                   K230_IRQ_UART1
#define UART2_IRQ                   K230_IRQ_UART2
#define UART3_IRQ                   K230_IRQ_UART3
#define UART4_IRQ                   K230_IRQ_UART4

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
    void*  pa_base;
    rt_uint32_t irqno;

};

static rt_err_t  rt_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t  uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int       drv_uart_putc(struct rt_serial_device *serial, char c);
static int       drv_uart_getc(struct rt_serial_device *serial);
static rt_ssize_t uart_dma_tran(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction);

const struct rt_uart_ops _uart_ops =
{
    .configure    = rt_uart_configure,
    .control      = uart_control,
    .putc         = drv_uart_putc,
    .getc         = drv_uart_getc,
    .dma_transmit = uart_dma_tran
};

struct k230_uart_dev
{
    struct rt_serial_device serial;
    struct device_uart      uart;
    const char *name;
    rt_uint32_t pa_base;
    rt_uint32_t uart_to_size;
    rt_uint32_t irqno;
};

/* 支持的 UART 设备列表 */
static struct k230_uart_dev uart_devs[] =
{
#ifdef BSP_USING_UART0
    {
        .name   = "uart0",
        .pa_base = UART0_BASE_ADDR,
        .uart_to_size = UART0_IO_SIZE,
        .irqno   = UART0_IRQ,
    },
#endif
#ifdef BSP_USING_UART1
    {
        .name   = "uart1",
        .pa_base = UART1_BASE_ADDR,
        .uart_to_size = UART1_IO_SIZE,
        .irqno   = UART1_IRQ,
    },
#endif
#ifdef BSP_USING_UART2
    {
        .name   = "uart2",
        .pa_base = UART2_BASE_ADDR,
        .uart_to_size = UART2_IO_SIZE,
        .irqno   = UART2_IRQ,
    },
#endif
#ifdef BSP_USING_UART3
    {
        .name   = "uart3",
        .pa_base = UART3_BASE_ADDR,
        .uart_to_size = UART3_IO_SIZE,
        .irqno   = UART3_IRQ,
    },
#endif
#ifdef BSP_USING_UART4
    {
        .name   = "uart4",
        .pa_base = UART4_BASE_ADDR,
        .uart_to_size = UART4_IO_SIZE,
        .irqno   = UART4_IRQ,
    },
#endif
#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && !defined(BSP_USING_UART4)
#error "No UART device defined!"
#endif
};

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
    // dlh can be 0 only if bdiv < 4096 (since we're shifting right by 12 bits)
    // bdiv = UART_CLK / UART_DEFAULT_BAUDRATE
    //      = 50000000 / 115200
    //      = 434.027
    // so when dlh is 0,
    // dll = (bdiv - (dlh << 12)) / 16
    //     = (434.027 - 0) / 16
    //     = 27.626
    // which means dll can not reach 0,
    // so we use 1 as the minimum value for dll
    if((dlh == 0) && (dll < 1))
    {
        dll = 1;
        dlf = 0;
    }

    write32(uart_base + UART_LCR, 0x00);
    /* Disable all interrupts */
    write32(uart_base + UART_IER, 0x00);
    /* Enable DLAB */
    write32(uart_base + UART_LCR, 0x80);
    if (bdiv)
    {
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

            mmap2->ret = lwp_map_user_phy(lwp_self(), RT_NULL, uart->pa_base, mmap2->length, 0);
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

static rt_ssize_t uart_dma_write(struct rt_serial_device *serial, const void *buffer, rt_size_t size)
{
    rt_uint8_t ch;
    rt_err_t err;
    rt_uint32_t recv_event;

    struct k230_uart_dev *uart_dev = rt_container_of(serial, struct k230_uart_dev, serial);
    uint32_t len = RT_ALIGN(size, 64);
    uint8_t *buf = rt_malloc_align(len, 64);
    rt_memcpy(buf, buffer, size);
    rt_hw_cpu_dcache_clean((void*)buf, len);
    void *buf_pa = rt_kmem_v2p(buf);
    rt_event_control(uart_pdma_event, RT_IPC_CMD_RESET, NULL);

    /* Configure DMA transfer */
    err = k230_pdma_request_channel(&ch);

    usr_pdma_cfg_t pdma_cfg;
    /* Configure DMA parameters */
    if (!strcmp(uart_dev->name, "uart0"))
    {
        pdma_cfg.device = UART0_TX;
    }
    else if (!strcmp(uart_dev->name, "uart1"))
    {
        pdma_cfg.device = UART1_TX;
    }
    else if (!strcmp(uart_dev->name, "uart2"))
    {
        pdma_cfg.device = UART2_TX;
    }
    else if (!strcmp(uart_dev->name, "uart3"))
    {
        pdma_cfg.device = UART3_TX;
    }
    else if (!strcmp(uart_dev->name, "uart4"))
    {
        pdma_cfg.device = UART4_TX;
    }

    pdma_cfg.src_addr = buf_pa;
    pdma_cfg.dst_addr = (rt_uint8_t *)uart_dev->pa_base;
    pdma_cfg.line_size = len;

    /* Set channel configuration */
    pdma_cfg.pdma_ch_cfg.ch_src_type = CONTINUE;
    pdma_cfg.pdma_ch_cfg.ch_dev_hsize = PSBYTE1;
    pdma_cfg.pdma_ch_cfg.ch_dat_endian = PDEFAULT;
    pdma_cfg.pdma_ch_cfg.ch_dev_blen = PBURST_LEN_16;
    pdma_cfg.pdma_ch_cfg.ch_priority = 7;
    pdma_cfg.pdma_ch_cfg.ch_dev_tout = 0xFFF;

    err = k230_pdma_set_callback(ch, uart_pdma_call_back);
    if(err != RT_EOK)
    {
        LOG_E("pdma_set_callback failed, err=%d\n", err);
    }
    err = k230_pdma_config(ch, &pdma_cfg);
    if(err != RT_EOK)
    {
        LOG_E("pdma_config failed, err=%d\n", err);
    }
    /* Start transfer and wait for completion */
    err = k230_pdma_start(ch);
    if(err != RT_EOK)
    {
        LOG_E("pdma_start failed, err=%d\n", err);
    }
    err = rt_event_recv(uart_pdma_event,
                       TEST_PDMA_EVENT_COMPLETE | TEST_PDMA_EVENT_TIMEOUT,
                       RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                       RT_WAITING_FOREVER,
                       &recv_event);
    /* Cleanup */
    if(err != RT_EOK)
    {
        LOG_E("event_recv failed, err=%d\n", err);
    }
    err = k230_pdma_stop(ch);
    if(err != RT_EOK)
    {
        LOG_E("pdma_stop failed, err=%d\n", err);
    }
    err = k230_pdma_release_channel(ch);
    if(err != RT_EOK)
    {
        LOG_E("pdma_release_channel failed, err=%d\n", err);
    }
    rt_free_align(buf);
    return size;
}

static rt_ssize_t uart_dma_tran(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    rt_ssize_t len;
    if (RT_SERIAL_DMA_TX == direction)
    {
        len = uart_dma_write(serial, (void*)buf, size);
    }
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
    return len;
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
        struct rt_serial_rx_fifo *rx_fifo;
        rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

        if (rx_fifo == NULL)
        {
            readb((void*)(uart_base + UART_RBR));
            return;
        }
    #ifdef RT_USING_SERIAL_V2
        uint8_t data;

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
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t ret;

    uart_pdma_event = (rt_event_t)rt_malloc(sizeof(struct rt_event));
    if (uart_pdma_event == RT_NULL)
    {
        LOG_E("Failed to allocate memory for pdma_event!");
        return -RT_ENOMEM;
    }

    if (rt_event_init(uart_pdma_event, "pdma_event", RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        LOG_E("Failed to init pdma_event!");
        rt_free(uart_pdma_event);
        return -RT_ERROR;
    }

    for (int i = 0; i < sizeof(uart_devs)/sizeof(uart_devs[0]); i++)
    {
        struct k230_uart_dev *dev = &uart_devs[i];

        dev->serial.ops = &_uart_ops;
        dev->serial.config = config;
        dev->serial.config.baud_rate = UART_DEFAULT_BAUDRATE;

        dev->uart.pa_base = (void *)dev->pa_base;
        dev->uart.hw_base = (rt_base_t)rt_ioremap(dev->uart.pa_base, dev->uart_to_size);
        dev->uart.irqno   = dev->irqno;

        _uart_init((void*)(dev->uart.hw_base));

        rt_hw_interrupt_install(dev->uart.irqno, rt_hw_uart_isr, &dev->serial, dev->name);
        rt_hw_interrupt_umask(dev->uart.irqno);

        ret = rt_hw_serial_register(&dev->serial,
                                    dev->name,
                                    RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_TX,
                                    &dev->uart);
        if (ret != RT_EOK)
        {
            LOG_E("Failed to register %s, ret=%d\n", dev->name, ret);
            return ret;
        }
    }
    return RT_EOK;
}