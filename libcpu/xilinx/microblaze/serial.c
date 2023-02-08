/*
 * File      : serial.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-23     Bernard      first version
 * 2009-05-14     Bernard      add RT-THread device interface
 *
 * 2011-12-17     nl1031       MicroBlaze
 */

#include <rthw.h>
#include <rtthread.h>
#include "serial.h"

typedef volatile rt_uint32_t REG32;
struct rt_mb_uart_lite_hw
{
    REG32    Rx_FIFO;   // Receiver Holding Register
    REG32    Tx_FIFO;   // Transmitter Holding Register
    REG32    STAT_REG;  // Channel Status Register
    REG32    CTRL_REG;  // Control Register
};

struct rt_mb_uart_lite
{
    struct rt_device parent;

    struct rt_mb_uart_lite_hw* hw_base;
    rt_uint16_t peripheral_id;
    rt_uint32_t baudrate;

    /* reception field */
    rt_uint16_t save_index, read_index;
    rt_uint8_t  rx_buffer[RT_UART_RX_BUFFER_SIZE];
};
#ifdef RT_USING_UART1
struct rt_mb_uart_lite serial1;
#endif

static void rt_hw_serial_isr(void)
{
    unsigned int status;
    rt_base_t level;
    struct rt_device* device;
    struct rt_mb_uart_lite* serial = RT_NULL;

#ifdef RT_USING_UART1
    /* serial 1 */
    serial = &serial1;
#endif
    RT_ASSERT(serial != RT_NULL);

    /* get generic device object */
    device = (rt_device_t)serial;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* get uart status register */
    status = serial->hw_base->STAT_REG;
    while (status & XUL_SR_RX_FIFO_VALID_DATA)
    {
        /* get received character */
        serial->rx_buffer[serial->save_index] = serial->hw_base->Rx_FIFO;

        /* move to next position */
        serial->save_index ++;
        if (serial->save_index >= RT_UART_RX_BUFFER_SIZE)
            serial->save_index = 0;

        /* if the next position is read index, discard this 'read char' */
        if (serial->save_index == serial->read_index)
        {
            serial->read_index ++;
            if (serial->read_index >= RT_UART_RX_BUFFER_SIZE)
                serial->read_index = 0;
        }
        status = serial->hw_base->STAT_REG;
    }
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    /* indicate to upper layer application */
    if (device->rx_indicate != RT_NULL)
        device->rx_indicate(device, 1);

}

static rt_err_t rt_serial_init (rt_device_t dev)
{
    struct rt_mb_uart_lite* serial = (struct rt_mb_uart_lite*) dev;

    RT_ASSERT(serial != RT_NULL);

    RT_ASSERT(serial->peripheral_id != XPAR_UARTLITE_1_DEVICE_ID);


    /* reset rx index */
    serial->save_index = 0;
    serial->read_index = 0;

    /* reset rx buffer */
    rt_memset(serial->rx_buffer, 0, RT_UART_RX_BUFFER_SIZE);

    return RT_EOK;
}

static rt_err_t rt_serial_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct rt_mb_uart_lite *serial = (struct rt_mb_uart_lite*)dev;
    RT_ASSERT(serial != RT_NULL);

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* enable UART rx interrupt */
        serial->hw_base->CTRL_REG = XUL_CR_ENABLE_INTR;         /* enable interrupt */

        /* install UART handler */
        rt_hw_interrupt_install(serial->peripheral_id, (rt_isr_handler_t)rt_hw_serial_isr, RT_NULL);
        rt_hw_interrupt_umask(serial->peripheral_id);
    }

    return RT_EOK;
}

static rt_err_t rt_serial_close(rt_device_t dev)
{
    struct rt_mb_uart_lite *serial = (struct rt_mb_uart_lite*)dev;
    RT_ASSERT(serial != RT_NULL);

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* disable interrupt */
        serial->hw_base->CTRL_REG =  0;         /* RxReady interrupt */
    }

    return RT_EOK;
}

static rt_ssize_t rt_serial_read (rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_uint8_t* ptr;
    struct rt_mb_uart_lite *serial = (struct rt_mb_uart_lite*)dev;
    RT_ASSERT(serial != RT_NULL);

    /* point to buffer */
    ptr = (rt_uint8_t*) buffer;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        while (size)
        {
            /* interrupt receive */
            rt_base_t level;

            /* disable interrupt */
            level = rt_hw_interrupt_disable();
            if (serial->read_index != serial->save_index)
            {
                *ptr = serial->rx_buffer[serial->read_index];

                serial->read_index ++;
                if (serial->read_index >= RT_UART_RX_BUFFER_SIZE)
                    serial->read_index = 0;
            }
            else
            {
                /* no data in rx buffer */

                /* enable interrupt */
                rt_hw_interrupt_enable(level);
                break;
            }

            /* enable interrupt */
            rt_hw_interrupt_enable(level);

            ptr ++; size --;
        }

        return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
    }
    else if (dev->flag & RT_DEVICE_FLAG_DMA_RX)
    {
        /* not support right now */
        RT_ASSERT(0);
    }
    else
    {
        /* poll mode */
        while (size)
        {
            /* Wait for Full Rx Buffer */
            while (!(serial->hw_base->STAT_REG & XUL_SR_RX_FIFO_VALID_DATA));

            /* Read Character */
            *ptr = serial->hw_base->Rx_FIFO;
            ptr ++;
            size --;
        }

        return (rt_size_t)ptr - (rt_size_t)buffer;
    }

    return 0;
}

static rt_ssize_t rt_serial_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_uint8_t* ptr;
    struct rt_mb_uart_lite *serial = (struct rt_mb_uart_lite*)dev;
    RT_ASSERT(serial != RT_NULL);

    ptr = (rt_uint8_t*) buffer;
    if (dev->open_flag & RT_DEVICE_OFLAG_WRONLY)
    {
        if (dev->flag & RT_DEVICE_FLAG_STREAM)
        {
            /* it's a stream mode device */
            while (size)
            {
                /* stream mode */
                if (*ptr == '\n')
                {
                    while (!(serial->hw_base->STAT_REG & XUL_SR_TX_FIFO_EMPTY));
                    serial->hw_base->Tx_FIFO = '\r';
                }

                /* Wait for Empty Tx Buffer */
                while (!(serial->hw_base->STAT_REG & XUL_SR_TX_FIFO_EMPTY));

                /* Transmit Character */
                serial->hw_base->Tx_FIFO = *ptr;
                if (*ptr & 1)
                    rt_hw_board_led_on(2);
                else
                    rt_hw_board_led_off(2);
                ptr ++; size --;
            }
        }
        else
        {
            while (size)
            {
                /* Wait for Empty Tx Buffer */
                while (!(serial->hw_base->STAT_REG & XUL_SR_TX_FIFO_EMPTY));

                /* Transmit Character */
                serial->hw_base->Tx_FIFO = *ptr;
                if (*ptr & 1)
                    rt_hw_board_led_on(2);
                else
                    rt_hw_board_led_off(2);
                ptr ++; size --;
            }
        }
    }

    return (rt_size_t)ptr - (rt_size_t)buffer;
}

static rt_err_t rt_serial_control (rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

rt_err_t rt_hw_serial_init()
{
    rt_device_t device;

#ifndef RT_USING_CONSOLE
    int Status;

    /*
     * Initialize the UartLite driver so that it is ready to use.
     */
    Status = XUartLite_Initialize(&uart_lite, RS232_DEVICE_ID);
    if (Status != XST_SUCCESS)
    {
        return;
    }

#endif

#ifdef RT_USING_UART1
    device = (rt_device_t) &serial1;

    /* init serial device private data */
    serial1.hw_base         = (struct rt_mb_uart_lite_hw*)XPAR_USB_UART_BASEADDR;
    serial1.peripheral_id   = XPAR_UARTLITE_1_DEVICE_ID;
    serial1.baudrate        = 115200;

    /* set device virtual interface */
    device->init    = rt_serial_init;
    device->open    = rt_serial_open;
    device->close   = rt_serial_close;
    device->read    = rt_serial_read;
    device->write   = rt_serial_write;
    device->control = rt_serial_control;

    /* register uart1 on device subsystem */
    rt_device_register(device, "uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
#endif


    return RT_EOK;
}


