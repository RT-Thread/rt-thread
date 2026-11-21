/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * UART0 from embedded board.dtb (polling). Gate/reset/pins/baud/reg
 * come from FDT; register program matches the proven divisor path.
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_uart.h"
#include "drv_fdt.h"

#define UART_RBR        0x00
#define UART_THR        0x00
#define UART_DLL        0x00
#define UART_DLM        0x04
#define UART_IER        0x04
#define UART_FCR        0x08
#define UART_LCR        0x0c
#define UART_MCR        0x10
#define UART_LSR        0x14
#define UART_LSR_DR     0x01
#define UART_LSR_THRE   0x20
#define UART_LCR_DLAB   0x80
#define UART_LCR_8N1    0x03
#define UART_FCR_EN     0x07
#define UART_MCR_DTR_RTS 0x03

/* sun252iw1 GPIO bank stride (PH_CFG1 is 0x02000154). */
#define SUNXI_GPIO_BASE     0x02000000U
#define SUNXI_GPIO_PORT_STRIDE 0x30U

static struct rt_serial_device serial0;
static struct v861_uart_fdt g_uart_fdt;
static rt_ubase_t g_uart_base = V861_UART0_BASE;

static rt_uint32_t uart_read(rt_ubase_t offset)
{
    return *(volatile rt_uint32_t *)(g_uart_base + offset);
}

static void uart_write(rt_ubase_t offset, rt_uint32_t value)
{
    *(volatile rt_uint32_t *)(g_uart_base + offset) = value;
}

static void mmio_set_bit(rt_ubase_t addr, rt_uint32_t bit)
{
    rt_uint32_t v = *(volatile rt_uint32_t *)addr;
    *(volatile rt_uint32_t *)addr = v | (1U << bit);
}

static void mmio_clr_bit(rt_ubase_t addr, rt_uint32_t bit)
{
    rt_uint32_t v = *(volatile rt_uint32_t *)addr;
    *(volatile rt_uint32_t *)addr = v & ~(1U << bit);
}

static void v861_apply_pin(rt_uint32_t port, rt_uint32_t pin, rt_uint32_t func)
{
    rt_ubase_t cfg;
    rt_uint32_t shift;
    rt_uint32_t value;

    cfg = SUNXI_GPIO_BASE + port * SUNXI_GPIO_PORT_STRIDE + (pin / 8U) * 4U;
    shift = (pin % 8U) * 4U;
    value = *(volatile rt_uint32_t *)cfg;
    value = (value & ~(0xFU << shift)) | ((func & 0xFU) << shift);
    *(volatile rt_uint32_t *)cfg = value;
}

static void v861_uart0_hw_init(const struct v861_uart_fdt *cfg)
{
    rt_uint32_t divisor;
    rt_uint32_t i;

    /* Match SyterKit/SPL: gate off, reset assert, release reset, gate on. */
    mmio_clr_bit(cfg->gate_reg, cfg->gate_bit);
    mmio_clr_bit(cfg->reset_reg, cfg->reset_bit);
    for (i = 0; i < 1000; i++)
        __asm__ volatile("nop");
    mmio_set_bit(cfg->reset_reg, cfg->reset_bit);
    mmio_set_bit(cfg->gate_reg, cfg->gate_bit);

    for (i = 0; i < cfg->pin_count; i++)
        v861_apply_pin(cfg->pin_port[i], cfg->pin_num[i], cfg->pin_func[i]);

    g_uart_base = cfg->reg;
    divisor = cfg->clk_hz / (16U * cfg->baud);
    if (divisor == 0)
        divisor = 13;

    uart_write(UART_IER, 0);
    uart_write(UART_LCR, UART_LCR_DLAB);
    uart_write(UART_DLL, divisor);
    uart_write(UART_DLM, 0);
    uart_write(UART_LCR, UART_LCR_8N1);
    uart_write(UART_FCR, UART_FCR_EN);
    uart_write(UART_MCR, UART_MCR_DTR_RTS);
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    RT_UNUSED(serial);
    RT_UNUSED(cfg);
    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    RT_UNUSED(serial);
    RT_UNUSED(cmd);
    RT_UNUSED(arg);
    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    RT_UNUSED(serial);

    if (c == '\n')
    {
        while ((uart_read(UART_LSR) & UART_LSR_THRE) == 0)
        {
        }
        uart_write(UART_THR, '\r');
    }

    while ((uart_read(UART_LSR) & UART_LSR_THRE) == 0)
    {
    }
    uart_write(UART_THR, (rt_uint32_t)c);
    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    RT_UNUSED(serial);

    while ((uart_read(UART_LSR) & UART_LSR_DR) == 0)
    {
    }
    return (int)(uart_read(UART_RBR) & 0xff);
}

static rt_ssize_t uart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    RT_UNUSED(serial);
    RT_UNUSED(buf);
    RT_UNUSED(size);
    RT_UNUSED(direction);
    return 0;
}

static const struct rt_uart_ops uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
    uart_dma_transmit,
};

int rt_hw_uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    if (rt_hw_fdt_load_uart(&g_uart_fdt) != 0)
    {
        /* Fall back to board.h constants if DTB is missing. */
        g_uart_fdt.reg = V861_UART0_BASE;
        g_uart_fdt.baud = V861_UART0_BAUD;
        g_uart_fdt.clk_hz = V861_UART0_CLOCK_HZ;
        g_uart_fdt.gate_reg = 0x0200190cU;
        g_uart_fdt.gate_bit = 0;
        g_uart_fdt.reset_reg = 0x0200190cU;
        g_uart_fdt.reset_bit = 16;
        g_uart_fdt.pin_count = 2;
        g_uart_fdt.pin_port[0] = 7;
        g_uart_fdt.pin_num[0] = 9;
        g_uart_fdt.pin_func[0] = 5;
        g_uart_fdt.pin_port[1] = 7;
        g_uart_fdt.pin_num[1] = 10;
        g_uart_fdt.pin_func[1] = 5;
        g_uart_fdt.valid = 0;
        rt_strncpy(g_uart_fdt.compatible, "(fallback)", sizeof(g_uart_fdt.compatible) - 1);
        rt_strncpy(g_uart_fdt.stdout_path, "board.h", sizeof(g_uart_fdt.stdout_path) - 1);
    }

    v861_uart0_hw_init(&g_uart_fdt);
    config.baud_rate = g_uart_fdt.baud;
    serial0.ops = &uart_ops;
    serial0.config = config;
    return rt_hw_serial_register(&serial0, "uart0", RT_DEVICE_FLAG_RDWR, RT_NULL);
}

void rt_hw_uart_print_dt(void)
{
    rt_hw_fdt_print_uart(&g_uart_fdt);
}
