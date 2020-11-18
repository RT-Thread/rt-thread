/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>

#include <rtdevice.h>
#include <drivers/serial.h>

#include "rt_board.h"
#include "arc/arc_timer.h"
#include "arc/arc_exception.h"

#include "embARC_error.h"

static rt_err_t _configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    DEV_UART_PTR uart;
    unsigned int id;
    int ret;

    id = (unsigned int)(serial->parent.user_data);

    uart = uart_get_dev(id);

    ret = uart->uart_control(UART_CMD_SET_BAUD, (void *)(cfg->baud_rate));

    if (ret != E_OK) {
        return RT_ERROR;
    }


    return RT_EOK;
}

static rt_err_t _control(struct rt_serial_device *serial, int cmd, void *arg)
{
    DEV_UART_PTR uart;
    unsigned int id;

    id = (unsigned int)(serial->parent.user_data);
    uart = uart_get_dev(id);

    switch (cmd) {
        case RT_DEVICE_CTRL_CLR_INT:
            uart->uart_control(UART_CMD_SET_RXINT, (void *)0);
            break;
        case RT_DEVICE_CTRL_SET_INT:
            uart->uart_control(UART_CMD_SET_RXINT, (void *)1);
            break;
        case RT_DEVICE_CTRL_SUSPEND:
            uart->uart_control(UART_CMD_DIS_DEV, (void *)0);
            break;
        case RT_DEVICE_CTRL_RESUME:
            uart->uart_control(UART_CMD_ENA_DEV, (void *)0);
            break;

        default:
            return  RT_ERROR;
            break;
    }

    return RT_EOK;
}

static int _putc(struct rt_serial_device *serial, char c)
{
    DEV_UART_PTR uart;
    unsigned int id;
    int ret;

    id = (unsigned int)(serial->parent.user_data);

    uart = uart_get_dev(id);

    ret = uart->uart_write(&c, 1);

    if (ret < 0) {
        return -1;
    } else {
        return 1;
    }
}

static int _getc(struct rt_serial_device *serial)
{
    DEV_UART_PTR uart;
    unsigned int id;
    unsigned int data;
    int ret;
    int rd_avail = 0;

    id = (unsigned int)(serial->parent.user_data);
    uart = uart_get_dev(id);

    uart->uart_control(UART_CMD_GET_RXAVAIL, (void *)(&rd_avail));

    if (rd_avail > 0) {
        ret = uart->uart_read(&data, 1);
    } else {
        return -1;
    }

    if (ret < 0) {
        return -1;
    } else {
        return data;
    }

}

static const struct rt_uart_ops uart_ops =
{
    _configure,
    _control,
    _putc,
    _getc,
};

static struct rt_serial_device uart0;
static struct rt_serial_device uart1;
static struct rt_serial_device uart2;
static struct rt_serial_device uart3;

static void uart0_isr(void *ptr)
{
    rt_hw_serial_isr((struct rt_serial_device*)&uart0, RT_SERIAL_EVENT_RX_IND);
}

static void uart1_isr(void *ptr)
{
    rt_hw_serial_isr((struct rt_serial_device*)&uart1, RT_SERIAL_EVENT_RX_IND);
}

static void uart2_isr(void *ptr)
{
    rt_hw_serial_isr((struct rt_serial_device*)&uart2, RT_SERIAL_EVENT_RX_IND);
}

static void uart3_isr(void *ptr)
{
    rt_hw_serial_isr((struct rt_serial_device*)&uart3, RT_SERIAL_EVENT_RX_IND);
}


int rt_hw_uart_init(void)
{
    DEV_UART_PTR uart;
    struct serial_configure config;
    int ret;

    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    uart0.ops    = &uart_ops;
    uart0.config = config;

    uart1.ops    = &uart_ops;
    uart1.config = config;

    uart2.ops    = &uart_ops;
    uart2.config = config;

    uart3.ops    = &uart_ops;
    uart3.config = config;

    /* uart0 init */
    uart = uart_get_dev(0);

    if (uart != NULL) {
        /* default format: 8bits, no parity, 1 stop bits */
        ret = uart->uart_open(config.baud_rate);

        if (ret != E_OPNED && ret != E_OK) {
            return RT_ERROR;
        }

        /* enable rx int */
        uart->uart_control(UART_CMD_SET_RXINT, (void *)0);
        /* use customized int isr */
        uart->uart_control(UART_CMD_SET_RXCB, uart0_isr);
        uart->uart_control(UART_CMD_SET_RXINT_BUF, NULL);

        rt_hw_serial_register(&uart0, "uart0",
                            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                            (void *)0);
    }

    /* uart1 init */
    uart = uart_get_dev(1);

    if (uart != NULL) {
        /* default format: 8bits, no parity, 1 stop bits */
        ret = uart->uart_open(config.baud_rate);

        if (ret != E_OPNED && ret != E_OK) {
            return RT_ERROR;
        }

        /* enable rx int */
        uart->uart_control(UART_CMD_SET_RXINT, (void *)0);
        /* use customized int isr */
        uart->uart_control(UART_CMD_SET_RXCB, uart1_isr);
        uart->uart_control(UART_CMD_SET_RXINT_BUF, NULL);

        rt_hw_serial_register(&uart1, "uart1",
                            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                            (void *)1);
    }

    /* uart2 init */
    uart = uart_get_dev(2);

    if (uart != NULL) {
        /* default format: 8bits, no parity, 1 stop bits */
        ret = uart->uart_open(config.baud_rate);

        if (ret != E_OPNED && ret != E_OK) {
            return RT_ERROR;
        }

        /* enable rx int */
        uart->uart_control(UART_CMD_SET_RXINT, (void *)0);
        /* use customized int isr */
        uart->uart_control(UART_CMD_SET_RXCB, uart2_isr);
        uart->uart_control(UART_CMD_SET_RXINT_BUF, NULL);

        rt_hw_serial_register(&uart2, "uart2",
                            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                            (void *)2);
    }

    /* uart3 init */
    uart = uart_get_dev(3);

    if (uart != NULL) {
        /* default format: 8bits, no parity, 1 stop bits */
        ret = uart->uart_open(config.baud_rate);

        if (ret != E_OPNED && ret != E_OK) {
            return RT_ERROR;
        }

        /* enable rx int */
        uart->uart_control(UART_CMD_SET_RXINT, (void *)0);
        /* use customized int isr */
        uart->uart_control(UART_CMD_SET_RXCB, uart3_isr);
        uart->uart_control(UART_CMD_SET_RXINT_BUF, NULL);

        rt_hw_serial_register(&uart3, "uart3",
                            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                            (void *)3);
    }

    return RT_EOK;
}

#if defined BOARD_EMSK
#define CONSOLE_UART "uart1"
struct rt_serial_device *console_uart = &uart1;
#elif defined BOARD_IOTDK || defined BOARD_EMSDP || defined BOARD_NSIM
#define CONSOLE_UART "uart0"
struct rt_serial_device *console_uart = &uart0;
#elif defined BOARD_AXS
#define CONSOLE_UART "uart2"
struct rt_serial_device *console_uart = &uart2;
#elif defined BOARD_HSDK
#define CONSOLE_UART "uart3"
struct rt_serial_device *console_uart = &uart3;
#else
#error "no supported board selected!"
#endif

void rt_hw_console_output(const char *str)
{
    while(*str != '\0')
    {
        if (*str == '\n') {
            _putc(console_uart,'\r');
        }
        _putc(console_uart,*str);
        str++;
    }
}

void rt_hw_board_init()
{
    rt_hw_uart_init();
    rt_components_board_init();
    rt_console_set_device(CONSOLE_UART);
}



static void rt_hw_timer_isr(int vector, void *param)
{
    timer_int_clear(BOARD_OS_TIMER_ID);
    rt_tick_increase();
}

int rt_hw_timer_init(void)
{

    unsigned int cyc = BOARD_CPU_CLOCK / RT_TICK_PER_SECOND;

    int_disable(BOARD_OS_TIMER_INTNO); /* disable os timer interrupt */
    timer_stop(BOARD_OS_TIMER_ID);
    timer_start(BOARD_OS_TIMER_ID, TIMER_CTRL_IE | TIMER_CTRL_NH, cyc);

    int_handler_install(BOARD_OS_TIMER_INTNO, (INT_HANDLER_T)rt_hw_timer_isr);
    int_pri_set(BOARD_OS_TIMER_INTNO, INT_PRI_MIN + 1); /* currently, firq(INT_PRI_MIN) not supported*/
    int_enable(BOARD_OS_TIMER_INTNO);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);
