/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#include <rthw.h>
#include <rtthread.h>
#ifdef RT_USING_SERIAL
#include <rtdevice.h>
#endif
#include "drv_intc.h"
#include "drv_usart.h"
#include "soc.h"

#define RLIN3_LWBR   0x01
#define RLIN3_LBRP01 0x02
#define RLIN3_LMD    0x08
#define RLIN3_LBFC   0x09
#define RLIN3_LEDE   0x0d
#define RLIN3_LCUC   0x0e
#define RLIN3_LMST   0x11
#define RLIN3_LST    0x12
#define RLIN3_LUOER  0x20
#define RLIN3_LUOR1  0x21
#define RLIN3_LUTDR  0x24
#define RLIN3_LURDR  0x26

#define RLIN3_SAMPLES    16
#define RLIN3_LMD_UART   0x01
#define RLIN3_LCUC_OM0   (1 << 0)
#define RLIN3_LMST_OMM0  (1 << 0)
#define RLIN3_LST_UTS    (1 << 4)
#define RLIN3_LUOER_UTOE (1 << 0)
#define RLIN3_LUOER_UROE (1 << 1)

struct rh850_uart
{
#ifdef RT_USING_SERIAL
    struct rt_serial_device serial;
#endif
    rt_ubase_t base;
    int rx_vector;
    rt_uint32_t clk_hz;
    const char *name;
    volatile rt_uint8_t rx_ready;
};

static struct rh850_uart uarts[] = {
    {
        .base = SOC_RLIN311_BASE,
        .rx_vector = SOC_IRQ_RLIN311_UR1,
        .clk_hz = SOC_CLK_HSB_HZ,
        .name = "rlin311",
    },
};

static rt_ubase_t console_base;

/* Baud = clk / (LBRP01 + 1) / 16 with LWBR = 0; LBFC = 0 is 8N1 */
static void rlin3_setup(rt_ubase_t base, rt_uint32_t clk_hz, rt_uint32_t baud)
{
    rt_uint32_t div =
        (clk_hz + (RLIN3_SAMPLES * baud) / 2U) / (RLIN3_SAMPLES * baud);

    if (div == 0U)
    {
        div = 1U;
    }

    HWREG8(base + RLIN3_LCUC) = 0;
    while ((HWREG8(base + RLIN3_LMST) & RLIN3_LMST_OMM0) != 0U)
    {
    }

    HWREG8(base + RLIN3_LWBR) = 0;
    HWREG16(base + RLIN3_LBRP01) = (rt_uint16_t)(div - 1U);
    HWREG8(base + RLIN3_LMD) = RLIN3_LMD_UART;
    HWREG8(base + RLIN3_LBFC) = 0;
    HWREG8(base + RLIN3_LEDE) = 0;
    HWREG8(base + RLIN3_LUOR1) = 0;

    HWREG8(base + RLIN3_LCUC) = RLIN3_LCUC_OM0;
    while ((HWREG8(base + RLIN3_LMST) & RLIN3_LMST_OMM0) == 0U)
    {
    }
    HWREG8(base + RLIN3_LUOER) = RLIN3_LUOER_UTOE | RLIN3_LUOER_UROE;
}

static void rlin3_putc(rt_ubase_t base, char c)
{
    HWREG8(base + RLIN3_LUTDR) = (rt_uint8_t)c;
    while ((HWREG8(base + RLIN3_LST) & RLIN3_LST_UTS) != 0U)
    {
    }
}

#ifdef RT_USING_SERIAL
static rt_err_t rh850_uart_configure(struct rt_serial_device *serial,
                                     struct serial_configure *cfg)
{
    struct rh850_uart *uart = serial->parent.user_data;

    if (cfg->data_bits != DATA_BITS_8 || cfg->stop_bits != STOP_BITS_1 ||
        cfg->parity != PARITY_NONE || cfg->baud_rate == 0)
    {
        return -RT_EINVAL;
    }

    rlin3_setup(uart->base, uart->clk_hz, cfg->baud_rate);
    return RT_EOK;
}

static rt_err_t rh850_uart_control(struct rt_serial_device *serial, int cmd,
                                   void *arg)
{
    struct rh850_uart *uart = serial->parent.user_data;

    RT_UNUSED(arg);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SET_INT:
        rh850_intc_set_priority(uart->rx_vector, RH850_INTC_PRIO_LOWEST);
        rt_hw_interrupt_umask(uart->rx_vector);
        break;
    case RT_DEVICE_CTRL_CLR_INT:
        rt_hw_interrupt_mask(uart->rx_vector);
        break;
    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static int rh850_uart_putc(struct rt_serial_device *serial, char c)
{
    struct rh850_uart *uart = serial->parent.user_data;

    rlin3_putc(uart->base, c);
    return 1;
}

/* EIRF is cleared before LURDR is read, so the next request stays */
static int rh850_uart_getc(struct rt_serial_device *serial)
{
    struct rh850_uart *uart = serial->parent.user_data;

    if (!uart->rx_ready && !rh850_intc_pending(uart->rx_vector))
    {
        return -1;
    }

    uart->rx_ready = 0;
    rh850_intc_clear(uart->rx_vector);
    return HWREG16(uart->base + RLIN3_LURDR) & 0xffU;
}

static const struct rt_uart_ops rh850_uart_ops = {
    .configure = rh850_uart_configure,
    .control = rh850_uart_control,
    .putc = rh850_uart_putc,
    .getc = rh850_uart_getc,
    .dma_transmit = RT_NULL,
};

static void rh850_uart_isr(int vector, void *param)
{
    struct rh850_uart *uart = param;

    RT_UNUSED(vector);
    uart->rx_ready = 1;
    rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_RX_IND);
}

#endif

void rt_hw_console_output(const char *str)
{
    if (console_base == 0U)
    {
        return;
    }

    while (*str != '\0')
    {
        if (*str == '\n')
        {
            rlin3_putc(console_base, '\r');
        }
        rlin3_putc(console_base, *str++);
    }
}

int rt_hw_usart_init(void)
{
#ifdef RT_USING_SERIAL
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_size_t i;
    rt_err_t ret;

    rlin3_setup(uarts[0].base, uarts[0].clk_hz, config.baud_rate);
    console_base = uarts[0].base;

    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++)
    {
        uarts[i].serial.ops = &rh850_uart_ops;
        uarts[i].serial.config = config;
        rt_hw_interrupt_install(uarts[i].rx_vector, rh850_uart_isr, &uarts[i],
                                uarts[i].name);
        ret = rt_hw_serial_register(&uarts[i].serial, uarts[i].name,
                                    RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                    &uarts[i]);
        if (ret != RT_EOK)
        {
            return ret;
        }
    }
#else
    rlin3_setup(uarts[0].base, uarts[0].clk_hz, 115200);
    console_base = uarts[0].base;
#endif

    return RT_EOK;
}
