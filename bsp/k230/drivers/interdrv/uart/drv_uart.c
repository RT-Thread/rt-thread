/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

#define UART_DEFAULT_BAUDRATE       115200
#define UART_CLK                    50000000
#define PDMA_CH_INVALID             0xFF
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

#ifdef BSP_UART_USING_DMA
typedef enum
{
    K230_UART_PDMA_EVENT_NONE,
    K230_UART_PDMA_EVENT_COMPLETE,
    K230_UART_PDMA_EVENT_TIMEOUT
} uart_pdma_event_t;
#endif

struct device_uart
{
    rt_ubase_t  hw_base;
    void*  pa_base;
    rt_uint32_t irqno;
};

static rt_err_t  _rt_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t  _uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int       _drv_uart_putc(struct rt_serial_device *serial, char c);
static int       _drv_uart_getc(struct rt_serial_device *serial);
#ifdef BSP_UART_USING_DMA
static rt_ssize_t _uart_dma_tran(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction);
#endif

const struct rt_uart_ops _uart_ops =
{
    .configure    = _rt_uart_configure,
    .control      = _uart_control,
    .putc         = _drv_uart_putc,
    .getc         = _drv_uart_getc,
#ifdef BSP_UART_USING_DMA
    .dma_transmit = _uart_dma_tran
#else
    .dma_transmit = RT_NULL
#endif
};

struct k230_uart_dev
{
    struct rt_serial_device serial;
    struct device_uart      uart;
    const char *name;
    rt_uint32_t pa_base;
    rt_uint32_t uart_to_size;
    rt_uint32_t irqno;

    #ifdef BSP_UART_USING_DMA
    /* DMA info */
    rt_uint8_t dma_ch;
    usr_pdma_cfg_t pdma_cfg;
    rt_event_t dma_event;
    #endif
};

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

#ifdef BSP_UART_USING_DMA
static void _k230_uart_pdma_call_back(rt_uint8_t ch, rt_bool_t is_done)
{
    uart_pdma_event_t event_type = is_done ? K230_UART_PDMA_EVENT_COMPLETE : K230_UART_PDMA_EVENT_TIMEOUT;
    for (size_t i = 0; i < sizeof(uart_devs)/sizeof(uart_devs[0]); i++)
    {
        struct k230_uart_dev *d = &uart_devs[i];
        if (d->dma_ch != PDMA_CH_INVALID && d->dma_ch == ch && d->dma_event != RT_NULL)
        {
            rt_event_send(d->dma_event, event_type);
            return;
        }
    }
}
#endif

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

static void _uart_set_isr(void *uart_base, uint8_t enable, uint32_t irq_type)
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
static rt_err_t _rt_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    return (RT_EOK);
}

static rt_err_t _uart_control(struct rt_serial_device *serial, int cmd, void *arg)
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
            _uart_set_isr((void*)(uart->hw_base), 0, UART_IER_RDI);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
#ifdef RT_USING_SERIAL_V2
        if (ctrl_flag & RT_DEVICE_FLAG_INT_RX)
#else
        if ((size_t)arg == RT_DEVICE_FLAG_INT_RX)
#endif
        {
            _uart_set_isr((void*)(uart->hw_base), 1, UART_IER_RDI);
        }
        break;
#ifdef RT_USING_SERIAL_V2
    case RT_DEVICE_CTRL_CONFIG:
        if (ctrl_flag & RT_DEVICE_FLAG_INT_RX)
        {
            _uart_set_isr((void*)(uart->hw_base), 1, UART_IER_RDI);
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

static int _drv_uart_putc(struct rt_serial_device *serial, char c)
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

static int _drv_uart_getc(struct rt_serial_device *serial)
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

#ifdef BSP_UART_USING_DMA
static rt_err_t _uart_dma_init(struct k230_uart_dev *dev)
{
    rt_err_t err;

    usr_pdma_cfg_t *cfg = &dev->pdma_cfg;

    if (!strcmp(dev->name, "uart0"))
    {
        cfg->device = UART0_TX;
    }
    else if (!strcmp(dev->name, "uart1"))
    {
        cfg->device = UART1_TX;
    }
    else if (!strcmp(dev->name, "uart2"))
    {
        cfg->device = UART2_TX;
    }
    else if (!strcmp(dev->name, "uart3"))
    {
        cfg->device = UART3_TX;
    }
    else if (!strcmp(dev->name, "uart4"))
    {
        cfg->device = UART4_TX;
    }

    cfg->dst_addr = (rt_uint8_t *)(uintptr_t)dev->pa_base;

    cfg->pdma_ch_cfg.ch_src_type   = CONTINUE;
    cfg->pdma_ch_cfg.ch_dev_hsize  = PSBYTE1;
    cfg->pdma_ch_cfg.ch_dat_endian = PDEFAULT;
    cfg->pdma_ch_cfg.ch_dev_blen   = PBURST_LEN_16;
    cfg->pdma_ch_cfg.ch_priority   = 7;                   // channel priority
    cfg->pdma_ch_cfg.ch_dev_tout   = 0xFFF;               // device timeout

    return RT_EOK;
}

static rt_ssize_t _uart_dma_write(struct rt_serial_device *serial, const void *buffer, rt_size_t size)
{
    struct k230_uart_dev *uart_dev = rt_container_of(serial, struct k230_uart_dev, serial);
    rt_uint32_t recv_event;
    rt_err_t err;
    rt_uint8_t ch;

    err = k230_pdma_request_channel(&ch);
    if (err != RT_EOK)
    {
        const char *ptr = buffer;
        for (rt_size_t i = 0; i < size; i++)
        {
            _drv_uart_putc(serial, ptr[i]);
        }
        return size;
    }

    uint32_t len = RT_ALIGN(size, 64);
    uint8_t *buf = rt_malloc_align(len, 64);
    rt_memcpy(buf, buffer, size);
    rt_hw_cpu_dcache_clean((void*)buf, len);
    void *buf_pa = rt_kmem_v2p(buf);
    uart_dev->dma_ch = ch;

    err = k230_pdma_set_callback(ch, _k230_uart_pdma_call_back);
    if (err != RT_EOK)
    {
        k230_pdma_release_channel(ch);
        rt_free_align(buf);
        return err;
    }

    uart_dev->pdma_cfg.src_addr  = buf_pa;
    uart_dev->pdma_cfg.line_size = len;
    rt_event_control(uart_dev->dma_event, RT_IPC_CMD_RESET, NULL);

    err = k230_pdma_config(ch, &uart_dev->pdma_cfg);
    err = k230_pdma_start(ch);

    err = rt_event_recv(uart_dev->dma_event,
                       K230_UART_PDMA_EVENT_COMPLETE | K230_UART_PDMA_EVENT_TIMEOUT,
                       RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                       RT_WAITING_FOREVER,
                       &recv_event);

    k230_pdma_stop(ch);
    k230_pdma_release_channel(ch);
    uart_dev->dma_ch = PDMA_CH_INVALID;
    rt_free_align(buf);
    return size;
}

static rt_ssize_t _uart_dma_tran(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    rt_ssize_t len;
    if (RT_SERIAL_DMA_TX == direction)
    {
        len = _uart_dma_write(serial, (void*)buf, size);
    }
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
    return len;
}
#endif

static void _rt_hw_uart_isr(int irq, void *param)
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

int rt_hw_uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t ret;

    for (int i = 0; i < sizeof(uart_devs)/sizeof(uart_devs[0]); i++)
    {
        struct k230_uart_dev *dev = &uart_devs[i];

        dev->serial.ops = &_uart_ops;
        dev->serial.config = config;
        dev->serial.config.baud_rate = UART_DEFAULT_BAUDRATE;

        dev->uart.pa_base = (void *)(uintptr_t)dev->pa_base;
        dev->uart.hw_base = (rt_base_t)rt_ioremap(dev->uart.pa_base, dev->uart_to_size);
        dev->uart.irqno   = dev->irqno;

        #ifdef BSP_UART_USING_DMA
            dev->dma_ch = PDMA_CH_INVALID;
            dev->dma_event = (rt_event_t)rt_malloc(sizeof(struct rt_event));
            if (dev->dma_event == RT_NULL)
            {
                LOG_E("Failed to allocate memory for %s pdma_event!", dev->name);
                return -RT_ENOMEM;
            }

            ret = rt_event_init(dev->dma_event, dev->name, RT_IPC_FLAG_FIFO);
            if (ret != RT_EOK)
            {
                LOG_E("Failed to init pdma_event for %s!", dev->name);
                rt_free(dev->dma_event);
                return ret;
            }

            ret = _uart_dma_init(dev);
            if (ret != RT_EOK)
            {
                LOG_E("Failed to init DMA for %s, ret=%d\n", dev->name, ret);
                return ret;
            }
        #endif

        _uart_init((void*)(dev->uart.hw_base));

        rt_hw_interrupt_install(dev->uart.irqno, _rt_hw_uart_isr, &dev->serial, dev->name);
        rt_hw_interrupt_umask(dev->uart.irqno);

        rt_uint32_t flags;
        flags = RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX;
        #ifdef BSP_UART_USING_DMA
        flags = RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_TX;
        #endif

        ret = rt_hw_serial_register(&dev->serial, dev->name, flags, &dev->uart);
        if (ret != RT_EOK)
        {
            LOG_E("Failed to register %s, ret=%d\n", dev->name, ret);
            return ret;
        }
    }
    return RT_EOK;
}