/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-06     Bernard    the first version
 * 2014-01-11     RTsien     support UART0 to UART5 straightly
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <am33xx.h>
#include <interrupt.h>
#include "uart.h"
#include "uart_reg.h"

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
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
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
    else if (cfg->baud_rate == BAUD_RATE_9600)
    {
        UART_DLL_REG(base) = 0x38;
        UART_DLH_REG(base) = 1;
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

/* UART device driver structure */
#ifdef RT_USING_UART0
struct am33xx_uart uart0 =
{
    UART0_BASE,
    UART0_INT,
};
struct rt_serial_device serial0;
#endif

#ifdef RT_USING_UART1
struct am33xx_uart uart1 =
{
    UART1_BASE,
    UART1_INT,
};
struct rt_serial_device serial1;
#endif

#ifdef RT_USING_UART2
struct am33xx_uart uart2 =
{
    UART2_BASE,
    UART2_INT,
};
struct rt_serial_device serial2;
#endif

#ifdef RT_USING_UART3
struct am33xx_uart uart3 =
{
    UART3_BASE,
    UART3_INT,
};
struct rt_serial_device serial3;
#endif

#ifdef RT_USING_UART4
struct am33xx_uart uart4 =
{
    UART4_BASE,
    UART4_INT,
};
struct rt_serial_device serial4;
#endif

#ifdef RT_USING_UART5
struct am33xx_uart uart5 =
{
    UART5_BASE,
    UART5_INT,
};
struct rt_serial_device serial5;
#endif

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

#if defined(RT_USING_UART1) || defined(RT_USING_UART2) || defined(RT_USING_UART3) || defined(RT_USING_UART4) || defined(RT_USING_UART5)
    /* software forced wakeup */
    CM_PER_L4LS_CLKSTCTRL_REG(prcm_base) |= 0x2;

    /* Waiting for the L4LS clock */
    while (!(CM_PER_L4LS_CLKSTCTRL_REG(prcm_base) & (1<<8)))
        ;

    /* enable uart1 */
#ifdef RT_USING_UART1
    CM_PER_UART1_CLKCTRL_REG(prcm_base) |= 0x2;
    /* wait for uart1 clk */
    while ((CM_PER_UART1_CLKCTRL_REG(prcm_base) & (0x3<<16)) != 0)
        ;
#endif

#ifdef RT_USING_UART2
    CM_PER_UART2_CLKCTRL_REG(prcm_base) |= 0x2;
    /* wait for uart2 clk */
    while ((CM_PER_UART2_CLKCTRL_REG(prcm_base) & (0x3<<16)) != 0)
        ;
#endif

#ifdef RT_USING_UART3
    CM_PER_UART3_CLKCTRL_REG(prcm_base) |= 0x2;
    /* wait for uart3 clk */
    while ((CM_PER_UART3_CLKCTRL_REG(prcm_base) & (0x3<<16)) != 0)
        ;
#endif

#ifdef RT_USING_UART4
    CM_PER_UART4_CLKCTRL_REG(prcm_base) |= 0x2;
    /* wait for uart4 clk */
    while ((CM_PER_UART4_CLKCTRL_REG(prcm_base) & (0x3<<16)) != 0)
        ;
#endif

#ifdef RT_USING_UART5
    CM_PER_UART5_CLKCTRL_REG(prcm_base) |= 0x2;
    /* wait for uart5 clk */
    while ((CM_PER_UART5_CLKCTRL_REG(prcm_base) & (0x3<<16)) != 0)
        ;
#endif

    /* Waiting for the L4LS UART clock */
    while (!(CM_PER_L4LS_CLKSTCTRL_REG(prcm_base) & (1<<10)))
        ;
#endif

#ifdef RT_USING_UART0
    /* software forced wakeup */
    CM_WKUP_CLKSTCTRL_REG(prcm_base) |= 0x2;

    /* Waiting for the L4_WKUP clock */
    while (!(CM_WKUP_CLKSTCTRL_REG(prcm_base) & (1<<2)))
        ;

    /* enable uart0 */
    CM_WKUP_UART0_CLKCTRL_REG(prcm_base) |= 0x2;
    /* wait for uart0 clk */
    while ((CM_WKUP_UART0_CLKCTRL_REG(prcm_base) & (0x3<<16)) != 0)
        ;

    /* Waiting for the L4_WKUP UART0 clock */
    while (!(CM_WKUP_CLKSTCTRL_REG(prcm_base) & (1<<12)))
        ;
#endif
}

static void config_pinmux(void)
{
    unsigned long ctlm_base;

    ctlm_base = AM33XX_CTLM_REGS;

    /* make sure the pin mux is OK for uart */
#ifdef RT_USING_UART0
    REG32(ctlm_base + 0x800 + 0x170) = 0x20;
    REG32(ctlm_base + 0x800 + 0x174) = 0x00;
#endif

#ifdef RT_USING_UART1
    REG32(ctlm_base + 0x800 + 0x180) = 0x20;
    REG32(ctlm_base + 0x800 + 0x184) = 0x00;
#endif

#ifdef RT_USING_UART2
    REG32(ctlm_base + 0x800 + 0x150) = 0x20;
    REG32(ctlm_base + 0x800 + 0x154) = 0x00;
#endif

#ifdef RT_USING_UART3
    REG32(ctlm_base + 0x800 + 0x164) = 0x01;
#endif

#ifdef RT_USING_UART4
    REG32(ctlm_base + 0x800 + 0x070) = 0x26;
    REG32(ctlm_base + 0x800 + 0x074) = 0x06;
#endif

#ifdef RT_USING_UART5
    REG32(ctlm_base + 0x800 + 0x0C4) = 0x24;
    REG32(ctlm_base + 0x800 + 0x0C0) = 0x04;
#endif
}

int rt_hw_serial_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    poweron_per_domain();
    start_uart_clk();
    config_pinmux();

#ifdef RT_USING_UART0
    serial0.ops    = &am33xx_uart_ops;
    serial0.config = config;

    /* enable RX interrupt */
    UART_IER_REG(uart0.base) = 0x01;
    /* install ISR */
    rt_hw_interrupt_install(uart0.irq, am33xx_uart_isr, &serial0, "uart0");
    rt_hw_interrupt_control(uart0.irq, 0, 0);
    rt_hw_interrupt_mask(uart0.irq);
    /* register UART0 device */
    rt_hw_serial_register(&serial0, "uart0",
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
            &uart0);
#endif

#ifdef RT_USING_UART1
    serial1.ops    = &am33xx_uart_ops;
    serial1.config = config;
    /* enable RX interrupt */
    UART_IER_REG(uart1.base) = 0x01;
    /* install ISR */
    rt_hw_interrupt_install(uart1.irq, am33xx_uart_isr, &serial1, "uart1");
    rt_hw_interrupt_control(uart1.irq, 0, 0);
    rt_hw_interrupt_mask(uart1.irq);
    /* register UART0 device */
    rt_hw_serial_register(&serial1, "uart1",
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
            &uart1);
#endif

#ifdef RT_USING_UART2
    serial2.ops    = &am33xx_uart_ops;
    serial2.config = config;
    /* enable RX interrupt */
    UART_IER_REG(uart2.base) = 0x01;
    /* install ISR */
    rt_hw_interrupt_install(uart2.irq, am33xx_uart_isr, &serial2, "uart2");
    rt_hw_interrupt_control(uart2.irq, 0, 0);
    rt_hw_interrupt_mask(uart2.irq);
    /* register UART2 device */
    rt_hw_serial_register(&serial2, "uart2",
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
            &uart2);
#endif

#ifdef RT_USING_UART3
    serial3.ops    = &am33xx_uart_ops;
    serial3.config = config;
    /* enable RX interrupt */
    UART_IER_REG(uart3.base) = 0x01;
    /* install ISR */
    rt_hw_interrupt_install(uart3.irq, am33xx_uart_isr, &serial3, "uart3");
    rt_hw_interrupt_control(uart3.irq, 0, 0);
    rt_hw_interrupt_mask(uart3.irq);
    /* register UART3 device */
    rt_hw_serial_register(&serial3, "uart3",
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
            &uart3);
#endif

#ifdef RT_USING_UART4
    /* use 9600bps for GDB stub. */
    config.baud_rate = BAUD_RATE_9600;

    serial4.ops    = &am33xx_uart_ops;
    serial4.config = config;
    /* enable RX interrupt */
    UART_IER_REG(uart4.base) = 0x00;
    /* install ISR */
    rt_hw_interrupt_install(uart4.irq, am33xx_uart_isr, &serial4, "uart4");
    rt_hw_interrupt_control(uart4.irq, 0, 0);
    rt_hw_interrupt_mask(uart4.irq);
    /* register UART4 device */
    rt_hw_serial_register(&serial4, "uart4",
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
            &uart4);
#endif

#ifdef RT_USING_UART5
    config.baud_rate = BAUD_RATE_115200;

    serial5.ops    = &am33xx_uart_ops;
    serial5.config = config;
    /* enable RX interrupt */
    UART_IER_REG(uart5.base) = 0x01;
    /* install ISR */
    rt_hw_interrupt_install(uart5.irq, am33xx_uart_isr, &serial5, "uart5");
    rt_hw_interrupt_control(uart5.irq, 0, 0);
    rt_hw_interrupt_mask(uart5.irq);
    /* register UART4 device */
    rt_hw_serial_register(&serial5, "uart5",
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
            &uart5);
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_serial_init);
