/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-10-15     IronsideZhang     first version
 */

#include <rthw.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_uart.h"
#include "riscv_io.h"
#include "drv_pinctrl.h"
#include "sysctl_clk.h"

#ifndef RT_USING_SMART
#define rt_ioremap(addr, size) (addr)
#endif

/* K1 UART is 16550A compatible, use standard register offsets */
#define UART_RBR (0x00)
#define UART_THR (0x00)
#define UART_DLL (0x00)
#define UART_IER (0x04)
#define UART_DLH (0x04)
#define UART_IIR (0x08)
#define UART_FCR (0x08)
#define UART_LCR (0x0c)
#define UART_LSR (0x14)

#define UART_LCR_DLAB (1 << 7)
#define UART_LCR_WLEN8 (3)
#define UART_LSR_THRE (1 << 5)
#define UART_LSR_DR (1 << 0)
#define UART_IER_RDI (1 << 0)
#define UART_IIR_NO_INT (1)

struct k1_uart
{
    struct rt_serial_device serial;
    volatile void *hw_base;
    int irqno;
    const char *name;
};

static struct k1_uart uart_devs[] =
{
#ifdef BSP_USING_UART0
    {
        .name = "uart0",
        .hw_base = (void*)UART0_BASE_ADDR,
        .irqno = K1_IRQ_UART0,
    },
#endif
};

static rt_err_t _uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct k1_uart *uart = (struct k1_uart *)serial->parent.user_data;
    rt_uint32_t uart_clk = k1_sysctl_clk_get_leaf_freq(CLK_UART1);
    if (uart_clk == 0)
    {
        rt_kprintf("ERROR: UART clock is 0!\n");
        return -RT_ERROR;
    }
    rt_uint32_t divisor = uart_clk / (16 * cfg->baud_rate);

    /* Set DLAB to access DLL and DLH */
    writel(readl(uart->hw_base + UART_LCR) | UART_LCR_DLAB, uart->hw_base + UART_LCR);

    writel(divisor & 0xff, uart->hw_base + UART_DLL);
    writel((divisor >> 8) & 0xff, uart->hw_base + UART_DLH);

    /* Clear DLAB and set 8N1 format */
    writel(UART_LCR_WLEN8, uart->hw_base + UART_LCR);

    /* Enable FIFO */
    writel(0x01, uart->hw_base + UART_FCR);

    return RT_EOK;
}

static rt_err_t _uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct k1_uart *uart = (struct k1_uart *)serial->parent.user_data;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        writel(readl(uart->hw_base + UART_IER) & ~UART_IER_RDI, uart->hw_base + UART_IER);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        writel(readl(uart->hw_base + UART_IER) | UART_IER_RDI, uart->hw_base + UART_IER);
        break;
    }
    return RT_EOK;
}

static int _uart_putc(struct rt_serial_device *serial, char c)
{
    struct k1_uart *uart = (struct k1_uart *)serial->parent.user_data;
    while (!(readl(uart->hw_base + UART_LSR) & UART_LSR_THRE));
    writel(c, uart->hw_base + UART_THR);
    return 1;
}

static int _uart_getc(struct rt_serial_device *serial)
{
    struct k1_uart *uart = (struct k1_uart *)serial->parent.user_data;
    if (readl(uart->hw_base + UART_LSR) & UART_LSR_DR)
    {
        return readl(uart->hw_base + UART_RBR);
    }
    return -1;
}

static void _uart_isr(int irq, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;
    struct k1_uart *uart = (struct k1_uart *)serial->parent.user_data;

    if ((readl(uart->hw_base + UART_IIR) & 0x1) == UART_IIR_NO_INT)
        return;

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

static const struct rt_uart_ops _uart_ops =
{
    .configure = _uart_configure,
    .control = _uart_control,
    .putc = _uart_putc,
    .getc = _uart_getc,
};

int rt_hw_uart_init(void)
{
    /* 1. Initialize prerequisite drivers */
    k1_pinctrl_init();
    k1_sysctl_clk_init();

    for (int i = 0; i < sizeof(uart_devs) / sizeof(uart_devs[0]); i++)
    {
        struct k1_uart *uart = &uart_devs[i];
        struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

        /* 2. Configure Pin Function for UART0*/
        // Configure TX pin
        k1_pinctrl_set_function(GPIO_68, MUX_MODE2);
        k1_pinctrl_set_pull(GPIO_68, PULL_UP); // Set TX to pull-up as per DTS

        // Configure RX pin
        k1_pinctrl_set_function(GPIO_69, MUX_MODE2);
        k1_pinctrl_set_pull(GPIO_69, PULL_UP); // Set RX to pull-up as per DTS

        /* 3. Enable Clock for UART0 (from DTS and TRM) */
        k1_sysctl_clk_set_leaf_en(CLK_UART1, 1);

        /* 4. Register device to RT-Thread */
        uart->serial.ops = &_uart_ops;
        uart->serial.config = config;
        uart->hw_base = rt_ioremap(uart->hw_base, UART0_IO_SIZE);

        rt_hw_serial_register(&uart->serial, uart->name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
        rt_hw_interrupt_install(uart->irqno, _uart_isr, &uart->serial, uart->name);
        rt_hw_interrupt_umask(uart->irqno);
    }
    return 0;
}