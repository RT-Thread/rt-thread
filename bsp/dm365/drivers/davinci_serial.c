/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-01-13     weety     first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <dm36x.h>
#include <rtdevice.h>

static struct rt_serial_device davinci_serial_dev0;

static struct rt_serial_device davinci_serial_dev1;


#define LSR_DR      0x01        /* Data ready */
#define LSR_THRE    0x20        /* Xmit holding register empty */
//#define   USTAT_TXB_EMPTY     0x02    /* tx buffer empty */
#define BPS                 115200  /* serial baudrate */

typedef struct uartport
{
    volatile rt_uint32_t rbr;
    volatile rt_uint32_t ier;
    volatile rt_uint32_t fcr;
    volatile rt_uint32_t lcr;
    volatile rt_uint32_t mcr;
    volatile rt_uint32_t lsr;
    volatile rt_uint32_t msr;
    volatile rt_uint32_t scr;
    volatile rt_uint32_t dll;
    volatile rt_uint32_t dlh;

    volatile rt_uint32_t res[2];
    volatile rt_uint32_t pwremu_mgmt;
    volatile rt_uint32_t mdr;
}uartport;

#define thr rbr
#define iir fcr

#define UART0   ((struct uartport *)DAVINCI_UART0_BASE)

#define UART1   ((struct uartport *)DM365_UART1_BASE)


/**
 * This function will handle serial
 */
void rt_davinci_serial_handler(int vector, void *param)
{
    struct rt_serial_device *dev = (struct rt_serial_device *)param;
    rt_hw_serial_isr(dev, RT_SERIAL_EVENT_RX_IND);
}

/**
* UART device in RT-Thread
*/
static rt_err_t davinci_uart_configure(struct rt_serial_device *serial,
                                struct serial_configure *cfg)
{
    return RT_EOK;
}

static rt_err_t davinci_uart_control(struct rt_serial_device *serial,
                              int cmd, void *arg)
{
    uartport *uart = serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        if (uart == UART0)
            rt_hw_interrupt_mask(IRQ_UARTINT0);
        else if (uart == UART1)
            rt_hw_interrupt_mask(IRQ_UARTINT1);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        if (uart == UART0)
            rt_hw_interrupt_umask(IRQ_UARTINT0);
        else if (uart == UART1)
            rt_hw_interrupt_umask(IRQ_UARTINT1);
        break;
    }

    return RT_EOK;
}

static int davinci_uart_putc(struct rt_serial_device *serial, char c)
{
    rt_uint32_t level;
    uartport *uart = serial->parent.user_data;

    while (!(uart->lsr & LSR_THRE));
    uart->thr = c;

    return 1;
}

static int davinci_uart_getc(struct rt_serial_device *serial)
{
    int result;
    uartport *uart = serial->parent.user_data;

    if (uart->lsr & LSR_DR)
    {
        result = uart->rbr & 0xff;
    }
    else
    {
        result = -1;
    }

    return result;
}

static const struct rt_uart_ops davinci_uart_ops =
{
    davinci_uart_configure,
    davinci_uart_control,
    davinci_uart_putc,
    davinci_uart_getc,
};

void davinci_uart0_init(void)
{
    rt_uint32_t divisor;

    divisor = (24000000 + (115200 * (16 / 2))) / (16 * 115200);
    UART0->ier = 0;
    UART0->lcr = 0x83; //8N1
    UART0->dll = 0;
    UART0->dlh = 0;
    UART0->lcr = 0x03;
    UART0->mcr = 0x03; //RTS,CTS
    UART0->fcr = 0x07; //FIFO
    UART0->lcr = 0x83;
    UART0->dll = divisor & 0xff;
    UART0->dlh = (divisor >> 8) & 0xff;
    UART0->lcr = 0x03;
    UART0->mdr = 0; //16x over-sampling
    UART0->pwremu_mgmt = 0x6000;
    rt_hw_interrupt_install(IRQ_UARTINT0, rt_davinci_serial_handler,
                            (void *)&davinci_serial_dev0, "UART0");
    rt_hw_interrupt_mask(IRQ_UARTINT0);
    UART0->ier = 0x05;
}

void davinci_uart_gpio_init()
{
    rt_uint32_t val;

    val = davinci_readl(PINMUX3);
    val &= 0xf3ffffff; /* gio23 RS485_CTRL */
    val |= 0x60000000; /*UART1_TXD (gio25)*/
    davinci_writel(val, PINMUX3);
    val = davinci_readl(PINMUX4);
    val |= 0x0000c000; /* UART1_RXD (gio34) */
    davinci_writel(val, PINMUX4);

    val = davinci_readl(DAVINCI_GPIO_BASE + 0x10);
    val &= ~(1 << 23);
    davinci_writel(val, DAVINCI_GPIO_BASE + 0x10);
    davinci_writel((1<<23), DAVINCI_GPIO_BASE + 0x1C);
}

void davinci_uart1_init(void)
{
    rt_uint32_t divisor;
    rt_uint32_t freq;
    rt_uint32_t baudrate;
    struct clk *clk;

    davinci_uart_gpio_init();
    psc_change_state(DAVINCI_DM365_LPSC_UART1, PSC_ENABLE);
    clk = clk_get("UART1");
    freq = clk_get_rate(clk);

    baudrate = 9600;
    divisor = (freq + (baudrate * (16 / 2))) / (16 * baudrate);
    UART1->ier = 0;
    UART1->lcr = 0x87; //8N2, 0x83 8N1
    UART1->dll = 0;
    UART1->dlh = 0;
    UART1->lcr = 0x07;
    UART1->mcr = 0x03; //RTS,CTS
    UART1->fcr = 0x07; //FIFO
    UART1->lcr = 0x87;
    UART1->dll = divisor & 0xff;
    UART1->dlh = (divisor >> 8) & 0xff;
    UART1->lcr = 0x07;
    UART1->mdr = 0; //16x over-sampling
    UART1->pwremu_mgmt = 0x6000;

    rt_hw_interrupt_install(IRQ_UARTINT1, rt_davinci_serial_handler,
                            (void *)&davinci_serial_dev1, "UART1");
    rt_hw_interrupt_mask(IRQ_UARTINT1);
    UART1->ier = 0x05;
}


/**
 * This function will handle init uart
 */
int rt_hw_uart_init(void)
{
    davinci_serial_dev0.ops = &davinci_uart_ops;
    //davinci_serial_dev0.config = RT_SERIAL_CONFIG_DEFAULT;
    davinci_serial_dev0.config.baud_rate = BAUD_RATE_115200;
    davinci_serial_dev0.config.bit_order = BIT_ORDER_LSB;
    davinci_serial_dev0.config.data_bits = DATA_BITS_8;
    davinci_serial_dev0.config.parity = PARITY_NONE;
    davinci_serial_dev0.config.stop_bits = STOP_BITS_1;
    davinci_serial_dev0.config.invert = NRZ_NORMAL;
    davinci_serial_dev0.config.bufsz = RT_SERIAL_RB_BUFSZ;

    /* register vcom device */
    rt_hw_serial_register(&davinci_serial_dev0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          UART0);
    davinci_uart0_init();

    davinci_serial_dev1.ops = &davinci_uart_ops;
    //davinci_serial_dev1.config = RT_SERIAL_CONFIG_DEFAULT;
    davinci_serial_dev1.config.baud_rate = BAUD_RATE_115200;
    davinci_serial_dev1.config.bit_order = BIT_ORDER_LSB;
    davinci_serial_dev1.config.data_bits = DATA_BITS_8;
    davinci_serial_dev1.config.parity = PARITY_NONE;
    davinci_serial_dev1.config.stop_bits = STOP_BITS_1;
    davinci_serial_dev1.config.invert = NRZ_NORMAL;
    davinci_serial_dev1.config.bufsz = RT_SERIAL_RB_BUFSZ;

    /* register vcom device */
    rt_hw_serial_register(&davinci_serial_dev1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          UART1);
    davinci_uart1_init();

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_uart_init);

