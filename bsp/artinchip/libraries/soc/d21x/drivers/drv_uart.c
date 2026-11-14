/*
 * Copyright (c) 2021-2026, ArtInChip Technology Co., Ltd
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * D213 serial-v1 adapter. Register sequence adapted from Luban-Lite
 * bsp/artinchip/hal/uart/aic_hal_uart.c. No vendor OSAL or DMA dependency.
 */

#include <rthw.h>
#include <rtdevice.h>
#include <interrupt.h>
#include <riscv_timer.h>
#include "aic_soc.h"
#include "aic_uart_reg.h"

struct aic_uart
{
    struct rt_serial_device serial;
    rt_ubase_t base;
    rt_ubase_t clock_reg;
    int irq;
    const char *name;
    rt_bool_t rx_enabled;
};

static struct aic_uart uart0 = {
    .base = AIC_UART0_BASE,
    .clock_reg = AIC_CMU_UART0,
    .irq = AIC_UART0_IRQ,
    .name = "uart0",
};
static struct rt_thread rx_thread;
rt_align(RT_ALIGN_SIZE) static rt_uint8_t rx_stack[1024];

static rt_err_t aic_uart_configure(struct rt_serial_device *serial,
                                   struct serial_configure *cfg)
{
    struct aic_uart *uart = serial->parent.user_data;
    rt_uint32_t divisor, lcr, old_lcr;
    rt_uint64_t deadline;
    rt_err_t ret = -RT_EIO;
    rt_base_t level;

    if (!cfg->baud_rate || cfg->data_bits < DATA_BITS_5 ||
        cfg->data_bits > DATA_BITS_8 ||
        (cfg->stop_bits != STOP_BITS_1 && cfg->stop_bits != STOP_BITS_2) ||
        (cfg->data_bits == DATA_BITS_5 && cfg->stop_bits == STOP_BITS_2) ||
        (cfg->parity != PARITY_NONE && cfg->parity != PARITY_ODD &&
         cfg->parity != PARITY_EVEN) ||
        cfg->bit_order != BIT_ORDER_LSB || cfg->invert != NRZ_NORMAL ||
        cfg->flowcontrol != RT_SERIAL_FLOWCONTROL_NONE)
    {
        /* With five data bits the hardware STOP bit means 1.5 stop bits,
         * which serial-v1 cannot represent. Reject a request for two. */
        return -RT_EINVAL;
    }
    lcr = cfg->data_bits - DATA_BITS_5;
    if (cfg->stop_bits == STOP_BITS_2)
    {
        lcr |= UART_LCR_STOP;
    }
    if (cfg->parity != PARITY_NONE)
    {
        lcr |= UART_LCR_PARITY;
        if (cfg->parity == PARITY_EVEN)
        {
            lcr |= UART_LCR_EVEN;
        }
    }
    divisor = ((rt_uint64_t)BSP_UART_CLK_FREQ + cfg->baud_rate * 8ULL) /
              (cfg->baud_rate * 16ULL);
    if (!divisor || divisor > 0xffff)
    {
        return -RT_EINVAL;
    }

    deadline = riscv_timer_rdtime() + BSP_CLINT_FREQ / 10;
    for (;;)
    {
        level = rt_hw_interrupt_disable();
        /* Like the vendor HAL, reset FIFOs before waiting for idle.
         * A busy controller can ignore LCR writes; DLL then aliases THR. */
        aic_write32(uart->base + UART_FCR,
                    UART_FCR_ENABLE | UART_FCR_RX_RESET | UART_FCR_TX_RESET |
                        UART_FCR_TX_TRIGGER | UART_FCR_RX_TRIGGER);
        if (!(aic_read32(uart->base + UART_USR) & UART_USR_BUSY))
        {
            break;
        }
        rt_hw_interrupt_enable(level);
        if (riscv_timer_rdtime() >= deadline)
        {
            return -RT_ETIMEOUT;
        }
    }
    /* IER aliases DLH while DLAB is set, including on loader handoff. */
    old_lcr = aic_read32(uart->base + UART_LCR) & ~UART_LCR_DLAB;
    aic_write32(uart->base + UART_LCR, old_lcr);
    if (aic_read32(uart->base + UART_LCR) & UART_LCR_DLAB)
    {
        goto restore_lcr;
    }
    aic_write32(uart->base + UART_IER, 0);
    aic_write32(uart->base + UART_LCR, lcr | UART_LCR_DLAB);
    if ((aic_read32(uart->base + UART_LCR) & 0xff) != (lcr | UART_LCR_DLAB))
    {
        goto restore_lcr;
    }
    aic_write32(uart->base + UART_DLL, divisor & 0xff);
    aic_write32(uart->base + UART_DLH, divisor >> 8);
    aic_write32(uart->base + UART_LCR, lcr);
    if ((aic_read32(uart->base + UART_LCR) & 0xff) != lcr)
    {
        goto restore_lcr;
    }
    aic_write32(uart->base + UART_MCR, 0);
    ret = RT_EOK;
    goto out;

restore_lcr:
    aic_write32(uart->base + UART_LCR, old_lcr);
out:
    rt_hw_interrupt_enable(level);
    return ret;
}

static rt_err_t aic_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct aic_uart *uart = serial->parent.user_data;
    rt_base_t level;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SET_INT:
    case RT_DEVICE_CTRL_CLR_INT:
        level = rt_hw_interrupt_disable();
        uart->rx_enabled = (cmd == RT_DEVICE_CTRL_SET_INT);
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    default:
        return -RT_ENOSYS;
    }
}

static int aic_uart_putc(struct rt_serial_device *serial, char c)
{
    struct aic_uart *uart = serial->parent.user_data;

    /* Bound a stalled transmitter without depending on scheduler state. */
    rt_uint64_t deadline = riscv_timer_rdtime() + BSP_CLINT_FREQ / 10;

    /* Like the vendor hal_usart_putchar, wait for room in the TX FIFO.
     * LSR.THRE reports the TX threshold, not whether a byte can be queued. */
    while (!(aic_read32(uart->base + UART_USR) & UART_USR_TFNF))
    {
        if (riscv_timer_rdtime() >= deadline)
        {
            return -1;
        }
    }
    aic_write32(uart->base + UART_THR, (rt_uint8_t)c);
    return 1;
}

static int aic_uart_getc(struct rt_serial_device *serial)
{
    struct aic_uart *uart = serial->parent.user_data;

    if (aic_read32(uart->base + UART_LSR) & UART_LSR_DR)
    {
        return aic_read32(uart->base + UART_RBR) & 0xff;
    }
    return -1;
}

static const struct rt_uart_ops aic_uart_ops = {
    .configure = aic_uart_configure,
    .control = aic_uart_control,
    .putc = aic_uart_putc,
    .getc = aic_uart_getc,
};

static void aic_uart_rx_poll(void *parameter)
{
    for (;;)
    {
        rt_base_t level = rt_hw_interrupt_disable();

        /* Serial-v1 owns the FIFO. Serialize with close/reconfigure
         * so the single-core poller cannot access a freed FIFO. */
        if (uart0.rx_enabled && uart0.serial.serial_rx != RT_NULL &&
            (aic_read32(uart0.base + UART_LSR) & UART_LSR_DR))
        {
            rt_hw_serial_isr(&uart0.serial, RT_SERIAL_EVENT_RX_IND);
        }
        rt_hw_interrupt_enable(level);
        rt_thread_mdelay(1);
    }
}

static int aic_uart_poll_init(void)
{
    rt_err_t ret;
    int priority = RT_THREAD_PRIORITY_MAX / 2;

#ifdef RT_USING_FINSH
    /* Poll RX even while the shell is busy transmitting console output. */
    priority = FINSH_THREAD_PRIORITY > 0 ? FINSH_THREAD_PRIORITY - 1 : 0;
#endif

    ret = rt_thread_init(&rx_thread, "uart0rx", aic_uart_rx_poll, RT_NULL,
                         rx_stack, sizeof(rx_stack), priority, 10);
    if (ret != RT_EOK)
    {
        return ret;
    }
    return rt_thread_startup(&rx_thread);
}
INIT_DEVICE_EXPORT(aic_uart_poll_init);

void rt_hw_serial_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t ret;

    rt_uint32_t value = aic_read32(uart0.clock_reg);

    /* Drop loader state while retaining the divider and gate bits. */
    aic_write32(uart0.clock_reg, value & ~(1U << 13));
    rt_hw_us_delay(30);
    aic_write32(uart0.clock_reg, value | (1U << 13));
    rt_hw_us_delay(30);

    uart0.serial.ops = &aic_uart_ops;
    uart0.serial.config = config;
    rt_hw_interrupt_mask(IRQ_PLIC(uart0.irq));
    ret = rt_hw_serial_register(&uart0.serial, uart0.name,
                                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, &uart0);
    RT_ASSERT(ret == RT_EOK);
}
