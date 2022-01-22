/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-05-30     Bernard      the first version
 * 2018-03-15     flyingcys    add amebaz
 */
#include <rtl8710b.h>
#include <serial_api.h>
#include "board.h"
#include "drv_uart.h"

struct device_uart
{
    serial_t serial;

    rt_uint32_t irqno;
};

extern int LOGUART_SetBaud(u32 BaudRate);

#ifdef BSP_USING_UART0
static struct rt_serial_device  serial0;
static struct device_uart       uart0;
#endif

static rt_err_t  ameba_uart_configure    (struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t  ameba_uart_control      (struct rt_serial_device *serial, int cmd, void *arg);
static int       ameba_uart_putc         (struct rt_serial_device *serial, char c);
static int       ameba_uart_getc         (struct rt_serial_device *serial);
static rt_size_t ameba_uart_dma_transmit (struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction);

static void ameba_uart_irq(uint32_t id, SerialIrq event);

const struct rt_uart_ops _uart_ops =
{
    ameba_uart_configure,
    ameba_uart_control,
    ameba_uart_putc,
    ameba_uart_getc,
    ameba_uart_dma_transmit
};

/*
 * UART interface
 */
static rt_err_t ameba_uart_configure (struct rt_serial_device *serial, struct serial_configure *cfg)
{
     struct device_uart * uart;

     RT_ASSERT(serial != RT_NULL);
     serial->config = *cfg;

     uart = serial->parent.user_data;
     RT_ASSERT(uart != RT_NULL);

     /* Set databits, stopbits and parity. (8-bit data, 1 stopbit, no parity) */
     serial_format(&uart->serial, 8, ParityNone, 1);

     /* set baudrate */
     serial_baud(&uart->serial, 115200);

     return (RT_EOK);
}

static rt_err_t ameba_uart_control (struct rt_serial_device *serial, int cmd, void *arg)
{
    struct device_uart * uart;

    uart = serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable the UART Interrupt */
        serial_irq_set(&uart->serial, RxIrq, 0);
        serial_irq_handler(&uart->serial, RT_NULL, 0);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* install interrupt */
        serial_irq_handler(&uart->serial, ameba_uart_irq, (uint32_t)serial);

        /* Enable the UART Interrupt */
        serial_irq_set(&uart->serial, RxIrq, 1);
        break;
    }

    return (RT_EOK);
}

static int ameba_uart_putc (struct rt_serial_device *serial, char c)
{
    struct device_uart* uart;

    uart = serial->parent.user_data;

    /* FIFO status, contain valid data */
    /* write data */
    serial_putc(&uart->serial, c);

    return (1);
}

static int ameba_uart_getc (struct rt_serial_device *serial)
{
    struct device_uart* uart = serial->parent.user_data;

    if(!serial_readable(&uart->serial))
        return -1;

    /* Receive Data Available */
    return serial_getc(&uart->serial);
}

static rt_size_t ameba_uart_dma_transmit (struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    return (0);
}

static void ameba_uart_irq(uint32_t id, SerialIrq event)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)id;
    if(event == RxIrq)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    else if(event == TxIrq)
    {
    }
}

static rt_err_t dbg_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t dbg_control(struct rt_serial_device *serial, int cmd, void *arg);
static int dbg_putc(struct rt_serial_device *serial, char c);
static int dbg_getc(struct rt_serial_device *serial);

static struct rt_serial_device ameba_dbg_serial;
const struct rt_uart_ops _ambed_dbg_ops =
{
    dbg_configure,
    dbg_control,
    dbg_putc,
    dbg_getc,
    RT_NULL,
};

static rt_err_t dbg_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    LOGUART_SetBaud(115200);
    return RT_EOK;
}

void dbg_uart_irq_handler(void * data)
{
    u32 IrqEn = DiagGetIsrEnReg();

    DiagSetIsrEnReg(0);

    rt_hw_serial_isr(&ameba_dbg_serial, RT_SERIAL_EVENT_RX_IND);

    DiagSetIsrEnReg(IrqEn);
}

static rt_err_t dbg_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable the UART Interrupt */
        NVIC_DisableIRQ(UART_LOG_IRQ); /* this is rom_code_patch */
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* install interrupt */
        DIAG_UartReInit((IRQ_FUN) dbg_uart_irq_handler);
        /* Enable the UART Interrupt */
        NVIC_SetPriority(UART_LOG_IRQ, 10); /* this is rom_code_patch */
        break;
    }

    return (RT_EOK);
}

static int dbg_putc(struct rt_serial_device *serial, char c)
{
    DiagPutChar(c);

    return 1;
};

static int dbg_getc(struct rt_serial_device *serial)
{
    int c = -1;

    if(!UART_Readable(UART2_DEV))
        return -1;

    c = DiagGetChar(_FALSE);

    return c;
}

/*
 * UART Initiation
 */
int rt_hw_uart_init(void)
{
    struct rt_serial_device *serial;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART0
    {
        struct device_uart      *uart;

        serial  = &serial0;
        uart    = &uart0;

        /* Init UART Hardware */
        serial_init(&uart->serial, UART_TX, UART_RX);

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = 115200;

        uart->irqno     = UART0_IRQ;

        rt_hw_serial_register(serial,
                              "uart0",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif

    {
        serial  = &ameba_dbg_serial;

        serial->ops = &_ambed_dbg_ops;
        serial->config = config;

        rt_hw_serial_register(serial,
                              RT_CONSOLE_DEVICE_NAME,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              RT_NULL);
    }
    return 0;
}
