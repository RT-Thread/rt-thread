/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021/04/22     Juice           Add UART0 support for JuiceVm.
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_uart.h"

#include "rv_mtvec_map.h"

struct rt_serial_device *serial;
char *device_name = "uart0";

static rt_err_t  uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t  uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int       uart_putc(struct rt_serial_device *serial, char c);
static int       uart_getc(struct rt_serial_device *serial);
static rt_size_t uart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction);

void UART0_DriverIRQHandler(void);

const struct rt_uart_ops _uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
    uart_dma_transmit
};

static void uart_isr(struct rt_serial_device *serial);

#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;

void UART0_DriverIRQHandler(void)
{
    uart_isr(&serial0);
}
#endif



/*
 * UART Initiation
 */
int rt_hw_uart_init(void)
{
    int i;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    serial = &serial0;
    serial->ops    = &_uart_ops;
    serial->config = config;

    /* register UART device */
    rt_hw_serial_register(serial,
                          device_name,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          (void *)0);

    return 0;
}

/*
 * UART interface
 */
static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    RT_ASSERT(serial != RT_NULL);

    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char c)
{

    RT_ASSERT(serial != RT_NULL);

    *((char *)(pdev_uart0_write_addr)) = c;

    return (1);
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;

    RT_ASSERT(serial != RT_NULL);

    ch = -1;

    if (*(char *)(pdev_uart0_state_addr) == pdev_uart0_readbusy_state)
    {
        ch = *(char *)(pdev_uart0_read_addr);
        *(char *)(pdev_uart0_state_addr) = pdev_uart0_free_state;
    }
    return ch;
}

static rt_size_t uart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    return (0);
}

/* UART ISR */
/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    RT_ASSERT(serial != RT_NULL);

    if (*(char *)(pdev_uart0_state_addr) == pdev_uart0_readbusy_state)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
}
