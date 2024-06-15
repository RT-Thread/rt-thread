/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-11     liYony       the first version
 */

#include <rthw.h>
#include <rtdevice.h>
#include <drv_uart.h>
#include "board.h"
#include "zynqmp_uart.h"

#define ZYNQMP_UART_DEVICE_DEFAULT(base, irq, clk) {{   \
        .ops = &_zynqmp_ops,                            \
        .config = RT_SERIAL_CONFIG_DEFAULT              \
    },                                                  \
    .hw_base = base,                                    \
    .irqno = irq,                                       \
    .in_clk = clk                                       \
}

struct zynqmp_uart_device
{
    struct rt_serial_device device;
    rt_ubase_t hw_base;
    rt_uint32_t irqno;
    rt_uint32_t in_clk;
};

static void _uart_set_fifo_threshold(rt_ubase_t base, rt_uint8_t trigger_level)
{
    rt_uint32_t reg_triger;

    /* Assert validates the input arguments */
    RT_ASSERT(base != RT_NULL);
    RT_ASSERT(trigger_level <= (rt_uint8_t)XUARTPS_RXWM_MASK);

    reg_triger = ((rt_uint32_t)trigger_level) & (rt_uint32_t)XUARTPS_RXWM_MASK;

    /*
     * Write the new value for the FIFO control register to it such that the
     * threshold is changed
     */
    writel(reg_triger, base + XUARTPS_RXWM_OFFSET);
}

static void _uart_set_interrupt_mask(rt_ubase_t base, rt_uint32_t mask)
{
    rt_uint32_t temp_mask = mask;

    RT_ASSERT(base != RT_NULL);

    temp_mask &= (rt_uint32_t)XUARTPS_IXR_MASK;

    writel(temp_mask, base + XUARTPS_IER_OFFSET);
    writel((~temp_mask), base + XUARTPS_IDR_OFFSET);
}

static rt_err_t _uart_baudrate_init(rt_ubase_t base, struct serial_configure *cfg, rt_uint32_t in_clk)
{
    rt_uint32_t iter_baud_div;     /* Iterator for available baud divisor values */
    rt_uint32_t brgr_value;        /* Calculated value for baud rate generator */
    rt_uint32_t calc_baudrate;     /* Calculated baud rate */
    rt_uint32_t baud_error;        /* Diff between calculated and requested baud rate */
    rt_uint32_t best_brgr = 0U;    /* Best value for baud rate generator */
    rt_uint8_t best_baud_div = 0U; /* Best value for baud divisor */
    rt_uint32_t best_error = 0xFFFFFFFFU;
    rt_uint32_t percent_error;
    rt_uint32_t mode_reg;
    rt_uint32_t input_clk;
    rt_uint32_t temp_reg;

    /* Asserts validate the input arguments */
    RT_ASSERT(base != RT_NULL);
    RT_ASSERT(cfg->baud_rate <= (rt_uint32_t)XUARTPS_MAX_RATE);
    RT_ASSERT(cfg->baud_rate >= (rt_uint32_t)XUARTPS_MIN_RATE);

    /*
     * Make sure the baud rate is not impossilby large.
     * Fastest possible baud rate is Input Clock / 2.
     */
    if ((cfg->baud_rate * 2) > in_clk)
    {
        return -RT_EINVAL;
    }
    /* Check whether the input clock is divided by 8 */
    mode_reg = readl(base + XUARTPS_MR_OFFSET);

    input_clk = in_clk;
    if (mode_reg & XUARTPS_MR_CLKSEL)
    {
        input_clk = in_clk / 8;
    }

    /*
     * Determine the Baud divider. It can be 4to 254.
     * Loop through all possible combinations
     */
    for (iter_baud_div = 4; iter_baud_div < 255; iter_baud_div++)
    {

        /* Calculate the value for BRGR register */
        brgr_value = input_clk / (cfg->baud_rate * (iter_baud_div + 1));

        /* Calculate the baud rate from the BRGR value */
        calc_baudrate = input_clk / (brgr_value * (iter_baud_div + 1));

        /* Avoid unsigned integer underflow */
        if (cfg->baud_rate > calc_baudrate)
        {
            baud_error = cfg->baud_rate - calc_baudrate;
        }
        else
        {
            baud_error = calc_baudrate - cfg->baud_rate;
        }

        /* Find the calculated baud rate closest to requested baud rate. */
        if (best_error > baud_error)
        {

            best_brgr = brgr_value;
            best_baud_div = iter_baud_div;
            best_error = baud_error;
        }
    }

    /* Make sure the best error is not too large. */
    percent_error = (best_error * 100) / cfg->baud_rate;
    if (XUARTPS_MAX_BAUD_ERROR_RATE < percent_error)
    {
        return -RT_EINVAL;
    }

    /* Disable TX and RX to avoid glitches when setting the baud rate. */
    temp_reg = (((readl(base + XUARTPS_CR_OFFSET)) & ((rt_uint32_t)(~XUARTPS_CR_EN_DIS_MASK))) |
                ((rt_uint32_t)XUARTPS_CR_RX_DIS | (rt_uint32_t)XUARTPS_CR_TX_DIS));
    writel(temp_reg, base + XUARTPS_CR_OFFSET);

    /* Set the baud rate divisor */
    writel(best_brgr, base + XUARTPS_BAUDGEN_OFFSET);
    writel(best_baud_div, base + XUARTPS_BAUDDIV_OFFSET);

    /* RX and TX SW reset */
    writel(XUARTPS_CR_TXRST | XUARTPS_CR_RXRST, base + XUARTPS_CR_OFFSET);

    /* Enable device */
    temp_reg = (((readl(base + XUARTPS_CR_OFFSET)) & ((rt_uint32_t)(~XUARTPS_CR_EN_DIS_MASK))) |
                ((rt_uint32_t)XUARTPS_CR_RX_EN | (rt_uint32_t)XUARTPS_CR_TX_EN));
    writel(temp_reg, base + XUARTPS_CR_OFFSET);

    return RT_EOK;
}

static rt_err_t zynqmp_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct zynqmp_uart_device *uart = (struct zynqmp_uart_device *)serial;

    RT_ASSERT(uart != RT_NULL);

    if (_uart_baudrate_init(uart->hw_base, cfg, uart->in_clk) != RT_EOK)
    {
        return -RT_ERROR;
    }

    rt_uint32_t mode_reg = 0U;

    /* Set the parity mode */
    mode_reg = readl(uart->hw_base + XUARTPS_MR_OFFSET);

    /* Mask off what's already there */
    mode_reg &= (~((rt_uint32_t)XUARTPS_MR_CHARLEN_MASK |
                   (rt_uint32_t)XUARTPS_MR_STOPMODE_MASK |
                   (rt_uint32_t)XUARTPS_MR_PARITY_MASK));

    switch (cfg->data_bits)
    {
    case DATA_BITS_6:
        mode_reg |= (rt_uint32_t)XUARTPS_MR_CHARLEN_6_BIT;
        break;
    case DATA_BITS_7:
        mode_reg |= (rt_uint32_t)XUARTPS_MR_CHARLEN_7_BIT;
        break;
    case DATA_BITS_8:
        mode_reg |= (rt_uint32_t)XUARTPS_MR_CHARLEN_8_BIT;
        break;
    default:
        mode_reg |= (rt_uint32_t)XUARTPS_MR_CHARLEN_8_BIT;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        mode_reg |= (rt_uint32_t)XUARTPS_MR_STOPMODE_1_BIT;
        break;
    case STOP_BITS_2:
        mode_reg |= (rt_uint32_t)XUARTPS_MR_STOPMODE_2_BIT;
        break;
    default:
        mode_reg |= (rt_uint32_t)XUARTPS_MR_STOPMODE_1_BIT;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        mode_reg |= (rt_uint32_t)XUARTPS_MR_PARITY_NONE;
        break;
    case PARITY_ODD:
        mode_reg |= (rt_uint32_t)XUARTPS_MR_PARITY_ODD;
        break;
    case PARITY_EVEN:
        mode_reg |= (rt_uint32_t)XUARTPS_MR_PARITY_EVEN;
        break;
    default:
        mode_reg |= (rt_uint32_t)XUARTPS_MR_PARITY_NONE;
        break;
    }

    /* Write the mode register out */
    writel(mode_reg, uart->hw_base + XUARTPS_MR_OFFSET);

    /* Set the RX FIFO trigger at 8 data bytes. */
    writel(0x08U, uart->hw_base + XUARTPS_RXWM_OFFSET);

    /* Set the RX timeout to 1, which will be 4 character time */
    writel(0x01U, uart->hw_base + XUARTPS_RXTOUT_OFFSET);

    /* Disable all interrupts, polled mode is the default */
    writel(XUARTPS_IXR_MASK, uart->hw_base + XUARTPS_IDR_OFFSET);

    return RT_EOK;
}

static rt_err_t zynqmp_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct zynqmp_uart_device *uart = (struct zynqmp_uart_device *)serial;

    RT_ASSERT(uart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable the UART Interrupt */
        rt_hw_interrupt_mask(uart->irqno);
        _uart_set_interrupt_mask(uart->hw_base, 0U);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* Enable the UART Interrupt */
        _uart_set_fifo_threshold(uart->hw_base, 1);
        rt_hw_interrupt_umask(uart->irqno);
        _uart_set_interrupt_mask(uart->hw_base, XUARTPS_IXR_RXOVR);
        break;
    }

    return RT_EOK;
}

static int zynqmp_uart_putc(struct rt_serial_device *serial, char c)
{
    struct zynqmp_uart_device *uart = (struct zynqmp_uart_device *)serial;

    RT_ASSERT(uart != RT_NULL);

    /* Wait until there is space in TX FIFO */
    while ((readl(uart->hw_base + XUARTPS_SR_OFFSET) &
            XUARTPS_SR_TXFULL) == XUARTPS_SR_TXFULL)
    {
        ;
    }

    /* Write the byte into the TX FIFO */
    writel((rt_uint32_t)c, uart->hw_base + XUARTPS_FIFO_OFFSET);

    return 1;
}

static int zynqmp_uart_getc(struct rt_serial_device *serial)
{
    struct zynqmp_uart_device *uart = (struct zynqmp_uart_device *)serial;

    RT_ASSERT(uart != RT_NULL);

    /* Wait until there is data */
    if ((readl(uart->hw_base + XUARTPS_SR_OFFSET) &
         XUARTPS_SR_RXEMPTY) == XUARTPS_SR_RXEMPTY)
    {
        return -1;
    }

    int ch = readl(uart->hw_base + XUARTPS_FIFO_OFFSET);

    return ch;
}

static const struct rt_uart_ops _zynqmp_ops =
{
    zynqmp_uart_configure,
    zynqmp_uart_control,
    zynqmp_uart_putc,
    zynqmp_uart_getc,
};

#ifdef BSP_USING_UART0
static struct zynqmp_uart_device _uart0_device =
    ZYNQMP_UART_DEVICE_DEFAULT(ZYNQMP_UART0_BASE, ZYNQMP_UART0_IRQNUM, ZYNQMP_UART0_CLK_FREQ_HZ);
#endif

static void rt_hw_uart_isr(int irqno, void *param)
{
    struct zynqmp_uart_device *uart = (struct zynqmp_uart_device *)param;

    RT_ASSERT(uart != RT_NULL);
    struct rt_serial_device *serial = &(uart->device);
    rt_uint32_t isr_status;

    isr_status = readl(uart->hw_base + XUARTPS_IMR_OFFSET);
    isr_status &= readl(uart->hw_base + XUARTPS_ISR_OFFSET);
    if (isr_status & (rt_uint32_t)XUARTPS_IXR_RXOVR)
    {
        writel(XUARTPS_IXR_RXOVR, uart->hw_base + XUARTPS_ISR_OFFSET);
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
}

int rt_hw_uart_init(void)
{
    struct zynqmp_uart_device *uart = RT_NULL;

#ifdef BSP_USING_UART0
    uart = &_uart0_device;
    _uart0_device.hw_base = (rt_size_t)rt_ioremap((void*)_uart0_device.hw_base, ZYNQMP_UART0_SIZE);
    /* register UART0 device */
    rt_hw_serial_register(&uart->device, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
    rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, uart, "uart0");
#endif

    return 0;
}
