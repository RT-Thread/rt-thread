/*
 * File      : serial.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-06     Bernard    the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <am33xx.h>
#include <interrupt.h>
#include "serial.h"
#include "serial_reg.h"

struct am33xx_uart
{
    unsigned long base;
    int irq;
};

static void am33xx_uart_isr(int irqno, void* param)
{
    rt_uint32_t iir;
    struct am33xx_uart* uart;
    struct rt_serial_device *serial;

    serial = (struct rt_serial_device*)param;
    uart = (struct am33xx_uart *)serial->parent.user_data;

    iir = UART_IIR_REG(uart->base);

	if ((iir & (0x02 << 1)) || (iir & (0x6 << 1)))
    {
        rt_hw_serial_isr(serial);
    }
}

#define NOT_IMPLEMENTED() RT_ASSERT(0)

static rt_err_t am33xx_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct am33xx_uart* uart;
    unsigned long base;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct am33xx_uart *)serial->parent.user_data;
    RT_ASSERT(uart);
    base = uart->base;

#define __LCR UART_LCR_REG(base)

    if (cfg->data_bits == DATA_BITS_8)
        __LCR |= 3;
    else
        NOT_IMPLEMENTED();

    if (cfg->stop_bits == STOP_BITS_1)
        __LCR &= ~(1<<2);
    else
        __LCR |=  (1<<2);

    if (cfg->parity == PARITY_NONE)
        __LCR &= ~(1<<3);
    else
        __LCR |=  (1<<3);

    __LCR |=  (1<<7);
    if (cfg->baud_rate == BAUD_RATE_115200)
    {
        UART_DLL_REG(base) = 26;
        UART_DLH_REG(base) = 0;
    }
    else
    {
        NOT_IMPLEMENTED();
    }
    __LCR &= ~(1<<7);

    UART_MDR1_REG(base) = 0;
    UART_MDR2_REG(base) = 0;

#undef __LCR
    return RT_EOK;
}

static rt_err_t am33xx_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct am33xx_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct am33xx_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        rt_hw_interrupt_mask(uart->irq);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        rt_hw_interrupt_umask(uart->irq);
        break;
    }

    return RT_EOK;
}

int printkc(char c)
{
    int base = 0xf9e09000;

    while (!(UART_LSR_REG(base) & 0x20));
    UART_THR_REG(base) = c;

    return 1;
}

static int am33xx_putc(struct rt_serial_device *serial, char c)
{
    struct am33xx_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct am33xx_uart *)serial->parent.user_data;

    while (!(UART_LSR_REG(uart->base) & 0x20));
    UART_THR_REG(uart->base) = c;

    return 1;
}

static int am33xx_getc(struct rt_serial_device *serial)
{
    int ch;
    struct am33xx_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct am33xx_uart *)serial->parent.user_data;

    ch = -1;
    if (UART_LSR_REG(uart->base) & 0x01)
    {
        ch = UART_RHR_REG(uart->base) & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops am33xx_uart_ops =
{
    am33xx_configure,
    am33xx_control,
    am33xx_putc,
    am33xx_getc,
};

/* UART1 device driver structure */
struct serial_ringbuffer uart1_int_rx;
struct am33xx_uart uart1 =
{
    UART0_BASE,
    UART0_INT,
};
struct rt_serial_device serial1;

#define write_reg(base, value) *(int*)(base) = value
#define read_reg(base)         *(int*)(base)

#define PRM_PER_INTRANSLATION     (1 << 20)
#define PRM_PER_POWSTATEOFF       (0)
#define PRM_PER_PERMEMSTATEOFF    (0)

static void poweron_per_domain(void)
{
    unsigned long prcm_base;
    unsigned long prm_state;

    prcm_base = AM33XX_PRCM_REGS;

    /* wait for ongoing translations */
    for (prm_state = PRM_PER_PWRSTST_REG(prcm_base);
         prm_state & PRM_PER_INTRANSLATION;
         prm_state = PRM_PER_PWRSTST_REG(prcm_base))
        ;

    /* check power state */
    if ((prm_state & 0x03) == PRM_PER_POWSTATEOFF)
        /* power on PER domain */
        PRM_PER_PWRSTCTRL_REG(prcm_base) |= 0x3;

    /* check per mem state */
    if ((prm_state & 0x03) == PRM_PER_PERMEMSTATEOFF)
        /* power on PER domain */
        PRM_PER_PWRSTCTRL_REG(prcm_base) |= 0x3 << 25;

    while (PRM_PER_PWRSTST_REG(prcm_base) & PRM_PER_INTRANSLATION)
        ;
}

static void start_uart_clk(void)
{
    unsigned long prcm_base;

    prcm_base = AM33XX_PRCM_REGS;

    /* software forced wakeup */
    CM_PER_L4LS_CLKSTCTRL_REG(prcm_base) |= 0x2;

    /* Waiting for the L4LS clock */
    while (!(CM_PER_L4LS_CLKSTCTRL_REG(prcm_base) & (1<<8)))
        ;

    /* enable uart1 */
    CM_PER_UART1_CLKCTRL_REG(prcm_base) |= 0x2;

    /* wait for uart1 clk */
    while ((CM_PER_UART1_CLKCTRL_REG(prcm_base) & (0x3<<16)) != 0)
        ;
    /* Waiting for the L4LS UART clock */
    while (!(CM_PER_L4LS_CLKSTCTRL_REG(prcm_base) & (1<<10)))
        ;
}

static void config_pinmux(void)
{
    unsigned long ctlm_base;

    ctlm_base = AM33XX_CTLM_REGS;

    /* make sure the pin mux is OK for uart */
    REG32(ctlm_base + 0x800 + 0x180) = 0x20;
    REG32(ctlm_base + 0x800 + 0x184) = 0x00;
}

int rt_hw_serial_init(void)
{
    struct am33xx_uart* uart;
    struct serial_configure config;

    uart = &uart1;
    uart->base = UART1_BASE;

    poweron_per_domain();
    start_uart_clk();
    config_pinmux();

    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;

    serial1.ops    = &am33xx_uart_ops;
    serial1.int_rx = &uart1_int_rx;
    serial1.config = config;

    /* enable RX interrupt */
    UART_IER_REG(uart->base) = 0x01;
    /* install ISR */
    rt_hw_interrupt_install(uart->irq, am33xx_uart_isr, &serial1, "uart1");
    rt_hw_interrupt_control(uart->irq, 0, 0);
    rt_hw_interrupt_mask(uart->irq);

    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
            uart);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_serial_init);

